#pragma once

#include <stdio.h>

extern int GMode, GVar, GCmd, GLast;
static char * GModeTable[] = {
	"INPUT", "CALC", "OUTPUT"
	};
static char * GVarTable[] = {
	"A", "B", "C"
	};
static char * GCmdTable[] = {
	"STO", "REC", "CLR", "CLEAR ALL", "CLEAR"
	};

void execCmd();
void execClear(int var);
void execStore(int var);
void execReclaim(int var);
bool execVal(char * txt, char * msgerr);


namespace MatCalc {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Runtime::InteropServices;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	private:
		void clrAll() {
			GMode = GVar = GLast = -1;
			txtInput -> Text = "";
			char msg[30];
			sprintf_s(msg, "CLEAR ALL");
			String^ msgitem = gcnew String(msg);
			lstHistory -> Items -> Add(msgitem);
			lstHistory -> SelectedIndex = lstHistory -> Items -> Count - 1;
			}
		void clrLast() {
			if (GLast == -1) {
				return;
				}
			String^ last = (String^) lstHistory -> SelectedItem;
			lstHistory -> Items -> Remove(last);
			switch (GLast) {
				case 0:
					GMode = -1;
					break;
				case 1:
					GVar = -1;
					updCmd(GCmd);
					break;
				}
			}
		void updMode(int mode) {
			GMode = mode;
			char msg[30];
			sprintf_s(msg, "%s MODE", GModeTable[mode]);
			String^ msgitem = gcnew String(msg);
			lstCurMode -> Items -> Clear();
			lstCurMode -> Items -> Add(msgitem);
			lstHistory -> Items -> Add(msgitem);
			lstHistory -> SelectedIndex = lstHistory -> Items -> Count - 1;
			lstMsg->Items->Clear();
			switch (mode) {
				case 0:
					btnPlus -> Enabled = false;
					btnMinus -> Enabled = false;
					btnTimes -> Enabled = false;
					btnStore -> Enabled = true;
					btnReclaim -> Enabled = true;
					btnClear -> Enabled = true;
					btnA -> Enabled = true;
					btnB -> Enabled = true;
					btnC -> Enabled = true;
					btnD -> Enabled = true;
					btnE -> Enabled = true;
					btnF -> Enabled = true;
					txtInput -> Enabled = true;
					break;
				case 2:
					btnPlus -> Enabled = false;
					btnMinus -> Enabled = false;
					btnTimes -> Enabled = false;
					btnStore -> Enabled = false;
					btnReclaim -> Enabled = false;
					btnClear -> Enabled = false;
					btnA -> Enabled = false;
					btnB -> Enabled = false;
					btnC -> Enabled = false;
					btnD -> Enabled = false;
					btnE -> Enabled = false;
					btnF -> Enabled = false;
					txtInput -> Enabled = false;
					break;
		}

			}
		void updCmd(int cmd) {
			GCmd = cmd;
			GLast = 0;
			char msg[30];
			sprintf_s(msg, "%s", GCmdTable[cmd]);
			String^ msgitem = gcnew String(msg);
			lstHistory -> Items -> Add(msgitem);
			lstHistory -> SelectedIndex = lstHistory -> Items -> Count - 1;
			lstMsg->Items->Clear();
			}
		void updVar(int var) {
			if (GCmd == -1) {
				return;
				}
			GVar = var;
			GLast = 1;
			char msg[30];
			sprintf_s(msg, "%s %s", GCmdTable[GCmd], GVarTable[var]);
			String^ msgitem = gcnew String(msg);
			String^ last = (String^) lstHistory -> SelectedItem;
			lstHistory -> Items -> Remove(last);
			lstHistory -> Items -> Add(msgitem);
			lstHistory->SelectedIndex = lstHistory->Items->Count - 1;
			execCmd();
			}
		void updVal() {
			lstMsg -> Items -> Clear();
			char msg[30];
			String^ msgerr = gcnew String("");
			char * txt = (char *) Marshal::StringToHGlobalAnsi(txtInput -> Text).ToPointer();
			bool valid = execVal(txt, msg);
			Marshal::FreeHGlobal(IntPtr(txt));
			if (! valid) {
				lstMsg -> Items -> Add(msgerr);
				return;
				}
			String^ msgitem = gcnew String("VALIDATE INPUT");
			lstHistory -> Items -> Add(msgitem);
			lstHistory -> SelectedIndex = lstHistory -> Items -> Count - 1;
			}

