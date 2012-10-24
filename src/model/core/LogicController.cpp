#include "../_include/LogicController.h"

// Dependencies
#include <algorithm>
#include <utility>
#include "../../common/_include/Exception.h"
#include "../_include/BaseController.h"
#include "../_include/Resource.h"
#include "../_include/SimpleGraph.h"

#define INITIAL_ID 1

LogicController LogicController::instance_;

LogicController::LogicController ()
: base_(BaseControl),
  idCount_(INITIAL_ID)
// Do nothing.
{
}

LogicController::~LogicController ()
// Clean up all graphs.
{
    std::for_each(graphs_.begin(), graphs_.end(),
                  [] (std::pair<Identity, Graph*> it) {
                      delete it.second;
                  });
}

Identity LogicController::newGraph ()
// Create a new graph, assign idCount_, and increment idCount_.
{
    Identity newId = newIdentity();
    SimpleGraph *g = new SimpleGraph(newId);
    graphs_.insert(std::make_pair(newId, g));
    return newId;
}

Identity LogicController::newVertex (const Identity g_id)
// Create a new vertex and assign it to the graph corresponding to g_id.
// Throw if g_id is not valid.
{
    auto it = graphs_.find(g_id);
    if (it == graphs_.end()) {
        throw BadArgumentExcept();
    }

    Identity newId = newIdentity();
    if (base_.newVertex(newId) == NULL) {
        throw RuntimeExcept();
    }

    it->second->addVertex(newId);
    register_.insert(std::make_pair(newId, g_id));
    return newId;
}

bool LogicController::remGraph (const Identity g_id)
// Return false if g_id isn't valid.
// Otherwise, remove the graph and its corresponding vertices.
{
    if (graphs_.find(g_id) == graphs_.end()) {
        return false;
    }

    Graph *g = graphs_[g_id];
    Graph::VertexList list = g->getVertices();
    std::for_each(list.begin(), list.end(),
                  [&] (const Identity id) {
                      register_.erase(id);
                  });
    graphs_.erase(g_id);
    delete g;

    return true;
}

bool LogicController::remVertex (const Identity v_id)
// Return false if v_id isn't valid.
// Otherwise, remove the vertex.
{
    auto it = register_.find(v_id);
    if (it == register_.end()) {
        return false;
    }

    Graph *g = graphs_[it->second];
    if (!g->remVertex(v_id)) {
        return false;
    }

    register_.erase(v_id);
    return true;
}

Identity LogicController::newIdentity ()
{
    if (idCount_ >= UINT32_MAX) {
        throw OverflowExcept();
    }
    return (idCount_++);
}
