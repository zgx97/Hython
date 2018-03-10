#ifndef _HYTHON_UNIT_H
#define _HYTHON_UNIT_H

#include "hlLexer.h"
#include "hlParser.h"
#include <cassert>
#include <map>
#include <string>
#include <iostream>
#include <stdexcept>
#include "hython_type.h"

using std::shared_ptr;
using std::string;
using std::pair;

namespace HL {

class DFANodeFactory;
class IDFANode;

pANTLR3_BASE_TREE getChild(pANTLR3_BASE_TREE, unsigned);
const char* getText(pANTLR3_BASE_TREE tree);
string ConvertToCLString(const char *str);
IDFANode *ConnectAllDFAFromTree(
    IDFANode *, 
    pANTLR3_BASE_TREE, 
    shared_ptr<DFANodeFactory>, 
    pair<int, int> = {-1, -1}
);

template <typename T>
bool isTrue(T &&p) {
    return p && p->isTrue();
}

template <typename T>
bool isFalse(T &&p) {
    return !p || p->isFalse();
}

template <typename T>
shared_ptr<IValue> fetchNot(T &&p) {
    return isTrue(p) ? IValue::HLFalse : IValue::HLTrue;
}

template <typename T>
shared_ptr<IValue> fetchYes(T &&p) {
    return isTrue(p) ? IValue::HLTrue : IValue::HLFalse;
}

} // end of namespace HL
#endif
