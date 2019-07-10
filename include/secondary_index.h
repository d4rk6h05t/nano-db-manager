#ifndef REPOSITORY_CC_SECONDARY_INDEX_H_
#define REPOSITORY_CC_SECONDARY_INDEX_H_

#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <vector>

#include "file.h"

const int READ_HEADER_FILE_I_ = 1048;
const int SIZE_DATA_BLOCK_ = 5; // last data is next address 
const int LENGTH_ADDRESS_I_ = sizeof(long int); // 8
const int SIZE_BLOCK_I_ = READ_HEADER_FILE_I_ - LENGTH_ADDRESS_I_; // 1040
const int SIZE_ROW_INT_I_ = sizeof(int) + (SIZE_DATA_BLOCK_ * sizeof(long int)); // 44
const int ROW_CAPACITY_I_ = SIZE_BLOCK_I_ / SIZE_ROW_INT_I_;  // 23

namespace repository {

    class SecondaryIndex : public File {
    
        public:
             
            SecondaryIndex(){}
            SecondaryIndex(const std::string& name){ name_ = name; ext_ = EXT_INDEX_; }
            ~SecondaryIndex(){}

            void CreateBlock(int position);
            static std::list< std::pair< int, std::vector<long int>>> ReadBlock(const std::string& name,int position);
            static void AddLineToBlock(const std::string& name,int position, std::list< std::pair<int, std::vector<long int>> > list_data_pair, int data, std::vector<long int> block_address);
            static void UpdateLineToBlock(const std::string& name,int position, int data, std::vector<long int> block_address);

            static void RemoveItem(const std::string& name,int position, int key, long int key_address, std::list< std::pair< int, std::vector<long int>>> bucket);
            static void RemoveLine(const std::string& name,int position, int key, long int key_address, std::list< std::pair< int, std::vector<long int>>> bucket);
            static std::vector<long int> GetCollectionAddress(const std::string& name,int position, int key);
                          
    
    }; 

}  // end namespace repository

#endif  // REPOSITORY_CC_SECONDARY_INDEX_H_