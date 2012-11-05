#ifndef ALGORITHM_BASE_H
#define ALGORITHM_BASE_H

// All algorithms on graph theory inheirt from Algorithm class.
// This is a high level facility, direct access to resources is forbidden.
// Queries should always go to LogicController.

// Dependencies
#include "AlgorithmList.h"
#include "LogicController.h"
#include "ModelTypes.h"

class Algorithm {
public:
//--Constructor
    Algorithm (LogicController &logic = LogicControl) : logic_(logic) {}

//--Destructor
    virtual ~Algorithm () = default;

    union Parameter;
    union Result;

    virtual Result run (const Parameter& param) = 0;

protected:
    LogicController &logic_;
};

union Algorithm::Parameter {
    Identity id_;
};

union Algorithm::Result {
    bool hasCycle_;
};

#endif//ALGORITHM_BASE_H
