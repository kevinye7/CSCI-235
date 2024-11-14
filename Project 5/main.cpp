#include "Dish.hpp"
#include "KitchenStation.hpp"
#include "LinkedList.hpp"
#include "Node.hpp"
#include "PrecondViolatedExcep.hpp"
#include "StationManager.hpp"
#include <iostream>
#include <vector>
#include <string>

int main() {
    Ingredient ing1 = Ingredient("Chicken", 5, 2, 7.7);
    Ingredient ing2 = Ingredient("Beef", 5, 2, 7.7);
    Ingredient ing3 = Ingredient("Lamb", 5, 2, 7.7);
    Ingredient ing4 = Ingredient("Lamb", 5, 2, 7.7);
    std::vector<Ingredient> ing; 
    ing.push_back(ing1);
    ing.push_back(ing2);
    ing.push_back(ing3);
    Dish* d1 = new Dish("dish", ing, 7, 8.8, Dish::ITALIAN);
    Dish* d2 = new Dish("dishes", ing, 7, 8.8, Dish::ITALIAN);
    std::vector<Dish*> dish; 
    dish.push_back(d1);
    dish.push_back(d2);

    KitchenStation* ks = new KitchenStation{"1"};
    ks->setDish(dish);

    ks->setIngredient(ing);
    std::cout << ks->canCompleteOrder("dish") << std::endl;

    // for (int i = 0; i < ks->getDish().size(); i++) {
    //     std::cout << ((ks->getDish())[i]->getName()) << std::endl;
    // }


    return 0;
}