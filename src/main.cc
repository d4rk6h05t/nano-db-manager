

#include <iostream>
#include <cstddef>
#include <string>
#include <fstream>
#include <list>

#include "entity.h"
#include "attribute.h"
#include "data_dictionary_file.h"
#include "view.h"

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

    string file_name;
    string entity_name;
    string attribute_name;

    DataDictionaryFile data_dictionary;

    list<Entity> list_entities;
    list<Attribute> list_attributes;

    do {
    	
		view.ShowTitle();
		view.ShowMainMenu();
	    view.ShowMessage("Select a option >_");
	    cin >> option;

	    switch (option){
	    	case 1: 

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
				    		view.ShowMessage("create file with name ==> " + file_name);
				    		break;
				    	case 2: 
				    		view.ShowMessage("Enter a file name: ");
				    		cin >> file_name;
				    			if ( file_name !="" ){
				    				data_dictionary.SetName( file_name );
				    				view.ShowMessage("open file with name ==> " + file_name);
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

	    	case 2:

	    		do {
	    			 
	    			view.Clear();
		    		view.ShowDictionaryMenu();
		    		view.ShowMessage("Select a option >_");
		    		cin >> option_dictionary;
	    			switch (option_dictionary){
				    	case 1: 

				    		do {
	    			       
				    			view.Clear();
					    		cout << "Size of Entity structure: " << sizeof(Entity) << endl;
					    		view.ShowEntityMenu();
					    		view.ShowMessage("Select a option >_");
					    		cin >> option_entity;
				    			switch (option_entity){
							    	case 1: 
							    		view.ShowMessage("Add Entity");
							    		view.ShowMessage("Enter a new file name: ");
							    		//cout << "size file: " << data_dictionary.GetFileSize() << "Address Next entity: " << data_dictionary.GetFileSize() + sizeof(Entity); 
							    		cin >> entity_name;
							    		if ( entity_name !="" ){
							    			Entity entity(entity_name);

							    			entity.SetEntityAddress( data_dictionary.GetFileSize() );
											entity.SetNextEntityAddress( data_dictionary.GetFileSize() + sizeof(entity) );
											//view.ShowMessage( data_dictionary.GetFileSize() );
											//view.ShowMessage( " / " );
											//view.ShowMessage( sizeof(entity) );
											data_dictionary.AddEntity(entity);
											list_entities.push_back(entity);
							    			view.ShowMessage("create Entity with name ==> ");
							    			view.ShowMessage(entity.GetName());
							    			
							    		}
										break;
							    	case 2: 
							    		view.ShowMessage("Update Entity");
							    		break;
							    	case 3:
							    		view.ShowMessage("Delete Entity");
							    		break;
							    	case 4:
							    		view.ShowMessage("Select Entity");
							    		break;
							    	case 5:
							    		view.ShowMessage("\n::::: \t Metadata of Entity \t :::::\n");
							    	
									    std::cout << "|\t\t Name \t\t | Entity Address | Attribute Address | Data Addres | Next Entity Address |" << endl; 
										for (list<Entity>::iterator it = list_entities.begin(); it != list_entities.end(); ++it)
    										cout << " | " << it->GetName()<< " | " << it->GetEntityAddress()<< " | " << it->GetAttributeAddress()<< " | " << it->GetDataAddress()<< " | " << it->GetNextEntityAddress() << endl;
										
							    		break;
							    }
				    		} while(option_entity < 6);

				    		if (option_entity > 5 ) view.Clear();
				    		break;
				    		
						case 2:

							do {
	    			 
				    			view.Clear();
				    			cout << "Size of Attribute structure: " << sizeof(Attribute) << endl;
					    		view.ShowAttributeMenu();
					    		view.ShowMessage("Select a option >_");
					    		cin >> option_attribute;
				    			switch (option_attribute){
							    	case 1: 
							    		view.ShowMessage("Add Attribute");
							    		break;
							    	case 2: 
							    		view.ShowMessage("Update Attribute");
							    		break;
							    	case 3:
							    		view.ShowMessage("Delete Attribute");
							    		break;
							    	case 4:
							    		view.ShowMessage("Select Attribute");
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
	    		 
	    		case 3:
	    		view.ShowMessage("\t\t Good bye! :'v \n ");
	    		return 0;
	    		break;
	    }
	    
    } while(option <= 3);
    return 0;
    
}