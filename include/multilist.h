#ifndef DICTIONARY_CC_MULTILIST_H_
#define DICTIONARY_CC_MULTILIST_H_

#include <iostream>
#include <string>
#include <fstream>
#include <list>

const int READ_HEADER_FILE_M_ = 1048;
const int LENGTH_ADDRESS_M_ = sizeof(long int);
const int SIZE_BLOCK_M_ = READ_HEADER_FILE_M_ - LENGTH_ADDRESS_M_;
const int SIZE_ROW_INT_M_ = sizeof(int) + sizeof(long int);
const int ROW_CAPACITY_M_ = SIZE_BLOCK_M_ / SIZE_ROW_INT_M_;

namespace dictionary {

    class Multilist {
    
        public:
             
            Multilist();
            Multilist(const std::string& name);
            ~Multilist();

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
            static std::list< std::pair< int, long int> > ReadBlock(const std::string& name,int position);
            static void AddLineToBlock(const std::string& name,int position, std::list< std::pair<int, long int> > list_data_pair, int data, long int data_address);

        private:

            std::string name_;
            std::string dir_;
            std::string ext_;

            long int file_header_; 
            long int file_size_;

    }; 

}  // end namespace dictionary

#endif  // DICTIONARY_CC_MULTILIST_H_