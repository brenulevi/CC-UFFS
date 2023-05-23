class Order {
    private OrderItem itens[];
    private double totalValue;
    private int lastIndex;

    public Order(OrderItem... orders) {
        this.itens = new OrderItem[10];
        this.totalValue = 0;
        int i = 0;
        for (OrderItem order : orders) {
            this.itens[i] = order;
            this.totalValue += order.getValue();
            i++;
        }
        this.lastIndex = i;
    }

    // Test
    // public int getLastIndex() { return this.lastIndex; }

    public void addItem(OrderItem order) {
        this.itens[lastIndex++] = order;
        this.totalValue += order.getValue();
    }

    public double getTotalValue() { return this.totalValue; }

}

class OrderItem {
    private Product prod;
    private int qtd;

    public OrderItem(Product prod, int qtd)
    {
        this.prod = prod;
        this.qtd = qtd;
    }

    // Getters
    public Product getProduct() { return this.prod; }
    public int getQtd() { return this.qtd; }

    // Setters
    public void setProduct(Product prod) { this.prod = prod; }
    public void setQtd(int qtd) { this.qtd = qtd; }

    public double getValue()
    {
        return this.prod.getValue() * this.qtd;
    }
}

class Product {
    private int code;
    private double value;
    private String description;

    public Product(int code, double value, String descrition)
    {
        this.code = code;
        this.value = value;
        this.description = descrition;
    }

    // Getters
    public int getCode() { return this.code; }
    public double getValue() { return this.value; }
    public String getDescription() { return this.description; }

    // Setters
    public void setCode(int code) { this.code = code; }
    public void setValue(double value) { this.value = value; }
    public void setCode(String description) { this.description = description; }
}

class Main
{
    public static void main(String[] args) {
        Product p1 = new Product(123, 10.23, "Ball");
        Product p2 = new Product(145, 23.99, "Chocolate");

        OrderItem oi1 = new OrderItem(p1, 1);
        OrderItem oi2 = new OrderItem(p1, 2);
        OrderItem oi3 = new OrderItem(p2, 1);
        OrderItem oi4 = new OrderItem(p2, 2);

        Order order = new Order(oi1, oi2, oi3);

        order.addItem(oi4);

        System.out.println(order.getTotalValue());
    }
}