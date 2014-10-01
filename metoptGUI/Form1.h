#pragma once

#include "FuncList.h"

namespace metoptGUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	
	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	private: AxC1Chart3D8::AxChart3D^  axChart3D1;
	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::GroupBox^  groupBox5;
	private: System::Windows::Forms::Label^  label16;
	private: System::Windows::Forms::ComboBox^  comboBox1;
	private: System::Windows::Forms::Label^  label15;
	private: System::Windows::Forms::Label^  label14;
	private: System::Windows::Forms::Label^  label13;
	private: System::Windows::Forms::Label^  label12;
	private: System::Windows::Forms::TextBox^  textBox5;
	private: System::Windows::Forms::Label^  label11;
	private: System::Windows::Forms::TextBox^  textBox4;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown3;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown2;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown1;
	private: System::Windows::Forms::GroupBox^  groupBox4;
	private: System::Windows::Forms::TextBox^  textBox2;

	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::CheckBox^  checkBox1;
	private: System::Windows::Forms::GroupBox^  groupBox6;
	private: System::Windows::Forms::ComboBox^  comboBox2;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::TextBox^  textBox6;
	private: System::Windows::Forms::Label^  label3;
	private: 
		int rotz;
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::TextBox^  textBox8;
	private: System::Windows::Forms::TextBox^  textBox7;
	private: System::Windows::Forms::TextBox^  textBox3;
	private: System::Windows::Forms::TextBox^  textBox9;
	private: System::Windows::Forms::TabControl^  tabControl2;
	private: System::Windows::Forms::TabPage^  tabPage3;
	private: System::Windows::Forms::TabPage^  tabPage4;
	private: System::Windows::Forms::CheckedListBox^  checkedListBox1;
	private: System::Windows::Forms::Panel^  panel2;
	private: System::Windows::Forms::RadioButton^  radioButton5;
	private: System::Windows::Forms::RadioButton^  radioButton4;
	private: System::Windows::Forms::RadioButton^  radioButton3;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::RadioButton^  radioButton6;
	private: System::Windows::Forms::RadioButton^  radioButton7;
			 int rotx;
		int checkDimMethod()
		{
			if (radioButton1->Checked)
			{
				return 0;
			}
			else
			{
				return 1;
			}
		}

		int chekTaskType()
		{
			if (tabControl2->SelectedTab->Name == "tabPage3")
			{
				return 0;
			}
			else
			{
				return 1;
			}
		}
	
		metopt::TYPE_EXIT_PRECISION_FLAG checkFlagExit()
		{
			switch( comboBox1->SelectedIndex )
			{
			case 0:
				return metopt::TYPE_EXIT_PRECISION_STEP;
			case 1:
				return metopt::TYPE_EXIT_PRECISION_FUNC;
			case 2:
				return metopt::TYPE_EXIT_PRECISION_VAR;
			}
			
		}	
				
		metopt::CFunc* checkFunc()
		{
			int jump = 0;
			if (!radioButton1->Checked)
				jump = 5;
			
			int a = cbFList->SelectedIndex + jump;
			metopt::CFunc* func;
			switch(cbFList->SelectedIndex + jump)
			{
			case 0:
				return func = new metopt::CFunc(Parabola);
				break;
			case 1:
				return func = new metopt::CFunc(Polynomial3D);
				break;
			case 2:
				return func = new metopt::CFunc(Parabola4D);
				break;
			case 3:
				return func = new metopt::CFunc(FractionalRational);
				break;
			case 4:
				return func = new metopt::CFunc(NonSmooth);
				break;
			case 5:
				return func = new metopt::CFunc(Paraboloid3d);
				break;
			case 6:
				return func = new metopt::CFunc(ExtendedParaboloid3d);
				break;
			case 7:
				return func = new metopt::CFunc(RotatedParaboloid3d);
				break;
			case 8:
				return func = new metopt::CFunc(Rosenbrock3d);
				break;
			case 9:
				return func = new metopt::CFunc(Z3d);
				break;
			case 10:
				return func = new metopt::CFunc(W3d);
				break;
			case 11:
				return func = new metopt::CFunc(RosenbrockMOD3d);
				break;
			}

		//	return func;
		}

		metopt::NAME_METHOD checkOneMethod()
		{
			switch (comboBox2->SelectedIndex)
			{
			case 0:
				return metopt::NAME_METHOD_ADAPTATION_STEP;
			case 1:
				return metopt::NAME_METHOD_UNIFORM;
			case 2:
				return metopt::NAME_METHOD_DIVISION;
			case 3:
				return metopt::NAME_METHOD_DICHOTOMY;
			case 4:
				return metopt::NAME_METHOD_FIBONACCI;
			case 5:
				return metopt::NAME_METHOD_GOLDEN_SECTION;
			case 6:
				return metopt::NAME_METHOD_QUADRATIC_INTERPOLATION;
			case 7:
				return metopt::NAME_METHOD_CUBIC_INTERPOLATION;
			}

			return metopt::NAME_METHOD_NONE;
		}

		metopt::NAME_METHOD checkMethod()
		{
			int jump = 0;
			if (!radioButton1->Checked)
				jump = 9;
			
			switch (cbMList->SelectedIndex + jump)
			{
				case 0:
					return metopt::NAME_METHOD_SVEN;
				case 1:
					return metopt::NAME_METHOD_ADAPTATION_STEP;
				case 2:
					return metopt::NAME_METHOD_UNIFORM;
				case 3:
					return metopt::NAME_METHOD_DIVISION;
				case 4:
					return metopt::NAME_METHOD_DICHOTOMY;
				case 5:
					return metopt::NAME_METHOD_FIBONACCI;
				case 6:
					return metopt::NAME_METHOD_GOLDEN_SECTION;
				case 7:
					return metopt::NAME_METHOD_QUADRATIC_INTERPOLATION;
				case 8:
					return metopt::NAME_METHOD_CUBIC_INTERPOLATION;
				case 9:
					return metopt::NAME_METHOD_HOOKE_JEEVES;
				case 10:
					return metopt::NAME_METHOD_NELDER_MEAD;
				case 11:
					return metopt::NAME_METHOD_SIMPLEX_METHOD;
				case 12:
					return metopt::NAME_METHOD_BOX;
				case 13:
					return metopt::NAME_METHOD_CYCLIC_MINMIN;
				case 14:
					return metopt::NAME_METHOD_GAUSS_SEIDEL;
				case 15:
					return metopt::NAME_METHOD_POWELL_SEARCH;
				case 16:
					return metopt::NAME_METHOD_RANDOM_SEARCH;
				case 17:
					return metopt::NAME_METHOD_WEIL_PI_SEARCH;
				case 18:
					return metopt::NAME_METHOD_WEIL_E_SEARCH;
				case 19:
					return metopt::NAME_METHOD_FASTEST_DESCENT;
				case 20:
					return metopt::NAME_METHOD_FLETCHER_REEVES;
				case 21:
					return metopt::NAME_METHOD_POLAK_RIBIERE;
				case 22:
					return metopt::NAME_METHOD_DFP_SEARCH;
				case 23:
					return metopt::NAME_METHOD_NEWTON_SEARCH;
				case 24:
					return metopt::NAME_METHOD_NEWTON_RAPHSON;
				case 25:
					return metopt::NAME_METHOD_BIN_GENETIC_ALGORITHM;
				case 26:
					return metopt::NAME_METHOD_CON_GENETIC_ALGORITHM;
			}

			return metopt::NAME_METHOD_NONE;
		}
		
		void selectNext( System::Windows::Forms::ContextMenu^ cm)
		{
			int sel = 0;
			for( int i=0; i<cm->MenuItems->Count; i++)
			{
				if( cm->MenuItems[i]->Checked)
				{
					sel =i;
					break;
				}
			}

			if( sel >= cm->MenuItems->Count-1)
				sel = 0;
			else
				sel++;

			if( cm->MenuItems[sel]->Text->Equals( "-"))
			{
				if( sel >= cm->MenuItems->Count-1)
					sel = 0;
				else
					sel++;
			}

			cm->MenuItems[sel]->PerformClick();
		}

		double* getCompareData(const metopt::CCompareData* _data)
		{
			double* array = new double[_data->getSize()];

			if (radioButton3->Checked)
			{
				int* data = _data->getCountCalcArray();
				for (int i = 0; i < _data->getSize(); ++i)
				{
					array[i] = (double)data[i];
				}
			}
			else if (radioButton4->Checked)
			{
				int* data = _data->getCountIterationArray();
				for (int i = 0; i < _data->getSize(); ++i)
				{
					array[i] = (double)data[i];
				}
			}
			else if (radioButton5->Checked)
			{
				double* data = _data->getElapsedTimeArray();
				for (int i = 0; i < _data->getSize(); ++i)
				{
					array[i] = data[i];
				}
			}
			else if (radioButton6->Checked)
			{
				double* data = _data->getPrecisionFuncArray();
				for (int i = 0; i < _data->getSize(); ++i)
				{
					array[i] = data[i];
				}
			}
			else if (radioButton7->Checked)
			{
				double* data = _data->getPrecisionArgArray();
				for (int i = 0; i < _data->getSize(); ++i)
				{
					array[i] = data[i];
				}
			}
			else
			{
				int* data = _data->getCountCalcArray();
				for (int i = 0; i < _data->getSize(); ++i)
				{
					array[i] = (double)data[i];
				}
			}

			return array;
		}

		void drawChart(const metopt::CFunc* _func)
		{
			axChart2D1->ChartGroups[1]->ChartType = C1Chart2D8::ChartTypeConstants::oc2dTypePlot;

			double** arrayPoints = _func->getData()->getPointsPointer();
			double max_el = arrayPoints[0][0];
			double min_el = arrayPoints[0][0];
			for ( int i = 0; i < _func->getData()->getCountPoints(); ++i )
			{
				if (arrayPoints[0][i] > max_el)
				{
					max_el = arrayPoints[0][i];
				}
				if (arrayPoints[0][i] < min_el)
				{
					min_el = arrayPoints[0][i];
				}
			}
			
			metopt::PTRFUNCONEDIM func = _func->getFunc()->getFunction();
			
			int countPoints = 20;
			axChart2D1->ChartGroups[1]->Data->NumSeries = 1;
			axChart2D1->ChartGroups[1]->Data->NumPoints[1] = countPoints + 1;
			//axChart2D1->ChartGroups[1]->_Item->Styles->_Item->
			double step = (max_el - min_el)/countPoints;
			double value = min_el;
			for ( int i = 0; i < countPoints + 1; ++i )
			{
				axChart2D1->ChartGroups[1]->Data->X[1,i+1] = value ;
				axChart2D1->ChartGroups[1]->Data->Y[1,i+1] = func(value);
				value += step;
			}

			axChart2D1->ChartGroups[2]->Data->NumSeries = 1;
			axChart2D1->ChartGroups[2]->Data->NumPoints[1] = _func->getData()->getCountPoints();
			for ( int i = 0; i < _func->getData()->getCountPoints(); ++i )
			{
				axChart2D1->ChartGroups[2]->Data->X[1,i+1] = arrayPoints[0][i];
				axChart2D1->ChartGroups[2]->Data->Y[1,i+1] = arrayPoints[1][i];
			}
						
		}

		void drawChart3D(const metopt::CFunc* _func)
		{
			double** arrayPoints = _func->getMultiData()->getPointsPointer();
			double max_el1 = arrayPoints[0][0];
			double min_el1 = arrayPoints[0][0];
			double max_el2 = arrayPoints[1][0];
			double min_el2 = arrayPoints[1][0];
		
			for ( int i = 0; i < _func->getMultiData()->getCountPoints(); ++i )
			{
				if (arrayPoints[0][i] > max_el1)
				{
					max_el1 = arrayPoints[0][i];
				}
				if (arrayPoints[0][i] < min_el1)
				{
					min_el1 = arrayPoints[0][i];
				}

				if (arrayPoints[1][i] > max_el2)
				{
					max_el2 = arrayPoints[1][i];
				}
				if (arrayPoints[1][i] < min_el2)
				{
					min_el2 = arrayPoints[1][i];
				}

			}

			metopt::PTRFUNCMULTDIM func = _func->getMultiFunc()->getFunction();

			int countPoints = 20;
			//axChart3D1->ChartGroups[1]->ElevationData->NumSeries = 1;
			axChart3D1->ChartGroups[1]->ElevationData->ColumnCount = countPoints + 1;
			axChart3D1->ChartGroups[1]->ElevationData->RowCount = countPoints + 1;
			
			double step1 = (max_el1 - min_el1)/countPoints;
			double step2 = (max_el2 - min_el2)/countPoints;
			double* value = new double[2];
			value[0] = min_el1;
			value[1] = min_el2;
			double funcValue = 0;
			for ( int i = 0; i < countPoints; ++i )
			{
				for ( int j = 0; j < countPoints; ++j )
				{
					funcValue = func(value);
					axChart3D1->ChartGroups[1]->ElevationData->Value[i+1,j+1] = funcValue;
				//	axChart2D1->ChartGroups[1]->Data->Y[1,i+1] = func(value);
					value[0] += step1;
				}
				value[0] = min_el1;
				value[1] += step2;
			}

			//axChart2D1->ChartGroups[2]->Data->NumSeries = 1;
			//axChart2D1->ChartGroups[2]->Data->NumPoints[1] = _func->getData()->getCountPoints();
			//for ( int i = 0; i < _func->getData()->getCountPoints(); ++i )
			//{
			//	axChart2D1->ChartGroups[2]->Data->X[1,i+1] = arrayPoints[0][i];
			//	axChart2D1->ChartGroups[2]->Data->Y[1,i+1] = arrayPoints[1][i];
			//}

		}

		void drawGistogram(const metopt::CCompareData* _data)
		{
			int countPoints = _data->getSize();
			axChart2D1->ChartGroups[1]->Data->NumSeries = 1;
			axChart2D1->ChartGroups[1]->Data->NumPoints[1] = countPoints;
			axChart2D1->ChartGroups[2]->Data->NumSeries = 1;
			axChart2D1->ChartGroups[2]->Data->NumPoints[1] = 0;
			axChart2D1->ChartGroups[1]->ChartType = C1Chart2D8::ChartTypeConstants::oc2dTypeBar;

			double* arrayPoints = getCompareData(_data);
			double max_el = arrayPoints[0];
			for (int i = 0; i < countPoints; ++i)
			{
				if (arrayPoints[i] > max_el)
				{
					max_el = arrayPoints[i];
				}
			}

			for (int i = 0; i < countPoints; ++i)
			{
				axChart2D1->ChartGroups[1]->Data->X[1, i + 1] = i;
				axChart2D1->ChartGroups[1]->Data->Y[1, i + 1] = arrayPoints[i];
			}
		}
		
	
	public:

		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: AxC1Chart2D8::AxChart2D^  axChart2D1;
	private: System::Windows::Forms::Panel^  panel1;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::ListBox^  listBox1;
	private: System::Windows::Forms::Panel^  pnlFuncEditor;
	private: System::Windows::Forms::ComboBox^  cbMList;
	private: System::Windows::Forms::GroupBox^  groupBox3;
	private: System::Windows::Forms::RadioButton^  radioButton2;
	private: System::Windows::Forms::RadioButton^  radioButton1;
	private: System::Windows::Forms::ComboBox^  cbFList;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TabControl^  tabControl1;
	private: System::Windows::Forms::TabPage^  tabPage1;

	private: System::Windows::Forms::Button^  btnGenerate;
	private: System::Windows::Forms::TabPage^  tabPage2;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::TextBox^  tbFile;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Splitter^  splitter1;
	private: System::Windows::Forms::ToolBar^  tlbChart;
	private: System::Windows::Forms::ToolBarButton^  toolBarButton1;
	private: System::Windows::Forms::ToolBarButton^  toolBarButton11;
	private: System::Windows::Forms::ToolBarButton^  toolBarButton2;
	private: System::Windows::Forms::ToolBarButton^  toolBarButton4;
	private: System::Windows::Forms::ToolBarButton^  toolBarButton3;
	private: System::Windows::Forms::ToolBarButton^  toolBarButton5;
	private: System::Windows::Forms::ToolBarButton^  toolBarButton7;
	private: System::Windows::Forms::ToolBarButton^  toolBarButton6;
	private: System::Windows::Forms::ToolBarButton^  toolBarButton8;
	private: System::Windows::Forms::ToolBarButton^  toolBarButton9;
	private: System::Windows::Forms::ToolBarButton^  toolBarButton10;
	private: System::Windows::Forms::ToolBarButton^  toolBarButton14;
	private: System::Windows::Forms::ToolBarButton^  toolBarButton12;
	private: System::Windows::Forms::ToolBarButton^  toolBarButton13;
	private: System::Windows::Forms::StatusBar^  sbChart;
	private: System::Windows::Forms::StatusBarPanel^  sbpChart;
	private: System::Windows::Forms::StatusBarPanel^  sbpC1;

	private: System::Windows::Forms::ImageList^  imageList1;
	private: System::Windows::Forms::ContextMenu^  cmNCont;
	private: System::Windows::Forms::MenuItem^  menuItem24;
	private: System::Windows::Forms::MenuItem^  menuItem25;
	private: System::Windows::Forms::MenuItem^  menuItem26;
	private: System::Windows::Forms::MenuItem^  menuItem27;
	private: System::Windows::Forms::MenuItem^  menuItem28;
	private: System::Windows::Forms::MenuItem^  menuItem29;
	private: System::Windows::Forms::MenuItem^  menuItem30;
	private: System::Windows::Forms::MenuItem^  menuItem31;
	private: System::Windows::Forms::MenuItem^  menuItem32;
	private: System::Windows::Forms::ContextMenu^  cmContour;
	private: System::Windows::Forms::MenuItem^  menuItem19;
	private: System::Windows::Forms::MenuItem^  menuItem20;
	private: System::Windows::Forms::MenuItem^  menuItem21;
	private: System::Windows::Forms::MenuItem^  menuItem22;
	private: System::Windows::Forms::MenuItem^  menuItem23;
	private: System::Windows::Forms::MenuItem^  menuItem33;
	private: System::Windows::Forms::MenuItem^  menuItem34;
	private: System::Windows::Forms::MenuItem^  menuItem35;
	private: System::Windows::Forms::MenuItem^  menuItem36;
	private: System::Windows::Forms::MenuItem^  menuItem37;
	private: System::Windows::Forms::MenuItem^  menuItem38;
	private: System::Windows::Forms::ContextMenu^  cmView;
	private: System::Windows::Forms::MenuItem^  menuItem11;
	private: System::Windows::Forms::MenuItem^  menuItem18;
	private: System::Windows::Forms::MenuItem^  menuItem15;
	private: System::Windows::Forms::MenuItem^  menuItem16;
	private: System::Windows::Forms::MenuItem^  menuItem17;
	private: System::Windows::Forms::ContextMenu^  cmChartType;
	private: System::Windows::Forms::MenuItem^  menuItem14;
	private: System::Windows::Forms::MenuItem^  menuItem12;
	private: System::Windows::Forms::MenuItem^  menuItem13;
	private: System::ComponentModel::IContainer^  components;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->listBox1 = (gcnew System::Windows::Forms::ListBox());
			this->pnlFuncEditor = (gcnew System::Windows::Forms::Panel());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->btnGenerate = (gcnew System::Windows::Forms::Button());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->radioButton2 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton1 = (gcnew System::Windows::Forms::RadioButton());
			this->tabControl2 = (gcnew System::Windows::Forms::TabControl());
			this->tabPage3 = (gcnew System::Windows::Forms::TabPage());
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->groupBox6 = (gcnew System::Windows::Forms::GroupBox());
			this->comboBox2 = (gcnew System::Windows::Forms::ComboBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->textBox6 = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->groupBox5 = (gcnew System::Windows::Forms::GroupBox());
			this->numericUpDown3 = (gcnew System::Windows::Forms::NumericUpDown());
			this->numericUpDown2 = (gcnew System::Windows::Forms::NumericUpDown());
			this->numericUpDown1 = (gcnew System::Windows::Forms::NumericUpDown());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->textBox5 = (gcnew System::Windows::Forms::TextBox());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->textBox9 = (gcnew System::Windows::Forms::TextBox());
			this->textBox8 = (gcnew System::Windows::Forms::TextBox());
			this->textBox7 = (gcnew System::Windows::Forms::TextBox());
			this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->tbFile = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->cbMList = (gcnew System::Windows::Forms::ComboBox());
			this->cbFList = (gcnew System::Windows::Forms::ComboBox());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->tabPage4 = (gcnew System::Windows::Forms::TabPage());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->radioButton7 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton6 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton5 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton4 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton3 = (gcnew System::Windows::Forms::RadioButton());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->checkedListBox1 = (gcnew System::Windows::Forms::CheckedListBox());
			this->splitter1 = (gcnew System::Windows::Forms::Splitter());
			this->tlbChart = (gcnew System::Windows::Forms::ToolBar());
			this->toolBarButton1 = (gcnew System::Windows::Forms::ToolBarButton());
			this->cmChartType = (gcnew System::Windows::Forms::ContextMenu());
			this->menuItem14 = (gcnew System::Windows::Forms::MenuItem());
			this->menuItem12 = (gcnew System::Windows::Forms::MenuItem());
			this->menuItem13 = (gcnew System::Windows::Forms::MenuItem());
			this->toolBarButton11 = (gcnew System::Windows::Forms::ToolBarButton());
			this->cmView = (gcnew System::Windows::Forms::ContextMenu());
			this->menuItem11 = (gcnew System::Windows::Forms::MenuItem());
			this->menuItem18 = (gcnew System::Windows::Forms::MenuItem());
			this->menuItem15 = (gcnew System::Windows::Forms::MenuItem());
			this->menuItem16 = (gcnew System::Windows::Forms::MenuItem());
			this->menuItem17 = (gcnew System::Windows::Forms::MenuItem());
			this->toolBarButton2 = (gcnew System::Windows::Forms::ToolBarButton());
			this->toolBarButton4 = (gcnew System::Windows::Forms::ToolBarButton());
			this->toolBarButton3 = (gcnew System::Windows::Forms::ToolBarButton());
			this->toolBarButton5 = (gcnew System::Windows::Forms::ToolBarButton());
			this->toolBarButton7 = (gcnew System::Windows::Forms::ToolBarButton());
			this->toolBarButton6 = (gcnew System::Windows::Forms::ToolBarButton());
			this->toolBarButton8 = (gcnew System::Windows::Forms::ToolBarButton());
			this->toolBarButton9 = (gcnew System::Windows::Forms::ToolBarButton());
			this->toolBarButton10 = (gcnew System::Windows::Forms::ToolBarButton());
			this->toolBarButton14 = (gcnew System::Windows::Forms::ToolBarButton());
			this->toolBarButton12 = (gcnew System::Windows::Forms::ToolBarButton());
			this->cmContour = (gcnew System::Windows::Forms::ContextMenu());
			this->menuItem19 = (gcnew System::Windows::Forms::MenuItem());
			this->menuItem20 = (gcnew System::Windows::Forms::MenuItem());
			this->menuItem21 = (gcnew System::Windows::Forms::MenuItem());
			this->menuItem22 = (gcnew System::Windows::Forms::MenuItem());
			this->menuItem23 = (gcnew System::Windows::Forms::MenuItem());
			this->menuItem33 = (gcnew System::Windows::Forms::MenuItem());
			this->menuItem34 = (gcnew System::Windows::Forms::MenuItem());
			this->menuItem35 = (gcnew System::Windows::Forms::MenuItem());
			this->menuItem36 = (gcnew System::Windows::Forms::MenuItem());
			this->menuItem37 = (gcnew System::Windows::Forms::MenuItem());
			this->menuItem38 = (gcnew System::Windows::Forms::MenuItem());
			this->toolBarButton13 = (gcnew System::Windows::Forms::ToolBarButton());
			this->cmNCont = (gcnew System::Windows::Forms::ContextMenu());
			this->menuItem24 = (gcnew System::Windows::Forms::MenuItem());
			this->menuItem25 = (gcnew System::Windows::Forms::MenuItem());
			this->menuItem26 = (gcnew System::Windows::Forms::MenuItem());
			this->menuItem27 = (gcnew System::Windows::Forms::MenuItem());
			this->menuItem28 = (gcnew System::Windows::Forms::MenuItem());
			this->menuItem29 = (gcnew System::Windows::Forms::MenuItem());
			this->menuItem30 = (gcnew System::Windows::Forms::MenuItem());
			this->menuItem31 = (gcnew System::Windows::Forms::MenuItem());
			this->menuItem32 = (gcnew System::Windows::Forms::MenuItem());
			this->imageList1 = (gcnew System::Windows::Forms::ImageList(this->components));
			this->sbChart = (gcnew System::Windows::Forms::StatusBar());
			this->sbpChart = (gcnew System::Windows::Forms::StatusBarPanel());
			this->sbpC1 = (gcnew System::Windows::Forms::StatusBarPanel());
			this->axChart2D1 = (gcnew AxC1Chart2D8::AxChart2D());
			this->axChart3D1 = (gcnew AxC1Chart3D8::AxChart3D());
			this->panel1->SuspendLayout();
			this->pnlFuncEditor->SuspendLayout();
			this->groupBox3->SuspendLayout();
			this->tabControl2->SuspendLayout();
			this->tabPage3->SuspendLayout();
			this->tabControl1->SuspendLayout();
			this->tabPage1->SuspendLayout();
			this->groupBox6->SuspendLayout();
			this->groupBox5->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown3))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->BeginInit();
			this->tabPage2->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->groupBox4->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->tabPage4->SuspendLayout();
			this->panel2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->sbpChart))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->sbpC1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->axChart2D1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->axChart3D1))->BeginInit();
			this->SuspendLayout();
			// 
			// panel1
			// 
			this->panel1->Controls->Add(this->label8);
			this->panel1->Controls->Add(this->listBox1);
			this->panel1->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->panel1->Location = System::Drawing::Point(0, 538);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(884, 291);
			this->panel1->TabIndex = 3;
			// 
			// label8
			// 
			this->label8->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->label8->Dock = System::Windows::Forms::DockStyle::Top;
			this->label8->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->label8->Location = System::Drawing::Point(0, 0);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(884, 19);
			this->label8->TabIndex = 2;
			this->label8->Text = L"Result";
			// 
			// listBox1
			// 
			this->listBox1->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->listBox1->Font = (gcnew System::Drawing::Font(L"Courier New", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->listBox1->FormattingEnabled = true;
			this->listBox1->ItemHeight = 21;
			this->listBox1->Location = System::Drawing::Point(0, 14);
			this->listBox1->Name = L"listBox1";
			this->listBox1->Size = System::Drawing::Size(884, 277);
			this->listBox1->TabIndex = 1;
			// 
			// pnlFuncEditor
			// 
			this->pnlFuncEditor->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pnlFuncEditor->Controls->Add(this->label1);
			this->pnlFuncEditor->Controls->Add(this->btnGenerate);
			this->pnlFuncEditor->Controls->Add(this->groupBox3);
			this->pnlFuncEditor->Controls->Add(this->tabControl2);
			this->pnlFuncEditor->Dock = System::Windows::Forms::DockStyle::Left;
			this->pnlFuncEditor->Location = System::Drawing::Point(0, 0);
			this->pnlFuncEditor->Name = L"pnlFuncEditor";
			this->pnlFuncEditor->Size = System::Drawing::Size(240, 538);
			this->pnlFuncEditor->TabIndex = 4;
			// 
			// label1
			// 
			this->label1->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->label1->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->label1->Location = System::Drawing::Point(-1, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(238, 16);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Metods";
			// 
			// btnGenerate
			// 
			this->btnGenerate->Location = System::Drawing::Point(60, 492);
			this->btnGenerate->Name = L"btnGenerate";
			this->btnGenerate->Size = System::Drawing::Size(114, 36);
			this->btnGenerate->TabIndex = 1;
			this->btnGenerate->Text = L"Generate Chart";
			this->btnGenerate->Click += gcnew System::EventHandler(this, &Form1::btnGenerate_Click);
			// 
			// groupBox3
			// 
			this->groupBox3->Controls->Add(this->radioButton2);
			this->groupBox3->Controls->Add(this->radioButton1);
			this->groupBox3->Location = System::Drawing::Point(26, 19);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(211, 57);
			this->groupBox3->TabIndex = 4;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"Current Dimensional";
			// 
			// radioButton2
			// 
			this->radioButton2->AutoSize = true;
			this->radioButton2->Location = System::Drawing::Point(5, 33);
			this->radioButton2->Name = L"radioButton2";
			this->radioButton2->Size = System::Drawing::Size(144, 17);
			this->radioButton2->TabIndex = 1;
			this->radioButton2->Text = L"Multi Dimensional Search";
			this->radioButton2->UseVisualStyleBackColor = true;
			this->radioButton2->CheckedChanged += gcnew System::EventHandler(this, &Form1::radioButton2_CheckedChanged);
			// 
			// radioButton1
			// 
			this->radioButton1->AutoSize = true;
			this->radioButton1->Checked = true;
			this->radioButton1->Location = System::Drawing::Point(5, 15);
			this->radioButton1->Name = L"radioButton1";
			this->radioButton1->Size = System::Drawing::Size(142, 17);
			this->radioButton1->TabIndex = 0;
			this->radioButton1->TabStop = true;
			this->radioButton1->Text = L"One Dimensional Search";
			this->radioButton1->UseVisualStyleBackColor = true;
			this->radioButton1->CheckedChanged += gcnew System::EventHandler(this, &Form1::radioButton1_CheckedChanged);
			// 
			// tabControl2
			// 
			this->tabControl2->Alignment = System::Windows::Forms::TabAlignment::Left;
			this->tabControl2->Controls->Add(this->tabPage3);
			this->tabControl2->Controls->Add(this->tabPage4);
			this->tabControl2->Location = System::Drawing::Point(3, 19);
			this->tabControl2->Multiline = true;
			this->tabControl2->Name = L"tabControl2";
			this->tabControl2->SelectedIndex = 0;
			this->tabControl2->Size = System::Drawing::Size(236, 518);
			this->tabControl2->TabIndex = 14;
			this->tabControl2->Selected += gcnew System::Windows::Forms::TabControlEventHandler(this, &Form1::tabControl2_Selected);
			this->tabControl2->TabIndexChanged += gcnew System::EventHandler(this, &Form1::tabControl2_TabIndexChanged);
			// 
			// tabPage3
			// 
			this->tabPage3->Controls->Add(this->tabControl1);
			this->tabPage3->Controls->Add(this->label10);
			this->tabPage3->Controls->Add(this->cbMList);
			this->tabPage3->Controls->Add(this->cbFList);
			this->tabPage3->Controls->Add(this->label9);
			this->tabPage3->Location = System::Drawing::Point(23, 4);
			this->tabPage3->Name = L"tabPage3";
			this->tabPage3->Padding = System::Windows::Forms::Padding(3);
			this->tabPage3->Size = System::Drawing::Size(209, 510);
			this->tabPage3->TabIndex = 0;
			this->tabPage3->Text = L"Seatch";
			this->tabPage3->UseVisualStyleBackColor = true;
			// 
			// tabControl1
			// 
			this->tabControl1->Controls->Add(this->tabPage1);
			this->tabControl1->Controls->Add(this->tabPage2);
			this->tabControl1->Location = System::Drawing::Point(3, 139);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(203, 328);
			this->tabControl1->TabIndex = 0;
			// 
			// tabPage1
			// 
			this->tabPage1->Controls->Add(this->groupBox6);
			this->tabPage1->Controls->Add(this->groupBox5);
			this->tabPage1->Controls->Add(this->label12);
			this->tabPage1->Controls->Add(this->textBox5);
			this->tabPage1->Controls->Add(this->label11);
			this->tabPage1->Controls->Add(this->textBox4);
			this->tabPage1->Location = System::Drawing::Point(4, 22);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Size = System::Drawing::Size(195, 302);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = L"Method Settings";
			// 
			// groupBox6
			// 
			this->groupBox6->Controls->Add(this->comboBox2);
			this->groupBox6->Controls->Add(this->label4);
			this->groupBox6->Controls->Add(this->textBox6);
			this->groupBox6->Controls->Add(this->label3);
			this->groupBox6->Location = System::Drawing::Point(6, 217);
			this->groupBox6->Name = L"groupBox6";
			this->groupBox6->Size = System::Drawing::Size(186, 87);
			this->groupBox6->TabIndex = 14;
			this->groupBox6->TabStop = false;
			this->groupBox6->Text = L"One Dimensional Method";
			this->groupBox6->Visible = false;
			// 
			// comboBox2
			// 
			this->comboBox2->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBox2->Location = System::Drawing::Point(7, 60);
			this->comboBox2->MaxDropDownItems = 10;
			this->comboBox2->Name = L"comboBox2";
			this->comboBox2->Size = System::Drawing::Size(173, 21);
			this->comboBox2->TabIndex = 15;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(6, 42);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(62, 13);
			this->label4->TabIndex = 14;
			this->label4->Text = L"Method List";
			// 
			// textBox6
			// 
			this->textBox6->Location = System::Drawing::Point(65, 19);
			this->textBox6->Name = L"textBox6";
			this->textBox6->Size = System::Drawing::Size(115, 20);
			this->textBox6->TabIndex = 12;
			this->textBox6->Text = L"0,01";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(9, 18);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(50, 13);
			this->label3->TabIndex = 13;
			this->label3->Text = L"Precision";
			// 
			// groupBox5
			// 
			this->groupBox5->Controls->Add(this->numericUpDown3);
			this->groupBox5->Controls->Add(this->numericUpDown2);
			this->groupBox5->Controls->Add(this->numericUpDown1);
			this->groupBox5->Controls->Add(this->label16);
			this->groupBox5->Controls->Add(this->comboBox1);
			this->groupBox5->Controls->Add(this->label15);
			this->groupBox5->Controls->Add(this->label14);
			this->groupBox5->Controls->Add(this->label13);
			this->groupBox5->Location = System::Drawing::Point(6, 67);
			this->groupBox5->Name = L"groupBox5";
			this->groupBox5->Size = System::Drawing::Size(200, 142);
			this->groupBox5->TabIndex = 11;
			this->groupBox5->TabStop = false;
			this->groupBox5->Text = L"Conditions of Exit";
			// 
			// numericUpDown3
			// 
			this->numericUpDown3->Location = System::Drawing::Point(87, 70);
			this->numericUpDown3->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10000, 0, 0, 0 });
			this->numericUpDown3->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->numericUpDown3->Name = L"numericUpDown3";
			this->numericUpDown3->Size = System::Drawing::Size(99, 20);
			this->numericUpDown3->TabIndex = 18;
			this->numericUpDown3->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10000, 0, 0, 0 });
			// 
			// numericUpDown2
			// 
			this->numericUpDown2->Location = System::Drawing::Point(87, 44);
			this->numericUpDown2->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10000, 0, 0, 0 });
			this->numericUpDown2->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->numericUpDown2->Name = L"numericUpDown2";
			this->numericUpDown2->Size = System::Drawing::Size(99, 20);
			this->numericUpDown2->TabIndex = 17;
			this->numericUpDown2->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 200, 0, 0, 0 });
			// 
			// numericUpDown1
			// 
			this->numericUpDown1->Location = System::Drawing::Point(87, 18);
			this->numericUpDown1->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10000, 0, 0, 0 });
			this->numericUpDown1->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->numericUpDown1->Name = L"numericUpDown1";
			this->numericUpDown1->Size = System::Drawing::Size(99, 20);
			this->numericUpDown1->TabIndex = 16;
			this->numericUpDown1->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, 0 });
			// 
			// label16
			// 
			this->label16->AutoSize = true;
			this->label16->Location = System::Drawing::Point(6, 102);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(47, 13);
			this->label16->TabIndex = 15;
			this->label16->Text = L"Flag Exit";
			// 
			// comboBox1
			// 
			this->comboBox1->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->comboBox1->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBox1->Location = System::Drawing::Point(6, 116);
			this->comboBox1->MaxDropDownItems = 10;
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(180, 21);
			this->comboBox1->TabIndex = 8;
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Location = System::Drawing::Point(4, 72);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(49, 13);
			this->label15->TabIndex = 14;
			this->label15->Text = L"maxTime";
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Location = System::Drawing::Point(3, 46);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(71, 13);
			this->label14->TabIndex = 13;
			this->label14->Text = L"maxFuncCalc";
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Location = System::Drawing::Point(4, 20);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(64, 13);
			this->label13->TabIndex = 12;
			this->label13->Text = L"maxIteration";
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Location = System::Drawing::Point(3, 41);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(29, 13);
			this->label12->TabIndex = 10;
			this->label12->Text = L"Step";
			// 
			// textBox5
			// 
			this->textBox5->Location = System::Drawing::Point(73, 41);
			this->textBox5->Name = L"textBox5";
			this->textBox5->Size = System::Drawing::Size(119, 20);
			this->textBox5->TabIndex = 9;
			this->textBox5->Text = L"0,1";
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(3, 15);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(50, 13);
			this->label11->TabIndex = 8;
			this->label11->Text = L"Precision";
			// 
			// textBox4
			// 
			this->textBox4->Location = System::Drawing::Point(73, 15);
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(119, 20);
			this->textBox4->TabIndex = 8;
			this->textBox4->Text = L"0,01";
			// 
			// tabPage2
			// 
			this->tabPage2->Controls->Add(this->groupBox2);
			this->tabPage2->Controls->Add(this->groupBox4);
			this->tabPage2->Controls->Add(this->groupBox1);
			this->tabPage2->Location = System::Drawing::Point(4, 22);
			this->tabPage2->Name = L"tabPage2";
			this->tabPage2->Size = System::Drawing::Size(195, 302);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = L"Function Settings";
			// 
			// groupBox2
			// 
			this->groupBox2->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->groupBox2->Controls->Add(this->textBox3);
			this->groupBox2->Controls->Add(this->textBox9);
			this->groupBox2->Controls->Add(this->textBox8);
			this->groupBox2->Controls->Add(this->textBox7);
			this->groupBox2->Location = System::Drawing::Point(-7, 93);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(200, 75);
			this->groupBox2->TabIndex = 8;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Interval [a,b]";
			this->groupBox2->Visible = false;
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(108, 45);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(78, 20);
			this->textBox3->TabIndex = 9;
			this->textBox3->Text = L"2";
			// 
			// textBox9
			// 
			this->textBox9->Location = System::Drawing::Point(11, 45);
			this->textBox9->Name = L"textBox9";
			this->textBox9->Size = System::Drawing::Size(78, 20);
			this->textBox9->TabIndex = 8;
			this->textBox9->Text = L"5";
			// 
			// textBox8
			// 
			this->textBox8->Location = System::Drawing::Point(108, 19);
			this->textBox8->Name = L"textBox8";
			this->textBox8->Size = System::Drawing::Size(77, 20);
			this->textBox8->TabIndex = 7;
			this->textBox8->Text = L"-1";
			// 
			// textBox7
			// 
			this->textBox7->Location = System::Drawing::Point(11, 19);
			this->textBox7->Name = L"textBox7";
			this->textBox7->Size = System::Drawing::Size(77, 20);
			this->textBox7->TabIndex = 6;
			this->textBox7->Text = L"-2";
			// 
			// groupBox4
			// 
			this->groupBox4->Controls->Add(this->textBox2);
			this->groupBox4->Controls->Add(this->textBox1);
			this->groupBox4->Location = System::Drawing::Point(3, 13);
			this->groupBox4->Name = L"groupBox4";
			this->groupBox4->Size = System::Drawing::Size(208, 74);
			this->groupBox4->TabIndex = 9;
			this->groupBox4->TabStop = false;
			this->groupBox4->Text = L"Initial Point";
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(19, 42);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(170, 20);
			this->textBox2->TabIndex = 4;
			this->textBox2->Text = L"1,0";
			this->textBox2->TextChanged += gcnew System::EventHandler(this, &Form1::textBox2_TextChanged);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(19, 16);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(170, 20);
			this->textBox1->TabIndex = 3;
			this->textBox1->Text = L"-1,0";
			// 
			// groupBox1
			// 
			this->groupBox1->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->groupBox1->Controls->Add(this->checkBox1);
			this->groupBox1->Controls->Add(this->tbFile);
			this->groupBox1->Controls->Add(this->label2);
			this->groupBox1->Location = System::Drawing::Point(-7, 202);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(200, 97);
			this->groupBox1->TabIndex = 0;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Save in File";
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->Location = System::Drawing::Point(11, 28);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(51, 17);
			this->checkBox1->TabIndex = 7;
			this->checkBox1->Text = L"Save";
			this->checkBox1->UseVisualStyleBackColor = true;
			// 
			// tbFile
			// 
			this->tbFile->Location = System::Drawing::Point(11, 71);
			this->tbFile->Name = L"tbFile";
			this->tbFile->Size = System::Drawing::Size(175, 20);
			this->tbFile->TabIndex = 6;
			this->tbFile->Text = L"Method.log";
			// 
			// label2
			// 
			this->label2->Location = System::Drawing::Point(6, 50);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(68, 23);
			this->label2->TabIndex = 1;
			this->label2->Text = L"Name File";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(2, 96);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(67, 13);
			this->label10->TabIndex = 7;
			this->label10->Text = L"Function List";
			this->label10->Click += gcnew System::EventHandler(this, &Form1::label10_Click);
			// 
			// cbMList
			// 
			this->cbMList->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cbMList->Location = System::Drawing::Point(3, 72);
			this->cbMList->MaxDropDownItems = 10;
			this->cbMList->Name = L"cbMList";
			this->cbMList->Size = System::Drawing::Size(204, 21);
			this->cbMList->TabIndex = 5;
			// 
			// cbFList
			// 
			this->cbFList->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cbFList->Location = System::Drawing::Point(3, 112);
			this->cbFList->MaxDropDownItems = 10;
			this->cbFList->Name = L"cbFList";
			this->cbFList->Size = System::Drawing::Size(204, 21);
			this->cbFList->TabIndex = 3;
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(6, 56);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(62, 13);
			this->label9->TabIndex = 6;
			this->label9->Text = L"Method List";
			// 
			// tabPage4
			// 
			this->tabPage4->Controls->Add(this->panel2);
			this->tabPage4->Controls->Add(this->label6);
			this->tabPage4->Controls->Add(this->label5);
			this->tabPage4->Controls->Add(this->checkedListBox1);
			this->tabPage4->Location = System::Drawing::Point(23, 4);
			this->tabPage4->Name = L"tabPage4";
			this->tabPage4->Padding = System::Windows::Forms::Padding(3);
			this->tabPage4->Size = System::Drawing::Size(209, 510);
			this->tabPage4->TabIndex = 1;
			this->tabPage4->Text = L"Compare";
			this->tabPage4->UseVisualStyleBackColor = true;
			// 
			// panel2
			// 
			this->panel2->Controls->Add(this->radioButton7);
			this->panel2->Controls->Add(this->radioButton6);
			this->panel2->Controls->Add(this->radioButton5);
			this->panel2->Controls->Add(this->radioButton4);
			this->panel2->Controls->Add(this->radioButton3);
			this->panel2->Location = System::Drawing::Point(12, 289);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(187, 120);
			this->panel2->TabIndex = 17;
			// 
			// radioButton7
			// 
			this->radioButton7->AutoSize = true;
			this->radioButton7->Location = System::Drawing::Point(3, 98);
			this->radioButton7->Name = L"radioButton7";
			this->radioButton7->Size = System::Drawing::Size(87, 17);
			this->radioButton7->TabIndex = 4;
			this->radioButton7->TabStop = true;
			this->radioButton7->Text = L"Precision Arg";
			this->radioButton7->UseVisualStyleBackColor = true;
			// 
			// radioButton6
			// 
			this->radioButton6->AutoSize = true;
			this->radioButton6->Location = System::Drawing::Point(4, 74);
			this->radioButton6->Name = L"radioButton6";
			this->radioButton6->Size = System::Drawing::Size(95, 17);
			this->radioButton6->TabIndex = 3;
			this->radioButton6->TabStop = true;
			this->radioButton6->Text = L"Precision Func";
			this->radioButton6->UseVisualStyleBackColor = true;
			// 
			// radioButton5
			// 
			this->radioButton5->AutoSize = true;
			this->radioButton5->Location = System::Drawing::Point(4, 51);
			this->radioButton5->Name = L"radioButton5";
			this->radioButton5->Size = System::Drawing::Size(85, 17);
			this->radioButton5->TabIndex = 2;
			this->radioButton5->Text = L"Elapsed time";
			this->radioButton5->UseVisualStyleBackColor = true;
			// 
			// radioButton4
			// 
			this->radioButton4->AutoSize = true;
			this->radioButton4->Location = System::Drawing::Point(3, 27);
			this->radioButton4->Name = L"radioButton4";
			this->radioButton4->Size = System::Drawing::Size(93, 17);
			this->radioButton4->TabIndex = 1;
			this->radioButton4->Text = L"Count iteration";
			this->radioButton4->UseVisualStyleBackColor = true;
			// 
			// radioButton3
			// 
			this->radioButton3->AutoSize = true;
			this->radioButton3->Checked = true;
			this->radioButton3->Location = System::Drawing::Point(3, 3);
			this->radioButton3->Name = L"radioButton3";
			this->radioButton3->Size = System::Drawing::Size(104, 17);
			this->radioButton3->TabIndex = 0;
			this->radioButton3->TabStop = true;
			this->radioButton3->Text = L"Count Calc Func";
			this->radioButton3->UseVisualStyleBackColor = true;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(9, 273);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(100, 13);
			this->label6->TabIndex = 16;
			this->label6->Text = L"Compate Parameter";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(6, 63);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(62, 13);
			this->label5->TabIndex = 14;
			this->label5->Text = L"Method List";
			// 
			// checkedListBox1
			// 
			this->checkedListBox1->FormattingEnabled = true;
			this->checkedListBox1->Location = System::Drawing::Point(6, 79);
			this->checkedListBox1->Name = L"checkedListBox1";
			this->checkedListBox1->Size = System::Drawing::Size(197, 169);
			this->checkedListBox1->TabIndex = 13;
			this->checkedListBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::checkedListBox1_SelectedIndexChanged);
			// 
			// splitter1
			// 
			this->splitter1->Location = System::Drawing::Point(240, 0);
			this->splitter1->MinSize = 220;
			this->splitter1->Name = L"splitter1";
			this->splitter1->Size = System::Drawing::Size(10, 516);
			this->splitter1->TabIndex = 5;
			this->splitter1->TabStop = false;
			// 
			// tlbChart
			// 
			this->tlbChart->Appearance = System::Windows::Forms::ToolBarAppearance::Flat;
			this->tlbChart->Buttons->AddRange(gcnew cli::array< System::Windows::Forms::ToolBarButton^  >(14) {
				this->toolBarButton1, this->toolBarButton11,
					this->toolBarButton2, this->toolBarButton4, this->toolBarButton3, this->toolBarButton5, this->toolBarButton7, this->toolBarButton6,
					this->toolBarButton8, this->toolBarButton9, this->toolBarButton10, this->toolBarButton14, this->toolBarButton12, this->toolBarButton13
			});
			this->tlbChart->DropDownArrows = true;
			this->tlbChart->ImageList = this->imageList1;
			this->tlbChart->Location = System::Drawing::Point(250, 0);
			this->tlbChart->Name = L"tlbChart";
			this->tlbChart->ShowToolTips = true;
			this->tlbChart->Size = System::Drawing::Size(634, 28);
			this->tlbChart->TabIndex = 10;
			this->tlbChart->TextAlign = System::Windows::Forms::ToolBarTextAlign::Right;
			this->tlbChart->ButtonClick += gcnew System::Windows::Forms::ToolBarButtonClickEventHandler(this, &Form1::tlbChart_ButtonClick);
			// 
			// toolBarButton1
			// 
			this->toolBarButton1->DropDownMenu = this->cmChartType;
			this->toolBarButton1->ImageIndex = 0;
			this->toolBarButton1->Name = L"toolBarButton1";
			this->toolBarButton1->Style = System::Windows::Forms::ToolBarButtonStyle::DropDownButton;
			this->toolBarButton1->ToolTipText = L"Chart type";
			// 
			// cmChartType
			// 
			this->cmChartType->MenuItems->AddRange(gcnew cli::array< System::Windows::Forms::MenuItem^  >(3) {
				this->menuItem14, this->menuItem12,
					this->menuItem13
			});
			// 
			// menuItem14
			// 
			this->menuItem14->Index = 0;
			this->menuItem14->RadioCheck = true;
			this->menuItem14->Text = L"Bar";
			this->menuItem14->Click += gcnew System::EventHandler(this, &Form1::menuItem14_Click);
			// 
			// menuItem12
			// 
			this->menuItem12->Index = 1;
			this->menuItem12->RadioCheck = true;
			this->menuItem12->Text = L"Scatter";
			this->menuItem12->Click += gcnew System::EventHandler(this, &Form1::menuItem12_Click);
			// 
			// menuItem13
			// 
			this->menuItem13->Checked = true;
			this->menuItem13->Index = 2;
			this->menuItem13->RadioCheck = true;
			this->menuItem13->Text = L"Surface";
			this->menuItem13->Click += gcnew System::EventHandler(this, &Form1::menuItem13_Click);
			// 
			// toolBarButton11
			// 
			this->toolBarButton11->DropDownMenu = this->cmView;
			this->toolBarButton11->ImageIndex = 9;
			this->toolBarButton11->Name = L"toolBarButton11";
			this->toolBarButton11->Style = System::Windows::Forms::ToolBarButtonStyle::DropDownButton;
			this->toolBarButton11->ToolTipText = L"View";
			// 
			// cmView
			// 
			this->cmView->MenuItems->AddRange(gcnew cli::array< System::Windows::Forms::MenuItem^  >(5) {
				this->menuItem11, this->menuItem18,
					this->menuItem15, this->menuItem16, this->menuItem17
			});
			// 
			// menuItem11
			// 
			this->menuItem11->Checked = true;
			this->menuItem11->Index = 0;
			this->menuItem11->RadioCheck = true;
			this->menuItem11->Text = L"3D - Default";
			this->menuItem11->Click += gcnew System::EventHandler(this, &Form1::menuItem11_Click);
			// 
			// menuItem18
			// 
			this->menuItem18->Index = 1;
			this->menuItem18->Text = L"-";
			// 
			// menuItem15
			// 
			this->menuItem15->Index = 2;
			this->menuItem15->RadioCheck = true;
			this->menuItem15->Text = L"2D - XY plane";
			this->menuItem15->Click += gcnew System::EventHandler(this, &Form1::menuItem15_Click);
			// 
			// menuItem16
			// 
			this->menuItem16->Index = 3;
			this->menuItem16->RadioCheck = true;
			this->menuItem16->Text = L"2D - XZ plane";
			this->menuItem16->Click += gcnew System::EventHandler(this, &Form1::menuItem16_Click);
			// 
			// menuItem17
			// 
			this->menuItem17->Index = 4;
			this->menuItem17->RadioCheck = true;
			this->menuItem17->Text = L"2D - YZ plane";
			this->menuItem17->Click += gcnew System::EventHandler(this, &Form1::menuItem17_Click);
			// 
			// toolBarButton2
			// 
			this->toolBarButton2->Name = L"toolBarButton2";
			this->toolBarButton2->Style = System::Windows::Forms::ToolBarButtonStyle::Separator;
			// 
			// toolBarButton4
			// 
			this->toolBarButton4->ImageIndex = 5;
			this->toolBarButton4->Name = L"toolBarButton4";
			this->toolBarButton4->ToolTipText = L"Rotation Z";
			// 
			// toolBarButton3
			// 
			this->toolBarButton3->ImageIndex = 1;
			this->toolBarButton3->Name = L"toolBarButton3";
			this->toolBarButton3->ToolTipText = L"Rotation Z";
			// 
			// toolBarButton5
			// 
			this->toolBarButton5->Name = L"toolBarButton5";
			this->toolBarButton5->Style = System::Windows::Forms::ToolBarButtonStyle::Separator;
			// 
			// toolBarButton7
			// 
			this->toolBarButton7->ImageIndex = 6;
			this->toolBarButton7->Name = L"toolBarButton7";
			this->toolBarButton7->ToolTipText = L"Rotation X";
			// 
			// toolBarButton6
			// 
			this->toolBarButton6->ImageIndex = 2;
			this->toolBarButton6->Name = L"toolBarButton6";
			this->toolBarButton6->ToolTipText = L"Rotation X";
			// 
			// toolBarButton8
			// 
			this->toolBarButton8->Name = L"toolBarButton8";
			this->toolBarButton8->Style = System::Windows::Forms::ToolBarButtonStyle::Separator;
			// 
			// toolBarButton9
			// 
			this->toolBarButton9->ImageIndex = 7;
			this->toolBarButton9->Name = L"toolBarButton9";
			this->toolBarButton9->Pushed = true;
			this->toolBarButton9->Style = System::Windows::Forms::ToolBarButtonStyle::ToggleButton;
			this->toolBarButton9->ToolTipText = L"Grid";
			// 
			// toolBarButton10
			// 
			this->toolBarButton10->ImageIndex = 8;
			this->toolBarButton10->Name = L"toolBarButton10";
			this->toolBarButton10->Pushed = true;
			this->toolBarButton10->Style = System::Windows::Forms::ToolBarButtonStyle::ToggleButton;
			this->toolBarButton10->ToolTipText = L"Axes";
			// 
			// toolBarButton14
			// 
			this->toolBarButton14->Name = L"toolBarButton14";
			this->toolBarButton14->Style = System::Windows::Forms::ToolBarButtonStyle::Separator;
			// 
			// toolBarButton12
			// 
			this->toolBarButton12->DropDownMenu = this->cmContour;
			this->toolBarButton12->ImageIndex = 10;
			this->toolBarButton12->Name = L"toolBarButton12";
			this->toolBarButton12->Style = System::Windows::Forms::ToolBarButtonStyle::DropDownButton;
			this->toolBarButton12->ToolTipText = L"Zone colors";
			// 
			// cmContour
			// 
			this->cmContour->MenuItems->AddRange(gcnew cli::array< System::Windows::Forms::MenuItem^  >(11) {
				this->menuItem19, this->menuItem20,
					this->menuItem21, this->menuItem22, this->menuItem23, this->menuItem33, this->menuItem34, this->menuItem35, this->menuItem36,
					this->menuItem37, this->menuItem38
			});
			// 
			// menuItem19
			// 
			this->menuItem19->Checked = true;
			this->menuItem19->Index = 0;
			this->menuItem19->RadioCheck = true;
			this->menuItem19->Text = L"None";
			// 
			// menuItem20
			// 
			this->menuItem20->Index = 1;
			this->menuItem20->RadioCheck = true;
			this->menuItem20->Text = L"Rainbow";
			// 
			// menuItem21
			// 
			this->menuItem21->Index = 2;
			this->menuItem21->RadioCheck = true;
			this->menuItem21->Text = L"RevRainbow";
			// 
			// menuItem22
			// 
			this->menuItem22->Index = 3;
			this->menuItem22->RadioCheck = true;
			this->menuItem22->Text = L"Black -> White";
			// 
			// menuItem23
			// 
			this->menuItem23->Index = 4;
			this->menuItem23->RadioCheck = true;
			this->menuItem23->Text = L"White -> Black";
			// 
			// menuItem33
			// 
			this->menuItem33->Index = 5;
			this->menuItem33->RadioCheck = true;
			this->menuItem33->Text = L"Green -> Blue";
			// 
			// menuItem34
			// 
			this->menuItem34->Index = 6;
			this->menuItem34->RadioCheck = true;
			this->menuItem34->Text = L"Red -> White";
			// 
			// menuItem35
			// 
			this->menuItem35->Index = 7;
			this->menuItem35->RadioCheck = true;
			this->menuItem35->Text = L"Blue -> Pink";
			// 
			// menuItem36
			// 
			this->menuItem36->Index = 8;
			this->menuItem36->RadioCheck = true;
			this->menuItem36->Text = L"Blue -> White -> Red";
			// 
			// menuItem37
			// 
			this->menuItem37->Index = 9;
			this->menuItem37->RadioCheck = true;
			this->menuItem37->Text = L"Black -> Red ->Yellow";
			// 
			// menuItem38
			// 
			this->menuItem38->Index = 10;
			this->menuItem38->RadioCheck = true;
			this->menuItem38->Text = L"Green -> Purple -> Yellow";
			// 
			// toolBarButton13
			// 
			this->toolBarButton13->DropDownMenu = this->cmNCont;
			this->toolBarButton13->ImageIndex = 11;
			this->toolBarButton13->Name = L"toolBarButton13";
			this->toolBarButton13->Style = System::Windows::Forms::ToolBarButtonStyle::DropDownButton;
			this->toolBarButton13->ToolTipText = L"Number of levels";
			// 
			// cmNCont
			// 
			this->cmNCont->MenuItems->AddRange(gcnew cli::array< System::Windows::Forms::MenuItem^  >(9) {
				this->menuItem24, this->menuItem25,
					this->menuItem26, this->menuItem27, this->menuItem28, this->menuItem29, this->menuItem30, this->menuItem31, this->menuItem32
			});
			// 
			// menuItem24
			// 
			this->menuItem24->Index = 0;
			this->menuItem24->RadioCheck = true;
			this->menuItem24->Text = L"10";
			// 
			// menuItem25
			// 
			this->menuItem25->Index = 1;
			this->menuItem25->RadioCheck = true;
			this->menuItem25->Text = L"15";
			// 
			// menuItem26
			// 
			this->menuItem26->Checked = true;
			this->menuItem26->Index = 2;
			this->menuItem26->RadioCheck = true;
			this->menuItem26->Text = L"20";
			// 
			// menuItem27
			// 
			this->menuItem27->Index = 3;
			this->menuItem27->RadioCheck = true;
			this->menuItem27->Text = L"25";
			// 
			// menuItem28
			// 
			this->menuItem28->Index = 4;
			this->menuItem28->RadioCheck = true;
			this->menuItem28->Text = L"30";
			// 
			// menuItem29
			// 
			this->menuItem29->Index = 5;
			this->menuItem29->RadioCheck = true;
			this->menuItem29->Text = L"35";
			// 
			// menuItem30
			// 
			this->menuItem30->Index = 6;
			this->menuItem30->RadioCheck = true;
			this->menuItem30->Text = L"40";
			// 
			// menuItem31
			// 
			this->menuItem31->Index = 7;
			this->menuItem31->RadioCheck = true;
			this->menuItem31->Text = L"45";
			// 
			// menuItem32
			// 
			this->menuItem32->Index = 8;
			this->menuItem32->RadioCheck = true;
			this->menuItem32->Text = L"50";
			// 
			// imageList1
			// 
			this->imageList1->ImageStream = (cli::safe_cast<System::Windows::Forms::ImageListStreamer^>(resources->GetObject(L"imageList1.ImageStream")));
			this->imageList1->TransparentColor = System::Drawing::Color::White;
			this->imageList1->Images->SetKeyName(0, L"");
			this->imageList1->Images->SetKeyName(1, L"");
			this->imageList1->Images->SetKeyName(2, L"");
			this->imageList1->Images->SetKeyName(3, L"");
			this->imageList1->Images->SetKeyName(4, L"");
			this->imageList1->Images->SetKeyName(5, L"");
			this->imageList1->Images->SetKeyName(6, L"");
			this->imageList1->Images->SetKeyName(7, L"");
			this->imageList1->Images->SetKeyName(8, L"");
			this->imageList1->Images->SetKeyName(9, L"");
			this->imageList1->Images->SetKeyName(10, L"");
			this->imageList1->Images->SetKeyName(11, L"");
			// 
			// sbChart
			// 
			this->sbChart->Location = System::Drawing::Point(240, 516);
			this->sbChart->Name = L"sbChart";
			this->sbChart->Panels->AddRange(gcnew cli::array< System::Windows::Forms::StatusBarPanel^  >(2) { this->sbpChart, this->sbpC1 });
			this->sbChart->ShowPanels = true;
			this->sbChart->Size = System::Drawing::Size(644, 22);
			this->sbChart->TabIndex = 9;
			this->sbChart->Text = L"Ready";
			// 
			// sbpChart
			// 
			this->sbpChart->AutoSize = System::Windows::Forms::StatusBarPanelAutoSize::Spring;
			this->sbpChart->BorderStyle = System::Windows::Forms::StatusBarPanelBorderStyle::None;
			this->sbpChart->Name = L"sbpChart";
			this->sbpChart->Text = L"Ready";
			this->sbpChart->Width = 597;
			// 
			// sbpC1
			// 
			this->sbpC1->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"sbpC1.Icon")));
			this->sbpC1->MinWidth = 30;
			this->sbpC1->Name = L"sbpC1";
			this->sbpC1->Width = 30;
			// 
			// axChart2D1
			// 
			this->axChart2D1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->axChart2D1->Enabled = true;
			this->axChart2D1->Location = System::Drawing::Point(240, 0);
			this->axChart2D1->Name = L"axChart2D1";
			this->axChart2D1->OcxState = (cli::safe_cast<System::Windows::Forms::AxHost::State^>(resources->GetObject(L"axChart2D1.OcxState")));
			this->axChart2D1->Size = System::Drawing::Size(644, 516);
			this->axChart2D1->TabIndex = 11;
			// 
			// axChart3D1
			// 
			this->axChart3D1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->axChart3D1->Enabled = true;
			this->axChart3D1->Location = System::Drawing::Point(250, 0);
			this->axChart3D1->Name = L"axChart3D1";
			this->axChart3D1->OcxState = (cli::safe_cast<System::Windows::Forms::AxHost::State^>(resources->GetObject(L"axChart3D1.OcxState")));
			this->axChart3D1->Size = System::Drawing::Size(634, 516);
			this->axChart3D1->TabIndex = 12;
			this->axChart3D1->Visible = false;
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(884, 829);
			this->Controls->Add(this->tlbChart);
			this->Controls->Add(this->axChart3D1);
			this->Controls->Add(this->splitter1);
			this->Controls->Add(this->axChart2D1);
			this->Controls->Add(this->sbChart);
			this->Controls->Add(this->pnlFuncEditor);
			this->Controls->Add(this->panel1);
			this->Name = L"Form1";
			this->Text = L"Methods Demo";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->panel1->ResumeLayout(false);
			this->pnlFuncEditor->ResumeLayout(false);
			this->groupBox3->ResumeLayout(false);
			this->groupBox3->PerformLayout();
			this->tabControl2->ResumeLayout(false);
			this->tabPage3->ResumeLayout(false);
			this->tabPage3->PerformLayout();
			this->tabControl1->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->tabPage1->PerformLayout();
			this->groupBox6->ResumeLayout(false);
			this->groupBox6->PerformLayout();
			this->groupBox5->ResumeLayout(false);
			this->groupBox5->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown3))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->EndInit();
			this->tabPage2->ResumeLayout(false);
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->groupBox4->ResumeLayout(false);
			this->groupBox4->PerformLayout();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->tabPage4->ResumeLayout(false);
			this->tabPage4->PerformLayout();
			this->panel2->ResumeLayout(false);
			this->panel2->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->sbpChart))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->sbpC1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->axChart2D1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->axChart3D1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
