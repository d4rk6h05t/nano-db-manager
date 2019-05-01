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

    void DataFile::AppendData(std::list<dictionary::Attribute> list_attributes, std::list<std::string> & list_data){
    	
    	std::list<dictionary::Attribute>::iterator it = list_attributes.begin();
    	std::fstream file( dir_ + name_ + ext_, std::ios::binary | std::ios::in | std::ios::out | std::ios::ate);
		  file.exceptions( file.failbit | file.badbit );
			
			try {
		       	
		      file.seekg(0, std::ios::end);
		    	long int file_size = file.tellg();
		    	long int end_address = -1;
          long int length_struct_register = sizeof(long int) * 2;
				  bool disable_index = true;
          std::string search_key;
          std::string current_data_key;
          if(list_data.empty())
              file_header_ = 0;
          file.seekp(file_size);
				  
          file.write( reinterpret_cast<const char*>(&file_size), sizeof(long int)  );
				
				while ( it != list_attributes.end() ) {
			        std::cout <<":: " << it->GetName() << " : ";
                    
                    if ( it->GetTypeIndex() == 3 ){
                    	disable_index = false;
                    	std::string search_key( it->GetName() );
                    }
			        
			        if ( it->GetDataType() == 'c' ){
			        	length_struct_register = length_struct_register + it->GetLengthDataType();
						    char str[ it->GetLengthDataType() ];
						    std::cin >> str;
                    
	              if( it->GetTypeIndex() == 3 ){
							    std::string data(str);
							    current_data_key = data;
							    list_data.push_back(data); 
						    }

						file.write( reinterpret_cast<const char*>(&str),  it->GetLengthDataType() );
					} else if ( it->GetDataType() == 'i' ){
						length_struct_register = length_struct_register + sizeof(int);
						int  x;
						std::cin >> x;
                        
            if ( it->GetTypeIndex() == 3 ){
						
            	std::string data_int = std::to_string(x);
							current_data_key = data_int;
							list_data.push_back(data_int); 
						
            } else if ( it->GetTypeIndex() == 1 ){
            
              std::string attr_active( it->GetName() );
              std::list< std::pair< int, long int> > block = dictionary::IndexFile::ReadBlock( attr_active, 0 );
              dictionary::IndexFile::AddLineToBlock(attr_active, 0, block, x, file_size);
            
            }

						file.write( reinterpret_cast<const char*>(&x), sizeof(int) );
					}
			       	it++;
			    }
			    
			    file.write( reinterpret_cast<const char*>(&end_address), sizeof(long int) ); // e n d   w r i t e   f i r s t   p a r t

			    // : : : : :   R e w ri t e      f o r     u p d a t e    f i l e  : : : : : 
                 
          file.seekg(0, std::ios::end);
		    	file_size = file.tellg(); 
	        
          if ( disable_index && (file_size >  length_struct_register) ) {
              
            file_header_ = 0;   
				    long int previus_next_address = file_size - ( length_struct_register  + sizeof(long int) ); 
				    long int next_address = file_size - length_struct_register;	    
				    file.seekp(previus_next_address);
				    file.write( reinterpret_cast<const char*>(&next_address), sizeof(long int) );
				    		   	
				} else if ( disable_index == false && (file_size >  length_struct_register) ) {
                   
            std::list<std::string>::iterator current_data = list_data.begin();       
                    
            std::string prev;
            std::string current;  
            std::string next;
                    
            long int position_update = 0;

            long int prev_addr;
            long int curr_addr;
            long int next_addr;

            long int prev_addr_next;
            long int curr_addr_next;
            long int next_addr_next;
                    
            long int prev_position_update = -1;
            long int curr_position_update = -1;
            long int next_position_update = -1;

                    if ( list_data.size() == 2 ){
                        
                        current = *current_data;
                        ++current_data;
                        next = *current_data;

                        if ( current.compare(next) > 0 ){
                        
                          file_header_ = file_size - length_struct_register;
                        	position_update = file_size -  sizeof(long int) ;
                        	next_addr = 0;
                        	file.seekp(position_update);
				        	        file.write( reinterpret_cast<const char*>(&next_addr), sizeof(long int) );

                        } else if ( current.compare(next) <= 0 ) {
                        	
                        	file_header_ = 0;
                        	position_update = file_size - ( length_struct_register  + sizeof(long int) ); 
				        	        next_addr = file_size - length_struct_register;	    
				        	        file.seekp(position_update);
				        	        file.write( reinterpret_cast<const char*>(&next_addr), sizeof(long int) );
	
                        } 
                        
                    } else if ( list_data.size() > 2 ){
                        
                    	list_data.sort();  
                      
                      std::list<std::string>::iterator i_ = list_data.begin();
                      std::list<std::string>::iterator i_prev = std::prev( i_ , 1 );
                    	std::list<std::string>::iterator i_next = std::next( i_ , 1 );
                        
                      while( i_ != list_data.end() ){
                        		
                        if ( current_data_key == *i_ ){
                    	        current = *i_;
                              i_  !=  list_data.begin() ? prev = *i_prev : prev = ""; 
                              i_next != list_data.end() ? next = *i_next : next = "";
                    		}

                        i_++;
                        i_prev++;
                        i_next++;
                      }

                        
      long int register_address;
    	long int next_register_address;  
    	long int next_row;
    	std::string string_read;          
                    	
if ( prev != "" ){ 
long int save_addr_prev, save_next_addr_prev;
next_row = file_header_;
while ( next_row != -1 ) {
	std::list<dictionary::Attribute>::iterator itr_prev = list_attributes.begin();
	file.exceptions( file.failbit | file.badbit );
		try {
			file.seekg( next_row );
			file.read( reinterpret_cast<char*>(&register_address) , sizeof(long int) );
			while ( itr_prev != list_attributes.end() ) {
			    if ( itr_prev->GetDataType() == 'c' ){
					char str[ itr_prev->GetLengthDataType() ];
					file.read( reinterpret_cast<char*>(str) , itr_prev->GetLengthDataType() );
					if( itr_prev->GetTypeIndex() == 3 )
						string_read = str;		
				} else if ( itr_prev->GetDataType() == 'i' ){
					int  x;
					file.read( reinterpret_cast<char*>(&x), sizeof( int ) );
					if( itr_prev->GetTypeIndex() == 3 )
						string_read = std::to_string(x);
				}
			    itr_prev++;
			}
			file.read( reinterpret_cast<char*>(&next_register_address) , sizeof(long int) );
		    next_row = next_register_address; 
		    if( prev.compare(string_read) == 0 ){
            save_addr_prev = register_address;
            save_next_addr_prev = next_register_address;
        }       
		    if ( next_register_address == -1 ) 
          break;

        } catch (const std::ios_base::failure & e) {
    		std::cout << std::endl << "::FLAG Y :: Warning Exception: " << e.what() << std::endl << ":: Error code: " << e.code() << std::endl;
    		std::cout << std::endl << ":: Fail file in:" 
    				  << std::endl << ":: failbit: " << file.fail() 
            		  << std::endl << ":: eofbit: " << file.eof()
            		  << std::endl << ":: badbit: " << file.bad();
  		}
}

prev_addr = save_addr_prev;
prev_addr_next = save_next_addr_prev;
prev_position_update = prev_addr + (length_struct_register - sizeof(long int));

} // end if prev !=""

if ( current != "" ){            
    curr_addr = file_size - length_struct_register;
    curr_addr_next = -1;
} // end if current

if ( next != "" ){
next_row = file_header_;
while ( next_row != -1 ) {
	std::list<dictionary::Attribute>::iterator itr_next = list_attributes.begin();
	file.exceptions( file.failbit | file.badbit );
		try {
			file.seekg( next_row );
			file.read( reinterpret_cast<char*>(&register_address) , sizeof(long int) );
			next_addr = register_address;
			while ( itr_next != list_attributes.end() ) {
			    if ( itr_next->GetDataType() == 'c' ){
					char str2[ itr_next->GetLengthDataType() ];
					file.read( reinterpret_cast<char*>(str2) , itr_next->GetLengthDataType() );
					if( itr_next->GetTypeIndex() == 3 )
						string_read = str2;		
				} else if ( itr_next->GetDataType() == 'i' ){
					int  x2;
					file.read( reinterpret_cast<char*>(&x2), sizeof( int ) );
					if( itr_next->GetTypeIndex() == 3 )
						string_read = std::to_string(x2);
				}	
			    itr_next++;
			}
			file.read( reinterpret_cast<char*>(&next_register_address) , sizeof(long int) );
		    next_row = next_register_address;       
		    if( next.compare(string_read) == 0 )
          break;
		    if ( next_register_address == -1 ) 
		    	break; 
        } catch (const std::ios_base::failure & e) {
    		std::cout << std::endl << "::FLAG Z :: Warning Exception: " << e.what() << std::endl << ":: Error code: " << e.code() << std::endl;
    		std::cout << std::endl << ":: Fail file in:" 
    				  << std::endl << ":: failbit: " << file.fail() 
            		  << std::endl << ":: eofbit: " << file.eof()
            		  << std::endl << ":: badbit: " << file.bad();
  		}
} // end while next_row != -1

} // end if next

	            	// EXIST PREV &&  NEXT (MIDDLE) 
	            	if ( prev != "" && next != "" ){
	            		 
	            		file.seekp( curr_addr + (length_struct_register - sizeof(long int)) );
	            		file.write( reinterpret_cast<const char*>(&next_addr), sizeof(long int) );
	            		file.seekp( prev_addr + (length_struct_register - sizeof(long int)) );
	            		file.write( reinterpret_cast<const char*>(&curr_addr), sizeof(long int) );
	            	
	            	// EXIST PREV &&  DONT EXIST NEXT (LAST)
	            	} else if (prev != "" && next == ""){
	            	
	            		file.seekp( prev_position_update );
	            		file.write( reinterpret_cast<const char*>(&curr_addr), sizeof(long int) );
	            	
	            	// DONT EXIST PREV && EXIST NEXT (FIRST)
	            	} else if ( prev == "" && next != "" ) {

	            	    file_header_ = curr_addr;
	            	    file.seekp(curr_addr + (length_struct_register - sizeof(long int)) );
	            	    file.write( reinterpret_cast<const char*>(&next_addr), sizeof(long int) );
	            	
                }

            } // end else if case 3
                    
				} // end else if index 3

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
        long int next = file_header_;
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

    std::list<long int> DataFile::GetAddressBySearchKey(const std::string & name,const std::string & search_key, long int file_header, std::list<dictionary::Attribute> list_attributes){
        std::list<long int> list_address;
        long int register_address;
        long int next_register_address;
        long int next = file_header;
        std::string current_data;
        std::string dir = "tmp/";
        std::string ext = ".dat";
        std::fstream file( dir + name + ext, std::ios::binary | std::ios::in | std::ios::out );
        
        while ( next != -1 ) {
        
            std::list<dictionary::Attribute>::iterator it = list_attributes.begin();
            file.exceptions( file.failbit | file.badbit );
            
            try {
            
              file.seekg( next );
              file.read( reinterpret_cast<char*>(&register_address) , sizeof(long int) );
                  
                  while ( it != list_attributes.end() ) {
                    if ( it->GetTypeIndex() == 3 ) {

                      if ( it->GetDataType() == 'c' ){
                        char str[ it->GetLengthDataType() ];
                        file.read( reinterpret_cast<char*>(str) , it->GetLengthDataType() );
                        current_data = str; 
                      } else if ( it->GetDataType() == 'i' ){
                        int  x;
                        file.read( reinterpret_cast<char*>(&x), sizeof( int ) );
                        current_data = std::to_string(x);
                      } // end else if  
                      if ( search_key.compare( current_data ) == 0)
                        list_address.push_back(register_address);
                    } // end if type index
                    it++;
                  } // end while
                  file.read( reinterpret_cast<char*>(&next_register_address) , sizeof(long int) );
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
      return list_address;
    }


}  // end namespace archive