using System;
using System.Drawing;
using System.Windows.Forms;


namespace EventPlayground
{

    // Custom EventArgs class
    public class ColorChangedEventArgs : EventArgs
    {
        public Color NewColor { get; }
        public ColorChangedEventArgs(Color newColor)
        {
            NewColor = newColor;
        }
    }

    public class TextChangedEventArgs : EventArgs
    {
        public string NewText { get; }
        public TextChangedEventArgs(string newText)
        {
            NewText = newText;
        }
    }

    // Custom Delegates

    public delegate void ColorChangedEventHandler(ColorChangedEventArgs e);
    public delegate void TextChangedEventHandler(TextChangedEventArgs e);



    public class EventPlaygroundForm : Form
    {

        private Button btnChangeColor;
        private Button btnChangeText;
        private Label lblDisplay;
        private ComboBox cmbColors;

        private event ColorChangedEventHandler ColorChangedEvent;
        private event TextChangedEventHandler TextChangedEvent;

        public EventPlaygroundForm()

        {
            Text = "Event Playground";
            Size = new Size(420, 200);
            StartPosition = FormStartPosition.CenterScreen;
            InitializeControls();
            InitializeHandlers();
        }

        private void InitializeControls()
        {
            // Label
            lblDisplay = new Label
            {
                Text = "Welcome to Events Lab",
                AutoSize = false,
                TextAlign = ContentAlignment.MiddleCenter,
                Font = new Font("Segoe UI", 11f, FontStyle.Regular),
                Size = new Size(360, 40),
                Location = new Point(20, 15),
                ForeColor = Color.Black,
                BorderStyle = BorderStyle.FixedSingle
            };
            Controls.Add(lblDisplay);

            // ComboBox
            cmbColors = new ComboBox
            {
                Location = new Point(20, 70),
                Size = new Size(120, 24),
                DropDownStyle = ComboBoxStyle.DropDownList
            };
            cmbColors.Items.AddRange(new object[] { "Red", "Green", "Blue" });
            cmbColors.SelectedIndex = 0;
            Controls.Add(cmbColors);

            // Buttons
            btnChangeColor = new Button
            {
                Text = "Change Color",
                Location = new Point(160, 68),
                Size = new Size(100, 28)
            };
            Controls.Add(btnChangeColor);

            btnChangeText = new Button
            {
                Text = "Change Text",
                Location = new Point(280, 68),
                Size = new Size(100, 28)
            };
            Controls.Add(btnChangeText);
        }

        private void InitializeHandlers()
        {
            // Subscribe to events
            ColorChangedEvent += OnColorChanged;
            ColorChangedEvent += NotifyColorChange;
            TextChangedEvent += OnTextChanged;

            // Button Click Events
            btnChangeColor.Click += (s, e) =>
            {
                Color selectedColor = cmbColors?.SelectedItem?.ToString() switch
                {
                    "Red" => Color.Red,
                    "Green" => Color.Green,
                    "Blue" => Color.Blue,
                    _ => Color.Black
                };

                ColorChangedEvent?.Invoke(new ColorChangedEventArgs(selectedColor));
            };
            btnChangeText.Click += (s, e) =>
            {
                string newText = DateTime.Now.ToString("F");
                TextChangedEvent?.Invoke(new TextChangedEventArgs(newText));
            };
        }

        private void OnColorChanged(ColorChangedEventArgs e)
        {
            lblDisplay.ForeColor = e.NewColor;
        }
        private void OnTextChanged(TextChangedEventArgs e)
        {
            lblDisplay.Text = e.NewText;
        }
        private void NotifyColorChange(ColorChangedEventArgs e)
        {
            MessageBox.Show($"The colour has changed to {e.NewColor.Name}", "Colour Changed!", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }
    }

    internal static class Program
    {
        /// <summary>
        ///  The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            // To customize application configuration such as set high DPI settings or default font,
            // see https://aka.ms/applicationconfiguration.
            ApplicationConfiguration.Initialize();
            Application.Run(new EventPlaygroundForm());
        }
    }
}