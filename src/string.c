#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "myString.h"

void mallocString(String *ptr,int len)
{
    if (0 < len )
    {
        ptr->chr = (char *)malloc(len);
    }
    else if ((0 >len) || (NULL == ptr->chr))
    {
        fprintf(stderr,"ERROR:Memory Allocation Failed\n");
        exit (1);
    }

}

void getString(String *ptr)
{
    char temp[MAX_STRING_LIMIT];
    int index =0;

    fgets(temp,MAX_STRING_LIMIT,stdin);
    int len = strlen(temp);

    mallocString(ptr,len);

    for (index =0;index<len;index++)
    {
        ptr->chr[index] = temp[index];
    }
    *(ptr->chr +len -1) = '\0';
    ptr->length = strlen(ptr->chr);
}

char *DisplayString(String *ptr)
{
    if (0 > ptr->length)
    {
        fprintf(stderr,"ERROR:string length is 0 no string found ");
        exit (1);
    }
    else
        return ptr->chr;
}
