/* Library in charge of creating and controlling the state machine
Created by Andre Felix */
#ifndef STATEMACHINE_H
#define	STATEMACHINE_H

    //States
    enum {
        STATE_MENU,      
        STATE_EQUIPMENT_MENU,  
        STATE_REGISTER_EQUIPMENT_NAME,
        STATE_REGISTER_EQUIPMENT_SERIAL,
        STATE_REGISTER_EQUIPMENT_TYPE,
        STATE_REGISTER_EQUIPMENT_DATE,
        STATE_EQUIPMENT_READ,
        STATE_EQUIPMENT_UPDATE,
        STATE_EQUIPMENT_UPDATE_OPT,
        STATE_EQUIPMENT_UPDATE_NAME,
        STATE_EQUIPMENT_UPDATE_NUM_SERIAL,
        STATE_EQUIPMENT_UPDATE_TYPE,
        STATE_EQUIPMENT_UPDATE_DATE,
        STATE_EQUIPMENT_DELETE,
        STATE_EQUIPMENT_CONFIRM,
        STATE_ALARM_MENU,
        STATE_REGISTER_ALARM_DESCRIPTION,
        STATE_REGISTER_ALARM_CLASSIFICATION,
        STATE_REGISTER_ALARM_EQUIP,
        STATE_REGISTER_ALARM_SET,
        STATE_REGISTER_ALARM_DATE,
        STATE_ALARM_READ,        
        STATE_ALARM_UPDATE,
        STATE_ALARM_UPDATE_DESCRIPTION,
        STATE_ALARM_UPDATE_CLASS,
        STATE_ALARM_UPDATE_SET,
        STATE_ALARM_UPDATE_DATE,
        STATE_ALARM_UPDATE_EQUIP,
        STATE_ALARM_DELETE,
        STATE_ALARM_CONFIRM,         
        STATE_END
    };
    
    void smInit(void);
    void smLoop(void);

#endif	/* STATEMACHINE_H */