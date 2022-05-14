#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED

typedef struct
{
    int    year;
    int    month;
    int    day;
    int    hour;
    int    minute;
    double second;
} datetime_t;

typedef struct
{
    char*       filename;
    datetime_t* time;
    double*     relative_time;
    int*        value1;
    int*        value2;
    double*     value3;
    double*     value3_sorted;
    double*     value1_modified;
    double*     value2_modified;
    double*     value3_modified;
    int         length;
} dataset_t;

#endif // TYPES_H_INCLUDED
