#include <wx/wx.h>
#include <wx/listctrl.h>
#include <wx/stopwatch.h>
#include "MainFrame.h"

#include <string>
#include <vector>
#include <unordered_set>

#include <fstream>
#include <filesystem>

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    MainFrame *frame = new MainFrame("Watchlist Application", wxPoint(50, 50), wxSize(800, 600));
    frame->Show(true);
    return true;
}


