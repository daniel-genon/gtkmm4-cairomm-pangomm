/*
ElementGraphique
Daniel Génon - 19.11.2023 - 08500 Revin
Classe destinée à créer des objets graphiques
   Ce programme est un logiciel libre ; vous pouvez le redistribuer et/ou le modifier 
selon les termes de la Licence Publique Générale GNU telle que publiée par la Free Software Foundation :
- soit la version 2 de la Licence;
- soit (à votre choix) toute version ultérieure.
Ce programme est distribué dans l'espoir qu'il sera utile, mais SANS AUCUNE GARANTIE.
Voir GNU GPL pour plus de détails.
*/
#ifndef ELEMENTGRAPHIQUE_H
#define ELEMENTGRAPHIQUE_H

#include <cairomm/context.h>

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
	
	virtual void Dessiner();
};

class Rectangle : public ElementGraphique
{
public:
	Rectangle();
	Rectangle( const double xc, const double yc, const double largeur, const double hauteur );
	virtual ~Rectangle();

protected:
	virtual void Dessiner();
  
};

class Carre : public Rectangle
{
public:
	Carre( const double xc, const double yc, const double valcote );
	virtual ~Carre();
  
};

class Rond : public ElementGraphique
{
public:
	Rond( const double xc, const double yc, const double rayon );
	virtual ~Rond();
	
	virtual bool ContientPoint( const double x, const double y );

protected:
	virtual void Dessiner();
	
private :
	double rx;
  
};

#endif // ELEMENTGRAPHIQUE_H
