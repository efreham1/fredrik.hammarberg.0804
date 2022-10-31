import java.util.LinkedList;
import java.util.NoSuchElementException;



public class Queue <T>{
    private LinkedList<T> list;

    static class QueueEmptyException extends Exception{
        
        public QueueEmptyException(String msg){
            super(msg);
        }
        
    }

    public Queue(){
        this.list = new LinkedList<T>();
    }

    public T first() throws QueueEmptyException{
        try {
            return this.list.getFirst();
        } catch (NoSuchElementException e){
            throw new QueueEmptyException("The queue is empty");
        }
    }

    public T pop() throws Queue.QueueEmptyException{
        try {
            return this.list.removeFirst();
        } catch (NoSuchElementException e){
            throw new QueueEmptyException("The queue is empty");
        }
    }

    public boolean isEmpty(){
        return this.list.isEmpty();
    }

    public void add(T e){
        this.list.addLast(e);
    }

    public int length(){
        return this.list.size();
    }
}
