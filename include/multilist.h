#ifndef DICTIONARY_CC_MULTILIST_H_
#define DICTIONARY_CC_MULTILIST_H_

#include <iostream>
#include <string>
#include <fstream>
#include <list>

#include "file.h"

const int READ_HEADER_FILE_M_ = 1048;
const int LENGTH_ADDRESS_M_ = sizeof(long int);
const int SIZE_BLOCK_M_ = READ_HEADER_FILE_M_ - LENGTH_ADDRESS_M_;
const int SIZE_ROW_INT_M_ = sizeof(int) + sizeof(long int);
const int ROW_CAPACITY_M_ = SIZE_BLOCK_M_ / SIZE_ROW_INT_M_;

namespace dictionary {

    class Multilist : public File {
    
        public:
             
            Multilist(){}
            Multilist(const std::string& name){ name_ = name; }
            ~Multilist(){}

            void CreateBlock(int position);
            static std::list< std::pair< int, long int> > ReadBlock(const std::string& name,int position);
            static void AddLineToBlock(const std::string& name,int position, std::list< std::pair<int, long int> > list_data_pair, int data, long int data_address);

    
    }; 

}  // end namespace dictionary

#endif  // DICTIONARY_CC_MULTILIST_H_