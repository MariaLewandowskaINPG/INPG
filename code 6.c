/*Zaimplementować prostą wersję (bez wyrażeń regularnych) programu ''grep''. Program wypisuje
wszystkie linie z podanego pliku które zawierają wybraną frazę. Plik jest przetwarzany po linii.
Przykładowe wywołanie:
grep <fraza> <nazwa_pliku> */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE1 128
#define SIZE2 2048
int main(int argc, char *argv[]){
    char filename[SIZE1], *src = NULL;
    FILE *fp;
    int i, i2, phraselen, nextLine;
    if(argc != 3){
        printf("\nIncorrect amount of agruments! In the command prompt"
               " write: \n%s phrase filename\n", argv[0]);
        return -1;
    }
    sprintf(filename, "%s.txt", argv[2]);
    if ((fp=fopen(filename,"r")) == NULL){
        printf("\nCannot open file %s\n", filename);
        return -1;
    }
    src = (char*) malloc(SIZE2*sizeof(char));
    if(src == NULL){
        printf("\nRAM error!\n");
        return -1;
    }
    phraselen = strlen(argv[1]);
    for(;fgets(src, SIZE2, fp) != NULL;){
        for(i=0; src[i]!='\0' && nextLine == 0; i++)
            for(i2=0; src[i+i2] == argv[1][i2] && i2<phraselen; i2++)
                if(i2==phraselen-1){
                    fputs(src, stdout);
                    nextLine=1;                     //nextLine zabezpiecza przed wypisaniem tej samej linii wiele razy
                }                                   //na wypadek gdyby znalazło się tam wielokrotnie takie samo wyrażenie
    nextLine = 0;
    }
    if (fclose(fp) != 0){
        printf("\nCannot close file %s\n", filename);
        return -1;
    }
    free(src);
    src = NULL;
    return 0;
}


