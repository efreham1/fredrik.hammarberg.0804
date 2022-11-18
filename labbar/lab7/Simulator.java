public class Simulator{

    public static void main(String[] args) throws InterruptedException{
        int steps = 100;
        Simulation s = new Simulation(5, 30, 25, 3);
        for(int i = 0; i < steps; i++){
            s.step();
            System.out.println(s.averageWaitTime());
            Thread.sleep(500);
        }
        System.out.println("");
        System.out.println("Simulation finished!");
    }
}