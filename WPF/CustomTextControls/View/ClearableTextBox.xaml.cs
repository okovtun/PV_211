using System;
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

namespace CustomTextControls.View
{
	/// <summary>
	/// Interaction logic for ClearableTextBox.xaml
	/// </summary>
	public partial class ClearableTextBox : UserControl
	{
		public ClearableTextBox()
		{
			InitializeComponent();
		}
		private string placeholder;	//переменная-член всегда называется с маленькой буквы

		public string Placeholder	//а соответствующее ей свойство с большой буквы
		{
			get { return placeholder; }
			set
			{
				placeholder = value;
				tbPlaceholder.Text = placeholder;
			}
		}

		private void BtnClear_Click(object sender, RoutedEventArgs e)
		{
			txtInput.Clear();
			txtInput.Focus();
		}

		private void TxtInput_TextChanged(object sender, TextChangedEventArgs e)
		{
			//if (string.IsNullOrEmpty(txtInput.Text))
			//	tbPlaceholder.Visibility = Visibility.Visible;
			//else
			//	tbPlaceholder.Visibility = Visibility.Hidden;
			tbPlaceholder.Visibility = string.IsNullOrEmpty(txtInput.Text) ? Visibility.Visible : Visibility.Hidden;
		}
	}
}
