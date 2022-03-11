#include "MyForm.h"


using namespace System;
using namespace System::Windows::Forms;
using namespace std;


[STAThread]
void Main(cli::array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	Game_Editor::MyForm form;
	Application::Run(%form);
}

