#include "../_include/Command.h"

// Dependencies
#include <array>
#include <cstdint>
#include "../_include/DeltaInitMacro.h"

#define WHITESPACE      "\t\n\r"
#define LETTER          "ABCDEFGHIJKLMNOPQRSTUVWXYZ" \
                        "abcdefghijklmnopqrstuvwxyz"
#define DIGIT           "0123456789"
#define REGISTER        '@'
#define COMMENT         '#'

#define MAKE_IS(func) constexpr bool is##func (char ARG)
#define IS(func, ARG) is##func(ARG)
#define ARG c

#define INIT(S, N) INIT_##N(S)
#define INITIALIZE(S) {INIT(S, 0)}

namespace cmd {

enum State {
    ST_NUL,         // NULL State
    ST_START,       // START State

    ST_ID,          // Numbers that prefixed by REGISTER
    ST_NUMBER,      // Numbers

    ST_KEYWORD,     // Keyword - temporary state during tokenization

    ST_LBRACE,      // {
    ST_RBRACE,      // }
    ST_COLON,       // :
    ST_SEMICOLON,   // ;

    ST_COMMENT,     // COMMENT
    ST_WHITESPACE,  // WHITESPACE
};

typedef const std::array<std::array<State, 256>, ST_WHITESPACE + 1> Delta;

inline MAKE_IS (whitespace)
{
    return (ARG == '\t' || ARG == '\n' || ARG == '\r');
}

inline MAKE_IS (letter)     // A==0x41, Z==0x5A, a==0x61, z==0x7A
{
    return ((ARG >= 0x41 && ARG <= 0x5A) ||
            (ARG >= 0x61 && ARG <= 0x7A));
}

inline MAKE_IS (number)    // 0==0x30, 9==0x39
{
    return (ARG >= 0x30 && ARG <= 0x39);
}

constexpr State next (State from, char c)
{
    return from == ST_START      && IS(whitespace, c) ? ST_WHITESPACE :
           from == ST_WHITESPACE && IS(whitespace, c) ? ST_WHITESPACE :
           from == ST_START      && IS(letter,     c) ? ST_KEYWORD:
           from == ST_KEYWORD    && IS(letter,     c) ? ST_KEYWORD:
           from == ST_START      && IS(number,     c) ? ST_NUMBER:
           from == ST_NUMBER     && IS(number,     c) ? ST_NUMBER:
           from == ST_START      && (c == REGISTER)   ? ST_ID:
           from == ST_ID         && IS(number,     c) ? ST_ID:
           from == ST_START      && (c == '{')        ? ST_LBRACE:
           from == ST_START      && (c == '}')        ? ST_RBRACE:
           from == ST_START      && (c == ':')        ? ST_COLON:
           from == ST_START      && (c == ';')        ? ST_SEMICOLON:
           from == ST_START      && (c == COMMENT)    ? ST_COMMENT:
           ST_NUL;
}

/*
constexpr State* init (State *states, State from, int n = 255)
{
    return n >= 0 ? (states[n] = next(from, n), init(states, from, --n)) :
           states;
}
*/

constexpr State delta[ST_WHITESPACE + 1][256] = { INITIALIZE(ST_NUL),
                                                  INITIALIZE(ST_START),
                                                  INITIALIZE(ST_ID),
                                                  INITIALIZE(ST_NUMBER),
                                                  INITIALIZE(ST_KEYWORD),
                                                  INITIALIZE(ST_LBRACE),
                                                  INITIALIZE(ST_RBRACE),
                                                  INITIALIZE(ST_COLON),
                                                  INITIALIZE(ST_SEMICOLON),
                                                  INITIALIZE(ST_COMMENT),
                                                  INITIALIZE(ST_WHITESPACE) };

}
