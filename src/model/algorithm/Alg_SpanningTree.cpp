#include "../_include/Alg_SpanningTree.h"

// Dependencies
#include <algorithm>
#include <utility>
#include "../_include/Graph.h"
#include "../_include/ModelTypes.h"

SpanningTree::SpanningTree (LogicController &logic)
: Algorithm(logic)
{
}

SpanningTree::Result
SpanningTree::run (const SpanningTree::Parameter& parm)
{
    Result result = { .hasPath_ = false };
    return result;
}
