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
        if ((status = Process(&cmd)) == EXIT) {
            return;
        }
        switch (status) {
            case PENDING:
                render();
                refresh();
                status = SUCCESS;
                break;
            case ERROR:
                if (cmd.type_ == Command::HAS_CYCLE_AT) {
                    Print("There doesn't exist a cycle at Graph %d.\n", cmd.id_);
                }
                else if (cmd.type_ == Command::HAS_PATH_AT) {
                    Print("There doesn't exist a path between "
                          "Vertex %d and Vertex %d at Graph %d.\n",
                          cmd.findPath_.vertexPair_[0],
                          cmd.findPath_.vertexPair_[1],
                          cmd.findPath_.graph_);
                }
                Print("Error in Operation!\n");
                break;
            case SUCCESS:
                if (cmd.type_ == Command::HAS_CYCLE_AT) {
                    Print("There exists a cycle at Graph %d.\n", cmd.id_);
                }
                else if (cmd.type_ == Command::HAS_PATH_AT) {
                    Print("There exists a path between "
                          "Vertex %d and Vertex %d at Graph %d.\n",
                          cmd.findPath_.vertexPair_[0],
                          cmd.findPath_.vertexPair_[1],
                          cmd.findPath_.graph_);
                }
                else if (cmd.type_ == Command::HAS_SPANNINGTREE_AT) {
                    Print("There exists a spanning tree at Graph %d.\n",
                          cmd.idPair_[0]);
                    render(cmd.idPair_[1]);
                    refresh();
                }
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
             << "    CREATE GRAPH;\n"
             << "    CREATE VERTEX AT GRAPH <Graph ID>;\n"
             << "    JOIN VERTEX <Vertex1 ID> AND <Vertex2 ID>;\n"
             << "    DISJOIN VERTEX <Vertex1 ID> AND <Vertex2 ID>;\n"
             << "    HAS CYCLE AT GRAPH <Graph ID>;\n"
             << "    HAS PATH AT VERTEX <Vertex1 ID> AND <Vertex2 ID> AT GRAPH <Graph ID>;\n"
             << "    HAS SPANNINGTREE AT GRAPH <Graph ID>;\n";
    refresh();
}

ConsoleMain::Command ConsoleMain::interaction ()
{
    Print("Enter Command: ");
    std::string input;

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
            if (command.resourceType_ == cmd::Command::Resource::GRAPH) {
                return Command{ .type_ = Command::NEW_GRAPH, {0} };
            }
            else if (command.resourceType_ == cmd::Command::Resource::VERTEX) {
                Command com = { .type_ = Command::NEW_VERTEX_AT, {0} };
                com.id_ = command.resource_;
                return com;
            }
        }
        if (command == cmd::Command::Action::REMOVE) {
            if (command.resourceType_ == cmd::Command::Resource::GRAPH) {
                Command com = { .type_ = Command::REM_GRAPH, {0} };
                com.id_ = command.resource_;
                return com;
            }
            else if (command.resourceType_ == cmd::Command::Resource::VERTEX) {
                Command com = { .type_ = Command::REM_VERTEX, {0} };
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
        if (command == cmd::Command::Action::HAS) {
            if (command.resourceType_ == cmd::Command::Resource::CYCLE) {
                Command com{ .type_ = Command::HAS_CYCLE_AT, {0} };
                com.id_ = command.resource_;
                return com;
            }
            else if (command.resourceType_ == cmd::Command::Resource::PATH) {
                Command com{ .type_ = Command::HAS_PATH_AT, {0} };
                com.findPath_ = {
                    .graph_ = command.findPath_.graph_,
                    .vertexPair_ = { command.findPath_.vertexPair_[0],
                                     command.findPath_.vertexPair_[1]}
                };
                return com;
            }
            else if (command.resourceType_ == cmd::Command::Resource::SPANNINGTREE) {
                Command com{ .type_ = Command::HAS_SPANNINGTREE_AT, {0} };
                com.idPair_[0] = command.resource_;
                return com;
            }
        }
    }
    catch (RuntimeExcept &err) {
        return Command { .type_ = Command::ERROR, {0} };
    }
    catch (LogicExcept &err) {
        return Command { .type_ = Command::ERROR, {0} };
    }

    return Command { .type_ = Command::ERROR, {0} };
}

ConsoleMain::Status ConsoleMain::Process (Command *cmd)
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
        case Command::HAS_CYCLE_AT:
            return (control_->hasCycleAt(cmd->id_)) ? SUCCESS : ERROR;
        case Command::HAS_PATH_AT:
            return (control_->hasPathAt(
                        cmd->findPath_.vertexPair_[0],
                        cmd->findPath_.vertexPair_[1],
                        cmd->findPath_.graph_
                        )) ? SUCCESS : ERROR;
        case Command::HAS_SPANNINGTREE_AT:
            Result result = control_->findSpanningTreeAt(cmd->idPair_[0]);
            if (!result) {
                return ERROR;
            }
            cmd->idPair_[1] = result.id();
            return SUCCESS;
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

void ConsoleMain::render (const Identity graph)
{
    display_.clear();
    display_.str(std::string());
    display_ << "Graph " << graph;
    display_ << "\n=============\n";
    IdentityList list = control_->verticesOf(graph).idList();
    std::for_each(list.begin(), list.end(),
        [&] (Identity v) {
            std::stringstream buffer;
            buffer << v << " <--> ";
            IdentityList neighbours = control_->neighboursOf(v).idList();
            std::for_each(neighbours.begin(), neighbours.end(),
                [&] (Identity n) {
                    buffer << n << ", ";
                });
            display_ << buffer.str();
            display_ << "\n";
        });
    display_ << "\n\n";
}

void ConsoleMain::refresh ()
{
    Print("%s\n", display_.str());
}
