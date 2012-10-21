#include "../_include/Edge.h"

// Dependencies
#include "../../common/_include/Exception.h"
#include "../_include/Vertex.h"

Edge::Edge (const Identity id, Vertex *v1, Vertex *v2)
: id_(id), pair_(v1, v2)
// Do nothing.
{
}

Identity Edge::identity () const
{
    return id_;
}

Vertex* Edge::left () const
{
    return pair_.first;
}

Vertex* Edge::right () const
{
    return pair_.second;
}

Vertex* Edge::other (Identity id) const
// Return the other vertex.
{
    if (pair_.first->identity() == id) {
        return pair_.second;
    }
    else if (pair_.second->identity() == id) {
        return pair_.first;
    }
    else {
        throw RuntimeExcept();
    }
}
