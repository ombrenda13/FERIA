/*---------------------------------------------------------*/
/* ----------------   Proyecto feria --------------------------*/
/*-----------------    2019-2   ---------------------------*/
/*------------- Alumno: Diaz Acosta Erika y Ortiz Martínez Brenda -----------------*/

/*-------------  Grupo4 -------------- */
/*---------------------Version visual 2017------------------------*/
/*---------Instrucciones-------------------------------------------*/
/*--------Use las teclas para mover el modelo----------------------*/
/*--------W acercar   S  alejar------------------------------------*/
/*--------Z Bajar   E  subir------------------------------------*/
/*--------A izquierda   D derecha------------------------------------*/
/*----------mouse: mover, scroll = acercar---------------*/
//#define STB_IMAGE_IMPLEMENTATION
#include <glew.h>
#include <glfw3.h>
#include <stb_image.h>
#include "esfera.h"
#include "camera.h"
#include <stb_image.h>
#include "Model.h"


Esfera my_sphere(1.0f);

void resize(GLFWwindow* window, int width, int height);
void my_input(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

// settings
// Window size
int SCR_WIDTH = 3800;
int SCR_HEIGHT = 7600;

GLFWmonitor* monitors;
GLuint VBO, VAO, EBO;

//Camera
Camera camera(glm::vec3(0.0f, 0.0f, 0.0f));
double	lastX = 0.0f,
lastY = 0.0f;
bool firstMouse = true;

//Timing
double	deltaTime = 0.0f,
lastFrame = 0.0f;

//Lighting
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

void myData(void);
void display(Model, Model, Model,Model);
void getResolution(void);
void animate(void);
void circulos(void);
//For Keyboard
float	movX = 0.0f,
movY = 0.0f,
movZ = -5.0f,
rotX = 0.0f,
rotZ = 0.0f,
rotY = 0.0f;

//rueda
float angRueda = 0.0f, angCanasta = 0.0f;
float movimiento = 0.0, colgando = 0.0;

//for model carrito 
//5.0f, 30.10f, -125.0f
float movKit_z = -112.0f,
movKit_x = 5.0f,
movKit_y = 28.0f,
rotKit_y = -90.0f;

int estado = 0;
bool play, play2;

//Texture
unsigned int texture1, texture2, texture3, texture4, texture5, texture6, texture7; //Indice que va a tener cada textura, i.e., 2 índices = 2 texturas
unsigned int texture8, texture9, texture10, texture11, texture12, texture13, texture14, texture15, texture16, texture17;
unsigned int texture18, texture19, texture20;

void getResolution()
{
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	SCR_WIDTH = mode->width;
	SCR_HEIGHT = (mode->height) - 80;

	lastX = SCR_WIDTH / 2.0f;
	lastY = SCR_HEIGHT / 2.0f;

}


void myData() //Recordemos que antes aquí teníamos un cubo, pero ahora hay un plano.
{
	float vertices[] = {
		// positions          // texture coords
												//front
		0.5f, 0.5f, 0.5f,		1.0f, 1.0f,
		0.5f, -0.5f, 0.5f,		1.0f, 0.0f,
		-0.5f, -0.5f, 0.5f,		0.0f, 0.0f,
		-0.5f, 0.5f, 0.5f,		0.0f, 1.0f,

		// Trasera
0.5f, -0.5f, -0.5f,	1.0f, 1.0f,
0.5f,  0.5f, -0.5f,	1.0f, 0.0f,
-0.5f,  0.5f, -0.5f,	0.0f, 0.0f,
-0.5f, -0.5f, -0.5f,	0.0f, 1.0f,

//Izq
-0.5f,  0.5f, 0.5f,		1.0f, 1.0f,
-0.5f,  0.5f, -0.5f,	0.0f, 1.0f,
-0.5f, -0.5f, -0.5f,	0.0f, 0.0f,
-0.5f, -0.5f, 0.5f,		1.0f, 0.0f,

//Der
0.5f,  0.5f, 0.5f,		0.0f, 1.0f,
0.5f,  0.5f, -0.5f,		1.0f, 1.0f,
0.5f, -0.5f, -0.5f,		1.0f, 0.0f,
0.5f, -0.5f, 0.5f,		0.0f, 0.0f,

//Sup
-0.5f, 0.5f, 0.5f,		2.0f, 2.0f,
 0.5f, 0.5f, 0.5f,		2.0f, 0.0f,
 0.5f, 0.5f, -0.5f,		0.0f, 0.0f,
-0.5f, 0.5f, -0.5f,		0.0f, 2.0f,

//Inf
-0.5f, -0.5f, 0.5f,		1.0f, 1.0f,
-0.5f, -0.5f, -0.5f,	1.0f, 0.0f,
 0.5f, -0.5f, -0.5f,	0.0f, 0.0f,
 0.5f, -0.5f, 0.5f,		0.0f, 1.0f,

 -0.5f, -0.5f, 0.5f,	0.0f, 0.0f,
-0.5f, 0.0f, 0.5f,		0.0f, 1.0f,
0.7f, -0.3f, 0.5f,      1.0f, 0.0f,

 -0.3f, 0.0f, 0.5f,		0.0f, 0.0f,
 0.3f, 0.0f, 0.5f,		1.0f, 0.0f,
 0.0f, 0.8f, 0.5f,		0.50f, 1.0f


	};
	unsigned int indices[] = {

		0, 1, 3, // primer triangulo
		1, 2, 3,  // segundo

		6, 7, 5,
		7, 4, 5,

		8, 9, 10,
		8, 10, 11,

		12, 13, 14,
		12, 14, 15,

		16, 17, 18,
		16, 18, 19,

		20, 21, 22,
		20, 22, 23,

		24,25,26,
		27,28,29

		/*		24,25,26,
				24,26,27,
				28,29,30,
				28,30,31,
				31,32,33,
				31,33,34,
				35,36,37,
				35,37,38,
				39,40,41,
				39,41,42,
				43,44,45,
				43,45,46*/



	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0); //El atributo 0 corresponde a la posicion
	glEnableVertexAttribArray(0);
	// texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float))); //El atributo 1 corresponde a la textura
	glEnableVertexAttribArray(1);
	//---------------hereee textura2
	//glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(2);

	// load and create a texture 
	// -------------------------

	// texture 1
	// ---------
	glGenTextures(1, &texture1); //Leemos una textura 
	glBindTexture(GL_TEXTURE_2D, texture1); //tipo 2D 
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //filtro 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
	unsigned char* data = stbi_load("texturas_feria/piedras.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture one" << std::endl;
	}
	stbi_image_free(data);
	// texture 2
	// ---------
	glGenTextures(2, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2); //tipo 2D 
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //filtro 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	data = stbi_load("texturas_feria/marmol.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture two" << std::endl;
	}
	stbi_image_free(data);
	// texture 3
	// ---------
	glGenTextures(3, &texture3);
	glBindTexture(GL_TEXTURE_2D, texture3); //tipo 2D 
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //filtro 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	data = stbi_load("texturas_feria/estrellas1.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture three" << std::endl;
	}
	stbi_image_free(data);

	// texture 4 banderas
	// ---------
	glGenTextures(4, &texture4);
	glBindTexture(GL_TEXTURE_2D, texture4); //tipo 2D 
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //filtro 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	data = stbi_load("texturas_feria/red_flag.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture three" << std::endl;
	}
	stbi_image_free(data);


	// texture 5 
	glGenTextures(5, &texture5);
	glBindTexture(GL_TEXTURE_2D, texture5); //tipo 2D 
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //filtro 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	data = stbi_load("texturas_feria/galaxia3.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture three" << std::endl;
	}
	stbi_image_free(data);

	// texture 6`puertas
	glGenTextures(6, &texture6);
	glBindTexture(GL_TEXTURE_2D, texture6); //tipo 2D 
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //filtro 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	data = stbi_load("texturas_feria/cubos.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture three" << std::endl;
	}

	stbi_image_free(data);



	// texture 7
	glGenTextures(7, &texture7);
	glBindTexture(GL_TEXTURE_2D, texture7); //tipo 2D 
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //filtro 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	data = stbi_load("texturas_feria/marciano2.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture three" << std::endl;
	}
	stbi_image_free(data);


	// texture 8
	glGenTextures(8, &texture8);
	glBindTexture(GL_TEXTURE_2D, texture8); //tipo 2D 
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //filtro 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	data = stbi_load("texturas_feria/morado2.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture three" << std::endl;
	}
	stbi_image_free(data);



	// texture 9
	glGenTextures(9, &texture9);
	glBindTexture(GL_TEXTURE_2D, texture9); //tipo 2D 
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //filtro 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	data = stbi_load("texturas_feria/blue.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture three" << std::endl;
	}
	stbi_image_free(data);


	// texture 10
	glGenTextures(10, &texture10);
	glBindTexture(GL_TEXTURE_2D, texture10); //tipo 2D 
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //filtro 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	data = stbi_load("texturas_feria/verde.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture three" << std::endl;
	}
	stbi_image_free(data);
	//TEXTURA 11
	glGenTextures(11, &texture11);
	glBindTexture(GL_TEXTURE_2D, texture11); //tipo 2D 
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //filtro 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	data = stbi_load("texturas_feria/letrero.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture two" << std::endl;
	}
	stbi_image_free(data);


	//TEXTURA 12
	glGenTextures(12, &texture12);
	glBindTexture(GL_TEXTURE_2D, texture12); //tipo 2D 
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //filtro 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	data = stbi_load("texturas_feria/lego.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture three" << std::endl;
	}
	stbi_image_free(data);



	glGenTextures(13, &texture13);
	glBindTexture(GL_TEXTURE_2D, texture13); //tipo 2D 
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //filtro 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	data = stbi_load("texturas_feria/legoverde.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture three" << std::endl;
	}
	stbi_image_free(data);

	// texture 14
		// ---------
	glGenTextures(14, &texture14);
	glBindTexture(GL_TEXTURE_2D, texture14); //tipo 2D 
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //filtro 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	data = stbi_load("texturas_feria/lego.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture two" << std::endl;
	}
	stbi_image_free(data);




	// texture 15
		// ---------
	glGenTextures(15, &texture15);
	glBindTexture(GL_TEXTURE_2D, texture14); //tipo 2D 
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //filtro 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	data = stbi_load("texturas_feria/nubes1000.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture two" << std::endl;
	}
	stbi_image_free(data);




}



