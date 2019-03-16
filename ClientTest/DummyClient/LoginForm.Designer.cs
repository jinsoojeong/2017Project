namespace DummyClient
{
    partial class LoginForm
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
            this.textBox_id_ = new System.Windows.Forms.TextBox();
            this.textBox_pw_ = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.button_login_ = new System.Windows.Forms.Button();
            this.button_quit_ = new System.Windows.Forms.Button();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.Textbox_NickName = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.button_connect_login_skip_ = new System.Windows.Forms.Button();
            this.button_connect_ = new System.Windows.Forms.Button();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.SuspendLayout();
            // 
            // textBox_id_
            // 
            this.textBox_id_.Location = new System.Drawing.Point(76, 27);
            this.textBox_id_.Name = "textBox_id_";
            this.textBox_id_.Size = new System.Drawing.Size(109, 21);
            this.textBox_id_.TabIndex = 0;
            // 
            // textBox_pw_
            // 
            this.textBox_pw_.Location = new System.Drawing.Point(76, 54);
            this.textBox_pw_.Name = "textBox_pw_";
            this.textBox_pw_.PasswordChar = '*';
            this.textBox_pw_.Size = new System.Drawing.Size(109, 21);
            this.textBox_pw_.TabIndex = 1;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(31, 30);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(16, 12);
            this.label1.TabIndex = 2;
            this.label1.Text = "ID";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(8, 57);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(62, 12);
            this.label2.TabIndex = 3;
            this.label2.Text = "Password";
            // 
            // button_login_
            // 
            this.button_login_.Location = new System.Drawing.Point(70, 94);
            this.button_login_.Name = "button_login_";
            this.button_login_.Size = new System.Drawing.Size(57, 23);
            this.button_login_.TabIndex = 4;
            this.button_login_.Text = "로그인";
            this.button_login_.UseVisualStyleBackColor = true;
            this.button_login_.Click += new System.EventHandler(this.button_login_Click);
            // 
            // button_quit_
            // 
            this.button_quit_.Location = new System.Drawing.Point(133, 94);
            this.button_quit_.Name = "button_quit_";
            this.button_quit_.Size = new System.Drawing.Size(66, 23);
            this.button_quit_.TabIndex = 5;
            this.button_quit_.Text = "종료";
            this.button_quit_.UseVisualStyleBackColor = true;
            this.button_quit_.Click += new System.EventHandler(this.button_quit);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.button_connect_);
            this.groupBox1.Controls.Add(this.button_quit_);
            this.groupBox1.Controls.Add(this.button_login_);
            this.groupBox1.Controls.Add(this.textBox_id_);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.textBox_pw_);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Location = new System.Drawing.Point(12, 12);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(205, 123);
            this.groupBox1.TabIndex = 6;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Login Field";
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.button_connect_login_skip_);
            this.groupBox2.Controls.Add(this.label3);
            this.groupBox2.Controls.Add(this.Textbox_NickName);
            this.groupBox2.Location = new System.Drawing.Point(223, 12);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(176, 123);
            this.groupBox2.TabIndex = 7;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Login Skip";
            // 
            // Textbox_NickName
            // 
            this.Textbox_NickName.Location = new System.Drawing.Point(50, 27);
            this.Textbox_NickName.Name = "Textbox_NickName";
            this.Textbox_NickName.Size = new System.Drawing.Size(120, 21);
            this.Textbox_NickName.TabIndex = 0;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(6, 30);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(39, 12);
            this.label3.TabIndex = 1;
            this.label3.Text = "Name";
            // 
            // button_connect_login_skip_
            // 
            this.button_connect_login_skip_.Location = new System.Drawing.Point(8, 57);
            this.button_connect_login_skip_.Name = "button_connect_login_skip_";
            this.button_connect_login_skip_.Size = new System.Drawing.Size(162, 23);
            this.button_connect_login_skip_.TabIndex = 2;
            this.button_connect_login_skip_.Text = "Connect";
            this.button_connect_login_skip_.UseVisualStyleBackColor = true;
            this.button_connect_login_skip_.Click += new System.EventHandler(this.button_connect_login_skip__Click);
            // 
            // button_connect_
            // 
            this.button_connect_.Location = new System.Drawing.Point(6, 94);
            this.button_connect_.Name = "button_connect_";
            this.button_connect_.Size = new System.Drawing.Size(54, 23);
            this.button_connect_.TabIndex = 6;
            this.button_connect_.Text = "연결";
            this.button_connect_.UseVisualStyleBackColor = true;
            this.button_connect_.Click += new System.EventHandler(this.button_connect__Click);
            // 
            // LoginForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSize = true;
            this.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.ClientSize = new System.Drawing.Size(414, 148);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.Name = "LoginForm";
            this.Text = "DummyLogin";
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TextBox textBox_id_;
        private System.Windows.Forms.TextBox textBox_pw_;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button button_login_;
        private System.Windows.Forms.Button button_quit_;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox Textbox_NickName;
        private System.Windows.Forms.Button button_connect_login_skip_;
        private System.Windows.Forms.Button button_connect_;
    }
}