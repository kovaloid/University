/*
 2. Есть класс Furniture c подклассами Chair, Table, и есть интерфейс Tree c методом tree, 
 а также унаследованный от Tree подинтерфейс Oak c методом oak. Класс Chair реализует интерфейс Tree,
 а класс Table - Oak. Создать массив объектов Tree, как представителей классов Chair, Table,
 состоящий из количества  элементов, заданных параметром. Для всех этих объектов выполнить все методы,
 которые реализованы в соответствующих классах. 
*/

package lab2;

import java.util.Random;

public class Furniture {

	public static void main(String[] args) {
		
		int n = 3;
		
		try {
			n = Integer.parseInt(args[0]);
			
			System.out.println("Количество предметов: "+n);
		} catch(Exception e) {
			System.out.println("Введите число! По умолчанию количество предметов - 3");
		}
		if (n < 0){
			n = 3;
		}
		System.out.println("");
		
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
		
		for (int i=0; i<n; i++)
			if (tr[i] instanceof Chair)
				tr[i].tree();
		System.out.println("----------");
		for (int i=0; i<n; i++)
			if (tr[i] instanceof Table)
				tr[i].tree();	
		System.out.println("----------");
		for (int i=0; i<n; i++)
			if (tr[i] instanceof Oak)
				((Oak) tr[i]).oak();

	}

}
