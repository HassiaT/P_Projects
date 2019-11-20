package allbutmain;

import java.util.logging.Logger;

public class CurrencyExchange {

    private String source;
    private String[] _destinationcurrencies;
    private static Logger logger = Logger.getLogger(CurrencyExchange.class.getName());


    public String getSource() {
        return source;
    }

    public void setSource(String source) {
        this.source = source;
    }

    public String[] get_destinationcurrencies() {
        return _destinationcurrencies;
    }

    public void set_destinationcurrencies(String[] _destinationcurrencies) {
        this._destinationcurrencies = _destinationcurrencies;
    }

    public CurrencyExchange(String _source, String[] _sinks) {
        logger.info("In constructor CurrencyExchange - class CurrencyExchange");
        this.source = _source;
        this._destinationcurrencies = _sinks;
    }

}
