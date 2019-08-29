#ifndef REPOSITORY_CC_SCHEMA_H_
#define REPOSITORY_CC_SCHEMA_H_

#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <iterator>

#include "file.h"
#include "entity.h"
#include "attribute.h"
#include "data_dictionary.h"
#include "data_file.h"
#include "primary_index.h"
#include "secondary_index.h"
#include "static_hashing.h"
#include "multilist.h"

namespace repository {

    class Schema : public File {
    
        public:
             
            // Constructor & destructors
            Schema(){}
            ~Schema(){}
            
    }; 

}  // end namespacerepository

#endif  // REPOSITORY_CC_SCHEMA_H_