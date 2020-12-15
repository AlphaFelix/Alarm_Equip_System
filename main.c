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
    smInit();
    dataInit();
    displayInit();       
    for(;;)
    {          
        smLoop(); 
        checkAlarm(); 
        saveData();                              
    }

    //It should never arrive here   
    return 0;
}