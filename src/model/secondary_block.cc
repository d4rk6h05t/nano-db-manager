
#include "secondary_block.h"

namespace dictionary {


    SecondaryBlock::SecondaryBlock(){
        for ( int i = 0; i < SIZE_DATA_BLOCK_; i++){
            data_block_int_[i] = -1;
            data_block_str_[i] = "";
        }
        next_block_address_ = -1;            
    }

    SecondaryBlock::~SecondaryBlock(){}
    
    void SecondaryBlock::SetDataBlockInt(std::vector<int> data_block_int){
        data_block_int_ = data_block_int;
    }

    void SecondaryBlock::SetDataBlockStr(std::vector<std::string> data_block_str){
        data_block_str_ = data_block_str;
    }

    void SecondaryBlock::SetNextAddress(long int next_block_address){
        next_block_address_ = next_block_address;
    }
            
    void SecondaryBlock::AddItemDataBlockInt(int new_item){
        data_block_int_.push_back(new_item);
    }

    void SecondaryBlock::AddItemDataBlockStr(std::string new_item){
        data_block_str_.push_back(new_item);
    }
                  
    std::vector<int> SecondaryBlock::GetDataBlockInt(){
        return data_block_int_;
    }

    std::vector<std::string> SecondaryBlock::GetDataBlockStr(){
        return data_block_str_;
    }

    long int SecondaryBlock::GetNextAddress(){
        return next_block_address_;
    }

    int SecondaryBlock::GetItemDataBlockInt(int index){
        return data_block_int_[index];
    }
    
    std::string SecondaryBlock::GetItemDataBlockStr(int index){
        return data_block_str_[index];
    } 
   
}  // end namespace dictionary