/*---------------------------------------------------------*/
/* ----------------  Práctica Animación 3       -----------*/
/*-----------------    2024-1   ---------------------------*/
/*------------- Alumno: Daniel Pérez Cruz   ---------------*/
/*------------- No. Cuenta: 315609343       ---------------*/
#include <Windows.h>

#include <glad/glad.h>
#include <glfw3.h>	//main
#include <stdlib.h>		
#include <glm/glm.hpp>	//camera y model
#include <glm/gtc/matrix_transform.hpp>	//camera y model
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/random.hpp>
#include <time.h>


#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>	//Texture

#define SDL_MAIN_HANDLED
#include <SDL/SDL.h>

#include <shader_m.h>
#include <camera.h>
#include <modelAnim.h>
#include <model.h>
#include <Skybox.h>
#include <iostream>

//#pragma comment(lib, "winmm.lib")

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//void my_input(GLFWwindow *window);
void my_input(GLFWwindow* window, int key, int scancode, int action, int mods);
void animate(void);

// settings
unsigned int SCR_WIDTH = 800;
unsigned int SCR_HEIGHT = 600;
GLFWmonitor *monitors;

void getResolution(void);

// camera
Camera camera(glm::vec3(0.0f, 5.0f, 30.0f));
float MovementSpeed = 0.1f;
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
const int FPS = 60;
const int LOOP_TIME = 1000 / FPS; // = 16 milisec // 1000 millisec == 1 sec
double	deltaTime = 0.0f,
		lastFrame = 0.0f;

//Lighting
glm::vec3 lightPosition(60.0f, 50.0f, 30.0f);
glm::vec3 lightDirection(0.0f, -1.0f, 0.0f);

//// Light
glm::vec3 lightColor = glm::vec3(0.7f);
glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
glm::vec3 ambientColor = diffuseColor * glm::vec3(0.75f);

// posiciones
float	torg_x = 30.0f,
		torg_y = 0.0f,
		torg_z = 15.0f,

		torm_x = 30.0f,
		torm_y = 0.0f,
		torm_z = 15.0f,

		torp_x = 30.0f,
		torp_y = 0.0f,
		torp_z = 15.0f;

bool	hanoyAnim = false,
		paso1 = true,
		paso2 = false,
		paso3 = false,
		paso4 = false,
		paso5 = false,
		paso6 = false,
		paso7 = false;

