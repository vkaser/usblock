//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit15.h"
#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm15 *Form15;
AnsiString WhiteString;
bool Search(AnsiString string);
//---------------------------------------------------------------------------
__fastcall TForm15::TForm15(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm15::Button2Click(TObject *Sender)
{
Form15->Close();
}
//---------------------------------------------------------------------------



void __fastcall TForm15::Button1Click(TObject *Sender)
{
AnsiString s;
int i;
if (Form2->ListBox1->ItemIndex == -1)
	Form2->ListBox1->ItemIndex = 0;
s = Form2->ListBox1->Items->Strings[Form2->ListBox1->ItemIndex];
i = s.Pos(":");
s.Delete(1,i+1);
WhiteString = LabeledEdit1->Text + " " + ComboBox1->Text + " " + LabeledEdit2->Text;
Form2->ListBox2->Items->Add(WhiteString	+ "   (" + s + ")" );
Form15->Close();
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------


void __fastcall TForm15::FormClose(TObject *Sender, TCloseAction &Action)
{
ComboBox1->ClearSelection();
LabeledEdit1->Clear();
LabeledEdit2->Clear();	
}
//---------------------------------------------------------------------------