private: System::Void tlbChart_ButtonClick(System::Object^  sender, System::Windows::Forms::ToolBarButtonClickEventArgs^  e) 
		 {
			 int rot_inc = 5;
			 switch(tlbChart->Buttons->IndexOf( e->Button ))
			 {
			 	case 0:
			 		selectNext( cmChartType );
			 		break;
			 	case 1:
			 		selectNext( cmView );
			 		break;
			 	case 4:
			 		rotz += rot_inc;
			 		if( rotz>360)
			 			rotz -= 360;
					axChart3D1->ChartArea->View3D->ZRotation = rotz;
			 		//c1Chart3D1->ChartArea->View->RotationZ = rotz;
			 		break;
			 	case 3:
			 		rotz -= rot_inc;
			 		if( rotz<0)
			 			rotz += 360;
					axChart3D1->ChartArea->View3D->ZRotation = rotz;
			 		//c1Chart3D1->ChartArea->View->RotationZ = rotz;
			 		break;
			 	case 6:
			 		rotx += rot_inc;
			 		if( rotx>360)
			 			rotx -= 360;
					axChart3D1->ChartArea->View3D->XRotation = rotx;
			 		//c1Chart3D1->ChartArea->View->RotationX = rotx;
			 		break;
			 	case 7:
			 		rotx -= rot_inc;
			 		if( rotx<0)
			 			rotx += 360;
					axChart3D1->ChartArea->View3D->XRotation = rotx;
			 		//c1Chart3D1->ChartArea->View->RotationX = rotx;
			 		break;
			 	case 9:
			 		//c1Chart3D1->ChartGroups[0]->Elevation->IsMeshed = !c1Chart3D1->ChartGroups[0]->Elevation->IsMeshed;
			 		break;
			 	case 10:
			 		//c1Chart3D1->ChartArea->AxisX->Visible = !c1Chart3D1->ChartArea->AxisX->Visible;
			 		//c1Chart3D1->ChartArea->AxisY->Visible = !c1Chart3D1->ChartArea->AxisY->Visible;
			 		//c1Chart3D1->ChartArea->AxisZ->Visible = !c1Chart3D1->ChartArea->AxisZ->Visible;
			 		break;
			 	case 12:
			 		selectNext( cmContour);
			 		break;
			 	case 13:
			 		selectNext( cmNCont);
			 		break;
			 	default:
			 		break;
			 }
		 }
