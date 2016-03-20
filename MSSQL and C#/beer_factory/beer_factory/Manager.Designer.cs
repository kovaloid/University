namespace beer_factory
{
    partial class Manager
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
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.dateTimePicker1 = new System.Windows.Forms.DateTimePicker();
            this.label1 = new System.Windows.Forms.Label();
            this.fio_field = new System.Windows.Forms.TextBox();
            this.FindName_button = new System.Windows.Forms.Button();
            this.FindPeriod1_button = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.ALL1_button = new System.Windows.Forms.Button();
            this.dataGrid1 = new System.Windows.Forms.DataGrid();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.dateTimePicker2 = new System.Windows.Forms.DateTimePicker();
            this.ALL2_button = new System.Windows.Forms.Button();
            this.FindPeriod2_button = new System.Windows.Forms.Button();
            this.label3 = new System.Windows.Forms.Label();
            this.dataGrid2 = new System.Windows.Forms.DataGrid();
            this.tabPage3 = new System.Windows.Forms.TabPage();
            this.button2 = new System.Windows.Forms.Button();
            this.button1 = new System.Windows.Forms.Button();
            this.dataGrid3 = new System.Windows.Forms.DataGrid();
            this.cn = new System.Data.OleDb.OleDbConnection();
            this.ds1 = new System.Data.DataSet();
            this.ds2 = new System.Data.DataSet();
            this.ds3 = new System.Data.DataSet();
            this.dataGrid4 = new System.Windows.Forms.DataGrid();
            this.button3 = new System.Windows.Forms.Button();
            this.ds4 = new System.Data.DataSet();
            this.tabControl1.SuspendLayout();
            this.tabPage1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGrid1)).BeginInit();
            this.tabPage2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGrid2)).BeginInit();
            this.tabPage3.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGrid3)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.ds1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.ds2)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.ds3)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataGrid4)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.ds4)).BeginInit();
            this.SuspendLayout();
            // 
            // tabControl1
            // 
            this.tabControl1.Controls.Add(this.tabPage1);
            this.tabControl1.Controls.Add(this.tabPage2);
            this.tabControl1.Controls.Add(this.tabPage3);
            this.tabControl1.Location = new System.Drawing.Point(3, 3);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(857, 485);
            this.tabControl1.TabIndex = 0;
            // 
            // tabPage1
            // 
            this.tabPage1.Controls.Add(this.dateTimePicker1);
            this.tabPage1.Controls.Add(this.label1);
            this.tabPage1.Controls.Add(this.fio_field);
            this.tabPage1.Controls.Add(this.FindName_button);
            this.tabPage1.Controls.Add(this.FindPeriod1_button);
            this.tabPage1.Controls.Add(this.label2);
            this.tabPage1.Controls.Add(this.ALL1_button);
            this.tabPage1.Controls.Add(this.dataGrid1);
            this.tabPage1.Location = new System.Drawing.Point(4, 25);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage1.Size = new System.Drawing.Size(849, 456);
            this.tabPage1.TabIndex = 0;
            this.tabPage1.Text = "Заказ продукции";
            this.tabPage1.UseVisualStyleBackColor = true;
            // 
            // dateTimePicker1
            // 
            this.dateTimePicker1.Location = new System.Drawing.Point(394, 406);
            this.dateTimePicker1.Name = "dateTimePicker1";
            this.dateTimePicker1.Size = new System.Drawing.Size(219, 22);
            this.dateTimePicker1.TabIndex = 9;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(347, 372);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(310, 17);
            this.label1.TabIndex = 8;
            this.label1.Text = "Установите начальную дату создания заказа";
            // 
            // fio_field
            // 
            this.fio_field.Location = new System.Drawing.Point(21, 406);
            this.fio_field.Name = "fio_field";
            this.fio_field.Size = new System.Drawing.Size(201, 22);
            this.fio_field.TabIndex = 7;
            // 
            // FindName_button
            // 
            this.FindName_button.Location = new System.Drawing.Point(242, 366);
            this.FindName_button.Name = "FindName_button";
            this.FindName_button.Size = new System.Drawing.Size(72, 73);
            this.FindName_button.TabIndex = 6;
            this.FindName_button.Text = "Найти по имени";
            this.FindName_button.UseVisualStyleBackColor = true;
            this.FindName_button.Click += new System.EventHandler(this.FindName_button_Click);
            // 
            // FindPeriod1_button
            // 
            this.FindPeriod1_button.Location = new System.Drawing.Point(675, 366);
            this.FindPeriod1_button.Name = "FindPeriod1_button";
            this.FindPeriod1_button.Size = new System.Drawing.Size(69, 73);
            this.FindPeriod1_button.TabIndex = 0;
            this.FindPeriod1_button.Text = "Найти за период";
            this.FindPeriod1_button.UseVisualStyleBackColor = true;
            this.FindPeriod1_button.Click += new System.EventHandler(this.FindPeriod1_button_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(40, 372);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(163, 17);
            this.label2.TabIndex = 4;
            this.label2.Text = "Напишите имя клиента";
            // 
            // ALL1_button
            // 
            this.ALL1_button.Location = new System.Drawing.Point(766, 366);
            this.ALL1_button.Name = "ALL1_button";
            this.ALL1_button.Size = new System.Drawing.Size(65, 73);
            this.ALL1_button.TabIndex = 0;
            this.ALL1_button.Text = "ВСЕ";
            this.ALL1_button.UseVisualStyleBackColor = true;
            this.ALL1_button.Click += new System.EventHandler(this.ALL1_button_Click);
            // 
            // dataGrid1
            // 
            this.dataGrid1.CaptionVisible = false;
            this.dataGrid1.DataMember = "";
            this.dataGrid1.HeaderForeColor = System.Drawing.SystemColors.ControlText;
            this.dataGrid1.Location = new System.Drawing.Point(6, 6);
            this.dataGrid1.Name = "dataGrid1";
            this.dataGrid1.Size = new System.Drawing.Size(840, 346);
            this.dataGrid1.TabIndex = 1;
            // 
            // tabPage2
            // 
            this.tabPage2.Controls.Add(this.dateTimePicker2);
            this.tabPage2.Controls.Add(this.ALL2_button);
            this.tabPage2.Controls.Add(this.FindPeriod2_button);
            this.tabPage2.Controls.Add(this.label3);
            this.tabPage2.Controls.Add(this.dataGrid2);
            this.tabPage2.Location = new System.Drawing.Point(4, 25);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage2.Size = new System.Drawing.Size(849, 456);
            this.tabPage2.TabIndex = 1;
            this.tabPage2.Text = "Заказ сырья";
            this.tabPage2.UseVisualStyleBackColor = true;
            // 
            // dateTimePicker2
            // 
            this.dateTimePicker2.Location = new System.Drawing.Point(203, 407);
            this.dateTimePicker2.Name = "dateTimePicker2";
            this.dateTimePicker2.Size = new System.Drawing.Size(211, 22);
            this.dateTimePicker2.TabIndex = 5;
            // 
            // ALL2_button
            // 
            this.ALL2_button.Location = new System.Drawing.Point(612, 372);
            this.ALL2_button.Name = "ALL2_button";
            this.ALL2_button.Size = new System.Drawing.Size(90, 73);
            this.ALL2_button.TabIndex = 4;
            this.ALL2_button.Text = "ВСЕ";
            this.ALL2_button.UseVisualStyleBackColor = true;
            this.ALL2_button.Click += new System.EventHandler(this.ALL2_button_Click);
            // 
            // FindPeriod2_button
            // 
            this.FindPeriod2_button.Location = new System.Drawing.Point(487, 372);
            this.FindPeriod2_button.Name = "FindPeriod2_button";
            this.FindPeriod2_button.Size = new System.Drawing.Size(93, 73);
            this.FindPeriod2_button.TabIndex = 3;
            this.FindPeriod2_button.Text = "Найти за период";
            this.FindPeriod2_button.UseVisualStyleBackColor = true;
            this.FindPeriod2_button.Click += new System.EventHandler(this.FindPeriod2_button_Click);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(149, 381);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(310, 17);
            this.label3.TabIndex = 2;
            this.label3.Text = "Установите начальную дату создания заказа";
            // 
            // dataGrid2
            // 
            this.dataGrid2.CaptionVisible = false;
            this.dataGrid2.DataMember = "";
            this.dataGrid2.HeaderForeColor = System.Drawing.SystemColors.ControlText;
            this.dataGrid2.Location = new System.Drawing.Point(6, 6);
            this.dataGrid2.Name = "dataGrid2";
            this.dataGrid2.Size = new System.Drawing.Size(837, 346);
            this.dataGrid2.TabIndex = 1;
            // 
            // tabPage3
            // 
            this.tabPage3.Controls.Add(this.button3);
            this.tabPage3.Controls.Add(this.dataGrid4);
            this.tabPage3.Controls.Add(this.button2);
            this.tabPage3.Controls.Add(this.button1);
            this.tabPage3.Controls.Add(this.dataGrid3);
            this.tabPage3.Location = new System.Drawing.Point(4, 25);
            this.tabPage3.Name = "tabPage3";
            this.tabPage3.Size = new System.Drawing.Size(849, 456);
            this.tabPage3.TabIndex = 0;
            this.tabPage3.Text = "Статистика";
            this.tabPage3.UseVisualStyleBackColor = true;
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(566, 365);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(166, 69);
            this.button2.TabIndex = 4;
            this.button2.Text = "Самые популярные сорта пива";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(118, 365);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(162, 69);
            this.button1.TabIndex = 3;
            this.button1.Text = "Клиенты, купившие больше одного сорта пива";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // dataGrid3
            // 
            this.dataGrid3.CaptionVisible = false;
            this.dataGrid3.DataMember = "";
            this.dataGrid3.HeaderForeColor = System.Drawing.SystemColors.ControlText;
            this.dataGrid3.Location = new System.Drawing.Point(5, 3);
            this.dataGrid3.Name = "dataGrid3";
            this.dataGrid3.Size = new System.Drawing.Size(417, 346);
            this.dataGrid3.TabIndex = 2;
            // 
            // cn
            // 
            this.cn.ConnectionString = ((string)(configurationAppSettings.GetValue("cn.ConnectionString", typeof(string))));
            // 
            // ds1
            // 
            this.ds1.DataSetName = "ds";
            this.ds1.Locale = new System.Globalization.CultureInfo("ru-RU");
            // 
            // ds2
            // 
            this.ds2.DataSetName = "ds2";
            this.ds2.Locale = new System.Globalization.CultureInfo("ru-RU");
            // 
            // ds3
            // 
            this.ds3.DataSetName = "ds3";
            this.ds3.Locale = new System.Globalization.CultureInfo("ru-RU");
            // 
            // dataGrid4
            // 
            this.dataGrid4.CaptionVisible = false;
            this.dataGrid4.DataMember = "";
            this.dataGrid4.HeaderForeColor = System.Drawing.SystemColors.ControlText;
            this.dataGrid4.Location = new System.Drawing.Point(429, 3);
            this.dataGrid4.Name = "dataGrid4";
            this.dataGrid4.Size = new System.Drawing.Size(417, 346);
            this.dataGrid4.TabIndex = 5;
            // 
            // button3
            // 
            this.button3.Location = new System.Drawing.Point(343, 365);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(160, 69);
            this.button3.TabIndex = 6;
            this.button3.Text = "Очистить";
            this.button3.UseVisualStyleBackColor = true;
            this.button3.Click += new System.EventHandler(this.button3_Click);
            // 
            // ds4
            // 
            this.ds4.DataSetName = "ds4";
            this.ds4.Locale = new System.Globalization.CultureInfo("ru-RU");
            // 
            // Manager
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(861, 492);
            this.Controls.Add(this.tabControl1);
            this.Name = "Manager";
            this.Text = "Менеджер";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Manager_FormClosing);
            this.tabControl1.ResumeLayout(false);
            this.tabPage1.ResumeLayout(false);
            this.tabPage1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGrid1)).EndInit();
            this.tabPage2.ResumeLayout(false);
            this.tabPage2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGrid2)).EndInit();
            this.tabPage3.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.dataGrid3)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.ds1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.ds2)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.ds3)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataGrid4)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.ds4)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tabPage1;
        private System.Windows.Forms.TabPage tabPage2;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button FindPeriod1_button;
        private System.Windows.Forms.Button ALL1_button;
        private System.Data.OleDb.OleDbConnection cn;
        private System.Windows.Forms.DataGrid dataGrid1;
        private System.Windows.Forms.DataGrid dataGrid2;
        private System.Data.DataSet ds1;
        private System.Data.DataSet ds2;
        private System.Data.DataRow dRow1;
        private System.Data.DataRow dRow2;
        private System.Data.OleDb.OleDbDataAdapter dAdapter1;
        private System.Data.OleDb.OleDbDataAdapter dAdapter2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox fio_field;
        private System.Windows.Forms.Button FindName_button;
        private System.Windows.Forms.Button ALL2_button;
        private System.Windows.Forms.Button FindPeriod2_button;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.DateTimePicker dateTimePicker1;
        private System.Windows.Forms.DateTimePicker dateTimePicker2;
        private System.Windows.Forms.TabPage tabPage3;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.DataGrid dataGrid3;
        private System.Data.DataSet ds3;
        private System.Data.DataRow dRow3;
        private System.Data.OleDb.OleDbDataAdapter dAdapter3;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.DataGrid dataGrid4;
        private System.Data.DataSet ds4;
        private System.Data.DataRow dRow4;
        private System.Data.OleDb.OleDbDataAdapter dAdapter4;
    }
}