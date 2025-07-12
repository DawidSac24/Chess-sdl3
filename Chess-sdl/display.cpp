#include "display.h"

#include "square.h"

display* display::instance_ = nullptr;

display* display::get_instance()
{
	if (instance_ == nullptr) {
		instance_ = new display();
	}
	return instance_;
}

display::display()
{
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
	}

	if (!SDL_CreateWindowAndRenderer("Hello SDL", width_, height_, SDL_WINDOW_RESIZABLE, &window_, &renderer_)) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window and renderer: %s", SDL_GetError());
	}

	// Check that the display was successfully created
	if (window_ == nullptr)
	{
		// In the case that the display could not be made...
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create display: %s\n", SDL_GetError());
	}
}

display::~display()
{
	// Close and destroy the Renderer and display
	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);

	// Clean up
	SDL_Quit();
}

SDL_Renderer* display::get_renderer() const
{
	return renderer_;
}

SDL_Texture* display::load_texture(const char* path) const
{
	SDL_Surface* surface = IMG_Load(path);
	if (!surface) {
		SDL_Log("Failed to load image");
		return nullptr;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer_, surface);
	SDL_DestroySurface(surface);

	if (!texture) {
		SDL_Log("Failed to create texture: %s", SDL_GetError());
	}

	return texture;
}

