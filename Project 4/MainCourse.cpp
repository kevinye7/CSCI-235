/**
 * @author Kevin Ye
 * @date 10/29/2024
 * @brief This file contains the implementation of the MainCourse class, which represents a MainCourse in a virtual bistro simulation.
*/

#include "MainCourse.hpp"

/**
 * Default constructor.
 * Initializes all private members with default values.
 */
MainCourse::MainCourse()
    : Dish(), cooking_method_(GRILLED), protein_type_("UNKNOWN"), side_dishes_(), gluten_free_(false) {}

/**
 * Parameterized constructor.
 * @param name The name of the main course.
 * @param ingredients The ingredients used in the main course.
 * @param prep_time The preparation time in minutes.
 * @param price The price of the main course.
 * @param cuisine_type The cuisine type of the main course.
 * @param cooking_method The cooking method used for the main course.
 * @param protein_type The type of protein used in the main course.
 * @param side_dishes The side dishes served with the main course.
 * @param gluten_free Flag indicating if the main course is gluten-free.
 */
MainCourse::MainCourse(const std::string& name, const std::vector<std::string>& ingredients, const int &prep_time, const double &price, const CuisineType &cuisine_type, const CookingMethod &cooking_method, const std::string& protein_type, const std::vector<SideDish>& side_dishes, const bool &gluten_free)
    : Dish(name, ingredients, prep_time, price, cuisine_type), cooking_method_(cooking_method), protein_type_(protein_type), side_dishes_(side_dishes), gluten_free_(gluten_free) {}

/**
 * Sets the cooking method of the main course.
 * @param cooking_method The new cooking method.
 * @post Sets the private member `cooking_method_` to the value of the parameter.
 */
void MainCourse::setCookingMethod(const CookingMethod &cooking_method) {
    cooking_method_ = cooking_method;
}

/**
 * @return The cooking method of the main course.
 */
