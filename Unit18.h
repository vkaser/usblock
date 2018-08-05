//---------------------------------------------------------------------------

#ifndef Unit18H
#define Unit18H
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
class TForm18 : public TForm
{
__published:	// IDE-managed Components
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
private:	// User declarations
	void virtual __fastcall WMDeviceChange(TMessage &Message);
public:		// User declarations
	__fastcall TForm18(TComponent* Owner);
	BEGIN_MESSAGE_MAP
		MESSAGE_HANDLER(WM_DEVICECHANGE,TMessage,WMDeviceChange);
	END_MESSAGE_MAP(TForm);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm18 *Form18;
//---------------------------------------------------------------------------
#endif
