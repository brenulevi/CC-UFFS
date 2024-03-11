package operations;

import cards.Card;
import user.Client;

public class DepositOperation extends Operation {
    private double amount;

    public DepositOperation(Client clientOrigin, double amount, Card clientCard) {
        super("Deposit", clientOrigin, OPERATION_TYPE_DEPOSIT);

        this.amount = amount;
    }

        // =======================================================================

        public double getAmount() {
            return this.amount;
        }
}
