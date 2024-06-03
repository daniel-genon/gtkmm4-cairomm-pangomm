/*
ElementGraphique
Daniel Génon - 19.11.2023 - 08500 Revin
Classe destinée à créer et manipuler les objets graphiques
   Ce programme est un logiciel libre ; vous pouvez le redistribuer et/ou le modifier 
selon les termes de la Licence Publique Générale GNU telle que publiée par la Free Software Foundation :
- soit la version 2 de la Licence;
- soit (à votre choix) toute version ultérieure.
Ce programme est distribué dans l'espoir qu'il sera utile, mais SANS AUCUNE GARANTIE.
Voir GNU GPL pour plus de détails.
*/
#include"../entete/elementgraphique.h"

ElementGraphique::ElementGraphique(){}
ElementGraphique::~ElementGraphique(){}

void ElementGraphique::ReDessiner(const Cairo::RefPtr<Cairo::Context>& cr)
{
	tmpcr = cr;
	Dessiner();
}
void ElementGraphique::Dessiner()
{
	tmpcr->rectangle(50,50,100,100);
	tmpcr->fill();
}

bool ElementGraphique::ContientPoint( const double x, const double y )
{
	return (((x>xg)&&(x<xd))&&((y>yh)&&(y<yb)));
}
void ElementGraphique::BougerElement( const double dx, const double dy )
{
	xctr += dx;
	yctr += dy;
	xg += dx;
	xd += dx;
	yh += dy;
	yb += dy;
	Dessiner();
}
void ElementGraphique::PlacerElement( const double nx, const double ny )
{
	double dplx = nx - xctr;
	double dply = ny - yctr;
	BougerElement( dplx, dply );
}

Rectangle::Rectangle(){};
Rectangle::Rectangle( const double xc, const double yc, const double largeur, const double hauteur )
{
	xctr = xc;
	yctr = yc;
	xg = xc-largeur/2.0;
	xd = xc+largeur/2.0;
	yh = yc-hauteur/2.0;
	yb = yc+hauteur/2.0;
}
Rectangle::~Rectangle(){}
void Rectangle::Dessiner()
{
	tmpcr->rectangle(xg,yh,xd-xg,yb-yh);
	tmpcr->fill();
}

Carre::Carre( const double xc, const double yc, const double valcote )
{
	xctr = xc;
	yctr = yc;
	double demicote = valcote/2.0;
	xg = xc-demicote;
	xd = xc+demicote;
	yh = yc-demicote;
	yb = yc+demicote;
}
Carre::~Carre(){}

Rond::Rond( const double xc, const double yc, const double rayon )
{
	xctr = xc;
	yctr = yc;
	rx = rayon;
	xg = xctr - rx;
	xd = xctr + rx;
	yh = yctr - rx;
	yb = yctr + rx;
}
Rond::~Rond(){}
void Rond::Dessiner()
{
	tmpcr->arc(xctr, yctr, rx, 0.0, 2.0*M_PI);
	tmpcr->fill();
}
bool Rond::ContientPoint( const double x, const double y )
{
	if(ElementGraphique::ContientPoint( x, y ))
	{
		double vx = abs(xctr-x);
		double vy = abs(yctr-y);
		//if(vx==0) return (vy<rx);// inutile puisque la valeur 0 est quasi impossible
		//if(vy==0) return (vx<rx);// inutile puisque la valeur 0 est quasi impossible
		return (hypot (vx, vy)<rx);
	}
	return false;
}