/************************************************************************/
/*						Chart Type                                      */
/************************************************************************/
private: System::Void menuItem14_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 //c1Chart3D1->ChartGroups[0]->ChartType = C1::Win::C1Chart3D::Chart3DTypeEnum::Bar;
			 axChart3D1->ChartGroups[1]->ChartType = C1Chart3D8::ChartTypeConstants::oc3dTypeBar;
			 menuItem14->Checked = true;
			 menuItem12->Checked = false;
			 menuItem13->Checked = false;
		 }
private: System::Void menuItem12_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 //c1Chart3D1->ChartGroups[0]->ChartType = C1::Win::C1Chart3D::Chart3DTypeEnum::Scatter;
			 axChart3D1->ChartGroups[1]->ChartType = C1Chart3D8::ChartTypeConstants::oc3dTypeScatter;
			 menuItem14->Checked = false;
			 menuItem12->Checked = true;
			 menuItem13->Checked = false;
		 }
private: System::Void menuItem13_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 //c1Chart3D1->ChartGroups[0]->ChartType = C1::Win::C1Chart3D::Chart3DTypeEnum::Surface;
			 axChart3D1->ChartGroups[1]->ChartType = C1Chart3D8::ChartTypeConstants::oc3dTypeSurface;
			 menuItem14->Checked = false;
			 menuItem12->Checked = false;
			 menuItem13->Checked = true;
		 }
