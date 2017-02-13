#ifndef AUTOCOMPLETEGRAPH_BASEMENTFULL_15112016
#define AUTOCOMPLETEGRAPH_BASEMENTFULL_15112016

#include <random>

#include "bettergraph/PseudoGraph.hpp"
#include "vodigrex/linefollower/SimpleNode.hpp"
#include "das/CornerDetector.hpp"
#include "PriorLoaderInterface.hpp"

namespace AASS{
	namespace acg{

		/**
		 * @brief The class with all the hardcoded first guess things
		 */
		class BasementFull : public PriorLoaderInterface{
			
		protected:
// 			std::vector<cv::Point2f> _corner_prior;
// 			std::vector<cv::Point2f> _same_point_prior;
// 			std::vector<cv::Point2f> _same_point_slam;
// 			std::vector<cv::Point2f> _corner_prior_matched;
// 			bettergraph::PseudoGraph<AASS::vodigrex::SimpleNode, AASS::vodigrex::SimpleEdge> _prior_graph;
// 			cv::Mat _scale_transform_prior2ndt;
// 			std::string _file;
			
		public: 

			BasementFull(double deviation, double anglet, double scalet, cv::Point2f center) : PriorLoaderInterface("/home/malcolm/ros_catkin_ws/kinetic_ws/src/auto_complete_graph/tests/emergbasement_flipped_nodoor.png"){
				
				auto randomNoise = [](double mean, double deviationt) -> double {
					std::default_random_engine engine{std::random_device()() };
					std::normal_distribution<double> dist(mean, deviationt);
					return dist(engine);
				};
				
// 				cv::Point center = cv::Point(7, 08);
				double angle = anglet;
				double scale = scalet;
				
				cv::Mat rot_mat = cv::getRotationMatrix2D(center, angle, scale);
				std::cout << rot_mat << std::endl;
// 				exit(0);
				
				auto rotatef = [](const cv::Mat& rot_mat, const cv::Point2d point) -> cv::Point2d {
					//Matrix multiplication
					cv::Mat point_m = (cv::Mat_<double>(3,1) << point.x, point.y, 1);
					cv::Mat mat_out = rot_mat * point_m;
// 					std::cout << "Mat out " << mat_out << std::endl;
					cv::Point2d point_out;
					point_out.x = mat_out.at<double>(0);
					point_out.y = mat_out.at<double>(1);
					return point_out;
				};
				
				
				
				
				auto noise_x = randomNoise(0, deviation);
				auto noise_y = randomNoise(0, deviation);
				
				std::cout << "Noise X Y " << noise_x << " " << noise_y << std::endl;
// 				exit(0);
				
				cv::Point2f out = cv::Point2f(19.36 + noise_x, 6.25 + noise_y);
				cv::Point2f slam_point = rotatef(rot_mat, out);
				
				_same_point_prior.push_back(cv::Point2f(786, 373));
				_same_point_slam.push_back(slam_point);
				
				noise_x = randomNoise(0, deviation);
				noise_y = randomNoise(0, deviation);
				out = cv::Point2f(19.14 + noise_x, 2.25 + noise_y);
				slam_point = rotatef(rot_mat, out);
				
				_same_point_prior.push_back(cv::Point2f(788, 311));                   
				_same_point_slam.push_back(slam_point);
				
				noise_x = randomNoise(0, deviation);
				noise_y = randomNoise(0, deviation);
				out = cv::Point2f(7.64 + noise_x, 3.63 + noise_y);
				slam_point = rotatef(rot_mat, out);
				
				//ATTENTION : next line or for used the points only
				
				_same_point_prior.push_back(cv::Point2f(614, 306));
				_same_point_slam.push_back(slam_point);
				
				noise_x = randomNoise(0, deviation);
				noise_y = randomNoise(0, deviation);
				out = cv::Point2f(9.5 + noise_x, 16 + noise_y);
				slam_point = rotatef(rot_mat, out);
				
				_same_point_prior.push_back(cv::Point2f(637, 529));              
				_same_point_slam.push_back(slam_point);
				
// 				_same_point_prior.push_back(cv::Point2f(786, 373));
// 				_same_point_slam.push_back(cv::Point2f(786, 373));
// 				
// 				_same_point_prior.push_back(cv::Point2f(788, 311));                   
// 				_same_point_slam.push_back(cv::Point2f(786, 373));
// 				
// 				//ATTENTION : next line or for used the points only
// 				
// 				_same_point_prior.push_back(cv::Point2f(614, 306));
// 				_same_point_slam.push_back(cv::Point2f(786, 373));
// 				
// 				_same_point_prior.push_back(cv::Point2f(637, 529));              
// 				_same_point_slam.push_back(cv::Point2f(786, 373));
				
				_scale_transform_prior2ndt = cv::findHomography(_same_point_prior, _same_point_slam, CV_RANSAC, 3, cv::noArray());
		
			}
			
// 			const bettergraph::PseudoGraph<AASS::vodigrex::SimpleNode, AASS::vodigrex::SimpleEdge> getGraph() const {return _prior_graph;}
// 			bettergraph::PseudoGraph<AASS::vodigrex::SimpleNode, AASS::vodigrex::SimpleEdge> getGraph(){return _prior_graph;}
			
