#include "../_include/ConsoleMain.h"

// Dependencies
#include <algorithm>
#include <string>
#include <utility>
#include "../_include/InputOutput.h"
#include "../../_include/Command.h"
#include "../../../common/_include/Exception.h"

ConsoleMain::ConsoleMain (Controller *control)
: control_(control)
{
}

void ConsoleMain::start ()
{
    Status status;
    hint();
    while (1) {
        Command cmd = interaction();
        Print("test\n");
        if ((status = Process(&cmd)) == EXIT) {
            return;
        }
        Print("test\n");
        switch (status) {
            case PENDING:
                render();
                refresh();
                status = SUCCESS;
                break;
            case ERROR:
                Print("Error in Operation!\n");
                break;
            default:
                break;
        }
    }
}

void ConsoleMain::update ()
{
    graphs_.clear();
    Result graphsResult = control_->allGraphs();
    if (graphsResult) {
        IdentityList graphs = graphsResult.idList();
        std::for_each(graphs.begin(), graphs.end(),
                      [&] (Identity g) {
                          Result verticesResult = control_->verticesOf(g);
                          IdentityList vertices = verticesResult.idList();
                          graphs_[g] = vertices;
                      });
    }
}

void ConsoleMain::hint ()
{
    display_.clear();
    display_.str(std::string());
    display_ << "Commands Available: \n"
             << "    EXIT\n"
             << "    INFO\n"
             << "    HELP\n"
             << "    CREATE GRAPH\n"
             << "    CREATE VERTEX AT <Graph ID>\n"
             << "    JOIN VERTEX <Vertex1 ID> AND <Vertex2 ID>\n"
             << "    DISJOIN VERTEX <Vertex1 ID> AND <Vertex2 ID>\n";
    refresh();
}

ConsoleMain::Command ConsoleMain::interaction ()
{
    Print("Enter Command: ");
    std::string input;

    /*
    std::getline(std::cin, input);
    if (input == "EXIT") {
        return Command{ .type_ = Command::EXIT, {0} };
    }
    else if (input == "INFO") {
        return Command{ .type_ = Command::INFO, {0} };
    }
    else if (input == "HELP") {
        return Command{ .type_ = Command::HELP, {0} };
    }
    try {
        cmd::Command command = cmd::parse(cmd::tokenize(input));
        if (command == cmd::Command::Action::CREATE) {
            Print("matched 1: ");
            if (command.resourceType_ == cmd::Command::Resource::GRAPH) {
                Print("matched 2: ");
                return Command{ .type_ = Command::NEW_GRAPH, {0} };
            }
            else if (command.resourceType_ == cmd::Command::Resource::VERTEX) {
                Command com = { .type_ = Command::NEW_VERTEX_AT, {0} };
                com.id_ = command.resource_;
                return com;
            }
        }
        if (command == cmd::Command::Action::JOIN) {
            Command com{ .type_ = Command::JOIN, {0} };
            com.idPair_[0] = command.targetPair_[0];
            com.idPair_[1] = command.targetPair_[1];
            return com;
        }
        if (command == cmd::Command::Action::DISJOIN) {
            Command com{ .type_ = Command::DISJOIN, {0} };
            com.idPair_[0] = command.targetPair_[0];
            com.idPair_[1] = command.targetPair_[1];
            return com;
        }
    }
    catch (LogicExcept &err) {
        return Command { .type_ = Command::ERROR, {0} };
    }
    */

    while (std::cin >> input) {
        if (input == "EXIT") {
            return Command{ .type_ = Command::EXIT, {0} };
        }
        else if (input == "INFO") {
            return Command{ .type_ = Command::INFO, {0} };
        }
        else if (input == "HELP") {
            return Command{ .type_ = Command::HELP, {0} };
        }
        else if (input == "CREATE") {
            std::cin >> input;
            if (input == "GRAPH") {
                return Command{ .type_ = Command::NEW_GRAPH, {0} };
            }
            else if (input == "VERTEX") {
                Command cmd = { .type_ = Command::NEW_VERTEX_AT, {0} };
                std::cin >> input;
                if (input != "AT") {
                    cmd.type_ = Command::ERROR;
                    return cmd;
                }
                Identity graph;
                if (!(std::cin >> graph)) {
                    std::cin.clear();
                    cmd.type_ = Command::ERROR;
                    return cmd;
                }
                cmd.id_ = graph;
                return cmd;
            }
            else {
                return Command{ .type_ = Command::ERROR, {0} };
            }
        }
        else if (input == "REMOVE") {
            std::cin >> input;
            if (input == "GRAPH") {
                Command cmd = { .type_ = Command::REM_GRAPH, {0} };
                Identity graph;
                if (!(std::cin >> graph)) {
                    std::cin.clear();
                    cmd.type_ = Command::ERROR;
                    return cmd;
                }
                cmd.id_ = graph;
                return cmd;
            }
            else if (input == "VERTEX") {
                Command cmd = { .type_ = Command::REM_VERTEX, {0} };
                Identity vertex;
                if (!(std::cin >> vertex)) {
                    std::cin.clear();
                    cmd.type_ = Command::ERROR;
                    return cmd;
                }
                cmd.id_ = vertex;
                return cmd;
            }
        }
        else if (input == "JOIN") {
            Command cmd = { .type_ = Command::JOIN, {0} };
            Identity vertex1;
            if (!(std::cin >> vertex1)) {
                std::cin.clear();
                cmd.type_ = Command::ERROR;
                return cmd;
            }
            Identity vertex2;
            if (!(std::cin >> vertex2)) {
                std::cin.clear();
                cmd.type_ = Command::ERROR;
                return cmd;
            }
            cmd.idPair_[0] = vertex1;
            cmd.idPair_[1] = vertex2;
            return cmd;
        }
        else if (input == "DISJOIN") {
            Command cmd = { .type_ = Command::DISJOIN, {0} };
            Identity vertex1;
            if (!(std::cin >> vertex1)) {
                std::cin.clear();
                cmd.type_ = Command::ERROR;
                return cmd;
            }
            Identity vertex2;
            if (!(std::cin >> vertex2)) {
                std::cin.clear();
                cmd.type_ = Command::ERROR;
                return cmd;
            }
            cmd.idPair_[0] = vertex1;
            cmd.idPair_[1] = vertex2;
            return cmd;
        }
        else {
            return Command{ .type_ = Command::ERROR, {0} };
        }
    }

    // For consistency, control should never reach here.
    return Command { .type_ = Command::ERROR, {0} };
}

