// ConsoleApplication1.cpp : fichier projet principal.

#include "stdafx.h"
#include "form_main.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
   Application::Run(gcnew ConsoleApplication1::form_main());

	return 0;
}

