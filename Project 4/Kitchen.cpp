/**
 * @author Kevin Ye
 * @date 10/29/2024
 * @brief This file contains the implementation of the Kitchen class, which represents a kitchen in a virtual bistro simulation.
*/

#include "Kitchen.hpp"

Kitchen::Kitchen() : ArrayBag<Dish*>(), total_prep_time_(0), count_elaborate_(0) {

}
bool Kitchen::newOrder(Dish* new_dish)
{
    if (add(new_dish))
    {
        total_prep_time_ += new_dish->getPrepTime();
        //std::cout<< "Dish added: "<<new_dish.getName() << std::endl;
        //if the new dish has 5 or more ingredients AND takes an hour or more to prepare, increment count_elaborate_
        if (new_dish->getIngredients().size() >= 5 && new_dish->getPrepTime() >= 60)
        {
            //std::cout << "Elaborate dish added: "<<new_dish.getName() << std::endl;
            count_elaborate_++;
        }
        return true;
    }
    return false;
}
bool Kitchen::serveDish(Dish* dish_to_remove)
{
    if (getCurrentSize() == 0)
    {
        return false;
    }
    if (remove(dish_to_remove))
    {
        total_prep_time_ -= dish_to_remove->getPrepTime();
        if (dish_to_remove->getIngredients().size() >= 5 && dish_to_remove->getPrepTime() >= 60)
        {
            count_elaborate_--;
        }
        return true;
    }
    return false;
}
int Kitchen::getPrepTimeSum() const
{
    if (getCurrentSize() == 0)
    {
        return 0;
    }
    return total_prep_time_;
}
int Kitchen::calculateAvgPrepTime() const
{
    if (getCurrentSize() == 0)
    {
        return 0;
    }
    double total_prep_time_ = 0;
    for (int i = 0; i < getCurrentSize(); i++)
    {
        total_prep_time_ += items_[i]->getPrepTime();
    }
    total_prep_time_ = total_prep_time_ / getCurrentSize();
    // std::cout<< "Total prep time: "<<total_prep_time_ << std::endl;
    // std::cout<<"rounded: "<<round(total_prep_time_)<<std::endl;
    return round(total_prep_time_);
}
int Kitchen::elaborateDishCount() const
{
    if (getCurrentSize() == 0 || count_elaborate_ == 0)
    {
        return 0;
    }
    return count_elaborate_;
}
double Kitchen::calculateElaboratePercentage() const
{
    // //Computes the percentage of vegetarian dishes in the kitchen rounded up to 2 decimal places.
    // double elaborate_dish = count_elaborate_;
    // std::cout << elaborate_dish << std::endl;

    // double total_dish = getCurrentSize();
    // std::cout << total_dish << std::endl;

    // double percentage = (elaborate_dish / total_dish) * 10000;
    // std::cout << percentage << std::endl;
    // percentage = round(percentage);
    // std::cout << percentage << std::endl;
    // percentage = percentage / 100;
    // std::cout << percentage << std::endl;

    // return percentage;
    if (getCurrentSize() == 0 || count_elaborate_ == 0)
    {
        return 0;
    }
    return round(double(count_elaborate_) / double(getCurrentSize()) * 10000)/100;

    //return count_elaborate_ / getCurrentSize();
}
int Kitchen::tallyCuisineTypes(const std::string& cuisine_type) const{
    int count = 0;
    for (int i = 0; i < getCurrentSize(); i++)
    {
        if (items_[i]->getCuisineType() == cuisine_type)
        {
            count++;
        }
    }
    return count;
}
int Kitchen::releaseDishesBelowPrepTime(const int& prep_time)
{
    int count = 0;
    int num= getCurrentSize();
    for (int i = 0; i < num; i++)
    {
        if (items_[i]->getPrepTime() < prep_time)
        {
            count++;
            serveDish(items_[i]);
        }
    }
    return count;
}

