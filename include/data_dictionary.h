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
            // Constructor & destructors
            DataDictionary();
            DataDictionary(const std::string& name);
            ~DataDictionary();
            // Setters
            void SetId(int id);
            void SetName(const std::string& name);
            void SetDir(const std::string& dir); 
            void SetPath(const std::string& path); 
            void SetExt(const std::string& ext);
            void SetFileHeader(long int file_header);
            // Getters
            int GetId();
            std::string GetName();
            std::string GetDir();
            std::string GetPath();
            std::string GetExt();                        
            long int GetFileHeader();
            long int GetFileSize();
            
            // Methods of File
            void CreateFile();
            void UpdateHeader();
            void UpdateAddress(long int position, long int new_address);
            void UpdateName(long int position, std::string new_name);

            void UpdateChar(long int position, char new_char);
            void UpdateInt(long int position, int new_int);

            // Methods of entities
            void AddEntity(Entity entity);
            void UpdateEntity(std::list<Entity> list_entities, Entity *entity);
            void RemoveEntity(std::list<Entity> list_entities, std::string remove_entity);
            Entity SearchEntity(std::list<Entity> list_entities, std::string new_entity);            
            std::list<Entity> ReadListEntities();
            
            void AddAttribute(Attribute attribute);
            void UpdateAttribute(std::list<Attribute> list_attributes, Attribute attribute);
            std::list<Attribute> ReadListAttributes(Entity entity);
            void RemoveAttribute(Entity current_entity, std::list<Attribute> list_attributes, std::string remove_attribute);
            Attribute SearchAttribute(std::list<Attribute> list_attributes, std::string name_attribute);

        private:
            // file metadata
            int id_;
            std::string name_;
            std::string dir_;
            std::string path_;
            std::string ext_;
            long int file_header_;
            long int file_size_;
    };


}  // end namespace dictionary

#endif  // DICTIONARY_CC_DATADICTIONARY_H_

