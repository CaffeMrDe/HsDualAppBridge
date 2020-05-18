#include <communication_bridge/util_robConnUI.h>

RobConnUI::RobConnUI(ros::NodeHandle* node):Node(node)
{
    server_rbConnCommand = Node->advertiseService("/Rb_connCommand", &RobConnUI::callback_rbConnCommand,this);
    server_rbRunCommand = Node->advertiseService("/Rb_runCommand", &RobConnUI::callback_rbRunCommand,this);
    server_magicGetDatapCommand = Node->advertiseService("/MagicGetDataCommand", &RobConnUI::callback_magicGetDatapCommand,this);
    server_magicSolveCommand = Node->advertiseService("/MagicSolveCommand", &RobConnUI::callback_magicSolveCommand,this);
    server_magicRunSolverCommand = Node->advertiseService("/MagicRunSolveCommand", &RobConnUI::callback_magicRunSolverCommand,this);
    server_rbGrepSetCommand = Node->advertiseService("/Rb_grepSetCommand", &RobConnUI::callback_rbGrepSetCommand,this);
    publisher_rbConnStatus=Node->advertise<std_msgs::UInt8MultiArray>("/Rb_connStatus", 1);
//    QObject::connect(pushButton_7,&QPushButton::clicked,this,&RobConnUI::rbConnStatus);
    publisher_rbErrStatus=Node->advertise<std_msgs::UInt16MultiArray>("/Rb_errStatus", 1);
//    QObject::connect(pushButton_8,&QPushButton::clicked,this,&RobConnUI::rbErrStatus);
    subscriber_rbStop=Node->subscribe<std_msgs::Bool>("/Rb_stopCommand", 1,&RobConnUI::callback_rbStop_subscriber,this);
}

RobConnUI::~RobConnUI()
{
}

void RobConnUI::callback_rbStop_subscriber(std_msgs::Bool msg){
    if(msg.data){
        cout<<"接收到机器人停止命令"<<endl;
    } else{
        cout<<"没有接收到机器人停止命令"<<endl;
    }
}

void RobConnUI::rbConnStatus(){
    cout<<"点击了连按钮"<<endl;
    std_msgs::UInt8MultiArray msg;
    msg.data.resize(2);
    msg.data[0]=1;
    msg.data[1]=1;
    publisher_rbConnStatus.publish(msg);
}
void RobConnUI::rbErrStatus(){
    cout<<"点击了故障按钮"<<endl;
    std_msgs::UInt16MultiArray msg;
    msg.data.resize(2);
    msg.data[0]=1;
    msg.data[1]=1;
    publisher_rbErrStatus.publish(msg);
}
bool RobConnUI::callback_rbConnCommand(communication_bridge::rb_DoubleBoolRequest& request,communication_bridge::rb_DoubleBoolResponse& response){
    for (int i = 0; i < 99999; ++i) {
        if(request.request){
            cout<<"--"<<i<<"收到请求"<<endl;
        }
    }
    response.respond= true;
    cout<<"发出完成信号"<<endl;
}

bool RobConnUI::callback_rbRunCommand(communication_bridge::rb_DoubleBoolRequest& request,communication_bridge::rb_DoubleBoolResponse& response){
    for (int i = 0; i < 99999; ++i) {
        if(request.request){
            cout<<"--"<<i<<"收到请求"<<endl;
        }
    }
    response.respond= true;
    cout<<"发出完成信号"<<endl;
}

bool RobConnUI::callback_magicGetDatapCommand(communication_bridge::rb_DoubleBoolRequest& request,communication_bridge::rb_DoubleBoolResponse& response){
    for (int i = 0; i < 99999; ++i) {
        if(request.request){
            cout<<"--"<<i<<"收到请求"<<endl;
        }
    }
    response.respond= true;
    cout<<"发出完成信号"<<endl;
}

bool RobConnUI::callback_magicSolveCommand(communication_bridge::rb_DoubleBoolRequest& request,communication_bridge::rb_DoubleBoolResponse& response){
    for (int i = 0; i < 99999; ++i) {
        if(request.request){
            cout<<"--"<<i<<"收到请求"<<endl;
        }
    }
    response.respond= true;
    cout<<"发出完成信号"<<endl;
}

bool RobConnUI::callback_magicRunSolverCommand(communication_bridge::rb_DoubleBoolRequest& request,communication_bridge::rb_DoubleBoolResponse& response){
    for (int i = 0; i < 99999; ++i) {
        if(request.request){
            cout<<"--"<<i<<"收到请求"<<endl;
        }
    }
    response.respond= true;
    cout<<"发出完成信号"<<endl;
}

bool RobConnUI::callback_rbGrepSetCommand(communication_bridge::rb_ArrayAndBoolRequest& request,communication_bridge::rb_ArrayAndBoolResponse& response){
    for (int i = 0; i < 99999; ++i) {
        cout<<"--"<<i<<"收到请求"<<endl;
    }
    request.data.resize(3);
    cout<<"收到请求数据"<<request.data[0]<<request.data[1]<<request.data[2]<<endl;
    response.respond= true;
    cout<<"发出完成信号"<<endl;
}

bool RobConnUI::checkNet(std::string URL) {
    /*
   -c 2（代表ping次数，ping 2次后结束ping操作） -w 2（代表超时时间，2秒后结束ping操作）
*/
//    system("ping %s -c 2 -w 2 >netlog.bat", URL.c_str());
    string tmp_command="ping "+ URL+" -c 2 -w 2 >netlog.bat";
    system(tmp_command.c_str());
    sleep(2);

    //把文件一行一行读取放入vector
    ifstream infile;
    infile.open("netlog.bat");
    string s;
    vector<string> v;
    while(infile)
    {
        getline(infile,s);
        if(infile.fail())
            break;
        v.push_back(s);
    }
    infile.close();

    //读取倒数第二行 2 packets transmitted, 2 received, 0% packet loss, time 1001ms
    if (v.size() > 1)
    {
        string data = v[v.size()-2];
        int iPos = data.find("received,");
        if (iPos != -1 )
        {
            data = data.substr(iPos+10,3);//截取字符串返回packet loss
            int  n = atoi(data.c_str());
            if(n == 0)
                return 1;
            else
                return 0 ;
        }

    }else
    {
        return 0;
    }
}


bool RobConnUI::checkAllNect()
{
    vector<string> urlList = {"10.10.56.214"};
    for(int i=0; i<urlList.size(); ++i)
    if (checkNet(urlList[i]))
    {
        printf("%s: 网络连接成功\n", urlList[i].c_str());
    }
    else
    {
        printf("%s: 网络连接失败\n", urlList[i].c_str());
    }
}

bool RobConnUI::stopCommand()
{
    system("rosservice call /UR51/set_robot_enable 'enable: false'");
    system("rosservice call /UR52/set_robot_enable 'enable: false'");
    system("rosservice call /UR51/clear_robot_fault '{}'");
    system("rosservice call /UR52/clear_robot_fault '{}'");
}