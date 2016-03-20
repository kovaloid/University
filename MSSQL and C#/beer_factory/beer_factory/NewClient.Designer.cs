namespace beer_factory
{
    partial class NewClient
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.Configuration.AppSettingsReader configurationAppSettings = new System.Configuration.AppSettingsReader();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.userFIO = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.userCompany = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.userLogin = new System.Windows.Forms.TextBox();
            this.OK_button = new System.Windows.Forms.Button();
            this.cn = new System.Data.OleDb.OleDbConnection();
            this.userPass = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.Location = new System.Drawing.Point(23, 20);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(371, 63);
            this.label1.TabIndex = 0;
            this.label1.Text = "Мы не имеем такую комбинацию логина и пароля. Попробуйте проверить эти поля, или " +
    "же вы можете создать нового клиента.";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(123, 96);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(168, 17);
            this.label2.TabIndex = 1;
            this.label2.Text = "Фамилия Имя Отчество";
            // 
            // userFIO
            // 
            this.userFIO.Location = new System.Drawing.Point(49, 125);
            this.userFIO.Name = "userFIO";
            this.userFIO.Size = new System.Drawing.Size(314, 22);
            this.userFIO.TabIndex = 2;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(170, 162);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(74, 17);
            this.label3.TabIndex = 3;
            this.label3.Text = "Компания";
            // 
            // userCompany
            // 
            this.userCompany.Location = new System.Drawing.Point(49, 182);
            this.userCompany.Name = "userCompany";
            this.userCompany.Size = new System.Drawing.Size(314, 22);
            this.userCompany.TabIndex = 4;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(167, 220);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(77, 17);
            this.label4.TabIndex = 5;
            this.label4.Text = "Ваш логин";
            // 
            // userLogin
            // 
            this.userLogin.Location = new System.Drawing.Point(49, 240);
            this.userLogin.Name = "userLogin";
            this.userLogin.Size = new System.Drawing.Size(314, 22);
            this.userLogin.TabIndex = 6;
            // 
            // OK_button
            // 
            this.OK_button.Location = new System.Drawing.Point(140, 360);
            this.OK_button.Name = "OK_button";
            this.OK_button.Size = new System.Drawing.Size(125, 45);
            this.OK_button.TabIndex = 7;
            this.OK_button.Text = "OK";
            this.OK_button.UseVisualStyleBackColor = true;
            this.OK_button.Click += new System.EventHandler(this.OK_button_Click);
            // 
            // cn
            // 
            this.cn.ConnectionString = ((string)(configurationAppSettings.GetValue("cn.ConnectionString", typeof(string))));
            // 
            // userPass
            // 
            this.userPass.Location = new System.Drawing.Point(49, 305);
            this.userPass.Name = "userPass";
            this.userPass.Size = new System.Drawing.Size(314, 22);
            this.userPass.TabIndex = 8;
            this.userPass.KeyDown += new System.Windows.Forms.KeyEventHandler(this.userPass_KeyDown);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(167, 285);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(87, 17);
            this.label5.TabIndex = 9;
            this.label5.Text = "Ваш пароль";
            // 
            // NewClient
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(420, 437);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.userPass);
            this.Controls.Add(this.OK_button);
            this.Controls.Add(this.userLogin);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.userCompany);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.userFIO);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Name = "NewClient";
            this.Text = "Регистрация";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.NewClient_FormClosing);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox userFIO;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox userCompany;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox userLogin;
        private System.Windows.Forms.Button OK_button;
        private System.Data.OleDb.OleDbConnection cn;
        private System.Windows.Forms.TextBox userPass;
        private System.Windows.Forms.Label label5;
    }
}