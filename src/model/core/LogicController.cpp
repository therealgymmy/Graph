#include "../_include/LogicController.h"

// Dependencies
#include <algorithm>
#include <utility>
#include "../../common/_include/Exception.h"
#include "../_include/Resource.h"
#include "../_include/SimpleGraph.h"

#define INITIAL_ID 1

LogicController LogicController::instance_;

LogicController::LogicController (BaseController &base)
: base_(base),
  idCount_(INITIAL_ID)
// Do nothing.
{
}

#include <iostream>

LogicController::~LogicController ()
// Clean up all graphs.
{
    clear();
}

void LogicController::clear ()
{
    IdentityList list;
    std::for_each(graphs_.begin(), graphs_.end(),
                  [&] (std::pair<Identity, Graph*> it) {
                      //delete it.second;
                  std::cout << it.first << std::endl;
                      list.insert(it.first);
                  });
    std::for_each(list.begin(), list.end(),
                  [&] (Identity g) {
                      remGraph(g);
                  });
}

bool LogicController::hasGraph (const Identity g_id) const
{
    if (graphs_.find(g_id) == graphs_.end()) {
        return false;
    }
    return true;
}

bool LogicController::hasVertex (const Identity v_id) const
{
    if (register_.find(v_id) == register_.end()) {
        return false;
    }
    return true;
}

bool LogicController::isJointBetween (const Identity v1_id, const Identity v2_id) const
{
    if (!hasVertex(v1_id) || !hasVertex(v2_id)) {
        return false;
    }
    return base_.isJoint(v1_id, v2_id);
}

Identity LogicController::graphOf (const Identity v_id) const
{
    auto it = register_.find(v_id);
    if (it == register_.end()) {
        throw BadArgumentExcept();
    }
    return it->second;
}

Graph::VertexList LogicController::verticesOf (const Identity g_id) const
{
    auto it = graphs_.find(g_id);
    if (it == graphs_.end()) {
        throw BadArgumentExcept();
    }
    return it->second->getVertices();
}

Graph::VertexList LogicController::neighboursOf (const Identity v_id) const
{
    if (!hasVertex(v_id)) {
        throw BadArgumentExcept();
    }
    return base_.getNeighbours(v_id);
}

Graph::GraphList LogicController::allGraphs () const
{
    Graph::GraphList list;
    std::for_each(graphs_.begin(), graphs_.end(),
                  [&] (std::pair<Identity, Graph*> it) {
                      list.insert(it.first);
                  });
    return list;
}

Graph::VertexList LogicController::allVertices () const
{
    Graph::VertexList list;
    std::for_each(register_.begin(), register_.end(),
                  [&] (std::pair<Identity, Identity> it) {
                      list.insert(it.first);
                  });
    return list;
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
    std::for_each(list.begin(), list.end(),
                  [&] (const Identity id) {
                      base_.removeVertex(id);
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
    base_.removeVertex(v_id);
    return true;
}

bool LogicController::join (const Identity v1_id, const Identity v2_id)
// Return false if v1_id or v2_id doesn't exist or are in different graphs,
//  or are already joint.
{
    auto v1_it = register_.find(v1_id);
    auto v2_it = register_.find(v2_id);
    if (v1_it == register_.end() ||
        v2_it == register_.end() ||
        v1_it->second != v2_it->second) {
        return false;
    }

    // Create new edge id, and join v1 & v2.
    Identity e_id;
    try {
        e_id = newIdentity();
    }
    catch (OverflowExcept &err) {
        return false;
    }

    if (base_.join(e_id, v1_id, v2_id) == NULL) {
        return false;
    }
    return true;
}

bool LogicController::disjoin (const Identity v1_id, const Identity v2_id)
// Return false if v1_id or v2_id doesn't exist or are in different graphs,
//  or are not joint.
{
    auto v1_it = register_.find(v1_id);
    auto v2_it = register_.find(v2_id);
    if (v1_it == register_.end() ||
        v2_it == register_.end() ||
        v1_it->second != v2_it->second) {
        return false;
    }

    return base_.disjoin(v1_id, v2_id);
}

Identity LogicController::newIdentity ()
{
    if (idCount_ >= UINT32_MAX) {
        throw OverflowExcept();
    }
    return (idCount_++);
}
