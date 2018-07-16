namespace DummyClient
{
    partial class LobbyForm
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
            this.textBox_input_ = new System.Windows.Forms.TextBox();
            this.richTextBox_view_ = new System.Windows.Forms.RichTextBox();
            this.Btn_Start = new System.Windows.Forms.Button();
            this.Btn_Cancel = new System.Windows.Forms.Button();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.SuspendLayout();
            // 
            // textBox_input_
            // 
            this.textBox_input_.Location = new System.Drawing.Point(20, 369);
            this.textBox_input_.Name = "textBox_input_";
            this.textBox_input_.Size = new System.Drawing.Size(495, 21);
            this.textBox_input_.TabIndex = 3;
            this.textBox_input_.KeyDown += new System.Windows.Forms.KeyEventHandler(this.textBox_input_KeyDown);
            // 
            // richTextBox_view_
            // 
            this.richTextBox_view_.BackColor = System.Drawing.Color.Teal;
            this.richTextBox_view_.ForeColor = System.Drawing.Color.White;
            this.richTextBox_view_.Location = new System.Drawing.Point(20, 12);
            this.richTextBox_view_.Name = "richTextBox_view_";
            this.richTextBox_view_.ReadOnly = true;
            this.richTextBox_view_.ScrollBars = System.Windows.Forms.RichTextBoxScrollBars.Vertical;
            this.richTextBox_view_.Size = new System.Drawing.Size(495, 351);
            this.richTextBox_view_.TabIndex = 2;
            this.richTextBox_view_.Text = "";
            // 
            // Btn_Start
            // 
            this.Btn_Start.Location = new System.Drawing.Point(522, 13);
            this.Btn_Start.Name = "Btn_Start";
            this.Btn_Start.Size = new System.Drawing.Size(180, 35);
            this.Btn_Start.TabIndex = 4;
            this.Btn_Start.Text = "MATCH_START";
            this.Btn_Start.UseVisualStyleBackColor = true;
            this.Btn_Start.Click += new System.EventHandler(this.Btn_Start_Click);
            // 
            // Btn_Cancel
            // 
            this.Btn_Cancel.Location = new System.Drawing.Point(522, 54);
            this.Btn_Cancel.Name = "Btn_Cancel";
            this.Btn_Cancel.Size = new System.Drawing.Size(180, 35);
            this.Btn_Cancel.TabIndex = 5;
            this.Btn_Cancel.Text = "MATCH_CANCEL";
            this.Btn_Cancel.UseVisualStyleBackColor = true;
            this.Btn_Cancel.Click += new System.EventHandler(this.Btn_Cancel_Click);
            // 
            // groupBox1
            // 
            this.groupBox1.Location = new System.Drawing.Point(522, 96);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(180, 294);
            this.groupBox1.TabIndex = 6;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Lobby Info";
            // 
            // LobbyForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSize = true;
            this.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.ClientSize = new System.Drawing.Size(714, 402);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.Btn_Cancel);
            this.Controls.Add(this.Btn_Start);
            this.Controls.Add(this.textBox_input_);
            this.Controls.Add(this.richTextBox_view_);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.Name = "LobbyForm";
            this.Text = "LobbyForm";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox textBox_input_;
        private System.Windows.Forms.RichTextBox richTextBox_view_;
        private System.Windows.Forms.Button Btn_Start;
        private System.Windows.Forms.Button Btn_Cancel;
        private System.Windows.Forms.GroupBox groupBox1;
    }
}