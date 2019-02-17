
#include "attribute.h"

namespace dictionary {


    Attribute::Attribute(){
        data_type_ = '\0'; 
        length_data_type_= 0; 
        attribute_address_ = NULL;
        type_index_ = 0; 
        index_address_ = NULL;
        next_attribute_address_ = NULL;
    }
    
    Attribute::Attribute(char* name){
        for (int i = 0; i < MAX_LENGTH_NAME_ATTRIBUTE_; i++){
            name_[i] = name[i];      
        }
        data_type_ = '\0'; 
        length_data_type_= 0; 
        attribute_address_ = NULL;
        type_index_ = 0; 
        index_address_ = NULL;
        next_attribute_address_ = NULL;
        
    }

    Attribute::Attribute(char* name, char data_type, int length_data_type, int* attribute_address,
            int type_index,int* index_address, int* next_attribute_address){
        
        for (int i = 0; i < MAX_LENGTH_NAME_ATTRIBUTE_; i++){
            name_[i] = name[i];      
        }

        data_type_ = data_type;
        
        if (data_type_ == 'C') 
            length_data_type_= sizeof(char);
        else if (data_type_ == 'I')
            length_data_type_= sizeof(int);
        else
            length_data_type_ = 0;

        attribute_address_ = attribute_address;
        type_index_ = type_index; 
        index_address_ = index_address;
        next_attribute_address_ = next_attribute_address;
        
    }

    Attribute::~Attribute(){}

    void Attribute::SetName(char* name){ 
        for (int i = 0; i < MAX_LENGTH_NAME_ATTRIBUTE_; i++){
            name_[i] = name[i];      
        }
    }
    
    void Attribute::SetDataType(char data_type) { data_type_ = data_type; }
    
    void Attribute::SetLengthDataType(char data_type) { 
        if (data_type_ == 'C') 
            length_data_type_= sizeof(char);
        else if (data_type_ == 'I')
            length_data_type_= sizeof(int);
        else
            length_data_type_ = 0;
    }
    
    void Attribute::SetAttributeAddress(int* attribute_address) { attribute_address_ = attribute_address; }
    void Attribute::SetTypeIndex(int type_index){ type_index_ = type_index; }
    void Attribute::SetIndexAddress(int* index_address){ index_address_ = index_address; }
    void Attribute::SetNextAttributeAddress(int* next_attribute_address){ next_attribute_address_  = next_attribute_address;}
                  
    char* Attribute::GetName() { return name_; }
    char Attribute::GetDataType() { return data_type_; }
    int Attribute::GetLengthDataType() { return length_data_type_; }
    int* Attribute::GetAttributeAddress() { return attribute_address_; }
    int Attribute::GetTypeIndex() { return type_index_; }
    int* Attribute::GetIndexAddress() { return index_address_; }
    int* Attribute::GetNextAttributeAddress() { return next_attribute_address_; }


}  // end namespace dictionary
