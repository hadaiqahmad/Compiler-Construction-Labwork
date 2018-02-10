#define _CRT_SECURE_NO_WARNINGS 

#include <stdio.h>
#include <string.h>

#define SIZE 100

char input[SIZE];
char production[SIZE][SIZE];

int position = -1, length, stacktop = -1;
char id, num;	// Identifier and number
void E();
void T();
void F();
void T_prime();
void E_prime();
void advance();

/* Advance the input pointer i.e. position gives use the next token */
void advance()
{
	position++;
	if (position < length)
	{
		if (input[position] >= '0' && input[position] <= '9')
		{
			num = input[position];
			id = '\0';
		}

		if ((input[position] >= 'a' || input[position] >= 'A') &&
			(input[position] <= 'z' || input[position] <= 'Z'))
		{
			id = input[position];
			num = '\0';
		}
	}
}

/* Use the following as an example */
void E()
{
	strcpy(production[++stacktop], "E->TE'");
	T();
	E_prime();
}

void E_prime()
{
	if (input[position] == '+'){
		strcpy(production[++stacktop], "E'->+TE'");
		//Plus thing
		advance();


		T();
		E_prime();
	}
	else if (input[position] == '-'){
		strcpy(production[++stacktop], "E'->-TE'");
		//Minus thing
		advance();
		T();
		E_prime();
	} 
	else {
		strcpy(production[++stacktop], "E'->NULL");
	}
}

void T()
{
	strcpy(production[++stacktop], "T->FT'");
	F();
	T_prime();
}

void T_prime()
{
	if (input[position]=='*'){
		strcpy(production[++stacktop], "T'->*FT'");
		//Multiply
		advance();
		F();
		T_prime();
	}
	else if (input[position] == '/'){
		strcpy(production[++stacktop], "T'->/FT'");
		//Divide
		advance();
		F();
		T_prime();
	}
	else{
		strcpy(production[++stacktop], "T'->NULL");	
	}
}

void F()
{
	if (id != '\0'){
		strcpy(production[++stacktop], "F->id");
		advance();
	}
	else if (input[position]=='('){
		strcpy(production[++stacktop], "F->(E)");
		advance();
		E();
		advance();
		
	}
	else if (num != '\0'){
		strcpy(production[++stacktop], "F->num");
		advance();
	}
	
}

/*
Recursive Descent Parser for Grammar given below:
E-> TE’
E’-> +TE’ | -TE’ | NULL
T-> FT’
T’-> *FT’ | /FT’ | NULL
F-> id    | (E)  | num
*/

int main()
{
	int i;

	printf("Enter Input String: ");
	scanf("%s", input);

	length = strlen(input);
	input[length] = '$';

	// Get the next token i.e. move the position index to first input character
	advance();
	// Start with the goal symbol
	E();

	// See if we consumed the whole input string
	if (position == length)
	{
		printf("String Accepted\n");
		/*TODO: printout all the productions used during the parse */
		while (stacktop){
			printf("%s\n", production[stacktop]);
			stacktop--;
		}
	}
	else
	{
		printf("String Rejected\n");
	}

	return 0;
}
