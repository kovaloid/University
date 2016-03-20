/*
 2. ���� ����� Furniture c ����������� Chair, Table, � ���� ��������� Tree c ������� tree, 
 � ����� �������������� �� Tree ������������ Oak c ������� oak. ����� Chair ��������� ��������� Tree,
 � ����� Table - Oak. ������� ������ �������� Tree, ��� �������������� ������� Chair, Table,
 ��������� �� ����������  ���������, �������� ����������. ��� ���� ���� �������� ��������� ��� ������,
 ������� ����������� � ��������������� �������. 
*/

package lab2;

import java.util.Random;

public class Furniture {

	public static void main(String[] args) {
		
		int n = 3;
		
		try {
			n = Integer.parseInt(args[0]);
			
			System.out.println("���������� ���������: "+n);
		} catch(Exception e) {
			System.out.println("������� �����! �� ��������� ���������� ��������� - 3");
		}
		if (n < 0){
			n = 3;
		}
		System.out.println("");
		
		Tree[] tr = new Tree[n];
		String[] type = {"������", "���", "�����", "������", "�����", "����", "������"};
		String[] color = {"�������", "�����", "�������", "���������", "����������", "������", "����������"};
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
