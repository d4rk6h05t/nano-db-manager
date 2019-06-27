#include "secondary_index.h"

namespace dictionary {

    // Constructors & destructosr
    SecondaryIndex::SecondaryIndex(){ 
        dir_ = "tmp/";
        name_ = "unamed"; 
        ext_ = ".idx";
        file_header_ = -1;
    
    }

    SecondaryIndex::SecondaryIndex(const std::string& name){ 
        dir_ = "tmp/";
        name_ = name; 
        ext_ = ".idx";
        file_header_ = -1;
        
    }

    SecondaryIndex::~SecondaryIndex(){}
    
    // Setters
    void SecondaryIndex::SetName(const std::string& name){ name_ = name; }
    void SecondaryIndex::SetDir(const std::string& dir){ dir_ = dir; }
    void SecondaryIndex::SetExt(const std::string& ext){ ext_ = ext; }
    
    void SecondaryIndex::SetFileHeader(long int file_header){ file_header_ = file_header; }
    
    // Getters
    std::string SecondaryIndex::GetName(){ return name_;}
    std::string SecondaryIndex::GetDir(){ return dir_;}
    std::string SecondaryIndex::GetExt(){ return ext_;}

    long int SecondaryIndex::GetFileHeader(){return file_header_;}
    
    long int SecondaryIndex::GetFileSize(){
        std::ifstream file ( dir_ + name_ + ext_, std::ios::binary | std::ios::in );
        file.exceptions( file.failbit | file.badbit );
            try { 
                file.seekg(0, std::ios::end);
                file_size_ = file.tellg();
            } catch (const std::ios_base::failure & e) {
                std::cout << std::endl << ":: Warning Exception: " << e.what() 
                          << std::endl << ":: Error code: " << e.code() 
                          << std::endl;
            }
        file.close();
        return file_size_;
    }

    // Methods of file 
   void SecondaryIndex::CreateFile(){
        std::ifstream in_file( dir_ + name_ + ext_, std::ios::binary | std::ios::in );
        if ( !in_file.good() ){
            std::ofstream out_file( dir_ + name_ + ext_, std::ios::binary | std::ios::out );
            out_file.close();
        } else {
            in_file.close();
        }
   }

   void SecondaryIndex::UpdateHeader(){
        std::fstream file( dir_ + name_ + ext_, std::ios::binary | std::ios::in | std::ios::out | std::ios::ate );
        file.exceptions( file.failbit | file.badbit );
            try {
                file.seekp(0);
                file.write( reinterpret_cast<const char*>(&file_header_), sizeof(long int) );
                 
            } catch (const std::ios_base::failure & e) {
                std::cout << std::endl << ":: Warning Exception: " << e.what() 
                          << std::endl << ":: Error code: " << e.code() 
                          << std::endl;
                if ( file.fail() ){
                    std::cout << " Error writing to file " << std::endl;
                    file.clear();
                }
            }
        file.close();
    }
    
    long int SecondaryIndex::ReadAddress(long int position){
        long int data;
        std::fstream file( dir_ + name_ + ext_, std::ios::binary | std::ios::in | std::ios::out );
        file.exceptions( file.failbit | file.badbit );
            try {
                file.seekp( position  );
                file.read( reinterpret_cast<char*>(&data) , sizeof(long int) );
            } catch (const std::ios_base::failure & e) {
                std::cout << std::endl << ":: Warning Exception: " << e.what() 
                          << std::endl << ":: Error code: " << e.code() 
                          << std::endl;

            }
        file.close();
        return data;
    }

    void SecondaryIndex::UpdateAddress(long int position, long int new_address){
        
        std::fstream file( dir_ + name_ + ext_, std::ios::binary | std::ios::in | std::ios::out | std::ios::ate );
        file.exceptions( file.failbit | file.badbit );
            try {
                file.seekp( position  );
                file.write( reinterpret_cast<const char*>(&new_address), sizeof(long int) );
            } catch (const std::ios_base::failure & e) {
                std::cout << std::endl << ":: Warning Exception: " << e.what() 
                          << std::endl << ":: Error code: " << e.code() 
                          << std::endl;
                if ( file.fail() ){
                    std::cout << " Error writing to file " << std::endl;
                    file.clear();
                }
            }
        file.close();
    }

