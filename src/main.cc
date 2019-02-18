#include <iostream> 
#include <string> 
#include <fstream>
#include <stdlib.h>

using namespace std; 

class Interface {
	public:
		Interface(){}
		~Interface(){}
};

class View : public Interface{
	public:
		View(){}
		~View(){}
		void Clear(){ system("clear"); }
		void ShowTitle(){ cout << " \n\t\t Project Structure File \n"; }
		void ShowMessage(string str ){ cout << endl << "\t" + str ;  }
		void ShowMainMenu(){
				cout << " \n\t::::: Main Menu  ::::: ";
    			cout << " \n\t\t\t [ 1 ]: File \n";
    			cout << " \n\t\t\t [ 2 ]: Dictionary \n";	
    			cout << " \n\t\t\t [ 3 ]: Exit \n";	
		}
		void ShowFileMenu(){
				cout << " \n\t::: File Menu  ::::: ";
		    	cout << " \n\t\t\t\t [ 1 ]: New File \n";
		    	cout << " \n\t\t\t\t [ 2 ]: Open File \n";
		    	cout << " \n\t\t\t\t [ 3 ]: Delete File \n";
		    	cout << " \n\t\t\t\t [ 4 ]: Back to main menu \n";	
		}
		void ShowDictionaryMenu(){
				cout << " \n\t::: Dictionary Menu  ::::: ";
		 		cout << " \n\t\t\t\t [ 1 ]: Entity \n";
    			cout << " \n\t\t\t\t [ 2 ]: Attribute \n";
    			cout << " \n\t\t\t\t [ 3 ]: Back to main menu \n";
		}
		void ShowEntityMenu(){
				cout << " \n\t::: Entity Menu  :::::  ";
				cout << " \n\t\t\t\t [ 1 ]: Add Entity \n";
	    		cout << " \n\t\t\t\t [ 2 ]: Update Entity \n";
	    		cout << " \n\t\t\t\t [ 3 ]: Delete Entity \n";
	    		cout << " \n\t\t\t\t [ 4 ]: Select Entity \n";
	    		cout << " \n\t\t\t\t [ 5 ]: Back to main menu \n";		
		}

};


int main(){ 
	
	View view;
    int option;
    int option_file;
    int option_dictionary;
    int option_entity;

    do {
    	
		view.ShowTitle();
		view.ShowMainMenu();
	    view.ShowMessage("Select a option >_");
	    cin >> option;

	    switch (option){
	    	case 1: 

	    		do {
	    			string file_name; 
	    			view.Clear();
		    		view.ShowFileMenu();
		    		view.ShowMessage("Select a option >_");
		    		cin >> option_file;
	    			switch (option_file){
				    	case 1: 
				    		view.ShowMessage("Enter a new file name: ");
				    		cin >> file_name;
				    		view.ShowMessage("create file with name ==> " + file_name);
				    		break;
				    	case 2: 
				    		view.ShowMessage("Enter a file name: ");
				    		cin >> file_name;
				    		view.ShowMessage("open file with name ==> " + file_name);
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
	    		view.Clear();
	    		view.ShowDictionaryMenu();
	    		view.ShowMessage("Select a option >_");
	    		cin >> option_dictionary;
	    		break;
	    	case 3:
	    		view.ShowMessage("\t\t Good bye! :'v \n ");
	    		return 0;
	    		break;
	    	//case default:
	    	//	printf("\n Option not valid! \n");
	    	//	break;	
	    }
	    
    } while(option <= 3);
    return 0;
    
}