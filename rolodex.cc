//
//  rolodex.cc
//
//
//  Created by Eric Walsh on 4/3/14.
//
//
#include <algorithm>
#include <string>
#include <iostream>
#include <fstream>
#include <strings.h>
using namespace std;

#ifndef ____cardNode__
#define ____cardNode__

class cardNode{

public:
    std::string firstName;
    std::string lastName;
    std::string address;
    std::string phoneNumber;
    cardNode * next;
    cardNode * prev;
    cardNode(std::string first, std::string last, std::string add, std::string phone , cardNode * target, cardNode * predecessor);
    ~cardNode();
    bool operator == (const cardNode &s) const;
    void print(int i);
    void printSelf();
};

#endif // card_node

//cardNode for rolodex class
cardNode::cardNode(std::string first, std::string last, std::string add, std::string phone, cardNode * target, cardNode * predecessor){
    firstName = first;
    lastName = last;
    address = add;
    phoneNumber = phone;
    next = target;
    prev = predecessor;
}
cardNode::~cardNode(){
    delete next;
    delete prev;
}
bool cardNode::operator == (const cardNode &s) const{
    return firstName==s.firstName && lastName==s.lastName && address==s.address && phoneNumber==s.phoneNumber;
}
void cardNode::print(int i){
    cout << "Card #" << i++ << endl;
    cout << "Last Name: " << lastName << "    First Name: " << firstName << endl;
    cout << "Address: " << address << "    Phone Number: " << phoneNumber << endl;
    if(next!=NULL) next->print(i);
}
void cardNode::printSelf(){
    cout << "Last Name: " << lastName << "    First Name: " << firstName << endl;
    cout << "Address: " << address << "    Phone Number: " << phoneNumber << endl;
}

#ifndef ____rolodex__
#define ____rolodex__

class rolodex{

public:
    cardNode * head;
    rolodex();
    rolodex(cardNode * target);
    ~rolodex();
    void insertAddress(cardNode * target);
    void deleteAddress(cardNode * target);
    cardNode * find(cardNode * target);
    void print();
    void saveAddresses(char * fileName);
};

#endif // rolodex
rolodex::rolodex(){
    head = NULL;
}
rolodex::rolodex(cardNode * target){
    head = target;
}
rolodex::~rolodex(){
    delete head;
}
void rolodex::saveAddresses(char * fileName){
    std:ofstream outfile(fileName);
    cardNode * temp = head;
    while(temp!=NULL){
        outfile << temp->firstName << endl;
        outfile << temp->lastName << endl;
        outfile << temp->address << endl;
        outfile << temp->phoneNumber << endl;
        temp=temp->next;
    }
    outfile.close();
    cout << "Rolodex saved to " << fileName << " ." << endl;
}
void rolodex::insertAddress(cardNode * target){
    if(head==NULL){
        head = target;
        cout << "Address successfully inserted." << endl;
    }
    else{
        cardNode * temp = head;
        std::string a = temp->lastName;
        std::string b = target->lastName;
        std::transform(a.begin(), a.end(), a.begin(), ::tolower);
        std::transform(b.begin(), b.end(), b.begin(), ::tolower);
        //cout << a << " and also " << b << endl;
        while(a<b){
            if(temp->next == NULL){
                temp->next = target;
                target->prev = temp;
                cout << "Address successfully inserted." << endl;
                return;
            }
            temp = temp->next;
            a = temp->lastName;
            std::transform(a.begin(), a.end(), a.begin(), ::tolower);
        }
        if(target!=temp){
            if(temp->prev==NULL){
                temp->prev = target;
                target->next = temp;
                head = target;
                return;
            }
            temp->prev->next = target;
            target->prev = temp->prev;
            temp->prev = target;
            target->next=temp;
            cout << "Address successfully inserted." << endl;
        }
        else cout << "Attempted to insert an address that is already in the rolodex." << endl;
    }

}
cardNode * rolodex::find(cardNode * target){
    if(head==NULL) return NULL;
    else{
        cardNode * temp = head;
        std::string a = temp->lastName;
        std::string b = target->lastName;
        std::transform(a.begin(), a.end(), a.begin(), ::tolower);
        std::transform(b.begin(), b.end(), b.begin(), ::tolower);
        //cout << a << " and also " << b << endl;
        while(a<b){
            if(temp->next == NULL) return NULL;
            temp = temp->next;
            a = temp->lastName;
            std::transform(a.begin(), a.end(), a.begin(), ::tolower);
            //cout << "LOOKIN AT " << a << endl;
        }
        //cout << " THIS IS A " << a << endl;
        std::string c = target->firstName;
        std::string d = temp->firstName;
        std::transform(c.begin(), c.end(), c.begin(), ::tolower);
        std::transform(d.begin(), d.end(), d.begin(), ::tolower);
        /**
        cout << "a is " << a.length() << endl;
        cout << "b is " << b.length() << endl;
        cout << "c is " << c.length() << endl;
        cout << "d is " << d.length() << endl;
        **/
        if(a.substr(0,a.length()-1)==b && c==d.substr(0,d.length()-1) ) return temp;
        else return NULL;
    }


    return target;
}
void rolodex::deleteAddress(cardNode * finder){
    if(finder==NULL) cout << "The address cannot be deleted because it does not exist in the rolodex." << endl;
    else{
        if(finder->prev==NULL && finder==head){
            if(head->next==NULL) head=NULL;
            else{
                head=head->next;
                head->prev=NULL;
            }
        }
        else if(finder->next==NULL){
            finder->prev->next=NULL;
            finder->prev=NULL;
            delete finder;
        }
        else{
            finder->prev->next=finder->next;
            finder->next->prev=finder->prev;
            finder->prev = NULL;
            finder->next = NULL;
            delete finder;
        }
        cout << "The address was successfully deleted!" << endl;
    }
}
void rolodex::print(){
    if(head!=NULL) head->print(1);
    else cout << "No addresses in rolodex, nothing to print!" << endl;
}

