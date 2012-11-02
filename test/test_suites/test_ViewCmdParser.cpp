#include "../_include/test_ViewCmdParser.h"

// Dependencies
#include <string>
#include <vector>
#include "../_include/test_Log.h"

// Required By Test
#include "../../src/view/_include/Command.h"

TestStatus ViewCmdParser::run ()
{
    __enter;

    std::string command = "CREATE VERTEX AT @15";
    __checkpoint(command);
    std::vector<cmd::Token> list = cmd::tokenize(command);
    if (list[0].type() != cmd::Token::CREATE) {
        __log_print << "CREATE is not matched";
        __return_status(TestStatus::FAIL);
    }
    if (list[1].type() != cmd::Token::VERTEX) {
        __log_print << "VERTEX is not matched";
        __return_status(TestStatus::FAIL);
    }
    if (list[2].type() != cmd::Token::AT) {
        __log_print << "AT is not matched";
        __return_status(TestStatus::FAIL);
    }
    if (list[3].type() != cmd::Token::ID) {
        __log_print << "ID is not matched";
        __return_status(TestStatus::FAIL);
    }

    command = "JOIN VERTEX @1 AND @5";
    __checkpoint(command);
    list = cmd::tokenize(command);
    if (list[0].type() != cmd::Token::JOIN) {
        __log_print << "CREATE is not matched";
        __return_status(TestStatus::FAIL);
    }
    if (list[1].type() != cmd::Token::VERTEX) {
        __log_print << "VERTEX is not matched";
        __return_status(TestStatus::FAIL);
    }
    if (list[2].type() != cmd::Token::ID) {
        __log_print << "ID is not matched";
        __return_status(TestStatus::FAIL);
    }
    if (list[3].type() != cmd::Token::AND) {
        __log_print << "AND is not matched";
        __return_status(TestStatus::FAIL);
    }
    if (list[4].type() != cmd::Token::ID) {
        __log_print << "ID is not matched";
        __return_status(TestStatus::FAIL);
    }

    __return(TestStatus::PASS);
}
