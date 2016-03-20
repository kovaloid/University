package autopark;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

public class ConnectService {

	// how to connect:
	// http://theopentutorials.com/tutorials/java/jdbc/jdbc-oracle-connection-tutorial/

	private static Connection con;
	private static Statement stmt;
	private static ResultSet rs;
	private final static String username = "system";
	private final static String password = "koval";
	private final static String hostname = "localhost";

	public static void init() {
		
		try {
			Class.forName("oracle.jdbc.driver.OracleDriver");
			con = DriverManager.getConnection("jdbc:oracle:thin:" + username
					+ "/" + password + "@" + hostname);
			stmt = con.createStatement();
			System.out.println("connection opened");
		} catch (SQLException | ClassNotFoundException e) {
			System.out.println("connection opened error");
			System.exit(0);
		}
		
	}

	public static void makeRequest(String request) throws SQLException {
		rs = stmt.executeQuery(request);
	}

	public static ResultSet getResultSet() {
		return rs;
	}

	public static void closeConnect() throws SQLException {
		stmt.close();
		con.close();
		System.out.println("connection closed");
	}

}
