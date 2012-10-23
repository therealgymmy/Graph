Graph
=====

Introduction
------------
**Graph** is a program which builds simple graphs as defined in graph theory of MATH239
at University of Waterloo.
This means you can build a graph and query the program on the graph's connectivity,
if it's isomorphic to another graph, or find a spanning tree, etc.

**Graph** is still a work in progress.
A command line interpreter should come first.
Also in the plan is a gui front-end, though I'm still considering which framework to use.

Pre-requisite
--------------

To build **Graph**, you'll need rake and a compiler conforming to the **C++11** standard.

Compile and Test
-----------------------

#### Rake Commands
* `rake` or `rake help` outputs help message.
* `rake build` builds the project normally.
* `rake debug` links the test framework to the project for testing.
* `rake run` runs the executable.
* `rake test` runs the executable within valgrind (with --leak-check=full).

#### Source Organization
    src/ ---> common/ ---> _include/
         ---> model/  ---> _include/
                      ---> base/
                      ---> core/
         ---> main.cpp

* `src` is the place for all program source code.
* `common` is for facilities such as exception handling.
* `model` is the part that handles internal logic of the program.
* `_include` within each directory stores all corresponding header files.

In the near future, `controller` and `view` will be added to handle external requests.

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
