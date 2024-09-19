#include "Queue.h"

Table* newTable(int size)
{
    Table* newTable = (Table*)malloc(size * sizeof(Table));
    
    initializeTable(newTable, size);
    return newTable;
}

void initializeTable(Table* t, int size)
{
    int i;
    
    for(i = 0; i < size; i++)
    {
        //t[i].e = NULL;
        t[i].lTime = 0;
        t[i].isFull = FALSE;
    }
    
}

Queue newQueue()
{
    Queue newQ = (Queue)malloc(sizeof(QueueImp));
    newQ->head = NULL;
    newQ->foot = NULL;

    return newQ;
}

void freeQueue(Queue q)
{
    NodeLL* temp;
    while(q->head != q->foot)
    {
        temp = q->head;
        q->head = q->head->next;
        free(temp);
    }

    free(q->head);
    free(q);
}

NodeLL* allocateNode(Element value)
{
    NodeLL* newNode = (NodeLL*)malloc(sizeof(NodeLL));

    newNode->element = value;
    newNode->next = NULL;

    return newNode;
}

void enqueue(Queue q, Element value)
{
    NodeLL* newNode = (allocateNode(value));

    if(isEmpty(q) == TRUE)
    {
        q->head = newNode;
        q->foot = newNode;
    }

    q->foot->next = newNode;
    q->foot = q->foot->next;
}

int dequeue(Queue q, Element *e){

    if(isEmpty(q) == TRUE){
        return FALSE;
    }
    else if(q->head == q->foot){
        *e = q->head->element;
        q->head = NULL;
        q->foot = NULL;
        return TRUE;
    }
    else{
        *e = q->head->element;
        NodeLL *tempNode = q->head;
        q->head = q->head->next;
        free(tempNode);
        return TRUE;
    }

}

int frontElement(Queue q, Element* e)
{
    if(isEmpty(q) == TRUE) return 0;

    *e = q->head->element;

    return 1;
}

int isEmpty(Queue q)
{
    if(q->head == NULL) return TRUE;
    else return FALSE;
}
