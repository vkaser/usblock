//---------------------------------------------------------------------------

#ifndef Unit2H
#define Unit2H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <jpeg.hpp>
//---------------------------------------------------------------------------
class TForm2 : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TPanel *Panel2;
	TPanel *Panel3;
	TLabel *Label1;
	TSpeedButton *SpeedButton1;
	TSpeedButton *SpeedButton2;
	TListBox *ListBox1;
	TListBox *ListBox2;
	TImage *Image1;
	TSpeedButton *SpeedButton3;
	TLabel *Label3;
	void __fastcall SpeedButton3Click(TObject *Sender);
	void __fastcall SpeedButton1Click(TObject *Sender);
	void __fastcall ListBox2Click(TObject *Sender);
	void __fastcall SpeedButton2Click(TObject *Sender);
	void __fastcall ListBox1Click(TObject *Sender);
	void __fastcall ListBox2DblClick(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
	void virtual __fastcall WMDeviceChange(TMessage &Message);
public:		// User declarations
	__fastcall TForm2(TComponent* Owner);
	BEGIN_MESSAGE_MAP
		MESSAGE_HANDLER(WM_DEVICECHANGE,TMessage,WMDeviceChange);
	END_MESSAGE_MAP(TForm);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif
