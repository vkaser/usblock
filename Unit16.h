//---------------------------------------------------------------------------

#ifndef Unit16H
#define Unit16H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm16 : public TForm
{
__published:	// IDE-managed Components
	TButton *Button1;
	TLabel *Label1;
	TTimer *Timer1;
	TEdit *Edit1;
	TButton *Button4;
	TButton *Button5;
	TButton *Button3;
	TButton *Button6;
	TButton *Button7;
	TButton *Button8;
	TButton *Button9;
	TButton *Button10;
	TButton *Button12;
	TButton *Button13;
	TButton *Button11;
	TMemo *Memo1;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall Button5Click(TObject *Sender);
	void __fastcall Button6Click(TObject *Sender);
	void __fastcall Button7Click(TObject *Sender);
	void __fastcall Button8Click(TObject *Sender);
	void __fastcall Button9Click(TObject *Sender);
	void __fastcall Button10Click(TObject *Sender);
	void __fastcall Button11Click(TObject *Sender);
	void __fastcall Button13Click(TObject *Sender);
	void __fastcall Button12Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm16(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm16 *Form16;
//---------------------------------------------------------------------------
#endif