MainCourse::CookingMethod MainCourse::getCookingMethod() const {
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
std::string MainCourse::getProteinType() const {
    return protein_type_;
}

/**
 * Adds a side dish to the main course.
 * @param side_dish A SideDish struct containing the name and category of the side dish.
 * @post Adds the side dish to the `side_dishes_` vector.
 */
void MainCourse::addSideDish(const SideDish& side_dish) {
    side_dishes_.push_back(side_dish);
}

/**
 * @return A vector of SideDish structs representing the side dishes served with the main course.
 */
std::vector<MainCourse::SideDish> MainCourse::getSideDishes() const {
    return side_dishes_;
}

/**
 * Sets the gluten-free flag of the main course.
 * @param gluten_free A boolean indicating if the main course is gluten-free.
 * @post Sets the private member `gluten_free_` to the value of the parameter.
 */
void MainCourse::setGlutenFree(const bool &gluten_free) {
    gluten_free_ = gluten_free;
}

/**
 * @return True if the main course is gluten-free, false otherwise.
 */
bool MainCourse::isGlutenFree() const {
    return gluten_free_;
}

/**
* Displays the main course's details.
* @post Outputs the main course's details, including name, ingredients,
preparation time, price, cuisine type, cooking method, protein type,
side dishes, and gluten-free status to the standard output.
* The information must be displayed in the following format:
*
* Dish Name: [Name of the dish]
* Ingredients: [Comma-separated list of ingredients
* Preparation Time: [Preparation time] minutes
* Price: $[Price, formatted to two decimal places]
* Cuisine Type: [Cuisine type]
* Cooking Method: [Cooking method: e.g., Grilled, Baked, etc.]
* Protein Type: [Type of protein: e.g., Chicken, Beef, etc.]
* Side Dishes: [Side dish name] (Category: [Category: e.g., Starches,
Vegetables])
* Gluten-Free: [Yes/No]
*/
void MainCourse::display() const {
    Dish::display(); //Display dish

    std::cout << "Cooking Method: ";

    if (cooking_method_ == 0)
        std::cout << "Grilled";
    else if (cooking_method_ == 1)
        std::cout << "Baked";
    else if (cooking_method_ == 2)
        std::cout << "Boiled";
    else if (cooking_method_ == 3)
        std::cout << "Fried";
    else if (cooking_method_ == 4)
        std::cout << "Steamed";
    else if (cooking_method_ == 5)
        std::cout << "Raw";

    std::cout << std::endl;
    std::cout << "Protein Type: " << getProteinType() << std::endl;
    std::cout << "Side Dishes: ";

    for (int i = 0; i < side_dishes_.size(); i++) {
        std::cout << side_dishes_[i].name;

        //Finding side dish i category
        if (side_dishes_[i].category == 0)
            std::cout << " (Category: Grain)";
        else if (side_dishes_[i].category == 1)
            std::cout << " (Category: Pasta)";
        else if (side_dishes_[i].category == 2)
            std::cout << " (Category: Legume)";
        else if (side_dishes_[i].category == 3)
            std::cout << " (Category: Bread)";
        else if (side_dishes_[i].category == 4)
            std::cout << " (Category: Salad)";
        else if (side_dishes_[i].category == 5)
            std::cout << " (Category: Soup)";
        else if (side_dishes_[i].category == 6)
            std::cout << " (Category: Starches)";
        else if (side_dishes_[i].category == 7)
            std::cout << " (Category: Vegetable)";

        //Puts a comma if i isn't the last side dish in the list
        if (i != side_dishes_.size()-1)
            std::cout << ", ";
    }

    std::cout << std::endl;

    if (gluten_free_ == 1) //1 = Yes, 0 = No
        std::cout << "Gluten-Free: Yes" << std::endl;
    else
        std::cout << "Gluten-Free: No" << std::endl;
}

/**
* Modifies the main course based on dietary accommodations.
* @param request A DietaryRequest structure specifying the dietary
accommodations.
* @post Adjusts the main course's attributes to meet the specified
dietary needs.
* - If `request.vegetarian` is true:
* - Changes `protein_type_` to "Tofu".
* - Searches `ingredients_` for any non-vegetarian
ingredients and replaces the first occurrence with "Beans". If there are
other non-vegetarian ingredients, the next non-vegetarian ingredient is
replaced with "Mushrooms". If there are more, they will be removed
without substitution.
* Non-vegetarian ingredients are: "Meat", "Chicken",
"Fish", "Beef", "Pork", "Lamb", "Shrimp", "Bacon".
* - If `request.vegan` is true:
* - Changes `protein_type_` to "Tofu".
* - Removes dairy and egg ingredients from `ingredients_`.
* Dairy and egg ingredients are: "Milk", "Eggs", "Cheese",
"Butter", "Cream", "Yogurt".
* - If `request.gluten_free` is true:
* - Sets `gluten_free_` to true.
* - Removes side dishes from `side_dishes_` whose category
involves gluten.
* Gluten-containing side dish categories are: `GRAIN`,
`PASTA`, `BREAD`, `STARCHES`.
*/
void MainCourse::dietaryAccommodations(const Dish::DietaryRequest &request) {
    if (request.vegetarian) {
        protein_type_ = "Tofu";

        int count = 0;
        int occurrence = 0;

        std::vector<std::string> nonVegetarian = {"Meat", "Chicken", "Fish", "Beef", "Pork", "Lamb", "Shrimp", "Bacon"};
        std::vector<std::string> copy = getIngredients();
        std::vector<std::string> set;

        //Checking if ingredients contains non-vegetarian ingredients by checking each element in copy to each non-vegetarian element
        for (int i = 0; i < copy.size(); i++) {
            for (int j = 0; j < nonVegetarian.size(); j++) {
                if (copy[i] != nonVegetarian[j]) {
                    count++;
                }
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

    if (request.vegan) {
        protein_type_ = "Tofu";

        int count = 0;

        std::vector<std::string> dairyAndEgg = {"Milk", "Eggs", "Cheese", "Butter", "Cream", "Yogurt"}; 
        std::vector<std::string> copy = getIngredients();
        std::vector<std::string> set;

        //Checking if ingredients contains nuts ingredients by checking each element in copy to each dairy and egg element
        for (int i = 0; i < copy.size(); i++) {
            for (int j = 0; j < dairyAndEgg.size(); j++) {
                if (copy[i] != dairyAndEgg[j]) {
                    count++;
                }
            }
            
            if (count == dairyAndEgg.size()) {
                set.push_back(copy[i]); //Ingredient get added if it is not dairy and egg ingredients 
            }
            
            count = 0; //Set count back to zero since it is finished checking if the ingredient match with any of the dairy and egg ingredients 
        }

        setIngredients(set);
    
    }

    if (request.gluten_free) {
        gluten_free_ = true;

        int count = 0;

        std::vector<SideDish> glutenContaining = {{"", GRAIN}, {"", PASTA}, {"", BREAD}, {"", STARCHES}}; 
        std::vector<SideDish> copy = side_dishes_;
        std::vector<SideDish> set;

        side_dishes_.clear(); //Needs to clear side dishes before adding the non gluten-containg side dish categories

        //Checking if side dishes category contains gluten-containing side dish categories by checking each category for each element in copy to each category in each gluten-containing element
        for (int i = 0; i < copy.size(); i++) {
            for (int j = 0; j < glutenContaining.size(); j++) {
                if (copy[i].category != glutenContaining[j].category) {
                    count++;
                }
            }
            
            if (count == glutenContaining.size()) {
                addSideDish(copy[i]); //Side dishes get added if the side dish category does not contain gluten
            }
            
            count = 0; //Set count back to zero since it is finished checking if each category for each element in copy match to each category in each gluten-containing element
        }

    }
}