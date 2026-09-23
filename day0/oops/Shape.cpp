#include <iostream>
#include <string>

using namespace std;

class Shape{
  private:
    string name;

  public:
    Shape(string name):name{name}{
    }

    virtual void describe(){
        cout << "Shape: " << this->name << " Area: " << 0 << " Perimeter: " << 0 << endl;
    }

    virtual ~Shape() = default;

  protected:
    virtual float area(){
        return 0.0;
    }
    virtual float perimeter(){
        return 0.0;
    }
    string getName(){
        return this->name;
    }
};

class Circle: public Shape{
  private:
    float radius;

    float area(){
        return 3.14*this->radius*this->radius;
    }

    float perimeter(){
        return 3.14*2*this->radius;
    }

  public:
    Circle(string name, float radius_):Shape{name}, radius{radius_}{

    }

    void describe(){
        cout << "Shape: " << getName() << " Area: " << area() << " Perimeter: " << perimeter() << endl;
    }
};

class Rectangle: public Shape{
  private:
    float length;
    float breadth;

    float area(){
        return this->length*this->breadth;
    }

    float perimeter(){
        return 2*(this->length + this->breadth);
    }

  public:
    Rectangle(string name, float length_, float breadth_)
    :Shape{name}, length{length_}, breadth{breadth_}{

    }

    void describe(){
        cout << "Shape: " << getName() << " Area: " << area() << " Perimeter: " << perimeter() << endl;
    }
};

int main(){
    Shape* sh = new Shape("Random Shape");
    sh->describe();
    Circle* ci = new Circle("Circle", 4);
    ci->describe();
    Rectangle* rec = new Rectangle("Rectangle", 2, 4);
    rec->describe();

    delete sh;
    delete ci;
    delete rec;
    sh = nullptr;
    ci = nullptr;
    rec = nullptr;
    return 0;
}