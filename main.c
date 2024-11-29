#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

// Function prototypes
void captureTask();
void listTasks();
void addTask();

int main() {
  char input[10];
  printf("Welcome to ajk-task-breaker\n");
  printf("What would you like to do?\n");
  printf("c. Capture a task\n");
  printf("s. List tasks\n");
  scanf("%9s", input);
  printf("You entered: %s\n", input);

  switch (input[0]) {
  case 'c':
    captureTask();
    break;
  case 's':
    listTasks();
    break;
  default:
    printf("Invalid option\n");
    break;
  }

  return 0;
}

// Function definitions
void captureTask() {
  char title[100];
  char filename[100];
  char taskIdStr[100];
  time_t currentTime;
  time(&currentTime);
  int taskId = (int)currentTime;
  sprintf(taskIdStr, "db/%d.md", taskId);
  snprintf(filename, sizeof(filename), "%s", taskIdStr);

  printf("Enter the task title: ");
  getchar(); // Consume the newline character left by scanf
  fgets(title, sizeof(title), stdin);
  // Remove the newline character from the end of the string
  title[strcspn(title, "\n")] = 0;

  // Generate the filename
  // TODO: (id autogenerated for task)
  // TODO: (logs to keep track of created task_id, tomake sure id is unique (db

  FILE *file = fopen(filename, "w");
  if (file == NULL) {
    printf("Error creating file\n");
    return;
  }
  fprintf(file, "%s\n", title);
  fclose(file);
  return;
  // Add your task capturing logic here
  // TODO: (title is the first line of file)
  // TODO: (content of the file is saved from second line)
  // TODO: (file type is md)
  // function))
}

/* TODO: (this is to have cli flags feature) */
void flagHandlers(int argc, char *argv[]) {
  int opt;
  while ((opt = getopt(argc, argv, "cs")) != -1) {
    switch (opt) {
    case 'c':
      captureTask();
      return;
    case 's':
      listTasks();
      return;
    default:
      fprintf(stderr, "Usage: %s [-c] [-s]\n", argv[0]);
      return;
    }
  }
}

void listTasks() {
  DIR *dir;
  struct dirent *ent;
  if ((dir = opendir("db")) != NULL) {
    while ((ent = readdir(dir)) != NULL) {
      if (ent->d_type == DT_REG) { // Check if it's a regular file
        char filepath[300];
        snprintf(filepath, sizeof(filepath), "db/%s", ent->d_name);
        printf("Task file: %s\n", ent->d_name);
        printf("\n");
      }
    }
    closedir(dir);
  } else {
    perror("Could not open directory");
  }
}
