package autopark;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.sql.SQLException;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JPasswordField;
import javax.swing.JTextField;

@SuppressWarnings("serial")
public class Login extends JFrame {

	public Login() {
		super("ВХОД");
		setBounds(500, 300, 300, 260);
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

		JLabel label_1 = new JLabel("Введите логин:");
		final JTextField text_1 = new JTextField("admin");
		text_1.setHorizontalAlignment(JTextField.CENTER);
		JLabel label_2 = new JLabel("Введите пароль:");
		final JPasswordField text_2 = new JPasswordField("admin");
		text_2.setHorizontalAlignment(JPasswordField.CENTER);
		JButton button_1 = new JButton("OK");

		JPanel panel_1 = new JPanel();
		panel_1.setLayout(null);
		panel_1.setBounds(0, 0, 300, 300);
		label_1.setBounds(90, 10, 200, 30);
		text_1.setBounds(40, 40, 200, 30);
		label_2.setBounds(90, 70, 200, 30);
		text_2.setBounds(40, 100, 200, 30);
		button_1.setBounds(40, 150, 200, 30);
		panel_1.add(label_1);
		panel_1.add(text_1);
		panel_1.add(label_2);
		panel_1.add(text_2);
		panel_1.add(button_1);
		this.add(panel_1);

		button_1.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {

				String user = String.valueOf(text_1.getText()).trim();
				String pass = String.valueOf(text_2.getPassword()).trim();
				int user_id = Auth.checkAndGetUserId(user, pass);
				
				if (user_id < 0) {
					JOptionPane.showMessageDialog(null,
							"Неправильный логин или пароль!", "Ошибка",
							JOptionPane.ERROR_MESSAGE);
				} else {
					closeLoginWindow();
					Menu menu = new Menu(user_id);
					menu.setVisible(true);
				}

			}
		});
	}

	private void closeLoginWindow() {
		this.setVisible(false);
	}

}
