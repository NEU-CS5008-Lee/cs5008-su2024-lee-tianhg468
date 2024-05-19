/* Name: Tian Huang
 * Email: huang.tian2@northeastern.edu*/

/*C Program to read and print the n employee details using structure and dynamic memory allocation*/
#include <stdio.h>
#include <stdlib.h>
/*structure to hold the details of an employee*/
typedef struct employee
{
    int empId;
    char Name[100];
    char Designation[100];
    char Dept[10];

}employee_t;

/* Read the employee details using scanf*/
void readData(int n, employee_t* s)
{
    for (int i=0; i<n; i++) {
        printf("Enter the employeeID, Name, Designation and Department of Employee %d: \n", i+1);
	scanf("%d %s %s %s",&(s->empId), s->Name, s->Designation, s->Dept);
	s++;
	printf("\n");
    }
}   

/* Function to print the employee details*/
void display(int n, employee_t* s)
{
    for (int i=0; i<n; i++) {
        printf("The details of Employee %d: \n empId: %d\n Name: %s\n Designation: %s\n Dept: %s\n", i+1, s->empId, 
			s->Name, s->Designation, s->Dept);
	s++;
	printf("\n");
    }    
}

/*----------Main Program--------*/
int main()

{
    // Main Function to print the employee details
    int n;
    printf("Enter the number of employees: ");
    scanf("%d", &n);
    employee_t* s = (employee_t*) malloc(n * sizeof(employee_t));
    readData(n, s);
    display(n, s);
    free(s);
    return 0;
}

