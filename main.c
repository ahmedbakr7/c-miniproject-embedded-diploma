#include <stdio.h>
#include <stdlib.h>

#define WITH_ENGINE_TEMP_CONTROLLER 0

struct flags{
    int engineState;    // bool
    int ac;             // bool
    int speed;          // velocity
    int roomTemp;       // int
    #if WITH_ENGINE_TEMP_CONTROLLER
    int engineTempController; // bool
    int engineTemp;     // int
    #endif
};

struct flags states={0,0,0,20,0,0};

void vehicleSpeedAction()
{
    if(states.speed==30)
    {
        states.ac=1;
        states.roomTemp=states.roomTemp*(5/4)+1;
    #if WITH_ENGINE_TEMP_CONTROLLER
        states.engineTempController=1;
        states.engineTemp=states.engineTemp*(5/4)+1;
    #endif

    }
}

void trafficLightAction(char traffic)
{
    switch (traffic) {
        case 'G':
        states.speed=100;
            break;
        case 'O':
        states.speed=30;
            break;
        case 'R':
        states.speed=0;
            break;
    }
    vehicleSpeedAction();
    return;
}

void roomTempAction(int temperature)
{
    if(temperature<10 || temperature>30)
    {
        states.ac=1;
        states.roomTemp=20;
    }
    else
    {
        states.ac=0;
        states.roomTemp=temperature;
    }
}
    #if WITH_ENGINE_TEMP_CONTROLLER

void engineTempAction(int engineTemp_)
{
    if(engineTemp_<100 ||engineTemp_>150 )
    {
        states.engineTempController=1;
        states.engineTemp=125;
    }
    else
    {
        states.engineTempController=0;
        states.engineTemp=engineTemp_;
    }
}
    #endif

void actionsMenu()
{
    puts("a. Turn off the engine");    // display the welcome menu
    puts("b. Set the traffic light color.");   // change the
    puts("c. Set the room temperature (Temperature Sensor)");
    #if WITH_ENGINE_TEMP_CONTROLLER
    puts("d. Set the engine temperature (Engine Temperature Sensor)");
    #endif
}

void printVehicleStates()
{
    system("cls");
    printf("Engine is %s\n",states.engineState?"ON":"OFF");
    printf("AC is %s\n",states.ac?"ON":"OFF");
    printf("Vehicle Speed: %d Km/Hr\n",states.speed);
    printf("Room Temperature: %d C\n",states.roomTemp);
    #if WITH_ENGINE_TEMP_CONTROLLER
    printf("Engine Temp Controller is %s\n",states.engineTempController?"ON":"OFF");
    printf("Engine temperature: %d C\n",states.engineTemp);
    #endif
}

void welcomePrompt()
{
    system("cls");
    puts("\ta. Turn on the vehicle engine");    // open Actions menu
    puts("\tb. Turn off the vehicle engine");      // display the welcome menu again
    puts("\tc. Quit the system");          // exit program
}



int main(){
    setvbuf(stdout, NULL, _IONBF,0);
    setvbuf(stderr, NULL, _IONBF, 0);

    while (1) {
        welcomePrompt();
        char userInput;
        scanf(" %c",&userInput);
        switch (userInput)
        {
            case 'a':
                states.engineState=1;
                printVehicleStates();
                actionsMenu();
                break;
            case 'c':
            	puts("bye!!");
                return 1;
                break;
            default:
                continue;
        }
        int breakLoop=0;
        while (!breakLoop)
        {
            scanf(" %c",&userInput);
            switch (userInput)
            {
                char input;
                int inputTemp;
                case 'a':
                    states.engineState=0;
                    breakLoop=1;
                    break;

                case 'b':
                    puts(" enter traffic light:");
                    scanf(" %c",&input);
                    trafficLightAction(input);
                    break;
                case 'c':
                    puts(" enter room temperature:");
                    scanf(" %d",&inputTemp);
                    roomTempAction(inputTemp);
                    break;
                    #if WITH_ENGINE_TEMP_CONTROLLER
                case 'd':
                    puts(" enter engine temperature:");
                    scanf(" %d",&inputTemp);
                    engineTempAction(inputTemp);
                    break;
                    #endif
                default:
                    continue;
            }
            printVehicleStates();
            actionsMenu();
        }
    }
}
