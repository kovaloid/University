package autopark;

import java.sql.SQLException;
import javax.swing.JFrame;

@SuppressWarnings("serial")
public class Launcher extends JFrame {

	public static void main(String[] args) throws ClassNotFoundException,
			SQLException {

		ConnectService.init();
		Login login = new Login();
		login.setVisible(true);

	}

}
