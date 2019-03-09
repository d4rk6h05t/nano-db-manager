
#include "view.h"

namespace ui {

		View::View(){}
		View::~View(){}
		void View::Clear(){ system("clear"); }
		void View::ShowTitle(){ std::cout << std::endl << "\t\t Project Structure File "<< std::endl; }
		void View::ShowMessage(std::string str ){ std::cout << std::endl << std::endl << " \t " + str;  }
		
		void View::ShowMainMenu(){
				//std::cout << std::endl << " \t\t ::::: Main Menu  ::::: " << std::endl;
				std::cout << std::endl << " \t\t::::::::::::: \t Main Menu \t ::::::::::::" << std::endl;
    			std::cout << std::endl << " \t\t [ 1 ]: File ";
    			std::cout << std::endl << " \t\t [ 2 ]: Dictionary ";	
    			std::cout << std::endl << " \t\t [ 3 ]: Exit ";	
		}
		
		void View::ShowFileMenu(){
				//std::cout << std::endl << " \t\t ::::: File Menu  ::::: " << std::endl;
		    	std::cout << std::endl << " \t\t::::::::::::: \t File Menu \t ::::::::::::" << std::endl;
		    	std::cout << std::endl << " \t\t\t [ 1 ]: New File ";
		    	std::cout << std::endl << " \t\t\t [ 2 ]: Open File ";
		    	std::cout << std::endl << " \t\t\t [ 3 ]: Delete File ";
		    	std::cout << std::endl << " \t\t\t [ 4 ]: Back to main menu ";	
		}
		
		void View::ShowDictionaryMenu(){
				std::cout << std::endl << " \t\t::::::::::::: \t Data Dictionary Menu \t ::::::::::::" << std::endl;
				//std::cout << std::endl << " \t\t ::::: Dictionary Menu  ::::: " << std::endl;
		 		std::cout << std::endl << " \t\t\t [ 1 ]: Entity ";
    			std::cout << std::endl << " \t\t\t [ 2 ]: Attribute ";
    			std::cout << std::endl << " \t\t\t [ 3 ]: Back to main menu ";
		}
		
		void View::ShowEntityMenu(){
				//std::cout << std::endl << " \t\t ::::: Entity Menu  :::::  "<< std::endl;
				std::cout << std::endl << " \t\t::::::::::::: \t Entity Menu \t ::::::::::::" << std::endl;
				std::cout << std::endl << " \t\t\t [ 1 ]: Add Entity ";
	    		std::cout << std::endl << " \t\t\t [ 2 ]: Update Entity ";
	    		std::cout << std::endl << " \t\t\t [ 3 ]: Delete Entity ";
	    		std::cout << std::endl << " \t\t\t [ 4 ]: Select Entity " ;
	    		std::cout << std::endl << " \t\t\t [ 5 ]: List of entities ";
	    		std::cout << std::endl << " \t\t\t [ 6 ]: Back to main menu ";		
		}

		void View::ShowAttributeMenu(){
				//std::cout << std::endl << " \t\t ::::: Attribute Menu  :::::  "<< std::endl;
				std::cout << std::endl << " \t\t::::::::::::: \t Attribute Menu \t ::::::::::::" << std::endl;
				std::cout << std::endl << " \t\t\t [ 1 ]: Add Attribute ";
	    		std::cout << std::endl << " \t\t\t [ 2 ]: Update Attribute ";
	    		std::cout << std::endl << " \t\t\t [ 3 ]: Delete Attribute ";
	    		std::cout << std::endl << " \t\t\t [ 4 ]: Select Attribute ";
	    		std::cout << std::endl << " \t\t\t [ 5 ]: Back to main menu ";		
		}


}  // end namespace dictionary
