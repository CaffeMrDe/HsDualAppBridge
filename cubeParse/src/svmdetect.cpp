/**
* @version 	v1.0.1
* @file		svmdetect.cpp
* @brief	魔方检测相关函数
* @date		2020/5/12
*/

#include "svmdetect.h"

svmDetect::svmDetect(NodeHandle n)
{
	//初始化节点
    mNodeHandle = n;
	fileNum = 0;
	imglistPub = mNodeHandle.advertise<rb_msgAndSrv::rbImageList>("cube_image", 1);
}

svmDetect::~svmDetect()
{
   
}

void svmDetect::start()
{
    //发布服务
	takephotoServer =  mNodeHandle.advertiseService(TAKE_PHOTO_SERVER_NAME, &svmDetect::takephoto_server_Callback, this);
	detectionServer = mNodeHandle.advertiseService(DETECTION_SERVER_NAME, &svmDetect::detection_server_Callback, this);
}

vector<char> svmDetect::getResult()
{
	vector<char> label = svmDetect::establish_benchmark();
	vector<char> totoal_result;
	//按照算法要求的U、R、F、D、L、B的顺序读取图片得出颜色序列
	int read_order[6] = {1, 0, 4, 2, 3, 5};
	for ( int i = 0; i < 6; i++ )
	{
		Mat img_cube = cv::imread(pathSave + to_string(read_order[i]) + ".png");
        vector<char> singleface_result( svmDetect::detection(img_cube, label));
		for ( size_t j = 0; j <  singleface_result.size(); ++j)
		   totoal_result.push_back(singleface_result[j]);
        //singleface_result.clear();
		vector<char>().swap(singleface_result);
	}


    cout <<  "魔方的颜色序列为: " << endl;
	for ( size_t k = 0; k <  totoal_result[k]; k++)
	    std::cout <<  totoal_result[k] ;
    cout << endl;
	
	return totoal_result;

}

void svmDetect::printResult()
{
	cout << "开始进行颜色识别" << endl;
	vector<char> label = svmDetect::establish_benchmark();
	int count = 0;
	string facelet_name[6] = {"魔方右面", "魔方上面", "魔方底面", "魔方左面", "魔方前面", "魔方后面"};

	//依次读取照片进行颜色识别
	for ( int num = 0; num < 6; num++ )
	{
		Mat img_cube = cv::imread(pathSave + to_string(num) + ".png");

		int cube_interval = 200;
		int ROI_inverval = 20;

		cv::Point cen_point(300, 300);
		int start_x = (cen_point.x - cube_interval) - 10;
		int start_y = (cen_point.y - cube_interval) - 10;
		int current_x = 0;
		int current_y = 0;
        
		//画魔方展示图相关参数
		cv::Point draw_point(20, 20);
        int draw_point_shift = 190;
		cv::Point current_draw_point;
		cv::Mat cube_model = cv::Mat( 600, 600, CV_8UC3, Scalar(0, 0, 0) ); 
		cv::Mat cube_real;

		cout << facelet_name[count] << ": " ;
		for (int i = 0; i < 3; i++)
		{
			//Capture the ROI form the left_top of the cube
			current_y = start_y + i * cube_interval;
			current_draw_point.y = draw_point.y + i * draw_point_shift;
			for (int j = 0; j < 3; j++)
			{
				//截取所要进行检测的区域
				current_x = start_x + j * cube_interval;
				current_draw_point.x = draw_point.x + j * draw_point_shift;
				cv::Rect rect(current_x, current_y, ROI_inverval, ROI_inverval);
				cv::Mat ROI = img_cube(rect);

				//使用SVM进行颜色识别
				std::string color_result = svmDetect::SVM_Color(ROI);
                
				//画展示图和进行图片颜色文本框输入
				svmDetect::WriteText(img_cube, color_result, cv::Point(current_x, current_y));
				svmDetect::filling_color(cube_model, color_result, current_draw_point);

				cout << color_result << " ";
				
			}
		}
        
		//进行图拼接并保存最后的识别效果图
		cv::hconcat(img_cube, cube_model, cube_real);
		cv::imwrite(pathShow + to_string(num) + ".png", cube_real);
		//cv::imwrite(pathShow + to_string(num) + ".png", cube_model);
        
		count++;
		cout << endl;
	}
}




