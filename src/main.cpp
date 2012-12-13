#ifdef _RELEASE

#include "controller/_include/Controller.h"
#include "model/_include/AlgorithmController.h"
#include "model/_include/LogicController.h"
#include "view/console/_include/ConsoleMain.h"

int main ()
{
    std::cout << "Hi Jimmy" << std::endl;
    Storage stack;
    BaseController base(stack);
    LogicController logic(base);
    AlgorithmController alg(logic);

    Controller control(&logic, &alg);
    ConsoleMain console(&control);

    control.subscribe(&console);
    console.start();

    return 0;
}

#endif
