#include "deleteDialog.h"

BEGIN_EVENT_TABLE(DeleteDialog, wxDialog)
    EVT_UPDATE_UI(wxID_OK, DeleteDialog::onUpdateOkButton)
END_EVENT_TABLE()

DeleteDialog::DeleteDialog(wxWindow *parent, wxWindowID id,
        const wxString &title,
        const wxPoint &pos,
        const wxSize &size,
        long style,
        const wxString &name): wxDialog(parent, id, title, pos, size, style, name)
{
    wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);

//id field
    wxBoxSizer *idSizer = new wxBoxSizer(wxHORIZONTAL);
//name field text
    wxStaticText *idLabel = new wxStaticText(this, wxID_ANY, "id: ");
    idLabel->SetMinSize(wxSize(50, idLabel->GetMinSize().y));
    idSizer->Add(idLabel);

    idbox = new wxTextCtrl(this, wxID_ANY);
    idSizer->Add(idbox, 1);

    mainSizer->Add(idSizer, 0,  wxEXPAND | wxALL, 5);

//button
    wxSizer* buttonSizer = CreateButtonSizer(wxOK | wxCANCEL);
    mainSizer->Add(buttonSizer, 0, wxALIGN_RIGHT | wxALL, 10);

    SetSizer(mainSizer);
    SetMinSize(wxSize(400, 100));
    Fit();
}

bool DeleteDialog::TransferDataFromWindow()
{
    id = idbox->GetValue();
    return true;
}

void DeleteDialog::onUpdateOkButton(wxUpdateUIEvent& event)
{
    event.Enable(false);

    if(!idbox->GetValue().empty() && idbox->GetValue().IsNumber())
    {
        event.Enable(true);
    }
}

DeleteDialog::~DeleteDialog()
{

}