#include <stdlib.h>
#include <stdio.h>

typedef struct User{
    int sal;
    int id;
}user;

void main(void){

    user *puser = NULL;
    int count = 10;

    puser = (user *)calloc(10 , sizeof(user));

    if(puser == NULL){
        printf("\n calloc failed");
        exit(-1);
    }

    printf("\n calloc success");
    for (count = 0; count < 10; count++){
        puser[count].id = count;
        puser[count].sal = count + 100;
    }
    for (count = 0; count < 10; count++){
        printf("\nuser [%d] id = (%d)",count,puser[count].id);
        printf("\nuser [%d] salary = (%d)",count,puser[count].sal);
    }
    free(puser);
}

