#include "data.h"
#include "output.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Variable responsible for maintaining the state of the machine
static unsigned char state;

//Variable that counts the amount of equipment registered
int x = -1;

//Variable that counts the amount of alarm registered
int z = -1;

//Keeps track of the product that is being modified
int event = -1;
//A Flag to indicate reorganization in the alarm vector struct 
bool change = false;

struct tm *locTime;
time_t secs;

//The maximum amount of products and characters in strings is set to 256
equipment equipamentos[256];
alarm alarmes[256];
//Struct sorted by the number of times the alarm was triggered
alarm sortTON[256];

bool alarmFlag[256];

//Read the data from the database or initialize the data with NULL if the txt does not exist
void dataInit(void){  
    FILE *database;   
    //Open or create file
    database = fopen("data.txt", "a+");  
    if (database == NULL)
    {
        printf("ERRO! O arquivo não foi aberto!\n");
        for(int i=0; i<256; i++) {
            strcpy(equipamentos[i].name, "NULL");
            strcpy(equipamentos[i].numSerial, "NULL");
            equipamentos[i].type = 0;
            equipamentos[i].equipDate.day = 0;
            equipamentos[i].equipDate.month = 0;
            equipamentos[i].equipDate.year = 0;

            strcpy(alarmes[i].description, "NULL");
            alarmes[i].classification = 0;
            alarmes->associated = NULL;
            alarmes[i].state = true; 
            alarmes[i].timesOn = 0;

            alarmFlag[i] = false;

            //Test only 
            alarmes[i].set = false;                      
        }
    }
    else
    {
        fscanf(database, "%d_%d", &x,&z);        
        for(int i = 0; i<=x;i++){
            fscanf(database, "%s %s %d_%d/%d/%d\n", &equipamentos[i].name, &equipamentos[i].numSerial, &equipamentos[i].type, &equipamentos[i].equipDate.day, &equipamentos[i].equipDate.month, &equipamentos[i].equipDate.year);
        }
        for(int j = 0; j<=z;j++){
            int index = 0;
            fscanf(database, "%s\n%d_%d/%d/%d_%d/%d/%d_%d/%d/%d_%d_%d_%d_%d_%d\n", &alarmes[j].description, &alarmes[j].classification,&alarmes[j].alarmDate.day,&alarmes[j].alarmDate.month,&alarmes[j].alarmDate.year,&alarmes[j].dateOn.day,&alarmes[j].dateOn.month,&alarmes[j].dateOn.year,&alarmes[j].dateOff.day,&alarmes[j].dateOff.month,&alarmes[j].dateOff.year,&alarmes[j].set,&alarmes[j].state,&alarmes[j].timesOn,&alarmFlag[j],&index);    
            if(index<256)
            {
                alarmes[j].associated = &equipamentos[index];
            }
        }
        printf("O arquivo foi aberto com sucesso!");        
    }
    //Close the file
    fclose(database);
    
}

//Equipment------------------------------------------------------------------------------------------------
void setEquipName(int i, char* name){
    strcpy(equipamentos[i].name, name);    
}

char* getEquipName(int i){    
    return equipamentos[i].name;
}

void setEquipSerial(int i, char* serial){
    strcpy(equipamentos[i].numSerial, serial);       
}

char* getEquipSerial(int i){    
    return equipamentos[i].numSerial;
}

void setEquipType(int i, unsigned short int type){
    equipamentos[i].type = type % 4;      
}

//Return the type of the equipment as a string
const char* getEquipType(int i){
    const char *temp;
    switch(equipamentos[i].type){
        case 0 :
            temp = "Nao definido";
            break;
        case 1 :
            temp = "Tensao";
            break;
        case 2 :
            temp = "Corrente";
            break;
        case 3 :
            temp = "Oleo";
            break;
        default : 
            temp = "Nao definido";
            break;        
    }
    return temp;         
}

//Save the date of the computer in the equipment registe date
void setEquipLocalTime(int i){
    time(&secs);
    locTime = localtime(&secs);
    equipamentos[i].equipDate.day = locTime->tm_mday;
    equipamentos[i].equipDate.month = locTime->tm_mon+1;
    equipamentos[i].equipDate.year = locTime->tm_year+1900;   
}

//Save the date using the int DDMMYYYY
char setEquipDate(int i, unsigned int date){   
    equipamentos[i].equipDate.day = date/1000000;    
    equipamentos[i].equipDate.month = (date/10000)%100;     
    equipamentos[i].equipDate.year = date%10000;    
    if(equipamentos[i].equipDate.day>31 || equipamentos[i].equipDate.day<1 || equipamentos[i].equipDate.month>12 || equipamentos[i].equipDate.month<1){
        return -1;
    }    
    return 1; 
}

unsigned int getEquipDay(int i){  
    return equipamentos[i].equipDate.day;       
}

unsigned int getEquipMonth(int i){
    return equipamentos[i].equipDate.month;       
}

