#include "File.h"

namespace fileManager {

	using namespace std;	
	
	File::File(const string & name){ 
		
		string path = "/home/ghostdev/Projects/c++/";
		string dir = "tmp/";
		string ext = ".txt";
		path_ = path;
		directory_ = dir;
		name_ = name ; 
		ext_ = ext;
        
	}

	File::~File(){}
	
}
