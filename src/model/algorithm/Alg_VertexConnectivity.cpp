#include "../_include/Alg_VertexConnectivity.h"

// Dependencies
#include <algorithm>
#include <utility>
#include "../_include/Graph.h"
#include "../_include/ModelTypes.h"

class PathFound {};

VertexConnectivity::VertexConnectivity (LogicController &logic)
: Algorithm(logic)
{
}

VertexConnectivity::Result
VertexConnectivity::run (const VertexConnectivity::Parameter& parm)
{
    // In the future, should use this to validate that
    // the two vertices are within the same graph.
    // If not, return false right away.
    Identity g_id = parm.findPath.graph_;

    Identity v1_id = parm.findPath.vertexPair_[0];
    Identity v2_id = parm.findPath.vertexPair_[1];
    Result result = { .hasPath_ = false };

    NodeStatus node;
    Graph::VertexList list = logic_.verticesOf(g_id);
    try {
        findPath(v1_id, v2_id, NULL_IDENTITY, &node);
    }
    catch (PathFound&) {
        result.hasPath_ = true;
    }

    return result;
}

void VertexConnectivity::findPath (const Identity v1_id,
                                   const Identity target_id,
                                   const Identity parent_id,
                                   NodeStatus *node)
{
    node->visit(v1_id);
    Graph::VertexList neighbours = logic_.neighboursOf(v1_id);
    std::for_each(neighbours.begin(), neighbours.end(),
                  [&] (const Identity id) {
                      if (id == target_id) {
                          throw PathFound();
                      }
                      if (id != parent_id &&
                          node->statusOf(id) != NodeStatus::BLACK) {
                          findPath(id, target_id, v1_id, node);
                      }
                  });

    node->leave(v1_id);
}
