#ifndef COMMAND_H
#define COMMAND_H

// Dependencies
#include <string>
#include <vector>
#include "../../common/_include/Types.h"

namespace cmd {

class Token {
public:
    enum Type {
        // Condition
        REPEAT,

        // Action
        CREATE,     REMOVE,
        JOIN,       DISJOIN,
        MERGE,      UNMERGE,
        HAS,

        // Resource
        GRAPH,
        VERTEX,
        CYCLE,
        PATH,

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

// A limited form of grammar is currently supported.
//
// <Statement> -> <ACTION> <RESOURCE> <MODIFIER> <SEMICOLON>
//
// <MODIFIER> -> <AT> <RESOURCE> <ID>
//            -> <ID> <AND> <ID>
//            -> <ID>
//            -> NULL
//
// <ACTION>   ->    <CREATE>
//            ->    <REMOVE>
//            ->    <JOIN>
//            ->    <DISJOIN>
//            ->    <MERGE>
//            ->    <UNMERGE>
//            ->    <HAS>
//
// <RESOURCE> ->    <GRAPH>
//            ->    <VERTEX>
//            ->    <CYCLE>
//
// This needs to be modified later.
struct Command {
    enum class Action { CREATE, REMOVE, JOIN, DISJOIN, MERGE, UNMERGE, HAS };
    enum class Resource { GRAPH, VERTEX, CYCLE, PATH };
    union {
        struct {
            Identity resource_;
        };
        Identity targetPair_[2];
        struct {
            Identity graph_;
            Identity vertexPair_[2];
        } findPath_;
    };
    Action   actionType_;
    Resource resourceType_;

    operator Action   () const { return actionType_; }
};

Command parse (std::vector<Token> list);

}

#endif//COMMAND_H
