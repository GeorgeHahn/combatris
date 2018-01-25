#pragma once

#include <vector>

// 0 = spawn state
// R = state resulting from a clockwise rotation ("right") from spawn
// L = state resulting from a counter-clockwise ("left") rotation from spawn
// 2 = state resulting from 2 successive rotations in either direction from spawn.
//
// The kick-values are represented as (col, row) and assumes the rows goes from
// 22 to 0 while in my implementation rows goes from 0 -> 22, I therefore adjust
// the row values by reversing the sign

// J, L, S, T, Z Tetromino Wall Kick Data
const std::vector<std::vector<std::vector<int>>> kWallKickDataForJLSTZ = {
    {{0, 0}, {-1, 0}, {-1, +1}, {0, -2}, {-1, -2}}, // 0->R S0
    {{0, 0}, {+1, 0}, {+1, -1}, {0, +2}, {+1, +2}}, // R->0 S1
    {{0, 0}, {+1, 0}, {+1, -1}, {0, +2}, {+1, +2}}, // R->2 S2
    {{0, 0}, {-1, 0}, {-1, +1}, {0, -2}, {-1, -2}}, // 2->R S3
    {{0, 0}, {+1, 0}, {+1, +1}, {0, -2}, {+1, -2}}, // 2->L S4
    {{0, 0}, {-1, 0}, {-1, -1}, {0, +2}, {-1, +2}}, // L->2 S5
    {{0, 0}, {-1, 0}, {-1, -1}, {0, +2}, {-1, +2}}, // L->0 S6
    {{0, 0}, {+1, 0}, {+1, +1}, {0, -2}, {+1, -2}}  // 0->L S7
};

// I Tetromino Wall Kick Data
const std::vector<std::vector<std::vector<int>>> kWallKickDataForI = {
    {{0, 0}, {-2, 0}, {+1, 0}, {-2, -1}, {+1, +2}}, // 0->R S0
    {{0, 0}, {+2, 0}, {-1, 0}, {+2, +1}, {-1, -2}}, // R->0 S1
    {{0, 0}, {-1, 0}, {+2, 0}, {-1, +2}, {+2, -1}}, // R->2 S2
    {{0, 0}, {+1, 0}, {-2, 0}, {+1, -2}, {-2, +1}}, // 2->R S3
    {{0, 0}, {+2, 0}, {-1, 0}, {+2, +1}, {-1, -2}}, // 2->L S4
    {{0, 0}, {-2, 0}, {+1, 0}, {-2, -1}, {+1, +2}}, // L->2 S5
    {{0, 0}, {+1, 0}, {-2, 0}, {+1, -2}, {-2, +1}}, // L->0 S6
    {{0, 0}, {-1, 0}, {+2, 0}, {-1, +2}, {+2, -1}}  // 0->L S7
};

struct TetrominoRotationData {
  explicit TetrominoRotationData(const std::vector<std::vector<int>> &shape) : shape_(shape) {}

  std::vector<std::vector<int>> shape_;
};

// I Tetromino 1

const TetrominoRotationData kTetrominoRotationShape_I_0D({
    {0, 0, 0, 0},
    {1, 1, 1, 1},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
  });

const TetrominoRotationData kTetrominoRotationShape_I_90D({
    {0, 0, 1, 0},
    {0, 0, 1, 0},
    {0, 0, 1, 0},
    {0, 0, 1, 0}
  });

const TetrominoRotationData kTetrominoRotationShape_I_180D({
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {1, 1, 1, 1},
    {0, 0, 0, 0}
  });

const TetrominoRotationData kTetrominoRotationShape_I_270D({
    {0, 1, 0, 0},
    {0, 1, 0, 0},
    {0, 1, 0, 0},
    {0, 1, 0, 0}
  });

const std::vector<TetrominoRotationData> kTetromino_I_Rotations = {
  kTetrominoRotationShape_I_0D,
  kTetrominoRotationShape_I_90D,
  kTetrominoRotationShape_I_180D,
  kTetrominoRotationShape_I_270D
};

// J Tetromino 2

const TetrominoRotationData kTetrominoRotationShape_J_0D({
    {2, 0, 0},
    {2, 2, 2},
    {0, 0, 0}
  });

const TetrominoRotationData kTetrominoRotationShape_J_90D({
    {0, 2, 2},
    {0, 2, 0},
    {0, 2, 0}
  });

const TetrominoRotationData kTetrominoRotationShape_J_180D({
    {0, 0, 0},
    {2, 2, 2},
    {0, 0, 2}
  });

