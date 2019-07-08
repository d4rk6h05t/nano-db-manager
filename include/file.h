#ifndef DICTIONARY_CC_FILE_H_
#define DICTIONARY_CC_FILE_H_

#include <iostream>
#include <string>
#include <fstream>
#include <list>

namespace dictionary {

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
            void UpdateHeader();
            long int ReadAddress(long int position);
            void UpdateAddress(long int position, long int new_address);
            void UpdateName(long int position, std::string new_name);

        public:
            std::string name_;
            std::string dir_;
            std::string ext_;

            long int file_header_; 
            long int file_size_;

    }; 

}  // end namespace dictionary

#endif  // DICTIONARY_CC_FILE_H_