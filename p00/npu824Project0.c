#include <stdio.h>  //For input/output functions.
#include <stdlib.h> //For malloc, free, etc.
#include "Project0.h"  //Include our own header file for the Employee struct.


int main()
{
	//1.  Open the file Project0.txt and read in the first line of the file to determine how many Employees we need for our array, and use malloc() to dynamically allocate an array of this size.
	FILE* fileIn;
	fileIn = fopen("Project0Input.txt", "r");

	Employee* employees;
	char buffer[1024];
	int lines, i;
	
	fgets(buffer, 1024, fileIn);
	sscanf(buffer, "%d", &lines);

	employees = (Employee*)malloc(lines * sizeof(Employee));

	//2.  Use a loop to read the Employee information from Project0.txt and write the information to the entries of your array.
	//Suggestion:  read a single line of the file using fgets() then use sscanf() to parse out the variables from the line.  
	for (i = 0; i < lines; i++)
	{
		fgets(buffer, 1024, fileIn);
		sscanf(buffer, "%s %d %lf", employees[i].name, &employees[i].id, &employees[i].hRate);
	}
	
	//3.  Loop through your array and print out the employee information.  Each employee (name, ID, hourly rate) should be on a single line.  The name should be left justified in a column of width 10.  
	//The IDs are each 6 digits long so they can be printed with a single space after it.  The hourly rate should be printed to 2 decimal places.
	for (i = 0; i < lines; i++)
	{
		printf("%s, %d, %.2lf\n", employees[i].name, employees[i].id, employees[i].hRate);
	}

	free(employees);

	return 0;
}