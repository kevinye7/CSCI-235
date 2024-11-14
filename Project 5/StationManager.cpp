/**
 * @author Kevin Ye
 * @date 11/07/2024
 * @brief This file contains the implementation of the StationManager class, which represents a station manager in a virtual bistro simulation.
*/

#include "StationManager.hpp"

/**
* Default Constructor
* @post: Initializes an empty station manager.
*/
StationManager::StationManager() : LinkedList<KitchenStation*>() {
}

/**
* Destructor
* @post: Deallocates all kitchen stations and clears the list.
*/
StationManager::~StationManager() {
    for (int i = 0; i < getLength(); i++) {
        delete getEntry(i);
    }
    clear();
}

/**
* Adds a new station to the station manager.
* @param station A pointer to a KitchenStation object.
* @post: Inserts the station into the linked list.
* @return: True if the station was successfully added; false
otherwise.
*/
bool StationManager::addStation(KitchenStation* station) {
    return insert(getLength(), station);
}

/**
* Removes a station from the station manager by name.
* @param station_name A string representing the station's name.
* @post: Removes the station from the list and deallocates it.
* @return: True if the station was found and removed; false
otherwise.
*/
bool StationManager::removeStation(const std::string& station_name) {
    for (int i = 0; i < getLength(); i++) {
        //Storing the data into station
        KitchenStation* station = getEntry(i); 

        if (station->getName() == station_name) {
            delete getEntry(i);
            remove(i);
            return true;
        }
    }

    return false;
}

/**
* Finds a station in the station manager by name.
* @param station_name A string representing the station's name.
* @return: A pointer to the KitchenStation if found; nullptr
otherwise.
*/
KitchenStation* StationManager::findStation(const std::string& station_name) {
    for (int i = 0; i < getLength(); i++) {
        //Storing the data into station
        KitchenStation* station = getEntry(i);

        if (station->getName() == station_name)
            return station;
    }

    return nullptr;
}

/**
* Moves a specified station to the front of the station manager
list.
* @param station_name A string representing the station's name.
* @post: The station is moved to the front of the list if it
exists.
* @return: True if the station was found and moved; false
otherwise.
*/
bool StationManager::moveStationToFront(const std::string& station_name) {
    for (int i = 0; i < getLength(); i++) {
        //Storing the data into station
        KitchenStation* station = getEntry(i);

        if (station->getName() == station_name) {
            remove(i);
            insert(0, station);
            return true;
        }
    }

    return false;
}

/**
* Merges the dishes and ingredients of two specified stations.
* @param station_name1 The name of the first station.
* @param station_name2 The name of the second station.
* @post: The second station is removed from the list, and its
contents are added to the first station.
* @return: True if both stations were found and merged; false
otherwise.
*/
bool StationManager::mergeStations(const std::string& station_name1, const std::string& station_name2) {
    //Storing the data into their own pointer to KitchenStation
    KitchenStation* station1 = findStation(station_name1);
    KitchenStation* station2 = findStation(station_name2);

    //If both station_name1 and station_name2 are found
    if (station1 != nullptr && station2 != nullptr) { 
        //Removing the second station from the list
        for (int i = 0; i < getLength(); i++) {
            if (station2->getName() == getEntry(i)->getName())
                remove(i);
        }

        std::vector<Dish*> dishes = station2->getDishes();

        //Adding station_name2 dishes into station_name1
        for (int i = 0; i < dishes.size(); i++) 
            station1->assignDishToStation(dishes[i]);
        
        std::vector<Ingredient> ingre = station2->getIngredientsStock();
        
        //Adding station_name2 ingredients into station_name1
        for (int i = 0; i < ingre.size(); i++) 
            station1->replenishStationIngredients(ingre[i]);
        
        return true;
    }
    
    return false;
}

/**
* Assigns a dish to a specific station.
* @param station_name A string representing the station's name.
* @param dish A pointer to a Dish object.
* @post: Assigns the dish to the specified station.
* @return: True if the station was found and the dish was assigned;
false otherwise.
*/
bool StationManager::assignDishToStation(const std::string& station_name, Dish* dish) {
    //Storing the data into station
    KitchenStation* station = findStation(station_name);
    
    //Checking if the station exists before adding dish to station
    if (station != nullptr) {
        station->assignDishToStation(dish);
        return true;
    }

    return false;
}

/**
* Replenishes an ingredient at a specific station.
* @param station_name A string representing the station's name.
* @param ingredient An Ingredient object.
* @post: Replenishes the ingredient stock at the specified station.
* @return: True if the station was found and the ingredient was
replenished; false otherwise.
*/
bool StationManager::replenishIngredientAtStation(const std::string& station_name, const Ingredient& ingredient) {
    //Storing the data into station
    KitchenStation* station = findStation(station_name);

    //Checking if the station exists before adding ingredient to station
    if (station != nullptr) {
        station->replenishStationIngredients(ingredient);
        return true;
    }

    return false;
}

/**
* Checks if any station in the station manager can complete an
order for a specific dish.
* @param dish_name A string representing the name of the dish.
* @return: True if any station can complete the order; false
otherwise.
*/
bool StationManager::canCompleteOrder(const std::string& dish_name) {
    for (int i = 0; i < getLength(); i++) {
        //Storing the data into station
        KitchenStation* station = getEntry(i);

        //Return true once the first station is found that can complete the order
        if (station->canCompleteOrder(dish_name))
            return true;
    }

    return false;
}

/**
* Prepares a dish at a specific station if possible.
* @param station_name A string representing the station's name.
* @param dish_name A string representing the name of the dish.
* @post: If the dish can be prepared, reduces the quantities of the
used ingredients at the station.
* @return: True if the dish was prepared successfully; false
otherwise.
*/
bool StationManager::prepareDishAtStation(const std::string& station_name, const std::string& dish_name_) {
    //Storing the data into station
    KitchenStation* station = findStation(station_name);

    //Checking if station exists
    if (station != nullptr)
        return station->prepareDish(dish_name_);

    return true;
}