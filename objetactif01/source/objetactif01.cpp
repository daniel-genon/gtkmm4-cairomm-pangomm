#include "../entete/fenetre.h"

int main(int argc, char* argv[])
{
  auto app = Gtk::Application::create("org.gtkmm-cairomm-pangomm.objetactif01");
  return app->make_window_and_run<Fenetre>(argc, argv);
}
