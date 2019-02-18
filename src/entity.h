#ifndef DICTIONARY_CC_ENTITY_H_
#define DICTIONARY_CC_ENTITY_H_

#include <cstddef>
#include <string>

const int MAX_LENGTH_NAME_ENTTITY_ = 35;
const int MAX_LENGTH_ENTTITY_ = 67;

namespace dictionary {

    class Entity {
    
        public:
             
            Entity();
            Entity(const std::string& name);
            Entity(const std::string& name,int* entity_address, int* attribute_address, int* data_address, int* next_entity_address);
            ~Entity();

            void SetName(const std::string& name); 
            void SetEntityAddress(int* entity_address); 
            void SetAttributeAddress(int* attribute_address); 
            void SetDataAddress(int* data_address); 
            void SetNextEntityAddress(int* next_entity_address);
                  
            char* GetName(); 
            int* GetEntityAddress(); 
            int* GetAttributeAddress();
            int* GetDataAddress();
            int* GetNextEntityAddress();

        private:
            char name_[MAX_LENGTH_NAME_ENTTITY_];
            int* entity_address_;
            int* attribute_address_;
            int* data_address_;
            int* next_entity_address_;

    };


}  // end namespace dictionary

#endif  // DICTIONARY_CC_ENTITY_H_

