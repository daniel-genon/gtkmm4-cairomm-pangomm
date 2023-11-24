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
#include"../entete/elementgraphique.h"
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
void ElementGraphique::DefinirCoordonees( double larg, double haut)
{
	xg = xctr-larg/2.0;
	xd = xctr+larg/2.0;
	yh = yctr-haut/2.0;
	yb = yctr+haut/2.0;
}

Rectangle::Rectangle()
{
	double largeur = 150.0;
	double hauteur = 80.0;
	xctr = 80;
	yctr = 70;
	DefinirCoordonees(largeur,hauteur);
	htcartouche		= (yb-yh)*0.4;
	txtcartouche	= "rectangle";
	txtcorps		= "corps";
	policecar		= "Free Serif";
	imagecorps		= "./rect48.png";
	taillepol		= 10;
	p_rouge=0; 	p_vert=0;	p_bleu=0;
	f_rouge=251;f_vert=174;	f_bleu=54;
	t_rouge=255;t_vert=255;	t_bleu=0;
}
Rectangle::~Rectangle(){}

void Rectangle::Dessiner()
{
    Couleurs(f_rouge, f_vert, f_bleu);	
		tmpcr->rectangle(xg,yh,xd-xg,yb-yh);
		tmpcr->fill();
    Couleurs(t_rouge, t_vert, t_bleu);	
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
    Couleurs(p_rouge, p_vert, p_bleu);	
	Pango::FontDescription lettrage;
		lettrage.set_family(policecar);
		lettrage.set_weight(Pango::Weight::NORMAL);
		lettrage.set_size(Pango::SCALE*Pango::SCALE_X_LARGE*taillepol);
		
	auto image = Gdk::Pixbuf::create_from_file(imagecorps);
		int lgimg = image->get_width();
		int htimg = image->get_height();
		
	int lgtxt, httxt;
	Glib::RefPtr<Pango::Layout> cadrecorp = Pango::Layout::create(tmpcr);
		cadrecorp->set_font_description(lettrage);
		cadrecorp->set_text(txtcorps);
			cadrecorp->get_pixel_size( lgtxt, httxt );
	tmpcr->move_to(xctr+(lgimg*0.375)-lgtxt/2,yctr+htcartouche/2-httxt/2);
	cadrecorp->show_in_cairo_context(tmpcr);
	
	Glib::RefPtr<Pango::Layout> cadrecart = Pango::Layout::create(tmpcr);
		cadrecart->set_font_description(lettrage);
		cadrecart->set_text(txtcartouche);
			cadrecart->get_pixel_size( lgtxt, httxt );
	tmpcr->move_to(xctr-lgtxt/2,yh+htcartouche/2-httxt/2);
	cadrecart->show_in_cairo_context(tmpcr);
	
	Gdk::Cairo::set_source_pixbuf(tmpcr, image, xg-image->get_width()*0.25, yh+htcartouche+image->get_height()*0.25);
	tmpcr->paint();
}

Logiciel::Logiciel()
{
	txtcartouche	= "Logiciel";
	txtcorps		= "Edit";
	policecar		= "Liberation Mono";
	imagecorps		= "./edit48.png";
	taillepol		= 8;
}
Logiciel::~Logiciel(){}

FichierJoint::FichierJoint()
{
	double largeur = 180.0;
	double hauteur = 50.0;
	xctr = 200;
	yctr = 100;
	DefinirCoordonees(largeur,hauteur);
	txtcartouche	= "Fichier de travail";
	txtcorps		= "texte édito";
	policecar		= "Dejavu Serif";
	imagecorps		= "./ftrav48.png";
	taillepol		= 7;
	htcartouche		= (yb-yh)*0.4;
	f_rouge=137; f_vert=251; f_bleu=250;
}
FichierJoint::~FichierJoint(){}
