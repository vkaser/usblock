//---------------------------------------------------------------------------

#ifndef Unit19H
#define Unit19H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TForm19 : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TEdit *Edit1;
	TMemo *Memo1;
	TButton *Button1;
	TButton *Button2;
	TEdit *Edit2;
	TEdit *Edit3;
	TButton *Button3;
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Edit1KeyPress(TObject *Sender, char &Key);
	void __fastcall Edit2KeyPress(TObject *Sender, char &Key);
	void __fastcall Edit3KeyPress(TObject *Sender, char &Key);
	void __fastcall Edit1Exit(TObject *Sender);
	void __fastcall Edit2Exit(TObject *Sender);
	void __fastcall Edit3Exit(TObject *Sender);
	void __fastcall Edit2Enter(TObject *Sender);
	void __fastcall Edit1Enter(TObject *Sender);
	void __fastcall Edit3Enter(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm19(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm19 *Form19;
//---------------------------------------------------------------------------
#endif
