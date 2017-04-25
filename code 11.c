 /*3. Napisz funkcję char * deleteLastChar(char* s) która wylicza długość napisu s i usuwa z niego ostatni
 znak poprzez zmniejszenie rozmiaru tablicy zawierającej napis - funkcja przydziela dokładnie tyle pamięci,
 ile potrzebuje nowy napis (bez ostatniej litery) i zwalnia pamięć przydzieloną staremu. Funkcja zwraca
 adres nowo przydzielonej pamięci. Po każdym usunięciu kolejnego znaku program (main) ma wypisać napis.
 W funkcji proszę nie używać funkcji realloc().
UWAGA:
 Przy testowaniu funkcji w programie głównym (main) napis przekazywany do funkcji deleteChar musi być
 alokowany dynamicznie - w przeciwnym razie funkcja deleteChar będzie próbowała zwolnić pamięć przydzielaną
 statycznie (należy dynamicznie utworzyć 100-elementową tablicę znakową i wczytać do niej napis przy użyciu
funkcji fgets). */
#include <stdio.h>
#include <stdlib.h>
#define SIZE 100

char * deleteLastChar(char* s);

int main(void){
    char *str;
    int i, n;
    str = (char*) malloc(SIZE * sizeof(char));
    if (str == NULL){
        printf("\nRAM error.\n");
        return -1;
    }
    printf("\nEnter your text: ");
    fgets(str, SIZE, stdin);
    printf("How many characters should be deleted? ");
    scanf("%d", &n);
    if (n<1){
        printf("\nThis variable must be positive!\n");
        return -1;
    }
    for(i=0; str[i]!='\0'; i++);
    if(n>=i){
        n=i-1;
        printf("\nYour text is not long enough."
               " %d characters will be deleted.\n",n);
    }
    for(i=0; i<=n; i++){
        str = deleteLastChar(str);
        if (str == NULL){
            printf("\nRAM error.\n");
            return -1;
        }
        puts(str);
    }
    free(str);
    str = NULL;
    return 0;
}

char * deleteLastChar(char* s){
    char *tmp;
    int i, n;
    for(i=0; s[i]!='\0' ; i++);
    n=i;
    tmp = (char*) malloc(n*sizeof(char));
    if (tmp == NULL){
        printf("\nRAM error.\n");
        return NULL;
    }
    for(i=0; i<n; i++)
        tmp[i]=s[i];
    tmp[n-1]='\0';
    free(s);
    s = NULL;
    return tmp;
}