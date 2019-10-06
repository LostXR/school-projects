	
/* c206.c **********************************************************}
{* T�ma: Dvousm�rn� v�zan� line�rn� seznam
**
**                   N�vrh a referen�n� implementace: Bohuslav K�ena, ��jen 2001
**                            P�epracovan� do jazyka C: Martin Tu�ek, ��jen 2004
**                                             �pravy: Bohuslav K�ena, ��jen 2013
**
** Implementujte abstraktn� datov� typ dvousm�rn� v�zan� line�rn� seznam.
** U�ite�n�m obsahem prvku seznamu je hodnota typu int.
** Seznam bude jako datov� abstrakce reprezentov�n prom�nnou
** typu tDLList (DL znamen� Double-Linked a slou�� pro odli�en�
** jmen konstant, typ� a funkc� od jmen u jednosm�rn� v�zan�ho line�rn�ho
** seznamu). Definici konstant a typ� naleznete v hlavi�kov�m souboru c206.h.
**
** Va��m �kolem je implementovat n�sleduj�c� operace, kter� spolu
** s v��e uvedenou datovou ��st� abstrakce tvo�� abstraktn� datov� typ
** obousm�rn� v�zan� line�rn� seznam:
**
**      DLInitList ...... inicializace seznamu p�ed prvn�m pou�it�m,
**      DLDisposeList ... zru�en� v�ech prvk� seznamu,
**      DLInsertFirst ... vlo�en� prvku na za��tek seznamu,
**      DLInsertLast .... vlo�en� prvku na konec seznamu, 
**      DLFirst ......... nastaven� aktivity na prvn� prvek,
**      DLLast .......... nastaven� aktivity na posledn� prvek, 
**      DLCopyFirst ..... vrac� hodnotu prvn�ho prvku,
**      DLCopyLast ...... vrac� hodnotu posledn�ho prvku, 
**      DLDeleteFirst ... zru�� prvn� prvek seznamu,
**      DLDeleteLast .... zru�� posledn� prvek seznamu, 
**      DLPostDelete .... ru�� prvek za aktivn�m prvkem,
**      DLPreDelete ..... ru�� prvek p�ed aktivn�m prvkem, 
**      DLPostInsert .... vlo�� nov� prvek za aktivn� prvek seznamu,
**      DLPreInsert ..... vlo�� nov� prvek p�ed aktivn� prvek seznamu,
**      DLCopy .......... vrac� hodnotu aktivn�ho prvku,
**      DLActualize ..... p�ep�e obsah aktivn�ho prvku novou hodnotou,
**      DLSucc .......... posune aktivitu na dal�� prvek seznamu,
**      DLPred .......... posune aktivitu na p�edchoz� prvek seznamu, 
**      DLActive ........ zji��uje aktivitu seznamu.
**
** P�i implementaci jednotliv�ch funkc� nevolejte ��dnou z funkc�
** implementovan�ch v r�mci tohoto p��kladu, nen�-li u funkce
** explicitn� uvedeno n�co jin�ho.
**
** Nemus�te o�et�ovat situaci, kdy m�sto leg�ln�ho ukazatele na seznam 
** p�ed� n�kdo jako parametr hodnotu NULL.
**
** Svou implementaci vhodn� komentujte!
**
** Terminologick� pozn�mka: Jazyk C nepou��v� pojem procedura.
** Proto zde pou��v�me pojem funkce i pro operace, kter� by byly
** v algoritmick�m jazyce Pascalovsk�ho typu implemenov�ny jako
** procedury (v jazyce C procedur�m odpov�daj� funkce vracej�c� typ void).
**/

#include "c206.h"

int solved;
int errflg;

void DLError() {
/*
** Vytiskne upozorn�n� na to, �e do�lo k chyb�.
** Tato funkce bude vol�na z n�kter�ch d�le implementovan�ch operac�.
**/	
    printf ("*ERROR* This program has performed an illegal operation.\n");
    errflg = TRUE;             /* glob�ln� prom�nn� -- p��znak o�et�en� chyby */
    return;
}

