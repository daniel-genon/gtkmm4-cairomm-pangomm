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
#include "../entete/elementgraphique.h"
ElementGraphique::ElementGraphique(){}
ElementGraphique::~ElementGraphique(){}

void ElementGraphique::ReDessiner(const Cairo::RefPtr<Cairo::Context>& cr)
{
	tmpcr = cr;
	Dessiner();
}
void ElementGraphique::Dessiner(){}

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
void ElementGraphique::Couleurs(int valR, int valV, int valB)
{
	tmpcr->set_source_rgb( (valR/255.0), (valV/255.0), (valB/255.0) );
}
void ElementGraphique::DefinirCoordonnees( double larg, double haut)
{
	xg = xctr-larg/2.0;
	xd = xctr+larg/2.0;
	yh = yctr-haut/2.0;
	yb = yctr+haut/2.0;
}

Rectangle::Rectangle()
{
	xctr = 0.0;
	yctr = 0.0;
	DefinirCoordonnees(0,0);
}
Rectangle::~Rectangle(){}

void Rectangle::Dessiner()
{
    Couleurs(pdonnee->couleurfond[0], pdonnee->couleurfond[1], pdonnee->couleurfond[2]);	
		tmpcr->rectangle(xg,yh,xd-xg,yb-yh);
		tmpcr->fill();
    Couleurs(pdonnee->couleurcartouche[0], pdonnee->couleurcartouche[1], pdonnee->couleurcartouche[2]);	
		tmpcr->rectangle(xg,yh,xd-xg,htcartouche);
		tmpcr->fill();
	Couleurs(0, 0, 0);	
		tmpcr->set_line_width(3.0);
		tmpcr->move_to(xg,yh);
		tmpcr->line_to(xd,yh);
		tmpcr->line_to(xd,yb);
		tmpcr->line_to(xg,yb);
		tmpcr->close_path();
		tmpcr->stroke();
    Couleurs(pdonnee->couleurpolice[0], pdonnee->couleurpolice[1], pdonnee->couleurpolice[2]);	
	Pango::FontDescription lettrage;
		lettrage.set_family(pdonnee->policecar);
		lettrage.set_weight(Pango::Weight::NORMAL);
		lettrage.set_size( Pango::SCALE * Pango::SCALE_X_LARGE * pdonnee->taillepol );

	Glib::RefPtr<Gdk::Pixbuf> image = Gdk::Pixbuf::create_from_resource(pdonnee->imagecorps);//resobjetactif_get_resource
		int lgimg = image->get_width();
		int htimg = image->get_height();
		
	int lgtxt, httxt;
	Glib::RefPtr<Pango::Layout> cadrecorp = Pango::Layout::create(tmpcr);
		cadrecorp->set_font_description(lettrage);
		cadrecorp->set_text(pdonnee->txtcorps);
			cadrecorp->get_pixel_size( lgtxt, httxt );
	tmpcr->move_to(xctr+(lgimg*0.375)-lgtxt/2,yctr+htcartouche/2-httxt/2);
	cadrecorp->show_in_cairo_context(tmpcr);
	
	Glib::RefPtr<Pango::Layout> cadrecart = Pango::Layout::create(tmpcr);
		cadrecart->set_font_description(lettrage);
		cadrecart->set_text(pdonnee->txtcartouche);
			cadrecart->get_pixel_size( lgtxt, httxt );
	tmpcr->move_to(xctr-lgtxt/2,yh+htcartouche/2-httxt/2);
	cadrecart->show_in_cairo_context(tmpcr);
	
	Gdk::Cairo::set_source_pixbuf(tmpcr, image, xg-image->get_width()*0.25, yh+htcartouche+image->get_height()*0.25);
	tmpcr->paint();
}

Logiciel::Logiciel( donneesymbole *ptrdonnee )
{
	pdonnee = ptrdonnee;
	xctr = pdonnee->dimension.xctr;
	yctr = pdonnee->dimension.yctr;
	DefinirCoordonnees(pdonnee->dimension.largeur,pdonnee->dimension.hauteur);
	htcartouche		= (yb-yh)*0.4;
}
Logiciel::~Logiciel(){}

FichierJoint::FichierJoint( donneesymbole *ptrdonnee )
{
	pdonnee = ptrdonnee;
	xctr = 200;
	yctr = 100;
	DefinirCoordonnees(pdonnee->dimension.largeur,pdonnee->dimension.hauteur);
	htcartouche		= (yb-yh)*0.4;
}
FichierJoint::~FichierJoint(){}
