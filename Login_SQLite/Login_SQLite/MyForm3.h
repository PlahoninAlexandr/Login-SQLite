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
	/// Сводка для MyForm3
	/// </summary>
	public ref class MyForm3 : public System::Windows::Forms::Form
	{
	public:
		MyForm3(void)
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
		~MyForm3()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ button5;
	protected:
	private: System::Windows::Forms::Button^ button4;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::TextBox^ mail;

	private: System::Windows::Forms::TextBox^ pass;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Button^ button2;

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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm3::typeid));
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->mail = (gcnew System::Windows::Forms::TextBox());
			this->pass = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
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
			this->button5->TabIndex = 13;
			this->button5->Text = L"—";
			this->button5->UseVisualStyleBackColor = false;
			this->button5->Click += gcnew System::EventHandler(this, &MyForm3::button5_Click);
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
			this->button4->TabIndex = 12;
			this->button4->Text = L"X";
			this->button4->UseVisualStyleBackColor = false;
			this->button4->Click += gcnew System::EventHandler(this, &MyForm3::button4_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::Color::Transparent;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 23.25F));
			this->label1->ForeColor = System::Drawing::Color::White;
			this->label1->Location = System::Drawing::Point(100, 34);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(191, 35);
			this->label1->TabIndex = 14;
			this->label1->Text = L"🅡🅔🅒🅞🅥🅔🅡🅨";
			this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->BackColor = System::Drawing::Color::Transparent;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label2->ForeColor = System::Drawing::Color::White;
			this->label2->Location = System::Drawing::Point(78, 123);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(196, 29);
			this->label2->TabIndex = 15;
			this->label2->Text = L"Введите почту";
			// 
			// mail
			// 
			this->mail->BackColor = System::Drawing::SystemColors::MenuHighlight;
			this->mail->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->mail->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 18, System::Drawing::FontStyle::Bold));
			this->mail->ForeColor = System::Drawing::Color::Silver;
			this->mail->Location = System::Drawing::Point(62, 174);
			this->mail->Name = L"mail";
			this->mail->Size = System::Drawing::Size(250, 32);
			this->mail->TabIndex = 16;
			this->mail->Text = L"Mail";
			this->mail->Enter += gcnew System::EventHandler(this, &MyForm3::mail_Enter);
			this->mail->Leave += gcnew System::EventHandler(this, &MyForm3::mail_Leave);
			// 
			// pass
			// 
			this->pass->BackColor = System::Drawing::SystemColors::MenuHighlight;
			this->pass->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->pass->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 18, System::Drawing::FontStyle::Bold));
			this->pass->ForeColor = System::Drawing::Color::Silver;
			this->pass->Location = System::Drawing::Point(62, 278);
			this->pass->Name = L"pass";
			this->pass->Size = System::Drawing::Size(250, 32);
			this->pass->TabIndex = 18;
			this->pass->Text = L"Password";
			this->pass->Enter += gcnew System::EventHandler(this, &MyForm3::pass_Enter);
			this->pass->Leave += gcnew System::EventHandler(this, &MyForm3::pass_Leave);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->BackColor = System::Drawing::Color::Transparent;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label3->ForeColor = System::Drawing::Color::White;
			this->label3->Location = System::Drawing::Point(32, 233);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(301, 29);
			this->label3->TabIndex = 19;
			this->label3->Text = L"Введите новый пароль";
			// 
			// button2
			// 
			this->button2->BackColor = System::Drawing::Color::White;
			this->button2->FlatAppearance->BorderSize = 0;
			this->button2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold));
			this->button2->ForeColor = System::Drawing::Color::SteelBlue;
			this->button2->Location = System::Drawing::Point(106, 327);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(155, 28);
			this->button2->TabIndex = 20;
			this->button2->Text = L"Далее";
			this->button2->UseVisualStyleBackColor = false;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm3::button2_Click);
			// 
			// MyForm3
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->ClientSize = System::Drawing::Size(368, 449);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->pass);
			this->Controls->Add(this->mail);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button5);
			this->Controls->Add(this->button4);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->KeyPreview = true;
			this->Name = L"MyForm3";
			this->ShowIcon = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm3::MyForm3_KeyDown);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
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
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
		if (mail->Text->Trim() == "" || mail->Text->Trim() == "Mail" || pass->Text->Trim() == "" || pass->Text->Trim() == "Password") {
			MessageBox::Show("Emty field", "Alert");
		}
		else {
			String^ query = "SELECT * FROM students WHERE mail = @mail";
			auto conn = gcnew SQLiteConnection("Data Source=Students.db;Version=3;");
			conn->Open();
			auto cmd = gcnew SQLiteCommand(query, conn);
			cmd->Parameters->AddWithValue("@mail", mail->Text);
			auto da = gcnew SQLiteDataAdapter(cmd);
			auto dt = gcnew DataTable();
			da->Fill(dt);

			if (dt->Rows->Count > 0) {
				String^ query = "UPDATE students SET password = @pass WHERE mail = @mail";
				auto conn = gcnew SQLiteConnection("Data Source=Students.db;Version=3;");
				conn->Open();
				auto cmd = gcnew SQLiteCommand(query, conn);
				cmd->Parameters->AddWithValue("@mail", mail->Text);
				cmd->Parameters->AddWithValue("@pass", pass->Text);
				auto da = gcnew SQLiteDataAdapter(cmd);
				auto dt = gcnew DataTable();
				da->Fill(dt);
				MessageBox::Show("Password changed", "Alert");
				MyForm3::Close();
			}
			else {
				MessageBox::Show("mail is entered incorrectly", "Alert");
			}
		}
	}
	private: System::Void button4_Click(System::Object^ sender, System::EventArgs^ e) {
		Application::Exit();
	}
	private: System::Void button5_Click(System::Object^ sender, System::EventArgs^ e) {
		MyForm3::Hide();
	}
	private: System::Void MyForm3_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		if (e->KeyCode == Keys::Enter) {
			button2_Click(button2, nullptr);
		}
	}
};
}
