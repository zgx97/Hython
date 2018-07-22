#include <cassert>
#include <map>
#include <string>
#include <iostream>
#include <stdexcept>
#include <memory>
#include "hython_dfa.h"
#include "hython_debug.h"
#include "hlLexer.h"
#include "hlParser.h"

using std::map;
using std::string;
using std::cout;
using std::shared_ptr;
using std::make_shared;
using std::runtime_error;

int main(int argc, char* argv[]) {
    pANTLR3_INPUT_STREAM input;
    phlLexer lex;
    pANTLR3_COMMON_TOKEN_STREAM tokens;
    phlParser parser;
    
    assert(argc > 1);

    input = antlr3FileStreamNew((pANTLR3_UINT8)argv[1],ANTLR3_ENC_8BIT);

    if (!input) {
        printf("can't open the program file : %s\n", argv[1]);
        exit(1);
    }
    lex = hlLexerNew(input);

    tokens = antlr3CommonTokenStreamSourceNew(ANTLR3_SIZE_HINT,
                                            TOKENSOURCE(lex));

    if (!tokens) {
        exit(1);
    }

    parser = hlParserNew(tokens);

    if (!parser) {
        exit(1);
    }
    hlParser_prog_return r = parser->prog(parser);
    pANTLR3_BASE_TREE tree = r.tree;
    if (!tree) {
        exit(1);
    }

    HL::DFA dfa;
    dfa.exchange(tree);

    dfa.run();

    parser->free(parser);
    tokens->free(tokens);
    lex->free(lex);
    input->close(input);
    return 0;
}
