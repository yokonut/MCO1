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

void CREATE(Stack *s)
{
    s->top = -1;
}

bool ISFULL(Stack *s)
{
    return s->top == STACK_LENGTH - 1;
}

bool ISEMPTY(Stack *s)
{
    return s->top == -1;
}

void push(Stack *s, float x, float y)
{
    if (!ISFULL(s))
    {

        ++s->top;

        s->arr[s->top].x = x;
        s->arr[s->top].y = y;

        printf("Pushed x = %f and y = %f onto the stack\n", x, y);
    }
}

struct point POP(Stack *s)
{
    if (!ISEMPTY(s))
    {

        struct point popped = s->arr[s->top];
        s->top--;
        return popped;
    }

}

struct point
TOP(Stack s)
{
    return s.arr[s.top];
}

struct point
NEXT_TO_TOP(Stack s)
{
    return s.arr[--s.top];
}
