#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "GeneradorCodigo.h"
#include "ParserNatural.h"
#include <msclr/marshal_cppstd.h>
#include <iostream>
namespace CRandallAC {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	
	/// <summary>
	/// Resumen de InterfazGrafica
	/// </summary>
	public ref class InterfazGrafica : public System::Windows::Forms::Form
	{
	public:
		InterfazGrafica(void)
		{
			InitializeComponent();
			//
			//TODO: agregar código de constructor aquí
			//
		}

	protected:
		/// <summary>
		/// Limpiar los recursos que se estén usando.
		/// </summary>
		~InterfazGrafica()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ btnCargarTXT;
	private: System::Windows::Forms::Label^ txtTitulo;
	private: System::Windows::Forms::PictureBox^ LOGO;
	private: System::Windows::Forms::Label^ txtNombrePrograma;

	private: System::Windows::Forms::Button^ btnEjecutar;
	private: System::Windows::Forms::Button^ btnGenerarCPP;








	protected:

	protected:

	private:
		/// <summary>
		/// Variable del diseñador necesaria.
		/// </summary>
		System::ComponentModel::Container^ components;
	private: System::Windows::Forms::Button^ btnSalir;
		   GeneradorCodigo* generadorGlobal;
		   // Variable global para guardar la ruta del archivo cargado
		   String^ rutaArchivo = nullptr;
#pragma region Windows Form Designer generated code
		   /// <summary>
		   /// Método necesario para admitir el Diseñador. No se puede modificar
		   /// el contenido de este método con el editor de código.
		   /// </summary>
		   void InitializeComponent(void)
		   {
			   System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(InterfazGrafica::typeid));
			   this->btnCargarTXT = (gcnew System::Windows::Forms::Button());
			   this->txtTitulo = (gcnew System::Windows::Forms::Label());
			   this->LOGO = (gcnew System::Windows::Forms::PictureBox());
			   this->txtNombrePrograma = (gcnew System::Windows::Forms::Label());
			   this->btnEjecutar = (gcnew System::Windows::Forms::Button());
			   this->btnGenerarCPP = (gcnew System::Windows::Forms::Button());
			   this->btnSalir = (gcnew System::Windows::Forms::Button());
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->LOGO))->BeginInit();
			   this->SuspendLayout();
			   // 
			   // btnCargarTXT
			   // 
			   this->btnCargarTXT->BackColor = System::Drawing::SystemColors::HotTrack;
			   this->btnCargarTXT->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei UI", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   this->btnCargarTXT->ForeColor = System::Drawing::Color::Black;
			   this->btnCargarTXT->Location = System::Drawing::Point(659, 189);
			   this->btnCargarTXT->Name = L"btnCargarTXT";
			   this->btnCargarTXT->Size = System::Drawing::Size(292, 77);
			   this->btnCargarTXT->TabIndex = 0;
			   this->btnCargarTXT->Text = L"CARGAR .TXT";
			   this->btnCargarTXT->UseVisualStyleBackColor = false;
			   this->btnCargarTXT->Click += gcnew System::EventHandler(this, &InterfazGrafica::button1_Click);
			   // 
			   // txtTitulo
			   // 
			   this->txtTitulo->AutoSize = true;
			   this->txtTitulo->BackColor = System::Drawing::SystemColors::MenuHighlight;
			   this->txtTitulo->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei UI", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   this->txtTitulo->Location = System::Drawing::Point(540, 91);
			   this->txtTitulo->Name = L"txtTitulo";
			   this->txtTitulo->Size = System::Drawing::Size(512, 27);
			   this->txtTitulo->TabIndex = 1;
			   this->txtTitulo->Text = L"Bienvenido(a) al sistema de carga de Archivos.txt";
			   this->txtTitulo->Click += gcnew System::EventHandler(this, &InterfazGrafica::label1_Click);
			   // 
			   // LOGO
			   // 
			   this->LOGO->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"LOGO.Image")));
			   this->LOGO->Location = System::Drawing::Point(31, 91);
			   this->LOGO->Name = L"LOGO";
			   this->LOGO->Size = System::Drawing::Size(440, 519);
			   this->LOGO->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			   this->LOGO->TabIndex = 2;
			   this->LOGO->TabStop = false;
			   this->LOGO->Click += gcnew System::EventHandler(this, &InterfazGrafica::pictureBox1_Click);
			   // 
			   // txtNombrePrograma
			   // 
			   this->txtNombrePrograma->AutoSize = true;
			   this->txtNombrePrograma->BackColor = System::Drawing::SystemColors::Highlight;
			   this->txtNombrePrograma->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei UI", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   this->txtNombrePrograma->Location = System::Drawing::Point(1123, 294);
			   this->txtNombrePrograma->Name = L"txtNombrePrograma";
			   this->txtNombrePrograma->Size = System::Drawing::Size(185, 31);
			   this->txtNombrePrograma->TabIndex = 3;
			   this->txtNombrePrograma->Text = L"CRANDALL_AC";
			   this->txtNombrePrograma->Click += gcnew System::EventHandler(this, &InterfazGrafica::label1_Click_1);
			   // 
			   // btnEjecutar
			   // 
			   this->btnEjecutar->BackColor = System::Drawing::SystemColors::HotTrack;
			   this->btnEjecutar->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei UI", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   this->btnEjecutar->Location = System::Drawing::Point(659, 359);
			   this->btnEjecutar->Name = L"btnEjecutar";
			   this->btnEjecutar->Size = System::Drawing::Size(292, 77);
			   this->btnEjecutar->TabIndex = 4;
			   this->btnEjecutar->Text = L"EJECUTAR TXT";
			   this->btnEjecutar->UseVisualStyleBackColor = false;
			   this->btnEjecutar->Click += gcnew System::EventHandler(this, &InterfazGrafica::btnEjecutar_Click);
			   // 
			   // btnGenerarCPP
			   // 
			   this->btnGenerarCPP->BackColor = System::Drawing::Color::Teal;
			   this->btnGenerarCPP->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei UI", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   this->btnGenerarCPP->Location = System::Drawing::Point(659, 543);
			   this->btnGenerarCPP->Name = L"btnGenerarCPP";
			   this->btnGenerarCPP->Size = System::Drawing::Size(292, 67);
			   this->btnGenerarCPP->TabIndex = 5;
			   this->btnGenerarCPP->Text = L"GENERAR .CPP";
			   this->btnGenerarCPP->UseVisualStyleBackColor = false;
			   this->btnGenerarCPP->Click += gcnew System::EventHandler(this, &InterfazGrafica::btnGenerar_Click);
			   // 
			   // btnSalir
			   // 
			   this->btnSalir->BackColor = System::Drawing::Color::Red;
			   this->btnSalir->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei UI", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   this->btnSalir->ForeColor = System::Drawing::Color::Cornsilk;
			   this->btnSalir->Location = System::Drawing::Point(1143, 467);
			   this->btnSalir->Name = L"btnSalir";
			   this->btnSalir->Size = System::Drawing::Size(165, 56);
			   this->btnSalir->TabIndex = 7;
			   this->btnSalir->Text = L"SALIR";
			   this->btnSalir->UseVisualStyleBackColor = false;
			   this->btnSalir->Click += gcnew System::EventHandler(this, &InterfazGrafica::button1_Click_1);
			   // 
			   // InterfazGrafica
			   // 
			   this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->BackColor = System::Drawing::SystemColors::InactiveCaption;
			   this->ClientSize = System::Drawing::Size(1511, 805);
			   this->Controls->Add(this->btnSalir);
			   this->Controls->Add(this->btnGenerarCPP);
			   this->Controls->Add(this->btnEjecutar);
			   this->Controls->Add(this->txtNombrePrograma);
			   this->Controls->Add(this->LOGO);
			   this->Controls->Add(this->txtTitulo);
			   this->Controls->Add(this->btnCargarTXT);
			   this->Name = L"InterfazGrafica";
			   this->Text = L"InterfazGrafica";
			   this->Load += gcnew System::EventHandler(this, &InterfazGrafica::InterfazGrafica_Load);
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->LOGO))->EndInit();
			   this->ResumeLayout(false);
			   this->PerformLayout();

		   }
