/*
 5. ������� ���������� � ���������������� ����������� ��� ������� 1-4. ��� ����� ���������� 
    ������ ���� ����������� ����������� ������ �� ������ ������ ���������� � ��� ����������. 
    �������������� ������� 1-4 ���, ����� ���� ����� ���������� ���� � ���������� �����, 
    ���� � ��������� ��������. �.�. ��� ������ ���� �� ���������� ��������� ������,
    � ��������� ����������� ����������.
*/

package lab5;

import javax.swing.JFrame;

public class Lab5 {

	static myFrame frame;

	public static void main(String[] args) {
		frame = new myFrame();
		frame.setVisible(true);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setTitle("������� � 5");
		frame.setSize(600,100);
		frame.setResizable(false);
		frame.setLocationRelativeTo(null);
		frame.setLayout(null);
	}

}
