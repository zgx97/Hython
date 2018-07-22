/** \file
 *  This C header file was generated by $ANTLR version 3.4
 *
 *     -  From the grammar source file : ./hl.g
 *     -                            On : 2018-07-22 16:32:03
 *     -                 for the lexer : hlLexerLexer
 *
 * Editing it, at least manually, is not wise.
 *
 * C language generator and runtime by Jim Idle, jimi|hereisanat|idle|dotgoeshere|ws.
 *
 *
 * The lexer 
hlLexer

has the callable functions (rules) shown below,
 * which will invoke the code for the associated rule in the source grammar
 * assuming that the input stream is pointing to a token/text stream that could begin
 * this rule.
 *
 * For instance if you call the first (topmost) rule in a parser grammar, you will
 * get the results of a full parse, but calling a rule half way through the grammar will
 * allow you to pass part of a full token stream to the parser, such as for syntax checking
 * in editors and so on.
 *
 * The parser entry points are called indirectly (by function pointer to function) via
 * a parser context typedef phlLexer, which is returned from a call to hlLexerNew().
 *
 * As this is a generated lexer, it is unlikely you will call it 'manually'. However
 * the methods are provided anyway.
 *
 * The methods in phlLexer are  as follows:
 *
 *  - 
 void
      phlLexer->T__45(phlLexer)
 *  - 
 void
      phlLexer->T__46(phlLexer)
 *  - 
 void
      phlLexer->T__47(phlLexer)
 *  - 
 void
      phlLexer->T__48(phlLexer)
 *  - 
 void
      phlLexer->T__49(phlLexer)
 *  - 
 void
      phlLexer->T__50(phlLexer)
 *  - 
 void
      phlLexer->T__51(phlLexer)
 *  - 
 void
      phlLexer->T__52(phlLexer)
 *  - 
 void
      phlLexer->MOD(phlLexer)
 *  - 
 void
      phlLexer->DIV(phlLexer)
 *  - 
 void
      phlLexer->BREAK(phlLexer)
 *  - 
 void
      phlLexer->CONTINUE(phlLexer)
 *  - 
 void
      phlLexer->SWITCH(phlLexer)
 *  - 
 void
      phlLexer->CASE(phlLexer)
 *  - 
 void
      phlLexer->DEFAULT(phlLexer)
 *  - 
 void
      phlLexer->ARRAY(phlLexer)
 *  - 
 void
      phlLexer->DO(phlLexer)
 *  - 
 void
      phlLexer->DOWHILE(phlLexer)
 *  - 
 void
      phlLexer->WHILE(phlLexer)
 *  - 
 void
      phlLexer->FOR(phlLexer)
 *  - 
 void
      phlLexer->PRINT(phlLexer)
 *  - 
 void
      phlLexer->IF(phlLexer)
 *  - 
 void
      phlLexer->ELSE(phlLexer)
 *  - 
 void
      phlLexer->OR(phlLexer)
 *  - 
 void
      phlLexer->AND(phlLexer)
 *  - 
 void
      phlLexer->GE(phlLexer)
 *  - 
 void
      phlLexer->NE(phlLexer)
 *  - 
 void
      phlLexer->LITTLE(phlLexer)
 *  - 
 void
      phlLexer->LE(phlLexer)
 *  - 
 void
      phlLexer->GT(phlLexer)
 *  - 
 void
      phlLexer->EQ(phlLexer)
 *  - 
 void
      phlLexer->PLUS(phlLexer)
 *  - 
 void
      phlLexer->MINUS(phlLexer)
 *  - 
 void
      phlLexer->TIMES(phlLexer)
 *  - 
 void
      phlLexer->DOT(phlLexer)
 *  - 
 void
      phlLexer->ASSIGN(phlLexer)
 *  - 
 void
      phlLexer->BLOCK(phlLexer)
 *  - 
 void
      phlLexer->DEF(phlLexer)
 *  - 
 void
      phlLexer->INT(phlLexer)
 *  - 
 void
      phlLexer->ID(phlLexer)
 *  - 
 void
      phlLexer->FLOAT(phlLexer)
 *  - 
 void
      phlLexer->COMMENT(phlLexer)
 *  - 
 void
      phlLexer->WS(phlLexer)
 *  - 
 void
      phlLexer->STRING(phlLexer)
 *  - 
 void
      phlLexer->EXPONENT(phlLexer)
 *  - 
 void
      phlLexer->HEX_DIGIT(phlLexer)
 *  - 
 void
      phlLexer->ESC_SEQ(phlLexer)
 *  - 
 void
      phlLexer->OCTAL_ESC(phlLexer)
 *  - 
 void
      phlLexer->UNICODE_ESC(phlLexer)
 *  - 
 void
      phlLexer->Tokens(phlLexer)
 *
 * The return type for any particular rule is of course determined by the source
 * grammar file.
 */
