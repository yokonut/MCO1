
#include <stdio.h>
#include <stdbool.h>

#define STACK_LENGTH 32768

struct point
{
    float x;
    float y;
};


typedef struct
{
    struct point arr[STACK_LENGTH];
    int top;
} Stack;

void CREATE(Stack *s);
bool ISFULL(Stack *s);
bool ISEMPTY(Stack *s);
void push(Stack *s, float x, float y);
struct point POP(Stack *s);
struct point TOP(Stack s);
struct point NEXT_TO_TOP(Stack s);
struct point TOP(Stack s);