void DLInitList (tDLList *L)	{
/*
** Provede inicializaci seznamu L p�ed jeho prvn�m pou�it�m (tzn. ��dn�
** z n�sleduj�c�ch funkc� nebude vol�na nad neinicializovan�m seznamem).
** Tato inicializace se nikdy nebude prov�d�t nad ji� inicializovan�m
** seznamem, a proto tuto mo�nost neo�et�ujte. V�dy p�edpokl�dejte,
** �e neinicializovan� prom�nn� maj� nedefinovanou hodnotu.
**/
   L->First = NULL;	//Inicializacia zoznamu.Jedna sa o prazdny zoznam,takze vsetky ukazatele budu NULL
   L->Act = NULL;
   L->Last = NULL; 
}

void DLDisposeList (tDLList *L)	{
/*
** Zru�� v�echny prvky seznamu L a uvede seznam do stavu, v jak�m
** se nach�zel po inicializaci. Ru�en� prvky seznamu budou korektn�
** uvoln�ny vol�n�m operace free. 
**/
	tDLElemPtr PomUk = NULL;  //Vytvorenie pomocneho ukazatela, na zaciatku bude NULL
	while (L->First != NULL) //Rus postupne prvky , az pokial nebude prvy NULL
		{
			PomUk = L->First; //Zaciatok si ulozime do pomocneho ukazatela
			L->First = L->First->rptr; //nasledujuci prvok (od prveho) sa premiestni do prveho
						
			free(PomUk); //zrusi sa v podstate prvy prvok..a takto v cykle postupne
		}
	L->Last = NULL;
	L->Act = NULL;	
	
 
}

void DLInsertFirst (tDLList *L, int val)	{
/*
** Vlo�� nov� prvek na za��tek seznamu L.
** V p��pad�, �e nen� dostatek pam�ti pro nov� prvek p�i operaci malloc,
** vol� funkci DLError().
**/
	tDLElemPtr PomUk = NULL;  //Vytvorenie pomocneho ukazatela, na zaciatku bude NULL
	PomUk = (tDLElemPtr)malloc(sizeof(struct tDLElem));	

	if(PomUk == NULL) //Ak sa alokacia nepodari, zavolaj danu funkciu
	{
		DLError();
		return;
	}

	PomUk->data = val; //parameter val bude priradeny do data
	PomUk->lptr = NULL; //Predchadzajuci prvok neexistuje, pretoze tato funkcia vklada prvy prvok
	PomUk->rptr = L->First; //Nasledujuci prvok je vlastne prvym alebo NULL

	if(L->First != NULL) //Ak prvy prvok nieje NULL - to znamena ze sa nejedna o prazdny zoznam
		L->First->lptr = PomUk;
	else				//Ak sa jedna o prazdny zoznam , tak prvy a posledny prvok su rovnake
		L->Last = PomUk; 

		L->First = PomUk; //Prvemu prvku priradim hodnotu ktora ma byt na prvom mieste v zozname
	
}

void DLInsertLast(tDLList *L, int val)	{
/*
** Vlo�� nov� prvek na konec seznamu L (symetrick� operace k DLInsertFirst).
** V p��pad�, �e nen� dostatek pam�ti pro nov� prvek p�i operaci malloc,
** vol� funkci DLError().
**/ 	
	tDLElemPtr PomUk = NULL;  //Vytvorenie pomocneho ukazatela, na zaciatku bude NULL
	PomUk = (tDLElemPtr)malloc(sizeof(struct tDLElem));	

	if(PomUk == NULL) //Ak sa alokacia nepodari, zavolaj danu funkciu
	{
		DLError();
		return;
	}

	PomUk->data = val; //parameter val bude priradeny do data
	PomUk->lptr = L->Last; //Predchadzajuci prvok 
	PomUk->rptr = NULL; //Nasledujuci prvok neexistuje, lebo vkladame posledny prvok.

	if((L->First != NULL) && (L->Last != NULL)) //Ak prvy a posledny prvok nieje NULL - to znamena ze sa nejedna o prazdny zoznam
		L->Last->rptr = PomUk;
	else
		L->First = PomUk; //ak sa jedna o prazdny zoznam, posledny bude prvy

		L->Last = PomUk; //poslednemu prvku priradim hodnotu ktora ma byt na poslednom mieste v zozname
}



