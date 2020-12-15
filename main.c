//Basic
#include <stdio.h>
#include <stdlib.h>
//Created
#include "data.h"
#include "output.h"
#include "input.h"
#include "stateMachine.h"

int main(int argc, char *argv[ ] )
{   
    FILE *database; 
       
    //Open or create file
    database = fopen("data.txt", "a");
    /*if (database == NULL)
    {
        printf("ERRO! O arquivo não foi aberto!\n");
    }
    else
    {
        printf("O arquivo foi aberto com sucesso!");
        //Close the file
        fclose(database);
    }*/
    smInit();
    dataInit();
    displayInit();       
    for(;;)
    {          
        smLoop(); 
        checkAlarm();                        
    }

    //It should never arrive here   
    return 0;
}