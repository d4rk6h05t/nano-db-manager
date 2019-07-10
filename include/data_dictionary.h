#ifndef REPOSITORY_CC_DATADICTIONARY_H_
#define REPOSITORY_CC_DATADICTIONARY_H_

#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <iterator>

//#include <bits/stdc++.h> 
//#include <sys/stat.h> 
//#include <sys/types.h> 

#include "entity.h"
#include "attribute.h"
#include "file.h"

namespace repository {

    class DataDictionary : public File {
    
        public:
            // Constructor & destructors
            DataDictionary(){}
            DataDictionary(const std::string& name){  name_ = name; ext_ = EXT_DATA_DICTIONARY_; }
            ~DataDictionary(){}

            // Methods of entities
            void AddEntity(dictionary::Entity entity);
            void UpdateEntity(std::list<dictionary::Entity> list_entities, dictionary::Entity *entity);
            void RemoveEntity(std::list<dictionary::Entity> list_entities, std::string remove_entity);
            dictionary::Entity SearchEntity(std::list<dictionary::Entity> list_entities, std::string new_entity);            
            std::list<dictionary::Entity> ReadListEntities();
            
            void AddAttribute(dictionary::Attribute attribute);
            void UpdateAttribute(std::list<dictionary::Attribute> list_attributes, dictionary::Attribute attribute);
            std::list<dictionary::Attribute> ReadListAttributes(dictionary::Entity entity);
            void RemoveAttribute(dictionary::Entity current_entity, std::list<dictionary::Attribute> list_attributes, std::string remove_attribute);
            dictionary::Attribute SearchAttribute(std::list<dictionary::Attribute> list_attributes, std::string name_attribute);
            long int LengthStartToSearchKey(std::list<dictionary::Attribute> list_attributes); 
    };


}  // end namespace repository

#endif  // REPOSITORY_CC_DATADICTIONARY_H_

