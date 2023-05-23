package user;

import cards.Card;
import cards.CreditCard;
import cards.DebitCard;
import operations.Operation;

public class Client {
    private String name;              
    private int agency;                  
    private int account;                  
    private Card cards[];                   
    private int cardsIndex;
    private double balance;                     
    private double specialCheck;                
    private Operation operations[];
    private int operationsIndex;
    private int activeCard;

    public Client(String name, int agency, int account, int cardsLimit, int operationsLimit, double specialCheck) {
        this.name = name;
        this.agency = agency;
        this.account = account;
        this.cards = new Card[cardsLimit];
        this.cardsIndex = 0;
        this.balance = 0.0;
        this.specialCheck = specialCheck;
        this.operations = new Operation[operationsLimit];
        this.operationsIndex = 0;
        this.activeCard = 0;
    }

    // =======================================================================

    public String getName() { return this.name; }

    public int getAgency() { return this.agency; }

    public int getAccount() { return this.account; }

    public Card[] listCards() { return this.cards; }

    public Card getActiveCard() { return this.cards[this.activeCard]; }

    public double getBalance() { return this.balance; }

    public double getSpecialCheck() { return this.specialCheck; }

    // =======================================================================

    public void setName(String name) { this.name = name; }

    public void setAgency(int agency) { this.agency = agency; }

    public void setAccount(int account) { this.account = account; }

    public void setSpecialCheck(double amount) { this.specialCheck = (amount < 0) ? -amount : amount; }

    // =======================================================================

    public void addCard(int number, int securityCode, Client owner, String flag, Boolean isBlocked, int type) {
        
        Card card = (type == Card.DEBIT_CARD) ? 
        new DebitCard(number, securityCode, owner, flag, isBlocked) : new CreditCard(number, securityCode, owner, flag, isBlocked, type);
        
        this.cards[cardsIndex++] = card;
    }
    
    // =======================================================================

    public void addOperation(Operation operation) {
        this.operations[operationsIndex++] = operation;
    }

    // =======================================================================

    public void addBalance(double amount) {
        this.balance += amount;
    }

    public void removeBalance(double amount) throws Exception {
        if(this.balance - amount < -this.getSpecialCheck())
            throw new Exception("Insufficient balance");

        this.balance -= amount;
    }
}