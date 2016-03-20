package lab3;

public class First implements Runnable {
	
	Q q;
	int num;
	Thread t1;
	
	First(Q q, int num){
		this.q = q;
		this.num = num;
		t1 = new Thread(this, "1");
		t1.start();
	}

	@Override
	public void run(){
		int i = 1;
		while(i < num+1){
			q.printNum(i++, t1.getName());
		}
	}

}
