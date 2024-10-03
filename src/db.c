#include <string.h>
#include <math.h>
#include "db.h"

Movie *binsearch_in_memory(Movie **movies, int start, int end, char *name, int *pos, bool *found)
{
    int middle;
    *found = false;
    Movie *cursor;
    if (start <= end)
    {
        middle = (end + start) / 2;
        cursor = movies[middle];

        int cmp = strcmp(name, cursor->name);
        if (cmp == 0)
        {
            *found = true;
            *pos = middle;
            return cursor;
        }

        else if (cmp < 0)
            return binsearch_in_memory(movies, start, middle - 1, name, pos, found);
        else
            return binsearch_in_memory(movies, middle + 1, end, name, pos, found);
    }

    return NULL;
}

Movie *binsearch_in_file(FILE *movies, int start, int end, char *name, int *pos, bool *found)
{
    int middle;
    *found = false;
    Movie *cursor = (Movie *)malloc(sizeof(Movie));

    if (start <= end)
    {
        middle = (end + start) / 2;
        fseek(movies, sizeof(Movie) * middle, SEEK_SET);
        fread(cursor, sizeof(Movie), 1, movies);

        int cmp = strcmp(name, cursor->name);

        if (cmp == 0)
        {
            *found = true;
            *pos = middle;
            return cursor;
        }

        else if (cmp < 0)
            return binsearch_in_file(movies, start, middle - 1, name, pos, found);
        else
            return binsearch_in_file(movies, middle + 1, end, name, pos, found);
    }

    return NULL;
}

int compare(const void *arg1, const void *arg2)
{
    return ((MovieIndex *)arg1)->id - ((MovieIndex *)arg2)->id;
}

MovieIndex *index_movies_by_id(char *index_name)
{
    FILE *source = fopen("input/arqMovies.bin", "rb");
    if (source == NULL)
        exit(EXIT_FAILURE);

    fseek(source, 0, SEEK_END);
    int count = ftell(source) / sizeof(Movie);
    rewind(source);

    Movie **movies = (Movie **)malloc(sizeof(Movie *) * count);

    for (int i = 0; i < count; i++)
    {
        movies[i] = (Movie *)malloc(sizeof(Movie));
        fread(movies[i], sizeof(Movie), 1, source);
    }

    char buffer[256];
    snprintf(buffer, 256, "input/index/%s", index_name);
    FILE *index = fopen(buffer, "wb");
    MovieIndex *indexes = (MovieIndex *)malloc(sizeof(Movie) * count);
    for (int i = 0; i < count; i++)
    {
        indexes[i].id = movies[i]->id;
        indexes[i].addr = sizeof(Movie) * i;
    }

    qsort(indexes, count, sizeof(MovieIndex), compare);
    for (int i = 0; i < count; i++)
        fwrite(&(indexes[i]), sizeof(MovieIndex), 1, index);

    return indexes;
}
