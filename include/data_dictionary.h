#ifndef DICTIONARY_CC_DATADICTIONARY_H_
#define DICTIONARY_CC_DATADICTIONARY_H_

#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <iterator>

#include "entity.h"
#include "attribute.h"


namespace dictionary {

    class DataDictionary {
    
        public:
             
            DataDictionary();
            DataDictionary(const std::string& name);
            ~DataDictionary();

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
            void UpdateHeader();
            
            void UpdateAddress(long int position, long int new_address);            

            void UpdateEntity(Entity *entity);
            void AddEntity(Entity entity);

            
            void UpdateName(long int position, std::string new_name);
            std::list<Entity> ReadListEntities();
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

#endif  // DICTIONARY_CC_DATADICTIONARY_H_

