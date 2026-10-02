#pragma once

#include <msclr\marshal_cppstd.h>
#include <vcclr.h>
#include <sstream>
#include <string>
#include <vector>
#include <utility>

#include "..\..\tp1\entitee.h"

extern gcroot<System::Windows::Forms::RichTextBox^> richTextBox1;

void simuler_avec_parametres(int duree_simu, int interarrivee, int duree_traitement, std::vector<std::pair<int, int>>& points_systeme);

namespace ConsoleApplication1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	using namespace msclr::interop;

	/// <summary>
	/// Description resumee de form_main
	/// </summary>
	public ref class form_main : public System::Windows::Forms::Form
	{
	public:
		form_main(void)
		{
			InitializeComponent();
			::richTextBox1 = this->richTextBox1;
		}

	protected:
		/// <summary>
		/// Nettoyage des ressources utilisees.
		/// </summary>
		~form_main()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label1;
	protected:
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::TextBox^  textBox2;


	private: System::Windows::Forms::Button^  button1;

	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::TextBox^ textBox4;
	private: System::Windows::Forms::RichTextBox^ richTextBox1;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^ chart1;

	private:
		/// <summary>
		/// Variable necessaire au concepteur.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Methode requise pour la prise en charge du concepteur - ne modifiez pas
		/// le contenu de cette methode avec l'editeur de code.
		/// </summary>
		void InitializeComponent(void)
		{
			System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^ legend1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^ series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->chart1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->BeginInit();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(27, 27);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(111, 13);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Durée de la simulation";
			this->label1->Click += gcnew System::EventHandler(this, &form_main::label1_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(46, 53);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(92, 13);
			this->label2->TabIndex = 1;
			this->label2->Text = L"Durée Interarrivée";
			this->label2->Click += gcnew System::EventHandler(this, &form_main::label2_Click);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(144, 24);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(100, 20);
			this->textBox1->TabIndex = 2;
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &form_main::textBox1_TextChanged);
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(144, 50);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(100, 20);
			this->textBox2->TabIndex = 3;
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"Modern No. 20", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button1->Location = System::Drawing::Point(395, 12);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(212, 38);
			this->button1->TabIndex = 6;
			this->button1->Text = L"Lancer la simulation";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &form_main::button1_Click);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(34, 81);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(104, 13);
			this->label4->TabIndex = 8;
			this->label4->Text = L"Durée de Traitement";
			this->label4->Click += gcnew System::EventHandler(this, &form_main::label4_Click);
			// 
			// textBox4
			// 
			this->textBox4->Location = System::Drawing::Point(144, 74);
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(100, 20);
			this->textBox4->TabIndex = 9;
			// 
			// richTextBox1
			// 
			this->richTextBox1->BackColor = System::Drawing::Color::Black;
			this->richTextBox1->Font = (gcnew System::Drawing::Font(L"Consolas", 10.0F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->richTextBox1->ForeColor = System::Drawing::Color::NavajoWhite;
			this->richTextBox1->Location = System::Drawing::Point(550, 127);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->Size = System::Drawing::Size(620, 520);
			this->richTextBox1->TabIndex = 10;
			this->richTextBox1->Text = L"";
			this->richTextBox1->TextChanged += gcnew System::EventHandler(this, &form_main::richTextBox1_TextChanged);
			// 
			// chart1
			// 
			this->chart1->BackColor = System::Drawing::Color::WhiteSmoke;
			this->chart1->BorderlineColor = System::Drawing::Color::Black;
			chartArea1->Name = L"ChartArea1";
			this->chart1->ChartAreas->Add(chartArea1);
			legend1->Name = L"Legend1";
			this->chart1->Legends->Add(legend1);
			this->chart1->Location = System::Drawing::Point(27, 127);
			this->chart1->Name = L"chart1";
			series1->ChartArea = L"ChartArea1";
			series1->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::StepLine;
			series1->Legend = L"Legend1";
			series1->Name = L"Series1";
			series1->BorderWidth = 2;
			series1->Color = System::Drawing::Color::SteelBlue;
			this->chart1->Series->Add(series1);
			this->chart1->Size = System::Drawing::Size(500, 520);
			this->chart1->TabIndex = 11;
			this->chart1->Text = L"chart1";
			this->chart1->Click += gcnew System::EventHandler(this, &form_main::chart1_Click);
			// 
			// form_main
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1208, 701);
			this->Controls->Add(this->chart1);
			this->Controls->Add(this->richTextBox1);
			this->Controls->Add(this->textBox4);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Name = L"form_main";
			this->Text = L"Simulation de bureau de poste";
			this->Load += gcnew System::EventHandler(this, &form_main::form_main_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		try {
			::richTextBox1 = this->richTextBox1;
			this->richTextBox1->Clear();

			int duree_simu = 32;
			int interarrivee = 2;
			int duree_traitement = 4;

			if (!System::Int32::TryParse(this->textBox1->Text, duree_simu) || duree_simu <= 0)
				duree_simu = 32;
			if (!System::Int32::TryParse(this->textBox2->Text, interarrivee) || interarrivee <= 0)
				interarrivee = 2;
			if (!System::Int32::TryParse(this->textBox4->Text, duree_traitement) || duree_traitement <= 0)
				duree_traitement = 4;

			this->textBox1->Text = duree_simu.ToString();
			this->textBox2->Text = interarrivee.ToString();
			this->textBox4->Text = duree_traitement.ToString();

			std::vector<std::pair<int, int>> points_systeme;
			simuler_avec_parametres(duree_simu, interarrivee, duree_traitement, points_systeme);

			int max_systeme = 0;
			for (size_t i = 0; i < points_systeme.size(); ++i) {
				if (points_systeme[i].second > max_systeme) max_systeme = points_systeme[i].second;
			}

			this->chart1->Series["Series1"]->Points->Clear();
			this->chart1->Series["Series1"]->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::StepLine;
			this->chart1->Series["Series1"]->LegendText = L"Clients dans le système";
			this->chart1->Series["Series1"]->BorderWidth = 2;
			this->chart1->Series["Series1"]->Color = System::Drawing::Color::SteelBlue;

			this->chart1->ChartAreas["ChartArea1"]->AxisX->Title = L"Temps (t)";
			this->chart1->ChartAreas["ChartArea1"]->AxisY->Title = L"Nombre de clients dans tout le système";
			this->chart1->ChartAreas["ChartArea1"]->AxisY->Interval = (max_systeme > 20) ? (max_systeme / 10) : 1;
			this->chart1->ChartAreas["ChartArea1"]->AxisY->Minimum = 0;
			this->chart1->ChartAreas["ChartArea1"]->AxisY->Maximum = (max_systeme < 5) ? 5 : (max_systeme + 1);
			this->chart1->ChartAreas["ChartArea1"]->AxisX->Minimum = 0;

			for (size_t i = 0; i < points_systeme.size(); ++i) {
				this->chart1->Series["Series1"]->Points->AddXY(points_systeme[i].first, points_systeme[i].second);
			}
		}
		catch (System::Exception^ ex) {
			this->richTextBox1->AppendText(L"\nErreur : " + ex->Message + L"\n");
		}
	}
private: System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void label3_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void label2_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void form_main_Load(System::Object^ sender, System::EventArgs^ e) {
	if (System::String::IsNullOrEmpty(this->textBox1->Text)) this->textBox1->Text = L"32";
	if (System::String::IsNullOrEmpty(this->textBox2->Text)) this->textBox2->Text = L"2";
	if (System::String::IsNullOrEmpty(this->textBox4->Text)) this->textBox4->Text = L"4";

	this->chart1->Series["Series1"]->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::StepLine;
	this->chart1->Series["Series1"]->LegendText = L"Clients dans le système";
	this->chart1->Series["Series1"]->BorderWidth = 2;
	this->chart1->Series["Series1"]->Color = System::Drawing::Color::SteelBlue;

	this->chart1->ChartAreas["ChartArea1"]->AxisX->Title = L"Temps (t)";
	this->chart1->ChartAreas["ChartArea1"]->AxisY->Title = L"Nombre de clients dans tout le système";
	this->chart1->ChartAreas["ChartArea1"]->AxisY->Interval = 1;
	this->chart1->ChartAreas["ChartArea1"]->AxisY->Minimum = 0;
	this->chart1->ChartAreas["ChartArea1"]->AxisY->Maximum = 10;
	this->chart1->ChartAreas["ChartArea1"]->AxisX->Minimum = 0;
}
private: System::Void label4_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void richTextBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void chart1_Click(System::Object^ sender, System::EventArgs^ e) {
}
};
}
