#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "movie.h"
#include "db.h"

int convert_to_bin(void)
{
    FILE *file = fopen("input/arqMovies.txt", "r");
    int count = 0;
    Movie **movies = movie_read_all(file, &count);
    FILE *out = fopen("input/arqMovies.bin", "wb");

    for (int i = 0; i < count; i++)
        fwrite(movies[i], sizeof(Movie), 1, out);

    fclose(out);
    return EXIT_SUCCESS;
}

int run_binsearch_file(void)
{
    int count, pos;
    clock_t time;
    char name[256];
    bool found;

    printf("Inform the movie name:\n");
    gets(name);

    time = clock(); // Start to count time

    FILE *file = fopen("input/arqMovies.bin", "rb");
    fseek(file, 0, SEEK_END);
    count = ftell(file) / sizeof(Movie);
    fseek(file, 0, SEEK_SET);

    Movie *movie = binsearch_in_file(file, 0, count - 1, name, &pos, &found);

    double time_taken = ((double)time) / CLOCKS_PER_SEC * 1000;

    if (movie == NULL)
    {
        printf("Movie \"%s\" was not found!\n", name);
        printf("Took %f milliseconds\n", time_taken);
        return EXIT_FAILURE;
    }

    printf("Movie \"%s\" found!\n", name);
    printf("Took %f milliseconds\n", time_taken);

    return EXIT_SUCCESS;
}

int run_binsearch_memory(void)
{
    int count, pos;
    clock_t time;
    char name[256];
    bool found;

    printf("Inform the movie name:\n");
    gets(name);

    time = clock(); // Start to count time

    FILE *file = fopen("input/arqMovies.txt", "r");
    Movie **movies = movie_read_all(file, &count);
    Movie *movie = binsearch_in_memory(movies, 0, count - 1, name, &pos, &found);

    double time_taken = ((double)time) / CLOCKS_PER_SEC * 1000;
    if (movie == NULL)
    {
        printf("Movie \"%s\" was not found!\n", name);
        printf("Took %f milliseconds\n", time_taken);
        return EXIT_FAILURE;
    }

    printf("Movie \"%s\" found!\n", name);
    printf("Took %f milliseconds\n", time_taken);

    return EXIT_SUCCESS;
}

int main(void)
{
    int option;
    char name[256];

    printf("Choose and option:\n");
    printf(" 1 - Dump text file;\n");
    printf(" 2 - Bin. search in memory;\n");
    printf(" 3 - Bin. search in file (no indexing);\n");
    printf(" 4 - Run indexing by ID;\n");
    printf(" 5 - Bin. search in file (with indexing);\n");
    printf(" 6 - Add new movie;\n");

    scanf("%d", &option);
    getchar();

    switch (option)
    {
    case 1:
        return convert_to_bin();
        break;

    case 2:
        return run_binsearch_memory();
        break;

    case 3:
        return run_binsearch_file();
        break;

    case 4:
        break;

    case 5:
        index_movies_by_id("id");
        break;

    default:
        printf("Invalid option!\n");
    }

    return EXIT_FAILURE;
}
