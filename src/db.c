#include <string.h>
#include <math.h>
#include "db.h"

Movie *binsearch_in_memory(FILE *input, char *name)
{
    int cmp, middle, upper, lower = 0;
    Movie **movies = movie_read_all(input, &upper);
    upper--; // Treat it as index

    while (upper != lower)
    {
        middle = (int)ceilf((upper - lower) / 2. + lower);

        if (middle == upper)
            break;

        cmp = strcmp(name, movies[middle]->name);
        if (cmp == 0)
            return movies[middle];

        if (cmp < 0)
            upper = middle;

        if (cmp > 0)
            lower = middle;
    }

    return NULL;
}

Movie *binsearch_in_file(FILE *input, char *name)
{
    int cmp, middle, upper, lower = 0;
    fseek(input, 0, SEEK_END);
    upper = ftell(input) / sizeof(Movie) - 1;
    fseek(input, 0, SEEK_SET);
    Movie *movie = (Movie *)malloc(sizeof(Movie));

    while (upper != lower)
    {
        middle = (int)ceilf((upper - lower) / 2. + lower);

        if (middle == upper)
            break;

        fseek(input, middle * sizeof(Movie), SEEK_SET);
        fread(movie, sizeof(Movie), 1, input);

        cmp = strcmp(name, movie->name);
        if (cmp == 0)
            return movie;

        if (cmp < 0)
            upper = middle;

        if (cmp > 0)
            lower = middle;
    }

    return NULL;
}