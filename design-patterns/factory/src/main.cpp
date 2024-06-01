#include "AbstractPizza.hpp"
#include "PizzaStoreFactory.hpp"
#include "ConcreteChicagoPizzaStore.hpp"
#include "ConcreteChicagoStyleCheesePizza.hpp"
#include "ConcreteChicagoStyleVeggiePizza.hpp"
#include "ConcreteNYPizzaStore.hpp"
#include "ConcreteNYStyleCheesePizza.hpp"
#include "ConcreteNYStyleVeggiePizza.hpp"
#include <iostream>
#include <memory>

using namespace std;

/**
 * The main function that demonstrates creating pizza stores and ordering pizzas.
 *
 * @return 0 indicating successful execution
 * @throws std::runtime_error if the pizza store or pizza creation fails
 */
int main() {

    //create a NY pizza store
    try {
        unique_ptr<PizzastoreFactory> nyStore = make_unique<ConcreteNYPizzaStore>();
        if (!nyStore) {
            throw std::runtime_error("Failed to create NY pizza store");
        }
        //create NY style cheese pizza
        nyStore->orderPizza("cheese");
        
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    //create a Chicgo style pizza store
    try {
        unique_ptr<PizzastoreFactory> chicagoStore = make_unique<ConcreteChicagoPizzaStore>();
        if (!chicagoStore) {
            throw std::runtime_error("Failed to create Chicgo pizza store");
        }
        //order a chicago pizza
        chicagoStore->orderPizza("veggie");
        
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}


