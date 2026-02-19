#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// Vertex Shader
const char* vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor; // «··Ê‰ ·ﬂ· —√”
out vec3 ourColor; // ‰—”· «··Ê‰ ··‹ Fragment Shader
void main()
{
    gl_Position = vec4(aPos, 1.0);
    ourColor = aColor;
}
)";

// Fragment Shader
const char* fragmentShaderSource = R"(
#version 330 core
in vec3 ourColor;
out vec4 FragColor;
uniform float uAlpha; 
void main()
{
    FragColor = vec4(ourColor, uAlpha);
}
)";

void processInput(GLFWwindow* window)
{
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Two Triangles Z-Alpha", NULL, NULL);
    if (!window) { glfwTerminate(); return -1; }
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    glewInit();

    // 2.  ›⁄Ì· Depth Ê Blend
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // 3. »‰«¡ «·‘Ìœ—
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    
    float vertices[] = {
       
        -0.5f, -0.5f, 0.0f,  1.0f, 1.0f, 0.0f,
         0.5f, -0.5f, 0.0f,  1.0f, 1.0f, 0.0f,
         0.0f,  0.5f, 0.0f,  1.0f, 1.0f, 0.0f,
         
        -0.2f, -0.5f, 0.5f,  0.0f, 1.0f, 1.0f,
         0.8f, -0.5f, 0.5f,  0.0f, 1.0f, 1.0f,
         0.3f,  0.5f, 0.5f,  0.0f, 1.0f, 1.0f
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // «·„Êﬁ⁄
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // «··Ê‰
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Õ·ﬁ… «·—”„
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        int alphaLoc = glGetUniformLocation(shaderProgram, "uAlpha");
        
        glUniform1f(alphaLoc, 1.0f); 
        glDrawArrays(GL_TRIANGLES, 3, 3);

        glUniform1f(alphaLoc, 0.5f); 
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
    glfwTerminate();
    return 0;
}