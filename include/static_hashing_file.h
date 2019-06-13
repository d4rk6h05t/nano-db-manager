#ifndef DICTIONARY_CC_STATIC_HASHING_FILE_H_
#define DICTIONARY_CC_STATIC_HASHING_FILE_H_

#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <vector>

//#include "secondary_block.h"
const int NO_BUCKETS_SH_ = 9;
const int READ_HEADER_FILE_SH_ = 1048;
const int SIZE_DATA_BLOCK_SH_ = 5; // last data is next address
const int LENGTH_ADDRESS_SH_ = sizeof(long int); // 8
const int SIZE_BLOCK_SH_ = READ_HEADER_FILE_SH_ - LENGTH_ADDRESS_SH_; // 1040
const int SIZE_ROW_INT_SH_ = sizeof(int) + (SIZE_DATA_BLOCK_SH_ * sizeof(long int)); // 44
const int ROW_CAPACITY_SH_ = SIZE_BLOCK_SH_ / SIZE_ROW_INT_SH_;  // 23

namespace dictionary {

    class StaticHashingFile {
    
        public:
             
            StaticHashingFile();
            StaticHashingFile(const std::string& name);
            ~StaticHashingFile();

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
            static int GetHash(int key);
            static std::list< std::pair< int, std::vector<long int>>> ReadBlock(const std::string& name,int position);
            static void UpdateLineToBlock(const std::string& name, int hash_position, std::vector<long int> block_address);

        private:

            std::string name_;
            std::string dir_;
            std::string ext_;

            long int file_header_; 
            long int file_size_;

    }; 

}  // end namespace dictionary

#endif  // DICTIONARY_CC_STATIC_HASHING_FILE_H_