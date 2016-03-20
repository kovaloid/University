package autopark;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.sql.SQLException;
import javax.swing.*;

@SuppressWarnings("serial")
public class Menu extends JFrame {

	private Personnel personnel;
	private Routes routes;
	private Auto auto;
	private Journal journal;

	public Menu(final int user_id) {

		super("Ã≈Õﬁ");
		setBounds(500, 300, 320, 400);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		addWindowListener(new WindowAdapter() {
			public void windowClosing(WindowEvent e) {
				try {
					ConnectService.closeConnect();
				} catch (SQLException e1) {
					System.out.println("connection closed error");
				}
			}
		});

		JButton button_1 = new JButton("¬Œƒ»“≈À»");
		JButton button_2 = new JButton("Ã¿–ÿ–”“€");
		JButton button_3 = new JButton("¿¬“ŒÃŒ¡»À»");
		JButton button_4 = new JButton("∆”–Õ¿À");
		JButton button_5 = new JButton("¬€…“»");
		JLabel label_1 = new JLabel("¬˚·ÂËÚÂ ÔÛÌÍÚ ÏÂÌ˛:");

		button_1.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				try {
					personnel = new Personnel(user_id);
				} catch (ClassNotFoundException | SQLException e1) {
					e1.printStackTrace();
				}
				personnel.setVisible(true);
			}
		});

		button_2.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				try {
					routes = new Routes(user_id);
				} catch (ClassNotFoundException | SQLException e1) {
					e1.printStackTrace();
				}
				routes.setVisible(true);
			}
		});

		button_3.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				try {
					auto = new Auto(user_id);
				} catch (ClassNotFoundException | SQLException e1) {
					e1.printStackTrace();
				}
				auto.setVisible(true);
			}
		});

		button_4.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				try {
					journal = new Journal(user_id);
				} catch (ClassNotFoundException | SQLException e1) {
					e1.printStackTrace();
				}
				journal.setVisible(true);
			}
		});

		button_5.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				try {
					ConnectService.closeConnect();
				} catch (SQLException e1) {
					System.out.println("connection closed error");
				}
				System.exit(0);
			}
		});

		JPanel mainPanel = new JPanel();
		mainPanel.setLayout(null);
		mainPanel.setBounds(0, 0, 600, 60);
		label_1.setBounds(85, 30, 200, 20);
		button_1.setBounds(50, 70, 200, 30);
		button_2.setBounds(50, 120, 200, 30);
		button_3.setBounds(50, 170, 200, 30);
		button_4.setBounds(50, 220, 200, 30);
		button_5.setBounds(50, 270, 200, 30);
		mainPanel.add(label_1);
		mainPanel.add(button_1);
		mainPanel.add(button_2);
		mainPanel.add(button_3);
		mainPanel.add(button_4);
		mainPanel.add(button_5);
		this.add(mainPanel);

	}

}
