#ifndef EXCEPTION_H
#define EXCEPTION_H

class ExceptionBase {
};

class RuntimeExcept : public ExceptionBase {
};

class LogicExcept : public ExceptionBase {
};

class MemoryExcept : public RuntimeExcept {
};

class NumericExcept : public RuntimeExcept {
};

class BadArgumentExcept : public LogicExcept {
};

class BadTokenExcept : public LogicExcept {
};

class OverflowExcept : public NumericExcept {
};

#endif//EXCEPTION_H
