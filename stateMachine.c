#include "stateMachine.h"
#include "data.h"
#include "output.h"
#include "input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Initialize the machine on the first menu 
void smInit(void) {
    setState(STATE_MENU);    
}

//Control the states and variables variations 
void smLoop(void){  
    char word[256];    
    int up = -1;    
    int event = readKey(word);      
    switch (getState()) {        
        case STATE_MENU:                      
            if (event == 1){
                setState(STATE_EQUIPMENT_MENU);
                displayInit();
            } 
            if (event == 2){
                setState(STATE_ALARM_MENU);
                displayInit();
            }  
            break;       

        case STATE_EQUIPMENT_MENU:           
            if (event == 0){
                setState(STATE_MENU); 
                displayInit();                               
            }
            if (event == 1){
                setState(STATE_REGISTER_EQUIPMENT_NAME);                
                displayInit();                                                
            }             
            if(event == 2){
                setState(STATE_EQUIPMENT_UPDATE);
                displayInit(); 
                printRead(0);
            }
            if(event == 3){
                setState(STATE_EQUIPMENT_DELETE);
                displayInit(); 
                printRead(0);
            }
            break;

        case STATE_REGISTER_EQUIPMENT_NAME:           
            if (event == 0){
                setState(STATE_MENU);                 
                displayInit();                               
            }
            if (event == -1){
                setState(STATE_REGISTER_EQUIPMENT_SERIAL);
                setEquipName((getI()+1),word);                
                printMenu();                                
            }                  
            break;       
        
        case STATE_REGISTER_EQUIPMENT_SERIAL:            
            if (event == 0){                
                setState(STATE_REGISTER_EQUIPMENT_NAME);
                displayInit();                                
            }
            if (event ==-1){
                setState(STATE_REGISTER_EQUIPMENT_TYPE);
                setEquipSerial((getI()+1), word); 
                printMenu();
            }
            if (event>0){
                char temp[256];
                itoa(event,temp,10);
                setState(STATE_REGISTER_EQUIPMENT_TYPE);
                setEquipSerial((getI()+1), temp); 
                printMenu();
            } 
            break;

        case STATE_REGISTER_EQUIPMENT_TYPE:             
            if (event == 0){                
                setState(STATE_REGISTER_EQUIPMENT_SERIAL);
                printMenu();                                                
            }
            if (event>0 && event<=3){                
                setState(STATE_REGISTER_EQUIPMENT_DATE);
                setEquipType((getI()+1),event);
                printMenu();                                                
            }                   
            break;

        case STATE_REGISTER_EQUIPMENT_DATE:              
            if (event == 0){                
                setState(STATE_REGISTER_EQUIPMENT_TYPE);
                printMenu();                                                
            }
            if (event == -1){
                printf(" Formato de string nao compativel\n");
                printf(" Digite novamente : "); 
            } 
            if(event==1){
                setEquipLocalTime(getI()+1);
                setState(STATE_EQUIPMENT_UPDATE);
                addI();
                displayInit(); 
                printRead(0);
            }
            if (event > 1){  
                if(setEquipDate(getI()+1, event)>0){
                    setState(STATE_EQUIPMENT_UPDATE);
                    addI();
                    displayInit(); 
                    printRead(0);
                }
                else{
                    printf(" Data nao compativel com o formato DDMMAAAA\n");
                    printf(" Digite novamente : "); 
                }
            }                               
            break;       

        case STATE_EQUIPMENT_UPDATE:            
            if(event == 0){
                setState(STATE_EQUIPMENT_MENU);
                displayInit();
            } 
            else{
                if(event>0 && event<=getI()+1){ 
                    setEv(event - 1);               
                    setState(STATE_EQUIPMENT_UPDATE_OPT);     
                    displayUpdateOpt(event - 1); 
                }                
                else if(event!=-2){
                    printf(" Numero invalido\n Digite outro numero : ");
                }                                        
            }            
            break;

        case STATE_EQUIPMENT_UPDATE_OPT:            
            if(event == 0){
                setState(STATE_EQUIPMENT_UPDATE);
                displayInit();
                printRead(0);
            } 
            if(event==1){
                setState(STATE_EQUIPMENT_UPDATE_NAME);
                displayInit();                                               
            }
            if(event==2){
                setState(STATE_EQUIPMENT_UPDATE_NUM_SERIAL);
                displayInit();                                               
            }
            if(event==3){
                setState(STATE_EQUIPMENT_UPDATE_TYPE);
                displayInit();                                               
            }
            if(event==4){
                setState(STATE_EQUIPMENT_UPDATE_DATE);
                displayInit();                                               
            }
            break;
        
        case STATE_EQUIPMENT_UPDATE_NAME:           
            if (event == 0){
                setState(STATE_EQUIPMENT_UPDATE_OPT);                
                displayUpdateOpt(getEv());                                                              
            }
            if (event == -1){
                up = getEv();
                setState(STATE_EQUIPMENT_UPDATE_OPT);                
                setEquipName(up,word);                                               
                displayUpdateOpt(up);                                                
            }                  
            break;  

        case STATE_EQUIPMENT_UPDATE_NUM_SERIAL:           
            if (event == 0){
                setState(STATE_EQUIPMENT_UPDATE_OPT);                
                displayUpdateOpt(getEv());                                                              
            }
            if (event>0 || event ==-1){
                up = getEv();
                setState(STATE_EQUIPMENT_UPDATE_OPT);
                setEquipSerial(up, word); 
                displayUpdateOpt(up);  
            }                       
            break;

        case STATE_EQUIPMENT_UPDATE_TYPE:           
            if (event == 0){
                setState(STATE_EQUIPMENT_UPDATE_OPT);                
                displayUpdateOpt(getEv());                                                              
            }
            if (event>0 && event<=3){
                up = getEv();
                setState(STATE_EQUIPMENT_UPDATE_OPT);
                setEquipType(up, event); 
                displayUpdateOpt(up);  
            }                         
            break; 

        case STATE_EQUIPMENT_UPDATE_DATE:           
            if (event == 0){
                setState(STATE_EQUIPMENT_UPDATE_OPT);                
                displayUpdateOpt(getEv());                                                              
            }
            if (event == -1){
                printf(" Formato de string nao compativel\n");
                printf(" Digite novamente : "); 
            }
            if (event > 0){ 
                up = getEv();
                if(setEquipDate(up, event)>0){
                    setState(STATE_EQUIPMENT_UPDATE_OPT);                    
                    displayUpdateOpt(up); 
                }
                else{
                    printf(" Data nao compativel com o formato DDMMAAAA\n");
                    printf(" Digite novamente : "); 
                }
            }                                    
            break; 

        case STATE_EQUIPMENT_DELETE :           
            if (event == 0){
                setState(STATE_EQUIPMENT_MENU);                
                displayInit();                                                              
            }            
            if (event > 0 && event<=getI()+1){                
                setState(STATE_EQUIPMENT_CONFIRM); 
                setEv(event-1);                           
                displayInit(); 
                printProduct(event-1);                               
            }                                    
            break;  
        
        case STATE_EQUIPMENT_CONFIRM :
            if (event == 0){
                setState(STATE_EQUIPMENT_DELETE);
                displayInit(); 
                printRead(0);                                                                             
            } 
            if (event == 1){
                setState(STATE_EQUIPMENT_DELETE);
                deleteEquip(getEv());
                subI();
                displayInit(); 
                printRead(0);                                                                             
            }  
            break;

        case STATE_ALARM_MENU:           
            if (event == 0){
                setState(STATE_MENU); 
                displayInit();                               
            }
            if (event == 1){
                setState(STATE_REGISTER_ALARM_DESCRIPTION);                
                displayInit();                                                
            } 
            if(event == 2){
                setState(STATE_ALARM_READ);
                alarmMaxTON();               
                displayInit();                    
                printAlarmRead();
                printMaxTON();
            }            
            if(event == 3){
                setState(STATE_ALARM_DELETE);
                displayInit(); 
                printAlarmRead();
            }           
            break;      
        
        case STATE_REGISTER_ALARM_DESCRIPTION :
            if (event == 0){
                setState(STATE_ALARM_MENU); 
                displayInit();                               
            }              
            if (event == -1){                
                setState(STATE_REGISTER_ALARM_CLASSIFICATION);
                setAlarmDescription((getY()+1), word);
                printMenu();                                                
            }                       
            break;

        case STATE_REGISTER_ALARM_CLASSIFICATION:             
            if (event == 0){                
                setState(STATE_REGISTER_ALARM_DESCRIPTION);
                displayInit();                                                
            }
            if (event > 0 && event<=3){                
                setState(STATE_REGISTER_ALARM_EQUIP);
                setAlarmClassification((getY()+1),event);
                printMenu();                
                printRead(1); 
            }                   
            break;

        case STATE_REGISTER_ALARM_EQUIP:             
            if (event == 0){                
                setState(STATE_REGISTER_ALARM_CLASSIFICATION);
                printMenu();                                                
            }
            if (event > 1 && event<=getI()+2){ 
                setAlarmEquip(getY()+1,event);               
                setState(STATE_REGISTER_ALARM_SET);                
                printMenu();                                                                 
            }     
            if(event==1){                
                setState(STATE_REGISTER_ALARM_SET);
                printMenu();               
            }              
            break;

        case STATE_REGISTER_ALARM_SET :            
            if (event == 0){                
                setState(STATE_REGISTER_ALARM_EQUIP);
                printMenu();                              
                printRead(1);                                                
            }
            if(event==1){
                toggleAlarmSet(getY()+1);
                setState(STATE_REGISTER_ALARM_DATE);
                printMenu();                
            }
            if(event==2){
                setState(STATE_REGISTER_ALARM_DATE);
                printMenu();
            }            
            break;

        case STATE_REGISTER_ALARM_DATE:              
            if (event == 0){                
                setState(STATE_REGISTER_ALARM_SET);
                printMenu();                                                       
            }
            if (event == -1){
                printf(" Formato de string nao compativel\n");
                printf(" Digite novamente : "); 
            } 
            if(event == 1)
            {              
                setAlarmLocalTime(getY()+1);
                setState(STATE_ALARM_READ);
                addY();
                alarmMaxTON();               
                displayInit();                    
                printAlarmRead();
                printMaxTON();

            }
            if (event > 1){  
                if(setAlarmDate(getI()+1, event)>0){
                    setState(STATE_ALARM_READ);                  
                    addY();
                    alarmMaxTON();               
                    displayInit();                    
                    printAlarmRead();
                    printMaxTON();
                }
                else{
                    printf(" Data nao compativel com o formato DDMMAAAA\n");
                    printf(" Digite novamente : "); 
                }
            }                               
            break;
        
        case STATE_ALARM_READ:            
            if(event == 0){
                setState(STATE_ALARM_MENU);
                displayInit();
            }   
            if(event>0){
                setState(STATE_ALARM_UPDATE);
                setEv(event-1);
                displayInit();
                printAlarm(event-1);
            }
            if(event == -1){
                if(strcmp(word,"ON")==0){
                    displayInit(); 
                    printAlarmOn();                                       
                }
                else if(strcmp(word,"OK")==0){
                    displayInit(); 
                    printAlarmRead();                                      
                }
                else if(strcmp(word,"D")==0){ 
                    sortAlarmDescription();                   
                    displayInit(); 
                    printAlarmRead();
                }
                else if(strcmp(word,"C")==0){ 
                    sortAlarmClassification();                   
                    displayInit(); 
                    printAlarmRead();
                }                
                else{
                    displayInit(); 
                    int temp = 0;                  
                    for(int i =0; i<=getY();i++){
                        if(strstr(getAlarmDescription(i),word)!=NULL){
                            printAlarm(i);
                            temp++;
                        }
                    }
                    if(temp<=0){
                        printf(" Descricao nao encontrada\n");
                    }
                }                
            }  
            break; 

        case STATE_ALARM_UPDATE :           
            if (event == 0){
                setState(STATE_ALARM_READ);                
                alarmMaxTON();               
                displayInit();                    
                printAlarmRead();
                printMaxTON();                                                           
            }   
            if (event == 1){
                setState(STATE_ALARM_UPDATE_DESCRIPTION);
                displayInit();
                printf(" Alarme : \n");
                printAlarm(getEv());                 
            }   
            if (event == 2){
                setState(STATE_ALARM_UPDATE_CLASS);
                displayInit();
                printf(" Alarme : \n");
                printAlarm(getEv()); 
            }   
            if (event == 3){
                setState(STATE_ALARM_UPDATE_SET);
                displayInit();
                printf(" Alarme : \n");
                printAlarm(getEv());
            }  
            if (event == 4){
                setState(STATE_ALARM_UPDATE_DATE);
                displayInit();
                printf(" Alarme : \n");
                printAlarm(getEv());
            }
            if (event == 5){
                setState(STATE_ALARM_UPDATE_EQUIP);
                displayInit();
                printRead(1);
                printf(" Alarme : \n");
                printAlarm(getEv());
            }                                                
            break;

        case STATE_ALARM_UPDATE_DESCRIPTION:           
            if (event == 0){
                setState(STATE_ALARM_UPDATE);                
                displayInit();
                printAlarm(getEv());                 
            }
            if (event == -1){
                up = getEv();
                setState(STATE_ALARM_UPDATE_DESCRIPTION);                
                setAlarmDescription(up,word);                                               
                displayInit();
                printf(" Descricao do alarme atualizada\n Alarme : ");
                printAlarm(up);                                            
            }                  
            break;

        case STATE_ALARM_UPDATE_CLASS:           
            if (event == 0){
                setState(STATE_ALARM_UPDATE);                
                displayInit();
                printAlarm(getEv());                 
            }
            if (event > 0){
                up = getEv();
                setState(STATE_ALARM_UPDATE_CLASS);                
                setAlarmClassification(up,event);                                               
                displayInit();
                printf(" Classificacao do alarme atualizada\n Alarme : ");
                printAlarm(up);                                                            
            }                  
            break;

        case STATE_ALARM_UPDATE_SET:           
            if (event == 0){
                setState(STATE_ALARM_UPDATE);                
                displayInit();
                printAlarm(getEv());                 
            }
            if(event==1){
                up = getEv();
                toggleAlarmSet(up);
                displayInit();
                printf(" Modo do alarme atualizado\n Alarme : \n");
                printAlarm(up);    
            }                             
            break; 
        
        case STATE_ALARM_UPDATE_DATE:           
            if (event == 0){
                setState(STATE_ALARM_UPDATE);                
                displayInit();
                printAlarm(getEv());                 
            }
            if(event == 1){              
                setAlarmLocalTime(getEv());           
                displayInit(); 
                printf(" Data de cadastro do alarme atualizada para a local\n Alarme : \n");
                printAlarm(getEv()); 
            }
            if (event > 1){
                up = getEv();  
                if(setAlarmDate(up, event)>0){                                     
                    displayInit(); 
                    printf(" Data de cadastro do alarme atualizada\n Alarme : \n");
                    printAlarm(up);
                }
                else{
                    printf(" Data nao compativel com o formato DDMMAAAA\n");
                    printf(" Digite novamente : "); 
                }
            }                              
            break;

        case STATE_ALARM_UPDATE_EQUIP:             
            if (event == 0){                
                setState(STATE_ALARM_UPDATE);                
                displayInit();
                printAlarm(getEv());                                               
            }
            if(event==1){                
                displayInit(); 
                printf(" Equipamento associado ao alarme atualizado\n Alarme : \n");
                printAlarm(getEv());                   
            } 
            if (event > 1 && event<=getI()+2){ 
                setAlarmEquip(getEv(),event);
                displayInit(); 
                printRead(1);
                printf(" Equipamento associado ao alarme atualizado\n Alarme : \n");
                printAlarm(getEv());                                                                        
            }                                  
            break;             

        case STATE_ALARM_DELETE :           
            if (event == 0){
                setState(STATE_ALARM_MENU);                
                displayInit();                                                              
            }            
            if (event > 0 && event<=getY()+1){                
                setState(STATE_ALARM_CONFIRM); 
                setEv(event-1);                           
                displayInit(); 
                printAlarm(event-1);                               
            }                                    
            break;  
        
        case STATE_ALARM_CONFIRM :
            if (event == 0){
                setState(STATE_ALARM_DELETE);
                displayInit(); 
                printAlarmRead();                                                                             
            } 
            if (event == 1){
                setState(STATE_ALARM_DELETE);
                deleteAlarm(getEv());               
                displayInit(); 
                printAlarmRead();                                                                             
            }  
            break;

        default: setState(STATE_MENU);  
                 displayInit(); 
                 printf("Error");   
            break;        
    }    
    
}