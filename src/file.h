#ifndef FILE_H__
#define FILE_H__

#include <string>
#include <iostream>
#include <fstream>

//using std::string;
using namespace std; 

namespace fileManager { 

	class File {

		private:
	 		string name_;
	 		string path_;
	 		string ext_;
	 		string directory_;
	 		string fullPath_;
		
		public:
	 		File(const string & name);
	 		~File();
            
	 		void setName(const string & name){ name_ = name;}
	 		void setPath(string & path){ path_ = path;}
	 		void setExt(string & ext){ ext_ = ext;}
	 		void setDirectory(string & directory){ directory_ = directory;}
	 		void setFullPath(string & fullPath){ fullPath_ = fullPath;}

	 		string getName(){ return name_;}	
	 		string getPath(){ return path_;}
	 		string getExt(){ return ext_;}
	 		string getDirectory(){ return directory_;}
	 		string getFullPath(){ return fullPath_;}
            
	 		void create();
	 		void open();
	 		void write();
	 		void read();
	 		void close();
	 		void remove();
	 		void rename();
			
	 	
	 		
	};
}
#endif // FILE_H_ _