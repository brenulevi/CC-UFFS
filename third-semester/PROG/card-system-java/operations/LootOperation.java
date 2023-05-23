package operations;

import cards.Card;
import user.Client;

public class LootOperation extends Operation {
    private double amount;

    public LootOperation(Client clientOrigin, double amount, Card clientCard) {
        super("Loot", clientOrigin, OPERATION_TYPE_LOOT);

        this.amount = amount;
    }

    // =======================================================================

    public double getAmount() {
        return this.amount;
    }
}
