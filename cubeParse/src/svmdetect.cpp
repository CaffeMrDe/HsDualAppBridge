/**
* @version 	v1.0.1
* @file		svmdetect.cpp
* @brief	魔方检测相关函数
* @date		2020/5/12
*/

#include "svmdetect.h"

svmDetect::svmDetect(NodeHandle n)
{
    mNodeHandle = n;
}

svmDetect::~svmDetect()
{
   
}

void svmDetect::start()
{
    /**
     *  发布服务
     */
	takephotoServer =  mNodeHandle.advertiseService(TAKE_PHOTO_SERVER_NAME, &svmDetect::takephoto_server_Callback, this);
	detectionServer = mNodeHandle.advertiseService(DETECTION_SERVER_NAME, &svmDetect::detection_server_Callback, this);
}

vector<char> svmDetect::getResult()
{
	vector<char> label = svmDetect::establish_benchmark();
	vector<char> totoal_result;
	//按照算法要求的U、R、F、D、L、B的顺序读取图片得出颜色序列
	int read_order[6] = {4, 3, 0, 5, 2, 1};
	for ( int i = 0; i < 6; i++ )
	{
		Mat img_cube = cv::imread("/home/xiaohuihui/catkin_ws/src/cube/photo/" + to_string(read_order[i]) + ".jpg");
        vector<char> singleface_result( svmDetect::detection(img_cube, label));
		for ( size_t j = 0; j <  singleface_result.size(); ++j)
		   totoal_result.push_back(singleface_result[j]);
        //singleface_result.clear();
		vector<char>().swap(singleface_result);
	}

	for ( size_t k = 0; k <  totoal_result[k]; k++)
	    std::cout <<  totoal_result[k] ;
	
	return totoal_result;

}

void svmDetect::printResult()
{
	vector<char> label = svmDetect::establish_benchmark();
	vector<char> totoal_result;
	//按照算法要求的U、R、F、D、L、B的顺序读取图片得出颜色序列
	int read_order[6] = {4, 3, 0, 5, 2, 1};
	for ( int i = 0; i < 6; i++ )
	{
		Mat img_cube = cv::imread("/home/xiaohuihui/catkin_ws/src/cube/photo/" + to_string(read_order[i]) + ".jpg");
        vector<char> singleface_result( svmDetect::detection(img_cube, label));
		for ( size_t j = 0; j <  singleface_result.size(); ++j)
		   totoal_result.push_back(singleface_result[j]);
        //singleface_result.clear();
		vector<char>().swap(singleface_result);
	}
	
	for ( size_t k = 0; k <  totoal_result[k]; k++)
	    std::cout <<  totoal_result[k] ;
}


cv::Mat svmDetect::capture_cube(cv::Mat img)
{
	Mat dst = img.clone();
	cv::Point amplify_start;
	amplify_start.x = 256;
	amplify_start.y = 256;
	int side_length = 300;
	cv::Rect amplify_rect(amplify_start.x, amplify_start.y, side_length, side_length);
	cv::Mat amplify_ROI = dst(amplify_rect);
	cv::resize(amplify_ROI, amplify_ROI, Size(dst.cols, dst.rows), 0, 0, INTER_AREA);
	//imshow("Amplify", (amplify_ROI));
	//waitKey(0);
	return amplify_ROI;
}

//Funtion to get the color of the facelet of the cube
vector<char> svmDetect::detection(cv::Mat img, vector<char> facelet_label)
{

    vector<char> result;
    //const string lableName[6] = { "red", "yellow", "blue", "orange", "green", "white" };
    cv::Point cen_point;
    int cube_interval = 250;
    int ROI_inverval = 20;
    cen_point = svmDetect::find_central_point(img);
    int start_x = cen_point.x - cube_interval;
    int start_y = cen_point.y - cube_interval;
    int current_x = 0;
	int current_y = 0;
    int k = 0;
    for (int i = 0; i < 3; i++)
    {
        //Capture the ROI form the left_top of the cube
        current_y = start_y + i * cube_interval;
        for (int j = 0; j < 3; j++)
        {
            current_x = start_x + j * cube_interval;
            cv::Rect rect(current_x, current_y, 20, 20);
            cv::Mat ROI = img(rect);
            //Use the SVM
			std::string color_result = svmDetect::SVM_Color(ROI);
            result.push_back(svmDetect::color_code(color_result, facelet_label));
            k++;
        }
    }
    return result;
}


//Funtion to find the central point of the cube
cv::Point svmDetect::find_central_point(cv::Mat img)
{
    int x1 = 0;
	int x2 = 0;
	int y1 = 0;
	int y2 = 0;
	bool flag1 = false;
	bool flag2 = false;
	cv::Mat dst;
	//process with filter
	cv::bilateralFilter(img, dst, 8, 16, 5);
	//convert to grey picture
	cv::cvtColor(dst, dst, COLOR_BGR2GRAY);
	cv::Canny(dst, dst, 60, 70);
	//imshow("Canny", dst);
	//waitKey(3);

	//find the upper_left point
	for (int i = 0; i < int(dst.rows*0.25); i++)
	{
		uchar* data = dst.ptr<uchar>(i);
		for (int j = 0; j < int(0.25*dst.cols); j++)
		{
			if (data[j] == 255)
			{
				x1 = j;
				y1 = i;
				flag1 = true;
				break;
			}
		}

		if (flag1)
		{
			flag1 = false;
			break;
		}
	}

	//find th down_right point 
	for (int i = (dst.rows - 1); i > int(dst.rows*0.75); i--)
	{
		uchar* data = dst.ptr<uchar>(i);
		for (int j = dst.cols; j > int(0.75*dst.cols); j--)
		{
			if (data[j] == 255)
			{
				x2 = j;
				y2 = i;
				flag2 = true;
				break;
			}
		}

		if (flag2)
		{
			flag2 = false;
			break;
		}
		
	}

	//return the central point's coordinate
	return Point((x1 + x2) / 2, (y1 + y2) / 2);
}


