#include "../_include/BaseController.h"

// Dependencies
#include <algorithm>
#include "../../common/_include/Exception.h"
#include "../_include/Edge.h"
#include "../_include/Resource.h"

BaseController BaseController::instance_;

Vertex::NeighbourList BaseController::getNeighbours (const Identity id)
// If id is not valid, Stack.getVertex will throw.
{
    return Stack.getVertex(id)->getNeighbours();
}

bool BaseController::isJoint (const Identity v1_id, const Identity v2_id)
// If id is not valid, Stack.getVertex will throw.
{
    Vertex *v1 = Stack.getVertex(v1_id);
    Vertex *v2 = Stack.getVertex(v2_id);
    return (v1->hasVertex(v2_id) & v2->hasVertex(v1_id));
}

Vertex* BaseController::newVertex (const Identity id)
// Create a new vertex with this id.
// Attempt to register it on Stack.
// If fail, return NULL.
{
    Vertex *v = new Vertex(id);
    try {
        Stack.reg(v);
    }
    catch (RuntimeExcept &err) {
        delete v;
        return NULL;
    }
    return v;
}

bool BaseController::removeVertex (const Identity id)
// Remvoe vertex with this id.
// If not exist, return null.
// If vertex is joint with other vertices,
//  remove common edges, and unref its neighbours.
// If id is not valid, Stack.getVertex will throw.
{
    Vertex *v = Stack.getVertex(id);
    Vertex::NeighbourList list = v->getNeighbours();
    std::for_each(list.begin(), list.end(),
                  [&] (const Identity otherId) {
                      disjoin(id, otherId);
                  });
    Stack.unref(v);
    return true;
}

Edge* BaseController::join (const Identity id, const Identity v1_id, const Identity v2_id)
// Attempt to ref v1 and v2 from Stack.
// Create a new edge with this id, connect it to v1 and v2.
// Then try to register it on Stack.
// If fail, return NULL.
// If id is not valid, Stack.getVertex will throw.
{
    if (v1_id == v2_id) {
        return NULL;
    }

    // May throw if id's are not valid.
    Vertex *v1 = Stack.getVertex(v1_id);
    Vertex *v2 = Stack.getVertex(v2_id);

    // If v1 & v2 are already joint, return NULL.
    if (v1->hasVertex(v2_id) || v2->hasVertex(v1_id)) {
        return NULL;
    }

    Edge *e = new Edge(id, v1, v2);
    try {
        Stack.reg(e);
    }
    catch (RuntimeExcept &err) {
        delete e;
        return NULL;
    }

    if (!v1->addEdge(e)) {
        delete e;
        return NULL;
    }
    if (!v2->addEdge(e)) {
        delete e;
        return NULL;
    }

    Stack.ref(v1);
    Stack.ref(v2);
    return e;
}

bool BaseController::disjoin (const Identity v1_id, const Identity v2_id)
// Attempt to disjoin v1 and v2.
// If v1 == v2, v1 or v2 does not exist, or not connected,
//  return false.
{
    if (v1_id == v2_id) {
        return false;
    }

    // May throw if id's are not valid.
    Vertex *v1 = Stack.getVertex(v1_id);
    Vertex *v2 = Stack.getVertex(v2_id);

    Edge *e = commonEdge(v1, v2);
    if (e == NULL) {
        return false;
    }

    if (!v1->removeVertex(v2_id)) {
        return false;
    }
    if (!v2->removeVertex(v1_id)) {
        return false;
    }

    Stack.unref(v1);
    Stack.unref(v2);
    Stack.unref(e);
    return true;
}

// Pre: v1 and v2 must point at valid addresses.
//      v1 and v2 must be connected.
Edge* BaseController::commonEdge (const Vertex *v1, const Vertex *v2) const
// Return common edge
{
    Edge *e1 = v1->commonEdge(v2->identity());
    Edge *e2 = v2->commonEdge(v1->identity());
    if (e1 != e2) {     // If e1 == e2 == NULL, then it's fine.
        throw RuntimeExcept();
    }

    return e1;
}
