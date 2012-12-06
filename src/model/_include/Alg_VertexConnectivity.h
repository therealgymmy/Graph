#ifndef ALG_VERTEX_CONNECTIVITY_H
#define ALG_VERTEX_CONNECTIVITY_H

// Dependencies
#include "AlgorithmBase.h"

class VertexConnectivity : public Algorithm {
public:
    VertexConnectivity (LogicController &logic);
    virtual Result run (const Parameter& param) override;

private:
    void findPath (const Identity v1_id,
                   const Identity target_id,
                   const Identity parent_id,
                   NodeStatus *node);
};

#endif//ALG_VERTEX_CONNECTIVITY_H
