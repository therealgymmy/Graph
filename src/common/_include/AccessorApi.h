#ifndef ACCESSOR_API_H
#define ACCESSOR_API_H

#include "Result.h"
#include "Types.h"

class AccessorApi {
public:
    virtual Result hasGraph  (const Identity graph)  const = 0;
    virtual Result hasVertex (const Identity vertex) const = 0;
    virtual Result isJointBetween (const Identity vertex1,
                                   const Identity vertex2) const = 0;
};

#endif//ACCESSOR_API_H
