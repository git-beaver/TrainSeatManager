package swu.com.good_diy;

import java.io.Serializable;
import java.util.ArrayList;

public class SeatAdapter implements Serializable {
    public String seatNum;
    public String seatAvailable;

    public SeatAdapter(String seatNum, String seatAvailable) {
        this.seatAvailable = seatAvailable;
        this.seatNum = seatNum;
    }

    public String getSeatNum() {
        return seatNum;
    }

    public void setSeatNum(String seatNum) {
        this.seatNum = seatNum;
    }

    public String getSeatAvailable() {
        return seatAvailable;
    }

    public void setSeatAvailable(String seatAvailable) {
        this.seatAvailable = seatAvailable;
    }
}