#pragma endregion
	private: System::Void InterfazGrafica_Load(System::Object^ sender, System::EventArgs^ e) {
	}

private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
	OpenFileDialog^ dialogo = gcnew OpenFileDialog();
	dialogo->Filter = "Archivos de texto (*.txt)|*.txt";

	if (dialogo->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
		rutaArchivo = dialogo->FileName; // Guardar ruta globalmente
		Console::Clear();
		String^ contenido = System::IO::File::ReadAllText(rutaArchivo);
		Console::WriteLine("Contenido del archivo:\n" + contenido);
		Console::WriteLine("\n");
	}
}

	private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void pictureBox1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label1_Click_1(System::Object^ sender, System::EventArgs^ e) {
	}

	private: System::Void btnEjecutar_Click(System::Object^ sender, System::EventArgs^ e) {
		if (rutaArchivo == nullptr) {
			Console::WriteLine("Primero carga un archivo con el boton 'Cargar'.");
			return;
		}

		String^ contenido = System::IO::File::ReadAllText(rutaArchivo);
		if (String::IsNullOrWhiteSpace(contenido)) {
			Console::WriteLine("El archivo esta vacio.");
			return;
		}

		array<String^>^ lineas = contenido->Split(gcnew array<wchar_t>{'\n'}, StringSplitOptions::RemoveEmptyEntries);

		// Reiniciar generador y limpiar archivo anterior
		if (generadorGlobal != nullptr) {
			delete generadorGlobal;
			generadorGlobal = nullptr;
		}
		if (System::IO::File::Exists("salida.txt")) {
			System::IO::File::Delete("salida.txt");
		}

		ParserNatural parser;
		generadorGlobal = new GeneradorCodigo();
		int numeroLinea = 1;
		for each (String ^ linea in lineas) {
			msclr::interop::marshal_context context;
			std::string stdLinea = context.marshal_as<std::string>(linea);
			char lineaC[256];
			strcpy(lineaC, stdLinea.c_str());

			char salidaC[256];
			parser.parseLinea(lineaC, salidaC);

			if (strstr(salidaC, "// Error:") != nullptr) {
				Console::WriteLine("// Error en línea " + numeroLinea + ": " + gcnew String(linea));
				Console::WriteLine(gcnew String(salidaC));
				Console::WriteLine("// Se detecto un error.  Corrige el archivo antes de continuar.");
				return;
			}
			generadorGlobal->agregar(salidaC, true);  // Agregar con indentación dentro del main
			numeroLinea++;
		}

		generadorGlobal->finalizar();                      // Agrega return 0; y cierre de llave
		generadorGlobal->imprimirCodigo();                 // Muestra el programa completo en consola
		generadorGlobal->generarArchivo("salida.txt");     // Exporta el archivo final
		Console::WriteLine("// Proceso completado. Código listo para exportar.");
	}

	private: System::Void richTextBox2_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}

	private: System::Void btnGenerar_Click(System::Object^ sender, System::EventArgs^ e) {
		if (generadorGlobal == nullptr) {
			Console::WriteLine("No hay codigo generado para exportar.");
			return;
		}

		try {
			// Ruta fija donde guardar el archivo (mismo directorio que el ejecutable)
			const char* nombreArchivo = "salida.txt";

			// Generar el archivo directamente sin pedir ruta al usuario
			generadorGlobal->generarArchivo(nombreArchivo);

			Console::WriteLine("//Codigo exportado automaticamente a salida.txt");
		}
		catch (Exception^ ex) {
			Console::WriteLine("Error: " + ex->Message);
		}

		// Liberar memoria
		if (generadorGlobal != nullptr) {
			delete generadorGlobal;
			generadorGlobal = nullptr;
		}
	}

	private: System::Void button1_Click_1(System::Object^ sender, System::EventArgs^ e) {
		System::Windows::Forms::DialogResult resultado = MessageBox::Show(
			"Seguro que quieres cerrar el programa?",
			"Confirmar salida",
			MessageBoxButtons::YesNo,
			MessageBoxIcon::Question
		);

		if (resultado == System::Windows::Forms::DialogResult::Yes) {
			Application::Exit();
		}
	}
	};
}
