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
#include "view.h"

// namespaces to use
using namespace std; 
using namespace dictionary;
using namespace ui;

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

	string min;
	long int entity_address_min;
	long int entity_next_address_min;

    list<Entity> list_entities;
    list<Attribute> list_attributes;

    do {    	
		view.ShowTitle();
		view.ShowMainMenu();
	    view.ShowMessage("Select a option >_");
	    cin >> option;

	    switch (option){
	    	case 1: /* :::::::::::::::: F i l e  M e n u  ::::::::::::::::::::::::: */ 

	    		do {
	    			 
	    			view.Clear();
		    		view.ShowFileMenu();
		    		view.ShowMessage("Select a option >_");
		    		cin >> option_file;
	    			switch (option_file){
				    	case 1: 
				    		view.ShowMessage("Enter a new file name: ");
				    		cin >> file_name;
				    		if ( file_name !="" ){
				    			data_dictionary.SetName( file_name );
				    			data_dictionary.CreateFile();
				    		}
				    		break;
				    	case 2:
				    		view.ShowStatusBar(data_dictionary.GetName(), data_dictionary.GetFileHeader(), data_dictionary.GetFileSize() );
				    		view.ShowMessage("Enter a file name: ");
				    		cin >> file_name;
				    			if ( file_name !="" ){
				    				data_dictionary.SetName( file_name );
				    				list_entities = data_dictionary.ReadListEntities();
				    			}
				    		break;
				    	case 3:
				    		view.ShowMessage("Enter a new file name: ");
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
		    		view.ShowMessage("Select an option >_");
		    		cin >> option_dictionary;
	    			switch (option_dictionary){
				    	case 1: 
				    		do {       
				    			view.Clear();
					    		view.ShowStatusBar(data_dictionary.GetName(), data_dictionary.GetFileHeader(), data_dictionary.GetFileSize() );
					    		view.ShowEntityMenu();
					    		view.ShowMessage("Select an option >_");
					    		cin >> option_entity;
				    			switch (option_entity){
							    	case 1: 
							    		view.ShowMessage("===> Add Entity ::: Enter a new entity name: ");
							    		cin >> new_entity;
							    		if ( new_entity !="" ){
/***********************************************************************************************************************************************/
										    Entity entity(new_entity);
										    entity.SetEntityAddress( data_dictionary.GetFileSize() ); 
									        data_dictionary.UpdateEntity(&entity); 								        
									        data_dictionary.AddEntity( entity );
									       	list_entities = data_dictionary.ReadListEntities();
									        if (	list_entities.empty() )
									       		cout << "( ) more empty" << list_entities.front().GetEntityAddress();
									        else
									        	cout << "->" << list_entities.front().GetEntityAddress();

									        //data_dictionary.SetFileHeader( list_entities.front().GetEntityAddress() );
                                            //data_dictionary.UpdateHeader(  );
                                            
/********************************************************************************************************************************************/				    		
										}
										break;
							    	case 2: 

							    		view.ShowMessage("===> Update Entity ::: First, Select a entity for update: ");
							    		
							    		cin >> new_entity;
							    		
							    		if ( new_entity !="" ){
							    
							    			if( new_entity == list_entities.front().GetName() )
							    				data_dictionary.SetFileHeader( list_entities.front().GetNextEntityAddress() );
							    			
							    			list<Entity>::iterator it = list_entities.begin();
							    			list<Entity>::iterator prev = std::prev( it , 1 );
												
											while ( it != list_entities.end() ){
												if ( new_entity == it->GetName() ){
													it->SetNextEntityAddress( it->GetNextEntityAddress() );
													data_dictionary.UpdateAddress( prev->GetEntityAddress(), it->GetNextEntityAddress() );														
													list_entities.erase( it );		
													break;												
												}

											it++;
											prev++;
											}

												} // first end if != ""
							    		break;
							    	case 3:
							    		view.ShowMessage("===> Remove Entity ::: Enter entity name: ");
							    		cin >> remove_entity;
							    		if ( remove_entity !="" ){
							    			
							    			if( remove_entity == list_entities.front().GetName() )
							    				data_dictionary.SetFileHeader( list_entities.front().GetNextEntityAddress() );

							    			list<Entity>::iterator it_current = list_entities.begin();
							    			list<Entity>::iterator it_previus = std::prev( it_current , 1 );
											
											while ( it_current != list_entities.end() ){

												if ( remove_entity == it_current->GetName() ){
												
													it_previus->SetNextEntityAddress( it_current->GetNextEntityAddress() );
													data_dictionary.UpdateAddress( it_previus->GetEntityAddress() , it_current->GetNextEntityAddress() );
													it_current->SetNextEntityAddress(-1);
													data_dictionary.UpdateAddress(it_current->GetNextEntityAddress(), -1 );
													list_entities.erase( it_current );
													break;												
												}

											it_current++;
											it_previus++;
											}

							    		}
                                        

							    		break;
							    	case 4:
							    		view.ShowMessage("===> Select Entity");
							    		break;
							    	case 5:
							    		view.ShowStatusBar(data_dictionary.GetName(), data_dictionary.GetFileHeader(), data_dictionary.GetFileSize() );
							    		view.ShowListEntities(list_entities);
							    		break;
							    }
				    		} while(option_entity < 6);

				    		if (option_entity > 5 ) view.Clear();
				    		break;
				    		
						case 2: 

							do {
	    			 
				    			view.Clear();
				    			view.ShowStatusBar(data_dictionary.GetName(), data_dictionary.GetFileHeader(), data_dictionary.GetFileSize() );
				    			view.ShowAttributeMenu();
					    		view.ShowMessage("\nSelect an option >_");
					    		cin >> option_attribute;
				    			switch (option_attribute){
							    	case 1: 
							    		view.ShowMessage("===> Add Attribute");
							    		break;
							    	case 2: 
							    		view.ShowMessage("===> Update Attribute");
							    		break;
							    	case 3:
							    		view.ShowMessage("===> Delete Attribute");
							    		break;
							    	case 4:
							    		view.ShowMessage("===>Select Attribute");
							    		break;
							    }
				    		} while(option_attribute < 5);

				    		if (option_attribute > 4 ) view.Clear();
				    		break;

				    		break;
				    }

	    		} while(option_dictionary < 3);

	    		if (option_dictionary > 2 ) view.Clear();
	    		break;
	    		 
	    		case 3:  /* :::::::::::::::: Exit  M e n u  ::::::::::::::::::::::::: */ 
	    			view.ShowMessage("::: ===> Good bye! :'v \n ");
	    			return 0;
	    			break;
	    }
	    
    } while(option <= 3);
    return 0;
    
}