#include "pokemon.h"
#include <stdlib.h>
#include <string.h>

static int next_pokemon_id = 1;

static pokemon *pokemon_dup(const pokemon *p)
{
    if (!p) { printf("Error: no pokemon to duplicate.\n"); return NULL; }
    pokemon *copy = malloc(sizeof(pokemon));
    if (copy) *copy = *p;
    return copy;
}

static int pokemon_compare_id(type_t *a, type_t *b)
{
    return (((pokemon *)a)->id > ((pokemon *)b)->id) - (((pokemon *)a)->id < ((pokemon *)b)->id);
    //todo: replace id compares with this format: (a > b) - (a < b)
}

static int pokemon_compare_name(type_t *a, type_t *b)
{
    return strcmp(((pokemon *)a)->name, ((pokemon *)b)->name);
}

static int pokemon_compare_dexno(type_t *a, type_t *b)
{
    return (((pokemon *)a)->dexno > ((pokemon *)b)->dexno) - (((pokemon *)a)->dexno < ((pokemon *)b)->dexno);
}

static int (*comparator_table[])(type_t *, type_t *) = {
    [SEARCH_BY_ID]    = pokemon_compare_id,
    [SEARCH_BY_NAME]  = pokemon_compare_name,
    [SEARCH_BY_DEXNO] = pokemon_compare_dexno,
};

static int validate_pokemon(const pokemon *p)
{
    if (!p) { printf("Error: no pokemon to validate.\n"); return 0; }
    if (!p->type1) { printf("Error: no primary type specified.\n"); return 0; }
    if (p->type2 && p->type1 == p->type2) { printf("Error: both types cannot be the same.\n"); return 0; }
    if (p->dexno <= 0) { printf("Error: invalid dex number.\n"); return 0; }
    if (p->weight <= 0) { printf("Error: invalid weight.\n"); return 0; }
    if (strlen(p->name) == 0 || strlen(p->species) == 0 || strlen(p->entry) == 0) { printf("Error: one or more required fields are empty.\n"); return 0; }
    if (strlen(p->name) >= sizeof(p->name) || strlen(p->species) >= sizeof(p->species) || strlen(p->entry) >= sizeof(p->entry)) { printf("Error: one or more fields exceed maximum length.\n"); return 0; }
    return 1;
}

static pokemon *prepare_insert(linked_list_t *pokedex, pokemon *src)
{
    if (!validate_pokemon(src)) {
        return NULL;
    }
    if (list_found(*pokedex, src, pokemon_compare_id)) {
        printf("Error: Pokemon with ID %d already exists in the Pokedex.\n", src->id);
        return NULL;
    }
    return pokemon_dup(src);
}

pokemon *pokemon_create(int dexno, const char *name, const pokemon_type *type1, const pokemon_type *type2, const char *species, double weight, const char *entry)
{
    pokemon *pokeptr = malloc(sizeof(pokemon));

    if (pokeptr != NULL){
        pokeptr->id = next_pokemon_id++;
        pokeptr->dexno = dexno;
        strncpy(pokeptr->name, name, sizeof pokeptr->name - 1);
        pokeptr->name[sizeof pokeptr->name - 1] = '\0';
        pokeptr->type1 = type1;
        pokeptr->type2 = type2;
        strncpy(pokeptr->species, species, sizeof pokeptr->species - 1);
        pokeptr->species[sizeof pokeptr->species - 1] = '\0';
        pokeptr->weight = weight;
        strncpy(pokeptr->entry, entry, sizeof pokeptr->entry - 1);
        pokeptr->entry[sizeof pokeptr->entry - 1] = '\0';
    } 

    return pokeptr;
}

int add_pokemon_first(linked_list_t *pokedex, pokemon *newPokemon)
{
    pokemon *p = prepare_insert(pokedex ,newPokemon);
    if (!p) return 0;  // If preparation failed, do not add to the list
    list_add_first(pokedex, p);
    return 1;
}

int add_pokemon_last(linked_list_t *pokedex, pokemon *newPokemon)
{
    pokemon *p = prepare_insert(pokedex, newPokemon);
    if (!p) return 0;  // If preparation failed, do not add to the list
    list_add_last(pokedex, p);
    return 1;
}

