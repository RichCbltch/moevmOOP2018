#ifndef OBJECT
#define OBJECT

#include <iostream>
#include <fstream>
#include <memory>
#include "iter.cpp"
#include "crown.cpp"

using namespace std;

class Object 
{
    int x;
    int y;
    int hp;
    
    const int id;
    const shared_ptr<Crown> crown;

    static int count_ob;
    static int cur_amount;

public:     
    Object(shared_ptr<Crown> crown, int x, int y, int hp);
    Object(shared_ptr<Crown> crown, istream &in);      
    ~Object();

    void read_obj(fstream &f, int id);
    void damage(int damage);
    bool alive();
    int army();
    bool check_crown();

    void print_ob();
    void print_ob_simple();
    char draw(); 

    int &getx();
    int &gety();
    int &gethp();
    int &getid();
    int &get_cur_amount();
    const int &getid() const;
    const shared_ptr<Crown> getcrown();

    friend istream &operator>>(istream &in, Object &ob);
    friend ostream &operator<<(ostream &out, Object &ob);
};


void Object::print_ob() {
    cout << "Object:"<< endl 
         << "    x = " << x << endl
         << "    y = " << y << endl
         << "    hp = " << hp << endl
         << "    crown = " << crown->getcolor() << endl
         << "    id = " << id << endl
         << "Object." <<endl; 
}

Object::Object(shared_ptr<Crown> crown, int x, int y, int hp): x(x), y(y), hp(hp), id(count_ob++), crown(crown) {
    cur_amount++;    
    print_ob(); 
}

Object::Object(shared_ptr<Crown> crown, istream &in): id(count_ob++), crown(crown){ 
    in >> *this; 
    cur_amount++;
    print_ob(); 
}

Object::~Object(){
    cout << "~Object:"<< endl 
            << "    x = " << x << endl
            << "    y = " << y << endl
            << "    hp = " << hp << endl
            << "    crown = " <<crown->getcolor() << endl
            << "    id = " << id << endl
        << "~Object." <<endl;
    cur_amount--;
}   

void Object::damage(int damage) { 
    hp -= damage; 
}

bool Object::alive(){
    return (hp > 0);
}

char Object::draw(){
    if(alive()) return 'o'; 
    else if(!alive()) return 'x';
} 

int Object::army(){
    if(crown->getcolor() == "green") return 1;
    if(crown->getcolor() == "red")return 0;    
}

void Object::print_ob_simple() { 
    cout << "[ " << id << " " << x << " " << y << " "<< hp << " ]" << endl; 
}

int &Object::getx()
    {return x;}

int &Object::gety()
    {return y;}

int &Object::gethp()
    {return hp;} 

const int &Object::getid() const
    {return id;}   

int &Object::get_cur_amount()
    {return cur_amount;}

const shared_ptr<Crown> Object::getcrown()
    {return crown;}
       
istream &operator>>(istream &in, Object &ob){
    in >> ob.x >> ob.y >> ob.hp; 
    return in;
}

ostream &operator<<(ostream &out, Object &ob){
    if(ob.crown->getcolor() ==  "green" ) // 1
        out << "\033[32m";
    if(ob.crown->getcolor() == "red") // 0
        out << "\033[31m";
    out << ob.draw() << "\033[0m";
    return out;
}   

#endif //OBJECT
