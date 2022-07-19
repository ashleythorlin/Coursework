#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char* argvp[]){
    
    char str[] = "fuckthisshit";
    char arr[20];

    printf("Starting string: '%s'\n", str);
    printf("Starting array: '%s'\n", arr);

    memset(arr, 0, sizeof(char));

    for(int i = 0; i < strlen(str); i++){
        arr[i] = str[i];
    }
    
    printf("Starting array: ");

    for(int i = 0; i < strlen(str); i++){
        printf("'%c' ", arr[i]);
    }
    
    printf("\n");

    return 0;

}