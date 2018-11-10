#include<iostream>
#include "console.cpp"

using namespace std;


class Bowl_Vocabulary
{
private:
    int x,y;
    int core;
public:
    Bowl_Vocabulary(int x, int y, int core) {this->x = x;this->y = y; this->core = core; }

    ~Bowl_Vocabulary() { }

    void IncreateCore(int core){
        this->core = core;
    }
    void Position(int x, int y){
        this->x = x;
        this->y = y;
    }

    void go_left(int speed){
        this->x -= speed;
    }
    void go_right(int speed){
        this->x += speed;
    }
    int getCore(){return this->core;}

    int getX(){return this->x;}
    int getY(){return this->y;}

    void draw_bowl(){
        cout<<"||______||";
    }
};



int main(int argc, char const *argv[])
{

    clrscr();

    int key = inputKey();
    bool endgamne = true;
    Bowl_Vocabulary bowl1(0,0,0);
    bowl1.Position(20,20);

    gotoXY(0,0);
    cout<<"this is a word mean the place you live in?";

    while(endgamne){

        clrscr();  
        key = inputKey();
        gotoXY(bowl1.getX(), bowl1.getY());
        bowl1.draw_bowl();
        if(key == 1075){
            bowl1.go_left(5);
        }

        if(key == 1077){
            bowl1.go_right(5);
        }
        if(key==0){
            endgamne = false;
        }
        delay(40000);
    }

    
    return 0;
}
