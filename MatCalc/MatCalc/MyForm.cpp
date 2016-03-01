#include "MyForm.h"

using namespace System;
using namespace System::Windows::Forms;

#include "Matriz.h"

int GMode = -1, GVar = -1, GCmd = -1, GLast = -1;
Matriz * A = new Matriz();
Matriz * B = new Matriz();
Matriz * C = new Matriz();
Matriz * D = new Matriz();
Matriz * E = new Matriz();
Matriz * F = new Matriz();
Matriz * T = new Matriz();
static Matriz * Gpvar[] = { A, B, C, D, E, E, F };


void execCmd() {
	switch (GCmd) {
		case 0:
			execStore(GVar);
			break;
		case 1:
			execReclaim(GVar);
			break;
		case 2:
			execClear(GVar);
			break;
		}
	}

void execClear(int var) {
	Gpvar[var] -> Clear();
	}

void execStore(int var) {
	* Gpvar[var] = *T;
	}

void execReclaim(int var) {
	* T = * Gpvar[var];
	}

bool execVal(char * txt, char * msgerr) { return false;  }


[STAThread]
int main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	MatCalc::MyForm form;
	Application::Run(%form);
	}
