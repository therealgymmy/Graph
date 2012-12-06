#ifndef ALG_SPANNING_TREE_H
#define ALG_SPANNING_TREE_H

// Dependencies
#include <vector>
#include "AlgorithmBase.h"
#include "ModelTypes.h"

class SpanningTree : public Algorithm {
public:
    SpanningTree (LogicController &logic);
    virtual Result run (const Parameter& param) override;

private:
    void findSpanningTree (Identity g_id, Identity tree);
};

#endif//ALG_SPANNING_TREE_H
