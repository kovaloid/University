using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Data.OleDb;
using System.Collections;

namespace beer_factory
{
    public partial class Client : Form
    {
        public int user_id = 0;
        private bool nextClick = false;
        private ArrayList orderArr = new ArrayList();

        public Client()
        {
            InitializeComponent();
            conn.Open();
            OleDbCommand IDS = new OleDbCommand("SELECT name FROM Production", conn);
            OleDbDataReader rdr = IDS.ExecuteReader();

            while (rdr.Read())
                comboBEER.Items.Add(rdr["name"]);
            rdr.Close();		
        }

        private void comboBEER_SelectedIndexChanged(object sender, EventArgs e)
        {
            String dbBeerName;
            OleDbCommand IDS = new OleDbCommand("SELECT name,price,id_beer FROM Production", conn);
            OleDbDataReader rdr = IDS.ExecuteReader();
            string beerPrice;
            int beerID = 0;
            String beer;
            beer = comboBEER.Text;
            beerPrice = "";

            while (rdr.Read())
            {
                dbBeerName = rdr.GetString(0);
                if (beer.CompareTo(dbBeerName) == 0)
                {
                    beerPrice = rdr.GetValue(1).ToString();
                    beerID = rdr.GetInt32(2);
                }
            }
            rdr.Close();
            Price.Text = beerPrice;
            if (nextClick)
            {
                ds.Tables["Raw_Materials"].Clear();
            }
            String strSQL = "SELECT name, proportion FROM Raw_Materials JOIN Composition " +
                            "ON Raw_Materials.id_raw = Composition.id_raw " +
                            "WHERE Composition.id_beer = " + beerID;
            dAdapter = new OleDbDataAdapter(strSQL, conn);
            dAdapter.Fill(ds, "Raw_Materials");
            dataGrid1.SetDataBinding(ds, "Raw_Materials");
            dRow = ds.Tables["Raw_Materials"].NewRow();
            nextClick = true;
        }

        class Order
        {
            public int OrderID;
            public int BeerID;
            public string beerName;
            public int numberBeer;
            public Order(int ID, int bID, string name, int number)
            {
                OrderID = ID;
                BeerID = bID;
                beerName = name;
                numberBeer = number;
            }
        }

