/* Library in charge of creating the txt database and manipulating system data
Created by Andre Felix */

#ifndef DATA_H
#define	DATA_H
#include <stdbool.h>

typedef struct{
    unsigned short int day;
    unsigned short int month;
    unsigned int year;    
} date;

typedef struct{
    char name[256];
    char numSerial[256];
    unsigned short int type;
    date equipDate;    
} equipment;

typedef struct{    
    char description[256];
    unsigned short int classification;
    equipment *associated;
    date alarmDate;
    //Data de entrada foi considerado como a data que o alarme foi para on
    date dateOn;
    //Data de saida foi considerado como a data que o alarme foi para off
    date dateOff;
    //Variable to activate and desactivate the alarm    
    bool set;
    //Variable that indicates if the alarm is triggered or not
    bool state; 
    unsigned int timesOn;   
} alarm;

void dataInit(void);
//Equipment functions
void setEquipName(int i, char* name);
char* getEquipName(int i);

void setEquipSerial(int i, char* serial);
char* getEquipSerial(int i);

void setEquipType(int i, unsigned short int type);
const char* getEquipType(int i);

void setEquipLocalTime(int i);
char setEquipDate(int i, unsigned int date);
unsigned int getEquipDay(int i);
unsigned int getEquipMonth(int i);
unsigned int getEquipYear(int i);

void deleteEquip(int i);

int getI(void);
void addI(void);
void subI(void);

//Alarm functions
void setAlarmDescription(int i, char* name);
char* getAlarmDescription(int i);
int cmpAlarmDescription(const void * a, const void * b);
void sortAlarmDescription(void);

void setAlarmClassification(int i, unsigned short int classification);
const char* getAlarmClassification(int i);
int cmpAlarmClassification(const void * a, const void * b);
void sortAlarmClassification(void);

void setAlarmEquip(int i, int w);
char* getAlarmEquipName(int i);

void setAlarmLocalTime(int i);
void setAlarmDateIn(int i);

void setAlarmDateOut(int i);
char setAlarmDate(int i, unsigned int date);
unsigned int getAlarmDay(int i);
unsigned int getAlarmMonth(int i);
unsigned int getAlarmYear(int i);

unsigned int getAlarmInDay(int i);
unsigned int getAlarmInMonth(int i);
unsigned int getAlarmInYear(int i);

unsigned int getAlarmOutDay(int i);
unsigned int getAlarmOutMonth(int i);
unsigned int getAlarmOutYear(int i);

void deleteAlarm(int i);

void alarmMaxTON(void);
unsigned int getMaxTON(int i);
char* getDescriptionTON(int i);
int cmpAlarmTON(const void * a, const void * b);
unsigned int getAlarmTimesOn(int i);


void setAlarmState(int i);
bool getAlarmState(int i);

void toggleAlarmSet(int i);
bool getAlarmSet(int i);

int getY(void);
void addY(void);
void subY(void);

void checkAlarm(void);

//Functions of the state machine
void setEv(int ev);
int getEv(void);

unsigned char getState(void);
void setState(unsigned char newState);

#endif	/* DATA_H */