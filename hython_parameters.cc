#include <stdio.h>
#include "hython_parameters.h"
#include "hython_debug.h"

using std::runtime_error;

namespace HL {

shared_ptr<IValue> Parameters::getVal(string name) {
    if (this->memory.find(name) != this->memory.end()) 
        return this->memory[name];
    if (this->next == nullptr) {
        throw runtime_error(name + " is not a varable!");
        return IValue::HLNull;
    }
    return this->next->getVal(name);
}

shared_ptr<IValue> Parameters::setVal(string name, shared_ptr<IValue> val) {
    if (this->memory.find(name) != this->memory.end()) {
        val->setName(name);
        this->memory[name] = val;
        return val;
    } else if (this->next == nullptr) {
        throw runtime_error(name + " is not a varable!");
        return IValue::HLNull;
    }
    return this->next->setVal(name, val);
}

bool Parameters::addVar(string name) {
    if (this->memory.find(name) == this->memory.end()) {
        this->memory[name] = IValue::HLNull;
        return 1;
    }
    throw runtime_error(name + " re-declared!");
    return 0;
}

} // end of namespace HL
