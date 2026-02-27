 #include <iostream> 
using namespace std;

// ÷„Ì‰ «·„ﬂ »«  

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath> 

// ======================= Vertex Shader =======================
// „”ƒÊ· ⁄‰  ÕœÌœ „Êﬁ⁄ ﬂ· ‰ﬁÿ… (Vertex)
const char* vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec2 aPos;   
uniform vec2 offset; 
uniform vec2 scale;   

void main()
{
    
    vec2 pos = aPos * scale + offset;
    gl_Position = vec4(pos, 0.0, 1.0);
}
)";

// ======================= Fragment Shader =======================
// „”ƒÊ· ⁄‰ ·Ê‰ ﬂ· »ﬂ”·
const char* fragmentShaderSource = R"(
#version 330 core
out vec4 FragColor;    
uniform vec3 color;    

void main()
{
    FragColor = vec4(color, 1.0);
}
)";

GLuint shaderProgram; // »—‰«„Ã «·‘Ìœ—
GLuint VAO, VBO;      // VAO Ê VBO

// ======================= —”„ „” ÿÌ· =======================
void drawRectangle(float x, float y, float w, float h, float r, float g, float b)
{
    
    float vertices[] = {
        -0.5f,-0.5f,
         0.5f,-0.5f,
         0.5f, 0.5f,
        -0.5f, 0.5f
    };

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    
    glUseProgram(shaderProgram);

    
    glUniform2f(glGetUniformLocation(shaderProgram, "offset"), x, y);
    glUniform2f(glGetUniformLocation(shaderProgram, "scale"), w, h);
    glUniform3f(glGetUniformLocation(shaderProgram, "color"), r, g, b);

    glBindVertexArray(VAO);

    // —”„ «·„” ÿÌ· »«” Œœ«„ TRIANGLE_FAN
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

// ======================= —”„ „À·À =======================
void drawTriangle(float x, float y, float w, float h, float r, float g, float b)
{
    float vertices[] = {
         0.0f, 0.5f,
        -0.5f,-0.5f,
         0.5f,-0.5f
    };

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glUseProgram(shaderProgram);
    glUniform2f(glGetUniformLocation(shaderProgram, "offset"), x, y);
    glUniform2f(glGetUniformLocation(shaderProgram, "scale"), w, h);
    glUniform3f(glGetUniformLocation(shaderProgram, "color"), r, g, b);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

// ======================= —”„ œ«∆—… =======================
void drawCircle(float x, float y, float radius, float r, float g, float b)
{
    const int segments = 40; // ⁄œœ «·‰ﬁ«ÿ «· Ì  ﬂÊ¯‰ «·œ«∆—…
    float vertices[segments * 2];

    // Õ”«» ‰ﬁ«ÿ «·œ«∆—… »«” Œœ«„ sin Ê cos
    for (int i = 0; i < segments; i++)
    {
        float angle = 2.0f * 3.14159f * i / segments;
        vertices[i * 2] = cos(angle);
        vertices[i * 2 + 1] = sin(angle);
    }

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glUseProgram(shaderProgram);
    glUniform2f(glGetUniformLocation(shaderProgram, "offset"), x, y);
    glUniform2f(glGetUniformLocation(shaderProgram, "scale"), radius, radius);
    glUniform3f(glGetUniformLocation(shaderProgram, "color"), r, g, b);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLE_FAN, 0, segments);
}

// ======================= main =======================
int main()
{
    glfwInit(); 

    // ≈‰‘«¡ ‰«›–…
    GLFWwindow* window = glfwCreateWindow(800, 600, "Robot Face", NULL, NULL);
    glfwMakeContextCurrent(window);

    glewInit(); 

    // ===== Compile Vertex Shader =====
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // ===== Compile Fragment Shader =====
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // ===== Link Shader Program =====
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // ≈‰‘«¡ VAO Ê VBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

   
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    
    while (!glfwWindowShouldClose(window))
    {
		// ⁄‰œ ÷€ÿ (Space)° «·⁄ÌÊ‰   ÕÊ· ≈·Ï Õ„—«¡
        bool spacePressed = glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS;

        glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

		// —√” «·—Ê»Ê ... „” ÿÌ·
        drawRectangle(0.0f, 0.0f, 0.6f, 0.6f, 0.7f, 0.7f, 0.8f);

		// «·√–‰Ì‰..„” ÿÌ·Ì‰
        drawRectangle(-0.35f, 0.0f, 0.08f, 0.25f, 1.0f, 0.0f, 0.0f);
        drawRectangle(0.35f, 0.0f, 0.08f, 0.25f, 1.0f, 0.0f, 0.0f);

        //„” ÿÌ· Ê œ«∆—…  ..  „” ﬁ»· ≈‘«—«  
        drawRectangle(0.0f, 0.35f, 0.05f, 0.15f, 0.5f, 0.5f, 0.5f);
        drawCircle(0.0f, 0.48f, 0.035f, 1.0f, 0.0f, 0.0f);

		// «·⁄Ì‰Ì‰ ... œ«∆— Ì‰
        if (spacePressed)
        {
            drawCircle(-0.15f, 0.1f, 0.05f, 1.0f, 0.0f, 0.0f);
            drawCircle(0.15f, 0.1f, 0.05f, 1.0f, 0.0f, 0.0f);
        }
        else
        {
            drawCircle(-0.15f, 0.1f, 0.05f, 1.0f, 1.0f, 1.0f);
            drawCircle(0.15f, 0.1f, 0.05f, 1.0f, 1.0f, 1.0f);
        }

        // «·√‰› ...„À·À 
        drawTriangle(0.0f, -0.05f, 0.08f, 0.08f, 0.9f, 0.6f, 0.3f);

		// «·›„... „” ÿÌ·
        drawRectangle(0.0f, -0.22f, 0.25f, 0.03f, 1.0f, 1.0f, 1.0f);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

