#ifndef ACCESSOR_API_H
#define ACCESSOR_API_H

// Dependencies
#include "../../common/_include/Result.h"
#include "../../common/_include/Types.h"

class AccessorApi {
public:
//--Basic Query
    virtual Result hasGraph  (const Identity graph)  const = 0;
    virtual Result hasVertex (const Identity vertex) const = 0;
    virtual Result isJointBetween (const Identity vertex1,
                                   const Identity vertex2) const = 0;

    virtual Result graphOf      (const Identity vertex) const = 0;
    virtual Result neighboursOf (const Identity vertex) const = 0;
    virtual Result verticesOf   (const Identity graph)  const = 0;

    virtual Result allGraphs   () const = 0;
    virtual Result allVertices () const = 0;

//--Algorithm
    virtual Result hasCycleAt (const Identity graph) const = 0;

protected:
    AccessorApi () = default;
    virtual ~AccessorApi () = default;
};

#endif//ACCESSOR_API_H
