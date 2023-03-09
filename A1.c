#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    char ganttChoice[4];
    char useOfProgram[5];

    //Part 1: Creating the inital Gantt
    printf("Welcome to the Gantt generator!\n");
    //Asks the user whether they will use the predermined test example or create their own.
    printf("Would you like to use the test example or create your own Gantt from scratch? (yes/no)\n");
    //Stores their answer to the string ganttChoice.
    scanf("%s", ganttChoice);

    //Checks to see if their answer is a selectable option
    //If their answer is not a selectable option the program will request another choice attempt until it works.
    while((strcmp(ganttChoice, "yes") != 0) && (strcmp(ganttChoice, "no") != 0))
    {
        printf("What you have entered is not a selectable choice. Please choose yes or no\n");
        scanf("%s", ganttChoice);
    }

    //The switch function checks to see if the user's choice was yes or no.
    switch (strcmp(ganttChoice, "yes"))
    {
        case 0:
            //If yes the function for creating the test example is used.
            printf("Y\n");
            //The program then exits the switch function.
            break;
        default:
            //If no the function for creating the user's own Gantt is used.
            printf("N\n");
            //The program then exits the switch function.
            break;
    }

    //Part 2:
    printf("If you wish to edit the Gantt please type ''edit'' / If you wish to run a test, type ''test'' or to exit, type ''quit'' and then press enter to execute your option\n");
    while((strcmp(useOfProgram, "edit") != 0) && (strcmp(useOfProgram, "test") != 0) && (strcmp(useOfProgram, "quit") != 0))
    {
        printf("What you have entered is not a selectable choice. Please choose edit, test, or quit\n");
        scanf("%s", useOfProgram);
    }
    if(strcmp(useOfProgram, "quit") == 0)
    {
        printf("You have selected quit\n");
        printf("Thank you for using the Gantt generator\n");
        exit(0);
    }
    switch (strcmp(useOfProgram, "edit"))
    {
        case 0:
            //If "exit" the function for editing the gantt is used.
            printf("You have selected edit\n");
            //The program then exits the switch function.
            break;
        default:
            //If test the function for testing the Gantt is used.
            printf("You have selected test\n");
            //The program then exits the switch function.
            break;
    }

return 0;

}
