#ifndef COMMAND_H
#define COMMAND_H

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
