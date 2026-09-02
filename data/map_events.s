#include "constants/event_bg.h"
#include "constants/event_object_movement.h"
#include "constants/event_objects.h"
#include "constants/flags.h"
#include "constants/items.h"
#include "constants/map_scripts.h"
#include "constants/layouts.h"
#include "constants/maps.h"
#include "constants/trainer_types.h"
#include "constants/vars.h"
#include "constants/weather.h"
@ ===== BEGIN asm/macros.inc =====
@ ===== BEGIN asm/macros/asm.inc =====
	.ifndef GUARD_ASM_MACROS_ASM_INC
	.set GUARD_ASM_MACROS_ASM_INC, 1

	.macro inc x
	.set \x, \x + 1
	.endm

	.macro enum_start x=0
	.set __enum__, \x
	.endm

	.macro enum constant
	.equiv \constant, __enum__
	inc __enum__
	.endm

	.endif @ GUARD_ASM_MACROS_ASM_INC
@ ===== END asm/macros/asm.inc =====
@ ===== BEGIN asm/macros/function.inc =====
	.macro arm_func_start name
	.align 2, 0
	.global \name
	.arm
	.type \name, function
	.endm

	.macro arm_func_end name
	.size \name, .-\name
	.endm

	.macro thumb_func_start name
	.align 2, 0
	.global \name
	.thumb
	.thumb_func
	.type \name, function
	.endm

	.macro non_word_aligned_thumb_func_start name
	.global \name
	.thumb
	.thumb_func
	.type \name, function
	.endm

	.macro thumb_func_end name
	.size \name, .-\name
	.endm
@ ===== END asm/macros/function.inc =====
@ ===== BEGIN asm/macros/movement.inc =====
	.macro create_movement_action name:req, value:req
	.macro \name
	.byte \value
	.endm
	.endm

	create_movement_action face_down, MOVEMENT_ACTION_FACE_DOWN
	create_movement_action face_up, MOVEMENT_ACTION_FACE_UP
	create_movement_action face_left, MOVEMENT_ACTION_FACE_LEFT
	create_movement_action face_right, MOVEMENT_ACTION_FACE_RIGHT
	create_movement_action face_down_fast, MOVEMENT_ACTION_FACE_DOWN_FAST
	create_movement_action face_up_fast, MOVEMENT_ACTION_FACE_UP_FAST
	create_movement_action face_left_fast, MOVEMENT_ACTION_FACE_LEFT_FAST
	create_movement_action face_right_fast, MOVEMENT_ACTION_FACE_RIGHT_FAST
	create_movement_action walk_slower_down, MOVEMENT_ACTION_WALK_SLOWER_DOWN
	create_movement_action walk_slower_up, MOVEMENT_ACTION_WALK_SLOWER_UP
	create_movement_action walk_slower_left, MOVEMENT_ACTION_WALK_SLOWER_LEFT
	create_movement_action walk_slower_right, MOVEMENT_ACTION_WALK_SLOWER_RIGHT
	create_movement_action walk_slow_down, MOVEMENT_ACTION_WALK_SLOW_DOWN
	create_movement_action walk_slow_up, MOVEMENT_ACTION_WALK_SLOW_UP
	create_movement_action walk_slow_left, MOVEMENT_ACTION_WALK_SLOW_LEFT
	create_movement_action walk_slow_right, MOVEMENT_ACTION_WALK_SLOW_RIGHT
	create_movement_action walk_down, MOVEMENT_ACTION_WALK_NORMAL_DOWN
	create_movement_action walk_up, MOVEMENT_ACTION_WALK_NORMAL_UP
	create_movement_action walk_left, MOVEMENT_ACTION_WALK_NORMAL_LEFT
	create_movement_action walk_right, MOVEMENT_ACTION_WALK_NORMAL_RIGHT
	create_movement_action jump_2_down, MOVEMENT_ACTION_JUMP_2_DOWN
	create_movement_action jump_2_up, MOVEMENT_ACTION_JUMP_2_UP
	create_movement_action jump_2_left, MOVEMENT_ACTION_JUMP_2_LEFT
	create_movement_action jump_2_right, MOVEMENT_ACTION_JUMP_2_RIGHT
	create_movement_action delay_1, MOVEMENT_ACTION_DELAY_1
	create_movement_action delay_2, MOVEMENT_ACTION_DELAY_2
	create_movement_action delay_4, MOVEMENT_ACTION_DELAY_4
	create_movement_action delay_8, MOVEMENT_ACTION_DELAY_8
	create_movement_action delay_16, MOVEMENT_ACTION_DELAY_16
	create_movement_action walk_fast_down, MOVEMENT_ACTION_WALK_FAST_DOWN
	create_movement_action walk_fast_up, MOVEMENT_ACTION_WALK_FAST_UP
	create_movement_action walk_fast_left, MOVEMENT_ACTION_WALK_FAST_LEFT
	create_movement_action walk_fast_right, MOVEMENT_ACTION_WALK_FAST_RIGHT
	create_movement_action walk_in_place_slow_down, MOVEMENT_ACTION_WALK_IN_PLACE_SLOW_DOWN
	create_movement_action walk_in_place_slow_up, MOVEMENT_ACTION_WALK_IN_PLACE_SLOW_UP
	create_movement_action walk_in_place_slow_left, MOVEMENT_ACTION_WALK_IN_PLACE_SLOW_LEFT
	create_movement_action walk_in_place_slow_right, MOVEMENT_ACTION_WALK_IN_PLACE_SLOW_RIGHT
	create_movement_action walk_in_place_down, MOVEMENT_ACTION_WALK_IN_PLACE_NORMAL_DOWN
	create_movement_action walk_in_place_up, MOVEMENT_ACTION_WALK_IN_PLACE_NORMAL_UP
	create_movement_action walk_in_place_left, MOVEMENT_ACTION_WALK_IN_PLACE_NORMAL_LEFT
	create_movement_action walk_in_place_right, MOVEMENT_ACTION_WALK_IN_PLACE_NORMAL_RIGHT
	create_movement_action walk_in_place_fast_down, MOVEMENT_ACTION_WALK_IN_PLACE_FAST_DOWN
	create_movement_action walk_in_place_fast_up, MOVEMENT_ACTION_WALK_IN_PLACE_FAST_UP
	create_movement_action walk_in_place_fast_left, MOVEMENT_ACTION_WALK_IN_PLACE_FAST_LEFT
	create_movement_action walk_in_place_fast_right, MOVEMENT_ACTION_WALK_IN_PLACE_FAST_RIGHT
	create_movement_action walk_in_place_faster_down, MOVEMENT_ACTION_WALK_IN_PLACE_FASTER_DOWN
	create_movement_action walk_in_place_faster_up, MOVEMENT_ACTION_WALK_IN_PLACE_FASTER_UP
	create_movement_action walk_in_place_faster_left, MOVEMENT_ACTION_WALK_IN_PLACE_FASTER_LEFT
	create_movement_action walk_in_place_faster_right, MOVEMENT_ACTION_WALK_IN_PLACE_FASTER_RIGHT
	create_movement_action ride_water_current_down, MOVEMENT_ACTION_RIDE_WATER_CURRENT_DOWN
	create_movement_action ride_water_current_up, MOVEMENT_ACTION_RIDE_WATER_CURRENT_UP
	create_movement_action ride_water_current_lefft, MOVEMENT_ACTION_RIDE_WATER_CURRENT_LEFT
	create_movement_action ride_water_current_right, MOVEMENT_ACTION_RIDE_WATER_CURRENT_RIGHT
	create_movement_action walk_faster_down, MOVEMENT_ACTION_WALK_FASTER_DOWN
	create_movement_action walk_faster_up, MOVEMENT_ACTION_WALK_FASTER_UP
	create_movement_action walk_faster_left, MOVEMENT_ACTION_WALK_FASTER_LEFT
	create_movement_action walk_faster_right, MOVEMENT_ACTION_WALK_FASTER_RIGHT
	create_movement_action slide_down, MOVEMENT_ACTION_SLIDE_DOWN
	create_movement_action slide_up, MOVEMENT_ACTION_SLIDE_UP
	create_movement_action slide_left, MOVEMENT_ACTION_SLIDE_LEFT
	create_movement_action slide_right, MOVEMENT_ACTION_SLIDE_RIGHT
	create_movement_action player_run_down, MOVEMENT_ACTION_PLAYER_RUN_DOWN
	create_movement_action player_run_up, MOVEMENT_ACTION_PLAYER_RUN_UP
	create_movement_action player_run_left, MOVEMENT_ACTION_PLAYER_RUN_LEFT
	create_movement_action player_run_right, MOVEMENT_ACTION_PLAYER_RUN_RIGHT
	create_movement_action player_run_down_slow, MOVEMENT_ACTION_PLAYER_RUN_DOWN_SLOW
	create_movement_action player_run_up_slow, MOVEMENT_ACTION_PLAYER_RUN_UP_SLOW
	create_movement_action player_run_left_slow, MOVEMENT_ACTION_PLAYER_RUN_LEFT_SLOW
	create_movement_action player_run_right_slow, MOVEMENT_ACTION_PLAYER_RUN_RIGHT_SLOW
	create_movement_action start_anim_in_direction, MOVEMENT_ACTION_START_ANIM_IN_DIRECTION
	create_movement_action jump_special_down, MOVEMENT_ACTION_JUMP_SPECIAL_DOWN
	create_movement_action jump_special_up, MOVEMENT_ACTION_JUMP_SPECIAL_UP
	create_movement_action jump_special_left, MOVEMENT_ACTION_JUMP_SPECIAL_LEFT
	create_movement_action jump_special_right, MOVEMENT_ACTION_JUMP_SPECIAL_RIGHT
	create_movement_action face_player, MOVEMENT_ACTION_FACE_PLAYER
	create_movement_action face_away_player, MOVEMENT_ACTION_FACE_AWAY_PLAYER
	create_movement_action lock_facing_direction, MOVEMENT_ACTION_LOCK_FACING_DIRECTION
	create_movement_action unlock_facing_direction, MOVEMENT_ACTION_UNLOCK_FACING_DIRECTION
	create_movement_action jump_down, MOVEMENT_ACTION_JUMP_DOWN
	create_movement_action jump_up, MOVEMENT_ACTION_JUMP_UP
	create_movement_action jump_left, MOVEMENT_ACTION_JUMP_LEFT
	create_movement_action jump_right, MOVEMENT_ACTION_JUMP_RIGHT
	create_movement_action jump_in_place_down, MOVEMENT_ACTION_JUMP_IN_PLACE_DOWN
	create_movement_action jump_in_place_up, MOVEMENT_ACTION_JUMP_IN_PLACE_UP
	create_movement_action jump_in_place_left, MOVEMENT_ACTION_JUMP_IN_PLACE_LEFT
	create_movement_action jump_in_place_right, MOVEMENT_ACTION_JUMP_IN_PLACE_RIGHT
	create_movement_action jump_in_place_down_up, MOVEMENT_ACTION_JUMP_IN_PLACE_DOWN_UP
	create_movement_action jump_in_place_up_down, MOVEMENT_ACTION_JUMP_IN_PLACE_UP_DOWN
	create_movement_action jump_in_place_left_right, MOVEMENT_ACTION_JUMP_IN_PLACE_LEFT_RIGHT
	create_movement_action jump_in_place_right_left, MOVEMENT_ACTION_JUMP_IN_PLACE_RIGHT_LEFT
	create_movement_action face_original_direction, MOVEMENT_ACTION_FACE_ORIGINAL_DIRECTION
	create_movement_action nurse_joy_bow, MOVEMENT_ACTION_NURSE_JOY_BOW_DOWN
	create_movement_action enable_jump_landing_ground_effect, MOVEMENT_ACTION_ENABLE_JUMP_LANDING_GROUND_EFFECT
	create_movement_action disable_jump_landing_ground_effect, MOVEMENT_ACTION_DISABLE_JUMP_LANDING_GROUND_EFFECT
	create_movement_action disable_anim, MOVEMENT_ACTION_DISABLE_ANIMATION
	create_movement_action restore_anim, MOVEMENT_ACTION_RESTORE_ANIMATION
	create_movement_action set_invisible, MOVEMENT_ACTION_SET_INVISIBLE
	create_movement_action set_visible, MOVEMENT_ACTION_SET_VISIBLE
	create_movement_action emote_exclamation_mark, MOVEMENT_ACTION_EMOTE_EXCLAMATION_MARK
	create_movement_action emote_question_mark, MOVEMENT_ACTION_EMOTE_QUESTION_MARK
	create_movement_action emote_x, MOVEMENT_ACTION_EMOTE_X
	create_movement_action emote_double_exclamation_mark, MOVEMENT_ACTION_EMOTE_DOUBLE_EXCL_MARK
	create_movement_action emote_smile, MOVEMENT_ACTION_EMOTE_SMILE
	create_movement_action reveal_trainer, MOVEMENT_ACTION_REVEAL_TRAINER
	create_movement_action rock_smash_break, MOVEMENT_ACTION_ROCK_SMASH_BREAK
	create_movement_action cut_tree, MOVEMENT_ACTION_CUT_TREE
	create_movement_action set_fixed_priority, MOVEMENT_ACTION_SET_FIXED_PRIORITY
	create_movement_action clear_fixed_priority, MOVEMENT_ACTION_CLEAR_FIXED_PRIORITY
	create_movement_action init_affine_anim, MOVEMENT_ACTION_INIT_AFFINE_ANIM
	create_movement_action clear_affine_anim, MOVEMENT_ACTION_CLEAR_AFFINE_ANIM
	create_movement_action walk_down_start_affine, MOVEMENT_ACTION_WALK_DOWN_START_AFFINE
	create_movement_action walk_down_affine, MOVEMENT_ACTION_WALK_DOWN_AFFINE
	create_movement_action acro_wheelie_face_down, MOVEMENT_ACTION_ACRO_WHEELIE_FACE_DOWN
	create_movement_action acro_wheelie_face_up, MOVEMENT_ACTION_ACRO_WHEELIE_FACE_UP
	create_movement_action acro_wheelie_face_left, MOVEMENT_ACTION_ACRO_WHEELIE_FACE_LEFT
	create_movement_action acro_wheelie_face_right, MOVEMENT_ACTION_ACRO_WHEELIE_FACE_RIGHT
	create_movement_action acro_pop_wheelie_down, MOVEMENT_ACTION_ACRO_POP_WHEELIE_DOWN
	create_movement_action acro_pop_wheelie_up, MOVEMENT_ACTION_ACRO_POP_WHEELIE_UP
	create_movement_action acro_pop_wheelie_left, MOVEMENT_ACTION_ACRO_POP_WHEELIE_LEFT
	create_movement_action acro_pop_wheelie_right, MOVEMENT_ACTION_ACRO_POP_WHEELIE_RIGHT
	create_movement_action acro_end_wheelie_face_down, MOVEMENT_ACTION_ACRO_END_WHEELIE_FACE_DOWN
	create_movement_action acro_end_wheelie_face_up, MOVEMENT_ACTION_ACRO_END_WHEELIE_FACE_UP
	create_movement_action acro_end_wheelie_face_left, MOVEMENT_ACTION_ACRO_END_WHEELIE_FACE_LEFT
	create_movement_action acro_end_wheelie_face_right, MOVEMENT_ACTION_ACRO_END_WHEELIE_FACE_RIGHT
	create_movement_action acro_wheelie_hop_face_down, MOVEMENT_ACTION_ACRO_WHEELIE_HOP_FACE_DOWN
	create_movement_action acro_wheelie_hop_face_up, MOVEMENT_ACTION_ACRO_WHEELIE_HOP_FACE_UP
	create_movement_action acro_wheelie_hop_face_left, MOVEMENT_ACTION_ACRO_WHEELIE_HOP_FACE_LEFT
	create_movement_action acro_wheelie_hop_face_right, MOVEMENT_ACTION_ACRO_WHEELIE_HOP_FACE_RIGHT
	create_movement_action acro_wheelie_hop_down, MOVEMENT_ACTION_ACRO_WHEELIE_HOP_DOWN
	create_movement_action acro_wheelie_hop_up, MOVEMENT_ACTION_ACRO_WHEELIE_HOP_UP
	create_movement_action acro_wheelie_hop_left, MOVEMENT_ACTION_ACRO_WHEELIE_HOP_LEFT
	create_movement_action acro_wheelie_hop_right, MOVEMENT_ACTION_ACRO_WHEELIE_HOP_RIGHT
	create_movement_action acro_wheelie_jump_down, MOVEMENT_ACTION_ACRO_WHEELIE_JUMP_DOWN
	create_movement_action acro_wheelie_jump_up, MOVEMENT_ACTION_ACRO_WHEELIE_JUMP_UP
	create_movement_action acro_wheelie_jump_left, MOVEMENT_ACTION_ACRO_WHEELIE_JUMP_LEFT
	create_movement_action acro_wheelie_jump_right, MOVEMENT_ACTION_ACRO_WHEELIE_JUMP_RIGHT
	create_movement_action acro_wheelie_in_place_down, MOVEMENT_ACTION_ACRO_WHEELIE_IN_PLACE_DOWN
	create_movement_action acro_wheelie_in_place_up, MOVEMENT_ACTION_ACRO_WHEELIE_IN_PLACE_UP
	create_movement_action acro_wheelie_in_place_left, MOVEMENT_ACTION_ACRO_WHEELIE_IN_PLACE_LEFT
	create_movement_action acro_wheelie_in_place_right, MOVEMENT_ACTION_ACRO_WHEELIE_IN_PLACE_RIGHT
	create_movement_action acro_pop_wheelie_move_down, MOVEMENT_ACTION_ACRO_POP_WHEELIE_MOVE_DOWN
	create_movement_action acro_pop_wheelie_move_up, MOVEMENT_ACTION_ACRO_POP_WHEELIE_MOVE_UP
	create_movement_action acro_pop_wheelie_move_left, MOVEMENT_ACTION_ACRO_POP_WHEELIE_MOVE_LEFT
	create_movement_action acro_pop_wheelie_move_right, MOVEMENT_ACTION_ACRO_POP_WHEELIE_MOVE_RIGHT
	create_movement_action acro_wheelie_move_down, MOVEMENT_ACTION_ACRO_WHEELIE_MOVE_DOWN
	create_movement_action acro_wheelie_move_up, MOVEMENT_ACTION_ACRO_WHEELIE_MOVE_UP
	create_movement_action acro_wheelie_move_left, MOVEMENT_ACTION_ACRO_WHEELIE_MOVE_LEFT
	create_movement_action acro_wheelie_move_right, MOVEMENT_ACTION_ACRO_WHEELIE_MOVE_RIGHT
	create_movement_action spin_down, MOVEMENT_ACTION_SPIN_DOWN
	create_movement_action spin_up, MOVEMENT_ACTION_SPIN_UP
	create_movement_action spin_left, MOVEMENT_ACTION_SPIN_LEFT
	create_movement_action spin_right, MOVEMENT_ACTION_SPIN_RIGHT
	create_movement_action raise_hand_and_stop, MOVEMENT_ACTION_RAISE_HAND_AND_STOP
	create_movement_action raise_hand_and_jump, MOVEMENT_ACTION_RAISE_HAND_AND_JUMP
	create_movement_action raise_hand_and_swim, MOVEMENT_ACTION_RAISE_HAND_AND_SWIM
	create_movement_action walk_slowest_down, MOVEMENT_ACTION_WALK_SLOWEST_DOWN
	create_movement_action walk_slowest_up, MOVEMENT_ACTION_WALK_SLOWEST_UP
	create_movement_action walk_slowest_left, MOVEMENT_ACTION_WALK_SLOWEST_LEFT
	create_movement_action walk_slowest_right, MOVEMENT_ACTION_WALK_SLOWEST_RIGHT
	create_movement_action shake_head_or_walk_in_place, MOVEMENT_ACTION_SHAKE_HEAD_OR_WALK_IN_PLACE
	create_movement_action glide_down, MOVEMENT_ACTION_GLIDE_DOWN
	create_movement_action glide_up, MOVEMENT_ACTION_GLIDE_UP
	create_movement_action glide_left, MOVEMENT_ACTION_GLIDE_LEFT
	create_movement_action glide_right, MOVEMENT_ACTION_GLIDE_RIGHT
	create_movement_action fly_up, MOVEMENT_ACTION_FLY_UP
	create_movement_action fly_down, MOVEMENT_ACTION_FLY_DOWN
	create_movement_action jump_special_with_effect_down, MOVEMENT_ACTION_JUMP_SPECIAL_WITH_EFFECT_DOWN
	create_movement_action jump_special_with_effect_up, MOVEMENT_ACTION_JUMP_SPECIAL_WITH_EFFECT_UP
	create_movement_action jump_special_with_effect_left, MOVEMENT_ACTION_JUMP_SPECIAL_WITH_EFFECT_LEFT
	create_movement_action jump_special_with_effect_right, MOVEMENT_ACTION_JUMP_SPECIAL_WITH_EFFECT_RIGHT
	create_movement_action step_end, MOVEMENT_ACTION_STEP_END
@ ===== END asm/macros/movement.inc =====
@ ===== BEGIN asm/macros/ec.inc =====

	.macro ec_duplicates count
	.2byte 0xff00 + \count
	.endm

	.macro ec_words_by_letter label
	.2byte (gEasyChatWordsByLetter_\label - gEasyChatWordsAlphabetized) / 2
	.endm
@ ===== END asm/macros/ec.inc =====
@ ===== BEGIN asm/macros/map.inc =====
@ Most of the macros in this file are for arranging map event data, and are output by mapjson using data from each map's JSON file.

	@ Takes a MAP constant and outputs the map group and map number as separate bytes
	.macro map map_id:req
	.byte \map_id >> 8    @ map group
	.byte \map_id & 0xFF  @ map num
	.endm

	@ Defines a map script. 'type' is any MAP_SCRIPT_* constant (see include/constants/map_scripts.h)
	.macro map_script type:req, script:req
	.byte \type
	.4byte \script
	.endm

	@ Defines an entry in a map script table (for either ON_WARP_INTO_MAP_TABLE or ON_FRAME_TABLE)
	.macro map_script_2 var:req, compare:req, script:req
	.2byte \var
	.2byte \compare
	.4byte \script
	.endm

	@ Defines an object event template for map data, to be used by a normal object. Mirrors the struct layout of ObjectEventTemplate in include/global.fieldmap.h
	.macro object_event index:req, gfx:req, x:req, y:req, elevation:req, movement_type:req, x_radius:req, y_radius:req, trainer_type:req, sight_radius_tree_etc:req, script:req, event_flag:req
	.byte \index
	.byte \gfx
	.byte OBJ_KIND_NORMAL
	.space 1  @ Padding
	.2byte \x, \y
	.byte \elevation
	.byte \movement_type
	.byte ((\y_radius << 4) | \x_radius)
	.space 1  @ Padding
	.2byte \trainer_type
	.2byte \sight_radius_tree_etc
	.4byte \script
	.2byte \event_flag
	.space 2  @ Padding
	inc _num_npcs
	.endm

	@ Defines an object event template for map data, to be used by a clone object. Mirrors the struct layout of ObjectEventTemplate in include/global.fieldmap.h
	.macro clone_event index:req, gfx:req, x:req, y:req, target_local_id:req, target_map_id:req
	.byte \index
	.byte \gfx
	.byte OBJ_KIND_CLONE
	.space 1  @ Padding
	.2byte \x, \y
	.byte \target_local_id
	.space 3  @ Padding
	.2byte \target_map_id & 0xFF  @ map num
	.2byte \target_map_id >> 8    @ map group
	.space 8  @ Padding
	inc _num_npcs
	.endm

	@ Defines a warp event for map data. Mirrors the struct layout of WarpEvent in include/global.fieldmap.h
	.macro warp_def x:req, y:req, elevation:req, warpId:req, map_id:req
	.2byte \x, \y
	.byte \elevation
	.byte \warpId
	.byte \map_id & 0xFF  @ map num
	.byte \map_id >> 8    @ map group
	inc _num_warps
	.endm

	@ Defines a coord event for map data. Mirrors the struct layout of CoordEvent in include/global.fieldmap.h
	.macro coord_event x:req, y:req, elevation:req, var:req, varValue:req, script:req
	.2byte \x, \y
	.byte \elevation
	.space 1  @ Padding
	.2byte \var
	.2byte \varValue
	.space 2  @ Padding
	.4byte \script
	inc _num_traps
	.endm

	@ Defines a weather coord event for map data. Any coord event is treated as a weather coord event if its script is NULL.
	@ NOTE: In FRLG, the weather handling functions are dummied out. See src/coord_event_weather.c
	.macro coord_weather_event x:req, y:req, elevation:req, weather:req
	coord_event \x, \y, \elevation, \weather, 0, NULL
	.endm

	@ Defines a generic background event for map data. Mirrors the struct layout of BgEvent in include/global.fieldmap.h
	@ 'kind' is any BG_EVENT_* constant (see include/constants/event_bg.h).
	@ 'arg6' is used differently depending on the bg event type. 'arg7' and 'arg8' are only used by bg_hidden_item_event.
	@ See macros below.
	.macro bg_event x:req, y, elevation:req, kind:req, arg6:req, arg7, arg8
	.2byte \x, \y
	.byte \elevation
	.byte \kind
	.space 2  @ Padding
	.if \kind != BG_EVENT_HIDDEN_ITEM
		.4byte \arg6
	.else
		.2byte \arg6
		.byte \arg7
		.byte \arg8
	.endif
	inc _num_signs
	.endm

	@ Defines a background sign event for map data. 'facing_dir' is any of the BG_EVENT_PLAYER_FACING_* constants (see include/constants/event_bg.h)
	.macro bg_sign_event x:req, y:req, elevation:req, facing_dir:req, script:req
	bg_event \x, \y, \elevation, \facing_dir, \script
	.endm

	@ Defines a background hidden item event for map data
	.macro bg_hidden_item_event x:req, y:req, elevation:req, item:req, flag:req, quantity:req, underfoot:req
	bg_event \x, \y, \elevation, BG_EVENT_HIDDEN_ITEM, \item, ((\flag) - FLAG_HIDDEN_ITEMS_START), \quantity | (\underfoot << 7)
	.endm

	@ Defines a background secret base event for map data.
	@ Unused by FRLG
	.macro bg_secret_base_event x:req, y:req, elevation:req, secret_base_id:req
	bg_event \x, \y, \elevation, BG_EVENT_SECRET_BASE, \secret_base_id
	.endm

	@ Defines the table of event data for a map. Mirrors the struct layout of MapEvents in include/global.fieldmap.h
	.macro map_events npcs:req, warps:req, traps:req, signs:req
	.byte _num_npcs, _num_warps, _num_traps, _num_signs
	.4byte \npcs, \warps, \traps, \signs
	reset_map_events
	.endm

	@ Resets the event counters used to track how many events a map has. Run when the events table is created by map_events
	.macro reset_map_events
	.set _num_npcs, 0
	.set _num_warps, 0
	.set _num_traps, 0
	.set _num_signs, 0
	.endm

	@ Initialize the event counters for the first map
	reset_map_events

	@ Directions for connecting maps
	@ The map.json files will only have e.g. "down" as direction data, and this will be appended to "connection_" by the connection macro
	.equiv connection_down, CONNECTION_SOUTH
	.equiv connection_up, CONNECTION_NORTH
	.equiv connection_left, CONNECTION_WEST
	.equiv connection_right, CONNECTION_EAST
	.equiv connection_dive, CONNECTION_DIVE
	.equiv connection_emerge, CONNECTION_EMERGE

	@ Defines a map connection. Mirrors the struct layout of MapConnection in include/global.fieldmap.h
	.macro connection direction:req, offset:req, map:req
	.byte connection_\direction
	.space 3  @ Padding
	.4byte \offset
	map \map
	.space 2  @ Padding
	.endm

	@ Defines the flags for a map header. Mirrors the layout of the bitfield in struct MapHeader in include/global.fieldmap.h
	.macro map_header_flags allow_cycling:req, allow_escaping:req, allow_running:req, show_map_name:req
	.byte \allow_cycling
	.byte ((\show_map_name & 1) << 2) | ((\allow_running & 1) << 1) | ((\allow_escaping & 1) << 0)
	.endm
@ ===== END asm/macros/map.inc =====
@ ===== BEGIN asm/macros/m4a.inc =====
	.macro song label, music_player, unknown
	.4byte \label
	.2byte \music_player
	.2byte \unknown
	.endm

	.macro music_player info_struct, track_struct, unknown_1, unknown_2
	.4byte \info_struct
	.4byte \track_struct
	.byte \unknown_1
	.space 1
	.2byte \unknown_2
	.endm
@ ===== END asm/macros/m4a.inc =====
@ ===== BEGIN asm/macros/trainer_tower.inc =====
	@ Sets NPC gfx and the floor layout depending on current challenge and floor
	.macro ttower_initfloor
	setvar VAR_0x8004, TRAINER_TOWER_FUNC_INIT_FLOOR
	special CallTrainerTowerFunc
	.endm

	@ Buffers the opponents battle speech to gStringVar4. speech is any TRAINER_TOWER_TEXT_*.
	.macro ttower_getspeech speech:req, trainer=0xFF
	setvar VAR_0x8004, TRAINER_TOWER_FUNC_GET_SPEECH
	setvar VAR_0x8005, \speech
	.if \trainer >= VARS_START && \trainer != 0xFF
	copyvar VAR_0x8006, \trainer
	.elseif \trainer != 0xFF
	setvar VAR_0x8006, \trainer
	.endif
	special CallTrainerTowerFunc
	.endm

	@ Starts a trainer tower battle. VAR_0x8005 is unused
	.macro ttower_dobattle
	setvar VAR_0x8004, TRAINER_TOWER_FUNC_DO_BATTLE
	setvar VAR_0x8005, 0
	special CallTrainerTowerFunc
	.endm

	@ Returns the current challenge type (CHALLENGE_TYPE_*). Mixed challenges use different types for each floor. If VAR_0x8005 is != FALSE, does nothing
	.macro ttower_getchallengetype
	setvar VAR_0x8004, TRAINER_TOWER_FUNC_GET_CHALLENGE_TYPE
	setvar VAR_0x8005, FALSE
	special CallTrainerTowerFunc
	.endm

	@ Adds 1 to the number of floors cleared (all trainers on floor defeated)
	.macro ttower_clearedfloor
	setvar VAR_0x8004, TRAINER_TOWER_FUNC_CLEARED_FLOOR
	special CallTrainerTowerFunc
	.endm

	@ TRUE if the trainers on this floor were already beaten, FALSE otherwise
	.macro ttower_isfloorcleared
	setvar VAR_0x8004, TRAINER_TOWER_FUNC_GET_FLOOR_CLEARED
	special CallTrainerTowerFunc
	.endm

	@ Initializes the Trainer Tower challenge and starts the timer
	.macro ttower_startchallenge
	setvar VAR_0x8004, TRAINER_TOWER_FUNC_START_CHALLENGE
	special CallTrainerTowerFunc
	.endm

	@ 0 if not spoken to yet, 1 if spoken to but not received prize, 2 if received prize
	.macro ttower_getownerstate
	setvar VAR_0x8004, TRAINER_TOWER_FUNC_GET_OWNER_STATE
	special CallTrainerTowerFunc
	.endm

	@ Tries to give prize. 0 if given successfully, 1 if no room for prize, 2 if giving prize should be skipped
	.macro ttower_giveprize
	setvar VAR_0x8004, TRAINER_TOWER_FUNC_GIVE_PRIZE
	special CallTrainerTowerFunc
	.endm

	@ Checks the final challenge time. 0 if new record, 1 if not, 2 if time has already been checked
	.macro ttower_checkfinaltime
	setvar VAR_0x8004, TRAINER_TOWER_FUNC_CHECK_FINAL_TIME
	special CallTrainerTowerFunc
	.endm

	@ Resumes the challenge timer (or starts, if the timer is 0)
	.macro ttower_resumetimer
	setvar VAR_0x8004, TRAINER_TOWER_FUNC_RESUME_TIMER
	special CallTrainerTowerFunc
	.endm

	@ Sets that the player lost the challenge
	.macro ttower_setlost
	setvar VAR_0x8004, TRAINER_TOWER_FUNC_SET_LOST
	special CallTrainerTowerFunc
	.endm

	@ Returns the status of the current Trainer Tower challenge (CHALLENGE_STATUS_*)
	.macro ttower_getchallengestatus
	setvar VAR_0x8004, TRAINER_TOWER_FUNC_GET_CHALLENGE_STATUS
	special CallTrainerTowerFunc
	.endm

	@ Buffers the current challenge time (min in gStringVar1, sec in gStringVar2, fraction sec in gStringVar3)
	.macro ttower_gettime
	setvar VAR_0x8004, TRAINER_TOWER_FUNC_GET_TIME
	special CallTrainerTowerFunc
	.endm

	@ Unused. Displays Trainer Tower results. Handled by ShowBattleRecords instead
	.macro ttower_showresults
	setvar VAR_0x8004, TRAINER_TOWER_FUNC_SHOW_RESULTS
	special CallTrainerTowerFunc
	.endm

	@ Unused. See above
	.macro ttower_closeresults
	setvar VAR_0x8004, TRAINER_TOWER_FUNC_CLOSE_RESULTS
	special CallTrainerTowerFunc
	.endm

	@ Returns the eligibility of the players party for a double battle (using GetMonsStateToDoubles)
	.macro ttower_checkdoubles
	setvar VAR_0x8004, TRAINER_TOWER_FUNC_CHECK_DOUBLES
	special CallTrainerTowerFunc
	.endm

	@ For the unused E-Reader challenges, gets the number of floors used. Otherwise returns FALSE (all floors used)
	.macro ttower_getnumfloors
	setvar VAR_0x8004, TRAINER_TOWER_FUNC_GET_NUM_FLOORS
	special CallTrainerTowerFunc
	.endm

	@ Dummied, always returns FALSE
	.macro ttower_shouldexit
	setvar VAR_0x8004, TRAINER_TOWER_FUNC_SHOULD_WARP_TO_COUNTER
	special CallTrainerTowerFunc
	.endm

	@ Plays the encounter music for the trainer number in VAR_TEMP_1
	.macro ttower_encountermusic
	setvar VAR_0x8004, TRAINER_TOWER_FUNC_ENCOUNTER_MUSIC
	special CallTrainerTowerFunc
	.endm

	@ TRUE if the player reached the Battle Tower owner, FALSE otherwise
	.macro ttower_getbeatchallenge
	setvar VAR_0x8004, TRAINER_TOWER_FUNC_GET_BEAT_CHALLENGE
	special CallTrainerTowerFunc
	.endm
@ ===== END asm/macros/trainer_tower.inc =====

	.macro region_map_location x, y, width, height, name
	.byte \x
	.byte \y
	.byte \width
	.byte \height
	.4byte gMapName_\name
	.endm

	.macro obj_tiles address, uncompressed_size, tag
	.4byte \address
	.2byte \uncompressed_size
	.2byte \tag
	.endm

	.macro null_obj_tiles
	obj_tiles 0, 0, 0
	.endm

	.macro obj_pal address, tag
	.4byte \address
	.2byte \tag
	.2byte 0 @ padding
	.endm

	.macro null_obj_pal
	obj_pal 0, 0
	.endm

	.macro paired_pals tag, address
	.2byte \tag
	.2byte 0 @ padding
	.4byte \address
	.endm

@ For object animation frames.
	.macro obj_frame_tiles address, uncompressed_size
	.4byte \address
	.2byte \uncompressed_size
	.2byte 0 @ padding
	.endm

	.macro spr_template tile_tag, pal_tag, oam, anims, images, affine_anims, callback
	.2byte \tile_tag
	.2byte \pal_tag
	.4byte \oam
	.4byte \anims
	.4byte \images
	.4byte \affine_anims
	.4byte \callback
	.endm

@ Berry trees have a table defining the palette slot used for each of their 5
@ stages. However, the first 2 stages always use the same slots regardless of
@ the type of tree and the slots of the last 3 stages always equal each other.
	.macro berry_tree_palette_slot_table slot
	.byte 3, 4, \slot, \slot, \slot
	.endm

	.macro subsprite x, y, priority, tile_num_offset, size
	.byte \x
	.byte \y
	.2byte ((\priority) << 14) | ((\tile_num_offset) << 4) | SPRITE_SIZE_\size
	.endm

	.macro obj_image_anim_frame pic_id, duration, flags = 0
	.2byte \pic_id
	.byte (\flags) | (\duration)
	.byte 0 @ padding
	.endm

	.macro obj_image_anim_loop count
	.2byte 0xfffd
	.byte \count
	.byte 0 @ padding
	.endm

	.macro obj_image_anim_jump target_index
	.2byte 0xfffe
	.byte \target_index
	.byte 0 @ padding
	.endm

	.macro obj_image_anim_end
	.2byte 0xffff
	.2byte 0 @ padding
	.endm

	.macro obj_rot_scal_anim_frame delta_x_scale, delta_y_scale, delta_angle, duration
	.2byte \delta_x_scale
	.2byte \delta_y_scale
	.byte \delta_angle
	.byte \duration
	.2byte 0 @ padding
	.endm

	.macro obj_rot_scal_anim_loop count
	.2byte 0x7ffd
	.2byte \count
	.4byte 0 @ padding
	.endm

	.macro obj_rot_scal_anim_jump target_index
	.2byte 0x7ffe
	.2byte \target_index
	.4byte 0 @ padding
	.endm

	.macro obj_rot_scal_anim_end unknown=0
	.2byte 0x7fff
	.2byte \unknown
	.fill 4 @ padding
	.endm

	.macro overworld_frame ptr:req, width:req, height:req, frame:req
	.4byte (\ptr + (\width * \height * \frame * 64) / 2)
	.2byte (\width * \height * 64) / 2
	.2byte 0 @ padding
	.endm

	.macro credits_entry number, text
	.4byte \number
	.4byte \text
	.endm

	.macro door_anim_frame unknown, offset
	.byte \unknown
	.byte 0 @ padding
	.2byte \offset
	.endm

	.macro door_anim_gfx metatile_num, unknown, tile_addr, palette_addr
	.2byte \metatile_num
	.2byte \unknown
	.4byte \tile_addr
	.4byte \palette_addr
	.endm

	.macro trainer_eye_trainer opp_1, opp_2, opp_3, opp_4, opp_5, map_name
	.2byte OPPONENT_\opp_1
	.2byte OPPONENT_\opp_2
	.2byte OPPONENT_\opp_3
	.2byte OPPONENT_\opp_4
	.2byte OPPONENT_\opp_5
	.2byte GROUP_\map_name
	.2byte MAP_\map_name
	.space 2
	.endm

	.macro window_template bg, top, left, height, width, palno, baseBlock
	.byte \bg, \top, \left, \height, \width, \palno
	.2byte \baseBlock
	.endm

	.macro abspath relative
	.if REVISION == 0
	.ascii "C:/WORK/POKeFRLG/src/pm_lgfr_ose/source/"
	.else
	.ascii "C:/WORK/POKeFRLG/Src/pm_lgfr_ose/source/"
	.endif
	.asciz "\relative"
	.endm
@ ===== END asm/macros.inc =====
@ ===== BEGIN constants/constants.inc =====
@ ===== BEGIN constants/gba_constants.inc =====
	.set PSR_USR_MODE,  0x00000010
	.set PSR_FIQ_MODE,  0x00000011
	.set PSR_IRQ_MODE,  0x00000012
	.set PSR_SVC_MODE,  0x00000013
	.set PSR_ABT_MODE,  0x00000017
	.set PSR_UND_MODE,  0x0000001b
	.set PSR_SYS_MODE,  0x0000001f
	.set PSR_MODE_MASK, 0x0000001f
	.set PSR_T_BIT,     0x00000020
	.set PSR_F_BIT,     0x00000040
	.set PSR_I_BIT,     0x00000080

	.set EWRAM_START, 0x02000000
	.set EWRAM_END,   EWRAM_START + 0x40000
	.set IWRAM_START, 0x03000000
	.set IWRAM_END,   IWRAM_START + 0x8000

	.set PLTT,     0x5000000
	.set BG_PLTT,  PLTT
	.set OBJ_PLTT, PLTT + 0x200

	.set VRAM,      0x6000000
	.set BG_VRAM,   VRAM
	.set OBJ_VRAM0, VRAM + 0x10000 @ text-mode BG
	.set OBJ_VRAM1, VRAM + 0x14000 @ bitmap-mode BG

	.set OAM, 0x7000000

	.set SOUND_INFO_PTR, 0x3007FF0
	.set INTR_CHECK,     0x3007FF8
	.set INTR_VECTOR,    0x3007FFC

	.set INTR_FLAG_VBLANK,  1 << 0
	.set INTR_FLAG_HBLANK,  1 << 1
	.set INTR_FLAG_VCOUNT,  1 << 2
	.set INTR_FLAG_TIMER0,  1 << 3
	.set INTR_FLAG_TIMER1,  1 << 4
	.set INTR_FLAG_TIMER2,  1 << 5
	.set INTR_FLAG_TIMER3,  1 << 6
	.set INTR_FLAG_SERIAL,  1 << 7
	.set INTR_FLAG_DMA0,    1 << 8
	.set INTR_FLAG_DMA1,    1 << 9
	.set INTR_FLAG_DMA2,    1 << 10
	.set INTR_FLAG_DMA3,    1 << 11
	.set INTR_FLAG_KEYPAD,  1 << 12
	.set INTR_FLAG_GAMEPAK, 1 << 13

	.set VCOUNT_VBLANK, 160
	.set TOTAL_SCANLINES, 228

	.set REG_BASE, 0x4000000 @ I/O register base address

@ I/O register offsets
	.set OFFSET_REG_DISPCNT,     0x0
	.set OFFSET_REG_DISPSTAT,    0x4
	.set OFFSET_REG_VCOUNT,      0x6
	.set OFFSET_REG_BG0CNT,      0x8
	.set OFFSET_REG_BG1CNT,      0xa
	.set OFFSET_REG_BG2CNT,      0xc
	.set OFFSET_REG_BG3CNT,      0xe
	.set OFFSET_REG_BG0HOFS,     0x10
	.set OFFSET_REG_BG0VOFS,     0x12
	.set OFFSET_REG_BG1HOFS,     0x14
	.set OFFSET_REG_BG1VOFS,     0x16
	.set OFFSET_REG_BG2HOFS,     0x18
	.set OFFSET_REG_BG2VOFS,     0x1a
	.set OFFSET_REG_BG3HOFS,     0x1c
	.set OFFSET_REG_BG3VOFS,     0x1e
	.set OFFSET_REG_BG2PA,       0x20
	.set OFFSET_REG_BG2PB,       0x22
	.set OFFSET_REG_BG2PC,       0x24
	.set OFFSET_REG_BG2PD,       0x26
	.set OFFSET_REG_BG2X_L,      0x28
	.set OFFSET_REG_BG2X_H,      0x2a
	.set OFFSET_REG_BG2Y_L,      0x2c
	.set OFFSET_REG_BG2Y_H,      0x2e
	.set OFFSET_REG_BG3PA,       0x30
	.set OFFSET_REG_BG3PB,       0x32
	.set OFFSET_REG_BG3PC,       0x34
	.set OFFSET_REG_BG3PD,       0x36
	.set OFFSET_REG_BG3X_L,      0x38
	.set OFFSET_REG_BG3X_H,      0x3a
	.set OFFSET_REG_BG3Y_L,      0x3c
	.set OFFSET_REG_BG3Y_H,      0x3e
	.set OFFSET_REG_WIN0H,       0x40
	.set OFFSET_REG_WIN1H,       0x42
	.set OFFSET_REG_WIN0V,       0x44
	.set OFFSET_REG_WIN1V,       0x46
	.set OFFSET_REG_WININ,       0x48
	.set OFFSET_REG_WINOUT,      0x4a
	.set OFFSET_REG_MOSAIC,      0x4c
	.set OFFSET_REG_BLDCNT,      0x50
	.set OFFSET_REG_BLDALPHA,    0x52
	.set OFFSET_REG_BLDY,        0x54

	.set OFFSET_REG_SOUND1CNT,   0x60
	.set OFFSET_REG_SOUND1CNT_L, 0x60
	.set OFFSET_REG_NR10,        0x60
	.set OFFSET_REG_SOUND1CNT_H, 0x62
	.set OFFSET_REG_NR11,        0x62
	.set OFFSET_REG_NR12,        0x63
	.set OFFSET_REG_SOUND1CNT_X, 0x64
	.set OFFSET_REG_NR13,        0x64
	.set OFFSET_REG_NR14,        0x65
	.set OFFSET_REG_SOUND2CNT,   0x68
	.set OFFSET_REG_SOUND2CNT_L, 0x68
	.set OFFSET_REG_NR21,        0x68
	.set OFFSET_REG_NR22,        0x69
	.set OFFSET_REG_SOUND2CNT_H, 0x6c
	.set OFFSET_REG_NR23,        0x6c
	.set OFFSET_REG_NR24,        0x6d
	.set OFFSET_REG_SOUND3CNT,   0x70
	.set OFFSET_REG_SOUND3CNT_L, 0x70
	.set OFFSET_REG_NR30,        0x70
	.set OFFSET_REG_SOUND3CNT_H, 0x72
	.set OFFSET_REG_NR31,        0x72
	.set OFFSET_REG_NR32,        0x73
	.set OFFSET_REG_SOUND3CNT_X, 0x74
	.set OFFSET_REG_NR33,        0x74
	.set OFFSET_REG_NR34,        0x75
	.set OFFSET_REG_SOUND4CNT,   0x78
	.set OFFSET_REG_SOUND4CNT_L, 0x78
	.set OFFSET_REG_NR41,        0x78
	.set OFFSET_REG_NR42,        0x79
	.set OFFSET_REG_SOUND4CNT_H, 0x7c
	.set OFFSET_REG_NR43,        0x7c
	.set OFFSET_REG_NR44,        0x7d
	.set OFFSET_REG_SOUNDCNT,    0x80
	.set OFFSET_REG_SOUNDCNT_L,  0x80
	.set OFFSET_REG_NR50,        0x80
	.set OFFSET_REG_NR51,        0x81
	.set OFFSET_REG_SOUNDCNT_H,  0x82
	.set OFFSET_REG_SOUNDCNT_X,  0x84
	.set OFFSET_REG_NR52,        0x84
	.set OFFSET_REG_SOUNDBIAS,   0x88
	.set OFFSET_REG_WAVE_RAM,    0x90
	.set OFFSET_REG_WAVE_RAM0,   0x90
	.set OFFSET_REG_WAVE_RAM0_L, 0x90
	.set OFFSET_REG_WAVE_RAM0_H, 0x92
	.set OFFSET_REG_WAVE_RAM1,   0x94
	.set OFFSET_REG_WAVE_RAM1_L, 0x94
	.set OFFSET_REG_WAVE_RAM1_H, 0x96
	.set OFFSET_REG_WAVE_RAM2,   0x98
	.set OFFSET_REG_WAVE_RAM2_L, 0x98
	.set OFFSET_REG_WAVE_RAM2_H, 0x9a
	.set OFFSET_REG_WAVE_RAM3,   0x9c
	.set OFFSET_REG_WAVE_RAM3_L, 0x9c
	.set OFFSET_REG_WAVE_RAM3_H, 0x9e
	.set OFFSET_REG_FIFO,        0xa0
	.set OFFSET_REG_FIFO_A,      0xa0
	.set OFFSET_REG_FIFO_A_L,    0xa0
	.set OFFSET_REG_FIFO_A_H,    0xa2
	.set OFFSET_REG_FIFO_B,      0xa4
	.set OFFSET_REG_FIFO_B_L,    0xa4
	.set OFFSET_REG_FIFO_B_H,    0xa6

	.set OFFSET_REG_DMA0,        0xb0
	.set OFFSET_REG_DMA0SAD,     0xb0
	.set OFFSET_REG_DMA0SAD_L,   0xb0
	.set OFFSET_REG_DMA0SAD_H,   0xb2
	.set OFFSET_REG_DMA0DAD,     0xb4
	.set OFFSET_REG_DMA0DAD_L,   0xb4
	.set OFFSET_REG_DMA0DAD_H,   0xb6
	.set OFFSET_REG_DMA0CNT,     0xb8
	.set OFFSET_REG_DMA0CNT_L,   0xb8
	.set OFFSET_REG_DMA0CNT_H,   0xba
	.set OFFSET_REG_DMA1,        0xbc
	.set OFFSET_REG_DMA1SAD,     0xbc
	.set OFFSET_REG_DMA1SAD_L,   0xbc
	.set OFFSET_REG_DMA1SAD_H,   0xbe
	.set OFFSET_REG_DMA1DAD,     0xc0
	.set OFFSET_REG_DMA1DAD_L,   0xc0
	.set OFFSET_REG_DMA1DAD_H,   0xc2
	.set OFFSET_REG_DMA1CNT,     0xc4
	.set OFFSET_REG_DMA1CNT_L,   0xc4
	.set OFFSET_REG_DMA1CNT_H,   0xc6
	.set OFFSET_REG_DMA2,        0xc8
	.set OFFSET_REG_DMA2SAD,     0xc8
	.set OFFSET_REG_DMA2SAD_L,   0xc8
	.set OFFSET_REG_DMA2SAD_H,   0xca
	.set OFFSET_REG_DMA2DAD,     0xcc
	.set OFFSET_REG_DMA2DAD_L,   0xcc
	.set OFFSET_REG_DMA2DAD_H,   0xce
	.set OFFSET_REG_DMA2CNT,     0xd0
	.set OFFSET_REG_DMA2CNT_L,   0xd0
	.set OFFSET_REG_DMA2CNT_H,   0xd2
	.set OFFSET_REG_DMA3,        0xd4
	.set OFFSET_REG_DMA3SAD,     0xd4
	.set OFFSET_REG_DMA3SAD_L,   0xd4
	.set OFFSET_REG_DMA3SAD_H,   0xd6
	.set OFFSET_REG_DMA3DAD,     0xd8
	.set OFFSET_REG_DMA3DAD_L,   0xd8
	.set OFFSET_REG_DMA3DAD_H,   0xda
	.set OFFSET_REG_DMA3CNT,     0xdc
	.set OFFSET_REG_DMA3CNT_L,   0xdc
	.set OFFSET_REG_DMA3CNT_H,   0xde

	.set OFFSET_REG_TM0CNT,      0x100
	.set OFFSET_REG_TM0CNT_L,    0x100
	.set OFFSET_REG_TM0CNT_H,    0x102
	.set OFFSET_REG_TM1CNT,      0x104
	.set OFFSET_REG_TM1CNT_L,    0x104
	.set OFFSET_REG_TM1CNT_H,    0x106
	.set OFFSET_REG_TM2CNT,      0x108
	.set OFFSET_REG_TM2CNT_L,    0x108
	.set OFFSET_REG_TM2CNT_H,    0x10a
	.set OFFSET_REG_TM3CNT,      0x10c
	.set OFFSET_REG_TM3CNT_L,    0x10c
	.set OFFSET_REG_TM3CNT_H,    0x10e

	.set OFFSET_REG_SIOCNT,      0x128
	.set OFFSET_REG_SIODATA8,    0x12a
	.set OFFSET_REG_SIODATA32,   0x120
	.set OFFSET_REG_SIOMLT_SEND, 0x12a
	.set OFFSET_REG_SIOMLT_RECV, 0x120
	.set OFFSET_REG_SIOMULTI0,   0x120
	.set OFFSET_REG_SIOMULTI1,   0x122
	.set OFFSET_REG_SIOMULTI2,   0x124
	.set OFFSET_REG_SIOMULTI3,   0x126

	.set OFFSET_REG_KEYINPUT,    0x130
	.set OFFSET_REG_KEYCNT,      0x132

	.set OFFSET_REG_RCNT,        0x134

	.set OFFSET_REG_JOYCNT,      0x140
	.set OFFSET_REG_JOYSTAT,     0x158
	.set OFFSET_REG_JOY_RECV,    0x150
	.set OFFSET_REG_JOY_RECV_L,  0x150
	.set OFFSET_REG_JOY_RECV_H,  0x152
	.set OFFSET_REG_JOY_TRANS,   0x154
	.set OFFSET_REG_JOY_TRANS_L, 0x154
	.set OFFSET_REG_JOY_TRANS_H, 0x156

	.set OFFSET_REG_IME,         0x208
	.set OFFSET_REG_IE,          0x200
	.set OFFSET_REG_IF,          0x202

	.set OFFSET_REG_WAITCNT,     0x204

@ I/O register addresses
	.set REG_DISPCNT,     REG_BASE + OFFSET_REG_DISPCNT
	.set REG_DISPSTAT,    REG_BASE + OFFSET_REG_DISPSTAT
	.set REG_VCOUNT,      REG_BASE + OFFSET_REG_VCOUNT
	.set REG_BG0CNT,      REG_BASE + OFFSET_REG_BG0CNT
	.set REG_BG1CNT,      REG_BASE + OFFSET_REG_BG1CNT
	.set REG_BG2CNT,      REG_BASE + OFFSET_REG_BG2CNT
	.set REG_BG3CNT,      REG_BASE + OFFSET_REG_BG3CNT
	.set REG_BG0HOFS,     REG_BASE + OFFSET_REG_BG0HOFS
	.set REG_BG0VOFS,     REG_BASE + OFFSET_REG_BG0VOFS
	.set REG_BG1HOFS,     REG_BASE + OFFSET_REG_BG1HOFS
	.set REG_BG1VOFS,     REG_BASE + OFFSET_REG_BG1VOFS
	.set REG_BG2HOFS,     REG_BASE + OFFSET_REG_BG2HOFS
	.set REG_BG2VOFS,     REG_BASE + OFFSET_REG_BG2VOFS
	.set REG_BG3HOFS,     REG_BASE + OFFSET_REG_BG3HOFS
	.set REG_BG3VOFS,     REG_BASE + OFFSET_REG_BG3VOFS
	.set REG_BG2PA,       REG_BASE + OFFSET_REG_BG2PA
	.set REG_BG2PB,       REG_BASE + OFFSET_REG_BG2PB
	.set REG_BG2PC,       REG_BASE + OFFSET_REG_BG2PC
	.set REG_BG2PD,       REG_BASE + OFFSET_REG_BG2PD
	.set REG_BG2X_L,      REG_BASE + OFFSET_REG_BG2X_L
	.set REG_BG2X_H,      REG_BASE + OFFSET_REG_BG2X_H
	.set REG_BG2Y_L,      REG_BASE + OFFSET_REG_BG2Y_L
	.set REG_BG2Y_H,      REG_BASE + OFFSET_REG_BG2Y_H
	.set REG_BG3PA,       REG_BASE + OFFSET_REG_BG3PA
	.set REG_BG3PB,       REG_BASE + OFFSET_REG_BG3PB
	.set REG_BG3PC,       REG_BASE + OFFSET_REG_BG3PC
	.set REG_BG3PD,       REG_BASE + OFFSET_REG_BG3PD
	.set REG_BG3X_L,      REG_BASE + OFFSET_REG_BG3X_L
	.set REG_BG3X_H,      REG_BASE + OFFSET_REG_BG3X_H
	.set REG_BG3Y_L,      REG_BASE + OFFSET_REG_BG3Y_L
	.set REG_BG3Y_H,      REG_BASE + OFFSET_REG_BG3Y_H
	.set REG_WIN0H,       REG_BASE + OFFSET_REG_WIN0H
	.set REG_WIN1H,       REG_BASE + OFFSET_REG_WIN1H
	.set REG_WIN0V,       REG_BASE + OFFSET_REG_WIN0V
	.set REG_WIN1V,       REG_BASE + OFFSET_REG_WIN1V
	.set REG_WININ,       REG_BASE + OFFSET_REG_WININ
	.set REG_WINOUT,      REG_BASE + OFFSET_REG_WINOUT
	.set REG_MOSAIC,      REG_BASE + OFFSET_REG_MOSAIC
	.set REG_BLDCNT,      REG_BASE + OFFSET_REG_BLDCNT
	.set REG_BLDALPHA,    REG_BASE + OFFSET_REG_BLDALPHA
	.set REG_BLDY,        REG_BASE + OFFSET_REG_BLDY

	.set REG_SOUND1CNT,   REG_BASE + OFFSET_REG_SOUND1CNT
	.set REG_SOUND1CNT_L, REG_BASE + OFFSET_REG_SOUND1CNT_L
	.set REG_NR10,        REG_BASE + OFFSET_REG_NR10
	.set REG_SOUND1CNT_H, REG_BASE + OFFSET_REG_SOUND1CNT_H
	.set REG_NR11,        REG_BASE + OFFSET_REG_NR11
	.set REG_NR12,        REG_BASE + OFFSET_REG_NR12
	.set REG_SOUND1CNT_X, REG_BASE + OFFSET_REG_SOUND1CNT_X
	.set REG_NR13,        REG_BASE + OFFSET_REG_NR13
	.set REG_NR14,        REG_BASE + OFFSET_REG_NR14
	.set REG_SOUND2CNT,   REG_BASE + OFFSET_REG_SOUND2CNT
	.set REG_SOUND2CNT_L, REG_BASE + OFFSET_REG_SOUND2CNT_L
	.set REG_NR21,        REG_BASE + OFFSET_REG_NR21
	.set REG_NR22,        REG_BASE + OFFSET_REG_NR22
	.set REG_SOUND2CNT_H, REG_BASE + OFFSET_REG_SOUND2CNT_H
	.set REG_NR23,        REG_BASE + OFFSET_REG_NR23
	.set REG_NR24,        REG_BASE + OFFSET_REG_NR24
	.set REG_SOUND3CNT,   REG_BASE + OFFSET_REG_SOUND3CNT
	.set REG_SOUND3CNT_L, REG_BASE + OFFSET_REG_SOUND3CNT_L
	.set REG_NR30,        REG_BASE + OFFSET_REG_NR30
	.set REG_SOUND3CNT_H, REG_BASE + OFFSET_REG_SOUND3CNT_H
	.set REG_NR31,        REG_BASE + OFFSET_REG_NR31
	.set REG_NR32,        REG_BASE + OFFSET_REG_NR32
	.set REG_SOUND3CNT_X, REG_BASE + OFFSET_REG_SOUND3CNT_X
	.set REG_NR33,        REG_BASE + OFFSET_REG_NR33
	.set REG_NR34,        REG_BASE + OFFSET_REG_NR34
	.set REG_SOUND4CNT,   REG_BASE + OFFSET_REG_SOUND4CNT
	.set REG_SOUND4CNT_L, REG_BASE + OFFSET_REG_SOUND4CNT_L
	.set REG_NR41,        REG_BASE + OFFSET_REG_NR41
	.set REG_NR42,        REG_BASE + OFFSET_REG_NR42
	.set REG_SOUND4CNT_H, REG_BASE + OFFSET_REG_SOUND4CNT_H
	.set REG_NR43,        REG_BASE + OFFSET_REG_NR43
	.set REG_NR44,        REG_BASE + OFFSET_REG_NR44
	.set REG_SOUNDCNT,    REG_BASE + OFFSET_REG_SOUNDCNT
	.set REG_SOUNDCNT_L,  REG_BASE + OFFSET_REG_SOUNDCNT_L
	.set REG_NR50,        REG_BASE + OFFSET_REG_NR50
	.set REG_NR51,        REG_BASE + OFFSET_REG_NR51
	.set REG_SOUNDCNT_H,  REG_BASE + OFFSET_REG_SOUNDCNT_H
	.set REG_SOUNDCNT_X,  REG_BASE + OFFSET_REG_SOUNDCNT_X
	.set REG_NR52,        REG_BASE + OFFSET_REG_NR52
	.set REG_SOUNDBIAS,   REG_BASE + OFFSET_REG_SOUNDBIAS
	.set REG_WAVE_RAM,    REG_BASE + OFFSET_REG_WAVE_RAM
	.set REG_WAVE_RAM0,   REG_BASE + OFFSET_REG_WAVE_RAM0
	.set REG_WAVE_RAM0_L, REG_BASE + OFFSET_REG_WAVE_RAM0_L
	.set REG_WAVE_RAM0_H, REG_BASE + OFFSET_REG_WAVE_RAM0_H
	.set REG_WAVE_RAM1,   REG_BASE + OFFSET_REG_WAVE_RAM1
	.set REG_WAVE_RAM1_L, REG_BASE + OFFSET_REG_WAVE_RAM1_L
	.set REG_WAVE_RAM1_H, REG_BASE + OFFSET_REG_WAVE_RAM1_H
	.set REG_WAVE_RAM2,   REG_BASE + OFFSET_REG_WAVE_RAM2
	.set REG_WAVE_RAM2_L, REG_BASE + OFFSET_REG_WAVE_RAM2_L
	.set REG_WAVE_RAM2_H, REG_BASE + OFFSET_REG_WAVE_RAM2_H
	.set REG_WAVE_RAM3,   REG_BASE + OFFSET_REG_WAVE_RAM3
	.set REG_WAVE_RAM3_L, REG_BASE + OFFSET_REG_WAVE_RAM3_L
	.set REG_WAVE_RAM3_H, REG_BASE + OFFSET_REG_WAVE_RAM3_H
	.set REG_FIFO,        REG_BASE + OFFSET_REG_FIFO
	.set REG_FIFO_A,      REG_BASE + OFFSET_REG_FIFO_A
	.set REG_FIFO_A_L,    REG_BASE + OFFSET_REG_FIFO_A_L
	.set REG_FIFO_A_H,    REG_BASE + OFFSET_REG_FIFO_A_H
	.set REG_FIFO_B,      REG_BASE + OFFSET_REG_FIFO_B
	.set REG_FIFO_B_L,    REG_BASE + OFFSET_REG_FIFO_B_L
	.set REG_FIFO_B_H,    REG_BASE + OFFSET_REG_FIFO_B_H

	.set REG_DMA0,        REG_BASE + OFFSET_REG_DMA0
	.set REG_DMA0SAD,     REG_BASE + OFFSET_REG_DMA0SAD
	.set REG_DMA0SAD_L,   REG_BASE + OFFSET_REG_DMA0SAD_L
	.set REG_DMA0SAD_H,   REG_BASE + OFFSET_REG_DMA0SAD_H
	.set REG_DMA0DAD,     REG_BASE + OFFSET_REG_DMA0DAD
	.set REG_DMA0DAD_L,   REG_BASE + OFFSET_REG_DMA0DAD_L
	.set REG_DMA0DAD_H,   REG_BASE + OFFSET_REG_DMA0DAD_H
	.set REG_DMA0CNT,     REG_BASE + OFFSET_REG_DMA0CNT
	.set REG_DMA0CNT_L,   REG_BASE + OFFSET_REG_DMA0CNT_L
	.set REG_DMA0CNT_H,   REG_BASE + OFFSET_REG_DMA0CNT_H
	.set REG_DMA1,        REG_BASE + OFFSET_REG_DMA1
	.set REG_DMA1SAD,     REG_BASE + OFFSET_REG_DMA1SAD
	.set REG_DMA1SAD_L,   REG_BASE + OFFSET_REG_DMA1SAD_L
	.set REG_DMA1SAD_H,   REG_BASE + OFFSET_REG_DMA1SAD_H
	.set REG_DMA1DAD,     REG_BASE + OFFSET_REG_DMA1DAD
	.set REG_DMA1DAD_L,   REG_BASE + OFFSET_REG_DMA1DAD_L
	.set REG_DMA1DAD_H,   REG_BASE + OFFSET_REG_DMA1DAD_H
	.set REG_DMA1CNT,     REG_BASE + OFFSET_REG_DMA1CNT
	.set REG_DMA1CNT_L,   REG_BASE + OFFSET_REG_DMA1CNT_L
	.set REG_DMA1CNT_H,   REG_BASE + OFFSET_REG_DMA1CNT_H
	.set REG_DMA2,        REG_BASE + OFFSET_REG_DMA2
	.set REG_DMA2SAD,     REG_BASE + OFFSET_REG_DMA2SAD
	.set REG_DMA2SAD_L,   REG_BASE + OFFSET_REG_DMA2SAD_L
	.set REG_DMA2SAD_H,   REG_BASE + OFFSET_REG_DMA2SAD_H
	.set REG_DMA2DAD,     REG_BASE + OFFSET_REG_DMA2DAD
	.set REG_DMA2DAD_L,   REG_BASE + OFFSET_REG_DMA2DAD_L
	.set REG_DMA2DAD_H,   REG_BASE + OFFSET_REG_DMA2DAD_H
	.set REG_DMA2CNT,     REG_BASE + OFFSET_REG_DMA2CNT
	.set REG_DMA2CNT_L,   REG_BASE + OFFSET_REG_DMA2CNT_L
	.set REG_DMA2CNT_H,   REG_BASE + OFFSET_REG_DMA2CNT_H
	.set REG_DMA3,        REG_BASE + OFFSET_REG_DMA3
	.set REG_DMA3SAD,     REG_BASE + OFFSET_REG_DMA3SAD
	.set REG_DMA3SAD_L,   REG_BASE + OFFSET_REG_DMA3SAD_L
	.set REG_DMA3SAD_H,   REG_BASE + OFFSET_REG_DMA3SAD_H
	.set REG_DMA3DAD,     REG_BASE + OFFSET_REG_DMA3DAD
	.set REG_DMA3DAD_L,   REG_BASE + OFFSET_REG_DMA3DAD_L
	.set REG_DMA3DAD_H,   REG_BASE + OFFSET_REG_DMA3DAD_H
	.set REG_DMA3CNT,     REG_BASE + OFFSET_REG_DMA3CNT
	.set REG_DMA3CNT_L,   REG_BASE + OFFSET_REG_DMA3CNT_L
	.set REG_DMA3CNT_H,   REG_BASE + OFFSET_REG_DMA3CNT_H

	.set REG_TM0CNT,      REG_BASE + OFFSET_REG_TM0CNT
	.set REG_TM0CNT_L,    REG_BASE + OFFSET_REG_TM0CNT_L
	.set REG_TM0CNT_H,    REG_BASE + OFFSET_REG_TM0CNT_H
	.set REG_TM1CNT,      REG_BASE + OFFSET_REG_TM1CNT
	.set REG_TM1CNT_L,    REG_BASE + OFFSET_REG_TM1CNT_L
	.set REG_TM1CNT_H,    REG_BASE + OFFSET_REG_TM1CNT_H
	.set REG_TM2CNT,      REG_BASE + OFFSET_REG_TM2CNT
	.set REG_TM2CNT_L,    REG_BASE + OFFSET_REG_TM2CNT_L
	.set REG_TM2CNT_H,    REG_BASE + OFFSET_REG_TM2CNT_H
	.set REG_TM3CNT,      REG_BASE + OFFSET_REG_TM3CNT
	.set REG_TM3CNT_L,    REG_BASE + OFFSET_REG_TM3CNT_L
	.set REG_TM3CNT_H,    REG_BASE + OFFSET_REG_TM3CNT_H

	.set REG_SIOCNT,      REG_BASE + OFFSET_REG_SIOCNT
	.set REG_SIODATA8,    REG_BASE + OFFSET_REG_SIODATA8
	.set REG_SIODATA32,   REG_BASE + OFFSET_REG_SIODATA32
	.set REG_SIOMLT_SEND, REG_BASE + OFFSET_REG_SIOMLT_SEND
	.set REG_SIOMLT_RECV, REG_BASE + OFFSET_REG_SIOMLT_RECV
	.set REG_SIOMULTI0,   REG_BASE + OFFSET_REG_SIOMULTI0
	.set REG_SIOMULTI1,   REG_BASE + OFFSET_REG_SIOMULTI1
	.set REG_SIOMULTI2,   REG_BASE + OFFSET_REG_SIOMULTI2
	.set REG_SIOMULTI3,   REG_BASE + OFFSET_REG_SIOMULTI3

	.set REG_KEYINPUT,    REG_BASE + OFFSET_REG_KEYINPUT
	.set REG_KEYCNT,      REG_BASE + OFFSET_REG_KEYCNT

	.set REG_RCNT,        REG_BASE + OFFSET_REG_RCNT

	.set REG_JOYCNT,      REG_BASE + OFFSET_REG_JOYCNT
	.set REG_JOYSTAT,     REG_BASE + OFFSET_REG_JOYSTAT
	.set REG_JOY_RECV,    REG_BASE + OFFSET_REG_JOY_RECV
	.set REG_JOY_RECV_L,  REG_BASE + OFFSET_REG_JOY_RECV_L
	.set REG_JOY_RECV_H,  REG_BASE + OFFSET_REG_JOY_RECV_H
	.set REG_JOY_TRANS,   REG_BASE + OFFSET_REG_JOY_TRANS
	.set REG_JOY_TRANS_L, REG_BASE + OFFSET_REG_JOY_TRANS_L
	.set REG_JOY_TRANS_H, REG_BASE + OFFSET_REG_JOY_TRANS_H

	.set REG_IME,         REG_BASE + OFFSET_REG_IME
	.set REG_IE,          REG_BASE + OFFSET_REG_IE
	.set REG_IF,          REG_BASE + OFFSET_REG_IF

	.set REG_WAITCNT,     REG_BASE + OFFSET_REG_WAITCNT

@ DMA register constants

	.set DMA_DEST_INC,      0x0000
	.set DMA_DEST_DEC,      0x0020
	.set DMA_DEST_FIXED,    0x0040
	.set DMA_DEST_RELOAD,   0x0060
	.set DMA_SRC_INC,       0x0000
	.set DMA_SRC_DEC,       0x0080
	.set DMA_SRC_FIXED,     0x0100
	.set DMA_REPEAT,        0x0200
	.set DMA_16BIT,         0x0000
	.set DMA_32BIT,         0x0400
	.set DMA_DREQ_ON,       0x0800
	.set DMA_START_NOW,     0x0000
	.set DMA_START_VBLANK,  0x1000
	.set DMA_START_HBLANK,  0x2000
	.set DMA_START_SPECIAL, 0x3000
	.set DMA_INTR_ENABLE,   0x4000
	.set DMA_ENABLE,        0x8000

@ OAM attribute constants

	.set OAM_OBJ_NORMAL,         0x00000000
	.set OAM_OBJ_BLEND,          0x00000400
	.set OAM_OBJ_WINDOW,         0x00000800

	.set OAM_AFFINE_NONE,        0x00000000
	.set OAM_AFFINE_NORMAL_SIZE, 0x00000100
	.set OAM_OBJ_DISABLED,       0x00000200
	.set OAM_AFFINE_DOUBLE_SIZE, 0x00000300

	.set OAM_MOSAIC_OFF,         0x00000000
	.set OAM_MOSAIC_ON,          0x00001000

	.set OAM_4BPP,               0x00000000
	.set OAM_8BPP,               0x00002000

	.set OAM_H_FLIP,             0x10000000
	.set OAM_V_FLIP,             0x20000000

	.set OAM_SQUARE,             0x00000000
	.set OAM_H_RECTANGLE,        0x00004000
	.set OAM_V_RECTANGLE,        0x00008000
	.set OAM_SIZE_0,             0x00000000
	.set OAM_SIZE_1,             0x40000000
	.set OAM_SIZE_2,             0x80000000
	.set OAM_SIZE_3,             0xc0000000

	.set OAM_SIZE_8x8,           OAM_SIZE_0 | OAM_SQUARE
	.set OAM_SIZE_16x16,         OAM_SIZE_1 | OAM_SQUARE
	.set OAM_SIZE_32x32,         OAM_SIZE_2 | OAM_SQUARE
	.set OAM_SIZE_64x64,         OAM_SIZE_3 | OAM_SQUARE

	.set OAM_SIZE_16x8,          OAM_SIZE_0 | OAM_H_RECTANGLE
	.set OAM_SIZE_32x8,          OAM_SIZE_1 | OAM_H_RECTANGLE
	.set OAM_SIZE_32x16,         OAM_SIZE_2 | OAM_H_RECTANGLE
	.set OAM_SIZE_64x32,         OAM_SIZE_3 | OAM_H_RECTANGLE

	.set OAM_SIZE_8x16,          OAM_SIZE_0 | OAM_V_RECTANGLE
	.set OAM_SIZE_8x32,          OAM_SIZE_1 | OAM_V_RECTANGLE
	.set OAM_SIZE_16x32,         OAM_SIZE_2 | OAM_V_RECTANGLE
	.set OAM_SIZE_32x64,         OAM_SIZE_3 | OAM_V_RECTANGLE

@ BLDCNT

	.set BLDCNT_TGT1_BG0,       1 << 0
	.set BLDCNT_TGT1_BG1,       1 << 1
	.set BLDCNT_TGT1_BG2,       1 << 2
	.set BLDCNT_TGT1_BG3,       1 << 3
	.set BLDCNT_TGT1_OBJ,       1 << 4
	.set BLDCNT_TGT1_BD,        1 << 5
	.set BLDCNT_TGT1_ALL,       BLDCNT_TGT1_BG0 | BLDCNT_TGT1_BG1 | BLDCNT_TGT1_BG2 | BLDCNT_TGT1_BG3 | BLDCNT_TGT1_OBJ | BLDCNT_TGT1_BD

	.set BLDCNT_EFFECT_NONE,    0 << 6
	.set BLDCNT_EFFECT_BLEND,   1 << 6
	.set BLDCNT_EFFECT_LIGHTEN, 2 << 6
	.set BLDCNT_EFFECT_DARKEN,  3 << 6

	.set BLDCNT_TGT2_BG0,       1 << 8
	.set BLDCNT_TGT2_BG1,       1 << 9
	.set BLDCNT_TGT2_BG2,       1 << 10
	.set BLDCNT_TGT2_BG3,       1 << 11
	.set BLDCNT_TGT2_OBJ,       1 << 12
	.set BLDCNT_TGT2_BD,        1 << 13
	.set BLDCNT_TGT2_ALL,       BLDCNT_TGT2_BG0 | BLDCNT_TGT2_BG1 | BLDCNT_TGT2_BG2 | BLDCNT_TGT2_BG3 | BLDCNT_TGT2_OBJ | BLDCNT_TGT2_BD
@ ===== END constants/gba_constants.inc =====
@ ===== BEGIN constants/misc_constants.inc =====
	.set TRUE, 1
	.set FALSE, 0

	.set NULL, 0

	.set SPRITE_SIZE_8x8,   (OAM_SIZE_0 >> 28) | (OAM_SQUARE >> 14)
	.set SPRITE_SIZE_16x16, (OAM_SIZE_1 >> 28) | (OAM_SQUARE >> 14)
	.set SPRITE_SIZE_32x32, (OAM_SIZE_2 >> 28) | (OAM_SQUARE >> 14)
	.set SPRITE_SIZE_64x64, (OAM_SIZE_3 >> 28) | (OAM_SQUARE >> 14)

	.set SPRITE_SIZE_16x8,  (OAM_SIZE_0 >> 28) | (OAM_H_RECTANGLE >> 14)
	.set SPRITE_SIZE_32x8,  (OAM_SIZE_1 >> 28) | (OAM_H_RECTANGLE >> 14)
	.set SPRITE_SIZE_32x16, (OAM_SIZE_2 >> 28) | (OAM_H_RECTANGLE >> 14)
	.set SPRITE_SIZE_64x32, (OAM_SIZE_3 >> 28) | (OAM_H_RECTANGLE >> 14)

	.set SPRITE_SIZE_8x16,  (OAM_SIZE_0 >> 28) | (OAM_V_RECTANGLE >> 14)
	.set SPRITE_SIZE_8x32,  (OAM_SIZE_1 >> 28) | (OAM_V_RECTANGLE >> 14)
	.set SPRITE_SIZE_16x32, (OAM_SIZE_2 >> 28) | (OAM_V_RECTANGLE >> 14)
	.set SPRITE_SIZE_32x64, (OAM_SIZE_3 >> 28) | (OAM_V_RECTANGLE >> 14)

	.set OBJ_IMAGE_ANIM_H_FLIP, 1 << 6
	.set OBJ_IMAGE_ANIM_V_FLIP, 1 << 7
@ ===== END constants/misc_constants.inc =====
@ ===== BEGIN constants/version.inc =====
	.ifdef FIRERED
	.equiv GAME_VERSION, 4
	.else
	.equiv GAME_VERSION, 5
	.endif

	.ifdef ENGLISH
	.equiv GAME_LANGUAGE, 2
	.else
	.ifdef GERMAN
	.equiv GAME_LANGUAGE, 5
	.endif
	.endif
@ ===== END constants/version.inc =====
@ ===== END constants/constants.inc =====

    .section .rodata

@ ===== BEGIN data/maps/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/map_groups.json
@

@ ===== BEGIN data/maps/BattleColosseum_2P/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/BattleColosseum_2P/map.json
@

	.align 2

BattleColosseum_2P_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_UNION_ROOM_RECEPTIONIST, 9, 3, 3, MOVEMENT_TYPE_FACE_LEFT, 0, 0, TRAINER_TYPE_NONE, 0, BattleColosseum_2P_EventScript_Attendant, 0

BattleColosseum_2P_MapWarps:
	warp_def 6, 8, 3, WARP_ID_DYNAMIC, MAP_DYNAMIC
	warp_def 7, 8, 3, WARP_ID_DYNAMIC, MAP_DYNAMIC

BattleColosseum_2P_MapCoordEvents:
	coord_event 3, 5, 3, VAR_TEMP_0, 0, BattleColosseum_2P_EventScript_PlayerSpot0
	coord_event 10, 5, 3, VAR_TEMP_0, 0, BattleColosseum_2P_EventScript_PlayerSpot1

BattleColosseum_2P_MapEvents::
	map_events BattleColosseum_2P_ObjectEvents, BattleColosseum_2P_MapWarps, BattleColosseum_2P_MapCoordEvents, NULL

@ ===== END data/maps/BattleColosseum_2P/events.inc =====
@ ===== BEGIN data/maps/TradeCenter/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/TradeCenter/map.json
@

	.align 2

TradeCenter_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_UNION_ROOM_RECEPTIONIST, 9, 6, 3, MOVEMENT_TYPE_FACE_LEFT, 0, 0, TRAINER_TYPE_NONE, 0, TradeCenter_EventScript_Attendant, 0

TradeCenter_MapWarps:
	warp_def 5, 8, 3, WARP_ID_DYNAMIC, MAP_DYNAMIC
	warp_def 6, 8, 3, WARP_ID_DYNAMIC, MAP_DYNAMIC

TradeCenter_MapCoordEvents:
	coord_event 4, 5, 3, VAR_TEMP_0, 0, TradeCenter_EventScript_Chair0
	coord_event 7, 5, 3, VAR_TEMP_0, 0, TradeCenter_EventScript_Chair1

TradeCenter_MapEvents::
	map_events TradeCenter_ObjectEvents, TradeCenter_MapWarps, TradeCenter_MapCoordEvents, NULL

@ ===== END data/maps/TradeCenter/events.inc =====
@ ===== BEGIN data/maps/RecordCorner/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/RecordCorner/map.json
@

	.align 2

RecordCorner_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_UNION_ROOM_RECEPTIONIST, 10, 5, 0, MOVEMENT_TYPE_FACE_DOWN, 0, 0, TRAINER_TYPE_NONE, 0, RecordCorner_EventScript_Attendant, 0

RecordCorner_MapWarps:
	warp_def 8, 9, 3, WARP_ID_DYNAMIC, MAP_DYNAMIC
	warp_def 9, 9, 3, WARP_ID_DYNAMIC, MAP_DYNAMIC
	warp_def 11, 9, 3, WARP_ID_DYNAMIC, MAP_DYNAMIC
	warp_def 10, 9, 3, WARP_ID_DYNAMIC, MAP_DYNAMIC

RecordCorner_MapCoordEvents:
	coord_event 6, 4, 3, VAR_TEMP_0, 0, RecordCorner_EventScript_Spot0
	coord_event 6, 6, 3, VAR_TEMP_0, 0, RecordCorner_EventScript_Spot1
	coord_event 13, 4, 3, VAR_TEMP_0, 0, RecordCorner_EventScript_Spot2
	coord_event 13, 6, 3, VAR_TEMP_0, 0, RecordCorner_EventScript_Spot3

RecordCorner_MapEvents::
	map_events RecordCorner_ObjectEvents, RecordCorner_MapWarps, RecordCorner_MapCoordEvents, NULL

@ ===== END data/maps/RecordCorner/events.inc =====
@ ===== BEGIN data/maps/BattleColosseum_4P/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/BattleColosseum_4P/map.json
@

	.align 2

BattleColosseum_4P_MapWarps:
	warp_def 5, 8, 3, WARP_ID_DYNAMIC, MAP_DYNAMIC
	warp_def 6, 8, 3, WARP_ID_DYNAMIC, MAP_DYNAMIC
	warp_def 7, 8, 3, WARP_ID_DYNAMIC, MAP_DYNAMIC
	warp_def 8, 8, 3, WARP_ID_DYNAMIC, MAP_DYNAMIC

BattleColosseum_4P_MapCoordEvents:
	coord_event 3, 4, 3, VAR_TEMP_0, 0, BattleColosseum_4P_EventScript_PlayerSpot0
	coord_event 3, 6, 3, VAR_TEMP_0, 0, BattleColosseum_4P_EventScript_PlayerSpot2
	coord_event 10, 4, 3, VAR_TEMP_0, 0, BattleColosseum_4P_EventScript_PlayerSpot1
	coord_event 10, 6, 3, VAR_TEMP_0, 0, BattleColosseum_4P_EventScript_PlayerSpot3

BattleColosseum_4P_MapEvents::
	map_events NULL, BattleColosseum_4P_MapWarps, BattleColosseum_4P_MapCoordEvents, NULL

@ ===== END data/maps/BattleColosseum_4P/events.inc =====
@ ===== BEGIN data/maps/UnionRoom/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/UnionRoom/map.json
@

	.align 2

UnionRoom_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_UNION_ROOM_RECEPTIONIST, 3, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 0, 0, TRAINER_TYPE_NONE, 0, UnionRoom_EventScript_Attendant, 0
	object_event 2, OBJ_EVENT_GFX_VAR_3, 1, 8, 3, MOVEMENT_TYPE_WANDER_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, UnionRoom_EventScript_Player4, FLAG_HIDE_UNION_ROOM_PLAYER_4
	object_event 3, OBJ_EVENT_GFX_VAR_7, 7, 8, 3, MOVEMENT_TYPE_WANDER_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, UnionRoom_EventScript_Player8, FLAG_HIDE_UNION_ROOM_PLAYER_8
	object_event 4, OBJ_EVENT_GFX_VAR_6, 1, 4, 3, MOVEMENT_TYPE_WANDER_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, UnionRoom_EventScript_Player7, FLAG_HIDE_UNION_ROOM_PLAYER_7
	object_event 5, OBJ_EVENT_GFX_VAR_5, 7, 4, 3, MOVEMENT_TYPE_WANDER_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, UnionRoom_EventScript_Player6, FLAG_HIDE_UNION_ROOM_PLAYER_6
	object_event 6, OBJ_EVENT_GFX_VAR_4, 13, 4, 3, MOVEMENT_TYPE_WANDER_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, UnionRoom_EventScript_Player5, FLAG_HIDE_UNION_ROOM_PLAYER_5
	object_event 7, OBJ_EVENT_GFX_VAR_2, 10, 6, 3, MOVEMENT_TYPE_WANDER_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, UnionRoom_EventScript_Player3, FLAG_HIDE_UNION_ROOM_PLAYER_3
	object_event 8, OBJ_EVENT_GFX_VAR_1, 13, 8, 3, MOVEMENT_TYPE_WANDER_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, UnionRoom_EventScript_Player2, FLAG_HIDE_UNION_ROOM_PLAYER_2
	object_event 9, OBJ_EVENT_GFX_VAR_0, 4, 6, 3, MOVEMENT_TYPE_WANDER_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, UnionRoom_EventScript_Player1, FLAG_HIDE_UNION_ROOM_PLAYER_1

UnionRoom_MapWarps:
	warp_def 7, 11, 3, WARP_ID_DYNAMIC, MAP_DYNAMIC

UnionRoom_MapEvents::
	map_events UnionRoom_ObjectEvents, UnionRoom_MapWarps, NULL, NULL

@ ===== END data/maps/UnionRoom/events.inc =====
@ ===== BEGIN data/maps/ViridianForest/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/ViridianForest/map.json
@

	.align 2

ViridianForest_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_YOUNGSTER, 29, 58, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NONE, 0, ViridianForest_EventScript_Youngster, 0
	object_event 2, OBJ_EVENT_GFX_BOY, 45, 58, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NONE, 0, ViridianForest_EventScript_Boy, 0
	object_event 3, OBJ_EVENT_GFX_BUG_CATCHER, 47, 45, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NORMAL, 5, ViridianForest_EventScript_Rick, 0
	object_event 4, OBJ_EVENT_GFX_BUG_CATCHER, 47, 29, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NORMAL, 4, ViridianForest_EventScript_Doug, 0
	object_event 5, OBJ_EVENT_GFX_BUG_CATCHER, 7, 22, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NORMAL, 4, ViridianForest_EventScript_Sammy, 0
	object_event 6, OBJ_EVENT_GFX_ITEM_BALL, 5, 41, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, ViridianForest_EventScript_ItemPokeBall, FLAG_HIDE_VIRIDIAN_FOREST_POKE_BALL
	object_event 7, OBJ_EVENT_GFX_ITEM_BALL, 40, 21, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, ViridianForest_EventScript_ItemAntidote, FLAG_HIDE_VIRIDIAN_FOREST_ANTIDOTE
	object_event 8, OBJ_EVENT_GFX_ITEM_BALL, 21, 34, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, ViridianForest_EventScript_ItemPotion, FLAG_HIDE_VIRIDIAN_FOREST_POTION
	object_event 9, OBJ_EVENT_GFX_BUG_CATCHER, 43, 6, 3, MOVEMENT_TYPE_FACE_DOWN_AND_UP, 1, 1, TRAINER_TYPE_NORMAL, 1, ViridianForest_EventScript_Anthony, 0
	object_event 10, OBJ_EVENT_GFX_BUG_CATCHER, 16, 5, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NORMAL, 1, ViridianForest_EventScript_Charlie, 0
	object_event 11, OBJ_EVENT_GFX_ITEM_BALL, 49, 60, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, ViridianForest_EventScript_ItemPotion2, FLAG_HIDE_VIRIDIAN_FOREST_POTION_2

ViridianForest_MapWarps:
	warp_def 29, 62, 3, 3, MAP_ROUTE2_VIRIDIAN_FOREST_SOUTH_ENTRANCE
	warp_def 28, 62, 3, 3, MAP_ROUTE2_VIRIDIAN_FOREST_SOUTH_ENTRANCE
	warp_def 5, 9, 3, 1, MAP_ROUTE2_VIRIDIAN_FOREST_NORTH_ENTRANCE
	warp_def 6, 9, 3, 1, MAP_ROUTE2_VIRIDIAN_FOREST_NORTH_ENTRANCE
	warp_def 30, 62, 3, 3, MAP_ROUTE2_VIRIDIAN_FOREST_SOUTH_ENTRANCE
	warp_def 4, 9, 3, 1, MAP_ROUTE2_VIRIDIAN_FOREST_NORTH_ENTRANCE

ViridianForest_MapBGEvents:
	bg_sign_event 39, 59, 3, BG_EVENT_PLAYER_FACING_ANY, ViridianForest_EventScript_TrainerTips1
	bg_sign_event 43, 26, 0, BG_EVENT_PLAYER_FACING_ANY, ViridianForest_EventScript_TrainerTips3
	bg_sign_event 9, 29, 0, BG_EVENT_PLAYER_FACING_ANY, ViridianForest_EventScript_TrainerTips4
	bg_sign_event 6, 12, 0, BG_EVENT_PLAYER_FACING_ANY, ViridianForest_EventScript_ExitSign
	bg_sign_event 28, 44, 0, BG_EVENT_PLAYER_FACING_ANY, ViridianForest_EventScript_TrainerTips2
	bg_sign_event 31, 60, 0, BG_EVENT_PLAYER_FACING_ANY, ViridianForest_EventScript_TrainerTips5
	bg_hidden_item_event 3, 22, 3, ITEM_POTION, FLAG_HIDDEN_ITEM_VIRIDIAN_FOREST_POTION, 1, FALSE
	bg_hidden_item_event 28, 57, 0, ITEM_ANTIDOTE, FLAG_HIDDEN_ITEM_VIRIDIAN_FOREST_ANTIDOTE, 1, FALSE

ViridianForest_MapEvents::
	map_events ViridianForest_ObjectEvents, ViridianForest_MapWarps, NULL, ViridianForest_MapBGEvents

@ ===== END data/maps/ViridianForest/events.inc =====
@ ===== BEGIN data/maps/MtMoon_1F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/MtMoon_1F/map.json
@

	.align 2

MtMoon_1F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_LASS, 20, 26, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 2, MtMoon_1F_EventScript_Iris, 0
	object_event 2, OBJ_EVENT_GFX_BUG_CATCHER, 36, 30, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 2, MtMoon_1F_EventScript_Robby, 0
	object_event 3, OBJ_EVENT_GFX_SCIENTIST, 30, 35, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NORMAL, 4, MtMoon_1F_EventScript_Jovan, 0
	object_event 4, OBJ_EVENT_GFX_LASS, 33, 4, 3, MOVEMENT_TYPE_WALK_SEQUENCE_LEFT_DOWN_RIGHT_UP, 5, 3, TRAINER_TYPE_NORMAL, 2, MtMoon_1F_EventScript_Miriam, 0
	object_event 5, OBJ_EVENT_GFX_BUG_CATCHER, 7, 26, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 4, MtMoon_1F_EventScript_Kent, 0
	object_event 6, OBJ_EVENT_GFX_YOUNGSTER, 13, 17, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 4, MtMoon_1F_EventScript_Josh, 0
	object_event 7, OBJ_EVENT_GFX_HIKER, 7, 10, 3, MOVEMENT_TYPE_WANDER_AROUND, 2, 2, TRAINER_TYPE_NORMAL, 1, MtMoon_1F_EventScript_Marcos, 0
	object_event 8, OBJ_EVENT_GFX_ITEM_BALL, 2, 22, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, MtMoon_1F_EventScript_ItemParalyzeHeal, FLAG_HIDE_MT_MOON_1F_PARALYZE_HEAL
	object_event 9, OBJ_EVENT_GFX_ITEM_BALL, 11, 35, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, MtMoon_1F_EventScript_ItemTM09, FLAG_HIDE_MT_MOON_1F_TM09
	object_event 10, OBJ_EVENT_GFX_ITEM_BALL, 26, 32, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, MtMoon_1F_EventScript_ItemPotion, FLAG_HIDE_MT_MOON_1F_POTION
	object_event 11, OBJ_EVENT_GFX_ITEM_BALL, 42, 35, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, MtMoon_1F_EventScript_ItemRareCandy, FLAG_HIDE_MT_MOON_1F_RARE_CANDY
	object_event 12, OBJ_EVENT_GFX_ITEM_BALL, 44, 21, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, MtMoon_1F_EventScript_ItemEscapeRope, FLAG_HIDE_MT_MOON_1F_ESCAPE_ROPE
	object_event 13, OBJ_EVENT_GFX_ITEM_BALL, 3, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, MtMoon_1F_EventScript_ItemMoonStone, FLAG_HIDE_MT_MOON_1F_MOON_STONE
	object_event 14, OBJ_EVENT_GFX_BALDING_MAN, 42, 7, 3, MOVEMENT_TYPE_FACE_DOWN_AND_LEFT, 1, 1, TRAINER_TYPE_NONE, 0, MtMoon_1F_EventScript_BaldingMan, 0

MtMoon_1F_MapWarps:
	warp_def 5, 6, 3, 0, MAP_MT_MOON_B1F
	warp_def 19, 14, 3, 1, MAP_MT_MOON_B1F
	warp_def 31, 16, 3, 2, MAP_MT_MOON_B1F
	warp_def 18, 37, 3, 0, MAP_ROUTE4

MtMoon_1F_MapBGEvents:
	bg_sign_event 19, 26, 0, BG_EVENT_PLAYER_FACING_ANY, MtMoon_1F_EventScript_ZubatSign

MtMoon_1F_MapEvents::
	map_events MtMoon_1F_ObjectEvents, MtMoon_1F_MapWarps, NULL, MtMoon_1F_MapBGEvents

@ ===== END data/maps/MtMoon_1F/events.inc =====
@ ===== BEGIN data/maps/MtMoon_B1F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/MtMoon_B1F/map.json
@

	.align 2

MtMoon_B1F_MapWarps:
	warp_def 3, 3, 3, 0, MAP_MT_MOON_1F
	warp_def 25, 4, 3, 1, MAP_MT_MOON_1F
	warp_def 43, 21, 3, 2, MAP_MT_MOON_1F
	warp_def 22, 18, 3, 0, MAP_MT_MOON_B2F
	warp_def 17, 5, 3, 1, MAP_MT_MOON_B2F
	warp_def 26, 36, 3, 2, MAP_MT_MOON_B2F
	warp_def 39, 4, 3, 3, MAP_MT_MOON_B2F
	warp_def 45, 4, 3, 1, MAP_ROUTE4

MtMoon_B1F_MapBGEvents:
	bg_hidden_item_event 46, 2, 0, ITEM_TINY_MUSHROOM, FLAG_HIDDEN_ITEM_MT_MOON_B1F_TINY_MUSHROOM, 1, FALSE
	bg_hidden_item_event 26, 2, 0, ITEM_TINY_MUSHROOM, FLAG_HIDDEN_ITEM_MT_MOON_B1F_TINY_MUSHROOM_2, 1, FALSE
	bg_hidden_item_event 39, 34, 0, ITEM_TINY_MUSHROOM, FLAG_HIDDEN_ITEM_MT_MOON_B1F_TINY_MUSHROOM_3, 1, FALSE
	bg_hidden_item_event 24, 35, 0, ITEM_BIG_MUSHROOM, FLAG_HIDDEN_ITEM_MT_MOON_B1F_BIG_MUSHROOM, 1, FALSE
	bg_hidden_item_event 6, 12, 0, ITEM_BIG_MUSHROOM, FLAG_HIDDEN_ITEM_MT_MOON_B1F_BIG_MUSHROOM_2, 1, FALSE
	bg_hidden_item_event 25, 34, 0, ITEM_BIG_MUSHROOM, FLAG_HIDDEN_ITEM_MT_MOON_B1F_BIG_MUSHROOM_3, 1, FALSE

MtMoon_B1F_MapEvents::
	map_events NULL, MtMoon_B1F_MapWarps, NULL, MtMoon_B1F_MapBGEvents

@ ===== END data/maps/MtMoon_B1F/events.inc =====
@ ===== BEGIN data/maps/MtMoon_B2F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/MtMoon_B2F/map.json
@

	.align 2

MtMoon_B2F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_FOSSIL, 13, 7, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, MtMoon_B2F_EventScript_DomeFossil, FLAG_HIDE_DOME_FOSSIL
	object_event 2, OBJ_EVENT_GFX_FOSSIL, 14, 7, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, MtMoon_B2F_EventScript_HelixFossil, FLAG_HIDE_HELIX_FOSSIL
	object_event 3, OBJ_EVENT_GFX_SCIENTIST, 13, 11, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, MtMoon_B2F_EventScript_Miguel, 0
	object_event 4, OBJ_EVENT_GFX_ROCKET_M, 37, 21, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NORMAL, 3, MtMoon_B2F_EventScript_Grunt4, FLAG_HIDE_MISC_KANTO_ROCKETS
	object_event 5, OBJ_EVENT_GFX_ROCKET_M, 12, 20, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 2, MtMoon_B2F_EventScript_Grunt1, FLAG_HIDE_MISC_KANTO_ROCKETS
	object_event 6, OBJ_EVENT_GFX_ROCKET_M, 35, 12, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NORMAL, 4, MtMoon_B2F_EventScript_Grunt3, FLAG_HIDE_MISC_KANTO_ROCKETS
	object_event 7, OBJ_EVENT_GFX_ROCKET_M, 18, 27, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 4, MtMoon_B2F_EventScript_Grunt2, FLAG_HIDE_MISC_KANTO_ROCKETS
	object_event 8, OBJ_EVENT_GFX_ITEM_BALL, 30, 26, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, MtMoon_B2F_EventScript_ItemStarPiece, FLAG_HIDE_MT_MOON_B2F_STAR_PIECE
	object_event 9, OBJ_EVENT_GFX_ITEM_BALL, 35, 5, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, MtMoon_B2F_EventScript_ItemTM46, FLAG_HIDE_MT_MOON_B2F_TM46
	object_event 10, OBJ_EVENT_GFX_ITEM_BALL, 24, 6, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, MtMoon_B2F_EventScript_ItemRevive, FLAG_HIDE_MT_MOON_B2F_REVIVE
	object_event 11, OBJ_EVENT_GFX_ITEM_BALL, 3, 11, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, MtMoon_B2F_EventScript_ItemAntidote, FLAG_HIDE_MT_MOON_B2F_ANTIDOTE

MtMoon_B2F_MapWarps:
	warp_def 25, 21, 3, 3, MAP_MT_MOON_B1F
	warp_def 31, 11, 3, 4, MAP_MT_MOON_B1F
	warp_def 17, 31, 3, 5, MAP_MT_MOON_B1F
	warp_def 5, 10, 3, 6, MAP_MT_MOON_B1F

MtMoon_B2F_MapCoordEvents:
	coord_event 14, 11, 3, VAR_MAP_SCENE_MT_MOON_B2F, 0, MtMoon_B2F_EventScript_MiguelTrigger

MtMoon_B2F_MapBGEvents:
	bg_hidden_item_event 20, 16, 3, ITEM_MOON_STONE, FLAG_HIDDEN_ITEM_MT_MOON_B2F_MOON_STONE, 1, FALSE
	bg_hidden_item_event 39, 11, 3, ITEM_ETHER, FLAG_HIDDEN_ITEM_MT_MOON_B2F_ETHER, 1, FALSE

MtMoon_B2F_MapEvents::
	map_events MtMoon_B2F_ObjectEvents, MtMoon_B2F_MapWarps, MtMoon_B2F_MapCoordEvents, MtMoon_B2F_MapBGEvents

@ ===== END data/maps/MtMoon_B2F/events.inc =====
@ ===== BEGIN data/maps/SSAnne_Exterior/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SSAnne_Exterior/map.json
@

	.align 2

SSAnne_Exterior_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_SS_ANNE, 30, 16, 1, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, 0x0, FLAG_HIDE_SS_ANNE

SSAnne_Exterior_MapWarps:
	warp_def 31, 5, 0, 0, MAP_VERMILION_CITY
	warp_def 32, 5, 3, 1, MAP_VERMILION_CITY
	warp_def 32, 14, 3, 2, MAP_SSANNE_1F_CORRIDOR
	warp_def 33, 15, 0, 3, MAP_SSANNE_1F_CORRIDOR
	warp_def 33, 5, 0, 2, MAP_VERMILION_CITY

SSAnne_Exterior_MapBGEvents:
	bg_hidden_item_event 58, 28, 3, ITEM_LAVA_COOKIE, FLAG_HIDDEN_ITEM_SSANNE_EXTERIOR_LAVA_COOKIE, 1, FALSE

SSAnne_Exterior_MapEvents::
	map_events SSAnne_Exterior_ObjectEvents, SSAnne_Exterior_MapWarps, NULL, SSAnne_Exterior_MapBGEvents

@ ===== END data/maps/SSAnne_Exterior/events.inc =====
@ ===== BEGIN data/maps/SSAnne_1F_Corridor/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SSAnne_1F_Corridor/map.json
@

	.align 2

SSAnne_1F_Corridor_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_SAILOR, 18, 8, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NONE, 0, SSAnne_1F_Corridor_EventScript_Sailor, 0
	object_event 2, OBJ_EVENT_GFX_WORKER_M, 12, 9, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SSAnne_1F_Corridor_EventScript_WorkerM, 0

SSAnne_1F_Corridor_MapWarps:
	warp_def 3, 8, 3, 0, MAP_SSANNE_2F_CORRIDOR
	warp_def 2, 18, 3, 0, MAP_SSANNE_KITCHEN
	warp_def 19, 1, 3, 2, MAP_SSANNE_EXTERIOR
	warp_def 20, 0, 0, 3, MAP_SSANNE_EXTERIOR
	warp_def 3, 20, 0, 0, MAP_SSANNE_KITCHEN
	warp_def 28, 17, 3, 0, MAP_SSANNE_B1F_CORRIDOR
	warp_def 5, 10, 3, 0, MAP_SSANNE_1F_ROOM1
	warp_def 8, 10, 3, 0, MAP_SSANNE_1F_ROOM2
	warp_def 11, 10, 3, 0, MAP_SSANNE_1F_ROOM3
	warp_def 14, 10, 3, 0, MAP_SSANNE_1F_ROOM4
	warp_def 17, 10, 3, 0, MAP_SSANNE_1F_ROOM5
	warp_def 23, 10, 3, 0, MAP_SSANNE_1F_ROOM7
	warp_def 20, 10, 3, 0, MAP_SSANNE_1F_ROOM6

SSAnne_1F_Corridor_MapEvents::
	map_events SSAnne_1F_Corridor_ObjectEvents, SSAnne_1F_Corridor_MapWarps, NULL, NULL

@ ===== END data/maps/SSAnne_1F_Corridor/events.inc =====
@ ===== BEGIN data/maps/SSAnne_2F_Corridor/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SSAnne_2F_Corridor/map.json
@

	.align 2

SSAnne_2F_Corridor_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_BLUE, 30, 2, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NONE, 0, 0x0, FLAG_HIDE_SS_ANNE_RIVAL
	object_event 2, OBJ_EVENT_GFX_SAILOR, 2, 7, 3, MOVEMENT_TYPE_WANDER_UP_AND_DOWN, 1, 2, TRAINER_TYPE_NONE, 0, SSAnne_2F_Corridor_EventScript_Sailor, 0

SSAnne_2F_Corridor_MapWarps:
	warp_def 2, 2, 3, 0, MAP_SSANNE_1F_CORRIDOR
	warp_def 3, 12, 3, 1, MAP_SSANNE_3F_CORRIDOR
	warp_def 30, 2, 3, 0, MAP_SSANNE_CAPTAINS_OFFICE
	warp_def 6, 10, 0, 0, MAP_SSANNE_2F_ROOM1
	warp_def 10, 10, 0, 0, MAP_SSANNE_2F_ROOM2
	warp_def 14, 10, 0, 0, MAP_SSANNE_2F_ROOM3
	warp_def 18, 10, 0, 0, MAP_SSANNE_2F_ROOM4
	warp_def 22, 10, 0, 0, MAP_SSANNE_2F_ROOM5
	warp_def 26, 10, 0, 0, MAP_SSANNE_2F_ROOM6

SSAnne_2F_Corridor_MapCoordEvents:
	coord_event 30, 6, 3, VAR_MAP_SCENE_S_S_ANNE_2F_CORRIDOR, 0, SSAnne_2F_Corridor_EventScript_RivalTriggerLeft
	coord_event 31, 6, 3, VAR_MAP_SCENE_S_S_ANNE_2F_CORRIDOR, 0, SSAnne_2F_Corridor_EventScript_RivalTriggerMid
	coord_event 32, 6, 3, VAR_MAP_SCENE_S_S_ANNE_2F_CORRIDOR, 0, SSAnne_2F_Corridor_EventScript_RivalTriggerRight

SSAnne_2F_Corridor_MapEvents::
	map_events SSAnne_2F_Corridor_ObjectEvents, SSAnne_2F_Corridor_MapWarps, SSAnne_2F_Corridor_MapCoordEvents, NULL

@ ===== END data/maps/SSAnne_2F_Corridor/events.inc =====
@ ===== BEGIN data/maps/SSAnne_3F_Corridor/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SSAnne_3F_Corridor/map.json
@

	.align 2

SSAnne_3F_Corridor_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_SAILOR, 10, 4, 3, MOVEMENT_TYPE_WANDER_LEFT_AND_RIGHT, 3, 1, TRAINER_TYPE_NONE, 0, SSAnne_3F_Corridor_EventScript_Sailor, 0

SSAnne_3F_Corridor_MapWarps:
	warp_def 1, 4, 3, 0, MAP_SSANNE_DECK
	warp_def 18, 2, 3, 1, MAP_SSANNE_2F_CORRIDOR
	warp_def 0, 5, 0, 0, MAP_SSANNE_DECK

SSAnne_3F_Corridor_MapEvents::
	map_events SSAnne_3F_Corridor_ObjectEvents, SSAnne_3F_Corridor_MapWarps, NULL, NULL

@ ===== END data/maps/SSAnne_3F_Corridor/events.inc =====
@ ===== BEGIN data/maps/SSAnne_B1F_Corridor/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SSAnne_B1F_Corridor/map.json
@

	.align 2

SSAnne_B1F_Corridor_MapWarps:
	warp_def 19, 3, 3, 5, MAP_SSANNE_1F_CORRIDOR
	warp_def 2, 2, 0, 0, MAP_SSANNE_B1F_ROOM1
	warp_def 6, 2, 0, 0, MAP_SSANNE_B1F_ROOM2
	warp_def 10, 2, 0, 0, MAP_SSANNE_B1F_ROOM3
	warp_def 14, 2, 0, 0, MAP_SSANNE_B1F_ROOM4
	warp_def 18, 2, 0, 0, MAP_SSANNE_B1F_ROOM5

SSAnne_B1F_Corridor_MapBGEvents:
	bg_hidden_item_event 21, 5, 3, ITEM_HYPER_POTION, FLAG_HIDDEN_ITEM_SSANNE_B1F_CORRIDOR_HYPER_POTION, 1, FALSE

SSAnne_B1F_Corridor_MapEvents::
	map_events NULL, SSAnne_B1F_Corridor_MapWarps, NULL, SSAnne_B1F_Corridor_MapBGEvents

@ ===== END data/maps/SSAnne_B1F_Corridor/events.inc =====
@ ===== BEGIN data/maps/SSAnne_Deck/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SSAnne_Deck/map.json
@

	.align 2

SSAnne_Deck_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_SAILOR, 12, 10, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NORMAL, 2, SSAnne_Deck_EventScript_Trevor, 0
	object_event 2, OBJ_EVENT_GFX_BALDING_MAN, 14, 11, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SSAnne_Deck_EventScript_BaldingMan, 0
	object_event 3, OBJ_EVENT_GFX_SAILOR, 13, 13, 3, MOVEMENT_TYPE_WALK_LEFT_AND_RIGHT, 4, 1, TRAINER_TYPE_NONE, 0, SSAnne_Deck_EventScript_Sailor, 0
	object_event 4, OBJ_EVENT_GFX_SAILOR, 6, 9, 3, MOVEMENT_TYPE_WANDER_AROUND, 1, 1, TRAINER_TYPE_NORMAL, 1, SSAnne_Deck_EventScript_Edmond, 0
	object_event 5, OBJ_EVENT_GFX_YOUNGSTER, 11, 5, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NONE, 0, SSAnne_Deck_EventScript_Youngster, 0

SSAnne_Deck_MapWarps:
	warp_def 16, 8, 3, 0, MAP_SSANNE_3F_CORRIDOR
	warp_def 16, 9, 3, 0, MAP_SSANNE_3F_CORRIDOR

SSAnne_Deck_MapEvents::
	map_events SSAnne_Deck_ObjectEvents, SSAnne_Deck_MapWarps, NULL, NULL

@ ===== END data/maps/SSAnne_Deck/events.inc =====
@ ===== BEGIN data/maps/SSAnne_Kitchen/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SSAnne_Kitchen/map.json
@

	.align 2

SSAnne_Kitchen_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_CHEF, 1, 5, 3, MOVEMENT_TYPE_WANDER_UP_AND_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SSAnne_Kitchen_EventScript_Chef1, 0
	object_event 2, OBJ_EVENT_GFX_CHEF, 6, 6, 3, MOVEMENT_TYPE_WANDER_UP_AND_DOWN, 1, 2, TRAINER_TYPE_NONE, 0, SSAnne_Kitchen_EventScript_Chef2, 0
	object_event 3, OBJ_EVENT_GFX_CHEF, 10, 4, 3, MOVEMENT_TYPE_FACE_DOWN_AND_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, SSAnne_Kitchen_EventScript_Chef3, 0
	object_event 4, OBJ_EVENT_GFX_CHEF, 8, 9, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NONE, 0, SSAnne_Kitchen_EventScript_Chef4, 0
	object_event 5, OBJ_EVENT_GFX_CHEF, 14, 5, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NONE, 0, SSAnne_Kitchen_EventScript_Chef5, 0
	object_event 6, OBJ_EVENT_GFX_CHEF, 14, 7, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NONE, 0, SSAnne_Kitchen_EventScript_Chef6, 0
	object_event 7, OBJ_EVENT_GFX_CHEF, 14, 9, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NONE, 0, SSAnne_Kitchen_EventScript_Chef7, 0
	object_event 8, OBJ_EVENT_GFX_ITEM_BALL, 1, 10, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SSAnne_Kitchen_EventScript_ItemGreatBall, FLAG_HIDE_SSANNE_KITCHEN_GREAT_BALL

SSAnne_Kitchen_MapWarps:
	warp_def 7, 1, 0, 1, MAP_SSANNE_1F_CORRIDOR

SSAnne_Kitchen_MapBGEvents:
	bg_hidden_item_event 14, 8, 0, ITEM_CHESTO_BERRY, FLAG_HIDDEN_ITEM_SSANNE_KITCHEN_CHESTO_BERRY, 1, FALSE
	bg_hidden_item_event 14, 4, 0, ITEM_PECHA_BERRY, FLAG_HIDDEN_ITEM_SSANNE_KITCHEN_PECHA_BERRY, 1, FALSE
	bg_hidden_item_event 14, 6, 0, ITEM_CHERI_BERRY, FLAG_HIDDEN_ITEM_SSANNE_KITCHEN_CHERI_BERRY, 1, FALSE

SSAnne_Kitchen_MapEvents::
	map_events SSAnne_Kitchen_ObjectEvents, SSAnne_Kitchen_MapWarps, NULL, SSAnne_Kitchen_MapBGEvents

@ ===== END data/maps/SSAnne_Kitchen/events.inc =====
@ ===== BEGIN data/maps/SSAnne_CaptainsOffice/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SSAnne_CaptainsOffice/map.json
@

	.align 2

SSAnne_CaptainsOffice_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_CAPTAIN, 5, 4, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NONE, 0, SSAnne_CaptainsOffice_EventScript_Captain, 0

SSAnne_CaptainsOffice_MapWarps:
	warp_def 3, 7, 3, 2, MAP_SSANNE_2F_CORRIDOR

SSAnne_CaptainsOffice_MapBGEvents:
	bg_sign_event 2, 4, 0, BG_EVENT_PLAYER_FACING_ANY, SSAnne_CaptainsOffice_EventScript_Book
	bg_sign_event 5, 3, 0, BG_EVENT_PLAYER_FACING_ANY, SSAnne_CaptainsOffice_EventScript_TrashCan
	bg_sign_event 2, 3, 0, BG_EVENT_PLAYER_FACING_ANY, SSAnne_CaptainsOffice_EventScript_Book

SSAnne_CaptainsOffice_MapEvents::
	map_events SSAnne_CaptainsOffice_ObjectEvents, SSAnne_CaptainsOffice_MapWarps, NULL, SSAnne_CaptainsOffice_MapBGEvents

@ ===== END data/maps/SSAnne_CaptainsOffice/events.inc =====
@ ===== BEGIN data/maps/SSAnne_1F_Room1/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SSAnne_1F_Room1/map.json
@

	.align 2

SSAnne_1F_Room1_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_GENTLEMAN, 2, 5, 3, MOVEMENT_TYPE_WANDER_LEFT_AND_RIGHT, 2, 1, TRAINER_TYPE_NONE, 0, SSAnne_1F_Room1_EventScript_Gentleman, 0

SSAnne_1F_Room1_MapWarps:
	warp_def 2, 1, 0, 6, MAP_SSANNE_1F_CORRIDOR

SSAnne_1F_Room1_MapEvents::
	map_events SSAnne_1F_Room1_ObjectEvents, SSAnne_1F_Room1_MapWarps, NULL, NULL

@ ===== END data/maps/SSAnne_1F_Room1/events.inc =====
@ ===== BEGIN data/maps/SSAnne_1F_Room2/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SSAnne_1F_Room2/map.json
@

	.align 2

SSAnne_1F_Room2_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_LASS, 5, 3, 3, MOVEMENT_TYPE_FACE_DOWN_AND_LEFT, 1, 1, TRAINER_TYPE_NORMAL, 2, SSAnne_1F_Room2_EventScript_Ann, 0
	object_event 2, OBJ_EVENT_GFX_YOUNGSTER, 0, 4, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 3, SSAnne_1F_Room2_EventScript_Tyler, 0
	object_event 3, OBJ_EVENT_GFX_WOMAN_2, 2, 6, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NONE, 1, SSAnne_1F_Room2_EventScript_Woman, 0
	object_event 4, OBJ_EVENT_GFX_ITEM_BALL, 5, 7, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SSAnne_1F_Room2_EventScript_ItemTM31, FLAG_HIDE_SSANNE_1F_ROOM2_TM31

SSAnne_1F_Room2_MapWarps:
	warp_def 2, 1, 0, 7, MAP_SSANNE_1F_CORRIDOR

SSAnne_1F_Room2_MapEvents::
	map_events SSAnne_1F_Room2_ObjectEvents, SSAnne_1F_Room2_MapWarps, NULL, NULL

@ ===== END data/maps/SSAnne_1F_Room2/events.inc =====
@ ===== BEGIN data/maps/SSAnne_1F_Room3/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SSAnne_1F_Room3/map.json
@

	.align 2

SSAnne_1F_Room3_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_LITTLE_GIRL, 3, 4, 3, MOVEMENT_TYPE_WALK_SEQUENCE_RIGHT_DOWN_LEFT_UP, 2, 3, TRAINER_TYPE_NONE, 0, SSAnne_1F_Room3_EventScript_LittleGirl, 0
	object_event 2, OBJ_EVENT_GFX_WIGGLYTUFF, 4, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SSAnne_1F_Room3_EventScript_Wigglytuff, 0
	object_event 3, OBJ_EVENT_GFX_BALDING_MAN, 0, 4, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, SSAnne_1F_Room3_EventScript_BaldingMan, 0

SSAnne_1F_Room3_MapWarps:
	warp_def 2, 1, 0, 8, MAP_SSANNE_1F_CORRIDOR

SSAnne_1F_Room3_MapEvents::
	map_events SSAnne_1F_Room3_ObjectEvents, SSAnne_1F_Room3_MapWarps, NULL, NULL

@ ===== END data/maps/SSAnne_1F_Room3/events.inc =====
@ ===== BEGIN data/maps/SSAnne_1F_Room4/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SSAnne_1F_Room4/map.json
@

	.align 2

SSAnne_1F_Room4_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_WOMAN_1, 2, 4, 3, MOVEMENT_TYPE_WANDER_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, SSAnne_1F_Room4_EventScript_Woman, 0

SSAnne_1F_Room4_MapWarps:
	warp_def 2, 1, 0, 9, MAP_SSANNE_1F_CORRIDOR

SSAnne_1F_Room4_MapEvents::
	map_events SSAnne_1F_Room4_ObjectEvents, SSAnne_1F_Room4_MapWarps, NULL, NULL

@ ===== END data/maps/SSAnne_1F_Room4/events.inc =====
@ ===== BEGIN data/maps/SSAnne_1F_Room5/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SSAnne_1F_Room5/map.json
@

	.align 2

SSAnne_1F_Room5_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_GENTLEMAN, 2, 6, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NORMAL, 4, SSAnne_1F_Room5_EventScript_Arthur, 0

SSAnne_1F_Room5_MapWarps:
	warp_def 2, 1, 0, 10, MAP_SSANNE_1F_CORRIDOR

SSAnne_1F_Room5_MapEvents::
	map_events SSAnne_1F_Room5_ObjectEvents, SSAnne_1F_Room5_MapWarps, NULL, NULL

@ ===== END data/maps/SSAnne_1F_Room5/events.inc =====
@ ===== BEGIN data/maps/SSAnne_1F_Room7/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SSAnne_1F_Room7/map.json
@

	.align 2

SSAnne_1F_Room7_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_GENTLEMAN, 4, 3, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NORMAL, 3, SSAnne_1F_Room7_EventScript_Thomas, 0

SSAnne_1F_Room7_MapWarps:
	warp_def 2, 1, 0, 11, MAP_SSANNE_1F_CORRIDOR

SSAnne_1F_Room7_MapEvents::
	map_events SSAnne_1F_Room7_ObjectEvents, SSAnne_1F_Room7_MapWarps, NULL, NULL

@ ===== END data/maps/SSAnne_1F_Room7/events.inc =====
@ ===== BEGIN data/maps/SSAnne_2F_Room1/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SSAnne_2F_Room1/map.json
@

	.align 2

SSAnne_2F_Room1_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_GENTLEMAN, 1, 4, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NONE, 0, SSAnne_2F_Room1_EventScript_Gentleman, 0

SSAnne_2F_Room1_MapWarps:
	warp_def 4, 7, 3, 3, MAP_SSANNE_2F_CORRIDOR

SSAnne_2F_Room1_MapEvents::
	map_events SSAnne_2F_Room1_ObjectEvents, SSAnne_2F_Room1_MapWarps, NULL, NULL

@ ===== END data/maps/SSAnne_2F_Room1/events.inc =====
@ ===== BEGIN data/maps/SSAnne_2F_Room2/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SSAnne_2F_Room2/map.json
@

	.align 2

SSAnne_2F_Room2_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_FISHER, 5, 5, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NORMAL, 3, SSAnne_2F_Room2_EventScript_Dale, 0
	object_event 2, OBJ_EVENT_GFX_GENTLEMAN, 1, 4, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 2, SSAnne_2F_Room2_EventScript_Brooks, 0
	object_event 3, OBJ_EVENT_GFX_ITEM_BALL, 3, 3, 0, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SSAnne_2F_Room2_EventScript_ItemStardust, FLAG_HIDE_SSANNE_2F_ROOM2_STARDUST

SSAnne_2F_Room2_MapWarps:
	warp_def 4, 7, 3, 4, MAP_SSANNE_2F_CORRIDOR

SSAnne_2F_Room2_MapEvents::
	map_events SSAnne_2F_Room2_ObjectEvents, SSAnne_2F_Room2_MapWarps, NULL, NULL

@ ===== END data/maps/SSAnne_2F_Room2/events.inc =====
@ ===== BEGIN data/maps/SSAnne_2F_Room3/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SSAnne_2F_Room3/map.json
@

	.align 2

SSAnne_2F_Room3_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_GENTLEMAN, 2, 5, 3, MOVEMENT_TYPE_WANDER_LEFT_AND_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, SSAnne_2F_Room3_EventScript_Gentleman, 0
	object_event 2, OBJ_EVENT_GFX_OLD_MAN_1, 3, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SSAnne_2F_Room3_EventScript_OldMan, 0

SSAnne_2F_Room3_MapWarps:
	warp_def 4, 7, 3, 5, MAP_SSANNE_2F_CORRIDOR

SSAnne_2F_Room3_MapEvents::
	map_events SSAnne_2F_Room3_ObjectEvents, SSAnne_2F_Room3_MapWarps, NULL, NULL

@ ===== END data/maps/SSAnne_2F_Room3/events.inc =====
@ ===== BEGIN data/maps/SSAnne_2F_Room4/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SSAnne_2F_Room4/map.json
@

	.align 2

SSAnne_2F_Room4_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_GENTLEMAN, 0, 5, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 3, SSAnne_2F_Room4_EventScript_Lamar, 0
	object_event 2, OBJ_EVENT_GFX_LASS, 3, 3, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 3, SSAnne_2F_Room4_EventScript_Dawn, 0
	object_event 3, OBJ_EVENT_GFX_ITEM_BALL, 2, 4, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SSAnne_2F_Room4_EventScript_ItemXAttack, FLAG_HIDE_SSANNE_2F_ROOM4_X_ATTACK

SSAnne_2F_Room4_MapWarps:
	warp_def 4, 7, 3, 6, MAP_SSANNE_2F_CORRIDOR

SSAnne_2F_Room4_MapEvents::
	map_events SSAnne_2F_Room4_ObjectEvents, SSAnne_2F_Room4_MapWarps, NULL, NULL

@ ===== END data/maps/SSAnne_2F_Room4/events.inc =====
@ ===== BEGIN data/maps/SSAnne_2F_Room5/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SSAnne_2F_Room5/map.json
@

	.align 2

SSAnne_2F_Room5_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_GENTLEMAN, 5, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SSAnne_2F_Room5_EventScript_Gentleman, 0
	object_event 2, OBJ_EVENT_GFX_LITTLE_BOY, 3, 5, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, SSAnne_2F_Room5_EventScript_LittleBoy, 0

SSAnne_2F_Room5_MapWarps:
	warp_def 4, 7, 3, 7, MAP_SSANNE_2F_CORRIDOR

SSAnne_2F_Room5_MapEvents::
	map_events SSAnne_2F_Room5_ObjectEvents, SSAnne_2F_Room5_MapWarps, NULL, NULL

@ ===== END data/maps/SSAnne_2F_Room5/events.inc =====
@ ===== BEGIN data/maps/SSAnne_2F_Room6/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SSAnne_2F_Room6/map.json
@

	.align 2

SSAnne_2F_Room6_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_WOMAN_3, 1, 4, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, SSAnne_2F_Room6_EventScript_Woman2, 0
	object_event 2, OBJ_EVENT_GFX_WOMAN_1, 4, 4, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NONE, 0, SSAnne_2F_Room6_EventScript_Woman1, 0

SSAnne_2F_Room6_MapWarps:
	warp_def 4, 7, 3, 8, MAP_SSANNE_2F_CORRIDOR

SSAnne_2F_Room6_MapEvents::
	map_events SSAnne_2F_Room6_ObjectEvents, SSAnne_2F_Room6_MapWarps, NULL, NULL

@ ===== END data/maps/SSAnne_2F_Room6/events.inc =====
@ ===== BEGIN data/maps/SSAnne_B1F_Room1/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SSAnne_B1F_Room1/map.json
@

	.align 2

SSAnne_B1F_Room1_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_FISHER, 5, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 2, SSAnne_B1F_Room1_EventScript_Barny, 0
	object_event 2, OBJ_EVENT_GFX_SAILOR, 3, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 2, SSAnne_B1F_Room1_EventScript_Phillip, 0

SSAnne_B1F_Room1_MapWarps:
	warp_def 4, 7, 3, 1, MAP_SSANNE_B1F_CORRIDOR

SSAnne_B1F_Room1_MapEvents::
	map_events SSAnne_B1F_Room1_ObjectEvents, SSAnne_B1F_Room1_MapWarps, NULL, NULL

@ ===== END data/maps/SSAnne_B1F_Room1/events.inc =====
@ ===== BEGIN data/maps/SSAnne_B1F_Room2/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SSAnne_B1F_Room2/map.json
@

	.align 2

SSAnne_B1F_Room2_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_SAILOR, 3, 5, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NORMAL, 1, SSAnne_B1F_Room2_EventScript_Huey, 0
	object_event 2, OBJ_EVENT_GFX_ITEM_BALL, 3, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SSAnne_B1F_Room2_EventScript_ItemTM44, FLAG_HIDE_SSANNE_B1F_ROOM2_TM44

SSAnne_B1F_Room2_MapWarps:
	warp_def 4, 7, 3, 2, MAP_SSANNE_B1F_CORRIDOR

SSAnne_B1F_Room2_MapEvents::
	map_events SSAnne_B1F_Room2_ObjectEvents, SSAnne_B1F_Room2_MapWarps, NULL, NULL

@ ===== END data/maps/SSAnne_B1F_Room2/events.inc =====
@ ===== BEGIN data/maps/SSAnne_B1F_Room3/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SSAnne_B1F_Room3/map.json
@

	.align 2

SSAnne_B1F_Room3_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_SAILOR, 4, 4, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 3, SSAnne_B1F_Room3_EventScript_Dylan, 0
	object_event 2, OBJ_EVENT_GFX_ITEM_BALL, 1, 5, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SSAnne_B1F_Room3_EventScript_ItemEther, FLAG_HIDE_SSANNE_B1F_ROOM3_ETHER

SSAnne_B1F_Room3_MapWarps:
	warp_def 4, 7, 3, 3, MAP_SSANNE_B1F_CORRIDOR

SSAnne_B1F_Room3_MapEvents::
	map_events SSAnne_B1F_Room3_ObjectEvents, SSAnne_B1F_Room3_MapWarps, NULL, NULL

@ ===== END data/maps/SSAnne_B1F_Room3/events.inc =====
@ ===== BEGIN data/maps/SSAnne_B1F_Room4/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SSAnne_B1F_Room4/map.json
@

	.align 2

SSAnne_B1F_Room4_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_SAILOR, 3, 3, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 3, SSAnne_B1F_Room4_EventScript_Duncan, 0
	object_event 2, OBJ_EVENT_GFX_SAILOR, 2, 6, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NORMAL, 1, SSAnne_B1F_Room4_EventScript_Leonard, 0

SSAnne_B1F_Room4_MapWarps:
	warp_def 4, 7, 3, 4, MAP_SSANNE_B1F_CORRIDOR

SSAnne_B1F_Room4_MapEvents::
	map_events SSAnne_B1F_Room4_ObjectEvents, SSAnne_B1F_Room4_MapWarps, NULL, NULL

@ ===== END data/maps/SSAnne_B1F_Room4/events.inc =====
@ ===== BEGIN data/maps/SSAnne_B1F_Room5/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SSAnne_B1F_Room5/map.json
@

	.align 2

SSAnne_B1F_Room5_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_BOY, 3, 5, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SSAnne_B1F_Room5_EventScript_Boy, 0
	object_event 2, OBJ_EVENT_GFX_MACHOKE, 2, 5, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SSAnne_B1F_Room5_EventScript_Machoke, 0
	object_event 3, OBJ_EVENT_GFX_ITEM_BALL, 2, 2, 0, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SSAnne_B1F_Room5_EventScript_ItemSuperPotion, FLAG_HIDE_SSANNE_B1F_ROOM5_SUPER_POTION

SSAnne_B1F_Room5_MapWarps:
	warp_def 4, 7, 3, 5, MAP_SSANNE_B1F_CORRIDOR

SSAnne_B1F_Room5_MapEvents::
	map_events SSAnne_B1F_Room5_ObjectEvents, SSAnne_B1F_Room5_MapWarps, NULL, NULL

@ ===== END data/maps/SSAnne_B1F_Room5/events.inc =====
@ ===== BEGIN data/maps/SSAnne_1F_Room6/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SSAnne_1F_Room6/map.json
@

	.align 2

SSAnne_1F_Room6_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_WOMAN_2, 3, 5, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NONE, 0, SSAnne_1F_Room6_EventScript_Woman, 0

SSAnne_1F_Room6_MapWarps:
	warp_def 2, 1, 0, 12, MAP_SSANNE_1F_CORRIDOR

SSAnne_1F_Room6_MapEvents::
	map_events SSAnne_1F_Room6_ObjectEvents, SSAnne_1F_Room6_MapWarps, NULL, NULL

@ ===== END data/maps/SSAnne_1F_Room6/events.inc =====
@ ===== BEGIN data/maps/UndergroundPath_NorthEntrance/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/UndergroundPath_NorthEntrance/map.json
@

	.align 2

UndergroundPath_NorthEntrance_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_LITTLE_GIRL, 5, 6, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, UndergroundPath_NorthEntrance_EventScript_Saige, 0

UndergroundPath_NorthEntrance_MapWarps:
	warp_def 5, 8, 3, 0, MAP_ROUTE5
	warp_def 6, 8, 3, 0, MAP_ROUTE5
	warp_def 7, 8, 3, 0, MAP_ROUTE5
	warp_def 7, 4, 3, 0, MAP_UNDERGROUND_PATH_NORTH_SOUTH_TUNNEL

UndergroundPath_NorthEntrance_MapEvents::
	map_events UndergroundPath_NorthEntrance_ObjectEvents, UndergroundPath_NorthEntrance_MapWarps, NULL, NULL

@ ===== END data/maps/UndergroundPath_NorthEntrance/events.inc =====
@ ===== BEGIN data/maps/UndergroundPath_NorthSouthTunnel/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/UndergroundPath_NorthSouthTunnel/map.json
@

	.align 2

UndergroundPath_NorthSouthTunnel_MapWarps:
	warp_def 4, 3, 3, 3, MAP_UNDERGROUND_PATH_NORTH_ENTRANCE
	warp_def 3, 60, 3, 3, MAP_UNDERGROUND_PATH_SOUTH_ENTRANCE

UndergroundPath_NorthSouthTunnel_MapBGEvents:
	bg_hidden_item_event 5, 30, 3, ITEM_POTION, FLAG_HIDDEN_ITEM_UNDERGROUND_PATH_NORTH_SOUTH_TUNNEL_POTION, 1, FALSE
	bg_hidden_item_event 5, 6, 3, ITEM_ANTIDOTE, FLAG_HIDDEN_ITEM_UNDERGROUND_PATH_NORTH_SOUTH_TUNNEL_ANTIDOTE, 1, FALSE
	bg_hidden_item_event 2, 57, 3, ITEM_BURN_HEAL, FLAG_HIDDEN_ITEM_UNDERGROUND_PATH_NORTH_SOUTH_TUNNEL_BURN_HEAL, 1, FALSE
	bg_hidden_item_event 1, 24, 3, ITEM_AWAKENING, FLAG_HIDDEN_ITEM_UNDERGROUND_PATH_NORTH_SOUTH_TUNNEL_AWAKENING, 1, FALSE
	bg_hidden_item_event 6, 53, 3, ITEM_ICE_HEAL, FLAG_HIDDEN_ITEM_UNDERGROUND_PATH_NORTH_SOUTH_TUNNEL_ICE_HEAL, 1, FALSE
	bg_hidden_item_event 3, 15, 3, ITEM_PARALYZE_HEAL, FLAG_HIDDEN_ITEM_UNDERGROUND_PATH_NORTH_SOUTH_TUNNEL_PARALYZE_HEAL, 1, FALSE
	bg_hidden_item_event 3, 39, 3, ITEM_ETHER, FLAG_HIDDEN_ITEM_UNDERGROUND_PATH_NORTH_SOUTH_TUNNEL_ETHER, 1, FALSE

UndergroundPath_NorthSouthTunnel_MapEvents::
	map_events NULL, UndergroundPath_NorthSouthTunnel_MapWarps, NULL, UndergroundPath_NorthSouthTunnel_MapBGEvents

@ ===== END data/maps/UndergroundPath_NorthSouthTunnel/events.inc =====
@ ===== BEGIN data/maps/UndergroundPath_SouthEntrance/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/UndergroundPath_SouthEntrance/map.json
@

	.align 2

UndergroundPath_SouthEntrance_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_WOMAN_2, 5, 6, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, UndergroundPath_SouthEntrance_EventScript_Woman, 0

UndergroundPath_SouthEntrance_MapWarps:
	warp_def 5, 8, 3, 0, MAP_ROUTE6
	warp_def 6, 8, 3, 0, MAP_ROUTE6
	warp_def 7, 8, 3, 0, MAP_ROUTE6
	warp_def 7, 4, 3, 1, MAP_UNDERGROUND_PATH_NORTH_SOUTH_TUNNEL

UndergroundPath_SouthEntrance_MapEvents::
	map_events UndergroundPath_SouthEntrance_ObjectEvents, UndergroundPath_SouthEntrance_MapWarps, NULL, NULL

@ ===== END data/maps/UndergroundPath_SouthEntrance/events.inc =====
@ ===== BEGIN data/maps/UndergroundPath_WestEntrance/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/UndergroundPath_WestEntrance/map.json
@

	.align 2

UndergroundPath_WestEntrance_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_BALDING_MAN, 5, 6, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, UndergroundPath_WestEntrance_EventScript_BaldingMan, 0

UndergroundPath_WestEntrance_MapWarps:
	warp_def 5, 8, 3, 0, MAP_ROUTE7
	warp_def 6, 8, 3, 0, MAP_ROUTE7
	warp_def 7, 8, 3, 0, MAP_ROUTE7
	warp_def 7, 4, 3, 1, MAP_UNDERGROUND_PATH_EAST_WEST_TUNNEL

UndergroundPath_WestEntrance_MapEvents::
	map_events UndergroundPath_WestEntrance_ObjectEvents, UndergroundPath_WestEntrance_MapWarps, NULL, NULL

@ ===== END data/maps/UndergroundPath_WestEntrance/events.inc =====
@ ===== BEGIN data/maps/UndergroundPath_EastWestTunnel/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/UndergroundPath_EastWestTunnel/map.json
@

	.align 2

UndergroundPath_EastWestTunnel_MapWarps:
	warp_def 76, 3, 3, 3, MAP_UNDERGROUND_PATH_EAST_ENTRANCE
	warp_def 3, 4, 3, 3, MAP_UNDERGROUND_PATH_WEST_ENTRANCE

UndergroundPath_EastWestTunnel_MapBGEvents:
	bg_hidden_item_event 7, 3, 3, ITEM_POTION, FLAG_HIDDEN_ITEM_UNDERGROUND_PATH_EAST_WEST_TUNNEL_POTION, 1, FALSE
	bg_hidden_item_event 17, 5, 3, ITEM_PARALYZE_HEAL, FLAG_HIDDEN_ITEM_UNDERGROUND_PATH_EAST_WEST_TUNNEL_PARALYZE_HEAL, 1, FALSE
	bg_hidden_item_event 31, 4, 3, ITEM_AWAKENING, FLAG_HIDDEN_ITEM_UNDERGROUND_PATH_EAST_WEST_TUNNEL_AWAKENING, 1, FALSE
	bg_hidden_item_event 45, 3, 3, ITEM_BURN_HEAL, FLAG_HIDDEN_ITEM_UNDERGROUND_PATH_EAST_WEST_TUNNEL_BURN_HEAL, 1, FALSE
	bg_hidden_item_event 70, 3, 3, ITEM_ICE_HEAL, FLAG_HIDDEN_ITEM_UNDERGROUND_PATH_EAST_WEST_TUNNEL_ICE_HEAL, 1, FALSE
	bg_hidden_item_event 55, 2, 3, ITEM_ETHER, FLAG_HIDDEN_ITEM_UNDERGROUND_PATH_EAST_WEST_TUNNEL_ETHER, 1, FALSE
	bg_hidden_item_event 62, 5, 3, ITEM_ANTIDOTE, FLAG_HIDDEN_ITEM_UNDERGROUND_PATH_EAST_WEST_TUNNEL_ANTIDOTE, 1, FALSE

UndergroundPath_EastWestTunnel_MapEvents::
	map_events NULL, UndergroundPath_EastWestTunnel_MapWarps, NULL, UndergroundPath_EastWestTunnel_MapBGEvents

@ ===== END data/maps/UndergroundPath_EastWestTunnel/events.inc =====
@ ===== BEGIN data/maps/UndergroundPath_EastEntrance/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/UndergroundPath_EastEntrance/map.json
@

	.align 2

UndergroundPath_EastEntrance_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_WOMAN_2, 5, 6, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, UndergroundPath_EastEntrance_EventScript_Woman, 0

UndergroundPath_EastEntrance_MapWarps:
	warp_def 5, 8, 3, 0, MAP_ROUTE8
	warp_def 6, 8, 3, 0, MAP_ROUTE8
	warp_def 7, 8, 3, 0, MAP_ROUTE8
	warp_def 7, 4, 3, 0, MAP_UNDERGROUND_PATH_EAST_WEST_TUNNEL

UndergroundPath_EastEntrance_MapEvents::
	map_events UndergroundPath_EastEntrance_ObjectEvents, UndergroundPath_EastEntrance_MapWarps, NULL, NULL

@ ===== END data/maps/UndergroundPath_EastEntrance/events.inc =====
@ ===== BEGIN data/maps/DiglettsCave_NorthEntrance/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/DiglettsCave_NorthEntrance/map.json
@

	.align 2

DiglettsCave_NorthEntrance_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_HIKER, 4, 4, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, DiglettsCave_NorthEntrance_EventScript_Hiker, 0

DiglettsCave_NorthEntrance_MapWarps:
	warp_def 6, 4, 3, 0, MAP_DIGLETTS_CAVE_B1F
	warp_def 4, 6, 3, 3, MAP_ROUTE2

DiglettsCave_NorthEntrance_MapEvents::
	map_events DiglettsCave_NorthEntrance_ObjectEvents, DiglettsCave_NorthEntrance_MapWarps, NULL, NULL

@ ===== END data/maps/DiglettsCave_NorthEntrance/events.inc =====
@ ===== BEGIN data/maps/DiglettsCave_B1F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/DiglettsCave_B1F/map.json
@

	.align 2

DiglettsCave_B1F_MapWarps:
	warp_def 3, 3, 3, 0, MAP_DIGLETTS_CAVE_NORTH_ENTRANCE
	warp_def 82, 71, 3, 1, MAP_DIGLETTS_CAVE_SOUTH_ENTRANCE

DiglettsCave_B1F_MapEvents::
	map_events NULL, DiglettsCave_B1F_MapWarps, NULL, NULL

@ ===== END data/maps/DiglettsCave_B1F/events.inc =====
@ ===== BEGIN data/maps/DiglettsCave_SouthEntrance/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/DiglettsCave_SouthEntrance/map.json
@

	.align 2

DiglettsCave_SouthEntrance_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_OLD_MAN_1, 4, 4, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, DiglettsCave_SouthEntrance_EventScript_OldMan, 0

DiglettsCave_SouthEntrance_MapWarps:
	warp_def 4, 6, 3, 0, MAP_ROUTE11
	warp_def 6, 4, 3, 1, MAP_DIGLETTS_CAVE_B1F

DiglettsCave_SouthEntrance_MapEvents::
	map_events DiglettsCave_SouthEntrance_ObjectEvents, DiglettsCave_SouthEntrance_MapWarps, NULL, NULL

@ ===== END data/maps/DiglettsCave_SouthEntrance/events.inc =====
@ ===== BEGIN data/maps/VictoryRoad_1F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/VictoryRoad_1F/map.json
@

	.align 2

VictoryRoad_1F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_COOLTRAINER_M, 5, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 4, VictoryRoad_1F_EventScript_Rolando, 0
	object_event 2, OBJ_EVENT_GFX_COOLTRAINER_F, 14, 6, 4, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 4, VictoryRoad_1F_EventScript_Naomi, 0
	object_event 3, OBJ_EVENT_GFX_ITEM_BALL, 12, 3, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, VictoryRoad_1F_EventScript_ItemRareCandy, FLAG_HIDE_VICTORY_ROAD_1F_RARE_CANDY
	object_event 4, OBJ_EVENT_GFX_ITEM_BALL, 14, 1, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, VictoryRoad_1F_EventScript_ItemTM02, FLAG_HIDE_VICTORY_ROAD_1F_TM02
	object_event 5, OBJ_EVENT_GFX_PUSHABLE_BOULDER, 7, 18, 3, MOVEMENT_TYPE_FACE_DOWN, 0, 0, TRAINER_TYPE_NONE, 0, EventScript_StrengthBoulder, 0
	object_event 6, OBJ_EVENT_GFX_PUSHABLE_BOULDER, 4, 12, 3, MOVEMENT_TYPE_FACE_DOWN, 0, 0, TRAINER_TYPE_NONE, 0, EventScript_StrengthBoulder, 0
	object_event 7, OBJ_EVENT_GFX_PUSHABLE_BOULDER, 16, 3, 3, MOVEMENT_TYPE_FACE_DOWN, 0, 0, TRAINER_TYPE_NONE, 0, EventScript_StrengthBoulder, 0

VictoryRoad_1F_MapWarps:
	warp_def 3, 2, 3, 0, MAP_VICTORY_ROAD_2F
	warp_def 11, 20, 3, 0, MAP_ROUTE23

VictoryRoad_1F_MapCoordEvents:
	coord_event 20, 16, 3, VAR_MAP_SCENE_VICTORY_ROAD_1F, 99, VictoryRoad_1F_EventScript_FloorSwitch

VictoryRoad_1F_MapBGEvents:
	bg_hidden_item_event 12, 12, 0, ITEM_ULTRA_BALL, FLAG_HIDDEN_ITEM_VICTORY_ROAD_1F_ULTRA_BALL, 1, FALSE
	bg_hidden_item_event 16, 1, 0, ITEM_FULL_RESTORE, FLAG_HIDDEN_ITEM_VICTORY_ROAD_1F_FULL_RESTORE, 1, FALSE

VictoryRoad_1F_MapEvents::
	map_events VictoryRoad_1F_ObjectEvents, VictoryRoad_1F_MapWarps, VictoryRoad_1F_MapCoordEvents, VictoryRoad_1F_MapBGEvents

@ ===== END data/maps/VictoryRoad_1F/events.inc =====
@ ===== BEGIN data/maps/VictoryRoad_2F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/VictoryRoad_2F/map.json
@

	.align 2

VictoryRoad_2F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_POKE_MANIAC, 7, 4, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 1, VictoryRoad_2F_EventScript_Dawson, 0
	object_event 2, OBJ_EVENT_GFX_BLACK_BELT, 20, 11, 4, MOVEMENT_TYPE_FACE_DOWN_AND_LEFT, 1, 1, TRAINER_TYPE_NORMAL, 4, VictoryRoad_2F_EventScript_Daisuke, 0
	object_event 3, OBJ_EVENT_GFX_ROCKER, 31, 16, 4, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NORMAL, 4, VictoryRoad_2F_EventScript_Nelson, 0
	object_event 4, OBJ_EVENT_GFX_MAN, 26, 6, 3, MOVEMENT_TYPE_WALK_SEQUENCE_DOWN_RIGHT_LEFT_UP, 4, 4, TRAINER_TYPE_NORMAL, 1, VictoryRoad_2F_EventScript_Vincent, 0
	object_event 5, OBJ_EVENT_GFX_ROCKER, 36, 5, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NORMAL, 3, VictoryRoad_2F_EventScript_Gregory, 0
	object_event 6, OBJ_EVENT_GFX_ITEM_BALL, 17, 6, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, VictoryRoad_2F_EventScript_ItemGuardSpec, FLAG_HIDE_VICTORY_ROAD_2F_GUARD_SPEC
	object_event 7, OBJ_EVENT_GFX_ITEM_BALL, 40, 7, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, VictoryRoad_2F_EventScript_ItemTM07, FLAG_HIDE_VICTORY_ROAD_2F_TM07
	object_event 8, OBJ_EVENT_GFX_ITEM_BALL, 25, 13, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, VictoryRoad_2F_EventScript_ItemFullHeal, FLAG_HIDE_VICTORY_ROAD_2F_FULL_HEAL
	object_event 9, OBJ_EVENT_GFX_ITEM_BALL, 14, 13, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, VictoryRoad_2F_EventScript_ItemTM37, FLAG_HIDE_VICTORY_ROAD_2F_TM37
	object_event 10, OBJ_EVENT_GFX_PUSHABLE_BOULDER, 8, 7, 3, MOVEMENT_TYPE_FACE_DOWN, 0, 0, TRAINER_TYPE_NONE, 0, EventScript_StrengthBoulder, 0
	object_event 11, OBJ_EVENT_GFX_PUSHABLE_BOULDER, 6, 17, 3, MOVEMENT_TYPE_FACE_DOWN, 0, 0, TRAINER_TYPE_NONE, 0, EventScript_StrengthBoulder, 0
	object_event 12, OBJ_EVENT_GFX_PUSHABLE_BOULDER, 33, 19, 3, MOVEMENT_TYPE_FACE_DOWN, 0, 0, TRAINER_TYPE_NONE, 0, EventScript_StrengthBoulder, FLAG_HIDE_VICTORY_ROAD_2F_BOULDER
	object_event 13, OBJ_EVENT_GFX_COOLTRAINER_M, 40, 9, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, VictoryRoad_2F_EventScript_DoubleEdgeTutor, 0

VictoryRoad_2F_MapWarps:
	warp_def 1, 9, 3, 0, MAP_VICTORY_ROAD_1F
	warp_def 3, 3, 3, 0, MAP_VICTORY_ROAD_3F
	warp_def 34, 9, 3, 1, MAP_VICTORY_ROAD_3F
	warp_def 38, 9, 3, 2, MAP_VICTORY_ROAD_3F
	warp_def 36, 17, 4, 3, MAP_VICTORY_ROAD_3F
	warp_def 49, 13, 0, 1, MAP_ROUTE23
	warp_def 48, 12, 3, 1, MAP_ROUTE23
	warp_def 47, 13, 0, 1, MAP_ROUTE23
	warp_def 34, 19, 3, 4, MAP_VICTORY_ROAD_3F

VictoryRoad_2F_MapCoordEvents:
	coord_event 2, 19, 3, VAR_MAP_SCENE_VICTORY_ROAD_2F_BOULDER1, 99, VictoryRoad_2F_EventScript_FloorSwitch1
	coord_event 14, 19, 3, VAR_MAP_SCENE_VICTORY_ROAD_2F_BOULDER2, 99, VictoryRoad_2F_EventScript_FloorSwitch2

VictoryRoad_2F_MapEvents::
	map_events VictoryRoad_2F_ObjectEvents, VictoryRoad_2F_MapWarps, VictoryRoad_2F_MapCoordEvents, NULL

@ ===== END data/maps/VictoryRoad_2F/events.inc =====
@ ===== BEGIN data/maps/VictoryRoad_3F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/VictoryRoad_3F/map.json
@

	.align 2

VictoryRoad_3F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_COOLTRAINER_M, 40, 7, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NORMAL, 1, VictoryRoad_3F_EventScript_George, 0
	object_event 2, OBJ_EVENT_GFX_COOLTRAINER_F, 21, 5, 4, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 4, VictoryRoad_3F_EventScript_Alexa, 0
	object_event 3, OBJ_EVENT_GFX_COOLTRAINER_M, 10, 17, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NORMAL, 5, VictoryRoad_3F_EventScript_Colby, 0
	object_event 4, OBJ_EVENT_GFX_COOLTRAINER_F, 11, 16, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 5, VictoryRoad_3F_EventScript_Caroline, 0
	object_event 5, OBJ_EVENT_GFX_ITEM_BALL, 38, 7, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, VictoryRoad_3F_EventScript_ItemMaxRevive, FLAG_HIDE_VICTORY_ROAD_3F_MAX_REVIVE
	object_event 6, OBJ_EVENT_GFX_ITEM_BALL, 12, 9, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, VictoryRoad_3F_EventScript_ItemTM50, FLAG_HIDE_VICTORY_ROAD_3F_TM50
	object_event 7, OBJ_EVENT_GFX_PUSHABLE_BOULDER, 19, 15, 3, MOVEMENT_TYPE_FACE_DOWN, 0, 0, TRAINER_TYPE_NONE, 0, EventScript_StrengthBoulder, 0
	object_event 8, OBJ_EVENT_GFX_PUSHABLE_BOULDER, 33, 18, 0, MOVEMENT_TYPE_FACE_DOWN, 0, 0, FLAG_HIDE_VICTORY_ROAD_2F_BOULDER, 0, EventScript_StrengthBoulder, FLAG_HIDE_VICTORY_ROAD_3F_BOULDER
	object_event 9, OBJ_EVENT_GFX_PUSHABLE_BOULDER, 35, 13, 3, MOVEMENT_TYPE_FACE_DOWN, 0, 0, TRAINER_TYPE_NONE, 0, EventScript_StrengthBoulder, 0
	object_event 10, OBJ_EVENT_GFX_PUSHABLE_BOULDER, 32, 5, 3, MOVEMENT_TYPE_FACE_DOWN, 0, 0, TRAINER_TYPE_NONE, 0, EventScript_StrengthBoulder, 0
	object_event 11, OBJ_EVENT_GFX_COOLTRAINER_M, 38, 13, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 1, VictoryRoad_3F_EventScript_Ray, 0
	object_event 12, OBJ_EVENT_GFX_COOLTRAINER_F, 39, 13, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 1, VictoryRoad_3F_EventScript_Tyra, 0

VictoryRoad_3F_MapWarps:
	warp_def 5, 2, 3, 1, MAP_VICTORY_ROAD_2F
	warp_def 34, 9, 3, 2, MAP_VICTORY_ROAD_2F
	warp_def 37, 10, 3, 3, MAP_VICTORY_ROAD_2F
	warp_def 39, 17, 3, 4, MAP_VICTORY_ROAD_2F
	warp_def 34, 18, 3, 8, MAP_VICTORY_ROAD_2F

VictoryRoad_3F_MapCoordEvents:
	coord_event 7, 7, 3, VAR_MAP_SCENE_VICTORY_ROAD_3F, 99, VictoryRoad_3F_EventScript_FloorSwitch

VictoryRoad_3F_MapEvents::
	map_events VictoryRoad_3F_ObjectEvents, VictoryRoad_3F_MapWarps, VictoryRoad_3F_MapCoordEvents, NULL

@ ===== END data/maps/VictoryRoad_3F/events.inc =====
@ ===== BEGIN data/maps/RocketHideout_B1F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/RocketHideout_B1F/map.json
@

	.align 2

RocketHideout_B1F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_ROCKET_M, 4, 9, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 5, RocketHideout_B1F_EventScript_Grunt2, FLAG_HIDE_MISC_KANTO_ROCKETS
	object_event 2, OBJ_EVENT_GFX_ROCKET_M, 24, 12, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NORMAL, 2, RocketHideout_B1F_EventScript_Grunt1, FLAG_HIDE_MISC_KANTO_ROCKETS
	object_event 3, OBJ_EVENT_GFX_ROCKET_M, 6, 32, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 4, RocketHideout_B1F_EventScript_Grunt4, FLAG_HIDE_MISC_KANTO_ROCKETS
	object_event 4, OBJ_EVENT_GFX_ROCKET_M, 10, 22, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 3, RocketHideout_B1F_EventScript_Grunt3, FLAG_HIDE_MISC_KANTO_ROCKETS
	object_event 5, OBJ_EVENT_GFX_ROCKET_M, 21, 27, 3, MOVEMENT_TYPE_FACE_UP_AND_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 3, RocketHideout_B1F_EventScript_Grunt5, FLAG_HIDE_MISC_KANTO_ROCKETS
	object_event 6, OBJ_EVENT_GFX_ITEM_BALL, 5, 16, 0, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, RocketHideout_B1F_EventScript_ItemEscapeRope, FLAG_HIDE_ROCKET_HIDEOUT_B1F_ESCAPE_ROPE
	object_event 7, OBJ_EVENT_GFX_ITEM_BALL, 1, 22, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, RocketHideout_B1F_EventScript_ItemHyperPotion, FLAG_HIDE_ROCKET_HIDEOUT_B1F_HYPER_POTION

RocketHideout_B1F_MapWarps:
	warp_def 12, 2, 3, 3, MAP_CELADON_CITY_GAME_CORNER
	warp_def 17, 2, 3, 1, MAP_ROCKET_HIDEOUT_B2F
	warp_def 15, 30, 3, 2, MAP_ROCKET_HIDEOUT_B2F
	warp_def 23, 25, 0, 1, MAP_ROCKET_HIDEOUT_ELEVATOR
	warp_def 24, 25, 0, 1, MAP_ROCKET_HIDEOUT_ELEVATOR
	warp_def 25, 25, 0, 1, MAP_ROCKET_HIDEOUT_ELEVATOR

RocketHideout_B1F_MapBGEvents:
	bg_hidden_item_event 16, 17, 0, ITEM_PP_UP, FLAG_HIDDEN_ITEM_ROCKET_HIDEOUT_B1F_PP_UP, 1, FALSE

RocketHideout_B1F_MapEvents::
	map_events RocketHideout_B1F_ObjectEvents, RocketHideout_B1F_MapWarps, NULL, RocketHideout_B1F_MapBGEvents

@ ===== END data/maps/RocketHideout_B1F/events.inc =====
@ ===== BEGIN data/maps/RocketHideout_B2F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/RocketHideout_B2F/map.json
@

	.align 2

RocketHideout_B2F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_ROCKET_M, 20, 6, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NORMAL, 2, RocketHideout_B2F_EventScript_Grunt, FLAG_HIDE_MISC_KANTO_ROCKETS
	object_event 2, OBJ_EVENT_GFX_ITEM_BALL, 15, 3, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, RocketHideout_B2F_EventScript_ItemXSpeed, FLAG_HIDE_ROCKET_HIDEOUT_B2F_X_SPEED
	object_event 3, OBJ_EVENT_GFX_ITEM_BALL, 2, 5, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, RocketHideout_B2F_EventScript_ItemMoonStone, FLAG_HIDE_ROCKET_HIDEOUT_B2F_MOON_STONE
	object_event 4, OBJ_EVENT_GFX_ITEM_BALL, 5, 7, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, RocketHideout_B2F_EventScript_ItemTM12, FLAG_HIDE_ROCKET_HIDEOUT_B2F_TM12
	object_event 5, OBJ_EVENT_GFX_ITEM_BALL, 0, 14, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, RocketHideout_B2F_EventScript_ItemSuperPotion, FLAG_HIDE_ROCKET_HIDEOUT_B2F_SUPER_POTION

RocketHideout_B2F_MapWarps:
	warp_def 21, 2, 3, 0, MAP_ROCKET_HIDEOUT_B3F
	warp_def 28, 2, 3, 1, MAP_ROCKET_HIDEOUT_B1F
	warp_def 23, 12, 3, 2, MAP_ROCKET_HIDEOUT_B1F
	warp_def 28, 16, 0, 1, MAP_ROCKET_HIDEOUT_ELEVATOR
	warp_def 29, 16, 0, 1, MAP_ROCKET_HIDEOUT_ELEVATOR

RocketHideout_B2F_MapEvents::
	map_events RocketHideout_B2F_ObjectEvents, RocketHideout_B2F_MapWarps, NULL, NULL

@ ===== END data/maps/RocketHideout_B2F/events.inc =====
@ ===== BEGIN data/maps/RocketHideout_B3F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/RocketHideout_B3F/map.json
@

	.align 2

RocketHideout_B3F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_ROCKET_M, 19, 9, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NORMAL, 4, RocketHideout_B3F_EventScript_Grunt2, FLAG_HIDE_MISC_KANTO_ROCKETS
	object_event 2, OBJ_EVENT_GFX_ROCKET_M, 2, 20, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 2, RocketHideout_B3F_EventScript_Grunt1, FLAG_HIDE_MISC_KANTO_ROCKETS
	object_event 3, OBJ_EVENT_GFX_ITEM_BALL, 12, 12, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, RocketHideout_B3F_EventScript_ItemRareCandy, FLAG_HIDE_ROCKET_HIDEOUT_B3F_RARE_CANDY
	object_event 4, OBJ_EVENT_GFX_ITEM_BALL, 19, 14, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, RocketHideout_B3F_EventScript_ItemTM21, FLAG_HIDE_ROCKET_HIDEOUT_B3F_TM21
	object_event 5, OBJ_EVENT_GFX_ITEM_BALL, 14, 24, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, RocketHideout_B3F_EventScript_ItemBlackGlasses, FLAG_HIDE_ROCKET_HIDEOUT_B3F_BLACK_GLASSES

RocketHideout_B3F_MapWarps:
	warp_def 18, 2, 3, 0, MAP_ROCKET_HIDEOUT_B2F
	warp_def 15, 18, 3, 0, MAP_ROCKET_HIDEOUT_B4F

RocketHideout_B3F_MapBGEvents:
	bg_hidden_item_event 1, 3, 3, ITEM_NUGGET, FLAG_HIDDEN_ITEM_ROCKET_HIDEOUT_B3F_NUGGET, 1, FALSE

RocketHideout_B3F_MapEvents::
	map_events RocketHideout_B3F_ObjectEvents, RocketHideout_B3F_MapWarps, NULL, RocketHideout_B3F_MapBGEvents

@ ===== END data/maps/RocketHideout_B3F/events.inc =====
@ ===== BEGIN data/maps/RocketHideout_B4F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/RocketHideout_B4F/map.json
@

	.align 2

RocketHideout_B4F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_GIOVANNI, 19, 4, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, RocketHideout_B4F_EventScript_Giovanni, FLAG_HIDE_HIDEOUT_GIOVANNI
	object_event 2, OBJ_EVENT_GFX_ITEM_BALL, 20, 5, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, RocketHideout_B4F_EventScript_SilphScope, FLAG_HIDE_SILPH_SCOPE
	object_event 3, OBJ_EVENT_GFX_ROCKET_M, 4, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 1, RocketHideout_B4F_EventScript_Grunt1, FLAG_HIDE_MISC_KANTO_ROCKETS
	object_event 4, OBJ_EVENT_GFX_ITEM_BALL, 3, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, RocketHideout_B4F_EventScript_LiftKey, FLAG_HIDE_LIFT_KEY
	object_event 5, OBJ_EVENT_GFX_ROCKET_M, 19, 14, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 0, RocketHideout_B4F_EventScript_Grunt3, FLAG_HIDE_MISC_KANTO_ROCKETS
	object_event 6, OBJ_EVENT_GFX_ROCKET_M, 16, 14, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 0, RocketHideout_B4F_EventScript_Grunt2, FLAG_HIDE_MISC_KANTO_ROCKETS
	object_event 7, OBJ_EVENT_GFX_ITEM_BALL, 1, 6, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, RocketHideout_B4F_EventScript_ItemTM49, FLAG_HIDE_ROCKET_HIDEOUT_B4F_TM49
	object_event 8, OBJ_EVENT_GFX_ITEM_BALL, 4, 14, 0, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, RocketHideout_B4F_EventScript_ItemMaxEther, FLAG_HIDE_ROCKET_HIDEOUT_B4F_MAX_ETHER
	object_event 9, OBJ_EVENT_GFX_ITEM_BALL, 6, 23, 0, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, RocketHideout_B4F_EventScript_ItemCalcium, FLAG_HIDE_ROCKET_HIDEOUT_B4F_CALCIUM

RocketHideout_B4F_MapWarps:
	warp_def 11, 15, 3, 1, MAP_ROCKET_HIDEOUT_B3F
	warp_def 20, 23, 0, 1, MAP_ROCKET_HIDEOUT_ELEVATOR
	warp_def 21, 23, 0, 1, MAP_ROCKET_HIDEOUT_ELEVATOR

RocketHideout_B4F_MapBGEvents:
	bg_hidden_item_event 22, 6, 3, ITEM_NEST_BALL, FLAG_HIDDEN_ITEM_ROCKET_HIDEOUT_B4F_NEST_BALL, 1, FALSE
	bg_hidden_item_event 16, 6, 3, ITEM_NET_BALL, FLAG_HIDDEN_ITEM_ROCKET_HIDEOUT_B4F_NET_BALL, 1, FALSE

RocketHideout_B4F_MapEvents::
	map_events RocketHideout_B4F_ObjectEvents, RocketHideout_B4F_MapWarps, NULL, RocketHideout_B4F_MapBGEvents

@ ===== END data/maps/RocketHideout_B4F/events.inc =====
@ ===== BEGIN data/maps/RocketHideout_Elevator/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/RocketHideout_Elevator/map.json
@

	.align 2

RocketHideout_Elevator_MapWarps:
	warp_def 1, 5, 3, WARP_ID_DYNAMIC, MAP_DYNAMIC
	warp_def 2, 5, 3, WARP_ID_DYNAMIC, MAP_DYNAMIC

RocketHideout_Elevator_MapBGEvents:
	bg_sign_event 0, 2, 0, BG_EVENT_PLAYER_FACING_ANY, RocketHideout_Elevator_EventScript_FloorSelect

RocketHideout_Elevator_MapEvents::
	map_events NULL, RocketHideout_Elevator_MapWarps, NULL, RocketHideout_Elevator_MapBGEvents

@ ===== END data/maps/RocketHideout_Elevator/events.inc =====
@ ===== BEGIN data/maps/SilphCo_1F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SilphCo_1F/map.json
@

	.align 2

SilphCo_1F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_WORKER_F, 3, 7, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SilphCo_1F_EventScript_Receptionist, FLAG_HIDE_SAFFRON_CIVILIANS

SilphCo_1F_MapWarps:
	warp_def 7, 21, 0, 0, MAP_SAFFRON_CITY
	warp_def 8, 20, 3, 0, MAP_SAFFRON_CITY
	warp_def 9, 20, 3, 0, MAP_SAFFRON_CITY
	warp_def 31, 2, 3, 3, MAP_SILPH_CO_2F
	warp_def 22, 3, 0, 0, MAP_SILPH_CO_ELEVATOR

SilphCo_1F_MapBGEvents:
	bg_sign_event 30, 1, 0, BG_EVENT_PLAYER_FACING_ANY, SilphCo_1F_EventScript_FloorSign

SilphCo_1F_MapEvents::
	map_events SilphCo_1F_ObjectEvents, SilphCo_1F_MapWarps, NULL, SilphCo_1F_MapBGEvents

@ ===== END data/maps/SilphCo_1F/events.inc =====
@ ===== BEGIN data/maps/SilphCo_2F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SilphCo_2F/map.json
@

	.align 2

SilphCo_2F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_ROCKET_M, 29, 12, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NORMAL, 5, SilphCo_2F_EventScript_Grunt2, FLAG_HIDE_SILPH_ROCKETS
	object_event 2, OBJ_EVENT_GFX_SCIENTIST, 28, 18, 3, MOVEMENT_TYPE_FACE_UP_AND_LEFT, 1, 1, TRAINER_TYPE_NORMAL, 4, SilphCo_2F_EventScript_Jerry, FLAG_HIDE_SILPH_ROCKETS
	object_event 3, OBJ_EVENT_GFX_ROCKET_M, 20, 14, 3, MOVEMENT_TYPE_FACE_DOWN_AND_UP, 1, 1, TRAINER_TYPE_NORMAL, 3, SilphCo_2F_EventScript_Grunt1, FLAG_HIDE_SILPH_ROCKETS
	object_event 4, OBJ_EVENT_GFX_SCIENTIST, 5, 19, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NORMAL, 0, SilphCo_2F_EventScript_Connor, FLAG_HIDE_SILPH_ROCKETS
	object_event 5, OBJ_EVENT_GFX_WOMAN_2, 10, 4, 0, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NONE, 0, SilphCo_2F_EventScript_ThunderWaveTutor, 0

SilphCo_2F_MapWarps:
	warp_def 28, 2, 3, 0, MAP_SILPH_CO_3F
	warp_def 2, 6, 3, 8, MAP_SILPH_CO_3F
	warp_def 15, 6, 3, 5, MAP_SILPH_CO_8F
	warp_def 30, 2, 3, 3, MAP_SILPH_CO_1F
	warp_def 7, 19, 3, 1, MAP_SILPH_CO_6F
	warp_def 33, 19, 3, 2, MAP_SILPH_CO_8F
	warp_def 22, 3, 0, 0, MAP_SILPH_CO_ELEVATOR

SilphCo_2F_MapBGEvents:
	bg_sign_event 5, 8, 0, BG_EVENT_PLAYER_FACING_ANY, SilphCo_2F_EventScript_Door1
	bg_sign_event 6, 8, 0, BG_EVENT_PLAYER_FACING_ANY, SilphCo_2F_EventScript_Door1
	bg_sign_event 5, 9, 0, BG_EVENT_PLAYER_FACING_ANY, SilphCo_2F_EventScript_Door1
	bg_sign_event 6, 9, 0, BG_EVENT_PLAYER_FACING_ANY, SilphCo_2F_EventScript_Door1
	bg_sign_event 5, 15, 0, BG_EVENT_PLAYER_FACING_ANY, SilphCo_2F_EventScript_Door2
	bg_sign_event 6, 15, 0, BG_EVENT_PLAYER_FACING_ANY, SilphCo_2F_EventScript_Door2
	bg_sign_event 5, 16, 0, BG_EVENT_PLAYER_FACING_ANY, SilphCo_2F_EventScript_Door2
	bg_sign_event 6, 16, 0, BG_EVENT_PLAYER_FACING_ANY, SilphCo_2F_EventScript_Door2
	bg_hidden_item_event 11, 21, 0, ITEM_ULTRA_BALL, FLAG_HIDDEN_ITEM_SILPH_CO_2F_ULTRA_BALL, 1, FALSE
	bg_sign_event 29, 1, 0, BG_EVENT_PLAYER_FACING_ANY, SilphCo_2F_EventScript_FloorSign

SilphCo_2F_MapEvents::
	map_events SilphCo_2F_ObjectEvents, SilphCo_2F_MapWarps, NULL, SilphCo_2F_MapBGEvents

@ ===== END data/maps/SilphCo_2F/events.inc =====
@ ===== BEGIN data/maps/SilphCo_3F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SilphCo_3F/map.json
@

	.align 2

SilphCo_3F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_ROCKET_M, 25, 9, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NORMAL, 3, SilphCo_3F_EventScript_Grunt, FLAG_HIDE_SILPH_ROCKETS
	object_event 2, OBJ_EVENT_GFX_WORKER_M, 31, 13, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, SilphCo_3F_EventScript_WorkerM, 0
	object_event 3, OBJ_EVENT_GFX_SCIENTIST, 4, 12, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NORMAL, 0, SilphCo_3F_EventScript_Jose, FLAG_HIDE_SILPH_ROCKETS
	object_event 4, OBJ_EVENT_GFX_ITEM_BALL, 8, 10, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SilphCo_3F_EventScript_ItemHyperPotion, FLAG_HIDE_SILPH_CO_3F_HYPER_POTION

SilphCo_3F_MapWarps:
	warp_def 28, 2, 3, 0, MAP_SILPH_CO_2F
	warp_def 4, 6, 3, 1, MAP_SILPH_CO_5F
	warp_def 13, 14, 3, 4, MAP_SILPH_CO_7F
	warp_def 30, 2, 3, 2, MAP_SILPH_CO_4F
	warp_def 2, 14, 3, 2, MAP_SILPH_CO_9F
	warp_def 3, 20, 3, 4, MAP_SILPH_CO_5F
	warp_def 29, 14, 3, 7, MAP_SILPH_CO_3F
	warp_def 32, 20, 3, 6, MAP_SILPH_CO_3F
	warp_def 33, 5, 3, 1, MAP_SILPH_CO_2F
	warp_def 22, 3, 0, 0, MAP_SILPH_CO_ELEVATOR

SilphCo_3F_MapBGEvents:
	bg_sign_event 10, 12, 3, BG_EVENT_PLAYER_FACING_ANY, SilphCo_3F_EventScript_Door1
	bg_sign_event 10, 13, 3, BG_EVENT_PLAYER_FACING_ANY, SilphCo_3F_EventScript_Door1
	bg_sign_event 21, 12, 3, BG_EVENT_PLAYER_FACING_ANY, SilphCo_3F_EventScript_Door2
	bg_sign_event 21, 13, 3, BG_EVENT_PLAYER_FACING_ANY, SilphCo_3F_EventScript_Door2
	bg_sign_event 9, 12, 3, BG_EVENT_PLAYER_FACING_ANY, SilphCo_3F_EventScript_Door1
	bg_sign_event 9, 13, 3, BG_EVENT_PLAYER_FACING_ANY, SilphCo_3F_EventScript_Door1
	bg_sign_event 20, 12, 3, BG_EVENT_PLAYER_FACING_ANY, SilphCo_3F_EventScript_Door2
	bg_sign_event 20, 13, 3, BG_EVENT_PLAYER_FACING_ANY, SilphCo_3F_EventScript_Door2
	bg_hidden_item_event 34, 18, 0, ITEM_PROTEIN, FLAG_HIDDEN_ITEM_SILPH_CO_3F_PROTEIN, 1, FALSE
	bg_sign_event 29, 1, 0, BG_EVENT_PLAYER_FACING_ANY, SilphCo_3F_EventScript_FloorSign

SilphCo_3F_MapEvents::
	map_events SilphCo_3F_ObjectEvents, SilphCo_3F_MapWarps, NULL, SilphCo_3F_MapBGEvents

@ ===== END data/maps/SilphCo_3F/events.inc =====
@ ===== BEGIN data/maps/SilphCo_4F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SilphCo_4F/map.json
@

	.align 2

SilphCo_4F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_ROCKET_M, 33, 16, 3, MOVEMENT_TYPE_WANDER_AROUND, 1, 1, TRAINER_TYPE_NORMAL, 1, SilphCo_4F_EventScript_Grunt2, FLAG_HIDE_SILPH_ROCKETS
	object_event 2, OBJ_EVENT_GFX_ROCKET_M, 10, 19, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 5, SilphCo_4F_EventScript_Grunt1, FLAG_HIDE_SILPH_ROCKETS
	object_event 3, OBJ_EVENT_GFX_SCIENTIST, 14, 8, 3, MOVEMENT_TYPE_FACE_DOWN_AND_LEFT, 1, 1, TRAINER_TYPE_NORMAL, 2, SilphCo_4F_EventScript_Rodney, FLAG_HIDE_SILPH_ROCKETS
	object_event 4, OBJ_EVENT_GFX_WORKER_M, 5, 5, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, SilphCo_4F_EventScript_WorkerM, 0
	object_event 5, OBJ_EVENT_GFX_ITEM_BALL, 3, 11, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SilphCo_4F_EventScript_ItemMaxRevive, FLAG_HIDE_SILPH_CO_4F_MAX_REVIVE
	object_event 6, OBJ_EVENT_GFX_ITEM_BALL, 4, 12, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SilphCo_4F_EventScript_ItemEscapeRope, FLAG_HIDE_SILPH_CO_4F_ESCAPE_ROPE
	object_event 7, OBJ_EVENT_GFX_ITEM_BALL, 2, 13, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SilphCo_4F_EventScript_ItemFullHeal, FLAG_HIDE_SILPH_CO_4F_FULL_HEAL
	object_event 8, OBJ_EVENT_GFX_ITEM_BALL, 30, 18, 0, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SilphCo_4F_EventScript_ItemTM41, FLAG_HIDE_SILPH_CO_4F_TM41

SilphCo_4F_MapWarps:
	warp_def 28, 2, 3, 0, MAP_SILPH_CO_5F
	warp_def 18, 6, 3, 3, MAP_SILPH_CO_6F
	warp_def 30, 2, 3, 3, MAP_SILPH_CO_3F
	warp_def 12, 9, 3, 1, MAP_SILPH_CO_10F
	warp_def 2, 20, 3, 4, MAP_SILPH_CO_10F
	warp_def 18, 14, 3, 2, MAP_SILPH_CO_10F
	warp_def 22, 3, 0, 0, MAP_SILPH_CO_ELEVATOR

SilphCo_4F_MapBGEvents:
	bg_sign_event 3, 16, 0, BG_EVENT_PLAYER_FACING_ANY, SilphCo_4F_EventScript_Door1
	bg_sign_event 4, 16, 0, BG_EVENT_PLAYER_FACING_ANY, SilphCo_4F_EventScript_Door1
	bg_sign_event 3, 17, 0, BG_EVENT_PLAYER_FACING_ANY, SilphCo_4F_EventScript_Door1
	bg_sign_event 4, 17, 0, BG_EVENT_PLAYER_FACING_ANY, SilphCo_4F_EventScript_Door1
	bg_sign_event 15, 11, 0, BG_EVENT_PLAYER_FACING_ANY, SilphCo_4F_EventScript_Door2
	bg_sign_event 14, 11, 0, BG_EVENT_PLAYER_FACING_ANY, SilphCo_4F_EventScript_Door2
	bg_sign_event 14, 12, 0, BG_EVENT_PLAYER_FACING_ANY, SilphCo_4F_EventScript_Door2
	bg_sign_event 15, 12, 0, BG_EVENT_PLAYER_FACING_ANY, SilphCo_4F_EventScript_Door2
	bg_hidden_item_event 35, 20, 0, ITEM_IRON, FLAG_HIDDEN_ITEM_SILPH_CO_4F_IRON, 1, FALSE
	bg_sign_event 29, 1, 0, BG_EVENT_PLAYER_FACING_ANY, SilphCo_4F_EventScript_FloorSign

SilphCo_4F_MapEvents::
	map_events SilphCo_4F_ObjectEvents, SilphCo_4F_MapWarps, NULL, SilphCo_4F_MapBGEvents

@ ===== END data/maps/SilphCo_4F/events.inc =====
@ ===== BEGIN data/maps/SilphCo_5F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SilphCo_5F/map.json
@

	.align 2

SilphCo_5F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_ROCKET_M, 35, 7, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NORMAL, 2, SilphCo_5F_EventScript_Grunt2, FLAG_HIDE_SILPH_ROCKETS
	object_event 2, OBJ_EVENT_GFX_ROCKER, 23, 13, 3, MOVEMENT_TYPE_FACE_DOWN_AND_UP, 1, 1, TRAINER_TYPE_NORMAL, 4, SilphCo_5F_EventScript_Dalton, FLAG_HIDE_SILPH_ROCKETS
	object_event 3, OBJ_EVENT_GFX_WORKER_M, 16, 13, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, SilphCo_5F_EventScript_WorkerM, 0
	object_event 4, OBJ_EVENT_GFX_SCIENTIST, 11, 6, 3, MOVEMENT_TYPE_WANDER_AROUND, 1, 1, TRAINER_TYPE_NORMAL, 1, SilphCo_5F_EventScript_Beau, FLAG_HIDE_SILPH_ROCKETS
	object_event 5, OBJ_EVENT_GFX_ROCKET_M, 9, 21, 3, MOVEMENT_TYPE_FACE_UP_AND_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 3, SilphCo_5F_EventScript_Grunt1, FLAG_HIDE_SILPH_ROCKETS
	object_event 6, OBJ_EVENT_GFX_ITEM_BALL, 4, 9, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SilphCo_5F_EventScript_ItemProtein, FLAG_HIDE_SILPH_CO_5F_PROTEIN
	object_event 7, OBJ_EVENT_GFX_ITEM_BALL, 1, 18, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SilphCo_5F_EventScript_ItemTM01, FLAG_HIDE_SILPH_CO_5F_TM01
	object_event 8, OBJ_EVENT_GFX_ITEM_BALL, 22, 21, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SilphCo_5F_EventScript_ItemCardKey, FLAG_HIDE_SILPH_CO_5F_CARD_KEY
	object_event 9, OBJ_EVENT_GFX_SCIENTIST, 2, 7, 3, MOVEMENT_TYPE_WALK_RIGHT_AND_LEFT, 2, 1, TRAINER_TYPE_NONE, 0, SilphCo_5F_EventScript_Scientist, 0

SilphCo_5F_MapWarps:
	warp_def 28, 2, 3, 0, MAP_SILPH_CO_4F
	warp_def 15, 7, 3, 1, MAP_SILPH_CO_3F
	warp_def 30, 2, 3, 2, MAP_SILPH_CO_6F
	warp_def 10, 20, 3, 1, MAP_SILPH_CO_9F
	warp_def 2, 20, 3, 5, MAP_SILPH_CO_3F
	warp_def 33, 5, 3, 2, MAP_SILPH_CO_7F
	warp_def 22, 3, 0, 0, MAP_SILPH_CO_ELEVATOR

SilphCo_5F_MapBGEvents:
	bg_hidden_item_event 13, 16, 0, ITEM_ELIXIR, FLAG_HIDDEN_ITEM_SILPH_CO_5F_ELIXIR, 1, FALSE
	bg_sign_event 8, 9, 0, BG_EVENT_PLAYER_FACING_ANY, SilphCo_5F_EventScript_Door1
	bg_sign_event 8, 10, 0, BG_EVENT_PLAYER_FACING_ANY, SilphCo_5F_EventScript_Door1
	bg_sign_event 8, 18, 0, BG_EVENT_PLAYER_FACING_ANY, SilphCo_5F_EventScript_Door2
	bg_sign_event 8, 19, 0, BG_EVENT_PLAYER_FACING_ANY, SilphCo_5F_EventScript_Door2
	bg_sign_event 19, 13, 0, BG_EVENT_PLAYER_FACING_ANY, SilphCo_5F_EventScript_Door3
	bg_sign_event 19, 14, 0, BG_EVENT_PLAYER_FACING_ANY, SilphCo_5F_EventScript_Door3
	bg_sign_event 7, 9, 0, BG_EVENT_PLAYER_FACING_ANY, SilphCo_5F_EventScript_Door1
	bg_sign_event 7, 10, 0, BG_EVENT_PLAYER_FACING_ANY, SilphCo_5F_EventScript_Door1
	bg_sign_event 7, 19, 0, BG_EVENT_PLAYER_FACING_ANY, SilphCo_5F_EventScript_Door2
	bg_sign_event 7, 18, 0, BG_EVENT_PLAYER_FACING_ANY, SilphCo_5F_EventScript_Door2
	bg_sign_event 18, 13, 0, BG_EVENT_PLAYER_FACING_ANY, SilphCo_5F_EventScript_Door3
	bg_sign_event 18, 14, 0, BG_EVENT_PLAYER_FACING_ANY, SilphCo_5F_EventScript_Door3
	bg_sign_event 28, 11, 0, BG_EVENT_PLAYER_FACING_ANY, SilphCo_5F_EventScript_PokemonReport3
	bg_sign_event 30, 13, 0, BG_EVENT_PLAYER_FACING_ANY, SilphCo_5F_EventScript_PokemonReport2
	bg_sign_event 25, 15, 0, BG_EVENT_PLAYER_FACING_ANY, SilphCo_5F_EventScript_PokemonReport1
	bg_hidden_item_event 32, 9, 0, ITEM_PP_UP, FLAG_HIDDEN_ITEM_SILPH_CO_5F_PP_UP, 1, FALSE
	bg_sign_event 29, 1, 0, BG_EVENT_PLAYER_FACING_ANY, SilphCo_5F_EventScript_FloorSign

SilphCo_5F_MapEvents::
	map_events SilphCo_5F_ObjectEvents, SilphCo_5F_MapWarps, NULL, SilphCo_5F_MapBGEvents

@ ===== END data/maps/SilphCo_5F/events.inc =====
@ ===== BEGIN data/maps/SilphCo_6F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SilphCo_6F/map.json
@

	.align 2

SilphCo_6F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_ROCKET_M, 21, 5, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 2, SilphCo_6F_EventScript_Grunt1, FLAG_HIDE_SILPH_ROCKETS
	object_event 2, OBJ_EVENT_GFX_WORKER_M, 23, 9, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SilphCo_6F_EventScript_WorkerM1, 0
	object_event 3, OBJ_EVENT_GFX_WORKER_F, 24, 9, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SilphCo_6F_EventScript_WorkerF1, 0
	object_event 4, OBJ_EVENT_GFX_WORKER_M, 22, 13, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NONE, 0, SilphCo_6F_EventScript_WorkerM2, 0
	object_event 5, OBJ_EVENT_GFX_WORKER_M, 14, 9, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, SilphCo_6F_EventScript_WorkerM3, 0
	object_event 6, OBJ_EVENT_GFX_WORKER_F, 16, 12, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, SilphCo_6F_EventScript_WorkerF2, 0
	object_event 7, OBJ_EVENT_GFX_SCIENTIST, 9, 11, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 4, SilphCo_6F_EventScript_Taylor, FLAG_HIDE_SILPH_ROCKETS
	object_event 8, OBJ_EVENT_GFX_ITEM_BALL, 2, 14, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SilphCo_6F_EventScript_ItemHPUp, FLAG_HIDE_SILPH_CO_6F_HP_UP
	object_event 9, OBJ_EVENT_GFX_ITEM_BALL, 1, 17, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SilphCo_6F_EventScript_ItemXSpecial, FLAG_HIDE_SILPH_CO_6F_X_SPECIAL
	object_event 10, OBJ_EVENT_GFX_ROCKET_M, 18, 17, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NORMAL, 2, SilphCo_6F_EventScript_Grunt2, FLAG_HIDE_SILPH_ROCKETS

SilphCo_6F_MapWarps:
	warp_def 14, 2, 3, 0, MAP_SILPH_CO_7F
	warp_def 29, 5, 3, 4, MAP_SILPH_CO_2F
	warp_def 26, 2, 3, 2, MAP_SILPH_CO_5F
	warp_def 2, 6, 3, 1, MAP_SILPH_CO_4F
	warp_def 20, 3, 0, 0, MAP_SILPH_CO_ELEVATOR

SilphCo_6F_MapBGEvents:
	bg_sign_event 6, 15, 0, BG_EVENT_PLAYER_FACING_ANY, SilphCo_6F_EventScript_Door
	bg_sign_event 6, 16, 0, BG_EVENT_PLAYER_FACING_ANY, SilphCo_6F_EventScript_Door
	bg_sign_event 5, 15, 0, BG_EVENT_PLAYER_FACING_ANY, SilphCo_6F_EventScript_Door
	bg_sign_event 5, 16, 0, BG_EVENT_PLAYER_FACING_ANY, SilphCo_6F_EventScript_Door
	bg_hidden_item_event 1, 8, 0, ITEM_CARBOS, FLAG_HIDDEN_ITEM_SILPH_CO_6F_CARBOS, 1, FALSE
	bg_sign_event 25, 1, 0, BG_EVENT_PLAYER_FACING_ANY, SilphCo_6F_EventScript_FloorSign

SilphCo_6F_MapEvents::
	map_events SilphCo_6F_ObjectEvents, SilphCo_6F_MapWarps, NULL, SilphCo_6F_MapBGEvents

@ ===== END data/maps/SilphCo_6F/events.inc =====
@ ===== BEGIN data/maps/SilphCo_7F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SilphCo_7F/map.json
@

	.align 2

SilphCo_7F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_BLUE, 2, 6, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NONE, 0, 0x0, FLAG_HIDE_SILPH_RIVAL
	object_event 2, OBJ_EVENT_GFX_WORKER_M, 0, 7, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, SilphCo_7F_EventScript_LaprasGuy, 0
	object_event 3, OBJ_EVENT_GFX_ROCKET_M, 24, 5, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NORMAL, 4, SilphCo_7F_EventScript_Grunt1, FLAG_HIDE_SILPH_ROCKETS
	object_event 4, OBJ_EVENT_GFX_ROCKET_M, 24, 15, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 2, SilphCo_7F_EventScript_Grunt2, FLAG_HIDE_SILPH_ROCKETS
	object_event 5, OBJ_EVENT_GFX_ROCKET_M, 13, 4, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 3, SilphCo_7F_EventScript_Grunt3, FLAG_HIDE_SILPH_ROCKETS
	object_event 6, OBJ_EVENT_GFX_WORKER_F, 10, 10, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, SilphCo_7F_EventScript_WorkerF, 0
	object_event 7, OBJ_EVENT_GFX_WORKER_M, 13, 14, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NONE, 0, SilphCo_7F_EventScript_WorkerM1, 0
	object_event 8, OBJ_EVENT_GFX_WORKER_M, 9, 14, 3, MOVEMENT_TYPE_WALK_LEFT_AND_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, SilphCo_7F_EventScript_WorkerM2, 0
	object_event 9, OBJ_EVENT_GFX_SCIENTIST, 3, 13, 3, MOVEMENT_TYPE_WANDER_LEFT_AND_RIGHT, 2, 1, TRAINER_TYPE_NORMAL, 1, SilphCo_7F_EventScript_Joshua, FLAG_HIDE_SILPH_ROCKETS
	object_event 10, OBJ_EVENT_GFX_ITEM_BALL, 0, 12, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SilphCo_7F_EventScript_ItemCalcium, FLAG_HIDE_SILPH_CO_7F_CALCIUM
	object_event 11, OBJ_EVENT_GFX_ITEM_BALL, 30, 11, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SilphCo_7F_EventScript_ItemTM08, FLAG_HIDE_SILPH_CO_7F_TM08

SilphCo_7F_MapWarps:
	warp_def 19, 2, 3, 0, MAP_SILPH_CO_6F
	warp_def 5, 8, 3, 1, MAP_SILPH_CO_11F
	warp_def 25, 17, 3, 5, MAP_SILPH_CO_5F
	warp_def 27, 2, 3, 3, MAP_SILPH_CO_8F
	warp_def 5, 4, 3, 2, MAP_SILPH_CO_3F
	warp_def 23, 3, 0, 0, MAP_SILPH_CO_ELEVATOR

SilphCo_7F_MapCoordEvents:
	coord_event 2, 4, 3, VAR_MAP_SCENE_SILPH_CO_7F, 0, SilphCo_7F_EventScript_RivalTriggerTop
	coord_event 2, 5, 3, VAR_MAP_SCENE_SILPH_CO_7F, 0, SilphCo_7F_EventScript_RivalTriggerBottom

SilphCo_7F_MapBGEvents:
	bg_sign_event 11, 8, 0, BG_EVENT_PLAYER_FACING_ANY, SilphCo_7F_EventScript_Door1
	bg_sign_event 12, 8, 0, BG_EVENT_PLAYER_FACING_ANY, SilphCo_7F_EventScript_Door1
	bg_sign_event 11, 9, 0, BG_EVENT_PLAYER_FACING_ANY, SilphCo_7F_EventScript_Door1
	bg_sign_event 12, 9, 0, BG_EVENT_PLAYER_FACING_ANY, SilphCo_7F_EventScript_Door1
	bg_sign_event 24, 7, 0, BG_EVENT_PLAYER_FACING_ANY, SilphCo_7F_EventScript_Door2
	bg_sign_event 25, 7, 0, BG_EVENT_PLAYER_FACING_ANY, SilphCo_7F_EventScript_Door2
	bg_sign_event 25, 8, 0, BG_EVENT_PLAYER_FACING_ANY, SilphCo_7F_EventScript_Door2
	bg_sign_event 24, 8, 0, BG_EVENT_PLAYER_FACING_ANY, SilphCo_7F_EventScript_Door2
	bg_sign_event 25, 13, 0, BG_EVENT_PLAYER_FACING_ANY, SilphCo_7F_EventScript_Door3
	bg_sign_event 26, 13, 0, BG_EVENT_PLAYER_FACING_ANY, SilphCo_7F_EventScript_Door3
	bg_sign_event 25, 14, 0, BG_EVENT_PLAYER_FACING_ANY, SilphCo_7F_EventScript_Door3
	bg_sign_event 26, 14, 0, BG_EVENT_PLAYER_FACING_ANY, SilphCo_7F_EventScript_Door3
	bg_hidden_item_event 22, 11, 0, ITEM_ZINC, FLAG_HIDDEN_ITEM_SILPH_CO_7F_ZINC, 1, FALSE
	bg_sign_event 20, 1, 0, BG_EVENT_PLAYER_FACING_ANY, SilphCo_7F_EventScript_FloorSign

SilphCo_7F_MapEvents::
	map_events SilphCo_7F_ObjectEvents, SilphCo_7F_MapWarps, SilphCo_7F_MapCoordEvents, SilphCo_7F_MapBGEvents

@ ===== END data/maps/SilphCo_7F/events.inc =====
@ ===== BEGIN data/maps/SilphCo_8F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SilphCo_8F/map.json
@

	.align 2

SilphCo_8F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_ROCKET_M, 28, 5, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NORMAL, 4, SilphCo_8F_EventScript_Grunt1, FLAG_HIDE_SILPH_ROCKETS
	object_event 2, OBJ_EVENT_GFX_ROCKET_M, 10, 17, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 5, SilphCo_8F_EventScript_Grunt2, FLAG_HIDE_SILPH_ROCKETS
	object_event 3, OBJ_EVENT_GFX_SCIENTIST, 9, 4, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 2, SilphCo_8F_EventScript_Parker, FLAG_HIDE_SILPH_ROCKETS
	object_event 4, OBJ_EVENT_GFX_WORKER_M, 2, 5, 3, MOVEMENT_TYPE_WANDER_LEFT_AND_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, SilphCo_8F_EventScript_WorkerM, 0
	object_event 5, OBJ_EVENT_GFX_ITEM_BALL, 24, 8, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SilphCo_8F_EventScript_ItemIron, FLAG_HIDE_SILPH_CO_8F_IRON
	object_event 6, OBJ_EVENT_GFX_SCIENTIST, 29, 9, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SilphCo_8F_EventScript_Scientist, 0

SilphCo_8F_MapWarps:
	warp_def 16, 2, 3, 0, MAP_SILPH_CO_9F
	warp_def 11, 10, 3, 4, MAP_SILPH_CO_8F
	warp_def 10, 6, 3, 5, MAP_SILPH_CO_2F
	warp_def 28, 2, 3, 3, MAP_SILPH_CO_7F
	warp_def 2, 12, 3, 1, MAP_SILPH_CO_8F
	warp_def 2, 17, 3, 2, MAP_SILPH_CO_2F
	warp_def 22, 3, 0, 0, MAP_SILPH_CO_ELEVATOR

SilphCo_8F_MapBGEvents:
	bg_sign_event 6, 10, 0, BG_EVENT_PLAYER_FACING_ANY, SilphCo_8F_EventScript_Door
	bg_sign_event 6, 11, 0, BG_EVENT_PLAYER_FACING_ANY, SilphCo_8F_EventScript_Door
	bg_sign_event 5, 11, 0, BG_EVENT_PLAYER_FACING_ANY, SilphCo_8F_EventScript_Door
	bg_sign_event 5, 10, 0, BG_EVENT_PLAYER_FACING_ANY, SilphCo_8F_EventScript_Door
	bg_hidden_item_event 29, 10, 0, ITEM_NUGGET, FLAG_HIDDEN_ITEM_SILPH_CO_8F_NUGGET, 1, FALSE
	bg_sign_event 27, 1, 0, BG_EVENT_PLAYER_FACING_ANY, SilphCo_8F_EventScript_FloorSign

SilphCo_8F_MapEvents::
	map_events SilphCo_8F_ObjectEvents, SilphCo_8F_MapWarps, NULL, SilphCo_8F_MapBGEvents

@ ===== END data/maps/SilphCo_8F/events.inc =====
@ ===== BEGIN data/maps/SilphCo_9F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SilphCo_9F/map.json
@

	.align 2

SilphCo_9F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_SCIENTIST, 26, 16, 3, MOVEMENT_TYPE_WANDER_UP_AND_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 2, SilphCo_9F_EventScript_Ed, FLAG_HIDE_SILPH_ROCKETS
	object_event 2, OBJ_EVENT_GFX_ROCKET_M, 15, 18, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NORMAL, 3, SilphCo_9F_EventScript_Grunt2, FLAG_HIDE_SILPH_ROCKETS
	object_event 3, OBJ_EVENT_GFX_WOMAN_2, 2, 16, 0, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SilphCo_9F_EventScript_HealWoman, 0
	object_event 4, OBJ_EVENT_GFX_ROCKET_M, 1, 6, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 5, SilphCo_9F_EventScript_Grunt1, FLAG_HIDE_SILPH_ROCKETS

SilphCo_9F_MapWarps:
	warp_def 16, 2, 0, 0, MAP_SILPH_CO_8F
	warp_def 22, 18, 3, 3, MAP_SILPH_CO_5F
	warp_def 9, 4, 3, 4, MAP_SILPH_CO_3F
	warp_def 18, 2, 3, 3, MAP_SILPH_CO_10F
	warp_def 24, 3, 0, 0, MAP_SILPH_CO_ELEVATOR

SilphCo_9F_MapBGEvents:
	bg_hidden_item_event 11, 14, 3, ITEM_MAX_POTION, FLAG_HIDDEN_ITEM_SILPH_CO_9F_MAX_POTION, 1, FALSE
	bg_sign_event 3, 10, 0, BG_EVENT_PLAYER_FACING_ANY, SilphCo_9F_EventScript_Door1
	bg_sign_event 3, 11, 0, BG_EVENT_PLAYER_FACING_ANY, SilphCo_9F_EventScript_Door1
	bg_sign_event 13, 16, 0, BG_EVENT_PLAYER_FACING_ANY, SilphCo_9F_EventScript_Door2
	bg_sign_event 13, 17, 0, BG_EVENT_PLAYER_FACING_ANY, SilphCo_9F_EventScript_Door2
	bg_sign_event 21, 6, 0, BG_EVENT_PLAYER_FACING_ANY, SilphCo_9F_EventScript_Door3
	bg_sign_event 22, 6, 0, BG_EVENT_PLAYER_FACING_ANY, SilphCo_9F_EventScript_Door3
	bg_sign_event 22, 7, 0, BG_EVENT_PLAYER_FACING_ANY, SilphCo_9F_EventScript_Door3
	bg_sign_event 21, 7, 0, BG_EVENT_PLAYER_FACING_ANY, SilphCo_9F_EventScript_Door3
	bg_sign_event 21, 13, 0, BG_EVENT_PLAYER_FACING_ANY, SilphCo_9F_EventScript_Door4
	bg_sign_event 21, 12, 0, BG_EVENT_PLAYER_FACING_ANY, SilphCo_9F_EventScript_Door4
	bg_sign_event 22, 12, 0, BG_EVENT_PLAYER_FACING_ANY, SilphCo_9F_EventScript_Door4
	bg_sign_event 22, 13, 0, BG_EVENT_PLAYER_FACING_ANY, SilphCo_9F_EventScript_Door4
	bg_sign_event 2, 11, 0, BG_EVENT_PLAYER_FACING_ANY, SilphCo_9F_EventScript_Door1
	bg_sign_event 2, 10, 0, BG_EVENT_PLAYER_FACING_ANY, SilphCo_9F_EventScript_Door1
	bg_sign_event 12, 16, 0, BG_EVENT_PLAYER_FACING_ANY, SilphCo_9F_EventScript_Door2
	bg_sign_event 12, 17, 0, BG_EVENT_PLAYER_FACING_ANY, SilphCo_9F_EventScript_Door2
	bg_hidden_item_event 5, 8, 0, ITEM_CALCIUM, FLAG_HIDDEN_ITEM_SILPH_CO_9F_CALCIUM, 1, FALSE
	bg_sign_event 17, 1, 0, BG_EVENT_PLAYER_FACING_ANY, SilphCo_9F_EventScript_FloorSign

SilphCo_9F_MapEvents::
	map_events SilphCo_9F_ObjectEvents, SilphCo_9F_MapWarps, NULL, SilphCo_9F_MapBGEvents

@ ===== END data/maps/SilphCo_9F/events.inc =====
@ ===== BEGIN data/maps/SilphCo_10F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SilphCo_10F/map.json
@

	.align 2

SilphCo_10F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_SCIENTIST, 2, 7, 3, MOVEMENT_TYPE_WANDER_AROUND, 2, 2, TRAINER_TYPE_NORMAL, 1, SilphCo_10F_EventScript_Travis, FLAG_HIDE_SILPH_ROCKETS
	object_event 2, OBJ_EVENT_GFX_WORKER_F, 10, 17, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SilphCo_10F_EventScript_WorkerF, 0
	object_event 3, OBJ_EVENT_GFX_ROCKET_M, 0, 13, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 4, SilphCo_10F_EventScript_Grunt, FLAG_HIDE_SILPH_ROCKETS
	object_event 4, OBJ_EVENT_GFX_ITEM_BALL, 5, 15, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SilphCo_10F_EventScript_ItemCarbos, FLAG_HIDE_SILPH_CO_10F_CARBOS
	object_event 5, OBJ_EVENT_GFX_ITEM_BALL, 2, 15, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SilphCo_10F_EventScript_ItemUltraBall, FLAG_HIDE_SILPH_CO_10F_ULTRA_BALL
	object_event 6, OBJ_EVENT_GFX_ITEM_BALL, 3, 17, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SilphCo_10F_EventScript_ItemRareCandy, FLAG_HIDE_SILPH_CO_10F_RARE_CANDY

SilphCo_10F_MapWarps:
	warp_def 6, 2, 3, 0, MAP_SILPH_CO_11F
	warp_def 10, 14, 3, 3, MAP_SILPH_CO_4F
	warp_def 14, 9, 3, 5, MAP_SILPH_CO_4F
	warp_def 8, 2, 3, 3, MAP_SILPH_CO_9F
	warp_def 14, 17, 3, 4, MAP_SILPH_CO_4F
	warp_def 13, 3, 0, 0, MAP_SILPH_CO_ELEVATOR

SilphCo_10F_MapBGEvents:
	bg_sign_event 12, 11, 0, BG_EVENT_PLAYER_FACING_ANY, SilphCo_10F_EventScript_Door
	bg_sign_event 13, 11, 0, BG_EVENT_PLAYER_FACING_ANY, SilphCo_10F_EventScript_Door
	bg_sign_event 12, 12, 0, BG_EVENT_PLAYER_FACING_ANY, SilphCo_10F_EventScript_Door
	bg_sign_event 13, 12, 0, BG_EVENT_PLAYER_FACING_ANY, SilphCo_10F_EventScript_Door
	bg_hidden_item_event 9, 9, 0, ITEM_HP_UP, FLAG_HIDDEN_ITEM_SILPH_CO_10F_HP_UP, 1, FALSE
	bg_sign_event 7, 1, 0, BG_EVENT_PLAYER_FACING_ANY, SilphCo_10F_EventScript_FloorSign

SilphCo_10F_MapEvents::
	map_events SilphCo_10F_ObjectEvents, SilphCo_10F_MapWarps, NULL, SilphCo_10F_MapBGEvents

@ ===== END data/maps/SilphCo_10F/events.inc =====
@ ===== BEGIN data/maps/SilphCo_11F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SilphCo_11F/map.json
@

	.align 2

SilphCo_11F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_OLD_MAN_2, 9, 9, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SilphCo_11F_EventScript_President, 0
	object_event 2, OBJ_EVENT_GFX_WORKER_F, 11, 9, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SilphCo_11F_EventScript_Secretary, 0
	object_event 3, OBJ_EVENT_GFX_GIOVANNI, 6, 11, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, 0x0, FLAG_HIDE_SILPH_ROCKETS
	object_event 4, OBJ_EVENT_GFX_ROCKET_M, 16, 12, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NORMAL, 5, SilphCo_11F_EventScript_Grunt1, FLAG_HIDE_SILPH_ROCKETS
	object_event 5, OBJ_EVENT_GFX_ITEM_BALL, 16, 18, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SilphCo_11F_EventScript_ItemZinc, FLAG_HIDE_SILPH_CO_11F_ZINC
	object_event 6, OBJ_EVENT_GFX_ROCKET_M, 2, 19, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NORMAL, 5, SilphCo_11F_EventScript_Grunt2, FLAG_HIDE_SILPH_ROCKETS

SilphCo_11F_MapWarps:
	warp_def 7, 2, 3, 0, MAP_SILPH_CO_10F
	warp_def 2, 5, 3, 1, MAP_SILPH_CO_7F
	warp_def 13, 3, 0, 0, MAP_SILPH_CO_ELEVATOR

SilphCo_11F_MapCoordEvents:
	coord_event 5, 15, 3, VAR_MAP_SCENE_SILPH_CO_11F, 0, SilphCo_11F_EventScript_GiovanniTriggerLeft
	coord_event 6, 15, 3, VAR_MAP_SCENE_SILPH_CO_11F, 0, SilphCo_11F_EventScript_GiovanniTriggerRight

SilphCo_11F_MapBGEvents:
	bg_sign_event 5, 16, 3, BG_EVENT_PLAYER_FACING_ANY, SilphCo_11F_EventScript_Door
	bg_sign_event 5, 17, 3, BG_EVENT_PLAYER_FACING_ANY, SilphCo_11F_EventScript_Door
	bg_sign_event 6, 16, 3, BG_EVENT_PLAYER_FACING_ANY, SilphCo_11F_EventScript_Door
	bg_sign_event 6, 17, 3, BG_EVENT_PLAYER_FACING_ANY, SilphCo_11F_EventScript_Door
	bg_hidden_item_event 10, 18, 0, ITEM_REVIVE, FLAG_HIDDEN_ITEM_SILPH_CO_11F_REVIVE, 1, FALSE
	bg_sign_event 8, 1, 0, BG_EVENT_PLAYER_FACING_ANY, SilphCo_11F_EventScript_FloorSign

SilphCo_11F_MapEvents::
	map_events SilphCo_11F_ObjectEvents, SilphCo_11F_MapWarps, SilphCo_11F_MapCoordEvents, SilphCo_11F_MapBGEvents

@ ===== END data/maps/SilphCo_11F/events.inc =====
@ ===== BEGIN data/maps/SilphCo_Elevator/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SilphCo_Elevator/map.json
@

	.align 2

SilphCo_Elevator_MapWarps:
	warp_def 2, 5, 3, WARP_ID_DYNAMIC, MAP_DYNAMIC

SilphCo_Elevator_MapBGEvents:
	bg_sign_event 0, 2, 3, BG_EVENT_PLAYER_FACING_ANY, SilphCo_Elevator_EventScript_FloorSelect

SilphCo_Elevator_MapEvents::
	map_events NULL, SilphCo_Elevator_MapWarps, NULL, SilphCo_Elevator_MapBGEvents

@ ===== END data/maps/SilphCo_Elevator/events.inc =====
@ ===== BEGIN data/maps/PokemonMansion_1F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/PokemonMansion_1F/map.json
@

	.align 2

PokemonMansion_1F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_SCIENTIST, 22, 24, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NORMAL, 4, PokemonMansion_1F_EventScript_Ted, 0
	object_event 2, OBJ_EVENT_GFX_ITEM_BALL, 29, 32, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, PokemonMansion_1F_EventScript_ItemCarbos, FLAG_HIDE_POKEMON_MANSION_1F_CARBOS
	object_event 3, OBJ_EVENT_GFX_ITEM_BALL, 22, 6, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, PokemonMansion_1F_EventScript_ItemEscapeRope, FLAG_HIDE_POKEMON_MANSION_1F_ESCAPE_ROPE
	object_event 4, OBJ_EVENT_GFX_ITEM_BALL, 27, 15, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, PokemonMansion_1F_EventScript_ItemProtein, FLAG_HIDE_POKEMON_MANSION_1F_PROTEIN
	object_event 5, OBJ_EVENT_GFX_YOUNGSTER, 8, 8, 3, MOVEMENT_TYPE_WANDER_LEFT_AND_RIGHT, 2, 1, TRAINER_TYPE_NORMAL, 1, PokemonMansion_1F_EventScript_Johnson, 0

PokemonMansion_1F_MapWarps:
	warp_def 7, 33, 3, 0, MAP_CINNABAR_ISLAND
	warp_def 8, 33, 3, 0, MAP_CINNABAR_ISLAND
	warp_def 9, 33, 3, 0, MAP_CINNABAR_ISLAND
	warp_def 10, 13, 3, 2, MAP_POKEMON_MANSION_2F
	warp_def 25, 27, 3, 0, MAP_POKEMON_MANSION_B1F
	warp_def 34, 33, 3, 0, MAP_CINNABAR_ISLAND
	warp_def 35, 34, 0, 0, MAP_CINNABAR_ISLAND
	warp_def 19, 22, 3, 3, MAP_POKEMON_MANSION_3F
	warp_def 20, 22, 3, 4, MAP_POKEMON_MANSION_3F
	warp_def 11, 13, 0, 2, MAP_POKEMON_MANSION_2F

PokemonMansion_1F_MapBGEvents:
	bg_sign_event 5, 5, 0, BG_EVENT_PLAYER_FACING_NORTH, PokemonMansion_1F_EventScript_Statue
	bg_hidden_item_event 2, 21, 0, ITEM_MOON_STONE, FLAG_HIDDEN_ITEM_POKEMON_MANSION_1F_MOON_STONE, 1, FALSE

PokemonMansion_1F_MapEvents::
	map_events PokemonMansion_1F_ObjectEvents, PokemonMansion_1F_MapWarps, NULL, PokemonMansion_1F_MapBGEvents

@ ===== END data/maps/PokemonMansion_1F/events.inc =====
@ ===== BEGIN data/maps/PokemonMansion_2F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/PokemonMansion_2F/map.json
@

	.align 2

PokemonMansion_2F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_POKE_MANIAC, 5, 23, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NORMAL, 1, PokemonMansion_2F_EventScript_Arnie, 0
	object_event 2, OBJ_EVENT_GFX_ITEM_BALL, 36, 8, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, PokemonMansion_2F_EventScript_ItemCalcium, FLAG_HIDE_POKEMON_MANSION_2F_CALCIUM
	object_event 3, OBJ_EVENT_GFX_ITEM_BALL, 18, 23, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, PokemonMansion_2F_EventScript_ItemZinc, FLAG_HIDE_POKEMON_MANSION_2F_ZINC
	object_event 4, OBJ_EVENT_GFX_ITEM_BALL, 35, 17, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, PokemonMansion_2F_EventScript_ItemHPUp, FLAG_HIDE_POKEMON_MANSION_2F_HP_UP

PokemonMansion_2F_MapWarps:
	warp_def 9, 3, 3, 0, MAP_POKEMON_MANSION_3F
	warp_def 34, 22, 3, 1, MAP_POKEMON_MANSION_3F
	warp_def 6, 14, 3, 3, MAP_POKEMON_MANSION_1F
	warp_def 9, 14, 3, 2, MAP_POKEMON_MANSION_3F
	warp_def 27, 17, 3, 5, MAP_POKEMON_MANSION_3F

PokemonMansion_2F_MapBGEvents:
	bg_sign_event 2, 16, 0, BG_EVENT_PLAYER_FACING_NORTH, PokemonMansion_2F_EventScript_Statue
	bg_sign_event 6, 31, 0, BG_EVENT_PLAYER_FACING_ANY, PokemonMansion_2F_EventScript_DiaryJuly10th
	bg_sign_event 25, 4, 0, BG_EVENT_PLAYER_FACING_ANY, PokemonMansion_2F_EventScript_DiaryJuly5th

PokemonMansion_2F_MapEvents::
	map_events PokemonMansion_2F_ObjectEvents, PokemonMansion_2F_MapWarps, NULL, PokemonMansion_2F_MapBGEvents

@ ===== END data/maps/PokemonMansion_2F/events.inc =====
@ ===== BEGIN data/maps/PokemonMansion_3F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/PokemonMansion_3F/map.json
@

	.align 2

PokemonMansion_3F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_POKE_MANIAC, 7, 13, 3, MOVEMENT_TYPE_WANDER_AROUND, 1, 1, TRAINER_TYPE_NORMAL, 1, PokemonMansion_3F_EventScript_Simon, 0
	object_event 2, OBJ_EVENT_GFX_SCIENTIST, 22, 13, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 1, PokemonMansion_3F_EventScript_Braydon, 0
	object_event 3, OBJ_EVENT_GFX_ITEM_BALL, 9, 19, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, PokemonMansion_3F_EventScript_ItemMaxPotion, FLAG_HIDE_POKEMON_MANSION_3F_MAX_POTION
	object_event 4, OBJ_EVENT_GFX_ITEM_BALL, 32, 6, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, PokemonMansion_3F_EventScript_ItemIron, FLAG_HIDE_POKEMON_MANSION_3F_IRON

PokemonMansion_3F_MapWarps:
	warp_def 8, 3, 3, 0, MAP_POKEMON_MANSION_2F
	warp_def 34, 18, 3, 1, MAP_POKEMON_MANSION_2F
	warp_def 11, 11, 3, 3, MAP_POKEMON_MANSION_2F
	warp_def 18, 18, 3, 7, MAP_POKEMON_MANSION_1F
	warp_def 19, 18, 3, 8, MAP_POKEMON_MANSION_1F
	warp_def 23, 18, 3, 4, MAP_POKEMON_MANSION_2F
	warp_def 20, 18, 3, 8, MAP_POKEMON_MANSION_1F
	warp_def 24, 18, 3, 4, MAP_POKEMON_MANSION_2F

PokemonMansion_3F_MapBGEvents:
	bg_sign_event 8, 16, 0, BG_EVENT_PLAYER_FACING_ANY, PokemonMansion_3F_EventScript_DiaryFeb6th
	bg_sign_event 12, 5, 0, BG_EVENT_PLAYER_FACING_NORTH, PokemonMansion_3F_EventScript_Statue
	bg_hidden_item_event 36, 13, 3, ITEM_RARE_CANDY, FLAG_HIDDEN_ITEM_POKEMON_MANSION_3F_RARE_CANDY, 1, FALSE

PokemonMansion_3F_MapEvents::
	map_events PokemonMansion_3F_ObjectEvents, PokemonMansion_3F_MapWarps, NULL, PokemonMansion_3F_MapBGEvents

@ ===== END data/maps/PokemonMansion_3F/events.inc =====
@ ===== BEGIN data/maps/PokemonMansion_B1F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/PokemonMansion_B1F/map.json
@

	.align 2

PokemonMansion_B1F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_ITEM_BALL, 6, 21, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, PokemonMansion_B1F_EventScript_ItemTM22, FLAG_HIDE_POKEMON_MANSION_B1F_TM22
	object_event 2, OBJ_EVENT_GFX_POKE_MANIAC, 20, 25, 3, MOVEMENT_TYPE_WANDER_AROUND, 1, 1, TRAINER_TYPE_NORMAL, 1, PokemonMansion_B1F_EventScript_Lewis, 0
	object_event 3, OBJ_EVENT_GFX_SCIENTIST, 34, 13, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 6, PokemonMansion_B1F_EventScript_Ivan, 0
	object_event 4, OBJ_EVENT_GFX_ITEM_BALL, 23, 4, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, PokemonMansion_B1F_EventScript_ItemTM14, FLAG_HIDE_POKEMON_MANSION_B1F_TM14
	object_event 5, OBJ_EVENT_GFX_ITEM_BALL, 2, 29, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, PokemonMansion_B1F_EventScript_ItemFullRestore, FLAG_HIDE_POKEMON_MANSION_B1F_FULL_RESTORE
	object_event 6, OBJ_EVENT_GFX_ITEM_BALL, 5, 7, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, PokemonMansion_B1F_EventScript_ItemSecretKey, FLAG_HIDE_POKEMON_MANSION_B1F_SECRET_KEY

PokemonMansion_B1F_MapWarps:
	warp_def 34, 29, 3, 4, MAP_POKEMON_MANSION_1F

PokemonMansion_B1F_MapBGEvents:
	bg_sign_event 21, 27, 0, BG_EVENT_PLAYER_FACING_ANY, PokemonMansion_B1F_EventScript_DiarySep1st
	bg_sign_event 24, 29, 0, BG_EVENT_PLAYER_FACING_NORTH, PokemonMansion_B1F_EventScript_Statue
	bg_sign_event 27, 5, 0, BG_EVENT_PLAYER_FACING_NORTH, PokemonMansion_B1F_EventScript_Statue
	bg_hidden_item_event 35, 5, 3, ITEM_ELIXIR, FLAG_HIDDEN_ITEM_POKEMON_MANSION_B1F_ELIXIR, 1, FALSE

PokemonMansion_B1F_MapEvents::
	map_events PokemonMansion_B1F_ObjectEvents, PokemonMansion_B1F_MapWarps, NULL, PokemonMansion_B1F_MapBGEvents

@ ===== END data/maps/PokemonMansion_B1F/events.inc =====
@ ===== BEGIN data/maps/SafariZone_Center/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SafariZone_Center/map.json
@

	.align 2

SafariZone_Center_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_ITEM_BALL, 24, 15, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SafariZone_Center_EventScript_ItemNugget, FLAG_HIDE_SAFARI_ZONE_CENTER_NUGGET

SafariZone_Center_MapWarps:
	warp_def 25, 30, 3, 0, MAP_FUCHSIA_CITY_SAFARI_ZONE_ENTRANCE
	warp_def 26, 30, 3, 0, MAP_FUCHSIA_CITY_SAFARI_ZONE_ENTRANCE
	warp_def 27, 30, 3, 0, MAP_FUCHSIA_CITY_SAFARI_ZONE_ENTRANCE
	warp_def 25, 5, 3, 9, MAP_SAFARI_ZONE_NORTH
	warp_def 26, 5, 3, 10, MAP_SAFARI_ZONE_NORTH
	warp_def 27, 5, 0, 11, MAP_SAFARI_ZONE_NORTH
	warp_def 8, 17, 3, 6, MAP_SAFARI_ZONE_WEST
	warp_def 8, 18, 3, 7, MAP_SAFARI_ZONE_WEST
	warp_def 8, 19, 0, 8, MAP_SAFARI_ZONE_WEST
	warp_def 43, 15, 3, 3, MAP_SAFARI_ZONE_EAST
	warp_def 43, 16, 3, 4, MAP_SAFARI_ZONE_EAST
	warp_def 43, 17, 0, 5, MAP_SAFARI_ZONE_EAST
	warp_def 29, 25, 0, 1, MAP_SAFARI_ZONE_CENTER_REST_HOUSE

SafariZone_Center_MapBGEvents:
	bg_sign_event 30, 26, 0, BG_EVENT_PLAYER_FACING_ANY, SafariZone_Center_EventScript_RestHouseSign
	bg_sign_event 25, 27, 0, BG_EVENT_PLAYER_FACING_ANY, SafariZone_Center_EventScript_TrainerTips
	bg_hidden_item_event 27, 15, 3, ITEM_LEAF_STONE, FLAG_HIDDEN_ITEM_SAFARI_ZONE_CENTER_LEAF_STONE, 1, FALSE
	bg_sign_event 33, 20, 0, BG_EVENT_PLAYER_FACING_ANY, SafariZone_Center_EventScript_AreaSign

SafariZone_Center_MapEvents::
	map_events SafariZone_Center_ObjectEvents, SafariZone_Center_MapWarps, NULL, SafariZone_Center_MapBGEvents

@ ===== END data/maps/SafariZone_Center/events.inc =====
@ ===== BEGIN data/maps/SafariZone_East/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SafariZone_East/map.json
@

	.align 2

SafariZone_East_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_ITEM_BALL, 13, 12, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SafariZone_East_EventScript_ItemMaxPotion, FLAG_HIDE_SAFARI_ZONE_EAST_MAX_POTION
	object_event 2, OBJ_EVENT_GFX_ITEM_BALL, 37, 15, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SafariZone_East_EventScript_ItemFullRestore, FLAG_HIDE_SAFARI_ZONE_EAST_FULL_RESTORE
	object_event 3, OBJ_EVENT_GFX_ITEM_BALL, 31, 18, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SafariZone_East_EventScript_ItemTM11, FLAG_HIDE_SAFARI_ZONE_EAST_TM11
	object_event 4, OBJ_EVENT_GFX_ITEM_BALL, 36, 17, 4, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SafariZone_East_EventScript_ItemLeafStone, FLAG_HIDE_SAFARI_ZONE_EAST_LEAF_STONE

SafariZone_East_MapWarps:
	warp_def 8, 9, 3, 6, MAP_SAFARI_ZONE_NORTH
	warp_def 8, 10, 3, 7, MAP_SAFARI_ZONE_NORTH
	warp_def 8, 11, 0, 8, MAP_SAFARI_ZONE_NORTH
	warp_def 8, 26, 3, 9, MAP_SAFARI_ZONE_CENTER
	warp_def 8, 27, 3, 10, MAP_SAFARI_ZONE_CENTER
	warp_def 8, 28, 0, 11, MAP_SAFARI_ZONE_CENTER
	warp_def 40, 14, 0, 1, MAP_SAFARI_ZONE_EAST_REST_HOUSE

SafariZone_East_MapBGEvents:
	bg_sign_event 18, 27, 0, BG_EVENT_PLAYER_FACING_ANY, SafariZone_East_EventScript_AreaSign
	bg_sign_event 43, 15, 0, BG_EVENT_PLAYER_FACING_ANY, SafariZone_East_EventScript_RestHouseSign
	bg_sign_event 17, 8, 0, BG_EVENT_PLAYER_FACING_ANY, SafariZone_East_EventScript_TrainerTips

SafariZone_East_MapEvents::
	map_events SafariZone_East_ObjectEvents, SafariZone_East_MapWarps, NULL, SafariZone_East_MapBGEvents

@ ===== END data/maps/SafariZone_East/events.inc =====
@ ===== BEGIN data/maps/SafariZone_North/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SafariZone_North/map.json
@

	.align 2

SafariZone_North_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_ITEM_BALL, 33, 5, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SafariZone_North_EventScript_ItemProtein, FLAG_HIDE_SAFARI_ZONE_NORTH_PROTEIN
	object_event 2, OBJ_EVENT_GFX_ITEM_BALL, 28, 9, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SafariZone_North_EventScript_ItemTM47, FLAG_HIDE_SAFARI_ZONE_NORTH_TM47
	object_event 3, OBJ_EVENT_GFX_ITEM_BALL, 29, 17, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SafariZone_North_EventScript_ItemQuickClaw, FLAG_HIDE_SAFARI_ZONE_NORTH_QUICK_CLAW

SafariZone_North_MapWarps:
	warp_def 10, 34, 3, 0, MAP_SAFARI_ZONE_WEST
	warp_def 11, 34, 3, 1, MAP_SAFARI_ZONE_WEST
	warp_def 12, 34, 0, 2, MAP_SAFARI_ZONE_WEST
	warp_def 20, 34, 3, 3, MAP_SAFARI_ZONE_WEST
	warp_def 21, 34, 3, 4, MAP_SAFARI_ZONE_WEST
	warp_def 22, 34, 0, 5, MAP_SAFARI_ZONE_WEST
	warp_def 48, 31, 3, 0, MAP_SAFARI_ZONE_EAST
	warp_def 48, 32, 3, 1, MAP_SAFARI_ZONE_EAST
	warp_def 48, 33, 0, 2, MAP_SAFARI_ZONE_EAST
	warp_def 30, 34, 3, 3, MAP_SAFARI_ZONE_CENTER
	warp_def 31, 34, 3, 4, MAP_SAFARI_ZONE_CENTER
	warp_def 32, 34, 0, 5, MAP_SAFARI_ZONE_CENTER
	warp_def 43, 8, 0, 1, MAP_SAFARI_ZONE_NORTH_REST_HOUSE

SafariZone_North_MapBGEvents:
	bg_sign_event 13, 27, 0, BG_EVENT_PLAYER_FACING_ANY, SafariZone_North_EventScript_TrainerTips1
	bg_sign_event 23, 31, 0, BG_EVENT_PLAYER_FACING_ANY, SafariZone_North_EventScript_AreaSign
	bg_sign_event 29, 32, 0, BG_EVENT_PLAYER_FACING_ANY, SafariZone_North_EventScript_TrainerTips2
	bg_sign_event 34, 28, 0, BG_EVENT_PLAYER_FACING_ANY, SafariZone_North_EventScript_TrainerTips3
	bg_sign_event 44, 9, 0, BG_EVENT_PLAYER_FACING_ANY, SafariZone_North_EventScript_RestHouseSign

SafariZone_North_MapEvents::
	map_events SafariZone_North_ObjectEvents, SafariZone_North_MapWarps, NULL, SafariZone_North_MapBGEvents

@ ===== END data/maps/SafariZone_North/events.inc =====
@ ===== BEGIN data/maps/SafariZone_West/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SafariZone_West/map.json
@

	.align 2

SafariZone_West_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_ITEM_BALL, 28, 14, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SafariZone_West_EventScript_ItemGoldTeeth, FLAG_HIDE_SAFARI_ZONE_WEST_GOLD_TEETH
	object_event 2, OBJ_EVENT_GFX_ITEM_BALL, 17, 13, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SafariZone_West_EventScript_ItemTM32, FLAG_HIDE_SAFARI_ZONE_WEST_TM32
	object_event 3, OBJ_EVENT_GFX_ITEM_BALL, 16, 27, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SafariZone_West_EventScript_ItemMaxPotion, FLAG_HIDE_SAFARI_ZONE_WEST_MAX_POTION
	object_event 4, OBJ_EVENT_GFX_ITEM_BALL, 27, 24, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SafariZone_West_EventScript_ItemMaxRevive, FLAG_HIDE_SAFARI_ZONE_WEST_MAX_REVIVE

SafariZone_West_MapWarps:
	warp_def 30, 5, 3, 0, MAP_SAFARI_ZONE_NORTH
	warp_def 31, 5, 3, 1, MAP_SAFARI_ZONE_NORTH
	warp_def 32, 5, 0, 2, MAP_SAFARI_ZONE_NORTH
	warp_def 37, 5, 3, 3, MAP_SAFARI_ZONE_NORTH
	warp_def 38, 5, 3, 4, MAP_SAFARI_ZONE_NORTH
	warp_def 39, 5, 0, 5, MAP_SAFARI_ZONE_NORTH
	warp_def 40, 26, 3, 6, MAP_SAFARI_ZONE_CENTER
	warp_def 40, 27, 3, 7, MAP_SAFARI_ZONE_CENTER
	warp_def 40, 28, 0, 8, MAP_SAFARI_ZONE_CENTER
	warp_def 12, 7, 0, 1, MAP_SAFARI_ZONE_SECRET_HOUSE
	warp_def 19, 18, 0, 1, MAP_SAFARI_ZONE_WEST_REST_HOUSE

SafariZone_West_MapBGEvents:
	bg_sign_event 27, 9, 0, BG_EVENT_PLAYER_FACING_ANY, SafariZone_West_EventScript_LostTeethNotice
	bg_sign_event 36, 10, 0, BG_EVENT_PLAYER_FACING_ANY, SafariZone_West_EventScript_TrainerTips
	bg_sign_event 35, 26, 0, BG_EVENT_PLAYER_FACING_ANY, SafariZone_West_EventScript_AreaSign
	bg_sign_event 22, 19, 0, BG_EVENT_PLAYER_FACING_ANY, SafariZone_West_EventScript_RestHouseSign
	bg_hidden_item_event 13, 11, 3, ITEM_REVIVE, FLAG_HIDDEN_ITEM_SAFARI_ZONE_WEST_REVIVE, 1, FALSE

SafariZone_West_MapEvents::
	map_events SafariZone_West_ObjectEvents, SafariZone_West_MapWarps, NULL, SafariZone_West_MapBGEvents

@ ===== END data/maps/SafariZone_West/events.inc =====
@ ===== BEGIN data/maps/SafariZone_Center_RestHouse/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SafariZone_Center_RestHouse/map.json
@

	.align 2

SafariZone_Center_RestHouse_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_SCIENTIST, 3, 4, 3, MOVEMENT_TYPE_WANDER_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, SafariZone_Center_RestHouse_EventScript_Scientist, 0
	object_event 2, OBJ_EVENT_GFX_WOMAN_1, 7, 3, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SafariZone_Center_RestHouse_EventScript_Sara, 0

SafariZone_Center_RestHouse_MapWarps:
	warp_def 3, 9, 3, 12, MAP_SAFARI_ZONE_CENTER
	warp_def 4, 9, 3, 12, MAP_SAFARI_ZONE_CENTER
	warp_def 5, 9, 3, 12, MAP_SAFARI_ZONE_CENTER

SafariZone_Center_RestHouse_MapEvents::
	map_events SafariZone_Center_RestHouse_ObjectEvents, SafariZone_Center_RestHouse_MapWarps, NULL, NULL

@ ===== END data/maps/SafariZone_Center_RestHouse/events.inc =====
@ ===== BEGIN data/maps/SafariZone_East_RestHouse/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SafariZone_East_RestHouse/map.json
@

	.align 2

SafariZone_East_RestHouse_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_SCIENTIST, 3, 5, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, SafariZone_East_RestHouse_EventScript_Scientist, 0
	object_event 2, OBJ_EVENT_GFX_ROCKER, 6, 3, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SafariZone_East_RestHouse_EventScript_Rocker, 0
	object_event 3, OBJ_EVENT_GFX_BALDING_MAN, 7, 3, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SafariZone_East_RestHouse_EventScript_BaldingMan, 0

SafariZone_East_RestHouse_MapWarps:
	warp_def 3, 9, 3, 6, MAP_SAFARI_ZONE_EAST
	warp_def 4, 9, 3, 6, MAP_SAFARI_ZONE_EAST
	warp_def 5, 9, 3, 6, MAP_SAFARI_ZONE_EAST

SafariZone_East_RestHouse_MapEvents::
	map_events SafariZone_East_RestHouse_ObjectEvents, SafariZone_East_RestHouse_MapWarps, NULL, NULL

@ ===== END data/maps/SafariZone_East_RestHouse/events.inc =====
@ ===== BEGIN data/maps/SafariZone_North_RestHouse/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SafariZone_North_RestHouse/map.json
@

	.align 2

SafariZone_North_RestHouse_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_GENTLEMAN, 3, 4, 3, MOVEMENT_TYPE_WANDER_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, SafariZone_North_RestHouse_EventScript_Gentleman, 0
	object_event 2, OBJ_EVENT_GFX_SCIENTIST, 7, 5, 3, MOVEMENT_TYPE_WANDER_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, SafariZone_North_RestHouse_EventScript_Scientist, 0
	object_event 3, OBJ_EVENT_GFX_FISHER, 6, 2, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, SafariZone_North_RestHouse_EventScript_Fisher, 0
	object_event 4, OBJ_EVENT_GFX_BALDING_MAN, 11, 2, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NONE, 0, SafariZone_North_RestHouse_EventScript_BaldingMan, 0

SafariZone_North_RestHouse_MapWarps:
	warp_def 3, 9, 3, 12, MAP_SAFARI_ZONE_NORTH
	warp_def 4, 9, 3, 12, MAP_SAFARI_ZONE_NORTH
	warp_def 5, 9, 3, 12, MAP_SAFARI_ZONE_NORTH

SafariZone_North_RestHouse_MapEvents::
	map_events SafariZone_North_RestHouse_ObjectEvents, SafariZone_North_RestHouse_MapWarps, NULL, NULL

@ ===== END data/maps/SafariZone_North_RestHouse/events.inc =====
@ ===== BEGIN data/maps/SafariZone_West_RestHouse/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SafariZone_West_RestHouse/map.json
@

	.align 2

SafariZone_West_RestHouse_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_SCIENTIST, 3, 4, 3, MOVEMENT_TYPE_WANDER_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, SafariZone_West_RestHouse_EventScript_Scientist, 0
	object_event 2, OBJ_EVENT_GFX_MAN, 2, 2, 0, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, SafariZone_West_RestHouse_EventScript_Man, 0
	object_event 3, OBJ_EVENT_GFX_COOLTRAINER_F, 7, 3, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, SafariZone_West_RestHouse_EventScript_CooltrainerF, 0

SafariZone_West_RestHouse_MapWarps:
	warp_def 3, 9, 3, 10, MAP_SAFARI_ZONE_WEST
	warp_def 4, 9, 3, 10, MAP_SAFARI_ZONE_WEST
	warp_def 5, 9, 3, 10, MAP_SAFARI_ZONE_WEST

SafariZone_West_RestHouse_MapEvents::
	map_events SafariZone_West_RestHouse_ObjectEvents, SafariZone_West_RestHouse_MapWarps, NULL, NULL

@ ===== END data/maps/SafariZone_West_RestHouse/events.inc =====
@ ===== BEGIN data/maps/SafariZone_SecretHouse/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SafariZone_SecretHouse/map.json
@

	.align 2

SafariZone_SecretHouse_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_WORKER_M, 6, 5, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SafariZone_SecretHouse_EventScript_Attendant, 0

SafariZone_SecretHouse_MapWarps:
	warp_def 3, 9, 3, 9, MAP_SAFARI_ZONE_WEST
	warp_def 4, 9, 3, 9, MAP_SAFARI_ZONE_WEST
	warp_def 5, 9, 3, 9, MAP_SAFARI_ZONE_WEST

SafariZone_SecretHouse_MapEvents::
	map_events SafariZone_SecretHouse_ObjectEvents, SafariZone_SecretHouse_MapWarps, NULL, NULL

@ ===== END data/maps/SafariZone_SecretHouse/events.inc =====
@ ===== BEGIN data/maps/CeruleanCave_1F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/CeruleanCave_1F/map.json
@

	.align 2

CeruleanCave_1F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_ITEM_BALL, 7, 3, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, CeruleanCave_1F_EventScript_ItemNugget, FLAG_HIDE_CERULEAN_CAVE_1F_NUGGET
	object_event 2, OBJ_EVENT_GFX_ITEM_BALL, 11, 16, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, CeruleanCave_1F_EventScript_ItemFullRestore, FLAG_HIDE_CERULEAN_CAVE_1F_FULL_RESTORE
	object_event 3, OBJ_EVENT_GFX_ITEM_BALL, 25, 5, 4, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, CeruleanCave_1F_EventScript_ItemMaxElixir, FLAG_HIDE_CERULEAN_CAVE_1F_MAX_ELIXIR
	object_event 4, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 7, 21, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_12
	object_event 5, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 13, 21, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_13
	object_event 6, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 5, 20, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_14
	object_event 7, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 14, 20, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_15
	object_event 8, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 11, 21, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_16
	object_event 9, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 9, 18, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_17

CeruleanCave_1F_MapWarps:
	warp_def 33, 21, 3, 7, MAP_CERULEAN_CITY
	warp_def 34, 2, 3, 0, MAP_CERULEAN_CAVE_2F
	warp_def 1, 7, 3, 0, MAP_CERULEAN_CAVE_B1F
	warp_def 10, 2, 3, 1, MAP_CERULEAN_CAVE_2F
	warp_def 5, 15, 3, 2, MAP_CERULEAN_CAVE_2F
	warp_def 30, 10, 4, 3, MAP_CERULEAN_CAVE_2F
	warp_def 24, 11, 3, 4, MAP_CERULEAN_CAVE_2F
	warp_def 2, 4, 3, 5, MAP_CERULEAN_CAVE_2F

CeruleanCave_1F_MapBGEvents:
	bg_hidden_item_event 12, 2, 3, ITEM_ULTRA_BALL, FLAG_HIDDEN_ITEM_CERULEAN_CAVE_1F_ULTRA_BALL, 1, FALSE

CeruleanCave_1F_MapEvents::
	map_events CeruleanCave_1F_ObjectEvents, CeruleanCave_1F_MapWarps, NULL, CeruleanCave_1F_MapBGEvents

@ ===== END data/maps/CeruleanCave_1F/events.inc =====
@ ===== BEGIN data/maps/CeruleanCave_2F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/CeruleanCave_2F/map.json
@

	.align 2

CeruleanCave_2F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_ITEM_BALL, 9, 18, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, CeruleanCave_2F_EventScript_ItemPPUp, FLAG_HIDE_CERULEAN_CAVE_2F_PP_UP
	object_event 2, OBJ_EVENT_GFX_ITEM_BALL, 29, 16, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, CeruleanCave_2F_EventScript_ItemUltraBall, FLAG_HIDE_CERULEAN_CAVE_2F_ULTRA_BALL
	object_event 3, OBJ_EVENT_GFX_ITEM_BALL, 33, 12, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, CeruleanCave_2F_EventScript_ItemFullRestore, FLAG_HIDE_CERULEAN_CAVE_2F_FULL_RESTORE
	object_event 4, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 33, 10, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_12
	object_event 5, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 33, 9, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_13
	object_event 6, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 25, 11, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_14
	object_event 7, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 28, 20, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_15
	object_event 8, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 30, 20, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_16
	object_event 9, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 9, 13, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_17
	object_event 10, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 23, 16, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_18
	object_event 11, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 13, 6, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_19
	object_event 12, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 4, 12, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_1A
	object_event 13, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 10, 20, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_1B

CeruleanCave_2F_MapWarps:
	warp_def 33, 4, 3, 1, MAP_CERULEAN_CAVE_1F
	warp_def 13, 4, 3, 3, MAP_CERULEAN_CAVE_1F
	warp_def 7, 14, 3, 4, MAP_CERULEAN_CAVE_1F
	warp_def 26, 9, 3, 5, MAP_CERULEAN_CAVE_1F
	warp_def 23, 10, 3, 6, MAP_CERULEAN_CAVE_1F
	warp_def 5, 6, 3, 7, MAP_CERULEAN_CAVE_1F

CeruleanCave_2F_MapEvents::
	map_events CeruleanCave_2F_ObjectEvents, CeruleanCave_2F_MapWarps, NULL, NULL

@ ===== END data/maps/CeruleanCave_2F/events.inc =====
@ ===== BEGIN data/maps/CeruleanCave_B1F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/CeruleanCave_B1F/map.json
@

	.align 2

CeruleanCave_B1F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_ITEM_BALL, 31, 9, 4, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, CeruleanCave_B1F_EventScript_ItemUltraBall, FLAG_HIDE_CERULEAN_CAVE_B1F_ULTRA_BALL
	object_event 2, OBJ_EVENT_GFX_ITEM_BALL, 32, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, CeruleanCave_B1F_EventScript_ItemMaxRevive, FLAG_HIDE_CERULEAN_CAVE_B1F_MAX_REVIVE
	object_event 3, OBJ_EVENT_GFX_MEWTWO, 7, 12, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, CeruleanCave_B1F_EventScript_Mewtwo, FLAG_HIDE_MEWTWO
	object_event 4, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 37, 1, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_12
	object_event 5, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 38, 2, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_13
	object_event 6, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 35, 1, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_14
	object_event 7, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 37, 4, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_15
	object_event 8, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 35, 5, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_16
	object_event 9, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 2, 2, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_17
	object_event 10, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 4, 1, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_18
	object_event 11, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 6, 1, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_19
	object_event 12, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 3, 4, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_1A

CeruleanCave_B1F_MapWarps:
	warp_def 5, 7, 3, 2, MAP_CERULEAN_CAVE_1F

CeruleanCave_B1F_MapEvents::
	map_events CeruleanCave_B1F_ObjectEvents, CeruleanCave_B1F_MapWarps, NULL, NULL

@ ===== END data/maps/CeruleanCave_B1F/events.inc =====
@ ===== BEGIN data/maps/PokemonLeague_LoreleisRoom/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/PokemonLeague_LoreleisRoom/map.json
@

	.align 2

PokemonLeague_LoreleisRoom_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_LORELEI, 6, 5, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, PokemonLeague_LoreleisRoom_EventScript_Lorelei, 0

PokemonLeague_LoreleisRoom_MapWarps:
	warp_def 6, 12, 0, 1, MAP_INDIGO_PLATEAU_POKEMON_CENTER_1F
	warp_def 6, 2, 0, 0, MAP_POKEMON_LEAGUE_BRUNOS_ROOM

PokemonLeague_LoreleisRoom_MapEvents::
	map_events PokemonLeague_LoreleisRoom_ObjectEvents, PokemonLeague_LoreleisRoom_MapWarps, NULL, NULL

@ ===== END data/maps/PokemonLeague_LoreleisRoom/events.inc =====
@ ===== BEGIN data/maps/PokemonLeague_BrunosRoom/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/PokemonLeague_BrunosRoom/map.json
@

	.align 2

PokemonLeague_BrunosRoom_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_BRUNO, 6, 5, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, PokemonLeague_BrunosRoom_EventScript_Bruno, 0

PokemonLeague_BrunosRoom_MapWarps:
	warp_def 6, 12, 0, 1, MAP_POKEMON_LEAGUE_LORELEIS_ROOM
	warp_def 6, 2, 0, 0, MAP_POKEMON_LEAGUE_AGATHAS_ROOM

PokemonLeague_BrunosRoom_MapEvents::
	map_events PokemonLeague_BrunosRoom_ObjectEvents, PokemonLeague_BrunosRoom_MapWarps, NULL, NULL

@ ===== END data/maps/PokemonLeague_BrunosRoom/events.inc =====
@ ===== BEGIN data/maps/PokemonLeague_AgathasRoom/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/PokemonLeague_AgathasRoom/map.json
@

	.align 2

PokemonLeague_AgathasRoom_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_AGATHA, 6, 5, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, PokemonLeague_AgathasRoom_EventScript_Agatha, 0

PokemonLeague_AgathasRoom_MapWarps:
	warp_def 6, 12, 0, 1, MAP_POKEMON_LEAGUE_BRUNOS_ROOM
	warp_def 6, 2, 0, 0, MAP_POKEMON_LEAGUE_LANCES_ROOM

PokemonLeague_AgathasRoom_MapEvents::
	map_events PokemonLeague_AgathasRoom_ObjectEvents, PokemonLeague_AgathasRoom_MapWarps, NULL, NULL

@ ===== END data/maps/PokemonLeague_AgathasRoom/events.inc =====
@ ===== BEGIN data/maps/PokemonLeague_LancesRoom/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/PokemonLeague_LancesRoom/map.json
@

	.align 2

PokemonLeague_LancesRoom_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_LANCE, 6, 8, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, PokemonLeague_LancesRoom_EventScript_Lance, 0

PokemonLeague_LancesRoom_MapWarps:
	warp_def 23, 13, 3, 1, MAP_POKEMON_LEAGUE_AGATHAS_ROOM
	warp_def 6, 5, 0, 0, MAP_POKEMON_LEAGUE_CHAMPIONS_ROOM

PokemonLeague_LancesRoom_MapEvents::
	map_events PokemonLeague_LancesRoom_ObjectEvents, PokemonLeague_LancesRoom_MapWarps, NULL, NULL

@ ===== END data/maps/PokemonLeague_LancesRoom/events.inc =====
@ ===== BEGIN data/maps/PokemonLeague_ChampionsRoom/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/PokemonLeague_ChampionsRoom/map.json
@

	.align 2

PokemonLeague_ChampionsRoom_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_BLUE, 6, 8, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, 0x0, 0
	object_event 2, OBJ_EVENT_GFX_PROF_OAK, 6, 15, 0, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NONE, 0, 0x0, FLAG_HIDE_OAK_IN_CHAMP_ROOM

PokemonLeague_ChampionsRoom_MapWarps:
	warp_def 6, 19, 3, 1, MAP_POKEMON_LEAGUE_LANCES_ROOM
	warp_def 6, 2, 3, 0, MAP_POKEMON_LEAGUE_HALL_OF_FAME

PokemonLeague_ChampionsRoom_MapEvents::
	map_events PokemonLeague_ChampionsRoom_ObjectEvents, PokemonLeague_ChampionsRoom_MapWarps, NULL, NULL

@ ===== END data/maps/PokemonLeague_ChampionsRoom/events.inc =====
@ ===== BEGIN data/maps/PokemonLeague_HallOfFame/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/PokemonLeague_HallOfFame/map.json
@

	.align 2

PokemonLeague_HallOfFame_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_PROF_OAK, 6, 4, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, 0x0, 0

PokemonLeague_HallOfFame_MapWarps:
	warp_def 5, 12, 3, 1, MAP_POKEMON_LEAGUE_CHAMPIONS_ROOM

PokemonLeague_HallOfFame_MapEvents::
	map_events PokemonLeague_HallOfFame_ObjectEvents, PokemonLeague_HallOfFame_MapWarps, NULL, NULL

@ ===== END data/maps/PokemonLeague_HallOfFame/events.inc =====
@ ===== BEGIN data/maps/RockTunnel_1F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/RockTunnel_1F/map.json
@

	.align 2

RockTunnel_1F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_PICNICKER, 26, 28, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 3, RockTunnel_1F_EventScript_Dana, 0
	object_event 2, OBJ_EVENT_GFX_PICNICKER, 39, 27, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 4, RockTunnel_1F_EventScript_Ariana, 0
	object_event 3, OBJ_EVENT_GFX_PICNICKER, 45, 24, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NORMAL, 5, RockTunnel_1F_EventScript_Leah, 0
	object_event 4, OBJ_EVENT_GFX_HIKER, 20, 17, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NORMAL, 4, RockTunnel_1F_EventScript_Lucas, 0
	object_event 5, OBJ_EVENT_GFX_HIKER, 5, 20, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 4, RockTunnel_1F_EventScript_Oliver, 0
	object_event 6, OBJ_EVENT_GFX_HIKER, 7, 5, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 4, RockTunnel_1F_EventScript_Lenny, 0
	object_event 7, OBJ_EVENT_GFX_POKE_MANIAC, 27, 10, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NORMAL, 3, RockTunnel_1F_EventScript_Ashton, 0
	object_event 8, OBJ_EVENT_GFX_ITEM_BALL, 37, 5, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, RockTunnel_1F_EventScript_ItemRepel, FLAG_HIDE_ROCK_TUNNEL_1F_REPEL
	object_event 9, OBJ_EVENT_GFX_ITEM_BALL, 33, 22, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, RockTunnel_1F_EventScript_ItemPearl, FLAG_HIDE_ROCK_TUNNEL_1F_PEARL
	object_event 10, OBJ_EVENT_GFX_ITEM_BALL, 22, 22, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, RockTunnel_1F_EventScript_ItemEscapeRope, FLAG_HIDE_ROCK_TUNNEL_1F_ESCAPE_ROPE

RockTunnel_1F_MapWarps:
	warp_def 17, 2, 3, 0, MAP_ROUTE10
	warp_def 45, 2, 3, 0, MAP_ROCK_TUNNEL_B1F
	warp_def 4, 2, 3, 1, MAP_ROCK_TUNNEL_B1F
	warp_def 20, 13, 3, 2, MAP_ROCK_TUNNEL_B1F
	warp_def 45, 21, 3, 3, MAP_ROCK_TUNNEL_B1F
	warp_def 18, 37, 3, 1, MAP_ROUTE10

RockTunnel_1F_MapBGEvents:
	bg_sign_event 14, 33, 3, BG_EVENT_PLAYER_FACING_ANY, RockTunnel_1F_EventScript_RouteSign

RockTunnel_1F_MapEvents::
	map_events RockTunnel_1F_ObjectEvents, RockTunnel_1F_MapWarps, NULL, RockTunnel_1F_MapBGEvents

@ ===== END data/maps/RockTunnel_1F/events.inc =====
@ ===== BEGIN data/maps/RockTunnel_B1F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/RockTunnel_B1F/map.json
@

	.align 2

RockTunnel_B1F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_POKE_MANIAC, 2, 6, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NORMAL, 2, RockTunnel_B1F_EventScript_Cooper, 0
	object_event 2, OBJ_EVENT_GFX_HIKER, 5, 11, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 4, RockTunnel_B1F_EventScript_Dudley, 0
	object_event 3, OBJ_EVENT_GFX_PICNICKER, 11, 15, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 4, RockTunnel_B1F_EventScript_Sofia, 0
	object_event 4, OBJ_EVENT_GFX_HIKER, 36, 11, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 3, RockTunnel_B1F_EventScript_Allen, 0
	object_event 5, OBJ_EVENT_GFX_HIKER, 41, 5, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 3, RockTunnel_B1F_EventScript_Eric, 0
	object_event 6, OBJ_EVENT_GFX_POKE_MANIAC, 23, 23, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 4, RockTunnel_B1F_EventScript_Steve, 0
	object_event 7, OBJ_EVENT_GFX_PICNICKER, 15, 33, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 2, RockTunnel_B1F_EventScript_Martha, 0
	object_event 8, OBJ_EVENT_GFX_POKE_MANIAC, 29, 35, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 3, RockTunnel_B1F_EventScript_Winston, 0
	object_event 9, OBJ_EVENT_GFX_YOUNGSTER, 2, 29, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, RockTunnel_B1F_EventScript_RockSlideTutor, 0
	object_event 10, OBJ_EVENT_GFX_ITEM_BALL, 2, 37, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, RockTunnel_B1F_EventScript_ItemRevive, FLAG_HIDE_ROCK_TUNNEL_B1F_REVIVE
	object_event 11, OBJ_EVENT_GFX_ITEM_BALL, 9, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, RockTunnel_B1F_EventScript_ItemMaxEther, FLAG_HIDE_ROCK_TUNNEL_B1F_MAX_ETHER
	object_event 12, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 1, 20, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_12
	object_event 13, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 1, 22, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_13
	object_event 14, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 4, 23, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_14
	object_event 15, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 2, 23, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_15
	object_event 16, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 39, 26, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_16
	object_event 17, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 42, 26, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_17
	object_event 18, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 43, 28, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_18
	object_event 19, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 45, 30, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_19
	object_event 20, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 45, 33, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_1A
	object_event 21, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 25, 1, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_1B
	object_event 22, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 27, 4, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_1C
	object_event 23, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 23, 2, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_1D
	object_event 24, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 26, 2, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_1E
	object_event 25, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 24, 7, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_1F
	object_event 26, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 27, 6, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_11

RockTunnel_B1F_MapWarps:
	warp_def 38, 28, 3, 1, MAP_ROCK_TUNNEL_1F
	warp_def 33, 3, 3, 2, MAP_ROCK_TUNNEL_1F
	warp_def 27, 12, 3, 3, MAP_ROCK_TUNNEL_1F
	warp_def 2, 3, 3, 4, MAP_ROCK_TUNNEL_1F

RockTunnel_B1F_MapEvents::
	map_events RockTunnel_B1F_ObjectEvents, RockTunnel_B1F_MapWarps, NULL, NULL

@ ===== END data/maps/RockTunnel_B1F/events.inc =====
@ ===== BEGIN data/maps/SeafoamIslands_1F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SeafoamIslands_1F/map.json
@

	.align 2

SeafoamIslands_1F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_PUSHABLE_BOULDER, 22, 12, 3, MOVEMENT_TYPE_FACE_DOWN, 0, 0, FLAG_HIDE_SEAFOAM_B1F_BOULDER_1, 0, EventScript_StrengthBoulder, FLAG_HIDE_SEAFOAM_1F_BOULDER_1
	object_event 2, OBJ_EVENT_GFX_PUSHABLE_BOULDER, 32, 9, 3, MOVEMENT_TYPE_FACE_DOWN, 0, 0, FLAG_HIDE_SEAFOAM_B1F_BOULDER_2, 0, EventScript_StrengthBoulder, FLAG_HIDE_SEAFOAM_1F_BOULDER_2
	object_event 3, OBJ_EVENT_GFX_ITEM_BALL, 11, 8, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SeafoamIslands_1F_EventScript_ItemIceHeal, FLAG_HIDE_SEAFOAM_ISLANDS_1F_ICE_HEAL

SeafoamIslands_1F_MapWarps:
	warp_def 10, 6, 3, 0, MAP_SEAFOAM_ISLANDS_B1F
	warp_def 31, 4, 3, 1, MAP_SEAFOAM_ISLANDS_B1F
	warp_def 28, 19, 3, 2, MAP_SEAFOAM_ISLANDS_B1F
	warp_def 6, 21, 3, 0, MAP_ROUTE20
	warp_def 32, 21, 3, 1, MAP_ROUTE20
	warp_def 21, 8, 3, 9, MAP_SEAFOAM_ISLANDS_B1F
	warp_def 30, 8, 3, 10, MAP_SEAFOAM_ISLANDS_B1F

SeafoamIslands_1F_MapEvents::
	map_events SeafoamIslands_1F_ObjectEvents, SeafoamIslands_1F_MapWarps, NULL, NULL

@ ===== END data/maps/SeafoamIslands_1F/events.inc =====
@ ===== BEGIN data/maps/SeafoamIslands_B1F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SeafoamIslands_B1F/map.json
@

	.align 2

SeafoamIslands_B1F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_PUSHABLE_BOULDER, 22, 8, 3, MOVEMENT_TYPE_FACE_DOWN, 0, 0, FLAG_HIDE_SEAFOAM_B2F_BOULDER_1, 0, EventScript_StrengthBoulder, FLAG_HIDE_SEAFOAM_B1F_BOULDER_1
	object_event 2, OBJ_EVENT_GFX_PUSHABLE_BOULDER, 30, 8, 3, MOVEMENT_TYPE_FACE_DOWN, 0, 0, FLAG_HIDE_SEAFOAM_B2F_BOULDER_2, 0, EventScript_StrengthBoulder, FLAG_HIDE_SEAFOAM_B1F_BOULDER_2
	object_event 3, OBJ_EVENT_GFX_ITEM_BALL, 19, 18, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SeafoamIslands_B1F_EventScript_ItemWaterStone, FLAG_HIDE_SEAFOAM_ISLANDS_B1F_WATER_STONE
	object_event 4, OBJ_EVENT_GFX_ITEM_BALL, 24, 14, 4, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SeafoamIslands_B1F_EventScript_ItemRevive, FLAG_HIDE_SEAFOAM_ISLANDS_B1F_REVIVE

SeafoamIslands_B1F_MapWarps:
	warp_def 10, 6, 4, 0, MAP_SEAFOAM_ISLANDS_1F
	warp_def 31, 4, 3, 1, MAP_SEAFOAM_ISLANDS_1F
	warp_def 28, 19, 3, 2, MAP_SEAFOAM_ISLANDS_1F
	warp_def 7, 3, 3, 3, MAP_SEAFOAM_ISLANDS_B2F
	warp_def 17, 9, 4, 4, MAP_SEAFOAM_ISLANDS_B2F
	warp_def 25, 19, 3, 5, MAP_SEAFOAM_ISLANDS_B2F
	warp_def 32, 14, 3, 6, MAP_SEAFOAM_ISLANDS_B2F
	warp_def 23, 8, 3, 7, MAP_SEAFOAM_ISLANDS_B2F
	warp_def 28, 8, 3, 8, MAP_SEAFOAM_ISLANDS_B2F
	warp_def 21, 8, 3, 5, MAP_SEAFOAM_ISLANDS_1F
	warp_def 29, 8, 3, 6, MAP_SEAFOAM_ISLANDS_1F

SeafoamIslands_B1F_MapEvents::
	map_events SeafoamIslands_B1F_ObjectEvents, SeafoamIslands_B1F_MapWarps, NULL, NULL

@ ===== END data/maps/SeafoamIslands_B1F/events.inc =====
@ ===== BEGIN data/maps/SeafoamIslands_B2F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SeafoamIslands_B2F/map.json
@

	.align 2

SeafoamIslands_B2F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_PUSHABLE_BOULDER, 22, 8, 3, MOVEMENT_TYPE_FACE_DOWN, 0, 0, FLAG_HIDE_SEAFOAM_B3F_BOULDER_1, 0, EventScript_StrengthBoulder, FLAG_HIDE_SEAFOAM_B2F_BOULDER_1
	object_event 2, OBJ_EVENT_GFX_PUSHABLE_BOULDER, 30, 8, 3, MOVEMENT_TYPE_FACE_DOWN, 0, 0, FLAG_HIDE_SEAFOAM_B3F_BOULDER_2, 0, EventScript_StrengthBoulder, FLAG_HIDE_SEAFOAM_B2F_BOULDER_2
	object_event 3, OBJ_EVENT_GFX_ITEM_BALL, 18, 15, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SeafoamIslands_B2F_EventScript_ItemBigPearl, FLAG_HIDE_SEAFOAM_ISLANDS_B2F_BIG_PEARL

SeafoamIslands_B2F_MapWarps:
	warp_def 7, 17, 3, 0, MAP_SEAFOAM_ISLANDS_B3F
	warp_def 32, 4, 3, 1, MAP_SEAFOAM_ISLANDS_B3F
	warp_def 31, 17, 4, 2, MAP_SEAFOAM_ISLANDS_B3F
	warp_def 7, 4, 3, 3, MAP_SEAFOAM_ISLANDS_B1F
	warp_def 17, 9, 4, 4, MAP_SEAFOAM_ISLANDS_B1F
	warp_def 25, 19, 3, 5, MAP_SEAFOAM_ISLANDS_B1F
	warp_def 32, 14, 4, 6, MAP_SEAFOAM_ISLANDS_B1F
	warp_def 22, 7, 3, 7, MAP_SEAFOAM_ISLANDS_B1F
	warp_def 29, 8, 3, 8, MAP_SEAFOAM_ISLANDS_B1F
	warp_def 24, 8, 3, 5, MAP_SEAFOAM_ISLANDS_B3F
	warp_def 27, 8, 3, 6, MAP_SEAFOAM_ISLANDS_B3F

SeafoamIslands_B2F_MapEvents::
	map_events SeafoamIslands_B2F_ObjectEvents, SeafoamIslands_B2F_MapWarps, NULL, NULL

@ ===== END data/maps/SeafoamIslands_B2F/events.inc =====
@ ===== BEGIN data/maps/SeafoamIslands_B3F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SeafoamIslands_B3F/map.json
@

	.align 2

SeafoamIslands_B3F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_PUSHABLE_BOULDER, 23, 8, 1, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, 0x0, FLAG_HIDE_SEAFOAM_B3F_BOULDER_1
	object_event 2, OBJ_EVENT_GFX_PUSHABLE_BOULDER, 24, 8, 1, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, 0x0, FLAG_HIDE_SEAFOAM_B3F_BOULDER_2
	object_event 3, OBJ_EVENT_GFX_PUSHABLE_BOULDER, 12, 16, 3, MOVEMENT_TYPE_FACE_DOWN, 0, 0, FLAG_HIDE_SEAFOAM_B4F_BOULDER_2, 0, EventScript_StrengthBoulder, FLAG_HIDE_SEAFOAM_B3F_BOULDER_5
	object_event 4, OBJ_EVENT_GFX_PUSHABLE_BOULDER, 13, 16, 3, MOVEMENT_TYPE_FACE_DOWN, 0, 0, TRAINER_TYPE_NONE, 0, EventScript_StrengthBoulder, FLAG_HIDE_SEAFOAM_B3F_BOULDER_6
	object_event 5, OBJ_EVENT_GFX_PUSHABLE_BOULDER, 9, 16, 3, MOVEMENT_TYPE_FACE_DOWN, 0, 0, TRAINER_TYPE_NONE, 0, EventScript_StrengthBoulder, FLAG_HIDE_SEAFOAM_B3F_BOULDER_4
	object_event 6, OBJ_EVENT_GFX_PUSHABLE_BOULDER, 6, 17, 3, MOVEMENT_TYPE_FACE_DOWN, 0, 0, FLAG_HIDE_SEAFOAM_B4F_BOULDER_1, 0, EventScript_StrengthBoulder, FLAG_HIDE_SEAFOAM_B3F_BOULDER_3

SeafoamIslands_B3F_MapWarps:
	warp_def 8, 14, 4, 0, MAP_SEAFOAM_ISLANDS_B2F
	warp_def 31, 4, 3, 1, MAP_SEAFOAM_ISLANDS_B2F
	warp_def 31, 16, 4, 2, MAP_SEAFOAM_ISLANDS_B2F
	warp_def 12, 9, 3, 0, MAP_SEAFOAM_ISLANDS_B4F
	warp_def 29, 5, 3, 1, MAP_SEAFOAM_ISLANDS_B4F
	warp_def 23, 9, 1, 7, MAP_SEAFOAM_ISLANDS_B2F
	warp_def 24, 9, 1, 8, MAP_SEAFOAM_ISLANDS_B2F
	warp_def 6, 18, 3, 2, MAP_SEAFOAM_ISLANDS_B4F
	warp_def 9, 18, 3, 3, MAP_SEAFOAM_ISLANDS_B4F

SeafoamIslands_B3F_MapBGEvents:
	bg_hidden_item_event 5, 12, 0, ITEM_NUGGET, FLAG_HIDDEN_ITEM_SEAFOAM_ISLANDS_B3F_NUGGET, 1, FALSE

SeafoamIslands_B3F_MapEvents::
	map_events SeafoamIslands_B3F_ObjectEvents, SeafoamIslands_B3F_MapWarps, NULL, SeafoamIslands_B3F_MapBGEvents

@ ===== END data/maps/SeafoamIslands_B3F/events.inc =====
@ ===== BEGIN data/maps/SeafoamIslands_B4F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SeafoamIslands_B4F/map.json
@

	.align 2

SeafoamIslands_B4F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_PUSHABLE_BOULDER, 8, 18, 1, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, 0x0, FLAG_HIDE_SEAFOAM_B4F_BOULDER_1
	object_event 2, OBJ_EVENT_GFX_PUSHABLE_BOULDER, 9, 18, 1, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, 0x0, FLAG_HIDE_SEAFOAM_B4F_BOULDER_2
	object_event 3, OBJ_EVENT_GFX_ARTICUNO, 9, 2, 4, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SeafoamIslands_B4F_EventScript_Articuno, FLAG_HIDE_ARTICUNO
	object_event 4, OBJ_EVENT_GFX_ITEM_BALL, 22, 19, 4, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SeafoamIslands_B4F_EventScript_ItemUltraBall, FLAG_HIDE_SEAFOAM_ISLANDS_B4F_ULTRA_BALL

SeafoamIslands_B4F_MapWarps:
	warp_def 15, 9, 4, 3, MAP_SEAFOAM_ISLANDS_B3F
	warp_def 32, 5, 4, 4, MAP_SEAFOAM_ISLANDS_B3F
	warp_def 8, 17, 1, 7, MAP_SEAFOAM_ISLANDS_B3F
	warp_def 9, 17, 1, 8, MAP_SEAFOAM_ISLANDS_B3F

SeafoamIslands_B4F_MapCoordEvents:
	coord_event 26, 19, 1, VAR_MAP_SCENE_SEAFOAM_ISLANDS_B4F, 0, SeafoamIslands_B4F_EventScript_UpwardCurrent
	coord_event 27, 19, 1, VAR_MAP_SCENE_SEAFOAM_ISLANDS_B4F, 0, SeafoamIslands_B4F_EventScript_UpwardCurrent
	coord_event 28, 19, 1, VAR_MAP_SCENE_SEAFOAM_ISLANDS_B4F, 0, SeafoamIslands_B4F_EventScript_UpwardCurrent

SeafoamIslands_B4F_MapBGEvents:
	bg_hidden_item_event 13, 8, 0, ITEM_WATER_STONE, FLAG_HIDDEN_ITEM_SEAFOAM_ISLANDS_B4F_WATER_STONE, 1, FALSE
	bg_sign_event 30, 2, 0, BG_EVENT_PLAYER_FACING_ANY, SeafoamIslands_B4F_EventScript_FastCurrentSign
	bg_sign_event 14, 18, 0, BG_EVENT_PLAYER_FACING_ANY, SeafoamIslands_B4F_EventScript_BoulderHintSign

SeafoamIslands_B4F_MapEvents::
	map_events SeafoamIslands_B4F_ObjectEvents, SeafoamIslands_B4F_MapWarps, SeafoamIslands_B4F_MapCoordEvents, SeafoamIslands_B4F_MapBGEvents

@ ===== END data/maps/SeafoamIslands_B4F/events.inc =====
@ ===== BEGIN data/maps/PokemonTower_1F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/PokemonTower_1F/map.json
@

	.align 2

PokemonTower_1F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_WORKER_F, 18, 13, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NONE, 0, PokemonTower_1F_EventScript_WorkerF, 0
	object_event 2, OBJ_EVENT_GFX_CHANNELER, 18, 7, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NONE, 0, PokemonTower_1F_EventScript_Channeler, 0
	object_event 3, OBJ_EVENT_GFX_WOMAN_2, 15, 6, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NONE, 0, PokemonTower_1F_EventScript_Woman1, 0
	object_event 4, OBJ_EVENT_GFX_WOMAN_3, 7, 8, 3, MOVEMENT_TYPE_WANDER_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, PokemonTower_1F_EventScript_Woman2, 0
	object_event 5, OBJ_EVENT_GFX_BALDING_MAN, 8, 12, 3, MOVEMENT_TYPE_WANDER_AROUND, 2, 2, TRAINER_TYPE_NONE, 0, PokemonTower_1F_EventScript_BaldingMan, 0

PokemonTower_1F_MapWarps:
	warp_def 10, 19, 3, 0, MAP_LAVENDER_TOWN
	warp_def 11, 18, 3, 0, MAP_LAVENDER_TOWN
	warp_def 12, 19, 3, 0, MAP_LAVENDER_TOWN
	warp_def 18, 9, 3, 1, MAP_POKEMON_TOWER_2F

PokemonTower_1F_MapEvents::
	map_events PokemonTower_1F_ObjectEvents, PokemonTower_1F_MapWarps, NULL, NULL

@ ===== END data/maps/PokemonTower_1F/events.inc =====
@ ===== BEGIN data/maps/PokemonTower_2F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/PokemonTower_2F/map.json
@

	.align 2

PokemonTower_2F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_BLUE, 16, 5, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NONE, 0, 0x0, FLAG_HIDE_TOWER_RIVAL
	object_event 2, OBJ_EVENT_GFX_CHANNELER, 3, 7, 0, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, PokemonTower_2F_EventScript_Channeler, 0

PokemonTower_2F_MapWarps:
	warp_def 4, 10, 3, 0, MAP_POKEMON_TOWER_3F
	warp_def 18, 10, 3, 3, MAP_POKEMON_TOWER_1F

PokemonTower_2F_MapCoordEvents:
	coord_event 17, 5, 3, VAR_MAP_SCENE_POKEMON_TOWER_2F, 0, PokemonTower_2F_EventScript_RivalTriggerRight
	coord_event 16, 6, 3, VAR_MAP_SCENE_POKEMON_TOWER_2F, 0, PokemonTower_2F_EventScript_RivalTriggerDown

PokemonTower_2F_MapEvents::
	map_events PokemonTower_2F_ObjectEvents, PokemonTower_2F_MapWarps, PokemonTower_2F_MapCoordEvents, NULL

@ ===== END data/maps/PokemonTower_2F/events.inc =====
@ ===== BEGIN data/maps/PokemonTower_3F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/PokemonTower_3F/map.json
@

	.align 2

PokemonTower_3F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_CHANNELER, 10, 14, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 3, PokemonTower_3F_EventScript_Patricia, 0
	object_event 2, OBJ_EVENT_GFX_CHANNELER, 9, 9, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 3, PokemonTower_3F_EventScript_Carly, 0
	object_event 3, OBJ_EVENT_GFX_CHANNELER, 12, 4, 3, MOVEMENT_TYPE_FACE_DOWN_AND_UP, 1, 1, TRAINER_TYPE_NORMAL, 2, PokemonTower_3F_EventScript_Hope, 0
	object_event 4, OBJ_EVENT_GFX_ITEM_BALL, 13, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, PokemonTower_3F_EventScript_ItemEscapeRope, FLAG_HIDE_POKEMON_TOWER_3F_ESCAPE_ROPE

PokemonTower_3F_MapWarps:
	warp_def 4, 10, 3, 0, MAP_POKEMON_TOWER_2F
	warp_def 18, 10, 3, 1, MAP_POKEMON_TOWER_4F

PokemonTower_3F_MapEvents::
	map_events PokemonTower_3F_ObjectEvents, PokemonTower_3F_MapWarps, NULL, NULL

@ ===== END data/maps/PokemonTower_3F/events.inc =====
@ ===== BEGIN data/maps/PokemonTower_4F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/PokemonTower_4F/map.json
@

	.align 2

PokemonTower_4F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_CHANNELER, 17, 7, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 3, PokemonTower_4F_EventScript_Laurel, 0
	object_event 2, OBJ_EVENT_GFX_CHANNELER, 15, 13, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NORMAL, 5, PokemonTower_4F_EventScript_Jody, 0
	object_event 3, OBJ_EVENT_GFX_CHANNELER, 4, 12, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 2, PokemonTower_4F_EventScript_Paula, 0
	object_event 4, OBJ_EVENT_GFX_ITEM_BALL, 12, 11, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, PokemonTower_4F_EventScript_ItemElixir, FLAG_HIDE_POKEMON_TOWER_4F_ELIXIR
	object_event 5, OBJ_EVENT_GFX_ITEM_BALL, 8, 11, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, PokemonTower_4F_EventScript_ItemAwakening, FLAG_HIDE_POKEMON_TOWER_4F_AWAKENING
	object_event 6, OBJ_EVENT_GFX_ITEM_BALL, 11, 16, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, PokemonTower_4F_EventScript_ItemGreatBall, FLAG_HIDE_POKEMON_TOWER_4F_GREAT_BALL

PokemonTower_4F_MapWarps:
	warp_def 4, 10, 3, 0, MAP_POKEMON_TOWER_5F
	warp_def 18, 10, 3, 1, MAP_POKEMON_TOWER_3F

PokemonTower_4F_MapEvents::
	map_events PokemonTower_4F_ObjectEvents, PokemonTower_4F_MapWarps, NULL, NULL

@ ===== END data/maps/PokemonTower_4F/events.inc =====
@ ===== BEGIN data/maps/PokemonTower_5F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/PokemonTower_5F/map.json
@

	.align 2

PokemonTower_5F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_CHANNELER, 11, 4, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NORMAL, 2, PokemonTower_5F_EventScript_Ruth, 0
	object_event 2, OBJ_EVENT_GFX_CHANNELER, 19, 7, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NORMAL, 3, PokemonTower_5F_EventScript_Tammy, 0
	object_event 3, OBJ_EVENT_GFX_CHANNELER, 7, 12, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 2, PokemonTower_5F_EventScript_Karina, 0
	object_event 4, OBJ_EVENT_GFX_CHANNELER, 11, 16, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NORMAL, 2, PokemonTower_5F_EventScript_Janae, 0
	object_event 5, OBJ_EVENT_GFX_CHANNELER, 12, 8, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, PokemonTower_5F_EventScript_Channeler, 0
	object_event 6, OBJ_EVENT_GFX_ITEM_BALL, 6, 16, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, PokemonTower_5F_EventScript_ItemNugget, FLAG_HIDE_POKEMON_TOWER_5F_NUGGET
	object_event 7, OBJ_EVENT_GFX_ITEM_BALL, 11, 9, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, PokemonTower_5F_EventScript_ItemCleanseTag, FLAG_HIDE_POKEMON_TOWER_5F_CLEANSE_TAG

PokemonTower_5F_MapWarps:
	warp_def 4, 10, 3, 0, MAP_POKEMON_TOWER_4F
	warp_def 18, 10, 3, 1, MAP_POKEMON_TOWER_6F

PokemonTower_5F_MapCoordEvents:
	coord_event 10, 8, 3, VAR_TEMP_1, 0, PokemonTower_5F_EventScript_PurifiedZone
	coord_event 11, 8, 3, VAR_TEMP_1, 0, PokemonTower_5F_EventScript_PurifiedZone
	coord_event 12, 8, 3, VAR_TEMP_1, 0, PokemonTower_5F_EventScript_PurifiedZone
	coord_event 10, 9, 3, VAR_TEMP_1, 0, PokemonTower_5F_EventScript_PurifiedZone
	coord_event 9, 8, 3, VAR_TEMP_1, 1, PokemonTower_5F_EventScript_ExitPurifiedZone
	coord_event 12, 9, 3, VAR_TEMP_1, 0, PokemonTower_5F_EventScript_PurifiedZone
	coord_event 10, 10, 3, VAR_TEMP_1, 0, PokemonTower_5F_EventScript_PurifiedZone
	coord_event 11, 10, 3, VAR_TEMP_1, 0, PokemonTower_5F_EventScript_PurifiedZone
	coord_event 12, 10, 0, VAR_TEMP_1, 0, PokemonTower_5F_EventScript_PurifiedZone
	coord_event 9, 9, 3, VAR_TEMP_1, 1, PokemonTower_5F_EventScript_ExitPurifiedZone
	coord_event 9, 10, 3, VAR_TEMP_1, 1, PokemonTower_5F_EventScript_ExitPurifiedZone
	coord_event 10, 11, 3, VAR_TEMP_1, 1, PokemonTower_5F_EventScript_ExitPurifiedZone
	coord_event 11, 11, 3, VAR_TEMP_1, 1, PokemonTower_5F_EventScript_ExitPurifiedZone
	coord_event 12, 11, 0, VAR_TEMP_1, 1, PokemonTower_5F_EventScript_ExitPurifiedZone
	coord_event 13, 8, 0, VAR_TEMP_1, 1, PokemonTower_5F_EventScript_ExitPurifiedZone
	coord_event 13, 9, 0, VAR_TEMP_1, 1, PokemonTower_5F_EventScript_ExitPurifiedZone
	coord_event 13, 10, 0, VAR_TEMP_1, 1, PokemonTower_5F_EventScript_ExitPurifiedZone

PokemonTower_5F_MapBGEvents:
	bg_hidden_item_event 7, 3, 3, ITEM_BIG_MUSHROOM, FLAG_HIDDEN_ITEM_POKEMON_TOWER_5F_BIG_MUSHROOM, 1, FALSE

PokemonTower_5F_MapEvents::
	map_events PokemonTower_5F_ObjectEvents, PokemonTower_5F_MapWarps, PokemonTower_5F_MapCoordEvents, PokemonTower_5F_MapBGEvents

@ ===== END data/maps/PokemonTower_5F/events.inc =====
@ ===== BEGIN data/maps/PokemonTower_6F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/PokemonTower_6F/map.json
@

	.align 2

PokemonTower_6F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_CHANNELER, 13, 10, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 3, PokemonTower_6F_EventScript_Angelica, 0
	object_event 2, OBJ_EVENT_GFX_CHANNELER, 18, 6, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NORMAL, 3, PokemonTower_6F_EventScript_Jennifer, 0
	object_event 3, OBJ_EVENT_GFX_CHANNELER, 9, 6, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 3, PokemonTower_6F_EventScript_Emilia, 0
	object_event 4, OBJ_EVENT_GFX_ITEM_BALL, 5, 15, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, PokemonTower_6F_EventScript_ItemRareCandy, FLAG_HIDE_POKEMON_TOWER_6F_RARE_CANDY
	object_event 5, OBJ_EVENT_GFX_ITEM_BALL, 15, 15, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, PokemonTower_6F_EventScript_ItemXAccuracy, FLAG_HIDE_POKEMON_TOWER_6F_X_ACCURACY

PokemonTower_6F_MapWarps:
	warp_def 11, 16, 3, 0, MAP_POKEMON_TOWER_7F
	warp_def 18, 10, 3, 1, MAP_POKEMON_TOWER_5F

PokemonTower_6F_MapCoordEvents:
	coord_event 11, 15, 3, VAR_MAP_SCENE_POKEMON_TOWER_6F, 0, PokemonTower_6F_EventScript_MarowakGhost
	coord_event 12, 16, 3, VAR_MAP_SCENE_POKEMON_TOWER_6F, 0, PokemonTower_6F_EventScript_MarowakGhost

PokemonTower_6F_MapEvents::
	map_events PokemonTower_6F_ObjectEvents, PokemonTower_6F_MapWarps, PokemonTower_6F_MapCoordEvents, NULL

@ ===== END data/maps/PokemonTower_6F/events.inc =====
@ ===== BEGIN data/maps/PokemonTower_7F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/PokemonTower_7F/map.json
@

	.align 2

PokemonTower_7F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_MR_FUJI, 11, 4, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, PokemonTower_7F_EventScript_MrFuji, FLAG_HIDE_TOWER_FUJI
	object_event 2, OBJ_EVENT_GFX_ROCKET_M, 9, 10, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 4, PokemonTower_7F_EventScript_Grunt1, FLAG_HIDE_TOWER_ROCKET_1
	object_event 3, OBJ_EVENT_GFX_ROCKET_M, 13, 8, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NORMAL, 4, PokemonTower_7F_EventScript_Grunt2, FLAG_HIDE_TOWER_ROCKET_2
	object_event 4, OBJ_EVENT_GFX_ROCKET_M, 9, 6, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 4, PokemonTower_7F_EventScript_Grunt3, FLAG_HIDE_TOWER_ROCKET_3

PokemonTower_7F_MapWarps:
	warp_def 11, 16, 3, 0, MAP_POKEMON_TOWER_6F

PokemonTower_7F_MapBGEvents:
	bg_hidden_item_event 11, 4, 3, ITEM_SOOTHE_BELL, FLAG_HIDDEN_ITEM_POKEMON_TOWER_7F_SOOTHE_BELL, 1, TRUE

PokemonTower_7F_MapEvents::
	map_events PokemonTower_7F_ObjectEvents, PokemonTower_7F_MapWarps, NULL, PokemonTower_7F_MapBGEvents

@ ===== END data/maps/PokemonTower_7F/events.inc =====
@ ===== BEGIN data/maps/PowerPlant/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/PowerPlant/map.json
@

	.align 2

PowerPlant_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_ITEM_BALL, 7, 27, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, PowerPlant_EventScript_ItemMaxPotion, FLAG_HIDE_POWER_PLANT_MAX_POTION
	object_event 2, OBJ_EVENT_GFX_ITEM_BALL, 40, 22, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, PowerPlant_EventScript_ItemTM17, FLAG_HIDE_POWER_PLANT_TM17
	object_event 3, OBJ_EVENT_GFX_ITEM_BALL, 46, 37, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, PowerPlant_EventScript_ItemTM25, FLAG_HIDE_POWER_PLANT_TM25
	object_event 4, OBJ_EVENT_GFX_ITEM_BALL, 45, 4, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, PowerPlant_EventScript_ItemThunderStone, FLAG_HIDE_POWER_PLANT_THUNDER_STONE
	object_event 5, OBJ_EVENT_GFX_ITEM_BALL, 26, 22, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, PowerPlant_EventScript_ItemElixir, FLAG_HIDE_POWER_PLANT_ELIXIR
	object_event 6, OBJ_EVENT_GFX_ZAPDOS, 5, 11, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, PowerPlant_EventScript_Zapdos, FLAG_HIDE_ZAPDOS
	object_event 7, OBJ_EVENT_GFX_ITEM_BALL, 36, 5, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, PowerPlant_EventScript_Electrode2, FLAG_HIDE_POWER_PLANT_ELECTRODE_2
	object_event 8, OBJ_EVENT_GFX_ITEM_BALL, 30, 38, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, PowerPlant_EventScript_Electrode1, FLAG_HIDE_POWER_PLANT_ELECTRODE_1

PowerPlant_MapWarps:
	warp_def 4, 39, 3, 2, MAP_ROUTE10
	warp_def 5, 38, 3, 2, MAP_ROUTE10
	warp_def 6, 39, 3, 2, MAP_ROUTE10
	warp_def 1, 11, 3, 4, MAP_ROUTE10
	warp_def 0, 13, 3, 2, MAP_ROUTE10

PowerPlant_MapBGEvents:
	bg_hidden_item_event 29, 16, 3, ITEM_MAX_ELIXIR, FLAG_HIDDEN_ITEM_POWER_PLANT_MAX_ELIXIR, 1, FALSE
	bg_hidden_item_event 8, 12, 3, ITEM_THUNDER_STONE, FLAG_HIDDEN_ITEM_POWER_PLANT_THUNDER_STONE, 1, FALSE

PowerPlant_MapEvents::
	map_events PowerPlant_ObjectEvents, PowerPlant_MapWarps, NULL, PowerPlant_MapBGEvents

@ ===== END data/maps/PowerPlant/events.inc =====
@ ===== BEGIN data/maps/MtEmber_RubyPath_B4F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/MtEmber_RubyPath_B4F/map.json
@

	.align 2

MtEmber_RubyPath_B4F_MapWarps:
	warp_def 14, 14, 3, 0, MAP_MT_EMBER_RUBY_PATH_B5F
	warp_def 4, 2, 3, 2, MAP_MT_EMBER_RUBY_PATH_B3F

MtEmber_RubyPath_B4F_MapBGEvents:
	bg_sign_event 3, 7, 0, BG_EVENT_PLAYER_FACING_NORTH, MtEmber_RubyPath_B4F_EventScript_BrailleABC
	bg_sign_event 4, 7, 0, BG_EVENT_PLAYER_FACING_NORTH, MtEmber_RubyPath_B4F_EventScript_BrailleABC
	bg_sign_event 5, 7, 0, BG_EVENT_PLAYER_FACING_NORTH, MtEmber_RubyPath_B4F_EventScript_BrailleABC
	bg_sign_event 4, 9, 0, BG_EVENT_PLAYER_FACING_NORTH, MtEmber_RubyPath_B4F_EventScript_BrailleGHI
	bg_sign_event 3, 9, 0, BG_EVENT_PLAYER_FACING_NORTH, MtEmber_RubyPath_B4F_EventScript_BrailleGHI
	bg_sign_event 5, 9, 0, BG_EVENT_PLAYER_FACING_NORTH, MtEmber_RubyPath_B4F_EventScript_BrailleGHI
	bg_sign_event 3, 11, 0, BG_EVENT_PLAYER_FACING_NORTH, MtEmber_RubyPath_B4F_EventScript_BrailleMNO
	bg_sign_event 4, 11, 0, BG_EVENT_PLAYER_FACING_NORTH, MtEmber_RubyPath_B4F_EventScript_BrailleMNO
	bg_sign_event 5, 11, 0, BG_EVENT_PLAYER_FACING_NORTH, MtEmber_RubyPath_B4F_EventScript_BrailleMNO
	bg_sign_event 3, 13, 0, BG_EVENT_PLAYER_FACING_NORTH, MtEmber_RubyPath_B4F_EventScript_BrailleTUV
	bg_sign_event 4, 13, 0, BG_EVENT_PLAYER_FACING_NORTH, MtEmber_RubyPath_B4F_EventScript_BrailleTUV
	bg_sign_event 5, 13, 0, BG_EVENT_PLAYER_FACING_NORTH, MtEmber_RubyPath_B4F_EventScript_BrailleTUV
	bg_sign_event 7, 7, 0, BG_EVENT_PLAYER_FACING_NORTH, MtEmber_RubyPath_B4F_EventScript_BrailleDEF
	bg_sign_event 8, 7, 0, BG_EVENT_PLAYER_FACING_NORTH, MtEmber_RubyPath_B4F_EventScript_BrailleDEF
	bg_sign_event 9, 7, 0, BG_EVENT_PLAYER_FACING_NORTH, MtEmber_RubyPath_B4F_EventScript_BrailleDEF
	bg_sign_event 7, 9, 0, BG_EVENT_PLAYER_FACING_NORTH, MtEmber_RubyPath_B4F_EventScript_BrailleJKL
	bg_sign_event 8, 9, 0, BG_EVENT_PLAYER_FACING_NORTH, MtEmber_RubyPath_B4F_EventScript_BrailleJKL
	bg_sign_event 9, 9, 0, BG_EVENT_PLAYER_FACING_NORTH, MtEmber_RubyPath_B4F_EventScript_BrailleJKL
	bg_sign_event 7, 11, 0, BG_EVENT_PLAYER_FACING_NORTH, MtEmber_RubyPath_B4F_EventScript_BraillePQRS
	bg_sign_event 11, 7, 0, BG_EVENT_PLAYER_FACING_NORTH, MtEmber_RubyPath_B4F_EventScript_BraillePeriod
	bg_sign_event 11, 9, 0, BG_EVENT_PLAYER_FACING_NORTH, MtEmber_RubyPath_B4F_EventScript_BrailleComma
	bg_sign_event 8, 11, 0, BG_EVENT_PLAYER_FACING_NORTH, MtEmber_RubyPath_B4F_EventScript_BraillePQRS
	bg_sign_event 9, 11, 0, BG_EVENT_PLAYER_FACING_NORTH, MtEmber_RubyPath_B4F_EventScript_BraillePQRS
	bg_sign_event 7, 13, 0, BG_EVENT_PLAYER_FACING_NORTH, MtEmber_RubyPath_B4F_EventScript_BrailleWXYZ
	bg_sign_event 9, 13, 0, BG_EVENT_PLAYER_FACING_NORTH, MtEmber_RubyPath_B4F_EventScript_BrailleWXYZ
	bg_sign_event 8, 13, 0, BG_EVENT_PLAYER_FACING_NORTH, MtEmber_RubyPath_B4F_EventScript_BrailleWXYZ

MtEmber_RubyPath_B4F_MapEvents::
	map_events NULL, MtEmber_RubyPath_B4F_MapWarps, NULL, MtEmber_RubyPath_B4F_MapBGEvents

@ ===== END data/maps/MtEmber_RubyPath_B4F/events.inc =====
@ ===== BEGIN data/maps/MtEmber_Exterior/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/MtEmber_Exterior/map.json
@

	.align 2

MtEmber_Exterior_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_HIKER, 29, 45, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NONE, 0, MtEmber_Exterior_EventScript_ExplosionTutor, 0
	object_event 2, OBJ_EVENT_GFX_ROCKET_M, 41, 40, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, MtEmber_Exterior_EventScript_Grunt1, FLAG_HIDE_MT_EMBER_EXTERIOR_ROCKETS
	object_event 3, OBJ_EVENT_GFX_ROCKET_M, 42, 40, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NONE, 0, MtEmber_Exterior_EventScript_Grunt2, FLAG_HIDE_MT_EMBER_EXTERIOR_ROCKETS
	object_event 4, OBJ_EVENT_GFX_CRUSH_GIRL, 22, 35, 3, MOVEMENT_TYPE_WALK_SEQUENCE_DOWN_RIGHT_UP_LEFT, 5, 3, TRAINER_TYPE_NORMAL, 1, MtEmber_Exterior_EventScript_Jocelyn, 0
	object_event 5, OBJ_EVENT_GFX_CAMPER, 15, 28, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 5, MtEmber_Exterior_EventScript_Logan, 0
	object_event 6, OBJ_EVENT_GFX_PICNICKER, 14, 42, 3, MOVEMENT_TYPE_FACE_DOWN_AND_LEFT, 1, 1, TRAINER_TYPE_NORMAL, 3, MtEmber_Exterior_EventScript_Beth, 0
	object_event 7, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 29, 41, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_12
	object_event 8, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 30, 42, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_13
	object_event 9, OBJ_EVENT_GFX_PUSHABLE_BOULDER, 22, 45, 3, MOVEMENT_TYPE_LOOK_AROUND, 0, 0, TRAINER_TYPE_NONE, 0, EventScript_StrengthBoulder, 0
	object_event 10, OBJ_EVENT_GFX_PUSHABLE_BOULDER, 17, 46, 3, MOVEMENT_TYPE_LOOK_AROUND, 0, 0, TRAINER_TYPE_NONE, 0, EventScript_StrengthBoulder, 0
	object_event 11, OBJ_EVENT_GFX_PUSHABLE_BOULDER, 36, 14, 3, MOVEMENT_TYPE_LOOK_AROUND, 0, 0, TRAINER_TYPE_NONE, 0, EventScript_StrengthBoulder, 0
	object_event 12, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 34, 14, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_14
	object_event 13, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 36, 15, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_15
	object_event 14, OBJ_EVENT_GFX_PUSHABLE_BOULDER, 35, 14, 3, MOVEMENT_TYPE_LOOK_AROUND, 0, 0, TRAINER_TYPE_NONE, 0, EventScript_StrengthBoulder, 0
	object_event 15, OBJ_EVENT_GFX_PUSHABLE_BOULDER, 35, 17, 3, MOVEMENT_TYPE_LOOK_AROUND, 0, 0, TRAINER_TYPE_NONE, 0, EventScript_StrengthBoulder, 0
	object_event 16, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 18, 39, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_16
	object_event 17, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 19, 40, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_17
	object_event 18, OBJ_EVENT_GFX_ITEM_BALL, 13, 6, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, MtEmber_Exterior_EventScript_ItemUltraBall, FLAG_HIDE_MT_EMBER_EXTERIOR_ULTRA_BALL
	object_event 19, OBJ_EVENT_GFX_ITEM_BALL, 38, 10, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, MtEmber_Exterior_EventScript_ItemFireStone, FLAG_HIDE_MT_EMBER_EXTERIOR_FIRE_STONE
	object_event 20, OBJ_EVENT_GFX_ITEM_BALL, 48, 20, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, MtEmber_Exterior_EventScript_ItemDireHit, FLAG_HIDE_MT_EMBER_EXTERIOR_DIRE_HIT

MtEmber_Exterior_MapWarps:
	warp_def 28, 48, 3, 0, MAP_ONE_ISLAND_KINDLE_ROAD
	warp_def 29, 48, 3, 1, MAP_ONE_ISLAND_KINDLE_ROAD
	warp_def 14, 24, 3, 0, MAP_MT_EMBER_SUMMIT_PATH_1F
	warp_def 39, 19, 3, 1, MAP_MT_EMBER_SUMMIT_PATH_3F
	warp_def 29, 7, 3, 0, MAP_MT_EMBER_SUMMIT
	warp_def 42, 39, 0, 0, MAP_MT_EMBER_RUBY_PATH_1F

MtEmber_Exterior_MapCoordEvents:
	coord_event 37, 43, 0, VAR_MAP_SCENE_MT_EMBER_EXTERIOR, 1, MtEmber_Exterior_EventScript_RocketPasswordScene
	coord_event 38, 43, 0, VAR_MAP_SCENE_MT_EMBER_EXTERIOR, 1, MtEmber_Exterior_EventScript_RocketPasswordScene
	coord_event 39, 43, 0, VAR_MAP_SCENE_MT_EMBER_EXTERIOR, 1, MtEmber_Exterior_EventScript_RocketPasswordScene

MtEmber_Exterior_MapBGEvents:
	bg_hidden_item_event 18, 17, 0, ITEM_FIRE_STONE, FLAG_HIDDEN_ITEM_MT_EMBER_EXTERIOR_FIRE_STONE, 1, FALSE
	bg_hidden_item_event 8, 30, 3, ITEM_ULTRA_BALL, FLAG_HIDDEN_ITEM_MT_EMBER_EXTERIOR_ULTRA_BALL, 1, FALSE

MtEmber_Exterior_MapEvents::
	map_events MtEmber_Exterior_ObjectEvents, MtEmber_Exterior_MapWarps, MtEmber_Exterior_MapCoordEvents, MtEmber_Exterior_MapBGEvents

@ ===== END data/maps/MtEmber_Exterior/events.inc =====
@ ===== BEGIN data/maps/MtEmber_SummitPath_1F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/MtEmber_SummitPath_1F/map.json
@

	.align 2

MtEmber_SummitPath_1F_MapWarps:
	warp_def 2, 15, 0, 2, MAP_MT_EMBER_EXTERIOR
	warp_def 11, 1, 0, 0, MAP_MT_EMBER_SUMMIT_PATH_2F

MtEmber_SummitPath_1F_MapEvents::
	map_events NULL, MtEmber_SummitPath_1F_MapWarps, NULL, NULL

@ ===== END data/maps/MtEmber_SummitPath_1F/events.inc =====
@ ===== BEGIN data/maps/MtEmber_SummitPath_2F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/MtEmber_SummitPath_2F/map.json
@

	.align 2

MtEmber_SummitPath_2F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 40, 7, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_12
	object_event 2, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 33, 5, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_13
	object_event 3, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 15, 19, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_14
	object_event 4, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 13, 23, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_15
	object_event 5, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 13, 21, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_16
	object_event 6, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 7, 38, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_17
	object_event 7, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 9, 35, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_18
	object_event 8, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 7, 34, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_19
	object_event 9, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 15, 26, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_1A

MtEmber_SummitPath_2F_MapWarps:
	warp_def 8, 39, 0, 1, MAP_MT_EMBER_SUMMIT_PATH_1F
	warp_def 39, 6, 3, 0, MAP_MT_EMBER_SUMMIT_PATH_3F

MtEmber_SummitPath_2F_MapEvents::
	map_events MtEmber_SummitPath_2F_ObjectEvents, MtEmber_SummitPath_2F_MapWarps, NULL, NULL

@ ===== END data/maps/MtEmber_SummitPath_2F/events.inc =====
@ ===== BEGIN data/maps/MtEmber_SummitPath_3F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/MtEmber_SummitPath_3F/map.json
@

	.align 2

MtEmber_SummitPath_3F_MapWarps:
	warp_def 2, 4, 0, 1, MAP_MT_EMBER_SUMMIT_PATH_2F
	warp_def 11, 8, 0, 3, MAP_MT_EMBER_EXTERIOR

MtEmber_SummitPath_3F_MapEvents::
	map_events NULL, MtEmber_SummitPath_3F_MapWarps, NULL, NULL

@ ===== END data/maps/MtEmber_SummitPath_3F/events.inc =====
@ ===== BEGIN data/maps/MtEmber_Summit/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/MtEmber_Summit/map.json
@

	.align 2

MtEmber_Summit_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_MOLTRES, 9, 6, 3, MOVEMENT_TYPE_FACE_DOWN, 0, 0, TRAINER_TYPE_NONE, 0, MtEmber_Summit_EventScript_Moltres, FLAG_HIDE_MOLTRES
	object_event 2, OBJ_EVENT_GFX_PUSHABLE_BOULDER, 10, 12, 3, MOVEMENT_TYPE_LOOK_AROUND, 0, 0, TRAINER_TYPE_NONE, 0, EventScript_StrengthBoulder, 0
	object_event 3, OBJ_EVENT_GFX_PUSHABLE_BOULDER, 9, 12, 3, MOVEMENT_TYPE_LOOK_AROUND, 0, 0, TRAINER_TYPE_NONE, 0, EventScript_StrengthBoulder, 0
	object_event 4, OBJ_EVENT_GFX_PUSHABLE_BOULDER, 8, 11, 3, MOVEMENT_TYPE_LOOK_AROUND, 0, 0, TRAINER_TYPE_NONE, 0, EventScript_StrengthBoulder, 0
	object_event 5, OBJ_EVENT_GFX_PUSHABLE_BOULDER, 8, 10, 3, MOVEMENT_TYPE_LOOK_AROUND, 0, 0, TRAINER_TYPE_NONE, 0, EventScript_StrengthBoulder, 0

MtEmber_Summit_MapWarps:
	warp_def 9, 15, 0, 4, MAP_MT_EMBER_EXTERIOR

MtEmber_Summit_MapEvents::
	map_events MtEmber_Summit_ObjectEvents, MtEmber_Summit_MapWarps, NULL, NULL

@ ===== END data/maps/MtEmber_Summit/events.inc =====
@ ===== BEGIN data/maps/MtEmber_RubyPath_B5F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/MtEmber_RubyPath_B5F/map.json
@

	.align 2

MtEmber_RubyPath_B5F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_RUBY, 7, 7, 0, MOVEMENT_TYPE_FACE_DOWN, 0, 0, TRAINER_TYPE_NONE, 0, MtEmber_RubyPath_B5F_EventScript_Ruby, FLAG_HIDE_RUBY

MtEmber_RubyPath_B5F_MapWarps:
	warp_def 11, 7, 3, 0, MAP_MT_EMBER_RUBY_PATH_B4F

MtEmber_RubyPath_B5F_MapBGEvents:
	bg_sign_event 7, 2, 0, BG_EVENT_PLAYER_FACING_NORTH, MtEmber_RubyPath_B5F_EventScript_BrailleMessage

MtEmber_RubyPath_B5F_MapEvents::
	map_events MtEmber_RubyPath_B5F_ObjectEvents, MtEmber_RubyPath_B5F_MapWarps, NULL, MtEmber_RubyPath_B5F_MapBGEvents

@ ===== END data/maps/MtEmber_RubyPath_B5F/events.inc =====
@ ===== BEGIN data/maps/MtEmber_RubyPath_1F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/MtEmber_RubyPath_1F/map.json
@

	.align 2

MtEmber_RubyPath_1F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 18, 11, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_12
	object_event 2, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 23, 16, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_13
	object_event 3, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 20, 12, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_14
	object_event 4, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 19, 7, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_15
	object_event 5, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 21, 15, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_16

MtEmber_RubyPath_1F_MapWarps:
	warp_def 22, 17, 3, 5, MAP_MT_EMBER_EXTERIOR
	warp_def 1, 1, 0, 0, MAP_MT_EMBER_RUBY_PATH_B1F
	warp_def 24, 5, 0, 1, MAP_MT_EMBER_RUBY_PATH_B2F_STAIRS

MtEmber_RubyPath_1F_MapEvents::
	map_events MtEmber_RubyPath_1F_ObjectEvents, MtEmber_RubyPath_1F_MapWarps, NULL, NULL

@ ===== END data/maps/MtEmber_RubyPath_1F/events.inc =====
@ ===== BEGIN data/maps/MtEmber_RubyPath_B1F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/MtEmber_RubyPath_B1F/map.json
@

	.align 2

MtEmber_RubyPath_B1F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 1, 8, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_12
	object_event 2, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 1, 11, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_13
	object_event 3, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 3, 12, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_14
	object_event 4, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 5, 14, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_15

MtEmber_RubyPath_B1F_MapWarps:
	warp_def 9, 21, 0, 1, MAP_MT_EMBER_RUBY_PATH_1F
	warp_def 6, 1, 0, 0, MAP_MT_EMBER_RUBY_PATH_B2F

MtEmber_RubyPath_B1F_MapEvents::
	map_events MtEmber_RubyPath_B1F_ObjectEvents, MtEmber_RubyPath_B1F_MapWarps, NULL, NULL

@ ===== END data/maps/MtEmber_RubyPath_B1F/events.inc =====
@ ===== BEGIN data/maps/MtEmber_RubyPath_B2F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/MtEmber_RubyPath_B2F/map.json
@

	.align 2

MtEmber_RubyPath_B2F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_PUSHABLE_BOULDER, 9, 3, 3, MOVEMENT_TYPE_LOOK_AROUND, 0, 0, TRAINER_TYPE_NONE, 0, EventScript_StrengthBoulder, 0
	object_event 2, OBJ_EVENT_GFX_PUSHABLE_BOULDER, 12, 5, 3, MOVEMENT_TYPE_LOOK_AROUND, 0, 0, TRAINER_TYPE_NONE, 0, EventScript_StrengthBoulder, 0
	object_event 3, OBJ_EVENT_GFX_PUSHABLE_BOULDER, 12, 2, 3, MOVEMENT_TYPE_LOOK_AROUND, 0, 0, TRAINER_TYPE_NONE, 0, EventScript_StrengthBoulder, 0
	object_event 4, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 4, 8, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_12
	object_event 5, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 1, 8, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_13
	object_event 6, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 4, 5, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_14
	object_event 7, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 5, 5, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_15

MtEmber_RubyPath_B2F_MapWarps:
	warp_def 1, 7, 3, 1, MAP_MT_EMBER_RUBY_PATH_B1F
	warp_def 13, 9, 3, 0, MAP_MT_EMBER_RUBY_PATH_B3F

MtEmber_RubyPath_B2F_MapEvents::
	map_events MtEmber_RubyPath_B2F_ObjectEvents, MtEmber_RubyPath_B2F_MapWarps, NULL, NULL

@ ===== END data/maps/MtEmber_RubyPath_B2F/events.inc =====
@ ===== BEGIN data/maps/MtEmber_RubyPath_B3F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/MtEmber_RubyPath_B3F/map.json
@

	.align 2

MtEmber_RubyPath_B3F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_PUSHABLE_BOULDER, 10, 4, 3, MOVEMENT_TYPE_LOOK_AROUND, 0, 0, TRAINER_TYPE_NONE, 0, EventScript_StrengthBoulder, 0
	object_event 2, OBJ_EVENT_GFX_PUSHABLE_BOULDER, 26, 12, 3, MOVEMENT_TYPE_LOOK_AROUND, 0, 0, TRAINER_TYPE_NONE, 0, EventScript_StrengthBoulder, 0
	object_event 3, OBJ_EVENT_GFX_PUSHABLE_BOULDER, 28, 8, 3, MOVEMENT_TYPE_LOOK_AROUND, 0, 0, TRAINER_TYPE_NONE, 0, EventScript_StrengthBoulder, 0
	object_event 4, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 7, 2, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_12
	object_event 5, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 4, 3, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_13
	object_event 6, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 6, 6, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_14
	object_event 7, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 7, 6, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_15
	object_event 8, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 4, 5, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_16
	object_event 9, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 5, 2, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_17
	object_event 10, OBJ_EVENT_GFX_PUSHABLE_BOULDER, 15, 13, 3, MOVEMENT_TYPE_LOOK_AROUND, 0, 0, TRAINER_TYPE_NONE, 0, EventScript_StrengthBoulder, 0

MtEmber_RubyPath_B3F_MapWarps:
	warp_def 1, 4, 0, 1, MAP_MT_EMBER_RUBY_PATH_B2F
	warp_def 19, 19, 3, 0, MAP_MT_EMBER_RUBY_PATH_B1F_STAIRS
	warp_def 5, 19, 3, 1, MAP_MT_EMBER_RUBY_PATH_B4F

MtEmber_RubyPath_B3F_MapEvents::
	map_events MtEmber_RubyPath_B3F_ObjectEvents, MtEmber_RubyPath_B3F_MapWarps, NULL, NULL

@ ===== END data/maps/MtEmber_RubyPath_B3F/events.inc =====
@ ===== BEGIN data/maps/MtEmber_RubyPath_B1F_Stairs/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/MtEmber_RubyPath_B1F_Stairs/map.json
@

	.align 2

MtEmber_RubyPath_B1F_Stairs_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 4, 2, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_12

MtEmber_RubyPath_B1F_Stairs_MapWarps:
	warp_def 4, 1, 0, 1, MAP_MT_EMBER_RUBY_PATH_B3F
	warp_def 1, 5, 0, 0, MAP_MT_EMBER_RUBY_PATH_B2F_STAIRS

MtEmber_RubyPath_B1F_Stairs_MapEvents::
	map_events MtEmber_RubyPath_B1F_Stairs_ObjectEvents, MtEmber_RubyPath_B1F_Stairs_MapWarps, NULL, NULL

@ ===== END data/maps/MtEmber_RubyPath_B1F_Stairs/events.inc =====
@ ===== BEGIN data/maps/MtEmber_RubyPath_B2F_Stairs/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/MtEmber_RubyPath_B2F_Stairs/map.json
@

	.align 2

MtEmber_RubyPath_B2F_Stairs_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 4, 3, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_12
	object_event 2, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 6, 2, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_13

MtEmber_RubyPath_B2F_Stairs_MapWarps:
	warp_def 6, 1, 0, 1, MAP_MT_EMBER_RUBY_PATH_B1F_STAIRS
	warp_def 1, 4, 0, 2, MAP_MT_EMBER_RUBY_PATH_1F

MtEmber_RubyPath_B2F_Stairs_MapEvents::
	map_events MtEmber_RubyPath_B2F_Stairs_ObjectEvents, MtEmber_RubyPath_B2F_Stairs_MapWarps, NULL, NULL

@ ===== END data/maps/MtEmber_RubyPath_B2F_Stairs/events.inc =====
@ ===== BEGIN data/maps/ThreeIsland_BerryForest/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/ThreeIsland_BerryForest/map.json
@

	.align 2

ThreeIsland_BerryForest_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_LITTLE_GIRL, 4, 8, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, ThreeIsland_BerryForest_EventScript_Lostelle, FLAG_HIDE_LOSTELLE_IN_BERRY_FOREST
	object_event 2, OBJ_EVENT_GFX_CUT_TREE, 12, 11, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_CutTree, FLAG_TEMP_12
	object_event 3, OBJ_EVENT_GFX_CUT_TREE, 19, 7, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_CutTree, FLAG_TEMP_13
	object_event 4, OBJ_EVENT_GFX_CUT_TREE, 23, 17, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_CutTree, FLAG_TEMP_14
	object_event 5, OBJ_EVENT_GFX_CUT_TREE, 38, 23, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_CutTree, FLAG_TEMP_15
	object_event 6, OBJ_EVENT_GFX_CUT_TREE, 44, 23, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_CutTree, FLAG_TEMP_16
	object_event 7, OBJ_EVENT_GFX_CUT_TREE, 44, 29, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_CutTree, FLAG_TEMP_17
	object_event 8, OBJ_EVENT_GFX_CUT_TREE, 16, 43, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_CutTree, FLAG_TEMP_18
	object_event 9, OBJ_EVENT_GFX_CUT_TREE, 17, 39, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_CutTree, FLAG_TEMP_19
	object_event 10, OBJ_EVENT_GFX_CUT_TREE, 14, 39, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_CutTree, FLAG_TEMP_1A
	object_event 11, OBJ_EVENT_GFX_CUT_TREE, 11, 39, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_CutTree, FLAG_TEMP_1B
	object_event 12, OBJ_EVENT_GFX_ITEM_BALL, 12, 5, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, ThreeIsland_BerryForest_EventScript_ItemMaxEther, FLAG_HIDE_THREE_ISLAND_BERRY_FOREST_MAX_ETHER
	object_event 13, OBJ_EVENT_GFX_ITEM_BALL, 27, 11, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, ThreeIsland_BerryForest_EventScript_ItemFullHeal, FLAG_HIDE_THREE_ISLAND_BERRY_FOREST_FULL_HEAL
	object_event 14, OBJ_EVENT_GFX_ITEM_BALL, 12, 43, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, ThreeIsland_BerryForest_EventScript_ItemMaxElixir, FLAG_HIDE_THREE_ISLAND_BERRY_FOREST_MAX_ELIXIR

ThreeIsland_BerryForest_MapWarps:
	warp_def 43, 41, 3, 0, MAP_THREE_ISLAND_BOND_BRIDGE
	warp_def 42, 41, 3, 0, MAP_THREE_ISLAND_BOND_BRIDGE
	warp_def 44, 41, 3, 1, MAP_THREE_ISLAND_BOND_BRIDGE

ThreeIsland_BerryForest_MapBGEvents:
	bg_sign_event 7, 27, 0, BG_EVENT_PLAYER_FACING_ANY, ThreeIsland_BerryForest_EventScript_BewareSign
	bg_sign_event 39, 35, 0, BG_EVENT_PLAYER_FACING_ANY, ThreeIsland_BerryForest_EventScript_WelcomeSign
	bg_hidden_item_event 31, 25, 3, ITEM_RAZZ_BERRY, FLAG_HIDDEN_ITEM_THREE_ISLAND_BERRY_FOREST_RAZZ_BERRY, 1, FALSE
	bg_hidden_item_event 15, 15, 3, ITEM_BLUK_BERRY, FLAG_HIDDEN_ITEM_THREE_ISLAND_BERRY_FOREST_BLUK_BERRY, 1, FALSE
	bg_hidden_item_event 25, 24, 3, ITEM_NANAB_BERRY, FLAG_HIDDEN_ITEM_THREE_ISLAND_BERRY_FOREST_NANAB_BERRY, 1, FALSE
	bg_hidden_item_event 11, 24, 3, ITEM_WEPEAR_BERRY, FLAG_HIDDEN_ITEM_THREE_ISLAND_BERRY_FOREST_WEPEAR_BERRY, 1, FALSE
	bg_hidden_item_event 37, 18, 3, ITEM_ORAN_BERRY, FLAG_HIDDEN_ITEM_THREE_ISLAND_BERRY_FOREST_ORAN_BERRY, 1, FALSE
	bg_hidden_item_event 14, 23, 3, ITEM_CHERI_BERRY, FLAG_HIDDEN_ITEM_THREE_ISLAND_BERRY_FOREST_CHERI_BERRY, 1, FALSE
	bg_hidden_item_event 47, 5, 3, ITEM_CHESTO_BERRY, FLAG_HIDDEN_ITEM_THREE_ISLAND_BERRY_FOREST_CHESTO_BERRY, 1, FALSE
	bg_hidden_item_event 7, 30, 3, ITEM_PECHA_BERRY, FLAG_HIDDEN_ITEM_THREE_ISLAND_BERRY_FOREST_PECHA_BERRY, 1, FALSE
	bg_hidden_item_event 16, 5, 3, ITEM_RAWST_BERRY, FLAG_HIDDEN_ITEM_THREE_ISLAND_BERRY_FOREST_RAWST_BERRY, 1, FALSE
	bg_hidden_item_event 25, 6, 3, ITEM_ASPEAR_BERRY, FLAG_HIDDEN_ITEM_THREE_ISLAND_BERRY_FOREST_ASPEAR_BERRY, 1, FALSE
	bg_hidden_item_event 46, 32, 3, ITEM_PERSIM_BERRY, FLAG_HIDDEN_ITEM_THREE_ISLAND_BERRY_FOREST_PERSIM_BERRY, 1, FALSE
	bg_hidden_item_event 43, 16, 3, ITEM_PINAP_BERRY, FLAG_HIDDEN_ITEM_THREE_ISLAND_BERRY_FOREST_PINAP_BERRY, 1, FALSE
	bg_hidden_item_event 8, 5, 3, ITEM_LUM_BERRY, FLAG_HIDDEN_ITEM_THREE_ISLAND_BERRY_FOREST_LUM_BERRY, 1, FALSE

ThreeIsland_BerryForest_MapEvents::
	map_events ThreeIsland_BerryForest_ObjectEvents, ThreeIsland_BerryForest_MapWarps, NULL, ThreeIsland_BerryForest_MapBGEvents

@ ===== END data/maps/ThreeIsland_BerryForest/events.inc =====
@ ===== BEGIN data/maps/FourIsland_IcefallCave_Entrance/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FourIsland_IcefallCave_Entrance/map.json
@

	.align 2

FourIsland_IcefallCave_Entrance_MapWarps:
	warp_def 17, 30, 3, 3, MAP_FOUR_ISLAND
	warp_def 10, 21, 3, 0, MAP_FOUR_ISLAND_ICEFALL_CAVE_1F
	warp_def 9, 7, 3, 1, MAP_FOUR_ISLAND_ICEFALL_CAVE_1F

FourIsland_IcefallCave_Entrance_MapEvents::
	map_events NULL, FourIsland_IcefallCave_Entrance_MapWarps, NULL, NULL

@ ===== END data/maps/FourIsland_IcefallCave_Entrance/events.inc =====
@ ===== BEGIN data/maps/FourIsland_IcefallCave_1F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FourIsland_IcefallCave_1F/map.json
@

	.align 2

FourIsland_IcefallCave_1F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_ITEM_BALL, 11, 7, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, FourIsland_IcefallCave_1F_EventScript_ItemUltraBall, FLAG_HIDE_FOUR_ISLAND_ICEFALL_CAVE_1F_ULTRA_BALL
	object_event 2, OBJ_EVENT_GFX_ITEM_BALL, 12, 16, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, FourIsland_IcefallCave_1F_EventScript_ItemHM07, FLAG_HIDE_FOUR_ISLAND_ICEFALL_CAVE_1F_HM07

FourIsland_IcefallCave_1F_MapWarps:
	warp_def 3, 17, 0, 1, MAP_FOUR_ISLAND_ICEFALL_CAVE_ENTRANCE
	warp_def 2, 8, 3, 2, MAP_FOUR_ISLAND_ICEFALL_CAVE_ENTRANCE
	warp_def 12, 12, 3, 0, MAP_FOUR_ISLAND_ICEFALL_CAVE_B1F
	warp_def 12, 3, 3, 1, MAP_FOUR_ISLAND_ICEFALL_CAVE_B1F
	warp_def 15, 16, 3, 2, MAP_FOUR_ISLAND_ICEFALL_CAVE_B1F
	warp_def 3, 6, 3, 0, MAP_FOUR_ISLAND_ICEFALL_CAVE_BACK

FourIsland_IcefallCave_1F_MapEvents::
	map_events FourIsland_IcefallCave_1F_ObjectEvents, FourIsland_IcefallCave_1F_MapWarps, NULL, NULL

@ ===== END data/maps/FourIsland_IcefallCave_1F/events.inc =====
@ ===== BEGIN data/maps/FourIsland_IcefallCave_B1F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FourIsland_IcefallCave_B1F/map.json
@

	.align 2

FourIsland_IcefallCave_B1F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_ITEM_BALL, 10, 14, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, FourIsland_IcefallCave_B1F_EventScript_ItemFullRestore, FLAG_HIDE_FOUR_ISLAND_ICEFALL_CAVE_B1F_FULL_RESTORE
	object_event 2, OBJ_EVENT_GFX_ITEM_BALL, 21, 7, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, FourIsland_IcefallCave_B1F_EventScript_ItemNeverMeltIce, FLAG_HIDE_FOUR_ISLAND_ICEFALL_CAVE_B1F_NEVER_MELT_ICE

FourIsland_IcefallCave_B1F_MapWarps:
	warp_def 12, 12, 3, 2, MAP_FOUR_ISLAND_ICEFALL_CAVE_1F
	warp_def 12, 3, 3, 3, MAP_FOUR_ISLAND_ICEFALL_CAVE_1F
	warp_def 15, 16, 3, 4, MAP_FOUR_ISLAND_ICEFALL_CAVE_1F

FourIsland_IcefallCave_B1F_MapEvents::
	map_events FourIsland_IcefallCave_B1F_ObjectEvents, FourIsland_IcefallCave_B1F_MapWarps, NULL, NULL

@ ===== END data/maps/FourIsland_IcefallCave_B1F/events.inc =====
@ ===== BEGIN data/maps/FourIsland_IcefallCave_Back/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FourIsland_IcefallCave_Back/map.json
@

	.align 2

FourIsland_IcefallCave_Back_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_ROCKET_M, 11, 14, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, 0x0, FLAG_HIDE_ICEFALL_CAVE_ROCKETS
	object_event 2, OBJ_EVENT_GFX_ROCKET_M, 13, 14, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, 0x0, FLAG_HIDE_ICEFALL_CAVE_ROCKETS
	object_event 3, OBJ_EVENT_GFX_LORELEI, 12, 16, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NONE, 0, FourIsland_IcefallCave_Back_EventScript_Lorelei, FLAG_HIDE_ICEFALL_CAVE_LORELEI
	object_event 4, OBJ_EVENT_GFX_ROCKET_M, 10, 15, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, 0x0, FLAG_HIDE_ICEFALL_CAVE_ROCKETS

FourIsland_IcefallCave_Back_MapWarps:
	warp_def 12, 23, 0, 5, MAP_FOUR_ISLAND_ICEFALL_CAVE_1F

FourIsland_IcefallCave_Back_MapCoordEvents:
	coord_event 11, 18, 3, VAR_MAP_SCENE_ICEFALL_CAVE_BACK, 0, FourIsland_IcefallCave_Back_EventScript_LoreleiRocketsScene
	coord_event 12, 18, 3, VAR_MAP_SCENE_ICEFALL_CAVE_BACK, 0, FourIsland_IcefallCave_Back_EventScript_LoreleiRocketsScene
	coord_event 13, 18, 3, VAR_MAP_SCENE_ICEFALL_CAVE_BACK, 0, FourIsland_IcefallCave_Back_EventScript_LoreleiRocketsScene

FourIsland_IcefallCave_Back_MapEvents::
	map_events FourIsland_IcefallCave_Back_ObjectEvents, FourIsland_IcefallCave_Back_MapWarps, FourIsland_IcefallCave_Back_MapCoordEvents, NULL

@ ===== END data/maps/FourIsland_IcefallCave_Back/events.inc =====
@ ===== BEGIN data/maps/FiveIsland_RocketWarehouse/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FiveIsland_RocketWarehouse/map.json
@

	.align 2

FiveIsland_RocketWarehouse_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_ROCKET_M, 15, 11, 3, MOVEMENT_TYPE_FACE_DOWN_AND_LEFT, 1, 1, TRAINER_TYPE_NORMAL, 1, FiveIsland_RocketWarehouse_EventScript_Grunt2, FLAG_HIDE_FIVE_ISLAND_ROCKETS
	object_event 2, OBJ_EVENT_GFX_ROCKET_M, 17, 15, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 1, FiveIsland_RocketWarehouse_EventScript_Grunt3, FLAG_HIDE_FIVE_ISLAND_ROCKETS
	object_event 3, OBJ_EVENT_GFX_ROCKET_F, 27, 16, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NORMAL, 3, FiveIsland_RocketWarehouse_EventScript_Admin1, FLAG_HIDE_FIVE_ISLAND_ROCKETS
	object_event 4, OBJ_EVENT_GFX_ROCKET_M, 25, 11, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 3, FiveIsland_RocketWarehouse_EventScript_Admin2, FLAG_HIDE_FIVE_ISLAND_ROCKETS
	object_event 5, OBJ_EVENT_GFX_ROCKET_F, 6, 6, 3, MOVEMENT_TYPE_FACE_UP_AND_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 3, FiveIsland_RocketWarehouse_EventScript_Grunt1, FLAG_HIDE_FIVE_ISLAND_ROCKETS
	object_event 6, OBJ_EVENT_GFX_SCIENTIST, 27, 4, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NORMAL, 0, FiveIsland_RocketWarehouse_EventScript_Gideon, 0
	object_event 7, OBJ_EVENT_GFX_ITEM_BALL, 8, 25, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, FiveIsland_RocketWarehouse_EventScript_ItemBigPearl, FLAG_HIDE_FIVE_ISLAND_ROCKET_WAREHOUSE_BIG_PEARL
	object_event 8, OBJ_EVENT_GFX_ITEM_BALL, 17, 3, 0, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, FiveIsland_RocketWarehouse_EventScript_ItemTM36, FLAG_HIDE_FIVE_ISLAND_ROCKET_WAREHOUSE_TM36
	object_event 9, OBJ_EVENT_GFX_ITEM_BALL, 1, 16, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, FiveIsland_RocketWarehouse_EventScript_ItemPearl, FLAG_HIDE_FIVE_ISLAND_ROCKET_WAREHOUSE_PEARL
	object_event 10, OBJ_EVENT_GFX_ITEM_BALL, 4, 5, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, FiveIsland_RocketWarehouse_EventScript_ItemUpGrade, FLAG_HIDE_FIVE_ISLAND_ROCKET_WAREHOUSE_UP_GRADE

FiveIsland_RocketWarehouse_MapWarps:
	warp_def 24, 25, 3, 0, MAP_FIVE_ISLAND_MEADOW

FiveIsland_RocketWarehouse_MapCoordEvents:
	coord_event 22, 11, 3, VAR_MAP_SCENE_ROCKET_WAREHOUSE, 0, FiveIsland_RocketWarehouse_EventScript_Admin2Trigger
	coord_event 23, 11, 3, VAR_MAP_SCENE_ROCKET_WAREHOUSE, 0, FiveIsland_RocketWarehouse_EventScript_Admin2Trigger
	coord_event 24, 11, 3, VAR_MAP_SCENE_ROCKET_WAREHOUSE, 0, FiveIsland_RocketWarehouse_EventScript_Admin2Trigger

FiveIsland_RocketWarehouse_MapBGEvents:
	bg_sign_event 11, 2, 0, BG_EVENT_PLAYER_FACING_ANY, FiveIsland_RocketWarehouse_EventScript_Cage
	bg_sign_event 26, 11, 0, BG_EVENT_PLAYER_FACING_EAST, FiveIsland_RocketWarehouse_EventScript_Computer
	bg_hidden_item_event 27, 2, 0, ITEM_NEST_BALL, FLAG_HIDDEN_ITEM_FIVE_ISLAND_ROCKET_WAREHOUSE_NEST_BALL, 1, FALSE
	bg_hidden_item_event 7, 16, 0, ITEM_NET_BALL, FLAG_HIDDEN_ITEM_FIVE_ISLAND_ROCKET_WAREHOUSE_NET_BALL, 1, FALSE
	bg_sign_event 12, 2, 0, BG_EVENT_PLAYER_FACING_ANY, FiveIsland_RocketWarehouse_EventScript_Cage
	bg_sign_event 10, 2, 0, BG_EVENT_PLAYER_FACING_ANY, FiveIsland_RocketWarehouse_EventScript_Cage
	bg_sign_event 9, 2, 0, BG_EVENT_PLAYER_FACING_ANY, FiveIsland_RocketWarehouse_EventScript_Cage
	bg_sign_event 8, 2, 0, BG_EVENT_PLAYER_FACING_ANY, FiveIsland_RocketWarehouse_EventScript_Cage
	bg_sign_event 7, 2, 0, BG_EVENT_PLAYER_FACING_ANY, FiveIsland_RocketWarehouse_EventScript_Cage
	bg_sign_event 11, 5, 0, BG_EVENT_PLAYER_FACING_ANY, FiveIsland_RocketWarehouse_EventScript_Cage
	bg_sign_event 10, 5, 0, BG_EVENT_PLAYER_FACING_ANY, FiveIsland_RocketWarehouse_EventScript_Cage
	bg_sign_event 11, 4, 0, BG_EVENT_PLAYER_FACING_ANY, FiveIsland_RocketWarehouse_EventScript_Cage
	bg_sign_event 10, 4, 0, BG_EVENT_PLAYER_FACING_ANY, FiveIsland_RocketWarehouse_EventScript_Cage
	bg_sign_event 8, 4, 0, BG_EVENT_PLAYER_FACING_ANY, FiveIsland_RocketWarehouse_EventScript_Cage
	bg_sign_event 7, 4, 0, BG_EVENT_PLAYER_FACING_ANY, FiveIsland_RocketWarehouse_EventScript_Cage
	bg_sign_event 8, 5, 0, BG_EVENT_PLAYER_FACING_ANY, FiveIsland_RocketWarehouse_EventScript_Cage
	bg_sign_event 7, 5, 0, BG_EVENT_PLAYER_FACING_ANY, FiveIsland_RocketWarehouse_EventScript_Cage
	bg_sign_event 5, 3, 0, BG_EVENT_PLAYER_FACING_ANY, FiveIsland_RocketWarehouse_EventScript_Cage
	bg_sign_event 4, 3, 0, BG_EVENT_PLAYER_FACING_ANY, FiveIsland_RocketWarehouse_EventScript_Cage
	bg_sign_event 5, 4, 0, BG_EVENT_PLAYER_FACING_ANY, FiveIsland_RocketWarehouse_EventScript_Cage
	bg_sign_event 4, 4, 0, BG_EVENT_PLAYER_FACING_ANY, FiveIsland_RocketWarehouse_EventScript_Cage
	bg_sign_event 3, 4, 0, BG_EVENT_PLAYER_FACING_ANY, FiveIsland_RocketWarehouse_EventScript_Cage
	bg_sign_event 2, 4, 0, BG_EVENT_PLAYER_FACING_ANY, FiveIsland_RocketWarehouse_EventScript_Cage
	bg_sign_event 2, 5, 0, BG_EVENT_PLAYER_FACING_ANY, FiveIsland_RocketWarehouse_EventScript_Cage
	bg_sign_event 3, 5, 0, BG_EVENT_PLAYER_FACING_ANY, FiveIsland_RocketWarehouse_EventScript_Cage

FiveIsland_RocketWarehouse_MapEvents::
	map_events FiveIsland_RocketWarehouse_ObjectEvents, FiveIsland_RocketWarehouse_MapWarps, FiveIsland_RocketWarehouse_MapCoordEvents, FiveIsland_RocketWarehouse_MapBGEvents

@ ===== END data/maps/FiveIsland_RocketWarehouse/events.inc =====
@ ===== BEGIN data/maps/SixIsland_DottedHole_1F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SixIsland_DottedHole_1F/map.json
@

	.align 2

SixIsland_DottedHole_1F_MapWarps:
	warp_def 6, 9, 3, 0, MAP_SIX_ISLAND_RUIN_VALLEY
	warp_def 6, 5, 3, 0, MAP_SIX_ISLAND_DOTTED_HOLE_B1F
	warp_def 13, 5, 3, 0, MAP_SIX_ISLAND_DOTTED_HOLE_SAPPHIRE_ROOM
	warp_def 6, 7, 3, 2, MAP_SIX_ISLAND_DOTTED_HOLE_B1F

SixIsland_DottedHole_1F_MapEvents::
	map_events NULL, SixIsland_DottedHole_1F_MapWarps, NULL, NULL

@ ===== END data/maps/SixIsland_DottedHole_1F/events.inc =====
@ ===== BEGIN data/maps/SixIsland_DottedHole_B1F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SixIsland_DottedHole_B1F/map.json
@

	.align 2

SixIsland_DottedHole_B1F_MapWarps:
	warp_def 6, 7, 3, 1, MAP_SIX_ISLAND_DOTTED_HOLE_1F
	warp_def 6, 1, 3, 0, MAP_SIX_ISLAND_DOTTED_HOLE_B2F
	warp_def 11, 5, 3, 3, MAP_SIX_ISLAND_DOTTED_HOLE_1F
	warp_def 6, 9, 3, 3, MAP_SIX_ISLAND_DOTTED_HOLE_1F
	warp_def 1, 5, 3, 3, MAP_SIX_ISLAND_DOTTED_HOLE_1F

SixIsland_DottedHole_B1F_MapBGEvents:
	bg_sign_event 6, 5, 0, BG_EVENT_PLAYER_FACING_NORTH, SixIsland_DottedHole_B1F_EventScript_BrailleUp

SixIsland_DottedHole_B1F_MapEvents::
	map_events NULL, SixIsland_DottedHole_B1F_MapWarps, NULL, SixIsland_DottedHole_B1F_MapBGEvents

@ ===== END data/maps/SixIsland_DottedHole_B1F/events.inc =====
@ ===== BEGIN data/maps/SixIsland_DottedHole_B2F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SixIsland_DottedHole_B2F/map.json
@

	.align 2

SixIsland_DottedHole_B2F_MapWarps:
	warp_def 6, 7, 3, 1, MAP_SIX_ISLAND_DOTTED_HOLE_B1F
	warp_def 6, 1, 3, 3, MAP_SIX_ISLAND_DOTTED_HOLE_1F
	warp_def 11, 5, 3, 3, MAP_SIX_ISLAND_DOTTED_HOLE_1F
	warp_def 6, 9, 3, 3, MAP_SIX_ISLAND_DOTTED_HOLE_1F
	warp_def 1, 5, 3, 0, MAP_SIX_ISLAND_DOTTED_HOLE_B3F

SixIsland_DottedHole_B2F_MapBGEvents:
	bg_sign_event 6, 5, 0, BG_EVENT_PLAYER_FACING_NORTH, SixIsland_DottedHole_B2F_EventScript_BrailleLeft

SixIsland_DottedHole_B2F_MapEvents::
	map_events NULL, SixIsland_DottedHole_B2F_MapWarps, NULL, SixIsland_DottedHole_B2F_MapBGEvents

@ ===== END data/maps/SixIsland_DottedHole_B2F/events.inc =====
@ ===== BEGIN data/maps/SixIsland_DottedHole_B3F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SixIsland_DottedHole_B3F/map.json
@

	.align 2

SixIsland_DottedHole_B3F_MapWarps:
	warp_def 6, 7, 3, 4, MAP_SIX_ISLAND_DOTTED_HOLE_B2F
	warp_def 6, 1, 3, 3, MAP_SIX_ISLAND_DOTTED_HOLE_1F
	warp_def 11, 5, 3, 0, MAP_SIX_ISLAND_DOTTED_HOLE_B4F
	warp_def 6, 9, 3, 3, MAP_SIX_ISLAND_DOTTED_HOLE_1F
	warp_def 1, 5, 3, 3, MAP_SIX_ISLAND_DOTTED_HOLE_1F

SixIsland_DottedHole_B3F_MapBGEvents:
	bg_sign_event 6, 5, 0, BG_EVENT_PLAYER_FACING_NORTH, SixIsland_DottedHole_B3F_EventScript_BrailleRight

SixIsland_DottedHole_B3F_MapEvents::
	map_events NULL, SixIsland_DottedHole_B3F_MapWarps, NULL, SixIsland_DottedHole_B3F_MapBGEvents

@ ===== END data/maps/SixIsland_DottedHole_B3F/events.inc =====
@ ===== BEGIN data/maps/SixIsland_DottedHole_B4F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SixIsland_DottedHole_B4F/map.json
@

	.align 2

SixIsland_DottedHole_B4F_MapWarps:
	warp_def 6, 7, 3, 2, MAP_SIX_ISLAND_DOTTED_HOLE_B3F
	warp_def 6, 1, 3, 3, MAP_SIX_ISLAND_DOTTED_HOLE_1F
	warp_def 11, 5, 3, 3, MAP_SIX_ISLAND_DOTTED_HOLE_1F
	warp_def 6, 9, 3, 1, MAP_SIX_ISLAND_DOTTED_HOLE_SAPPHIRE_ROOM
	warp_def 1, 5, 3, 3, MAP_SIX_ISLAND_DOTTED_HOLE_1F

SixIsland_DottedHole_B4F_MapBGEvents:
	bg_sign_event 6, 5, 0, BG_EVENT_PLAYER_FACING_NORTH, SixIsland_DottedHole_B4F_EventScript_BrailleDown

SixIsland_DottedHole_B4F_MapEvents::
	map_events NULL, SixIsland_DottedHole_B4F_MapWarps, NULL, SixIsland_DottedHole_B4F_MapBGEvents

@ ===== END data/maps/SixIsland_DottedHole_B4F/events.inc =====
@ ===== BEGIN data/maps/SixIsland_DottedHole_SapphireRoom/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SixIsland_DottedHole_SapphireRoom/map.json
@

	.align 2

SixIsland_DottedHole_SapphireRoom_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_SAPPHIRE, 7, 7, 0, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SixIsland_DottedHole_SapphireRoom_EventScript_Sapphire, FLAG_HIDE_SAPPHIRE
	object_event 2, OBJ_EVENT_GFX_SCIENTIST, 5, 9, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, 0x0, FLAG_HIDE_DOTTED_HOLE_SCIENTIST

SixIsland_DottedHole_SapphireRoom_MapWarps:
	warp_def 11, 7, 3, 2, MAP_SIX_ISLAND_DOTTED_HOLE_1F
	warp_def 5, 9, 3, 3, MAP_SIX_ISLAND_DOTTED_HOLE_B4F

SixIsland_DottedHole_SapphireRoom_MapBGEvents:
	bg_sign_event 7, 2, 0, BG_EVENT_PLAYER_FACING_NORTH, SixIsland_DottedHole_SapphireRoom_EventScript_BrailleMessage

SixIsland_DottedHole_SapphireRoom_MapEvents::
	map_events SixIsland_DottedHole_SapphireRoom_ObjectEvents, SixIsland_DottedHole_SapphireRoom_MapWarps, NULL, SixIsland_DottedHole_SapphireRoom_MapBGEvents

@ ===== END data/maps/SixIsland_DottedHole_SapphireRoom/events.inc =====
@ ===== BEGIN data/maps/SixIsland_PatternBush/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SixIsland_PatternBush/map.json
@

	.align 2

SixIsland_PatternBush_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_WOMAN_2, 48, 15, 3, MOVEMENT_TYPE_FACE_DOWN_UP_AND_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 3, SixIsland_PatternBush_EventScript_Bethany, 0
	object_event 2, OBJ_EVENT_GFX_WOMAN_2, 10, 5, 3, MOVEMENT_TYPE_FACE_DOWN_AND_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 2, SixIsland_PatternBush_EventScript_Allison, 0
	object_event 3, OBJ_EVENT_GFX_BUG_CATCHER, 51, 6, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 2, SixIsland_PatternBush_EventScript_Garret, 0
	object_event 4, OBJ_EVENT_GFX_BUG_CATCHER, 12, 13, 3, MOVEMENT_TYPE_WANDER_AROUND, 1, 2, TRAINER_TYPE_NORMAL, 2, SixIsland_PatternBush_EventScript_Jonah, 0
	object_event 5, OBJ_EVENT_GFX_BUG_CATCHER, 37, 23, 3, MOVEMENT_TYPE_WALK_SEQUENCE_LEFT_UP_RIGHT_DOWN, 2, 5, TRAINER_TYPE_NORMAL, 1, SixIsland_PatternBush_EventScript_Vance, 0
	object_event 6, OBJ_EVENT_GFX_YOUNGSTER, 32, 5, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 2, SixIsland_PatternBush_EventScript_Nash, 0
	object_event 7, OBJ_EVENT_GFX_YOUNGSTER, 52, 20, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 4, SixIsland_PatternBush_EventScript_Cordell, 0
	object_event 8, OBJ_EVENT_GFX_LASS, 8, 21, 3, MOVEMENT_TYPE_FACE_DOWN_AND_LEFT, 1, 1, TRAINER_TYPE_NORMAL, 5, SixIsland_PatternBush_EventScript_Dalia, 0
	object_event 9, OBJ_EVENT_GFX_LASS, 39, 6, 3, MOVEMENT_TYPE_WANDER_AROUND, 1, 1, TRAINER_TYPE_NORMAL, 3, SixIsland_PatternBush_EventScript_Joana, 0
	object_event 10, OBJ_EVENT_GFX_CAMPER, 3, 9, 3, MOVEMENT_TYPE_WANDER_UP_AND_DOWN, 1, 2, TRAINER_TYPE_NORMAL, 3, SixIsland_PatternBush_EventScript_Riley, 0
	object_event 11, OBJ_EVENT_GFX_PICNICKER, 19, 24, 3, MOVEMENT_TYPE_WALK_RIGHT_AND_LEFT, 5, 1, TRAINER_TYPE_NORMAL, 1, SixIsland_PatternBush_EventScript_Marcy, 0
	object_event 12, OBJ_EVENT_GFX_HIKER, 30, 19, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NORMAL, 3, SixIsland_PatternBush_EventScript_Layton, 0

SixIsland_PatternBush_MapWarps:
	warp_def 54, 26, 3, 0, MAP_SIX_ISLAND_GREEN_PATH
	warp_def 55, 26, 3, 0, MAP_SIX_ISLAND_GREEN_PATH
	warp_def 56, 26, 3, 1, MAP_SIX_ISLAND_GREEN_PATH
	warp_def 3, 26, 3, 2, MAP_SIX_ISLAND_GREEN_PATH
	warp_def 4, 26, 3, 2, MAP_SIX_ISLAND_GREEN_PATH
	warp_def 5, 26, 3, 3, MAP_SIX_ISLAND_GREEN_PATH

SixIsland_PatternBush_MapEvents::
	map_events SixIsland_PatternBush_ObjectEvents, SixIsland_PatternBush_MapWarps, NULL, NULL

@ ===== END data/maps/SixIsland_PatternBush/events.inc =====
@ ===== BEGIN data/maps/SixIsland_AlteringCave/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SixIsland_AlteringCave/map.json
@

	.align 2

SixIsland_AlteringCave_MapWarps:
	warp_def 18, 22, 3, 0, MAP_SIX_ISLAND_OUTCAST_ISLAND

SixIsland_AlteringCave_MapEvents::
	map_events NULL, SixIsland_AlteringCave_MapWarps, NULL, NULL

@ ===== END data/maps/SixIsland_AlteringCave/events.inc =====
@ ===== BEGIN data/maps/NavelRock_Exterior/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/NavelRock_Exterior/map.json
@

	.align 2

NavelRock_Exterior_MapWarps:
	warp_def 9, 8, 3, 1, MAP_NAVEL_ROCK_1F
	warp_def 9, 16, 3, 0, MAP_NAVEL_ROCK_HARBOR

NavelRock_Exterior_MapEvents::
	map_events NULL, NavelRock_Exterior_MapWarps, NULL, NULL

@ ===== END data/maps/NavelRock_Exterior/events.inc =====
@ ===== BEGIN data/maps/TrainerTower_1F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/TrainerTower_1F/map.json
@

	.align 2

TrainerTower_1F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_TRAINER_TOWER_DUDE, 9, 7, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, 0x0, FLAG_TEMP_6
	object_event 2, OBJ_EVENT_GFX_VAR_0, 11, 10, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, TrainerTower_EventScript_DoublesTrainer1, FLAG_TEMP_2
	object_event 3, OBJ_EVENT_GFX_VAR_1, 15, 13, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NONE, 0, TrainerTower_EventScript_SinglesTrainer, FLAG_TEMP_3
	object_event 4, OBJ_EVENT_GFX_VAR_2, 10, 16, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NONE, 0, TrainerTower_EventScript_KnockoutTrainer, FLAG_TEMP_4
	object_event 5, OBJ_EVENT_GFX_VAR_3, 10, 10, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, TrainerTower_EventScript_DoublesTrainer2, FLAG_TEMP_5

TrainerTower_1F_MapWarps:
	warp_def 15, 6, 3, 1, MAP_TRAINER_TOWER_2F
	warp_def 4, 6, 3, 0, MAP_TRAINER_TOWER_LOBBY

TrainerTower_1F_MapCoordEvents:
	coord_event 10, 13, 3, VAR_TEMP_E, 0, TrainerTower_EventScript_SingleBattleTrigger
	coord_event 9, 12, 0, VAR_TEMP_F, 0, TrainerTower_EventScript_DoubleBattleTriggerTop
	coord_event 9, 13, 3, VAR_TEMP_F, 0, TrainerTower_EventScript_DoubleBattleTriggerBottom

TrainerTower_1F_MapEvents::
	map_events TrainerTower_1F_ObjectEvents, TrainerTower_1F_MapWarps, TrainerTower_1F_MapCoordEvents, NULL

@ ===== END data/maps/TrainerTower_1F/events.inc =====
@ ===== BEGIN data/maps/TrainerTower_2F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/TrainerTower_2F/map.json
@

	.align 2

TrainerTower_2F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_TRAINER_TOWER_DUDE, 9, 7, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, TrainerTower_EventScript_Owner, FLAG_TEMP_6
	object_event 2, OBJ_EVENT_GFX_VAR_0, 10, 10, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, TrainerTower_EventScript_DoublesTrainer1, FLAG_TEMP_2
	object_event 3, OBJ_EVENT_GFX_VAR_1, 15, 13, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NONE, 0, TrainerTower_EventScript_SinglesTrainer, FLAG_TEMP_3
	object_event 4, OBJ_EVENT_GFX_VAR_2, 10, 16, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NONE, 0, TrainerTower_EventScript_KnockoutTrainer, FLAG_TEMP_4
	object_event 5, OBJ_EVENT_GFX_VAR_3, 11, 10, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, TrainerTower_EventScript_DoublesTrainer2, FLAG_TEMP_5

TrainerTower_2F_MapWarps:
	warp_def 15, 6, 3, 1, MAP_TRAINER_TOWER_3F
	warp_def 4, 6, 3, 0, MAP_TRAINER_TOWER_1F
	warp_def 13, 5, 0, 0, MAP_TRAINER_TOWER_ELEVATOR

TrainerTower_2F_MapCoordEvents:
	coord_event 10, 13, 3, VAR_TEMP_E, 0, TrainerTower_EventScript_SingleBattleTrigger
	coord_event 9, 12, 3, VAR_TEMP_F, 0, TrainerTower_EventScript_DoubleBattleTriggerTop
	coord_event 9, 13, 3, VAR_TEMP_F, 0, TrainerTower_EventScript_DoubleBattleTriggerBottom

TrainerTower_2F_MapEvents::
	map_events TrainerTower_2F_ObjectEvents, TrainerTower_2F_MapWarps, TrainerTower_2F_MapCoordEvents, NULL

@ ===== END data/maps/TrainerTower_2F/events.inc =====
@ ===== BEGIN data/maps/TrainerTower_3F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/TrainerTower_3F/map.json
@

	.align 2

TrainerTower_3F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_TRAINER_TOWER_DUDE, 9, 7, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, TrainerTower_EventScript_Owner, FLAG_TEMP_6
	object_event 2, OBJ_EVENT_GFX_VAR_0, 10, 10, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, TrainerTower_EventScript_DoublesTrainer1, FLAG_TEMP_2
	object_event 3, OBJ_EVENT_GFX_VAR_1, 15, 13, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NONE, 0, TrainerTower_EventScript_SinglesTrainer, FLAG_TEMP_3
	object_event 4, OBJ_EVENT_GFX_VAR_2, 10, 16, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NONE, 0, TrainerTower_EventScript_KnockoutTrainer, FLAG_TEMP_4
	object_event 5, OBJ_EVENT_GFX_VAR_3, 11, 10, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, TrainerTower_EventScript_DoublesTrainer2, FLAG_TEMP_5

TrainerTower_3F_MapWarps:
	warp_def 15, 6, 3, 1, MAP_TRAINER_TOWER_4F
	warp_def 4, 6, 3, 0, MAP_TRAINER_TOWER_2F
	warp_def 13, 5, 0, 0, MAP_TRAINER_TOWER_ELEVATOR

TrainerTower_3F_MapCoordEvents:
	coord_event 10, 13, 3, VAR_TEMP_E, 0, TrainerTower_EventScript_SingleBattleTrigger
	coord_event 9, 12, 3, VAR_TEMP_F, 0, TrainerTower_EventScript_DoubleBattleTriggerTop
	coord_event 9, 13, 3, VAR_TEMP_F, 0, TrainerTower_EventScript_DoubleBattleTriggerBottom

TrainerTower_3F_MapEvents::
	map_events TrainerTower_3F_ObjectEvents, TrainerTower_3F_MapWarps, TrainerTower_3F_MapCoordEvents, NULL

@ ===== END data/maps/TrainerTower_3F/events.inc =====
@ ===== BEGIN data/maps/TrainerTower_4F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/TrainerTower_4F/map.json
@

	.align 2

TrainerTower_4F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_TRAINER_TOWER_DUDE, 9, 7, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, TrainerTower_EventScript_Owner, FLAG_TEMP_6
	object_event 2, OBJ_EVENT_GFX_VAR_0, 10, 10, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, TrainerTower_EventScript_DoublesTrainer1, FLAG_TEMP_2
	object_event 3, OBJ_EVENT_GFX_VAR_1, 15, 13, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NONE, 0, TrainerTower_EventScript_SinglesTrainer, FLAG_TEMP_3
	object_event 4, OBJ_EVENT_GFX_VAR_2, 10, 16, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NONE, 0, TrainerTower_EventScript_KnockoutTrainer, FLAG_TEMP_4
	object_event 5, OBJ_EVENT_GFX_VAR_3, 11, 10, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, TrainerTower_EventScript_DoublesTrainer2, FLAG_TEMP_5

TrainerTower_4F_MapWarps:
	warp_def 15, 6, 3, 1, MAP_TRAINER_TOWER_5F
	warp_def 4, 6, 3, 0, MAP_TRAINER_TOWER_3F
	warp_def 13, 5, 0, 0, MAP_TRAINER_TOWER_ELEVATOR

TrainerTower_4F_MapCoordEvents:
	coord_event 10, 13, 3, VAR_TEMP_E, 0, TrainerTower_EventScript_SingleBattleTrigger
	coord_event 9, 12, 3, VAR_TEMP_F, 0, TrainerTower_EventScript_DoubleBattleTriggerTop
	coord_event 9, 13, 3, VAR_TEMP_F, 0, TrainerTower_EventScript_DoubleBattleTriggerBottom

TrainerTower_4F_MapEvents::
	map_events TrainerTower_4F_ObjectEvents, TrainerTower_4F_MapWarps, TrainerTower_4F_MapCoordEvents, NULL

@ ===== END data/maps/TrainerTower_4F/events.inc =====
@ ===== BEGIN data/maps/TrainerTower_5F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/TrainerTower_5F/map.json
@

	.align 2

TrainerTower_5F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_TRAINER_TOWER_DUDE, 9, 7, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, TrainerTower_EventScript_Owner, FLAG_TEMP_6
	object_event 2, OBJ_EVENT_GFX_VAR_0, 10, 10, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, TrainerTower_EventScript_DoublesTrainer1, FLAG_TEMP_2
	object_event 3, OBJ_EVENT_GFX_VAR_1, 15, 13, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NONE, 0, TrainerTower_EventScript_SinglesTrainer, FLAG_TEMP_3
	object_event 4, OBJ_EVENT_GFX_VAR_2, 10, 16, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NONE, 0, TrainerTower_EventScript_KnockoutTrainer, FLAG_TEMP_4
	object_event 5, OBJ_EVENT_GFX_VAR_3, 11, 10, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, TrainerTower_EventScript_DoublesTrainer2, FLAG_TEMP_5

TrainerTower_5F_MapWarps:
	warp_def 15, 6, 3, 1, MAP_TRAINER_TOWER_6F
	warp_def 4, 6, 3, 0, MAP_TRAINER_TOWER_4F
	warp_def 13, 5, 0, 0, MAP_TRAINER_TOWER_ELEVATOR

TrainerTower_5F_MapCoordEvents:
	coord_event 10, 13, 3, VAR_TEMP_E, 0, TrainerTower_EventScript_SingleBattleTrigger
	coord_event 9, 12, 3, VAR_TEMP_F, 0, TrainerTower_EventScript_DoubleBattleTriggerTop
	coord_event 9, 13, 3, VAR_TEMP_F, 0, TrainerTower_EventScript_DoubleBattleTriggerBottom

TrainerTower_5F_MapEvents::
	map_events TrainerTower_5F_ObjectEvents, TrainerTower_5F_MapWarps, TrainerTower_5F_MapCoordEvents, NULL

@ ===== END data/maps/TrainerTower_5F/events.inc =====
@ ===== BEGIN data/maps/TrainerTower_6F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/TrainerTower_6F/map.json
@

	.align 2

TrainerTower_6F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_TRAINER_TOWER_DUDE, 9, 7, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, TrainerTower_EventScript_Owner, FLAG_TEMP_6
	object_event 2, OBJ_EVENT_GFX_VAR_0, 10, 10, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, TrainerTower_EventScript_DoublesTrainer1, FLAG_TEMP_2
	object_event 3, OBJ_EVENT_GFX_VAR_1, 15, 13, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NONE, 0, TrainerTower_EventScript_SinglesTrainer, FLAG_TEMP_3
	object_event 4, OBJ_EVENT_GFX_VAR_2, 10, 16, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NONE, 0, TrainerTower_EventScript_KnockoutTrainer, FLAG_TEMP_4
	object_event 5, OBJ_EVENT_GFX_VAR_3, 11, 10, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, TrainerTower_EventScript_DoublesTrainer2, FLAG_TEMP_5

TrainerTower_6F_MapWarps:
	warp_def 15, 6, 3, 1, MAP_TRAINER_TOWER_7F
	warp_def 4, 6, 3, 0, MAP_TRAINER_TOWER_5F
	warp_def 13, 5, 0, 0, MAP_TRAINER_TOWER_ELEVATOR

TrainerTower_6F_MapCoordEvents:
	coord_event 10, 13, 3, VAR_TEMP_E, 0, TrainerTower_EventScript_SingleBattleTrigger
	coord_event 9, 12, 3, VAR_TEMP_F, 0, TrainerTower_EventScript_DoubleBattleTriggerTop
	coord_event 9, 13, 3, VAR_TEMP_F, 0, TrainerTower_EventScript_DoubleBattleTriggerBottom

TrainerTower_6F_MapEvents::
	map_events TrainerTower_6F_ObjectEvents, TrainerTower_6F_MapWarps, TrainerTower_6F_MapCoordEvents, NULL

@ ===== END data/maps/TrainerTower_6F/events.inc =====
@ ===== BEGIN data/maps/TrainerTower_7F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/TrainerTower_7F/map.json
@

	.align 2

TrainerTower_7F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_TRAINER_TOWER_DUDE, 9, 7, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, TrainerTower_EventScript_Owner, FLAG_TEMP_6
	object_event 2, OBJ_EVENT_GFX_VAR_0, 10, 10, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, TrainerTower_EventScript_DoublesTrainer1, FLAG_TEMP_2
	object_event 3, OBJ_EVENT_GFX_VAR_1, 15, 13, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NONE, 0, TrainerTower_EventScript_SinglesTrainer, FLAG_TEMP_3
	object_event 4, OBJ_EVENT_GFX_VAR_2, 10, 16, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NONE, 0, TrainerTower_EventScript_KnockoutTrainer, FLAG_TEMP_4
	object_event 5, OBJ_EVENT_GFX_VAR_3, 11, 10, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, TrainerTower_EventScript_DoublesTrainer2, FLAG_TEMP_5

TrainerTower_7F_MapWarps:
	warp_def 15, 6, 3, 1, MAP_TRAINER_TOWER_8F
	warp_def 4, 6, 3, 0, MAP_TRAINER_TOWER_6F
	warp_def 13, 5, 0, 0, MAP_TRAINER_TOWER_ELEVATOR

TrainerTower_7F_MapCoordEvents:
	coord_event 10, 13, 3, VAR_TEMP_E, 0, TrainerTower_EventScript_SingleBattleTrigger
	coord_event 9, 12, 3, VAR_TEMP_F, 0, TrainerTower_EventScript_DoubleBattleTriggerTop
	coord_event 9, 13, 3, VAR_TEMP_F, 0, TrainerTower_EventScript_DoubleBattleTriggerBottom

TrainerTower_7F_MapEvents::
	map_events TrainerTower_7F_ObjectEvents, TrainerTower_7F_MapWarps, TrainerTower_7F_MapCoordEvents, NULL

@ ===== END data/maps/TrainerTower_7F/events.inc =====
@ ===== BEGIN data/maps/TrainerTower_8F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/TrainerTower_8F/map.json
@

	.align 2

TrainerTower_8F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_TRAINER_TOWER_DUDE, 9, 7, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, TrainerTower_EventScript_Owner, FLAG_TEMP_6
	object_event 2, OBJ_EVENT_GFX_VAR_0, 10, 10, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, TrainerTower_EventScript_DoublesTrainer1, FLAG_TEMP_2
	object_event 3, OBJ_EVENT_GFX_VAR_1, 15, 13, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NONE, 0, TrainerTower_EventScript_SinglesTrainer, FLAG_TEMP_3
	object_event 4, OBJ_EVENT_GFX_VAR_2, 10, 16, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NONE, 0, TrainerTower_EventScript_KnockoutTrainer, FLAG_TEMP_4
	object_event 5, OBJ_EVENT_GFX_VAR_3, 11, 10, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, TrainerTower_EventScript_DoublesTrainer2, FLAG_TEMP_5

TrainerTower_8F_MapWarps:
	warp_def 15, 6, 3, 1, MAP_TRAINER_TOWER_ROOF
	warp_def 4, 6, 3, 0, MAP_TRAINER_TOWER_7F
	warp_def 13, 5, 0, 0, MAP_TRAINER_TOWER_ELEVATOR

TrainerTower_8F_MapCoordEvents:
	coord_event 10, 13, 3, VAR_TEMP_E, 0, TrainerTower_EventScript_SingleBattleTrigger
	coord_event 9, 12, 3, VAR_TEMP_F, 0, TrainerTower_EventScript_DoubleBattleTriggerTop
	coord_event 9, 13, 3, VAR_TEMP_F, 0, TrainerTower_EventScript_DoubleBattleTriggerBottom

TrainerTower_8F_MapEvents::
	map_events TrainerTower_8F_ObjectEvents, TrainerTower_8F_MapWarps, TrainerTower_8F_MapCoordEvents, NULL

@ ===== END data/maps/TrainerTower_8F/events.inc =====
@ ===== BEGIN data/maps/TrainerTower_Roof/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/TrainerTower_Roof/map.json
@

	.align 2

TrainerTower_Roof_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_TRAINER_TOWER_DUDE, 9, 7, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, TrainerTower_EventScript_Owner, FLAG_TEMP_6

TrainerTower_Roof_MapWarps:
	warp_def 13, 5, 0, 0, MAP_TRAINER_TOWER_ELEVATOR
	warp_def 4, 6, 3, 0, MAP_TRAINER_TOWER_8F

TrainerTower_Roof_MapEvents::
	map_events TrainerTower_Roof_ObjectEvents, TrainerTower_Roof_MapWarps, NULL, NULL

@ ===== END data/maps/TrainerTower_Roof/events.inc =====
@ ===== BEGIN data/maps/TrainerTower_Lobby/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/TrainerTower_Lobby/map.json
@

	.align 2

TrainerTower_Lobby_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_NURSE, 4, 9, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, TrainerTower_Lobby_EventScript_Nurse, 0
	object_event 2, OBJ_EVENT_GFX_UNION_ROOM_RECEPTIONIST, 14, 9, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, TrainerTower_Lobby_EventScript_MartClerk, 0
	object_event 3, OBJ_EVENT_GFX_UNION_ROOM_RECEPTIONIST, 11, 7, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NONE, 0, TrainerTower_Lobby_EventScript_Receptionist, 0
	object_event 4, OBJ_EVENT_GFX_COOLTRAINER_F, 12, 13, 3, MOVEMENT_TYPE_WANDER_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, TrainerTower_Lobby_EventScript_CooltrainerF, 0
	object_event 5, OBJ_EVENT_GFX_BALDING_MAN, 2, 12, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, TrainerTower_Lobby_EventScript_BaldingMan, 0

TrainerTower_Lobby_MapWarps:
	warp_def 9, 2, 3, 1, MAP_TRAINER_TOWER_1F
	warp_def 9, 15, 3, 0, MAP_SEVEN_ISLAND_TRAINER_TOWER
	warp_def 17, 8, 0, 0, MAP_TRAINER_TOWER_ELEVATOR

TrainerTower_Lobby_MapCoordEvents:
	coord_event 9, 7, 3, VAR_MAP_SCENE_TRAINER_TOWER, 0, TrainerTower_Lobby_EventScript_EntryTrigger

TrainerTower_Lobby_MapBGEvents:
	bg_sign_event 8, 10, 0, BG_EVENT_PLAYER_FACING_NORTH, TrainerTower_Lobby_EventScript_ShowRecords

TrainerTower_Lobby_MapEvents::
	map_events TrainerTower_Lobby_ObjectEvents, TrainerTower_Lobby_MapWarps, TrainerTower_Lobby_MapCoordEvents, TrainerTower_Lobby_MapBGEvents

@ ===== END data/maps/TrainerTower_Lobby/events.inc =====
@ ===== BEGIN data/maps/TrainerTower_Elevator/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/TrainerTower_Elevator/map.json
@

	.align 2

TrainerTower_Elevator_MapWarps:
	warp_def 2, 5, 3, WARP_ID_DYNAMIC, MAP_DYNAMIC

TrainerTower_Elevator_MapBGEvents:
	bg_sign_event 0, 2, 0, BG_EVENT_PLAYER_FACING_ANY, TrainerTower_Elevator_EventScript_FloorSelect

TrainerTower_Elevator_MapEvents::
	map_events NULL, TrainerTower_Elevator_MapWarps, NULL, TrainerTower_Elevator_MapBGEvents

@ ===== END data/maps/TrainerTower_Elevator/events.inc =====
@ ===== BEGIN data/maps/FiveIsland_LostCave_Entrance/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FiveIsland_LostCave_Entrance/map.json
@

	.align 2

FiveIsland_LostCave_Entrance_MapWarps:
	warp_def 5, 8, 3, 0, MAP_FIVE_ISLAND_RESORT_GORGEOUS
	warp_def 5, 5, 3, 0, MAP_FIVE_ISLAND_LOST_CAVE_ROOM1

FiveIsland_LostCave_Entrance_MapEvents::
	map_events NULL, FiveIsland_LostCave_Entrance_MapWarps, NULL, NULL

@ ===== END data/maps/FiveIsland_LostCave_Entrance/events.inc =====
@ ===== BEGIN data/maps/FiveIsland_LostCave_Room1/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FiveIsland_LostCave_Room1/map.json
@

	.align 2

FiveIsland_LostCave_Room1_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_HIKER, 5, 4, 3, MOVEMENT_TYPE_WANDER_AROUND, 1, 1, TRAINER_TYPE_NORMAL, 1, FiveIsland_LostCave_Room1_EventScript_Lawson, 0

FiveIsland_LostCave_Room1_MapWarps:
	warp_def 8, 2, 3, 1, MAP_FIVE_ISLAND_LOST_CAVE_ENTRANCE
	warp_def 5, 1, 3, 3, MAP_FIVE_ISLAND_LOST_CAVE_ROOM1
	warp_def 8, 5, 3, 3, MAP_FIVE_ISLAND_LOST_CAVE_ROOM2
	warp_def 5, 8, 3, 1, MAP_FIVE_ISLAND_LOST_CAVE_ROOM1
	warp_def 2, 5, 3, 2, MAP_FIVE_ISLAND_LOST_CAVE_ROOM1

FiveIsland_LostCave_Room1_MapEvents::
	map_events FiveIsland_LostCave_Room1_ObjectEvents, FiveIsland_LostCave_Room1_MapWarps, NULL, NULL

@ ===== END data/maps/FiveIsland_LostCave_Room1/events.inc =====
@ ===== BEGIN data/maps/FiveIsland_LostCave_Room2/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FiveIsland_LostCave_Room2/map.json
@

	.align 2

FiveIsland_LostCave_Room2_MapWarps:
	warp_def 5, 1, 3, 2, MAP_FIVE_ISLAND_LOST_CAVE_ROOM3
	warp_def 8, 5, 3, 4, MAP_FIVE_ISLAND_LOST_CAVE_ROOM1
	warp_def 5, 8, 3, 0, MAP_FIVE_ISLAND_LOST_CAVE_ROOM11
	warp_def 2, 5, 3, 2, MAP_FIVE_ISLAND_LOST_CAVE_ROOM1

FiveIsland_LostCave_Room2_MapEvents::
	map_events NULL, FiveIsland_LostCave_Room2_MapWarps, NULL, NULL

@ ===== END data/maps/FiveIsland_LostCave_Room2/events.inc =====
@ ===== BEGIN data/maps/FiveIsland_LostCave_Room3/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FiveIsland_LostCave_Room3/map.json
@

	.align 2

FiveIsland_LostCave_Room3_MapWarps:
	warp_def 5, 1, 3, 3, MAP_FIVE_ISLAND_LOST_CAVE_ROOM1
	warp_def 8, 5, 3, 4, MAP_FIVE_ISLAND_LOST_CAVE_ROOM1
	warp_def 5, 8, 3, 0, MAP_FIVE_ISLAND_LOST_CAVE_ROOM4
	warp_def 2, 5, 3, 2, MAP_FIVE_ISLAND_LOST_CAVE_ROOM1

FiveIsland_LostCave_Room3_MapEvents::
	map_events NULL, FiveIsland_LostCave_Room3_MapWarps, NULL, NULL

@ ===== END data/maps/FiveIsland_LostCave_Room3/events.inc =====
@ ===== BEGIN data/maps/FiveIsland_LostCave_Room4/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FiveIsland_LostCave_Room4/map.json
@

	.align 2

FiveIsland_LostCave_Room4_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_WOMAN_1, 6, 4, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 1, FiveIsland_LostCave_Room4_EventScript_Laura, 0

FiveIsland_LostCave_Room4_MapWarps:
	warp_def 5, 1, 3, 0, MAP_FIVE_ISLAND_LOST_CAVE_ROOM12
	warp_def 8, 5, 3, 4, MAP_FIVE_ISLAND_LOST_CAVE_ROOM1
	warp_def 5, 8, 3, 0, MAP_FIVE_ISLAND_LOST_CAVE_ROOM5
	warp_def 2, 5, 3, 2, MAP_FIVE_ISLAND_LOST_CAVE_ROOM1

FiveIsland_LostCave_Room4_MapEvents::
	map_events FiveIsland_LostCave_Room4_ObjectEvents, FiveIsland_LostCave_Room4_MapWarps, NULL, NULL

@ ===== END data/maps/FiveIsland_LostCave_Room4/events.inc =====
@ ===== BEGIN data/maps/FiveIsland_LostCave_Room5/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FiveIsland_LostCave_Room5/map.json
@

	.align 2

FiveIsland_LostCave_Room5_MapWarps:
	warp_def 5, 1, 3, 3, MAP_FIVE_ISLAND_LOST_CAVE_ROOM1
	warp_def 8, 5, 3, 3, MAP_FIVE_ISLAND_LOST_CAVE_ROOM6
	warp_def 5, 8, 3, 1, MAP_FIVE_ISLAND_LOST_CAVE_ROOM1
	warp_def 2, 5, 3, 2, MAP_FIVE_ISLAND_LOST_CAVE_ROOM1

FiveIsland_LostCave_Room5_MapEvents::
	map_events NULL, FiveIsland_LostCave_Room5_MapWarps, NULL, NULL

@ ===== END data/maps/FiveIsland_LostCave_Room5/events.inc =====
@ ===== BEGIN data/maps/FiveIsland_LostCave_Room6/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FiveIsland_LostCave_Room6/map.json
@

	.align 2

FiveIsland_LostCave_Room6_MapWarps:
	warp_def 5, 1, 3, 3, MAP_FIVE_ISLAND_LOST_CAVE_ROOM1
	warp_def 8, 5, 3, 0, MAP_FIVE_ISLAND_LOST_CAVE_ROOM13
	warp_def 5, 8, 3, 1, MAP_FIVE_ISLAND_LOST_CAVE_ROOM1
	warp_def 2, 5, 3, 1, MAP_FIVE_ISLAND_LOST_CAVE_ROOM7

FiveIsland_LostCave_Room6_MapEvents::
	map_events NULL, FiveIsland_LostCave_Room6_MapWarps, NULL, NULL

@ ===== END data/maps/FiveIsland_LostCave_Room6/events.inc =====
@ ===== BEGIN data/maps/FiveIsland_LostCave_Room7/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FiveIsland_LostCave_Room7/map.json
@

	.align 2

FiveIsland_LostCave_Room7_MapWarps:
	warp_def 5, 1, 3, 3, MAP_FIVE_ISLAND_LOST_CAVE_ROOM1
	warp_def 8, 5, 3, 4, MAP_FIVE_ISLAND_LOST_CAVE_ROOM1
	warp_def 5, 8, 3, 0, MAP_FIVE_ISLAND_LOST_CAVE_ROOM8
	warp_def 2, 5, 3, 2, MAP_FIVE_ISLAND_LOST_CAVE_ROOM1

FiveIsland_LostCave_Room7_MapEvents::
	map_events NULL, FiveIsland_LostCave_Room7_MapWarps, NULL, NULL

@ ===== END data/maps/FiveIsland_LostCave_Room7/events.inc =====
@ ===== BEGIN data/maps/FiveIsland_LostCave_Room8/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FiveIsland_LostCave_Room8/map.json
@

	.align 2

FiveIsland_LostCave_Room8_MapWarps:
	warp_def 5, 1, 3, 3, MAP_FIVE_ISLAND_LOST_CAVE_ROOM1
	warp_def 8, 5, 3, 3, MAP_FIVE_ISLAND_LOST_CAVE_ROOM9
	warp_def 5, 8, 3, 1, MAP_FIVE_ISLAND_LOST_CAVE_ROOM1
	warp_def 2, 5, 3, 0, MAP_FIVE_ISLAND_LOST_CAVE_ROOM14

FiveIsland_LostCave_Room8_MapEvents::
	map_events NULL, FiveIsland_LostCave_Room8_MapWarps, NULL, NULL

@ ===== END data/maps/FiveIsland_LostCave_Room8/events.inc =====
@ ===== BEGIN data/maps/FiveIsland_LostCave_Room9/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FiveIsland_LostCave_Room9/map.json
@

	.align 2

FiveIsland_LostCave_Room9_MapWarps:
	warp_def 5, 1, 3, 0, MAP_FIVE_ISLAND_LOST_CAVE_ROOM10
	warp_def 8, 5, 3, 4, MAP_FIVE_ISLAND_LOST_CAVE_ROOM1
	warp_def 5, 8, 3, 1, MAP_FIVE_ISLAND_LOST_CAVE_ROOM1
	warp_def 2, 5, 3, 2, MAP_FIVE_ISLAND_LOST_CAVE_ROOM1

FiveIsland_LostCave_Room9_MapEvents::
	map_events NULL, FiveIsland_LostCave_Room9_MapWarps, NULL, NULL

@ ===== END data/maps/FiveIsland_LostCave_Room9/events.inc =====
@ ===== BEGIN data/maps/FiveIsland_LostCave_Room10/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FiveIsland_LostCave_Room10/map.json
@

	.align 2

FiveIsland_LostCave_Room10_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_WOMAN_2, 5, 5, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NONE, 0, 0x0, FLAG_HIDE_LOST_CAVE_SELPHY
	object_event 2, OBJ_EVENT_GFX_ITEM_BALL, 5, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, FiveIsland_LostCave_Room10_EventScript_ItemSilkScarf, FLAG_HIDE_FIVE_ISLAND_LOST_CAVE_ROOM10_SILK_SCARF

FiveIsland_LostCave_Room10_MapWarps:
	warp_def 5, 8, 3, 1, MAP_FIVE_ISLAND_LOST_CAVE_ROOM1

FiveIsland_LostCave_Room10_MapEvents::
	map_events FiveIsland_LostCave_Room10_ObjectEvents, FiveIsland_LostCave_Room10_MapWarps, NULL, NULL

@ ===== END data/maps/FiveIsland_LostCave_Room10/events.inc =====
@ ===== BEGIN data/maps/FiveIsland_LostCave_Room11/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FiveIsland_LostCave_Room11/map.json
@

	.align 2

FiveIsland_LostCave_Room11_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_ITEM_BALL, 5, 5, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, FiveIsland_LostCave_Room11_EventScript_ItemLaxIncense, FLAG_HIDE_FIVE_ISLAND_LOST_CAVE_ROOM11_LAX_INCENSE

FiveIsland_LostCave_Room11_MapWarps:
	warp_def 5, 1, 3, 3, MAP_FIVE_ISLAND_LOST_CAVE_ROOM1

FiveIsland_LostCave_Room11_MapEvents::
	map_events FiveIsland_LostCave_Room11_ObjectEvents, FiveIsland_LostCave_Room11_MapWarps, NULL, NULL

@ ===== END data/maps/FiveIsland_LostCave_Room11/events.inc =====
@ ===== BEGIN data/maps/FiveIsland_LostCave_Room12/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FiveIsland_LostCave_Room12/map.json
@

	.align 2

FiveIsland_LostCave_Room12_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_ITEM_BALL, 5, 5, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, FiveIsland_LostCave_Room12_EventScript_ItemSeaIncense, FLAG_HIDE_FIVE_ISLAND_LOST_CAVE_ROOM12_SEA_INCENSE

FiveIsland_LostCave_Room12_MapWarps:
	warp_def 5, 8, 3, 1, MAP_FIVE_ISLAND_LOST_CAVE_ROOM1

FiveIsland_LostCave_Room12_MapEvents::
	map_events FiveIsland_LostCave_Room12_ObjectEvents, FiveIsland_LostCave_Room12_MapWarps, NULL, NULL

@ ===== END data/maps/FiveIsland_LostCave_Room12/events.inc =====
@ ===== BEGIN data/maps/FiveIsland_LostCave_Room13/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FiveIsland_LostCave_Room13/map.json
@

	.align 2

FiveIsland_LostCave_Room13_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_ITEM_BALL, 5, 5, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, FiveIsland_LostCave_Room13_EventScript_ItemMaxRevive, FLAG_HIDE_FIVE_ISLAND_LOST_CAVE_ROOM13_MAX_REVIVE

FiveIsland_LostCave_Room13_MapWarps:
	warp_def 2, 5, 3, 2, MAP_FIVE_ISLAND_LOST_CAVE_ROOM1

FiveIsland_LostCave_Room13_MapEvents::
	map_events FiveIsland_LostCave_Room13_ObjectEvents, FiveIsland_LostCave_Room13_MapWarps, NULL, NULL

@ ===== END data/maps/FiveIsland_LostCave_Room13/events.inc =====
@ ===== BEGIN data/maps/FiveIsland_LostCave_Room14/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FiveIsland_LostCave_Room14/map.json
@

	.align 2

FiveIsland_LostCave_Room14_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_ITEM_BALL, 5, 5, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, FiveIsland_LostCave_Room14_EventScript_ItemRareCandy, FLAG_HIDE_FIVE_ISLAND_LOST_CAVE_ROOM14_RARE_CANDY

FiveIsland_LostCave_Room14_MapWarps:
	warp_def 8, 5, 3, 4, MAP_FIVE_ISLAND_LOST_CAVE_ROOM1

FiveIsland_LostCave_Room14_MapEvents::
	map_events FiveIsland_LostCave_Room14_ObjectEvents, FiveIsland_LostCave_Room14_MapWarps, NULL, NULL

@ ===== END data/maps/FiveIsland_LostCave_Room14/events.inc =====
@ ===== BEGIN data/maps/SevenIsland_TanobyRuins_MoneanChamber/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SevenIsland_TanobyRuins_MoneanChamber/map.json
@

	.align 2

SevenIsland_TanobyRuins_MoneanChamber_MapWarps:
	warp_def 11, 15, 3, 0, MAP_SEVEN_ISLAND_TANOBY_RUINS

SevenIsland_TanobyRuins_MoneanChamber_MapEvents::
	map_events NULL, SevenIsland_TanobyRuins_MoneanChamber_MapWarps, NULL, NULL

@ ===== END data/maps/SevenIsland_TanobyRuins_MoneanChamber/events.inc =====
@ ===== BEGIN data/maps/SevenIsland_TanobyRuins_LiptooChamber/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SevenIsland_TanobyRuins_LiptooChamber/map.json
@

	.align 2

SevenIsland_TanobyRuins_LiptooChamber_MapWarps:
	warp_def 11, 15, 3, 1, MAP_SEVEN_ISLAND_TANOBY_RUINS

SevenIsland_TanobyRuins_LiptooChamber_MapEvents::
	map_events NULL, SevenIsland_TanobyRuins_LiptooChamber_MapWarps, NULL, NULL

@ ===== END data/maps/SevenIsland_TanobyRuins_LiptooChamber/events.inc =====
@ ===== BEGIN data/maps/SevenIsland_TanobyRuins_WeepthChamber/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SevenIsland_TanobyRuins_WeepthChamber/map.json
@

	.align 2

SevenIsland_TanobyRuins_WeepthChamber_MapWarps:
	warp_def 11, 15, 3, 2, MAP_SEVEN_ISLAND_TANOBY_RUINS

SevenIsland_TanobyRuins_WeepthChamber_MapEvents::
	map_events NULL, SevenIsland_TanobyRuins_WeepthChamber_MapWarps, NULL, NULL

@ ===== END data/maps/SevenIsland_TanobyRuins_WeepthChamber/events.inc =====
@ ===== BEGIN data/maps/SevenIsland_TanobyRuins_DilfordChamber/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SevenIsland_TanobyRuins_DilfordChamber/map.json
@

	.align 2

SevenIsland_TanobyRuins_DilfordChamber_MapWarps:
	warp_def 11, 15, 3, 3, MAP_SEVEN_ISLAND_TANOBY_RUINS

SevenIsland_TanobyRuins_DilfordChamber_MapEvents::
	map_events NULL, SevenIsland_TanobyRuins_DilfordChamber_MapWarps, NULL, NULL

@ ===== END data/maps/SevenIsland_TanobyRuins_DilfordChamber/events.inc =====
@ ===== BEGIN data/maps/SevenIsland_TanobyRuins_ScufibChamber/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SevenIsland_TanobyRuins_ScufibChamber/map.json
@

	.align 2

SevenIsland_TanobyRuins_ScufibChamber_MapWarps:
	warp_def 11, 15, 3, 4, MAP_SEVEN_ISLAND_TANOBY_RUINS

SevenIsland_TanobyRuins_ScufibChamber_MapEvents::
	map_events NULL, SevenIsland_TanobyRuins_ScufibChamber_MapWarps, NULL, NULL

@ ===== END data/maps/SevenIsland_TanobyRuins_ScufibChamber/events.inc =====
@ ===== BEGIN data/maps/SevenIsland_TanobyRuins_RixyChamber/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SevenIsland_TanobyRuins_RixyChamber/map.json
@

	.align 2

SevenIsland_TanobyRuins_RixyChamber_MapWarps:
	warp_def 11, 15, 3, 5, MAP_SEVEN_ISLAND_TANOBY_RUINS

SevenIsland_TanobyRuins_RixyChamber_MapEvents::
	map_events NULL, SevenIsland_TanobyRuins_RixyChamber_MapWarps, NULL, NULL

@ ===== END data/maps/SevenIsland_TanobyRuins_RixyChamber/events.inc =====
@ ===== BEGIN data/maps/SevenIsland_TanobyRuins_ViapoisChamber/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SevenIsland_TanobyRuins_ViapoisChamber/map.json
@

	.align 2

SevenIsland_TanobyRuins_ViapoisChamber_MapWarps:
	warp_def 11, 15, 3, 6, MAP_SEVEN_ISLAND_TANOBY_RUINS

SevenIsland_TanobyRuins_ViapoisChamber_MapEvents::
	map_events NULL, SevenIsland_TanobyRuins_ViapoisChamber_MapWarps, NULL, NULL

@ ===== END data/maps/SevenIsland_TanobyRuins_ViapoisChamber/events.inc =====
@ ===== BEGIN data/maps/ThreeIsland_DunsparceTunnel/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/ThreeIsland_DunsparceTunnel/map.json
@

	.align 2

ThreeIsland_DunsparceTunnel_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_FAT_MAN, 23, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, ThreeIsland_DunsparceTunnel_EventScript_Prospector, 0

ThreeIsland_DunsparceTunnel_MapWarps:
	warp_def 3, 4, 3, 0, MAP_THREE_ISLAND_PORT
	warp_def 25, 5, 3, 1, MAP_THREE_ISLAND_PORT

ThreeIsland_DunsparceTunnel_MapBGEvents:
	bg_hidden_item_event 21, 3, 0, ITEM_NUGGET, FLAG_HIDDEN_ITEM_THREE_ISLAND_DUNSPARCE_TUNNEL_NUGGET, 1, FALSE

ThreeIsland_DunsparceTunnel_MapEvents::
	map_events ThreeIsland_DunsparceTunnel_ObjectEvents, ThreeIsland_DunsparceTunnel_MapWarps, NULL, ThreeIsland_DunsparceTunnel_MapBGEvents

@ ===== END data/maps/ThreeIsland_DunsparceTunnel/events.inc =====
@ ===== BEGIN data/maps/SevenIsland_SevaultCanyon_TanobyKey/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SevenIsland_SevaultCanyon_TanobyKey/map.json
@

	.align 2

SevenIsland_SevaultCanyon_TanobyKey_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_PUSHABLE_BOULDER, 7, 6, 3, MOVEMENT_TYPE_LOOK_AROUND, 0, 0, TRAINER_TYPE_NONE, 0, EventScript_StrengthBoulder, 0
	object_event 2, OBJ_EVENT_GFX_PUSHABLE_BOULDER, 8, 6, 3, MOVEMENT_TYPE_LOOK_AROUND, 0, 0, TRAINER_TYPE_NONE, 0, EventScript_StrengthBoulder, 0
	object_event 3, OBJ_EVENT_GFX_PUSHABLE_BOULDER, 8, 9, 3, MOVEMENT_TYPE_LOOK_AROUND, 0, 0, TRAINER_TYPE_NONE, 0, EventScript_StrengthBoulder, 0
	object_event 4, OBJ_EVENT_GFX_PUSHABLE_BOULDER, 6, 10, 3, MOVEMENT_TYPE_LOOK_AROUND, 0, 0, TRAINER_TYPE_NONE, 0, EventScript_StrengthBoulder, 0
	object_event 5, OBJ_EVENT_GFX_PUSHABLE_BOULDER, 8, 10, 3, MOVEMENT_TYPE_LOOK_AROUND, 0, 0, TRAINER_TYPE_NONE, 0, EventScript_StrengthBoulder, 0
	object_event 6, OBJ_EVENT_GFX_PUSHABLE_BOULDER, 6, 9, 3, MOVEMENT_TYPE_LOOK_AROUND, 0, 0, TRAINER_TYPE_NONE, 0, EventScript_StrengthBoulder, 0
	object_event 7, OBJ_EVENT_GFX_PUSHABLE_BOULDER, 6, 6, 3, MOVEMENT_TYPE_LOOK_AROUND, 0, 0, TRAINER_TYPE_NONE, 0, EventScript_StrengthBoulder, 0

SevenIsland_SevaultCanyon_TanobyKey_MapWarps:
	warp_def 7, 13, 3, 0, MAP_SEVEN_ISLAND_SEVAULT_CANYON

SevenIsland_SevaultCanyon_TanobyKey_MapCoordEvents:
	coord_event 7, 2, 3, VAR_TEMP_1, 99, SevenIsland_SevaultCanyon_TanobyKey_EventScript_Switch1
	coord_event 9, 8, 3, VAR_TEMP_7, 99, SevenIsland_SevaultCanyon_TanobyKey_EventScript_Switch7
	coord_event 5, 8, 3, VAR_TEMP_6, 99, SevenIsland_SevaultCanyon_TanobyKey_EventScript_Switch6
	coord_event 9, 6, 3, VAR_TEMP_5, 99, SevenIsland_SevaultCanyon_TanobyKey_EventScript_Switch5
	coord_event 5, 6, 3, VAR_TEMP_4, 99, SevenIsland_SevaultCanyon_TanobyKey_EventScript_Switch4
	coord_event 10, 4, 3, VAR_TEMP_3, 99, SevenIsland_SevaultCanyon_TanobyKey_EventScript_Switch3
	coord_event 4, 4, 3, VAR_TEMP_2, 99, SevenIsland_SevaultCanyon_TanobyKey_EventScript_Switch2

SevenIsland_SevaultCanyon_TanobyKey_MapEvents::
	map_events SevenIsland_SevaultCanyon_TanobyKey_ObjectEvents, SevenIsland_SevaultCanyon_TanobyKey_MapWarps, SevenIsland_SevaultCanyon_TanobyKey_MapCoordEvents, NULL

@ ===== END data/maps/SevenIsland_SevaultCanyon_TanobyKey/events.inc =====
@ ===== BEGIN data/maps/NavelRock_1F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/NavelRock_1F/map.json
@

	.align 2

NavelRock_1F_MapWarps:
	warp_def 8, 4, 3, 0, MAP_NAVEL_ROCK_B1F
	warp_def 8, 23, 3, 0, MAP_NAVEL_ROCK_EXTERIOR

NavelRock_1F_MapEvents::
	map_events NULL, NavelRock_1F_MapWarps, NULL, NULL

@ ===== END data/maps/NavelRock_1F/events.inc =====
@ ===== BEGIN data/maps/NavelRock_Summit/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/NavelRock_Summit/map.json
@

	.align 2

NavelRock_Summit_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_HO_OH, 9, 6, 0, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, 0x0, FLAG_HIDE_HO_OH

NavelRock_Summit_MapWarps:
	warp_def 10, 18, 3, 1, MAP_NAVEL_ROCK_SUMMIT_PATH_5F

NavelRock_Summit_MapCoordEvents:
	coord_event 9, 12, 3, VAR_TEMP_1, 0, NavelRock_Summit_EventScript_HoOh

NavelRock_Summit_MapBGEvents:
	bg_hidden_item_event 9, 11, 3, ITEM_SACRED_ASH, FLAG_HIDDEN_ITEM_NAVEL_ROCK_SUMMIT_SACRED_ASH, 1, TRUE

NavelRock_Summit_MapEvents::
	map_events NavelRock_Summit_ObjectEvents, NavelRock_Summit_MapWarps, NavelRock_Summit_MapCoordEvents, NavelRock_Summit_MapBGEvents

@ ===== END data/maps/NavelRock_Summit/events.inc =====
@ ===== BEGIN data/maps/NavelRock_Base/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/NavelRock_Base/map.json
@

	.align 2

NavelRock_Base_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_LUGIA, 10, 15, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, NavelRock_Base_EventScript_Lugia, FLAG_HIDE_LUGIA

NavelRock_Base_MapWarps:
	warp_def 13, 20, 3, 1, MAP_NAVEL_ROCK_BASE_PATH_B11F

NavelRock_Base_MapEvents::
	map_events NavelRock_Base_ObjectEvents, NavelRock_Base_MapWarps, NULL, NULL

@ ===== END data/maps/NavelRock_Base/events.inc =====
@ ===== BEGIN data/maps/NavelRock_SummitPath_2F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/NavelRock_SummitPath_2F/map.json
@

	.align 2

NavelRock_SummitPath_2F_MapWarps:
	warp_def 4, 4, 3, 1, MAP_NAVEL_ROCK_FORK
	warp_def 2, 2, 3, 0, MAP_NAVEL_ROCK_SUMMIT_PATH_3F

NavelRock_SummitPath_2F_MapEvents::
	map_events NULL, NavelRock_SummitPath_2F_MapWarps, NULL, NULL

@ ===== END data/maps/NavelRock_SummitPath_2F/events.inc =====
@ ===== BEGIN data/maps/NavelRock_SummitPath_3F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/NavelRock_SummitPath_3F/map.json
@

	.align 2

NavelRock_SummitPath_3F_MapWarps:
	warp_def 2, 2, 3, 1, MAP_NAVEL_ROCK_SUMMIT_PATH_2F
	warp_def 4, 4, 3, 0, MAP_NAVEL_ROCK_SUMMIT_PATH_4F

NavelRock_SummitPath_3F_MapEvents::
	map_events NULL, NavelRock_SummitPath_3F_MapWarps, NULL, NULL

@ ===== END data/maps/NavelRock_SummitPath_3F/events.inc =====
@ ===== BEGIN data/maps/NavelRock_SummitPath_4F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/NavelRock_SummitPath_4F/map.json
@

	.align 2

NavelRock_SummitPath_4F_MapWarps:
	warp_def 4, 4, 3, 1, MAP_NAVEL_ROCK_SUMMIT_PATH_3F
	warp_def 2, 2, 3, 0, MAP_NAVEL_ROCK_SUMMIT_PATH_5F

NavelRock_SummitPath_4F_MapEvents::
	map_events NULL, NavelRock_SummitPath_4F_MapWarps, NULL, NULL

@ ===== END data/maps/NavelRock_SummitPath_4F/events.inc =====
@ ===== BEGIN data/maps/NavelRock_SummitPath_5F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/NavelRock_SummitPath_5F/map.json
@

	.align 2

NavelRock_SummitPath_5F_MapWarps:
	warp_def 2, 2, 3, 1, MAP_NAVEL_ROCK_SUMMIT_PATH_4F
	warp_def 4, 4, 3, 0, MAP_NAVEL_ROCK_SUMMIT

NavelRock_SummitPath_5F_MapEvents::
	map_events NULL, NavelRock_SummitPath_5F_MapWarps, NULL, NULL

@ ===== END data/maps/NavelRock_SummitPath_5F/events.inc =====
@ ===== BEGIN data/maps/NavelRock_BasePath_B1F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/NavelRock_BasePath_B1F/map.json
@

	.align 2

NavelRock_BasePath_B1F_MapWarps:
	warp_def 2, 2, 3, 2, MAP_NAVEL_ROCK_FORK
	warp_def 4, 4, 3, 0, MAP_NAVEL_ROCK_BASE_PATH_B2F

NavelRock_BasePath_B1F_MapEvents::
	map_events NULL, NavelRock_BasePath_B1F_MapWarps, NULL, NULL

@ ===== END data/maps/NavelRock_BasePath_B1F/events.inc =====
@ ===== BEGIN data/maps/NavelRock_BasePath_B2F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/NavelRock_BasePath_B2F/map.json
@

	.align 2

NavelRock_BasePath_B2F_MapWarps:
	warp_def 4, 4, 3, 1, MAP_NAVEL_ROCK_BASE_PATH_B1F
	warp_def 2, 2, 3, 0, MAP_NAVEL_ROCK_BASE_PATH_B3F

NavelRock_BasePath_B2F_MapEvents::
	map_events NULL, NavelRock_BasePath_B2F_MapWarps, NULL, NULL

@ ===== END data/maps/NavelRock_BasePath_B2F/events.inc =====
@ ===== BEGIN data/maps/NavelRock_BasePath_B3F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/NavelRock_BasePath_B3F/map.json
@

	.align 2

NavelRock_BasePath_B3F_MapWarps:
	warp_def 2, 2, 3, 1, MAP_NAVEL_ROCK_BASE_PATH_B2F
	warp_def 4, 4, 3, 0, MAP_NAVEL_ROCK_BASE_PATH_B4F

NavelRock_BasePath_B3F_MapEvents::
	map_events NULL, NavelRock_BasePath_B3F_MapWarps, NULL, NULL

@ ===== END data/maps/NavelRock_BasePath_B3F/events.inc =====
@ ===== BEGIN data/maps/NavelRock_BasePath_B4F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/NavelRock_BasePath_B4F/map.json
@

	.align 2

NavelRock_BasePath_B4F_MapWarps:
	warp_def 4, 4, 3, 1, MAP_NAVEL_ROCK_BASE_PATH_B3F
	warp_def 2, 2, 3, 0, MAP_NAVEL_ROCK_BASE_PATH_B5F

NavelRock_BasePath_B4F_MapEvents::
	map_events NULL, NavelRock_BasePath_B4F_MapWarps, NULL, NULL

@ ===== END data/maps/NavelRock_BasePath_B4F/events.inc =====
@ ===== BEGIN data/maps/NavelRock_BasePath_B5F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/NavelRock_BasePath_B5F/map.json
@

	.align 2

NavelRock_BasePath_B5F_MapWarps:
	warp_def 2, 2, 3, 1, MAP_NAVEL_ROCK_BASE_PATH_B4F
	warp_def 4, 4, 3, 0, MAP_NAVEL_ROCK_BASE_PATH_B6F

NavelRock_BasePath_B5F_MapEvents::
	map_events NULL, NavelRock_BasePath_B5F_MapWarps, NULL, NULL

@ ===== END data/maps/NavelRock_BasePath_B5F/events.inc =====
@ ===== BEGIN data/maps/NavelRock_BasePath_B6F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/NavelRock_BasePath_B6F/map.json
@

	.align 2

NavelRock_BasePath_B6F_MapWarps:
	warp_def 4, 4, 3, 1, MAP_NAVEL_ROCK_BASE_PATH_B5F
	warp_def 2, 2, 3, 0, MAP_NAVEL_ROCK_BASE_PATH_B7F

NavelRock_BasePath_B6F_MapEvents::
	map_events NULL, NavelRock_BasePath_B6F_MapWarps, NULL, NULL

@ ===== END data/maps/NavelRock_BasePath_B6F/events.inc =====
@ ===== BEGIN data/maps/NavelRock_BasePath_B7F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/NavelRock_BasePath_B7F/map.json
@

	.align 2

NavelRock_BasePath_B7F_MapWarps:
	warp_def 2, 2, 3, 1, MAP_NAVEL_ROCK_BASE_PATH_B6F
	warp_def 4, 4, 3, 0, MAP_NAVEL_ROCK_BASE_PATH_B8F

NavelRock_BasePath_B7F_MapEvents::
	map_events NULL, NavelRock_BasePath_B7F_MapWarps, NULL, NULL

@ ===== END data/maps/NavelRock_BasePath_B7F/events.inc =====
@ ===== BEGIN data/maps/NavelRock_BasePath_B8F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/NavelRock_BasePath_B8F/map.json
@

	.align 2

NavelRock_BasePath_B8F_MapWarps:
	warp_def 4, 4, 3, 1, MAP_NAVEL_ROCK_BASE_PATH_B7F
	warp_def 2, 2, 3, 0, MAP_NAVEL_ROCK_BASE_PATH_B9F

NavelRock_BasePath_B8F_MapEvents::
	map_events NULL, NavelRock_BasePath_B8F_MapWarps, NULL, NULL

@ ===== END data/maps/NavelRock_BasePath_B8F/events.inc =====
@ ===== BEGIN data/maps/NavelRock_BasePath_B9F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/NavelRock_BasePath_B9F/map.json
@

	.align 2

NavelRock_BasePath_B9F_MapWarps:
	warp_def 2, 2, 3, 1, MAP_NAVEL_ROCK_BASE_PATH_B8F
	warp_def 4, 4, 3, 0, MAP_NAVEL_ROCK_BASE_PATH_B10F

NavelRock_BasePath_B9F_MapEvents::
	map_events NULL, NavelRock_BasePath_B9F_MapWarps, NULL, NULL

@ ===== END data/maps/NavelRock_BasePath_B9F/events.inc =====
@ ===== BEGIN data/maps/NavelRock_BasePath_B10F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/NavelRock_BasePath_B10F/map.json
@

	.align 2

NavelRock_BasePath_B10F_MapWarps:
	warp_def 4, 4, 3, 1, MAP_NAVEL_ROCK_BASE_PATH_B9F
	warp_def 2, 2, 3, 0, MAP_NAVEL_ROCK_BASE_PATH_B11F

NavelRock_BasePath_B10F_MapEvents::
	map_events NULL, NavelRock_BasePath_B10F_MapWarps, NULL, NULL

@ ===== END data/maps/NavelRock_BasePath_B10F/events.inc =====
@ ===== BEGIN data/maps/NavelRock_BasePath_B11F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/NavelRock_BasePath_B11F/map.json
@

	.align 2

NavelRock_BasePath_B11F_MapWarps:
	warp_def 2, 2, 3, 1, MAP_NAVEL_ROCK_BASE_PATH_B10F
	warp_def 4, 4, 3, 0, MAP_NAVEL_ROCK_BASE

NavelRock_BasePath_B11F_MapEvents::
	map_events NULL, NavelRock_BasePath_B11F_MapWarps, NULL, NULL

@ ===== END data/maps/NavelRock_BasePath_B11F/events.inc =====
@ ===== BEGIN data/maps/NavelRock_B1F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/NavelRock_B1F/map.json
@

	.align 2

NavelRock_B1F_MapWarps:
	warp_def 4, 2, 3, 0, MAP_NAVEL_ROCK_1F
	warp_def 11, 5, 3, 0, MAP_NAVEL_ROCK_FORK

NavelRock_B1F_MapEvents::
	map_events NULL, NavelRock_B1F_MapWarps, NULL, NULL

@ ===== END data/maps/NavelRock_B1F/events.inc =====
@ ===== BEGIN data/maps/NavelRock_Fork/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/NavelRock_Fork/map.json
@

	.align 2

NavelRock_Fork_MapWarps:
	warp_def 13, 95, 3, 1, MAP_NAVEL_ROCK_B1F
	warp_def 3, 1, 3, 0, MAP_NAVEL_ROCK_SUMMIT_PATH_2F
	warp_def 26, 1, 3, 0, MAP_NAVEL_ROCK_BASE_PATH_B1F

NavelRock_Fork_MapEvents::
	map_events NULL, NavelRock_Fork_MapWarps, NULL, NULL

@ ===== END data/maps/NavelRock_Fork/events.inc =====
@ ===== BEGIN data/maps/BirthIsland_Exterior/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/BirthIsland_Exterior/map.json
@

	.align 2

BirthIsland_Exterior_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_METEORITE, 15, 12, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, BirthIsland_Exterior_EventScript_Triangle, FLAG_HIDE_BIRTH_ISLAND_METEORITE
	object_event 2, OBJ_EVENT_GFX_VAR_0, 15, 3, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, 0x0, FLAG_HIDE_DEOXYS

BirthIsland_Exterior_MapWarps:
	warp_def 15, 24, 3, 0, MAP_BIRTH_ISLAND_HARBOR

BirthIsland_Exterior_MapEvents::
	map_events BirthIsland_Exterior_ObjectEvents, BirthIsland_Exterior_MapWarps, NULL, NULL

@ ===== END data/maps/BirthIsland_Exterior/events.inc =====
@ ===== BEGIN data/maps/OneIsland_KindleRoad_EmberSpa/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/OneIsland_KindleRoad_EmberSpa/map.json
@

	.align 2

OneIsland_KindleRoad_EmberSpa_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_OLD_MAN_1, 11, 13, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, OneIsland_KindleRoad_EmberSpa_EventScript_OldMan, 0
	object_event 2, OBJ_EVENT_GFX_BALDING_MAN, 15, 11, 3, MOVEMENT_TYPE_FACE_DOWN_AND_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, OneIsland_KindleRoad_EmberSpa_EventScript_BaldingMan1, 0
	object_event 3, OBJ_EVENT_GFX_BLACK_BELT, 6, 8, 3, MOVEMENT_TYPE_WANDER_LEFT_AND_RIGHT, 2, 1, TRAINER_TYPE_NONE, 0, OneIsland_KindleRoad_EmberSpa_EventScript_BlackBelt, FLAG_HIDE_POSTGAME_GOSSIPERS
	object_event 4, OBJ_EVENT_GFX_OLD_WOMAN, 20, 7, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, OneIsland_KindleRoad_EmberSpa_EventScript_OldWoman, 0
	object_event 5, OBJ_EVENT_GFX_OLD_MAN_1, 10, 5, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, OneIsland_KindleRoad_EmberSpa_EventScript_RockSmashMan, 0
	object_event 6, OBJ_EVENT_GFX_BALDING_MAN, 11, 20, 3, MOVEMENT_TYPE_WANDER_LEFT_AND_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, OneIsland_KindleRoad_EmberSpa_EventScript_BaldingMan2, 0

OneIsland_KindleRoad_EmberSpa_MapWarps:
	warp_def 13, 36, 3, 2, MAP_ONE_ISLAND_KINDLE_ROAD

OneIsland_KindleRoad_EmberSpa_MapCoordEvents:
	coord_event 13, 13, 3, VAR_TEMP_1, 0, OneIsland_KindleRoad_EmberSpa_EventScript_SpaHeal

OneIsland_KindleRoad_EmberSpa_MapEvents::
	map_events OneIsland_KindleRoad_EmberSpa_ObjectEvents, OneIsland_KindleRoad_EmberSpa_MapWarps, OneIsland_KindleRoad_EmberSpa_MapCoordEvents, NULL

@ ===== END data/maps/OneIsland_KindleRoad_EmberSpa/events.inc =====
@ ===== BEGIN data/maps/BirthIsland_Harbor/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/BirthIsland_Harbor/map.json
@

	.align 2

BirthIsland_Harbor_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_SEAGALLOP, 8, 9, 0, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, 0x0, 0
	object_event 2, OBJ_EVENT_GFX_SAILOR, 8, 6, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NONE, 0, BirthIsland_Harbor_EventScript_Sailor, 0

BirthIsland_Harbor_MapWarps:
	warp_def 8, 2, 3, 0, MAP_BIRTH_ISLAND_EXTERIOR

BirthIsland_Harbor_MapEvents::
	map_events BirthIsland_Harbor_ObjectEvents, BirthIsland_Harbor_MapWarps, NULL, NULL

@ ===== END data/maps/BirthIsland_Harbor/events.inc =====
@ ===== BEGIN data/maps/NavelRock_Harbor/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/NavelRock_Harbor/map.json
@

	.align 2

NavelRock_Harbor_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_SEAGALLOP, 8, 9, 0, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, 0x0, 0
	object_event 2, OBJ_EVENT_GFX_SAILOR, 8, 6, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NONE, 0, NavelRock_Harbor_EventScript_Sailor, 0

NavelRock_Harbor_MapWarps:
	warp_def 8, 2, 3, 1, MAP_NAVEL_ROCK_EXTERIOR

NavelRock_Harbor_MapEvents::
	map_events NavelRock_Harbor_ObjectEvents, NavelRock_Harbor_MapWarps, NULL, NULL

@ ===== END data/maps/NavelRock_Harbor/events.inc =====
@ ===== BEGIN data/maps/PalletTown/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/PalletTown/map.json
@

	.align 2

PalletTown_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_WOMAN_1, 3, 10, 3, MOVEMENT_TYPE_WANDER_AROUND, 1, 4, TRAINER_TYPE_NONE, 0, PalletTown_EventScript_SignLady, 0
	object_event 2, OBJ_EVENT_GFX_FAT_MAN, 13, 17, 3, MOVEMENT_TYPE_WANDER_AROUND, 6, 2, TRAINER_TYPE_NONE, 0, PalletTown_EventScript_FatMan, 0
	object_event 3, OBJ_EVENT_GFX_PROF_OAK, 10, 8, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NONE, 0, 0x0, FLAG_HIDE_OAK_IN_PALLET_TOWN

PalletTown_MapWarps:
	warp_def 6, 7, 0, 1, MAP_PALLET_TOWN_PLAYERS_HOUSE_1F
	warp_def 15, 7, 0, 0, MAP_PALLET_TOWN_RIVALS_HOUSE
	warp_def 16, 13, 0, 0, MAP_PALLET_TOWN_PROFESSOR_OAKS_LAB

PalletTown_MapCoordEvents:
	coord_event 12, 1, 3, VAR_MAP_SCENE_PALLET_TOWN_OAK, 0, PalletTown_EventScript_OakTriggerLeft
	coord_event 13, 1, 3, VAR_MAP_SCENE_PALLET_TOWN_OAK, 0, PalletTown_EventScript_OakTriggerRight
	coord_event 13, 2, 3, VAR_TEMP_2, 1, PalletTown_EventScript_SignLadyTrigger

PalletTown_MapBGEvents:
	bg_sign_event 16, 16, 0, BG_EVENT_PLAYER_FACING_ANY, PalletTown_EventScript_OaksLabSign
	bg_sign_event 4, 7, 0, BG_EVENT_PLAYER_FACING_ANY, PalletTown_EventScript_PlayersHouseSign
	bg_sign_event 13, 7, 0, BG_EVENT_PLAYER_FACING_ANY, PalletTown_EventScript_RivalsHouseSign
	bg_sign_event 9, 11, 0, BG_EVENT_PLAYER_FACING_ANY, PalletTown_EventScript_TownSign
	bg_sign_event 5, 14, 0, BG_EVENT_PLAYER_FACING_ANY, PalletTown_EventScript_TrainerTips

PalletTown_MapEvents::
	map_events PalletTown_ObjectEvents, PalletTown_MapWarps, PalletTown_MapCoordEvents, PalletTown_MapBGEvents

@ ===== END data/maps/PalletTown/events.inc =====
@ ===== BEGIN data/maps/ViridianCity/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/ViridianCity/map.json
@

	.align 2

ViridianCity_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_FAT_MAN, 8, 26, 3, MOVEMENT_TYPE_FACE_DOWN, 0, 0, TRAINER_TYPE_NONE, 0, ViridianCity_EventScript_DreamEaterTutor, 0
	object_event 2, OBJ_EVENT_GFX_CUT_TREE, 11, 24, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_CutTree, FLAG_TEMP_11
	object_event 3, OBJ_EVENT_GFX_OLD_MAN_1, 34, 11, 3, MOVEMENT_TYPE_FACE_UP, 0, 0, TRAINER_TYPE_NONE, 0, ViridianCity_EventScript_OldMan, 0
	object_event 4, OBJ_EVENT_GFX_VAR_0, 21, 6, 3, MOVEMENT_TYPE_LOOK_AROUND, 2, 3, TRAINER_TYPE_NONE, 0, ViridianCity_EventScript_TutorialOldMan, 0
	object_event 5, OBJ_EVENT_GFX_WOMAN_3, 20, 12, 3, MOVEMENT_TYPE_FACE_UP, 1, 3, TRAINER_TYPE_NONE, 0, ViridianCity_EventScript_Woman, 0
	object_event 6, OBJ_EVENT_GFX_YOUNGSTER, 33, 26, 3, MOVEMENT_TYPE_WANDER_UP_AND_DOWN, 0, 2, TRAINER_TYPE_NONE, 0, ViridianCity_EventScript_Youngster, 0
	object_event 7, OBJ_EVENT_GFX_BOY, 16, 22, 3, MOVEMENT_TYPE_WANDER_AROUND, 1, 2, TRAINER_TYPE_NONE, 0, ViridianCity_EventScript_Boy, 0
	object_event 8, OBJ_EVENT_GFX_CUT_TREE, 18, 5, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_CutTree, FLAG_TEMP_12
	object_event 9, OBJ_EVENT_GFX_ITEM_BALL, 17, 5, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, ViridianCity_EventScript_ItemPotion, FLAG_HIDE_VIRIDIAN_CITY_POTION

ViridianCity_MapWarps:
	warp_def 26, 26, 0, 1, MAP_VIRIDIAN_CITY_POKEMON_CENTER_1F
	warp_def 25, 11, 3, 1, MAP_VIRIDIAN_CITY_HOUSE
	warp_def 36, 10, 0, 1, MAP_VIRIDIAN_CITY_GYM
	warp_def 25, 18, 0, 1, MAP_VIRIDIAN_CITY_SCHOOL
	warp_def 36, 19, 0, 1, MAP_VIRIDIAN_CITY_MART

ViridianCity_MapCoordEvents:
	coord_event 22, 11, 3, VAR_MAP_SCENE_VIRIDIAN_CITY_OLD_MAN, 0, ViridianCity_EventScript_RoadBlocked
	coord_event 36, 11, 3, VAR_MAP_SCENE_VIRIDIAN_CITY_GYM_DOOR, 0, ViridianCity_EventScript_GymDoorLocked
	coord_event 20, 8, 3, VAR_MAP_SCENE_VIRIDIAN_CITY_OLD_MAN, 1, ViridianCity_EventScript_TutorialTriggerLeft
	coord_event 22, 8, 3, VAR_MAP_SCENE_VIRIDIAN_CITY_OLD_MAN, 1, ViridianCity_EventScript_TutorialTriggerRight

ViridianCity_MapBGEvents:
	bg_sign_event 23, 1, 3, BG_EVENT_PLAYER_FACING_ANY, ViridianCity_EventScript_TrainerTips1
	bg_sign_event 32, 10, 0, BG_EVENT_PLAYER_FACING_ANY, ViridianCity_EventScript_GymSign
	bg_sign_event 20, 31, 0, BG_EVENT_PLAYER_FACING_ANY, ViridianCity_EventScript_TrainerTips2
	bg_sign_event 20, 16, 0, BG_EVENT_PLAYER_FACING_ANY, ViridianCity_EventScript_CitySign
	bg_sign_event 36, 10, 0, BG_EVENT_PLAYER_FACING_ANY, ViridianCity_EventScript_GymDoor

ViridianCity_MapEvents::
	map_events ViridianCity_ObjectEvents, ViridianCity_MapWarps, ViridianCity_MapCoordEvents, ViridianCity_MapBGEvents

@ ===== END data/maps/ViridianCity/events.inc =====
@ ===== BEGIN data/maps/PewterCity/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/PewterCity/map.json
@

	.align 2

PewterCity_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_LASS, 6, 15, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, PewterCity_EventScript_Lass, 0
	object_event 2, OBJ_EVENT_GFX_MAN, 33, 17, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, PewterCity_EventScript_MuseumGuide, FLAG_HIDE_PEWTER_MUSEUM_GUIDE
	object_event 3, OBJ_EVENT_GFX_FAT_MAN, 21, 28, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, PewterCity_EventScript_FatMan, 0
	object_event 4, OBJ_EVENT_GFX_BUG_CATCHER, 33, 27, 3, MOVEMENT_TYPE_WANDER_LEFT_AND_RIGHT, 2, 1, TRAINER_TYPE_NONE, 0, PewterCity_EventScript_BugCatcher, 0
	object_event 5, OBJ_EVENT_GFX_BOY, 42, 20, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, PewterCity_EventScript_GymGuide, FLAG_HIDE_PEWTER_CITY_GYM_GUIDE
	object_event 6, OBJ_EVENT_GFX_CUT_TREE, 30, 5, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_CutTree, FLAG_TEMP_12
	object_event 7, OBJ_EVENT_GFX_SCIENTIST, 46, 20, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, PewterCity_EventScript_RunningShoesAide, FLAG_HIDE_PEWTER_CITY_RUNNING_SHOES_GUY

PewterCity_MapWarps:
	warp_def 17, 6, 0, 1, MAP_PEWTER_CITY_MUSEUM_1F
	warp_def 25, 4, 0, 3, MAP_PEWTER_CITY_MUSEUM_1F
	warp_def 15, 16, 0, 1, MAP_PEWTER_CITY_GYM
	warp_def 28, 18, 0, 1, MAP_PEWTER_CITY_MART
	warp_def 33, 11, 0, 1, MAP_PEWTER_CITY_HOUSE1
	warp_def 17, 25, 0, 1, MAP_PEWTER_CITY_POKEMON_CENTER_1F
	warp_def 9, 30, 0, 1, MAP_PEWTER_CITY_HOUSE2

PewterCity_MapCoordEvents:
	coord_event 42, 21, 3, VAR_MAP_SCENE_PEWTER_CITY, 0, PewterCity_EventScript_GymGuideTriggerTop
	coord_event 42, 22, 3, VAR_MAP_SCENE_PEWTER_CITY, 0, PewterCity_EventScript_GymGuideTriggerMid
	coord_event 42, 23, 3, VAR_MAP_SCENE_PEWTER_CITY, 0, PewterCity_EventScript_GymGuideTriggerBottom
	coord_event 43, 23, 3, VAR_MAP_SCENE_PEWTER_CITY, 0, PewterCity_EventScript_GymGuideTriggerRight
	coord_event 46, 21, 3, VAR_MAP_SCENE_PEWTER_CITY, 1, PewterCity_EventScript_RunningShoesAideTriggerTop
	coord_event 46, 22, 3, VAR_MAP_SCENE_PEWTER_CITY, 1, PewterCity_EventScript_RunningShoesAideTriggerMid
	coord_event 46, 23, 3, VAR_MAP_SCENE_PEWTER_CITY, 1, PewterCity_EventScript_RunningShoesAideTriggerBottom

PewterCity_MapBGEvents:
	bg_sign_event 19, 7, 0, BG_EVENT_PLAYER_FACING_ANY, PewterCity_EventScript_MuseumSign
	bg_sign_event 39, 19, 0, BG_EVENT_PLAYER_FACING_ANY, PewterCity_EventScript_PoliceNotice
	bg_sign_event 11, 16, 0, BG_EVENT_PLAYER_FACING_ANY, PewterCity_EventScript_GymSign
	bg_sign_event 20, 30, 0, BG_EVENT_PLAYER_FACING_ANY, PewterCity_EventScript_TrainerTips
	bg_sign_event 31, 25, 0, BG_EVENT_PLAYER_FACING_ANY, PewterCity_EventScript_CitySign
	bg_hidden_item_event 6, 3, 3, ITEM_POKE_BALL, FLAG_HIDDEN_ITEM_PEWTER_CITY_POKE_BALL, 1, FALSE

PewterCity_MapEvents::
	map_events PewterCity_ObjectEvents, PewterCity_MapWarps, PewterCity_MapCoordEvents, PewterCity_MapBGEvents

@ ===== END data/maps/PewterCity/events.inc =====
@ ===== BEGIN data/maps/CeruleanCity/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/CeruleanCity/map.json
@

	.align 2

CeruleanCity_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_POLICEMAN, 31, 12, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, CeruleanCity_EventScript_Policeman, 0
	object_event 2, OBJ_EVENT_GFX_ROCKET_M, 33, 6, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, CeruleanCity_EventScript_Grunt, FLAG_HIDE_CERULEAN_ROCKET
	object_event 3, OBJ_EVENT_GFX_LITTLE_BOY, 16, 21, 3, MOVEMENT_TYPE_WANDER_UP_AND_DOWN, 1, 3, TRAINER_TYPE_NONE, 0, CeruleanCity_EventScript_LittleBoy, 0
	object_event 4, OBJ_EVENT_GFX_BALDING_MAN, 9, 23, 3, MOVEMENT_TYPE_WANDER_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, CeruleanCity_EventScript_BaldingMan, 0
	object_event 5, OBJ_EVENT_GFX_SLOWBRO, 32, 29, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, CeruleanCity_EventScript_Slowbro, 0
	object_event 6, OBJ_EVENT_GFX_LASS, 33, 29, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NONE, 0, CeruleanCity_EventScript_Lass, 0
	object_event 7, OBJ_EVENT_GFX_YOUNGSTER, 34, 22, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, CeruleanCity_EventScript_Youngster, 0
	object_event 8, OBJ_EVENT_GFX_BLUE, 22, 0, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, 0x0, FLAG_HIDE_CERULEAN_RIVAL
	object_event 9, OBJ_EVENT_GFX_CUT_TREE, 26, 32, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_CutTree, FLAG_TEMP_13
	clone_event 10, OBJ_EVENT_GFX_CUT_TREE, 50, 18, LOCALID_ROUTE9_CUT_TREE, MAP_ROUTE9
	object_event 11, OBJ_EVENT_GFX_WOMAN_1, 12, 30, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NONE, 0, CeruleanCity_EventScript_Woman, 0
	object_event 12, OBJ_EVENT_GFX_COOLTRAINER_M, 1, 13, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, CeruleanCity_EventScript_CeruleanCaveGuard, FLAG_HIDE_CERULEAN_CAVE_GUARD

CeruleanCity_MapWarps:
	warp_def 10, 11, 0, 1, MAP_CERULEAN_CITY_HOUSE1
	warp_def 30, 11, 0, 1, MAP_CERULEAN_CITY_HOUSE2
	warp_def 15, 17, 0, 1, MAP_CERULEAN_CITY_HOUSE3
	warp_def 22, 19, 0, 1, MAP_CERULEAN_CITY_POKEMON_CENTER_1F
	warp_def 31, 21, 0, 1, MAP_CERULEAN_CITY_GYM
	warp_def 13, 28, 3, 1, MAP_CERULEAN_CITY_BIKE_SHOP
	warp_def 29, 28, 0, 1, MAP_CERULEAN_CITY_MART
	warp_def 1, 12, 0, 0, MAP_CERULEAN_CAVE_1F
	warp_def 10, 8, 3, 3, MAP_CERULEAN_CITY_HOUSE1
	warp_def 31, 8, 3, 3, MAP_CERULEAN_CITY_HOUSE2
	warp_def 31, 9, 3, 3, MAP_CERULEAN_CITY_HOUSE2
	warp_def 14, 28, 3, 1, MAP_CERULEAN_CITY_BIKE_SHOP
	warp_def 23, 28, 0, 0, MAP_CERULEAN_CITY_HOUSE4
	warp_def 17, 11, 0, 0, MAP_CERULEAN_CITY_HOUSE5

CeruleanCity_MapCoordEvents:
	coord_event 22, 6, 3, VAR_MAP_SCENE_CERULEAN_CITY_RIVAL, 0, CeruleanCity_EventScript_RivalTriggerLeft
	coord_event 23, 6, 3, VAR_MAP_SCENE_CERULEAN_CITY_RIVAL, 0, CeruleanCity_EventScript_RivalTriggerMid
	coord_event 24, 6, 3, VAR_MAP_SCENE_CERULEAN_CITY_RIVAL, 0, CeruleanCity_EventScript_RivalTriggerRight
	coord_event 33, 5, 3, VAR_MAP_SCENE_CERULEAN_CITY_ROCKET, 0, CeruleanCity_EventScript_GruntTriggerTop
	coord_event 33, 7, 3, VAR_MAP_SCENE_CERULEAN_CITY_ROCKET, 0, CeruleanCity_EventScript_GruntTriggerBottom

CeruleanCity_MapBGEvents:
	bg_sign_event 20, 25, 0, BG_EVENT_PLAYER_FACING_ANY, CeruleanCity_EventScript_CitySign
	bg_sign_event 27, 21, 0, BG_EVENT_PLAYER_FACING_ANY, CeruleanCity_EventScript_GymSign
	bg_sign_event 11, 28, 0, BG_EVENT_PLAYER_FACING_ANY, CeruleanCity_EventScript_BikeShopSign
	bg_sign_event 19, 32, 0, BG_EVENT_PLAYER_FACING_ANY, CeruleanCity_EventScript_TrainerTips
	bg_hidden_item_event 18, 7, 3, ITEM_RARE_CANDY, FLAG_HIDDEN_ITEM_CERULEAN_CITY_RARE_CANDY, 1, FALSE
	bg_sign_event 11, 25, 0, BG_EVENT_PLAYER_FACING_ANY, CeruleanCity_BikeShop_EventScript_Bicycle
	bg_sign_event 11, 27, 0, BG_EVENT_PLAYER_FACING_ANY, CeruleanCity_BikeShop_EventScript_Bicycle
	bg_sign_event 11, 26, 0, BG_EVENT_PLAYER_FACING_ANY, CeruleanCity_BikeShop_EventScript_Bicycle

CeruleanCity_MapEvents::
	map_events CeruleanCity_ObjectEvents, CeruleanCity_MapWarps, CeruleanCity_MapCoordEvents, CeruleanCity_MapBGEvents

@ ===== END data/maps/CeruleanCity/events.inc =====
@ ===== BEGIN data/maps/LavenderTown/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/LavenderTown/map.json
@

	.align 2

LavenderTown_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_LITTLE_GIRL, 19, 10, 3, MOVEMENT_TYPE_WANDER_AROUND, 2, 1, TRAINER_TYPE_NONE, 0, LavenderTown_EventScript_LittleGirl, 0
	object_event 2, OBJ_EVENT_GFX_WORKER_M, 12, 12, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, LavenderTown_EventScript_WorkerM, 0
	object_event 3, OBJ_EVENT_GFX_BOY, 10, 7, 3, MOVEMENT_TYPE_FACE_LEFT_AND_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, LavenderTown_EventScript_Boy, 0

LavenderTown_MapWarps:
	warp_def 18, 6, 0, 1, MAP_POKEMON_TOWER_1F
	warp_def 6, 5, 0, 1, MAP_LAVENDER_TOWN_POKEMON_CENTER_1F
	warp_def 10, 11, 0, 1, MAP_LAVENDER_TOWN_VOLUNTEER_POKEMON_HOUSE
	warp_def 5, 16, 0, 1, MAP_LAVENDER_TOWN_HOUSE1
	warp_def 10, 16, 0, 1, MAP_LAVENDER_TOWN_HOUSE2
	warp_def 20, 15, 0, 1, MAP_LAVENDER_TOWN_MART

LavenderTown_MapBGEvents:
	bg_sign_event 12, 4, 0, BG_EVENT_PLAYER_FACING_ANY, LavenderTown_EventScript_SilphScopeNotice
	bg_sign_event 15, 11, 0, BG_EVENT_PLAYER_FACING_ANY, LavenderTown_EventScript_TownSign
	bg_sign_event 21, 7, 0, BG_EVENT_PLAYER_FACING_ANY, LavenderTown_EventScript_PokemonTowerSign
	bg_sign_event 7, 11, 0, BG_EVENT_PLAYER_FACING_ANY, LavenderTown_EventScript_VolunteerHouseSign

LavenderTown_MapEvents::
	map_events LavenderTown_ObjectEvents, LavenderTown_MapWarps, NULL, LavenderTown_MapBGEvents

@ ===== END data/maps/LavenderTown/events.inc =====
@ ===== BEGIN data/maps/VermilionCity/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/VermilionCity/map.json
@

	.align 2

VermilionCity_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_WOMAN_1, 22, 11, 3, MOVEMENT_TYPE_WANDER_LEFT_AND_RIGHT, 4, 1, TRAINER_TYPE_NONE, 0, VermilionCity_EventScript_Woman, 0
	object_event 2, OBJ_EVENT_GFX_OLD_MAN_1, 17, 9, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, VermilionCity_EventScript_OldMan1, 0
	object_event 3, OBJ_EVENT_GFX_OLD_MAN_2, 36, 10, 0, MOVEMENT_TYPE_FACE_DOWN_AND_LEFT, 1, 1, TRAINER_TYPE_NONE, 0, VermilionCity_EventScript_OldMan2, 0
	object_event 4, OBJ_EVENT_GFX_MACHOP, 35, 11, 3, MOVEMENT_TYPE_WANDER_AROUND, 2, 2, TRAINER_TYPE_NONE, 0, VermilionCity_EventScript_Machop, 0
	object_event 5, OBJ_EVENT_GFX_SAILOR, 31, 30, 3, MOVEMENT_TYPE_WANDER_LEFT_AND_RIGHT, 4, 1, TRAINER_TYPE_NONE, 0, VermilionCity_EventScript_Sailor, 0
	object_event 6, OBJ_EVENT_GFX_SAILOR, 24, 33, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NONE, 0, VermilionCity_EventScript_FerrySailor, 0
	object_event 7, OBJ_EVENT_GFX_CUT_TREE, 19, 24, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_CutTree, FLAG_TEMP_12
	object_event 8, OBJ_EVENT_GFX_SCIENTIST, 25, 7, 3, MOVEMENT_TYPE_LOOK_AROUND, 4, 1, TRAINER_TYPE_NONE, 0, VermilionCity_EventScript_OaksAide, FLAG_HIDE_VERMILION_CITY_OAKS_AIDE

VermilionCity_MapWarps:
	warp_def 22, 34, 3, 1, MAP_SSANNE_EXTERIOR
	warp_def 23, 34, 3, 1, MAP_SSANNE_EXTERIOR
	warp_def 24, 34, 3, 1, MAP_SSANNE_EXTERIOR
	warp_def 9, 6, 0, 1, MAP_VERMILION_CITY_HOUSE1
	warp_def 15, 6, 3, 1, MAP_VERMILION_CITY_POKEMON_CENTER_1F
	warp_def 12, 17, 0, 1, MAP_VERMILION_CITY_POKEMON_FAN_CLUB
	warp_def 19, 17, 0, 1, MAP_VERMILION_CITY_HOUSE2
	warp_def 29, 17, 0, 1, MAP_VERMILION_CITY_MART
	warp_def 28, 24, 0, 1, MAP_VERMILION_CITY_HOUSE3
	warp_def 14, 25, 0, 1, MAP_VERMILION_CITY_GYM

VermilionCity_MapCoordEvents:
	coord_event 22, 33, 0, VAR_VERMILION_CITY_TICKET_CHECK_TRIGGER, 0, VermilionCity_EventScript_CheckTicketLeft
	coord_event 23, 33, 0, VAR_VERMILION_CITY_TICKET_CHECK_TRIGGER, 0, VermilionCity_EventScript_CheckTicketRight
	coord_event 22, 32, 0, VAR_TEMP_1, 0, VermilionCity_EventScript_ExitedTicketCheck
	coord_event 23, 32, 0, VAR_TEMP_1, 0, VermilionCity_EventScript_ExitedTicketCheck

VermilionCity_MapBGEvents:
	bg_sign_event 33, 6, 0, BG_EVENT_PLAYER_FACING_ANY, VermilionCity_EventScript_CitySign
	bg_sign_event 10, 17, 3, BG_EVENT_PLAYER_FACING_ANY, VermilionCity_EventScript_PokemonFanClubSign
	bg_sign_event 10, 24, 0, BG_EVENT_PLAYER_FACING_ANY, VermilionCity_EventScript_GymSign
	bg_sign_event 34, 18, 0, BG_EVENT_PLAYER_FACING_ANY, VermilionCity_EventScript_HarborSign
	bg_sign_event 45, 17, 3, BG_EVENT_PLAYER_FACING_ANY, VermilionCity_EventScript_SnorlaxNotice
	bg_hidden_item_event 14, 11, 3, ITEM_MAX_ETHER, FLAG_HIDDEN_ITEM_VERMILION_CITY_MAX_ETHER, 1, FALSE

VermilionCity_MapEvents::
	map_events VermilionCity_ObjectEvents, VermilionCity_MapWarps, VermilionCity_MapCoordEvents, VermilionCity_MapBGEvents

@ ===== END data/maps/VermilionCity/events.inc =====
@ ===== BEGIN data/maps/CeladonCity/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/CeladonCity/map.json
@

	.align 2

CeladonCity_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_ROCKET_M, 48, 15, 3, MOVEMENT_TYPE_WANDER_LEFT_AND_RIGHT, 4, 1, TRAINER_TYPE_NONE, 0, CeladonCity_EventScript_RocketGrunt1, FLAG_HIDE_CELADON_ROCKETS
	object_event 2, OBJ_EVENT_GFX_FAT_MAN, 38, 14, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NONE, 0, CeladonCity_EventScript_FatMan, 0
	object_event 3, OBJ_EVENT_GFX_POLIWRATH, 36, 14, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, CeladonCity_EventScript_Poliwrath, 0
	object_event 4, OBJ_EVENT_GFX_LITTLE_GIRL, 11, 18, 3, MOVEMENT_TYPE_WALK_SEQUENCE_RIGHT_DOWN_LEFT_UP, 4, 4, TRAINER_TYPE_NONE, 0, CeladonCity_EventScript_LittleGirl, 0
	object_event 5, OBJ_EVENT_GFX_WOMAN_2, 18, 22, 3, MOVEMENT_TYPE_WANDER_AROUND, 2, 5, TRAINER_TYPE_NONE, 0, CeladonCity_EventScript_Woman, 0
	object_event 6, OBJ_EVENT_GFX_OLD_MAN_1, 30, 24, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, CeladonCity_EventScript_OldMan2, 0
	object_event 7, OBJ_EVENT_GFX_OLD_MAN_2, 26, 19, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, CeladonCity_EventScript_SoftboiledTutor, 0
	object_event 8, OBJ_EVENT_GFX_ROCKET_M, 38, 31, 3, MOVEMENT_TYPE_WANDER_LEFT_AND_RIGHT, 5, 1, TRAINER_TYPE_NONE, 0, CeladonCity_EventScript_RocketGrunt2, FLAG_HIDE_CELADON_ROCKETS
	object_event 9, OBJ_EVENT_GFX_OLD_MAN_1, 9, 30, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NONE, 0, CeladonCity_EventScript_OldMan1, 0
	object_event 10, OBJ_EVENT_GFX_CUT_TREE, 52, 22, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_CutTree, FLAG_TEMP_14
	object_event 11, OBJ_EVENT_GFX_CUT_TREE, 40, 35, 0, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_CutTree, FLAG_TEMP_13
	object_event 12, OBJ_EVENT_GFX_BOY, 25, 10, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NONE, 0, CeladonCity_EventScript_Boy, 0
	clone_event 13, OBJ_EVENT_GFX_CUT_TREE, -7, 21, LOCALID_ROUTE16_CUT_TREE, MAP_ROUTE16
	object_event 14, OBJ_EVENT_GFX_ITEM_BALL, 5, 3, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, CeladonCity_EventScript_ItemEther, FLAG_HIDE_CELADON_CITY_ETHER
	object_event 15, OBJ_EVENT_GFX_SCIENTIST, 47, 24, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, CeladonCity_EventScript_SilphCoScientist, FLAG_HIDE_CELADON_ROCKETS

CeladonCity_MapWarps:
	warp_def 34, 21, 0, 0, MAP_CELADON_CITY_GAME_CORNER
	warp_def 11, 14, 0, 1, MAP_CELADON_CITY_DEPARTMENT_STORE_1F
	warp_def 15, 14, 0, 4, MAP_CELADON_CITY_DEPARTMENT_STORE_1F
	warp_def 30, 11, 0, 1, MAP_CELADON_CITY_CONDOMINIUMS_1F
	warp_def 48, 11, 0, 1, MAP_CELADON_CITY_POKEMON_CENTER_1F
	warp_def 39, 20, 0, 1, MAP_CELADON_CITY_GAME_CORNER_PRIZE_ROOM
	warp_def 11, 30, 0, 1, MAP_CELADON_CITY_GYM
	warp_def 37, 29, 0, 1, MAP_CELADON_CITY_RESTAURANT
	warp_def 41, 29, 0, 1, MAP_CELADON_CITY_HOUSE1
	warp_def 49, 29, 0, 1, MAP_CELADON_CITY_HOTEL
	warp_def 29, 5, 0, 5, MAP_CELADON_CITY_CONDOMINIUMS_1F
	warp_def 30, 4, 3, 5, MAP_CELADON_CITY_CONDOMINIUMS_1F
	warp_def 31, 5, 0, 5, MAP_CELADON_CITY_CONDOMINIUMS_1F

CeladonCity_MapBGEvents:
	bg_sign_event 45, 23, 0, BG_EVENT_PLAYER_FACING_ANY, CeladonCity_EventScript_TrainerTips2
	bg_sign_event 38, 23, 0, BG_EVENT_PLAYER_FACING_ANY, CeladonCity_EventScript_PrizeExchangeSign
	bg_sign_event 33, 23, 0, BG_EVENT_PLAYER_FACING_ANY, CeladonCity_EventScript_GameCornerSign
	bg_sign_event 22, 18, 3, BG_EVENT_PLAYER_FACING_ANY, CeladonCity_EventScript_CitySign
	bg_sign_event 26, 11, 0, BG_EVENT_PLAYER_FACING_ANY, CeladonCity_EventScript_MansionSign
	bg_sign_event 33, 16, 0, BG_EVENT_PLAYER_FACING_ANY, CeladonCity_EventScript_TrainerTips1
	bg_sign_event 18, 14, 3, BG_EVENT_PLAYER_FACING_ANY, CeladonCity_EventScript_DeptStoreSign
	bg_sign_event 16, 31, 0, BG_EVENT_PLAYER_FACING_ANY, CeladonCity_EventScript_GymSign
	bg_hidden_item_event 55, 20, 3, ITEM_PP_UP, FLAG_HIDDEN_ITEM_CELADON_CITY_PP_UP, 1, FALSE

CeladonCity_MapEvents::
	map_events CeladonCity_ObjectEvents, CeladonCity_MapWarps, NULL, CeladonCity_MapBGEvents

@ ===== END data/maps/CeladonCity/events.inc =====
@ ===== BEGIN data/maps/FuchsiaCity/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FuchsiaCity/map.json
@

	.align 2

FuchsiaCity_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_FAT_MAN, 37, 17, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, FuchsiaCity_EventScript_Erik, 0
	object_event 2, OBJ_EVENT_GFX_SLOWPOKE, 36, 15, 3, MOVEMENT_TYPE_WANDER_AROUND_SLOWER, 4, 1, TRAINER_TYPE_NONE, 0, 0x0, 0
	object_event 3, OBJ_EVENT_GFX_VOLTORB, 33, 8, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, 0x0, 0
	object_event 4, OBJ_EVENT_GFX_YOUNGSTER, 33, 11, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NONE, 0, FuchsiaCity_EventScript_Youngster, 0
	object_event 5, OBJ_EVENT_GFX_CHANSEY, 39, 8, 3, MOVEMENT_TYPE_WANDER_AROUND, 3, 1, TRAINER_TYPE_NONE, 0, 0x0, 0
	object_event 6, OBJ_EVENT_GFX_LITTLE_BOY, 14, 15, 3, MOVEMENT_TYPE_WANDER_LEFT_AND_RIGHT, 3, 1, TRAINER_TYPE_NONE, 0, FuchsiaCity_EventScript_LittleBoy, 0
	object_event 7, OBJ_EVENT_GFX_LAPRAS, 12, 20, 1, MOVEMENT_TYPE_WANDER_AROUND, 2, 1, TRAINER_TYPE_NONE, 0, 0x0, 0
	object_event 8, OBJ_EVENT_GFX_OLD_MAN_1, 36, 20, 3, MOVEMENT_TYPE_WANDER_LEFT_AND_RIGHT, 4, 1, TRAINER_TYPE_NONE, 0, FuchsiaCity_EventScript_OldMan, 0
	object_event 9, OBJ_EVENT_GFX_VAR_0, 8, 8, 1, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, 0x0, 0
	object_event 10, OBJ_EVENT_GFX_KANGASKHAN, 16, 9, 3, MOVEMENT_TYPE_WANDER_AROUND, 4, 1, TRAINER_TYPE_NONE, 0, 0x0, 0
	object_event 11, OBJ_EVENT_GFX_CUT_TREE, 30, 10, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_CutTree, FLAG_TEMP_12
	object_event 12, OBJ_EVENT_GFX_CUT_TREE, 21, 13, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_CutTree, FLAG_TEMP_13
	object_event 13, OBJ_EVENT_GFX_CUT_TREE, 32, 16, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_CutTree, FLAG_TEMP_14
	object_event 14, OBJ_EVENT_GFX_CUT_TREE, 24, 22, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_CutTree, FLAG_TEMP_15
	object_event 15, OBJ_EVENT_GFX_BUG_CATCHER, 15, 11, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NONE, 0, FuchsiaCity_EventScript_SubstituteTutor, 0
	object_event 16, OBJ_EVENT_GFX_LASS, 40, 6, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, FuchsiaCity_EventScript_Lass, FLAG_HIDE_POSTGAME_GOSSIPERS

FuchsiaCity_MapWarps:
	warp_def 24, 5, 0, 2, MAP_FUCHSIA_CITY_SAFARI_ZONE_ENTRANCE
	warp_def 33, 31, 0, 1, MAP_FUCHSIA_CITY_WARDENS_HOUSE
	warp_def 11, 15, 0, 1, MAP_FUCHSIA_CITY_MART
	warp_def 28, 16, 0, 1, MAP_FUCHSIA_CITY_SAFARI_ZONE_OFFICE
	warp_def 9, 32, 0, 1, MAP_FUCHSIA_CITY_GYM
	warp_def 14, 31, 0, 1, MAP_FUCHSIA_CITY_HOUSE1
	warp_def 25, 31, 3, 1, MAP_FUCHSIA_CITY_POKEMON_CENTER_1F
	warp_def 38, 31, 0, 1, MAP_FUCHSIA_CITY_HOUSE2
	warp_def 39, 28, 3, 3, MAP_FUCHSIA_CITY_HOUSE2
	warp_def 39, 29, 3, 3, MAP_FUCHSIA_CITY_HOUSE2
	warp_def 19, 31, 0, 0, MAP_FUCHSIA_CITY_HOUSE3

FuchsiaCity_MapBGEvents:
	bg_sign_event 31, 18, 3, BG_EVENT_PLAYER_FACING_ANY, FuchsiaCity_EventScript_CitySign
	bg_sign_event 26, 18, 0, BG_EVENT_PLAYER_FACING_ANY, FuchsiaCity_EventScript_SafariZoneSign
	bg_sign_event 5, 32, 0, BG_EVENT_PLAYER_FACING_ANY, FuchsiaCity_EventScript_GymSign
	bg_sign_event 31, 31, 0, BG_EVENT_PLAYER_FACING_ANY, FuchsiaCity_EventScript_WardensHomeSign
	bg_sign_event 35, 10, 0, BG_EVENT_PLAYER_FACING_ANY, FuchsiaCity_EventScript_VoltorbSign
	bg_sign_event 38, 16, 3, BG_EVENT_PLAYER_FACING_ANY, FuchsiaCity_EventScript_SlowpokeSign
	bg_sign_event 41, 10, 0, BG_EVENT_PLAYER_FACING_ANY, FuchsiaCity_EventScript_ChanseySign
	bg_sign_event 17, 10, 0, BG_EVENT_PLAYER_FACING_ANY, FuchsiaCity_EventScript_KangaskhanSign
	bg_sign_event 11, 10, 0, BG_EVENT_PLAYER_FACING_ANY, FuchsiaCity_EventScript_FossilMonSign
	bg_sign_event 17, 18, 3, BG_EVENT_PLAYER_FACING_ANY, FuchsiaCity_EventScript_LaprasSign
	bg_sign_event 22, 7, 0, BG_EVENT_PLAYER_FACING_ANY, FuchsiaCity_EventScript_SafariGameSign
	bg_hidden_item_event 33, 26, 3, ITEM_MAX_REVIVE, FLAG_HIDDEN_ITEM_FUCHSIA_CITY_MAX_REVIVE, 1, FALSE

FuchsiaCity_MapEvents::
	map_events FuchsiaCity_ObjectEvents, FuchsiaCity_MapWarps, NULL, FuchsiaCity_MapBGEvents

@ ===== END data/maps/FuchsiaCity/events.inc =====
@ ===== BEGIN data/maps/CinnabarIsland/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/CinnabarIsland/map.json
@

	.align 2

CinnabarIsland_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_WOMAN_2, 14, 6, 3, MOVEMENT_TYPE_WANDER_LEFT_AND_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, CinnabarIsland_EventScript_Woman, 0
	object_event 2, OBJ_EVENT_GFX_OLD_MAN_1, 11, 11, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, CinnabarIsland_EventScript_OldMan, 0
	object_event 3, OBJ_EVENT_GFX_BILL, 20, 7, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, 0x0, FLAG_HIDE_CINNABAR_BILL
	object_event 4, OBJ_EVENT_GFX_SEAGALLOP, 23, 7, 1, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NONE, 0, 0x0, FLAG_HIDE_CINNABAR_SEAGALLOP

CinnabarIsland_MapWarps:
	warp_def 8, 3, 0, 1, MAP_POKEMON_MANSION_1F
	warp_def 20, 4, 0, 1, MAP_CINNABAR_ISLAND_GYM
	warp_def 8, 9, 0, 1, MAP_CINNABAR_ISLAND_POKEMON_LAB_ENTRANCE
	warp_def 14, 11, 0, 0, MAP_CINNABAR_ISLAND_POKEMON_CENTER_1F
	warp_def 19, 11, 0, 1, MAP_CINNABAR_ISLAND_MART

CinnabarIsland_MapCoordEvents:
	coord_event 20, 5, 3, VAR_TEMP_1, 0, CinnabarIsland_EventScript_GymDoorLocked

CinnabarIsland_MapBGEvents:
	bg_sign_event 12, 3, 0, BG_EVENT_PLAYER_FACING_ANY, CinnabarIsland_EventScript_IslandSign
	bg_sign_event 9, 9, 0, BG_EVENT_PLAYER_FACING_ANY, CinnabarIsland_EventScript_PokemonLabSign
	bg_sign_event 22, 5, 0, BG_EVENT_PLAYER_FACING_ANY, CinnabarIsland_EventScript_GymSign
	bg_sign_event 10, 9, 0, BG_EVENT_PLAYER_FACING_ANY, CinnabarIsland_EventScript_PokemonLabSign

CinnabarIsland_MapEvents::
	map_events CinnabarIsland_ObjectEvents, CinnabarIsland_MapWarps, CinnabarIsland_MapCoordEvents, CinnabarIsland_MapBGEvents

@ ===== END data/maps/CinnabarIsland/events.inc =====
@ ===== BEGIN data/maps/IndigoPlateau_Exterior/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/IndigoPlateau_Exterior/map.json
@

	.align 2

IndigoPlateau_Exterior_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_BLUE, 11, 6, 0, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, 0x0, FLAG_HIDE_CREDITS_RIVAL
	object_event 2, OBJ_EVENT_GFX_PROF_OAK, 11, 6, 0, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, 0x0, FLAG_HIDE_CREDITS_OAK

IndigoPlateau_Exterior_MapWarps:
	warp_def 11, 6, 0, 0, MAP_INDIGO_PLATEAU_POKEMON_CENTER_1F

IndigoPlateau_Exterior_MapEvents::
	map_events IndigoPlateau_Exterior_ObjectEvents, IndigoPlateau_Exterior_MapWarps, NULL, NULL

@ ===== END data/maps/IndigoPlateau_Exterior/events.inc =====
@ ===== BEGIN data/maps/SaffronCity/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SaffronCity/map.json
@

	.align 2

SaffronCity_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_ROCKET_M, 22, 15, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SaffronCity_EventScript_RocketGrunt1, FLAG_HIDE_SAFFRON_ROCKETS
	object_event 2, OBJ_EVENT_GFX_ROCKET_M, 26, 16, 3, MOVEMENT_TYPE_WANDER_LEFT_AND_RIGHT, 4, 1, TRAINER_TYPE_NONE, 0, SaffronCity_EventScript_RocketGrunt2, FLAG_HIDE_SAFFRON_ROCKETS
	object_event 3, OBJ_EVENT_GFX_ROCKET_M, 46, 13, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SaffronCity_EventScript_RocketGrunt3, FLAG_HIDE_SAFFRON_ROCKETS
	object_event 4, OBJ_EVENT_GFX_ROCKET_M, 27, 22, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SaffronCity_EventScript_RocketGrunt4, FLAG_HIDE_SAFFRON_ROCKETS
	object_event 5, OBJ_EVENT_GFX_ROCKET_M, 25, 33, 3, MOVEMENT_TYPE_WANDER_LEFT_AND_RIGHT, 7, 1, TRAINER_TYPE_NONE, 0, SaffronCity_EventScript_RocketGrunt5, FLAG_HIDE_SAFFRON_ROCKETS
	object_event 6, OBJ_EVENT_GFX_ROCKET_M, 34, 31, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SaffronCity_EventScript_DoorGuardGrunt, FLAG_HIDE_SAFFRON_ROCKETS
	object_event 7, OBJ_EVENT_GFX_ROCKET_M, 30, 39, 3, MOVEMENT_TYPE_WANDER_LEFT_AND_RIGHT, 5, 1, TRAINER_TYPE_NONE, 0, SaffronCity_EventScript_RocketGrunt7, FLAG_HIDE_SAFFRON_ROCKETS
	object_event 8, OBJ_EVENT_GFX_ROCKET_M, 48, 24, 3, MOVEMENT_TYPE_WANDER_LEFT_AND_RIGHT, 4, 1, TRAINER_TYPE_NONE, 0, SaffronCity_EventScript_RocketGrunt6, FLAG_HIDE_SAFFRON_ROCKETS
	object_event 9, OBJ_EVENT_GFX_YOUNGSTER, 37, 32, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, SaffronCity_EventScript_Youngster, FLAG_HIDE_SAFFRON_CIVILIANS
	object_event 10, OBJ_EVENT_GFX_WORKER_M, 21, 23, 3, MOVEMENT_TYPE_WANDER_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, SaffronCity_EventScript_WorkerM, FLAG_HIDE_SAFFRON_CIVILIANS
	object_event 11, OBJ_EVENT_GFX_MAN, 39, 16, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NONE, 0, SaffronCity_EventScript_Man, FLAG_HIDE_SAFFRON_CIVILIANS
	object_event 12, OBJ_EVENT_GFX_BOY, 44, 22, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SaffronCity_EventScript_Boy, FLAG_HIDE_SAFFRON_CIVILIANS
	object_event 13, OBJ_EVENT_GFX_PIDGEOT, 45, 22, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SaffronCity_EventScript_Pidgeot, FLAG_HIDE_SAFFRON_CIVILIANS
	object_event 14, OBJ_EVENT_GFX_LASS, 32, 39, 3, MOVEMENT_TYPE_WANDER_LEFT_AND_RIGHT, 5, 1, TRAINER_TYPE_NONE, 0, SaffronCity_EventScript_Lass, FLAG_HIDE_SAFFRON_CIVILIANS
	object_event 15, OBJ_EVENT_GFX_CRUSH_GIRL, 47, 24, 3, MOVEMENT_TYPE_WANDER_LEFT_AND_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, SaffronCity_EventScript_CrushGirl, FLAG_HIDE_POSTGAME_GOSSIPERS

SaffronCity_MapWarps:
	warp_def 33, 30, 0, 1, MAP_SILPH_CO_1F
	warp_def 22, 14, 0, 1, MAP_SAFFRON_CITY_COPYCATS_HOUSE_1F
	warp_def 40, 12, 0, 1, MAP_SAFFRON_CITY_DOJO
	warp_def 46, 12, 0, 1, MAP_SAFFRON_CITY_GYM
	warp_def 27, 21, 0, 1, MAP_SAFFRON_CITY_HOUSE
	warp_def 40, 21, 0, 1, MAP_SAFFRON_CITY_MART
	warp_def 24, 38, 0, 1, MAP_SAFFRON_CITY_POKEMON_CENTER_1F
	warp_def 43, 38, 0, 1, MAP_SAFFRON_CITY_MR_PSYCHICS_HOUSE
	warp_def 8, 27, 3, 2, MAP_ROUTE7_EAST_ENTRANCE
	warp_def 34, 5, 3, 2, MAP_ROUTE5_SOUTH_ENTRANCE
	warp_def 58, 27, 3, 1, MAP_ROUTE8_WEST_ENTRANCE
	warp_def 34, 46, 3, 0, MAP_ROUTE6_NORTH_ENTRANCE
	warp_def 35, 46, 3, 0, MAP_ROUTE6_NORTH_ENTRANCE
	warp_def 35, 5, 3, 2, MAP_ROUTE5_SOUTH_ENTRANCE
	warp_def 47, 21, 0, 0, MAP_SAFFRON_CITY_POKEMON_TRAINER_FAN_CLUB

SaffronCity_MapBGEvents:
	bg_sign_event 29, 14, 0, BG_EVENT_PLAYER_FACING_ANY, SaffronCity_EventScript_CitySign
	bg_sign_event 42, 14, 0, BG_EVENT_PLAYER_FACING_ANY, SaffronCity_EventScript_DojoSign
	bg_sign_event 13, 25, 0, BG_EVENT_PLAYER_FACING_ANY, SaffronCity_EventScript_SilphProductSign
	bg_sign_event 18, 30, 0, BG_EVENT_PLAYER_FACING_ANY, SaffronCity_EventScript_TrainerTips2
	bg_sign_event 29, 31, 0, BG_EVENT_PLAYER_FACING_ANY, SaffronCity_EventScript_SilphCoSign
	bg_sign_event 54, 25, 0, BG_EVENT_PLAYER_FACING_ANY, SaffronCity_EventScript_TrainerTips1
	bg_sign_event 50, 14, 0, BG_EVENT_PLAYER_FACING_ANY, SaffronCity_EventScript_GymSign
	bg_sign_event 40, 38, 0, BG_EVENT_PLAYER_FACING_ANY, SaffronCity_EventScript_MrPsychicsHouseSign
	bg_sign_event 49, 22, 0, BG_EVENT_PLAYER_FACING_ANY, SaffronCity_EventScript_TrainerFanClubSign

SaffronCity_MapEvents::
	map_events SaffronCity_ObjectEvents, SaffronCity_MapWarps, NULL, SaffronCity_MapBGEvents

@ ===== END data/maps/SaffronCity/events.inc =====
@ ===== BEGIN data/maps/SaffronCity_Connection/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SaffronCity_Connection/map.json
@

	.align 2

SaffronCity_Connection_MapEvents::
	map_events NULL, NULL, NULL, NULL

@ ===== END data/maps/SaffronCity_Connection/events.inc =====
@ ===== BEGIN data/maps/OneIsland/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/OneIsland/map.json
@

	.align 2

OneIsland_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_BILL, 12, 16, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, 0x0, FLAG_HIDE_ONE_ISLAND_BILL
	object_event 2, OBJ_EVENT_GFX_OLD_MAN_1, 16, 12, 3, MOVEMENT_TYPE_WANDER_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, OneIsland_EventScript_OldMan, 0
	object_event 3, OBJ_EVENT_GFX_BALDING_MAN, 13, 9, 3, MOVEMENT_TYPE_FACE_DOWN_AND_UP, 1, 1, TRAINER_TYPE_NONE, 0, OneIsland_EventScript_BaldingMan, 0

OneIsland_MapWarps:
	warp_def 14, 5, 0, 0, MAP_ONE_ISLAND_POKEMON_CENTER_1F
	warp_def 19, 9, 0, 0, MAP_ONE_ISLAND_HOUSE1
	warp_def 8, 11, 0, 0, MAP_ONE_ISLAND_HOUSE2
	warp_def 12, 18, 3, 0, MAP_ONE_ISLAND_HARBOR

OneIsland_MapBGEvents:
	bg_sign_event 14, 13, 0, BG_EVENT_PLAYER_FACING_ANY, OneIsland_EventScript_IslandSign
	bg_sign_event 15, 6, 0, BG_EVENT_PLAYER_FACING_ANY, OneIsland_EventScript_PokemonNetCenterSign

OneIsland_MapEvents::
	map_events OneIsland_ObjectEvents, OneIsland_MapWarps, NULL, OneIsland_MapBGEvents

@ ===== END data/maps/OneIsland/events.inc =====
@ ===== BEGIN data/maps/TwoIsland/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/TwoIsland/map.json
@

	.align 2

TwoIsland_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_CLERK, 28, 4, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 2, TRAINER_TYPE_NONE, 0, TwoIsland_EventScript_Clerk, 0
	object_event 2, OBJ_EVENT_GFX_WOMAN_1, 31, 6, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NONE, 0, TwoIsland_EventScript_Woman, FLAG_HIDE_TWO_ISLAND_WOMAN
	object_event 3, OBJ_EVENT_GFX_BEAUTY, 30, 11, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NONE, 0, TwoIsland_EventScript_Beauty, FLAG_HIDE_TWO_ISLAND_BEAUTY
	object_event 4, OBJ_EVENT_GFX_SAILOR, 26, 5, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, TwoIsland_EventScript_Sailor, 0
	object_event 5, OBJ_EVENT_GFX_POKE_MANIAC, 27, 6, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, TwoIsland_EventScript_PokeManiac, FLAG_HIDE_TWO_ISLAND_POKE_MANIAC
	object_event 6, OBJ_EVENT_GFX_CUT_TREE, 30, 16, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_CutTree, FLAG_TEMP_12
	object_event 7, OBJ_EVENT_GFX_ITEM_BALL, 39, 16, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, TwoIsland_EventScript_ItemRevive, FLAG_HIDE_TWO_ISLAND_REVIVE
	object_event 8, OBJ_EVENT_GFX_LITTLE_BOY, 37, 12, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, TwoIsland_EventScript_LittleBoy, 0
	object_event 9, OBJ_EVENT_GFX_BOY, 24, 12, 3, MOVEMENT_TYPE_WANDER_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, TwoIsland_EventScript_Boy, 0

TwoIsland_MapWarps:
	warp_def 39, 9, 0, 0, MAP_TWO_ISLAND_JOYFUL_GAME_CORNER
	warp_def 33, 9, 0, 0, MAP_TWO_ISLAND_HOUSE
	warp_def 21, 7, 0, 0, MAP_TWO_ISLAND_POKEMON_CENTER_1F
	warp_def 10, 8, 3, 0, MAP_TWO_ISLAND_HARBOR

TwoIsland_MapBGEvents:
	bg_sign_event 29, 8, 0, BG_EVENT_PLAYER_FACING_ANY, TwoIsland_EventScript_IslandSign
	bg_sign_event 40, 10, 0, BG_EVENT_PLAYER_FACING_ANY, TwoIsland_EventScript_JoyfulGameCornerSign
	bg_sign_event 8, 3, 0, BG_EVENT_PLAYER_FACING_ANY, TwoIsland_EventScript_FastCurrentSign

TwoIsland_MapEvents::
	map_events TwoIsland_ObjectEvents, TwoIsland_MapWarps, NULL, TwoIsland_MapBGEvents

@ ===== END data/maps/TwoIsland/events.inc =====
@ ===== BEGIN data/maps/ThreeIsland/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/ThreeIsland/map.json
@

	.align 2

ThreeIsland_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_MAN, 7, 24, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, ThreeIsland_EventScript_AntiBiker1, FLAG_HIDE_THREE_ISLAND_ANTIBIKERS
	object_event 2, OBJ_EVENT_GFX_MAN, 8, 23, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, ThreeIsland_EventScript_AntiBiker2, FLAG_HIDE_THREE_ISLAND_ANTIBIKERS
	object_event 3, OBJ_EVENT_GFX_BIKER, 8, 24, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NONE, 0, ThreeIsland_EventScript_Biker, FLAG_HIDE_THREE_ISLAND_LONE_BIKER
	object_event 4, OBJ_EVENT_GFX_BIKER, 9, 23, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NONE, 0, ThreeIsland_EventScript_Biker, FLAG_HIDE_THREE_ISLAND_BIKERS
	object_event 5, OBJ_EVENT_GFX_BIKER, 9, 24, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NONE, 0, ThreeIsland_EventScript_Biker, FLAG_HIDE_THREE_ISLAND_BIKERS
	object_event 6, OBJ_EVENT_GFX_BIKER, 10, 22, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NONE, 0, ThreeIsland_EventScript_Biker, FLAG_HIDE_THREE_ISLAND_BIKERS
	object_event 7, OBJ_EVENT_GFX_BIKER, 10, 24, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NONE, 0, ThreeIsland_EventScript_Biker, FLAG_HIDE_THREE_ISLAND_BIKERS
	object_event 8, OBJ_EVENT_GFX_BIKER, 11, 23, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NONE, 0, ThreeIsland_EventScript_Biker, FLAG_HIDE_THREE_ISLAND_BIKERS
	object_event 9, OBJ_EVENT_GFX_CUT_TREE, 20, 7, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_CutTree, FLAG_TEMP_12
	object_event 10, OBJ_EVENT_GFX_ITEM_BALL, 18, 17, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, ThreeIsland_EventScript_ItemZinc, FLAG_HIDE_THREE_ISLAND_ZINC
	object_event 11, OBJ_EVENT_GFX_WOMAN_1, 15, 7, 3, MOVEMENT_TYPE_WANDER_LEFT_AND_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, ThreeIsland_EventScript_Woman, 0
	object_event 12, OBJ_EVENT_GFX_LITTLE_BOY, 14, 14, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, ThreeIsland_EventScript_LittleBoy, 0
	object_event 13, OBJ_EVENT_GFX_DODUO, 15, 14, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NONE, 0, ThreeIsland_EventScript_Doduo, 0
	object_event 14, OBJ_EVENT_GFX_BIKER, 15, 31, 3, MOVEMENT_TYPE_WANDER_LEFT_AND_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, ThreeIsland_EventScript_Biker6, FLAG_HIDE_THREE_ISLAND_BIKERS

ThreeIsland_MapWarps:
	warp_def 3, 31, 0, 0, MAP_THREE_ISLAND_HOUSE1
	warp_def 14, 27, 0, 0, MAP_THREE_ISLAND_POKEMON_CENTER_1F
	warp_def 18, 12, 0, 0, MAP_THREE_ISLAND_MART
	warp_def 4, 6, 0, 0, MAP_THREE_ISLAND_HOUSE2
	warp_def 12, 6, 0, 0, MAP_THREE_ISLAND_HOUSE3
	warp_def 12, 12, 0, 0, MAP_THREE_ISLAND_HOUSE4
	warp_def 13, 19, 0, 0, MAP_THREE_ISLAND_HOUSE5

ThreeIsland_MapCoordEvents:
	coord_event 7, 27, 3, VAR_MAP_SCENE_THREE_ISLAND, 2, ThreeIsland_EventScript_BikerBossIntroTrigger
	coord_event 8, 27, 3, VAR_MAP_SCENE_THREE_ISLAND, 2, ThreeIsland_EventScript_BikerBossIntroTrigger
	coord_event 9, 27, 3, VAR_MAP_SCENE_THREE_ISLAND, 2, ThreeIsland_EventScript_BikerBossIntroTrigger
	coord_event 10, 27, 3, VAR_MAP_SCENE_THREE_ISLAND, 2, ThreeIsland_EventScript_BikerBossIntroTrigger
	coord_event 7, 26, 3, VAR_MAP_SCENE_THREE_ISLAND, 3, ThreeIsland_EventScript_BattleBikersTriggerLeft
	coord_event 8, 26, 3, VAR_MAP_SCENE_THREE_ISLAND, 3, ThreeIsland_EventScript_BattleBikersTriggerMidLeft
	coord_event 9, 26, 3, VAR_MAP_SCENE_THREE_ISLAND, 3, ThreeIsland_EventScript_BattleBikersTriggerMid
	coord_event 11, 27, 3, VAR_MAP_SCENE_THREE_ISLAND, 2, ThreeIsland_EventScript_BikerBossIntroTrigger
	coord_event 10, 26, 3, VAR_MAP_SCENE_THREE_ISLAND, 3, ThreeIsland_EventScript_BattleBikersTriggerMidRight
	coord_event 11, 26, 3, VAR_MAP_SCENE_THREE_ISLAND, 3, ThreeIsland_EventScript_BattleBikersTriggerRight

ThreeIsland_MapBGEvents:
	bg_sign_event 12, 31, 0, BG_EVENT_PLAYER_FACING_ANY, ThreeIsland_EventScript_IslandSign
	bg_hidden_item_event 5, 13, 3, ITEM_PP_UP, FLAG_HIDDEN_ITEM_THREE_ISLAND_PP_UP, 1, FALSE

ThreeIsland_MapEvents::
	map_events ThreeIsland_ObjectEvents, ThreeIsland_MapWarps, ThreeIsland_MapCoordEvents, ThreeIsland_MapBGEvents

@ ===== END data/maps/ThreeIsland/events.inc =====
@ ===== BEGIN data/maps/FourIsland/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FourIsland/map.json
@

	.align 2

FourIsland_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_OLD_MAN_1, 16, 13, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, FourIsland_EventScript_DaycareMan, 0
	object_event 2, OBJ_EVENT_GFX_DODUO, 12, 9, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, 0x0, 0
	object_event 3, OBJ_EVENT_GFX_NIDORAN_F, 13, 7, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, 0x0, 0
	object_event 4, OBJ_EVENT_GFX_NIDORAN_M, 14, 7, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NONE, 0, 0x0, 0
	object_event 5, OBJ_EVENT_GFX_PSYDUCK, 17, 9, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, 0x0, 0
	object_event 6, OBJ_EVENT_GFX_OLD_WOMAN, 26, 19, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NONE, 0, FourIsland_EventScript_OldWoman, 0
	object_event 7, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 5, 11, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_12
	object_event 8, OBJ_EVENT_GFX_ITEM_BALL, 5, 6, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, FourIsland_EventScript_ItemStarPiece, FLAG_HIDE_FOUR_ISLAND_STAR_PIECE
	object_event 9, OBJ_EVENT_GFX_ITEM_BALL, 32, 19, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, FourIsland_EventScript_ItemStardust, FLAG_HIDE_FOUR_ISLAND_STARDUST
	object_event 10, OBJ_EVENT_GFX_BLUE, 8, 25, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NONE, 0, 0x0, FLAG_HIDE_FOUR_ISLAND_RIVAL
	object_event 11, OBJ_EVENT_GFX_FAT_MAN, 36, 13, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, FourIsland_EventScript_FatMan, 0
	object_event 12, OBJ_EVENT_GFX_LITTLE_GIRL, 31, 21, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, FourIsland_EventScript_LittleGirl, 0

FourIsland_MapWarps:
	warp_def 18, 20, 0, 0, MAP_FOUR_ISLAND_POKEMON_CENTER_1F
	warp_def 12, 13, 0, 0, MAP_FOUR_ISLAND_POKEMON_DAY_CARE
	warp_def 25, 14, 0, 0, MAP_FOUR_ISLAND_HOUSE1
	warp_def 38, 12, 0, 0, MAP_FOUR_ISLAND_ICEFALL_CAVE_ENTRANCE
	warp_def 33, 23, 0, 0, MAP_FOUR_ISLAND_LORELEIS_HOUSE
	warp_def 25, 26, 0, 0, MAP_FOUR_ISLAND_HOUSE2
	warp_def 10, 28, 3, 0, MAP_FOUR_ISLAND_HARBOR
	warp_def 22, 26, 0, 0, MAP_FOUR_ISLAND_MART

FourIsland_MapBGEvents:
	bg_sign_event 13, 19, 0, BG_EVENT_PLAYER_FACING_ANY, FourIsland_EventScript_IslandSign
	bg_hidden_item_event 22, 34, 3, ITEM_PEARL, FLAG_HIDDEN_ITEM_FOUR_ISLAND_PEARL, 1, FALSE
	bg_hidden_item_event 6, 21, 3, ITEM_ULTRA_BALL, FLAG_HIDDEN_ITEM_FOUR_ISLAND_ULTRA_BALL, 1, FALSE
	bg_sign_event 31, 23, 0, BG_EVENT_PLAYER_FACING_ANY, FourIsland_EventScript_LoreleisHouseSign

FourIsland_MapEvents::
	map_events FourIsland_ObjectEvents, FourIsland_MapWarps, NULL, FourIsland_MapBGEvents

@ ===== END data/maps/FourIsland/events.inc =====
@ ===== BEGIN data/maps/FiveIsland/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FiveIsland/map.json
@

	.align 2

FiveIsland_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_FISHER, 8, 5, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NONE, 0, FiveIsland_EventScript_Fisher, 0
	object_event 2, OBJ_EVENT_GFX_BUG_CATCHER, 16, 10, 3, MOVEMENT_TYPE_WANDER_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, FiveIsland_EventScript_BugCatcher, 0
	clone_event 3, OBJ_EVENT_GFX_CUT_TREE, 32, 9, LOCALID_FIVE_ISLAND_MEADOW_BORDER_TREE, MAP_FIVE_ISLAND_MEADOW

FiveIsland_MapWarps:
	warp_def 12, 14, 3, 0, MAP_FIVE_ISLAND_HARBOR
	warp_def 18, 6, 0, 0, MAP_FIVE_ISLAND_POKEMON_CENTER_1F
	warp_def 12, 6, 0, 0, MAP_FIVE_ISLAND_HOUSE1
	warp_def 22, 9, 0, 0, MAP_FIVE_ISLAND_HOUSE2

FiveIsland_MapBGEvents:
	bg_sign_event 20, 8, 0, BG_EVENT_PLAYER_FACING_ANY, FiveIsland_EventScript_IslandSign

FiveIsland_MapEvents::
	map_events FiveIsland_ObjectEvents, FiveIsland_MapWarps, NULL, FiveIsland_MapBGEvents

@ ===== END data/maps/FiveIsland/events.inc =====
@ ===== BEGIN data/maps/SevenIsland/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SevenIsland/map.json
@

	.align 2

SevenIsland_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_COOLTRAINER_M, 7, 18, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NONE, 0, SevenIsland_EventScript_SwordsDanceTutor, 0
	object_event 2, OBJ_EVENT_GFX_OLD_WOMAN, 9, 7, 3, MOVEMENT_TYPE_FACE_DOWN_AND_UP, 1, 1, TRAINER_TYPE_NONE, 0, SevenIsland_EventScript_OldWoman, 0
	object_event 3, OBJ_EVENT_GFX_SCIENTIST, 15, 5, 3, MOVEMENT_TYPE_WANDER_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, SevenIsland_EventScript_Scientist, 0

SevenIsland_MapWarps:
	warp_def 11, 9, 0, 0, MAP_SEVEN_ISLAND_HOUSE_ROOM1
	warp_def 5, 9, 0, 0, MAP_SEVEN_ISLAND_MART
	warp_def 12, 3, 0, 0, MAP_SEVEN_ISLAND_POKEMON_CENTER_1F
	warp_def 16, 13, 3, 0, MAP_SEVEN_ISLAND_HARBOR

SevenIsland_MapBGEvents:
	bg_sign_event 17, 9, 0, BG_EVENT_PLAYER_FACING_ANY, SevenIsland_EventScript_IslandSign

SevenIsland_MapEvents::
	map_events SevenIsland_ObjectEvents, SevenIsland_MapWarps, NULL, SevenIsland_MapBGEvents

@ ===== END data/maps/SevenIsland/events.inc =====
@ ===== BEGIN data/maps/SixIsland/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SixIsland/map.json
@

	.align 2

SixIsland_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_BOY, 10, 15, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NONE, 0, SixIsland_EventScript_Boy, 0
	object_event 2, OBJ_EVENT_GFX_HIKER, 15, 13, 3, MOVEMENT_TYPE_FACE_DOWN_AND_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, SixIsland_EventScript_Hiker, 0

SixIsland_MapWarps:
	warp_def 11, 23, 3, 0, MAP_SIX_ISLAND_HARBOR
	warp_def 11, 11, 0, 0, MAP_SIX_ISLAND_POKEMON_CENTER_1F
	warp_def 16, 17, 0, 0, MAP_SIX_ISLAND_HOUSE
	warp_def 20, 11, 0, 0, MAP_SIX_ISLAND_MART

SixIsland_MapBGEvents:
	bg_sign_event 9, 17, 0, BG_EVENT_PLAYER_FACING_ANY, SixIsland_EventScript_IslandSign
	bg_hidden_item_event 9, 7, 3, ITEM_LEPPA_BERRY, FLAG_HIDDEN_ITEM_SIX_ISLAND_LEPPA_BERRY, 1, FALSE

SixIsland_MapEvents::
	map_events SixIsland_ObjectEvents, SixIsland_MapWarps, NULL, SixIsland_MapBGEvents

@ ===== END data/maps/SixIsland/events.inc =====
@ ===== BEGIN data/maps/Route1/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route1/map.json
@

	.align 2

Route1_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_CLERK, 6, 28, 3, MOVEMENT_TYPE_WANDER_UP_AND_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, Route1_EventScript_MartClerk, 0
	object_event 2, OBJ_EVENT_GFX_BOY, 19, 16, 3, MOVEMENT_TYPE_WANDER_LEFT_AND_RIGHT, 1, 3, TRAINER_TYPE_NONE, 0, Route1_EventScript_Boy, 0

Route1_MapBGEvents:
	bg_sign_event 9, 31, 0, BG_EVENT_PLAYER_FACING_ANY, Route1_EventScript_RouteSign

Route1_MapEvents::
	map_events Route1_ObjectEvents, NULL, NULL, Route1_MapBGEvents

@ ===== END data/maps/Route1/events.inc =====
@ ===== BEGIN data/maps/Route2/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route2/map.json
@

	.align 2

Route2_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_CUT_TREE, 16, 62, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_CutTree, FLAG_TEMP_14
	object_event 2, OBJ_EVENT_GFX_CUT_TREE, 15, 69, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_CutTree, FLAG_TEMP_13
	object_event 3, OBJ_EVENT_GFX_CUT_TREE, 11, 13, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_CutTree, FLAG_TEMP_15
	object_event 4, OBJ_EVENT_GFX_CUT_TREE, 18, 26, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_CutTree, FLAG_TEMP_16
	object_event 5, OBJ_EVENT_GFX_ITEM_BALL, 17, 54, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, Route2_EventScript_ItemEther, FLAG_HIDE_ROUTE2_ETHER
	object_event 6, OBJ_EVENT_GFX_ITEM_BALL, 17, 64, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, Route2_EventScript_ItemParalyzeHeal, FLAG_HIDE_ROUTE2_PARALYZE_HEAL
	clone_event 7, OBJ_EVENT_GFX_CUT_TREE, 6, 85, LOCALID_VIRIDIAN_BORDER_TREE, MAP_VIRIDIAN_CITY

Route2_MapWarps:
	warp_def 5, 13, 3, 3, MAP_ROUTE2_VIRIDIAN_FOREST_NORTH_ENTRANCE
	warp_def 6, 13, 3, 3, MAP_ROUTE2_VIRIDIAN_FOREST_NORTH_ENTRANCE
	warp_def 5, 51, 3, 1, MAP_ROUTE2_VIRIDIAN_FOREST_SOUTH_ENTRANCE
	warp_def 17, 11, 3, 1, MAP_DIGLETTS_CAVE_NORTH_ENTRANCE
	warp_def 17, 22, 0, 1, MAP_ROUTE2_HOUSE
	warp_def 18, 46, 3, 1, MAP_ROUTE2_EAST_BUILDING
	warp_def 18, 41, 3, 3, MAP_ROUTE2_EAST_BUILDING
	warp_def 19, 41, 3, 3, MAP_ROUTE2_EAST_BUILDING
	warp_def 19, 46, 3, 1, MAP_ROUTE2_EAST_BUILDING
	warp_def 6, 51, 3, 1, MAP_ROUTE2_VIRIDIAN_FOREST_SOUTH_ENTRANCE

Route2_MapBGEvents:
	bg_sign_event 14, 12, 0, BG_EVENT_PLAYER_FACING_ANY, Route2_EventScript_DiglettsCaveSign
	bg_sign_event 7, 73, 0, BG_EVENT_PLAYER_FACING_ANY, Route2_EventScript_RouteSign

Route2_MapEvents::
	map_events Route2_ObjectEvents, Route2_MapWarps, NULL, Route2_MapBGEvents

@ ===== END data/maps/Route2/events.inc =====
@ ===== BEGIN data/maps/Route3/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route3/map.json
@

	.align 2

Route3_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_YOUNGSTER, 70, 13, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, Route3_EventScript_Youngster, 0
	object_event 2, OBJ_EVENT_GFX_LASS, 40, 11, 3, MOVEMENT_TYPE_WANDER_UP_AND_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 3, Route3_EventScript_Robin, 0
	object_event 3, OBJ_EVENT_GFX_BUG_CATCHER, 32, 6, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 4, Route3_EventScript_James, 0
	object_event 4, OBJ_EVENT_GFX_LASS, 30, 3, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NORMAL, 5, Route3_EventScript_Sally, 0
	object_event 5, OBJ_EVENT_GFX_BUG_CATCHER, 25, 4, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 2, Route3_EventScript_Greg, 0
	object_event 6, OBJ_EVENT_GFX_YOUNGSTER, 29, 10, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NORMAL, 5, Route3_EventScript_Calvin, 0
	object_event 7, OBJ_EVENT_GFX_LASS, 19, 9, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NORMAL, 5, Route3_EventScript_Janice, 0
	object_event 8, OBJ_EVENT_GFX_BUG_CATCHER, 12, 6, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 3, Route3_EventScript_Colton, 0
	object_event 9, OBJ_EVENT_GFX_YOUNGSTER, 17, 4, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 2, Route3_EventScript_Ben, 0

Route3_MapBGEvents:
	bg_sign_event 72, 11, 0, BG_EVENT_PLAYER_FACING_ANY, Route3_EventScript_RouteSign
	bg_hidden_item_event 26, 9, 3, ITEM_ORAN_BERRY, FLAG_HIDDEN_ITEM_ROUTE3_ORAN_BERRY, 1, FALSE

Route3_MapEvents::
	map_events Route3_ObjectEvents, NULL, NULL, Route3_MapBGEvents

@ ===== END data/maps/Route3/events.inc =====
@ ===== BEGIN data/maps/Route4/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route4/map.json
@

	.align 2

Route4_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_WOMAN_1, 9, 8, 3, MOVEMENT_TYPE_WANDER_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, Route4_EventScript_Woman, 0
	object_event 2, OBJ_EVENT_GFX_LASS, 75, 3, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 4, Route4_EventScript_Crissy, 0
	object_event 3, OBJ_EVENT_GFX_ITEM_BALL, 67, 5, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, Route4_EventScript_ItemTM05, FLAG_HIDE_ROUTE4_TM05
	object_event 4, OBJ_EVENT_GFX_BOY, 15, 14, 3, MOVEMENT_TYPE_WANDER_LEFT_AND_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, Route4_EventScript_Boy, 0
	object_event 5, OBJ_EVENT_GFX_BLACK_BELT, 47, 3, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, Route4_EventScript_MegaPunchTutor, 0
	object_event 6, OBJ_EVENT_GFX_BLACK_BELT, 50, 3, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NONE, 0, Route4_EventScript_MegaKickTutor, 0
	clone_event 7, OBJ_EVENT_GFX_COOLTRAINER_M, 109, 3, LOCALID_CERULEAN_CAVE_GUARD, MAP_CERULEAN_CITY

Route4_MapWarps:
	warp_def 19, 5, 3, 3, MAP_MT_MOON_1F
	warp_def 32, 5, 0, 7, MAP_MT_MOON_B1F
	warp_def 12, 5, 0, 1, MAP_ROUTE4_POKEMON_CENTER_1F

Route4_MapBGEvents:
	bg_sign_event 18, 7, 0, BG_EVENT_PLAYER_FACING_ANY, Route4_EventScript_MtMoonSign
	bg_sign_event 34, 7, 0, BG_EVENT_PLAYER_FACING_ANY, Route4_EventScript_RouteSign
	bg_hidden_item_event 43, 2, 3, ITEM_GREAT_BALL, FLAG_HIDDEN_ITEM_ROUTE4_GREAT_BALL, 1, FALSE
	bg_hidden_item_event 5, 4, 3, ITEM_PERSIM_BERRY, FLAG_HIDDEN_ITEM_ROUTE4_PERSIM_BERRY, 1, FALSE
	bg_hidden_item_event 67, 17, 3, ITEM_RAZZ_BERRY, FLAG_HIDDEN_ITEM_ROUTE4_RAZZ_BERRY, 1, FALSE

Route4_MapEvents::
	map_events Route4_ObjectEvents, Route4_MapWarps, NULL, Route4_MapBGEvents

@ ===== END data/maps/Route4/events.inc =====
@ ===== BEGIN data/maps/Route5/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route5/map.json
@

	.align 2

Route5_MapWarps:
	warp_def 31, 31, 0, 1, MAP_UNDERGROUND_PATH_NORTH_ENTRANCE
	warp_def 23, 25, 0, 1, MAP_ROUTE5_POKEMON_DAY_CARE
	warp_def 24, 32, 3, 1, MAP_ROUTE5_SOUTH_ENTRANCE
	warp_def 25, 32, 3, 1, MAP_ROUTE5_SOUTH_ENTRANCE

Route5_MapBGEvents:
	bg_sign_event 32, 32, 0, BG_EVENT_PLAYER_FACING_ANY, Route5_EventScript_UndergroundPathSign

Route5_MapEvents::
	map_events NULL, Route5_MapWarps, NULL, Route5_MapBGEvents

@ ===== END data/maps/Route5/events.inc =====
@ ===== BEGIN data/maps/Route6/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route6/map.json
@

	.align 2

Route6_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_BUG_CATCHER, 3, 16, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 5, Route6_EventScript_Keigo, 0
	object_event 2, OBJ_EVENT_GFX_CAMPER, 12, 21, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 0, Route6_EventScript_Ricky, 0
	object_event 3, OBJ_EVENT_GFX_PICNICKER, 13, 21, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NORMAL, 0, Route6_EventScript_Nancy, 0
	object_event 4, OBJ_EVENT_GFX_BUG_CATCHER, 20, 25, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NORMAL, 3, Route6_EventScript_Elijah, 0
	object_event 5, OBJ_EVENT_GFX_PICNICKER, 13, 32, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NORMAL, 3, Route6_EventScript_Isabelle, 0
	object_event 6, OBJ_EVENT_GFX_CAMPER, 13, 33, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NORMAL, 3, Route6_EventScript_Jeff, 0

Route6_MapWarps:
	warp_def 19, 13, 0, 1, MAP_UNDERGROUND_PATH_SOUTH_ENTRANCE
	warp_def 12, 5, 3, 2, MAP_ROUTE6_NORTH_ENTRANCE
	warp_def 13, 5, 3, 2, MAP_ROUTE6_NORTH_ENTRANCE

Route6_MapBGEvents:
	bg_sign_event 21, 15, 0, BG_EVENT_PLAYER_FACING_ANY, Route6_EventScript_UndergroundPathSign
	bg_hidden_item_event 5, 5, 3, ITEM_SITRUS_BERRY, FLAG_HIDDEN_ITEM_ROUTE6_SITRUS_BERRY, 1, FALSE
	bg_hidden_item_event 19, 5, 3, ITEM_RARE_CANDY, FLAG_HIDDEN_ITEM_ROUTE6_RARE_CANDY, 1, FALSE

Route6_MapEvents::
	map_events Route6_ObjectEvents, Route6_MapWarps, NULL, Route6_MapBGEvents

@ ===== END data/maps/Route6/events.inc =====
@ ===== BEGIN data/maps/Route7/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route7/map.json
@

	.align 2

Route7_ObjectEvents:
	clone_event 1, OBJ_EVENT_GFX_CUT_TREE, -8, 12, LOCALID_CELADON_BORDER_TREE, MAP_CELADON_CITY

Route7_MapWarps:
	warp_def 7, 14, 0, 1, MAP_UNDERGROUND_PATH_WEST_ENTRANCE
	warp_def 15, 10, 3, 0, MAP_ROUTE7_EAST_ENTRANCE

Route7_MapBGEvents:
	bg_sign_event 5, 14, 0, BG_EVENT_PLAYER_FACING_ANY, Route7_EventScript_UndergroundPathSign
	bg_hidden_item_event 16, 15, 3, ITEM_WEPEAR_BERRY, FLAG_HIDDEN_ITEM_ROUTE7_WEPEAR_BERRY, 1, FALSE

Route7_MapEvents::
	map_events Route7_ObjectEvents, Route7_MapWarps, NULL, Route7_MapBGEvents

@ ===== END data/maps/Route7/events.inc =====
@ ===== BEGIN data/maps/Route8/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route8/map.json
@

	.align 2

Route8_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_LASS, 62, 14, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NORMAL, 6, Route8_EventScript_Julia, 0
	object_event 2, OBJ_EVENT_GFX_OLD_MAN_1, 55, 15, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 3, Route8_EventScript_Rich, 0
	object_event 3, OBJ_EVENT_GFX_SCIENTIST, 51, 6, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NORMAL, 4, Route8_EventScript_Glenn, 0
	object_event 4, OBJ_EVENT_GFX_LASS, 29, 3, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NORMAL, 3, Route8_EventScript_Paige, 0
	object_event 5, OBJ_EVENT_GFX_SCIENTIST, 29, 4, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 6, Route8_EventScript_Leslie, 0
	object_event 6, OBJ_EVENT_GFX_LASS, 29, 5, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NORMAL, 3, Route8_EventScript_Andrea, 0
	object_event 7, OBJ_EVENT_GFX_LASS, 29, 6, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 6, Route8_EventScript_Megan, 0
	object_event 8, OBJ_EVENT_GFX_OLD_MAN_1, 21, 3, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NORMAL, 1, Route8_EventScript_Stan, 0
	object_event 9, OBJ_EVENT_GFX_SCIENTIST, 9, 6, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 4, Route8_EventScript_Aidan, 0
	object_event 10, OBJ_EVENT_GFX_CUT_TREE, 33, 15, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_CutTree, FLAG_TEMP_12
	object_event 11, OBJ_EVENT_GFX_CUT_TREE, 47, 12, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_CutTree, FLAG_TEMP_13
	object_event 12, OBJ_EVENT_GFX_LITTLE_GIRL, 40, 3, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 1, Route8_EventScript_Eli, 0
	object_event 13, OBJ_EVENT_GFX_LITTLE_GIRL, 41, 3, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 1, Route8_EventScript_Anne, 0
	object_event 14, OBJ_EVENT_GFX_BIKER, 14, 16, 3, MOVEMENT_TYPE_WALK_SEQUENCE_RIGHT_DOWN_LEFT_UP, 5, 2, TRAINER_TYPE_NORMAL, 1, Route8_EventScript_Ricardo, 0
	object_event 15, OBJ_EVENT_GFX_BIKER, 24, 17, 3, MOVEMENT_TYPE_WALK_SEQUENCE_RIGHT_UP_DOWN_LEFT, 5, 5, TRAINER_TYPE_NORMAL, 1, Route8_EventScript_Jaren, 0

Route8_MapWarps:
	warp_def 13, 4, 0, 1, MAP_UNDERGROUND_PATH_EAST_ENTRANCE
	warp_def 7, 10, 3, 2, MAP_ROUTE8_WEST_ENTRANCE

Route8_MapBGEvents:
	bg_sign_event 16, 5, 0, BG_EVENT_PLAYER_FACING_ANY, Route8_EventScript_UndergroundPathSign
	bg_hidden_item_event 42, 10, 3, ITEM_RAWST_BERRY, FLAG_HIDDEN_ITEM_ROUTE8_RAWST_BERRY, 1, FALSE
	bg_hidden_item_event 38, 11, 3, ITEM_LUM_BERRY, FLAG_HIDDEN_ITEM_ROUTE8_LUM_BERRY, 1, FALSE
	bg_hidden_item_event 42, 15, 3, ITEM_LEPPA_BERRY, FLAG_HIDDEN_ITEM_ROUTE8_LEPPA_BERRY, 1, FALSE

Route8_MapEvents::
	map_events Route8_ObjectEvents, Route8_MapWarps, NULL, Route8_MapBGEvents

@ ===== END data/maps/Route8/events.inc =====
@ ===== BEGIN data/maps/Route9/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route9/map.json
@

	.align 2

Route9_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_PICNICKER, 14, 10, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NORMAL, 3, Route9_EventScript_Alicia, 0
	object_event 2, OBJ_EVENT_GFX_HIKER, 20, 17, 3, MOVEMENT_TYPE_FACE_UP_AND_LEFT, 1, 1, TRAINER_TYPE_NORMAL, 4, Route9_EventScript_Jeremy, 0
	object_event 3, OBJ_EVENT_GFX_HIKER, 61, 16, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 1, Route9_EventScript_Alan, 0
	object_event 4, OBJ_EVENT_GFX_CAMPER, 26, 7, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NORMAL, 3, Route9_EventScript_Chris, 0
	object_event 5, OBJ_EVENT_GFX_BUG_CATCHER, 26, 1, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 2, Route9_EventScript_Brent, 0
	object_event 6, OBJ_EVENT_GFX_BUG_CATCHER, 49, 7, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 3, Route9_EventScript_Conner, 0
	object_event 7, OBJ_EVENT_GFX_HIKER, 53, 2, 3, MOVEMENT_TYPE_WANDER_LEFT_AND_RIGHT, 3, 1, TRAINER_TYPE_NORMAL, 1, Route9_EventScript_Brice, 0
	object_event 8, OBJ_EVENT_GFX_PICNICKER, 60, 9, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 4, Route9_EventScript_Caitlin, 0
	object_event 9, OBJ_EVENT_GFX_CAMPER, 36, 6, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 5, Route9_EventScript_Drew, 0
	object_event 10, OBJ_EVENT_GFX_CUT_TREE, 2, 8, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_CutTree, FLAG_TEMP_12
	object_event 11, OBJ_EVENT_GFX_ITEM_BALL, 12, 17, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, Route9_EventScript_ItemTM40, FLAG_HIDE_ROUTE9_TM40
	object_event 12, OBJ_EVENT_GFX_ITEM_BALL, 65, 17, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, Route9_EventScript_ItemBurnHeal, FLAG_HIDE_ROUTE9_BURN_HEAL

Route9_MapBGEvents:
	bg_sign_event 29, 7, 0, BG_EVENT_PLAYER_FACING_ANY, Route9_EventScript_RouteSign
	bg_hidden_item_event 15, 7, 0, ITEM_ETHER, FLAG_HIDDEN_ITEM_ROUTE9_ETHER, 1, FALSE
	bg_hidden_item_event 63, 2, 3, ITEM_RARE_CANDY, FLAG_HIDDEN_ITEM_ROUTE9_RARE_CANDY, 1, FALSE
	bg_hidden_item_event 48, 2, 3, ITEM_CHESTO_BERRY, FLAG_HIDDEN_ITEM_ROUTE9_CHESTO_BERRY, 1, FALSE

Route9_MapEvents::
	map_events Route9_ObjectEvents, NULL, NULL, Route9_MapBGEvents

@ ===== END data/maps/Route9/events.inc =====
@ ===== BEGIN data/maps/Route10/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route10/map.json
@

	.align 2

Route10_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_PICNICKER, 7, 60, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NORMAL, 2, Route10_EventScript_Carol, 0
	object_event 2, OBJ_EVENT_GFX_HIKER, 4, 62, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NORMAL, 1, Route10_EventScript_Clark, 0
	object_event 3, OBJ_EVENT_GFX_POKE_MANIAC, 15, 70, 3, MOVEMENT_TYPE_WANDER_LEFT_AND_RIGHT, 2, 1, TRAINER_TYPE_NORMAL, 2, Route10_EventScript_Herman, 0
	object_event 4, OBJ_EVENT_GFX_HIKER, 4, 68, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NORMAL, 2, Route10_EventScript_Trent, 0
	object_event 5, OBJ_EVENT_GFX_POKE_MANIAC, 13, 44, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NORMAL, 5, Route10_EventScript_Mark, 0
	object_event 6, OBJ_EVENT_GFX_PICNICKER, 9, 27, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 2, Route10_EventScript_Heidi, 0
	object_event 7, OBJ_EVENT_GFX_CUT_TREE, 10, 20, 0, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_CutTree, FLAG_TEMP_12
	object_event 8, OBJ_EVENT_GFX_CUT_TREE, 10, 22, 0, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_CutTree, FLAG_TEMP_13
	object_event 9, OBJ_EVENT_GFX_CUT_TREE, 10, 24, 0, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_CutTree, FLAG_TEMP_14
	object_event 10, OBJ_EVENT_GFX_CUT_TREE, 10, 26, 0, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_CutTree, FLAG_TEMP_15

Route10_MapWarps:
	warp_def 8, 19, 3, 0, MAP_ROCK_TUNNEL_1F
	warp_def 8, 57, 3, 5, MAP_ROCK_TUNNEL_1F
	warp_def 7, 40, 3, 1, MAP_POWER_PLANT
	warp_def 13, 20, 0, 1, MAP_ROUTE10_POKEMON_CENTER_1F
	warp_def 2, 37, 3, 3, MAP_POWER_PLANT

Route10_MapBGEvents:
	bg_sign_event 15, 59, 0, BG_EVENT_PLAYER_FACING_ANY, Route10_EventScript_SouthRockTunnelSign
	bg_sign_event 6, 42, 0, BG_EVENT_PLAYER_FACING_ANY, Route10_EventScript_PowerPlantSign
	bg_sign_event 7, 21, 0, BG_EVENT_PLAYER_FACING_ANY, Route10_EventScript_NorthRockTunnelSign
	bg_hidden_item_event 10, 19, 0, ITEM_SUPER_POTION, FLAG_HIDDEN_ITEM_ROUTE10_SUPER_POTION, 1, FALSE
	bg_hidden_item_event 12, 40, 3, ITEM_MAX_ETHER, FLAG_HIDDEN_ITEM_ROUTE10_MAX_ETHER, 1, FALSE
	bg_hidden_item_event 6, 26, 3, ITEM_CHERI_BERRY, FLAG_HIDDEN_ITEM_ROUTE10_CHERI_BERRY, 1, FALSE
	bg_hidden_item_event 17, 29, 3, ITEM_PERSIM_BERRY, FLAG_HIDDEN_ITEM_ROUTE10_PERSIM_BERRY, 1, FALSE
	bg_hidden_item_event 20, 57, 3, ITEM_NANAB_BERRY, FLAG_HIDDEN_ITEM_ROUTE10_NANAB_BERRY, 1, FALSE

Route10_MapEvents::
	map_events Route10_ObjectEvents, Route10_MapWarps, NULL, Route10_MapBGEvents

@ ===== END data/maps/Route10/events.inc =====
@ ===== BEGIN data/maps/Route11/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route11/map.json
@

	.align 2

Route11_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_YOUNGSTER, 19, 8, 3, MOVEMENT_TYPE_FACE_DOWN_AND_LEFT, 1, 1, TRAINER_TYPE_NORMAL, 4, Route11_EventScript_Eddie, 0
	object_event 2, OBJ_EVENT_GFX_OLD_MAN_1, 16, 17, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NORMAL, 1, Route11_EventScript_Hugo, 0
	object_event 3, OBJ_EVENT_GFX_YOUNGSTER, 31, 8, 3, MOVEMENT_TYPE_FACE_UP_AND_LEFT, 1, 1, TRAINER_TYPE_NORMAL, 4, Route11_EventScript_Dillon, 0
	object_event 4, OBJ_EVENT_GFX_YOUNGSTER, 28, 10, 3, MOVEMENT_TYPE_WALK_SEQUENCE_DOWN_RIGHT_LEFT_UP, 8, 4, TRAINER_TYPE_NORMAL, 1, Route11_EventScript_Dave, 0
	object_event 5, OBJ_EVENT_GFX_OLD_MAN_1, 38, 15, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NORMAL, 1, Route11_EventScript_Jasper, 0
	object_event 6, OBJ_EVENT_GFX_OLD_MAN_1, 50, 4, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NORMAL, 1, Route11_EventScript_Darian, 0
	object_event 7, OBJ_EVENT_GFX_BALDING_MAN, 42, 8, 3, MOVEMENT_TYPE_FACE_LEFT_AND_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 4, Route11_EventScript_Braxton, 0
	object_event 8, OBJ_EVENT_GFX_YOUNGSTER, 50, 14, 3, MOVEMENT_TYPE_WALK_UP_AND_DOWN, 1, 4, TRAINER_TYPE_NORMAL, 1, Route11_EventScript_Yasu, 0
	object_event 9, OBJ_EVENT_GFX_OLD_MAN_1, 57, 16, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NORMAL, 1, Route11_EventScript_Dirk, 0
	object_event 10, OBJ_EVENT_GFX_BALDING_MAN, 32, 18, 3, MOVEMENT_TYPE_FACE_LEFT_AND_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 6, Route11_EventScript_Bernie, 0
	object_event 11, OBJ_EVENT_GFX_ITEM_BALL, 42, 12, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, Route11_EventScript_ItemXDefend, FLAG_HIDE_ROUTE11_X_DEFEND
	object_event 12, OBJ_EVENT_GFX_ITEM_BALL, 63, 13, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, Route11_EventScript_ItemGreatBall, FLAG_HIDE_ROUTE11_GREAT_BALL
	object_event 13, OBJ_EVENT_GFX_ITEM_BALL, 13, 3, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, Route11_EventScript_ItemAwakening, FLAG_HIDE_ROUTE11_AWAKENING

Route11_MapWarps:
	warp_def 6, 7, 0, 0, MAP_DIGLETTS_CAVE_SOUTH_ENTRANCE
	warp_def 58, 10, 3, 0, MAP_ROUTE11_EAST_ENTRANCE_1F
	warp_def 65, 10, 3, 2, MAP_ROUTE11_EAST_ENTRANCE_1F

Route11_MapBGEvents:
	bg_sign_event 3, 7, 3, BG_EVENT_PLAYER_FACING_ANY, Route11_EventScript_DiglettsCaveSign
	bg_hidden_item_event 58, 5, 0, ITEM_ESCAPE_ROPE, FLAG_HIDDEN_ITEM_ROUTE11_ESCAPE_ROPE, 1, FALSE

Route11_MapEvents::
	map_events Route11_ObjectEvents, Route11_MapWarps, NULL, Route11_MapBGEvents

@ ===== END data/maps/Route11/events.inc =====
@ ===== BEGIN data/maps/Route12/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route12/map.json
@

	.align 2

Route12_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_FISHER, 17, 32, 3, MOVEMENT_TYPE_FACE_DOWN_AND_UP, 1, 1, TRAINER_TYPE_NORMAL, 1, Route12_EventScript_Ned, 0
	object_event 2, OBJ_EVENT_GFX_FISHER, 9, 40, 3, MOVEMENT_TYPE_FACE_LEFT_AND_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 1, Route12_EventScript_Chip, 0
	object_event 3, OBJ_EVENT_GFX_FISHER, 16, 47, 3, MOVEMENT_TYPE_FACE_DOWN_AND_LEFT, 1, 1, TRAINER_TYPE_NORMAL, 4, Route12_EventScript_Hank, 0
	object_event 4, OBJ_EVENT_GFX_FISHER, 13, 59, 3, MOVEMENT_TYPE_FACE_DOWN_AND_UP, 1, 1, TRAINER_TYPE_NORMAL, 1, Route12_EventScript_Elliot, 0
	object_event 5, OBJ_EVENT_GFX_SNORLAX, 14, 70, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, Route12_EventScript_Snorlax, FLAG_HIDE_ROUTE_12_SNORLAX
	object_event 6, OBJ_EVENT_GFX_ROCKER, 13, 92, 3, MOVEMENT_TYPE_WALK_SEQUENCE_LEFT_UP_DOWN_RIGHT, 4, 4, TRAINER_TYPE_NORMAL, 1, Route12_EventScript_Luca, 0
	object_event 7, OBJ_EVENT_GFX_CAMPER, 10, 99, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 1, Route12_EventScript_Justin, 0
	object_event 8, OBJ_EVENT_GFX_FISHER, 18, 108, 3, MOVEMENT_TYPE_FACE_LEFT_AND_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 1, Route12_EventScript_Andrew, 0
	object_event 9, OBJ_EVENT_GFX_CUT_TREE, 11, 100, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_CutTree, FLAG_TEMP_12
	object_event 10, OBJ_EVENT_GFX_ITEM_BALL, 18, 36, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, Route12_EventScript_ItemTM48, FLAG_HIDE_ROUTE12_TM48
	object_event 11, OBJ_EVENT_GFX_ITEM_BALL, 9, 101, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, Route12_EventScript_ItemIron, FLAG_HIDE_ROUTE12_IRON
	object_event 12, OBJ_EVENT_GFX_BEAUTY, 19, 64, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 0, Route12_EventScript_Gia, 0
	object_event 13, OBJ_EVENT_GFX_MAN, 19, 63, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 0, Route12_EventScript_Jes, 0
	object_event 14, OBJ_EVENT_GFX_CUT_TREE, 12, 111, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_CutTree, FLAG_TEMP_13

Route12_MapWarps:
	warp_def 12, 86, 0, 1, MAP_ROUTE12_FISHING_HOUSE
	warp_def 14, 15, 3, 0, MAP_ROUTE12_NORTH_ENTRANCE_1F
	warp_def 15, 15, 3, 1, MAP_ROUTE12_NORTH_ENTRANCE_1F
	warp_def 14, 21, 3, 2, MAP_ROUTE12_NORTH_ENTRANCE_1F

Route12_MapBGEvents:
	bg_sign_event 17, 13, 0, BG_EVENT_PLAYER_FACING_ANY, Route12_EventScript_RouteSign
	bg_sign_event 15, 69, 0, BG_EVENT_PLAYER_FACING_ANY, Route12_EventScript_FishingSign
	bg_hidden_item_event 18, 57, 3, ITEM_HYPER_POTION, FLAG_HIDDEN_ITEM_ROUTE12_HYPER_POTION, 1, FALSE
	bg_hidden_item_event 14, 70, 3, ITEM_LEFTOVERS, FLAG_HIDDEN_ITEM_ROUTE12_LEFTOVERS, 1, TRUE
	bg_hidden_item_event 9, 116, 3, ITEM_RARE_CANDY, FLAG_HIDDEN_ITEM_ROUTE12_RARE_CANDY, 1, FALSE

Route12_MapEvents::
	map_events Route12_ObjectEvents, Route12_MapWarps, NULL, Route12_MapBGEvents

@ ===== END data/maps/Route12/events.inc =====
@ ===== BEGIN data/maps/Route13/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route13/map.json
@

	.align 2

Route13_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_PICNICKER, 62, 6, 3, MOVEMENT_TYPE_WANDER_AROUND, 1, 1, TRAINER_TYPE_NORMAL, 1, Route13_EventScript_Alma, 0
	object_event 2, OBJ_EVENT_GFX_ROCKER, 63, 12, 3, MOVEMENT_TYPE_WANDER_AROUND, 1, 1, TRAINER_TYPE_NORMAL, 1, Route13_EventScript_Sebastian, 0
	object_event 3, OBJ_EVENT_GFX_PICNICKER, 54, 11, 3, MOVEMENT_TYPE_WANDER_AROUND, 1, 1, TRAINER_TYPE_NORMAL, 1, Route13_EventScript_Susie, 0
	object_event 4, OBJ_EVENT_GFX_BEAUTY, 42, 7, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 3, Route13_EventScript_Sheila, 0
	object_event 5, OBJ_EVENT_GFX_BEAUTY, 43, 7, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 3, Route13_EventScript_Lola, 0
	object_event 6, OBJ_EVENT_GFX_PICNICKER, 35, 10, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 1, Route13_EventScript_Valerie, 0
	object_event 7, OBJ_EVENT_GFX_PICNICKER, 29, 11, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NORMAL, 3, Route13_EventScript_Gwen, 0
	object_event 8, OBJ_EVENT_GFX_ROCKER, 9, 14, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NORMAL, 3, Route13_EventScript_Robert, 0
	object_event 9, OBJ_EVENT_GFX_ROCKER, 16, 5, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 3, Route13_EventScript_Perry, 0
	object_event 10, OBJ_EVENT_GFX_BIKER, 14, 8, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NORMAL, 1, Route13_EventScript_Jared, 0
	object_event 11, OBJ_EVENT_GFX_CUT_TREE, 44, 5, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_CutTree, FLAG_TEMP_12

Route13_MapBGEvents:
	bg_sign_event 41, 12, 0, BG_EVENT_PLAYER_FACING_ANY, Route13_EventScript_RouteSign
	bg_sign_event 37, 6, 0, BG_EVENT_PLAYER_FACING_ANY, Route13_EventScript_TrainerTips2
	bg_sign_event 21, 14, 0, BG_EVENT_PLAYER_FACING_ANY, Route13_EventScript_TrainerTips1
	bg_hidden_item_event 23, 14, 3, ITEM_PP_UP, FLAG_HIDDEN_ITEM_ROUTE13_PP_UP, 1, FALSE

Route13_MapEvents::
	map_events Route13_ObjectEvents, NULL, NULL, Route13_MapBGEvents

@ ===== END data/maps/Route13/events.inc =====
@ ===== BEGIN data/maps/Route14/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route14/map.json
@

	.align 2

Route14_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_BIKER, 7, 37, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 2, Route14_EventScript_Gerald, 0
	object_event 2, OBJ_EVENT_GFX_ROCKER, 18, 35, 3, MOVEMENT_TYPE_WANDER_AROUND, 2, 2, TRAINER_TYPE_NORMAL, 1, Route14_EventScript_Donald, 0
	object_event 3, OBJ_EVENT_GFX_ROCKER, 10, 14, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 4, Route14_EventScript_Beck, 0
	object_event 4, OBJ_EVENT_GFX_ROCKER, 16, 16, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NORMAL, 3, Route14_EventScript_Marlon, 0
	object_event 5, OBJ_EVENT_GFX_BIKER, 7, 31, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 2, Route14_EventScript_Isaac, 0
	object_event 6, OBJ_EVENT_GFX_BIKER, 7, 34, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 2, Route14_EventScript_Malik, 0
	object_event 7, OBJ_EVENT_GFX_ROCKER, 8, 9, 3, MOVEMENT_TYPE_WANDER_LEFT_AND_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 1, Route14_EventScript_Mitch, 0
	object_event 8, OBJ_EVENT_GFX_ROCKER, 7, 6, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 1, Route14_EventScript_Carter, 0
	object_event 9, OBJ_EVENT_GFX_BIKER, 10, 37, 3, MOVEMENT_TYPE_WALK_UP_AND_DOWN, 1, 6, TRAINER_TYPE_NORMAL, 1, Route14_EventScript_Lukas, 0
	object_event 10, OBJ_EVENT_GFX_ROCKER, 18, 47, 3, MOVEMENT_TYPE_WANDER_AROUND, 2, 2, TRAINER_TYPE_NORMAL, 1, Route14_EventScript_Benny, 0
	object_event 11, OBJ_EVENT_GFX_CUT_TREE, 7, 26, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_CutTree, FLAG_TEMP_12
	object_event 12, OBJ_EVENT_GFX_CUT_TREE, 12, 35, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_CutTree, FLAG_TEMP_13
	object_event 13, OBJ_EVENT_GFX_CUT_TREE, 1, 47, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_CutTree, FLAG_TEMP_14
	object_event 14, OBJ_EVENT_GFX_LITTLE_GIRL, 13, 51, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 1, Route14_EventScript_Jan, 0
	object_event 15, OBJ_EVENT_GFX_LITTLE_GIRL, 12, 51, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 1, Route14_EventScript_Kiri, 0

Route14_MapBGEvents:
	bg_sign_event 17, 12, 0, BG_EVENT_PLAYER_FACING_ANY, Route14_EventScript_RouteSign
	bg_hidden_item_event 9, 20, 3, ITEM_ZINC, FLAG_HIDDEN_ITEM_ROUTE14_ZINC, 1, FALSE
	bg_hidden_item_event 19, 53, 3, ITEM_PINAP_BERRY, FLAG_HIDDEN_ITEM_ROUTE14_PINAP_BERRY, 1, FALSE

Route14_MapEvents::
	map_events Route14_ObjectEvents, NULL, NULL, Route14_MapBGEvents

@ ===== END data/maps/Route14/events.inc =====
@ ===== BEGIN data/maps/Route15/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route15/map.json
@

	.align 2

Route15_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_PICNICKER, 22, 13, 3, MOVEMENT_TYPE_WANDER_AROUND, 1, 1, TRAINER_TYPE_NORMAL, 1, Route15_EventScript_Yazmin, 0
	object_event 2, OBJ_EVENT_GFX_ROCKER, 31, 12, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NORMAL, 5, Route15_EventScript_Edwin, 0
	object_event 3, OBJ_EVENT_GFX_ROCKER, 37, 14, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NORMAL, 2, Route15_EventScript_Chester, 0
	object_event 4, OBJ_EVENT_GFX_PICNICKER, 44, 13, 3, MOVEMENT_TYPE_WANDER_AROUND, 1, 1, TRAINER_TYPE_NORMAL, 1, Route15_EventScript_Kindra, 0
	object_event 5, OBJ_EVENT_GFX_BEAUTY, 50, 12, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 2, Route15_EventScript_Olivia, 0
	object_event 6, OBJ_EVENT_GFX_BIKER, 59, 12, 3, MOVEMENT_TYPE_FACE_DOWN_AND_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 2, Route15_EventScript_Alex, 0
	object_event 7, OBJ_EVENT_GFX_BIKER, 63, 13, 3, MOVEMENT_TYPE_FACE_DOWN_AND_UP, 1, 1, TRAINER_TYPE_NORMAL, 1, Route15_EventScript_Ernest, 0
	object_event 8, OBJ_EVENT_GFX_PICNICKER, 52, 8, 3, MOVEMENT_TYPE_WANDER_AROUND, 2, 4, TRAINER_TYPE_NORMAL, 1, Route15_EventScript_Becky, 0
	object_event 9, OBJ_EVENT_GFX_BEAUTY, 54, 12, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 2, Route15_EventScript_Grace, 0
	object_event 10, OBJ_EVENT_GFX_PICNICKER, 28, 6, 3, MOVEMENT_TYPE_WANDER_AROUND, 2, 4, TRAINER_TYPE_NORMAL, 1, Route15_EventScript_Celia, 0
	object_event 11, OBJ_EVENT_GFX_ITEM_BALL, 20, 6, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, Route15_EventScript_ItemTM18, FLAG_HIDE_ROUTE15_TM18
	object_event 12, OBJ_EVENT_GFX_BLACK_BELT, 39, 7, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 1, Route15_EventScript_Ron, 0
	object_event 13, OBJ_EVENT_GFX_CRUSH_GIRL, 40, 7, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 1, Route15_EventScript_Mya, 0
	clone_event 14, OBJ_EVENT_GFX_CUT_TREE, 73, 7, LOCALID_ROUTE14_BORDER_TREE, MAP_ROUTE14

Route15_MapWarps:
	warp_def 9, 11, 3, 0, MAP_ROUTE15_WEST_ENTRANCE_1F
	warp_def 16, 11, 3, 2, MAP_ROUTE15_WEST_ENTRANCE_1F

Route15_MapBGEvents:
	bg_sign_event 41, 11, 0, BG_EVENT_PLAYER_FACING_ANY, Route15_EventScript_RouteSign

Route15_MapEvents::
	map_events Route15_ObjectEvents, Route15_MapWarps, NULL, Route15_MapBGEvents

@ ===== END data/maps/Route15/events.inc =====
@ ===== BEGIN data/maps/Route16/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route16/map.json
@

	.align 2

Route16_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_BIKER, 16, 12, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NORMAL, 1, Route16_EventScript_Lao, 0
	object_event 2, OBJ_EVENT_GFX_BIKER, 14, 14, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NORMAL, 1, Route16_EventScript_Koji, 0
	object_event 3, OBJ_EVENT_GFX_BIKER, 12, 12, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NORMAL, 1, Route16_EventScript_Luke, 0
	object_event 4, OBJ_EVENT_GFX_BIKER, 8, 12, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NORMAL, 1, Route16_EventScript_Ruben, 0
	object_event 5, OBJ_EVENT_GFX_BIKER, 10, 14, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NORMAL, 1, Route16_EventScript_Hideo, 0
	object_event 6, OBJ_EVENT_GFX_BIKER, 6, 14, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NORMAL, 1, Route16_EventScript_Camron, 0
	object_event 7, OBJ_EVENT_GFX_CUT_TREE, 41, 11, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_CutTree, FLAG_TEMP_12
	object_event 8, OBJ_EVENT_GFX_BEAUTY, 30, 5, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 1, Route16_EventScript_Lea, 0
	object_event 9, OBJ_EVENT_GFX_MAN, 31, 5, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 1, Route16_EventScript_Jed, 0
	object_event 10, OBJ_EVENT_GFX_SNORLAX, 31, 13, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, Route16_EventScript_Snorlax, FLAG_HIDE_ROUTE_16_SNORLAX

Route16_MapWarps:
	warp_def 10, 5, 0, 1, MAP_ROUTE16_HOUSE
	warp_def 20, 6, 3, 0, MAP_ROUTE16_NORTH_ENTRANCE_1F
	warp_def 27, 6, 3, 1, MAP_ROUTE16_NORTH_ENTRANCE_1F
	warp_def 20, 13, 3, 2, MAP_ROUTE16_NORTH_ENTRANCE_1F
	warp_def 27, 13, 3, 3, MAP_ROUTE16_NORTH_ENTRANCE_1F

Route16_MapBGEvents:
	bg_sign_event 6, 17, 0, BG_EVENT_PLAYER_FACING_ANY, Route16_EventScript_RouteSign
	bg_sign_event 33, 11, 0, BG_EVENT_PLAYER_FACING_ANY, Route16_EventScript_CyclingRoadSign
	bg_hidden_item_event 31, 13, 3, ITEM_LEFTOVERS, FLAG_HIDDEN_ITEM_ROUTE16_LEFTOVERS, 1, TRUE

Route16_MapEvents::
	map_events Route16_ObjectEvents, Route16_MapWarps, NULL, Route16_MapBGEvents

@ ===== END data/maps/Route16/events.inc =====
@ ===== BEGIN data/maps/Route17/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route17/map.json
@

	.align 2

Route17_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_BIKER, 4, 18, 3, MOVEMENT_TYPE_WALK_DOWN_AND_UP, 1, 6, TRAINER_TYPE_NORMAL, 1, Route17_EventScript_Virgil, 0
	object_event 2, OBJ_EVENT_GFX_BIKER, 11, 15, 3, MOVEMENT_TYPE_WALK_DOWN_AND_UP, 1, 5, TRAINER_TYPE_NORMAL, 1, Route17_EventScript_Isaiah, 0
	object_event 3, OBJ_EVENT_GFX_BIKER, 15, 24, 3, MOVEMENT_TYPE_WALK_SEQUENCE_RIGHT_DOWN_LEFT_UP, 4, 2, TRAINER_TYPE_NORMAL, 1, Route17_EventScript_Raul, 0
	object_event 4, OBJ_EVENT_GFX_BIKER, 18, 41, 3, MOVEMENT_TYPE_WALK_DOWN_AND_UP, 1, 5, TRAINER_TYPE_NORMAL, 1, Route17_EventScript_Nikolas, 0
	object_event 5, OBJ_EVENT_GFX_BIKER, 7, 38, 3, MOVEMENT_TYPE_FACE_LEFT_AND_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 5, Route17_EventScript_Billy, 0
	object_event 6, OBJ_EVENT_GFX_BIKER, 2, 61, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 4, Route17_EventScript_Jamal, 0
	object_event 7, OBJ_EVENT_GFX_BIKER, 21, 61, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NORMAL, 3, Route17_EventScript_Zeek, 0
	object_event 8, OBJ_EVENT_GFX_BIKER, 18, 94, 3, MOVEMENT_TYPE_WALK_DOWN_AND_UP, 1, 5, TRAINER_TYPE_NORMAL, 1, Route17_EventScript_Corey, 0
	object_event 9, OBJ_EVENT_GFX_BIKER, 16, 134, 3, MOVEMENT_TYPE_WALK_SEQUENCE_LEFT_DOWN_RIGHT_UP, 8, 1, TRAINER_TYPE_NORMAL, 1, Route17_EventScript_William, 0
	object_event 10, OBJ_EVENT_GFX_BIKER, 4, 116, 3, MOVEMENT_TYPE_WALK_DOWN_AND_UP, 1, 5, TRAINER_TYPE_NORMAL, 1, Route17_EventScript_Jaxon, 0

Route17_MapBGEvents:
	bg_sign_event 12, 97, 0, BG_EVENT_PLAYER_FACING_ANY, Route17_EventScript_RouteSign
	bg_sign_event 12, 83, 0, BG_EVENT_PLAYER_FACING_ANY, Route17_EventScript_TrainerTips2
	bg_sign_event 12, 68, 0, BG_EVENT_PLAYER_FACING_ANY, Route17_EventScript_TrainerTips1
	bg_sign_event 12, 53, 0, BG_EVENT_PLAYER_FACING_ANY, Route17_EventScript_ItemsNotice
	bg_sign_event 12, 125, 3, BG_EVENT_PLAYER_FACING_ANY, Route17_EventScript_BallsNotice
	bg_sign_event 11, 157, 0, BG_EVENT_PLAYER_FACING_ANY, Route17_EventScript_CyclingRoadSign
	bg_hidden_item_event 18, 83, 3, ITEM_RARE_CANDY, FLAG_HIDDEN_ITEM_ROUTE17_RARE_CANDY, 1, FALSE
	bg_hidden_item_event 10, 53, 3, ITEM_FULL_RESTORE, FLAG_HIDDEN_ITEM_ROUTE17_FULL_RESTORE, 1, FALSE
	bg_hidden_item_event 4, 68, 3, ITEM_PP_UP, FLAG_HIDDEN_ITEM_ROUTE17_PP_UP, 1, FALSE
	bg_hidden_item_event 4, 125, 3, ITEM_MAX_REVIVE, FLAG_HIDDEN_ITEM_ROUTE17_MAX_REVIVE, 1, FALSE
	bg_hidden_item_event 14, 157, 3, ITEM_MAX_ELIXIR, FLAG_HIDDEN_ITEM_ROUTE17_MAX_ELIXIR, 1, FALSE

Route17_MapEvents::
	map_events Route17_ObjectEvents, NULL, NULL, Route17_MapBGEvents

@ ===== END data/maps/Route17/events.inc =====
@ ===== BEGIN data/maps/Route18/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route18/map.json
@

	.align 2

Route18_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_ROCKER, 46, 14, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NORMAL, 4, Route18_EventScript_Jacob, 0
	object_event 2, OBJ_EVENT_GFX_ROCKER, 41, 15, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NORMAL, 1, Route18_EventScript_Ramiro, 0
	object_event 3, OBJ_EVENT_GFX_ROCKER, 39, 12, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 6, Route18_EventScript_Wilton, 0

Route18_MapWarps:
	warp_def 41, 9, 3, 0, MAP_ROUTE18_EAST_ENTRANCE_1F
	warp_def 48, 9, 3, 1, MAP_ROUTE18_EAST_ENTRANCE_1F

Route18_MapBGEvents:
	bg_sign_event 37, 7, 0, BG_EVENT_PLAYER_FACING_ANY, Route18_EventScript_CyclingRoadSign
	bg_sign_event 52, 7, 0, BG_EVENT_PLAYER_FACING_ANY, Route18_EventScript_RouteSign

Route18_MapEvents::
	map_events Route18_ObjectEvents, Route18_MapWarps, NULL, Route18_MapBGEvents

@ ===== END data/maps/Route18/events.inc =====
@ ===== BEGIN data/maps/Route19/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route19/map.json
@

	.align 2

Route19_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_SWIMMER_M_LAND, 15, 10, 3, MOVEMENT_TYPE_FACE_LEFT, 6, 3, TRAINER_TYPE_NORMAL, 3, Route19_EventScript_Reece, 0
	object_event 2, OBJ_EVENT_GFX_SWIMMER_M_LAND, 10, 9, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 3, Route19_EventScript_Richard, 0
	object_event 3, OBJ_EVENT_GFX_SWIMMER_M_WATER, 12, 17, 1, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NORMAL, 3, Route19_EventScript_Tony, 0
	object_event 4, OBJ_EVENT_GFX_SWIMMER_M_WATER, 18, 33, 1, MOVEMENT_TYPE_WALK_SEQUENCE_LEFT_UP_RIGHT_DOWN, 5, 3, TRAINER_TYPE_NORMAL, 1, Route19_EventScript_Matthew, 0
	object_event 5, OBJ_EVENT_GFX_SWIMMER_M_WATER, 8, 27, 1, MOVEMENT_TYPE_WANDER_AROUND, 2, 2, TRAINER_TYPE_NORMAL, 1, Route19_EventScript_Douglas, 0
	object_event 6, OBJ_EVENT_GFX_SWIMMER_M_WATER, 16, 22, 1, MOVEMENT_TYPE_FACE_LEFT_AND_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 6, Route19_EventScript_David, 0
	object_event 7, OBJ_EVENT_GFX_SWIMMER_M_WATER, 11, 47, 1, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NORMAL, 1, Route19_EventScript_Axle, 0
	object_event 8, OBJ_EVENT_GFX_SWIMMER_F_WATER, 14, 48, 1, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NORMAL, 1, Route19_EventScript_Alice, 0
	object_event 9, OBJ_EVENT_GFX_SWIMMER_F_WATER, 12, 49, 1, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NORMAL, 1, Route19_EventScript_Connie, 0
	object_event 10, OBJ_EVENT_GFX_SWIMMER_F_WATER, 9, 48, 1, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NORMAL, 1, Route19_EventScript_Anya, 0
	object_event 11, OBJ_EVENT_GFX_SWIMMER_F_WATER, 8, 41, 1, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 1, Route19_EventScript_Lia, 0
	object_event 12, OBJ_EVENT_GFX_TUBER_M_WATER, 9, 41, 1, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 1, Route19_EventScript_Luc, 0

Route19_MapBGEvents:
	bg_sign_event 13, 12, 0, BG_EVENT_PLAYER_FACING_ANY, Route19_EventScript_RouteSign

Route19_MapEvents::
	map_events Route19_ObjectEvents, NULL, NULL, Route19_MapBGEvents

@ ===== END data/maps/Route19/events.inc =====
@ ===== BEGIN data/maps/Route20/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route20/map.json
@

	.align 2

Route20_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_SWIMMER_F_WATER, 8, 11, 1, MOVEMENT_TYPE_FACE_DOWN_AND_UP, 1, 1, TRAINER_TYPE_NORMAL, 3, Route20_EventScript_Melissa, 0
	object_event 2, OBJ_EVENT_GFX_PICNICKER, 16, 14, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 1, Route20_EventScript_Missy, 0
	object_event 3, OBJ_EVENT_GFX_SWIMMER_F_WATER, 34, 7, 1, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 4, Route20_EventScript_Nora, 0
	object_event 4, OBJ_EVENT_GFX_ROCKER, 43, 9, 3, MOVEMENT_TYPE_WANDER_AROUND, 1, 1, TRAINER_TYPE_NORMAL, 1, Route20_EventScript_Roger, 0
	object_event 5, OBJ_EVENT_GFX_SWIMMER_M_WATER, 23, 10, 1, MOVEMENT_TYPE_WALK_SEQUENCE_RIGHT_DOWN_LEFT_UP, 5, 4, TRAINER_TYPE_NORMAL, 1, Route20_EventScript_Dean, 0
	object_event 6, OBJ_EVENT_GFX_PICNICKER, 73, 16, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NORMAL, 2, Route20_EventScript_Irene, 0
	object_event 7, OBJ_EVENT_GFX_SWIMMER_M_WATER, 111, 9, 1, MOVEMENT_TYPE_WALK_SEQUENCE_UP_LEFT_DOWN_RIGHT, 5, 3, TRAINER_TYPE_NORMAL, 1, Route20_EventScript_Barry, 0
	object_event 8, OBJ_EVENT_GFX_SWIMMER_M_WATER, 106, 11, 1, MOVEMENT_TYPE_WALK_SEQUENCE_DOWN_LEFT_UP_RIGHT, 5, 3, TRAINER_TYPE_NORMAL, 1, Route20_EventScript_Darrin, 0
	object_event 9, OBJ_EVENT_GFX_SWIMMER_F_WATER, 93, 10, 1, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NORMAL, 5, Route20_EventScript_Shirley, 0
	object_event 10, OBJ_EVENT_GFX_SWIMMER_F_WATER, 54, 11, 1, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NORMAL, 1, Route20_EventScript_Tiffany, 0
	object_event 11, OBJ_EVENT_GFX_CAMPER, 69, 3, 3, MOVEMENT_TYPE_WANDER_LEFT_AND_RIGHT, 2, 1, TRAINER_TYPE_NONE, 0, Route20_EventScript_Camper, 0

Route20_MapWarps:
	warp_def 60, 8, 3, 3, MAP_SEAFOAM_ISLANDS_1F
	warp_def 72, 14, 3, 4, MAP_SEAFOAM_ISLANDS_1F

Route20_MapBGEvents:
	bg_sign_event 68, 14, 0, BG_EVENT_PLAYER_FACING_ANY, Route20_EventScript_SeafoamIslandsSign
	bg_sign_event 64, 8, 0, BG_EVENT_PLAYER_FACING_ANY, Route20_EventScript_SeafoamIslandsSign
	bg_hidden_item_event 23, 6, 3, ITEM_STARDUST, FLAG_HIDDEN_ITEM_ROUTE20_STARDUST, 1, FALSE

Route20_MapEvents::
	map_events Route20_ObjectEvents, Route20_MapWarps, NULL, Route20_MapBGEvents

@ ===== END data/maps/Route20/events.inc =====
@ ===== BEGIN data/maps/Route21_North/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route21_North/map.json
@

	.align 2

Route21_North_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_FISHER, 7, 27, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NORMAL, 0, Route21_North_EventScript_Ronald, 0
	object_event 2, OBJ_EVENT_GFX_FISHER, 16, 26, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 0, Route21_North_EventScript_Wade, 0
	object_event 3, OBJ_EVENT_GFX_SWIMMER_M_WATER, 12, 44, 1, MOVEMENT_TYPE_WALK_SEQUENCE_LEFT_UP_RIGHT_DOWN, 4, 2, TRAINER_TYPE_NORMAL, 1, Route21_North_EventScript_Spencer, 0
	object_event 4, OBJ_EVENT_GFX_SWIMMER_F_WATER, 14, 35, 1, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 1, Route21_North_EventScript_Lil, 0
	object_event 5, OBJ_EVENT_GFX_TUBER_M_WATER, 15, 35, 1, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 1, Route21_North_EventScript_Ian, 0
	clone_event 6, OBJ_EVENT_GFX_FAT_MAN, 13, -3, LOCALID_PALLET_FAT_MAN, MAP_PALLET_TOWN

Route21_North_MapBGEvents:
	bg_hidden_item_event 17, 42, 3, ITEM_PEARL, FLAG_HIDDEN_ITEM_ROUTE21_NORTH_PEARL, 1, FALSE

Route21_North_MapEvents::
	map_events Route21_North_ObjectEvents, NULL, NULL, Route21_North_MapBGEvents

@ ===== END data/maps/Route21_North/events.inc =====
@ ===== BEGIN data/maps/Route21_South/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route21_South/map.json
@

	.align 2

Route21_South_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_FISHER, 11, 8, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 0, Route21_South_EventScript_Claude, 0
	object_event 2, OBJ_EVENT_GFX_FISHER, 14, 15, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NORMAL, 0, Route21_South_EventScript_Nolan, 0
	object_event 3, OBJ_EVENT_GFX_SWIMMER_M_WATER, 15, 24, 1, MOVEMENT_TYPE_FACE_LEFT_AND_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 3, Route21_South_EventScript_Jack, 0
	object_event 4, OBJ_EVENT_GFX_SWIMMER_M_WATER, 15, 38, 1, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NORMAL, 3, Route21_South_EventScript_Jerome, 0
	object_event 5, OBJ_EVENT_GFX_SWIMMER_M_WATER, 10, 29, 1, MOVEMENT_TYPE_WANDER_AROUND, 2, 2, TRAINER_TYPE_NORMAL, 4, Route21_South_EventScript_Roland, 0

Route21_South_MapEvents::
	map_events Route21_South_ObjectEvents, NULL, NULL, NULL

@ ===== END data/maps/Route21_South/events.inc =====
@ ===== BEGIN data/maps/Route22/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route22/map.json
@

	.align 2

Route22_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_BLUE, 25, 4, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, 0x0, FLAG_HIDE_ROUTE_22_RIVAL

Route22_MapWarps:
	warp_def 8, 5, 0, 2, MAP_ROUTE22_NORTH_ENTRANCE
	warp_def 9, 5, 0, 2, MAP_ROUTE22_NORTH_ENTRANCE

Route22_MapCoordEvents:
	coord_event 33, 4, 3, VAR_MAP_SCENE_ROUTE22, 1, Route22_EventScript_EarlyRivalTriggerTop
	coord_event 33, 5, 3, VAR_MAP_SCENE_ROUTE22, 1, Route22_EventScript_EarlyRivalTriggerMid
	coord_event 33, 6, 0, VAR_MAP_SCENE_ROUTE22, 1, Route22_EventScript_EarlyRivalTriggerBottom
	coord_event 33, 4, 3, VAR_MAP_SCENE_ROUTE22, 3, Route22_EventScript_LateRivalTriggerTop
	coord_event 33, 5, 3, VAR_MAP_SCENE_ROUTE22, 3, Route22_EventScript_LateRivalTriggerMid
	coord_event 33, 6, 0, VAR_MAP_SCENE_ROUTE22, 3, Route22_EventScript_LateRivalTriggerBottom

Route22_MapBGEvents:
	bg_sign_event 7, 12, 0, BG_EVENT_PLAYER_FACING_ANY, Route22_EventScript_LeagueGateSign

Route22_MapEvents::
	map_events Route22_ObjectEvents, Route22_MapWarps, Route22_MapCoordEvents, Route22_MapBGEvents

@ ===== END data/maps/Route22/events.inc =====
@ ===== BEGIN data/maps/Route23/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route23/map.json
@

	.align 2

Route23_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_POLICEMAN, 15, 149, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, Route23_EventScript_CascadeBadgeGuard, 0
	object_event 2, OBJ_EVENT_GFX_POLICEMAN, 8, 140, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, Route23_EventScript_ThunderBadgeGuard, 0
	object_event 3, OBJ_EVENT_GFX_POLICEMAN, 14, 123, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, Route23_EventScript_RainbowBadgeGuard, 0
	object_event 4, OBJ_EVENT_GFX_POLICEMAN, 16, 112, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, Route23_EventScript_SoulBadgeGuard, 0
	object_event 5, OBJ_EVENT_GFX_POLICEMAN, 10, 94, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, Route23_EventScript_MarshBadgeGuard, 0
	object_event 6, OBJ_EVENT_GFX_POLICEMAN, 14, 61, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, Route23_EventScript_VolcanoBadgeGuard, 0
	object_event 7, OBJ_EVENT_GFX_POLICEMAN, 6, 35, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, Route23_EventScript_EarthBadgeGuard, 0

Route23_MapWarps:
	warp_def 5, 28, 3, 1, MAP_VICTORY_ROAD_1F
	warp_def 18, 28, 3, 6, MAP_VICTORY_ROAD_2F
	warp_def 8, 153, 3, 0, MAP_ROUTE22_NORTH_ENTRANCE
	warp_def 9, 154, 0, 0, MAP_ROUTE22_NORTH_ENTRANCE

Route23_MapCoordEvents:
	coord_event 13, 149, 3, VAR_MAP_SCENE_ROUTE23, 1, Route23_EventScript_CascadeBadgeGuardTrigger
	coord_event 7, 140, 3, VAR_MAP_SCENE_ROUTE23, 2, Route23_EventScript_ThunderBadgeGuardTrigger
	coord_event 12, 123, 3, VAR_MAP_SCENE_ROUTE23, 3, Route23_EventScript_RainbowBadgeGuardTrigger
	coord_event 11, 111, 0, VAR_MAP_SCENE_ROUTE23, 4, Route23_EventScript_SoulBadgeGuardTrigger
	coord_event 9, 94, 1, VAR_MAP_SCENE_ROUTE23, 5, Route23_EventScript_MarshBadgeGuardTrigger
	coord_event 12, 61, 3, VAR_MAP_SCENE_ROUTE23, 6, Route23_EventScript_VolcanoBadgeGuardTrigger
	coord_event 1, 35, 0, VAR_MAP_SCENE_ROUTE23, 7, Route23_EventScript_EarthBadgeGuardTrigger
	coord_event 1, 34, 0, VAR_MAP_SCENE_ROUTE23, 7, Route23_EventScript_EarthBadgeGuardTrigger
	coord_event 1, 32, 3, VAR_MAP_SCENE_ROUTE23, 7, Route23_EventScript_EarthBadgeGuardTrigger
	coord_event 1, 33, 0, VAR_MAP_SCENE_ROUTE23, 7, Route23_EventScript_EarthBadgeGuardTrigger
	coord_event 1, 31, 0, VAR_MAP_SCENE_ROUTE23, 7, Route23_EventScript_EarthBadgeGuardTrigger
	coord_event 1, 36, 0, VAR_MAP_SCENE_ROUTE23, 7, Route23_EventScript_EarthBadgeGuardTrigger
	coord_event 5, 35, 3, VAR_MAP_SCENE_ROUTE23, 7, Route23_EventScript_EarthBadgeGuardTrigger
	coord_event 4, 35, 3, VAR_MAP_SCENE_ROUTE23, 7, Route23_EventScript_EarthBadgeGuardTrigger
	coord_event 10, 60, 0, VAR_MAP_SCENE_ROUTE23, 6, Route23_EventScript_VolcanoBadgeGuardTrigger
	coord_event 13, 61, 3, VAR_MAP_SCENE_ROUTE23, 6, Route23_EventScript_VolcanoBadgeGuardTrigger
	coord_event 11, 60, 0, VAR_MAP_SCENE_ROUTE23, 6, Route23_EventScript_VolcanoBadgeGuardTrigger
	coord_event 8, 94, 1, VAR_MAP_SCENE_ROUTE23, 5, Route23_EventScript_MarshBadgeGuardTrigger
	coord_event 5, 92, 1, VAR_MAP_SCENE_ROUTE23, 5, Route23_EventScript_MarshBadgeGuardTrigger
	coord_event 7, 94, 1, VAR_MAP_SCENE_ROUTE23, 5, Route23_EventScript_MarshBadgeGuardTrigger
	coord_event 4, 92, 1, VAR_MAP_SCENE_ROUTE23, 5, Route23_EventScript_MarshBadgeGuardTrigger
	coord_event 3, 92, 1, VAR_MAP_SCENE_ROUTE23, 5, Route23_EventScript_MarshBadgeGuardTrigger
	coord_event 2, 92, 1, VAR_MAP_SCENE_ROUTE23, 5, Route23_EventScript_MarshBadgeGuardTrigger
	coord_event 4, 139, 0, VAR_MAP_SCENE_ROUTE23, 2, Route23_EventScript_ThunderBadgeGuardTrigger
	coord_event 5, 139, 0, VAR_MAP_SCENE_ROUTE23, 2, Route23_EventScript_ThunderBadgeGuardTrigger
	coord_event 6, 140, 3, VAR_MAP_SCENE_ROUTE23, 2, Route23_EventScript_ThunderBadgeGuardTrigger
	coord_event 10, 122, 0, VAR_MAP_SCENE_ROUTE23, 3, Route23_EventScript_RainbowBadgeGuardTrigger
	coord_event 11, 122, 0, VAR_MAP_SCENE_ROUTE23, 3, Route23_EventScript_RainbowBadgeGuardTrigger
	coord_event 13, 123, 3, VAR_MAP_SCENE_ROUTE23, 3, Route23_EventScript_RainbowBadgeGuardTrigger
	coord_event 8, 109, 1, VAR_MAP_SCENE_ROUTE23, 4, Route23_EventScript_SoulBadgeGuardTrigger
	coord_event 9, 109, 1, VAR_MAP_SCENE_ROUTE23, 4, Route23_EventScript_SoulBadgeGuardTrigger
	coord_event 10, 109, 1, VAR_MAP_SCENE_ROUTE23, 4, Route23_EventScript_SoulBadgeGuardTrigger
	coord_event 11, 109, 1, VAR_MAP_SCENE_ROUTE23, 4, Route23_EventScript_SoulBadgeGuardTrigger
	coord_event 12, 109, 1, VAR_MAP_SCENE_ROUTE23, 4, Route23_EventScript_SoulBadgeGuardTrigger
	coord_event 12, 111, 0, VAR_MAP_SCENE_ROUTE23, 4, Route23_EventScript_SoulBadgeGuardTrigger
	coord_event 14, 112, 1, VAR_MAP_SCENE_ROUTE23, 4, Route23_EventScript_SoulBadgeGuardTrigger
	coord_event 13, 112, 1, VAR_MAP_SCENE_ROUTE23, 4, Route23_EventScript_SoulBadgeGuardTrigger
	coord_event 15, 112, 1, VAR_MAP_SCENE_ROUTE23, 4, Route23_EventScript_SoulBadgeGuardTrigger
	coord_event 12, 148, 0, VAR_MAP_SCENE_ROUTE23, 1, Route23_EventScript_CascadeBadgeGuardTrigger
	coord_event 11, 148, 0, VAR_MAP_SCENE_ROUTE23, 1, Route23_EventScript_CascadeBadgeGuardTrigger
	coord_event 14, 149, 3, VAR_MAP_SCENE_ROUTE23, 1, Route23_EventScript_CascadeBadgeGuardTrigger
	coord_event 10, 148, 0, VAR_MAP_SCENE_ROUTE23, 1, Route23_EventScript_CascadeBadgeGuardTrigger

Route23_MapBGEvents:
	bg_hidden_item_event 19, 42, 0, ITEM_FULL_RESTORE, FLAG_HIDDEN_ITEM_ROUTE23_FULL_RESTORE, 1, FALSE
	bg_hidden_item_event 20, 72, 0, ITEM_ULTRA_BALL, FLAG_HIDDEN_ITEM_ROUTE23_ULTRA_BALL, 1, FALSE
	bg_hidden_item_event 11, 101, 3, ITEM_MAX_ETHER, FLAG_HIDDEN_ITEM_ROUTE23_MAX_ETHER, 1, FALSE
	bg_hidden_item_event 3, 18, 3, ITEM_LUM_BERRY, FLAG_HIDDEN_ITEM_ROUTE23_LUM_BERRY, 1, FALSE
	bg_hidden_item_event 2, 29, 3, ITEM_SITRUS_BERRY, FLAG_HIDDEN_ITEM_ROUTE23_SITRUS_BERRY, 1, FALSE
	bg_hidden_item_event 10, 67, 3, ITEM_ASPEAR_BERRY, FLAG_HIDDEN_ITEM_ROUTE23_ASPEAR_BERRY, 1, FALSE
	bg_hidden_item_event 3, 128, 3, ITEM_LEPPA_BERRY, FLAG_HIDDEN_ITEM_ROUTE23_LEPPA_BERRY, 1, FALSE
	bg_hidden_item_event 9, 8, 3, ITEM_MAX_ELIXIR, FLAG_HIDDEN_ITEM_ROUTE23_MAX_ELIXIR, 1, FALSE
	bg_sign_event 3, 31, 0, BG_EVENT_PLAYER_FACING_ANY, Route23_EventScript_VictoryRoadGateSign

Route23_MapEvents::
	map_events Route23_ObjectEvents, Route23_MapWarps, Route23_MapCoordEvents, Route23_MapBGEvents

@ ===== END data/maps/Route23/events.inc =====
@ ===== BEGIN data/maps/Route24/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route24/map.json
@

	.align 2

Route24_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_MAN, 12, 15, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NONE, 0, Route24_EventScript_Rocket, FLAG_HIDE_NUGGET_BRIDGE_ROCKET
	object_event 2, OBJ_EVENT_GFX_CAMPER, 12, 19, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NORMAL, 2, Route24_EventScript_Ethan, 0
	object_event 3, OBJ_EVENT_GFX_LASS, 10, 22, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 2, Route24_EventScript_Reli, 0
	object_event 4, OBJ_EVENT_GFX_YOUNGSTER, 12, 25, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NORMAL, 2, Route24_EventScript_Timmy, 0
	object_event 5, OBJ_EVENT_GFX_LASS, 10, 28, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 2, Route24_EventScript_Ali, 0
	object_event 6, OBJ_EVENT_GFX_BUG_CATCHER, 12, 31, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NORMAL, 2, Route24_EventScript_Cale, 0
	object_event 7, OBJ_EVENT_GFX_CAMPER, 5, 21, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NORMAL, 5, Route24_EventScript_Shane, 0
	object_event 8, OBJ_EVENT_GFX_ITEM_BALL, 11, 4, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, Route24_EventScript_ItemTM45, FLAG_HIDE_ROUTE24_TM45

Route24_MapCoordEvents:
	coord_event 10, 15, 3, VAR_MAP_SCENE_ROUTE24, 0, Route24_EventScript_RocketTriggerLeft
	coord_event 11, 15, 3, VAR_MAP_SCENE_ROUTE24, 0, Route24_EventScript_RocketTriggerRight

Route24_MapBGEvents:
	bg_hidden_item_event 19, 4, 3, ITEM_PECHA_BERRY, FLAG_HIDDEN_ITEM_ROUTE24_PECHA_BERRY, 1, FALSE

Route24_MapEvents::
	map_events Route24_ObjectEvents, NULL, Route24_MapCoordEvents, Route24_MapBGEvents

@ ===== END data/maps/Route24/events.inc =====
@ ===== BEGIN data/maps/Route25/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route25/map.json
@

	.align 2

Route25_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_HIKER, 11, 4, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 4, Route25_EventScript_Franklin, 0
	object_event 2, OBJ_EVENT_GFX_YOUNGSTER, 18, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 2, Route25_EventScript_Joey, 0
	object_event 3, OBJ_EVENT_GFX_HIKER, 17, 7, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 2, Route25_EventScript_Wayne, 0
	object_event 4, OBJ_EVENT_GFX_YOUNGSTER, 22, 4, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NORMAL, 2, Route25_EventScript_Dan, 0
	object_event 5, OBJ_EVENT_GFX_PICNICKER, 22, 8, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 2, Route25_EventScript_Kelsey, 0
	object_event 6, OBJ_EVENT_GFX_HIKER, 27, 9, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NORMAL, 3, Route25_EventScript_Nob, 0
	object_event 7, OBJ_EVENT_GFX_CAMPER, 28, 4, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 3, Route25_EventScript_Flint, 0
	object_event 8, OBJ_EVENT_GFX_YOUNGSTER, 36, 4, 3, MOVEMENT_TYPE_WALK_DOWN_AND_UP, 1, 3, TRAINER_TYPE_NORMAL, 2, Route25_EventScript_Chad, 0
	object_event 9, OBJ_EVENT_GFX_LASS, 42, 5, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 3, Route25_EventScript_Haley, 0
	object_event 10, OBJ_EVENT_GFX_ITEM_BALL, 26, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, Route25_EventScript_ItemTM43, FLAG_HIDE_ROUTE25_TM43
	object_event 11, OBJ_EVENT_GFX_CUT_TREE, 30, 3, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_CutTree, FLAG_TEMP_12
	object_event 12, OBJ_EVENT_GFX_BEAUTY, 49, 10, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NONE, 0, Route25_EventScript_Beauty, 0
	object_event 13, OBJ_EVENT_GFX_MAN, 49, 11, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NONE, 0, Route25_EventScript_Man, 0

Route25_MapWarps:
	warp_def 51, 4, 0, 1, MAP_ROUTE25_SEA_COTTAGE

Route25_MapBGEvents:
	bg_sign_event 48, 4, 0, BG_EVENT_PLAYER_FACING_ANY, Route25_EventScript_SeaCottageSign
	bg_hidden_item_event 14, 2, 3, ITEM_ELIXIR, FLAG_HIDDEN_ITEM_ROUTE25_ELIXIR, 1, FALSE
	bg_hidden_item_event 58, 6, 3, ITEM_ETHER, FLAG_HIDDEN_ITEM_ROUTE25_ETHER, 1, FALSE
	bg_hidden_item_event 33, 8, 3, ITEM_ORAN_BERRY, FLAG_HIDDEN_ITEM_ROUTE25_ORAN_BERRY, 1, FALSE
	bg_hidden_item_event 40, 3, 3, ITEM_BLUK_BERRY, FLAG_HIDDEN_ITEM_ROUTE25_BLUK_BERRY, 1, FALSE

Route25_MapEvents::
	map_events Route25_ObjectEvents, Route25_MapWarps, NULL, Route25_MapBGEvents

@ ===== END data/maps/Route25/events.inc =====
@ ===== BEGIN data/maps/OneIsland_KindleRoad/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/OneIsland_KindleRoad/map.json
@

	.align 2

OneIsland_KindleRoad_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_SWIMMER_F_WATER, 11, 32, 1, MOVEMENT_TYPE_FACE_LEFT_AND_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 4, OneIsland_KindleRoad_EventScript_Maria, 0
	object_event 2, OBJ_EVENT_GFX_SWIMMER_F_LAND, 17, 132, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 2, OneIsland_KindleRoad_EventScript_Abigail, 0
	object_event 3, OBJ_EVENT_GFX_SWIMMER_M_WATER, 7, 39, 1, MOVEMENT_TYPE_WALK_SEQUENCE_RIGHT_DOWN_LEFT_UP, 6, 3, TRAINER_TYPE_NORMAL, 1, OneIsland_KindleRoad_EventScript_Finn, 0
	object_event 4, OBJ_EVENT_GFX_SWIMMER_M_LAND, 19, 79, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 1, OneIsland_KindleRoad_EventScript_Garrett, 0
	object_event 5, OBJ_EVENT_GFX_FISHER, 15, 25, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NORMAL, 0, OneIsland_KindleRoad_EventScript_Tommy, 0
	object_event 6, OBJ_EVENT_GFX_CRUSH_GIRL, 9, 53, 3, MOVEMENT_TYPE_WALK_DOWN_AND_UP, 1, 7, TRAINER_TYPE_NORMAL, 1, OneIsland_KindleRoad_EventScript_Sharon, 0
	object_event 7, OBJ_EVENT_GFX_CRUSH_GIRL, 18, 105, 4, MOVEMENT_TYPE_WALK_SEQUENCE_DOWN_LEFT_UP_RIGHT, 1, 4, TRAINER_TYPE_NORMAL, 1, OneIsland_KindleRoad_EventScript_Tanya, 0
	object_event 8, OBJ_EVENT_GFX_BLACK_BELT, 16, 64, 3, MOVEMENT_TYPE_WALK_LEFT_AND_RIGHT, 2, 1, TRAINER_TYPE_NORMAL, 1, OneIsland_KindleRoad_EventScript_Shea, 0
	object_event 9, OBJ_EVENT_GFX_BLACK_BELT, 11, 64, 3, MOVEMENT_TYPE_WALK_RIGHT_AND_LEFT, 2, 1, TRAINER_TYPE_NORMAL, 1, OneIsland_KindleRoad_EventScript_Hugh, 0
	object_event 10, OBJ_EVENT_GFX_CAMPER, 11, 89, 3, MOVEMENT_TYPE_FACE_LEFT_AND_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 3, OneIsland_KindleRoad_EventScript_Bryce, 0
	object_event 11, OBJ_EVENT_GFX_PICNICKER, 9, 108, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NORMAL, 1, OneIsland_KindleRoad_EventScript_Claire, 0
	object_event 12, OBJ_EVENT_GFX_BLACK_BELT, 8, 68, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 1, OneIsland_KindleRoad_EventScript_Mik, 0
	object_event 13, OBJ_EVENT_GFX_CRUSH_GIRL, 9, 68, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 1, OneIsland_KindleRoad_EventScript_Kia, 0
	object_event 14, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 8, 104, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_13
	object_event 15, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 11, 95, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_15
	object_event 16, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 12, 96, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_16
	object_event 17, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 10, 95, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_17
	object_event 18, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 9, 105, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_18
	object_event 19, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 15, 75, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_19
	object_event 20, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 9, 84, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_1A
	object_event 21, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 15, 74, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_1B
	object_event 22, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 15, 73, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_1C
	object_event 23, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 18, 111, 4, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_1D
	object_event 24, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 10, 86, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_1E
	object_event 25, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 9, 110, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_1F
	object_event 26, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 18, 112, 4, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_11
	object_event 27, OBJ_EVENT_GFX_ITEM_BALL, 15, 70, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, OneIsland_KindleRoad_EventScript_ItemEther, FLAG_HIDE_ONE_ISLAND_KINDLE_ROAD_ETHER
	object_event 28, OBJ_EVENT_GFX_ITEM_BALL, 17, 103, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, OneIsland_KindleRoad_EventScript_ItemMaxRepel, FLAG_HIDE_ONE_ISLAND_KINDLE_ROAD_MAX_REPEL
	object_event 29, OBJ_EVENT_GFX_ITEM_BALL, 18, 114, 4, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, OneIsland_KindleRoad_EventScript_ItemCarbos, FLAG_HIDE_ONE_ISLAND_KINDLE_ROAD_CARBOS

OneIsland_KindleRoad_MapWarps:
	warp_def 11, 6, 3, 0, MAP_MT_EMBER_EXTERIOR
	warp_def 12, 6, 3, 1, MAP_MT_EMBER_EXTERIOR
	warp_def 15, 58, 3, 0, MAP_ONE_ISLAND_KINDLE_ROAD_EMBER_SPA

OneIsland_KindleRoad_MapBGEvents:
	bg_sign_event 13, 59, 0, BG_EVENT_PLAYER_FACING_ANY, OneIsland_KindleRoad_EventScript_EmberSpaSign
	bg_sign_event 8, 115, 0, BG_EVENT_PLAYER_FACING_ANY, OneIsland_KindleRoad_EventScript_RouteSign

OneIsland_KindleRoad_MapEvents::
	map_events OneIsland_KindleRoad_ObjectEvents, OneIsland_KindleRoad_MapWarps, NULL, OneIsland_KindleRoad_MapBGEvents

@ ===== END data/maps/OneIsland_KindleRoad/events.inc =====
@ ===== BEGIN data/maps/OneIsland_TreasureBeach/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/OneIsland_TreasureBeach/map.json
@

	.align 2

OneIsland_TreasureBeach_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_SWIMMER_F_WATER, 8, 11, 1, MOVEMENT_TYPE_WANDER_AROUND, 2, 1, TRAINER_TYPE_NORMAL, 1, OneIsland_TreasureBeach_EventScript_Amara, 0
	object_event 2, OBJ_EVENT_GFX_BOY, 13, 20, 3, MOVEMENT_TYPE_WANDER_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, OneIsland_TreasureBeach_EventScript_Boy, 0

OneIsland_TreasureBeach_MapBGEvents:
	bg_hidden_item_event 8, 20, 3, ITEM_STARDUST, FLAG_HIDDEN_ITEM_ONE_ISLAND_TREASURE_BEACH_STARDUST, 1, FALSE
	bg_hidden_item_event 13, 27, 3, ITEM_STARDUST, FLAG_HIDDEN_ITEM_ONE_ISLAND_TREASURE_BEACH_STARDUST_2, 1, FALSE
	bg_hidden_item_event 11, 31, 3, ITEM_PEARL, FLAG_HIDDEN_ITEM_ONE_ISLAND_TREASURE_BEACH_PEARL, 1, FALSE
	bg_hidden_item_event 9, 34, 3, ITEM_PEARL, FLAG_HIDDEN_ITEM_ONE_ISLAND_TREASURE_BEACH_PEARL_2, 1, FALSE
	bg_hidden_item_event 15, 22, 3, ITEM_ULTRA_BALL, FLAG_HIDDEN_ITEM_ONE_ISLAND_TREASURE_BEACH_ULTRA_BALL, 1, FALSE
	bg_hidden_item_event 16, 33, 3, ITEM_ULTRA_BALL, FLAG_HIDDEN_ITEM_ONE_ISLAND_TREASURE_BEACH_ULTRA_BALL_2, 1, FALSE
	bg_hidden_item_event 15, 29, 3, ITEM_STAR_PIECE, FLAG_HIDDEN_ITEM_ONE_ISLAND_TREASURE_BEACH_STAR_PIECE, 1, FALSE
	bg_hidden_item_event 8, 27, 3, ITEM_BIG_PEARL, FLAG_HIDDEN_ITEM_ONE_ISLAND_TREASURE_BEACH_BIG_PEARL, 1, FALSE

OneIsland_TreasureBeach_MapEvents::
	map_events OneIsland_TreasureBeach_ObjectEvents, NULL, NULL, OneIsland_TreasureBeach_MapBGEvents

@ ===== END data/maps/OneIsland_TreasureBeach/events.inc =====
@ ===== BEGIN data/maps/TwoIsland_CapeBrink/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/TwoIsland_CapeBrink/map.json
@

	.align 2

TwoIsland_CapeBrink_MapWarps:
	warp_def 12, 16, 0, 0, MAP_TWO_ISLAND_CAPE_BRINK_HOUSE

TwoIsland_CapeBrink_MapBGEvents:
	bg_hidden_item_event 16, 28, 3, ITEM_PP_MAX, FLAG_HIDDEN_ITEM_TWO_ISLAND_CAPE_BRINK_PP_MAX, 1, TRUE
	bg_hidden_item_event 15, 13, 3, ITEM_RARE_CANDY, FLAG_HIDDEN_ITEM_TWO_ISLAND_CAPE_BRINK_RARE_CANDY, 1, FALSE

TwoIsland_CapeBrink_MapEvents::
	map_events NULL, TwoIsland_CapeBrink_MapWarps, NULL, TwoIsland_CapeBrink_MapBGEvents

@ ===== END data/maps/TwoIsland_CapeBrink/events.inc =====
@ ===== BEGIN data/maps/ThreeIsland_BondBridge/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/ThreeIsland_BondBridge/map.json
@

	.align 2

ThreeIsland_BondBridge_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_WOMAN_2, 27, 10, 3, MOVEMENT_TYPE_WANDER_AROUND, 1, 1, TRAINER_TYPE_NORMAL, 5, ThreeIsland_BondBridge_EventScript_Nikki, 0
	object_event 2, OBJ_EVENT_GFX_WOMAN_2, 68, 10, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NORMAL, 2, ThreeIsland_BondBridge_EventScript_Violet, 0
	object_event 3, OBJ_EVENT_GFX_TUBER_F, 33, 13, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 1, ThreeIsland_BondBridge_EventScript_Amira, 0
	object_event 4, OBJ_EVENT_GFX_TUBER_F, 50, 11, 3, MOVEMENT_TYPE_WALK_LEFT_AND_RIGHT, 2, 1, TRAINER_TYPE_NORMAL, 1, ThreeIsland_BondBridge_EventScript_Alexis, 0
	object_event 5, OBJ_EVENT_GFX_SWIMMER_F_WATER, 36, 4, 1, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NORMAL, 1, ThreeIsland_BondBridge_EventScript_Tisha, 0
	object_event 6, OBJ_EVENT_GFX_LITTLE_GIRL, 77, 5, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 1, ThreeIsland_BondBridge_EventScript_Joy, 0
	object_event 7, OBJ_EVENT_GFX_LITTLE_GIRL, 78, 5, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 1, ThreeIsland_BondBridge_EventScript_Meg, 0
	object_event 8, OBJ_EVENT_GFX_CUT_TREE, 72, 8, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_CutTree, FLAG_TEMP_12
	object_event 9, OBJ_EVENT_GFX_CUT_TREE, 86, 13, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_CutTree, FLAG_TEMP_13

ThreeIsland_BondBridge_MapWarps:
	warp_def 12, 6, 3, 0, MAP_THREE_ISLAND_BERRY_FOREST
	warp_def 13, 6, 3, 0, MAP_THREE_ISLAND_BERRY_FOREST

ThreeIsland_BondBridge_MapBGEvents:
	bg_sign_event 14, 7, 0, BG_EVENT_PLAYER_FACING_ANY, ThreeIsland_BondBridge_EventScript_BerryForestSign
	bg_hidden_item_event 61, 5, 0, ITEM_MAX_REPEL, FLAG_HIDDEN_ITEM_THREE_ISLAND_BOND_BRIDGE_MAX_REPEL, 1, FALSE
	bg_hidden_item_event 44, 12, 3, ITEM_PEARL, FLAG_HIDDEN_ITEM_THREE_ISLAND_BOND_BRIDGE_PEARL, 1, FALSE
	bg_hidden_item_event 33, 7, 3, ITEM_STARDUST, FLAG_HIDDEN_ITEM_THREE_ISLAND_BOND_BRIDGE_STARDUST, 1, FALSE
	bg_sign_event 91, 9, 0, BG_EVENT_PLAYER_FACING_ANY, ThreeIsland_BondBridge_EventScript_BondBridgeSign

ThreeIsland_BondBridge_MapEvents::
	map_events ThreeIsland_BondBridge_ObjectEvents, ThreeIsland_BondBridge_MapWarps, NULL, ThreeIsland_BondBridge_MapBGEvents

@ ===== END data/maps/ThreeIsland_BondBridge/events.inc =====
@ ===== BEGIN data/maps/ThreeIsland_Port/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/ThreeIsland_Port/map.json
@

	.align 2

ThreeIsland_Port_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_WOMAN_3, 14, 9, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, ThreeIsland_Port_EventScript_Woman, 0
	object_event 2, OBJ_EVENT_GFX_BIKER, 8, 8, 3, MOVEMENT_TYPE_WALK_RIGHT_AND_LEFT, 3, 1, TRAINER_TYPE_NONE, 0, ThreeIsland_Port_EventScript_Biker1, FLAG_HIDE_THREE_ISLAND_BIKERS
	object_event 3, OBJ_EVENT_GFX_BIKER, 13, 10, 3, MOVEMENT_TYPE_WALK_SEQUENCE_UP_RIGHT_DOWN_LEFT, 2, 2, TRAINER_TYPE_NONE, 0, ThreeIsland_Port_EventScript_Biker2, FLAG_HIDE_THREE_ISLAND_BIKERS

ThreeIsland_Port_MapWarps:
	warp_def 16, 4, 0, 0, MAP_THREE_ISLAND_DUNSPARCE_TUNNEL
	warp_def 38, 5, 3, 1, MAP_THREE_ISLAND_DUNSPARCE_TUNNEL
	warp_def 12, 13, 3, 0, MAP_THREE_ISLAND_HARBOR

ThreeIsland_Port_MapEvents::
	map_events ThreeIsland_Port_ObjectEvents, ThreeIsland_Port_MapWarps, NULL, NULL

@ ===== END data/maps/ThreeIsland_Port/events.inc =====
@ ===== BEGIN data/maps/Prototype_SeviiIsle_6/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Prototype_SeviiIsle_6/map.json
@

	.align 2

Prototype_SeviiIsle_6_MapEvents::
	map_events NULL, NULL, NULL, NULL

@ ===== END data/maps/Prototype_SeviiIsle_6/events.inc =====
@ ===== BEGIN data/maps/Prototype_SeviiIsle_7/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Prototype_SeviiIsle_7/map.json
@

	.align 2

Prototype_SeviiIsle_7_MapEvents::
	map_events NULL, NULL, NULL, NULL

@ ===== END data/maps/Prototype_SeviiIsle_7/events.inc =====
@ ===== BEGIN data/maps/Prototype_SeviiIsle_8/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Prototype_SeviiIsle_8/map.json
@

	.align 2

Prototype_SeviiIsle_8_MapEvents::
	map_events NULL, NULL, NULL, NULL

@ ===== END data/maps/Prototype_SeviiIsle_8/events.inc =====
@ ===== BEGIN data/maps/Prototype_SeviiIsle_9/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Prototype_SeviiIsle_9/map.json
@

	.align 2

Prototype_SeviiIsle_9_MapEvents::
	map_events NULL, NULL, NULL, NULL

@ ===== END data/maps/Prototype_SeviiIsle_9/events.inc =====
@ ===== BEGIN data/maps/FiveIsland_ResortGorgeous/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FiveIsland_ResortGorgeous/map.json
@

	.align 2

FiveIsland_ResortGorgeous_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_LASS, 44, 10, 3, MOVEMENT_TYPE_FACE_DOWN_AND_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 3, FiveIsland_ResortGorgeous_EventScript_Daisy, 0
	object_event 2, OBJ_EVENT_GFX_LASS, 33, 12, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NORMAL, 4, FiveIsland_ResortGorgeous_EventScript_Celina, 0
	object_event 3, OBJ_EVENT_GFX_LASS, 12, 10, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 1, FiveIsland_ResortGorgeous_EventScript_Rayna, 0
	object_event 4, OBJ_EVENT_GFX_WOMAN_2, 23, 9, 3, MOVEMENT_TYPE_WANDER_AROUND, 2, 1, TRAINER_TYPE_NORMAL, 1, FiveIsland_ResortGorgeous_EventScript_Jacki, 0
	object_event 5, OBJ_EVENT_GFX_WOMAN_2, 33, 8, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 1, FiveIsland_ResortGorgeous_EventScript_Gillian, 0
	object_event 6, OBJ_EVENT_GFX_YOUNGSTER, 33, 3, 3, MOVEMENT_TYPE_WALK_SEQUENCE_DOWN_RIGHT_UP_LEFT, 10, 1, TRAINER_TYPE_NORMAL, 1, FiveIsland_ResortGorgeous_EventScript_Destin, 0
	object_event 7, OBJ_EVENT_GFX_SWIMMER_M_WATER, 56, 7, 1, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NORMAL, 1, FiveIsland_ResortGorgeous_EventScript_Toby, 0
	object_event 8, OBJ_EVENT_GFX_WOMAN_2, 39, 9, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, 0x0, FLAG_HIDE_RESORT_GORGEOUS_SELPHY

FiveIsland_ResortGorgeous_MapWarps:
	warp_def 64, 13, 3, 0, MAP_FIVE_ISLAND_LOST_CAVE_ENTRANCE
	warp_def 39, 8, 0, 0, MAP_FIVE_ISLAND_RESORT_GORGEOUS_HOUSE

FiveIsland_ResortGorgeous_MapBGEvents:
	bg_hidden_item_event 10, 7, 3, ITEM_NEST_BALL, FLAG_HIDDEN_ITEM_FIVE_ISLAND_RESORT_GORGEOUS_NEST_BALL, 1, FALSE
	bg_hidden_item_event 27, 11, 3, ITEM_STARDUST, FLAG_HIDDEN_ITEM_FIVE_ISLAND_RESORT_GORGEOUS_STARDUST, 1, FALSE
	bg_hidden_item_event 40, 12, 3, ITEM_STAR_PIECE, FLAG_HIDDEN_ITEM_FIVE_ISLAND_RESORT_GORGEOUS_STAR_PIECE, 1, FALSE
	bg_hidden_item_event 27, 5, 3, ITEM_STARDUST, FLAG_HIDDEN_ITEM_FIVE_ISLAND_RESORT_GORGEOUS_STARDUST_2, 1, FALSE
	bg_sign_event 42, 9, 0, BG_EVENT_PLAYER_FACING_ANY, FiveIsland_ResortGorgeous_EventScript_SelphysHouseSign

FiveIsland_ResortGorgeous_MapEvents::
	map_events FiveIsland_ResortGorgeous_ObjectEvents, FiveIsland_ResortGorgeous_MapWarps, NULL, FiveIsland_ResortGorgeous_MapBGEvents

@ ===== END data/maps/FiveIsland_ResortGorgeous/events.inc =====
@ ===== BEGIN data/maps/FiveIsland_WaterLabyrinth/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FiveIsland_WaterLabyrinth/map.json
@

	.align 2

FiveIsland_WaterLabyrinth_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_GENTLEMAN, 14, 11, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, FiveIsland_WaterLabyrinth_EventScript_EggGentleman, 0
	object_event 2, OBJ_EVENT_GFX_WOMAN_2, 9, 7, 3, MOVEMENT_TYPE_WANDER_AROUND, 1, 1, TRAINER_TYPE_NORMAL, 1, FiveIsland_WaterLabyrinth_EventScript_Alize, 0

FiveIsland_WaterLabyrinth_MapEvents::
	map_events FiveIsland_WaterLabyrinth_ObjectEvents, NULL, NULL, NULL

@ ===== END data/maps/FiveIsland_WaterLabyrinth/events.inc =====
@ ===== BEGIN data/maps/FiveIsland_Meadow/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FiveIsland_Meadow/map.json
@

	.align 2

FiveIsland_Meadow_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_ROCKET_F, 18, 18, 3, MOVEMENT_TYPE_WANDER_AROUND, 1, 1, TRAINER_TYPE_NORMAL, 1, FiveIsland_Meadow_EventScript_Rocket3, FLAG_HIDE_FIVE_ISLAND_ROCKETS
	object_event 2, OBJ_EVENT_GFX_ROCKET_M, 17, 5, 3, MOVEMENT_TYPE_FACE_DOWN_AND_LEFT, 1, 1, TRAINER_TYPE_NORMAL, 5, FiveIsland_Meadow_EventScript_Rocket1, FLAG_HIDE_FIVE_ISLAND_ROCKETS
	object_event 3, OBJ_EVENT_GFX_ROCKET_M, 11, 27, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 3, FiveIsland_Meadow_EventScript_Rocket2, FLAG_HIDE_FIVE_ISLAND_ROCKETS
	object_event 4, OBJ_EVENT_GFX_CUT_TREE, 8, 9, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_CutTree, FLAG_TEMP_12
	object_event 5, OBJ_EVENT_GFX_CUT_TREE, 19, 12, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_CutTree, FLAG_TEMP_13
	object_event 6, OBJ_EVENT_GFX_ITEM_BALL, 12, 11, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, FiveIsland_Meadow_EventScript_ItemMaxPotion, FLAG_HIDE_FIVE_ISLAND_MEADOW_MAX_POTION
	object_event 7, OBJ_EVENT_GFX_ITEM_BALL, 3, 22, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, FiveIsland_Meadow_EventScript_ItemPPUp, FLAG_HIDE_FIVE_ISLAND_MEADOW_PP_UP

FiveIsland_Meadow_MapWarps:
	warp_def 12, 21, 0, 0, MAP_FIVE_ISLAND_ROCKET_WAREHOUSE

FiveIsland_Meadow_MapBGEvents:
	bg_sign_event 12, 21, 0, BG_EVENT_PLAYER_FACING_ANY, FiveIsland_Meadow_EventScript_WarehouseDoor

FiveIsland_Meadow_MapEvents::
	map_events FiveIsland_Meadow_ObjectEvents, FiveIsland_Meadow_MapWarps, NULL, FiveIsland_Meadow_MapBGEvents

@ ===== END data/maps/FiveIsland_Meadow/events.inc =====
@ ===== BEGIN data/maps/FiveIsland_MemorialPillar/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FiveIsland_MemorialPillar/map.json
@

	.align 2

FiveIsland_MemorialPillar_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_MAN, 8, 44, 4, MOVEMENT_TYPE_FACE_UP_AND_LEFT, 1, 1, TRAINER_TYPE_NONE, 0, FiveIsland_MemorialPillar_EventScript_MemorialMan, 0
	object_event 2, OBJ_EVENT_GFX_ROCKER, 12, 6, 3, MOVEMENT_TYPE_FACE_UP_LEFT_AND_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 3, FiveIsland_MemorialPillar_EventScript_Milo, 0
	object_event 3, OBJ_EVENT_GFX_ROCKER, 14, 17, 3, MOVEMENT_TYPE_FACE_DOWN_UP_AND_LEFT, 1, 1, TRAINER_TYPE_NORMAL, 2, FiveIsland_MemorialPillar_EventScript_Chaz, 0
	object_event 4, OBJ_EVENT_GFX_ROCKER, 17, 31, 3, MOVEMENT_TYPE_WANDER_AROUND, 1, 1, TRAINER_TYPE_NORMAL, 3, FiveIsland_MemorialPillar_EventScript_Harold, 0
	object_event 5, OBJ_EVENT_GFX_ITEM_BALL, 4, 47, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, FiveIsland_MemorialPillar_EventScript_ItemMetalCoat, FLAG_HIDE_FIVE_ISLAND_MEMORIAL_PILLAR_METAL_COAT

FiveIsland_MemorialPillar_MapBGEvents:
	bg_sign_event 9, 43, 0, BG_EVENT_PLAYER_FACING_NORTH, FiveIsland_MemorialPillar_EventScript_Memorial
	bg_hidden_item_event 8, 52, 3, ITEM_BIG_PEARL, FLAG_HIDDEN_ITEM_FIVE_ISLAND_MEMORIAL_PILLAR_BIG_PEARL, 1, FALSE
	bg_hidden_item_event 15, 7, 3, ITEM_RAZZ_BERRY, FLAG_HIDDEN_ITEM_FIVE_ISLAND_MEMORIAL_PILLAR_RAZZ_BERRY, 1, FALSE
	bg_hidden_item_event 17, 22, 3, ITEM_SITRUS_BERRY, FLAG_HIDDEN_ITEM_FIVE_ISLAND_MEMORIAL_PILLAR_SITRUS_BERRY, 1, FALSE
	bg_hidden_item_event 14, 25, 3, ITEM_BLUK_BERRY, FLAG_HIDDEN_ITEM_FIVE_ISLAND_MEMORIAL_PILLAR_BLUK_BERRY, 1, FALSE

FiveIsland_MemorialPillar_MapEvents::
	map_events FiveIsland_MemorialPillar_ObjectEvents, NULL, NULL, FiveIsland_MemorialPillar_MapBGEvents

@ ===== END data/maps/FiveIsland_MemorialPillar/events.inc =====
@ ===== BEGIN data/maps/SixIsland_OutcastIsland/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SixIsland_OutcastIsland/map.json
@

	.align 2

SixIsland_OutcastIsland_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_ROCKET_M, 9, 24, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NORMAL, 1, SixIsland_OutcastIsland_EventScript_Rocket, FLAG_HIDE_FIVE_ISLAND_ROCKETS
	object_event 2, OBJ_EVENT_GFX_FISHER, 12, 15, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NORMAL, 1, SixIsland_OutcastIsland_EventScript_Tylor, 0
	object_event 3, OBJ_EVENT_GFX_SWIMMER_M_WATER, 13, 34, 1, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NORMAL, 1, SixIsland_OutcastIsland_EventScript_Mymo, 0
	object_event 4, OBJ_EVENT_GFX_SWIMMER_F_WATER, 14, 61, 1, MOVEMENT_TYPE_WALK_SEQUENCE_DOWN_LEFT_UP_RIGHT, 2, 4, TRAINER_TYPE_NORMAL, 1, SixIsland_OutcastIsland_EventScript_Nicole, 0
	object_event 5, OBJ_EVENT_GFX_SWIMMER_F_WATER, 10, 44, 1, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NORMAL, 1, SixIsland_OutcastIsland_EventScript_Ava, 0
	object_event 6, OBJ_EVENT_GFX_TUBER_M_WATER, 11, 44, 1, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NORMAL, 1, SixIsland_OutcastIsland_EventScript_Geb, 0
	object_event 7, OBJ_EVENT_GFX_ITEM_BALL, 11, 16, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SixIsland_OutcastIsland_EventScript_ItemPPUp, FLAG_HIDE_SIX_ISLAND_OUTCAST_ISLAND_PP_UP

SixIsland_OutcastIsland_MapWarps:
	warp_def 7, 21, 3, 0, MAP_SIX_ISLAND_ALTERING_CAVE

SixIsland_OutcastIsland_MapBGEvents:
	bg_hidden_item_event 16, 23, 3, ITEM_STAR_PIECE, FLAG_HIDDEN_ITEM_SIX_ISLAND_OUTCAST_ISLAND_STAR_PIECE, 1, FALSE
	bg_hidden_item_event 6, 24, 3, ITEM_NET_BALL, FLAG_HIDDEN_ITEM_SIX_ISLAND_OUTCAST_ISLAND_NET_BALL, 1, FALSE

SixIsland_OutcastIsland_MapEvents::
	map_events SixIsland_OutcastIsland_ObjectEvents, SixIsland_OutcastIsland_MapWarps, NULL, SixIsland_OutcastIsland_MapBGEvents

@ ===== END data/maps/SixIsland_OutcastIsland/events.inc =====
@ ===== BEGIN data/maps/SixIsland_GreenPath/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SixIsland_GreenPath/map.json
@

	.align 2

SixIsland_GreenPath_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_WOMAN_1, 11, 8, 3, MOVEMENT_TYPE_FACE_DOWN_UP_AND_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 2, SixIsland_GreenPath_EventScript_Jaclyn, 0

SixIsland_GreenPath_MapWarps:
	warp_def 63, 10, 3, 1, MAP_SIX_ISLAND_PATTERN_BUSH
	warp_def 64, 10, 3, 1, MAP_SIX_ISLAND_PATTERN_BUSH
	warp_def 45, 10, 3, 4, MAP_SIX_ISLAND_PATTERN_BUSH
	warp_def 46, 10, 3, 4, MAP_SIX_ISLAND_PATTERN_BUSH

SixIsland_GreenPath_MapBGEvents:
	bg_sign_event 40, 10, 0, BG_EVENT_PLAYER_FACING_ANY, SixIsland_GreenPath_EventScript_LeftRouteSign
	bg_sign_event 69, 10, 0, BG_EVENT_PLAYER_FACING_ANY, SixIsland_GreenPath_EventScript_RightRouteSign
	bg_hidden_item_event 12, 9, 3, ITEM_ULTRA_BALL, FLAG_HIDDEN_ITEM_SIX_ISLAND_GREEN_PATH_ULTRA_BALL, 1, FALSE

SixIsland_GreenPath_MapEvents::
	map_events SixIsland_GreenPath_ObjectEvents, SixIsland_GreenPath_MapWarps, NULL, SixIsland_GreenPath_MapBGEvents

@ ===== END data/maps/SixIsland_GreenPath/events.inc =====
@ ===== BEGIN data/maps/SixIsland_WaterPath/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SixIsland_WaterPath/map.json
@

	.align 2

SixIsland_WaterPath_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_WOMAN_2, 12, 13, 3, MOVEMENT_TYPE_FACE_DOWN_UP_AND_LEFT, 1, 1, TRAINER_TYPE_NORMAL, 3, SixIsland_WaterPath_EventScript_Rose, 0
	object_event 2, OBJ_EVENT_GFX_ROCKER, 11, 52, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NORMAL, 3, SixIsland_WaterPath_EventScript_Edward, 0
	object_event 3, OBJ_EVENT_GFX_SWIMMER_M_WATER, 13, 35, 1, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NORMAL, 4, SixIsland_WaterPath_EventScript_Samir, 0
	object_event 4, OBJ_EVENT_GFX_SWIMMER_F_WATER, 15, 45, 1, MOVEMENT_TYPE_WANDER_AROUND, 1, 1, TRAINER_TYPE_NORMAL, 1, SixIsland_WaterPath_EventScript_Denise, 0
	object_event 5, OBJ_EVENT_GFX_LITTLE_GIRL, 6, 21, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 1, SixIsland_WaterPath_EventScript_Miu, 0
	object_event 6, OBJ_EVENT_GFX_LITTLE_GIRL, 7, 21, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 1, SixIsland_WaterPath_EventScript_Mia, 0
	object_event 7, OBJ_EVENT_GFX_HIKER, 11, 76, 3, MOVEMENT_TYPE_FACE_UP_AND_LEFT, 1, 1, TRAINER_TYPE_NORMAL, 4, SixIsland_WaterPath_EventScript_Earl, 0
	object_event 8, OBJ_EVENT_GFX_ITEM_BALL, 17, 19, 0, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SixIsland_WaterPath_EventScript_ItemElixir, FLAG_HIDE_SIX_ISLAND_WATER_PATH_ELIXIR
	object_event 9, OBJ_EVENT_GFX_ITEM_BALL, 17, 87, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SixIsland_WaterPath_EventScript_ItemDragonScale, FLAG_HIDE_SIX_ISLAND_WATER_PATH_DRAGON_SCALE

SixIsland_WaterPath_MapWarps:
	warp_def 5, 13, 0, 0, MAP_SIX_ISLAND_WATER_PATH_HOUSE1
	warp_def 11, 19, 0, 0, MAP_SIX_ISLAND_WATER_PATH_HOUSE2

SixIsland_WaterPath_MapBGEvents:
	bg_sign_event 8, 14, 0, BG_EVENT_PLAYER_FACING_ANY, SixIsland_WaterPath_EventScript_HornWantedSign
	bg_hidden_item_event 15, 76, 3, ITEM_ASPEAR_BERRY, FLAG_HIDDEN_ITEM_SIX_ISLAND_WATER_PATH_ASPEAR_BERRY, 1, FALSE
	bg_hidden_item_event 3, 8, 3, ITEM_ORAN_BERRY, FLAG_HIDDEN_ITEM_SIX_ISLAND_WATER_PATH_ORAN_BERRY, 1, FALSE
	bg_hidden_item_event 13, 63, 3, ITEM_PINAP_BERRY, FLAG_HIDDEN_ITEM_SIX_ISLAND_WATER_PATH_PINAP_BERRY, 1, FALSE
	bg_sign_event 12, 54, 0, BG_EVENT_PLAYER_FACING_ANY, SixIsland_WaterPath_EventScript_RouteSign

SixIsland_WaterPath_MapEvents::
	map_events SixIsland_WaterPath_ObjectEvents, SixIsland_WaterPath_MapWarps, NULL, SixIsland_WaterPath_MapBGEvents

@ ===== END data/maps/SixIsland_WaterPath/events.inc =====
@ ===== BEGIN data/maps/SixIsland_RuinValley/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SixIsland_RuinValley/map.json
@

	.align 2

SixIsland_RuinValley_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_SCIENTIST, 24, 25, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NONE, 0, SixIsland_RuinValley_EventScript_Scientist, FLAG_HIDE_RUIN_VALLEY_SCIENTIST
	object_event 2, OBJ_EVENT_GFX_HIKER, 32, 11, 5, MOVEMENT_TYPE_FACE_DOWN_AND_LEFT, 1, 1, TRAINER_TYPE_NORMAL, 4, SixIsland_RuinValley_EventScript_Stanly, 0
	object_event 3, OBJ_EVENT_GFX_HIKER, 33, 16, 5, MOVEMENT_TYPE_FACE_LEFT_AND_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 2, SixIsland_RuinValley_EventScript_Foster, 0
	object_event 4, OBJ_EVENT_GFX_HIKER, 31, 24, 5, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NORMAL, 1, SixIsland_RuinValley_EventScript_Larry, 0
	object_event 5, OBJ_EVENT_GFX_HIKER, 14, 10, 5, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 2, SixIsland_RuinValley_EventScript_Daryl, 0
	object_event 6, OBJ_EVENT_GFX_POKE_MANIAC, 21, 29, 5, MOVEMENT_TYPE_WANDER_AROUND, 2, 3, TRAINER_TYPE_NORMAL, 1, SixIsland_RuinValley_EventScript_Hector, 0
	object_event 7, OBJ_EVENT_GFX_PUSHABLE_BOULDER, 17, 10, 5, MOVEMENT_TYPE_LOOK_AROUND, 0, 0, TRAINER_TYPE_NONE, 0, EventScript_StrengthBoulder, 0
	object_event 8, OBJ_EVENT_GFX_PUSHABLE_BOULDER, 17, 12, 5, MOVEMENT_TYPE_LOOK_AROUND, 0, 0, TRAINER_TYPE_NONE, 0, EventScript_StrengthBoulder, 0
	object_event 9, OBJ_EVENT_GFX_PUSHABLE_BOULDER, 18, 11, 5, MOVEMENT_TYPE_LOOK_AROUND, 0, 0, TRAINER_TYPE_NONE, 0, EventScript_StrengthBoulder, 0
	object_event 10, OBJ_EVENT_GFX_PUSHABLE_BOULDER, 6, 33, 3, MOVEMENT_TYPE_LOOK_AROUND, 0, 0, TRAINER_TYPE_NONE, 0, EventScript_StrengthBoulder, 0
	object_event 11, OBJ_EVENT_GFX_PUSHABLE_BOULDER, 6, 34, 3, MOVEMENT_TYPE_LOOK_AROUND, 0, 0, TRAINER_TYPE_NONE, 0, EventScript_StrengthBoulder, 0
	object_event 12, OBJ_EVENT_GFX_PUSHABLE_BOULDER, 41, 32, 3, MOVEMENT_TYPE_LOOK_AROUND, 0, 0, TRAINER_TYPE_NONE, 0, EventScript_StrengthBoulder, 0
	object_event 13, OBJ_EVENT_GFX_PUSHABLE_BOULDER, 41, 33, 3, MOVEMENT_TYPE_LOOK_AROUND, 0, 0, TRAINER_TYPE_NONE, 0, EventScript_StrengthBoulder, 0
	object_event 14, OBJ_EVENT_GFX_PUSHABLE_BOULDER, 42, 33, 3, MOVEMENT_TYPE_LOOK_AROUND, 0, 0, TRAINER_TYPE_NONE, 0, EventScript_StrengthBoulder, 0
	object_event 15, OBJ_EVENT_GFX_ITEM_BALL, 5, 33, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SixIsland_RuinValley_EventScript_ItemHPUp, FLAG_HIDE_SIX_ISLAND_RUIN_VALLEY_HP_UP
	object_event 16, OBJ_EVENT_GFX_ITEM_BALL, 19, 11, 5, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SixIsland_RuinValley_EventScript_ItemFullRestore, FLAG_HIDE_SIX_ISLAND_RUIN_VALLEY_FULL_RESTORE
	object_event 17, OBJ_EVENT_GFX_ITEM_BALL, 43, 32, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SixIsland_RuinValley_EventScript_ItemSunStone, FLAG_HIDE_SIX_ISLAND_RUIN_VALLEY_SUN_STONE

SixIsland_RuinValley_MapWarps:
	warp_def 24, 24, 3, 0, MAP_SIX_ISLAND_DOTTED_HOLE_1F

SixIsland_RuinValley_MapBGEvents:
	bg_sign_event 24, 24, 3, BG_EVENT_PLAYER_FACING_ANY, SixIsland_RuinValley_EventScript_DottedHoleDoor

SixIsland_RuinValley_MapEvents::
	map_events SixIsland_RuinValley_ObjectEvents, SixIsland_RuinValley_MapWarps, NULL, SixIsland_RuinValley_MapBGEvents

@ ===== END data/maps/SixIsland_RuinValley/events.inc =====
@ ===== BEGIN data/maps/SevenIsland_TrainerTower/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SevenIsland_TrainerTower/map.json
@

	.align 2

SevenIsland_TrainerTower_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_BOY, 56, 26, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NORMAL, 1, SevenIsland_TrainerTower_EventScript_Dario, 0
	object_event 2, OBJ_EVENT_GFX_WOMAN_1, 56, 29, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 1, SevenIsland_TrainerTower_EventScript_Rodette, 0

SevenIsland_TrainerTower_MapWarps:
	warp_def 58, 7, 3, 1, MAP_TRAINER_TOWER_LOBBY

SevenIsland_TrainerTower_MapBGEvents:
	bg_hidden_item_event 49, 27, 3, ITEM_BIG_PEARL, FLAG_HIDDEN_ITEM_SEVEN_ISLAND_TRAINER_TOWER_BIG_PEARL, 1, FALSE
	bg_hidden_item_event 47, 30, 3, ITEM_PEARL, FLAG_HIDDEN_ITEM_SEVEN_ISLAND_TRAINER_TOWER_PEARL, 1, FALSE
	bg_hidden_item_event 59, 32, 3, ITEM_NANAB_BERRY, FLAG_HIDDEN_ITEM_SEVEN_ISLAND_TRAINER_TOWER_NANAB_BERRY, 1, FALSE
	bg_sign_event 56, 8, 0, BG_EVENT_PLAYER_FACING_ANY, SevenIsland_TrainerTower_EventScript_TrainerTowerSign
	bg_sign_event 50, 30, 0, BG_EVENT_PLAYER_FACING_ANY, SevenIsland_TrainerTower_EventScript_TrainerTowerAheadSign

SevenIsland_TrainerTower_MapEvents::
	map_events SevenIsland_TrainerTower_ObjectEvents, SevenIsland_TrainerTower_MapWarps, NULL, SevenIsland_TrainerTower_MapBGEvents

@ ===== END data/maps/SevenIsland_TrainerTower/events.inc =====
@ ===== BEGIN data/maps/SevenIsland_SevaultCanyon_Entrance/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SevenIsland_SevaultCanyon_Entrance/map.json
@

	.align 2

SevenIsland_SevaultCanyon_Entrance_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_WOMAN_2, 12, 6, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NORMAL, 5, SevenIsland_SevaultCanyon_Entrance_EventScript_Miah, 0
	object_event 2, OBJ_EVENT_GFX_BEAUTY, 3, 34, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 1, SevenIsland_SevaultCanyon_Entrance_EventScript_Eve, 0
	object_event 3, OBJ_EVENT_GFX_MAN, 4, 34, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NORMAL, 1, SevenIsland_SevaultCanyon_Entrance_EventScript_Jon, 0
	object_event 4, OBJ_EVENT_GFX_CAMPER, 11, 26, 3, MOVEMENT_TYPE_FACE_DOWN_UP_AND_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 2, SevenIsland_SevaultCanyon_Entrance_EventScript_Nicolas, 0
	object_event 5, OBJ_EVENT_GFX_PICNICKER, 10, 26, 3, MOVEMENT_TYPE_FACE_DOWN_UP_AND_LEFT, 1, 1, TRAINER_TYPE_NORMAL, 2, SevenIsland_SevaultCanyon_Entrance_EventScript_Madeline, 0
	object_event 6, OBJ_EVENT_GFX_ROCKER, 11, 17, 5, MOVEMENT_TYPE_ROTATE_COUNTERCLOCKWISE, 1, 1, TRAINER_TYPE_NORMAL, 1, SevenIsland_SevaultCanyon_Entrance_EventScript_Mason, 0
	clone_event 7, OBJ_EVENT_GFX_COOLTRAINER_M, 7, -2, LOCALID_SWORDS_DANCE_TUTOR, MAP_SEVEN_ISLAND

SevenIsland_SevaultCanyon_Entrance_MapBGEvents:
	bg_hidden_item_event 8, 29, 5, ITEM_RAWST_BERRY, FLAG_HIDDEN_ITEM_SEVEN_ISLAND_SEVAULT_CANYON_ENTRANCE_RAWST_BERRY, 1, FALSE
	bg_sign_event 14, 26, 0, BG_EVENT_PLAYER_FACING_ANY, SevenIsland_SevaultCanyon_Entrance_EventScript_RouteSign

SevenIsland_SevaultCanyon_Entrance_MapEvents::
	map_events SevenIsland_SevaultCanyon_Entrance_ObjectEvents, NULL, NULL, SevenIsland_SevaultCanyon_Entrance_MapBGEvents

@ ===== END data/maps/SevenIsland_SevaultCanyon_Entrance/events.inc =====
@ ===== BEGIN data/maps/SevenIsland_SevaultCanyon/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SevenIsland_SevaultCanyon/map.json
@

	.align 2

SevenIsland_SevaultCanyon_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_CRUSH_GIRL, 13, 43, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NORMAL, 2, SevenIsland_SevaultCanyon_EventScript_Cyndy, 0
	object_event 2, OBJ_EVENT_GFX_MAN, 13, 36, 3, MOVEMENT_TYPE_FACE_DOWN_AND_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 2, SevenIsland_SevaultCanyon_EventScript_Evan, 0
	object_event 3, OBJ_EVENT_GFX_CAMPER, 3, 35, 3, MOVEMENT_TYPE_FACE_UP_LEFT_AND_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 3, SevenIsland_SevaultCanyon_EventScript_Jackson, 0
	object_event 4, OBJ_EVENT_GFX_PICNICKER, 3, 36, 3, MOVEMENT_TYPE_FACE_DOWN_LEFT_AND_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 3, SevenIsland_SevaultCanyon_EventScript_Katelyn, 0
	object_event 5, OBJ_EVENT_GFX_COOLTRAINER_M, 7, 56, 3, MOVEMENT_TYPE_WANDER_AROUND, 1, 1, TRAINER_TYPE_NORMAL, 1, SevenIsland_SevaultCanyon_EventScript_Leroy, 0
	object_event 6, OBJ_EVENT_GFX_COOLTRAINER_F, 11, 63, 3, MOVEMENT_TYPE_WANDER_AROUND, 1, 1, TRAINER_TYPE_NORMAL, 1, SevenIsland_SevaultCanyon_EventScript_Michelle, 0
	object_event 7, OBJ_EVENT_GFX_COOLTRAINER_M, 14, 13, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 1, SevenIsland_SevaultCanyon_EventScript_Lex, 0
	object_event 8, OBJ_EVENT_GFX_COOLTRAINER_F, 14, 14, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 1, SevenIsland_SevaultCanyon_EventScript_Nya, 0
	object_event 9, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 3, 41, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_12
	object_event 10, OBJ_EVENT_GFX_PUSHABLE_BOULDER, 13, 47, 3, MOVEMENT_TYPE_LOOK_AROUND, 0, 0, TRAINER_TYPE_NONE, 0, EventScript_StrengthBoulder, 0
	object_event 11, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 7, 44, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_13
	object_event 12, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 12, 47, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_15
	object_event 13, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 15, 46, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_16
	object_event 14, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 16, 47, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_17
	object_event 15, OBJ_EVENT_GFX_PUSHABLE_BOULDER, 17, 47, 3, MOVEMENT_TYPE_LOOK_AROUND, 0, 0, TRAINER_TYPE_NONE, 0, EventScript_StrengthBoulder, 0
	object_event 16, OBJ_EVENT_GFX_ROCK_SMASH_ROCK, 11, 31, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_RockSmash, FLAG_TEMP_1B
	object_event 17, OBJ_EVENT_GFX_ITEM_BALL, 18, 45, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SevenIsland_SevaultCanyon_EventScript_ItemKingsRock, FLAG_HIDE_SEVEN_ISLAND_SEVAULT_CANYON_KINGS_ROCK
	object_event 18, OBJ_EVENT_GFX_ITEM_BALL, 7, 38, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SevenIsland_SevaultCanyon_EventScript_ItemMaxElixir, FLAG_HIDE_SEVEN_ISLAND_SEVAULT_CANYON_MAX_ELIXIR
	object_event 19, OBJ_EVENT_GFX_ITEM_BALL, 17, 23, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SevenIsland_SevaultCanyon_EventScript_ItemNugget, FLAG_HIDE_SEVEN_ISLAND_SEVAULT_CANYON_NUGGET
	object_event 20, OBJ_EVENT_GFX_BLACK_BELT, 8, 26, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NONE, 0, SevenIsland_SevaultCanyon_EventScript_BlackBelt, 0

SevenIsland_SevaultCanyon_MapWarps:
	warp_def 7, 17, 5, 0, MAP_SEVEN_ISLAND_SEVAULT_CANYON_TANOBY_KEY
	warp_def 14, 61, 0, 0, MAP_SEVEN_ISLAND_SEVAULT_CANYON_HOUSE

SevenIsland_SevaultCanyon_MapBGEvents:
	bg_hidden_item_event 15, 66, 3, ITEM_CHERI_BERRY, FLAG_HIDDEN_ITEM_SEVEN_ISLAND_SEVAULT_CANYON_CHERI_BERRY, 1, FALSE
	bg_sign_event 16, 71, 0, BG_EVENT_PLAYER_FACING_ANY, SevenIsland_SevaultCanyon_EventScript_RouteSign

SevenIsland_SevaultCanyon_MapEvents::
	map_events SevenIsland_SevaultCanyon_ObjectEvents, SevenIsland_SevaultCanyon_MapWarps, NULL, SevenIsland_SevaultCanyon_MapBGEvents

@ ===== END data/maps/SevenIsland_SevaultCanyon/events.inc =====
@ ===== BEGIN data/maps/SevenIsland_TanobyRuins/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SevenIsland_TanobyRuins/map.json
@

	.align 2

SevenIsland_TanobyRuins_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_HIKER, 35, 7, 3, MOVEMENT_TYPE_WANDER_AROUND, 1, 1, TRAINER_TYPE_NORMAL, 1, SevenIsland_TanobyRuins_EventScript_Brandon, 0
	object_event 2, OBJ_EVENT_GFX_HIKER, 121, 11, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NORMAL, 1, SevenIsland_TanobyRuins_EventScript_Benjamin, 0
	object_event 3, OBJ_EVENT_GFX_LASS, 85, 8, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 1, SevenIsland_TanobyRuins_EventScript_Edna, 0
	object_event 4, OBJ_EVENT_GFX_GENTLEMAN, 85, 5, 3, MOVEMENT_TYPE_WANDER_AROUND, 1, 1, TRAINER_TYPE_NORMAL, 1, SevenIsland_TanobyRuins_EventScript_Clifford, 0

SevenIsland_TanobyRuins_MapWarps:
	warp_def 120, 10, 3, 0, MAP_SEVEN_ISLAND_TANOBY_RUINS_MONEAN_CHAMBER
	warp_def 103, 10, 3, 0, MAP_SEVEN_ISLAND_TANOBY_RUINS_LIPTOO_CHAMBER
	warp_def 88, 8, 3, 0, MAP_SEVEN_ISLAND_TANOBY_RUINS_WEEPTH_CHAMBER
	warp_def 44, 11, 3, 0, MAP_SEVEN_ISLAND_TANOBY_RUINS_DILFORD_CHAMBER
	warp_def 32, 9, 3, 0, MAP_SEVEN_ISLAND_TANOBY_RUINS_SCUFIB_CHAMBER
	warp_def 12, 15, 3, 0, MAP_SEVEN_ISLAND_TANOBY_RUINS_RIXY_CHAMBER
	warp_def 11, 6, 3, 0, MAP_SEVEN_ISLAND_TANOBY_RUINS_VIAPOIS_CHAMBER

SevenIsland_TanobyRuins_MapBGEvents:
	bg_hidden_item_event 33, 10, 3, ITEM_HEART_SCALE, FLAG_HIDDEN_ITEM_SEVEN_ISLAND_TANOBY_RUINS_HEART_SCALE, 1, FALSE
	bg_hidden_item_event 86, 9, 3, ITEM_HEART_SCALE, FLAG_HIDDEN_ITEM_SEVEN_ISLAND_TANOBY_RUINS_HEART_SCALE_2, 1, FALSE
	bg_hidden_item_event 125, 5, 3, ITEM_HEART_SCALE, FLAG_HIDDEN_ITEM_SEVEN_ISLAND_TANOBY_RUINS_HEART_SCALE_3, 1, FALSE
	bg_hidden_item_event 8, 2, 3, ITEM_HEART_SCALE, FLAG_HIDDEN_ITEM_SEVEN_ISLAND_TANOBY_RUINS_HEART_SCALE_4, 1, FALSE

SevenIsland_TanobyRuins_MapEvents::
	map_events SevenIsland_TanobyRuins_ObjectEvents, SevenIsland_TanobyRuins_MapWarps, NULL, SevenIsland_TanobyRuins_MapBGEvents

@ ===== END data/maps/SevenIsland_TanobyRuins/events.inc =====
@ ===== BEGIN data/maps/PalletTown_PlayersHouse_1F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/PalletTown_PlayersHouse_1F/map.json
@

	.align 2

PalletTown_PlayersHouse_1F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_MOM, 8, 4, 3, MOVEMENT_TYPE_FACE_LEFT, 0, 0, TRAINER_TYPE_NONE, 0, PalletTown_PlayersHouse_1F_EventScript_Mom, 0

PalletTown_PlayersHouse_1F_MapWarps:
	warp_def 5, 8, 3, 0, MAP_PALLET_TOWN
	warp_def 4, 8, 3, 0, MAP_PALLET_TOWN
	warp_def 10, 2, 3, 0, MAP_PALLET_TOWN_PLAYERS_HOUSE_2F
	warp_def 3, 9, 0, 0, MAP_PALLET_TOWN

PalletTown_PlayersHouse_1F_MapBGEvents:
	bg_sign_event 6, 1, 0, BG_EVENT_PLAYER_FACING_ANY, PalletTown_PlayersHouse_1F_EventScript_TV

PalletTown_PlayersHouse_1F_MapEvents::
	map_events PalletTown_PlayersHouse_1F_ObjectEvents, PalletTown_PlayersHouse_1F_MapWarps, NULL, PalletTown_PlayersHouse_1F_MapBGEvents

@ ===== END data/maps/PalletTown_PlayersHouse_1F/events.inc =====
@ ===== BEGIN data/maps/PalletTown_PlayersHouse_2F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/PalletTown_PlayersHouse_2F/map.json
@

	.align 2

PalletTown_PlayersHouse_2F_MapWarps:
	warp_def 10, 2, 3, 2, MAP_PALLET_TOWN_PLAYERS_HOUSE_1F

PalletTown_PlayersHouse_2F_MapBGEvents:
	bg_sign_event 6, 5, 3, BG_EVENT_PLAYER_FACING_ANY, PalletTown_PlayersHouse_2F_EventScript_NES
	bg_sign_event 1, 1, 0, BG_EVENT_PLAYER_FACING_ANY, PalletTown_PlayersHouse_2F_EventScript_PC
	bg_sign_event 11, 1, 0, BG_EVENT_PLAYER_FACING_ANY, PalletTown_PlayersHouse_2F_EventScript_Sign

PalletTown_PlayersHouse_2F_MapEvents::
	map_events NULL, PalletTown_PlayersHouse_2F_MapWarps, NULL, PalletTown_PlayersHouse_2F_MapBGEvents

@ ===== END data/maps/PalletTown_PlayersHouse_2F/events.inc =====
@ ===== BEGIN data/maps/PalletTown_RivalsHouse/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/PalletTown_RivalsHouse/map.json
@

	.align 2

PalletTown_RivalsHouse_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_DAISY, 10, 6, 3, MOVEMENT_TYPE_WANDER_AROUND, 1, 3, TRAINER_TYPE_NONE, 0, PalletTown_RivalsHouse_EventScript_Daisy, 0
	object_event 2, OBJ_EVENT_GFX_TOWN_MAP, 6, 4, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, PalletTown_RivalsHouse_EventScript_TownMap, FLAG_HIDE_TOWN_MAP

PalletTown_RivalsHouse_MapWarps:
	warp_def 4, 8, 3, 1, MAP_PALLET_TOWN
	warp_def 5, 8, 3, 1, MAP_PALLET_TOWN
	warp_def 3, 8, 3, 1, MAP_PALLET_TOWN

PalletTown_RivalsHouse_MapBGEvents:
	bg_sign_event 12, 1, 0, BG_EVENT_PLAYER_FACING_ANY, PalletTown_RivalsHouse_EventScript_Bookshelf
	bg_sign_event 11, 1, 0, BG_EVENT_PLAYER_FACING_ANY, PalletTown_RivalsHouse_EventScript_Bookshelf
	bg_sign_event 9, 1, 0, BG_EVENT_PLAYER_FACING_ANY, PalletTown_RivalsHouse_EventScript_Picture

PalletTown_RivalsHouse_MapEvents::
	map_events PalletTown_RivalsHouse_ObjectEvents, PalletTown_RivalsHouse_MapWarps, NULL, PalletTown_RivalsHouse_MapBGEvents

@ ===== END data/maps/PalletTown_RivalsHouse/events.inc =====
@ ===== BEGIN data/maps/PalletTown_ProfessorOaksLab/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/PalletTown_ProfessorOaksLab/map.json
@

	.align 2

PalletTown_ProfessorOaksLab_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_SCIENTIST, 3, 11, 3, MOVEMENT_TYPE_LOOK_AROUND, 0, 0, TRAINER_TYPE_NONE, 0, PalletTown_ProfessorOaksLab_EventScript_Aide1, 0
	object_event 2, OBJ_EVENT_GFX_WORKER_F, 2, 10, 3, MOVEMENT_TYPE_WANDER_UP_AND_DOWN, 0, 4, TRAINER_TYPE_NONE, 0, PalletTown_ProfessorOaksLab_EventScript_Aide3, 0
	object_event 3, OBJ_EVENT_GFX_SCIENTIST, 11, 10, 3, MOVEMENT_TYPE_LOOK_AROUND, 0, 0, TRAINER_TYPE_NONE, 0, PalletTown_ProfessorOaksLab_EventScript_Aide2, 0
	object_event 4, OBJ_EVENT_GFX_PROF_OAK, 6, 3, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, PalletTown_ProfessorOaksLab_EventScript_ProfOak, FLAG_HIDE_OAK_IN_HIS_LAB
	object_event 5, OBJ_EVENT_GFX_ITEM_BALL, 8, 4, 0, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, PalletTown_ProfessorOaksLab_EventScript_BulbasaurBall, FLAG_HIDE_BULBASAUR_BALL
	object_event 6, OBJ_EVENT_GFX_ITEM_BALL, 9, 4, 0, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, PalletTown_ProfessorOaksLab_EventScript_SquirtleBall, FLAG_HIDE_SQUIRTLE_BALL
	object_event 7, OBJ_EVENT_GFX_ITEM_BALL, 10, 4, 0, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, PalletTown_ProfessorOaksLab_EventScript_CharmanderBall, FLAG_HIDE_CHARMANDER_BALL
	object_event 8, OBJ_EVENT_GFX_BLUE, 5, 4, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, PalletTown_ProfessorOaksLab_EventScript_Rival, FLAG_HIDE_RIVAL_IN_LAB
	object_event 9, OBJ_EVENT_GFX_POKEDEX, 4, 1, 0, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, PalletTown_ProfessorOaksLab_EventScript_Pokedex, FLAG_HIDE_POKEDEX
	object_event 10, OBJ_EVENT_GFX_POKEDEX, 5, 1, 0, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, PalletTown_ProfessorOaksLab_EventScript_Pokedex, FLAG_HIDE_POKEDEX

PalletTown_ProfessorOaksLab_MapWarps:
	warp_def 6, 12, 3, 2, MAP_PALLET_TOWN
	warp_def 7, 12, 3, 2, MAP_PALLET_TOWN
	warp_def 5, 12, 3, 2, MAP_PALLET_TOWN

PalletTown_ProfessorOaksLab_MapCoordEvents:
	coord_event 5, 8, 3, VAR_MAP_SCENE_PALLET_TOWN_PROFESSOR_OAKS_LAB, 2, PalletTown_ProfessorOaksLab_EventScript_LeaveStarterSceneTrigger
	coord_event 6, 8, 3, VAR_MAP_SCENE_PALLET_TOWN_PROFESSOR_OAKS_LAB, 2, PalletTown_ProfessorOaksLab_EventScript_LeaveStarterSceneTrigger
	coord_event 7, 8, 3, VAR_MAP_SCENE_PALLET_TOWN_PROFESSOR_OAKS_LAB, 2, PalletTown_ProfessorOaksLab_EventScript_LeaveStarterSceneTrigger
	coord_event 5, 8, 3, VAR_MAP_SCENE_PALLET_TOWN_PROFESSOR_OAKS_LAB, 3, PalletTown_ProfessorOaksLab_EventScript_RivalBattleTriggerLeft
	coord_event 6, 8, 3, VAR_MAP_SCENE_PALLET_TOWN_PROFESSOR_OAKS_LAB, 3, PalletTown_ProfessorOaksLab_EventScript_RivalBattleTriggerMid
	coord_event 7, 8, 3, VAR_MAP_SCENE_PALLET_TOWN_PROFESSOR_OAKS_LAB, 3, PalletTown_ProfessorOaksLab_EventScript_RivalBattleTriggerRight

PalletTown_ProfessorOaksLab_MapBGEvents:
	bg_sign_event 2, 1, 0, BG_EVENT_PLAYER_FACING_ANY, PalletTown_ProfessorOaksLab_EventScript_Computer
	bg_sign_event 3, 1, 0, BG_EVENT_PLAYER_FACING_ANY, PalletTown_ProfessorOaksLab_EventScript_Computer
	bg_sign_event 6, 1, 0, BG_EVENT_PLAYER_FACING_ANY, PalletTown_ProfessorOaksLab_EventScript_LeftSign
	bg_sign_event 7, 1, 0, BG_EVENT_PLAYER_FACING_ANY, PalletTown_ProfessorOaksLab_EventScript_RightSign

PalletTown_ProfessorOaksLab_MapEvents::
	map_events PalletTown_ProfessorOaksLab_ObjectEvents, PalletTown_ProfessorOaksLab_MapWarps, PalletTown_ProfessorOaksLab_MapCoordEvents, PalletTown_ProfessorOaksLab_MapBGEvents

@ ===== END data/maps/PalletTown_ProfessorOaksLab/events.inc =====
@ ===== BEGIN data/maps/ViridianCity_House/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/ViridianCity_House/map.json
@

	.align 2

ViridianCity_House_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_BALDING_MAN, 7, 4, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NONE, 0, ViridianCity_House_EventScript_BaldingMan, 0
	object_event 2, OBJ_EVENT_GFX_LITTLE_GIRL, 2, 5, 3, MOVEMENT_TYPE_WANDER_UP_AND_DOWN, 1, 2, TRAINER_TYPE_NONE, 0, ViridianCity_House_EventScript_LittleGirl, 0
	object_event 3, OBJ_EVENT_GFX_SPEAROW, 6, 6, 3, MOVEMENT_TYPE_WANDER_LEFT_AND_RIGHT, 4, 1, TRAINER_TYPE_NONE, 0, ViridianCity_House_EventScript_Speary, 0

ViridianCity_House_MapWarps:
	warp_def 3, 7, 0, 1, MAP_VIRIDIAN_CITY
	warp_def 4, 7, 0, 1, MAP_VIRIDIAN_CITY
	warp_def 5, 7, 3, 1, MAP_VIRIDIAN_CITY

ViridianCity_House_MapBGEvents:
	bg_sign_event 7, 1, 0, BG_EVENT_PLAYER_FACING_ANY, ViridianCity_House_EventScript_NicknameSign

ViridianCity_House_MapEvents::
	map_events ViridianCity_House_ObjectEvents, ViridianCity_House_MapWarps, NULL, ViridianCity_House_MapBGEvents

@ ===== END data/maps/ViridianCity_House/events.inc =====
@ ===== BEGIN data/maps/ViridianCity_Gym/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/ViridianCity_Gym/map.json
@

	.align 2

ViridianCity_Gym_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_BLACK_BELT, 10, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 3, ViridianCity_Gym_EventScript_Takashi, 0
	object_event 2, OBJ_EVENT_GFX_COOLTRAINER_M, 12, 10, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 3, ViridianCity_Gym_EventScript_Yuji, 0
	object_event 3, OBJ_EVENT_GFX_BLACK_BELT, 11, 14, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NORMAL, 3, ViridianCity_Gym_EventScript_Atsushi, 0
	object_event 4, OBJ_EVENT_GFX_MAN, 10, 10, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 3, ViridianCity_Gym_EventScript_Jason, 0
	object_event 5, OBJ_EVENT_GFX_MAN, 2, 21, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 2, ViridianCity_Gym_EventScript_Cole, 0
	object_event 6, OBJ_EVENT_GFX_BLACK_BELT, 3, 11, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NORMAL, 2, ViridianCity_Gym_EventScript_Kiyo, 0
	object_event 7, OBJ_EVENT_GFX_COOLTRAINER_M, 6, 8, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 3, ViridianCity_Gym_EventScript_Samuel, 0
	object_event 8, OBJ_EVENT_GFX_GIOVANNI, 2, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, ViridianCity_Gym_EventScript_Giovanni, FLAG_HIDE_VIRIDIAN_GIOVANNI
	object_event 9, OBJ_EVENT_GFX_COOLTRAINER_M, 13, 7, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 3, ViridianCity_Gym_EventScript_Warren, 0
	object_event 10, OBJ_EVENT_GFX_GYM_GUY, 16, 20, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, ViridianCity_Gym_EventScript_GymGuy, 0

ViridianCity_Gym_MapWarps:
	warp_def 16, 22, 3, 2, MAP_VIRIDIAN_CITY
	warp_def 17, 22, 3, 2, MAP_VIRIDIAN_CITY
	warp_def 18, 22, 3, 2, MAP_VIRIDIAN_CITY

ViridianCity_Gym_MapBGEvents:
	bg_sign_event 15, 20, 0, BG_EVENT_PLAYER_FACING_ANY, ViridianCity_Gym_EventScript_GymStatue
	bg_sign_event 19, 20, 0, BG_EVENT_PLAYER_FACING_ANY, ViridianCity_Gym_EventScript_GymStatue
	bg_hidden_item_event 2, 2, 3, ITEM_MACHO_BRACE, FLAG_HIDDEN_ITEM_VIRIDIAN_CITY_GYM_MACHO_BRACE, 1, TRUE

ViridianCity_Gym_MapEvents::
	map_events ViridianCity_Gym_ObjectEvents, ViridianCity_Gym_MapWarps, NULL, ViridianCity_Gym_MapBGEvents

@ ===== END data/maps/ViridianCity_Gym/events.inc =====
@ ===== BEGIN data/maps/ViridianCity_School/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/ViridianCity_School/map.json
@

	.align 2

ViridianCity_School_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_WOMAN_2, 6, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, ViridianCity_School_EventScript_Woman, 0
	object_event 2, OBJ_EVENT_GFX_LASS, 4, 5, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NONE, 0, ViridianCity_School_EventScript_Lass, 0

ViridianCity_School_MapWarps:
	warp_def 3, 7, 0, 3, MAP_VIRIDIAN_CITY
	warp_def 4, 7, 0, 3, MAP_VIRIDIAN_CITY
	warp_def 5, 7, 3, 3, MAP_VIRIDIAN_CITY

ViridianCity_School_MapBGEvents:
	bg_sign_event 4, 4, 0, BG_EVENT_PLAYER_FACING_ANY, ViridianCity_School_EventScript_Notebook
	bg_sign_event 5, 1, 0, BG_EVENT_PLAYER_FACING_ANY, ViridianCity_School_EventScript_Blackboard
	bg_sign_event 4, 1, 0, BG_EVENT_PLAYER_FACING_ANY, ViridianCity_School_EventScript_Blackboard
	bg_sign_event 9, 2, 0, BG_EVENT_PLAYER_FACING_NORTH, ViridianCity_School_EventScript_PokemonJournal
	bg_sign_event 8, 2, 0, BG_EVENT_PLAYER_FACING_NORTH, ViridianCity_School_EventScript_PokemonJournal

ViridianCity_School_MapEvents::
	map_events ViridianCity_School_ObjectEvents, ViridianCity_School_MapWarps, NULL, ViridianCity_School_MapBGEvents

@ ===== END data/maps/ViridianCity_School/events.inc =====
@ ===== BEGIN data/maps/ViridianCity_Mart/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/ViridianCity_Mart/map.json
@

	.align 2

ViridianCity_Mart_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_CLERK, 2, 3, 0, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, ViridianCity_Mart_EventScript_Clerk, 0
	object_event 2, OBJ_EVENT_GFX_YOUNGSTER, 6, 2, 3, MOVEMENT_TYPE_WANDER_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, ViridianCity_Mart_EventScript_Youngster, 0
	object_event 3, OBJ_EVENT_GFX_WOMAN_1, 9, 5, 3, MOVEMENT_TYPE_WANDER_UP_AND_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, ViridianCity_Mart_EventScript_Woman, 0

ViridianCity_Mart_MapWarps:
	warp_def 3, 7, 3, 4, MAP_VIRIDIAN_CITY
	warp_def 4, 7, 3, 4, MAP_VIRIDIAN_CITY
	warp_def 5, 7, 3, 4, MAP_VIRIDIAN_CITY

ViridianCity_Mart_MapEvents::
	map_events ViridianCity_Mart_ObjectEvents, ViridianCity_Mart_MapWarps, NULL, NULL

@ ===== END data/maps/ViridianCity_Mart/events.inc =====
@ ===== BEGIN data/maps/ViridianCity_PokemonCenter_1F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/ViridianCity_PokemonCenter_1F/map.json
@

	.align 2

ViridianCity_PokemonCenter_1F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_NURSE, 7, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, ViridianCity_PokemonCenter_1F_EventScript_Nurse, 0
	object_event 2, OBJ_EVENT_GFX_GENTLEMAN, 12, 5, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, ViridianCity_PokemonCenter_1F_EventScript_Gentleman, 0
	object_event 3, OBJ_EVENT_GFX_BOY, 4, 7, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, ViridianCity_PokemonCenter_1F_EventScript_Boy, 0
	object_event 4, OBJ_EVENT_GFX_YOUNGSTER, 2, 3, 3, MOVEMENT_TYPE_WANDER_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, ViridianCity_PokemonCenter_1F_EventScript_Youngster, 0

ViridianCity_PokemonCenter_1F_MapWarps:
	warp_def 6, 8, 3, 0, MAP_VIRIDIAN_CITY
	warp_def 7, 8, 3, 0, MAP_VIRIDIAN_CITY
	warp_def 8, 8, 3, 0, MAP_VIRIDIAN_CITY
	warp_def 1, 6, 4, 0, MAP_VIRIDIAN_CITY_POKEMON_CENTER_2F

ViridianCity_PokemonCenter_1F_MapEvents::
	map_events ViridianCity_PokemonCenter_1F_ObjectEvents, ViridianCity_PokemonCenter_1F_MapWarps, NULL, NULL

@ ===== END data/maps/ViridianCity_PokemonCenter_1F/events.inc =====
@ ===== BEGIN data/maps/ViridianCity_PokemonCenter_2F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/ViridianCity_PokemonCenter_2F/map.json
@

	.align 2

ViridianCity_PokemonCenter_2F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_CABLE_CLUB_RECEPTIONIST, 6, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 0, 0, TRAINER_TYPE_NONE, 0, Common_EventScript_UnionRoomAttendant, 0
	object_event 2, OBJ_EVENT_GFX_CABLE_CLUB_RECEPTIONIST, 2, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 0, 0, TRAINER_TYPE_NONE, 0, Common_EventScript_WirelessClubAttendant, 0
	object_event 3, OBJ_EVENT_GFX_CABLE_CLUB_RECEPTIONIST, 10, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 0, 0, TRAINER_TYPE_NONE, 0, Common_EventScript_DirectCornerAttendant, 0
	object_event 4, OBJ_EVENT_GFX_MG_DELIVERYMAN, 1, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, CableClub_EventScript_MysteryGiftMan, FLAG_HIDE_MG_DELIVERYMEN

ViridianCity_PokemonCenter_2F_MapWarps:
	warp_def 1, 6, 4, 3, MAP_VIRIDIAN_CITY_POKEMON_CENTER_1F
	warp_def 5, 1, 0, 0, MAP_UNION_ROOM
	warp_def 9, 1, 0, 0, MAP_TRADE_CENTER

ViridianCity_PokemonCenter_2F_MapEvents::
	map_events ViridianCity_PokemonCenter_2F_ObjectEvents, ViridianCity_PokemonCenter_2F_MapWarps, NULL, NULL

@ ===== END data/maps/ViridianCity_PokemonCenter_2F/events.inc =====
@ ===== BEGIN data/maps/PewterCity_Museum_1F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/PewterCity_Museum_1F/map.json
@

	.align 2

PewterCity_Museum_1F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_WORKER_M, 16, 5, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NONE, 0, PewterCity_Museum_1F_EventScript_Scientist1, 0
	object_event 2, OBJ_EVENT_GFX_OLD_MAN_1, 2, 4, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, PewterCity_Museum_1F_EventScript_OldMan, 0
	object_event 3, OBJ_EVENT_GFX_SCIENTIST, 21, 3, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, PewterCity_Museum_1F_EventScript_OldAmberScientist, 0
	object_event 4, OBJ_EVENT_GFX_OLD_AMBER, 22, 3, 0, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, PewterCity_Museum_1F_EventScript_OldAmber, FLAG_HIDE_OLD_AMBER
	object_event 5, OBJ_EVENT_GFX_SCIENTIST, 26, 4, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, PewterCity_Museum_1F_EventScript_Scientist2, 0
	object_event 6, OBJ_EVENT_GFX_SCIENTIST, 26, 7, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, PewterCity_Museum_1F_EventScript_SeismicTossTutor, 0

PewterCity_Museum_1F_MapWarps:
	warp_def 13, 9, 3, 0, MAP_PEWTER_CITY
	warp_def 14, 9, 3, 0, MAP_PEWTER_CITY
	warp_def 15, 9, 3, 0, MAP_PEWTER_CITY
	warp_def 21, 9, 3, 1, MAP_PEWTER_CITY
	warp_def 22, 9, 3, 1, MAP_PEWTER_CITY
	warp_def 8, 8, 3, 0, MAP_PEWTER_CITY_MUSEUM_2F

PewterCity_Museum_1F_MapCoordEvents:
	coord_event 12, 5, 3, VAR_MAP_SCENE_PEWTER_CITY_MUSEUM_1F, 0, PewterCity_Museum_1F_EventScript_EntranceTriggerLeft
	coord_event 13, 5, 3, VAR_MAP_SCENE_PEWTER_CITY_MUSEUM_1F, 0, PewterCity_Museum_1F_EventScript_EntranceTriggerMid
	coord_event 14, 5, 3, VAR_MAP_SCENE_PEWTER_CITY_MUSEUM_1F, 0, PewterCity_Museum_1F_EventScript_EntranceTriggerRight

PewterCity_Museum_1F_MapBGEvents:
	bg_sign_event 4, 4, 0, BG_EVENT_PLAYER_FACING_ANY, PewterCity_Museum_1F_EventScript_AerodactylFossil
	bg_sign_event 4, 7, 0, BG_EVENT_PLAYER_FACING_ANY, PewterCity_Museum_1F_EventScript_KabutopsFossil
	bg_sign_event 27, 1, 0, BG_EVENT_PLAYER_FACING_NORTH, PewterCity_Museum_1F_EventScript_PokemonJournalBrock
	bg_sign_event 26, 1, 0, BG_EVENT_PLAYER_FACING_NORTH, PewterCity_Museum_1F_EventScript_PokemonJournalBrock

PewterCity_Museum_1F_MapEvents::
	map_events PewterCity_Museum_1F_ObjectEvents, PewterCity_Museum_1F_MapWarps, PewterCity_Museum_1F_MapCoordEvents, PewterCity_Museum_1F_MapBGEvents

@ ===== END data/maps/PewterCity_Museum_1F/events.inc =====
@ ===== BEGIN data/maps/PewterCity_Museum_2F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/PewterCity_Museum_2F/map.json
@

	.align 2

PewterCity_Museum_2F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_SCIENTIST, 10, 5, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, PewterCity_Museum_2F_EventScript_Scientist, 0
	object_event 2, OBJ_EVENT_GFX_MAN, 4, 9, 3, MOVEMENT_TYPE_WANDER_LEFT_AND_RIGHT, 3, 1, TRAINER_TYPE_NONE, 0, PewterCity_Museum_2F_EventScript_Man, 0
	object_event 3, OBJ_EVENT_GFX_OLD_MAN_2, 0, 6, 3, MOVEMENT_TYPE_LOOK_AROUND, 3, 1, TRAINER_TYPE_NONE, 0, PewterCity_Museum_2F_EventScript_OldMan, 0
	object_event 4, OBJ_EVENT_GFX_LITTLE_GIRL, 15, 8, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, PewterCity_Museum_2F_EventScript_LittleGirl, 0
	object_event 5, OBJ_EVENT_GFX_BALDING_MAN, 16, 8, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, PewterCity_Museum_2F_EventScript_BaldingMan, 0

PewterCity_Museum_2F_MapWarps:
	warp_def 11, 8, 3, 5, MAP_PEWTER_CITY_MUSEUM_1F

PewterCity_Museum_2F_MapBGEvents:
	bg_sign_event 3, 6, 0, BG_EVENT_PLAYER_FACING_ANY, PewterCity_Museum_2F_EventScript_MoonStone
	bg_sign_event 15, 5, 0, BG_EVENT_PLAYER_FACING_ANY, PewterCity_Museum_2F_EventScript_SpaceShuttle
	bg_sign_event 14, 5, 0, BG_EVENT_PLAYER_FACING_ANY, PewterCity_Museum_2F_EventScript_SpaceShuttle
	bg_sign_event 16, 5, 0, BG_EVENT_PLAYER_FACING_ANY, PewterCity_Museum_2F_EventScript_SpaceShuttle
	bg_sign_event 14, 4, 0, BG_EVENT_PLAYER_FACING_ANY, PewterCity_Museum_2F_EventScript_SpaceShuttle
	bg_sign_event 15, 4, 0, BG_EVENT_PLAYER_FACING_ANY, PewterCity_Museum_2F_EventScript_SpaceShuttle
	bg_sign_event 16, 4, 0, BG_EVENT_PLAYER_FACING_ANY, PewterCity_Museum_2F_EventScript_SpaceShuttle
	bg_sign_event 3, 5, 0, BG_EVENT_PLAYER_FACING_ANY, PewterCity_Museum_2F_EventScript_MoonStone

PewterCity_Museum_2F_MapEvents::
	map_events PewterCity_Museum_2F_ObjectEvents, PewterCity_Museum_2F_MapWarps, NULL, PewterCity_Museum_2F_MapBGEvents

@ ===== END data/maps/PewterCity_Museum_2F/events.inc =====
@ ===== BEGIN data/maps/PewterCity_Gym/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/PewterCity_Gym/map.json
@

	.align 2

PewterCity_Gym_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_BROCK, 6, 5, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, PewterCity_Gym_EventScript_Brock, 0
	object_event 2, OBJ_EVENT_GFX_CAMPER, 3, 8, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 4, PewterCity_Gym_EventScript_Liam, 0
	object_event 3, OBJ_EVENT_GFX_GYM_GUY, 7, 12, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, PewterCity_Gym_EventScript_GymGuy, 0

PewterCity_Gym_MapWarps:
	warp_def 5, 14, 3, 2, MAP_PEWTER_CITY
	warp_def 6, 14, 3, 2, MAP_PEWTER_CITY
	warp_def 7, 14, 3, 2, MAP_PEWTER_CITY

PewterCity_Gym_MapBGEvents:
	bg_sign_event 4, 12, 0, BG_EVENT_PLAYER_FACING_ANY, PewterCity_Gym_EventScript_GymStatue
	bg_sign_event 8, 12, 0, BG_EVENT_PLAYER_FACING_ANY, PewterCity_Gym_EventScript_GymStatue

PewterCity_Gym_MapEvents::
	map_events PewterCity_Gym_ObjectEvents, PewterCity_Gym_MapWarps, NULL, PewterCity_Gym_MapBGEvents

@ ===== END data/maps/PewterCity_Gym/events.inc =====
@ ===== BEGIN data/maps/PewterCity_Mart/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/PewterCity_Mart/map.json
@

	.align 2

PewterCity_Mart_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_YOUNGSTER, 8, 2, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, PewterCity_Mart_EventScript_Youngster, 0
	object_event 2, OBJ_EVENT_GFX_BOY, 6, 4, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, PewterCity_Mart_EventScript_Boy, 0
	object_event 3, OBJ_EVENT_GFX_CLERK, 2, 3, 0, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, PewterCity_Mart_EventScript_Clerk, 0

PewterCity_Mart_MapWarps:
	warp_def 3, 7, 3, 3, MAP_PEWTER_CITY
	warp_def 4, 7, 3, 3, MAP_PEWTER_CITY
	warp_def 5, 7, 3, 3, MAP_PEWTER_CITY

PewterCity_Mart_MapEvents::
	map_events PewterCity_Mart_ObjectEvents, PewterCity_Mart_MapWarps, NULL, NULL

@ ===== END data/maps/PewterCity_Mart/events.inc =====
@ ===== BEGIN data/maps/PewterCity_House1/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/PewterCity_House1/map.json
@

	.align 2

PewterCity_House1_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_BALDING_MAN, 1, 2, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NONE, 0, PewterCity_House1_EventScript_BaldingMan, 0
	object_event 2, OBJ_EVENT_GFX_LITTLE_BOY, 5, 3, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, PewterCity_House1_EventScript_LittleBoy, 0
	object_event 3, OBJ_EVENT_GFX_NIDORAN_M, 6, 3, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NONE, 0, PewterCity_House1_EventScript_Nidoran, 0

PewterCity_House1_MapWarps:
	warp_def 3, 7, 0, 4, MAP_PEWTER_CITY
	warp_def 4, 7, 0, 4, MAP_PEWTER_CITY
	warp_def 5, 7, 0, 4, MAP_PEWTER_CITY

PewterCity_House1_MapEvents::
	map_events PewterCity_House1_ObjectEvents, PewterCity_House1_MapWarps, NULL, NULL

@ ===== END data/maps/PewterCity_House1/events.inc =====
@ ===== BEGIN data/maps/PewterCity_PokemonCenter_1F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/PewterCity_PokemonCenter_1F/map.json
@

	.align 2

PewterCity_PokemonCenter_1F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_JIGGLYPUFF, 2, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, PewterCity_PokemonCenter_1F_EventScript_Jigglypuff, 0
	object_event 2, OBJ_EVENT_GFX_GENTLEMAN, 4, 8, 3, MOVEMENT_TYPE_FACE_LEFT_AND_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, PewterCity_PokemonCenter_1F_EventScript_Gentleman, 0
	object_event 3, OBJ_EVENT_GFX_NURSE, 7, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, PewterCity_PokemonCenter_1F_EventScript_Nurse, 0
	object_event 4, OBJ_EVENT_GFX_YOUNGSTER, 1, 2, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, PewterCity_PokemonCenter_1F_EventScript_Youngster, 0
	object_event 5, OBJ_EVENT_GFX_WOMAN_1, 13, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, MysteryEventClub_EventScript_Woman, 0
	object_event 6, OBJ_EVENT_GFX_GBA_KID, 10, 7, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, PewterCity_PokemonCenter_1F_EventScript_GBAKid1, 0
	object_event 7, OBJ_EVENT_GFX_GBA_KID, 14, 6, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NONE, 0, PewterCity_PokemonCenter_1F_EventScript_GBAKid2, 0

PewterCity_PokemonCenter_1F_MapWarps:
	warp_def 6, 8, 0, 5, MAP_PEWTER_CITY
	warp_def 7, 8, 3, 5, MAP_PEWTER_CITY
	warp_def 8, 8, 0, 5, MAP_PEWTER_CITY
	warp_def 1, 6, 4, 0, MAP_PEWTER_CITY_POKEMON_CENTER_2F

PewterCity_PokemonCenter_1F_MapEvents::
	map_events PewterCity_PokemonCenter_1F_ObjectEvents, PewterCity_PokemonCenter_1F_MapWarps, NULL, NULL

@ ===== END data/maps/PewterCity_PokemonCenter_1F/events.inc =====
@ ===== BEGIN data/maps/PewterCity_PokemonCenter_2F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/PewterCity_PokemonCenter_2F/map.json
@

	.align 2

PewterCity_PokemonCenter_2F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_CABLE_CLUB_RECEPTIONIST, 6, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 0, 0, TRAINER_TYPE_NONE, 0, Common_EventScript_UnionRoomAttendant, 0
	object_event 2, OBJ_EVENT_GFX_CABLE_CLUB_RECEPTIONIST, 2, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 0, 0, TRAINER_TYPE_NONE, 0, Common_EventScript_WirelessClubAttendant, 0
	object_event 3, OBJ_EVENT_GFX_CABLE_CLUB_RECEPTIONIST, 10, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 0, 0, TRAINER_TYPE_NONE, 0, Common_EventScript_DirectCornerAttendant, 0
	object_event 4, OBJ_EVENT_GFX_MG_DELIVERYMAN, 1, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, CableClub_EventScript_MysteryGiftMan, FLAG_HIDE_MG_DELIVERYMEN

PewterCity_PokemonCenter_2F_MapWarps:
	warp_def 1, 6, 4, 3, MAP_PEWTER_CITY_POKEMON_CENTER_1F
	warp_def 5, 1, 0, 0, MAP_UNION_ROOM
	warp_def 9, 1, 0, 0, MAP_TRADE_CENTER

PewterCity_PokemonCenter_2F_MapEvents::
	map_events PewterCity_PokemonCenter_2F_ObjectEvents, PewterCity_PokemonCenter_2F_MapWarps, NULL, NULL

@ ===== END data/maps/PewterCity_PokemonCenter_2F/events.inc =====
@ ===== BEGIN data/maps/PewterCity_House2/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/PewterCity_House2/map.json
@

	.align 2

PewterCity_House2_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_OLD_MAN_1, 3, 3, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, PewterCity_House2_EventScript_OldMan, 0
	object_event 2, OBJ_EVENT_GFX_LITTLE_BOY, 5, 3, 3, MOVEMENT_TYPE_FACE_DOWN_AND_UP, 1, 1, TRAINER_TYPE_NONE, 0, PewterCity_House2_EventScript_LittleBoy, 0

PewterCity_House2_MapWarps:
	warp_def 3, 7, 0, 6, MAP_PEWTER_CITY
	warp_def 4, 7, 0, 6, MAP_PEWTER_CITY
	warp_def 5, 7, 0, 6, MAP_PEWTER_CITY

PewterCity_House2_MapEvents::
	map_events PewterCity_House2_ObjectEvents, PewterCity_House2_MapWarps, NULL, NULL

@ ===== END data/maps/PewterCity_House2/events.inc =====
@ ===== BEGIN data/maps/CeruleanCity_House1/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/CeruleanCity_House1/map.json
@

	.align 2

CeruleanCity_House1_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_GENTLEMAN, 6, 5, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, CeruleanCity_House1_EventScript_BadgeGuy, 0

CeruleanCity_House1_MapWarps:
	warp_def 2, 9, 0, 0, MAP_CERULEAN_CITY
	warp_def 3, 8, 3, 0, MAP_CERULEAN_CITY
	warp_def 4, 9, 0, 0, MAP_CERULEAN_CITY
	warp_def 3, 1, 3, 8, MAP_CERULEAN_CITY

CeruleanCity_House1_MapEvents::
	map_events CeruleanCity_House1_ObjectEvents, CeruleanCity_House1_MapWarps, NULL, NULL

@ ===== END data/maps/CeruleanCity_House1/events.inc =====
@ ===== BEGIN data/maps/CeruleanCity_House2/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/CeruleanCity_House2/map.json
@

	.align 2

CeruleanCity_House2_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_HIKER, 1, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, CeruleanCity_House2_EventScript_Hiker, 0
	object_event 2, OBJ_EVENT_GFX_LASS, 7, 6, 3, MOVEMENT_TYPE_WANDER_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, CeruleanCity_House2_EventScript_Lass, 0

CeruleanCity_House2_MapWarps:
	warp_def 2, 7, 0, 1, MAP_CERULEAN_CITY
	warp_def 3, 7, 0, 1, MAP_CERULEAN_CITY
	warp_def 4, 7, 1, 1, MAP_CERULEAN_CITY
	warp_def 4, 1, 0, 9, MAP_CERULEAN_CITY

CeruleanCity_House2_MapBGEvents:
	bg_sign_event 4, 1, 0, BG_EVENT_PLAYER_FACING_ANY, CeruleanCity_House2_EventScript_WallHole

CeruleanCity_House2_MapEvents::
	map_events CeruleanCity_House2_ObjectEvents, CeruleanCity_House2_MapWarps, NULL, CeruleanCity_House2_MapBGEvents

@ ===== END data/maps/CeruleanCity_House2/events.inc =====
@ ===== BEGIN data/maps/CeruleanCity_House3/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/CeruleanCity_House3/map.json
@

	.align 2

CeruleanCity_House3_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_OLD_MAN_1, 2, 2, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NONE, 0, CeruleanCity_House3_EventScript_Dontae, 0
	object_event 2, OBJ_EVENT_GFX_OLD_WOMAN, 7, 5, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NONE, 0, CeruleanCity_House3_EventScript_OldWoman, 0

CeruleanCity_House3_MapWarps:
	warp_def 3, 7, 0, 2, MAP_CERULEAN_CITY
	warp_def 4, 7, 0, 2, MAP_CERULEAN_CITY
	warp_def 5, 7, 0, 2, MAP_CERULEAN_CITY

CeruleanCity_House3_MapEvents::
	map_events CeruleanCity_House3_ObjectEvents, CeruleanCity_House3_MapWarps, NULL, NULL

@ ===== END data/maps/CeruleanCity_House3/events.inc =====
@ ===== BEGIN data/maps/CeruleanCity_PokemonCenter_1F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/CeruleanCity_PokemonCenter_1F/map.json
@

	.align 2

CeruleanCity_PokemonCenter_1F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_NURSE, 7, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, CeruleanCity_PokemonCenter_1F_EventScript_Nurse, 0
	object_event 2, OBJ_EVENT_GFX_GENTLEMAN, 12, 5, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, CeruleanCity_PokemonCenter_1F_EventScript_Gentleman, 0
	object_event 3, OBJ_EVENT_GFX_ROCKER, 5, 4, 3, MOVEMENT_TYPE_WANDER_LEFT_AND_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, CeruleanCity_PokemonCenter_1F_EventScript_Rocker, 0
	object_event 4, OBJ_EVENT_GFX_YOUNGSTER, 4, 8, 3, MOVEMENT_TYPE_WANDER_LEFT_AND_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, CeruleanCity_PokemonCenter_1F_EventScript_Youngster, 0
	object_event 5, OBJ_EVENT_GFX_LASS, 3, 3, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, CeruleanCity_PokemonCenter_1F_EventScript_Lass, 0
	object_event 6, 0, 2, 1, 0, MOVEMENT_TYPE_INVISIBLE, 1, 1, TRAINER_TYPE_NONE, 0, CeruleanCity_PokemonCenter_1F_EventScript_PokemonJournalMisty, FLAG_HIDE_POSTGAME_GOSSIPERS
	object_event 7, 0, 3, 1, 0, MOVEMENT_TYPE_INVISIBLE, 1, 1, TRAINER_TYPE_NONE, 0, CeruleanCity_PokemonCenter_1F_EventScript_PokemonJournalMisty, FLAG_HIDE_POSTGAME_GOSSIPERS

CeruleanCity_PokemonCenter_1F_MapWarps:
	warp_def 6, 8, 0, 3, MAP_CERULEAN_CITY
	warp_def 7, 8, 0, 3, MAP_CERULEAN_CITY
	warp_def 8, 8, 0, 3, MAP_CERULEAN_CITY
	warp_def 1, 6, 4, 0, MAP_CERULEAN_CITY_POKEMON_CENTER_2F

CeruleanCity_PokemonCenter_1F_MapEvents::
	map_events CeruleanCity_PokemonCenter_1F_ObjectEvents, CeruleanCity_PokemonCenter_1F_MapWarps, NULL, NULL

@ ===== END data/maps/CeruleanCity_PokemonCenter_1F/events.inc =====
@ ===== BEGIN data/maps/CeruleanCity_PokemonCenter_2F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/CeruleanCity_PokemonCenter_2F/map.json
@

	.align 2

CeruleanCity_PokemonCenter_2F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_CABLE_CLUB_RECEPTIONIST, 6, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 0, 0, TRAINER_TYPE_NONE, 0, Common_EventScript_UnionRoomAttendant, 0
	object_event 2, OBJ_EVENT_GFX_CABLE_CLUB_RECEPTIONIST, 2, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 0, 0, TRAINER_TYPE_NONE, 0, Common_EventScript_WirelessClubAttendant, 0
	object_event 3, OBJ_EVENT_GFX_CABLE_CLUB_RECEPTIONIST, 10, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 0, 0, TRAINER_TYPE_NONE, 0, Common_EventScript_DirectCornerAttendant, 0
	object_event 4, OBJ_EVENT_GFX_MG_DELIVERYMAN, 1, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, CableClub_EventScript_MysteryGiftMan, FLAG_HIDE_MG_DELIVERYMEN

CeruleanCity_PokemonCenter_2F_MapWarps:
	warp_def 1, 6, 4, 3, MAP_CERULEAN_CITY_POKEMON_CENTER_1F
	warp_def 5, 1, 0, 0, MAP_UNION_ROOM
	warp_def 9, 1, 0, 0, MAP_TRADE_CENTER

CeruleanCity_PokemonCenter_2F_MapEvents::
	map_events CeruleanCity_PokemonCenter_2F_ObjectEvents, CeruleanCity_PokemonCenter_2F_MapWarps, NULL, NULL

@ ===== END data/maps/CeruleanCity_PokemonCenter_2F/events.inc =====
@ ===== BEGIN data/maps/CeruleanCity_Gym/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/CeruleanCity_Gym/map.json
@

	.align 2

CeruleanCity_Gym_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_SWIMMER_M_WATER, 10, 12, 0, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NORMAL, 1, CeruleanCity_Gym_EventScript_Luis, 0
	object_event 2, OBJ_EVENT_GFX_PICNICKER, 4, 7, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 4, CeruleanCity_Gym_EventScript_Diana, 0
	object_event 3, OBJ_EVENT_GFX_MISTY, 8, 6, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, CeruleanCity_Gym_EventScript_Misty, 0
	object_event 4, OBJ_EVENT_GFX_GYM_GUY, 7, 16, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, CeruleanCity_Gym_EventScript_GymGuy, 0

CeruleanCity_Gym_MapWarps:
	warp_def 7, 18, 3, 4, MAP_CERULEAN_CITY
	warp_def 8, 18, 3, 4, MAP_CERULEAN_CITY
	warp_def 9, 18, 3, 4, MAP_CERULEAN_CITY

CeruleanCity_Gym_MapBGEvents:
	bg_sign_event 6, 17, 0, BG_EVENT_PLAYER_FACING_ANY, CeruleanCity_Gym_EventScript_GymStatue
	bg_sign_event 10, 17, 0, BG_EVENT_PLAYER_FACING_ANY, CeruleanCity_Gym_EventScript_GymStatue

CeruleanCity_Gym_MapEvents::
	map_events CeruleanCity_Gym_ObjectEvents, CeruleanCity_Gym_MapWarps, NULL, CeruleanCity_Gym_MapBGEvents

@ ===== END data/maps/CeruleanCity_Gym/events.inc =====
@ ===== BEGIN data/maps/CeruleanCity_BikeShop/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/CeruleanCity_BikeShop/map.json
@

	.align 2

CeruleanCity_BikeShop_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_MAN, 9, 3, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NONE, 0, CeruleanCity_BikeShop_EventScript_Clerk, 0
	object_event 2, OBJ_EVENT_GFX_YOUNGSTER, 9, 7, 3, MOVEMENT_TYPE_WANDER_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, CeruleanCity_BikeShop_EventScript_Youngster, 0
	object_event 3, OBJ_EVENT_GFX_WOMAN_2, 5, 5, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, CeruleanCity_BikeShop_EventScript_Woman, 0

CeruleanCity_BikeShop_MapWarps:
	warp_def 4, 9, 0, 5, MAP_CERULEAN_CITY
	warp_def 5, 8, 3, 5, MAP_CERULEAN_CITY
	warp_def 6, 9, 0, 5, MAP_CERULEAN_CITY

CeruleanCity_BikeShop_MapBGEvents:
	bg_sign_event 4, 3, 0, BG_EVENT_PLAYER_FACING_ANY, CeruleanCity_BikeShop_EventScript_Bicycle
	bg_sign_event 4, 4, 0, BG_EVENT_PLAYER_FACING_ANY, CeruleanCity_BikeShop_EventScript_Bicycle
	bg_sign_event 4, 5, 0, BG_EVENT_PLAYER_FACING_ANY, CeruleanCity_BikeShop_EventScript_Bicycle
	bg_sign_event 2, 3, 0, BG_EVENT_PLAYER_FACING_ANY, CeruleanCity_BikeShop_EventScript_Bicycle
	bg_sign_event 1, 4, 0, BG_EVENT_PLAYER_FACING_ANY, CeruleanCity_BikeShop_EventScript_Bicycle
	bg_sign_event 2, 5, 0, BG_EVENT_PLAYER_FACING_ANY, CeruleanCity_BikeShop_EventScript_Bicycle
	bg_sign_event 2, 7, 0, BG_EVENT_PLAYER_FACING_ANY, CeruleanCity_BikeShop_EventScript_Bicycle
	bg_sign_event 2, 8, 0, BG_EVENT_PLAYER_FACING_ANY, CeruleanCity_BikeShop_EventScript_Bicycle

CeruleanCity_BikeShop_MapEvents::
	map_events CeruleanCity_BikeShop_ObjectEvents, CeruleanCity_BikeShop_MapWarps, NULL, CeruleanCity_BikeShop_MapBGEvents

@ ===== END data/maps/CeruleanCity_BikeShop/events.inc =====
@ ===== BEGIN data/maps/CeruleanCity_Mart/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/CeruleanCity_Mart/map.json
@

	.align 2

CeruleanCity_Mart_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_CLERK, 2, 3, 0, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, CeruleanCity_Mart_EventScript_Clerk, 0
	object_event 2, OBJ_EVENT_GFX_WOMAN_1, 9, 2, 3, MOVEMENT_TYPE_WANDER_LEFT_AND_RIGHT, 4, 1, TRAINER_TYPE_NONE, 0, CeruleanCity_Mart_EventScript_Woman, 0
	object_event 3, OBJ_EVENT_GFX_YOUNGSTER, 1, 7, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NONE, 0, CeruleanCity_Mart_EventScript_Youngster, 0

CeruleanCity_Mart_MapWarps:
	warp_def 3, 7, 3, 6, MAP_CERULEAN_CITY
	warp_def 4, 7, 3, 6, MAP_CERULEAN_CITY
	warp_def 5, 7, 3, 6, MAP_CERULEAN_CITY

CeruleanCity_Mart_MapEvents::
	map_events CeruleanCity_Mart_ObjectEvents, CeruleanCity_Mart_MapWarps, NULL, NULL

@ ===== END data/maps/CeruleanCity_Mart/events.inc =====
@ ===== BEGIN data/maps/CeruleanCity_House4/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/CeruleanCity_House4/map.json
@

	.align 2

CeruleanCity_House4_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_OLD_MAN_1, 5, 3, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NONE, 0, CeruleanCity_House4_EventScript_WonderNewsBerryMan, 0

CeruleanCity_House4_MapWarps:
	warp_def 4, 7, 3, 12, MAP_CERULEAN_CITY

CeruleanCity_House4_MapEvents::
	map_events CeruleanCity_House4_ObjectEvents, CeruleanCity_House4_MapWarps, NULL, NULL

@ ===== END data/maps/CeruleanCity_House4/events.inc =====
@ ===== BEGIN data/maps/CeruleanCity_House5/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/CeruleanCity_House5/map.json
@

	.align 2

CeruleanCity_House5_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_OLD_MAN_2, 7, 4, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, CeruleanCity_House5_EventScript_BerryPowderMan, 0

CeruleanCity_House5_MapWarps:
	warp_def 4, 7, 3, 13, MAP_CERULEAN_CITY

CeruleanCity_House5_MapBGEvents:
	bg_sign_event 3, 1, 0, BG_EVENT_PLAYER_FACING_ANY, CeruleanCity_House5_EventScript_BerryCrushRankings

CeruleanCity_House5_MapEvents::
	map_events CeruleanCity_House5_ObjectEvents, CeruleanCity_House5_MapWarps, NULL, CeruleanCity_House5_MapBGEvents

@ ===== END data/maps/CeruleanCity_House5/events.inc =====
@ ===== BEGIN data/maps/LavenderTown_PokemonCenter_1F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/LavenderTown_PokemonCenter_1F/map.json
@

	.align 2

LavenderTown_PokemonCenter_1F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_NURSE, 7, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, LavenderTown_PokemonCenter_1F_EventScript_Nurse, 0
	object_event 2, OBJ_EVENT_GFX_GENTLEMAN, 9, 4, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, LavenderTown_PokemonCenter_1F_EventScript_Gentleman, 0
	object_event 3, OBJ_EVENT_GFX_LASS, 5, 6, 3, MOVEMENT_TYPE_WANDER_UP_AND_DOWN, 1, 2, TRAINER_TYPE_NONE, 0, LavenderTown_PokemonCenter_1F_EventScript_Lass, 0
	object_event 4, OBJ_EVENT_GFX_YOUNGSTER, 2, 2, 3, MOVEMENT_TYPE_WANDER_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, LavenderTown_PokemonCenter_1F_EventScript_Youngster, 0
	object_event 5, OBJ_EVENT_GFX_BALDING_MAN, 14, 6, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NONE, 0, LavenderTown_PokemonCenter_1F_EventScript_BaldingMan, FLAG_HIDE_POSTGAME_GOSSIPERS

LavenderTown_PokemonCenter_1F_MapWarps:
	warp_def 6, 8, 3, 1, MAP_LAVENDER_TOWN
	warp_def 7, 8, 3, 1, MAP_LAVENDER_TOWN
	warp_def 8, 8, 3, 1, MAP_LAVENDER_TOWN
	warp_def 1, 6, 4, 0, MAP_LAVENDER_TOWN_POKEMON_CENTER_2F

LavenderTown_PokemonCenter_1F_MapEvents::
	map_events LavenderTown_PokemonCenter_1F_ObjectEvents, LavenderTown_PokemonCenter_1F_MapWarps, NULL, NULL

@ ===== END data/maps/LavenderTown_PokemonCenter_1F/events.inc =====
@ ===== BEGIN data/maps/LavenderTown_PokemonCenter_2F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/LavenderTown_PokemonCenter_2F/map.json
@

	.align 2

LavenderTown_PokemonCenter_2F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_CABLE_CLUB_RECEPTIONIST, 6, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 0, 0, TRAINER_TYPE_NONE, 0, Common_EventScript_UnionRoomAttendant, 0
	object_event 2, OBJ_EVENT_GFX_CABLE_CLUB_RECEPTIONIST, 2, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 0, 0, TRAINER_TYPE_NONE, 0, Common_EventScript_WirelessClubAttendant, 0
	object_event 3, OBJ_EVENT_GFX_CABLE_CLUB_RECEPTIONIST, 10, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 0, 0, TRAINER_TYPE_NONE, 0, Common_EventScript_DirectCornerAttendant, 0
	object_event 4, OBJ_EVENT_GFX_MG_DELIVERYMAN, 1, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, CableClub_EventScript_MysteryGiftMan, FLAG_HIDE_MG_DELIVERYMEN

LavenderTown_PokemonCenter_2F_MapWarps:
	warp_def 1, 6, 4, 3, MAP_LAVENDER_TOWN_POKEMON_CENTER_1F
	warp_def 5, 1, 0, 0, MAP_UNION_ROOM
	warp_def 9, 1, 0, 0, MAP_TRADE_CENTER

LavenderTown_PokemonCenter_2F_MapEvents::
	map_events LavenderTown_PokemonCenter_2F_ObjectEvents, LavenderTown_PokemonCenter_2F_MapWarps, NULL, NULL

@ ===== END data/maps/LavenderTown_PokemonCenter_2F/events.inc =====
@ ===== BEGIN data/maps/LavenderTown_VolunteerPokemonHouse/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/LavenderTown_VolunteerPokemonHouse/map.json
@

	.align 2

LavenderTown_VolunteerPokemonHouse_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_MR_FUJI, 3, 3, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, LavenderTown_VolunteerPokemonHouse_EventScript_MrFuji, FLAG_HIDE_POKEHOUSE_FUJI
	object_event 2, OBJ_EVENT_GFX_NIDORINO, 1, 4, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, LavenderTown_VolunteerPokemonHouse_EventScript_Nidorino, 0
	object_event 3, OBJ_EVENT_GFX_PSYDUCK, 9, 6, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NONE, 0, LavenderTown_VolunteerPokemonHouse_EventScript_Psyduck, 0
	object_event 4, OBJ_EVENT_GFX_LITTLE_BOY, 9, 5, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, LavenderTown_VolunteerPokemonHouse_EventScript_LittleBoy, 0
	object_event 5, OBJ_EVENT_GFX_YOUNGSTER, 3, 5, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, LavenderTown_VolunteerPokemonHouse_EventScript_Youngster, 0
	object_event 6, OBJ_EVENT_GFX_LITTLE_GIRL, 7, 2, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, LavenderTown_VolunteerPokemonHouse_EventScript_LittleGirl, 0

LavenderTown_VolunteerPokemonHouse_MapWarps:
	warp_def 3, 7, 3, 2, MAP_LAVENDER_TOWN
	warp_def 4, 7, 3, 2, MAP_LAVENDER_TOWN
	warp_def 5, 7, 3, 2, MAP_LAVENDER_TOWN

LavenderTown_VolunteerPokemonHouse_MapBGEvents:
	bg_sign_event 5, 4, 0, BG_EVENT_PLAYER_FACING_ANY, LavenderTown_VolunteerPokemonHouse_EventScript_PokemonFanMagazine
	bg_sign_event 3, 1, 0, BG_EVENT_PLAYER_FACING_ANY, LavenderTown_VolunteerPokemonHouse_EventScript_Bookshelf
	bg_sign_event 4, 1, 0, BG_EVENT_PLAYER_FACING_ANY, LavenderTown_VolunteerPokemonHouse_EventScript_Bookshelf

LavenderTown_VolunteerPokemonHouse_MapEvents::
	map_events LavenderTown_VolunteerPokemonHouse_ObjectEvents, LavenderTown_VolunteerPokemonHouse_MapWarps, NULL, LavenderTown_VolunteerPokemonHouse_MapBGEvents

@ ===== END data/maps/LavenderTown_VolunteerPokemonHouse/events.inc =====
@ ===== BEGIN data/maps/LavenderTown_House1/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/LavenderTown_House1/map.json
@

	.align 2

LavenderTown_House1_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_COOLTRAINER_F, 4, 4, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, LavenderTown_House1_EventScript_CooltrainerF, 0
	object_event 2, OBJ_EVENT_GFX_CUBONE, 8, 6, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, LavenderTown_House1_EventScript_Cubone, 0

LavenderTown_House1_MapWarps:
	warp_def 3, 7, 3, 3, MAP_LAVENDER_TOWN
	warp_def 4, 7, 3, 3, MAP_LAVENDER_TOWN
	warp_def 5, 7, 3, 3, MAP_LAVENDER_TOWN

LavenderTown_House1_MapEvents::
	map_events LavenderTown_House1_ObjectEvents, LavenderTown_House1_MapWarps, NULL, NULL

@ ===== END data/maps/LavenderTown_House1/events.inc =====
@ ===== BEGIN data/maps/LavenderTown_House2/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/LavenderTown_House2/map.json
@

	.align 2

LavenderTown_House2_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_GENTLEMAN, 4, 4, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, LavenderTown_House2_EventScript_NameRater, 0

LavenderTown_House2_MapWarps:
	warp_def 3, 7, 3, 4, MAP_LAVENDER_TOWN
	warp_def 4, 7, 3, 4, MAP_LAVENDER_TOWN
	warp_def 5, 7, 3, 4, MAP_LAVENDER_TOWN

LavenderTown_House2_MapEvents::
	map_events LavenderTown_House2_ObjectEvents, LavenderTown_House2_MapWarps, NULL, NULL

@ ===== END data/maps/LavenderTown_House2/events.inc =====
@ ===== BEGIN data/maps/LavenderTown_Mart/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/LavenderTown_Mart/map.json
@

	.align 2

LavenderTown_Mart_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_CLERK, 2, 3, 0, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, LavenderTown_Mart_EventScript_Clerk, 0
	object_event 2, OBJ_EVENT_GFX_BALDING_MAN, 6, 2, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, LavenderTown_Mart_EventScript_BaldingMan, 0
	object_event 3, OBJ_EVENT_GFX_ROCKER, 9, 2, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, LavenderTown_Mart_EventScript_Rocker, 0
	object_event 4, OBJ_EVENT_GFX_YOUNGSTER, 9, 5, 3, MOVEMENT_TYPE_FACE_LEFT_AND_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, LavenderTown_Mart_EventScript_Youngster, 0

LavenderTown_Mart_MapWarps:
	warp_def 3, 7, 3, 5, MAP_LAVENDER_TOWN
	warp_def 4, 7, 3, 5, MAP_LAVENDER_TOWN
	warp_def 5, 7, 3, 5, MAP_LAVENDER_TOWN

LavenderTown_Mart_MapEvents::
	map_events LavenderTown_Mart_ObjectEvents, LavenderTown_Mart_MapWarps, NULL, NULL

@ ===== END data/maps/LavenderTown_Mart/events.inc =====
@ ===== BEGIN data/maps/VermilionCity_House1/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/VermilionCity_House1/map.json
@

	.align 2

VermilionCity_House1_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_FISHER, 4, 5, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, VermilionCity_House1_EventScript_FishingGuru, 0

VermilionCity_House1_MapWarps:
	warp_def 3, 7, 3, 3, MAP_VERMILION_CITY
	warp_def 4, 7, 3, 3, MAP_VERMILION_CITY
	warp_def 5, 7, 3, 3, MAP_VERMILION_CITY

VermilionCity_House1_MapEvents::
	map_events VermilionCity_House1_ObjectEvents, VermilionCity_House1_MapWarps, NULL, NULL

@ ===== END data/maps/VermilionCity_House1/events.inc =====
@ ===== BEGIN data/maps/VermilionCity_PokemonCenter_1F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/VermilionCity_PokemonCenter_1F/map.json
@

	.align 2

VermilionCity_PokemonCenter_1F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_NURSE, 7, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, VermilionCity_PokemonCenter_1F_EventScript_Nurse, 0
	object_event 2, OBJ_EVENT_GFX_MAN, 4, 8, 3, MOVEMENT_TYPE_WANDER_LEFT_AND_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, VermilionCity_PokemonCenter_1F_EventScript_Man, 0
	object_event 3, OBJ_EVENT_GFX_HIKER, 12, 5, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, VermilionCity_PokemonCenter_1F_EventScript_Hiker, 0
	object_event 4, OBJ_EVENT_GFX_YOUNGSTER, 14, 4, 3, MOVEMENT_TYPE_WANDER_UP_AND_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, VermilionCity_PokemonCenter_1F_EventScript_Youngster, 0
	object_event 5, OBJ_EVENT_GFX_COOLTRAINER_F, 6, 4, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, VermilionCity_PokemonCenter_1F_EventScript_VSSeekerWoman, 0
	object_event 6, 0, 2, 1, 0, MOVEMENT_TYPE_INVISIBLE, 1, 1, TRAINER_TYPE_NONE, 0, VermilionCity_PokemonCenter_1F_EventScript_PokemonJournalLtSurge, FLAG_HIDE_FAME_CHECKER_LT_SURGE_JOURNAL
	object_event 7, 0, 3, 1, 0, MOVEMENT_TYPE_INVISIBLE, 1, 1, TRAINER_TYPE_NONE, 0, VermilionCity_PokemonCenter_1F_EventScript_PokemonJournalLtSurge, FLAG_HIDE_FAME_CHECKER_LT_SURGE_JOURNAL

VermilionCity_PokemonCenter_1F_MapWarps:
	warp_def 6, 8, 3, 4, MAP_VERMILION_CITY
	warp_def 7, 8, 3, 4, MAP_VERMILION_CITY
	warp_def 8, 8, 3, 4, MAP_VERMILION_CITY
	warp_def 1, 6, 4, 0, MAP_VERMILION_CITY_POKEMON_CENTER_2F

VermilionCity_PokemonCenter_1F_MapEvents::
	map_events VermilionCity_PokemonCenter_1F_ObjectEvents, VermilionCity_PokemonCenter_1F_MapWarps, NULL, NULL

@ ===== END data/maps/VermilionCity_PokemonCenter_1F/events.inc =====
@ ===== BEGIN data/maps/VermilionCity_PokemonCenter_2F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/VermilionCity_PokemonCenter_2F/map.json
@

	.align 2

VermilionCity_PokemonCenter_2F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_CABLE_CLUB_RECEPTIONIST, 6, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 0, 0, TRAINER_TYPE_NONE, 0, Common_EventScript_UnionRoomAttendant, 0
	object_event 2, OBJ_EVENT_GFX_CABLE_CLUB_RECEPTIONIST, 2, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 0, 0, TRAINER_TYPE_NONE, 0, Common_EventScript_WirelessClubAttendant, 0
	object_event 3, OBJ_EVENT_GFX_CABLE_CLUB_RECEPTIONIST, 10, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 0, 0, TRAINER_TYPE_NONE, 0, Common_EventScript_DirectCornerAttendant, 0
	object_event 4, OBJ_EVENT_GFX_MG_DELIVERYMAN, 1, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, CableClub_EventScript_MysteryGiftMan, FLAG_HIDE_MG_DELIVERYMEN

VermilionCity_PokemonCenter_2F_MapWarps:
	warp_def 1, 6, 4, 3, MAP_VERMILION_CITY_POKEMON_CENTER_1F
	warp_def 5, 1, 0, 0, MAP_UNION_ROOM
	warp_def 9, 1, 0, 0, MAP_TRADE_CENTER

VermilionCity_PokemonCenter_2F_MapEvents::
	map_events VermilionCity_PokemonCenter_2F_ObjectEvents, VermilionCity_PokemonCenter_2F_MapWarps, NULL, NULL

@ ===== END data/maps/VermilionCity_PokemonCenter_2F/events.inc =====
@ ===== BEGIN data/maps/VermilionCity_PokemonFanClub/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/VermilionCity_PokemonFanClub/map.json
@

	.align 2

VermilionCity_PokemonFanClub_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_GENTLEMAN, 5, 4, 4, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, VermilionCity_PokemonFanClub_EventScript_Chairman, 0
	object_event 2, OBJ_EVENT_GFX_WORKER_F, 6, 4, 4, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, VermilionCity_PokemonFanClub_EventScript_WorkerF, 0
	object_event 3, OBJ_EVENT_GFX_PIKACHU, 7, 6, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, VermilionCity_PokemonFanClub_EventScript_Pikachu, 0
	object_event 4, OBJ_EVENT_GFX_SEEL, 4, 6, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, VermilionCity_PokemonFanClub_EventScript_Seel, 0
	object_event 5, OBJ_EVENT_GFX_WOMAN_1, 4, 5, 0, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, VermilionCity_PokemonFanClub_EventScript_Woman, 0
	object_event 6, OBJ_EVENT_GFX_FAT_MAN, 7, 5, 0, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, VermilionCity_PokemonFanClub_EventScript_FatMan, 0

VermilionCity_PokemonFanClub_MapWarps:
	warp_def 4, 10, 3, 5, MAP_VERMILION_CITY
	warp_def 5, 10, 3, 5, MAP_VERMILION_CITY
	warp_def 6, 10, 3, 5, MAP_VERMILION_CITY

VermilionCity_PokemonFanClub_MapBGEvents:
	bg_sign_event 2, 1, 0, BG_EVENT_PLAYER_FACING_ANY, VermilionCity_PokemonFanClub_EventScript_RulesSign1
	bg_sign_event 9, 1, 0, BG_EVENT_PLAYER_FACING_ANY, VermilionCity_PokemonFanClub_EventScript_RulesSign2

VermilionCity_PokemonFanClub_MapEvents::
	map_events VermilionCity_PokemonFanClub_ObjectEvents, VermilionCity_PokemonFanClub_MapWarps, NULL, VermilionCity_PokemonFanClub_MapBGEvents

@ ===== END data/maps/VermilionCity_PokemonFanClub/events.inc =====
@ ===== BEGIN data/maps/VermilionCity_House2/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/VermilionCity_House2/map.json
@

	.align 2

VermilionCity_House2_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_LITTLE_GIRL, 4, 4, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NONE, 0, VermilionCity_House2_EventScript_Elyssa, 0

VermilionCity_House2_MapWarps:
	warp_def 3, 7, 3, 6, MAP_VERMILION_CITY
	warp_def 4, 7, 3, 6, MAP_VERMILION_CITY
	warp_def 5, 7, 3, 6, MAP_VERMILION_CITY

VermilionCity_House2_MapEvents::
	map_events VermilionCity_House2_ObjectEvents, VermilionCity_House2_MapWarps, NULL, NULL

@ ===== END data/maps/VermilionCity_House2/events.inc =====
@ ===== BEGIN data/maps/VermilionCity_Mart/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/VermilionCity_Mart/map.json
@

	.align 2

VermilionCity_Mart_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_CLERK, 2, 3, 0, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, VermilionCity_Mart_EventScript_Clerk, 0
	object_event 2, OBJ_EVENT_GFX_COOLTRAINER_F, 4, 2, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NONE, 0, VermilionCity_Mart_EventScript_CooltrainerF, 0
	object_event 3, OBJ_EVENT_GFX_BALDING_MAN, 9, 4, 3, MOVEMENT_TYPE_WANDER_AROUND, 1, 2, TRAINER_TYPE_NONE, 0, VermilionCity_Mart_EventScript_BaldingMan, 0

VermilionCity_Mart_MapWarps:
	warp_def 3, 7, 3, 7, MAP_VERMILION_CITY
	warp_def 4, 7, 3, 7, MAP_VERMILION_CITY
	warp_def 5, 7, 3, 7, MAP_VERMILION_CITY

VermilionCity_Mart_MapEvents::
	map_events VermilionCity_Mart_ObjectEvents, VermilionCity_Mart_MapWarps, NULL, NULL

@ ===== END data/maps/VermilionCity_Mart/events.inc =====
@ ===== BEGIN data/maps/VermilionCity_Gym/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/VermilionCity_Gym/map.json
@

	.align 2

VermilionCity_Gym_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_LT_SURGE, 5, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, VermilionCity_Gym_EventScript_LtSurge, 0
	object_event 2, OBJ_EVENT_GFX_BALDING_MAN, 2, 11, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NORMAL, 3, VermilionCity_Gym_EventScript_Baily, 0
	object_event 3, OBJ_EVENT_GFX_SAILOR, 8, 13, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NORMAL, 3, VermilionCity_Gym_EventScript_Dwayne, 0
	object_event 4, OBJ_EVENT_GFX_GYM_GUY, 4, 17, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, VermilionCity_Gym_EventScript_GymGuy, 0
	object_event 5, OBJ_EVENT_GFX_GENTLEMAN, 7, 8, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NORMAL, 3, VermilionCity_Gym_EventScript_Tucker, 0

VermilionCity_Gym_MapWarps:
	warp_def 4, 19, 3, 9, MAP_VERMILION_CITY
	warp_def 5, 19, 3, 9, MAP_VERMILION_CITY
	warp_def 6, 19, 3, 9, MAP_VERMILION_CITY

VermilionCity_Gym_MapBGEvents:
	bg_sign_event 3, 17, 0, BG_EVENT_PLAYER_FACING_ANY, VermilionCity_Gym_EventScript_GymStatue
	bg_sign_event 7, 17, 0, BG_EVENT_PLAYER_FACING_ANY, VermilionCity_Gym_EventScript_GymStatue
	bg_sign_event 1, 10, 0, BG_EVENT_PLAYER_FACING_ANY, VermilionCity_Gym_EventScript_TrashCan1
	bg_sign_event 3, 10, 0, BG_EVENT_PLAYER_FACING_ANY, VermilionCity_Gym_EventScript_TrashCan2
	bg_sign_event 5, 10, 0, BG_EVENT_PLAYER_FACING_ANY, VermilionCity_Gym_EventScript_TrashCan3
	bg_sign_event 7, 10, 0, BG_EVENT_PLAYER_FACING_ANY, VermilionCity_Gym_EventScript_TrashCan4
	bg_sign_event 9, 10, 0, BG_EVENT_PLAYER_FACING_ANY, VermilionCity_Gym_EventScript_TrashCan5
	bg_sign_event 1, 12, 0, BG_EVENT_PLAYER_FACING_ANY, VermilionCity_Gym_EventScript_TrashCan6
	bg_sign_event 3, 12, 0, BG_EVENT_PLAYER_FACING_ANY, VermilionCity_Gym_EventScript_TrashCan7
	bg_sign_event 5, 12, 0, BG_EVENT_PLAYER_FACING_ANY, VermilionCity_Gym_EventScript_TrashCan8
	bg_sign_event 7, 12, 0, BG_EVENT_PLAYER_FACING_ANY, VermilionCity_Gym_EventScript_TrashCan9
	bg_sign_event 9, 12, 0, BG_EVENT_PLAYER_FACING_ANY, VermilionCity_Gym_EventScript_TrashCan10
	bg_sign_event 1, 14, 0, BG_EVENT_PLAYER_FACING_ANY, VermilionCity_Gym_EventScript_TrashCan11
	bg_sign_event 3, 14, 0, BG_EVENT_PLAYER_FACING_ANY, VermilionCity_Gym_EventScript_TrashCan12
	bg_sign_event 5, 14, 0, BG_EVENT_PLAYER_FACING_ANY, VermilionCity_Gym_EventScript_TrashCan13
	bg_sign_event 7, 14, 0, BG_EVENT_PLAYER_FACING_ANY, VermilionCity_Gym_EventScript_TrashCan14
	bg_sign_event 9, 14, 0, BG_EVENT_PLAYER_FACING_ANY, VermilionCity_Gym_EventScript_TrashCan15

VermilionCity_Gym_MapEvents::
	map_events VermilionCity_Gym_ObjectEvents, VermilionCity_Gym_MapWarps, NULL, VermilionCity_Gym_MapBGEvents

@ ===== END data/maps/VermilionCity_Gym/events.inc =====
@ ===== BEGIN data/maps/VermilionCity_House3/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/VermilionCity_House3/map.json
@

	.align 2

VermilionCity_House3_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_BOY, 7, 4, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NONE, 0, VermilionCity_House3_EventScript_Boy, 0
	object_event 2, OBJ_EVENT_GFX_PIDGEY, 2, 5, 3, MOVEMENT_TYPE_WANDER_LEFT_AND_RIGHT, 2, 1, TRAINER_TYPE_NONE, 0, VermilionCity_House3_EventScript_Pidgey, 0
	object_event 3, OBJ_EVENT_GFX_CLIPBOARD, 6, 4, 0, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, 0x0, 0
	object_event 4, OBJ_EVENT_GFX_LASS, 2, 4, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, VermilionCity_House3_EventScript_Lass, 0

VermilionCity_House3_MapWarps:
	warp_def 3, 7, 3, 8, MAP_VERMILION_CITY
	warp_def 4, 7, 3, 8, MAP_VERMILION_CITY
	warp_def 5, 7, 3, 8, MAP_VERMILION_CITY

VermilionCity_House3_MapBGEvents:
	bg_sign_event 6, 4, 3, BG_EVENT_PLAYER_FACING_ANY, VermilionCity_House3_EventScript_Letter

VermilionCity_House3_MapEvents::
	map_events VermilionCity_House3_ObjectEvents, VermilionCity_House3_MapWarps, NULL, VermilionCity_House3_MapBGEvents

@ ===== END data/maps/VermilionCity_House3/events.inc =====
@ ===== BEGIN data/maps/CeladonCity_DepartmentStore_1F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/CeladonCity_DepartmentStore_1F/map.json
@

	.align 2

CeladonCity_DepartmentStore_1F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_WORKER_F, 6, 10, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, CeladonCity_DepartmentStore_1F_EventScript_Receptionist, 0

CeladonCity_DepartmentStore_1F_MapWarps:
	warp_def 1, 15, 0, 1, MAP_CELADON_CITY
	warp_def 2, 14, 3, 1, MAP_CELADON_CITY
	warp_def 3, 15, 0, 1, MAP_CELADON_CITY
	warp_def 9, 15, 0, 2, MAP_CELADON_CITY
	warp_def 10, 14, 3, 2, MAP_CELADON_CITY
	warp_def 11, 15, 0, 2, MAP_CELADON_CITY
	warp_def 6, 1, 0, 0, MAP_CELADON_CITY_DEPARTMENT_STORE_ELEVATOR
	warp_def 4, 2, 3, 1, MAP_CELADON_CITY_DEPARTMENT_STORE_2F

CeladonCity_DepartmentStore_1F_MapBGEvents:
	bg_sign_event 9, 11, 0, BG_EVENT_PLAYER_FACING_ANY, CeladonCity_DepartmentStore_1F_EventScript_LayoutSign
	bg_sign_event 8, 1, 0, BG_EVENT_PLAYER_FACING_ANY, CeladonCity_DepartmentStore_1F_EventScript_FloorSign

CeladonCity_DepartmentStore_1F_MapEvents::
	map_events CeladonCity_DepartmentStore_1F_ObjectEvents, CeladonCity_DepartmentStore_1F_MapWarps, NULL, CeladonCity_DepartmentStore_1F_MapBGEvents

@ ===== END data/maps/CeladonCity_DepartmentStore_1F/events.inc =====
@ ===== BEGIN data/maps/CeladonCity_DepartmentStore_2F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/CeladonCity_DepartmentStore_2F/map.json
@

	.align 2

CeladonCity_DepartmentStore_2F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_LASS, 5, 10, 3, MOVEMENT_TYPE_WANDER_UP_AND_DOWN, 2, 1, TRAINER_TYPE_NONE, 0, CeladonCity_DepartmentStore_2F_EventScript_Lass, 0
	object_event 2, OBJ_EVENT_GFX_CLERK, 1, 8, 0, MOVEMENT_TYPE_FACE_DOWN, 3, 1, TRAINER_TYPE_NONE, 0, CeladonCity_DepartmentStore_2F_EventScript_ClerkItems, 0
	object_event 3, OBJ_EVENT_GFX_CLERK, 1, 6, 3, MOVEMENT_TYPE_FACE_RIGHT, 3, 1, TRAINER_TYPE_NONE, 0, CeladonCity_DepartmentStore_2F_EventScript_ClerkTMs, 0
	object_event 4, OBJ_EVENT_GFX_WOMAN_1, 11, 6, 3, MOVEMENT_TYPE_WANDER_LEFT_AND_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, CeladonCity_DepartmentStore_2F_EventScript_Woman, FLAG_HIDE_POSTGAME_GOSSIPERS

CeladonCity_DepartmentStore_2F_MapWarps:
	warp_def 6, 1, 0, 0, MAP_CELADON_CITY_DEPARTMENT_STORE_ELEVATOR
	warp_def 3, 2, 3, 7, MAP_CELADON_CITY_DEPARTMENT_STORE_1F
	warp_def 9, 2, 3, 1, MAP_CELADON_CITY_DEPARTMENT_STORE_3F

CeladonCity_DepartmentStore_2F_MapBGEvents:
	bg_sign_event 4, 1, 0, BG_EVENT_PLAYER_FACING_ANY, CeladonCity_DepartmentStore_2F_EventScript_FloorSign

CeladonCity_DepartmentStore_2F_MapEvents::
	map_events CeladonCity_DepartmentStore_2F_ObjectEvents, CeladonCity_DepartmentStore_2F_MapWarps, NULL, CeladonCity_DepartmentStore_2F_MapBGEvents

@ ===== END data/maps/CeladonCity_DepartmentStore_2F/events.inc =====
@ ===== BEGIN data/maps/CeladonCity_DepartmentStore_3F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/CeladonCity_DepartmentStore_3F/map.json
@

	.align 2

CeladonCity_DepartmentStore_3F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_CLERK, 10, 9, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NONE, 0, CeladonCity_DepartmentStore_3F_EventScript_CounterTutor, 0
	object_event 2, OBJ_EVENT_GFX_GBA_KID, 11, 6, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, CeladonCity_DepartmentStore_3F_EventScript_GBAKid1, 0
	object_event 3, OBJ_EVENT_GFX_GBA_KID, 4, 9, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, CeladonCity_DepartmentStore_3F_EventScript_GBAKid3, 0
	object_event 4, OBJ_EVENT_GFX_GBA_KID, 1, 9, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, CeladonCity_DepartmentStore_3F_EventScript_GBAKid2, 0
	object_event 5, OBJ_EVENT_GFX_LITTLE_GIRL, 9, 14, 3, MOVEMENT_TYPE_FACE_LEFT_AND_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, CeladonCity_DepartmentStore_3F_EventScript_LittleGirl, 0

CeladonCity_DepartmentStore_3F_MapWarps:
	warp_def 6, 1, 0, 0, MAP_CELADON_CITY_DEPARTMENT_STORE_ELEVATOR
	warp_def 9, 2, 0, 2, MAP_CELADON_CITY_DEPARTMENT_STORE_2F
	warp_def 3, 2, 0, 1, MAP_CELADON_CITY_DEPARTMENT_STORE_4F

CeladonCity_DepartmentStore_3F_MapBGEvents:
	bg_sign_event 8, 1, 0, BG_EVENT_PLAYER_FACING_ANY, CeladonCity_DepartmentStore_3F_EventScript_FloorSign
	bg_sign_event 2, 8, 0, BG_EVENT_PLAYER_FACING_NORTH, CeladonCity_DepartmentStore_3F_EventScript_TV1
	bg_sign_event 5, 8, 0, BG_EVENT_PLAYER_FACING_NORTH, CeladonCity_DepartmentStore_3F_EventScript_TV2
	bg_sign_event 2, 11, 0, BG_EVENT_PLAYER_FACING_NORTH, CeladonCity_DepartmentStore_3F_EventScript_TV3
	bg_sign_event 5, 11, 0, BG_EVENT_PLAYER_FACING_NORTH, CeladonCity_DepartmentStore_3F_EventScript_TV4
	bg_sign_event 1, 8, 0, BG_EVENT_PLAYER_FACING_ANY, CeladonCity_DepartmentStore_3F_EventScript_SuperNES
	bg_sign_event 1, 11, 0, BG_EVENT_PLAYER_FACING_ANY, CeladonCity_DepartmentStore_3F_EventScript_SuperNES
	bg_sign_event 4, 8, 0, BG_EVENT_PLAYER_FACING_ANY, CeladonCity_DepartmentStore_3F_EventScript_SuperNES
	bg_sign_event 4, 11, 0, BG_EVENT_PLAYER_FACING_ANY, CeladonCity_DepartmentStore_3F_EventScript_SuperNES
	bg_sign_event 2, 4, 0, BG_EVENT_PLAYER_FACING_NORTH, CeladonCity_DepartmentStore_3F_EventScript_Poster
	bg_sign_event 0, 4, 0, BG_EVENT_PLAYER_FACING_NORTH, CeladonCity_DepartmentStore_3F_EventScript_Poster

CeladonCity_DepartmentStore_3F_MapEvents::
	map_events CeladonCity_DepartmentStore_3F_ObjectEvents, CeladonCity_DepartmentStore_3F_MapWarps, NULL, CeladonCity_DepartmentStore_3F_MapBGEvents

@ ===== END data/maps/CeladonCity_DepartmentStore_3F/events.inc =====
@ ===== BEGIN data/maps/CeladonCity_DepartmentStore_4F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/CeladonCity_DepartmentStore_4F/map.json
@

	.align 2

CeladonCity_DepartmentStore_4F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_MAN, 6, 6, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, CeladonCity_DepartmentStore_4F_EventScript_Man, 0
	object_event 2, OBJ_EVENT_GFX_YOUNGSTER, 10, 11, 3, MOVEMENT_TYPE_WANDER_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, CeladonCity_DepartmentStore_4F_EventScript_Youngster, 0
	object_event 3, OBJ_EVENT_GFX_CLERK, 3, 13, 0, MOVEMENT_TYPE_FACE_UP, 3, 1, TRAINER_TYPE_NONE, 0, CeladonCity_DepartmentStore_4F_EventScript_Clerk, 0

CeladonCity_DepartmentStore_4F_MapWarps:
	warp_def 6, 1, 0, 0, MAP_CELADON_CITY_DEPARTMENT_STORE_ELEVATOR
	warp_def 3, 2, 0, 2, MAP_CELADON_CITY_DEPARTMENT_STORE_3F
	warp_def 9, 2, 0, 1, MAP_CELADON_CITY_DEPARTMENT_STORE_5F

CeladonCity_DepartmentStore_4F_MapBGEvents:
	bg_sign_event 4, 1, 0, BG_EVENT_PLAYER_FACING_ANY, CeladonCity_DepartmentStore_4F_EventScript_FloorSign

CeladonCity_DepartmentStore_4F_MapEvents::
	map_events CeladonCity_DepartmentStore_4F_ObjectEvents, CeladonCity_DepartmentStore_4F_MapWarps, NULL, CeladonCity_DepartmentStore_4F_MapBGEvents

@ ===== END data/maps/CeladonCity_DepartmentStore_4F/events.inc =====
@ ===== BEGIN data/maps/CeladonCity_DepartmentStore_5F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/CeladonCity_DepartmentStore_5F/map.json
@

	.align 2

CeladonCity_DepartmentStore_5F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_GENTLEMAN, 11, 6, 3, MOVEMENT_TYPE_WANDER_LEFT_AND_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, CeladonCity_DepartmentStore_5F_EventScript_Gentleman, 0
	object_event 2, OBJ_EVENT_GFX_SAILOR, 6, 8, 3, MOVEMENT_TYPE_WANDER_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, CeladonCity_DepartmentStore_5F_EventScript_Sailor, 0
	object_event 3, OBJ_EVENT_GFX_CLERK, 1, 7, 3, MOVEMENT_TYPE_FACE_DOWN, 2, 1, TRAINER_TYPE_NONE, 0, CeladonCity_DepartmentStore_5F_EventScript_ClerkXItems, 0
	object_event 4, OBJ_EVENT_GFX_CLERK, 1, 6, 3, MOVEMENT_TYPE_FACE_RIGHT, 2, 1, TRAINER_TYPE_NONE, 0, CeladonCity_DepartmentStore_5F_EventScript_ClerkVitamins, 0

CeladonCity_DepartmentStore_5F_MapWarps:
	warp_def 6, 1, 0, 0, MAP_CELADON_CITY_DEPARTMENT_STORE_ELEVATOR
	warp_def 9, 2, 3, 2, MAP_CELADON_CITY_DEPARTMENT_STORE_4F
	warp_def 3, 2, 3, 0, MAP_CELADON_CITY_DEPARTMENT_STORE_ROOF

CeladonCity_DepartmentStore_5F_MapBGEvents:
	bg_sign_event 8, 1, 0, BG_EVENT_PLAYER_FACING_ANY, CeladonCity_DepartmentStore_5F_EventScript_FloorSign

CeladonCity_DepartmentStore_5F_MapEvents::
	map_events CeladonCity_DepartmentStore_5F_ObjectEvents, CeladonCity_DepartmentStore_5F_MapWarps, NULL, CeladonCity_DepartmentStore_5F_MapBGEvents

@ ===== END data/maps/CeladonCity_DepartmentStore_5F/events.inc =====
@ ===== BEGIN data/maps/CeladonCity_DepartmentStore_Roof/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/CeladonCity_DepartmentStore_Roof/map.json
@

	.align 2

CeladonCity_DepartmentStore_Roof_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_COOLTRAINER_M, 9, 5, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NONE, 0, CeladonCity_DepartmentStore_Roof_EventScript_CooltrainerM, 0
	object_event 2, OBJ_EVENT_GFX_LITTLE_GIRL, 5, 4, 3, MOVEMENT_TYPE_WANDER_AROUND, 2, 1, TRAINER_TYPE_NONE, 0, CeladonCity_DepartmentStore_Roof_EventScript_ThirstyGirl, 0

CeladonCity_DepartmentStore_Roof_MapWarps:
	warp_def 15, 6, 3, 2, MAP_CELADON_CITY_DEPARTMENT_STORE_5F

CeladonCity_DepartmentStore_Roof_MapBGEvents:
	bg_sign_event 14, 3, 0, BG_EVENT_PLAYER_FACING_ANY, CeladonCity_DepartmentStore_Roof_EventScript_FloorSign
	bg_sign_event 10, 3, 0, BG_EVENT_PLAYER_FACING_ANY, CeladonCity_DepartmentStore_Roof_EventScript_VendingMachine
	bg_sign_event 11, 3, 0, BG_EVENT_PLAYER_FACING_ANY, CeladonCity_DepartmentStore_Roof_EventScript_VendingMachine
	bg_sign_event 12, 3, 0, BG_EVENT_PLAYER_FACING_ANY, CeladonCity_DepartmentStore_Roof_EventScript_VendingMachine

CeladonCity_DepartmentStore_Roof_MapEvents::
	map_events CeladonCity_DepartmentStore_Roof_ObjectEvents, CeladonCity_DepartmentStore_Roof_MapWarps, NULL, CeladonCity_DepartmentStore_Roof_MapBGEvents

@ ===== END data/maps/CeladonCity_DepartmentStore_Roof/events.inc =====
@ ===== BEGIN data/maps/CeladonCity_DepartmentStore_Elevator/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/CeladonCity_DepartmentStore_Elevator/map.json
@

	.align 2

CeladonCity_DepartmentStore_Elevator_MapWarps:
	warp_def 2, 5, 3, WARP_ID_DYNAMIC, MAP_DYNAMIC
	warp_def 2, 6, 0, WARP_ID_DYNAMIC, MAP_DYNAMIC

CeladonCity_DepartmentStore_Elevator_MapBGEvents:
	bg_sign_event 0, 2, 0, BG_EVENT_PLAYER_FACING_ANY, CeladonCity_DepartmentStore_Elevator_EventScript_FloorSelect
	bg_sign_event 4, 1, 0, BG_EVENT_PLAYER_FACING_ANY, CeladonCity_DepartmentStore_Elevator_EventScript_FloorSelect

CeladonCity_DepartmentStore_Elevator_MapEvents::
	map_events NULL, CeladonCity_DepartmentStore_Elevator_MapWarps, NULL, CeladonCity_DepartmentStore_Elevator_MapBGEvents

@ ===== END data/maps/CeladonCity_DepartmentStore_Elevator/events.inc =====
@ ===== BEGIN data/maps/CeladonCity_Condominiums_1F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/CeladonCity_Condominiums_1F/map.json
@

	.align 2

CeladonCity_Condominiums_1F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_MEOWTH, 1, 9, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, CeladonCity_Condominiums_1F_EventScript_Meowth, 0
	object_event 2, OBJ_EVENT_GFX_CLEFAIRY, 5, 13, 3, MOVEMENT_TYPE_WANDER_LEFT_AND_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, CeladonCity_Condominiums_1F_EventScript_Clefairy, 0
	object_event 3, OBJ_EVENT_GFX_NIDORAN_F, 5, 8, 3, MOVEMENT_TYPE_WANDER_AROUND, 2, 1, TRAINER_TYPE_NONE, 0, CeladonCity_Condominiums_1F_EventScript_Nidoran, 0
	object_event 4, OBJ_EVENT_GFX_OLD_WOMAN, 2, 9, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, CeladonCity_Condominiums_1F_EventScript_TeaWoman, 0

CeladonCity_Condominiums_1F_MapWarps:
	warp_def 11, 19, 0, 3, MAP_CELADON_CITY
	warp_def 12, 18, 3, 3, MAP_CELADON_CITY
	warp_def 13, 19, 0, 3, MAP_CELADON_CITY
	warp_def 4, 2, 3, 0, MAP_CELADON_CITY_CONDOMINIUMS_2F
	warp_def 12, 2, 3, 3, MAP_CELADON_CITY_CONDOMINIUMS_2F
	warp_def 2, 1, 3, 11, MAP_CELADON_CITY

CeladonCity_Condominiums_1F_MapBGEvents:
	bg_sign_event 8, 12, 0, BG_EVENT_PLAYER_FACING_ANY, CeladonCity_Condominiums_1F_EventScript_SuiteSign
	bg_sign_event 7, 12, 0, BG_EVENT_PLAYER_FACING_ANY, CeladonCity_Condominiums_1F_EventScript_SuiteSign

CeladonCity_Condominiums_1F_MapEvents::
	map_events CeladonCity_Condominiums_1F_ObjectEvents, CeladonCity_Condominiums_1F_MapWarps, NULL, CeladonCity_Condominiums_1F_MapBGEvents

@ ===== END data/maps/CeladonCity_Condominiums_1F/events.inc =====
@ ===== BEGIN data/maps/CeladonCity_Condominiums_2F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/CeladonCity_Condominiums_2F/map.json
@

	.align 2

CeladonCity_Condominiums_2F_ObjectEvents:
	object_event 1, 0, 6, 6, 0, MOVEMENT_TYPE_INVISIBLE, 1, 1, TRAINER_TYPE_NONE, 0, CeladonCity_Condominiums_2F_EventScript_PokemonJournalErika, FLAG_HIDE_FAME_CHECKER_ERIKA_JOURNALS
	object_event 2, 0, 5, 6, 0, MOVEMENT_TYPE_INVISIBLE, 1, 1, TRAINER_TYPE_NONE, 0, CeladonCity_Condominiums_2F_EventScript_PokemonJournalErika, FLAG_HIDE_FAME_CHECKER_ERIKA_JOURNALS

CeladonCity_Condominiums_2F_MapWarps:
	warp_def 4, 2, 3, 3, MAP_CELADON_CITY_CONDOMINIUMS_1F
	warp_def 2, 2, 3, 0, MAP_CELADON_CITY_CONDOMINIUMS_3F
	warp_def 11, 2, 3, 3, MAP_CELADON_CITY_CONDOMINIUMS_3F
	warp_def 12, 2, 3, 4, MAP_CELADON_CITY_CONDOMINIUMS_1F

CeladonCity_Condominiums_2F_MapBGEvents:
	bg_sign_event 8, 12, 0, BG_EVENT_PLAYER_FACING_ANY, CeladonCity_Condominiums_2F_EventScript_MeetingRoomSign
	bg_sign_event 7, 12, 0, BG_EVENT_PLAYER_FACING_ANY, CeladonCity_Condominiums_2F_EventScript_MeetingRoomSign

CeladonCity_Condominiums_2F_MapEvents::
	map_events CeladonCity_Condominiums_2F_ObjectEvents, CeladonCity_Condominiums_2F_MapWarps, NULL, CeladonCity_Condominiums_2F_MapBGEvents

@ ===== END data/maps/CeladonCity_Condominiums_2F/events.inc =====
@ ===== BEGIN data/maps/CeladonCity_Condominiums_3F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/CeladonCity_Condominiums_3F/map.json
@

	.align 2

CeladonCity_Condominiums_3F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_ROCKER, 0, 10, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NONE, 0, CeladonCity_Condominiums_3F_EventScript_Programmer, 0
	object_event 2, OBJ_EVENT_GFX_MAN, 3, 8, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, CeladonCity_Condominiums_3F_EventScript_Designer, 0
	object_event 3, OBJ_EVENT_GFX_POKE_MANIAC, 4, 10, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NONE, 0, CeladonCity_Condominiums_3F_EventScript_GraphicArtist, 0
	object_event 4, OBJ_EVENT_GFX_FAT_MAN, 0, 13, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, CeladonCity_Condominiums_3F_EventScript_Writer, 0

CeladonCity_Condominiums_3F_MapWarps:
	warp_def 2, 2, 3, 1, MAP_CELADON_CITY_CONDOMINIUMS_2F
	warp_def 4, 2, 3, 0, MAP_CELADON_CITY_CONDOMINIUMS_ROOF
	warp_def 12, 2, 3, 1, MAP_CELADON_CITY_CONDOMINIUMS_ROOF
	warp_def 11, 2, 3, 2, MAP_CELADON_CITY_CONDOMINIUMS_2F

CeladonCity_Condominiums_3F_MapBGEvents:
	bg_sign_event 8, 12, 0, BG_EVENT_PLAYER_FACING_ANY, CeladonCity_Condominiums_3F_EventScript_DevelopmentRoomSign
	bg_sign_event 1, 9, 0, BG_EVENT_PLAYER_FACING_NORTH, CeladonCity_Condominiums_3F_EventScript_Computer1
	bg_sign_event 5, 9, 0, BG_EVENT_PLAYER_FACING_NORTH, CeladonCity_Condominiums_3F_EventScript_Computer2
	bg_sign_event 1, 12, 0, BG_EVENT_PLAYER_FACING_NORTH, CeladonCity_Condominiums_3F_EventScript_Computer3
	bg_sign_event 7, 12, 0, BG_EVENT_PLAYER_FACING_ANY, CeladonCity_Condominiums_3F_EventScript_DevelopmentRoomSign
	bg_sign_event 0, 12, 0, BG_EVENT_PLAYER_FACING_NORTH, CeladonCity_Condominiums_3F_EventScript_Computer3
	bg_sign_event 0, 9, 0, BG_EVENT_PLAYER_FACING_NORTH, CeladonCity_Condominiums_3F_EventScript_Computer1
	bg_sign_event 4, 9, 0, BG_EVENT_PLAYER_FACING_NORTH, CeladonCity_Condominiums_3F_EventScript_Computer2

CeladonCity_Condominiums_3F_MapEvents::
	map_events CeladonCity_Condominiums_3F_ObjectEvents, CeladonCity_Condominiums_3F_MapWarps, NULL, CeladonCity_Condominiums_3F_MapBGEvents

@ ===== END data/maps/CeladonCity_Condominiums_3F/events.inc =====
@ ===== BEGIN data/maps/CeladonCity_Condominiums_Roof/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/CeladonCity_Condominiums_Roof/map.json
@

	.align 2

CeladonCity_Condominiums_Roof_MapWarps:
	warp_def 4, 2, 3, 1, MAP_CELADON_CITY_CONDOMINIUMS_3F
	warp_def 10, 2, 3, 2, MAP_CELADON_CITY_CONDOMINIUMS_3F
	warp_def 2, 12, 3, 1, MAP_CELADON_CITY_CONDOMINIUMS_ROOF_ROOM

CeladonCity_Condominiums_Roof_MapBGEvents:
	bg_sign_event 4, 12, 0, BG_EVENT_PLAYER_FACING_ANY, CeladonCity_Condominiums_Roof_EventScript_Sign
	bg_sign_event 3, 12, 0, BG_EVENT_PLAYER_FACING_ANY, CeladonCity_Condominiums_Roof_EventScript_Sign

CeladonCity_Condominiums_Roof_MapEvents::
	map_events NULL, CeladonCity_Condominiums_Roof_MapWarps, NULL, CeladonCity_Condominiums_Roof_MapBGEvents

@ ===== END data/maps/CeladonCity_Condominiums_Roof/events.inc =====
@ ===== BEGIN data/maps/CeladonCity_Condominiums_RoofRoom/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/CeladonCity_Condominiums_RoofRoom/map.json
@

	.align 2

CeladonCity_Condominiums_RoofRoom_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_BLACK_BELT, 3, 5, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, CeladonCity_Condominiums_RoofRoom_EventScript_BlackBelt, 0
	object_event 2, OBJ_EVENT_GFX_ITEM_BALL, 7, 3, 0, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, CeladonCity_Condominiums_RoofRoom_EventScript_EeveeBall, FLAG_HIDE_EEVEE_BALL

CeladonCity_Condominiums_RoofRoom_MapWarps:
	warp_def 3, 8, 0, 2, MAP_CELADON_CITY_CONDOMINIUMS_ROOF
	warp_def 4, 7, 3, 2, MAP_CELADON_CITY_CONDOMINIUMS_ROOF
	warp_def 5, 8, 0, 2, MAP_CELADON_CITY_CONDOMINIUMS_ROOF

CeladonCity_Condominiums_RoofRoom_MapBGEvents:
	bg_sign_event 4, 1, 0, BG_EVENT_PLAYER_FACING_ANY, CeladonCity_Condominiums_RoofRoom_EventScript_Blackboard
	bg_sign_event 5, 1, 0, BG_EVENT_PLAYER_FACING_ANY, CeladonCity_Condominiums_RoofRoom_EventScript_Blackboard
	bg_sign_event 4, 4, 0, BG_EVENT_PLAYER_FACING_ANY, CeladonCity_Condominiums_RoofRoom_EventScript_TMsPamphlet

CeladonCity_Condominiums_RoofRoom_MapEvents::
	map_events CeladonCity_Condominiums_RoofRoom_ObjectEvents, CeladonCity_Condominiums_RoofRoom_MapWarps, NULL, CeladonCity_Condominiums_RoofRoom_MapBGEvents

@ ===== END data/maps/CeladonCity_Condominiums_RoofRoom/events.inc =====
@ ===== BEGIN data/maps/CeladonCity_PokemonCenter_1F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/CeladonCity_PokemonCenter_1F/map.json
@

	.align 2

CeladonCity_PokemonCenter_1F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_NURSE, 7, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, CeladonCity_PokemonCenter_1F_EventScript_Nurse, 0
	object_event 2, OBJ_EVENT_GFX_GENTLEMAN, 4, 4, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, CeladonCity_PokemonCenter_1F_EventScript_Gentleman, 0
	object_event 3, OBJ_EVENT_GFX_COOLTRAINER_F, 10, 6, 3, MOVEMENT_TYPE_WANDER_LEFT_AND_RIGHT, 2, 1, TRAINER_TYPE_NONE, 0, CeladonCity_PokemonCenter_1F_EventScript_CooltrainerF, 0
	object_event 4, OBJ_EVENT_GFX_YOUNGSTER, 12, 5, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, CeladonCity_PokemonCenter_1F_EventScript_Youngster, 0

CeladonCity_PokemonCenter_1F_MapWarps:
	warp_def 6, 8, 3, 4, MAP_CELADON_CITY
	warp_def 7, 8, 3, 4, MAP_CELADON_CITY
	warp_def 8, 8, 3, 4, MAP_CELADON_CITY
	warp_def 1, 6, 4, 0, MAP_CELADON_CITY_POKEMON_CENTER_2F

CeladonCity_PokemonCenter_1F_MapEvents::
	map_events CeladonCity_PokemonCenter_1F_ObjectEvents, CeladonCity_PokemonCenter_1F_MapWarps, NULL, NULL

@ ===== END data/maps/CeladonCity_PokemonCenter_1F/events.inc =====
@ ===== BEGIN data/maps/CeladonCity_PokemonCenter_2F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/CeladonCity_PokemonCenter_2F/map.json
@

	.align 2

CeladonCity_PokemonCenter_2F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_CABLE_CLUB_RECEPTIONIST, 6, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 0, 0, TRAINER_TYPE_NONE, 0, Common_EventScript_UnionRoomAttendant, 0
	object_event 2, OBJ_EVENT_GFX_CABLE_CLUB_RECEPTIONIST, 2, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 0, 0, TRAINER_TYPE_NONE, 0, Common_EventScript_WirelessClubAttendant, 0
	object_event 3, OBJ_EVENT_GFX_CABLE_CLUB_RECEPTIONIST, 10, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 0, 0, TRAINER_TYPE_NONE, 0, Common_EventScript_DirectCornerAttendant, 0
	object_event 4, OBJ_EVENT_GFX_MG_DELIVERYMAN, 1, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, CableClub_EventScript_MysteryGiftMan, FLAG_HIDE_MG_DELIVERYMEN

CeladonCity_PokemonCenter_2F_MapWarps:
	warp_def 1, 6, 4, 3, MAP_CELADON_CITY_POKEMON_CENTER_1F
	warp_def 5, 1, 0, 0, MAP_UNION_ROOM
	warp_def 9, 1, 0, 0, MAP_TRADE_CENTER

CeladonCity_PokemonCenter_2F_MapEvents::
	map_events CeladonCity_PokemonCenter_2F_ObjectEvents, CeladonCity_PokemonCenter_2F_MapWarps, NULL, NULL

@ ===== END data/maps/CeladonCity_PokemonCenter_2F/events.inc =====
@ ===== BEGIN data/maps/CeladonCity_GameCorner/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/CeladonCity_GameCorner/map.json
@

	.align 2

CeladonCity_GameCorner_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_WORKER_F, 4, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, CeladonCity_GameCorner_EventScript_InfoClerk, 0
	object_event 2, OBJ_EVENT_GFX_WORKER_M, 6, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, CeladonCity_GameCorner_EventScript_CoinsClerk, 0
	object_event 3, OBJ_EVENT_GFX_BALDING_MAN, 1, 6, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NONE, 0, CeladonCity_GameCorner_EventScript_BaldingMan, 0
	object_event 4, OBJ_EVENT_GFX_WOMAN_2, 1, 8, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NONE, 0, CeladonCity_GameCorner_EventScript_Woman1, 0
	object_event 5, OBJ_EVENT_GFX_FISHER, 4, 7, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, CeladonCity_GameCorner_EventScript_Fisher, 0
	object_event 6, OBJ_EVENT_GFX_GYM_GUY, 7, 10, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NONE, 0, CeladonCity_GameCorner_EventScript_GymGuy, 0
	object_event 7, OBJ_EVENT_GFX_WOMAN_1, 7, 8, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NONE, 0, CeladonCity_GameCorner_EventScript_Woman2, 0
	object_event 8, OBJ_EVENT_GFX_OLD_MAN_2, 10, 9, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, CeladonCity_GameCorner_EventScript_OldMan, 0
	object_event 9, OBJ_EVENT_GFX_SCIENTIST, 13, 7, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NONE, 0, CeladonCity_GameCorner_EventScript_Scientist, 0
	object_event 10, OBJ_EVENT_GFX_GENTLEMAN, 16, 10, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, CeladonCity_GameCorner_EventScript_Gentleman, 0
	object_event 11, OBJ_EVENT_GFX_ROCKET_M, 11, 2, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NORMAL, 0, CeladonCity_GameCorner_EventScript_RocketGrunt, FLAG_HIDE_GAME_CORNER_ROCKET

CeladonCity_GameCorner_MapWarps:
	warp_def 9, 13, 0, 0, MAP_CELADON_CITY
	warp_def 10, 13, 0, 0, MAP_CELADON_CITY
	warp_def 11, 13, 0, 0, MAP_CELADON_CITY
	warp_def 15, 2, 3, 0, MAP_ROCKET_HIDEOUT_B1F

CeladonCity_GameCorner_MapBGEvents:
	bg_hidden_item_event 2, 4, 3, ITEM_NONE, FLAG_HIDDEN_ITEM_CELADON_CITY_GAME_CORNER_COINS, 10, FALSE
	bg_hidden_item_event 3, 8, 3, ITEM_NONE, FLAG_HIDDEN_ITEM_CELADON_CITY_GAME_CORNER_COINS_2, 10, FALSE
	bg_hidden_item_event 2, 11, 3, ITEM_NONE, FLAG_HIDDEN_ITEM_CELADON_CITY_GAME_CORNER_COINS_3, 20, FALSE
	bg_hidden_item_event 6, 12, 3, ITEM_NONE, FLAG_HIDDEN_ITEM_CELADON_CITY_GAME_CORNER_COINS_4, 10, FALSE
	bg_hidden_item_event 9, 9, 3, ITEM_NONE, FLAG_HIDDEN_ITEM_CELADON_CITY_GAME_CORNER_COINS_5, 10, FALSE
	bg_hidden_item_event 8, 5, 3, ITEM_NONE, FLAG_HIDDEN_ITEM_CELADON_CITY_GAME_CORNER_COINS_6, 20, FALSE
	bg_hidden_item_event 10, 4, 3, ITEM_NONE, FLAG_HIDDEN_ITEM_CELADON_CITY_GAME_CORNER_COINS_7, 10, FALSE
	bg_hidden_item_event 13, 3, 3, ITEM_NONE, FLAG_HIDDEN_ITEM_CELADON_CITY_GAME_CORNER_COINS_8, 10, FALSE
	bg_hidden_item_event 15, 5, 3, ITEM_NONE, FLAG_HIDDEN_ITEM_CELADON_CITY_GAME_CORNER_COINS_9, 10, FALSE
	bg_hidden_item_event 17, 5, 3, ITEM_NONE, FLAG_HIDDEN_ITEM_CELADON_CITY_GAME_CORNER_COINS_10, 40, FALSE
	bg_hidden_item_event 15, 13, 3, ITEM_NONE, FLAG_HIDDEN_ITEM_CELADON_CITY_GAME_CORNER_COINS_11, 100, FALSE
	bg_hidden_item_event 12, 12, 3, ITEM_NONE, FLAG_HIDDEN_ITEM_CELADON_CITY_GAME_CORNER_COINS_12, 10, FALSE
	bg_sign_event 0, 7, 0, BG_EVENT_PLAYER_FACING_WEST, CeladonCity_GameCorner_EventScript_SlotMachine0
	bg_sign_event 0, 9, 0, BG_EVENT_PLAYER_FACING_WEST, CeladonCity_GameCorner_EventScript_SlotMachine1
	bg_sign_event 0, 10, 0, BG_EVENT_PLAYER_FACING_WEST, CeladonCity_GameCorner_EventScript_SlotMachine2
	bg_sign_event 5, 6, 0, BG_EVENT_PLAYER_FACING_EAST, CeladonCity_GameCorner_EventScript_SlotMachine3
	bg_sign_event 5, 8, 0, BG_EVENT_PLAYER_FACING_EAST, CeladonCity_GameCorner_EventScript_UnusableSlotMachine1
	bg_sign_event 5, 9, 0, BG_EVENT_PLAYER_FACING_EAST, CeladonCity_GameCorner_EventScript_SlotMachine5
	bg_sign_event 5, 10, 0, BG_EVENT_PLAYER_FACING_EAST, CeladonCity_GameCorner_EventScript_SlotMachine6
	bg_sign_event 6, 6, 0, BG_EVENT_PLAYER_FACING_WEST, CeladonCity_GameCorner_EventScript_SlotMachine7
	bg_sign_event 6, 7, 0, BG_EVENT_PLAYER_FACING_WEST, CeladonCity_GameCorner_EventScript_SlotMachine8
	bg_sign_event 6, 9, 0, BG_EVENT_PLAYER_FACING_WEST, CeladonCity_GameCorner_EventScript_SlotMachine9
	bg_sign_event 11, 6, 0, BG_EVENT_PLAYER_FACING_EAST, CeladonCity_GameCorner_EventScript_SlotMachine10
	bg_sign_event 11, 7, 0, BG_EVENT_PLAYER_FACING_EAST, CeladonCity_GameCorner_EventScript_SlotMachine11
	bg_sign_event 11, 8, 0, BG_EVENT_PLAYER_FACING_EAST, CeladonCity_GameCorner_EventScript_SlotMachine12
	bg_sign_event 11, 10, 0, BG_EVENT_PLAYER_FACING_EAST, CeladonCity_GameCorner_EventScript_SlotMachine13
	bg_sign_event 12, 6, 0, BG_EVENT_PLAYER_FACING_WEST, CeladonCity_GameCorner_EventScript_SlotMachine14
	bg_sign_event 12, 8, 0, BG_EVENT_PLAYER_FACING_WEST, CeladonCity_GameCorner_EventScript_UnusableSlotMachine2
	bg_sign_event 12, 9, 0, BG_EVENT_PLAYER_FACING_WEST, CeladonCity_GameCorner_EventScript_SlotMachine16
	bg_sign_event 12, 10, 0, BG_EVENT_PLAYER_FACING_WEST, CeladonCity_GameCorner_EventScript_SlotMachine17
	bg_sign_event 17, 6, 0, BG_EVENT_PLAYER_FACING_EAST, CeladonCity_GameCorner_EventScript_UnusableSlotMachine3
	bg_sign_event 17, 7, 0, BG_EVENT_PLAYER_FACING_EAST, CeladonCity_GameCorner_EventScript_SlotMachine19
	bg_sign_event 17, 8, 0, BG_EVENT_PLAYER_FACING_EAST, CeladonCity_GameCorner_EventScript_SlotMachine20
	bg_sign_event 17, 9, 0, BG_EVENT_PLAYER_FACING_EAST, CeladonCity_GameCorner_EventScript_SlotMachine21
	bg_sign_event 11, 1, 0, BG_EVENT_PLAYER_FACING_ANY, CeladonCity_GameCorner_EventScript_Poster
	bg_sign_event 17, 13, 0, BG_EVENT_PLAYER_FACING_EAST, CeladonCity_GameCorner_EventScript_PhotoPrinter

CeladonCity_GameCorner_MapEvents::
	map_events CeladonCity_GameCorner_ObjectEvents, CeladonCity_GameCorner_MapWarps, NULL, CeladonCity_GameCorner_MapBGEvents

@ ===== END data/maps/CeladonCity_GameCorner/events.inc =====
@ ===== BEGIN data/maps/CeladonCity_GameCorner_PrizeRoom/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/CeladonCity_GameCorner_PrizeRoom/map.json
@

	.align 2

CeladonCity_GameCorner_PrizeRoom_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_BALDING_MAN, 2, 6, 3, MOVEMENT_TYPE_WANDER_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, CeladonCity_GameCorner_PrizeRoom_EventScript_BaldingMan, 0
	object_event 2, OBJ_EVENT_GFX_OLD_MAN_2, 6, 7, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, CeladonCity_GameCorner_PrizeRoom_EventScript_OldMan, 0
	object_event 3, OBJ_EVENT_GFX_WORKER_M, 4, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, CeladonCity_GameCorner_PrizeRoom_EventScript_PrizeClerkMons, 0
	object_event 4, OBJ_EVENT_GFX_WORKER_M, 6, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, CeladonCity_GameCorner_PrizeRoom_EventScript_PrizeClerkTMs, 0
	object_event 5, OBJ_EVENT_GFX_WORKER_M, 2, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, CeladonCity_GameCorner_PrizeRoom_EventScript_PrizeClerkItems, 0

CeladonCity_GameCorner_PrizeRoom_MapWarps:
	warp_def 3, 9, 0, 5, MAP_CELADON_CITY
	warp_def 4, 8, 3, 5, MAP_CELADON_CITY
	warp_def 5, 9, 0, 5, MAP_CELADON_CITY

CeladonCity_GameCorner_PrizeRoom_MapEvents::
	map_events CeladonCity_GameCorner_PrizeRoom_ObjectEvents, CeladonCity_GameCorner_PrizeRoom_MapWarps, NULL, NULL

@ ===== END data/maps/CeladonCity_GameCorner_PrizeRoom/events.inc =====
@ ===== BEGIN data/maps/CeladonCity_Gym/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/CeladonCity_Gym/map.json
@

	.align 2

CeladonCity_Gym_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_LASS, 3, 11, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 3, CeladonCity_Gym_EventScript_Kay, 0
	object_event 2, OBJ_EVENT_GFX_BEAUTY, 9, 10, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NORMAL, 3, CeladonCity_Gym_EventScript_Bridget, 0
	object_event 3, OBJ_EVENT_GFX_PICNICKER, 10, 7, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 2, CeladonCity_Gym_EventScript_Tina, 0
	object_event 4, OBJ_EVENT_GFX_BEAUTY, 2, 6, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 4, CeladonCity_Gym_EventScript_Tamia, 0
	object_event 5, OBJ_EVENT_GFX_BEAUTY, 5, 4, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 3, CeladonCity_Gym_EventScript_Lori, 0
	object_event 6, OBJ_EVENT_GFX_LASS, 7, 4, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 2, CeladonCity_Gym_EventScript_Lisa, 0
	object_event 7, OBJ_EVENT_GFX_ERIKA, 6, 4, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, CeladonCity_Gym_EventScript_Erika, 0
	object_event 8, OBJ_EVENT_GFX_COOLTRAINER_F, 8, 7, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NORMAL, 2, CeladonCity_Gym_EventScript_Mary, 0
	object_event 9, OBJ_EVENT_GFX_CUT_TREE, 6, 8, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_CutTree, FLAG_TEMP_12
	object_event 10, OBJ_EVENT_GFX_CUT_TREE, 3, 5, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_CutTree, FLAG_TEMP_13
	object_event 11, OBJ_EVENT_GFX_CUT_TREE, 9, 6, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, EventScript_CutTree, FLAG_TEMP_14

CeladonCity_Gym_MapWarps:
	warp_def 5, 18, 3, 6, MAP_CELADON_CITY
	warp_def 6, 18, 3, 6, MAP_CELADON_CITY
	warp_def 7, 18, 3, 6, MAP_CELADON_CITY

CeladonCity_Gym_MapBGEvents:
	bg_sign_event 4, 16, 0, BG_EVENT_PLAYER_FACING_ANY, CeladonCity_Gym_EventScript_GymStatue
	bg_sign_event 8, 16, 0, BG_EVENT_PLAYER_FACING_ANY, CeladonCity_Gym_EventScript_GymStatue

CeladonCity_Gym_MapEvents::
	map_events CeladonCity_Gym_ObjectEvents, CeladonCity_Gym_MapWarps, NULL, CeladonCity_Gym_MapBGEvents

@ ===== END data/maps/CeladonCity_Gym/events.inc =====
@ ===== BEGIN data/maps/CeladonCity_Restaurant/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/CeladonCity_Restaurant/map.json
@

	.align 2

CeladonCity_Restaurant_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_CHEF, 12, 7, 3, MOVEMENT_TYPE_WANDER_LEFT_AND_RIGHT, 2, 1, TRAINER_TYPE_NONE, 0, CeladonCity_Restaurant_EventScript_Chef, 0
	object_event 2, OBJ_EVENT_GFX_WOMAN_2, 11, 4, 3, MOVEMENT_TYPE_WANDER_UP_AND_DOWN, 1, 2, TRAINER_TYPE_NONE, 0, CeladonCity_Restaurant_EventScript_Woman, 0
	object_event 3, OBJ_EVENT_GFX_FAT_MAN, 9, 4, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, CeladonCity_Restaurant_EventScript_FatMan, 0
	object_event 4, OBJ_EVENT_GFX_BALDING_MAN, 1, 2, 0, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, CeladonCity_Restaurant_EventScript_CoinCaseMan, 0
	object_event 5, OBJ_EVENT_GFX_WORKER_M, 3, 7, 0, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NONE, 0, CeladonCity_Restaurant_EventScript_WorkerM, 0

CeladonCity_Restaurant_MapWarps:
	warp_def 5, 9, 0, 7, MAP_CELADON_CITY
	warp_def 6, 9, 0, 7, MAP_CELADON_CITY
	warp_def 7, 9, 0, 7, MAP_CELADON_CITY

CeladonCity_Restaurant_MapEvents::
	map_events CeladonCity_Restaurant_ObjectEvents, CeladonCity_Restaurant_MapWarps, NULL, NULL

@ ===== END data/maps/CeladonCity_Restaurant/events.inc =====
@ ===== BEGIN data/maps/CeladonCity_House1/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/CeladonCity_House1/map.json
@

	.align 2

CeladonCity_House1_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_OLD_MAN_2, 5, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, CeladonCity_House1_EventScript_RocketChief, 0
	object_event 2, OBJ_EVENT_GFX_ROCKET_M, 2, 4, 3, MOVEMENT_TYPE_WANDER_UP_AND_DOWN, 1, 5, TRAINER_TYPE_NONE, 0, CeladonCity_House1_EventScript_Rocket1, 0
	object_event 3, OBJ_EVENT_GFX_ROCKET_M, 8, 4, 3, MOVEMENT_TYPE_WANDER_UP_AND_DOWN, 1, 5, TRAINER_TYPE_NONE, 0, CeladonCity_House1_EventScript_Rocket2, 0

CeladonCity_House1_MapWarps:
	warp_def 3, 7, 3, 8, MAP_CELADON_CITY
	warp_def 4, 7, 3, 8, MAP_CELADON_CITY
	warp_def 5, 7, 3, 8, MAP_CELADON_CITY

CeladonCity_House1_MapEvents::
	map_events CeladonCity_House1_ObjectEvents, CeladonCity_House1_MapWarps, NULL, NULL

@ ===== END data/maps/CeladonCity_House1/events.inc =====
@ ===== BEGIN data/maps/CeladonCity_Hotel/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/CeladonCity_Hotel/map.json
@

	.align 2

CeladonCity_Hotel_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_OLD_WOMAN, 5, 4, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, CeladonCity_Hotel_EventScript_Receptionist, 0
	object_event 2, OBJ_EVENT_GFX_BEAUTY, 3, 6, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, CeladonCity_Hotel_EventScript_Beauty, 0
	object_event 3, OBJ_EVENT_GFX_MAN, 9, 7, 3, MOVEMENT_TYPE_WANDER_LEFT_AND_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, CeladonCity_Hotel_EventScript_BeautyBoyfriend, 0
	object_event 4, OBJ_EVENT_GFX_LITTLE_BOY, 2, 6, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, CeladonCity_Hotel_EventScript_BeautyBrother, 0

CeladonCity_Hotel_MapWarps:
	warp_def 3, 10, 0, 9, MAP_CELADON_CITY
	warp_def 4, 9, 0, 9, MAP_CELADON_CITY
	warp_def 5, 10, 0, 9, MAP_CELADON_CITY

CeladonCity_Hotel_MapEvents::
	map_events CeladonCity_Hotel_ObjectEvents, CeladonCity_Hotel_MapWarps, NULL, NULL

@ ===== END data/maps/CeladonCity_Hotel/events.inc =====
@ ===== BEGIN data/maps/FuchsiaCity_SafariZone_Entrance/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FuchsiaCity_SafariZone_Entrance/map.json
@

	.align 2

FuchsiaCity_SafariZone_Entrance_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_WORKER_M, 7, 3, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NONE, 0, 0x0, 0
	object_event 2, OBJ_EVENT_GFX_WORKER_M, 1, 6, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, FuchsiaCity_SafariZone_Entrance_EventScript_InfoAttendant, 0

FuchsiaCity_SafariZone_Entrance_MapWarps:
	warp_def 4, 1, 3, 1, MAP_SAFARI_ZONE_CENTER
	warp_def 5, 7, 3, 0, MAP_FUCHSIA_CITY
	warp_def 4, 7, 3, 0, MAP_FUCHSIA_CITY
	warp_def 3, 7, 3, 0, MAP_FUCHSIA_CITY

FuchsiaCity_SafariZone_Entrance_MapCoordEvents:
	coord_event 4, 3, 3, VAR_TEMP_1, 0, FuchsiaCity_SafariZone_Entrance_EventScript_EntryTriggerMid
	coord_event 5, 3, 3, VAR_TEMP_1, 0, FuchsiaCity_SafariZone_Entrance_EventScript_EntryTriggerRight
	coord_event 3, 3, 3, VAR_TEMP_1, 0, FuchsiaCity_SafariZone_Entrance_EventScript_EntryTriggerLeft

FuchsiaCity_SafariZone_Entrance_MapEvents::
	map_events FuchsiaCity_SafariZone_Entrance_ObjectEvents, FuchsiaCity_SafariZone_Entrance_MapWarps, FuchsiaCity_SafariZone_Entrance_MapCoordEvents, NULL

@ ===== END data/maps/FuchsiaCity_SafariZone_Entrance/events.inc =====
@ ===== BEGIN data/maps/FuchsiaCity_Mart/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FuchsiaCity_Mart/map.json
@

	.align 2

FuchsiaCity_Mart_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_CLERK, 2, 3, 0, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, FuchsiaCity_Mart_EventScript_Clerk, 0
	object_event 2, OBJ_EVENT_GFX_GENTLEMAN, 6, 3, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, FuchsiaCity_Mart_EventScript_Gentleman, 0
	object_event 3, OBJ_EVENT_GFX_COOLTRAINER_F, 9, 5, 3, MOVEMENT_TYPE_WANDER_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, FuchsiaCity_Mart_EventScript_CooltrainerF, 0

FuchsiaCity_Mart_MapWarps:
	warp_def 3, 7, 3, 2, MAP_FUCHSIA_CITY
	warp_def 4, 7, 3, 2, MAP_FUCHSIA_CITY
	warp_def 5, 7, 3, 2, MAP_FUCHSIA_CITY

FuchsiaCity_Mart_MapEvents::
	map_events FuchsiaCity_Mart_ObjectEvents, FuchsiaCity_Mart_MapWarps, NULL, NULL

@ ===== END data/maps/FuchsiaCity_Mart/events.inc =====
@ ===== BEGIN data/maps/FuchsiaCity_SafariZone_Office/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FuchsiaCity_SafariZone_Office/map.json
@

	.align 2

FuchsiaCity_SafariZone_Office_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_WORKER_M, 2, 2, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NONE, 0, FuchsiaCity_SafariZone_Office_EventScript_Worker2, 0
	object_event 2, OBJ_EVENT_GFX_WORKER_M, 12, 3, 3, MOVEMENT_TYPE_WANDER_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, FuchsiaCity_SafariZone_Office_EventScript_Worker3, 0
	object_event 3, OBJ_EVENT_GFX_WORKER_M, 6, 4, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, FuchsiaCity_SafariZone_Office_EventScript_Worker1, 0
	object_event 4, OBJ_EVENT_GFX_WORKER_M, 10, 8, 3, MOVEMENT_TYPE_FACE_LEFT, 2, 1, TRAINER_TYPE_NONE, 0, FuchsiaCity_SafariZone_Office_EventScript_Worker4, 0

FuchsiaCity_SafariZone_Office_MapWarps:
	warp_def 5, 9, 0, 3, MAP_FUCHSIA_CITY
	warp_def 6, 9, 0, 3, MAP_FUCHSIA_CITY
	warp_def 7, 9, 3, 3, MAP_FUCHSIA_CITY

FuchsiaCity_SafariZone_Office_MapEvents::
	map_events FuchsiaCity_SafariZone_Office_ObjectEvents, FuchsiaCity_SafariZone_Office_MapWarps, NULL, NULL

@ ===== END data/maps/FuchsiaCity_SafariZone_Office/events.inc =====
@ ===== BEGIN data/maps/FuchsiaCity_Gym/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FuchsiaCity_Gym/map.json
@

	.align 2

FuchsiaCity_Gym_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_ROCKER, 12, 16, 3, MOVEMENT_TYPE_FACE_DOWN_AND_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 4, FuchsiaCity_Gym_EventScript_Kayden, 0
	object_event 2, OBJ_EVENT_GFX_ROCKER, 2, 9, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NORMAL, 1, FuchsiaCity_Gym_EventScript_Shawn, 0
	object_event 3, OBJ_EVENT_GFX_ROCKER, 11, 11, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 3, FuchsiaCity_Gym_EventScript_Kirk, 0
	object_event 4, OBJ_EVENT_GFX_MAN, 13, 4, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NORMAL, 2, FuchsiaCity_Gym_EventScript_Edgar, 0
	object_event 5, OBJ_EVENT_GFX_MAN, 4, 6, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NORMAL, 2, FuchsiaCity_Gym_EventScript_Phil, 0
	object_event 6, OBJ_EVENT_GFX_ROCKER, 2, 16, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 4, FuchsiaCity_Gym_EventScript_Nate, 0
	object_event 7, OBJ_EVENT_GFX_KOGA, 7, 13, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, FuchsiaCity_Gym_EventScript_Koga, 0
	object_event 8, OBJ_EVENT_GFX_GYM_GUY, 11, 19, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, FuchsiaCity_Gym_EventScript_GymGuy, 0

FuchsiaCity_Gym_MapWarps:
	warp_def 6, 21, 3, 4, MAP_FUCHSIA_CITY
	warp_def 7, 21, 3, 4, MAP_FUCHSIA_CITY
	warp_def 8, 21, 3, 4, MAP_FUCHSIA_CITY

FuchsiaCity_Gym_MapBGEvents:
	bg_sign_event 4, 19, 0, BG_EVENT_PLAYER_FACING_ANY, FuchsiaCity_Gym_EventScript_GymStatue
	bg_sign_event 10, 19, 0, BG_EVENT_PLAYER_FACING_ANY, FuchsiaCity_Gym_EventScript_GymStatue

FuchsiaCity_Gym_MapEvents::
	map_events FuchsiaCity_Gym_ObjectEvents, FuchsiaCity_Gym_MapWarps, NULL, FuchsiaCity_Gym_MapBGEvents

@ ===== END data/maps/FuchsiaCity_Gym/events.inc =====
@ ===== BEGIN data/maps/FuchsiaCity_House1/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FuchsiaCity_House1/map.json
@

	.align 2

FuchsiaCity_House1_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_OLD_MAN_1, 7, 4, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NONE, 0, FuchsiaCity_House1_EventScript_OldMan, 0
	object_event 2, OBJ_EVENT_GFX_WOMAN_2, 1, 2, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NONE, 0, FuchsiaCity_House1_EventScript_Woman, 0
	object_event 3, OBJ_EVENT_GFX_LITTLE_BOY, 2, 5, 3, MOVEMENT_TYPE_WANDER_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, FuchsiaCity_House1_EventScript_LittleBoy, 0

FuchsiaCity_House1_MapWarps:
	warp_def 3, 7, 3, 5, MAP_FUCHSIA_CITY
	warp_def 4, 7, 3, 5, MAP_FUCHSIA_CITY
	warp_def 5, 7, 3, 5, MAP_FUCHSIA_CITY

FuchsiaCity_House1_MapEvents::
	map_events FuchsiaCity_House1_ObjectEvents, FuchsiaCity_House1_MapWarps, NULL, NULL

@ ===== END data/maps/FuchsiaCity_House1/events.inc =====
@ ===== BEGIN data/maps/FuchsiaCity_PokemonCenter_1F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FuchsiaCity_PokemonCenter_1F/map.json
@

	.align 2

FuchsiaCity_PokemonCenter_1F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_NURSE, 7, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, FuchsiaCity_PokemonCenter_1F_EventScript_Nurse, 0
	object_event 2, OBJ_EVENT_GFX_MAN, 12, 5, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, FuchsiaCity_PokemonCenter_1F_EventScript_Man, 0
	object_event 3, OBJ_EVENT_GFX_COOLTRAINER_F, 13, 3, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NONE, 0, FuchsiaCity_PokemonCenter_1F_EventScript_CooltrainerF, 0
	object_event 4, OBJ_EVENT_GFX_YOUNGSTER, 4, 8, 3, MOVEMENT_TYPE_WANDER_LEFT_AND_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, FuchsiaCity_PokemonCenter_1F_EventScript_Youngster, 0

FuchsiaCity_PokemonCenter_1F_MapWarps:
	warp_def 6, 8, 3, 6, MAP_FUCHSIA_CITY
	warp_def 7, 8, 3, 6, MAP_FUCHSIA_CITY
	warp_def 8, 8, 3, 6, MAP_FUCHSIA_CITY
	warp_def 1, 6, 4, 0, MAP_FUCHSIA_CITY_POKEMON_CENTER_2F

FuchsiaCity_PokemonCenter_1F_MapEvents::
	map_events FuchsiaCity_PokemonCenter_1F_ObjectEvents, FuchsiaCity_PokemonCenter_1F_MapWarps, NULL, NULL

@ ===== END data/maps/FuchsiaCity_PokemonCenter_1F/events.inc =====
@ ===== BEGIN data/maps/FuchsiaCity_PokemonCenter_2F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FuchsiaCity_PokemonCenter_2F/map.json
@

	.align 2

FuchsiaCity_PokemonCenter_2F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_CABLE_CLUB_RECEPTIONIST, 6, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 0, 0, TRAINER_TYPE_NONE, 0, Common_EventScript_UnionRoomAttendant, 0
	object_event 2, OBJ_EVENT_GFX_CABLE_CLUB_RECEPTIONIST, 2, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 0, 0, TRAINER_TYPE_NONE, 0, Common_EventScript_WirelessClubAttendant, 0
	object_event 3, OBJ_EVENT_GFX_CABLE_CLUB_RECEPTIONIST, 10, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 0, 0, TRAINER_TYPE_NONE, 0, Common_EventScript_DirectCornerAttendant, 0
	object_event 4, OBJ_EVENT_GFX_MG_DELIVERYMAN, 1, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, CableClub_EventScript_MysteryGiftMan, FLAG_HIDE_MG_DELIVERYMEN

FuchsiaCity_PokemonCenter_2F_MapWarps:
	warp_def 1, 6, 4, 3, MAP_FUCHSIA_CITY_POKEMON_CENTER_1F
	warp_def 5, 1, 0, 0, MAP_UNION_ROOM
	warp_def 9, 1, 0, 0, MAP_TRADE_CENTER

FuchsiaCity_PokemonCenter_2F_MapEvents::
	map_events FuchsiaCity_PokemonCenter_2F_ObjectEvents, FuchsiaCity_PokemonCenter_2F_MapWarps, NULL, NULL

@ ===== END data/maps/FuchsiaCity_PokemonCenter_2F/events.inc =====
@ ===== BEGIN data/maps/FuchsiaCity_WardensHouse/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FuchsiaCity_WardensHouse/map.json
@

	.align 2

FuchsiaCity_WardensHouse_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_OLD_MAN_2, 3, 5, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, FuchsiaCity_WardensHouse_EventScript_Warden, 0
	object_event 2, OBJ_EVENT_GFX_PUSHABLE_BOULDER, 11, 6, 3, MOVEMENT_TYPE_FACE_DOWN, 0, 0, TRAINER_TYPE_NONE, 0, EventScript_StrengthBoulder, 0
	object_event 3, OBJ_EVENT_GFX_ITEM_BALL, 11, 5, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, FuchsiaCity_WardensHouse_EventScript_ItemRareCandy, FLAG_HIDE_FUCHSIA_CITY_WARDENS_HOUSE_RARE_CANDY
	object_event 4, 0, 4, 1, 0, MOVEMENT_TYPE_INVISIBLE, 1, 1, TRAINER_TYPE_NONE, 0, FuchsiaCity_WardensHouse_EventScript_PokemonJournalKoga, FLAG_HIDE_FAME_CHECKER_KOGA_JOURNAL

FuchsiaCity_WardensHouse_MapWarps:
	warp_def 5, 10, 0, 1, MAP_FUCHSIA_CITY
	warp_def 6, 9, 3, 1, MAP_FUCHSIA_CITY
	warp_def 7, 10, 0, 1, MAP_FUCHSIA_CITY

FuchsiaCity_WardensHouse_MapBGEvents:
	bg_sign_event 7, 4, 0, BG_EVENT_PLAYER_FACING_ANY, FuchsiaCity_WardensHouse_EventScript_DisplaySign2
	bg_sign_event 4, 4, 0, BG_EVENT_PLAYER_FACING_ANY, FuchsiaCity_WardensHouse_EventScript_DisplaySign1
	bg_sign_event 5, 4, 0, BG_EVENT_PLAYER_FACING_ANY, FuchsiaCity_WardensHouse_EventScript_DisplaySign1
	bg_sign_event 6, 4, 0, BG_EVENT_PLAYER_FACING_ANY, FuchsiaCity_WardensHouse_EventScript_DisplaySign2

FuchsiaCity_WardensHouse_MapEvents::
	map_events FuchsiaCity_WardensHouse_ObjectEvents, FuchsiaCity_WardensHouse_MapWarps, NULL, FuchsiaCity_WardensHouse_MapBGEvents

@ ===== END data/maps/FuchsiaCity_WardensHouse/events.inc =====
@ ===== BEGIN data/maps/FuchsiaCity_House2/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FuchsiaCity_House2/map.json
@

	.align 2

FuchsiaCity_House2_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_FISHER, 6, 5, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, FuchsiaCity_House2_EventScript_FishingGurusBrother, 0

FuchsiaCity_House2_MapWarps:
	warp_def 2, 9, 0, 7, MAP_FUCHSIA_CITY
	warp_def 3, 8, 3, 7, MAP_FUCHSIA_CITY
	warp_def 4, 9, 0, 7, MAP_FUCHSIA_CITY
	warp_def 3, 1, 3, 8, MAP_FUCHSIA_CITY

FuchsiaCity_House2_MapEvents::
	map_events FuchsiaCity_House2_ObjectEvents, FuchsiaCity_House2_MapWarps, NULL, NULL

@ ===== END data/maps/FuchsiaCity_House2/events.inc =====
@ ===== BEGIN data/maps/FuchsiaCity_House3/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FuchsiaCity_House3/map.json
@

	.align 2

FuchsiaCity_House3_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_BALDING_MAN, 4, 4, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, FuchsiaCity_House3_EventScript_MoveDeleter, 0

FuchsiaCity_House3_MapWarps:
	warp_def 4, 7, 3, 10, MAP_FUCHSIA_CITY

FuchsiaCity_House3_MapEvents::
	map_events FuchsiaCity_House3_ObjectEvents, FuchsiaCity_House3_MapWarps, NULL, NULL

@ ===== END data/maps/FuchsiaCity_House3/events.inc =====
@ ===== BEGIN data/maps/CinnabarIsland_Gym/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/CinnabarIsland_Gym/map.json
@

	.align 2

CinnabarIsland_Gym_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_POKE_MANIAC, 25, 11, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 0, CinnabarIsland_Gym_EventScript_Quinn, 0
	object_event 2, OBJ_EVENT_GFX_SCIENTIST, 25, 4, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 0, CinnabarIsland_Gym_EventScript_Erik, 0
	object_event 3, OBJ_EVENT_GFX_SCIENTIST, 17, 5, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 0, CinnabarIsland_Gym_EventScript_Avery, 0
	object_event 4, OBJ_EVENT_GFX_POKE_MANIAC, 16, 11, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 0, CinnabarIsland_Gym_EventScript_Ramon, 0
	object_event 5, OBJ_EVENT_GFX_SCIENTIST, 16, 18, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 0, CinnabarIsland_Gym_EventScript_Derek, 0
	object_event 6, OBJ_EVENT_GFX_POKE_MANIAC, 4, 19, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 0, CinnabarIsland_Gym_EventScript_Dusty, 0
	object_event 7, OBJ_EVENT_GFX_SCIENTIST, 4, 11, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 0, CinnabarIsland_Gym_EventScript_Zac, 0
	object_event 8, OBJ_EVENT_GFX_BLAINE, 5, 4, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, CinnabarIsland_Gym_EventScript_Blaine, 0
	object_event 9, OBJ_EVENT_GFX_GYM_GUY, 24, 20, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, CinnabarIsland_Gym_EventScript_GymGuy, 0

CinnabarIsland_Gym_MapWarps:
	warp_def 24, 23, 3, 1, MAP_CINNABAR_ISLAND
	warp_def 25, 23, 3, 1, MAP_CINNABAR_ISLAND
	warp_def 26, 23, 3, 1, MAP_CINNABAR_ISLAND

CinnabarIsland_Gym_MapBGEvents:
	bg_sign_event 23, 20, 0, BG_EVENT_PLAYER_FACING_ANY, CinnabarIsland_Gym_EventScript_GymStatue
	bg_sign_event 27, 20, 0, BG_EVENT_PLAYER_FACING_ANY, CinnabarIsland_Gym_EventScript_GymStatue
	bg_sign_event 22, 10, 0, BG_EVENT_PLAYER_FACING_NORTH, CinnabarIsland_Gym_EventScript_Quiz1Left
	bg_sign_event 23, 10, 0, BG_EVENT_PLAYER_FACING_NORTH, CinnabarIsland_Gym_EventScript_Quiz1Right
	bg_sign_event 15, 2, 0, BG_EVENT_PLAYER_FACING_NORTH, CinnabarIsland_Gym_EventScript_Quiz2Left
	bg_sign_event 16, 2, 0, BG_EVENT_PLAYER_FACING_NORTH, CinnabarIsland_Gym_EventScript_Quiz2Right
	bg_sign_event 13, 10, 0, BG_EVENT_PLAYER_FACING_NORTH, CinnabarIsland_Gym_EventScript_Quiz3Left
	bg_sign_event 14, 10, 0, BG_EVENT_PLAYER_FACING_NORTH, CinnabarIsland_Gym_EventScript_Quiz3Right
	bg_sign_event 13, 17, 0, BG_EVENT_PLAYER_FACING_NORTH, CinnabarIsland_Gym_EventScript_Quiz4Left
	bg_sign_event 14, 17, 0, BG_EVENT_PLAYER_FACING_NORTH, CinnabarIsland_Gym_EventScript_Quiz4Right
	bg_sign_event 1, 18, 0, BG_EVENT_PLAYER_FACING_NORTH, CinnabarIsland_Gym_EventScript_Quiz5Left
	bg_sign_event 2, 18, 0, BG_EVENT_PLAYER_FACING_NORTH, CinnabarIsland_Gym_EventScript_Quiz5Right
	bg_sign_event 1, 10, 0, BG_EVENT_PLAYER_FACING_NORTH, CinnabarIsland_Gym_EventScript_Quiz6Left
	bg_sign_event 2, 10, 0, BG_EVENT_PLAYER_FACING_NORTH, CinnabarIsland_Gym_EventScript_Quiz6Right
	bg_sign_event 3, 1, 0, BG_EVENT_PLAYER_FACING_NORTH, CinnabarIsland_Gym_EventScript_BlaineFujiPhoto

CinnabarIsland_Gym_MapEvents::
	map_events CinnabarIsland_Gym_ObjectEvents, CinnabarIsland_Gym_MapWarps, NULL, CinnabarIsland_Gym_MapBGEvents

@ ===== END data/maps/CinnabarIsland_Gym/events.inc =====
@ ===== BEGIN data/maps/CinnabarIsland_PokemonLab_Entrance/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/CinnabarIsland_PokemonLab_Entrance/map.json
@

	.align 2

CinnabarIsland_PokemonLab_Entrance_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_SCIENTIST, 2, 4, 3, MOVEMENT_TYPE_WANDER_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, CinnabarIsland_PokemonLab_Entrance_EventScript_Scientist, 0

CinnabarIsland_PokemonLab_Entrance_MapWarps:
	warp_def 3, 9, 3, 2, MAP_CINNABAR_ISLAND
	warp_def 4, 9, 3, 2, MAP_CINNABAR_ISLAND
	warp_def 5, 9, 3, 2, MAP_CINNABAR_ISLAND
	warp_def 13, 5, 0, 0, MAP_CINNABAR_ISLAND_POKEMON_LAB_LOUNGE
	warp_def 19, 5, 0, 0, MAP_CINNABAR_ISLAND_POKEMON_LAB_RESEARCH_ROOM
	warp_def 25, 5, 0, 0, MAP_CINNABAR_ISLAND_POKEMON_LAB_EXPERIMENT_ROOM

CinnabarIsland_PokemonLab_Entrance_MapBGEvents:
	bg_sign_event 4, 1, 0, BG_EVENT_PLAYER_FACING_ANY, CinnabarIsland_PokemonLab_Entrance_EventScript_DrFujiPhoto
	bg_sign_event 12, 5, 0, BG_EVENT_PLAYER_FACING_ANY, CinnabarIsland_PokemonLab_Entrance_EventScript_MeetingRoomSign
	bg_sign_event 18, 5, 0, BG_EVENT_PLAYER_FACING_ANY, CinnabarIsland_PokemonLab_Entrance_EventScript_RAndDRoomSign
	bg_sign_event 24, 5, 0, BG_EVENT_PLAYER_FACING_ANY, CinnabarIsland_PokemonLab_Entrance_EventScript_TestingRoomSign

CinnabarIsland_PokemonLab_Entrance_MapEvents::
	map_events CinnabarIsland_PokemonLab_Entrance_ObjectEvents, CinnabarIsland_PokemonLab_Entrance_MapWarps, NULL, CinnabarIsland_PokemonLab_Entrance_MapBGEvents

@ ===== END data/maps/CinnabarIsland_PokemonLab_Entrance/events.inc =====
@ ===== BEGIN data/maps/CinnabarIsland_PokemonLab_Lounge/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/CinnabarIsland_PokemonLab_Lounge/map.json
@

	.align 2

CinnabarIsland_PokemonLab_Lounge_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_SCIENTIST, 5, 3, 3, MOVEMENT_TYPE_WANDER_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, CinnabarIsland_PokemonLab_Lounge_EventScript_Scientist, 0
	object_event 2, OBJ_EVENT_GFX_OLD_MAN_2, 4, 6, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, CinnabarIsland_PokemonLab_Lounge_EventScript_Clifton, 0
	object_event 3, OBJ_EVENT_GFX_WOMAN_2, 10, 5, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, CinnabarIsland_PokemonLab_Lounge_EventScript_Norma, 0

CinnabarIsland_PokemonLab_Lounge_MapWarps:
	warp_def 7, 9, 3, 3, MAP_CINNABAR_ISLAND_POKEMON_LAB_ENTRANCE

CinnabarIsland_PokemonLab_Lounge_MapEvents::
	map_events CinnabarIsland_PokemonLab_Lounge_ObjectEvents, CinnabarIsland_PokemonLab_Lounge_MapWarps, NULL, NULL

@ ===== END data/maps/CinnabarIsland_PokemonLab_Lounge/events.inc =====
@ ===== BEGIN data/maps/CinnabarIsland_PokemonLab_ResearchRoom/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/CinnabarIsland_PokemonLab_ResearchRoom/map.json
@

	.align 2

CinnabarIsland_PokemonLab_ResearchRoom_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_POKE_MANIAC, 5, 4, 3, MOVEMENT_TYPE_WANDER_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, CinnabarIsland_PokemonLab_ResearchRoom_EventScript_MetronomeTutor, 0
	object_event 2, OBJ_EVENT_GFX_SCIENTIST, 10, 3, 3, MOVEMENT_TYPE_WANDER_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, CinnabarIsland_PokemonLab_ResearchRoom_EventScript_Scientist, 0

CinnabarIsland_PokemonLab_ResearchRoom_MapWarps:
	warp_def 7, 9, 3, 4, MAP_CINNABAR_ISLAND_POKEMON_LAB_ENTRANCE

CinnabarIsland_PokemonLab_ResearchRoom_MapBGEvents:
	bg_sign_event 6, 1, 0, BG_EVENT_PLAYER_FACING_ANY, CinnabarIsland_PokemonLab_ResearchRoom_EventScript_AmberPipe
	bg_sign_event 3, 1, 0, BG_EVENT_PLAYER_FACING_ANY, CinnabarIsland_PokemonLab_ResearchRoom_EventScript_Computer

CinnabarIsland_PokemonLab_ResearchRoom_MapEvents::
	map_events CinnabarIsland_PokemonLab_ResearchRoom_ObjectEvents, CinnabarIsland_PokemonLab_ResearchRoom_MapWarps, NULL, CinnabarIsland_PokemonLab_ResearchRoom_MapBGEvents

@ ===== END data/maps/CinnabarIsland_PokemonLab_ResearchRoom/events.inc =====
@ ===== BEGIN data/maps/CinnabarIsland_PokemonLab_ExperimentRoom/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/CinnabarIsland_PokemonLab_ExperimentRoom/map.json
@

	.align 2

CinnabarIsland_PokemonLab_ExperimentRoom_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_BOY, 11, 8, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NONE, 0, CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_Garett, 0
	object_event 2, OBJ_EVENT_GFX_SCIENTIST, 12, 3, 3, MOVEMENT_TYPE_WANDER_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_FossilScientist, 0

CinnabarIsland_PokemonLab_ExperimentRoom_MapWarps:
	warp_def 7, 9, 3, 5, MAP_CINNABAR_ISLAND_POKEMON_LAB_ENTRANCE

CinnabarIsland_PokemonLab_ExperimentRoom_MapEvents::
	map_events CinnabarIsland_PokemonLab_ExperimentRoom_ObjectEvents, CinnabarIsland_PokemonLab_ExperimentRoom_MapWarps, NULL, NULL

@ ===== END data/maps/CinnabarIsland_PokemonLab_ExperimentRoom/events.inc =====
@ ===== BEGIN data/maps/CinnabarIsland_PokemonCenter_1F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/CinnabarIsland_PokemonCenter_1F/map.json
@

	.align 2

CinnabarIsland_PokemonCenter_1F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_NURSE, 7, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, CinnabarIsland_PokemonCenter_1F_EventScript_Nurse, 0
	object_event 2, OBJ_EVENT_GFX_COOLTRAINER_F, 2, 4, 3, MOVEMENT_TYPE_WANDER_LEFT_AND_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, CinnabarIsland_PokemonCenter_1F_EventScript_CooltrainerF, 0
	object_event 3, OBJ_EVENT_GFX_GENTLEMAN, 9, 7, 3, MOVEMENT_TYPE_WANDER_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, CinnabarIsland_PokemonCenter_1F_EventScript_Gentleman, 0
	object_event 4, OBJ_EVENT_GFX_YOUNGSTER, 14, 6, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NONE, 0, CinnabarIsland_PokemonCenter_1F_EventScript_Youngster, 0
	object_event 5, 0, 2, 1, 0, MOVEMENT_TYPE_INVISIBLE, 1, 1, TRAINER_TYPE_NONE, 0, CinnabarIsland_PokemonCenter_1F_EventScript_PokemonJournalMrFuji, FLAG_HIDE_POSTGAME_GOSSIPERS
	object_event 6, 0, 3, 1, 0, MOVEMENT_TYPE_INVISIBLE, 1, 1, TRAINER_TYPE_NONE, 0, CinnabarIsland_PokemonCenter_1F_EventScript_PokemonJournalMrFuji, FLAG_HIDE_POSTGAME_GOSSIPERS
	object_event 7, OBJ_EVENT_GFX_BILL, 11, 5, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, CinnabarIsland_PokemonCenter_1F_EventScript_Bill, FLAG_HIDE_CINNABAR_POKECENTER_BILL

CinnabarIsland_PokemonCenter_1F_MapWarps:
	warp_def 7, 8, 0, 3, MAP_CINNABAR_ISLAND
	warp_def 6, 8, 3, 3, MAP_CINNABAR_ISLAND
	warp_def 8, 8, 0, 3, MAP_CINNABAR_ISLAND
	warp_def 1, 6, 4, 0, MAP_CINNABAR_ISLAND_POKEMON_CENTER_2F

CinnabarIsland_PokemonCenter_1F_MapEvents::
	map_events CinnabarIsland_PokemonCenter_1F_ObjectEvents, CinnabarIsland_PokemonCenter_1F_MapWarps, NULL, NULL

@ ===== END data/maps/CinnabarIsland_PokemonCenter_1F/events.inc =====
@ ===== BEGIN data/maps/CinnabarIsland_PokemonCenter_2F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/CinnabarIsland_PokemonCenter_2F/map.json
@

	.align 2

CinnabarIsland_PokemonCenter_2F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_CABLE_CLUB_RECEPTIONIST, 6, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 0, 0, TRAINER_TYPE_NONE, 0, Common_EventScript_UnionRoomAttendant, 0
	object_event 2, OBJ_EVENT_GFX_CABLE_CLUB_RECEPTIONIST, 2, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 0, 0, TRAINER_TYPE_NONE, 0, Common_EventScript_WirelessClubAttendant, 0
	object_event 3, OBJ_EVENT_GFX_CABLE_CLUB_RECEPTIONIST, 10, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 0, 0, TRAINER_TYPE_NONE, 0, Common_EventScript_DirectCornerAttendant, 0
	object_event 4, OBJ_EVENT_GFX_MG_DELIVERYMAN, 1, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, CableClub_EventScript_MysteryGiftMan, FLAG_HIDE_MG_DELIVERYMEN

CinnabarIsland_PokemonCenter_2F_MapWarps:
	warp_def 1, 6, 4, 3, MAP_CINNABAR_ISLAND_POKEMON_CENTER_1F
	warp_def 5, 1, 0, 0, MAP_UNION_ROOM
	warp_def 9, 1, 0, 0, MAP_TRADE_CENTER

CinnabarIsland_PokemonCenter_2F_MapEvents::
	map_events CinnabarIsland_PokemonCenter_2F_ObjectEvents, CinnabarIsland_PokemonCenter_2F_MapWarps, NULL, NULL

@ ===== END data/maps/CinnabarIsland_PokemonCenter_2F/events.inc =====
@ ===== BEGIN data/maps/CinnabarIsland_Mart/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/CinnabarIsland_Mart/map.json
@

	.align 2

CinnabarIsland_Mart_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_CLERK, 2, 3, 0, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, CinnabarIsland_Mart_EventScript_Clerk, 0
	object_event 2, OBJ_EVENT_GFX_WOMAN_2, 6, 2, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NONE, 0, CinnabarIsland_Mart_EventScript_Woman, 0
	object_event 3, OBJ_EVENT_GFX_SCIENTIST, 8, 2, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NONE, 0, CinnabarIsland_Mart_EventScript_Scientist, 0

CinnabarIsland_Mart_MapWarps:
	warp_def 3, 7, 3, 4, MAP_CINNABAR_ISLAND
	warp_def 4, 7, 3, 4, MAP_CINNABAR_ISLAND
	warp_def 5, 7, 3, 4, MAP_CINNABAR_ISLAND

CinnabarIsland_Mart_MapEvents::
	map_events CinnabarIsland_Mart_ObjectEvents, CinnabarIsland_Mart_MapWarps, NULL, NULL

@ ===== END data/maps/CinnabarIsland_Mart/events.inc =====
@ ===== BEGIN data/maps/IndigoPlateau_PokemonCenter_1F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/IndigoPlateau_PokemonCenter_1F/map.json
@

	.align 2

IndigoPlateau_PokemonCenter_1F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_CLERK, 0, 7, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, IndigoPlateau_PokemonCenter_1F_EventScript_Clerk, 0
	object_event 2, OBJ_EVENT_GFX_NURSE, 13, 10, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, IndigoPlateau_PokemonCenter_1F_EventScript_Nurse, 0
	object_event 3, OBJ_EVENT_GFX_GYM_GUY, 7, 14, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, IndigoPlateau_PokemonCenter_1F_EventScript_GymGuy, 0
	object_event 4, OBJ_EVENT_GFX_COOLTRAINER_F, 5, 3, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, IndigoPlateau_PokemonCenter_1F_EventScript_DoorGuard, 0
	object_event 5, OBJ_EVENT_GFX_BLACK_BELT, 23, 13, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, IndigoPlateau_PokemonCenter_1F_EventScript_BlackBelt, FLAG_HIDE_POSTGAME_GOSSIPERS
	object_event 6, 0, 22, 9, 0, MOVEMENT_TYPE_INVISIBLE, 1, 1, TRAINER_TYPE_NONE, 0, IndigoPlateau_PokemonCenter_1F_EventScript_PokemonJournal, FLAG_HIDE_POSTGAME_GOSSIPERS
	object_event 7, OBJ_EVENT_GFX_COOLTRAINER_M, 16, 15, 3, MOVEMENT_TYPE_WANDER_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, IndigoPlateau_PokemonCenter_1F_EventScript_CooltrainerM, FLAG_HIDE_POSTGAME_GOSSIPERS
	object_event 8, 0, 23, 9, 0, MOVEMENT_TYPE_INVISIBLE, 1, 1, TRAINER_TYPE_NONE, 0, IndigoPlateau_PokemonCenter_1F_EventScript_PokemonJournal, FLAG_HIDE_POSTGAME_GOSSIPERS

IndigoPlateau_PokemonCenter_1F_MapWarps:
	warp_def 11, 16, 3, 0, MAP_INDIGO_PLATEAU_EXTERIOR
	warp_def 4, 1, 3, 0, MAP_POKEMON_LEAGUE_LORELEIS_ROOM
	warp_def 1, 14, 4, 0, MAP_INDIGO_PLATEAU_POKEMON_CENTER_2F

IndigoPlateau_PokemonCenter_1F_MapEvents::
	map_events IndigoPlateau_PokemonCenter_1F_ObjectEvents, IndigoPlateau_PokemonCenter_1F_MapWarps, NULL, NULL

@ ===== END data/maps/IndigoPlateau_PokemonCenter_1F/events.inc =====
@ ===== BEGIN data/maps/IndigoPlateau_PokemonCenter_2F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/IndigoPlateau_PokemonCenter_2F/map.json
@

	.align 2

IndigoPlateau_PokemonCenter_2F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_CABLE_CLUB_RECEPTIONIST, 6, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 0, 0, TRAINER_TYPE_NONE, 0, Common_EventScript_UnionRoomAttendant, 0
	object_event 2, OBJ_EVENT_GFX_CABLE_CLUB_RECEPTIONIST, 2, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 0, 0, TRAINER_TYPE_NONE, 0, Common_EventScript_WirelessClubAttendant, 0
	object_event 3, OBJ_EVENT_GFX_CABLE_CLUB_RECEPTIONIST, 10, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 0, 0, TRAINER_TYPE_NONE, 0, Common_EventScript_DirectCornerAttendant, 0
	object_event 4, OBJ_EVENT_GFX_MG_DELIVERYMAN, 1, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, CableClub_EventScript_MysteryGiftMan, FLAG_HIDE_MG_DELIVERYMEN

IndigoPlateau_PokemonCenter_2F_MapWarps:
	warp_def 1, 6, 4, 2, MAP_INDIGO_PLATEAU_POKEMON_CENTER_1F
	warp_def 5, 1, 0, 0, MAP_UNION_ROOM
	warp_def 9, 1, 0, 0, MAP_TRADE_CENTER

IndigoPlateau_PokemonCenter_2F_MapEvents::
	map_events IndigoPlateau_PokemonCenter_2F_ObjectEvents, IndigoPlateau_PokemonCenter_2F_MapWarps, NULL, NULL

@ ===== END data/maps/IndigoPlateau_PokemonCenter_2F/events.inc =====
@ ===== BEGIN data/maps/SaffronCity_CopycatsHouse_1F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SaffronCity_CopycatsHouse_1F/map.json
@

	.align 2

SaffronCity_CopycatsHouse_1F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_BALDING_MAN, 8, 4, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NONE, 0, SaffronCity_CopycatsHouse_1F_EventScript_CopycatsDad, 0
	object_event 2, OBJ_EVENT_GFX_WOMAN_3, 3, 3, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SaffronCity_CopycatsHouse_1F_EventScript_CopycatsMom, 0
	object_event 3, OBJ_EVENT_GFX_CHANSEY, 4, 4, 3, MOVEMENT_TYPE_WANDER_UP_AND_DOWN, 1, 2, TRAINER_TYPE_NONE, 0, SaffronCity_CopycatsHouse_1F_EventScript_Chansey, 0

SaffronCity_CopycatsHouse_1F_MapWarps:
	warp_def 3, 8, 3, 1, MAP_SAFFRON_CITY
	warp_def 4, 8, 3, 1, MAP_SAFFRON_CITY
	warp_def 5, 8, 3, 1, MAP_SAFFRON_CITY
	warp_def 10, 2, 3, 0, MAP_SAFFRON_CITY_COPYCATS_HOUSE_2F

SaffronCity_CopycatsHouse_1F_MapEvents::
	map_events SaffronCity_CopycatsHouse_1F_ObjectEvents, SaffronCity_CopycatsHouse_1F_MapWarps, NULL, NULL

@ ===== END data/maps/SaffronCity_CopycatsHouse_1F/events.inc =====
@ ===== BEGIN data/maps/SaffronCity_CopycatsHouse_2F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SaffronCity_CopycatsHouse_2F/map.json
@

	.align 2

SaffronCity_CopycatsHouse_2F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_DODUO, 6, 8, 3, MOVEMENT_TYPE_WANDER_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, SaffronCity_CopycatsHouse_2F_EventScript_Doduo, 0
	object_event 2, OBJ_EVENT_GFX_PIKACHU, 4, 6, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SaffronCity_CopycatsHouse_2F_EventScript_Doll, 0
	object_event 3, OBJ_EVENT_GFX_JIGGLYPUFF, 7, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SaffronCity_CopycatsHouse_2F_EventScript_Doll, 0
	object_event 4, OBJ_EVENT_GFX_LITTLE_GIRL, 9, 6, 3, MOVEMENT_TYPE_WANDER_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, SaffronCity_CopycatsHouse_2F_EventScript_Copycat, 0

SaffronCity_CopycatsHouse_2F_MapWarps:
	warp_def 10, 2, 3, 3, MAP_SAFFRON_CITY_COPYCATS_HOUSE_1F

SaffronCity_CopycatsHouse_2F_MapBGEvents:
	bg_sign_event 1, 1, 0, BG_EVENT_PLAYER_FACING_ANY, SaffronCity_CopycatsHouse_2F_EventScript_Computer
	bg_sign_event 3, 5, 0, BG_EVENT_PLAYER_FACING_ANY, SaffronCity_CopycatsHouse_2F_EventScript_Game
	bg_hidden_item_event 2, 1, 0, ITEM_NUGGET, FLAG_HIDDEN_ITEM_SAFFRON_CITY_COPYCATS_HOUSE_2F_NUGGET, 1, FALSE

SaffronCity_CopycatsHouse_2F_MapEvents::
	map_events SaffronCity_CopycatsHouse_2F_ObjectEvents, SaffronCity_CopycatsHouse_2F_MapWarps, NULL, SaffronCity_CopycatsHouse_2F_MapBGEvents

@ ===== END data/maps/SaffronCity_CopycatsHouse_2F/events.inc =====
@ ===== BEGIN data/maps/SaffronCity_Dojo/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SaffronCity_Dojo/map.json
@

	.align 2

SaffronCity_Dojo_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_BLACK_BELT, 11, 10, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NORMAL, 7, SaffronCity_Dojo_EventScript_Hitoshi, 0
	object_event 2, OBJ_EVENT_GFX_BLACK_BELT, 1, 10, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 7, SaffronCity_Dojo_EventScript_Hideki, 0
	object_event 3, OBJ_EVENT_GFX_BLACK_BELT, 11, 8, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NORMAL, 7, SaffronCity_Dojo_EventScript_Aaron, 0
	object_event 4, OBJ_EVENT_GFX_BLACK_BELT, 1, 8, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NORMAL, 7, SaffronCity_Dojo_EventScript_Mike, 0
	object_event 5, OBJ_EVENT_GFX_BLACK_BELT, 6, 5, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 2, SaffronCity_Dojo_EventScript_MasterKoichi, 0
	object_event 6, OBJ_EVENT_GFX_ITEM_BALL, 5, 3, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SaffronCity_Dojo_EventScript_HitmonleeBall, FLAG_HIDE_DOJO_HITMONLEE_BALL
	object_event 7, OBJ_EVENT_GFX_ITEM_BALL, 7, 3, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SaffronCity_Dojo_EventScript_HitmonchanBall, FLAG_HIDE_DOJO_HITMONCHAN_BALL

SaffronCity_Dojo_MapWarps:
	warp_def 5, 14, 3, 2, MAP_SAFFRON_CITY
	warp_def 6, 14, 3, 2, MAP_SAFFRON_CITY
	warp_def 7, 14, 3, 2, MAP_SAFFRON_CITY

SaffronCity_Dojo_MapCoordEvents:
	coord_event 5, 5, 3, VAR_MAP_SCENE_SAFFRON_CITY_DOJO, 0, SaffronCity_Dojo_EventScript_TriggerMasterBattleLeft
	coord_event 7, 5, 3, VAR_MAP_SCENE_SAFFRON_CITY_DOJO, 0, SaffronCity_Dojo_EventScript_TriggerMasterBattleRight

SaffronCity_Dojo_MapBGEvents:
	bg_sign_event 3, 13, 0, BG_EVENT_PLAYER_FACING_ANY, SaffronCity_Dojo_EventScript_Statue
	bg_sign_event 9, 13, 0, BG_EVENT_PLAYER_FACING_ANY, SaffronCity_Dojo_EventScript_Statue
	bg_sign_event 5, 2, 0, BG_EVENT_PLAYER_FACING_ANY, SaffronCity_Dojo_EventScript_LeftScroll
	bg_sign_event 7, 2, 0, BG_EVENT_PLAYER_FACING_ANY, SaffronCity_Dojo_EventScript_RightScroll

SaffronCity_Dojo_MapEvents::
	map_events SaffronCity_Dojo_ObjectEvents, SaffronCity_Dojo_MapWarps, SaffronCity_Dojo_MapCoordEvents, SaffronCity_Dojo_MapBGEvents

@ ===== END data/maps/SaffronCity_Dojo/events.inc =====
@ ===== BEGIN data/maps/SaffronCity_Gym/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SaffronCity_Gym/map.json
@

	.align 2

SaffronCity_Gym_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_COOLTRAINER_M, 24, 18, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 3, SaffronCity_Gym_EventScript_Cameron, 0
	object_event 2, OBJ_EVENT_GFX_COOLTRAINER_M, 24, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 3, SaffronCity_Gym_EventScript_Johan, 0
	object_event 3, OBJ_EVENT_GFX_COOLTRAINER_M, 4, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 3, SaffronCity_Gym_EventScript_Preston, 0
	object_event 4, OBJ_EVENT_GFX_CHANNELER, 14, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 3, SaffronCity_Gym_EventScript_Amanda, 0
	object_event 5, OBJ_EVENT_GFX_CHANNELER, 4, 10, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 3, SaffronCity_Gym_EventScript_Stacy, 0
	object_event 6, OBJ_EVENT_GFX_CHANNELER, 4, 18, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 3, SaffronCity_Gym_EventScript_Tasha, 0
	object_event 7, OBJ_EVENT_GFX_SABRINA, 14, 11, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SaffronCity_Gym_EventScript_Sabrina, 0
	object_event 8, OBJ_EVENT_GFX_COOLTRAINER_M, 24, 10, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 3, SaffronCity_Gym_EventScript_Tyron, 0
	object_event 9, OBJ_EVENT_GFX_GYM_GUY, 15, 20, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SaffronCity_Gym_EventScript_GymGuy, 0

SaffronCity_Gym_MapWarps:
	warp_def 13, 23, 3, 3, MAP_SAFFRON_CITY
	warp_def 14, 23, 3, 3, MAP_SAFFRON_CITY
	warp_def 15, 23, 3, 3, MAP_SAFFRON_CITY
	warp_def 18, 20, 3, 32, MAP_SAFFRON_CITY_GYM
	warp_def 0, 4, 3, 22, MAP_SAFFRON_CITY_GYM
	warp_def 0, 7, 3, 20, MAP_SAFFRON_CITY_GYM
	warp_def 0, 12, 3, 30, MAP_SAFFRON_CITY_GYM
	warp_def 0, 15, 3, 11, MAP_SAFFRON_CITY_GYM
	warp_def 0, 20, 3, 28, MAP_SAFFRON_CITY_GYM
	warp_def 0, 23, 3, 19, MAP_SAFFRON_CITY_GYM
	warp_def 8, 4, 3, 18, MAP_SAFFRON_CITY_GYM
	warp_def 8, 7, 3, 7, MAP_SAFFRON_CITY_GYM
	warp_def 8, 12, 3, 17, MAP_SAFFRON_CITY_GYM
	warp_def 8, 15, 3, 15, MAP_SAFFRON_CITY_GYM
	warp_def 8, 20, 3, 26, MAP_SAFFRON_CITY_GYM
	warp_def 8, 23, 3, 13, MAP_SAFFRON_CITY_GYM
	warp_def 12, 4, 3, 24, MAP_SAFFRON_CITY_GYM
	warp_def 12, 7, 3, 12, MAP_SAFFRON_CITY_GYM
	warp_def 16, 4, 3, 10, MAP_SAFFRON_CITY_GYM
	warp_def 16, 7, 3, 9, MAP_SAFFRON_CITY_GYM
	warp_def 18, 15, 3, 5, MAP_SAFFRON_CITY_GYM
	warp_def 20, 4, 3, 23, MAP_SAFFRON_CITY_GYM
	warp_def 20, 7, 3, 4, MAP_SAFFRON_CITY_GYM
	warp_def 20, 12, 3, 21, MAP_SAFFRON_CITY_GYM
	warp_def 20, 15, 3, 16, MAP_SAFFRON_CITY_GYM
	warp_def 20, 20, 3, 27, MAP_SAFFRON_CITY_GYM
	warp_def 20, 23, 3, 14, MAP_SAFFRON_CITY_GYM
	warp_def 28, 4, 3, 25, MAP_SAFFRON_CITY_GYM
	warp_def 28, 7, 3, 8, MAP_SAFFRON_CITY_GYM
	warp_def 28, 12, 3, 31, MAP_SAFFRON_CITY_GYM
	warp_def 28, 15, 3, 6, MAP_SAFFRON_CITY_GYM
	warp_def 28, 20, 3, 29, MAP_SAFFRON_CITY_GYM
	warp_def 28, 23, 3, 3, MAP_SAFFRON_CITY_GYM

SaffronCity_Gym_MapBGEvents:
	bg_sign_event 12, 20, 0, BG_EVENT_PLAYER_FACING_ANY, SaffronCity_Gym_EventScript_GymStatue
	bg_sign_event 16, 20, 0, BG_EVENT_PLAYER_FACING_ANY, SaffronCity_Gym_EventScript_GymStatue

SaffronCity_Gym_MapEvents::
	map_events SaffronCity_Gym_ObjectEvents, SaffronCity_Gym_MapWarps, NULL, SaffronCity_Gym_MapBGEvents

@ ===== END data/maps/SaffronCity_Gym/events.inc =====
@ ===== BEGIN data/maps/SaffronCity_House/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SaffronCity_House/map.json
@

	.align 2

SaffronCity_House_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_PIDGEY, 0, 5, 3, MOVEMENT_TYPE_WANDER_UP_AND_DOWN, 1, 4, TRAINER_TYPE_NONE, 0, SaffronCity_House_EventScript_Pidgey, 0
	object_event 2, OBJ_EVENT_GFX_LASS, 4, 4, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, SaffronCity_House_EventScript_Lass, 0
	object_event 3, OBJ_EVENT_GFX_YOUNGSTER, 6, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SaffronCity_House_EventScript_Youngster, 0
	object_event 4, OBJ_EVENT_GFX_CLIPBOARD, 5, 4, 0, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NONE, 0, 0x0, 0

SaffronCity_House_MapWarps:
	warp_def 3, 7, 3, 4, MAP_SAFFRON_CITY
	warp_def 4, 7, 3, 4, MAP_SAFFRON_CITY
	warp_def 5, 7, 3, 4, MAP_SAFFRON_CITY

SaffronCity_House_MapBGEvents:
	bg_sign_event 5, 4, 3, BG_EVENT_PLAYER_FACING_ANY, SaffronCity_House_EventScript_Letter

SaffronCity_House_MapEvents::
	map_events SaffronCity_House_ObjectEvents, SaffronCity_House_MapWarps, NULL, SaffronCity_House_MapBGEvents

@ ===== END data/maps/SaffronCity_House/events.inc =====
@ ===== BEGIN data/maps/SaffronCity_Mart/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SaffronCity_Mart/map.json
@

	.align 2

SaffronCity_Mart_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_CLERK, 2, 3, 0, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, SaffronCity_Mart_EventScript_Clerk, 0
	object_event 2, OBJ_EVENT_GFX_YOUNGSTER, 1, 7, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, SaffronCity_Mart_EventScript_Youngster, 0
	object_event 3, OBJ_EVENT_GFX_LASS, 9, 5, 3, MOVEMENT_TYPE_WANDER_UP_AND_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SaffronCity_Mart_EventScript_Lass, 0

SaffronCity_Mart_MapWarps:
	warp_def 3, 7, 3, 5, MAP_SAFFRON_CITY
	warp_def 4, 7, 3, 5, MAP_SAFFRON_CITY
	warp_def 5, 7, 3, 5, MAP_SAFFRON_CITY

SaffronCity_Mart_MapEvents::
	map_events SaffronCity_Mart_ObjectEvents, SaffronCity_Mart_MapWarps, NULL, NULL

@ ===== END data/maps/SaffronCity_Mart/events.inc =====
@ ===== BEGIN data/maps/SaffronCity_PokemonCenter_1F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SaffronCity_PokemonCenter_1F/map.json
@

	.align 2

SaffronCity_PokemonCenter_1F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_NURSE, 7, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SaffronCity_PokemonCenter_1F_EventScript_Nurse, 0
	object_event 2, OBJ_EVENT_GFX_GENTLEMAN, 14, 6, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NONE, 0, SaffronCity_PokemonCenter_1F_EventScript_Gentleman, 0
	object_event 3, OBJ_EVENT_GFX_WOMAN_3, 4, 4, 3, MOVEMENT_TYPE_WANDER_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, SaffronCity_PokemonCenter_1F_EventScript_Woman, 0
	object_event 4, OBJ_EVENT_GFX_YOUNGSTER, 9, 6, 3, MOVEMENT_TYPE_WANDER_UP_AND_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SaffronCity_PokemonCenter_1F_EventScript_Youngster, 0
	object_event 5, 0, 2, 1, 0, MOVEMENT_TYPE_INVISIBLE, 1, 1, TRAINER_TYPE_NONE, 0, SaffronCity_PokemonCenter_1F_EventScript_PokemonJournalSabrina, FLAG_HIDE_SAFFRON_CITY_POKECENTER_SABRINA_JOURNALS
	object_event 6, 0, 3, 1, 0, MOVEMENT_TYPE_INVISIBLE, 1, 1, TRAINER_TYPE_NONE, 0, SaffronCity_PokemonCenter_1F_EventScript_PokemonJournalSabrina, FLAG_HIDE_SAFFRON_CITY_POKECENTER_SABRINA_JOURNALS

SaffronCity_PokemonCenter_1F_MapWarps:
	warp_def 6, 8, 3, 6, MAP_SAFFRON_CITY
	warp_def 7, 8, 3, 6, MAP_SAFFRON_CITY
	warp_def 8, 8, 3, 6, MAP_SAFFRON_CITY
	warp_def 1, 6, 4, 0, MAP_SAFFRON_CITY_POKEMON_CENTER_2F

SaffronCity_PokemonCenter_1F_MapEvents::
	map_events SaffronCity_PokemonCenter_1F_ObjectEvents, SaffronCity_PokemonCenter_1F_MapWarps, NULL, NULL

@ ===== END data/maps/SaffronCity_PokemonCenter_1F/events.inc =====
@ ===== BEGIN data/maps/SaffronCity_PokemonCenter_2F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SaffronCity_PokemonCenter_2F/map.json
@

	.align 2

SaffronCity_PokemonCenter_2F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_CABLE_CLUB_RECEPTIONIST, 6, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 0, 0, TRAINER_TYPE_NONE, 0, Common_EventScript_UnionRoomAttendant, 0
	object_event 2, OBJ_EVENT_GFX_CABLE_CLUB_RECEPTIONIST, 2, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 0, 0, TRAINER_TYPE_NONE, 0, Common_EventScript_WirelessClubAttendant, 0
	object_event 3, OBJ_EVENT_GFX_CABLE_CLUB_RECEPTIONIST, 10, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 0, 0, TRAINER_TYPE_NONE, 0, Common_EventScript_DirectCornerAttendant, 0
	object_event 4, OBJ_EVENT_GFX_MG_DELIVERYMAN, 1, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, CableClub_EventScript_MysteryGiftMan, FLAG_HIDE_MG_DELIVERYMEN

SaffronCity_PokemonCenter_2F_MapWarps:
	warp_def 1, 6, 4, 3, MAP_SAFFRON_CITY_POKEMON_CENTER_1F
	warp_def 5, 1, 0, 0, MAP_UNION_ROOM
	warp_def 9, 1, 0, 0, MAP_TRADE_CENTER

SaffronCity_PokemonCenter_2F_MapEvents::
	map_events SaffronCity_PokemonCenter_2F_ObjectEvents, SaffronCity_PokemonCenter_2F_MapWarps, NULL, NULL

@ ===== END data/maps/SaffronCity_PokemonCenter_2F/events.inc =====
@ ===== BEGIN data/maps/SaffronCity_MrPsychicsHouse/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SaffronCity_MrPsychicsHouse/map.json
@

	.align 2

SaffronCity_MrPsychicsHouse_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_BALDING_MAN, 7, 4, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NONE, 0, SaffronCity_MrPsychicsHouse_EventScript_MrPsychic, 0

SaffronCity_MrPsychicsHouse_MapWarps:
	warp_def 3, 7, 3, 7, MAP_SAFFRON_CITY
	warp_def 4, 7, 3, 7, MAP_SAFFRON_CITY
	warp_def 5, 7, 3, 7, MAP_SAFFRON_CITY

SaffronCity_MrPsychicsHouse_MapEvents::
	map_events SaffronCity_MrPsychicsHouse_ObjectEvents, SaffronCity_MrPsychicsHouse_MapWarps, NULL, NULL

@ ===== END data/maps/SaffronCity_MrPsychicsHouse/events.inc =====
@ ===== BEGIN data/maps/SaffronCity_PokemonTrainerFanClub/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SaffronCity_PokemonTrainerFanClub/map.json
@

	.align 2

SaffronCity_PokemonTrainerFanClub_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_CRUSH_GIRL, 7, 13, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NONE, 0, SaffronCity_PokemonTrainerFanClub_EventScript_CrushGirl, 0
	object_event 2, OBJ_EVENT_GFX_LITTLE_GIRL, 6, 11, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SaffronCity_PokemonTrainerFanClub_EventScript_LittleGirl, 0
	object_event 3, OBJ_EVENT_GFX_YOUNGSTER, 3, 13, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, SaffronCity_PokemonTrainerFanClub_EventScript_Youngster, 0
	object_event 4, OBJ_EVENT_GFX_GENTLEMAN, 3, 12, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, SaffronCity_PokemonTrainerFanClub_EventScript_Gentleman, 0
	object_event 5, OBJ_EVENT_GFX_WOMAN_3, 9, 11, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SaffronCity_PokemonTrainerFanClub_EventScript_Woman, FLAG_HIDE_SAFFRON_FAN_CLUB_WOMAN
	object_event 6, OBJ_EVENT_GFX_ROCKER, 7, 12, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NONE, 0, SaffronCity_PokemonTrainerFanClub_EventScript_Rocker, FLAG_HIDE_SAFFRON_FAN_CLUB_ROCKER
	object_event 7, OBJ_EVENT_GFX_BEAUTY, 9, 12, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NONE, 0, SaffronCity_PokemonTrainerFanClub_EventScript_Beauty, FLAG_HIDE_SAFFRON_FAN_CLUB_BEAUTY
	object_event 8, OBJ_EVENT_GFX_BLACK_BELT, 5, 11, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SaffronCity_PokemonTrainerFanClub_EventScript_BlackBelt, FLAG_HIDE_SAFFRON_FAN_CLUB_BLACK_BELT
	object_event 9, 0, 2, 1, 0, MOVEMENT_TYPE_INVISIBLE, 1, 1, TRAINER_TYPE_NONE, 0, SaffronCity_PokemonTrainerFanClub_EventScript_PokemonJournalBruno, FLAG_HIDE_POSTGAME_GOSSIPERS
	object_event 10, 0, 3, 1, 0, MOVEMENT_TYPE_INVISIBLE, 1, 1, TRAINER_TYPE_NONE, 0, SaffronCity_PokemonTrainerFanClub_EventScript_PokemonJournalBruno, FLAG_HIDE_POSTGAME_GOSSIPERS

SaffronCity_PokemonTrainerFanClub_MapWarps:
	warp_def 5, 15, 3, 14, MAP_SAFFRON_CITY

SaffronCity_PokemonTrainerFanClub_MapEvents::
	map_events SaffronCity_PokemonTrainerFanClub_ObjectEvents, SaffronCity_PokemonTrainerFanClub_MapWarps, NULL, NULL

@ ===== END data/maps/SaffronCity_PokemonTrainerFanClub/events.inc =====
@ ===== BEGIN data/maps/Route2_ViridianForest_SouthEntrance/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route2_ViridianForest_SouthEntrance/map.json
@

	.align 2

Route2_ViridianForest_SouthEntrance_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_WOMAN_2, 10, 6, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NONE, 0, Route2_ViridianForest_SouthEntrance_EventScript_Woman1, 0
	object_event 2, OBJ_EVENT_GFX_WOMAN_1, 4, 7, 3, MOVEMENT_TYPE_WANDER_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, Route2_ViridianForest_SouthEntrance_EventScript_Woman2, 0

Route2_ViridianForest_SouthEntrance_MapWarps:
	warp_def 6, 10, 3, 2, MAP_ROUTE2
	warp_def 7, 10, 3, 2, MAP_ROUTE2
	warp_def 8, 10, 3, 2, MAP_ROUTE2
	warp_def 7, 1, 3, 0, MAP_VIRIDIAN_FOREST

Route2_ViridianForest_SouthEntrance_MapEvents::
	map_events Route2_ViridianForest_SouthEntrance_ObjectEvents, Route2_ViridianForest_SouthEntrance_MapWarps, NULL, NULL

@ ===== END data/maps/Route2_ViridianForest_SouthEntrance/events.inc =====
@ ===== BEGIN data/maps/Route2_House/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route2_House/map.json
@

	.align 2

Route2_House_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_SCIENTIST, 4, 5, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, Route2_House_EventScript_Scientist, 0
	object_event 2, OBJ_EVENT_GFX_GBA_KID, 7, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, Route2_House_EventScript_Reyley, 0

Route2_House_MapWarps:
	warp_def 3, 7, 0, 4, MAP_ROUTE2
	warp_def 4, 7, 0, 4, MAP_ROUTE2
	warp_def 5, 7, 0, 4, MAP_ROUTE2

Route2_House_MapEvents::
	map_events Route2_House_ObjectEvents, Route2_House_MapWarps, NULL, NULL

@ ===== END data/maps/Route2_House/events.inc =====
@ ===== BEGIN data/maps/Route2_EastBuilding/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route2_EastBuilding/map.json
@

	.align 2

Route2_EastBuilding_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_SCIENTIST, 4, 6, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, Route2_EastBuilding_EventScript_Aide, 0
	object_event 2, OBJ_EVENT_GFX_ROCKER, 10, 3, 3, MOVEMENT_TYPE_WANDER_LEFT_AND_RIGHT, 2, 1, TRAINER_TYPE_NONE, 0, Route2_EastBuilding_EventScript_Rocker, 0

Route2_EastBuilding_MapWarps:
	warp_def 6, 10, 0, 5, MAP_ROUTE2
	warp_def 7, 10, 3, 5, MAP_ROUTE2
	warp_def 8, 10, 3, 5, MAP_ROUTE2
	warp_def 7, 1, 3, 6, MAP_ROUTE2

Route2_EastBuilding_MapEvents::
	map_events Route2_EastBuilding_ObjectEvents, Route2_EastBuilding_MapWarps, NULL, NULL

@ ===== END data/maps/Route2_EastBuilding/events.inc =====
@ ===== BEGIN data/maps/Route2_ViridianForest_NorthEntrance/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route2_ViridianForest_NorthEntrance/map.json
@

	.align 2

Route2_ViridianForest_NorthEntrance_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_YOUNGSTER, 5, 4, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, Route2_ViridianForest_NorthEntrance_EventScript_Youngster, 0
	object_event 2, OBJ_EVENT_GFX_OLD_MAN_1, 4, 7, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, Route2_ViridianForest_NorthEntrance_EventScript_OldMan, 0
	object_event 3, OBJ_EVENT_GFX_COOLTRAINER_F, 10, 5, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, Route2_ViridianForest_NorthEntrance_EventScript_CooltrainerF, 0

Route2_ViridianForest_NorthEntrance_MapWarps:
	warp_def 6, 10, 3, 2, MAP_VIRIDIAN_FOREST
	warp_def 7, 10, 3, 2, MAP_VIRIDIAN_FOREST
	warp_def 8, 10, 3, 2, MAP_VIRIDIAN_FOREST
	warp_def 7, 1, 3, 0, MAP_ROUTE2

Route2_ViridianForest_NorthEntrance_MapEvents::
	map_events Route2_ViridianForest_NorthEntrance_ObjectEvents, Route2_ViridianForest_NorthEntrance_MapWarps, NULL, NULL

@ ===== END data/maps/Route2_ViridianForest_NorthEntrance/events.inc =====
@ ===== BEGIN data/maps/Route4_PokemonCenter_1F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route4_PokemonCenter_1F/map.json
@

	.align 2

Route4_PokemonCenter_1F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_NURSE, 7, 2, 0, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, Route4_PokemonCenter_1F_EventScript_Nurse, 0
	object_event 2, OBJ_EVENT_GFX_BALDING_MAN, 1, 3, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, Route4_PokemonCenter_1F_EventScript_MagikarpSalesman, 0
	object_event 3, OBJ_EVENT_GFX_GENTLEMAN, 12, 5, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, Route4_PokemonCenter_1F_EventScript_Gentleman, 0
	object_event 4, OBJ_EVENT_GFX_BOY, 5, 4, 3, MOVEMENT_TYPE_WANDER_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, Route4_PokemonCenter_1F_EventScript_Boy, 0
	object_event 5, OBJ_EVENT_GFX_YOUNGSTER, 14, 4, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, Route4_PokemonCenter_1F_EventScript_Youngster, 0
	object_event 6, OBJ_EVENT_GFX_CLIPBOARD, 12, 6, 0, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, Route4_PokemonCenter_1F_EventScript_Newspaper, 0

Route4_PokemonCenter_1F_MapWarps:
	warp_def 6, 8, 3, 2, MAP_ROUTE4
	warp_def 7, 8, 3, 2, MAP_ROUTE4
	warp_def 8, 8, 3, 2, MAP_ROUTE4
	warp_def 1, 6, 4, 0, MAP_ROUTE4_POKEMON_CENTER_2F

Route4_PokemonCenter_1F_MapEvents::
	map_events Route4_PokemonCenter_1F_ObjectEvents, Route4_PokemonCenter_1F_MapWarps, NULL, NULL

@ ===== END data/maps/Route4_PokemonCenter_1F/events.inc =====
@ ===== BEGIN data/maps/Route4_PokemonCenter_2F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route4_PokemonCenter_2F/map.json
@

	.align 2

Route4_PokemonCenter_2F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_CABLE_CLUB_RECEPTIONIST, 6, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 0, 0, TRAINER_TYPE_NONE, 0, Common_EventScript_UnionRoomAttendant, 0
	object_event 2, OBJ_EVENT_GFX_CABLE_CLUB_RECEPTIONIST, 2, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 0, 0, TRAINER_TYPE_NONE, 0, Common_EventScript_WirelessClubAttendant, 0
	object_event 3, OBJ_EVENT_GFX_CABLE_CLUB_RECEPTIONIST, 10, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 0, 0, TRAINER_TYPE_NONE, 0, Common_EventScript_DirectCornerAttendant, 0
	object_event 4, OBJ_EVENT_GFX_MG_DELIVERYMAN, 1, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, CableClub_EventScript_MysteryGiftMan, FLAG_HIDE_MG_DELIVERYMEN

Route4_PokemonCenter_2F_MapWarps:
	warp_def 1, 6, 4, 3, MAP_ROUTE4_POKEMON_CENTER_1F
	warp_def 5, 1, 0, 0, MAP_UNION_ROOM
	warp_def 9, 1, 0, 0, MAP_TRADE_CENTER

Route4_PokemonCenter_2F_MapEvents::
	map_events Route4_PokemonCenter_2F_ObjectEvents, Route4_PokemonCenter_2F_MapWarps, NULL, NULL

@ ===== END data/maps/Route4_PokemonCenter_2F/events.inc =====
@ ===== BEGIN data/maps/Route5_PokemonDayCare/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route5_PokemonDayCare/map.json
@

	.align 2

Route5_PokemonDayCare_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_GENTLEMAN, 4, 4, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, Route5_PokemonDayCare_EventScript_DaycareMan, 0

Route5_PokemonDayCare_MapWarps:
	warp_def 3, 7, 0, 1, MAP_ROUTE5
	warp_def 4, 7, 0, 1, MAP_ROUTE5
	warp_def 5, 7, 0, 1, MAP_ROUTE5

Route5_PokemonDayCare_MapEvents::
	map_events Route5_PokemonDayCare_ObjectEvents, Route5_PokemonDayCare_MapWarps, NULL, NULL

@ ===== END data/maps/Route5_PokemonDayCare/events.inc =====
@ ===== BEGIN data/maps/Route5_SouthEntrance/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route5_SouthEntrance/map.json
@

	.align 2

Route5_SouthEntrance_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_POLICEMAN, 1, 5, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, Route5_SouthEntrance_EventScript_Guard, 0

Route5_SouthEntrance_MapWarps:
	warp_def 3, 9, 3, 9, MAP_SAFFRON_CITY
	warp_def 4, 1, 3, 2, MAP_ROUTE5
	warp_def 4, 9, 3, 9, MAP_SAFFRON_CITY
	warp_def 5, 1, 0, 3, MAP_ROUTE5

Route5_SouthEntrance_MapCoordEvents:
	coord_event 3, 5, 3, VAR_MAP_SCENE_ROUTE5_ROUTE6_ROUTE7_ROUTE8_GATES, 0, Route5_SouthEntrance_EventScript_GuardTriggerLeft
	coord_event 4, 5, 3, VAR_MAP_SCENE_ROUTE5_ROUTE6_ROUTE7_ROUTE8_GATES, 0, Route5_SouthEntrance_EventScript_GuardTriggerMid
	coord_event 5, 5, 3, VAR_MAP_SCENE_ROUTE5_ROUTE6_ROUTE7_ROUTE8_GATES, 0, Route5_SouthEntrance_EventScript_GuardTriggerRight

Route5_SouthEntrance_MapEvents::
	map_events Route5_SouthEntrance_ObjectEvents, Route5_SouthEntrance_MapWarps, Route5_SouthEntrance_MapCoordEvents, NULL

@ ===== END data/maps/Route5_SouthEntrance/events.inc =====
@ ===== BEGIN data/maps/Route6_NorthEntrance/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route6_NorthEntrance/map.json
@

	.align 2

Route6_NorthEntrance_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_POLICEMAN, 7, 5, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NONE, 0, Route6_NorthEntrance_EventScript_Guard, 0

Route6_NorthEntrance_MapWarps:
	warp_def 4, 1, 0, 11, MAP_SAFFRON_CITY
	warp_def 5, 1, 0, 11, MAP_SAFFRON_CITY
	warp_def 4, 9, 3, 1, MAP_ROUTE6
	warp_def 5, 9, 3, 1, MAP_ROUTE6

Route6_NorthEntrance_MapCoordEvents:
	coord_event 3, 5, 3, VAR_MAP_SCENE_ROUTE5_ROUTE6_ROUTE7_ROUTE8_GATES, 0, Route6_NorthEntrance_EventScript_GuardTriggerLeft
	coord_event 4, 5, 3, VAR_MAP_SCENE_ROUTE5_ROUTE6_ROUTE7_ROUTE8_GATES, 0, Route6_NorthEntrance_EventScript_GuardTriggerMid
	coord_event 5, 5, 3, VAR_MAP_SCENE_ROUTE5_ROUTE6_ROUTE7_ROUTE8_GATES, 0, Route6_NorthEntrance_EventScript_GuardTriggerRight

Route6_NorthEntrance_MapEvents::
	map_events Route6_NorthEntrance_ObjectEvents, Route6_NorthEntrance_MapWarps, Route6_NorthEntrance_MapCoordEvents, NULL

@ ===== END data/maps/Route6_NorthEntrance/events.inc =====
@ ===== BEGIN data/maps/Route6_UnusedHouse/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route6_UnusedHouse/map.json
@

	.align 2

Route6_UnusedHouse_MapEvents::
	map_events NULL, NULL, NULL, NULL

@ ===== END data/maps/Route6_UnusedHouse/events.inc =====
@ ===== BEGIN data/maps/Route7_EastEntrance/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route7_EastEntrance/map.json
@

	.align 2

Route7_EastEntrance_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_POLICEMAN, 6, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, Route7_EastEntrance_EventScript_Guard, 0

Route7_EastEntrance_MapWarps:
	warp_def 1, 5, 3, 1, MAP_ROUTE7
	warp_def 1, 6, 3, 1, MAP_ROUTE7
	warp_def 11, 5, 3, 8, MAP_SAFFRON_CITY
	warp_def 11, 6, 3, 8, MAP_SAFFRON_CITY

Route7_EastEntrance_MapCoordEvents:
	coord_event 6, 4, 3, VAR_MAP_SCENE_ROUTE5_ROUTE6_ROUTE7_ROUTE8_GATES, 0, Route7_EastEntrance_EventScript_GuardTriggerTop
	coord_event 6, 5, 3, VAR_MAP_SCENE_ROUTE5_ROUTE6_ROUTE7_ROUTE8_GATES, 0, Route7_EastEntrance_EventScript_GuardTriggerMid
	coord_event 6, 6, 3, VAR_MAP_SCENE_ROUTE5_ROUTE6_ROUTE7_ROUTE8_GATES, 0, Route7_EastEntrance_EventScript_GuardTriggerBottom

Route7_EastEntrance_MapEvents::
	map_events Route7_EastEntrance_ObjectEvents, Route7_EastEntrance_MapWarps, Route7_EastEntrance_MapCoordEvents, NULL

@ ===== END data/maps/Route7_EastEntrance/events.inc =====
@ ===== BEGIN data/maps/Route8_WestEntrance/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route8_WestEntrance/map.json
@

	.align 2

Route8_WestEntrance_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_POLICEMAN, 6, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, Route8_WestEntrance_EventScript_Guard, 0

Route8_WestEntrance_MapWarps:
	warp_def 1, 4, 3, 10, MAP_SAFFRON_CITY
	warp_def 1, 5, 3, 10, MAP_SAFFRON_CITY
	warp_def 11, 5, 3, 1, MAP_ROUTE8
	warp_def 11, 6, 3, 1, MAP_ROUTE8

Route8_WestEntrance_MapCoordEvents:
	coord_event 6, 4, 3, VAR_MAP_SCENE_ROUTE5_ROUTE6_ROUTE7_ROUTE8_GATES, 0, Route8_WestEntrance_EventScript_GuardTriggerTop
	coord_event 6, 5, 3, VAR_MAP_SCENE_ROUTE5_ROUTE6_ROUTE7_ROUTE8_GATES, 0, Route8_WestEntrance_EventScript_GuardTriggerMid
	coord_event 6, 6, 3, VAR_MAP_SCENE_ROUTE5_ROUTE6_ROUTE7_ROUTE8_GATES, 0, Route8_WestEntrance_EventScript_GuardTriggerBottom

Route8_WestEntrance_MapEvents::
	map_events Route8_WestEntrance_ObjectEvents, Route8_WestEntrance_MapWarps, Route8_WestEntrance_MapCoordEvents, NULL

@ ===== END data/maps/Route8_WestEntrance/events.inc =====
@ ===== BEGIN data/maps/Route10_PokemonCenter_1F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route10_PokemonCenter_1F/map.json
@

	.align 2

Route10_PokemonCenter_1F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_NURSE, 7, 2, 0, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, Route10_PokemonCenter_1F_EventScript_Nurse, 0
	object_event 2, OBJ_EVENT_GFX_GENTLEMAN, 9, 4, 3, MOVEMENT_TYPE_WANDER_LEFT_AND_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, Route10_PokemonCenter_1F_EventScript_Gentleman, 0
	object_event 3, OBJ_EVENT_GFX_FAT_MAN, 2, 3, 3, MOVEMENT_TYPE_WANDER_LEFT_AND_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, Route10_PokemonCenter_1F_EventScript_FatMan, 0
	object_event 4, OBJ_EVENT_GFX_YOUNGSTER, 14, 6, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NONE, 0, Route10_PokemonCenter_1F_EventScript_Youngster, 0
	object_event 5, OBJ_EVENT_GFX_SCIENTIST, 12, 5, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, Route10_PokemonCenter_1F_EventScript_Aide, 0

Route10_PokemonCenter_1F_MapWarps:
	warp_def 6, 8, 3, 3, MAP_ROUTE10
	warp_def 7, 8, 3, 3, MAP_ROUTE10
	warp_def 8, 8, 3, 3, MAP_ROUTE10
	warp_def 1, 6, 4, 0, MAP_ROUTE10_POKEMON_CENTER_2F

Route10_PokemonCenter_1F_MapEvents::
	map_events Route10_PokemonCenter_1F_ObjectEvents, Route10_PokemonCenter_1F_MapWarps, NULL, NULL

@ ===== END data/maps/Route10_PokemonCenter_1F/events.inc =====
@ ===== BEGIN data/maps/Route10_PokemonCenter_2F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route10_PokemonCenter_2F/map.json
@

	.align 2

Route10_PokemonCenter_2F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_CABLE_CLUB_RECEPTIONIST, 6, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 0, 0, TRAINER_TYPE_NONE, 0, Common_EventScript_UnionRoomAttendant, 0
	object_event 2, OBJ_EVENT_GFX_CABLE_CLUB_RECEPTIONIST, 2, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 0, 0, TRAINER_TYPE_NONE, 0, Common_EventScript_WirelessClubAttendant, 0
	object_event 3, OBJ_EVENT_GFX_CABLE_CLUB_RECEPTIONIST, 10, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 0, 0, TRAINER_TYPE_NONE, 0, Common_EventScript_DirectCornerAttendant, 0
	object_event 4, OBJ_EVENT_GFX_MG_DELIVERYMAN, 1, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, CableClub_EventScript_MysteryGiftMan, FLAG_HIDE_MG_DELIVERYMEN

Route10_PokemonCenter_2F_MapWarps:
	warp_def 1, 6, 4, 3, MAP_ROUTE10_POKEMON_CENTER_1F
	warp_def 5, 1, 0, 0, MAP_UNION_ROOM
	warp_def 9, 1, 0, 0, MAP_TRADE_CENTER

Route10_PokemonCenter_2F_MapEvents::
	map_events Route10_PokemonCenter_2F_ObjectEvents, Route10_PokemonCenter_2F_MapWarps, NULL, NULL

@ ===== END data/maps/Route10_PokemonCenter_2F/events.inc =====
@ ===== BEGIN data/maps/Route11_EastEntrance_1F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route11_EastEntrance_1F/map.json
@

	.align 2

Route11_EastEntrance_1F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_POLICEMAN, 6, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, Route11_EastEntrance_1F_EventScript_TopGuard, 0
	object_event 2, OBJ_EVENT_GFX_POLICEMAN, 4, 10, 0, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NONE, 0, Route11_EastEntrance_1F_EventScript_BottomGuard, 0

Route11_EastEntrance_1F_MapWarps:
	warp_def 1, 6, 3, 1, MAP_ROUTE11
	warp_def 1, 7, 3, 1, MAP_ROUTE11
	warp_def 11, 6, 3, 2, MAP_ROUTE11
	warp_def 11, 7, 3, 2, MAP_ROUTE11
	warp_def 9, 10, 3, 0, MAP_ROUTE11_EAST_ENTRANCE_2F

Route11_EastEntrance_1F_MapEvents::
	map_events Route11_EastEntrance_1F_ObjectEvents, Route11_EastEntrance_1F_MapWarps, NULL, NULL

@ ===== END data/maps/Route11_EastEntrance_1F/events.inc =====
@ ===== BEGIN data/maps/Route11_EastEntrance_2F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route11_EastEntrance_2F/map.json
@

	.align 2

Route11_EastEntrance_2F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_YOUNGSTER, 7, 3, 3, MOVEMENT_TYPE_WANDER_LEFT_AND_RIGHT, 2, 1, TRAINER_TYPE_NONE, 0, Route11_EastEntrance_2F_EventScript_Turner, 0
	object_event 2, OBJ_EVENT_GFX_SCIENTIST, 2, 6, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, Route11_EastEntrance_2F_EventScript_Aide, 0

Route11_EastEntrance_2F_MapWarps:
	warp_def 10, 9, 3, 4, MAP_ROUTE11_EAST_ENTRANCE_1F

Route11_EastEntrance_2F_MapBGEvents:
	bg_sign_event 4, 1, 0, BG_EVENT_PLAYER_FACING_ANY, Route11_EastEntrance_2F_EventScript_LeftBinoculars
	bg_sign_event 8, 1, 0, BG_EVENT_PLAYER_FACING_ANY, Route11_EastEntrance_2F_EventScript_RightBinoculars

Route11_EastEntrance_2F_MapEvents::
	map_events Route11_EastEntrance_2F_ObjectEvents, Route11_EastEntrance_2F_MapWarps, NULL, Route11_EastEntrance_2F_MapBGEvents

@ ===== END data/maps/Route11_EastEntrance_2F/events.inc =====
@ ===== BEGIN data/maps/Route12_NorthEntrance_1F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route12_NorthEntrance_1F/map.json
@

	.align 2

Route12_NorthEntrance_1F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_POLICEMAN, 1, 5, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, Route12_NorthEntrance_1F_EventScript_Guard, 0

Route12_NorthEntrance_1F_MapWarps:
	warp_def 5, 1, 3, 1, MAP_ROUTE12
	warp_def 6, 1, 0, 2, MAP_ROUTE12
	warp_def 5, 11, 3, 3, MAP_ROUTE12
	warp_def 6, 11, 3, 3, MAP_ROUTE12
	warp_def 8, 10, 3, 0, MAP_ROUTE12_NORTH_ENTRANCE_2F

Route12_NorthEntrance_1F_MapEvents::
	map_events Route12_NorthEntrance_1F_ObjectEvents, Route12_NorthEntrance_1F_MapWarps, NULL, NULL

@ ===== END data/maps/Route12_NorthEntrance_1F/events.inc =====
@ ===== BEGIN data/maps/Route12_NorthEntrance_2F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route12_NorthEntrance_2F/map.json
@

	.align 2

Route12_NorthEntrance_2F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_LASS, 7, 5, 3, MOVEMENT_TYPE_WANDER_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, Route12_NorthEntrance_2F_EventScript_Lass, 0

Route12_NorthEntrance_2F_MapWarps:
	warp_def 10, 9, 3, 4, MAP_ROUTE12_NORTH_ENTRANCE_1F

Route12_NorthEntrance_2F_MapBGEvents:
	bg_sign_event 4, 1, 0, BG_EVENT_PLAYER_FACING_ANY, Route12_NorthEntrance_2F_EventScript_LeftBinoculars
	bg_sign_event 8, 1, 0, BG_EVENT_PLAYER_FACING_ANY, Route12_NorthEntrance_2F_EventScript_RightBinoculars

Route12_NorthEntrance_2F_MapEvents::
	map_events Route12_NorthEntrance_2F_ObjectEvents, Route12_NorthEntrance_2F_MapWarps, NULL, Route12_NorthEntrance_2F_MapBGEvents

@ ===== END data/maps/Route12_NorthEntrance_2F/events.inc =====
@ ===== BEGIN data/maps/Route12_FishingHouse/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route12_FishingHouse/map.json
@

	.align 2

Route12_FishingHouse_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_FISHER, 4, 4, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, Route12_FishingHouse_EventScript_FishingGuruBrother, 0

Route12_FishingHouse_MapWarps:
	warp_def 2, 8, 0, 0, MAP_ROUTE12
	warp_def 3, 7, 3, 0, MAP_ROUTE12
	warp_def 4, 8, 0, 0, MAP_ROUTE12

Route12_FishingHouse_MapBGEvents:
	bg_sign_event 9, 1, 0, BG_EVENT_PLAYER_FACING_ANY, Route12_FishingHouse_EventScript_MagikarpRecordSign

Route12_FishingHouse_MapEvents::
	map_events Route12_FishingHouse_ObjectEvents, Route12_FishingHouse_MapWarps, NULL, Route12_FishingHouse_MapBGEvents

@ ===== END data/maps/Route12_FishingHouse/events.inc =====
@ ===== BEGIN data/maps/Route15_WestEntrance_1F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route15_WestEntrance_1F/map.json
@

	.align 2

Route15_WestEntrance_1F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_POLICEMAN, 6, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, Route15_WestEntrance_1F_EventScript_Guard, 0

Route15_WestEntrance_1F_MapWarps:
	warp_def 1, 6, 3, 0, MAP_ROUTE15
	warp_def 1, 7, 3, 0, MAP_ROUTE15
	warp_def 11, 6, 3, 1, MAP_ROUTE15
	warp_def 11, 7, 3, 1, MAP_ROUTE15
	warp_def 9, 10, 3, 0, MAP_ROUTE15_WEST_ENTRANCE_2F

Route15_WestEntrance_1F_MapEvents::
	map_events Route15_WestEntrance_1F_ObjectEvents, Route15_WestEntrance_1F_MapWarps, NULL, NULL

@ ===== END data/maps/Route15_WestEntrance_1F/events.inc =====
@ ===== BEGIN data/maps/Route15_WestEntrance_2F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route15_WestEntrance_2F/map.json
@

	.align 2

Route15_WestEntrance_2F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_SCIENTIST, 5, 5, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NONE, 0, Route15_WestEntrance_2F_EventScript_Aide, 0

Route15_WestEntrance_2F_MapWarps:
	warp_def 10, 9, 3, 4, MAP_ROUTE15_WEST_ENTRANCE_1F

Route15_WestEntrance_2F_MapBGEvents:
	bg_sign_event 4, 1, 0, BG_EVENT_PLAYER_FACING_ANY, Route15_WestEntrance_2F_EventScript_LeftBinoculars
	bg_sign_event 8, 1, 0, BG_EVENT_PLAYER_FACING_ANY, Route15_WestEntrance_2F_EventScript_RightBinoculars

Route15_WestEntrance_2F_MapEvents::
	map_events Route15_WestEntrance_2F_ObjectEvents, Route15_WestEntrance_2F_MapWarps, NULL, Route15_WestEntrance_2F_MapBGEvents

@ ===== END data/maps/Route15_WestEntrance_2F/events.inc =====
@ ===== BEGIN data/maps/Route16_House/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route16_House/map.json
@

	.align 2

Route16_House_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_WOMAN_1, 4, 2, 3, MOVEMENT_TYPE_WANDER_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, Route16_House_EventScript_Woman, 0
	object_event 2, OBJ_EVENT_GFX_FEAROW, 9, 3, 3, MOVEMENT_TYPE_WANDER_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, Route16_House_EventScript_Fearow, 0

Route16_House_MapWarps:
	warp_def 3, 7, 3, 0, MAP_ROUTE16
	warp_def 4, 7, 3, 0, MAP_ROUTE16
	warp_def 5, 7, 3, 0, MAP_ROUTE16

Route16_House_MapEvents::
	map_events Route16_House_ObjectEvents, Route16_House_MapWarps, NULL, NULL

@ ===== END data/maps/Route16_House/events.inc =====
@ ===== BEGIN data/maps/Route16_NorthEntrance_1F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route16_NorthEntrance_1F/map.json
@

	.align 2

Route16_NorthEntrance_1F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_POLICEMAN, 6, 8, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, Route16_NorthEntrance_1F_EventScript_Guard, 0
	object_event 2, OBJ_EVENT_GFX_OLD_MAN_1, 7, 4, 3, MOVEMENT_TYPE_WANDER_LEFT_AND_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, Route16_NorthEntrance_1F_EventScript_OldMan, 0

Route16_NorthEntrance_1F_MapWarps:
	warp_def 1, 3, 3, 1, MAP_ROUTE16
	warp_def 11, 3, 3, 2, MAP_ROUTE16
	warp_def 1, 12, 3, 3, MAP_ROUTE16
	warp_def 11, 12, 3, 4, MAP_ROUTE16
	warp_def 9, 16, 3, 0, MAP_ROUTE16_NORTH_ENTRANCE_2F

Route16_NorthEntrance_1F_MapCoordEvents:
	coord_event 10, 12, 3, VAR_MAP_SCENE_ROUTE16, 1, EventScript_SetExitingCyclingRoad
	coord_event 2, 12, 3, VAR_MAP_SCENE_ROUTE16, 0, EventScript_SetEnteringCyclingRoad
	coord_event 6, 10, 3, VAR_TEMP_1, 0, Route16_NorthEntrance_1F_EventScript_NeedBikeTriggerTop
	coord_event 6, 11, 3, VAR_TEMP_1, 0, Route16_NorthEntrance_1F_EventScript_NeedBikeTriggerMidTop
	coord_event 1, 13, 3, VAR_MAP_SCENE_ROUTE16, 0, EventScript_SetEnteringCyclingRoad
	coord_event 1, 11, 3, VAR_MAP_SCENE_ROUTE16, 0, EventScript_SetEnteringCyclingRoad
	coord_event 11, 11, 3, VAR_MAP_SCENE_ROUTE16, 1, EventScript_SetExitingCyclingRoad
	coord_event 11, 13, 3, VAR_MAP_SCENE_ROUTE16, 1, EventScript_SetExitingCyclingRoad
	coord_event 6, 12, 3, VAR_TEMP_1, 0, Route16_NorthEntrance_1F_EventScript_NeedBikeTriggerMid
	coord_event 6, 13, 3, VAR_TEMP_1, 0, Route16_NorthEntrance_1F_EventScript_NeedBikeTriggerMidBottom
	coord_event 6, 14, 3, VAR_TEMP_1, 0, Route16_NorthEntrance_1F_EventScript_NeedBikeTriggerBottom

Route16_NorthEntrance_1F_MapEvents::
	map_events Route16_NorthEntrance_1F_ObjectEvents, Route16_NorthEntrance_1F_MapWarps, Route16_NorthEntrance_1F_MapCoordEvents, NULL

@ ===== END data/maps/Route16_NorthEntrance_1F/events.inc =====
@ ===== BEGIN data/maps/Route16_NorthEntrance_2F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route16_NorthEntrance_2F/map.json
@

	.align 2

Route16_NorthEntrance_2F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_LITTLE_BOY, 6, 3, 3, MOVEMENT_TYPE_WANDER_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, Route16_NorthEntrance_2F_EventScript_LittleBoy, 0
	object_event 2, OBJ_EVENT_GFX_LITTLE_GIRL, 4, 8, 3, MOVEMENT_TYPE_WANDER_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, Route16_NorthEntrance_2F_EventScript_LittleGirl, 0
	object_event 3, OBJ_EVENT_GFX_SCIENTIST, 10, 6, 0, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NONE, 0, Route16_NorthEntrance_2F_EventScript_Aide, 0

Route16_NorthEntrance_2F_MapWarps:
	warp_def 10, 9, 3, 4, MAP_ROUTE16_NORTH_ENTRANCE_1F

Route16_NorthEntrance_2F_MapBGEvents:
	bg_sign_event 4, 1, 0, BG_EVENT_PLAYER_FACING_ANY, Route16_NorthEntrance_2F_EventScript_LeftBinoculars
	bg_sign_event 8, 1, 0, BG_EVENT_PLAYER_FACING_ANY, Route16_NorthEntrance_2F_EventScript_RightBinoculars

Route16_NorthEntrance_2F_MapEvents::
	map_events Route16_NorthEntrance_2F_ObjectEvents, Route16_NorthEntrance_2F_MapWarps, NULL, Route16_NorthEntrance_2F_MapBGEvents

@ ===== END data/maps/Route16_NorthEntrance_2F/events.inc =====
@ ===== BEGIN data/maps/Route18_EastEntrance_1F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route18_EastEntrance_1F/map.json
@

	.align 2

Route18_EastEntrance_1F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_POLICEMAN, 6, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, Route18_EastEntrance_1F_EventScript_Guard, 0

Route18_EastEntrance_1F_MapWarps:
	warp_def 1, 6, 3, 0, MAP_ROUTE18
	warp_def 11, 6, 3, 1, MAP_ROUTE18
	warp_def 9, 10, 3, 0, MAP_ROUTE18_EAST_ENTRANCE_2F

Route18_EastEntrance_1F_MapCoordEvents:
	coord_event 2, 6, 3, VAR_MAP_SCENE_ROUTE16, 0, EventScript_SetEnteringCyclingRoad
	coord_event 6, 4, 3, VAR_TEMP_1, 0, Route18_EastEntrance_1F_EventScript_NeedBikeTriggerTop
	coord_event 6, 5, 3, VAR_TEMP_1, 0, Route18_EastEntrance_1F_EventScript_NeedBikeTriggerMidTop
	coord_event 6, 6, 3, VAR_TEMP_1, 0, Route18_EastEntrance_1F_EventScript_NeedBikeTriggerMid
	coord_event 6, 7, 3, VAR_TEMP_1, 0, Route18_EastEntrance_1F_EventScript_NeedBikeTriggerMidBottom
	coord_event 6, 8, 3, VAR_TEMP_1, 0, Route18_EastEntrance_1F_EventScript_NeedBikeTriggerBottom
	coord_event 10, 6, 3, VAR_MAP_SCENE_ROUTE16, 1, EventScript_SetExitingCyclingRoad
	coord_event 11, 5, 3, VAR_MAP_SCENE_ROUTE16, 1, EventScript_SetExitingCyclingRoad
	coord_event 11, 7, 3, VAR_MAP_SCENE_ROUTE16, 1, EventScript_SetExitingCyclingRoad
	coord_event 1, 5, 3, VAR_MAP_SCENE_ROUTE16, 0, EventScript_SetEnteringCyclingRoad
	coord_event 1, 7, 3, VAR_MAP_SCENE_ROUTE16, 0, EventScript_SetEnteringCyclingRoad

Route18_EastEntrance_1F_MapEvents::
	map_events Route18_EastEntrance_1F_ObjectEvents, Route18_EastEntrance_1F_MapWarps, Route18_EastEntrance_1F_MapCoordEvents, NULL

@ ===== END data/maps/Route18_EastEntrance_1F/events.inc =====
@ ===== BEGIN data/maps/Route18_EastEntrance_2F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route18_EastEntrance_2F/map.json
@

	.align 2

Route18_EastEntrance_2F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_BOY, 5, 3, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NONE, 0, Route18_EastEntrance_2F_EventScript_Haden, 0

Route18_EastEntrance_2F_MapWarps:
	warp_def 10, 9, 3, 2, MAP_ROUTE18_EAST_ENTRANCE_1F

Route18_EastEntrance_2F_MapBGEvents:
	bg_sign_event 4, 1, 0, BG_EVENT_PLAYER_FACING_ANY, Route18_EastEntrance_2F_EventScript_LeftBinoculars
	bg_sign_event 8, 1, 0, BG_EVENT_PLAYER_FACING_ANY, Route18_EastEntrance_2F_EventScript_RightBinoculars

Route18_EastEntrance_2F_MapEvents::
	map_events Route18_EastEntrance_2F_ObjectEvents, Route18_EastEntrance_2F_MapWarps, NULL, Route18_EastEntrance_2F_MapBGEvents

@ ===== END data/maps/Route18_EastEntrance_2F/events.inc =====
@ ===== BEGIN data/maps/Route19_UnusedHouse/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route19_UnusedHouse/map.json
@

	.align 2

Route19_UnusedHouse_MapEvents::
	map_events NULL, NULL, NULL, NULL

@ ===== END data/maps/Route19_UnusedHouse/events.inc =====
@ ===== BEGIN data/maps/Route22_NorthEntrance/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route22_NorthEntrance/map.json
@

	.align 2

Route22_NorthEntrance_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_POLICEMAN, 8, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, Route22_NorthEntrance_EventScript_BoulderBadgeGuard, 0

Route22_NorthEntrance_MapWarps:
	warp_def 7, 1, 3, 2, MAP_ROUTE23
	warp_def 6, 10, 3, 0, MAP_ROUTE22
	warp_def 7, 10, 3, 0, MAP_ROUTE22
	warp_def 8, 10, 3, 0, MAP_ROUTE22

Route22_NorthEntrance_MapCoordEvents:
	coord_event 7, 2, 3, VAR_MAP_SCENE_ROUTE23, 0, Route22_NorthEntrance_EventScript_BoulderBadgeGuardTrigger

Route22_NorthEntrance_MapEvents::
	map_events Route22_NorthEntrance_ObjectEvents, Route22_NorthEntrance_MapWarps, Route22_NorthEntrance_MapCoordEvents, NULL

@ ===== END data/maps/Route22_NorthEntrance/events.inc =====
@ ===== BEGIN data/maps/Route23_UnusedHouse/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route23_UnusedHouse/map.json
@

	.align 2

Route23_UnusedHouse_MapEvents::
	map_events NULL, NULL, NULL, NULL

@ ===== END data/maps/Route23_UnusedHouse/events.inc =====
@ ===== BEGIN data/maps/Route25_SeaCottage/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route25_SeaCottage/map.json
@

	.align 2

Route25_SeaCottage_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_BILL, 7, 5, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, Route25_SeaCottage_EventScript_Bill, FLAG_HIDE_BILL_HUMAN_SEA_COTTAGE
	object_event 2, OBJ_EVENT_GFX_CLEFAIRY, 10, 6, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, Route25_SeaCottage_EventScript_Bill, FLAG_HIDE_BILL_CLEFAIRY

Route25_SeaCottage_MapWarps:
	warp_def 6, 9, 3, 0, MAP_ROUTE25
	warp_def 7, 9, 3, 0, MAP_ROUTE25
	warp_def 8, 9, 3, 0, MAP_ROUTE25

Route25_SeaCottage_MapBGEvents:
	bg_sign_event 4, 5, 0, BG_EVENT_PLAYER_FACING_NORTH, Route25_SeaCottage_EventScript_Computer

Route25_SeaCottage_MapEvents::
	map_events Route25_SeaCottage_ObjectEvents, Route25_SeaCottage_MapWarps, NULL, Route25_SeaCottage_MapBGEvents

@ ===== END data/maps/Route25_SeaCottage/events.inc =====
@ ===== BEGIN data/maps/SevenIsland_House_Room1/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SevenIsland_House_Room1/map.json
@

	.align 2

SevenIsland_House_Room1_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_OLD_WOMAN, 4, 4, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, SevenIsland_House_Room1_EventScript_OldWoman, 0

SevenIsland_House_Room1_MapWarps:
	warp_def 4, 7, 3, 0, MAP_SEVEN_ISLAND
	warp_def 4, 1, 0, 0, MAP_SEVEN_ISLAND_HOUSE_ROOM2

SevenIsland_House_Room1_MapBGEvents:
	bg_sign_event 4, 1, 0, BG_EVENT_PLAYER_FACING_ANY, SevenIsland_House_Room1_EventScript_Box

SevenIsland_House_Room1_MapEvents::
	map_events SevenIsland_House_Room1_ObjectEvents, SevenIsland_House_Room1_MapWarps, NULL, SevenIsland_House_Room1_MapBGEvents

@ ===== END data/maps/SevenIsland_House_Room1/events.inc =====
@ ===== BEGIN data/maps/SevenIsland_House_Room2/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SevenIsland_House_Room2/map.json
@

	.align 2

SevenIsland_House_Room2_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_VAR_0, 6, 5, 0, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NONE, 0, 0x0, 0

SevenIsland_House_Room2_MapWarps:
	warp_def 3, 1, 0, 1, MAP_SEVEN_ISLAND_HOUSE_ROOM1

SevenIsland_House_Room2_MapEvents::
	map_events SevenIsland_House_Room2_ObjectEvents, SevenIsland_House_Room2_MapWarps, NULL, NULL

@ ===== END data/maps/SevenIsland_House_Room2/events.inc =====
@ ===== BEGIN data/maps/SevenIsland_Mart/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SevenIsland_Mart/map.json
@

	.align 2

SevenIsland_Mart_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_CLERK, 2, 3, 0, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, SevenIsland_Mart_EventScript_Clerk, 0
	object_event 2, OBJ_EVENT_GFX_LASS, 6, 2, 3, MOVEMENT_TYPE_FACE_UP_AND_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, SevenIsland_Mart_EventScript_Lass, 0
	object_event 3, OBJ_EVENT_GFX_FISHER, 9, 5, 3, MOVEMENT_TYPE_WANDER_UP_AND_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SevenIsland_Mart_EventScript_Fisher, 0
	object_event 4, OBJ_EVENT_GFX_HIKER, 5, 4, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SevenIsland_Mart_EventScript_Hiker, 0

SevenIsland_Mart_MapWarps:
	warp_def 4, 7, 3, 1, MAP_SEVEN_ISLAND

SevenIsland_Mart_MapEvents::
	map_events SevenIsland_Mart_ObjectEvents, SevenIsland_Mart_MapWarps, NULL, NULL

@ ===== END data/maps/SevenIsland_Mart/events.inc =====
@ ===== BEGIN data/maps/SevenIsland_PokemonCenter_1F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SevenIsland_PokemonCenter_1F/map.json
@

	.align 2

SevenIsland_PokemonCenter_1F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_NURSE, 7, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SevenIsland_PokemonCenter_1F_EventScript_Nurse, 0
	object_event 2, OBJ_EVENT_GFX_OLD_MAN_1, 11, 5, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SevenIsland_PokemonCenter_1F_EventScript_OldMan, 0
	object_event 3, OBJ_EVENT_GFX_SAILOR, 14, 6, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NONE, 0, SevenIsland_PokemonCenter_1F_EventScript_Sailor, 0
	object_event 4, OBJ_EVENT_GFX_BEAUTY, 4, 4, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, SevenIsland_PokemonCenter_1F_EventScript_Beauty, 0
	object_event 5, 0, 3, 1, 0, MOVEMENT_TYPE_INVISIBLE, 1, 1, TRAINER_TYPE_NONE, 0, SevenIsland_PokemonCenter_1F_EventScript_PokemonJournal, FLAG_HIDE_POSTGAME_GOSSIPERS
	object_event 6, 0, 2, 1, 0, MOVEMENT_TYPE_INVISIBLE, 1, 1, TRAINER_TYPE_NONE, 0, SevenIsland_PokemonCenter_1F_EventScript_PokemonJournal, FLAG_HIDE_POSTGAME_GOSSIPERS

SevenIsland_PokemonCenter_1F_MapWarps:
	warp_def 7, 8, 3, 2, MAP_SEVEN_ISLAND
	warp_def 1, 6, 4, 0, MAP_SEVEN_ISLAND_POKEMON_CENTER_2F

SevenIsland_PokemonCenter_1F_MapEvents::
	map_events SevenIsland_PokemonCenter_1F_ObjectEvents, SevenIsland_PokemonCenter_1F_MapWarps, NULL, NULL

@ ===== END data/maps/SevenIsland_PokemonCenter_1F/events.inc =====
@ ===== BEGIN data/maps/SevenIsland_PokemonCenter_2F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SevenIsland_PokemonCenter_2F/map.json
@

	.align 2

SevenIsland_PokemonCenter_2F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_CABLE_CLUB_RECEPTIONIST, 6, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 0, 0, TRAINER_TYPE_NONE, 0, Common_EventScript_UnionRoomAttendant, 0
	object_event 2, OBJ_EVENT_GFX_CABLE_CLUB_RECEPTIONIST, 2, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 0, 0, TRAINER_TYPE_NONE, 0, Common_EventScript_WirelessClubAttendant, 0
	object_event 3, OBJ_EVENT_GFX_CABLE_CLUB_RECEPTIONIST, 10, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 0, 0, TRAINER_TYPE_NONE, 0, Common_EventScript_DirectCornerAttendant, 0
	object_event 4, OBJ_EVENT_GFX_MG_DELIVERYMAN, 1, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, CableClub_EventScript_MysteryGiftMan, FLAG_HIDE_MG_DELIVERYMEN

SevenIsland_PokemonCenter_2F_MapWarps:
	warp_def 1, 6, 4, 1, MAP_SEVEN_ISLAND_POKEMON_CENTER_1F
	warp_def 5, 1, 0, 0, MAP_UNION_ROOM
	warp_def 9, 1, 0, 0, MAP_TRADE_CENTER

SevenIsland_PokemonCenter_2F_MapEvents::
	map_events SevenIsland_PokemonCenter_2F_ObjectEvents, SevenIsland_PokemonCenter_2F_MapWarps, NULL, NULL

@ ===== END data/maps/SevenIsland_PokemonCenter_2F/events.inc =====
@ ===== BEGIN data/maps/SevenIsland_UnusedHouse/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SevenIsland_UnusedHouse/map.json
@

	.align 2

SevenIsland_UnusedHouse_MapEvents::
	map_events NULL, NULL, NULL, NULL

@ ===== END data/maps/SevenIsland_UnusedHouse/events.inc =====
@ ===== BEGIN data/maps/SevenIsland_Harbor/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SevenIsland_Harbor/map.json
@

	.align 2

SevenIsland_Harbor_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_SEAGALLOP, 8, 9, 0, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, 0x0, 0
	object_event 2, OBJ_EVENT_GFX_SAILOR, 8, 6, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NONE, 0, SevenIsland_Harbor_EventScript_Sailor, 0

SevenIsland_Harbor_MapWarps:
	warp_def 8, 2, 3, 3, MAP_SEVEN_ISLAND

SevenIsland_Harbor_MapEvents::
	map_events SevenIsland_Harbor_ObjectEvents, SevenIsland_Harbor_MapWarps, NULL, NULL

@ ===== END data/maps/SevenIsland_Harbor/events.inc =====
@ ===== BEGIN data/maps/OneIsland_PokemonCenter_1F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/OneIsland_PokemonCenter_1F/map.json
@

	.align 2

OneIsland_PokemonCenter_1F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_NURSE, 5, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, OneIsland_PokemonCenter_1F_EventScript_Nurse, 0
	object_event 2, OBJ_EVENT_GFX_BILL, 14, 6, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NONE, 0, OneIsland_PokemonCenter_1F_EventScript_Bill, FLAG_HIDE_ONE_ISLAND_POKECENTER_BILL
	object_event 3, OBJ_EVENT_GFX_CELIO, 15, 6, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NONE, 0, OneIsland_PokemonCenter_1F_EventScript_Celio, FLAG_HIDE_ONE_ISLAND_POKECENTER_CELIO
	object_event 4, OBJ_EVENT_GFX_LITTLE_BOY, 6, 8, 3, MOVEMENT_TYPE_WANDER_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, OneIsland_PokemonCenter_1F_EventScript_LittleBoy, 0
	object_event 5, OBJ_EVENT_GFX_HIKER, 3, 7, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, OneIsland_PokemonCenter_1F_EventScript_Hiker, 0
	object_event 6, OBJ_EVENT_GFX_CRUSH_GIRL, 7, 4, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, OneIsland_PokemonCenter_1F_EventScript_CrushGirl, 0

OneIsland_PokemonCenter_1F_MapWarps:
	warp_def 9, 9, 3, 0, MAP_ONE_ISLAND
	warp_def 1, 5, 4, 0, MAP_ONE_ISLAND_POKEMON_CENTER_2F

OneIsland_PokemonCenter_1F_MapCoordEvents:
	coord_event 12, 6, 3, VAR_MAP_SCENE_ONE_ISLAND_POKEMON_CENTER_1F, 2, OneIsland_PokemonCenter_1F_EventScript_LeaveOneIslandTriggerTop
	coord_event 12, 7, 3, VAR_MAP_SCENE_ONE_ISLAND_POKEMON_CENTER_1F, 2, OneIsland_PokemonCenter_1F_EventScript_LeaveOneIslandTriggerMidTop
	coord_event 12, 8, 3, VAR_MAP_SCENE_ONE_ISLAND_POKEMON_CENTER_1F, 2, OneIsland_PokemonCenter_1F_EventScript_LeaveOneIslandTriggerMidBottom
	coord_event 12, 9, 3, VAR_MAP_SCENE_ONE_ISLAND_POKEMON_CENTER_1F, 2, OneIsland_PokemonCenter_1F_EventScript_LeaveOneIslandTriggerBottom

OneIsland_PokemonCenter_1F_MapBGEvents:
	bg_sign_event 12, 2, 0, BG_EVENT_PLAYER_FACING_ANY, OneIsland_PokemonCenter_1F_EventScript_NetworkMachine
	bg_sign_event 12, 3, 0, BG_EVENT_PLAYER_FACING_ANY, OneIsland_PokemonCenter_1F_EventScript_NetworkMachine
	bg_sign_event 12, 4, 0, BG_EVENT_PLAYER_FACING_ANY, OneIsland_PokemonCenter_1F_EventScript_NetworkMachine
	bg_sign_event 12, 5, 0, BG_EVENT_PLAYER_FACING_ANY, OneIsland_PokemonCenter_1F_EventScript_NetworkMachine
	bg_sign_event 13, 5, 0, BG_EVENT_PLAYER_FACING_ANY, OneIsland_PokemonCenter_1F_EventScript_NetworkMachine
	bg_sign_event 15, 5, 0, BG_EVENT_PLAYER_FACING_ANY, OneIsland_PokemonCenter_1F_EventScript_NetworkMachine
	bg_sign_event 14, 5, 0, BG_EVENT_PLAYER_FACING_ANY, OneIsland_PokemonCenter_1F_EventScript_NetworkMachine
	bg_sign_event 16, 5, 0, BG_EVENT_PLAYER_FACING_ANY, OneIsland_PokemonCenter_1F_EventScript_NetworkMachine
	bg_sign_event 17, 5, 0, BG_EVENT_PLAYER_FACING_ANY, OneIsland_PokemonCenter_1F_EventScript_NetworkMachine

OneIsland_PokemonCenter_1F_MapEvents::
	map_events OneIsland_PokemonCenter_1F_ObjectEvents, OneIsland_PokemonCenter_1F_MapWarps, OneIsland_PokemonCenter_1F_MapCoordEvents, OneIsland_PokemonCenter_1F_MapBGEvents

@ ===== END data/maps/OneIsland_PokemonCenter_1F/events.inc =====
@ ===== BEGIN data/maps/OneIsland_PokemonCenter_2F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/OneIsland_PokemonCenter_2F/map.json
@

	.align 2

OneIsland_PokemonCenter_2F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_CABLE_CLUB_RECEPTIONIST, 6, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 0, 0, TRAINER_TYPE_NONE, 0, Common_EventScript_UnionRoomAttendant, 0
	object_event 2, OBJ_EVENT_GFX_CABLE_CLUB_RECEPTIONIST, 2, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 0, 0, TRAINER_TYPE_NONE, 0, Common_EventScript_WirelessClubAttendant, 0
	object_event 3, OBJ_EVENT_GFX_CABLE_CLUB_RECEPTIONIST, 10, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 0, 0, TRAINER_TYPE_NONE, 0, Common_EventScript_DirectCornerAttendant, 0
	object_event 4, OBJ_EVENT_GFX_MG_DELIVERYMAN, 1, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, CableClub_EventScript_MysteryGiftMan, FLAG_HIDE_MG_DELIVERYMEN

OneIsland_PokemonCenter_2F_MapWarps:
	warp_def 1, 6, 4, 1, MAP_ONE_ISLAND_POKEMON_CENTER_1F
	warp_def 5, 1, 0, 0, MAP_UNION_ROOM
	warp_def 9, 1, 0, 0, MAP_TRADE_CENTER

OneIsland_PokemonCenter_2F_MapEvents::
	map_events OneIsland_PokemonCenter_2F_ObjectEvents, OneIsland_PokemonCenter_2F_MapWarps, NULL, NULL

@ ===== END data/maps/OneIsland_PokemonCenter_2F/events.inc =====
@ ===== BEGIN data/maps/OneIsland_House1/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/OneIsland_House1/map.json
@

	.align 2

OneIsland_House1_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_OLD_MAN_1, 4, 5, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, OneIsland_House1_EventScript_OldMan, 0
	object_event 2, OBJ_EVENT_GFX_OLD_WOMAN, 7, 5, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NONE, 0, OneIsland_House1_EventScript_OldWoman, 0

OneIsland_House1_MapWarps:
	warp_def 4, 7, 3, 1, MAP_ONE_ISLAND

OneIsland_House1_MapEvents::
	map_events OneIsland_House1_ObjectEvents, OneIsland_House1_MapWarps, NULL, NULL

@ ===== END data/maps/OneIsland_House1/events.inc =====
@ ===== BEGIN data/maps/OneIsland_House2/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/OneIsland_House2/map.json
@

	.align 2

OneIsland_House2_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_LASS, 9, 4, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, OneIsland_House2_EventScript_Lass, 0

OneIsland_House2_MapWarps:
	warp_def 4, 7, 3, 2, MAP_ONE_ISLAND

OneIsland_House2_MapEvents::
	map_events OneIsland_House2_ObjectEvents, OneIsland_House2_MapWarps, NULL, NULL

@ ===== END data/maps/OneIsland_House2/events.inc =====
@ ===== BEGIN data/maps/OneIsland_Harbor/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/OneIsland_Harbor/map.json
@

	.align 2

OneIsland_Harbor_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_SEAGALLOP, 8, 9, 0, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, 0x0, 0
	object_event 2, OBJ_EVENT_GFX_SAILOR, 8, 6, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NONE, 0, OneIsland_Harbor_EventScript_Sailor, 0

OneIsland_Harbor_MapWarps:
	warp_def 8, 2, 3, 3, MAP_ONE_ISLAND

OneIsland_Harbor_MapEvents::
	map_events OneIsland_Harbor_ObjectEvents, OneIsland_Harbor_MapWarps, NULL, NULL

@ ===== END data/maps/OneIsland_Harbor/events.inc =====
@ ===== BEGIN data/maps/TwoIsland_JoyfulGameCorner/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/TwoIsland_JoyfulGameCorner/map.json
@

	.align 2

TwoIsland_JoyfulGameCorner_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_BALDING_MAN, 5, 5, 1, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, TwoIsland_JoyfulGameCorner_EventScript_LostellesDaddy, 0
	object_event 2, OBJ_EVENT_GFX_BIKER, 5, 8, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NONE, 0, 0x0, FLAG_HIDE_TWO_ISLAND_GAME_CORNER_BIKER
	object_event 3, OBJ_EVENT_GFX_LITTLE_GIRL, 6, 5, 1, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NONE, 0, TwoIsland_JoyfulGameCorner_EventScript_Lostelle, FLAG_HIDE_TWO_ISLAND_GAME_CORNER_LOSTELLE
	object_event 4, OBJ_EVENT_GFX_MAN, 4, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, TwoIsland_JoyfulGameCorner_EventScript_InfoMan, 0

TwoIsland_JoyfulGameCorner_MapWarps:
	warp_def 5, 8, 3, 0, MAP_TWO_ISLAND

TwoIsland_JoyfulGameCorner_MapBGEvents:
	bg_sign_event 1, 1, 0, BG_EVENT_PLAYER_FACING_ANY, TwoIsland_JoyfulGameCorner_EventScript_ShowPokemonJumpRecords
	bg_sign_event 0, 1, 0, BG_EVENT_PLAYER_FACING_ANY, TwoIsland_JoyfulGameCorner_EventScript_ShowDodrioBerryPickingRecords

TwoIsland_JoyfulGameCorner_MapEvents::
	map_events TwoIsland_JoyfulGameCorner_ObjectEvents, TwoIsland_JoyfulGameCorner_MapWarps, NULL, TwoIsland_JoyfulGameCorner_MapBGEvents

@ ===== END data/maps/TwoIsland_JoyfulGameCorner/events.inc =====
@ ===== BEGIN data/maps/TwoIsland_House/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/TwoIsland_House/map.json
@

	.align 2

TwoIsland_House_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_FAT_MAN, 7, 5, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, TwoIsland_House_EventScript_MoveManiac, 0

TwoIsland_House_MapWarps:
	warp_def 4, 7, 3, 1, MAP_TWO_ISLAND

TwoIsland_House_MapEvents::
	map_events TwoIsland_House_ObjectEvents, TwoIsland_House_MapWarps, NULL, NULL

@ ===== END data/maps/TwoIsland_House/events.inc =====
@ ===== BEGIN data/maps/TwoIsland_PokemonCenter_1F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/TwoIsland_PokemonCenter_1F/map.json
@

	.align 2

TwoIsland_PokemonCenter_1F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_NURSE, 7, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, TwoIsland_PokemonCenter_1F_EventScript_Nurse, 0
	object_event 2, OBJ_EVENT_GFX_GBA_KID, 11, 5, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, TwoIsland_PokemonCenter_1F_EventScript_GBAKid, 0
	object_event 3, OBJ_EVENT_GFX_BUG_CATCHER, 4, 4, 3, MOVEMENT_TYPE_WANDER_LEFT_AND_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, TwoIsland_PokemonCenter_1F_EventScript_BugCatcher, 0

TwoIsland_PokemonCenter_1F_MapWarps:
	warp_def 7, 8, 3, 2, MAP_TWO_ISLAND
	warp_def 1, 6, 4, 0, MAP_TWO_ISLAND_POKEMON_CENTER_2F

TwoIsland_PokemonCenter_1F_MapEvents::
	map_events TwoIsland_PokemonCenter_1F_ObjectEvents, TwoIsland_PokemonCenter_1F_MapWarps, NULL, NULL

@ ===== END data/maps/TwoIsland_PokemonCenter_1F/events.inc =====
@ ===== BEGIN data/maps/TwoIsland_PokemonCenter_2F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/TwoIsland_PokemonCenter_2F/map.json
@

	.align 2

TwoIsland_PokemonCenter_2F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_CABLE_CLUB_RECEPTIONIST, 6, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 0, 0, TRAINER_TYPE_NONE, 0, Common_EventScript_UnionRoomAttendant, 0
	object_event 2, OBJ_EVENT_GFX_CABLE_CLUB_RECEPTIONIST, 2, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 0, 0, TRAINER_TYPE_NONE, 0, Common_EventScript_WirelessClubAttendant, 0
	object_event 3, OBJ_EVENT_GFX_CABLE_CLUB_RECEPTIONIST, 10, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 0, 0, TRAINER_TYPE_NONE, 0, Common_EventScript_DirectCornerAttendant, 0
	object_event 4, OBJ_EVENT_GFX_MG_DELIVERYMAN, 1, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, CableClub_EventScript_MysteryGiftMan, FLAG_HIDE_MG_DELIVERYMEN

TwoIsland_PokemonCenter_2F_MapWarps:
	warp_def 1, 6, 4, 1, MAP_TWO_ISLAND_POKEMON_CENTER_1F
	warp_def 5, 1, 0, 0, MAP_UNION_ROOM
	warp_def 9, 1, 0, 0, MAP_TRADE_CENTER

TwoIsland_PokemonCenter_2F_MapEvents::
	map_events TwoIsland_PokemonCenter_2F_ObjectEvents, TwoIsland_PokemonCenter_2F_MapWarps, NULL, NULL

@ ===== END data/maps/TwoIsland_PokemonCenter_2F/events.inc =====
@ ===== BEGIN data/maps/TwoIsland_Harbor/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/TwoIsland_Harbor/map.json
@

	.align 2

TwoIsland_Harbor_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_SEAGALLOP, 8, 9, 0, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, 0x0, 0
	object_event 2, OBJ_EVENT_GFX_SAILOR, 8, 6, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NONE, 0, TwoIsland_Harbor_EventScript_Sailor, 0

TwoIsland_Harbor_MapWarps:
	warp_def 8, 2, 3, 3, MAP_TWO_ISLAND

TwoIsland_Harbor_MapEvents::
	map_events TwoIsland_Harbor_ObjectEvents, TwoIsland_Harbor_MapWarps, NULL, NULL

@ ===== END data/maps/TwoIsland_Harbor/events.inc =====
@ ===== BEGIN data/maps/ThreeIsland_House1/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/ThreeIsland_House1/map.json
@

	.align 2

ThreeIsland_House1_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_LITTLE_GIRL, 3, 4, 0, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, ThreeIsland_House1_EventScript_Lostelle, FLAG_HIDE_LOSTELLE_IN_HER_HOME

ThreeIsland_House1_MapWarps:
	warp_def 4, 7, 3, 0, MAP_THREE_ISLAND

ThreeIsland_House1_MapBGEvents:
	bg_sign_event 2, 1, 0, BG_EVENT_PLAYER_FACING_ANY, ThreeIsland_House1_EventScript_DisplayCase

ThreeIsland_House1_MapEvents::
	map_events ThreeIsland_House1_ObjectEvents, ThreeIsland_House1_MapWarps, NULL, ThreeIsland_House1_MapBGEvents

@ ===== END data/maps/ThreeIsland_House1/events.inc =====
@ ===== BEGIN data/maps/ThreeIsland_PokemonCenter_1F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/ThreeIsland_PokemonCenter_1F/map.json
@

	.align 2

ThreeIsland_PokemonCenter_1F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_NURSE, 7, 2, 0, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, ThreeIsland_PokemonCenter_1F_EventScript_Nurse, 0
	object_event 2, OBJ_EVENT_GFX_ROCKER, 12, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, ThreeIsland_PokemonCenter_1F_EventScript_Rocker, 0
	object_event 3, OBJ_EVENT_GFX_LASS, 3, 4, 3, MOVEMENT_TYPE_WANDER_LEFT_AND_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, ThreeIsland_PokemonCenter_1F_EventScript_Lass, 0
	object_event 4, OBJ_EVENT_GFX_SAILOR, 11, 5, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, ThreeIsland_PokemonCenter_1F_EventScript_Sailor, 0

ThreeIsland_PokemonCenter_1F_MapWarps:
	warp_def 7, 8, 3, 1, MAP_THREE_ISLAND
	warp_def 1, 6, 4, 0, MAP_THREE_ISLAND_POKEMON_CENTER_2F

ThreeIsland_PokemonCenter_1F_MapEvents::
	map_events ThreeIsland_PokemonCenter_1F_ObjectEvents, ThreeIsland_PokemonCenter_1F_MapWarps, NULL, NULL

@ ===== END data/maps/ThreeIsland_PokemonCenter_1F/events.inc =====
@ ===== BEGIN data/maps/ThreeIsland_PokemonCenter_2F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/ThreeIsland_PokemonCenter_2F/map.json
@

	.align 2

ThreeIsland_PokemonCenter_2F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_CABLE_CLUB_RECEPTIONIST, 6, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 0, 0, TRAINER_TYPE_NONE, 0, Common_EventScript_UnionRoomAttendant, 0
	object_event 2, OBJ_EVENT_GFX_CABLE_CLUB_RECEPTIONIST, 2, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 0, 0, TRAINER_TYPE_NONE, 0, Common_EventScript_WirelessClubAttendant, 0
	object_event 3, OBJ_EVENT_GFX_CABLE_CLUB_RECEPTIONIST, 10, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 0, 0, TRAINER_TYPE_NONE, 0, Common_EventScript_DirectCornerAttendant, 0
	object_event 4, OBJ_EVENT_GFX_MG_DELIVERYMAN, 1, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, CableClub_EventScript_MysteryGiftMan, FLAG_HIDE_MG_DELIVERYMEN

ThreeIsland_PokemonCenter_2F_MapWarps:
	warp_def 1, 6, 4, 1, MAP_THREE_ISLAND_POKEMON_CENTER_1F
	warp_def 5, 1, 0, 0, MAP_UNION_ROOM
	warp_def 9, 1, 0, 0, MAP_TRADE_CENTER

ThreeIsland_PokemonCenter_2F_MapEvents::
	map_events ThreeIsland_PokemonCenter_2F_ObjectEvents, ThreeIsland_PokemonCenter_2F_MapWarps, NULL, NULL

@ ===== END data/maps/ThreeIsland_PokemonCenter_2F/events.inc =====
@ ===== BEGIN data/maps/ThreeIsland_Mart/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/ThreeIsland_Mart/map.json
@

	.align 2

ThreeIsland_Mart_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_CLERK, 2, 3, 0, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, ThreeIsland_Mart_EventScript_Clerk, 0
	object_event 2, OBJ_EVENT_GFX_PICNICKER, 2, 7, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NONE, 0, ThreeIsland_Mart_EventScript_Picnicker, 0
	object_event 3, OBJ_EVENT_GFX_BUG_CATCHER, 7, 2, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NONE, 0, ThreeIsland_Mart_EventScript_BugCatcher, 0
	object_event 4, OBJ_EVENT_GFX_YOUNGSTER, 6, 5, 3, MOVEMENT_TYPE_WANDER_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, ThreeIsland_Mart_EventScript_Youngster, 0

ThreeIsland_Mart_MapWarps:
	warp_def 4, 7, 3, 2, MAP_THREE_ISLAND

ThreeIsland_Mart_MapEvents::
	map_events ThreeIsland_Mart_ObjectEvents, ThreeIsland_Mart_MapWarps, NULL, NULL

@ ===== END data/maps/ThreeIsland_Mart/events.inc =====
@ ===== BEGIN data/maps/ThreeIsland_House2/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/ThreeIsland_House2/map.json
@

	.align 2

ThreeIsland_House2_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_ROCKER, 4, 4, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, ThreeIsland_House2_EventScript_Rocker, 0
	object_event 2, OBJ_EVENT_GFX_MAN, 7, 4, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NONE, 0, ThreeIsland_House2_EventScript_Man, 0

ThreeIsland_House2_MapWarps:
	warp_def 4, 7, 3, 3, MAP_THREE_ISLAND

ThreeIsland_House2_MapEvents::
	map_events ThreeIsland_House2_ObjectEvents, ThreeIsland_House2_MapWarps, NULL, NULL

@ ===== END data/maps/ThreeIsland_House2/events.inc =====
@ ===== BEGIN data/maps/ThreeIsland_House3/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/ThreeIsland_House3/map.json
@

	.align 2

ThreeIsland_House3_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_BEAUTY, 8, 2, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NONE, 0, ThreeIsland_House3_EventScript_Beauty, 0

ThreeIsland_House3_MapWarps:
	warp_def 4, 7, 3, 4, MAP_THREE_ISLAND

ThreeIsland_House3_MapEvents::
	map_events ThreeIsland_House3_ObjectEvents, ThreeIsland_House3_MapWarps, NULL, NULL

@ ===== END data/maps/ThreeIsland_House3/events.inc =====
@ ===== BEGIN data/maps/ThreeIsland_House4/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/ThreeIsland_House4/map.json
@

	.align 2

ThreeIsland_House4_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_BALDING_MAN, 7, 4, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NONE, 0, ThreeIsland_House4_EventScript_BaldingMan, 0
	object_event 2, OBJ_EVENT_GFX_LITTLE_BOY, 6, 3, 3, MOVEMENT_TYPE_WANDER_AROUND, 2, 1, TRAINER_TYPE_NONE, 0, ThreeIsland_House4_EventScript_LittleBoy, 0

ThreeIsland_House4_MapWarps:
	warp_def 4, 7, 3, 5, MAP_THREE_ISLAND

ThreeIsland_House4_MapEvents::
	map_events ThreeIsland_House4_ObjectEvents, ThreeIsland_House4_MapWarps, NULL, NULL

@ ===== END data/maps/ThreeIsland_House4/events.inc =====
@ ===== BEGIN data/maps/ThreeIsland_House5/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/ThreeIsland_House5/map.json
@

	.align 2

ThreeIsland_House5_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_LITTLE_GIRL, 2, 5, 3, MOVEMENT_TYPE_WANDER_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, ThreeIsland_House5_EventScript_LittleGirl, 0

ThreeIsland_House5_MapWarps:
	warp_def 4, 7, 3, 6, MAP_THREE_ISLAND

ThreeIsland_House5_MapEvents::
	map_events ThreeIsland_House5_ObjectEvents, ThreeIsland_House5_MapWarps, NULL, NULL

@ ===== END data/maps/ThreeIsland_House5/events.inc =====
@ ===== BEGIN data/maps/FourIsland_PokemonDayCare/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FourIsland_PokemonDayCare/map.json
@

	.align 2

FourIsland_PokemonDayCare_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_OLD_WOMAN, 2, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, FourIsland_PokemonDayCare_EventScript_DaycareWoman, 0

FourIsland_PokemonDayCare_MapWarps:
	warp_def 4, 7, 3, 1, MAP_FOUR_ISLAND

FourIsland_PokemonDayCare_MapEvents::
	map_events FourIsland_PokemonDayCare_ObjectEvents, FourIsland_PokemonDayCare_MapWarps, NULL, NULL

@ ===== END data/maps/FourIsland_PokemonDayCare/events.inc =====
@ ===== BEGIN data/maps/FourIsland_PokemonCenter_1F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FourIsland_PokemonCenter_1F/map.json
@

	.align 2

FourIsland_PokemonCenter_1F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_NURSE, 7, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, FourIsland_PokemonCenter_1F_EventScript_Nurse, 0
	object_event 2, OBJ_EVENT_GFX_MAN, 10, 6, 3, MOVEMENT_TYPE_WANDER_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, FourIsland_PokemonCenter_1F_EventScript_Man, 0
	object_event 3, OBJ_EVENT_GFX_WOMAN_3, 5, 5, 3, MOVEMENT_TYPE_FACE_DOWN_AND_UP, 1, 1, TRAINER_TYPE_NONE, 0, FourIsland_PokemonCenter_1F_EventScript_Woman, 0
	object_event 4, OBJ_EVENT_GFX_GENTLEMAN, 2, 2, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NONE, 0, FourIsland_PokemonCenter_1F_EventScript_Gentleman, 0

FourIsland_PokemonCenter_1F_MapWarps:
	warp_def 7, 8, 3, 0, MAP_FOUR_ISLAND
	warp_def 1, 6, 4, 0, MAP_FOUR_ISLAND_POKEMON_CENTER_2F

FourIsland_PokemonCenter_1F_MapBGEvents:
	bg_sign_event 3, 1, 0, BG_EVENT_PLAYER_FACING_NORTH, FourIsland_PokemonCenter_1F_EventScript_PokemonJournal
	bg_sign_event 2, 1, 0, BG_EVENT_PLAYER_FACING_NORTH, FourIsland_PokemonCenter_1F_EventScript_PokemonJournal

FourIsland_PokemonCenter_1F_MapEvents::
	map_events FourIsland_PokemonCenter_1F_ObjectEvents, FourIsland_PokemonCenter_1F_MapWarps, NULL, FourIsland_PokemonCenter_1F_MapBGEvents

@ ===== END data/maps/FourIsland_PokemonCenter_1F/events.inc =====
@ ===== BEGIN data/maps/FourIsland_PokemonCenter_2F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FourIsland_PokemonCenter_2F/map.json
@

	.align 2

FourIsland_PokemonCenter_2F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_CABLE_CLUB_RECEPTIONIST, 6, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 0, 0, TRAINER_TYPE_NONE, 0, Common_EventScript_UnionRoomAttendant, 0
	object_event 2, OBJ_EVENT_GFX_CABLE_CLUB_RECEPTIONIST, 2, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 0, 0, TRAINER_TYPE_NONE, 0, Common_EventScript_WirelessClubAttendant, 0
	object_event 3, OBJ_EVENT_GFX_CABLE_CLUB_RECEPTIONIST, 10, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 0, 0, TRAINER_TYPE_NONE, 0, Common_EventScript_DirectCornerAttendant, 0
	object_event 4, OBJ_EVENT_GFX_MG_DELIVERYMAN, 1, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, CableClub_EventScript_MysteryGiftMan, FLAG_HIDE_MG_DELIVERYMEN

FourIsland_PokemonCenter_2F_MapWarps:
	warp_def 1, 6, 4, 1, MAP_FOUR_ISLAND_POKEMON_CENTER_1F
	warp_def 5, 1, 0, 0, MAP_UNION_ROOM
	warp_def 9, 1, 0, 0, MAP_TRADE_CENTER

FourIsland_PokemonCenter_2F_MapEvents::
	map_events FourIsland_PokemonCenter_2F_ObjectEvents, FourIsland_PokemonCenter_2F_MapWarps, NULL, NULL

@ ===== END data/maps/FourIsland_PokemonCenter_2F/events.inc =====
@ ===== BEGIN data/maps/FourIsland_House1/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FourIsland_House1/map.json
@

	.align 2

FourIsland_House1_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_FAT_MAN, 8, 3, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, FourIsland_House1_EventScript_BodySlamTutor, 0
	object_event 2, OBJ_EVENT_GFX_FAT_MAN, 9, 3, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NONE, 0, FourIsland_House1_EventScript_FatMan, 0

FourIsland_House1_MapWarps:
	warp_def 4, 7, 3, 2, MAP_FOUR_ISLAND

FourIsland_House1_MapEvents::
	map_events FourIsland_House1_ObjectEvents, FourIsland_House1_MapWarps, NULL, NULL

@ ===== END data/maps/FourIsland_House1/events.inc =====
@ ===== BEGIN data/maps/FourIsland_LoreleisHouse/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FourIsland_LoreleisHouse/map.json
@

	.align 2

FourIsland_LoreleisHouse_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_LORELEI, 7, 4, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NONE, 0, FourIsland_LoreleisHouse_EventScript_Lorelei, FLAG_HIDE_LORELEI_IN_HER_HOUSE
	object_event 2, OBJ_EVENT_GFX_WIGGLYTUFF, 0, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, FourIsland_LoreleisHouse_EventScript_Doll, 0
	object_event 3, OBJ_EVENT_GFX_SEEL, 10, 3, 0, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, FourIsland_LoreleisHouse_EventScript_Doll, 0
	object_event 4, OBJ_EVENT_GFX_PIKACHU, 9, 3, 0, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, FourIsland_LoreleisHouse_EventScript_Doll, 0
	object_event 5, OBJ_EVENT_GFX_SLOWPOKE, 7, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, FourIsland_LoreleisHouse_EventScript_Doll, 0
	object_event 6, OBJ_EVENT_GFX_SLOWBRO, 6, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, FourIsland_LoreleisHouse_EventScript_Doll, 0
	object_event 7, OBJ_EVENT_GFX_PSYDUCK, 6, 4, 0, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, FourIsland_LoreleisHouse_EventScript_Doll, 0
	object_event 8, OBJ_EVENT_GFX_MEOWTH, 9, 4, 0, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, FourIsland_LoreleisHouse_EventScript_Doll, FLAG_HIDE_LORELEI_HOUSE_MEOWTH_DOLL
	object_event 9, OBJ_EVENT_GFX_CHANSEY, 10, 4, 0, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, FourIsland_LoreleisHouse_EventScript_Doll, FLAG_HIDE_LORELEI_HOUSE_CHANSEY_DOLL
	object_event 10, OBJ_EVENT_GFX_JIGGLYPUFF, 0, 3, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, FourIsland_LoreleisHouse_EventScript_Doll, FLAG_HIDE_LORELEI_HOUSE_JIGGLYPUFF_DOLL
	object_event 11, OBJ_EVENT_GFX_NIDORAN_F, 0, 5, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, FourIsland_LoreleisHouse_EventScript_Doll, FLAG_HIDE_LORELEIS_HOUSE_NIDORAN_F_DOLL
	object_event 12, OBJ_EVENT_GFX_NIDORAN_M, 1, 5, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, FourIsland_LoreleisHouse_EventScript_Doll, FLAG_HIDE_LORELEIS_HOUSE_NIDORAN_M_DOLL
	object_event 13, OBJ_EVENT_GFX_PIDGEOT, 9, 0, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, FourIsland_LoreleisHouse_EventScript_Doll, FLAG_HIDE_LORELEIS_HOUSE_PIDGEOT_DOLL
	object_event 14, OBJ_EVENT_GFX_FEAROW, 10, 0, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, FourIsland_LoreleisHouse_EventScript_Doll, FLAG_HIDE_LORELEIS_HOUSE_FEAROW_DOLL
	object_event 15, OBJ_EVENT_GFX_LAPRAS_DOLL, 9, 6, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, FourIsland_LoreleisHouse_EventScript_Doll, FLAG_HIDE_LORELEIS_HOUSE_LAPRAS_DOLL

FourIsland_LoreleisHouse_MapWarps:
	warp_def 4, 7, 3, 4, MAP_FOUR_ISLAND

FourIsland_LoreleisHouse_MapEvents::
	map_events FourIsland_LoreleisHouse_ObjectEvents, FourIsland_LoreleisHouse_MapWarps, NULL, NULL

@ ===== END data/maps/FourIsland_LoreleisHouse/events.inc =====
@ ===== BEGIN data/maps/FourIsland_Harbor/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FourIsland_Harbor/map.json
@

	.align 2

FourIsland_Harbor_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_SEAGALLOP, 8, 9, 0, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, 0x0, 0
	object_event 2, OBJ_EVENT_GFX_SAILOR, 8, 6, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NONE, 0, FourIsland_Harbor_EventScript_Sailor, 0

FourIsland_Harbor_MapWarps:
	warp_def 8, 2, 3, 6, MAP_FOUR_ISLAND

FourIsland_Harbor_MapEvents::
	map_events FourIsland_Harbor_ObjectEvents, FourIsland_Harbor_MapWarps, NULL, NULL

@ ===== END data/maps/FourIsland_Harbor/events.inc =====
@ ===== BEGIN data/maps/FourIsland_House2/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FourIsland_House2/map.json
@

	.align 2

FourIsland_House2_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_MAN, 4, 4, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, FourIsland_House2_EventScript_StickerMan, 0

FourIsland_House2_MapWarps:
	warp_def 4, 7, 3, 5, MAP_FOUR_ISLAND

FourIsland_House2_MapEvents::
	map_events FourIsland_House2_ObjectEvents, FourIsland_House2_MapWarps, NULL, NULL

@ ===== END data/maps/FourIsland_House2/events.inc =====
@ ===== BEGIN data/maps/FourIsland_Mart/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FourIsland_Mart/map.json
@

	.align 2

FourIsland_Mart_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_CLERK, 2, 3, 0, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, FourIsland_Mart_EventScript_Clerk, 0
	object_event 2, OBJ_EVENT_GFX_OLD_MAN_1, 6, 5, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, FourIsland_Mart_EventScript_OldMan, 0
	object_event 3, OBJ_EVENT_GFX_CAMPER, 8, 3, 3, MOVEMENT_TYPE_WANDER_AROUND, 2, 1, TRAINER_TYPE_NONE, 0, FourIsland_Mart_EventScript_Camper, 0

FourIsland_Mart_MapWarps:
	warp_def 4, 7, 3, 7, MAP_FOUR_ISLAND

FourIsland_Mart_MapEvents::
	map_events FourIsland_Mart_ObjectEvents, FourIsland_Mart_MapWarps, NULL, NULL

@ ===== END data/maps/FourIsland_Mart/events.inc =====
@ ===== BEGIN data/maps/FiveIsland_PokemonCenter_1F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FiveIsland_PokemonCenter_1F/map.json
@

	.align 2

FiveIsland_PokemonCenter_1F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_NURSE, 7, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, FiveIsland_PokemonCenter_1F_EventScript_Nurse, 0
	object_event 2, OBJ_EVENT_GFX_COOLTRAINER_F, 9, 4, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NONE, 0, FiveIsland_PokemonCenter_1F_EventScript_CooltrainerF, 0
	object_event 3, OBJ_EVENT_GFX_CHEF, 4, 8, 3, MOVEMENT_TYPE_WANDER_LEFT_AND_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, FiveIsland_PokemonCenter_1F_EventScript_Chef, 0
	object_event 4, 0, 2, 1, 0, MOVEMENT_TYPE_INVISIBLE, 1, 1, TRAINER_TYPE_NONE, 0, FiveIsland_PokemonCenter_1F_EventScript_PokemonJournal, FLAG_HIDE_POSTGAME_GOSSIPERS
	object_event 5, 0, 3, 1, 0, MOVEMENT_TYPE_INVISIBLE, 1, 1, TRAINER_TYPE_NONE, 0, FiveIsland_PokemonCenter_1F_EventScript_PokemonJournal, FLAG_HIDE_POSTGAME_GOSSIPERS

FiveIsland_PokemonCenter_1F_MapWarps:
	warp_def 7, 8, 3, 1, MAP_FIVE_ISLAND
	warp_def 1, 6, 4, 0, MAP_FIVE_ISLAND_POKEMON_CENTER_2F

FiveIsland_PokemonCenter_1F_MapEvents::
	map_events FiveIsland_PokemonCenter_1F_ObjectEvents, FiveIsland_PokemonCenter_1F_MapWarps, NULL, NULL

@ ===== END data/maps/FiveIsland_PokemonCenter_1F/events.inc =====
@ ===== BEGIN data/maps/FiveIsland_PokemonCenter_2F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FiveIsland_PokemonCenter_2F/map.json
@

	.align 2

FiveIsland_PokemonCenter_2F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_CABLE_CLUB_RECEPTIONIST, 6, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 0, 0, TRAINER_TYPE_NONE, 0, Common_EventScript_UnionRoomAttendant, 0
	object_event 2, OBJ_EVENT_GFX_CABLE_CLUB_RECEPTIONIST, 2, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 0, 0, TRAINER_TYPE_NONE, 0, Common_EventScript_WirelessClubAttendant, 0
	object_event 3, OBJ_EVENT_GFX_CABLE_CLUB_RECEPTIONIST, 10, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 0, 0, TRAINER_TYPE_NONE, 0, Common_EventScript_DirectCornerAttendant, 0
	object_event 4, OBJ_EVENT_GFX_MG_DELIVERYMAN, 1, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, CableClub_EventScript_MysteryGiftMan, FLAG_HIDE_MG_DELIVERYMEN

FiveIsland_PokemonCenter_2F_MapWarps:
	warp_def 1, 6, 4, 1, MAP_FIVE_ISLAND_POKEMON_CENTER_1F
	warp_def 5, 1, 0, 0, MAP_UNION_ROOM
	warp_def 9, 1, 0, 0, MAP_TRADE_CENTER

FiveIsland_PokemonCenter_2F_MapEvents::
	map_events FiveIsland_PokemonCenter_2F_ObjectEvents, FiveIsland_PokemonCenter_2F_MapWarps, NULL, NULL

@ ===== END data/maps/FiveIsland_PokemonCenter_2F/events.inc =====
@ ===== BEGIN data/maps/FiveIsland_Harbor/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FiveIsland_Harbor/map.json
@

	.align 2

FiveIsland_Harbor_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_SEAGALLOP, 8, 9, 0, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, 0x0, 0
	object_event 2, OBJ_EVENT_GFX_SAILOR, 8, 6, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NONE, 0, FiveIsland_Harbor_EventScript_Sailor, 0

FiveIsland_Harbor_MapWarps:
	warp_def 8, 2, 3, 0, MAP_FIVE_ISLAND

FiveIsland_Harbor_MapEvents::
	map_events FiveIsland_Harbor_ObjectEvents, FiveIsland_Harbor_MapWarps, NULL, NULL

@ ===== END data/maps/FiveIsland_Harbor/events.inc =====
@ ===== BEGIN data/maps/FiveIsland_House1/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FiveIsland_House1/map.json
@

	.align 2

FiveIsland_House1_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_WOMAN_3, 10, 2, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NONE, 0, FiveIsland_House1_EventScript_Woman, 0

FiveIsland_House1_MapWarps:
	warp_def 4, 7, 3, 2, MAP_FIVE_ISLAND

FiveIsland_House1_MapEvents::
	map_events FiveIsland_House1_ObjectEvents, FiveIsland_House1_MapWarps, NULL, NULL

@ ===== END data/maps/FiveIsland_House1/events.inc =====
@ ===== BEGIN data/maps/FiveIsland_House2/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FiveIsland_House2/map.json
@

	.align 2

FiveIsland_House2_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_OLD_MAN_1, 2, 3, 3, MOVEMENT_TYPE_WANDER_AROUND, 1, 2, TRAINER_TYPE_NONE, 0, FiveIsland_House2_EventScript_OldMan, 0

FiveIsland_House2_MapWarps:
	warp_def 4, 7, 3, 3, MAP_FIVE_ISLAND

FiveIsland_House2_MapEvents::
	map_events FiveIsland_House2_ObjectEvents, FiveIsland_House2_MapWarps, NULL, NULL

@ ===== END data/maps/FiveIsland_House2/events.inc =====
@ ===== BEGIN data/maps/SixIsland_PokemonCenter_1F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SixIsland_PokemonCenter_1F/map.json
@

	.align 2

SixIsland_PokemonCenter_1F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_NURSE, 7, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SixIsland_PokemonCenter_1F_EventScript_Nurse, 0
	object_event 2, OBJ_EVENT_GFX_BLUE, 5, 5, 3, MOVEMENT_TYPE_FACE_LEFT, 1, 1, TRAINER_TYPE_NONE, 0, 0x0, FLAG_HIDE_SIX_ISLAND_POKECENTER_RIVAL
	object_event 3, OBJ_EVENT_GFX_HIKER, 13, 3, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NONE, 0, SixIsland_PokemonCenter_1F_EventScript_Hiker, 0
	object_event 4, OBJ_EVENT_GFX_OLD_MAN_2, 12, 5, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SixIsland_PokemonCenter_1F_EventScript_OldMan, 0

SixIsland_PokemonCenter_1F_MapWarps:
	warp_def 7, 8, 3, 1, MAP_SIX_ISLAND
	warp_def 1, 6, 4, 0, MAP_SIX_ISLAND_POKEMON_CENTER_2F

SixIsland_PokemonCenter_1F_MapEvents::
	map_events SixIsland_PokemonCenter_1F_ObjectEvents, SixIsland_PokemonCenter_1F_MapWarps, NULL, NULL

@ ===== END data/maps/SixIsland_PokemonCenter_1F/events.inc =====
@ ===== BEGIN data/maps/SixIsland_PokemonCenter_2F/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SixIsland_PokemonCenter_2F/map.json
@

	.align 2

SixIsland_PokemonCenter_2F_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_CABLE_CLUB_RECEPTIONIST, 6, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 0, 0, TRAINER_TYPE_NONE, 0, Common_EventScript_UnionRoomAttendant, 0
	object_event 2, OBJ_EVENT_GFX_CABLE_CLUB_RECEPTIONIST, 2, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 0, 0, TRAINER_TYPE_NONE, 0, Common_EventScript_WirelessClubAttendant, 0
	object_event 3, OBJ_EVENT_GFX_CABLE_CLUB_RECEPTIONIST, 10, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 0, 0, TRAINER_TYPE_NONE, 0, Common_EventScript_DirectCornerAttendant, 0
	object_event 4, OBJ_EVENT_GFX_MG_DELIVERYMAN, 1, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, CableClub_EventScript_MysteryGiftMan, FLAG_HIDE_MG_DELIVERYMEN

SixIsland_PokemonCenter_2F_MapWarps:
	warp_def 1, 6, 4, 1, MAP_SIX_ISLAND_POKEMON_CENTER_1F
	warp_def 5, 1, 0, 0, MAP_UNION_ROOM
	warp_def 9, 1, 0, 0, MAP_TRADE_CENTER

SixIsland_PokemonCenter_2F_MapEvents::
	map_events SixIsland_PokemonCenter_2F_ObjectEvents, SixIsland_PokemonCenter_2F_MapWarps, NULL, NULL

@ ===== END data/maps/SixIsland_PokemonCenter_2F/events.inc =====
@ ===== BEGIN data/maps/SixIsland_Harbor/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SixIsland_Harbor/map.json
@

	.align 2

SixIsland_Harbor_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_SEAGALLOP, 8, 9, 0, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, 0x0, 0
	object_event 2, OBJ_EVENT_GFX_SAILOR, 8, 6, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NONE, 0, SixIsland_Harbor_EventScript_Sailor, 0

SixIsland_Harbor_MapWarps:
	warp_def 8, 2, 3, 0, MAP_SIX_ISLAND

SixIsland_Harbor_MapEvents::
	map_events SixIsland_Harbor_ObjectEvents, SixIsland_Harbor_MapWarps, NULL, NULL

@ ===== END data/maps/SixIsland_Harbor/events.inc =====
@ ===== BEGIN data/maps/SixIsland_House/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SixIsland_House/map.json
@

	.align 2

SixIsland_House_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_OLD_MAN_1, 7, 5, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SixIsland_House_EventScript_OldMan, 0

SixIsland_House_MapWarps:
	warp_def 4, 7, 3, 2, MAP_SIX_ISLAND

SixIsland_House_MapEvents::
	map_events SixIsland_House_ObjectEvents, SixIsland_House_MapWarps, NULL, NULL

@ ===== END data/maps/SixIsland_House/events.inc =====
@ ===== BEGIN data/maps/SixIsland_Mart/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SixIsland_Mart/map.json
@

	.align 2

SixIsland_Mart_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_CLERK, 2, 3, 0, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, SixIsland_Mart_EventScript_Clerk, 0
	object_event 2, OBJ_EVENT_GFX_OLD_WOMAN, 8, 3, 3, MOVEMENT_TYPE_WANDER_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, SixIsland_Mart_EventScript_OldWoman, 0
	object_event 3, OBJ_EVENT_GFX_PICNICKER, 7, 7, 3, MOVEMENT_TYPE_WANDER_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, SixIsland_Mart_EventScript_Picnicker, 0

SixIsland_Mart_MapWarps:
	warp_def 4, 7, 3, 3, MAP_SIX_ISLAND

SixIsland_Mart_MapEvents::
	map_events SixIsland_Mart_ObjectEvents, SixIsland_Mart_MapWarps, NULL, NULL

@ ===== END data/maps/SixIsland_Mart/events.inc =====
@ ===== BEGIN data/maps/ThreeIsland_Harbor/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/ThreeIsland_Harbor/map.json
@

	.align 2

ThreeIsland_Harbor_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_SEAGALLOP, 8, 9, 0, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, 0x0, 0
	object_event 2, OBJ_EVENT_GFX_SAILOR, 8, 6, 3, MOVEMENT_TYPE_FACE_UP, 1, 1, TRAINER_TYPE_NONE, 0, ThreeIsland_Harbor_EventScript_Sailor, 0

ThreeIsland_Harbor_MapWarps:
	warp_def 8, 2, 3, 2, MAP_THREE_ISLAND_PORT

ThreeIsland_Harbor_MapEvents::
	map_events ThreeIsland_Harbor_ObjectEvents, ThreeIsland_Harbor_MapWarps, NULL, NULL

@ ===== END data/maps/ThreeIsland_Harbor/events.inc =====
@ ===== BEGIN data/maps/FiveIsland_ResortGorgeous_House/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FiveIsland_ResortGorgeous_House/map.json
@

	.align 2

FiveIsland_ResortGorgeous_House_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_WOMAN_2, 4, 4, 3, MOVEMENT_TYPE_FACE_RIGHT, 1, 1, TRAINER_TYPE_NONE, 0, FiveIsland_ResortGorgeous_House_EventScript_Selphy, FLAG_HIDE_RESORT_GORGEOUS_INSIDE_SELPHY
	object_event 2, OBJ_EVENT_GFX_GENTLEMAN, 6, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, FiveIsland_ResortGorgeous_House_EventScript_Butler, FLAG_HIDE_SELPHYS_BUTLER

FiveIsland_ResortGorgeous_House_MapWarps:
	warp_def 4, 7, 3, 1, MAP_FIVE_ISLAND_RESORT_GORGEOUS

FiveIsland_ResortGorgeous_House_MapBGEvents:
	bg_sign_event 9, 1, 0, BG_EVENT_PLAYER_FACING_NORTH, FiveIsland_ResortGorgeous_House_EventScript_PokemonJournal
	bg_sign_event 8, 1, 0, BG_EVENT_PLAYER_FACING_NORTH, FiveIsland_ResortGorgeous_House_EventScript_PokemonJournal

FiveIsland_ResortGorgeous_House_MapEvents::
	map_events FiveIsland_ResortGorgeous_House_ObjectEvents, FiveIsland_ResortGorgeous_House_MapWarps, NULL, FiveIsland_ResortGorgeous_House_MapBGEvents

@ ===== END data/maps/FiveIsland_ResortGorgeous_House/events.inc =====
@ ===== BEGIN data/maps/TwoIsland_CapeBrink_House/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/TwoIsland_CapeBrink_House/map.json
@

	.align 2

TwoIsland_CapeBrink_House_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_CHANNELER, 4, 4, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, TwoIsland_CapeBrink_House_EventScript_StarterTutor, 0

TwoIsland_CapeBrink_House_MapWarps:
	warp_def 4, 7, 3, 0, MAP_TWO_ISLAND_CAPE_BRINK

TwoIsland_CapeBrink_House_MapEvents::
	map_events TwoIsland_CapeBrink_House_ObjectEvents, TwoIsland_CapeBrink_House_MapWarps, NULL, NULL

@ ===== END data/maps/TwoIsland_CapeBrink_House/events.inc =====
@ ===== BEGIN data/maps/SixIsland_WaterPath_House1/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SixIsland_WaterPath_House1/map.json
@

	.align 2

SixIsland_WaterPath_House1_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_BEAUTY, 3, 4, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SixIsland_WaterPath_House1_EventScript_Beauty, 0

SixIsland_WaterPath_House1_MapWarps:
	warp_def 3, 7, 3, 0, MAP_SIX_ISLAND_WATER_PATH

SixIsland_WaterPath_House1_MapBGEvents:
	bg_sign_event 9, 1, 0, BG_EVENT_PLAYER_FACING_ANY, SixIsland_WaterPath_House1_EventScript_SizeRecord

SixIsland_WaterPath_House1_MapEvents::
	map_events SixIsland_WaterPath_House1_ObjectEvents, SixIsland_WaterPath_House1_MapWarps, NULL, SixIsland_WaterPath_House1_MapBGEvents

@ ===== END data/maps/SixIsland_WaterPath_House1/events.inc =====
@ ===== BEGIN data/maps/SixIsland_WaterPath_House2/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SixIsland_WaterPath_House2/map.json
@

	.align 2

SixIsland_WaterPath_House2_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_MAN, 7, 4, 3, MOVEMENT_TYPE_FACE_UP_AND_LEFT, 1, 1, TRAINER_TYPE_NONE, 0, SixIsland_WaterPath_House2_EventScript_Man, 0

SixIsland_WaterPath_House2_MapWarps:
	warp_def 4, 7, 3, 1, MAP_SIX_ISLAND_WATER_PATH

SixIsland_WaterPath_House2_MapEvents::
	map_events SixIsland_WaterPath_House2_ObjectEvents, SixIsland_WaterPath_House2_MapWarps, NULL, NULL

@ ===== END data/maps/SixIsland_WaterPath_House2/events.inc =====
@ ===== BEGIN data/maps/SevenIsland_SevaultCanyon_House/events.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SevenIsland_SevaultCanyon_House/map.json
@

	.align 2

SevenIsland_SevaultCanyon_House_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_BALDING_MAN, 2, 4, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SevenIsland_SevaultCanyon_House_EventScript_ChanseyDanceMan, 0
	object_event 2, OBJ_EVENT_GFX_CHANSEY, 4, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SevenIsland_SevaultCanyon_House_EventScript_Chansey, 0
	object_event 3, OBJ_EVENT_GFX_ITEM_BALL, 6, 4, 0, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NONE, 0, SevenIsland_SevaultCanyon_House_EventScript_ItemLuckyPunch, FLAG_HIDE_SEVEN_ISLAND_SEVAULT_CANYON_HOUSE_LUCKY_PUNCH

SevenIsland_SevaultCanyon_House_MapWarps:
	warp_def 4, 7, 3, 1, MAP_SEVEN_ISLAND_SEVAULT_CANYON

SevenIsland_SevaultCanyon_House_MapEvents::
	map_events SevenIsland_SevaultCanyon_House_ObjectEvents, SevenIsland_SevaultCanyon_House_MapWarps, NULL, NULL

@ ===== END data/maps/SevenIsland_SevaultCanyon_House/events.inc =====
@ ===== END data/maps/events.inc =====
