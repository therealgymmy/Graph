#ifdef _DEBUG

// Dependencies
#include <ctime>
#include "_include/test_Base.h"
#include "_include/test_List.h"
#include "_include/test_Log.h"
#include "_include/test_Run.h"

static void curTime ();

int main ()
{
    curTime();
    initTest();
    runTest();
    cleanTest();
    curTime();
    __log_print << "\n";
}

void curTime ()
{
    std::time_t t = time(0);
    std::tm *now = localtime(&t);
    __log_print << "<--Current Time-->            "
                << (now->tm_year + 1900) << '-'
                << (now->tm_mon + 1)     << '-'
                << (now->tm_mday)        << "    "
                << (now->tm_hour)        << ':'
                << (now->tm_min)         << ':'
                << (now->tm_sec);
}

#endif
