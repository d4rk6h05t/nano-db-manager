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
#include "data_dictionary.h"
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
				    		cout << endl << "\t\t:: File Name [ " << data_dictionary.GetName() 
					    	     << " ] :: File Header [" << data_dictionary.GetFileHeader() << "]" 
					    	     << " ] :: File Size [" << data_dictionary.GetFileSize() << "]" <<endl; 
				    		view.ShowMessage("Enter a file name: ");
				    		cin >> file_name;
				    			if ( file_name !="" ){
				    				data_dictionary.SetName( file_name );
				    				view.ShowMessage("open file with name ==> " + file_name);
				    				list_entities = data_dictionary.ReadListEntities();
				    				cout << endl << "\t\t::::::::::::: \t Metadata of Entity \t ::::::::::::" << endl << endl;
										std::cout << " Name  \t Entity Address  Attribute Address  Data Addres  Next Entity Address " << endl << endl; 
	
										for (list<Entity>::iterator it = list_entities.begin(); it != list_entities.end(); ++it)
    										cout << it->GetName() 
    											 << "\t\t" << it->GetEntityAddress() 
    											 << "\t\t" << it->GetAttributeAddress()
    											 << "\t\t" << it->GetDataAddress()
    											 << "\t\t" << it->GetNextEntityAddress() 
    											 << endl;
    								

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
					    		cout << endl << "\t\t:: File Name [ " << data_dictionary.GetName() 
					    			 << " ] :: File Header [" << data_dictionary.GetFileHeader()  
					    			 << " ] :: File Size [" << data_dictionary.GetFileSize() << "]" <<endl;
					    		view.ShowEntityMenu();
					    		view.ShowMessage("Select an option >_");
					    		cin >> option_entity;
				    			switch (option_entity){
							    	case 1: 
							    		view.ShowMessage("===> Add Entity ::: Enter a new entity name: ");
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
										    	entity_address_min = data_dictionary.GetFileSize();
										    	entity_next_address_min = end_address;
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
										    				entity_address_min = data_dictionary.GetFileSize();
										    				entity_next_address_min = it_current->GetEntityAddress();
										    				it_position = i ; // first position
										    				
										    			} else if ( comparison_response > 0 ) {										    	
										    			    flag = 1;
										    			    min = it_current->GetName();
										    			    entity_address_min = it_current->GetEntityAddress();
										    				entity_next_address_min = data_dictionary.GetFileSize();
										    			    it_position = i + 1; // secon position			
										    			} 
										    		} else if ( i > 0 ) {
										    			flag = 2;
    													 
    													int comparison_response_next = strcmp( char_new_entity, char_current_entity );
    													
    													if ( comparison_response_next < 0 ){
                                                        	min = new_entity;
    														entity_address_min = data_dictionary.GetFileSize();
    														entity_next_address_min = it_current->GetEntityAddress();
    														
                                                        } else if ( comparison_response_next > 0 ){
    														min = it_current->GetName();
                                                        	entity_address_min = it_current->GetEntityAddress();
                                                        	entity_next_address_min = data_dictionary.GetFileSize();
    													}
                                                        
										    			int length_min_new_entity = min.length();  
														char char_min_new_entity[ length_min_new_entity + 1 ];
														strcpy( char_min_new_entity, min.c_str() );

										    			int comparison_response_current_min = strcmp( char_new_entity, char_min_new_entity );
										    			if ( comparison_response_current_min < 0 ) {
                                                        	it_position = i - 1;
										    				
										    				break;
										    			} else if ( comparison_response_current_min > 0 ) {
										    				it_position = i + 1;
										    			}
										    		} // end if else
										    		
										    		i++;
                                                    it_previus++;
										    		it_current++;
										    		it_next++;	
										    	} // end while
										    } // end else != empty list
											

											list<Entity>::iterator current = list_entities.begin();
											list<Entity>::iterator previus = std::prev( current , 1 );
										    list<Entity>::iterator next = std::next( current , 1 );

											int it_count = 0;

											if ( flag == -1 ){
												list_entities.push_back(entity); 
											} else if ( flag == 0 || it_position == 0){
												
												entity.SetNextEntityAddress( list_entities.front().GetEntityAddress() );
												list_entities.push_front(entity);
											
											} else if ( flag == 1 ){
												
												list_entities.front().SetNextEntityAddress( data_dictionary.GetFileSize() );
												data_dictionary.UpdateAddress( list_entities.front().GetEntityAddress() , data_dictionary.GetFileSize() );
												entity.SetNextEntityAddress( end_address );
												list_entities.push_back(entity);
											
											} else if ( flag == 2  ){
																								
												do {

													if ( it_count == it_position ){
														
														long int previus_next_entity = previus->GetNextEntityAddress();
														previus->SetNextEntityAddress( data_dictionary.GetFileSize() );
														data_dictionary.UpdateAddress( previus->GetEntityAddress() , data_dictionary.GetFileSize() );
														entity.SetNextEntityAddress( previus_next_entity ); 
                                                		list_entities.insert(current,entity);  	
                                                  	}

												  	it_count++;
                                                  	next++; 
                                                  	current++; 
                                                  	previus++; 
												} while ( it_count <= it_position );	
											}
											data_dictionary.SetFileHeader( list_entities.front().GetEntityAddress() );
                                            data_dictionary.UpdateHeader();
                                            data_dictionary.AddEntity( entity );
											
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
							    		cout << endl << "\t\t:: File Name [ " << data_dictionary.GetName() 
					    			 		 << " ] :: File Header [" << data_dictionary.GetFileHeader() << "]" 
					    			 		 << " ] :: File Size [" << data_dictionary.GetFileSize() << "]" <<endl;
							    		cout << endl << "\t\t::::::::::::: \t Metadata of Entity \t ::::::::::::" << endl << endl;
										std::cout << " Name  \t Entity Address  Attribute Address  Data Addres  Next Entity Address " << endl << endl; 
	
										for (list<Entity>::iterator it = list_entities.begin(); it != list_entities.end(); ++it)
    										cout << it->GetName() 
    											 << "\t\t" << it->GetEntityAddress() 
    											 << "\t\t" << it->GetAttributeAddress()
    											 << "\t\t" << it->GetDataAddress()
    											 << "\t\t" << it->GetNextEntityAddress() 
    											 << endl;
										
							    		break;
							    }
				    		} while(option_entity < 6);

				    		if (option_entity > 5 ) view.Clear();
				    		break;
				    		
						case 2:

							do {
	    			 
				    			view.Clear();
				    			cout << endl << "\t\t:: File Name [ " << data_dictionary.GetName() 
					    			 << " ] :: File Header [" << data_dictionary.GetFileHeader() << "]" 
					    			 << " ] :: File Size [" << data_dictionary.GetFileSize() << "]" <<endl;
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
	    		 
	    		case 3:
	    		view.ShowMessage("::: ===> Good bye! :'v \n ");
	    		return 0;
	    		break;
	    }
	    
    } while(option <= 3);
    return 0;
    
}