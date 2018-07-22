#include <stdio.h>
#include "hython_chain.h"
#include "hython_master.h"
#include "hython_visitor.h"

namespace HL {

MasterChain *MasterChain::single = nullptr;

MasterChain::MasterChain() {
    // this->p = new ProgramMaster::IProgramFactory();
    // this->p->next = new IFMaster::IIFFactory();
    this->p = new ExprMaster::IExprFactory();
    this->p->next = new PrintMaster::IPrintFactory();
}

MasterChain::~MasterChain() {
    IFactory *next = this->p;
    while (next) {
        this->p = next->next;
        delete next;
        next = this->p;
    }
}
/*
 * MasterChain::valid
 *     抽象责任链+工厂：查看哪个工厂能够接受这棵抽象语法树
 *     根据作用域，解析ABST，获取相应的值
 */
shared_ptr<IValue> MasterChain::valid(pANTLR3_BASE_TREE tree, shared_ptr<Parameters> param) {
    IFactory *f = this->p;
    while (f) {
        if (f->valid(tree)) {
            shared_ptr<IMaster> m(f->creator(param));
            shared_ptr<IValue> ret = m->run(tree);
            ConvertToIntVisitor v;
            // 将结果存放到ret->result中
            ret->Accept(&v);
            // return v.result() ? 
            return ret;
        }
        f = f->next;
    }
    pANTLR3_COMMON_TOKEN tok = tree->getToken(tree);
    cout << "Unhandled token: #" << tok->type << '\n';
    throw runtime_error("There is no Master could take over The Tree!");
    return IValue::HLNull;
}

} // end of namespace HL
