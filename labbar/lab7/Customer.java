public class Customer {
    private int borntime;
    private int items;

    static class NegativeItemsException extends RuntimeException {
        
        public NegativeItemsException(String msg){
            super(msg);
        }
        
    }

    public Customer(int borntime, int items){
        this.borntime = borntime;
        this.items = items;
    }

    public void serve(){
        if (items == 0){
            throw new NegativeItemsException("Customer was served when items were zero");
        }
        this.items--;
    }

    public boolean isDone(){
        return this.items<1;
    }

    public int getAge(int current_time){
        return current_time-this.borntime;
    }

    @Override
    public String toString() {
        return "[" + this.items + "]";
    }

    public static void main(String[] args){
        Customer C = new Customer(0, 5);
        int time = 0;
        while (time < 6) {
            System.out.print("Served\n");
            C.serve();
            time++;
        }
        System.out.print("age:" + C.getAge(time) + "\n");
    }
}
