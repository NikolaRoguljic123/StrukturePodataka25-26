

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ERROR (-1)

typedef struct osoba* Position;
typedef struct osoba {
    int data;       
    Position Next;   
} osoba;

// Prototipi funkcija
int Push(Position* P, int data);
int Pop(Position* P);
int IsEmpty(Position P);
int EvaluatePostfix(char* expression);

int main() {
    char expression[256];

   
    printf("Enter a postfix expression (space separated): ");
    fgets(expression, sizeof(expression), stdin);

   
    int result = EvaluatePostfix(expression);
    printf("Result: %d\n", result);

    return 0;
}

// Function to push an element onto the stack
int Push(Position* P, int data) {
    Position newElem = (Position)malloc(sizeof(osoba));  
    if (newElem == NULL) {
        printf("Error allocating memory!\n");
        return ERROR;
    }

    newElem->data = data;     
    newElem->Next = *P;       
    *P = newElem;           

    return 0;
}


int Pop(Position* P) {
    if (*P == NULL) {
        printf("Error: Stack is empty!\n");
        return ERROR; 
    }

    Position temp = *P;       
    int data = temp->data;   
    *P = temp->Next;         

    free(temp);               
    return data;             
}

int IsEmpty(Position P) {
    return P == NULL;  
}


int EvaluatePostfix(char* expression) {
    Position stack = NULL; 

   
    char* token = strtok(expression, " ");
    while (token != NULL) {
        if (isdigit(token[0])) {
            Push(&stack, atoi(token));
        }
        else {
           
            int operand2 = Pop(&stack);  
            int operand1 = Pop(&stack);  

            int result;
            switch (token[0]) {
            case '+':
                result = operand1 + operand2;
                break;
            case '-':
                result = operand1 - operand2;
                break;
            case '*':
                result = operand1 * operand2;
                break;
            case '/':
                if (operand2 == 0) {
                    printf("Error: Division by zero\n");
                    return ERROR;
                }
                result = operand1 / operand2;
                break;
            default:
                printf("Error: Unknown operator %c\n", token[0]);
                return ERROR;
            }

            Push(&stack, result);
        }

    
        token = strtok(NULL, " ");
    }


    int finalResult = Pop(&stack);
    if (IsEmpty(stack)) {
        return finalResult;  
    }
    else {
        printf("Error: Invalid postfix expression\n");
        return ERROR;
    }
}













