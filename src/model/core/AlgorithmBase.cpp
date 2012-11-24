#include "../_include/AlgorithmBase.h"

void NodeStatus::visit (const Identity id)
{
    status_[id] = GREY;
}

void NodeStatus::leave (const Identity id)
{
    status_[id] = BLACK;
}

NodeStatus::Color NodeStatus::statusOf (const Identity id) const
{
    auto it = status_.find(id);
    if (it == status_.end()) {
        return WHITE;
    }
    return it->second;
}
