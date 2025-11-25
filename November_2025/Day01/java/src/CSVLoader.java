
/**
 * Décrivez votre classe CSVLoader ici.
 *
 * @author (votre nom)
 * @version (un numéro de version ou une date)
 */

import java.util.*;
import java.io.*;

public class CSVLoader
{
    public static List<Row> load(String filename)
    {
        List<Row> rows = new ArrayList<>();
        
        try (BufferedReader br = new BufferedReader(new FileReader(filename)))
        {
           String line = br.readLine();
           
           while ((line = br.readLine()) != null) {
                String[] parts = line.split(",");

                if (parts.length < 6) continue;

                int id = Integer.parseInt(parts[0]);
                String gender = parts[1];
                String sport = parts[2];
                String style = parts[3];
                String color = parts[4];
                double budget = Double.parseDouble(parts[5]);

                rows.add(new Row(id, gender, sport, style, color, budget));
            }

        } catch (Exception e) {
            e.printStackTrace();
        }

        return rows;
    }
}