rolodex * loadAddresses(char * fileName){
    rolodex * ans = new rolodex();
    std::ifstream infile(fileName);
    int count = 0;
    std::string holder[3];
    for( std::string line; getline( infile, line ); ){
        if(count==3){
            ans->insertAddress(new cardNode(holder[0],holder[1],holder[2],line,NULL,NULL));
            count=0;
        }
        else holder[count++]=line;
    }
    return ans;
}

int rolodexMenu(rolodex * &r){
    cout << endl << "Welcome to the Rolodex Main Menu:" << endl;
    cout << "I - Insert new address" << endl;
    cout << "F - Find a given address" << endl;
    cout << "D - Delete a given address" << endl;
    cout << "P - Print all addresses" << endl;
    cout << "L - Load addresses from specified file" << endl;
    cout << "S - Save addresses to specified file" << endl;
    cout << "Q - Quit the program" << endl;
    string s;
    cout << endl << "Type your input: ";
    cin >> s;
    std::transform(s.begin(), s.end(), s.begin(), ::tolower);
    //CANNOT USE STRING FOR SWITCH STATEMENT so will use an int
    int switchExp = -1;
    if(s=="i") switchExp = 0;
    else if(s=="f") switchExp = 1;
    else if(s=="d") switchExp = 2;
    else if(s=="p") switchExp = 3;
    else if(s=="l") switchExp = 4;
    else if(s=="s") switchExp = 5;
    else if(s=="q") switchExp = 6;
    switch(switchExp){
        default: return -1;
        case 0: { //insert
            cout << "Insert a new address:" << endl;
            cout << "What is the first name of the person? : ";
            string s1;
            cin >> s1;
            cout << endl << "And the last name? : ";
            string s2;
            cin >> s2;
            cout << endl << "And the address? : ";
            string s3;
            cin >> s3;
            cout << endl << "And the phone number? : ";
            string s4;
            cin >> s4;
            r->insertAddress(new cardNode(s1,s2,s3,s4,NULL,NULL));
            return -1;
        }
        case 1: { // finder
            cout << "What is the last name of the person you are looking for? : ";
            string s2;
            cin >> s2;
            cout << endl << "And the first name? : ";
            string s1;
            cin >> s1;
            cardNode * temp = new cardNode(s1,s2,"","",NULL,NULL);
            temp = r->find(temp);
            if(temp!=NULL) temp->printSelf();
            else cout << "Sorry that address is not in the rolodex." << endl;
            return -1;
        }
        case 2: { //delete
            cout << "What is the last name of the person you are looking for? : ";
            string s2;
            cin >> s2;
            cout << endl << "And the first name? : ";
            string s1;
            cin >> s1;
            cardNode * temp = new cardNode(s1,s2,"","",NULL,NULL);
            temp = r->find(temp);
            r->deleteAddress(temp);
            return -1;
        }
        case 3: {
            r->print();
            return -1;
        }
        case 4: { // load
            cout << "Specify file to load addresses from : ";
            string s;
            cin >> s;
            char * sTemp = new char[s.length()+1];
            strcpy(sTemp,s.c_str());
            //cout << " this file is!!! " << sTemp << endl;
            r = loadAddresses(sTemp);
            //r->print();
            return -1;
        }
        case 5: { //save
            cout << "Specify file to save addresses to : ";
            string s;
            cin >> s;
            char * sTemp = new char[s.length()+1];
            strcpy(sTemp,s.c_str());
            r->saveAddresses(sTemp);
            return -1;
        }
        case 6: cout << "Would you like to save the rolodex - Y/N?" << endl;
            string s;
            cin >> s;
            if(s=="Y" || s == "y"){
                cout << "Specify file to save addresses to : ";
                string s;
                cin >> s;
                char * sTemp = new char[s.length()+1];
                strcpy(sTemp,s.c_str());
                r->saveAddresses(sTemp);
            }
            return 6;
    }


}
int main(){
    //rolodex * test = loadAddresses("test.txt");
    rolodex * test = new rolodex();
    //test->print();
    int x =0;
    while(x!=6) x = rolodexMenu(test);
}
