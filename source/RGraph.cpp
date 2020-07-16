#include <RG/RGraph.h>
#include <RG/r_util.h>

using namespace rg;

RGraph RGraph::_Rgraph_instance;


bool RGraph::init(std::string win_name, glm::ivec2 win_size)
{
    auto instance = Instance();
    if (instance._is_initiated)
    {
        printf("Already Initiated RGraph");
        return false;
    }
    

    // Init SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf( "Failed to initiate SDL! SDL_Error: %s\n", SDL_GetError() );
        SDL_Quit();
        return false;
    }
    
    // Set window name and create window
    instance._win_name = win_name;
    instance._win_size = win_size;
    instance._window = SDL_CreateWindow(win_name.c_str(), 100, 100, instance._win_size.x,
                                        instance._win_size.y, SDL_WINDOW_SHOWN);
    
    // Show error message if failed to create window
    if (instance._window == nullptr)
    {
        printf("Failed to create Window! SDL_Error:\n%s", SDL_GetError());
        SDL_Quit();
        return false;
    }

    instance._renderer = SDL_CreateRenderer(instance._window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    // Show error message if failed to create renderer
    if (instance._renderer == nullptr)
    {
        printf("Failed to create Renderer! SDL_Error:\n%s", SDL_GetError());
        SDL_DestroyWindow(instance._window);
        SDL_Quit();
        return false;  
    }


    instance._is_initiated = true;

    return true;
}

RGraph::~RGraph()
{
    // Destroy renderer , Window and Shut down SDL
    SDL_DestroyRenderer(Instance()._renderer);
    SDL_DestroyWindow(Instance()._window);
    SDL_Quit();
}