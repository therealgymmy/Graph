#ifndef BASE_OBJECT_H
#define BASE_OBJECT_H

// Base Object
//  - Identity

// Dependencies
#include "ModelTypes.h"

class BaseObject {
public:
//--Constructor
    BaseObject (const Identity id) : id_(id) {}

//--Accessor
    Identity identity () const { return id_; }

private:
    Identity id_;
};

#endif//BASE_OBJECT_H