void circulos(void) {

	glPointSize(0.1);
	float x = 0.0f, y = 0.0f, z = 0.27f;
	glPointSize(15);
	for (double i = 0; i <= 360;) {
		glBegin(GL_POINTS); {
			x = 1 * cos(i);
			y = 1 * sin(i);

			glVertex3f(x, y, z);
			i = i + 0.05;
			x = 1 * cos(i);
			y = 1 * sin(i);

			glVertex3f(x, y, z);
			glVertex3f(0, 0, 0);
		}
		i = i + 0.05;
	}
	glEnd();
}

void circulos2(void) {

	glPointSize(15);
	float x = 0.0f, y = 0.0f, z = -0.25f;

	for (double i = 0; i <= 360;) {
		glBegin(GL_POINTS); {
			x = 1 * cos(i);
			y = 1 * sin(i);

			glVertex3f(x, y, z);
			i = i + 0.05;
			x = 1 * cos(i);
			y = 1 * sin(i);

			glVertex3f(x, y, z);
			glVertex3f(0, 0, 0);
		}
		i = i + 0.05;
	}
	glEnd();
}


void animate(void)
{

	glm::mat4 view = glm::mat4(1.0f);
	movimiento = 0.05;
	colgando = -0.05;
	angRueda = angRueda + movimiento;
	angCanasta = angCanasta + colgando;
	if (angRueda >= 90)
	{
		movimiento = -0.1;
		if (angCanasta <= -80)
		{
			colgando = 0.20;
		}
	}
	if (angRueda <= -90)
	{
		movimiento = 0.1;
		if (angCanasta >= 80)
		{
			colgando = -0.20;
		}
	}


	/////PARA EL CARRITO EN LA MONTAÑA RUSA//////////

	if (play) {

		if (estado == 0) { //ESTADO A
		


			if (movKit_x > -9.0) {//
				movKit_x -= 1.0f;
				//printf("%f \n", movKit_z);

			}
			else {

				estado = 1;
				
			}
		}

		if (estado == 1) { //ESTADO b

			if (movKit_x > -18) {//SIGO EN EL ESTADO B    
				movKit_x -= 1.0f;
				movKit_y -= 0.07f;
				//printf("%f \n", movKit_x);
			}
			else {
				estado = 2;
			}
		}

		if (estado == 2) { //ESTADO b

			if (movKit_x > -45) {//SIGO EN EL ESTADO B    
				movKit_x -= 0.8;
				movKit_y -= 0.32f;
				//printf("%f \n", movKit_x);
			}
			else {
				estado = 3;
			}
		}
		if (estado == 3) { //ESTADO b

			if (movKit_x > -60) {//SIGO EN EL ESTADO B    
				movKit_x -= 0.9f;
				movKit_y += 0.09f;
				//printf("%f \n", movKit_x);
			}
			else {
				estado = 4;

			}
		}
		
		if (estado == 4) { //ESTADO b

			if (movKit_x > -75) {//SIGO EN EL ESTADO B    
				movKit_x -= 1.0f;
				movKit_z -= 0.2f;
				movKit_y += 0.6f;
				//printf("%f \n", movKit_x);
			}
			else {
				
				rotKit_y = 210.0f;
				estado = 5;
			}
		}

		if (estado == 5) { //ESTADO b

			if (movKit_x > -85) {//SIGO EN EL ESTADO B    
				movKit_x -= 0.5f;
				movKit_z -= 0.08f;
				movKit_y += 0.08f;
				//printf("%f \n", movKit_x);
			}
			else {

				rotKit_y = 180.0f;
				estado = 6;
			}
		}

		if (estado == 6) { //ESTADO b

			if (movKit_z > -145) {//SIGO EN EL ESTADO B    
				movKit_z -= 1.5;
				//printf("%f \n", movKit_x);
			}
			else {
				
				rotKit_y = 130.0f;
				estado = 7;
			}
		}

		if (estado == 7) { //ESTADO b

			if (movKit_x <-80) {//SIGO EN EL ESTADO B    
				movKit_x += 1.0f;
				movKit_z -= 0.2f;
				movKit_y += 0.2;
				//printf("%f \n", movKit_x);
			}
			else {

				rotKit_y = 90.0f;
				estado = 8;
			}
		}
		if (estado == 8) { //ESTADO b

			if (movKit_x < -60) {//SIGO EN EL ESTADO B    
				movKit_x += 1.0f;
			
				movKit_y -= 0.1f;
			}
			else {
				
				rotKit_y = 90.0f;
				estado = 9;
			}
		}
		

		if (estado == 9) { //ESTADO b

			if (movKit_x < -40) {//SIGO EN EL ESTADO B    
				movKit_x += 1.0f;

				movKit_y += 0.5f;
			}
			else {

				rotKit_y = 90.0f;
				estado = 10;
			}
		}


		if (estado == 10) { //ESTADO b

			if (movKit_x < -24) {//SIGO EN EL ESTADO B    
				movKit_x += 1.0f;

				movKit_y += 0.01f;
			}
			else {

				rotKit_y = 90.0f;
				estado = 11;
			}
		}

		if (estado == 11) { //ESTADO b

			if (movKit_x < -18) {//SIGO EN EL ESTADO B    
				movKit_x += 1.0f;

				movKit_y += 0.35f;
			}
			else {

				rotKit_y = 90.0f;
				estado = 12;
			}
		}

		if (estado == 12) { //ESTADO b

			if (movKit_x < -16) {//SIGO EN EL ESTADO B    
				movKit_x += 1.0f;

				movKit_y += 1.3f;
			}
			else {

				rotKit_y = 90.0f;
				estado = 13;

			}
		}

		if (estado == 13) { //ESTADO b

			if (movKit_x < -11) {//SIGO EN EL ESTADO B    
				movKit_x += 2.0f;

				movKit_y += 2.3f;
			}
			else {

				rotKit_y = 90.0f;
				estado = 14;
			}
		}

		if (estado == 14) { //ESTADO b

			if (movKit_x < -8) {//SIGO EN EL ESTADO B    
				movKit_x += 1.0f;

				movKit_y += 0.5f;
			}
			else {

				rotKit_y = 90.0f;
				estado = 15;
			}
		}
		if (estado == 15) { //ESTADO b

			if (movKit_x < 0.0) {//SIGO EN EL ESTADO B    
				movKit_x += 2.0f;

				movKit_y += 0.1f;
			}
			else {

				rotKit_y = 90.0f;
				estado = 16;
			}
		}
		if (estado == 16) { //ESTADO b

			if (movKit_x < 10.0) {//SIGO EN EL ESTADO B    
				movKit_x += 1.0f;

				movKit_y += 0.0f;
			}
			else {

				rotKit_y = 90.0f;
				estado = 17;
			}
		}

		if (estado == 17) { //ESTADO b

			if (movKit_x < 40.0) {//SIGO EN EL ESTADO B    
				movKit_x += 0.7f;

				movKit_y += -0.29f;
			}
			else {

				rotKit_y = 90.0f;
				estado = 18;
			}
		}
		if (estado == 18) { //ESTADO b

			if (movKit_x < 72.0) {//SIGO EN EL ESTADO B    
				movKit_x += 0.4f;

		
			}
			else {

				rotKit_y = 90.0f;
				estado = 19;
			}
		}
		if (estado == 19) { //ESTADO b

			if (movKit_x < 85.0) {//SIGO EN EL ESTADO B    
				movKit_x += 1.5f;
				movKit_y -= 2.0;

			}
			else {

				rotKit_y = 90.0f;
				estado = 20;
			}
		}
		if (estado == 20) { //ESTADO b

			if (movKit_x < 92.0) {//SIGO EN EL ESTADO B    
				movKit_x += 1.5f;
				//movKit_y -= 2.0;

			}
			else {

				rotKit_y = 90.0f;
				estado = 21;
			}
		}
		if (estado == 21) { //ESTADO b
			view = glm::rotate(view, glm::radians(-25.0f), glm::vec3(0.0f, 0.0f, 1.0f));
			view = glm::rotate(view, glm::radians(-25.0f), glm::vec3(1.0f, 0.0f, 0.0f));

			if (movKit_x < 94.0) {//SIGO EN EL ESTADO B    
				movKit_x += 0.8f;
				movKit_y -= 0.1;

			}
			else {

				rotKit_y = 90.0f;
				estado = 22;
			}
		}
		if (estado == 22) { //ESTADO b

			if (movKit_x < 110.0) {//SIGO EN EL ESTADO B    
				movKit_x += 0.8f;
				movKit_y -= 0.085;

			}
			else {

				rotKit_y = 10.0f;
				estado = 23;
			}
		}
		if (estado == 23) { //ESTADO b

			if (movKit_z < -124.0f) {//SIGO EN EL ESTADO B    
				movKit_y -= 0.3;
				movKit_z += 1.00f;

				printf("%f \n", movKit_z);
			}
			else {

				rotKit_y = 270.0f;
				estado = 24;
			}
		}


		if (estado == 24) { //ESTADO b

			if (movKit_x > 102.0f) {//SIGO EN EL ESTADO B    
				movKit_x -= 1.0f;
				movKit_z += 1.0f;

				printf("%f \n", movKit_z);
			}
			else {

				rotKit_y = 270.0f;
				estado = 25;
			}
		}


		if (estado == 25) { //ESTADO b

			if (movKit_x > 87.0f) {//SIGO EN EL ESTADO B    
				movKit_x -= 1.0f;
				

				printf("%f \n", movKit_z);
			}
			else {

				
				estado = 26;
			}
		}


		if (estado == 26) { //ESTADO b

			if (movKit_x > 57.0f) {//SIGO EN EL ESTADO B    
				movKit_x -= 1.0f;
				movKit_y += 0.55f;

			}
			else {


				estado = 27;
			}
		}

		if (estado == 27) { //ESTADO b

			if (movKit_x > 0.0f) {//SIGO EN EL ESTADO B    
				movKit_x -= 1.0f;
				

			}
			else {
				estado = 0;

			}
		}



	}









}

