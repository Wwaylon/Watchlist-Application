#include "searchDialog.h"

BEGIN_EVENT_TABLE(SearchDialog, wxDialog)
    EVT_UPDATE_UI(wxID_OK, SearchDialog::onUpdateOkButton)
END_EVENT_TABLE()

SearchDialog::SearchDialog(wxWindow *parent, wxWindowID id,
        const wxString &title,
        const wxPoint &pos,
        const wxSize &size,
        long style,
        const wxString &name): wxDialog(parent, id, title, pos, size, style, name)
{
    wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);

//id field
    wxBoxSizer *idSizer = new wxBoxSizer(wxHORIZONTAL);
//id field text
    wxStaticText *idLabel = new wxStaticText(this, wxID_ANY, "id: ");
    idLabel->SetMinSize(wxSize(50, idLabel->GetMinSize().y));
    idSizer->Add(idLabel);

    idbox = new wxTextCtrl(this, wxID_ANY);
    idSizer->Add(idbox, 1);

    mainSizer->Add(idSizer, 0,  wxEXPAND | wxALL, 5);


//name field
    wxBoxSizer *nameSizer = new wxBoxSizer(wxHORIZONTAL);
//name field text
    wxStaticText *nameLabel = new wxStaticText(this, wxID_ANY, "name: ");
    nameLabel->SetMinSize(wxSize(50, nameLabel->GetMinSize().y));
    nameSizer->Add(nameLabel);

    namebox = new wxTextCtrl(this, wxID_ANY);
    nameSizer->Add(namebox, 1);

    mainSizer->Add(nameSizer, 0,  wxEXPAND | wxALL, 5);


//genre field
    wxBoxSizer *genreSizer = new wxBoxSizer(wxHORIZONTAL);
//genre field text
    wxStaticText *genreLabel = new wxStaticText(this, wxID_ANY, "genre: ");
    genreLabel->SetMinSize(wxSize(50, genreLabel->GetMinSize().y));
    genreSizer->Add(genreLabel);

    genrebox = new wxTextCtrl(this, wxID_ANY);
    genreSizer->Add(genrebox, 1);

    mainSizer->Add(genreSizer, 0,  wxEXPAND | wxALL, 5);

//status field
    wxBoxSizer *statusSizer = new wxBoxSizer(wxHORIZONTAL);
//status field text
    wxStaticText *statusLabel = new wxStaticText(this, wxID_ANY, "status: ");
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

bool SearchDialog::TransferDataFromWindow()
{
    // if(!idbox->GetValue().IsEmpty())
    // {
    //     id = idbox->GetValue();
    // }else
    // {
    //     id = "-99999";
    // }

    if(!idbox->GetValue().IsEmpty())
    {
        id = idbox->GetValue();
    }else if(!namebox->GetValue().IsEmpty())
    {
        id = "-1";
        name = namebox->GetValue();
    } else if(!genrebox->GetValue().IsEmpty())
    {
        id = "-2";
        genre = genrebox->GetValue();
    } 
    else if (!statusbox->GetValue().IsEmpty())
    {
        id = "-3";
        status = statusbox->GetValue();
    }

    return true;
}


void SearchDialog::onUpdateOkButton(wxUpdateUIEvent& event)
{
    event.Enable(false);

    if(idbox->GetValue().empty() || idbox->GetValue().IsNumber())
    {
        event.Enable(true);
    }
}

SearchDialog::~SearchDialog()
{

}