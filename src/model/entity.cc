
#include "entity.h"

namespace dictionary {


    Entity::Entity(){
        entity_address_ = NULL_ENTITY_;
        attribute_address_ = NULL_ENTITY_;
        data_address_ = NULL_ENTITY_;
        next_entity_address_  = NULL_ENTITY_;   
    }
    
    Entity::Entity(const std::string& name){
        for (int i = 0; i < MAX_LENGTH_NAME_ENTTITY_; i++)
            name_[i] = name[i];      
        entity_address_ = NULL_ENTITY_;
        attribute_address_ = NULL_ENTITY_;
        data_address_ = NULL_ENTITY_;
        next_entity_address_  = NULL_ENTITY_;
    }

    Entity::Entity(const std::string& name,long int entity_address, long int attribute_address, long int data_address, long int next_entity_address){
        for (int i = 0; i < MAX_LENGTH_NAME_ENTTITY_; i++)
            name_[i] = name[i];      
        entity_address_ = entity_address;
        attribute_address_ = attribute_address;
        data_address_ = data_address;
        next_entity_address_  = next_entity_address;   
    }

    Entity::~Entity(){}

    void Entity::SetName(const std::string& name){ 
        for (int i = 0; i < MAX_LENGTH_NAME_ENTTITY_; i++)
            name_[i] = name[i];      
    }
    
    void Entity::SetEntityAddress(long int entity_address) { entity_address_ = entity_address; }
    void Entity::SetAttributeAddress(long int attribute_address) { attribute_address_ = attribute_address; }
    void Entity::SetDataAddress(long int data_address) { data_address_ = data_address; }
    void Entity::SetNextEntityAddress(long int next_entity_address) { next_entity_address_  = next_entity_address; }
                  
    char* Entity::GetName() {  return name_; }
    long int Entity::GetEntityAddress() { return entity_address_; }
    long int Entity::GetAttributeAddress() { return attribute_address_; }
    long int Entity::GetDataAddress() { return data_address_; }
    long int Entity::GetNextEntityAddress() { return next_entity_address_; }

}  // end namespace dictionary