        private void DrawTree()
        {
            treeView.BeginUpdate();
            treeView.Nodes.Clear();
            foreach (Order order1 in orderArr)
            {
                treeView.Nodes.Add(new TreeNode(order1.beerName + " -- " + order1.numberBeer));
            }
            treeView.EndUpdate();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            String numBeerStr = numberBEER.Text;
            bool exist = false;
            int numBeerInt = int.Parse(numBeerStr);
            String beer = comboBEER.Text;
            if (numBeerStr == "")
            {
                MessageBox.Show("Введите количество пива!");
            }
            else if (beer == "")
            {
                MessageBox.Show("Пожалуйста, выберите сорт пива!");
            }
            else
            {
                int dbID = 0;
                int dbBID = 0;
                foreach (Order order2 in orderArr)
                {
                    if (order2.beerName == beer)
                    {
                        exist = true;
                        order2.numberBeer += numBeerInt;
                    }
                }
                OleDbCommand IDS = new OleDbCommand("SELECT id_order FROM Orders", conn);
                OleDbDataReader rdr = IDS.ExecuteReader();
                try
                {
                    while (rdr.Read())
                    {
                        dbID = rdr.GetInt32(0);
                    }
                }
                finally
                {
                    rdr.Close();
                }

                OleDbCommand IDS2 = new OleDbCommand("SELECT id_beer,name FROM Production", conn);
                OleDbDataReader rdr2 = IDS2.ExecuteReader();
                try
                {
                    while (rdr2.Read())
                    {
                        String dbNameStr = rdr2.GetString(1); ;
                        if (beer.CompareTo(dbNameStr) == 0)
                        {
                            dbBID = rdr2.GetInt32(0);
                        }
                    }
                }
                finally
                {
                    rdr2.Close();
                }

                if (exist == false)
                {
                    orderArr.Add(new Order((dbID + 1), dbBID, beer, numBeerInt));
                }
                else
                {
                    exist = false;
                }
                DrawTree();
                numberBEER.Text = "";
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            String numBeerStr = numberBEER.Text;
            int numBeerInt = int.Parse(numBeerStr);
            if (numBeerStr == "")
            {
                MessageBox.Show("Введите количество пива для удаления из заказа!");
            }
            else
            {
                TreeNode node = treeView.SelectedNode;
                treeView.PathSeparator = ".";
                if (treeView.SelectedNode == null)
                {
                    MessageBox.Show("Вы не выбрали пиво для удаления!");
                }
                else
                {
                    foreach (Order order1 in orderArr)
                    {
                        if (node.FullPath == (order1.beerName + " -- " + order1.numberBeer))
                        {
                            if (order1.numberBeer <= numBeerInt)
                            {
                                orderArr.Remove(order1);
                                break;
                            }
                            else
                            {
                                order1.numberBeer -= numBeerInt;
                            }
                        }
                    }
                }
                DrawTree();
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            DateTime MyDateTime = DateTime.Today;
			double totalCost = 0;
			double price = 0;
			foreach(Order order1 in orderArr)
			{
				OleDbCommand IDS = new OleDbCommand("SELECT id_beer,price FROM Production", conn);
				OleDbDataReader rdr = IDS.ExecuteReader();
				try 
				{
					while (rdr.Read()) 
					{
						int dbID = rdr.GetInt32(0); 
						if (dbID.CompareTo(order1.BeerID)==0)
						{
							price = rdr.GetDouble(1);
							break;
						}
					}
				}
				finally 
				{
					rdr.Close();
				}
				totalCost +=price*order1.numberBeer;
			}
	
			String strSQL2 = "INSERT INTO Orders (id_user, data_in, total_cost) VALUES (?, ?, ?)";
			OleDbCommand cmdIC2 = new OleDbCommand(strSQL2, conn);
			cmdIC2.Parameters.Add("@p1", OleDbType.Integer, 4);
			cmdIC2.Parameters.Add("@p2", OleDbType.Date, 8);
			cmdIC2.Parameters.Add("@p3", OleDbType.Double, 8);
			foreach(Order order1 in orderArr)
			{
				cmdIC2.Parameters[0].Value = user_id;
				cmdIC2.Parameters[1].Value = MyDateTime;
				cmdIC2.Parameters[2].Value = totalCost;
				cmdIC2.ExecuteNonQuery();
				break;
			}
			String strSQL = "INSERT INTO Products_In_Order (id_order, id_beer, number_to_buy, status, data_out) VALUES (?, ?, ?, 0, ?)";
			OleDbCommand cmdIC = new OleDbCommand(strSQL, conn);
			cmdIC.Parameters.Add("@p1", OleDbType.Integer, 4);
			cmdIC.Parameters.Add("@p2", OleDbType.Integer, 4);
			cmdIC.Parameters.Add("@p3", OleDbType.Integer, 4);
			cmdIC.Parameters.Add("@p4", OleDbType.Date, 8);
			foreach(Order order1 in orderArr)
			{
				cmdIC.Parameters[0].Value = order1.OrderID;
				cmdIC.Parameters[1].Value = order1.BeerID;
				cmdIC.Parameters[2].Value = order1.numberBeer;
				cmdIC.Parameters[3].Value = null;
				cmdIC.ExecuteNonQuery();
			}
			numberBEER.Text = "";
			orderArr.Clear();
			DrawTree();
			MessageBox.Show("Конечная стоимость заказа: "+totalCost.ToString());
        }

        private void Client_FormClosing(object sender, FormClosingEventArgs e)
        {
            conn.Close();
        }

    }
}
