#include "bst.h"
using namespace std;

/**
 * Returns true if "src" contains *any* words in "filterWords" (case-insensitive).
 * e.g.: 
 *   containAnyWords("Example string", "example") == true
 *   containAnyWords("Example string", "amp") == true
 *   containAnyWords("Example string", "this is a long sentence") == true  [contains 'a']
 *   containAnyWords("Example string", "no occurence") == false
*/
bool containAnyWords(string src, string filterWords) {
    auto strToLower = [](string& str) {
        for (char& c: str) c = tolower(c);
    };
    strToLower(src);
    strToLower(filterWords);
    size_t found = filterWords.find(' ');
    while (found != string::npos) {
        if (src.find(filterWords.substr(0, found)) != string::npos)
            return true;
        filterWords = filterWords.substr(found+1);
        found = filterWords.find(' ');
    }
    return src.find(filterWords) != string::npos;
}


// TASK 2.1: Filter::match(const Animal&) const
// Returns true if the animal satisfies ALL 3 conditions:
// - species (including breed) contains *any* of the words in speciesMatch
// - health description contains *any* of the words in healthMatch
// - vaccine status contains *all* of the non-empty strings in vaccineMatch
bool Filter::match(const Animal& a) const
{

    // TODO
    bool containsAll = true;
    for (int i = 0; i < VACCINE_TABLE_SIZE; ++i){
        //for all vaccines in the table if the vaccine isnt present return false
        //CURRENT IMPLEMENTATION WONT WORK, TWO EMPTY STRINGS WILL RETURN TRUE
        if (this->vaccineFilter[i] != ""){
            //if curerntly checking is empty string, skip
            //if not check if the vaccine isn't contained, 
            if (!a.getVaccinationStatus().hasVaccine(this->vaccineFilter[i])){
                //if vaccine not within, then it isn;t present 
                //so not match, so can return false
                containsAll = false;
                return false;
            }
        }
    }
    if (containsAll){
        if (containAnyWords(a.getSpecies(), this->speciesFilter)){
            if (containAnyWords(a.getHealthCondition().description, this->healthFilter)){
                return true;
            }
        }
    }

    return false;
}

// TASK 2.2: AnimalLLnode::print(unsigned int&, unsigned int&, const Filter&) const
// Print the animals in this linked list if it matches with the filter.
// The linked list should be maintained such that it is in decreasing ID order.
//
// E.g. (each node is shown as ID[Name]):
//      7[Cat] -> 6[Cat] -> 5[Dog] -> 3[Cat] -> 1[Bird] -> 0[Cat]
// should be printed in the following order using Filter{Name = "Cat"}: 
//      0[Cat]
//      3[Cat]
//      6[Cat]
//      7[Cat]
//
// The parameters ignoreCount and displayCount should be passed to the animal's display() function
void AnimalLLnode::print(unsigned int& ignoreCount, unsigned int& displayCount, const Filter& filter) const
{
    
    // TODO
    //recursively 
    if (next == nullptr && containAnyWords(animal->getSpecies(),filter.speciesFilter)){
        animal->display(ignoreCount,displayCount);
    } 
    else {
        //if not end, print next one, then this one
        //print next one
        if (next){
            if (containAnyWords(next->animal->getSpecies(),filter.speciesFilter)){
                next->print(ignoreCount,displayCount,filter);
            }
            if (containAnyWords(animal->getSpecies(),filter.speciesFilter)){
                animal->display(ignoreCount,displayCount);
            }
        }

    }

}

// TASK 2.3: BSTnode destructor
BSTnode::~BSTnode()  {
    
    // TODO
    AnimalLLnode* curr = head;
    AnimalLLnode* nextnode;

    while (curr != nullptr){
        nextnode = curr->next;
        delete curr;
        curr = nextnode;
    }
    
}

