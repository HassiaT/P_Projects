package allbutmain;
import src.guicomponents.Arbitragepanel;
import javax.swing.*;
import java.util.*;
import java.util.logging.Logger;


public class ArbitrageFunctions {
    private static Logger logger = Logger.getLogger(ArbitrageFunctions.class.getName());


    public static CurrencyRequest initializeConfiguration(MyMojoCurrency mymojo) {
        logger.info("Class ArbitrageFunctions function initializeConfiguration");
        CurrencyRequest currencyrequest = null;
        if (mymojo != null) {
            try {
                currencyrequest = new CurrencyRequest(mymojo);
            } catch (Exception e) {
                logger.severe("Class ArbitrageFunctions function initializeConfiguration - Fatal error --" + e.getMessage());
            }
        }
        return currencyrequest;
    }

    public static <K, V> K getKey(Map<K, V> map, V value) {
        for (K key : map.keySet()) {
            if (value.equals(map.get(key))) {
                return key;
            }
        }
        return null;
    }

    public static Map<String, Integer> gettingIds(String[] currencies) {
        Map<String, Integer> _ids = new HashMap<>();
        logger.info("Starting function gettingIds in class ArbitrageFunctions");
        for (int i = 0; i < currencies.length; i++) {
            _ids.put(currencies[i], i);
        }
        logger.info("Function gettingIds. Ids of all the currencies created. Finished");
        return _ids;
    }

    public static String[] pickupothercurrencies(String[] currencies, int index) {
        logger.info("Starting function pickupothercurrencies. Removing elemnent at index " + index);
        int nb_currencies = currencies.length;
        if (currencies == null || index < 0 || index >= nb_currencies) {
            return currencies;
        }
        String[] _copy = currencies.clone();
        String[] result = new String[nb_currencies - 1];
        System.arraycopy(currencies, 0, result, 0, index);
        System.arraycopy(currencies, index + 1, result, index, nb_currencies - index - 1);
        return result;
    }

    public static List<CurrencyExchange> initializeCurrencyChange(String[] currencies) {
        logger.info("In function initializeCurrencyChange : initialize all the exchanges between given currencies");
        int nb_currencies = currencies.length;
        List<CurrencyExchange> _exchanges = new ArrayList<CurrencyExchange>();
        for (int i = 0; i < nb_currencies; i++) {
            String _s = currencies[i];
            String[] _othercurrencies = pickupothercurrencies(currencies, i);
            CurrencyExchange e = new CurrencyExchange(_s, _othercurrencies);
            _exchanges.add(e);
        }
        logger.info("Ending function initializeCurrencyChange : No error detected");
        return _exchanges;
    }


    public static void sendingrequest(CurrencyRequest req, UserRequest uq, Arbitragepanel panel, MyMojoCurrency mymojo) {
        logger.info("Starting class ArbitrageFunctions function sendingrequest");
        String requete = uq.getToSend();
        List<String> allsupportedcurrencies = req.gettingSupportedCurrencies();
        String[] currencies = requete.split(",");
        int edges = 0;
        int vertices = currencies.length;
        if (currencies.length > 2) {
            List<CurrencyExchange> _allpairscurrencies = initializeCurrencyChange(currencies);
            Set<DWEdge>[] alledges = (Set<DWEdge>[]) new HashSet[vertices]; // for the graph
            Map<String, Integer> currencies_ids = gettingIds(currencies);
            List<Exchange> _exchanges = new ArrayList<>();
            for (CurrencyExchange ce : _allpairscurrencies) {
                _exchanges = req.gettingrequestresponse(ce.getSource(), allsupportedcurrencies);
                for (Exchange e : _exchanges) {
                    try {
                        int source_currency = currencies_ids.get(e.getSource_exchange());
                        int destination_currency = currencies_ids.get(e.getSource_exchange());
                        DWEdge _ed = new DWEdge(source_currency, destination_currency, e.getExchange_rate());
                        alledges[source_currency].add(_ed);
                        edges++;
                    } catch (Exception ex) {
                        logger.severe("In function sendingrequest class ArbitrageFunctions. Exception found " + ex.getMessage());
                    }
                }
            }
            try {
                String serveraddress = mymojo.getProperties().getProperty("SERVER");
                int porttickerplant = Integer.parseInt(mymojo.getProperties().getProperty("TICKERPORT"));
                FeedHandler feedhdl = new FeedHandler(serveraddress, porttickerplant);
                feedhdl.publish(_exchanges);
                String total = "";
                for (Exchange ex : _exchanges)
                    total += ex.toString();
                panel.getTextPane1().setText(total);
                /* LOOKING FOR ARBITRAGE OPPORTUNITY */
//                int totaledges = edges;
//                Graph graph = new Graph(vertices, edges, alledges);
//                BFAlgorithm bfa = new BFAlgorithm(graph, 0);
//                String result = bfa.gettingArbitrageAnswer(currencies_ids);
//                panel.getTextPane1().setText(result);
            } catch (Exception e) {
                logger.severe("In function sendingrequest class ArbitrageFunctions" + e.getMessage());
            }
        } else {
            JOptionPane.showMessageDialog(null, "You have not entered enough currencies to search arbitrage opportunity");
        }
    }

}








