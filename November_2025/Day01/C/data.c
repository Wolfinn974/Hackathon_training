#include "data.h"

// create dynamic dataset

DataSet *create_dataset()
{
    DataSet *ds = malloc(sizeof(DataSet));
    if (!ds)
        return NULL;
    ds->rows = NULL;
    ds->count = 0;
    ds->capacity = 0;
    return ds;
}
//row add to dataset
void add_row(DataSet *ds, Row row)
{
    if (ds->count >= ds->capacity)
    {
        size_t new_cap = (ds->capacity == 0) ? 16 : ds->capacity * 2;
        Row *tmp = realloc(ds->rows, new_cap * sizeof(Row));
        if (!tmp)
        {
            fprintf(stderr, "ERREUR: Realloc échoué dans add_row()\n");
            exit(EXIT_FAILURE);
        }
        ds->rows = tmp;
        ds->capacity = new_cap;
    }
    ds->rows[ds->count] = row;
    ds->count++;
}

// free dataset

void free_dataset(DataSet *ds)
{
    if (!ds)
        return;

    for (size_t i = 0; i < ds->count; i++)
    {
        free(ds->rows[i].gender);
        free(ds->rows[i].sport);
        free(ds->rows[i].style);
        free(ds->rows[i].color);
    }
    free(ds->rows);
    free(ds);
}

// parsing csv line in Row
static Row parse_line(const char *line)
{
    Row r;
    r.id = 0;
    r.gender = NULL;
    r.sport = NULL;
    r.style = NULL;
    r.color = NULL;
    r.budget = 0;

    char *copy = ft_strdup(line);
    char *token = strtok(copy, ",");

    int col = 0;
    while (token)
    {
        switch (col) {
            case 0: r.id = ft_atoi(token);break;
            case 1: r.gender = ft_strdup(token); break;
            case 2: r.sport = ft_strdup(token); break;
            case 3: r.style = ft_strdup(token); break;
            case 4: r.color = ft_strdup(token); break;
            case 5: r.budget = atof(token); break;
        }
        col++;
        token = strtok(NULL, ",");
    }

    free(copy);
    return r;
}

//load complete csv

DataSet *load_csv(const char *file)
{
    FILE *f = fopen(file, "r");

    if(!f)
    {
        perror(file);
        return NULL;
    }

    DataSet *ds = create_dataset();

    char line[1024];

    if (!fgets(line, sizeof(line), f))
    {
        fclose(f);
        return ds;
    }

    while (fgets(line, sizeof(line), f))
    {
        trim_newline(line);

        if (line[0] == '\0')
            continue;

        Row r = parse_line(line);
        add_row(ds, r);
    }

    fclose(f);
    return ds;
}