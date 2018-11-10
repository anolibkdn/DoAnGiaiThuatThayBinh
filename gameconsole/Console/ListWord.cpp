#include<iostream>
#include<string>
#include<vector>
#include "Word.cpp"
#include<time.h>
#include<stdlib.h>
#include<fstream>
#include <sstream>
#include<stdio.h>

using namespace std;


class ListWord
{
private:
    vector<Word> _vocabulary;
public:
    ListWord();
    ListWord(const vector<Word> &vocabulary);
    ListWord(const ListWord &vocabulary);
    ~ListWord();

    //getmethod
    vector <Word> getVocabulary() const;

    //set method
    void setVocabulary(const vector<Word> &vocabulary);
    void setVocabulary(const ListWord &vocabulary);
    //insert method
    void insert(const Word &word,int index=-1);//=0 va header, -1 vao cuoi
    //update word
    void update(const Word &word, int index = -1);
    //sap xep quick sort
    void quick_sort(vector<Word> &vocabulary, int low, int high);
    void quick_sort_vocabulary(int low, int high);
    //binary search
    int binarySearchWord(vector<Word> &vocabulary, int low, int high, string x); 
    int binarySearchTopic(vector<Word> &vocabulary, int low, int high, int x); 
    //random n element word
    vector <Word> randomWord(int length);
    //random n element topic
    vector <Word> randomTopic(int length);

    //get topic, limit 20 word
    vector <Word> getTopic(int topic);
    //get anphal , limit 20 word
    vector <Word> getAnphal(char anphal);

    //read va write file
    void readAllData();
    vector <Word> readDataTopic();
    vector <Word> readDataAnphal();

    void writeAllData();
    void writeDataTopic();
    void writeDataAnphal();
    //push data trong file
    void writePushData();
    void writePushDataTopic();
    void writePushDataAnphal();
    //string write file format
    string stringWriteFileFormat(int index);
    Word convertStringToWord(string);
    //operator method
    Word &operator [] (int index);

    //size of list
    int size();

};

ListWord::ListWord()
{
}

ListWord::ListWord(const vector<Word> &vocabulary)
{
    
    for(int i = 0; i < vocabulary.size(); i++)
    {
        this->_vocabulary.push_back(vocabulary[i]);
    }
    
}

ListWord::ListWord(const ListWord &vocabulary)
{
    
    for(int i = 0; i < vocabulary._vocabulary.size(); i++)
    {
        this->_vocabulary.push_back(vocabulary._vocabulary[i]);
    }
}

ListWord::~ListWord()
{
}

//get method
vector <Word> ListWord::getVocabulary() const{
    return this->_vocabulary;
}

//set method
void ListWord::setVocabulary(const vector <Word> &vocabulary){
    this->_vocabulary.clear();
    for(int i = 0; i < vocabulary.size(); i++)
    {
        this->_vocabulary.push_back(vocabulary[i]);
    }
}

void ListWord::setVocabulary(const ListWord &vocabulary){
    this->_vocabulary.clear();
    for(int i = 0; i < vocabulary._vocabulary.size(); i++)
    {
        this->_vocabulary.push_back(vocabulary._vocabulary[i]);
    }
}

void ListWord::insert(const Word &word,int index){
    if(index == 0){
        this->_vocabulary.insert(this->_vocabulary.begin(),word);
    }else if(index == -1){
        this->_vocabulary.insert(this->_vocabulary.end(),word);
    }else{
        this->_vocabulary.insert(this->_vocabulary.begin() + index,word);
    }
}

//quick sort
void ListWord::quick_sort(vector<Word> &vocabulary, int low , int high)
{
    // If the first index less or equal than the last index
	if (low <= high)
	{
		// Create a Key/Pivot Element
		string key = vocabulary[(low+high)/2].getWord();
 
		// Create temp Variables to loop through array
		int i = low;
		int j = high;
 
		while (i <= j)
		{
			while (vocabulary[i].getWord() < key)
				i++;
			while (vocabulary[j].getWord() > key)
				j--;
 
			if (i <= j)
			{
				Word tmp = vocabulary[i];
                vocabulary[i] = vocabulary[j];
                vocabulary[j] = tmp;
				i++;
				j--;
			}
		}
 
		// Recursion to the smaller partition in the array after sorted above
		// Reference Giải Thuật Đệ Quy :: STDIO.VN
		if (low < j)
			quick_sort(vocabulary, low, j);
		if (high > i)
			quick_sort(vocabulary, i, high);
	}
}

