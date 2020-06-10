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
    vector<char> update_color(c.size());
    copy(c.begin(), c.end(), update_color.begin());

    //确定基准面信息
    vector<char> live_benchmark(update_color);

    vector<char> updata_color_code;
    for(size_t  i = 0; i < update_color.size(); i++)
    {
        char color_code = correct::color_code(update_color[i], live_benchmark);
        updata_color_code.push_back(color_code);
    }

    return updata_color_code;
}


vector<char> correct::benchmark(vector<char> c)
{
    char facelet_label[6] = { 'R', 'U', 'D', 'L', 'F', 'B' };
    char central_facelet[6] = { 4, 13, 22, 31, 40, 49};
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

    //生成基准面序列向量
    for (int j = 0; j < 6; j++)
	  live_facelet_label.push_back(live_label[j]);
    
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





