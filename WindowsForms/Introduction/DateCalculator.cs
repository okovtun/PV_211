using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Introduction
{
	public partial class DateCalculator : Form
	{
		public DateCalculator()
		{
			InitializeComponent();
			comboBox1.SelectedIndex = 0;
		}

		private void btnCalculate_Click(object sender, EventArgs e)
		{
			DateTime startDate = dateTimePickerStart.Value;
			DateTime endDate = dateTimePickerEnd.Value;
			if (startDate > endDate)
			{
				MessageBox.Show(this, "End date connot be less then start date", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
				return;
			}
			string result = "Результат вычисления даты: ";
			string units = comboBox1.SelectedItem.ToString();

			if (units == "Years")
			{
				if (startDate.Year != endDate.Year)
				{
					int years = endDate.Year - startDate.Year;
					result = years.ToString();
					string suffix = years == 1 ? " year" : " years";
					result += suffix;
				}
				if (startDate.Month != endDate.Month)
				{
					int monthes = endDate.Month - startDate.Month;
					if (result != "") result += ", ";
					result += monthes.ToString();
					string suffix = monthes == 1 ? " month" : " monthes";
					result += suffix;
				}
				if (startDate.Day != endDate.Day)
				{
					int days = endDate.Day - startDate.Day;
					if (result != "") result += ", ";
					result += days.ToString();
					string suffix = days == 1 ? " day" : " days";
					result += suffix;
				}
			}

			if (units == "Monthes")
			{
				//int monthes = endDate.Month - startDate.Month;
				////if (result != "") result += ", ";
				//int days = (endDate.Day - startDate.Day);
				//if (days < 0)
				//{
				//	monthes--;
				//	int daysInMonth = DateTime.DaysInMonth(endDate.Year, endDate.Month) + days;
				//	days = daysInMonth - days;
				//}
				//result = monthes.ToString() + (monthes == 1 ? " month" : " monthes");
				//result += " ";
				//result += days.ToString() + " " + (days == 1 ? " day" : " days");

				int monthes = endDate.Month - startDate.Month;
				int days = 0;
				if (endDate.Day > startDate.Day)
				{
					days = endDate.Day - startDate.Day;
				}
				else
				{
					monthes--;
					int daysInMonth = DateTime.DaysInMonth(endDate.Year, endDate.Month - 1);
					days = daysInMonth - startDate.Day + endDate.Day;
				}
				if (monthes != 0) result += monthes.ToString() + (monthes == 1 ? " month" : " monthes");
				if (result != "" && monthes != 0) result += ", ";
				result += days + (days == 1 ? " day" : " days");
			}

			MessageBox.Show(this, result, "Interval");
		}
	}
}
