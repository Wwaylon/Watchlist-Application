#pragma once
#include <string>
#include <vector>
#include <itemdata.h>

//resource  https://refactoring.guru/design-patterns/strategy/cpp/example#example-0--main-cc

class SearchStrategy
{
public:
    virtual ~SearchStrategy() {}
    virtual int search(std::vector<ItemData> vec, ItemData criteria) const = 0;
};

class SearchById : public SearchStrategy
{
public:
    int search(std::vector<ItemData> vec, ItemData criteria) const override
    {
        int index = 0;
        for (int i = 0; i < vec.size(); i++)
        {
            if (vec[i].id == criteria.id)
            {
                index = i;
                return index;
            }
        }
        return -1;
    }
};

class SearchByName : public SearchStrategy
{
public:
    int search(std::vector<ItemData> vec, ItemData criteria) const override
    {
        int index = 0;
        for (int i = 0; i < vec.size(); i++)
        {
            if (vec[i].name == criteria.name)
            {
                index = i;
                return index;
            }
        }
        return -1;
    }
};

class SearchByGenre : public SearchStrategy
{
public:
    int search(std::vector<ItemData> vec, ItemData criteria) const override
    {
        int index = 0;
        for (int i = 0; i < vec.size(); i++)
        {
            if (vec[i].genre == criteria.genre)
            {
                index = i;
                return index; //return the index found
            }
        }
        return -1; // return -1 if not found
    }
};

class SearchByStatus : public SearchStrategy
{
public:
    int search(std::vector<ItemData> vec, ItemData criteria) const override
    {
        int index = 0;
        for (int i = 0; i < vec.size(); i++)
        {
            if (vec[i].status == criteria.status)
            {
                index = i;
                return index; //return the index found
            }
        }
        return -1; // return -1 if not found
    }
};

class SearchEntriesContext // context
{
    public:
        SearchEntriesContext(SearchStrategy *strategy = nullptr) : strategy_(strategy)
        {

        }
        ~SearchEntriesContext()
        {
            delete this->strategy_;
        }

        void set_strategy(SearchStrategy *strategy)
        {
            delete this->strategy_;
            this->strategy_ = strategy;
        }

        int search(std::vector<ItemData> vec, ItemData criteria) const
        {
            return this->strategy_->search(vec, criteria);
        }

        //static int searchName(std::vector<ItemData> vec, std::string inputname);
    private:
    SearchStrategy *strategy_;
};
