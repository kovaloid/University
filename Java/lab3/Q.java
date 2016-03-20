package lab3;

public class Q {
	
	int count;
	long startTime, currentTime;
	
	synchronized void printTime(long startTime, String name){
		this.startTime = startTime;
		currentTime = System.nanoTime();
		System.out.println("ќбщее врем€ выполнени€ " + name + " потока : " + (currentTime-startTime)/1e6 + " миллисекунд");
		
		notifyAll();
		try{
			wait();
		} catch(InterruptedException e){
			System.out.println("InterruptedException перехвачено");
		}
	}
	
	synchronized void printNum(int count, String name){
		this.count = count;
		System.out.println(" оличество выполнений " + name + " потока  : " + count);
		
		notifyAll();
		try{
			wait();
		} catch(InterruptedException e){
			System.out.println("InterruptedException перехвачено");
		}
	}

}
