#include "AbstractComponent.hpp"
#include "CompositeComponent.hpp"
#include "LeafComponent.hpp"

int main() {

    //create leaf components
    AbstractComponent *leaf1 = new LeafComponent("leaf1");
    AbstractComponent *leaf2 = new LeafComponent("leaf2");
    AbstractComponent *leaf3 = new LeafComponent("leaf3");


    //create a composite object and add leafs to it
    CompositeComponent *composite = new CompositeComponent("composite");
    composite->add(leaf1);
    composite->add(leaf2);

    //create another composite object called root
    CompositeComponent *root = new CompositeComponent("root");

    //add a composite objext (composite) previously created
    root->add(composite);
    //add leaf3 to root 
    root->add(leaf3);

    /*
                  root
                /      \
              leaf3    composite  
                       /        \
                    leaf1     leaf2
    */

   //call the operation of root and it will recursively call all the operation on all nodes
   root->operation();





    return 0;
}