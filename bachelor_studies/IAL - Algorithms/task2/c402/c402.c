
/* c402.c: ********************************************************************}
{* T�ma: Nerekurzivn� implementace operac� nad BVS 
**                                     Implementace: Petr P�ikryl, prosinec 1994
**                                           �pravy: Petr P�ikryl, listopad 1997
**                                                     Petr P�ikryl, kv�ten 1998
**			  	                        P�evod do jazyka C: Martin Tu�ek, srpen 2005
**                                         �pravy: Bohuslav K�ena, listopad 2009
**                                         Upravy: Karel Masarik, rijen 2013
**
** S vyu�it�m dynamick�ho p�id�lov�n� pam�ti, implementujte NEREKURZIVN�
** n�sleduj�c� operace nad bin�rn�m vyhled�vac�m stromem (p�edpona BT znamen�
** Binary Tree a je u identifik�tor� uvedena kv�li mo�n� kolizi s ostatn�mi
** p��klady):
**
**     BTInit .......... inicializace stromu
**     BTInsert ........ nerekurzivn� vlo�en� nov�ho uzlu do stromu
**     BTPreorder ...... nerekurzivn� pr�chod typu pre-order
**     BTInorder ....... nerekurzivn� pr�chod typu in-order
**     BTPostorder ..... nerekurzivn� pr�chod typu post-order
**     BTDisposeTree ... zru� v�echny uzly stromu
**
** U v�ech funkc�, kter� vyu��vaj� n�kter� z pr�chod� stromem, implementujte
** pomocnou funkci pro nalezen� nejlev�j��ho uzlu v podstromu.
**
** P�esn� definice typ� naleznete v souboru c402.h. Uzel stromu je typu tBTNode,
** ukazatel na n�j je typu tBTNodePtr. Jeden uzel obsahuje polo�ku int Cont,
** kter� sou�asn� slou�� jako u�ite�n� obsah i jako vyhled�vac� kl�� 
** a ukazatele na lev� a prav� podstrom (LPtr a RPtr).
**
** P��klad slou�� zejm�na k procvi�en� nerekurzivn�ch z�pis� algoritm�
** nad stromy. Ne� za�nete tento p��klad �e�it, prostudujte si d�kladn�
** principy p�evodu rekurzivn�ch algoritm� na nerekurzivn�. Programov�n�
** je p�edev��m in�en�rsk� discipl�na, kde op�tn� objevov�n� Ameriky nem�
** m�sto. Pokud se V�m zd�, �e by n�co �lo zapsat optim�ln�ji, promyslete
** si v�echny detaily Va�eho �e�en�. Pov�imn�te si typick�ho um�st�n� akc�
** pro r�zn� typy pr�chod�. Zamyslete se nad modifikac� �e�en�ch algoritm�
** nap��klad pro v�po�et po�tu uzl� stromu, po�tu list� stromu, v��ky stromu
** nebo pro vytvo�en� zrcadlov�ho obrazu stromu (pouze pop�ehazov�n� ukazatel�
** bez vytv��en� nov�ch uzl� a ru�en� star�ch).
**
** P�i pr�chodech stromem pou�ijte ke zpracov�n� uzlu funkci BTWorkOut().
** Pro zjednodu�en� pr�ce m�te p�edem p�ipraveny z�sobn�ky pro hodnoty typu
** bool a tBTNodePtr. Pomocnou funkci BTWorkOut ani funkce pro pr�ci
** s pomocn�mi z�sobn�ky neupravujte 
** Pozor! Je t�eba spr�vn� rozli�ovat, kdy pou��t dereferen�n� oper�tor *
** (typicky p�i modifikaci) a kdy budeme pracovat pouze se samotn�m ukazatelem 
** (nap�. p�i vyhled�v�n�). V tomto p��kladu v�m napov� prototypy funkc�.
** Pokud pracujeme s ukazatelem na ukazatel, pou�ijeme dereferenci.
**/

#include "c402.h"
int solved;

