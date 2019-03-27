#include "attribute.h"

namespace dictionary {


    Attribute::Attribute(){
        data_type_ = '\0'; 
        length_data_type_= 0; 
        attribute_address_ = NULL_ATTRIBUTE_;
        type_index_ = 0; 
        index_address_ = NULL_ATTRIBUTE_;
        next_attribute_address_ = NULL_ATTRIBUTE_;
    }
    
    Attribute::Attribute(const std::string& name){
        for (int i = 0; i < MAX_LENGTH_NAME_ATTRIBUTE_; i++)
            name_[i] = name[i];      
        
        data_type_ = '\0'; 
        length_data_type_= 0; 
        attribute_address_ = NULL_ATTRIBUTE_;
        type_index_ = 0; 
        index_address_ = NULL_ATTRIBUTE_;
        next_attribute_address_ = NULL_ATTRIBUTE_;
        
    }

    Attribute::Attribute(const std::string& name, char data_type, int length_data_type, int type_index){
        
        for (int i = 0; i < MAX_LENGTH_NAME_ATTRIBUTE_; i++)
            name_[i] = name[i];      

        data_type_ = data_type;
        length_data_type_ = length_data_type;
        attribute_address_ = NULL_ATTRIBUTE_;
        type_index_ = type_index; 
        index_address_ = NULL_ATTRIBUTE_;
        next_attribute_address_ = NULL_ATTRIBUTE_;
        
    }

    Attribute::~Attribute(){}

    void Attribute::SetName(const std::string& name){ 
        for (int i = 0; i < MAX_LENGTH_NAME_ATTRIBUTE_; i++)
            name_[i] = name[i];      
    }
    
    void Attribute::SetDataType(char data_type) { data_type_ = data_type; }
    void Attribute::SetLengthDataType(int length_data_type) { length_data_type_= length_data_type; }
    void Attribute::SetAttributeAddress(long int attribute_address) { attribute_address_ = attribute_address; }
    void Attribute::SetTypeIndex(int type_index){ type_index_ = type_index; }
    void Attribute::SetIndexAddress(long int index_address){ index_address_ = index_address; }
    void Attribute::SetNextAttributeAddress(long int next_attribute_address){ next_attribute_address_  = next_attribute_address;}
                  
    char* Attribute::GetName() { return name_; }
    char Attribute::GetDataType() { return data_type_; }
    int Attribute::GetLengthDataType() { return length_data_type_; }
    long int Attribute::GetAttributeAddress() { return attribute_address_; }
    int Attribute::GetTypeIndex() { return type_index_; }
    long int Attribute::GetIndexAddress() { return index_address_; }
    long int Attribute::GetNextAttributeAddress() { return next_attribute_address_; }


}  // end namespace dictionary