cv::Mat svmDetect::capture_cube(cv::Mat img, int x1, int y1, int x2, int y2)
{
	//截取魔方区域
	Mat dst = img.clone();
	Point amplify_start(x1, y1);
	int side_length = int(((x2 - x1) + (y2 - y1)) / 2);
	Rect amplify_rect(amplify_start.x, amplify_start.y, side_length, side_length);
	Mat amplify_ROI = dst(amplify_rect);
	//imshow("Amplify", (amplify_ROI));
	//waitKey(0);
	return amplify_ROI;
}


//Funtion to get the color of the facelet of the cube
vector<char> svmDetect::detection(cv::Mat img, vector<char> facelet_label)
{

    vector<char> result;
    //const string lableName[6] = { "red", "yellow", "blue", "orange", "green", "white" };
    cv::Point cen_point(300, 300);
    int cube_interval = 200;
    int ROI_inverval = 20;
    int start_x = (cen_point.x - cube_interval) - 10;
    int start_y = (cen_point.y - cube_interval) - 10;
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
            cv::Rect rect(current_x, current_y, ROI_inverval, ROI_inverval);
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
	//进行滤波处理
	cv::bilateralFilter(img, dst, 8, 16, 5);
	//转换为灰度图
	cv::cvtColor(dst, dst, COLOR_BGR2GRAY);
	cv::Canny(dst, dst, 60, 70);
	//imshow("Canny", dst);
	//waitKey(3);

	//找到左上点
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

	//找到右下点
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

	//返回计算后的中心点
	return Point((x1 + x2) / 2, (y1 + y2) / 2);
}


void svmDetect::onMouse(int event, int x, int y, int flags, void* prarm)
{
    if(event == CV_EVENT_LBUTTONDOWN)
      printf("%d, %d\n", x, y); 
}


//Function to detect the color type using SVM(Support Vector Machine)
std::string svmDetect::SVM_Color(cv::Mat img)
{
    Ptr<cv::ml::SVM> model = Algorithm::load<cv::ml::SVM>(pahtloadSvm);
	//assert(model != nullptr);
	if (img.empty())
	{
		cout << "can not load  test image!" << endl;
	}
	const string lableName[6] = { "red", "yellow", "blue", "orange", "green", "white" };
	resize(img, img, Size(300, 300), 0, 0, INTER_LINEAR);
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
	svmDetect::ProcessImage();
	//按照拍照顺序确定
	char facelet_label[6] = { 'R', 'U', 'D', 'L', 'F', 'B' };
	//顺序为red, yellow, blue, orange, green, white, 
	char live_label[6];
	//实时的颜色基准面信息
    vector<char> live_facelet_label;
	string live_outcoming[6];

	for (int i = 0; i < 6; i++)
	{
		Mat src = imread(pathSave + to_string(i) + ".png");
		//cout << "加载成功！" << endl;
		cv::Point cen_point(300, 300);
		Rect central_region(cen_point.x - 10, cen_point.y - 10, 20, 20);
		cv::Mat central_ROI = src(central_region);

		string outcoming = SVM_Color(central_ROI);
		live_outcoming[i] = outcoming;
        
		//根据颜色确立各基准面
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

		outcoming.clear();
	}

	//打印基准面信息
    cout << "魔方基准面信息为:" << endl;
    for (int j = 0; j < 6; j++)
	{
		live_facelet_label.push_back(live_label[j]);
		cout << facelet_label[j] << ":" << live_outcoming[j] << " ";
	}
	cout << endl;

	return live_facelet_label;
	
}


