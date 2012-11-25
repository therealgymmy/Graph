#include "../_include/AlgorithmController.h"

// Dependencies
#include <algorithm>
#include <utility>

// Algorithms
#include "../_include/Alg_CycleDetect.h"
#include "../_include/Alg_VertexConnectivity.h"

AlgorithmController::AlgorithmController (LogicController &logic)
: logic_(logic)
// Initialize all algorithms.
{
    alg_[AlgorithmType::CYCLE_DETECT] = new CycleDetect(logic);
    alg_[AlgorithmType::FIND_PATH]    = new VertexConnectivity(logic);
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

