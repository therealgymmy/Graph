#ifndef EDGE_H
#define EDGE_H

// Edge
//  - joins two vertices together.
//  - cannot join the same vertex with itself.

// Dependencies
#include <utility>
#include <string>
#include "ModelTypes.h"

class Edge {
public:
//--Constructor
    Edge (const Identity id, Vertex *v1, Vertex *v2) noexcept;

//--Accessor
    Identity identity () const;
    Vertex* left  () const;
    Vertex* right () const;
    // Pre: If id is not either one of this's vertices, will throw.
    Vertex* other (const Identity id) const;     // may throw

private:
    Identity id_;
    std::pair<Vertex*, Vertex*> pair_;
};

#endif//EDGE_H
