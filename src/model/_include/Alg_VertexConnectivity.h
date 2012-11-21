#ifndef ALG_VERTEX_CONNECTIVITY_H
#define ALG_VERTEX_CONNECTIVITY_H

// Dependencies
#include "AlgorithmBase.h"

class VertexConnectivity : public Algorithm {
public:
    VertexConnectivity (LogicController &logic = LogicControl);
    virtual Result run (const Parameter& param);
};

#endif//ALG_VERTEX_CONNECTIVITY_H
