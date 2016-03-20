package lab5;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.*;

public class myFrame extends JFrame implements ActionListener {

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	JButton button_01 = new JButton ("Задание № 1");
	JButton button_02 = new JButton ("Задание № 2");
	JButton button_03 = new JButton ("Задание № 3");
	JButton button_04 = new JButton ("Задание № 4");
	JLabel label_01 = new JLabel ("Выберите задание:");

	JButton button_11 = new JButton ("Обработать строку");
	JLabel label_11 = new JLabel ("Введите строку:");
	JLabel label_12 = new JLabel ("Числа в строке:");
	JLabel label_13 = new JLabel ("После сортировки:");
	JTextField text_11 = new JTextField("rh-4fj7h8d--63ej21eh73h8j42");
	
	JButton button_21 = new JButton ("Запустить");
	JLabel label_21 = new JLabel ("Введите число:");
	static JTextField text_21 = new JTextField("20");
	
	JButton button_31 = new JButton ("Старт");
	JLabel label_31 = new JLabel ("Количество выполнений:");
	static JTextField text_31 = new JTextField("50");
	
	JButton button_41 = new JButton ("Старт");
	JLabel label_41 = new JLabel ("Количество выполнений:");
	static JTextField text_41 = new JTextField("50");
	
	JPanel lab1Panel;
	JPanel lab2Panel;
	JPanel lab3Panel;
	JPanel lab4Panel;
	
	public static JTextArea outputTextArea1_1;
	public static JTextArea outputTextArea1_2;
	public static JTextArea outputTextArea2_1;
	public static JTextArea outputTextArea2_2;
	public static JTextArea outputTextArea2_3;
	public static JTextArea outputTextArea3_1;
	public static JTextArea outputTextArea4_1;
	

	public myFrame(){

        button_01.addActionListener(this);
        button_02.addActionListener(this);
        button_03.addActionListener(this);
        button_04.addActionListener(this);
        button_11.addActionListener(this);
        button_21.addActionListener(this);
        button_31.addActionListener(this);
        button_41.addActionListener(this);
	
// General Panel
        JPanel mainPanel = new JPanel ();
        mainPanel.setLayout(null);
        mainPanel.setBounds(0,0,600,60);
		label_01.setBounds(240,5,340,15);
		button_01.setBounds(50,25,120,30);
		button_02.setBounds(175,25,120,30);
		button_03.setBounds(300,25,120,30);
		button_04.setBounds(425,25,120,30);
		mainPanel.add(label_01);
		mainPanel.add(button_01);
		mainPanel.add(button_02);
		mainPanel.add(button_03);
		mainPanel.add(button_04);
		this.add(mainPanel);
		
// Lab 1 Panel
		lab1Panel = new JPanel ();
		lab1Panel.setLayout(null);
		lab1Panel.setBounds(0,60,600,350);
		 
		JPanel panel_11 = new JPanel ();
		panel_11.setLayout(null);
		JTextArea textarea_11 = new JTextArea(10,10);
		textarea_11.setEditable(false);
		outputTextArea1_1 = textarea_11;
		JScrollPane scroll_11 = new JScrollPane (textarea_11,JScrollPane.VERTICAL_SCROLLBAR_ALWAYS,JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);
		scroll_11.setBounds(0,0,150,150);
		panel_11.setBounds(130,90,150,150);
		panel_11.add(scroll_11);
				
		JPanel panel_12 = new JPanel ();
		panel_12.setLayout(null);
		JTextArea textarea_12 = new JTextArea(10,10);
		textarea_12.setEditable(false);
		outputTextArea1_2 = textarea_12;
		JScrollPane scroll_12 = new JScrollPane (textarea_12,JScrollPane.VERTICAL_SCROLLBAR_ALWAYS,JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);
		scroll_12.setBounds(0,0,150,150);
		panel_12.setBounds(320,90,150,150);
		panel_12.add(scroll_12);
	
		label_11.setBounds(150,10,100,20);
		text_11.setBounds(250,10,200,20);
		button_11.setBounds(200,35,200,25);
		label_12.setBounds(160,60,120,30);
		label_13.setBounds(340,60,120,30);
		lab1Panel.add(label_11);
		lab1Panel.add(text_11);
		lab1Panel.add(button_11);
		lab1Panel.add(label_12);
		lab1Panel.add(label_13);
		lab1Panel.add(panel_11);
		lab1Panel.add(panel_12);
		lab1Panel.setVisible(false);
		this.add(lab1Panel);
	
// Lab 2 Panel 
		lab2Panel = new JPanel ();
		lab2Panel.setLayout(null);
		lab2Panel.setBounds(0,60,600,350);
			 
		JPanel panel_21 = new JPanel ();
		panel_21.setLayout(null);
		JTextArea textarea_21 = new JTextArea(10,10);
		textarea_21.setEditable(false);
		outputTextArea2_1 = textarea_21;
		JScrollPane scroll_21 = new JScrollPane (textarea_21,JScrollPane.VERTICAL_SCROLLBAR_ALWAYS,JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);
		scroll_21.setBounds(0,0,190,170);
		panel_21.setBounds(10,70,190,170);
		panel_21.add(scroll_21);

		JPanel panel_22 = new JPanel ();
		panel_22.setLayout(null);
		JTextArea textarea_22 = new JTextArea(10,10);
		textarea_22.setEditable(false);
		outputTextArea2_2 = textarea_22;
		JScrollPane scroll_22 = new JScrollPane (textarea_22,JScrollPane.VERTICAL_SCROLLBAR_ALWAYS,JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);
		scroll_22.setBounds(0,0,180,170);
		panel_22.setBounds(200,70,180,170);
		panel_22.add(scroll_22);
		
		JPanel panel_23 = new JPanel ();
		panel_23.setLayout(null);
		JTextArea textarea_23 = new JTextArea(10,10);
		textarea_23.setEditable(false);
		outputTextArea2_3 = textarea_23;
		JScrollPane scroll_23 = new JScrollPane (textarea_23,JScrollPane.VERTICAL_SCROLLBAR_ALWAYS,JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);
		scroll_23.setBounds(0,0,210,170);
		panel_23.setBounds(380,70,210,170);
		panel_23.add(scroll_23);

		label_21.setBounds(200,10,100,20);
		text_21.setBounds(300,10,100,20);
		button_21.setBounds(200,35,200,25);
		lab2Panel.add(label_21);
		lab2Panel.add(text_21);
		lab2Panel.add(button_21);
		lab2Panel.add(panel_21);
		lab2Panel.add(panel_22);
		lab2Panel.add(panel_23);
		lab2Panel.setVisible(false);
		this.add(lab2Panel);
		
// Lab 3 Panel
		lab3Panel = new JPanel ();
		lab3Panel.setLayout(null);
		lab3Panel.setBounds(0,60,600,350);
				 
		JPanel panel_31 = new JPanel ();
		panel_31.setLayout(null);
		JTextArea textarea_31 = new JTextArea(10,10);
		textarea_31.setEditable(false);
		outputTextArea3_1 = textarea_31;
		JScrollPane scroll_31 = new JScrollPane (textarea_31,JScrollPane.VERTICAL_SCROLLBAR_ALWAYS,JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);
		scroll_31.setBounds(0,0,400,170);
		panel_31.setBounds(100,70,400,170);
		panel_31.add(scroll_31);
					
		label_31.setBounds(170,10,200,20);
		text_31.setBounds(330,10,100,20);
		button_31.setBounds(200,35,200,25);
		lab3Panel.add(label_31);
		lab3Panel.add(text_31);
		lab3Panel.add(button_31);
		lab3Panel.add(panel_31);
		lab3Panel.setVisible(false);
		this.add(lab3Panel);
			
// Lab 4 Panel
		lab4Panel = new JPanel ();
		lab4Panel.setLayout(null);
		lab4Panel.setBounds(0,60,600,350);
						 
		JPanel panel_41 = new JPanel ();
		panel_41.setLayout(null);
		JTextArea textarea_41 = new JTextArea(10,10);
		textarea_41.setEditable(false);
		outputTextArea4_1 = textarea_41;
		JScrollPane scroll_41 = new JScrollPane (textarea_41,JScrollPane.VERTICAL_SCROLLBAR_ALWAYS,JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);
		scroll_41.setBounds(0,0,500,170);
		panel_41.setBounds(50,70,500,170);
		panel_41.add(scroll_41);
							
		label_41.setBounds(170,10,200,20);
		text_41.setBounds(330,10,100,20);
		button_41.setBounds(200,35,200,25);
		lab4Panel.add(label_41);
		lab4Panel.add(text_41);
		lab4Panel.add(button_41);
		lab4Panel.add(panel_41);
		lab4Panel.setVisible(false);
		this.add(lab4Panel);
		
	}
	
