/*Zaimplementować proste wersje programów ''head'' i ''tail''. Programy wypisują podaną ilość linii z początku/końca pliku.*/
#include <stdio.h>
#include <stdlib.h>
#define SIZE1 64
#define SIZE2 2048
int main(void){
    char filename[SIZE1], *singlerow;
    int i, lines = 0, nr, size, mode=0;
    FILE* fp;
    printf("\nEnter filename: ");                               //Pobranie danych
    scanf("%s", filename);
    sprintf(filename, "%s.txt", filename);
    if ((fp=fopen(filename,"r")) == NULL){
        printf("\nCannot open file %s\n", filename);
        return -1;
    }
    printf("\nEnter the number of lines to print: ");
    scanf("%d", &nr);

    printf("\n1. HEAD - from the beginning.\n"
           "2. TAIL - from the end.\nChoose: ");
    scanf("%d", &mode);
    putchar('\n');

    singlerow = (char*) malloc(SIZE2*sizeof(char));             //Przygotowanie miejsca na wers, który trzeba pobrać
    if(singlerow == NULL){
        printf("\nRAM error!\n");
        return -1;
    }

    if (mode == 2){                                             //Jeżeli tail to:
        fseek(fp, 0, SEEK_END);                                 //Idź na koniec
        size = ftell(fp);
        for(i=0; i<size; i++){
            fseek(fp, -i-lines, SEEK_END);                      //Poruszaj się krok po kroku do początku
            if(getc(fp) == '\n')                                //Szukając "entera"
                lines++;
            if(lines == nr)
                break;
        }
       if(i >= size){                                           //A jeśli tekst będzie za krótki
            fseek(fp, 0, SEEK_SET);                             //Ustaw kursor na początku
            nr=lines+1;                                         //I wypisz wszystkie linie
        }
    }

    for(i=0; fgets(singlerow, SIZE2, fp)!=NULL && i<nr; i++)    //Wydruk
        fputs(singlerow, stdout);
    putchar('\n');

    if (fclose(fp) != 0){
        printf("\nCannot close file %s\n", filename);
        return -1;
    }
    free(singlerow);                                            //Zwolnienie pamięci
    singlerow = NULL;
    return 0;
}

