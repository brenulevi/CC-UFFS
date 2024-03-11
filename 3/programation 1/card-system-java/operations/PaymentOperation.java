package operations;

import cards.Card;
import user.Client;

public class PaymentOperation extends Operation {
    private double amount;

    public PaymentOperation(Client clientOrigin, double amount, Card clientCard) {
        super("Payment", clientOrigin, OPERATION_TYPE_PAYMENT);

        this.amount = amount;
    }

    // =======================================================================

    public double getAmount() {
        return this.amount;
    }
}
