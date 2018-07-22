#include <stdio.h>
#include "hython_master.h"
#include "hython_unit.h"
#include "hython_chain.h"
#include "hython_type.h"
#include "hython_visitor.h"

using std::runtime_error;
using std::make_shared;

namespace HL{

bool ProgramMaster::IProgramFactory::valid(pANTLR3_BASE_TREE tree) {
    pANTLR3_COMMON_TOKEN tok = tree->getToken(tree);
    if (!tok) return true;
    switch (tok->type) {
        case WHILE:
        case DOWHILE:
        case FOR:
        case BLOCK:
            return true;
    }
    return false;
}

IMaster *ProgramMaster::IProgramFactory::creator(shared_ptr<Parameters> param) {
    return new ProgramMaster(param);
}

shared_ptr<IValue> ProgramMaster::run(pANTLR3_BASE_TREE tree) {
    // 增加作用域
    this->param = make_shared<Parameters>(this->param);
    pANTLR3_COMMON_TOKEN tok = tree->getToken(tree);
    if (!tok) {
        int k = tree->getChildCount(tree);
        for(int i = 0; i < k; i++) {
            MasterChain::get()->valid(getChild(tree, i), this->param);
        }
    } else {
        switch(tok->type) {
            case BLOCK: {
                int k = tree->getChildCount(tree);
                for (int i = 0; i < k; i++) {
                    MasterChain::get()->valid(getChild(tree, i), this->param);
                }
            } break;
            case WHILE: {
                // Q：为什么要得到while token抽象语法树第0个孩子的值？
                // A：因为在语法设计中，while的第0个孩子是条件判断表达式，第一个孩子是循环体
                while (isTrue(MasterChain::get()->valid(getChild(tree, 0), this->param))) {
                    MasterChain::get()->valid(getChild(tree, 1), this->param);
                }
            } break;
            case DOWHILE: {
                do {
                    MasterChain::get()->valid(getChild(tree, 1), this->param);
                } while (isTrue(MasterChain::get()->valid(getChild(tree, 0), this->param)));
            } break;
            case FOR: {
                MasterChain::get()->valid(getChild(tree, 0), this->param);
                while (isTrue(MasterChain::get()->valid(getChild(tree, 1), this->param))) {
                    MasterChain::get()->valid(getChild(tree, 3), this->param);
                    MasterChain::get()->valid(getChild(tree, 2), this->param);
                }
            } break;
            default: {
                cout << "Unhandled token: #" << tok->type << '\n';
                break;
            }
        }
    }
    // 删除作用域
    this->param = this->param->next;
    return IValue::HLNull;
}

bool IFMaster::IIFFactory::valid(pANTLR3_BASE_TREE tree) {
    pANTLR3_COMMON_TOKEN tok = tree->getToken(tree);
    if (!tok) return false;
    switch (tok->type) {
        case IF:
        case ELSE:
            return true;
    }
    return false;
}

IMaster *IFMaster::IIFFactory::creator(shared_ptr<Parameters> param) {
    return new IFMaster(param);
}

// MasterChain::get()->valid(getChild(tree, 0), this->param);
// 解析作用域中的值
shared_ptr<IValue> IFMaster::run(pANTLR3_BASE_TREE tree) {
    pANTLR3_COMMON_TOKEN tok = tree->getToken(tree);
    switch (tok->type) {
        case IF: {
            shared_ptr<IValue> ret = MasterChain::get()->valid(getChild(tree, 0), this->param);
            if (isTrue(ret)) {
                return MasterChain::get()->valid(getChild(tree, 1), this->param); 
            } else if (tree->getChildCount(tree) == 3) {
                return MasterChain::get()->valid(getChild(tree, 2), this->param);
            }
        } break;
        case ELSE: {
            return MasterChain::get()->valid(getChild(tree, 0), this->param);
        } break;
        default :
            cout << "Unhandled token: #" << tok->type << '\n';
            break;
    }
    return IValue::HLNull;
}

bool ExprMaster::IExprFactory::valid(pANTLR3_BASE_TREE tree) {
    pANTLR3_COMMON_TOKEN tok = tree->getToken(tree);
    if (!tok) return false;
    switch (tok->type) {
        case DEF:
        case INT:
        case STRING:
        case ARRAY:
        case FLOAT:
        case PLUS:
        case MINUS:
        case TIMES:
        case AND:
        case ASSIGN:
        case EQ:
        case GE:
        case GT:
        case LE:
        case LITTLE: 
        case NE:
        case OR:
        case ID:
        case DIV:
        case MOD:
            return true;
    }
    return false;
}

IMaster *ExprMaster::IExprFactory::creator(shared_ptr<Parameters> param) {
    return new ExprMaster(param);
}

shared_ptr<IValue> ExprMaster::run(pANTLR3_BASE_TREE tree) {
    pANTLR3_COMMON_TOKEN tok = tree->getToken(tree);
    switch (tok->type) {
        case DEF: {
            int k = tree->getChildCount(tree);
            shared_ptr<IValue> val(nullptr);
            for (int i = 0; i < k; i++) {
                string var(getText(getChild(tree, i)));
                this->param->addVar(var);
                if (tree->getChildCount(getChild(tree, i))) {
                    val = MasterChain::get()->valid(getChild(getChild(tree, i), 0), this->param);
                    this->param->setVal(var, val);
                }
            }
            return IValue::HLNull;
        } break;
        case INT: {
            const char *s = getText(tree);
            int64_t num = atoi(s);
            shared_ptr<IntValue> p = make_shared<IntValue>();
            p->setValue(num);
            return p;
        } break;
        case FLOAT: {
            string val(getText(tree));
            shared_ptr<FloatValue> p = make_shared<FloatValue>();
            p->setValue(atof(val.c_str()));
            return p;
        } break;
        case STRING: {
            string val(getText(tree));
            shared_ptr<StringValue> p = make_shared<StringValue>();
            val = ConvertToCLString(val.c_str());
            p->setValue(val);
            return p;
        } break;
        case ARRAY : {
            int k = tree->getChildCount(tree);
            shared_ptr<ArrayValue> p = make_shared<ArrayValue>();
            for (int i = 0; i < k; i++) {
                shared_ptr<IValue> val = MasterChain::get()->valid(getChild(tree, i), this->param);
                p->push_back(val);
            }
            return p;
        } break;
        case ID: {
            string var(getText(tree));
            return this->param->getVal(var);
        } break;
        case ASSIGN: {
            string var(getText(getChild(tree, 0)));
            shared_ptr<IValue> val = MasterChain::get()->valid(getChild(tree, 1), this->param);
            this->param->setVal(var, val);
            return val;
        } break;
        case PLUS:
        case MINUS: 
        case TIMES: 
        case DIV: 
        case MOD: 
        case EQ: 
        case GE: 
        case GT: 
        case LE: 
        case LITTLE: 
        case NE: 
        case AND: 
        case OR: {
            shared_ptr<IValue> a = MasterChain::get()->valid(getChild(tree, 0), this->param);
            shared_ptr<IValue> b = MasterChain::get()->valid(getChild(tree, 1), this->param);
            shared_ptr<IValue> ret = a->operator_all(b, tok->type);
            return ret;
        } break;
        default :
            cout << "Unhandled token: #" << tok->type << '\n';
            throw runtime_error("unhandled token : ExprMaster");
            break;
    }
    return IValue::HLNull;
}

bool PrintMaster::IPrintFactory::valid(pANTLR3_BASE_TREE tree) {
    pANTLR3_COMMON_TOKEN tok = tree->getToken(tree);
    if (!tok) return false;
    switch (tok->type) {
        case PRINT:
            return true;
    }
    return false;
}

IMaster *PrintMaster::IPrintFactory::creator(shared_ptr<Parameters> param) {
    return new PrintMaster(param);
}

shared_ptr<IValue> PrintMaster::run(pANTLR3_BASE_TREE tree) {
    pANTLR3_COMMON_TOKEN tok = tree->getToken(tree);
    switch (tok->type) {
        case PRINT: {
            int k = tree->getChildCount(tree);
            int64_t ret = 0;
            for (int i = 0; i < k; i++) {
                shared_ptr<IValue> val = MasterChain::get()->valid(getChild(tree, i), this->param);
                ConvertToStringVisitor visitor;
                string result;
                if (val) {
                    val->Accept(&visitor);
                    result = visitor.getResult()->getValue();
                } else {
                    result = "NULL";
                }
                ret += printf("%s", result.c_str());
                if (i < k - 1) printf(" ");
            }
            printf("\n");
            shared_ptr<IntValue> p = make_shared<IntValue>();
            p->setValue(ret);
            return p;
        } break;
        default:
            cout << "Unhandled token: #" << tok->type << '\n';
            break;
    }
    return IValue::HLNull;
}

} // end of namespace HL
