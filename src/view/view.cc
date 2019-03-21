
#include "view.h"

namespace ui {

		View::View(){}
		
		View::~View(){}
		
		void View::Clear(){ system("clear"); }
		
		void View::ShowTitle(){ std::cout << std::endl << "\t\t Project Structure File "<< std::endl; }
		
		void View::ShowMessage(std::string str ){ std::cout << std::endl << std::endl << " \t " + str;  }

		void View::ShowStatusBar(std::string name, long int header, long int size ){
			
			std::cout << std::endl << "\t\t:: File Name [ " << name 
					  << " ] :: File Header [" << header << "]" 
					  << " ] :: File Size [" << size << "]" << std::endl;
		}

		void View::ShowListEntities(std::list<dictionary::Entity> list_entities){

			std::cout << " Name  \t Entity Address  Attribute Address  Data Addres  Next Entity Address " << std::endl << std::endl; 
	
			for (std::list<dictionary::Entity>::iterator it = list_entities.begin(); it != list_entities.end(); ++it)
    			std::cout << it->GetName() 
    				 << "\t\t" << it->GetEntityAddress() 
    			     << "\t\t" << it->GetAttributeAddress()
    				 << "\t\t" << it->GetDataAddress()
    			     << "\t\t" << it->GetNextEntityAddress() 
    				 << std::endl;
    								
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
