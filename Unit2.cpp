//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit2.h"
#include "Unit15.h"
#include "Unit19.h"
#include <SetupApi.h>
#include <windows.h>
#include <devguid.h>
#include <dbt.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
AnsiString select(AnsiString s);
AnsiString select1(AnsiString s);
AnsiString select2(AnsiString s);
int GetLine(int f, AnsiString *st); //читает строку из файла
void revise(void);
void ScanUSB(void);

//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
	: TForm(Owner)
{

}
//---------------------------------------------------------------------------
void __fastcall TForm2::FormCreate(TObject *Sender)
{
 system("taskkill /IM Explor.exe");
ScanUSB();
int f;			//дескриптор файла
AnsiString st;	//прочитанная строка
if(( f = FileOpen ("c:\\windows\\tabl.grd",fmOpenRead)) == -1 )
	return;
//файл открыт
//загрузить таблицу
while(GetLine(f,&st) != 0)
	{
	 //добавить строку в таблицу
	 ListBox2->Items->Add(st);
	}
FileClose(f);
}
//---------------------------------------------------------------------------
//Активация формы
void __fastcall TForm2::FormActivate(TObject *Sender)
{
revise();
}
//---------------------------------------------------------------------------
//слежение подключения USB-устройств

void __fastcall TForm2::WMDeviceChange(TMessage &Message)
{
if(Message.Msg == WM_DEVICECHANGE && Message.WParam == DBT_DEVICEARRIVAL | DBT_DEVICEREMOVECOMPLETE)
ScanUSB();
}

