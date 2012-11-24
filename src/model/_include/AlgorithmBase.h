#ifndef ALGORITHM_BASE_H
#define ALGORITHM_BASE_H

// All algorithms on graph theory inheirt from Algorithm class.
// This is a high level facility, direct access to resources is forbidden.
// Queries should always go to LogicController.

// Dependencies
#include <map>
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
    struct {
        Identity graph_;
        Identity vertexPair_[2];
    } findPath;
};

union Algorithm::Result {
    bool hasCycle_;
    bool hasPath_;
};

class NodeStatus {
public:
    enum Color {
        WHITE,      // not yet visited
        GREY,       // being visited
        BLACK,      // done visited
    };

    void visit (const Identity id);
    void leave (const Identity id);
    Color statusOf (const Identity id) const;

private:
    std::map<Identity, Color> status_;
};

#endif//ALGORITHM_BASE_H