// [The "BSD license"]
// Copyright (c) 2005-2009 Jim Idle, Temporal Wave LLC
// http://www.temporal-wave.com
// http://www.linkedin.com/in/jimidle
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
// 1. Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
// 3. The name of the author may not be used to endorse or promote products
//    derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
// IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
// OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
// IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
// NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
// THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef	_hlLexer_H
#define _hlLexer_H
/* =============================================================================
 * Standard antlr3 C runtime definitions
 */
#include    <antlr3.h>

/* End of standard antlr 3 runtime definitions
 * =============================================================================
 */

#ifdef __cplusplus
extern "C" {
#endif

// Forward declare the context typedef so that we can use it before it is
// properly defined. Delegators and delegates (from import statements) are
// interdependent and their context structures contain pointers to each other
// C only allows such things to be declared if you pre-declare the typedef.
//
typedef struct hlLexer_Ctx_struct hlLexer, * phlLexer;



#ifdef	ANTLR3_WINDOWS
// Disable: Unreferenced parameter,							- Rules with parameters that are not used
//          constant conditional,							- ANTLR realizes that a prediction is always true (synpred usually)
//          initialized but unused variable					- tree rewrite variables declared but not needed
//          Unreferenced local variable						- lexer rule declares but does not always use _type
//          potentially unitialized variable used			- retval always returned from a rule
//			unreferenced local function has been removed	- susually getTokenNames or freeScope, they can go without warnigns
//
// These are only really displayed at warning level /W4 but that is the code ideal I am aiming at
// and the codegen must generate some of these warnings by necessity, apart from 4100, which is
// usually generated when a parser rule is given a parameter that it does not use. Mostly though
// this is a matter of orthogonality hence I disable that one.
//
#pragma warning( disable : 4100 )
#pragma warning( disable : 4101 )
#pragma warning( disable : 4127 )
#pragma warning( disable : 4189 )
#pragma warning( disable : 4505 )
#pragma warning( disable : 4701 )
#endif

/** Context tracking structure for 
hlLexer

 */
struct hlLexer_Ctx_struct
{
    /** Built in ANTLR3 context tracker contains all the generic elements
     *  required for context tracking.
     */
    pANTLR3_LEXER    pLexer;

     void
     (*mT__45)	(struct hlLexer_Ctx_struct * ctx);

     void
     (*mT__46)	(struct hlLexer_Ctx_struct * ctx);

     void
     (*mT__47)	(struct hlLexer_Ctx_struct * ctx);

     void
     (*mT__48)	(struct hlLexer_Ctx_struct * ctx);

     void
     (*mT__49)	(struct hlLexer_Ctx_struct * ctx);

     void
     (*mT__50)	(struct hlLexer_Ctx_struct * ctx);

     void
     (*mT__51)	(struct hlLexer_Ctx_struct * ctx);

     void
     (*mT__52)	(struct hlLexer_Ctx_struct * ctx);

     void
     (*mMOD)	(struct hlLexer_Ctx_struct * ctx);

     void
     (*mDIV)	(struct hlLexer_Ctx_struct * ctx);

     void
     (*mBREAK)	(struct hlLexer_Ctx_struct * ctx);

     void
     (*mCONTINUE)	(struct hlLexer_Ctx_struct * ctx);

     void
     (*mSWITCH)	(struct hlLexer_Ctx_struct * ctx);

     void
     (*mCASE)	(struct hlLexer_Ctx_struct * ctx);

     void
     (*mDEFAULT)	(struct hlLexer_Ctx_struct * ctx);

     void
     (*mARRAY)	(struct hlLexer_Ctx_struct * ctx);

     void
     (*mDO)	(struct hlLexer_Ctx_struct * ctx);

     void
     (*mDOWHILE)	(struct hlLexer_Ctx_struct * ctx);

     void
     (*mWHILE)	(struct hlLexer_Ctx_struct * ctx);

     void
     (*mFOR)	(struct hlLexer_Ctx_struct * ctx);

     void
     (*mPRINT)	(struct hlLexer_Ctx_struct * ctx);

     void
     (*mIF)	(struct hlLexer_Ctx_struct * ctx);

     void
     (*mELSE)	(struct hlLexer_Ctx_struct * ctx);

     void
     (*mOR)	(struct hlLexer_Ctx_struct * ctx);

     void
     (*mAND)	(struct hlLexer_Ctx_struct * ctx);

     void
     (*mGE)	(struct hlLexer_Ctx_struct * ctx);

     void
     (*mNE)	(struct hlLexer_Ctx_struct * ctx);

     void
     (*mLITTLE)	(struct hlLexer_Ctx_struct * ctx);

     void
     (*mLE)	(struct hlLexer_Ctx_struct * ctx);

     void
     (*mGT)	(struct hlLexer_Ctx_struct * ctx);

     void
     (*mEQ)	(struct hlLexer_Ctx_struct * ctx);

     void
     (*mPLUS)	(struct hlLexer_Ctx_struct * ctx);

     void
     (*mMINUS)	(struct hlLexer_Ctx_struct * ctx);

     void
     (*mTIMES)	(struct hlLexer_Ctx_struct * ctx);

     void
     (*mDOT)	(struct hlLexer_Ctx_struct * ctx);

     void
     (*mASSIGN)	(struct hlLexer_Ctx_struct * ctx);

     void
     (*mBLOCK)	(struct hlLexer_Ctx_struct * ctx);

     void
     (*mDEF)	(struct hlLexer_Ctx_struct * ctx);

     void
     (*mINT)	(struct hlLexer_Ctx_struct * ctx);

     void
     (*mID)	(struct hlLexer_Ctx_struct * ctx);

     void
     (*mFLOAT)	(struct hlLexer_Ctx_struct * ctx);

     void
     (*mCOMMENT)	(struct hlLexer_Ctx_struct * ctx);

     void
     (*mWS)	(struct hlLexer_Ctx_struct * ctx);

     void
     (*mSTRING)	(struct hlLexer_Ctx_struct * ctx);

     void
     (*mEXPONENT)	(struct hlLexer_Ctx_struct * ctx);

     void
     (*mHEX_DIGIT)	(struct hlLexer_Ctx_struct * ctx);

     void
     (*mESC_SEQ)	(struct hlLexer_Ctx_struct * ctx);

     void
     (*mOCTAL_ESC)	(struct hlLexer_Ctx_struct * ctx);

     void
     (*mUNICODE_ESC)	(struct hlLexer_Ctx_struct * ctx);

     void
     (*mTokens)	(struct hlLexer_Ctx_struct * ctx);
    const char * (*getGrammarFileName)();
    void            (*reset)  (struct hlLexer_Ctx_struct * ctx);
    void	    (*free)   (struct hlLexer_Ctx_struct * ctx);
};

// Function protoypes for the constructor functions that external translation units
// such as delegators and delegates may wish to call.
//
ANTLR3_API phlLexer hlLexerNew         (
pANTLR3_INPUT_STREAM
 instream);
ANTLR3_API phlLexer hlLexerNewSSD      (
pANTLR3_INPUT_STREAM
 instream, pANTLR3_RECOGNIZER_SHARED_STATE state);

/** Symbolic definitions of all the tokens that the 
lexer
 will work with.
 * \{
 *
 * Antlr will define EOF, but we can't use that as it it is too common in
 * in C header files and that would be confusing. There is no way to filter this out at the moment
 * so we just undef it here for now. That isn't the value we get back from C recognizers
 * anyway. We are looking for ANTLR3_TOKEN_EOF.
 */
#ifdef	EOF
#undef	EOF
#endif
#ifdef	Tokens
#undef	Tokens
#endif
#define EOF      -1
#define T__45      45
#define T__46      46
#define T__47      47
#define T__48      48
#define T__49      49
#define T__50      50
#define T__51      51
#define T__52      52
#define AND      4
#define ARRAY      5
#define ASSIGN      6
#define BLOCK      7
#define BREAK      8
#define CASE      9
#define COMMENT      10
#define CONTINUE      11
#define DEF      12
#define DEFAULT      13
#define DIV      14
#define DO      15
#define DOT      16
#define DOWHILE      17
#define ELSE      18
#define EQ      19
#define ESC_SEQ      20
#define EXPONENT      21
#define FLOAT      22
#define FOR      23
#define GE      24
#define GT      25
#define HEX_DIGIT      26
#define ID      27
#define IF      28
#define INT      29
#define LE      30
#define LITTLE      31
#define MINUS      32
#define MOD      33
#define NE      34
#define OCTAL_ESC      35
#define OR      36
#define PLUS      37
#define PRINT      38
#define STRING      39
#define SWITCH      40
#define TIMES      41
#define UNICODE_ESC      42
#define WHILE      43
#define WS      44
#ifdef	EOF
#undef	EOF
#define	EOF	ANTLR3_TOKEN_EOF
#endif

#ifndef TOKENSOURCE
#define TOKENSOURCE(lxr) lxr->pLexer->rec->state->tokSource
#endif

/* End of token definitions for hlLexer
 * =============================================================================
 */
/** } */

#ifdef __cplusplus
}
#endif

#endif

/* END - Note:Keep extra line feed to satisfy UNIX systems */
