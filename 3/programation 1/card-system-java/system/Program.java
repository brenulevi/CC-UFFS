package system;

import java.util.Scanner;

import db.ClientsDatabase;
import user.Client;

public class Program {
    private Client actualClient;
    private static Scanner sc = new Scanner(System.in);
    private ClientsDatabase db = new ClientsDatabase();

    //#region Array of Methods
    interface Actions {
        void action();
    }

    private Actions[] menuActions = new Actions[] {
        new Actions() { public void action() { DoOperation(); }},
        new Actions() { public void action() { ViewOperations(); }},
        new Actions() { public void action() { ChangeCard(); }},
        new Actions() { public void action() { ViewProfile(); }},
        new Actions() { public void action() { Logout(); }}
    };

    private Actions[] operationActions = new Actions[] {
        new Actions() { public void action() { Payment(); }},
        new Actions() { public void action() { Deposit(); }},
        new Actions() { public void action() { Transfer(); }},
        new Actions() { public void action() { Loot(); }}
    };
    //#endregion    

    public void Start() {
        this.Login();

        this.Menu();
    }

    private void Login() {
        System.out.println("================== LOGIN ==================");
        do {
            System.out.println("Type your agency number: ");
            int agency = sc.nextInt();
            System.out.println("Type your account number: ");
            int account = sc.nextInt();
            try {
                this.actualClient = db.getClient(agency, account);
                break;
            } catch(Exception e) {
                System.out.println("User not found, try again");
            }
        } while(true);
    }

    private void Menu() {
        System.out.println("================== MENU ==================");
        System.out.println("Hello, " + this.actualClient.getName());
        System.out.println("Your selected card is: " + this.actualClient.getActiveCard().getNumber());
        System.out.println("Card type: " + this.actualClient.getActiveCard().getType());
        int answer;
        do {
            System.out.println("1 - Do an operation");
            System.out.println("2 - View my operations");
            System.out.println("3 - Change active card");
            System.out.println("4 - View my profile");
            System.out.println("5 - Logout");
            System.out.print("Type an option: ");
            answer = sc.nextInt();
            if(answer <= 5 && answer >= 1)
                break;

            System.out.println("Invalid option, try again");
        } while(true);

        this.menuActions[answer-1].action();
    }

    private void DoOperation() {
        System.out.println("================== Operations ==================");
        int answer;
        do {
            System.out.println("1 - Payment");
            System.out.println("2 - Deposit");
            System.out.println("3 - Transfer");
            System.out.print((this.actualClient.getActiveCard().getType() == "Debit card") ? "4 - Loot\n" : "");
            System.out.println("Type an operation: ");
            answer = sc.nextInt();
            if(this.actualClient.getActiveCard().getType() == "Credit card") {
                if(answer <= 3 && answer >= 1)
                    break;
            } else if((answer <= 4 && answer >= 1))
                break;

            System.out.println("Invalid option");
        } while(true);
        
        this.operationActions[answer-1].action();
    }

    private void ViewOperations() {
        System.out.println("View operations");
    }

    private void ChangeCard() {
        System.out.println("Change card");
    }

    private void ViewProfile() {
        System.out.println("View profile");
    }

    private void Logout() {
        System.out.println("Logout");
    }

    private void Payment() {
        System.out.println("Payment");
    }

    private void Deposit() {
        System.out.println("Deposit");
    }

    private void Transfer() {
        System.out.println("Transfer");
    }

    private void Loot() {
        System.out.println("Loot");
    }
}
