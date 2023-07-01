#pragma once

#include <wx/wx.h>
#include <wx/listctrl.h>

#include <vector>
#include <numeric>
#include <algorithm>

#include "itemdata.h"

class virtualShowListControl : public wxListCtrl
{
public:
    virtualShowListControl(wxWindow *parent, const wxWindowID id, const wxPoint &pos, const wxSize &size)
        : wxListCtrl(parent, id, pos, size, wxLC_REPORT | wxLC_VIRTUAL)
    {
        this->AppendColumn("ID");
        this->AppendColumn("Name");
        this->AppendColumn("Genre");
        this->AppendColumn("Status");

        this->SetColumnWidth(0, 70);
        this->SetColumnWidth(1, 180);
        this->SetColumnWidth(2, 100);
        this->SetColumnWidth(3, 100);

        this->Bind(wxEVT_LIST_COL_CLICK, [this](wxListEvent &evt)
                   {
            auto selectedListIndex = getFirstSelectedIndex();
            long selectedDataIndex;

            if (selectedListIndex != -1)
            {
                selectedDataIndex = this->orderedIndices[selectedListIndex];

                // deselecting old index
                this->SetItemState(selectedListIndex, 0, wxLIST_STATE_SELECTED);
            }

            this->sortByColumn(evt.GetColumn());
            this->RefreshAfterUpdate();

            if (selectedListIndex != -1)
            {
                auto listIndexToSelect = findIndexOfDataIndex(selectedDataIndex);
                this->SetItemState(listIndexToSelect, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
                this->EnsureVisible(listIndexToSelect);
            }

            this->sortAscending = !this->sortAscending; });
    }

    virtual wxString OnGetItemText(long index, long column) const
    {
        ItemData item = items[orderedIndices[index]];

        switch (column)
        {
        case 0:
            return wxString::Format("%d", item.id);
        case 1:
            return item.name;
        case 2:
            return item.genre;
        case 3:
            return item.status;
        default:
            return "";
        }
    }

    void RefreshAfterUpdate()
    {
        this->SetItemCount(orderedIndices.size());
        this->Refresh();
    }

    void setItems(std::vector<ItemData> itemsToSet)
    {
        this->items = itemsToSet;

        this->orderedIndices = std::vector<long>(items.size());
        std::iota(orderedIndices.begin(), orderedIndices.end(), 0);
    }

private:
    bool sortAscending = true;

    std::vector<ItemData> items;
    std::vector<long> orderedIndices;

    void sortByColumn(int column)
    {
        // C++14 generic lambda
        static auto genericCompare = [](auto i1, auto i2, bool ascending)
        {
            return ascending ? i1 < i2 : i1 > i2;
        };

        bool ascending = this->sortAscending;

        std::sort(orderedIndices.begin(), orderedIndices.end(), [this, column, ascending](long index1, long index2)
                  {
            auto i1 = this->items[index1];
            auto i2 = this->items[index2];

            switch (column)
            {
            case 0:
                return genericCompare(i1.id, i2.id, ascending);
            case 1:
                return genericCompare(i1.name, i2.name, ascending);
            case 2:
                return genericCompare(i1.genre, i2.genre, ascending);
            case 3:
                return genericCompare(i1.status, i2.status, ascending);
            default:
                return false;
            } });
    }

    long getFirstSelectedIndex()
    {
        return GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    }

    long findIndexOfDataIndex(long dataIndex)
    {
        return std::find(orderedIndices.begin(), orderedIndices.end(), dataIndex) - orderedIndices.begin();
    }
};