void BTWorkOut (tBTNodePtr Ptr)		{
/*   ---------
** Pomocn� funkce, kterou budete volat p�i pr�chodech stromem pro zpracov�n�
** uzlu ur�en�ho ukazatelem Ptr. Tuto funkci neupravujte.
**/
			
	if (Ptr==NULL) 
    printf("Chyba: Funkce BTWorkOut byla vol�na s NULL argumentem!\n");
  else 
    printf("V�pis hodnoty dan�ho uzlu> %d\n",Ptr->Cont);
}
	
/* -------------------------------------------------------------------------- */
/*
** Funkce pro z�sobn�k hotnot typu tBTNodePtr. Tyto funkce neupravujte.
**/

void SInitP (tStackP *S)  
/*   ------
** Inicializace z�sobn�ku.
**/
{
	S->top = 0;  
}	

void SPushP (tStackP *S, tBTNodePtr ptr)
/*   ------
** Vlo�� hodnotu na vrchol z�sobn�ku.
**/
{ 
                 /* P�i implementaci v poli m��e doj�t k p�ete�en� z�sobn�ku. */
  if (S->top==MAXSTACK) 
    printf("Chyba: Do�lo k p�ete�en� z�sobn�ku s ukazateli!\n");
  else {  
		S->top++;  
		S->a[S->top]=ptr;
	}
}	

tBTNodePtr STopPopP (tStackP *S)
/*         --------
** Odstran� prvek z vrcholu z�sobn�ku a sou�asn� vr�t� jeho hodnotu.
**/
{
                            /* Operace nad pr�zdn�m z�sobn�kem zp�sob� chybu. */
	if (S->top==0)  {
		printf("Chyba: Do�lo k podte�en� z�sobn�ku s ukazateli!\n");
		return(NULL);	
	}	
	else {
		return (S->a[S->top--]);
	}	
}

bool SEmptyP (tStackP *S)
/*   -------
** Je-li z�sobn�k pr�zdn�, vr�t� hodnotu true.
**/
{
  return(S->top==0);
}	

/* -------------------------------------------------------------------------- */
/*
** Funkce pro z�sobn�k hotnot typu bool. Tyto funkce neupravujte.
*/

void SInitB (tStackB *S) {
/*   ------
** Inicializace z�sobn�ku.
**/

	S->top = 0;  
}	

void SPushB (tStackB *S,bool val) {
/*   ------
** Vlo�� hodnotu na vrchol z�sobn�ku.
**/
                 /* P�i implementaci v poli m��e doj�t k p�ete�en� z�sobn�ku. */
	if (S->top==MAXSTACK) 
		printf("Chyba: Do�lo k p�ete�en� z�sobn�ku pro boolean!\n");
	else {
		S->top++;  
		S->a[S->top]=val;
	}	
}

bool STopPopB (tStackB *S) {
/*   --------
** Odstran� prvek z vrcholu z�sobn�ku a sou�asn� vr�t� jeho hodnotu.
**/
                            /* Operace nad pr�zdn�m z�sobn�kem zp�sob� chybu. */
	if (S->top==0) {
		printf("Chyba: Do�lo k podte�en� z�sobn�ku pro boolean!\n");
		return(NULL);	
	}	
	else {  
		return(S->a[S->top--]); 
	}	
}

bool SEmptyB (tStackB *S) {
/*   -------
** Je-li z�sobn�k pr�zdn�, vr�t� hodnotu true.
**/
  return(S->top==0);
}

/* -------------------------------------------------------------------------- */
/*
** N�sleduje j�dro dom�c� �lohy - funkce, kter� m�te implementovat. 
*/

void BTInit (tBTNodePtr *RootPtr)	{
/*   ------
** Provede inicializaci bin�rn�ho vyhled�vac�ho stromu.
**
** Inicializaci sm� program�tor volat pouze p�ed prvn�m pou�it�m bin�rn�ho
** stromu, proto�e neuvol�uje uzly nepr�zdn�ho stromu (a ani to d�lat nem��e,
** proto�e p�ed inicializac� jsou hodnoty nedefinovan�, tedy libovoln�).
** Ke zru�en� bin�rn�ho stromu slou�� procedura BTDisposeTree.
**	
** V�imn�te si, �e zde se poprv� v hlavi�ce objevuje typ ukazatel na ukazatel,	
** proto je t�eba p�i pr�ci s RootPtr pou��t dereferen�n� oper�tor *.
**/
	
	(*RootPtr) = NULL;	////Inicializujeme tak ze Korenovy bude mat hodnotu NULL

}

