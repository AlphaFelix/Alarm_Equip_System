#include "output.h"
#include "data.h"
#include "stateMachine.h"
#include <stdio.h>
#include <stdlib.h>
#include <bits/stdc++.h> 

#define NUM_IDIOMS 1

//System menu
const char* msgs[STATE_END][NUM_IDIOMS] = {
    {"Sistema de Alarmes\n Digite o numero do produto que deseja trabalhar e aperte enter: \n 1. Equipamentos\n 2. Alarmes\n "},
    {"Menu de Equipamentos\n Digite o numero da funcionalidade que deseja : \n 1. Cadastrar\n 2. Ler\n 3. Modificar\n 4. Deletar\n "},
    {"Cadastro de Equipamentos : \n 0. voltar\n Digite o nome do equipamento : "},
    {" Digite o numero de serie do equipamento : "},
    {" Escolha um tipo : \n 1. Tensao\n 2. Corrente\n 3. Oleo\n "},
    {" Data de cadastro : \n Digite 1 para data local ou digite a data no formato DDMMAAAA : "},
    {"Equipamentos cadastrados : \n 0. voltar\n"},
    {"Modificar Equipamentos : \n Digite o numero do equipamento que deseja modificar :  \n 0. voltar \n"},
    {" 0. voltar \n 1. Nome\n 2. Numero de serie\n 3. Tipo\n 4. Data\n Digite o numero do que deseja alterar : "},
    {"Modificar Equipamento : \n 0. voltar\n Digite o novo nome do equipamento : "},
    {"Modificar Equipamento : \n 0. voltar\n Digite o novo numero de serie : "},
    {"Modificar Equipamento : \n Escolha um tipo : \n 1. Tensao\n 2. Corrente\n 3. Oleo\n "},
    {"Modificar Equipamento : \n Digite a nova data no formato DDMMAAAA : "},
    {"Deletar Equipamento : \n 0. voltar\n"},
    {"Tem certeza que deseja deletar ? 1(sim)/0(nao)\n"},
    {"Menu de Alarmes\n Digite o numero da funcionalidade que deseja : \n 1. Cadastrar\n 2. Ler e Modificar\n 3. Deletar\n "},
    {"Cadastro de Alarmes \n 0. voltar\n Digite a descricao do alarme : "},
    {" Escolha uma classificacao : \n 1. Baixo\n 2. Medio\n 3. Alto\n "},
    {" Escolha o equipamento relacionado : \n 0. voltar\n 1. Nenhum\n"},
    {" Funcionamento do alarme : \n 0. voltar\n 1. Ativado\n 2. Desativado\n "},
    {" Data de cadastro : \n Digite 1 para data local ou digite a data no formato DDMMAAAA : "},
    {"Alarmes cadastrados : \n Comandos : \n ON - Mostra apenas os alarmes acionados; \n OK - Mostra todos os alarmes; \n D - Classificar alarmes pes descricao; \n C - Classificar alarmes pela classificacao; \n Outros - Filtra o conteudo de Outros pela descricao do alarme; \n\n 0. voltar\n"},          
    {"Modificar alarmes : \n 0. voltar\n 1. Descricao\n 2. Classificacao\n 3. Modo\n 4. Data de cadastro\n 5. Equipamento \n Digite o numero do que deseja alterar : \n"},
    {"Modificar alarme : \n 0. voltar\n Digite a nova descricao do alarme : \n"},
    {"Modificar alarme : \n Escolha uma classificacao : \n 0. voltar\n 1. Baixo\n 2. Medio\n 3. Alto\n"},
    {"Modificar alarme : \n 0. voltar\n 1. Alternar modo\n"},
    {"Modificar alarme : \n Digite a nova data no formato DDMMAAAA : \n"},
    {"Modificar alarme : \n Escolha o equipamento relacionado : \n 0. voltar\n 1. Nenhum\n"},
    {"Deletar Alarme : \n 0. voltar\n"},
    {"Tem certeza que deseja deletar ? 1(sim)/0(nao)\n"}    
};

//Clean the screen and print the menu
void displayInit(void){
    system("cls || clear");                              
    printf("%s", msgs[getState()][0]);       
}

//Print the menu without cleaning the screen
void printMenu(void){
    char stateO = getState();      
    printf("%s", msgs[stateO][0]);   
}

//Equipment--------------------------------------------------------------------------------------------------
//Function to print the equipment menu with the possibility to choose the start number in front of the name 
void printRead(int inc){
    for(int i = 0; i<=getI(); i++){                            
        printf(" %d. Nome : %s", (i+1+inc), getEquipName(i));
        printf("    Serie : %s", getEquipSerial(i));
        printf("    Tipo : %s\n", getEquipType(i));
        printf("    Data de cadastro : %d/%d/%d\n", getEquipDay(i),getEquipMonth(i),getEquipYear(i));
    }
}

