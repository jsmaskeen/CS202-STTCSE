namespace OrderPipeline
{
    partial class Form1
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
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
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            customer_name_textbox = new TextBox();
            cst_name_label = new Label();
            product_combobox = new ComboBox();
            product_label = new Label();
            qty_updown = new NumericUpDown();
            qtyLabel = new Label();
            btnProcessOrder = new Button();
            lblStatus = new Label();
            chkExpress = new CheckBox();
            btnShipOrder = new Button();
            ((System.ComponentModel.ISupportInitialize)qty_updown).BeginInit();
            SuspendLayout();
            // 
            // customer_name_textbox
            // 
            customer_name_textbox.Anchor = AnchorStyles.Top | AnchorStyles.Left | AnchorStyles.Right;
            customer_name_textbox.Location = new Point(161, 26);
            customer_name_textbox.Name = "customer_name_textbox";
            customer_name_textbox.Size = new Size(326, 23);
            customer_name_textbox.TabIndex = 0;
            customer_name_textbox.TextChanged += customer_name_textbox_TextChanged;
            // 
            // cst_name_label
            // 
            cst_name_label.AutoSize = true;
            cst_name_label.Location = new Point(31, 29);
            cst_name_label.Name = "cst_name_label";
            cst_name_label.Size = new Size(124, 15);
            cst_name_label.TabIndex = 1;
            cst_name_label.Text = "Enter Customer Name";
            cst_name_label.Click += label1_Click;
            // 
            // product_combobox
            // 
            product_combobox.FormattingEnabled = true;
            product_combobox.Items.AddRange(new object[] { "Laptop", "Mouse", "Keyboard" });
            product_combobox.Location = new Point(161, 55);
            product_combobox.Name = "product_combobox";
            product_combobox.Size = new Size(121, 23);
            product_combobox.TabIndex = 2;
            product_combobox.SelectedIndexChanged += comboBox1_SelectedIndexChanged;
            // 
            // product_label
            // 
            product_label.AutoSize = true;
            product_label.Location = new Point(63, 58);
            product_label.Name = "product_label";
            product_label.Size = new Size(92, 15);
            product_label.TabIndex = 3;
            product_label.Text = "Choose Product";
            // 
            // qty_updown
            // 
            qty_updown.Location = new Point(161, 84);
            qty_updown.Name = "qty_updown";
            qty_updown.Size = new Size(120, 23);
            qty_updown.TabIndex = 4;
            qty_updown.ValueChanged += qty_updown_ValueChanged;
            // 
            // qtyLabel
            // 
            qtyLabel.AutoSize = true;
            qtyLabel.Location = new Point(102, 86);
            qtyLabel.Name = "qtyLabel";
            qtyLabel.Size = new Size(53, 15);
            qtyLabel.TabIndex = 5;
            qtyLabel.Text = "Quantity";
            qtyLabel.Click += label3_Click;
            // 
            // btnProcessOrder
            // 
            btnProcessOrder.Location = new Point(248, 242);
            btnProcessOrder.Name = "btnProcessOrder";
            btnProcessOrder.Size = new Size(122, 23);
            btnProcessOrder.TabIndex = 6;
            btnProcessOrder.Text = "Process Order";
            btnProcessOrder.UseVisualStyleBackColor = true;
            btnProcessOrder.Click += btnProcessOrder_Click;
            // 
            // lblStatus
            // 
            lblStatus.AutoSize = true;
            lblStatus.Location = new Point(161, 145);
            lblStatus.Name = "lblStatus";
            lblStatus.Size = new Size(147, 15);
            lblStatus.TabIndex = 7;
            lblStatus.Text = "Waiting for User's Action...";
            // 
            // chkExpress
            // 
            chkExpress.AutoSize = true;
            chkExpress.Location = new Point(161, 113);
            chkExpress.Name = "chkExpress";
            chkExpress.Size = new Size(105, 19);
            chkExpress.TabIndex = 8;
            chkExpress.Text = "Express Order ?";
            chkExpress.UseVisualStyleBackColor = true;
            // 
            // btnShipOrder
            // 
            btnShipOrder.Location = new Point(376, 242);
            btnShipOrder.Name = "btnShipOrder";
            btnShipOrder.Size = new Size(111, 23);
            btnShipOrder.TabIndex = 9;
            btnShipOrder.Text = "Ship Order";
            btnShipOrder.UseVisualStyleBackColor = true;
            btnShipOrder.Click += btnShipOrder_Click;
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(499, 277);
            Controls.Add(btnShipOrder);
            Controls.Add(chkExpress);
            Controls.Add(lblStatus);
            Controls.Add(btnProcessOrder);
            Controls.Add(qtyLabel);
            Controls.Add(qty_updown);
            Controls.Add(product_label);
            Controls.Add(product_combobox);
            Controls.Add(cst_name_label);
            Controls.Add(customer_name_textbox);
            Name = "Form1";
            Text = "OrderPipeline";
            Load += Form1_Load;
            ((System.ComponentModel.ISupportInitialize)qty_updown).EndInit();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private TextBox customer_name_textbox;
        private Label cst_name_label;
        private ComboBox product_combobox;
        private Label product_label;
        private NumericUpDown qty_updown;
        private Label qtyLabel;
        private Button btnProcessOrder;
        private Label lblStatus;
        private CheckBox chkExpress;
        private Button btnShipOrder;
    }
}
