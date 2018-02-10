#include <stdio.h>
#include <string.h>
#define MAX 30
#define MAX_KEYWORDS 48
#define IDMAX 256
#define KEYMAX 80
#define ERR 0;
#define FEND -1;



//here is our struct that keeps the key value pairs stored
typedef struct
        {
		int line;
                int curVal;
                int key;
		char value[MAX];
        } token;

typedef struct {
	char* ident_arr[IDMAX];	
	int total;
}ident_table;

ident_table identArr;

// here is a keywords array map
static char* keywords[2][KEYMAX] ={ { "break", "case", "char", "const", "continue", "default", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "return", "short", "static", "struct", "switch", "void", "while","/","+","-","*","++","--","<=","=",">=","==","<",">","(",")","{","}","[","]","!","!=",",",";",":","&&","||","%"},
{ "BR", "CASE", "CHAR", "CONST", "CONT", "DEF", "DOB", "EL", "ENUM", "EXTRN", "FLT", "FOR", "GOTO", "IF", "INT", "LNG", "RET", "SRT", "STAT", "STR", "SWIT", "VOID", "WH","DIV","PLS","MNS","MUL","INC","DEC","LE","EQ","GE","EE","LS","GR","LSB","RSB","LMB","RMB","LLB","RLB","NOT","NEQ","COMM","SCOLL","COLL","AND","OR","PERC"} };

// here is a id_s variable global
// used to store new identifiers
char id_s[IDMAX][MAX];

int main(){
	id_s[0][0] = 'a';
	int times = 0;
	token key;	
	printArray();
	key.curVal = 0;
	key.line = 0;
	int decision;
	int place;
	int curId = 0;
	// Opening the file
	FILE * fp;
	fp = fopen("/home/ubuntu/alpha", "r+"); // read mode
	
	// if not opened
	if (fp == NULL)
	{
		perror("Error while opening the file.\n");
		return 0;
	}
	// if opens start working
	while (1){	// till the end of the file
		key.value[0]='\0';
		//goto space and comment removal function
		decision = spaceComRemoval(fp, &key);	//sending fp and struct key
		
//		printf("VALUE OF TIMES = %d\n",times);
		if (decision == -1){
			printf("File Ended\n");
			printArr();
			return 0;
		}
		else if (decision == 0){
			printf("An Error Occurred!");
		}
		else{
			
			place = keywordLookup(keywords,&key,fp);
		}
		if(place == -1){
			strCopToArr(key.value,curId);
			curId++;
		}
		else
			printf("The value, %s is in Keywords at loc = %d\n",key.value,key.key);
	}

	return 0;
}


// space and Comments Removal function
int spaceComRemoval(FILE *fp , token* key){

	//seek to the current letter
	fseek(fp, key->curVal, SEEK_SET);		

	char ch = '\0';				//initialization of char // this will hold our characters from file

	while ((ch = fgetc(fp)) != EOF){				//takeing first character going to EOF
		key->curVal++;							// increment current letter
//		printf("value in ch = %c\n",ch);
	
		// on the basis of the taken character switch
		switch (ch){
			case ' ':			// Spaces will be removed
				break;
			case '/':			// multiline comments
				ch = fgetc(fp);		
				key->curVal++;			//get character and increment cur value
				if (ch == '*'){		// in case caught the * start multiline removal till */
					while ((ch = fgetc(fp)) != EOF){
						key->curVal++;			// get character and increment
						if (ch == '*'){			// in case its a *
							ch = fgetc(fp);			//get next character and increment
							key->curVal++;
							if (ch == '/')			// if its a / then multiline comment completed
								break;
						}
						if(ch == EOF){			// if this sequence breaks then show error and return
							printf("Invalid syntex File ended without closing multiline comments");
							return -1;
						}
					}
				}
				else if (ch == '/'){		// Inline comments removal
					while ((ch = fgetc(fp)) != '\n'){
						key->curVal++;
					}
					if(ch == '\n'){
						key->line++;		// increment lineNO
					}
				}
				else{
					key->curVal--;
					printf("missing \ at line no %d invalid syntex",key->line);
				}
				break;
			case '\n':
				key->line++;
				break;
			default:	// incase no space or comment detected return and decrement cur value
				key->curVal--;
				return key->curVal;
		}
	}
	return -1;
}