void BTInsert (tBTNodePtr *RootPtr, int Content) {
/*   --------
** Vlo�� do stromu nov� uzel s hodnotou Content.
**
** Z pohledu vkl�d�n� ch�pejte vytv��en� strom jako bin�rn� vyhled�vac� strom,
** kde uzly s hodnotou men�� ne� m� otec le�� v lev�m podstromu a uzly v�t��
** le�� vpravo. Pokud vkl�dan� uzel ji� existuje, neprov�d� se nic (dan� hodnota
** se ve stromu m��e vyskytnout nejv��e jednou). Pokud se vytv��� nov� uzel,
** vznik� v�dy jako list stromu. Funkci implementujte nerekurzivn�.
**/
	
	if((*RootPtr) == NULL) 									//Vkladame do prazdneho stromu
	{
		tBTNodePtr PomVar = malloc(sizeof(struct tBTNode));	//alokujeme novy prvok
		
		if(PomVar == NULL)									//ak sa nepodari alokacia
			return;

		(*RootPtr) = PomVar;								//prave vytvorena hodnota bude korenovy uzol, nacita sa donho obsah
		(*RootPtr)->Cont = Content;
		(*RootPtr)->LPtr = NULL;							//Co lavych a pravych uzlov budu mat hodnotu NULL, lebo niesu vytvorene
		(*RootPtr)->RPtr = NULL;
			
	}
	
	else													//Vkladame do neprazdneho stromu
	{
		tBTNodePtr OUzol = NULL;							//OUzol je otcovsky uzol, na zac. hodnota NULL
		tBTNodePtr PomUz = (*RootPtr);						//PomUz - v nom bude ulozeny korenovy uzol, ten sa nezmeni, a s korenovym ulozenym v pom. premennej mozeme dalej pracovat

		while(PomUz != NULL)								
		{
			if(PomUz->Cont > Content)						//Ak bude sucasny korenovy vacsi ako obsah co hladame...
			{	
				OUzol = PomUz;								//Ulozime si sucasny korenovy do Otcovskeho, a zmenime korenovy na ten co je vlavo
				PomUz = PomUz->LPtr;
			}

			else if(PomUz->Cont < Content)					//Symetricke s predch.
			{
				OUzol = PomUz;
				PomUz = PomUz->RPtr;
			}
			else return;									//Inak ukonci
		}
		
	
		tBTNodePtr PomVar = malloc(sizeof(struct tBTNode));	//Alokujeme novy prvok

		if(PomVar == NULL)
			return;

		PomVar->Cont = Content;								//ulozime si do nove vytvoreneho obsah
		PomVar->LPtr = NULL;								//Co lavych a pravych uzlov budu mat hodnotu NULL, lebo niesu vytvorene
		PomVar->RPtr = NULL;
		
		if(OUzol->Cont < Content)							//Ak otcovsky obsah je mensi , novu hodnotu vlozime do toho kt. je pravym poduzlom otcovskeho
			OUzol->RPtr	= PomVar;

		else if(OUzol->Cont > Content)						//symetricke s predchadzajucim
			OUzol->LPtr	= PomVar;
	}

}

/*                                  PREORDER                                  */

void Leftmost_Preorder (tBTNodePtr ptr, tStackP *Stack)	{
/*   -----------------
** Jde po lev� v�tvi podstromu, dokud nenaraz� na jeho nejlev�j�� uzel.
**
** P�i pr�chodu Preorder nav�t�ven� uzly zpracujeme vol�n�m funkce BTWorkOut()
** a ukazatele na n� is ulo��me do z�sobn�ku.
**/

	while(ptr != NULL)			//pokial nebude nalavo NULL, teda az po najlavejsi
	{
		BTWorkOut(ptr);			//Postupne vypisuj a ukladaj na zasobnik.
		SPushP(Stack, ptr);
		ptr = ptr->LPtr; 		//Posun sa o dalsi lavu poduzol, znovu vypis pushni atd.

	}
	
}

