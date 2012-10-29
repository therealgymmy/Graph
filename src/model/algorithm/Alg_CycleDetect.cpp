#include "../_include/Alg_CycleDetect.h"

// Dependencies
#include <algorithm>
#include <map>
#include <utility>
#include "../_include/Graph.h"
#include "../_include/LogicController.h"
#include "../_include/ModelTypes.h"

class CycleFound {};

class NodeStatus {
public:
    enum Color {
        WHITE,      // not yet visited
        GREY,       // being visited
        BLACK,      // done visited
    };

    void visit (const Identity id);
    void leave (const Identity id);
    Color statusOf (const Identity id) const;

private:
    std::map<Identity, Color> status_;
};

void NodeStatus::visit (const Identity id)
{
    status_[id] = GREY;
}

void NodeStatus::leave (const Identity id)
{
    status_[id] = BLACK;
}

NodeStatus::Color NodeStatus::statusOf (const Identity id) const
{
    auto it = status_.find(id);
    if (it == status_.end()) {
        return WHITE;
    }
    return it->second;
}

CycleDetect::Result CycleDetect::run (const CycleDetect::Parameter& parm)
{
    Identity g_id = parm.id_;
    Result result = { .hasCycle_ = false };

    NodeStatus node;
    Graph::VertexList list = LogicControl.verticesOf(g_id);
    try {
        findCycle(*list.begin(), NULL_IDENTITY, &node);
    }
    catch (CycleFound&) {
        result.hasCycle_ = true;
    }

    return result;
}

void CycleDetect::findCycle (const Identity v_id,
                             const Identity parent_id,
                             NodeStatus *node)
{
    if (node->statusOf(v_id) == NodeStatus::GREY) {
        throw CycleFound();
    }

    node->visit(v_id);
    Graph::VertexList neighbours = LogicControl.neighboursOf(v_id);
    std::for_each(neighbours.begin(), neighbours.end(),
                  [&] (const Identity id) {
                      if (id != parent_id &&
                          node->statusOf(id) != NodeStatus::BLACK) {
                          findCycle(id, v_id, node);
                      }
                  });

    node->leave(v_id);
}
