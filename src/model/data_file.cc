#include "data_file.h"

namespace archive {

	// Constructors & destructosr
	DataFile::DataFile(){ 
		dir_ = "tmp/";
		name_ = "unamed"; 
		ext_ = ".dat";
        file_header_ = -1;
	}

	DataFile::DataFile(const std::string& name){ 
		dir_ = "tmp/";
		name_ = name; 
		ext_ = ".dat";
        file_header_ = -1;
	}

	DataFile::~DataFile(){}
	
	// Setters

	void DataFile::SetName(const std::string& name){ name_ = name; }
	void DataFile::SetDir(const std::string& dir){ dir_ = dir; }
	void DataFile::SetExt(const std::string& ext){ ext_ = ext; }
    void DataFile::SetFileHeader(long int file_header){ file_header_ = file_header; }
    // Getters
    std::string DataFile::GetName(){ return name_;}
    std::string DataFile::GetDir(){ return dir_;}
    std::string DataFile::GetExt(){ return ext_;}
    long int DataFile::GetFileHeader(){return file_header_;}
    
    long int DataFile::GetFileSize(){
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
   void DataFile::CreateFile(){
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

   void DataFile::UpdateHeader(){
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
    
    long int DataFile::ReadAddress(long int position){
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

    void DataFile::UpdateAddress(long int position, long int new_address){
   		
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

    void DataFile::AppendCharData(char * char_data, int length_char_data){
    	std::fstream file( dir_ + name_ + ext_, std::ios::binary | std::ios::app);
	    char str[length_char_data];
		for (int i = 0; i < length_char_data; i++)
		    str[i] = char_data[i]; 
		file.exceptions( file.failbit | file.badbit );
			try {     
				file.write( reinterpret_cast<const char*>(str), length_char_data );
			} catch (const std::ios_base::failure & e) {
    			std::cout << std::endl << ":: Warning Exception: " << e.what() 
                          << std::endl << ":: Error code: " << e.code() 
                  		  << std::endl;
                if ( file.fail() ){
    				std::cout << " Error writing to file" << std::endl;
    				file.clear();
  				}
  			}
		file.close();
    }

    void DataFile::AppendIntData(int int_data){
    	std::fstream file( dir_ + name_ + ext_, std::ios::binary | std::ios::app);
    	file.exceptions( file.failbit | file.badbit );
			try {
				file.write( reinterpret_cast<const char*>(&int_data), sizeof(int) );
			} catch (const std::ios_base::failure & e) {
    			std::cout << std::endl << ":: Warning Exception: " << e.what() 
                          << std::endl << ":: Error code: " << e.code() 
                  		  << std::endl;
                if ( file.fail() ){
    				std::cout << "Error writing to file" << std::endl;
    				file.clear();
  				}
  			}
		file.close();	
    }

    void DataFile::AppendAddress(long int new_address){
    	std::fstream file( dir_ + name_ + ext_, std::ios::binary | std::ios::app);
		file.exceptions( file.failbit | file.badbit );
			try {
				file.write( reinterpret_cast<const char*>(&new_address), sizeof(long int) );
			} catch (const std::ios_base::failure & e) {
    			std::cout << std::endl << ":: Warning Exception: " << e.what() 
                          << std::endl << ":: Error code: " << e.code() 
                  		  << std::endl;
                if ( file.fail() ){
    				std::cout << "Error writing to file" << std::endl;
    				file.clear();
  				}
  			}
		file.close();	
    }

    void DataFile::AppendData(std::list<dictionary::Attribute> list_attributes){
    	
    	std::list<dictionary::Attribute>::iterator it = list_attributes.begin();
    	std::fstream file( dir_ + name_ + ext_, std::ios::binary | std::ios::in | std::ios::out | std::ios::ate);
		file.exceptions( file.failbit | file.badbit );
			try {
		       	
		       	file.seekg(0, std::ios::end);
		    	long int file_size = file.tellg();
		    	long int end_address = -1;
                long int length_struct_register = sizeof(long int) * 2;
				bool disable_index = true;

				file.write( reinterpret_cast<const char*>(&file_size), sizeof(long int)  );
				while ( it != list_attributes.end() ) {
			        std::cout << ":: " << it->GetName() << " : ";
                    if ( it->GetTypeIndex() > 0  )
                    	disable_index = false;
			        
			        if ( it->GetDataType() == 'c' ){
			        	length_struct_register = length_struct_register + it->GetLengthDataType();
						char str[ it->GetLengthDataType() ];
						std::cin >> str; 
						file.write( reinterpret_cast<const char*>(&str),  it->GetLengthDataType() );
					} else if ( it->GetDataType() == 'i' ){
						length_struct_register = length_struct_register + sizeof(int);
						int  x;
						std::cin >> x;
						file.write( reinterpret_cast<const char*>(&x), sizeof(int) );
					}
			       	++it;
			    }
			    
			    file.write( reinterpret_cast<const char*>(&end_address), sizeof(long int) );
                 
                file.seekg(0, std::ios::end);
		    	file_size = file.tellg(); 
	        	if ( disable_index && (file_size >  length_struct_register) ) {
                               
				    long int previus_next_address = file_size - ( length_struct_register  + sizeof(long int) ); 
				    long int next_address = file_size - length_struct_register;
				    std::cout << std::endl << ":: previus_next_address: " << previus_next_address << "/ next_address: " << next_address;     
				    
				    file.seekp(previus_next_address);
				    file.write( reinterpret_cast<const char*>(&next_address), sizeof(long int) );
				    		   	
				}	

	        } catch (const std::ios_base::failure & e) {
    			std::cout << std::endl << ":: Warning Exception: " << e.what() 
                          << std::endl << ":: Error code: " << e.code() 
                  		  << std::endl;
                if ( file.fail() ){
    				std::cout << "Error writing to file" << std::endl;
    				file.clear();
  				}
  			}
	    file.close();
    }

    
    void DataFile::ReadRegister(std::list<dictionary::Attribute> list_attributes){
    	long int register_address;
    	long int next_register_address;
    	
        std::fstream file( dir_ + name_ + ext_, std::ios::binary | std::ios::in | std::ios::out );
        long int next = 0;
        std::cout << std::endl << " register address \t";
        
        for( std::list<dictionary::Attribute>::iterator i = list_attributes.begin();  i != list_attributes.end() ; i++ )
        	std::cout << i->GetName() << "\t";		
        
        std::cout << " next address " << std::endl;

        while ( next != -1 ) {
			std::list<dictionary::Attribute>::iterator it = list_attributes.begin();
			file.exceptions( file.failbit | file.badbit );
				try {
					file.seekg( next );
					file.read( reinterpret_cast<char*>(&register_address) , sizeof(long int) );
					std::cout << "\t" << register_address << "\t\t";
			        
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
		            std::cout << "\t" << next_register_address << " \t ";
		            next = next_register_address;
		            std::cout << std::endl;
		            if ( next_register_address == -1 )
		            	break; 
            	} catch (const std::ios_base::failure & e) {
    				std::cout << std::endl << ":: Warning Exception: " << e.what() 
                          << std::endl << ":: Error code: " << e.code() 
                  		  << std::endl;
  				}
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