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
    AlgorithmController (LogicController &logic);

//--Destructor
    ~AlgorithmController ();

//--Query Interface
    bool hasCycleAt (const Identity g_id);
    bool hasPathBetween (const Identity v1, const Identity v2,
                         const Identity g_id);
    Identity spanningTreeAt (const Identity g_id);

private:
    LogicController &logic_;
    std::map<AlgorithmType, Algorithm*> alg_;
};

#endif//ALGORITHM_CONTROLLER_H
