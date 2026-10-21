#include <stdio.h>
#include "pokemon.h"

#define STRLEN 100

/*
To do list:
Add a way to search for a pokemon by:
Name
Dex number
Type
Type Effectiveness
Weight Tresholds
Implement filters for the search functions
Add sort feature
*/

int main()
{
    linked_list_t pokedex = LINKEDLISTINIT;
    pokemon *bulbasaur = pokemon_create(1, "Bulbasaur", &TYPE_TABLE[GRASS], &TYPE_TABLE[POISON], "Bulb", 25.6, "A small grass type perfect for beginners.");
    pokemon *charmander = pokemon_create(4, "Charmander", &TYPE_TABLE[FIRE], NULL, "Lizard", 30.2, "Small reptilian pokemon that is protective of its tail.");
    pokemon *squirtle = pokemon_create(3, "Squirtle", &TYPE_TABLE[WATER], NULL, "Turtle", 34.3, "Capable of hiding in its shell and propulsing at fast speeds.");
    pokemon *yoshi = pokemon_create(8, "Yoshi", &TYPE_TABLE[DRAGON], NULL, "Dinosaur", 120.4, "Wait, this ain't a pokemon!");

    //Test adding and updating pokemon
    add_pokemon_first(&pokedex, bulbasaur);
    add_pokemon_last(&pokedex, squirtle);
    add_pokemon_middle(&pokedex, charmander, 1);
    squirtle->dexno = 3;
    update_pokemon(&pokedex, squirtle);
    list_display(pokedex, print_pokemon);
    add_pokemon_first(&pokedex, yoshi);
    update_dex_number(&pokedex);
    list_display(pokedex, print_pokemon);

    //Damage effectiveness test
    printf("The damage multiplier is: %.2f\n", type_effectiveness_vs_pokemon(bulbasaur->type1, yoshi));

    //Test sorting and searching
    sort_pokedex(&pokedex, SEARCH_BY_NAME);
    list_display(pokedex, print_pokemon);
    sort_pokedex(&pokedex, SEARCH_BY_DEXNO);
    list_display(pokedex, print_pokemon);
    sort_pokedex(&pokedex, SEARCH_BY_ID);
    list_display(pokedex, print_pokemon);
    
    //Test removing pokemon
    remove_pokemon_middle(&pokedex, 1);
    remove_pokemon_last(&pokedex);
    remove_pokemon_first(&pokedex);
    update_dex_number(&pokedex);
    list_display(pokedex, print_pokemon);
    list_free_all(&pokedex);
    free(bulbasaur);
    free(charmander);
    free(squirtle);
    free(yoshi);
}