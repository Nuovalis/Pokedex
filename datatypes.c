#include "datatypes.h"

int *int_new(int i)
{
    int *new = malloc(sizeof(int));
    if (new != NULL) {
        *new = i;
    }
    return new;
}

float *float_new(float f)
{
    float *new = malloc(sizeof(float));
    if (new != NULL) {
        *new = f;
    }
    return new;
}

double *double_new(double d)
{
    double *new = malloc(sizeof(double));
    if (new != NULL) {
        *new = d;
    }
    return new;
}
