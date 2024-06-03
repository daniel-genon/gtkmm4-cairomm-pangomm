/*
objetactif01         version 1.0
Daniel Génon - 19.11.2023 - 08500 Revin
	  objetactif01  est un logiciel d'apprentissage à l'utilisation des bibliothèques : gtkmm 4.8.0 et cairo 1.16.0
Le but est de créer une zone -Gtk::DrawingArea- dans laquelle nous dessinons des objets graphiques
que nous déplaçons, supprimons ou groupons, à l'aide de la sélection et du déplacement de la souris.
   Ce programme est un logiciel libre ; vous pouvez le redistribuer et/ou le modifier 
selon les termes de la Licence Publique Générale GNU telle que publiée par la Free Software Foundation :
- soit la version 2 de la Licence;
- soit (à votre choix) toute version ultérieure.
Ce programme est distribué SANS AUCUNE GARANTIE.
Voir la licence GNU GPL pour plus de détails.
*/
#include "../entete/fenetre.h"
int main(int argc, char* argv[])
{
  auto app = Gtk::Application::create("org.gtkmm-cairomm-pangomm.objetactif01");
  return app->make_window_and_run<Fenetre>(argc, argv);
}
