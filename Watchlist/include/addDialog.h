#pragma once

#include <wx/wx.h>

class AddDialog : public wxDialog
{
public:
    AddDialog(wxWindow *parent, wxWindowID id,
            const wxString &title,
            const wxPoint &pos = wxDefaultPosition,
            const wxSize &size = wxDefaultSize,
            long style = wxDEFAULT_DIALOG_STYLE,
            const wxString &name = wxString::FromAscii(wxDialogNameStr));

    virtual ~AddDialog();
    virtual bool TransferDataFromWindow();
    wxString getName() const { return name; }
    wxString getGenre() const { return genre; }
    wxString getStatus() const { return status; }
private:

    wxTextCtrl *namebox = nullptr;
    wxTextCtrl *genrebox = nullptr;
    wxTextCtrl *statusbox = nullptr;
    wxString name;
    wxString genre;
    wxString status;
};
