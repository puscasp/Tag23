#include <graphicFunctions.h>


//Util
line drawline(Vertex v1, Vertex v2)
{
if ((v2.x - v1.x) == 0)
	return { INFINITY, -INFINITY, abs(v2.y-v1.y), &v1, &v2};
else
	return { (v2.y - v1.y) / (v2.x - v1.x),
	v1.y - ((v2.y - v1.y) / (v2.x - v1.x)*v2.x),
	sqrt((v2.x-v1.x)*(v2.x - v1.x) + (v2.y-v1.y)*(v2.y - v1.y)), &v1, &v2};
}

triangle makeTriangle(Vertex v1, Vertex v2, Vertex v3)
{
	return { v1,v2,v3 };
}

bool containsPoint(triangle t, Vertex v)
{
	line L1 = drawline(v, t.v1);
	line L2 = drawline(v, t.v2);
	line L3 = drawline(v, t.v3);
	line L12 = drawline(t.v1, t.v2);
	line L23 = drawline(t.v2, t.v3);
	line L31 = drawline(t.v3, t.v1);

	float alpha = acos((L1.l * L1.l + L2.l * L2.l - L12.l * L12.l) / (2 * L1.l * L2.l));
	float beta = acos((L2.l * L2.l + L3.l * L3.l - L23.l * L23.l) / (2 * L2.l * L3.l));
	float gamma = acos((L3.l * L3.l + L1.l * L1.l - L31.l * L31.l) / (2 * L3.l * L1.l));

	std::cout << alpha << " " << beta << " " << gamma << std::endl;
	return alpha < M_PI && beta < M_PI && gamma < M_PI;
}

bool linesIntersect(line l1, line l2)
{
	if (l1.m == l2.m)
		return false; //We will never need to check collinear line segments

	Vertex i = { (l2.b - l1.b) / (l1.m - l2.m), l1.m * (l2.b - l1.b) / (l1.m - l2.m) + l1.b };

	return !((i.x > l1.v1->x && i.x > l1.v2->x) || (i.x < l1.v1->x && i.x < l1.v2->x)
		|| (i.y > l1.v1->y && i.y > l1.v2->y) || (i.y < l1.v1->y && i.y < l1.v2->y)
		|| (i.x > l2.v1->x && i.x > l2.v2->x) || (i.x < l2.v1->x && i.x < l2.v2->x)
		|| (i.y > l2.v1->y && i.y > l2.v2->y) || (i.y < l2.v1->y && i.y < l2.v2->y));
}

Vertex normalizeCoords(Vertex v)
{
	return { (v.x*2)/WIDTH-1, (v.y*2)/HEIGHT-1};
}



//Screen
void screen_onclick(screen* s, int x, int y)
{
	for (int i = 0; i < s->elementList.size(); ++i)
	{
		if (s->elementList[i].onClick == NULL)
			continue;
		for (int j = 0; j < s->elementList[i].triList.size(); ++j)
		{
			if (containsPoint(s->elementList[i].triList[j], normalizeCoords({(float)x, (float)y})))
			{
				std::cout << j <<  "  " << normalizeCoords({ (float)x, (float)y }).x << "  " << normalizeCoords({ (float)x, (float)y }).y << std::endl;
				s->elementList[i].onClick(s->elementList[i].onClickInput, s->elementList[i].onClickOutput);
				return;
			}
		}
	}
}

void updateScreenDrawTable(screen* s, bool wipe)
{
	if (wipe)
	{
		s->vertexIndexTable.clear();
		s->indices.clear();
		s->v.clear();
	}
	int highestIndex = 0;
	for (int i = 0; i < s->elementList.size(); ++i)
	{
		for (int j = 0; j < s->elementList[i].triList.size(); ++j)
		{
			//foreach of the 3 verts in a triangle:
			// if not in table (new vert): add to table, add to list, add to index
			// if in table (old vert): get index, add to index list
			
			//std::cout << "Triangle " << j << ", v1: " << s->elementList[i].triList[j].v1.x << " " <<  s->elementList[i].triList[j].v1.y << std::endl;
			if (s->vertexIndexTable.find(s->elementList[i].triList[j].v1) != s->vertexIndexTable.end())
				s->indices.push_back(s->vertexIndexTable[s->elementList[i].triList[j].v1]);
			else
			{
				//std::cout << "v1(" << s->elementList[i].triList[j].v1.x << " " << s->elementList[i].triList[j].v1.y << ") written to index " << highestIndex << std::endl;
				s->vertexIndexTable.emplace(s->elementList[i].triList[j].v1, highestIndex);
				++highestIndex;
				s->v.push_back(s->elementList[i].triList[j].v1);
				s->indices.push_back(s->vertexIndexTable[s->elementList[i].triList[j].v1]);
			}



			//std::cout << "Triangle " << j << ", v2: " << s->elementList[i].triList[j].v2.x << " " << s->elementList[i].triList[j].v2.y << std::endl;
			if (s->vertexIndexTable.find(s->elementList[i].triList[j].v2) != s->vertexIndexTable.end())
				s->indices.push_back(s->vertexIndexTable[s->elementList[i].triList[j].v2]);
			else
			{

				//std::cout << "v2(" << s->elementList[i].triList[j].v2.x << " " << s->elementList[i].triList[j].v2.y << ") written to index " << highestIndex << std::endl;
				s->vertexIndexTable.emplace(s->elementList[i].triList[j].v2, highestIndex);
				++highestIndex;
				s->v.push_back(s->elementList[i].triList[j].v2);
				s->indices.push_back(s->vertexIndexTable[s->elementList[i].triList[j].v2]);
			}



			//std::cout << "Triangle " << j << ", v3: " << s->elementList[i].triList[j].v3.x << " " << s->elementList[i].triList[j].v3.y << std::endl;
			if (s->vertexIndexTable.find(s->elementList[i].triList[j].v3) != s->vertexIndexTable.end())
				s->indices.push_back(s->vertexIndexTable[s->elementList[i].triList[j].v3]);
			else
			{

				//std::cout << "v3(" << s->elementList[i].triList[j].v3.x << " " << s->elementList[i].triList[j].v3.y << ") written to index " << highestIndex << std::endl;
				s->vertexIndexTable.emplace(s->elementList[i].triList[j].v3, highestIndex);
				++highestIndex;
				s->v.push_back(s->elementList[i].triList[j].v3);
				s->indices.push_back(s->vertexIndexTable[s->elementList[i].triList[j].v3]);
			}

		}
	}
}

