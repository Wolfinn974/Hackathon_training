import java.io.*;
import java.util.*;

public class CSVExport {

    public static void exportCounts(String filename, Map<String, Integer> map) {
        try (PrintWriter pw = new PrintWriter(new FileWriter(filename))) {
            pw.println("key,count");
            for (var e : map.entrySet()) {
                pw.println(e.getKey() + "," + e.getValue());
            }
        } catch (Exception e) { e.printStackTrace(); }
    }

    public static void exportCombos(String filename, List<ComboAnalyzer.Combo> combos, int topk) {
        try (PrintWriter pw = new PrintWriter(new FileWriter(filename))) {
            pw.println("style,color,count");

            for (int i = 0; i < Math.min(topk, combos.size()); i++) {
                var c = combos.get(i);
                pw.println(c.style + "," + c.color + "," + c.count);
            }

        } catch (Exception e) { e.printStackTrace(); }
    }

    public static void exportPivot(String filename,
                                   List<String> sports,
                                   List<String> styles,
                                   int[][] table) {
        try (PrintWriter pw = new PrintWriter(new FileWriter(filename))) {

            pw.print("sport");
            for (String style : styles) pw.print("," + style);
            pw.println();

            for (int i = 0; i < sports.size(); i++) {
                pw.print(sports.get(i));
                for (int j = 0; j < styles.size(); j++) {
                    pw.print("," + table[i][j]);
                }
                pw.println();
            }

        } catch (Exception e) { e.printStackTrace(); }
    }
}