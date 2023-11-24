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
#include "../entete/airededessin.h"
AireDeDessin::AireDeDessin()
{
	set_content_width(600);
	set_content_height(450);
	stx = sty = 0.0;
	graphestocke = grapheselectionne = nullptr;
	set_draw_func(sigc::mem_fun(*this, &AireDeDessin::Dessiner));
}
AireDeDessin::~AireDeDessin()
{
	for (unsigned i=0; i<lstgraphe.size(); i++)
		delete lstgraphe[i];
}
void AireDeDessin::Dessiner(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height)
{
	for (unsigned i=0; i<lstgraphe.size(); i++)
		lstgraphe[i]->ReDessiner(cr);
}
void AireDeDessin::SymboleLogiciel()
{
	Logiciel *graphtmp = new Logiciel();
	lstgraphe.push_back(graphtmp);
	queue_draw();
}
void AireDeDessin::SymboleFichierJoint()
{
	FichierJoint *graphtmp = new FichierJoint();
	lstgraphe.push_back(graphtmp);
	queue_draw();
}
ElementGraphique *AireDeDessin::ChercherAuPoint(const double vx, const double vy)
{
	for (unsigned i=0; i<lstgraphe.size(); i++)
	{
		if(lstgraphe[i]->ContientPoint(vx,vy))
			return lstgraphe[i];
	}
	return nullptr;
}
void AireDeDessin::TesterObjet(const double vx, const double vy)
{
	if( (graphestocke = ChercherAuPoint( vx, vy)) != nullptr)
	{
		stx=vx;
		sty=vy;
	}
}
bool AireDeDessin::ElementStocke(){ return graphestocke != nullptr;}
bool AireDeDessin::ElementSelectionne(){ return grapheselectionne != nullptr;}
void AireDeDessin::ActualiserPositionElement(const double nx, const double ny)
{
	graphestocke->BougerElement((nx-stx),(ny-sty));
	stx=nx;
	sty=ny;
	queue_draw();
}
void AireDeDessin::SelectionnerObjet(const double vx, const double vy)
{
	grapheselectionne = ChercherAuPoint( vx, vy);
}

void AireDeDessin::NettoyerSelection()
{
	stx = sty = 0;
	graphestocke = grapheselectionne = nullptr;
}
void AireDeDessin::SupprimerSelection()
{
	if(grapheselectionne != nullptr)
	{
		for (unsigned i=0; i<lstgraphe.size(); i++)
		{
			if(lstgraphe[i]==grapheselectionne)
			{
				lstgraphe.erase(lstgraphe.begin()+i);
				delete grapheselectionne;
				NettoyerSelection();
				queue_draw();
			}
		}
	}
}
void AireDeDessin::Grouper()
{
	if(lstgraphe.size()>0)
	{
		int tpxc	= get_content_width()/2;
		int tpyc	= get_content_height()/2;
		for (unsigned i=0; i<lstgraphe.size(); i++)
		{
			lstgraphe[i]->PlacerElement(tpxc,tpyc);
		}
		queue_draw();
	}
}


