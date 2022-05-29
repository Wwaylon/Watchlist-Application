#pragma once
#include <vector>
#include "itemdata.h"

class Momento
{
public:
    Momento(std::vector<ItemData> items)
    {
        this->items = items;
    }
    std::vector<ItemData> items;
};


class Data
{
public:
    void setItems(std::vector<ItemData> items)
    {
        this->items = items;
    }
    
    void addItem(ItemData item) {
        items.push_back(item);
    }
    void removeItem(ItemData item){
        for(int i = 0; i < items.size(); i++){
            if(items[i].id == item.id){
                items.erase(items.begin() + i);
            }
        }
    }

    void removeItemByIndex(int index){
        items.erase(items.begin() + index);
    }

    void updateItem(ItemData item){
        for(int i = 0; i < items.size(); i++){
            if(items[i].id == item.id){
                items[i] = item;
            }
        }
    }
    std::vector<ItemData> getItems()
    {
        return items;
    }
    //deep copy
    std::vector<ItemData> getFilteredItems()
    {
        return filteredItems;
    }

    void addFilteredItem(ItemData item)
    {
        filteredItems.push_back(item);
    }

    void removeFilteredItem(ItemData item)
    {
        for(int i = 0; i < filteredItems.size(); i++){
            if(filteredItems[i].id == item.id){
                filteredItems.erase(filteredItems.begin() + i);
            }
        }
    }

    void removeFilteredItemByIndex(int index)
    {
        filteredItems.erase(filteredItems.begin() + index);
    }


    std::vector<ItemData> getTemp()
    {
        return temp;
    }

    void addTempItem(ItemData item) {
        temp.push_back(item);
    }

    void removeTempItemByIndex(int index)
    {
        temp.erase(temp.begin() + index);
    }

    void clearFilteredItems()
    {
        filteredItems.clear();
    }
    void  clearItems()
    {
        items.clear();
    }
    void clearTemp()
    {
        temp.clear();
    }

    void CopyItems()
    {
        temp.clear();
        for(auto it = items.begin(); it != items.end(); it++)
        {
            temp.push_back(*it);
        }
    }

    Momento* createMomento()
    {
        return new Momento(items);
    }
    
    void restoreMomento(Momento* momento)
    {
        items = momento->items;
    }

private:
    std::vector<ItemData> items;
    std::vector<ItemData> filteredItems;
    std::vector<ItemData> temp;
};