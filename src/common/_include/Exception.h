#ifndef EXCEPTION_H
#define EXCEPTION_H

class ExceptionBase {
};

class RuntimeExcept : public ExceptionBase {
};

class BadArgumentExcept : public RuntimeExcept {
};

class MemoryExcept : public RuntimeExcept {
};

class NumericExcept : public RuntimeExcept {
};

class OverflowExcept : public NumericExcept {
};

#endif//EXCEPTION_H
