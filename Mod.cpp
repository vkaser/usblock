//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Mod.h"
#include "Unit16.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
Form16->Edit1->Text =  Form16->Edit1->Text + "1";
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
Form16->Edit1->Text =  Form16->Edit1->Text + "2";
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
Form16->Edit1->Text =  Form16->Edit1->Text + "3";	
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender)
{
Form16->Edit1->Text =  Form16->Edit1->Text + "4";	
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button5Click(TObject *Sender)
{
Form16->Edit1->Text =  Form16->Edit1->Text + "5";	
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button6Click(TObject *Sender)
{
Form16->Edit1->Text =  Form16->Edit1->Text + "6";	
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button7Click(TObject *Sender)
{
Form16->Edit1->Text =  Form16->Edit1->Text + "7";	
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button8Click(TObject *Sender)
{
Form16->Edit1->Text =  Form16->Edit1->Text + "8";	
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button9Click(TObject *Sender)
{
Form16->Edit1->Text =  Form16->Edit1->Text + "9";	
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button10Click(TObject *Sender)
{
Form16->Edit1->Text =  Form16->Edit1->Text + "0";	
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button11Click(TObject *Sender)
{
Form16->Edit1->Clear();
}
//---------------------------------------------------------------------------

