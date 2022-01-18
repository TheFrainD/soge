/*********************************************************************
 * animator.h                                                        *
 *                                                                   *
 * Copyright (c) 2022 Dmytro Zykov                                   *
 *                                                                   *
 * This file is a part of the vally project, and may only be used,   *
 * modified and distributed under the terms of the MIT License,      *
 * LICENSE.md. By continuing to use, modify and distribute this file *
 * you inidicate that you have read the license and accept it fully. *
 *********************************************************************/

#ifndef VALLY_ANIMATOR_H_
#define VALLY_ANIMATOR_H_

#include <vally/config.h>

#include <vally/renderer/texture.h>
#include <vally/ecs/ecs.h>

/**
 * @brief An animation struct.
 * 
 * Periodically switches texture cooridinates
 * according to framerate.
 * 
 */
typedef struct {
  texture *texture;
  vector2f tiling;
  u32 first_frame;
  u32 last_frame;
  f32 frametime;
} animation;

/**
 * @brief An animator struct.
 * 
 */
typedef struct {
  b8 playing;
  animation *animation;
  u32 current_frame;
  f32 time;
} animator;

/**
 * @brief Creates animation.
 *
 * @param texture texture for animation
 * @param tiling tiling of spritesheet
 * @param first_frame index of first frame of the animation in spritesheeet
 * @param last_frame index of last frame of the animation in spritesheeet
 * @param framerate frames per second
 *
 */
VALLY_API animation animation_create(texture *texture, vector2f tiling, u32 first_frame, u32 last_frame, u32 framerate);

/**
 * @brief Adds animator component to the enitity.
 *
 * @param entity entity
 *
 */
VALLY_API void ecs_animator_add(entity entity);

/**
 * @brief Plays certain animation.
 *
 * @param entity entity
 * @param animation animation to play
 *
 */
VALLY_API void ecs_animator_play(entity entity, animation *animation);

/**
 * @brief Stops playing any animation.
 *
 * @param entity
 *
 */
VALLY_API void ecs_animator_stop(entity entity);

void ecs_animator_update(f32 dt);

#endif // VALLY_ANIMATOR_H_