void BTPreorder (tBTNodePtr RootPtr)	{
/*   ----------
** Pr�chod stromem typu preorder implementovan� nerekurzivn� s vyu�it�m funkce
** Leftmost_Preorder a z�sobn�ku ukazatel�. Zpracov�n� jednoho uzlu stromu
** realizujte jako vol�n� funkce BTWorkOut(). 
**/

	tStackP Stack;						//Pomocny zasobnik
	tBTNodePtr PomUz = RootPtr;
	SInitP(&Stack);

	Leftmost_Preorder(RootPtr, &Stack); //Napln zasobnik a vypis vsetky lave poduzly

	while(!SEmptyP(&Stack))				//Pokial nebude zasobnik prazdny....
	{
		PomUz = STopPopP(&Stack);		//z vrcholu odstran prvok a daj ho do pomocnej premennej
		PomUz = PomUz->RPtr;			//ulozime si pravy poduzol
		
		Leftmost_Preorder(PomUz, &Stack); //znovu (s pravym poduzlom) hladame najlavejsi, a postupne vypisujeme a ukladame na zasobnik...a takto dalej
	}

}


/*                                  INORDER                                   */ 

void Leftmost_Inorder(tBTNodePtr ptr, tStackP *Stack)		{
/*   ----------------
** Jde po lev� v�tvi podstromu, dokud nenaraz� na jeho nejlev�j�� uzel.
**
** P�i pr�chodu Inorder ukl�d�me ukazatele na v�echny nav�t�ven� uzly do
** z�sobn�ku. 
**/
		
	while(ptr != NULL)				//pokial nebude nalavo NULL, teda az po najlavejsi
	{
		SPushP(Stack, ptr);			//Uloz prvok na zasobnik, ale nevypisuj, to az neskor
		ptr = ptr->LPtr; 			//ulozime si dalsi lavy poduzol

	}
	
}

void BTInorder (tBTNodePtr RootPtr)	{
/*   ---------
** Pr�chod stromem typu inorder implementovan� nerekurzivn� s vyu�it�m funkce
** Leftmost_Inorder a z�sobn�ku ukazatel�. Zpracov�n� jednoho uzlu stromu
** realizujte jako vol�n� funkce BTWorkOut(). 
**/
	tStackP Stack;				     //Pomocny zasobnik...aj premenna v kt. bude ulozena hodnota korenoveho uzlu
	tBTNodePtr PomUz = RootPtr;

	SInitP(&Stack);
	Leftmost_Inorder(PomUz, &Stack); //Naplnime zasobnik lavymi poduzlami

	while(!SEmptyP(&Stack))			 //Pokial nebude zasobnik prazdny
	{
		PomUz = STopPopP(&Stack);	 //ulozime si do pomocnej premennej to co je na vrcholu zasobniku (prepiseme sucasne koren, kt. sa tam nachadzal)
		BTWorkOut(PomUz);			 //vypiseme uzol zo zasobniku
	
		if(PomUz->RPtr != NULL)		 //napln zasobnik najlevejsimi uzlami praveho podstromu
			Leftmost_Inorder(PomUz->RPtr, &Stack);
		
	}

}

/*                                 POSTORDER                                  */ 

void Leftmost_Postorder (tBTNodePtr ptr, tStackP *StackP, tStackB *StackB) {
/*           --------
** Jde po lev� v�tvi podstromu, dokud nenaraz� na jeho nejlev�j�� uzel.
**
** P�i pr�chodu Postorder ukl�d�me ukazatele na nav�t�ven� uzly do z�sobn�ku
** a sou�asn� do z�sobn�ku bool hodnot ukl�d�me informaci, zda byl uzel
** nav�t�ven poprv� a �e se tedy je�t� nem� zpracov�vat. 
**/
	while(ptr != NULL) 				//pokial nebude najlevejsi uzol laveho podstrom nulovy...
	{
		SPushP(StackP, ptr);		//...ukladaj postupne na zasobnik..
		SPushB(StackB, FALSE);		//...a prirad k nim hodnotu FALSE - este ich teda nespracuvaj
		ptr = ptr->LPtr;
	}

}

