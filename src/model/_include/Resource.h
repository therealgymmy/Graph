#ifndef RESOURCE_H
#define RESOURCE_H

// Dependencies
#include <cstdint>
#include <map>
#include <set>
#include <utility>
#include "ModelTypes.h"

class Storage {
public:
    typedef uint32_t RefCount;
    typedef std::pair<Edge*,   RefCount> EdgePair;
    typedef std::pair<Vertex*, RefCount> VertexPair;

    Storage () = default;
    Storage (Storage &rhs) = delete;

    Edge*   getEdge   (const Identity id);    // may throw
    Vertex* getVertex (const Identity id);    // may throw

    // Pre: every new object should have an unique id.
    void reg   (Edge   *e);   // may throw
    void reg   (Vertex *v);   // may throw
    void ref   (const Edge   *e);
    void ref   (const Vertex *v);
    void unref (const Edge   *e);
    void unref (const Vertex *v);
private:
    std::map<Identity, EdgePair>   eRef_;
    std::map<Identity, VertexPair> vRef_;
    std::set<Identity> id_;

    void unreg   (const Edge   *e);
    void unreg   (const Vertex *v);
};

#endif//RESOURCE_H
