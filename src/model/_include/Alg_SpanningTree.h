#ifndef ALG_SPANNING_TREE_H
#define ALG_SPANNING_TREE_H

// Dependencies
#include <vector>
#include "AlgorithmBase.h"
#include "ModelTypes.h"

class Tree {
public:
    class Node {
        Identity v_id;
        std::vector<Node*> neighbours_;
    };

private:
};

class SpanningTree : public Algorithm {
public:
    SpanningTree (LogicController &logic);
    virtual Result run (const Parameter& param) override;

    Tree findSpanningTree (Identity g_id);

private:
    void findSpanningTree (Identity v_id,
                           Identity parent_id,
                           NodeStatus *node,
                           Tree *tree);
};

#endif//ALG_SPANNING_TREE_H
