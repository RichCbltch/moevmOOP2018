#ifndef FIELD
#define FIELD
#include "object.cpp"
#include <vector>
#include "list.cpp"

using namespace std;

class Field{

    int x_size;
    int y_size;
    
    weak_ptr<Crown> crown_red;
    weak_ptr<Crown> crown_green;    

    char **map; 
    List<List<Object*>*> contains;     
    
    friend class Object;
    friend class List<Object*>;
   
public:
    Field(){}
    ~Field();
    
    void init(); 
    void print_field(ostream &out);
    void print_cont();
    void add_to_map(int i, int j);
    void read_file(istream &f);
    Object *get_ob(int x, int y);
    int belonging_army(int i, int j);
    void check_map();
    int is_obj(int x, int y);
    int find_ob_index(int i, int j);
    void read_from_file(istream &in);

    int &get_x_size();
    int &get_y_size();    
    char **getmap();
    List<List<Object*>*> &getconts();

    friend istream &operator>>(istream &in, Field &fd);
    friend ostream &operator<<(ostream &out, const Field &fd);
};


void Field::init() 
{
    cout << "Field:"<<endl    
         <<"    x_size = " << x_size << endl
         <<"    y_size = " << y_size <<endl; 
    
//  create a clean map
    int i = 0;
    map = new char*[y_size]; 
   
    for(int i = 0; i < y_size; i++){ 
        map[i] = new char[x_size];
    }
    for(int i = 0; i < x_size; i++){
        for(int j = 0; j < y_size; j++){
            map[i][j] = '.';
        }
    }

//create containers for armies
    for(i = 0; i < 2; i++)
{
        List<Object*>* some = new List<Object*>;
        contains.insert_tail(some);
    }
}

void Field::add_to_map(int i, int j) 
    { map[i][j] = 'o'; }

Field::~Field(){
    cout << "~Field:"<<endl    
         <<"    x_size = " << x_size << endl
         <<"    y_size = " << y_size <<endl; 
}

int Field::is_obj(int i, int j)
{
    if (map[i][i] = 'o') return 1;
    if (map[j][i] = 'x') {
        contains[get_ob(i,j)->army()]->delete_elem(find_ob_index(i,j));
        return 0;
    }
    else return -1; // not found
    
}

Object *Field::get_ob(int x, int y) //map[j][i]-ok
{
    int a = belonging_army(x,y);
    int ind = find_ob_index(x,y);
    if(ind == -1 || a == -1) return nullptr;
    return getconts()[a]->find(ind)->get();
}

int Field::find_ob_index(int i, int j)
{
    for(auto &cont: contains){ 
        int count = 0; 
        for(auto &obj : *(cont.get())){ 
            if(obj.get()->getx() == i && obj.get()->gety() == j) 
                return count; 
            count++;
        }
    }
    return -1; // not found
}

int Field::belonging_army(int i, int j)
{
    int army = 0;
    for(auto &cont: contains){ 
        for(auto &obj : *(cont.get())){ 
            if(obj.get()->getx() == i && obj.get()->gety() == j)  
                return army;
        }
        army++;
    }
    return -1; //not found
}

void Field::check_map()
{
    for(auto &cont: contains){ 
        for(auto &obj : *(cont.get())){ 
            if(obj.get()->gethp() <= 0) {
                map[obj.get()->gety()][obj.get()->getx()] = 'x';
            }
        }
    }
}

void Field::print_cont()
{
    int count_cont = 0;
    for(auto &cont: contains){ 
        for(auto &obj : *(cont.get())){ 
            cout << count_cont << ": "; obj.get()->print_ob_simple();
        }
        count_cont++;
    }
}

void Field::print_field(ostream &out)
{   
    check_map();
    out <<endl;
    for(int i = 0; i < y_size; i++){ if(i==0) out << "  "; out <<  i; } out << endl;        
    for(int i = 0; i < y_size; i++){ 
        if(i==0 || i == y_size-1) {
            if(i==0) out << "  ";
            out << "+"; 
        }
        else out << "-"; 
    }out << endl;   
    for(int i = 0; i < y_size; i++){
        out << i << "|";
        for(int j = 0; j < x_size; j++){
            int belong = belonging_army(j,i);
            switch(belong){
                case 0:
                    // out << *get_ob(j,i);
                    out << "\x1b[31m"<<map[i][j]<<"\x1b[0m";
                    break;
                case 1:
                    out << "\x1b[32m"<<map[i][j]<<"\x1b[0m";
                    break;
                default:
                    out << map[i][j];
                    break;
            }
        }
        out<< "|" <<endl;
    }
    for(int i = 0; i < y_size; i++){ 
        if(i==0 || i == y_size-1) {
            if(i==0) out << "  ";
            out << "+"; 
        }
        else out << "-"; 
    }out<<endl;   
    for(int i = 0; i < y_size; i++){ if(i==0) out << "  "; out <<  i; } out << endl; 
    out << endl;      
}

void Field::read_from_file(istream &in){
    int redflag = 0;
    int greenflag = 0;
    int obj_amount = 0;
    
    in >> *this;
    this->init();
    for(int j = 0; j < 2; j++){  
        in >> obj_amount; 
        for(int i = 0; i < obj_amount; i++){ 
            Object *ob;
            static shared_ptr<Crown> tmp;
            if(j == 0) {                            
                if(!redflag) {
                    tmp = shared_ptr<Crown>(new Crown("red"));
                    this->crown_red = tmp;
                    redflag = 1;
                }
                ob = new Object(tmp, in);
            }
            if(j == 1){  
                if(!greenflag) {
                    tmp = shared_ptr<Crown>(new Crown("green"));
                    this->crown_green = tmp;                                        
                    greenflag = 1;
                }
                ob = new Object(tmp, in);
            }
            contains[j]->insert_tail(ob); // add an object to j container   
            add_to_map(ob->gety(), ob->getx()); // mark this object on the map
        }
    }
    cout << "Field.\n"; 
}

ostream &operator<<(ostream &out, Field &fd){
    fd.print_field(out);
    return out;
}

istream &operator>>(istream &in, Field &fd){
    in >> fd.x_size >> fd.y_size;
    return in;
}

int &Field::get_x_size()
    {return x_size;}

int &Field::get_y_size()
    {return y_size;}

char **Field::getmap()
    {return map;}
    
List<List<Object*>*> &Field::getconts() 
    {return contains;}

#endif //FIELD
