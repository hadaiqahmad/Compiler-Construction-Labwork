%%

(("if"|("then")|("begin")|("end")|("procedure")|("function"))) {printf("A keyword: "); ECHO; printf("\n");}

([+-/*<>=/]|[%$]) {printf("An Operator: "); ECHO; printf("\n");}

([()]|[{}]) {printf("A Bracket: "); ECHO; printf("\n");}

(\") {printf("A Qoutation: "); ECHO; printf("\n");}

(\\n) {printf("A newline operator"); ECHO; printf("\n");}

("//".*) {printf("A Comment: "); ECHO; printf("\n");}

(!) {printf("An Exlamation Mark: "); ECHO; printf("\n");}

(;) {printf("A Semicolon: "); ECHO; printf("\n");}


([\n\t" "]) {}


([+-]?([0-9]*[.])?[0-9]+) {printf("A Number : "); ECHO; printf("\n");}

([a-z]+[0-9a-zA-Z]*) {printf("An id: "); ECHO; printf("\n");}

([A-Z]) {printf(" Capital Alphabets "); ECHO; printf("\n");}

. {printf("Unrecognized character: "); ECHO; printf("\n");}

%%

int main(int argc, char **argv)

{

if(argc>1)

yyin=fopen(argv[1],"r");

else

yyin=stdin;

yylex();

}
