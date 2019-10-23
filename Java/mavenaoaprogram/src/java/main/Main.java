package src.java.main;

import java.io.*;
import java.util.Properties;
import java.util.logging.Logger;

import org.apache.maven.plugin.logging.Log;
import org.apache.maven.model.Model;
import org.apache.maven.model.io.xpp3.MavenXpp3Reader;

import org.codehaus.plexus.util.xml.pull.XmlPullParserException;
import allbutmain.*;

public class Main {
    public static Logger loggermain = Logger.getLogger(Main.class.getName());

    public static void main(String[] args) {
        loggermain.info("Starting main function");
        String configFile = "";
        try {
            MavenXpp3Reader reader = new MavenXpp3Reader();
            String pom_file_path = "pom.xml";
            File pom_file = new File(pom_file_path);
            if (!pom_file.exists())
                throw new FileNotFoundException("Check your path for file pom");
            Model model = reader.read(new FileReader(pom_file_path));
            configFile = model.getProperties().getProperty("configfile");
            System.out.println("CONFIGURATION :" + configFile);

        } catch (Exception e) {
            loggermain.severe("Exception raised :" + e.getMessage());
        }
        MyMojoCurrency myMojoCurrency = new MyMojoCurrency(configFile);
        try{
            myMojoCurrency.execute();
            CurrencyRequest currRea = new CurrencyRequest( myMojoCurrency);
        }
        catch(Exception e)
        {
            loggermain.severe("Fatal error --"+e.getMessage());
        }


    }
}
