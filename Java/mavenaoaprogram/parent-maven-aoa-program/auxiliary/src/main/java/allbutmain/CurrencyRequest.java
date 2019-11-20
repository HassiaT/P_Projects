package allbutmain;
import org.apache.http.HttpEntity;
import org.apache.http.HttpResponse;
import org.apache.http.impl.client.CloseableHttpClient;
import org.apache.http.client.methods.CloseableHttpResponse;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.util.EntityUtils;
import org.apache.http.impl.client.HttpClients;
import org.json.JSONArray;
import org.json.JSONObject;

import javax.swing.*;
import java.sql.Timestamp;
import java.util.Iterator;
import java.util.ArrayList;
import java.util.List;
import java.util.logging.Logger;


public class CurrencyRequest {

    private String BASE_URL;
    private String ENDPOINT;
    private String ACCESS_KEY;
    private String BASE_URL_LIST;
    private static Logger logger = Logger.getLogger(CurrencyRequest.class.getName());


    public String getBASE_URL_LIST() {
        return BASE_URL_LIST;
    }

    public void setBASE_URL_LIST(String BASE_URL_LIST) {
        this.BASE_URL_LIST = BASE_URL_LIST;
    }

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
                case "BASE_URL_LIST":
                    this.BASE_URL_LIST = _mymohocurr.getProperties().getProperty(_s);
                    break;
                default:
                    break;
            }
        }
        logger.info("In constructor CurrencyRequest -- API endpoint is " + this.ENDPOINT);
        logger.info("In constructor CurrencyRequest -- BASE URL endpoint is " + this.BASE_URL);
    }

    @Override
    public String toString() {
        String currencyrequestrpr = "this.BASE_URL is: " + this.getBASE_URL() + "; this.ENDPOINT: " + this.ENDPOINT + "; this.ACCESS_KEY :" + this.getACCESS_KEY() + "\n";
        return currencyrequestrpr;
    }

    public List<String> gettingSupportedCurrencies() {
        logger.info("In function  gettingSupportedCurrencies. Getting all the supported currencies ");
        List<String> allcurrencies = new ArrayList<String>();
        String parameters_separator = "&";
        String before_parameters_separator = "?";
        try {
            CloseableHttpClient httpClient = HttpClients.createDefault();
            String request_currencies = this.getBASE_URL_LIST() + before_parameters_separator + "access_key=" + this.getACCESS_KEY();
            logger.info("Class CurrencyRequest- functiongettingSupportedCurrencies request to send :" + request_currencies);
            HttpGet get = new HttpGet(request_currencies);
            CloseableHttpResponse response = httpClient.execute(get);
            HttpEntity entity = response.getEntity();
            JSONObject exchangeRates = new JSONObject(EntityUtils.toString(entity));
            JSONObject json_currencies = exchangeRates.getJSONObject("currencies");
            System.out.println(json_currencies);
            json_currencies.keySet().forEach(key -> allcurrencies.add(key));
        } catch (Exception e) {
            String error = String.format("Exception found function gettingSupportedCurrencies: %s \n", e.getMessage());
            logger.severe(error);
        }
        return allcurrencies;
    }

    /* source is the currency source against which we query the exchange rates */
    public String buildingrequestfromsource(String source, List<String> allCurrencies) {
        logger.info("Starting function  buildingrequestfromsource. Getting rates for all the supported currencies ");
        String parameters_separator = "&";
        String before_parameters_separator = "?";
        String request_rates = "";
        if (allCurrencies.contains(source)) {
            request_rates = this.getBASE_URL() + this.getENDPOINT() + before_parameters_separator + "access_key=" + this.getACCESS_KEY()
                    + parameters_separator + "source=" + source;
        } else {
            String error = String.format("Error found - buildingrequestfromsource: The source currency %s is not supported\n", source);
            logger.severe(error);
        }
        String info = String.format("In function buildingrequestfromsource. Final HTTP request is : %s \n", request_rates);
        logger.info(info);
        return request_rates;
    }


    /* source is the currency source against which we query the exchange rate */
    public String buildingrequestfromsourcesink(List<String> allCurrencies, String source, String[] sinks) {
        logger.info("Starting function  buildingrequestfromsourcesink. Getting rates for all specific currencies");
        String parameters_separator = "&";
        String before_parameters_separator = "?";
        String request_rates = "";
        List<Boolean> isSupported = new ArrayList<Boolean>();
        isSupported.add(allCurrencies.contains(source));
        for (int i = 0; i < sinks.length; i++) {
            String current_sink = sinks[i];
            isSupported.add(allCurrencies.contains(current_sink));
        }
        if (!isSupported.contains(Boolean.FALSE)) {
            request_rates = this.getBASE_URL() + this.getENDPOINT() + before_parameters_separator + "access_key=" + this.getACCESS_KEY()
                    + parameters_separator + "source=" + source;
            request_rates += parameters_separator + "currencies=";
            for (int i = 0; i < sinks.length; i++) {
                String current_sink = sinks[i];
                request_rates += current_sink;
                if (i != sinks.length - 1) request_rates += ",";
            }
            String info = String.format("In function buildingrequestfromsourcesink. Final HTTP request is : %s \n", request_rates);

            logger.info(info);
        } else {
            logger.severe("Error found - buildingrequestfromsourcesink: At least one currency is not supported by the API!");
        }
        return request_rates;
    }

    public List<Exchange> gettingrequestresponse(List<String> allCurrencies, String source, String[] sinks) {
        logger.info("Starting function gettingrequestresponse with source and sinks as a parameter.");
        System.out.println(this);
        String httprequest = this.buildingrequestfromsourcesink(allCurrencies, source, sinks);
        List<Exchange> responses = new ArrayList<>();
        try {
            CloseableHttpClient httpClient = HttpClients.createDefault();
            HttpGet get = new HttpGet(httprequest);
            CloseableHttpResponse response = httpClient.execute(get);
            HttpEntity entity = response.getEntity();
            JSONObject rates = new JSONObject(EntityUtils.toString(entity));
            Timestamp timeStampDate = new Timestamp((long) (rates.getLong("timestamp") * 1000));
            for (int i = 0; i < sinks.length; i++) {
                String current_sink = sinks[i];
                String key = source + current_sink;
                fillinrates(key, responses, rates);
            }
        } catch (Exception e) {
            String error = String.format("Exception found - gettingrequestresponse only with source and sinks : %s \n", e.getMessage());
            logger.severe(error);
        }
        logger.info("Ending function  gettingrequestresponse with source and sinks. No error detected");
        return responses;
    }

    public static void fillinrates(String key, List<Exchange> responses, JSONObject rates) {
        logger.info("Running function fillinrates");
        String source_c = key.substring(0, 3);
        String sink_c = key.substring(3);
        JSONObject quotes = rates.getJSONObject("quotes");
        double rate = quotes.getDouble(key);
        Timestamp timeStampDate = new Timestamp((long) (rates.getLong("timestamp") * 1000));
        Exchange e = new Exchange(source_c, sink_c, rate, timeStampDate);
        responses.add(e);
    }

    public List<Exchange> gettingrequestresponse(String source, List<String> allCurrencies) {
        logger.info("Starting function gettingrequestresponse only with source as a parameter.");
        String httprequest = buildingrequestfromsource(source, allCurrencies);
        List<Exchange> responses = new ArrayList<>();
        try {
            CloseableHttpClient httpClient = HttpClients.createDefault();
            HttpGet get = new HttpGet(httprequest);
            CloseableHttpResponse response = httpClient.execute(get);
            HttpEntity entity = response.getEntity();
            //JSONArray _keys = rates.getJSONArray("quotes");
            JSONObject rates = new JSONObject(EntityUtils.toString(entity));
            //System.out.println("RATES :"+rates);

            JSONObject quotes = (JSONObject) rates.getJSONObject("quotes");
            System.out.println("JSONOBJECT quotes :" + quotes);
            //  quotes.keySet().forEach(key -> fillinrates(key, responses, rates));
            System.out.println("SIZE OF RESPONSES " + responses.size());
        } catch (Exception e) {
            String error = String.format("Exception found - gettingrequestresponse only with source: %s\n", e.getMessage());
            logger.severe(error);
            JOptionPane.showMessageDialog(null, error);
        }
        logger.info("Ending function  gettingrequestresponse only with source. No error detected");
        return responses;
    }
}
