import java.util.*;
class Buckets {
 private List<String> zeroBucket;
 private List<String> oneBucket;
 public Buckets() {
    zeroBucket = new ArrayList<>();
    oneBucket = new ArrayList<>();
 }
 public void addZero(String newValue) {
    zeroBucket.add(newValue);
 }
 public void addOne(String newValue) {
    oneBucket.add(newValue);
 }
 public List<String> getAllInOrder() {
    List<String> result = new ArrayList<>();
    for (String val: oneBucket) {
        result.add(val);
    }
    for (String val: zeroBucket) {
      result.add(val);
    }
    return result;
 }
}
public class RadixSort{ //radix sort class declaration
   public static void print(List <String> L){ //print method, prints a list
      System.out.print("[");
      for (int i = 0; i < L.size(); i++) {
         System.out.print(L.get(i) + " ");
      }
      System.out.println("]");
   }
   public static void radixsort(List<String> list){ // method uses radix sort to sort list
      Buckets b = new Buckets(); // four declarations of bucket due to me not finding a better method
      Buckets b2 = new Buckets();
      Buckets b3 = new Buckets();
      Buckets b4 = new Buckets();
      // each for loop is used to check a index of the string (for all for-loops below)
      // and determine if the string should be added to the zero bucket or one buck 
      for(String x : list){ 
         if(x.charAt(3) == '0'){
            b.addZero(x);
         }else{
            b.addOne(x);
         }
      }
      list  = b.getAllInOrder(); // list is now the ordered list that the bucket class made from the getAllInOrder
      print(list); 
      for(String x : list){
         if(x.charAt(2) == '0'){
            b2.addZero(x);
         }else{
            b2.addOne(x);
         }
      }
      list  = b2.getAllInOrder();
      print(list); 
      for(String x : list){
         if(x.charAt(1) == '0'){
            b3.addZero(x);
         }else{
            b3.addOne(x);
         }
      }
      list  = b3.getAllInOrder();
      print(list); 
      for(String x : list){
         if(x.charAt(0) == '0'){
            b4.addZero(x);
         }else{
            b4.addOne(x);
         }
      }
      list  = b4.getAllInOrder();
      print(list); 

   }
   // Driver code taken from the lab assignment sheet
   public static void main(String[] args) {
   String[] origNumbers = {"0011", "1001", "1000", "0111", "0101"};
   List<String> numbers = new ArrayList<>();
   for (String num: origNumbers){
      numbers.add(num);
   }
   int numDigits = 4;
   //print method to see the list at first hand(original)
   print(numbers); 
   //calling radix sort method
   radixsort(numbers);
   }
}