using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
namespace Editor
{
    public partial class Form1 : Form
    {
        IntPtr ptr;
        static String dllPath = "";
        public Form1()
        {
            InitializeComponent();
            ptr = panel1.Handle;
        }
        [DllImport(@"..\..\..\Win32\EngineDLL\Engine.dll")]
        public static extern int doubleValue(int value);
        [DllImport(@"..\..\..\Win32\EngineDLL\Engine.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void Add(int value);

        [DllImport(@"..\..\..\Win32\EngineDLL\Engine.dll", CallingConvention = CallingConvention.Cdecl)]
        public unsafe static extern void MakeGame(void *data);
        [DllImport(@"..\..\..\Win32\EngineDLL\Engine.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void Update();
        [DllImport(@"..\..\..\Win32\EngineDLL\Engine.dll")]
        public unsafe static extern int Pointer(void *data);
        private void button1_Click(object sender, EventArgs e)
        {
            doubleValue(2);
            Add(22);
            
            Thread doge = new Thread(updateGame);
            doge.Start();
            
        }
        void updateGame()
        {
            unsafe
            {
         
                MakeGame(ptr.ToPointer());
                while (true)
                {
                    Update();
            //        Console.Out.WriteLine(Pointer(ptr.ToPointer()));
               }
           }
        }
    }
}
