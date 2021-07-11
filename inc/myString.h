#include<stdio.h>
#include <stdlib.h>


#ifndef _STRING_ADT_
#define _STRING_ADT_

#define MAX_STRING_LIMIT 1024
typedef struct
{
    char *chr;
    int length;
}String;

void mallocString(String *ptr,int len);
void getString(String *ptr);
char *DisplayString(String *ptr);
    
#endif
