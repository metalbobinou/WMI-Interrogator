#include "WMI_Interrogator.h"

//Avec 1 argument ou + sur la ligne de commande, le programme sera lanc�
//en mode CLI... sinon la CLI attendra l'appui d'une touche
int		_tmain(int		argc,
			   _TCHAR*	argv[])
{
	_TCHAR*	WQLRequest = NULL;
	_TCHAR* Attribute = NULL;
	int		res = 0;

	//Win32 Classe du WMI � interroger
	WQLRequest = _tcsdup(_TEXT("SELECT * FROM Win32_Battery"));

	//Attribut � r�cup�rer
	Attribute = _tcsdup(_TEXT("BatteryStatus"));

	//Availability (uint16) => 2 : Unknown, 3 : Running or Full Power
	//BatteryStatus (uint16) => 1 : the battery is discharging, 2 : AC power, so no battery necessary
	//When connected to AC, Availability == 2, BatteryStatus == 2
	//When disconnected from AC, Availability == 3, BatteryStatus == 1

	/*
	** MyPrinter est un pointeur sur fonction pour personnaliser la gestion de la requ�te
	** MyArgs sert uniquement � savoir on a lanc� avec argument sur la ligne de commande ou non
	** (En g�n�ral, sans argument, c'est un double clique donc il faut attendre attendre � la fin)
	** La fonction utilis�e DOIT �tre de la forme :
	** void MaFonc(VARIANT VariantDeLaRequete, int NbArgs)
	*/
	//COMConnector(_TCHAR *WQLRequest, _TCHAR *Attribute, void *MyPrinter, int MyArgs);
	res = COMConnector(WQLRequest, Attribute, PrintVTVal, argc);

	//Permet d'attendre l'appui d'une touche avant de fermer le CMD
	if (argc <= 1)
		PressKey();

	return (res);
}

