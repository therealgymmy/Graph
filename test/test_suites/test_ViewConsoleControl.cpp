#include "../_include/test_ViewConsoleControl.h"

// Dependencies
#include "../_include/test_Log.h"

// Required By Test
#include "../../src/view/console/_include/ConsoleMain.h"

TestStatus ViewConsoleControl::run ()
{
    __enter;

    ConsoleMain main;
    main.start();

    __return(TestStatus::PASS);
}
