#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct CvorStabla* Stablo;
typedef struct CvorStabla* Pozicija;

struct CvorStabla {
    int El;
    Stablo Desno;
    Stablo Lijevo;
};

/* prototipi funkcija */
Stablo Dodaj(int el, Stablo S);
Stablo Brisi(int el, Stablo S);
Pozicija Trazi(int el, Stablo S);
Pozicija TraziMin(Stablo S);
void IspisIn(Stablo S);
void IspisPre(Stablo S);
void IspisPost(Stablo S);
int Visina(Stablo S);
void IspisRazina(Stablo S, int razina);
void IspisLevel(Stablo S);
Stablo ObrisiStablo(Stablo S);

int main(void) {
    Stablo root = NULL;
    Pozicija p = NULL;
    int izbor, el;

    while (1) {
        printf("\n--- IZBORNIK ---\n");
        printf("1 - Unos elementa\n");
        printf("2 - Ispis stabla\n");
        printf("3 - Brisanje elementa\n");
        printf("4 - Trazenje elementa\n");
        printf("5 - Izlaz\n");
        printf("Izbor: ");
        scanf("%d", &izbor);

        if (izbor == 1) {
            printf("Unesite element: ");
            scanf("%d", &el);
            root = Dodaj(el, root);
        }
        else if (izbor == 2) {
            printf("\nInorder: ");
            IspisIn(root);
            printf("\nPreorder: ");
            IspisPre(root);
            printf("\nPostorder: ");
            IspisPost(root);
            printf("\nLevel order: ");
            IspisLevel(root);
            printf("\n");
        }
        else if (izbor == 3) {
            printf("Unesite element za brisanje: ");
            scanf("%d", &el);
            root = Brisi(el, root);
        }
        else if (izbor == 4) {
            printf("Unesite element za trazenje: ");
            scanf("%d", &el);
            p = Trazi(el, root);

            if (p == NULL)
                printf("Element nije pronaden.\n");
            else
                printf("Element %d postoji u stablu.\n", p->El);
        }
        else if (izbor == 5) {
            root = ObrisiStablo(root);
            return 0;
        }
    }
}

/* dodavanje elementa */
Stablo Dodaj(int el, Stablo S) {
    if (S == NULL) {
        S = malloc(sizeof(struct CvorStabla));
        if (S == NULL) return NULL;
        S->El = el;
        S->Lijevo = NULL;
        S->Desno = NULL;
    }
    else if (el < S->El)
        S->Lijevo = Dodaj(el, S->Lijevo);
    else if (el > S->El)
        S->Desno = Dodaj(el, S->Desno);

    return S;
}

/* trazenje elementa */
Pozicija Trazi(int el, Stablo S) {
    if (S == NULL) return NULL;
    if (el < S->El) return Trazi(el, S->Lijevo);
    if (el > S->El) return Trazi(el, S->Desno);
    return S;
}

/* brisanje elementa */
Stablo Brisi(int el, Stablo S) {
    Pozicija temp;

    if (S == NULL) return NULL;

    if (el < S->El)
        S->Lijevo = Brisi(el, S->Lijevo);
    else if (el > S->El)
        S->Desno = Brisi(el, S->Desno);
    else {
        if (S->Lijevo != NULL && S->Desno != NULL) {
            temp = TraziMin(S->Desno);
            S->El = temp->El;
            S->Desno = Brisi(S->El, S->Desno);
        }
        else {
            temp = S;
            if (S->Lijevo != NULL)
                S = S->Lijevo;
            else
                S = S->Desno;
            free(temp);
        }
    }
    return S;
}

/* trazenje najmanjeg elementa */
Pozicija TraziMin(Stablo S) {
    while (S && S->Lijevo != NULL)
        S = S->Lijevo;
    return S;
}

/* inorder ispis */
void IspisIn(Stablo S) {
    if (S == NULL) return;
    IspisIn(S->Lijevo);
    printf("%d ", S->El);
    IspisIn(S->Desno);
}

/* preorder ispis */
void IspisPre(Stablo S) {
    if (S == NULL) return;
    printf("%d ", S->El);
    IspisPre(S->Lijevo);
    IspisPre(S->Desno);
}

/* postorder ispis */
void IspisPost(Stablo S) {
    if (S == NULL) return;
    IspisPost(S->Lijevo);
    IspisPost(S->Desno);
    printf("%d ", S->El);
}

/* visina stabla */
int Visina(Stablo S) {
    if (S == NULL) return 0;
    int l = Visina(S->Lijevo);
    int d = Visina(S->Desno);
    return (l > d ? l : d) + 1;
}

/* ispis jedne razine */
void IspisRazina(Stablo S, int razina) {
    if (S == NULL) return;
    if (razina == 1)
        printf("%d ", S->El);
    else {
        IspisRazina(S->Lijevo, razina - 1);
        IspisRazina(S->Desno, razina - 1);
    }
}

/* level order ispis */
void IspisLevel(Stablo S) {
    int h = Visina(S);
    for (int i = 1; i <= h; i++)
        IspisRazina(S, i);
}

/* brisanje cijelog stabla */
Stablo ObrisiStablo(Stablo S) {
    if (S == NULL) return NULL;
    ObrisiStablo(S->Lijevo);
    ObrisiStablo(S->Desno);
    free(S);
    return NULL;
}