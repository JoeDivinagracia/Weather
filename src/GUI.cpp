#include <gtkmm.h>
#include <iostream>
#include <string>
#include "includes/weather.h"

Gtk::ApplicationWindow* pApplication = nullptr;

void getEntryText(Gtk::Entry* copy, Gtk::Label* locationLabel){
  Glib::ustring loc = "\""+copy->get_text()+"\"";
  getWeather(loc);
  locationLabel->set_text(loc);
}

int main(int argc, char** argv){
  auto app = Gtk::Application::create(argc, argv, "org.gtk.example");
  auto refBuilder = Gtk::Builder::create();
  try{
    refBuilder->add_from_file("GUI.glade");
  }
  catch(const Glib::FileError& ex){
    std::cerr << "File Error: " << ex.what() << std::endl;
  }
  catch(const Glib::MarkupError& ex){
    std::cerr << "Markup Error: " << ex.what() << std::endl;
  }
  catch(const Gtk::BuilderError& ex){
    std::cerr << "Builder Error: " << ex.what() << std::endl;
  }

  refBuilder->get_widget("TopLevel", pApplication);
  if(pApplication){
    Gtk::Fixed* fixedLayout = nullptr;
    refBuilder->get_widget("layout_fixed", fixedLayout);
    if(fixedLayout){
      Gtk::Label* locationLabel = nullptr;
      refBuilder->get_widget("label_location", locationLabel);
      Gtk::Label* locationName = nullptr;
      refBuilder->get_widget("label_locationName", locationName);
      
      Gtk::Entry* locationEntry = nullptr;
      refBuilder->get_widget("entry_location", locationEntry);
      if(locationEntry){
	//this sends a signal to the function when enter is pressed in the TextEntry field
	locationEntry->signal_activate().connect(sigc::bind<Gtk::Entry*,Gtk::Label*>(sigc::ptr_fun(getEntryText),locationEntry,locationName));
      }

      Gtk::Button* locationSearchButton = nullptr;
      refBuilder->get_widget("button_search_location", locationSearchButton);
      if(locationSearchButton){
	locationSearchButton->signal_clicked().connect(sigc::bind<Gtk::Entry*,Gtk::Label*>(sigc::ptr_fun(getEntryText),locationEntry,locationName));
      }

      Gtk::Separator* pageBreak = nullptr;
      refBuilder->get_widget("pageBreak", pageBreak);

      Gtk::ScrolledWindow* locationList = nullptr;
      refBuilder->get_widget("locationList", locationList);
    }
    app->run(*pApplication);
  }
  delete pApplication;
  return 0;
}