vector<vector<int>> svmDetect::makeMatrix()
{
	//建立6*4矩阵
	vector<vector<int>> array(6);
	const int col = 4;
	for (int i = 0; i < 6; i++)
	{
		array[i].resize(col);
	}

	//输入截取6张图的魔方的矩阵数据

    /*-----cube_0(Right)----*/
	array[0][0] = Right_x1;
	array[0][1] = Right_y1;
	array[0][2] = Right_x2;
	array[0][3] = Right_y2;

	/*-----cube_1(Up)------ */
	array[1][0] = Up_x1;
	array[1][1] = Up_y1;
	array[1][2] = Up_x2;
	array[1][3] = Up_y2;

	/*-----cube_2(Down)---- */
	array[2][0] = Down_x1;
	array[2][1] = Down_y1;
	array[2][2] = Down_x2;
	array[2][3] = Down_y2;

	/*-----cube_3(Left)-----*/
	array[3][0] = Left_x1;
	array[3][1] = Left_y1;
	array[3][2] = Left_x2;
	array[3][3] = Left_y2;

	/*-----cube_4(Front)-----*/
	array[4][0] = Front_x1;
	array[4][1] = Front_y1;
	array[4][2] = Front_x2;
	array[4][3] = Front_y2;

	/*-----cube_5(Back)-----*/
	array[5][0] = Back_x1;
	array[5][1] = Back_y1;
	array[5][2] = Back_x2;
	array[5][3] = Back_y2;

	//打印出矩阵
	/*for (int r = 0; r < 6; r++)
	{
		for (int c = 0; c < 4; c++)
		{
			cout << array[r][c] << " ";
		}
		cout << endl;
	}*/
    
	//返回矩阵
	return array;
}


cv::Mat svmDetect::imgRotate(cv::Mat img, double angle)
{
	//旋转中心
	Point center(img.rows / 2, img.cols / 2);
	//缩放系数
	double scale = 1.0;
	Mat rotMat = getRotationMatrix2D(center, angle, scale);
	//对图片进行仿射矩阵变化
	warpAffine(img, img, rotMat, img.size());
	return img;
}

cv::Mat svmDetect::WhiteBalance(cv::Mat img)
{
	vector<Mat> imageRGB;

	//RGB三通道分离
	split(img, imageRGB);

	//求原始图像的RGB分量的均值
	double R, G, B;
	B = mean(imageRGB[0])[0];
	G = mean(imageRGB[1])[0];
	R = mean(imageRGB[2])[0];

	//需要调整的RGB分量的增益
	double KR, KG, KB;
	KB = (R + G + B) / (3 * B);
	KG = (R + G + B) / (3 * G);
	KR = (R + G + B) / (3 * R);

	//调整RGB三个通道各自的值
	imageRGB[0] = imageRGB[0] * KB;
	imageRGB[1] = imageRGB[1] * KG;
	imageRGB[2] = imageRGB[2] * KR;

	//RGB三通道图像合并
	merge(imageRGB, img);
	
	return img;
}


void svmDetect::ProcessImage()
{
    vector<vector<int>> matrix(svmDetect::makeMatrix());
	for( int i = 0; i < 6; i++)
	{
		cv::Mat imgOriginal = cv::imread(pathCurrent + to_string(i) + ".png");

		//旋转预处理
		if (i == 2)
			imgOriginal = imgRotate(imgOriginal, -2.0);
		if (i == 3)
			imgOriginal = imgRotate(imgOriginal, -5.0);
		if (i == 4)
			imgOriginal = imgRotate(imgOriginal, -2.0);
		if (i == 5)
			imgOriginal = imgRotate(imgOriginal, -3.0);
		
		cv::Mat imgCapture = capture_cube(imgOriginal, matrix[i][0], matrix[i][1], matrix[i][2], matrix[i][3]);
		cv::resize(imgCapture, imgCapture, Size(600, 600), 0, 0, INTER_LINEAR);
		//imgCapture = svmDetect::WhiteBalance(imgCapture);

		//二次旋转处理
		if (i == 1 || i == 2 || i == 5)
			imgCapture = imgRotate(imgCapture, 90.0);
		if (i == 3 || i == 4)
			imgCapture = imgRotate(imgCapture, -90.0);

		//保存图片	
		imwrite(pathSave + to_string(i) + ".png", imgCapture);
	}
}


void svmDetect::WriteText(cv::Mat img, std::string color, cv::Point p)
{
	cv::Point text_point;
	text_point.x = p.x ;
	text_point.y = p.y + 20 ;
    
	//根据颜色信息在图像上输入文本框
	if (color == "red")
	  cv::putText(img, "R", text_point,  cv::FONT_HERSHEY_COMPLEX, 2, cv::Scalar(0, 0, 0), 1, 8, 0);
	else if (color == "blue")
      cv::putText(img, "B", text_point,  cv::FONT_HERSHEY_COMPLEX, 2, cv::Scalar(0, 0, 0), 1, 8, 0);
	else if (color == "yellow")
	  cv::putText(img, "Y", text_point,  cv::FONT_HERSHEY_COMPLEX, 2, cv::Scalar(0, 0, 0), 1, 8, 0);
	else if (color == "orange")
	  cv::putText(img, "O", text_point,  cv::FONT_HERSHEY_COMPLEX, 2, cv::Scalar(0, 0, 0), 1, 8, 0);
	else if (color == "green")
	  cv::putText(img, "G", text_point,  cv::FONT_HERSHEY_COMPLEX, 2, cv::Scalar(0, 0, 0), 1, 8, 0);
	else if (color == "white")
	  cv::putText(img, "W", text_point,  cv::FONT_HERSHEY_COMPLEX, 2, cv::Scalar(0, 0, 0), 1, 8, 0);

}

