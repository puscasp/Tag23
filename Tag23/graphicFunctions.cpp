#include <types.h>
#include <cmath>

line drawline(Vertex v1, Vertex v2)
{
if ((v2.x - v1.x) == 0)
	return { INFINITY, -INFINITY, abs(v2.y-v1.y)};
else
	return { (v2.y - v1.y) / (v2.x - v1.x),
	v1.y - ((v2.y - v1.y) / (v2.x - v1.x)*v2.x),
	sqrt((v2.x-v1.x)*(v2.x - v1.x) + (v2.y-v1.y)*(v2.y - v1.y))};
}

triangle makeTriangle(Vertex v1, Vertex v2, Vertex v3)
{
	return { v1,v2,v3, drawline(v1,v2),drawline(v2,v3),drawline(v3,v1) };
}

bool containsPoint(triangle t, Vertex v)
{
	line L1 = drawline(v, t.v1);
	line L2 = drawline(v, t.v2);
	line L3 = drawline(v, t.v3);

	float alpha = acos((L1.l * L1.l + L2.l * L2.l - t.L12.l * t.L12.l) / (2 * L1.l * L2.l));
	float beta = acos((L2.l * L2.l + L3.l * L3.l - t.L23.l * t.L23.l) / (2 * L2.l * L3.l));
	float gamma = acos((L3.l * L3.l + L1.l * L1.l - t.L31.l * t.L31.l) / (2 * L3.l * L1.l));

	return alpha < 180 && beta < 180 && gamma < 180;
}





void screen_onclick(screen s, int x, int y)
{
	for (int i = 0; i < s.elementList.size(); ++i)
	{
		if (s.elementList[i].onClick == NULL)
			continue;
		for (int j = 0; j < s.elementList[i].triList.size(); ++j)
		{
			if (containsPoint(s.elementList[i].triList[j], { (float)x, (float)y }))
				s.elementList[i].onClick;
		}
	}
}





//action (onclick) functions


void action_test()