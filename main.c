#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/wait.h>

#define MAX_LINE 80
#define HISTORY_MAX_SIZE 10

/* depending on the pid the history command may look ugly and out of format.
I thought about counting the digits in pid and inserting \t accordingly to make it
look better but that's just gonna increase the progam complexity. Couldn't find a
better soln. Please let me know if there is one for vertical formatting in the feedback thx :) */

int main(void) {
  int should_run = 1;
  char *args[MAX_LINE/2 + 1];
  char *args_history_stack[HISTORY_MAX_SIZE];
  char *sample;
  long pids_history_stack[HISTORY_MAX_SIZE] = {0};
  int history_flag = 0;


  while (should_run == 1) {
    printf("\nCSCI3120> ");

    char *buffer = NULL;
    int characters_read;
    size_t len;

    characters_read = getline(&buffer, &len, stdin);
    buffer[strcspn(buffer, "\n")] = 0;

    if (characters_read != -1) {
      if (strcmp(buffer, "\0") == 0) {
        continue;
      }
      else if (strcmp(buffer, "exit") == 0) {
        should_run = 0;
        printf("Exiting SimpleShell...");
        free(buffer);
        break;
      }
      else if (strcmp(buffer, "history") == 0) {
        printf("\n ID\t PID\t Command");
        int id = 1;
        for (int i = HISTORY_MAX_SIZE - 1; i >= 0; i--) {
          if (pids_history_stack[i] != 0) {
            printf("\n %d", id);
            printf("\t %ld", pids_history_stack[i]);
            printf("\t %s", args_history_stack[i]);
            id++;
          }
        }
        printf("\n");
      }
      else {
        if (strcmp(buffer, "!!") == 0) {
          if (history_flag == 0) {
            printf("No commands in history.\n");
            continue;
          }
          else {
            strcpy(buffer, args_history_stack[history_flag - 1]);
          }
        }
        else if (strcmp(buffer, "!1") == 0) {
          if (history_flag < 1) {
            printf("No such command in history.\n");
            continue;
          }
          else {
            strcpy(buffer, args_history_stack[history_flag - 1]);
          }
        }
        else if (strcmp(buffer, "!2") == 0) {
          if (history_flag < 2) {
            printf("No such command in history.\n");
            continue;
          }
          else {
            strcpy(buffer, args_history_stack[history_flag - 2]);
          }
        }
        else if (strcmp(buffer, "!3") == 0) {
          if (history_flag < 3) {
            printf("No such command in history.\n");
            continue;
          }
          else {
            strcpy(buffer, args_history_stack[history_flag - 3]);
          }
        }
        else if (strcmp(buffer, "!4") == 0) {
          if (history_flag < 4) {
            printf("No such command in history.\n");
            continue;
          }
          else {
            strcpy(buffer, args_history_stack[history_flag - 4]);
          }
        }
        else if (strcmp(buffer, "!5") == 0) {
          if (history_flag < 5) {
            printf("No such command in history.\n");
            continue;
          }
          else {
            strcpy(buffer, args_history_stack[history_flag - 5]);
          }
        }
        else if (strcmp(buffer, "!6") == 0) {
          if (history_flag < 6) {
            printf("No such command in history.\n");
            continue;
          }
          else {
            strcpy(buffer, args_history_stack[history_flag - 6]);
          }
        }
        else if (strcmp(buffer, "!7") == 0) {
          if (history_flag < 7) {
            printf("No such command in history.\n");
            continue;
          }
          else {
            strcpy(buffer, args_history_stack[history_flag - 7]);
          }
        }
        else if (strcmp(buffer, "!8") == 0) {
          if (history_flag < 8) {
            printf("No such command in history.\n");
            continue;
          }
          else {
            strcpy(buffer, args_history_stack[history_flag - 8]);
          }
        }
        else if (strcmp(buffer, "!9") == 0) {
          if (history_flag < 9) {
            printf("No such command in history.\n");
            continue;
          }
          else {
            strcpy(buffer, args_history_stack[history_flag - 9]);
          }
        }
        else if (strcmp(buffer, "!10") == 0) {
          if (history_flag < 10) {
            printf("No such command in history.\n");
            continue;
          }
          else {
            strcpy(buffer, args_history_stack[history_flag - 10]);
          }
        }

        if (history_flag == HISTORY_MAX_SIZE) {
          for (int i = 0; i < HISTORY_MAX_SIZE - 1; i++) {
            pids_history_stack[i] = pids_history_stack[i+1];
            args_history_stack[i] = realloc(args_history_stack[i], strlen(args_history_stack[i+1]) + 1);
            strcpy(args_history_stack[i], args_history_stack[i+1]);
          }
          --history_flag;
        }
        
        args_history_stack[history_flag] = malloc(strlen(buffer) + 1);
        strcpy(args_history_stack[history_flag], buffer);
        
        int i = 0;
        char *token = NULL;
        token = strtok(buffer, " \t");
        while (token != NULL) {
          args[i++] = token;
          token = strtok(NULL," \t");
        }
        args[i] = NULL;

        pid_t c_pid, p_pid;
        int status;

        c_pid = fork();
        
        if (c_pid == 0) {
          execvp(args[0], args);
          perror("ERROR: execve failed");
          _exit(1);
        }
        else if (c_pid > 0) {
          pids_history_stack[history_flag] = c_pid;
          history_flag++;
          if ((p_pid = wait(&status)) < 0) {
            perror("WAIT");
            free(buffer);
            free(*args);
            free(token);
            _exit(1);
          }
          
          continue;
        }
        else {
          perror("ERROR: fork failed");
          _exit(1);
        }
      }
    }
    else {
      printf("ERROR: reading line...\n");
    }
  }
  
  printf("\n\nBye!\n");
  return 0;
}