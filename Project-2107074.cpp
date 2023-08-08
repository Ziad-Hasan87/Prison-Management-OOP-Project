#include <iostream>
using namespace std;

class PRISONER;
class GUARD;
class MANAGEMENT;
class PRISON;
class COURT;
void display_all(MANAGEMENT &manager);

class PRISONER{
    int tag;
    string name;
    int sentence;
    string crime;
    friend MANAGEMENT;
    friend COURT;
    void friend display_all(MANAGEMENT &manager);
public:
    PRISONER(){
        cout << "Prisoner Details: \n";
        cout << "Tag: ";
        cin >> tag;
        cout << "Name: ";
        cin >> name;
        cout << "Crime: ";
        cin >> crime;
        cout << "Sentence in years: ";
        cin >> sentence;
        cout << endl;
    }
    void display(){
        cout << "Tag: ";
        cout << tag;
        cout << "\tName: ";
        cout << name;
        cout << "\tCrime: ";
        cout << crime;
        cout << "\tSentence: ";
        cout << sentence;
        cout << " Years\n";
    }
    ~PRISONER(){
        cout << "Prisoner with tag: " << tag << " has been released.\n\n";
    }
};

class GUARD{
    int ID;
    string name;
    char block;
    friend MANAGEMENT;
    friend void display_all(MANAGEMENT &manager);
public:
    GUARD(){
        cout << "ID: ";
        cin >> ID;
        cout << "Name: ";
        cin >> name;
        cout << "Block: ";
        cin >> block;
        cout << endl;
    }
    void display(){
        cout << "ID: ";
        cout << ID;
        cout << "\tName: ";
        cout << name;
        cout << "\tBlock: ";
        cout << block;
        cout << "\n";
    }
    ~GUARD(){
        cout << "Guard with ID: "<< ID << " has left.\n\n";
    }

};

class MANAGEMENT{
    PRISONER *prisoner[100];
    GUARD *guard[50];
    int pr_kep;
    int pr_rel;
    int gd_kep;
    int gd_res;
    friend COURT;
    friend void display_all(MANAGEMENT &manager);
public:
    MANAGEMENT(){
        pr_kep = 0;
        pr_rel = 0;
        gd_kep = 0;
        gd_res = 0;
    }
    void add_prisoner(){
        prisoner[pr_kep+pr_rel] = new PRISONER;
        pr_kep++;
    }
    void add_guard(){
        guard[gd_kep+gd_res] = new GUARD;
        gd_kep++;
    }
    void remove_guard(int id){
        for(int i = 0; i < gd_kep+gd_res; i++){
            if(guard[i] == NULL) continue;
            if(guard[i]->ID  == id){
                delete guard[i];
                gd_kep--;
                gd_res++;
                guard[i] = NULL;
            }
        }
    }
    void display_guard(int id){
        for(int i = 0; i < gd_kep+gd_res; i++){
            if(guard[i] == NULL) continue;
            if(guard[i]->ID  == id){
                guard[i]->display();
                cout << endl;
                return;
            }
        }
        cout << "No Guard with ID " << id << " found\n" << endl;
    }
    void display_prisoner(int tag){
        for(int i = 0; i < pr_kep+pr_rel; i++){
            if(prisoner[i] == NULL) continue;
            if(prisoner[i]->tag  == tag){
                prisoner[i]->display();
                cout << endl;
                return;
            }
        }
        cout << "No prisoner with tag " << tag << " found\n" << endl;
    }
    void population(){
        cout << "Number of Guards: " << gd_kep << endl;
        cout << "Number of Prisoners: " << pr_kep << endl << endl;
    }
};

class COURT{
    MANAGEMENT *manager;
public:
    COURT(){
    }
    COURT(MANAGEMENT &a){
        manager = &a;
    }
    void increase_sentence(int tag, int n){
        for(int i = 0; i < manager->pr_kep+manager->pr_rel; i++){
            if(manager->prisoner[i] == NULL) continue;
            if(manager->prisoner[i]->tag  == tag){
                manager->prisoner[i]->sentence +=n;
                cout << "Sentence increased by " << n << "years\n";
                cout << "New sentence: " << manager->prisoner[i]->sentence << " Years\n\n";
                break;
            }
        }
    }
    void decrease_sentence(int tag, int n){
        for(int i = 0; i < manager->pr_kep+manager->pr_rel; i++){
            if(manager->prisoner[i] == NULL) continue;
            if(manager->prisoner[i]->tag  == tag){
                manager->prisoner[i]->sentence -= n;
                if(manager->prisoner[i]->sentence <= 0){
                    cout << "Prisoner has completed his sentence.\n";
                    release_prisoner(tag);
                }
                else {
                    cout << "Sentence decreased by " << n << "years\n";
                    cout << "New sentence: " << manager->prisoner[i]->sentence << "Years\n\n";
                }
            }
        }
    }
    void release_prisoner(int tag){
        for(int i = 0; i < manager->pr_kep+manager->pr_rel; i++){
            if(manager->prisoner[i] == NULL) continue;
            if(manager->prisoner[i]->tag  == tag){
                delete manager->prisoner[i];
                manager->pr_kep--;
                manager->pr_rel++;
                manager->prisoner[i] = NULL;
            }
        }
    }
};

void display_all(MANAGEMENT &manager){
    cout << "Prisoner list: \n";
    for(int i = 0; i < manager.pr_kep+manager.pr_rel; i++){
    if(manager.prisoner[i] == NULL) continue;
        manager.prisoner[i]->display();
    }
    cout << "Guard list: \n";
    for(int i = 0; i < manager.gd_kep+manager.gd_res; i++){
        if(manager.guard[i] == NULL) continue;
        manager.guard[i]->display();
    }
    cout << endl;
}

int main()
{
    int n, id, change;
    string command;
    MANAGEMENT manager;
    COURT court(manager);
    while(true){
        cout << "Enter Command: ";
        cin >> command;
        if(command == "END") break;
        else if(command == "add_prisoner") manager.add_prisoner();
        else if(command == "add_guard") manager.add_guard();
        else if(command == "population") manager.population();
        else if(command == "display_all") display_all(manager);
        else if(command == "remove_guard"){
            cout << "Guard ID: ";
            cin >> id;
            manager.remove_guard(id);
        }
        else if(command == "display_prisoner"){
            cout << "Prisoner Tag: ";
            cin >> id;
            manager.display_prisoner(id);
        }
        else if(command == "display_guard"){
            cout << "Guard ID: ";
            cin >> id;
            manager.display_guard(id);
        }
        else if(command == "increase_sentence") {
            cout << "Prisoner Tag: ";
            cin >> id;
            cout << "Increment in sentence: ";
            cin >> change;
            court.increase_sentence(id,change);
        }
        else if(command == "decrease_sentence") {
            cout << "Prisoner Tag: ";
            cin >> id;
            cout << "Decrement in sentence: ";
            cin >> change;
            court.decrease_sentence(id, change);
        }
        else if(command == "release_prisoner"){
            cout << "Prisoner Tag: ";
            cin >> id;
            court.release_prisoner(id);
        }
    }
    return 0;
}
