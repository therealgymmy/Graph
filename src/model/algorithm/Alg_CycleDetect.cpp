#include "../_include/Alg_CycleDetect.h"

// Dependencies
#include <algorithm>
#include <utility>
#include "../_include/Graph.h"
#include "../_include/ModelTypes.h"

class CycleFound {};

CycleDetect::CycleDetect (LogicController &logic)
: Algorithm(logic)
{
}

CycleDetect::Result CycleDetect::run (const CycleDetect::Parameter& parm)
{
    Identity g_id = parm.id_;
    Result result = { .hasCycle_ = false };

    NodeStatus node;
    Graph::VertexList list = logic_.verticesOf(g_id);
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
    Graph::VertexList neighbours = logic_.neighboursOf(v_id);
    std::for_each(neighbours.begin(), neighbours.end(),
                  [&] (const Identity id) {
                      if (id != parent_id &&
                          node->statusOf(id) != NodeStatus::BLACK) {
                          findCycle(id, v_id, node);
                      }
                  });

    node->leave(v_id);
}
