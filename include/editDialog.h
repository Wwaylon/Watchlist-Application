#pragma once

#include <wx/wx.h>
#include <wx/translation.h>

class EditDialog : public wxDialog
{
public:
    EditDialog(wxWindow *parent, wxWindowID id,
            const wxString &title,
            const wxPoint &pos = wxDefaultPosition,
            const wxSize &size = wxDefaultSize,
            long style = wxDEFAULT_DIALOG_STYLE,
            // const wxString &name = wxASCII_STR(wxDialogNameStr));
            const wxString &name = wxString::FromAscii(wxDialogNameStr));

    virtual ~EditDialog();
    virtual bool TransferDataFromWindow();
    wxString getId() const { return id; }
    wxString getName() const { return name; }
    wxString getGenre() const { return genre; }
    wxString getStatus() const { return status; }
private:
    void onUpdateOkButton(wxUpdateUIEvent& event);
    wxTextCtrl *idbox = nullptr;
    wxTextCtrl *namebox = nullptr;
    wxTextCtrl *genrebox = nullptr;
    wxTextCtrl *statusbox = nullptr;
    
    
    wxString id;
    wxString name;
    wxString genre;
    wxString status;
    DECLARE_EVENT_TABLE()
};
