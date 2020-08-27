    #include "Storage.h"
    #include <iostream>
    #include "fstream"
    #include <string>
    //To writing data of file in storage
        void Data::writing_data(FileAllocationTable object,string text){
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
    void Data::readData(FileAllocationTable object){
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
    void Data::deleteData(FileAllocationTable object){
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
    void Data::storeSnapShot(){
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
    void Data::load_data(){
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