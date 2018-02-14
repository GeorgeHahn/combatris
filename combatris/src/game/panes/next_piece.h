#pragma once

#include "game/tetromino_generator.h"
#include "game/panes/pane.h"

class NextPiece final : public TextPane {
 public:
  NextPiece(SDL_Renderer* renderer, const std::shared_ptr<TetrominoGenerator>& tetromino_generator, const std::shared_ptr<Assets>& assets)
      : TextPane(renderer,  kMatrixEndX + kBlockWidth + 8,
                 kMatrixStartY - kBlockHeight, "NEXT", assets), tetromino_generator_(tetromino_generator) {
    SetCaptionOrientation(TextPane::Orientation::Left);
  }

  void Show() { hide_pieces_ = false; }

  void Hide() { hide_pieces_ = true; }

  virtual void Render(double delta_time) override {
    TextPane::Render(delta_time);
    if (hide_pieces_) {
      return;
    }
    tetromino_generator_->RenderFromQueue(0, x_ + 10, y_ + caption_height_ + 15);

    for (size_t i = 1; i < 3; ++i) {
      tetromino_generator_->RenderFromQueue(i, x_ + 10, y_ + caption_height_ + 15 + (90 * i));
    }
  }

  virtual void Reset() override {}

 private:
  bool hide_pieces_ = true;
  std::shared_ptr<TetrominoGenerator> tetromino_generator_;
};
