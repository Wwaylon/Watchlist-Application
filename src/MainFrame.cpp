#include "MainFrame.h"

BEGIN_EVENT_TABLE(MainFrame, wxFrame)
    EVT_MENU(wxID_EXIT, MainFrame::OnQuit)
    EVT_MENU(wxID_ABOUT, MainFrame::OnAbout)
END_EVENT_TABLE()



MainFrame::MainFrame(const wxString &title, const wxPoint &pos, const wxSize &size)
    : wxFrame(NULL, wxID_ANY, title, pos, size), useVirtual(true), virtualListView(nullptr), 
    AddButton(nullptr), FilterButton(nullptr), UnfilterButton(nullptr), EditButton(nullptr),
    DeleteButton(nullptr), mode("show"), buttonPanel(new wxPanel(this)), SearchContext(new SearchEntriesContext(nullptr)),
    ImportButton(nullptr), ExportButton(nullptr), fileHandler(new FileHandler), items(new Data), UndoButton(nullptr), id(0)
{
    //items = readItemsFromCsv();
    setupLayout();
}
/*
std::vector<ItemData> MainFrame::readItemsFromCsv()
{
    std::ifstream stream(std::string("/aapl-1d.csv")); // should be copied by CMake to the bin directory

    // ignore header
    stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::vector<ItemData> items;

    while (stream)
    {
        auto item = ItemData::fromCsvLine(stream);
        if (!item.name.empty())
        {
            items.push_back(item);
        }
    }

    return items;
}*/

void MainFrame::populateVirtualListView()
{
    virtualListView->setItems(items->getItems());
    virtualListView->RefreshAfterUpdate();
}

void MainFrame::populateVirtualFilterListView()
{
    virtualListView->setItems(items->getFilteredItems());
    virtualListView->RefreshAfterUpdate();
}

void MainFrame::AddEntry(ItemData data)
{
    SaveMomento();
    id++;
    items->addItem(data);
    populateVirtualListView();
}

void MainFrame::DeleteEntry(ItemData criteria)
{
    //if(SearchContext != nullptr) { delete SearchContext; }
    SearchContext->set_strategy(new SearchById());
    int index = SearchContext->search(items->getItems(), criteria); // find index of item to delete
    if(index != -1) // if found
    {
        SaveMomento();
        // remove item from vector
        items->removeItemByIndex(index);
        populateVirtualListView();
        wxMessageBox(wxString::Format("You Successfully Deleted Entry with ID %d", criteria.id));
    }
    else
    {
        wxMessageBox(wxString::Format("ID %d not found", criteria.id));
    }
}

void MainFrame::EditEntry(ItemData criteria)
{
    //if(SearchContext != nullptr) { delete SearchContext; }
    SearchContext->set_strategy(new SearchById); //search using search by name strategy
    int index = SearchContext->search(items->getItems(), criteria); // find index of item to delete
    if(index != -1) // if found
    {
        SaveMomento();
        // remove item from vector
        //items->updateItem(criteria);
        std::vector<ItemData> itemsdata = items->getItems();
        if(criteria.name != "")
        {
            itemsdata[index].name = criteria.name;
        }
        if(criteria.genre != "")
        {
            itemsdata[index].genre = criteria.genre;
        }
        if(criteria.status != "")
        {
            itemsdata[index].status = criteria.status;
        }
        items->setItems(itemsdata);
        populateVirtualListView();
        wxMessageBox(wxString::Format("You Successfully Edited Entry at ID %d", criteria.id));
    }
    else
    {
        wxMessageBox(wxString::Format("ID %d not found", criteria.id));
    }
}

