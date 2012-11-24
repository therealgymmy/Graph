Graph
=====

Introduction
------------
**Graph** is a program which builds simple graphs as defined in graph theory of MATH239
at University of Waterloo.
This means you can build a graph and query the program on the graph's connectivity,
if it's isomorphic to another graph, or find a spanning tree, etc.

**Graph** is still a work in progress.
A basic command line interpreter is now available.
Also in the plan is a gui front-end, though I'm still considering which framework to use.

Pre-requisite
--------------

To build **Graph**, you'll need rake and a compiler conforming to the **C++11** standard.

How to Use Graph
----------------

#### Graph Commands
* `EXIT`
* `INFO`
* `HELP`
* `CREATE GRAPH;`
* `CREATE VERTEX AT GRAPH <Graph ID>;`
* `JOIN VERTEX <Vertex1 ID> AND <Vertex2 ID>;`
* `DISJOIN VERTEX <Vertex1 ID> AND <Vertex2 ID>;`
* `HAS CYCLE AT GRAPH <Graph ID>;`
* `HAS PATH AT VERTEX <Vertex1 ID> AND <Vertex2 ID> AT GRAPH <Graph ID>;`

Compile and Test
-----------------------

#### Rake Commands
* `rake` or `rake help` outputs help message.
* `rake info` outputs project related information.
* `rake build` builds the project normally.
* `rake debug` links the test framework to the project for testing.
* `rake run` runs the executable.
* `rake test` runs the executable within valgrind (with --leak-check=full).

#### Project Organization
    Graph/ ---> doc/                [Documentation]
           ---> ext/                [External libraries/resources]
           ---> obj/                [Object files (not synced)]
           ---> src/                [Source files]
           ---> test/               [Unit test source files]
           ---> rakefile
           ---> readme.md
           ---> test_results.log    [Log file (not synced)]
           ---> ...more misc stuff

#### Source Organization
    src/ ---> common/
         ---> controller/
         ---> external/
         ---> model/
         ---> view/
         ---> main.cpp

* `src` is the place for all program source code.
* `common` is for facilities such as exception handling.
* `model` handles internal logic of the program.
* `controller` handles communication between `view` and `model`.
* `view` is the user interface component.

#### Test Organization
    test/ ---> _include/
          ---> test_core/
          ---> test_suites/
          ---> test_main.cpp

* `test` is the place for all testing related code.
* `_include` is for all the header files.
* `test_core` is the part handling core logic of the test framework.
* `test_suites` stores individual tests.

To add a new test, create files corresponding to the sample test and modify accordingly.
