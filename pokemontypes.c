#include "pokemontypes.h"
#include <stdlib.h>
#include <string.h>

const pokemon_type *type_get_by_id(int id)
{
    return (id >= 0 && id < NUM_TYPES) ? &TYPE_TABLE[id] : NULL;
}

const pokemon_type *type_get_by_name(const char *name)
{
    for (int i = 0; i < NUM_TYPES; i++) {
        if (strcmp(TYPE_TABLE[i].name, name) == 0) {
            return &TYPE_TABLE[i];
        }
    }
    return NULL;
}

double type_effectiveness(const pokemon_type *attacker, const pokemon_type *defender)
{
    if (attacker->immune[defender->id]) return 0.0;
    double v = attacker->effectiveness[defender->id];
    return (v == 0.0) ? 1.0 : v;
}

const pokemon_type normal =
{
    .id = NORMAL,
    .name = "Normal",
    .effectiveness = {
        [ROCK]  = 0.5,
        [STEEL] = 0.5,
    },
    .immune = {
        [GHOST] = 1
    }
};

const pokemon_type fire =
{
    .id = FIRE,
    .name = "Fire",
    .effectiveness = {
        [GRASS] = 2.0,
        [ICE] = 2.0,
        [STEEL] = 2.0,
        [BUG] = 2.0,
        [FIRE] = 0.5,
        [WATER] = 0.5,
        [ROCK]  = 0.5,
        [DRAGON] = 0.5
    },
    .immune = {0}
};

const pokemon_type water =
{
    .id = WATER,
    .name = "Water",
    .effectiveness = {
        [FIRE] = 2.0,
        [ROCK] = 2.0,
        [GROUND] = 2.0,
        [WATER] = 0.5,
        [GRASS]  = 0.5,
        [DRAGON] = 0.5
    },
    .immune = {0}
};

const pokemon_type electric =
{
    .id = ELECTRIC,
    .name = "Electric",
    .effectiveness = {
        [WATER] = 2.0,
        [FLYING] = 2.0,
        [ELECTRIC] = 0.5,
        [GRASS]  = 0.5,
        [DRAGON] = 0.5
    },
    .immune = {
        [GROUND] = 1
    }
};

const pokemon_type grass =
{
    .id = GRASS,
    .name = "Grass",
    .effectiveness = {
        [WATER] = 2.0,
        [GROUND] = 2.0,
        [ROCK] = 2.0,
        [FIRE] = 0.5,
        [BUG] = 0.5,
        [POISON] = 0.5,
        [FLYING] = 0.5,
        [GRASS]  = 0.5,
        [DRAGON] = 0.5,
        [STEEL] = 0.5
    },
    .immune = {0}
};

const pokemon_type ice =
{
    .id = ICE,
    .name = "Ice",
    .effectiveness = {
        [FLYING] = 2.0,
        [GROUND] = 2.0,
        [DRAGON] = 2.0,
        [GRASS] = 2.0,
        [FIRE] = 0.5,
        [ICE] = 0.5,
        [WATER] = 0.5,
        [STEEL] = 0.5
    },
    .immune = {0}
};

const pokemon_type fighting =
{
    .id = FIGHTING,
    .name = "Fighting",
    .effectiveness = {
        [ROCK] = 2.0,
        [DARK] = 2.0,
        [STEEL] = 2.0,
        [NORMAL] = 2.0,
        [ICE] = 2.0,
        [POISON] = 0.5,
        [FLYING] = 0.5,
        [PSYCHIC] = 0.5,
        [BUG] = 0.5
    },
    .immune = {
        [GHOST] = 1
    }
};

const pokemon_type poison =
{
    .id = POISON,
    .name = "Poison",
    .effectiveness = {
        [GRASS] = 2.0,
        [FAIRY] = 2.0,
        [POISON] = 0.5,
        [GROUND] = 0.5,
        [ROCK] = 0.5,
        [GHOST] = 0.5
    },
    .immune = {
        [STEEL] = 1
    }
};

