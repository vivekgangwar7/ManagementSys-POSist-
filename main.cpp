//
//  main.cpp
//  POSist
//
//  Created by Vivek Gangwar on 07/12/17.
//  Copyright © 2017 Vivek Gangwar. All rights reserved.
//

#include <iostream>
#include <map>
#include <string.h>
#include <stdlib.h>
#include <time.h>

using namespace std;
map<int , int> nodeIDs;

struct Data {
    string owner_name ;
    string address ;
    string mobile_no ;
    string phone ;
    string value ;
};

struct node {
    time_t t_node ;
    string time ;
    Data data_node ;
    int nodeID ;
    static int node_number ;
    node *ref_ParentID ;
    node *ref_ChildNode ;
};

class Admin {

    public:
    
        // Creates Header node
        Admin *create_firstNode(node *new_node) {
            Admin *n1 = new Admin;
            return n1;
        }
    
        // Creates MultiSet of the header node
        void createMultiSet(node *head) ;
    
        // Add new node to the multiset node
        node *add_newNode(int nodeNum) ;
    
        // Encryption of the node data
        void EncryptNodeData(int node_number, int key, int password) ;
    
        // Verification of the owner
        void verifyOwner(int key, int password) ;
    
        // Still analysing
        void breakUpNode(int key, int password) ;
    
        // Transfer Owner
        void transferOwner(int key, int value, int nodeID) ;
    
        // Find longer Chain
        void findLongerChain() ;
    
        // Merge two given nodes
        void mergeNode(node *node1, node *node2) ;
} ;
node *Create_newNode(node *parent, string oname, string addr, string mno, string phn, string val) {
    // Allocates memory
    node *n = new node ;
    
    // For Date Time stamp
    n->t_node = time(0) ;
    struct tm * curr = localtime(&n->t_node) ;
    int yy = (curr->tm_year + 1900), mm = (curr->tm_mon + 1), dd = (curr->tm_mday) ;
    
    // Converting the format into date-time format
    n->time = yy+'-'+mm+'-'+dd ;
    
    // Retrieving data
    n->data_node.owner_name = oname ;
    n->data_node.address = addr ;
    n->data_node.mobile_no = mno ;
    n->data_node.phone = phn ;
    n->data_node.value = val ;
    
    // Initializing incremental node_number and the reference parentID
    if (n->node_number == 0) {
        n->node_number = 1;
        n->ref_ParentID = NULL;
    }else {
        n->node_number = n->node_number+1;
        n->ref_ParentID = parent;
    }
    
    //Generating Unique nodeID ranging (10,000- 99,999)
    int nID ;
    do {
        nID = rand() % 100000 + 1;
    }while (nodeIDs[nID] != 0);
    nodeIDs[nID] = 1;
    n->nodeID = nID;
    
    // ref_ChildNode
    return n;
}


int main(int argc, const char * argv[]) {
    // insert code here...
    /*time_t t = time(0);
    node *parent  = new node;
    node *new1 = Create_newNode(parent,"vivek", "391 Golden Jubilee", "mno", "As", "asa");
    cout << new1->data_node.owner_name << endl;*/
    return 0;
}
