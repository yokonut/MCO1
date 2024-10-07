#include "stack.h"



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

struct point TOP(Stack s)
{
    return s.arr[s.top];
}

struct point NEXT_TO_TOP(Stack s)
{
    return s.arr[--s.top];
}


int main()
{
    Stack stack;
    // Initialize the stack
    CREATE(&stack);
    struct point top;

    // Push elements onto the stack and print the stack after each push
    push(&stack, 3.5,4.5);
    top = TOP(stack);
    printf("Top element: %f and %f\n", top.x, top.y);

    push(&stack, 5.4,2.3);
    top = TOP(stack);
    printf("Top element: %f and %f\n", top.x, top.y);

    push(&stack, 2.1,8.7);
    top = TOP(stack);
    printf("Top element: %f and %f\n", top.x, top.y);

    push(&stack, 8.2,9.5);
    top = TOP(stack);
    printf("Top element: %f and %f\n", top.x, top.y);

    struct point popped = POP(&stack);
    printf("popped element: %f and %f\n", popped.x, popped.y);
    top = TOP(stack);
    printf("Top element: %f and %f\n", top.x, top.y);

    struct point next = NEXT_TO_TOP(stack);
    printf("Next to top element: %f and %f\n", next.x, next.y);
    // Pop elements from the stack and print the stack after each pop


    return 0;
}
