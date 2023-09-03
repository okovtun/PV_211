using System.Windows;
using System.Collections;
using System.Collections.ObjectModel;

namespace ListView
{
	/// <summary>
	/// Interaction logic for MainWindow.xaml
	/// </summary>
	public partial class MainWindow : Window
	{
		public MainWindow()
		{
			DataContext = this;
			Entries = new ObservableCollection<string>(new string[] { "No", "money", "no", "honey" });
			InitializeComponent();
		}

		private ObservableCollection<string> entries;

		public ObservableCollection<string> Entries
		{
			get { return  entries; }
			set
			{
				entries = value;
			}
		}


		private void BtnAdd_Click(object sender, RoutedEventArgs e)
		{
			Entries.Add(txtEntry.Text);
			txtEntry.Clear();
			txtEntry.Focus();
		}

		private void BtnClr_Click(object sender, RoutedEventArgs e)
		{
			Entries.Clear();
		}

		private void BtnDel_Click(object sender, RoutedEventArgs e)
		{
			Entries.Remove((string)lvEntries.SelectedItem);
		}
	}
}
