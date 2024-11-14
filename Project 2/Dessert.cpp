/**
* @file Dessert.cpp
* @brief This file contains the implementation of the Dessert class, which represents a dessert in a virtual bistro simulation.
* 
* The Dessert class includes methods to manage and present the details of a dessert, including flavor profile, sweetness level, and contains nuts.
* The implementation ensures that the dessert name is validated and correctly formatted.
* 
* @date 9/29/2024
* @author Kevin Ye
*/

#include "Dessert.hpp"
#include <iostream>

/**
* Default constructor.
* Initializes all private members with default values.
*/
Dessert::Dessert() {
   Dish();
   flavor_profile_ = SWEET; 
   sweetness_level_ = 0; 
   contains_nuts_ = false;
}

/**
* Parameterized constructor.
* @param name The name of the dessert.
* @param ingredients The ingredients used in the dessert.
* @param prep_time The preparation time in minutes.
* @param price The price of the dessert.
* @param cuisine_type The cuisine type of the dessert.
* @param flavor_profile The flavor profile of the dessert.
* @param sweetness_level The sweetness level of the dessert.
* @param contains_nuts Flag indicating if the dessert contains nuts.
*/
Dessert::Dessert(const std::string& name, const std::vector<std::string>& ingredients, int prep_time, double price, CuisineType cuisine_type, FlavorProfile flavor_profile, int sweetness_level, bool contains_nuts) : Dish(name, ingredients, prep_time, price, cuisine_type) {
   flavor_profile_ = flavor_profile; 
   sweetness_level_ = sweetness_level; 
   contains_nuts_ = contains_nuts;
}

/**
* Sets the flavor profile of the dessert.
* @param flavor_profile The new flavor profile.
* @post Sets the private member `flavor_profile_` to the value of the parameter.
*/
void Dessert::setFlavorProfile(const FlavorProfile& flavor_profile) {
   flavor_profile_ = flavor_profile;
}

/**
* @return The flavor profile of the dessert (as an enum).
*/
Dessert::FlavorProfile Dessert::getFlavorProfile() const{
   return flavor_profile_;
}

/**
* Sets the sweetness level of the dessert.
* @param sweetness_level An integer representing the sweetness level of the dessert.
* @post Sets the private member `sweetness_level_` to the value of the parameter.
*/
void Dessert::setSweetnessLevel(const int& sweetness_level) {
   sweetness_level_ = sweetness_level;
}

/**
* @return The sweetness level of the dessert.
*/
int Dessert::getSweetnessLevel() const{
    return sweetness_level_;
}

/**
* Sets the contains_nuts flag of the dessert.
* @param contains_nuts A boolean indicating if the dessert contains nuts.
* @post Sets the private member `contains_nuts_` to the value of the parameter.
*/
void Dessert::setContainsNuts(const bool& contains_nuts) {
   contains_nuts_ = contains_nuts;
}

/**
* @return True if the dessert contains nuts, false otherwise.
*/
bool Dessert::containsNuts() const{
    return contains_nuts_;
}

//Display dessert
void Dessert::displayDessert() const {
   display(); //Display dish

   std::cout << "Flavor Profile: ";

   if (flavor_profile_ == 0)
      std::cout << "SWEET";
   else if (flavor_profile_ == 1)
      std::cout << "BITTER";
   else if (flavor_profile_ == 2)
      std::cout << "SOUR";
   else if (flavor_profile_ == 3)
      std::cout << "UMAMI";
   else if (flavor_profile_ == 4)
      std::cout << "SALTY";

   std::cout << std::endl;
   std::cout << "Sweetness Level: " << getSweetnessLevel() << std::endl;

   if (containsNuts() == 1) //1 = True, 0 = False
      std::cout << "Contains Nuts: True" << std::endl;
   else 
      std::cout << "Contains Nuts: False" << std::endl;
}