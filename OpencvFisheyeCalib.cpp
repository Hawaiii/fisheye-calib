#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int N_IMGS = 2;
int N_ROWS = 9;
int N_COLS = 10;
int IMG_WIDTH = 1600;
int IMG_HEIGHT = 1200;

// some hard coded parts about the ordering of points: (1,1), (1,2), ... , (1, NCOL), (2,1), (2,2) ...
int openFeatureFile(char *feature_file, 
					std::vector<std::vector<cv::Point2d>> &img_pts,
					std::vector<std::vector<cv::Point3d>> &world_pts ){
	
	cout << "Attempting to open " << feature_file << endl;

	std::ifstream infile(feature_file);
	std::string line;

	int cnt_frame = 0;
  	int cnt_pts_in_frame = 0;
  	while (std::getline(infile, line)) {
  		std::istringstream iss(line);
  		double ix, iy, wx, wy;
  		iss >> ix >> iy >> wx >> wy;
  		cv::Point2d imp (ix, iy);
  		cv::Point3d wdp (wx, wy, 1.0);

  		img_pts[cnt_frame][cnt_pts_in_frame] = imp;
  		world_pts[cnt_frame][cnt_pts_in_frame] = wdp;

  		cnt_pts_in_frame ++;
  		if (cnt_pts_in_frame == N_COLS * N_ROWS){
  			cnt_frame++;
  			cnt_pts_in_frame = 0;
  		}
  	}
  	
  	cout << "read " << img_pts.size() << " frames in total." << endl;
  	cout << endl;
  	for (Point3d p:world_pts[1]){
  		cout << p << endl;
  	}
  	cout << endl;
  	return 0;
}

int main(int argc, char **argv){
	if (argc < 2){
		cout << "usage: ./OpencvFisheyeCalib <feature_file.txt>" << endl;
		return -1;
	}

	int error;
	vector<vector<cv::Point2d>> img_pts (N_IMGS, std::vector<cv::Point2d>(N_COLS*N_ROWS));
	vector<vector<cv::Point3d>> world_pts (N_IMGS, std::vector<cv::Point3d>(N_COLS*N_ROWS));
	error = openFeatureFile(argv[1], img_pts, world_pts);
	if (error != 0){
		cerr << "Something wrong with reading files" << endl;
		return -1;
	}

	cv::Size img_size(IMG_WIDTH, IMG_HEIGHT);
	cv::Matx33d K;
	cv::Vec4d D;
	std::vector<cv::Vec3d> rvec;
	std::vector<cv::Vec3d> tvec;
	double calibration_err = fisheye::calibrate(world_pts, img_pts, img_size,
 												K, D, rvec, tvec);

	cout << "Result: " << endl;
	cout << "K: " << K << endl;
	cout << "D: " << D << endl;
	for (int i = 0; i < rvec.size(); i++){
		cout << "rvec[" << i << "]:" << rvec[i] << " , tvec[" << i << "]:" << tvec[i] << endl;
	}
	cout << "calibration_err: " << calibration_err << endl;

	// Undistort image with 

	return 0;
}