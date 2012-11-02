#ifndef COMMAND_H
#define COMMAND_H

// A query is of the following format.
//
// <QUERY>     -> <CONDITION> <LBRACE> <OPERATION> <RBRACE>
//
// <CONDITION> -> <REPEAT> <COLON> <NUMBER>
//
// <OPERATION> -> <OPERATION> <STATEMENT>
//
// <STATEMENT> -> <ACTION> <RESOURCE> <MODIFIER> <SEMICOLON>
//
// <MODIFIER>  -> <AT> <RESOURCE> <ID>
//             -> <TARGET>
//
// <TARGET>    -> <TARGET> <AND> <ID>
//             -> <ID>
//
// Example:
//  1)  join vertex @15 and @20;
//
//  2)  repeat : 5 {
//          create vertex at graph @1 and @7;
//      }
//
//  3)  merge graph @7 and @38;
//
//  4)  remove vertex @11 and @12 and @13 and @14 and @15;

// Dependencies
#include <vector>
#include <string>

namespace cmd {

class Token {
public:
    enum Type {
        /*
        QUERY,
        CONDITION,
        OPERATION,
        STATEMENT,

        ACTION,
        RESOURCE,
        MODIFIER,

        TARGET,
        */

        // Condition
        REPEAT,

        // Action
        CREATE,     REMOVE,
        JOIN,       DISJOIN,
        MERGE,      UNMERGE,

        // Resource
        GRAPH,
        VERTEX,

        ID,         // A number prefixed by '@' - i.e. @123
        NUMBER,
        AT,
        AND,
        COLON,
        SEMICOLON,
        LBRACE,
        RBRACE,
    };

//--Constructor
    Token (Type type, std::string lexeme) : type_(type), lexeme_(lexeme) {}
    Token (const Token &rhs) : type_(rhs.type()), lexeme_(rhs.lexeme()) {}

//--Comparison Operator
    bool operator== (const Token &rhs) {
        return (type_ == rhs.type_ && lexeme_ == rhs.lexeme_);
    }

//--Accessor
    Type        type   () const { return type_; }
    std::string lexeme () const { return lexeme_; }

private:
    Type type_;
    std::string lexeme_;
};

std::vector<Token> tokenize(const std::string &input);

}

#endif//COMMAND_H