//Funtion to get the coordinate using the mouse, which only be used to justify
void svmDetect::onMouse(int event, int x, int y, int flags, void* prarm)
{
    if(event == CV_EVENT_LBUTTONDOWN)
      printf("%d, %d\n", x, y); 
}


//Function to detect the color type using SVM(Support Vector Machine)
std::string svmDetect::SVM_Color(cv::Mat img)
{
    Ptr<cv::ml::SVM> model = Algorithm::load<cv::ml::SVM>("/home/xiaohuihui/catkin_ws/src/cube/svm_color.xml");
	//assert(model != nullptr);
	if (img.empty())
	{
		cout << "can not load  test image!" << endl;
	}
	const string lableName[6] = { "red", "yellow", "blue", "orange", "green", "white" };
	cv::resize(img, img, Size(300, 300), 0, 0, INTER_LINEAR);
	int featureSum = 3;
	Mat testDataMat = Mat::zeros(1, featureSum, CV_32FC1);
	Mat testLabelsMat;
	//求各通道均值
	Scalar test_rgbSum = sum(img);
	test_rgbSum = test_rgbSum / (img.rows * img.cols);
	//取前三个通道即BGR通道的均值作为特征值
	for (int j = 0; j < featureSum; j++)
	{
		testDataMat.at<float>(0, j) = test_rgbSum[j];
		//cout << test_rgbSum[j] << endl;
	}
	//使用训练好的SVM模型进行预测
	model->predict(testDataMat, testLabelsMat);
	//预测结果
	int testLabel = testLabelsMat.at<float>(0, 0);
	string response = lableName[testLabel];
	return response;
}

char svmDetect::color_code(std::string color,  vector<char> facelet_label)
{
	char facelets_color_code;
	if (color == "red")
		facelets_color_code = facelet_label[0];
	else if (color == "yellow")
		facelets_color_code = facelet_label[1];
	else if (color == "blue")
		facelets_color_code = facelet_label[2];
	else if (color == "orange")
		facelets_color_code = facelet_label[3];
	else if (color == "green")
		facelets_color_code = facelet_label[4];
	else if (color == "white")
		facelets_color_code = facelet_label[5];
	return facelets_color_code;
}


vector<char> svmDetect::establish_benchmark()
{
	//按照拍照顺序确定
	char facelet_label[6] = { 'F', 'B', 'L', 'R', 'U', 'D' };
	//顺序为red, yellow, blue, orange, green, white, 
	char live_label[6];
	//实时的颜色基准面信息
    vector<char> live_facelet_label;

	for (int i = 0; i < 6; i++)
	{
		Mat src = imread("F:/picture/cube/test/cube_" + to_string(i) + ".png");
		//cout << "加载成功！" << endl;
		cv::Point cen_point = find_central_point(src);
		cen_point.x = 932;
		cen_point.y = 578;
		Rect central_region(cen_point.x - 10, cen_point.y - 10, 20, 20);
		cv::Mat central_ROI = src(central_region);
		string outcoming = SVM_Color(central_ROI);
		if (outcoming == "red")
			live_label[0] = facelet_label[i];
		if (outcoming == "yellow")
			live_label[1] = facelet_label[i];
		if (outcoming == "blue")
			live_label[2] = facelet_label[i];
		if (outcoming == "orange")
			live_label[3] = facelet_label[i];
		if (outcoming == "green")
			live_label[4] = facelet_label[i];
		if (outcoming == "white")
			live_label[5] = facelet_label[i];
	}

    for (int j = 0; j < 6; j++)
	{
		live_facelet_label.push_back(live_label[j]);
	}

	return live_facelet_label;
	
}


//拍照服务回调函数
bool svmDetect::takephoto_server_Callback(cube::TakePhoto::Request &req, cube::TakePhoto::Response &res)
{
   cout << "taking photo..." << endl;
   image_transport::ImageTransport it(mNodeHandle);
   Imgsub  = it.subscribe("camera_base/image_row", 1, &svmDetect::ImageSubscribeCallback, this);
   return true;
}

//识别魔方颜色服务回调函数
bool svmDetect::detection_server_Callback(cube::Detection::Request &req, cube::Detection::Response &res)
{
	cout << "cube color detecting...." << endl;
	svmDetect::printResult();
    return true;
}

//订阅相机话题回调函数
void  svmDetect::ImageSubscribeCallback(const sensor_msgs::ImageConstPtr & msg)
{
	try
	{
		std::stringstream stream1;
		std::stringstream stream2;
		stream1 << "Goal CubeImage" << fileNum << ".jpg";
		stream2 << "/home/xiaohuihui/catkin_ws/src/cube/photo" << fileNum << ".jpg";
		std::string filename1 = stream1.str();
		std::string filename2 = stream2.str();
		cv::imwrite(filename2, cv_bridge::toCvShare(msg)->image);
		fileNum++;
		if( fileNum == 6)
		    fileNum = 0;
		cout << filename1 << " had saved." << endl;
	}
	catch (cv_bridge::Exception& e)
	{
		ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
	}

}