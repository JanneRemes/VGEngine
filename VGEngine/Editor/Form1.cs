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
         const String dllPath = @"..\..\..\Win32\EngineDLL\Engine.dll";

        public Form1()
        {
            InitializeComponent();
            ptr = panel1.Handle;
        }
        [DllImport(dllPath)]
        public static extern int doubleValue(int value);
        [DllImport(dllPath, CallingConvention = CallingConvention.Cdecl)]
        public static extern void Add(int value);

        [DllImport(dllPath, CallingConvention = CallingConvention.Cdecl)]
        public unsafe static extern void MakeGame(void *data);
        [DllImport(dllPath, CallingConvention = CallingConvention.Cdecl)]
        public static extern void Update();
        [DllImport(dllPath)]
        public unsafe static extern int Pointer(void *data);

        [DllImport(dllPath)]
        public unsafe static extern int SendCommand(string data, StringBuilder outData, int outSize);


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
                Console.Out.WriteLine(Directory.GetCurrentDirectory());
                MakeGame(ptr.ToPointer());
                while (true)
                {
                    Update();
            //        Console.Out.WriteLine(Pointer(ptr.ToPointer()));
               }
           }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            //byte[] buf = new byte[300];
            StringBuilder sb = new StringBuilder(100);
            int numbah = SendCommand("GETNAMEGAMEOBJECT 0", sb, sb.Length);
            Console.Out.WriteLine(sb.ToString());
            int numbah2 = SendCommand("GETNAMESGAMEOBJECTS 1", sb, sb.Length);
            Console.Out.WriteLine("Return objects: " + sb.ToString());
            treeViewGameObjects.Nodes.Clear();

            string text = sb.ToString();
            var splitted = text.Split(',');
            foreach(var nakki in splitted)
            {
                TreeNode node;
                var components = nakki.Split(';');
                  node = new TreeNode(components[0]);
                if(components.Length > 1)
                {
                  
                    for (int i = 0; i < components.Length; i++ )
                    {
                        if (i == 0)
                            continue;
                        node.Nodes.Add(components[i].Split(' ')[1]);
                    }
                }
                treeViewGameObjects.Nodes.Add(node);
            }
           // Console.Out.WriteLine(System.Text.Encoding.Unicode.GetString(buf));
            Console.Out.WriteLine(sb.ToString());
        }

        private void buttonAddGameObject_Click(object sender, EventArgs e)
        {
            if (textBoxGameObjectName.Text == "")
                return;
            StringBuilder sb = new StringBuilder(100);
            int numbah = SendCommand("CREATEGAMEOBJECT "+ textBoxGameObjectName.Text, sb, sb.Length);
            Console.Out.WriteLine(sb.ToString());
        }
    }
}
