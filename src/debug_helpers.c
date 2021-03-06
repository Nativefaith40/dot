#include "debug_helpers.h"

/* void debugMathExpression(Context* context, MathExpression* math_expression); */
/* void debugMathFactor(Context* context, MathFactor* factor); */

void debugLog(Context* context, const char* format, ...)
{
    if ( context->debug_mode == 0 ) return;
	char result[1024];

    /* Declare a va_list type variable */
    va_list myargs;

    /* Initialise the va_list variable with the ... after fmt */
    va_start(myargs, format);

    /* Forward the '...' to vprintf */
    vsprintf(result, format, myargs);

    /* Clean up the va_list */
    va_end(myargs);

	printf("%s\n", result);
}

void debugLogNoNewLine(Context* context, const char* format, ...)
{
    if ( context->debug_mode == 0 ) return;
	char result[1024];

    /* Declare a va_list type variable */
    va_list myargs;

    /* Initialise the va_list variable with the ... after fmt */
    va_start(myargs, format);

    /* Forward the '...' to vprintf */
    vsprintf(result, format, myargs);

    /* Clean up the va_list */
    va_end(myargs);

	printf("%s", result);
}

void debugLogAddNewLine(Context* context)
{
    if ( context->debug_mode == 0 ) return;
	printf("\n");
}

void dumpExpression(Context* context, Expression* expression)
{
    if ( context->debug_mode != 1 ) return;
    debugLogNoNewLine(context, "Dumping expression: ");

    ExpressionNode* node = expression->first_node;
    while ( node != NULL ) 
    {
        debugLogNoNewLine(context, "%s(%d) ", node->token, node->kind);
        node = node->next;
    }
    debugLog(context, "\n");
}


void errorLog(const char* format, ...)
{
	char result[1024];

    /* Declare a va_list type variable */
    va_list myargs;

    /* Initialise the va_list variable with the ... after fmt */
    va_start(myargs, format);

    /* Forward the '...' to vprintf */
    vsprintf(result, format, myargs);

    /* Clean up the va_list */
    va_end(myargs);

	printf("%s\n", result);
	abort();
}