void DLFirst (tDLList *L)	{
/*
** Nastav� aktivitu na prvn� prvek seznamu L.
** Funkci implementujte jako jedin� p��kaz (nepo��t�me-li return),
** ani� byste testovali, zda je seznam L pr�zdn�.
**/
	
	L->Act = L->First;
}

void DLLast (tDLList *L)	{
/*
** Nastav� aktivitu na posledn� prvek seznamu L.
** Funkci implementujte jako jedin� p��kaz (nepo��t�me-li return),
** ani� byste testovali, zda je seznam L pr�zdn�.
**/
	
	L->Act = L->Last;
}

void DLCopyFirst (tDLList *L, int *val)	{
/*
** Prost�ednictv�m parametru val vr�t� hodnotu prvn�ho prvku seznamu L.
** Pokud je seznam L pr�zdn�, vol� funkci DLError().
**/

	if(L->First == NULL) 	
	{
		DLError();
		return;
	}

	*val = L->First->data; //Do parametru val prirad hodnotu ktora sa nachadza v prvom prvku 
 
}

void DLCopyLast (tDLList *L, int *val)	{
/*
** Prost�ednictv�m parametru val vr�t� hodnotu posledn�ho prvku seznamu L.
** Pokud je seznam L pr�zdn�, vol� funkci DLError().
**/

	if(L->First == NULL)	
	{	
		DLError();
		return;
	}
	*val = L->Last->data; //Symetricka funkcia s predchadzajucou, ibaze kopiruje poslednu prvok

}

void DLDeleteFirst (tDLList *L)	{
/*
** Zru�� prvn� prvek seznamu L. Pokud byl prvn� prvek aktivn�, aktivita 
** se ztr�c�. Pokud byl seznam L pr�zdn�, nic se ned�je.
**/
	tDLElemPtr PomUk = NULL;  //Vytvorenie pomocneho ukazatela, na zaciatku bude NULL
	
	if(L->First == NULL)	
	{	
		free(PomUk);
		return;
	}

	if(L->Act == L->First)	  //Ak je prvy aktivnym, nastav ukazatel aktivneho na NULL...teda zrus aktivitu
		L->Act = NULL;

	if(L->First == L->Last) //Ak je prvy zaroven poslednym, vynuluj posledny
		L->Last = NULL; 

	PomUk = L->First->rptr; //Ulozim si hodnotu dalsieho prvku do pomocneho ukazatela, vzapati sa z neho stane prvy prvok
	free(L->First);	//Prvy zrusime

	L->First = PomUk; //Ulozili sme si hodnotu Dalsieho prvku do pomocneho ukazatela , teraz sa z neho stane prvy prvok v zozname
	if(L->First != NULL)
		L->First->lptr = NULL; //Lavy vynulujeme, aby bol prvy naozaj prvym a nic nalavo 
}	

