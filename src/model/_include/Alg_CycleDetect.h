#ifndef ALG_CYCLE_DETECT_H
#define ALG_CYCLE_DETECT_H

// Dependencies
#include "AlgorithmBase.h"

class NodeStatus;

class CycleDetect : public Algorithm {
public:
    virtual Result run (const Parameter& param);

private:
    void findCycle (const Identity v_id, const Identity parent_id, NodeStatus *n);
};

#endif//ALG_CYCLE_DETECT_H