import java.util.LinkedList;

public class Store {
    private Register registers[];
    private int open_idx;

    public Store(int No_registers){
        this.registers[No_registers] = new Register();
        this.registers[0].open();
        this.open_idx = 1;
    }

    public int getAverageQueueLength() {
        int sum = 0;
        for (Register register : this.registers) {
            sum += register.getQueueLength();
        }
        return sum/registers.length;
    }

    public void newCustomer(Customer c) {
        Register shortestqueue = this.registers[0];

        for (Register register : this.registers) {
            if (register.getQueueLength() < shortestqueue.getQueueLength()) {
                shortestqueue = register;
            }
        }

        shortestqueue.addToQueue(c);
    }

    public void step() {
        for (Register register : this.registers) {
            register.step();
        }
    }

    public void openNewRegister(){
        this.registers[this.open_idx++].open();
    }

    public LinkedList<Customer> getDoneCustomers(){
        LinkedList<Customer> list = new LinkedList<Customer>();
        for (Register register : this.registers) {
            try {
                if (register.currentCustomerIsDone()) {
                    list.addLast(register.removeCurrentCustomer());
                }
            } catch (Queue.QueueEmptyException e) {
                e.printStackTrace();
            }
        }
        return list;
    }

}
