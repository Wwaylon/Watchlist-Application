#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <filesystem>
#include "itemdata.h"
#include <wx/wx.h>

class CSVHandler
{
public: 
    void exportCSV(std::vector<ItemData> items, std::string path)
    {
        std::ofstream file(path);
        if(!file.is_open())
        {
            wxMessageBox("Error opening file");
            return;
        }

        for(auto it = items.begin(); it != items.end(); it++)
        {
            if(it->name.empty())
            {
                it->name = " ";
            }
            if(it->genre.empty())
            {
                it->genre = " ";
            }
            if(it->status.empty())
            {
                it->status = " ";
            }
            file << it->id << "," << it->name << "," << it->genre << "," << it->status << std::endl;
        }
        file.close();
    }
    std::vector<ItemData> importCSV(std::string path)
    {
        std::vector<ItemData> items;
        std::ifstream file(path);
        if(!file.is_open())
        {
            wxMessageBox("Error opening file");
            return items;
        }
        std::string line;
        while(std::getline(file, line))
        {
            std::stringstream lineStream(line);
            std::string cell;
            std::vector<std::string> values;
            while(std::getline(lineStream, cell, ','))
            {
                values.push_back(cell);
            }
            ItemData item;
            item.id = std::stoi(values[0]);
            item.name = values[1];
            item.genre = values[2];
            item.status = values[3];
            items.push_back(item);
        }
        file.close();
        return items;
    }
};

class XMLHandler
{
public: 
    void exportXML(std::vector<ItemData> items, std::string path)
    {
        std::ofstream file(path);
        if(!file.is_open())
        {
            wxMessageBox("Error opening file");
            return;
        }
        file << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << std::endl;
        file << "<items>" << std::endl;
        for(auto it = items.begin(); it != items.end(); it++)
        {
            if(it->name.empty())
            {
                it->name = " ";
            }
            if(it->genre.empty())
            {
                it->genre = " ";
            }
            if(it->status.empty())
            {
                it->status = " ";
            }
            file << "<item>" << std::endl;
            file << "<id>" << it->id << "</id>" << std::endl;
            file << "<name>" << it->name << "</name>" << std::endl;
            file << "<genre>" << it->genre << "</genre>" << std::endl;
            file << "<status>" << it->status << "</status>" << std::endl;
            file << "</item>" << std::endl;
        }
        file << "</items>" << std::endl;
        file.close();
    }
    std::vector<ItemData> importXML(std::string path)
    {
        std::vector<ItemData> items;
        std::ifstream file(path);
        if(!file.is_open())
        {
            wxMessageBox("Error opening file");
            return items;
        }
        std::string line;
        while(std::getline(file, line))
        {
            std::stringstream lineStream(line);
            std::string cell;
            std::vector<std::string> values;
            while(std::getline(lineStream, cell, ','))
            {
                values.push_back(cell);
            }
            ItemData item;
            item.id = std::stoi(values[0]);
            item.name = values[1];
            item.genre = values[2];
            item.status = values[3];
            items.push_back(item);
        }
        file.close();
        return items;
    }
};

class JSONHandler
{
public: 
    void exportJSON(std::vector<ItemData> items, std::string path)
    {
        std::ofstream file(path);
        if(!file.is_open())
        {
            wxMessageBox("Error opening file");
            return;
        }
        file << "{" << std::endl;
        file << "\"items\": [" << std::endl;
        for(auto it = items.begin(); it != items.end(); it++)
        {
            file << "{" << std::endl;
            file << "\"id\": " << it->id << "," << std::endl;
            file << "\"name\": \"" << it->name << "\"," << std::endl;
            file << "\"genre\": \"" << it->genre << "\"" << std::endl;
            file << "\"status\": \"" << it->status << "\"" << std::endl;
            file << "}" << std::endl;
            if(it != items.end() - 1)
            {
                file << "," << std::endl;
            }
        }
        file << "]" << std::endl;
        file << "}" << std::endl;
        file.close();
    }

};


//XML


class FileHandler//facade 
{
private: 
    std::vector<ItemData> items;
    std::string path;
    CSVHandler *csvH;
    XMLHandler *xmlH;
    JSONHandler *jsonH;
public:
    FileHandler(){
        csvH = new CSVHandler();
        xmlH = new XMLHandler();
        jsonH = new JSONHandler();
    }

    virtual ~FileHandler(){
        delete csvH;
        delete xmlH;
        delete jsonH;
    }

    void exportData(std::vector<ItemData> items, std::string path)
    {
        if(path.find(".csv") != std::string::npos)
        {
            this->csvH->exportCSV(items, path);
        }else if(path.find(".xml") != std::string::npos)
        {
            this->xmlH->exportXML(items, path);
        }else if(path.find(".json") != std::string::npos)
        {
            this->jsonH->exportJSON(items, path);
        }else
        {
            wxMessageBox("Error: Please specify a valid file extension(CSV, JSON, XML)");
        }
    }

    std::vector<ItemData> importData(std::string path)
    {
        if(path.find(".csv") != std::string::npos)
        {
            return this->csvH->importCSV(path);
        }else if(path.find(".xml") != std::string::npos)
        {
            //return this->xmlH->importXML(path);
            wxMessageBox("Not implemented yet");
        }else if(path.find(".json") != std::string::npos)
        {
             wxMessageBox("Not implemented yet");
            //this->items = this->jsonH->importJSON(path);
        }else
        {
            wxMessageBox("Error: Please specify a valid file extension(CSV, JSON, XML)");
        }
        std::vector<ItemData> items;
        return items;
    }
};
