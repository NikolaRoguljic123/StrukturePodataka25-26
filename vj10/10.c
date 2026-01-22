#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct CvorStabla* Stablo;

struct CvorStabla {
    char ime[50];       // ime drzave ili grada
    int broj;           // broj stanovnika za grad, 0 za drzavu
    Stablo Lijevo;
    Stablo Desno;
    Stablo Gradovi;     // za drzavu: pokazivac na stablo gradova
};


Stablo NoviCvor(char* ime, int broj) {
    Stablo c = (Stablo)malloc(sizeof(struct CvorStabla));
    strcpy(c->ime, ime);
    c->broj = broj;
    c->Lijevo = NULL;
    c->Desno = NULL;
    c->Gradovi = NULL;
    return c;
}


Stablo DodajGrad(Stablo root, char* ime, int broj) {
    if (!root) 
    return NoviCvor(ime, broj);
    if (broj < root->broj || (broj == root->broj && strcmp(ime, root->ime) < 0))
        root->Lijevo = DodajGrad(root->Lijevo, ime, broj);
    else
        root->Desno = DodajGrad(root->Desno, ime, broj);
    return root;
}


Stablo DodajDrzavu(Stablo root, char* ime, Stablo gradovi) {
    if (!root) return NoviCvor(ime, 0);  // broj=0 za drzavu
    if (strcmp(ime, root->ime) < 0)
        root->Lijevo = DodajDrzavu(root->Lijevo, ime, gradovi);
    else
        root->Desno = DodajDrzavu(root->Desno, ime, gradovi);

    root->Gradovi = gradovi; // spremi pokazivac na stablo gradova
    return root;
}


void IspisGradova(Stablo root) {
    if (!root) return;
    IspisGradova(root->Lijevo);
    printf("%s (%d)\n", root->ime, root->broj);
    IspisGradova(root->Desno);
}


void IspisDrzava(Stablo root) {
    if (!root) return;
    IspisDrzava(root->Lijevo);
    printf("Drzava: %s\n", root->ime);
    if (root->Gradovi)
        IspisGradova(root->Gradovi);
    printf("\n");
    IspisDrzava(root->Desno);
}


void PretragaGradova(Stablo root, char* imeDrzave, int minStan) {
    if (!root) return;
    if (strcmp(root->ime, imeDrzave) == 0) {
        printf("Gradovi u %s sa brojem stanovnika vecim od %d:\n", root->ime, minStan);
        Stablo g = root->Gradovi;
        if (!g) { printf("Nema gradova\n"); return; }
        // inorder prolazak i filtriranje
        if (g) {
            if (g->Lijevo) PretragaGradova(g->Lijevo, g->ime, minStan); // rekurzija na lijevo
            if (g->broj > minStan)
                printf("%s (%d)\n", g->ime, g->broj);
            if (g->Desno) PretragaGradova(g->Desno, g->ime, minStan); // rekurzija na desno
        }
    } else if (strcmp(imeDrzave, root->ime) < 0)
        PretragaGradova(root->Lijevo, imeDrzave, minStan);
    else
        PretragaGradova(root->Desno, imeDrzave, minStan);
}


Stablo UcitajDrzave() {
    FILE* f = fopen("drzave.txt", "r");
    if (!f) { printf("Ne mogu otvoriti drzave.txt\n"); return NULL; }

    Stablo root = NULL;
    char imeDrzave[50], imeDat[50];

    while (fscanf(f, "%s %s", imeDrzave, imeDat) != EOF) {
        FILE* fg = fopen(imeDat, "r");
        if (!fg) continue;

        Stablo stabloGradovi = NULL;
        char imeGrada[50];
        int broj;

        while (fscanf(fg, " %[^,],%d\n", imeGrada, &broj) != EOF) {
            stabloGradovi = DodajGrad(stabloGradovi, imeGrada, broj);
        }
        fclose(fg);

        root = DodajDrzavu(root, imeDrzave, stabloGradovi);
    }
    fclose(f);
    return root;
}

void ObrisiStablo(Stablo root) {
    if (!root) return;
    ObrisiStablo(root->Lijevo);
    ObrisiStablo(root->Desno);
    if (root->Gradovi) ObrisiStablo(root->Gradovi);
    free(root);
}

int main() {
    Stablo root = UcitajDrzave();

    printf("Ispis drzava i gradova:\n");
    IspisDrzava(root);

    char trazena[50];
    int minStan;
    printf("Unesite ime drzave za pretragu gradova: ");
    scanf("%s", trazena);
    printf("Unesite minimalan broj stanovnika: ");
    scanf("%d", &minStan);

    PretragaGradova(root, trazena, minStan);

    ObrisiStablo(root);
    return 0;
}