#include "data_dictionary.h"

namespace repository {

    // Methods of entities

    void DataDictionary::AddEntity(dictionary::Entity entity){
        std::fstream file( dir_ + name_ + ext_, std::ios::binary | std::ios::app);
	    
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
        file.exceptions( std::fstream::failbit | std::fstream::badbit );
			try {
				file.write( reinterpret_cast<const char*>(name), MAX_LENGTH_NAME_ENTTITY_ );
				file.write( reinterpret_cast<const char*>(&entity_address) , sizeof(long int) );
				file.write( reinterpret_cast<const char*>(&attribute_address), sizeof(long int) );
				file.write( reinterpret_cast<const char*>(&data_address), sizeof(long int) );
				file.write( reinterpret_cast<const char*>(&next_entity_address), sizeof(long int) );	
			} catch (const std::ios_base::failure & e) {
    			std::cout << std::endl << ":: Warning Exception: " << e.what() 
                  		  << std::endl << ":: Error code: " << e.code() 
                  		  << std::endl;
  			}
		file.close();
    }

    void DataDictionary::UpdateEntity2(std::list<dictionary::Entity> list_entities, dictionary::Entity *new_entity){

       	std::fstream file( dir_ + name_ + ext_, std::ios::binary | std::ios::in | std::ios::out | std::ios::ate);
       	file.exceptions( file.failbit | file.badbit );
       	
       	try {
       		
       		file.seekg(0, std::ios::end);
		    file_size_ = file.tellg();
			long int  end_address = -1;
       		list_entities.push_back(*new_entity);
       		
       		if ( list_entities.size() == 1 ) {
       			file.seekp( 0 );
				file.write( reinterpret_cast<const char*>(&file_size_), sizeof(long int) );
				file_header_ = file_size_;
       		} else if ( list_entities.size() > 1 ){

	       		list_entities.sort([](dictionary::Entity entity_x, dictionary::Entity entity_y){
		       	 	return entity_x.GetNameStr() < entity_y.GetNameStr(); 
		       	});
			
				std::list<dictionary::Entity>::iterator current_entity = list_entities.begin();
				std::list<dictionary::Entity>::iterator previus_entity = std::prev( current_entity, 1 );
				std::list<dictionary::Entity>::iterator next_entity = std::next( current_entity, 1 );
				
				while( current_entity != list_entities.end() ){
					
					if ( new_entity->GetNameStr().compare( current_entity->GetNameStr() ) == 0 ){

						if ( current_entity == list_entities.begin() ) { // Begin
							new_entity->SetNextEntityAddress( next_entity->GetEntityAddress() );	
							file.seekp( 0 );
							file.write( reinterpret_cast<const char*>(&file_size_), sizeof(long int) );
							file_header_ = file_size_;
							break;
						} else if ( current_entity != list_entities.begin() && next_entity != list_entities.end() ) { // midle
							new_entity->SetNextEntityAddress( previus_entity->GetEntityAddress() );
							file.seekp( previus_entity->GetEntityAddress() + 59 );
							file.write( reinterpret_cast<const char*>(&file_size_), sizeof(long int) );
							break;
						} else if ( next_entity == list_entities.end() ) { // last
							file.seekp( previus_entity->GetEntityAddress() + 59 );
							file.write( reinterpret_cast<const char*>(&file_size_), sizeof(long int) );
							break;
						}	
					}
					++current_entity;
					++previus_entity;
					++next_entity;
				}   
	       	}
       	} catch (const std::ios_base::failure & e) {
    			std::cout << std::endl << ":: Warning Exception: " << e.what() 
                  		  << std::endl << ":: Error code: " << e.code() 
                  		  << std::endl;
  			}
		file.close();
    }

