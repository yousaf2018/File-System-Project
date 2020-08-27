#include "FAT.h"
#include <string>
using namespace std;
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
    void writing_data(FileAllocationTable,string);
    void readData(FileAllocationTable);
    void deleteData(FileAllocationTable);
    void storeSnapShot();
    void load_data();
};