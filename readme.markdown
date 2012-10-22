Graph
=====

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
         ---> main.cpp

* `src` is the place for all program source code.
* `common` is for facilities such as exception handling.
* `model` is the part that handles internal logic of the program.

All header files go into the corresponding `_include` directory.

**Graph** is still a work in progress.
Later on, `controller` and `view` should be added to handle external requests.
A command line interpreter should come first.
Also in the plan is a gui front-end, though I'm still considering which framework to use.

#### Tests Organization
    test/ ---> _include/
          ---> test_interface/
          ---> test_suites/
          ---> test_main.cpp

* `test` is the place for all testing related code.
* `_include` is for all the header files.
* `test_interface` is the part handling core logic of the test framework.
* `test_suites` stores individual tests.

To add a new test, create files corresponding to the sample test and modify accordingly.
