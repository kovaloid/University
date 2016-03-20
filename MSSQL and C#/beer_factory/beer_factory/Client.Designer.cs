namespace beer_factory
{
    partial class Client
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
            this.conn = new System.Data.OleDb.OleDbConnection();
            this.ds = new System.Data.DataSet();
            this.treeView = new System.Windows.Forms.TreeView();
            this.button3 = new System.Windows.Forms.Button();
            this.label5 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.numberBEER = new System.Windows.Forms.TextBox();
            this.Price = new System.Windows.Forms.TextBox();
            this.dataGrid1 = new System.Windows.Forms.DataGrid();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.button2 = new System.Windows.Forms.Button();
            this.button1 = new System.Windows.Forms.Button();
            this.comboBEER = new System.Windows.Forms.ComboBox();
            ((System.ComponentModel.ISupportInitialize)(this.ds)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataGrid1)).BeginInit();
            this.SuspendLayout();
            // 
            // conn
            // 
            this.conn.ConnectionString = ((string)(configurationAppSettings.GetValue("conn.ConnectionString", typeof(string))));
            // 
            // ds
            // 
            this.ds.DataSetName = "ds";
            this.ds.Locale = new System.Globalization.CultureInfo("ru-RU");
            // 
            // treeView
            // 
            this.treeView.Location = new System.Drawing.Point(11, 391);
            this.treeView.Name = "treeView";
            this.treeView.Size = new System.Drawing.Size(567, 157);
            this.treeView.TabIndex = 27;
            // 
            // button3
            // 
            this.button3.Location = new System.Drawing.Point(387, 332);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(191, 35);
            this.button3.TabIndex = 26;
            this.button3.Text = "OK";
            this.button3.Click += new System.EventHandler(this.button3_Click);
            // 
            // label5
            // 
            this.label5.Location = new System.Drawing.Point(12, 142);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(163, 19);
            this.label5.TabIndex = 25;
            this.label5.Text = "Состав";
            // 
            // label4
            // 
            this.label4.Location = new System.Drawing.Point(12, 370);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(202, 18);
            this.label4.TabIndex = 24;
            this.label4.Text = "Ваш заказ";
            // 
            // label3
            // 
            this.label3.Location = new System.Drawing.Point(12, 291);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(231, 38);
            this.label3.TabIndex = 23;
            this.label3.Text = "Количество пива для покупки или для удаления из заказа";
            // 
            // numberBEER
            // 
            this.numberBEER.Location = new System.Drawing.Point(12, 332);
            this.numberBEER.Name = "numberBEER";
            this.numberBEER.Size = new System.Drawing.Size(231, 22);
            this.numberBEER.TabIndex = 22;
            // 
            // Price
            // 
            this.Price.Location = new System.Drawing.Point(12, 109);
            this.Price.Name = "Price";
            this.Price.ReadOnly = true;
            this.Price.Size = new System.Drawing.Size(231, 22);
            this.Price.TabIndex = 18;
            this.Price.Text = "0";
            // 
            // dataGrid1
            // 
            this.dataGrid1.CaptionVisible = false;
            this.dataGrid1.DataMember = "";
            this.dataGrid1.HeaderForeColor = System.Drawing.SystemColors.ControlText;
            this.dataGrid1.Location = new System.Drawing.Point(12, 164);
            this.dataGrid1.Name = "dataGrid1";
            this.dataGrid1.Size = new System.Drawing.Size(346, 111);
            this.dataGrid1.TabIndex = 21;
            // 
            // label2
            // 
            this.label2.Location = new System.Drawing.Point(12, 22);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(182, 19);
            this.label2.TabIndex = 20;
            this.label2.Text = "Выберите сорт пива...";
            // 
            // label1
            // 
            this.label1.Location = new System.Drawing.Point(12, 88);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(163, 18);
            this.label1.TabIndex = 19;
            this.label1.Text = "Стоимость (1 бутылки)";
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(387, 219);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(192, 37);
            this.button2.TabIndex = 17;
            this.button2.Text = "Удалить из заказа";
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(387, 173);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(192, 37);
            this.button1.TabIndex = 16;
            this.button1.Text = "Добавить к заказу";
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // comboBEER
            // 
            this.comboBEER.Location = new System.Drawing.Point(12, 44);
            this.comboBEER.Name = "comboBEER";
            this.comboBEER.Size = new System.Drawing.Size(231, 24);
            this.comboBEER.TabIndex = 15;
            this.comboBEER.SelectedIndexChanged += new System.EventHandler(this.comboBEER_SelectedIndexChanged);
            // 
            // Client
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(590, 564);
            this.Controls.Add(this.treeView);
            this.Controls.Add(this.button3);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.numberBEER);
            this.Controls.Add(this.Price);
            this.Controls.Add(this.dataGrid1);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.comboBEER);
            this.Name = "Client";
            this.Text = "Клиент";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Client_FormClosing);
            ((System.ComponentModel.ISupportInitialize)(this.ds)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataGrid1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Data.OleDb.OleDbConnection conn;
        private System.Data.DataSet ds;
        private System.Windows.Forms.TreeView treeView;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox numberBEER;
        private System.Windows.Forms.TextBox Price;
        private System.Windows.Forms.DataGrid dataGrid1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.ComboBox comboBEER;
        private System.Data.DataRow dRow;
        private System.Data.OleDb.OleDbDataAdapter dAdapter;
    }
}