namespace beer_factory
{
    partial class Stockman
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
            this.btnChange = new System.Windows.Forms.Button();
            this.dataGrid1 = new System.Windows.Forms.DataGrid();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.button3 = new System.Windows.Forms.Button();
            this.txtBoxNumber = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.txtBoxName = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.tabPage3 = new System.Windows.Forms.TabPage();
            this.dataGrid3 = new System.Windows.Forms.DataGrid();
            this.button1 = new System.Windows.Forms.Button();
            this.txtBoxRawMatPrice = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.txtBoxRawMatNumber = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.txtBoxRawMatName = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.cn = new System.Data.OleDb.OleDbConnection();
            this.dsNumber = new System.Data.DataSet();
            this.dsNewRawMat = new System.Data.DataSet();
            this.tabControl1.SuspendLayout();
            this.tabPage1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGrid1)).BeginInit();
            this.tabPage2.SuspendLayout();
            this.tabPage3.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGrid3)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dsNumber)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dsNewRawMat)).BeginInit();
            this.SuspendLayout();
            // 
            // tabControl1
            // 
            this.tabControl1.Controls.Add(this.tabPage1);
            this.tabControl1.Controls.Add(this.tabPage2);
            this.tabControl1.Controls.Add(this.tabPage3);
            this.tabControl1.Location = new System.Drawing.Point(2, 1);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(802, 405);
            this.tabControl1.TabIndex = 0;
            // 
            // tabPage1
            // 
            this.tabPage1.Controls.Add(this.btnChange);
            this.tabPage1.Controls.Add(this.dataGrid1);
            this.tabPage1.Location = new System.Drawing.Point(4, 25);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage1.Size = new System.Drawing.Size(794, 376);
            this.tabPage1.TabIndex = 0;
            this.tabPage1.Text = "Выполнение заказа";
            this.tabPage1.UseVisualStyleBackColor = true;
            // 
            // btnChange
            // 
            this.btnChange.Location = new System.Drawing.Point(282, 339);
            this.btnChange.Name = "btnChange";
            this.btnChange.Size = new System.Drawing.Size(231, 27);
            this.btnChange.TabIndex = 2;
            this.btnChange.Text = "Подтвердить изменения";
            this.btnChange.Click += new System.EventHandler(this.btnChange_Click);
            // 
            // dataGrid1
            // 
            this.dataGrid1.CaptionVisible = false;
            this.dataGrid1.DataMember = "";
            this.dataGrid1.HeaderForeColor = System.Drawing.SystemColors.ControlText;
            this.dataGrid1.Location = new System.Drawing.Point(3, 3);
            this.dataGrid1.Name = "dataGrid1";
            this.dataGrid1.Size = new System.Drawing.Size(788, 330);
            this.dataGrid1.TabIndex = 1;
            // 
            // tabPage2
            // 
            this.tabPage2.Controls.Add(this.button3);
            this.tabPage2.Controls.Add(this.txtBoxNumber);
            this.tabPage2.Controls.Add(this.label2);
            this.tabPage2.Controls.Add(this.txtBoxName);
            this.tabPage2.Controls.Add(this.label1);
            this.tabPage2.Location = new System.Drawing.Point(4, 25);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage2.Size = new System.Drawing.Size(794, 376);
            this.tabPage2.TabIndex = 1;
            this.tabPage2.Text = "Пополнение продукции на складе";
            this.tabPage2.UseVisualStyleBackColor = true;
            // 
            // button3
            // 
            this.button3.Location = new System.Drawing.Point(267, 206);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(234, 27);
            this.button3.TabIndex = 9;
            this.button3.Text = "Подтвердить изменения";
            this.button3.Click += new System.EventHandler(this.button3_Click);
            // 
            // txtBoxNumber
            // 
            this.txtBoxNumber.Location = new System.Drawing.Point(217, 145);
            this.txtBoxNumber.Name = "txtBoxNumber";
            this.txtBoxNumber.Size = new System.Drawing.Size(327, 22);
            this.txtBoxNumber.TabIndex = 8;
            // 
            // label2
            // 
            this.label2.Location = new System.Drawing.Point(239, 115);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(291, 27);
            this.label2.TabIndex = 7;
            this.label2.Text = "Пожалуйста, введите количество пива.";
            // 
            // txtBoxName
            // 
            this.txtBoxName.Location = new System.Drawing.Point(217, 57);
            this.txtBoxName.Name = "txtBoxName";
            this.txtBoxName.Size = new System.Drawing.Size(327, 22);
            this.txtBoxName.TabIndex = 6;
            // 
            // label1
            // 
            this.label1.Location = new System.Drawing.Point(141, 26);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(486, 28);
            this.label1.TabIndex = 5;
            this.label1.Text = "Пожалуйста, напишите название пива, которое вы хотите пополнить.";
            // 
            // tabPage3
            // 
            this.tabPage3.Controls.Add(this.dataGrid3);
            this.tabPage3.Controls.Add(this.button1);
            this.tabPage3.Controls.Add(this.txtBoxRawMatPrice);
            this.tabPage3.Controls.Add(this.label5);
            this.tabPage3.Controls.Add(this.txtBoxRawMatNumber);
            this.tabPage3.Controls.Add(this.label4);
            this.tabPage3.Controls.Add(this.txtBoxRawMatName);
            this.tabPage3.Controls.Add(this.label3);
            this.tabPage3.Location = new System.Drawing.Point(4, 25);
            this.tabPage3.Name = "tabPage3";
            this.tabPage3.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage3.Size = new System.Drawing.Size(794, 376);
            this.tabPage3.TabIndex = 2;
            this.tabPage3.Text = "Пополнение сырья на складе";
            this.tabPage3.UseVisualStyleBackColor = true;
            // 
            // dataGrid3
            // 
            this.dataGrid3.CaptionVisible = false;
            this.dataGrid3.DataMember = "";
            this.dataGrid3.HeaderForeColor = System.Drawing.SystemColors.ControlText;
            this.dataGrid3.Location = new System.Drawing.Point(427, 24);
            this.dataGrid3.Name = "dataGrid3";
            this.dataGrid3.Size = new System.Drawing.Size(343, 325);
            this.dataGrid3.TabIndex = 10;
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(84, 310);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(229, 28);
            this.button1.TabIndex = 9;
            this.button1.Text = "Подтвердить изменения";
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // txtBoxRawMatPrice
            // 
            this.txtBoxRawMatPrice.Location = new System.Drawing.Point(31, 265);
            this.txtBoxRawMatPrice.Name = "txtBoxRawMatPrice";
            this.txtBoxRawMatPrice.Size = new System.Drawing.Size(327, 22);
            this.txtBoxRawMatPrice.TabIndex = 8;
            // 
            // label5
            // 
            this.label5.Location = new System.Drawing.Point(31, 224);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(330, 38);
            this.label5.TabIndex = 7;
            this.label5.Text = "Пожалуйста, напишите здесь цену на единицу сырья.";
            // 
            // txtBoxRawMatNumber
            // 
            this.txtBoxRawMatNumber.Location = new System.Drawing.Point(31, 154);
            this.txtBoxRawMatNumber.Name = "txtBoxRawMatNumber";
            this.txtBoxRawMatNumber.Size = new System.Drawing.Size(330, 22);
            this.txtBoxRawMatNumber.TabIndex = 6;
            // 
            // label4
            // 
            this.label4.Location = new System.Drawing.Point(31, 132);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(327, 28);
            this.label4.TabIndex = 5;
            this.label4.Text = "Пожалуйста, напишите количество сырья.";
            // 
            // txtBoxRawMatName
            // 
            this.txtBoxRawMatName.Location = new System.Drawing.Point(31, 64);
            this.txtBoxRawMatName.Name = "txtBoxRawMatName";
            this.txtBoxRawMatName.Size = new System.Drawing.Size(327, 22);
            this.txtBoxRawMatName.TabIndex = 4;
            // 
            // label3
            // 
            this.label3.Location = new System.Drawing.Point(31, 24);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(327, 37);
            this.label3.TabIndex = 3;
            this.label3.Text = "Пожалуйста, напишите здесь название сырья, которое вы хотите пополнить.";
            // 
            // cn
            // 
            this.cn.ConnectionString = ((string)(configurationAppSettings.GetValue("cn.ConnectionString", typeof(string))));
            // 
            // dsNumber
            // 
            this.dsNumber.DataSetName = "NewDataSet";
            this.dsNumber.Locale = new System.Globalization.CultureInfo("ru-RU");
            // 
            // dsNewRawMat
            // 
            this.dsNewRawMat.DataSetName = "NewDataSet";
            this.dsNewRawMat.Locale = new System.Globalization.CultureInfo("ru-RU");
            // 
            // Stockman
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(803, 407);
            this.Controls.Add(this.tabControl1);
            this.Name = "Stockman";
            this.Text = "Кладовщик";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Stockman_FormClosing);
            this.tabControl1.ResumeLayout(false);
            this.tabPage1.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.dataGrid1)).EndInit();
            this.tabPage2.ResumeLayout(false);
            this.tabPage2.PerformLayout();
            this.tabPage3.ResumeLayout(false);
            this.tabPage3.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGrid3)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.dsNumber)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.dsNewRawMat)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tabPage1;
        private System.Windows.Forms.TabPage tabPage2;
        private System.Windows.Forms.TabPage tabPage3;
        private System.Windows.Forms.Button btnChange;
        private System.Windows.Forms.DataGrid dataGrid1;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.TextBox txtBoxNumber;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox txtBoxName;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.DataGrid dataGrid3;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.TextBox txtBoxRawMatPrice;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox txtBoxRawMatNumber;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox txtBoxRawMatName;
        private System.Windows.Forms.Label label3;
        private System.Data.OleDb.OleDbConnection cn;
        private System.Data.DataSet dsNumber;
        private System.Data.DataSet dsNewRawMat;
        private System.Data.OleDb.OleDbDataAdapter dAdapter;
        private System.Data.DataRow dRow;
        private System.Data.OleDb.OleDbDataAdapter dAdapter3;
        private System.Data.DataRow dRow3;
    }
}