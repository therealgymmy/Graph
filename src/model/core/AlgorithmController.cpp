#include "../_include/AlgorithmController.h"

// Dependencies
#include <algorithm>
#include <utility>

// Algorithms
#include "../_include/Alg_CycleDetect.h"

AlgorithmController AlgorithmController::instance_;

AlgorithmController::AlgorithmController (LogicController &logic)
: logic_(logic)
// Initialize all algorithms.
{
    alg_[AlgorithmType::CYCLE_DETECT] = new CycleDetect(logic);
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
