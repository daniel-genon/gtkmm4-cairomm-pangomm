/*
Fenetre
Daniel Génon - 19.11.2023 - 08500 Revin
Classe de création de l'interface de l'application test
   Ce programme est un logiciel libre ; vous pouvez le redistribuer et/ou le modifier 
selon les termes de la Licence Publique Générale GNU telle que publiée par la Free Software Foundation :
- soit la version 2 de la Licence;
- soit (à votre choix) toute version ultérieure.
Ce programme est distribué dans l'espoir qu'il sera utile, mais SANS AUCUNE GARANTIE.
Voir GNU GPL pour plus de détails.
*/
#ifndef FENETRE_H
#define FENETRE_H
#include <gtkmm.h>
#include "../entete/airededessin.h"
class Fenetre : public Gtk::Window
{
	public:
		Fenetre();
		virtual ~Fenetre();
private:
	AireDeDessin *zonegraphique;
	Glib::RefPtr<Gtk::CssProvider> styledecor;
//slots
	void ChoisirObjet(int n_press, double x, double y);
	void AppuyerSouris( int n_press, double x, double y );
	void LacherSouris( int n_press, double x, double y );
	void SourisBouge( double x, double y );
};
#endif /* FENETRE_H */ 
