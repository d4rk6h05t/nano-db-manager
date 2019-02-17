#ifndef DICTIONARY_CC_ATTRIBUTE_H_
#define DICTIONARY_CC_ATTRIBUTE_H_

#include <cstddef>

const int MAX_LENGTH_NAME_ATTRIBUTE_ = 35;


namespace dictionary {

    class Attribute {
    
        public:
             
            Attribute();
            Attribute(char* name);
            Attribute(char* name, char data_type, int length_data_type, int* attribute_address,
                int type_index,int* index_address, int* next_attribute_address);
            ~Attribute();

            void SetName(char* name); 
            void SetDataType(char data_type); 
            void SetLengthDataType(char data_type); 
            void SetAttributeAddress(int* attribute_address);
            void SetTypeIndex(int type_index);
            void SetIndexAddress(int* index_address); 
            void SetNextAttributeAddress(int* next_attribute_address);
                  
            char* GetName(); 
            char GetDataType();
            int GetLengthDataType();
            int* GetAttributeAddress(); 
            int GetTypeIndex();
            int* GetIndexAddress();
            int* GetNextAttributeAddress();

        private:
            char name_[MAX_LENGTH_NAME_ATTRIBUTE_];

            // I: Integer or C: char
            char data_type_; 
            
            int length_data_type_; 
            int* attribute_address_;
            
            // 0: Without Type Index
            // 1: Search Key
            // 2: Primary Index
            // 3: Secondary Index
            int type_index_; 

            int* index_address_;
            int* next_attribute_address_;

    };


}  // end namespace dictionary

#endif  // DICTIONARY_CC_ATTRIBUTE_H_

