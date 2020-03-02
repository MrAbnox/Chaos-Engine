#include "Grid.h"
#include "TheShader.h"

//-------------------------------------------------------------------------------
//Constructor
//-------------------------------------------------------------------------------
Grid::Grid(GLuint size, GLfloat lineWidth, GLfloat r, GLfloat g, GLfloat b)
{
	//Set name
	m_name = "Grid";

	//----------------------------- Set grid to not textured;

	isTextured = 0;

	//----------------------------- Set grid to not Lit

	m_isLit = 0;

	//----------------------------- Set values to constructor overloaded variables

	m_size = size;
	m_lineWidth = lineWidth;
	m_totalVertices = 0;
	m_color = glm::vec3(r, g, b);

	//----------------------------- Declare VAOs and VBOs

	m_VAO = 0;
	VBO_color = 0;
	VBO_vertex = 0;

	m_axisVAO = 0;
	VBO_axisColor = 0;
	VBO_axisVertex = 0;

	m_shader = "Lightless";

	//----------------------------- Call create function

	Create();
}

//-------------------------------------------------------------------------------
//Destructor
//-------------------------------------------------------------------------------
Grid::~Grid()
{
	Destroy();
}

//-------------------------------------------------------------------------------
//Create Function
//-------------------------------------------------------------------------------
void Grid::Create()
{
	TheShader::Instance()->UseShader("Lightless");

	//----------------------------- Temp variables for offset create

	GLuint offset = 0;
	GLuint axisOffset = 0;

	//----------------------------- Temp const variables 

	const int SIZE = m_size;
	const int QUADRANTS = 4;
	const int BYTES_PER_LINE = 6 * sizeof(GLfloat);
	const int BYTES_PER_VERTEX = 3 * sizeof(GLfloat);

	const int TOTAL_BYTES_VBO = BYTES_PER_LINE * SIZE * QUADRANTS;
	const int TOTAL_BYTES_LINEVBO = BYTES_PER_LINE * SIZE + BYTES_PER_LINE * 3;

	//----------------------------- Get attribute ids from shader for linking buffers below

	GLint m_vertexAttributeID = TheShader::Instance()->GetAttributeID("Lightless_vertexIn");
	GLint m_colorAttributeID = TheShader::Instance()->GetAttributeID("Lightless_colorIn");

	//----------------------------- Generate VAO and VBOs

	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &VBO_vertex);
	glGenBuffers(1, &VBO_color);

	//----------------------------- Generate line VAO and VBOs

	glGenVertexArrays(1, &m_axisVAO);
	glGenBuffers(1, &VBO_axisVertex);
	glGenBuffers(1, &VBO_axisColor);

	//----------------------------- Bind vertex array and buffer info

	glBindVertexArray(m_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_vertex);
	glBufferData(GL_ARRAY_BUFFER, TOTAL_BYTES_VBO, NULL, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(m_vertexAttributeID, 3, GL_INT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(m_vertexAttributeID);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_color);
	glBufferData(GL_ARRAY_BUFFER, TOTAL_BYTES_VBO, NULL, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(m_colorAttributeID, 3, GL_INT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(m_colorAttributeID);

	glBindVertexArray(0);
	
	//----------------------------- Bind linesvertex array and buffer info

	glBindVertexArray(m_axisVAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_axisVertex);
	glBufferData(GL_ARRAY_BUFFER, TOTAL_BYTES_LINEVBO, NULL, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(m_vertexAttributeID, 3, GL_INT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(m_vertexAttributeID);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_axisColor);
	glBufferData(GL_ARRAY_BUFFER, TOTAL_BYTES_LINEVBO, NULL, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(m_colorAttributeID, 3, GL_INT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(m_colorAttributeID);

	glBindVertexArray(0);

	//----------------------------- Draw Quadrant one from the grid

	for (int i = 0; i < SIZE; i++)
	{

		GLint vertices[] = { -SIZE + i, 0,  SIZE,
							 -SIZE + i, 0, -SIZE};

		GLfloat color[] = { m_color.r, m_color.g, m_color.b,
							m_color.r, m_color.g, m_color.b};

		glBindBuffer(GL_ARRAY_BUFFER, VBO_vertex);
		glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(vertices), vertices);

		glBindBuffer(GL_ARRAY_BUFFER, VBO_color);
		glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(color), color);

		offset += BYTES_PER_LINE;

	}

	//----------------------------- Draw Quadrant two from the grid

	for (int i = 0; i < SIZE; i++)
	{

		GLint vertices[] = {  SIZE - i, 0, -SIZE,
							  SIZE - i, 0,  SIZE };

		GLfloat color[] = { m_color.r, m_color.g, m_color.b,
							m_color.r, m_color.g, m_color.b };

		glBindBuffer(GL_ARRAY_BUFFER, VBO_vertex);
		glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(vertices), vertices);

		glBindBuffer(GL_ARRAY_BUFFER, VBO_color);
		glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(color), color);
		
		offset += BYTES_PER_LINE;

	}

	//----------------------------- Draw Quadrant three from the grid

	for (int i = 0; i < SIZE; i++)
	{

		GLint vertices[] = {  -SIZE, 0,  SIZE - i,
							   SIZE, 0,  SIZE - i };

		GLfloat color[] = { m_color.r, m_color.g, m_color.b,
							m_color.r, m_color.g, m_color.b };

		glBindBuffer(GL_ARRAY_BUFFER, VBO_vertex);
		glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(vertices), vertices);

		glBindBuffer(GL_ARRAY_BUFFER, VBO_color);
		glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(color), color);

		offset += BYTES_PER_LINE;

	}

	//----------------------------- Draw Quadrant four from the grid

	for (int i = 0; i < SIZE; i++)
	{

		GLint vertices[] = {  SIZE, 0, -SIZE + i,
							 -SIZE, 0, -SIZE + i };

		GLfloat color[] = { m_color.r, m_color.g, m_color.b,
							m_color.r, m_color.g, m_color.b };

		glBindBuffer(GL_ARRAY_BUFFER, VBO_vertex);
		glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(vertices), vertices);

		glBindBuffer(GL_ARRAY_BUFFER, VBO_color);
		glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(color), color);

		offset += BYTES_PER_LINE;

	}

	//----------------------------- Draw Red x axis


	GLint vertices[] = { SIZE - 10 , 0, SIZE -20,
						 SIZE - 10, 0, SIZE  };

	GLfloat color[] = { 1.0f, 0.0f, 0.0f,
					    1.0f, 0.0f, 0.0f };


	glBindBuffer(GL_ARRAY_BUFFER, VBO_axisVertex);
	glBufferSubData(GL_ARRAY_BUFFER, axisOffset, sizeof(vertices), vertices);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_axisColor);
	glBufferSubData(GL_ARRAY_BUFFER, axisOffset, sizeof(color), color);;
	
	axisOffset += BYTES_PER_LINE;



	//----------------------------- Draw Green z axis


	GLint vertices2[] = {SIZE , 0, SIZE - 10,
						-SIZE, 0, -SIZE + 10};

	GLfloat color2[] = {0.0f, 1.0f, 0.0f,
						0.0f, 1.0f, 0.0f };

	glBindBuffer(GL_ARRAY_BUFFER, VBO_axisVertex);
	glBufferSubData(GL_ARRAY_BUFFER, axisOffset, sizeof(vertices2), vertices2);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_axisColor);
	glBufferSubData(GL_ARRAY_BUFFER, axisOffset, sizeof(color2), color2);
	axisOffset += BYTES_PER_LINE;


	//----------------------------- Draw blue y axis


	GLint vertices3[] = {0, -SIZE, 0,
						 0,  SIZE, 0 };

	GLfloat color3[] = { 0.0f, 0.0f, 1.0f,
						0.0f, 0.0f, 1.0f };

	glBindBuffer(GL_ARRAY_BUFFER, VBO_axisVertex);
	glBufferSubData(GL_ARRAY_BUFFER, axisOffset, sizeof(vertices3), vertices3);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_axisColor);
	glBufferSubData(GL_ARRAY_BUFFER, axisOffset, sizeof(color3), color3);
	axisOffset += BYTES_PER_LINE;



	//----------------------------- Calculate vertices

	m_totalAxisVertices = axisOffset / BYTES_PER_VERTEX;
	m_totalVertices = offset / BYTES_PER_VERTEX;

	//----------------------------- Send Uniform data

	TheShader::Instance()->SendUniformData("Lightless_isTextured", isTextured);
}

//-------------------------------------------------------------------------------
//Update Function
//-------------------------------------------------------------------------------
void Grid::Update()
{
}

//-------------------------------------------------------------------------------
//Draw Function
//-------------------------------------------------------------------------------
void Grid::Draw()
{
	//----------------------------- Set line width for grid

	glLineWidth(m_lineWidth);

	//----------------------------- Bind grid VAO and draw the grid lines

	glBindVertexArray(m_VAO);

	glDrawArrays(GL_LINES, 0, m_totalVertices);

	glBindVertexArray(0);

	//----------------------------- Set line width for axis

	glLineWidth(m_lineWidth + 5);

	//----------------------------- Bind axis VAO and draw the axis lines

	glBindVertexArray(m_axisVAO);

	glDrawArrays(GL_LINES, 0, m_totalAxisVertices);

	glBindVertexArray(0);
}

//-------------------------------------------------------------------------------
//Destroy function
//-------------------------------------------------------------------------------
void Grid::Destroy()
{
}