void MainFrame::SearchList(ItemData criteria)
{
    SaveMomento();
    items->CopyItems();
    //items->getFilteredItems().clear();
    items->clearFilteredItems();
    int index;
    /*
    if(!(criteria.id >= 0))
    {
        if(criteria.id == -1)
        {
            SearchContext->set_strategy(new SearchByName());
            do
            {
                index = SearchContext->search(items->getTemp(), criteria); // find index of item to delete
                if(index != -1) // if found
                {
                    //filteredItems.push_back(temp[index]);
                    items->addFilteredItem(items->getTemp()[index]);
                    //temp.erase(temp.begin() + index);
                    items->removeTempItemByIndex(index);
                }     
            } while (index != -1);
        }else
        {
            items->CopyItems();
            SearchContext->set_strategy(new SearchByGenre); //search using search by genre strategy
            do
            {
                index = SearchContext->search(items->getTemp(), criteria); // find index of item to delete
                if(index != -1) // if found
                {
                    //filteredItems.push_back(temp[index]);
                    items->addFilteredItem(items->getTemp()[index]);
                    //temp.erase(temp.begin() + index);
                    items->removeTempItemByIndex(index);
                }     
            } while (index != -1);
            items->CopyItems();
            SearchContext->set_strategy(new SearchByStatus); //search using search by status strategy
            do
            {
                index = SearchContext->search(items->getTemp(), criteria); // find index of item to delete
                if(index != -1) // if found
                {
                    //filteredItems.push_back(temp[index]);
                    items->addFilteredItem(items->getTemp()[index]);
                    //temp.erase(temp.begin() + index);
                    items->removeTempItemByIndex(index);
                }     
            } while (index != -1);
        }
    }else
    {
        SearchContext->set_strategy(new SearchById); //search using search by id strategy
        index = SearchContext->search(items->getItems(), criteria); 
        if(index != -1) // if found
        {
            //filteredItems.push_back(items[index]);
            items->addFilteredItem(items->getItems()[index]);
        }

    }*/

    if(criteria.id == -1)
    {
        SearchContext->set_strategy(new SearchByName); //search using search by name strategy
        do
        {
            index = SearchContext->search(items->getTemp(), criteria); // find index of item to delete
            if(index != -1) // if found
            {
                //filteredItems.push_back(temp[index]);
                items->addFilteredItem(items->getTemp()[index]);
                //temp.erase(temp.begin() + index);
                items->removeTempItemByIndex(index);
            }     
        } while (index != -1);
    }
    else if(criteria.id == -2)
    {
        SearchContext->set_strategy(new SearchByGenre); //search using search by genre strategy
        do
        {
            index = SearchContext->search(items->getTemp(), criteria); // find index of item to delete
            if(index != -1) // if found
            {
                //filteredItems.push_back(temp[index]);
                items->addFilteredItem(items->getTemp()[index]);
                //temp.erase(temp.begin() + index);
                items->removeTempItemByIndex(index);
            }     
        } while (index != -1);
    } else if (criteria.id == -3) 
    {
        SearchContext->set_strategy(new SearchByStatus); //search using search by status strategy
        do
        {
            index = SearchContext->search(items->getTemp(), criteria); // find index of item to delete
            if(index != -1) // if found
            {
                //filteredItems.push_back(temp[index]);
                items->addFilteredItem(items->getTemp()[index]);
                //temp.erase(temp.begin() + index);
                items->removeTempItemByIndex(index);
            }     
        } while (index != -1);
    } else 
    {
        SearchContext->set_strategy(new SearchById); //search using search by id strategy
        index = SearchContext->search(items->getItems(), criteria); 
        if(index != -1) // if found
        {
            //filteredItems.push_back(items[index]);
            items->addFilteredItem(items->getItems()[index]);
        }
    }

    populateVirtualFilterListView();
}

void MainFrame::Undo()
{
    if(undoStack.size() > 0)
    {
        items->setItems(undoStack.back()->items);
        undoStack.pop_back();
        populateVirtualListView();
    }
}

void MainFrame::SaveMomento()
{
    undoStack.push_back(new Momento(items->getItems()));
}