/************************************************************************/
/*                            Chart View                                */
/************************************************************************/
private: System::Void menuItem15_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 //c1Chart3D1->ChartArea->View3D = C1::Win::C1Chart3D::View3DEnum::XY_2D_Pos;
			 menuItem15->Checked = true;
			 menuItem16->Checked = false;
			 menuItem17->Checked = false;
			 menuItem11->Checked = false;
		 }
private: System::Void menuItem16_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 //c1Chart3D1->ChartArea->View->View3D = C1::Win::C1Chart3D::View3DEnum::XZ_2D_Pos;
			 menuItem15->Checked = false;
			 menuItem16->Checked = true;
			 menuItem17->Checked = false;
			 menuItem11->Checked = false;
		 }
private: System::Void menuItem17_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 //c1Chart3D1->ChartArea->View3D = C1::Win::C1Chart3D::View3DEnum::YZ_2D_Pos;
			 menuItem15->Checked = false;
			 menuItem16->Checked = false;
			 menuItem17->Checked = true;
			 menuItem11->Checked = false;
		 }
private: System::Void menuItem11_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 //c1Chart3D1->ChartArea->View->View3D = C1::Win::C1Chart3D::View3DEnum::Default;
			 menuItem15->Checked = false;
			 menuItem16->Checked = false;
			 menuItem17->Checked = false;
			 menuItem11->Checked = true;
		 }
