#include "../_include/Alg_SpanningTree.h"

// Dependencies
#include <algorithm>
#include <utility>
#include "../_include/Graph.h"

class SpanningTreeFound {};

SpanningTree::SpanningTree (LogicController &logic)
: Algorithm(logic)
{
}

SpanningTree::Result
SpanningTree::run (const SpanningTree::Parameter& parm)
{
    throw "Should not be here";
    return Result();
}

// Temporary approach!
// Once the common Result/Param facility is done,
// this code needs to be updated.
Tree
SpanningTree::findSpanningTree (Identity g_id)
{
    IdentityList list = logic_.verticesOf(g_id);
    NodeStatus node;
    Tree tree;
    try {
        findSpanningTree(*list.begin(), NULL_IDENTITY, &node, &tree);
    }
    catch (SpanningTreeFound&) {
        // Tree should be populated.
        return tree;
    }

    // Should not reach here.
    return Tree();
}

void
SpanningTree::findSpanningTree (Identity v_id,
                                Identity parent_id,
                                NodeStatus *node,
                                Tree *tree)
{
    if (node->statusOf(v_id) == NodeStatus::GREY) {
        // Reached a cycle.
        return;
    }

    node->visit(v_id);
    IdentityList neighbours = logic_.neighboursOf(v_id);
    std::for_each(neighbours.begin(), neighbours.end(),
                  [&] (const Identity id) {
                      if (id != parent_id &&
                          node->statusOf(id) != NodeStatus::BLACK) {
                      }
                  });

    node->leave(v_id);
}
