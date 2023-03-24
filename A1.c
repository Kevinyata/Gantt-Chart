#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_TASKS 10

struct Task {
    char name[20];
    int start_month;
    int end_month;
    int num_dependencies;
    int dependencies[MAX_TASKS];
};

void generate_gantt();
void example_gantt();
void print_gantt(struct Task taskList[], int num_tasks);
void edit_gantt(struct Task taskList[], int num_tasks);
void printDependentTasks(struct Task taskList[], int taskId, int visitedTasks[]);
void checkIfCircular(struct Task taskList[], int dependentTaskId, int resetVisitedTasks);
void among_us();

enum month {january,february,march,april,may,june,july,august,september,october,november,december};
int main()
{
    char ganttChoice[4];

    //Part 1: Creating the inital Gantt
    printf("Welcome to the Gantt generator!\n");
    //Asks the user whether they will use the predermined test example or create their own.
    printf("Would you like to use the test example or create your own Gantt from scratch? (yes/no)\n");
    //Stores their answer to the string ganttChoice.
    scanf("%s", ganttChoice);

    //Checks to see if their answer is a selectable option
    //If their answer is not a selectable option the program will request another choice attempt until it works.
    while((strcasecmp(ganttChoice, "yes") != 0) && (strcasecmp(ganttChoice, "no") != 0))
    {
        printf("What you have entered is not a selectable choice. Please choose yes or no\n");
        scanf("%s", ganttChoice);
    }

    //The switch function checks to see if the user's choice was yes or no.
    switch (strcasecmp(ganttChoice, "yes"))
    {
        case 0:
            //If yes the function for creating the test example is used.
            example_gantt();
            //The program then exits the switch function.
            break;
        default:
            //If no the function for creating the user's own Gantt is used.
            generate_gantt();
            //The program then exits the switch function.
            break;
    }
    return 0;
}

// Function to generate a user-defined gantt
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
        getchar();
        printf("Enter name of task %d:\n", i + 1);
        scanf("%s", taskList[i].name);
        printf("Enter start month of task %d:\n", i + 1);
        scanf("%d", &taskList[i].start_month);

        // Program ensures start month is possible
        while(taskList[i].start_month < 1 || taskList[i].start_month > 12)
        {
            printf("The start month for task %d you entered is invalid. Please enter a number between 1 and 12\n", i + 1);
            scanf("%d", &taskList[i].start_month);
        }

        printf("Enter end month of task %d:\n", i + 1);
        scanf("%d", &taskList[i].end_month);

        // Program ensures end month is possible
        while(taskList[i].end_month < taskList[i].start_month || taskList[i].end_month > 12)
        {
            printf("The end month for task %d you entered is invalid. Please enter a number between %d and 12\n", i + 1, taskList[i].start_month);
            scanf("%d", &taskList[i].end_month);
        }

        printf("How many dependencies does task %d have?\n", i + 1);
        scanf("%d", &taskList[i].num_dependencies);
        for(int j = 0; j < taskList[i].num_dependencies; j++)
        {
            printf("Enter dependency %d of task %d:\n", j + 1, i + 1);
            scanf("%d", &taskList[i].dependencies[j]);
        }
    }
    print_gantt(taskList, num_tasks);
}

// Function to generate an example gantt
void example_gantt()
{

    struct Task taskList[MAX_TASKS] = {
    {"Saving_money", 1, 4, 0},
    {"Research_spots", 1, 2, 0},
    {"Check_hotels", 3, 3, 0},
    {"Check_flights", 3, 3, 0},
    {"Book_hotel", 4, 4, 2},
    {"Book_flight", 4, 4, 2},
    {"Book_trip", 4, 4, 2},
    {"Plan_activities", 6, 8, 0},
    {"Pack", 8, 8, 1},
    {"Enjoy_trip", 8, 8, 2},
    };

    taskList[4].dependencies[0] = 0;
    taskList[4].dependencies[1] = 2;
    taskList[5].dependencies[0] = 0;
    taskList[5].dependencies[1] = 3;
    taskList[6].dependencies[0] = 4;
    taskList[6].dependencies[1] = 5;
    taskList[8].dependencies[0] = 6;
    taskList[9].dependencies[0] = 6;
    taskList[9].dependencies[1] = 7;

    print_gantt(taskList, MAX_TASKS);
}

