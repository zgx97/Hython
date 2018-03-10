#ifndef _HYTHON_INTERFACE_H
#define _HYTHON_INTERFACE_H

#include "hython_parameters.h"
#include "hlLexer.h"
#include "hlParser.h"
#include <cassert>
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>
#include <memory>

using std::shared_ptr;
using std::weak_ptr;
using std::string;
using std::vector;


namespace HL {

class IMaster;
class IFactory;
class IValue;
class Parameters;
class IDFANode;
class IDFAEdge;

class IDFAEdge {
public :
    enum class Type {
        AnyEdge,
        YesEdge,
        NotEdge,
        ValueEdge,
        TypeNum
    };
    IDFAEdge(IDFAEdge::Type type, IDFANode *node) 
        : __node(node), __type(type), __next(nullptr) {}
    virtual ~IDFAEdge() {}
    virtual void setNext(shared_ptr<IDFAEdge> &next) { this->__next = next; }
    virtual IDFAEdge::Type getType() { return this->__type; }
    virtual void setValue(shared_ptr<IValue> val) { this->__val = val; }
    virtual IDFANode *forward(shared_ptr<IValue> &);
    IDFANode *getNode() { return this->__node; }

protected:
    virtual bool valid(shared_ptr<IValue> &) = 0;
    shared_ptr<IValue> __val;

private :
    IDFANode *__node;
    IDFAEdge::Type __type;
    shared_ptr<IDFAEdge> __next;
};

class IDFANode {
public :
    enum class Type {
        BlockBegin,
        BlockEnd,
        Master,
        OneEdge,
        TypeNum
    };
    IDFANode(Type type)
        : __type(type), __edges(nullptr) {}
    virtual ~IDFANode() {}
    virtual IDFANode *forward(shared_ptr<Parameters> &);
    IDFANode::Type getType() { return this->__type; }
    void clearEdges() { this->__edges = nullptr; }
    virtual void addEdge(IDFAEdge::Type, IDFANode *);
    virtual void addEdge(shared_ptr<IDFAEdge> );
    
protected :
    virtual void beginForward(shared_ptr<Parameters> &) { return ; }
    virtual shared_ptr<IValue> getValue(shared_ptr<Parameters> &);
    IDFANode::Type __type;
    shared_ptr<IDFAEdge> __edges;
};

class IFactory {
public:
    virtual bool valid(pANTLR3_BASE_TREE) = 0;
    virtual IMaster *creator(shared_ptr<Parameters> ) = 0;
    IFactory *next;
    virtual ~IFactory() {}
};

class IMaster {
public:
    IMaster(shared_ptr<Parameters> param) : param(param) {}
    virtual ~IMaster() {}
    virtual shared_ptr<IValue> run(pANTLR3_BASE_TREE) = 0;
protected:
    shared_ptr<Parameters> param;
};

class IntValue;
class FloatValue;
class StringValue;
class ArrayValue;

class IValue {
public :
    class IVisitor {
    public :
        virtual void Visit(IntValue *) = 0;
        virtual void Visit(FloatValue *) = 0;
        virtual void Visit(StringValue *) = 0;
        virtual void Visit(ArrayValue *) = 0;
    };
    virtual void Accept(IVisitor *) = 0;
    enum class Type {
        None,
        Int,
        Float,
        String,
        Array,
        TypeNum
    };
    IValue(Type t) : __t(t) , __name("") {}
    virtual ~IValue() {}
    virtual Type getType() { return this->__t; }
    virtual string getName() { return this->__name; }
    virtual void setName(string name) { this->__name = name; }
    virtual bool isTrue() = 0;
    virtual bool isFalse() = 0;
    virtual shared_ptr<IValue> isEqual(IValue *) = 0;
    virtual shared_ptr<IValue> isLittle(IValue *) = 0;
    virtual shared_ptr<IValue> operator==(IValue *);
    virtual shared_ptr<IValue> operator<(IValue *);
    virtual shared_ptr<IValue> operator||(IValue *);
    virtual shared_ptr<IValue> operator&&(IValue *);
    virtual shared_ptr<IValue> operator>(IValue *);
    virtual shared_ptr<IValue> operator!=(IValue *);
    virtual shared_ptr<IValue> operator>=(IValue *);
    virtual shared_ptr<IValue> operator<=(IValue *);
    virtual bool gt(IValue *obj) { return this->getType() > obj->getType(); }
    virtual shared_ptr<IValue> operator_all(shared_ptr<IValue> &, int);
    static const shared_ptr<IValue> HLNull;
    static const shared_ptr<IValue> HLTrue;
    static const shared_ptr<IValue> HLFalse;

protected:
    virtual shared_ptr<IValue> __operator_other(shared_ptr<IValue> &, int) = 0;
    
    Type __t;
    string __name;
};

} // end of namespace HL

#endif
