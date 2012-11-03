#include "../_include/Result.h"
#include "../_include/Exception.h"

Result::Result (Type type, bool isSuccess)
: type_(type), isSuccess_(isSuccess),
  idList_() // Special handling for non-trvial union member idList_.
// Do nothing
{
}

Result::Result (const Result &rhs)
: type_(rhs.type_), isSuccess_(rhs.isSuccess_)
// Required for special handling of non-trivial union member idList_.
{
    switch (type_) {
        case BOOL:
            // Do nothing
            break;
        case ID:
            id_ = rhs.id_;
            break;
        case ID_LIST:
            idList_ = rhs.idList_;
            break;
    }
}

inline
void Result::validate (Result::Type type) const
{
    if (type_ != type) {
        throw LogicExcept();
    }
}

Identity Result::id () const
{
    validate(ID);
    return id_;
}

void Result::setId (const Identity id)
{
    validate(ID);
    id_ = id;
}

IdentityList Result::idList () const
{
    validate(ID_LIST);
    return idList_;
}

void Result::setIdList (const IdentityList idList)
{
    validate(ID_LIST);
    idList_ = idList;
}
