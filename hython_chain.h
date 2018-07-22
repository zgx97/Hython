#ifndef _HYTHON_CHAIN_H
#define _HYTHON_CHAIN_H

#include "hlLexer.h"
#include "hlParser.h"
#include <cassert>
#include <map>
#include <string>
#include <iostream>
#include <stdexcept>
#include "hython_parameters.h"
#include "hython_interface.h"

using std::map;
using std::string;
using std::cout;
using std::runtime_error;

namespace HL {

class MasterChain {
public :
    static MasterChain *get() {
        if (MasterChain::single) return MasterChain::single;
        MasterChain::single = new MasterChain();
        return MasterChain::single;
    }
    static void destroy() {
        if (MasterChain::single == nullptr) return ;
        MasterChain::get()->~MasterChain();
        MasterChain::single = nullptr;
    }
    shared_ptr<IValue> valid(pANTLR3_BASE_TREE, shared_ptr<Parameters> );
private:
    static MasterChain *single;
    MasterChain();
    ~MasterChain();
    IFactory *p;
};

} // end of namespace HL
#endif
