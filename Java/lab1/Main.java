/*
 1. ������� ����������, ������� ������� ��� ��������������� �����, ������� ���������� � ������, 
 �������� ��� ��������. ����� ���������� ������ (��� ����� ����� ��������) ������ ������������ �����.
 ���������� ����� ������ ���� �������������. ������� �� ������� �������� ��� �������� ������,
 ���������� �� ��� ����� � ��������� ����������.
*/

package lab1;

import java.util.*;

public class Main {
	
	public static String[] divider(String s) {
		
        ArrayList<String> tmp = new ArrayList<String>();
        int i = 0;
        char letter[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m',
        		         'n','o','p','q','r','s','t','u','v','w','x','y','z',
        			     'A','B','C','D','E','F','G','H','I','J','K','L','M',
        			     'N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
        			     '.',',','!','&','?','/','-'};
        
        for (int j = 0; j < s.length(); j++) {
        	for (int n = 0; n < letter.length; n++){
        		if (s.charAt(j) == letter[n]) {
        			if ((j > i) && (i > 0) && (s.charAt(i-1) != '-')) {
        				tmp.add(s.substring(i, j));
        			}
        			if ((j > i) && (i <= 0)) {
        				tmp.add(s.substring(0, j));
        			}
        			i = j + 1;
        		}
        	}
        }
        
        if (i < s.length()) {
            tmp.add(s.substring(i));
        }
        
        return tmp.toArray(new String[tmp.size()]);
	}

	public static void main(String args[]){
		
		System.out.println("��������� ������: " + args[0]);	
		
        String[] r = divider(args[0]);
        int[] value = new int[r.length];
               
        try {
        	for (int i = 0; i < r.length; i++)
        		value[i] = Integer.parseInt(r[i]);	
        } catch (NumberFormatException e) {
            e.printStackTrace();
        } 
        	
        System.out.println("������������� ����� � ������:");
        for (int i = 0; i < r.length; i++)
            System.out.println(value[i]);
        
        System.out.println("����� ����� ����������:");
        Arrays.sort(value);
        for (int i = 0; i < r.length; i++)
            System.out.println(value[i]);
	}
	
}