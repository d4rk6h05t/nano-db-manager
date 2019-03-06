

#include <iostream>
#include <cstddef>
#include <string>
#include <fstream>
#include <list>
#include <vector>
#include <iterator> 
#include <algorithm> 


#include <bits/stdc++.h> 

#include "entity.h"
#include "attribute.h"
#include "data_dictionary_file.h"
#include "view.h"

using namespace std; 
using namespace dictionary;
using namespace ui;

typedef unsigned char BYTE;

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
    string attribute_name;

    DataDictionaryFile data_dictionary;

	string min;    
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
				    				list_entities = data_dictionary.ReadListEntities();
                                    //vector<BYTE> v = data_dictionary.readFile();

				    				view.ShowMessage("\n::::: \t Metadata of Entity \t :::::\n");
							    	
									std::cout << "|  Name  | Entity Address | Attribute Address | Data Addres | Next Entity Address |" << endl; 
									for (list<Entity>::iterator it = list_entities.begin(); it != list_entities.end(); ++it)
    										cout << " | " << it->GetName()<< " | " << it->GetEntityAddress()<< " | " << it->GetAttributeAddress()<< " | " << it->GetDataAddress()<< " | " << it->GetNextEntityAddress() << endl;
    								//for (int i = 0; i < v.size(); i++){
    								//	cout << v[i] << endl; 	
    								//}

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
		    		view.ShowMessage("Select an option >_");
		    		cin >> option_dictionary;
	    			switch (option_dictionary){
				    	case 1: 

				    		do {
	    			       
				    			view.Clear();
					    		cout << endl << ":::::::::::::  File Header [ "<< data_dictionary.GetFileHeader() << " ]::::::::::::" << endl;
					    		view.ShowEntityMenu();
					    		view.ShowMessage("Select an option >_");
					    		cin >> option_entity;
				    			switch (option_entity){
							    	case 1: 
							    		view.ShowMessage("Add Entity");
							    		view.ShowMessage("Enter a new entity name: ");
							    		cin >> new_entity;

							    		if ( new_entity !="" ){
											
							    			int n = new_entity.length();  
										    char char_new_entity[ n + 1];    
										    strcpy(char_new_entity, new_entity.c_str());  

										    Entity entity(new_entity);
										    entity.SetEntityAddress( data_dictionary.GetFileSize() ); 
										    
										    long int previus_address, current_address, next_address, start_address, end_address;
                                            start_address = data_dictionary.GetFileSize();
                                            end_address = -1;

                                            list<Entity>::iterator it_current = list_entities.begin();
										    list<Entity>::iterator it_previus = std::prev( it_current , 1 );
										    list<Entity>::iterator it_next = std::next( it_current , 1 );

										    int i = 0; // first position
										    int it_position = i;
										    int flag;
										    if( list_entities.empty() ) {
										    	min = new_entity;
										    	data_dictionary.SetFileHeader( start_address );
										    	flag = -1; 
										    } else {
										    	while ( it_current != list_entities.end()  ){
										    		string current_entity( it_current->GetName() );
					    							int length_current_entity = current_entity.length();  
													char char_current_entity[ length_current_entity + 1 ];
													strcpy( char_current_entity, current_entity.c_str() );

    												int comparison_response = strcmp( char_new_entity, char_current_entity );
	    											
	    											previus_address = it_previus->GetNextEntityAddress();
													current_address = it_current->GetEntityAddress();
										    		next_address = it_current->GetNextEntityAddress();
										    		
										    		if ( i == 0  ){
										    			if ( comparison_response < 0 ) {
										    				flag = 0;
										    				min = new_entity;
										    				it_position = i ; // first position
										    				data_dictionary.SetFileHeader( start_address );
										    				
										    			} else if ( comparison_response > 0 ) {										    	
										    			    flag = 1;
										    			    min = it_current->GetName();
										    			    it_position = i + 1; // secon position			
										    				data_dictionary.SetFileHeader( current_address );	
										    			} 
										    		} else if ( i > 0 ) {
										    			flag = 2;
    													min = new_entity;
    													long int entity_address_min = data_dictionary.GetFileSize();
    													long int entity_next_address_min = it_current->GetEntityAddress(); 
    													int comparison_response_next = strcmp( char_new_entity, char_current_entity );
    													
    													if ( comparison_response_next > 0 ){
                                                        	min = it_current->GetName();
                                                        	entity_address_min = it_current->GetEntityAddress();
                                                        	int entity_next_address_min = data_dictionary.GetFileSize();
    													}
                                                        
                                                        cout << endl << "new min -> " << min  << endl;
										    			int length_min_new_entity = min.length();  
														char char_min_new_entity[ length_min_new_entity + 1 ];
														strcpy( char_min_new_entity, min.c_str() );

										    			int comparison_response_current_min = strcmp( char_new_entity, char_min_new_entity );
										    			if ( comparison_response_current_min < 0 ) {
                                                        	it_position = i - 1;
                                                        	data_dictionary.SetFileHeader( 	data_dictionary.GetFileSize() );
										    				break;
										    			} else if ( comparison_response_current_min > 0 ) {
										    				it_position = i + 1;
										    				data_dictionary.SetFileHeader( it_current->GetEntityAddress() );	
										    			}
										    		} // end if else
										    		
										    		i++;
                                                    it_previus++;
										    		it_current++;	
										    	} // end while
										    } // end else != empty list
											

											list<Entity>::iterator current = list_entities.begin();
											list<Entity>::iterator previus = std::prev( current , 1 );
										    list<Entity>::iterator next = std::next( current , 1 );

											int it_count = 0;

											if ( flag == -1 ){
												list_entities.push_back(entity); 
											} else if ( flag == 0 || it_position == 0){
												
												entity.SetNextEntityAddress( current->GetEntityAddress() );
												list_entities.push_front(entity);
											
											} else if ( flag == 1 ){

												current->SetNextEntityAddress( data_dictionary.GetFileSize() );
												entity.SetNextEntityAddress( end_address );
												list_entities.push_back(entity);
											
											} else if ( flag == 2  ){
												
												
												do {



													if ( it_count == it_position ){
														long int previus_next_entity = previus->GetNextEntityAddress();
														previus->SetNextEntityAddress( data_dictionary.GetFileSize() );
														entity.SetNextEntityAddress( previus_next_entity ); 
                                                		list_entities.insert(current,entity);  	
                                                  	}

												  	it_count++;
                                                  	next++; 
                                                  	current++; 
                                                  	previus++; 
												} while ( it_count <= it_position );
												
											}

											data_dictionary.UpdateListEntities(list_entities, data_dictionary.GetFileHeader() );
							    			view.ShowMessage(" / create Entity with name ==> ");
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