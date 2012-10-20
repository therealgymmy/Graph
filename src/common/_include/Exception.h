#ifndef EXCEPTION_H
#define EXCEPTION_H

class ExceptionBase {
};

class RuntimeExcept : public ExceptionBase {
};

class MemoryExcept : public RuntimeExcept {
};

#endif//EXCEPTION_H
