#ifndef DICTIONARY_CC_DATADICTIONARYFILE_H_
#define DICTIONARY_CC_DATADICTIONARYFILE_H_

#include <iostream>
#include <cstddef>
#include <string>
#include <fstream>
#include <list>
#include <vector>
#include <iterator>

#include "entity.h"
#include "attribute.h"

namespace dictionary {

    class DataDictionaryFile {
    
        public:
             
            DataDictionaryFile();
            DataDictionaryFile(const std::string& name);
            ~DataDictionaryFile();

            void SetId(int id);
            void SetName(const std::string& name);
            void SetDir(const std::string& dir); 
            void SetPath(const std::string& path); 
            void SetExt(const std::string& ext);
            void SetFileHeader(long int file_header);

            int GetId();
            std::string GetName();
            std::string GetDir();
            std::string GetPath();
            std::string GetExt();                        
            long int GetFileHeader();
            long int GetFileSize();
            
            void CreateFile();            
            void AddEntity(Entity entity);
            void AddAttribute(Attribute attribute);
            /*
            long int UpdateEntity(long int position, Entity entity);
            long int UpdateAttribute(long int position, Attribute attribute);
            long int RemoveEntity(long int position, Entity entity);
            long int RemoveAttribute(long int position, Attribute attribute);
            long int ReadEntity(long int position, Entity entity);
            long int ReadAttribute(long int position, Attribute attribute);
            */

        private:
            // file metadata
            int id_;
            std::string name_;
            std::string dir_;
            std::string path_;
            std::string ext_;

            long int file_header_;
            long int file_size_;

            std::list<Entity> list_entities_;
            std::list<Attribute> list_attributes_;


    };


}  // end namespace dictionary

#endif  // DICTIONARY_CC_DATADICTIONARYFILE_H_

