
#pragma once
#include <wx/wx.h>
#include <wx/listctrl.h>
#include <wx/stopwatch.h>

#include <string>
#include <vector>
#include <unordered_set>

#include <fstream>
#include <filesystem>
#include <stdlib.h>
#include <time.h>  

#include "itemdata.h"
#include "virtualShowListControl.h"
#include "addDialog.h"
#include "deleteDialog.h"
#include "search.h"
#include "editDialog.h"
#include "searchDialog.h"
#include "fileHandler.h"
#include "data.h"
#include <algorithm>

class MainFrame : public wxFrame
{
public:
    MainFrame(const wxString &title, const wxPoint &pos, const wxSize &size);
    void OnAbout(wxCommandEvent& event);
    void OnQuit(wxCommandEvent& event);
    void OnStartList(wxCommandEvent& event);
    void OnAdd(wxCommandEvent& event);
    void OnDelete(wxCommandEvent& event);
    void OnEdit(wxCommandEvent& event);
    void OnFilter(wxCommandEvent& event);
    void OnUnfilter(wxCommandEvent& event);
    void OnExport(wxCommandEvent& event);
    void OnImport(wxCommandEvent& event);
    void OnUndo(wxCommandEvent& event);

    DECLARE_EVENT_TABLE()

private:
    int id;
    SearchEntriesContext *SearchContext;
    FileHandler *fileHandler;

    virtualShowListControl *virtualListView;

    wxPanel *buttonPanel;

    std::string mode;

    wxButton *AddButton;
    wxButton *FilterButton;
    wxButton *EditButton;
    wxButton *DeleteButton;
    wxButton *UnfilterButton;
    wxButton *ExportButton;
    wxButton *ImportButton;
    wxButton *UndoButton;

    //std::vector<ItemData> readItemsFromCsv();
    //std::vector<ItemData> items;
    //std::vector<ItemData> filteredItems;
    //std::vector<ItemData> temp;

    std::vector<Momento *> undoStack;
    Data *items;

    void populateVirtualListView();
    void populateVirtualFilterListView();
    void setupLayout();
    void addVirtualList();
    void AddEntry(ItemData data);
    void DeleteEntry(ItemData data);
    void EditEntry(ItemData data);
    void SearchList(ItemData data);
    void ExportItems();
    void ImportItems();
    void Undo();
    void SaveMomento();

    

    bool useVirtual;
};


