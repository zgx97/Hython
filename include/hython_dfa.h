#ifndef _HYTHON_DFA_H
#define _HYTHON_DFA_H

#include "hlLexer.h"
#include "hlParser.h"
#include "hython_parameters.h"
#include "hython_interface.h"
#include "hython_unit.h"
#include <vector>
#include <memory>
#include <stack>

using std::vector;
using std::shared_ptr;
using std::make_shared;
using std::stack;

namespace HL {

class ExprDFANode;
class BlockBeginDFANode;
class BlockEndDFANode;
class OneEdgeDFANode;

class DFANodeFactory;

class AnyEdge;
class YesEdge;
class NotEdge;
class ValueEdge;

class DFA {
public :
    DFA() : begin(nullptr), end(nullptr), productor(nullptr) {
        this->productor = make_shared<DFANodeFactory>();
    }
    DFA(shared_ptr<DFANodeFactory> productor) 
        : begin(nullptr), end(nullptr), productor(productor) {} 
    ~DFA() {}
    void exchange(pANTLR3_BASE_TREE);
    void run();
    IDFANode *getBegin() { return this->begin; }
    IDFANode *getEnd() { return this->end; }

private :
    void __initBlockBeginEnd();
    IDFANode *begin;
    IDFANode *end;
    shared_ptr<IDFAEdge> suggestion_edge;
    shared_ptr<DFANodeFactory> productor;
};

class DFANodeFactory {
public :
    DFANodeFactory() {}
    ~DFANodeFactory() {}
    IDFANode *getNewNode(IDFANode::Type, pANTLR3_BASE_TREE = nullptr);
    void clearBreakPointList(IDFANode *);
    void clearContinuePointList(IDFANode *);
    stack<IDFANode *> __breakPointList;
    stack<IDFANode *> __continuePointList;
    
private :
    vector<shared_ptr<IDFANode> > __storage;
};

class MasterDFANode : public IDFANode {
public :
    MasterDFANode(pANTLR3_BASE_TREE tree) : IDFANode(IDFANode::Type::Master), __tree(tree) {}
    virtual ~MasterDFANode() {}
    virtual shared_ptr<IValue> getValue(shared_ptr<Parameters> &);

private :
    pANTLR3_BASE_TREE __tree;
};

class BlockBeginDFANode : public IDFANode {
public :
    BlockBeginDFANode() : IDFANode(IDFANode::Type::BlockBegin) {}
    virtual ~BlockBeginDFANode() {}
    virtual void setCheckpoint(IDFANode *cp) { this->__checkpoint = cp; }
    virtual void beginForward(shared_ptr<Parameters> &);

private :
    IDFANode *__checkpoint;
};

class BlockEndDFANode : public IDFANode {
public :
    BlockEndDFANode() : IDFANode(IDFANode::Type::BlockEnd) {}
    virtual ~BlockEndDFANode() {}
    virtual void beginForward(shared_ptr<Parameters> &);
};

class OneEdgeDFANode : public IDFANode {
public :
    OneEdgeDFANode() : IDFANode(IDFANode::Type::OneEdge) {}
    virtual ~OneEdgeDFANode() {}
    virtual void addEdge(IDFAEdge::Type, IDFANode *);
};

class AnyEdge : public IDFAEdge {
public :
    AnyEdge(IDFANode *node) : IDFAEdge(IDFAEdge::Type::AnyEdge, node) {}
    virtual ~AnyEdge() {}
    virtual bool valid(shared_ptr<IValue> &val) { return true; };
};

class YesEdge : public IDFAEdge {
public :
    YesEdge(IDFANode *node) : IDFAEdge(IDFAEdge::Type::YesEdge, node) {}
    virtual ~YesEdge() {}
    virtual bool valid(shared_ptr<IValue> &val) { return HL::isTrue(val); };
};

class NotEdge : public IDFAEdge {
public :
    NotEdge(IDFANode *node) : IDFAEdge(IDFAEdge::Type::NotEdge, node) {}
    virtual ~NotEdge() {}
    virtual bool valid(shared_ptr<IValue> &val) { return HL::isFalse(val); };
};

class ValueEdge : public IDFAEdge {
public :
    ValueEdge(IDFANode *node) 
        : IDFAEdge(IDFAEdge::Type::ValueEdge, node) {}
    virtual ~ValueEdge() {}
    virtual bool valid(shared_ptr<IValue> &val);
};

} // end of namespace HL

#endif