void animate(void)
{
	if (hanoyAnim)
	{
		if (paso1)
		{
			if (torp_y <= 10.0f && torp_z <= 20.0f)
				torp_y += 1.0f;
			if (torp_y >= 10.0f && torp_z <= 44.0f)
				torp_z += 1.0f;
			if (torp_y <= 11.0f && torp_z >= 44.0f)
				torp_y -= 1.0f;
			if (torp_y <= -2.75f && torp_z >= 44.0f)
			{
				paso2 = true;
				paso1 = false;
			}
		}
		if (paso2)
		{
			if (torm_y <= 10.0f && torm_z <= 20.0f)
				torm_y += 1.0f;
			if (torm_y >= 10.0f && torm_z <= 29.0f)
				torm_z += 1.0f;
			if (torm_y <= 11.0f && torm_z >= 29.0f)
				torm_y -= 0.7f;
			if (torm_y <= -1.05f && torm_z >= 29.0f)
			{
				paso3 = true;
				paso2 = false;
			}
		}
		if (paso3)
		{
			if (torp_y <= 10.0f && torp_z >= 44.0f)
				torp_y += 1.0f;
			if (torp_y >= 10.0f && torp_z >= 31.0f)
				torp_z -= 1.0f;
			if (torp_y <= 11.0f && torp_z <= 31.0f)
				torp_y -= 1.0f;
			if (torp_y <= -1.05f && torp_z <= 31.0f)
			{
				paso4 = true;
				paso3 = false;
			}
		}
		if (paso4)
		{
			if (torg_y <= 10.0f && torg_z <= 20.0f)
				torg_y += 1.0f;
			if (torg_y >= 10.0f && torg_z <= 44.0f)
				torg_z += 1.0f;
			if (torg_y <= 11.0f && torg_z >= 44.0f)
				torg_y -= 1.0f;
			if (torg_y <= 0.0f && torg_z >= 44.0f)
			{
				paso5 = true;
				paso4 = false;
			}
		}
		if (paso5)
		{
			if (torp_y <= 10.0f && torp_z >= 30.0f)
				torp_y += 1.0f;
			if (torp_y >= 10.0f && torp_z >= 15.0f)
				torp_z -= 1.0f;
			if (torp_y <= 11.0f && torp_z <= 15.0f)
				torp_y -= 1.0f;
			if (torp_y <= -2.75f && torp_z <= 15.0f)
			{
				paso6 = true;
				paso5 = false;
			}
		}
		if (paso6)
		{
			if (torm_y <= 10.0f && torm_z <= 30.0f)
				torm_y += 1.0f;
			if (torm_y >= 10.0f && torm_z <= 45.0f)
				torm_z += 1.0f;
			if (torm_y <= 11.0f && torm_z >= 45.0f)
				torm_y -= 0.7f;
			if (torm_y <= 0.0f && torm_z >= 45.0f)
			{
				paso7 = true;
				paso6 = false;
			}
		}
		if (paso7)
		{
			if (torp_y <= 10.0f && torp_z <= 20.0f)
				torp_y += 1.0f;
			if (torp_y >= 10.0f && torp_z <= 44.0f)
				torp_z += 1.0f;
			if (torp_y <= 11.0f && torp_z >= 44.0f)
				torp_y -= 1.0f;
			if (torp_y <= 0.0f && torp_z >= 44.0f)
			{
				paso7 = false;
				hanoyAnim = false;
			}
		}
	}
}

void getResolution()
{
	const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	SCR_WIDTH = mode->width;
	SCR_HEIGHT = (mode->height) - 80;
}

