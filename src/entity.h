#ifndef DICTIONARY_CC_ENTITY_H_
#define DICTIONARY_CC_ENTITY_H_

#include <cstddef>
#include <iostream>

const int MAX_LENGTH_NAME_ENTTITY_ = 35;
const int MAX_LENGTH_ENTTITY_ = 67;
const long int NULL_ENTITY_ = -1;

namespace dictionary {

    class Entity {
    
        public:
             
            Entity();
            Entity(const std::string& name);
            Entity(const std::string& name,long int entity_address, long int attribute_address, long int data_address, long int next_entity_address);
            ~Entity();

            void SetName(const std::string& name); 
            void SetEntityAddress(long int entity_address); 
            void SetAttributeAddress(long int attribute_address); 
            void SetDataAddress(long int data_address); 
            void SetNextEntityAddress(long int next_entity_address);
                  
            char* GetName(); 
            long int GetEntityAddress(); 
            long int GetAttributeAddress();
            long int GetDataAddress();
            long int GetNextEntityAddress();

            void DisplayEntity();

        private:

            char name_[MAX_LENGTH_NAME_ENTTITY_];
            long int entity_address_;
            long int attribute_address_;
            long int data_address_;
            long int next_entity_address_;

            

    }; 

}  // end namespace dictionary

#endif  // DICTIONARY_CC_ENTITY_H_

