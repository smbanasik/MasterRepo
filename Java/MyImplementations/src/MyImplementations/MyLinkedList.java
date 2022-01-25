// Name: Spencer Banasik
// NetID: SMB200007

package MyImplementations;

public class MyLinkedList<E> implements MyList<E> {
  private Node<E> head, tail;
  private int size = 0; // Number of elements in the list
  
  /** Create an empty list */
  public MyLinkedList() {
  }

  /** Create a list from an array of objects */
  public MyLinkedList(E[] objects) {
	  
	  for(int i = 0; i < objects.length; i++) {
		  
		  add(objects[i]);
		  
	  }
  }

  /** Return the head element in the list */
  public E getFirst() {
    
    return head.element;
  }

  /** Return the last element in the list */
  public E getLast() {
    
    return tail.element;
  }

  /** Add an element to the beginning of the list */
  public void addFirst(E e) {
	  
	Node<E> newNode = new Node<>(e);
	
	newNode.next = head;
	
	head = newNode;
	
	size++;
	
	if (tail == null) {
		tail = head;
	}
	
  }

  /** Add an element to the end of the list */
  public void addLast(E e) {
	  
	  Node<E> newNode = new Node<>(e);
	  
	  if(tail == null) {
		
		  head = tail = newNode;
		  
	  } else {
		  
		  tail.next = newNode;
		  
		  tail = newNode;
		  
	  }
	  
	  size++;
	  
  }

  @Override /** Add a new element at the specified index 
   * in this list. The index of the head element is 0 */
  public void add(int index, E e) {
    
	  if(index == 0) {
		
		  addFirst(e);
		  
	  } else if (index >= size) {
		  
		  addLast(e);
		  
	  } else {
		  
		  Node<E> current = head;
		  
		  for(int i = 1; i < index; i++) {
			  
			  current = current.next;
			  Node<E> temp = current.next;
			  current.next = new Node<>(e);
			  (current.next).next = temp;
			  size++;
			  
		  }
		  
	  }
	  
  }

  /** Remove the head node and
   *  return the object that is contained in the removed node. */
  public E removeFirst() {
	  
	  if (size == 0) {
		  
		  return null;
		  
	  } else {
		  
		Node<E> temp = head;
		
		head = head.next;
		
		size--;
		
		if(head == null) {
			
			tail = null;
		
		}
		
		return temp.element;
	  }
  }

  /** Remove the last node and
   * return the object that is contained in the removed node. */
  public E removeLast() {
      
	  if(size == 0) {
		  
		  return null;
		  
	  } else if (size == 1) {
		  
		  Node<E> temp = head;
		  
		  head = tail = null;
		  
		  size = 0;
		  
		  return temp.element;
	  } else {
		  
		  Node<E> current = head;
		  
		  for (int i = 0; i < size - 2; i++) {
			  
			  current = current.next;
			  
		  }
		  
		  Node<E> temp = tail;
		  
		  tail = current;
		  
		  tail.next = null;
		  
		  size--;
		  
		  return temp.element;
	  }
	  
  }

  @Override /** Remove the element at the specified position in this 
   *  list. Return the element that was removed from the list. */
  public E remove(int index) {   
      
	  if (index < 0 || index >= size) {
		  
		  return null;
		  
	  } else if (index == 0) {
		  
		  return removeFirst();
		  
	  } else if (index == size - 1) {
		  
		  return removeLast();
		  
	  } else {
		  
		  Node<E> previous = head;
		  
		  for (int i = 1; i < index; i++) {
			  
			  previous = previous.next;
			  
		  }
		  
		  Node<E> current = previous.next;
		  
		  previous.next = current.next;
		  
		  size--;
		  
		  return current.element;
	  }
	  
  }

  @Override /** Override toString() to return elements in the list */
  public String toString() {
    StringBuilder result = new StringBuilder("[");

    Node<E> current = head;
    for (int i = 0; i < size; i++) {
      result.append(current.element);
      current = current.next;
      if (current != null) {
        result.append(", "); // Separate two elements with a comma
      }
      else {
        result.append("]"); // Insert the closing ] in the string
      }
    }

    return result.toString();
  }

  @Override /** Clear the list */
  public void clear() {
    size = 0;
    head = tail = null;
  }

  @Override /** Return true if this list contains the element e */
  public boolean contains(Object e) {
    // Left as an exercise
    // TODO : Implement this method
	  
	  Node<E> current = head;
	  
	  for (int i = 0; i < size; i++) {
		  
		  if(current.element.equals(e)) return true;
		  
		  current = current.next;
		  
	  }
	  
    return false;
  }

  @Override /** Return the element at the specified index */
  public E get(int index) {
    // Left as an exercise
      
	  if (index < 0 || index > size) return null;
	  
	  if (index == 0) {
		  
		  getFirst();
		  
	  } else if (index == size - 1) {
		  
		  getLast();
		  
	  } else {
		  
		  Node<E> current = head;
		  
		  for (int i = 0; i < index; i++) {
			  
			  current = current.next;
			  
		  }
		  
		  return current.element;
	  }
	  
	  return null;
  }

  @Override /** Return the index of the head matching element in 
   *  this list. Return -1 if no match. */
  public int indexOf(Object e) {
    // Left as an exercise
	  
	Node<E> current = head;
	  
	for (int i = 0; i < size; i++) {
		  
		if(current.element.equals(e)) return i;
		  
	 	current = current.next;
		  
	}
	  
    return -1;
  }

  @Override /** Return the index of the last matching element in 
   *  this list. Return -1 if no match. */
  public int lastIndexOf(E e) {
    // Left as an exercise
	  
		Node<E> current = head;
		Node<E> temp = head;
		
		for (int i = size - 1; i >= 0; i--) {
			  
			if(current.element.equals(e)) temp = current;
			  
		 	current = current.next;
			  
		}
		
		current = head;
		
		for (int i = 0; i < size; i++) {
			  
			if(current.element.equals(temp)) return i;
			  
		 	current = current.next;
			  
		}
		  
	    return -1;
  }

  @Override /** Replace the element at the specified position 
   *  in this list with the specified element. */
  public E set(int index, E e) {
    // Left as an exercise
	  if (index < 0 || index > size) return null;
	  
	  if (index == 0) {
		  
		  addFirst(e);
		  
	  } else if (index == size - 1) {
		  
		  addLast(e);
		  
	  } else {
		  
		  Node<E> current = head;
		  
		  for (int i = 0; i < index; i++) {
			  
			  current = current.next;
			  
		  }
		  
		  return current.element = e;
	  }
    return null;
  }

  @Override /** Override iterator() defined in Iterable */
  public java.util.Iterator<E> iterator() {
    return new LinkedListIterator();
  }
  
  private class LinkedListIterator 
      implements java.util.Iterator<E> {
    private Node<E> current = head; // Current index 
    
    @Override
    public boolean hasNext() {
      return (current != null);
    }

    @Override
    public E next() {
      E e = current.element;
      current = current.next;
      return e;
    }

    @Override
    public void remove() {
      // Left as an exercise
      
      MyLinkedList.this.remove(current);
      
    }
  }
  
  private static class Node<E> {
    E element;
    Node<E> next;

    public Node(E element) {
      this.element = element;
    }
  }
  
  @Override /** Return the number of elements in this list */
  public int size() {
    return size;
  }
}

