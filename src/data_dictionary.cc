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
		
		//std::ofstream outfile (name_ + ext_,std::ofstream::binary);
        //outfile.write( (char*) &ptr_header_, sizeof(int*) );
        //std::cout << std::endl << name_ + ext_ << " successfully created file!  ::size ==> " << sizeof(int*) << std::endl;
		//outfile.close(); 
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
		
		//std::ofstream outfile (name_ + ext_,std::ofstream::binary);
        //outfile.write( (char*) &ptr_header_, sizeof(int*) );
        //std::cout << std::endl << name_ + ext_ << " successfully created file!  [ size ] ==> " << sizeof(int*) << std::endl;
		//outfile.close(); 

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
        
    	std::ofstream outfile (name_ + ext_,std::ofstream::binary);
        
        //outfile.write( (char*) &ptr_header_, sizeof(int*) );
        outfile.write( (char*) &entity, sizeof(entity) );
        
        std::cout << std::endl << name_ + ext_ << " successfully updated file!  [ size ] ==> " << sizeof(entity) << std::endl;
		outfile.close(); 
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
	std::cout << std::endl << "::: ===> Name DataDictionary: " << data_dictionary.GetName() << std::endl << std::endl; 
    
	dictionary::Entity fisrt_entity("MyFirstEntity");
	dictionary::Attribute fisrt_attribute("MyFirstAttribute");

	std::cout << "::: ===> Name Entity: " << fisrt_entity.GetName() << std::endl;
	std::cout << "::: ===> Name Attribute: " << fisrt_attribute.GetName() << std::endl;
	
	data_dictionary.AddEntity(fisrt_entity);
	data_dictionary.AddAttribute(fisrt_attribute);

	//std::cout << "::: ===> Name Entity: " << std::endl;



	return 0;



}