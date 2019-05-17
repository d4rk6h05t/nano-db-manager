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
#include "index.h"
#include "data_dictionary.h"
#include "data_file.h"
#include "index_file.h"
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
										    		view.ShowMessage("===>Show list entities");
										    		current_entity = data_dictionary.SearchEntity( data_dictionary.ReadListEntities(), current_entity_name);
										    		view.ShowListAttributes( data_dictionary.ReadListAttributes(current_entity) );
										    		break;
										    	}
										    	case 6: view.ShowMessage("===> Return back"); break;
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
				    if ( current_entity.GetEntityAddress() != -1 ){
				    	data_file.SetName( current_entity_name );
				    	data_file.CreateFile();

				    	list<Attribute> list_attributes = data_dictionary.ReadListAttributes( current_entity );
						for( list<Attribute>::iterator i = list_attributes.begin(); i != list_attributes.end(); i++ ){
							
							string attr_name( i->GetName() );
							if ( i->GetTypeIndex() == 1 || i->GetTypeIndex() == 2 ){
								IndexFile index_file( attr_name , i->GetTypeIndex()  );
								index_file.CreateFile();
								index_file.CreateBlock( 0 );
								list< pair< int, long int> > block_int = IndexFile::ReadBlock(attr_name, 0 );
							} 		
							//cout << ":: Name attr : " << attr_name << " :: type index attr : " << i->GetTypeIndex();
							//data_file.UpdateAddress( i->GetAttributeAddress() + 35 + 1 + 4 + 8 + 4 , 0 );
						}
				    } else {
				    	data_file.SetName( current_entity_name );
				    	//data_file.SetFileHeader(  );
				    } 
				    	list<string> list_data;
	    		do {
	    			view.Clear();
		    		view.ShowDataFileMenu();
		    		view.ShowMessage("\n\t\t Select a option >_");
		    		cin >> option_file;
	    			switch (option_file){
				    	case 1: { // Add new Register
				    		view.ShowStatusBar(data_file.GetName(),  data_file.GetFileHeader() , data_file.GetFileSize() );
				    		//if ( current_entity.GetDataAddress() == -1 )
				    		data_dictionary.UpdateAddress( current_entity.GetEntityAddress() + 35 + 8 + 8 , data_file.GetFileHeader() );
				    		data_file.AppendData(list_attributes,list_data);
				    		//data_dictionary.UpdateAddress(   , data_file.GetFileHeader() );
				    		//  UPDATE DATA ADDRESS FOR ENTITY && FOR ATTR INDEX ADDRESS
				    		break;
				    	} 
				    	case 2: {// Show primary Index
				    		cout << "\t\t::::: Show Primary Index ::::";
				    		cout << endl << "data \t data address";
				    		for( list<Attribute>::iterator j = list_attributes.begin(); j != list_attributes.end(); j++ ){
								if ( j->GetTypeIndex() == 1 || j->GetTypeIndex() == 2 ){
									string attr_name_show( j->GetName() );
									list< pair< int, long int> > block = IndexFile::ReadBlock(attr_name_show, 0 );
									for( list< pair< int, long int> >::iterator k = block.begin(); k != block.end(); k++ ){
										cout << endl << k->first << " \t " << k->second;
									}
								} 
							}
				    		break;
				    	}
				    	case 3 : { // Show Data File
				    		view.ShowMessage("===> Show data file");
				    		view.ShowStatusBar(data_file.GetName(), data_file.GetFileHeader(), data_file.GetFileSize() );
							current_entity = data_dictionary.SearchEntity( data_dictionary.ReadListEntities(), current_entity_name);
							data_file.ReadRegister( data_dictionary.ReadListAttributes(current_entity) );
							break;
						}
				    }
	    		} while(option_file < 4);
	    		if (option_file > 3 ) view.Clear();
	    			break;
	    		//}
	    	} //  end if current_entity
	    		case 4:  // Exit 
	    			view.ShowMessage("::: ===> Good bye! :'v \n ");
	    			return 0;
	    			break;
	    }
    } while(option <= 4);
    return 0;  
}