// Lookup table example
int keywordLookup(char* table[],token* key, FILE *fp){
	//Local Declerations
	char str[30];
	static int i = 0;		//a static variable excessively used
	int dec=0;		//Short for decision
	char ch = '\0';
	
	//Initializations:-
	key->key = -1;
	strcpy(key->value,"");
	strcpy(str,"");
	
	//Opening file
	fseek(fp, key->curVal, SEEK_SET);
	
	//Until End of File
	while ((ch = fgetc(fp)) != EOF){
		key->curVal++;
//		printf("value in curval = %d\n",key->curVal);
//		printf("value in ch = %c\n",ch);
		if(ch == '/'){
			(key->value,"/");
			break;
		}
		else if(ch == ';'){
			(key->value,";");
			break;
		}
		else if(ch == '*'){
			(key->value,"*");
			break;
		}
		else if(ch == '%'){
			(key->value,"%");
			break;
		}
		else if(ch == '{'){
			(key->value,"{");
			break;
		}
		else if(ch == '}'){
			(key->value,"}");
			break;
		}
		else if(ch == '('){
			(key->value,"(");
			break;
		}
		else if(ch == ')'){
			(key->value,")");
			break;
		}
		else if(ch == '['){
			(key->value,"[");
			break;
		}
		else if(ch == ']'){
			(key->value,"]");
			break;
		}
		else if((ch > 64 && ch< 91)||(ch > 96 && ch <123)||(ch == 95)) //characters ident
		{
			int j = 0;
			while (ch != EOF){
				if((ch > 64 && ch < 91)||(ch > 96 && ch <123)||(ch == 95)||(ch>47 && ch<56)){
					str[j] = ch;
					str[j+1]='\0';
					// get next character
					ch = fgetc(fp);
					key->curVal++;
					j++;
				}
				else{
					strcpy(key->value,str);
					dec = lookChar(key->value);
					key->curVal--;
					if(dec == -1){
						printf("Not in ident array\n");
						return dec;
					}
					else
					{
						key->key = dec;
						return dec;
					}
				}
			}
			strcpy(key->value,str);
		}
		else if(ch == ','){
			(key->value,",");
			break;
		}
		else if(ch == ':'){
			(key->value,":");
			break;
		}
		else if(ch == '!'){
			strcpy(key->value,"!");
			ch = fgetc(fp);
			if(ch == '='){
				strcat(key->value,'=');
				key->curVal++;
			}
			break;
		}
		else if(ch == '='){
			strcpy(key->value,"=");
			ch = fgetc(fp);
			if(ch == '='){
				strcat(key->value,'=');
				key->curVal++;
			}
			else
				return key->key;
		}
		else if(ch == '<'){
			(key->value,"<");
			ch = fgetc(fp);
			if(ch == '='){
				strcat(key->value,'=');
				key->curVal++;
			}
			break;
		}
		else if(ch == '>'){
			(key->value,">");
			ch = fgetc(fp);
			if(ch == '='){
				strcat(key->value,'=');
				key->curVal++;
			}
			break;
		}
		else if(ch == '+'){
			(key->value,"+");
			ch = fgetc(fp);
			key->curVal++;
			if(ch == '+'){
				strcat(key->value,'+');
				key->curVal++;
			}
			else if(ch>47 && ch<56){
				while(ch>47&&ch<56){
					strcat(key->value,ch);
					ch = fgetc(fp);
					if(ch>47&&ch<56)
						key->curVal++;
					else if(ch == '.'){		// . check
						strcat(key->value,ch);
						ch = fgetc(fp);
						key->curVal++;
						if(ch>47&&ch<56){
							strcat(key->value,ch);
							ch = fgetc(fp);
							key->curVal++;
							while(ch>47&&ch<56){	//0-9 after .
								strcat(key->value,ch);
								ch = fgetc(fp);
								if(ch>47&&ch<56)	//Until 0-9
									key->curVal++;
								else if(ch == 'e'||ch == 'E'){	//found e E
									strcat(key->value,ch);
									ch = fgetc(fp);
									key->curVal++;
									if(ch == '+'||ch =='-'){
										strcat(key->value,ch);
										ch = fgetc(fp);
										key->curVal++;
										if(ch == '>'){
											strcat(key->value,ch);
											ch = fgetc(fp);
											key->curVal++;
											if(ch>47&&ch<56){	//On 0-9
												strcat(key->value,ch);
												ch = fgetc(fp);
												key->curVal++;
												while(ch>47&&ch<56){	//Till 0-9
													strcat(key->value,ch);
													ch = fgetc(fp);
													if(ch>47&&ch<56)	//Until 0-9
														key->curVal++;
													else
														return key->key;
												}
											}
											else{
												printf("incomplete float");
												return key->key;
											}
										}
										else{
											printf("incomplete float");
											return key->key;
										}
									}
									else{
										printf("incomplete float");
										return key->key;
									}
								}
								else{
									return key->key;
								}
							}
						}
						else{
							return key->key;
						}
					}
					else{
						return key->key;
					}
				}
			}
			break;
		}
		else if(ch == '-'){
			(key->value,"-");
			ch = fgetc(fp);
			if(ch == '-'){
				strcat(key->value,'-');
				key->curVal++;
			}
			break;
		}
		printf("Reading Done! \n");
		
	}
	dec = lookChar(key->value);
	if(dec == -1){
		printf("Not in ident array");
		return dec;
	}
	else
	{
		key->key = dec;
		return dec;
	}
}

int strCop(char* dest, char* source[], int value){
	int i =0;
	while(source[value][i]!= '\0'){
		dest[i] = source[value][i];
		i++;
	}
	dest[i]='\0';
	return 0;
}

// This function copies the new keyword in the array we want to store
// Now changing this function so that it can work with the new table scheme
int strCopToArr(char* source, int holder){
	int i = 0;
	while(source[i]!= '\0'){
		id_s[holder][i] = source[i];
		i++;
	}
	id_s[holder][i] = '\0';
	return 0;
}
int valCop(char* dest, char* source){
	int i = 0;
	while(source[i]!='\0'){
		dest[i]=source[i];
		i++;
	}
	dest[i]='\0';
	return i;
}
int lookChar(char* val){
	int i = 0;
	while (keywords[0][i] != NULL){
		if (strcmp (keywords[0][i],val) == 0){
			printf("The value in table = %s for time %d\n",keywords[0][i],i);
			return i;
		}
		else
			i++;
	}
	return -1;
}

void printArray(){
	int i = 0;
	while (keywords[0][i] != NULL){
		printf("The value in table = %s for time %d and operator = %s\n",keywords[0][i],i,keywords[1][i]);
		i++;	
	}
}
void printArr(){
	int i = 0;
	int j = 0;
	while(id_s[i][j] != '\0'){
		while(id_s[i][j] != '\0'){
			printf("%c",id_s[i][j]);
			j++;
		}
		printf("\n\n");
		j=0;
		i++;
	}
}

