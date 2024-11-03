
#include <stdio.h>
#include <stdbool.h>

#define STACK_LENGTH 32768

typedef struct
{
    int arr[STACK_LENGTH];
    int top;
} Stack;

void CREATE(Stack *s);
bool ISFULL(Stack *s);
bool ISEMPTY(Stack *s);
void push(Stack *s, int index);
int POP(Stack *s);
int TOP(Stack s);
int NEXT_TO_TOP(Stack s);
int TOP(Stack s);