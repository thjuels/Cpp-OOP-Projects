#include "SpecificAnimal.h"   
#include <iostream>
using namespace std;

Lion::Lion(const string& name, int age, double foodPerDay, int teethCount)
    : Carnivore(name, age, foodPerDay, teethCount) {}

void Lion::describe() const {
    cout << "Lion: " << name << " is " << age << " years old and eats " << foodPerDay << "kg of meat per day." 
         << " Teeth Count: " << getTeethCount() << endl;
}

// Tiger class


// Todo 3.1: Implement the Tiger class according to the Lion class and the sample output.
Tiger::Tiger(const string& name, int age, double foodPerDay, int teethCount)
    : Carnivore(name, age, foodPerDay, teethCount) {}

void Tiger::describe() const {
    cout << "Tiger: " << name << " is " << age << " years old and eats " << foodPerDay << "kg of meat per day." 
         << " Teeth Count: " << getTeethCount() << endl;
}




// Elephant class

// Todo 3.2: Implement the Elephant class according to the Lion class and the sample output. 
Elephant::Elephant(const string& name, int age, double foodPerDay, const string& favoritePlant, const string& habitatPreference):
Herbivore(name,age, foodPerDay, favoritePlant ,habitatPreference){}

void Elephant::describe() const {
    cout << "Elephant: " << name << " is " << age << " years old and eats " << foodPerDay << "kg of vegetation per day." 
            << " Favorite Plant: " << getFavoritePlant() << ", Habitat Preference: " << getHabitatPreference() <<endl;
}