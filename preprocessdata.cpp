#include "preprocessdata.h"
#include <iostream>
#include <fstream>
#include <boost/algorithm/string.hpp>


PreprocessData :: PreprocessData(){
	//std::cout << "Constuctor for preprocessdata" <<std::endl;
}

void PreprocessData :: loadDataFile(std::string fn){
	std::cout << "attempding to load file: " << fn<< std::endl;
	std::ifstream file(fn);
	std::cout << "file loaded" << std::endl;

	std::string str;
	std::vector< std::string > file_contents;


	std::string buf;
int i=1;
	while (std::getline(file, str))
	{
		parse_line(str);
		//std::stringstream ss(str);
//	    while (ss >> buf)
//	    	my_data.relev.push_back(buf);

		//file_contents += str;
		//file_contents.push_back(str);
//		std::cout << i << std::endl;
//		i++
	}

	std::cout << "file parsed" <<std::endl;

	//parse_line(file_contents.front());

}

void PreprocessData :: parse_line(std::string str){
	//std::cout << str << std::endl;
	std::vector<std::string> strs;
	boost::split(strs,str,boost::is_any_of(" "),boost::token_compress_on);

	//Parse doc-id
	parse_docid(strs.back());
	strs.pop_back();
	strs.pop_back();
	strs.pop_back();

	//Once doc-id taken out, reverse list
	std::reverse(strs.begin(), strs.end());

	//Parse relevance id
	int temp_int =std::stoi( strs.back());
	my_data.relev.push_back(temp_int);
	strs.pop_back();

	//Parse qid
	parse_qid(strs.back());
	strs.pop_back();

	//Parse features
	//for(std::vector<int>::iterator it = strs.begin() ; it != strs.end(); ++it){
	//std::reverse(strs.begin(), strs.end());
	parse_features(strs);
	//	strs.pop_back();
	//}


	//std::cout << strs.back() << std::endl;
	//printstrs(strs);
}

void PreprocessData ::printstrs(std::vector<std::string> strs){
    for(std::vector<std::string>::iterator it = strs.begin();it!=strs.end();++it){
        std::cout<<*it<<std::endl;
    }
}

void PreprocessData ::parse_qid(std::string qidstr){
	std::vector<std::string> strs;
	boost::split(strs,qidstr,boost::is_any_of(":"),boost::token_compress_on);
	my_data.qid.push_back(strs.back());
}

void PreprocessData ::parse_docid(std::string docidstr){
	std::vector<std::string> strs;
	boost::split(strs,docidstr,boost::is_any_of("="),boost::token_compress_on);
	my_data.docid.push_back(strs.back());
}

void PreprocessData ::parse_features(std::vector<std::string> strs){

	std::vector<double> feat_vals;

	for(std::vector<std::string>::iterator it= strs.begin() ; it != strs.end(); ++it){
		std::vector<std::string> featstr;
		boost::split(featstr,*it,boost::is_any_of(":"),boost::token_compress_on);
		double temp_val = std::atof(featstr.back().c_str());
		feat_vals.push_back(temp_val);

	}

	//printstrs(strs);
	my_data.feats.push_back(feat_vals);
	//my_data.feats.push_back(temp_val);
}
