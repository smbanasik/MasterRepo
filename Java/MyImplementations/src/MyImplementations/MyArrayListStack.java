// Name: Spencer Banasik
// NetID: SMB200007

package MyImplementations;

public class MyArrayListStack<T> implements MyStack<T> {
  private MyArrayList<T> list = new MyArrayList<T>();

  public T pop() {
	  
	 T newList = list.get(size() - 1);
	 
	 list.remove(size() - 1);
	  
    return newList;
  }

  public void push(T element) {
    
	list.add(element);
  }

  public int size() {
	  
    return list.size();
  }
}