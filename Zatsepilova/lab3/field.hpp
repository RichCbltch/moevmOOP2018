#ifndef FIELD
#define FIELD
#include <vector>
#include "object.hpp"
#include "iter.hpp"
#include "warrior.hpp"
#include "building.hpp"
// #include <cstring>

using namespace std;

class Warrior;

//--------------------------------------FIELD----------------------------------------------
class Field
{
    int x_size;
    int y_size;

    weak_ptr<Crown> crown_red;
    weak_ptr<Crown> crown_green;

    List<Object *> list;

  public:
    Field() {}
    ~Field();

    void init();
    int find_id(int x, int y);
    int find_index(int id_);  
    int find_index(int x, int y, int mark); 
    Object *get_obj(int id_);
    Object *get_obj(int x, int y, char mark);
    bool is_obj(int id_);
    int attack(int x, int y, int power);
    void read_from_file(istream &in);
    void print_list();
    void print_field(ostream &out);

    List<Object *> &getlist();  
   int &get_x_size();
    int &get_y_size();

   friend istream &operator>>(istream &in, Field &fd);
    friend ostream &operator<<(ostream &out, const Field &fd);
};
//-----------------------------------------------------------------------------------------

//---------------------------------FIELD-METHODS-------------------------------------------
void Field::init(){
    cout << "Field:" << endl
         << "    x_size = " << x_size << endl
         << "    y_size = " << y_size << endl;
}

Field::~Field(){
    cout << "~Field:" << endl
         << "    x_size = " << x_size << endl
         << "    y_size = " << y_size << endl;
}

int Field::find_id(int x, int y){
    for (const auto &obj : list){
        if (obj.get()->getx() == x && obj.get()->gety() == y){
            return obj.get()->getid();
        }
    }
    return -1;
}

int Field::find_index(int id_){
    int count = 0;
    for (const auto &obj : list){
        if (obj.get()->getid() == id_){
            return count;
        }
        count++;
    }
    return -1; // not found
}

int Field::find_index(int x, int y, int mark){
    int count = 0;
    for (const auto &obj : list){
        if (obj.get()->getx() == x && obj.get()->gety() == y){
            if(mark == 'a') // ob, bd, wr
                return count;
        
            if(mark == 'g'){ // ob, bd
               if(obj.get()->getcrown()->getcolor() == "green"){
                    return count;
                }
            }
            if(mark == 'r'){
                if(obj.get()->getcrown()->getcolor() == "red"){
                    return count;
                }
            }
        }
        count++;
    }
    return -1; // not found
}

Object *Field::get_obj(int id_){
    for(const auto &item: list){
        if(item.get()->getid() == id_){
            return item.get();
        }
    }
    return nullptr;
}

Object *Field::get_obj(int x, int y, char mark){ //map[j][i]-ok
    int ind = find_index(x,y,mark);
    if (ind == -1)
        return nullptr;
    return list.find(ind)->get();
}

bool Field::is_obj(int id_){
    Object* o = get_obj(id_);
    if (o){
        if (!o->alive()){
            list.delete_elem(find_index(id_));
            return false;
        }
        else return true;
    }
    return false; // not found
}

int Field::attack(int x, int y, int id_){
    Object* ob = get_obj(id_);
    if (!ob)  return -1;    

    char mark;
  string color = ob->getcrown()->getcolor();
    if(color == "red") { color = "green"; mark = 'g';}
    else {color == "red"; mark = 'r';}
    ob = get_obj(x,y,mark);
    if (!ob)  return -1;
    if(ob->getmark() == 'o' || ob->getmark() == 'w'){
        ob->damage(get_obj(id_)->getpower());
        if(!ob->alive()) {
            list.delete_elem(find_index(x,y,mark));
        }
    }
    if(ob->getmark() == 'b'){
            Building* bd = static_cast<Building*>(ob);
            for(auto &item: bd->getlocation()){
                Object* bd = get_obj(get<0>(item), get<1>(item), mark);
                bd->damage(get_obj(id_)->getpower());
                if(!ob->alive()) {
                    list.delete_elem(find_index(get<0>(item),get<1>(item),mark));
                }
            } 
    }
    return 0;
}

void Field::print_list(){
    for (auto &ob : list){
        ob.get()->print_ob_simple();
    }
}

void Field::print_field(ostream &out){
    //borders
    out << endl;
    for (int i = 0; i < y_size; i++)
    {
        if (i == 0)
            out << "  ";
       out << i;
    }
    out << endl;
    for (int i = 0; i < y_size; i++)
    {
        if (i == 0 || i == y_size - 1)
        {
            if (i == 0)
                out << "  ";
            out << "+";
        }
        else
            out << "-";
    }
    out << endl;

    //fill field
    for (int i = 0; i < y_size; i++)
    {
        out << i << "|";
        for (int j = 0; j < x_size; j++)
        {
            if (!get_obj(j, i, 'a'))
                out << '.';
            else{
                out << *get_obj(j, i, 'a');
            }
        }
        out << "|" << endl;
    }

    //borders
    for (int i = 0; i < y_size; i++)
    {
        if (i == 0 || i == y_size - 1)
        {
            if (i == 0)
                out << "  ";
            out << "+";
        }
        else
            out << "-";
    }
    out << endl;
    for (int i = 0; i < y_size; i++)
    {
        if (i == 0)
            out << "  ";
        out << i;
    }
    out << endl;
    out << endl;
}

void Field::read_from_file(istream &in){
    int flag_init = 0;
    int obj_amount = 0;
    char which_army_mark;
    char type;
    string color;

    for (int j = 0; j < 2; j++){
        in >> obj_amount >> which_army_mark;
        if (which_army_mark == 'r')
            color = "red";
        if (which_army_mark == 'g')
            color = "green";

        for (int i = 0; i < obj_amount; i++){
            static shared_ptr<Crown> tmp;
            if (!flag_init){
                tmp = shared_ptr<Crown>(new Crown(color));
                this->crown_red = tmp;
                flag_init = 1;
            }
            in >> type;
            in.unget();
            Object *ob;
            if (type == 'o') { ob = new Object(tmp, in); list.insert_tail(ob); }
            if (type == 'w') { ob = new Warrior(tmp, in); list.insert_tail(ob); }
            if (type == 'b') {
                in >> type;
                int hp;
                in >> hp;
                int coord_amount;
                in >> coord_amount;
                vector<pair<int, int>> loc;
                int x, y;
                for(int i = 0; i < coord_amount; i++){
                    in >> x >> y;
                    auto p = make_pair(x, y);
                    loc.push_back(p);
                }
                for(auto &coord: loc){
                    Object* o;
                    o = new Building(tmp, type, get<0>(coord), get<1>(coord), hp, loc);
                    list.insert_tail(o); 
                }               
            }
            cout << type << endl;
        }
        flag_init = 0;
    }
    cout << "Field.\n";
}

ostream &operator<<(ostream &out, Field &fd){
    fd.print_field(out);
    return out;
}

istream &operator>>(istream &in, Field &fd){
    in >> fd.x_size >> fd.y_size;
    fd.init();
    fd.read_from_file(in);
    return in;
}

int &Field::get_x_size()
    { return x_size;}

int &Field::get_y_size()
    {return y_size;}

List<Object *> &Field::getlist()
    { return list; }

//-----------------------------------------------------------------------------------------
#endif //FIELD 