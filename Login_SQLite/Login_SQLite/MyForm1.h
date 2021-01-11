#pragma once

namespace LoginSQLite {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Data::SQLite;

	/// <summary>
	/// Сводка для MyForm1
	/// </summary>
	public ref class MyForm1 : public System::Windows::Forms::Form
	{
	public:
		MyForm1(void)
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
		~MyForm1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::TextBox^ login;
	private: System::Windows::Forms::TextBox^ mail;
	private: System::Windows::Forms::TextBox^ pass;
	private: System::Windows::Forms::CheckBox^ chek;





	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Button^ button5;
	private: System::Windows::Forms::Button^ button4;
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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm1::typeid));
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->login = (gcnew System::Windows::Forms::TextBox());
			this->mail = (gcnew System::Windows::Forms::TextBox());
			this->pass = (gcnew System::Windows::Forms::TextBox());
			this->chek = (gcnew System::Windows::Forms::CheckBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
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
			this->label1->TabIndex = 0;
			this->label1->Text = L" 🅢🅐🅚🅤🅡🅐🅢🅞";
			// 
			// login
			// 
			this->login->BackColor = System::Drawing::SystemColors::MenuHighlight;
			this->login->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->login->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 18, System::Drawing::FontStyle::Bold));
			this->login->ForeColor = System::Drawing::Color::Silver;
			this->login->Location = System::Drawing::Point(62, 127);
			this->login->Name = L"login";
			this->login->Size = System::Drawing::Size(250, 32);
			this->login->TabIndex = 4;
			this->login->Text = L"Login";
			this->login->Enter += gcnew System::EventHandler(this, &MyForm1::login_Enter);
			this->login->Leave += gcnew System::EventHandler(this, &MyForm1::login_Leave);
			// 
			// mail
			// 
			this->mail->BackColor = System::Drawing::SystemColors::MenuHighlight;
			this->mail->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->mail->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 18, System::Drawing::FontStyle::Bold));
			this->mail->ForeColor = System::Drawing::Color::Silver;
			this->mail->Location = System::Drawing::Point(62, 184);
			this->mail->Name = L"mail";
			this->mail->Size = System::Drawing::Size(250, 32);
			this->mail->TabIndex = 5;
			this->mail->Text = L"Mail";
			this->mail->Enter += gcnew System::EventHandler(this, &MyForm1::mail_Enter);
			this->mail->Leave += gcnew System::EventHandler(this, &MyForm1::mail_Leave);
			// 
			// pass
			// 
			this->pass->BackColor = System::Drawing::SystemColors::MenuHighlight;
			this->pass->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->pass->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 18, System::Drawing::FontStyle::Bold));
			this->pass->ForeColor = System::Drawing::Color::Silver;
			this->pass->Location = System::Drawing::Point(62, 240);
			this->pass->Name = L"pass";
			this->pass->Size = System::Drawing::Size(250, 32);
			this->pass->TabIndex = 6;
			this->pass->Text = L"Password";
			this->pass->Enter += gcnew System::EventHandler(this, &MyForm1::pass_Enter);
			this->pass->Leave += gcnew System::EventHandler(this, &MyForm1::pass_Leave);
			// 
			// chek
			// 
			this->chek->AutoSize = true;
			this->chek->BackColor = System::Drawing::Color::Transparent;
			this->chek->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.25F));
			this->chek->ForeColor = System::Drawing::Color::White;
			this->chek->Location = System::Drawing::Point(62, 294);
			this->chek->Name = L"chek";
			this->chek->Size = System::Drawing::Size(231, 20);
			this->chek->TabIndex = 7;
			this->chek->Text = L"пользовательское соглашение";
			this->chek->UseVisualStyleBackColor = false;
			// 
			// button1
			// 
			this->button1->BackColor = System::Drawing::Color::White;
			this->button1->FlatAppearance->BorderSize = 0;
			this->button1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold));
			this->button1->ForeColor = System::Drawing::Color::SteelBlue;
			this->button1->Location = System::Drawing::Point(111, 351);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(141, 52);
			this->button1->TabIndex = 8;
			this->button1->Text = L"REGISTER";
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm1::button1_Click);
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
			this->button5->TabIndex = 11;
			this->button5->Text = L"—";
			this->button5->UseVisualStyleBackColor = false;
			this->button5->Click += gcnew System::EventHandler(this, &MyForm1::button5_Click);
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
			this->button4->TabIndex = 10;
			this->button4->Text = L"X";
			this->button4->UseVisualStyleBackColor = false;
			this->button4->Click += gcnew System::EventHandler(this, &MyForm1::button4_Click);
			// 
			// MyForm1
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->ClientSize = System::Drawing::Size(368, 449);
			this->Controls->Add(this->button5);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->chek);
			this->Controls->Add(this->pass);
			this->Controls->Add(this->mail);
			this->Controls->Add(this->login);
			this->Controls->Add(this->label1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->KeyPreview = true;
			this->Name = L"MyForm1";
			this->ShowIcon = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button4_Click(System::Object^ sender, System::EventArgs^ e) {
		Application::Exit();
	}
	private: System::Void button5_Click(System::Object^ sender, System::EventArgs^ e) {
		MyForm1::Hide();
	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		if (login->Text->Trim() == "" && mail->Text->Trim() == "" && pass->Text->Trim() == "") {
			MessageBox::Show("emty field", "error");
		}
		else if (chek->CheckState == CheckState::Unchecked) {
			MessageBox::Show("Read the agreement", "Alert");
		}
		else {
			String^ query = "INSERT INTO students (username, mail, password) VALUES (@login, @mail, @pass)";
			auto conn = gcnew SQLiteConnection("Data Source=Students.db;Version=3;");
			conn->Open();
			auto cmd = gcnew SQLiteCommand(query, conn);
			cmd->Parameters->AddWithValue("@login", login->Text);
			cmd->Parameters->AddWithValue("@mail", mail->Text);
			cmd->Parameters->AddWithValue("@pass", pass->Text);
			auto da = gcnew SQLiteDataAdapter(cmd);
			auto dt = gcnew DataTable();
			da->Fill(dt);
			MessageBox::Show("You create account", "Alert");
			MyForm1::Close();
		}
	}
	private: System::Void login_Enter(System::Object^ sender, System::EventArgs^ e) {
		if (login->Text == "Login") {
			login->Text = "";
			this->login->ForeColor = System::Drawing::Color::White;
		}
	}
	private: System::Void login_Leave(System::Object^ sender, System::EventArgs^ e) {
		if (login->Text == "") {
			login->Text = "Login";
			this->login->ForeColor = System::Drawing::Color::Silver;
		}
	}
	private: System::Void mail_Enter(System::Object^ sender, System::EventArgs^ e) {
		if (mail->Text == "Mail") {
			mail->Text = "";
			this->mail->ForeColor = System::Drawing::Color::White;
		}
	}
	private: System::Void mail_Leave(System::Object^ sender, System::EventArgs^ e) {
		if (mail->Text == "") {
			mail->Text = "Mail";
			this->mail->ForeColor = System::Drawing::Color::Silver;
		}
	}
	private: System::Void pass_Enter(System::Object^ sender, System::EventArgs^ e) {
		if (pass->Text == "Password") {
			pass->Text = "";
			this->pass->ForeColor = System::Drawing::Color::White;
		}
	}
	private: System::Void pass_Leave(System::Object^ sender, System::EventArgs^ e) {
		if (pass->Text == "") {
			pass->Text = "Password";
			this->pass->ForeColor = System::Drawing::Color::Silver;
		}
	}
};
}
