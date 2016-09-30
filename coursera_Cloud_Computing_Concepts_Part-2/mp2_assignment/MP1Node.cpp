/**********************************
 * FILE NAME: MP1Node.cpp
 *
 * DESCRIPTION: Membership protocol run by this Node.
 * 				Definition of MP1Node class functions.
 **********************************/

#include "MP1Node.h"
/*
 * Note: You can change/add any functions in MP1Node.{h,cpp}
 */

/**
 * Overloaded Constructor of the MP1Node class
 * You can add new members to the class if you think it
 * is necessary for your logic to work
 */
MP1Node::MP1Node(Member *member, Params *params, EmulNet *emul, Log *log, Address *address) {

    for( int i = 0; i < 6; i++ ) {
        NULLADDR[i] = 0;
    }
    this->memberNode = member;
    this->emulNet = emul;
    this->log = log;
    this->par = params;
    this->memberNode->addr = *address;
}

/**
 * Destructor of the MP1Node class
 */
MP1Node::~MP1Node() {}

/**
 * FUNCTION NAME: recvLoop
 *
 * DESCRIPTION: This function receives message from the network and pushes into the queue
 * 				This function is called by a node to receive messages currently waiting for it
 */
int MP1Node::recvLoop() {
    if ( memberNode->bFailed ) {
        return false;
    }
    else {
        //cout << "message received" <<endl;
        return emulNet->ENrecv(&(memberNode->addr), enqueueWrapper, NULL, 1, &(memberNode->mp1q));
    }
}

/**
 * FUNCTION NAME: enqueueWrapper
 *
 * DESCRIPTION: Enqueue the message from Emulnet into the queue
 */
int MP1Node::enqueueWrapper(void *env, char *buff, int size) {
    Queue q;
    return q.enqueue((queue<q_elt> *)env, (void *)buff, size);
}

/**
 * FUNCTION NAME: nodeStart
 *
 * DESCRIPTION: This function bootstraps the node
 * 				All initializations routines for a member.
 * 				Called by the application layer.
 */
void MP1Node::nodeStart(char *servaddrstr, short servport) {
    Address joinaddr;
    joinaddr = getJoinAddress();

    // Self booting routines
    if(initThisNode(&joinaddr) == -1 ) {
#ifdef DEBUGLOG
        log->LOG(&memberNode->addr, "init_this node failed. Exit.");
#endif
        exit(1);
    }

    if( !introduceSelfToGroup(&joinaddr) ) {
        finishUpThisNode();
#ifdef DEBUGLOG
        log->LOG(&memberNode->addr, "Unable to join self to group. Exiting.");
#endif
        exit(1);
    }
    return;
}

/**
 * FUNCTION NAME: initThisNode
 *
 * DESCRIPTION: Find out who I am and start up
 */
int MP1Node::initThisNode(Address *joinaddr) {
    /*
     * This function is partially implemented and may require changes
     */
    memberNode->bFailed = false;
    memberNode->inited = true;
    memberNode->inGroup = false;
    // node is up!
    memberNode->nnb = 0;
    memberNode->heartbeat = 0;
    memberNode->pingCounter = TFAIL;
    memberNode->timeOutCounter = -1;
    initMemberListTable(memberNode);

    //add the enty for self in the membership table when the node is startted
    initMemberListTableWithSelf(memberNode, &memberNode->addr);

    return 0;
}


/**
 * FUNCTION NAME: introduceSelfToGroup
 *
 * DESCRIPTION: Join the distributed system
 */
    int MP1Node::introduceSelfToGroup(Address *joinaddr) {
        
        if ( 0 == memcmp((char *)&(memberNode->addr.addr), (char *)&(joinaddr->addr), sizeof(memberNode->addr.addr))) {
            // I am the group booter (first process to join the group). Boot up the group
#ifdef DEBUGLOG
            log->LOG(&memberNode->addr, "Starting up group...");
#endif
            memberNode->inGroup = true;
            //printMemberListTable(memberNode->memberList);
        }
        else {
            //when any node joins the group it tries to send JOINREQ messsage to the introducer(joinaddr)
            sendMemberListTableToAddress(memberNode, joinaddr, JOINREQ);
            memberNode->inGroup = true;
            printMemberListTable(memberNode->memberList);
        }
        return 1;
    }

