/**
* @version 	v1.0.1
* @file		cube_solve.cpp
* @brief	解算魔方相关函数
* @date		2020/5/12
*/


#include "cube_solve.h"

cubeSolve::cubeSolve()
{
	//cout << "solving the cube......" << endl;
}

cubeSolve::~cubeSolve()
{

}

vector<int>  cubeSolve::settlement(std::string c)
{
    //cout << "解算魔方中..." << endl;
	char* sss = cubeSolve::ko_solve(c);
	vector<int> answer( cubeSolve::move_code(sss) );

	for ( size_t i = 0; i < answer.size(); ++i)
	   cout << answer[i] << " ";
    cout << endl;
	cout << "解算输出完成！" << endl;
	return answer;
}


char* cubeSolve::ko_solve(std::string color_code)
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
    PyRun_SimpleString("sys.path.append('/home/de/catkin_ws/src/HsDualAppBridge/cubeParse/')"); //
    //PyRun_SimpleString("sys.path.append('/home/xiaohuihui/kociemba/kociemba-1.2')");
    //PyRun_SimpleString("print(sys.path)");

    //声明变量
    PyObject* pModule = NULL;
	// 声明变量
    PyObject* pFunc = NULL;

	//引入模块
	PyRun_SimpleString("print('----------PyImport_ImportModule!!!!')");
	
	//这里是要调用的.py文件名
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
	PyObject* pParams = Py_BuildValue( "(s)", color_code.c_str() );

	//调用函数
	PyObject* pRet = PyObject_CallObject(pFunc, pParams);
	

	char* solution_result = NULL;
    PyArg_Parse(pRet, "s", &solution_result);

	Py_XDECREF(pParams);
	Py_XDECREF(pRet);
    
	//输出结果
	std::cout << "res: " << solution_result << std::endl; 

	//释放python
	Py_Finalize();
	// delete[] solution_result;
    return solution_result;
}


vector<int> cubeSolve::move_code(std::string solution)
{
    vector<int> motion_code;
	string judge;
	//std::string solution = "D2 R' D' F2 B D R2 D2 R' F2 D' F2 U' B2 L2 U2 D R2 U";
	//cout << solution << endl;
	string buf;
	stringstream ss(solution);
	vector<string>  tokens;
	while (ss >> buf)
		tokens.push_back(buf);
	for (size_t i = 0; i < tokens.size(); i++)
	{
		//cout << tokens[i] << endl;
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