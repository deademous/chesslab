#include "chess_board.h"
#include <Windows.h>

using namespace System;
using namespace System::Windows::Forms;
using namespace chesslab;
[STAThread]
int main(array<System::String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew chess_board());
}