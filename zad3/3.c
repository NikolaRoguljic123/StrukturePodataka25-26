
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR (-1)

typedef struct osoba* Position;
typedef struct osoba {
    char ime[64];
    char prezime[64];
    int godine;
    Position Next;
} osoba;

// Prototipi funkcija
int Addbegin(char ime[64], char prezime[64], int godine, Position P);
int Addend(char ime[64], char prezime[64], int godine, Position P);
int AddAfter(char ime[64], char prezime[64], int godine, Position P, char targetPrezime[64]);
int AddBefore(char ime[64], char prezime[64], int godine, Position P, char targetPrezime[64]);
int print(Position P);
int search(char prezime[64], Position P);
int erase(char ime[64], char prezime[64], Position P);
int SortList(Position P);
int WriteListToFile(Position P, const char* filename);
int ReadListFile(Position P, const char* filename);

int main() {
    osoba head;
    head.Next = NULL; // Inicijaliziraj po?etnu listu kao praznu

    // Dodavanje elemenata u listu
    Addbegin("Nikola", "Izgoren", 2004, &head);
    Addbegin("Pero", "Peric", 2003, &head);
    Addend("Tudo", "Tudumovic", 2002, &head);
    Addend("Pero", "Izbacic", 2001, &head);

    printf("Lista nakon dodavanja: \n");
    print(head.Next);

    // Testiranje dodavanja nakon odre?enog elementa
    AddAfter("Marko", "Kovac", 1990, &head, "Peric");

    // Testiranje dodavanja ispred odre?enog elementa
    AddBefore("Ivana", "Novak", 1995, &head, "Izgoren");

    printf("\nLista nakon dodatka: \n");
    print(head.Next);

    // Sortiranje liste po godinama ro?enja
    SortList(&head);

    printf("\nLista nakon sortiranja: \n");
    print(head.Next);

    // Upisivanje u datoteku
    WriteListToFile(head.Next, "lista.txt");

    // ?itanje iz datoteke
    osoba headFile;
    headFile.Next = NULL;
    ReadListFile(&headFile, "lista.txt");

    printf("\nLista nakon u?itavanja iz datoteke: \n");
    print(headFile.Next);

    return 0;
}

// Funkcija za dodavanje na po?etak
int Addbegin(char ime[64], char prezime[64], int godine, Position P) {
    Position Q = (Position)malloc(sizeof(osoba));
    if (Q == NULL) {
        printf("Greska prilikom alokacije\n");
        return ERROR;
    }

    Q->Next = P->Next;
    P->Next = Q;

    strcpy(Q->ime, ime);
    strcpy(Q->prezime, prezime);
    Q->godine = godine;

    return 0;
}

// Funkcija za dodavanje na kraj
int Addend(char ime[64], char prezime[64], int godine, Position P) {
    Position Q = (Position)malloc(sizeof(osoba));
    if (Q == NULL) {
        printf("Greska prilikom alokacije\n");
        return ERROR;
    }

    while (P->Next != NULL) {
        P = P->Next;
    }

    Q->Next = NULL;
    P->Next = Q;

    strcpy(Q->ime, ime);
    strcpy(Q->prezime, prezime);
    Q->godine = godine;

    return 0;
}

// Funkcija za dodavanje nakon odre?enog elementa
int AddAfter(char ime[64], char prezime[64], int godine, Position P, char targetPrezime[64]) {
    P = P->Next; // Start from first actual node, not head

    while (P != NULL) {
        if (strcmp(P->prezime, targetPrezime) == 0) {
            Position Q = (Position)malloc(sizeof(osoba));
            if (Q == NULL) {
                printf("Greska prilikom alokacije\n");
                return ERROR;
            }

            Q->Next = P->Next;
            P->Next = Q;

            strcpy(Q->ime, ime);
            strcpy(Q->prezime, prezime);
            Q->godine = godine;
            return 0;
        }
        P = P->Next;
    }

    printf("Osoba s prezimenom '%s' nije pronadjena.\n", targetPrezime);
    return ERROR;
}

