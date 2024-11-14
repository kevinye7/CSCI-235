/**
 * @author Kevin Ye
 * @date 10/29/2024
 * @brief This file contains the declaration of the Kitchen class, which represents a kitchen in a virtual bistro simulation.
*/

#ifndef KITCHEN_HPP
#define KITCHEN_HPP

#include "ArrayBag.hpp"
#include "Dish.hpp"
#include "Appetizer.hpp"
#include "MainCourse.hpp"
#include "Dessert.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <memory>
// for round
#include <cmath>

class Kitchen : public ArrayBag<Dish*> {
    public:
        Kitchen();
        bool newOrder(Dish* new_dish);
        bool serveDish(Dish* dish_to_remove);
        int getPrepTimeSum() const;
        int calculateAvgPrepTime() const;
        int elaborateDishCount() const;
        double calculateElaboratePercentage() const;
        int tallyCuisineTypes(const std::string& cuisine_type) const;
        int releaseDishesBelowPrepTime(const int& prep_time);
        int releaseDishesOfCuisineType(const std::string& cuisine_type);
        void kitchenReport() const;

        /**
        * Parameterized constructor.
        * @param filename The name of the input CSV file containing dish
        information.
        * @pre The CSV file must be properly formatted.
        * @post Initializes the kitchen by reading dishes from the CSV file and
        storing them as `Dish*`.
        */
        Kitchen(const std::string& filename);

        /**
        * Adjusts all dishes in the kitchen based on the specified dietary
        accommodation.
        * @param request A DietaryRequest structure specifying the dietary
        accommodations.
        * @post Calls the `dietaryAccommodations()` method on each dish in the
        kitchen to adjust them accordingly.
        */
        void dietaryAdjustment(const Dish::DietaryRequest& request);

        /**
        * Displays all dishes currently in the kitchen.
        * @post Calls the `display()` method of each dish.
        */
        void displayMenu() const;

        /**
        * Destructor.
        * @post Deallocates all dynamically allocated dishes to prevent memory
        leaks.
        */
        ~Kitchen();

    private:
        int total_prep_time_;
        int count_elaborate_;
    
};

#endif // KITCHEN_HPP