int add_pokemon_middle(linked_list_t *pokedex, pokemon *newPokemon, int position)
{
    if (position < 0 || position > pokedex->size) return 0;
    pokemon *p = prepare_insert(pokedex, newPokemon);
    if (!p) return 0;
    list_add_middle(pokedex, p, position);
    return 1;
}

int update_pokemon(linked_list_t *pokedex, pokemon *newPokemon)
{
    if (!validate_pokemon(newPokemon)) {
        printf("Error: Invalid pokemon data.\n");
        return 0;
    }
    int position = list_find_position(*pokedex, newPokemon, pokemon_compare_id);
    int pointerPosition = 0;
    node_t *head = pokedex->first;
    pokemon *p = pokemon_dup(newPokemon);

    if(position != -1){
        while (pointerPosition != position)
        {
            head = head->next;
            
            pointerPosition++;
        }
        list_modify(head, p);
    } else{
        printf("Couldn't find the pokemon to update\n");
        free(p);
        return 0;
    }
    return 1;
}

int remove_pokemon_first(linked_list_t *pokedex)
{
    if (pokedex->first == NULL) {
        return 0;
    }
    pokemon *p = pokedex->first->data;
    list_delete_first(pokedex);
    free(p);
    return 1;
}

int remove_pokemon_last(linked_list_t *pokedex)
{
    if (pokedex->first == NULL) {
        return 0;
    }
    pokemon *p = pokedex->last->data;
    list_delete_last(pokedex);
    free(p);
    return 1;
}

int remove_pokemon_middle(linked_list_t *pokedex, int position)
{
    if (pokedex->first == NULL) return 0;
    pokemon *p = list_get(*pokedex, position);   // NULL if position is invalid
    if (p == NULL) return 0;      
    list_delete_middle(pokedex, position);
    free(p);
    return 1;
}

void print_pokemon(type_t *data) 
{
    pokemon *p = (pokemon *)data;
    char types[41];  // "Type1/Type2" max

    if (p->type2 != NULL) {
        snprintf(types, sizeof(types), "%s/%s", p->type1->name, p->type2->name);
    } else {
        snprintf(types, sizeof(types), "%s", p->type1->name);
    }

    printf("#%d %s (%s) - %.1fkg - %s\n",
           p->dexno, p->name, p->species, p->weight, types);
}

void update_dex_number(linked_list_t *pokedex)
{
    int pointerPosition = 0;
    node_t *head = pokedex->first;
    pokemon *p;
    while (head != NULL) 
    {
        p = head->data;
        p->dexno = pointerPosition + 1;
        pointerPosition++;
        head = head->next;
    }
}

double type_effectiveness_vs_pokemon(const pokemon_type *attacker, const pokemon *defender)
{
    if (attacker == NULL || defender == NULL) return 1.0;

    double multiplier = 1.0;

    multiplier *= type_effectiveness(attacker, defender->type1);

    if (defender->type2 != NULL) {
        multiplier *= type_effectiveness(attacker, defender->type2);
    }

    return multiplier;
}

void pokemon_id_counter_sync(linked_list_t *pokedex)
{
    node_t *ptr = pokedex->first;
    while (ptr != NULL) {
        pokemon *p = ptr->data;
        if (p->id >= next_pokemon_id) {
            next_pokemon_id = p->id + 1;
        }
        ptr = ptr->next;
    }
}

int (*pokemon_comparator(pokemon_search_field field))(type_t *, type_t *)
{
    if (field < 0 || field >= (int)(sizeof(comparator_table) / sizeof(comparator_table[0]))) {
        return NULL;
    }
    return comparator_table[field];
}

int pokemon_search(linked_list_t *pokedex, pokemon *target, pokemon_search_field field)
{
    int (*comparator)(type_t *, type_t *) = pokemon_comparator(field);
    if (!comparator) {
        printf("Error: Invalid search field.\n");
        return -1;
    }
    return list_find_position(*pokedex, target, comparator);
}

int sort_pokedex(linked_list_t *pokedex, pokemon_search_field field)
{
    int (*comparator)(type_t *, type_t *) = pokemon_comparator(field);
    if (!comparator) {
        printf("Error: Invalid sort field.\n");
        return 0;
    }

    list_sort(pokedex, comparator);

    return 1; // Return 1 to indicate success
}