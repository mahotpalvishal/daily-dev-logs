/**
Design a Car class that remembers both its identity and its current speed as it is driven.
The brand and model stay the same for the lifetime of the object, while the speed changes after
every acceleration or braking operation.

Implement the Car class:

Car(String brand, String model) creates a car with the given brand and model. Every new car starts at 0 km/h.

int accelerate(int amount) increases the current speed by amount, stores the result, and returns the new speed.

int brake(int amount) decreases the current speed by amount, stores the result, and returns the new speed. If braking would make the speed negative, 
set it to 0 instead.

int getSpeed() returns the car's current speed without changing it.

String describe() returns the latest state in the exact format "<brand> <model> at <speed> km/h".

All method calls operate on the same object. For example, accelerating by 20 and then by 15 produces a speed of 35, not 15. Braking by more than 35 then brings the car to a stop at 0.
*/
#include <iostream>
#include <string>

using namespace std;

class CAR{
  public:
    CAR(string brand_, string model_):brand{brand_}, model{model_}{
        this->speed = 0;
    }

    int accelerate(int const amount){
        if(amount > 0){
            this->speed += amount;
        }
        return this->speed;
    }

    int brake(int const amount){
        if(amount > 0){
            this->speed -= amount;
        }
        return this->speed;
    }

    int getSpeed(){
        return this->speed;
    }

    string describe(){
        return "------------------\nBrand: " + this->brand + "\nModel: " + this->model + "\nSpeed: " + to_string(speed) + "\n---------------------";
    }

    ~CAR(){

    }

  private:
    string brand;
    string model;
    int speed;
};

int main(){
    CAR* car = new CAR("Honda", "City XT");
    int curr = car->accelerate(94);
    curr = car->brake(15);
    cout << "Current Speed: " << car->getSpeed() << endl;
    curr = car->accelerate(1);
    curr = car->accelerate(-12);
    cout << car->describe() << endl;
    delete car;
    return 0;
}

