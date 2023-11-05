#include "AbstractPizza.hpp"
#include "PizzaStoreFactory.hpp"
#include "ConcreteChicagoPizzaStore.hpp"
#include "ConcreteChicagoStyleCheesePizza.hpp"
#include "ConcreteChicagoStyleVeggiePizza.hpp"
#include "ConcreteNYPizzaStore.hpp"
#include "ConcreteNYStyleCheesePizza.hpp"
#include "ConcreteNYStyleVeggiePizza.hpp"

using namespace std;

int main() {

    //create a NY pizza store
    PizzastoreFactory *nyStore = new ConcreteNYPizzaStore();

    //create NY style cheese pizza
     nyStore->orderPizza("cheese");

    //create a Chicgo style pizza store
    PizzastoreFactory *chicagoStore = new ConcreteChicagoPizzaStore();
    //order a chicago pizza
    chicagoStore->orderPizza("veggie");


    return 0;
}


