#include "../_include/AlgorithmController.h"

// Dependencies
#include <algorithm>
#include <utility>

// Algorithms
#include "../_include/Alg_CycleDetect.h"
#include "../_include/Alg_VertexConnectivity.h"
#include "../_include/Alg_SpanningTree.h"


AlgorithmController::AlgorithmController (LogicController &logic)
: logic_(logic)
// Initialize all algorithms.
{
#define Init(TYPE, ALG) alg_[AlgorithmType::TYPE] = new ALG(logic)
    Init( CYCLE_DETECT,  CycleDetect        );
    Init( FIND_PATH,     VertexConnectivity );
    Init( SPANNING_TREE, SpanningTree       );
#undef Init
}

AlgorithmController::~AlgorithmController ()
// Delete all algorithms.
{
    std::for_each(alg_.begin(), alg_.end(),
                  [] (std::pair<AlgorithmType, Algorithm*> it) {
                      delete it.second;
                  });
}

bool AlgorithmController::hasCycleAt (const Identity g_id)
{
    Algorithm::Parameter param = { .id_ = g_id };
    Algorithm::Result result = alg_[AlgorithmType::CYCLE_DETECT]->run(param);
    return result.hasCycle_;
}

bool AlgorithmController::hasPathBetween (const Identity v1,
                                          const Identity v2,
                                          const Identity g_id)
{
    Algorithm::Parameter param = { .findPath = { .graph_ = g_id,
                                                 .vertexPair_ = { v1, v2 } } };
    Algorithm::Result result = alg_[AlgorithmType::FIND_PATH]->run(param);
    return result.hasPath_;
}

