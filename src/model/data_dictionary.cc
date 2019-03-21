#include "data_dictionary.h"

namespace dictionary {

	
	DataDictionary::DataDictionary(){ 
		
		id_ = 0;
		std::string path = "/home/someuser/myproject";
		std::string tmp_dir = "tmp/";
		std::string tmp_name = "unamed";
		std::string ext = ".dat";
       
		path_ = path;
		dir_ = tmp_dir;
		name_ = tmp_name; 
		ext_ = ext;
        
        file_header_ = -1;
		
         
	}

	DataDictionary::DataDictionary(const std::string& name){ 
		
		id_ = 0;
		std::string path = "/home/someuser/myproject";
		std::string tmp_dir = "tmp/";
		std::string ext = ".dat";

		path_ = path;
		dir_ = tmp_dir;
		name_ = name; 
		ext_ = ext;
        
        file_header_ = -1;
	}

	DataDictionary::~DataDictionary(){}
	
	void DataDictionary::SetId(int id){ id_ = id; }
	void DataDictionary::SetName(const std::string& name){ name_ = name; }
	void DataDictionary::SetDir(const std::string& dir){ dir_ = dir; }
	void DataDictionary::SetPath(const std::string& path){ path_ = path; }
	void DataDictionary::SetExt(const std::string& ext){ ext_ = ext; }
    void DataDictionary::SetFileHeader(long int file_header){ file_header_ = file_header; }

    int DataDictionary::GetId(){ return id_;}
    std::string DataDictionary::GetName(){ return name_;}
    std::string DataDictionary::GetDir(){ return dir_;}
    std::string DataDictionary::GetPath(){ return path_;}
    std::string DataDictionary::GetExt(){ return ext_;}
    long int DataDictionary::GetFileHeader(){return file_header_;}
    
    long int DataDictionary::GetFileSize(){
    	std::ifstream file ( name_ + ext_, std::ios::binary | std::ios::in );
    	file.seekg(0, std::ios::end);
    	file_size_ = file.tellg();
    	file.close();
		return file_size_;
    }
    
   void DataDictionary::CreateFile(){
   			std::ofstream out_file( name_ + ext_, std::ios::binary | std::ios::out );
			out_file.seekp(0);
			std::cout << std::endl << " ::::: file_header :::: ***** >>> " << file_header_ << std::endl;
			out_file.write( reinterpret_cast<const char*>(&file_header_), sizeof(long int) );
			out_file.close();
   }

   void DataDictionary::UpdateHeader(){
   		std::fstream out_file( name_ + ext_, std::ios::binary | std::ios::in | std::ios::out | std::ios::ate );
		out_file.seekp(0);
		out_file.write( reinterpret_cast<const char*>(&file_header_), sizeof(long int) );
		long int save;
		out_file.seekp(0);
		out_file.read( reinterpret_cast<char*>(&save), sizeof(long int) );
		std::cout << std::endl << " ::::: file_header :::: ***** >>>{saved..} " << save << std::endl;
		out_file.close();
    }

    void DataDictionary::AddEntity(Entity entity){
        std::fstream out_file( name_ + ext_, std::ios::binary | std::ios::app);
	
	    char name[MAX_LENGTH_NAME_ENTTITY_];
		long int entity_address;
		long int attribute_address;
		long int data_address;
		long int next_entity_address;
				
		for (int i = 0; i < MAX_LENGTH_NAME_ENTTITY_; i++)
		    name[i] = entity.GetName()[i];      
		        
		entity_address = entity.GetEntityAddress();
		attribute_address = entity.GetAttributeAddress();
		data_address = entity.GetDataAddress();
		next_entity_address = entity.GetNextEntityAddress();

		out_file.write( reinterpret_cast<const char*>(name), MAX_LENGTH_NAME_ENTTITY_ );
		out_file.write( reinterpret_cast<const char*>(&entity_address) , sizeof(long int) );
		out_file.write( reinterpret_cast<const char*>(&attribute_address), sizeof(long int) );
		out_file.write( reinterpret_cast<const char*>(&data_address), sizeof(long int) );
		out_file.write( reinterpret_cast<const char*>(&next_entity_address), sizeof(long int) );
	 
		out_file.close();
    }
    /*
    void DataDictionary::AddEntity(Entity entity){

        std::fstream out_file( name_ + ext_, std::ios::binary | std::ios::app);
	
	    char name[MAX_LENGTH_NAME_ENTTITY_];
		long int entity_address;
		long int attribute_address;
		long int data_address;
		long int next_entity_address;
				
		for (int i = 0; i < MAX_LENGTH_NAME_ENTTITY_; i++)
		    name[i] = entity.GetName()[i];      
		        
		entity_address = entity.GetEntityAddress();
		attribute_address = entity.GetAttributeAddress();
		data_address = entity.GetDataAddress();
		next_entity_address = entity.GetNextEntityAddress();

		out_file.write( reinterpret_cast<const char*>(name), MAX_LENGTH_NAME_ENTTITY_ );
		out_file.write( reinterpret_cast<const char*>(&entity_address) , sizeof(long int) );
		out_file.write( reinterpret_cast<const char*>(&attribute_address), sizeof(long int) );
		out_file.write( reinterpret_cast<const char*>(&data_address), sizeof(long int) );
		out_file.write( reinterpret_cast<const char*>(&next_entity_address), sizeof(long int) );
	 
		out_file.close();
    }
    
    void DataDictionary::AddEntityV2(Entity new_entity){
    	
    	std::list<Entity> list_entities;
       	std::fstream file( name_ + ext_, std::ios::in | std::ios::out | std::ios::ate | std::ios::binary );
       	file.seekp(0);
       	long int file_header, next;
    	file.read( reinterpret_cast<char*>( &file_header ), sizeof( long int ) );
		file_header_ = file_header;
		std::cout << std::endl << " ::::: file_header :::: ***** >>> " << file_header << std::endl;
		
		next = file_header;
		char name[MAX_LENGTH_NAME_ENTTITY_];
		long int entity_address;
		long int next_entity_address;
		
		while( next != -1 ){

			Entity current_entity; // entity tmp
			file.seekg( next );
			
			file.read( reinterpret_cast<char*>( name) , MAX_LENGTH_NAME_ENTTITY_ );
			file.read( reinterpret_cast<char*>(&entity_address), sizeof(long int) );
			file.read( reinterpret_cast<char*>(&next_entity_address), sizeof(long int) );
			
			
			std::string current_name(name);
			current_entity.SetName(current_name);
			
			if ( new_entity.GetName() < current_entity.GetName() ) {

			} else if ( new_entity.GetName() > current_entity.GetName() ) {

			}
			 
			current_entity.SetEntityAddress(entity_address);
		    current_entity.SetNextEntityAddress(next_entity_address);
			
            

		    next = next_entity_address; // jump to next
		}
		file.close();	
       	
    	return list_entities;
    }
    */