//Function to print only one equipment
char printProduct(int i){ 
    char temp;
    if(getEquipDay(i)>0){          
        printf("    Nome : %s", getEquipName(i));
        printf("    Serie : %s", getEquipSerial(i));
        printf("    Tipo : %s\n", getEquipType(i));
        printf("    Data de cadastro : %d/%d/%d\n", getEquipDay(i),getEquipMonth(i),getEquipYear(i));
        temp = 1; 
    }            
    else{
        printf(" Numero de equipamento nao existe\n");
        printf(" Digite outro numero : ");   
        temp = -1;
    }      
    return temp;
}

//Options menu to choose the variable that the user wants to change in the equipment update state 
void displayUpdateOpt(int i){
    system("cls || clear");
    printf("Modificar Equipamento\n");
    printf(" Nome : %s", getEquipName(i));
    printf(" Serie : %d", getEquipSerial(i));
    printf("    Tipo : %s\n", getEquipType(i));
    printf(" Data de cadastro : %d/%d/%d\n", getEquipDay(i),getEquipMonth(i),getEquipYear(i));                              
    printf("%s", msgs[getState()][0]); 
}

//Alarm------------------------------------------------------------------------------------------------------
//Function to print all the alarms
void printAlarmRead(void){
    for(int i = 0; i<=getY(); i++){                            
        printf(" %d. Descricao : %s", (i+1), getAlarmDescription(i));
        printf("    Classificacao : %s\n", getAlarmClassification(i));
        printf("    Modo : %s",getAlarmSet(i)?"Ativado":"Desativado");
        printf("    Estado : %s",getAlarmState(i)?"ON":"OFF"); 
        printf("    Ativacoes : %d\n",getAlarmTimesOn(i));  
        printf("    Data de entrada : %d/%d/%d\n", getAlarmInDay(i),getAlarmInMonth(i),getAlarmInYear(i));
        printf("    Data de saida : %d/%d/%d\n", getAlarmOutDay(i),getAlarmOutMonth(i),getAlarmOutYear(i));
        printf("    Data de cadastro : %d/%d/%d\n", getAlarmDay(i),getAlarmMonth(i),getAlarmYear(i));        
        printf("    Equipamento : %s\n\n", getAlarmEquipName(i));
        
    }
}

//Function to print one alarm
char printAlarm(int i){ 
    char temp;
    if(getAlarmDay(i)>0){ 
        printf("    Descricao : %s", getAlarmDescription(i));
        printf("    Classificacao : %s\n", getAlarmClassification(i));
        printf("    Modo : %s",getAlarmSet(i)?"Ativado":"Desativado");
        printf("    Estado : %s",getAlarmState(i)?"ON":"OFF"); 
        printf("    Ativacoes : %d\n",getAlarmTimesOn(i));  
        printf("    Data de entrada : %d/%d/%d\n", getAlarmInDay(i),getAlarmInMonth(i),getAlarmInYear(i));
        printf("    Data de saida : %d/%d/%d\n", getAlarmOutDay(i),getAlarmOutMonth(i),getAlarmOutYear(i));
        printf("    Data de cadastro : %d/%d/%d\n", getAlarmDay(i),getAlarmMonth(i),getAlarmYear(i));        
        printf("    Equipamento : %s\n\n", getAlarmEquipName(i));          
        temp = 1; 
    }            
    else{
        printf(" Numero de alarme nao existe\n");
        printf(" Digite outro numero : ");   
        temp = -1;
    }      
    return temp;
}

//Function to print all the alarms triggered
void printAlarmOn(void){     
    for(int i=0; i<=getY(); i++){        
        if(getAlarmState(i) == true){                      
            printf("   Descricao : %s", getAlarmDescription(i));   
            printf("    Classificacao : %s", getAlarmClassification(i));         
            printf("    Modo : %s",getAlarmSet(i)?"Ativado":"Desativado");
            printf("    Estado : %s\n",getAlarmState(i)?"ON":"OFF");   
            printf("    Data de entrada : %d/%d/%d\n", getAlarmInDay(i),getAlarmInMonth(i),getAlarmInYear(i));
            printf("    Data de saida : %d/%d/%d\n", getAlarmOutDay(i),getAlarmOutMonth(i),getAlarmOutYear(i));     
            printf("    Data de cadastro : %d/%d/%d\n", getAlarmDay(i),getAlarmMonth(i),getAlarmYear(i));        
            printf("    Equipamento : %s\n\n", getAlarmEquipName(i));
        }             
    }    
}

//Print the 3 alarms that were mostly triggered
void printMaxTON(void){    
    unsigned int temp = getMaxTON(0);
    if(temp>0){
        printf(" Alarmes mais atuados : %s %d",getDescriptionTON(0),temp);
        temp = getMaxTON(1);
        if(temp>0){
            printf(", %s %d",getDescriptionTON(1),temp);
            temp = getMaxTON(2);
            if(temp>0){
                printf(", %s %d",getDescriptionTON(2),temp);
            }
        } 
        printf("\n ");
    }    
}


