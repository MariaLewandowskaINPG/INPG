/*Zaimplementować dynamiczną listę dwukierunkową zawierającą dane osobowe :imię, nazwisko,
rok urodzenia. Program musi zawierać osobne funkcje realizujące następujące operacje:
* wyszukiwanie elementów wg. roku urodzenia, imienia, nazwiska
* dodawanie nowego elementu na początku listy
* dodawanie nowego elementu na końcu listy
* dodawanie nowego elementu w dowolnym miejscu listy (za wyszukanym)
* usuwanie elementu z początku listy
* usuwanie elementu z końca listy
* usuwanie elementu z dowolnego miejsca listy (wyszukanego)
* usuwanie całej listy (zwalnianie pamięci).
W programie proszę nie używać zmiennych globalnych.*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 64

struct list{
    char firstName[SIZE];
    char surname[SIZE];
    int year;
    struct list* prev;
    struct list* next;
};

void new_elem(struct list**, struct list**);
void new_beginning(struct list**, struct list**);
void new_end(struct list**, struct list**);
void new_else(struct list**, struct list**);
struct list* search_elem(struct list*, int);
struct list* search_year(struct list*, int);
struct list* search_surname(struct list*, int);
void delete_elem(struct list**, struct list**);
void delete_beginning(struct list**);
void delete_end(struct list**);
void delete_else(struct list**, struct list**);
void show_all(struct list*);
void freeRAM(struct list*, struct list*);

//----------------------------------------------------------------------------------------------------------

int main(void){
    int activity=0;
    struct list *head = NULL, *tail = NULL;
    for(system("cls");;system("cls")){
        printf("\nDOUBLY-LINKED LIST\n\n1. Add new element.\n2. Search for an element.\n3. Delete an element.\n"
               "4. Show database.\nTo complete, enter any letter.\n\nChoose activity: ");
            fflush(stdin);
            if(scanf("%d", &activity) == 0){
                (head, tail);
                return 1;
        }
        switch (activity){
            case 1:
                new_elem(&head, &tail);
                break;
            case 2:
                search_elem(head, 0);
                break;
            case 3:
                delete_elem(&head, &tail);
                break;
            case 4:
                show_all(head);
                break;
            default:
                printf("\nIncorrect choice. Try one more time.\nPress any key to continue.\n.");
                getch();
                continue;
        }
    }
    return 0;
}

//----------------------------------------------------------------------------------------------------------

void new_elem(struct list **head, struct list **tail){
    int choice;
    printf("\nA new record should be added:\n1. At the beginning.\n2. At the end.\n3. After an existing one.\n\nChoose: ");
    scanf("%d", &choice);
    switch (choice){
        case 1:
            printf("\nAdding a new record at the beginning of the list.\n");
            new_beginning(head, tail);
            break;
        case 2:
            printf("\nAdding a new record at the end of the list.\n");
            new_end(head, tail);
            break;
        case 3:
            printf("\nAdding a new record after an existing one.\n");
            new_else(head, tail);
            break;
        default:
            printf("\nIncorrect input. Try one more time.\nPress any key to continue.\n");
            getch();
    }
    return;
}

void new_beginning(struct list **head, struct list **tail){
    struct list *new_elem;
    new_elem = (struct list*) malloc (sizeof(struct list));
    if (new_elem == NULL)
        return;
    printf("\nFirst name: ");
    scanf("%s", new_elem->firstName);
    printf("Surname:    ");
    scanf("%s", new_elem->surname);
    printf("Year:       ");
    scanf("%d", &(new_elem->year));
    if(*head == NULL && *tail == NULL){
        new_elem->next = *head;
        new_elem->prev = NULL;
        *head = new_elem;
        *tail = new_elem;
    } else {
        new_elem->next = *head;
        new_elem->prev = NULL;
        (*head)->prev = new_elem;
        *head = new_elem;
    }
    printf("\nSuccess!\nPress any key to continue.\n");
    getch();
    return;
}

void new_end(struct list **head, struct list **tail){
    if (*head == NULL){
        new_beginning(head, tail);
        return;
    }
    struct list *new_elem;
    new_elem = (struct list*) malloc (sizeof(struct list));
    if (new_elem == NULL)
        return;
    printf("\nFirst name: ");
    scanf("%s", new_elem->firstName);
    printf("Surname:    ");
    scanf("%s", new_elem->surname);
    printf("Year:       ");
    scanf("%d", &(new_elem->year));
    if(*head == NULL && *tail == NULL){
        new_elem->next = NULL;
        new_elem->prev = NULL;
        *head = new_elem;
        *tail = new_elem;
    } else {
        new_elem->next = NULL;
        new_elem->prev = *tail;
        (*tail)->next = new_elem;
        *tail = new_elem;
    }
    printf("\nSuccess!\nPress any key to continue.\n");
    getch();
    return;
}

void new_else(struct list **head, struct list **tail){
    struct list *new_elem, *prev_elem;
    prev_elem = search_elem(*head, 1);
    if(prev_elem == NULL){
        printf(" Record cannot be added.\n");
        getch();
        return;
    } else if(prev_elem == *tail){
        new_end(head, tail);
        return;
    }
    new_elem = (struct list*) malloc (sizeof(struct list));
    if (new_elem == NULL)
        return;
    printf("\nFirst name: ");
    scanf("%s", new_elem->firstName);
    printf("Surname:    ");
    scanf("%s", new_elem->surname);
    printf("Year:       ");
    scanf("%d", &(new_elem->year));

    new_elem->next = prev_elem->next;
    new_elem->prev = prev_elem;
    (prev_elem->next)->prev = new_elem;
    prev_elem->next = new_elem;
    printf("\nSuccess!\nPress any key to continue.\n");
    getch();
    return;
}

//----------------------------------------------------------------------------------------------------------

struct list* search_elem(struct list *head, int mustReturn){
    struct list *obj = NULL;
    if(head == NULL){
        printf("\nThe list is empty. ");
    } else {
        int choice;
        printf("\nSearch by:\n1. Year of birth.\n2. Surname.\n\nChoose: ");
        scanf("%d", &choice);
        switch (choice){
        case 1:
            printf("\nChosen criterion: year of birth.\n");
            obj = search_year(head, mustReturn);
            break;
        case 2:
            printf("\nChosen criterion: surname.\n");
            obj = search_surname(head, mustReturn);
            break;
        default:
            printf("\nIncorrect input. Try one more time.\n");
            getch();
        }
    }
    if(!mustReturn){
        printf("\nPress any key to continue.\n");
        getch();
    }
    return obj;
}

struct list* search_year(struct list *head, int mustReturn){
    int wanted_year, i1=0, i2=0;
    struct list *p;
    printf("\nEnter the year of birth: ");
    scanf("%d", &wanted_year);
    for(p = head; p!=NULL; p=p->next, i1++)
        if(p->year == wanted_year){
            if(mustReturn){
                return p;
            } else {
                if(!i2)
                    printf("\nResults:\n\n No. | %15s | %15s |  Year\n", "First Name", "Surname");
                i2++;
                printf("%3d. | %15s | %15s | %4d\n", i1, p->firstName, p->surname, p->year);
            }
        }
    if(!i2)
        printf("\nNo one was found.");
    return NULL;
}

struct list* search_surname(struct list *head, int mustReturn){
    int i1=0, i2=0;
    char wanted_surname[SIZE];
    struct list* p;
    printf("\nEnter surname: ");
    scanf("%s", wanted_surname);

    for(p = head; p!=NULL; p=p->next, i1++)
        if(!strcmp(p->surname,wanted_surname)){
            if(mustReturn){
                return p;
            } else {
                if(!i2)
                    printf("\nResults:\n\n No. | %15s | %15s |  Year\n", "First Name", "Surname");
                i2++;
                printf("%3d. | %15s | %15s | %4d\n", i1, p->firstName, p->surname, p->year);
            }
        }
    if(!i2)
        printf("\nNo one was found.");
    return NULL;
}

//----------------------------------------------------------------------------------------------------------

void delete_elem(struct list **head, struct list **tail){
    if(*head == NULL){
        printf("\nThe list is empty. ");
    } else {
        int choice;
        printf("\nWhich record should be deleted?\n1. First.\n2. Last.\n3. Another one.\n\nChoose: ");
        scanf("%d", &choice);
        switch (choice){
        case 1:
            delete_beginning(head);
            break;
        case 2:
            delete_end(tail);
            break;
        case 3:
            delete_else(head, tail);
            break;
        default:
            printf("\nIncorrect input.\n");
        }
    }
    printf("\nPress any key to continue.\n");
    getch();
    return;
}

void delete_beginning(struct list **head){
    struct list *next_elem;
    int confirm;
    printf("\nAre you sure you want to delete the following record?\n");
    printf("\nFirst name: ");
    printf("%s", (*head)->firstName);
    printf("\nSurname:    ");
    printf("%s", (*head)->surname);
    printf("\nYear:       ");
    printf("%d", (*head)->year);
    printf("\n\nChoose 1 - yes lub 0 - no: ");
    scanf("%d", &confirm);
    if(confirm == 1){
        next_elem = (*head)->next;
        ((*head)->next)->prev=NULL;
        free(*head);
        *head = next_elem;
        printf("\nRecord has been deleted.");
    } else
        printf("\nRecord has not been deleted.");
    return;
}

void delete_end(struct list **tail){
    struct list *prev_elem;
    int confirm;
    if(*tail == NULL){
        printf("\nThe list is empty. ");
    } else {
        printf("\nAre you sure you want to delete the following record?\n");
        printf("\nFirst name: ");
        printf("%s", (*tail)->firstName);
        printf("\nSurname:    ");
        printf("%s", (*tail)->surname);
        printf("\nYear:       ");
        printf("%d", (*tail)->year);
        printf("\n\nChoose 1 - yes lub 0 - no: ");
        scanf("%d", &confirm);
        if(confirm == 1){
            prev_elem = (*tail)->prev;
            ((*tail)->prev)->next=NULL;
            free(*tail);
            *tail = prev_elem;
            printf("\nRecord has been deleted.");
        } else
            printf("\nRecord has not been deleted.");
    }
    return;
}

void delete_else(struct list **head, struct list **tail){
    struct list *p;
    int confirm;
    if(*head == NULL){
        printf("\nThe list is empty. ");
    } else {
        p = search_elem(*head, 1);
        if(p == NULL){
            printf(" Record cannot be deleted.\n");
        } else if (p == *head) {
            delete_beginning(head);
        } else if (p == *tail) {
             delete_end(tail);
        } else {
            printf("\nAre you sure you want to delete the following record?\n");
            printf("\nFirst name: ");
            printf("%s", p->firstName);
            printf("\nSurname:    ");
            printf("%s", p->surname);
            printf("\nYear:       ");
            printf("%d", p->year);
            printf("\n\nChoose 1 - yes lub 0 - no: ");
            scanf("%d", &confirm);
            if(confirm == 1){
                (p->prev)->next = p->next;
                (p->next)->prev = p->prev;
                free(p);
                p = NULL;
                printf("\nRecord has been deleted.");
            } else
                printf("\nRecord has not been deleted.");
       }
    }
    return;
}Krakow

void show_all(struct list* head){
    if(head == NULL){
        printf("\nThe list is empty. ");
    } else {
        struct list* p;
        int i=1;
        printf("\n\n No. | %15s | %15s |  Year\n", "First Name", "Surname");
        for(p = head; p!=NULL; p=p->next, i++)
            printf("%3d. | %15s | %15s | %4d\n", i, p->firstName, p->surname, p->year);
    }
    printf("\nPress any key to continue.\n");
    getch();
    return;
}

//----------------------------------------------------------------------------------------------------------

void freeRAM(struct list *head, struct list *tail){
    struct list *p, *next_elem;
    for(p = head; p!=NULL; p=next_elem){
        next_elem = p->next;
        free(p);
    }
    head = NULL;
    tail = NULL;
    return;
}

