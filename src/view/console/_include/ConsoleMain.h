#ifndef CONSOLE_MAIN_H
#define CONSOLE_MAIN_H

// Dependencies
#include <map>
#include <sstream>
#include "../../../common/_include/Types.h"
#include "../../../common/_include/Observer.h"
#include "../../../controller/_include/Controller.h"

class ConsoleMain : public Observer {
public:
//--Constructor
    ConsoleMain (Controller *control);

//--Destructor
    ~ConsoleMain () noexcept {};

    void start ();

    virtual void update ();

private:
    enum Status {
        ERROR,
        SUCCESS,
        PENDING,
        EXIT,
    };

    struct Command {
        enum {
            // ERROR
            ERROR,

            // VIEW CONTROL
            EXIT,
            INFO,
            HELP,

            // Access
            HAS_GRAPH,
            HAS_VERTEX,
            IS_JOINT_BETWEEN,
            GRAPH_OF,
            NEIGHBOURS_OF,
            VERTICES_OF,
            ALL_GRAPHS,
            ALL_VERTICES,
            HAS_CYCLE_AT,

            // Mutate
            NEW_GRAPH,
            NEW_VERTEX_AT,
            REM_GRAPH,
            REM_VERTEX,
            JOIN,
            DISJOIN,
        } type_;

        union {
            Identity id_;
            Identity idPair_[2];
        };
    };

    Controller *control_;
    std::stringstream display_;
    std::map<Identity, IdentityList> graphs_;

    void hint ();
    Command interaction ();
    Status Process (const Command *cmd);
    void render ();
    void refresh ();
};

#endif//CONSOLE_MAIN_H
