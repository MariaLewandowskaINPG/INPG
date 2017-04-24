/*Zaimplementować strukturę opisującą liczbę zespoloną, a następnie funkcje realizujące podstawowe
 operacje na liczbach zespolonych (obowiązkowo dodawanie, moduł, liczba sprzężona, nadobowiązkowo
odejmowanie, mnożenie dzielenie). Funkcje, których wynikiem działania jest struktura powinny ją
zwrócić poprzez return.
W wypisywaniu liczby zespolonej można się posłużyć przykładową funkcją:
void wypisz_zesp(struct complex z) {
printf("%.2f %+.2fi \n", z.re, z.im);
}
gdzie z jest zmienną strukturalną o polach re i im (to jest przykładowa struktura - państwo użyją tu własnych struktur).*/
#include <stdio.h>
#include <math.h>

struct complex{
    double re;
    double im;
};

void wypisz_zesp(struct complex);
struct complex getComplex(char);
struct complex addition(void);
struct complex subtraction(void);
struct complex multiplication(void);
struct complex divistion(void);
struct complex module(void);
struct complex conjugate(void);

int main(void){
    char sign;
    struct complex a, b, complexNumber;
    printf("\nComplex numbres calculator.\n");
    printf("\n+ - addition\n- - subtraction\n* - multiplication\n/ - divistion"
           "\nm - module\nc - conjugate\n\nChoose the operation: ");
    scanf("%c", &sign);
    putchar('\n');
    switch (sign){
        case '+': complexNumber = addition(); break;
        case '-': complexNumber = subtraction(); break;
        case '*': complexNumber = multiplication(); break;
        case '/': complexNumber = divistion(); break;
        case 'm': complexNumber = module(); break;
        case 'c': complexNumber = conjugate(); break;
        default:
            printf("Incorrect sign!\n");
            return -1;
    }
    wypisz_zesp(complexNumber);
    return 0;
}

void wypisz_zesp(struct complex z) {
    printf("\nResult: %.2lf %+.2lfi \n", z.re, z.im);
}

struct complex getComplex(char name) {
    struct complex variable;
    printf("Enter number %c:\nRe(%c) = ", name,name);
    scanf("%lf", &(variable.re));
    printf("Im(%c) = ", name);
    scanf("%lf", &(variable.im));
    return variable;
}

struct complex addition(void){
    struct complex result;
    struct complex a = getComplex('a');
    struct complex b = getComplex('b');
    result.re = a.re + b.re;
    result.im = a.im + b.im;
    return result;
}

struct complex subtraction(void){
    struct complex result;
    struct complex a = getComplex('a');
    struct complex b = getComplex('b');
    result.re = a.re - b.re;
    result.im = a.im - b.im;
    return result;
}

struct complex multiplication(void){
    struct complex result;
    struct complex a = getComplex('a');
    struct complex b = getComplex('b');
    result.re = a.re * b.re - a.im * b.im;
    result.im = a.re * b.im + a.im * b.re;
    return result;
}

struct complex divistion(void){
    struct complex result;
    struct complex a = getComplex('a');
    struct complex b = getComplex('b');
    result.re = (a.re * b.re + a.im * b.im) / (b.re * b.re + b.im * b.im);
    result.im = (a.im * b.re - a.re * b.im) / (b.re * b.re + b.im * b.im);
    return result;
}

struct complex module(void){
    struct complex result;
    struct complex a = getComplex('a');
    result.re = sqrt(a.re * a.re + a.im * a.im);
    result.im = 0;
    return result;
}

struct complex conjugate(void){
    struct complex result;
    struct complex a = getComplex('a');
    result.re = a.re;
    result.im = -a.im;
    return result;
}


