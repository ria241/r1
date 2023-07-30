#include<stdio.h>
#include<string.h>
typedef enum
{
    idle,
    start,
    change_speed,
    stop,
    MAX_STATE
} motor_state;

typedef enum
{
    setspeed,
    halt,
    MAX_EVENT
} motor_event;
motor_state state = idle;
motor_state noevent_handler(void)
{
    printf("sorry wrong input\n");
    return state;
}
motor_state idle_setspeed_handler(void)
{
    int speed = 0;
    printf("motor in idle state , enter the speed to start \n");
    scanf("%d",&speed);
    printf("speed set to %d\n",speed);
     printf("motor started  \n");
    return start;
}
motor_state start_setspeed_handler(void)
{
    int speed;
    printf(" input speed to change \n");
    scanf("%d",&speed);
    printf("speed set to %d\n",speed);
    return change_speed;
}
motor_state start_halt_event_handler(void)
{
    printf("motor put to halt,stopping it\n");
    printf("motor stopped\n");
    return stop;
}
motor_state cs_setspeed_handler(void)
{
    int speed;
    printf("input the speed to change speed \n",speed);
    scanf("%d",&speed);
    printf("speed set to %d\n",speed);
    return change_speed;
}
motor_state cs_halt_event_handler(void)
{
    printf("motor put to halt,stopping it\n");
    printf("motor stopped\n");
    return stop;
}
motor_state stop_halt_event_handler(void)
{
    printf("motor in idle state\n");
    return idle;
}
motor_event read_event()
{
        char input;
        fflush(stdin);
        printf("enter input , (s for set speed , h for halt)\n");
        scanf("%c",&input);
        if(input == 's')
        {
            return setspeed;
        }
        else if(input == 'h')
        {
            return halt;
        }

}
int main()
{
    char input;
    motor_event event;

    motor_state (*fsm[MAX_STATE][MAX_EVENT])(void)= {
        {idle_setspeed_handler, noevent_handler},
        {start_setspeed_handler,start_halt_event_handler},
        {cs_setspeed_handler,cs_halt_event_handler},
        {noevent_handler,stop_halt_event_handler}
    };

        while(1)
        {
            motor_event event = read_event();
            // function call as per the state and event and return the next state of the finite state machine
            state = (fsm[state][event]());
        }

}
