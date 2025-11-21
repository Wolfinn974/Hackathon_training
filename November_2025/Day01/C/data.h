#ifndef DATA_H
#define DATA_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LINE_MAX 512
#define FIELD_MAX 64

typedef struct {
	int id;
	char *gender;
	char *sport;
	char *style;
	char *color;
	double budget;
} Row;

typedef struct {
	char *key;
	int count;
} CountEntry;

typedef struct {
	char *key;
	double sum;
	int count;
} AvgEntry;

typedef struct{
    Row *rows;
    size_t count;
    size_t capacity;
}DataSet;

// utils

int	ft_atoi(const char *str);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strdup(const char *src);
size_t	ft_strlen(const char *s);
void trim_newline(char *s);

// data

DataSet *create_dataset();
void add_row(DataSet *ds, Row row);
void free_dataset(DataSet *ds);
//static Row parse_line(const char *line);
DataSet *load_csv(const char *file);

//Analysis

//static const char *get_field(const Row *r, const char *field);
//static CountEntry *find_entry(CountEntry *entries, size_t count, const char *key);
CountEntry *value_counts(DataSet *ds, const char *field, size_t *out_size);
//static AvgEntry *find_avg_entry(AvgEntry *entries, size_t count, const char *key);
AvgEntry *average_by(DataSet *ds, const char *field, size_t *out_size);


// addons

typedef struct {
	char *key1;
	char *key2;
	int count;
} ComboEntry;

ComboEntry *top_combos_style_color(DataSet *ds, size_t *out_size);
void free_combo_entries(ComboEntry *entries, size_t n);

typedef struct {
	char **row_keys;  // sports
	size_t n_rows;
	char **col_keys;  // styles
	size_t n_cols;
	int **counts;     // [n_rows][n_cols]
} PivotTable;

PivotTable *pivot_sport_style(DataSet *ds);
void free_pivot(PivotTable *pt);
int export_counts_csv(const char *filename, CountEntry *entries, size_t n);
int export_pivot_csv(const char *filename, PivotTable *pt);
int export_combos_csv(const char *filename, ComboEntry *entries, size_t n, size_t topk);



#endif
