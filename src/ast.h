#ifndef __AST_H__
#define __AST_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "llvm-c/Core.h"
#include "hash.h"

#define OK   1
#define FAIL -1

#define ALLOC(V, T)  T* V = (T*)calloc(1, sizeof(T))
#define PARSE(R, F) R = F(context); if ( R == NULL ) return NULL
#define PARSE_ELSE(R, F) R = F(context); if ( R == NULL )

#define EXPECT(x)     if ( matchLiteral(context, x) == false ) return NULL
#define IF_MATCH(x)   if ( matchLiteral(context, x) == true )

/* #define OP_NOP 0 */
/* #define OP_AND 1 */
/* #define OP_OR  2 */
/* #define OP_XOR 3 */
/* #define OP_EQ  4 */
/* #define OP_NE  5 */
/* #define OP_GT  6 */
/* #define OP_LT  7 */
/* #define OP_GE  8 */
/* #define OP_LE  9 */
/* #define OP_SHR 10 */
/* #define OP_SHL 11 */
/* #define OP_POW 12 */
/* #define OP_ADD 13 */
/* #define OP_SUB 14 */
/* #define OP_MUL 15 */
/* #define OP_DIV 16 */
/* #define OP_REM 17 */
/* #define OP_DVT 18  //divisibility test */
/* #define OP_NOT 19 */
/* #define OP_NEG 20 */
/* #define OP_DOT 21 */
/* #define OP_BRC 22  //braces a[1] */
/* #define OP_CAL 23  //function call */

typedef struct
{
    char* input_file_path;
    char  input_file_name[1024];
    FILE* input_file;
    int   debug_mode;
    char  output_file_path[1024];

    char llvmir_dir[1024];
    char llvmir_file_path[1024];

    LLVMModuleRef module;
    LLVMBuilderRef builder;
    //This is a map of non-function bindings defined at module level
    /* hashtable_t* module_value_bindings; */
    //List of bindings defined inside current function
    hashtable_t* function_bindings;

} Context;


typedef struct Binding Binding;
typedef struct Expression Expression;
typedef struct ExpressionNode ExpressionNode;
typedef struct BindingList Module;
typedef struct BindingList FunctionDecl;

typedef struct BindingList
{
    Binding* first_binding, *last_binding;
} BindingList;

typedef struct Binding
{
    char lhs[32];

    //true, if this is a binding inside a function_decl and is prefixed with `::`
    bool is_return;

    //A binding can be either an expression or a function declaration
    FunctionDecl* function_decl;
    Expression* expression;

    struct Binding* next;
} Binding;

typedef struct Expression
{
    ExpressionNode *first_node, *last_node;
} Expression;

//TODO: rename left/right to open/cose
typedef enum
{
    NA,
    INT_LITERAL,
    IDENTIFIER,
    LEFT_PAREN,
    RIGHT_PAREN,
    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DIV,
    OP_REM,
    OP_DVT,
    LEFT_BRACE,
    RIGHT_BRACE,
    OP_COMMA,
    COMMA,
    //TODO: rename to fn_call
    OP_FUNCTION
} TokenKind;

typedef struct ExpressionNode
{
    char token[32];
    TokenKind kind;
    //TODO: remove this field
    int  prec;
    int arg_count;

    struct ExpressionNode* next;
} ExpressionNode;

#endif
