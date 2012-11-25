#ifndef ALG_CYCLE_DETECT_H
#define ALG_CYCLE_DETECT_H

// Dependencies
#include "AlgorithmBase.h"

class NodeStatus;

class CycleDetect : public Algorithm {
public:
    CycleDetect (LogicController &logic);
    virtual Result run (const Parameter& param);

private:
    void findCycle (const Identity v_id,
                    const Identity parent_id,
                    NodeStatus *node);
};

#endif//ALG_CYCLE_DETECT_H
