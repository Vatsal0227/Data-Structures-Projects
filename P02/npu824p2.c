#include "Queue.h"

void fillTable(Table* t, int num, int time, Queue q);

void selectionSort(Table* t, int size);

void printTable(Table* t, int size);

int isTableEmpty(Table* t, int size);

int main()
{
    
    int i, j, k;

    char buffer[1024];

    Table* checkIn = newTable(5);

    Table* vaccine = newTable(10);


    Queue cQ = newQueue();
    Queue vQ = newQueue();

    FILE* fileIn = fopen("p2Input.txt", "r");
    if(fileIn == NULL)
    {
        printf("ERROR: Could not open the file\n");
        return -1;
    }
    

    for(i = 1; !feof(fileIn) || isEmpty(cQ) == FALSE || isEmpty(vQ) == FALSE || isTableEmpty(checkIn, 5) == FALSE || isTableEmpty(vaccine, 10) == FALSE; i++)
    {
//================================================Adding=People=To=1st=Queue===============================================
        if(!feof(fileIn))
        {
            Element input;
            char eC[4];
            fgets(buffer, 1024, fileIn);
            
            if(sscanf(buffer, "%d %d %s", &input.arrivalTime, &input.patientID, eC) == 3)
            {
                if(strcmp(eC, "yes") == 0) input.eCheckIn = TRUE;
                else if(strcmp(eC, "no") == 0) input.eCheckIn = FALSE;
            }
            
            enqueue(cQ, input);
            
            
            
            
            //printf("Patient-(%d %d %d)\n----------------------\n", cQ->foot->element.arrivalTime, cQ->foot->element.patientID, cQ->foot->element.eCheckIn);
            
        }
        

//================================================Check=In=Table============================================================
        
        fillTable(checkIn, 5, i, cQ);
        
        k = 0;
        for(j = 0; j < 5; j++)
        {
            if(checkIn[j].lTime == i)
            {
                k++;
            }
        }
        if(k>0)
        {
            Table* leaveCIT = newTable(k);
            k=0;
            for(j = 0; j < 5; j++)
            {
                if(checkIn[j].lTime == i)
                {
                    leaveCIT[k]=checkIn[j];
                    checkIn[j].isFull = FALSE;
                    k++;
                }
            }
            
            selectionSort(leaveCIT, k);
            
            //printTable(checkIn, 5);
            
            for(j = 0; j < k; j++)
            {
                enqueue(vQ, leaveCIT[j].e);
            }
        }

        fillTable(checkIn, 5, i, cQ);
        
//================================================Vaccine=Table=============================================================

        

        fillTable(vaccine, 10, i, vQ);

        //printTable(vaccine, 10);

        k = 0;
        for(j = 0; j < 10; j++)
        {
            if(vaccine[j].lTime == i)
            {
                k++;
            }
        }
        
        Table* leaveVT = newTable(k);
        
        if(k>0)
        {
            k=0;
            for(j = 0; j < 10; j++)
            {
                if(vaccine[j].lTime == i)
                {
                    leaveVT[k]=vaccine[j];
                    vaccine[j].isFull = FALSE;
                    k++;
                }
            }
            
            selectionSort(leaveVT, k);
            
            //printTable(leaveVT, 10);
        }

        fillTable(vaccine, 10, i, vQ);
        
       

//================================================Observation=Queue=========================================================

        for(j = 0; j < k; j++)
        {

            printf("Patient %d arrived at time %d and completed observation at time %d.\n", leaveVT[j].e.patientID, leaveVT[j].e.arrivalTime, leaveVT[j].lTime+30);
        }
        
        memset( buffer, 0, sizeof(buffer));

    }
    
    free(checkIn);
    free(vaccine);
    
    freeQueue(cQ);
    freeQueue(vQ);
    
    return 0;
}







//------------------------------------------------Helper-Functions----------------------------------------------------------
void fillTable(Table* t, int num, int time, Queue q)
{
    int i;
    Element e;

    for(i = 0; i < num; i++)
    {
        if(t[i].isFull == FALSE && isEmpty(q) == FALSE)
        {
             dequeue(q, &e);
            //Element temp;
            //frontElement(q, &temp);
            //printf("Patient-(%d %d %d)\n================\n", temp.arrivalTime, temp.patientID, temp.eCheckIn);             
            
            if(e.eCheckIn == TRUE) 
            {
                t[i].lTime = time+4;
                e.eCheckIn = FALSE;
            }
            else t[i].lTime = time+10;
            
            

            t[i].e = e;
            t[i].isFull = TRUE;
        }
    }
}

void selectionSort(Table* t, int size)
{
    int i, j, min;

    for(i = 0; i < size-1; i++)
    {
        min = i;

        for(j = i+1; j < size; j++)
        {
            if(t[j].e.arrivalTime < t[min].e.arrivalTime)
            {
                min = j;
            }

            Table temp = t[min];
            t[min] = t[i];
            t[i] = temp;
        }
    }
}

void printTable(Table* t, int size)
{
    int i = 0;
    
    for(i = 0; i < size; i++)
    {
        if(t[i].lTime == 0) break;
        printf("Patient-(%d %d %d), Leave-Time-%d, Is-Full-%d\n", t[i].e.patientID, t[i].e.arrivalTime, t[i].e.eCheckIn, t[i].lTime, t[i].isFull);
    }
    printf("=================================\n");
}

int isTableEmpty(Table* t, int size)
{
    int i = 0;
    
    for(i = 0; i < size; i++)
    {
        if(t[i].isFull == TRUE) return FALSE;
    }
    return TRUE;
}
