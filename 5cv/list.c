#include <stdio.h>
#include <stdlib.h>



int list_add (person **list, char name[], int age){
    person *new;
    new = malloc (sizeof (person));
    if (!new) return FALSE;

    strcpy(new->name, name);
    new->age = age;
    new->next = *list;
    *list = new;
    return TRUE;
    
}

void list_dump(person *list){
    while (list->next){
        printf("Name: %s, age: %d\n", list->name, list->age);
        list = list->next;
    }
}

void list_free(person **list){
    person *temp;

    while (*list)
    {
        printf("Freeing list: %s\n", (*list))->name);
        temp = (*list)->next;
        free(*list);
        *list = temp;
    }
    
    
    *list = NULL;
}

int main(){
    person *list = NULL;

    list_add(&list, "Pepa", 50);
    list_add(&list, "Tomas", 54);
    list_add(&list, "Karel", 43);
    list_add(&list, "Monika", 43);

    list_dump(list);
    list_free(&list);
    return EXIT_SUCCESS;
}