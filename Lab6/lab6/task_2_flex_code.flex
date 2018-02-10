import java.io.*;
%%
%class Lab_6_Task_2
%public
%type Object
%function getNextToken
%{ 
public int comments = 0;
 public static void main(String[] args) {
 		try {
			InputStream is = new FileInputStream("input.txt");
			Lab_6_Task_2 s = new Lab_6_Task_2(is);
			s.getNextToken();
		}
		catch (IOException e) { }
 }
%}

ALPHA=[A-Za-z]
DIGIT=[0-9]
SPACE=[\ ]
NEWLINE = [\n|\r|\r\n]
identifier = {ALPHA}+
RESERVE = (read|write|then|if|else|repeat|until|end)
COMMENT=(\{[^}]*\})
int_const = {DIGIT}+

%% 
"int"         {System.out.println("Error: unrecognized symbol  "+yytext()); }

{int_const}  {System.out.println("Integer Constant: " + yytext());}  
{DIGIT}+{identifier} {System.out.println("Error: int literal followed by identifier: " +yytext());}
{RESERVE}       {System.out.println("Keyword: " + yytext());}

{identifier} { System.out.println("Identifier: " + yytext()); }  
{SPACE}      { }
{COMMENT}    { }
{NEWLINE}    { }
"*"       { System.out.println("Operator: Multiply");} 
"+"       {System.out.println("Operator: Addition"); }
"-"       {System.out.println("Operator: Subtraction"); }
"/"       {System.out.println("Operator: Division"); }
";"       {System.out.println("Operator: Semicolon");}
":="      {System.out.println("Operator: Assignment");}
"="       {System.out.println("Operator: Comparison");}
"("       {System.out.println("Operator: Starting Braces");}
")"       {System.out.println("Operator: Ending Braces");}
">"       {System.out.println("Operator: Greater than");}
"<"       {System.out.println("Operator: Less than");}
.         {System.out.println("Error: unrecognized symbol  "+yytext()); }
