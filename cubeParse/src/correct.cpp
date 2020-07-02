#include "correct.h"


correct::correct()
{

}

correct::~correct()
{

}

vector<char> correct::getResult(string c)
{
    //将string转为vector<char>
    vector<char> update_color;
    update_color.resize(c.size());
    update_color.assign(c.begin(), c.end());
    // cout << "打印接收信息" << endl;
    // cout << update_color.size() << endl;
    // for(size_t i = 0; i < update_color.size(); i++)
    //    cout << update_color[i] << " ";
    // cout << endl;

    //确定基准面信息
    vector<char> live_benchmark(correct::benchmark(update_color));
  
    //进行编码 
    vector<char> updata_color_code;
    for(size_t i = 0; i < update_color.size(); i++)
    {
        char color_code = correct::color_code(update_color[i], live_benchmark);
        updata_color_code.push_back(color_code);
        cout << color_code << " ";
    }
    cout << endl;

    return updata_color_code;
}


vector<char> correct::benchmark(vector<char> c)
{
    char facelet_label[6] = { 'R', 'U', 'D', 'L', 'F', 'B' };
    int central_facelet[6] = {13, 4, 31, 40, 22, 49};
    char live_label[6];
    vector<char> live_facelet_label;

    //确定标准面信息
    for (int i = 0; i < 6; i++)
    {
        if ( c[central_facelet[i]] == 'R' )
          live_label[0] = facelet_label[i];

        if ( c[central_facelet[i]] == 'Y' )
          live_label[1] = facelet_label[i];
          
        if ( c[central_facelet[i]] == 'B' )
          live_label[2] = facelet_label[i];

        if ( c[central_facelet[i]] == 'O' )
          live_label[3] = facelet_label[i];

        if ( c[central_facelet[i]] == 'G' )
          live_label[4] = facelet_label[i];

        if ( c[central_facelet[i]] == 'W' )
          live_label[5] = facelet_label[i];
    }

    cout << "基准面信息为:" << endl;
    //生成基准面序列向量
    for (int j = 0; j < 6; j++)
    {
       cout << facelet_label[j] << ":" <<  c[central_facelet[j]] << " ";
       live_facelet_label.push_back(live_label[j]);
    }
	  cout << endl;

    //返回基准面序列向量
    return live_facelet_label;
}

char correct::color_code(char color,  vector<char> facelet_label)
{

	char facelets_color_code;

	if (color == 'R')
		facelets_color_code = facelet_label[0];

	else if (color == 'Y')
		facelets_color_code = facelet_label[1];

	else if (color == 'B')
		facelets_color_code = facelet_label[2];

	else if (color == 'O')
		facelets_color_code = facelet_label[3];

	else if (color == 'G')
		facelets_color_code = facelet_label[4];

	else if (color == 'W')
		facelets_color_code = facelet_label[5];
    
    //返回编码后的颜色码
	return facelets_color_code;
}





