/**
* @file Appetizer.cpp
* @brief This file contains the implementation of the Appetizer class, which represents a appetizer in a virtual bistro simulation.
* 
* The Appetizer class includes methods to manage and present the details of a appetizer, including serving style, spiciness level, and vegetarian.
* The implementation ensures that the appetizer name is validated and correctly formatted.
* 
* @date 9/29/2024
* @author Kevin Ye
*/

#include "Appetizer.hpp"
#include <iostream>

/**
* Default constructor.
* Initializes all private members with default values.
*/
Appetizer::Appetizer() {
   Dish();
   serving_style_ = PLATED;
   spiciness_level_ = 0;
   vegetarian_ = false;
}

/**
* Parameterized constructor.
* @param name The name of the appetizer.
* @param ingredients The ingredients used in the appetizer.
* @param prep_time The preparation time in minutes.
* @param price The price of the appetizer.
* @param cuisine_type The cuisine type of the appetizer.
* @param serving_style The serving style of the appetizer.
* @param spiciness_level The spiciness level of the appetizer.
* @param vegetarian Flag indicating if the appetizer is vegetarian.
*/
Appetizer::Appetizer(const std::string& name, const std::vector<std::string>& ingredients, int prep_time, double price, CuisineType cuisine_type, ServingStyle serving_style, int spiciness_level, bool vegetarian) : Dish(name, ingredients, prep_time, price, cuisine_type) {
   serving_style_ = serving_style;
   spiciness_level_ = spiciness_level;
   vegetarian_ = vegetarian;
}

/**
* Sets the serving style of the appetizer.
* @param serving_style The new serving style.
* @post Sets the private member `serving_style_` to the value of the parameter.
*/
void Appetizer::setServingStyle(const ServingStyle& serving_style) {
   serving_style_ = serving_style;
}

/**
* @return The serving style of the appetizer (as an enum).
*/
Appetizer::ServingStyle Appetizer::getServingStyle() const {
   return serving_style_;
}
 
/**
* Sets the spiciness level of the appetizer.
* @param spiciness_level An integer representing the spiciness level of the appetizer.
* @post Sets the private member `spiciness_level_` to the value of the parameter.
*/
void Appetizer::setSpicinessLevel(const int& spiciness_level) {
   spiciness_level_ = spiciness_level;
}

/**
* @return The spiciness level of the appetizer.
*/
int Appetizer::getSpicinessLevel() const {
   return spiciness_level_;
}

/**
* Sets the vegetarian flag of the appetizer.
* @param vegetarian A boolean indicating if the appetizer is vegetarian.
* @post Sets the private member `vegetarian_` to the value of the parameter.
*/
void Appetizer::setVegetarian(const bool& vegetarian) {
   vegetarian_ = vegetarian;
}

/**
* @return True if the appetizer is vegetarian, false otherwise.
*/
bool Appetizer::isVegetarian() const {
   return vegetarian_;
}

//Display appetizer
void Appetizer::displayAppetizer() const {
   display(); //Display dish

   std::cout << "Spiciness Level: " << getSpicinessLevel() << std::endl;
   std::cout << "Serving Style: ";

   if (serving_style_ == 0)
      std::cout << "PLATED";
   else if (serving_style_ == 1)
      std::cout << "FAMILY_STYLE";
   else if (serving_style_ == 2)
      std::cout << "BUFFET";
      
   std::cout << std::endl;

   if (isVegetarian() == 1) //1 = True, 0 = False
      std::cout << "Vegetarian: True" << std::endl;
   else 
      std::cout << "Vegetarian: False" << std::endl;
}