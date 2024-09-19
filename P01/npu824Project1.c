#include "Stack.h"
#include <string.h>

#define MAX_LINE_LENGTH 50


int convertToPostfix(char *infixString, char *postfixString);
int evaluatePostfix(char *postfixString);
int findPriority(char);
int isOperator(char);
int ctoi(char);
int calc(int, int, char);

int main()
{
	FILE *inputFile;
	inputFile = fopen("p1Input.txt", "r");
	if(inputFile == NULL){

		perror("Error opening file");
		return -1;
	}


	//This string will hold the infix equations that are read from inputFile, one at a time.
	char infixString[MAX_LINE_LENGTH];


	//Use fgets to read the next line from the inputFile.
	//Store the line into infixString.
	//The while loop repeats until there are no more lines in the file.
	while(fgets(infixString, MAX_LINE_LENGTH, inputFile)!=NULL){

		//If the line is blank, skip it.
		if(infixString[0] == '\n')
			continue;

		printf("Current infix string: %s",infixString);

		//postfixString is a string to store the equation from szInfixString converted into postfix.
		char postfixString[MAX_LINE_LENGTH];

		//Call the convertToPostfix function (that you are to implement below main).
		int returnMessage = convertToPostfix(infixString,postfixString);


		//convertToPostfix should return an integer letting us know if the infix string was in a valid format.
		//If the format is valid (we returned 0), then we call the evalutaePostfix function (that you are to implement below), and print the result of the evalution.
		//If the format is not valid (we returned something other than 0), then we print the corresponding error message.
		switch(returnMessage)
		{

			case 0: //0 means the infix string had no errors.  Go ahead and evaluate the postfix string.
				printf("Postfix string: %s\n",postfixString);
				int result = evaluatePostfix(postfixString);
				printf("It evaluates to %d.\n",result);
				break;
			case 1:  //1 means the infix string is missing a left parenthesis.
				printf("WARNING: Missing left parenthesis.\n");
				break;
			case 2: //2 means the infix string is missing a right parenthesis.
				printf("WARNING: Missing right parenthesis.\n");
				break;
			case 3: // 3 means missing operator.
				printf("WARNING: Missing operator.\n");
				break;
			case 4: //4 means missing operand.
				printf("WARNING: Missing operand.\n");
				break;
			default:
				printf("WARNING: %d.\n", returnMessage);


		}


		printf("\n\n");
	}

	fclose(inputFile);

	return 0;
}


/*******
int convertToPostfix(char *infixString, char *postfixString)

Input: 
infixString is a character array of length <= MAX_LINE_LENGTH that contains an equation in infix format.
postfixString is a currently empty character array of length <= MAX_LINE_LENGTH that we should fill with a postfix representation of infixString.

Output:
We return an integer based on any errors found in infixString.
If there are no errors, return 0.
If there is a missing (, return 1.
If there is a missing ), return 2.
If there is a missing operator, return 3 (for extra credit).
If there is a missing operand, return 4 (for extra credit).
*********/
int convertToPostfix(char *infixString, char *postfixString){
    strcpy(postfixString, "");
    int i;
    Element e;
    Stack s = newStack(MAX_LINE_LENGTH);
   
//========================================Parenthesis ERROR========================================

    for(i = 0; i < strlen(infixString); i+=2)
    {
        char temp = infixString[i];

        if(temp == '(')
        {
            e.operation = temp;
            push(s, e);
        }
        else if(temp == ')' && isEmpty(s) == 1) return 1;
        else if(temp == ')' && isEmpty(s) == 0) e = pop(s);
    }
    if(isEmpty(s) == 0) return 2;

    freeStack(s);

//===================================================================================================

    char infixCopy[strlen(infixString)+1];

    strcpy(infixCopy, infixString);

    int nCount = 0, oCount = 0;
    char* token;

    token = strtok(infixCopy, " ");

    while(token != NULL)
    {
        char temp = token[0];
        if(isdigit(temp) != 0) nCount++;
        else if(isOperator(temp) == 1) oCount++;

        token = strtok(NULL, " ");
    }
    oCount++;

    if(oCount < nCount) return 3;
    else if(oCount > nCount) return 4;

//===================================================================================================

    Stack oStack = newStack(MAX_LINE_LENGTH);
    Element op;

    for(i = 0; i < strlen(infixString); i+=2)
    {
        char temp = infixString[i];

        if(isdigit(temp) != 0) strncat(postfixString, &temp, 1);

        else if(isOperator(temp) == 1)
        {
            while(isEmpty(s) == 0 && topElement(oStack).operation != '(' && findPriority(topElement(oStack).operation) >= findPriority(temp))
            {
                op = pop(oStack);
                strncat(postfixString, &op.operation, 1);
            }
            op.operation = temp;
            push(s, op);
        }
        else if(temp == '(')
        {
            op.operation = temp;
            push(oStack, op);
        }
        else if(temp == ')')
        {
            while(isEmpty(oStack) == 0 && topElement(oStack).operation != '(')
            {
                op = pop(oStack);
                strncat(postfixString, &op.operation, 1);
            }
            if(topElement(oStack).operation == '(') op = pop(oStack);
        }
    }

    while(isEmpty(s) == 0)
    {
        op = pop(oStack);
        strncat(postfixString, &op.operation, 1);
    } 

    freeStack(oStack);
    return 0;
}

int isOperator(char c)
{
    if (c == '*' || c == '/' || c == '+' || c == '-') return 1;
    else return 0;
}

int findPriority(char c)
{
    if(c == '*' || c == '/') return 2;
    else if(c == '+' || c == '-') return 1;
    else return 0;
}

/************
evaluatePostfix(char *postfixString)

Input:
postfixString is a string of length <= MAX_LINE_LENGTH that contains an equation in postfix representation.
If your convertToPostfix() function is correct, this string should be in a valid postfix format.

Output:
Return an integer representing what the postfix equation evaluated to.
************/
int evaluatePostfix(char *postfixString){

    int i, x = 0, y = 0, result = 0;
    Stack nStack = newStack(MAX_LINE_LENGTH);
    Element num;

    for(i = 0; i < strlen(postfixString); i++)
    {
        char temp = postfixString[i];

        if(isdigit(temp) != 0)
        {
            num.operand = ctoi(temp);
            push(nStack, num);
        }
        else if(isOperator(temp) == 1)
        {
            x = pop(nStack).operand;
            y = pop(nStack).operand;

            num.operand = calc(x, y, temp);

            push(nStack, num);
        }
    }
    result = pop(nStack).operand;
    freeStack(nStack);

    return result;
}

int calc(int x, int y, char o)
{
    switch(o)
    {
        case '+':
            return x+y;
            break;
        case '-':
            return y-x;
            break;
        case '*':
            return x*y;
            break;
        case '/':
            return y/x;
            break;
        default:
            break;
    }
}

int ctoi(char c)
{
    if(c == 48) return 0;
    if(c == 49) return 1;
    if(c == 50) return 2;
    if(c == 51) return 3;
    if(c == 52) return 4;
    if(c == 53) return 5;
    if(c == 54) return 6;
    if(c == 55) return 7;
    if(c == 56) return 8;
    if(c == 57) return 9;
}
