/**
 * @author Kevin Ye
 * @date 10/29/2024
 * @brief This file contains the implementation of the Appetizer class, which represents a appetizer in a virtual bistro simulation.
*/

#include "Appetizer.hpp"

/**
 * Default constructor.
 * Initializes all private members with default values.
 */
Appetizer::Appetizer()
    : Dish(), serving_style_(PLATED), spiciness_level_(0), vegetarian_(false) {}

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
Appetizer::Appetizer(const std::string& name, const std::vector<std::string>& ingredients, const int &prep_time, const double &price, const CuisineType &cuisine_type, const ServingStyle &serving_style, const int &spiciness_level, const bool &vegetarian)
    : Dish(name, ingredients, prep_time, price, cuisine_type), serving_style_(serving_style), spiciness_level_(spiciness_level), vegetarian_(vegetarian) {}

/**
 * Sets the serving style of the appetizer.
 * @param serving_style The new serving style.
 * @post Sets the private member `serving_style_` to the value of the parameter.
 */
void Appetizer::setServingStyle(const ServingStyle &serving_style) {
    serving_style_ = serving_style;
}

/**
 * @return The serving style of the appetizer.
 */
Appetizer::ServingStyle Appetizer::getServingStyle() const {
    return serving_style_;
}

/**
 * Sets the spiciness level of the appetizer.
 * @param spiciness_level An integer representing the spiciness level of the appetizer.
 * @post Sets the private member `spiciness_level_` to the value of the parameter.
 */
void Appetizer::setSpicinessLevel(const int &spiciness_level) {
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
void Appetizer::setVegetarian(const bool &vegetarian) {
    vegetarian_ = vegetarian;
}

/**
 * @return True if the appetizer is vegetarian, false otherwise.
 */
bool Appetizer::isVegetarian() const {
    return vegetarian_;
}

/**
* Displays the appetizer's details.
* @post Outputs the appetizer's details, including name, ingredients,
preparation time, price, cuisine type, serving style, spiciness level, and
vegetarian status, to the standard output.
* The information must be displayed in the following format:
*
* Dish Name: [Name of the dish]
* Ingredients: [Comma-separated list of ingredients]
* Preparation Time: [Preparation time] minutes
* Price: $[Price, formatted to two decimal places]
* Cuisine Type: [Cuisine type]
* Serving Style: [Serving style: Plated, Family Style, or Buffet]
* Spiciness Level: [Spiciness level]
* Vegetarian: [Yes/No]
*/
void Appetizer::display() const {
    Dish::display();

    std::cout << "Serving Style: ";

    //Printing out the enum values of serving style into a string
    if (serving_style_ == 0)
        std::cout << "Plated";
    else if (serving_style_ == 1)
        std::cout << "Family Style";
    else if (serving_style_ == 2)
        std::cout << "Buffet";
        
    std::cout << std::endl;
    std::cout << "Spiciness Level: " << getSpicinessLevel() << std::endl;

    if (isVegetarian() == 1) //1 = Yes, 0 = No
        std::cout << "Vegetarian: Yes" << std::endl;
    else 
        std::cout << "Vegetarian: No" << std::endl;
}

/**
* Modifies the appetizer based on dietary accommodations.
* @param request A DietaryRequest structure specifying the dietary
accommodations.
* @post Adjusts the appetizer's attributes to meet the specified
dietary needs.
* - If `request.vegetarian` is true:
* - Sets `vegetarian_` to true.
* - Searches `ingredients_` for any non-vegetarian
ingredients and replaces the first occurrence with "Beans". If there are
other non-vegetarian ingredients, the next non-vegetarian ingredient is
replaced with "Mushrooms". If there are more, they will be removed
without substitution.
* Non-vegetarian ingredients are: "Meat", "Chicken",
"Fish", "Beef", "Pork", "Lamb", "Shrimp", "Bacon".
* - If `request.low_sodium` is true:
* - Reduces `spiciness_level_` by 2 (minimum of 0).
* - If `request.gluten_free` is true:
* - Removes gluten-containing ingredients from
`ingredients_`.
* Gluten-containing ingredients are: "Wheat", "Flour",
"Bread", "Pasta", "Barley", "Rye", "Oats", "Crust".
*/
void Appetizer::dietaryAccommodations(const Dish::DietaryRequest &request) {
    if (request.vegetarian) {
        vegetarian_ = true;

        int count = 0;
        int occurrence = 0;

        std::vector<std::string> nonVegetarian = {"Meat", "Chicken", "Fish", "Beef", "Pork", "Lamb", "Shrimp", "Bacon"};
        std::vector<std::string> copy = getIngredients();
        std::vector<std::string> set;

        //Checking if ingredients contains non-vegetarian ingredients by checking each element in copy to each non-vegetarian element
        for (int i = 0; i < copy.size(); i++) {
            for (int j = 0; j < nonVegetarian.size(); j++) {
                if (copy[i] != nonVegetarian[j])
                    count++;
            }

            if (count == nonVegetarian.size()) {
                set.push_back(copy[i]); //Ingredient get added if it is vegetarian ingredients
            }
            else if (occurrence == 0) {
                set.push_back("Beans"); //Beans get added if the first non-vegetarian ingredient is found
                occurrence++;
            }
            else if (occurrence == 1) {
                set.push_back("Mushrooms"); //Mushrooms get added if the second non-vegetarian ingredient is found
                occurrence++;
            }

            count = 0; //Set count back to zero since it is finished checking if the ingredient match with any of the non-vegetarian ingredients 
        }

        setIngredients(set);
    }

    if (request.low_sodium) {
        spiciness_level_-=2;

        if (spiciness_level_ < 0)
            spiciness_level_ = 0;
    }

    if (request.gluten_free) {
        int count = 0;

        std::vector<std::string> glutenContaining = {"Wheat", "Flour", "Bread", "Pasta", "Barley", "Rye", "Oats", "Crust"}; 
        std::vector<std::string> copy = getIngredients();
        std::vector<std::string> set;

        //Checking if ingredients contains gluten-containing ingredients by checking each element in copy to each gluten-containing element
        for (int i = 0; i < copy.size(); i++) {
            for (int j = 0; j < glutenContaining.size(); j++) {
                if (copy[i] != glutenContaining[j]) {
                    count++;
                }
            }
            
            if (count == glutenContaining.size()) {
                set.push_back(copy[i]); //Ingredient get added if it is not gluten-containing ingredients 
            }
            
            count = 0; //Set count back to zero since it is finished checking if the ingredient match with any of the gluten-containing ingredients 
        }

        setIngredients(set);
    }
}