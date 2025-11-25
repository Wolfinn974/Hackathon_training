
/**
 * Décrivez votre classe PivotTable ici.
 *
 * @author (votre nom)
 * @version (un numéro de version ou une date)
 */
import java.util.*;

public class PivotTable
{
   public static int[][] build(List<Row> rows, List<String> sports, List<String> styles) 
   {

        int[][] table = new int[sports.size()][styles.size()];

        for (Row r : rows) {
            int si = sports.indexOf(r.sport);
            int st = styles.indexOf(r.style);

            if (si >= 0 && st >= 0)
                table[si][st]++;
        }

        return table;
    }
    
    public static List<String> unique(List<Row> rows, String field) 
    {
        Set<String> set = new HashSet<>();

        for (Row r : rows) {
            switch(field) {
                case "sport" -> set.add(r.sport);
                case "style" -> set.add(r.style);
            }
        }
        return new ArrayList<>(set);
    }
}