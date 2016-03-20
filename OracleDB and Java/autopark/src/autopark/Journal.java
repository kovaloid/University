package autopark;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.sql.SQLException;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import javax.swing.JButton;
import javax.swing.JComboBox;
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
public class Journal extends JFrame {

	int selectedID = 0;

	public Journal(int user_id) throws ClassNotFoundException, SQLException {
		super("ЖУРНАЛ");
		setBounds(500, 300, 800, 550);

		ConnectService.makeRequest("SELECT JOURNAL.ID, NUM, TIME_IN, TIME_OUT, NAME, LAST_NAME FROM KOVAL.JOURNAL "
				+ "JOIN KOVAL.AUTO ON AUTO_ID = AUTO.ID "
				+ "JOIN KOVAL.ROUTES ON ROUTE_ID = ROUTES.ID "
				+ "JOIN KOVAL.AUTO_PERSONNEL ON PERSONNEL_ID = AUTO_PERSONNEL.ID "
				+ "ORDER BY JOURNAL.ID");

		final TableModel model = new TableModel();
		model.setDataSource(ConnectService.getResultSet());
		final JTable table = new JTable(model);
		table.setSelectionMode(0);

		final JComboBox<String> combo_1 = new JComboBox<String>();
		final JComboBox<String> combo_2 = new JComboBox<String>();

		ConnectService.makeRequest("SELECT NUM FROM KOVAL.AUTO");
		while (ConnectService.getResultSet().next()) {
			combo_1.addItem(ConnectService.getResultSet().getString(1));
		}
		ConnectService.makeRequest("SELECT ID, NAME FROM KOVAL.ROUTES");
		while (ConnectService.getResultSet().next()) {
			combo_2.addItem(ConnectService.getResultSet().getInt(1) + " - "
					+ ConnectService.getResultSet().getString(2));
		}

		JLabel label_1 = new JLabel("Время отъезда");
		JLabel label_2 = new JLabel("Автомобиль");
		JLabel label_3 = new JLabel("Маршрут");
		JLabel label_4 = new JLabel("Время приезда");
		JButton button_1 = new JButton("ДОБАВИТЬ");
		JButton button_2 = new JButton("ИЗМЕНИТЬ");
		JButton button_3 = new JButton("УДАЛИТЬ");
		final JTextField text_1 = new JTextField("28-MAR-15 08.27.06.854000000 AM");
		final JTextField text_2 = new JTextField("28-MAR-15 08.27.06.854000000 AM");
		JScrollPane scroll_1 = new JScrollPane(table);

		JPanel panel_1 = new JPanel();
		panel_1.setLayout(null);
		panel_1.setBounds(0, 0, 800, 550);

		scroll_1.setBounds(20, 20, 740, 250);
		label_1.setBounds(20, 300, 200, 20);
		label_2.setBounds(20, 350, 200, 20);
		label_3.setBounds(20, 400, 200, 20);
		label_4.setBounds(410, 300, 200, 20);
		button_1.setBounds(80, 445, 200, 40);
		button_2.setBounds(470, 360, 200, 40);
		button_3.setBounds(470, 420, 200, 40);
		text_1.setBounds(150, 300, 200, 25);
		text_2.setBounds(530, 300, 200, 25);
		combo_1.setBounds(150, 350, 200, 25);
		combo_2.setBounds(150, 400, 200, 25);

		if (user_id != 1) {
			button_1.setEnabled(false);
			button_2.setEnabled(false);
			button_3.setEnabled(false);
		}

		panel_1.add(scroll_1);
		panel_1.add(label_1);
		panel_1.add(label_2);
		panel_1.add(label_3);
		panel_1.add(label_4);
		panel_1.add(button_1);
		panel_1.add(button_2);
		panel_1.add(button_3);
		panel_1.add(text_1);
		panel_1.add(text_2);
		panel_1.add(combo_1);
		panel_1.add(combo_2);

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

					String aid = "";
					ConnectService.makeRequest("SELECT ID FROM KOVAL.AUTO WHERE NUM = '"
							+ combo_1.getSelectedItem() + "'");
					ConnectService.getResultSet().next();
					aid = ConnectService.getResultSet().getString(1);

					String rid = "";
					Pattern pattern = Pattern.compile("\\d+");
					String word = combo_2.getSelectedItem().toString();
					Matcher matcher = pattern.matcher(word);
					int start = 0;
					while (matcher.find(start)) {
						rid = word.substring(matcher.start(), matcher.end());
						start = matcher.end();
					}

					boolean errorFlag = false;
					try {
						ConnectService.makeRequest("INSERT INTO KOVAL.JOURNAL(TIME_OUT,AUTO_ID,ROUTE_ID) VALUES('"
								+ text_1.getText()
								+ "','"
								+ aid
								+ "','"
								+ rid
								+ "')");
					} catch (SQLException exc) {
						JOptionPane.showMessageDialog(null, exc.getMessage(),
								"Ошибка", JOptionPane.ERROR_MESSAGE);
						errorFlag = true;
					}

					ConnectService.makeRequest("SELECT JOURNAL.ID, NUM, TIME_IN, TIME_OUT, NAME, LAST_NAME FROM KOVAL.JOURNAL "
							+ "JOIN KOVAL.AUTO ON AUTO_ID = AUTO.ID "
							+ "JOIN KOVAL.ROUTES ON ROUTE_ID = ROUTES.ID "
							+ "JOIN KOVAL.AUTO_PERSONNEL ON PERSONNEL_ID = AUTO_PERSONNEL.ID "
							+ "ORDER BY JOURNAL.ID");

					model.setDataSource(ConnectService.getResultSet());

					if (!errorFlag) {
						JOptionPane.showMessageDialog(null,
								"Новый запись добавлена в базу!", "Внимание",
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
						ConnectService.makeRequest("UPDATE KOVAL.JOURNAL SET TIME_IN = '"
								+ text_2.getText() + "' WHERE ID='"
								+ selectedID + "'");
					} catch (SQLException exc) {
						JOptionPane.showMessageDialog(null, exc.getMessage(),
								"Ошибка", JOptionPane.ERROR_MESSAGE);
						errorFlag = true;
					}

					ConnectService.makeRequest("SELECT JOURNAL.ID, NUM, TIME_IN, TIME_OUT, NAME, LAST_NAME FROM KOVAL.JOURNAL "
							+ "JOIN KOVAL.AUTO ON AUTO_ID = AUTO.ID "
							+ "JOIN KOVAL.ROUTES ON ROUTE_ID = ROUTES.ID "
							+ "JOIN KOVAL.AUTO_PERSONNEL ON PERSONNEL_ID = AUTO_PERSONNEL.ID "
							+ "ORDER BY JOURNAL.ID");
					model.setDataSource(ConnectService.getResultSet());

					if (!errorFlag) {
						JOptionPane.showMessageDialog(null, "Запись изменена!",
								"Внимание", JOptionPane.WARNING_MESSAGE);
					}

				} catch (ClassNotFoundException | SQLException e1) {
					e1.printStackTrace();
				}

			}
		});

		button_3.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {

				try {

					boolean errorFlag = false;
					try {
						ConnectService.makeRequest("DELETE FROM KOVAL.JOURNAL WHERE ID='"
								+ selectedID + "'");
					} catch (SQLException exc) {
						JOptionPane.showMessageDialog(null, exc.getMessage(),
								"Ошибка", JOptionPane.ERROR_MESSAGE);
						errorFlag = true;
					}

					ConnectService.makeRequest("SELECT JOURNAL.ID, NUM, TIME_IN, TIME_OUT, NAME, LAST_NAME FROM KOVAL.JOURNAL "
							+ "JOIN KOVAL.AUTO ON AUTO_ID = AUTO.ID "
							+ "JOIN KOVAL.ROUTES ON ROUTE_ID = ROUTES.ID "
							+ "JOIN KOVAL.AUTO_PERSONNEL ON PERSONNEL_ID = AUTO_PERSONNEL.ID "
							+ "ORDER BY JOURNAL.ID");
					model.setDataSource(ConnectService.getResultSet());

					if (!errorFlag) {
						JOptionPane.showMessageDialog(null,
								"Запись удалена из базы!", "Внимание",
								JOptionPane.WARNING_MESSAGE);
					}

				} catch (ClassNotFoundException | SQLException e1) {
					e1.printStackTrace();
				}

			}
		});

	}

}