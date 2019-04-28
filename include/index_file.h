#ifndef DICTIONARY_CC_INDEX_FILE_H_
#define DICTIONARY_CC_INDEX_FILE_H_

#include <iostream>
#include <string>
#include <fstream>

namespace dictionary {

    class IndexFile {
    
        public:
             
            IndexFile();
            IndexFile(const std::string& name, int type);
            ~IndexFile();

            // Setters
            void SetName(const std::string& name);
            void SetDir(const std::string& dir); 
            void SetExt(const std::string& ext);
            void SetTypeIndex(int type);
            void SetFileHeader(long int file_header);
            // Getters
            std::string GetName();
            std::string GetDir();
            std::string GetExt();                        
            int GetTypeIndex();
            long int GetFileHeader();
            long int GetFileSize();

            
            // Methods of File
            void CreateFile();
            void UpdateHeader();
            long int ReadAddress(long int position);
            void UpdateAddress(long int position, long int new_address);
            void UpdateName(long int position, std::string new_name);

        private:

            std::string name_;
            std::string dir_;
            std::string ext_;

            long int file_header_; 
            long int file_size_;

            // 0: Without Type Index
            // 1: Primary Index
            // 2: Secondary Index
            // 3: Search Key
            // 4: TreeB+
            // 5: Hash Static
            // 6: Hash Dinamic
            // 7: Multilist
            int type_;
    }; 

}  // end namespace dictionary

#endif  // DICTIONARY_CC_INDEX_FILE_H_