void display(Model Tree, Model FoodCart, Model Soldado1,Model Carrito)
{
	// bind textures on corresponding texture units
	glActiveTexture(GL_TEXTURE);			//activar la textura a 0. 
	glBindTexture(GL_TEXTURE_2D, texture1);

	//Shader projectionShader("shaders/shader_light.vs", "shaders/shader_light.fs");
	Shader projectionShader("shaders/shader_texture.vs", "shaders/shader_texture.fs");
	Shader lampShader("shaders/shader_lamp.vs", "shaders/shader_lamp.fs");
	Shader modelShader("Shaders/modelLoading.vs", "Shaders/modelLoading.fs");
	//To Use Lighting
	projectionShader.use();
	projectionShader.setInt("texture1", 0);


	// create transformations and Projection
	glm::mat4 model = glm::mat4(1.0f);		// initialize Matrix, Use this matrix for individual models
	glm::mat4 view = glm::mat4(1.0f);		//Use this matrix for ALL models
	glm::mat4 projection = glm::mat4(1.0f);	//This matrix is for Projection
	glm::mat4 modelTemp = glm::mat4(1.0f);
	glm::mat4 modelTemp2 = glm::mat4(1.0f);
	glm::mat4 modelTemp3 = glm::mat4(1.0f);
	view = glm::rotate(view, glm::radians(rotX), glm::vec3(1.0f, 0.0f, 0.0f));
	view = glm::rotate(view, glm::radians(rotY), glm::vec3(0.0f, 1.0f, 0.0f));
	view = glm::rotate(view, glm::radians(rotZ), glm::vec3(0.0f, 0.0f, 1.0f));

	//Use "projection" to include Camera
	projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	view = camera.GetViewMatrix();
	view = glm::translate(view, glm::vec3(movX, movY, movZ));

	//	view = glm::rotate(view, glm::radians(rotX), glm::vec3(1.0f, 0.0f, 0.0f));
		//view = glm::rotate(view, glm::radians(rotY), glm::vec3(0.0f, 1.0f, 0.0f));


		// pass them to the shaders
	projectionShader.setVec3("viewPos", camera.Position);
	projectionShader.setMat4("model", model);
	projectionShader.setMat4("view", view);
	// note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
	projectionShader.setMat4("projection", projection);


	glBindVertexArray(VAO);

	//glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	model = glm::scale(model, glm::vec3(20.0f, 0.05f, 20.0f));
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 0.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 0.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 0.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 0.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(-2.0f, 0.0f, -1.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


	model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 0.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 0.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 0.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 0.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	for (int i = 0; i <= 11; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
		projectionShader.setMat4("model", model);
		projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	}
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	for (int i = 0; i <= 11; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 0.0f));
		projectionShader.setMat4("model", model);
		projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	}

	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	for (int i = 0; i <= 11; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
		projectionShader.setMat4("model", model);
		projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	}

	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	for (int i = 0; i <= 11; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 0.0f));
		projectionShader.setMat4("model", model);
		projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	}


	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	for (int i = 0; i <= 11; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
		projectionShader.setMat4("model", model);
		projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	}
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	for (int i = 0; i <= 11; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 0.0f));
		projectionShader.setMat4("model", model);
		projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	}


	///
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	for (int i = 0; i <= 11; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
		projectionShader.setMat4("model", model);
		projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	}

	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	for (int i = 0; i <= 11; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 0.0f));
		projectionShader.setMat4("model", model);
		projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	}

	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	for (int i = 0; i <= 11; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
		projectionShader.setMat4("model", model);
		projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	}

	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	for (int i = 0; i <= 11; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 0.0f));
		projectionShader.setMat4("model", model);
		projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	}
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	for (int i = 0; i <= 11; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
		projectionShader.setMat4("model", model);
		projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	}
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	for (int i = 0; i <= 11; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 0.0f));
		projectionShader.setMat4("model", model);
		projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	}
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	for (int i = 0; i <= 11; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
		projectionShader.setMat4("model", model);
		projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	}


	//entrada	--------------------------------------------

	glActiveTexture(GL_TEXTURE);
	glBindTexture(GL_TEXTURE_2D, texture2);
	projectionShader.setInt("texture2", 1);

	model = glm::mat4(1.0f);

	model = glm::translate(model, glm::vec3(-42.0f, 2.0f, 26.0f));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(15.0f, 4.0f, 4.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 1.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(3.0f, 0.0f, 0.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 1.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = modelTemp;
	//columna 1 lado izquierdo
	model = glm::translate(model, glm::vec3(-5.0f, 8.5f, 0.0f));
	model = glm::scale(model, glm::vec3(5.0f, 13.0f, 4.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 1.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	//columna 2 lado izquierdo
	model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 1.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	//columna 1 lado derecho
	model = glm::translate(model, glm::vec3(7.0f, 0.0f, 0.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 1.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	//columna 2 lado derecho
	model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 1.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	//base bandera lado derecho columna 2
	glActiveTexture(GL_TEXTURE);
	glBindTexture(GL_TEXTURE_2D, texture3);

	model = glm::translate(model, glm::vec3(0.0f, 0.5250f, 0.0f));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(1.0f, 0.05f, 1.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 1.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(-2.0f, 0.0f, 0.0f));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 1.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(-9.0f, 0.0f, 0.0f));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 1.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 1.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//parte alta
	//model = modelTemp;

	model = glm::translate(model, glm::vec3(-2.0f, 3.53f, 0.0f));
	model = glm::scale(model, glm::vec3(0.450f, 6.0f, 0.450f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 1.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(24.5f, 0.0f, 0.0f));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 1.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(-4.55f, 0.5f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0f, 2.0f, 1.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 2.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(-15.55f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 1.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	//palito
	model = glm::translate(model, glm::vec3(0.0f, 0.75f, 0.0f));
	model = glm::scale(model, glm::vec3(0.2f, 0.50f, 0.20f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 1.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(-22.0f, -1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 1.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(99.7f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 1.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(22.7f, -1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 1.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//banderas
	glActiveTexture(GL_TEXTURE);
	glBindTexture(GL_TEXTURE_2D, texture4);

	model = glm::translate(model, glm::vec3(5.3f, 0.50f, -0.20f));
	//modelTemp = model;
	model = glm::scale(model, glm::vec3(10.0f, 0.5f, 1.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 0.0f));
	glDrawArrays(GL_TRIANGLES, 24, 3);
	//model = modelTemp;

	model = glm::translate(model, glm::vec3(-2.30f, 1.90f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 0.0f));
	glDrawArrays(GL_TRIANGLES, 24, 3);
	//model = modelTemp;

	model = glm::translate(model, glm::vec3(-7.750f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 0.0f));
	glDrawArrays(GL_TRIANGLES, 24, 3);

	model = glm::translate(model, glm::vec3(-2.18f, -1.9f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 0.0f));
	glDrawArrays(GL_TRIANGLES, 24, 3);


	//----------------letrero-------------------

	glActiveTexture(GL_TEXTURE);
	glBindTexture(GL_TEXTURE_2D, texture11);

	model = glm::translate(model, glm::vec3(5.550f, -0.430f, 1.0f));
	//model = glm::mat4(1.0f);
	model = glm::scale(model, glm::vec3(7.30, 3.10, 1.50));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	//Rueda de la fortuna////////////////////////////////////////////////////////////////
	glActiveTexture(GL_TEXTURE);
	glBindTexture(GL_TEXTURE_2D, texture5);//galaxia
	//base
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(2.0f, 0.5f, 0.0f));
	modelTemp = model;
	modelTemp3 = model;
	model = glm::scale(model, glm::vec3(35.0f, 0.50f, 15.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	model = modelTemp;

	//soporte
	model = glm::translate(model, glm::vec3(1.0f, 0.24f, 7.3));
	model = glm::scale(model, glm::vec3(15.0f, 25.0f, 0.33f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 0.0f));
	glDrawArrays(GL_TRIANGLES, 27, 3);

	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -45.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 0.0f));
	glDrawArrays(GL_TRIANGLES, 27, 3);

	//eje
	model = modelTemp;
	model = glm::translate(model, glm::vec3(1.0f, 18.0f, 0.0f));
	model = glm::rotate(model, glm::radians(angRueda), glm::vec3(0, 0, 1));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.5, 0.5, 14.8));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	//barras que sostienen la rueda al eje
	model = modelTemp;
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 3.20f));
	model = glm::scale(model, glm::vec3(1.0, 25.0, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	model = modelTemp;
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -3.20f));
	model = glm::scale(model, glm::vec3(1.0, 25.0, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = modelTemp;
	model = glm::translate(model, glm::vec3(6.50f, 0.0f, 3.20f));
	model = glm::scale(model, glm::vec3(12.0, 1.0, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	model = modelTemp;
	model = glm::translate(model, glm::vec3(6.50f, 0.0f, -3.20f));
	model = glm::scale(model, glm::vec3(12.0, 1.0, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = modelTemp;
	model = glm::translate(model, glm::vec3(-6.50f, 0.0f, 3.20f));
	model = glm::scale(model, glm::vec3(12.0, 1.0, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	model = modelTemp;
	model = glm::translate(model, glm::vec3(-6.50f, 0.0f, -3.20f));
	model = glm::scale(model, glm::vec3(12.0, 1.0, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = modelTemp;
	model = glm::rotate(model, glm::radians(40.0f), glm::vec3(0, 0, 1));
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 2.20f));
	model = glm::scale(model, glm::vec3(0.80, 25.50, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = modelTemp;
	model = glm::rotate(model, glm::radians(-40.0f), glm::vec3(0, 0, 1));
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.20f));
	model = glm::scale(model, glm::vec3(0.80, 25.50, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	//circulos rueda
	model = modelTemp;
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -3.50f));
	model = glm::scale(model, glm::vec3(12.50, 12.50, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	circulos();
	model = modelTemp;
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 3.50f));
	model = glm::scale(model, glm::vec3(12.50, 12.50, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	circulos2();

	//barras entre las ruedas
	model = modelTemp;
	model = glm::translate(model, glm::vec3(0.0f, -12.55f, 0.0f));
	model = glm::scale(model, glm::vec3(0.5, 0.5, 7.5));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(16.0f, 6.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(-32.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(-7.0f, 9.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(46.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(2.0f, 10.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(-50.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(3.0f, 12.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(44.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(-6.0f, 7.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(-32.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = modelTemp;
	model = glm::translate(model, glm::vec3(0.0f, 12.50f, 0.0f));
	model = glm::scale(model, glm::vec3(0.50, 0.50, 8.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glActiveTexture(GL_TEXTURE);
	glBindTexture(GL_TEXTURE_2D, texture7);
	//esferas rueda de la fortuna
	//canasta1 Aros-------------------------------------------------------------------------
	model = modelTemp;
	model = glm::translate(model, glm::vec3(0.0f, -12.350f, -0.20f));
	model = glm::rotate(model, glm::radians(angCanasta), glm::vec3(0, 0, 1));
	modelTemp2 = model;
	model = glm::translate(model, glm::vec3(0.0f, -0.50f, 0.0f));
	//model = modelTemp2;
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 0.0f));
	circulos();
	//canasta 
	//soporte
	model = modelTemp2;
	glActiveTexture(GL_TEXTURE);
	glBindTexture(GL_TEXTURE_2D, texture2);
	model = glm::translate(model, glm::vec3(0.0f, -2.50f, 0.3f));
	model = glm::scale(model, glm::vec3(0.250, 2.50, 0.250));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//techo canasta
	model = glm::translate(model, glm::vec3(0.0f, 0.45f, 0.0f));
	model = glm::scale(model, glm::vec3(2.0, 0.10, 2.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 0.0f));
	my_sphere.render();
	glBindVertexArray(VAO);
	//piso canasta
	//caja
	glActiveTexture(GL_TEXTURE);
	glBindTexture(GL_TEXTURE_2D, texture7);
	model = glm::translate(model, glm::vec3(0.0f, -8.05f, 0.0f));
	model = glm::scale(model, glm::vec3(3.50, 3.0, 3.50));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);
	glActiveTexture(GL_TEXTURE);
	glBindTexture(GL_TEXTURE_2D, texture8);
	model = glm::translate(model, glm::vec3(0.0f, -0.550f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 0.10, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 0.0f));
	my_sphere.render();
	glBindVertexArray(VAO);
	glActiveTexture(GL_TEXTURE);
	//asiento enfrente textura galaxia
	glBindTexture(GL_TEXTURE_2D, texture5);
	model = glm::translate(model, glm::vec3(0.0f, 1.80f, 0.39f));
	model = glm::scale(model, glm::vec3(0.80, 5.0, 0.20));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//asientoatras
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -3.90f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 01.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//asientoder
	model = glm::translate(model, glm::vec3(0.4950f, 0.0f, 2.0f));
	model = glm::scale(model, glm::vec3(0.250, 1.0, 2.500));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//asientoizq
	model = glm::translate(model, glm::vec3(-3.94950f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.00));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//disco azul
	glActiveTexture(GL_TEXTURE);
	glBindTexture(GL_TEXTURE_2D, texture9);
	model = glm::translate(model, glm::vec3(2.0f, 6.0f, 0.0f));
	model = glm::scale(model, glm::vec3(2.0, 0.010, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 0.0f));
	my_sphere.render();
	glBindVertexArray(VAO);

	//canasta2 Aros------------------------------------------------------------------------
	glActiveTexture(GL_TEXTURE);
	glBindTexture(GL_TEXTURE_2D, texture7);
	model = modelTemp;
	model = glm::translate(model, glm::vec3(0.0f, 12.350f, 0.0f));
	model = glm::rotate(model, glm::radians(angCanasta), glm::vec3(0, 0, 1));
	modelTemp2 = model;
	model = glm::translate(model, glm::vec3(0.0f, -0.50f, 0.0f));
	//model = modelTemp2;
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 0.0f));
	circulos();
	//canasta
	//soporte
	model = modelTemp2;
	glActiveTexture(GL_TEXTURE);
	glBindTexture(GL_TEXTURE_2D, texture2);
	model = glm::translate(model, glm::vec3(0.0f, -2.50f, 0.3f));
	model = glm::scale(model, glm::vec3(0.250, 2.50, 0.250));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//techo canasta
	model = glm::translate(model, glm::vec3(0.0f, 0.45f, 0.0f));
	model = glm::scale(model, glm::vec3(2.0, 0.10, 2.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 0.0f));
	my_sphere.render();
	glBindVertexArray(VAO);
	//piso canasta
	//model = modelTemp2;
	glActiveTexture(GL_TEXTURE);
	glBindTexture(GL_TEXTURE_2D, texture7);
	model = glm::translate(model, glm::vec3(0.0f, -8.05f, 0.0f));
	model = glm::scale(model, glm::vec3(3.50, 3.0, 3.50));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);
	glActiveTexture(GL_TEXTURE);
	glBindTexture(GL_TEXTURE_2D, texture8);
	model = glm::translate(model, glm::vec3(0.0f, -0.550f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 0.10, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 0.0f));
	my_sphere.render();
	glBindVertexArray(VAO);
	glActiveTexture(GL_TEXTURE);
	//asiento enfrente textura galaxia
	glBindTexture(GL_TEXTURE_2D, texture5);
	model = glm::translate(model, glm::vec3(0.0f, 1.80f, 0.39f));
	model = glm::scale(model, glm::vec3(0.80, 5.0, 0.20));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//asientoatras
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -3.90f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 01.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//asientoder
	model = glm::translate(model, glm::vec3(0.4950f, 0.0f, 2.0f));
	model = glm::scale(model, glm::vec3(0.250, 1.0, 2.500));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//asientoizq
	model = glm::translate(model, glm::vec3(-3.94950f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.00));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//disco azul
	glActiveTexture(GL_TEXTURE);
	glBindTexture(GL_TEXTURE_2D, texture9);
	model = glm::translate(model, glm::vec3(2.0f, 6.0f, 0.0f));
	model = glm::scale(model, glm::vec3(2.0, 0.010, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 0.0f));
	my_sphere.render();
	glBindVertexArray(VAO);
	//canasta3 Aros-----------------------------------------------------------------------------------------
	glActiveTexture(GL_TEXTURE);
	glBindTexture(GL_TEXTURE_2D, texture7);
	model = modelTemp;
	model = glm::translate(model, glm::vec3(12.30f, -0.30f, 0.0f));
	model = glm::rotate(model, glm::radians(angCanasta), glm::vec3(0, 0, 1));
	modelTemp2 = model;
	model = glm::translate(model, glm::vec3(0.0f, -0.50f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 0.0f));
	circulos();
	//canasta
	//soporte
	model = modelTemp2;
	glActiveTexture(GL_TEXTURE);
	glBindTexture(GL_TEXTURE_2D, texture2);
	model = glm::translate(model, glm::vec3(0.0f, -2.50f, 0.3f));
	model = glm::scale(model, glm::vec3(0.250, 2.50, 0.250));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//techo canasta
	model = glm::translate(model, glm::vec3(0.0f, 0.45f, 0.0f));
	model = glm::scale(model, glm::vec3(2.0, 0.10, 2.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 0.0f));
	my_sphere.render();
	glBindVertexArray(VAO);
	//piso canasta
	glActiveTexture(GL_TEXTURE);
	glBindTexture(GL_TEXTURE_2D, texture7);
	model = glm::translate(model, glm::vec3(0.0f, -8.05f, 0.0f));
	model = glm::scale(model, glm::vec3(3.50, 3.0, 3.50));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);
	glActiveTexture(GL_TEXTURE);
	glBindTexture(GL_TEXTURE_2D, texture8);
	model = glm::translate(model, glm::vec3(0.0f, -0.550f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 0.10, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 0.0f));
	my_sphere.render();
	glBindVertexArray(VAO);
	glActiveTexture(GL_TEXTURE);
	//asiento enfrente textura galaxia
	glBindTexture(GL_TEXTURE_2D, texture5);
	model = glm::translate(model, glm::vec3(0.0f, 1.80f, 0.39f));
	model = glm::scale(model, glm::vec3(0.80, 5.0, 0.20));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//asientoatras
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -3.90f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 01.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//asientoder
	model = glm::translate(model, glm::vec3(0.4950f, 0.0f, 2.0f));
	model = glm::scale(model, glm::vec3(0.250, 1.0, 2.500));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//asientoizq
	model = glm::translate(model, glm::vec3(-3.94950f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.00));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//disco azul
	glActiveTexture(GL_TEXTURE);
	glBindTexture(GL_TEXTURE_2D, texture9);
	model = glm::translate(model, glm::vec3(2.0f, 6.0f, 0.0f));
	model = glm::scale(model, glm::vec3(2.0, 0.010, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 0.0f));
	my_sphere.render();
	glBindVertexArray(VAO);
	//canasta 4  Aros--------------------------------------------------------------------------------------
	glActiveTexture(GL_TEXTURE);
	glBindTexture(GL_TEXTURE_2D, texture7);
	model = modelTemp;
	model = glm::translate(model, glm::vec3(-12.30f, -0.30f, 0.0f));
	model = glm::rotate(model, glm::radians(angCanasta), glm::vec3(0, 0, 1));
	modelTemp2 = model;
	model = glm::translate(model, glm::vec3(0.0f, -0.50f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 0.0f));
	circulos();
	//canasta
	//soporte
	model = modelTemp2;
	glActiveTexture(GL_TEXTURE);
	glBindTexture(GL_TEXTURE_2D, texture2);
	model = glm::translate(model, glm::vec3(0.0f, -2.50f, 0.3f));
	model = glm::scale(model, glm::vec3(0.250, 2.50, 0.250));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//techo canasta
	model = glm::translate(model, glm::vec3(0.0f, 0.45f, 0.0f));
	model = glm::scale(model, glm::vec3(2.0, 0.10, 2.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 0.0f));
	my_sphere.render();
	glBindVertexArray(VAO);
	//piso canasta
	glActiveTexture(GL_TEXTURE);
	glBindTexture(GL_TEXTURE_2D, texture7);
	model = glm::translate(model, glm::vec3(0.0f, -8.05f, 0.0f));
	model = glm::scale(model, glm::vec3(3.50, 3.0, 3.50));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);
	glActiveTexture(GL_TEXTURE);
	glBindTexture(GL_TEXTURE_2D, texture8);
	model = glm::translate(model, glm::vec3(0.0f, -0.550f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 0.10, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 0.0f));
	my_sphere.render();
	glBindVertexArray(VAO);
	glActiveTexture(GL_TEXTURE);
	//asiento enfrente textura galaxia
	glBindTexture(GL_TEXTURE_2D, texture5);
	model = glm::translate(model, glm::vec3(0.0f, 1.80f, 0.39f));
	model = glm::scale(model, glm::vec3(0.80, 5.0, 0.20));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//asientoatras
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -3.90f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 01.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//asientoder
	model = glm::translate(model, glm::vec3(0.4950f, 0.0f, 2.0f));
	model = glm::scale(model, glm::vec3(0.250, 1.0, 2.500));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//asientoizq
	model = glm::translate(model, glm::vec3(-3.94950f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.00));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//disco azul
	glActiveTexture(GL_TEXTURE);
	glBindTexture(GL_TEXTURE_2D, texture9);
	model = glm::translate(model, glm::vec3(2.0f, 6.0f, 0.0f));
	model = glm::scale(model, glm::vec3(2.0, 0.010, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 0.0f));
	my_sphere.render();
	glBindVertexArray(VAO);

	//canasta 5  Aros--------------------------------------------------------------------------------------
	glActiveTexture(GL_TEXTURE);
	glBindTexture(GL_TEXTURE_2D, texture7);
	model = modelTemp;
	model = glm::translate(model, glm::vec3(8.320f, 9.40f, 0.0f));
	model = glm::rotate(model, glm::radians(angCanasta), glm::vec3(0, 0, 1));
	modelTemp2 = model;
	model = glm::translate(model, glm::vec3(0.0f, -0.50f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 0.0f));
	circulos();
	//canasta
	//soporte
	model = modelTemp2;
	glActiveTexture(GL_TEXTURE);
	glBindTexture(GL_TEXTURE_2D, texture2);
	model = glm::translate(model, glm::vec3(0.0f, -2.50f, 0.3f));
	model = glm::scale(model, glm::vec3(0.250, 2.50, 0.250));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//techo canasta
	model = glm::translate(model, glm::vec3(0.0f, 0.45f, 0.0f));
	model = glm::scale(model, glm::vec3(2.0, 0.10, 2.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 0.0f));
	my_sphere.render();
	glBindVertexArray(VAO);
	//piso canasta
	glActiveTexture(GL_TEXTURE);
	glBindTexture(GL_TEXTURE_2D, texture7);
	model = glm::translate(model, glm::vec3(0.0f, -8.05f, 0.0f));
	model = glm::scale(model, glm::vec3(3.50, 3.0, 3.50));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);
	glActiveTexture(GL_TEXTURE);
	glBindTexture(GL_TEXTURE_2D, texture8);
	model = glm::translate(model, glm::vec3(0.0f, -0.550f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 0.10, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 0.0f));
	my_sphere.render();
	glBindVertexArray(VAO);
	glActiveTexture(GL_TEXTURE);
	//asiento enfrente textura galaxia
	glBindTexture(GL_TEXTURE_2D, texture5);
	model = glm::translate(model, glm::vec3(0.0f, 1.80f, 0.39f));
	model = glm::scale(model, glm::vec3(0.80, 5.0, 0.20));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//asientoatras
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -3.90f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 01.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//asientoder
	model = glm::translate(model, glm::vec3(0.4950f, 0.0f, 2.0f));
	model = glm::scale(model, glm::vec3(0.250, 1.0, 2.500));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//asientoizq
	model = glm::translate(model, glm::vec3(-3.94950f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.00));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//disco azul
	glActiveTexture(GL_TEXTURE);
	glBindTexture(GL_TEXTURE_2D, texture9);
	model = glm::translate(model, glm::vec3(2.0f, 6.0f, 0.0f));
	model = glm::scale(model, glm::vec3(2.0, 0.010, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 0.0f));
	my_sphere.render();
	glBindVertexArray(VAO);

	//canasta 6 Aros--------------------------------------------------------------------------------------
	glActiveTexture(GL_TEXTURE);
	glBindTexture(GL_TEXTURE_2D, texture7);
	model = modelTemp;
	model = glm::translate(model, glm::vec3(-8.320f, 9.40f, 0.0f));
	model = glm::rotate(model, glm::radians(angCanasta), glm::vec3(0, 0, 1));
	modelTemp2 = model;
	model = glm::translate(model, glm::vec3(0.0f, -0.50f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 0.0f));
	circulos();
	//canasta
	//soporte
	model = modelTemp2;
	glActiveTexture(GL_TEXTURE);
	glBindTexture(GL_TEXTURE_2D, texture2);
	model = glm::translate(model, glm::vec3(0.0f, -2.50f, 0.3f));
	model = glm::scale(model, glm::vec3(0.250, 2.50, 0.250));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//techo canasta
	model = glm::translate(model, glm::vec3(0.0f, 0.45f, 0.0f));
	model = glm::scale(model, glm::vec3(2.0, 0.10, 2.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 0.0f));
	my_sphere.render();
	glBindVertexArray(VAO);
	//piso canasta
	glActiveTexture(GL_TEXTURE);
	glBindTexture(GL_TEXTURE_2D, texture7);
	model = glm::translate(model, glm::vec3(0.0f, -8.05f, 0.0f));
	model = glm::scale(model, glm::vec3(3.50, 3.0, 3.50));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);
	glActiveTexture(GL_TEXTURE);
	glBindTexture(GL_TEXTURE_2D, texture8);
	model = glm::translate(model, glm::vec3(0.0f, -0.550f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 0.10, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 0.0f));
	my_sphere.render();
	glBindVertexArray(VAO);
	glActiveTexture(GL_TEXTURE);
	//asiento enfrente textura galaxia
	glBindTexture(GL_TEXTURE_2D, texture5);
	model = glm::translate(model, glm::vec3(0.0f, 1.80f, 0.39f));
	model = glm::scale(model, glm::vec3(0.80, 5.0, 0.20));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//asientoatras
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -3.90f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 01.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//asientoder
	model = glm::translate(model, glm::vec3(0.4950f, 0.0f, 2.0f));
	model = glm::scale(model, glm::vec3(0.250, 1.0, 2.500));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//asientoizq
	model = glm::translate(model, glm::vec3(-3.94950f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.00));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//disco azul
	glActiveTexture(GL_TEXTURE);
	glBindTexture(GL_TEXTURE_2D, texture9);
	model = glm::translate(model, glm::vec3(2.0f, 6.0f, 0.0f));
	model = glm::scale(model, glm::vec3(2.0, 0.010, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 0.0f));
	my_sphere.render();
	glBindVertexArray(VAO);

	//canasta 7 Aros--------------------------------------------------------------------------------------
	glActiveTexture(GL_TEXTURE);
	glBindTexture(GL_TEXTURE_2D, texture7);
	model = modelTemp;
	model = glm::translate(model, glm::vec3(8.310f, -9.450f, 0.0f));
	model = glm::rotate(model, glm::radians(angCanasta), glm::vec3(0, 0, 1));
	modelTemp2 = model;
	model = glm::translate(model, glm::vec3(0.0f, -0.50f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 0.0f));
	circulos();
	//canasta
	//soporte
	model = modelTemp2;
	glActiveTexture(GL_TEXTURE);
	glBindTexture(GL_TEXTURE_2D, texture2);
	model = glm::translate(model, glm::vec3(0.0f, -2.50f, 0.3f));
	model = glm::scale(model, glm::vec3(0.250, 2.50, 0.250));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//techo canasta
	model = glm::translate(model, glm::vec3(0.0f, 0.45f, 0.0f));
	model = glm::scale(model, glm::vec3(2.0, 0.10, 2.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 0.0f));
	my_sphere.render();
	glBindVertexArray(VAO);
	//piso canasta
	glActiveTexture(GL_TEXTURE);
	glBindTexture(GL_TEXTURE_2D, texture7);
	model = glm::translate(model, glm::vec3(0.0f, -8.05f, 0.0f));
	model = glm::scale(model, glm::vec3(3.50, 3.0, 3.50));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);
	glActiveTexture(GL_TEXTURE);
	glBindTexture(GL_TEXTURE_2D, texture8);
	model = glm::translate(model, glm::vec3(0.0f, -0.550f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 0.10, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 0.0f));
	my_sphere.render();
	glBindVertexArray(VAO);
	glActiveTexture(GL_TEXTURE);
	//asiento enfrente textura galaxia
	glBindTexture(GL_TEXTURE_2D, texture5);
	model = glm::translate(model, glm::vec3(0.0f, 1.80f, 0.39f));
	model = glm::scale(model, glm::vec3(0.80, 5.0, 0.20));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//asientoatras
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -3.90f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 01.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//asientoder
	model = glm::translate(model, glm::vec3(0.4950f, 0.0f, 2.0f));
	model = glm::scale(model, glm::vec3(0.250, 1.0, 2.500));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//asientoizq
	model = glm::translate(model, glm::vec3(-3.94950f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.00));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//disco azul
	glActiveTexture(GL_TEXTURE);
	glBindTexture(GL_TEXTURE_2D, texture9);
	model = glm::translate(model, glm::vec3(2.0f, 6.0f, 0.0f));
	model = glm::scale(model, glm::vec3(2.0, 0.010, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 0.0f));
	my_sphere.render();
	glBindVertexArray(VAO);

	//canasta 8 Aros--------------------------------------------------------------------------------------
	glActiveTexture(GL_TEXTURE);
	glBindTexture(GL_TEXTURE_2D, texture7);
	model = modelTemp;
	model = glm::translate(model, glm::vec3(-8.320f, -9.450f, 0.0f));
	model = glm::rotate(model, glm::radians(angCanasta), glm::vec3(0, 0, 1));
	modelTemp2 = model;
	model = glm::translate(model, glm::vec3(0.0f, -0.50f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 0.0f));
	circulos();
	//canasta
	//soporte
	model = modelTemp2;
	glActiveTexture(GL_TEXTURE);
	glBindTexture(GL_TEXTURE_2D, texture2);
	model = glm::translate(model, glm::vec3(0.0f, -2.50f, 0.3f));
	model = glm::scale(model, glm::vec3(0.250, 2.50, 0.250));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//techo canasta
	model = glm::translate(model, glm::vec3(0.0f, 0.45f, 0.0f));
	model = glm::scale(model, glm::vec3(2.0, 0.10, 2.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 0.0f));
	my_sphere.render();
	glBindVertexArray(VAO);
	//piso canasta
	glActiveTexture(GL_TEXTURE);
	glBindTexture(GL_TEXTURE_2D, texture7);
	model = glm::translate(model, glm::vec3(0.0f, -8.05f, 0.0f));
	model = glm::scale(model, glm::vec3(3.50, 3.0, 3.50));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);
	glActiveTexture(GL_TEXTURE);
	glBindTexture(GL_TEXTURE_2D, texture8);
	model = glm::translate(model, glm::vec3(0.0f, -0.550f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 0.10, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 0.0f));
	my_sphere.render();
	glBindVertexArray(VAO);
	glActiveTexture(GL_TEXTURE);
	//asiento enfrente textura galaxia
	glBindTexture(GL_TEXTURE_2D, texture5);
	model = glm::translate(model, glm::vec3(0.0f, 1.80f, 0.39f));
	model = glm::scale(model, glm::vec3(0.80, 5.0, 0.20));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//asientoatras
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -3.90f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 01.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//asientoder
	model = glm::translate(model, glm::vec3(0.4950f, 0.0f, 2.0f));
	model = glm::scale(model, glm::vec3(0.250, 1.0, 2.500));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//asientoizq
	model = glm::translate(model, glm::vec3(-3.94950f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.00));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//disco azul
	glActiveTexture(GL_TEXTURE);
	glBindTexture(GL_TEXTURE_2D, texture9);
	model = glm::translate(model, glm::vec3(2.0f, 6.0f, 0.0f));
	model = glm::scale(model, glm::vec3(2.0, 0.010, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 0.0f));
	my_sphere.render();
	glBindVertexArray(VAO);

	model = modelTemp;
	glActiveTexture(GL_TEXTURE);
	glBindTexture(GL_TEXTURE_2D, texture10);
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 7.50f));
	model = glm::scale(model, glm::vec3(2.0, 2.0, 0.150));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 0.0f));
	my_sphere.render();
	glBindVertexArray(VAO);

	//escalera canastas
	model = modelTemp3;
	glActiveTexture(GL_TEXTURE);
	glBindTexture(GL_TEXTURE_2D, texture5);
	model = glm::translate(model, glm::vec3(1.0f, 0.860f, 2.0f));
	model = glm::scale(model, glm::vec3(02.0, 1.40, 1.0));
	projectionShader.setMat4("model", model);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glBindTexture(GL_TEXTURE_2D, texture9);
	model = glm::translate(model, glm::vec3(0.0f, -0.10, 0.750f));
	model = glm::scale(model, glm::vec3(01.0, 0.80, 0.50));
	projectionShader.setMat4("model", model);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glBindTexture(GL_TEXTURE_2D, texture8);
	model = glm::translate(model, glm::vec3(0.0f, -0.10, 1.0f));
	model = glm::scale(model, glm::vec3(01.0, 0.80, 1.0));
	projectionShader.setMat4("model", model);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glBindTexture(GL_TEXTURE_2D, texture9);
	model = glm::translate(model, glm::vec3(0.0f, -0.10, 1.0f));
	model = glm::scale(model, glm::vec3(01.0, 0.80, 1.0));
	projectionShader.setMat4("model", model);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glBindTexture(GL_TEXTURE_2D, texture8);
	model = glm::translate(model, glm::vec3(0.0f, -0.10, 1.0f));
	model = glm::scale(model, glm::vec3(01.0, 0.80, 1.0));
	projectionShader.setMat4("model", model);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glBindTexture(GL_TEXTURE_2D, texture9);
	model = glm::translate(model, glm::vec3(0.0f, -0.10, 1.0f));
	model = glm::scale(model, glm::vec3(01.0, 0.80, 1.0));
	projectionShader.setMat4("model", model);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//cercado
	model = modelTemp3;
	glActiveTexture(GL_TEXTURE);
	glBindTexture(GL_TEXTURE_2D, texture9);
	model = glm::translate(model, glm::vec3(-18.0f, 1.010f, 12.0f));
	model = glm::scale(model, glm::vec3(0.40, 3.0, 0.40));
	projectionShader.setMat4("model", model);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	projectionShader.setMat4("model", model);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	projectionShader.setMat4("model", model);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	projectionShader.setMat4("model", model);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	projectionShader.setMat4("model", model);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	projectionShader.setMat4("model", model);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	projectionShader.setMat4("model", model);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


	model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	projectionShader.setMat4("model", model);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	projectionShader.setMat4("model", model);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	projectionShader.setMat4("model", model);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	projectionShader.setMat4("model", model);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	projectionShader.setMat4("model", model);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	projectionShader.setMat4("model", model);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);







	//-------------------------------------------------------------------------------------------

	//MONTAÑA RUSA 
	glActiveTexture(GL_TEXTURE);
	glBindTexture(GL_TEXTURE_2D, texture14);
	model = glm::mat4(1.0f);
	//modelTemp = model;
	model = glm::translate(model, glm::vec3(0.0f, 13.0f, -100.0f));
	model = glm::scale(model, glm::vec3(8, 25, 4));
	modelTemp2 = model;
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(5.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1, 1, 1));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -6.0f));
	model = glm::scale(model, glm::vec3(1, 1, 1));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(-5.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1, 1, 1));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	//cabina plancha 
	glActiveTexture(GL_TEXTURE);
	glBindTexture(GL_TEXTURE_2D, texture10);


	model = glm::translate(model, glm::vec3(2.5f, 0.55f, 3.0f));
	model = glm::scale(model, glm::vec3(6.0, 0.1, 8.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


	//parte donde van los rieles en la plancha 
	glActiveTexture(GL_TEXTURE);
	glBindTexture(GL_TEXTURE_2D, texture14);
	model = glm::translate(model, glm::vec3(0.0f, 0.5f, 0.0f));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(1.0, 0.1, 0.5));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//barandales de la plancha
	glActiveTexture(GL_TEXTURE);
	glBindTexture(GL_TEXTURE_2D, texture4);
	model = glm::translate(model, glm::vec3(-0.495f, 5.9f, 0.55f));
	model = glm::scale(model, glm::vec3(0.01, 12.0, 0.02));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	for (int i = 0; i <= 3; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 5.5f));
		model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
		projectionShader.setMat4("model", model);
		projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	}

	model = glm::translate(model, glm::vec3(10.0f, 0.0f, -22.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	for (int i = 0; i <= 1; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 5.5f));
		model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
		projectionShader.setMat4("model", model);
		projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	}

	model = glm::translate(model, glm::vec3(10.0f, 0.0f, -11.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	for (int i = 0; i <= 1; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 5.5f));
		model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
		projectionShader.setMat4("model", model);
		projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	}

	model = glm::translate(model, glm::vec3(10.0f, 0.0f, -11.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	for (int i = 0; i <= 1; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 5.5f));
		model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
		projectionShader.setMat4("model", model);
		projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	}


	model = glm::translate(model, glm::vec3(10.0f, 0.0f, -11.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	for (int i = 0; i <= 1; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 5.5f));
		model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
		projectionShader.setMat4("model", model);
		projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	}

	model = glm::translate(model, glm::vec3(10.0f, 0.0f, -11.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	for (int i = 0; i <= 1; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 5.5f));
		model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
		projectionShader.setMat4("model", model);
		projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	}
	model = glm::translate(model, glm::vec3(10.0f, 0.0f, -11.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	for (int i = 0; i <= 1; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 5.5f));
		model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
		projectionShader.setMat4("model", model);
		projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	}
	model = glm::translate(model, glm::vec3(10.0f, 0.0f, -11.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	for (int i = 0; i <= 1; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 5.5f));
		model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
		projectionShader.setMat4("model", model);
		projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	}
	model = glm::translate(model, glm::vec3(10.0f, 0.0f, -11.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	for (int i = 0; i <= 1; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 5.5f));
		model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
		projectionShader.setMat4("model", model);
		projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	}


	model = glm::translate(model, glm::vec3(19.0f, 0.0f, 11.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	for (int i = 0; i <= 37; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(-2.5f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
		projectionShader.setMat4("model", model);
		projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	}

	model = glm::translate(model, glm::vec3(-3.5f, 0.0f, -98.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	for (int i = 0; i <= 29; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(2.5f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
		projectionShader.setMat4("model", model);
		projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	}

	model = glm::translate(model, glm::vec3(23.5f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	for (int i = 0; i <= 3; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 5.5f));
		model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
		projectionShader.setMat4("model", model);
		projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	}

	model = glm::translate(model, glm::vec3(-98.5f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	for (int i = 0; i <= 2; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -5.5f));
		model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
		projectionShader.setMat4("model", model);
		projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	}
	//barandales de las rejas 
	model = glm::translate(model, glm::vec3(0.0f, 0.5f, 6.0f));
	model = glm::scale(model, glm::vec3(1.0, 0.04, 23.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(98.5f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.2));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(-19.0, 0.0f, 2.55f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 0.5));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	for (int i = 0; i <= 6; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(-10.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
		projectionShader.setMat4("model", model);
		projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	}

	model = glm::translate(model, glm::vec3(-10.0f, 0.0f, 0.3f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.8));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(50.0f, 0.0f, 0.5f));
	model = glm::scale(model, glm::vec3(100.0, 1.0, 0.05));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(-0.13f, 0.0f, -79.0f));
	model = glm::scale(model, glm::vec3(0.75, 1.0, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


	//puertas 

	model = glm::translate(model, glm::vec3(-0.42f, -10.0f, 61.0f));
	model = glm::scale(model, glm::vec3(0.130, 20.0, 0.5));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


	model = glm::translate(model, glm::vec3(1.025f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.02, 1.0, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	for (int i = 0; i <= 5; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
		projectionShader.setMat4("model", model);
		projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	}
	model = glm::translate(model, glm::vec3(1.5f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(2.0, 1.0, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	//ESCALERAS 
	glActiveTexture(GL_TEXTURE);
	glBindTexture(GL_TEXTURE_2D, texture4);
	model = glm::translate(model, glm::vec3(0.6f, -6.4f, 16.0f));
	model = glm::scale(model, glm::vec3(0.3, 11.3, 40.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(1.0f, -0.05f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 0.9, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


	for (int i = 0; i <= 25; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(1.0f, -0.05f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0, 0.9, 1.0));
		projectionShader.setMat4("model", model);
		projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	}

	//escalera para bajar 
	model = glm::translate(model, glm::vec3(-30.0f, 7.5f, -3.6f));
	model = glm::scale(model, glm::vec3(3.5, 18.0, 0.3));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(0.0f, -0.05f, -1.0f));
	model = glm::scale(model, glm::vec3(1.0, 0.9, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


	for (int i = 0; i <= 30; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(0.0, -0.05f, -1.0f));
		model = glm::scale(model, glm::vec3(1.0, 0.9, 1.0));
		projectionShader.setMat4("model", model);
		projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	}

	//--------------------Postes-Soporte----------------
	glActiveTexture(GL_TEXTURE);
	glBindTexture(GL_TEXTURE_2D, texture14);

	model = modelTemp2;

	//aqui los pones, escalalos y todo
	//ejemplo:
		//aqui los pones, escalalos y todo
	//ejemplo:
	model = glm::translate(model, glm::vec3(-2.0f, 0.0f, -3.1f));
	model = glm::scale(model, glm::vec3(0.25, 1.07, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(-5.5f, -0.09f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 0.8, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(-5.5f, -0.088f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 0.78, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(-5.5f, -0.065f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 0.95, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(-5.5f, -0.02f, -0.05f));
	model = glm::scale(model, glm::vec3(1.0, 1.32, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(-8.0f, 0.18f, -0.05f));
	model = glm::scale(model, glm::vec3(2.0, 1.28, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(-2.5f, 0.05f, -2.5f));
	model = glm::scale(model, glm::vec3(1.0, 1.2, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(0.0f, 0.00f, -3.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(2.5f, 0.0f, -2.5f));
	model = glm::scale(model, glm::vec3(1.0, 1.03, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


	model = glm::translate(model, glm::vec3(3.7f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.05, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(6.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.4, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(4.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.1, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(5.0f, 0.07, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.25, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(7.0f, 0.065, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 0.64, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(7.0f, -0.02, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 0.9, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(8.0f, -0.25f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 0.59, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(6.0f, -0.1f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 0.85, 1.5));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(0.0f, -0.13f, 3.0f));
	model = glm::scale(model, glm::vec3(1.5, 0.6, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 2.0));
	model = glm::scale(model, glm::vec3(0.8, 1.2, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


	model = glm::translate(model, glm::vec3(-4.5f, 0.0f, 0.1f));
	model = glm::scale(model, glm::vec3(1.0, 1.2, 1.2));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(-5.0f, 0.4, 0.0f));
	model = glm::scale(model, glm::vec3(-1.0, 1.7, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	//----------------Rieles-------------------Rieles-----------------Rieles-----------------------------------

	glActiveTexture(GL_TEXTURE);
	glBindTexture(GL_TEXTURE_2D, texture13);

	model = modelTemp;

	model = glm::translate(model, glm::vec3(0.50f, 0.150f, 0.0f));
	model = glm::scale(model, glm::vec3(0.0250, 0.250, 0.15));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(-2.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.00, 1.0, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


	for (int i = 0; i <= 20; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(-2.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
		modelTemp = model;
		projectionShader.setMat4("model", model);
		projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	}
	for (int i = 0; i <= 4; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(-1.80f, -0.80f, 0.0f));
		model = glm::scale(model, glm::vec3(1.00, 1.0, 1.0));
		model = glm::rotate(model, glm::radians(2.50f), glm::vec3(0, 0, 1));
		projectionShader.setMat4("model", model);
		projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	for (int i = 0; i <= 4; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(-1.80f, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.00, 1.0, 1.0));
		model = glm::rotate(model, glm::radians(1.0f), glm::vec3(0, 0, 1));
		projectionShader.setMat4("model", model);
		projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	for (int i = 0; i <= 5; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(-2.0f, -0.80f, 0.0f));
		model = glm::scale(model, glm::vec3(1.00, 1.0, 1.0));
		model = glm::rotate(model, glm::radians(-1.0f), glm::vec3(0, 0, 1));
		projectionShader.setMat4("model", model);
		projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	model = glm::translate(model, glm::vec3(0.0f, -0.50f, 0.0f));
	model = glm::rotate(model, glm::radians(-14.0f), glm::vec3(0, 0, 1));

	for (int i = 0; i <= 3; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(-2.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
		projectionShader.setMat4("model", model);
		projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}

	for (int i = 0; i <= 2; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(-1.80f, 0.80f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
		model = glm::rotate(model, glm::radians(-1.0f), glm::vec3(0, 0, 1));
		projectionShader.setMat4("model", model);
		projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	for (int i = 0; i <= 2; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(-1.80f, 0.80f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
		model = glm::rotate(model, glm::radians(-2.0f), glm::vec3(0, 0, 1));
		projectionShader.setMat4("model", model);
		projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	for (int i = 0; i <= 5; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(-1.60f, 0.80f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
		model = glm::rotate(model, glm::radians(-3.0f), glm::vec3(0, 0, 1));

		projectionShader.setMat4("model", model);
		projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	//-------------------giroooooo--------------------------------------	
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(21.0f), glm::vec3(0, 0, 1));

	for (int i = 0; i <= 1; i = i + 1) //giro
	{
		model = glm::translate(model, glm::vec3(-1.2, 0.07f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
		model = glm::rotate(model, glm::radians(-8.50f), glm::vec3(0, 1, 0));
		model = glm::rotate(model, glm::radians(-1.50f), glm::vec3(1, 0, 0));

		projectionShader.setMat4("model", model);
		projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	model = modelTemp;
	model = glm::translate(model, glm::vec3(-64.0f, 1.0f, -5.50f));
	model = glm::scale(model, glm::vec3(4.0, 1.0, 0.250));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	for (int i = 0; i <= 3; i = i + 1) //giro 2 a la derecha 
	{
		model = glm::translate(model, glm::vec3(0.2f, 0.50f, -0.750f));
		model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
		model = glm::rotate(model, glm::radians(-5.65f), glm::vec3(0, 1, 0));
		projectionShader.setMat4("model", model);
		projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}

	//middle
	model = modelTemp;
	model = glm::translate(model, glm::vec3(-64.0f, 1.0f, -5.20f));
	model = glm::scale(model, glm::vec3(4.0, 1.0, 0.250));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	for (int i = 0; i <= 6; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.30f));
		model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
		projectionShader.setMat4("model", model);
		projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	//giro 1
	model = modelTemp;
	model = glm::translate(model, glm::vec3(-64.0f, 1.0f, -2.50f));
	model = glm::scale(model, glm::vec3(4.0, 1.0, 0.250));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	for (int i = 0; i <= 5; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(0.015f, -0.520f, 1.40f));
		model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
		model = glm::rotate(model, glm::radians(4.50f), glm::vec3(0, 1, 0));
		model = glm::rotate(model, glm::radians(3.50f), glm::vec3(1, 0, 0));
		projectionShader.setMat4("model", model);
		projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	//atras rampa
	model = modelTemp;
	model = glm::translate(model, glm::vec3(-51.50f, 0.0f, -7.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	//model = glm::rotate(model, glm::radians(-8.50f), glm::vec3(0, 1, 0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(-1.50f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	model = glm::translate(model, glm::vec3(-1.50f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	model = glm::translate(model, glm::vec3(-1.50f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	model = glm::translate(model, glm::vec3(-1.50f, 1.0f, 0.0001f));
	model = glm::rotate(model, glm::radians(10.50f), glm::vec3(0, 1, 0));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 0.60));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	//atras rampa
	model = modelTemp;//subida
	model = glm::translate(model, glm::vec3(-50.0f, 0.0f, -7.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	for (int i = 0; i <= 8; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(1.50f, 0.50f, 0.0f));
		model = glm::scale(model, glm::vec3(1.00, 1.0, 1.0));
		model = glm::rotate(model, glm::radians(2.50f), glm::vec3(0, 0, 1));
		projectionShader.setMat4("model", model);
		projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	for (int i = 0; i <= 8; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(1.80f, 0.50f, 0.0f));
		model = glm::scale(model, glm::vec3(1.00, 1.0, 1.0));
		model = glm::rotate(model, glm::radians(-2.50f), glm::vec3(0, 0, 1));
		projectionShader.setMat4("model", model);
		projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	for (int i = 0; i <= 4; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(1.50f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.00, 1.0, 1.0));
		//model = glm::rotate(model, glm::radians(-2.0f), glm::vec3(0, 0, 1));
		projectionShader.setMat4("model", model);
		projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	for (int i = 0; i <= 7; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(1.50f, 0.80f, 0.0f));
		model = glm::scale(model, glm::vec3(1.00, 1.0, 1.0));
		model = glm::rotate(model, glm::radians(2.50f), glm::vec3(0, 0, 1));
		projectionShader.setMat4("model", model);
		projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	for (int i = 0; i <= 4; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(1.20f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.00, 1.0, 1.0));
		model = glm::rotate(model, glm::radians(2.50f), glm::vec3(0, 0, 1));
		projectionShader.setMat4("model", model);
		projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	for (int i = 0; i <= 2; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(1.50f, 0.70f, 0.0f));
		model = glm::scale(model, glm::vec3(1.00, 1.0, 1.0));
		model = glm::rotate(model, glm::radians(-2.50f), glm::vec3(0, 0, 1));
		projectionShader.setMat4("model", model);
		projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	for (int i = 0; i <= 1; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(1.50f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.00, 1.0, 1.0));
		model = glm::rotate(model, glm::radians(-2.50f), glm::vec3(0, 0, 1));
		projectionShader.setMat4("model", model);
		projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	for (int i = 0; i <= 6; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(1.50f, -0.70f, 0.0f));
		model = glm::scale(model, glm::vec3(1.00, 1.0, 1.0));
		model = glm::rotate(model, glm::radians(-2.50f), glm::vec3(0, 0, 1));
		projectionShader.setMat4("model", model);
		projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	for (int i = 0; i <= 9; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(1.20f, -0.60f, 0.0f));
		model = glm::scale(model, glm::vec3(1.00, 1.0, 1.0));
		model = glm::rotate(model, glm::radians(-2.80f), glm::vec3(0, 0, 1));
		projectionShader.setMat4("model", model);
		projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	for (int i = 0; i <= 2; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(1.50f, -0.40f, 0.0f));
		model = glm::scale(model, glm::vec3(1.00, 1.0, 1.0));
		model = glm::rotate(model, glm::radians(0.80f), glm::vec3(0, 0, 1));
		projectionShader.setMat4("model", model);
		projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	for (int i = 0; i <= 2; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(1.60f, -0.40f, 0.0f));
		model = glm::scale(model, glm::vec3(1.00, 1.0, 1.0));
		model = glm::rotate(model, glm::radians(2.50f), glm::vec3(0, 0, 1));
		projectionShader.setMat4("model", model);
		projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	for (int i = 0; i <= 3; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(1.50f, -0.40f, 0.0f));
		model = glm::scale(model, glm::vec3(1.00, 1.0, 1.0));
		model = glm::rotate(model, glm::radians(-1.0f), glm::vec3(0, 0, 1));
		projectionShader.setMat4("model", model);
		projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	for (int i = 0; i <= 2; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(1.50f, 0.50f, 0.0f));
		model = glm::scale(model, glm::vec3(1.00, 1.0, 1.0));
		model = glm::rotate(model, glm::radians(-1.0f), glm::vec3(0, 0, 1));
		projectionShader.setMat4("model", model);
		projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	for (int i = 0; i <= 7; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(1.20f, 0.750f, 0.0f));
		model = glm::scale(model, glm::vec3(1.00, 1.0, 1.0));
		model = glm::rotate(model, glm::radians(1.10f), glm::vec3(0, 0, 1));
		projectionShader.setMat4("model", model);
		projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	for (int i = 0; i <= 2; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(1.50f, 0.50f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
		model = glm::rotate(model, glm::radians(-1.10f), glm::vec3(0, 0, 1));
		projectionShader.setMat4("model", model);
		projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	for (int i = 0; i <= 2; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(1.50f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
		model = glm::rotate(model, glm::radians(-1.0f), glm::vec3(0, 0, 1));
		projectionShader.setMat4("model", model);
		projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	for (int i = 0; i <= 7; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(1.60f, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
		model = glm::rotate(model, glm::radians(-1.10f), glm::vec3(0, 0, 1));
		projectionShader.setMat4("model", model);
		projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	for (int i = 0; i <= 5; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(1.70f, -1.20f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
		model = glm::rotate(model, glm::radians(-1.50f), glm::vec3(0, 0, 1));
		projectionShader.setMat4("model", model);
		projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	for (int i = 0; i <= 2; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(1.80f, -0.5f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
		model = glm::rotate(model, glm::radians(1.0f), glm::vec3(0, 0, 1));
		projectionShader.setMat4("model", model);
		projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	for (int i = 0; i <= 2; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(1.50f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
		model = glm::rotate(model, glm::radians(1.30f), glm::vec3(0, 0, 1));
		projectionShader.setMat4("model", model);
		projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	for (int i = 0; i <= 4; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(1.50f, 0.50f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
		model = glm::rotate(model, glm::radians(1.50f), glm::vec3(0, 0, 1));
		projectionShader.setMat4("model", model);
		projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	//giro de regreso
	model = glm::rotate(model, glm::radians(15.50f), glm::vec3(0, 0, 1));

	for (int i = 0; i <= 3; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(1.30f, 0.0f, 0.1f));
		model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
		model = glm::rotate(model, glm::radians(-3.50f), glm::vec3(0, 1, 0));
		projectionShader.setMat4("model", model);
		projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	model = modelTemp;
	model = glm::translate(model, glm::vec3(45.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	for (int i = 0; i <= 4; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(1.30f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
		projectionShader.setMat4("model", model);
		projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	for (int i = 0; i <= 2; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(1.50f, -0.50f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
		projectionShader.setMat4("model", model);
		projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	for (int i = 0; i <= 8; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(1.50f, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
		model = glm::rotate(model, glm::radians(-2.50f), glm::vec3(0, 0, 1));
		projectionShader.setMat4("model", model);
		projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	for (int i = 0; i <= 2; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(1.640f, -0.850f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
		model = glm::rotate(model, glm::radians(1.0f), glm::vec3(0, 0, 1));
		projectionShader.setMat4("model", model);
		projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	for (int i = 0; i <= 3; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(1.80f, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
		model = glm::rotate(model, glm::radians(1.0f), glm::vec3(0, 0, 1));
		projectionShader.setMat4("model", model);
		projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	model = glm::rotate(model, glm::radians(4.0f), glm::vec3(0, 0, 1));

	for (int i = 0; i <= 5; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(1.90f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
		projectionShader.setMat4("model", model);
		projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	for (int i = 0; i <= 8; i = i + 1)//no
	{
		model = glm::translate(model, glm::vec3(1.30f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
		model = glm::rotate(model, glm::radians(2.70f), glm::vec3(0, 1, 0));
		projectionShader.setMat4("model", model);
		projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	
	model = modelTemp;
	model = glm::translate(model, glm::vec3(100.0f, -16.0f,- 6.5f));
	model = glm::scale(model, glm::vec3(4.0, 1.0, 0.250));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	for (int i = 0; i <= 11; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(0.0f, -0.50f, 1.30f));
		model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
		projectionShader.setMat4("model", model);
		projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}




	//---------------------------------------MODELOS -------------------------------------------
	//arbol ////////////////

	modelShader.use();

	modelShader.setMat4("model", model);
	modelShader.setMat4("view", view);
	// note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
	modelShader.setMat4("projection", projection);

	model = glm::mat4(1.0f);
	modelShader.setMat4("model", model);
	model = glm::translate(model, glm::vec3(-60.0f, 0.10f, -25.0f));
	model = glm::scale(model, glm::vec3(0.0150f, 0.0150f, 0.0150f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 1.0f, 0.0f));
	Tree.Draw(modelShader);

	model = glm::mat4(1.0f);
	modelShader.setMat4("model", model);
	model = glm::translate(model, glm::vec3(-55.0f, 0.10f, -15.0f));
	model = glm::scale(model, glm::vec3(01.350f, 01.350f, 01.350f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 1.0f, 0.0f));
	FoodCart.Draw(modelShader);

	model = glm::mat4(1.0f);
	modelShader.setMat4("model", model);
	model = glm::translate(model, glm::vec3(-45.0f, 0.10f, -15.0f));
	model = glm::scale(model, glm::vec3(0.0150f, 0.0250f, 0.0150f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 1.0f, 0.0f));
	//Tree.Draw(modelShader);
	model = glm::mat4(1.0f);
	modelShader.setMat4("model", model);
	model = glm::translate(model, glm::vec3(-45.0f, 0.10f, -10.0f));
	model = glm::scale(model, glm::vec3(0.0150f, 0.0250f, 0.0150f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 1.0f, 0.0f));
	//Tree.Draw(modelShader);
	model = glm::mat4(1.0f);
	modelShader.setMat4("model", model);
	model = glm::translate(model, glm::vec3(-45.0f, 0.10f, -5.0f));
	model = glm::scale(model, glm::vec3(0.0150f, 0.0250f, 0.0150f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 1.0f, 0.0f));
	//Tree.Draw(modelShader);

	model = glm::mat4(1.0f);
	modelShader.setMat4("model", model);
	model = glm::translate(model, glm::vec3(5.0f, 0.10f, 5.0f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1, 0, 0));
	model = glm::scale(model, glm::vec3(1.0f, 1.00f, 1.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 1.0f, 0.0f));
	//Soldado1.Draw(modelShader);

	model = glm::mat4(1.0f);
	modelShader.setMat4("model", model);// 5.0f, 30.10f, -125.0f
	model = glm::translate(model, glm::vec3(movKit_x, movKit_y, movKit_z));
	model = glm::rotate(model, glm::radians(rotKit_y), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.4f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 1.0f, 0.0f));
	Carrito.Draw(modelShader);
	


	glBindVertexArray(VAO);
}

int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	// glfw window creation
	// --------------------
	monitors = glfwGetPrimaryMonitor();
	getResolution();

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Proyecto Feria Diaz y Ortiz", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwSetWindowPos(window, 0, 30);
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, resize);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	//To Enable capture of our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	glewInit();


	//Mis funciones
	//Datos a utilizar
	myData();
	my_sphere.init();
	glEnable(GL_DEPTH_TEST);

	//-----------------------MODELOS-------------------------------------
	Shader modelShader("Shaders/modelLoading.vs", "Shaders/modelLoading.fs");
	// Load models
	Model Tree = ((char*)"Models/arbol2/Tree_Conifer_1.obj");
	Model FoodCart = ((char*)"Models/Cart_food/street_cart_meetball.obj");
	Model Soldado = ((char*)"Models/Soldier_with_binoculars/18826_Soldier_with_binoculars_in_one_hand_and_pointing_with_the_other_hand_v1_NEW.obj");
	Model Carrito= ((char*)"Models/carrito/wooden_model _truck.obj");


	//-------------------------------------------------------






	// render loop
	// While the windows is not closed
	while (!glfwWindowShouldClose(window))
	{
		// per-frame time logic
		// --------------------
		double currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		// input
		// -----
		my_input(window);
		animate();

		// render
		// Backgound color
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Mi función de dibujo
		display(Tree, FoodCart, Soldado,Carrito);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void my_input(GLFWwindow * window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		movY += 0.07f;
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
		movY -= 0.07f;
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		play = true;

}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void resize(GLFWwindow * window, int width, int height)
{
	// Set the Viewport to the size of the created window
	glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow * window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	double xoffset = xpos - lastX;
	double yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow * window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}
