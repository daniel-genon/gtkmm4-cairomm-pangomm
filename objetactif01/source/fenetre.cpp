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
#include "../entete/fenetre.h"
Fenetre::Fenetre()
{
	set_title("Interface pour tests graphiques");
	set_default_size(600, 500);
	
	Gtk::Box *total = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::VERTICAL, 2 );
	Gtk::Box *zonebouton = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::HORIZONTAL, 2 );
		zonebouton->set_halign(Gtk::Align::CENTER);
	Gtk::Box *zoneboutoncentre = Gtk::make_managed<Gtk::Box>( Gtk::Orientation::HORIZONTAL, 2 );

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

	Gtk::Button *bgrouper = Gtk::make_managed<Gtk::Button>("grouper");
		bgrouper->signal_clicked().connect(sigc::bind(sigc::mem_fun(*zonegraphique, &AireDeDessin::Grouper))) ;
		bgrouper->set_name("grouper");

	Gtk::Button *bcarre = Gtk::make_managed<Gtk::Button>("carré");
		bcarre->signal_clicked().connect(sigc::bind(sigc::mem_fun(*zonegraphique, &AireDeDessin::SymboleCarre))) ;
	Gtk::Button *brectangle = Gtk::make_managed<Gtk::Button>("rectangle");
		brectangle->signal_clicked().connect(sigc::bind(sigc::mem_fun(*zonegraphique, &AireDeDessin::SymboleRectangle))) ;
	Gtk::Button *brond = Gtk::make_managed<Gtk::Button>("rond");
		brond->signal_clicked().connect(sigc::bind(sigc::mem_fun(*zonegraphique, &AireDeDessin::SymboleRond))) ;

	Gtk::Button *bsupprimer = Gtk::make_managed<Gtk::Button>("supprimer");
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
	
  styledecor = Gtk::CssProvider::create();
  Gtk::StyleContext::add_provider_for_display(get_display(), styledecor, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
  styledecor->load_from_path("objetactif01.css");
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
