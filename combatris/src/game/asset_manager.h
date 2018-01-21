#pragma once

#include "game/tetromino.h"
#include "game/constants.h"
#include "tools/function_caller.h"

#include <memory>
#include <exception>

#include <SDL_ttf.h>

enum Font { Normal, Bold, Small, Large };

class AssetManager final {
 public:
  explicit AssetManager(SDL_Renderer *renderer);

  AssetManager(const AssetManager&) = delete;

  virtual ~AssetManager() noexcept {};

  std::shared_ptr<const Tetromino> GetTetromino(Tetromino::Type type) const { return tetrominos_.at(static_cast<int>(type) - 1); }

  const std::vector<std::shared_ptr<const Tetromino>>& GetTetrominos() const { return tetrominos_; }

  SDL_Texture* GetBorderTexture() const { return border_texture_.get(); }

  virtual TTF_Font *GetFont(int id) const { return fonts_[id].get(); }

 private:
  using UniqueFontPtr = std::unique_ptr<TTF_Font, function_caller<void(TTF_Font*), &TTF_CloseFont>>;

  std::vector<UniqueFontPtr> fonts_;
  std::shared_ptr<SDL_Texture> border_texture_;
  std::vector<std::shared_ptr<const Tetromino>> tetrominos_;
};