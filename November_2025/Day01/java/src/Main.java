import java.util.*;

public class Main {

    public static void main(String[] args) {

        List<Row> data = CSVLoader.load("data.csv");
        System.out.println("Loaded: " + data.size() + " rows");

        if (args.length > 0 && args[0].equals("--export")) {
            runExport(data);
        } else {
            runAnalysis(data);
        }
    }

    static void runAnalysis(List<Row> data) {

        System.out.println("\n=== Styles ===");
        var styles = Analyzer.valueCounts(data, "style");
        styles.forEach((k,v) -> System.out.println(k + ": " + v));

        System.out.println("\n=== Sports ===");
        var sports = Analyzer.valueCounts(data, "sport");
        sports.forEach((k,v) -> System.out.println(k + ": " + v));

        System.out.println("\n=== Budget moyen par style ===");
        var avg = Analyzer.averageBudgetByStyle(data);
        avg.forEach((k,v) -> System.out.println(k + ": " + String.format("%.2f", v)));

        System.out.println("\n=== Top 3 combos ===");
        var combos = ComboAnalyzer.topCombos(data);
        for (int i = 0; i < Math.min(3, combos.size()); i++) {
            var c = combos.get(i);
            System.out.println(c.style + " + " + c.color + ": " + c.count);
        }
    }

    static void runExport(List<Row> data) {

        var styles = Analyzer.valueCounts(data, "style");
        var sports = Analyzer.valueCounts(data, "sport");
        var combos = ComboAnalyzer.topCombos(data);

        var sportList = Analyzer.unique(data, "sport");
        var styleList = Analyzer.unique(data, "style");
        var pivot = PivotTable.build(data, sportList, styleList);

        System.out.println("Exporting files...");

        CSVExport.exportCounts("style_counts.csv", styles);
        CSVExport.exportCounts("sport_counts.csv", sports);
        CSVExport.exportCombos("top3_combos.csv", combos, 3);
        CSVExport.exportPivot("pivot_sport_style.csv", sportList, styleList, pivot);

        System.out.println("Done.");
    }
}