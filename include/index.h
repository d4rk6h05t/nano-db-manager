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


            // Setters
            void SetType(int type);
            void SetAddress(long int address); 
            // Getters
            int GetType();
            long int GetAddress();

        protected:
            // 0: Without Type Index
            // 1: Primary Index
            // 2: Secondary Index
            // 3: Search Key
            // 4: TreeB+
            // 5: Hash Static
            // 6: Hash Dinamic
            // 7: Multilist
            int type_; 
            long int address_;

    };

    class SearchKey : public Index {
    
        public:
            SearchKey();
            ~SearchKey();

    };

    class PrimaryIndex : public Index {
    
        public:
            PrimaryIndex();
            ~PrimaryIndex();

    };

    class SecondaryIndex : public Index {
    
        public:
            SecondaryIndex();
            ~SecondaryIndex();

    }; 

}  // end namespace dictionary

#endif  // DICTIONARY_CC_INDEX_H_