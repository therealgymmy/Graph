#include "../_include/Resource.h"

// Dependencies
#include "../../common/_include/Exception.h"
#include "../_include/Edge.h"
#include "../_include/Vertex.h"

#define REG_DEFAULT_VAL 1

Storage Storage::instance_;

Edge* Storage::getEdge (const Identity id)
{
    auto it = eRef_.find(id);
    if (it == eRef_.end()) {
        throw RuntimeExcept();
    }
    return it->second.first;
}

Vertex* Storage::getVertex (const Identity id)
{
    auto it = vRef_.find(id);
    if (it == vRef_.end()) {
        throw RuntimeExcept();
    }
    return it->second.first;
}

void Storage::reg (Edge *e)
// Register this edge with the storage.
// If the edge already exists in the storage, throw.
{
    Identity id = e->identity();
    if (eRef_.find(id) != eRef_.end()) {
        throw RuntimeExcept();
    }
    if (id_.find(id) != id_.end()) {
        throw RuntimeExcept();
    }

    // Register id.
    eRef_[id] = std::make_pair(e, REG_DEFAULT_VAL);
    id_.insert(id);
}

void Storage::reg (Vertex *v)
// Register this vertex with the storage.
// If the vertex already exists in the storage, throw.
{
    Identity id = v->identity();
    if (vRef_.find(id) != vRef_.end()) {
        throw RuntimeExcept();
    }
    if (id_.find(id) != id_.end()) {
        throw RuntimeExcept();
    }

    // Register id.
    vRef_[id] = std::make_pair(v, REG_DEFAULT_VAL);
    id_.insert(id);
}

void Storage::ref (const Edge *e)
// Increase the reference count for this edge.
{
    Identity id = e->identity();
    ++eRef_[id].second;
}

void Storage::ref (const Vertex *v)
// Increase the reference count for this vertex.
{
    Identity id = v->identity();
    ++vRef_[id].second;
}

void Storage::unref (const Edge *e)
// Decrease the reference count for this edge.
// If ref count is 0, call unref() on this edge's two vertices
//  and then unregister this edge.
{
    Identity id = e->identity();
    if (--eRef_[id].second == 0) {
        unreg(e);
    }
}

void Storage::unref (const Vertex *v)
// Decrease the reference count for this vertex.
// If ref count is 0, call unref() to unregister this vertex.
{
    Identity id = v->identity();
    if (--vRef_[id].second == 0) {
        unreg(v);
    }
}

void Storage::unreg (const Edge *e)
// Unregister this edge -> delete it.
{
    Identity id = e->identity();
    Edge *e_del = eRef_.find(id)->second.first;

    eRef_.erase(id);
    id_.erase(id);

    delete e_del;
}

void Storage::unreg (const Vertex *v)
// Unregister this vertex -> delete it.
{
    Identity id = v->identity();
    Vertex *v_del = vRef_.find(id)->second.first;

    vRef_.erase(id);
    id_.erase(id);

    delete v_del;
}
