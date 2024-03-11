import javax.swing.JFrame;
import java.awt.Dimension;
import java.awt.Toolkit;

class Main {
    public static void main(String[] args) {
        JFrame frame = new JFrame("Example window");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        // Setting size
        Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
        frame.setSize( (int) screenSize.getWidth(), (int) screenSize.getHeight());
        frame.setVisible(true);
    }
}