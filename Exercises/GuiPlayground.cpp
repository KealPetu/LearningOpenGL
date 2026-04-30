//
// Created by Keal on 4/27/2026.
//

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Includes de tu motor
#include "WindowManager.hpp"
#include "VAO.hpp"
#include "VBO.hpp"
#include "EBO.hpp"
#include "Shader.hpp"
#include "Texture.hpp"

// Includes de ImGui
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

constexpr int SCREEN_WIDTH { 800 };
constexpr int SCREEN_HEIGHT { 600 };

int main() {
    WindowManager::initializeGLFW(3, 3);
    WindowManager wm;
    wm.initializeWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "ImGui Control Panel");

    const std::vector<GLfloat> VERTICES {
        -.5f, -.5f, 1.0, 0.0, 0.0,  0.0f, 1.0f,
        .5f, -.5f,  0.0, 1.0, 0.0,  1.0f, 1.0f,
        .5f, .5f,   0.0, 0.0, 1.0,  1.0f, 0.0f,
        -.5f, .5f,  1.0, 1.0, 1.0,  0.0f, 0.0f
   };

    constexpr int STRIDE { 7 * sizeof(GLfloat) };

    const std::vector<GLuint> INDICES {
        0, 1, 2,
        0, 2, 3
    };

    const VBO VBO(VERTICES.data(), static_cast<GLsizeiptr>(sizeof(GLfloat) * VERTICES.size()));
    const EBO EBO(INDICES.data(), static_cast<GLsizeiptr>(sizeof(GLuint) * INDICES.size()));
    VAO VAO;
    VAO.bind();
    EBO.bind();

    // Atribute 0: Position (2 floats)
    VAO.linkAttrib(VBO, 0, 2, GL_FLOAT, STRIDE, nullptr);
    // Atribute 1: Color (3 floats)
    VAO.linkAttrib(VBO, 1, 3, GL_FLOAT, STRIDE, reinterpret_cast<void*>(2 * sizeof(GLfloat)));
    // Atribute 2: Texture (2 floats)
    VAO.linkAttrib(VBO, 2, 2, GL_FLOAT, STRIDE, reinterpret_cast<void*>(5 * sizeof(GLfloat)));

    VAO::unbind();
    EBO::unbind();

    const Texture happyFace("./resources/textures/awesomeface.png", GL_TEXTURE_2D, GL_TEXTURE0);
    happyFace.setWrappingMode(GL_MIRRORED_REPEAT);
    happyFace.setFilteringMode(GL_LINEAR);

    const Shader SHADER("./resources/shaders/ProjectionShader.vert","./resources/shaders/ProjectionShader.frag");

    // ==========================================
    // 1. INICIALIZAR IMGUI
    // ==========================================
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark(); // Estilo visual del motor

    // Conectamos ImGui a tu ventana y a OpenGL 3.3
    ImGui_ImplGlfw_InitForOpenGL(wm.getWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 330 core");

    // --- VARIABLES DE CONTROL (Las que modificará ImGui) ---
    glm::vec2 posicion(400.0f, 300.0f); // Empezamos en el centro de la pantalla
    float rotacion = 0.0f;
    float velocidadRotacion = 0.0f;
    glm::vec2 escala (512.f, 512.f); // Asumiendo que tu caja normalizada mida 1x1, esto la hace de 100x100 píxeles
    bool vsyncEnabled = true;
    bool wireframeModeEnabled = false;
    // ==========================================
    // BUCLE PRINCIPAL
    // ==========================================
    GLfloat currentTime {0};
    GLfloat lastTime {0};

    while (!wm.windowShouldClose()) {
        // --- 2. PREPARAR EL FRAME DE IMGUI ---
        wm.toggleVsync(vsyncEnabled);
        currentTime = glfwGetTime();
        float deltaTime = currentTime - lastTime;
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // --- 3. DISEÑAR LA INTERFAZ ---
        ImGui::Begin("Inspector 2D"); // Crea una ventana flotante
        ImGui::Text("Propiedades del Objeto:");
        ImGui::SliderFloat2("Posicion (X, Y)", &posicion.x, 0.0f, static_cast<float>(wm.getWidth()), "%.0f");
        ImGui::SliderFloat("Rotacion", &rotacion, -360.f, 360.f, "%.2f");
        ImGui::SliderFloat("Velocidad de Rotacion", &velocidadRotacion, -360.f, 360.f, "%.2f");
        ImGui::SliderFloat2("Escala (X, Y)", &escala.x, 1.0f, static_cast<float>(wm.getWidth()), "%.2f");
        ImGui::Checkbox("Vsync", &vsyncEnabled);
        ImGui::Checkbox("Wireframe Mode", &wireframeModeEnabled);
        ImGui::TextDisabled("FPS: %.1f\nframe time: %.2f\nRotacion: %.2f rads", 1.f/deltaTime, deltaTime * 1000, rotacion);
        ImGui::End();

        // --- RENDERIZADO DE TU MOTOR (OpenGL) ---
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        SHADER.use();

        // APLICAR LAS MATRICES USANDO LAS VARIABLES DE IMGUI
        glm::mat4 projection {glm::ortho(
            0.0f, static_cast<float>(wm.getWidth()),
            static_cast<float>(wm.getHeight()), 0.0f,
            -1.0f, 1.0f)};

        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::translate(trans, glm::vec3(posicion.x, posicion.y, 0.0f));
        rotacion += velocidadRotacion * deltaTime;
        trans = glm::rotate(trans, glm::radians(rotacion), glm::vec3(0.0f, 0.0f, 1.0f)); // Convertimos grados a radianes
        trans = glm::scale(trans, glm::vec3(escala, 1.0f));

        SHADER.setMat4("projection", projection);
        SHADER.setMat4("transform", trans);

        wireframeModeEnabled ? glPolygonMode(GL_FRONT_AND_BACK, GL_LINE) : glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        // ... (Dibujar tu VAO con glDrawElements) ...
        VAO.bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        VAO.unbind();

        // --- 4. RENDERIZAR IMGUI SOBRE TU JUEGO ---
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        wm.endDrawing();
        lastTime = currentTime;
    }

    // ==========================================
    // 5. LIMPIEZA DE IMGUI
    // ==========================================
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    return 0;
}