    void DataDictionary::UpdateEntity(std::list<dictionary::Entity> list_entities, dictionary::Entity *entity){
       	std::fstream file( dir_ + name_ + ext_, std::ios::binary | std::ios::in | std::ios::out | std::ios::ate);
       	file.exceptions( file.failbit | file.badbit );
			try {
		       	file.seekg(0, std::ios::end);
		    	file_size_ = file.tellg();
		       	/* ::::: create a sort list  ::::: */
				long int  end_address = -1;
		        long int entity_address_min,entity_next_address_min;
		        int i = 0; // first position
				int it_position = i;
				int flag;
		        std::string min;
		        std::list<dictionary::Entity>::iterator it_current = list_entities.begin();	     								    
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
					std::list<dictionary::Entity>::iterator current = list_entities.begin();
					std::list<dictionary::Entity>::iterator previus = std::prev( current , 1 );
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
			} catch (const std::ios_base::failure & e) {
    			std::cout << std::endl << ":: Warning Exception: " << e.what() 
                  		  << std::endl << ":: Error code: " << e.code() 
                  		  << std::endl;
  			}
		file.close();
    }

    void DataDictionary::RemoveEntity(std::list<dictionary::Entity> list_entities, std::string remove_entity){
       	
       	long int end_address = -1;
       	std::fstream file( dir_ + name_ + ext_, std::ios::binary | std::ios::in | std::ios::out | std::ios::ate);
        file.exceptions( file.failbit | file.badbit );
			try {
		        if ( !list_entities.empty() ){
		        
		        	std::string first_entity( list_entities.front().GetName() );
				
				    // update Header when is remove first  
					if( remove_entity.compare(first_entity) ==  0 ){
						file_header_ = list_entities.front().GetNextEntityAddress();
						file.seekp( 0 );
						file.write( reinterpret_cast<const char*>(&file_header_), sizeof(long int) );
						file.seekp( list_entities.front().GetEntityAddress() + 59 );
						file.write( reinterpret_cast<const char*>(&end_address), sizeof(long int) );
					} else {
						std::list<dictionary::Entity>::iterator it_current = list_entities.begin();
						std::list<dictionary::Entity>::iterator it_previus = std::prev( it_current , 1 );
					    
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
						} // end while	
					}
				
					 
		        } 
		    } catch (const std::ios_base::failure & e) {
    			std::cout << std::endl << ":: Warning Exception: " << e.what() 
                          << std::endl << ":: Error code: " << e.code() 
                  		  << std::endl;
                std::cout << std::endl << ":: Fail file in:" 
    				  	  << std::endl << ":: failbit: " << file.fail() 
            		      << std::endl << ":: eofbit: " << file.eof()
            		      << std::endl << ":: badbit: " << file.bad();
  			}
		file.close();											
    }

    dictionary::Entity DataDictionary::SearchEntity(std::list<dictionary::Entity> list_entities, std::string name_entity){
    	
    	dictionary::Entity entity;
    	
    	for (std::list<dictionary::Entity>::iterator it = list_entities.begin(); it != list_entities.end(); it++){
    	
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

    std::list<dictionary::Entity> DataDictionary::ReadListEntities(){
    	
    	std::list<dictionary::Entity> list_entities;
       	std::fstream file( dir_ + name_ + ext_, std::ios::in | std::ios::out | std::ios::binary );
       	file.exceptions( file.failbit | file.badbit );
			try {
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
					dictionary::Entity entity;
					entity.SetName(str_name);
					entity.SetEntityAddress(entity_address);
				    entity.SetAttributeAddress(attribute_address);
				    entity.SetDataAddress(data_address);
				    entity.SetNextEntityAddress(next_entity_address);
					list_entities.push_back(entity);
				}
			} catch (const std::ios_base::failure & e) {
    			std::cout << std::endl << ":: Warning Exception: " << e.what() 
                          << std::endl << ":: Error code: " << e.code() 
                  		  << std::endl;
  			}
		
		file.close();	
       	
    	return list_entities;
    }

    void DataDictionary::AddAttribute(dictionary::Attribute attribute){
    	
    	std::fstream file( dir_ + name_ + ext_, std::ios::binary | std::ios::app);
	
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
		file.exceptions( file.failbit | file.badbit );
			try {        
				file.write( reinterpret_cast<const char*>(name), MAX_LENGTH_NAME_ATTRIBUTE_ );      // 35
				file.write( reinterpret_cast<const char*>(&data_type) , sizeof(char) );             // 1
				file.write( reinterpret_cast<const char*>(&length_data_type), sizeof(int) );        // 4
				file.write( reinterpret_cast<const char*>(&attribute_address), sizeof(long int) );  // 8 
				file.write( reinterpret_cast<const char*>(&type_index), sizeof(int) );              // 4
				file.write( reinterpret_cast<const char*>(&index_address), sizeof(long int) );      // 8
				file.write( reinterpret_cast<const char*>(&next_attribute_address), sizeof(long int) );	 
			} catch (const std::ios_base::failure & e) {
    			std::cout << std::endl << ":: Warning Exception: " << e.what() 
                          << std::endl << ":: Error code: " << e.code() 
                  		  << std::endl;
  			}
		file.close();
    }


    void DataDictionary::UpdateAttribute(std::list<dictionary::Attribute> list_attributes, dictionary::Attribute attribute){

       	std::fstream file( dir_ + name_ + ext_, std::ios::binary | std::ios::in | std::ios::out | std::ios::ate);
       	long int end_address = -1;
        long int attribute_address = attribute.GetAttributeAddress();
        
    	if ( !list_attributes.empty() ){
    		file.exceptions( file.failbit | file.badbit );
				try { 
		    	    file.seekp( list_attributes.back().GetAttributeAddress() + 35 + 1 + 4 + 8 + 4 + 8 );
					file.write( reinterpret_cast<const char*>(&attribute_address), sizeof(long int) );
				} catch (const std::ios_base::failure & e) {
    				std::cout << std::endl << ":: Warning Exception: " << e.what() 
                              << std::endl << ":: Error code: " << e.code() 
                  		      << std::endl;
  				}
    	}
	
		file.close();
    }

    std::list<dictionary::Attribute> DataDictionary::ReadListAttributes(dictionary::Entity entity){
    	
    	std::list<dictionary::Attribute> list_attributes;
       	std::fstream file( dir_ + name_ + ext_, std::ios::in | std::ios::out | std::ios::binary );
     	
		long int next = entity.GetAttributeAddress();
		char name[MAX_LENGTH_NAME_ATTRIBUTE_];
		char data_type;
		int length_data_type;
		long int attribute_address;
		int type_index;
		long int index_address;
		long int next_attribute_address;
			
		while( next != -1 ){
			file.exceptions( file.failbit | file.badbit );
				try {
					file.seekg( next );
					file.read( reinterpret_cast<char*>( name) , MAX_LENGTH_NAME_ENTTITY_ );
					file.read( reinterpret_cast<char*>(&data_type), sizeof(char) );
					file.read( reinterpret_cast<char*>(&length_data_type), sizeof(int) );
					file.read( reinterpret_cast<char*>(&attribute_address), sizeof(long int) );
					file.read( reinterpret_cast<char*>(&type_index), sizeof(int) );
					file.read( reinterpret_cast<char*>(&index_address), sizeof(long int) );
					file.read( reinterpret_cast<char*>(&next_attribute_address), sizeof(long int) );
				} catch (const std::ios_base::failure & e) {
    				std::cout << std::endl << ":: Warning Exception: " << e.what() 
                              << std::endl << ":: Error code: " << e.code() 
                  		      << std::endl;
  				}
			next = next_attribute_address;
			
			std::string str_name(name);
			dictionary::Attribute attribute;
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

    void DataDictionary::RemoveAttribute(dictionary::Entity current_entity, std::list<dictionary::Attribute> list_attributes, std::string remove_attribute){
       	
       	long int end_address = -1;
       	std::fstream file( dir_ + name_ + ext_, std::ios::binary | std::ios::in | std::ios::out | std::ios::ate);
        
        if ( !list_attributes.empty() ){
            
        	std::string first_attribute( list_attributes.front().GetName() );
			std::list<dictionary::Attribute>::iterator it_current = list_attributes.begin();
			std::list<dictionary::Attribute>::iterator it_previus = std::prev( it_current , 1 );
			std::list<dictionary::Attribute>::iterator it_next = std::next( it_current , 1 );
		    
			while ( it_current != list_attributes.end() ){
		
				std::string it_current_attribute( it_current->GetName() );
				file.exceptions( file.failbit | file.badbit );
					try {

						if( remove_attribute.compare(first_attribute) ==  0 ){
							file.seekp( current_entity.GetEntityAddress() + 35 + 8 );
							long int next_attr = it_next->GetAttributeAddress();
							file.write( reinterpret_cast<const char*>(&next_attr), sizeof(long int) );
							file.seekp( it_current->GetAttributeAddress() + 35 + 1 + 4 + 8 + 4 + 8 );
							file.write( reinterpret_cast<const char*>(&end_address), sizeof(long int) );
							break;		
						}	        
						
						if ( remove_attribute.compare(it_current_attribute) == 0 ){
							
							file.seekp( it_previus->GetAttributeAddress() + 35 + 1 + 4 + 8 + 4 + 8  );
							long int new_next_attribute_address = it_current->GetNextAttributeAddress();
							file.write( reinterpret_cast<const char*>(&new_next_attribute_address), sizeof(long int) );
							
							file.seekp( it_current->GetAttributeAddress() + 35 + 1 + 4 + 8 + 4 + 8 );
							file.write( reinterpret_cast<const char*>(&end_address), sizeof(long int) );		 
							break;
						
						}

				    } catch (const std::ios_base::failure & e) {
    					std::cout << std::endl << ":: Warning Exception: " << e.what() 
                                  << std::endl << ":: Error code: " << e.code() 
                  		          << std::endl;
                  		std::cout << std::endl << ":: Fail file in:" 
    				  	  		  << std::endl << ":: failbit: " << file.fail() 
            		      		  << std::endl << ":: eofbit: " << file.eof()
            		              << std::endl << ":: badbit: " << file.bad();
  				    }
				it_current++;
				it_previus++;
				it_next++;
			}
        } 
		file.close();											
    }

    dictionary::Attribute DataDictionary::SearchAttribute(std::list<dictionary::Attribute> list_attributes, std::string name_attribute){
    	
    	dictionary::Attribute attribute;
    	
    	for (std::list<dictionary::Attribute>::iterator it = list_attributes.begin(); it != list_attributes.end(); it++){
    	
    		std::string current_name( it->GetName() );
    	
    		if ( name_attribute.compare( current_name ) == 0 ){
    			attribute.SetName( current_name );
    		    attribute.SetDataType( it->GetDataType() );
    			attribute.SetLengthDataType( it->GetLengthDataType() );
    			attribute.SetAttributeAddress( it->GetAttributeAddress() );
    			attribute.SetTypeIndex( it->GetTypeIndex() );
    			attribute.SetIndexAddress( it->GetIndexAddress() );
    			attribute.SetNextAttributeAddress( it->GetNextAttributeAddress() );	
    		}
    	
    	}

    	return attribute;
    }

    long int DataDictionary::LengthStartToSearchKey(std::list<dictionary::Attribute> list_attributes){
    	
    	long int length = sizeof(long int); // first address of data file
    	
    	for (std::list<dictionary::Attribute>::iterator it = list_attributes.begin(); it != list_attributes.end(); it++){
    	    
    	    if ( it->GetTypeIndex() != 3 ){
    	    	if ( it->GetDataType() == 'i' )
    	    		length += sizeof(int);
    	    	else if ( it->GetDataType() == 'c' )
    	    		length += it->GetLengthDataType();
    	    } else
    	     	break;

    	
    	}

    	return length;
    }

}  // end namespace repository