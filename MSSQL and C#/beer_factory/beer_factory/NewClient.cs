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
    public partial class NewClient : Form
    {
        public NewClient()
        {
            InitializeComponent();
            cn.Open();
        }

        private void OK_button_Click(object sender, EventArgs e)
        {
            bool somethingWrong = false;
            String fio = userFIO.Text;
            String company = userCompany.Text;
            String login = userLogin.Text;
            String password = userPass.Text;
            if (fio == "" & company == "" & login == "")
            {
                Close();
            }
            else if ((fio != "") & (company != "") & (login != ""))
            {
                OleDbCommand IDS = new OleDbCommand("SELECT id_user,fio,company,login FROM Users WHERE id_type = 3", cn);
                OleDbDataReader rdr = IDS.ExecuteReader();
                while (rdr.Read())
                {
                    if ((fio.ToLower() == rdr.GetString(1).ToLower()) & (company.ToLower() == rdr.GetString(2).ToLower()))
                    {
                        MessageBox.Show("Мы имеем такого клиента!");
                        somethingWrong = true;
                    }
                    if (login.ToLower() == rdr.GetString(3))
                    {
                        MessageBox.Show("Такой логин уже есть в базе данных!");
                        somethingWrong = true;
                    }
                }
                rdr.Close();
                if (!somethingWrong)
                {
                    String strSQL = "INSERT INTO Users (fio,company, " +
                        "id_type,login,password) VALUES (?, ?, ?, ?, ?)";
                    OleDbCommand cmdIC = new OleDbCommand(strSQL, cn);

                    cmdIC.Parameters.Add("@p1", System.Data.OleDb.OleDbType.VarChar, 50);
                    cmdIC.Parameters.Add("@p2", System.Data.OleDb.OleDbType.VarChar, 50);
                    cmdIC.Parameters.Add("@p3", System.Data.OleDb.OleDbType.Integer, 4);
                    cmdIC.Parameters.Add("@p4", System.Data.OleDb.OleDbType.VarChar, 20);
                    cmdIC.Parameters.Add("@p5", System.Data.OleDb.OleDbType.VarChar, 20);

                    cmdIC.Parameters[0].Value = fio;
                    cmdIC.Parameters[1].Value = company;
                    cmdIC.Parameters[2].Value = 3;
                    cmdIC.Parameters[3].Value = login;
                    cmdIC.Parameters[4].Value = password;
                    try
                    {
                        cmdIC.ExecuteNonQuery();
                    }
                    catch (System.Data.OleDb.OleDbException exc)
                    {
                        MessageBox.Show(exc.ToString());
                    }
                    Close();
                }
            }
            else
            {
                MessageBox.Show("Заполните или очистите все поля!");
            }
        }

        private void NewClient_FormClosing(object sender, FormClosingEventArgs e)
        {
            cn.Close();
        }

        private void userPass_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                OK_button_Click(sender, e);
            } 
        }
    }
}
