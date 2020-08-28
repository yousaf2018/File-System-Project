#include <string>
using namespace std;
//Class for file allocation table
//To hold name for file with indexes list and length of list
class FileAllocationTable{ 
    private:
        string name;
        int* indexList;
        int lengthIndex;
    public:
    //Constructor
        FileAllocationTable(){
        name = "None";
        indexList = NULL;
        lengthIndex = -1;
        }

        int checkFileName(string);
        void InitializeIndexList_and_Name(int,string);
        string get_file_name();
        void set_file_name(string);
        int* get_list();
        int get_list_size();
        int searchFile(string);
        int count_files(); 
        void Load_IndexList_and_Name(int,string,int*);
        void deleteList();
};