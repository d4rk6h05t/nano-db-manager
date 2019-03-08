
#include "view.h"

namespace ui {

		View::View(){}
		View::~View(){}
		void View::Clear(){ system("clear"); }
		void View::ShowTitle(){ std::cout << std::endl << "\t\t Project Structure File "<< std::endl; }
		void View::ShowMessage(std::string str ){ std::cout << std::endl << "\t" + str;  }
		
		void View::ShowMainMenu(){
				std::cout << std::endl << " \t\t ::::: Main Menu  ::::: ";
    			std::cout << std::endl << " \t\t\t [ 1 ]: File " << std::endl;
    			std::cout << std::endl << " \t\t\t [ 2 ]: Dictionary " << std::endl;	
    			std::cout << std::endl << " \t\t\t [ 3 ]: Exit " << std::endl;	
		}
		
		void View::ShowFileMenu(){
				std::cout << std::endl << " \t\t ::::: File Menu  ::::: ";
		    	std::cout << std::endl << " \t\t\t\t [ 1 ]: New File " << std::endl;
		    	std::cout << std::endl << " \t\t\t\t [ 2 ]: Open File " << std::endl;
		    	std::cout << std::endl << " \t\t\t\t [ 3 ]: Delete File " << std::endl;
		    	std::cout << std::endl << " \t\t\t\t [ 4 ]: Back to main menu " << std::endl;	
		}
		
		void View::ShowDictionaryMenu(){
				std::cout << std::endl << " \t\t ::::: Dictionary Menu  ::::: ";
		 		std::cout << std::endl << " \t\t\t\t [ 1 ]: Entity " << std::endl;
    			std::cout << std::endl << " \t\t\t\t [ 2 ]: Attribute " << std::endl;
    			std::cout << std::endl << " \t\t\t\t [ 3 ]: Back to main menu " << std::endl;
		}
		
		void View::ShowEntityMenu(){
				std::cout << std::endl << " \t\t ::::: Entity Menu  :::::  ";
				std::cout << std::endl << " \t\t\t\t [ 1 ]: Add Entity " << std::endl;
	    		std::cout << std::endl << " \t\t\t\t [ 2 ]: Update Entity " << std::endl;
	    		std::cout << std::endl << " \t\t\t\t [ 3 ]: Delete Entity " << std::endl;
	    		std::cout << std::endl << " \t\t\t\t [ 4 ]: Select Entity " << std::endl;
	    		std::cout << std::endl << " \t\t\t\t [ 5 ]: List of entities " << std::endl;
	    		//std::cout << std::endl << " \t\t\t\t [ 6 ]: List of entities sorted " << std::endl;
	    		std::cout << std::endl << " \t\t\t\t [ 6 ]: Back to main menu ";		
		}

		void View::ShowAttributeMenu(){
				std::cout << std::endl << " \t\t ::::: Attribute Menu  :::::  ";
				std::cout << std::endl << " \t\t\t\t [ 1 ]: Add Attribute " << std::endl;
	    		std::cout << std::endl << " \t\t\t\t [ 2 ]: Update Attribute " << std::endl;
	    		std::cout << std::endl << " \t\t\t\t [ 3 ]: Delete Attribute " << std::endl;
	    		std::cout << std::endl << " \t\t\t\t [ 4 ]: Select Attribute " << std::endl;
	    		std::cout << std::endl << " \t\t\t\t [ 5 ]: Back to main menu " << std::endl;		
		}


}  // end namespace dictionary
