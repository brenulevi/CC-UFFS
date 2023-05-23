package operations;

import cards.Card;
import user.Client;

public class TransferOperation extends Operation {
    private double amount;
    private Client destClient;

    public TransferOperation(Client clientOrigin, double amount, Card clientCard, Client destClient) {
        super("Transfer", clientOrigin, OPERATION_TYPE_TRANSFER);

        this.amount = amount;
        this.destClient = destClient;
    }

    // =======================================================================
    public double getAmount() {
        return this.amount;
    }

    public Client getDestinationClient() {
        return this.destClient;
    }
}