const TetrominoRotationData kTetrominoRotationShape_J_270D({
    {0, 2, 0},
    {0, 2, 0},
    {2, 2, 0}
  });

const std::vector<TetrominoRotationData> kTetromino_J_Rotations = {
  kTetrominoRotationShape_J_0D,
  kTetrominoRotationShape_J_90D,
  kTetrominoRotationShape_J_180D,
  kTetrominoRotationShape_J_270D
};

// L Tetromino 3

const TetrominoRotationData kTetrominoRotationShape_L_0D({
    {0, 0, 3},
    {3, 3, 3},
    {0, 0, 0}
  });

const TetrominoRotationData kTetrominoRotationShape_L_90D({
    {0, 3, 0},
    {0, 3, 0},
    {0, 3, 3}
  });

const TetrominoRotationData kTetrominoRotationShape_L_180D({
    {0, 0, 0},
    {3, 3, 3},
    {3, 0, 0}
  });

const TetrominoRotationData kTetrominoRotationShape_L_270D({
    {3, 3, 0},
    {0, 3, 0},
    {0, 3, 0}
  });

const std::vector<TetrominoRotationData> kTetromino_L_Rotations = {
  kTetrominoRotationShape_L_0D,
  kTetrominoRotationShape_L_90D,
  kTetrominoRotationShape_L_180D,
  kTetrominoRotationShape_L_270D
};

// O Tetromino 4

const TetrominoRotationData kTetrominoRotationShape_O({
    {0, 4, 4, 0},
    {0, 4, 4, 0},
    {0, 0, 0, 0}
  });

const std::vector<TetrominoRotationData> kTetromino_O_Rotations = {
  kTetrominoRotationShape_O,
  kTetrominoRotationShape_O,
  kTetrominoRotationShape_O,
  kTetrominoRotationShape_O
};

// S Tetromino 5

const TetrominoRotationData kTetrominoRotationShape_S_0D({
    {0, 5, 5},
    {5, 5, 0},
    {0, 0, 0}
  });

const TetrominoRotationData kTetrominoRotationShape_S_90D({
    {0, 5, 0},
    {0, 5, 5},
    {0, 0, 5}
  });

const TetrominoRotationData kTetrominoRotationShape_S_180D({
    {0, 0, 0},
    {0, 5, 5},
    {5, 5, 0}
  });

const TetrominoRotationData kTetrominoRotationShape_S_270D({
    {5, 0, 0},
    {5, 5, 0},
    {0, 5, 0}
  });

const std::vector<TetrominoRotationData> kTetromino_S_Rotations = {
  kTetrominoRotationShape_S_0D,
  kTetrominoRotationShape_S_90D,
  kTetrominoRotationShape_S_180D,
  kTetrominoRotationShape_S_270D
};

// T Tetromino 6

const TetrominoRotationData kTetrominoRotationShape_T_0D({
    {0, 6, 0},
    {6, 6, 6},
    {0, 0, 0}
  });

const TetrominoRotationData kTetrominoRotationShape_T_90D({
    {0, 6, 0},
    {0, 6, 6},
    {0, 6, 0}
  });

const TetrominoRotationData kTetrominoRotationShape_T_180D({
    {0, 0, 0},
    {6, 6, 6},
    {0, 6, 0}
  });

const TetrominoRotationData kTetrominoRotationShape_T_270D({
    {0, 6, 0},
    {6, 6, 0},
    {0, 6, 0}
  });

const std::vector<TetrominoRotationData> kTetromino_T_Rotations = {
  kTetrominoRotationShape_T_0D,
  kTetrominoRotationShape_T_90D,
  kTetrominoRotationShape_T_180D,
  kTetrominoRotationShape_T_270D
};

// Z Tetromino 7

const TetrominoRotationData kTetrominoRotationShape_Z_0D({
    {7, 7, 0},
    {0, 7, 7},
    {0, 0, 0}
  });

const TetrominoRotationData kTetrominoRotationShape_Z_90D({
    {0, 0, 7},
    {0, 7, 7},
    {0, 7, 0}
  });

const TetrominoRotationData kTetrominoRotationShape_Z_180D({
    {0, 0, 0},
    {7, 7, 0},
    {0, 7, 7}
  });

const TetrominoRotationData kTetrominoRotationShape_Z_270D({
    {0, 7, 0},
    {7, 7, 0},
    {7, 0, 0}
  });

const std::vector<TetrominoRotationData> kTetromino_Z_Rotations = {
  kTetrominoRotationShape_Z_0D,
  kTetrominoRotationShape_Z_90D,
  kTetrominoRotationShape_Z_180D,
  kTetrominoRotationShape_Z_270D
};
