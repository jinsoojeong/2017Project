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
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.ping_label_ = new System.Windows.Forms.Label();
            this.total_user_label_ = new System.Windows.Forms.Label();
            this.lobby_user_label_ = new System.Windows.Forms.Label();
            this.waiting_user_lable_ = new System.Windows.Forms.Label();
            this.playing_user_label_ = new System.Windows.Forms.Label();
            this.groupBox1.SuspendLayout();
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
            this.groupBox1.Controls.Add(this.playing_user_label_);
            this.groupBox1.Controls.Add(this.waiting_user_lable_);
            this.groupBox1.Controls.Add(this.lobby_user_label_);
            this.groupBox1.Controls.Add(this.total_user_label_);
            this.groupBox1.Controls.Add(this.ping_label_);
            this.groupBox1.Controls.Add(this.label5);
            this.groupBox1.Controls.Add(this.label4);
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Location = new System.Drawing.Point(522, 96);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(180, 294);
            this.groupBox1.TabIndex = 6;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Lobby Info";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("굴림", 10F);
            this.label1.Location = new System.Drawing.Point(6, 27);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(51, 14);
            this.label1.TabIndex = 0;
            this.label1.Text = "Ping : ";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("굴림", 10F);
            this.label2.Location = new System.Drawing.Point(6, 51);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(89, 14);
            this.label2.TabIndex = 1;
            this.label2.Text = "Total User : ";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("굴림", 10F);
            this.label3.Location = new System.Drawing.Point(6, 102);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(105, 14);
            this.label3.TabIndex = 2;
            this.label3.Text = "Waiting User : ";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("굴림", 10F);
            this.label4.Location = new System.Drawing.Point(6, 127);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(105, 14);
            this.label4.TabIndex = 3;
            this.label4.Text = "Playing User : ";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("굴림", 10F);
            this.label5.Location = new System.Drawing.Point(6, 76);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(98, 14);
            this.label5.TabIndex = 4;
            this.label5.Text = "Lobby User : ";
            // 
            // ping_label_
            // 
            this.ping_label_.AutoSize = true;
            this.ping_label_.Font = new System.Drawing.Font("굴림", 10F);
            this.ping_label_.Location = new System.Drawing.Point(63, 27);
            this.ping_label_.Name = "ping_label_";
            this.ping_label_.Size = new System.Drawing.Size(12, 14);
            this.ping_label_.TabIndex = 5;
            this.ping_label_.Text = " ";
            // 
            // total_user_label_
            // 
            this.total_user_label_.AutoSize = true;
            this.total_user_label_.Font = new System.Drawing.Font("굴림", 10F);
            this.total_user_label_.Location = new System.Drawing.Point(92, 51);
            this.total_user_label_.Name = "total_user_label_";
            this.total_user_label_.Size = new System.Drawing.Size(12, 14);
            this.total_user_label_.TabIndex = 6;
            this.total_user_label_.Text = " ";
            // 
            // lobby_user_label_
            // 
            this.lobby_user_label_.AutoSize = true;
            this.lobby_user_label_.Font = new System.Drawing.Font("굴림", 10F);
            this.lobby_user_label_.Location = new System.Drawing.Point(99, 76);
            this.lobby_user_label_.Name = "lobby_user_label_";
            this.lobby_user_label_.Size = new System.Drawing.Size(12, 14);
            this.lobby_user_label_.TabIndex = 7;
            this.lobby_user_label_.Text = " ";
            // 
            // waiting_user_lable_
            // 
            this.waiting_user_lable_.AutoSize = true;
            this.waiting_user_lable_.Font = new System.Drawing.Font("굴림", 10F);
            this.waiting_user_lable_.Location = new System.Drawing.Point(108, 102);
            this.waiting_user_lable_.Name = "waiting_user_lable_";
            this.waiting_user_lable_.Size = new System.Drawing.Size(12, 14);
            this.waiting_user_lable_.TabIndex = 8;
            this.waiting_user_lable_.Text = " ";
            // 
            // playing_user_label_
            // 
            this.playing_user_label_.AutoSize = true;
            this.playing_user_label_.Font = new System.Drawing.Font("굴림", 10F);
            this.playing_user_label_.Location = new System.Drawing.Point(108, 127);
            this.playing_user_label_.Name = "playing_user_label_";
            this.playing_user_label_.Size = new System.Drawing.Size(12, 14);
            this.playing_user_label_.TabIndex = 9;
            this.playing_user_label_.Text = " ";
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
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox textBox_input_;
        private System.Windows.Forms.RichTextBox richTextBox_view_;
        private System.Windows.Forms.Button Btn_Start;
        private System.Windows.Forms.Button Btn_Cancel;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label lobby_user_label_;
        private System.Windows.Forms.Label total_user_label_;
        private System.Windows.Forms.Label ping_label_;
        private System.Windows.Forms.Label waiting_user_lable_;
        private System.Windows.Forms.Label playing_user_label_;
    }
}