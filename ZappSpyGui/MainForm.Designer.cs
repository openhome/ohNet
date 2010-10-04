namespace ZapSpyGui
{
    partial class MainForm
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
            this.iDeviceTreeView = new System.Windows.Forms.TreeView();
            this.splitContainer1 = new System.Windows.Forms.SplitContainer();
            this.iDetailsListView = new System.Windows.Forms.ListView();
            this.iNameColumn = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.iValueColumn = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            //((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).BeginInit();
            this.splitContainer1.Panel1.SuspendLayout();
            this.splitContainer1.Panel2.SuspendLayout();
            this.splitContainer1.SuspendLayout();
            this.SuspendLayout();
            // 
            // iDeviceTreeView
            // 
            this.iDeviceTreeView.Dock = System.Windows.Forms.DockStyle.Fill;
            this.iDeviceTreeView.Location = new System.Drawing.Point(0, 0);
            this.iDeviceTreeView.Name = "iDeviceTreeView";
            this.iDeviceTreeView.Size = new System.Drawing.Size(326, 466);
            this.iDeviceTreeView.TabIndex = 0;
            // 
            // splitContainer1
            // 
            this.splitContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer1.Location = new System.Drawing.Point(0, 0);
            this.splitContainer1.Name = "splitContainer1";
            // 
            // splitContainer1.Panel1
            // 
            this.splitContainer1.Panel1.Controls.Add(this.iDeviceTreeView);
            // 
            // splitContainer1.Panel2
            // 
            this.splitContainer1.Panel2.Controls.Add(this.iDetailsListView);
            this.splitContainer1.Size = new System.Drawing.Size(719, 466);
            this.splitContainer1.SplitterDistance = 326;
            this.splitContainer1.TabIndex = 1;
            this.splitContainer1.TabStop = false;
            // 
            // iDetailsListView
            // 
            this.iDetailsListView.Activation = System.Windows.Forms.ItemActivation.OneClick;
            this.iDetailsListView.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.iNameColumn,
            this.iValueColumn});
            this.iDetailsListView.Dock = System.Windows.Forms.DockStyle.Fill;
            this.iDetailsListView.HoverSelection = true;
            this.iDetailsListView.Location = new System.Drawing.Point(0, 0);
            this.iDetailsListView.Name = "iDetailsListView";
            this.iDetailsListView.Size = new System.Drawing.Size(389, 466);
            this.iDetailsListView.Sorting = System.Windows.Forms.SortOrder.Ascending;
            this.iDetailsListView.TabIndex = 0;
            this.iDetailsListView.UseCompatibleStateImageBehavior = false;
            this.iDetailsListView.View = System.Windows.Forms.View.Details;
            // 
            // iNameColumn
            // 
            this.iNameColumn.Text = "Name";
            this.iNameColumn.Width = 146;
            // 
            // iValueColumn
            // 
            this.iValueColumn.Text = "Value";
            this.iValueColumn.Width = 238;
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(719, 466);
            this.Controls.Add(this.splitContainer1);
            this.Name = "MainForm";
            this.Text = "Zapp Spy";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.splitContainer1.Panel1.ResumeLayout(false);
            this.splitContainer1.Panel2.ResumeLayout(false);
            //((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).EndInit();
            this.splitContainer1.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TreeView iDeviceTreeView;
        private System.Windows.Forms.SplitContainer splitContainer1;
        private System.Windows.Forms.ListView iDetailsListView;
        private System.Windows.Forms.ColumnHeader iNameColumn;
        private System.Windows.Forms.ColumnHeader iValueColumn;
    }
}

