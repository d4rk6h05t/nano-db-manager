
#include "view.h"

namespace ui {

		View::View(){}
		
		View::~View(){}
		
		void View::Clear(){ system("clear"); }
		
		void View::ShowTitle(){ std::cout << std::endl << "\t\t Project Structure File "<< std::endl; }
		
		void View::ShowMessage(std::string str ){ std::cout << std::endl << std::endl << " \t " + str;  }

		void View::ShowStatusBar(std::string name, long int header, long int size ){
			
			std::cout << std::endl << "\t\t:: File Name [ " << name 
					  << " ] :: File Header [" << header 
					  << " ] :: File Size [" << size << "]" << std::endl;
		}

		void View::ShowListEntities(std::list<dictionary::Entity> list_entities){
   			
   			std::cout << std::endl 
   				<< std::left << std::setw(35) << std::setfill('-') << std::left 
   				<< '+' << std::setw(17) << std::setfill('-') << std::left 
   				<< '+' << std::setw(20) << std::setfill('-') << std::left
   				<< '+' << std::setw(15) << std::setfill('-') << std::left 
   				<< '+' << std::setw(22) << std::setfill('-')
		        << '+' << '+' << std::endl;

		   	std::cout << std::setfill(' ') << '|' 
		   		<< std::setw(34)  << " Name " << std::setfill(' ') << '|' 
		   		<< std::setw(13)  << " Entity Address " << std::setfill(' ') << '|' 
		   		<< std::setw(13)  << " Attribute Address " << std::setfill(' ') << '|' 
		   		<< std::setw(13)  << " Data Address " << std::setfill(' ') << '|' 
		   		<< std::setw(13)  << " Next Entity Address " << '|' << std::endl;

	        std::cout 
   				<< std::left << std::setw(35) << std::setfill('-') << std::left 
   				<< '+' << std::setw(17) << std::setfill('-') << std::left 
   				<< '+' << std::setw(20) << std::setfill('-') << std::left
   				<< '+' << std::setw(15) << std::setfill('-') << std::left 
   				<< '+' << std::setw(22) << std::setfill('-')
		        << '+' << '+' << std::endl;
			//std::cout << " Name  \t Entity Address  Attribute Address  Data Addres  Next Entity Address " << std::endl << std::endl; 
	
			for (std::list<dictionary::Entity>::iterator it = list_entities.begin(); it != list_entities.end(); ++it){
    			
    			std::string name( it->GetName() );
    			std::string entity_address = std::to_string( it->GetEntityAddress() );
    			std::string attribute_address = std::to_string( it->GetAttributeAddress() );
    			std::string data_address = std::to_string( it->GetDataAddress() );
    			std::string next_entity_address = std::to_string( it->GetNextEntityAddress() );
    		
    			int length_name = 34 - (name.length() + 1);
    			int length_entity_address = 16 - ( entity_address.length() + 1);
    			int length_attribute_address = 19 - (attribute_address.length() + 1);
    			int length_data_address = 14 - (data_address.length() + 1);
    			int length_next_entity_address = 21 - (next_entity_address.length() + 1);

    			std::cout << std::setfill(' ') << '|' 
    				<< " " << it->GetName() << std::setw(length_name) << " " <<  '|' // name
    				<< " " << it->GetEntityAddress() << std::setw(length_entity_address) << " " <<  '|' // entity address
    				<< " " << it->GetAttributeAddress() << std::setw(length_attribute_address) << " " <<  '|' // attribute address
    				<< " " << it->GetDataAddress() << std::setw(length_data_address) << " " <<  '|' // data  address
    				<< " " << it->GetNextEntityAddress() << std::setw(length_next_entity_address) << " " <<  '|' // next entity address
					<< std::endl;
			}
			/*
			std::cout 
   				<< std::left << std::setw(35) << std::setfill('-') << std::left 
   				<< '+' << std::setw(17) << std::setfill('-') << std::left 
   				<< '+' << std::setw(20) << std::setfill('-') << std::left
   				<< '+' << std::setw(15) << std::setfill('-') << std::left 
   				<< '+' << std::setw(22) << std::setfill('-')
		        << '+' << '+' << std::endl;
		    */
    								
		}
		
		void View::ShowMainMenu(){
				std::cout << std::endl << " \t\t::::::::::::: \t Main Menu \t ::::::::::::" << std::endl;
    			std::cout << std::endl << " \t\t [ 1 ]: File ";
    			std::cout << std::endl << " \t\t [ 2 ]: Dictionary ";	
    			std::cout << std::endl << " \t\t [ 3 ]: Exit ";	
		}
		
		void View::ShowFileMenu(){
				std::cout << std::endl << " \t\t::::::::::::: \t File Menu \t ::::::::::::" << std::endl;
		    	std::cout << std::endl << " \t\t\t [ 1 ]: New File ";
		    	std::cout << std::endl << " \t\t\t [ 2 ]: Open File ";
		    	std::cout << std::endl << " \t\t\t [ 3 ]: Delete File ";
		    	std::cout << std::endl << " \t\t\t [ 4 ]: Back to main menu ";	
		}
		
		void View::ShowDictionaryMenu(){
				std::cout << std::endl << " \t\t::::::::::::: \t Data Dictionary Menu \t ::::::::::::" << std::endl;
				std::cout << std::endl << " \t\t\t [ 1 ]: Entity ";
    			std::cout << std::endl << " \t\t\t [ 2 ]: Attribute ";
    			std::cout << std::endl << " \t\t\t [ 3 ]: Back to main menu ";
		}
		
		void View::ShowEntityMenu(){
				std::cout << std::endl << " \t\t::::::::::::: \t Entity Menu \t ::::::::::::" << std::endl;
				std::cout << std::endl << " \t\t\t [ 1 ]: Add Entity ";
	    		std::cout << std::endl << " \t\t\t [ 2 ]: Update Entity ";
	    		std::cout << std::endl << " \t\t\t [ 3 ]: Delete Entity ";
	    		std::cout << std::endl << " \t\t\t [ 4 ]: Select Entity " ;
	    		std::cout << std::endl << " \t\t\t [ 5 ]: List of entities ";
	    		std::cout << std::endl << " \t\t\t [ 6 ]: Back to main menu ";		
		}

		void View::ShowAttributeMenu(){
				std::cout << std::endl << " \t\t::::::::::::: \t Attribute Menu \t ::::::::::::" << std::endl;
				std::cout << std::endl << " \t\t\t [ 1 ]: Add Attribute ";
	    		std::cout << std::endl << " \t\t\t [ 2 ]: Update Attribute ";
	    		std::cout << std::endl << " \t\t\t [ 3 ]: Delete Attribute ";
	    		std::cout << std::endl << " \t\t\t [ 4 ]: Select Attribute ";
	    		std::cout << std::endl << " \t\t\t [ 5 ]: Back to main menu ";		
		}


}  // end namespace dictionary
