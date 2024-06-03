/*
AireDeDessin
Daniel Génon - 19.11.2023 - 08500 Revin
Classe destinée à créer et manipuler les objets graphiques
   Ce programme est un logiciel libre ; vous pouvez le redistribuer et/ou le modifier 
selon les termes de la Licence Publique Générale GNU telle que publiée par la Free Software Foundation :
- soit la version 2 de la Licence;
- soit (à votre choix) toute version ultérieure.
Ce programme est distribué dans l'espoir qu'il sera utile, mais SANS AUCUNE GARANTIE.
Voir GNU GPL pour plus de détails.
*/
#ifndef AIRE_DESSIN_H
#define AIRE_DESSIN_H

#include <gtkmm/drawingarea.h>
#include <cairomm/context.h>
#include "elementgraphique.h"
#include <algorithm>

class AireDeDessin : public Gtk::DrawingArea
{
public:
  AireDeDessin();
  virtual ~AireDeDessin();

  void SymboleCarre();
  void SymboleRectangle();
  void SymboleRond();
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
	std::vector<ElementGraphique*>::iterator ctmp;
	ElementGraphique *graphestocke, *grapheselectionne;
	ElementGraphique *ChercherAuPoint(const double vx, const double vy);

};
#endif // AIRE_DESSIN_H
