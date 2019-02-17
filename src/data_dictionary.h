#ifndef DICTIONARY_CC_DATADICTIONARY_H_
#define DICTIONARY_CC_DATADICTIONARY_H_

#include <iostream>
#include <cstddef>
#include <string>
#include <fstream>
#include <list>


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
            void SetPtrHeader(int* prt_header);

            void AddEntity(Entity entity);
            void AddAttribute(Attribute attribute);

            int GetId();
            std::string GetName();
            std::string GetDir();
            std::string GetPath();
            std::string GetExt();
            int* GetPtrHeader();
            // list<Entity> GetListEntities();
            // list<Attribute> GetListAttributes();

        private:
        	// file metadata
        	int id_;
        	std::string name_;
        	std::string dir_;
            std::string path_;
            std::string ext_;
            // data ti save in the file
        	int* ptr_header_;
            std::list<Entity> list_entities_;
            std::list<Attribute> list_attributes_;
    };


}  // end namespace dictionary

#endif  // DICTIONARY_CC_DATADICTIONARY_H_

