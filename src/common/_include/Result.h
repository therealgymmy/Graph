#ifndef RESULTS_H
#define RESULTS_H

// Dependencies
#include "Types.h"

class Result {
public:
    enum Type {
        BOOL,
        ID,
        ID_LIST,
    };

//--Constructor
    Result (Type type, bool isSuccess);

//--Accessor
    operator bool () const { return isSuccess_; }
    Identity id () const;   // may throw
    IdentityList idList () const;   // may throw

//--Mutator
    void setIsSuccess (const bool isSuccess) { isSuccess_ = isSuccess; }
    void setId (const Identity id); // may throw
    void setIdList (const IdentityList idList); // may throw

private:
    Type type_;
    bool isSuccess_;

    // Return Fields
    Identity id_;
    IdentityList idList_;

    void validate (Type type) const;
};

#endif//RESULTS_H
