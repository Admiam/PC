#include "searchers.h"

/**
 * Klíč k úspěchu!
 *
 * ! `struct commodity comms[]` == `struct commodity *comms`
 * ! `comm_id_array_type id` == `char ids[MAX_ID_LENGTH]`
 * ! `comm_id_array_type ids[]` == `char(*ids)[MAX_ID_LENGTH]`
 * ! `comm_id_array_type ids[]` == `char(ids[])[MAX_ID_LENGTH]`
 */

/**
 * Funkce ke studiu:
 *
 * `qsort`      https://en.cppreference.com/w/c/algorithm/qsort
 * `bsearch`    https://en.cppreference.com/w/c/algorithm/bsearch
 * `strcmp`     https://en.cppreference.com/w/c/string/byte/strcmp
 */

/** INFO: pro rychlejší debugging snižte hodnotu TEST_RUNS v souboru `config.h`. */

int linear_search(const struct commodity comms[], const size_t comms_count,
                    const comm_id_array_type ids[], const size_t ids_count, int quantities[]) {
    size_t i, j;
    int found;

    if (!comms || comms_count == 0 || !ids || ids_count == 0 || !quantities) {
        return EXIT_FAILURE;
    }

    for (i = 0; i < ids_count; ++i) {
        found = 0;

        for (j = 0; j < comms_count; ++j) {
            if (strcmp(ids[i], comms[j].id) == 0) {
                quantities[i] = comms[j].quantity;
                found = 1;
                break;
            }
        }

        if (!found) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}

int compare_commodity(const void *a, const void *b)
{
    struct commodity *commodity_a = (struct commodity *)a;
    struct commodity *commodity_b = (struct commodity *)b;

    return strcmp(commodity_a->id, commodity_b->id);
}

int compare_commodity2(const void *a, const void *b)
{
    struct commodity *commodity_b = (struct commodity *)b;

    return strcmp(a, commodity_b->id);
}

/* TODO */
int binary_search(const struct commodity comms[], const size_t comms_count, const comm_id_array_type ids[], const size_t ids_count, int quantities[])
{
    if (comms == NULL || comms_count == 0 || ids == NULL || ids_count == 0 || quantities == NULL)
    {
        return EXIT_FAILURE;
    }

    size_t i;
    struct commodity *found;
    struct commodity *copy_commodity = malloc(sizeof(struct commodity) * comms_count);

    if (copy_commodity == NULL)
    {
        return EXIT_FAILURE;
    }
    
    memcpy(copy_commodity, comms, sizeof(struct commodity) * comms_count);

    qsort(copy_commodity, comms_count, sizeof(struct commodity) * comms_count, compare_commodity);

    for (i = 0; i < ids_count; i++)
    {
        found = bsearch(ids[i], copy_commodity, comms_count, sizeof(struct commodity) * comms_count, compare_commodity2);
       printf("true \n");
        if (found == NULL)
        {
            free(copy_commodity);
            return EXIT_FAILURE;
        }
        quantities[i] = found->quantity;
    }
    

    free(copy_commodity);
    return EXIT_SUCCESS;

}