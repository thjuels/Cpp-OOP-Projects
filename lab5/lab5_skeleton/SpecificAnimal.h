#include "Animal.h"

// ======== Carnivore class ========
class Lion : public Carnivore {
// Todo 3.1: Implement the Lion class
    public:
        Lion(const string& name, int age, double foodPerDay, int teethCount);
        void describe() const override;
};

class Tiger : public Carnivore {
// Todo 3.1: Implement the Tiger class
    public:
        Tiger(const string& name, int age, double foodPerDay, int teethCount);
        void describe() const override;
};


// ======== Herbivore class ========
class Elephant : public Herbivore {
// Todo 3.2: Implement the Elephant class
    public:
        Elephant(const string& name, int age, double foodPerDay, const string& favoritePlant, const string& habitatPreference);
        void describe() const override;
};

