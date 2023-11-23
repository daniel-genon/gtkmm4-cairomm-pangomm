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
Fenetre::Fenetre()
{
	set_title("Interface pour tests graphiques");
	set_default_size(600, 500);
	
	auto total = 	Gtk::make_managed<Gtk::Box>( Gtk::Orientation::VERTICAL, 2 );
	auto zonebouton = 	Gtk::make_managed<Gtk::Box>( Gtk::Orientation::HORIZONTAL, 2 );
		zonebouton->set_halign(Gtk::Align::CENTER);
	auto zoneboutoncentre = 	Gtk::make_managed<Gtk::Box>( Gtk::Orientation::HORIZONTAL, 2 );

	zonegraphique = Gtk::make_managed<AireDeDessin>();
		zonegraphique->set_expand(true);
		zonegraphique->set_name("zonegraphe");
	auto controle = Gtk::GestureClick::create();
		controle->set_propagation_phase(Gtk::PropagationPhase::CAPTURE);
		controle->set_button(1);
		controle->signal_pressed().connect(sigc::mem_fun(*this, &Fenetre::AppuyerSouris));
		controle->signal_released().connect(sigc::mem_fun(*this, &Fenetre::LacherSouris),true);
	auto controledroit = Gtk::GestureClick::create();
		controledroit->set_propagation_phase(Gtk::PropagationPhase::CAPTURE);
		controledroit->set_button(3);
		controledroit->signal_pressed().connect(sigc::mem_fun(*this, &Fenetre::ChoisirObjet));

	auto controlebouge = Gtk::EventControllerMotion::create();
		controlebouge->signal_motion().connect(sigc::mem_fun(*this, &Fenetre::SourisBouge));

	zonegraphique->add_controller(controle);
	zonegraphique->add_controller(controledroit);
	zonegraphique->add_controller(controlebouge);

	auto bgrouper = Gtk::make_managed<Gtk::Button>("groupire");
		bgrouper->signal_clicked().connect(sigc::bind(sigc::mem_fun(*zonegraphique, &AireDeDessin::Grouper))) ;
		bgrouper->set_name("groupire");

	auto bcarre = Gtk::make_managed<Gtk::Button>("carré");
		bcarre->signal_clicked().connect(sigc::bind(sigc::mem_fun(*zonegraphique, &AireDeDessin::SymboleCarre))) ;
	auto brectangle = Gtk::make_managed<Gtk::Button>("rectangle");
		brectangle->signal_clicked().connect(sigc::bind(sigc::mem_fun(*zonegraphique, &AireDeDessin::SymboleRectangle))) ;
	auto brond = Gtk::make_managed<Gtk::Button>("rond");
		brond->signal_clicked().connect(sigc::bind(sigc::mem_fun(*zonegraphique, &AireDeDessin::SymboleRond))) ;

	auto bsupprimer = Gtk::make_managed<Gtk::Button>("supprimer");
		bsupprimer->signal_clicked().connect(sigc::bind(sigc::mem_fun(*zonegraphique, &AireDeDessin::SupprimerSelection))) ;
		bsupprimer->set_name("supprimer");
		
	zoneboutoncentre->append(*bcarre);
	zoneboutoncentre->append(*brectangle);
	zoneboutoncentre->append(*brond);
	zonebouton->append(*bgrouper);
	zonebouton->append(*zoneboutoncentre);
	zonebouton->append(*bsupprimer);
	total->append(*zonebouton);
	total->append(*zonegraphique);
	set_child(*total);
	
  m_refCssProvider = Gtk::CssProvider::create();
  Gtk::StyleContext::add_provider_for_display(get_display(), m_refCssProvider, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
  m_refCssProvider->load_from_path("objetactif01.css");
}
Fenetre::~Fenetre(){}

void Fenetre::AppuyerSouris(int n_press, double x, double y)
{
	zonegraphique->TesterObjet(x,y);
}
void Fenetre::LacherSouris(int n_press, double x, double y)
{
	if(zonegraphique->ElementStocke())
		zonegraphique->NettoyerSelection();
}
void Fenetre::SourisBouge( double x, double y )
{
	if(zonegraphique->ElementStocke())
	{
		zonegraphique->ActualiserPositionElement(x,y);
	}
}
void Fenetre::ChoisirObjet(int n_press, double x, double y)
{
	zonegraphique->SelectionnerObjet(x,y);
}
