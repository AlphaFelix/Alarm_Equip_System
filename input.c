#include "input.h"
#include <string.h>
#include <stdio.h>
#include <conio.h>

struct termios orig_termios;

//Function to read only after enter (Not ideal)
int readKey(char *word){
    int num;    
    if(kbhit()){       
        if (scanf("%d", &num) != 1){ 
            static char temp[256];          
            fgets(temp, sizeof(temp), stdin);
            strcpy(word,temp);                       
            word[strcspn(word, "\n")] = 0;                           
            num = -1;        
        }            
    } 
    else{
        num = -2;
    }    
    return num;
}



