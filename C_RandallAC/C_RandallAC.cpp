#include "pch.h"
#include "InterfazGrafica.h"
#define _CRT_SECURE_NO_WARNINGS
using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
int main(array<String^>^ args) {
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    Application::Run(gcnew CRandallAC::InterfazGrafica());
    return 0;
}