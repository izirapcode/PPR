package localhost.example;
import java.net.URL;
import java.util.*;
class Client{

	 public static void main(String[] args){
		ExampleService helloService = new ExampleService();
		StringPort hello = helloService.getExamplePort();
        Scanner scanner=new Scanner(System.in);
        String data;
        while (true) {
        System.out.println("Wprowadz dane, wpisz quit aby zakonczyc:");
        data = scanner.nextLine();
        if(data.equals("quit"))
            break;
        hello.stringPass(data);
        }
	}
}
