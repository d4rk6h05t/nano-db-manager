#include "data_dictionary_file.h"

namespace dictionary {

	
	DataDictionaryFile::DataDictionaryFile(){ 
		
		id_ = 0;
		std::string path = "/home/ghostdev/Projects/cc/file_structures/";
		std::string tmp_dir = "tmp/";
		std::string tmp_name = "unamed";
		std::string ext = ".dat";
       
		path_ = path;
		dir_ = tmp_dir;
		name_ = tmp_name; 
		ext_ = ext;
        
        file_header_ = -1;
		
        //std::fstream file ( name_ + ext_, std::fstream::binary | std::fstream::out );
        //file.seekg (0);
		//	file.write( (char*) &file_header_, sizeof(long int) );


			//std::ofstream outfile (name_ + ext_,std::ofstream::binary);
	        //outfile.write( (char*) &file_header_, sizeof(long int) );
	        //std::cout << std::endl << name_ + ext_ << " successfully created file!  " << std::endl;
		//	file.close();
			//std::ofstream outfile (name_ + ext_,std::ofstream::binary);
	        //outfile.write( (char*) &file_header_, sizeof(long int) );
	        //std::cout << std::endl << name_ + ext_ << " successfully created file!" << std::endl;
			//outfile.close();
         
	}

	DataDictionaryFile::DataDictionaryFile(const std::string& name){ 
		
		id_ = 0;
		std::string path = "/home/ghostdev/Projects/cc/file_structures/";
		std::string tmp_dir = "tmp/";
		std::string ext = ".dat";

		path_ = path;
		dir_ = tmp_dir;
		name_ = name; 
		ext_ = ext;
        
        file_header_ = -1;
		
        //std::fstream file ( name_ + ext_, std::fstream::binary | std::fstream::out );
        //file.open(name_ + ext_ , std::fstream::out | std::fstream::in | std::fstream::binary);
        //if ( file.is_open() ){

        //	file.seekg (0);
		//	file.write( (char*) &file_header_, sizeof(long int) );


			//std::ofstream outfile (name_ + ext_,std::ofstream::binary);
	        //outfile.write( (char*) &file_header_, sizeof(long int) );
	        //std::cout << std::endl << name_ + ext_ << " successfully created file!  " << std::endl;
		//	file.close();
			//std::ofstream outfile (name_ + ext_,std::ofstream::binary);
	        //outfile.write( (char*) &file_header_, sizeof(long int) );
	    //    std::cout << std::endl << name_ + ext_ << " successfully created file!" << std::endl;
			//outfile.close();
        		
        //}
	}



	DataDictionaryFile::~DataDictionaryFile(){}
	
	void DataDictionaryFile::SetId(int id){ id_ = id; }
	void DataDictionaryFile::SetName(const std::string& name){ name_ = name; }
	void DataDictionaryFile::SetDir(const std::string& dir){ dir_ = dir; }
	void DataDictionaryFile::SetPath(const std::string& path){ path_ = path; }
	void DataDictionaryFile::SetExt(const std::string& ext){ ext_ = ext; }
    void DataDictionaryFile::SetFileHeader(long int file_header){ file_header_ = file_header; }

    int DataDictionaryFile::GetId(){ return id_;}
    std::string DataDictionaryFile::GetName(){ return name_;}
    std::string DataDictionaryFile::GetDir(){ return dir_;}
    std::string DataDictionaryFile::GetPath(){ return path_;}
    std::string DataDictionaryFile::GetExt(){ return ext_;}
    long int DataDictionaryFile::GetFileHeader(){return file_header_;}
    
    long int DataDictionaryFile::GetFileSize(){
    	std::streampos file_begin, file_end;
		std::ifstream file ( name_ + ext_, std::ifstream::binary );
		file_begin = file.tellg();
		file.seekg (0, std::ifstream::end);
		file_end = file.tellg();
		file.close();
		file_size_ = file_end - file_begin;
		return file_size_;
    }
    
   void DataDictionaryFile::CreateFile(){
   		    std::ofstream file ( name_ + ext_, std::ofstream::binary | std::ofstream::out );
			file.seekp (0);
			file.write( (char*) &file_header_, sizeof(long int) );
			file.close();
	        std::cout << std::endl << name_ + ext_ << " successfully created file!" << std::endl;
   }

