package lab5;

import java.util.ArrayList;
import java.util.Arrays;
import javax.swing.JOptionPane;

public class Lab1 {

	public static void main(String[] args) {		
		if (args[0].isEmpty())
		{
			JOptionPane.showMessageDialog(Lab5.frame,"Вы ничего не ввели!","Ошибка аргумента",JOptionPane.ERROR_MESSAGE);
			myFrame.outputTextArea1_1.setText("");
	        myFrame.outputTextArea1_2.setText("");
		}
		String[] arr = divider(args[0]);
        int[] value = new int[arr.length];
        try {
        	for (int i = 0; i < arr.length; i++)
        		value[i] = Integer.parseInt(arr[i]);	
        } catch (NumberFormatException x) {
        	for (int i = 0; i < arr.length; i++)
        		arr[i] = "";
        	arr[0] = "Ошибка";
        } 		        
        Arrays.sort(value);
        String[] arr2 = new String[arr.length];
        for (int i = 0; i < value.length; i++)
    		arr2[i] = Integer.toString(value[i]);
        for (int i = 0; i < arr.length; i++) {
        	myFrame.outputTextArea1_1.append(" " + arr[i] + "\n");
        	myFrame.outputTextArea1_2.append(" " + arr2[i] + "\n");
        }
	}
	
	public static String[] divider(String s) {
        ArrayList<String> tmp = new ArrayList<String>();
        int i = 0;
        char letter[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m',
        		         'n','o','p','q','r','s','t','u','v','w','x','y','z',
        			     'A','B','C','D','E','F','G','H','I','J','K','L','M',
        			     'N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
        			     'а','б','в','г','д','е','ё','ж','з','и','й','к','л','м','н','о','п',
        			     'р','с','т','у','ф','х','ц','ч','ш','щ','ъ','ы','ь','э','ю','я',
        			     'А','Б','В','Г','Д','Е','Ё','Ж','З','И','Й','К','Л','М','Н','О','П',
        			     'Р','С','Т','У','Ф','Х','Ц','Ч','Ш','Щ','Ъ','Ы','Ь','Э','Ю','Я',
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
	
}
