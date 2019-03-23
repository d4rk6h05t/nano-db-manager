#include "data_dictionary.h"

namespace dictionary {

	
	DataDictionary::DataDictionary(){ 
		id_ = 0;
		path_ = "/home/someuser/myproject";
		dir_ = "tmp/";
		name_ = "unamed"; 
		ext_ = ".dat";
        file_header_ = -1;
	}

	DataDictionary::DataDictionary(const std::string& name){ 
		id_ = 0;
		path_ = "/home/someuser/myproject";
		dir_ = "tmp/";
		name_ = name; 
		ext_ = ".dat";
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
   			std::ofstream file( name_ + ext_, std::ios::binary | std::ios::out );
			file.seekp(0);
			file.write( reinterpret_cast<const char*>(&file_header_), sizeof(long int) );
			file.close();
   }

   void DataDictionary::UpdateHeader(){
   		std::fstream file( name_ + ext_, std::ios::binary | std::ios::in | std::ios::out | std::ios::ate );
		file.seekp(0);
		file.write( reinterpret_cast<const char*>(&file_header_), sizeof(long int) );
		file.close();
    }

    void DataDictionary::UpdateEntity(Entity *entity){
        
       	char name[MAX_LENGTH_NAME_ENTTITY_];
		long int entity_address;
		long int attribute_address;
		long int data_address;
		long int next_entity_address;

       	std::list<Entity> list_entities;
       	
       	std::fstream file( name_ + ext_, std::ios::binary | std::ios::in | std::ios::out | std::ios::ate);

       	file.seekg(0, std::ios::end);
    	file_size_ = file.tellg();
       	
       	file.seekp(0);
       	long int file_header, next;
    	file.read( reinterpret_cast<char*>( &file_header ), sizeof( long int ) );
		file_header_ = file_header;

		next = file_header;
			
		while( next != -1 ){
		
			file.seekg( next );
			file.read( reinterpret_cast<char*>( name) , MAX_LENGTH_NAME_ENTTITY_ );
			file.read( reinterpret_cast<char*>(&entity_address), sizeof(long int) );
			file.read( reinterpret_cast<char*>(&attribute_address), sizeof(long int) );
			file.read( reinterpret_cast<char*>(&data_address), sizeof(long int) );
			file.read( reinterpret_cast<char*>(&next_entity_address), sizeof(long int) );

			next = next_entity_address;
			
			std::string str_name(name);
			Entity current_entity;
			current_entity.SetName(str_name);
			current_entity.SetEntityAddress(entity_address);
		    current_entity.SetAttributeAddress(attribute_address);
		    current_entity.SetDataAddress(data_address);
		    current_entity.SetNextEntityAddress(next_entity_address);
			list_entities.push_back(current_entity);
		}
		
	    /* ::::: create a sort list  ::::: */
		long int  end_address = -1;
        long int entity_address_min,entity_next_address_min;
        int i = 0; // first position
		int it_position = i;
		int flag;
        std::string min;
        std::list<Entity>::iterator it_current = list_entities.begin();
										     								    
		if( list_entities.empty() ) {
										    	
			min = entity->GetName();
			entity_address_min = file_size_;
			entity_next_address_min = end_address;
			flag = -1; 
										    
		} else {

			while ( it_current != list_entities.end()  ){
                                                     
                std::string new_entity( entity->GetName() );
                std::string it_current_entity( it_current->GetName() ); 										    
				int comparison_response = new_entity.compare( it_current_entity ); 
										    		
				if ( i == 0  ){
					if ( comparison_response < 0 ) {
						flag = 0;
						min = entity->GetName();
						entity_address_min = file_size_;
						entity_next_address_min = it_current->GetEntityAddress();
						it_position = i ; // first position
										    				
					} else if ( comparison_response > 0 ) {										    	
						flag = 1;
						min = it_current->GetName();
						entity_address_min = it_current->GetEntityAddress();
						entity_next_address_min = file_size_;
						it_position = i + 1; // secon position			
					} 
				} else if ( i > 0 ) {
					flag = 2;									 
    				if ( comparison_response < 0 ){
                        min = entity->GetName();
    					entity_address_min = file_size_;
    					entity_next_address_min = it_current->GetEntityAddress();									
                    } else if ( comparison_response > 0 ){
    					min = it_current->GetName();
                        entity_address_min = it_current->GetEntityAddress();
                        entity_next_address_min = file_size_;
    				}
                                                        
					int comparison_response_current_min = new_entity.compare(min); 
					if ( comparison_response_current_min < 0 ) { it_position = i - 1; break; } 
					else if ( comparison_response_current_min > 0 ) it_position = i + 1;
										    			
				} // end if else
										    		
				i++;
				it_current++;
										    
				} // end while
			} // end else != empty list
											
			std::list<Entity>::iterator current = list_entities.begin();
			std::list<Entity>::iterator previus = std::prev( current , 1 );

			int it_count = 0;

			if ( flag == -1 ) list_entities.push_back(*entity); 
			else if ( flag == 0 || it_position == 0){								
				entity->SetNextEntityAddress( list_entities.front().GetEntityAddress() );
				list_entities.push_front(*entity);
			} else if ( flag == 1 ){
				file.seekp( list_entities.front().GetEntityAddress() );
				file.write( reinterpret_cast<const char*>(&file_size_), sizeof(long int) );
				entity->SetNextEntityAddress( end_address );
				list_entities.push_back(*entity);						
			} else if ( flag == 2  ){																				
				
				do {
					if ( it_count == it_position ){
						file.seekp( previus->GetEntityAddress() + 59 );
						file.write( reinterpret_cast<const char*>(&file_size_), sizeof(long int) );
						entity->SetNextEntityAddress( previus->GetNextEntityAddress() ); 
                        list_entities.insert(current,*entity);  	
                    }
					it_count++;
                    current++; 
                    previus++; 
				} while ( it_count <= it_position );	
			}
			/* ::::: end create a sort list  ::::: */
		file_header_ = list_entities.front().GetEntityAddress();
		file.seekp( 0 );
		file.write( reinterpret_cast<const char*>(&file_header_), sizeof(long int) );
		file.close();
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
		// 59 = 35 + 8 + 8 + 8
		out_file.seekp( position + 59 );
		out_file.write( reinterpret_cast<const char*>(&new_address), sizeof(long int) );
		out_file.seekp( position + 59 );
		out_file.read( reinterpret_cast<char*>(&next_entity_address), sizeof(long int) );
		
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
		file.close(); 
    }
    

}  // end namespace dictionary

