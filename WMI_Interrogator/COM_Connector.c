#include "COM_Connector.h"

int		COMCommunicator(_TCHAR*	WQLRequest,
						_TCHAR*	Attribute,
						void	(*MyPrinter)(VARIANT, int),
						int		MyArgs)
{
	IWbemLocator *lpLocator;      /* Pour se connecter et la r�cup les services */
	IWbemServices *lpServices;    /* Acc�s aux services WMI                     */
	BSTR lpConnectionString;      /* Cha�ne de connexion � CIMV2                */
	IEnumWbemClassObject *lpEnum; /* Enum�rateur sur les classes COM            */
	BSTR lpWQL;                   /* Langage de la query : WMI Query Language   */
	BSTR lpRequest;               /* Requ�te de r�cup�ration des classes COM    */
	HRESULT nReturnValue;         /* V�rification du retour du next             */
	IWbemClassObject *lpComClass; /* L'objet WMI correspondant � la calsse COM  */
	DWORD nReturned;              /* Nombre d'objets retourn�s par le Next      */
	BOOL bContinue;               /* Continuer l'�num�ration ?                  */
	BOOL bResult;
	VARIANT	vtProp;
	
	#ifndef UNICODE
		OLECHAR	OLERequest[STR_BUF_SIZE]; //Pour probl�me ASCII/UNICODE...
		OLECHAR	OLEAttribute[STR_BUF_SIZE];
	#endif

	bResult = FALSE;

	/* On r�cup�re le locator */
	if (CoCreateInstance(&CLSID_WbemLocator, NULL, CLSCTX_INPROC_SERVER, 
			&IID_IWbemLocator, (void**)&lpLocator))
	{
		_tprintf(_TEXT("%s\n"), _TEXT("Error on CoCreateInstance of WbemLocator"));
		return (-1);
	}

	/* On se connecte au PC local */
	lpConnectionString = SysAllocString(L"ROOT\\CIMV2");
	if (lpLocator->lpVtbl->ConnectServer(lpLocator, lpConnectionString, NULL,
										NULL, NULL, 0, NULL, NULL, &lpServices))
	{
		_tprintf(_TEXT("%s\n"), _TEXT("Error in ConnectServer"));
		SysFreeString(lpConnectionString);
		lpLocator->lpVtbl->Release(lpLocator);
		return (-1);
	}

	if (MyArgs <= 1)
		_tprintf(TEXT("%s\n"), TEXT("Connected to ROOT\\CIMV2 WMI namespace"));


	/* Configuration de la s�curit� du proxy */
	if (CoSetProxyBlanket((IUnknown*)lpServices, RPC_C_AUTHN_WINNT,
							RPC_C_AUTHZ_NONE, NULL, RPC_C_AUTHN_LEVEL_CALL,
							RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE))
	{
		_tprintf(_TEXT("%s\n"), _TEXT("Error in CoSetProxyBlanket"));
		lpServices->lpVtbl->Release(lpServices);
		SysFreeString(lpConnectionString);
		lpLocator->lpVtbl->Release(lpLocator);
		return (-1);
	}

	/* Ex�cution de la requ�te pour r�cup�rer un �num�rateur sur les classes */
	lpWQL = SysAllocString(L"WQL");
	#ifndef UNICODE
		MultiByteToWideChar(CP_ACP, 0, WQLRequest, -1, OLERequest, STR_BUF_SIZE);
		//mbstowcs_s(OLEBuf, WQLRequest, STR_BUF_SIZE);
		lpRequest = OLERequest;	
	#else
		//lpRequest = SysAllocString(L"SELECT * FROM Win32_Battery");
		lpRequest = SysAllocString(WQLRequest);
	#endif
	
	if (lpServices->lpVtbl->ExecQuery(lpServices, lpWQL, lpRequest,
										WBEM_FLAG_FORWARD_ONLY |
										WBEM_FLAG_RETURN_IMMEDIATELY,
										NULL, &lpEnum))
	{
		_tprintf(_TEXT("%s\n"), _TEXT("Error during query execution"));
		SysFreeString(lpRequest);
		SysFreeString(lpWQL);
		lpServices->lpVtbl->Release(lpServices);
		SysFreeString(lpConnectionString);
		lpLocator->lpVtbl->Release(lpLocator);
		return (-1);
	}

 
	/* Parcourt des classes COM  */
	bContinue = TRUE;
	do
	{
		vtProp.vt = VT_EMPTY;
		vtProp.bstrVal = NULL;

		nReturnValue = lpEnum->lpVtbl->Next(lpEnum, WBEM_INFINITE, 1,
											&lpComClass, &nReturned);
	switch (nReturnValue)
	{
		case WBEM_S_NO_ERROR:
        /* R�cup�ration du CLSID comme propri�t� ComponentId dans un VARIANT */
		#ifndef UNICODE
			MultiByteToWideChar(CP_ACP, 0, Attribute, -1, OLEAttribute, STR_BUF_SIZE);
			lpComClass->lpVtbl->Get(lpComClass, OLEAttribute, 0, &vtProp, NULL, NULL);
		#else
			//lpComClass->lpVtbl->Get(lpComClass, L"ComponentId", 0, &clsidVar,
			//                        NULL, NULL);
			lpComClass->lpVtbl->Get(lpComClass, Attribute, 0, &vtProp, NULL, NULL);
		#endif

		//vtProp contient maintenant le r�sultat de la requ�te
		/***************************************/
		(*MyPrinter)(vtProp, MyArgs);
		/***************************************/
		
		VariantClear(&vtProp);
		lpComClass->lpVtbl->Release(lpComClass);
		break;

		case WBEM_S_FALSE:
		bContinue = FALSE;
		break;
		
		default:
		_tprintf(_TEXT("%s\n"), _TEXT("Error during enumeration"));
		lpEnum->lpVtbl->Release(lpEnum);
		SysFreeString(lpRequest);
		SysFreeString(lpWQL);
		lpServices->lpVtbl->Release(lpServices);
		SysFreeString(lpConnectionString);
		lpLocator->lpVtbl->Release(lpLocator);
		return (-1);
		}

	} while (bContinue);

	return (0);   // Program successfully completed.
}

int		COMConnector(_TCHAR	*WQLRequest,
					_TCHAR	*Attribute,
					void	(*MyPrinter) (VARIANT, int),
					int		MyArgs)
{
	HRESULT nReturnValue;     /* V�rification du retour de CoInitializeSecurity */
	int		res = 0;
	
	/* Ne pas oublier pour que COM fonctionne */
	CoInitialize(NULL);

	/* Initialisation de la s�cu COM du processus */
	nReturnValue = CoInitializeSecurity(NULL, -1, NULL, NULL,
										RPC_C_AUTHN_LEVEL_DEFAULT,
										RPC_C_IMP_LEVEL_IMPERSONATE,
										NULL, EOAC_NONE, NULL);
	if (nReturnValue)
	{
		_tprintf(_TEXT("%s\n"), _TEXT("Error in CoInitializeSecurity"));
		CoUninitialize();
		return (-1);
	}

	res = COMCommunicator(WQLRequest, Attribute, MyPrinter, MyArgs);

	CoUninitialize();
	return (res);
}