//quick sort
void ListWord::quick_sort_vocabulary( int low , int high)
{
    // If the first index less or equal than the last index
	if (low <= high)
	{
		// Create a Key/Pivot Element
		string key = _vocabulary[(low+high)/2].getWord();
 
		// Create temp Variables to loop through array
		int i = low;
		int j = high;
 
		while (i <= j)
		{
			while (_vocabulary[i].getWord() < key)
				i++;
			while (_vocabulary[j].getWord() > key)
				j--;
 
			if (i <= j)
			{
				Word tmp = _vocabulary[i];
                _vocabulary[i] = _vocabulary[j];
                _vocabulary[j] = tmp;
				i++;
				j--;
			}
		}
 
		// Recursion to the smaller partition in the array after sorted above
		// Reference Giải Thuật Đệ Quy :: STDIO.VN
		if (low < j)
			quick_sort(_vocabulary, low, j);
		if (high > i)
			quick_sort(_vocabulary, i, high);
	}
}
//update method
void ListWord::update(const Word &word, int index ){
    if(index ==0 ){
        this->_vocabulary[index].update(word);
    }else if(index == -1){
        this->_vocabulary[this->_vocabulary.size()-1].update(word);
    }else{
        this->_vocabulary[index].update(word);
    }
}

//binary search word
int ListWord::binarySearchWord(vector <Word> &vocabulary, int low, int high, string x) 
{ 
   if (high >= low) 
   { 
        int mid = low + (high - low)/2; 
  
        // If the element is present at the middle  
        // itself 
        if (vocabulary[mid].getWord() == x)   
            return mid; 
  
        // If element is smaller than mid, then  
        // it can only be present in left subarray 
        if (vocabulary[mid].getWord() > x)  
            return binarySearchWord(vocabulary, low, mid-1, x); 
  
        // Else the element can only be present 
        // in right subarray 
        return binarySearchWord(vocabulary, mid+1, high, x); 
   } 
  
   // We reach here when element is not  
   // present in array 
   return -1; 
} 

//binary search topic
int ListWord::binarySearchTopic(vector <Word> &vocabulary, int low, int high, int x) 
{ 
   if (high >= low) 
   { 
        int mid = low + (high - low)/2; 
  
        // If the element is present at the middle  
        // itself 
        if (vocabulary[mid].getTopic() == x)   
            return mid; 
  
        // If element is smaller than mid, then  
        // it can only be present in left subarray 
        if (vocabulary[mid].getTopic() > x)  
            return binarySearchTopic(vocabulary, low, mid-1, x); 
  
        // Else the element can only be present 
        // in right subarray 
        return binarySearchTopic(vocabulary, mid+1, high, x); 
   } 
  
   return -1; 
} 

//random n word in listword
vector <Word> ListWord::randomWord(int length){
    int index;
    vector <Word> randomword;
    while(randomword.size() <= length){
        /* initialize random seed: */
        srand (time(NULL));
        /* generate secret number between 0 and length: */
        index = rand() % this->_vocabulary.size();
        int i;
        for( i = 0; i < randomword.size(); i++)
        {
            if(this->_vocabulary[index].getWord() == randomword[i].getWord()){
                break;
            }
        }
        
        if (i == randomword.size()) {
            randomword.push_back(this->_vocabulary[index]);
        }
        
    }
    return randomword;
}

