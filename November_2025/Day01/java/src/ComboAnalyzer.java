import java.util.*;

public class ComboAnalyzer {

    public static class Combo {
        public String style;
        public String color;
        public int count;

        public Combo(String s, String c, int ct) {
            style = s;
            color = c;
            count = ct;
        }
    }

    public static List<Combo> topCombos(List<Row> rows) {
        Map<String, Integer> map = new HashMap<>();

        for (Row r : rows) {
            if (r.style == null || r.color == null) continue;

            String key = r.style + "|" + r.color;
            map.put(key, map.getOrDefault(key, 0) + 1);
        }

        // Transform map → list
        List<Combo> combos = new ArrayList<>();
        for (var entry : map.entrySet()) {
            String[] parts = entry.getKey().split("\\|");
            combos.add(new Combo(parts[0], parts[1], entry.getValue()));
        }

        // Trier décroissant
        combos.sort((a, b) -> b.count - a.count);

        return combos;
    }
}