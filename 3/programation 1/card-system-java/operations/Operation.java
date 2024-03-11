package operations;

import java.util.Calendar;
import java.util.Date;

import user.Client;

public class Operation {
    private String name;
    private int id;
    private Client client;
    private Date date;

    public final static int OPERATION_TYPE_PAYMENT = 04;
    public final static int OPERATION_TYPE_TRANSFER = 03;
    public final static int OPERATION_TYPE_DEPOSIT = 02;
    public final static int OPERATION_TYPE_LOOT = 01;
    
    public Operation(String name, Client client, int type) {
        this.name = name;
        this.client = client;
        this.date = new Date();
        Calendar c = Calendar.getInstance();
        this.id = Integer.parseInt(
            String.format(
                "%s%s%s", 
                c.get(Calendar.YEAR)%100, 
                Long.toString(date.getTime()).substring(8), 
                String.format("%02d", type)
            )
        );
    }

    // =======================================================================

    public String   getName() { return this.name; }
    public int      getId() { return this.id; }
    public Client   getClient() { return this.client; }
    public Date     getDate() { return this.date; }
}
