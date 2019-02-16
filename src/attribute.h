#ifndef DICTIONARY_CC_ATTRIBUTE_H_
#define DICTIONARY_CC_ATTRIBUTE_H_

const int MAX_LENGTH_STR = 35;

namespace dictionary {
    
    class Attribute {

        public:
             
            Attribute();
            Attribute(char* name);
            ~Attribute();

            void SetName(char* name); 
            void SetAttributeAddress(int Attribute_address); 
            void SetAttributeAddress(int attribute_address); 
            void SetDataAddress(int data_address); 
            void SetNextAttributeAddress(int next_Attribute_address);
                  
            char* GetName(); 
            int GetAttributeAddress(); 
            int GetAttributeAddress();
            int GetDataAddress();
            int GetNextAttributeAddress();

        private:
            char name_[MAX_LENGTH_STR];
            char data_type_;
            int length_data_type_;
            int
    };


}  // end namespace dictionary

#endif  // DICTIONARY_CC_ATTRIBUTE_H_

