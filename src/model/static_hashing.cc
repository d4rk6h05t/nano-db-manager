#include "static_hashing.h"

namespace repository {

    // Methods of file 
   void StaticHashing::InitAddressBucket(){
        long int data_null = -1;
        std::fstream file( dir_ + name_ + ext_, std::ios::binary | std::ios::in | std::ios::out );
        file.exceptions( file.failbit | file.badbit );
            try {
                for (int i = 0; i < NO_BUCKETS_SH_; i++)
                    file.write( reinterpret_cast<const char*>(&data_null), sizeof(long int) );
             } catch (const std::ios_base::failure & e) {
                std::cout << std::endl << ":: Warning Exception: " << e.what() 
                          << std::endl << ":: Error code: " << e.code() 
                          << std::endl;

            }
        file.close();
   }

   long int StaticHashing::GetFileSizeSH(const std::string& name){
        long int file_size = 0;
        std::string dir = "tmp/";
        std::string ext = ".idx";
        std::ifstream file ( dir + name + ext, std::ios::binary | std::ios::in );
        file.exceptions( file.failbit | file.badbit );
            try { 
                file.seekg(0, std::ios::end);
                file_size = file.tellg();
            } catch (const std::ios_base::failure & e) {
                std::cout << std::endl << ":: Warning Exception: " << e.what() 
                          << std::endl << ":: Error code: " << e.code() 
                          << std::endl;
            }
        file.close();
        return file_size;
    }
    
    int StaticHashing::ReadInt(const std::string& name,long int position){
        int data;
        std::string dir = "tmp/";
        std::string ext = ".idx";
        std::fstream file( dir + name + ext, std::ios::binary | std::ios::in | std::ios::out );
        file.exceptions( file.failbit | file.badbit );
            try {
                file.seekp( position  );
                file.read( reinterpret_cast<char*>(&data) , sizeof(int) );
            } catch (const std::ios_base::failure & e) {
                std::cout << std::endl << ":: Warning Exception: " << e.what() 
                          << std::endl << ":: Error code: " << e.code() 
                          << std::endl;

            }
        file.close();
        return data;
    }

