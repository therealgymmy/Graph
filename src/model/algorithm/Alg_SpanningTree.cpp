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
    Identity g_id = parm.id_;
    Result result = { .id_ = NULL_IDENTITY };

    Identity tree = logic_.newGraph();

    try {
        findSpanningTree(g_id, tree);
    }
    catch (SpanningTreeFound&) {
        result.id_ = tree;
    }

    return result;
}

// Temporary approach!
// Once the common Result/Param facility is done,
// this code needs to be updated.
void
SpanningTree::findSpanningTree (Identity g_id, Identity tree)
{
}
