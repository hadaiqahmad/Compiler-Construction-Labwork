%{
#include "lab8.tab.h"
%}

%x CMNT
%x CPPCMNT

%%
[0-9]+     			{ yylval.ival = atoi(yytext); return INT;}
[-+]?[0-9]+"."[0-9]+            { yylval.fval = atof(yytext); return FLOAT;}

[-+*^/\n]			{ return yytext[0];}
"e"				{ yylval.sval = strdup(yytext);return EXP;}
log				{ yylval.sval = strdup(yytext);return LOG;}

<CMNT>\n	{}
<CMNT>"*/"	{BEGIN INITIAL;}
<CMNT>.		{}

"//"		{BEGIN CPPCMNT;}
<CPPCMNT>.	{}
<CPPCMNT>\n	{BEGIN INITIAL;}
.				{ /* ignore everything else */ }

%%
