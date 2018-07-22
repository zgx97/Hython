
#include "hython_dfa.h"
#include "hython_chain.h"
#include "hython_debug.h"
#include "hython_visitor.h"
#include "hython_unit.h"
#include <cinttypes>
#include <stdexcept>

using std::runtime_error;

namespace HL {

void DFA::__initBlockBeginEnd() {
    this->begin = this->productor->getNewNode(IDFANode::Type::BlockBegin);
    this->end   = this->productor->getNewNode(IDFANode::Type::BlockEnd);
    dynamic_cast<BlockBeginDFANode *>(this->begin)->setCheckpoint(this->end);
    return ;    
}

void DFA::run() {
    // 创建开始的作用域
    shared_ptr<Parameters> param = make_shared<Parameters>();
    IDFANode *p = this->begin;
    while (p != nullptr) {
        p = p->forward(param);
    }
    return ;
}

// 该如何修改这里的代码使之能够去掉最歪层括号呢？
void DFA::exchange(pANTLR3_BASE_TREE tree) {
    printf("exchange start!\n");
    fflush(stdout);
    printf("tree point : %p\n", tree);
    fflush(stdout);
    pANTLR3_COMMON_TOKEN tok = tree->getToken(tree);
    // 如果当前节点没有类型则直接exchange孩子节点
    if (tok == NULL) {
        DFA child(this->productor);
        this->__initBlockBeginEnd();
        IDFANode *p = ConnectAllDFAFromTree(
            this->begin, tree, this->productor, {-1, -1}
        );
        p->addEdge(IDFAEdge::Type::AnyEdge, this->end);
        return;
    }
    switch (tok->type) {
        case 0 : 
        case BLOCK : {
            DFA child(this->productor);
            this->__initBlockBeginEnd();
            IDFANode *p = ConnectAllDFAFromTree(
                this->begin, tree, this->productor, {-1, -1}
            );
            p->addEdge(IDFAEdge::Type::AnyEdge, this->end);
        } break;
        case WHILE : {
            DFA cond_child(this->productor);
            DFA stmt_child(this->productor);
            this->__initBlockBeginEnd();
            cond_child.exchange(getChild(tree, 0));
            stmt_child.exchange(getChild(tree, 1));
            this->begin->addEdge(IDFAEdge::Type::AnyEdge, cond_child.begin);
            cond_child.end->addEdge(IDFAEdge::Type::YesEdge, stmt_child.begin);
            cond_child.end->addEdge(IDFAEdge::Type::NotEdge, this->end);
            stmt_child.end->addEdge(IDFAEdge::Type::AnyEdge, cond_child.begin);
            this->productor->clearBreakPointList(this->end);
            this->productor->clearContinuePointList(stmt_child.end);
        } break;
        case DOWHILE : {
            DFA cond_child(this->productor);
            DFA stmt_child(this->productor);
            this->__initBlockBeginEnd();
            cond_child.exchange(getChild(tree, 0));
            stmt_child.exchange(getChild(tree, 1));
            this->begin->addEdge(IDFAEdge::Type::AnyEdge, stmt_child.begin);
            stmt_child.end->addEdge(IDFAEdge::Type::AnyEdge, cond_child.begin);
            cond_child.end->addEdge(IDFAEdge::Type::YesEdge, stmt_child.begin);
            cond_child.end->addEdge(IDFAEdge::Type::NotEdge, this->end);
            this->productor->clearBreakPointList(this->end);
            this->productor->clearContinuePointList(stmt_child.end);
        } break;
        case FOR : {
            DFA init_child(this->productor);
            DFA cond_child(this->productor);
            DFA do_child(this->productor);
            DFA stmt_child(this->productor);
            this->__initBlockBeginEnd();
            init_child.exchange(getChild(tree, 0));
            cond_child.exchange(getChild(tree, 1));
            do_child.exchange(getChild(tree, 2));
            stmt_child.exchange(getChild(tree, 3));
            this->begin->addEdge(IDFAEdge::Type::AnyEdge, init_child.begin);
            init_child.end->addEdge(IDFAEdge::Type::AnyEdge, cond_child.begin);
            cond_child.end->addEdge(IDFAEdge::Type::YesEdge, stmt_child.begin);
            cond_child.end->addEdge(IDFAEdge::Type::NotEdge, this->end);
            stmt_child.end->addEdge(IDFAEdge::Type::AnyEdge, do_child.begin);
            do_child.end->addEdge(IDFAEdge::Type::AnyEdge, cond_child.begin);
            this->productor->clearBreakPointList(this->end);
            this->productor->clearContinuePointList(stmt_child.end);
        } break;
        case IF : {
            DFA cond_child(this->productor);
            DFA stmt_child(this->productor);
            DFA else_child(this->productor);
            this->__initBlockBeginEnd();
            cond_child.exchange(getChild(tree, 0));
            stmt_child.exchange(getChild(tree, 1));
            this->begin->addEdge(IDFAEdge::Type::AnyEdge, cond_child.begin);
            cond_child.end->addEdge(IDFAEdge::Type::YesEdge, stmt_child.begin);
            stmt_child.end->addEdge(IDFAEdge::Type::AnyEdge, this->end);
            if (tree->getChildCount(tree) == 3) {
                else_child.exchange(getChild(tree, 2));
                cond_child.end->addEdge(IDFAEdge::Type::NotEdge, else_child.begin);
                else_child.end->addEdge(IDFAEdge::Type::AnyEdge, this->end);
            } else {
                cond_child.end->addEdge(IDFAEdge::Type::NotEdge, this->end);
            }
        } break;
        case SWITCH : {
            DFA cond_child(this->productor);
            this->__initBlockBeginEnd();
            cond_child.exchange(getChild(tree, 0));
            this->begin->addEdge(IDFAEdge::Type::AnyEdge, cond_child.begin);
            cond_child.begin->addEdge(IDFAEdge::Type::AnyEdge, this->end);
            DFA child(this->productor);
            IDFANode *p = this->end;
            int k = tree->getChildCount(tree);
            for (int i = k - 1; i >= 1; i--) {
                child.exchange(getChild(tree, i));
                cond_child.begin->addEdge(child.suggestion_edge);
                child.end->addEdge(IDFAEdge::Type::AnyEdge, p);
                p = child.begin;
            }
            this->productor->clearBreakPointList(this->end);
        } break;
        case DEFAULT : {
            this->begin = this->productor->getNewNode(IDFANode::Type::OneEdge);
            this->suggestion_edge = make_shared<AnyEdge>(this->begin);
            this->end = ConnectAllDFAFromTree(
                this->begin, tree, this->productor, {0, -1}
            );
            this->productor->__breakPointList.push(this->end);
        } break;
        case CASE : {
            this->begin = this->productor->getNewNode(IDFANode::Type::OneEdge);
            shared_ptr<IValue> val = MasterChain::get()->valid(getChild(tree, 0), nullptr);
            this->suggestion_edge = make_shared<ValueEdge>(this->begin);
            this->suggestion_edge->setValue(val);
            this->end = ConnectAllDFAFromTree(
                this->begin, tree, this->productor, {1, -1}
            );
        } break;
        case BREAK : {
            this->begin = this->end = this->productor->getNewNode(IDFANode::Type::OneEdge, tree);
            this->productor->__breakPointList.push(this->end);
        } break;
        case CONTINUE : {
            this->begin = this->end = this->productor->getNewNode(IDFANode::Type::OneEdge, tree);
            this->productor->__continuePointList.push(this->end);
        } break;
        default : {
            this->begin = this->end = this->productor->getNewNode(IDFANode::Type::Master, tree);
        } break;
    }
    return ;
}

void DFANodeFactory::clearBreakPointList(IDFANode *node) {
    IDFANode *p;
    while (!(this->__breakPointList.empty())) {
        P("connect break point to %p", node);
        p = this->__breakPointList.top();
        P("Break Point : %p", p);
        p->clearEdges();
        p->addEdge(IDFAEdge::Type::AnyEdge, node);
        this->__breakPointList.pop();
    }
    return ;
}

void DFANodeFactory::clearContinuePointList(IDFANode *node) {
    IDFANode *p;
    while (!(this->__continuePointList.empty())) {
        p = this->__continuePointList.top();
        p->clearEdges();
        p->addEdge(IDFAEdge::Type::AnyEdge, node);
        this->__continuePointList.pop();
    }
    return ;
}

IDFANode *DFANodeFactory::getNewNode(IDFANode::Type type, pANTLR3_BASE_TREE tree) {
    shared_ptr<IDFANode> ret(nullptr);
    switch (type) {
        case IDFANode::Type::BlockBegin : {
            ret = make_shared<BlockBeginDFANode>();
        } break;
        case IDFANode::Type::BlockEnd : {
            ret = make_shared<BlockEndDFANode>();
        } break;
        case IDFANode::Type::Master : {
            ret = make_shared<MasterDFANode>(tree);
        } break;
        case IDFANode::Type::OneEdge : {
            ret = make_shared<OneEdgeDFANode>();
        } break;
        default :  
            throw runtime_error("Unknown DFA Node Type");
            break;
    }
    this->__storage.push_back(ret);
    return ret.get();
}

shared_ptr<IValue> MasterDFANode::getValue(shared_ptr<Parameters> &param) {
    P("get master node value tree = %p", this->__tree);
    if (!(this->__tree)) return IValue::HLNull;
    shared_ptr<IValue> temp_val = MasterChain::get()->valid(this->__tree, param);
    return temp_val;
}

void BlockBeginDFANode::beginForward(shared_ptr<Parameters> &param) {
    shared_ptr<Parameters> np = make_shared<Parameters>(param);
    np->checkpoint = this->__checkpoint;
    param = np;
    return ;
}

void BlockEndDFANode::beginForward(shared_ptr<Parameters> &param) {
    while (param && param->checkpoint != this) {
        param = param->next;
    }
    if (!param) {
        throw runtime_error("Block End and Parameters Don't Match");
    }
    param = param->next;
    return ;
}

void OneEdgeDFANode::addEdge(IDFAEdge::Type type, IDFANode *node) {
    if (this->__edges != nullptr) return ;
    this->IDFANode::addEdge(type, node);
    return ;
}

bool ValueEdge::valid(shared_ptr<IValue> &val) {
    if (!(this->__val.get())) return false;
    if (val->getType() != this->__val->getType()) return false;
    return HL::isTrue(this->__val->operator==(val.get()));
}

} // end of namespace HL
