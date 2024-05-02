#include "adoptionCenter.h"
#include <iostream>
using namespace std;


// TASK 4.1: AdoptionCenter constructor
// Initialize all data members to represent an empty database.
// The BSTs need to be initialized with their comparison functions:
// - NAME: Sort by species name (including breed), in increasing lexicographic order
// - AGE: Sort by increasing age
// - HEALTH: Sort by increasing health severity
// - VACCINE: Sort by increasing VaccinationStatus total hash value
//
// The comparison functions when comparing the left animal (a1) and right animal (a2) should return:
// - a negative value if a1 < a2
// - 0 if a1 == a2
// - a positive value if a1 > a2
//
// Hints:
// - You can write lambda functions to pass into the BST constructors
// - For comparing strings, look up the documentation for std::string::compare()
// - Be careful when performing arithmetic calculations with unsigned int
AdoptionCenter::AdoptionCenter(): animals(nullptr),numAnimals(0), 
sortedAnimals {BST{[](const Animal* animal1, const Animal* animal2)
                        {return animal1->getSpecies().compare(animal2->getSpecies());}},
            BST{[](const Animal* animal1, const Animal* animal2){
                if (animal1->getAge() < animal2->getAge()){
                    return -1;
                } else if (animal1->getAge() > animal2->getAge()){
                    return 1;
                } else {
                    return 0;
                }
            }},
            BST{[](const Animal* animal1, const Animal* animal2){
                if (animal1->getHealthCondition().severity < animal2->getHealthCondition().severity){
                    return -1;
                } else if (animal1->getHealthCondition().severity > animal2->getHealthCondition().severity){
                    return 1;
                } else {
                    return 0;
                } 
            }},
            BST{[](const Animal* animal1, const Animal* animal2){
                if (animal1->getVaccinationStatus().getTotalHashValue() < animal2->getVaccinationStatus().getTotalHashValue()){
                    return -1;
                } else if (animal1->getVaccinationStatus().getTotalHashValue() > animal2->getVaccinationStatus().getTotalHashValue()){
                    return 1;
                } else {
                    return 0;
                } 

            }}}{
    
    // TODO
    // sortedAnimals {BST{[](const Animal* animal1, const Animal* animal2)
    //                     {return AnimalComparator}},
    //                 BST{[](const Animal* animal1, const Animal* animal2)
    //                     {return AnimalComparator}},
    //                 BST{[](const Animal* animal1, const Animal* animal2)
    //                     {return AnimalComparator}},
    //                 BST{[](const Animal* animal1, const Animal* animal2)
    //                     {return AnimalComparator}} };
}

// TASK 4.2: AdoptionCenter destructor
// Deallocate any dynamic memory in this class.
// Hint: This is where the animals should be deallocated.
AdoptionCenter::~AdoptionCenter() {
    
    // TODO
    // POSSIBLE DOUBLE DELETE
    //shouldnt be, as this deletes animal array,
    //deleting bst doesn't deallocate any memory so no
    for (int i = 0; i < numAnimals; ++i){
        delete animals[i];
    }
    delete [] animals;
}

// TASK 4.3: AdoptionCenter::addAnimal(Animal*)
// Add an animal to the dynamic-length array data member,
// by increasing its size by 1 and increment numAnimals accordingly.
// Add the animal to the end of the array, 
// such that the array is sorted by increasing ID (assume we only add increasing IDs)
// The animal should also be added to the 4 BSTs.
void AdoptionCenter::addAnimal(Animal* a) {
    
    // TODO
    if (a){
        Animal** temp = new Animal*[++numAnimals];
        for (int i = 0; i < numAnimals - 1; ++i){
            temp[i] = animals[i];
        }
        temp[numAnimals-1] = a;
        delete [] animals;
        animals = temp;

        for (int i = 0; i < ID; ++i){
            sortedAnimals[i].insert(a);
        }
    }
}

// TASK 4.4: AdoptionCenter::removeAnimal(unsigned int)
// Remove an animal from the database by ID.
// If the ID does not exist, do nothing.
// Otherwise, resize the array to decrease its size by 1,
// copy the non-deleted animals over and decrement numAnimals accordingly.
// The animal should also be removed from the 4 BSTs.
// Finally, return true if the animal was successfully removed.
bool AdoptionCenter::removeAnimal(unsigned int id) {
    
    // TODO
    bool exists = false;
    unsigned int index = 0;
    for (; index < numAnimals; ++index){
        if (animals[index]->getID() == id){
            exists = true;
            break;
        }
    }
    if (exists){
        Animal** temp = new Animal*[numAnimals-1];
        for (int i = 0, k = 0; i < numAnimals - 1; ++i){
            if (i >= index){
                //if at position to delete
                // increment other variable, then continue on 
                ++k;
                temp[i] = animals[k];
            }
            else {
                temp[i] = animals[k];
                ++k;
            }
        }
        //decrement
        numAnimals--;
        //remove from all animals using pointer to that animal
        for (int i = 0; i < ID; ++i){
            sortedAnimals[i].remove(animals[index]);
        }
        //deallocate - delete that object
        delete animals[index]; //quesitonable whether to deallocate???
        //delete dynamic array only
        delete [] animals;
        //recopy new array of size - 1 
        animals = temp;
        return true;
    }

    return false;
}

