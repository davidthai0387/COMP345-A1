#include "ProjectDef.h"
#include "Cards.h"
#include "Orders.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include "Map.h"
using namespace std;

int main() {
    ////---------------TESTING CARDS---------------

    //Create the deck
    cout << "TESTING CARDS CLASS" << endl;
    Deck* theDeck = new Deck();

    //Create the hand
    Hand* myHand = new Hand();

    //Print out nb of cards in deck and hand
    cout << "Total number of cards: " << theDeck->getNumOfCardsInDeck() << endl;
    cout << "Number of cards in hand: " << myHand->getHand().size() << endl;
    
    cout << "Drawing cards" << endl;
    theDeck->draw(myHand->getHand());

    cout << "Total number of cards: " << theDeck->getNumOfCardsInDeck() << endl;
    cout << "Number of cards in hand: " << myHand->getHand().size() << endl;
    
    //Print out cards in hand
    string allcards;
    for(int i = 0; i < myHand->getHand().size(); i++){
        if (allcards == "")
            allcards += myHand->getHand()[i] -> getCardName();
        else
            allcards += ", " + myHand->getHand()[i] -> getCardName();
    }
    cout << "Your cards are: " << endl;
    cout << allcards << endl;

    cout << "Choose your card number: ";

    int choice; //input variable
    int index; //input - 1
    cin >> choice;

    index = choice - 1;
    myHand->getHand()[index] -> Play(index, myHand->getHand(), theDeck->getDeck());

    cout << "Total number of cards: " << theDeck->getNumOfCardsInDeck() << endl;
    cout << "Number of cards in hand: " << myHand->getHand().size() << endl;

    //---------------TESTING MAPLOADER AND MAP---------------
    Map m1, m2, m3;

    cout << endl << "TESTING MAPLOADER CLASS" << endl;
    MapLoader ml1 = MapLoader("google.map");
    cout << "READING GOOGLE.MAP" << endl;
    vector<string> mapText1 = ml1.read();
    if (ml1.checkFormat(mapText1)) {
        cout << "MAP IS VALID" << endl;
        ml1.parseContinents(mapText1[2]);
        ml1.parseCountries(mapText1[3]);
        m1 = Map(ml1.parseContinents(mapText1[2]), ml1.getNumOfContinents(), ml1.parseCountries(mapText1[3]), ml1.getNumOfCountries(), ml1.parseBorders(mapText1[4]));
    }
    else {
        cout << "MAP IS INVALID" << endl;
    }

    MapLoader ml2 = MapLoader("europe.map");
    cout << "READING EUROPE.MAP" << endl;
    vector<string> mapText2 = ml2.read();
    if (ml2.checkFormat(mapText2)) {
        cout << "MAP IS VALID" << endl;
        ml2.parseContinents(mapText2[2]);
        ml2.parseCountries(mapText2[3]);
        m2 = Map(ml2.parseContinents(mapText2[2]), ml2.getNumOfContinents(), ml2.parseCountries(mapText2[3]), ml2.getNumOfCountries(), ml2.parseBorders(mapText2[4]));
    }
    else {
        cout << "MAP IS INVALID" << endl;
    }

    MapLoader ml3 = MapLoader("solar.map");
    cout << "READING SOLAR.MAP" << endl;
    vector<string> mapText3 = ml3.read();
    if (ml3.checkFormat(mapText3)) {
        cout << "MAP IS VALID" << endl;
        ml3.parseContinents(mapText3[2]);
        ml3.parseCountries(mapText3[3]);
        m3 = Map(ml3.parseContinents(mapText3[2]), ml3.getNumOfContinents(), ml3.parseCountries(mapText3[3]), ml3.getNumOfCountries(), ml3.parseBorders(mapText3[4]));
    }
    else {
        cout << "MAP IS INVALID" << endl;
    }

    cout << endl << "TESTING MAP CLASS" << endl;
    cout << endl << "Validating google.map" << endl;
    m1.validate();
    cout << endl << "Validating europe.map" << endl;
    m2.validate();
    

    //---------------TESTING ORDERS---------------
    cout << endl << "TESTING ORDERS CLASS" << endl;
    OrderList l = OrderList();
    Player* p = new Player("PLAYER");
    Orders* d = new Deploy(-3, "Canada");
    Orders* a = new Advance(2, "Canada", "USA");
    Orders* b = new Bomb("USA");
    Orders* bl = new Blockade("Canada");
    Orders* ai = new Airlift(1, "Canada", "Japan");
    Orders* n = new Negotiate(p);

    l.add(d);
    l.add(a);
    l.add(b);
    l.add(bl);
    l.add(ai);
    l.add(n);

    cout << l.displayOrders() << endl;
    l.move(1, 3);
    cout << l.displayOrders() << endl;
    l.remove(2);
    cout << l.displayOrders() << endl;
    l.execOrders();
    cout << l.displayOrders() << endl;


    //---------------TESTING PLAYERS---------------
    //List of players
    vector<Player*> listofplayers;
    Player* p1 = new Player("Bob");
    Player* p2 = new Player("Jesus");
    listofplayers.push_back(p1);
    listofplayers.push_back(p2);

    //Checking player name
    cout << p1->getName() << endl;

    //Checking collection of territories
    Country* c1, * c2;
    c1 = new Country(0, "Korea", 0);
    c2 = new Country(1, "Canada", 0);

    p1->setCountry(c1); //Adding countries
    p1->setCountry(c2);
    cout << p1->getCountries() << endl;

    p1->removeCountry("Korea");
    cout << p1->getCountries() << endl;

    p1->setCountry(c1);

    //toAttack method
    cout << "toAttack: " << p1->toAttack() << endl;

    //toDefend method
    cout << "toDefend: " << p1->toDefend() << endl;

    //Cards 
    Deck* deck = new Deck();
    cout << deck->getNumOfCardsInDeck() << endl;;

    deck->draw(p1->getHand());
    cout << p1->getHand().size() << endl;
    cout << p1->showHand() << endl;
    //issueOrder
    p1->issueOrder("Bomb", listofplayers);

}