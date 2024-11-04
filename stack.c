#include "stack.h"

#define STACK_MAX 32768

//s.top basically is the index of the stack and we initialize it to -1
void CREATE(Stack *s)
{
    s->top = -1;
}

//if the index is MAX - 1 then the stack is full 
bool ISFULL(Stack *s)
{
    return s->top == STACK_MAX - 1;
}

//if the index is -1 then the stack is still empty
bool ISEMPTY(Stack *s)
{
    return s->top == -1;
}

//if the stack isn't full it increments the index and adds the index value to the point array
void push(Stack *s, int index)
{
    if (!ISFULL(s))
    {

        ++s->top; // increment top

        s->arr[s->top] = index; //assign index value to the point array
    }
}

//decrements the index while it isn't empty and returns value of the popped index
int POP(Stack *s)
{
    if (!ISEMPTY(s)) 
    {

        int popped = s->arr[s->top];    //puts the to be removed value into variable popped
        s->top--;                       //decrement top
        return popped;                  //returned the value that was lost
    }
}

//returns the top value of the stack
int TOP(Stack s)
{
    return s.arr[s.top];
}


//returns the second most top value of the stack
int NEXT_TO_TOP(Stack s)
{
    return s.arr[--s.top];
}

