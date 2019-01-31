/* authors: Scott Miller & Paul Jureidini  */

/*This file contains all of our global variables*/

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define BUFFSIZE 1024
#define TRUE 1
#define FALSE 0

typedef struct node {
  int job;    // J
  int mem;    // M
  int max;    // S - serial dirves
  int run;    // R
  int pri;    // P
  int quant;  // Q
  int device; // D - number of devices
  int arrival;
  char instruction;
  int comptime;
  struct node *next;

} node;

node *hq1head;   // hq1
node *hq2head;   // hq2
node *devqhead;  // device wait queue
node *readyhead; // ready queue
node *CPU;
node *finished;

FILE* file_pointer;
json_object *outputArray;

// global variables for the system
int totalmem;
int currentmem;
int totaldev;
int currentdev;
int quantum;
int time;
int flag;
int cpuflag;
int m;
char buf[BUFFSIZE];