    void DataDictionaryFile::AddEntity(Entity entity){
    	//std::list<std::string> 
    	/*
    	std::string entity_name = entity.GetName();
    	std::list<int> ascii_number; 
    	
    	for( int i = 0; i < entity_name.size(); i++)
    		ascii_number.push_front((int)entity_name[i] );		
    	
    	

    	std::cout << std::endl <<  "=> entity_name :::: " << entity_name << std::endl; 
        */
        
        //std::list<std::string> list_names; 
    	//for (std::list<int>::iterator it = ascii_number.begin(); it != ascii_number.end(); it++)
    	//		std::cout << ' ' << *it;
        
    	list_entities_.push_back(entity);
		
		//std::streampos begin_position, end_position;
    	std::fstream file ( name_ + ext_, std::fstream::binary | std::fstream::out );
        
    	file.seekg(0, std::fstream::end);
		int file_length = file.tellg(); // Entity Address

		file_header_ = file_length + sizeof(dictionary::Entity); // Next Entity Address 
		
		std::cout << std::endl << ":::::: File Size ::::::: ===>  " << file_length << std::endl;
		std::cout << std::endl << ":::::: Header ::::::: ===>  " << file_header_ << std::endl;

		file.seekg( file_length + sizeof(dictionary::Entity), std::fstream::end  );
		
		file.seekp (0);
		file.write( (char*) &file_header_, sizeof(long int) );
		
		file.close();
		//file.seekp(file_length, std::fstream::beg);
		//file.seekg( sizeof(dictionary::Entity)  );
		//file.seekg( file_length + sizeof(dictionary::Entity), std::fstream::end  );
		//begin_position = file.tellg();
		//file.seekp (0);
		std::fstream efile ( name_ + ext_, std::fstream::binary | std::fstream::out );
		//efile.seekg(0, std::fstream::end);
		//int efile_length = efile.tellg(); 

		//efile.seekp (efile_length);
		//efile.seekg( efile_length + sizeof(dictionary::Entity), std::fstream::end  );
		efile.seekg (file_size_, std::fstream::end);
		efile.write( (char*) &entity, sizeof(dictionary::Entity) );
		//end_position = file.tellg();
        //file.write( (char*) &file_header_, sizeof(long int) );
        std::cout << std::endl << name_ + ext_ << " successfully updated file!"  << std::endl;
		efile.close(); 

        //file.open(name_ + ext_ , std::fstream::in | std::fstream::binary);
    	
		/*

		if ( file.is_open() ){
			
			file.seekg( 8 );	
			if ( file.read( (char*)&entity, sizeof(entity) ) ){
				std::cout << std:: endl<< std::endl;
				std::cout << "::::: Data extracted from file :::::" << std::endl;
				entity.DisplayEntity();
			} else {
				std::cout << " Error in reading data from file... " << std::endl;
				//return -1;
			}
		
        //std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(file), {});


        //begin_position = file.tellg();
		file.seekg (file_size_, std::fstream::end);
		file.write( (char*) &entity, sizeof(dictionary::Entity) );
		//end_position = file.tellg();
        //file.write( (char*) &file_header_, sizeof(long int) );
        std::cout << std::endl << name_ + ext_ << " successfully updated file!"  << std::endl;
		file.close(); 

		} else {
			std::cout << "Ups! Error in opening file ..." << std::endl;
			//std::cerr << "Error: " << strerror(errno) << std::endl;
			//return -1;
		}
*/
		

    }

    void DataDictionaryFile::AddAttribute(Attribute attribute){
    	list_attributes_.push_back(attribute);
    	//std::streampos begin_position, end_position;
    	std::fstream file ( name_ + ext_, std::fstream::binary | std::fstream::out );
        //begin_position = file.tellg();
		file.seekg (file_size_, std::fstream::end);
		file.write( (char*) &attribute, sizeof(dictionary::Attribute) );
		//end_position = file.tellg();
        //file.write( (char*) &file_header_, sizeof(long int) );
        std::cout << std::endl << name_ + ext_ << " successfully updated file!"  << std::endl;
		file.close(); 
    }

    

}  // end namespace dictionary

