/*Code for PostFix*/

%{ 
 #define stack_size 5
 static int stackIterator, stack [stack_size];
int j = 0;
int iterator = 0;
int it2 = 0;
 static void push (int i) {
   if (++stackIterator<stack_size) {
stack[stackIterator]= i;



}

 }

static void print() {

for(j = 0;j<stack_size;j++){
printf("%d ",stack[j]);

}
printf("\n");


}
 static int pop (void) {
   if (stackIterator>=0) {
stackIterator = stackIterator;
int val = stack[stackIterator];
stack[stackIterator] = 0;
stackIterator = stackIterator -1;
return val;

}

 }
%}
%%

[0-9]+                   {push (atoi(yytext));print();}
"+"                      {push (pop() + pop());print();}
"*"                      {int first = pop();int second = pop(); int product = first*second; push(product);print();}
"-"                        {int right= pop(); push (pop() - right);print();}
"/"                      {int right= pop(); push (pop() / right);print();}
"\n"                       {printf ("%d\n", pop());}
[ \t\n]                  ;
%%                        

 int main (void) {
stackIterator= -1; 

yyin = stdin;
yylex(); 

}


