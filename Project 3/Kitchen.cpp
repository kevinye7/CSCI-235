/**
 * @file Kitchen.cpp
 * @brief This file contains the implementation of the Kitchen class, which represents a kitchen in a virtual bistro simulation.
 * 
 * The Kitchen class includes methods to manage and present the details of a kitchen, including total prepreation time and count elaborate.
 * The implementation ensures that the kitchen name is validated and correctly formatted.
 * 
 * @date 10/10/2024
 * @author Kevin Ye
 */

#include "Kitchen.hpp"
#include "cmath"

/**
* Default constructor.
* Default-initializes all private members.
*/
Kitchen::Kitchen() : ArrayBag<Dish>(){
    total_prep_time_ = 0;
    count_elaborate_ = 0;
}

/**
 * @param : A reference to a `Dish` being added to the kitchen.
 * @post : If the given `Dish` is not already in the kitchen, adds the
`Dish` to the kitchen and updates the preparation time sum and elaborate dish count if the dish is elaborate.
 * @return : Returns true if a `Dish` was successfully added to the kitchen, false otherwise.
 Hint: Use the above definition of equality to help determine if a `Dish` is already in the kitchen.
*/
bool Kitchen::newOrder(const Dish& dish) {
    for (int i = 0; i < getCurrentSize(); i++) {
        if (contains(dish))
            return false;
    }

    if (add(dish)) {
        total_prep_time_+=dish.getPrepTime();
        if (dish.getIngredients().size() >=5 && dish.getPrepTime() >= 60)
            count_elaborate_++;
        return true;
    }

    return false;
}

/**
 * @param : A reference to a `Dish` leaving the kitchen.
 * @return : Returns true if a dish was successfully removed from the kitchen 
 * (i.e., items_), false otherwise.
 * @post : Removes the dish from the kitchen and updates the preparation time sum.
 If the `Dish` is elaborate, it also updates the elaborate count.
*/
bool Kitchen::serveDish(const Dish& dish) {
    if (remove(dish)) {
        total_prep_time_-=dish.getPrepTime();
        if (dish.getIngredients().size() >=5 && dish.getPrepTime() >= 60)
            count_elaborate_--;
        return true;
    }

    return false;
}

/**
 * @return : The integer sum of preparation times for all the dishes currently in the kitchen.
*/
int Kitchen::getPrepTimeSum() const {
    return total_prep_time_;
}

/**
 * @return : The average preparation time (int) of all the dishes in the
kitchen. The lowest possible average prep time should be 0.
 * @post : Computes the average preparation time (double) of the kitchen
rounded to the NEAREST integer.
*/
int Kitchen::calculateAvgPrepTime() const {
    if (getCurrentSize() == 0) {
        return 0;
    }

    return round((total_prep_time_/(double)getCurrentSize()));
}

/**
 * @return : The integer count of the elaborate dishes in the kitchen.
*/
int Kitchen::elaborateDishCount() const {
    return count_elaborate_;
}

/**
 * @return : The percentage (double) of all the elaborate dishes in the 
 * kitchen. The lowest possible percentage should be 0%.
 * @post : Computes the percentage of elaborate dishes in the kitchen
 * rounded up to 2 decimal places.
*/
double Kitchen::calculateElaboratePercentage() const {
    if (getCurrentSize() == 0) {
        return 0;
    }

    return ((round((count_elaborate_/(double)getCurrentSize())*10000)))/100;
}

/**
 * @param : A reference to a string representing a cuisine type with a value in 
 * ["ITALIAN", "MEXICAN", "CHINESE", "INDIAN", "AMERICAN", "FRENCH", "OTHER"].
 * @return : An integer tally of the number of dishes in the kitchen of the given cuisine type.
 * If the argument string does not match one of the expected cuisine types, the tally is zero.
 * NOTE: No pre-processing of the input string necessary, only uppercase input will match.
*/
int Kitchen::tallyCuisineTypes(const std::string& cuisine_type) const {
    int count = 0;

    for (int i = 0; i < getCurrentSize(); i++) {
        if (items_[i].getCuisineType() == cuisine_type)
            count++;
    }

    return count;
}

