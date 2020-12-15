/* Library in charge of controlling the menu that is printed on the terminal
Created by Andre Felix */
#ifndef OUTPUT_H
#define	OUTPUT_H

void displayInit(void);
void printMenu(void);
void printRead(int inc);
void printAlarmRead(void);
char printProduct(int i);
char printAlarm(int i);
void printAlarmOn(void);
void printMaxTON(void);
void displayUpdateOpt(int i);

#endif	/* OUTPUT_H */