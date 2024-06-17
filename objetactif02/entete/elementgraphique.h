/*
objetactif02         version 1.0
Daniel Génon - 24.11.2023 - 08500 Revin
	  objetactif02  est un logiciel d'apprentissage à l'utilisation des bibliothèques :
gtkmm 4.8.0, cairomm 1.16.0 et pangomm 2.48.1
Le but est de créer une zone -Gtk::DrawingArea- dans laquelle nous dessinons des objets graphiques avec texte et image
que nous déplaçons, supprimons ou groupons, à l'aide de la sélection et du déplacement de la souris.

   Ce programme est un logiciel libre ; vous pouvez le redistribuer et/ou le modifier 
selon les termes de la Licence Publique Générale GNU telle que publiée par la Free Software Foundation :
- soit la version 2 de la Licence;
- soit (à votre choix) toute version ultérieure.
Ce programme est distribué SANS AUCUNE GARANTIE.
Voir la licence GNU GPL pour plus de détails.
*/
#ifndef ELEMENTGRAPHIQUE_H
#define ELEMENTGRAPHIQUE_H

#include <cairomm/context.h>
#include <pangomm.h>
#include <gdkmm/pixbuf.h>
#include <gdkmm/general.h>
#include <glibmm.h>
#include <giomm.h>

typedef double tabcoul[3];

struct dimsymbole
{
	double hauteur, largeur, xctr, yctr;
};

struct donneesymbole
{
	std::string txtcartouche;
	std::string txtcorps;
	std::string policecar;
	std::string imagecorps;
	int	taillepol;
	tabcoul	couleurpolice;
	tabcoul	couleurfond;
	tabcoul	couleurcartouche;
	dimsymbole	dimension;
};

class ElementGraphique
{
public:
	ElementGraphique();
	virtual ~ElementGraphique();
	
	virtual bool ContientPoint( const double x, const double y );
	virtual void BougerElement( const double dx, const double dy );
	virtual void PlacerElement( const double nx, const double ny );

	void ReDessiner(const Cairo::RefPtr<Cairo::Context>& cr);
  
protected:
	Cairo::RefPtr<Cairo::Context> tmpcr;
	double xg,xd,yh,yb;
	double xctr,yctr;
	
	void Couleurs(int valR, int valV, int valB);
	void DefinirCoordonnees( double larg, double haut );
	
	virtual void Dessiner();
};

class Rectangle : public ElementGraphique
{
public:
	Rectangle();
	virtual ~Rectangle();
	
protected:
	donneesymbole	*pdonnee;
	double htcartouche;
	
	virtual void Dessiner();
};

class Logiciel : public Rectangle
{
public:
	Logiciel( donneesymbole *ptrdonnee );
	virtual ~Logiciel();
};

class FichierJoint : public Rectangle
{
public:
	FichierJoint( donneesymbole *ptrdonnee );
	virtual ~FichierJoint();
};

#endif // ELEMENTGRAPHIQUE_H