private: System::Void radioButton2_CheckedChanged(System::Object^  sender, System::EventArgs^  e) 
		 {
			 axChart2D1->Visible = false;
			 if (tabControl2->SelectedIndex == 0)
			 {
				 axChart3D1->Visible = true;
			 }
			 else
			 {
				 axChart3D1->Visible = false;
				 axChart2D1->Visible = true;
			 }
			 
			 groupBox6->Visible = true;
			 textBox2->Visible = true;
			 groupBox2->Visible = true;

			 cbMList->Items->Clear();
			 cbMList->Items->Add("NAME_METHOD_HOOKE_JEEVES");
			 cbMList->Items->Add("NAME_METHOD_NELDER_MEAD");
			 cbMList->Items->Add("NAME_METHOD_SIMPLEX_METHOD");
			 cbMList->Items->Add("NAME_METHOD_BOX");
			 cbMList->Items->Add("NAME_METHOD_CYCLIC_MINMIN");
			 cbMList->Items->Add("NAME_METHOD_GAUSS_SEIDEL");
			 cbMList->Items->Add("NAME_METHOD_POWELL_SEARCH");
			 cbMList->Items->Add("NAME_METHOD_RANDOM_SEARCH");
			 cbMList->Items->Add("NAME_METHOD_WEIL_PI_SEARCH");
			 cbMList->Items->Add("NAME_METHOD_WEIL_E_SEARCH");
			 cbMList->Items->Add("NAME_METHOD_FASTEST_DESCENT");
			 cbMList->Items->Add("NAME_METHOD_FLETCHER_REEVES");
			 cbMList->Items->Add("NAME_METHOD_POLAK_RIBIERE");
			 cbMList->Items->Add("NAME_METHOD_DFP_SEARCH");
			 cbMList->Items->Add("NAME_METHOD_NEWTON_SEARCH");
			 cbMList->Items->Add("NAME_METHOD_NEWTON_RAPHSON");
			 cbMList->Items->Add("NAME_METHOD_BIN_GENETIC_ALGORITHM");
			 cbMList->Items->Add("NAME_METHOD_CON_GENETIC_ALGORITHM");
			 cbMList->SelectedIndex = 0;

			 cbFList->Items->Clear();
			 cbFList->Items->Add("Func Paraboloid3d");
			 cbFList->Items->Add("Func ExtendedParaboloid3d");
			 cbFList->Items->Add("Func RotatedParaboloid3d");
			 cbFList->Items->Add("Func Rosenbrock3d");
			 cbFList->Items->Add("Func Z3d");
			 cbFList->Items->Add("Func W3d");
			 cbFList->Items->Add("Func RosenbrockMOD3d");
			 cbFList->SelectedIndex = 0;

			 comboBox2->Items->Clear();
			 comboBox2->Items->Add("METHOD_ADAPTATION_STEP");
			 comboBox2->Items->Add("METHOD_UNIFORM");
			 comboBox2->Items->Add("METHOD_DIVISION");
			 comboBox2->Items->Add("METHOD_DICHOTOMY");
			 comboBox2->Items->Add("METHOD_FIBONACCI");
			 comboBox2->Items->Add("METHOD_GOLDEN_SECTION");
			 comboBox2->Items->Add("METHOD_QUADRATIC_INTERPOLATION");
			 comboBox2->Items->Add("METHOD_CUBIC_INTERPOLATION");
			 comboBox2->SelectedIndex = 0;

			 checkedListBox1->Items->Clear();
			 checkedListBox1->Items->Add("HOOKE_JEEVES");
			 checkedListBox1->Items->Add("NELDER_MEAD");
			 checkedListBox1->Items->Add("SIMPLEX_METHOD");
			 checkedListBox1->Items->Add("BOX");
			 checkedListBox1->Items->Add("CYCLIC_MINMIN");
			 checkedListBox1->Items->Add("GAUSS_SEIDEL");
			 checkedListBox1->Items->Add("POWELL_SEARCH");
			 checkedListBox1->Items->Add("RANDOM_SEARCH");
			 checkedListBox1->Items->Add("WEIL_PI_SEARCH");
			 checkedListBox1->Items->Add("WEIL_E_SEARCH");
			 checkedListBox1->Items->Add("FASTEST_DESCENT");
			 checkedListBox1->Items->Add("FLETCHER_REEVES");
			 checkedListBox1->Items->Add("POLAK_RIBIERE");
			 checkedListBox1->Items->Add("DFP_SEARCH");
			 checkedListBox1->Items->Add("NEWTON_SEARCH");
			 checkedListBox1->Items->Add("NEWTON_RAPHSON");
			 checkedListBox1->Items->Add("BIN_GENETIC_ALGORITHM");
			 checkedListBox1->SelectedIndex = 0;

		 }
