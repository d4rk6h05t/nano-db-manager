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
		void ShowMessage(string str ){ cout << str;  }
		void ShowMainMenu(){
				cout << " \n\t Main Menu  ";
    			cout << " \n\t\t\t [ 1 ]: File \n";
    			cout << " \n\t\t\t [ 2 ]: Dictionary \n";	
    			cout << " \n\t\t\t [ 3 ]: Exit \n";	
		}
		void ShowFileMenu(){
				cout << " \n\t File Menu  ";
		    	cout << " \n\t\t\t\t [ 1 ]: New File \n";
		    	cout << " \n\t\t\t\t [ 2 ]: Open File \n";
		    	cout << " \n\t\t\t\t [ 3 ]: Delete File \n";
		    	cout << " \n\t\t\t\t [ 4 ]: Back to main menu \n";	
		}
		void ShowDictionaryMenu(){
				cout << " \n\t Dictionary Menu  ";
		 		cout << " \n\t\t\t\t [ 1 ]: Entity \n";
    			cout << " \n\t\t\t\t [ 2 ]: Attribute \n";
    			cout << " \n\t\t\t\t [ 3 ]: Back to main menu \n";
		}
		void ShowEntityMenu(){
				cout << " \n\t Entity Menu  ";
				cout << " \n\t\t\t\t [ 1 ]: Add Entity \n";
	    		cout << " \n\t\t\t\t [ 2 ]: Update Entity \n";
	    		cout << " \n\t\t\t\t [ 3 ]: Delete Entity \n";
	    		cout << " \n\t\t\t\t [ 4 ]: Select Entity \n";
	    		cout << " \n\t\t\t\t [ 5 ]: Back to main menu \n";		
		}

		
};


int main(){ 
	/*
	View view;
    int option;
    do {
    	
		view.ShowTitle();
		view.ShowMainMenu();
	    view.ShowMessage("Hello world!");
	    cin >> option;
	    switch (option){
	    	case 1: 
	    		view.Clear();
	    		view.ShowFileMenu();
	    		break;
	    	case 2: 
	    		view.Clear();
	    		view.ShowTitle();
	    		view.ShowDictionaryMenu();
	    		break;
	    	//case default:
	    	//	printf("\n Option not valid! \n");
	    	//	break;	
	    }
	    
    } while(option != 4);
    return 0;
    */
    int data;
    int* ptr_data = &data;

    cout << "\n size ptr int : %d \n" << sizeof(ptr_data);
}