void MainFrame::setupLayout()
{
    wxMenuBar *menuBar = new wxMenuBar;
    wxMenu *appMenu = new wxMenu;
    wxMenu *dataMenu = new wxMenu;
    menuBar->Append(appMenu, "&Application");
    menuBar->Append(dataMenu, "&Data");
        

    wxMenuItem *ExportItem = new wxMenuItem(appMenu, wxID_ANY, "&Export");
    dataMenu->Append(ExportItem);
    Bind(wxEVT_MENU, &MainFrame::OnExport, this, ExportItem->GetId());

    wxMenuItem *ImportItem = new wxMenuItem(appMenu, wxID_ANY, "&Import");
    dataMenu->Append(ImportItem);
    Bind(wxEVT_MENU, &MainFrame::OnImport, this, ImportItem->GetId());

    dataMenu->AppendSeparator();

    wxMenuItem *AddItem = new wxMenuItem(appMenu, wxID_ANY, "&Add Entry");
    dataMenu->Append(AddItem);
    Bind(wxEVT_MENU, &MainFrame::OnAdd, this, AddItem->GetId());

    wxMenuItem *DeleteItem = new wxMenuItem(appMenu, wxID_ANY, "&Delete Entry");
    dataMenu->Append(DeleteItem);
    Bind(wxEVT_MENU, &MainFrame::OnDelete, this, DeleteItem->GetId());

    wxMenuItem *EditItem = new wxMenuItem(appMenu, wxID_ANY, "&Edit Entry");
    dataMenu->Append(EditItem);
    Bind(wxEVT_MENU, &MainFrame::OnEdit, this, EditItem->GetId());

    wxMenuItem *FilterItem = new wxMenuItem(appMenu, wxID_ANY, "&Filter List");
    dataMenu->Append(FilterItem);
    Bind(wxEVT_MENU, &MainFrame::OnFilter, this, FilterItem->GetId());

    dataMenu->AppendSeparator();

    wxMenuItem *UnfilterItem = new wxMenuItem(appMenu, wxID_ANY, "&Unfilter List");
    dataMenu->Append(UnfilterItem);
    Bind(wxEVT_MENU, &MainFrame::OnUnfilter, this, UnfilterItem->GetId());


    //seperator
    appMenu->AppendSeparator();

    //about wxmenuitem
    wxMenuItem *aboutitem = new wxMenuItem(appMenu, wxID_ABOUT);
    appMenu->Append(aboutitem);

    //create wxmenuitem example
    wxMenuItem *quitItem = new wxMenuItem(appMenu, wxID_EXIT);
    appMenu->Append(quitItem);

    SetMenuBar(menuBar);


//////////////////

    addVirtualList();
    populateVirtualListView();
    
    AddButton = new wxButton(buttonPanel, wxID_ANY, "Add");
    DeleteButton = new wxButton(buttonPanel, wxID_ANY, "Delete");
    EditButton = new wxButton(buttonPanel, wxID_ANY, "Edit");
    FilterButton = new wxButton(buttonPanel, wxID_ANY, "Filter");
    UnfilterButton = new wxButton(buttonPanel, wxID_ANY, "Unfilter");
    ImportButton = new wxButton(buttonPanel, wxID_ANY, "Import");
    ExportButton = new wxButton(buttonPanel, wxID_ANY, "Export");
    UndoButton = new wxButton(buttonPanel, wxID_ANY, "Undo");

    auto sizerVert = new wxBoxSizer(wxVERTICAL);
    auto buttonPanelSizer = new wxBoxSizer(wxVERTICAL);
    auto buttonSizerHorizontal = new wxBoxSizer(wxHORIZONTAL);
    sizerVert->Add(virtualListView, 1, wxALL | wxEXPAND, 0);
    buttonSizerHorizontal->Add(AddButton, 0, wxALIGN_LEFT | wxLEFT | wxTOP | wxBOTTOM, 5);
    buttonSizerHorizontal->Add(DeleteButton, 0, wxALIGN_LEFT | wxLEFT | wxTOP | wxBOTTOM, 5);
    buttonSizerHorizontal->Add(EditButton, 0, wxALIGN_LEFT | wxLEFT | wxTOP | wxBOTTOM, 5);
    buttonSizerHorizontal->Add(FilterButton, 0, wxALIGN_LEFT | wxLEFT | wxTOP | wxBOTTOM, 5);
    buttonSizerHorizontal->Add(UnfilterButton, 0, wxALIGN_LEFT | wxLEFT | wxTOP | wxBOTTOM, 5);
    buttonSizerHorizontal->Add(ImportButton, 0, wxALIGN_LEFT | wxLEFT | wxTOP | wxBOTTOM, 5);
    buttonSizerHorizontal->Add(ExportButton, 0, wxALIGN_LEFT | wxLEFT | wxTOP | wxBOTTOM, 5);
    buttonSizerHorizontal->Add(UndoButton, 0, wxALIGN_LEFT | wxLEFT | wxTOP | wxBOTTOM, 5);
    buttonPanelSizer->Add(buttonSizerHorizontal);

    AddButton->Bind(wxEVT_BUTTON, &MainFrame::OnAdd, this);
    DeleteButton->Bind(wxEVT_BUTTON, &MainFrame::OnDelete, this);
    EditButton->Bind(wxEVT_BUTTON, &MainFrame::OnEdit, this);
    FilterButton->Bind(wxEVT_BUTTON, &MainFrame::OnFilter, this);
    UnfilterButton->Bind(wxEVT_BUTTON, &MainFrame::OnUnfilter, this);
    ImportButton->Bind(wxEVT_BUTTON, &MainFrame::OnImport, this);
    ExportButton->Bind(wxEVT_BUTTON, &MainFrame::OnExport, this);
    UndoButton->Bind(wxEVT_BUTTON, &MainFrame::OnUndo, this);


    buttonPanel->SetSizer(buttonPanelSizer);
    sizerVert->Add(buttonPanel, 1, wxALL | wxEXPAND, 0);
    this->SetSizer(sizerVert);
    //buttonPanel->Disable();
    this->Layout();

}
void MainFrame::addVirtualList()
{
    virtualListView = new virtualShowListControl(this, wxID_ANY, wxDefaultPosition, wxSize(800, 500));
}


