#ifndef ALGORITHM_CONTROLLER_H
#define ALGORITHM_CONTROLLER_H

// Interface for all operations involve algorithms.

// Dependencies
#include <map>
#include "AlgorithmList.h"
#include "AlgorithmBase.h"
#include "LogicController.h"
#include "ModelTypes.h"

class AlgorithmController {
public:
//--Constructor
    AlgorithmController (LogicController &logic = LogicControl);

//--Destructor
    ~AlgorithmController ();

//--Static Accessor
    static AlgorithmController& Instance () { return instance_; }

//--Query Interface
    bool hasCycleAt (const Identity g_id);

private:
    static AlgorithmController instance_;
    LogicController &logic_;
    std::map<AlgorithmType, Algorithm*> alg_;
};

#define AlgorithmControl AlgorithmController::Instance()

#endif//ALGORITHM_CONTROLLER_H
