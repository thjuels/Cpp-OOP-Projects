#include "ZooSystem.h"
#include "Animal.h"

ZooSystem::ZooSystem(int cap) : capacity(cap), size(0){
// To do4: Implement the ZooSystem constructor
    animals = new Animal*[cap];
}

void ZooSystem::listAllAnimals() const {
// To do4: Implement the listAllAnimals function
    // cout << "All animals in the zoo:" << endl;
    for (int i = 0; i < size; i++){
            animals[i]->describe();
    }
}

void ZooSystem::listCarnivores() const {
// To do4: Implement the listCarnivores function
    // cout << "Carnivores in the zoo:" << endl;
    for (int i = 0; i < size; i ++){
        if (animals[i]->getFoodType() == Meat){
            animals[i]->describe();
        }
    }
}

void ZooSystem::listHerbivores() const {
// To do4: Implement the listHerbivores function
    // cout << "Herbivores in the zoo:" << endl;
    for (int i = 0; i < size; i ++){
        if (animals[i]->getFoodType() == Vegetable){
            animals[i]->describe();
        }
    }
}


double ZooSystem::calculateMeatConsumption() const {
// Todo4: Implement the calculateMeatConsumption function
    double totalMeatConsumption = 0;
    for (int i = 0; i <  size; i++){
        if (animals[i]->getFoodType() == Meat){
            totalMeatConsumption += animals[i]->getFoodPerDay();
        }
    }

    return totalMeatConsumption;
}

double ZooSystem::calculateVegetableConsumption() const {
// Todo4: Implement the calculateVegetableConsumption function
    double totalVegetableConsumption = 0;
    for (int i = 0; i <  size; i++){
        if (animals[i]->getFoodType() == Vegetable){
            totalVegetableConsumption += animals[i]->getFoodPerDay();
        }
    }
    return totalVegetableConsumption;
}

void ZooSystem::addAnimal(Animal* animal){
    if (size < capacity){
        animals[size++] = animal;
        return;
    }
}

ZooSystem::~ZooSystem(){
    for (int i = 0; i < size; i++){
        delete animals[i];
    }
    delete [] animals;
}