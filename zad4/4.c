
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct * Position;
typedef struct Node {
    int data;
    Position Next;
} Node;

    Push(Position head, int value) {
    Position newNode = (Position)malloc(sizeof(Node));
    if (!newNode) {
        printf("Greska u alokaciji memorije!\n");
        exit(1);
    }

    newNode->data = value;
    newNode->Next = head->Next;
    head->Next = newNode;
}


int Pop(Position head) {
    if (head->Next == NULL) {
        printf("Greska: stog je prazan!\n");
        exit(1);
    }

    Position temp = head->Next;
    int value = temp->data;

    head->Next = temp->Next;
    free(temp);

    return value;
}

// Evaluacija postfiksnog izraza
int EvaluatePostfix(char* expr, Position head) {
    char* token = strtok(expr, " ");

    while (token != NULL) {

        
        if (isdigit(token[0]) || 
           (token[0] == '-' && isdigit(token[1]))) {

            Push(head, atoi(token));
        }
        else {
          
            int b = Pop(head);
            int a = Pop(head);
            int result = 0;

            switch (token[0]) {
                case '+': result = a + b; break;
                case '-': result = a - b; break;
                case '*': result = a * b; break;
                case '/': 
                    if (b == 0) {
                        printf("Dijeljenje s nulom!\n");
                        exit(1);
                    }
                    result = a / b;
                    break;
                default:
                    printf("Nepoznat operator: %s\n", token);
                    exit(1);
            }

            Push(head, result);
        }

        token = strtok(NULL, " ");
    }

    return Pop(head);
}

int main() {
    FILE* file = fopen("postfix.txt", "r");
    if (!file) {
        printf("Greska: ne mogu otvoriti postfix.txt\n");
        return 1;
    }

    char buffer[256];
    fgets(buffer, sizeof(buffer), file);
    fclose(file);

    buffer[strcspn(buffer, "\n")] = 0;//vazno 

    Node head;
    head.Next = NULL;

    int result = EvaluatePostfix(buffer, &head);

    printf("Rezultat: %d\n", result);

    return 0;
}