void BTPostorder (tBTNodePtr RootPtr)	{
/*           -----------
** Pr�chod stromem typu postorder implementovan� nerekurzivn� s vyu�it�m funkce
** Leftmost_Postorder, z�sobn�ku ukazatel� a z�sobn�ku hotdnot typu bool.
** Zpracov�n� jednoho uzlu stromu realizujte jako vol�n� funkce BTWorkOut(). 
**/
	tStackP StackP;					//2 pomocne zasobniky, jeden pre pravdivostne hodnoty - ci mame uz spracuvat alebo nie, a druhy pre prvky stromu (uzly)
	tStackB StackB;
	tBTNodePtr PomUz = RootPtr;

	SInitP(&StackP);
	SInitB(&StackB);
	Leftmost_Postorder(PomUz, &StackP, &StackB); //Naplnime zasobnik vsetkymi najlevejsimi uzlami laveho podstromu
	
	while(!SEmptyP(&StackP))					//Cyklus bezi az po vyprazdnenie zasobniku, teda az pokial nebude na vystupe posledna hodnota
	{
		PomUz = STopPopP(&StackP);				//uloz si hodnotu do pomocneho prvku. zial nemame oddelene implementovane funkcie pop a top...
		SPushP(&StackP, PomUz);					//...preto musime znovu vlozit prvok na zasobnik

		if(!STopPopB(&StackB))					//Ak sme este len raz navstivili uzol, teda vracia hodnotu FALSE , !FALSE = true, teda pojdeme k prvej casti podmien. prikazu
		{
			SPushB(&StackB, TRUE);				//vlozime hodnotu TRUE na bool zasobnik, to znamena ze uz ho najblizsie spracuvame , pretoze uz raz navstiveny bol 
			Leftmost_Postorder(PomUz->RPtr, &StackP, &StackB);	//Hned za tym vlozime na zasobnik prave uzly 
			continue;							//Cyklus ideme od zaciatku, znovu skontrolujeme uzol , ak mame spracuvat pokracujeme 2.vetvou, ak nie(napr. ze je na zas. pravy uzol) tak 1. vetvou
		}
			STopPopP(&StackP);					//uzol sme uz raz navstivili, takze ho dame pred zo zasobniku 
			BTWorkOut(PomUz);					//Vypiseme na vystup uzol , kt. sme naposledy pushli na zasobnik
	}
}


void BTDisposeTree (tBTNodePtr *RootPtr)	{
/*   -------------
** Zru�� v�echny uzly stromu a korektn� uvoln� jimi zabranou pam�.
**
** Funkci implementujte nerekurzivn� s vyu�it�m z�sobn�ku ukazatel�.
**/

	
	if((*RootPtr) == NULL)							//Ak uz je korenovy NULL, nic nerob
		return;			
	else
	{
		tStackP StackP;								//Pomocny zasobnik,pomocou neho sa bude rusit
		SInitP(&StackP);
		tBTNodePtr PomUz = (*RootPtr);				//pomocne premenne
		tBTNodePtr PomUz2 = NULL;

		while(1)									//bezi nekonecny cyklus
		{
			if(!SEmptyP(&StackP))	//ak zasobnik nieje prazdny
			{
				PomUz = STopPopP(&StackP);			//do pomocneho uzlu si vlozime hodnotu zo zasobniku , v cykle uz nic nerobime , pokracujeme dalsou iteraciou
				continue;
			}
			else if(PomUz == NULL) 					//cyklus sa ukonci ,az ked bude sucasny korenovy uzol prazdny
				break;

			PomUz2 = PomUz;
			PomUz = PomUz->LPtr;
			free(PomUz2);
		}

		(*RootPtr) = NULL; 							//Po zruseni celeho stromu proved to iste co pri inicializacii, teda nastav korenovy na NULL
	}
}

/* konec c402.c */