int Kitchen::releaseDishesOfCuisineType(const std::string& cuisine_type)
{
    int count = 0;
    for (int i = 0; i < getCurrentSize(); i++)
    {
        if (items_[i]->getCuisineType() == cuisine_type)
        {
            count++;
            serveDish(items_[i]);
        }
    }
    return count;
}
void Kitchen::kitchenReport() const
{
    std::cout << "ITALIAN: " << tallyCuisineTypes("ITALIAN") << std::endl;
    std::cout << "MEXICAN: " << tallyCuisineTypes("MEXICAN") << std::endl;
    std::cout << "CHINESE: " << tallyCuisineTypes("CHINESE") << std::endl;
    std::cout << "INDIAN: " << tallyCuisineTypes("INDIAN") << std::endl;
    std::cout << "AMERICAN: " << tallyCuisineTypes("AMERICAN") << std::endl;
    std::cout << "FRENCH: " << tallyCuisineTypes("FRENCH") << std::endl;
    std::cout << "OTHER: " << tallyCuisineTypes("OTHER") << std::endl<<std::endl;
    std::cout << "AVERAGE PREP TIME: " << calculateAvgPrepTime() << std::endl;
    std::cout << "ELABORATE DISHES: " << calculateElaboratePercentage() << "%" << std::endl;
}

