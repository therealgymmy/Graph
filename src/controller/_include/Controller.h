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
    virtual Result hasGraph  (const Identity graph)  const;
    virtual Result hasVertex (const Identity vertex) const;
    virtual Result isJointBetween (const Identity vertex1,
                                   const Identity vertex2) const;

    virtual Result graphOf      (const Identity vertex) const;
    virtual Result neighboursOf (const Identity vertex) const;
    virtual Result verticesOf   (const Identity graph)  const;

    virtual Result allGraphs   () const;
    virtual Result allVertices () const;

//--Algorithm
    virtual Result hasCycleAt (const Identity graph) const;

//--Resource Creation
    virtual Result newGraph ();
    virtual Result newVertexAt (const Identity graph);

//--Resource Deletion
    virtual Result remGraph  (const Identity graph) ;
    virtual Result remVertex (const Identity vertex);

//--Resource Management
    virtual Result join    (const Identity vertex1, const Identity vertex2);
    virtual Result disjoin (const Identity vertex1, const Identity vertex2);

private:
    LogicController *logic_;
    AlgorithmController *alg_;
};

#endif//CONTROLLER_H
