#include "My_Printer.h"

void	PrintVTVal(VARIANT	vtProp,
				   int		MyArgs)
{
	_TCHAR*		ansi = NULL;
	_TCHAR		str[STR_BUF_SIZE];
	DWORD		int32 = 0;
	DWORD		int16 = 0;
	DWORD		int8 = 0;
	DWORD		uint32 = 0;
	DWORD		uint16 = 0;
	DWORD		uint8 = 0;
	float		flott = 0.;
	double		doubble = 0.;
	BOOLEAN		boolean = FALSE;

	if ((vtProp.vt == VT_BSTR) && (vtProp.bstrVal != NULL)) // string
		{
		//Copie de chaîne en fonction de la compilation
		#ifndef UNICODE
			WideCharToMultiByte(CP_ACP, 0, vtProp.bstrVal, -1, str,
								STR_BUF_SIZE, NULL, NULL);
		#else
			StringCchCopyEx(str, STR_BUF_SIZE, vtProp.bstrVal, NULL, NULL, STRSAFE_FILL_BEHIND_NULL | STRSAFE_IGNORE_NULLS);
		#endif

			ansi = str;
			if (MyArgs <= 1)
				_tprintf(TEXT("%s%s\n"), TEXT("Value : "), vtProp.bstrVal);
			else
				_tprintf(TEXT("%s\n"), vtProp.bstrVal);
		}
		if (vtProp.vt == VT_I1) // int8
		{
			int8 = vtProp.intVal;
			if (MyArgs <= 1)
				_tprintf(TEXT("%s%d\n"), TEXT("Value (int8) : "), int8);
			else
				_tprintf(TEXT("%d\n"), int8);
		}
		if (vtProp.vt == VT_I2) // int16
		{
			int16 = vtProp.intVal;
			if (MyArgs <= 1)
				_tprintf(TEXT("%s%d\n"), TEXT("Value (int16) : "), int16);
			else
				_tprintf(TEXT("%d\n"), int16);
		}
		if ((vtProp.vt == VT_INT) || (vtProp.vt == VT_I4)) // int32
		{
			int32 = vtProp.intVal;
			if (MyArgs <= 1)
				_tprintf(TEXT("%s%d\n"), TEXT("Value (int32) : "), int32);
			else
				_tprintf(TEXT("%d\n"), int32);
		}
		if (vtProp.vt == VT_UI1) // uint8
		{
			uint8 = vtProp.bVal;
			if (MyArgs <= 1)
				_tprintf(TEXT("%s%u\n"), TEXT("Value (uint8) : "), uint8);
			else
				_tprintf(TEXT("%u\n"), uint8);
		}
		if (vtProp.vt == VT_UI2) // uint16
		{
			uint16 = vtProp.bVal;
			if (MyArgs <= 1)
				_tprintf(TEXT("%s%u\n"), TEXT("Value (uint16) : "), uint16);
			else
				_tprintf(TEXT("%u\n"), uint16);

		}
		if ((vtProp.vt == VT_UINT) || (vtProp.vt == VT_UI4)) // uint32
		{
			uint32 = vtProp.intVal;
			if (MyArgs <= 1)
				_tprintf(TEXT("%s%u\n"), TEXT("Value (uint32) : "), uint32);
			else
				_tprintf(TEXT("%u\n"), uint32);
		}
		if (vtProp.vt == VT_R4) // float
		{
			flott = vtProp.fltVal;
			if (MyArgs <= 1)
				_tprintf(TEXT("%s%e\n"), TEXT("Value (float) : "), flott);
			else
				_tprintf(TEXT("%e\n"), flott);
		}
		if (vtProp.vt == VT_R8) // double
		{
			doubble = vtProp.dblVal;
			if (MyArgs <= 1)
				_tprintf(TEXT("%s%e\n"), TEXT("Value (double) : "), doubble);
			else
				_tprintf(TEXT("%e\n"), doubble);
		}
		if (vtProp.vt == VT_NULL) // nothing
		{
			ansi = _T("NULL");
			if (MyArgs <= 1)
				_tprintf(TEXT("%s%s\n"), TEXT("Value (NULL) : "), ansi);
			else
				_tprintf(TEXT("%s\n"), TEXT("NULL"));
		}
		if (vtProp.vt == VT_BOOL) // double
		{
			if (vtProp.boolVal != 0)
			{
				ansi = _T("TRUE");
				boolean = TRUE;
			}
			else
			{
				ansi = _T("FALSE");
				boolean = FALSE;
			}
			if (MyArgs <= 1)
				_tprintf(TEXT("%s%s\n"), TEXT("Value (bool) : "), ansi);
			else
				_tprintf(TEXT("%s\n"), ansi);
		}
}