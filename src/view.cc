
#include "view.h"

namespace ui {

		View::View(){}
		View::~View(){}
		void View::Clear(){ system("clear"); }
		void View::ShowTitle(){ std::cout << " \n\t\t Project Structure File \n"; }
		void View::ShowMessage(std::string str ){ std::cout << "\t" + str ;  }
		
		void View::ShowMainMenu(){
				std::cout << " \n\t\t ::::: Main Menu  ::::: ";
    			std::cout << " \n\t\t\t [ 1 ]: File \n";
    			std::cout << " \n\t\t\t [ 2 ]: Dictionary \n";	
    			std::cout << " \n\t\t\t [ 3 ]: Exit \n";	
		}
		
		void View::ShowFileMenu(){
				std::cout << " \n\t\t ::::: File Menu  ::::: ";
		    	std::cout << " \n\t\t\t\t [ 1 ]: New File \n";
		    	std::cout << " \n\t\t\t\t [ 2 ]: Open File \n";
		    	std::cout << " \n\t\t\t\t [ 3 ]: Delete File \n";
		    	std::cout << " \n\t\t\t\t [ 4 ]: Back to main menu \n";	
		}
		
		void View::ShowDictionaryMenu(){
				std::cout << " \n\t\t ::::: Dictionary Menu  ::::: ";
		 		std::cout << " \n\t\t\t\t [ 1 ]: Entity \n";
    			std::cout << " \n\t\t\t\t [ 2 ]: Attribute \n";
    			std::cout << " \n\t\t\t\t [ 3 ]: Back to main menu \n";
		}
		
		void View::ShowEntityMenu(){
				std::cout << " \n\t\t ::::: Entity Menu  :::::  ";
				std::cout << " \n\t\t\t\t [ 1 ]: Add Entity \n";
	    		std::cout << " \n\t\t\t\t [ 2 ]: Update Entity \n";
	    		std::cout << " \n\t\t\t\t [ 3 ]: Delete Entity \n";
	    		std::cout << " \n\t\t\t\t [ 4 ]: Select Entity \n";
	    		std::cout << " \n\t\t\t\t [ 5 ]: List of entities \n";
	    		//std::cout << " \n\t\t\t\t [ 6 ]: List of entities sorted \n";
	    		std::cout << " \n\t\t\t\t [ 6 ]: Back to main menu \n";		
		}

		void View::ShowAttributeMenu(){
				std::cout << " \n\t\t ::::: Attribute Menu  :::::  ";
				std::cout << " \n\t\t\t\t [ 1 ]: Add Attribute \n";
	    		std::cout << " \n\t\t\t\t [ 2 ]: Update Attribute \n";
	    		std::cout << " \n\t\t\t\t [ 3 ]: Delete Attribute \n";
	    		std::cout << " \n\t\t\t\t [ 4 ]: Select Attribute \n";
	    		std::cout << " \n\t\t\t\t [ 5 ]: Back to main menu \n";		
		}


}  // end namespace dictionary
