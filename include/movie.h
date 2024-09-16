#ifndef _MOVIE_H_
#define _MOVIE_H_

#include <stdio.h>
#include <stdlib.h>
#define BUFF_SZ 256

typedef struct s_movie {
    int id;
    int year;
    int director_id;
    char name[BUFF_SZ];
    char url[BUFF_SZ];
} Movie;

Movie *movie_read_next(FILE *input);
Movie **movie_read_all(FILE *input, int *count);

#endif