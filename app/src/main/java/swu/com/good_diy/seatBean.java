package swu.com.good_diy;

import java.io.Serializable;

public class seatBean implements Serializable {
    String seatOK;
    String seatName;

    public String getSeatOK() {
        return seatOK;
    }

    public void setSeatOK(String seatOK) {
        this.seatOK = seatOK;
    }

    public String getSeatName() {
        return seatName;
    }

    public void setSeatName(String seatName) {
        this.seatName = seatName;
    }

    public seatBean(String seatOK, String seatName) {
        this.seatOK = seatOK;
        this.seatName = seatName;
    }

    public seatBean() {

    }
}