void DLDeleteLast (tDLList *L)	{
/*
** Zru�� posledn� prvek seznamu L. Pokud byl posledn� prvek aktivn�,
** aktivita seznamu se ztr�c�. Pokud byl seznam L pr�zdn�, nic se ned�je.
**/ 
	tDLElemPtr PomUk = NULL;  //Vytvorenie pomocneho ukazatela, na zaciatku bude NULL
	

	if (L->First == NULL)
	{
		free(PomUk);
		return;
	}

	PomUk=L->Last;
	
	if(L->Last == L->Act)	  //Ak je posledny aktivnym, nastav ukazatel aktivneho na NULL...teda zrus aktivitu
		L->Act = NULL;

	if(L->First == L->Last)
	{
		L->First = NULL; 
		L->Last = NULL;
	}
	else
	{
	L->Last = L->Last->lptr; //Ulozim si hodnotu predosleho prvku do pomocneho ukazatela, vzapati sa z neho stane prvy prvok
	
	L->Last->rptr = NULL;
	}
	free(PomUk);
}

void DLPostDelete (tDLList *L)	{
/*
** Zru�� prvek seznamu L za aktivn�m prvkem.
** Pokud je seznam L neaktivn� nebo pokud je aktivn� prvek
** posledn�m prvkem seznamu, nic se ned�je.
**/
	tDLElemPtr PomUk = NULL;

	if((L->Act == NULL) || (L->Act == L->Last))	//Presne podla zadania (neaktivita ....) -> zrus ukazatel, a nic nerob 
 		{
 			free(PomUk);
 			return ;
 		}

 	PomUk = L->Act->rptr; //ukazatel na prvok ktory sa nachadza napravo od aktivneho
 	
 	if(PomUk->rptr != NULL) //Moze byt nasledujuci nulovy alebo nie ....a na zaver zrus pomocny ukazatel
 		{
 			L->Act->rptr = PomUk->rptr;
 			PomUk->rptr->lptr = L->Act;
 		}
 	else
 		{
 			L->Act->rptr=NULL;
 			L->Last = L->Act;
 		}
 			free(PomUk);
}

void DLPreDelete (tDLList *L)	{
/*
** Zru�� prvek p�ed aktivn�m prvkem seznamu L .
** Pokud je seznam L neaktivn� nebo pokud je aktivn� prvek
** prvn�m prvkem seznamu, nic se ned�je.
**/
	
	tDLElemPtr PomUk = NULL;
	
	if((L->Act == NULL) || (L->Act == L->First))	//Presne podla zadania (neaktivita ....) -> zrus ukazatel, a nic nerob	
 		{
 			free(PomUk);
 			return ;
 		}

 	PomUk = L->Act->lptr;  //ukazatel na prvok ktory sa nachadza nalavo od aktivneho

 	if(PomUk->lptr != NULL) //Moze byt predosly nulovy alebo nie ....a na zaver zrus pomocny ukazatel
 		{
 			L->Act->lptr = PomUk->lptr;
 			PomUk->lptr->rptr = L->Act;
 		}
 	else
 		{
 			L->Act->lptr=NULL;
 			L->First = L->Act;
 		}
 			free(PomUk);
}

void DLPostInsert (tDLList *L, int val) {
/*
** Vlo�� prvek za aktivn� prvek seznamu L.
** Pokud nebyl seznam L aktivn�, nic se ned�je.
** V p��pad�, �e nen� dostatek pam�ti pro nov� prvek p�i operaci malloc,
** vol� funkci DLError().
**/
	
	tDLElemPtr PomUk = NULL;  //Vytvorenie pomocneho ukazatela, na zaciatku bude NULL
	PomUk = (tDLElemPtr)malloc(sizeof(struct tDLElem));	

	if(PomUk == NULL) //Ak sa alokacia nepodari, zavolaj danu funkciu
	{	
		DLError();
	}

	if(L->Act == NULL) //Ak je neaktivny nic sa nedeje
		return;

	if(L->Act->rptr == NULL) //Ak je napravo od aktivneho nulovy, tak sa z pomocneho ukazatela do posledneho vlozi prvok
		L->Last =PomUk;
	else
		L->Act->rptr->lptr = PomUk; 

	PomUk->rptr = L->Act->rptr;	//ukazatele na dalsi a predchadzajuci
	PomUk->lptr = L->Act;
	L->Act->rptr = PomUk;

	PomUk->data = val; //VLozime prvok do miesta kam ukazuje pomocny ukazatel
	
}