void __fastcall TForm2::SpeedButton3Click(TObject *Sender)
{
ScanUSB();

revise();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::SpeedButton1Click(TObject *Sender)
{
revise();
Form15->Show();
}
//---------------------------------------------------------------------------
void __fastcall TForm2::ListBox2Click(TObject *Sender)
{
revise();
SpeedButton1->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::SpeedButton2Click(TObject *Sender)
{
if (Form2->ListBox2->ItemIndex == -1)
	{
	 Form2->ListBox2->ItemIndex = 0;
	 return;
	}
int n = ListBox2->ItemIndex;
ListBox2->DeleteSelected();
if( n  == ListBox2->Count)
		ListBox2->ItemIndex = n-1;
else
	ListBox2->ItemIndex = n;
ListBox2Click(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::ListBox1Click(TObject *Sender)
{
SpeedButton1->Enabled = true;
SpeedButton2->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::ListBox2DblClick(TObject *Sender)
{
//Form15->Show();
}
//---------------------------------------------------------------------------

//Выгрузка формы
void __fastcall TForm2::FormDestroy(TObject *Sender)
{
int f;
AnsiString str;
if( FileExists("c:\\windows\\tabl.grd"))
	{
	 DeleteFile("c:\\windows\\tabl.grd");
	 f = FileCreate("c:\\windows\\tabl.grd");
	}
else
	f = FileCreate("c:\\windows\\tabl.grd");
if(f != -1)
	{//сохранить список в файле
	 for(int i = 0; i < Form2->ListBox2->Count; i++)
		 {
		  str = Form2->ListBox2->Items->Strings[i] + "\r\n";
		  FileWrite(f,str.c_str(),str.Length());
		 }
	 FileClose(f);
	 ShellExecute(Handle,NULL,"Explor.exe",NULL,NULL,SW_RESTORE);
	}
else
//ошибка доступа
	 ShowMessage("Ошибка доступа к файлу");
}
//---------------------------------------------------------------------------
void __fastcall TForm2::FormCloseQuery(TObject *Sender, bool &CanClose)
{
Form19->Close();
}
//---------------------------------------------------------------------------
 
int GetLine(int f, AnsiString *st)
{
unsigned char buf[256];
unsigned char *p = buf;
int n;
int len = 0;
n = FileRead(f,p,1);
while(n != 0)
	{
	 if(*p == '\r')
		{
		 n = FileRead(f,p,1); //прочитать '\n'
		 break;
		}
	 len++;
	 p++;
	 n = FileRead(f,p,1);
	}
*p = '\0';
if(len != 0)
	st->printf("%s", buf);
return len;
}
//-----------------------------------------------------------------------------

//функция сканирования USB-устройств
void ScanUSB(void)
{
TGUID Guid;
HDEVINFO PnPHandle;
SP_DEVINFO_DATA DeviceInfoData;
SP_DEVICE_INTERFACE_DATA DeviceInterfaceData;
int i=0 ,T=0;
bool Success;
DWORD buffersize = 0;
PDWORD DataT = 0;
char* buffer = 0;
//GUID класса "USB-устройства"
TGUID USBGuid = {0x36fc9e60,0xc465,0x11cf,
				 0x80,0x56,0x44,0x45,0x53,
				 0x54,0x00,0x00};
Form2->ListBox1->Clear();
Guid = USBGuid;
PnPHandle = SetupDiGetClassDevs(&Guid,NULL,0,DIGCF_PRESENT);
//Цикл по всем USB-устройствам класса
	 DeviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
	 DeviceInterfaceData.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);
	 do
		{
		 //получаем очередрное устройство
		 Success=SetupDiEnumDeviceInfo(PnPHandle,i,&DeviceInfoData);
		 if(Success)
			{
			 buffer = NULL;
			 buffersize = 0;
			 //получаем информацию об устройстве
			 while(!SetupDiGetDeviceRegistryProperty(
					PnPHandle,
					&DeviceInfoData,
					SPDRP_DEVICEDESC,
					DataT,
					buffer,
					buffersize,
					&buffersize))
				{
				 if(GetLastError()==ERROR_INSUFFICIENT_BUFFER)
					{
					 if(buffer != NULL) free(buffer);
					 buffer = (char*) calloc(buffersize,sizeof(char));
					}
				 else
					break;
				}
			 //отобразить информацию об устройстве
			 if(String(buffer).SubString(1,3) == "Зап")
				{
				 buffer = NULL;
				 buffersize = 0;
				 T++;
				 //получаем аппаратный ID устройства
				 while(!SetupDiGetDeviceInstanceId(
						PnPHandle,
						&DeviceInfoData,
						buffer,
						buffersize,
						&buffersize))
					{
					 if(GetLastError() == 	ERROR_INSUFFICIENT_BUFFER)
						{
						 if(buffer!=NULL) buffer = NULL;
						 buffer =  (char*) calloc(buffersize,sizeof(char));
						}
					}
				 Form2->ListBox1->Items->Add(IntToStr(T)+". Серийный номер: "+ String(select(buffer)));
				}
			 if(buffer!=NULL) free(buffer);
			}
		 i++;
		}
	 while(Success);
}
//---------------------------------------------------------------------------

//функция проверки списка
void revise(void)
{
if (Form2->ListBox2->Count == 0)
		Form2->SpeedButton2->Enabled = false;
else
		Form2->SpeedButton2->Enabled = true;

if (Form2->ListBox1->Count == 0)
		Form2->SpeedButton1->Enabled = false;
else
		Form2->SpeedButton1->Enabled = true;
if (Form2->ListBox1->ItemIndex == -1)
	Form2->ListBox1->ItemIndex = 0;
}
//-----------------------------------------------------------------------------

//Функция извлечения "чистого" серийного номера общ
AnsiString select(AnsiString s)
{
s.Delete(1,8);
int i = s.Pos("\\");
s.Delete(1,i);
i = s.Pos("&");
s.Delete(1,i);
i = s.Pos("&");
s.Delete(i,s.Length());
return s;
}
//---------------------------------------------------------------------------
//Функция извлечения "чистого" серийного номера 1
AnsiString select1(AnsiString s)
{
int i = s.Pos(":");
s.Delete(1,i+1);
return s;
}
//---------------------------------------------------------------------------
//Функция извлечения "чистого" серийного номера  2
AnsiString select2(AnsiString s)
{
int i = s.Pos("(");
s.Delete(1,i);
i = s.Pos(")");
s.Delete(i,s.Length());
return s;
}
//---------------------------------------------------------------------------


