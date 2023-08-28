//WPF - Windows Presentation Foundation
//MVC - Model View Cotroller
//GUI - Graphics User Interface
//UX/UI - User Experience / User Interface

//XAML - eXtensible Application Markup Language
//		(Расширяемый язык разметки приложений)
//XML  - xEtensible Markup Language
//HTML - Hyper-Text Markup Language

using System.Windows;

namespace WPF
{
	public partial class MainWindow : Window
	{
		public MainWindow()
		{
			InitializeComponent();
		}
		bool running = false;
		private void BtnStatus_Click(object sender, RoutedEventArgs e)
		{
			running = !running;
			//!true == false;
			if (running)
			{
				tbStatus.Text = "Running...";
				btnStatus.Content = "Stop";
			}
			else
			{
				tbStatus.Text = "Stopped";
				btnStatus.Content = "Run";
			}
		}
	}
}
