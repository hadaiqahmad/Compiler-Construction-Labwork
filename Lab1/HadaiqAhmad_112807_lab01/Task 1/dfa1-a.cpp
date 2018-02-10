#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "DFA.h"

/*
* TODO: Define your Alphabet here
*/
char alphabet[] = { '0' };
int len = 0;

int main(void)
{
	 char input[MAX_SIZE] = { 0 };
	 
	printf("DFA :: Enter a string: ");
	//while (scanf("%s", (char *)&input) == 0);
	gets_s(input);
	for (int i = 0; i < MAX_SIZE; i++){
		if (input[i] == 0)
			len = i;
	}
	for (int i = 0; i <len; i++){
		printf("%c\n", input[i]);
	}
	if (validate(input) != 0)
	{
		printf("Error: The input string contains unknown symbols\n");
		system("pause");
		return 0;
	}

	if (recognize(input) == 1)
	{
		printf("Success: The input string is recognized!\n");
		
	}
	else
	{
		printf("Failure: The input string isn't recognized!!\n");
		
	}
	

	system("pause");
	return 0;
}

int validate(char input[])
{
	/*
	* TODO: Implement this function to validate the input string for Alphabet
	*/
	int flag=0;
	for (int i = 0; i <len; i++){
		if (input[i] == 'a' || input[i] == 'b' || input[i] == 'c')
		{
			flag = 0;
		}
		else
		{
			flag = 1;
			break;
		}
	}
	return flag;
}

int recognize( char input[])
{
	/*
	* TODO: Implement this function to recognize your input string for the DFA
	*/
	char CS = 'A';
	for (int i = 0; i < len; i++)
	{
		if (CS == 'A')
			goto A;
		else
			break;
	A:
		printf("CS%c\n", CS);
		if (input[i] == 'a')
		{
			CS = 'B';
			goto B;
		}

		if (input[i] == 'b')
		{
			CS = 'E';
			goto E;
		}

		if (input[i] == 'c')
		{
			CS = 'E';
			goto E;
		}
	B:
		i++;
		printf("CS%c\n", CS);
		if (input[i] == 'a')
		{
			CS = 'E';
			goto E;
		}
		if (input[i] == 'b')
		{
			CS = 'C';
			goto C;
		}
		if (input[i] == 'c')
		{
			CS = 'B';
			goto B;
		}
	C:
		i++;
		printf("CS%c\n", CS);
		if (input[i] == 'a')
		{
			CS = 'E';
			goto E;
		}
		if (input[i] == 'b')
		{
			CS = 'B';
			goto B;
		}
		if (input[i] == 'c')
		{
			CS = 'D';
			goto D;
		}
	E:
		i++;

		CS = 'E';
		printf("CS%c \n", CS);
		i++;
		break;

	D:
		i++;
		
		printf("CS%c \n", CS);
		if (input[i] == 'a')

		{
			CS = 'E';
			goto E;
		}
		else
		if (input[i] == 'b')

		{
			CS = 'E';
			goto E;
		}else
		if (input[i] == 'c')
		{
			CS = 'E';
			goto E;
		}else
		break;

	}
	if (CS == 'D')
		return 1;
	else
		return 0 ;
}


