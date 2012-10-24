#ifndef GRAPH_H
#define GRAPH_H

// Graph
//  - Base class for all kinds of graphs.
//  - contains any number of vertices and edges.
//
// Note:
//      Graph's id does not have to be unique from vertices or edges.

// Dependencies
#include <set>
#include "BaseObject.h"
#include "ModelTypes.h"

class Graph : public BaseObject {
public:
    typedef std::set<Identity> VertexList;

//--Destructor
    virtual ~Graph ();

//--Accessor
    VertexList getVertices () const;

//--Mutator
    bool addVertex (const Identity id);
    bool remVertex (const Identity id);

protected:
//--Constructor
    Graph (const Identity id);

private:
    std::set<Identity> vertices_;
};

#endif//GRAPH_H
