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
#include "view.h"

// namespaces to use
using namespace std; 
using namespace dictionary;
using namespace ui;
using namespace archive;

int main(){ 
	
	View view;
    int option;
    int option_file;
    int option_dictionary;
    int option_entity;
    int option_attribute;

    long int file_header = -1;
    
    string file_name;
    string new_entity;
    string remove_entity;
    string attribute_name;

    DataDictionary data_dictionary;
    DataFile data_file;

    Entity current_entity;

	string min;
	string current_entity_name;

	long int entity_address_min;
	long int entity_next_address_min;

	list<Attribute> list_attributes;

    do {    	
		view.ShowTitle();
		view.ShowMainMenu();
	    view.ShowMessage("\n\t\t Select a option >_");
	    cin >> option;

	    switch (option){
	    	case 1: /* :::::::::::::::: F i l e  M e n u  ::::::::::::::::::::::::: */ 

	    		do {
	    			view.Clear();
		    		view.ShowFileMenu();
		    		view.ShowMessage("\n\t\t Select a option >_");
		    		cin >> option_file;
	    			switch (option_file){
				    	case 1: /* ::::::::::: N e w   f i l e  ::::::::::  */ 
				    		view.ShowMessage("\n\t\tEnter a new file name: ");
				    		cin >> file_name;
				    		if ( file_name !="" ){
				    			data_dictionary.SetName( file_name );
				    			data_dictionary.CreateFile();
				    		}
				    		break;
				    	case 2: /* ::::::::::: O p e n  f i l e  ::::::::::  */
				    		view.ShowStatusBar(data_dictionary.GetName(), data_dictionary.GetFileHeader(), data_dictionary.GetFileSize() );
				    		view.ShowMessage("\n\t\tEnter a file name: ");
				    		cin >> file_name;
				    			if ( file_name !="" ){
				    				data_dictionary.SetName( file_name );
				    			}
				    		break;
				    	case 3:/* ::::::::::: R e m o ve   f i l e  ::::::::::  */
				    		view.ShowMessage("\n\t\tEnter a new file name: ");
				    		cin >> file_name;
				    		view.ShowMessage("Deleted file with name ==> " + file_name);
				    		break;
				    }
	    		} while(option_file < 4);
	    		if (option_file > 3 ) view.Clear();
	    			break;
	    	case 2:  /* :::::::::::::::::::::::::::: D i c  t i  o n a r  y   M e n u  ::::::::::::::::::::::::::::::::::::::: */ 

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
							    	case 1: /*  :::::::::::  N e w   E n t i t y  ::::::::::  */
							    		view.ShowMessage("\n\t\t===> Add Entity ::: Enter a new entity name: ");
							    		cin >> new_entity;
							    		if ( new_entity !="" ){
										    Entity entity(new_entity);
										    entity.SetEntityAddress( data_dictionary.GetFileSize() ); 
									        data_dictionary.UpdateEntity( data_dictionary.ReadListEntities(), &entity); 								        
									        data_dictionary.AddEntity( entity );
										}
										break;
							    	case 2: /*  :::::::::::  U p d a t e  E n t i t y  ::::::::::  */
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
							    	case 3: /*  :::::::::::  R e m o v e   E n t i t y  ::::::::::  */
							    		view.ShowMessage("\n\t\t===> Remove Entity ::: Enter entity name: ");
							    		cin >> remove_entity;
							    		if ( remove_entity !="" ){
							    			data_dictionary.RemoveEntity(data_dictionary.ReadListEntities() ,remove_entity);
							    		}	
							    		break;
							    	case 4: /*  :::::::::::  S e l e c t  E n t i t y  ::::::::::  */
							    		view.ShowMessage("===> Select Entity");
							    		break;
							    	case 5:/*  :::::::::::  S h o w  L i s t  o f   E n t i t i e s  ::::::::::  */
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
							//string current_entity_name;
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
										    	case 1: /*  :::::::::::  N e w   A t t r i b u t e  ::::::::::  */
										    		//view.ShowMessage("===> Add Attribute");
										    		

										    		view.ShowMessage("\n\t\t===> Add Entity ");
										    		view.ShowMessage("\n\t\t:: Enter a new attribute name: ");
										    		cin >> attr_name;
										    		
										    		if ( attr_name != "" ){
										    			view.ShowMessage("\n\t\t:: Enter data type: ");
											    		cin >> attr_data_type;
											    		if ( attr_data_type != '\0'  ){
											    			view.ShowMessage("\n\t\t:: Enter lenngth of data type: ");
												    		cin >> attr_length;
												    		if ( attr_length > 0 ){
												    			view.ShowMessage("\n\t\t:: Enter type index: ");
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
													    		}	
												    		}	
											    		}
													    
													}
										    		break;
										    	case 2: /*  :::::::::::  U p d a t e   A t t r i b u t e  ::::::::::  */
										    		view.ShowMessage("===> Update Attribute");
										    		break;
										    	case 3: /*  :::::::::::  R e m o v e    A t t r i b u t e  ::::::::::  */
										    		view.ShowMessage("===> Delete Attribute");
										    		break;
										    	case 4: /*  :::::::::::  S e l e c t   A t t r i b u t e  ::::::::::  */
										    		view.ShowMessage("===>Select Attribute");
										    		break;
										    	case 5: /*  :::::::::::  S h o w  l i s t   o f  A t t r i b u t e s  ::::::::::  */
										    		view.ShowMessage("===>Show list entities");
										    		current_entity = data_dictionary.SearchEntity( data_dictionary.ReadListEntities(), current_entity_name);
										    		view.ShowListAttributes( data_dictionary.ReadListAttributes(current_entity) );
										    		break;
										    	case 6: /*  ::::::::::: E x i t  ::::::::::  */
										    		view.ShowMessage("===>Return back");
										    		break;
										    }
										} while(option_attribute < 6);
					    					if (option_attribute > 5 ) view.Clear();
					    					break;		
				    				} 
				    			}

				    			
				    		
				    }
	    		} while(option_dictionary < 3);
	    		if (option_dictionary > 2 ) view.Clear();
	    		break;
	    		case 3:  /* :::::::::::::::: Data file  M e n u  ::::::::::::::::::::::::: */ 

	    		//string current_entity_name;
				view.ShowMessage("\n\t\t ::: select an entity to work with :");
				cin >> current_entity_name;

				if ( current_entity_name !="" ){
					current_entity = data_dictionary.SearchEntity( data_dictionary.ReadListEntities(), current_entity_name);
				    if ( current_entity.GetEntityAddress() != -1 ){

	    		do {
	    			view.Clear();
		    		view.ShowDataFileMenu();
		    		view.ShowMessage("\n\t\t Select a option >_");
		    		cin >> option_file;
	    			switch (option_file){
                        /* ::::::::::: A d d   R e g i s t e  r  ::::::::::  */
				    	case 1: {
				    		int current_length_structure = 0;
				    		data_file.SetName( current_entity_name );
				    		data_file.CreateFile();
				    		view.ShowStatusBar(data_file.GetName(), 0 , data_file.GetFileSize() );
				    		list_attributes = data_dictionary.ReadListAttributes(current_entity);
				    		
				    		//if ( data_file.GetFileHeader() == -1){
				    			//data_file.SetFileHeader( data_file.GetFileSize() );
				    			//data_file.UpdateHeader();
				    			data_dictionary.UpdateAddress( current_entity.GetEntityAddress() + 35 + 8 + 8 , 0 );
				    		//}
                            cout << endl << "data_file.GetFileSize(): " << data_file.GetFileSize() << endl;
				    		data_file.UpdateAddress( data_file.GetFileSize(), data_file.GetFileSize() ); // address
				    		current_length_structure = current_length_structure + sizeof(long int); 
				    		cout << endl << ":: current_length_structure: " << current_length_structure << ": ";
				    		for (list<Attribute>::iterator it = list_attributes.begin(); it != list_attributes.end() ; ++it){
				    			
				    			cout << endl << ":: " << it->GetName() << ": ";

				    			if ( it->GetDataType() == 'c' ){
				    				char str[ it->GetLengthDataType() ];
				    				cin >> str;
				    				data_file.AppendCharData(str, it->GetLengthDataType() );
				    				current_length_structure = current_length_structure + it->GetLengthDataType();
				    				cout << endl << ":: current_length_structure: +str " << current_length_structure << ": "; 
				    			} else if ( it->GetDataType() == 'i' ){
				    				int  x;
				    				cin >> x;
				    				data_file.AppendIntData(x);
				    				current_length_structure = current_length_structure + sizeof(int);
				    				cout << endl << ":: current_length_structure: +int" << current_length_structure << ": ";
				    			}
				    			
				    			   	
				    		} 
				    		cout << endl << ":: current_length_structure: finally" << current_length_structure << ": ";
				    		data_file.UpdateAddress( current_length_structure , -1 ); // next address
				    		
				    		
				    			
				    		break;
				    	} 
				    		
				    	case 2: /* ::::::::::: O p e n  f i l e  ::::::::::  */
				    		cout << "->";
				    		break;
				    	case 3:/* ::::::::::: S h o w   d a t a    f i l e  ::::::::::  */
				    		view.ShowMessage("===>Show data file");

				    		view.ShowStatusBar(data_file.GetName(), 0, data_file.GetFileSize() );
				    		
							current_entity = data_dictionary.SearchEntity( data_dictionary.ReadListEntities(), current_entity_name);
							
							list_attributes = data_dictionary.ReadListAttributes(current_entity);

							data_file.ReadRegister( current_entity, data_dictionary.ReadListAttributes(current_entity) );
							//view.ShowListAttributes( data_dictionary.ReadListAttributes(current_entity) );
				    		break;
				    }
	    		} while(option_file < 4);
	    		if (option_file > 3 ) view.Clear();
	    			break;

	    		}
	    	}


	    		case 4:  /* :::::::::::::::: Exit  M e n u  ::::::::::::::::::::::::: */ 
	    			view.ShowMessage("::: ===> Good bye! :'v \n ");
	    			return 0;
	    			break;
	    }
    } while(option <= 4);
    return 0;
    
}