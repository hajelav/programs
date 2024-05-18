/*
The Decorator Pattern is a structural design pattern that allows behavior to be added to individual objects, either statically or dynamically, without affecting the behavior of other objects from the same class. It is useful for extending the functionality of objects in a flexible and reusable way.

Components:
Component: Defines the interface for objects that can have responsibilities added to them dynamically.

Concrete Component: Represents the base object to which additional responsibilities can be added. It implements the component interface.

Decorator: Maintains a reference to a component object and conforms to the component interface. It adds its own behavior before and/or after delegating to the component.

Concrete Decorator: Adds new responsibilities to the component. It extends the functionality of the component by adding new operations or modifying existing ones.
*/

#include <iostream>
#include "AbstractBeverage.hpp"
#include "AbstractCondimentDecorator.hpp"
#include "ConcreteBeverageHouseBlend.hpp"
#include "ConcreteCondimentMocha.hpp"
#include "ConcreteCondimentWhip.hpp"

int main() {

    //create a beverage House Blend
    cout << "creating House Blend beverage" << endl;
    AbstractBeverage *houseBlend = new ConcreteBeverageHouseBlend();

    //Add Mocha to House Blend coffee
    cout << "Adding Mocha" << endl;
    houseBlend = new ConcreteConditmentMocha(houseBlend);
    cout << houseBlend->getDescription() << endl; 
    cout << houseBlend->cost() << endl;

    cout << "Adding whip cream" << endl;
    houseBlend = new ConcreteConditmentWhip(houseBlend);
    cout << houseBlend->getDescription() << endl;
    cout << houseBlend->cost() << endl;


    return 0;
}

using namespace std;
