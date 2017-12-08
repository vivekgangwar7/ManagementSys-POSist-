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
int curr1 = 0;

struct Data {
    string owner_name ;
    string address ;
    string mobile_no ;
    string phone ;
    float value ;
};

struct node {
    time_t t_node ;
    string time ;
    Data data_node ;
    int nodeID ;
    int node_number ;
    node *ref_ParentID ;
    node *ref_ChildNode ;
    void getData(Data data_node);
    void putData(Data data_node, node *hdr);
};

map<int, node> map_node;
//Additive Cipher
string encrypt(string str, int key) {
    for (int i = 0 ; i < str.length() ; i++) {
        if (isupper(str[i])) {
            str[i] = (char)(((int)str[i]+key-65)%26+65);
        }else {
            str[i] = (char)(((int)str[i]+key-97)%26+97);
        }
    }
    return str;
}

//Decrypt
string decrypt(string str, int key) {
    for (int i = 0 ; i < str.length() ; i++) {
        if (isupper(str[i])) {
            str[i] = (char)(((int)str[i]-key-65)%26+65);
        }else {
            str[i] = (char)(((int)str[i]-key-97)%26+97);
        }
    }
    return str;
}
void node::getData(Data data_node) {
    cout << "Owner Name : " << data_node.owner_name << endl ;
    cout << "Address : " << data_node.address << endl ;
    cout << "Mobile number : " << data_node.mobile_no << endl ;
    cout << "Phone nymber : " << data_node.phone << endl;
    cout << "Value : " << data_node.value << endl;
}

void node::putData(Data d_node, node *hdr) {
    cout << "Enter Owner Name : " ;
    cin >> d_node.owner_name ;
    cout << "Enter Address : " ;
    cin >> d_node.address ;
    cout << "Enter Mobile Number : " ;
    cin >> d_node.mobile_no ;
    cout << "Enter Phone Number : " ;
    cin >> d_node.phone ;
    cout << "Enter value : " ;
    cin >> d_node.value ;
    hdr->data_node = d_node;
}

node *Create_newNode(node *parent) {
    // Allocates memory
    node *n = new node ;
    
    // For Date Time stamp
    n->t_node = time(0) ;
    struct tm * curr = localtime(&n->t_node) ;
    int yy = (curr->tm_year + 1900), mm = (curr->tm_mon + 1), dd = (curr->tm_mday) ;
    
    // Converting the format into date-time format
    n->time = yy+'-'+mm+'-'+dd ;
    
    // Retrieving data
    n->getData(n->data_node);
    
    // Initializing incremental node_number and the reference parentID
    if (curr1 == 0) {
        n->node_number = 1;
        curr1 += 1;
        n->ref_ParentID = NULL;
    }else {
        n->node_number = curr1;
        curr1 += 1;
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
    n->ref_ChildNode = NULL;
    
    return n;
}

class Admin {
    
public:
    
    node *Hdr;
    node* childNode[];
    
    // Creates Header node
    Admin *create_firstNode(node *new_node) {
        Admin *n1 = new Admin;
        n1->Hdr = new_node;
        return n1;
    }
    
    // Creates MultiSet of the header node
    void createMultiSet(Admin *head) ;
    
    // Add new node to the multiset node
    void add_newNode(Admin *head, int nodeNum,int n) ;
    
    // Encryption of the node data
    void EncryptNodeData(int node_number, int key, int password) ;
    
    // Verification of the owner
    bool verifyOwner(int key, int password) ;
    
    // Still analysing
    void breakUpNode(int key, int password) ;
    
    // Transfer Owner
    void transferOwner(int key, int value, int nodeID) ;
    
    // Find longer Chain
    void findLongerChain() ;
    
    // Merge two given nodes
    void mergeNode(node *node1, node *node2) ;
} ;

void Admin::createMultiSet(Admin *head) {
    cout << "Wants to create multi set of the node?\n" ;
    int n ;
    cin >> n ;
    for (int i = 0 ; i < n ; i++) {
        // Currently initializing basic features of the multiset
        // Initialized new node
        head->childNode[i] = new node ;
        
        //Initialized parent node referencce
        head->childNode[i]->ref_ParentID = head->Hdr;
        
        //Initialized child node reference
        head->childNode[i]->ref_ChildNode = NULL;
        
        //Initialized incremental number
        head->childNode[i]->node_number = curr1 ;
        curr1++ ;
        map_node[head->childNode[i]->node_number] = *head->childNode[i];
    }
}

// n is the size of the multiset
void Admin::add_newNode(Admin *head,int nodeNum, int n) {
    node *add_newNodeH = NULL ;
    for (int i = 0 ; i < n ; i++) {
        if (head->childNode[i]->node_number == nodeNum) {
            add_newNodeH = head->childNode[i];
            break;
        }
    }
    // add new node
    if (add_newNodeH != NULL) {
        node *ChildNode = new node;
        ChildNode = Create_newNode(add_newNodeH);
    }
}

bool Admin::verifyOwner(int key, int password) {
    //requires database
    return true;
}

void Admin::EncryptNodeData(int node_number, int key, int password) {
    //find node_number
    node *temp = new node;
    temp = &map_node[node_number] ;
    if (temp == NULL) {
        cout << "Doesn't Exists!\n";
    }else {
        if (verifyOwner(key, password)) {
            Data dr = temp->data_node;
            encrypt(dr.owner_name , key);
            encrypt(dr.address, key);
            encrypt(dr.mobile_no, key);
            encrypt(dr.phone, key);
            encrypt(dr.phone, key);
        }
    }
}


void Admin::breakUpNode(int key, int password) {
    // require database access
}

void Admin::transferOwner(int key, int value, int nodeID) {
    // require database access
}

void Admin::findLongerChain() {
    // applying depth first search on findingLongerChain can work
}

void Admin::mergeNode(node *node1, node *node2) {
    // Find the lowest common ancestor of the two nodes.
    // the lca found suppose x
    // merge both the nodes at that particular point
}

int main(int argc, const char * argv[]) {
    Admin *d = new Admin;
    d->Hdr = new node;
    d->Hdr = Create_newNode(d->Hdr);
    d->Hdr->getData(d->Hdr->data_node);
    return 0;
}
