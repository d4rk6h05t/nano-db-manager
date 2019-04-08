#include "data_file.h"

namespace archive {

	// Constructors & destructosr
	DataFile::DataFile(){ 
		path_ = "/home/someuser/myproject";
		dir_ = "tmp/";
		name_ = "unamed"; 
		ext_ = ".dat";
        file_header_ = -1;
	}

	DataFile::DataFile(const std::string& name){ 
		path_ = "/home/someuser/myproject";
		dir_ = "tmp/";
		name_ = name; 
		ext_ = ".dat";
        file_header_ = -1;
	}

	DataFile::~DataFile(){}
	
	// Setters

	void DataFile::SetName(const std::string& name){ name_ = name; }
	void DataFile::SetDir(const std::string& dir){ dir_ = dir; }
	void DataFile::SetPath(const std::string& path){ path_ = path; }
	void DataFile::SetExt(const std::string& ext){ ext_ = ext; }
    void DataFile::SetFileHeader(long int file_header){ file_header_ = file_header; }
    // Getters
    std::string DataFile::GetName(){ return name_;}
    std::string DataFile::GetDir(){ return dir_;}
    std::string DataFile::GetPath(){ return path_;}
    std::string DataFile::GetExt(){ return ext_;}
    long int DataFile::GetFileHeader(){return file_header_;}
    
    long int DataFile::GetFileSize(){
    	std::ifstream file ( name_ + ext_, std::ios::binary | std::ios::in );
    	file.seekg(0, std::ios::end);
    	file_size_ = file.tellg();
    	file.close();
		return file_size_;
    }
    
   // Methods of file 
   void DataFile::CreateFile(){
   			std::ofstream file( name_ + ext_, std::ios::binary | std::ios::out );
			file.seekp(0);
			//file.write( reinterpret_cast<const char*>(&file_header_), sizeof(long int) );
			file.close();
   }

   void DataFile::UpdateHeader(){
   		std::fstream file( name_ + ext_, std::ios::binary | std::ios::in | std::ios::out | std::ios::ate );
		file.seekp(0);
		file.write( reinterpret_cast<const char*>(&file_header_), sizeof(long int) );
		file.close();
    }
    
    long int DataFile::ReadAddress(long int position){
    	long int data;
   		std::fstream file( name_ + ext_, std::ios::binary | std::ios::in | std::ios::out );
		file.seekp( position  );
		file.read( reinterpret_cast<char*>(&data) , sizeof(long int) ); 
		file.close();
		return data;
    }

    void DataFile::UpdateAddress(long int position, long int new_address){
   		
   		std::fstream file( name_ + ext_, std::ios::binary | std::ios::in | std::ios::out | std::ios::ate );
		file.seekp( position  );
		file.write( reinterpret_cast<const char*>(&new_address), sizeof(long int) );
		file.close();
   		//std::fstream file( name_ + ext_, std::ios::binary | std::ios::in | std::ios::out | std::ios::ate );
		
		//long int data;
		
		//file.seekp( position  );
		//file.read( reinterpret_cast<char*>(&data) , sizeof(long int) );
		//std::cout << std::endl << "data old " << data; 
		/*
		file.seekp( position  );
		file.write( reinterpret_cast<const char*>(&new_address), sizeof(long int) );
        
        file.seekp( position  );
		file.read( reinterpret_cast<char*>(&data) , sizeof(long int) );
		std::cout << std::endl << "data new " << data;
		*/
		//file.close();
    }

    void DataFile::AppendCharData(char * char_data, int length_char_data){
    	std::fstream file( name_ + ext_, std::ios::binary | std::ios::app);
	    char str[length_char_data];
		for (int i = 0; i < length_char_data; i++)
		    str[i] = char_data[i];      
		file.write( reinterpret_cast<const char*>(str), length_char_data );
		file.close();
    }

    void DataFile::AppendIntData(int int_data){
    	std::fstream file( name_ + ext_, std::ios::binary | std::ios::app);
		file.write( reinterpret_cast<const char*>(&int_data), sizeof(int) );
		file.close();	
    }

    void DataFile::AppendAddress(long int new_address){
    	std::fstream file( name_ + ext_, std::ios::binary | std::ios::app);
		file.write( reinterpret_cast<const char*>(&new_address), sizeof(long int) );
		file.close();	
    }

