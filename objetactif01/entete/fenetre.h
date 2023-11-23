/*
 * fenetre.h
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
		
protected:

	Glib::RefPtr<Gtk::CssProvider> m_refCssProvider;
	
private:

	AireDeDessin *zonegraphique;

	void ChoisirObjet(int n_press, double x, double y);
	void AppuyerSouris( int n_press, double x, double y );
	void LacherSouris( int n_press, double x, double y );
	void SourisBouge( double x, double y );

};
#endif /* FENETRE_H */ 
