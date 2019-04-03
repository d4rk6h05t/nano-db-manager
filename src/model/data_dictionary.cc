#include "data_dictionary.h"

namespace dictionary {

	// Constructors & destructosr
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
	
	// Setters
	void DataDictionary::SetId(int id){ id_ = id; }
	void DataDictionary::SetName(const std::string& name){ name_ = name; }
	void DataDictionary::SetDir(const std::string& dir){ dir_ = dir; }
	void DataDictionary::SetPath(const std::string& path){ path_ = path; }
	void DataDictionary::SetExt(const std::string& ext){ ext_ = ext; }
    void DataDictionary::SetFileHeader(long int file_header){ file_header_ = file_header; }
    // Getters
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
    
   // Methods of file 
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

    void DataDictionary::UpdateAddress(long int position, long int new_address){
   		std::fstream file( name_ + ext_, std::ios::binary | std::ios::in | std::ios::out | std::ios::ate );
		file.seekp( position  );
		file.write( reinterpret_cast<const char*>(&new_address), sizeof(long int) );
		file.close();
    }

    void DataDictionary::UpdateName(long int position, std::string new_name){
   		
   		char name[MAX_LENGTH_NAME_ENTTITY_];
        for (int i = 0; i < MAX_LENGTH_NAME_ENTTITY_; i++)
        	name[i] = new_name[i];

   		std::fstream file( name_ + ext_, std::ios::binary | std::ios::in | std::ios::out | std::ios::ate );
		file.seekp(position);
		file.write( reinterpret_cast<const char*>(name), MAX_LENGTH_NAME_ENTTITY_ );
		file.close();
    }

    // Methods of entities

    void DataDictionary::AddEntity(Entity entity){
        std::fstream file( name_ + ext_, std::ios::binary | std::ios::app);
	
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

		file.write( reinterpret_cast<const char*>(name), MAX_LENGTH_NAME_ENTTITY_ );
		file.write( reinterpret_cast<const char*>(&entity_address) , sizeof(long int) );
		file.write( reinterpret_cast<const char*>(&attribute_address), sizeof(long int) );
		file.write( reinterpret_cast<const char*>(&data_address), sizeof(long int) );
		file.write( reinterpret_cast<const char*>(&next_entity_address), sizeof(long int) );	 
		file.close();
    }

    void DataDictionary::UpdateEntity(std::list<Entity> list_entities, Entity *entity){
       	std::fstream file( name_ + ext_, std::ios::binary | std::ios::in | std::ios::out | std::ios::ate);
       	file.seekg(0, std::ios::end);
    	file_size_ = file.tellg();
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
				file.seekp( list_entities.front().GetEntityAddress() + 59 );
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

    void DataDictionary::RemoveEntity(std::list<Entity> list_entities, std::string remove_entity){
       	
       	long int end_address = -1;
       	std::fstream file( name_ + ext_, std::ios::binary | std::ios::in | std::ios::out | std::ios::ate);
        
        if ( !list_entities.empty() ){
        
        	std::string first_entity( list_entities.front().GetName() );
		
			if( remove_entity.compare(first_entity) ==  0 ){
				file_header_ = list_entities.front().GetNextEntityAddress();
				file.seekp( 0 );
				file.write( reinterpret_cast<const char*>(&file_header_), sizeof(long int) );
			}
		
			std::list<Entity>::iterator it_current = list_entities.begin();
			std::list<Entity>::iterator it_previus = std::prev( it_current , 1 );
		
			while ( it_current != list_entities.end() ){
		
				std::string it_current_entity( it_current->GetName() );
		
				if ( remove_entity.compare(it_current_entity) == 0 ){
					
					file.seekp( it_previus->GetEntityAddress() + 59 );
					long int new_next_entity_address = it_current->GetNextEntityAddress();
					file.write( reinterpret_cast<const char*>(&new_next_entity_address), sizeof(long int) );
					file.seekp( it_current->GetEntityAddress() + 59 );
					file.write( reinterpret_cast<const char*>(&end_address), sizeof(long int) );		 
					break;
				
				}
		
				it_current++;
				it_previus++;
			}
        } 
		file.close();											
    }

    Entity DataDictionary::SearchEntity(std::list<Entity> list_entities, std::string name_entity){
    	
    	Entity entity;
    	
    	for (std::list<Entity>::iterator it = list_entities.begin(); it != list_entities.end(); it++){
    	
    		std::string current_name( it->GetName() );
    	
    		if ( name_entity.compare( current_name ) == 0 ){
    			entity.SetName( current_name );
    			entity.SetEntityAddress( it->GetEntityAddress() );
    			entity.SetAttributeAddress( it->GetAttributeAddress() );
    			entity.SetDataAddress( it->GetDataAddress() );
    			entity.SetNextEntityAddress( it->GetNextEntityAddress() );
    		}
    	
    	}

    	return entity;
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
    	
    	std::fstream file( name_ + ext_, std::ios::binary | std::ios::app);
	
	    char name[MAX_LENGTH_NAME_ATTRIBUTE_];
		char data_type;
		int length_data_type;
		long int attribute_address;
		int type_index;
		long int index_address;
		long int next_attribute_address;
				
		for (int i = 0; i < MAX_LENGTH_NAME_ENTTITY_; i++)
		    name[i] = attribute.GetName()[i];      
		        
		data_type = attribute.GetDataType();
		length_data_type = attribute.GetLengthDataType();
		attribute_address = attribute.GetAttributeAddress();
		type_index = attribute.GetTypeIndex();
		index_address = attribute.GetIndexAddress();
		next_attribute_address = attribute.GetNextAttributeAddress();

		file.write( reinterpret_cast<const char*>(name), MAX_LENGTH_NAME_ATTRIBUTE_ );      // 35
		file.write( reinterpret_cast<const char*>(&data_type) , sizeof(char) );             // 1
		file.write( reinterpret_cast<const char*>(&length_data_type), sizeof(int) );        // 4
		file.write( reinterpret_cast<const char*>(&attribute_address), sizeof(long int) );  // 8 
		file.write( reinterpret_cast<const char*>(&type_index), sizeof(int) );              // 4
		file.write( reinterpret_cast<const char*>(&index_address), sizeof(long int) );      // 8
		file.write( reinterpret_cast<const char*>(&next_attribute_address), sizeof(long int) );	 
		file.close();
    }


    void DataDictionary::UpdateAttribute(std::list<Attribute> list_attributes, Attribute attribute){

       	std::fstream file( name_ + ext_, std::ios::binary | std::ios::in | std::ios::out | std::ios::ate);
       	long int end_address = -1;
        long int attribute_address = attribute.GetAttributeAddress();

    	if ( !list_attributes.empty() ){
    	    file.seekp( list_attributes.back().GetAttributeAddress() + 35 + 1 + 4 + 8 + 4 + 8 );
			file.write( reinterpret_cast<const char*>(&attribute_address), sizeof(long int) );
    	}
	
		file.close();
    }

    std::list<Attribute> DataDictionary::ReadListAttributes(Entity entity){
    	
    	std::list<Attribute> list_attributes;
       	std::fstream file( name_ + ext_, std::ios::in | std::ios::out | std::ios::binary );
     	
		long int next = entity.GetAttributeAddress();
		char name[MAX_LENGTH_NAME_ATTRIBUTE_];
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
       	
    	return list_attributes;
    }

}  // end namespace dictionary