ConsoleMain::Status ConsoleMain::Process (const Command *cmd)
{
    switch (cmd->type_) {
        default:
        case Command::ERROR:
            return ERROR;

        case Command::EXIT:
            return EXIT;

        case Command::INFO:
            render();
            refresh();
            return SUCCESS;

        case Command::HELP:
            hint();
            return SUCCESS;

    // Mutate
        case Command::NEW_GRAPH:
            return (control_->newGraph()) ? PENDING : ERROR;

        case Command::NEW_VERTEX_AT:
            return (control_->newVertexAt(cmd->id_)) ? PENDING : ERROR;

        case Command::REM_GRAPH:
            return (control_->remGraph(cmd->id_)) ? PENDING : ERROR;

        case Command::REM_VERTEX:
            return (control_->remVertex(cmd->id_)) ? PENDING : ERROR;

        case Command::JOIN:
            return (control_->join(cmd->idPair_[0], cmd->idPair_[1]))
                    ? PENDING : ERROR;

        case Command::DISJOIN:
            return (control_->disjoin(cmd->idPair_[0], cmd->idPair_[1]))
                    ? PENDING : ERROR;

    // Access
    }
}

void ConsoleMain::render ()
{
    display_.clear();
    display_.str(std::string());
    std::for_each(graphs_.begin(), graphs_.end(),
        [&] (std::pair<Identity, IdentityList> it) {
            display_ << "Graph " << it.first
                     << "\n============\n";
            std::for_each(it.second.begin(), it.second.end(),
                [&] (Identity vertex) {
                    display_ << vertex << " <--> ";
                    Result neighbourResult = control_->neighboursOf(vertex);
                    IdentityList neighbours = neighbourResult.idList();
                    std::for_each(neighbours.begin(), neighbours.end(),
                        [&] (Identity neighbour) {
                            display_ << neighbour << ", ";
                        });
                    display_ << "\n";
                });
            display_ << "\n\n";
            });
}

void ConsoleMain::refresh ()
{
    Print("%s\n", display_.str());
}
