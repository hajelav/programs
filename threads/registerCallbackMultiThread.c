
/*
 *  Consider a time scale. At random points in time, there will be register callback functions invoked. The callback functions are waiting on an event that will be fired at some point in time. By the time the caller registers the callback, if the event had happened, the caller should execute the function, otherwise, the callback needs to be registered and executed once the event has fired. After the event has fired, any callback dependent on the event can be executed without having to register
 */

#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>

//function pointer which takes void* as argument and returns void*
typedef void (*CB)(void);

//creating an event, an event can be just ca callback for now
typedef struct event {
    CB cb;
    struct event *next;
    int time;
}EVENT;

//structure for event handler
typedef struct eventHandler {
    bool isEventFired;
    EVENT *event;
} EHANDLER;


// the caller initializes the event
EVENT* initEvent(CB cb) {

    EVENT* e;
    e = (EVENT*)malloc(sizeof(EVENT));
    if(!e)
        return NULL;
    e->cb = cb;
    e->time = 0;
    e->next = NULL;

    return e;
}

EHANDLER* initEventHandler() {

    EHANDLER *eh;
    eh = (EHANDLER*)malloc(sizeof(EHANDLER));
    if(!eh)
        return NULL;
    eh->isEventFired = false;
    eh->event = NULL;
    return eh;
}

void invoke(EVENT *e) {

    if(e){
        (*e->cb)(); // calling the function using function pointer
    }
}

void handleEvents(EHANDLER *eh) {

    EVENT *trav;

    if(eh && eh->event) {
        trav = eh->event;
        
        while(trav) {

            invoke(trav);// invoke the cb function
            eh->event = trav->next; // delete the event from the list
            free(trav);// free the event node
            trav = eh->event;
        }

    }
}

//when the event is fired, we just set the flag as true
void fire(EHANDLER *eh) {
    if(eh)
        eh->isEventFired = true;

    //delete all the events in the event list
    handleEvents(eh);
}

// register event : add the event to the event handler list;
void registerEvent(EHANDLER *eh, EVENT *e) {

    EVENT *temp;
    if(!eh || !e)
        return;

    //if the fire event has alredy occured, the we just invoke the the event
    if(eh->isEventFired) {
        invoke(e);
    } else {
        //add events in a link list
        temp = eh->event;
        eh->event = e;
        e->next = temp;
    }
}


/*****************************************************************************************************************************************/

void cb1() {
    printf("inside cb1\n");
}
void cb2() {
    printf("inside cb2\n");
}
void cb3() {
    printf("inside cb3\n");
}
void cb4() {
    printf("inside cb4\n");
}
void cb5() {
    printf("inside cb5\n");
}


int main() {

    CB f;
    EHANDLER *eh;
    EVENT *e;

    //initialize event handler system
    eh = initEventHandler();


    // initialize events
    f = &cb1;
    e = initEvent(f);
    registerEvent(eh, e);

    f = &cb2;
    e = initEvent(f);
    registerEvent(eh, e);

    fire(eh);

    f = &cb3;
    e = initEvent(f);
    registerEvent(eh, e);
    return 0;
}















    


