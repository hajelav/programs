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
