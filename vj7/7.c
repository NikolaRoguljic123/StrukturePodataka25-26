#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Dir* Position;

typedef struct Dir {
    char name[50];
    Position parent;
    Position child;
    Position sibling;
} Dir;


Position createDir(char* name, Position parent) {
    Position newDir = (Position)malloc(sizeof(Dir));
    strcpy(newDir->name, name);
    newDir->parent = parent;
    newDir->child = NULL;
    newDir->sibling = NULL;
    return newDir;
}


void md(Position current) {
    char name[50];
    printf("Ime direktorija: ");
    scanf("%s", name);

    Position newDir = createDir(name, current);

    if (current->child == NULL) {
        current->child = newDir;
    }
    else {
        Position temp = current->child;
        while (temp->sibling != NULL)
            temp = temp->sibling;
        temp->sibling = newDir;
    }
}

Position cd(Position current) {
    char name[50];
    printf("U koji direktorij: ");
    scanf("%s", name);

    Position temp = current->child;
    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0)
            return temp;
        temp = temp->sibling;
    }

    printf("Direktorij ne postoji!\n");
    return current;
}


Position cd_back(Position current) {
    if (current->parent != NULL)
        return current->parent;
    return current;
}


void dir(Position current) {
    Position temp = current->child;
    if (temp == NULL) {
        printf("Direktorij je prazan.\n");
        return;
    }

    while (temp != NULL) {
        printf("%s\n", temp->name);
        temp = temp->sibling;
    }
}

int main() {
    Position root = createDir("C:", NULL);
    Position current = root;
    int choice;

    do {
        printf("\nTrenutni direktorij: %s\n", current->name);
        printf("1 - md\n");
        printf("2 - cd dir\n");
        printf("3 - cd..\n");
        printf("4 - dir\n");
        printf("5 - izlaz\n");
        printf("Izbor: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            md(current);
            break;
        case 2:
            current = cd(current);
            break;
        case 3:
            current = cd_back(current);
            break;
        case 4:
            dir(current);
            break;
        case 5:
            printf("Izlaz iz programa.\n");
            break;
        default:
            printf("Nepoznata opcija!\n");
        }
    } while (choice != 5);

    return 0;
}