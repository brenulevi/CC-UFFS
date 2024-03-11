package db;

import cards.Card;
import user.Client;

public class ClientsDatabase {
    public Client clientDb[] = new Client[2];

    public ClientsDatabase() {
        Client c1 = new Client("Breno", 12345, 67, 2, 20, 300);
        Client c2 = new Client("Nicolas", 12345, 12, 3, 20, 300);
        c1.addCard(135791113, 112, c1, "MASTERCARD", false, Card.CREDIT_CARD);
        c1.addCard(123456789, 998, c1, "VISA", false, Card.DEBIT_CARD);
        c2.addCard(987654321, 110, c2, "MASTER", false, Card.CREDIT_CARD);
        c2.addCard(587109348, 450, c2, "VISA", false, Card.DEBIT_CARD);
        clientDb[0] = c1;
        clientDb[1] = c2;
    }

    public Client getClient(int agency, int account) throws Exception {
        for(Client c : this.clientDb) {
            if(c.getAccount() == account && c.getAgency() == agency)
                return c;
        }
        throw new Exception("Client not found");
    }
}
