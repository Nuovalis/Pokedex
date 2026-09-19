#ifndef _POKEMON_H_
    #define _POKEMON_H_

    #include "linkedlist.h"
    #include <stdio.h>

    typedef struct pokemon {
        int id;
        int dexno;
        char name[20];
        char type; //to do: Add types
        char species[20];
        double weight;
        char entry[200];
    } pokemon;

    pokemon *pokemon_create(int id, int dexno, const char name[20], char type, const char species[20], double weight, const char entry[200]);
    void add_pokemon_first(linked_list_t *pokedex, pokemon *newPokemon);
    void add_pokemon_last(linked_list_t *pokedex, pokemon *newPokemon);
    void add_pokemon_middle(linked_list_t *pokedex, pokemon *newPokemon, int position);
    void update_pokemon(linked_list_t *pokedex, pokemon *newPokemon);
    void remove_pokemon_first(linked_list_t *pokedex);
    void remove_pokemon_last(linked_list_t *pokedex);
    void remove_pokemon_middle(linked_list_t *pokedex, int position);
    void print_pokemon(type_t *data);

#endif