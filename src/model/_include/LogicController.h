#ifndef LOGIC_CONTROLLER_H
#define LOGIC_CONTROLLER_H

// Interface for core logic of the model.
// Graphs and its associated vertices and edges are managed here.
// Also responsible for determining all sorts of graph theory relations.
//
// Note:
// This is NOT a *Controller* (as the C in MVC) type of facility.
// Although the interface here presents a relatively high abstraction of the
//  program logic, external requests from *Controller* should never come here.

// Dependencies
#include <set>
#include "ModelTypes.h"

class LogicController {
public:
//--Constructor
    LogicController ();

//--Mutator to underlying resources.
    bool join    (const Identity v1_id, const Identity v2_id);
    bool disjoin (const Identity v1_id, const Identity v2_id);

private:
    static LogicController instance_;
    BaseController &base_;

    std::set<Identity> id_;
    Identity idCount_;      // Newest assigned ID + 1
};

#endif//LOGIC_CONTROLLER_H
