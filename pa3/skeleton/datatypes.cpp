#include "datatypes.h"
#include <iostream>
using namespace std;

/**
 * Returns the ASCII sum of all characters in a string
 * To be used as the indexing key of a string into the hash table,
 * e.g. k = sumStringChars(str)
*/
unsigned int sumStringChars(const string& str) 
{
    unsigned int sum = 0;
    for (unsigned int i=0; i<str.length(); ++i)
        sum += static_cast<unsigned int>(str[i]);
    return sum;
}


// TASK 1.1: VaccinationStatus default constructor
VaccinationStatus::VaccinationStatus():vaccineHashTable{},numVaccines(0) {

    // TODO
    for (int i = 0; i < VACCINE_TABLE_SIZE; ++i){
        vaccineHashTable[i] = "";
    }
}

// TASK 1.2: VaccinationStatus::addVaccine(const string&)
// - If the table is not at least half empty, output the first error message and return.
// - Else, calculate k = sumStringChars(v) and hash(k) = k % VACCINE_TABLE_SIZE
//   Follow the quadratic probing formula: h(i) = [hash(k) + i^2] % VACCINE_TABLE_SIZE
//   to add the vaccine to the table.
//   If the vaccine already exists, output the second error message and return.
void VaccinationStatus::addVaccine(const string& v)
{
    if (numVaccines >= VACCINE_TABLE_SIZE/2 /* TODO: Table is not half-empty */) { // numvaccines > 23/2
        cout << "This system does not support having taken more than " << numVaccines << " vaccines." << endl;
        return;
    }
    //alternative to the function within loop
    // if (hasVaccine(v)) {
    //         cout << "This animal has already taken " << v << "." << endl;
    //         return;
    // }
    // TODO: Quadratic probing
    unsigned int k = sumStringChars(v) % VACCINE_TABLE_SIZE;
    for (int i = 0; i < VACCINE_TABLE_SIZE; ++i){
        if (vaccineHashTable[(k + i*i) % VACCINE_TABLE_SIZE] == v) {
            cout << "This animal has already taken " << v << "." << endl;
            return;
        }
        else if (vaccineHashTable[(k + i*i) % VACCINE_TABLE_SIZE] == "") {
            vaccineHashTable[(k + i*i) % VACCINE_TABLE_SIZE] = v;
            numVaccines++;
            return;
        }
    }


    

    cout << "SOME OTHER ERROR" << endl;
    return;

    // TODO: Quadratic probing
}

// TASK 1.3: VaccinationStatus::hasVaccine(const string&) const
// Returns true if the vaccine exists in the table, false otherwise
bool VaccinationStatus::hasVaccine(const string& v) const
{
    // TODO
    unsigned int hash = (sumStringChars(v) % VACCINE_TABLE_SIZE);
    //probe into hash table using same method as TASK 1.2, and check if it exists
    for (int i = 0; i < VACCINE_TABLE_SIZE; ++i){
        if (vaccineHashTable[(hash + i*i) % VACCINE_TABLE_SIZE] == v){
            return true;
        }
    }

    return false;
}


/**
 * Returns a value representing the current hash table
 * Used for comparing 2 animals with different vaccination status
*/
unsigned int VaccinationStatus::getTotalHashValue() const 
{
    unsigned int hash = 0;
    for (unsigned int i=0; i<VACCINE_TABLE_SIZE; ++i)
        hash += sumStringChars(vaccineHashTable[i]);
    return hash * numVaccines;
}
