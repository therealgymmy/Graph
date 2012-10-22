#include "../_include/test_Log.h"

// Dependencies
#include <fstream>

TestLog::~TestLog ()
{
    os_ << std::endl;
    std::fprintf(stderr, "%s", os_.str().c_str());
    std::fflush(stderr);

    std::ofstream logfile("test_results.log",
                          std::ios::out | std::ios::app | std::ios::binary);
    if (logfile.is_open()) {
        logfile << os_.str();
        logfile.close();
    }
}

std::ostringstream& TestLog::get ()
{
    os_ << "--TEST--    ";
    return os_;
}
