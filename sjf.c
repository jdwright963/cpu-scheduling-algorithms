#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Define a task struct.
typedef struct task {
  char name[10];
  int priority;
  int burst;
  
  //A Pointer to the next task.
  struct task *next; 
} Task;

//Function prototypes.
void insertTask(Task **head, Task *newTask);
Task* createTask(char *name, int priority, int burst);
void readFile(char *filename, Task **head);
void executeTasks(Task *head);

int main() {

  //Initialize the head of the linked list.
  Task *head = NULL;

  //Read the tasks from the .txt file and create a linked list out of them.
  readFile("schedule.txt", &head);

  //Execute the tasks in the linked list using SJF.
  executeTasks(head);

  return 0;

}

//Function to insert a task into the linked list.
void insertTask(Task **head, Task *newTask) {

  //If the list is empty or if the burst time of the head of the list is greater than that of the new task,
  //then insert the new task at the head of the list.
  if (*head == NULL || (*head)->burst > newTask->burst) {
    newTask->next = *head;
    *head = newTask;
  }
  
  //Otherwise, find the correct position for the new task.
  else {
    Task *current = *head;
    while (current->next != NULL && current->next->burst <= newTask->burst) {
      current = current->next;
    }
    
    newTask->next = current->next;
    current->next = newTask;
  }
}

//Function to create a new task node.
Task* createTask(char *name, int priority, int burst) {

  //Allocate memory for a task.
  Task *newTask = (Task *)malloc(sizeof(Task));
  
  //If the allocation fails, then terminate the program and throw an error.
  if (newTask == NULL) {
    perror("Memory allocation error.");
    exit(EXIT_FAILURE);
  }
  
  //Initialize the variables of the task.
  strcpy(newTask->name, name);
  newTask->priority = priority;
  newTask->burst = burst;
  newTask->next = NULL;
  return newTask;
}

//Function to read a file.
void readFile(char *fileName, Task **head) {

  //Open the file.
  FILE *file = fopen(fileName, "r");
  
  //If opening the file fails, throw an error.
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
      insertTask(head, newTask);
    }
  }  
  fclose(file);
}
      

//Function to execute tasks with SJF.
void executeTasks(Task *head) {
  while (head != NULL) {
  //Print the variables of the task.
  printf("Executing Task: %s, Priority: %d, Burst: %d, Time in processor: %d\n", head->name, head->priority, head->burst, head->burst);
  
  //Make the next task the current task, and free the task that was the current task before this.
  Task *temp = head;
  head = head->next;
  free(temp);
  }
}
