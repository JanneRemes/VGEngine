﻿namespace Editor
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
            this.button1 = new System.Windows.Forms.Button();
            this.panel1 = new System.Windows.Forms.Panel();
            this.button2 = new System.Windows.Forms.Button();
            this.buttonAddGameObject = new System.Windows.Forms.Button();
            this.textBoxGameObjectName = new System.Windows.Forms.TextBox();
            this.treeViewGameObjects = new System.Windows.Forms.TreeView();
            this.SuspendLayout();
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(85, 42);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 0;
            this.button1.Text = "button1";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // panel1
            // 
            this.panel1.BackColor = System.Drawing.SystemColors.ControlDark;
            this.panel1.Location = new System.Drawing.Point(232, 100);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(863, 461);
            this.panel1.TabIndex = 1;
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(514, 42);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(75, 23);
            this.button2.TabIndex = 2;
            this.button2.Text = "Test";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // buttonAddGameObject
            // 
            this.buttonAddGameObject.Location = new System.Drawing.Point(12, 538);
            this.buttonAddGameObject.Name = "buttonAddGameObject";
            this.buttonAddGameObject.Size = new System.Drawing.Size(107, 23);
            this.buttonAddGameObject.TabIndex = 4;
            this.buttonAddGameObject.Text = "Add GameObject";
            this.buttonAddGameObject.UseVisualStyleBackColor = true;
            this.buttonAddGameObject.Click += new System.EventHandler(this.buttonAddGameObject_Click);
            // 
            // textBoxGameObjectName
            // 
            this.textBoxGameObjectName.Location = new System.Drawing.Point(12, 567);
            this.textBoxGameObjectName.Name = "textBoxGameObjectName";
            this.textBoxGameObjectName.Size = new System.Drawing.Size(120, 20);
            this.textBoxGameObjectName.TabIndex = 5;
            // 
            // treeViewGameObjects
            // 
            this.treeViewGameObjects.Location = new System.Drawing.Point(12, 100);
            this.treeViewGameObjects.Name = "treeViewGameObjects";
            this.treeViewGameObjects.Size = new System.Drawing.Size(193, 432);
            this.treeViewGameObjects.TabIndex = 6;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1097, 695);
            this.Controls.Add(this.treeViewGameObjects);
            this.Controls.Add(this.textBoxGameObjectName);
            this.Controls.Add(this.buttonAddGameObject);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.button1);
            this.Name = "Form1";
            this.Text = "Form1";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Button buttonAddGameObject;
        private System.Windows.Forms.TextBox textBoxGameObjectName;
        private System.Windows.Forms.TreeView treeViewGameObjects;
    }
}

