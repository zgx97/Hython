#include "hython_type.h"
#include "hython_visitor.h"
#include "hython_unit.h"

using std::runtime_error;

namespace HL {

shared_ptr<IValue> StringValue::isEqual(IValue *obj) {
    ConvertToStringVisitor vis;
    obj->Accept(&vis);
    return (
        (this->getValue() == vis.getResult()->getValue()) ? 
        IValue::HLTrue : IValue::HLFalse
    );
}

shared_ptr<IValue> StringValue::isLittle(IValue *obj) {
    ConvertToStringVisitor vis;
    obj->Accept(&vis);
    return (
        (this->getValue() < vis.getResult()->getValue()) ? 
        IValue::HLTrue : IValue::HLFalse
    );
}

shared_ptr<IValue> StringValue::__operator_other(shared_ptr<IValue> &obj, int opr_type) {
    ConvertToStringVisitor vis;
    obj->Accept(&vis);

    string ret;
    switch (opr_type) {
        case PLUS: {
            ret = this->getValue() + vis.getResult()->getValue();
            vis.getResult()->setValue(ret);
            return vis.getResult();
        } break;
        default : throw runtime_error("unrecognized operator between string value"); break;
    }
    return IValue::HLNull;
}

shared_ptr<IValue> FloatValue::isEqual(IValue *obj) {
    ConvertToFloatVisitor vis;
    obj->Accept(&vis);
    return (
        (this->getValue() == vis.getResult()->getValue()) ? 
        IValue::HLTrue : IValue::HLFalse
    );
}

shared_ptr<IValue> FloatValue::isLittle(IValue *obj) {
    ConvertToFloatVisitor vis;
    obj->Accept(&vis);
    return (
        (this->getValue() < vis.getResult()->getValue()) ? 
        IValue::HLTrue : IValue::HLFalse
    );
}

shared_ptr<IValue> FloatValue::__operator_other(shared_ptr<IValue> &obj, int opr_type) {
    ConvertToFloatVisitor vis;
    obj->Accept(&vis);

    double ret_value;
    switch (opr_type) {
        case PLUS: ret_value = this->getValue() + vis.getResult()->getValue(); break;
        case MINUS: ret_value = this->getValue() - vis.getResult()->getValue(); break;
        case TIMES: ret_value = this->getValue() * vis.getResult()->getValue(); break;
        case DIV: ret_value = this->getValue() / vis.getResult()->getValue(); break;
        case MOD: throw runtime_error("illegal operator mod between float value"); break;
        default : throw runtime_error("unrecognized operator between float value"); break;
    }
    vis.getResult()->setValue(ret_value);
    return vis.getResult();
}

shared_ptr<IValue> IntValue::isEqual(IValue *obj) {
    ConvertToIntVisitor vis;
    obj->Accept(&vis);
    return (
        (this->getValue() == vis.getResult()->getValue()) ? 
        IValue::HLTrue : IValue::HLFalse
    );
}

shared_ptr<IValue> IntValue::isLittle(IValue *obj) {
    ConvertToIntVisitor vis;
    obj->Accept(&vis);
    return (
        (this->getValue() < vis.getResult()->getValue()) ? 
        IValue::HLTrue : IValue::HLFalse
    );
}

shared_ptr<IValue> IntValue::__operator_other(shared_ptr<IValue> &obj, int opr_type) {
    ConvertToIntVisitor vis;
    obj->Accept(&vis);
    
    int64_t ret_value;
    switch (opr_type) {
        case PLUS: ret_value = this->getValue() + vis.getResult()->getValue(); break;
        case MINUS: ret_value = this->getValue() - vis.getResult()->getValue(); break;
        case TIMES: ret_value = this->getValue() * vis.getResult()->getValue(); break;
        case DIV: ret_value = this->getValue() / vis.getResult()->getValue(); break;
        case MOD: ret_value = this->getValue() % vis.getResult()->getValue(); break;
        default : throw runtime_error("unrecognized operator between int value"); break;
    }
    vis.getResult()->setValue(ret_value);
    return vis.getResult();
}

ArrayValue::ArrayValue(const ArrayValue &a) : IValue(IValue::Type::Array) {
    for (auto x : a.arr) {
        this->arr.push_back(x);
    }
    return ;
}

shared_ptr<IValue> ArrayValue::isEqual(IValue *obj) {
    ConvertToArrayVisitor vis;
    obj->Accept(&vis);
    ArrayValue *aobj = vis.getResult().get();
    if (this->getSize() != aobj->getSize()) return IValue::HLFalse;
    for (int i = 0; i < this->getSize(); i++) {
        if (this->getValue(i)->operator==(aobj->getValue(i).get())) continue;
        return IValue::HLFalse;
    }
    return IValue::HLTrue;
}

shared_ptr<IValue> ArrayValue::isLittle(IValue *obj) {
    ConvertToArrayVisitor vis;
    obj->Accept(&vis);
    ArrayValue *aobj = vis.getResult().get();
    for (int i = 0; i < aobj->getSize() || i < this->getSize(); i++) {
        if (this->getValue(i)->operator==(aobj->getValue(i).get())) continue;
        return  this->getValue(i)->operator<(aobj->getValue(i).get());
    }
    return (this->getSize() < aobj->getSize() ? IValue::HLTrue : IValue::HLFalse);
}

shared_ptr<IValue> ArrayValue::__operator_other(shared_ptr<IValue> &obj, int opr_type) {
    ConvertToArrayVisitor vis;
    obj->Accept(&vis);
    
    switch (opr_type) {
        case PLUS: {
            auto iter = this->arr.rbegin();
            while (iter != this->arr.rend()) {
                vis.getResult()->push_front(*iter);
                iter++;
            }
        } break;
        default : throw runtime_error("unrecognized operator between int value"); break;
    }
    return vis.getResult();
}
    
} // end of namespace HL
