#ifndef DICTIONARY_CC_ATTRIBUTE_H_
#define DICTIONARY_CC_ATTRIBUTE_H_

#include <iostream>
#include <string>

const int MAX_LENGTH_NAME_ATTRIBUTE_ = 35;
const int MAX_LENGTH_ATTRIBUTE_ = 68;
const long int NULL_ATTRIBUTE_ = -1;

namespace dictionary {

    class Attribute {
    
        public:
             
            Attribute();
            Attribute(const std::string& name);
            Attribute(const std::string& name, char data_type, int length_data_type,int type_index);
            ~Attribute();

            void SetName(const std::string& name); 
            void SetDataType(char data_type); 
            void SetLengthDataType(int length_data_type); 
            void SetAttributeAddress(long int attribute_address);
            void SetTypeIndex(int type_index);
            void SetIndexAddress(long int index_address); 
            void SetNextAttributeAddress(long int next_attribute_address);
                  
            char* GetName(); 
            char GetDataType();
            int GetLengthDataType();
            long int GetAttributeAddress(); 
            int GetTypeIndex();
            long int GetIndexAddress();
            long int GetNextAttributeAddress();

        private:
            char name_[MAX_LENGTH_NAME_ATTRIBUTE_];

            // I: Integer or C: char
            char data_type_; 
            
            int length_data_type_; 
            long int attribute_address_;
            
            // 0: Without Type Index
            // 1: Search Key
            // 2: Primary Index
            // 3: Secondary Index
            int type_index_; 

            long int index_address_;
            long int next_attribute_address_;
    };


}  // end namespace dictionary

#endif  // DICTIONARY_CC_ATTRIBUTE_H_

