package cards;

import user.Client;

public abstract class Card {
    public final static int DEBIT_CARD = 1;
    public final static int CREDIT_CARD = 0;

    private int number;
    private int securityCode;
    private Client owner;
    private String flag;
    private Boolean isBlocked;

    public Card(int number, int securityCode, Client owner, String flag, Boolean isBlocked) {
        this.number = number;
        this.securityCode = securityCode;
        this.owner = owner;
        this.flag = flag;
        this.isBlocked = isBlocked;
    }

    // =======================================================================

    public int getNumber() {
        return this.number;
    }

    public int getSecurityCode() {
        return this.securityCode;
    }

    public Client getOwner() {
        return this.owner;
    }

    public String getFlag() {
        return this.flag;
    }

    public Boolean getBlockStatus() {
        return this.isBlocked;
    }

    public abstract String getType();
    

    // =======================================================================

    public void setNumber(int number) {
        this.number = number;
    }

    public void setSecurityCode(int securityCode) {
        this.securityCode = securityCode;
    }

    public void setOwner(Client owner) {
        this.owner = owner;
    }

    public void setFlag(String flag) {
        this.flag = flag;
    }

    public void setBlockStatus(Boolean blockStatus) {
        this.isBlocked = blockStatus;
    }

    // =======================================================================

    public abstract void pay(double amount) throws Exception;

    public abstract void transfer(double amount, Client dest) throws Exception;

    public abstract void deposit(double amount) throws Exception;

    public void loot(double amount) throws Exception {
        throw new Exception("This type of card can't do this operation");
    }
}