//Tian Huang
//huang.tian2@northeastern.edu
//To perform insertion sort of integers stored in a file and display the output and store it in another file.
#include <stdio.h>
#include<stdlib.h>

int main()
{
    FILE *fp;
    int arr[10],temp;
    int count=0,i,j;
    /*count will have the total number of elements in the array*/

    /*read the file*/
    fp=fopen("Input1.txt","r");
    if(fp==NULL){
        //if file returns NULL then can't open the file
        printf("\n Cannot open the file \n");
        exit(0);
    }

    while(fscanf(fp, "%d", &arr[count]) != EOF) {
        count++;
    }
         
    printf("The array before sorting is: \n");
    for (i=0; i<count; i++) {
       printf("%d ", arr[i]);   
    }
    
    //insertion sort
    for (i=1; i<count; i++) {
        for (j=i; j>0 && arr[j-1]>arr[j]; j--) {
	    temp = arr[j];
	    arr[j] = arr[j-1];
	    arr[j-1] = temp;
	}
    }

    printf("\nThe array after sorting is: \n");
    for (i=0; i<count; i++) {
       printf("%d ", arr[i]);   
    }
    //write to file 
    fp = fopen("Output.txt", "w");
    if (fp==NULL){
        printf("\n Cannot open the file");
	exit(0);
    }
    for(i=0; i<count; i++){
        fprintf(fp, "%d\n", arr[i]);
    }

    fclose(fp);
    
    return 0;
}
