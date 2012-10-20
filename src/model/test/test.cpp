#include <iostream>
#include "../_include/Edge.h"
#include "../_include/Handler.h"
#include "../_include/Resource.h"
#include "../_include/Vertex.h"

int main ()
{
    Vertex *v1 = Handle.newVertex(1);
    Vertex *v2 = Handle.newVertex(2);
    Edge *e = Handle.join(1, 1, 2);
    if (e == NULL) {
        std::cout << "no edge" << std::endl;
    }
    if (!Handle.disjoin(1, 2)) {
        std::cout << "no disjoin" << std::endl;
    }

    Stack.unref(v1);
    Stack.unref(v2);
    return 0;
}
