#include "../_include/Alg_SpanningTree.h"

// Dependencies
#include <algorithm>
#include <utility>
#include "../../common/_include/Exception.h"
#include "../_include/Graph.h"

SpanningTree::SpanningTree (LogicController &logic)
: Algorithm(logic)
{
}

SpanningTree::Result
SpanningTree::run (const SpanningTree::Parameter& parm)
{
    Identity g_id = parm.id_;

    NodeStatus node;
    Identity tree = logic_.newGraph();
    IdentityList list = logic_.verticesOf(g_id);
    TreeNodes treeNodes;
    for (Identity id : list) {
        treeNodes[id] = logic_.newVertex(tree);
    }

    findSpanningTree(*list.begin(), NULL_IDENTITY, tree, treeNodes, &node);

    return Result { .id_ = tree };
}

void
SpanningTree::findSpanningTree (const Identity v_id,
                                const Identity parent_id,
                                const Identity tree,
                                TreeNodes treeNodes,
                                NodeStatus *nodeStatus)
{
    if (nodeStatus->statusOf(v_id) == NodeStatus::GREY) {
        return;
    }

    nodeStatus->visit(v_id);

    if (parent_id != NULL_IDENTITY) {
        if (!logic_.join(treeNodes[v_id], treeNodes[parent_id])) {
            throw LogicExcept();
        }
    }

    IdentityList neighbours = logic_.neighboursOf(v_id);
    std::for_each(neighbours.begin(), neighbours.end(),
                  [&] (const Identity id) {
                      if (id != parent_id &&
                          nodeStatus->statusOf(id) != NodeStatus::BLACK) {
                          findSpanningTree(id, v_id, tree, treeNodes, nodeStatus);
                      }
                  });

    nodeStatus->leave(v_id);
}
