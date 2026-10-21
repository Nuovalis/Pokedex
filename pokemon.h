#ifndef _POKEMON_H_
    #define _POKEMON_H_

    #include "linkedlist.h"
    #include "pokemontypes.h"
    #include <stdio.h>

    typedef enum { SEARCH_BY_ID, SEARCH_BY_NAME, SEARCH_BY_DEXNO } pokemon_search_field;

    typedef struct pokemon {
        int id;
        int dexno;
        char name[20];
        const pokemon_type *type1;
        const pokemon_type *type2;
        char species[20];
        double weight;
        char entry[200];
    } pokemon;

    pokemon *pokemon_create(int dexno, const char *name, const pokemon_type *type1, const pokemon_type *type2, const char *species, double weight, const char *entry);
    int add_pokemon_first(linked_list_t *pokedex, pokemon *newPokemon);
    int add_pokemon_last(linked_list_t *pokedex, pokemon *newPokemon);
    int add_pokemon_middle(linked_list_t *pokedex, pokemon *newPokemon, int position);
    int update_pokemon(linked_list_t *pokedex, pokemon *newPokemon);
    int remove_pokemon_first(linked_list_t *pokedex);
    int remove_pokemon_last(linked_list_t *pokedex);
    int remove_pokemon_middle(linked_list_t *pokedex, int position);
    void print_pokemon(type_t *data);
    void update_dex_number(linked_list_t *pokedex);
    double type_effectiveness_vs_pokemon(const pokemon_type *attacker, const pokemon *defender);
    void pokemon_id_counter_sync(linked_list_t *pokedex);
    int (*pokemon_comparator(pokemon_search_field field))(type_t *, type_t *);
    int pokemon_search(linked_list_t *pokedex, pokemon *target, pokemon_search_field field);
    int sort_pokedex(linked_list_t *pokedex, pokemon_search_field field);

#endif