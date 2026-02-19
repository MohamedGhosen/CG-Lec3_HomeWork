#include <iostream>
// 1.  ÷„Ì‰ «·„ﬂ »« 
// „·«ÕŸ…: ÌÃ»  ÷„Ì‰ GLEW ﬁ»· GLFW œ«∆„«
#define GLEW_STATIC // ·√‰‰« ‰” Œœ„ „ﬂ »… glew32s.lib (Static)
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// ≈⁄œ«œ«  «·‰«›–…
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

float vertices[] = {
        -0.5f, -0.5f, 0.0f, // Ì”«— √”›·
         0.5f, -0.5f, 0.0f, // Ì„Ì‰ √”›·
         0.5f,  0.5f, 0.0f  // √⁄·Ï Ì„Ì‰
};
// --- 2. ﬂÊœ «·„Ÿ··«  (Shaders) ---

// A. ﬂÊœ Vertex Shader
// ÊŸÌ› Â:  ÕœÌœ „Êﬁ⁄ —ƒÊ” «·„À·À ›Ì «·›÷«¡
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n" // ‰” ﬁ»· «·»Ì«‰«  ›Ì «·„Êﬁ⁄ 0
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n" // ‰„—— «·„Êﬁ⁄ ﬂ„« ÂÊ
"}\0";

// B. ﬂÊœ Fragment Shader
// ÊŸÌ› Â:  ÕœÌœ ·Ê‰ «·»ﬂ”·«  (Â‰« »— ﬁ«·Ì)
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.0f, 0.5f, 0.5f, 1.0f);\n" // RGBA: »— ﬁ«·Ì
"}\n\0";

// œ«·… ·„⁄«·Ã…  €ÌÌ— ÕÃ„ «·‰«›–… „‰ ﬁ»· «·„” Œœ„
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

// œ«·… ·„⁄«·Ã… «·„œŒ·«  („À· «·÷€ÿ ⁄·Ï “— ESC)
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        vertices[1] += 0.01f;
        vertices[4] += 0.01f;
        vertices[7] += 0.01f;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        vertices[1] -= 0.01f;
        vertices[4] -= 0.01f;
        vertices[7] -= 0.01f;
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        vertices[0] += 0.01f;
        vertices[3] += 0.01f;
        vertices[6] += 0.01f;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        vertices[0] -= 0.01f;
        vertices[3] -= 0.01f;
        vertices[6] -= 0.01f;
    }

}

int main()
{
    // --- 3.  ÂÌ∆… GLFW Ê≈⁄œ«œ «·‰«›–… ---
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // ≈’œ«— OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // «·‰„ÿ «·ÕœÌÀ

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Œ«’ »√ÃÂ“… „«ﬂ
#endif

    // ≈‰‘«¡ ﬂ«∆‰ «·‰«›–…
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL - First Triangle", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window); // Ã⁄· Â–Â «·‰«›–… ÂÌ ”Ì«ﬁ «·—”„ «·Õ«·Ì
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); // —»ÿ œ«·…  €ÌÌ— «·ÕÃ„

    // --- 4.  ÂÌ∆… GLEW ---
    glewExperimental = GL_TRUE; //  ›⁄Ì· «· ﬁ‰Ì«  «·ÕœÌÀ…
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    // --- 5. »‰«¡ Ê Ã„Ì⁄ »—‰«„Ã «·‘Ìœ— (Shader Program) ---

    // √.  Ã„Ì⁄ Vertex Shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // ›Õ’ «·√Œÿ«¡
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // ».  Ã„Ì⁄ Fragment Shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // ›Õ’ «·√Œÿ«¡
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Ã. —»ÿ «·‘Ìœ—“ ›Ì »—‰«„Ã Ê«Õœ (Shader Program)
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // ›Õ’ √Œÿ«¡ «·—»ÿ
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    // Õ–› «·‘Ìœ—“ «·„‰›’·… ·√‰‰« —»ÿ‰«Â« ›Ì «·»—‰«„Ã Ê·„ ‰⁄œ »Õ«Ã… ·Â«
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // --- 6.  ⁄—Ì› «·»Ì«‰«  («·„À·À) ---


    // --- 7. ≈⁄œ«œ VBO Ê VAO ---
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO); //  Ê·Ìœ «·„⁄—›« 
    glGenBuffers(1, &VBO);

    // ŒÿÊ… „Â„… Ãœ«: «—»ÿ VAO √Ê·« ﬁ»· √Ì ‘Ì¡ ¬Œ—
    glBindVertexArray(VAO);

    // «—»ÿ VBO Ê«‰”Œ «·»Ì«‰«  ≈·ÌÂ
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // ‘—Õ «·»Ì«‰«  ·‹ OpenGL (Linking Vertex Attributes)
    // 0: «·„Êﬁ⁄ ›Ì «·‘Ìœ—
    // 3: ÕÃ„ «·»Ì«‰«  (3 floats ·ﬂ· ‰ﬁÿ…)
    // GL_FLOAT: ‰Ê⁄ «·»Ì«‰« 
    // GL_FALSE: ·« ‰—Ìœ  ÿ»Ì⁄ «·»Ì«‰« 
    // 3 * sizeof(float): «·ŒÿÊ… (Stride)
    // (void*)0: «·≈“«Õ… (»œ«Ì… «·»Ì«‰« )
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0); //  ›⁄Ì· «·”„… —ﬁ„ 0

    // ›ﬂ «·—»ÿ («Œ Ì«—Ì Ê·ﬂ‰Â „„«—”… ÃÌœ…)
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // --- 8. Õ·ﬁ… «·—”„ (Render Loop) ---
    while (!glfwWindowShouldClose(window))
    {
        // √. „⁄«·Ã… «·„œŒ·« 
        processInput(window);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        // ». «· ‰ŸÌ› (·Ê‰ «·Œ·›Ì…)
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // ·Ê‰  —ﬂÊ«“Ì €«„ﬁ
        glClear(GL_COLOR_BUFFER_BIT);

        // Ã. «·—”„
        glUseProgram(shaderProgram); //  ›⁄Ì· «·‘Ìœ—
        glBindVertexArray(VAO); //  ›⁄Ì· ﬂ«∆‰ «·„À·À
        glDrawArrays(GL_TRIANGLES, 0, 3); // «—”„ „À·À« „‰ 3 —ƒÊ”
        // glBindVertexArray(0); // ·« œ«⁄Ì ·›ﬂ «·—»ÿ ›Ì ﬂ· ›—Ì„

        // œ.  »œÌ· «·‹ Buffers Ê„⁄«·Ã… «·√Õœ«À
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // --- 9. «· ‰ŸÌ› «·‰Â«∆Ì ---
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}