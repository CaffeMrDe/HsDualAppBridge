#include "solve.h"


Solve::Solve( ros::NodeHandle n)
{
     nh = n;
}

Solve::~Solve()
{
    solution_supervise_pub.shutdown();
    solution_pub.shutdown();

}

void Solve::start()
{
     //初始化服务和发布话题
     solution_pub = nh.advertise<std_msgs::Int8MultiArray>("cube_solution", 1000);
     solution_supervise_pub = nh.advertise<std_msgs::Bool>("solution_situation", 1);
     solvecubeServer = nh.advertiseService(SOLVE_SERVER_NAME, &Solve::solvecube_server_Callback, this);
     correctionServer = nh.advertiseService(CORRECTION_SERVER_NAME, &Solve::correction_server_Callback, this);
}

vector<int> Solve::operation()
{
      //创建对象
      svmDetect s(nh);
      cubeSolve t;

      vector<char> color_answer_vector ( s.getResult() );
      std::string str = "";

      //将颜色向量转换为颜色字符串
      for(vector<char>::iterator i = color_answer_vector.begin(); i != color_answer_vector.end(); ++i)
         str += *i;

      //打印检测
      //cout << "魔方颜色序列为: " << endl;
      cout << str << endl;

      //得到解算指令
      vector<int> motion_answer( t.settlement(str) );

      //返回指令
      return motion_answer;
}

vector<int> Solve::reoperation(string c)
{
    //创建对象
    correct h;
    cubeSolve t;

    vector<char> color_answer_vector( h.getResult(c));
    string str = "";
    for(vector<char>::iterator iter = color_answer_vector.begin(); iter != color_answer_vector.end(); ++iter)
         str += *iter;
    cout << "颜色序列为:" << endl; 
    cout << str << endl;

    //执行解算
    vector<int> motion_answer( t.settlement(str) );
    
    return motion_answer;
}

//解算魔方服务回调函数
bool Solve::solvecube_server_Callback(cubeParse::SolveCube::Request &req, cubeParse::SolveCube::Response &res)
{
    std_msgs::Int8MultiArray data;

    cout << "solving cube..."<< endl;
    vector<int> final_solution(Solve::operation());
    
    if ( final_solution.size() == 1 && final_solution[0] == 18 ) 
    {
        solve_judge.data = false;
        solution_supervise_pub.publish(solve_judge);
        ros::Duration(0.5).sleep();
    }

    else
    {
         for(size_t i = 0; i < final_solution.size(); ++i)
         {
            data.data.push_back(final_solution[i]);
            cout << final_solution[i] << " ";
         }

         solve_judge.data = true;
         solution_supervise_pub.publish(solve_judge);
         ros::Duration(0.5).sleep();
         solution_pub.publish(data);
         ros::Duration(0.5).sleep();

         cout << endl;
         cout << "发送解算魔方指令完毕！" << endl;

    }
    
}

//更改魔方序列重新解算回调函数
bool Solve::correction_server_Callback(rb_msgAndSrv::rb_string::Request &req, rb_msgAndSrv::rb_string::Response &res)
{
    string update_color_string = req.data.data;
    std_msgs::Int8MultiArray data;

    cout << "solving cube..."<< endl;

    vector<int> final_solution(Solve::reoperation(update_color_string));

    if ( final_solution.size() == 1 && final_solution[0] == 18 ) 
    {
        solve_judge.data = false;
        solution_supervise_pub.publish(solve_judge);
        ros::Duration(0.5).sleep();
    }

    else
    {
         for(size_t i = 0; i < final_solution.size(); ++i)
         {
            data.data.push_back(final_solution[i]);
            cout << final_solution[i] << " ";
         }

         solve_judge.data = true;
         solution_supervise_pub.publish(solve_judge);
         ros::Duration(0.5).sleep();
         solution_pub.publish(data);
         ros::Duration(0.5).sleep();

         cout << endl;
         cout << "发送解算魔方指令完毕！" << endl;
    }

}