package lab3;

public class Second implements Runnable {

	Q q;
	Thread t2;
	
	Second(Q q){
		this.q = q;
		t2 = new Thread(this, "2");
		t2.start();
	}

	@Override
	public void run(){
		long t = System.nanoTime();
		while(true){
			q.printTime(t, t2.getName());
		}
	}

}
