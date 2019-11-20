package src.java.main;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.logging.Logger;
import allbutmain.*;
import org.apache.maven.model.Model;
import org.apache.maven.model.io.xpp3.MavenXpp3Reader;
import src.guicomponents.Arbitragepanel;
import src.guicomponents.Historicalpanel;
import javax.swing.*;


public class Main {
    public static Logger loggermain = Logger.getLogger(Main.class.getName());
    static JFrame mymainframe;

    public static void launchingscripts() {
        loggermain.info("Starting function launchingscripts in class Main");
        Process pcr = null;

        try {
            loggermain.info("Loading initialization q scripts within kdb+");
            Runtime run = Runtime.getRuntime();
            pcr = run.exec("cmd.exe /k C:\\Users\\Hassia\\JAVA-exercises\\mavenaoaprogram\\src\\java\\main\\starter.bat");
            Thread.sleep(1000);
            System.out.println("Process pcr  exit value :" + pcr.exitValue());
        } catch (Exception e) {
            loggermain.severe("The batch could not execute properly  " + e.getMessage());
        }
    }

    public static void main(String[] args) throws IOException, c.KException {
        loggermain.info("Starting main function");
        String configFile = "";
        c conn = null;
        MyMojoCurrency myMojoCurrency = null;
        try {
            MavenXpp3Reader reader = new MavenXpp3Reader();
            String pom_file_path = "pom.xml";
            File pom_file = new File(pom_file_path);
            if (!pom_file.exists())
                throw new FileNotFoundException("Check your path for file pom");
            Model model = reader.read(new FileReader(pom_file_path));
            configFile = model.getProperties().getProperty("configfile");
            loggermain.info("Function initializeConfiguration- configuration file is : " + configFile);
        } catch (Exception e) {
            loggermain.severe("Function initializeConfiguration - Exception raised :" + e.getMessage());
        }
        myMojoCurrency = new MyMojoCurrency(configFile);
        try {
            myMojoCurrency.execute();
        } catch (Exception e) {
            loggermain.severe("Function initializeConfiguration - Fatal error --" + e.getMessage());
        }
        launchingscripts();
        Historicalpanel _hist = new Historicalpanel(myMojoCurrency);
        Arbitragepanel _arbitrage = new Arbitragepanel(myMojoCurrency);
        JSplitPane _mainsplit = new JSplitPane(JSplitPane.HORIZONTAL_SPLIT, _hist.getMypanel(), _arbitrage.getPanel1());
        mymainframe = new JFrame("Welcome to AO/EX app!");
        mymainframe.add(_mainsplit);
        mymainframe.setSize(700, 400);
        mymainframe.setVisible(true);
        try {
            String server = myMojoCurrency.getProperties().getProperty("SERVER");
            int porttickerplant = Integer.parseInt(myMojoCurrency.getProperties().getProperty("TICKERPORT"));
            loggermain.info("TICKERPORT IS :" + porttickerplant);

            while (true) {
                conn = new c(server, porttickerplant);
                Object[] response = (Object[]) conn.k(".u.sub[`;`]");
                for (Object tt : response) {
                    Object[] tableData = (Object[]) tt;
                    String computerows = "count " + tableData[0].toString();
                    long answer = (long) (conn.k(computerows));
                    System.out.printf("Table %s currently has %d records \n", tableData[0], answer);
                }
                try {
                    loggermain.info("This thread is going to sleep for 10 seconds");
                    Thread.sleep(10000);
                } catch (Exception f) {
                    loggermain.severe("This thread can't sleep. EXCEPTION RAISED");
                }
            }
        } catch (
                IOException e) {
            loggermain.severe("Main class  IOException RAISED  - message :" + e.getMessage());
        } catch (
                c.KException e) {
            loggermain.severe("Main class c.KException RAISED  - message :" + e.getMessage());
        } catch (
                Exception e) {
            loggermain.severe("Main class GENERAL EXCEPTION RAISED  - message :" + e.getMessage());
        } finally {
            {
                if (conn != null) {
                    try {
                        conn.close();
                    } catch (Exception e) {
                        loggermain.severe("Function main - Exception raised when trying to close q connection");
                    }
                }
            }
        }
    }
}

