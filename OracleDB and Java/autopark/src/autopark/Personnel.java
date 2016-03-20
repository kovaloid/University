package autopark;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.sql.SQLException;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.JTextField;
import javax.swing.ListSelectionModel;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;

@SuppressWarnings("serial")
public class Personnel extends JFrame {

	int selectedID = 0;

	public Personnel(int user_id) throws ClassNotFoundException, SQLException {
		super("ВОДИТЕЛИ");
		setBounds(500, 300, 800, 550);

		ConnectService.makeRequest("SELECT ID, FIRST_NAME, LAST_NAME FROM KOVAL.AUTO_PERSONNEL ORDER BY ID");

		final TableModel model = new TableModel();
		model.setDataSource(ConnectService.getResultSet());
		final JTable table = new JTable(model);

		JLabel label_1 = new JLabel("Имя");
		JLabel label_2 = new JLabel("Фамилия");
		JButton button_1 = new JButton("ДОБАВИТЬ");
		JButton button_2 = new JButton("УДАЛИТЬ");
		final JTextField text_1 = new JTextField();
		final JTextField text_2 = new JTextField();
		JScrollPane scroll_1 = new JScrollPane(table);

		JPanel panel_1 = new JPanel();
		panel_1.setLayout(null);
		panel_1.setBounds(0, 0, 800, 550);

		scroll_1.setBounds(380, 40, 360, 420);
		label_1.setBounds(40, 100, 200, 20);
		label_2.setBounds(40, 150, 200, 20);
		button_1.setBounds(100, 250, 200, 40);
		button_2.setBounds(100, 320, 200, 40);
		text_1.setBounds(150, 100, 200, 25);
		text_2.setBounds(150, 150, 200, 25);

		if (user_id != 1) {
			button_1.setEnabled(false);
			button_2.setEnabled(false);
		}

		panel_1.add(scroll_1);
		panel_1.add(label_1);
		panel_1.add(label_2);
		panel_1.add(button_1);
		panel_1.add(button_2);
		panel_1.add(text_1);
		panel_1.add(text_2);

		this.setContentPane(panel_1);

		ListSelectionModel selModel = table.getSelectionModel();
		selModel.addListSelectionListener(new ListSelectionListener() {
			public void valueChanged(ListSelectionEvent e) {
				int[] selectedRows = table.getSelectedRows();
				for (int i = 0; i < selectedRows.length; i++) {
					int selIndex = selectedRows[0];
					Object value = model.getValueAt(selIndex, 0);
					selectedID = Integer.parseInt(String.valueOf(value));
				}
			}
		});

		button_1.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {

				try {

					boolean errorFlag = false;
					try {
						ConnectService.makeRequest("INSERT INTO KOVAL.AUTO_PERSONNEL(FIRST_NAME,LAST_NAME) VALUES('"
								+ text_1.getText()
								+ "','"
								+ text_2.getText()
								+ "')");
					} catch (SQLException exc) {
						JOptionPane.showMessageDialog(null, exc.getMessage(),
								"Ошибка", JOptionPane.ERROR_MESSAGE);
						errorFlag = true;
					}

					ConnectService.makeRequest("SELECT ID, FIRST_NAME, LAST_NAME FROM KOVAL.AUTO_PERSONNEL ORDER BY ID");
					model.setDataSource(ConnectService.getResultSet());

					if (!errorFlag) {
						JOptionPane.showMessageDialog(null,
								"Новый водитель добавлен в базу!", "Внимание",
								JOptionPane.WARNING_MESSAGE);
					}

				} catch (ClassNotFoundException | SQLException e1) {
					e1.printStackTrace();
				}

			}
		});

		button_2.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				try {

					boolean errorFlag = false;
					try {
						ConnectService.makeRequest("DELETE FROM KOVAL.AUTO_PERSONNEL WHERE ID='"
								+ selectedID + "'");
					} catch (SQLException exc) {
						JOptionPane.showMessageDialog(null, exc.getMessage(),
								"Ошибка", JOptionPane.ERROR_MESSAGE);
						errorFlag = true;
					}

					ConnectService.makeRequest("SELECT ID, FIRST_NAME, LAST_NAME FROM KOVAL.AUTO_PERSONNEL ORDER BY ID");
					model.setDataSource(ConnectService.getResultSet());

					if (!errorFlag) {
						JOptionPane.showMessageDialog(null,
								"Водитель удален из базы!", "Внимание",
								JOptionPane.WARNING_MESSAGE);
					}

				} catch (ClassNotFoundException | SQLException e1) {
					e1.printStackTrace();
				}
			}
		});

	}

}