void DLPreInsert (tDLList *L, int val)		{
/*
** Vlo�� prvek p�ed aktivn� prvek seznamu L.
** Pokud nebyl seznam L aktivn�, nic se ned�je.
** V p��pad�, �e nen� dostatek pam�ti pro nov� prvek p�i operaci malloc,
** vol� funkci DLError().
**/
	
	tDLElemPtr PomUk = NULL;  //Vytvorenie pomocneho ukazatela, na zaciatku bude NULL
	PomUk = (tDLElemPtr)malloc(sizeof(struct tDLElem));	

	if(PomUk == NULL) //Ak sa alokacia nepodari, zavolaj danu funkciu
	{
		DLError();
		return;
	}

	if(L->Act == NULL)	//Ak je neaktivny nic sa nedeje
		return;

	if(L->Act->lptr == NULL)	//Ak je naplavo od aktivneho nulovy, tak sa z pomocneho ukazatela do prveho vlozi prvok
		L->First = PomUk;

	else
		L->Act->lptr->rptr = PomUk;

	PomUk->lptr = L->Act->lptr; //ukazatele na predchadzajuci a dalsi
	PomUk->rptr = L->Act;
	L->Act->lptr = PomUk;

	PomUk->data = val;  //Vlozime prvok do miesta kam ukazuje pomocny ukazatel
}

void DLCopy (tDLList *L, int *val)	{
/*
** Prost�ednictv�m parametru val vr�t� hodnotu aktivn�ho prvku seznamu L.
** Pokud seznam L nen� aktivn�, vol� funkci DLError ().
**/
		
	if (L->Act == NULL) //Ak je zoznam neaktivny nic nerob resp. zavolaj iba funkciu ktora to oznami
	{
		DLError();
		return;
	}
	*val = L->Act->data;	//inak prirad do parametru val hodnotu z aktivneho prvku
	
 
}

void DLActualize (tDLList *L, int val) {
/*
** P�ep�e obsah aktivn�ho prvku seznamu L.
** Pokud seznam L nen� aktivn�, ned�l� nic.
**/
	
	if(L->Act == NULL) //Nic nerob ak je zoznam aktivny...inak prirad do aktivneho hodnotu z parametru val
		return;
	L->Act->data = val;
 
}

void DLSucc (tDLList *L)	{
/*
** Posune aktivitu na n�sleduj�c� prvek seznamu L.
** Nen�-li seznam aktivn�, ned�l� nic.
** V�imn�te si, �e p�i aktivit� na posledn�m prvku se seznam stane neaktivn�m.
**/
	if (L->Act == NULL) 	//Nic nerob ak nieje zoznam aktivny
		return;

	if (L->Act == L->Last) //zrus aktivitu ak je posledny aktivny
	{
      L->Act = NULL;
      return;
  	}
  	L->Act = L->Act->rptr;
 }



void DLPred (tDLList *L)	{
/*
** Posune aktivitu na p�edchoz� prvek seznamu L.
** Nen�-li seznam aktivn�, ned�l� nic.
** V�imn�te si, �e p�i aktivit� na prvn�m prvku se seznam stane neaktivn�m.
**/
	if(L->Act == NULL) //Nic nerob ak nieje zoznam aktivny
		return;

	if (L->Act == L->First) //zrus aktivitu ak je prvy aktivny
	{
      L->Act = NULL;
      return;
  	}
	L->Act = L->Act->lptr;

}

int DLActive (tDLList *L) {		
/*
** Je-li seznam aktivn�, vrac� true. V opa�n�m p��pad� vrac� false.
** Funkci implementujte jako jedin� p��kaz.
**/
	
	return (L->Act != NULL) ? 1 : 0;	// 1 predstavuje TRUE, 0 predstavuje FALSE
 
}

/* Konec c206.c*/
