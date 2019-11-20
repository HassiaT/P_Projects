package allbutmain;

import java.io.IOException;
import java.util.Date;
import java.util.logging.*;
import java.util.List;
import java.sql.Timestamp;


public class FeedHandler {

    /* TABLE LAST UPDATES */
    private static final String[] COL_NAMES_LU
            = new String[]{"time", "sym", "source", "sink", "rate"};


    /* TABLE RATES */
    private static final String[] COL_NAMES_RATES
            = new String[]{"time", "sym", "rate", "actualtime"};

    private c conn;
    private static Logger logger = Logger.getLogger(FeedHandler.class.getName());

    public c getConn() {
        return conn;
    }

    public void setConn(c conn) {
        this.conn = conn;
    }

    public FeedHandler(String host, int port) {
        logger.info("In constructor FeedHandler - initiliazing feedHandler ");
        try {
            this.conn = new c(host, port);
            System.out.println("PORT :::::::::" + port);


        } catch (Exception e) {
            logger.severe("Exception found. Constructor FeedHandler " + e.getMessage());
        } finally {
            logger.info("In constructor FeedHandler - bloc finally executed");
        }
    }

    public void publish(List<Exchange> exchanges) throws IOException {
        int numRecords = exchanges.size();
        // create the vectors for each column of table myrates
        c.Timespan[] mytimes = new c.Timespan[numRecords];
        Date[] t = new Date[numRecords];
        String[] currencies = new String[numRecords];
        String[] sources = new String[numRecords];
        String[] sinks = new String[numRecords];
        double[] rates = new double[numRecords];
        // loop through filling the columns with data
        for (int i = 0; i < exchanges.size(); i++) {
            Exchange exch = exchanges.get(i);
            String _currency = exch.getSource_exchange() + exch.getSink_exchange();
            sources[i] = exch.getSource_exchange();
            sinks[i] = exch.getSink_exchange();
            currencies[i] = _currency;
            rates[i] = exch.getExchange_rate();
            t[i] = exch.getTime();
            mytimes[i] = new c.Timespan();
        }
        // create the table itself from the separate columns
        Object[] data_1 = new Object[]{currencies, rates, t};
        Object[] data_2 = new Object[]{currencies, sources, sinks, rates};
        try {
            conn.ks(".u.upd", "rates", data_1);
            conn.ks(".u.upd", "lastupdates", data_2);
            System.out.println("Ticker plant has received " + numRecords + " new records");

        } catch (IOException e) {
            logger.severe("Function publish class FeedHandler - Error sending feed to server.");
        } finally {
//            try {
//                //        conn.close();
//            } catch (Exception e) {
//                logger.severe("Function publish class FeedHandler - Error while closing kdb+ connection.");
//            }
        }
    }

    public static void endConnection(FeedHandler hdl) {
        logger.info("In function endConnection - class FeedHandler");
        try {
            hdl.conn.close();
        } catch (Exception e) {
            logger.severe("In function endConnection - Exception raised" + e.getMessage());

        }

    }
}