unsigned int getEquipYear(int i){
    return equipamentos[i].equipDate.year;       
}

//Replace the deleted values with the following values
void deleteEquip(int i){    
    for(int y=i; y<=x; y++) {
        strcpy(equipamentos[y].name, equipamentos[y+1].name);
        strcpy(equipamentos[y].numSerial, equipamentos[y+1].numSerial);        
        equipamentos[y].type = equipamentos[y+1].type;
        equipamentos[y].equipDate.day = equipamentos[y+1].equipDate.day;
        equipamentos[y].equipDate.month = equipamentos[y+1].equipDate.month;
        equipamentos[y].equipDate.year = equipamentos[y+1].equipDate.year;              
    }
}

//It counts the quantity of equipments registered
int getI(void){
    return x;
}

void addI(void){
    x++;
}

void subI(void){
    x--;
}

//Alarm----------------------------------------------------------------------------------------------
void setAlarmDescription(int i, char* description){
    strcpy(alarmes[i].description, description);     
}
char* getAlarmDescription(int i){    
    return alarmes[i].description;
}

void setAlarmClassification(int i, unsigned short int classification){
    alarmes[i].classification = classification % 4;      
}

const char* getAlarmClassification(int i){
    const char *temp;
    switch(alarmes[i].classification){
        case 0 :
            temp = "Nao definido";
            break;
        case 1 :
            temp = "Baixo";
            break;
        case 2 :
            temp = "Medio";
            break;
        case 3 :
            temp = "Alto";
            break;
        default : 
            temp = "Nao definido";
            break;        
    }
    return temp;         
}

//Save the date of the computer
void setAlarmLocalTime(int i){
    time(&secs);
    locTime = localtime(&secs);
    alarmes[i].alarmDate.day = locTime->tm_mday;
    alarmes[i].alarmDate.month = locTime->tm_mon+1;
    alarmes[i].alarmDate.year = locTime->tm_year+1900;   
}

//Save the date of the computer
void setAlarmDateIn(int i){
    time(&secs);
    locTime = localtime(&secs);
    alarmes[i].dateOn.day = locTime->tm_mday;
    alarmes[i].dateOn.month = locTime->tm_mon+1;
    alarmes[i].dateOn.year = locTime->tm_year+1900;   
}

//Save the date of the computer
void setAlarmDateOut(int i){
    time(&secs);
    locTime = localtime(&secs);
    alarmes[i].dateOff.day = locTime->tm_mday;
    alarmes[i].dateOff.month = locTime->tm_mon+1;
    alarmes[i].dateOff.year = locTime->tm_year+1900;   
}

//Takes the int ddmmyyyy and transfer it to the the variables in the alarm date struct 
char setAlarmDate(int i, unsigned int date){   
    unsigned short int day = date/1000000;  
    unsigned short int month = (date/10000)%100;
    unsigned int year = date%10000;
    if(day>31 || day<1 || month>12 || month<1){
        return -1;
    } 
    else{
        alarmes[i].alarmDate.day = day;    
        alarmes[i].alarmDate.month = month;     
        alarmes[i].alarmDate.year = year; 
    }   
    return 1; 
}

unsigned int getAlarmDay(int i){  
    return alarmes[i].alarmDate.day;       
}

unsigned int getAlarmMonth(int i){
    return alarmes[i].alarmDate.month;       
}

unsigned int getAlarmYear(int i){
    return alarmes[i].alarmDate.year;       
}

unsigned int getAlarmInDay(int i){  
    return alarmes[i].dateOn.day;       
}

unsigned int getAlarmInMonth(int i){
    return alarmes[i].dateOn.month;       
}

unsigned int getAlarmInYear(int i){
    return alarmes[i].dateOn.year;       
}

unsigned int getAlarmOutDay(int i){  
    return alarmes[i].dateOff.day;       
}

unsigned int getAlarmOutMonth(int i){
    return alarmes[i].dateOff.month;       
}

unsigned int getAlarmOutYear(int i){
    return alarmes[i].dateOff.year;       
}

//Associate an alarm to an equipment
void setAlarmEquip(int i, int w){
    alarmes[i].associated = &equipamentos[i];
}
char* getAlarmEquipName(int i){
    return alarmes[i].associated->name;
}

//Delete the alarm and reorganize the vector
void deleteAlarm(int i){    
    for(int y=i; y<=z; y++) {
        strcpy(alarmes[y].description, alarmes[y+1].description);
        alarmes[y].classification = alarmes[y+1].classification;
        alarmes[y].associated = alarmes[y+1].associated;
        alarmes[y].dateOn = alarmes[y+1].dateOn;
        alarmes[y].dateOff = alarmes[y+1].dateOff;        
        alarmes[y].set = alarmes[y+1].set; 
        alarmes[y].state = alarmes[y+1].state; 
        alarmes[y].timesOn = alarmes[y+1].timesOn;                            
    }
    change = true;
    z--;
}

