package allbutmain;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.logging.Logger;


public class CurrencyRequest {

    private String BASE_URL;
    private String ENDPOINT;
    private String ACCESS_KEY;


    private static Logger logger = Logger.getLogger(CurrencyRequest.class.getName());


    public String getBASE_URL() {
        return BASE_URL;
    }

    public void setBASE_URL(String BASE_URL) {
        this.BASE_URL = BASE_URL;
    }

    public String getENDPOINT() {
        return ENDPOINT;
    }

    public void setENDPOINT(String ENDPOINT) {
        this.ENDPOINT = ENDPOINT;
    }

    public String getACCESS_KEY() {
        return ACCESS_KEY;
    }

    public void setACCESS_KEY(String ACCESS_KEY) {
        this.ACCESS_KEY = ACCESS_KEY;
    }

    public CurrencyRequest(MyMojoCurrency _mymohocurr) {
        logger.info("In constructor CurrencyRequest -- Initializing API configuration");

        for (Object s : _mymohocurr.getProperties().keySet()) {
            String _s = ((String) s);

            switch (_s) {
                case "BASE_URL":
                    this.BASE_URL = _mymohocurr.getProperties().getProperty(_s);
                    break;
                case "ENDPOINT":
                    this.ENDPOINT = _mymohocurr.getProperties().getProperty(_s);
                    break;
                case "ACCESS_KEY":
                    this.ACCESS_KEY = _mymohocurr.getProperties().getProperty(_s);
                    break;
                default:
                    break;
            }
        }
        logger.info("In constructor CurrencyRequest -- API endpoint is " + this.ENDPOINT);
        logger.info("In constructor CurrencyRequest -- BASE URL endpoint is " + this.BASE_URL);
    }

}
