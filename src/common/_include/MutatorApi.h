#ifndef MUTATOR_API_H
#define MUTATOR_API_H

#include "Result.h"
#include "Types.h"

class MutatorApi {
public:
//--Resource Creation
    virtual Result newGraph () = 0;
    virtual Result newVertexAt (const Identity graph) = 0;

//--Resource Deletion
    virtual Result remGraph  (const Identity graph)  = 0;
    virtual Result remVertex (const Identity vertex) = 0;

//--Resource Management
    virtual Result join    (const Identity vertex1, const Identity vertex2) = 0;
    virtual Result disjoin (const Identity vertex1, const Identity vertex2) = 0;
};

#endif//MUTATOR_API_H
