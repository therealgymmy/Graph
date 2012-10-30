#include "../_include/Result.h"
#include "../_include/Exception.h"

Result::Result (Type type, bool isSuccess)
: type_(type), isSuccess_(isSuccess)
// Do nothing
{
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
