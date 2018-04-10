#include "game/tetromino_sprite.h"

#include <unordered_map>

namespace {

const int kResetsAllowed = 15;

using Angle = Tetromino::Angle;
using Rotation = TetrominoSprite::Rotation;

const std::unordered_map<Tetromino::Angle, const std::unordered_map<Tetromino::Angle, int>> kStates = {
  { Angle::A0, { { Angle::A90, 0 }, { Angle::A270, 7 } } },
  { Angle::A90, { { Angle::A180, 2 }, { Angle::A0, 1 } } },
  { Angle::A180, { { Angle::A270, 4 }, { Angle::A90, 3 } } },
  { Angle::A270, { { Angle::A0, 6 }, { Angle::A180 , 5 } } }
};

inline const std::vector<std::vector<int>>& GetWallKickData(Tetromino::Type type, Tetromino::Angle from_angle, Tetromino::Angle to_angle) {
  auto state = kStates.at(from_angle).at(to_angle);

  return (type == Tetromino::Type::I) ? kWallKickDataForI[state] : kWallKickDataForJLSTZ[state];
}

Tetromino::Angle GetNextAngle(Tetromino::Angle current_angle, Rotation rotate) {
  auto angle= static_cast<int>(current_angle);

  angle += (rotate == Rotation::Clockwise) ? 1 : -1;
  if (angle > static_cast<int>(Tetromino::Angle::A270)) {
    angle = 0;
  } else if (angle < 0) {
    angle =  static_cast<int>(Tetromino::Angle::A270);
  }
  return static_cast<Tetromino::Angle>(angle);
}

} // namespace

void TetrominoSprite::ResetDelayCounter() {
  if (State::OnFloor == state_ && reset_delay_counter_ < kResetsAllowed) {
    ++reset_delay_counter_;
    level_->ResetTime();
  } else if (reset_delay_counter_ > 0) {
    ++reset_delay_counter_;
  }
}

std::tuple<bool, Position, Tetromino::Angle> TetrominoSprite::TryRotation(Tetromino::Type type, const Position& current_pos, Tetromino::Angle current_angle, Rotation rotate) {
  enum { GetX = 0, GetY = 1 };

  auto try_angle = GetNextAngle(current_angle, rotate);
  const auto& wallkick_data = GetWallKickData(type, current_angle, try_angle);

  for (const auto& offsets : wallkick_data) {
    Position try_pos(current_pos.row() + offsets[GetY], current_pos.col() + offsets[GetX]);

    if (matrix_->IsValid(try_pos, tetromino_.GetRotationData(try_angle))) {
      ResetDelayCounter();
      return std::make_tuple(true, try_pos, try_angle);
    }
  }
  return std::make_tuple(false, current_pos, current_angle);
}

void TetrominoSprite::RotateClockwise() {
  bool success;

  std::tie(success, pos_, angle_) = TryRotation(tetromino_.type(), pos_, angle_, Rotation::Clockwise);

  if (success) {
    rotation_data_ = tetromino_.GetRotationData(angle_);
    matrix_->Insert(pos_, rotation_data_);
    last_move_ = Tetromino::Move::Rotation;
  }
}

void TetrominoSprite::RotateCounterClockwise() {
  bool success;

  std::tie(success, pos_, angle_) = TryRotation(tetromino_.type(), pos_, angle_, Rotation::CounterClockwise);

  if (success) {
    rotation_data_ = tetromino_.GetRotationData(angle_);
    matrix_->Insert(pos_, rotation_data_);
    last_move_ = Tetromino::Move::Rotation;
  }
}

void TetrominoSprite::SoftDrop() {
  if (State::OnFloor == state_) {
    return;
  }
  if (pos_.row() >= kVisibleRowStart - 1) {
    events_.Push(Event::Type::ScoringData, 1);
  }
  level_->Release();
}

void TetrominoSprite::HardDrop() {
  if (State::OnFloor == state_) {
    return;
  }
  auto drop_row = pos_.row();

  pos_ = matrix_->GetDropPosition(pos_, rotation_data_);
  level_->Release();
  state_ = State::Commit;
  last_move_ = Tetromino::Move::Down;
  events_.Push(Event::Type::ScoringData, (kVisibleRows - drop_row) * 2);
}

void TetrominoSprite::Left() {
  if (matrix_->IsValid(Position(pos_.row(), pos_.col() - 1), rotation_data_)) {
    pos_.dec_col();
    matrix_->Insert(pos_, rotation_data_);
    last_move_ = Tetromino::Move::Left;
    ResetDelayCounter();
  }
}

void TetrominoSprite::Right() {
  if (matrix_->IsValid(Position(pos_.row(), pos_.col() + 1), rotation_data_)) {
    pos_.inc_col();
    matrix_->Insert(pos_, rotation_data_);
    last_move_ = Tetromino::Move::Right;
    ResetDelayCounter();
  }
}

TetrominoSprite::State TetrominoSprite::Down(double delta_time) {
  switch (state_) {
    case State::Falling:
      last_move_ = Tetromino::Move::Down;
      if (level_->WaitForMoveDown(delta_time)) {
        if (reset_delay_counter_ >= kResetsAllowed) {
          state_ = State::Commit;
        } else if (matrix_->IsValid(Position(pos_.row() + 1, pos_.col()), rotation_data_)) {
          pos_.inc_row();
          matrix_->Insert(pos_, rotation_data_);
          if (!matrix_->IsValid(Position(pos_.row() + 1, pos_.col()), rotation_data_)) {
            events_.Push(Event::Type::OnFloor, Events::QueueRule::NoDuplicates);
            state_ = State::OnFloor;
          }
        } else {
          events_.Push(Event::Type::OnFloor, Events::QueueRule::NoDuplicates);
          state_ = State::OnFloor;
        }
      }
      break;
    case State::OnFloor:
      if (level_->WaitForLockDelay(delta_time)) {
        state_ = State::Commit;
      } else if (matrix_->IsValid(Position(pos_.row() + 1, pos_.col()), rotation_data_)) {
        events_.Push(Event::Type::Falling, Events::QueueRule::NoDuplicates);
        state_ = State::Falling;
      }
      break;
    case State::Commit: {
        auto [lines_cleared, tspin_type, perfect_clear] = matrix_->Commit(tetromino_.type(), last_move_, pos_, rotation_data_);

        if (perfect_clear) {
          events_.Push(Event::Type::PerfectClear);
        }
        if (!lines_cleared.empty() || TSpinType::None != tspin_type) {
          events_.Push(Event::Type::ScoringData, lines_cleared, pos_, tspin_type);
        }
        state_ = State::Commited;
      }
      break;
    default:
      break;
  }
  return state_;
}
