//Shubhayu Shrestha 1001724804
//Coding Assignment 7
//Answer: SpongeBob SquarePants
#include <stdlib.h>
#include <gtkmm.h>
#include <iostream>
#include <stdbool.h>


class MainWindow : public Gtk::Window
{
public:
    MainWindow();
    void button_OK(Gtk::Entry *entry);
    void button_Cancel();
};


MainWindow::MainWindow()
{
    //setting title
    set_title("Welcome to My Guessing Game");

    //settign the default size of the box
    set_default_size(500, 400);

    //creating box
    Gtk::Box *MainVBox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 0));
    Gtk::MenuBar *MyMenuBar = Gtk::manage(new Gtk::MenuBar());
    MyMenuBar->override_background_color(Gdk::RGBA("dark gray")); 
    MainVBox->pack_start(*MyMenuBar, Gtk::PACK_SHRINK, 0);

    //adding new box to window widet
    add(*MainVBox);

    //Menu Item 1
    Gtk::MenuItem *HintHouse = Gtk::manage(new Gtk::MenuItem("_Home Hint", true));
    //Menu Item 2
    Gtk::MenuItem *HintFriend = Gtk::manage(new Gtk::MenuItem("_Friend Hint", true));
    //Menu Item 3
    Gtk::MenuItem *HintPet = Gtk::manage(new Gtk::MenuItem("_Pet Hint", true));

    MyMenuBar->append(*HintHouse);
    MyMenuBar->append(*HintFriend);
    MyMenuBar->append(*HintPet);

    //Submenu 1
    Gtk::Menu *HintSubMenu1 = Gtk::manage(new Gtk::Menu());
    HintHouse->set_submenu(*HintSubMenu1);

    Gtk::MenuItem *HintHouse_More = Gtk::manage(new Gtk::MenuItem("_He lives in a pineapple under the sea.", true));
    HintSubMenu1->append(*HintHouse_More);

    //Submenu 2
    Gtk::Menu *HintSubMenu2 = Gtk::manage(new Gtk::Menu());
    HintFriend->set_submenu(*HintSubMenu2);

    Gtk::MenuItem *HintFriend_More = Gtk::manage(new Gtk::MenuItem("_His best friend is a star fish.", true));
    HintSubMenu2->append(*HintFriend_More);

    //Submenu 3
    Gtk::Menu *HintSubMenu3 = Gtk::manage(new Gtk::Menu());
    HintPet->set_submenu(*HintSubMenu3);

    Gtk::MenuItem *HintPet_More = Gtk::manage(new Gtk::MenuItem("_He has a pet snail.", true));
    HintSubMenu3->append(*HintPet_More);

    //Asking Question
    Gtk::Label *MyLabel = Gtk::manage(new Gtk::Label{"Who is this?"});
    MainVBox->pack_start(*MyLabel);

    //Show Image
    Gtk::Image *MyImage = Gtk::manage(new Gtk::Image{"spongebob.jpg"});
    MainVBox->pack_start(*MyImage);

    //Add Buttons and entry box
    Gtk::Box *hBox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 0));
    MainVBox->add(*hBox);

    //making vbox1
    Gtk::Box *vBox1 = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 1));
    hBox->pack_end(*vBox1);

    //making vbox2
    Gtk::Box *vBox2 = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 1));
    hBox->pack_end(*vBox2);

    //creating entry
    Gtk::Entry *entry = Gtk::manage(new Gtk::Entry());
    entry->set_text("Enter your guess here");
    entry->set_max_length(50);
    entry->select_region(0, entry->get_text_length());
    entry->signal_activate().connect(sigc::bind<Gtk::Entry *>(sigc::mem_fun(*this, &MainWindow::button_OK), (entry)));

    //OK button
    Gtk::Button *okButton = Gtk::manage(new Gtk::Button{"OK"});
    vBox2->pack_start(*okButton);
    okButton->set_border_width(3);

    //Cancel Button
    Gtk::Button *cancButton = Gtk::manage(new Gtk::Button{"Cancel"});
    vBox2->pack_start(*cancButton);
    cancButton->set_border_width(3);

    //Cancel Button Signal
    cancButton->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::button_Cancel));

    //Ok Button Signal
    okButton->signal_clicked().connect(sigc::bind<Gtk::Entry *>(sigc::mem_fun(*this, &MainWindow::button_OK), (entry)));



    //adding entry
    vBox1->add(*entry);

    //changing focus to entry box
    entry->grab_focus(); 

    //setting position to center
    set_position(Gtk::WIN_POS_CENTER);

    //Displays to Screen
    MainVBox->show_all();
}

//button okay
void MainWindow::button_OK(Gtk::Entry *entry)
{
    std::string answer=entry->get_text();
    if(answer.compare("SpongeBob SquarePants") == 0)
    {
        Gtk::MessageDialog outcome("You guessed <span fgcolor='#0000ff'>correctly!!</span>", true, Gtk::MESSAGE_WARNING, Gtk::BUTTONS_OK, false);
        outcome.run();
        hide(); 
    }
    else
    {
        Gtk::MessageDialog outcome("Your answer is not <span fgcolor='#ff0000'>correct</span>.\nPlease try again", true, Gtk::MESSAGE_ERROR, Gtk::BUTTONS_OK, false);
        outcome.run();
    }
}

//button cancel
void MainWindow::button_Cancel()
{
    // hide the window which will cause the application to finish
    hide();
}

int main(int argc, char *argv[])
{
    auto app = Gtk::Application::create(argc, argv, "");
    MainWindow MyWindow;
    return app->run(MyWindow);
}
