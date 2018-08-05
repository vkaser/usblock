//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit19.h"
#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm19 *Form19;
//---------------------------------------------------------------------------
__fastcall TForm19::TForm19(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm19::FormActivate(TObject *Sender)
{
Edit1->Clear();
Edit1->Font->Color = clBlack;
Edit1->PasswordChar = '\*';
if(FileExists("c:\\windows\\gl.obg"))
	Memo1->Lines->LoadFromFile("c:\\windows\\gl.obg");
else
	{
	 Label1->Caption = "Создайте пароль";
	 Button2->Visible = false;
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm19::Button1Click(TObject *Sender)
{
int f;
if(Edit1->Text == "")
	{
	 MessageBox(NULL,"Введите пароль","Предупреждение",MB_ICONEXCLAMATION);
	 return;
	}

if(Memo1->Lines->Strings[0] == "")
	 {
	  Memo1->Lines->Strings[0] = Edit1->Text;
	  MessageBox(NULL,"Пароль создан","Информация",MB_ICONINFORMATION);
	  Label1->Caption = "Введите пароль";
	  Edit1->Clear();
	  return;
	 }

if( (Edit1->Text != Memo1->Lines->Strings[0]) && (Edit2->Visible == false) )
		{
		 MessageBox(NULL,"Неверный пароль","Ошибка",MB_ICONSTOP);
		 Edit1->SetFocus();
		 Edit1->SelectAll();
		 return;
		}

if(Edit2->Visible == true)
	{
	 if( (Edit1->Text == Memo1->Lines->Strings[0]) && (Edit2->Text == Edit3->Text) )
		{
		 Memo1->Lines->Strings[0] = Edit3->Text;
		 Edit2->Visible = false;
		 Edit3->Visible = false;
		 Button2->Visible = true;
		 Label1->Caption = "Введите пароль";
		 Button3->Visible = false;
		 MessageBox(NULL,"Пароль изменен","Информация",MB_ICONINFORMATION);
		 Memo1->Lines->SaveToFile("c:\\windows\\gl.obg");
		 Edit1->Clear();
		 return;
		}
	else
		{
		 MessageBox(NULL,"Пароль не создан", "Предупреждение",MB_ICONEXCLAMATION);
		 Button2->OnClick;
		 return;
		}
	 }

//Пароль введен правильно
if(Edit1->Text == Memo1->Lines->Strings[0])
	{
	 if(FileExists("c:\\windows\\gl.obg"))
		Memo1->Lines->SaveToFile("c:\\windows\\gl.obg");
	 else
		{
		 f = FileCreate("c:\\windows\\gl.obg");
		 FileClose(f);
		 Memo1->Lines->SaveToFile("c:\\windows\\gl.obg");
		}
	 Form2->Show();
	 Form19->Hide();
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm19::Button2Click(TObject *Sender)
{
Label1->Caption = "Смена пароля";
Button2->Visible = false;
Edit1->Clear();
Edit1->SetFocus();
Edit2->Visible = true;
Edit3->Visible = true;
Button3->Visible = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm19::Edit1KeyPress(TObject *Sender, char &Key)
{
if(Key == ' ')
	{
	 Key = 0;
	 return;
	}
if( (Edit2->Visible == false) && (Key == VK_RETURN) )
	{
	 Button1->Click();
	 return;
	}
if( (Edit2->Visible == true) && (Key == VK_RETURN) )
	 Edit2->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TForm19::Edit2KeyPress(TObject *Sender, char &Key)
{
if(Key == '\ ')
	{
	 Key = 0;
	 return;
	}
if(Key == VK_RETURN)
	 Edit3->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TForm19::Edit3KeyPress(TObject *Sender, char &Key)
{
if(Key == VK_RETURN)
	 Button1->Click();
}
//---------------------------------------------------------------------------
void __fastcall TForm19::Edit1Exit(TObject *Sender)
{
if(Edit1->Text == "")
	{
	 Edit1->Font->Color = clScrollBar;
	 Edit1->PasswordChar = NULL;
	 Edit1->Text = "Пароль";
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm19::Edit2Exit(TObject *Sender)
{
if(Edit2->Text == "")
	{
	 Edit2->Font->Color = clScrollBar;
	 Edit2->PasswordChar = NULL;
	 Edit2->Text = "Новый пароль";
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm19::Edit3Exit(TObject *Sender)
{
if(Edit3->Text == "")
	{
	 Edit3->Font->Color = clScrollBar;
	 Edit3->PasswordChar = NULL;
	 Edit3->Text = "Подтверждение";
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm19::Edit1Enter(TObject *Sender)
{
if(Edit1->Text == "Пароль")
	Edit1->Clear();
else
	Edit1->SelectAll();
Edit1->PasswordChar = '\*';
Edit1->Font->Color = clBlack;
}
//---------------------------------------------------------------------------
void __fastcall TForm19::Edit2Enter(TObject *Sender)
{
if(Edit2->Text == "Новый пароль")
	Edit2->Clear();
else
	Edit2->SelectAll();
Edit2->PasswordChar = '\*';
Edit2->Font->Color = clBlack;
}
//---------------------------------------------------------------------------

void __fastcall TForm19::Edit3Enter(TObject *Sender)
{
if(Edit3->Text == "Подтверждение")
	Edit3->Clear();
else
	Edit3->SelectAll();
Edit3->PasswordChar = '\*';
Edit3->Font->Color = clBlack;
}
//---------------------------------------------------------------------------
void __fastcall TForm19::Button3Click(TObject *Sender)
{
Label1->Caption = "Введите пароль";
Button2->Visible = true;
Edit2->Visible = false;
Edit3->Visible = false;
Button3->Visible = false;
}
//---------------------------------------------------------------------------

