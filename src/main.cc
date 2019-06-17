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
#include "primary_index_file.h"
#include "secondary_index_file.h"
#include "static_hashing_file.h"
#include "multilist_file.h"
#include "view.h"

// namespaces to use
using namespace std; 
using namespace dictionary;
using namespace ui;
using namespace archive;

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

    do {    	
		view.ShowTitle();
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
					    					view.ShowMessage(":: Entity selected: " +  str_entity_selected );
					    					view.ShowAttributeMenu();
								    		view.ShowMessage("\nSelect an option >_");
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
										    		view.ShowMessage("===> Update Attribute");
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
										    		view.ShowMessage("\n===> Delete Attribute \t\t:: Attribute Name:");
										    		cin >> attr_name;
										    		if (attr_name != "")
										    			data_dictionary.RemoveAttribute(current_entity, data_dictionary.ReadListAttributes(current_entity), attr_name);
										    		break;
										    	}
										    	case 4: view.ShowMessage("===>Select Attribute"); break;
										    	case 5: { // Show entities
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
								PrimaryIndexFile primary_index_file( name_primary_index );
								primary_index_file.CreateFile();
								primary_index_file.CreateBlock( 0 );
								list< pair< int, long int> > block_int = PrimaryIndexFile::ReadBlock(name_primary_index, 0 );
								if ( i->GetIndexAddress() == -1 )
									data_dictionary.UpdateAddress( i->GetAttributeAddress() + 52, 0 );
							} 	else if ( i->GetTypeIndex() == 2 ) {
								string name_secondary_index = current_entity_name + "_" + attr_name;
								SecondaryIndexFile secondary_index_file( name_secondary_index );
								secondary_index_file.CreateFile();
								secondary_index_file.CreateBlock( 0 );
								if ( i->GetIndexAddress() == -1 )
									data_dictionary.UpdateAddress( i->GetAttributeAddress() + 52, 0 );
							}   else if ( i->GetTypeIndex() == 4 ) {
								string name_static_hashing = current_entity_name + "_" + attr_name;
								StaticHashingFile static_hashing_file( name_static_hashing );
								static_hashing_file.CreateFile();
								if ( i->GetIndexAddress() == -1 )
									data_dictionary.UpdateAddress( i->GetAttributeAddress() + 52, ( sizeof(long int) * ( NO_BUCKETS_SH_ + 1 ) ) );
							} else if ( i->GetTypeIndex() == 5 ) {
								string name_multilist = current_entity_name + "_" + attr_name;
								MultilistFile multilist_file( name_multilist );
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
				    		list<pair<int,long int>> list_data_multilist;
				    		for( list<Attribute>::iterator j = list_attributes.begin(); j != list_attributes.end(); j++ ){
								if ( j->GetTypeIndex() == 5  ){
									list_data_multilist = data_file.GetListDataMultilist( list_attributes, *j );
								}
							}	
				    		long int header_data_file = data_file.AppendData(list_attributes,list_data,current_entity_name, list_data_multilist);
				    		
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
									
									list< pair< int, long int> > block = PrimaryIndexFile::ReadBlock(name_primary_index_i, 0 );
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
									
									list< pair< int, vector<long int>> > block_x = SecondaryIndexFile::ReadBlock(name_secondary_index_i, 0 );
                                    
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
									vector<long int> bucket_addrs = StaticHashingFile::GetBucketsAddress(name_sh);
                            		vector<long int>::iterator itr_bck = bucket_addrs.begin();
                            		int count_hash = 0;
                            		while ( itr_bck != bucket_addrs.end() ) {
									
										if ( *itr_bck != -1 ){ 
											cout << endl << "\t\t :: Hash [ " << count_hash << " ]";
											cout << endl << "\t\t Data \t Data Address";
											list< pair< int, long int> > bucket = StaticHashingFile::ReadBlock(name_sh, *itr_bck );
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
									list< pair< int, long int> > block_l = MultilistFile::ReadBlock(name_multilist, 0 );
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
				    		view.ShowMessage("\n\t\t ===> Remove a register use Primary Index");
				    		view.ShowStatusBar(data_file.GetName(), data_file.GetFileHeader(), data_file.GetFileSize() );
				    		int data_search;
				    		string name_primary_index;
				    		view.ShowMessage("\n\t\t ::: select of data for remove :");
							cin >> data_search;
							
							for( list<Attribute>::iterator j = list_attributes.begin(); j != list_attributes.end(); j++ ){
								if ( j->GetTypeIndex() == 1  ){
									string attr_name_key( j->GetName() );
									name_primary_index = current_entity_name + "_" + attr_name_key;
								}
							}

							list<pair< int, long int>> bucket = PrimaryIndexFile::ReadBlock(name_primary_index,0);	
							PrimaryIndexFile::RemoveDataInt(name_primary_index, 0 , data_search, bucket );

							long int length_struct_log = data_file.GetLengthStructLog( list_attributes );

                            long int addr_select = data_file.GetAddress(list_attributes, length_struct_log, data_search);
                            long int addr_select_point_me = data_file.GetAddress(list_attributes, length_struct_log, addr_select);

                            long int next_addr_select = data_file.GetNextAddress(list_attributes, length_struct_log, data_search);
							cout << ":: " << length_struct_log << " /  " << addr_select << " /  " << next_addr_select << " / " << addr_select_point_me;
							
							// first
                            if ( addr_select_point_me == -1){
                                data_file.UpdateAddress( addr_select + length_struct_log - sizeof(long int) , -1  );
				    			data_dictionary.UpdateAddress( current_entity.GetEntityAddress() + 35 + 8 + 8 , next_addr_select); 	
				    			data_file.SetFileHeader(next_addr_select);
                            }
							// remove midle
							else if ( addr_select_point_me != -1){
								data_file.UpdateAddress( addr_select_point_me + length_struct_log - sizeof(long int) , next_addr_select );
								data_file.UpdateAddress( addr_select + length_struct_log - sizeof(long int) , -1  );
							}
							// last 
							else if ( next_addr_select == -1){
								data_file.UpdateAddress( addr_select_point_me + length_struct_log - sizeof(long int) , -1 );
								data_file.UpdateAddress( addr_select + length_struct_log - sizeof(long int) , -1  );
							}
								
							break;
						}
						case 8 : break; 
				    }
	    		} while(option_file < 8);
	    		if (option_file > 7 ) view.Clear();
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