using System.Windows;
using System.Collections;

namespace ListView
{
	/// <summary>
	/// Interaction logic for MainWindow.xaml
	/// </summary>
	public partial class MainWindow : Window
	{
		public MainWindow()
		{
			InitializeComponent();
			lvEntries.Items.Add("Хорошо");
			lvEntries.Items.Add("живет");
			lvEntries.Items.Add("на");
			lvEntries.Items.Add("свете");
			lvEntries.Items.Add("Винни");
			lvEntries.Items.Add("Пух");
		}

		private void BtnAdd_Click(object sender, RoutedEventArgs e)
		{
			lvEntries.Items.Add(txtEntry.Text);
			txtEntry.Clear();
		}

		private void BtnClr_Click(object sender, RoutedEventArgs e)
		{
			lvEntries.Items.Clear();
		}

		private void BtnDel_Click(object sender, RoutedEventArgs e)
		{
			//object item = lvEntries.SelectedItem;
			//if
			//	(
			//		MessageBox.Show
			//		(
			//		"Вы действительно собираетесь удавить выбранный элемент",
			//		"Question",
			//		MessageBoxButton.YesNo,
			//		MessageBoxImage.Question
			//		) == MessageBoxResult.Yes
			//	)
			//{
			//	lvEntries.Items.Remove(item);
			//}

			System.Collections.IList items = lvEntries.SelectedItems;
			if
				(
					MessageBox.Show
					(
						"Вы действительно хотите удавить выбранные элементы",
						"Question",
						MessageBoxButton.YesNo,
						MessageBoxImage.Question
					) == MessageBoxResult.Yes
				)
			{
				System.Collections.ArrayList itemsList = new ArrayList(items);
				foreach (string item in itemsList)
				{
					lvEntries.Items.Remove(item);
				}
			}
		}
	}
}
