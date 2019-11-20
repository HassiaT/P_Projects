package allbutmain;

import java.util.logging.*;

public class UserRequest {

    private static Logger logger = Logger.getLogger(UserRequest.class.getName());
    private String toSend;
    private Boolean _toSend;
    private String responsetodisplay;
    private Boolean _toDisplay;


    public UserRequest() {
        logger.info("In constructor UserRequest. Initializing all attributes to either empty string or FALSE");
        this._toSend = false;
        this._toDisplay = false;
        this.toSend = "";
        this.responsetodisplay = "";
    }

    public String getToSend() {
        return toSend;
    }

    public void setToSend(String toSend) {
        this.toSend = toSend;
    }

    public Boolean get_toSend() {
        return _toSend;
    }

    public void set_toSend(Boolean _toSend) {
        this._toSend = _toSend;
    }

    public String getResponsetodisplay() {
        return responsetodisplay;
    }

    public void setResponsetodisplay(String responsetodisplay) {
        this.responsetodisplay = responsetodisplay;
    }

    public Boolean get_toDisplay() {
        return _toDisplay;
    }

    public void set_toDisplay(Boolean _toDisplay) {
        this._toDisplay = _toDisplay;
    }

}
