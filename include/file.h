#ifndef REPOSITORY_CC_FILE_H_
#define REPOSITORY_CC_FILE_H_

#include <iostream>
#include <string>
#include <fstream>
#include <list>

#include <cstdlib>
#include <filesystem>

const std::string EXT_INDEX_ = ".idx";
const std::string EXT_DATA_FILE_ = ".dat";
const std::string EXT_DATA_DICTIONARY_ = ".dd";
const int MAX_LENGTH_NAME_ = 35;

namespace repository {

    class File {
    
        public:
             
            File();
            File(const std::string& name);
            ~File();

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
            void CreateDirectory();
            void UpdateHeader();
            long int ReadAddress(long int position);
            void UpdateAddress(long int position, long int new_address);
            void UpdateName(long int position, std::string new_name);

            void UpdateChar(long int position, char new_char);
            void UpdateInt(long int position, int new_int);

        public:
            std::string name_;
            std::string dir_;
            std::string ext_;

            long int file_header_; 
            long int file_size_;

    }; 

}  // end namespacerepository

#endif  // REPOSITORY_CC_FILE_H_