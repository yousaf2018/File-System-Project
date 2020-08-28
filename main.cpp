#include <bits/stdc++.h> 
#include "fstream"
#include <string>
#include <typeinfo>
using namespace std;
#include "Storage.h"
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
    cout << "Enter 9 for edit file name\n";
    cout << "Enter 10 for overwrite file data\n";
    cout << "Enter 11 for append file data\n";
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

        //Method to load previous snapshot of files stored in memory
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

        //Method for Rename file in file system
        else if(choice=="9"){
            cout << "Enter file name for Rename\n";
            cin.ignore();
            getline(cin,name);
            for(j=0;j<100;j++){
                check = Files[j].searchFile(name);
                if(check==1){
                    cout << "<<<We find your file in our system>>>\n";
                    cout << "Enter New file name\n";
                    getline(cin,name);
                indicator = 0;
            //checking does file name already exists or not
            for(i=0;i<100;i++){
                check=Files[i].checkFileName(name);
                if(check==-1){
                    cout << "Your input file name already exists\n";
                    indicator = 0;
                    break;
                }
                else if(check==1){
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
            Files[j].set_file_name(name);
            break;
            }
            else if(indicator==0){
                cout << "\n<<<Enter unique file name>>>\n\n";
            }
            else if(indicator==-1){
                cout << "File system have no more space delete extra files\n";
            }

                }
                else if(j==99){
                    cout << "We donot find your file in our system\n";
                }
            }



        }

        //Method for overwrite file data
        else if(choice=="10"){
            cout << "Enter file name for overwrite file data\n";
            cin.ignore();
            getline(cin,name);
            cout << name << endl;
            for(i=0;i<100;i++){
                check = Files[i].searchFile(name);
                if(check==1){
            storage.deleteData(Files[i]);
            //File creation with some text data
            cout << "Enter some text data for file\n";
            getline(cin,text);
            LenTex = text.size();
            //Initialize Index list with length of user input text
            Files[i].InitializeIndexList_and_Name(LenTex,name);
            //Writing data into storage
            storage.writing_data(Files[i],text);
                }
                else if(i==99){
                    cout << "We donot find your file in our system\n";
                }
            }
        }


        //Method for append file data
        else if(choice=="11"){
            char *Stored;
            int Length;
            cout << "Enter file name for append file data\n";
            cin.ignore();
            getline(cin,name);
            for(i=0;i<100;i++){
                check = Files[i].searchFile(name);
                if(check==1){
            Stored = storage.help_to_append(Files[i]);
            Length = Files[i].get_list_size();
            string Stored_part="";
            for(j=0;j<Length;j++){
                Stored_part = Stored_part + *Stored;
                Stored++;
            }
            cout << "Enter some text to append in file before your input make sure at least one space\n";
            cin.ignore();
            getline(cin,text);
            Stored_part.append(text);
            cout << Stored_part << endl;
            LenTex = Stored_part.size();
            storage.deleteData(Files[i]);
            Files[i].deleteList();
            Files[i].set_file_name("None");
           // Initialize Index list with length of user input text
            Files[i].InitializeIndexList_and_Name(LenTex,name);
          //  Writing data into storage
            storage.writing_data(Files[i],Stored_part);
            break;
                }
                else if(i==99){
                    cout << "We donot find your file in our system\n";
                }
            }
        }

        
    }    
    return 0;
    
}
