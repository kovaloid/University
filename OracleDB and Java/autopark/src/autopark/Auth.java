package autopark;

import java.sql.ResultSet;
import java.sql.SQLException;

public class Auth {

	public static int checkAndGetUserId(String user, String pass) {

		int id = -1;
		
		try {	
			ConnectService.makeRequest("SELECT LOGIN, PASSWORD FROM KOVAL.USERS");
			ResultSet rs = ConnectService.getResultSet();
			while (rs.next()) {
				if (user.equals(rs.getString(1))) {
					if (pass.equals(rs.getString(2))) {
						id = rs.getRow();
					}
				}
			}
			System.out.println("user = " + user + " ; id = " + id);
		} catch (SQLException e1) {
			System.out.println("login error");
		}

		return id;
	}

}
