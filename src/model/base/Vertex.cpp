#include "../_include/Vertex.h"

// Dependencies
#include <algorithm>
#include "../../common/_include/Exception.h"
#include "../_include/Edge.h"

Vertex::Vertex (Identity id)
: id_(id)
// Do nothing.
{
}

Identity Vertex::identity () const
{
    return id_;
}

bool Vertex::hasVertex (const Identity id) const
{
    if (neighbours_.find(id) == neighbours_.end()) {
        return false;
    }
    else {
        return true;
    }
}

bool Vertex::hasEdge (const Identity id) const
{
    if (e_.find(id) == e_.end()) {
        return false;
    }
    else {
        return true;
    }
}

Edge* Vertex::commonEdge (const Identity id) const
{
    auto it = neighbours_.find(id);
    if (it == neighbours_.end()) {
        return NULL;
    }
    else {
        return e_.find(it->second)->second;
    }
}

Vertex::NeighbourList Vertex::getNeighbours () const
{
    NeighbourList list;
    std::for_each(neighbours_.begin(), neighbours_.end(),
                  [&] (std::pair<Identity, Identity> it) {
                      list.push_back(it.first);
                  });
    return list;
}

bool Vertex::addEdge (Edge *e)
// Attempt to add an edge.
// If this edge already exists, return false.
// Otherwise, add edge and add the other vertex <-> edge pair.
{
    Identity e_id = e->identity();
    if (e_.find(e_id) != e_.end()) {
        return false;
    }

    e_[e_id] = e;
    Vertex *v_other = e->other(id_);
    neighbours_[v_other->identity()] = e_id;
    return true;
}

bool Vertex::removeVertex (const Identity id)
// Remove the neighbour vertex.
// If not joint, return false.
// Otherwise, remove.
{
    if (neighbours_.find(id) == neighbours_.end()) {
        return false;
    }

    Identity e_id = neighbours_[id];
    if (!removeEdge(e_id)) {
        return false;
    }

    neighbours_.erase(id);
    return true;
}

bool Vertex::removeEdge (const Identity id)
// Attempt to remove an edge.
// If is not joint with this, return false;
// Otherwise, remove it and then return true.
// Also, unref this vertex at the same time.
{
    if (e_.find(id) == e_.end()) {
        // Edge is not joint with this.
        return false;
    }

    e_.erase(id);
    return true;
}
