#ifndef VERTEX_H
#define VERTEX_H

// Vertex
//  - can be joined with arbitrary number of vertices except itself.
//  - is joined with another vertex only when they point to each other.
//  - cannot join to itself.

// Dependencies
#include <map>
#include <set>
#include <string>
#include <vector>
#include "ModelTypes.h"

class Vertex {
public:
    typedef std::vector<Identity> NeighbourList;

//--Constructor
    Vertex (const Identity id);

//--Accessor
    Identity identity () const;
    bool hasVertex (const Identity id) const;
    bool hasEdge   (const Identity id) const;
    // Pre: If id is not in neighbours_, return NULL;
    Edge* commonEdge (const Identity id) const;

    NeighbourList getNeighbours () const;

//--Mutator
    bool removeVertex (const Identity id);

    // Pre: Variable e must point at valid address.
    bool addEdge (Edge *e);

private:
    Identity id_;
    // neighbours_ : key -> vertex_id
    //               val -> edge_id
    std::map<Identity, Identity> neighbours_;
    std::map<Identity, Edge*> e_;

//--Mutator
    bool removeEdge (const Identity id);
};

#endif//VERTEX_H
