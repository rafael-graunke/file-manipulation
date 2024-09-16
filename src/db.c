#include <string.h>
#include <math.h>
#include "db.h"

Movie *binsearch_in_memory(FILE *input, char *name, int *iter)
{
    int cmp, middle, upper, lower = 0;
    Movie **movies = movie_read_all(input, &upper);
    upper--; // Treat it as index

    while (upper != lower)
    {
        *iter += 1;
        middle = (int)ceilf((upper - lower) / 2. + lower);

        if (middle == upper)
            break;

        cmp = strcmp(name, movies[middle]->name);
        if (cmp == 0)
            return movies[middle];

        if (cmp < 0)
        {
            printf("\"%s\" comes BEFORE \"%s\"\n", name, movies[middle]->name);
            upper = middle;
        }

        if (cmp > 0)
        {
            printf("\"%s\" comes AFTER \"%s\"\n", name, movies[middle]->name);
            lower = middle;
        }
    }

    return NULL;
}

Movie *binsearch_in_file(FILE *input, char *name, int *iter)
{
    int cmp, middle, upper, lower = 0;
    fseek(input, 0, SEEK_END);
    upper = ftell(input) / sizeof(Movie) - 1;
    Movie *movie = (Movie *)malloc(sizeof(Movie));

    while (upper != lower)
    {
        *iter += 1;
        middle = (int)ceilf((upper - lower) / 2. + lower);

        if (middle == upper)
            break;

        fseek(input, middle * sizeof(Movie), SEEK_SET);
        fread(movie, sizeof(Movie), 1, input);

        cmp = strcmp(name, movie->name);
        if (cmp == 0)
            return movie;

        if (cmp < 0)
        {
            printf("\"%s\" comes BEFORE \"%s\"\n", name, movie->name);
            upper = middle;
        }

        if (cmp > 0)
        {
            printf("\"%s\" comes AFTER \"%s\"\n", name, movie->name);
            lower = middle;
        }
    }

    return NULL;
}