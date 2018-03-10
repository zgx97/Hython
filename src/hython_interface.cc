#include "hython_type.h"
#include "hython_unit.h"
#include "hython_interface.h"
#include "hython_type.h"
#include "hython_debug.h"
#include "hython_dfa.h"
#include "hython_visitor.h"

using std::runtime_error;

namespace HL {

void IDFANode::addEdge(shared_ptr<IDFAEdge> edge) {
    edge->setNext(this->__edges);
    this->__edges = edge;
    return ;
}

void IDFANode::addEdge(IDFAEdge::Type type, IDFANode *node) {
    shared_ptr<IDFAEdge> edge;
    switch (type) {
        case IDFAEdge::Type::AnyEdge :
            edge = make_shared<AnyEdge>(node);
            break;
        case IDFAEdge::Type::YesEdge :
            edge = make_shared<YesEdge>(node);
            break;
        case IDFAEdge::Type::NotEdge :
            edge = make_shared<NotEdge>(node);
            break;
        case IDFAEdge::Type::ValueEdge :
            edge = make_shared<ValueEdge>(node);
            break;
        default :
            throw runtime_error("Unknown DFA Edge Type");
            break;
    }
    edge->setNext(this->__edges); 
    this->__edges = edge;
    return ;
}

IDFANode *IDFANode::forward(shared_ptr<Parameters> &param) {
    this->beginForward(param);
    shared_ptr<IValue> val = this->getValue(param);
    if (this->__edges) {
        return this->__edges->forward(val);
    }
    return nullptr;
}

shared_ptr<IValue> IDFANode::getValue(shared_ptr<Parameters> &param) {
    return IValue::HLNull;
}

IDFANode *IDFAEdge::forward(shared_ptr<IValue> &val) {
    if (this->valid(val)) {
        return this->getNode();
    } else if (this->__next) {
        return this->__next->forward(val);
    } else {
        throw runtime_error("DFA Error, could not forward to next node");
    }
    return nullptr;
}

const shared_ptr<IValue> IValue::HLNull(new StringValue());
const shared_ptr<IValue> IValue::HLTrue(new IntValue(1));
const shared_ptr<IValue> IValue::HLFalse(new IntValue(0));

shared_ptr<IValue> IValue::operator_all(shared_ptr<IValue> &obj, int opr_type) {
    if (!obj) obj = IValue::HLNull;
    switch (opr_type) {
        case    AND : return this->operator&&(obj.get());
        case     OR : return this->operator||(obj.get());
        case     EQ : return this->operator==(obj.get());
        case     GE : return this->operator>=(obj.get());
        case     GT : return this->operator>(obj.get());
        case     LE : return this->operator<=(obj.get());
        case LITTLE : return this->operator<(obj.get());
        case     NE : return this->operator!=(obj.get());
        default :
            break;
    }
    if (!(obj->gt(this))) return this->__operator_other(obj, opr_type);
    switch (obj->getType()) {
        case IValue::Type::Int : {
            ConvertToIntVisitor vis;
            this->Accept(&vis);
            return vis.getResult()->__operator_other(obj, opr_type);
        } break;
        case IValue::Type::Float : {
            ConvertToFloatVisitor vis;
            this->Accept(&vis);
            return vis.getResult()->__operator_other(obj, opr_type);
        } break;
        case IValue::Type::String : {
            ConvertToStringVisitor vis;
            this->Accept(&vis);
            return vis.getResult()->__operator_other(obj, opr_type);
        } break;
        case IValue::Type::Array : {
            ConvertToArrayVisitor vis;
            this->Accept(&vis);
            return vis.getResult()->__operator_other(obj, opr_type);
        } break;
        default :
            throw runtime_error("Unkonwn Data type!");
    }
    return IValue::HLNull;
}

shared_ptr<IValue> IValue::operator==(IValue *obj) {
    if (obj->gt(this)) {
        return obj->operator==(this);
    }
    return this->isEqual(obj);
}
shared_ptr<IValue> IValue::operator<(IValue *obj) {
    if (obj->gt(this)) {
        return obj->operator>(this);
    }
    return this->isLittle(obj);
}

shared_ptr<IValue> IValue::operator||(IValue *obj) {
    return ((HL::isTrue(this) || HL::isTrue(obj)) ? IValue::HLTrue : IValue::HLFalse);
}

shared_ptr<IValue> IValue::operator&&(IValue *obj) {
    return ((HL::isTrue(this) && HL::isTrue(obj)) ? IValue::HLTrue : IValue::HLFalse);
}

shared_ptr<IValue> IValue::operator>(IValue *obj) {
    return fetchNot(this->IValue::operator<(obj)->operator||(this->IValue::operator==(obj).get()));
}

shared_ptr<IValue> IValue::operator!=(IValue *obj) {
    return fetchNot(this->IValue::operator==(obj));
}

shared_ptr<IValue> IValue::operator>=(IValue *obj) {
    return fetchNot(this->IValue::operator<(obj));
}

shared_ptr<IValue> IValue::operator<=(IValue *obj) {
    return fetchNot(this->IValue::operator>(obj));
}

} // end of namespace HL
