/* 
4. 3 ������ ��������� ��������� ������: 1-�� ������� ������� ����� � ��������� � ��������������, 
2-�� ����� ������� ���������� ���������� ����� ������, 3-�� ����� ������� ����� ����� ���������� 
���� �������. ������ ������� ������������� ����� ���� ��� �������� ���������� ����������, 
�������� ����������. ������������ ����������� �� ������� 3. �������� �� ������� ���������� ������
������� ������ ������ � ������ ����������� ������.
*/

package lab4;

import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Date;

class Main extends Thread
{
	static Object obj1 = new Object();
	static Object obj2 = new Object();
	static Object obj3 = new Object();
	static long startTime;

	public static void main(String arg[]) 
	{   
		String str = "";
		int num = 0;
		
		try {
			str = arg[0];
	    } catch (ArrayIndexOutOfBoundsException e) {
	    	System.out.println("�� ������ �� �����!");
	    	System.exit(1);
		}
		try {			
		    num = Integer.parseInt(str);
		    if (num <= 0) {
			    System.out.println("�� ����� ������������� ��������!");
				System.exit(1);	
		    }
		} catch(Exception e) {
			System.out.println("�� ����� �� �����!");
			System.exit(1);
		}
		
		System.out.println("���������� ���������� �������: "+num);
		System.out.println("");
	   
		Thread t1 = new Thread1(num);
		Thread t2 = new Thread2(num);
		Thread t3 = new Thread3(num);
		  
		startTime = System.nanoTime();
		t1.start();
		t2.start();
		t3.start();
	}  
}
  

class Thread1 extends Main
{
	int num;
	String dateTime;
	long currentTime;
	Date curTime = new Date();
	DateFormat dateFormat = new SimpleDateFormat("HH:mm:ss");
	
	public Thread1(int num)
	{   
		this.num = num;
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
	           	    System.out.print(Thread.currentThread().getName());
	           	    System.out.println(" - ������� ����� c ��������������: "+dateTime+":"+currentTime%1000);
            	}
                try{
                	obj3.wait();                 
                }catch(Exception e){}       
			}
		}
	}
}

class Thread2 extends Main
{
	int num;
	int count = 0;
	
	public Thread2(int num)
	{  
		this.num = num;
	}

	public void run()
	{
		for(int i=0; i<num; i++)
		{
			synchronized(obj1){
				synchronized(obj3){          
					obj3.notify();

                    count++;
                    System.out.print(Thread.currentThread().getName());
                    System.out.println(" - ���������� ���������� ����� ������: "+count);
                }
                try{
               		obj1.wait();                 
                }catch(Exception e){}                      
			}
		}  
	}
}

class Thread3 extends Main
{
	int num;
	long currentTime;
	
	public Thread3(int num)
	{	  
		this.num = num;
	}
	
	public void run()
	{
		for(int i=0; i<num; i++)
		{
			synchronized(obj2){
				synchronized(obj1){          
					obj1.notify();
	            
	                currentTime = System.nanoTime();
	                System.out.print(Thread.currentThread().getName());
	                System.out.println(" - ����� ����� ���������� ���� �������: "+(currentTime-startTime)/1e6+" �����������");
	                System.out.println("");
	            }
	            try{
	           		obj2.wait();                 
	            }catch(Exception e){}                      
			}
		}
	}
}