	public void actionPerformed(ActionEvent event){

		String[] args = new String[1];
		this.setSize(600,350);
		
		if (event.getSource() == button_01 ){
			this.setLocationRelativeTo(null);
			lab1Panel.setVisible(true);
			lab2Panel.setVisible(false);
			lab3Panel.setVisible(false);
			lab4Panel.setVisible(false);
			myFrame.outputTextArea1_1.setText("");
			myFrame.outputTextArea1_2.setText("");
		}
		if (event.getSource() == button_02 ){
			this.setLocationRelativeTo(null);
			lab1Panel.setVisible(false);
			lab2Panel.setVisible(true);
			lab3Panel.setVisible(false);
			lab4Panel.setVisible(false);
			myFrame.outputTextArea2_1.setText("");
			myFrame.outputTextArea2_2.setText("");
			myFrame.outputTextArea2_3.setText("");
		}
		if (event.getSource() == button_03 ){
			this.setLocationRelativeTo(null);
			lab1Panel.setVisible(false);
			lab2Panel.setVisible(false);
			lab3Panel.setVisible(true);
			lab4Panel.setVisible(false);
			myFrame.outputTextArea3_1.setText("");
		}
		if (event.getSource() == button_04 ){
			this.setLocationRelativeTo(null);
			lab1Panel.setVisible(false);
			lab2Panel.setVisible(false);
			lab3Panel.setVisible(false);
			lab4Panel.setVisible(true);
			myFrame.outputTextArea4_1.setText("");
		}
		if (event.getSource() == button_11 ){
			myFrame.outputTextArea1_1.setText("");
			myFrame.outputTextArea1_2.setText("");
			args[0] = text_11.getText();
			Lab1.main(args);
		}
		if (event.getSource() == button_21 ){
			myFrame.outputTextArea2_1.setText("");
			myFrame.outputTextArea2_2.setText("");
			myFrame.outputTextArea2_3.setText("");
			args[0] = text_21.getText();
			Lab2.main(args);
		}
		if (event.getSource() == button_31 ){
			myFrame.outputTextArea3_1.setText("");
			args[0] = text_31.getText();
			Lab3.main(args);
		}
		if (event.getSource() == button_41 ){
			myFrame.outputTextArea4_1.setText("");
			args[0] = text_41.getText();
			Lab4.main(args);
		}

	}
	
}

