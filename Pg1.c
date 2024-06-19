#include<stdio.h>
#include<string.h>
int main(){
    char str[]="Hello World";
    int i,len;
    len = strlen(str);

    printf("Input string: %s",str);
    printf("\nAfter applying AND operation corresponding ASCII and its values:\n");
    printf("ASCII:");
    for(i=0;i<len;i++){
        printf("\t%d",str[i]&127);
    }
    printf("\nCHAR:");
    for(i=0;i<len;i++){
        printf("\t%c",str[i]&127);
    }
    printf("\nOutput string:");
    for(i=0;i<len;i++){
        printf("%c",str[i]&127);
    }

    printf("\nAfter applying OR operation corresponding ASCII and its values\n");
    printf("ASCII:");
    for(int i=0;i<len;i++){
        printf("\t%d",str[i]|127);
    }
    printf("\nCHAR:");
    for(int i=0;i<len;i++){
        printf("\t%c",str[i]|127);
    }
    printf("\nOutput string:");
    for(i=0;i<len;i++){
        printf("%c",str[i]|127);
    }
    
    printf("\nAfter applying XOR operation corresponding ASCII and its values\n");
    printf("ASCII:");
    for(int i=0;i<len;i++){
        printf("\t%d",str[i]^127);
    }
    printf("\nCHAR:");
    for(int i=0;i<len;i++){
        printf("\t%c",str[i]^127);
    }
    printf("\n\tOoutput string:");
    for(i=0;i<len;i++){
        printf("%c",str[i]^127);
    }
    printf("\n");
   
    return 0;
}