    long int StaticHashing::ReadAddress(const std::string& name,long int position){
        long int data;
        std::string dir = "tmp/";
        std::string ext = ".idx";
        std::fstream file( dir + name + ext, std::ios::binary | std::ios::in | std::ios::out );
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

    void StaticHashing::UpdateInt(const std::string& name,long int position, int new_address){
        std::string dir = "tmp/";
        std::string ext = ".idx";
        std::fstream file( dir + name + ext, std::ios::binary | std::ios::in | std::ios::out | std::ios::ate );
        file.exceptions( file.failbit | file.badbit );
            try {
                file.seekp( position  );
                file.write( reinterpret_cast<const char*>(&new_address), sizeof(int) );
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

    void StaticHashing::UpdateAddress(const std::string& name,long int position, long int new_address){
        std::string dir = "tmp/";
        std::string ext = ".idx";
        std::fstream file( dir + name + ext, std::ios::binary | std::ios::in | std::ios::out | std::ios::ate );
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

    std::vector<long int> StaticHashing::GetBucketsAddress(const std::string& name){
        std::vector<long int> address;
        long int bucket_addr;
        std::string dir = "tmp/";
        std::string ext = ".idx";
        std::fstream file( dir + name + ext, std::ios::binary | std::ios::in | std::ios::out );
        file.exceptions( file.failbit | file.badbit );
            try {
                file.seekp( 0 );
                for ( int i = 0; i < NO_BUCKETS_SH_; i++ ){
                    file.read( reinterpret_cast<char*>(&bucket_addr) , sizeof(long int) );
                    address.push_back(bucket_addr);
                }
            } catch (const std::ios_base::failure & e) {
                std::cout << std::endl << ":: Warning Exception: " << e.what() 
                          << std::endl << ":: Error code: " << e.code() 
                          << std::endl;

            }
        file.close();
        return address;
    }   

    void StaticHashing::CreateBlock(const std::string& name,int position){
        
        int x = -1;
        long int y = -1;
        long int overflow_chain = -1;
         std::string dir = "tmp/";
        std::string ext = ".idx";

        std::fstream file( dir + name + ext, std::ios::binary | std::ios::in | std::ios::out | std::ios::ate );
        file.exceptions( file.failbit | file.badbit );
            try {
                file.seekp( position );
                for ( int i = 0; i < ROW_CAPACITY_SH_; i++ ) { 
                    file.write( reinterpret_cast<const char*>(&x), sizeof(int) );
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

    int StaticHashing::GetHash(int key){
       int hash;
       hash = key % NO_BUCKETS_SH_;
       return hash; 
    }

    std::list< std::pair< int, long int> > StaticHashing::ReadBlock(const std::string& name,int position){
        
        std::list< std::pair< int, long int> > block_data_int;
            
        int data;
        long int data_address;
        
        std::string dir = "tmp/";
        std::string ext = ".idx";

        std::fstream file( dir + name + ext, std::ios::binary | std::ios::in | std::ios::out | std::ios::ate );
        file.exceptions( file.failbit | file.badbit );
            try {
                file.seekp( position );
                for ( int i = 0; i < ROW_CAPACITY_SH_; i++ ) { 
                    file.read( reinterpret_cast<char*>(&data) , sizeof(int) );
                    file.read( reinterpret_cast<char*>(&data_address), sizeof(long int) );
                    if ( data != -1 && data_address != -1){
                        std::pair< int, long int> data_pair;
                        data_pair.first = data;
                        data_pair.second = data_address;
                        block_data_int.push_back(data_pair);
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
        return block_data_int;
    }

    void StaticHashing::AddLineToBlock(const std::string& name,int position, std::list< std::pair<int, long int>> list_data_pair, int data, long int data_address){
        
        std::pair<int, long int> new_pair;
        new_pair.first = data;
        new_pair.second = data_address;
        list_data_pair.push_back(new_pair);
        std::string dir = "tmp/";
        std::string ext = ".idx";
        std::fstream file( dir + name + ext, std::ios::binary | std::ios::in | std::ios::out | std::ios::ate );  
        
        std::list<std::pair<int, long int>>::iterator i_ = list_data_pair.begin();
        std::pair<int, long int> current_pair, next_pair, previus_pair;

        file.exceptions( file.failbit | file.badbit );
            try {
                
                file.seekp( position );
                
                if ( list_data_pair.size() == 1 ) {
                    
                    file.write( reinterpret_cast<const char*>(&data), sizeof(int) );
                    file.write( reinterpret_cast<const char*>(&data_address), sizeof(long int) );

                } else if ( list_data_pair.size() == 2 ) {

                    current_pair.first = i_->first;
                    current_pair.second = i_->second;
                    i_++;
                    next_pair.first = i_->first;
                    next_pair.second = i_->second;
                    
                    if ( current_pair.first < next_pair.first ) {
                        // curent first    
                        file.write( reinterpret_cast<const char*>(&current_pair.first), sizeof(int) );
                        file.write( reinterpret_cast<const char*>(&current_pair.second), sizeof(long int) );
                        file.write( reinterpret_cast<const char*>(&next_pair.first), sizeof(int) );
                        file.write( reinterpret_cast<const char*>(&next_pair.second), sizeof(long int) );
                    } else {
                        // current last
                        file.write( reinterpret_cast<const char*>(&next_pair.first), sizeof(int) );
                        file.write( reinterpret_cast<const char*>(&next_pair.second), sizeof(long int) );
                        file.write( reinterpret_cast<const char*>(&current_pair.first), sizeof(int) );
                        file.write( reinterpret_cast<const char*>(&current_pair.second), sizeof(long int) );
                       
                    }

                } else if ( list_data_pair.size() > 2 ) {

                    list_data_pair.sort([](const std::pair<int, long int> & a, const std::pair<int, long int> & b) { return a.first < b.first; });
                    i_ = list_data_pair.begin();
                    std::list<std::pair<int, long int>>::iterator prev = std::prev( i_ , 1 );
                    std::list<std::pair<int, long int>>::iterator next = std::next( i_ , 1 );
                    
                    while ( i_ != list_data_pair.end() ) {

                        if ( data == i_->first ){

                            current_pair.first = i_->first;
                            current_pair.second = i_->second;

                            if ( i_ != list_data_pair.begin() ){
                                previus_pair.first = prev->first;
                                previus_pair.second = prev->second;
                            } else {
                                previus_pair.first = -1;
                                previus_pair.second = -1;
                            }

                            if ( next != list_data_pair.end() ){
                                next_pair.first = next->first;
                                next_pair.second = next->second;  
                            } else {
                                next_pair.first = -1;
                                next_pair.second = -1; 
                            }    
                            break;
                        } // end if data == i->first

                        i_++;
                        next++;
                        prev++;
                    } // emd while i_ != list_data_pair
                    
                    i_ = list_data_pair.begin();
                    int k = 0;
                        while ( i_ != list_data_pair.end() && k < ROW_CAPACITY_SH_) {
                            current_pair.first = i_->first;
                            current_pair.second = i_->second;                            
                            file.write( reinterpret_cast<const char*>(&current_pair.first), sizeof(int) );
                            file.write( reinterpret_cast<const char*>(&current_pair.second), sizeof(long int) );
                            i_++;
                            k++;
                        }


                } // end else if list_data_pair.size() > 2
            } catch (const std::ios_base::failure & e) {
                std::cout << std::endl << ":: Warning Exception: " << e.what() 
                          << std::endl << ":: Error code: " << e.code() 
                          << std::endl;
            }
        file.close();  
    }

    long int StaticHashing::GetAddress(const std::string& name,long int bucket_address, int key ){
        int data_saved;
        long int data_address_saved;
        std::string dir = "tmp/";
        std::string ext = ".idx";
        std::fstream file( dir + name + ext, std::ios::binary | std::ios::in | std::ios::out | std::ios::ate );
        file.exceptions( file.failbit | file.badbit );
            try {
                file.seekp( bucket_address );
                for ( int i = 0; i < ROW_CAPACITY_SH_; i++ ) { 
                    file.read( reinterpret_cast<char*>(&data_saved) , sizeof(int) );
                    file.read( reinterpret_cast<char*>(&data_address_saved), sizeof(long int) );
                    if ( data_saved != -1 && data_address_saved != -1){
                        if( key == data_saved ){
                            break;       
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
        return data_address_saved;
    }

    long int StaticHashing::GetBucketAddress(const std::string& name, int hash){
        long int bucket_addr;
        int ptr_current_position = 0;
        std::string dir = "tmp/";
        std::string ext = ".idx";
        std::fstream file( dir + name + ext, std::ios::binary | std::ios::in | std::ios::out );
        file.exceptions( file.failbit | file.badbit );
            try {
                file.seekp( 0 );
                for ( int i = 0; i < NO_BUCKETS_SH_; i++ ){
                    if ( hash == i ){
                        file.read( reinterpret_cast<char*>(&bucket_addr) , sizeof(long int) );
                        ptr_current_position = ptr_current_position + sizeof(long int);
                    } else {
                        file.seekg( ptr_current_position + sizeof(long int) );
                        ptr_current_position = ptr_current_position + sizeof(long int);
                    }
                }
            } catch (const std::ios_base::failure & e) {
                std::cout << std::endl << ":: Warning Exception: " << e.what() 
                          << std::endl << ":: Error code: " << e.code() 
                          << std::endl;

            }
        file.close();
        return bucket_addr;
    }

    void StaticHashing::RemoveDataInt(const std::string& name, int position, int data, std::list< std::pair<int, long int>> list_data_pair){
        int x = -1;
        long int y = -1;
        std::string dir = "tmp/";
        std::string ext = ".idx";
        std::fstream file( dir + name + ext , std::ios::binary | std::ios::in | std::ios::out | std::ios::ate );
        file.exceptions( file.failbit | file.badbit );
            try {
                file.seekp( position );
                std::list<std::pair<int,long int>>::iterator i_ = list_data_pair.begin();
                while ( i_ != list_data_pair.end() ) { 
                    if ( i_->first != data ){
                        file.write( reinterpret_cast<const char*>(&(i_->first)), sizeof(int) );
                        file.write( reinterpret_cast<const char*>(&(i_->second)), sizeof(long int) );    
                    }
                    i_++;
                }
                file.write( reinterpret_cast<const char*>(&x), sizeof(int) );
                file.write( reinterpret_cast<const char*>(&y), sizeof(long int) );
            } catch (const std::ios_base::failure & e) {
                std::cout << std::endl << "-> :: Warning Exception: " << e.what() 
                          << std::endl << "-> :: Error code: " << e.code() 
                          << std::endl;
                if ( file.fail() ){
                    std::cout << "-> :: Error writing to file " << std::endl;
                    file.clear();
                }
            }
        file.close();
    }

}  // end namespace repository