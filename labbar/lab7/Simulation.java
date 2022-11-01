import java.util.Random;
import java.util.LinkedList;

public class Simulation {
    Store store;
    int time;
    int intensity;
    int maxItems;
    int thresholdForNewRegister;
    int averageWait;
    int totalCustomersServed;
    
    public Simulation(int numberOfRegisters, int intensity, int maxItems, int thresholdForNewRegister) {
        this.store = new Store(numberOfRegisters);
        this.time = 0;
        this.intensity = intensity;
        this.maxItems = maxItems;
        this.thresholdForNewRegister = thresholdForNewRegister;
    }

    public void step(){
        this.store.step();
        this.time++;
        Random random = new Random();
        if (random.nextInt(100)<this.intensity){
            int NoItems = random.nextInt(this.maxItems)+1;
            Customer newCustomer = new Customer(this.time, NoItems);
            this.store.newCustomer(newCustomer);
        }
        if (this.store.getAverageQueueLength() > thresholdForNewRegister) {
            this.store.openNewRegister();
        }
        LinkedList<Customer> doneCustomers = this.store.getDoneCustomers();
        for (Customer customer : doneCustomers) {
            this.averageWait += customer.getAge(this.time);
            this.totalCustomersServed++;
        }
        System.out.print("\033[2J\033[;H");
        System.out.println(this.store.toString());
    }

    public float averageWaitTime(){
        return this.averageWait/this.totalCustomersServed;
    }

    public static void main(String[] args) throws InterruptedException {
        Simulation s = new Simulation(5, 30, 10, 5);
        for (int i = 0; i < 30; i++) {
            s.step();
            System.out.println(i);
            Thread.sleep(500);
        }
        System.out.println(s.averageWaitTime());
    }
}