/**
* Parameterized constructor.
* @param filename The name of the input CSV file containing dish
information.
* @pre The CSV file must be properly formatted.
* @post Initializes the kitchen by reading dishes from the CSV file and
storing them as `Dish*`.
*/
Kitchen::Kitchen(const std::string& filename) : ArrayBag<Dish*>(), total_prep_time_(0), count_elaborate_(0) {
    std::ifstream file(filename);

    std::string line;
    std::string dishType;
    std::string name;
    std::string ingredients;
    std::string preparationTime;
    std::string price;
    std::string cuisineType;
    std::string additionalAttributes;

    if (file.is_open()) { //Checking if it is able to open the file
        std::getline(file, line);

        while(std::getline(file, line)) {
            std::stringstream l(line);

            std::getline(l, dishType, ',');
            std::getline(l, name, ',');
            std::getline(l, ingredients, ',');
            std::getline(l, preparationTime, ',');
            std::getline(l, price, ',');
            std::getline(l, cuisineType, ',');
            std::getline(l, additionalAttributes, ',');

            std::stringstream i(ingredients);
            std::string eachI;
            std::vector<std::string> list1;

            //Seperating the ingredients by ; and storing them into a list1
            while (std::getline(i, eachI, ';')) {
                list1.push_back(eachI);
            }

            std::stringstream a(additionalAttributes);
            std::string eachA;
            std::vector<std::string> list2;

            //Seperating the additional attributes by ; and storing them into a list2
            while (std::getline(a, eachA, ';')) {
                list2.push_back(eachA);
            }

            //Converting string into cuisine type
            Dish::CuisineType cuisine;
            if (cuisineType == "ITALIAN")
                cuisine = Dish::CuisineType::ITALIAN;
            else if (cuisineType == "MEXICAN")
                cuisine = Dish::CuisineType::MEXICAN;
            else if (cuisineType == "CHINESE")
                cuisine = Dish::CuisineType::CHINESE;
            else if (cuisineType == "INDIAN")
                cuisine = Dish::CuisineType::INDIAN;
            else if (cuisineType == "AMERICAN")
                cuisine = Dish::CuisineType::AMERICAN;
            else if (cuisineType == "FRENCH")
                cuisine = Dish::CuisineType::FRENCH;
            else
                cuisine = Dish::CuisineType::OTHER;

            if (dishType == "APPETIZER") {
                Appetizer::ServingStyle style;

                //Converting string into serving style
                if (list2[0] == "FAMILY_STYLE")
                    style = Appetizer::ServingStyle::FAMILY_STYLE;
                else if (list2[0] == "BUFFET")
                    style = Appetizer::ServingStyle::BUFFET;
                else 
                    style = Appetizer::ServingStyle::PLATED;

                bool vegetarian = list2[2] == "true"; //Converting string into boolean

                Dish *a = new Appetizer(name, list1, stoi(preparationTime), stod(price), cuisine, style, stoi(list2[1]), vegetarian);
                newOrder(a);
            }

            else if (dishType == "MAINCOURSE") {
                MainCourse::CookingMethod method;
                
                //Converting string into cooking method
                if (list2[0] == "GRILLED")
                    method = MainCourse::CookingMethod::GRILLED;
                else if (list2[0] == "BAKED")
                    method = MainCourse::CookingMethod::BAKED;
                else if (list2[0] == "BOILED")
                    method = MainCourse::CookingMethod::BOILED;
                else if (list2[0] == "FRIED")
                    method = MainCourse::CookingMethod::FRIED;
                else if (list2[0] == "STEAMED")
                    method = MainCourse::CookingMethod::STEAMED;
                else if (list2[0] == "RAW")
                    method = MainCourse::CookingMethod::RAW;

                bool gluten = list2[3] == "true"; //Converting string into boolean

                std::string d;
                std::string item;

                std::stringstream sideD(list2[2]);
                std::string eachD;
                std::vector<MainCourse::SideDish> side;
                std::vector<std::string> sideList;
                MainCourse::Category c;

                //Separate by | then separate by ; and adding it inside list
                while (std::getline(sideD, eachD, '|')) {
                    sideList = {};
                    std::stringstream d(eachD); 
                    while (std::getline(d, item, ':')) {
                        sideList.push_back(item);
                    }

                    //Converting string into cooking method
                    if (sideList[1] == "GRAIN")
                        c = MainCourse::Category::GRAIN;
                    else if (sideList[1] == "PASTA")
                        c = MainCourse::Category::PASTA;
                    else if (sideList[1] == "LEGUME")
                        c = MainCourse::Category::LEGUME;
                    else if (sideList[1] == "BREAD")
                        c = MainCourse::Category::BREAD;
                    else if (sideList[1] == "SALAD")
                        c = MainCourse::Category::SALAD;
                    else if (sideList[1] == "SOUP")
                        c = MainCourse::Category::SOUP;
                    else if (sideList[1] == "STARCHES")
                        c = MainCourse::Category::STARCHES;
                    else if (sideList[1] == "VEGETABLE")
                        c = MainCourse::Category::VEGETABLE;
                        
                        side.push_back({sideList[0], c});
                }

                Dish *m = new MainCourse(name, list1, std::stoi(preparationTime), std::stod(price), cuisine, method, list2[1], side, gluten);
                newOrder(m);
            }

            else if (dishType == "DESSERT") {
                Dessert::FlavorProfile flavor;

                //Converting string into flavor profile
                if (list2[0] == "UMAMI")
                    flavor = Dessert::FlavorProfile::UMAMI;
                else if (list2[0] == "BITTER")
                    flavor = Dessert::FlavorProfile::BITTER;
                else if (list2[0] == "SOUR")
                    flavor = Dessert::FlavorProfile::SOUR;
                else if (list2[0] == "SALTY")
                    flavor = Dessert::FlavorProfile::SALTY;
                else 
                    flavor = Dessert::FlavorProfile::SWEET;

                bool nuts = list2[2] == "true"; //Converting string into boolean

                Dish *d = new Dessert(name, list1, std::stoi(preparationTime), std::stod(price), cuisine, flavor, stoi(list2[1]), nuts);
                newOrder(d);
            }
        }
    }

    file.close();
}

/**
* Adjusts all dishes in the kitchen based on the specified dietary
accommodation.
* @param request A DietaryRequest structure specifying the dietary
accommodations.
* @post Calls the `dietaryAccommodations()` method on each dish in the
kitchen to adjust them accordingly.
*/
void Kitchen::dietaryAdjustment(const Dish::DietaryRequest& request) {
    for (int i = 0; i < getCurrentSize(); i++) {
        items_[i]->dietaryAccommodations(request);
    }
}

/**
* Displays all dishes currently in the kitchen.
* @post Calls the `display()` method of each dish.
*/
void Kitchen::displayMenu() const {
    for (int i = 0; i < getCurrentSize(); i++) {
        items_[i]->display();
    }
}

Kitchen::~Kitchen() {
    for (int i = 0; i < getCurrentSize(); i++) {
        delete items_[i];
        items_[i] = nullptr;
    }
    clear();
}

