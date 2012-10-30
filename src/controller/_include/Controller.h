#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../../common/_include/AccessorApi.h"
#include "../../common/_include/MutatorApi.h"

class Controller : public AccessorApi,
                   public MutatorApi {
};

#endif//CONTROLLER_H
