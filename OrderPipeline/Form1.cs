using System;
using System.Windows.Forms;

namespace OrderPipeline
{
    public partial class Form1 : Form
    {
        ProcessOrder worker = new ProcessOrder();
        public Form1()
        {
            InitializeComponent();
            subscribe_events();

        }
        private void subscribe_events()
        {
            worker.OrderCreated += DisplayOrderInfo;
            worker.OrderConfirmed += ShowConfirmation;
            worker.OrderRejected += ShowRejection;
            worker.OrderShipped += ShowDispatch;
        }
        private void DisplayOrderInfo(object sender, ShipEventArgs e)
        {
            MessageBox.Show($"Processing order for {e.Product}. Express: {e.Express}");
        }
        private void ShowConfirmation(object sender, ShipEventArgs e)
        {
            lblStatus.Text = $"Order Processed (and Validated) Successfully for {customer_name_textbox.Text}";
        }
        private void ShowRejection(object sender, EventArgs e)
        {
            lblStatus.Text = "Order Invalid - Please retry";
        }
        private void ShowDispatch(object sender, ShipEventArgs e)
        {
            lblStatus.Text = $"Product dispatched: [{e.Product}]";
        }

        private void NotifyCourier(object sender, ShipEventArgs e)
        {
            if (e.Express)
            {
                MessageBox.Show("Express delivery initiated!");
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void label3_Click(object sender, EventArgs e)
        {

        }

        private void btnProcessOrder_Click(object sender, EventArgs e)
        {
            string product = product_combobox.SelectedItem?.ToString() ?? "Unknown";
            int quantity = (int)qty_updown.Value;
            bool is_order_express = chkExpress.Checked;

            worker.CreateOrder(product, quantity, is_order_express);
        }

        private void customer_name_textbox_TextChanged(object sender, EventArgs e)
        {

        }

        private void btnShipOrder_Click(object sender, EventArgs e)
        {
            string product = product_combobox.SelectedItem?.ToString() ?? "Unknown";
            bool is_order_express = chkExpress.Checked;
            worker.OrderShipped -= NotifyCourier;
            // Ensure no duplicate subscriptions so that multiple clicks dont show multiple messages.
            if (is_order_express)
            {
                worker.OrderShipped += NotifyCourier;
            }
            else
            {
                worker.OrderShipped -= NotifyCourier;
            }
            worker.ShipOrder(product, is_order_express);
        }

        private void qty_updown_ValueChanged(object sender, EventArgs e)
        {

        }
    }

    public class ShipEventArgs : EventArgs
    {
        public string Product
        {
            get;
        }
        public bool Express
        {
            get;
        }
        public ShipEventArgs(string p, bool ex) => (Product, Express) = (p, ex);
    }

    public class ProcessOrder
    {
        public delegate void ShipEventHandler(object sender, ShipEventArgs e);
        public delegate void OrderStatusHandler(object sender, EventArgs e);

        public event ShipEventHandler OrderCreated;
        public event ShipEventHandler OrderConfirmed;
        public event OrderStatusHandler OrderRejected;
        public event ShipEventHandler OrderShipped;

        private bool is_order_cnf = false;
        private int _qt = 0;

        public ProcessOrder()
        {
            this.OrderCreated += ValidateOrder;
        }

        public void CreateOrder(string product, int quantity, bool express)
        {
            _qt = quantity;
            ShipEventArgs args = new ShipEventArgs(product, express);
            OrderCreated?.Invoke(this, args);
        }

        private void ValidateOrder(object sender, ShipEventArgs e)
        {
            if (_qt > 0)
            {
                is_order_cnf = true;
                OrderConfirmed?.Invoke(this, e);
            }
            else
            {
                is_order_cnf = false;
                OrderRejected?.Invoke(this, EventArgs.Empty);
            }
        }
        public void ShipOrder(string product, bool express)
        {
            if (is_order_cnf)
            {
                ShipEventArgs args = new ShipEventArgs(product, express);
                OrderShipped?.Invoke(this, args);
            }
            else
            {
                MessageBox.Show("Please process order first.");
            }
        }

    }
}