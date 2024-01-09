package fi.tuni.prog3.jsoncountries;

import com.google.gson.*;
import java.io.FileReader;
import java.util.*;
import java.io.FileWriter;

public class CountryData {
    
    // List<Country> readFromJsons(String areaFile, String populationFile, String gdpFile) 
    // lukee maiden tietoja parametrien nimeämistä JSON-tiedostoista.

    public static List<Country> readFromJsons(String areaFile, String populationFile, String gdpFile) throws Exception {
        Map<String, Country> maaMap = new HashMap<>();

        // Lue area data
        kasitteleTiedosto(areaFile, maaMap, "area");
        // Lue population data
        kasitteleTiedosto(populationFile, maaMap, "population");
        // Lue GDP data
        kasitteleTiedosto(gdpFile, maaMap, "gdp");

        return new ArrayList<>(maaMap.values());
    }

    private static void kasitteleTiedosto(String tiedostonNimi, Map<String, Country> maaMap, String tyyppi) throws Exception {
        
        JsonObject juuri = JsonParser.parseReader(new FileReader(tiedostonNimi)).getAsJsonObject();
        JsonArray tietueet = juuri.getAsJsonObject("Root").getAsJsonObject("data").getAsJsonArray("record");
        
        for (JsonElement tietueElem : tietueet) {
            JsonObject tietue = tietueElem.getAsJsonObject();
            JsonArray kentat = tietue.getAsJsonArray("field");

            String maanNimi = kentat.get(0).getAsJsonObject().get("value").getAsString();
            double arvo = kentat.get(2).getAsJsonObject().get("value").getAsDouble();

            if (!maaMap.containsKey(maanNimi)) {
                maaMap.put(maanNimi, new Country(maanNimi, 0, 0, 0));
            }

            Country maa = maaMap.get(maanNimi);

            switch (tyyppi) {
                case "area":
                    maaMap.put(maanNimi, new Country(maa.getName(), arvo, maa.getPopulation(), maa.getGdp()));
                    break;
                case "population":
                    maaMap.put(maanNimi, new Country(maa.getName(), maa.getArea(), (long) arvo, maa.getGdp()));
                    break;
                case "gdp":
                    maaMap.put(maanNimi, new Country(maa.getName(), maa.getArea(), maa.getPopulation(), arvo));
                    break;
            }
        }
    }

    // void writeToJson(List<Country> countries, String countryFile) kirjoittaa 
    // listan countries sisältämien Country-olioiden kuvaamat tiedot JSON-muodossa parametrin countryFile nimeämään tiedostoon.

    public static void writeToJson(List<Country> countries, String countryFile) throws Exception {
        // Katso tarkka muoto esimerkkitulosteista.
        // Tulostuksen muoto vastaa GSON-kirjaston muotoilua setPrettyPrinting().
        Gson gson = new GsonBuilder().setPrettyPrinting().create();

        // JSON-taulukko, joka sisältää yhden JSON-objektin kutakin maata kohden.
        // Kukin JSON-objekti kuvaa yhden maan tiedot avainten name, area, population ja gdp alla.
    
        JsonArray countryArray = new JsonArray();
        for (Country country : countries) {
            JsonObject countryObj = new JsonObject();
            countryObj.addProperty("name", country.getName());
            countryObj.addProperty("area", country.getArea());
            countryObj.addProperty("population", country.getPopulation());
            countryObj.addProperty("gdp", country.getGdp());
            countryArray.add(countryObj);
        }
    
        // Kirjoita JSON-tiedosto
        try (FileWriter fileWriter = new FileWriter(countryFile)) {
            gson.toJson(countryArray, fileWriter);
        }
    }

}