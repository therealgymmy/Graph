#include "../_include/Controller.h"
#include "../../common/_include/Exception.h"

Controller::Controller (LogicController *logic, AlgorithmController *alg)
: logic_(logic), alg_(alg)
{
}

Result Controller::hasGraph (const Identity graph) const
{
    return Result(Result::BOOL, logic_->hasGraph(graph));
}

Result Controller::hasVertex (const Identity vertex) const
{
    return Result(Result::BOOL, logic_->hasVertex(vertex));
}

Result Controller::isJointBetween (const Identity vertex1,
                                   const Identity vertex2) const
{
    return Result(Result::BOOL, logic_->isJointBetween(vertex1, vertex2));
}

Result Controller::graphOf (const Identity vertex) const
try
{
    Identity graph = logic_->graphOf(vertex);
    Result result(Result::ID, true);
    result.setId(graph);
    return result;
}
catch (BadArgumentExcept &err)
{
    return Result(Result::ID, false);
}

Result Controller::neighboursOf (const Identity vertex) const
try
{
    IdentityList neighbours = logic_->neighboursOf(vertex);
    Result result(Result::ID_LIST, true);
    result.setIdList(neighbours);
    return result;
}
catch (BadArgumentExcept &err)
{
    return Result(Result::ID_LIST, false);
}

Result Controller::verticesOf (const Identity graph) const
try
{
    IdentityList neighbours = logic_->verticesOf(graph);
    Result result(Result::ID_LIST, true);
    result.setIdList(neighbours);
    return result;
}
catch (BadArgumentExcept &err)
{
    return Result(Result::ID_LIST, false);
}

Result Controller::allGraphs () const
{
    Result result(Result::ID_LIST, true);
    result.setIdList(logic_->allGraphs());
    return result;
}

Result Controller::allVertices () const
{
    Result result(Result::ID_LIST, true);
    result.setIdList(logic_->allVertices());
    return result;
}

Result Controller::hasCycleAt (const Identity graph) const
try
{
    return Result(Result::BOOL, alg_->hasCycleAt(graph));
}
catch (BadArgumentExcept &err)
{
    return Result(Result::BOOL, false);
}

Result Controller::newGraph ()
try
{
    Result result(Result::ID, true);
    result.setId(logic_->newGraph());
    notify();
    return result;
}
catch (OverflowExcept &err)
{
    return Result(Result::ID, false);
}

Result Controller::newVertexAt (const Identity graph)
try
{
    Result result(Result::ID, true);
    result.setId(logic_->newVertex(graph));
    notify();
    return result;
}
catch (OverflowExcept &err)
{
    return Result(Result::ID, false);
}
catch (BadArgumentExcept &err)
{
    return Result(Result::ID, false);
}

Result Controller::remGraph (const Identity graph)
{
    Result result(Result::BOOL, logic_->remGraph(graph));
    notify();
    return result;
}

Result Controller::remVertex (const Identity vertex)
{
    Result result(Result::BOOL, logic_->remVertex(vertex));
    notify();
    return result;
}

Result Controller::join (const Identity vertex1, const Identity vertex2)
{
    Result result(Result::BOOL, logic_->join(vertex1, vertex2));
    notify();
    return result;
}

Result Controller::disjoin (const Identity vertex1, const Identity vertex2)
{
    Result result(Result::BOOL, logic_->disjoin(vertex1, vertex2));
    notify();
    return result;
}
