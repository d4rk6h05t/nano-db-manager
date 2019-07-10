#ifndef REPOSITORY_CC_PRIMARY_INDEX_H_
#define REPOSITORY_CC_PRIMARY_INDEX_H_

#include <iostream>
#include <string>
#include <fstream>
#include <list>

#include "file.h"

const int READ_HEADER_FILE_ = 1048;
const int LENGTH_ADDRESS_ = sizeof(long int);
const int SIZE_BLOCK_ = READ_HEADER_FILE_ - LENGTH_ADDRESS_;
const int SIZE_ROW_INT = sizeof(int) + sizeof(long int);
const int ROW_CAPACITY = SIZE_BLOCK_ / SIZE_ROW_INT;


namespace repository {

    class PrimaryIndex : public File {
    
        public:
             
            PrimaryIndex(){}
            PrimaryIndex(const std::string& name){ name_ = name; ext_ = EXT_INDEX_; }
            ~PrimaryIndex(){}

            void CreateBlock(int position);
            static std::list< std::pair< int, long int> > ReadBlock(const std::string& name,int position);
            static void AddLineToBlock(const std::string& name,int position, std::list< std::pair<int, long int> > list_data_pair, int data, long int data_address);
            static long int SearchDataInt(const std::string& name, int position, int data);
            static void RemoveDataInt(const std::string& name, int position, int data, std::list< std::pair<int, long int> > list_data_pair);

        

    }; 

}  // end namespace repository

#endif  // REPOSITORY_CC_PRIMARY_INDEX_H_