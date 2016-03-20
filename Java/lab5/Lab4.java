package lab5;

import javax.swing.JOptionPane;

import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Date;

class Lab4 extends Thread {
	
	static Object obj1 = new Object();
	static Object obj2 = new Object();
	static Object obj3 = new Object();
	static long startTime;

	public static void main(String[] args) 
	{   
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
				myFrame.text_41.setText("50");
			}
		} catch (NumberFormatException e) {
			num = 50;
			JOptionPane.showMessageDialog(null, "Ошибка ввода! Теперь n = " + num);
			myFrame.text_41.setText("50");
		}
	   
		Thread t1 = new Thread1(num);
		Thread t2 = new Thread2(num);
		Thread t3 = new Thread3(num);
		  
		startTime = System.nanoTime();
		t1.start();
		t2.start();
		t3.start();
	}  
}
  

class Thread1 extends Lab4
{
	int num;
	String dateTime;
	long currentTime;
	Date curTime = new Date();
	DateFormat dateFormat = new SimpleDateFormat("HH:mm:ss");
	
	public Thread1(int num)
	{   
		this.num = num;
		this.setName("Thread-0");
	}
	
	public void run()
	{    
		for(int i=0; i<num; i++)
		{
			synchronized(obj3){
            	synchronized(obj2){          
            		obj2.notify();

	           	    dateTime = dateFormat.format(curTime);
	           	    currentTime = System.currentTimeMillis();
	           	    myFrame.outputTextArea4_1.append(Thread.currentThread().getName());
	           	    myFrame.outputTextArea4_1.append(" - текущее время c миллисекундами: "+dateTime+":"+currentTime%1000+"\n");
            	}
                try{
                	obj3.wait();                 
                }catch(Exception e){}       
			}
		}
	}
}

class Thread2 extends Lab4
{
	int num;
	int count = 0;
	
	public Thread2(int num)
	{  
		this.num = num;
		this.setName("Thread-1");
	}

	public void run()
	{
		for(int i=0; i<num; i++)
		{
			synchronized(obj1){
				synchronized(obj3){          
					obj3.notify();

                    count++;
                    myFrame.outputTextArea4_1.append(Thread.currentThread().getName());
                    myFrame.outputTextArea4_1.append(" - количество выполнений этого потока: "+count+"\n");
                }
                try{
               		obj1.wait();                 
                }catch(Exception e){}                      
			}
		} 
	}
}

class Thread3 extends Lab4
{
	int num;
	long currentTime;
	
	public Thread3(int num)
	{	  
		this.num = num;
		this.setName("Thread-2");
	}
	
	public void run()
	{
		for(int i=0; i<num; i++)
		{
			synchronized(obj2){
				synchronized(obj1){          
					obj1.notify();
	                currentTime = System.nanoTime();
	                myFrame.outputTextArea4_1.append(Thread.currentThread().getName());
	                myFrame.outputTextArea4_1.append(" - общее время выполнения всех потоков: "+(currentTime-startTime)/1e6+" миллисекунд\n\n");
	            }
	            try{
	           		obj2.wait();                 
	            }catch(Exception e){}                      
			}
		}
	}
}
