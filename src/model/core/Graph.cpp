#include "../_include/Graph.h"

// Dependencies
#include <algorithm>
#include "../_include/BaseController.h"

Graph::Graph (const Identity id)
: BaseObject (id)
// Do nothing.
{
}

Graph::~Graph ()
// Remove all vertices.
{
    std::for_each(vertices_.begin(), vertices_.end(),
                  [] (Identity v_id) {
                      BaseControl.removeVertex(v_id);
                  });
}

Graph::VertexList Graph::getVertices () const
{
    return vertices_;
}

bool Graph::addVertex (const Identity id)
// Return false if id already exists.
{
    if (vertices_.find(id) != vertices_.end()) {
        return false;
    }
    vertices_.insert(id);
    return true;
}

bool Graph::remVertex (const Identity id)
// Return false if id does not exist.
{
    if (vertices_.find(id) == vertices_.end()) {
        return false;
    }
    vertices_.erase(id);
    return true;
}
