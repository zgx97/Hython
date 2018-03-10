#ifndef _HYTHON_TYPE_H
#define _HYTHON_TYPE_H

#include "hython_interface.h"
#include <cinttypes>
#include <deque>
#include <string>

using std::string;
using std::deque;

namespace HL {

class IntValue : public IValue {
public :
    IntValue() : IValue(IValue::Type::Int), num(0) {}
    IntValue(int64_t num) : IValue(IValue::Type::Int), num(num) {}
    virtual ~IntValue() {}
    int64_t getValue() { return this->num; }
    void setValue(int64_t num) { this->num = num; }
    virtual bool isTrue() { return this->num != 0; }
    virtual bool isFalse() { return this->num == 0; };
    virtual void Accept(IVisitor *visitor) { visitor->Visit(this); return ;}
    virtual shared_ptr<IValue> isEqual(IValue *);
    virtual shared_ptr<IValue> isLittle(IValue *);
    virtual shared_ptr<IValue> __operator_other(shared_ptr<IValue> &, int);

private :
    int64_t num;
};

class FloatValue : public IValue {
public :
    FloatValue() : IValue(IValue::Type::Float), num(0.0) {}
    FloatValue(double num) : IValue(IValue::Type::Float), num(num) {}
    virtual ~FloatValue() {}
    double getValue() { return this->num; }
    void setValue(double num) { this->num = num; }
    virtual bool isTrue() { return this->num != 0.0; }
    virtual bool isFalse() { return this->num == 0.0; };
    virtual void Accept(IVisitor *visitor) { visitor->Visit(this); return ;}
    virtual shared_ptr<IValue> isEqual(IValue *);
    virtual shared_ptr<IValue> isLittle(IValue *);
    virtual shared_ptr<IValue> __operator_other(shared_ptr<IValue> &, int);

private :
    double num;
};

class StringValue : public IValue {
public :
    StringValue() : IValue(IValue::Type::String), str("") {}
    StringValue(string str) : IValue(IValue::Type::String), str(str) {}
    virtual ~StringValue() {}
    string getValue() { return this->str; }
    void setValue(string str) { this->str = str; }
    virtual bool isTrue() { return this->str != ""; }
    virtual bool isFalse() { return this->str == ""; };
    virtual void Accept(IVisitor *visitor) { visitor->Visit(this); return ;}
    virtual shared_ptr<IValue> isEqual(IValue *);
    virtual shared_ptr<IValue> isLittle(IValue *);
    virtual shared_ptr<IValue> __operator_other(shared_ptr<IValue> &, int);

private :
    string str;
};

class ArrayValue : public IValue {
public :
    ArrayValue() : IValue(IValue::Type::Array), arr() {}
    ArrayValue(const ArrayValue &a);
    virtual ~ArrayValue() {}
    virtual bool isTrue() { return this->arr.size() != 0; }
    virtual bool isFalse() { return this->arr.size() == 0; };
    virtual void Accept(IVisitor *visitor) { visitor->Visit(this); return ;}
    void push_back(shared_ptr<IValue> val) { this->arr.push_back(val); }
    void push_front(shared_ptr<IValue> val) { this->arr.push_front(val); }
    size_t getSize() { return this->arr.size(); }
    shared_ptr<IValue> getValue(size_t ind) { return (this->arr.size() > ind) ? this->arr[ind] : IValue::HLNull; }
    virtual shared_ptr<IValue> isEqual(IValue *);
    virtual shared_ptr<IValue> isLittle(IValue *);
    virtual shared_ptr<IValue> __operator_other(shared_ptr<IValue> &, int);

private :
    deque<shared_ptr<IValue> > arr;
};


} // end of namespace HL

#endif
