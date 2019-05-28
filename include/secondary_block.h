#ifndef DICTIONARY_CC_SECONDARY_BLOCK_H_
#define DICTIONARY_CC_SECONDARY_BLOCK_H_

#include <iostream>
#include <string>
#include <vector>

const int SIZE_DATA_BLOCK_ = 4;

namespace dictionary {

    class SecondaryBlock {
    
        public:
             
            SecondaryBlock();
            ~SecondaryBlock();

            void SetDataBlockInt(std::vector<int> data_block_int); 
            void SetDataBlockStr(std::vector<std::string> data_block_str);
            void SetNextAddress(long int next_block_address);
            
            void AddItemDataBlockInt(int new_item);
            void AddItemDataBlockStr(std::string new_item);
                  
            std::vector<int> GetDataBlockInt();
            std::vector<std::string> GetDataBlockStr();
            long int GetNextAddress();

            int GetItemDataBlockInt(int index);
            std::string GetItemDataBlockStr(int index);

        private:

            std::vector<int> data_block_int_;
            std::vector<std::string> data_block_str_;
            long int next_block_address_;
    }; 

}  // end namespace dictionary

#endif  // DICTIONARY_CC_SECONDARY_BLOCK_H_