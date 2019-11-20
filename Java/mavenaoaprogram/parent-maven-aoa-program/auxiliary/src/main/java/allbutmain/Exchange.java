package allbutmain;


import java.util.Date;
import java.sql.Timestamp;


public class Exchange {

    private String source_exchange;
    private String sink_exchange;
    private double exchange_rate;
    public Date time;


    public Exchange(String _source, String _sink, double _rate, Date _time) {
        this.source_exchange = _source;
        this.sink_exchange = _sink;
        this.exchange_rate = _rate;
        this.time = _time;
    }


    public String getSource_exchange() {
        return source_exchange;
    }

    public void setSource_exchange(String source_exchange) {
        this.source_exchange = source_exchange;
    }

    public String getSink_exchange() {
        return sink_exchange;
    }

    public void setSink_exchange(String sink_exchange) {
        this.sink_exchange = sink_exchange;
    }

    public double getExchange_rate() {
        return exchange_rate;
    }

    public void setExchange_rate(double exchange_rate) {
        this.exchange_rate = exchange_rate;
    }

    public Date getTime() {
        return time;
    }

    public void setTime(Date time) {
        this.time = time;
    }


    @Override
    public String toString() {
        String mystring = "";
        mystring += "1 " + this.getSource_exchange().toUpperCase() + " is worth " + this.getExchange_rate() + this.getSink_exchange().toUpperCase() +"\n";
        return mystring;
    }


}