const pokemon_type ground =
{
    .id = GROUND,
    .name = "Ground",
    .effectiveness = {
        [FIRE] = 2.0,
        [ELECTRIC] = 2.0,
        [POISON] = 2.0,
        [STEEL] = 2.0,
        [ROCK] = 2.0,
        [GRASS] = 0.5,
        [BUG] = 0.5
    },
    .immune = {
        [FLYING] = 1
    }
};

const pokemon_type flying =
{
    .id = FLYING,
    .name = "Flying",
    .effectiveness = {
        [GRASS] = 2.0,
        [BUG] = 2.0,
        [FIGHTING] = 2.0,
        [ELECTRIC] = 0.5,
        [ROCK] = 0.5,
        [STEEL] = 0.5
    },
    .immune = {0}
};

const pokemon_type psychic =
{
    .id = PSYCHIC,
    .name = "Psychic",
    .effectiveness = {
        [POISON] = 2.0,
        [FIGHTING] = 2.0,
        [PSYCHIC] = 0.5,
        [STEEL] = 0.5
    },
    .immune = {
        [DARK] = 1
    }
};

const pokemon_type bug =
{
    .id = BUG,
    .name = "Bug",
    .effectiveness = {
        [GRASS] = 2.0,
        [PSYCHIC] = 2.0,
        [DARK] = 2.0,
        [FIRE] = 0.5,
        [FIGHTING] = 0.5,
        [FAIRY] = 0.5,
        [POISON] = 0.5,
        [FLYING] = 0.5,
        [GHOST] = 0.5,
        [STEEL] = 0.5
    },
    .immune = {0}
};

const pokemon_type rock =
{
    .id = ROCK,
    .name = "Rock",
    .effectiveness = {
        [FIRE] = 2.0,
        [BUG] = 2.0,
        [FLYING] = 2.0,
        [ICE] = 2.0,
        [FIGHTING] = 0.5,
        [GROUND] = 0.5,
        [STEEL] = 0.5
    },
    .immune = {0}
};

const pokemon_type ghost =
{
    .id = GHOST,
    .name = "Ghost",
    .effectiveness = {
        [PSYCHIC] = 2.0,
        [GHOST] = 2.0,
        [DARK] = 0.5,
    },
    .immune = {
        [NORMAL] = 1
    }
};

const pokemon_type dragon =
{
    .id = DRAGON,
    .name = "Dragon",
    .effectiveness = {
        [DRAGON] = 2.0,
        [STEEL] = 0.5,
    },
    .immune = {
        [FAIRY] = 1
    }
};

const pokemon_type dark =
{
    .id = DARK,
    .name = "Dark",
    .effectiveness = {
        [PSYCHIC] = 2.0,
        [GHOST] = 2.0,
        [FIGHTING] = 0.5,
        [DARK] = 0.5,
        [FAIRY] = 0.5
    },
    .immune = {0}
};

const pokemon_type steel =
{
    .id = STEEL,
    .name = "Steel",
    .effectiveness = {
        [ICE] = 2.0,
        [ROCK] = 2.0,
        [FAIRY] = 2.0,
        [FIRE] = 0.5,
        [WATER] = 0.5,
        [STEEL] = 0.5,
        [ELECTRIC] = 0.5
    },
    .immune = {0}
};

const pokemon_type fairy =
{
    .id = FAIRY,
    .name = "Fairy",
    .effectiveness = {
        [FIGHTING] = 2.0,
        [DRAGON] = 2.0,
        [DARK] = 2.0,
        [FIRE] = 0.5,
        [POISON] = 0.5,
        [STEEL] = 0.5
    },
    .immune = {0}
};

//FIRE, WATER, ELECTRIC, GRASS, ICE, FIGHTING, POISON, GROUND, FLYING, PSYCHIC, BUG, ROCK, GHOST, DRAGON, DARK, STEEL, FAIRY;

const pokemon_type TYPE_TABLE[NUM_TYPES] = {
    normal, fire, water, electric, grass, ice, fighting, poison, ground, flying, psychic, bug, rock, ghost, dragon, dark, steel, fairy
};