import java.util.Scanner;

public class NameOrder {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("First name: ");
        String name1 = sc.nextLine();
        System.out.print("Second name: ");
        String name2 = sc.nextLine();
        if (name1.compareToIgnoreCase(name2) < 0) {
            System.out.print(name1 + "\n");
            System.out.print(name2 + "\n");
        }
        else {
            System.out.print(name2 + "\n");
            System.out.print(name1 + "\n");
        }
        sc.close();
    }
}
