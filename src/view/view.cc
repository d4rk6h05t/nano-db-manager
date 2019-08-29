
#include "view.h"

namespace ui {

		View::View(){}
		
		View::~View(){}
		
		void View::Clear(){ system("clear"); }
		
		void View::ShowTitle(const std::string & author,const std::string & version){ 
         std::cout << std::endl 
                   << "\t\t   10    11  111     10    11 1111      1011  10110  " << std::endl
                   << "\t\t  11011 11  1 1 1   11011 11  1  1     10  1  11 1   \t  \033[1;32m Nano-DB-Manager-" << version << "\033[0m" << std::endl
                   << "\t\t 11    10  11   11 11    10   1111    11111   10110  \t \033[1;37m By: \033[0m " << author << std::endl
                   << std::endl;
    }
		
		void View::ShowMessage(const std::string & str ){ std::cout << str;  }

		void View::ShowStatusBar(const std::string & name, long int header, long int size ){
			
			std::cout << std::endl << "\t\t \033[1;37m :: File Name [ " << name 
					  << " ] :: File Header [ " << header 
					  << " ] :: File Size [ " << size << " ] \033[0m" << std::endl;
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
			
    								
		}

		void View::ShowListAttributes(std::list<dictionary::Attribute> list_attributes){
   			
   			std::cout << std::endl 
   				<< std::left << std::setw(35) << std::setfill('-') << std::left 
   				<< '+' << std::setw(12) << std::setfill('-') << std::left 
   				<< '+' << std::setw(10) << std::setfill('-') << std::left
   				<< '+' << std::setw(21) << std::setfill('-') << std::left
   				<< '+' << std::setw(13) << std::setfill('-') << std::left 
   				<< '+' << std::setw(16) << std::setfill('-') << std::left
   				<< '+' << std::setw(25) << std::setfill('-') << std::left
		        << '+' << '+' << std::endl;
           
		   	std::cout << std::setfill(' ') << '|' 
		   		<< std::setw(34)  << " Name " << std::setfill(' ') << '|' 
		   		<< std::setw(10)  << " Data Type " << std::setfill(' ') << '|' 
		   		<< std::setw(6)  << " Length  " << std::setfill(' ') << '|' 
		   		<< std::setw(15)  << " Attribute  Address " << std::setfill(' ') << '|'
		   		<< std::setw(12)  << " Type Index " << std::setfill(' ') << '|'
		   		<< std::setw(12)  << " Index Address " << std::setfill(' ') << '|' 
		   		<< std::setw(10)  << " Next Attribute Address " << '|' << std::endl;

	        std::cout 
   				<< std::left << std::setw(35) << std::setfill('-') << std::left 
   				<< '+' << std::setw(12) << std::setfill('-') << std::left 
   				<< '+' << std::setw(10) << std::setfill('-') << std::left
   				<< '+' << std::setw(21) << std::setfill('-') << std::left 
   				<< '+' << std::setw(13) << std::setfill('-') << std::left
   				<< '+' << std::setw(16) << std::setfill('-') << std::left
   				<< '+' << std::setw(25) << std::setfill('-') << std::left
		        << '+' << '+' << std::endl;
			
			for (std::list<dictionary::Attribute>::iterator it = list_attributes.begin(); it != list_attributes.end(); ++it){
    		
    			std::string name( it->GetName() );
    			std::string data_type = std::to_string( it->GetDataType() );
    			std::string length_data_type = std::to_string( it->GetLengthDataType() );
    			std::string attribute_address = std::to_string( it->GetAttributeAddress() );
    			std::string type_index = std::to_string( it->GetTypeIndex() );
    			std::string index_address = std::to_string( it->GetIndexAddress() );
    			std::string next_attribute_address = std::to_string( it->GetNextAttributeAddress() );
    		
    			int length_name = 34 - ( name.length() + 1 );
    			int length_dt = 16 - ( data_type.length() + 1);
    			int length_lgth_dt = 19 - ( length_data_type.length() + 1);
    			int length_attribute_address = 14 - ( attribute_address.length() + 1);
    			int length_type_index = 21 - ( type_index.length() + 1);
    			int length_index_address = 21 - ( index_address.length() + 1);
    			int length_next_attribute_address = 21 - ( next_attribute_address.length() + 1);
                
                int no_equilibrium;
    			if ( it->GetDataType()  == 'i')
    				no_equilibrium = length_dt - 3;
    			else if ( it->GetDataType()  == 'c' )
    				no_equilibrium = length_dt - 4;

    			std::cout << std::setfill(' ') << '|' 
    				<< " " << it->GetName() << std::setw(length_name) << " " <<  '|' // name
    				<< " " << it->GetDataType() << std::setw(no_equilibrium) << " " <<  '|' // entity address
    				<< " " << it->GetLengthDataType() << std::setw(length_lgth_dt-10) << " " <<  '|' // attribute address
    				<< " " << it->GetAttributeAddress() << std::setw(length_attribute_address+6) << " " <<  '|' // data  address
    				<< " " << it->GetTypeIndex() << std::setw(length_type_index-9) << " " <<  '|' //  type index
    				<< " " << it->GetIndexAddress() << std::setw(length_index_address-6) << " " <<  '|' // index address
    				<< " " << it->GetNextAttributeAddress() << std::setw(length_next_attribute_address+3) << " " <<  '|' // next entity address
					<< std::endl;
			}
			
    								
		}
		
