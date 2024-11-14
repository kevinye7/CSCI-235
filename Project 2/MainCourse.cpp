/**
* @file MainCourse.cpp
* @brief This file contains the implementation of the MainCourse class, which represents a MainCourse in a virtual bistro simulation.
* 
* The MainCourse class includes methods to manage and present the details of a MainCourse, including cooking method, protein type, side dishes, and gluten free.
* The implementation ensures that the MainCourse name is validated and correctly formatted.
* 
* @date 9/29/2024
* @author Kevin Ye
*/

#include "MainCourse.hpp"
#include <iostream>

/**
* Default constructor.
* Initializes all private members with default values.
*/
MainCourse::MainCourse() : Dish(), cooking_method_{GRILLED}, protein_type_{"UNKNOWN"}, side_dishes_{}, gluten_free_{false}{
}

/**
* Parameterized constructor.
* @param name The name of the main course.
* @param ingredients A vector of the ingredients used in the main course.
* @param prep_time The preparation time in minutes.
* @param price The price of the main course.
* @param cuisine_type The cuisine type of the main course.
* @param cooking_method The cooking method used for the main course.
* @param protein_type The type of protein used in the main course.
* @param side_dishes A vector of the side dishes served with the main course.
* @param gluten_free Boolean flag indicating if the main course is gluten-free.
*/
MainCourse::MainCourse(const std::string& name, const std::vector<std::string>& ingredients, int prep_time, double price, CuisineType cuisine_type, CookingMethod cooking_method, std::string protein_type, std::vector<SideDish> side_dishes, bool gluten_free) : Dish(name, ingredients, prep_time, price, cuisine_type) {
   cooking_method_ = cooking_method;
   protein_type_ = protein_type; 
   side_dishes_ = side_dishes; 
   gluten_free_ = gluten_free;
}

/**
* Sets the cooking method of the main course.
* @param cooking_method The new cooking method.
* @post Sets the private member `cooking_method_` to the value of the parameter.
*/
void MainCourse::setCookingMethod(const CookingMethod& cooking_method) {
   cooking_method_ = cooking_method;
}

/**
* @return The cooking method of the main course (as an enum).
*/
MainCourse::CookingMethod MainCourse::getCookingMethod() const{
   return cooking_method_;
}

/**
* Sets the type of protein in the main course.
* @param protein_type A string representing the type of protein.
* @post Sets the private member `protein_type_` to the value of the parameter.
*/
void MainCourse::setProteinType(const std::string& protein_type) {
   protein_type_ = protein_type;
}

/**
* @return The type of protein in the main course.
*/
std::string MainCourse::getProteinType() const{
    return protein_type_;
}

/**
* Adds a side dish to the main course.
* @param side_dish A SideDish struct containing the name and category of the side dish.
* @post Adds the side dish to the `side_dishes_` vector.
*/
void MainCourse::addSideDish(const SideDish& side_dishes) {
   side_dishes_.push_back(side_dishes);
}

/**
* @return A vector of SideDish structs representing the side dishes served with the main course.
*/
std::vector<MainCourse::SideDish> MainCourse::getSideDishes() const {
    return side_dishes_;
}

/**
* Sets the gluten-free flag of the main course.
* @param gluten_free A boolean indicating if the main course is glutenfree.
* @post Sets the private member `gluten_free_` to the value of the parameter.
*/
void MainCourse::setGlutenFree(const bool& gluten_free) {
   gluten_free_ = gluten_free;
}

/**
* @return True if the main course is gluten-free, false otherwise.
*/
bool MainCourse::isGlutenFree() const{
    return gluten_free_;
}


//Display main course
void MainCourse::displayMainCourse() const {
   display(); //Display dish

   std::cout << "Cooking Method: ";

   if (cooking_method_ == 0)
      std::cout << "GRILLED";
   else if (cooking_method_ == 1)
      std::cout << "BAKED";
   else if (cooking_method_ == 2)
      std::cout << "FRIED";
   else if (cooking_method_ == 3)
      std::cout << "STEAMED";
   else if (cooking_method_ == 4)
      std::cout << "RAW";

   std::cout << std::endl;
   std::cout << "Protein Type: " << getProteinType() << std::endl;
   std::cout << "Side Dishes: ";

   //
   for (int i = 0; i < side_dishes_.size(); i++) {
      std::cout << side_dishes_[i].name;

      //Finding side dish i category
      if (side_dishes_[i].category == 0)
         std::cout << " (GRAIN)";
      else if (side_dishes_[i].category == 1)
         std::cout << " (PASTA)";
      else if (side_dishes_[i].category == 2)
         std::cout << " (LEGUME)";
      else if (side_dishes_[i].category == 3)
         std::cout << " (BREAD)";
      else if (side_dishes_[i].category == 4)
         std::cout << " (SALAD)";
      else if (side_dishes_[i].category == 5)
         std::cout << " (SOUP)";
      else if (side_dishes_[i].category == 6)
         std::cout << " (STARCHES)";
      else if (side_dishes_[i].category == 7)
         std::cout << " (VEGETABLE)";

      //Puts a comma if i isn't the last side dish in the list
      if (i != side_dishes_.size()-1)
         std::cout << ", ";
   }

   std::cout << std::endl;

   if (gluten_free_ == 1) //1 = True, 0 = False
      std::cout << "Gluten-Free: True" << std::endl;
   else
      std::cout << "Gluten-Free: False" << std::endl;
}