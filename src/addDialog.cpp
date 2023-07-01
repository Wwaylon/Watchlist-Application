#include "addDialog.h"

AddDialog::AddDialog(wxWindow *parent, wxWindowID id,
        const wxString &title,
        const wxPoint &pos,
        const wxSize &size,
        long style,
        const wxString &name): wxDialog(parent, id, title, pos, size, style, name)
{
    wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);

//name field
    wxBoxSizer *NameSizer = new wxBoxSizer(wxHORIZONTAL);
//name field text
    wxStaticText *nameLabel = new wxStaticText(this, wxID_ANY, "Name: ");
    nameLabel->SetMinSize(wxSize(50, nameLabel->GetMinSize().y));
    NameSizer->Add(nameLabel);

    namebox = new wxTextCtrl(this, wxID_ANY);
    NameSizer->Add(namebox, 1);

    mainSizer->Add(NameSizer, 0,  wxEXPAND | wxALL, 5);


//genre field
    wxBoxSizer *genreSizer = new wxBoxSizer(wxHORIZONTAL);
//genre field text
    wxStaticText *genreLabel = new wxStaticText(this, wxID_ANY, "Genre: ");
    genreLabel->SetMinSize(wxSize(50, genreLabel->GetMinSize().y));
    genreSizer->Add(genreLabel);

    genrebox = new wxTextCtrl(this, wxID_ANY);
    genreSizer->Add(genrebox, 1);

    mainSizer->Add(genreSizer, 0,  wxEXPAND | wxALL, 5);

//status field
    wxBoxSizer *statusSizer = new wxBoxSizer(wxHORIZONTAL);
//status field text
    wxStaticText *statusLabel = new wxStaticText(this, wxID_ANY, "Status: ");
    statusLabel->SetMinSize(wxSize(50, statusLabel->GetMinSize().y));
    statusSizer->Add(statusLabel);

    statusbox = new wxTextCtrl(this, wxID_ANY);
    statusSizer->Add(statusbox, 1);

    mainSizer->Add(statusSizer, 0,  wxEXPAND | wxALL, 5);

//button
    wxSizer* buttonSizer = CreateButtonSizer(wxOK | wxCANCEL);
    mainSizer->Add(buttonSizer, 0, wxALIGN_RIGHT | wxALL, 10);

    SetSizer(mainSizer);
    SetMinSize(wxSize(400, 100));
    Fit();
}

bool AddDialog::TransferDataFromWindow()
{
    name = namebox->GetValue();
    genre = genrebox->GetValue();
    status = statusbox->GetValue();
    return true;
}


AddDialog::~AddDialog()
{

}