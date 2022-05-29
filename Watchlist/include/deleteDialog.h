#pragma once

#include <wx/wx.h>

class DeleteDialog : public wxDialog
{
public:
    DeleteDialog(wxWindow *parent, wxWindowID id,
            const wxString &title,
            const wxPoint &pos = wxDefaultPosition,
            const wxSize &size = wxDefaultSize,
            long style = wxDEFAULT_DIALOG_STYLE,
            const wxString &name = wxString::FromAscii(wxDialogNameStr));

    virtual ~DeleteDialog();
    virtual bool TransferDataFromWindow();
    wxString getId() const { return id; }
    //wxString getGenre() const { return genre; }
private:
    void onUpdateOkButton(wxUpdateUIEvent& event);
    wxTextCtrl *idbox = nullptr;
    //wxTextCtrl *genrebox = nullptr;
    wxString id;
   // wxString genre;

   DECLARE_EVENT_TABLE()
};