		void View::ShowMainMenu(){
				std::cout << std::endl << " \t\t \033[1;37m ::::::::::::: \t Main Menu \t :::::::::::: \033[0m" << std::endl;
    			std::cout << std::endl << " \t\t [ 1 ]: Schema ";
    			std::cout << std::endl << " \t\t [ 2 ]: Dictionary ";	
    			std::cout << std::endl << " \t\t [ 3 ]: Data File ";	
    			std::cout << std::endl << " \t\t [ 4 ]: Exit ";	
		}
		
		void View::ShowFileMenu(){
				std::cout << std::endl << " \t\t \033[1;37m ::::::::::::: \t Schema Menu \t :::::::::::: \033[0m " << std::endl;
		    	std::cout << std::endl << " \t\t\t [ 1 ]: New Schama ";
		    	std::cout << std::endl << " \t\t\t [ 2 ]: Open Schema ";
		    	std::cout << std::endl << " \t\t\t [ 3 ]: Delete Schema ";
		    	std::cout << std::endl << " \t\t\t [ 4 ]: Back to main menu ";	
		}
		
		void View::ShowDictionaryMenu(){
				std::cout << std::endl << " \t\t \033[1;37m ::::::::::::: \t Data Dictionary Menu \t :::::::::::: \033[0m " << std::endl;
				std::cout << std::endl << " \t\t\t [ 1 ]: Entity ";
    			std::cout << std::endl << " \t\t\t [ 2 ]: Attribute ";
    			std::cout << std::endl << " \t\t\t [ 3 ]: Back to main menu ";
		}
		
		void View::ShowEntityMenu(){
				std::cout << std::endl << " \t\t \033[1;37m ::::::::::::: \t Entity Menu \t :::::::::::: \033[0m " << std::endl;
				std::cout << std::endl << " \t\t\t [ 1 ]: Add Entity ";
	    		std::cout << std::endl << " \t\t\t [ 2 ]: Update Entity ";
	    		std::cout << std::endl << " \t\t\t [ 3 ]: Delete Entity ";
	    		std::cout << std::endl << " \t\t\t [ 4 ]: Select Entity " ;
	    		std::cout << std::endl << " \t\t\t [ 5 ]: List of entities ";
	    		std::cout << std::endl << " \t\t\t [ 6 ]: Back to main menu ";		
		}

		void View::ShowAttributeMenu(){
				std::cout << std::endl << " \t\t \033[1;37m ::::::::::::: \t Attribute Menu \t :::::::::::: \033[0m " << std::endl;
				std::cout << std::endl << " \t\t\t [ 1 ]: Add Attribute ";
	    		std::cout << std::endl << " \t\t\t [ 2 ]: Update Attribute ";
	    		std::cout << std::endl << " \t\t\t [ 3 ]: Delete Attribute ";
	    		std::cout << std::endl << " \t\t\t [ 4 ]: Select Attribute ";
	    		std::cout << std::endl << " \t\t\t [ 5 ]: List of attributes ";
	    		std::cout << std::endl << " \t\t\t [ 6 ]: Back to main menu ";		
		}

		void View::ShowDataFileMenu(){
				std::cout << std::endl << " \t\t \033[1;37m ::::::::::::: \t Data File Menu \t :::::::::::: \033[0m " << std::endl;
    			std::cout << std::endl << " \t\t [ 1 ]: Add a register ";
    			std::cout << std::endl << " \t\t [ 2 ]: Show Primary Index ";
    			std::cout << std::endl << " \t\t [ 3 ]: Show Secondary Index";
          std::cout << std::endl << " \t\t [ 4 ]: Show Static Hashing";
          std::cout << std::endl << " \t\t [ 5 ]: Show Multilist";	
    			std::cout << std::endl << " \t\t [ 6 ]: Show Data File ";	
    			std::cout << std::endl << " \t\t [ 7 ]: Remove use Primary Index ";
          std::cout << std::endl << " \t\t [ 8 ]: Remove use Secondary Index ";
          std::cout << std::endl << " \t\t [ 9 ]: Remove use Static Hashing ";
          std::cout << std::endl << " \t\t [ 10 ]: Update use Primary Index ";
          std::cout << std::endl << " \t\t [ 11 ]: Update use Secondary Index ";
          std::cout << std::endl << " \t\t [ 12 ]: Update use Static Hashing ";
    			std::cout << std::endl << " \t\t [ 13 ]: Back to main menu ";	
		}


}  // end namespace dictionary