/**
 * FUNCTION NAME: finishUpThisNode
 *
 * DESCRIPTION: Wind up this node and clean up state
 */
    int MP1Node::finishUpThisNode(){

        //set the status of node as false once it exits the group
        memberNode->inGroup = false;
        return 0;
    }

/**
 * FUNCTION NAME: nodeLoop
 *
 * DESCRIPTION: Executed periodically at each member
 * 				Check your messages in queue and perform membership protocol duties
 */

void MP1Node::nodeLoop() {

    if (memberNode->bFailed) {
        return;
    }

    /*
     *increment the heartbeat counter for the node at regular intervals, this is 
     *to make sure that the members are alive in a group
     */
    updateHearbeatCounter();
    // Check my messages
    checkMessages();

    // Wait until you're in the group...
    if( !memberNode->inGroup ) {
        return;
    }

    // ...then jump in and share your responsibilites!
    nodeLoopOps();

    return;
}

/**
 * FUNCTION NAME: checkMessages
 *
 * DESCRIPTION: Check messages in the queue and call the respective message handler
 */
void MP1Node::checkMessages() {
    void *ptr;
    int size;

    // Pop waiting messages from memberNode's mp1q
    while ( !memberNode->mp1q.empty() ) {
        ptr = memberNode->mp1q.front().elt;
        size = memberNode->mp1q.front().size;
        memberNode->mp1q.pop();
        recvCallBack((void *)memberNode, (char *)ptr, size);
    }
    return;
}

/**
 * FUNCTION NAME: recvCallBack
 *
 * DESCRIPTION: Message handler for different message types
 */
        bool MP1Node::recvCallBack(void *env, char *data, int size ) {

            Member *memberNode;
            vector<MemberListEntry> memberList;
            size_t memListSize;
            MessageHdr *msg;

            memberNode = (Member*)(env);
            msg  = (MessageHdr *)data;

            memListSize =  ((size_t)size - sizeof(*msg))/sizeof(memberList);
            memberList.resize(memListSize);

            memcpy(&memberList[0], msg+1, (size_t)size - sizeof(*msg));

            /*
             *   we have received the msg, 
             *   -add the entry into memberlist table of the process which received it,
             *   if the entry has not already been added else just update the table(ie heartbeat and timestamp)
             */
            mergeMemberListTable(memberNode, memberList);
            return true;
        }
/*
 *FUNCTION NAME: nodeLoopOps
 *DESCRIPTION: Check if any node hasn't responded within a timeout period and then delete
 *the nodes Propagate your membership list
 */
void MP1Node::nodeLoopOps() {

    checkMemberFailure(memberNode);
    sendMemberListTableToNeighbors(memberNode);
    //printMemberListTable(memberNode->memberList);
    return;
}

/**
 * FUNCTION NAME: isNullAddress
 *
 * DESCRIPTION: Function checks if the address is NULL
 */
        int MP1Node::isNullAddress(Address *addr) {
            return (memcmp(addr->addr, NULLADDR, 6) == 0 ? 1 : 0);
        }

/**
 * FUNCTION NAME: getJoinAddress
 *
 * DESCRIPTION: Returns the Address of the coordinator
 */
                Address MP1Node::getJoinAddress() {
                    Address joinaddr;

                    memset(&joinaddr, 0, sizeof(Address));
                    *(int *)(&joinaddr.addr) = 1;
                    *(short *)(&joinaddr.addr[4]) = 0;

                    return joinaddr;
                }

/**
 * FUNCTION NAME: initMemberListTable
 *
 * DESCRIPTION: Initialize the membership list
 */
    void MP1Node::initMemberListTable(Member *memberNode) {
        memberNode->memberList.clear();
    }


/**
 * FUNCTION NAME: printAddress
 *
 * DESCRIPTION: Print the Address
 */
