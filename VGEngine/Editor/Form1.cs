using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Editor
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }
        [DllImport(@"D:\Users\Zero\Documents\visual studio 2013\Projects\DllTest\Debug\DllTest.dll")]
        public static extern int doubleValue(int value);
        [DllImport(@"D:\Users\Zero\Documents\visual studio 2013\Projects\DllTest\Debug\DllTest.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void Add(int value);
        private void button1_Click(object sender, EventArgs e)
        {
            doubleValue(2);
            Add(22);
        }
    }
}
