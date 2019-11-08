import java.util.*;
public class LinkedListDriver {
 public static void main(String[] args) {
	 LinkedList list = new SortedDoublyLinkedList();

	 System.out.println(list);
	 Warrior krogg = new Warrior("Krogg", 30, 50, 200);
	 list.insert(krogg);

	 System.out.println(list);
	 Warrior gurkh = new Warrior("Gurkh", 40, 45, 180);
	 list.insert(gurkh);
	 System.out.println(list);

	 Warrior between = new Warrior("Between", 35, 45, 189); // added to test between function
	 list.insert(between);


	 System.out.println(list);
	 Warrior brynn = new Warrior("Brynn", 45, 40, 190);
	 list.insert(brynn);

	 System.out.println(list);
	 Warrior dolf = new Warrior("Dolf", 20, 65, 210);
	 list.insert(dolf);

	 System.out.println(list);
	 Warrior zuni = new Warrior("Zuni", 50, 35, 170);
	 list.insert(zuni);

	 System.out.println(list);
 	}
}
interface LinkedList {
 void insert(Warrior warrior);
 String toString();
}
class Warrior {
	private String name;
	private int speed;
	private int strength;
	private int hp;


	public Warrior(String name, int speed, int str, int hp) {
		this.name = name;
		this.speed = speed;
		this.strength = str;
		this.hp = hp;
	}

	public String getName() { return this.name; }
	public int getSpeed() { return this.speed; }
	public int getStrength() { return this.strength; }
	public int getHp() { return this.hp; }

	public String toString() { return this.name + "(" +
	this.speed + ")"; }
}
class SortedDoublyLinkedList implements LinkedList{ // Double linked list function implementing the interface
	class Node{ // nested Node class
		private String name; // each node has a name next and prev and speed parameter so I can sort it
		private int speed;
		private Node next;
		private Node prev;
		public Node(String name, int speed){ // initializing a node with the data it has
			this.name = name;
			this.speed = speed;
		}
		public String getElement(){ // get and set methods for nodes
			return this.name;
		}
		public void setNext(Node next){
			this.next = next;
		}
		public void setPrev(Node prev){
			this.prev = prev;
		}
		public Node getPrev(){
			return this.prev;
		}
		public Node getNext(){
			return this.next;
		}
	}

	private static int size; // instances of SortedDoublyLinkedList class
	private Node Head;
	private Node Tail;

	public SortedDoublyLinkedList(){ // SortedDoublyLinkedList constructer
		this.Head = new Node(null,0);
		this.Tail = new Node(null,0);
	}
	public boolean isEmpty(){ // checking if LinkedList is empty
		if(size == 0) {
			return true;
		}
			return false;
	}
	public void Infront(Node temp){ // method to put a node infront of head
		Head.prev = temp;
		temp.next = Head;
		Head = temp;
	}
	public void Between(Node iter , Node middle){ // method to put node between two nodes
		middle.next = iter;
		middle.prev = iter.prev;
		(iter.prev).next = middle;
		iter.prev = middle;


	}
	public void insert(Warrior warrior){ // insert function to insert nodes into list
		SortedDoublyLinkedList.Node temp = new SortedDoublyLinkedList.Node(warrior.getName(), warrior.getSpeed()); // node to add to list
		SortedDoublyLinkedList.Node iter = new SortedDoublyLinkedList.Node(null,0); // node to iterate through list to see where to put node

		if(isEmpty()){
			Head = temp;
			Tail = temp;
			size++;
		}else{
			iter = Head;
			while(iter != null){
				if(temp.speed > Head.speed){
					Infront(temp);
					size++;
				}
				else if(iter.speed < temp.speed && (iter.prev).speed > temp.speed){
				 // System.out.println("hello");
				 // System.out.println(iter.speed);
					Between(iter, temp);
					size++;
				}else	if (temp.speed < Tail.speed){
					// this is inserting at the end
					Tail.next = temp;
					temp.prev = Tail;
					Tail = temp;
					size++;
				}
				iter = iter.next;
			}
		}
	}
	public String toString(){ // String function to output list
		SortedDoublyLinkedList.Node current = Head; // Head
		String total = "";
		if(isEmpty()){
			System.out.print("Empty");
		}else
			while (current != null){ // as long as current(node) is not empty keeps moving through list
				total += current.name + " (" + current.speed + ")";
				current = current.next;
			}
	 	return total;
	}
}