void MP1Node::printAddress(Address *addr)
{
    printf("%d.%d.%d.%d:%d\n",  addr->addr[0],addr->addr[1],addr->addr[2],
            addr->addr[3], *(short*)&addr->addr[4]) ;    
}

int MP1Node::getIdFromAddress(Address *addr) {

    int id = *(int*)(&(addr->addr));
    return id;
}

int MP1Node::getPortFromAddress(Address *addr) {

    short port = *(short*)(&addr->addr[4]);
    return port;
}

/*
 *this function checks if the address (id, port) is present in memberNode and 
 *returns its index in the membership table
 */
int MP1Node::searchMemberListTable(Member *memberNode, int id, int port) {
    int idM, portM;

    if(!memberNode)
        return -1;

    for(unsigned int i = 0; i<memberNode->memberList.size();i++){
        idM = memberNode->memberList[i].getid();
        portM = memberNode->memberList[i].getport();

        if(id == idM && port == portM)
            return i;
    }
    return -1;
}

//given a port and id, return an adddress
Address MP1Node::getAddressFromPortAndId(int id, int port) {
    Address addr;

    memset(&addr, 0, sizeof(Address));
    *(int *)(&addr.addr) = id;
    *(short *)(&addr.addr[4]) = port;

    return addr;
}

/*
 *this function is updates the membership table of a node(memberNode) when it receives 
 *memberlist table(memberList) from another node
 */
void MP1Node::updateMemberListTable(Member *memberNode, vector<MemberListEntry> memberList) {

    int id, port;
    Address addr;
    MemberListEntry memberListEntry; 
    if(!memberNode)
        return;

    //loop through the received membership table
    for(unsigned int i = 0; i<memberList.size();i++){
        id = memberList[i].getid();
        port = memberList[i].getport();

        memset(&addr, 0, sizeof(Address));
        *(int *)(&addr.addr) = id;
        *(short *)(&addr.addr[4]) = port;

        //if you dont find an entry in node's memberlist, then add it
        if(searchMemberListTable(memberNode, id, port) < 0) {
            memberListEntry.setid(id);
            memberListEntry.setport(port);
            memberNode->memberList.push_back(memberListEntry);

            memberNode->nnb = memberNode->nnb + 1;
            log->logNodeAdd(&memberNode->addr, &addr);
        }
    }
}

void MP1Node::initMemberListTableWithSelf(Member *memberNode, Address *addr) {

    int id, port;

     id = *(int*)(&addr->addr);
     port = *(short*)(&addr->addr[4]);

    MemberListEntry memberList; 
    memberList.setid(id);
    memberList.setport(port);

    //add the entry into the membership list
    memberNode->myPos = memberNode->memberList.begin();
    memberNode->memberList.push_back(memberList);

    //update the heartbeat counter when the node starts
    updateHearbeatCounter();

}

void MP1Node::printMemberListTable(vector<MemberListEntry> memberList) {

    long heartbeat;
    int id, port, timestamp;
    char hb[256];
    char ts[256];

    for(unsigned int i = 0; i< memberList.size();i++){

        heartbeat = memberList[i].getheartbeat();
        timestamp = memberList[i].gettimestamp();
        id = memberList[i].getid();
        port = memberList[i].getport();

        sprintf(hb, "%ld", heartbeat);
        sprintf(ts, "%d", timestamp);
        cout <<"id="<<id<<"|"<<"port="<<port<<"|"<<"heartbeat="<<heartbeat<<"|"<<"timestamp="<<timestamp<<endl;
    }
}