    void DataFile::AppendData(std::list<dictionary::Attribute> list_attributes){
    	
    	std::list<dictionary::Attribute>::iterator it = list_attributes.begin();
    	std::fstream file( name_ + ext_, std::ios::binary | std::ios::app);
       	file.seekg(0, std::ios::end);
    	long int file_size = file.tellg();
    	long int end_address = -1;

		file.write( reinterpret_cast<const char*>(&file_size), sizeof(long int)  );
		while ( it != list_attributes.end() ) {
	        std::cout << std::endl << ":: " << it->GetName() << " : ";
	        if ( it->GetDataType() == 'c' ){
				char str[ it->GetLengthDataType() ];
				std::cin >> str; 
				file.write( reinterpret_cast<const char*>(&str),  it->GetLengthDataType() );
			} else if ( it->GetDataType() == 'i' ){
				int  x;
				std::cin >> x;
				file.write( reinterpret_cast<const char*>(&x), sizeof(int) );
			}
	       	++it;
	    }
	    file.write( reinterpret_cast<const char*>(&end_address), sizeof(long int) );
	    file.close();
    }

    
    void DataFile::ReadRegister(std::list<dictionary::Attribute> list_attributes){
    	long int register_address;
    	long int next_register_address;
    	std::list<dictionary::Attribute>::iterator it = list_attributes.begin();
        std::fstream file( name_ + ext_, std::ios::binary | std::ios::in | std::ios::out );
        long int next = 0;
        while( next != -1 ){
			//file.seekg( next );
			file.read( reinterpret_cast<char*>(&register_address) , sizeof(long int) );
			std::cout << "\t" << register_address << "\t";
	        while ( it != list_attributes.end() ) {
	        	if ( it->GetDataType() == 'c' ){
					char str[ it->GetLengthDataType() ];
					file.read( reinterpret_cast<char*>(str) , it->GetLengthDataType() );
					std::cout << str << "\t";		
				} else if ( it->GetDataType() == 'i' ){
					int  x;
					file.read( reinterpret_cast<char*>(&x), sizeof( int ) );
					std::cout << x << "\t";
				}
	        	it++;
	        }
	        file.read( reinterpret_cast<char*>(&next_register_address) , sizeof(long int) );
            std::cout << next_register_address << " \t ";
            next = next_register_address;
            if ( next_register_address == -1 )
            	break; 
            
    	}
    	file.close();
    }


    int DataFile::GetSizeRegister(std::list<dictionary::Attribute> list_attributes){
    	int length = sizeof(long int)*2; // because start address & end addres
    	std::list<dictionary::Attribute>::iterator it = list_attributes.begin();
	        while ( it != list_attributes.end() ) {
	        	if ( it->GetDataType() == 'c' )
		            length = length + it->GetLengthDataType();	
				else if ( it->GetDataType() == 'i' )
					length = length + sizeof( int );
	        	it++;
	        }
	    return length; 
    }

    /*
    void DataFile::UpdateRegister(std::list<dictionary::Attribute> list_attributes,long int position ,long int new_address){
    	
    	long int register_address;
    	long int next_register_address;
		
		std::fstream file( name_ + ext_, std::ios::binary | std::ios::in | std::ios::out | std::ios::ate);
        
        long int next = position;
        file.seekg( next );
        while( next != -1 ){
			file.read( reinterpret_cast<char*>(&register_address) , sizeof(long int) );
	        while ( it != list_attributes.end() ) {
	        	if ( it->GetDataType() == 'c' ){
					char str[ it->GetLengthDataType() ];
					file.read( reinterpret_cast<char*>(str) , it->GetLengthDataType() );
				} else if ( it->GetDataType() == 'i' ){
					int  x;
					file.read( reinterpret_cast<char*>(&x), sizeof( int ) );
				}
	        	it++;
	        }
	        file.read( reinterpret_cast<char*>(&next_register_address) , sizeof(long int) );
            std::cout << "->" << next_register_address << " \t ";
            next = next_register_address;
            if (next == -1 ){
            	file.seekp( next - sizeof(long int) );
                file.write( reinterpret_cast<const char*>(&), sizeof(int) );
            }
            list_next_addres.push_back(next);
    	}

    	file.close();	
        return list_next_addres;
    }*/


   

}  // end namespace archive