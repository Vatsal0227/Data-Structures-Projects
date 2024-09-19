#include "Queue.h"

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

NodeLL *allocateNode(Element value)
{
    NodeLL* newNode;
    newNode = (NodeLL*)malloc(sizeof(NodeLL));
    if (newNode == NULL)
    {
        printf("Error: unable to allocate Node\n");
    }
    newNode->element = value;
    newNode->next = NULL;
    return newNode;
}

void enqueue(Queue queue, Element value)
{
    NodeLL* newNode = allocateNode(value);
    if (queue->foot == NULL || queue->head == NULL)
    {
        queue->head = newNode;
        queue->foot = newNode;
    }
    else
    {
        queue->foot->next = newNode;
        queue->foot = queue->foot->next;
    }
}

int dequeue(Queue queue, Element *e)
{
    if (queue->foot == NULL)
    {
        return 0;
    }
    else if (queue->head == queue->foot)
    {
        *e = queue->head->element;
        NodeLL* p = queue->head;
        queue->head = NULL;
        queue->foot = NULL;
        free(p);
        return 1;
    }
    else
    {
        NodeLL* p = queue->head;
        queue->head = queue->head->next;
        *e = p->element;
        free(p);
        return 1;
    }
}

int frontElement(Queue q, Element* e)
{
    if(isEmpty(q) == TRUE) return 0;

    *e = q->head->element;

    return 1;
}

int isEmptyQueue(Queue q)
{
    if(q->head == NULL) return TRUE;
    else return FALSE;
}


