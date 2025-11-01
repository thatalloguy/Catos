#define ENABLE_REFLECTION 1
#include "catos/reflection.h"
#include "catos/game.h"
#include "core/platform.h"

#include "core/entry_point.h"

#include <direct.h>

#include "renderer/renderPipeline.h"


std::string loadTextFromFile(const catos::string& path) {
    std::ifstream in(path.c_str(), std::ios::binary);
    std::ostringstream stringStream;

    // Check if file opened
    if (!in.is_open())
    {
        // Handle error
        spdlog::error("Unable to open file");
        return "";
    }

    // Read file
    stringStream << in.rdbuf();

    // Copy string stream to string
    std::string fileData = stringStream.str();

    // Close file
    in.close();
    return fileData;
}
float cube_vertices[288] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
    };


int main() {


    catos::Renderer& renderer = catos::Renderer::getInstance();
    catos::Window window{};


    if (!window.initialize({.size = {1280, 720}})) {
        spdlog::error("HELP");
    }


    renderer.init({
        catos::RenderBackendType::OPENGL_4_2
    });



    catos::RenderPipeline defaultPipeline{};

    ///--------- Pass creation
    catos::Shader colorShader{};
    colorShader.init({
        loadTextFromFile("../../../Assets/Shaders/color.vert").c_str(),
        loadTextFromFile("../../../Assets/Shaders/color.frag").c_str(),
    });

    catos::RenderPass colorPass{
        catos::RenderPassCreationInfo{
            true,
            {1280, 720},
            false,
            catos::COLOR,
            catos::RGB,
            catos::IMG_2D,
            0,
            nullptr,
            "color",
            nullptr
        },
        colorShader
    };

    defaultPipeline.setBeginPass(colorPass);
    ///------------------ Mesh creation.

    catos::Mesh cube_mesh{};
    cube_mesh.init(catos::MeshCreationInfo{
        cube_vertices,
        nullptr,
        sizeof(cube_vertices),
        0,
        288
    });

    Matrix4 transform{};
    transform.translate({0, 0, -10});
    transform.scale({1, 1, 1});

    cube_mesh.transform = transform.value_ptr();
    defaultPipeline.addMesh(cube_mesh);

    ////------------- Camera
    Matrix4 proj = perspective(toRadians(90.0f), 1280 / 720, 0.1f, 1000.0f);
    Matrix4 view{};
    view.translate({0, 0, 5});

    Matrix4 camera = proj * view;

    // Timer
    Timer frame_timer{};
    float offset = 70.0f;
    ///------------- Render loop
    while (!window.should_window_close()) {
        float delta_time = frame_timer.elapsed() * 10;
        frame_timer.reset();


        offset += 1 * delta_time;
        transform.rotate(offset, {0, 1,0 });
        transform.rotate(offset, {1, 1, 0 });

        window.update();
        defaultPipeline.draw(camera);


        renderer.renderPassToScreen(colorPass);
    }

    return 0;
}

