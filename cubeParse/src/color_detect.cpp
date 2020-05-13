#include "svmdetect.h"
#include "cube_solve.h"
#include <Python.h>

//Customize function
int HSV_Color_Judge(Mat img);
char* calculate(std::string solution);
vector<int> move_code(std::string solution);

using namespace std;


int main(int argc, char *argv[])
{
    std::string jiji = "RLLDUDRBRUBDURUULDFRBFFBBRBLFLDDUFBBDLUFLDURDFFFRBURLL";
	// char* sss = calculate(jiji);
    // cout << sss << endl;
	// vector<int> answer(move_code(sss));
	// for (int i = 0; i < answer.size(); ++i)
	//    cout << answer[i] << " ";
    // cout << "make" << endl;

	cubeSolve cube;
	// char* sss = cube.solve(jiji);
	// vector<int> answer( cube.move_code(sss) );
	// for (int i = 0; i < answer.size(); ++i)
	//    cout << answer[i] << " ";
    // cout << "make jjj" << endl;
	cube.settlement(jiji);

    return 0;
}


//Funtion to recognize the type of the color using HSV
int HSV_Color_Judge(cv::Mat img)
{
	cv::Mat matHSV;
	int color_code = 0;
	cv::cvtColor(img, matHSV, COLOR_BGR2HSV);
	vector<int>colorVec;
	colorVec.push_back(matHSV.at<uchar>(0, 0));
	colorVec.push_back(matHSV.at<uchar>(0, 1));
	colorVec.push_back(matHSV.at<uchar>(0, 2));

	if ((colorVec[0] >= 0 && colorVec[0] <= 180) && (colorVec[1] >= 0 && colorVec[1] <= 30) && (colorVec[2] >= 145 && colorVec[2] <= 255))
	{
		color_code = 0;
		//cout << "WHITE" << endl;
	}

	//((colorVec[0] >= 0 && colorVec[0] <= 10) || (colorVec[0] >= 156 && colorVec[0] <= 180)) && (colorVec[1] >= 43 && colorVec[1] <= 255) && (colorVec[2] >= 46 && colorVec[2] <= 255)
	else if ((colorVec[0] >= 156 && colorVec[0] <= 180) && (colorVec[1] >= 43 && colorVec[1] <= 255) && (colorVec[2] >= 96 && colorVec[2] <= 255))
	{
		color_code = 1;
		//cout << "RED" << endl;
	}

	else if ((colorVec[0] >= 8 && colorVec[0] <= 25) && (colorVec[1] >= 46 && colorVec[1] <= 255) && (colorVec[2] >= 46 && colorVec[2] <= 255))
	{
		color_code = 2;
		//cout << "ORANGE" << endl;
	}

	else if ((colorVec[0] >= 26 && colorVec[0] <= 34) && (colorVec[1] >= 43 && colorVec[1] <= 255) && (colorVec[2] >= 46 && colorVec[2] <= 255))
	{
		color_code = 3;
		//cout << "YELLOW" << endl;
	}

	else if ((colorVec[0] >= 35 && colorVec[0] <= 77) && (colorVec[1] >= 43 && colorVec[1] <= 255) && (colorVec[2] >= 46 && colorVec[2] <= 255))
	{
		color_code = 4;
		//cout << "GREEN" << endl;
	}

	else if ((colorVec[0] >= 100 && colorVec[0] <= 124) && (colorVec[1] >= 43 && colorVec[1] <= 255) && (colorVec[2] >= 46 && colorVec[2] <= 255))
	{
		color_code = 5;
		//cout << "BLUE" << endl;
	}

	else
	{
		color_code = 6;
		//cout << "UNKNOWN" << endl;
	}

	return color_code;
}



char* calculate(std::string solution)
{

	//初始化python
	Py_Initialize();
    if (!Py_IsInitialized())
	{
		printf("初始化失败！");
	}

	//直接运行python代码
	PyRun_SimpleString("print('----------Python Start')");

	//引入当前路径,否则下面模块不能正常导入
	PyRun_SimpleString("import sys"); 
    PyRun_SimpleString("sys.path.append('/home/xiaohuihui/catkin_ws/src/cube')"); //
    //PyRun_SimpleString("sys.path.append('/home/xiaohuihui/kociemba/kociemba-1.2')");
    //PyRun_SimpleString("print(sys.path)");

    //声明变量
    PyObject* pModule = NULL;
	// 声明变量
    PyObject* pFunc = NULL;

	//引入模块
	PyRun_SimpleString("print('----------PyImport_ImportModule!!!!')");
	
	//这里是要调用的.py文件名.py
    pModule = PyImport_ImportModule("CubeSolver");
	if (pModule == NULL)
	  std::cout << "没找到相关的.py文件可供执行,请检查有无此.py文件！" << std::endl;
    else
	  std::cout << "加载.py文件成功，可调用文件中已定义函数！" << std::endl;

	//这里是要调用的函数名
	pFunc = PyObject_GetAttrString(pModule, "solver");
	//pFunc = PyObject_GetAttrString(pModule, "hellos");
	if (pFunc == NULL)
	  std::cout << "没找到相关的函数可供执行,请检查有无定义此函数！" << std::endl;
	else
	  std::cout << "加载函数成功!" << std::endl;

	//需要输入的字符串参数
	//PyObject* pParams = Py_BuildValue("(s)", "RLLDUDRBRUBDURUULDFRBFFBBRBLFLDDUFBBDLUFLDURDFFFRBURLL");
	PyObject* pParams = Py_BuildValue( "(s)", solution.c_str() );
	//std::string* solution_result = NULL;
    char* solution_result = NULL;

	//调用函数
	PyObject* pRet = PyObject_CallObject(pFunc, pParams);

    PyArg_Parse(pRet, "s", &solution_result);
    
	//输出结果
	std::cout << "res: " << solution_result << std::endl; 
    
	//释放python
	Py_Finalize();

	return solution_result;

}

vector<int> move_code(std::string solution)
{
    vector<int> motion_code;
	string judge;
	//std::string solution = "D2 R' D' F2 B D R2 D2 R' F2 D' F2 U' B2 L2 U2 D R2 U";
	cout << solution << endl;
	string buf;
	stringstream ss(solution);
	vector<string>  tokens;
	while (ss >> buf)
		tokens.push_back(buf);
	for (size_t i = 0; i < tokens.size(); i++)
	{
		cout << tokens[i] << endl;
		judge = tokens[i];
		if (judge == "U")
			motion_code.push_back(0);
		else if (judge == "U2")
			motion_code.push_back(1);
		else if (judge == "U'")
			motion_code.push_back(2);
		else if (judge == "D")
			motion_code.push_back(3);
		else if (judge == "D2")
			motion_code.push_back(4);
		else if (judge == "D'")
			motion_code.push_back(5);
		else if (judge == "F")
			motion_code.push_back(6);
		else if (judge == "F2")
			motion_code.push_back(7);
		else if (judge == "F'")
			motion_code.push_back(8);
		else if (judge == "B")
			motion_code.push_back(9);
		else if (judge == "B2")
			motion_code.push_back(10);
		else if (judge == "B'")
			motion_code.push_back(11);
		else if (judge == "L")
			motion_code.push_back(12);
		else if (judge == "L2")
			motion_code.push_back(13);
		else if (judge == "L'")
			motion_code.push_back(14);
		else if (judge == "R")
			motion_code.push_back(15);
		else if (judge == "R2")
			motion_code.push_back(16);
		else if (judge == "R'")
			motion_code.push_back(17);
		//cout << motion_code[i] << endl;

	}
	return motion_code;
}