void MP1Node::sendMemberListTableToAddress(Member *memberNode, Address *toAddr, enum MsgTypes msgtype) {
    MessageHdr *msg;
    char  *buf;
    char s[1024];
    size_t memListSize;

    memListSize = sizeof(memberNode->memberList)*memberNode->memberList.size();

    buf =  (char*)malloc(memListSize*sizeof(char));
    memcpy(buf, &memberNode->memberList[0], memListSize);

    size_t msgsize = sizeof(MessageHdr) + memListSize;

    msg = (MessageHdr *) malloc(msgsize * sizeof(char));

    // create message(of msgType): format of data is {struct Address myaddr}
    msg->msgType = msgtype;
    memcpy(&msg->fromAddr.addr, &memberNode->addr.addr, sizeof(memberNode->addr.addr));
    memcpy(&msg->toAddr, toAddr->addr, sizeof((toAddr->addr)));

    memcpy(msg+1, buf, memListSize); 

//#ifdef DEBUGLOG
    //sprintf(s, "sending to %d.%d.%d.%d:%d ", toAddr->addr[0],toAddr->addr[1],toAddr->addr[2],
            //toAddr->addr[3], *(short*)&toAddr->addr[4]) ;    
    //log->LOG(&memberNode->addr, s);
//#endif

    // send msg to another node(toAddr)
    emulNet->ENsend(&memberNode->addr, toAddr, (char*)msg, msgsize);
    free(msg);
}

void MP1Node::sendMemberListTableToNeighbors(Member *memberNode) {
    MessageHdr *msg;
    Address neighborAddr;
    int idM, portM;

    for(unsigned int i = 0; i<memberNode->memberList.size();i++){
        idM = memberNode->memberList[i].getid();
        portM = memberNode->memberList[i].getport();

        //do not send message to yourself
        if(idM == getIdFromAddress(&memberNode->addr) and
                portM == getPortFromAddress(&memberNode->addr))
            continue;

        //get the neighbor address from the memberlist table
        memset(&neighborAddr, 0, sizeof(Address));
        *(int *)(&neighborAddr.addr) = idM;
        *(short *)(&neighborAddr.addr[4]) = portM;

        sendMemberListTableToAddress(memberNode, &neighborAddr,JOINREP);

    }
}

void MP1Node::updateHearbeatCounter(){

    memberNode->heartbeat++;
    memberNode->memberList[0].setheartbeat(memberNode->heartbeat);
    memberNode->memberList[0].settimestamp(par->getcurrtime());

}

void MP1Node::mergeMemberListTable(Member *memberNode, vector<MemberListEntry> memberList){

    int id, port;
    long heartbeat, timestamp;
    Address addr;
    int pos;
    MemberListEntry memberListEntry; 
    if(!memberNode)
        return;

    for(unsigned int i = 0; i<memberList.size();i++){
        id = memberList[i].getid();
        port = memberList[i].getport();
        heartbeat = memberList[i].getheartbeat();
        timestamp = memberList[i].gettimestamp();


        memset(&addr, 0, sizeof(Address));
        *(int *)(&addr.addr) = id;
        *(short *)(&addr.addr[4]) = port;

        if((pos = searchMemberListTable(memberNode, id, port)) < 0) {
            memberListEntry.setid(id);
            memberListEntry.setport(port);
            memberListEntry.setheartbeat(heartbeat);
            memberListEntry.settimestamp(timestamp);
            memberNode->memberList.push_back(memberListEntry);

            memberNode->nnb = memberNode->nnb + 1;
            log->logNodeAdd(&memberNode->addr, &addr);
        } else {
            if(memberList[i].getheartbeat() > memberNode->memberList[pos].getheartbeat()){
                memberNode->memberList[pos].setheartbeat(memberList[i].getheartbeat());
                memberNode->memberList[pos].settimestamp(par->getcurrtime());
            } 
        }
    }
}

void MP1Node::checkMemberFailure(Member *memberNode){

    int idM, portM;
    Address addr;
    int  time = par->getcurrtime();
    int timestamp;

    for(unsigned int i = 0; i<memberNode->memberList.size();i++){
        idM = memberNode->memberList[i].getid();
        portM = memberNode->memberList[i].getport();

        memset(&addr, 0, sizeof(Address));
        *(int *)(&addr.addr) = idM;
        *(short *)(&addr.addr[4]) = portM;

        timestamp = memberNode->memberList[i].gettimestamp(); 
        if((time - timestamp) > 2*TFAIL){
            memberNode->memberList.erase(memberNode->memberList.begin() + i);
            log->logNodeRemove(&memberNode->addr, &addr);

        }
    }
}
