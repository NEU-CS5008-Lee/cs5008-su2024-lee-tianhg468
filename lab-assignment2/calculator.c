//Tian Huang
//huang.tian2@northeastern.edu

#include<stdio.h>
int main()
{
    int a,b,c,remainder, choice;
    
    printf("Enter your choice\n");
    printf(" 1.addition\n 2. Subtraction\n 3. Multiplication\n 4. Division\n");
    scanf("%d",&choice);
    
    printf("Enter a and b values: ");
    scanf("%d %d", &a, &b);
    
    switch (choice) {
     case (1):
      c = a + b;
      printf("Addition\n");
      printf("Sum = %d", c);
      break;
     case (2):
      c = a - b;
      printf("Subtraction\n");
      printf("Difference = %d", c);
      break;
     case (3):
      c = a * b;
      printf("Multiplication\n");
      printf("Product = %d", c);
      break;
     case (4):
      if (b==0) {
          printf("Divide by zero error");
	  break;
      }
      else {
          c = a / b;
	  remainder = a % b;
          printf("Division\n");
          printf("Quotient = %d\n", c);
	  printf("Remainder = %d", remainder);
	  break;
      }
     default:
      printf("Invalid option");
      break;

    }           
    return 0;
}
