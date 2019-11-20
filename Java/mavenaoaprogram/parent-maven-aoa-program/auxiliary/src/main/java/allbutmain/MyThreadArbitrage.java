package allbutmain;

import src.guicomponents.Arbitragepanel;
import src.guicomponents.Historicalpanel;

import java.util.logging.Logger;

public class MyThreadArbitrage extends Thread {
    private static Logger logger = Logger.getLogger(MyThreadArbitrage.class.getName());
    private String _name;
    private MyMojoCurrency mymojo;
    private Arbitragepanel mypanel;


    public MyThreadArbitrage(String name, Arbitragepanel arbtpanel, MyMojoCurrency _mymojo) {
        logger.info("In constructor MyThreadArbitrage - initializing thread name with " + name);
        this._name = name;
        this.mypanel = arbtpanel;
        this.mymojo = _mymojo;
    }

    public void run() {
        logger.info("Starting function run in MyThreadArbitrage");
        if (this.mypanel != null) {
            UserRequest request = new UserRequest();
            String source = mypanel.getTextField1().getText();
            String sinks = mypanel.getTextField2().getText();
            String _buildrequest = source + "," + sinks;
            request.setToSend(_buildrequest);


            CurrencyRequest mycurrencyreq = ArbitrageFunctions.initializeConfiguration(this.mymojo);
           System.out.println(mycurrencyreq);



            ArbitrageFunctions.sendingrequest(mycurrencyreq, request, this.mypanel, this.mymojo);
            logger.info("Ending function run in MyThreadArbitrage");
        }
    }
}