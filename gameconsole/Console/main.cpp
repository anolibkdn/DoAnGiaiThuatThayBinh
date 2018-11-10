#include<iostream>
#include<string>
#include "ListWord.cpp"
#include "console.cpp"
#include<math.h>

using namespace std;

//class bottle

class BowlCatchWord
{
private:
    int x,y;
    int core;
public:
    BowlCatchWord(int x=0,int y=0, int core=0);
    ~BowlCatchWord();
    //positon update
    void Update_positon_of_bowl(int x, int y);
    void setCore(int core);
    void Turn_left(int speed);
    void Turn_right(int speed);

    int getCore();
    int getX();
    int getY();
    void Draw_Bowl();

    void ResetBowl();
};

BowlCatchWord::BowlCatchWord(int x, int y, int core)
{
    this->x = x;
    this->y = y;
    this->core = core;
}

BowlCatchWord::~BowlCatchWord()
{
}

void BowlCatchWord::Update_positon_of_bowl(int x,int y){
    this->x = x;
    this->y = y;
}

void BowlCatchWord::Turn_left(int speed){
    this->x -= speed;
}

void BowlCatchWord::Turn_right(int speed){
    this->x += speed;
}

int BowlCatchWord::getCore(){ return this->core; }
int BowlCatchWord::getX(){ return this->x; }
int BowlCatchWord::getY(){ return this->y; }

void BowlCatchWord::setCore(int core){
    this->core = core;
}

void BowlCatchWord::Draw_Bowl(){
    cout<<"|     |"<<endl;
}
//=========================================================

ListWord list_word;
void EnterListWord();
void ShowListWord();
void WriteDataIntoFile();
void ReadDataFromFile();
void SortData();
void GameCatchRightWord();

int main(int argc, char const *argv[])
{
    // EnterListWord();
    // ReadDataFromFile();
    // ShowListWord();
    // SortData();
    // ShowListWord();
    // WriteDataIntoFile();
    GameCatchRightWord();
    return 0;
}

void EnterListWord(){
    vector<Word> tmp;
    Word word; 
    int high = 0;
    string x="";
    while(true){
        cin>>word;
        if(word.getWord().length()==0) break;
        tmp = list_word.getVocabulary();
        high = list_word.size();
        x = word.getWord();
        if (list_word.binarySearchWord(tmp,0,high-1,x)==-1) {
            list_word.insert(word);
        }
    }  
}

void ShowListWord(){
    
    for(int i = 0; i < list_word.size(); i++)
    {
        cout<<list_word[i];
    }
    
}

void WriteDataIntoFile(){
    
    if (list_word.size()) {
        list_word.writeAllData();
    }
    
}
void ReadDataFromFile(){
    list_word.readAllData();
}

void SortData(){
    
    if (list_word.size()) {
        list_word.quick_sort_vocabulary(0,list_word.size()-1);
    }
}

void GameCatchRightWord(){
    clrscr();
    //man hinh start
    int sum = 1;
    string str = "#";
    
    while(sum <= 100){
        gotoXY(40,10);
        cout<<str<<sum<<"%"<<endl;
        delay(1000000);
        sum*=2;
        for(int i = 0; i < sqrt(sum); i++)
        {
            str +="#";
        }
        clrscr();
    }
    int keyboard = 0;
    bool exists = true;
    BowlCatchWord bowlgame(40,20);
    clrscr();
    gotoXY(0,0);
    while(exists){

        clrscr();  
        keyboard = inputKey();
        gotoXY(bowlgame.getX(), bowlgame.getY());
        bowlgame.Draw_Bowl();
        if(keyboard == 1075){
            bowlgame.Turn_left(5);
        }

        if(keyboard == 1077){
            bowlgame.Turn_right(5);
        }
        if(keyboard==0){
            exists = false;
        }
        delay(50000);
    }
}