/*

int main () {

	dictionary::DataDictionaryFile data_dictionary("My_First_Data_Dictionary");

	std::cout << "::::: ===> Name Data Dictionary : " << data_dictionary.GetName() << std::endl; 
    std::cout << "::::: ===> Size File: " << data_dictionary.GetFileSize() << std::endl; 
	
	dictionary::Entity fisrt_entity("user");
	fisrt_entity.SetEntityAddress( data_dictionary.GetFileSize() );
	fisrt_entity.SetNextEntityAddress( data_dictionary.GetFileSize() + sizeof(dictionary::Entity) );
	data_dictionary.AddEntity(fisrt_entity);
    //std::cout << "::::: after add First entity ===> Size File: " << data_dictionary.GetFileSize() << std::endl; 
	
	dictionary::Entity second_entity("bank");
	second_entity.SetEntityAddress( data_dictionary.GetFileSize() );
	second_entity.SetNextEntityAddress( data_dictionary.GetFileSize() + sizeof(dictionary::Entity) );
	data_dictionary.AddEntity(second_entity);
	//std::cout << "::::: after add second entity ===> Size File: " << data_dictionary.GetFileSize() << std::endl; 
	

	dictionary::Entity third_entity("buy");
	third_entity.SetEntityAddress( data_dictionary.GetFileSize() );
	third_entity.SetNextEntityAddress( data_dictionary.GetFileSize() + sizeof(dictionary::Entity) );
	data_dictionary.AddEntity(third_entity);
    
	std::list<std::string> names_entities; 
    names_entities.push_back("user");
    names_entities.push_back("bank");
    names_entities.push_back("buy");
    
    names_entities.sort();

    	std::cout << std::endl << std::endl ;
    	for (std::list<std::string>::iterator it = names_entities.begin(); it != names_entities.end(); ++it)
    			std::cout << ' ' << *it;
    	std::cout << std::endl << std::endl ;


	
	//std::cout << "::::: after add second entity ===> Size File: " << data_dictionary.GetFileSize() << std::endl; 
	
    
    std::cout << "::::: \t Metadata of Entity \t :::::  " << std::endl << std::endl;

    std::cout << "|\t\t Name \t\t | Entity Address | Attribute Address | Data Addres | Next Entity Address |"  << std::endl; 
	
	std::cout << "\t" << fisrt_entity.GetName() << "\t\t"
			  << "\t" << fisrt_entity.GetEntityAddress() << "\t"
			  << "\t" << fisrt_entity.GetAttributeAddress() << "\t"
			  << "\t" << fisrt_entity.GetDataAddress() << "\t"
			  << "\t" << fisrt_entity.GetNextEntityAddress() << "\t"
			  << std::endl;
	
	std::cout << "\t" << second_entity.GetName() << "\t\t"
			  << "\t" << second_entity.GetEntityAddress() << "\t"
			  << "\t" << second_entity.GetAttributeAddress() << "\t"
			  << "\t" << second_entity.GetDataAddress() << "\t"
			  << "\t" << second_entity.GetNextEntityAddress() << "\t"
			  << std::endl;

	std::cout << "\t" << third_entity.GetName() << "\t\t"
			  << "\t" << third_entity.GetEntityAddress() << "\t"
			  << "\t" << third_entity.GetAttributeAddress() << "\t"
			  << "\t" << third_entity.GetDataAddress() << "\t"
			  << "\t" << third_entity.GetNextEntityAddress() << "\t"
			  << std::endl;
	


	dictionary::Attribute fisrt_attribute("MyFirstAttribute",'C',60,0);
	fisrt_attribute.SetAttributeAddress( data_dictionary.GetFileSize() );
	fisrt_attribute.SetNextAttributeAddress( data_dictionary.GetFileSize() + sizeof(dictionary::Attribute) );
	data_dictionary.AddAttribute(fisrt_attribute);

	dictionary::Attribute second_attribute("MySecondAttribute",'I',30,0);
	second_attribute.SetAttributeAddress( data_dictionary.GetFileSize() );
	second_attribute.SetNextAttributeAddress( data_dictionary.GetFileSize() + sizeof(dictionary::Attribute) );
	data_dictionary.AddAttribute(second_attribute);

	dictionary::Attribute third_attribute("MySecondAttribute",'C',10,0);
	third_attribute.SetAttributeAddress( data_dictionary.GetFileSize() );
	third_attribute.SetNextAttributeAddress( data_dictionary.GetFileSize() + sizeof(dictionary::Attribute) );
	data_dictionary.AddAttribute(third_attribute);

	

	std::cout << "|\t\t Name \t\t | Data Type | Length Data Type | Attribute Address | Index Type | Index Address | Next Attribute Address" << std::endl << std::endl; 
	
	std::cout << "\t" << fisrt_attribute.GetName() << "\t"
			  << "\t" << fisrt_attribute.GetDataType() << "\t"
			  << "\t" << fisrt_attribute.GetLengthDataType() << "\t"
			  << "\t" << fisrt_attribute.GetAttributeAddress() << "\t"
			  << "\t" << fisrt_attribute.GetTypeIndex() << "\t"
			  << "\t" << fisrt_attribute.GetIndexAddress() << "\t"
			  << "\t" << fisrt_attribute.GetNextAttributeAddress() << "\t"
			  << std::endl;
	
	std::cout << "\t" << second_attribute.GetName() << "\t"
			  << "\t" << second_attribute.GetDataType() << "\t"
			  << "\t" << second_attribute.GetLengthDataType() << "\t"
			  << "\t" << second_attribute.GetAttributeAddress() << "\t"
			  << "\t" << second_attribute.GetTypeIndex() << "\t"
			  << "\t" << second_attribute.GetIndexAddress() << "\t"
			  << "\t" << second_attribute.GetNextAttributeAddress() << "\t"
			  << std::endl;

	std::cout << "\t" << third_attribute.GetName() << "\t"
			  << "\t" << third_attribute.GetDataType() << "\t"
			  << "\t" << third_attribute.GetLengthDataType() << "\t"
			  << "\t" << third_attribute.GetAttributeAddress() << "\t"
			  << "\t" << third_attribute.GetTypeIndex() << "\t"
			  << "\t" << third_attribute.GetIndexAddress() << "\t"
			  << "\t" << third_attribute.GetNextAttributeAddress() << "\t"
			  << std::endl;
    
    
	return 0;



}

*/
