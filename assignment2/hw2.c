// name: Tian Huang 
// email: huang.tian2@northeastern.edu

#include <stdio.h>   // stardard input/output library
#include <stdbool.h> // standard boolean library: bool, true, false

#define MAXSIZE 100

bool isEmpty (int* s, int t) {
  // returns true if t = -1
  if (t == -1) {
      return true;
  }
  else {
      return false;
  }
}

bool isFull (int* s, int t) {
  // returns true if no more room in the stack
  if (t >= MAXSIZE-1) {
      return true;
  }
  else {
      return false;
  }
}

void push(int v, int* s, int* tp) {
  // put v onto the top of the stack s unless it is already full
  if (isFull(s, *tp)) {
      printf("Error in pushing %d onto a full stack.\n", v);
      return;
  }
  s[++*tp] = v;
  return;
}

int pop (int* s, int* tp) {
  // return the top entry in the stack unless stack is empty
  // update s and *tp -- requires top to be passed by reference!
  if (isEmpty(s, *tp)) {
      printf("Error in popping from an empty stack.\n");
      return 0;
  }
  int popEle = s[*tp];
  --*tp;
  return popEle;
  
}

int main () {

  int stack1[MAXSIZE]; // array in which stack will live
  int top1 = -1;       // top valid location in stack, -1 == empty
  int stack2[MAXSIZE]; // array in which stack will live
  int top2 = -1;       // top valid location in stack, -1 == empty
  
  printf("pushing: 1, 2, 3, 4, 5 onto first stack\n");
  printf("pushing: 100, 200, 300, 400, 500 onto second stack\n\n");
  push(1, stack1, &top1);
  push(2, stack1, &top1);
  push(3, stack1, &top1);
  push(4, stack1, &top1);
  push(5, stack1, &top1);
  push(100, stack2, &top2);
  push(200, stack2, &top2);
  push(300, stack2, &top2);
  push(400, stack2, &top2);
  push(500, stack2, &top2);

  printf("popping alternating stacks:\n");
  printf("1> %d\n",pop(stack1, &top1));
  printf("2> %d\n",pop(stack2, &top2));
  printf("1> %d\n",pop(stack1, &top1));
  printf("2> %d\n",pop(stack2, &top2));
  printf("1> %d\n",pop(stack1, &top1));
  printf("2> %d\n",pop(stack2, &top2));
  printf("1> %d\n",pop(stack1, &top1));
  printf("2> %d\n",pop(stack2, &top2));
  printf("1> %d\n",pop(stack1, &top1));
  printf("2> %d\n",pop(stack2, &top2));
  printf("1> %d\n",pop(stack1, &top1));
  printf("2> %d\n",pop(stack2, &top2));
  return 0;
}