	public:
		MyForm(void)
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
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  btnInput;
	private: System::Windows::Forms::Label^  lbl;

	private: System::Windows::Forms::ListBox^  lstCurMode;
	private: System::Windows::Forms::Panel^  panel1;
	private: System::Windows::Forms::DataGridView^  dataGridView1;
	private: System::Windows::Forms::TextBox^  txtInput;

	private: System::Windows::Forms::ListBox^  lstHistory;
	private: System::Windows::Forms::ListBox^  lstMsg;
	private: System::Windows::Forms::Button^  btnCalc;
	private: System::Windows::Forms::Button^  btnOutput;
	private: System::Windows::Forms::Button^  btnStore;
	private: System::Windows::Forms::Button^  btnReclaim;
	private: System::Windows::Forms::Button^  btnClear;
	private: System::Windows::Forms::Button^  btnA;
	private: System::Windows::Forms::Button^  btnB;
	private: System::Windows::Forms::Button^  btnC;
	private: System::Windows::Forms::Button^  btnCls;
	private: System::Windows::Forms::Button^  btnCE;
	private: System::Windows::Forms::Button^  btnOFF;
	private: System::Windows::Forms::ListView^  lvwHistory;
	private: System::Windows::Forms::ColumnHeader^  Msg;
	private: System::Windows::Forms::Button^  btnPlus;
	private: System::Windows::Forms::Button^  btnMinus;
	private: System::Windows::Forms::Button^  btnTimes;
private: System::Windows::Forms::Button^  btnD;
private: System::Windows::Forms::Button^  btnE;
private: System::Windows::Forms::Button^  btnF;
private: System::Windows::Forms::Button^  btnVal;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->btnInput = (gcnew System::Windows::Forms::Button());
			this->lbl = (gcnew System::Windows::Forms::Label());
			this->lstCurMode = (gcnew System::Windows::Forms::ListBox());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->txtInput = (gcnew System::Windows::Forms::TextBox());
			this->lstHistory = (gcnew System::Windows::Forms::ListBox());
			this->lstMsg = (gcnew System::Windows::Forms::ListBox());
			this->btnCalc = (gcnew System::Windows::Forms::Button());
			this->btnOutput = (gcnew System::Windows::Forms::Button());
			this->btnStore = (gcnew System::Windows::Forms::Button());
			this->btnReclaim = (gcnew System::Windows::Forms::Button());
			this->btnClear = (gcnew System::Windows::Forms::Button());
			this->btnA = (gcnew System::Windows::Forms::Button());
			this->btnB = (gcnew System::Windows::Forms::Button());
			this->btnC = (gcnew System::Windows::Forms::Button());
			this->btnCls = (gcnew System::Windows::Forms::Button());
			this->btnCE = (gcnew System::Windows::Forms::Button());
			this->btnOFF = (gcnew System::Windows::Forms::Button());
			this->lvwHistory = (gcnew System::Windows::Forms::ListView());
			this->Msg = (gcnew System::Windows::Forms::ColumnHeader());
			this->btnPlus = (gcnew System::Windows::Forms::Button());
			this->btnMinus = (gcnew System::Windows::Forms::Button());
			this->btnTimes = (gcnew System::Windows::Forms::Button());
			this->btnD = (gcnew System::Windows::Forms::Button());
			this->btnE = (gcnew System::Windows::Forms::Button());
			this->btnF = (gcnew System::Windows::Forms::Button());
			this->btnVal = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			this->SuspendLayout();
			// 
			// btnInput
			// 
			this->btnInput->BackColor = System::Drawing::SystemColors::WindowText;
			this->btnInput->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnInput->ForeColor = System::Drawing::SystemColors::Window;
			this->btnInput->Location = System::Drawing::Point(12, 198);
			this->btnInput->Name = L"btnInput";
			this->btnInput->Size = System::Drawing::Size(75, 23);
			this->btnInput->TabIndex = 0;
			this->btnInput->Text = L"INP";
			this->btnInput->UseVisualStyleBackColor = false;
			this->btnInput->Click += gcnew System::EventHandler(this, &MyForm::btnInput_Click);
			// 
			// lbl
			// 
			this->lbl->AutoSize = true;
			this->lbl->Location = System::Drawing::Point(1028, 142);
			this->lbl->Name = L"lbl";
			this->lbl->Size = System::Drawing::Size(35, 13);
			this->lbl->TabIndex = 1;
			this->lbl->Text = L"label1";
			// 
			// lstCurMode
			// 
			this->lstCurMode->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->lstCurMode->CausesValidation = false;
			this->lstCurMode->Enabled = false;
			this->lstCurMode->Font = (gcnew System::Drawing::Font(L"Segoe UI Black", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lstCurMode->FormattingEnabled = true;
			this->lstCurMode->ItemHeight = 21;
			this->lstCurMode->Location = System::Drawing::Point(4, 2);
			this->lstCurMode->Name = L"lstCurMode";
			this->lstCurMode->SelectionMode = System::Windows::Forms::SelectionMode::None;
			this->lstCurMode->Size = System::Drawing::Size(781, 42);
			this->lstCurMode->TabIndex = 2;
			this->lstCurMode->TabStop = false;
			// 
			// panel1
			// 
			this->panel1->Location = System::Drawing::Point(1267, 215);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(200, 100);
			this->panel1->TabIndex = 3;
			// 
			// dataGridView1
			// 
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->Location = System::Drawing::Point(1227, 42);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->Size = System::Drawing::Size(240, 150);
			this->dataGridView1->TabIndex = 4;
			// 
			// txtInput
			// 
			this->txtInput->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->txtInput->Font = (gcnew System::Drawing::Font(L"Courier New", 8, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->txtInput->Location = System::Drawing::Point(4, 383);
			this->txtInput->Multiline = true;
			this->txtInput->Name = L"txtInput";
			this->txtInput->Size = System::Drawing::Size(781, 150);
			this->txtInput->TabIndex = 3;
			this->txtInput->WordWrap = false;
			// 
			// lstHistory
			// 
			this->lstHistory->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->lstHistory->CausesValidation = false;
			this->lstHistory->Enabled = false;
			this->lstHistory->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lstHistory->FormattingEnabled = true;
			this->lstHistory->ItemHeight = 21;
			this->lstHistory->Location = System::Drawing::Point(4, 40);
			this->lstHistory->Name = L"lstHistory";
			this->lstHistory->Size = System::Drawing::Size(781, 105);
			this->lstHistory->TabIndex = 6;
			this->lstHistory->TabStop = false;
			// 
			// lstMsg
			// 
			this->lstMsg->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->lstMsg->CausesValidation = false;
			this->lstMsg->Enabled = false;
			this->lstMsg->Font = (gcnew System::Drawing::Font(L"Segoe UI", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lstMsg->FormattingEnabled = true;
			this->lstMsg->Location = System::Drawing::Point(4, 145);
			this->lstMsg->Name = L"lstMsg";
			this->lstMsg->SelectionMode = System::Windows::Forms::SelectionMode::None;
			this->lstMsg->Size = System::Drawing::Size(781, 39);
			this->lstMsg->TabIndex = 7;
			this->lstMsg->TabStop = false;
			// 
			// btnCalc
			// 
			this->btnCalc->BackColor = System::Drawing::SystemColors::WindowText;
			this->btnCalc->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnCalc->ForeColor = System::Drawing::SystemColors::Window;
			this->btnCalc->Location = System::Drawing::Point(93, 198);
			this->btnCalc->Name = L"btnCalc";
			this->btnCalc->Size = System::Drawing::Size(75, 23);
			this->btnCalc->TabIndex = 8;
			this->btnCalc->Text = L"CALC";
			this->btnCalc->UseVisualStyleBackColor = false;
			this->btnCalc->Click += gcnew System::EventHandler(this, &MyForm::btnCalc_Click);
			// 
			// btnOutput
			// 
			this->btnOutput->BackColor = System::Drawing::SystemColors::WindowText;
			this->btnOutput->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnOutput->ForeColor = System::Drawing::SystemColors::Window;
			this->btnOutput->Location = System::Drawing::Point(174, 198);
			this->btnOutput->Name = L"btnOutput";
			this->btnOutput->Size = System::Drawing::Size(75, 23);
			this->btnOutput->TabIndex = 9;
			this->btnOutput->Text = L"OUT";
			this->btnOutput->UseVisualStyleBackColor = false;
			this->btnOutput->Click += gcnew System::EventHandler(this, &MyForm::btnOutput_Click);
			// 
			// btnStore
			// 
			this->btnStore->BackColor = System::Drawing::SystemColors::WindowText;
			this->btnStore->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnStore->ForeColor = System::Drawing::SystemColors::Window;
			this->btnStore->Location = System::Drawing::Point(708, 198);
			this->btnStore->Name = L"btnStore";
			this->btnStore->Size = System::Drawing::Size(75, 23);
			this->btnStore->TabIndex = 10;
			this->btnStore->Text = L"STO";
			this->btnStore->UseVisualStyleBackColor = false;
			this->btnStore->Click += gcnew System::EventHandler(this, &MyForm::btnStore_Click);
			// 
			// btnReclaim
			// 
			this->btnReclaim->BackColor = System::Drawing::SystemColors::WindowText;
			this->btnReclaim->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnReclaim->ForeColor = System::Drawing::SystemColors::Window;
			this->btnReclaim->Location = System::Drawing::Point(708, 227);
			this->btnReclaim->Name = L"btnReclaim";
			this->btnReclaim->Size = System::Drawing::Size(75, 23);
			this->btnReclaim->TabIndex = 11;
			this->btnReclaim->Text = L"REC";
			this->btnReclaim->UseVisualStyleBackColor = false;
			this->btnReclaim->Click += gcnew System::EventHandler(this, &MyForm::btnReclaim_Click);
			// 
			// btnClear
			// 
			this->btnClear->BackColor = System::Drawing::SystemColors::WindowText;
			this->btnClear->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnClear->ForeColor = System::Drawing::SystemColors::Window;
			this->btnClear->Location = System::Drawing::Point(708, 256);
			this->btnClear->Name = L"btnClear";
			this->btnClear->Size = System::Drawing::Size(75, 23);
			this->btnClear->TabIndex = 12;
			this->btnClear->Text = L"CLR";
			this->btnClear->UseVisualStyleBackColor = false;
			this->btnClear->Click += gcnew System::EventHandler(this, &MyForm::btnClear_Click);
			// 
			// btnA
			// 
			this->btnA->BackColor = System::Drawing::SystemColors::WindowText;
			this->btnA->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnA->ForeColor = System::Drawing::SystemColors::Window;
			this->btnA->Location = System::Drawing::Point(619, 198);
			this->btnA->Name = L"btnA";
			this->btnA->Size = System::Drawing::Size(75, 23);
			this->btnA->TabIndex = 13;
			this->btnA->Text = L"A";
			this->btnA->UseVisualStyleBackColor = false;
			this->btnA->Click += gcnew System::EventHandler(this, &MyForm::btnA_Click);
			// 
			// btnB
			// 
			this->btnB->BackColor = System::Drawing::SystemColors::WindowText;
			this->btnB->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnB->ForeColor = System::Drawing::SystemColors::Window;
			this->btnB->Location = System::Drawing::Point(619, 227);
			this->btnB->Name = L"btnB";
			this->btnB->Size = System::Drawing::Size(75, 23);
			this->btnB->TabIndex = 14;
			this->btnB->Text = L"B";
			this->btnB->UseVisualStyleBackColor = false;
			this->btnB->Click += gcnew System::EventHandler(this, &MyForm::btnB_Click);
			// 
			// btnC
			// 
			this->btnC->BackColor = System::Drawing::SystemColors::WindowText;
			this->btnC->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnC->ForeColor = System::Drawing::SystemColors::Window;
			this->btnC->Location = System::Drawing::Point(619, 256);
			this->btnC->Name = L"btnC";
			this->btnC->Size = System::Drawing::Size(75, 23);
			this->btnC->TabIndex = 15;
			this->btnC->Text = L"C";
			this->btnC->UseVisualStyleBackColor = false;
			this->btnC->Click += gcnew System::EventHandler(this, &MyForm::btnC_Click);
			// 
			// btnCls
			// 
			this->btnCls->BackColor = System::Drawing::Color::Crimson;
			this->btnCls->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnCls->ForeColor = System::Drawing::SystemColors::WindowText;
			this->btnCls->Location = System::Drawing::Point(525, 198);
			this->btnCls->Name = L"btnCls";
			this->btnCls->Size = System::Drawing::Size(75, 53);
			this->btnCls->TabIndex = 16;
			this->btnCls->Text = L"AC";
			this->btnCls->UseVisualStyleBackColor = false;
			this->btnCls->Click += gcnew System::EventHandler(this, &MyForm::btnCls_Click);
			// 
			// btnCE
			// 
			this->btnCE->BackColor = System::Drawing::Color::Yellow;
			this->btnCE->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnCE->ForeColor = System::Drawing::SystemColors::WindowText;
			this->btnCE->Location = System::Drawing::Point(444, 198);
			this->btnCE->Name = L"btnCE";
			this->btnCE->Size = System::Drawing::Size(75, 53);
			this->btnCE->TabIndex = 17;
			this->btnCE->Text = L"CE";
			this->btnCE->UseVisualStyleBackColor = false;
			this->btnCE->Click += gcnew System::EventHandler(this, &MyForm::btnCE_Click);
			// 
			// btnOFF
			// 
			this->btnOFF->BackColor = System::Drawing::Color::Crimson;
			this->btnOFF->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnOFF->ForeColor = System::Drawing::SystemColors::Window;
			this->btnOFF->Location = System::Drawing::Point(255, 198);
			this->btnOFF->Name = L"btnOFF";
			this->btnOFF->Size = System::Drawing::Size(75, 23);
			this->btnOFF->TabIndex = 18;
			this->btnOFF->Text = L"OFF";
			this->btnOFF->UseVisualStyleBackColor = false;
			this->btnOFF->Click += gcnew System::EventHandler(this, &MyForm::btnOFF_Click);
			// 
			// lvwHistory
			// 
			this->lvwHistory->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->lvwHistory->CausesValidation = false;
			this->lvwHistory->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(1) { this->Msg });
			this->lvwHistory->Enabled = false;
			this->lvwHistory->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lvwHistory->HeaderStyle = System::Windows::Forms::ColumnHeaderStyle::None;
			this->lvwHistory->Location = System::Drawing::Point(1242, 383);
			this->lvwHistory->MultiSelect = false;
			this->lvwHistory->Name = L"lvwHistory";
			this->lvwHistory->Size = System::Drawing::Size(225, 97);
			this->lvwHistory->TabIndex = 19;
			this->lvwHistory->TabStop = false;
			this->lvwHistory->UseCompatibleStateImageBehavior = false;
			// 
			// btnPlus
			// 
			this->btnPlus->BackColor = System::Drawing::SystemColors::WindowText;
			this->btnPlus->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnPlus->ForeColor = System::Drawing::SystemColors::Window;
			this->btnPlus->Location = System::Drawing::Point(525, 257);
			this->btnPlus->Name = L"btnPlus";
			this->btnPlus->Size = System::Drawing::Size(75, 23);
			this->btnPlus->TabIndex = 20;
			this->btnPlus->Text = L"+";
			this->btnPlus->UseVisualStyleBackColor = false;
			// 
			// btnMinus
			// 
			this->btnMinus->BackColor = System::Drawing::SystemColors::WindowText;
			this->btnMinus->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnMinus->ForeColor = System::Drawing::SystemColors::Window;
			this->btnMinus->Location = System::Drawing::Point(525, 286);
			this->btnMinus->Name = L"btnMinus";
			this->btnMinus->Size = System::Drawing::Size(75, 23);
			this->btnMinus->TabIndex = 21;
			this->btnMinus->Text = L"-";
			this->btnMinus->UseVisualStyleBackColor = false;
			// 
			// btnTimes
			// 
			this->btnTimes->BackColor = System::Drawing::SystemColors::WindowText;
			this->btnTimes->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnTimes->ForeColor = System::Drawing::SystemColors::Window;
			this->btnTimes->Location = System::Drawing::Point(525, 315);
			this->btnTimes->Name = L"btnTimes";
			this->btnTimes->Size = System::Drawing::Size(75, 23);
			this->btnTimes->TabIndex = 22;
			this->btnTimes->Text = L"x";
			this->btnTimes->UseVisualStyleBackColor = false;
			// 
			// btnD
			// 
			this->btnD->BackColor = System::Drawing::SystemColors::WindowText;
			this->btnD->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnD->ForeColor = System::Drawing::SystemColors::Window;
			this->btnD->Location = System::Drawing::Point(619, 285);
			this->btnD->Name = L"btnD";
			this->btnD->Size = System::Drawing::Size(75, 23);
			this->btnD->TabIndex = 23;
			this->btnD->Text = L"D";
			this->btnD->UseVisualStyleBackColor = false;
			// 
			// btnE
			// 
			this->btnE->BackColor = System::Drawing::SystemColors::WindowText;
			this->btnE->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnE->ForeColor = System::Drawing::SystemColors::Window;
			this->btnE->Location = System::Drawing::Point(619, 314);
			this->btnE->Name = L"btnE";
			this->btnE->Size = System::Drawing::Size(75, 23);
			this->btnE->TabIndex = 24;
			this->btnE->Text = L"E";
			this->btnE->UseVisualStyleBackColor = false;
			// 
			// btnF
			// 
			this->btnF->BackColor = System::Drawing::SystemColors::WindowText;
			this->btnF->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnF->ForeColor = System::Drawing::SystemColors::Window;
			this->btnF->Location = System::Drawing::Point(619, 343);
			this->btnF->Name = L"btnF";
			this->btnF->Size = System::Drawing::Size(75, 23);
			this->btnF->TabIndex = 25;
			this->btnF->Text = L"F";
			this->btnF->UseVisualStyleBackColor = false;
			// 
			// btnVal
			// 
			this->btnVal->BackColor = System::Drawing::SystemColors::WindowText;
			this->btnVal->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnVal->ForeColor = System::Drawing::SystemColors::Window;
			this->btnVal->Location = System::Drawing::Point(708, 343);
			this->btnVal->Name = L"btnVal";
			this->btnVal->Size = System::Drawing::Size(75, 23);
			this->btnVal->TabIndex = 26;
			this->btnVal->Text = L"VAL";
			this->btnVal->UseVisualStyleBackColor = false;
			this->btnVal->Click += gcnew System::EventHandler(this, &MyForm::btnVal_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ControlDark;
			this->ClientSize = System::Drawing::Size(1486, 535);
			this->Controls->Add(this->btnVal);
			this->Controls->Add(this->btnF);
			this->Controls->Add(this->btnE);
			this->Controls->Add(this->btnD);
			this->Controls->Add(this->btnTimes);
			this->Controls->Add(this->btnMinus);
			this->Controls->Add(this->btnPlus);
			this->Controls->Add(this->lvwHistory);
			this->Controls->Add(this->btnOFF);
			this->Controls->Add(this->btnCE);
			this->Controls->Add(this->btnCls);
			this->Controls->Add(this->btnC);
			this->Controls->Add(this->btnB);
			this->Controls->Add(this->btnA);
			this->Controls->Add(this->btnClear);
			this->Controls->Add(this->btnReclaim);
			this->Controls->Add(this->btnStore);
			this->Controls->Add(this->btnOutput);
			this->Controls->Add(this->btnCalc);
			this->Controls->Add(this->lstHistory);
			this->Controls->Add(this->lstMsg);
			this->Controls->Add(this->txtInput);
			this->Controls->Add(this->dataGridView1);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->lbl);
			this->Controls->Add(this->btnInput);
			this->Controls->Add(this->lstCurMode);
			this->Name = L"MyForm";
			this->Text = L"MatCalc";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private:
		System::Void btnInput_Click(System::Object^  sender, System::EventArgs^  e) {
			updMode(0);
			}
		System::Void btnCalc_Click(System::Object^  sender, System::EventArgs^  e) {
			updMode(1);
			}
		System::Void btnOutput_Click(System::Object^  sender, System::EventArgs^  e) {
			updMode(2);
			}
		System::Void btnOFF_Click(System::Object^  sender, System::EventArgs^  e) {
			Hide();
			}
		System::Void btnCls_Click(System::Object^  sender, System::EventArgs^  e) {
			clrAll();
			}
		System::Void btnCE_Click(System::Object^  sender, System::EventArgs^  e) {
			clrLast();
			}
		System::Void btnA_Click(System::Object^  sender, System::EventArgs^  e) {
			updVar(0);
			}
		System::Void btnB_Click(System::Object^  sender, System::EventArgs^  e) {
			updVar(1);
			}
		System::Void btnC_Click(System::Object^  sender, System::EventArgs^  e) {
			updVar(2);
			}
		System::Void btnStore_Click(System::Object^  sender, System::EventArgs^  e) {
			updCmd(0);
			}
		System::Void btnReclaim_Click(System::Object^  sender, System::EventArgs^  e) {
			updCmd(1);
			}
		System::Void btnClear_Click(System::Object^  sender, System::EventArgs^  e) {
			updCmd(2);
			}
		System::Void btnVal_Click(System::Object^  sender, System::EventArgs^  e) {
			updVal();
			}
		};
	}
