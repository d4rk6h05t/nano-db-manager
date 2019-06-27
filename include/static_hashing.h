#ifndef DICTIONARY_CC_STATIC_HASHING_H_
#define DICTIONARY_CC_STATIC_HASHING_H_

#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <vector>

//#include "secondary_block.h"
const int NO_BUCKETS_SH_ = 7;
const int READ_HEADER_FILE_SH_ = 1048;
const int LENGTH_ADDRESS_SH_ = sizeof(long int);
const int SIZE_BLOCK_SH_ = READ_HEADER_FILE_SH_ - LENGTH_ADDRESS_SH_;
const int SIZE_ROW_INT_SH_ = sizeof(int) + sizeof(long int);
const int ROW_CAPACITY_SH_ = SIZE_BLOCK_SH_ / SIZE_ROW_INT_SH_;

namespace dictionary {

    class StaticHashing {
    
        public:
             
            StaticHashing();
            StaticHashing(const std::string& name);
            ~StaticHashing();

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
            static long int GetFileSize(const std::string& name);
            
            // Methods of File
            void CreateFile();
            void UpdateHeader();
            static int ReadInt(const std::string& name, long int position);
            static long int ReadAddress(const std::string& name, long int position);
            static void UpdateInt(const std::string& name, long int position, int new_address);
            static void UpdateAddress(const std::string& name, long int position, long int new_address);
            void UpdateName(long int position, std::string new_name);
            
            static std::vector<long int> GetBucketsAddress(const std::string& name);

            static void CreateBlock(const std::string& name, int position);
            static int GetHash(int key);
            static std::list< std::pair< int, long int>> ReadBlock(const std::string& name,int position);
            static void AddLineToBlock(const std::string& name,int position, std::list< std::pair<int, long int> > list_data_pair, int data, long int data_address);
            static long int GetAddress(const std::string& name,long int bucket_address, int key );
            static long int GetBucketAddress(const std::string& name,int hash);
            static void RemoveDataInt(const std::string& name, int position, int data, std::list< std::pair<int, long int>> list_data_pair);
        
        private:

            std::string name_;
            std::string dir_;
            std::string ext_;

            long int file_header_; 
            long int file_size_;

    }; 

}  // end namespace dictionary

#endif  // DICTIONARY_CC_STATIC_HASHING_H_