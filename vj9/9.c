#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* DEFINICIJA STRUKTURE (kao prije) */
typedef struct CvorStabla* Stablo;

struct CvorStabla {
    int El;
    Stablo Desno;
    Stablo Lijevo;
};

/* stvaranje novog cvora */
Stablo NoviCvor(int x) {
    Stablo c = (Stablo)malloc(sizeof(struct CvorStabla));
    if (!c) return NULL;
    c->El = x;
    c->Lijevo = NULL;
    c->Desno = NULL;
    return c;
}

/* a) INSERT – umetanje po razinama (level-order) */
Stablo Insert(Stablo root, int x) {
    if (root == NULL)
        return NoviCvor(x);

    Stablo red[100];
    int front = 0, rear = 0;

    red[rear++] = root;

    while (front < rear) {
        Stablo temp = red[front++];

        if (temp->Lijevo == NULL) {
            temp->Lijevo = NoviCvor(x);
            break;
        } else
            red[rear++] = temp->Lijevo;

        if (temp->Desno == NULL) {
            temp->Desno = NoviCvor(x);
            break;
        } else
            red[rear++] = temp->Desno;
    }
    return root;
}

/* inorder ispis u datoteku */
void InorderDatoteka(Stablo root, FILE* f) {
    if (!root) return;
    InorderDatoteka(root->Lijevo, f);
    fprintf(f, "%d ", root->El);
    InorderDatoteka(root->Desno, f);
}

/* b) REPLACE – zamjena vrijednosti sumom potomaka */
int Replace(Stablo root) {
    if (root == NULL)
        return 0;

    int sumaL = Replace(root->Lijevo);
    int sumaD = Replace(root->Desno);

    int staraVrijednost = root->El;
    root->El = sumaL + sumaD;

    return root->El + staraVrijednost;
}

/* oslobadanje memorije */
void ObrisiStablo(Stablo root) {
    if (!root) return;
    ObrisiStablo(root->Lijevo);
    ObrisiStablo(root->Desno);
    free(root);
}

int main(void) {
    Stablo root = NULL;
    FILE* f;
    int i, broj;

    /* c) generiranje slucajnih brojeva <10, 90> */
    srand((unsigned)time(NULL));

    for (i = 0; i < 10; i++) {
        broj = rand() % 81 + 10;   /* raspon 10–90 */
        root = Insert(root, broj);
    }

    f = fopen("studenti.txt", "w");
    if (!f) return 1;

    /* zapis nakon a) */
    fprintf(f, "Inorder nakon insert:\n");
    InorderDatoteka(root, f);
    fprintf(f, "\n");

    /* b) replace */
    Replace(root);

    /* zapis nakon b) */
    fprintf(f, "Inorder nakon replace:\n");
    InorderDatoteka(root, f);
    fprintf(f, "\n");

    fclose(f);
    ObrisiStablo(root);
    return 0;
}