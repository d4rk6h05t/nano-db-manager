#include "index.h"

namespace dictionary {

    Index::Index(int type) : type_( type ){ }
    Index::~Index(){}

    void Index::SetType(int type){ type_ = type; }
    void Index::SetAddress(long int address){ address_; } 
    int Index::GetType(){ return type_; }
    long int Index::GetAddress(){ return address_; }

    SearchKey::SearchKey() : Index(3){ }
    SearchKey::~SearchKey(){}

    PrimaryIndex::PrimaryIndex() : Index(1){ std::cout << std::endl << ":: Start PrimaryIndex :: "; }
    PrimaryIndex::~PrimaryIndex(){}

    SecondaryIndex::SecondaryIndex() : Index(2){ }
    SecondaryIndex::~SecondaryIndex(){}

}  // end namespace dictionary