    void SecondaryIndex::CreateBlock(int position){
        
        int x = -1;
        long int y = -1;
        long int overflow_chain = -1;

        std::fstream file( dir_ + name_ + ext_, std::ios::binary | std::ios::in | std::ios::out | std::ios::ate );
        file.exceptions( file.failbit | file.badbit );
            try {
                file.seekp( position );
                for ( int i = 0; i < ROW_CAPACITY_I_; i++ ) { 
                    file.write( reinterpret_cast<const char*>(&x), sizeof(int) );
                    for ( int j = 0; j < SIZE_DATA_BLOCK_; j++ )
                       file.write( reinterpret_cast<const char*>(&y), sizeof(long int) );
                }
                // overflow chain
                file.write( reinterpret_cast<const char*>(&overflow_chain), sizeof(long int) );
            } catch (const std::ios_base::failure & e) {
                std::cout << std::endl << ":: Warning Exception: " << e.what() 
                          << std::endl << ":: Error code: " << e.code() 
                          << std::endl;
                if ( file.fail() ){
                    std::cout << " Error writing to file " << std::endl;
                    file.clear();
                }
            }
        file.close();
    }

    std::list< std::pair< int, std::vector<long int>>> SecondaryIndex::ReadBlock(const std::string& name,int position){
        
        std::list< std::pair< int, std::vector<long int>> > block;
        
        std::string dir = "tmp/";
        std::string ext = ".idx";

        std::fstream file( dir + name + ext, std::ios::binary | std::ios::in | std::ios::out | std::ios::ate );
        file.exceptions( file.failbit | file.badbit );
            try {
                file.seekp( position );
                for ( int i = 0; i < ROW_CAPACITY_I_; i++ ) { 
                    int data = -1;
                    std::vector<long int> datablock;
                    file.read( reinterpret_cast<char*>(&data) , sizeof(int) );
                    if ( data != -1 ) {
                        for ( int j = 0; j < SIZE_DATA_BLOCK_; j++ ){
                            long int data_address = -1;
                            file.read( reinterpret_cast<char*>(&data_address), sizeof(long int) );
                            datablock.push_back(data_address);
                        }
                        std::pair< int, std::vector<long int>> data_pair;
                        data_pair.first = data;
                        data_pair.second = datablock;
                        block.push_back(data_pair);    
                    } else {
                        break;
                    }
                    
                }
            } catch (const std::ios_base::failure & e) {
                std::cout << std::endl << ":: Warning Exception: " << e.what() 
                          << std::endl << ":: Error code: " << e.code() 
                          << std::endl;
                if ( file.fail() ){
                    std::cout << " Error writing to file " << std::endl;
                    file.clear();
                }
            }
        file.close();
        return block;
    }

