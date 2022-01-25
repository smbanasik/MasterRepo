// Name: Spencer Banasik
// NetID: SMB200007

package MyImplementations;

public class MyLinkedListQueue<E> {
  private MyLinkedList<E> list 
    = new MyLinkedList<E>();

  public void enqueue(E e) {
    
	  list.addLast(e);
	  
  }

  public E dequeue() {
	  
    return list.removeFirst();
  }

  public int getSize() {
    return list.size();
  }

  @Override
  public String toString() {
    return "Queue: " + list.toString();
  }
}