void svmDetect::filling_color(cv::Mat img, std::string color, cv::Point p)
{
	cv::Point end;
	end.x = p.x + 180;
	end.y = p.y + 180; 

	//Scalar(B, G, R)
	if (color == "red")
      rectangle(img, p, end, Scalar(0, 0, 255), -1, 4);
	else if (color == "blue")
	  rectangle(img, p, end, Scalar(255, 0, 0), -1, 4);
	else if (color == "yellow")
      rectangle(img, p, end, Scalar(0, 255, 255), -1, 4);
	else if (color == "orange")
	  rectangle(img, p, end, Scalar(0, 165, 255), -1, 4);
	else if (color == "green")
      rectangle(img, p, end, Scalar(0, 255, 0), -1, 4);
	else if (color == "white")
	  rectangle(img, p, end, Scalar(255, 255, 255), -1, 4);

}


//拍照服务回调函数
bool svmDetect::takephoto_server_Callback(cubeParse::TakePhoto::Request &req, cubeParse::TakePhoto::Response &res)
{
   cout << "taking photo..." << endl;
   fileNum = req.photoNum;
   //cout << fileNum << endl;
   image_transport::ImageTransport it(mNodeHandle);
   if(fileNum < 3)
     Imgsub  = it.subscribe("/camera_base/color/image_raw", 1, &svmDetect::ImageSubscribeCallback, this);
   else
     Imgsub  = it.subscribe("/camera_base_right/color/image_raw", 1, &svmDetect::ImageSubscribeCallback, this);
   cout << "Succeed in taking photo" << endl;
   //Imgsub.shutdown();
   return true;
}

//识别魔方颜色服务回调函数
bool svmDetect::detection_server_Callback(cubeParse::Detection::Request &req, cubeParse::Detection::Response &res)
{
	cout << "cube color detecting...." << endl;

	svmDetect::printResult();
	image_transport::ImageTransport it(mNodeHandle);
	// Imgpub = it.advertise("cube_image", 1);
	ros::Duration(0.5).sleep();
	

	rb_msgAndSrv::rbImageList imglist;
	imglist.imagelist.resize(6);
	for(int i = 0; i < 6; i++)
	{
		cv::Mat image = cv::imread(pathShow + to_string(i) + ".png", CV_LOAD_IMAGE_COLOR);
		sensor_msgs::ImagePtr msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", image).toImageMsg();
		imglist.imagelist[i].data = msg->data;
		cout << "图片" << i << "发送成功" << endl;
	}

	imglistPub.publish(imglist);
	ros::Duration(0.5).sleep();

	cout << "图片发送完毕，请注意接收" << endl;
	// Imgpub.shutdown();
	// imglistPub.shutdown();
    return true;
}

//订阅相机话题回调函数
void  svmDetect::ImageSubscribeCallback(const sensor_msgs::ImageConstPtr & msg)
{
    cout << "进入回调函数成功!" << endl;
	try
	{
		cout << "保存照片中..." << endl;
		stream1 << "Goal CubeImage" << fileNum << ".png";
		stream2 << pathCurrent << std::to_string(fileNum) << ".png";
		filename1 = stream1.str();
		filename2 = stream2.str();
		cv::Mat temp = cv_bridge::toCvShare(msg)->image.clone();
		cvtColor(temp,temp,cv::COLOR_BGR2RGB);
		cv::imwrite(filename2, temp);
		fileNum++;
		if( fileNum == 6)
		    fileNum = 0;
		cout << filename1 << " had saved." << endl;
           
		Imgsub.shutdown();
		stream1.str("");
		stream2.str("");
	}

	catch (cv_bridge::Exception& e)
	{
		ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
		cout <<  "拍照失败" << endl;
	}

}