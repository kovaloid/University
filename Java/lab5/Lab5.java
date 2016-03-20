/*
 5. —оздать приложение с пользовательским интерфейсом дл€ заданий 1-4. ƒл€ этого приложени€ 
    должна быть реализована возможность выбора из списка любого приложени€ и его выполнение. 
    ћодифицировать задани€ 1-4 так, чтобы весь вывод происходил либо в диалоговых окнах, 
    либо в текстовых област€х. “.е. это должно быть не приложение командной строки,
    а полностью графическое приложение.
*/

package lab5;

import javax.swing.JFrame;

public class Lab5 {

	static myFrame frame;

	public static void main(String[] args) {
		frame = new myFrame();
		frame.setVisible(true);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setTitle("«адание є 5");
		frame.setSize(600,100);
		frame.setResizable(false);
		frame.setLocationRelativeTo(null);
		frame.setLayout(null);
	}

}
