#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_TASKS 10

void generate_gantt();

enum month {january,february,march,april,may,june,july,august,september,october,november,december};
struct Task {
    char name[10];
    int start_month;
    int end_month;
    int num_dependencies;
    int dependencies[];
};


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
            generate_gantt();
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

void generate_gantt()
{
    int num_tasks;
    struct Task taskList[MAX_TASKS];

    // Function requests the number of tasks to be used in the gantt table from the user
    printf("Enter number of tasks(1-10): \n");
    scanf("%d", &num_tasks);

    // Program ensures the number of tasks is possible
    while(num_tasks > MAX_TASKS || num_tasks < 1)
    {
        printf("The amount of tasks you entered is invalid. Please enter a number between 1 and 10\n");
        scanf("%d", num_tasks);
    }

    // Read in task names, start months, end months and dependencies to a struct
    for (int i = 0; i < num_tasks; i++)
    {
        printf("Enter name of task %d:\n", i + 1);
        scanf("%s", taskList[i].name);
        printf("Enter start month of task %d:\n", i + 1);
        scanf("%d", &taskList[i].start_month);

        // Program ensures start month is possible
        while(taskList[i].start_month < 1 || taskList[i].start_month > 12)
        {
            printf("The start month for task %d you entered is invalid. Please enter a number between 1 and 12", i + 1);
        }

        printf("Enter end month of task %d:\n", i + 1);
        scanf("%d", &taskList[i].end_month);

        // Program ensures end month is possible
        while(taskList[i].end_month < taskList[i].start_month || taskList[i].end_month > 12)
        {
            printf("The end month for task %d you entered is invalid. Please enter a number between %d and 12", i + 1, taskList[i].start_month);
        }

        printf("How many dependencies does task %d have?\n", i + 1);
        scanf("%d", &taskList[i].num_dependencies);
        for(int j = 0; j < taskList[i].num_dependencies; j++)
        {
            printf("Enter dependency %d of task %d:\n", j + 1, i + 1);
            scanf("%d", &taskList[i].dependencies[j]);
        }
    }

    // Print Gantt chart
    printf("\n");
    for (int i = 0; i < 120; i++) {
        printf("_");
    }
    printf("\n");
    printf("\t\t| Jan\t| Feb\t| Mar\t| Apr\t| May\t| Jun\t| Jul\t| Aug\t| Sep\t| Oct\t| Nov\t| Dec\t| Dependencies\n");
    for (int i = 0; i < num_tasks; i++)
    {
        printf("%s\t\t", taskList[i].name);
        for(int j = 1; j <= 12; j++)
        {
            if(j <= taskList[i].end_month && j >= taskList[i].start_month)
            {
                printf("| XXX\t");
            }
            else
            {
                printf("|\t");
            }
        }
        printf("|");
        for (int k = 0; k < taskList[i].num_dependencies; k++)
        {
            printf("%d ", taskList[i].dependencies[k]);
        }
        printf("\n");
    }
}
