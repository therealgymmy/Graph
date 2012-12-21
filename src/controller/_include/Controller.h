#ifndef CONTROLLER_H
#define CONTROLLER_H

// Controller
//  - translates requests from View to Model and vice versa.
//  - is a vessel for data transportation, not storage.
//  - resource related functions notify() observers.

// Dependencies
#include "../../common/_include/Subject.h"
#include "../../model/_include/AlgorithmController.h"
#include "../../model/_include/LogicController.h"
#include "AccessorApi.h"
#include "MutatorApi.h"

class Controller : public Subject,
                   public AccessorApi,
                   public MutatorApi {
public:
//--Constructor
    Controller (LogicController *logic, AlgorithmController *alg);

//--Basic Query
    virtual Result hasGraph  (const Identity graph)  const override;
    virtual Result hasVertex (const Identity vertex) const override;
    virtual Result isJointBetween (const Identity vertex1,
                                   const Identity vertex2) const override;

    virtual Result graphOf      (const Identity vertex) const override;
    virtual Result neighboursOf (const Identity vertex) const override;
    virtual Result verticesOf   (const Identity graph)  const override;

    virtual Result allGraphs   () const override;
    virtual Result allVertices () const override;

//--Algorithm
    virtual Result hasCycleAt (const Identity graph) const override;
    virtual Result hasPathAt  (const Identity v1,
                               const Identity v2,
                               const Identity graph) const override;
    virtual Result findSpanningTreeAt (const Identity graph) const override;


//--Resource Creation
    virtual Result newGraph () override;
    virtual Result newVertexAt (const Identity graph) override;

//--Resource Deletion
    virtual Result remGraph  (const Identity graph)  override;
    virtual Result remVertex (const Identity vertex) override;

//--Resource Management
    virtual Result join    (const Identity vertex1, const Identity vertex2) override;
    virtual Result disjoin (const Identity vertex1, const Identity vertex2) override;

private:
    LogicController *logic_;
    AlgorithmController *alg_;
};

#endif//CONTROLLER_H
