#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Define a struct for tasks
typedef struct task {
 char name[10];
 int priority;
 int burst;
 int remainingBurst;
 struct task *next;
} Task;

//Function prototypes.
Task* createTask(char *name, int priority, int burst);
void appendTask(Task **head, Task *newTask);
void readFile(char *fileName, Task **head);
void executeTasks(Task **head, int quantum);

int main() {

  //Initialize the head of the list.
  Task *head = NULL;
 
  //Read the file and other functions are called inside this function. Applicable contents
  //Are located within.
  readFile("schedule.txt", &head);
 
  //Execute tasks using round robin with a time quantum of 10 ms
  executeTasks(&head, 10);
 
  return 0;
}

//Function to create a new task node.
Task * createTask(char *name, int priority, int burst) {

  //Allocate memory for a task.
  Task *newTask = (Task *)malloc(sizeof(Task));
 
  //If memory allocation fails, throw an error.
  if (newTask == NULL) {
   perror("Memory allocation error.");
   exit(EXIT_FAILURE);
  }
 
  //Initialize the task variables.
  strcpy(newTask->name, name);
  newTask->priority = priority;
  newTask->burst = burst;
  newTask->remainingBurst = burst;
  newTask->next = NULL;
 
  return newTask;
 
}

//Function to append a task to the end of the singly linked list.
void appendTask(Task **head, Task *newTask) {

 //If the list is empty, add the new task at the head.
  if (*head == NULL) {
   *head = newTask;
  }
  //Otherwise, start from the head and traverse the list until we arrive at the last node.
  else {
   Task *current = *head;
   while (current->next != NULL) {
    current = current->next;
   }
  
   //After the end of the list is reached insert the current task at the end of the list.
   current->next = newTask;
 } 
}

//Function to read file.
void readFile(char *fileName, Task **head) {
  
  //Open the file.
  FILE *file = fopen(fileName, "r");
  
  //If the open operation fails, then throw an error.
  if (file == NULL) {
    perror("Error opening file");
    exit(EXIT_FAILURE);
  }
  
  //Initialize variables.
  char line[512];
  char name[10];
  int priority, burst;
  
  //Read every line from the file.
  while (fgets(line, sizeof(line), file) != NULL) {
  
    //Extract each tasks variables.
    if (sscanf(line, "%[^,], %d, %d", name, &priority, &burst) == 3) {
    
    //Call createTask and insertTask for each task read from the file.
      Task *newTask = createTask(name, priority, burst);
      appendTask(head, newTask);
    }
  }  
  fclose(file);
}

//Function to execute tasks using round robin.
void executeTasks(Task **head, int quantum) {

  Task *current = *head;
  Task *previous = NULL;
  
  //While there is atleast one task in the list.
  while (*head != NULL) {
    //Execute the current task if it has any burst time remaining.
    if (current->remainingBurst > 0) {
    
      //If the remaining burst of the current task is greater than quantum, then set time to qua
      //Otherwise, set time to remaining burst.
      int time = (current->remainingBurst > quantum) ? quantum : current->remainingBurst;

      //Decrease the remaining burst of the current process by the amount of time it was execute
      current->remainingBurst -= time;
    
      //Print the details of the task.
      printf("Executing Task: %s, Priority: %d, Burst Left: %d, Time in Processor: %d ms\n", current->name, current->priority, current->remainingBurst, time);
    }
    
    //Check if the current task is complete.
    if (current->remainingBurst <= 0) {
    
      Task *temp = current;
      
      //If the current task is the head, move the head pointer to the next task, make current the new head, and free the memory
      //of the task that was executed.
      if (current == *head) {
        *head = current->next; //updates the head of the list to be the next task
        current = *head;  //updates the current pointer to be the task at the new head.
        free(temp);     //frees the mem of the task that just ran.
      
      //If the list is empty exit the loop.  
      if (!current) {
        break;
      }
     } 
      else {
        
        //If the current task is not the head, set the next pointer of the previous task to the task following the current task
        //so that the current task is effectively removed from the list,
        //make current the next task, and free the memory of the task that was completed.
        previous->next = current->next; //remove current task from the list.
        current = current->next; //The current task becomes the task following the task to be removed.
        free(temp);
        
        //If current is at the end of the list, then make current the head.
        if (!current) {
          current = *head; //Loop back to beginning of list.
          previous = NULL; //There is no previous task for the head.
        }
      }
    } 
      //If the current task is not complete, then update previous and current.
      else {
        previous = current;
        current = current->next ? current->next : *head; //If current next is not falsy then current becomes the next task otherwise loop back to the head.
      }
    }
  }  