void MainFrame::OnQuit(wxCommandEvent& event)
{
    Close(true);
}

void MainFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox(wxString::Format("This is a watchlist application"));
}


void MainFrame::OnAdd(wxCommandEvent& event)
{
    AddDialog dlg(this, wxID_ANY, "Add");
    if(dlg.ShowModal() == wxID_OK)
    {
        //wxMessageBox(wxString::Format("hello"));
        ItemData data;
        data.name = dlg.getName();
        data.genre = dlg.getGenre();
        data.status = dlg.getStatus();
        data.id = this->id;
        AddEntry(data);
    }
}

void MainFrame::OnDelete(wxCommandEvent& event)
{
    DeleteDialog dlg(this, wxID_ANY, "Delete");
    if(dlg.ShowModal() == wxID_OK)
    {
        //wxMessageBox(wxString::Format("hello"));
        ItemData criteria;
        criteria.id = std::stoi(dlg.getId().ToStdString());
        DeleteEntry(criteria);
    }
}

void MainFrame::OnEdit(wxCommandEvent& event)
{
    EditDialog dlg(this, wxID_ANY, "Edit");
    if(dlg.ShowModal() == wxID_OK)
    {
        //wxMessageBox(wxString::Format("hello"));
        ItemData criteria;
        //criteria.id = std::stoi(dlg.getId().ToStdString());
        criteria.id = std::stoi(dlg.getId().ToStdString());
        criteria.name = dlg.getName();
        criteria.genre = dlg.getGenre();
        criteria.status = dlg.getStatus();
        EditEntry(criteria);
    }
}

void MainFrame::OnFilter(wxCommandEvent& event)
{
    SearchDialog dlg(this, wxID_ANY, "Filter");
    if(dlg.ShowModal() == wxID_OK)
    {
        //wxMessageBox(wxString::Format("hello"));
        ItemData criteria;
        //criteria.id = std::stoi(dlg.getId().ToStdString());
        criteria.id = std::stoi(dlg.getId().ToStdString());
        criteria.name = dlg.getName();
        criteria.genre = dlg.getGenre();
        criteria.status = dlg.getStatus();
        std::cout << criteria.id << std::endl;
        SearchList(criteria);
    }
}

void MainFrame::OnUnfilter(wxCommandEvent& event)
{
    populateVirtualListView();
}

void MainFrame::OnExport(wxCommandEvent& event)
{
    //wxMessageBox(wxString::Format("Export"));
    ExportItems();
}

void MainFrame::OnImport(wxCommandEvent& event)
{
    wxMessageBox(wxString::Format("Import"));
    ImportItems();
}

void MainFrame::OnUndo(wxCommandEvent& event)
{
    //wxMessageBox(wxString::Format("Undo"));
    Undo();
}

void MainFrame::ExportItems()
{
    SaveMomento();
    wxFileDialog saveFileDialog(this, _("Save file"), "", "", "CSV files (*.csv)|*.csv| JSON files (*.json)|*.json | XML files (*.xml)|*.xml", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
    if(saveFileDialog.ShowModal() == wxID_CANCEL)
        return;
    std::string path = saveFileDialog.GetPath().ToStdString();
    fileHandler->exportData(items->getItems(), path);
}


void MainFrame::ImportItems()
{
    SaveMomento();
    wxFileDialog saveFileDialog(this, _("Select file"), "", "", "CSV files (*.csv)|*.csv| JSON files (*.json)|*.json| XML files (*.xml)|*.xml", wxFD_OPEN |wxFD_FILE_MUST_EXIST);
    if(saveFileDialog.ShowModal() == wxID_CANCEL)
        return;
    std::string path = saveFileDialog.GetPath().ToStdString();
    items->setItems(fileHandler->importData(path));
    populateVirtualListView();
    //populateVirtualListView();
    //search items for largest id and set it as the new id
    std::vector<int> ids;
    for(auto item : items->getItems())
    {
        ids.push_back(item.id);
    }
    int maxId=*std::max_element(ids.begin(), ids.end());
    id = maxId+1;
}

