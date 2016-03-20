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
    public partial class Main_Form : Form
    {

        public Main_Form()
        {
            InitializeComponent();
            cn.Open();
        }

        private void OK_button_Click(object sender, EventArgs e)
        {
            int dbUserID = 0;
            int id_type = 0;
            String userLogin = "";
            String userPass = "";
            String dbLogin = "";
            String dbPass = "";

            userLogin = username.Text.ToLower();
            userPass = password.Text.ToLower();
            if (userPass.CompareTo("") == 0)
            {
                userPass = "NULL";
            }

            OleDbCommand IDS = new OleDbCommand("SELECT id_type,login,password,id_user FROM Users", cn);
            OleDbDataReader rdr = IDS.ExecuteReader();
            try
            {
                while (rdr.Read())
                {
                    dbLogin = rdr.GetString(1).ToLower().Trim();

                    if (userLogin.CompareTo(dbLogin) == 0)
                    {
                        dbPass = rdr.GetString(2).ToLower().Trim();
                        if (userPass.CompareTo(dbPass) == 0)
                        {
                            id_type = rdr.GetInt32(0);
                            dbUserID = rdr.GetInt32(3);
                        }
                    }
                }
            }
            finally
            {
                rdr.Close();
            }

            if (id_type == 1)
            {
                childManager.ShowDialog(this);
            }
            else if (id_type == 2)
            {
                childStockman.user_id = dbUserID;
                childStockman.ShowDialog(this);
            }
            else if (id_type == 3)
            {
                childClient.user_id = dbUserID;
                childClient.ShowDialog(this);
            }
            else
            {
                childNewClient.ShowDialog(this);
            }
        }

        private void password_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                OK_button_Click(sender, e);
            } 
        }

        private void Main_Form_FormClosing(object sender, FormClosingEventArgs e)
        {
            cn.Close();
        }

    }
}
