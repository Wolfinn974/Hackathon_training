#include "data.h"

static void run_analysis(DataSet *ds)
{
    printf("Loaded %zu rows.\n", ds->count);

    printf("\n=== Styles ===\n");
    size_t n_style = 0;
    CountEntry *styles = value_counts(ds, "style", &n_style);
    for (size_t i = 0; i < n_style; i++)
        printf("%s: %d\n", styles[i].key, styles[i].count);

    printf("\n=== Sports ===\n");
    size_t n_sport = 0;
    CountEntry *sports = value_counts(ds, "sport", &n_sport);
    for (size_t i = 0; i < n_sport; i++)
        printf("%s: %d\n", sports[i].key, sports[i].count);

    printf("\n=== Budget moyen par style ===\n");
    size_t n_avg = 0;
    AvgEntry *avg = average_by(ds, "style", &n_avg);
    for (size_t i = 0; i < n_avg; i++)
    {
        double mean = avg[i].sum / avg[i].count;
        printf("%s: %.2f\n", avg[i].key, mean);
    }

    printf("\n=== Top 3 combos style+color ===\n");
    size_t n_combo = 0;
    ComboEntry *combos = top_combos_style_color(ds, &n_combo);
    size_t topk = n_combo < 3 ? n_combo : 3;
    for (size_t i = 0; i < topk; i++)
        printf("%s + %s: %d\n", combos[i].key1, combos[i].key2, combos[i].count);

    // free
    for (size_t i = 0; i < n_style; i++) free(styles[i].key);
    free(styles);

    for (size_t i = 0; i < n_sport; i++) free(sports[i].key);
    free(sports);

    for (size_t i = 0; i < n_avg; i++) free(avg[i].key);
    free(avg);

    free_combo_entries(combos, n_combo);
}

static void run_export(DataSet *ds)
{
    size_t n_style = 0, n_sport = 0, n_avg = 0, n_combo = 0;

    CountEntry *styles = value_counts(ds, "style", &n_style);
    CountEntry *sports = value_counts(ds, "sport", &n_sport);
    AvgEntry *avg = average_by(ds, "style", &n_avg);
    ComboEntry *combos = top_combos_style_color(ds, &n_combo);
    PivotTable *pt = pivot_sport_style(ds);

    printf("Exporting CSV files...\n");

    export_counts_csv("style_counts.csv", styles, n_style);
    export_counts_csv("sport_counts.csv", sports, n_sport);
    export_pivot_csv("pivot_sport_style.csv", pt);
    export_combos_csv("top3_combos.csv", combos, n_combo, 3);

    // free
    for (size_t i = 0; i < n_style; i++) free(styles[i].key);
    free(styles);

    for (size_t i = 0; i < n_sport; i++) free(sports[i].key);
    free(sports);

    for (size_t i = 0; i < n_avg; i++) free(avg[i].key);
    free(avg);

    free_combo_entries(combos, n_combo);
    free_pivot(pt);
}

int main(int argc, char **argv)
{
    DataSet *ds = load_csv("data.csv");
    if (!ds)
    {
        fprintf(stderr, "Erreur : impossible de charger data.csv\n");
        return 1;
    }

    if (argc > 1 && strcmp(argv[1], "--export") == 0)
        run_export(ds);
    else
        run_analysis(ds);

    free_dataset(ds);
    return 0;
}