private: System::Void radioButton1_CheckedChanged(System::Object^  sender, System::EventArgs^  e) 
		 {
			 axChart3D1->Visible = false;
			 axChart2D1->Visible = true;
			 groupBox6->Visible = false;
			 textBox2->Visible = false;
			 groupBox2->Visible = false;

			 cbMList->Items->Clear();
			 cbMList->Items->Add("METHOD_SVEN");
			 cbMList->Items->Add("METHOD_ADAPTATION_STEP");
			 cbMList->Items->Add("METHOD_UNIFORM");
			 cbMList->Items->Add("METHOD_DIVISION");
			 cbMList->Items->Add("METHOD_DICHOTOMY");
			 cbMList->Items->Add("METHOD_FIBONACCI");
			 cbMList->Items->Add("METHOD_GOLDEN_SECTION");
			 cbMList->Items->Add("METHOD_QUADRATIC_INTERPOLATION");
			 cbMList->Items->Add("METHOD_CUBIC_INTERPOLATION");
			 cbMList->SelectedIndex = 0;

			 cbFList->Items->Clear();
			 cbFList->Items->Add("Func Parabola y=x^2");
			 cbFList->Items->Add("Func Polynomial3D y=x^2(x+3)");
			 cbFList->Items->Add("Func Parabola4D");
			 cbFList->Items->Add("Func FractionalRational");
			 cbFList->Items->Add("Func NonSmooth");
			 cbFList->SelectedIndex = 0;

			 checkedListBox1->Items->Clear();
			 checkedListBox1->Items->Add("SVEN");
			 checkedListBox1->Items->Add("ADAPTATION_STEP");
			 checkedListBox1->Items->Add("UNIFORM");
			 checkedListBox1->Items->Add("DIVISION");
			 checkedListBox1->Items->Add("DICHOTOMY");
			 checkedListBox1->Items->Add("FIBONACCI");
			 checkedListBox1->Items->Add("GOLDEN_SECTION");
			 checkedListBox1->Items->Add("QUADRATIC_INTERPOLATION");
			 checkedListBox1->Items->Add("CUBIC_INTERPOLATION");
			 checkedListBox1->SelectedIndex = 0;
		 }

		 metopt::NAME_METHOD getMethod(int index)
		 {
			 switch (index)
			 {
			 case 0:
				 return metopt::NAME_METHOD_SVEN;
			 case 1:
				 return metopt::NAME_METHOD_ADAPTATION_STEP;
			 case 2:
				 return metopt::NAME_METHOD_UNIFORM;
			 case 3:
				 return metopt::NAME_METHOD_DIVISION;
			 case 4:
				 return metopt::NAME_METHOD_DICHOTOMY;
			 case 5:
				 return metopt::NAME_METHOD_FIBONACCI;
			 case 6:
				 return metopt::NAME_METHOD_GOLDEN_SECTION;
			 case 7:
				 return metopt::NAME_METHOD_QUADRATIC_INTERPOLATION;
			 case 8:
				 return metopt::NAME_METHOD_CUBIC_INTERPOLATION;
			 case 9:
				 return metopt::NAME_METHOD_HOOKE_JEEVES;
			 case 10:
				 return metopt::NAME_METHOD_NELDER_MEAD;
			 case 11:
				 return metopt::NAME_METHOD_SIMPLEX_METHOD;
			 case 12:
				 return metopt::NAME_METHOD_BOX;
			 case 13:
				 return metopt::NAME_METHOD_CYCLIC_MINMIN;
			 case 14:
				 return metopt::NAME_METHOD_GAUSS_SEIDEL;
			 case 15:
				 return metopt::NAME_METHOD_POWELL_SEARCH;
			 case 16:
				 return metopt::NAME_METHOD_RANDOM_SEARCH;
			 case 17:
				 return metopt::NAME_METHOD_WEIL_PI_SEARCH;
			 case 18:
				 return metopt::NAME_METHOD_WEIL_E_SEARCH;
			 case 19:
				 return metopt::NAME_METHOD_FASTEST_DESCENT;
			 case 20:
				 return metopt::NAME_METHOD_FLETCHER_REEVES;
			 case 21:
				 return metopt::NAME_METHOD_POLAK_RIBIERE;
			 case 22:
				 return metopt::NAME_METHOD_DFP_SEARCH;
			 case 23:
				 return metopt::NAME_METHOD_NEWTON_SEARCH;
			 case 24:
				 return metopt::NAME_METHOD_NEWTON_RAPHSON;
			 case 25:
				 return metopt::NAME_METHOD_BIN_GENETIC_ALGORITHM;
			 case 26:
				 return metopt::NAME_METHOD_CON_GENETIC_ALGORITHM;
			 }
		 }

