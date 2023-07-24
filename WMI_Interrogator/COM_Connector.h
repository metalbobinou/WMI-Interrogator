#ifndef COM_CONNECTOR_H_
# define COM_CONNECTOR_H_

/* Pour CoInitializeSecurity et quelques autres */
# define _WIN32_DCOM

# include <windows.h>
# include <tchar.h>
# include <stdio.h>
# include <strsafe.h>
# include <objbase.h>
# include <wbemcli.h>

# pragma comment(lib, "wbemuuid.lib")

# include "CharMgmt.h"

int		COMConnector(_TCHAR*	WQLRequest,
					_TCHAR*		Attribute,
					void		(*MyPrinter)(VARIANT, int),
					int			MyArgs);

#endif /* !COM_CONNECTOR_H_ */