package lab5;

import javax.swing.JOptionPane;

public class Lab3 {

	public static void main(String[] args) {
		if (args[0].isEmpty())
		{
			JOptionPane.showMessageDialog(Lab5.frame,"Вы ничего не ввели!","Ошибка аргумента",JOptionPane.ERROR_MESSAGE);
		}
		int num = 0;
		try {
			num = Integer.parseInt(args[0]);
			if(num < 0){
				num = 50;
				JOptionPane.showMessageDialog(null, "Вы ввели число < 0! Теперь n = " + num);
				myFrame.text_31.setText("50");
			}
		} catch (NumberFormatException e) {
			num = 50;
			JOptionPane.showMessageDialog(null, "Ошибка ввода! Теперь n = " + num);
			myFrame.text_31.setText("50");
		}
		Q q = new Q();
		new First(q,num);
		new Second(q);
	}	

	public static class Q {
		int count;
		long startTime, currentTime;
		synchronized void printTime(long startTime, String name){
			this.startTime = startTime;
			currentTime = System.nanoTime();
			myFrame.outputTextArea3_1.append(" Общее время выполнения " + name + " потока : " + (currentTime-startTime)/1e6 + " миллисекунд\n");
			notifyAll();
			try{
				wait();
			} catch(InterruptedException e){}
		}
		synchronized void printNum(int count, String name){
			this.count = count;
			myFrame.outputTextArea3_1.append(" Количество выполнений " + name + " потока  : " + count + "\n");
			
			notifyAll();
			try{
				wait();
			} catch(InterruptedException e){}
		}
	}
	
	public static class First implements Runnable {
		Q q;
		int num;
		Thread t1;
		First(Q q, int num){
			this.q = q;
			this.num = num;
			t1 = new Thread(this, "1");
			t1.start();
		}
		public void run(){
			int i = 1;
			while(i < num+1){
				q.printNum(i++, t1.getName());
			}
		}
	}

	public static class Second implements Runnable {
		Q q;
		Thread t2;
		Second(Q q){
			this.q = q;
			t2 = new Thread(this, "2");
			t2.start();
		}
		public void run(){
			long t = System.nanoTime();
			while(true){
				q.printTime(t, t2.getName());
			}
		}
	}
	
}

