/**
 * @file Kitchen.hpp
 * @brief This file contains the declaration of the Kitchen class, which represents a kitchen in a virtual bistro simulation.
 * 
 * The Kitchen class includes attributes such as total prepreation time and count elaborate.
 * It provides constructors, accessor and mutator functions, and a display function to manage and present
 * the details of a kitchen.
 * 
 * @date 10/10/2024
 * @author Kevin Ye
 */

#ifndef KITCHEN_HPP
#define KITCHEN_HPP

#include "Dish.hpp"
#include "ArrayBag.hpp"

class Kitchen : public ArrayBag<Dish> {
    public:
        /**
        * Default constructor.
        * Default-initializes all private members.
        */
        Kitchen();

        /**
         * @param : A reference to a `Dish` being added to the kitchen.
         * @post : If the given `Dish` is not already in the kitchen, adds the
        `Dish` to the kitchen and updates the preparation time sum and elaborate dish count if the dish is elaborate.
        * @return : Returns true if a `Dish` was successfully added to the kitchen, false otherwise.
        Hint: Use the above definition of equality to help determine if a `Dish` is already in the kitchen.
        */
        bool newOrder(const Dish& dish);

        /**
         * @param : A reference to a `Dish` leaving the kitchen.
         * @return : Returns true if a dish was successfully removed from the kitchen 
         * (i.e., items_), false otherwise.
         * @post : Removes the dish from the kitchen and updates the preparation time sum.
         If the `Dish` is elaborate, it also updates the elaborate count.
        */
        bool serveDish(const Dish& dish);

        /**
         * @return : The integer sum of preparation times for all the dishes currently in the kitchen.
        */
        int getPrepTimeSum() const;

        /**
         * @return : The average preparation time (int) of all the dishes in the
        kitchen. The lowest possible average prep time should be 0.
        * @post : Computes the average preparation time (double) of the kitchen
        rounded to the NEAREST integer.
        */
        int calculateAvgPrepTime() const;

        /**
         * @return : The integer count of the elaborate dishes in the kitchen.
        */
        int elaborateDishCount() const;

        /**
         * @return : The percentage (double) of all the elaborate dishes in the 
         * kitchen. The lowest possible percentage should be 0%.
         * @post : Computes the percentage of elaborate dishes in the kitchen
         * rounded up to 2 decimal places.
        */
        double calculateElaboratePercentage() const;

        /**
         * @param : A reference to a string representing a cuisine type with a value in 
         * ["ITALIAN", "MEXICAN", "CHINESE", "INDIAN", "AMERICAN", "FRENCH", "OTHER"].
         * @return : An integer tally of the number of dishes in the kitchen of the given cuisine type.
         * If the argument string does not match one of the expected cuisine types, the tally is zero.
         * NOTE: No pre-processing of the input string necessary, only uppercase input will match.
        */
        int tallyCuisineTypes(const std::string& cuisine_type) const;

        /**
         * @param : A reference to an integer representing the preparation time
         * threshold of the dishes to be removed from the kitchen, with a default value of 0.
         * @post : Removes all dishes from the kitchen whose preparation time is less than the given time.
         * If no time is given, removes all dishes from the kitchen. Ignore negative input.
         * @return : The number of dishes removed from the kitchen.
        */
        int releaseDishesBelowPrepTime(const int& prep_time);

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
        int releaseDishesOfCuisineType(const std::string& cuisine_type);

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
        void kitchenReport() const;

    private:
        //An integer sum of the preparation times of all the dishes currently in the kitchen.
        int total_prep_time_;

        //An integer count of all of the elaborate dishes in the kitchen. 
        //An elaborate dish is one that has 5 or more ingredients, and a prep time of an hour or more. 
        int count_elaborate_;
};

#endif // KITCHEN_HPP