    void DataDictionary::UpdateAddress(long int position, long int new_address){
   		
   		char name[MAX_LENGTH_NAME_ENTTITY_];
		long int entity_address;
		long int attribute_address;
		long int data_address;
		long int next_entity_address;

   		std::fstream out_file( name_ + ext_, std::ios::binary | std::ios::in | std::ios::out | std::ios::ate );
		

		out_file.seekp(position);

		out_file.read( reinterpret_cast<char*>(name), MAX_LENGTH_NAME_ENTTITY_ );
		out_file.read( reinterpret_cast<char*>(&entity_address) , sizeof(long int) );
		out_file.read( reinterpret_cast<char*>(&attribute_address), sizeof(long int) );
		out_file.read( reinterpret_cast<char*>(&data_address), sizeof(long int) );
		out_file.read( reinterpret_cast<char*>(&next_entity_address), sizeof(long int) );
		/*
		std::cout << std::endl << " :: name -> " << name << std::endl
							   << " :: entity addres -> " << entity_address << std::endl
							   << " :: attribute addres -> " << attribute_address << std::endl
							   << " :: data addres -> " << data_address << std::endl
							   << " :: next entity addres -> " << next_entity_address << std::endl			
							   << std::endl;
		*/
		// 59 = 35 + 8 + 8 + 8
		out_file.seekp( position + 59 );
		out_file.write( reinterpret_cast<const char*>(&new_address), sizeof(long int) );
		out_file.seekp( position + 59 );
		out_file.read( reinterpret_cast<char*>(&next_entity_address), sizeof(long int) );
		
		//std::cout << std::endl << " :: new next entity addres -> " << next_entity_address << std::endl;
		out_file.close();
    }

    void DataDictionary::UpdateName(long int position, std::string new_name){
   		
   		char name[MAX_LENGTH_NAME_ENTTITY_];
        for (int i = 0; i < MAX_LENGTH_NAME_ENTTITY_; i++)
        	name[i] = new_name[i];

   		std::fstream out_file( name_ + ext_, std::ios::binary | std::ios::in | std::ios::out | std::ios::ate );
		
		out_file.seekp(position);
		out_file.write( reinterpret_cast<const char*>(&name), MAX_LENGTH_NAME_ENTTITY_ );
		
		out_file.close();
    }

    
    std::list<Entity> DataDictionary::ReadListEntities(){
    	
    	std::list<Entity> list_entities;
       	std::fstream file( name_ + ext_, std::ios::in | std::ios::out | std::ios::binary );
       	
       	file.seekp(0);
       	long int file_header, next;
    	file.read( reinterpret_cast<char*>( &file_header ), sizeof( long int ) );
		file_header_ = file_header;
		std::cout << std::endl << " ::::: file_header :::: ***** >>> " << file_header << std::endl;
		next = file_header;

		char name[MAX_LENGTH_NAME_ENTTITY_];
		long int entity_address;
		long int attribute_address;
		long int data_address;
		long int next_entity_address;
			
		while( next != -1 ){
		
			file.seekg( next );
			file.read( reinterpret_cast<char*>( name) , MAX_LENGTH_NAME_ENTTITY_ );
			file.read( reinterpret_cast<char*>(&entity_address), sizeof(long int) );
			file.read( reinterpret_cast<char*>(&attribute_address), sizeof(long int) );
			file.read( reinterpret_cast<char*>(&data_address), sizeof(long int) );
			file.read( reinterpret_cast<char*>(&next_entity_address), sizeof(long int) );

			next = next_entity_address;
			
			std::string str_name(name);
			Entity entity;
			entity.SetName(str_name);
			entity.SetEntityAddress(entity_address);
		    entity.SetAttributeAddress(attribute_address);
		    entity.SetDataAddress(data_address);
		    entity.SetNextEntityAddress(next_entity_address);
			list_entities.push_back(entity);
		}
		
		file.close();	
       	
    	return list_entities;
    }

    void DataDictionary::AddAttribute(Attribute attribute){
    	list_attributes_.push_back(attribute);
    	std::fstream file ( name_ + ext_, std::fstream::binary | std::fstream::out );
        file.seekg (file_size_, std::fstream::end);
		file.write( (char*) &attribute, sizeof(dictionary::Attribute) );
		std::cout << std::endl << name_ + ext_ << " successfully updated file!"  << std::endl;
		file.close(); 
    }
    

}  // end namespace dictionary

