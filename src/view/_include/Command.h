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
#include <set>
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
    Token (Type type, std::string lexeme);

//--Comparison Operator
    bool operator== (Token &rhs);

//--Accessor
    Type        type   () const;
    std::string lexeme () const;

//--Mutator
    void tokenize ();

private:
    Type type_;
    std::string lexeme_;
};

std::set<Token> tokenize(std::string input);

}

#endif//COMMAND_H
