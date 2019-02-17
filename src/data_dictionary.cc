#include "data_dictionary.h"

namespace dictionary {

	
	DataDictionary::DataDictionary(){ 
		
		id_ = 0;
		std::string path = "/home/ghostdev/Projects/cc/file_structures/";
		std::string tmp_dir = "tmp/";
		std::string tmp_name = "unamed";
		std::string ext = ".dat";
       
		path_ = path;
		dir_ = tmp_dir;
		name_ = tmp_name; 
		ext_ = ext;
        
        ptr_header_ = NULL;
		
		// create file
		std::fstream file( name_ + ext_, std::ios::out | std::ios::binary);
		// std::ios::in | std::ios::out | std::ios::binary
		//file.binary | file.trunc | file.in | file.out
		file.open( name_ + ext_, std::ios::in | std::ios::out | std::ios::binary ); 

		   	
		
		const float f = 3.14f;
		file.write( (char*) &f, sizeof(float) );
        file.write( (char*) &id_, sizeof(int) );
        file.write( (char*) &path_, sizeof(std::string) );
        file.write( (char*) &ptr_header_, sizeof(int*) );

		//file.write(reinterpret_cast<int*>(&id_), sizeof id_);
		//file.write(&path_, sizeof(std::string));
		//file.write(&ptr_header_, sizeof(int*));
		
		std::string line;
		if (file.is_open()){
			std::cout << std::endl << "File Open success!" << std::endl;
			while ( std::getline (file,line) )
				std::cout << line << std::endl;
		} else std::cout << "I'm sorry :'v , Don't open file ";
        
		file.close(); 
        
	}

	DataDictionary::DataDictionary(const std::string& name){ 
		
		id_ = 0;
		std::string path = "/home/ghostdev/Projects/cc/file_structures/";
		std::string tmp_dir = "tmp/";
		std::string ext = ".dat";

		path_ = path;
		dir_ = tmp_dir;
		name_ = name; 
		ext_ = ext;
        
        ptr_header_ = NULL;
		
		std::ofstream outfile (name_ + ext_,std::ofstream::binary);
		
		const float f = 3.14f;
		outfile.write ((char*)&f,sizeof(float));
		outfile.write( (char*) &id_, sizeof(int) );
        outfile.write( (char*) &path_, sizeof(std::string) );
        outfile.write( (char*) &ptr_header_, sizeof(int*) );
        std::cout << std::endl << "Weigth file.dat: " << sizeof(std::string)+sizeof(float)+sizeof(int)+sizeof(int*) << std::endl;
		outfile.close(); 


        
		std::ifstream infile (name_ + ext_,std::ifstream::binary);

	}

	DataDictionary::~DataDictionary(){}
	
	void DataDictionary::SetId(int id){ id_ = id; }
	void DataDictionary::SetName(const std::string& name){ name_ = name; }
	void DataDictionary::SetDir(const std::string& dir){ dir_ = dir; }
	void DataDictionary::SetPath(const std::string& path){ path_ = path; }
	void DataDictionary::SetExt(const std::string& ext){ ext_ = ext; }
    void DataDictionary::SetPtrHeader(int* ptr_header){ ptr_header_ = ptr_header; }

    void DataDictionary::AddEntity(Entity entity){
    	list_entities_.push_back(entity);
    }

    void DataDictionary::AddAttribute(Attribute attribute){
    	list_attributes_.push_back(attribute);
    }

    int DataDictionary::GetId(){ return id_;}
    std::string DataDictionary::GetName(){ return name_;}
    std::string DataDictionary::GetDir(){ return dir_;}
    std::string DataDictionary::GetPath(){ return path_;}
    std::string DataDictionary::GetExt(){ return ext_;}
    int* DataDictionary::GetPtrHeader(){return ptr_header_;}



}  // end namespace dictionary

int main(){
	dictionary::DataDictionary data_dictionary("MyFirstDataDictionary");
	std::cout << "Name DataDictionary: " << data_dictionary.GetName() << std::endl; 
	return 0;
}