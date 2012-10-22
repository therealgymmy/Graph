#include "_include/test_Base.h"
#include "_include/test_List.h"
#include "_include/test_Run.h"

#ifdef _DEBUG
int main ()
{
    initTest();
    runTest();
    cleanTest();
}
#endif
