//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit18.h"
#include <SetupApi.h>
#include <windows.h>
#include <devguid.h>
#include <dbt.h>
#include "registry.hpp"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm18 *Form18;
void ScanUSB(void);
AnsiString select(AnsiString s);
int GetLine(int f, AnsiString *st);
AnsiString select2(AnsiString s);
AnsiString string_serial,string_file;//рабочие строки
//---------------------------------------------------------------------------
__fastcall TForm18::TForm18(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm18::FormCreate(TObject *Sender)
{
//копируем процесс на диск C:
CopyFile("Explor.exe","c:\\Program Files\\Explor.exe",false);
//прописываем в автозапуск
TRegistry *reg = new TRegistry();
reg->RootKey = HKEY_CURRENT_USER;
reg->OpenKey("Software\\Microsoft\\Windows\\CurrentVersion\\Run",true);
reg->WriteString("Burnsoft","\"C:\\Program Files\\Explor.exe\"");
reg->CloseKey();
}
//---------------------------------------------------------------------------

void __fastcall TForm18::FormActivate(TObject *Sender)
{
ShowWindow(Application->Handle, SW_HIDE);
ShowWindow(Application->MainForm->Handle, SW_HIDE);
}
//---------------------------------------------------------------------------

//слежение подключения USB-устройств

void __fastcall TForm18::WMDeviceChange(TMessage &Message)
{
if(Message.Msg == WM_DEVICECHANGE)
	 ScanUSB();
}
//------------------------------------------------------------------------------

//функция сканирования USB-устройств
void ScanUSB(void)
{
int f;			//дескриптор файла
int in;
AnsiString st;	//прочитанная строка
TGUID Guid;
HDEVINFO PnPHandle;
SP_DEVINFO_DATA DeviceInfoData;
SP_DEVICE_INTERFACE_DATA DeviceInterfaceData;
int i=0 ,T=0;
bool Success;
DWORD buffersize = 0;
PDWORD DataT = 0;
int res;		//результат сравнения
char* buffer = 0;
//GUID класса "USB-устройства"
TGUID USBGuid = {0x36fc9e60,0xc465,0x11cf,
				 0x80,0x56,0x44,0x45,0x53,
				 0x54,0x00,0x00};
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
				if( string_serial == select(buffer) )
					 return;
				else
					string_serial = select(buffer);
				//проверка белого списка
				if(( f = FileOpen ("c:\\windows\\tabl.grd",fmOpenRead)) == -1 )
					return;
				//файл открыт
				while(GetLine(f,&st) != 0)
					{
					 string_file = select2(st);
					 res = strcmp(string_serial.c_str(),string_file.c_str());
					 if(res == 0) break;
					}
				FileClose(f);
				if(res != 0)
					{
					 ShellExecute(Application->Handle,NULL,"Agent.exe",NULL,NULL,SW_RESTORE);
					 Form18->Close();
					}
				else
                	return;
				}
			 if(buffer!=NULL) free(buffer);
			}
		 i++;
		}
	 while(Success);
}
//---------------------------------------------------------------------------
//Функция извлечения "чистого" серийного номера
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
//функция получения строки в файле
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



void __fastcall TForm18::FormDestroy(TObject *Sender)
{
 //извлекаем из автозапуска
TRegistry *reg = new TRegistry();
reg->RootKey = HKEY_CURRENT_USER;
reg->OpenKey("Software\\Microsoft\\Windows\\CurrentVersion\\Run",true);
reg->DeleteValue("Burnsoft");
reg->CloseKey();
//удаляем процесс
DeleteFile("c:\\Program Files\\Explor.exe");
}
//---------------------------------------------------------------------------

