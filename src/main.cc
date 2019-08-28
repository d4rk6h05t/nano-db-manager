// Includes
#include <iostream>
#include <string>
#include <list>
#include <iterator>

#include <algorithm>
#include <functional>
// personal includes
#include "entity.h"
#include "attribute.h"
#include "data_dictionary.h"
#include "data_file.h"
#include "file.h"
#include "primary_index.h"
#include "secondary_index.h"
#include "static_hashing.h"
#include "multilist.h"
#include "view.h"

// namespaces to use
using namespace std; 
using namespace dictionary;
using namespace repository;
using namespace ui;

int main( int argc, char* argv[] ){ 
	
	View view;
    long int file_header = -1;
    long int entity_address_min, entity_next_address_min, list_next_address;
    int option, option_file, option_dictionary, option_entity, option_attribute;
    string file_name, new_entity, remove_entity, attribute_name, min, current_entity_name;
    DataDictionary data_dictionary;
    DataFile data_file;
    Entity current_entity;
	list<Attribute> list_attributes;
    data_dictionary.CreateDirectory();
    do {    	
		view.ShowTitle("Michani M. De La Calleja E.", "V1.0.0");
		view.ShowMainMenu();
	    view.ShowMessage("\n\t\t Select a option >_");
	    cin >> option;

	    switch (option){
	    	case 1: // File Menu
	    		do {
	    			view.Clear();
		    		view.ShowFileMenu();
		    		view.ShowMessage("\n\t\t Select a option >_");
		    		cin >> option_file;
	    			switch (option_file){
				    	case 1: { // New file data dictionari [DB] 

				    		view.ShowMessage("\n\t\tfile name: ");
				    		cin >> file_name;
				    		if ( file_name !="" ){
				    			data_dictionary.SetName( file_name );
				    			data_dictionary.CreateFile();
				    			data_dictionary.UpdateHeader();
				    		}
				    		break;
				    	}
				    	case 2: { // Open file data dictionary [DB]
				    		view.ShowMessage("\n\t\tfile name: ");
				    		cin >> file_name;
				    			if ( file_name !="" )
				    				data_dictionary.SetName( file_name );
				    		break;
				    	}
				    	case 3: {// Delete file data dictionary [DB]
				    		view.ShowMessage("\n\t\tfile name: ");
				    		cin >> file_name;
				    			if ( file_name !="" )
				    				view.ShowMessage("Deleted file with name ==> " + file_name);
				    		break;
				    	}
				    }
	    		} while(option_file < 4);
	    		if (option_file > 3 ) view.Clear();
	    			break;
	    	case 2:  // Dictionary Menu 
	    		do {
	    			view.Clear();
		    		view.ShowDictionaryMenu();
		    		view.ShowMessage("\n\t\t Select an option >_");
		    		cin >> option_dictionary;
	    			switch (option_dictionary){
				    	case 1: 
				    		do {       
				    			view.Clear();
					    		view.ShowStatusBar(data_dictionary.GetName(), data_dictionary.GetFileHeader(), data_dictionary.GetFileSize() );
					    		view.ShowEntityMenu();
					    		view.ShowMessage("\n\t\t Select an option >_");
					    		cin >> option_entity;
				    			switch (option_entity){
							    	case 1: // New entity
							    		view.ShowMessage("\n\t\t===> Add Entity ::: Enter a new entity name: ");
							    		cin >> new_entity;
							    		if ( new_entity !="" ){
										    Entity entity(new_entity);
										    entity.SetEntityAddress( data_dictionary.GetFileSize() ); 
									        //data_dictionary.UpdateEntity2( data_dictionary.ReadListEntities(), &entity);
									        data_dictionary.UpdateEntity( data_dictionary.ReadListEntities(), &entity); 								        
									        data_dictionary.AddEntity( entity );
										}
										break;
							    	case 2: // Update Entity
							    		view.ShowMessage("\n\t\t===> Update Entity ::: First, Select a entity for update: ");
							    		cin >> new_entity;
							    		if ( new_entity !="" ){
							    			Entity entity_selected = data_dictionary.SearchEntity( data_dictionary.ReadListEntities(), new_entity);
							    			if(entity_selected.GetEntityAddress() != -1 ){
							    				string new_name;
								    			view.ShowMessage("\n\t\t===> Change name entity ::: Enter new entity name: ");
								    			cin >> new_name;
								    			if ( new_name !="" ){
								    				data_dictionary.UpdateName( entity_selected.GetEntityAddress(), new_name );
								    			}	
							    			} else {
							    				view.ShowMessage("===> I'm sorry not found entity ");
							    			}		
										} // first end if != ""
							    		break;
							    	case 3: // Remove entity
							    		view.ShowMessage("\n\t\t===> Remove Entity ::: Enter entity name: ");
							    		cin >> remove_entity;
							    		if ( remove_entity !="" ){
							    			data_dictionary.RemoveEntity(data_dictionary.ReadListEntities() ,remove_entity);
							    		}	
							    		break;
							    	case 4: // select Entity
							    		view.ShowMessage("===> Select Entity");
							    		break;
							    	case 5:// Show Entities
							    		view.ShowListEntities( data_dictionary.ReadListEntities() );
							    		break;
							    }
				    		} while(option_entity < 6);

				    		if (option_entity > 5 ) view.Clear();
				    		break;
						case 2: 

							string attr_name;
							char attr_data_type;
							int attr_length;
							int attr_index;
										
							view.ShowStatusBar(data_dictionary.GetName(), data_dictionary.GetFileHeader(), data_dictionary.GetFileSize() );
							
				    		view.ShowMessage("\n\t\t ::: select an entity to work with :");
				    		cin >> current_entity_name;

				    			if ( current_entity_name !="" ){
				    				current_entity = data_dictionary.SearchEntity( data_dictionary.ReadListEntities(), current_entity_name);
				    				if ( current_entity.GetEntityAddress() != -1 ){

					    				do { 
					    					view.Clear();
					    					string str_entity_selected(current_entity.GetName());

					    					view.ShowMessage("\n\t\t:: Entity selected: " +  str_entity_selected );
					    					view.ShowStatusBar(data_dictionary.GetName(), data_dictionary.GetFileHeader(), data_dictionary.GetFileSize() );
					    					view.ShowAttributeMenu();
								    		view.ShowMessage("\n\t\tSelect an option >_");
								    		cin >> option_attribute;
							    			switch (option_attribute){
										    	case 1: { // create new attribute 
										    		view.ShowMessage("\n\t\t===> Add Attribute \n");
										    		view.ShowMessage("\t\t:: Name: ");
										    		cin >> attr_name;
										    		if ( attr_name != "" ){
										    			view.ShowMessage("\t\t:: Data Type: ");
											    		cin >> attr_data_type;
											    		if ( attr_data_type != '\0'  ){
											    			view.ShowMessage("\t\t:: Length: ");
												    		cin >> attr_length;
												    		if ( attr_length > 0 ){
												    			view.ShowMessage("\t\t:: Type Index: ");
													    		cin >> attr_index;
													    		if ( attr_index > -1 ){
													    			Attribute attribute( attr_name, attr_data_type, attr_length, attr_index );
																    attribute.SetAttributeAddress( data_dictionary.GetFileSize() );  
															        if ( current_entity.GetAttributeAddress() == -1){
															        	data_dictionary.UpdateAddress( (current_entity.GetEntityAddress() + 35 + 8) , data_dictionary.GetFileSize() );
															        } 
															        data_dictionary.UpdateAttribute( data_dictionary.ReadListAttributes( current_entity ), attribute); 								        
															        data_dictionary.AddAttribute( attribute );
															        current_entity = data_dictionary.SearchEntity( data_dictionary.ReadListEntities(), current_entity_name);			
													    		} // end if attr_index > -1	
												    		} // end if attr_length > 0	
											    		} // end if attr_data_type != '\0' 
													} // end id attr_name != "" 
										    		break;
										    	} // end case 1 
										    	case 2: { // Update Attribute
										    		view.ShowMessage("\n\t\t===> Update Attribute");
										    		view.ShowStatusBar(data_dictionary.GetName(), data_dictionary.GetFileHeader(), data_dictionary.GetFileSize() );
										    		view.ShowMessage("\n\t\t:: Select a attribute : ");
										    		string current_attr_name;
										    		cin >> current_attr_name;
										    		if ( current_attr_name != "" ){
										    			Attribute attr = data_dictionary.SearchAttribute( data_dictionary.ReadListAttributes( current_entity ) ,current_attr_name );
										    				view.ShowMessage("\t\t:: Name: ");
												    		cin >> attr_name;
												    		if ( attr_name != "" ){
												    			data_dictionary.UpdateName( attr.GetAttributeAddress() ,attr_name);
												    			view.ShowMessage("\t\t:: Data Type: ");
													    		cin >> attr_data_type;
													    		if ( attr_data_type != '\0'  ){
													    			data_dictionary.UpdateChar( attr.GetAttributeAddress() + 35 ,attr_data_type);
													    			view.ShowMessage("\t\t:: Length: ");
														    		cin >> attr_length;
														    		if ( attr_length > 0 ){
														    			data_dictionary.UpdateInt( attr.GetAttributeAddress() + 35 + 1 ,attr_length);
														    			view.ShowMessage("\t\t:: Type Index: ");
															    		cin >> attr_index;
															    		if ( attr_index > -1 ){
															    			data_dictionary.UpdateInt( attr.GetAttributeAddress() + 35 + 1 + 4 + 8 ,attr_index);
															    		}	
														    		} // end if attr_length > 0	
													    		} // end if attra_data_type
															} // end if attr_name != ""
										    		} // end if attr_current_name != ""
										    		break;
										    	} // end caase 2
										    	case 3: { // Delete Attribute
										    		view.ShowStatusBar(data_dictionary.GetName(), data_dictionary.GetFileHeader(), data_dictionary.GetFileSize() );
										    		view.ShowMessage("\n\t\t===> Delete Attribute \t\t:: Attribute Name:");
										    		cin >> attr_name;
										    		if (attr_name != "")
										    			data_dictionary.RemoveAttribute(current_entity, data_dictionary.ReadListAttributes(current_entity), attr_name);
										    		break;
										    	}
										    	case 4:
										    		view.ShowStatusBar(data_dictionary.GetName(), data_dictionary.GetFileHeader(), data_dictionary.GetFileSize() ); 
										    		view.ShowMessage("\n\t\t===>Select Attribute"); 
										    		break;
										    	case 5: { // Show entities
										    		view.ShowStatusBar(data_dictionary.GetName(), data_dictionary.GetFileHeader(), data_dictionary.GetFileSize() );
										    		current_entity = data_dictionary.SearchEntity( data_dictionary.ReadListEntities(), current_entity_name);
										    		view.ShowListAttributes( data_dictionary.ReadListAttributes(current_entity) );
										    		break;
										    	}
										    	case 6: break;
										    } // end switch 
										} while(option_attribute < 6);
					    					if (option_attribute > 5 ) view.Clear();
					    					break;		
				    				} 
				    			}
				    }
	    		} while(option_dictionary < 3);
	    		if (option_dictionary > 2 ) view.Clear();
	    		break;
	    		case 3:  // Data File menu
				view.ShowMessage("\n\t\t ::: select an entity to work with :");
				cin >> current_entity_name;
				if ( current_entity_name !="" ){
					current_entity = data_dictionary.SearchEntity( data_dictionary.ReadListEntities(), current_entity_name);
					list_attributes = data_dictionary.ReadListAttributes(current_entity);
				    data_file.SetName( current_entity_name );
				    data_file.SetFileHeader( current_entity.GetDataAddress() );
				    
				    if ( current_entity.GetDataAddress() == -1 ){ 	
				    	data_file.CreateFile();
				    	list<Attribute> list_attributes = data_dictionary.ReadListAttributes( current_entity );
						for( list<Attribute>::iterator i = list_attributes.begin(); i != list_attributes.end(); i++ ){
							
							string attr_name( i->GetName() );

							if ( i->GetTypeIndex() == 1  ){
								string name_primary_index = current_entity_name + "_" + attr_name;
								PrimaryIndex primary_index_file( name_primary_index );
								primary_index_file.CreateFile();
								primary_index_file.CreateBlock( 0 );
								list< pair< int, long int> > block_int = PrimaryIndex::ReadBlock(name_primary_index, 0 );
								if ( i->GetIndexAddress() == -1 )
									data_dictionary.UpdateAddress( i->GetAttributeAddress() + 52, 0 );
							} 	else if ( i->GetTypeIndex() == 2 ) {
								string name_secondary_index = current_entity_name + "_" + attr_name;
								SecondaryIndex secondary_index_file( name_secondary_index );
								secondary_index_file.CreateFile();
								secondary_index_file.CreateBlock( 0 );
								if ( i->GetIndexAddress() == -1 )
									data_dictionary.UpdateAddress( i->GetAttributeAddress() + 52, 0 );
							}   else if ( i->GetTypeIndex() == 4 ) {
								string name_static_hashing = current_entity_name + "_" + attr_name;
								StaticHashing static_hashing_file( name_static_hashing );
								static_hashing_file.CreateFile();
								static_hashing_file.InitAddressBucket();
								if ( i->GetIndexAddress() == -1 )
									data_dictionary.UpdateAddress( i->GetAttributeAddress() + 52, ( sizeof(long int) * ( NO_BUCKETS_SH_ + 1 ) ) );
							} else if ( i->GetTypeIndex() == 5 ) {
								string name_multilist = current_entity_name + "_" + attr_name;
								Multilist multilist_file( name_multilist );
								multilist_file.CreateFile();
								multilist_file.CreateBlock( 0 );
								if ( i->GetIndexAddress() == -1 )
									data_dictionary.UpdateAddress( i->GetAttributeAddress() + 52, 0 );
							}	
						}
				    } 

				list<string> list_data;
	    		do {
	    			view.Clear();
	    			view.ShowStatusBar(data_file.GetName(),  data_file.GetFileHeader() , data_file.GetFileSize() );
		    		view.ShowDataFileMenu();
		    		view.ShowMessage("\n\t\t Select a option >_");
		    		cin >> option_file;
	    			switch (option_file){
				    	case 1: { // Add new Register
				    		view.ShowStatusBar(data_file.GetName(),  data_file.GetFileHeader() , data_file.GetFileSize() );
				    	
				    		string current_entity_name( current_entity.GetName() );
				    		data_dictionary.UpdateAddress( current_entity.GetEntityAddress() + 35 + 8 + 8 , data_file.GetFileHeader() );
				    		string name_multilist;
				    		list<string> list_name_multilist;
				    		for( list<Attribute>::iterator j = list_attributes.begin(); j != list_attributes.end(); j++ ){
				    			if ( j->GetTypeIndex() == 5  ){
				    				string tmp_name_multilist( j->GetName() );
				    				list_name_multilist.push_back(tmp_name_multilist);
				    				name_multilist = current_entity_name + "_" + tmp_name_multilist;
				    			}
				    		}
				    		
				    		
							long int length_struct_log = data_file.GetLengthStructLog( list_attributes );
				    		long int header_data_file = data_file.AppendData(list_attributes,list_data,current_entity_name, length_struct_log);
				    		
				    		if ( header_data_file != -1)
				    			data_dictionary.UpdateAddress( current_entity.GetEntityAddress() + 35 + 8 + 8 , header_data_file);
				    		break;
				    	} 
				    	case 2: {// Show primary Index
				    		view.ShowStatusBar(data_file.GetName(), data_file.GetFileHeader(), data_file.GetFileSize() );
				    		cout << endl << "\t\t Data \t Data Address";
				    		for( list<Attribute>::iterator j = list_attributes.begin(); j != list_attributes.end(); j++ ){
								if ( j->GetTypeIndex() == 1  ){
									string attr_name_show( j->GetName() );
									string name_primary_index_i = current_entity_name + "_" + attr_name_show;
									
									list< pair< int, long int> > block = PrimaryIndex::ReadBlock(name_primary_index_i, 0 );
                                    if ( !block.empty() )
										for( list< pair< int, long int> >::iterator k = block.begin(); k != block.end(); k++ )
											cout << endl << "\t\t "<< k->first << " \t " << k->second;
									else
										cout << endl << " ::  block empty ";;
								}  
							}
							cout << endl;
				    		break;
				    	}
				    	case 3 : { // Show Secondary Index
                            view.ShowStatusBar(data_file.GetName(), data_file.GetFileHeader(), data_file.GetFileSize() );
				    		cout << endl << "\t\tData \t Data Address \t\t\t Next Block Secondary";
				    		for( list<Attribute>::iterator j = list_attributes.begin(); j != list_attributes.end(); j++ ){
								if ( j->GetTypeIndex() == 2  ){
									string attr_name_show( j->GetName() );
									string name_secondary_index_i = current_entity_name + "_" + attr_name_show;
									
									list< pair< int, vector<long int>> > block_x = SecondaryIndex::ReadBlock(name_secondary_index_i, 0 );
                                    
                                    if ( !block_x.empty() )
										for( list< pair< int, vector<long int>> >::iterator m = block_x.begin(); m != block_x.end(); m++ ){
											cout << endl << "\t\t " << m->first;
											for( vector<long int>::iterator n = m->second.begin(); n != m->second.end(); n++ )
												cout << " \t " << *n;
										}
									else
										cout << endl << " ::  block empty ";;
								}  
							}
							cout << endl;
				    		break;	
						}
						case 4 : {// Show Static Hashing
				    		view.ShowStatusBar(data_file.GetName(), data_file.GetFileHeader(), data_file.GetFileSize() );
				    		 
				    		for( list<Attribute>::iterator j = list_attributes.begin(); j != list_attributes.end(); j++ ){
								if ( j->GetTypeIndex() == 4  ){
									
									string attr_name_sh( j->GetName() );
									string name_sh = current_entity_name + "_" + attr_name_sh;
									vector<long int> bucket_addrs = StaticHashing::GetBucketsAddress(name_sh);
                            		vector<long int>::iterator itr_bck = bucket_addrs.begin();
                            		int count_hash = 0;
                            		while ( itr_bck != bucket_addrs.end() ) {
									
										if ( *itr_bck != -1 ){ 
											cout << endl << "\t\t :: Hash [ " << count_hash << " ]";
											cout << endl << "\t\t Data \t Data Address";
											list< pair< int, long int> > bucket = StaticHashing::ReadBlock(name_sh, *itr_bck );
											if ( !bucket.empty() )
												for( list< pair< int, long int> >::iterator k = bucket.begin(); k != bucket.end(); k++ )
													cout << endl << "\t\t "<< k->first << " \t " << k->second;
											else
												cout << endl << " ::  block empty ";			
										
										}
										if ( count_hash == 0 || count_hash == 1 || count_hash == 2 || count_hash == 4 || count_hash == 6|| count_hash ==  7)
											cout << "\t\t";
										else if ( count_hash == 3 || count_hash == 5 )
										 	cout << endl; 
									itr_bck++;
									count_hash++;
									}

								}  
							}
							cout << endl;
				    		break;
				    	}
						case 5 : { // Show Multilist
							view.ShowStatusBar(data_file.GetName(), data_file.GetFileHeader(), data_file.GetFileSize() );
				    		
				    		for( list<Attribute>::iterator l = list_attributes.begin(); l != list_attributes.end(); l++ ){
								if ( l->GetTypeIndex() == 5  ){
									cout << "\t\t:: [ " << l->GetName() << " ] ";
									cout << endl << "\t\t Data \t Data Address";
									string attr_name_m( l->GetName() );
									string name_multilist = current_entity_name + "_" + attr_name_m;
									list< pair< int, long int> > block_l = Multilist::ReadBlock(name_multilist, 0 );
                                    if ( !block_l.empty() )
										for( list< pair< int, long int> >::iterator m = block_l.begin(); m != block_l.end(); m++ )
											cout << endl << "\t\t "<< m->first << " \t " << m->second;
									else
										cout << endl << " ::  block empty ";;
								}  
							cout << endl;
							}
							cout << endl;
				    		break;
				    		break;
						}
						case 6 : { // Show Data File
				    		view.ShowStatusBar(data_file.GetName(), data_file.GetFileHeader(), data_file.GetFileSize() );
							Entity current_entity_new = data_dictionary.SearchEntity( data_dictionary.ReadListEntities(), current_entity_name);
							data_file.ReadRegister( data_dictionary.ReadListAttributes(current_entity_new) );
							break;
						}
						case 7 : { // Update a register
				    		
				    		view.ShowStatusBar(data_file.GetName(), data_file.GetFileHeader(), data_file.GetFileSize() );
				    		
				    		int data_search;
				    		int primary_index_active = 0;
				    		int secondary_index_active = 0;
				    		int static_hashing_active = 0;

				    		string name_primary_index;
				    		string name_secondary_index;
				    		string name_static_hashing;

							for( list<Attribute>::iterator j = list_attributes.begin(); j != list_attributes.end(); j++ ){
								if ( j->GetTypeIndex() == 1  ){
									primary_index_active = 1;
									string attr_name_key( j->GetName() );
									name_primary_index = current_entity_name + "_" + attr_name_key;
									view.ShowMessage("\n\t\t ::: select of " + attr_name_key + " for remove : ");
									cin >> data_search;
								} else if ( j->GetTypeIndex() == 2) {
									secondary_index_active = 1;
									string attr_name_key( j->GetName() );
									name_secondary_index = current_entity_name + "_" + attr_name_key;
								} else if ( j->GetTypeIndex() == 4 ) {
									static_hashing_active = 1;
									string attr_name_sh( j->GetName() );
									name_static_hashing = current_entity_name + "_" + attr_name_sh;
								}

							}
                          
							 
							long int length_struct_log = data_file.GetLengthStructLog( list_attributes );
                            long int addr_select = data_file.GetAddress(list_attributes, length_struct_log, data_search);
                            long int addr_select_point_me = data_file.GetAddress(list_attributes, length_struct_log, addr_select);
                            long int next_addr_select = data_file.GetNextAddress(list_attributes, length_struct_log, data_search);
                            
                            if ( primary_index_active == 1 ) {
                            
                            	list<pair< int, long int>> bucket_primary = PrimaryIndex::ReadBlock(name_primary_index,0);	
								PrimaryIndex::RemoveDataInt(name_primary_index, 0 , data_search, bucket_primary );
                            
                            }
                            
                            if ( secondary_index_active == 1 ) {
                            
                            	list<pair< int, vector<long int>>> bucket_secondary =  SecondaryIndex::ReadBlock( name_secondary_index, 0 );
								int data_search_secondary = data_file.GetDataInt(list_attributes, 2, length_struct_log ,addr_select);
								SecondaryIndex::RemoveItem(name_secondary_index , 0, data_search_secondary, addr_select, bucket_secondary);

								vector<long int> collection_addr = SecondaryIndex::GetCollectionAddress(name_secondary_index,0, data_search_secondary);
	                            int length_collection = 0;
	                     
	                            for (vector<long int>::iterator i_ = collection_addr.begin() ; i_ !=  collection_addr.end(); i_++){
	                            	if ( *i_ != -1 )
	                            		length_collection = length_collection + 1;
	                            }

	                            if ( length_collection == 0 ) {
	                            	SecondaryIndex::RemoveLine(name_secondary_index , 0, data_search_secondary, addr_select, bucket_secondary);
	                            }
                            
                            }
                            
                            if ( static_hashing_active == 1 ) {

                            	int data_search_static_hashing = data_file.GetDataInt(list_attributes,4,length_struct_log,addr_select);
								int hash = StaticHashing::GetHash(data_search_static_hashing);
								long int bucket_address_sh = StaticHashing::GetBucketAddress(name_static_hashing,hash);
								long int addr_select_sh = StaticHashing::GetAddress(name_static_hashing,bucket_address_sh, data_search_static_hashing);
								list<pair< int, long int>> bucket_static_hashing = StaticHashing::ReadBlock(name_static_hashing, bucket_address_sh);	
								StaticHashing::RemoveDataInt(name_static_hashing, bucket_address_sh , data_search_static_hashing, bucket_static_hashing );
                            	
                            }

							// When only exist 1 log
                            if ( addr_select_point_me == -1  && next_addr_select == -1){
                                data_file.UpdateAddress( addr_select + length_struct_log - sizeof(long int) , -1  );
				    			data_dictionary.UpdateAddress( current_entity.GetEntityAddress() + 35 + 8 + 8 , -1); 	
				    			data_file.SetFileHeader(next_addr_select);
                            }
							// first
                            else if ( addr_select_point_me == -1 && next_addr_select != -1){
                                data_file.UpdateAddress( addr_select + length_struct_log - sizeof(long int) , -1  );
				    			data_dictionary.UpdateAddress( current_entity.GetEntityAddress() + 35 + 8 + 8 , next_addr_select); 	
				    			data_file.SetFileHeader(next_addr_select);
                            }
							// remove midle
							else if ( addr_select_point_me != -1 && next_addr_select != -1){
								data_file.UpdateAddress( addr_select_point_me + length_struct_log - sizeof(long int) , next_addr_select );
								data_file.UpdateAddress( addr_select + length_struct_log - sizeof(long int) , -1  );
							}
							// last 
							else if ( addr_select_point_me != -1 && next_addr_select == -1){
								data_file.UpdateAddress( addr_select_point_me + length_struct_log - sizeof(long int) , -1 );
								data_file.UpdateAddress( addr_select + length_struct_log - sizeof(long int) , -1  );
							}
									
							break;
						}
						case 8  : {
							
				    		view.ShowStatusBar(data_file.GetName(), data_file.GetFileHeader(), data_file.GetFileSize() );
				    		int data_search;
				    		long int addr_select;
				    		
				    		int primary_index_active = 0;
				    		int secondary_index_active = 0;
				    		int static_hashing_active = 0;

				    		string name_primary_index;
				    		string name_secondary_index;
				    		string name_static_hashing;

				    		view.ShowMessage("\n\t\t ::: select of data for remove : ");
							cin >> data_search;
							view.ShowMessage("\n\t\t ::: get address of log : ");
							cin >> addr_select;

							for( list<Attribute>::iterator j = list_attributes.begin(); j != list_attributes.end(); j++ ){
								if ( j->GetTypeIndex() == 2  ){
									secondary_index_active = 1;
									string attr_name_key( j->GetName() );
									name_secondary_index = current_entity_name + "_" + attr_name_key;
								} else if ( j->GetTypeIndex() == 1 ) {
									primary_index_active = 1; 
									string attr_name_key( j->GetName() );
									name_primary_index = current_entity_name + "_" + attr_name_key;
								} else if ( j->GetTypeIndex() == 4 ) {
									static_hashing_active = 1;
									string attr_name_sh( j->GetName() );
									name_static_hashing = current_entity_name + "_" + attr_name_sh;
								}
							}
							
                            long int length_struct_log = data_file.GetLengthStructLog( list_attributes );
                            long int addr_select_point_me = data_file.GetAddress(list_attributes, length_struct_log, addr_select);
                            long int next_addr_select = data_file.GetNextAddress(list_attributes, length_struct_log, addr_select);
                            
                            if ( secondary_index_active == 1 ) { 
                            	list<pair< int, vector<long int>>> bucket =  SecondaryIndex::ReadBlock( name_secondary_index, 0 );
								SecondaryIndex::RemoveItem(name_secondary_index , 0, data_search, addr_select, bucket);

								vector<long int> collection_addr = SecondaryIndex::GetCollectionAddress(name_secondary_index,0, data_search);
                            	int length_collection = 0;
                            
                            	for (vector<long int>::iterator i_ = collection_addr.begin() ; i_ !=  collection_addr.end(); i_++){
                            		if ( *i_ != -1 )
                            			length_collection = length_collection + 1;
                            	}

                            	if ( length_collection == 0 ) {
                            		SecondaryIndex::RemoveLine(name_secondary_index , 0, data_search, addr_select, bucket);
                            	}
                            }
							

							
							if ( primary_index_active == 1 ) { 
							
								list<pair< int, long int>> bucket_primary = PrimaryIndex::ReadBlock(name_primary_index,0);	
								int data_search_primary = data_file.GetDataInt(list_attributes,1,length_struct_log,addr_select);
								PrimaryIndex::RemoveDataInt(name_primary_index, 0 , data_search_primary, bucket_primary );

							}
                            
                            
							if ( static_hashing_active == 1 ) {
								
								int data_search_static_hashing = data_file.GetDataInt(list_attributes,4,length_struct_log,addr_select);
								int hash = StaticHashing::GetHash(data_search_static_hashing);
								long int bucket_address_sh = StaticHashing::GetBucketAddress(name_static_hashing,hash);
								long int addr_select_sh = StaticHashing::GetAddress(name_static_hashing,bucket_address_sh, data_search_static_hashing);
								list<pair< int, long int>> bucket_static_hashing = StaticHashing::ReadBlock(name_static_hashing, bucket_address_sh);	
								StaticHashing::RemoveDataInt(name_static_hashing, bucket_address_sh , data_search_static_hashing, bucket_static_hashing );
	
							}
                            

							// When only exist 1 log
                            if ( addr_select_point_me == -1  && next_addr_select == -1){
                                data_file.UpdateAddress( addr_select + length_struct_log - sizeof(long int) , -1  );
				    			data_dictionary.UpdateAddress( current_entity.GetEntityAddress() + 35 + 8 + 8 , -1); 	
				    			data_file.SetFileHeader(next_addr_select);
                            }
							// first
                            else if ( addr_select_point_me == -1 && next_addr_select != -1){
                                data_file.UpdateAddress( addr_select + length_struct_log - sizeof(long int) , -1  );
				    			data_dictionary.UpdateAddress( current_entity.GetEntityAddress() + 35 + 8 + 8 , next_addr_select); 	
				    			data_file.SetFileHeader(next_addr_select);
                            }
							// remove midle
							else if ( addr_select_point_me != -1 && next_addr_select != -1){
								data_file.UpdateAddress( addr_select_point_me + length_struct_log - sizeof(long int) , next_addr_select );
								data_file.UpdateAddress( addr_select + length_struct_log - sizeof(long int) , -1  );
							}
							// last 
							else if ( addr_select_point_me != -1 && next_addr_select == -1){
								data_file.UpdateAddress( addr_select_point_me + length_struct_log - sizeof(long int) , -1 );
								data_file.UpdateAddress( addr_select + length_struct_log - sizeof(long int) , -1  );
							}
							
							
							break; 
						}  
						case 9  : { 
							
							view.ShowStatusBar(data_file.GetName(), data_file.GetFileHeader(), data_file.GetFileSize() );
				    		
				    		int data_search;

				    		int primary_index_active = 0;
				    		int secondary_index_active = 0;
				    		int static_hashing_active = 0;

				    		string name_primary_index;
				    		string name_secondary_index;
				    		string name_static_hashing;
							
							for( list<Attribute>::iterator j = list_attributes.begin(); j != list_attributes.end(); j++ ){
								if ( j->GetTypeIndex() == 2  ){
									secondary_index_active = 1;
									string attr_name_key( j->GetName() );
									name_secondary_index = current_entity_name + "_" + attr_name_key;
								} else if ( j->GetTypeIndex() == 1 ) {
									primary_index_active = 1; 
									string attr_name_key( j->GetName() );
									name_primary_index = current_entity_name + "_" + attr_name_key;
								} else if ( j->GetTypeIndex() == 4  ){
									static_hashing_active = 1;
									string attr_name_sh( j->GetName() );
									name_static_hashing = current_entity_name + "_" + attr_name_sh;
									view.ShowMessage("\n\t\t ::: select of " + attr_name_sh + " for remove : ");	
								}
							}

							cin >> data_search;
                            
                            int hash = StaticHashing::GetHash(data_search);
							long int bucket_address = StaticHashing::GetBucketAddress(name_static_hashing,hash);
							long int addr_select = StaticHashing::GetAddress(name_static_hashing,bucket_address, data_search);
							list<pair< int, long int>> bucket = StaticHashing::ReadBlock(name_static_hashing,bucket_address);	
							StaticHashing::RemoveDataInt(name_static_hashing, bucket_address , data_search, bucket );
							
							long int length_struct_log = data_file.GetLengthStructLog( list_attributes );
							long int addr_select_point_me = data_file.GetAddress(list_attributes, length_struct_log, addr_select);
                            long int next_addr_select = data_file.GetNextAddress(list_attributes, length_struct_log, data_search);
							
							if ( primary_index_active == 1 ) {
								list<pair< int, long int>> bucket_primary = PrimaryIndex::ReadBlock(name_primary_index,0);	
								int data_search_primary = data_file.GetDataInt(list_attributes,1,length_struct_log,addr_select);
								PrimaryIndex::RemoveDataInt(name_primary_index, 0 , data_search_primary, bucket_primary );
							}
                            
                            if ( secondary_index_active == 2 ){

                            	list<pair< int, vector<long int>>> bucket_secondary =  SecondaryIndex::ReadBlock( name_secondary_index, 0 );
								int data_search_secondary = data_file.GetDataInt(list_attributes, 2, length_struct_log ,addr_select);
								SecondaryIndex::RemoveItem(name_secondary_index , 0, data_search_secondary, addr_select, bucket_secondary);

								vector<long int> collection_addr = SecondaryIndex::GetCollectionAddress(name_secondary_index,0, data_search_secondary);
	                            int length_collection = 0;
	                     
	                            for (vector<long int>::iterator i_ = collection_addr.begin() ; i_ !=  collection_addr.end(); i_++){
	                            	if ( *i_ != -1 )
	                            		length_collection = length_collection + 1;
	                            }

	                            if ( length_collection == 0 ) {
	                            	SecondaryIndex::RemoveLine(name_secondary_index , 0, data_search_secondary, addr_select, bucket_secondary);
	                            }	
                            }
							

							// When only exist 1 log
                            if ( addr_select_point_me == -1  && next_addr_select == -1){
                                data_file.UpdateAddress( addr_select + length_struct_log - sizeof(long int) , -1  );
				    			data_dictionary.UpdateAddress( current_entity.GetEntityAddress() + 35 + 8 + 8 , -1); 	
				    			data_file.SetFileHeader(next_addr_select);
                            }
							// first
                            else if ( addr_select_point_me == -1 && next_addr_select != -1){
                                data_file.UpdateAddress( addr_select + length_struct_log - sizeof(long int) , -1  );
				    			data_dictionary.UpdateAddress( current_entity.GetEntityAddress() + 35 + 8 + 8 , next_addr_select); 	
				    			data_file.SetFileHeader(next_addr_select);
                            }
							// remove midle
							else if ( addr_select_point_me != -1 && next_addr_select != -1){
								data_file.UpdateAddress( addr_select_point_me + length_struct_log - sizeof(long int) , next_addr_select );
								data_file.UpdateAddress( addr_select + length_struct_log - sizeof(long int) , -1  );
							}
							// last 
							else if ( addr_select_point_me != -1 && next_addr_select == -1){
								data_file.UpdateAddress( addr_select_point_me + length_struct_log - sizeof(long int) , -1 );
								data_file.UpdateAddress( addr_select + length_struct_log - sizeof(long int) , -1  );
							}
							
							
							break; 
						}  
						case 10 : { 
				    		view.ShowStatusBar(data_file.GetName(), data_file.GetFileHeader(), data_file.GetFileSize() );
				    		int data_search;
				    		int primary_index_active = 0;
				    		int secondary_index_active = 0;
				    		int static_hashing_active = 0;
				    		bool exist_search_key = false;
				    		string name_primary_index;
				    		string name_secondary_index;
				    		string name_static_hashing;
                            Attribute attr;
							for( list<Attribute>::iterator j = list_attributes.begin(); j != list_attributes.end(); j++ ){
								if ( j->GetTypeIndex() == 1  ){
									primary_index_active = 1;
									string attr_name_key( j->GetName() );
									name_primary_index = current_entity_name + "_" + attr_name_key;
									view.ShowMessage("\n\t\t::: select of " + attr_name_key + " to Update  => ");
								} else if ( j->GetTypeIndex() == 2) {
									secondary_index_active = 1;
									string attr_name_key( j->GetName() );
									name_secondary_index = current_entity_name + "_" + attr_name_key;
								} else if ( j->GetTypeIndex() == 4 ) {
									static_hashing_active = 1;
									string attr_name_sh( j->GetName() );
									name_static_hashing = current_entity_name + "_" + attr_name_sh;
								} else if ( j->GetTypeIndex() == 3 ) {
									attr = *j;
									exist_search_key = true;
								}
							}
							cin >> data_search;
							long int length_struct_log = data_file.GetLengthStructLog( list_attributes );
                            long int addr_select = data_file.GetAddress(list_attributes, length_struct_log, data_search);
                            long int addr_select_point_me = data_file.GetAddress(list_attributes, length_struct_log, addr_select);
                            long int next_addr_select_point_me = data_file.GetNextAddress(list_attributes, length_struct_log, addr_select_point_me);
                            long int next_addr_select = data_file.GetNextAddress(list_attributes, length_struct_log, data_search);
                            
                            if ( primary_index_active == 1 ) {
                            	list<pair< int, long int>> bucket_primary = PrimaryIndex::ReadBlock(name_primary_index,0);	
								PrimaryIndex::RemoveDataInt(name_primary_index, 0 , data_search, bucket_primary );
                            }
                            
                            if ( secondary_index_active == 1 ) {
                            	list<pair< int, vector<long int>>> bucket_secondary =  SecondaryIndex::ReadBlock( name_secondary_index, 0 );
								int data_search_secondary = data_file.GetDataInt(list_attributes, 2, length_struct_log ,addr_select);
								SecondaryIndex::RemoveItem(name_secondary_index , 0, data_search_secondary, addr_select, bucket_secondary);
								vector<long int> collection_addr = SecondaryIndex::GetCollectionAddress(name_secondary_index,0, data_search_secondary);
	                            int length_collection = 0;
	                            for (vector<long int>::iterator i_ = collection_addr.begin() ; i_ !=  collection_addr.end(); i_++){
	                            	if ( *i_ != -1 )
	                            		length_collection = length_collection + 1;
	                            }
	                            if ( length_collection == 0 ) 
	                            	SecondaryIndex::RemoveLine(name_secondary_index , 0, data_search_secondary, addr_select, bucket_secondary);
                            }
                            
                            if ( static_hashing_active == 1 ) {
                            	int data_search_static_hashing = data_file.GetDataInt(list_attributes,4,length_struct_log,addr_select);
								int hash = StaticHashing::GetHash(data_search_static_hashing);
								long int bucket_address_sh = StaticHashing::GetBucketAddress(name_static_hashing,hash);
								long int addr_select_sh = StaticHashing::GetAddress(name_static_hashing,bucket_address_sh, data_search_static_hashing);
								list<pair< int, long int>> bucket_static_hashing = StaticHashing::ReadBlock(name_static_hashing, bucket_address_sh);	
								StaticHashing::RemoveDataInt(name_static_hashing, bucket_address_sh , data_search_static_hashing, bucket_static_hashing );	
                            }

                            string data_key_search = data_file.Update(list_attributes, current_entity_name ,addr_select);
							
							if ( exist_search_key == true ) {
								int amount_log = data_file.GetAmountLog(list_attributes);
								int length_to_search_key = data_dictionary.LengthStartToSearchKey(list_attributes);
								long int prev_point_me = data_file.GetAddress(list_attributes,length_struct_log,addr_select);
								list<string> list_str = data_file.GetListStr(list_attributes,attr,length_struct_log,length_to_search_key,amount_log);
	                            list_str.sort();
								pair<string,string> next_prev = data_file.GetPrevNext(list_str,data_key_search);
								long int previus_addr_i = -1;
								long int previus_next_addr_i = -1;
								long int next_addr_j = -1;
								long int next_next_addr_j = -1;
	                            // previus
								if ( next_prev.first != "-1" ) {
									previus_addr_i = data_file.GetAddress(list_attributes,length_struct_log,next_prev.first); 
									previus_next_addr_i = data_file.GetNextAddress(list_attributes,length_struct_log,previus_addr_i);
								}
								// next
								if ( next_prev.second != "-1"  ) {
									next_addr_j = data_file.GetAddress(list_attributes,length_struct_log,next_prev.second);
									next_next_addr_j = data_file.GetNextAddress(list_attributes,length_struct_log,next_addr_j);
								}

								if ( amount_log == 2 ) {
									// first 
									if (  next_prev.first == "-1" && next_prev.second != "-1" ) {
										data_file.UpdateAddress( addr_select + length_struct_log - sizeof(long int) ,  next_addr_j );
										data_file.UpdateAddress( next_addr_j + length_struct_log - sizeof(long int) ,  -1 );
					    				data_dictionary.UpdateAddress( current_entity.GetEntityAddress() + 35 + 8 + 8 , addr_select ); 	
					    				data_file.SetFileHeader( addr_select );
									} // last 
									else if ( next_prev.first != "-1" && next_prev.second == "-1" ) {
										data_file.UpdateAddress( previus_addr_i + length_struct_log - sizeof(long int) , addr_select );
										data_file.UpdateAddress( addr_select + length_struct_log - sizeof(long int) , -1 );
									}
								} else if ( amount_log > 3 ) {
	                                //  ==> SEND TO TOP  [ midle :: TO :: top ]
									if ( addr_select != data_file.GetFileHeader() && next_addr_select != -1 && next_prev.first == "-1" && next_prev.second != "-1" ) {
											
											data_file.UpdateAddress( addr_select + length_struct_log - sizeof(long int) ,  data_file.GetFileHeader() ); 
											data_file.UpdateAddress( addr_select_point_me + length_struct_log - sizeof(long int) ,  next_addr_select );  
											data_dictionary.UpdateAddress( current_entity.GetEntityAddress() + 35 + 8 + 8 , addr_select );
											data_file.SetFileHeader( addr_select );	
									//  ==> SEND TO TOP [ last :: TO :: top ]
									}	else if ( addr_select != data_file.GetFileHeader() && next_addr_select == -1 && next_prev.first == "-1" && next_prev.second != "-1") {
											
											data_file.UpdateAddress( addr_select + length_struct_log - sizeof(long int) ,  data_file.GetFileHeader() );
											data_file.UpdateAddress( addr_select_point_me + length_struct_log - sizeof(long int) ,  -1 );
											data_dictionary.UpdateAddress( current_entity.GetEntityAddress() + 35 + 8 + 8 , addr_select );
											data_file.SetFileHeader( addr_select );
									//  ==> SEND TO MIDLE [  last :: TO :: midle ]
									}   else if ( addr_select != data_file.GetFileHeader() && next_addr_select == -1 && next_prev.first != "-1" && next_prev.second != "-1" ) {
											
											data_file.UpdateAddress( addr_select_point_me + length_struct_log - sizeof(long int) ,  -1 );
											data_file.UpdateAddress( addr_select + length_struct_log - sizeof(long int) ,  next_addr_j );
											data_file.UpdateAddress( previus_addr_i + length_struct_log - sizeof(long int) ,  addr_select );
									//  ==> SEND TO MIDLE [ midle :: TO :: midle ]
									}   else if ( addr_select != data_file.GetFileHeader() && next_addr_select != -1 && next_prev.first != "-1" && next_prev.second != "-1" ) {
											
											data_file.UpdateAddress( addr_select_point_me + length_struct_log - sizeof(long int) ,  next_addr_select );
											data_file.UpdateAddress( previus_addr_i + length_struct_log - sizeof(long int) ,  addr_select );
											data_file.UpdateAddress( addr_select + length_struct_log - sizeof(long int) ,  next_addr_j );
									//  ==> SEND TO MIDLE [ top :: TO :: midle ]
									}   else if ( addr_select == data_file.GetFileHeader() && next_addr_select != -1 && next_prev.first != "-1" && next_prev.second != "-1" ) {
											
											data_file.UpdateAddress( addr_select + length_struct_log - sizeof(long int) ,  next_addr_j );
											data_file.UpdateAddress( previus_addr_i + length_struct_log - sizeof(long int) ,  addr_select );
											data_dictionary.UpdateAddress( current_entity.GetEntityAddress() + 35 + 8 + 8 , next_addr_select );
											data_file.SetFileHeader( next_addr_select );
									//  ==> SEND TO LAST   [  top :: TO :: last ]
									}	else if ( addr_select == data_file.GetFileHeader() && next_addr_select != -1 && next_prev.first != "-1" && next_prev.second == "-1" ) {
											
											data_file.UpdateAddress( addr_select + length_struct_log - sizeof(long int) , -1 );
											data_file.UpdateAddress( previus_addr_i + length_struct_log - sizeof(long int) , addr_select );
											data_dictionary.UpdateAddress( current_entity.GetEntityAddress() + 35 + 8 + 8 , next_addr_select );
											data_file.SetFileHeader( next_addr_select );
									// 	==> SEND TO LAST  [ midle  :: TO :: last ]
									}	else if (  addr_select != data_file.GetFileHeader() && next_addr_select != -1  && next_prev.first != "-1" && next_prev.second == "-1" ) {
											
											data_file.UpdateAddress( addr_select + length_struct_log - sizeof(long int) , -1 );
											data_file.UpdateAddress( previus_addr_i + length_struct_log - sizeof(long int) , addr_select );
											data_file.UpdateAddress( addr_select_point_me + length_struct_log - sizeof(long int) , next_addr_select );	
									}	
								}
							} // end if exist_search_key
							break;
						}  
						case 11 : { 
				    		view.ShowStatusBar(data_file.GetName(), data_file.GetFileHeader(), data_file.GetFileSize() );
				    		int data_search;
				    		long int addr_select;
				    		int primary_index_active = 0;
				    		int secondary_index_active = 0;
				    		int static_hashing_active = 0;
				    		bool exist_search_key = false;
				    		string name_primary_index;
				    		string name_secondary_index;
				    		string name_static_hashing;
				    		Attribute attr;
				    		view.ShowMessage("\n\t\t ::: select of data for update => : ");
							cin >> data_search;
							view.ShowMessage("\n\t\t ::: get address of log : ");
							cin >> addr_select;

							for( list<Attribute>::iterator j = list_attributes.begin(); j != list_attributes.end(); j++ ){
								if ( j->GetTypeIndex() == 2  ){
									secondary_index_active = 1;
									string attr_name_key( j->GetName() );
									name_secondary_index = current_entity_name + "_" + attr_name_key;
								} else if ( j->GetTypeIndex() == 1 ) {
									primary_index_active = 1; 
									string attr_name_key( j->GetName() );
									name_primary_index = current_entity_name + "_" + attr_name_key;
								} else if ( j->GetTypeIndex() == 4 ) {
									static_hashing_active = 1;
									string attr_name_sh( j->GetName() );
									name_static_hashing = current_entity_name + "_" + attr_name_sh;
								} else if ( j->GetTypeIndex() == 3 ) {
									attr = *j;
									exist_search_key = true;
								}
							}
							
                            long int length_struct_log = data_file.GetLengthStructLog( list_attributes );
                            long int addr_select_point_me = data_file.GetAddress(list_attributes, length_struct_log, addr_select);
                            long int next_addr_select = data_file.GetNextAddress(list_attributes, length_struct_log, addr_select);
                            
                            if ( secondary_index_active == 1 ) { 
                            	list<pair< int, vector<long int>>> bucket =  SecondaryIndex::ReadBlock( name_secondary_index, 0 );
								SecondaryIndex::RemoveItem(name_secondary_index , 0, data_search, addr_select, bucket);
								vector<long int> collection_addr = SecondaryIndex::GetCollectionAddress(name_secondary_index,0, data_search);
                            	int length_collection = 0;
                            	for (vector<long int>::iterator i_ = collection_addr.begin() ; i_ !=  collection_addr.end(); i_++){
                            		if ( *i_ != -1 )
                            			length_collection = length_collection + 1;
                            	}
                            	if ( length_collection == 0 )
                            		SecondaryIndex::RemoveLine(name_secondary_index , 0, data_search, addr_select, bucket);
                            }
							if ( primary_index_active == 1 ) { 
								list<pair< int, long int>> bucket_primary = PrimaryIndex::ReadBlock(name_primary_index,0);	
								int data_search_primary = data_file.GetDataInt(list_attributes,1,length_struct_log,addr_select);
								PrimaryIndex::RemoveDataInt(name_primary_index, 0 , data_search_primary, bucket_primary );
							}
							if ( static_hashing_active == 1 ) {	
								int data_search_static_hashing = data_file.GetDataInt(list_attributes,4,length_struct_log,addr_select);
								int hash = StaticHashing::GetHash(data_search_static_hashing);
								long int bucket_address_sh = StaticHashing::GetBucketAddress(name_static_hashing,hash);
								long int addr_select_sh = StaticHashing::GetAddress(name_static_hashing,bucket_address_sh, data_search_static_hashing);
								list<pair< int, long int>> bucket_static_hashing = StaticHashing::ReadBlock(name_static_hashing, bucket_address_sh);	
								StaticHashing::RemoveDataInt(name_static_hashing, bucket_address_sh , data_search_static_hashing, bucket_static_hashing );
							}

							string data_key_search = data_file.Update(list_attributes, current_entity_name ,addr_select);
							
							if ( exist_search_key == true ) {
								int amount_log = data_file.GetAmountLog(list_attributes);
								int length_to_search_key = data_dictionary.LengthStartToSearchKey(list_attributes);
								long int prev_point_me = data_file.GetAddress(list_attributes,length_struct_log,addr_select);
								list<string> list_str = data_file.GetListStr(list_attributes,attr,length_struct_log,length_to_search_key,amount_log);
	                            list_str.sort();
								pair<string,string> next_prev = data_file.GetPrevNext(list_str,data_key_search);
								long int previus_addr_i = -1;
								long int previus_next_addr_i = -1;
								long int next_addr_j = -1;
								long int next_next_addr_j = -1;
	                            // previus
								if ( next_prev.first != "-1" ) {
									previus_addr_i = data_file.GetAddress(list_attributes,length_struct_log,next_prev.first); 
									previus_next_addr_i = data_file.GetNextAddress(list_attributes,length_struct_log,previus_addr_i);
								}
								// next
								if ( next_prev.second != "-1"  ) {
									next_addr_j = data_file.GetAddress(list_attributes,length_struct_log,next_prev.second);
									next_next_addr_j = data_file.GetNextAddress(list_attributes,length_struct_log,next_addr_j);
								}
								if ( amount_log == 2 ) {
									// first 
									if (  next_prev.first == "-1" && next_prev.second != "-1" ) {
										data_file.UpdateAddress( addr_select + length_struct_log - sizeof(long int) ,  next_addr_j );
										data_file.UpdateAddress( next_addr_j + length_struct_log - sizeof(long int) ,  -1 );
					    				data_dictionary.UpdateAddress( current_entity.GetEntityAddress() + 35 + 8 + 8 , addr_select ); 	
					    				data_file.SetFileHeader( addr_select );
									} // last 
									else if ( next_prev.first != "-1" && next_prev.second == "-1" ) {
										data_file.UpdateAddress( previus_addr_i + length_struct_log - sizeof(long int) , addr_select );
										data_file.UpdateAddress( addr_select + length_struct_log - sizeof(long int) , -1 );
									}
								} else if ( amount_log > 3 ) {
	                                //  ==> SEND TO TOP  [ midle :: TO :: top ]
									if ( addr_select != data_file.GetFileHeader() && next_addr_select != -1 && next_prev.first == "-1" && next_prev.second != "-1" ) {
											
											data_file.UpdateAddress( addr_select + length_struct_log - sizeof(long int) ,  data_file.GetFileHeader() ); 
											data_file.UpdateAddress( addr_select_point_me + length_struct_log - sizeof(long int) ,  next_addr_select );  
											data_dictionary.UpdateAddress( current_entity.GetEntityAddress() + 35 + 8 + 8 , addr_select );
											data_file.SetFileHeader( addr_select );	
									//  ==> SEND TO TOP [ last :: TO :: top ]
									}	else if ( addr_select != data_file.GetFileHeader() && next_addr_select == -1 && next_prev.first == "-1" && next_prev.second != "-1") {
											
											data_file.UpdateAddress( addr_select + length_struct_log - sizeof(long int) ,  data_file.GetFileHeader() );
											data_file.UpdateAddress( addr_select_point_me + length_struct_log - sizeof(long int) ,  -1 );
											data_dictionary.UpdateAddress( current_entity.GetEntityAddress() + 35 + 8 + 8 , addr_select );
											data_file.SetFileHeader( addr_select );
									//  ==> SEND TO MIDLE [  last :: TO :: midle ]
									}   else if ( addr_select != data_file.GetFileHeader() && next_addr_select == -1 && next_prev.first != "-1" && next_prev.second != "-1" ) {
											
											data_file.UpdateAddress( addr_select_point_me + length_struct_log - sizeof(long int) ,  -1 );
											data_file.UpdateAddress( addr_select + length_struct_log - sizeof(long int) ,  next_addr_j );
											data_file.UpdateAddress( previus_addr_i + length_struct_log - sizeof(long int) ,  addr_select );
									//  ==> SEND TO MIDLE [ midle :: TO :: midle ]
									}   else if ( addr_select != data_file.GetFileHeader() && next_addr_select != -1 && next_prev.first != "-1" && next_prev.second != "-1" ) {
											
											data_file.UpdateAddress( addr_select_point_me + length_struct_log - sizeof(long int) ,  next_addr_select );
											data_file.UpdateAddress( previus_addr_i + length_struct_log - sizeof(long int) ,  addr_select );
											data_file.UpdateAddress( addr_select + length_struct_log - sizeof(long int) ,  next_addr_j );
									//  ==> SEND TO MIDLE [ top :: TO :: midle ]
									}   else if ( addr_select == data_file.GetFileHeader() && next_addr_select != -1 && next_prev.first != "-1" && next_prev.second != "-1" ) {
											
											data_file.UpdateAddress( addr_select + length_struct_log - sizeof(long int) ,  next_addr_j );
											data_file.UpdateAddress( previus_addr_i + length_struct_log - sizeof(long int) ,  addr_select );
											data_dictionary.UpdateAddress( current_entity.GetEntityAddress() + 35 + 8 + 8 , next_addr_select );
											data_file.SetFileHeader( next_addr_select );
									//  ==> SEND TO LAST   [  top :: TO :: last ]
									}	else if ( addr_select == data_file.GetFileHeader() && next_addr_select != -1 && next_prev.first != "-1" && next_prev.second == "-1" ) {
											
											data_file.UpdateAddress( addr_select + length_struct_log - sizeof(long int) , -1 );
											data_file.UpdateAddress( previus_addr_i + length_struct_log - sizeof(long int) , addr_select );
											data_dictionary.UpdateAddress( current_entity.GetEntityAddress() + 35 + 8 + 8 , next_addr_select );
											data_file.SetFileHeader( next_addr_select );
									// 	==> SEND TO LAST  [ midle  :: TO :: last ]
									}	else if (  addr_select != data_file.GetFileHeader() && next_addr_select != -1  && next_prev.first != "-1" && next_prev.second == "-1" ) {
											
											data_file.UpdateAddress( addr_select + length_struct_log - sizeof(long int) , -1 );
											data_file.UpdateAddress( previus_addr_i + length_struct_log - sizeof(long int) , addr_select );
											data_file.UpdateAddress( addr_select_point_me + length_struct_log - sizeof(long int) , next_addr_select );	
									}	
								}
							}
							break; 
						}  
						case 12 : { 
							view.ShowStatusBar(data_file.GetName(), data_file.GetFileHeader(), data_file.GetFileSize() );
				    		
				    		int data_search;
				    		int primary_index_active = 0;
				    		int secondary_index_active = 0;
				    		int static_hashing_active = 0;
				    		bool exist_search_key = false;
				    		string name_primary_index;
				    		string name_secondary_index;
				    		string name_static_hashing;
							Attribute attr;
							for( list<Attribute>::iterator j = list_attributes.begin(); j != list_attributes.end(); j++ ){
								if ( j->GetTypeIndex() == 2  ){
									secondary_index_active = 1;
									string attr_name_key( j->GetName() );
									name_secondary_index = current_entity_name + "_" + attr_name_key;
								} else if ( j->GetTypeIndex() == 1 ) {
									primary_index_active = 1; 
									string attr_name_key( j->GetName() );
									name_primary_index = current_entity_name + "_" + attr_name_key;
								} else if ( j->GetTypeIndex() == 4  ){
									static_hashing_active = 1;
									string attr_name_sh( j->GetName() );
									name_static_hashing = current_entity_name + "_" + attr_name_sh;
									view.ShowMessage("\n\t\t ::: select of " + attr_name_sh + " to update =>  : ");	
								}  else if ( j->GetTypeIndex() == 3 ) {
									attr = *j;
									exist_search_key = true;
								}
							}
							cin >> data_search;
                            int hash = StaticHashing::GetHash(data_search);
							long int bucket_address = StaticHashing::GetBucketAddress(name_static_hashing,hash);
							long int addr_select = StaticHashing::GetAddress(name_static_hashing,bucket_address, data_search);
							list<pair< int, long int>> bucket = StaticHashing::ReadBlock(name_static_hashing,bucket_address);	
							StaticHashing::RemoveDataInt(name_static_hashing, bucket_address , data_search, bucket );
							long int length_struct_log = data_file.GetLengthStructLog( list_attributes );
							long int addr_select_point_me = data_file.GetAddress(list_attributes, length_struct_log, addr_select);
                            long int next_addr_select = data_file.GetNextAddress(list_attributes, length_struct_log, data_search);
							
							if ( primary_index_active == 1 ) {
								list<pair< int, long int>> bucket_primary = PrimaryIndex::ReadBlock(name_primary_index,0);	
								int data_search_primary = data_file.GetDataInt(list_attributes,1,length_struct_log,addr_select);
								PrimaryIndex::RemoveDataInt(name_primary_index, 0 , data_search_primary, bucket_primary );
							}
                            if ( secondary_index_active == 2 ){
                            	list<pair< int, vector<long int>>> bucket_secondary =  SecondaryIndex::ReadBlock( name_secondary_index, 0 );
								int data_search_secondary = data_file.GetDataInt(list_attributes, 2, length_struct_log ,addr_select);
								SecondaryIndex::RemoveItem(name_secondary_index , 0, data_search_secondary, addr_select, bucket_secondary);
								vector<long int> collection_addr = SecondaryIndex::GetCollectionAddress(name_secondary_index,0, data_search_secondary);
	                            int length_collection = 0;
	                            for (vector<long int>::iterator i_ = collection_addr.begin() ; i_ !=  collection_addr.end(); i_++){
	                            	if ( *i_ != -1 )
	                            		length_collection = length_collection + 1;
	                            }
	                            if ( length_collection == 0 ) 
	                            	SecondaryIndex::RemoveLine(name_secondary_index , 0, data_search_secondary, addr_select, bucket_secondary);
                            }

                            string data_key_search = data_file.Update(list_attributes, current_entity_name ,addr_select);

                            if ( exist_search_key == true ) {
								int amount_log = data_file.GetAmountLog(list_attributes);
								int length_to_search_key = data_dictionary.LengthStartToSearchKey(list_attributes);
								long int prev_point_me = data_file.GetAddress(list_attributes,length_struct_log,addr_select);
								list<string> list_str = data_file.GetListStr(list_attributes,attr,length_struct_log,length_to_search_key,amount_log);
	                            list_str.sort();
								pair<string,string> next_prev = data_file.GetPrevNext(list_str,data_key_search);
								long int previus_addr_i = -1;
								long int previus_next_addr_i = -1;
								long int next_addr_j = -1;
								long int next_next_addr_j = -1;
	                            // previus
								if ( next_prev.first != "-1" ) {
									previus_addr_i = data_file.GetAddress(list_attributes,length_struct_log,next_prev.first); 
									previus_next_addr_i = data_file.GetNextAddress(list_attributes,length_struct_log,previus_addr_i);
								}
								// next
								if ( next_prev.second != "-1"  ) {
									next_addr_j = data_file.GetAddress(list_attributes,length_struct_log,next_prev.second);
									next_next_addr_j = data_file.GetNextAddress(list_attributes,length_struct_log,next_addr_j);
								}
								if ( amount_log == 2 ) {
									// first 
									if (  next_prev.first == "-1" && next_prev.second != "-1" ) {
										data_file.UpdateAddress( addr_select + length_struct_log - sizeof(long int) ,  next_addr_j );
										data_file.UpdateAddress( next_addr_j + length_struct_log - sizeof(long int) ,  -1 );
					    				data_dictionary.UpdateAddress( current_entity.GetEntityAddress() + 35 + 8 + 8 , addr_select ); 	
					    				data_file.SetFileHeader( addr_select );
									} // last 
									else if ( next_prev.first != "-1" && next_prev.second == "-1" ) {
										data_file.UpdateAddress( previus_addr_i + length_struct_log - sizeof(long int) , addr_select );
										data_file.UpdateAddress( addr_select + length_struct_log - sizeof(long int) , -1 );
									}
								} else if ( amount_log > 3 ) {
	                                //  ==> SEND TO TOP  [ midle :: TO :: top ]
									if ( addr_select != data_file.GetFileHeader() && next_addr_select != -1 && next_prev.first == "-1" && next_prev.second != "-1" ) {
											
											data_file.UpdateAddress( addr_select + length_struct_log - sizeof(long int) ,  data_file.GetFileHeader() ); 
											data_file.UpdateAddress( addr_select_point_me + length_struct_log - sizeof(long int) ,  next_addr_select );  
											data_dictionary.UpdateAddress( current_entity.GetEntityAddress() + 35 + 8 + 8 , addr_select );
											data_file.SetFileHeader( addr_select );	
									//  ==> SEND TO TOP [ last :: TO :: top ]
									}	else if ( addr_select != data_file.GetFileHeader() && next_addr_select == -1 && next_prev.first == "-1" && next_prev.second != "-1") {
											
											data_file.UpdateAddress( addr_select + length_struct_log - sizeof(long int) ,  data_file.GetFileHeader() );
											data_file.UpdateAddress( addr_select_point_me + length_struct_log - sizeof(long int) ,  -1 );
											data_dictionary.UpdateAddress( current_entity.GetEntityAddress() + 35 + 8 + 8 , addr_select );
											data_file.SetFileHeader( addr_select );
									//  ==> SEND TO MIDLE [  last :: TO :: midle ]
									}   else if ( addr_select != data_file.GetFileHeader() && next_addr_select == -1 && next_prev.first != "-1" && next_prev.second != "-1" ) {
											
											data_file.UpdateAddress( addr_select_point_me + length_struct_log - sizeof(long int) ,  -1 );
											data_file.UpdateAddress( addr_select + length_struct_log - sizeof(long int) ,  next_addr_j );
											data_file.UpdateAddress( previus_addr_i + length_struct_log - sizeof(long int) ,  addr_select );
									//  ==> SEND TO MIDLE [ midle :: TO :: midle ]
									}   else if ( addr_select != data_file.GetFileHeader() && next_addr_select != -1 && next_prev.first != "-1" && next_prev.second != "-1" ) {
											
											data_file.UpdateAddress( addr_select_point_me + length_struct_log - sizeof(long int) ,  next_addr_select );
											data_file.UpdateAddress( previus_addr_i + length_struct_log - sizeof(long int) ,  addr_select );
											data_file.UpdateAddress( addr_select + length_struct_log - sizeof(long int) ,  next_addr_j );
									//  ==> SEND TO MIDLE [ top :: TO :: midle ]
									}   else if ( addr_select == data_file.GetFileHeader() && next_addr_select != -1 && next_prev.first != "-1" && next_prev.second != "-1" ) {
											
											data_file.UpdateAddress( addr_select + length_struct_log - sizeof(long int) ,  next_addr_j );
											data_file.UpdateAddress( previus_addr_i + length_struct_log - sizeof(long int) ,  addr_select );
											data_dictionary.UpdateAddress( current_entity.GetEntityAddress() + 35 + 8 + 8 , next_addr_select );
											data_file.SetFileHeader( next_addr_select );
									//  ==> SEND TO LAST   [  top :: TO :: last ]
									}	else if ( addr_select == data_file.GetFileHeader() && next_addr_select != -1 && next_prev.first != "-1" && next_prev.second == "-1" ) {
											
											data_file.UpdateAddress( addr_select + length_struct_log - sizeof(long int) , -1 );
											data_file.UpdateAddress( previus_addr_i + length_struct_log - sizeof(long int) , addr_select );
											data_dictionary.UpdateAddress( current_entity.GetEntityAddress() + 35 + 8 + 8 , next_addr_select );
											data_file.SetFileHeader( next_addr_select );
									// 	==> SEND TO LAST  [ midle  :: TO :: last ]
									}	else if (  addr_select != data_file.GetFileHeader() && next_addr_select != -1  && next_prev.first != "-1" && next_prev.second == "-1" ) {
											
											data_file.UpdateAddress( addr_select + length_struct_log - sizeof(long int) , -1 );
											data_file.UpdateAddress( previus_addr_i + length_struct_log - sizeof(long int) , addr_select );
											data_file.UpdateAddress( addr_select_point_me + length_struct_log - sizeof(long int) , next_addr_select );	
									}	
								}
							}

							break; 
						} 
						case 13 :  break;   
				    }
	    		} while(option_file < 13);
	    		if (option_file > 12 ) view.Clear();
	    			break;
	    		//}
	    	} //  end if current_entity
	    		case 4:  // Exit 
	    			return 0;
	    			break;
	    }
    } while(option <= 4);
    return 0;  
}