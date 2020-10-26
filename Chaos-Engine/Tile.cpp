#include "Tile.h"
#include "TheShader.h"

//-------------------------------------------------------------------------------
//Constructor
//-------------------------------------------------------------------------------
Tile::Tile(GLfloat width, GLfloat height, GLuint spriteSheetColRef, GLuint spriteSheetRowRef)
{
	spriteSheetRow = spriteSheetRowRef;
	spriteSheetCol = spriteSheetColRef;
	halfDimension.x = width;
	halfDimension.y = height;
	color = glm::vec4(1.0f);
	shader = "Lightless";
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
	glm::vec2 celDimension(1.0f / spriteSheetCol, 1.0f / spriteSheetRow);
	glm::vec2 UVOrigin(spriteSheetCol * celDimension.x, spriteSheetRow * celDimension.y);
	buffer->GenerateVertexArrays(1, &VAO);

	glGenBuffers(1, &vertexVBO);
	glGenBuffers(1, &colorVBO);
	glGenBuffers(1, &textureVBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	for (GLuint row = 0; row < spriteSheetRow; row++)
	{
		for(GLuint col = 0; col < spriteSheetCol; col++)
		{
			count++;
			GLfloat
				vertices[] = 
			{
				-halfDimension.x, halfDimension.y, 0.0f,
				 halfDimension.x,  halfDimension.y, 0.0f,
				 halfDimension.x, -halfDimension.y, 0.0f,
				-halfDimension.x, -halfDimension.y, 0.0f
			};

			glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
			glBufferSubData(GL_ARRAY_BUFFER, offSetVert, sizeof(vertices), vertices);
			glVertexAttribPointer(ID_vertex, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(ID_vertex);

			offsetVert += BYTES_PER_TILE_VERTEX;

			GLfloat colors[]
			{
				color.r, color.g, color.b, color.a,
				color.r, color.g, color.b, color.a,
				color.r, color.g, color.b, color.a,
				color.r, color.g, color.b, color.a
			};

			glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
			glBufferSubData(GL_ARRAY_BUFFER, offSetColor, sizeof(colors), colors);
			glVertexAttribPointer(ID_color, 4, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(ID_color);

			offsetColor += BYTES_PER_TILE_COLOR;

			GLfloat UVs[] = 
			{
				UVOrigin.s, UVOrigin.t,
				UVOrigin.s + celDimension.x, UVOrigin.t,
				UVOrigin.s + celDimension.x, UVOrigin.t + celDimension.y,
				UVOrigin.s, UVOrigin.t + celDimension.y
			};

			glBindBuffer(GL_ARRAY_BUFFER, textureVBO);
			glBufferSubData(GL_ARRAY_BUFFER, offsetUV, sizeof(UVs), UVs);
			glVertexAttribPointer(ID_texture, 2, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(ID_texture);

			offsetUV += BYTES_PER_TILE_UV;

			GLuint indices[] = {0 + (count * 4),1 + (count * 4), 3 + (count * 4),
								3 + (count * 4),1 + (count * 4), 2 + (count * 4) };
		
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
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
	TheShader::Instance()->SendUniformData("Lightless_model", 1, GL_FALSE, transform->GetLocalToWorldCoords());

	glActiveTexture(0);
	texture.Bind();
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void*)( tileIndex * BYTES_PER_TILE_INDEX));
	glBindVertexArray(0);
}

//-------------------------------------------------------------------------------
//Set Tile
//-------------------------------------------------------------------------------
void Tile::SetTile(GLuint column, GLuint row)
{
	tileIndex = ((row - 1) * spriteSheetCol + column);

	//zero based decrement
	tileIndex--;
}

//-------------------------------------------------------------------------------
//Load Texture
//-------------------------------------------------------------------------------
void Tile::LoadTexture(std::string filepath, std::string textureID)
{
	texture.Load(filepath, textureID);
}
