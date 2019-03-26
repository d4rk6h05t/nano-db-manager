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
										    Entity entity(new_entity);
										    entity.SetEntityAddress( data_dictionary.GetFileSize() ); 
									        data_dictionary.UpdateEntity( data_dictionary.ReadListEntities(), &entity); 								        
									        data_dictionary.AddEntity( entity );
										}
										break;
							    	case 2: 
							    		view.ShowMessage("===> Update Entity ::: First, Select a entity for update: ");
							    		cin >> new_entity;
							    		if ( new_entity !="" ){
							    			Entity entity_selected = data_dictionary.SearchEntity( data_dictionary.ReadListEntities(), new_entity);
							    			if(entity_selected.GetEntityAddress() != -1 ){
							    				string new_name;
								    			view.ShowMessage("===> Change name entity ::: Enter new entity name: ");
								    			cin >> new_name;
								    			if ( new_name !="" ){
								    				data_dictionary.UpdateName( entity_selected.GetEntityAddress(), new_name );
								    			}	
							    			} else {
							    				view.ShowMessage("===> I'm sorry not found entity ");
							    			}		
										} // first end if != ""
							    		break;
							    	case 3:
							    		view.ShowMessage("===> Remove Entity ::: Enter entity name: ");
							    		cin >> remove_entity;
							    		if ( remove_entity !="" ){
							    			data_dictionary.RemoveEntity(remove_entity);
							    		}	
							    		break;
							    	case 4:
							    		view.ShowMessage("===> Select Entity");
							    		break;
							    	case 5:
							    		view.ShowListEntities( data_dictionary.ReadListEntities() );
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
				    		//break;
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