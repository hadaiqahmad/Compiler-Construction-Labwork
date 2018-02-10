%{
#include <stdio.h>
#include <assert.h>
#include <math.h>
static float Pop();
static float Top();
static void Push(float val);
%}

%union {
	int ival;
	float fval;
        char* sval;
}

%token <ival> INT
%token <fval> FLOAT
%token <sval> LOG EXP

%%
S : S E  '\n' { printf("= %f\n", Top()); }
| /*empty string*/
;

E : E '+' T     { Push(Pop() + Pop()); }
|   E '-' T     { float op2 = Pop(); Push(Pop() -op2); }
|   T
;

T : T '*' G     { Push(Pop() * Pop()); }
|   T '/' G     { float op2 = Pop(); Push(Pop() / op2); }
|   G
;

G : LOG F       { Push(log(Pop())); }
|   F
;

F : F '^' B	{ float exp1 = Pop(); float base = Pop(); Push(pow(base,exp1));}
|   EXP B	{ Push(exp(Pop()));}
|   B
; 

B : INT         {Push($1);}
  | FLOAT       {Push($1);}
  | '(' E ')'   
;


%%

static float stack[100];
int count = 0;

static float Pop() {
assert(count > 0);
return stack[--count];
}
static float Top() {
assert(count > 0);
return stack[count-1];
}
static void Push(float val) {
assert(count < sizeof(stack)/sizeof(*stack));
stack[count++] = val;
}
int main() {
return yyparse();
}
