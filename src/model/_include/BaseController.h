#ifndef BASE_CONTROLLER_H
#define BASE_CONTROLLER_H

// Dependencies
#include "ModelTypes.h"

class BaseController {
public:
    static BaseController& Instance() { return instance_; }

//--Mutator to Stack
    // Pre: If id is not unique, will return NULL.
    Vertex* newVertex (const Identity id);

    // Pre: id must be valid.
    bool removeVertex (const Identity id);

    // Pre: If id is not unique, v1 or v2 doesn't exist, or v1 == v2,
    //       will return NULL.
    //      id must be valid.
    Edge* join (const Identity id, const Identity v1_id, const Identity v2_id);

    // Pre: id must be valid, and v1 != v2.
    bool disjoin (const Identity v1_id, const Identity v2_id);

private:
    static BaseController instance_;

//--Accessor
    Edge* commonEdge (const Vertex *v1, const Vertex *v2) const;
};

#define BaseControl BaseController::Instance()

#endif//BASE_CONTROLLER_H
