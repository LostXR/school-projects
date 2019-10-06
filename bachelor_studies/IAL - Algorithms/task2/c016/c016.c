
/* c016.c: **********************************************************}
{* T�ma:  Tabulka s Rozpt�len�mi Polo�kami
**                      Prvn� implementace: Petr P�ikryl, prosinec 1994
**                      Do jazyka C prepsal a upravil: Vaclav Topinka, 2005
**                      �pravy: Karel Masa��k, ��jen 2013
**
** Vytvo�ete abstraktn� datov� typ
** TRP (Tabulka s Rozpt�len�mi Polo�kami = Hash table)
** s explicitn� �et�zen�mi synonymy. Tabulka je implementov�na polem
** line�rn�ch seznam� synonym.
**
** Implementujte n�sleduj�c� procedury a funkce.
**
**  HTInit ....... inicializuje tabulku p�ed prvn�m pou�it�m
**  HTInsert ..... vlo�en� prvku
**  HTSearch ..... zji�t�n� p��tomnosti prvku v tabulce
**  HTDelete ..... zru�en� prvku
**  HTRead ....... p�e�ten� hodnoty prvku
**  HTClearAll ... zru�en� obsahu cel� tabulky (inicializace tabulky
**                 pot�, co ji� byla pou�ita)
**
** Definici typ� naleznete v souboru c016.h.
**
** Tabulka je reprezentov�na datovou strukturou typu tHTable,
** kter� se skl�d� z ukazatel� na polo�ky, je� obsahuj� slo�ky
** kl��e 'key', obsahu 'data' (pro jednoduchost typu float), a
** ukazatele na dal�� synonymum 'ptrnext'. P�i implementaci funkc�
** uva�ujte maxim�ln� rozm�r pole HTSIZE.
**
** U v�ech procedur vyu��vejte rozptylovou funkci hashCode.  Pov�imn�te si
** zp�sobu p�ed�v�n� parametr� a zamyslete se nad t�m, zda je mo�n� parametry
** p�ed�vat jin�m zp�sobem (hodnotou/odkazem) a v p��pad�, �e jsou ob�
** mo�nosti funk�n� p��pustn�, jak� jsou v�hody �i nev�hody toho �i onoho
** zp�sobu.
**
** V p��kladech jsou pou�ity polo�ky, kde kl��em je �et�zec, ke kter�mu
** je p�id�n obsah - re�ln� ��slo.
*/

#include "c016.h"

int HTSIZE = MAX_HTSIZE;
int solved;

/*          -------
** Rozptylovac� funkce - jej�m �kolem je zpracovat zadan� kl�� a p�id�lit
** mu index v rozmez� 0..HTSize-1.  V ide�ln�m p��pad� by m�lo doj�t
** k rovnom�rn�mu rozpt�len� t�chto kl��� po cel� tabulce.  V r�mci
** pokus� se m��ete zamyslet nad kvalitou t�to funkce.  (Funkce nebyla
** volena s ohledem na maxim�ln� kvalitu v�sledku). }
*/

int hashCode ( tKey key ) {
	int retval = 1;
	int keylen = strlen(key);
	for ( int i=0; i<keylen; i++ )
		retval += key[i];
	return ( retval % HTSIZE );
}

/*
** Inicializace tabulky s explicitn� z�et�zen�mi synonymy.  Tato procedura
** se vol� pouze p�ed prvn�m pou�it�m tabulky.
*/

void htInit ( tHTable* ptrht ) {

	if(ptrht != NULL)						//Osetrenie , ci ptrht nieje nulovy , ak je, nic sa nevykona, takto budem zacinat kazdu funkciu.
		for(int i=0 ; i <= HTSIZE-1 ; i++) 	//cyklus kt. bude nulovat vsetky prvky hash. tabulky, teda vytvorime prazdnu tabulku o velkosti 0-HTSIZE-1 , teda HTSIZE
			(*ptrht)[i] = NULL; 
}

/* TRP s explicitn� z�et�zen�mi synonymy.
** Vyhled�n� prvku v TRP ptrht podle zadan�ho kl��e key.  Pokud je
** dan� prvek nalezen, vrac� se ukazatel na dan� prvek. Pokud prvek nalezen nen�, 
** vrac� se hodnota NULL.
**
*/

tHTItem* htSearch ( tHTable* ptrht, tKey key ) {

	if(ptrht != NULL)
	{
		int i = 0;
 		i = hashCode(key);				//Najdeme prislusny index kluca, ulozime ho do pomocnej premennej 
	
		tHTItem* PomUk = NULL;			//Vytvorime si pomocny ukazatel, na zac. ho inicializujeme na NULL
		PomUk = (*ptrht)[i];			
		if(PomUk == NULL)
			return NULL;

		else
		{		
			while((PomUk != NULL) && (PomUk->key != key)) //Ak nieje pomocny ukazatel hodny NULL, a kluce sa nezhoduju, pozri dalsi, a dalsi, a ked sa budu zhodovat tak ho returni
				PomUk = PomUk->ptrnext;

			return PomUk;
		}
	}

	else
		return NULL;
}

/* 
** TRP s explicitn� z�et�zen�mi synonymy.
** Tato procedura vkl�d� do tabulky ptrht polo�ku s kl��em key a s daty
** data.  Proto�e jde o vyhled�vac� tabulku, nem��e b�t prvek se stejn�m
** kl��em ulo�en v tabulce v�ce ne� jedenkr�t.  Pokud se vkl�d� prvek,
** jeho� kl�� se ji� v tabulce nach�z�, aktualizujte jeho datovou ��st.
**
** Vyu�ijte d��ve vytvo�enou funkci htSearch.  P�i vkl�d�n� nov�ho
** prvku do seznamu synonym pou�ijte co nejefektivn�j�� zp�sob,
** tedy prove�te.vlo�en� prvku na za��tek seznamu.
**/