// Function to print the generated gantt
void print_gantt(struct Task taskList[], int num_tasks)
{
    // Print Gantt chart
    printf("\n");
    for (int i = 0; i < 130; i++)
    {
        printf("_");
    }
    printf("\n");
    printf("\t\t| Jan\t| Feb\t| Mar\t| Apr\t| May\t| Jun\t| Jul\t| Aug\t| Sep\t| Oct\t| Nov\t| Dec\t| Dependencies\n");
    for (int i = 0; i < num_tasks; i++)
    {
        for(int j = 0; j < 130; j++)
        {
            printf("-");
        }
        printf("\n");
        if(strlen(taskList[i].name) >= 8)
        {
            printf("%s\t", taskList[i].name);
        }
        if(strlen(taskList[i].name) < 8)
        {
            printf("%s\t\t", taskList[i].name);
        }

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
    for(int j = 0; j < 130; j++)
    {
        printf("-");
    }
    printf("\n");

    //Part 2:
    char useOfProgram[5];
    int visitedTasks[10];
    char testtask[20];
    printf("If you wish to edit the Gantt please type ''edit'' / If you wish to run a test, type ''test'' or to exit, type ''quit'' and then press enter to execute your option\n");
    scanf("%s", useOfProgram);
    while((strcasecmp(useOfProgram, "edit") != 0) && (strcasecmp(useOfProgram, "test") != 0) && (strcasecmp(useOfProgram, "quit") != 0))
    {
        printf("What you have entered is not a selectable choice. Please choose edit, test, or quit\n");
        scanf("%s", useOfProgram);
    }
    if(strcasecmp(useOfProgram, "quit") == 0)
    {
        printf("You have selected quit\n");
        printf("Thank you for using the Gantt generator\n");
        among_us(); // print ascii art
        return 0;
    }
    switch (strcasecmp(useOfProgram, "edit"))
    {
        case 0:
            //If "exit" the function for editing the gantt is used.
            printf("You have selected edit\n");
            edit_gantt(taskList, num_tasks);
            //The program then exits the switch function.
            break;
        default:
            //If test the function for testing the Gantt is used.
            printf("You have selected test\n");
            printf("Please enter the task name to test:\n");
            scanf("%s", testtask);
            for(int comp = 0; comp < num_tasks; comp++)
            {
                if(strcasecmp(testtask, taskList[comp].name) == 0)
                {
                    num_tasks = comp;
                }
            }
            printDependentTasks(taskList, num_tasks, visitedTasks);
            //The program then exits the switch function.
            break;
    }
}
//Function to edit the gantt
void edit_gantt(struct Task taskList[], int num_tasks)
{
    char taskedit[20];
    printf("Please enter the task name you want to change exactly.\n");
    scanf("%s", taskedit);
    for(int compare = 0; compare < num_tasks; compare++) //compare the amount of tasks
    {
        if(strcasecmp(taskedit, taskList[compare].name) == 0) //if task entered is same as a task listed
        {
            printf("Please enter the new task name or write its old one:\n");
            scanf("%s", taskList[compare].name);
            printf("Please enter the start month (1-12):\n");
            scanf("%d", &taskList[compare].start_month);
            while(taskList[compare].start_month < 1 || taskList[compare].start_month > 12) //To stop from entering invalid start month
            {
                printf("The start month you entered is invalid. Please enter a number between 1 and 12:\n");
                scanf("%d", &taskList[compare].start_month);
            }
            printf("Please enter the end month (%d-12):\n", taskList[compare].start_month);
            scanf("%d", &taskList[compare].end_month);
            while(taskList[compare].end_month < taskList[compare].start_month || taskList[compare].end_month > 12) //To stop from entering an invalid end month
            {
                printf("The end month you entered is invalid. Please enter a number between %d and 12:\n", taskList[compare].start_month);
                scanf("%d", &taskList[compare].end_month);
            }
            printf("Enter how many dependencies this task has:\n");
            scanf("%d", &taskList[compare].num_dependencies);
            for(int depend = 0; depend < taskList[compare].num_dependencies; depend++)
            {
                printf("Enter dependency %d of this task:\n", depend + 1);
                scanf("%d", &taskList[compare].dependencies[depend]);
            }
        }
    }
    print_gantt(taskList, num_tasks);
}
//function to check for circular dependencies
void printDependentTasks(struct Task taskList[], int taskId, int visitedTasks[])
{
    printf("%d - > ", taskId); //print current dependency
    visitedTasks[taskId] = 0; //mark dependency as visited

    for (int x = 0; x < taskList[taskId].num_dependencies; x++) //to go through every dependency for the current task
    {
        int dependentTaskId = taskList[taskId].dependencies[x]; //to go to the next task

        if(visitedTasks[dependentTaskId] != 0) //to check if the task has already been checked
        {
            printDependentTasks(taskList, dependentTaskId, visitedTasks); //recursvie call
        }

        else
        {
            printf("( !!!!!!!!! warning potential circular dependency !!!!!!!!!!!!!)\n");
            taskId = dependentTaskId; // for use in circular dependency function
            checkIfCircular(taskList, taskId, dependentTaskId); //recursive call to check for circular dependency
        }
    }
}
//function to check for circular dependencies
void checkIfCircular(struct Task taskList[],int TaskId, int dependentTaskId)
{
    printf("%d - > ", dependentTaskId); // print current dependency

    for(int r = 0; r < taskList[dependentTaskId].num_dependencies; r++) //to go through every dependency for the current task
    {
         dependentTaskId = taskList[dependentTaskId].dependencies[r]; //to go to next task

         if(dependentTaskId != TaskId) //if task is not the same as the first task call function again
         {
             checkIfCircular(taskList, TaskId, dependentTaskId); //recursive call
         }

         else //if task is the same as the first task it is a circular dependency
         {
             printf("Circuar Dependency Found!!!\n");
             break;
         }
    }
    if(taskList[dependentTaskId].num_dependencies == 0) //if no circular dependencies are found
    {
        printf("Circular Dependency Not Found.\n");
    }
}

//function for ascii art
void among_us()
{
printf("\n          ,@@@@@@@@@@@@@@@@@@                                \n");
printf("           @@@%%%%%%%%%%%%%%%%%%%%%%%%%%%%%@@@@@               \n");
printf("          @@@%%%%%%%%%%%%%%%%&&&&&&&&&&&&&&&,                  \n");
printf("         @@@&%%%%%%%%%%%&&&&*,,,,,,     ,#&&&                  \n");
printf("      ,%@@@&&%%%%%%%%%%%&&&(/,,,,,,,,,,    ,&&&                \n");
printf("  @@@@@@@@@&&%%%%%%%%&&&(((/,,,,,,,,,,,,,%%&&                  \n");
printf(" %%@@%%%%%%%%@@@&&%%%%%%%%&&&#((((((((((((((((&&&              \n");
printf(" @@&&&&&@@@&&%%%%%%%%%%&&&&&&#(((((#%%&&&&&&.                  \n");
printf(" @@&&&&&@@@&&%%%%%%%%%%%%%%%%%%%%&&&&&&&&&&%%%%&@@             \n");
printf("*@@&&&&&@@@&&%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%@@  \n");
printf("%%@@&&&&&@@@&&&%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%&@@   \n");
printf("/@@&&&&&@@@&&&&%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%&&@@      \n");
printf(" @@&&&&&@@@&&&&&&%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%&&&@@@          \n");
printf(" @@@&&&&@@@&&&&&&&&&&&&&&&&&&&&&&&&@@&                         \n");
printf("  @@@&&&@@@&&&&&&&&&&&&&&&&&&&&&&&&@@                          \n");
printf("    (@@@@@@&&&&&&&&&@@@@@@@@&&&&&&@@@                          \n");
printf("         @@&&&&&&&&&@@  @@&&&&&&&&@@                           \n");
printf("         @@&&&&&&&&&@@  @@@&&&&&&@@@                           \n");
printf("         @@@&&&&&&&@@@   @@@@@@@@@                             \n");
printf("           @@@@@@@@                                            \n");
}
