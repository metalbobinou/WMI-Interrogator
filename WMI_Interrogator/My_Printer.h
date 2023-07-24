#ifndef MY_PRINTER_H_
# define MY_PRINTER_H_

# include <windows.h>
# include <tchar.h>
# include <stdio.h> 
# include <strsafe.h>

# include "CharMgmt.h"

/*
** Définition de la/les fonctions pour imprimer et formatter le résultat
** Utile si vous avez plusieurs requêtes à faire...
** Ne pas oublie qu'elles doivent toutes avoir le même format !
** void MaFonc(VARIANT, int);
*/
void	PrintVTVal(VARIANT	vtProp,
				   int		MyArgs);

#endif /* !MY_PRINTER_H_ */