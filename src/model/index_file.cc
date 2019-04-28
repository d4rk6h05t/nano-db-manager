#include "index_file.h"

namespace dictionary {

    // Constructors & destructosr
    IndexFile::IndexFile(){ 
        dir_ = "tmp/";
        name_ = "unamed"; 
        ext_ = ".idx";
        file_header_ = -1;
        type_ = 0;
    }

    IndexFile::IndexFile(const std::string& name, int type){ 
        dir_ = "tmp/";
        name_ = name; 
        ext_ = ".idx";
        file_header_ = -1;
        type_ = type;
    }

    IndexFile::~IndexFile(){}
    
    // Setters

    void IndexFile::SetName(const std::string& name){ name_ = name; }
    void IndexFile::SetDir(const std::string& dir){ dir_ = dir; }
    void IndexFile::SetExt(const std::string& ext){ ext_ = ext; }
    
    void IndexFile::SetTypeIndex(int type){ type_ = type; }
    void IndexFile::SetFileHeader(long int file_header){ file_header_ = file_header; }
    
    // Getters
    std::string IndexFile::GetName(){ return name_;}
    std::string IndexFile::GetDir(){ return dir_;}
    std::string IndexFile::GetExt(){ return ext_;}

    int IndexFile::GetTypeIndex(){ return type_; }
    long int IndexFile::GetFileHeader(){return file_header_;}
    
    long int IndexFile::GetFileSize(){
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
   void IndexFile::CreateFile(){
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

   void IndexFile::UpdateHeader(){
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
    
    long int IndexFile::ReadAddress(long int position){
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

    void IndexFile::UpdateAddress(long int position, long int new_address){
        
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


}  // end namespace dictionary