
#define ERROR (-1)
#include<stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct osoba* Position;
typedef struct osoba {


    char ime[64];
    char prezime[64];
    int godine;
    Position Next;


}osoba;



int Addbegin(char ime[64], char prezime[64], int godine, Position P);
int Addend(char ime[64], char prezime[64], int godine, Position P);
int print(Position P);
int search(char prezime[64], Position P);
int erase(char ime[64], char prezime[64], Position P);

int main() {

    osoba head;

    head.Next = NULL;
    Addbegin("Nikola", "Izgoren", "2004", &head);
    Addbegin("Pero", "Peric", "2003", &head);
    Addend("Tudo", "Tudumovic", "2002", &head);
    Addend("Pero", "Izbacic", "2001", &head);
    ispis(head.Next);
    search("Tudumovic", head.Next);
    erase("Tudo", "Tudumovic", "2002", &head)




}
int Addbegin(char ime[64], char prezime[64], int godine, Position P) {





    Position Q = NULL;
    Q = (Position)malloc(sizeof(osoba));

    if (head == NULL) {
        printf(greska prilikom alokacije);
        return ERROR;
    }

    Q->Next = P->Next;
    P->Next = Q;

    strcpy(Q->ime, ime);
    strcpy(P->prezime, prezime);
    Q->godine = godine;



}

int Addend(char ime[64], char prezime[64], int godine, Position P) {





    Position Q = NULL;
    Q = (Position)malloc(sizeof(osoba));

    if (head == NULL) {
        printf(greska prilikom alokacije);
        return ERROR;
    }



    while (P->Next != NULL) {

        P = P->Next;

    }


    Q->Next = P->Next;
    P->Next = Q;

    strcpy(Q->ime, ime);
    strcpy(P->prezime, prezime);
    Q->godine = godine;



}


int print(Position P) {


    while (P != NULL) {

        printf("%s %s %d "P->ime, P->Prezime, P->godina);

        P = P->Next;


    }

}

int search(char prezime[64], Position P) {


    While(P->Next != NULL) {

        P = P->Next;

        if (strcmp(P->Prezime, Prezime) == 0) {

            printf("pronadjena osoba je %s %s", P->ime, P->Prezime);
        }
        else {


            return ERROR;
        }
    }
}
int erase(char ime[64], char prezime[64], Position P) {


    Position Q = NULL;

    While(P->Next != NULL) {

        Q = P;
        P = P->Next;

        if (strcmp(P->prezime, prezime) == 0 && strcmp(P->ime, ime) == 0) {

            Q->Next = P->Next;
            P->Next = NULL;

            free(P);


        }
    }












