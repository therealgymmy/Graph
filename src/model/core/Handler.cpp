#include "../_include/Handler.h"

// Dependencies
#include "../../common/_include/Exception.h"
#include "../_include/Edge.h"
#include "../_include/Resource.h"
#include "../_include/Vertex.h"

Handler Handler::instance_;

Vertex* Handler::newVertex (const Identity id)
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

Edge* Handler::join (const Identity id, const Identity v1_id, const Identity v2_id)
// Attempt to ref v1 and v2 from Stack.
// Create a new edge with this id, connect it to v1 and v2.
// Then try to register it on Stack.
// If fail, return NULL.
{
    if (v1_id == v2_id) {
        return NULL;
    }

    // May throw if id's are not valid.
    Vertex *v1 = Stack.getVertex(v1_id);
    Vertex *v2 = Stack.getVertex(v2_id);

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

bool Handler::disjoin (const Identity v1_id, const Identity v2_id)
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
Edge* Handler::commonEdge (const Vertex *v1, const Vertex *v2) const
// Return common edge
{
    Edge *e1 = v1->commonEdge(v2->identity());
    Edge *e2 = v2->commonEdge(v1->identity());
    if (e1 != e2) {
        throw RuntimeExcept();
    }

    return e1;
}
