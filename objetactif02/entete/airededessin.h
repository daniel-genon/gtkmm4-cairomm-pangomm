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
#ifndef AIRE_DESSIN_H
#define AIRE_DESSIN_H

#include <gtkmm/drawingarea.h>
#include <cairomm/context.h>
#include "elementgraphique.h"

class AireDeDessin : public Gtk::DrawingArea
{
public:
  AireDeDessin();
  virtual ~AireDeDessin();

  void SymboleLogiciel();
  void SymboleFichierJoint();
  void Grouper();
  void SupprimerSelection();
  void TesterObjet(const double vx, const double vy);
  bool ElementStocke();
  void NettoyerSelection();
  void ActualiserPositionElement(const double nx, const double ny);
  void SelectionnerObjet(const double nx, const double ny);
  
protected:
  void Dessiner(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height);
  bool ElementSelectionne();
  
private:
	double	stx,sty;
	std::vector<ElementGraphique*> lstgraphe;
	std::vector<donneesymbole> lstdonnee;
	ElementGraphique *graphestocke, *grapheselectionne;
	ElementGraphique *ChercherAuPoint(const double vx, const double vy);
	
	void FormateCouleur( tabcoul &tabcouleur, const std::string &phrasecouleur );
	void ChargerDonneeSymbole();
};

#endif // AIRE_DESSIN_H
