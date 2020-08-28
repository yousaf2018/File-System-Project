#include "FAT.h"
#include <iostream>
#include "fstream"
#include <string>
using namespace std;
    //Check file name already exists or not
        int FileAllocationTable::checkFileName(string name){
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
        void FileAllocationTable::InitializeIndexList_and_Name(int LenTex,string name){
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
        string FileAllocationTable::get_file_name(){
            return name;
        }
    //Set file name
        void FileAllocationTable::set_file_name(string name){
            this->name = name;
        }
    //Get list 
        int* FileAllocationTable::get_list(){
            return indexList;
        }
    //Get list size
        int FileAllocationTable::get_list_size(){
            return lengthIndex;
        }
    //Search file name
        int FileAllocationTable::searchFile(string name){
            if(this->name==name){
                return 1;
            }
            else{
                return 0;
            }
        }
        //Method count number of files
        int FileAllocationTable::count_files(){
            if(name=="None"){
                return 0;
            }
            else{
                return 1;
            }
        }
        //Method to load file
        void FileAllocationTable::Load_IndexList_and_Name(int LenTex,string name,int *IndextList){
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
        //Method to delete list of indexes
        void FileAllocationTable::deleteList(){
            delete [] indexList;
            indexList = NULL;
            lengthIndex = -1;
        }