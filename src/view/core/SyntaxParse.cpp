#include "../_include/Command.h"

// Dependencies
#include <cstdlib>
#include "../../common/_include/Exception.h"

namespace cmd {

// Temporary parse, need rework in the future.
Command parse (std::vector<Token> list)
try
{
    Command command;
    switch (list.at(0).type()) {
        case Token::CREATE:
            command.actionType_ = Command::Action::CREATE;
            break;
        case Token::REMOVE:
            command.actionType_ = Command::Action::REMOVE;
            break;
        case Token::JOIN:
            command.actionType_ = Command::Action::JOIN;
            break;
        case Token::DISJOIN:
            command.actionType_ = Command::Action::DISJOIN;
            break;
        case Token::MERGE:
            command.actionType_ = Command::Action::MERGE;
            break;
        case Token::UNMERGE:
            command.actionType_ = Command::Action::UNMERGE;
            break;
        case Token::HAS:
            command.actionType_ = Command::Action::HAS;
            break;
        default:
            throw LogicExcept();
    }

    switch (command) {
        default:
            throw LogicExcept();
        case Command::Action::CREATE:
            if (list.at(1).type() == Token::GRAPH &&
                list.at(2).type() == Token::SEMICOLON) {
                command.resourceType_ = Command::Resource::GRAPH;
                return command;
            }
            if (list.at(1).type() == Token::VERTEX &&
                list.at(2).type() == Token::AT &&
                list.at(3).type() == Token::GRAPH &&
                list.at(5).type() == Token::SEMICOLON) {
                command.resourceType_ = Command::Resource::VERTEX;
                command.resource_ = std::atoi(list.at(4).lexeme()
                                                  .substr(1, list.at(4)
                                                  .lexeme().length())
                                                  .c_str());
                return command;
            }
            throw LogicExcept();
        case Command::Action::REMOVE:
            if (list.at(1).type() == Token::GRAPH &&
                list.at(3).type() == Token::SEMICOLON) {
                command.resourceType_ = Command::Resource::VERTEX;
                command.resource_ = std::atoi(list.at(2).lexeme()
                                                  .substr(1, list.at(2)
                                                  .lexeme().length())
                                                  .c_str());
                return command;
                break;
            }
            if (list.at(1).type() == Token::VERTEX &&
                list.at(3).type() == Token::SEMICOLON) {
                command.resourceType_ = Command::Resource::VERTEX;
                break;
            }
            throw LogicExcept();
        case Command::Action::HAS:
            if (list.at(1).type() == Token::CYCLE) {
                command.resourceType_ = Command::Resource::CYCLE;
                break;
            }
            throw LogicExcept();

        case Command::Action::JOIN:
        case Command::Action::DISJOIN:
            if (list.at(2).type() == Token::VERTEX &&
                list.at(4).type() == Token::AND &&
                list.at(6).type() == Token::SEMICOLON) {
                command.targetPair_[0] = std::atoi(list.at(3).lexeme()
                                                       .substr(1, list.at(3)
                                                       .lexeme().length())
                                                       .c_str());
                command.targetPair_[1] = std::atoi(list.at(5).lexeme()
                                                       .substr(1, list.at(5)
                                                       .lexeme().length())
                                                       .c_str());
                return command;
            }
            throw LogicExcept();
    }
}
catch (...) {
    throw LogicExcept();
}

}