// TASK 4.5: AdoptionCenter::incrementAge()
// Increment the age of all animals by 1.
void AdoptionCenter::incrementAge()
{
    
    // TODO
    for (int i = 0 ; i < numAnimals; ++i){
        animals[i]->incrementAge();
    }

}

// TASK 4.6: AdoptionCenter::setAnimalHealthCondition(unsigned int, const HealthCondition&)
// Modify the animal with the specified ID's health condition to the provided parameter.
// If the animal does not exist, do nothing.
// Else, ensure the BST for health condition is sorted after the modification.
void AdoptionCenter::setAnimalHealthCondition(unsigned int id, const HealthCondition& h)
{
    
    // TODO
    bool exists = false;
    unsigned int index = 0;
    //find if the index exists
    for (; index < numAnimals; ++index){
        if (animals[index]->getID() == id){
            exists = true;
            break;
        }
    }
    if (exists){
        sortedAnimals[2].remove(animals[index]);
        animals[index]->setHealthCondition(h);
        sortedAnimals[2].insert(animals[index]);
    }

    return;
}

// TASK 4.7: AdoptionCenter:addAnimalVaccine(unsigned int, const string&)
// Add the provided vaccine to the animal specified by ID.
// If the animal does not exist, do nothing.
// Else, ensure the BST for vaccine status is sorted after the modification.
void AdoptionCenter::addAnimalVaccine(unsigned int id, const string& v)
{
    
    // TODO
    bool exists = false;
    unsigned int index = 0;
    for (; index < numAnimals; ++index){
        if (animals[index]->getID() == id){
            exists = true;
            break;
        }
    }
    if (exists){
        sortedAnimals[3].remove(animals[index]);
        animals[index]->addVaccine(v);
        sortedAnimals[3].insert(animals[index]);
    }
}

// TASK 4.8: AdoptionCenter::setAnimalSpecialNeeds(unsigned int, const std::string&)
// Modify the animal with the specified ID's special needs to the provided parameter.
// If the animal does not exist, do nothing.
void AdoptionCenter::setAnimalSpecialNeeds(unsigned int id, const std::string& n)
{
    
    // TODO
    bool exists = false;
    unsigned int index = 0;
    for (; index < numAnimals; ++index){
        if (animals[index]->getID() == id){
            exists = true;
            break;
        }
    }
    if (exists){
        animals[index]->setSpecialNeeds(n);
    }
}


/**
 * Provided function to display the animals in the database.
 * @param start: Starting index to print (e.g. start == 5: ignore the first 5 animals that matches the filter)
 * @param stop: Index to stop printing (e.g. stop == 10: print until the 10th animal [exclusive] that matches the filter)
 * @param filter: Only print animals that match this filter.
 * @param criteria: Sorting criteria. By default sort by ID (assuming animals are added in increasing ID)
*/
void AdoptionCenter::display(unsigned int start, unsigned int stop, const Filter& filter, SortCriteria criteria) const {
    unsigned int displayCount = stop - start;
    if (criteria == ID) {
        for (unsigned int i=0; i<numAnimals; ++i) {
            if (filter.match(*animals[i])) {
                animals[i]->display(start, displayCount);
            }
        }
    }
    else {
        sortedAnimals[criteria].print(start, displayCount, filter);
    }
}

/**
 * Provided function to print the vaccines an animal, specified by ID, has taken.
*/
void AdoptionCenter::displayPetVaccines(unsigned int id) const
{
    unsigned int i = 0;
    for (; i<numAnimals; ++i) {
        if (animals[i]->getID() == id) {
            VaccinationStatus v = animals[i]->getVaccinationStatus();
            if (v.numVaccines == 0)
                cout << "No vaccines found." << endl;
            else
                for (unsigned int j = 0; j < VACCINE_TABLE_SIZE; ++j) {
                    if (v.vaccineHashTable[j].length() > 0)
                        cout << v.vaccineHashTable[j] << endl;
                }
            return;
        }
    }
    if (i == numAnimals)
        cout << "ID not found in database." << endl;
}