// TASK 2.4: BSTnode::addAnimal(const Animal* a)
// Add an animal to the linked list.
// Ensure the order is *decreasing ID*, e.g.: 7[Cat] -> 6[Cat] -> 5[Dog] -> 3[Cat] -> 1[Bird] -> 0[Cat]
// You may assume no two animals with the same ID will be added to a node
// (this also means you should not add the same animal to a node twice!)
void BSTnode::addAnimal(const Animal* a) {
    
    // TODO
    // AnimalLLnode* curr = head;
    // AnimalLLnode* prev;
    // if (head != nullptr){
    //     for (; curr; curr=curr->next){
    //         //if the ID being added is the largest yet, ie: replaces the head
    //         if (curr->animal->getID() == a->getID()){
    //             return;
    //         }
    //         else if (head->animal->getID() < a->getID()){
    //             curr = new AnimalLLnode(a,head);
    //             head = curr;
    //             return;
    //         }
    //         //somewhere in the middle
    //         else if (prev->animal->getID() > a->getID() && curr->animal->getID() < a->getID()){
    //             prev->next = new AnimalLLnode(a,curr);
    //             return;
    //         } 
    //         //the end
    //         else if (curr->next == nullptr && curr->animal->getID() > a->getID()){
    //             curr->next = new AnimalLLnode(a);
    //             return;
    //         }
    //         prev = curr;
    //     }
    // }
    AnimalLLnode* newNode = new AnimalLLnode(a);  // Create a new node

    if (head == nullptr || head->animal->getID() < a->getID()) {
        newNode->next = head;
        head = newNode;  // Update head to point to the new node
        return;
    }

    AnimalLLnode* curr = head;
    AnimalLLnode* prev = nullptr;

    while (curr != nullptr && curr->animal->getID() > a->getID()) {
        prev = curr;
        curr = curr->next;
    }

    if (curr != nullptr && curr->animal->getID() == a->getID()) {
        delete newNode;  // ID already exists, so delete the newly created node
        return;
    }

    if (prev != nullptr) {
        prev->next = newNode;
    } else {
        head = newNode;
    }

    newNode->next = curr;
}

// TASK 2.5: BSTnode::addAnimal(const Animal* a)
// Remove an animal from the linked list.
// Ensure the order of the other animals are kept.
// If the animal does not exist, do nothing.
// If there are no animals left after removing, set head to nullptr.
void BSTnode::removeAnimal(const Animal* a) {
    
    // TODO
    //don't deallocate the animal object
    //as it is now, it isn't deallocating
    if (head != nullptr){
        //if at head, should also handle case with only 1 element
        if (head->animal->getID() == a->getID()){
            head = head->next;
            return;
        }
        AnimalLLnode* curr = head;
        AnimalLLnode* prev = nullptr;

        while (curr != nullptr && curr->animal->getID() != a->getID()) {
            prev = curr;
            curr = curr->next;
        }

        if (curr == nullptr) {
            return; // Animal with the given ID not found
        }

        prev->next = curr->next;

    }

}



// TASK 3.1: BST destructor
BST::~BST() {
    
    // TODO
    delete root;
}

// TASK 3.2: BST::findMinNode()
// Optional task, but may be needed for BST::remove().
// Return a reference to the BSTnode* of the min node in this BST.
BSTnode*& BST::findMinNode()
{
    
    // TODO
    if (root->left.root == nullptr){
        return root;
    }
    else {
        return root->left.findMinNode();
    }
}

// TASK 3.3: BST::insert(const Animal* a)
// Insert an animal 'a' to the BST.
// Use the comparator "data member function" to compare the animal with the current node:
// - If 'a' is "less than" the current node, insert it to the left subtree.
// - If 'a' is "more than" the current node, insert it to the right subtree.
// - If 'a' "equals" the current node, insert it into this node's linked list.
// - Otherwise, if the node is empty, create a new node using 'a'.
void BST::insert(const Animal* a)
{
    
    // TODO
    //comparator returns -1 if a1 < a2, 0 if a1 == a2, and 1 if a1 > a2
    if (isEmpty()){
        root = new BSTnode{a,nullptr};
    }
    else if (comparator(a,root->head->animal) < 0){
        root->left.insert(a);
    } 
    else if (comparator(a,root->head->animal) > 0){
        root->right.insert(a);
    } 
    else if (comparator(a,root->head->animal) == 0){
        root->addAnimal(a);
    }
}

