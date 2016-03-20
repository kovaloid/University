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
    public partial class Stockman : Form
    {
        public int user_id = 0;

        public Stockman()
        {
            InitializeComponent();
            cn.Open();
            String strSQL = "SELECT Orders.id_order, Production.id_beer, name, number, number_to_buy, company, status FROM " +
                            "Products_In_Order JOIN Production ON Products_In_Order.id_beer = Production.id_beer " +
                            "JOIN Orders ON Products_In_Order.id_order = Orders.id_order " +
                            "JOIN Users ON Orders.id_user = Users.id_user " +
                            "WHERE Products_In_Order.status = 0";
            dAdapter = new OleDbDataAdapter(strSQL, cn);
            dAdapter.Fill(dsNumber, "Orders");
            dataGrid1.SetDataBinding(dsNumber, "Orders");
            dRow = dsNumber.Tables["Orders"].NewRow();
            dRow.BeginEdit();

            String strSQL3 = "SELECT id_raw, name FROM Raw_Materials";
            dAdapter3 = new OleDbDataAdapter(strSQL3, cn);
            dAdapter3.Fill(dsNewRawMat, "Raw_Materials");
            dataGrid3.SetDataBinding(dsNewRawMat, "Raw_Materials");
            dRow3 = dsNewRawMat.Tables["Raw_Materials"].NewRow();
        }

        private void btnChange_Click(object sender, EventArgs e)
        {
            bool notThisNum = false;
            bool lessNum = false;
            dRow.EndEdit();
            DateTime MyDateTime = DateTime.Today;
            int RowID = 0;
            String strSQL = "UPDATE Products_In_Order SET status = 1, data_out = ? WHERE status = 0 AND id_order = ? AND id_beer = ?";
            OleDbCommand cmdIC = new OleDbCommand(strSQL, cn);
            cmdIC.Parameters.Add("@p1", OleDbType.Date, 8);
            cmdIC.Parameters.Add("@p2", OleDbType.Integer, 4);
            cmdIC.Parameters.Add("@p3", OleDbType.Integer, 4);
            for (RowID = 0; RowID < dsNumber.Tables["Orders"].Rows.Count; RowID++)
            {
                DataRow Row = dsNumber.Tables["Orders"].Rows[RowID];
                if (Row["status"].ToString() == "True")
                {
                    if ((int.Parse(Row["number"].ToString()) - int.Parse(Row["number_to_buy"].ToString())) >= 0)
                    {
                        cmdIC.Parameters[0].Value = MyDateTime;
                        cmdIC.Parameters[1].Value = int.Parse(Row["id_order"].ToString());
                        cmdIC.Parameters[2].Value = int.Parse(Row["id_beer"].ToString());
                        cmdIC.ExecuteNonQuery();
                    }
                    else
                    {
                        DialogResult result;
                        result = MessageBox.Show("У нас нет такого количества " + Row["name"] + "! Хотите ли заказать меньшее количество пива?", "Нет пива", MessageBoxButtons.YesNo);
                        if (result == DialogResult.Yes)
                        {
                            lessNum = true;
                        }
                        notThisNum = true;
                    }
                }
            }
            RowID = 0;
            strSQL = "UPDATE Production SET number = ? WHERE id_beer = ?";
            cmdIC = new OleDbCommand(strSQL, cn);
            cmdIC.Parameters.Add("@p1", OleDbType.Integer, 4);
            cmdIC.Parameters.Add("@p2", OleDbType.Integer, 4);
            for (RowID = 0; RowID < dsNumber.Tables["Orders"].Rows.Count; RowID++)
            {
                DataRow Row = dsNumber.Tables["Orders"].Rows[RowID];
                if ((Row["status"].ToString() == "True") & ((!notThisNum) | ((lessNum) & (int.Parse(Row["number_to_buy"].ToString()) - int.Parse(Row["number"].ToString())) <= 0)))
                {
                    cmdIC.Parameters[0].Value = int.Parse(Row["number"].ToString()) - int.Parse(Row["number_to_buy"].ToString());
                    cmdIC.Parameters[1].Value = int.Parse(Row["id_beer"].ToString());
                    cmdIC.ExecuteNonQuery();
                }
                else if ((Row["status"].ToString() == "True") & lessNum)
                {
                    cmdIC.Parameters[0].Value = 0;
                    cmdIC.Parameters[1].Value = int.Parse(Row["id_beer"].ToString());
                    cmdIC.ExecuteNonQuery();
                }
            }
            if (lessNum)
            {
                RowID = 0;
                strSQL = "UPDATE Products_In_Order SET number_to_buy = ? WHERE id_order = ? AND id_beer = ?";
                cmdIC = new OleDbCommand(strSQL, cn);
                cmdIC.Parameters.Add("@p1", OleDbType.Integer, 4);
                cmdIC.Parameters.Add("@p2", OleDbType.Integer, 4);
                cmdIC.Parameters.Add("@p3", OleDbType.Integer, 4);
                for (RowID = 0; RowID < dsNumber.Tables["Orders"].Rows.Count; RowID++)
                {
                    DataRow Row = dsNumber.Tables["Orders"].Rows[RowID];
                    if ((Row["status"].ToString() == "True") & ((int.Parse(Row["number_to_buy"].ToString()) - int.Parse(Row["number"].ToString())) >= 0))
                    {
                        cmdIC.Parameters[0].Value = int.Parse(Row["number_to_buy"].ToString()) - int.Parse(Row["number"].ToString());
                        cmdIC.Parameters[1].Value = int.Parse(Row["id_order"].ToString());
                        cmdIC.Parameters[2].Value = int.Parse(Row["id_beer"].ToString());
                        cmdIC.ExecuteNonQuery();
                    }
                }

                RowID = 0;
                strSQL = "INSERT INTO Products_In_Order (id_order,id_beer,number_to_buy,status,data_out) VALUES (?, ?, ?, 1, ?)";
                cmdIC = new OleDbCommand(strSQL, cn);
                cmdIC.Parameters.Add("@p1", OleDbType.Integer, 4);
                cmdIC.Parameters.Add("@p2", OleDbType.Integer, 4);
                cmdIC.Parameters.Add("@p1", OleDbType.Integer, 4);
                cmdIC.Parameters.Add("@p1", OleDbType.Date, 4);
                for (RowID = 0; RowID < dsNumber.Tables["Orders"].Rows.Count; RowID++)
                {
                    DataRow Row = dsNumber.Tables["Orders"].Rows[RowID];
                    if ((Row["status"].ToString() == "True") & ((int.Parse(Row["number_to_buy"].ToString()) - int.Parse(Row["number"].ToString())) >= 0))
                    {
                        cmdIC.Parameters[0].Value = int.Parse(Row["id_order"].ToString());
                        cmdIC.Parameters[1].Value = int.Parse(Row["id_beer"].ToString());
                        cmdIC.Parameters[2].Value = int.Parse(Row["number"].ToString());
                        cmdIC.Parameters[3].Value = MyDateTime;
                        cmdIC.ExecuteNonQuery();
                    }
                }
            }
            dRow.BeginEdit();

            dsNumber.Clear();
            strSQL = "SELECT Orders.id_order, Production.id_beer, name, number, number_to_buy, company, status FROM " +
                        "Products_In_Order JOIN Production ON Products_In_Order.id_beer = Production.id_beer " +
                        "JOIN Orders ON Products_In_Order.id_order = Orders.id_order " +
                        "JOIN Users ON Orders.id_user = Users.id_user " +
                        "WHERE Products_In_Order.status = 0";
            
            dAdapter = new OleDbDataAdapter(strSQL, cn);
            dAdapter.Fill(dsNumber, "Orders");
            dataGrid1.SetDataBinding(dsNumber, "Orders");
            dRow = dsNumber.Tables["Orders"].NewRow();
            dRow.BeginEdit();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            String beerNameStr = txtBoxName.Text;
            String beerNumberStr = txtBoxNumber.Text;
            int dbIdInt = 0;
            if (beerNameStr == "")
            {
                MessageBox.Show("Пожалуйста, введите название пива, которое вы хотите добавить!");
            }
            else if (beerNumberStr == "")
            {
                MessageBox.Show("Пожалуйста, введите количество пива, которое вы хотите добавить!");
            }
            else
            {
                OleDbCommand IDS = new OleDbCommand("SELECT id_beer,name FROM Production", cn);
                OleDbDataReader rdr = IDS.ExecuteReader();
                try
                {
                    while (rdr.Read())
                    {
                        String dbNameStr = rdr.GetString(1); ;
                        if (beerNameStr.CompareTo(dbNameStr) == 0)
                        {
                            dbIdInt = rdr.GetInt32(0);
                        }
                    }
                }
                finally
                {
                    rdr.Close();
                }
                if (dbIdInt == 0)
                {
                    MessageBox.Show("У нас нет такого пива!");
                }
                else
                {
                    int beerNumberInt = int.Parse(beerNumberStr);
                    String strSQL = "UPDATE Production SET number = number+? WHERE id_beer = ?";
                    OleDbCommand cmdIC = new OleDbCommand(strSQL, cn);
                    cmdIC.Parameters.Add("@p1", OleDbType.Integer, 4);
                    cmdIC.Parameters.Add("@p2", OleDbType.Integer, 4);
                    cmdIC.Parameters[0].Value = beerNumberInt;
                    cmdIC.Parameters[1].Value = dbIdInt;
                    cmdIC.ExecuteNonQuery();
                }
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            DateTime MyDateTime = DateTime.Today;
            String rawMatNameStr = txtBoxRawMatName.Text;
            String rawMatNumberStr = txtBoxRawMatNumber.Text;
            String rawMatPriceStr = txtBoxRawMatPrice.Text;
            int dbIdInt = 0;
            int orderID = 0;
            if (rawMatNameStr == "")
            {
                MessageBox.Show("Вы не заполнили поле с названием сырья!");
            }
            else if (rawMatNumberStr == "")
            {
                MessageBox.Show("Вы не заполнили поле с количеством сырья!");
            }
            else if (rawMatPriceStr == "")
            {
                MessageBox.Show("Вы не заполнили поле с ценой сырья!");
            }
            else
            {
                OleDbCommand IDS = new OleDbCommand("SELECT id_raw,name FROM Raw_Materials", cn);
                OleDbDataReader rdr = IDS.ExecuteReader();
                try
                {
                    while (rdr.Read())
                    {
                        String dbNameStr = rdr.GetString(1); ;
                        if (rawMatNameStr.CompareTo(dbNameStr) == 0)
                        {
                            dbIdInt = rdr.GetInt32(0);
                        }
                    }
                }
                finally
                {
                    rdr.Close();
                }

                if (dbIdInt == 0)
                {
                    MessageBox.Show("У нас нет такого сырья!");
                }
                else
                {
                    OleDbCommand IDS2 = new OleDbCommand("SELECT id_order FROM Orders", cn);
                    OleDbDataReader rdr2 = IDS2.ExecuteReader();
                    try
                    {
                        while (rdr2.Read())
                        {
                            orderID = rdr2.GetInt32(0);
                        }
                    }
                    finally
                    {
                        rdr2.Close();
                    }
                    orderID++;
                    double test2 = double.Parse(rawMatPriceStr);
                    int test3 = int.Parse(rawMatNumberStr);
                    double test = test2 * test3;

                    String strSQL2 = "INSERT INTO Orders (id_user, data_in,total_cost) VALUES (?, ?, ?)";
                    OleDbCommand cmdIC2 = new OleDbCommand(strSQL2, cn);
                    cmdIC2.Parameters.Add("@p1", OleDbType.Integer, 4);
                    cmdIC2.Parameters.Add("@p2", OleDbType.Date, 8);
                    cmdIC2.Parameters.Add("@p3", OleDbType.Double, 8);

                    cmdIC2.Parameters[0].Value = user_id;
                    cmdIC2.Parameters[1].Value = MyDateTime;
                    cmdIC2.Parameters[2].Value = test;
                    cmdIC2.ExecuteNonQuery();

                    String strSQL = "INSERT INTO Raw_In_Order (id_order, id_raw, number_to_buy, data_out) VALUES (?, ?, ?, ?)";
                    OleDbCommand cmdIC = new OleDbCommand(strSQL, cn);
                    cmdIC.Parameters.Add("@p1", OleDbType.Integer, 4);
                    cmdIC.Parameters.Add("@p2", OleDbType.Integer, 4);
                    cmdIC.Parameters.Add("@p3", OleDbType.Integer, 4);
                    cmdIC.Parameters.Add("@p4", OleDbType.Date, 8);

                    cmdIC.Parameters[0].Value = orderID;
                    cmdIC.Parameters[1].Value = dbIdInt;
                    cmdIC.Parameters[2].Value = int.Parse(rawMatNumberStr);
                    cmdIC.Parameters[3].Value = MyDateTime;

                    cmdIC.ExecuteNonQuery();
                }
            }

        }

        private void Stockman_FormClosing(object sender, FormClosingEventArgs e)
        {
            cn.Close();
        }
    }
}
