
#define _CRT_SECURE_NO_WARNINGS
#define N 50
#define ERROR_OPENING_FILE -1
#define maxpoints 500
#include <stdio.h>
#include <stdlib.h>


typedef struct{

    char ime[N];
    char prezime[N];
    int broj;
    
    
}student;


int izbrojS(char *file);

int main() {
    
    
    student* sp=NULL;
    
    char *file = "studenti.txt";
    
    int brojstudenata = izbrojS(file);
    

    
    
    
    sp = (student*)malloc(sizeof(student)*brojstudenata);

    
    
    FILE *fp= NULL;
    
    fp = fopen("studenti.txt","r");
    
    
    if(fp == NULL){
    printf("Error opening file\n");
      return ERROR_OPENING_FILE;
        
    }
    
    for(int i=0;i<brojstudenata;i++){
    
     fscanf(fp,"%s %s %d",sp[i].ime,sp[i].prezime,&sp[i].broj);


}
    fclose(fp);
 
  for(int i=0;i<brojstudenata;i++){
     
     float percentage = ((float)sp[i].broj/maxpoints)*100;
     printf("%s %s %d %f ",sp[i].ime,sp[i].prezime,sp[i].broj,percentage);
 



}
    return 0;
}


int izbrojS(char *file){

    FILE* fp;
    char ch;
    int count = 0;

    fp = fopen("studenti.txt", "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        return ERROR_OPENING_FILE;
    }

    while ((ch = fgetc(fp)) != EOF) {
        if (ch == '\n') {
            count++;
        }
    }

    fclose(fp);
   
    return count;
}
    



























