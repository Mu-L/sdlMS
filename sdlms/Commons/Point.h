#pragma once

#include <SDL3/SDL.h>
#include <optional>

// 重载 SDL_Point 的加法运算符
SDL_FPoint operator+(const SDL_FPoint &m, const SDL_FPoint &n);
// 重载 SDL_Point 的减法运算符
SDL_FPoint operator-(const SDL_FPoint &m, const SDL_FPoint &n);

std::optional<SDL_FPoint> intersect(const SDL_FPoint &p1,
                                    const SDL_FPoint &p2,
                                    const SDL_FPoint &p3,
                                    const SDL_FPoint &p4);

float distance(const SDL_FPoint &m, const SDL_FPoint &n);