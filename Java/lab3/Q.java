package lab3;

public class Q {
	
	int count;
	long startTime, currentTime;
	
	synchronized void printTime(long startTime, String name){
		this.startTime = startTime;
		currentTime = System.nanoTime();
		System.out.println("����� ����� ���������� " + name + " ������ : " + (currentTime-startTime)/1e6 + " �����������");
		
		notifyAll();
		try{
			wait();
		} catch(InterruptedException e){
			System.out.println("InterruptedException �����������");
		}
	}
	
	synchronized void printNum(int count, String name){
		this.count = count;
		System.out.println("���������� ���������� " + name + " ������  : " + count);
		
		notifyAll();
		try{
			wait();
		} catch(InterruptedException e){
			System.out.println("InterruptedException �����������");
		}
	}

}
