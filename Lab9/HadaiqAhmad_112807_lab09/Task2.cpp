#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

#define SIZE 100
//Token Types
#define PUBLIC 1
#define FINAL 2
#define CLASS 3
#define IDENTIFIER 4
#define EXTENDS 5
#define IMPLEMENTS 6
#define COMMA 7


char input[SIZE];
char production[SIZE][SIZE];

int position = -1, length, stacktop = -1;
char string[SIZE];
int tokenType = -1;
int commaFound = 0;

void S();
void C();
void P();
void F();
void X();
void Y();
void I();
void J();
void advance();

/* Advance the input pointer i.e. position gives use the next token */
void advance()
{
	if (commaFound)
	{
		commaFound = 0;
		tokenType = COMMA;
		return;
	}

	tokenType = -1;
	position++;
	if (position < length)
	{
		//Skip whitespace
		while (input[position] == ' ')
		{
			position++;
		}

		int stringFound = 0;
		int stringIterator = 0;
		while ((input[position] >= 'a' || input[position] >= 'A') && (input[position] <= 'z' || input[position] <= 'Z'))
		{
			string[stringIterator] = input[position];
			stringIterator++;
			position++;

			stringFound = 1;
		}

		if (stringFound)
		{
			string[stringIterator] = '\0';
			//printf("%s\n", string);

			//Check the string
			if (strcmp(string, "public") == 0)
			{
				tokenType = PUBLIC;
			}

			else if (strcmp(string, "final") == 0)
			{
				tokenType = FINAL;
			}

			else if (strcmp(string, "class") == 0)
			{
				tokenType = CLASS;
			}

			else if (strcmp(string, "extends") == 0)
			{
				tokenType = EXTENDS;
			}

			else if (strcmp(string, "implements") == 0)
			{
				tokenType = IMPLEMENTS;
			}

			else
			{
				tokenType = IDENTIFIER;
			}
		}

		//Verify comma is not ommitted along with whitespace
		if (input[position] == ',')
		{
			commaFound = 1;
		}
	}
}

void S()
{
	strcpy(production[++stacktop], "S->C");
	C();
}

void C()
{
	strcpy(production[++stacktop], "C->P F class identifier X Y");
	P();
	F();
	if (tokenType==CLASS){ advance(); }
	else { printf("Error: invalid class\n"); position = -5; }	//Sasta way to break the flow

	if (tokenType == IDENTIFIER){ advance(); }
	else { printf("Error: invalid identifer\n"); position = -5; }

	X();
	Y();
}

void P()
{
	if (tokenType == PUBLIC){
		strcpy(production[++stacktop], "P->public");
		advance();
	}
	else{
		strcpy(production[++stacktop], "P->NULL");
	}
}

void F()
{
	if (tokenType == FINAL){
		strcpy(production[++stacktop], "F->final");
		advance();
	}
	else{
		strcpy(production[++stacktop], "F->NULL");
	}
}

void X()
{
	if (tokenType == EXTENDS){
		advance();
		if (tokenType == IDENTIFIER){
			strcpy(production[++stacktop], "X->extends identifier");
			advance();
		}
	}
	else{
		strcpy(production[++stacktop], "X->NULL");
	}

}

void Y()
{
	if (tokenType == IMPLEMENTS){
		strcpy(production[++stacktop], "Y->implements I");
		advance();
		I();
	}
	else
	{
		strcpy(production[++stacktop], "Y->NULL");
	}
}

void I()
{
	if (tokenType == IDENTIFIER){
		strcpy(production[++stacktop], "I->identifier j");
		advance();
		J();
	}
}

void J()
{
	if (input[position] == ','){
		strcpy(production[++stacktop], "J->, I");
		advance();
		I();
	}
	else
	{
		strcpy(production[++stacktop], "J->NULL");
	}
}

/*
Recursive Descent Parser for Grammar given below:
S -> C
C -> P F class identifier X Y
P -> public | epsilon
F -> final | epsilon
X -> extends identifier | epsilon
Y -> implements I | epsilon
I -> identifier J
J -> , I | epsilon
*/

int main()
{
	int i;

	printf("Enter Input String: ");
	//scanf("%s", input);
	//gets(input);
	fgets(input, SIZE, stdin);

	length = strlen(input);
	input[length] = '$';

	// Get the next token i.e. move the position index to first input character
	advance();
	// Start with the goal symbol
	S();

	// See if we consumed the whole input string
	if (position == length)
	{
		printf("String Accepted\n");

		/*TODO: printout all the productions used during the parse */
		int i;
		for (i = 0; i <= stacktop; i++)
		{
			printf("%s\n", production[i]);
		}
	}
	else
	{
		printf("String Rejected\n");
	}

	return 0;
}