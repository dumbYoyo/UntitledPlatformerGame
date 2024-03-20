#pragma once

inline const unsigned int WINDOW_WIDTH = 1280;
inline const unsigned int WINDOW_HEIGHT = 720;
inline const float BOX2D_RENDERER_VIEWPORT_WIDTH = 1280.f;
inline const float BOX2D_RENDERER_VIEWPORT_HEIGHT = 720.f;
inline const float RENDERER_VIEWPORT_WIDTH = 1280.f;
inline const float RENDERER_VIEWPORT_HEIGHT = 720.f;
inline const float BOX2D_RENDERER_SCALE_X = 100.f;
inline const float BOX2D_RENDERER_SCALE_Y = 100.f;
inline const float BOX2D_METERS_PER_PIXEL_X = (BOX2D_RENDERER_VIEWPORT_WIDTH / BOX2D_RENDERER_SCALE_X) / (float)WINDOW_WIDTH;
inline const float BOX2D_METERS_PER_PIXEL_Y = (BOX2D_RENDERER_VIEWPORT_HEIGHT / BOX2D_RENDERER_SCALE_Y) / (float)WINDOW_HEIGHT;
