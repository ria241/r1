#include <stdio.h>
typedef enum {
    IDLE,
    STOP,
    START,
    CHANGESPEED
} state_t;

state_t state = IDLE;

int haltEvent = 0;
int setSpeedEvent = 0;
int speed = 0;
void setSpeed()
{
    printf("\n enter the speed you want to set for the motor,current speed is %d\n",speed);
    scanf("%d",&speed);
    printf("\n speed set to %d\n",speed);
}

void changeSpeed() {
    printf("Changing the speed of the motor\n");
}

void startMotor() {
    printf("Motor starting up\n");
}

void stopMotor() {
    printf("Motor stopping\n");
    state = STOP;
    printf("Motor stopped\n");
    speed = 0;
}

void haltMotor()
{
    printf("Command for halting the vehicle logging in ...\n");
    printf("going to stop state\n");
}

int main() {
    char input;

     do{
        printf("Enter event (h = Halt, s = SetSpeed): ");
        scanf(" %c", &input);
        if (input == 'h')
        {
            haltEvent = 1;
        } else if (input == 's')
        {
            setSpeedEvent = 1;
        }
        else
        {
            printf("try again/n");
            printf("Enter event (h = Halt, s = SetSpeed): ");
            scanf(" %c", &input);
        }
        switch (state) {
            case IDLE:
                if (setSpeedEvent)
                {
                    setSpeed();
                    startMotor();
                    state = START;
                    setSpeedEvent = 0;
                }
                else
                {
                    printf("Motor already on idle state , cant halt it , try again.. \n");
                    haltEvent = 0;
                }
                break;
            /*case STOP:
                printf("Motor stopped")
                state = IDLE;
                break;*/
            case START:
                if (haltEvent)
                {
                    haltMotor();
                    stopMotor();
                    state = IDLE;
                    printf("In idle state now\n");
                    haltEvent = 0;
                } else {
                    changeSpeed();
                    setSpeed();
                    state = CHANGESPEED;
                    setSpeedEvent = 0;
                }
                break;
            case CHANGESPEED:
                if (setSpeedEvent)
                {
                    changeSpeed();
                    setSpeed();
                    state = CHANGESPEED;
                    setSpeedEvent = 0;
                }
                else
                {
                    stopMotor();
                    state = IDLE;
                    printf("In idle state now\n");
                    haltEvent = 0;
                }
                break;
        }
    }while (input == 'h' || input == 's');
    printf("wrong input , code terminated\n");
}

