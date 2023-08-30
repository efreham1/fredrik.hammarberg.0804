import java.util.LinkedList;

public class Store {
    private Register registers[];
    private int open_idx;

    public Store(int No_registers){
        this.registers = new Register[No_registers];
        for (int i = 0; i < registers.length; i++) {
            registers[i] = new Register();
        }
        this.registers[0].open();
        this.open_idx = 1;
    }

    public int getAverageQueueLength() {
        int sum = 0;
        int len = 0;
        for (Register register : this.registers) {
            if (register.isOpen()){
                sum += register.getQueueLength();
                len++;
            }
        }
        return sum/len;
    }

    public void newCustomer(Customer c) {
        Register shortestqueue = this.registers[0];

        for (Register register : this.registers) {
            if (register.getQueueLength() < shortestqueue.getQueueLength() && register.isOpen()) {
                shortestqueue = register;
            }
        }

        shortestqueue.addToQueue(c);
    }

    public void step() {
        for (Register register : this.registers) {
            if (register.isOpen()){
                register.step();
            }
        }
    }

    public void openNewRegister(){
        if (open_idx < this.registers.length){
            this.registers[this.open_idx++].open();
        }
    }

    public LinkedList<Customer> getDoneCustomers(){
        LinkedList<Customer> list = new LinkedList<Customer>();
        for (Register register : this.registers) {
            try {
                if (register.currentCustomerIsDone()) {
                    list.addLast(register.removeCurrentCustomer());
                }
            } catch (Queue.QueueEmptyException ignore) { }
        }
        return list;
    }

    @Override
    public String toString() {
        String str = "";
        for (Register register : this.registers) {
           str += register.toString() + "\n";
        }
        return str;
    }

    public static void main(String[] args) {
        Store store = new Store(5);
        for (int i = 0; i < 10; i++) {
            Customer c = new Customer(5, 6);
            store.newCustomer(c);
        }
        System.out.println(store.toString());
    }

}
