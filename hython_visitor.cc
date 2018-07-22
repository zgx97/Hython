#include <cstdio>
#include "hython_type.h"
#include "hython_interface.h"
#include "hython_visitor.h"

namespace HL {

using std::make_shared;

void ConvertToStringVisitor::Visit(IntValue *obj) {
    static const size_t MAX_N = 22;
    char str[MAX_N];
    snprintf(str, MAX_N, "%" PRId64, obj->getValue());
    this->result = make_shared<StringValue>(str);
    return ; 
}
void ConvertToStringVisitor::Visit(FloatValue *obj) {
    static const size_t MAX_N = 1000;
    char str[MAX_N];
    snprintf(str, MAX_N, "%lf", obj->getValue());
    this->result = make_shared<StringValue>(str);
    return ;
}
void ConvertToStringVisitor::Visit(StringValue *obj) {
    this->result = make_shared<StringValue>(obj->getValue());
    return ;
}

void ConvertToStringVisitor::Visit(ArrayValue *obj) {
    string ret = "";
    ConvertToStringVisitor vis;
    shared_ptr<IValue> val;
    for (int i = 0; i < obj->getSize(); i++) {
        obj->getValue(i)->Accept(&vis);
        if (ret != "") {
            ret += ", ";
        }
        ret += vis.getResult()->getValue();
    }
    ret = "[ " + ret + " ]";
    this->result = make_shared<StringValue>(ret);
    return ;
}

void ConvertToIntVisitor::Visit(IntValue *obj) {
    this->result = make_shared<IntValue>(obj->getValue());
    return ; 
}
void ConvertToIntVisitor::Visit(FloatValue *obj) {
    this->result = make_shared<IntValue>((int64_t)(obj->getValue()));
    return ;
}
void ConvertToIntVisitor::Visit(StringValue *obj) {
    int64_t ret;
    sscanf(obj->getValue().c_str(), "%" PRId64, &ret);
    this->result = make_shared<IntValue>(ret);
    return ;
}
void ConvertToIntVisitor::Visit(ArrayValue *obj) {
    this->result = make_shared<IntValue>(obj->getSize());
    return ;
}

void ConvertToFloatVisitor::Visit(IntValue *obj) {
    this->result = make_shared<FloatValue>(obj->getValue());
    return ; 
}
void ConvertToFloatVisitor::Visit(FloatValue *obj) {
    this->result = make_shared<FloatValue>(obj->getValue());
    return ;
}
void ConvertToFloatVisitor::Visit(StringValue *obj) {
    double ret;
    sscanf(obj->getValue().c_str(), "%lf", &ret);
    this->result = make_shared<FloatValue>(ret);
    return ;
}
void ConvertToFloatVisitor::Visit(ArrayValue *obj) {
    this->result = make_shared<FloatValue>(obj->getSize());
    return ;
}
void ConvertToArrayVisitor::Visit(IntValue *obj) {
    shared_ptr<IValue> ret = make_shared<IntValue>(obj->getValue());
    this->result = make_shared<ArrayValue>();
    this->result->push_back(ret);
    return ;
}
void ConvertToArrayVisitor::Visit(FloatValue *obj) {
    shared_ptr<IValue> ret = make_shared<FloatValue>(obj->getValue());
    this->result = make_shared<ArrayValue>();
    this->result->push_back(ret);
    return ;
}
void ConvertToArrayVisitor::Visit(StringValue *obj) {
    shared_ptr<IValue> ret = make_shared<StringValue>(obj->getValue());
    this->result = make_shared<ArrayValue>();
    this->result->push_back(ret);
    return ;
}
void ConvertToArrayVisitor::Visit(ArrayValue *obj) {
    shared_ptr<ArrayValue> ret = make_shared<ArrayValue>(*obj);
    this->result = ret;
    return ;
}

void PrintValueVisitor::Visit(IntValue *obj) {
    printf("%" PRId64 "\n", obj->getValue());
    return ;
}
void PrintValueVisitor::Visit(FloatValue *obj) {
    printf("%lf\n", obj->getValue());
    return ;
}
void PrintValueVisitor::Visit(StringValue *obj) {
    printf("%s\n", obj->getValue().c_str());
    return ;
}
void PrintValueVisitor::Visit(ArrayValue *obj) {
    ConvertToStringVisitor vis;
    obj->Accept(&vis);
    printf("%s\n", vis.getResult()->getValue().c_str());
    return ;
}

} // end of namespace HL

