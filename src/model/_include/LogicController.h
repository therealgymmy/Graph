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
#include <map>
#include "Graph.h"
#include "ModelTypes.h"

class LogicController {
public:
//--Constructor
    LogicController ();

//--Destructor
    ~LogicController ();

//--Accessor
    static LogicController& Instance () { return instance_; }

//--Mutator
    Identity newGraph ();   // may throw
    // Pre: g_id must be valid.
    Identity newVertex (const Identity g_id);   // may throw

    bool remGraph  (const Identity g_id);
    bool remVertex (const Identity v_id);

    // Vertices from different graphs cannot be joint.
    bool join    (const Identity v1_id, const Identity v2_id);
    bool disjoin (const Identity v1_id, const Identity v2_id);

private:
    static LogicController instance_;
    BaseController &base_;

    // register_
    //  - First Id  -> vertex
    //  - Second Id -> graph
    std::map<Identity, Identity> register_;
    std::map<Identity, Graph*> graphs_;
    Identity idCount_;      // Newest assigned ID + 1

    // Throw if idCount_ >= maximum allowed.
    Identity newIdentity ();     // may throw
};

#define LogicControl LogicController::Instance()

#endif//LOGIC_CONTROLLER_H