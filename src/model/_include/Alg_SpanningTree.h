#ifndef ALG_SPANNING_TREE_H
#define ALG_SPANNING_TREE_H

// Dependencies
#include <vector>
#include "AlgorithmBase.h"
#include "ModelTypes.h"

class SpanningTree : public Algorithm {
public:
    typedef std::map<Identity, Identity> TreeNodes;

    SpanningTree (LogicController &logic);
    virtual Result run (const Parameter& param) override;

private:
    void findSpanningTree (const Identity v_id,
                           const Identity parent_id,
                           const Identity tree,
                           TreeNodes treeNodes,
                           NodeStatus *node);
};

#endif//ALG_SPANNING_TREE_H
