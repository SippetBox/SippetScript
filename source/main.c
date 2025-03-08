#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "sippetscript.h"

#define INPUT_SIZE 1024

int main() {
  printf("SippetScript Interpreter (type something and press Enter):\n");

  char input[INPUT_SIZE];
  while (true) {
    printf("> ");

    if (fgets(input, INPUT_SIZE, stdin) == NULL) {
      break;
    }

    input[strcspn(input, "\n")] = 0;

    enum SippetscriptStatus status = sippetscript(input);
    printf("SippetScript Status: %s\n", sippetscript_status_string(status));
  }

  exit(EXIT_SUCCESS);
}