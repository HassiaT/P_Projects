package src.guicomponents;

import allbutmain.Javaqinterface;
import allbutmain.MyMojoCurrency;
import allbutmain.MyThreadArbitrage;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.logging.Logger;

public class Arbitragepanel extends JPanel implements ActionListener {
    private JPanel panel1;
    private JTextField textField1;
    private JTextField textField2;
    private JButton getArbitrageButton;
    private JLabel arbitrageOpportunityLabel;
    private JTextPane textPane1;

    public MyMojoCurrency getMymojo() {
        return mymojo;
    }

    public void setMymojo(MyMojoCurrency mymojo) {
        this.mymojo = mymojo;
    }

    private MyMojoCurrency mymojo;
    public static Logger logger = Logger.getLogger(Arbitragepanel.class.getName());

    public JPanel getPanel1() {
        return panel1;
    }

    public void setPanel1(JPanel panel1) {
        this.panel1 = panel1;
    }

    public JTextField getTextField1() {
        return textField1;
    }

    public void setTextField1(JTextField textField1) {
        this.textField1 = textField1;
    }

    public JTextField getTextField2() {
        return textField2;
    }

    public void setTextField2(JTextField textField2) {
        this.textField2 = textField2;
    }

    public JButton getGetArbitrageButton() {
        return getArbitrageButton;
    }

    public void setGetArbitrageButton(JButton getArbitrageButton) {
        this.getArbitrageButton = getArbitrageButton;
    }

    public JLabel getArbitrageOpportunityLabel() {
        return arbitrageOpportunityLabel;
    }

    public void setArbitrageOpportunityLabel(JLabel arbitrageOpportunityLabel) {
        this.arbitrageOpportunityLabel = arbitrageOpportunityLabel;
    }

    public JTextPane getTextPane1() {
        return textPane1;
    }

    public void setTextPane1(JTextPane textPane1) {
        this.textPane1 = textPane1;
    }

    private void createUIComponents() {
        // TODO: place custom component creation code here
    }

    public Arbitragepanel(MyMojoCurrency mymojo) {
        logger.info("Starting constructor of class Arbitragepanel");
        this.mymojo = mymojo;
        getArbitrageButton.setBackground(Color.darkGray);
        getArbitrageButton.setForeground(Color.RED);
        getArbitrageButton.addActionListener(this);
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        String source = this.getTextField1().getText();
        String sinks = this.getTextField2().getText();
        if (source.equals("") || sinks.equals("")) {
            JOptionPane.showMessageDialog(null, "Missing source or sinks input");
        } else {
            MyThreadArbitrage arbitrage = new MyThreadArbitrage("ARBITRAGE OPPORTUNITY", this, mymojo);
            arbitrage.start();
        }
    }
}
