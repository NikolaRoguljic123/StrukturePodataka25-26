#define CRT_SECURE_NO_WARNING
#define ERROR_NOT_OPENED
#include <stdio.h>

typedef struct {


	char ime;
	char prezime;
	int brojbodova;

}osoba;




int brojstud() {

	FILE* fp;
	int brojac = 0;
	fp = fopen("student.txt", "r");

	while (feof(fp) == 0) {

		brojac++;
		}
	printf("%d", brojac);
}