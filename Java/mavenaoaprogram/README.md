**AO\EX App - Historical exchange rates and arbitrage opportunity Java application**\

**1. Main functionalities**\
  AO\EX is a multithreaded trading Java application for fetching historical and real-time exchange rates and searching real-time arbitrage   opportunities among currencies. The search for arbitrage opportunities in a user-determined currency exchange table is implemented with   the Bellman-Ford algorithm.

**2. Technologies**\
    1.IntelliJ/ Maven
    2.Kdb+/Q (modified tickerplant) for historical data and processing real-time conversion rates
    3.Java Swing for GUI
    4.Currency Layer API

**3. How to use AO\EX**\
    1.Button Get rate - For **Historical rates** : The user enters a source currency and a sink currency(currency to which 1 unit of the       currency source will be converted) on a selected date. If input date is missing, the program automatically selects yesterday's date by     default and send a query to the historical database created on the input date ( or yesterday's date) to get the last rate between the     two currencies.\
    \
    2.Button Get Arbitrage - For **arbitrage opportunity**: The user enters a source currency and a basket of sink currencies. The               program fetches the necessary rates in the real-time KDB+ database, builds a currency exchange table among the selected currencies         and searches any possible arbitrage opportunity among the currencies. If one is found, the user is alerted with the detailed               strategy. Otherwise, the message "No arbitrage opportunity" is displayed.

**4. AO\EX GUI:**\
Below is a screenshot of the GUI:\
![alt text](https://github.com/HassiaT/P_Projects/blob/local-experiments/AuxiliaryFiles/APPGUI.PNG)
