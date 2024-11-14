/**
 * @author Kevin Ye
 * @date 11/07/2024
 * @brief This file contains the implementation of the KitchenStation class, which represents a kitchen station in a virtual bistro simulation.
*/

#include "KitchenStation.hpp"

/**
* Default Constructor
* @post: Initializes an empty kitchen station with default values.
*/
KitchenStation::KitchenStation() {
    station_name_ = "UNKNOWN";
    dishes_ = {};
    ingredients_stock_ = {};
}

/**
* Parameterized Constructor
* @param station_name A string representing the station's name.
* @post: Initializes a kitchen station with the given name.
*/
KitchenStation::KitchenStation(const std::string& station_name) {
    station_name_ = station_name;
    dishes_ = {};
    ingredients_stock_ = {};
}

/**
* Destructor
* @post: Deallocates all dynamically allocated dishes in the
station.
*/
KitchenStation::~KitchenStation() {
    for (int i = 0; i < dishes_.size(); i++) {
        delete dishes_[i];
        dishes_[i] = nullptr;
    }
}

/**
* Retrieves the name of the kitchen station.
* @return: The name of the station.
*/
std::string KitchenStation::getName() const {
    return station_name_;
}

/**
* Sets the name of the kitchen station.
* @param name A string representing the new station name.
* @post: Updates the station's name.
*/
void KitchenStation::setName(const std::string& name) {
    station_name_ = name;
}

/**
* Retrieves the list of dishes assigned to the kitchen station.
* @return A vector of pointers to Dish objects assigned to the station.
*/
std::vector<Dish*> KitchenStation::getDishes() const {
    return dishes_;
}

/**
* Retrieves the ingredient stock available at the kitchen station.
* @return A vector of Ingredient objects representing the station's
ingredient stock.
*/
std::vector<Ingredient> KitchenStation::getIngredientsStock() const {
    return ingredients_stock_;
}

/**
* Assigns a dish to the station.
* @param dish A pointer to a Dish object.
* @post: Adds the dish to the station's list of dishes if not
already present.
* @return: True if the dish was added successfully; false
otherwise.
*/
bool KitchenStation::assignDishToStation(Dish* dish) {
    //Checking if the dish is already present
    for (int i = 0; i < dishes_.size(); i++) {
        if (dishes_[i]->getName() == dish->getName()) {
            return false;
        }
    }

    //Since the dish is not present then it gets added to the station
    dishes_.push_back(dish);
    return true;
}

/**
* Replenishes the station's ingredient stock.
* @param ingredient An Ingredient object.
* @post: Adds the ingredient to the station's stock or updates the
quantity if it already exists.
*/
void KitchenStation::replenishStationIngredients(const Ingredient& ingredient) {
    bool update = false;

    //Checking if the ingredient already exists
    for (int i = 0; i < ingredients_stock_.size(); i++) {
        if (ingredients_stock_[i].name == ingredient.name) {
            //Update the quantity
            ingredients_stock_[i].quantity+=ingredient.quantity;
            update = true;
        }
    }

    //If the ingredient does not exist then it gets added to the ingredients stock
    if (!update)
        ingredients_stock_.push_back(ingredient);
}

/**
* Checks if the station can complete an order for a specific dish.
* @param dish_name A string representing the name of the dish.
* @return: True if the station has the dish assigned and all
required ingredients are in stock; false otherwise.
*/
bool KitchenStation::canCompleteOrder(const std::string& dish_name) {
    bool found = false;
    std::vector<Ingredient> ingre = {};

    //Checking if dish_name exist in dishes
    for (int i = 0; i < dishes_.size(); i++) {
        if (dishes_[i]->getName() == dish_name) {
            //Sets ingre to dish_name ingredients
            ingre = dishes_[i]->getIngredients();
            break;
        }
    }

    //If ingre is empty then dish_name doesn't exist in dishes
    if (ingre.size() == 0)
        return false;

    //Checking dish_name ingredients is in stock
    for (int j = 0; j < ingre.size(); j++) {
        found = false;

        for (int k = 0; k < ingredients_stock_.size(); k++) {
            if (ingre[j].name == ingredients_stock_[k].name) {
                if (ingredients_stock_[k].quantity < ingredients_stock_[k].required_quantity)
                    return false;

                found = true;
            }
        }

        //Checking if dish_name ingredients exists in ingredients_stock
        if (!found)
            return false; //dish_name did not exist
    }

    return true;
}

/**
* Prepares a dish if possible.
* @param dish_name A string representing the name of the dish.
* @post: If the dish can be prepared, reduce the quantities of the
used ingredients accordingly. If the stock ingredient is depleted to
0, remove the ingredient from the Kitchen Station.
* @return: True if the dish was prepared successfully; false
otherwise.
*/
bool KitchenStation::prepareDish(const std::string& dish_name) {
    //Early check if dish_name can be created
    if (!canCompleteOrder(dish_name)) 
        return false;

    std::vector<Ingredient> ingre = {};

    //Gets dish_name ingredients and storing them in ingre
    for (int i = 0; i < dishes_.size(); i++) {
        if (dishes_[i]->getName() == dish_name)
            ingre = dishes_[i]->getIngredients();
    }

    //Updates the ingredients stock quantity
    for (int j = 0; j < ingre.size(); j++) {
        for (int k = 0; k < ingredients_stock_.size(); k++) {
            if (ingre[j].name == ingredients_stock_[k].name) {
                ingredients_stock_[k].quantity-=ingredients_stock_[k].required_quantity;

                //Remove the ingredient from the stock if the quantity is 0
                if (ingredients_stock_[k].quantity == 0)
                    ingredients_stock_.erase(ingredients_stock_.begin() + k);
            }
        }
    }

    return true;
}

// void KitchenStation::setIngredient(const std::vector<Ingredient> i) {
//     ingredients_stock_ = i;
// }

// std::vector<Ingredient> KitchenStation::getIngredient() {
//     return ingredients_stock_;
// }

// void KitchenStation::setDish(const std::vector<Dish*> d) {
//     dishes_ = d;
// }

// std::vector<Dish*> KitchenStation::getDish() {
//     return dishes_;
// }