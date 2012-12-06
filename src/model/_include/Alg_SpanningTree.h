#ifndef ALG_SPANNING_TREE_H
#define ALG_SPANNING_TREE_H

// Dependencies
#include "AlgorithmBase.h"

class SpanningTree : public Algorithm {
public:
    SpanningTree (LogicController &logic);
    virtual Result run (const Parameter& param) override;

private:
};

#endif//ALG_SPANNING_TREE_H
