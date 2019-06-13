#include "static_hashing_file.h"

namespace dictionary {

    // Constructors & destructosr
    StaticHashingFile::StaticHashingFile(){ 
        dir_ = "tmp/";
        name_ = "unamed"; 
        ext_ = ".idx";
        file_header_ = -1;
    }

    StaticHashingFile::StaticHashingFile(const std::string& name){ 
        dir_ = "tmp/";
        name_ = name; 
        ext_ = ".idx";
        file_header_ = -1;
    }

    StaticHashingFile::~StaticHashingFile(){}
    
    // Setters
    void StaticHashingFile::SetName(const std::string& name){ name_ = name; }
    void StaticHashingFile::SetDir(const std::string& dir){ dir_ = dir; }
    void StaticHashingFile::SetExt(const std::string& ext){ ext_ = ext; }
    void StaticHashingFile::SetFileHeader(long int file_header){ file_header_ = file_header; }
    
    // Getters
    std::string StaticHashingFile::GetName(){ return name_;}
    std::string StaticHashingFile::GetDir(){ return dir_;}
    std::string StaticHashingFile::GetExt(){ return ext_;}
    long int StaticHashingFile::GetFileHeader(){return file_header_;}
    
    long int StaticHashingFile::GetFileSize(){
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
   void StaticHashingFile::CreateFile(){
        std::ifstream in_file( dir_ + name_ + ext_, std::ios::binary | std::ios::in );
        if ( !in_file.good() ){
            std::ofstream out_file( dir_ + name_ + ext_, std::ios::binary | std::ios::out );
            for (int i = 0; i <= NO_BUCKETS_SH_; i++)
                out_file.write( reinterpret_cast<const char*>(&i), sizeof(int) );
            out_file.close();
        } else {
            in_file.close();
        }
   }

   void StaticHashingFile::UpdateHeader(){
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
    
    long int StaticHashingFile::ReadAddress(long int position){
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

    void StaticHashingFile::UpdateAddress(long int position, long int new_address){
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

    void StaticHashingFile::CreateBlock(int position){
        
        long int y = -1;
        long int overflow_chain = -1;

        std::fstream file( dir_ + name_ + ext_, std::ios::binary | std::ios::in | std::ios::out | std::ios::ate );
        file.exceptions( file.failbit | file.badbit );
            try {
                file.seekp( position );
                for ( int i = 0; i <= NO_BUCKETS_SH_; i++ ) { 
                    file.write( reinterpret_cast<const char*>(&i), sizeof(int) );
                    for ( int j = 0; j < SIZE_DATA_BLOCK_SH_; j++ )
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

    int StaticHashingFile::GetHash(int key){
       int hash;
       hash = key % NO_BUCKETS_SH_;
       return hash; 
    }

    std::list< std::pair< int, std::vector<long int>> > StaticHashingFile::ReadBlock(const std::string& name,int position){
        
        std::list< std::pair< int, std::vector<long int>> > block;
        
        std::string dir = "tmp/";
        std::string ext = ".idx";

        std::fstream file( dir + name + ext, std::ios::binary | std::ios::in | std::ios::out | std::ios::ate );
        file.exceptions( file.failbit | file.badbit );
            try {
                file.seekp( position );
                for ( int i = 0; i <= NO_BUCKETS_SH_; i++ ) { 
                    int bucket = -1;
                    std::vector<long int> datablock;
                    file.read( reinterpret_cast<char*>(&bucket) , sizeof(int) );
                        for ( int j = 0; j < SIZE_DATA_BLOCK_SH_; j++ ){
                            long int data_address = -1;
                            file.read( reinterpret_cast<char*>(&data_address), sizeof(long int) );
                            datablock.push_back(data_address);
                        }
                        std::pair< int, std::vector<long int>> data_pair;
                        data_pair.first = bucket;
                        data_pair.second = datablock;
                        block.push_back(data_pair);
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

    void StaticHashingFile::UpdateLineToBlock(const std::string& name, int hash_position, std::vector<long int> block_address){
        
        if ( block_address.size() < SIZE_DATA_BLOCK_SH_ ){
            for (int i = block_address.size(); i < SIZE_DATA_BLOCK_SH_; i++){
                block_address.push_back(-1);
            }
        }
   
        std::string dir = "tmp/";
        std::string ext = ".idx";
        std::fstream file( dir + name + ext, std::ios::binary | std::ios::in | std::ios::out | std::ios::ate );  

        file.exceptions( file.failbit | file.badbit );
            try {
                
                file.seekp( hash_position );
                
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

}  // end namespace dictionary