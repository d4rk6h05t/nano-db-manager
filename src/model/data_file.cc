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

    void DataFile::UpdateAddress(long int position, long int new_address){
   		std::fstream file( name_ + ext_, std::ios::binary | std::ios::in | std::ios::out | std::ios::ate );
		file.seekp( position  );
		file.write( reinterpret_cast<const char*>(&new_address), sizeof(long int) );
		file.close();
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

    
    void DataFile::ReadRegister(dictionary::Entity entity, std::list<dictionary::Attribute> list_attributes){
    	
    	//long int next = entity.GetDataAddress();
    	long int register_address;
    	long int next_register_address;
    	//std::cout << ":: next : " << next << std::endl;
        std::list<dictionary::Attribute>::iterator it = list_attributes.begin();
        std::fstream file( name_ + ext_, std::ios::in | std::ios::out | std::ios::binary );
        
        //file.seekg( next );
        long int next = 0;
        file.seekg( next );
        while( next != -1 ){
            
            
			file.read( reinterpret_cast<char*>(&register_address) , sizeof(long int) );
			//next = next + sizeof(long int);
            std::cout << "->" << register_address << " \t ";

	        while ( it != list_attributes.end() ) {
        	

	        	if ( it->GetDataType() == 'c' ){
					
					char str[ it->GetLengthDataType() ];
					//file.seekg( next );
					file.read( reinterpret_cast<char*>(str) , it->GetLengthDataType() );
					//next = next + it->GetLengthDataType();
					std::cout << "->" << str << " \t ";		
				
				} else if ( it->GetDataType() == 'i' ){
					
					int  x;
					//file.seekg( next );
					file.read( reinterpret_cast<char*>(&x), sizeof( int ) );
					//next = next + it->GetLengthDataType();
					std::cout << "->" << x << " \t ";
				}

	        	it++;
	        }

	        //file.seekg( next );
			file.read( reinterpret_cast<char*>(&next_register_address) , sizeof(long int) );
            std::cout << "->" << next_register_address << " \t ";
            next = next_register_address;
    	}

    	file.close();	


       	
     	
        /*
     	
		
		char name[MAX_LENGTH_NAME_DATA_FILE_];
		char data_type;
		int length_data_type;
		long int attribute_address;
		int type_index;
		long int index_address;
		long int next_attribute_address;
			
		while( next != -1 ){
		
			file.seekg( next );
			file.read( reinterpret_cast<char*>( name) , MAX_LENGTH_NAME_ENTTITY_ );
			file.read( reinterpret_cast<char*>(&data_type), sizeof(char) );
			file.read( reinterpret_cast<char*>(&length_data_type), sizeof(int) );
			file.read( reinterpret_cast<char*>(&attribute_address), sizeof(long int) );
			file.read( reinterpret_cast<char*>(&type_index), sizeof(int) );
			file.read( reinterpret_cast<char*>(&index_address), sizeof(long int) );
			file.read( reinterpret_cast<char*>(&next_attribute_address), sizeof(long int) );

			next = next_attribute_address;
			
			std::string str_name(name);
			Attribute attribute;
			attribute.SetName(str_name);
			attribute.SetDataType(data_type);
			attribute.SetLengthDataType(length_data_type);
			attribute.SetAttributeAddress(attribute_address);
			attribute.SetTypeIndex(type_index);
			attribute.SetIndexAddress(index_address);
			attribute.SetNextAttributeAddress(next_attribute_address);

			list_attributes.push_back(attribute);
		}
		
		file.close();	
       	
    	*/
    }

   

}  // end namespace archive