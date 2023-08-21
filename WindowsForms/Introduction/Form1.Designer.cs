namespace Introduction
{
	partial class Form1
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
			this.components = new System.ComponentModel.Container();
			System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
			this.label1 = new System.Windows.Forms.Label();
			this.timer1 = new System.Windows.Forms.Timer(this.components);
			this.cbShowDate = new System.Windows.Forms.CheckBox();
			this.btnClose = new System.Windows.Forms.Button();
			this.btnHideControls = new System.Windows.Forms.Button();
			this.notifyIcon1 = new System.Windows.Forms.NotifyIcon(this.components);
			this.sysTrayContextMenu = new System.Windows.Forms.ContextMenuStrip(this.components);
			this.stcmShowControlsItem = new System.Windows.Forms.ToolStripMenuItem();
			this.stcmHideControlsItem = new System.Windows.Forms.ToolStripMenuItem();
			this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
			this.stcmExitItem = new System.Windows.Forms.ToolStripMenuItem();
			this.btnDateCalculator = new System.Windows.Forms.Button();
			this.sysTrayContextMenu.SuspendLayout();
			this.SuspendLayout();
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.BackColor = System.Drawing.SystemColors.GradientActiveCaption;
			this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 48F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
			this.label1.Location = new System.Drawing.Point(26, 9);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(204, 73);
			this.label1.TabIndex = 0;
			this.label1.Text = "label1";
			this.label1.MouseHover += new System.EventHandler(this.label1_MouseHover);
			this.label1.Move += new System.EventHandler(this.label1_Move);
			// 
			// timer1
			// 
			this.timer1.Enabled = true;
			this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
			// 
			// cbShowDate
			// 
			this.cbShowDate.AutoSize = true;
			this.cbShowDate.Font = new System.Drawing.Font("Microsoft Sans Serif", 24F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
			this.cbShowDate.Location = new System.Drawing.Point(39, 181);
			this.cbShowDate.Name = "cbShowDate";
			this.cbShowDate.Size = new System.Drawing.Size(187, 41);
			this.cbShowDate.TabIndex = 1;
			this.cbShowDate.Text = "Show date";
			this.cbShowDate.UseVisualStyleBackColor = true;
			this.cbShowDate.Visible = false;
			// 
			// btnClose
			// 
			this.btnClose.Font = new System.Drawing.Font("Microsoft Sans Serif", 24F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
			this.btnClose.Location = new System.Drawing.Point(39, 389);
			this.btnClose.Name = "btnClose";
			this.btnClose.Size = new System.Drawing.Size(273, 50);
			this.btnClose.TabIndex = 2;
			this.btnClose.Text = "Close";
			this.btnClose.UseVisualStyleBackColor = true;
			this.btnClose.Visible = false;
			this.btnClose.Click += new System.EventHandler(this.btnClose_Click);
			// 
			// btnHideControls
			// 
			this.btnHideControls.Font = new System.Drawing.Font("Microsoft Sans Serif", 24F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
			this.btnHideControls.Location = new System.Drawing.Point(39, 333);
			this.btnHideControls.Name = "btnHideControls";
			this.btnHideControls.Size = new System.Drawing.Size(273, 50);
			this.btnHideControls.TabIndex = 3;
			this.btnHideControls.Text = "Hide controls";
			this.btnHideControls.UseVisualStyleBackColor = true;
			this.btnHideControls.Visible = false;
			this.btnHideControls.Click += new System.EventHandler(this.btnHideControls_Click);
			// 
			// notifyIcon1
			// 
			this.notifyIcon1.ContextMenuStrip = this.sysTrayContextMenu;
			this.notifyIcon1.Icon = ((System.Drawing.Icon)(resources.GetObject("notifyIcon1.Icon")));
			this.notifyIcon1.Text = "notifyIcon1";
			this.notifyIcon1.Visible = true;
			// 
			// sysTrayContextMenu
			// 
			this.sysTrayContextMenu.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.stcmShowControlsItem,
            this.stcmHideControlsItem,
            this.toolStripSeparator1,
            this.stcmExitItem});
			this.sysTrayContextMenu.Name = "sysTrayContextMenu";
			this.sysTrayContextMenu.Size = new System.Drawing.Size(150, 76);
			// 
			// stcmShowControlsItem
			// 
			this.stcmShowControlsItem.Name = "stcmShowControlsItem";
			this.stcmShowControlsItem.Size = new System.Drawing.Size(149, 22);
			this.stcmShowControlsItem.Text = "Show controls";
			this.stcmShowControlsItem.Click += new System.EventHandler(this.label1_MouseHover);
			// 
			// stcmHideControlsItem
			// 
			this.stcmHideControlsItem.Name = "stcmHideControlsItem";
			this.stcmHideControlsItem.Size = new System.Drawing.Size(149, 22);
			this.stcmHideControlsItem.Text = "Hide controls";
			this.stcmHideControlsItem.Click += new System.EventHandler(this.btnHideControls_Click);
			// 
			// toolStripSeparator1
			// 
			this.toolStripSeparator1.Name = "toolStripSeparator1";
			this.toolStripSeparator1.Size = new System.Drawing.Size(146, 6);
			// 
			// stcmExitItem
			// 
			this.stcmExitItem.Name = "stcmExitItem";
			this.stcmExitItem.Size = new System.Drawing.Size(149, 22);
			this.stcmExitItem.Text = "Exit";
			this.stcmExitItem.Click += new System.EventHandler(this.btnClose_Click);
			// 
			// btnDateCalculator
			// 
			this.btnDateCalculator.Font = new System.Drawing.Font("Microsoft Sans Serif", 24F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
			this.btnDateCalculator.Location = new System.Drawing.Point(39, 277);
			this.btnDateCalculator.Name = "btnDateCalculator";
			this.btnDateCalculator.Size = new System.Drawing.Size(273, 50);
			this.btnDateCalculator.TabIndex = 4;
			this.btnDateCalculator.Text = "Date calculator";
			this.btnDateCalculator.UseVisualStyleBackColor = true;
			this.btnDateCalculator.Visible = false;
			this.btnDateCalculator.Click += new System.EventHandler(this.btnDateCalculator_Click);
			// 
			// Form1
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(473, 451);
			this.Controls.Add(this.btnDateCalculator);
			this.Controls.Add(this.btnHideControls);
			this.Controls.Add(this.btnClose);
			this.Controls.Add(this.cbShowDate);
			this.Controls.Add(this.label1);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
			this.Location = new System.Drawing.Point(900, 10);
			this.Name = "Form1";
			this.ShowInTaskbar = false;
			this.StartPosition = System.Windows.Forms.FormStartPosition.Manual;
			this.Text = "Clock";
			this.TopMost = true;
			this.TransparencyKey = System.Drawing.SystemColors.Control;
			this.sysTrayContextMenu.ResumeLayout(false);
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.Timer timer1;
		private System.Windows.Forms.CheckBox cbShowDate;
		private System.Windows.Forms.Button btnClose;
		private System.Windows.Forms.Button btnHideControls;
		private System.Windows.Forms.NotifyIcon notifyIcon1;
		private System.Windows.Forms.ContextMenuStrip sysTrayContextMenu;
		private System.Windows.Forms.ToolStripMenuItem stcmShowControlsItem;
		private System.Windows.Forms.ToolStripMenuItem stcmHideControlsItem;
		private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
		private System.Windows.Forms.ToolStripMenuItem stcmExitItem;
		private System.Windows.Forms.Button btnDateCalculator;
	}
}