void buildScreenBuffers(screen* s)
{
	glGenVertexArrays(1, &s->VAO);
	glGenBuffers(1, &s->VBO);
	glGenBuffers(1, &s->EBO);

	glBindVertexArray(s->VAO);


	glBindBuffer(GL_ARRAY_BUFFER, s->VBO);
	glBufferData(GL_ARRAY_BUFFER, s->v.size() * sizeof(Vertex), &s->v[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, s->indices.size() * sizeof(unsigned int), &s->indices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//what kind of magic
	glBindBuffer(GL_ARRAY_BUFFER, 0); //unbindes vbo (for what purpose?)
	glBindVertexArray(0); //unbindes vao (again, why?), and why not ebo?

	std::cout << "f: " << s->indices.size() << std::endl;

}


//UiElements
uiElement generateUiElement(Vertex verts[], int nverts, unsigned int* s, ocfunc ocptr, voidArray in, voidArray out)
{
	// Some Notes on creation: verts are considered the sequential vertices of a CONCAVE shape
	// All onclick pointers must have an input and output pointer as arguments, and return nothing
	uiElement elem = {};
	elem.onClick = ocptr;
	elem.onClickInput = in;
	elem.onClickOutput = out;
	elem.shader = s;

	float maxx = -INFINITY, minx = INFINITY, maxy = -INFINITY, miny = INFINITY;
	for (int i = 0; i < nverts; ++i)
	{
		std::cout << verts[i].x << "  " << verts[i].y << std::endl;
		if (verts[i].x > maxx)
			maxx = verts[i].x;
		else if (verts[i].x < minx)
			minx = verts[i].x;

		if (verts[i].y > maxy)
			maxy = verts[i].y;
		else if (verts[i].y < miny)
			miny = verts[i].y;
	}
	Vertex mid = { (maxx + minx) / 2, (maxy + miny) / 2 };

	//Foreach adjacent pair of verts, draw triangle between them + mid.
	//Because all verts assumed to be concave, this will automatically fill it in in O(n) time and 3n space for n verts
	for (int i = 0; i < nverts; ++i) {
		elem.triList.push_back({ verts[i], verts[(i+1) % nverts], mid });
	}
	return elem;
}

//Shaders
unsigned int generateShader(const char* vPath, const char* fPath, void* vArgs, void* fArgs)
{
	unsigned int ID;

	//Read Shader source
	std::string vCode;
	std::string fCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		//open file
		vShaderFile.open(vPath);
		fShaderFile.open(fPath);
		std::stringstream vShaderStream, fShaderStream;
		//read file into stream
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		vShaderFile.close();
		fShaderFile.close();
		//convert string to stream
		vCode = vShaderStream.str();
		fCode = fShaderStream.str();

	}
	catch (std::ifstream::failure e) {
		std::cout << "SHADER FILE READ ERROR" << std::endl;
	}

	//Convert to null-terminator version
	const char* vShaderCode = vCode.c_str();
	const char* fShaderCode = fCode.c_str();

	unsigned int vertex, fragment;
	int success;
	char log[512];

	//Vertex shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertex, 512, NULL, log);
		std::cout << "VERTEX SHADER COMPILE ERROR\n" << log << std::endl;
	}

	//Fragment shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragment, 512, NULL, log);
		std::cout << "FRAGMENT SHADER COMPILE ERROR\n" << log << std::endl;
	}

	//Shader Linking, Cleanup, and Return
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);

	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(ID, 512, NULL, log);
		std::cout << "SHADER LINKING ERROR\n" << log << std::endl;
	}
	glDeleteShader(vertex);
	glDeleteShader(fragment);
	return ID;

}

void activateShaders(screen* s) 
{
	for (int i = 0; i < s->elementList.size(); ++i)
	{
		std::cout << "activateshaderssize: " << s->elementList[i].shader << std::endl;
		glUseProgram((GLuint)s->elementList[i].shader);
	}
}