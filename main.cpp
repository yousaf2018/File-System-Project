#include <iostream>

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
            cout << "Length " << lengthIndex << endl;
            indexList = new int[LenTex];
            int i;
            for(i=0;i<LenTex;i++){
                indexList[i]=-1;
            }
            return;
        }
    //Get file name
        void get_file_name(){
            cout << "File name is " << name << endl;
        }
    //Get list 
        int* get_list(){
            return indexList;
        }
    //Get list size
        int get_list_size(){
            return lengthIndex;
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
                cout << "Size of list " << sizeList << endl;
                cout << actualData[99] << endl; 
                for(i=0;i<100;i++){
                    if(counter==sizeList){
                        cout << "File is stored successfully\n";
                        break;
                    }
                    else if(bitMap[i]==-1){
                        actualData[i]=text[counter];
                        cout << text[counter] << endl;
                        ptr[i] = i;
                        bitMap[i] = 1;
                        counter++;
                    }
                    else if(counter<sizeList&&i==99){
                        cout << "Storage is full\n";
                    }
                }
        }


};

int main(){
    int LenTex,i,check,fileNumber,indicator=0;
    string name,text,choice;
    FileAllocationTable Files[100];
    Data storage;
    while(true){
    cout << "Enter 1 for create file\n";
    cin >> choice;
//Method for creation of file
        if(choice == "1"){
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
            cout << "Last index " << text[6] << endl;
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
    }    
    return 0;
}