void htInsert ( tHTable* ptrht, tKey key, tData data ) {
	if(ptrht != NULL)
	{
		tHTItem* PomUk = NULL; 					//Vytvorime si dva pomocne ukazatele, na zac. ich inicializujeme na NULL
		tHTItem* novy = NULL;
	
		PomUk = htSearch(ptrht, key); 			//pomocny ukazatel 'PomUk' je kvoli zapamataniu si indexu , ak nieje nulovy, znamena to ze tam nieco bolo, a iba sa prepise datova cast
		if (PomUk == NULL)
		{
		 	novy = malloc(sizeof(tHTable));		//pomocny ukazatel 'novy' - donho sa pamata alokovanie miesta v pamati , o velkosti Hash. tabulky
		 	if(novy != NULL)					//ak sa alokacia nepodari vrati null
			{
		 		novy->key=key;					//kluc, data sa vlozia do pomocneho ukazatela
		 		novy->data=data;
		 		novy->ptrnext = (*ptrht)[hashCode(key)]; //naplnime ukazatel na dalsi prvok, a pridame do tabulky
		 		(*ptrht)[hashCode(key)] = novy;

		 	}
		}
		else 
			PomUk->data = data;   				//prepisanie datova cast, vid IF
	}
}

/*
** TRP s explicitn� z�et�zen�mi synonymy.
** Tato funkce zji��uje hodnotu datov� ��sti polo�ky zadan� kl��em.
** Pokud je polo�ka nalezena, vrac� funkce ukazatel na polo�ku
** Pokud polo�ka nalezena nebyla, vrac� se funk�n� hodnota NULL
**
** Vyu�ijte d��ve vytvo�enou funkci HTSearch.
*/

tData* htRead ( tHTable* ptrht, tKey key ) {

	tHTItem* PomUk = NULL;
	if(ptrht != NULL)
	{
		PomUk = htSearch(ptrht, key);		//Najdeme poziciu pomocou hrSearch , ulozime do pomocneho retazca, ak nieje NULL tak funkcia vrati obsah z klucu (data), inak vzdy NULL
		
		if(PomUk != NULL)
			return &PomUk->data;
		else
			return NULL;
	}

	else 
		return NULL;

}

/*
** TRP s explicitn� z�et�zen�mi synonymy.
** Tato procedura vyjme polo�ku s kl��em key z tabulky
** ptrht.  Uvoln�nou polo�ku korektn� zru�te.  Pokud polo�ka s uveden�m
** kl��em neexistuje, d�lejte, jako kdyby se nic nestalo (tj. ned�lejte
** nic).
**
** V tomto p��pad� NEVYU��VEJTE d��ve vytvo�enou funkci HTSearch.
*/

void htDelete ( tHTable* ptrht, tKey key ) {
	if(ptrht == NULL)
		return;

	tHTItem* PomUk1 = NULL;				//vytvorime 2 ukazatele, na zac. budu mat rovnake hodnoty = NULL
	tHTItem* PomUk2 = NULL;
	unsigned int i = 0;
	i = hashCode(key);					//Najdeme a ulozime index na kt. sa bude ukladat
	PomUk1 = (*ptrht)[i];				//Obe ukazatele su zatial stejne
	PomUk2 = (*ptrht)[i];

	if(PomUk2 == NULL)					//usetrenie ci nieje jeden z nich nulovy - jeden staci preto lebo su rovnake
		return;

	if(PomUk2->key == key)				//ak je zhoda klucov, uloz do PomUk2, dalsi prvok bude v predchadzjucom, a odalokuj PomUk2
	{
		PomUk2=(*ptrht)[i];
		(*ptrht)[i] = (*ptrht)[i]->ptrnext;
		free(PomUk2);
	}
	else
	{
		while(PomUk2 != NULL)			//zastav az ked bude pomocny ukazatel NULL teda bude uvolneny z pamati
		{
			if(PomUk2 != (*ptrht)[i])	
			{
				PomUk2->ptrnext = PomUk1->ptrnext; 	//prepiseme ukazatele a prvy uvolnime
				free(PomUk1);
			}
			else
			{
				(*ptrht)[i] = PomUk2->ptrnext;		//dalsi prvok priradime k sucasnemu a uvolnime pomocny ukazatel
				free(PomUk2);
				return;
			}

		}
	}

}

/* TRP s explicitn� z�et�zen�mi synonymy.
** Tato procedura zru�� v�echny polo�ky tabulky,          korektn� uvoln� prostor,
** kter� tyto polo�ky zab�raly, a uvede tabulku do po��te�n�ho stavu.
*/

void htClearAll ( tHTable* ptrht ) {
	if(ptrht == NULL) 
		return;

	tHTItem* PomUk = NULL; 						//Vytvorime si pomocny ukazatel typu hash.tabulky

	for(int i = 0; i <= HTSIZE -1 ; i++) {		//Budeme mazat postupne v cykle vsetky prvky tabulky
		while((*ptrht)[i] != NULL)				//Kazdy prvok musime nulovat a odalokovat, vyuzijeme na to pomocnu premennu
		{
			PomUk = (*ptrht)[i];				//Ulozime si obsah HT z daneho indexu do pomocnej premennej
			(*ptrht)[i] = (*ptrht)[i]->ptrnext;	//Nahradime dalsi sucasnym
			free(PomUk);						//Uvolnime pomocny retazec
		}
	}

}
