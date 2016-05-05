#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SCRIPT_MAX_LENGTH 128
#define TYPE_CONSOLE 0
#define TYPE_EXPLAIN 1
  FILE * f;
double numBuf;
char *strBuf;
char *scpHead;
char *scpBody;
char *strPtr;
int lines = 1;

int execute(char *script, int type) {
  sscanf(script, "%s %s", scpHead, scpBody);
  if (strcmp(scpHead, "print") == 0) {
    if (strcmp(scpBody, "_ver_") == 0) {
      printf("v0.01\n");
    } else if (strcmp(scpBody, "_mem_") == 0) {
      printf("%f\n", numBuf);
    } else {
      printf("%s\n", scpBody);
    }
  } else if (strcmp(scpHead, "version") == 0 || strcmp(scpHead, "ver") == 0) {
    printf("Scripter version: v0.01\n");
  } else if (strcmp(scpHead, "put") == 0) {
    numBuf = atof(scpBody);
  } else if (strcmp(scpHead, "op+") == 0) {
    numBuf = numBuf + atof(scpBody);
  } else if (strcmp(scpHead, "op-") == 0) {
    numBuf = numBuf - atof(scpBody);
  } else if (strcmp(scpHead, "op*") == 0) {
    numBuf = numBuf * atof(scpBody);
  } else if (strcmp(scpHead, "op/") == 0) {
    numBuf = numBuf / atof(scpBody);
  } else if (strcmp(scpHead, "exit") == 0) {
    if (strcmp(scpBody, "this") == 0) {
      return 0;
    } else {
      return 1;
    }
  } else {
    printf("Syntax error, in line %d: %s %s\n", lines, scpHead, scpBody);
    printf("Script aborted.\n");
    return type == TYPE_CONSOLE ? 1 : (type == TYPE_EXPLAIN ? 0 : 1);
  }
  return 1;
}

void cliBuild() {
  printf("================\n");
  printf("Scripter ver0.01\n");
  printf("================\n");
  printf("Usage: Scripter <script name>\n\n");
  while (1) {
    printf("%d >>> ", lines);
    strPtr = gets(strBuf);
    if (!execute(strBuf, TYPE_CONSOLE))
      break;
    lines++;
  }
}

int main(int argc, char *argv[]) {
  strBuf = (char *)malloc(sizeof(char) * SCRIPT_MAX_LENGTH);
  strcpy(strBuf, "_null_");
  scpHead = (char *)malloc(sizeof(char) * SCRIPT_MAX_LENGTH);
  strcpy(scpHead, "_null_");
  scpBody = (char *)malloc(sizeof(char) * SCRIPT_MAX_LENGTH);
  strcpy(scpBody, "_null_");
  if (argc < 2) {
    cliBuild();
  } else if (argc == 2) {
    f = fopen(argv[1], "r");
    if (f == NULL) {
      printf("File open failed.\n");
      return 0;
    } else {
      while (1) {
        strPtr = fgets(strBuf, SCRIPT_MAX_LENGTH, f);
        if (strPtr == NULL)
          break;
        if (!execute(strPtr, TYPE_EXPLAIN))
          break;
        lines++;
      }
      fclose(f);
    }
  }
  free(strBuf);
  free(scpHead);
  free(scpBody);
  return 0;
}