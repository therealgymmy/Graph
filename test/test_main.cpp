#include "test_def.h"

#include <iostream>
#include "../src/model/_include/BaseController.h"
#include "../src/model/_include/Edge.h"
#include "../src/model/_include/Resource.h"
#include "../src/model/_include/Vertex.h"

int main ()
{
    Vertex *v1 = BaseControl.newVertex(1);
    Vertex *v2 = BaseControl.newVertex(2);
    Vertex *v3 = BaseControl.newVertex(3);
    Edge *e = BaseControl.join(1, 1, 2);
    Edge *e1 = BaseControl.join(2, 1, 3);
    Edge *e2 = BaseControl.join(3, 2, 3);
    if (e == NULL) {
        std::cout << "no edge" << std::endl;
    }
    if (!BaseControl.disjoin(1, 2)) {
        std::cout << "no disjoin" << std::endl;
    }
    BaseControl.disjoin(1, 2);
    BaseControl.disjoin(1, 3);
    BaseControl.disjoin(2, 3);

    Stack.unref(v1);
    Stack.unref(v2);
    Stack.unref(v3);
    return 0;
}
