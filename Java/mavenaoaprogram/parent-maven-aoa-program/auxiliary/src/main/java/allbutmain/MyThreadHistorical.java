package allbutmain;


import src.guicomponents.Historicalpanel;

import javax.swing.*;
import java.awt.*;
import java.io.IOException;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.logging.Logger;

public class MyThreadHistorical extends Thread {
    private static Logger logger = Logger.getLogger(MyThreadHistorical.class.getName());
    private String _name;
    private MyMojoCurrency mymojo;
    private Historicalpanel histpanel;


    public MyThreadHistorical(String name, Historicalpanel _histpanel, MyMojoCurrency _mymojo) {
        logger.info("In constructor MyThreadHistorical - initializing thread name with " + name);
        this._name = name;
        this.histpanel = _histpanel;
        this.mymojo = _mymojo;
    }

    public void run() {
        logger.info("Starting function run in MyThreadHistorical");
        double rate = 0.0;
        if (this.histpanel != null) {
            String source = this.histpanel.getEnterACurrencySourceTextField().getText();
            String sink = this.histpanel.getEnterACurrencySinkTextField().getText();
            String entereddate = this.histpanel.getEnterACompleteDateTextField().getText();
            if (source.equals("") || sink.equals(""))
                JOptionPane.showMessageDialog(null, "Please enter currencies");
            else {
                String histpathDB = mymojo.getProperties().getProperty("HISTDB");
                int portHDB = Integer.parseInt(mymojo.getProperties().getProperty("HDBPORT"));
                try {
                    rate = Javaqinterface.getRate(portHDB, histpathDB, source, sink, entereddate);
                } catch (IOException ex) {
                    logger.severe("class MyThreadHistorical IOException ex" + ex.getMessage());
                }
                if (rate != 0.0) {
                    String queryanswer = "1" + source.toUpperCase() + " is worth " + rate + sink.toUpperCase() + " on " + entereddate + "\n";
                    this.histpanel.getMytextarea().setText(queryanswer);
                }
            }
        }
        logger.info("Ending function run in MyThreadHistorical");
    }
}

