#include <stdio.h>
#include "hython_unit.h"
#include "hython_debug.h"
#include "hython_dfa.h"

using std::runtime_error;
using std::pair;

namespace HL {

IDFANode *ConnectAllDFAFromTree(
    IDFANode *begin, 
    pANTLR3_BASE_TREE tree, 
    shared_ptr<DFANodeFactory> productor, 
    pair<int, int> indp
) {
    int b = 0, e = tree->getChildCount(tree);
    if (indp.first != -1) {
        b = indp.first;
    }
    if (indp.second != -1) {
        e = indp.second;
    }
    IDFANode *p = begin;
    DFA child(productor);
    for (int i = b; i < e; i++) {
        child.exchange(getChild(tree, i));
        p->addEdge(IDFAEdge::Type::AnyEdge, child.getBegin());
        p = child.getEnd();
    }
    return p;
}

pANTLR3_BASE_TREE getChild(pANTLR3_BASE_TREE tree, unsigned i) {
    assert(i < tree->getChildCount(tree));
    return (pANTLR3_BASE_TREE) tree->getChild(tree, i);
}

const char* getText(pANTLR3_BASE_TREE tree) {
    return (const char*) tree->getText(tree)->chars;
}

string ConvertToCLString(const char *str) {
    string ret = "";
    ++str;
    int i = 0, stat = 0;
    while (str[i] != '\"' || str[i + 1]) {
        switch (str[i]) {
            case '\\' : {
                ++i;
                switch (str[i]) {
                    case 't'  : ret += '\t'; break;
                    case 'n'  : ret += '\n'; break;
                    case '\\' : ret += '\\'; break;
                    case '\'' : ret += '\''; break;
                    case '\"' : ret += '\"'; break;
                    case 'f'  : ret += '\f'; break;
                    case 'r'  : ret += '\r'; break;
                    case 'b'  : ret += '\b'; break;
                    default : 
                        throw runtime_error("string error");
                        break;
                }
            } break;
            default :
                ret += str[i];
                break;
        }
        ++i;
    }
    return ret;
}

} // end of namespace HL
