#include "Stack.h"

Stack newStack(int maximumStackSize)
{
    Stack newStack = (Stack)malloc(sizeof(StackImp)); // StactImp* newStack = (StackImp*)mallaoc(sizeof(StackImp));
    newStack->stackElements = (Element*) malloc(maximumStackSize * sizeof(Element));
    newStack->maxSize = maximumStackSize;
    newStack->count = 0;

    return newStack;
}

void freeStack(Stack s)
{
    free(s->stackElements);
    free(s);
}

void push(Stack s, Element e)
{
    if(s->count == s->maxSize)
    {
        printf("ERROR: The Stack is full\n");
        return;
    }

    s->stackElements[s->count++] = e;
}

Element pop(Stack s)
{  
    Element e;
    if(s->count == 0)
    {
       printf("ERROR: The stack is already empty/n");
       return e;
    }
 
    e = s->stackElements[--s->count];

    return e;
}

int isEmpty(Stack s)
{
    if(s->count == 0) return 1;
    else return 0;
}

Element topElement(Stack s)
{
    Element e = s->stackElements[s->count-1];

    return e;
}
