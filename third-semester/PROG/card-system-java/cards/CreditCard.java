package cards;

import operations.DepositOperation;
import operations.PaymentOperation;
import operations.TransferOperation;
import user.Client;

public class CreditCard extends Card {
    private double limit;
    private double bill;

    public CreditCard(
            int number,
            int securityCode,
            Client owner,
            String flag,
            Boolean isBlocked,
            double limit) {
        super(number, securityCode, owner, flag, isBlocked);

        this.limit = limit;
        this.bill = 0;
    }

    // =======================================================================

    public double getLimit() { return this.limit; }
    public double getBill() { return this.bill; }
    
    @Override
    public String getType() { return "Credit card"; }

    // =======================================================================

    public void setLimit(double limit) { this.limit = limit; }

    // =======================================================================

    @Override
    public void pay(double amount) throws Exception {
        if(this.bill + amount > limit)
            throw new Exception("You can't have a bill greater than limit");

        this.bill += amount;
        PaymentOperation operation = new PaymentOperation(this.getOwner(), amount, this);
        this.getOwner().addOperation(operation);
    }

    @Override
    public void transfer(double amount, Client dest) throws Exception {
        if(this.bill + amount > limit)
            throw new Exception("You can't have a bill greater than limit");

        this.bill += amount;
        dest.addBalance(amount);
        TransferOperation operation = new TransferOperation(this.getOwner(), amount, this, dest);
        this.getOwner().addOperation(operation);
        dest.addOperation(operation);
    }

    @Override
    public void deposit(double amount) throws Exception {
        if(amount > bill)
            amount = bill;
        if(amount == 0)
            throw new Exception("Your bill is payed");

        bill -= amount;

        DepositOperation operation = new DepositOperation(this.getOwner(), amount, this);
        this.getOwner().addOperation(operation);
    }
    // =======================================================================
}