    void SecondaryIndex::AddLineToBlock(const std::string& name,int position, std::list< std::pair<int, std::vector<long int>>> list_data_pair, int data, std::vector<long int> block_address){
        
        std::pair<int, std::vector<long int>> new_pair;
        new_pair.first = data;
        new_pair.second = block_address;
        list_data_pair.push_back(new_pair);
        
        std::string dir = "tmp/";
        std::string ext = ".idx";
        std::fstream file( dir + name + ext, std::ios::binary | std::ios::in | std::ios::out | std::ios::ate );  
        
        std::list<std::pair<int, std::vector<long int>>>::iterator i_ = list_data_pair.begin();
        std::pair<int, std::vector<long int>> current_pair, next_pair, previus_pair;

        file.exceptions( file.failbit | file.badbit );
            try {
                
                file.seekp( position );
                
                if ( list_data_pair.size() == 1 ) {

                    file.write( reinterpret_cast<const char*>(&data), sizeof(int) );
                    file.write( reinterpret_cast<const char*>(&block_address[0]), sizeof(long int) );
                    file.write( reinterpret_cast<const char*>(&block_address[1]), sizeof(long int) );
                    file.write( reinterpret_cast<const char*>(&block_address[2]), sizeof(long int) );
                    file.write( reinterpret_cast<const char*>(&block_address[3]), sizeof(long int) );
                    file.write( reinterpret_cast<const char*>(&block_address[4]), sizeof(long int) );
                    file.close();

                } else if ( list_data_pair.size() == 2 ) {

                    current_pair.first = i_->first;
                    current_pair.second = i_->second;
                    i_++;
                    next_pair.first = i_->first;
                    next_pair.second = i_->second;
                    
                    if ( current_pair.first < next_pair.first ) {
                        // curent first    
                        
                        file.write( reinterpret_cast<const char*>(&current_pair.first), sizeof(int) );
                        for ( int j = 0; j < SIZE_DATA_BLOCK_; j++ ){
                            long int data_addr_j = current_pair.second[j];
                            file.write( reinterpret_cast<const char*>(&data_addr_j), sizeof(long int) );
                        }
                    
                        file.write( reinterpret_cast<const char*>(&next_pair.first), sizeof(int) );
                        for ( int k = 0; k < SIZE_DATA_BLOCK_; k++ ){
                            long int data_addr_k = next_pair.second[k];
                            file.write( reinterpret_cast<const char*>(&data_addr_k), sizeof(long int) );
                        }
                    } else {
                        // current last
                        
                        file.write( reinterpret_cast<const char*>(&next_pair.first), sizeof(int) );
                        for ( int l = 0; l < SIZE_DATA_BLOCK_; l++ ){
                            long int data_addr_l = next_pair.second[l];
                            file.write( reinterpret_cast<const char*>(&data_addr_l), sizeof(long int) );
                        }
                        
                        file.write( reinterpret_cast<const char*>(&current_pair.first), sizeof(int) );
                        for ( int m = 0; m < SIZE_DATA_BLOCK_; m++ ){
                            long int data_addr_m = current_pair.second[m];
                            file.write( reinterpret_cast<const char*>(&data_addr_m), sizeof(long int) );
                        }
                    }
                    file.close();
                } else if ( list_data_pair.size() > 2 ) {

                    list_data_pair.sort([](const std::pair<int, std::vector<long int>> & a, const std::pair<int, std::vector<long int>> & b) { return a.first < b.first; });
                    i_ = list_data_pair.begin();
                    std::list<std::pair<int, std::vector<long int>>>::iterator prev = std::prev( i_ , 1 );
                    std::list<std::pair<int, std::vector<long int>>>::iterator next = std::next( i_ , 1 );
                    
                    while ( i_ != list_data_pair.end() ) {

                        if ( data == i_->first ){

                            current_pair.first = i_->first;
                            current_pair.second = i_->second;

                            if ( i_ != list_data_pair.begin() ){
                                previus_pair.first = prev->first;
                                previus_pair.second = prev->second;
                            } else {
                                previus_pair.first = -1;
                                previus_pair.second = {-1,-1,-1,-1,-1};
                            }

                            if ( next != list_data_pair.end() ){
                                next_pair.first = next->first;
                                next_pair.second = next->second;  
                            } else {
                                next_pair.first = -1;
                                next_pair.second = {-1,-1,-1,-1,-1}; 
                            }    
                            break;
                        } // end if data == i->first

                        i_++;
                        next++;
                        prev++;
                    } // emd while i_ != list_data_pair
                    i_ = list_data_pair.begin();
                    int x = 0;
                        while ( i_ != list_data_pair.end() && x < ROW_CAPACITY_I_) {
                            current_pair.first = i_->first;
                            current_pair.second = i_->second;                            
                            file.write( reinterpret_cast<const char*>(&current_pair.first), sizeof(int) );
                            for ( int n = 0; n < SIZE_DATA_BLOCK_; n++ ){
                                long int data_addr_n = current_pair.second[n];
                                file.write( reinterpret_cast<const char*>(&data_addr_n), sizeof(long int) );
                            }
                            i_++;
                            x++;
                        }    
                        file.close();
                } // end else if list_data_pair.size() > 2
            } catch (const std::ios_base::failure & e) {
                std::cout << std::endl << ":: Warning Exception: " << e.what() 
                          << std::endl << ":: Error code: " << e.code() 
                          << std::endl;
            }
        //file.close();  
    }

    void SecondaryIndex::UpdateLineToBlock(const std::string& name,int position, int data, std::vector<long int> block_address){
        
        if ( block_address.size() < SIZE_DATA_BLOCK_ ){
            for (int i = block_address.size(); i < SIZE_DATA_BLOCK_; i++){
                block_address.push_back(-1);
            }
        }

        std::string dir = "tmp/";
        std::string ext = ".idx";
        std::fstream file( dir + name + ext, std::ios::binary | std::ios::in | std::ios::out | std::ios::ate );  

        file.exceptions( file.failbit | file.badbit );
            try {
                
                file.seekp( position );
                
                file.write( reinterpret_cast<const char*>(&data), sizeof(int) );
                file.write( reinterpret_cast<const char*>(&block_address[0]), sizeof(long int) );
                file.write( reinterpret_cast<const char*>(&block_address[1]), sizeof(long int) );
                file.write( reinterpret_cast<const char*>(&block_address[2]), sizeof(long int) );
                file.write( reinterpret_cast<const char*>(&block_address[3]), sizeof(long int) );
                file.write( reinterpret_cast<const char*>(&block_address[4]), sizeof(long int) );
                    
            } catch (const std::ios_base::failure & e) {
                std::cout << std::endl << ":: Warning Exception: " << e.what() 
                          << std::endl << ":: Error code: " << e.code() 
                          << std::endl;
            }
        file.close();  
    }

