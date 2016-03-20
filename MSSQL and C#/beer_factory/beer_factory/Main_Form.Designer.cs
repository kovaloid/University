namespace beer_factory
{
    partial class Main_Form
    {
        /// <summary>
        /// Требуется переменная конструктора.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        /// <param name="disposing">истинно, если управляемый ресурс должен быть удален; иначе ложно.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Код, автоматически созданный конструктором форм Windows

        /// <summary>
        /// Обязательный метод для поддержки конструктора - не изменяйте
        /// содержимое данного метода при помощи редактора кода.
        /// </summary>
        private void InitializeComponent()
        {
            System.Configuration.AppSettingsReader configurationAppSettings = new System.Configuration.AppSettingsReader();
            this.label = new System.Windows.Forms.Label();
            this.username = new System.Windows.Forms.TextBox();
            this.password = new System.Windows.Forms.TextBox();
            this.OK_button = new System.Windows.Forms.Button();
            this.cn = new System.Data.OleDb.OleDbConnection();
            this.SuspendLayout();
            // 
            // label
            // 
            this.label.AutoSize = true;
            this.label.Location = new System.Drawing.Point(22, 22);
            this.label.Name = "label";
            this.label.Size = new System.Drawing.Size(287, 17);
            this.label.TabIndex = 0;
            this.label.Text = "Пожалуйста, введите ваш логин и пароль.";
            // 
            // username
            // 
            this.username.Location = new System.Drawing.Point(56, 54);
            this.username.Name = "username";
            this.username.Size = new System.Drawing.Size(217, 22);
            this.username.TabIndex = 1;
            // 
            // password
            // 
            this.password.Location = new System.Drawing.Point(56, 94);
            this.password.Name = "password";
            this.password.Size = new System.Drawing.Size(217, 22);
            this.password.TabIndex = 2;
            this.password.UseSystemPasswordChar = true;
            this.password.KeyDown += new System.Windows.Forms.KeyEventHandler(this.password_KeyDown);
            // 
            // OK_button
            // 
            this.OK_button.Location = new System.Drawing.Point(100, 136);
            this.OK_button.Name = "OK_button";
            this.OK_button.Size = new System.Drawing.Size(128, 41);
            this.OK_button.TabIndex = 3;
            this.OK_button.Text = "OK";
            this.OK_button.UseVisualStyleBackColor = true;
            this.OK_button.Click += new System.EventHandler(this.OK_button_Click);
            // 
            // cn
            // 
            this.cn.ConnectionString = ((string)(configurationAppSettings.GetValue("cn.ConnectionString", typeof(string))));
            // 
            // Main_Form
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(334, 205);
            this.Controls.Add(this.OK_button);
            this.Controls.Add(this.password);
            this.Controls.Add(this.username);
            this.Controls.Add(this.label);
            this.Name = "Main_Form";
            this.Text = "Вход в систему";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Main_Form_FormClosing);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label;
        private System.Windows.Forms.TextBox username;
        private System.Windows.Forms.TextBox password;
        private System.Windows.Forms.Button OK_button;
        private System.Data.OleDb.OleDbConnection cn;

        public Client childClient = new Client();
        public Manager childManager = new Manager();
        public Stockman childStockman = new Stockman();
        public NewClient childNewClient = new NewClient();
    }
}