unsigned int getAlarmTimesOn(int i){
    return alarmes[i].timesOn;          
}
//Used only for tests
void toggleAlarmSet(int i){
    alarmes[i].set = !alarmes[i].set;  
}

bool getAlarmSet(int i){
    return alarmes[i].set;  
}

bool getAlarmState(int i){
    return alarmes[i].state;          
}

//Check if the alarm was turned on or off and print a message
void checkAlarm(void){    
    for(int i = 0; i<=z; i++){
        bool temp = getAlarmState(i);
        if(change == false)
        {
            if(temp==true && alarmFlag[i]!=temp){
            setAlarmDateIn(i); 
            displayInit();
            printf("\n Alarme %s Acionado/ON\n", getAlarmDescription(i)); 
            alarmes[i].timesOn++;                      
            }
            else if(temp==false && alarmFlag[i]!=temp){
                setAlarmDateOut(i);
                displayInit();
                printf("\n Alarme %s Desacionado/OFF\n", getAlarmDescription(i));
            }
        }
        
        alarmFlag[i] = temp;
        change = false;
    }
}

//Basic comparison function used in qsort
int cmpAlarmTON(const void * a, const void * b){
    alarm *alarmA = (alarm *)a;
    alarm *alarmB = (alarm *)b;
    return (alarmB->timesOn-alarmA->timesOn);
}

//Sort the structure in descending timesOn order 
void alarmMaxTON(void){            
    for(int i =0; i<=z;i++){
        sortTON[i].timesOn = alarmes[i].timesOn;
        strcpy(sortTON[i].description,alarmes[i].description);
    }  
    qsort(sortTON,z+1,sizeof(alarm),cmpAlarmTON);     
}

//Select the value of the vector sorted according to the number of times it was triggered 
unsigned int getMaxTON(int i){     
    return sortTON[i].timesOn;  
}

char* getDescriptionTON(int i){    
    return sortTON[i].description;  
}

//Basic comparison function used in qsort
int cmpAlarmDescription(const void * a, const void * b){
    alarm *alarmA = (alarm *)a;
    alarm *alarmB = (alarm *)b;   
    int result = strcmp(alarmA->description,alarmB->description);
    if(result!=0){
        return result;
    }
    return 0;
}

//Sort the structure in alphabetical order of description
void sortAlarmDescription(void){  
    change = true; 
    qsort(alarmes,z+1,sizeof(alarm),cmpAlarmDescription);
}

//Basic comparison function used in qsort
int cmpAlarmClassification(const void * a, const void * b){
    alarm *alarmA = (alarm *)a;
    alarm *alarmB = (alarm *)b;
    return (alarmA->classification-alarmB->classification);    
}

//Sort the structure in alphabetical order of classification
void sortAlarmClassification(void){  
    change = true; 
    qsort(alarmes,z+1,sizeof(alarm),cmpAlarmClassification);
}

//Y counts the quantity of alarms registered
int getY(void){
    return z;
}

void addY(void){
    z++;
}

void subY(void){
    z--;
}

//State machine--------------------------------------------------------------------------------------
unsigned char getState(void){
    return state;
}

void setState(unsigned char newState){
    state = newState;
}

void setEv(int ev){
    event = ev;
}

int getEv(void){
    return event;
}

//Save the equipments and alarms to the txt database
void saveData(void){
    FILE *database;      
    //Open or create file
    database = fopen("./data.txt", "w");  
    if (database == NULL)
    {
        printf("ERRO! O arquivo nao foi aberto!\n");
    }
    else 
    {   
        fprintf(database, "%d_%d\n",x,z);
        for(int i=0; i<=x; i++){
            if(fprintf(database, "%s\n%s\n%d_%d/%d/%d\n", equipamentos[i].name, equipamentos[i].numSerial,equipamentos[i].type, equipamentos[i].equipDate.day, equipamentos[i].equipDate.month, equipamentos[i].equipDate.year)<0)         
                printf("ERRO! Ao gravar o arquivo!\n");  
        } 
        for(int j=0; j<=z; j++){
            if(fprintf(database, "%s\n%d_%d/%d/%d_%d/%d/%d_%d/%d/%d_%d_%d_%d_%d_%d\n", alarmes[j].description,
                alarmes[j].classification,
                alarmes[j].alarmDate.day, alarmes[j].alarmDate.month, alarmes[j].alarmDate.year,
                alarmes[j].dateOn.day, alarmes[j].dateOn.month, alarmes[j].dateOn.year,
                alarmes[j].dateOff.day, alarmes[j].dateOff.month, alarmes[j].dateOff.year,
                alarmes[j].set, alarmes[j].state, alarmes[j].timesOn,alarmFlag[j],(alarmes[j].associated-equipamentos))<0)         
                printf("ERRO! Ao gravar o arquivo!\n");
        }                 
    }     
    //Close the file
    fclose(database);    
}
