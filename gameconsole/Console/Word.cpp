#include<iostream>
#include<string>

using namespace std;


class Word
{
private:
    string _word,_mean,_type,_example;
    int _topic;
public:
    Word(string word="",string mean="", string type="", string example="",int topic=0);
    Word(const Word &word);
    ~Word();

    //get phuong thuc
    string getWord();
    string getMean();
    string getType();
    string getExample();
    int getTopic();

    //set phuong thuc
    void setWord(string);
    void setMean(string);
    void setType(string);
    void setExample(string);
    void setTopic(int topic);

    //update word
    void update(string word="",string mean="", string type="", string example="", int topic=0);
    void update(const Word &word);

    //operator method
    friend istream &operator >> (istream &in, Word &Word);
    friend ostream &operator << (ostream &out,const Word &Word);

};

Word::Word(string word, string mean, string type, string example, int topic)
{
    this->_word = word;
    this->_mean = mean;
    this->_type = type;
    this->_example = example;
    this->_topic = topic;
}

Word::Word(const Word &word)
{
    this->_word = word._word;
    this->_mean = word._mean;
    this->_type = word._type;
    this->_example = word._example;
    this->_topic = word._topic;
}

Word::~Word()
{
}

//get method
string Word::getWord(){ return this->_word; }
string Word::getType(){ return this->_type; }
string Word::getMean(){ return this->_mean; }
string Word::getExample(){ return this->_example; }
int Word::getTopic(){ return this->_topic; }

//set method
void Word::setWord(string word){ this->_word = word; }
void Word::setMean(string mean){ this->_word = mean; }
void Word::setType(string type){ this->_word = type; }
void Word::setExample(string example){ this->_word = example; }
void Word::setTopic(int topic){ this->_topic = topic ; }

//update method
void Word::update(string word, string mean, string type, string example, int topic){
    this->_word = word;
    this->_mean = mean;
    this->_type = type;
    this->_example = example;
    this->_topic = topic;
}

void Word::update(const Word &word)
{
    this->_word = word._word;
    this->_mean = word._mean;
    this->_type = word._type;
    this->_example = word._example;
    this->_topic = word._topic;
}

//operator method
istream &operator >> (istream &in, Word & word){
    cout<<"Word: ";
    getline(in,word._word);
    in.ignore();
    cout<<"Mean: ";
    getline(in,word._mean);
    in.ignore();
    cout<<"Type: ";
    getline(in,word._type);
    in.ignore();
    cout<<"Example: ";
    getline(in,word._example);
    in.ignore();
    cout<<"Topic: ";
    in>>word._topic;
    in.ignore();
    return in;
}

ostream &operator << (ostream &out, const Word &word){
    out<<word._word<<endl<<word._mean<<endl<<word._type<<endl<<word._example<<endl<<word._topic;
    return out;
}


