#ifndef ARCHIVE_CC_DATA_FILE_H_
#define ARCHIVE_CC_DATA_FILE_H_

#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <iterator>

#include "entity.h"
#include "attribute.h"


const int MAX_LENGTH_NAME_DATA_FILE_ = 35;
const long int NULL_DATA_FILE_ = -1;

namespace archive {

    class DataFile {
    
        public:
             
            DataFile();
            DataFile(const std::string& name);
            ~DataFile();

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

            void AppendCharData(char * char_data,int length_char_data);
            void AppendIntData(int int_data);
            void AppendAddress(long int new_address);

            void AppendData(std::list<dictionary::Attribute> list_attributes);
            
            void ReadRegister(std::list<dictionary::Attribute> list_attributes);
            int GetSizeRegister(std::list<dictionary::Attribute> list_attributes);

        private:
            std::string name_;
            std::string dir_;
            std::string ext_;
            long int file_header_;
            long int file_size_;

            //long int register_address_;
            //std::list<dictionary::attribute> list_attributes_;
            //long int next_register_address_;

            // 0: Without Type Index
            // 1: Search Key
            // 2: Primary Index
            // 3: Secondary Index
            //int type_index_; 
            //long int index_address_;
    }; 

}  // end namespace archive

#endif  // ARCHIVE_CC_DATA_FILE_H_