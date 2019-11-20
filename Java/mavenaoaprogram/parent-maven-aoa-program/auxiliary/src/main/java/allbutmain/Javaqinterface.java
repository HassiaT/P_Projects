package allbutmain;

import javax.swing.*;
import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;
import java.util.logging.Logger;

public class Javaqinterface {

    public static Logger logger = Logger.getLogger(Javaqinterface.class.getName());

    public static Date getYesterdayDate() {
        Date yesterdayDate = null;
        Calendar c = Calendar.getInstance();
        c.setTime(c.getTime()); // Setting the today date
        c.add(Calendar.DATE, -1); // Decreasing 1 day
        yesterdayDate = c.getTime();
        return yesterdayDate;
    }


    public static double getRate(int port, String hdbpath, String source, String sink, String date) throws IOException {
        double resulttrate = 0.0;
        c conn = null;
        String symbol = source.toUpperCase() + sink.toUpperCase();
        logger.info("Function getRate. This is the date in input " + date);
        String loading = hdbpath + "/" + date + "/" + "rates_hist";
        String firstquery = "myhist: get `:" + loading;
        String times = "alltimes: select last actualtime from myhist where sym =`" + symbol;
        String ratequery = "0!select rate from myhist where sym=`" + symbol + ",actualtime=alltimes[`actualtime][0]";
        try {
            conn = new c("localhost", port);
            System.out.println("PORTTTT:" + port);
            conn.ks(firstquery);
            conn.ks(times);
            c.Flip tableResult = (c.Flip) conn.k(ratequery);
            if (tableResult == null)
                logger.severe("Table returned from kdb+ query is empty NULL");
            String[] columnNames = tableResult.x;
            Object[] columnData = tableResult.y;
            logger.info("class JavaqInterface - Function getRateresult: column name " + columnNames[0]);
            double[] rates = (double[]) columnData[0];
            logger.info("class JavaqInterface - Function getRateresult: Result " + rates[0]);
            resulttrate = rates[0];
        } catch (IOException e) {
            logger.severe("IOException raised : " + e.getMessage());
        } catch (c.KException e) {
            logger.severe("KException raised : " + e.getMessage());
            JOptionPane.showMessageDialog(null, "Issue with this historical database. Perhaps does not exist");
            return 0;
        } finally {
            try {
                conn.close();
            } catch (IOException e) {
                logger.severe("IOException raised while closing KDB connection: " + e.getMessage());
            }
        }
        return resulttrate;
    }
}
