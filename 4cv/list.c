/**
 * @file list.c
 * @author František Pártl (fpartl@ntis.zcu.cz)
 * @brief Soubor s cvičnou implementací jednosměrně zřetězeného spojového seznamu.
 * @version 1.0
 * @date 2020-09-03
 *
 * Program můžete zkontrolovat pomocí nástroje Valgrind následovně:
 *     gcc list.c -o list -Wall -Wextra -pedantic -ansi -g
 *     valgrind --leak-check=full ./list
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/** \brief Počet bytů pro uložení jména osoby. */
#define PERSON_NAME_LENGTH 64

/**
 * @brief Struktura představující jednoho člověka, u kterého sledujeme jeho jméno, věk a velikost bot.
 */
struct person
{
    char name[PERSON_NAME_LENGTH];
    unsigned short age, shoe_size;
};

/**
 * @brief Prvek spojového seznamu instancí struktury person.
 */
struct person_list_node
{
    struct person data;
    struct person_list_node *next;
};

/**
 * @brief Funkce přidá novou instanci struktury person na začátek zadaného spojového seznamu.
 *
 * @param list Spojový seznam, kam bude prvek přidán.
 * @param name Jméno nové osoby.
 * @param age Věk nové osoby.
 * @param shoe_size Velikost bot nové osoby.
 * @return int `1` pokud funkce dokončí své konání v pořádku, jinak `0`.
 */
int person_ll_add(struct person_list_node **list, const char *name, const unsigned short age, const unsigned short shoe_size)
{
    struct person_list_node *new;

    if (!list || !name)
    {
        return 0;
    }

    new = malloc(sizeof(*new));
    if (!new)
    {
        return 0;
    }
    strncpy(new->data.name, name, PERSON_NAME_LENGTH);
    (*new).data.age = age;
    new->data.shoe_size = shoe_size;

    new->next = *list;
    *list = new;
    return 1;
}

/**
 * @brief Funkce slouží k vypsání spojového seznamu s prvky typu person_list_node.
 * @param list Ukazatel na spojový seznam, jehož prvky mají být vypsány.
 */
void person_ll_print(const struct person_list_node *list)
{
    struct person_list_node *current = list;

    while (current != NULL)
    {
        printf("List: %s\n", current->data.name);
        current = current->next;
    }
}

/**
 * @brief Funkce sloužící k uvolnění spojového seznamu s prvky typu person_list_node.
 * @param list Ukazatel na ukazatel na spojový seznam, který má být uvolněn.
 */
void person_ll_free(struct person_list_node **list)
{ /* Proč zde předáváme ukazatel na ukazatel? */
    
    if (*list != NULL)
    {
        struct person_list_node *current = *list;
        struct person_list_node *next;

        while (current != NULL)
        {
            next = current->next;
            printf("Clearing: %s\n", current->data.name);
            free(current);
            current = next;
        }
        *list = NULL;
    }
    
}

/**
 * @brief Hlavní přístupový bod aplikace. Obsahuje definici spojového seznamu head, jeho naplnění, vypsání a uvolnění.
 * @return int Funkce vždy vrací hodnotu EXIT_SUCCESS.
 */
int main()
{
    struct person_list_node *head = NULL;

    person_ll_add(&head, "Vlastislav Cepicka", 26, 35);
    person_ll_add(&head, "Robert Cepicka", 34, 47);
    person_ll_add(&head, "Karel Cepicka", 56, 45);
    person_ll_add(&head, "Branka Cepicka", 14, 39);

    person_ll_print(head);

    person_ll_free(&head); /* Zkuste si zakomentovat tento řádek a sledujte co na to řekne Valgrind. */
    return EXIT_SUCCESS;
}
