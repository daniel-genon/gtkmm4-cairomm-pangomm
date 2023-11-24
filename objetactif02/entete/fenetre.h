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