/**
 * @param : A reference to an integer representing the preparation time
 * threshold of the dishes to be removed from the kitchen, with a default value of 0.
 * @post : Removes all dishes from the kitchen whose preparation time is less than the given time.
 * If no time is given, removes all dishes from the kitchen. Ignore negative input.
 * @return : The number of dishes removed from the kitchen.
*/
int Kitchen::releaseDishesBelowPrepTime(const int& prep_time) {
    int count = 0;

    if (prep_time == 0) {
        for (int i = 0; i < getCurrentSize(); i++) {
            remove(items_[i]);
            count++;
        }
    }
    else {
        for (int i = 0; i < getCurrentSize(); i++) {
        if (items_[i].getPrepTime() < prep_time)
            remove(items_[i]);
            count++;
        }
    }

    return count;
}

/**
 * @param : A reference to a string representing a cuisine type with a value in
 ["ITALIAN", "MEXICAN", "CHINESE", "INDIAN", "AMERICAN", "FRENCH", "OTHER"],
 or a default value of "ALL" if no cuisine type is given.
 * @post : Removes all dishes from the kitchen whose cuisine type matches the given type.
 If no cuisine type is given, removes all dishes from the kitchen.
 * @return : The number of dishes removed from the kitchen.
 NOTE: No pre-processing of the input string necessary, only uppercase input will match.
 If the input string does not match one of the expected cuisine
types, do not remove any dishes.
*/
int Kitchen::releaseDishesOfCuisineType(const std::string& cuisine_type) {
    int count = 0;

    if (cuisine_type == "ALL") {
        for (int i = 0; i < getCurrentSize(); i++) {
            remove(items_[i]);
            count++;
        }
    }
    else {
        for (int i = 0; i < getCurrentSize(); i++) {
        if (items_[i].getCuisineType() == cuisine_type)
            remove(items_[i]);
            count++;
        }
    }

    return count;
}

/**
 * @post : Outputs a report of the dishes currently in the kitchen in the form:
 "ITALIAN: {x}\nMEXICAN: {x}\nCHINESE: {x}\nINDIAN: {x}\nAMERICAN: {x}\nFRENCH: {x}\nOTHER: {x}\n\n
 AVERAGE PREP TIME: {x}\ELABORATE: {x}%\n"
 Note that the average preparation time should be rounded to the NEAREST integer, and the
 percentage of elaborate dishes in the kitchen should be rounded to 2 decimal places.

 Example output:
 ITALIAN: 2
 MEXICAN: 3
 CHINESE: 2
 INDIAN: 1
 AMERICAN: 1
 FRENCH: 2
 OTHER: 2
 AVERAGE PREP TIME: 62
 ELABORATE: 53.85%
*/
void Kitchen::kitchenReport() const {
    std::cout << "ITALIAN: " << tallyCuisineTypes("ITALIAN") << std::endl;
    std::cout << "MEXICAN: " << tallyCuisineTypes("MEXICAN") << std::endl;
    std::cout << "CHINESE: " << tallyCuisineTypes("CHINESE") << std::endl;
    std::cout << "INDIAN: " << tallyCuisineTypes("INDIAN") << std::endl;
    std::cout << "AMERICAN: " << tallyCuisineTypes("AMERICAN") << std::endl;
    std::cout << "FRENCH: " << tallyCuisineTypes("FRENCH") << std::endl;
    std::cout << "OTHER: " << tallyCuisineTypes("OTHER") << "\n" << std::endl;
    std::cout << "AVERAGE PREP TIME: " << calculateAvgPrepTime() << std::endl;
    std::cout << "ELABORATE DISHES: " << calculateElaboratePercentage() << "%" << std::endl;
}