// Funkcija za dodavanje ispred odre?enog elementa - FIXED
int AddBefore(char ime[64], char prezime[64], int godine, Position P, char targetPrezime[64]) {
    Position current = P->Next;
    Position prev = P;

    // Search for target
    while (current != NULL && strcmp(current->prezime, targetPrezime) != 0) {
        prev = current;
        current = current->Next;
    }

    if (current == NULL) {
        printf("Osoba s prezimenom '%s' nije pronadjena.\n", targetPrezime);
        return ERROR;
    }

    // Create new node
    Position Q = (Position)malloc(sizeof(osoba));
    if (Q == NULL) {
        printf("Greska prilikom alokacije\n");
        return ERROR;
    }

    // Insert before current
    strcpy(Q->ime, ime);
    strcpy(Q->prezime, prezime);
    Q->godine = godine;
    Q->Next = current;
    prev->Next = Q;

    return 0;
}

// Funkcija za ispisivanje liste
int print(Position P) {
    if (P == NULL) {
        printf("Lista je prazna.\n");
        return ERROR;
    }

    while (P != NULL) {
        printf("%s %s %d\n", P->ime, P->prezime, P->godine);
        P = P->Next;
    }

    return 0;
}

// Funkcija za pretragu osobe po prezimenu
int search(char prezime[64], Position P) {
    while (P != NULL) {
        if (strcmp(P->prezime, prezime) == 0) {
            printf("Pronadjena osoba: %s %s, Godine: %d\n", P->ime, P->prezime, P->godine);
            return 0;
        }
        P = P->Next;
    }

    printf("Osoba s prezimenom %s nije pronadjena.\n", prezime);
    return ERROR;
}

// Funkcija za brisanje osobe
int erase(char ime[64], char prezime[64], Position P) {
    Position Q = NULL;

    while (P->Next != NULL) {
        Q = P;
        P = P->Next;

        if (strcmp(P->prezime, prezime) == 0 && strcmp(P->ime, ime) == 0) {
            Q->Next = P->Next;
            free(P);
            return 0;
        }
    }

    printf("Osoba sa imenom %s i prezimenom %s nije pronadjena.\n", ime, prezime);
    return ERROR;
}

// Funkcija za sortiranje liste po godinama ro?enja
int SortList(Position P) {
    if (P == NULL || P->Next == NULL) {
        printf("Lista je prazna ili ima samo jedan element.\n");
        return 0;
    }

    P = P->Next; // Start from first actual node
    Position i, j;
    char tempIme[64], tempPrezime[64];
    int tempGodine;

    // Bubble sort: sortiranje po godinama ro?enja
    for (i = P; i != NULL; i = i->Next) {
        for (j = i->Next; j != NULL; j = j->Next) {
            if (i->godine > j->godine) { // Sortiramo po godinama ro?enja
                // Zamjena podataka
                strcpy(tempIme, i->ime);
                strcpy(tempPrezime, i->prezime);
                tempGodine = i->godine;

                strcpy(i->ime, j->ime);
                strcpy(i->prezime, j->prezime);
                i->godine = j->godine;

                strcpy(j->ime, tempIme);
                strcpy(j->prezime, tempPrezime);
                j->godine = tempGodine;
            }
        }
    }
    return 0;
}

// Funkcija za pisanje liste u datoteku
int WriteListToFile(Position P, const char* filename) {
    FILE* file = fopen("lista.txt", "w");
    if (file == NULL) {
        printf("Greska pri otvaranju datoteke '%s' za pisanje.\n", filename);
        return ERROR;
    }

    while (P != NULL) {
        fprintf(file, "%s %s %d\n", P->ime, P->prezime, P->godine);
        P = P->Next;
    }

    fclose(file);
    printf("Lista je uspješno zapisana u datoteku '%s'.\n", filename);
    return 0;
}

// Funkcija za ?itanje liste iz datoteke
int ReadListFile(Position P, const char* filename) {
    FILE* file = fopen("lista.txt", "r");
    if (file == NULL) {
        printf("Greska pri otvaranju datoteke '%s' za ?itanje.\n", filename);
        return ERROR;
    }

    char ime[64], prezime[64];
    int godine;

    while (fscanf(file, "%63s %63s %d", ime, prezime, &godine) == 3) {
        Addend(ime, prezime, godine, P);
    }

    fclose(file);
    printf("Lista je uspješno u?itana iz datoteke '%s'.\n", filename);
    return 0;
}