private: System::Void textBox2_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		 }

		 void compareMethods()
		 {
			 axChart3D1->Visible = false;
			 axChart2D1->Visible = true;
			 

			 int a = 0;
		 }

private: System::Void btnGenerate_Click(System::Object^  sender, System::EventArgs^  e)
{
			 int									metodDimID = checkDimMethod();
			 int									taskType = chekTaskType();
			 metopt::NAME_METHOD					nameMethodID = checkMethod();
			 metopt::TYPE_EXIT_PRECISION_FLAG	flagExit = checkFlagExit();
			 metopt::inputParam					oparam;
			 metopt::CFunc*						func;

			 if (taskType == 0)
			 {
				 switch (metodDimID)
				 {
				 case 0:
				 {
						   double x[] = { 0.0 };
						   x[0] = Convert::ToDouble(textBox1->Text);
						   metopt::Arg initPoint(x);
						   func = checkFunc();
						   func->setMethod(nameMethodID);
						   func->setPrecision(Convert::ToDouble(textBox4->Text));
						   func->setStep(Convert::ToDouble(textBox5->Text));
						   func->setParam((int)numericUpDown1->Value,
							   (int)numericUpDown2->Value,
							   (int)numericUpDown3->Value);
						   func->setFlagExit(flagExit);
						   oparam = func->calcArgMin(initPoint);
						   metopt::CDataOneDimensional* data = func->getData();
						   //if (checkBox1->Checked)
						   data->printToFile("method.log");
						   drawChart(func);
						   break;
				 }
				 case 1:
				 {
						   double x[] = { 0.0, 0.0 };
						   x[0] = Convert::ToDouble(textBox1->Text);
						   x[1] = Convert::ToDouble(textBox2->Text);
						   metopt::Arg initPoint(x);

						   double a[] = { 0.0, 0.0 };
						   a[0] = Convert::ToDouble(textBox7->Text);
						   a[1] = Convert::ToDouble(textBox8->Text);
						   double b[] = { 0.0, 0.0 };
						   b[0] = Convert::ToDouble(textBox9->Text);
						   b[1] = Convert::ToDouble(textBox3->Text);

						   func = checkFunc();
						   func->getMultiFunc()->setInterval(metopt::Arg(a), metopt::Arg(b));
						   func->setMethod(nameMethodID);
						   func->setPrecision(Convert::ToDouble(textBox4->Text));
						   func->setStep(Convert::ToDouble(textBox5->Text));
						   func->setParam((int)numericUpDown1->Value,
							   (int)numericUpDown2->Value,
							   (int)numericUpDown3->Value);
						   func->setFlagExit(flagExit);
						   func->setOneDimensionalPrecision(Convert::ToDouble(textBox6->Text));
						   func->setOneDimensionalMethod(checkOneMethod());

						   oparam = func->calcArgMin(initPoint);
						   metopt::CDataMultiDimensional* data = func->getMultiData();

						   data->printToFile("method.log");
						   drawChart3D(func);
						   break;
				 }
				 }

				 listBox1->Items->Clear();
				 listBox1->Items->AddRange(System::IO::File::ReadAllLines("method.log"));
			 }
			 else
			 {
				 switch (metodDimID)
				 {
				 case 0:
				 {
						   double x[] = { 0.0 };
						   x[0] = Convert::ToDouble(textBox1->Text);
						   metopt::Arg initPoint(x);
						   func = checkFunc();
						   metopt::CCompareMethods* compare = new metopt::CCompareSingleMethods(func);

						   compare->setPrecision(Convert::ToDouble(textBox4->Text));
						   compare->setStep(Convert::ToDouble(textBox5->Text));
						   compare->setParam((int)numericUpDown1->Value,
							   (int)numericUpDown2->Value,
							   (int)numericUpDown3->Value);
						   compare->setFlagExit(flagExit);

						   int count = checkedListBox1->CheckedItems->Count;
						   for (int i = 0; i < count; ++i)
						   {
							   int index = checkedListBox1->CheckedIndices[i];
							   metopt::NAME_METHOD nameMethodID = getMethod(index);
							   compare->pushMethod(nameMethodID);
						   }

						   compare->calcMethods(initPoint);
						   compare->getCompareData()->printToFile("CompareMethods.log");

						   drawGistogram(compare->getCompareData());
						   break;
				 }
				 case 1:
				 {
				 }
					 double x[] = { 0.0, 0.0 };
					 x[0] = Convert::ToDouble(textBox1->Text);
					 x[1] = Convert::ToDouble(textBox2->Text);
					 metopt::Arg initPoint(x);

					 double a[] = { 0.0, 0.0 };
					 a[0] = Convert::ToDouble(textBox7->Text);
					 a[1] = Convert::ToDouble(textBox8->Text);
					 double b[] = { 0.0, 0.0 };
					 b[0] = Convert::ToDouble(textBox9->Text);
					 b[1] = Convert::ToDouble(textBox3->Text);

					 func = checkFunc();
					 metopt::CCompareMultiMethods* compare = new metopt::CCompareMultiMethods(func);
					
					 compare->setInterval(metopt::Arg(a), metopt::Arg(b));
					 compare->setPrecision(Convert::ToDouble(textBox4->Text));
					 compare->setStep(Convert::ToDouble(textBox5->Text));
					 compare->setParam((int)numericUpDown1->Value,
						 (int)numericUpDown2->Value,
						 (int)numericUpDown3->Value);
					 compare->setFlagExit(flagExit);
					 compare->setOneDimensionalPrecision(Convert::ToDouble(textBox6->Text));
					 compare->setOneDimensionalMethod(checkOneMethod());

					 int count = checkedListBox1->CheckedItems->Count;
					 for (int i = 0; i < count; ++i)
					 {
						 int index = checkedListBox1->CheckedIndices[i];
						 metopt::NAME_METHOD nameMethodID = getMethod(index + 9);
						 compare->pushMethod(nameMethodID);
					 }

					 compare->calcMethods(initPoint);
					 compare->getCompareData()->printToFile("CompareMethods.log");

					 drawGistogram(compare->getCompareData());
					 break;
				 }

				 listBox1->Items->Clear();
				 listBox1->Items->AddRange(System::IO::File::ReadAllLines("CompareMethods.log"));
			 }
}
private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) 
		 {
			cbMList->Items->Clear();
			cbMList->Items->Add("METHOD_SVEN");
			cbMList->Items->Add("METHOD_ADAPTATION_STEP");
			cbMList->Items->Add("METHOD_UNIFORM");
			cbMList->Items->Add("METHOD_DIVISION");
			cbMList->Items->Add("METHOD_DICHOTOMY");
			cbMList->Items->Add("METHOD_FIBONACCI");
			cbMList->Items->Add("METHOD_GOLDEN_SECTION");
			cbMList->Items->Add("METHOD_QUADRATIC_INTERPOLATION");
			cbMList->Items->Add("METHOD_CUBIC_INTERPOLATION");
			cbMList->SelectedIndex = 0;

			cbFList->Items->Clear();
			cbFList->Items->Add("Func Parabola y=x^2");
			cbFList->Items->Add("Func Polynomial3D");
			cbFList->Items->Add("Func Parabola4D");
			cbFList->Items->Add("Func FractionalRational");
			cbFList->Items->Add("Func NonSmooth");
			cbFList->SelectedIndex = 0;

			comboBox1->Items->Clear();
			comboBox1->Items->Add("TYPE_EXIT_PRECISION_STEP");
			comboBox1->Items->Add("TYPE_EXIT_PRECISION_FUNC");
			comboBox1->Items->Add("TYPE_EXIT_PRECISION_VAR");
			comboBox1->SelectedIndex = 1;

			checkedListBox1->Items->Clear();
			checkedListBox1->Items->Add("SVEN");
			checkedListBox1->Items->Add("ADAPTATION_STEP");
			checkedListBox1->Items->Add("UNIFORM");
			checkedListBox1->Items->Add("DIVISION");
			checkedListBox1->Items->Add("DICHOTOMY");
			checkedListBox1->Items->Add("FIBONACCI");
			checkedListBox1->Items->Add("GOLDEN_SECTION");
			checkedListBox1->Items->Add("QUADRATIC_INTERPOLATION");
			checkedListBox1->Items->Add("CUBIC_INTERPOLATION");
			checkedListBox1->SelectedIndex = 0;
		 }

private: System::Void label10_Click(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void checkedListBox1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void tabControl2_Selected(System::Object^  sender, System::Windows::Forms::TabControlEventArgs^  e) {

	int index = tabControl2->SelectedIndex;
	
	if (index == 1)
	{
		axChart2D1->Visible = true;
		axChart3D1->Visible = false;
	}
}
private: System::Void tabControl2_TabIndexChanged(System::Object^  sender, System::EventArgs^  e) {
			 int b = 0;
}
};
}

