import java.util.*;

public class Analyzer {

    // ----------- VALUE COUNTS -----------
    public static Map<String, Integer> valueCounts(List<Row> rows, String field) {
        Map<String, Integer> map = new HashMap<>();

        for (Row r : rows) {
            String key = getField(r, field);
            if (key == null) continue;

            map.put(key, map.getOrDefault(key, 0) + 1);
        }
        return map;
    }

    private static String getField(Row r, String field) {
        return switch (field) {
            case "gender" -> r.gender;
            case "sport" -> r.sport;
            case "style" -> r.style;
            case "color" -> r.color;
            default -> null;
        };
    }

    // ----------- AVERAGE BUDGET -----------
    public static Map<String, Double> averageBudgetByStyle(List<Row> rows) {
        Map<String, Double> sum = new HashMap<>();
        Map<String, Integer> count = new HashMap<>();

        for (Row r : rows) {
            sum.put(r.style, sum.getOrDefault(r.style, 0.0) + r.budget);
            count.put(r.style, count.getOrDefault(r.style, 0) + 1);
        }

        Map<String, Double> result = new HashMap<>();
        for (String key : sum.keySet()) {
            result.put(key, sum.get(key) / count.get(key));
        }
        return result;
    }

    // ----------- UNIQUE VALUES -----------
    public static List<String> unique(List<Row> rows, String field) {
        Set<String> set = new HashSet<>();

        for (Row r : rows) {
            String key = getField(r, field);
            if (key != null) set.add(key);
        }

        return new ArrayList<>(set);
    }
}