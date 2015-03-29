#include "logreg.h"
#include <Eigen/Dense>
#include <iostream>

void stdvec2emat(std::vector<std::vector<double> > vec2d, Eigen::MatrixXd &test_mat);
//void GetSparseFeatLength(FeatureVec &features, int &num_l);
void MakeSparseFeatures (std::vector<double> &features, feature_node *x_space);
void GetSparseFeatLength(std::vector<double> &features, int &num_l);

LogReg::LogReg(){

}

void LogReg::init_params(){
	param.solver_type=L2R_LR;
	param.eps= 0.0001;
	param.C=0.001;
	param.nr_weight=0;
	double w_val=1;
	param.weight=&w_val;
	param.p=0.00001;
}

void LogReg::logreg_test(PreprocessData *pd, model *train_model){
	std::cout << "testing training" << std::endl;
	feature_node* testnode;

	//Change data struct to Libsvm format
	std::vector<int>test_labels, pred_labels;
	test_labels=pd->parsed_data.relev;

//	Eigen::MatrixXd feats_mat;
//	stdvec2emat(pd->parsed_data.feats, feats_mat);
//
//	int numq = pd->parsed_data.data_stats.num_queries;
//	for(int i =0; i<numq; i++){
//		int num_l;
//		FeatureVec features;
//		std::vector<double> feat_vec(feats_mat.row(i), feats_mat.row(i) + feats_mat.rows() * feats_mat.cols());
//		memcpy(feats_mat.row(i), features, sizeof(double)*1*64);
//		features = feats_mat.row(i);
//		GetSparseFeatLength(features, num_l);
//		feature_node *x_space = new feature_node[num_l+1];
//		MakeSparseFeatures (features, x_space);
//		double prob_est[2];
//		predict_probability(train_model, x_space, prob_est);
//	}

	FeatureVec features = pd->parsed_data.feats;
	std::vector <double> ::iterator col_it;
	for(std::vector<std::vector <double> >::iterator it= features.begin(); it!=features.end(); it++){
		std::vector<double> feat_vec;
		for (col_it = it->begin(); col_it != it->end(); col_it++) {
			feat_vec.push_back(*col_it);
		}
		std::reverse(feat_vec.begin(),feat_vec.end());

		int num_l;
		GetSparseFeatLength(feat_vec, num_l);
		feature_node *x_space = new feature_node[num_l+1];
		MakeSparseFeatures (feat_vec, x_space);
		double prob_est[2];
		predict_probability(train_model, x_space, prob_est);
	}
}



void LogReg::logreg_train(PreprocessData *pd){
	std::cout << "new lr train" <<std::endl;
	init_params();
	model *train_model;
	problem prob;
	check_parameter(&prob,&param);
	get_traindata(pd, &prob);
	train_model=train(&prob,&param);

	const char *model_file_name = "saved_model.model";
	int saved= save_model(model_file_name, train_model);
	destroy_param(&param);
}

void LogReg::get_traindata(PreprocessData *pd, problem *prob){
//	struct problem
//	{
//		int l, n;
//		int *y;
//		struct feature_node **x;
//		double bias;
//	};

	std::cout << "get_traindata" <<std::endl;
	prob->l = pd->parsed_data.data_stats.num_queries;
	prob->n = pd->parsed_data.data_stats.num_feats;
	prob->bias=0.0;

	//initialize the problem
	feature_node** x = new feature_node *[prob->l];

	//Change data struct to Libsvm format
	std::cout << "get_traindata ys" <<std::endl;
	//prob->y = new double(prob->l);
	double y_test[prob->l];
	std::cout << "get_traindata y init " << prob->l<<std::endl;
	for(int i =0; i<prob->l; i++){
		//std::cout <<i<<std::endl;
		y_test[i] = pd->parsed_data.relev[i];
	}

	prob->y=y_test;

	FeatureVec features = pd->parsed_data.feats;
	//std::vector <double> ::iterator col_it;
	int i =0;

	std::cout << "get_traindata row it" <<std::endl;

	for(FeatureVec::iterator it= features.begin(); it!=features.end(); it++, i++){
		std::vector<double> feat_vec;
		for (std::vector <double> ::iterator col_it = it->begin(); col_it != it->end(); col_it++) {
			//std::cout << *col_it << std::endl;
			feat_vec.push_back(*col_it);

		}

		std::cout << feat_vec.size() << std::endl;
		std::reverse(feat_vec.begin(),feat_vec.end());

		int num_l=0;
		GetSparseFeatLength(feat_vec, num_l);
		feature_node *x_space = new feature_node[num_l+1];
		std::cout << num_l+1 << std::endl;
		MakeSparseFeatures (feat_vec, x_space);
		x[i] = x_space;

		//feat_vec.clear();
	}

	prob->x = x;
	std::cout << "get_traindata ENDDDDDDD" <<std::endl;
}

void GetSparseFeatLength(std::vector<double> &features, int &num_l){
	for (int k=0; k<features.size(); k++){
		if(features[k]>0){
			num_l++;
		}
	}
}

//void GetSparseFeatLength(FeatureVec &features, int &num_l){
//	for (int k=0; k<features.size(); k++){
//		if(features[k]>0){
//			num_l++;
//		}
//	}
//}

void MakeSparseFeatures (std::vector<double> &features, feature_node *x_space){
	int j=0;
	for (int k=0; k<features.size(); k++){
		if(features[k]>0){
			x_space[j].index = j+1;
			x_space[j].value = features[k];
			j++;
		}
	}
	x_space[j].index = -1;
}

//void MakeSparseFeatures (FeatureVec &features, feature_node *x_space){
//	int j=0;
//	for (int k=0; k<features.size(); k++){
//		if(features[k]>0){
//			x_space[j].index = j+1;
//			x_space[j].value = features[k];
//			j++;
//		}
//	}
//	x_space[j].index = -1;
//}

void stdvec2emat(std::vector<std::vector<double> > vec2d, Eigen::MatrixXd &test_mat){
	for(int i =0; i<test_mat.rows(); i++){
		for(int j =0; j<test_mat.cols(); j++){
			test_mat(i,j) = vec2d[i][j];
		}
	}
}

void stdvec2emat(std::vector<double> vec1d, Eigen::MatrixXd &test_mat){
	for(int i =0; i<test_mat.rows(); i++){
		for(int j =0; j<test_mat.cols(); j++){
			test_mat(i,j) = vec1d[i];
		}
	}
}