			/**
			* @brief Extracting the corner from the prior
			*/
// 			void extractCornerPrior(){
// 		// 		AASS::das::BasementPriorLine basement;
// // 				cv::Mat src = cv::imread( _file, CV_LOAD_IMAGE_COLOR ), src_gray;
// // 				cv::cvtColor(src, src_gray, CV_RGB2GRAY );
// // 				
// // 				cv::threshold(src_gray, src_gray, 100, 255, src_gray.type());
// 				
// 				AASS::das::CornerDetector cornerDetect;
// 				cornerDetect.getFeaturesGraph(_file);
// // 				cornerDetect.removeClosePoints(20);
// 				_corner_prior = cornerDetect.getGraphPoint();
// 				_prior_graph = cornerDetect.getGraph(); 
// 				
// 			}
			
			/**
			 * @brief scale the corner and the graph depending on the _scale_transform_prior2ndt attribute
			 */
// 			void transformOntoSLAM(){
// 				std::cout << "Transform onto slam from scale : " << std::endl << _scale_transform_prior2ndt << std::endl;
// 				//Scale transform here:		
// 				//Then create association
// // 				cv::perspectiveTransform( _corner_prior, _corner_prior_matched, _scale_transform_prior2ndt);
// 				cv::Point2f srcTri[3];
// 				cv::Point2f dstTri[3];
// 				srcTri[0] = _same_point_prior[0];
// 				srcTri[1] = _same_point_prior[1];
// 				srcTri[2] = _same_point_prior[2];
//                           
// 				dstTri[0] = _same_point_slam[0];
// 				dstTri[1] = _same_point_slam[1];
// 				dstTri[2] = _same_point_slam[2];
// 				
// 				cv::Mat warp_mat = cv::getAffineTransform( srcTri, dstTri );
// 				/// Compute a rotation matrix with respect to the center of the image
// // 				cv::Point center = cv::Point( warp_dst.cols/2, warp_dst.rows/2 );
// // 				double angle = -50.0;
// // 				double scale = 0.6;
// 
// 				/// Get the rotation matrix with the specifications above
// // 				rot_mat = cv::getRotationMatrix2D( center, angle, scale );
// 				
// 				/// Apply the Affine Transform just found to the src image
// 				cv::Mat warp_dst = cv::imread( _file, 1 );
// 				
// 				std::cout << "Warp Affine" << warp_mat <<std::endl;
// 				//TODO Implement myself
// 				cv::warpAffine( _same_point_prior, warp_dst, warp_mat, warp_dst.size() );
// // 
// 				cv::namedWindow( "fuck", CV_WINDOW_AUTOSIZE );
// 				cv::imshow( "fuck", warp_dst );
// 				/** Rotating the image after Warp */
// 
// 				
// 
// 				/// Rotate the warped image
// // 				cv::warpAffine( warp_dst, warp_rotate_dst, rot_mat, warp_dst.size() );
// 				
// 				
// 				//Scale graph
// 				std::pair< AASS::das::CornerDetector::CornerVertexIterator, AASS::das::CornerDetector::CornerVertexIterator > vp;
// 				//vertices access all the vertix
// 				//Classify them in order
// 	// 				std::cout << "Gph size : " << _graph.getNumVertices() << std::endl;
// 				int i = 0 ;
// 				for (vp = boost::vertices(_prior_graph); vp.first != vp.second; ++vp.first) {
// 	// 					std::cout << "going throught grph " << i << std::endl; ++i;
// 					AASS::das::CornerDetector::CornerVertex v = *vp.first;
// 					cv::Point2f p;
// 					std::cout << "OLD value " << _prior_graph[v].getX() << " " << _prior_graph[v].getY() << std::endl;
// 					std::cout << "New value " << _corner_prior_matched[i].x << " " << _corner_prior_matched[i].y << std::endl;
// 					_prior_graph[v].setX(_corner_prior_matched[i].x);
// 					_prior_graph[v].setY(_corner_prior_matched[i].y);
// 					std::cout << "New value " << _prior_graph[v].getX() << " " << _prior_graph[v].getY() << std::endl;
// 					++i;
// 				}
// 				
// 				
// 				
// 			}
			
		};
		
	}
}

#endif
