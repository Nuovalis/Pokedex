#ifndef _POKEMON_TYPES_H_
    #define _POKEMON_TYPES_H_

    #include "linkedlist.h"
    #include <stdio.h>

    #define NUM_TYPES 18

    typedef enum {NORMAL, FIRE, WATER, ELECTRIC, GRASS, ICE, FIGHTING, POISON, GROUND, FLYING, PSYCHIC, BUG, ROCK, GHOST, DRAGON, DARK, STEEL, FAIRY
    } type_id;

    typedef struct pokemon_type {
        int id;
        char name[20];
        double effectiveness[NUM_TYPES];
        char immune[NUM_TYPES];  
    } pokemon_type;

    extern const pokemon_type TYPE_TABLE[NUM_TYPES];

    const pokemon_type *type_get_by_id(int id);
    const pokemon_type *type_get_by_name(const char *name);
    double type_effectiveness(const pokemon_type *attacker, const pokemon_type *defender);

#endif