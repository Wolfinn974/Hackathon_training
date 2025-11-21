#include "data.h"

static const char *get_field(const Row *r, const char *field)
{
    if (strcmp(field, "sport") == 0) return r->sport;
    if (strcmp(field, "style") == 0) return r->style;
    if (strcmp(field, "gender") == 0) return r->gender;
    if (strcmp(field, "color") == 0) return r->color;

    return NULL;
}

// search for entry

static CountEntry *find_entry(CountEntry *entries, size_t count, const char *key)
{
    for (size_t i = 0; i < count; i++)
    {
        if (strcmp(entries[i].key, key) == 0)
            return &entries[i];
    }
    return NULL;
}

// dynamic table

CountEntry *value_counts(DataSet *ds, const char *field, size_t *out_size)
{
    CountEntry *entries = NULL;
    size_t count = 0;
    size_t capacity = 0;

    for (size_t i = 0; i < ds->count; i++) {
        const char *key = get_field(&ds->rows[i], field);
        if (!key)
            continue;

        CountEntry *existing = find_entry(entries, count, key);
        if (existing) {
            existing->count++;
        } else {
            if (count >= capacity) {
                size_t new_cap = (capacity == 0) ? 8 : capacity * 2;
                CountEntry *tmp = realloc(entries, new_cap * sizeof(CountEntry));
                if (!tmp) {
                    fprintf(stderr, "ERREUR realloc value_counts\n");
                    exit(EXIT_FAILURE);
                }
                entries = tmp;
                capacity = new_cap;
            }

            entries[count].key = ft_strdup(key);
            entries[count].count = 1;
            count++;
        }
    }

    *out_size = count;
    return entries;
}

// search average entry
static AvgEntry *find_avg_entry(AvgEntry *entries, size_t count, const char *key)
{
    for (size_t i = 0; i < count; i++)
        if (strcmp(entries[i].key, key) == 0)
            return &entries[i];
    return NULL;
}
//mean
AvgEntry *average_by(DataSet *ds, const char *field, size_t *out_size)
{
    AvgEntry *entries = NULL;
    size_t count = 0;
    size_t capacity = 0;

    for (size_t i = 0; i < ds->count; i++)
    {
        const char *key = get_field(&ds->rows[i], field);
        if (!key)
            continue;

        AvgEntry *existing = find_avg_entry(entries, count, key);
        if (existing)
        {
            existing->sum += ds->rows[i].budget;
            existing->count++;
        }
        else
        {
            if (count >= capacity)
            {
                size_t new_cap = (capacity == 0) ? 8 : capacity * 2;
                AvgEntry *tmp = realloc(entries, new_cap * sizeof(AvgEntry));
                if (!tmp)
                {
                    fprintf(stderr, "ERREUR realloc average_by\n");
                    exit(EXIT_FAILURE);
                }
                entries = tmp;
                capacity = new_cap;
            }

            entries[count].key = ft_strdup(key);
            entries[count].sum = ds->rows[i].budget;
            entries[count].count = 1;
            count++;
        }
    }

    *out_size = count;
    return entries;
}

//combo insight
static ComboEntry *find_combo_entry(ComboEntry *entries, size_t count,
                                    const char *k1, const char *k2)
{
    for (size_t i = 0; i < count; i++)
    {
        if (strcmp(entries[i].key1, k1) == 0 &&
            strcmp(entries[i].key2, k2) == 0)
            return &entries[i];
    }
    return NULL;
}
static int combo_cmp(const void *a, const void *b)
{
    const ComboEntry *ea = a;
    const ComboEntry *eb = b;

    return eb->count - ea->count;
}
ComboEntry *top_combos_style_color(DataSet *ds, size_t *out_size)
{
    ComboEntry *entries = NULL;
    size_t count = 0;
    size_t capacity = 0;

    for (size_t i = 0; i < ds->count; i++)
    {
        const char *style = ds->rows[i].style;
        const char *color = ds->rows[i].color;
        if (!style || !color)
            continue;

        ComboEntry *existing = find_combo_entry(entries, count, style, color);
        if (existing)
        {
            existing->count++;
        }
        else
        {
            if (count >= capacity)
            {
                size_t new_cap = (capacity == 0) ? 8 : capacity * 2;
                ComboEntry *tmp = realloc(entries, new_cap * sizeof(ComboEntry));
                if (!tmp)
                {
                    fprintf(stderr, "ERREUR realloc top_combos\n");
                    exit(EXIT_FAILURE);
                }
                entries = tmp;
                capacity = new_cap;
            }
            entries[count].key1 = ft_strdup(style);
            entries[count].key2 = ft_strdup(color);
            entries[count].count = 1;
            count++;
        }
    }

    qsort(entries, count, sizeof(ComboEntry), combo_cmp);

    *out_size = count;
    return entries;
}

