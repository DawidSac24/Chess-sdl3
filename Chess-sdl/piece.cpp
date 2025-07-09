#include "piece.h"

piece::piece(const color color, const int value) :
	color_(color), value_(value)
{
}

SDL_Texture* piece::get_texture()
{
	if (texture_ == nullptr)
	{
		if (texture_path_ == nullptr)
		{
			SDL_LogError(SDL_LOG_CATEGORY_ERROR, "texture path must be assigned before rendering the texture\n");
			throw std::exception("texture path must be assigned before rendering the texture");
		}

		texture_ = display_->load_texture(texture_path_);

		if (texture_ == nullptr)
		{
			SDL_LogError(SDL_LOG_CATEGORY_ERROR, "loading texture failed for: %s", this->to_string());
		}
	}
	return texture_;
}
