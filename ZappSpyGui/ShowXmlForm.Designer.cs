namespace ZapSpyGui
{
    partial class ShowXmlForm
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
            this.iWebBrowser = new System.Windows.Forms.WebBrowser();
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.iTextBox = new System.Windows.Forms.TextBox();
            this.tabControl1.SuspendLayout();
            this.tabPage1.SuspendLayout();
            this.tabPage2.SuspendLayout();
            this.SuspendLayout();
            // 
            // iWebBrowser
            // 
            this.iWebBrowser.Dock = System.Windows.Forms.DockStyle.Fill;
            this.iWebBrowser.Location = new System.Drawing.Point(3, 3);
            this.iWebBrowser.MinimumSize = new System.Drawing.Size(20, 20);
            this.iWebBrowser.Name = "iWebBrowser";
            this.iWebBrowser.Size = new System.Drawing.Size(742, 436);
            this.iWebBrowser.TabIndex = 0;
            // 
            // tabControl1
            // 
            this.tabControl1.Controls.Add(this.tabPage1);
            this.tabControl1.Controls.Add(this.tabPage2);
            this.tabControl1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tabControl1.Location = new System.Drawing.Point(0, 0);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(756, 468);
            this.tabControl1.TabIndex = 1;
            // 
            // tabPage1
            // 
            this.tabPage1.Controls.Add(this.iWebBrowser);
            this.tabPage1.Location = new System.Drawing.Point(4, 22);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage1.Size = new System.Drawing.Size(748, 442);
            this.tabPage1.TabIndex = 0;
            this.tabPage1.Text = "XML";
            this.tabPage1.UseVisualStyleBackColor = true;
            this.tabPage1.UseWaitCursor = true;
            // 
            // tabPage2
            // 
            this.tabPage2.Controls.Add(this.iTextBox);
            this.tabPage2.Location = new System.Drawing.Point(4, 22);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage2.Size = new System.Drawing.Size(748, 442);
            this.tabPage2.TabIndex = 1;
            this.tabPage2.Text = "View source";
            this.tabPage2.UseVisualStyleBackColor = true;
            // 
            // iTextBox
            // 
            this.iTextBox.Dock = System.Windows.Forms.DockStyle.Fill;
            this.iTextBox.Font = new System.Drawing.Font("Consolas", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.iTextBox.Location = new System.Drawing.Point(3, 3);
            this.iTextBox.Multiline = true;
            this.iTextBox.Name = "iTextBox";
            this.iTextBox.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.iTextBox.Size = new System.Drawing.Size(742, 436);
            this.iTextBox.TabIndex = 0;
            // 
            // ShowXmlForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(756, 468);
            this.Controls.Add(this.tabControl1);
            this.Name = "ShowXmlForm";
            this.Text = "[Something] XML";
            this.tabControl1.ResumeLayout(false);
            this.tabPage1.ResumeLayout(false);
            this.tabPage2.ResumeLayout(false);
            this.tabPage2.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.WebBrowser iWebBrowser;
        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tabPage1;
        private System.Windows.Forms.TabPage tabPage2;
        private System.Windows.Forms.TextBox iTextBox;
    }
}