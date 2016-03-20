using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Data.OleDb;

namespace beer_factory
{
    public partial class Manager : Form
    {
        public Manager()
        {
            InitializeComponent();
            cn.Open();

            String strSQL1 = "SELECT Orders.id_order, Production.id_beer, name, number_to_buy, fio, data_in, data_out, total_cost, status FROM "+
	                        "Products_In_Order JOIN Production ON Products_In_Order.id_beer = Production.id_beer "+
	                        "JOIN Orders ON Products_In_Order.id_order = Orders.id_order "+
	                        "JOIN Users ON Orders.id_user = Users.id_user";
            dAdapter1 = new OleDbDataAdapter(strSQL1, cn);
            dAdapter1.Fill(ds1, "Products_In_Order");
            dataGrid1.SetDataBinding(ds1, "Products_In_Order");
            dRow1 = ds1.Tables["Products_In_Order"].NewRow();

            String strSQL2 = "SELECT Orders.id_order, Raw_Materials.id_raw, name, number_to_buy, fio, data_in, data_out, total_cost FROM "+
	                        "Raw_In_Order JOIN Raw_materials ON Raw_In_Order.id_raw = Raw_materials.id_raw "+
	                        "JOIN Orders ON Raw_In_Order.id_order = Orders.id_order "+
	                        "JOIN Users ON Orders.id_user = Users.id_user";
            dAdapter2 = new OleDbDataAdapter(strSQL2, cn);
            dAdapter2.Fill(ds2, "Raw_In_Order");
            dataGrid2.SetDataBinding(ds2, "Raw_In_Order");
            dRow2 = ds2.Tables["Raw_In_Order"].NewRow();
        }

        private void FindName_button_Click(object sender, EventArgs e)
        {
            int dbIdInt = 0;
            String fio = fio_field.Text;
            if (fio != "")
            {
                OleDbCommand IDS = new OleDbCommand("SELECT id_user,fio FROM Users", cn);
                OleDbDataReader rdr = IDS.ExecuteReader();
                try
                {
                    while (rdr.Read())
                    {
                        String dbUserName = rdr.GetString(1).ToLower();
                        if (dbUserName.CompareTo(fio.ToLower()) == 0)
                        {
                            dbIdInt = rdr.GetInt32(0);
                        }
                    }
                }
                finally
                {
                    rdr.Close();
                }
                if (dbIdInt != 0)
                {
                    ds1.Clear();
                    String strSQL = "SELECT Orders.id_order, Production.id_beer, name, number_to_buy, fio, data_in, total_cost, status FROM "+
	                                "Products_In_Order JOIN Production ON Products_In_Order.id_beer = Production.id_beer "+
	                                "JOIN Orders ON Products_In_Order.id_order = Orders.id_order "+
	                                "JOIN Users ON Orders.id_user = Users.id_user "+
	                                "WHERE Users.id_user = " + dbIdInt.ToString();
                    dAdapter1 = new OleDbDataAdapter(strSQL, cn);
                    dAdapter1.Fill(ds1, "Products_In_Order");
                    dataGrid1.SetDataBinding(ds1, "Products_In_Order");
                    dRow1 = ds1.Tables["Products_In_Order"].NewRow();
                }
                else
                {
                    MessageBox.Show("We don't have this client!");
                }
            }
            else
            {
                MessageBox.Show("Please.type parametrs of search!");
            }
        }

        private void FindPeriod1_button_Click(object sender, EventArgs e)
        {
            int dbID = 0;
            DateTime firstPeriodDate = dateTimePicker1.Value.Date;

            OleDbCommand IDS = new OleDbCommand("SELECT id_order,data_in FROM Orders", cn);
            OleDbDataReader rdr = IDS.ExecuteReader();
            try
            {
                while (rdr.Read())
                {
                    DateTime dbDate = rdr.GetDateTime(1);
                    if (dbDate < firstPeriodDate)
                    {
                        dbID++;
                    }
                    rdr.GetInt32(0);
                }
            }
            finally
            {
                rdr.Close();
            }
            ds1.Clear();
            String strSQL = "SELECT Orders.id_order, Production.id_beer, name, number_to_buy, fio, data_in, data_out, total_cost, status FROM " +
                            "Products_In_Order JOIN Production ON Products_In_Order.id_beer = Production.id_beer " +
                            "JOIN Orders ON Products_In_Order.id_order = Orders.id_order " +
                            "JOIN Users ON Orders.id_user = Users.id_user " +
                            "WHERE Orders.id_order > " + dbID.ToString();
            dAdapter1 = new OleDbDataAdapter(strSQL, cn);
            dAdapter1.Fill(ds1, "Product_In_Order");
            dataGrid1.SetDataBinding(ds1, "Product_In_Order");
            dRow1 = ds1.Tables["Product_In_Order"].NewRow();
        }

