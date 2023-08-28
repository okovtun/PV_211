using System.Windows;
using System.Windows.Controls;
using CustomUserControls;

namespace CustomUserControls.View.UserControls
{
	/// <summary>
	/// Interaction logic for MenuBar.xaml
	/// </summary>
	public partial class MenuBar : UserControl
	{
		public MenuBar()
		{
			InitializeComponent();
		}

		private void MenuItem_Click(object sender, RoutedEventArgs e)
		{
			Application.Current.Shutdown();
		}
	}
}
