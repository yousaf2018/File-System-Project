#include <iostream>
#include "fstream"
#include <string>
using namespace std;
//Class for file allocation table
//To hold name for file with index list for to acess data
class FileAllocationTable{ 
    private:
        string name;
        int* indexList;
        int lengthIndex;
    public:
    //Constructor to create new file with name and index list
        FileAllocationTable(){
        name = "None";
        indexList = NULL;
        lengthIndex = -1;
        }
    //Check file name already exists or not
        int checkFileName(string name){
               if(this->name=="None"){
                return 1;
               }
               else if(this->name==name){
                   return -1;
               }
               else if(this->name!=name){
                   return 0;
               }         
            }
    //Initialize index list with length of user input text
        void InitializeIndexList_and_Name(int LenTex,string name){
            this->name = name;
            lengthIndex = LenTex;
            indexList = new int[LenTex];
            int i;
            for(i=0;i<LenTex;i++){
                indexList[i]=-1;
            }
            return;
        }
    //Get file name
        string get_file_name(){
            return name;
        }
    //Set file name
        void set_file_name(string name){
            this->name = name;
        }
    //Get list 
        int* get_list(){
            return indexList;
        }
    //Get list size
        int get_list_size(){
            return lengthIndex;
        }
    //Search file name
        int searchFile(string name){
            if(this->name==name){
                return 1;
            }
            else{
                return 0;
            }
        }
        //Method count number of files
        int count_files(){
            if(name=="None"){
                return 0;
            }
            else{
                return 1;
            }
        }
        //Method to load file
        void Load_IndexList_and_Name(int LenTex,string name,int *IndextList){
            this->name = name;
            lengthIndex = LenTex;
            indexList = new int[LenTex];
            int i;
            cout << "We are here to initialize values\n";
            cout << LenTex <<endl;
            for(i=0;i<LenTex;i++){
                indexList[i] = IndextList[i];
                cout << indexList[i] << endl;
            }
        }
};
//Class for to store data in file system 
class Data{
    private:
        char actualData[100];
    //Bit map for actual values 
        int bitMap[100]; 
    public:
    //Constructor to initialize with defualt value
        Data(){
            int i;
            for(i=0;i<100;i++){
                actualData[i]='@';
                bitMap[i]=-1;
            }
        }
    //To writing data of file in storage
        void writing_data(FileAllocationTable object,string text){
                int *ptr,sizeList,i,counter=0;
                ptr =  object.get_list();
                sizeList = object.get_list_size();
                for(i=0;i<100;i++){
                    if(counter==sizeList){
                        cout << "File is stored successfully\n";
                        break;
                    }
                    else if(bitMap[i]==-1){
                        actualData[i]=text[counter];
                        ptr[counter] = i;
                        bitMap[i] = 1;
                        counter++;
                    }
                    else if(counter<sizeList&&i==99){
                        cout << "Storage is full\n";
                    }
                }
        }
    //Reading data from storage
    void readData(FileAllocationTable object){
        int listLength,*List,i;
        cout << "Below is the data stored in our file system\n";
        listLength = object.get_list_size();
        List = object.get_list();
        for(i=0;i<listLength;i++){
            cout << actualData[List[i]];
        }
        cout << "\n";

    }
    //Delete data from storage 
    void deleteData(FileAllocationTable object){
        int listLength,*List,i;
        listLength = object.get_list_size();
        List = object.get_list();
        object.set_file_name("None");
        for(i=0;i<listLength;i++){
            actualData[List[i]]='@';
            bitMap[List[i]]=-1;
        }
        
        cout << "File is deleted sucessfully\n";
    }
    //Method to store snapshot
    void storeSnapShot(){
        ofstream write;
        int i;
        write.open("data.txt");
        for(i=0;i<100;i++){
            if(actualData[i]==' '){
                write << "_";
            }
            else{
            write << actualData[i];
            }
        }
        write << "#";
        write.close();
        write.open("bitmapt.txt");
        for(i=0;i<100;i++){
            write << " " << bitMap[i] << " ";
        }
        write.close();
    }
    //Method for load data 
    void load_data(){
        char reading;
        int readingInt,i;
        ifstream read;
        read.open("data.txt");
        while(!read.eof()){
            for(i=0;i<100;i++){ 
                read >> reading;
                if(reading=='#'){
                    break;
                }
                else if(reading=='_'){
                    actualData[i] = ' ';
                }
                else{
                actualData[i] = reading;
                }
            }
        }
        read.close();
        read.open("bitmapt.txt");
            while(!read.eof()){
            for(i=0;i<100;i++){
                read >> readingInt;
                bitMap[i] = readingInt;
            }
        }
        read.close();
    }

};

