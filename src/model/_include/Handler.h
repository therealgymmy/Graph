#ifndef HANDLER_H
#define HANDLER_H

// Dependencies
#include "ModelTypes.h"

enum class Object {
    EDGE,
    VERTEX,
};

class Handler {
public:
    static Handler& Instance() { return instance_; }

//--Mutator to Stack
    // Pre: If id is not unique, will return NULL.
    Vertex* newVertex (const Identity id);

    // Pre: If id is not unique, v1 or v2 doesn't exist, or v1 == v2,
    //       will return NULL.
    Edge* join (const Identity id, const Identity v1_id, const Identity v2_id);

    bool disjoin (const Identity v1_id, const Identity v2_id);

private:
    static Handler instance_;

//--Accessor
    Edge* commonEdge (const Vertex *v1, const Vertex *v2) const;
};

#define Handle Handler::Instance()

#endif//HANDLER_H
