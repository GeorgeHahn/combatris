#include "game/tetromino_sprite.h"

#include <unordered_map>

namespace {

enum { GetRow = 1, GetCol = 0 };
using Angle = Tetromino::Angle;
using Rotation = TetrominoSprite::Rotation;

const std::unordered_map<Tetromino::Angle, const std::unordered_map<Tetromino::Angle, int>> kStates = {
  { Angle::A0, { { Angle::A90, 0 }, { Angle::A270, 7 } } },
  { Angle::A90, { { Angle::A180, 2 }, { Angle::A0, 1 } } },
  { Angle::A180, { { Angle::A270, 4 }, { Angle::A90, 3 } } },
  { Angle::A270, { { Angle::A0, 6 }, { Angle::A180 , 5 } } }
};

inline const std::vector<std::vector<int>>& GetWallKickData(Tetromino::Type type, Tetromino::Angle from_angle, Tetromino::Angle to_angle) {
  int state = kStates.at(from_angle).at(to_angle);

  std::cout << "State: " << state << std::endl;

  return (type == Tetromino::Type::I) ? kWallKickDataForI[state] : kWallKickDataForJLSTZ[state];
}

Tetromino::Angle GetNextAngle(Tetromino::Angle current_angle, Rotation rotate) {
  int angle = static_cast<int>(current_angle);

  if (rotate == Rotation::Clockwise) {
    angle++;
    if (angle > static_cast<int>(Tetromino::Angle::A270)) {
      angle = 0;
    }
  } else {
    angle--;
    if (angle < 0) {
      angle =  static_cast<int>(Tetromino::Angle::A270);
    }
  }
  return static_cast<Tetromino::Angle>(angle);
}

inline int ReverseSign(int value) { return value * -1; }

}

std::tuple<bool, Position, Tetromino::Angle> TetrominoSprite::TryRotation(Tetromino::Type type, const Position& current_pos, Tetromino::Angle current_angle, Rotation rotate) {
  auto try_angle = GetNextAngle(current_angle, rotate);
  const auto& wallkick_data = GetWallKickData(type, current_angle, try_angle);

  for (const auto& col_row : wallkick_data) {
    Position try_pos(current_pos.row() + ReverseSign(col_row[GetRow]), current_pos.col() + col_row[GetCol]);

    if (matrix_->IsValid(try_pos, tetromino_.GetRotationData(try_angle))) {
      return std::make_tuple(true, try_pos, try_angle);
    }
  }
  std::cout << "Failed" << std::endl;
  return std::make_tuple(false, current_pos, current_angle);
}

void TetrominoSprite::RotateClockwise() {
  bool success;

  std::tie(success, pos_, angle_) = TryRotation(tetromino_.type(), pos_, angle_, Rotation::Clockwise);

  if (success) {
    rotation_data_ = tetromino_.GetRotationData(angle_);
    matrix_->Insert(pos_, rotation_data_);
  }
}

void TetrominoSprite::RotateCounterClockwise() {
  bool success;

  std::tie(success, pos_, angle_) = TryRotation(tetromino_.type(), pos_, angle_, Rotation::CounterClockwise);

  if (success) {
    rotation_data_ = tetromino_.GetRotationData(angle_);
    matrix_->Insert(pos_, rotation_data_);
  }
}

void TetrominoSprite::HardDrop() {
  pos_ = matrix_->GetDropPosition(pos_, rotation_data_);
  level_.Release();
  floor_reached_ = true;
}

void TetrominoSprite::Left() {
  if (matrix_->IsValid(Position(pos_.row(), pos_.col() - 1), rotation_data_)) {
    pos_.dec_col();
    matrix_->Insert(pos_, rotation_data_);
  }
}

void TetrominoSprite::Right() {
  if (matrix_->IsValid(Position(pos_.row(), pos_.col() + 1), rotation_data_)) {
    pos_.inc_col();
    matrix_->Insert(pos_, rotation_data_);
  }
}

std::pair<bool, Matrix::Lines> TetrominoSprite::Down(double delta_time) {
  Matrix::Lines cleared_lines;
  bool next_piece = false;

  if (level_.Wait(delta_time, floor_reached_)) {
    if (floor_reached_) {
      cleared_lines = matrix_->Commit(pos_, rotation_data_);
      next_piece = true;
    } else {
      if (matrix_->IsValid(Position(pos_.row() + 1, pos_.col()), rotation_data_)) {
        pos_.inc_row();
        matrix_->Insert(pos_, rotation_data_);
      } else {
        floor_reached_ = true;
        can_move_ = (pos_.row() + 1 > kVisibleRowStart);
      }
    }
  }
  return std::make_pair(next_piece, cleared_lines);
}