void free_combo_entries(ComboEntry *entries, size_t n)
{
    if (!entries) return;
    for (size_t i = 0; i < n; i++)
    {
        free(entries[i].key1);
        free(entries[i].key2);
    }
    free(entries);
}

//pivot

static int index_of(char **keys, size_t n, const char *key)
{
    for (size_t i = 0; i < n; i++)
        if (strcmp(keys[i], key) == 0)
            return (int)i;
    return -1;
}

PivotTable *pivot_sport_style(DataSet *ds)
{
    PivotTable *pt = malloc(sizeof(PivotTable));
    if (!pt) return NULL;

    // 1) récupérer les sports uniques
    size_t n_sports = 0;
    CountEntry *sport_counts = value_counts(ds, "sport", &n_sports);

    // 2) récupérer les styles uniques
    size_t n_styles = 0;
    CountEntry *style_counts = value_counts(ds, "style", &n_styles);

    pt->n_rows = n_sports;
    pt->n_cols = n_styles;

    pt->row_keys = malloc(n_sports * sizeof(char *));
    pt->col_keys = malloc(n_styles * sizeof(char *));
    pt->counts   = malloc(n_sports * sizeof(int *));
    if (!pt->row_keys || !pt->col_keys || !pt->counts)
    {
        fprintf(stderr, "ERREUR malloc pivot_sport_style\n");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < n_sports; i++)
    {
        pt->row_keys[i] = ft_strdup(sport_counts[i].key);
        pt->counts[i] = calloc(n_styles, sizeof(int));
        if (!pt->counts[i])
        {
            fprintf(stderr, "ERREUR calloc pivot counts\n");
            exit(EXIT_FAILURE);
        }
    }

    for (size_t j = 0; j < n_styles; j++)
        pt->col_keys[j] = ft_strdup(style_counts[j].key);

    // 3) remplir la matrice
    for (size_t i = 0; i < ds->count; i++)
    {
        const char *sport = ds->rows[i].sport;
        const char *style = ds->rows[i].style;

        int r = index_of(pt->row_keys, pt->n_rows, sport);
        int c = index_of(pt->col_keys, pt->n_cols, style);

        if (r >= 0 && c >= 0)
            pt->counts[r][c] += 1;
    }

    // free les CountEntry utilisés seulement pour les clés
    for (size_t i = 0; i < n_sports; i++)
        free(sport_counts[i].key);
    free(sport_counts);

    for (size_t j = 0; j < n_styles; j++)
        free(style_counts[j].key);
    free(style_counts);

    return pt;
}

void free_pivot(PivotTable *pt)
{
    if (!pt) return;

    for (size_t i = 0; i < pt->n_rows; i++)
    {
        free(pt->row_keys[i]);
        free(pt->counts[i]);
    }
    free(pt->row_keys);

    for (size_t j = 0; j < pt->n_cols; j++)
        free(pt->col_keys[j]);
    free(pt->col_keys);

    free(pt->counts);
    free(pt);
}

//export csv

int export_counts_csv(const char *filename, CountEntry *entries, size_t n)
{
    FILE *f = fopen(filename, "w");
    if (!f)
    {
        perror(filename);
        return -1;
    }

    fprintf(f, "key,count\n");
    for (size_t i = 0; i < n; i++)
        fprintf(f, "%s,%d\n", entries[i].key, entries[i].count);

    fclose(f);
    return 0;
}

int export_pivot_csv(const char *filename, PivotTable *pt)
{
    FILE *f = fopen(filename, "w");
    if (!f)
    {
        perror(filename);
        return -1;
    }

    // header
    fprintf(f, "sport");
    for (size_t j = 0; j < pt->n_cols; j++)
        fprintf(f, ",%s", pt->col_keys[j]);
    fprintf(f, "\n");

    // rows
    for (size_t i = 0; i < pt->n_rows; i++)
    {
        fprintf(f, "%s", pt->row_keys[i]);
        for (size_t j = 0; j < pt->n_cols; j++)
            fprintf(f, ",%d", pt->counts[i][j]);
        fprintf(f, "\n");
    }

    fclose(f);
    return 0;
}

int export_combos_csv(const char *filename, ComboEntry *entries, size_t n, size_t topk)
{
    if (topk > n)
        topk = n;

    FILE *f = fopen(filename, "w");
    if (!f)
    {
        perror(filename);
        return -1;
    }

    fprintf(f, "style,color,count\n");
    for (size_t i = 0; i < topk; i++)
        fprintf(f, "%s,%s,%d\n", entries[i].key1, entries[i].key2, entries[i].count);

    fclose(f);
    return 0;
}