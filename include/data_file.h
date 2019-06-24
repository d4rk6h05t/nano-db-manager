#ifndef ARCHIVE_CC_DATA_FILE_H_
#define ARCHIVE_CC_DATA_FILE_H_

#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <iterator>
#include <vector>

#include "entity.h"
#include "attribute.h"
#include "primary_index_file.h"
#include "secondary_index_file.h"
#include "static_hashing_file.h"
#include "multilist_file.h"

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
            long int GetLengthStructLog(std::list<dictionary::Attribute> list_attributes);

            // Methods of File
            void CreateFile();
            void UpdateHeader();
            long int ReadAddress(long int position);
            void UpdateAddress(long int position, long int new_address);
            void UpdateName(long int position, std::string new_name);

            void AppendCharData(char * char_data,int length_char_data);
            void AppendIntData(int int_data);
            void AppendAddress(long int new_address);

            long int AppendData(std::list<dictionary::Attribute> list_attributes, std::list<std::string> & list_data, const std::string& entity_active, std::list<std::pair<int,long int>> list_multilist);
            long int UpdateData(std::list<dictionary::Attribute> list_attributes, std::list<std::string> & list_data, const std::string& entity_active, std::list<std::pair<int,long int>> list_multilist, long int log_address);
            //long int UpdateData(std::list<dictionary::Attribute> list_attributes, std::list<std::string> & list_data, const std::string& entity_active, std::list<std::pair<int,long int>> list_multilist);
            //long int RemoveData(std::list<dictionary::Attribute> list_attributes, std::list<std::string> & list_data, const std::string& entity_active, std::list<std::pair<int,long int>> list_multilist);
            
              
            
            void ReadRegister(std::list<dictionary::Attribute> list_attributes);
            
            std::string Update(std::list<dictionary::Attribute> list_attributes, const std::string& entity_active, long int log_address);
            int GetAmountLog(std::list<dictionary::Attribute> list_attributes);
            std::list<std::string> GetListStr(std::list<dictionary::Attribute> list_attributes, dictionary::Attribute attr, long int length_struct_log, long int length_ks, int amount_log );
            std::pair<std::string,std::string> GetPrevNext(std::list<std::string> list_str,const std::string& key_str);

            std::list<std::pair<int,long int>> GetListDataMultilist(std::list<dictionary::Attribute> list_attributes, dictionary::Attribute attribute);

            int GetSizeRegister(std::list<dictionary::Attribute> list_attributes);
            static std::list<long int> GetAddressBySearchKey(const std::string & name,const std::string & search_key, long int file_header, std::list<dictionary::Attribute> list_attributes);
            
            long int GetAddress(std::list<dictionary::Attribute> list_attributes, long int length_struct_log , int key);
            long int GetAddress(std::list<dictionary::Attribute> list_attributes, long int length_struct_log ,long int key_addr);
            
            long int GetAddressByNextAddress(std::list<dictionary::Attribute> list_attributes, long int length_struct_log ,long int next_addr);
            
            long int GetAddress(std::list<dictionary::Attribute> list_attributes, long int length_struct_log , const std::string& key_addr);
            
            long int GetNextAddress(std::list<dictionary::Attribute> list_attributes, long int length_struct_log , int key);
            long int GetNextAddress(std::list<dictionary::Attribute> list_attributes, long int length_struct_log , long int key_addr);

            int GetDataInt(std::list<dictionary::Attribute> list_attributes, int index, long int length_struct_log ,long int key_addr);
            

        private:

            std::string name_;
            std::string dir_;
            std::string ext_;
            
            long int file_header_;
            long int file_size_;

    }; 

}  // end namespace archive

#endif  // ARCHIVE_CC_DATA_FILE_H_