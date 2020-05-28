#include "solve.h"


Solve::Solve( ros::NodeHandle n)
{
     nh = n;
}

Solve::~Solve()
{

}

void Solve::start()
{
     //初始化服务和发布话题
     solution_pub = nh.advertise<std_msgs::Int8MultiArray>("cube_solution", 1000);
     solvecubeServer = nh.advertiseService(SOLVE_SERVER_NAME, &Solve::solvecube_server_Callback, this);
}

vector<int> Solve::operation()
{
      //创建对象
      svmDetect s(nh);
      cubeSolve t;

      vector<char> color_answer_vector ( s.getResult() );
      std::stringstream stream;
      //将颜色向量转换为颜色字符串
      for(size_t i; i < color_answer_vector.size(); ++i)
         stream << color_answer_vector[i];
      //打印颜色字符串结果
      std::string color_answer_string = stream.str();
      
      //打印检测
      //cout << "魔方颜色序列为: " << endl;
      //cout << color_answer_string << endl;

      //得到解算指令
      vector<int> motion_answer( t.settlement( color_answer_string) );

      stream.str("");
      //返回指令
      return motion_answer;
}

//解算魔方服务回调函数
bool Solve::solvecube_server_Callback(cubeParse::SolveCube::Request &req, cubeParse::SolveCube::Response &res)
{
    std_msgs::Int8MultiArray data;

    cout << "solving cube..."<< endl;
    vector<int> final_solution(Solve::operation());
    
    //进行数据转换
    for(size_t i = 0; i < final_solution.size(); ++i)
        data.data.push_back(final_solution[i]);
    //发送解算指令
    solution_pub.publish(data);
    cout << "魔方解算指令发送完毕,请注意查收!" << endl;
    ros::Duration(1).sleep();
    
    solution_pub.shutdown();
}