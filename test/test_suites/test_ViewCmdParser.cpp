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

    command = "REPEAT : 5 {\n"
              "    CREATE VERTEX AT GRAPH @1 AND @2;\n"
              "}\n";
    __checkpoint(command);
    list = cmd::tokenize(command);
    if (list[0].type() != cmd::Token::REPEAT) {
        __log_print << "REPEAT is not matched";
        __return_status(TestStatus::FAIL);
    }
    if (list[1].type() != cmd::Token::COLON) {
        __log_print << "COLON is not matched";
        __return_status(TestStatus::FAIL);
    }
    if (list[2].type() != cmd::Token::NUMBER) {
        __log_print << "NUMBER is not matched";
        __return_status(TestStatus::FAIL);
    }
    if (list[3].type() != cmd::Token::LBRACE) {
        __log_print << "LBRACE is not matched";
        __return_status(TestStatus::FAIL);
    }
    if (list[4].type() != cmd::Token::CREATE) {
        __log_print << "CREATE is not matched";
        __return_status(TestStatus::FAIL);
    }
    if (list[5].type() != cmd::Token::VERTEX) {
        __log_print << "VERTEX is not matched";
        __return_status(TestStatus::FAIL);
    }
    if (list[6].type() != cmd::Token::AT) {
        __log_print << "AT is not matched";
        __return_status(TestStatus::FAIL);
    }
    if (list[7].type() != cmd::Token::GRAPH) {
        __log_print << "GRAPH is not matched";
        __return_status(TestStatus::FAIL);
    }
    if (list[8].type() != cmd::Token::ID) {
        __log_print << "ID is not matched";
        __return_status(TestStatus::FAIL);
    }
    if (list[9].type() != cmd::Token::AND) {
        __log_print << "AND is not matched";
        __return_status(TestStatus::FAIL);
    }
    if (list[10].type() != cmd::Token::ID) {
        __log_print << "ID is not matched";
        __return_status(TestStatus::FAIL);
    }
    if (list[11].type() != cmd::Token::SEMICOLON) {
        __log_print << "SEMICOLON is not matched";
        __return_status(TestStatus::FAIL);
    }
    if (list[12].type() != cmd::Token::RBRACE) {
        __log_print << "RBRACE is not matched";
        __return_status(TestStatus::FAIL);
    }

    __return(TestStatus::PASS);
}
