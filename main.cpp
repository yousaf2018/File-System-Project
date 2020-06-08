#include <iostream>

#include <string>

using namespace std;
//Class for file allocation table
//To hold name and index of file 
class FileAllocationTable{ 
    private:
        string name;
        int index;
        int indexlist[100];
    public:
    //Constructor to inialize name and index
        FileAllocationTable(){
            name = "None";
            index = -1;
            int i;
            for(i=0;i<100;i++){
                indexlist[i]=-1;
            }
            cout << "i am constructor here for Fat\n";
        }
        //Function to create new file with index
        void setFileAllocationTable(string name,int index){
            this->name = name;
            this->index = index;
            indexlist[0] = index;
        }
        //Function to check does file exists
        int checkFileInFileAllocationTable(string name){
            if(this->name==name){
                return index;
            }
            else{
                return -1;
            }
        }
        //Function return empty index for new file
        int checkIndex(){
            if(index==-1){
                return -1;
            }
            else{
                return 1;
            }
        }
        //to store blocks
        void setindexlist(int blockIndex){
            int i;
            for(i=0;i<100;i++){
                if(indexlist[i]==-1){
                    indexlist[i]=blockIndex;
                    break;
                }
            }
        }
        //to check file exists or not
        int checkFile(string input){
            if(input==name){
            cout << "We find your file in our system\n";
            cout << "Blocks indexes for file is below\n";
            int i;
            for(i=0;i<100;i++)
            {
                if(indexlist[i]==-1){
                    return 1;
                }
                else{
                    cout << indexlist[i] << endl;
                }
                
            }
            return 1;
            }
            else{
                return -1;
            }
        }

};
//Class for to store data in file system 
class data{
    private:
        int actualData[100];
    public:
    //Constructor to inialize with defualt value
        data(){
            int i;
            cout << "Data is initialize with defualt values\n";
            for(i=0;i<100;i++){
                actualData[i]=0;
            }
        }
        int checkIndexIsAvailable(int index){
            if(actualData[index]==0){
                actualData[index]=1;
                return 1;
            }
            else{
                return -1;
            }
        }

};

int main(){
    FileAllocationTable FAT[100];
    data dataFAT;
    int input,blocks,index,i,check1,check2,counter;
    string name;
    cout << "Well Come to File System\n";
    while(true){
        cout << "Enter 1 for create file\n";
        cout << "Enter 2 for show file data\n";
        cin >> input;
        //File Creation
        if(input==1){
            cout << "Enter file name\n";
            cin >> name;
            for(i=0;i<100;i++){
                //To check index is avaible in data
                cout << "Index allocation outside\n";
                check2=dataFAT.checkIndexIsAvailable(i);
                if(check2==1)
                {   
                    cout << "Index allocation inside\n";
                    cout << check2 << endl;
                    cout << i << endl;
                    index=i;
                    break;
                }
                else{   
                    continue;
                }
            }
            cout << "I am here to allocate the index\n";
            FAT[index].setFileAllocationTable(name,index);
            cout << "Enter number of blocks for file\n";
            cin >> blocks;
            i = 0;
            counter = 1;
            while(true){
                check2=dataFAT.checkIndexIsAvailable(i);
                if(check2==1){
                    FAT[index].setindexlist(i);
                    i++;
                    counter++;
                    if(counter==blocks){
                        break;
                    }
                }
                else{
                    i++;
                    if(i==100){
                    break;
                    }
                }
            }
            

        }
        else if(input==2){
            cout << "Enter your file name\n";
            cin >> name;
            for(i=0;i<100;i++){
                check1=FAT[i].checkFile(name);
                if(check1==1){
                    break;
                }
                else{
                    continue;
                }
            }
            if(i==100){
                cout << "File is not found\n";
            }
        }

    }

    return 0;
}