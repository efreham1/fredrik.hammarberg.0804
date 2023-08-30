import java.util.Scanner;

public class Die {
    private int numberOfSides;
    private int value;

    public Die() {
        this.numberOfSides = 6;
    }

    public Die(int numberOfSides) {
        if (numberOfSides <= 0) {
            throw new IllegalArgumentException("Illegal number of sides");
        }
        this.numberOfSides = numberOfSides;
        this.value = 1;
    }

    public int roll() {
        this.value = (int) (Math.random() * numberOfSides) + 1;
        return this.get();
    }

    public int get() {
        return value;
    }

    boolean equals(Die otherdie) {
        return this.numberOfSides == otherdie.numberOfSides;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Number of sides: ");
        int sides = sc.nextInt();
        Die d = new Die(sides);
        System.out.println("Alea iacta est: " + d.roll());
        sc.close();
      
  }
}