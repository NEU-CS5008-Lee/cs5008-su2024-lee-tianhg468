// huang.tian2@northeastern.edu
// Tian Huang

#include<stdio.h>
#include<string.h>

int compression(char arr[], int n, char res[]){
    
    //insert your code here
    char *ptr=arr;
    char *ptrend=arr+n;
    char encoding[50];
    int repeat;
    strcpy(res,"");

    while(ptr<ptrend)
    {
        char ch = *ptr;
        repeat=0;
        while(*ptr==ch)
        {
            ptr++;
            repeat++;
        }
        if(repeat>1)
        {
            sprintf(encoding,"%c%d",ch,repeat);
            strcat(res,encoding);
        }else
        {
            sprintf(encoding,"%c",ch);
            strcat(res,encoding);
        }
    }
    printf("Compressed string is %s\n", res);
    return strlen(res);

}
 
int main()
{
    char a[]="aaaaaaaaaaaaaabbbbcccd";
    char res[50];
    int r,n=strlen(a);//n is the size of input array
    r=compression(a,n,res);
    printf("length of the compressed string:%d\n",r);
    return 0;
}