int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// glfw window creation
	// --------------------
	// --------------------
	monitors = glfwGetPrimaryMonitor();
	getResolution();

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "CGeIHC 20241", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwSetWindowPos(window, 0, 30);
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetKeyCallback(window, my_input);

	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);

	// build and compile shaders
	// -------------------------
	Shader staticShader("Shaders/shader_Lights.vs", "Shaders/shader_Lights_mod.fs");
	Shader skyboxShader("Shaders/skybox.vs", "Shaders/skybox.fs");
	Shader animShader("Shaders/anim.vs", "Shaders/anim.fs");

	vector<std::string> faces
	{
		"resources/skybox/right.jpg",
		"resources/skybox/left.jpg",
		"resources/skybox/top.jpg",
		"resources/skybox/bottom.jpg",
		"resources/skybox/front.jpg",
		"resources/skybox/back.jpg"
	};

	Skybox skybox = Skybox(faces);

	// Shader configuration
	// --------------------
	skyboxShader.use();
	skyboxShader.setInt("skybox", 0);

	// load models
	// -----------

	Model Plano("resources/objects/Hanoy/Plano.obj");
	Model Base("resources/objects/Hanoy/Base.obj");
	Model TorG("resources/objects/Hanoy/TorG.obj");
	Model TorM("resources/objects/Hanoy/TorM.obj");
	Model TorP("resources/objects/Hanoy/TorP.obj");

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		skyboxShader.setInt("skybox", 0);

		// per-frame time logic
		// --------------------
		lastFrame = SDL_GetTicks();

		// input
		// -----
		//my_input(window);
		animate();

		// render
		// ------
		glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// don't forget to enable shader before setting uniforms
		staticShader.use();
		//Setup Advanced Lights
		staticShader.setVec3("viewPos", camera.Position);
		staticShader.setVec3("dirLight.direction", lightDirection);
		staticShader.setVec3("dirLight.ambient", glm::vec3(0.3f, 0.3f, 0.3f));
		staticShader.setVec3("dirLight.diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
		staticShader.setVec3("dirLight.specular", glm::vec3(0.2f, 0.2f, 0.2f));

		staticShader.setVec3("pointLight[0].position", lightPosition);
		staticShader.setVec3("pointLight[0].ambient", glm::vec3(0.1f, 0.1f, 0.1f));
		staticShader.setVec3("pointLight[0].diffuse", glm::vec3(0.2f, 0.2f, 0.2f));
		staticShader.setVec3("pointLight[0].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("pointLight[0].constant", 0.08f);
		staticShader.setFloat("pointLight[0].linear", 0.00009f);
		staticShader.setFloat("pointLight[0].quadratic", 0.00032f);

		staticShader.setVec3("spotLight[0].position", glm::vec3(camera.Position.x, camera.Position.y, camera.Position.z));
		staticShader.setVec3("spotLight[0].direction", glm::vec3(camera.Front.x, camera.Front.y, camera.Front.z));
		staticShader.setVec3("spotLight[0].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("spotLight[0].diffuse", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("spotLight[0].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("spotLight[0].cutOff", glm::cos(glm::radians(10.0f)));
		staticShader.setFloat("spotLight[0].outerCutOff", glm::cos(glm::radians(15.0f)));
		staticShader.setFloat("spotLight[0].constant", 1.0f);
		staticShader.setFloat("spotLight[0].linear", 0.00009f);
		staticShader.setFloat("spotLight[0].quadratic", 0.00005f);

		staticShader.setFloat("material_shininess", 16.0f);

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 tmp = glm::mat4(1.0f);
		// view/projection transformations
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 10000.0f);
		glm::mat4 view = camera.GetViewMatrix();
		staticShader.setMat4("projection", projection);
		staticShader.setMat4("view", view);

		// -------------------------------------------------------------------------------------------------------------------------
		// Escenario
		// -------------------------------------------------------------------------------------------------------------------------
		staticShader.use();
		staticShader.setMat4("projection", projection);
		staticShader.setMat4("view", view);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(30.0f, 0.0f, 30.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", model);
		Plano.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(30.0f, 0.0f, 15.0f));
		staticShader.setMat4("model", model);
		Base.Draw(staticShader);
		
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(torg_x, torg_y, torg_z));
		staticShader.setMat4("model", model);
		TorG.Draw(staticShader);
		
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(torm_x, torm_y, torm_z));
		staticShader.setMat4("model", model);
		TorM.Draw(staticShader);
		
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(torp_x, torp_y, torp_z));
		staticShader.setMat4("model", model);
		TorP.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(30.0f, 0.0f, 30.0f));
		staticShader.setMat4("model", model);
		Base.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(30.0f, 0.0f, 45.0f));
		staticShader.setMat4("model", model);
		Base.Draw(staticShader);

		// -------------------------------------------------------------------------------------------------------------------------
		// Termina Escenario
		// -------------------------------------------------------------------------------------------------------------------------

		//-------------------------------------------------------------------------------------
		// draw skybox as last
		// -------------------
		skyboxShader.use();
		skybox.Draw(skyboxShader, view, projection, camera);

		// Limitar el framerate a 60
		deltaTime = SDL_GetTicks() - lastFrame; // time for full 1 loop
		//std::cout <<"frame time = " << frameTime << " milli sec"<< std::endl;
		if (deltaTime < LOOP_TIME)
		{
			SDL_Delay((int)(LOOP_TIME - deltaTime));
		}

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	skybox.Terminate();

	glfwTerminate();
	return 0;
}

void my_input(GLFWwindow *window, int key, int scancode, int action, int mode)
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
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		camera.ProcessKeyboard(UP, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		camera.ProcessKeyboard(DOWN, (float)deltaTime);

	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
		hanoyAnim ^= true;
	if (key == GLFW_KEY_R && action == GLFW_PRESS)
	{
		torg_x = torm_x = torp_x = 30.0f;
		torg_y = torm_y = torp_y = 0.0f;
		torg_z = torm_z = torp_z = 15.0f;

		paso1 = true;
		hanoyAnim = false;
	}
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}
// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}