#include "pokemon.h"
#include <stdlib.h>
#include <string.h>

static pokemon *pokemon_dup(const pokemon *p)
{
    pokemon *copy = malloc(sizeof(pokemon));
    if (copy) *copy = *p;
    return copy;
}

static int pokemon_compare_id(type_t *a, type_t *b)
{
    return ((pokemon *)a)->id - ((pokemon *)b)->id;
}

pokemon *pokemon_create(int id, int dexno, const char name[20], char type, const char species[20], double weight, const char entry[200])
{
    pokemon *pokeptr = malloc(sizeof(pokemon));

    if (pokeptr != NULL){
        pokeptr->id = id;
        pokeptr->dexno = dexno;
        strncpy(pokeptr->name, name, sizeof pokeptr->name - 1);
        pokeptr->name[sizeof pokeptr->name - 1] = '\0';
        pokeptr->type = type;
        strncpy(pokeptr->species, species, sizeof pokeptr->species - 1);
        pokeptr->species[sizeof pokeptr->species - 1] = '\0';
        pokeptr->weight = weight;
        strncpy(pokeptr->entry, entry, sizeof pokeptr->entry - 1);
        pokeptr->entry[sizeof pokeptr->entry - 1] = '\0';
    } 

    return pokeptr;
}

void add_pokemon_first(linked_list_t *pokedex, pokemon *newPokemon)
{
    pokemon *p = pokemon_dup(newPokemon);
    if (!p) { printf("Error: not enough memory.\n"); return; }
    list_add_first(pokedex, p);
}

void add_pokemon_last(linked_list_t *pokedex, pokemon *newPokemon)
{
    pokemon *p = pokemon_dup(newPokemon);
    if (!p) { printf("Error: not enough memory.\n"); return; }
    list_add_last(pokedex, p);
}

void add_pokemon_middle(linked_list_t *pokedex, pokemon *newPokemon, int position)
{
    pokemon *p = pokemon_dup(newPokemon);
    if (!p) { printf("Error: not enough memory.\n"); return; }
    list_add_middle(pokedex, p, position);
}

void update_pokemon(linked_list_t *pokedex, pokemon *newPokemon)
{
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
    }
}

void remove_pokemon_first(linked_list_t *pokedex)
{
    list_delete_first(pokedex);
}

void remove_pokemon_last(linked_list_t *pokedex)
{
    list_delete_last(pokedex);
}

void remove_pokemon_middle(linked_list_t *pokedex, int position)
{
    list_delete_middle(pokedex, position);
}

void print_pokemon(type_t *data) 
{
    pokemon *p = (pokemon *)data;
    printf("#%d %s (%s) - %.1fkg\n", p->dexno, p->name, p->species, p->weight);
}