    void SecondaryIndex::RemoveItem(const std::string& name,int position, int key, long int key_address, std::list< std::pair< int, std::vector<long int>>> bucket){
        std::string dir = "tmp/";
        std::string ext = ".idx";
        int current_position = 0;
        long int data_null = -1;
        std::fstream file( dir + name + ext, std::ios::binary | std::ios::in | std::ios::out | std::ios::ate );
        file.exceptions( file.failbit | file.badbit );
            try {
                file.seekp( position );
                std::list< std::pair< int, std::vector<long int>>>::iterator i_ = bucket.begin();
                while ( i_ != bucket.end() ) { 
                    file.write( reinterpret_cast<const char*>(&(i_->first)), sizeof(int) );
                    std::vector<long int> datablock = i_->second;
                    std::vector<long int>::iterator j_ =  datablock.begin();
                    int count_save = 0;
                    while ( j_ != datablock.end() ){
                        if ( key != i_->first &&  key_address !=  *j_ ){
                            file.write( reinterpret_cast<const char*>(&(*j_)), sizeof(long int) );
                           
                        } else if ( key == i_->first &&  key_address !=  *j_ ) {
                            file.write( reinterpret_cast<const char*>(&(*j_)), sizeof(long int) );
                            count_save = count_save + 1;
                            if ( count_save == SIZE_DATA_BLOCK_ - 1 )   {
                                file.write( reinterpret_cast<const char*>(&data_null), sizeof(long int) );       
                            }
                        }
                    j_++;  
                    }
                i_++;
                }
                // overflow chain
                file.write( reinterpret_cast<const char*>(&data_null), sizeof(long int) );
            } catch (const std::ios_base::failure & e) {
                std::cout << std::endl << ":: Warning Exception: " << e.what() 
                          << std::endl << ":: Error code: " << e.code() 
                          << std::endl;
                if ( file.fail() ){
                    std::cout << " Error writing to file " << std::endl;
                    file.clear();
                }
            }
        file.close();
    }

    void SecondaryIndex::RemoveLine(const std::string& name,int position, int key, long int key_address, std::list< std::pair< int, std::vector<long int>>> bucket){
        std::string dir = "tmp/";
        std::string ext = ".idx";
        int current_position = 0;
        long int data_null = -1;
        std::fstream file( dir + name + ext, std::ios::binary | std::ios::in | std::ios::out | std::ios::ate );
        file.exceptions( file.failbit | file.badbit );
            try {
                file.seekp( position );
                std::list< std::pair< int, std::vector<long int>>>::iterator i_ = bucket.begin();
                while ( i_ != bucket.end() ) { 
                    if ( key != i_->first ){
                        file.write( reinterpret_cast<const char*>(&(i_->first)), sizeof(int) );
                        std::vector<long int> datablock = i_->second;
                        std::vector<long int>::iterator j_ =  datablock.begin();
                        while ( j_ != datablock.end() ){
                                file.write( reinterpret_cast<const char*>(&(*j_)), sizeof(long int) );
                        j_++;  
                        }
                    }
                i_++;
                }
                // overflow chain
                file.write( reinterpret_cast<const char*>(&data_null), sizeof(long int) );
            } catch (const std::ios_base::failure & e) {
                std::cout << std::endl << ":: Warning Exception: " << e.what() 
                          << std::endl << ":: Error code: " << e.code() 
                          << std::endl;
                if ( file.fail() ){
                    std::cout << " Error writing to file " << std::endl;
                    file.clear();
                }
            }
        file.close();
    }

    std::vector<long int> SecondaryIndex::GetCollectionAddress(const std::string& name,int position, int key){

        std::vector<long int> datablock;
        std::string dir = "tmp/";
        std::string ext = ".idx";

        std::fstream file( dir + name + ext, std::ios::binary | std::ios::in | std::ios::out | std::ios::ate );
        file.exceptions( file.failbit | file.badbit );
            try {
                file.seekp( position );
                for ( int i = 0; i < ROW_CAPACITY_I_; i++ ) { 
                    int data = -1;
                    
                    file.read( reinterpret_cast<char*>(&data) , sizeof(int) );

                    if ( data != -1 ) {
                        if (  key == data ) {
                            for ( int j = 0; j < SIZE_DATA_BLOCK_; j++ ){
                                long int data_address = -1;
                                file.read( reinterpret_cast<char*>(&data_address), sizeof(long int) );
                                datablock.push_back(data_address);
                            }
                            break;
                        } else {
                             for ( int j = 0; j < SIZE_DATA_BLOCK_; j++ ){
                                long int data_address_x = -1;
                                file.read( reinterpret_cast<char*>(&data_address_x), sizeof(long int) );
                            }  
                        }    

                    } else {
                        break;
                    }
                    
                }
            } catch (const std::ios_base::failure & e) {
                std::cout << std::endl << ":: Warning Exception: " << e.what() 
                          << std::endl << ":: Error code: " << e.code() 
                          << std::endl;
                if ( file.fail() ){
                    std::cout << " Error writing to file " << std::endl;
                    file.clear();
                }
            }
        file.close();
        return datablock;
    }

}  // end namespace dictionary