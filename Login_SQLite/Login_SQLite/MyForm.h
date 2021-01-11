#pragma once
#include "MyForm1.h"
#include "MyForm2.h"
#include "MyForm3.h"

namespace LoginSQLite {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Data::SQLite;

	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::TextBox^ user;
	private: System::Windows::Forms::TextBox^ pass;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::Button^ button4;
	private: System::Windows::Forms::Button^ button5;
	protected:

	protected:

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->user = (gcnew System::Windows::Forms::TextBox());
			this->pass = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::Color::Transparent;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 23.25F));
			this->label1->ForeColor = System::Drawing::Color::White;
			this->label1->Location = System::Drawing::Point(77, 34);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(199, 35);
			this->label1->TabIndex = 1;
			this->label1->Text = L" 🅢🅐🅚🅤🅡🅐🅢🅞";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->BackColor = System::Drawing::Color::Transparent;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label2->ForeColor = System::Drawing::Color::White;
			this->label2->Location = System::Drawing::Point(78, 133);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(209, 29);
			this->label2->TabIndex = 2;
			this->label2->Text = L"Вход в Sakuraso";
			// 
			// user
			// 
			this->user->BackColor = System::Drawing::SystemColors::MenuHighlight;
			this->user->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->user->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 18, System::Drawing::FontStyle::Bold));
			this->user->ForeColor = System::Drawing::Color::Silver;
			this->user->Location = System::Drawing::Point(59, 202);
			this->user->Name = L"user";
			this->user->Size = System::Drawing::Size(250, 32);
			this->user->TabIndex = 3;
			this->user->Text = L"Имя пользователя";
			this->user->Enter += gcnew System::EventHandler(this, &MyForm::user_Enter);
			this->user->Leave += gcnew System::EventHandler(this, &MyForm::user_Leave);
			// 
			// pass
			// 
			this->pass->BackColor = System::Drawing::SystemColors::MenuHighlight;
			this->pass->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->pass->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 18, System::Drawing::FontStyle::Bold));
			this->pass->ForeColor = System::Drawing::Color::Silver;
			this->pass->Location = System::Drawing::Point(59, 263);
			this->pass->Name = L"pass";
			this->pass->Size = System::Drawing::Size(250, 32);
			this->pass->TabIndex = 4;
			this->pass->Text = L"Пароль";
			this->pass->Enter += gcnew System::EventHandler(this, &MyForm::pass_Enter);
			this->pass->Leave += gcnew System::EventHandler(this, &MyForm::pass_Leave);
			// 
			// button1
			// 
			this->button1->BackColor = System::Drawing::Color::White;
			this->button1->FlatAppearance->BorderSize = 0;
			this->button1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold));
			this->button1->ForeColor = System::Drawing::Color::SteelBlue;
			this->button1->Location = System::Drawing::Point(83, 345);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(91, 28);
			this->button1->TabIndex = 5;
			this->button1->Text = L"SIGN IN";
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// button2
			// 
			this->button2->BackColor = System::Drawing::Color::White;
			this->button2->FlatAppearance->BorderSize = 0;
			this->button2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold));
			this->button2->ForeColor = System::Drawing::Color::SteelBlue;
			this->button2->Location = System::Drawing::Point(196, 345);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(91, 28);
			this->button2->TabIndex = 6;
			this->button2->Text = L"SIGN UP";
			this->button2->UseVisualStyleBackColor = false;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// button3
			// 
			this->button3->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->button3->BackColor = System::Drawing::Color::Transparent;
			this->button3->FlatAppearance->BorderSize = 0;
			this->button3->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button3->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Bold));
			this->button3->ForeColor = System::Drawing::Color::White;
			this->button3->Location = System::Drawing::Point(93, 421);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(168, 28);
			this->button3->TabIndex = 7;
			this->button3->Text = L"Забыли пароль\?";
			this->button3->UseVisualStyleBackColor = false;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			// 
			// button4
			// 
			this->button4->BackColor = System::Drawing::Color::Transparent;
			this->button4->FlatAppearance->BorderSize = 0;
			this->button4->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12.25F));
			this->button4->ForeColor = System::Drawing::Color::White;
			this->button4->Location = System::Drawing::Point(329, -2);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(38, 25);
			this->button4->TabIndex = 8;
			this->button4->Text = L"X";
			this->button4->UseVisualStyleBackColor = false;
			this->button4->Click += gcnew System::EventHandler(this, &MyForm::button4_Click);
			// 
			// button5
			// 
			this->button5->BackColor = System::Drawing::Color::Transparent;
			this->button5->FlatAppearance->BorderSize = 0;
			this->button5->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12.25F));
			this->button5->ForeColor = System::Drawing::Color::White;
			this->button5->Location = System::Drawing::Point(295, -2);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(38, 25);
			this->button5->TabIndex = 9;
			this->button5->Text = L"—";
			this->button5->UseVisualStyleBackColor = false;
			this->button5->Click += gcnew System::EventHandler(this, &MyForm::button5_Click);
			// 
			// MyForm
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->ClientSize = System::Drawing::Size(368, 449);
			this->Controls->Add(this->button5);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->pass);
			this->Controls->Add(this->user);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->KeyPreview = true;
			this->Name = L"MyForm";
			this->ShowIcon = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyDown);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button4_Click(System::Object^ sender, System::EventArgs^ e) {
		Application::Exit();
	}
	private: System::Void button5_Click(System::Object^ sender, System::EventArgs^ e) {
		MyForm::Hide();
	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		if (user->Text->Trim() == "" || user->Text->Trim() == "Имя пользователя" || pass->Text->Trim() == "" || pass->Text->Trim() == "Пароль") {
			MessageBox::Show("Emty field", "Alert");
		}
		else {
			String^ query = "SELECT * FROM students WHERE username = @user AND password = @pass";
			auto conn = gcnew SQLiteConnection("Data Source=Students.db;Version=3;");
			conn->Open();
			auto cmd = gcnew SQLiteCommand(query, conn);
			cmd->Parameters->AddWithValue("@user", user->Text);
			cmd->Parameters->AddWithValue("@pass", pass->Text);
			auto da = gcnew SQLiteDataAdapter(cmd);
			auto dt = gcnew DataTable();
			da->Fill(dt);

			if (dt->Rows->Count > 0) {
				MyForm2^ Form3 = gcnew MyForm2();
				Form3->Show();
				user->Text = "", pass->Text = "";
			}
			else {
				MessageBox::Show("Username or password is entered incorrectly", "Alert");
			}
		}
	}
	private: System::Void user_Enter(System::Object^ sender, System::EventArgs^ e) {
		if (user->Text == "Имя пользователя") {
			user->Text = "";
			this->user->ForeColor = System::Drawing::Color::White;
		}
	}
	private: System::Void user_Leave(System::Object^ sender, System::EventArgs^ e) {
		if (user->Text == "") {
			user->Text = "Имя пользователя";
			this->user->ForeColor = System::Drawing::Color::Silver;
		}
	}
	private: System::Void pass_Enter(System::Object^ sender, System::EventArgs^ e) {
		if (pass->Text == "Пароль") {
			pass->Text = "";
			this->pass->ForeColor = System::Drawing::Color::White;
		}
	}
	private: System::Void pass_Leave(System::Object^ sender, System::EventArgs^ e) {
		if (pass->Text == "") {
			pass->Text = "Пароль";
			this->pass->ForeColor = System::Drawing::Color::Silver;
		}
	}
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
		MyForm1^ Form2 = gcnew MyForm1();
		Form2->Show();
	}
	private: System::Void MyForm_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		if (e->KeyCode == Keys::Enter) {
			button1_Click(button1, nullptr);
		}
	}
	private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
		MyForm3^ Form4 = gcnew MyForm3();
		Form4->Show();
	}
};
}
