#include "file.h"

namespace repository {

    // Constructors & destructosr
    File::File(){ 
        dir_ = "tmp/";
        name_ = "unamed"; 
        ext_ = ".dat";
        file_header_ = -1;
    }

    File::File(const std::string& name){ 
        dir_ = "tmp/";
        name_ = name; 
        ext_ = ".dat";
        file_header_ = -1;
    }

    File::~File(){}
    
    // Setters
    void File::SetName(const std::string& name){ name_ = name; }
    void File::SetDir(const std::string& dir){ dir_ = dir; }
    void File::SetExt(const std::string& ext){ ext_ = ext; }
    
    void File::SetFileHeader(long int file_header){ file_header_ = file_header; }
    
    // Getters
    std::string File::GetName(){ return name_;}
    std::string File::GetDir(){ return dir_;}
    std::string File::GetExt(){ return ext_;}

    long int File::GetFileHeader(){return file_header_;}
    
    long int File::GetFileSize(){
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

    void File::CreateDirectory(){
        std::filesystem::create_directory(dir_);
   }

    // Methods of file 
   void File::CreateFile(){
        std::ifstream in_file( dir_ + name_ + ext_, std::ios::binary | std::ios::in );
        if ( !in_file.good() ){
            std::ofstream out_file( dir_ + name_ + ext_, std::ios::binary | std::ios::out );
            out_file.seekp(0);
            out_file.close();
        } else {
            in_file.seekg(0);
            in_file.close();
        }
   }

   void File::UpdateHeader(){
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
    
    long int File::ReadAddress(long int position){
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

    void File::UpdateAddress(long int position, long int new_address){
        
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

    void File::UpdateName(long int position, std::string new_name){
        
        char name[MAX_LENGTH_NAME_];
        for (int i = 0; i < MAX_LENGTH_NAME_; i++)
            name[i] = new_name[i];

        std::fstream file( dir_ + name_ + ext_, std::ios::binary | std::ios::in | std::ios::out | std::ios::ate );
        file.exceptions( file.failbit | file.badbit );
            try {
                file.seekp(position);
                file.write( reinterpret_cast<const char*>(name), MAX_LENGTH_NAME_ );
            } catch (const std::ios_base::failure & e) {
                std::cout << std::endl << ":: Warning Exception: " << e.what() 
                          << std::endl << ":: Error code: " << e.code() 
                          << std::endl;
            }
        file.close();
    }
    
    void File::UpdateChar(long int position, char new_char){
        std::fstream file( dir_ + name_ + ext_, std::ios::binary | std::ios::in | std::ios::out | std::ios::ate );
        file.exceptions( file.failbit | file.badbit );
            try {
                file.seekp(position);
                file.write( reinterpret_cast<const char*>(&new_char), sizeof( char ) );
            } catch (const std::ios_base::failure & e) {
                std::cout << std::endl << ":: Warning Exception: " << e.what() 
                          << std::endl << ":: Error code: " << e.code() 
                          << std::endl;
            }
        file.close();
    }

    void File::UpdateInt(long int position, int new_int){
        std::fstream file( dir_ + name_ + ext_, std::ios::binary | std::ios::in | std::ios::out | std::ios::ate );
        file.exceptions( file.failbit | file.badbit );
            try {
                file.seekp(position);
                file.write( reinterpret_cast<const char*>(&new_int), sizeof( int ) );
            } catch (const std::ios_base::failure & e) {
                std::cout << std::endl << ":: Warning Exception: " << e.what() 
                          << std::endl << ":: Error code: " << e.code() 
                          << std::endl;
            }
        file.close();
    }

}  // end namespace repository