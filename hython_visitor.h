#ifndef _HYTHON_VISITOR_H
#define _HYTHON_VISITOR_H

#include <cstdio>
#include "hython_type.h"
#include "hython_interface.h"

namespace HL {

class ConvertToStringVisitor : public IValue::IVisitor {
public :
    virtual void Visit(IntValue *obj);
    virtual void Visit(FloatValue *obj);
    virtual void Visit(StringValue *obj);
    virtual void Visit(ArrayValue *obj);
    shared_ptr<StringValue> getResult() { return this->result; }
private :
    shared_ptr<StringValue> result;
};

class ConvertToIntVisitor : public IValue::IVisitor {
public :
    virtual void Visit(IntValue *obj);
    virtual void Visit(FloatValue *obj);
    virtual void Visit(StringValue *obj);
    virtual void Visit(ArrayValue *obj);
    shared_ptr<IntValue> getResult() { return this->result; }
private :
    shared_ptr<IntValue> result;
};

class ConvertToFloatVisitor : public IValue::IVisitor {
public :
    virtual void Visit(IntValue *obj);
    virtual void Visit(FloatValue *obj);
    virtual void Visit(StringValue *obj);
    virtual void Visit(ArrayValue *obj);
    shared_ptr<FloatValue> getResult() { return this->result; }
private :
    shared_ptr<FloatValue> result;
};

class ConvertToArrayVisitor : public IValue::IVisitor {
public :
    virtual void Visit(IntValue *obj);
    virtual void Visit(FloatValue *obj);
    virtual void Visit(StringValue *obj);
    virtual void Visit(ArrayValue *obj);
    shared_ptr<ArrayValue> getResult() { return this->result; }

private :
    shared_ptr<ArrayValue> result;
};

class PrintValueVisitor : public IValue::IVisitor {
public :
    virtual void Visit(IntValue *obj);
    virtual void Visit(FloatValue *obj);
    virtual void Visit(StringValue *obj);
    virtual void Visit(ArrayValue *obj);
};

} // end of namespace HL

#endif
