package cards;

import operations.DepositOperation;
import operations.LootOperation;
import operations.PaymentOperation;
import operations.TransferOperation;
import user.Client;

public class DebitCard extends Card {

    public DebitCard(
            int number,
            int securityCode,
            Client owner,
            String flag,
            Boolean isBlocked) {
        super(number, securityCode, owner, flag, isBlocked);
    }

    // =======================================================================

    @Override
    public String getType() { return "Debit card"; }

    // =======================================================================

    @Override
    public void pay(double amount) throws Exception {
        this.getOwner().removeBalance(amount);
        PaymentOperation operation = new PaymentOperation(this.getOwner(), amount, this);
        this.getOwner().addOperation(operation);
    }

    @Override
    public void transfer(double amount, Client dest) throws Exception {
        this.getOwner().removeBalance(amount);
        dest.addBalance(amount);
        TransferOperation operation = new TransferOperation(this.getOwner(), amount, this, dest);
        this.getOwner().addOperation(operation);
        dest.addOperation(operation);
    }

    @Override
    public void deposit(double amount) throws Exception {
        this.getOwner().addBalance(amount);
        DepositOperation operation = new DepositOperation(this.getOwner(), amount, this);
        this.getOwner().addOperation(operation);
    }

    @Override
    public void loot(double amount) throws Exception {
        this.getOwner().removeBalance(amount);
        LootOperation operation = new LootOperation(this.getOwner(), amount, this);
        this.getOwner().addOperation(operation);
    }

    // =======================================================================
}
