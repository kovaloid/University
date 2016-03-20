package lab5;

import java.util.Random;
import javax.swing.JOptionPane;

public class Lab2 {

	public static void main(String[] args) {
		if (args[0].isEmpty())
		{
			JOptionPane.showMessageDialog(Lab5.frame,"Вы ничего не ввели!","Ошибка аргумента",JOptionPane.ERROR_MESSAGE);
		}
		int n = 0;
		try {
			n = Integer.parseInt(args[0]);
			if(n < 0){
				n = 20;
				JOptionPane.showMessageDialog(null, "Вы ввели число < 0! Теперь n = " + n);
				myFrame.text_21.setText("20");
			}
		} catch (NumberFormatException e) {
			n = 20;
			JOptionPane.showMessageDialog(null, "Ошибка ввода! Теперь n = " + n);
			myFrame.text_21.setText("20");
		}
		Tree[] tr = new Tree[n];
		String[] type = {"береза", "ива", "ясень", "рябина", "сосна", "клен", "тополь"};
		String[] color = {"красный", "синий", "зеленый", "оранжевый", "коричневый", "желтый", "фиолетовый"};
		Random rand = new Random();
		int mix;
		for(int i=0; i<n; i++) {
			mix = rand.nextInt(2);
			if (mix == 0) {
				tr[i] = new Chair();
			    tr[i].setTypeOfTree(i+1,type[rand.nextInt(type.length)]);
			}
			else {
				tr[i] = new Table();
			    ((Oak) tr[i]).setColorOfOak(i+1,color[rand.nextInt(color.length)]);
			}
		}
		int n1 = 0, n2 = 0, j1 = 0, j2 = 0;
		for (int i=0; i<n; i++) {
			if (tr[i] instanceof Chair)
				n1++;
			if (tr[i] instanceof Table)
				n2++;	
		}
		String[] arr1 = new String[n1];
		String[] arr2 = new String[n2];
		String[] arr3 = new String[n2];
		for (int i = 0; i < n; i++)
			if (tr[i] instanceof Chair)
				arr1[j1++] = tr[i].tree();
		for (int i = 0; i < n; i++)
			if (tr[i] instanceof Table) {
				arr2[j2] = tr[i].tree();	
				arr3[j2++] = ((Oak) tr[i]).oak();
			}
        for (int i = 0; i < arr1.length; i++) {
        	myFrame.outputTextArea2_1.append(" " + arr1[i] + "\n");
        }
        for (int i = 0; i < arr2.length; i++) {
        	myFrame.outputTextArea2_2.append(" " + arr2[i] + "\n");
        }
        for (int i = 0; i < arr3.length; i++) {
        	myFrame.outputTextArea2_3.append(" " + arr3[i] + "\n");
        }
	}
	
	public static interface Tree {
		public String tree();
		public void setTypeOfTree(int num, String type);
	}
	
	public static interface Oak extends Tree {
		String type = "дуб";
		public String oak();
		public void setColorOfOak(int num, String color);
	}
	
	public static class Chair implements Tree{
		private String type;
		private int num;
		public String tree() {
			return "стул #"+num+": тип дерева: "+type;
		}
		public void setTypeOfTree(int num, String type) {
			this.type = type;
			this.num = num;
		}
	}
	
	public static class Table implements Oak {
		public String color;
		private int num;
		public String tree() {
			return "стол #"+num+": тип дерева: "+type;
		}
		public String oak() {
			return "стол #"+num+": цвет дуба: "+color;
		}
		public void setColorOfOak(int num, String color) {
			this.color = color;
			this.num = num;
		}
		public void setTypeOfTree(int num, String type) {}
	}

}

