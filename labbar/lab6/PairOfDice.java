public class PairOfDice {
    private Die die1;
    private Die die2;

    public PairOfDice() {
        this.die1 = new Die();
        this.die2 = new Die();
    }

    public PairOfDice(int numberOfSides) {
        this.die1 = new Die(numberOfSides);
        this.die2 = new Die(numberOfSides);
    }

    public int Roll() {
        this.die1.roll();
        this.die2.roll();
        return this.die1.get() + this.die2.get();
    }

    public int[] get() {
        int[] result = new int[2];
        result[0] = this.die1.get();
        result[1] = this.die2.get();
        return result;
    }

    public String toString() {
        return "Die 1:" + this.die1.get() + " Die 2:" + this.die2.get();
    }

    public static void main(String[] args) {
        PairOfDice pd = new PairOfDice(16);
        System.out.println(pd.toString());
        pd.Roll();
        System.out.println(pd.toString());
        int[] values = new int[2];
        values = pd.get();
        System.out.println(values[0]+values[1]);
    }
}

