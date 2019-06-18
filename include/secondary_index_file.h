#ifndef DICTIONARY_CC_SECONDARY_INDEX_FILE_H_
#define DICTIONARY_CC_SECONDARY_INDEX_FILE_H_

#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <vector>

//#include "secondary_block.h"

const int READ_HEADER_FILE_I_ = 1048;
const int SIZE_DATA_BLOCK_ = 5; // last data is next address 
const int LENGTH_ADDRESS_I_ = sizeof(long int); // 8
const int SIZE_BLOCK_I_ = READ_HEADER_FILE_I_ - LENGTH_ADDRESS_I_; // 1040
const int SIZE_ROW_INT_I_ = sizeof(int) + (SIZE_DATA_BLOCK_ * sizeof(long int)); // 44
const int ROW_CAPACITY_I_ = SIZE_BLOCK_I_ / SIZE_ROW_INT_I_;  // 23

namespace dictionary {

    class SecondaryIndexFile {
    
        public:
             
            SecondaryIndexFile();
            SecondaryIndexFile(const std::string& name);
            ~SecondaryIndexFile();

            // Setters
            void SetName(const std::string& name);
            void SetDir(const std::string& dir); 
            void SetExt(const std::string& ext);
            
            void SetFileHeader(long int file_header);
            // Getters
            std::string GetName();
            std::string GetDir();
            std::string GetExt();                        
            
            long int GetFileHeader();
            long int GetFileSize();
            
            // Methods of File
            void CreateFile();
            void UpdateHeader();
            long int ReadAddress(long int position);
            void UpdateAddress(long int position, long int new_address);
            void UpdateName(long int position, std::string new_name);

            void CreateBlock(int position);
            static std::list< std::pair< int, std::vector<long int>>> ReadBlock(const std::string& name,int position);
            static void AddLineToBlock(const std::string& name,int position, std::list< std::pair<int, std::vector<long int>> > list_data_pair, int data, std::vector<long int> block_address);
            static void UpdateLineToBlock(const std::string& name,int position, int data, std::vector<long int> block_address);

            static void RemoveItem(const std::string& name,int position, int key, long int key_address, std::list< std::pair< int, std::vector<long int>>> bucket);

        private:

            std::string name_;
            std::string dir_;
            std::string ext_;

            long int file_header_; 
            long int file_size_;

    }; 

}  // end namespace dictionary

#endif  // DICTIONARY_CC_SECONDARY_INDEX_FILE_H_