public class Register {
    private boolean open;
    private Queue<Customer> queue;

    public Register(){
        this.open = false;
        this.queue = new Queue<Customer>();
    }

    public void open(){
        this.open = true;
    }

    public void close(){
        this.open = false;
    }

    public boolean isOpen(){
        return this.open;
    }

    public void step(){
        try {
            this.queue.first().serve();
        } catch (Queue.QueueEmptyException e) {
            return;
        }
    }

    public boolean hasCustomers(){
        return !this.queue.isEmpty();
    }

    public boolean currentCustomerIsDone() throws Queue.QueueEmptyException{
        return this.queue.first().isDone();
    }

    public void addToQueue(Customer c){
        this.queue.add(c);
    }

    public Customer removeCurrentCustomer() throws Queue.QueueEmptyException{
        return this.queue.pop();
    }

    public int getQueueLength(){
        return this.queue.length();
    }
}