//random n topic in listword
vector <Word> ListWord::randomTopic(int length){
    int index;
    vector <Word> randomtopic;
    while(randomtopic.size() <= length){
        /* initialize random seed: */
        srand (time(NULL));
        /* generate secret number between 0 and length: */
        index = rand() % this->_vocabulary.size();
        int i;
        for( i = 0; i < randomtopic.size(); i++)
        {
            if(this->_vocabulary[index].getWord() == randomtopic[i].getWord()){
                break;
            }
        }
        
        if (i == randomtopic.size()) {
            randomtopic.push_back(this->_vocabulary[index]);
        }
    }
    return randomtopic;
}
//get topic
vector <Word> ListWord::getTopic(int topic){
    vector <Word> gettopic;  
    for(int i = 0; i < this->_vocabulary.size(); i++){
        if(this->_vocabulary[i].getTopic()== topic){
            gettopic.push_back(this->_vocabulary[i]);
        }
        if(gettopic.size()== 20) break;
    }
    return gettopic;
}

//get anphal
vector <Word> ListWord::getAnphal(char anphal){
    vector <Word> getanphal;  
    for(int i = 0; i < this->_vocabulary.size(); i++){
        if(this->_vocabulary[i].getWord()[0]== anphal){
            getanphal.push_back(this->_vocabulary[i]);
        }
        if(getanphal.size()== 20) break;
    }
    return getanphal;
}

//operatpr method
Word &ListWord::operator[] (int index){
    if(index >=0 & index < this->_vocabulary.size()){
        return this->_vocabulary[index];
    }
}
//string write file format
string ListWord::stringWriteFileFormat(int index){
    
    Word tmp = this->_vocabulary[index];
    int a = tmp.getTopic();
    stringstream ss;
    ss << a;
    string str = ss.str();
    string format = tmp.getWord() +"%" + tmp.getMean() +"%" +tmp.getType() +"%" + tmp.getExample()+"%"+str+"\n";
    return format;
}
//thao tac voi file
//write all data
void ListWord::writeAllData(){
    fstream f;
	f.open("alldata.txt",ios::out);
    
    for(int i = 0; i < this->_vocabulary.size(); i++)
    {
        string tmp = this->stringWriteFileFormat(i);
        f<<tmp;
    }
    f.close();
}
//read all data
void ListWord::readAllData(){
    fstream f;
	f.open("alldata.txt",ios::in);
	string line;
	while (!f.eof())
	{
		getline(f, line);
		this->_vocabulary.push_back(this->convertStringToWord(line));
	}
    f.close();
}
//read data topic
vector <Word> ListWord::readDataTopic(){
    vector <Word> dataTopic;
    fstream f;
	f.open("datatopic.txt",ios::in);
	string line;
	while (!f.eof())
	{
		getline(f, line);
		dataTopic.push_back(this->convertStringToWord(line));
	}
    f.close();
    return dataTopic;
}
//read data anphal
vector <Word> ListWord::readDataAnphal(){
    vector <Word> dataAnphal;
    fstream f;
	f.open("dataanphal.txt",ios::in);
	string line;
	while (!f.eof())
	{
		getline(f, line);
        
        if (line.length()!=0) {
            dataAnphal.push_back(this->convertStringToWord(line));
        }	
	}
    f.close();
    return dataAnphal;
}

//write data topic
// void ListWord::writeDataTopic(){
//     vector<Word> word_topic = this->getTopic();
//     fstream f;
// 	f.open("datatopic.txt",ios::out);
    
//     for(int i = 0; i < this->_vocabulary.size(); i++)
//     {
//         string tmp = this->stringWriteFileFormat(i);
//         f<<tmp;
//     }
//     f.close();
// }


//handle function
Word ListWord::convertStringToWord(string String){
    Word word("");
    int count = 0;
    string w ="",m="",t="",e="",tp = "";
    for(int i = 0; i < String.length(); i++)
    {
        if (String[i] == '%'){
            count++;
            continue;
        }     
        if (count < 1) {
            w += String[i];
        }else if(count < 2){
            m += String[i]; 
        }else if(count < 3){
            t += String[i]; 
        }else if(count <4){
            e += String[i]; 
        }else{
            tp += String[i];
        }
    }
    word.update(w,m,t,e,atoi(tp.c_str()));
    return word;
}

int ListWord::size(){ return this->_vocabulary.size(); }