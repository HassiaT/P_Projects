package src.guicomponents;

import allbutmain.Exchange;
import allbutmain.Javaqinterface;
import allbutmain.MyMojoCurrency;
import allbutmain.MyThreadHistorical;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.FocusEvent;
import java.awt.event.FocusListener;
import java.io.IOException;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.logging.Logger;


public class Historicalpanel extends JPanel implements ActionListener {
    public static Logger logger = Logger.getLogger(Historicalpanel.class.getName());
    private MyMojoCurrency mymojo;
    private JTextField enterACurrencySourceTextField;
    private JTextField enterACurrencySinkTextField;
    private JTextField enterACompleteDateTextField;
    private JButton getRateButton;
    private JTextArea mytextarea;
    private JLabel historicalExchangeRatesLabel;
    private JPanel mypanel;


    public MyMojoCurrency getMymojo() {
        return mymojo;
    }

    public void setMymojo(MyMojoCurrency mymojo) {
        this.mymojo = mymojo;
    }

    public JTextField getEnterACurrencySourceTextField() {
        return enterACurrencySourceTextField;
    }

    public void setEnterACurrencySourceTextField(JTextField enterACurrencySourceTextField) {
        this.enterACurrencySourceTextField = enterACurrencySourceTextField;
    }

    public JTextField getEnterACurrencySinkTextField() {
        return enterACurrencySinkTextField;
    }

    public void setEnterACurrencySinkTextField(JTextField enterACurrencySinkTextField) {
        this.enterACurrencySinkTextField = enterACurrencySinkTextField;
    }

    public JTextField getEnterACompleteDateTextField() {
        return enterACompleteDateTextField;
    }

    public void setEnterACompleteDateTextField(JTextField enterACompleteDateTextField) {
        this.enterACompleteDateTextField = enterACompleteDateTextField;
    }

    public JButton getGetRateButton() {
        return getRateButton;
    }

    public void setGetRateButton(JButton getRateButton) {
        this.getRateButton = getRateButton;
    }

    public JTextArea getMytextarea() {
        return mytextarea;
    }

    public void setMytextarea(JTextArea mytextarea) {
        this.mytextarea = mytextarea;
    }

    public JLabel getHistoricalExchangeRatesLabel() {
        return historicalExchangeRatesLabel;
    }

    public void setHistoricalExchangeRatesLabel(JLabel historicalExchangeRatesLabel) {
        this.historicalExchangeRatesLabel = historicalExchangeRatesLabel;
    }

    public JPanel getMypanel() {
        return mypanel;
    }

    public void setMypanel(JPanel mypanel) {
        this.mypanel = mypanel;
    }


    public Historicalpanel(MyMojoCurrency mymojo) {
        logger.info("In constructor Historicalpanel :");
        this.mymojo = mymojo;
        getRateButton.setBackground(Color.darkGray);
        getRateButton.setForeground(Color.RED);
        getRateButton.addActionListener(this);
        enterACurrencySourceTextField.addFocusListener(new FocusListener() {
            @Override
            public void focusGained(FocusEvent e) {
                if (enterACurrencySourceTextField.getText().equals("Enter a currency source...")) {
                    enterACurrencySourceTextField.setText("");
                    enterACurrencySourceTextField.setForeground(Color.BLACK);
                }
            }

            @Override
            public void focusLost(FocusEvent e) {
                if (enterACurrencySourceTextField.getText().isEmpty()) {
                    enterACurrencySourceTextField.setForeground(Color.GRAY);
                    enterACurrencySourceTextField.setText("Enter a currency source...");
                }
            }
        });

        enterACurrencySinkTextField.addFocusListener(new FocusListener() {
            @Override
            public void focusGained(FocusEvent e) {
                if (enterACurrencySinkTextField.getText().equals("Enter a currency sink...")) {
                    enterACurrencySinkTextField.setText("");
                    enterACurrencySinkTextField.setForeground(Color.BLACK);
                }
            }

            @Override
            public void focusLost(FocusEvent e) {
                if (enterACurrencySinkTextField.getText().isEmpty()) {
                    enterACurrencySinkTextField.setForeground(Color.GRAY);
                    enterACurrencySinkTextField.setText("Enter a currency sink...");
                }
            }
        });

        enterACompleteDateTextField.addFocusListener(new FocusListener() {
            @Override
            public void focusGained(FocusEvent e) {
                if (enterACompleteDateTextField.getText().equals("Choose a past date....")) {
                    enterACompleteDateTextField.setText("");
                    enterACompleteDateTextField.setForeground(Color.BLACK);
                }
            }

            @Override
            public void focusLost(FocusEvent e) {
                if (enterACompleteDateTextField.getText().isEmpty()) {
                    enterACompleteDateTextField.setForeground(Color.GRAY);
                    enterACompleteDateTextField.setText("Choose a past date...");
                }
            }
        });
    }


    @Override
    public void actionPerformed(ActionEvent e) {
        mytextarea.setText("");
        String source = getEnterACurrencySourceTextField().getText();
        String sink = getEnterACurrencySinkTextField().getText();
        String givendate = getEnterACompleteDateTextField().getText();
        Date entereddate = null;
        if (givendate.equals("")) {
            Date yesterday = Javaqinterface.getYesterdayDate();
            SimpleDateFormat DATE_FORMAT = new SimpleDateFormat("yyyy.MM.dd");
            String yesterdayDate = DATE_FORMAT.format(yesterday);
            logger.info("User has not selected any date. Default date is yesterday for HDB " + yesterdayDate);
            getEnterACompleteDateTextField().setText(yesterdayDate); /* choose yesterday date as default date */
        }
        MyThreadHistorical historical = new MyThreadHistorical("HISTORICAL RATES", this, mymojo);
        historical.start();
    }

    private void createUIComponents() {
        // TODO: place custom component creation code here
    }
}
