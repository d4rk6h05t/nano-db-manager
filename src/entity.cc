
#include "entity.h"

namespace dictionary {


    Entity::Entity(){
        entity_address_ = NULL;
        attribute_address_ = NULL;
        data_address_ = NULL;
        next_entity_address_  = NULL;   
    }
    
    Entity::Entity(const std::string& name){
        for (int i = 0; i < MAX_LENGTH_NAME_ENTTITY_; i++){
            name_[i] = name[i];      
        }
        entity_address_ = NULL;
        attribute_address_ = NULL;
        data_address_ = NULL;
        next_entity_address_  = NULL;
    }

    Entity::Entity(const std::string& name,int* entity_address, int* attribute_address, int* data_address, int* next_entity_address){
        for (int i = 0; i < MAX_LENGTH_NAME_ENTTITY_; i++){
            name_[i] = name[i];      
        }
        entity_address_ = entity_address;
        attribute_address_ = attribute_address;
        data_address_ = data_address;
        next_entity_address_  = next_entity_address;   
    }

    Entity::~Entity(){}

    void Entity::SetName(const std::string& name){ 
        for (int i = 0; i < MAX_LENGTH_NAME_ENTTITY_; i++){
            name_[i] = name[i];      
        }
    }
    
    void Entity::SetEntityAddress(int* entity_address) { entity_address_ = entity_address; }
    void Entity::SetAttributeAddress(int* attribute_address) { attribute_address_ = attribute_address; }
    void Entity::SetDataAddress(int* data_address) { data_address_ = data_address; }
    void Entity::SetNextEntityAddress(int* next_entity_address) { next_entity_address_  = next_entity_address; }
                  
    char* Entity::GetName() { return name_; }
    int* Entity::GetEntityAddress() { return entity_address_; }
    int* Entity::GetAttributeAddress() { return attribute_address_; }
    int* Entity::GetDataAddress() { return data_address_; }
    int* Entity::GetNextEntityAddress() { return next_entity_address_; }


}  // end namespace dictionary
