using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Diagnostics;

namespace MurenaLauncher
{
    /// <summary>
    /// Логика взаимодействия для MainWindow.xaml
    /// </summary>
    /// 
    public partial class MainWindow : Window
    {
        string path = System.IO.Path.GetDirectoryName(typeof(MainWindow).Assembly.Location);
        int SelectedBitness = 0;
        int ErrorCode = 0;
        bool isSucceeded = false;
        public MainWindow()
        {
            InitializeComponent();
            labelenginepath.Content = path;
            versionlabel.Content = "ver. " + "0.1 / Pre-Alpha Test Mode /";
        }

        private void launcherbtn_Click(object sender, RoutedEventArgs e)
        {
        
            switch (SelectedBitness)
            {
                case 0:
                    try
                    {
                        Process.Start(path + "\\R-Wolf Engine[Win32].exe");
                        isSucceeded = true;
                    }
                    catch
                    {
                        ErrorCode = 32;
                        MessageBox.Show("Code: 0x" + ErrorCode + "\nLauncher can't find an engine executable file\n" +
                            "Tried to open R-Wolf Engine by path: " + path + "\\" + "R-Wolf Engine[Win32].exe", "R-Wolf Engine Launcher:: Critical error", MessageBoxButton.OK,MessageBoxImage.Error);
                    }
                    break;
                case 1:
                    try
                    {
                        Process.Start(path + "\\R-Wolf Engine[x64].exe");
                        isSucceeded = true;
                    }
                    catch
                    {
                        ErrorCode = 64;
                        MessageBox.Show("Code: 0x" + ErrorCode + "\nLauncher can't find an engine executable file\n" +
                            "Tried to open R-Wolf Engine by path: " + path + "\\" + "R-Wolf Engine[x64].exe", "R-Wolf Engine Launcher:: Critical error", MessageBoxButton.OK, MessageBoxImage.Error);
                    }
                    break;
            }
            if(isSucceeded == true)
            {
                Process.GetCurrentProcess().Kill();
            }
        }

        private void RadioButton_Checked(object sender, RoutedEventArgs e)
        {
            SelectedBitness = 0;
        }

        private void RadioButton_Checked_1(object sender, RoutedEventArgs e)
        {
            SelectedBitness = 1;
        }

        private void exitbtn_Click(object sender, RoutedEventArgs e)
        {
            Process.GetCurrentProcess().Kill();
        }
    }
}
