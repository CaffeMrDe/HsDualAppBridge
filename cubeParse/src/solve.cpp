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
     
     solution_pub = nh.advertise<std_msgs::Int8MultiArray>("cube_solution", 1000);
     solvecubeServer = nh.advertiseService(SOLVE_SERVER_NAME, &Solve::solvecube_server_Callback, this);
}

vector<int> Solve::operation()
{
      svmDetect s(nh);
      cubeSolve t;
      vector<char> color_answer_vector ( s.getResult() );
      std::stringstream stream;
      for(size_t i; i < color_answer_vector.size(); ++i)
         stream << color_answer_vector[i];
      std::string color_answer_string = stream.str();
      cout << "魔方颜色序列为: " << endl;
      cout << color_answer_string << endl;
      vector<int> motion_answer( t.settlement( color_answer_string) );

      stream.str("");
      return motion_answer;
}

//解算魔方服务回调函数
bool Solve::solvecube_server_Callback(cubeParse::SolveCube::Request &req, cubeParse::SolveCube::Response &res)
{
    std_msgs::Int8MultiArray data;
    cout << "solving cube..."<< endl;
    vector<int> final_solution(Solve::operation());
    for(size_t i = 0; i < final_solution.size(); ++i)
        data.data.push_back(final_solution[i]);
    solution_pub.publish(data);
}