#ifndef DICTIONARY_CC_INDEX_H_
#define DICTIONARY_CC_INDEX_H_

#include <iostream>
#include <string>

namespace dictionary {

    class Index {
    
        public:
             
            Index();
            Index(int type_index);
            ~Index();

        private:

            // 0: Without Type Index
            // 1: Search Key
            // 2: Primary Index
            // 3: Secondary Index
            int type_index_; 
            long int index_address_;
    }; 

}  // end namespace dictionary

#endif  // DICTIONARY_CC_INDEX_H_