int main(){
    //Variables usded in file system
    int LenTex,i,j,check,fileNumber,index,indicator,counter,lenIndexList,*IndextList;
    ifstream read;
    ofstream write;
    char reading,Bracket;
    string name,text,choice;
    FileAllocationTable Files[100];
    Data storage;
    while(true){
    cout << "Enter 1 for create file\n";
    cout << "Enter 2 for search file\n";
    cout << "Enter 3 for display file data\n";
    cout << "Enter 4 for delete file\n";
    cout << "Enter 5 for to count number of files\n";
    cout << "Enter 6 to list name of all files\n";
    cout << "Enter 7 to save file system snapshot\n";
    cout << "Enter 8 to load snapshot previously stored\n";
    cin >> choice;
//Method for creation of file
        if(choice == "1"){
                indicator = 0;
                cout << "Enter name for file\n";
                cin.ignore();
                getline(cin,name);
            //checking does file name already exists or not
            for(i=0;i<100;i++){
                check=Files[i].checkFileName(name);
                if(check==-1){
                    cout << "Your input file name already exists\n";
                    indicator = 0;
                    break;
                }
                else if(check==1){
                    fileNumber = i;
                    indicator = 1;
                    break;
                }
                else if(check==0){
                    continue;
                }
                else if(i==99){
                    cout << "Our file system have no space for more files\n";
                    indicator = -1;
                    return 1;
                }
                cout << i;
            }
            if(indicator==1){
            //File creation with some text data
            cout << "Enter some text data for file\n";
            getline(cin,text);
            LenTex = text.size();
            //Initialize Index list with length of user input text
            Files[fileNumber].InitializeIndexList_and_Name(LenTex,name);
            //Writing data into storage
            storage.writing_data(Files[fileNumber],text);
            }
            else if(indicator==0){
                cout << "\n<<<Enter unique file name>>>\n\n";
            }
            else if(indicator==-1){
                cout << "File system have no more space delete extra files\n";
            }

        }
        //Method for search file in file system
        else if(choice=="2"){
            cout << "Enter file name for search\n";
            cin.ignore();
            getline(cin,name);
            cout << name << endl;
            for(i=0;i<100;i++){
                check = Files[i].searchFile(name);
                if(check==1){
                    cout << "<<<We find your file in our system>>>\n";
                    cout << Files[i].get_file_name() << endl;
                    break;
                }
                else if(i==99){
                    cout << "We donot find your file in our system\n";
                }
            }
        }
        //Method for display file from storage 
        else if(choice=="3"){
            cout << "Enter file name for display data\n";
            cin.ignore();
            getline(cin,name);
            cout << name << endl;
            for(i=0;i<100;i++){
                check = Files[i].searchFile(name);
                if(check==1){
                    cout << "<<<We find your file in our system>>>\n";
                    storage.readData(Files[i]);
                    break;
                }
                else if(i==99){
                    cout << "We donot find your file in our system\n";
                }
            }
        }
        //Method for delete file
        else if(choice=="4"){
            cout << "Enter file name for delete data\n";
            cin.ignore();
            getline(cin,name);
            cout << name << endl;
            for(i=0;i<100;i++){
                check = Files[i].searchFile(name);
                if(check==1){
                    cout << "<<<We find your file in our system>>>\n";
                    storage.deleteData(Files[i]);
                    Files[i].set_file_name("None");
                    break;
                }
                else if(i==99){
                    cout << "We donot find your file in our system\n";
                }
            }
        }
        //Method for count number of files
        else if(choice=="5"){
            counter = 0;
            for(i=0;i<100;i++){
                check=Files[i].count_files();
                if(check==1){
                    counter++;
                }
                else{
                    continue;
                }
            }
            cout << "Total number of files are :> " << counter << endl;            
        }
        //Method for list all name of files in file system
        else if(choice=="6"){
            indicator = 0;
            for(i=0;i<100;i++){
                check=Files[i].count_files();
                if(check==1){
                    name = Files[i].get_file_name();
                    cout << name << endl;
                    indicator = 1;
                }
                else{
                    continue;
                }
            }
            if(indicator==0){
                cout << "File system is empty\n";
            }
        }
        //Method for to save files permanantly which can be loaded after execution of program
        else if(choice=="7"){
        storage.storeSnapShot();
        write.open("FAT.txt");
            for(i=0;i<100;i++){
                check=Files[i].count_files();
                if(check==1){
                name = Files[i].get_file_name();
                write << name << " {";
                lenIndexList = Files[i].get_list_size();
                write << " " <<lenIndexList << " "; 
                IndextList = Files[i].get_list();
                for(j=0;j<lenIndexList;j++){
                    write << " " << IndextList[j] << " ";
                }
                write << "-1 ";
                }
                else {
                    continue;
                }
        }
        write << "@";
        write.close();
        }
        else if(choice=="8"){
            read.open("FAT.txt");
            while(!read.eof()){
            read >> name;
            if(name=="@"){
                read.close();
                storage.load_data();
                break;
            }
            read >> Bracket;
            read >> LenTex;
            int IndexList[LenTex]={0};
                for(i=0;i<100;i++){
                check = Files[i].count_files();
                if(check==0){
                    for(j=0;j<LenTex;j++){
                        read >> index;
                        IndexList[j] = index;
    
                    }
                        read >> index;
                        if(index==-1){
                        Files[i].Load_IndexList_and_Name(LenTex,name,IndexList);
                            break;
                        }
                    
                }
                        else{
                              continue;
                            }
                }

            }

           
           }

        
    }    
    return 0;
    
}
