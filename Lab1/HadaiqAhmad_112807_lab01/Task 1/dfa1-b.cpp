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
	int flag = 0;
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

int recognize(char input[])
{
	/*
	* TODO: Implement this function to recognize your input string for the DFA
	*/
	char CS = 'A';
	for (int i = 0; i <= len; i++)
	{
		
		switch (CS){
		case 'A':
			
			if (input[i] == 'a')
			{
				CS = 'B';
				break;
			}else

			if (input[i] == 'b')
			{
				CS = 'E';
				break;
			}else

			if (input[i] == 'c')
			{
				CS = 'E';
				break;
			}
		case 'B':
			
			
			if (input[i] == 'a')
			{
				CS = 'E';
				break;
			}else
			if (input[i] == 'b')
			{
				CS = 'C';
				break;
			}
			else
			if (input[i] == 'c')
			{
				CS = 'B';
				break;
			}
		case 'C':
			
			
			if (input[i] == 'a')
			{
				CS = 'E';
				break;
			}
			else
			if (input[i] == 'b')
			{
				CS = 'B';
				break;
			}
			else
			if (input[i] == 'c')
			{
				CS = 'D';
				break;
			}
		case 'E':
			

			CS = 'E';
			i++;
			break;

		case 'D':
			

			
			if (input[i] == 'a')

			{
				CS = 'E';
				break;
			}
			else
			if (input[i] == 'b')

			{
				CS = 'E';
				break;
			}
			else
			if (input[i] == 'c')
			{
				CS = 'E';
				break;
			}
			else
				break;

		}
	}
	if (CS == 'D')
		return 1;
	else
		return 0;
}


