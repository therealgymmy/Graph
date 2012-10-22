#ifndef TEST_LOG_H
#define TEST_LOG_H

#include <sstream>

#if defined(__GCC__) || (__GNUC__) || (__MINGW32__)
 #define FUNC __PRETTY_FUNCTION__
#else
 #define FUNC __func__
#endif

#define __log_print TestLog().get()
#define __enter TestLog().get() << "<--Enter-->    " << FUNC
#define __return(parm) do {\
                       TestLog().get() << "<--Leave-->    " << FUNC;\
                       return (parm);\
                       } while (0)
#define __checkpoint(parm) do {\
                           TestLog().get() << "CheckPoint: " << (parm);\
                           } while (0)

class TestLog {
public:
    ~TestLog ();
    std::ostringstream& get ();
private:
    std::ostringstream os_;
};

#endif//TEST_LOG_H