        private void ALL1_button_Click(object sender, EventArgs e)
        {
            ds1.Clear();
            String strSQL = "SELECT Orders.id_order, Production.id_beer, name, number_to_buy, fio, data_in, data_out, total_cost, status FROM " +
                            "Products_In_Order JOIN Production ON Products_In_Order.id_beer = Production.id_beer " +
                            "JOIN Orders ON Products_In_Order.id_order = Orders.id_order " +
                            "JOIN Users ON Orders.id_user = Users.id_user"; 
            dAdapter1 = new OleDbDataAdapter(strSQL, cn);
            dAdapter1.Fill(ds1, "Products_In_Order");
            dataGrid1.SetDataBinding(ds1, "Products_In_Order");
            dRow1 = ds1.Tables["Products_In_Order"].NewRow();
        }

        private void ALL2_button_Click(object sender, EventArgs e)
        {
            ds2.Clear();
            String strSQL = "SELECT Orders.id_order, Raw_Materials.id_raw, name, number_to_buy, fio, data_in, data_out, total_cost FROM " +
                             "Raw_In_Order JOIN Raw_materials ON Raw_In_Order.id_raw = Raw_materials.id_raw " +
                             "JOIN Orders ON Raw_In_Order.id_order = Orders.id_order " +
                             "JOIN Users ON Orders.id_user = Users.id_user"; 
            dAdapter2 = new OleDbDataAdapter(strSQL, cn);
            dAdapter2.Fill(ds2, "Raws_In_Order");
            dataGrid2.SetDataBinding(ds2, "Raws_In_Order");
            dRow2 = ds2.Tables["Raws_In_Order"].NewRow();		
        }

        private void FindPeriod2_button_Click(object sender, EventArgs e)
        {
            int dbID = 0;
            DateTime firstPeriodDate = dateTimePicker2.Value.Date;
          
            OleDbCommand IDS = new OleDbCommand("SELECT id_order, data_in FROM Orders", cn);
            OleDbDataReader rdr = IDS.ExecuteReader();
            try
            {
                while (rdr.Read())
                {
                    DateTime dbDate = rdr.GetDateTime(1);
                    if (dbDate < firstPeriodDate)
                    {
                        dbID++;
                    }
                    rdr.GetInt32(0);
                }
            }
            finally
            {
                rdr.Close();
            }
            ds2.Clear();
            String strSQL2 = "SELECT Orders.id_order, Raw_Materials.id_raw, name, number_to_buy, data_in, data_out, total_cost FROM " +
	                        "Raw_In_Order JOIN Raw_materials ON Raw_In_Order.id_raw = Raw_materials.id_raw " +
	                        "JOIN Orders ON Raw_In_Order.id_order = Orders.id_order " +
	                        "WHERE Orders.id_order > " + dbID.ToString();
            dAdapter2 = new OleDbDataAdapter(strSQL2, cn);
            dAdapter2.Fill(ds2, "Raw_In_Order");
            dataGrid2.SetDataBinding(ds2, "Raw_In_Order");
            dRow2 = ds2.Tables["Raw_In_Order"].NewRow();
        }

        private void Manager_FormClosing(object sender, FormClosingEventArgs e)
        {
            cn.Close();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            ds3.Clear();
     
            String strSQL3 = "SELECT Users.id_user, fio, count(id_beer) AS count_beer FROM Orders " +
                           "JOIN Products_In_Order ON Orders.id_order = Products_In_Order.id_order " +
                           "JOIN Users ON Users.id_user = Orders.id_user " +
                           "GROUP BY Users.id_user, fio " +
                           "HAVING count(id_beer) > 1";
            dAdapter3 = new OleDbDataAdapter(strSQL3, cn);
            dAdapter3.Fill(ds3, "Stat");
            dataGrid3.SetDataBinding(ds3, "Stat");
            dRow3 = ds3.Tables["Stat"].NewRow();	
        }

        private void button2_Click(object sender, EventArgs e)
        {
            ds4.Clear();

            String strSQL4 = "SELECT Production.id_beer, name, SUM(number_to_buy) AS summa FROM Products_In_Order " +
                            "JOIN Production ON Production.id_beer = Products_In_Order.id_beer " +
                            "GROUP BY Production.id_beer, name " +
                            "ORDER BY summa";
            dAdapter4 = new OleDbDataAdapter(strSQL4, cn);
            dAdapter4.Fill(ds4, "Stat");
            dataGrid4.SetDataBinding(ds4, "Stat");
            dRow4 = ds4.Tables["Stat"].NewRow();	
        }

        private void button3_Click(object sender, EventArgs e)
        {
            ds3.Clear();
            ds4.Clear();
        }

    }
}
