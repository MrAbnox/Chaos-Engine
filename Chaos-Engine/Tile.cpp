#include "Tile.h"
#include "TheShader.h"

//-------------------------------------------------------------------------------
//Constructor
//-------------------------------------------------------------------------------
Tile::Tile(GLfloat width, GLfloat height, GLuint spriteSheetCol, GLuint spriteSheetRow)
{
	m_spriteSheetRow = spriteSheetRow;
	halfDimension.x = width;
	halfDimension.y = height;
	m_color = glm::vec4(1.0f);
	m_shader = "Lightless";
}

//-------------------------------------------------------------------------------
//Destructor
//-------------------------------------------------------------------------------
Tile::~Tile()
{
}

//-------------------------------------------------------------------------------
//Create Function
//-------------------------------------------------------------------------------
void Tile::Create()
{

	ID_color = TheShader::Instance()->GetAttributeID("Lightless_colorIn");
	ID_vertex = TheShader::Instance()->GetAttributeID("Lightless_vertexIn");
	ID_texture = TheShader::Instance()->GetAttributeID("Lightless_textureIn");

	int count = 0;
	glm::vec2 celDimension(1.0f / m_spriteSheetCol, 1.0f / m_spriteSheetRow);
	glm::vec2 UVOrigin(m_spriteSheetCol * celDimension.x, m_spriteSheetRow * celDimension.y);
			m_buffer->GenerateVertexArrays(1, &m_VAO);
			glGenBuffers(1, &m_vertexVBO);
			glGenBuffers(1, &m_colorVBO);
			glGenBuffers(1, &m_textureVBO);
			glGenBuffers(1, &m_EBO);

			glBindVertexArray(m_VAO);
	for (GLuint row = 0; row < m_spriteSheetRow; row++)
	{
		for(GLuint col = 0; col < m_spriteSheetCol; col++)
		{
			count++;
			GLfloat
				vertices[] = 
			{
				0, 1, 0,
				1, 1, 0,
				1, 0, 0,
				0, 0, 0
			};

			glBindBuffer(GL_ARRAY_BUFFER, m_vertexVBO);
			glBufferSubData(GL_ARRAY_BUFFER, offSetVert, sizeof(vertices), vertices);
			glVertexAttribPointer(ID_vertex, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(ID_vertex);

			offsetVert += BYTES_PER_TILE_VERTEX;

			GLfloat colors[]
			{
				m_color.r, m_color.g, m_color.b, m_color.a,
				m_color.r, m_color.g, m_color.b, m_color.a,
				m_color.r, m_color.g, m_color.b, m_color.a,
				m_color.r, m_color.g, m_color.b, m_color.a
			};

			glBindBuffer(GL_ARRAY_BUFFER, m_colorVBO);
			glBufferSubData(GL_ARRAY_BUFFER, offSetColor, sizeof(colors), colors);
			glVertexAttribPointer(ID_color, 4, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(ID_color);

			offsetColor += BYTES_PER_TILE_COLOR;

			GLfloat UVs[] = 
			{
				0.0f, 0.0f,
				1.0f, 0.0f,
				1.0f, 1.0f,
				0.0f, 1.0f
			};

			glBindBuffer(GL_ARRAY_BUFFER, m_textureVBO);
			glBufferSubData(GL_ARRAY_BUFFER, offsetUV, sizeof(UVs), UVs);
			glVertexAttribPointer(ID_texture, 2, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(ID_texture);

			offsetUV += BYTES_PER_TILE_UV;

			GLuint indices[] = {0,1,3,
								3,1,2};
		
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
			glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offsetIndex, sizeof(indices), indices);

			offsetIndex += BYTES_PER_TILE_INDEX;
		}
	}
			glBindVertexArray(0);
}

//-------------------------------------------------------------------------------
//Draw
//-------------------------------------------------------------------------------
void Tile::Draw()
{
	glm::mat4 model = glm::mat4(1.0f);

	TheShader::Instance()->SendUniformData("Lightless_model", 1, GL_FALSE, model);

	glActiveTexture(0);
	m_texture.Bind();
	//SendModelInformation(m_shader);
	glBindVertexArray(m_VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void*)( m_tileIndex * BYTES_PER_TILE_INDEX));
	glBindVertexArray(0);
}

//-------------------------------------------------------------------------------
//Set Tile
//-------------------------------------------------------------------------------
void Tile::SetTile(GLuint column, GLuint row)
{
	m_tileIndex = ((row - 1) * m_spriteSheetCol + column);

	//zero based decrement
	m_tileIndex--;
}

void Tile::LoadTexture(std::string filepath, std::string textureID)
{
	m_texture.Load(filepath, textureID);
}
