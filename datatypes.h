#ifndef _DATATYPES_H_
    #define _DATATYPES_H_
    #include <stdlib.h>

    #define int_value(p) (*((int *) p))
    #define float_value(p) (*((float *) p))
    #define double_value(p) (*((double *) p))

    typedef void type_t;

    int *int_new(int i);
    float *float_new(float f);
    double *double_new(double d);
#endif 