// TASK 3.4: BST::remove(const Animal* a)
// Remove an animal 'a' from the BST
// Follow the same steps in BST::insert() to locate the node to remove.
// Removal strategy is similar to lecture notes example with a few differences:
// - If the node is not found, do nothing.
// - If the node is found, remove the animal from its linked list. If it makes the linked list become empty,
//   remove the node:
//   + If the node contains 0 or 1 child, move the children node to current root, and deallocate the old root.
//   + Else, *move* the linked list from the right subtree's min node to current root, and deallocate right subtree's min node.
void BST::remove(const Animal* a)
{
    
    // TODO
    if (isEmpty()){
        return;
    }
    else if (comparator(a,root->head->animal) < 0){
        //if a < current
        root->left.remove(a);
    } 
    else if (comparator(a,root->head->animal) > 0){
        //if a > current
        root->right.remove(a);
    } 
    else if (comparator(a,root->head->animal) == 0){
        //if node found
        if (root->head->animal){ //if not empty
            //will look for the animal and remove from linked list if found
            //if not found, nothing will happen, if found will be deleted
            root->removeAnimal(a);  //deleting
            //if deleted, and list now empty, that node must be deallocated
            if (root->head == nullptr){ 
                // check if list is empty - list IS empty
                if (root->left.root && root->right.root){
                    //has 2 children
                     //find minimum node from right subtree
                    BSTnode*& minNode = root->right.findMinNode();
                    BSTnode* temp = minNode;
                    // BSTnode* temp = root;
                    //assign the min node to root
                    minNode = minNode->right.root;
                    root->head = temp->head;
                    temp->head = nullptr;
                    temp->right.root = nullptr;
                    //remove minnode
                    delete temp;

                } 
                else {
                    //has 0 or 1 child
                    if (root->left.root){
                        //if left root exists -> implied right root doesn't exist
                        //create temp object
                        BSTnode* temp = root;
                        //reassign root to point to left side
                        root = root->left.root;
                        //make left side not exist so it isn't all deallocated
                        temp->left.root = nullptr;
                        delete temp;
                    } 
                    else if (root->right.root){
                        //if right root exists
                        BSTnode* temp = root;
                        root = root->right.root;
                        temp->right.root = nullptr;
                        delete temp;
                    } 
                    else {
                        //0 children
                        delete root;
                    }
                }
            }
        }
    }
    

}

// TASK 3.5: BST::print(unsigned int&, unsigned int&, const Filter&) const
// Print the BST using in-order traversal.
//
// E.g.: Consider a BST containing animals sorted by species name:
//                      8[Reptile, Healthy] -> 6[Reptile, Bad]
//                   5[Rabbit, Critical]
// 7[Dog, Healthy] -> 3[Dog, Healthy]
//                      9[Cat, Bad] -> 4[Cat, Healthy] -> 2[Cat, Very poor]
//              1[Bird, Healthy]
// 
// should print in the following order using Filter{Health = "Healthy"}:
//      1[Bird, Healthy]
//      4[Cat, Healthy]
//      3[Dog, Healthy]
//      7[Dog, Healthy]
//      8[Reptile, Healthy]
void BST::print(unsigned int& ignoreCount, unsigned int& displayCount, const Filter& filter) const
{
    
    // TODO
    // if (root->head){
    //     if (containAnyWords(root->left.root->head->animal->getHealthCondition().description,filter.healthFilter)){
    //         root->left.print(ignoreCount,displayCount,filter);
    //     }
    //     if (containAnyWords(root->head->animal->getHealthCondition().description,filter.healthFilter)){
    //         print(ignoreCount,displayCount,filter);
    //     }
    //     if (containAnyWords(root->right.root->head->animal->getHealthCondition().description,filter.healthFilter)){
    //         root->right.print(ignoreCount,displayCount,filter);
    //     }
    // }
    if (root->head){
            root->left.print(ignoreCount,displayCount,filter);
            root->head->print(ignoreCount,displayCount,filter);
            root->right.print(ignoreCount,displayCount,filter);
    }
}
