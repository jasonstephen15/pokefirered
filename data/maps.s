#include "constants/global.h"
#include "constants/layouts.h"
#include "constants/maps.h"
#include "constants/region_map_sections.h"
#include "constants/songs.h"
#include "constants/items.h"
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

@ ===== BEGIN data/layouts/layouts.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/layouts/layouts.json
@

PalletTown_PlayersHouse_1F_Layout_Border::
	.incbin "assets/data.bin", 0x0, 0x8
PalletTown_PlayersHouse_1F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x8, 0x104
	.align 2
PalletTown_PlayersHouse_1F_Layout::
	.4byte 13
	.4byte 10
	.4byte PalletTown_PlayersHouse_1F_Layout_Border
	.4byte PalletTown_PlayersHouse_1F_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_GenericBuilding1
	.byte 2
	.byte 2
	.2byte 0

PalletTown_PlayersHouse_2F_Layout_Border::
	.incbin "assets/data.bin", 0x10C, 0x8
PalletTown_PlayersHouse_2F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x114, 0xD8
	.align 2
PalletTown_PlayersHouse_2F_Layout::
	.4byte 12
	.4byte 9
	.4byte PalletTown_PlayersHouse_2F_Layout_Border
	.4byte PalletTown_PlayersHouse_2F_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_GenericBuilding1
	.byte 2
	.byte 2
	.2byte 0

PalletTown_RivalsHouse_Layout_Border::
	.incbin "assets/data.bin", 0x1EC, 0x8
PalletTown_RivalsHouse_Layout_Blockdata::
	.incbin "assets/data.bin", 0x1F4, 0x104
	.align 2
PalletTown_RivalsHouse_Layout::
	.4byte 13
	.4byte 10
	.4byte PalletTown_RivalsHouse_Layout_Border
	.4byte PalletTown_RivalsHouse_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_GenericBuilding2
	.byte 2
	.byte 2
	.2byte 0

LittlerootTown_MaysHouse_2F_Layout_Border::
	.incbin "assets/data.bin", 0x2F8, 0x8
LittlerootTown_MaysHouse_2F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x300, 0x90
	.align 2
LittlerootTown_MaysHouse_2F_Layout::
	.4byte 9
	.4byte 8
	.4byte LittlerootTown_MaysHouse_2F_Layout_Border
	.4byte LittlerootTown_MaysHouse_2F_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_GenericBuilding1
	.byte 0
	.byte 0
	.2byte 0

PalletTown_ProfessorOaksLab_Layout_Border::
	.incbin "assets/data.bin", 0x390, 0x8
PalletTown_ProfessorOaksLab_Layout_Blockdata::
	.incbin "assets/data.bin", 0x398, 0x16C
	.align 2
PalletTown_ProfessorOaksLab_Layout::
	.4byte 13
	.4byte 14
	.4byte PalletTown_ProfessorOaksLab_Layout_Border
	.4byte PalletTown_ProfessorOaksLab_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_Lab
	.byte 2
	.byte 2
	.2byte 0

House1_Layout_Border::
	.incbin "assets/data.bin", 0x504, 0x8
House1_Layout_Blockdata::
	.incbin "assets/data.bin", 0x50C, 0xC6
	.align 2
House1_Layout::
	.4byte 11
	.4byte 9
	.4byte House1_Layout_Border
	.4byte House1_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_GenericBuilding1
	.byte 2
	.byte 2
	.2byte 0

House2_Layout_Border::
	.incbin "assets/data.bin", 0x5D4, 0x8
House2_Layout_Blockdata::
	.incbin "assets/data.bin", 0x5DC, 0xC6
	.align 2
House2_Layout::
	.4byte 11
	.4byte 9
	.4byte House2_Layout_Border
	.4byte House2_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_GenericBuilding2
	.byte 2
	.byte 2
	.2byte 0

PokemonCenter_1F_Layout_Border::
	.incbin "assets/data.bin", 0x6A4, 0x8
PokemonCenter_1F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x6AC, 0x12C
	.align 2
PokemonCenter_1F_Layout::
	.4byte 15
	.4byte 10
	.4byte PokemonCenter_1F_Layout_Border
	.4byte PokemonCenter_1F_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_PokemonCenter
	.byte 2
	.byte 2
	.2byte 0

PokemonCenter_2F_Layout_Border::
	.incbin "assets/data.bin", 0x7D8, 0x8
PokemonCenter_2F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x7E0, 0x12C
	.align 2
PokemonCenter_2F_Layout::
	.4byte 15
	.4byte 10
	.4byte PokemonCenter_2F_Layout_Border
	.4byte PokemonCenter_2F_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_PokemonCenter
	.byte 2
	.byte 2
	.2byte 0

Mart_Layout_Border::
	.incbin "assets/data.bin", 0x90C, 0x8
Mart_Layout_Blockdata::
	.incbin "assets/data.bin", 0x914, 0xC6
	.align 2
Mart_Layout::
	.4byte 11
	.4byte 9
	.4byte Mart_Layout_Border
	.4byte Mart_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_Mart
	.byte 2
	.byte 2
	.2byte 0

House3_Layout_Border::
	.incbin "assets/data.bin", 0x9DC, 0x8
House3_Layout_Blockdata::
	.incbin "assets/data.bin", 0x9E4, 0xC6
	.align 2
House3_Layout::
	.4byte 11
	.4byte 9
	.4byte House3_Layout_Border
	.4byte House3_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_GenericBuilding2
	.byte 2
	.byte 2
	.2byte 0

CeruleanCity_Gym_Layout_Border::
	.incbin "assets/data.bin", 0xAAC, 0x8
CeruleanCity_Gym_Layout_Blockdata::
	.incbin "assets/data.bin", 0xAB4, 0x2A8
	.align 2
CeruleanCity_Gym_Layout::
	.4byte 17
	.4byte 20
	.4byte CeruleanCity_Gym_Layout_Border
	.4byte CeruleanCity_Gym_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_CeruleanGym
	.byte 2
	.byte 2
	.2byte 0

House4_Layout_Border::
	.incbin "assets/data.bin", 0xD5C, 0x8
House4_Layout_Blockdata::
	.incbin "assets/data.bin", 0xD64, 0xC6
	.align 2
House4_Layout::
	.4byte 11
	.4byte 9
	.4byte House4_Layout_Border
	.4byte House4_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_GenericBuilding2
	.byte 2
	.byte 2
	.2byte 0

LavaridgeTown_HerbShop_Layout_Border::
	.incbin "assets/data.bin", 0xE2C, 0x8
LavaridgeTown_HerbShop_Layout_Blockdata::
	.incbin "assets/data.bin", 0xE34, 0xB0
	.align 2
LavaridgeTown_HerbShop_Layout::
	.4byte 11
	.4byte 8
	.4byte LavaridgeTown_HerbShop_Layout_Border
	.4byte LavaridgeTown_HerbShop_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_Mart
	.byte 0
	.byte 0
	.2byte 0

CeladonCity_Gym_Layout_Border::
	.incbin "assets/data.bin", 0xEE4, 0x8
CeladonCity_Gym_Layout_Blockdata::
	.incbin "assets/data.bin", 0xEEC, 0x208
	.align 2
CeladonCity_Gym_Layout::
	.4byte 13
	.4byte 20
	.4byte CeladonCity_Gym_Layout_Border
	.4byte CeladonCity_Gym_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_CeladonGym
	.byte 2
	.byte 2
	.2byte 0

RS_PokemonCenter_1F_Layout_Border::
	.incbin "assets/data.bin", 0x10F4, 0x8
RS_PokemonCenter_1F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x10FC, 0xFC
	.align 2
RS_PokemonCenter_1F_Layout::
	.4byte 14
	.4byte 9
	.4byte RS_PokemonCenter_1F_Layout_Border
	.4byte RS_PokemonCenter_1F_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_PokemonCenter
	.byte 2
	.byte 2
	.2byte 0

FiveIsland_ResortGorgeous_House_Layout_Border::
	.incbin "assets/data.bin", 0x11F8, 0x8
FiveIsland_ResortGorgeous_House_Layout_Blockdata::
	.incbin "assets/data.bin", 0x1200, 0xC6
	.align 2
FiveIsland_ResortGorgeous_House_Layout::
	.4byte 11
	.4byte 9
	.4byte FiveIsland_ResortGorgeous_House_Layout_Border
	.4byte FiveIsland_ResortGorgeous_House_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_Museum
	.byte 2
	.byte 2
	.2byte 0

PacifidlogTown_House1_Layout_Border::
	.incbin "assets/data.bin", 0x12C8, 0x8
PacifidlogTown_House1_Layout_Blockdata::
	.incbin "assets/data.bin", 0x12D0, 0xB4
	.align 2
PacifidlogTown_House1_Layout::
	.4byte 10
	.4byte 9
	.4byte PacifidlogTown_House1_Layout_Border
	.4byte PacifidlogTown_House1_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_HoennBuilding
	.byte 0
	.byte 0
	.2byte 0

PacifidlogTown_House2_Layout_Border::
	.incbin "assets/data.bin", 0x1384, 0x8
PacifidlogTown_House2_Layout_Blockdata::
	.incbin "assets/data.bin", 0x138C, 0xB4
	.align 2
PacifidlogTown_House2_Layout::
	.4byte 10
	.4byte 9
	.4byte PacifidlogTown_House2_Layout_Border
	.4byte PacifidlogTown_House2_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_HoennBuilding
	.byte 0
	.byte 0
	.2byte 0

FuchsiaCity_Gym_Layout_Border::
	.incbin "assets/data.bin", 0x1440, 0x8
FuchsiaCity_Gym_Layout_Blockdata::
	.incbin "assets/data.bin", 0x1448, 0x2B2
	.align 2
FuchsiaCity_Gym_Layout::
	.4byte 15
	.4byte 23
	.4byte FuchsiaCity_Gym_Layout_Border
	.4byte FuchsiaCity_Gym_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_FuchsiaGym
	.byte 2
	.byte 2
	.2byte 0

House5_Layout_Border::
	.incbin "assets/data.bin", 0x16FC, 0x8
House5_Layout_Blockdata::
	.incbin "assets/data.bin", 0x1704, 0xC6
	.align 2
House5_Layout::
	.4byte 11
	.4byte 9
	.4byte House5_Layout_Border
	.4byte House5_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_GenericBuilding1
	.byte 2
	.byte 2
	.2byte 0

Unused1_Layout_Border::
	.incbin "assets/data.bin", 0x17CC, 0x8
Unused1_Layout_Blockdata::
	.incbin "assets/data.bin", 0x17D4, 0x120
	.align 2
Unused1_Layout::
	.4byte 12
	.4byte 12
	.4byte Unused1_Layout_Border
	.4byte Unused1_Layout_Blockdata
	.4byte NULL
	.4byte gTileset_Dummy1
	.byte 2
	.byte 2
	.2byte 0

VermilionCity_Gym_Layout_Border::
	.incbin "assets/data.bin", 0x18F4, 0x8
VermilionCity_Gym_Layout_Blockdata::
	.incbin "assets/data.bin", 0x18FC, 0x1CE
	.align 2
VermilionCity_Gym_Layout::
	.4byte 11
	.4byte 21
	.4byte VermilionCity_Gym_Layout_Border
	.4byte VermilionCity_Gym_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_VermilionGym
	.byte 2
	.byte 2
	.2byte 0

CeruleanCity_BikeShop_Layout_Border::
	.incbin "assets/data.bin", 0x1ACC, 0x8
CeruleanCity_BikeShop_Layout_Blockdata::
	.incbin "assets/data.bin", 0x1AD4, 0xDC
	.align 2
CeruleanCity_BikeShop_Layout::
	.4byte 11
	.4byte 10
	.4byte CeruleanCity_BikeShop_Layout_Border
	.4byte CeruleanCity_BikeShop_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_BikeShop
	.byte 2
	.byte 2
	.2byte 0

CeladonCity_GameCorner_Layout_Border::
	.incbin "assets/data.bin", 0x1BB0, 0x8
CeladonCity_GameCorner_Layout_Blockdata::
	.incbin "assets/data.bin", 0x1BB8, 0x21C
	.align 2
CeladonCity_GameCorner_Layout::
	.4byte 18
	.4byte 15
	.4byte CeladonCity_GameCorner_Layout_Border
	.4byte CeladonCity_GameCorner_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_GameCorner
	.byte 2
	.byte 2
	.2byte 0

PewterCity_Gym_Layout_Border::
	.incbin "assets/data.bin", 0x1DD4, 0x8
PewterCity_Gym_Layout_Blockdata::
	.incbin "assets/data.bin", 0x1DDC, 0x1A0
	.align 2
PewterCity_Gym_Layout::
	.4byte 13
	.4byte 16
	.4byte PewterCity_Gym_Layout_Border
	.4byte PewterCity_Gym_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_PewterGym
	.byte 2
	.byte 2
	.2byte 0

FourIsland_LoreleisHouse_Layout_Border::
	.incbin "assets/data.bin", 0x1F7C, 0x8
FourIsland_LoreleisHouse_Layout_Blockdata::
	.incbin "assets/data.bin", 0x1F84, 0xC6
	.align 2
FourIsland_LoreleisHouse_Layout::
	.4byte 11
	.4byte 9
	.4byte FourIsland_LoreleisHouse_Layout_Border
	.4byte FourIsland_LoreleisHouse_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_SafariZoneBuilding
	.byte 2
	.byte 2
	.2byte 0

ThreeIsland_House1_Layout_Border::
	.incbin "assets/data.bin", 0x204C, 0x8
ThreeIsland_House1_Layout_Blockdata::
	.incbin "assets/data.bin", 0x2054, 0xC6
	.align 2
ThreeIsland_House1_Layout::
	.4byte 11
	.4byte 9
	.4byte ThreeIsland_House1_Layout_Border
	.4byte ThreeIsland_House1_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_Lab
	.byte 2
	.byte 2
	.2byte 0

RustboroCity_CuttersHouse_Layout_Border::
	.incbin "assets/data.bin", 0x211C, 0x8
RustboroCity_CuttersHouse_Layout_Blockdata::
	.incbin "assets/data.bin", 0x2124, 0xC6
	.align 2
RustboroCity_CuttersHouse_Layout::
	.4byte 11
	.4byte 9
	.4byte RustboroCity_CuttersHouse_Layout_Border
	.4byte RustboroCity_CuttersHouse_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_HoennBuilding
	.byte 0
	.byte 0
	.2byte 0

FortreeCity_House1_Layout_Border::
	.incbin "assets/data.bin", 0x21EC, 0x8
FortreeCity_House1_Layout_Blockdata::
	.incbin "assets/data.bin", 0x21F4, 0x60
	.align 2
FortreeCity_House1_Layout::
	.4byte 8
	.4byte 6
	.4byte FortreeCity_House1_Layout_Border
	.4byte FortreeCity_House1_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_HoennBuilding
	.byte 0
	.byte 0
	.2byte 0

SaffronCity_Gym_Layout_Border::
	.incbin "assets/data.bin", 0x2254, 0x8
SaffronCity_Gym_Layout_Blockdata::
	.incbin "assets/data.bin", 0x225C, 0x5AA
	.align 2
SaffronCity_Gym_Layout::
	.4byte 29
	.4byte 25
	.4byte SaffronCity_Gym_Layout_Border
	.4byte SaffronCity_Gym_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_SaffronGym
	.byte 2
	.byte 2
	.2byte 0

FortreeCity_House2_Layout_Border::
	.incbin "assets/data.bin", 0x2808, 0x8
FortreeCity_House2_Layout_Blockdata::
	.incbin "assets/data.bin", 0x2810, 0x60
	.align 2
FortreeCity_House2_Layout::
	.4byte 8
	.4byte 6
	.4byte FortreeCity_House2_Layout_Border
	.4byte FortreeCity_House2_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_HoennBuilding
	.byte 0
	.byte 0
	.2byte 0

CinnabarIsland_Gym_Layout_Border::
	.incbin "assets/data.bin", 0x2870, 0x8
CinnabarIsland_Gym_Layout_Blockdata::
	.incbin "assets/data.bin", 0x2878, 0x5DC
	.align 2
CinnabarIsland_Gym_Layout::
	.4byte 30
	.4byte 25
	.4byte CinnabarIsland_Gym_Layout_Border
	.4byte CinnabarIsland_Gym_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_CinnabarGym
	.byte 2
	.byte 2
	.2byte 0

ViridianCity_Gym_Layout_Border::
	.incbin "assets/data.bin", 0x2E54, 0x8
ViridianCity_Gym_Layout_Blockdata::
	.incbin "assets/data.bin", 0x2E5C, 0x3C0
	.align 2
ViridianCity_Gym_Layout::
	.4byte 20
	.4byte 24
	.4byte ViridianCity_Gym_Layout_Border
	.4byte ViridianCity_Gym_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_ViridianGym
	.byte 2
	.byte 2
	.2byte 0

RS_SafariZone_Entrance_Layout_Border::
	.incbin "assets/data.bin", 0x321C, 0x8
RS_SafariZone_Entrance_Layout_Blockdata::
	.incbin "assets/data.bin", 0x3224, 0x1F8
	.align 2
RS_SafariZone_Entrance_Layout::
	.4byte 18
	.4byte 14
	.4byte RS_SafariZone_Entrance_Layout_Border
	.4byte RS_SafariZone_Entrance_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_Mart
	.byte 0
	.byte 0
	.2byte 0

BattleColosseum_2P_Layout_Border::
	.incbin "assets/data.bin", 0x341C, 0x8
BattleColosseum_2P_Layout_Blockdata::
	.incbin "assets/data.bin", 0x3424, 0xFC
	.align 2
BattleColosseum_2P_Layout::
	.4byte 14
	.4byte 9
	.4byte BattleColosseum_2P_Layout_Border
	.4byte BattleColosseum_2P_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_CableClub
	.byte 2
	.byte 2
	.2byte 0

TradeCenter_Layout_Border::
	.incbin "assets/data.bin", 0x3520, 0x8
TradeCenter_Layout_Blockdata::
	.incbin "assets/data.bin", 0x3528, 0xD8
	.align 2
TradeCenter_Layout::
	.4byte 12
	.4byte 9
	.4byte TradeCenter_Layout_Border
	.4byte TradeCenter_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_CableClub
	.byte 2
	.byte 2
	.2byte 0

RecordCorner_Layout_Border::
	.incbin "assets/data.bin", 0x3600, 0x8
RecordCorner_Layout_Blockdata::
	.incbin "assets/data.bin", 0x3608, 0x190
	.align 2
RecordCorner_Layout::
	.4byte 20
	.4byte 10
	.4byte RecordCorner_Layout_Border
	.4byte RecordCorner_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_CableClub
	.byte 2
	.byte 2
	.2byte 0

BattleColosseum_4P_Layout_Border::
	.incbin "assets/data.bin", 0x3798, 0x8
BattleColosseum_4P_Layout_Blockdata::
	.incbin "assets/data.bin", 0x37A0, 0xFC
	.align 2
BattleColosseum_4P_Layout::
	.4byte 14
	.4byte 9
	.4byte BattleColosseum_4P_Layout_Border
	.4byte BattleColosseum_4P_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_CableClub
	.byte 2
	.byte 2
	.2byte 0

FuchsiaCity_SafariZone_Entrance_Layout_Border::
	.incbin "assets/data.bin", 0x389C, 0x8
FuchsiaCity_SafariZone_Entrance_Layout_Blockdata::
	.incbin "assets/data.bin", 0x38A4, 0xA2
	.align 2
FuchsiaCity_SafariZone_Entrance_Layout::
	.4byte 9
	.4byte 9
	.4byte FuchsiaCity_SafariZone_Entrance_Layout_Border
	.4byte FuchsiaCity_SafariZone_Entrance_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_SafariZoneBuilding
	.byte 2
	.byte 2
	.2byte 0

RS_SafariZone_Northeast_Layout_Border::
	.incbin "assets/data.bin", 0x3948, 0x8
RS_SafariZone_Northeast_Layout_Blockdata::
	.incbin "assets/data.bin", 0x3950, 0xC80
	.align 2
RS_SafariZone_Northeast_Layout::
	.4byte 40
	.4byte 40
	.4byte RS_SafariZone_Northeast_Layout_Border
	.4byte RS_SafariZone_Northeast_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_CinnabarIsland
	.byte 0
	.byte 0
	.2byte 0

RS_SafariZone_Southwest_Layout_Border::
	.incbin "assets/data.bin", 0x45D0, 0x8
RS_SafariZone_Southwest_Layout_Blockdata::
	.incbin "assets/data.bin", 0x45D8, 0xC80
	.align 2
RS_SafariZone_Southwest_Layout::
	.4byte 40
	.4byte 40
	.4byte RS_SafariZone_Southwest_Layout_Border
	.4byte RS_SafariZone_Southwest_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_CinnabarIsland
	.byte 0
	.byte 0
	.2byte 0

RS_SafariZone_Southeast_Layout_Border::
	.incbin "assets/data.bin", 0x5258, 0x8
RS_SafariZone_Southeast_Layout_Blockdata::
	.incbin "assets/data.bin", 0x5260, 0xC80
	.align 2
RS_SafariZone_Southeast_Layout::
	.4byte 40
	.4byte 40
	.4byte RS_SafariZone_Southeast_Layout_Border
	.4byte RS_SafariZone_Southeast_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_CinnabarIsland
	.byte 0
	.byte 0
	.2byte 0

FortreeCity_DecorationShop_Layout_Border::
	.incbin "assets/data.bin", 0x5EE0, 0x8
FortreeCity_DecorationShop_Layout_Blockdata::
	.incbin "assets/data.bin", 0x5EE8, 0x60
	.align 2
FortreeCity_DecorationShop_Layout::
	.4byte 8
	.4byte 6
	.4byte FortreeCity_DecorationShop_Layout_Border
	.4byte FortreeCity_DecorationShop_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_HoennBuilding
	.byte 0
	.byte 0
	.2byte 0

RS_BattleTower_Layout_Border::
	.incbin "assets/data.bin", 0x5F48, 0x8
RS_BattleTower_Layout_Blockdata::
	.incbin "assets/data.bin", 0x5F50, 0x6CC
	.align 2
RS_BattleTower_Layout::
	.4byte 29
	.4byte 30
	.4byte RS_BattleTower_Layout_Border
	.4byte RS_BattleTower_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_PewterCity
	.byte 0
	.byte 0
	.2byte 0

SSTidal_Corridor_Layout_Border::
	.incbin "assets/data.bin", 0x661C, 0x8
SSTidal_Corridor_Layout_Blockdata::
	.incbin "assets/data.bin", 0x6624, 0x1D4
	.align 2
SSTidal_Corridor_Layout::
	.4byte 18
	.4byte 13
	.4byte SSTidal_Corridor_Layout_Border
	.4byte SSTidal_Corridor_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_SSAnne
	.byte 0
	.byte 0
	.2byte 0

SSTidal_LowerDeck_Layout_Border::
	.incbin "assets/data.bin", 0x67F8, 0x8
SSTidal_LowerDeck_Layout_Blockdata::
	.incbin "assets/data.bin", 0x6800, 0x1BA
	.align 2
SSTidal_LowerDeck_Layout::
	.4byte 17
	.4byte 13
	.4byte SSTidal_LowerDeck_Layout_Border
	.4byte SSTidal_LowerDeck_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_SSAnne
	.byte 0
	.byte 0
	.2byte 0

SSTidal_Rooms_Layout_Border::
	.incbin "assets/data.bin", 0x69BC, 0x8
SSTidal_Rooms_Layout_Blockdata::
	.incbin "assets/data.bin", 0x69C4, 0x510
	.align 2
SSTidal_Rooms_Layout::
	.4byte 36
	.4byte 18
	.4byte SSTidal_Rooms_Layout_Border
	.4byte SSTidal_Rooms_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_SSAnne
	.byte 0
	.byte 0
	.2byte 0

RustboroCity_Flat2_1F_Layout_Border::
	.incbin "assets/data.bin", 0x6ED4, 0x8
RustboroCity_Flat2_1F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x6EDC, 0xFC
	.align 2
RustboroCity_Flat2_1F_Layout::
	.4byte 14
	.4byte 9
	.4byte RustboroCity_Flat2_1F_Layout_Border
	.4byte RustboroCity_Flat2_1F_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_HoennBuilding
	.byte 0
	.byte 0
	.2byte 0

RustboroCity_Flat2_2F_Layout_Border::
	.incbin "assets/data.bin", 0x6FD8, 0x8
RustboroCity_Flat2_2F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x6FE0, 0xFC
	.align 2
RustboroCity_Flat2_2F_Layout::
	.4byte 14
	.4byte 9
	.4byte RustboroCity_Flat2_2F_Layout_Border
	.4byte RustboroCity_Flat2_2F_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_HoennBuilding
	.byte 0
	.byte 0
	.2byte 0

RustboroCity_Flat2_3F_Layout_Border::
	.incbin "assets/data.bin", 0x70DC, 0x8
RustboroCity_Flat2_3F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x70E4, 0xFC
	.align 2
RustboroCity_Flat2_3F_Layout::
	.4byte 14
	.4byte 9
	.4byte RustboroCity_Flat2_3F_Layout_Border
	.4byte RustboroCity_Flat2_3F_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_HoennBuilding
	.byte 0
	.byte 0
	.2byte 0

EverGrandeCity_HallOfFame_Layout_Border::
	.incbin "assets/data.bin", 0x71E0, 0x8
EverGrandeCity_HallOfFame_Layout_Blockdata::
	.incbin "assets/data.bin", 0x71E8, 0x1FE
	.align 2
EverGrandeCity_HallOfFame_Layout::
	.4byte 15
	.4byte 17
	.4byte EverGrandeCity_HallOfFame_Layout_Border
	.4byte EverGrandeCity_HallOfFame_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_CableClub
	.byte 0
	.byte 0
	.2byte 0

MossdeepCity_EReaderTrainerHouse_1F_Layout_Border::
	.incbin "assets/data.bin", 0x73E8, 0x8
MossdeepCity_EReaderTrainerHouse_1F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x73F0, 0xB0
	.align 2
MossdeepCity_EReaderTrainerHouse_1F_Layout::
	.4byte 11
	.4byte 8
	.4byte MossdeepCity_EReaderTrainerHouse_1F_Layout_Border
	.4byte MossdeepCity_EReaderTrainerHouse_1F_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_HoennBuilding
	.byte 0
	.byte 0
	.2byte 0

MossdeepCity_EReaderTrainerHouse_2F_Layout_Border::
	.incbin "assets/data.bin", 0x74A0, 0x8
MossdeepCity_EReaderTrainerHouse_2F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x74A8, 0xD8
	.align 2
MossdeepCity_EReaderTrainerHouse_2F_Layout::
	.4byte 12
	.4byte 9
	.4byte MossdeepCity_EReaderTrainerHouse_2F_Layout_Border
	.4byte MossdeepCity_EReaderTrainerHouse_2F_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_HoennBuilding
	.byte 0
	.byte 0
	.2byte 0

SootopolisCity_House1_Layout_Border::
	.incbin "assets/data.bin", 0x7580, 0x8
SootopolisCity_House1_Layout_Blockdata::
	.incbin "assets/data.bin", 0x7588, 0x70
	.align 2
SootopolisCity_House1_Layout::
	.4byte 8
	.4byte 7
	.4byte SootopolisCity_House1_Layout_Border
	.4byte SootopolisCity_House1_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_HoennBuilding
	.byte 0
	.byte 0
	.2byte 0

SootopolisCity_House2_Layout_Border::
	.incbin "assets/data.bin", 0x75F8, 0x8
SootopolisCity_House2_Layout_Blockdata::
	.incbin "assets/data.bin", 0x7600, 0x70
	.align 2
SootopolisCity_House2_Layout::
	.4byte 8
	.4byte 7
	.4byte SootopolisCity_House2_Layout_Border
	.4byte SootopolisCity_House2_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_HoennBuilding
	.byte 0
	.byte 0
	.2byte 0

SootopolisCity_House3_Layout_Border::
	.incbin "assets/data.bin", 0x7670, 0x8
SootopolisCity_House3_Layout_Blockdata::
	.incbin "assets/data.bin", 0x7678, 0x70
	.align 2
SootopolisCity_House3_Layout::
	.4byte 8
	.4byte 7
	.4byte SootopolisCity_House3_Layout_Border
	.4byte SootopolisCity_House3_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_HoennBuilding
	.byte 0
	.byte 0
	.2byte 0

RustboroCity_Flat1_1F_Layout_Border::
	.incbin "assets/data.bin", 0x76E8, 0x8
RustboroCity_Flat1_1F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x76F0, 0xE0
	.align 2
RustboroCity_Flat1_1F_Layout::
	.4byte 14
	.4byte 8
	.4byte RustboroCity_Flat1_1F_Layout_Border
	.4byte RustboroCity_Flat1_1F_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_HoennBuilding
	.byte 0
	.byte 0
	.2byte 0

RustboroCity_Flat1_2F_Layout_Border::
	.incbin "assets/data.bin", 0x77D0, 0x8
RustboroCity_Flat1_2F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x77D8, 0xE0
	.align 2
RustboroCity_Flat1_2F_Layout::
	.4byte 14
	.4byte 8
	.4byte RustboroCity_Flat1_2F_Layout_Border
	.4byte RustboroCity_Flat1_2F_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_HoennBuilding
	.byte 0
	.byte 0
	.2byte 0

RS_SafariZone_RestHouse_Layout_Border::
	.incbin "assets/data.bin", 0x78B8, 0x8
RS_SafariZone_RestHouse_Layout_Blockdata::
	.incbin "assets/data.bin", 0x78C0, 0xB4
	.align 2
RS_SafariZone_RestHouse_Layout::
	.4byte 10
	.4byte 9
	.4byte RS_SafariZone_RestHouse_Layout_Border
	.4byte RS_SafariZone_RestHouse_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_HoennBuilding
	.byte 0
	.byte 0
	.2byte 0

PalletTown_Layout_Border::
	.incbin "assets/data.bin", 0x7974, 0x8
PalletTown_Layout_Blockdata::
	.incbin "assets/data.bin", 0x797C, 0x3C0
	.align 2
PalletTown_Layout::
	.4byte 24
	.4byte 20
	.4byte PalletTown_Layout_Border
	.4byte PalletTown_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_PalletTown
	.byte 2
	.byte 2
	.2byte 0

ViridianCity_Layout_Border::
	.incbin "assets/data.bin", 0x7D3C, 0x8
ViridianCity_Layout_Blockdata::
	.incbin "assets/data.bin", 0x7D44, 0xF00
	.align 2
ViridianCity_Layout::
	.4byte 48
	.4byte 40
	.4byte ViridianCity_Layout_Border
	.4byte ViridianCity_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_ViridianCity
	.byte 2
	.byte 2
	.2byte 0

PewterCity_Layout_Border::
	.incbin "assets/data.bin", 0x8C44, 0x8
PewterCity_Layout_Blockdata::
	.incbin "assets/data.bin", 0x8C4C, 0xF00
	.align 2
PewterCity_Layout::
	.4byte 48
	.4byte 40
	.4byte PewterCity_Layout_Border
	.4byte PewterCity_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_PewterCity
	.byte 2
	.byte 2
	.2byte 0

CeruleanCity_Layout_Border::
	.incbin "assets/data.bin", 0x9B4C, 0x8
CeruleanCity_Layout_Blockdata::
	.incbin "assets/data.bin", 0x9B54, 0xF00
	.align 2
CeruleanCity_Layout::
	.4byte 48
	.4byte 40
	.4byte CeruleanCity_Layout_Border
	.4byte CeruleanCity_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_CeruleanCity
	.byte 2
	.byte 2
	.2byte 0

LavenderTown_Layout_Border::
	.incbin "assets/data.bin", 0xAA54, 0x8
LavenderTown_Layout_Blockdata::
	.incbin "assets/data.bin", 0xAA5C, 0x3C0
	.align 2
LavenderTown_Layout::
	.4byte 24
	.4byte 20
	.4byte LavenderTown_Layout_Border
	.4byte LavenderTown_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_LavenderTown
	.byte 2
	.byte 2
	.2byte 0

VermilionCity_Layout_Border::
	.incbin "assets/data.bin", 0xAE1C, 0x8
VermilionCity_Layout_Blockdata::
	.incbin "assets/data.bin", 0xAE24, 0xF00
	.align 2
VermilionCity_Layout::
	.4byte 48
	.4byte 40
	.4byte VermilionCity_Layout_Border
	.4byte VermilionCity_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_VermilionCity
	.byte 2
	.byte 2
	.2byte 0

CeladonCity_Layout_Border::
	.incbin "assets/data.bin", 0xBD24, 0x8
CeladonCity_Layout_Blockdata::
	.incbin "assets/data.bin", 0xBD2C, 0x12C0
	.align 2
CeladonCity_Layout::
	.4byte 60
	.4byte 40
	.4byte CeladonCity_Layout_Border
	.4byte CeladonCity_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_CeladonCity
	.byte 2
	.byte 2
	.2byte 0

FuchsiaCity_Layout_Border::
	.incbin "assets/data.bin", 0xCFEC, 0x8
FuchsiaCity_Layout_Blockdata::
	.incbin "assets/data.bin", 0xCFF4, 0xF00
	.align 2
FuchsiaCity_Layout::
	.4byte 48
	.4byte 40
	.4byte FuchsiaCity_Layout_Border
	.4byte FuchsiaCity_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_FuchsiaCity
	.byte 2
	.byte 2
	.2byte 0

CinnabarIsland_Layout_Border::
	.incbin "assets/data.bin", 0xDEF4, 0x8
CinnabarIsland_Layout_Blockdata::
	.incbin "assets/data.bin", 0xDEFC, 0x3C0
	.align 2
CinnabarIsland_Layout::
	.4byte 24
	.4byte 20
	.4byte CinnabarIsland_Layout_Border
	.4byte CinnabarIsland_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_CinnabarIsland
	.byte 2
	.byte 2
	.2byte 0

IndigoPlateau_Exterior_Layout_Border::
	.incbin "assets/data.bin", 0xE2BC, 0x8
IndigoPlateau_Exterior_Layout_Blockdata::
	.incbin "assets/data.bin", 0xE2C4, 0x3C0
	.align 2
IndigoPlateau_Exterior_Layout::
	.4byte 24
	.4byte 20
	.4byte IndigoPlateau_Exterior_Layout_Border
	.4byte IndigoPlateau_Exterior_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_IndigoPlateau
	.byte 2
	.byte 2
	.2byte 0

SaffronCity_Connection_Layout_Border::
	.incbin "assets/data.bin", 0xE684, 0x8
SaffronCity_Connection_Layout_Blockdata::
	.incbin "assets/data.bin", 0xE68C, 0xF00
	.align 2
SaffronCity_Connection_Layout::
	.4byte 48
	.4byte 40
	.4byte SaffronCity_Connection_Layout_Border
	.4byte SaffronCity_Connection_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_SaffronCity
	.byte 2
	.byte 2
	.2byte 0

Route1_Layout_Border::
	.incbin "assets/data.bin", 0xF58C, 0x8
Route1_Layout_Blockdata::
	.incbin "assets/data.bin", 0xF594, 0x780
	.align 2
Route1_Layout::
	.4byte 24
	.4byte 40
	.4byte Route1_Layout_Border
	.4byte Route1_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_PalletTown
	.byte 2
	.byte 2
	.2byte 0

Route2_Layout_Border::
	.incbin "assets/data.bin", 0xFD14, 0x8
Route2_Layout_Blockdata::
	.incbin "assets/data.bin", 0xFD1C, 0xF00
	.align 2
Route2_Layout::
	.4byte 24
	.4byte 80
	.4byte Route2_Layout_Border
	.4byte Route2_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_ViridianCity
	.byte 2
	.byte 2
	.2byte 0

Route3_Layout_Border::
	.incbin "assets/data.bin", 0x10C1C, 0x8
Route3_Layout_Blockdata::
	.incbin "assets/data.bin", 0x10C24, 0xD20
	.align 2
Route3_Layout::
	.4byte 84
	.4byte 20
	.4byte Route3_Layout_Border
	.4byte Route3_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_PewterCity
	.byte 2
	.byte 2
	.2byte 0

Route4_Layout_Border::
	.incbin "assets/data.bin", 0x11944, 0x8
Route4_Layout_Blockdata::
	.incbin "assets/data.bin", 0x1194C, 0x10E0
	.align 2
Route4_Layout::
	.4byte 108
	.4byte 20
	.4byte Route4_Layout_Border
	.4byte Route4_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_CeruleanCity
	.byte 2
	.byte 2
	.2byte 0

Route5_Layout_Border::
	.incbin "assets/data.bin", 0x12A2C, 0x8
Route5_Layout_Blockdata::
	.incbin "assets/data.bin", 0x12A34, 0xF00
	.align 2
Route5_Layout::
	.4byte 48
	.4byte 40
	.4byte Route5_Layout_Border
	.4byte Route5_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_CeruleanCity
	.byte 2
	.byte 2
	.2byte 0

Route6_Layout_Border::
	.incbin "assets/data.bin", 0x13934, 0x8
Route6_Layout_Blockdata::
	.incbin "assets/data.bin", 0x1393C, 0x780
	.align 2
Route6_Layout::
	.4byte 24
	.4byte 40
	.4byte Route6_Layout_Border
	.4byte Route6_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_VermilionCity
	.byte 2
	.byte 2
	.2byte 0

Route7_Layout_Border::
	.incbin "assets/data.bin", 0x140BC, 0x8
Route7_Layout_Blockdata::
	.incbin "assets/data.bin", 0x140C4, 0x3C0
	.align 2
Route7_Layout::
	.4byte 24
	.4byte 20
	.4byte Route7_Layout_Border
	.4byte Route7_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_CeladonCity
	.byte 2
	.byte 2
	.2byte 0

Route8_Layout_Border::
	.incbin "assets/data.bin", 0x14484, 0x8
Route8_Layout_Blockdata::
	.incbin "assets/data.bin", 0x1448C, 0xB40
	.align 2
Route8_Layout::
	.4byte 72
	.4byte 20
	.4byte Route8_Layout_Border
	.4byte Route8_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_LavenderTown
	.byte 2
	.byte 2
	.2byte 0

Route9_Layout_Border::
	.incbin "assets/data.bin", 0x14FCC, 0x8
Route9_Layout_Blockdata::
	.incbin "assets/data.bin", 0x14FD4, 0xB40
	.align 2
Route9_Layout::
	.4byte 72
	.4byte 20
	.4byte Route9_Layout_Border
	.4byte Route9_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_CeruleanCity
	.byte 2
	.byte 2
	.2byte 0

Route10_Layout_Border::
	.incbin "assets/data.bin", 0x15B14, 0x8
Route10_Layout_Blockdata::
	.incbin "assets/data.bin", 0x15B1C, 0xF00
	.align 2
Route10_Layout::
	.4byte 24
	.4byte 80
	.4byte Route10_Layout_Border
	.4byte Route10_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_LavenderTown
	.byte 2
	.byte 2
	.2byte 0

Route11_Layout_Border::
	.incbin "assets/data.bin", 0x16A1C, 0x8
Route11_Layout_Blockdata::
	.incbin "assets/data.bin", 0x16A24, 0xB40
	.align 2
Route11_Layout::
	.4byte 72
	.4byte 20
	.4byte Route11_Layout_Border
	.4byte Route11_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_VermilionCity
	.byte 2
	.byte 2
	.2byte 0

Route12_Layout_Border::
	.incbin "assets/data.bin", 0x17564, 0x8
Route12_Layout_Blockdata::
	.incbin "assets/data.bin", 0x1756C, 0x1680
	.align 2
Route12_Layout::
	.4byte 24
	.4byte 120
	.4byte Route12_Layout_Border
	.4byte Route12_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_LavenderTown
	.byte 2
	.byte 2
	.2byte 0

Route13_Layout_Border::
	.incbin "assets/data.bin", 0x18BEC, 0x8
Route13_Layout_Blockdata::
	.incbin "assets/data.bin", 0x18BF4, 0xB40
	.align 2
Route13_Layout::
	.4byte 72
	.4byte 20
	.4byte Route13_Layout_Border
	.4byte Route13_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_LavenderTown
	.byte 2
	.byte 2
	.2byte 0

Route14_Layout_Border::
	.incbin "assets/data.bin", 0x19734, 0x8
Route14_Layout_Blockdata::
	.incbin "assets/data.bin", 0x1973C, 0xB40
	.align 2
Route14_Layout::
	.4byte 24
	.4byte 60
	.4byte Route14_Layout_Border
	.4byte Route14_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_LavenderTown
	.byte 2
	.byte 2
	.2byte 0

Route15_Layout_Border::
	.incbin "assets/data.bin", 0x1A27C, 0x8
Route15_Layout_Blockdata::
	.incbin "assets/data.bin", 0x1A284, 0xB40
	.align 2
Route15_Layout::
	.4byte 72
	.4byte 20
	.4byte Route15_Layout_Border
	.4byte Route15_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_FuchsiaCity
	.byte 2
	.byte 2
	.2byte 0

Route16_Layout_Border::
	.incbin "assets/data.bin", 0x1ADC4, 0x8
Route16_Layout_Blockdata::
	.incbin "assets/data.bin", 0x1ADCC, 0x780
	.align 2
Route16_Layout::
	.4byte 48
	.4byte 20
	.4byte Route16_Layout_Border
	.4byte Route16_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_CeladonCity
	.byte 2
	.byte 2
	.2byte 0

Route17_Layout_Border::
	.incbin "assets/data.bin", 0x1B54C, 0x8
Route17_Layout_Blockdata::
	.incbin "assets/data.bin", 0x1B554, 0x1E00
	.align 2
Route17_Layout::
	.4byte 24
	.4byte 160
	.4byte Route17_Layout_Border
	.4byte Route17_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_CeladonCity
	.byte 2
	.byte 2
	.2byte 0

Route18_Layout_Border::
	.incbin "assets/data.bin", 0x1D354, 0x8
Route18_Layout_Blockdata::
	.incbin "assets/data.bin", 0x1D35C, 0x960
	.align 2
Route18_Layout::
	.4byte 60
	.4byte 20
	.4byte Route18_Layout_Border
	.4byte Route18_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_CeladonCity
	.byte 2
	.byte 2
	.2byte 0

Route19_Layout_Border::
	.incbin "assets/data.bin", 0x1DCBC, 0x8
Route19_Layout_Blockdata::
	.incbin "assets/data.bin", 0x1DCC4, 0xB40
	.align 2
Route19_Layout::
	.4byte 24
	.4byte 60
	.4byte Route19_Layout_Border
	.4byte Route19_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_FuchsiaCity
	.byte 2
	.byte 2
	.2byte 0

Route20_Layout_Border::
	.incbin "assets/data.bin", 0x1E804, 0x8
Route20_Layout_Blockdata::
	.incbin "assets/data.bin", 0x1E80C, 0x12C0
	.align 2
Route20_Layout::
	.4byte 120
	.4byte 20
	.4byte Route20_Layout_Border
	.4byte Route20_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_CinnabarIsland
	.byte 2
	.byte 2
	.2byte 0

Route21_North_Layout_Border::
	.incbin "assets/data.bin", 0x1FACC, 0x8
Route21_North_Layout_Blockdata::
	.incbin "assets/data.bin", 0x1FAD4, 0x960
	.align 2
Route21_North_Layout::
	.4byte 24
	.4byte 50
	.4byte Route21_North_Layout_Border
	.4byte Route21_North_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_PalletTown
	.byte 2
	.byte 2
	.2byte 0

Route22_Layout_Border::
	.incbin "assets/data.bin", 0x20434, 0x8
Route22_Layout_Blockdata::
	.incbin "assets/data.bin", 0x2043C, 0x900
	.align 2
Route22_Layout::
	.4byte 48
	.4byte 24
	.4byte Route22_Layout_Border
	.4byte Route22_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_ViridianCity
	.byte 2
	.byte 2
	.2byte 0

Route23_Layout_Border::
	.incbin "assets/data.bin", 0x20D3C, 0x8
Route23_Layout_Blockdata::
	.incbin "assets/data.bin", 0x20D44, 0x1E00
	.align 2
Route23_Layout::
	.4byte 24
	.4byte 160
	.4byte Route23_Layout_Border
	.4byte Route23_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_IndigoPlateau
	.byte 2
	.byte 2
	.2byte 0

Route24_Layout_Border::
	.incbin "assets/data.bin", 0x22B44, 0x8
Route24_Layout_Blockdata::
	.incbin "assets/data.bin", 0x22B4C, 0x780
	.align 2
Route24_Layout::
	.4byte 24
	.4byte 40
	.4byte Route24_Layout_Border
	.4byte Route24_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_CeruleanCity
	.byte 2
	.byte 2
	.2byte 0

Route25_Layout_Border::
	.incbin "assets/data.bin", 0x232CC, 0x8
Route25_Layout_Blockdata::
	.incbin "assets/data.bin", 0x232D4, 0xB40
	.align 2
Route25_Layout::
	.4byte 72
	.4byte 20
	.4byte Route25_Layout_Border
	.4byte Route25_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_CeruleanCity
	.byte 2
	.byte 2
	.2byte 0

MtMoon_1F_Layout_Border::
	.incbin "assets/data.bin", 0x23E14, 0x8
MtMoon_1F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x23E1C, 0xF00
	.align 2
MtMoon_1F_Layout::
	.4byte 48
	.4byte 40
	.4byte MtMoon_1F_Layout_Border
	.4byte MtMoon_1F_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_Cave
	.byte 2
	.byte 2
	.2byte 0

MtMoon_B1F_Layout_Border::
	.incbin "assets/data.bin", 0x24D1C, 0x8
MtMoon_B1F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x24D24, 0xF50
	.align 2
MtMoon_B1F_Layout::
	.4byte 49
	.4byte 40
	.4byte MtMoon_B1F_Layout_Border
	.4byte MtMoon_B1F_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_Cave
	.byte 2
	.byte 2
	.2byte 0

MtMoon_B2F_Layout_Border::
	.incbin "assets/data.bin", 0x25C74, 0x8
MtMoon_B2F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x25C7C, 0xF00
	.align 2
MtMoon_B2F_Layout::
	.4byte 48
	.4byte 40
	.4byte MtMoon_B2F_Layout_Border
	.4byte MtMoon_B2F_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_Cave
	.byte 2
	.byte 2
	.2byte 0

ViridianForest_Layout_Border::
	.incbin "assets/data.bin", 0x26B7C, 0xC
ViridianForest_Layout_Blockdata::
	.incbin "assets/data.bin", 0x26B88, 0x1D1C
	.align 2
ViridianForest_Layout::
	.4byte 54
	.4byte 69
	.4byte ViridianForest_Layout_Border
	.4byte ViridianForest_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_ViridianForest
	.byte 3
	.byte 2
	.2byte 0

SSAnne_Exterior_Layout_Border::
	.incbin "assets/data.bin", 0x288A4, 0x8
SSAnne_Exterior_Layout_Blockdata::
	.incbin "assets/data.bin", 0x288AC, 0x1180
	.align 2
SSAnne_Exterior_Layout::
	.4byte 70
	.4byte 32
	.4byte SSAnne_Exterior_Layout_Border
	.4byte SSAnne_Exterior_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_VermilionCity
	.byte 2
	.byte 2
	.2byte 0

SSAnne_1F_Corridor_Layout_Border::
	.incbin "assets/data.bin", 0x29A2C, 0x8
SSAnne_1F_Corridor_Layout_Blockdata::
	.incbin "assets/data.bin", 0x29A34, 0x516
	.align 2
SSAnne_1F_Corridor_Layout::
	.4byte 31
	.4byte 21
	.4byte SSAnne_1F_Corridor_Layout_Border
	.4byte SSAnne_1F_Corridor_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_SSAnne
	.byte 2
	.byte 2
	.2byte 0

SSAnne_2F_Corridor_Layout_Border::
	.incbin "assets/data.bin", 0x29F4C, 0x8
SSAnne_2F_Corridor_Layout_Blockdata::
	.incbin "assets/data.bin", 0x29F54, 0x440
	.align 2
SSAnne_2F_Corridor_Layout::
	.4byte 34
	.4byte 16
	.4byte SSAnne_2F_Corridor_Layout_Border
	.4byte SSAnne_2F_Corridor_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_SSAnne
	.byte 2
	.byte 2
	.2byte 0

SSAnne_3F_Corridor_Layout_Border::
	.incbin "assets/data.bin", 0x2A394, 0x8
SSAnne_3F_Corridor_Layout_Blockdata::
	.incbin "assets/data.bin", 0x2A39C, 0x134
	.align 2
SSAnne_3F_Corridor_Layout::
	.4byte 22
	.4byte 7
	.4byte SSAnne_3F_Corridor_Layout_Border
	.4byte SSAnne_3F_Corridor_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_SSAnne
	.byte 2
	.byte 2
	.2byte 0

SSAnne_B1F_Corridor_Layout_Border::
	.incbin "assets/data.bin", 0x2A4D0, 0x8
SSAnne_B1F_Corridor_Layout_Blockdata::
	.incbin "assets/data.bin", 0x2A4D8, 0x142
	.align 2
SSAnne_B1F_Corridor_Layout::
	.4byte 23
	.4byte 7
	.4byte SSAnne_B1F_Corridor_Layout_Border
	.4byte SSAnne_B1F_Corridor_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_SSAnne
	.byte 2
	.byte 2
	.2byte 0

SSAnne_Deck_Layout_Border::
	.incbin "assets/data.bin", 0x2A61C, 0x8
SSAnne_Deck_Layout_Blockdata::
	.incbin "assets/data.bin", 0x2A624, 0x390
	.align 2
SSAnne_Deck_Layout::
	.4byte 24
	.4byte 19
	.4byte SSAnne_Deck_Layout_Border
	.4byte SSAnne_Deck_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_SSAnne
	.byte 2
	.byte 2
	.2byte 0

DiglettsCave_B1F_Layout_Border::
	.incbin "assets/data.bin", 0x2A9B4, 0x8
DiglettsCave_B1F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x2A9BC, 0x3520
	.align 2
DiglettsCave_B1F_Layout::
	.4byte 85
	.4byte 80
	.4byte DiglettsCave_B1F_Layout_Border
	.4byte DiglettsCave_B1F_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_DiglettsCave
	.byte 2
	.byte 2
	.2byte 0

VictoryRoad_1F_Layout_Border::
	.incbin "assets/data.bin", 0x2DEDC, 0x8
VictoryRoad_1F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x2DEE4, 0x840
	.align 2
VictoryRoad_1F_Layout::
	.4byte 48
	.4byte 22
	.4byte VictoryRoad_1F_Layout_Border
	.4byte VictoryRoad_1F_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_Cave
	.byte 2
	.byte 2
	.2byte 0

VictoryRoad_2F_Layout_Border::
	.incbin "assets/data.bin", 0x2E724, 0x8
VictoryRoad_2F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x2E72C, 0x8C4
	.align 2
VictoryRoad_2F_Layout::
	.4byte 51
	.4byte 22
	.4byte VictoryRoad_2F_Layout_Border
	.4byte VictoryRoad_2F_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_Cave
	.byte 2
	.byte 2
	.2byte 0

VictoryRoad_3F_Layout_Border::
	.incbin "assets/data.bin", 0x2EFF0, 0x8
VictoryRoad_3F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x2EFF8, 0x7BC
	.align 2
VictoryRoad_3F_Layout::
	.4byte 45
	.4byte 22
	.4byte VictoryRoad_3F_Layout_Border
	.4byte VictoryRoad_3F_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_Cave
	.byte 2
	.byte 2
	.2byte 0

RocketHideout_B1F_Layout_Border::
	.incbin "assets/data.bin", 0x2F7B4, 0x8
RocketHideout_B1F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x2F7BC, 0x770
	.align 2
RocketHideout_B1F_Layout::
	.4byte 28
	.4byte 34
	.4byte RocketHideout_B1F_Layout_Border
	.4byte RocketHideout_B1F_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_SilphCo
	.byte 2
	.byte 2
	.2byte 0

RocketHideout_B2F_Layout_Border::
	.incbin "assets/data.bin", 0x2FF2C, 0x8
RocketHideout_B2F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x2FF34, 0x580
	.align 2
RocketHideout_B2F_Layout::
	.4byte 32
	.4byte 22
	.4byte RocketHideout_B2F_Layout_Border
	.4byte RocketHideout_B2F_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_SilphCo
	.byte 2
	.byte 2
	.2byte 0

RocketHideout_B3F_Layout_Border::
	.incbin "assets/data.bin", 0x304B4, 0x8
RocketHideout_B3F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x304BC, 0x4A4
	.align 2
RocketHideout_B3F_Layout::
	.4byte 22
	.4byte 27
	.4byte RocketHideout_B3F_Layout_Border
	.4byte RocketHideout_B3F_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_SilphCo
	.byte 2
	.byte 2
	.2byte 0

RocketHideout_B4F_Layout_Border::
	.incbin "assets/data.bin", 0x30960, 0x8
RocketHideout_B4F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x30968, 0x4E0
	.align 2
RocketHideout_B4F_Layout::
	.4byte 24
	.4byte 26
	.4byte RocketHideout_B4F_Layout_Border
	.4byte RocketHideout_B4F_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_SilphCo
	.byte 2
	.byte 2
	.2byte 0

SilphCo_1F_Layout_Border::
	.incbin "assets/data.bin", 0x30E48, 0x8
SilphCo_1F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x30E50, 0x630
	.align 2
SilphCo_1F_Layout::
	.4byte 36
	.4byte 22
	.4byte SilphCo_1F_Layout_Border
	.4byte SilphCo_1F_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_SilphCo
	.byte 2
	.byte 2
	.2byte 0

SilphCo_2F_Layout_Border::
	.incbin "assets/data.bin", 0x31480, 0x8
SilphCo_2F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x31488, 0x630
	.align 2
SilphCo_2F_Layout::
	.4byte 36
	.4byte 22
	.4byte SilphCo_2F_Layout_Border
	.4byte SilphCo_2F_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_SilphCo
	.byte 2
	.byte 2
	.2byte 0

SilphCo_3F_Layout_Border::
	.incbin "assets/data.bin", 0x31AB8, 0x8
SilphCo_3F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x31AC0, 0x630
	.align 2
SilphCo_3F_Layout::
	.4byte 36
	.4byte 22
	.4byte SilphCo_3F_Layout_Border
	.4byte SilphCo_3F_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_SilphCo
	.byte 2
	.byte 2
	.2byte 0

SilphCo_4F_Layout_Border::
	.incbin "assets/data.bin", 0x320F0, 0x8
SilphCo_4F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x320F8, 0x630
	.align 2
SilphCo_4F_Layout::
	.4byte 36
	.4byte 22
	.4byte SilphCo_4F_Layout_Border
	.4byte SilphCo_4F_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_SilphCo
	.byte 2
	.byte 2
	.2byte 0

SilphCo_5F_Layout_Border::
	.incbin "assets/data.bin", 0x32728, 0x8
SilphCo_5F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x32730, 0x630
	.align 2
SilphCo_5F_Layout::
	.4byte 36
	.4byte 22
	.4byte SilphCo_5F_Layout_Border
	.4byte SilphCo_5F_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_SilphCo
	.byte 2
	.byte 2
	.2byte 0

SilphCo_6F_Layout_Border::
	.incbin "assets/data.bin", 0x32D60, 0x8
SilphCo_6F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x32D68, 0x49A
	.align 2
SilphCo_6F_Layout::
	.4byte 31
	.4byte 19
	.4byte SilphCo_6F_Layout_Border
	.4byte SilphCo_6F_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_SilphCo
	.byte 2
	.byte 2
	.2byte 0

SilphCo_7F_Layout_Border::
	.incbin "assets/data.bin", 0x33204, 0x8
SilphCo_7F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x3320C, 0x49A
	.align 2
SilphCo_7F_Layout::
	.4byte 31
	.4byte 19
	.4byte SilphCo_7F_Layout_Border
	.4byte SilphCo_7F_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_SilphCo
	.byte 2
	.byte 2
	.2byte 0

SilphCo_8F_Layout_Border::
	.incbin "assets/data.bin", 0x336A8, 0x8
SilphCo_8F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x336B0, 0x49A
	.align 2
SilphCo_8F_Layout::
	.4byte 31
	.4byte 19
	.4byte SilphCo_8F_Layout_Border
	.4byte SilphCo_8F_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_SilphCo
	.byte 2
	.byte 2
	.2byte 0

SilphCo_9F_Layout_Border::
	.incbin "assets/data.bin", 0x33B4C, 0x8
SilphCo_9F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x33B54, 0x49A
	.align 2
SilphCo_9F_Layout::
	.4byte 31
	.4byte 19
	.4byte SilphCo_9F_Layout_Border
	.4byte SilphCo_9F_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_SilphCo
	.byte 2
	.byte 2
	.2byte 0

SilphCo_10F_Layout_Border::
	.incbin "assets/data.bin", 0x33FF0, 0x8
SilphCo_10F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x33FF8, 0x286
	.align 2
SilphCo_10F_Layout::
	.4byte 17
	.4byte 19
	.4byte SilphCo_10F_Layout_Border
	.4byte SilphCo_10F_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_SilphCo
	.byte 2
	.byte 2
	.2byte 0

SilphCo_11F_Layout_Border::
	.incbin "assets/data.bin", 0x34280, 0x8
SilphCo_11F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x34288, 0x2A8
	.align 2
SilphCo_11F_Layout::
	.4byte 17
	.4byte 20
	.4byte SilphCo_11F_Layout_Border
	.4byte SilphCo_11F_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_SilphCo
	.byte 2
	.byte 2
	.2byte 0

PokemonMansion_1F_Layout_Border::
	.incbin "assets/data.bin", 0x34530, 0x8
PokemonMansion_1F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x34538, 0xA64
	.align 2
PokemonMansion_1F_Layout::
	.4byte 38
	.4byte 35
	.4byte PokemonMansion_1F_Layout_Border
	.4byte PokemonMansion_1F_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_PokemonMansion
	.byte 2
	.byte 2
	.2byte 0

PokemonMansion_2F_Layout_Border::
	.incbin "assets/data.bin", 0x34F9C, 0x8
PokemonMansion_2F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x34FA4, 0xB48
	.align 2
PokemonMansion_2F_Layout::
	.4byte 38
	.4byte 38
	.4byte PokemonMansion_2F_Layout_Border
	.4byte PokemonMansion_2F_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_PokemonMansion
	.byte 2
	.byte 2
	.2byte 0

PokemonMansion_3F_Layout_Border::
	.incbin "assets/data.bin", 0x35AEC, 0x8
PokemonMansion_3F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x35AF4, 0xA64
	.align 2
PokemonMansion_3F_Layout::
	.4byte 38
	.4byte 35
	.4byte PokemonMansion_3F_Layout_Border
	.4byte PokemonMansion_3F_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_PokemonMansion
	.byte 2
	.byte 2
	.2byte 0

PokemonMansion_B1F_Layout_Border::
	.incbin "assets/data.bin", 0x36558, 0x8
PokemonMansion_B1F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x36560, 0xA64
	.align 2
PokemonMansion_B1F_Layout::
	.4byte 38
	.4byte 35
	.4byte PokemonMansion_B1F_Layout_Border
	.4byte PokemonMansion_B1F_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_PokemonMansion
	.byte 2
	.byte 2
	.2byte 0

SafariZone_Center_Layout_Border::
	.incbin "assets/data.bin", 0x36FC4, 0xC
SafariZone_Center_Layout_Blockdata::
	.incbin "assets/data.bin", 0x36FD0, 0xE58
	.align 2
SafariZone_Center_Layout::
	.4byte 51
	.4byte 36
	.4byte SafariZone_Center_Layout_Border
	.4byte SafariZone_Center_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_FuchsiaCity
	.byte 3
	.byte 2
	.2byte 0

SafariZone_East_Layout_Border::
	.incbin "assets/data.bin", 0x37E28, 0xC
SafariZone_East_Layout_Blockdata::
	.incbin "assets/data.bin", 0x37E34, 0xEC4
	.align 2
SafariZone_East_Layout::
	.4byte 54
	.4byte 35
	.4byte SafariZone_East_Layout_Border
	.4byte SafariZone_East_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_FuchsiaCity
	.byte 3
	.byte 2
	.2byte 0

SafariZone_North_Layout_Border::
	.incbin "assets/data.bin", 0x38CF8, 0xC
SafariZone_North_Layout_Blockdata::
	.incbin "assets/data.bin", 0x38D04, 0x11D0
	.align 2
SafariZone_North_Layout::
	.4byte 57
	.4byte 40
	.4byte SafariZone_North_Layout_Border
	.4byte SafariZone_North_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_FuchsiaCity
	.byte 3
	.byte 2
	.2byte 0

SafariZone_West_Layout_Border::
	.incbin "assets/data.bin", 0x39ED4, 0xC
SafariZone_West_Layout_Blockdata::
	.incbin "assets/data.bin", 0x39EE0, 0xD80
	.align 2
SafariZone_West_Layout::
	.4byte 48
	.4byte 36
	.4byte SafariZone_West_Layout_Border
	.4byte SafariZone_West_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_FuchsiaCity
	.byte 3
	.byte 2
	.2byte 0

CeruleanCave_1F_Layout_Border::
	.incbin "assets/data.bin", 0x3AC60, 0x8
CeruleanCave_1F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x3AC68, 0x730
	.align 2
CeruleanCave_1F_Layout::
	.4byte 40
	.4byte 23
	.4byte CeruleanCave_1F_Layout_Border
	.4byte CeruleanCave_1F_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_CeruleanCave
	.byte 2
	.byte 2
	.2byte 0

CeruleanCave_2F_Layout_Border::
	.incbin "assets/data.bin", 0x3B398, 0x8
CeruleanCave_2F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x3B3A0, 0x730
	.align 2
CeruleanCave_2F_Layout::
	.4byte 40
	.4byte 23
	.4byte CeruleanCave_2F_Layout_Border
	.4byte CeruleanCave_2F_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_CeruleanCave
	.byte 2
	.byte 2
	.2byte 0

CeruleanCave_B1F_Layout_Border::
	.incbin "assets/data.bin", 0x3BAD0, 0x8
CeruleanCave_B1F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x3BAD8, 0x730
	.align 2
CeruleanCave_B1F_Layout::
	.4byte 40
	.4byte 23
	.4byte CeruleanCave_B1F_Layout_Border
	.4byte CeruleanCave_B1F_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_CeruleanCave
	.byte 2
	.byte 2
	.2byte 0

RockTunnel_1F_Layout_Border::
	.incbin "assets/data.bin", 0x3C208, 0x8
RockTunnel_1F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x3C210, 0xF00
	.align 2
RockTunnel_1F_Layout::
	.4byte 48
	.4byte 40
	.4byte RockTunnel_1F_Layout_Border
	.4byte RockTunnel_1F_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_RockTunnel
	.byte 2
	.byte 2
	.2byte 0

RockTunnel_B1F_Layout_Border::
	.incbin "assets/data.bin", 0x3D110, 0x8
RockTunnel_B1F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x3D118, 0xF00
	.align 2
RockTunnel_B1F_Layout::
	.4byte 48
	.4byte 40
	.4byte RockTunnel_B1F_Layout_Border
	.4byte RockTunnel_B1F_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_RockTunnel
	.byte 2
	.byte 2
	.2byte 0

SeafoamIslands_1F_Layout_Border::
	.incbin "assets/data.bin", 0x3E018, 0x8
SeafoamIslands_1F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x3E020, 0x720
	.align 2
SeafoamIslands_1F_Layout::
	.4byte 38
	.4byte 24
	.4byte SeafoamIslands_1F_Layout_Border
	.4byte SeafoamIslands_1F_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_SeafoamIslands
	.byte 2
	.byte 2
	.2byte 0

SeafoamIslands_B1F_Layout_Border::
	.incbin "assets/data.bin", 0x3E740, 0x8
SeafoamIslands_B1F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x3E748, 0x6D4
	.align 2
SeafoamIslands_B1F_Layout::
	.4byte 38
	.4byte 23
	.4byte SeafoamIslands_B1F_Layout_Border
	.4byte SeafoamIslands_B1F_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_SeafoamIslands
	.byte 2
	.byte 2
	.2byte 0

SeafoamIslands_B2F_Layout_Border::
	.incbin "assets/data.bin", 0x3EE1C, 0x8
SeafoamIslands_B2F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x3EE24, 0x720
	.align 2
SeafoamIslands_B2F_Layout::
	.4byte 38
	.4byte 24
	.4byte SeafoamIslands_B2F_Layout_Border
	.4byte SeafoamIslands_B2F_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_SeafoamIslands
	.byte 2
	.byte 2
	.2byte 0

SeafoamIslands_B3F_Layout_Border::
	.incbin "assets/data.bin", 0x3F544, 0x8
SeafoamIslands_B3F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x3F54C, 0x720
	.align 2
SeafoamIslands_B3F_Layout::
	.4byte 38
	.4byte 24
	.4byte SeafoamIslands_B3F_Layout_Border
	.4byte SeafoamIslands_B3F_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_SeafoamIslands
	.byte 2
	.byte 2
	.2byte 0

SeafoamIslands_B4F_Layout_Border::
	.incbin "assets/data.bin", 0x3FC6C, 0x8
SeafoamIslands_B4F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x3FC74, 0x720
	.align 2
SeafoamIslands_B4F_Layout::
	.4byte 38
	.4byte 24
	.4byte SeafoamIslands_B4F_Layout_Border
	.4byte SeafoamIslands_B4F_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_SeafoamIslands
	.byte 2
	.byte 2
	.2byte 0

PokemonTower_1F_Layout_Border::
	.incbin "assets/data.bin", 0x40394, 0x8
PokemonTower_1F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x4039C, 0x3C0
	.align 2
PokemonTower_1F_Layout::
	.4byte 24
	.4byte 20
	.4byte PokemonTower_1F_Layout_Border
	.4byte PokemonTower_1F_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_PokemonTower
	.byte 2
	.byte 2
	.2byte 0

PokemonTower_2F_Layout_Border::
	.incbin "assets/data.bin", 0x4075C, 0x8
PokemonTower_2F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x40764, 0x3C0
	.align 2
PokemonTower_2F_Layout::
	.4byte 24
	.4byte 20
	.4byte PokemonTower_2F_Layout_Border
	.4byte PokemonTower_2F_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_PokemonTower
	.byte 2
	.byte 2
	.2byte 0

PokemonTower_3F_Layout_Border::
	.incbin "assets/data.bin", 0x40B24, 0x8
PokemonTower_3F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x40B2C, 0x3C0
	.align 2
PokemonTower_3F_Layout::
	.4byte 24
	.4byte 20
	.4byte PokemonTower_3F_Layout_Border
	.4byte PokemonTower_3F_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_PokemonTower
	.byte 2
	.byte 2
	.2byte 0

PokemonTower_4F_Layout_Border::
	.incbin "assets/data.bin", 0x40EEC, 0x8
PokemonTower_4F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x40EF4, 0x3C0
	.align 2
PokemonTower_4F_Layout::
	.4byte 24
	.4byte 20
	.4byte PokemonTower_4F_Layout_Border
	.4byte PokemonTower_4F_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_PokemonTower
	.byte 2
	.byte 2
	.2byte 0

PokemonTower_5F_Layout_Border::
	.incbin "assets/data.bin", 0x412B4, 0x8
PokemonTower_5F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x412BC, 0x3C0
	.align 2
PokemonTower_5F_Layout::
	.4byte 24
	.4byte 20
	.4byte PokemonTower_5F_Layout_Border
	.4byte PokemonTower_5F_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_PokemonTower
	.byte 2
	.byte 2
	.2byte 0

PokemonTower_6F_Layout_Border::
	.incbin "assets/data.bin", 0x4167C, 0x8
PokemonTower_6F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x41684, 0x3C0
	.align 2
PokemonTower_6F_Layout::
	.4byte 24
	.4byte 20
	.4byte PokemonTower_6F_Layout_Border
	.4byte PokemonTower_6F_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_PokemonTower
	.byte 2
	.byte 2
	.2byte 0

PokemonTower_7F_Layout_Border::
	.incbin "assets/data.bin", 0x41A44, 0x8
PokemonTower_7F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x41A4C, 0x3C0
	.align 2
PokemonTower_7F_Layout::
	.4byte 24
	.4byte 20
	.4byte PokemonTower_7F_Layout_Border
	.4byte PokemonTower_7F_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_PokemonTower
	.byte 2
	.byte 2
	.2byte 0

PowerPlant_Layout_Border::
	.incbin "assets/data.bin", 0x41E0C, 0x8
PowerPlant_Layout_Blockdata::
	.incbin "assets/data.bin", 0x41E14, 0xF50
	.align 2
PowerPlant_Layout::
	.4byte 49
	.4byte 40
	.4byte PowerPlant_Layout_Border
	.4byte PowerPlant_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_PowerPlant
	.byte 2
	.byte 2
	.2byte 0

Route25_SeaCottage_Layout_Border::
	.incbin "assets/data.bin", 0x42D64, 0x8
Route25_SeaCottage_Layout_Blockdata::
	.incbin "assets/data.bin", 0x42D6C, 0x14A
	.align 2
Route25_SeaCottage_Layout::
	.4byte 15
	.4byte 11
	.4byte Route25_SeaCottage_Layout_Border
	.4byte Route25_SeaCottage_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_SeaCottage
	.byte 2
	.byte 2
	.2byte 0

SSAnne_Kitchen_Layout_Border::
	.incbin "assets/data.bin", 0x42EB8, 0x8
SSAnne_Kitchen_Layout_Blockdata::
	.incbin "assets/data.bin", 0x42EC0, 0x1C0
	.align 2
SSAnne_Kitchen_Layout::
	.4byte 16
	.4byte 14
	.4byte SSAnne_Kitchen_Layout_Border
	.4byte SSAnne_Kitchen_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_SSAnne
	.byte 2
	.byte 2
	.2byte 0

SSAnne_CaptainsOffice_Layout_Border::
	.incbin "assets/data.bin", 0x43080, 0x8
SSAnne_CaptainsOffice_Layout_Blockdata::
	.incbin "assets/data.bin", 0x43088, 0xB4
	.align 2
SSAnne_CaptainsOffice_Layout::
	.4byte 9
	.4byte 10
	.4byte SSAnne_CaptainsOffice_Layout_Border
	.4byte SSAnne_CaptainsOffice_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_SSAnne
	.byte 2
	.byte 2
	.2byte 0

UndergroundPath_Entrance_Layout_Border::
	.incbin "assets/data.bin", 0x4313C, 0x8
UndergroundPath_Entrance_Layout_Blockdata::
	.incbin "assets/data.bin", 0x43144, 0x104
	.align 2
UndergroundPath_Entrance_Layout::
	.4byte 13
	.4byte 10
	.4byte UndergroundPath_Entrance_Layout_Border
	.4byte UndergroundPath_Entrance_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_GenericBuilding2
	.byte 2
	.byte 2
	.2byte 0

UndergroundPath_EastWestTunnel_Layout_Border::
	.incbin "assets/data.bin", 0x43248, 0x8
UndergroundPath_EastWestTunnel_Layout_Blockdata::
	.incbin "assets/data.bin", 0x43250, 0x460
	.align 2
UndergroundPath_EastWestTunnel_Layout::
	.4byte 80
	.4byte 7
	.4byte UndergroundPath_EastWestTunnel_Layout_Border
	.4byte UndergroundPath_EastWestTunnel_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_UndergroundPath
	.byte 2
	.byte 2
	.2byte 0

UndergroundPath_NorthSouthTunnel_Layout_Border::
	.incbin "assets/data.bin", 0x436B0, 0x8
UndergroundPath_NorthSouthTunnel_Layout_Blockdata::
	.incbin "assets/data.bin", 0x436B8, 0x3F0
	.align 2
UndergroundPath_NorthSouthTunnel_Layout::
	.4byte 8
	.4byte 63
	.4byte UndergroundPath_NorthSouthTunnel_Layout_Border
	.4byte UndergroundPath_NorthSouthTunnel_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_UndergroundPath
	.byte 2
	.byte 2
	.2byte 0

Route12_NorthEntrance_1F_Layout_Border::
	.incbin "assets/data.bin", 0x43AA8, 0x8
Route12_NorthEntrance_1F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x43AB0, 0x11E
	.align 2
Route12_NorthEntrance_1F_Layout::
	.4byte 11
	.4byte 13
	.4byte Route12_NorthEntrance_1F_Layout_Border
	.4byte Route12_NorthEntrance_1F_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_GenericBuilding2
	.byte 2
	.byte 2
	.2byte 0

SSAnne_Room1_Layout_Border::
	.incbin "assets/data.bin", 0x43BD0, 0x8
SSAnne_Room1_Layout_Blockdata::
	.incbin "assets/data.bin", 0x43BD8, 0x60
	.align 2
SSAnne_Room1_Layout::
	.4byte 6
	.4byte 8
	.4byte SSAnne_Room1_Layout_Border
	.4byte SSAnne_Room1_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_SSAnne
	.byte 2
	.byte 2
	.2byte 0

SSAnne_Room2_Layout_Border::
	.incbin "assets/data.bin", 0x43C38, 0x8
SSAnne_Room2_Layout_Blockdata::
	.incbin "assets/data.bin", 0x43C40, 0x6C
	.align 2
SSAnne_Room2_Layout::
	.4byte 6
	.4byte 9
	.4byte SSAnne_Room2_Layout_Border
	.4byte SSAnne_Room2_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_SSAnne
	.byte 2
	.byte 2
	.2byte 0

CeladonCity_DepartmentStore_Elevator_Layout_Border::
	.incbin "assets/data.bin", 0x43CAC, 0x8
CeladonCity_DepartmentStore_Elevator_Layout_Blockdata::
	.incbin "assets/data.bin", 0x43CB4, 0x46
	.align 2
CeladonCity_DepartmentStore_Elevator_Layout::
	.4byte 5
	.4byte 7
	.4byte CeladonCity_DepartmentStore_Elevator_Layout_Border
	.4byte CeladonCity_DepartmentStore_Elevator_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_SilphCo
	.byte 2
	.byte 2
	.2byte 0

PewterCity_Museum_1F_Layout_Border::
	.incbin "assets/data.bin", 0x43CFC, 0x8
PewterCity_Museum_1F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x43D04, 0x268
	.align 2
PewterCity_Museum_1F_Layout::
	.4byte 28
	.4byte 11
	.4byte PewterCity_Museum_1F_Layout_Border
	.4byte PewterCity_Museum_1F_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_Museum
	.byte 2
	.byte 2
	.2byte 0

PewterCity_Museum_2F_Layout_Border::
	.incbin "assets/data.bin", 0x43F6C, 0x8
PewterCity_Museum_2F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x43F74, 0x17C
	.align 2
PewterCity_Museum_2F_Layout::
	.4byte 19
	.4byte 10
	.4byte PewterCity_Museum_2F_Layout_Border
	.4byte PewterCity_Museum_2F_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_Museum
	.byte 2
	.byte 2
	.2byte 0

CeruleanCity_House2_Layout_Border::
	.incbin "assets/data.bin", 0x440F0, 0x8
CeruleanCity_House2_Layout_Blockdata::
	.incbin "assets/data.bin", 0x440F8, 0xB4
	.align 2
CeruleanCity_House2_Layout::
	.4byte 10
	.4byte 9
	.4byte CeruleanCity_House2_Layout_Border
	.4byte CeruleanCity_House2_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_BurgledHouse
	.byte 2
	.byte 2
	.2byte 0

CeruleanCity_House1_Layout_Border::
	.incbin "assets/data.bin", 0x441AC, 0x8
CeruleanCity_House1_Layout_Blockdata::
	.incbin "assets/data.bin", 0x441B4, 0xC8
	.align 2
CeruleanCity_House1_Layout::
	.4byte 10
	.4byte 10
	.4byte CeruleanCity_House1_Layout_Border
	.4byte CeruleanCity_House1_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_GenericBuilding2
	.byte 2
	.byte 2
	.2byte 0

CeladonCity_Condominiums_1F_Layout_Border::
	.incbin "assets/data.bin", 0x4427C, 0x8
CeladonCity_Condominiums_1F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x44284, 0x258
	.align 2
CeladonCity_Condominiums_1F_Layout::
	.4byte 15
	.4byte 20
	.4byte CeladonCity_Condominiums_1F_Layout_Border
	.4byte CeladonCity_Condominiums_1F_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_Condominiums
	.byte 2
	.byte 2
	.2byte 0

CeladonCity_Condominiums_2F_Layout_Border::
	.incbin "assets/data.bin", 0x444DC, 0x8
CeladonCity_Condominiums_2F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x444E4, 0x258
	.align 2
CeladonCity_Condominiums_2F_Layout::
	.4byte 15
	.4byte 20
	.4byte CeladonCity_Condominiums_2F_Layout_Border
	.4byte CeladonCity_Condominiums_2F_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_Condominiums
	.byte 2
	.byte 2
	.2byte 0

CeladonCity_Condominiums_3F_Layout_Border::
	.incbin "assets/data.bin", 0x4473C, 0x8
CeladonCity_Condominiums_3F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x44744, 0x258
	.align 2
CeladonCity_Condominiums_3F_Layout::
	.4byte 15
	.4byte 20
	.4byte CeladonCity_Condominiums_3F_Layout_Border
	.4byte CeladonCity_Condominiums_3F_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_Condominiums
	.byte 2
	.byte 2
	.2byte 0

CeladonCity_Condominiums_Roof_Layout_Border::
	.incbin "assets/data.bin", 0x4499C, 0x8
CeladonCity_Condominiums_Roof_Layout_Blockdata::
	.incbin "assets/data.bin", 0x449A4, 0x284
	.align 2
CeladonCity_Condominiums_Roof_Layout::
	.4byte 14
	.4byte 23
	.4byte CeladonCity_Condominiums_Roof_Layout_Border
	.4byte CeladonCity_Condominiums_Roof_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_Condominiums
	.byte 2
	.byte 2
	.2byte 0

CeladonCity_Condominiums_RoofRoom_Layout_Border::
	.incbin "assets/data.bin", 0x44C28, 0x8
CeladonCity_Condominiums_RoofRoom_Layout_Blockdata::
	.incbin "assets/data.bin", 0x44C30, 0xB4
	.align 2
CeladonCity_Condominiums_RoofRoom_Layout::
	.4byte 10
	.4byte 9
	.4byte CeladonCity_Condominiums_RoofRoom_Layout_Border
	.4byte CeladonCity_Condominiums_RoofRoom_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_School
	.byte 2
	.byte 2
	.2byte 0

CeladonCity_GameCorner_PrizeRoom_Layout_Border::
	.incbin "assets/data.bin", 0x44CE4, 0x8
CeladonCity_GameCorner_PrizeRoom_Layout_Blockdata::
	.incbin "assets/data.bin", 0x44CEC, 0xB4
	.align 2
CeladonCity_GameCorner_PrizeRoom_Layout::
	.4byte 9
	.4byte 10
	.4byte CeladonCity_GameCorner_PrizeRoom_Layout_Border
	.4byte CeladonCity_GameCorner_PrizeRoom_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_GameCorner
	.byte 2
	.byte 2
	.2byte 0

CeladonCity_Restaurant_Layout_Border::
	.incbin "assets/data.bin", 0x44DA0, 0x8
CeladonCity_Restaurant_Layout_Blockdata::
	.incbin "assets/data.bin", 0x44DA8, 0x14A
	.align 2
CeladonCity_Restaurant_Layout::
	.4byte 15
	.4byte 11
	.4byte CeladonCity_Restaurant_Layout_Border
	.4byte CeladonCity_Restaurant_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_RestaurantHotel
	.byte 2
	.byte 2
	.2byte 0

CeladonCity_Hotel_Layout_Border::
	.incbin "assets/data.bin", 0x44EF4, 0x8
CeladonCity_Hotel_Layout_Blockdata::
	.incbin "assets/data.bin", 0x44EFC, 0x176
	.align 2
CeladonCity_Hotel_Layout::
	.4byte 17
	.4byte 11
	.4byte CeladonCity_Hotel_Layout_Border
	.4byte CeladonCity_Hotel_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_RestaurantHotel
	.byte 2
	.byte 2
	.2byte 0

CeladonCity_DepartmentStore_1F_Layout_Border::
	.incbin "assets/data.bin", 0x45074, 0x8
CeladonCity_DepartmentStore_1F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x4507C, 0x1A0
	.align 2
CeladonCity_DepartmentStore_1F_Layout::
	.4byte 13
	.4byte 16
	.4byte CeladonCity_DepartmentStore_1F_Layout_Border
	.4byte CeladonCity_DepartmentStore_1F_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_DepartmentStore
	.byte 2
	.byte 2
	.2byte 0

CeladonCity_DepartmentStore_2F_Layout_Border::
	.incbin "assets/data.bin", 0x4521C, 0x8
CeladonCity_DepartmentStore_2F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x45224, 0x186
	.align 2
CeladonCity_DepartmentStore_2F_Layout::
	.4byte 13
	.4byte 15
	.4byte CeladonCity_DepartmentStore_2F_Layout_Border
	.4byte CeladonCity_DepartmentStore_2F_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_DepartmentStore
	.byte 2
	.byte 2
	.2byte 0

CeladonCity_DepartmentStore_3F_Layout_Border::
	.incbin "assets/data.bin", 0x453AC, 0x8
CeladonCity_DepartmentStore_3F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x453B4, 0x186
	.align 2
CeladonCity_DepartmentStore_3F_Layout::
	.4byte 13
	.4byte 15
	.4byte CeladonCity_DepartmentStore_3F_Layout_Border
	.4byte CeladonCity_DepartmentStore_3F_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_DepartmentStore
	.byte 2
	.byte 2
	.2byte 0

CeladonCity_DepartmentStore_4F_Layout_Border::
	.incbin "assets/data.bin", 0x4553C, 0x8
CeladonCity_DepartmentStore_4F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x45544, 0x186
	.align 2
CeladonCity_DepartmentStore_4F_Layout::
	.4byte 13
	.4byte 15
	.4byte CeladonCity_DepartmentStore_4F_Layout_Border
	.4byte CeladonCity_DepartmentStore_4F_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_DepartmentStore
	.byte 2
	.byte 2
	.2byte 0

CeladonCity_DepartmentStore_5F_Layout_Border::
	.incbin "assets/data.bin", 0x456CC, 0x8
CeladonCity_DepartmentStore_5F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x456D4, 0x186
	.align 2
CeladonCity_DepartmentStore_5F_Layout::
	.4byte 13
	.4byte 15
	.4byte CeladonCity_DepartmentStore_5F_Layout_Border
	.4byte CeladonCity_DepartmentStore_5F_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_DepartmentStore
	.byte 2
	.byte 2
	.2byte 0

CeladonCity_DepartmentStore_Roof_Layout_Border::
	.incbin "assets/data.bin", 0x4585C, 0x8
CeladonCity_DepartmentStore_Roof_Layout_Blockdata::
	.incbin "assets/data.bin", 0x45864, 0x214
	.align 2
CeladonCity_DepartmentStore_Roof_Layout::
	.4byte 19
	.4byte 14
	.4byte CeladonCity_DepartmentStore_Roof_Layout_Border
	.4byte CeladonCity_DepartmentStore_Roof_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_DepartmentStore
	.byte 2
	.byte 2
	.2byte 0

SafariZone_RestHouse_Layout_Border::
	.incbin "assets/data.bin", 0x45A78, 0x8
SafariZone_RestHouse_Layout_Blockdata::
	.incbin "assets/data.bin", 0x45A80, 0x11E
	.align 2
SafariZone_RestHouse_Layout::
	.4byte 13
	.4byte 11
	.4byte SafariZone_RestHouse_Layout_Border
	.4byte SafariZone_RestHouse_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_SafariZoneBuilding
	.byte 2
	.byte 2
	.2byte 0

SafariZone_SecretHouse_Layout_Border::
	.incbin "assets/data.bin", 0x45BA0, 0x8
SafariZone_SecretHouse_Layout_Blockdata::
	.incbin "assets/data.bin", 0x45BA8, 0x11E
	.align 2
SafariZone_SecretHouse_Layout::
	.4byte 13
	.4byte 11
	.4byte SafariZone_SecretHouse_Layout_Border
	.4byte SafariZone_SecretHouse_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_SafariZoneBuilding
	.byte 2
	.byte 2
	.2byte 0

FuchsiaCity_SafariZone_Office_Layout_Border::
	.incbin "assets/data.bin", 0x45CC8, 0x8
FuchsiaCity_SafariZone_Office_Layout_Blockdata::
	.incbin "assets/data.bin", 0x45CD0, 0x1B8
	.align 2
FuchsiaCity_SafariZone_Office_Layout::
	.4byte 20
	.4byte 11
	.4byte FuchsiaCity_SafariZone_Office_Layout_Border
	.4byte FuchsiaCity_SafariZone_Office_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_SafariZoneBuilding
	.byte 2
	.byte 2
	.2byte 0

FuchsiaCity_WardensHouse_Layout_Border::
	.incbin "assets/data.bin", 0x45E88, 0x8
FuchsiaCity_WardensHouse_Layout_Blockdata::
	.incbin "assets/data.bin", 0x45E90, 0x11E
	.align 2
FuchsiaCity_WardensHouse_Layout::
	.4byte 13
	.4byte 11
	.4byte FuchsiaCity_WardensHouse_Layout_Border
	.4byte FuchsiaCity_WardensHouse_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_Museum
	.byte 2
	.byte 2
	.2byte 0

FuchsiaCity_House2_Layout_Border::
	.incbin "assets/data.bin", 0x45FB0, 0x8
FuchsiaCity_House2_Layout_Blockdata::
	.incbin "assets/data.bin", 0x45FB8, 0xC8
	.align 2
FuchsiaCity_House2_Layout::
	.4byte 10
	.4byte 10
	.4byte FuchsiaCity_House2_Layout_Border
	.4byte FuchsiaCity_House2_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_Museum
	.byte 2
	.byte 2
	.2byte 0

CinnabarIsland_PokemonLab_Entrance_Layout_Border::
	.incbin "assets/data.bin", 0x46080, 0x8
CinnabarIsland_PokemonLab_Entrance_Layout_Blockdata::
	.incbin "assets/data.bin", 0x46088, 0x268
	.align 2
CinnabarIsland_PokemonLab_Entrance_Layout::
	.4byte 28
	.4byte 11
	.4byte CinnabarIsland_PokemonLab_Entrance_Layout_Border
	.4byte CinnabarIsland_PokemonLab_Entrance_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_Lab
	.byte 2
	.byte 2
	.2byte 0

CinnabarIsland_PokemonLab_Lounge_Layout_Border::
	.incbin "assets/data.bin", 0x462F0, 0x8
CinnabarIsland_PokemonLab_Lounge_Layout_Blockdata::
	.incbin "assets/data.bin", 0x462F8, 0x14A
	.align 2
CinnabarIsland_PokemonLab_Lounge_Layout::
	.4byte 15
	.4byte 11
	.4byte CinnabarIsland_PokemonLab_Lounge_Layout_Border
	.4byte CinnabarIsland_PokemonLab_Lounge_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_Lab
	.byte 2
	.byte 2
	.2byte 0

CinnabarIsland_PokemonLab_ResearchRoom_Layout_Border::
	.incbin "assets/data.bin", 0x46444, 0x8
CinnabarIsland_PokemonLab_ResearchRoom_Layout_Blockdata::
	.incbin "assets/data.bin", 0x4644C, 0x14A
	.align 2
CinnabarIsland_PokemonLab_ResearchRoom_Layout::
	.4byte 15
	.4byte 11
	.4byte CinnabarIsland_PokemonLab_ResearchRoom_Layout_Border
	.4byte CinnabarIsland_PokemonLab_ResearchRoom_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_Lab
	.byte 2
	.byte 2
	.2byte 0

CinnabarIsland_PokemonLab_ExperimentRoom_Layout_Border::
	.incbin "assets/data.bin", 0x46598, 0x8
CinnabarIsland_PokemonLab_ExperimentRoom_Layout_Blockdata::
	.incbin "assets/data.bin", 0x465A0, 0x14A
	.align 2
CinnabarIsland_PokemonLab_ExperimentRoom_Layout::
	.4byte 15
	.4byte 11
	.4byte CinnabarIsland_PokemonLab_ExperimentRoom_Layout_Border
	.4byte CinnabarIsland_PokemonLab_ExperimentRoom_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_Lab
	.byte 2
	.byte 2
	.2byte 0

SaffronCity_Layout_Border::
	.incbin "assets/data.bin", 0x466EC, 0x8
SaffronCity_Layout_Blockdata::
	.incbin "assets/data.bin", 0x466F4, 0x1C5C
	.align 2
SaffronCity_Layout::
	.4byte 66
	.4byte 55
	.4byte SaffronCity_Layout_Border
	.4byte SaffronCity_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_SaffronCity
	.byte 2
	.byte 2
	.2byte 0

SaffronCity_NorthSouthEntrance_Layout_Border::
	.incbin "assets/data.bin", 0x48350, 0x8
SaffronCity_NorthSouthEntrance_Layout_Blockdata::
	.incbin "assets/data.bin", 0x48358, 0xC6
	.align 2
SaffronCity_NorthSouthEntrance_Layout::
	.4byte 9
	.4byte 11
	.4byte SaffronCity_NorthSouthEntrance_Layout_Border
	.4byte SaffronCity_NorthSouthEntrance_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_GenericBuilding2
	.byte 2
	.byte 2
	.2byte 0

SaffronCity_EastWestEntrance_Layout_Border::
	.incbin "assets/data.bin", 0x48420, 0x8
SaffronCity_EastWestEntrance_Layout_Blockdata::
	.incbin "assets/data.bin", 0x48428, 0xEA
	.align 2
SaffronCity_EastWestEntrance_Layout::
	.4byte 13
	.4byte 9
	.4byte SaffronCity_EastWestEntrance_Layout_Border
	.4byte SaffronCity_EastWestEntrance_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_GenericBuilding2
	.byte 2
	.byte 2
	.2byte 0

DiglettsCave_NorthEntrance_Layout_Border::
	.incbin "assets/data.bin", 0x48514, 0x8
DiglettsCave_NorthEntrance_Layout_Blockdata::
	.incbin "assets/data.bin", 0x4851C, 0xA0
	.align 2
DiglettsCave_NorthEntrance_Layout::
	.4byte 10
	.4byte 8
	.4byte DiglettsCave_NorthEntrance_Layout_Border
	.4byte DiglettsCave_NorthEntrance_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_DiglettsCave
	.byte 2
	.byte 2
	.2byte 0

DiglettsCave_SouthEntrance_Layout_Border::
	.incbin "assets/data.bin", 0x485BC, 0x8
DiglettsCave_SouthEntrance_Layout_Blockdata::
	.incbin "assets/data.bin", 0x485C4, 0xA0
	.align 2
DiglettsCave_SouthEntrance_Layout::
	.4byte 10
	.4byte 8
	.4byte DiglettsCave_SouthEntrance_Layout_Border
	.4byte DiglettsCave_SouthEntrance_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_DiglettsCave
	.byte 2
	.byte 2
	.2byte 0

IndigoPlateau_PokemonCenter_1F_Layout_Border::
	.incbin "assets/data.bin", 0x48664, 0x8
IndigoPlateau_PokemonCenter_1F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x4866C, 0x384
	.align 2
IndigoPlateau_PokemonCenter_1F_Layout::
	.4byte 25
	.4byte 18
	.4byte IndigoPlateau_PokemonCenter_1F_Layout_Border
	.4byte IndigoPlateau_PokemonCenter_1F_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_PokemonCenter
	.byte 2
	.byte 2
	.2byte 0

PokemonLeague_LoreleisRoom_Layout_Border::
	.incbin "assets/data.bin", 0x489F0, 0x8
PokemonLeague_LoreleisRoom_Layout_Blockdata::
	.incbin "assets/data.bin", 0x489F8, 0x152
	.align 2
PokemonLeague_LoreleisRoom_Layout::
	.4byte 13
	.4byte 13
	.4byte PokemonLeague_LoreleisRoom_Layout_Border
	.4byte PokemonLeague_LoreleisRoom_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_PokemonLeague
	.byte 2
	.byte 2
	.2byte 0

PokemonLeague_BrunosRoom_Layout_Border::
	.incbin "assets/data.bin", 0x48B4C, 0x8
PokemonLeague_BrunosRoom_Layout_Blockdata::
	.incbin "assets/data.bin", 0x48B54, 0x152
	.align 2
PokemonLeague_BrunosRoom_Layout::
	.4byte 13
	.4byte 13
	.4byte PokemonLeague_BrunosRoom_Layout_Border
	.4byte PokemonLeague_BrunosRoom_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_PokemonLeague
	.byte 2
	.byte 2
	.2byte 0

PokemonLeague_AgathasRoom_Layout_Border::
	.incbin "assets/data.bin", 0x48CA8, 0x8
PokemonLeague_AgathasRoom_Layout_Blockdata::
	.incbin "assets/data.bin", 0x48CB0, 0x152
	.align 2
PokemonLeague_AgathasRoom_Layout::
	.4byte 13
	.4byte 13
	.4byte PokemonLeague_AgathasRoom_Layout_Border
	.4byte PokemonLeague_AgathasRoom_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_PokemonLeague
	.byte 2
	.byte 2
	.2byte 0

PokemonLeague_LancesRoom_Layout_Border::
	.incbin "assets/data.bin", 0x48E04, 0x8
PokemonLeague_LancesRoom_Layout_Blockdata::
	.incbin "assets/data.bin", 0x48E0C, 0x540
	.align 2
PokemonLeague_LancesRoom_Layout::
	.4byte 28
	.4byte 24
	.4byte PokemonLeague_LancesRoom_Layout_Border
	.4byte PokemonLeague_LancesRoom_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_PokemonLeague
	.byte 2
	.byte 2
	.2byte 0

PokemonLeague_ChampionsRoom_Layout_Border::
	.incbin "assets/data.bin", 0x4934C, 0x8
PokemonLeague_ChampionsRoom_Layout_Blockdata::
	.incbin "assets/data.bin", 0x49354, 0x208
	.align 2
PokemonLeague_ChampionsRoom_Layout::
	.4byte 13
	.4byte 20
	.4byte PokemonLeague_ChampionsRoom_Layout_Border
	.4byte PokemonLeague_ChampionsRoom_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_PokemonLeague
	.byte 2
	.byte 2
	.2byte 0

PokemonLeague_HallOfFame_Layout_Border::
	.incbin "assets/data.bin", 0x4955C, 0x8
PokemonLeague_HallOfFame_Layout_Blockdata::
	.incbin "assets/data.bin", 0x49564, 0x11E
	.align 2
PokemonLeague_HallOfFame_Layout::
	.4byte 11
	.4byte 13
	.4byte PokemonLeague_HallOfFame_Layout_Border
	.4byte PokemonLeague_HallOfFame_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_HallOfFame
	.byte 2
	.byte 2
	.2byte 0

Route21_South_Layout_Border::
	.incbin "assets/data.bin", 0x49684, 0x8
Route21_South_Layout_Blockdata::
	.incbin "assets/data.bin", 0x4968C, 0x960
	.align 2
Route21_South_Layout::
	.4byte 24
	.4byte 50
	.4byte Route21_South_Layout_Border
	.4byte Route21_South_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_CinnabarIsland
	.byte 2
	.byte 2
	.2byte 0

Entrance_2F_Layout_Border::
	.incbin "assets/data.bin", 0x49FEC, 0x8
Entrance_2F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x49FF4, 0x11E
	.align 2
Entrance_2F_Layout::
	.4byte 13
	.4byte 11
	.4byte Entrance_2F_Layout_Border
	.4byte Entrance_2F_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_GenericBuilding2
	.byte 2
	.byte 2
	.2byte 0

Route2_Entrance_Layout_Border::
	.incbin "assets/data.bin", 0x4A114, 0x8
Route2_Entrance_Layout_Blockdata::
	.incbin "assets/data.bin", 0x4A11C, 0x168
	.align 2
Route2_Entrance_Layout::
	.4byte 15
	.4byte 12
	.4byte Route2_Entrance_Layout_Border
	.4byte Route2_Entrance_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_GenericBuilding2
	.byte 2
	.byte 2
	.2byte 0

Route22_NorthEntrance_Layout_Border::
	.incbin "assets/data.bin", 0x4A284, 0x8
Route22_NorthEntrance_Layout_Blockdata::
	.incbin "assets/data.bin", 0x4A28C, 0x168
	.align 2
Route22_NorthEntrance_Layout::
	.4byte 15
	.4byte 12
	.4byte Route22_NorthEntrance_Layout_Border
	.4byte Route22_NorthEntrance_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_GenericBuilding2
	.byte 2
	.byte 2
	.2byte 0

Route16_NorthEntrance_1F_Layout_Border::
	.incbin "assets/data.bin", 0x4A3F4, 0x8
Route16_NorthEntrance_1F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x4A3FC, 0x1D4
	.align 2
Route16_NorthEntrance_1F_Layout::
	.4byte 13
	.4byte 18
	.4byte Route16_NorthEntrance_1F_Layout_Border
	.4byte Route16_NorthEntrance_1F_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_GenericBuilding2
	.byte 2
	.byte 2
	.2byte 0

Entrance_1F_Layout_Border::
	.incbin "assets/data.bin", 0x4A5D0, 0x8
Entrance_1F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x4A5D8, 0x138
	.align 2
Entrance_1F_Layout::
	.4byte 13
	.4byte 12
	.4byte Entrance_1F_Layout_Border
	.4byte Entrance_1F_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_GenericBuilding2
	.byte 2
	.byte 2
	.2byte 0

RocketHideout_Elevator_Layout_Border::
	.incbin "assets/data.bin", 0x4A710, 0x8
RocketHideout_Elevator_Layout_Blockdata::
	.incbin "assets/data.bin", 0x4A718, 0x46
	.align 2
RocketHideout_Elevator_Layout::
	.4byte 5
	.4byte 7
	.4byte RocketHideout_Elevator_Layout_Border
	.4byte RocketHideout_Elevator_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_SilphCo
	.byte 2
	.byte 2
	.2byte 0

SaffronCity_CopycatsHouse_1F_Layout_Border::
	.incbin "assets/data.bin", 0x4A760, 0x8
SaffronCity_CopycatsHouse_1F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x4A768, 0x104
	.align 2
SaffronCity_CopycatsHouse_1F_Layout::
	.4byte 13
	.4byte 10
	.4byte SaffronCity_CopycatsHouse_1F_Layout_Border
	.4byte SaffronCity_CopycatsHouse_1F_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_GenericBuilding1
	.byte 2
	.byte 2
	.2byte 0

SaffronCity_CopycatsHouse_2F_Layout_Border::
	.incbin "assets/data.bin", 0x4A86C, 0x8
SaffronCity_CopycatsHouse_2F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x4A874, 0xD8
	.align 2
SaffronCity_CopycatsHouse_2F_Layout::
	.4byte 12
	.4byte 9
	.4byte SaffronCity_CopycatsHouse_2F_Layout_Border
	.4byte SaffronCity_CopycatsHouse_2F_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_GenericBuilding1
	.byte 2
	.byte 2
	.2byte 0

SaffronCity_Dojo_Layout_Border::
	.incbin "assets/data.bin", 0x4A94C, 0x8
SaffronCity_Dojo_Layout_Blockdata::
	.incbin "assets/data.bin", 0x4A954, 0x1A0
	.align 2
SaffronCity_Dojo_Layout::
	.4byte 13
	.4byte 16
	.4byte SaffronCity_Dojo_Layout_Border
	.4byte SaffronCity_Dojo_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_PewterGym
	.byte 2
	.byte 2
	.2byte 0

SilphCo_Elevator_Layout_Border::
	.incbin "assets/data.bin", 0x4AAF4, 0x8
SilphCo_Elevator_Layout_Blockdata::
	.incbin "assets/data.bin", 0x4AAFC, 0x46
	.align 2
SilphCo_Elevator_Layout::
	.4byte 5
	.4byte 7
	.4byte SilphCo_Elevator_Layout_Border
	.4byte SilphCo_Elevator_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_SilphCo
	.byte 2
	.byte 2
	.2byte 0

OneIsland_Layout_Border::
	.incbin "assets/data.bin", 0x4AB44, 0x8
OneIsland_Layout_Blockdata::
	.incbin "assets/data.bin", 0x4AB4C, 0x3C0
	.align 2
OneIsland_Layout::
	.4byte 24
	.4byte 20
	.4byte OneIsland_Layout_Border
	.4byte OneIsland_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_SeviiIslands123
	.byte 2
	.byte 2
	.2byte 0

TwoIsland_Layout_Border::
	.incbin "assets/data.bin", 0x4AF0C, 0x8
TwoIsland_Layout_Blockdata::
	.incbin "assets/data.bin", 0x4AF14, 0x780
	.align 2
TwoIsland_Layout::
	.4byte 48
	.4byte 20
	.4byte TwoIsland_Layout_Border
	.4byte TwoIsland_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_SeviiIslands123
	.byte 2
	.byte 2
	.2byte 0

ThreeIsland_Layout_Border::
	.incbin "assets/data.bin", 0x4B694, 0x8
ThreeIsland_Layout_Blockdata::
	.incbin "assets/data.bin", 0x4B69C, 0x780
	.align 2
ThreeIsland_Layout::
	.4byte 24
	.4byte 40
	.4byte ThreeIsland_Layout_Border
	.4byte ThreeIsland_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_SeviiIslands123
	.byte 2
	.byte 2
	.2byte 0

FourIsland_Layout_Border::
	.incbin "assets/data.bin", 0x4BE1C, 0x8
FourIsland_Layout_Blockdata::
	.incbin "assets/data.bin", 0x4BE24, 0xF00
	.align 2
FourIsland_Layout::
	.4byte 48
	.4byte 40
	.4byte FourIsland_Layout_Border
	.4byte FourIsland_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_SeviiIslands45
	.byte 2
	.byte 2
	.2byte 0

FiveIsland_Layout_Border::
	.incbin "assets/data.bin", 0x4CD24, 0x8
FiveIsland_Layout_Blockdata::
	.incbin "assets/data.bin", 0x4CD2C, 0x3C0
	.align 2
FiveIsland_Layout::
	.4byte 24
	.4byte 20
	.4byte FiveIsland_Layout_Border
	.4byte FiveIsland_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_SeviiIslands45
	.byte 2
	.byte 2
	.2byte 0

SevenIsland_Layout_Border::
	.incbin "assets/data.bin", 0x4D0EC, 0x8
SevenIsland_Layout_Blockdata::
	.incbin "assets/data.bin", 0x4D0F4, 0x3C0
	.align 2
SevenIsland_Layout::
	.4byte 24
	.4byte 20
	.4byte SevenIsland_Layout_Border
	.4byte SevenIsland_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_SeviiIslands67
	.byte 2
	.byte 2
	.2byte 0

SixIsland_Layout_Border::
	.incbin "assets/data.bin", 0x4D4B4, 0x8
SixIsland_Layout_Blockdata::
	.incbin "assets/data.bin", 0x4D4BC, 0x5A0
	.align 2
SixIsland_Layout::
	.4byte 24
	.4byte 30
	.4byte SixIsland_Layout_Border
	.4byte SixIsland_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_SeviiIslands67
	.byte 2
	.byte 2
	.2byte 0

OneIsland_KindleRoad_Layout_Border::
	.incbin "assets/data.bin", 0x4DA5C, 0x8
OneIsland_KindleRoad_Layout_Blockdata::
	.incbin "assets/data.bin", 0x4DA64, 0x1A40
	.align 2
OneIsland_KindleRoad_Layout::
	.4byte 24
	.4byte 140
	.4byte OneIsland_KindleRoad_Layout_Border
	.4byte OneIsland_KindleRoad_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_SeviiIslands123
	.byte 2
	.byte 2
	.2byte 0

OneIsland_TreasureBeach_Layout_Border::
	.incbin "assets/data.bin", 0x4F4A4, 0x8
OneIsland_TreasureBeach_Layout_Blockdata::
	.incbin "assets/data.bin", 0x4F4AC, 0x780
	.align 2
OneIsland_TreasureBeach_Layout::
	.4byte 24
	.4byte 40
	.4byte OneIsland_TreasureBeach_Layout_Border
	.4byte OneIsland_TreasureBeach_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_SeviiIslands123
	.byte 2
	.byte 2
	.2byte 0

TwoIsland_CapeBrink_Layout_Border::
	.incbin "assets/data.bin", 0x4FC2C, 0x8
TwoIsland_CapeBrink_Layout_Blockdata::
	.incbin "assets/data.bin", 0x4FC34, 0x780
	.align 2
TwoIsland_CapeBrink_Layout::
	.4byte 24
	.4byte 40
	.4byte TwoIsland_CapeBrink_Layout_Border
	.4byte TwoIsland_CapeBrink_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_SeviiIslands123
	.byte 2
	.byte 2
	.2byte 0

ThreeIsland_BondBridge_Layout_Border::
	.incbin "assets/data.bin", 0x503B4, 0x8
ThreeIsland_BondBridge_Layout_Blockdata::
	.incbin "assets/data.bin", 0x503BC, 0xF00
	.align 2
ThreeIsland_BondBridge_Layout::
	.4byte 96
	.4byte 20
	.4byte ThreeIsland_BondBridge_Layout_Border
	.4byte ThreeIsland_BondBridge_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_SeviiIslands123
	.byte 2
	.byte 2
	.2byte 0

ThreeIsland_Port_Layout_Border::
	.incbin "assets/data.bin", 0x512BC, 0x8
ThreeIsland_Port_Layout_Blockdata::
	.incbin "assets/data.bin", 0x512C4, 0x780
	.align 2
ThreeIsland_Port_Layout::
	.4byte 48
	.4byte 20
	.4byte ThreeIsland_Port_Layout_Border
	.4byte ThreeIsland_Port_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_SeviiIslands123
	.byte 2
	.byte 2
	.2byte 0

Prototype_SeviiIsle_6_Layout_Border::
	.incbin "assets/data.bin", 0x51A44, 0x8
Prototype_SeviiIsle_6_Layout_Blockdata::
	.incbin "assets/data.bin", 0x51A4C, 0x2
	.align 2
Prototype_SeviiIsle_6_Layout::
	.4byte 1
	.4byte 1
	.4byte Prototype_SeviiIsle_6_Layout_Border
	.4byte Prototype_SeviiIsle_6_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_CeladonCity
	.byte 2
	.byte 2
	.2byte 0

Prototype_SeviiIsle_7_Layout_Border::
	.incbin "assets/data.bin", 0x51A50, 0x8
Prototype_SeviiIsle_7_Layout_Blockdata::
	.incbin "assets/data.bin", 0x51A58, 0x2
	.align 2
Prototype_SeviiIsle_7_Layout::
	.4byte 1
	.4byte 1
	.4byte Prototype_SeviiIsle_7_Layout_Border
	.4byte Prototype_SeviiIsle_7_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_CeladonCity
	.byte 2
	.byte 2
	.2byte 0

Prototype_SeviiIsle_8_Layout_Border::
	.incbin "assets/data.bin", 0x51A5C, 0x8
Prototype_SeviiIsle_8_Layout_Blockdata::
	.incbin "assets/data.bin", 0x51A64, 0xD20
	.align 2
Prototype_SeviiIsle_8_Layout::
	.4byte 84
	.4byte 20
	.4byte Prototype_SeviiIsle_8_Layout_Border
	.4byte Prototype_SeviiIsle_8_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_CeladonCity
	.byte 2
	.byte 2
	.2byte 0

Prototype_SeviiIsle_9_Layout_Border::
	.incbin "assets/data.bin", 0x52784, 0x8
Prototype_SeviiIsle_9_Layout_Blockdata::
	.incbin "assets/data.bin", 0x5278C, 0xB40
	.align 2
Prototype_SeviiIsle_9_Layout::
	.4byte 24
	.4byte 60
	.4byte Prototype_SeviiIsle_9_Layout_Border
	.4byte Prototype_SeviiIsle_9_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_CeladonCity
	.byte 2
	.byte 2
	.2byte 0

FiveIsland_ResortGorgeous_Layout_Border::
	.incbin "assets/data.bin", 0x532CC, 0x8
FiveIsland_ResortGorgeous_Layout_Blockdata::
	.incbin "assets/data.bin", 0x532D4, 0xB40
	.align 2
FiveIsland_ResortGorgeous_Layout::
	.4byte 72
	.4byte 20
	.4byte FiveIsland_ResortGorgeous_Layout_Border
	.4byte FiveIsland_ResortGorgeous_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_SeviiIslands45
	.byte 2
	.byte 2
	.2byte 0

FiveIsland_WaterLabyrinth_Layout_Border::
	.incbin "assets/data.bin", 0x53E14, 0x8
FiveIsland_WaterLabyrinth_Layout_Blockdata::
	.incbin "assets/data.bin", 0x53E1C, 0xB40
	.align 2
FiveIsland_WaterLabyrinth_Layout::
	.4byte 72
	.4byte 20
	.4byte FiveIsland_WaterLabyrinth_Layout_Border
	.4byte FiveIsland_WaterLabyrinth_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_SeviiIslands45
	.byte 2
	.byte 2
	.2byte 0

FiveIsland_Meadow_Layout_Border::
	.incbin "assets/data.bin", 0x5495C, 0x8
FiveIsland_Meadow_Layout_Blockdata::
	.incbin "assets/data.bin", 0x54964, 0x780
	.align 2
FiveIsland_Meadow_Layout::
	.4byte 24
	.4byte 40
	.4byte FiveIsland_Meadow_Layout_Border
	.4byte FiveIsland_Meadow_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_SeviiIslands45
	.byte 2
	.byte 2
	.2byte 0

FiveIsland_MemorialPillar_Layout_Border::
	.incbin "assets/data.bin", 0x550E4, 0x8
FiveIsland_MemorialPillar_Layout_Blockdata::
	.incbin "assets/data.bin", 0x550EC, 0xB40
	.align 2
FiveIsland_MemorialPillar_Layout::
	.4byte 24
	.4byte 60
	.4byte FiveIsland_MemorialPillar_Layout_Border
	.4byte FiveIsland_MemorialPillar_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_SeviiIslands45
	.byte 2
	.byte 2
	.2byte 0

SixIsland_OutcastIsland_Layout_Border::
	.incbin "assets/data.bin", 0x55C2C, 0x8
SixIsland_OutcastIsland_Layout_Blockdata::
	.incbin "assets/data.bin", 0x55C34, 0xF00
	.align 2
SixIsland_OutcastIsland_Layout::
	.4byte 24
	.4byte 80
	.4byte SixIsland_OutcastIsland_Layout_Border
	.4byte SixIsland_OutcastIsland_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_SeviiIslands67
	.byte 2
	.byte 2
	.2byte 0

SixIsland_GreenPath_Layout_Border::
	.incbin "assets/data.bin", 0x56B34, 0x8
SixIsland_GreenPath_Layout_Blockdata::
	.incbin "assets/data.bin", 0x56B3C, 0xB40
	.align 2
SixIsland_GreenPath_Layout::
	.4byte 72
	.4byte 20
	.4byte SixIsland_GreenPath_Layout_Border
	.4byte SixIsland_GreenPath_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_SeviiIslands67
	.byte 2
	.byte 2
	.2byte 0

SixIsland_WaterPath_Layout_Border::
	.incbin "assets/data.bin", 0x5767C, 0x8
SixIsland_WaterPath_Layout_Blockdata::
	.incbin "assets/data.bin", 0x57684, 0x12C0
	.align 2
SixIsland_WaterPath_Layout::
	.4byte 24
	.4byte 100
	.4byte SixIsland_WaterPath_Layout_Border
	.4byte SixIsland_WaterPath_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_SeviiIslands67
	.byte 2
	.byte 2
	.2byte 0

SixIsland_RuinValley_Layout_Border::
	.incbin "assets/data.bin", 0x58944, 0x8
SixIsland_RuinValley_Layout_Blockdata::
	.incbin "assets/data.bin", 0x5894C, 0xF00
	.align 2
SixIsland_RuinValley_Layout::
	.4byte 48
	.4byte 40
	.4byte SixIsland_RuinValley_Layout_Border
	.4byte SixIsland_RuinValley_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_SeviiIslands67
	.byte 2
	.byte 2
	.2byte 0

SevenIsland_TrainerTower_Layout_Border::
	.incbin "assets/data.bin", 0x5984C, 0x8
SevenIsland_TrainerTower_Layout_Blockdata::
	.incbin "assets/data.bin", 0x59854, 0x2580
	.align 2
SevenIsland_TrainerTower_Layout::
	.4byte 120
	.4byte 40
	.4byte SevenIsland_TrainerTower_Layout_Border
	.4byte SevenIsland_TrainerTower_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_SeviiIslands67
	.byte 2
	.byte 2
	.2byte 0

SevenIsland_SevaultCanyon_Entrance_Layout_Border::
	.incbin "assets/data.bin", 0x5BDD4, 0x8
SevenIsland_SevaultCanyon_Entrance_Layout_Blockdata::
	.incbin "assets/data.bin", 0x5BDDC, 0x780
	.align 2
SevenIsland_SevaultCanyon_Entrance_Layout::
	.4byte 24
	.4byte 40
	.4byte SevenIsland_SevaultCanyon_Entrance_Layout_Border
	.4byte SevenIsland_SevaultCanyon_Entrance_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_SeviiIslands67
	.byte 2
	.byte 2
	.2byte 0

SevenIsland_SevaultCanyon_Layout_Border::
	.incbin "assets/data.bin", 0x5C55C, 0x8
SevenIsland_SevaultCanyon_Layout_Blockdata::
	.incbin "assets/data.bin", 0x5C564, 0xF00
	.align 2
SevenIsland_SevaultCanyon_Layout::
	.4byte 24
	.4byte 80
	.4byte SevenIsland_SevaultCanyon_Layout_Border
	.4byte SevenIsland_SevaultCanyon_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_SeviiIslands67
	.byte 2
	.byte 2
	.2byte 0

SevenIsland_TanobyRuins_Layout_Border::
	.incbin "assets/data.bin", 0x5D464, 0x8
SevenIsland_TanobyRuins_Layout_Blockdata::
	.incbin "assets/data.bin", 0x5D46C, 0x1680
	.align 2
SevenIsland_TanobyRuins_Layout::
	.4byte 144
	.4byte 20
	.4byte SevenIsland_TanobyRuins_Layout_Border
	.4byte SevenIsland_TanobyRuins_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_SeviiIslands67
	.byte 2
	.byte 2
	.2byte 0

Prototype_SeviiIsle_22_Layout_Border::
	.incbin "assets/data.bin", 0x5EAEC, 0x8
Prototype_SeviiIsle_22_Layout_Blockdata::
	.incbin "assets/data.bin", 0x5EAF4, 0xB40
	.align 2
Prototype_SeviiIsle_22_Layout::
	.4byte 24
	.4byte 60
	.4byte Prototype_SeviiIsle_22_Layout_Border
	.4byte Prototype_SeviiIsle_22_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_PalletTown
	.byte 2
	.byte 2
	.2byte 0

Prototype_SeviiIsle_23_East_Layout_Border::
	.incbin "assets/data.bin", 0x5F634, 0x8
Prototype_SeviiIsle_23_East_Layout_Blockdata::
	.incbin "assets/data.bin", 0x5F63C, 0x1680
	.align 2
Prototype_SeviiIsle_23_East_Layout::
	.4byte 144
	.4byte 20
	.4byte Prototype_SeviiIsle_23_East_Layout_Border
	.4byte Prototype_SeviiIsle_23_East_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_PalletTown
	.byte 2
	.byte 2
	.2byte 0

Prototype_SeviiIsle_23_West_Layout_Border::
	.incbin "assets/data.bin", 0x60CBC, 0x8
Prototype_SeviiIsle_23_West_Layout_Blockdata::
	.incbin "assets/data.bin", 0x60CC4, 0xB40
	.align 2
Prototype_SeviiIsle_23_West_Layout::
	.4byte 24
	.4byte 60
	.4byte Prototype_SeviiIsle_23_West_Layout_Border
	.4byte Prototype_SeviiIsle_23_West_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_PalletTown
	.byte 2
	.byte 2
	.2byte 0

Prototype_SeviiIsle_24_Layout_Border::
	.incbin "assets/data.bin", 0x61804, 0x8
Prototype_SeviiIsle_24_Layout_Blockdata::
	.incbin "assets/data.bin", 0x6180C, 0x3C0
	.align 2
Prototype_SeviiIsle_24_Layout::
	.4byte 24
	.4byte 20
	.4byte Prototype_SeviiIsle_24_Layout_Border
	.4byte Prototype_SeviiIsle_24_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_PalletTown
	.byte 2
	.byte 2
	.2byte 0

UnionRoom_Layout_Border::
	.incbin "assets/data.bin", 0x61BCC, 0x8
UnionRoom_Layout_Blockdata::
	.incbin "assets/data.bin", 0x61BD4, 0x168
	.align 2
UnionRoom_Layout::
	.4byte 15
	.4byte 12
	.4byte UnionRoom_Layout_Border
	.4byte UnionRoom_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_HallOfFame
	.byte 2
	.byte 2
	.2byte 0

SaffronCity_PokemonTrainerFanClub_Layout_Border::
	.incbin "assets/data.bin", 0x61D3C, 0x8
SaffronCity_PokemonTrainerFanClub_Layout_Blockdata::
	.incbin "assets/data.bin", 0x61D44, 0x176
	.align 2
SaffronCity_PokemonTrainerFanClub_Layout::
	.4byte 11
	.4byte 17
	.4byte SaffronCity_PokemonTrainerFanClub_Layout_Border
	.4byte SaffronCity_PokemonTrainerFanClub_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_FanClubDaycare
	.byte 2
	.byte 2
	.2byte 0

SevenIsland_House_Room1_DoorOpen_Layout_Border::
	.incbin "assets/data.bin", 0x61EBC, 0x8
SevenIsland_House_Room1_DoorOpen_Layout_Blockdata::
	.incbin "assets/data.bin", 0x61EC4, 0xC6
	.align 2
SevenIsland_House_Room1_DoorOpen_Layout::
	.4byte 11
	.4byte 9
	.4byte SevenIsland_House_Room1_DoorOpen_Layout_Border
	.4byte SevenIsland_House_Room1_DoorOpen_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_GenericBuilding2
	.byte 2
	.byte 2
	.2byte 0

SevenIsland_House_Room2_Layout_Border::
	.incbin "assets/data.bin", 0x61F8C, 0x8
SevenIsland_House_Room2_Layout_Blockdata::
	.incbin "assets/data.bin", 0x61F94, 0xD8
	.align 2
SevenIsland_House_Room2_Layout::
	.4byte 12
	.4byte 9
	.4byte SevenIsland_House_Room2_Layout_Border
	.4byte SevenIsland_House_Room2_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_GenericBuilding2
	.byte 2
	.byte 2
	.2byte 0

ViridianCity_School_Layout_Border::
	.incbin "assets/data.bin", 0x6206C, 0x8
ViridianCity_School_Layout_Blockdata::
	.incbin "assets/data.bin", 0x62074, 0xB4
	.align 2
ViridianCity_School_Layout::
	.4byte 10
	.4byte 9
	.4byte ViridianCity_School_Layout_Border
	.4byte ViridianCity_School_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_School
	.byte 2
	.byte 2
	.2byte 0

CeladonCity_Restaurant_Duplicate_Layout_Border::
	.incbin "assets/data.bin", 0x62128, 0x8
CeladonCity_Restaurant_Duplicate_Layout_Blockdata::
	.incbin "assets/data.bin", 0x62130, 0x14A
	.align 2
CeladonCity_Restaurant_Duplicate_Layout::
	.4byte 15
	.4byte 11
	.4byte CeladonCity_Restaurant_Duplicate_Layout_Border
	.4byte CeladonCity_Restaurant_Duplicate_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_RestaurantHotel
	.byte 2
	.byte 2
	.2byte 0

CeladonCity_Hotel_Duplicate_Layout_Border::
	.incbin "assets/data.bin", 0x6227C, 0x8
CeladonCity_Hotel_Duplicate_Layout_Blockdata::
	.incbin "assets/data.bin", 0x62284, 0x176
	.align 2
CeladonCity_Hotel_Duplicate_Layout::
	.4byte 17
	.4byte 11
	.4byte CeladonCity_Hotel_Duplicate_Layout_Border
	.4byte CeladonCity_Hotel_Duplicate_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_RestaurantHotel
	.byte 2
	.byte 2
	.2byte 0

MtEmber_RubyPath_B4F_Layout_Border::
	.incbin "assets/data.bin", 0x623FC, 0x8
MtEmber_RubyPath_B4F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x62404, 0x240
	.align 2
MtEmber_RubyPath_B4F_Layout::
	.4byte 18
	.4byte 16
	.4byte MtEmber_RubyPath_B4F_Layout_Border
	.4byte MtEmber_RubyPath_B4F_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_MtEmber
	.byte 2
	.byte 2
	.2byte 0

ThreeIsland_BerryForest_Layout_Border::
	.incbin "assets/data.bin", 0x62644, 0xC
ThreeIsland_BerryForest_Layout_Blockdata::
	.incbin "assets/data.bin", 0x62650, 0x14EE
	.align 2
ThreeIsland_BerryForest_Layout::
	.4byte 57
	.4byte 47
	.4byte ThreeIsland_BerryForest_Layout_Border
	.4byte ThreeIsland_BerryForest_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_BerryForest
	.byte 3
	.byte 2
	.2byte 0

OneIsland_PokemonCenter_1F_Layout_Border::
	.incbin "assets/data.bin", 0x63B40, 0x8
OneIsland_PokemonCenter_1F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x63B48, 0x1A2
	.align 2
OneIsland_PokemonCenter_1F_Layout::
	.4byte 19
	.4byte 11
	.4byte OneIsland_PokemonCenter_1F_Layout_Border
	.4byte OneIsland_PokemonCenter_1F_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_PokemonCenter
	.byte 2
	.byte 2
	.2byte 0

TwoIsland_JoyfulGameCorner_Layout_Border::
	.incbin "assets/data.bin", 0x63CEC, 0x8
TwoIsland_JoyfulGameCorner_Layout_Blockdata::
	.incbin "assets/data.bin", 0x63CF4, 0xF0
	.align 2
TwoIsland_JoyfulGameCorner_Layout::
	.4byte 12
	.4byte 10
	.4byte TwoIsland_JoyfulGameCorner_Layout_Border
	.4byte TwoIsland_JoyfulGameCorner_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_GameCorner
	.byte 2
	.byte 2
	.2byte 0

VermilionCity_PokemonFanClub_Layout_Border::
	.incbin "assets/data.bin", 0x63DE4, 0x8
VermilionCity_PokemonFanClub_Layout_Blockdata::
	.incbin "assets/data.bin", 0x63DEC, 0x120
	.align 2
VermilionCity_PokemonFanClub_Layout::
	.4byte 12
	.4byte 12
	.4byte VermilionCity_PokemonFanClub_Layout_Border
	.4byte VermilionCity_PokemonFanClub_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_FanClubDaycare
	.byte 2
	.byte 2
	.2byte 0

LavenderTown_VolunteerPokemonHouse_Layout_Border::
	.incbin "assets/data.bin", 0x63F0C, 0x8
LavenderTown_VolunteerPokemonHouse_Layout_Blockdata::
	.incbin "assets/data.bin", 0x63F14, 0xD8
	.align 2
LavenderTown_VolunteerPokemonHouse_Layout::
	.4byte 12
	.4byte 9
	.4byte LavenderTown_VolunteerPokemonHouse_Layout_Border
	.4byte LavenderTown_VolunteerPokemonHouse_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_FanClubDaycare
	.byte 2
	.byte 2
	.2byte 0

Route5_PokemonDayCare_Layout_Border::
	.incbin "assets/data.bin", 0x63FEC, 0x8
Route5_PokemonDayCare_Layout_Blockdata::
	.incbin "assets/data.bin", 0x63FF4, 0xD8
	.align 2
Route5_PokemonDayCare_Layout::
	.4byte 12
	.4byte 9
	.4byte Route5_PokemonDayCare_Layout_Border
	.4byte Route5_PokemonDayCare_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_FanClubDaycare
	.byte 2
	.byte 2
	.2byte 0

ViridianCity_House_Layout_Border::
	.incbin "assets/data.bin", 0x640CC, 0x8
ViridianCity_House_Layout_Blockdata::
	.incbin "assets/data.bin", 0x640D4, 0xC6
	.align 2
ViridianCity_House_Layout::
	.4byte 11
	.4byte 9
	.4byte ViridianCity_House_Layout_Border
	.4byte ViridianCity_House_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_GenericBuilding2
	.byte 2
	.byte 2
	.2byte 0

FourIsland_PokemonDayCare_Layout_Border::
	.incbin "assets/data.bin", 0x6419C, 0x8
FourIsland_PokemonDayCare_Layout_Blockdata::
	.incbin "assets/data.bin", 0x641A4, 0xD8
	.align 2
FourIsland_PokemonDayCare_Layout::
	.4byte 12
	.4byte 9
	.4byte FourIsland_PokemonDayCare_Layout_Border
	.4byte FourIsland_PokemonDayCare_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_FanClubDaycare
	.byte 2
	.byte 2
	.2byte 0

SeafoamIslands_B3F_CurrentStopped_Layout_Border::
	.incbin "assets/data.bin", 0x6427C, 0x8
SeafoamIslands_B3F_CurrentStopped_Layout_Blockdata::
	.incbin "assets/data.bin", 0x64284, 0x720
	.align 2
SeafoamIslands_B3F_CurrentStopped_Layout::
	.4byte 38
	.4byte 24
	.4byte SeafoamIslands_B3F_CurrentStopped_Layout_Border
	.4byte SeafoamIslands_B3F_CurrentStopped_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_SeafoamIslands
	.byte 2
	.byte 2
	.2byte 0

SeafoamIslands_B4F_CurrentStopped_Layout_Border::
	.incbin "assets/data.bin", 0x649A4, 0x8
SeafoamIslands_B4F_CurrentStopped_Layout_Blockdata::
	.incbin "assets/data.bin", 0x649AC, 0x720
	.align 2
SeafoamIslands_B4F_CurrentStopped_Layout::
	.4byte 38
	.4byte 24
	.4byte SeafoamIslands_B4F_CurrentStopped_Layout_Border
	.4byte SeafoamIslands_B4F_CurrentStopped_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_SeafoamIslands
	.byte 2
	.byte 2
	.2byte 0

MtEmber_Exterior_Layout_Border::
	.incbin "assets/data.bin", 0x650CC, 0x8
MtEmber_Exterior_Layout_Blockdata::
	.incbin "assets/data.bin", 0x650D4, 0x180C
	.align 2
MtEmber_Exterior_Layout::
	.4byte 57
	.4byte 54
	.4byte MtEmber_Exterior_Layout_Border
	.4byte MtEmber_Exterior_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_SeviiIslands123
	.byte 2
	.byte 2
	.2byte 0

MtEmber_Summit_Layout_Border::
	.incbin "assets/data.bin", 0x668E0, 0x8
MtEmber_Summit_Layout_Blockdata::
	.incbin "assets/data.bin", 0x668E8, 0x344
	.align 2
MtEmber_Summit_Layout::
	.4byte 19
	.4byte 22
	.4byte MtEmber_Summit_Layout_Border
	.4byte MtEmber_Summit_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_SeviiIslands123
	.byte 2
	.byte 2
	.2byte 0

MtEmber_SummitPath_1F_Layout_Border::
	.incbin "assets/data.bin", 0x66C2C, 0x8
MtEmber_SummitPath_1F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x66C34, 0x21C
	.align 2
MtEmber_SummitPath_1F_Layout::
	.4byte 15
	.4byte 18
	.4byte MtEmber_SummitPath_1F_Layout_Border
	.4byte MtEmber_SummitPath_1F_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_MtEmber
	.byte 2
	.byte 2
	.2byte 0

MtEmber_SummitPath_2F_Layout_Border::
	.incbin "assets/data.bin", 0x66E50, 0x8
MtEmber_SummitPath_2F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x66E58, 0x1140
	.align 2
MtEmber_SummitPath_2F_Layout::
	.4byte 48
	.4byte 46
	.4byte MtEmber_SummitPath_2F_Layout_Border
	.4byte MtEmber_SummitPath_2F_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_MtEmber
	.byte 2
	.byte 2
	.2byte 0

MtEmber_SummitPath_3F_Layout_Border::
	.incbin "assets/data.bin", 0x67F98, 0x8
MtEmber_SummitPath_3F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x67FA0, 0x14A
	.align 2
MtEmber_SummitPath_3F_Layout::
	.4byte 15
	.4byte 11
	.4byte MtEmber_SummitPath_3F_Layout_Border
	.4byte MtEmber_SummitPath_3F_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_MtEmber
	.byte 2
	.byte 2
	.2byte 0

MtEmber_RubyPath_1F_Layout_Border::
	.incbin "assets/data.bin", 0x680EC, 0x8
MtEmber_RubyPath_1F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x680F4, 0x402
	.align 2
MtEmber_RubyPath_1F_Layout::
	.4byte 27
	.4byte 19
	.4byte MtEmber_RubyPath_1F_Layout_Border
	.4byte MtEmber_RubyPath_1F_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_MtEmber
	.byte 2
	.byte 2
	.2byte 0

MtEmber_RubyPath_B1F_Layout_Border::
	.incbin "assets/data.bin", 0x684F8, 0x8
MtEmber_RubyPath_B1F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x68500, 0x1FA
	.align 2
MtEmber_RubyPath_B1F_Layout::
	.4byte 11
	.4byte 23
	.4byte MtEmber_RubyPath_B1F_Layout_Border
	.4byte MtEmber_RubyPath_B1F_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_MtEmber
	.byte 2
	.byte 2
	.2byte 0

MtEmber_RubyPath_B2F_Layout_Border::
	.incbin "assets/data.bin", 0x686FC, 0x8
MtEmber_RubyPath_B2F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x68704, 0x160
	.align 2
MtEmber_RubyPath_B2F_Layout::
	.4byte 16
	.4byte 11
	.4byte MtEmber_RubyPath_B2F_Layout_Border
	.4byte MtEmber_RubyPath_B2F_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_MtEmber
	.byte 2
	.byte 2
	.2byte 0

MtEmber_RubyPath_B3F_Layout_Border::
	.incbin "assets/data.bin", 0x68864, 0x8
MtEmber_RubyPath_B3F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x6886C, 0x592
	.align 2
MtEmber_RubyPath_B3F_Layout::
	.4byte 31
	.4byte 23
	.4byte MtEmber_RubyPath_B3F_Layout_Border
	.4byte MtEmber_RubyPath_B3F_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_MtEmber
	.byte 2
	.byte 2
	.2byte 0

MtEmber_RubyPath_B1F_Stairs_Layout_Border::
	.incbin "assets/data.bin", 0x68E00, 0x8
MtEmber_RubyPath_B1F_Stairs_Layout_Blockdata::
	.incbin "assets/data.bin", 0x68E08, 0x54
	.align 2
MtEmber_RubyPath_B1F_Stairs_Layout::
	.4byte 6
	.4byte 7
	.4byte MtEmber_RubyPath_B1F_Stairs_Layout_Border
	.4byte MtEmber_RubyPath_B1F_Stairs_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_MtEmber
	.byte 2
	.byte 2
	.2byte 0

MtEmber_RubyPath_B2F_Stairs_Layout_Border::
	.incbin "assets/data.bin", 0x68E5C, 0x8
MtEmber_RubyPath_B2F_Stairs_Layout_Blockdata::
	.incbin "assets/data.bin", 0x68E64, 0x60
	.align 2
MtEmber_RubyPath_B2F_Stairs_Layout::
	.4byte 8
	.4byte 6
	.4byte MtEmber_RubyPath_B2F_Stairs_Layout_Border
	.4byte MtEmber_RubyPath_B2F_Stairs_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_MtEmber
	.byte 2
	.byte 2
	.2byte 0

MtEmber_RubyPath_B5F_Layout_Border::
	.incbin "assets/data.bin", 0x68EC4, 0x8
MtEmber_RubyPath_B5F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x68ECC, 0x1E0
	.align 2
MtEmber_RubyPath_B5F_Layout::
	.4byte 16
	.4byte 15
	.4byte MtEmber_RubyPath_B5F_Layout_Border
	.4byte MtEmber_RubyPath_B5F_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_MtEmber
	.byte 2
	.byte 2
	.2byte 0

FiveIsland_RocketWarehouse_Layout_Border::
	.incbin "assets/data.bin", 0x690AC, 0x8
FiveIsland_RocketWarehouse_Layout_Blockdata::
	.incbin "assets/data.bin", 0x690B4, 0x61E
	.align 2
FiveIsland_RocketWarehouse_Layout::
	.4byte 29
	.4byte 27
	.4byte FiveIsland_RocketWarehouse_Layout_Border
	.4byte FiveIsland_RocketWarehouse_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_SilphCo
	.byte 2
	.byte 2
	.2byte 0

FourIsland_IcefallCave_Entrance_Layout_Border::
	.incbin "assets/data.bin", 0x696D4, 0x8
FourIsland_IcefallCave_Entrance_Layout_Blockdata::
	.incbin "assets/data.bin", 0x696DC, 0x870
	.align 2
FourIsland_IcefallCave_Entrance_Layout::
	.4byte 30
	.4byte 36
	.4byte FourIsland_IcefallCave_Entrance_Layout_Border
	.4byte FourIsland_IcefallCave_Entrance_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_SeafoamIslands
	.byte 2
	.byte 2
	.2byte 0

FourIsland_IcefallCave_1F_Layout_Border::
	.incbin "assets/data.bin", 0x69F4C, 0x8
FourIsland_IcefallCave_1F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x69F54, 0x320
	.align 2
FourIsland_IcefallCave_1F_Layout::
	.4byte 20
	.4byte 20
	.4byte FourIsland_IcefallCave_1F_Layout_Border
	.4byte FourIsland_IcefallCave_1F_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_SeafoamIslands
	.byte 2
	.byte 2
	.2byte 0

FourIsland_IcefallCave_B1F_Layout_Border::
	.incbin "assets/data.bin", 0x6A274, 0x8
FourIsland_IcefallCave_B1F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x6A27C, 0x3C0
	.align 2
FourIsland_IcefallCave_B1F_Layout::
	.4byte 24
	.4byte 20
	.4byte FourIsland_IcefallCave_B1F_Layout_Border
	.4byte FourIsland_IcefallCave_B1F_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_SeafoamIslands
	.byte 2
	.byte 2
	.2byte 0

FourIsland_IcefallCave_Back_Layout_Border::
	.incbin "assets/data.bin", 0x6A63C, 0x8
FourIsland_IcefallCave_Back_Layout_Blockdata::
	.incbin "assets/data.bin", 0x6A644, 0x514
	.align 2
FourIsland_IcefallCave_Back_Layout::
	.4byte 25
	.4byte 26
	.4byte FourIsland_IcefallCave_Back_Layout_Border
	.4byte FourIsland_IcefallCave_Back_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_SeafoamIslands
	.byte 2
	.byte 2
	.2byte 0

TrainerTower_Lobby_Layout_Border::
	.incbin "assets/data.bin", 0x6AB58, 0x8
TrainerTower_Lobby_Layout_Blockdata::
	.incbin "assets/data.bin", 0x6AB60, 0x286
	.align 2
TrainerTower_Lobby_Layout::
	.4byte 19
	.4byte 17
	.4byte TrainerTower_Lobby_Layout_Border
	.4byte TrainerTower_Lobby_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_TrainerTower
	.byte 2
	.byte 2
	.2byte 0

TrainerTower_1F_Layout_Border::
	.incbin "assets/data.bin", 0x6ADE8, 0x8
TrainerTower_1F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x6ADF0, 0x264
	.align 2
TrainerTower_1F_Layout::
	.4byte 18
	.4byte 17
	.4byte TrainerTower_1F_Layout_Border
	.4byte TrainerTower_1F_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_TrainerTower
	.byte 2
	.byte 2
	.2byte 0

TrainerTower_2F_Layout_Border::
	.incbin "assets/data.bin", 0x6B054, 0x8
TrainerTower_2F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x6B05C, 0x264
	.align 2
TrainerTower_2F_Layout::
	.4byte 18
	.4byte 17
	.4byte TrainerTower_2F_Layout_Border
	.4byte TrainerTower_2F_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_TrainerTower
	.byte 2
	.byte 2
	.2byte 0

TrainerTower_3F_Layout_Border::
	.incbin "assets/data.bin", 0x6B2C0, 0x8
TrainerTower_3F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x6B2C8, 0x264
	.align 2
TrainerTower_3F_Layout::
	.4byte 18
	.4byte 17
	.4byte TrainerTower_3F_Layout_Border
	.4byte TrainerTower_3F_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_TrainerTower
	.byte 2
	.byte 2
	.2byte 0

TrainerTower_4F_Layout_Border::
	.incbin "assets/data.bin", 0x6B52C, 0x8
TrainerTower_4F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x6B534, 0x264
	.align 2
TrainerTower_4F_Layout::
	.4byte 18
	.4byte 17
	.4byte TrainerTower_4F_Layout_Border
	.4byte TrainerTower_4F_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_TrainerTower
	.byte 2
	.byte 2
	.2byte 0

TrainerTower_5F_Layout_Border::
	.incbin "assets/data.bin", 0x6B798, 0x8
TrainerTower_5F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x6B7A0, 0x264
	.align 2
TrainerTower_5F_Layout::
	.4byte 18
	.4byte 17
	.4byte TrainerTower_5F_Layout_Border
	.4byte TrainerTower_5F_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_TrainerTower
	.byte 2
	.byte 2
	.2byte 0

TrainerTower_6F_Layout_Border::
	.incbin "assets/data.bin", 0x6BA04, 0x8
TrainerTower_6F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x6BA0C, 0x264
	.align 2
TrainerTower_6F_Layout::
	.4byte 18
	.4byte 17
	.4byte TrainerTower_6F_Layout_Border
	.4byte TrainerTower_6F_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_TrainerTower
	.byte 2
	.byte 2
	.2byte 0

TrainerTower_7F_Layout_Border::
	.incbin "assets/data.bin", 0x6BC70, 0x8
TrainerTower_7F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x6BC78, 0x264
	.align 2
TrainerTower_7F_Layout::
	.4byte 18
	.4byte 17
	.4byte TrainerTower_7F_Layout_Border
	.4byte TrainerTower_7F_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_TrainerTower
	.byte 2
	.byte 2
	.2byte 0

TrainerTower_8F_Layout_Border::
	.incbin "assets/data.bin", 0x6BEDC, 0x8
TrainerTower_8F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x6BEE4, 0x264
	.align 2
TrainerTower_8F_Layout::
	.4byte 18
	.4byte 17
	.4byte TrainerTower_8F_Layout_Border
	.4byte TrainerTower_8F_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_TrainerTower
	.byte 2
	.byte 2
	.2byte 0

TrainerTower_Roof_Layout_Border::
	.incbin "assets/data.bin", 0x6C148, 0x8
TrainerTower_Roof_Layout_Blockdata::
	.incbin "assets/data.bin", 0x6C150, 0x240
	.align 2
TrainerTower_Roof_Layout::
	.4byte 18
	.4byte 16
	.4byte TrainerTower_Roof_Layout_Border
	.4byte TrainerTower_Roof_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_TrainerTower
	.byte 2
	.byte 2
	.2byte 0

TrainerTower_Elevator_Layout_Border::
	.incbin "assets/data.bin", 0x6C390, 0x8
TrainerTower_Elevator_Layout_Blockdata::
	.incbin "assets/data.bin", 0x6C398, 0x46
	.align 2
TrainerTower_Elevator_Layout::
	.4byte 5
	.4byte 7
	.4byte TrainerTower_Elevator_Layout_Border
	.4byte TrainerTower_Elevator_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_SilphCo
	.byte 2
	.byte 2
	.2byte 0

CeruleanCity_House5_Layout_Border::
	.incbin "assets/data.bin", 0x6C3E0, 0x8
CeruleanCity_House5_Layout_Blockdata::
	.incbin "assets/data.bin", 0x6C3E8, 0xC6
	.align 2
CeruleanCity_House5_Layout::
	.4byte 11
	.4byte 9
	.4byte CeruleanCity_House5_Layout_Border
	.4byte CeruleanCity_House5_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_GenericBuilding2
	.byte 2
	.byte 2
	.2byte 0

SixIsland_DottedHole_1F_Layout_Border::
	.incbin "assets/data.bin", 0x6C4B0, 0x8
SixIsland_DottedHole_1F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x6C4B8, 0x160
	.align 2
SixIsland_DottedHole_1F_Layout::
	.4byte 16
	.4byte 11
	.4byte SixIsland_DottedHole_1F_Layout_Border
	.4byte SixIsland_DottedHole_1F_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_NavelRock
	.byte 2
	.byte 2
	.2byte 0

SixIsland_DottedHole_B1F_Layout_Border::
	.incbin "assets/data.bin", 0x6C618, 0x8
SixIsland_DottedHole_B1F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x6C620, 0x11E
	.align 2
SixIsland_DottedHole_B1F_Layout::
	.4byte 13
	.4byte 11
	.4byte SixIsland_DottedHole_B1F_Layout_Border
	.4byte SixIsland_DottedHole_B1F_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_NavelRock
	.byte 2
	.byte 2
	.2byte 0

SixIsland_DottedHole_B2F_Layout_Border::
	.incbin "assets/data.bin", 0x6C740, 0x8
SixIsland_DottedHole_B2F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x6C748, 0x11E
	.align 2
SixIsland_DottedHole_B2F_Layout::
	.4byte 13
	.4byte 11
	.4byte SixIsland_DottedHole_B2F_Layout_Border
	.4byte SixIsland_DottedHole_B2F_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_NavelRock
	.byte 2
	.byte 2
	.2byte 0

SixIsland_DottedHole_B3F_Layout_Border::
	.incbin "assets/data.bin", 0x6C868, 0x8
SixIsland_DottedHole_B3F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x6C870, 0x11E
	.align 2
SixIsland_DottedHole_B3F_Layout::
	.4byte 13
	.4byte 11
	.4byte SixIsland_DottedHole_B3F_Layout_Border
	.4byte SixIsland_DottedHole_B3F_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_NavelRock
	.byte 2
	.byte 2
	.2byte 0

SixIsland_DottedHole_B4F_Layout_Border::
	.incbin "assets/data.bin", 0x6C990, 0x8
SixIsland_DottedHole_B4F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x6C998, 0x11E
	.align 2
SixIsland_DottedHole_B4F_Layout::
	.4byte 13
	.4byte 11
	.4byte SixIsland_DottedHole_B4F_Layout_Border
	.4byte SixIsland_DottedHole_B4F_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_NavelRock
	.byte 2
	.byte 2
	.2byte 0

SixIsland_DottedHole_SapphireRoom_Layout_Border::
	.incbin "assets/data.bin", 0x6CAB8, 0x8
SixIsland_DottedHole_SapphireRoom_Layout_Blockdata::
	.incbin "assets/data.bin", 0x6CAC0, 0x1E0
	.align 2
SixIsland_DottedHole_SapphireRoom_Layout::
	.4byte 16
	.4byte 15
	.4byte SixIsland_DottedHole_SapphireRoom_Layout_Border
	.4byte SixIsland_DottedHole_SapphireRoom_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_NavelRock
	.byte 2
	.byte 2
	.2byte 0

Island_Harbor_Layout_Border::
	.incbin "assets/data.bin", 0x6CCA0, 0x8
Island_Harbor_Layout_Blockdata::
	.incbin "assets/data.bin", 0x6CCA8, 0x1BA
	.align 2
Island_Harbor_Layout::
	.4byte 17
	.4byte 13
	.4byte Island_Harbor_Layout_Border
	.4byte Island_Harbor_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_IslandHarbor
	.byte 2
	.byte 2
	.2byte 0

OneIsland_PokemonCenter_2F_Layout_Border::
	.incbin "assets/data.bin", 0x6CE64, 0x8
OneIsland_PokemonCenter_2F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x6CE6C, 0x12C
	.align 2
OneIsland_PokemonCenter_2F_Layout::
	.4byte 15
	.4byte 10
	.4byte OneIsland_PokemonCenter_2F_Layout_Border
	.4byte OneIsland_PokemonCenter_2F_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_PokemonCenter
	.byte 2
	.byte 2
	.2byte 0

SixIsland_PatternBush_Layout_Border::
	.incbin "assets/data.bin", 0x6CF98, 0xC
SixIsland_PatternBush_Layout_Blockdata::
	.incbin "assets/data.bin", 0x6CFA4, 0xF00
	.align 2
SixIsland_PatternBush_Layout::
	.4byte 60
	.4byte 32
	.4byte SixIsland_PatternBush_Layout_Border
	.4byte SixIsland_PatternBush_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_ViridianForest
	.byte 3
	.byte 2
	.2byte 0

ThreeIsland_DunsparceTunnel_Layout_Border::
	.incbin "assets/data.bin", 0x6DEA4, 0x8
ThreeIsland_DunsparceTunnel_Layout_Blockdata::
	.incbin "assets/data.bin", 0x6DEAC, 0x1A4
	.align 2
ThreeIsland_DunsparceTunnel_Layout::
	.4byte 30
	.4byte 7
	.4byte ThreeIsland_DunsparceTunnel_Layout_Border
	.4byte ThreeIsland_DunsparceTunnel_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_Cave
	.byte 2
	.byte 2
	.2byte 0

ThreeIsland_DunsparceTunnel_DugOut_Layout_Border::
	.incbin "assets/data.bin", 0x6E050, 0x8
ThreeIsland_DunsparceTunnel_DugOut_Layout_Blockdata::
	.incbin "assets/data.bin", 0x6E058, 0x1A4
	.align 2
ThreeIsland_DunsparceTunnel_DugOut_Layout::
	.4byte 30
	.4byte 7
	.4byte ThreeIsland_DunsparceTunnel_DugOut_Layout_Border
	.4byte ThreeIsland_DunsparceTunnel_DugOut_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_Cave
	.byte 2
	.byte 2
	.2byte 0

FiveIsland_LostCave_Entrance_Layout_Border::
	.incbin "assets/data.bin", 0x6E1FC, 0x8
FiveIsland_LostCave_Entrance_Layout_Blockdata::
	.incbin "assets/data.bin", 0x6E204, 0xF2
	.align 2
FiveIsland_LostCave_Entrance_Layout::
	.4byte 11
	.4byte 11
	.4byte FiveIsland_LostCave_Entrance_Layout_Border
	.4byte FiveIsland_LostCave_Entrance_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_Cave
	.byte 2
	.byte 2
	.2byte 0

FiveIsland_LostCave_Room1_Layout_Border::
	.incbin "assets/data.bin", 0x6E2F8, 0x8
FiveIsland_LostCave_Room1_Layout_Blockdata::
	.incbin "assets/data.bin", 0x6E300, 0xF2
	.align 2
FiveIsland_LostCave_Room1_Layout::
	.4byte 11
	.4byte 11
	.4byte FiveIsland_LostCave_Room1_Layout_Border
	.4byte FiveIsland_LostCave_Room1_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_Cave
	.byte 2
	.byte 2
	.2byte 0

FiveIsland_LostCave_Room2_Layout_Border::
	.incbin "assets/data.bin", 0x6E3F4, 0x8
FiveIsland_LostCave_Room2_Layout_Blockdata::
	.incbin "assets/data.bin", 0x6E3FC, 0xF2
	.align 2
FiveIsland_LostCave_Room2_Layout::
	.4byte 11
	.4byte 11
	.4byte FiveIsland_LostCave_Room2_Layout_Border
	.4byte FiveIsland_LostCave_Room2_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_Cave
	.byte 2
	.byte 2
	.2byte 0

FiveIsland_LostCave_Room3_Layout_Border::
	.incbin "assets/data.bin", 0x6E4F0, 0x8
FiveIsland_LostCave_Room3_Layout_Blockdata::
	.incbin "assets/data.bin", 0x6E4F8, 0xF2
	.align 2
FiveIsland_LostCave_Room3_Layout::
	.4byte 11
	.4byte 11
	.4byte FiveIsland_LostCave_Room3_Layout_Border
	.4byte FiveIsland_LostCave_Room3_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_Cave
	.byte 2
	.byte 2
	.2byte 0

FiveIsland_LostCave_Room4_Layout_Border::
	.incbin "assets/data.bin", 0x6E5EC, 0x8
FiveIsland_LostCave_Room4_Layout_Blockdata::
	.incbin "assets/data.bin", 0x6E5F4, 0xF2
	.align 2
FiveIsland_LostCave_Room4_Layout::
	.4byte 11
	.4byte 11
	.4byte FiveIsland_LostCave_Room4_Layout_Border
	.4byte FiveIsland_LostCave_Room4_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_Cave
	.byte 2
	.byte 2
	.2byte 0

FiveIsland_LostCave_Room5_Layout_Border::
	.incbin "assets/data.bin", 0x6E6E8, 0x8
FiveIsland_LostCave_Room5_Layout_Blockdata::
	.incbin "assets/data.bin", 0x6E6F0, 0xF2
	.align 2
FiveIsland_LostCave_Room5_Layout::
	.4byte 11
	.4byte 11
	.4byte FiveIsland_LostCave_Room5_Layout_Border
	.4byte FiveIsland_LostCave_Room5_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_Cave
	.byte 2
	.byte 2
	.2byte 0

FiveIsland_LostCave_Room6_Layout_Border::
	.incbin "assets/data.bin", 0x6E7E4, 0x8
FiveIsland_LostCave_Room6_Layout_Blockdata::
	.incbin "assets/data.bin", 0x6E7EC, 0xF2
	.align 2
FiveIsland_LostCave_Room6_Layout::
	.4byte 11
	.4byte 11
	.4byte FiveIsland_LostCave_Room6_Layout_Border
	.4byte FiveIsland_LostCave_Room6_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_Cave
	.byte 2
	.byte 2
	.2byte 0

FiveIsland_LostCave_Room7_Layout_Border::
	.incbin "assets/data.bin", 0x6E8E0, 0x8
FiveIsland_LostCave_Room7_Layout_Blockdata::
	.incbin "assets/data.bin", 0x6E8E8, 0xF2
	.align 2
FiveIsland_LostCave_Room7_Layout::
	.4byte 11
	.4byte 11
	.4byte FiveIsland_LostCave_Room7_Layout_Border
	.4byte FiveIsland_LostCave_Room7_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_Cave
	.byte 2
	.byte 2
	.2byte 0

FiveIsland_LostCave_Room8_Layout_Border::
	.incbin "assets/data.bin", 0x6E9DC, 0x8
FiveIsland_LostCave_Room8_Layout_Blockdata::
	.incbin "assets/data.bin", 0x6E9E4, 0xF2
	.align 2
FiveIsland_LostCave_Room8_Layout::
	.4byte 11
	.4byte 11
	.4byte FiveIsland_LostCave_Room8_Layout_Border
	.4byte FiveIsland_LostCave_Room8_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_Cave
	.byte 2
	.byte 2
	.2byte 0

FiveIsland_LostCave_Room9_Layout_Border::
	.incbin "assets/data.bin", 0x6EAD8, 0x8
FiveIsland_LostCave_Room9_Layout_Blockdata::
	.incbin "assets/data.bin", 0x6EAE0, 0xF2
	.align 2
FiveIsland_LostCave_Room9_Layout::
	.4byte 11
	.4byte 11
	.4byte FiveIsland_LostCave_Room9_Layout_Border
	.4byte FiveIsland_LostCave_Room9_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_Cave
	.byte 2
	.byte 2
	.2byte 0

FiveIsland_LostCave_Room10_Layout_Border::
	.incbin "assets/data.bin", 0x6EBD4, 0x8
FiveIsland_LostCave_Room10_Layout_Blockdata::
	.incbin "assets/data.bin", 0x6EBDC, 0xF2
	.align 2
FiveIsland_LostCave_Room10_Layout::
	.4byte 11
	.4byte 11
	.4byte FiveIsland_LostCave_Room10_Layout_Border
	.4byte FiveIsland_LostCave_Room10_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_Cave
	.byte 2
	.byte 2
	.2byte 0

FiveIsland_LostCave_Room11_Layout_Border::
	.incbin "assets/data.bin", 0x6ECD0, 0x8
FiveIsland_LostCave_Room11_Layout_Blockdata::
	.incbin "assets/data.bin", 0x6ECD8, 0xF2
	.align 2
FiveIsland_LostCave_Room11_Layout::
	.4byte 11
	.4byte 11
	.4byte FiveIsland_LostCave_Room11_Layout_Border
	.4byte FiveIsland_LostCave_Room11_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_Cave
	.byte 2
	.byte 2
	.2byte 0

FiveIsland_LostCave_Room12_Layout_Border::
	.incbin "assets/data.bin", 0x6EDCC, 0x8
FiveIsland_LostCave_Room12_Layout_Blockdata::
	.incbin "assets/data.bin", 0x6EDD4, 0xF2
	.align 2
FiveIsland_LostCave_Room12_Layout::
	.4byte 11
	.4byte 11
	.4byte FiveIsland_LostCave_Room12_Layout_Border
	.4byte FiveIsland_LostCave_Room12_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_Cave
	.byte 2
	.byte 2
	.2byte 0

FiveIsland_LostCave_Room13_Layout_Border::
	.incbin "assets/data.bin", 0x6EEC8, 0x8
FiveIsland_LostCave_Room13_Layout_Blockdata::
	.incbin "assets/data.bin", 0x6EED0, 0xF2
	.align 2
FiveIsland_LostCave_Room13_Layout::
	.4byte 11
	.4byte 11
	.4byte FiveIsland_LostCave_Room13_Layout_Border
	.4byte FiveIsland_LostCave_Room13_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_Cave
	.byte 2
	.byte 2
	.2byte 0

FiveIsland_LostCave_Room14_Layout_Border::
	.incbin "assets/data.bin", 0x6EFC4, 0x8
FiveIsland_LostCave_Room14_Layout_Blockdata::
	.incbin "assets/data.bin", 0x6EFCC, 0xF2
	.align 2
FiveIsland_LostCave_Room14_Layout::
	.4byte 11
	.4byte 11
	.4byte FiveIsland_LostCave_Room14_Layout_Border
	.4byte FiveIsland_LostCave_Room14_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_Cave
	.byte 2
	.byte 2
	.2byte 0

SevenIsland_TanobyRuins_MoneanChamber_Layout_Border::
	.incbin "assets/data.bin", 0x6F0C0, 0x8
SevenIsland_TanobyRuins_MoneanChamber_Layout_Blockdata::
	.incbin "assets/data.bin", 0x6F0C8, 0x30E
	.align 2
SevenIsland_TanobyRuins_MoneanChamber_Layout::
	.4byte 23
	.4byte 17
	.4byte SevenIsland_TanobyRuins_MoneanChamber_Layout_Border
	.4byte SevenIsland_TanobyRuins_MoneanChamber_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_TanobyRuins
	.byte 2
	.byte 2
	.2byte 0

SevenIsland_TanobyRuins_LiptooChamber_Layout_Border::
	.incbin "assets/data.bin", 0x6F3D8, 0x8
SevenIsland_TanobyRuins_LiptooChamber_Layout_Blockdata::
	.incbin "assets/data.bin", 0x6F3E0, 0x30E
	.align 2
SevenIsland_TanobyRuins_LiptooChamber_Layout::
	.4byte 23
	.4byte 17
	.4byte SevenIsland_TanobyRuins_LiptooChamber_Layout_Border
	.4byte SevenIsland_TanobyRuins_LiptooChamber_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_TanobyRuins
	.byte 2
	.byte 2
	.2byte 0

SevenIsland_TanobyRuins_WeepthChamber_Layout_Border::
	.incbin "assets/data.bin", 0x6F6F0, 0x8
SevenIsland_TanobyRuins_WeepthChamber_Layout_Blockdata::
	.incbin "assets/data.bin", 0x6F6F8, 0x30E
	.align 2
SevenIsland_TanobyRuins_WeepthChamber_Layout::
	.4byte 23
	.4byte 17
	.4byte SevenIsland_TanobyRuins_WeepthChamber_Layout_Border
	.4byte SevenIsland_TanobyRuins_WeepthChamber_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_TanobyRuins
	.byte 2
	.byte 2
	.2byte 0

SevenIsland_TanobyRuins_DilfordChamber_Layout_Border::
	.incbin "assets/data.bin", 0x6FA08, 0x8
SevenIsland_TanobyRuins_DilfordChamber_Layout_Blockdata::
	.incbin "assets/data.bin", 0x6FA10, 0x30E
	.align 2
SevenIsland_TanobyRuins_DilfordChamber_Layout::
	.4byte 23
	.4byte 17
	.4byte SevenIsland_TanobyRuins_DilfordChamber_Layout_Border
	.4byte SevenIsland_TanobyRuins_DilfordChamber_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_TanobyRuins
	.byte 2
	.byte 2
	.2byte 0

SevenIsland_TanobyRuins_ScufibChamber_Layout_Border::
	.incbin "assets/data.bin", 0x6FD20, 0x8
SevenIsland_TanobyRuins_ScufibChamber_Layout_Blockdata::
	.incbin "assets/data.bin", 0x6FD28, 0x30E
	.align 2
SevenIsland_TanobyRuins_ScufibChamber_Layout::
	.4byte 23
	.4byte 17
	.4byte SevenIsland_TanobyRuins_ScufibChamber_Layout_Border
	.4byte SevenIsland_TanobyRuins_ScufibChamber_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_TanobyRuins
	.byte 2
	.byte 2
	.2byte 0

SixIsland_AlteringCave_Layout_Border::
	.incbin "assets/data.bin", 0x70038, 0x8
SixIsland_AlteringCave_Layout_Blockdata::
	.incbin "assets/data.bin", 0x70040, 0x600
	.align 2
SixIsland_AlteringCave_Layout::
	.4byte 32
	.4byte 24
	.4byte SixIsland_AlteringCave_Layout_Border
	.4byte SixIsland_AlteringCave_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_RockTunnel
	.byte 2
	.byte 2
	.2byte 0

SevenIsland_SevaultCanyon_TanobyKey_Layout_Border::
	.incbin "assets/data.bin", 0x70640, 0x8
SevenIsland_SevaultCanyon_TanobyKey_Layout_Blockdata::
	.incbin "assets/data.bin", 0x70648, 0x1E0
	.align 2
SevenIsland_SevaultCanyon_TanobyKey_Layout::
	.4byte 15
	.4byte 16
	.4byte SevenIsland_SevaultCanyon_TanobyKey_Layout_Border
	.4byte SevenIsland_SevaultCanyon_TanobyKey_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_DiglettsCave
	.byte 2
	.byte 2
	.2byte 0

BirthIsland_Exterior_Layout_Border::
	.incbin "assets/data.bin", 0x70828, 0x8
BirthIsland_Exterior_Layout_Blockdata::
	.incbin "assets/data.bin", 0x70830, 0x708
	.align 2
BirthIsland_Exterior_Layout::
	.4byte 30
	.4byte 30
	.4byte BirthIsland_Exterior_Layout_Border
	.4byte BirthIsland_Exterior_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_SeviiIslands67
	.byte 2
	.byte 2
	.2byte 0

NavelRock_Exterior_Layout_Border::
	.incbin "assets/data.bin", 0x70F38, 0x8
NavelRock_Exterior_Layout_Blockdata::
	.incbin "assets/data.bin", 0x70F40, 0x398
	.align 2
NavelRock_Exterior_Layout::
	.4byte 20
	.4byte 23
	.4byte NavelRock_Exterior_Layout_Border
	.4byte NavelRock_Exterior_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_SeviiIslands123
	.byte 2
	.byte 2
	.2byte 0

NavelRock_1F_Layout_Border::
	.incbin "assets/data.bin", 0x712D8, 0x8
NavelRock_1F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x712E0, 0x374
	.align 2
NavelRock_1F_Layout::
	.4byte 17
	.4byte 26
	.4byte NavelRock_1F_Layout_Border
	.4byte NavelRock_1F_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_NavelRock
	.byte 2
	.byte 2
	.2byte 0

NavelRock_Summit_Layout_Border::
	.incbin "assets/data.bin", 0x71654, 0x8
NavelRock_Summit_Layout_Blockdata::
	.incbin "assets/data.bin", 0x7165C, 0x3B6
	.align 2
NavelRock_Summit_Layout::
	.4byte 19
	.4byte 25
	.4byte NavelRock_Summit_Layout_Border
	.4byte NavelRock_Summit_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_NavelRock
	.byte 2
	.byte 2
	.2byte 0

NavelRock_Base_Layout_Border::
	.incbin "assets/data.bin", 0x71A14, 0x8
NavelRock_Base_Layout_Blockdata::
	.incbin "assets/data.bin", 0x71A1C, 0x3C6
	.align 2
NavelRock_Base_Layout::
	.4byte 21
	.4byte 23
	.4byte NavelRock_Base_Layout_Border
	.4byte NavelRock_Base_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_NavelRock
	.byte 2
	.byte 2
	.2byte 0

NavelRock_SummitPath_2F_Layout_Border::
	.incbin "assets/data.bin", 0x71DE4, 0x8
NavelRock_SummitPath_2F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x71DEC, 0x62
	.align 2
NavelRock_SummitPath_2F_Layout::
	.4byte 7
	.4byte 7
	.4byte NavelRock_SummitPath_2F_Layout_Border
	.4byte NavelRock_SummitPath_2F_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_NavelRock
	.byte 2
	.byte 2
	.2byte 0

NavelRock_SummitPath_3F_Layout_Border::
	.incbin "assets/data.bin", 0x71E50, 0x8
NavelRock_SummitPath_3F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x71E58, 0x62
	.align 2
NavelRock_SummitPath_3F_Layout::
	.4byte 7
	.4byte 7
	.4byte NavelRock_SummitPath_3F_Layout_Border
	.4byte NavelRock_SummitPath_3F_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_NavelRock
	.byte 2
	.byte 2
	.2byte 0

NavelRock_SummitPath_4F_Layout_Border::
	.incbin "assets/data.bin", 0x71EBC, 0x8
NavelRock_SummitPath_4F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x71EC4, 0x62
	.align 2
NavelRock_SummitPath_4F_Layout::
	.4byte 7
	.4byte 7
	.4byte NavelRock_SummitPath_4F_Layout_Border
	.4byte NavelRock_SummitPath_4F_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_NavelRock
	.byte 2
	.byte 2
	.2byte 0

NavelRock_SummitPath_5F_Layout_Border::
	.incbin "assets/data.bin", 0x71F28, 0x8
NavelRock_SummitPath_5F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x71F30, 0x62
	.align 2
NavelRock_SummitPath_5F_Layout::
	.4byte 7
	.4byte 7
	.4byte NavelRock_SummitPath_5F_Layout_Border
	.4byte NavelRock_SummitPath_5F_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_NavelRock
	.byte 2
	.byte 2
	.2byte 0

NavelRock_BasePath_B1F_Layout_Border::
	.incbin "assets/data.bin", 0x71F94, 0x8
NavelRock_BasePath_B1F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x71F9C, 0x62
	.align 2
NavelRock_BasePath_B1F_Layout::
	.4byte 7
	.4byte 7
	.4byte NavelRock_BasePath_B1F_Layout_Border
	.4byte NavelRock_BasePath_B1F_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_NavelRock
	.byte 2
	.byte 2
	.2byte 0

NavelRock_BasePath_B2F_Layout_Border::
	.incbin "assets/data.bin", 0x72000, 0x8
NavelRock_BasePath_B2F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x72008, 0x62
	.align 2
NavelRock_BasePath_B2F_Layout::
	.4byte 7
	.4byte 7
	.4byte NavelRock_BasePath_B2F_Layout_Border
	.4byte NavelRock_BasePath_B2F_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_NavelRock
	.byte 2
	.byte 2
	.2byte 0

NavelRock_BasePath_B3F_Layout_Border::
	.incbin "assets/data.bin", 0x7206C, 0x8
NavelRock_BasePath_B3F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x72074, 0x62
	.align 2
NavelRock_BasePath_B3F_Layout::
	.4byte 7
	.4byte 7
	.4byte NavelRock_BasePath_B3F_Layout_Border
	.4byte NavelRock_BasePath_B3F_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_NavelRock
	.byte 2
	.byte 2
	.2byte 0

NavelRock_BasePath_B4F_Layout_Border::
	.incbin "assets/data.bin", 0x720D8, 0x8
NavelRock_BasePath_B4F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x720E0, 0x62
	.align 2
NavelRock_BasePath_B4F_Layout::
	.4byte 7
	.4byte 7
	.4byte NavelRock_BasePath_B4F_Layout_Border
	.4byte NavelRock_BasePath_B4F_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_NavelRock
	.byte 2
	.byte 2
	.2byte 0

NavelRock_BasePath_B5F_Layout_Border::
	.incbin "assets/data.bin", 0x72144, 0x8
NavelRock_BasePath_B5F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x7214C, 0x62
	.align 2
NavelRock_BasePath_B5F_Layout::
	.4byte 7
	.4byte 7
	.4byte NavelRock_BasePath_B5F_Layout_Border
	.4byte NavelRock_BasePath_B5F_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_NavelRock
	.byte 2
	.byte 2
	.2byte 0

NavelRock_BasePath_B6F_Layout_Border::
	.incbin "assets/data.bin", 0x721B0, 0x8
NavelRock_BasePath_B6F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x721B8, 0x62
	.align 2
NavelRock_BasePath_B6F_Layout::
	.4byte 7
	.4byte 7
	.4byte NavelRock_BasePath_B6F_Layout_Border
	.4byte NavelRock_BasePath_B6F_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_NavelRock
	.byte 2
	.byte 2
	.2byte 0

NavelRock_BasePath_B7F_Layout_Border::
	.incbin "assets/data.bin", 0x7221C, 0x8
NavelRock_BasePath_B7F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x72224, 0x62
	.align 2
NavelRock_BasePath_B7F_Layout::
	.4byte 7
	.4byte 7
	.4byte NavelRock_BasePath_B7F_Layout_Border
	.4byte NavelRock_BasePath_B7F_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_NavelRock
	.byte 2
	.byte 2
	.2byte 0

NavelRock_BasePath_B8F_Layout_Border::
	.incbin "assets/data.bin", 0x72288, 0x8
NavelRock_BasePath_B8F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x72290, 0x62
	.align 2
NavelRock_BasePath_B8F_Layout::
	.4byte 7
	.4byte 7
	.4byte NavelRock_BasePath_B8F_Layout_Border
	.4byte NavelRock_BasePath_B8F_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_NavelRock
	.byte 2
	.byte 2
	.2byte 0

NavelRock_BasePath_B9F_Layout_Border::
	.incbin "assets/data.bin", 0x722F4, 0x8
NavelRock_BasePath_B9F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x722FC, 0x62
	.align 2
NavelRock_BasePath_B9F_Layout::
	.4byte 7
	.4byte 7
	.4byte NavelRock_BasePath_B9F_Layout_Border
	.4byte NavelRock_BasePath_B9F_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_NavelRock
	.byte 2
	.byte 2
	.2byte 0

NavelRock_BasePath_B10F_Layout_Border::
	.incbin "assets/data.bin", 0x72360, 0x8
NavelRock_BasePath_B10F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x72368, 0x62
	.align 2
NavelRock_BasePath_B10F_Layout::
	.4byte 7
	.4byte 7
	.4byte NavelRock_BasePath_B10F_Layout_Border
	.4byte NavelRock_BasePath_B10F_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_NavelRock
	.byte 2
	.byte 2
	.2byte 0

NavelRock_BasePath_B11F_Layout_Border::
	.incbin "assets/data.bin", 0x723CC, 0x8
NavelRock_BasePath_B11F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x723D4, 0x62
	.align 2
NavelRock_BasePath_B11F_Layout::
	.4byte 7
	.4byte 7
	.4byte NavelRock_BasePath_B11F_Layout_Border
	.4byte NavelRock_BasePath_B11F_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_NavelRock
	.byte 2
	.byte 2
	.2byte 0

SevenIsland_TanobyRuins_RixyChamber_Layout_Border::
	.incbin "assets/data.bin", 0x72438, 0x8
SevenIsland_TanobyRuins_RixyChamber_Layout_Blockdata::
	.incbin "assets/data.bin", 0x72440, 0x30E
	.align 2
SevenIsland_TanobyRuins_RixyChamber_Layout::
	.4byte 23
	.4byte 17
	.4byte SevenIsland_TanobyRuins_RixyChamber_Layout_Border
	.4byte SevenIsland_TanobyRuins_RixyChamber_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_TanobyRuins
	.byte 2
	.byte 2
	.2byte 0

SevenIsland_TanobyRuins_ViapoisChamber_Layout_Border::
	.incbin "assets/data.bin", 0x72750, 0x8
SevenIsland_TanobyRuins_ViapoisChamber_Layout_Blockdata::
	.incbin "assets/data.bin", 0x72758, 0x30E
	.align 2
SevenIsland_TanobyRuins_ViapoisChamber_Layout::
	.4byte 23
	.4byte 17
	.4byte SevenIsland_TanobyRuins_ViapoisChamber_Layout_Border
	.4byte SevenIsland_TanobyRuins_ViapoisChamber_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_TanobyRuins
	.byte 2
	.byte 2
	.2byte 0

NavelRock_B1F_Layout_Border::
	.incbin "assets/data.bin", 0x72A68, 0x8
NavelRock_B1F_Layout_Blockdata::
	.incbin "assets/data.bin", 0x72A70, 0xEE
	.align 2
NavelRock_B1F_Layout::
	.4byte 17
	.4byte 7
	.4byte NavelRock_B1F_Layout_Border
	.4byte NavelRock_B1F_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_NavelRock
	.byte 2
	.byte 2
	.2byte 0

NavelRock_Fork_Layout_Border::
	.incbin "assets/data.bin", 0x72B60, 0x8
NavelRock_Fork_Layout_Blockdata::
	.incbin "assets/data.bin", 0x72B68, 0x1770
	.align 2
NavelRock_Fork_Layout::
	.4byte 30
	.4byte 100
	.4byte NavelRock_Fork_Layout_Border
	.4byte NavelRock_Fork_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_NavelRock
	.byte 2
	.byte 2
	.2byte 0

TrainerTower_1F_Doubles_Layout_Border::
	.incbin "assets/data.bin", 0x742D8, 0x8
TrainerTower_1F_Doubles_Layout_Blockdata::
	.incbin "assets/data.bin", 0x742E0, 0x264
	.align 2
TrainerTower_1F_Doubles_Layout::
	.4byte 18
	.4byte 17
	.4byte TrainerTower_1F_Doubles_Layout_Border
	.4byte TrainerTower_1F_Doubles_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_TrainerTower
	.byte 2
	.byte 2
	.2byte 0

TrainerTower_2F_Doubles_Layout_Border::
	.incbin "assets/data.bin", 0x74544, 0x8
TrainerTower_2F_Doubles_Layout_Blockdata::
	.incbin "assets/data.bin", 0x7454C, 0x264
	.align 2
TrainerTower_2F_Doubles_Layout::
	.4byte 18
	.4byte 17
	.4byte TrainerTower_2F_Doubles_Layout_Border
	.4byte TrainerTower_2F_Doubles_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_TrainerTower
	.byte 2
	.byte 2
	.2byte 0

TrainerTower_3F_Doubles_Layout_Border::
	.incbin "assets/data.bin", 0x747B0, 0x8
TrainerTower_3F_Doubles_Layout_Blockdata::
	.incbin "assets/data.bin", 0x747B8, 0x264
	.align 2
TrainerTower_3F_Doubles_Layout::
	.4byte 18
	.4byte 17
	.4byte TrainerTower_3F_Doubles_Layout_Border
	.4byte TrainerTower_3F_Doubles_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_TrainerTower
	.byte 2
	.byte 2
	.2byte 0

TrainerTower_4F_Doubles_Layout_Border::
	.incbin "assets/data.bin", 0x74A1C, 0x8
TrainerTower_4F_Doubles_Layout_Blockdata::
	.incbin "assets/data.bin", 0x74A24, 0x264
	.align 2
TrainerTower_4F_Doubles_Layout::
	.4byte 18
	.4byte 17
	.4byte TrainerTower_4F_Doubles_Layout_Border
	.4byte TrainerTower_4F_Doubles_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_TrainerTower
	.byte 2
	.byte 2
	.2byte 0

TrainerTower_5F_Doubles_Layout_Border::
	.incbin "assets/data.bin", 0x74C88, 0x8
TrainerTower_5F_Doubles_Layout_Blockdata::
	.incbin "assets/data.bin", 0x74C90, 0x264
	.align 2
TrainerTower_5F_Doubles_Layout::
	.4byte 18
	.4byte 17
	.4byte TrainerTower_5F_Doubles_Layout_Border
	.4byte TrainerTower_5F_Doubles_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_TrainerTower
	.byte 2
	.byte 2
	.2byte 0

TrainerTower_6F_Doubles_Layout_Border::
	.incbin "assets/data.bin", 0x74EF4, 0x8
TrainerTower_6F_Doubles_Layout_Blockdata::
	.incbin "assets/data.bin", 0x74EFC, 0x264
	.align 2
TrainerTower_6F_Doubles_Layout::
	.4byte 18
	.4byte 17
	.4byte TrainerTower_6F_Doubles_Layout_Border
	.4byte TrainerTower_6F_Doubles_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_TrainerTower
	.byte 2
	.byte 2
	.2byte 0

TrainerTower_7F_Doubles_Layout_Border::
	.incbin "assets/data.bin", 0x75160, 0x8
TrainerTower_7F_Doubles_Layout_Blockdata::
	.incbin "assets/data.bin", 0x75168, 0x264
	.align 2
TrainerTower_7F_Doubles_Layout::
	.4byte 18
	.4byte 17
	.4byte TrainerTower_7F_Doubles_Layout_Border
	.4byte TrainerTower_7F_Doubles_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_TrainerTower
	.byte 2
	.byte 2
	.2byte 0

TrainerTower_8F_Doubles_Layout_Border::
	.incbin "assets/data.bin", 0x753CC, 0x8
TrainerTower_8F_Doubles_Layout_Blockdata::
	.incbin "assets/data.bin", 0x753D4, 0x264
	.align 2
TrainerTower_8F_Doubles_Layout::
	.4byte 18
	.4byte 17
	.4byte TrainerTower_8F_Doubles_Layout_Border
	.4byte TrainerTower_8F_Doubles_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_TrainerTower
	.byte 2
	.byte 2
	.2byte 0

TrainerTower_1F_Knockout_Layout_Border::
	.incbin "assets/data.bin", 0x75638, 0x8
TrainerTower_1F_Knockout_Layout_Blockdata::
	.incbin "assets/data.bin", 0x75640, 0x264
	.align 2
TrainerTower_1F_Knockout_Layout::
	.4byte 18
	.4byte 17
	.4byte TrainerTower_1F_Knockout_Layout_Border
	.4byte TrainerTower_1F_Knockout_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_TrainerTower
	.byte 2
	.byte 2
	.2byte 0

TrainerTower_2F_Knockout_Layout_Border::
	.incbin "assets/data.bin", 0x758A4, 0x8
TrainerTower_2F_Knockout_Layout_Blockdata::
	.incbin "assets/data.bin", 0x758AC, 0x264
	.align 2
TrainerTower_2F_Knockout_Layout::
	.4byte 18
	.4byte 17
	.4byte TrainerTower_2F_Knockout_Layout_Border
	.4byte TrainerTower_2F_Knockout_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_TrainerTower
	.byte 2
	.byte 2
	.2byte 0

TrainerTower_3F_Knockout_Layout_Border::
	.incbin "assets/data.bin", 0x75B10, 0x8
TrainerTower_3F_Knockout_Layout_Blockdata::
	.incbin "assets/data.bin", 0x75B18, 0x264
	.align 2
TrainerTower_3F_Knockout_Layout::
	.4byte 18
	.4byte 17
	.4byte TrainerTower_3F_Knockout_Layout_Border
	.4byte TrainerTower_3F_Knockout_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_TrainerTower
	.byte 2
	.byte 2
	.2byte 0

TrainerTower_4F_Knockout_Layout_Border::
	.incbin "assets/data.bin", 0x75D7C, 0x8
TrainerTower_4F_Knockout_Layout_Blockdata::
	.incbin "assets/data.bin", 0x75D84, 0x264
	.align 2
TrainerTower_4F_Knockout_Layout::
	.4byte 18
	.4byte 17
	.4byte TrainerTower_4F_Knockout_Layout_Border
	.4byte TrainerTower_4F_Knockout_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_TrainerTower
	.byte 2
	.byte 2
	.2byte 0

TrainerTower_5F_Knockout_Layout_Border::
	.incbin "assets/data.bin", 0x75FE8, 0x8
TrainerTower_5F_Knockout_Layout_Blockdata::
	.incbin "assets/data.bin", 0x75FF0, 0x264
	.align 2
TrainerTower_5F_Knockout_Layout::
	.4byte 18
	.4byte 17
	.4byte TrainerTower_5F_Knockout_Layout_Border
	.4byte TrainerTower_5F_Knockout_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_TrainerTower
	.byte 2
	.byte 2
	.2byte 0

TrainerTower_6F_Knockout_Layout_Border::
	.incbin "assets/data.bin", 0x76254, 0x8
TrainerTower_6F_Knockout_Layout_Blockdata::
	.incbin "assets/data.bin", 0x7625C, 0x264
	.align 2
TrainerTower_6F_Knockout_Layout::
	.4byte 18
	.4byte 17
	.4byte TrainerTower_6F_Knockout_Layout_Border
	.4byte TrainerTower_6F_Knockout_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_TrainerTower
	.byte 2
	.byte 2
	.2byte 0

TrainerTower_7F_Knockout_Layout_Border::
	.incbin "assets/data.bin", 0x764C0, 0x8
TrainerTower_7F_Knockout_Layout_Blockdata::
	.incbin "assets/data.bin", 0x764C8, 0x264
	.align 2
TrainerTower_7F_Knockout_Layout::
	.4byte 18
	.4byte 17
	.4byte TrainerTower_7F_Knockout_Layout_Border
	.4byte TrainerTower_7F_Knockout_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_TrainerTower
	.byte 2
	.byte 2
	.2byte 0

TrainerTower_8F_Knockout_Layout_Border::
	.incbin "assets/data.bin", 0x7672C, 0x8
TrainerTower_8F_Knockout_Layout_Blockdata::
	.incbin "assets/data.bin", 0x76734, 0x264
	.align 2
TrainerTower_8F_Knockout_Layout::
	.4byte 18
	.4byte 17
	.4byte TrainerTower_8F_Knockout_Layout_Border
	.4byte TrainerTower_8F_Knockout_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_TrainerTower
	.byte 2
	.byte 2
	.2byte 0

SevenIsland_House_Room1_Layout_Border::
	.incbin "assets/data.bin", 0x76998, 0x8
SevenIsland_House_Room1_Layout_Blockdata::
	.incbin "assets/data.bin", 0x769A0, 0xC6
	.align 2
SevenIsland_House_Room1_Layout::
	.4byte 11
	.4byte 9
	.4byte SevenIsland_House_Room1_Layout_Border
	.4byte SevenIsland_House_Room1_Layout_Blockdata
	.4byte gTileset_Building
	.4byte gTileset_SeafoamIslands
	.byte 2
	.byte 2
	.2byte 0

OneIsland_KindleRoad_EmberSpa_Layout_Border::
	.incbin "assets/data.bin", 0x76A68, 0x8
OneIsland_KindleRoad_EmberSpa_Layout_Blockdata::
	.incbin "assets/data.bin", 0x76A70, 0x83A
	.align 2
OneIsland_KindleRoad_EmberSpa_Layout::
	.4byte 27
	.4byte 39
	.4byte OneIsland_KindleRoad_EmberSpa_Layout_Border
	.4byte OneIsland_KindleRoad_EmberSpa_Layout_Blockdata
	.4byte gTileset_General
	.4byte gTileset_MtEmber
	.byte 2
	.byte 2
	.2byte 0

@ ===== END data/layouts/layouts.inc =====
@ ===== BEGIN data/layouts/layouts_table.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/layouts/layouts.json
@

	.align 2
gMapLayouts::
	.4byte PalletTown_PlayersHouse_1F_Layout
	.4byte PalletTown_PlayersHouse_2F_Layout
	.4byte PalletTown_RivalsHouse_Layout
	.4byte LittlerootTown_MaysHouse_2F_Layout
	.4byte PalletTown_ProfessorOaksLab_Layout
	.4byte House1_Layout
	.4byte House2_Layout
	.4byte PokemonCenter_1F_Layout
	.4byte PokemonCenter_2F_Layout
	.4byte Mart_Layout
	.4byte House3_Layout
	.4byte CeruleanCity_Gym_Layout
	.4byte House4_Layout
	.4byte LavaridgeTown_HerbShop_Layout
	.4byte CeladonCity_Gym_Layout
	.4byte RS_PokemonCenter_1F_Layout
	.4byte FiveIsland_ResortGorgeous_House_Layout
	.4byte PacifidlogTown_House1_Layout
	.4byte PacifidlogTown_House2_Layout
	.4byte FuchsiaCity_Gym_Layout
	.4byte House5_Layout
	.4byte NULL
	.4byte NULL
	.4byte Unused1_Layout
	.4byte VermilionCity_Gym_Layout
	.4byte CeruleanCity_BikeShop_Layout
	.4byte CeladonCity_GameCorner_Layout
	.4byte PewterCity_Gym_Layout
	.4byte NULL
	.4byte FourIsland_LoreleisHouse_Layout
	.4byte ThreeIsland_House1_Layout
	.4byte RustboroCity_CuttersHouse_Layout
	.4byte FortreeCity_House1_Layout
	.4byte SaffronCity_Gym_Layout
	.4byte FortreeCity_House2_Layout
	.4byte CinnabarIsland_Gym_Layout
	.4byte ViridianCity_Gym_Layout
	.4byte NULL
	.4byte NULL
	.4byte NULL
	.4byte NULL
	.4byte NULL
	.4byte NULL
	.4byte NULL
	.4byte NULL
	.4byte RS_SafariZone_Entrance_Layout
	.4byte BattleColosseum_2P_Layout
	.4byte TradeCenter_Layout
	.4byte RecordCorner_Layout
	.4byte BattleColosseum_4P_Layout
	.4byte FuchsiaCity_SafariZone_Entrance_Layout
	.4byte RS_SafariZone_Northeast_Layout
	.4byte RS_SafariZone_Southwest_Layout
	.4byte RS_SafariZone_Southeast_Layout
	.4byte FortreeCity_DecorationShop_Layout
	.4byte NULL
	.4byte RS_BattleTower_Layout
	.4byte NULL
	.4byte NULL
	.4byte NULL
	.4byte NULL
	.4byte SSTidal_Corridor_Layout
	.4byte SSTidal_LowerDeck_Layout
	.4byte SSTidal_Rooms_Layout
	.4byte RustboroCity_Flat2_1F_Layout
	.4byte RustboroCity_Flat2_2F_Layout
	.4byte RustboroCity_Flat2_3F_Layout
	.4byte EverGrandeCity_HallOfFame_Layout
	.4byte MossdeepCity_EReaderTrainerHouse_1F_Layout
	.4byte MossdeepCity_EReaderTrainerHouse_2F_Layout
	.4byte SootopolisCity_House1_Layout
	.4byte SootopolisCity_House2_Layout
	.4byte SootopolisCity_House3_Layout
	.4byte RustboroCity_Flat1_1F_Layout
	.4byte RustboroCity_Flat1_2F_Layout
	.4byte NULL
	.4byte RS_SafariZone_RestHouse_Layout
	.4byte PalletTown_Layout
	.4byte ViridianCity_Layout
	.4byte PewterCity_Layout
	.4byte CeruleanCity_Layout
	.4byte LavenderTown_Layout
	.4byte VermilionCity_Layout
	.4byte CeladonCity_Layout
	.4byte FuchsiaCity_Layout
	.4byte CinnabarIsland_Layout
	.4byte IndigoPlateau_Exterior_Layout
	.4byte SaffronCity_Connection_Layout
	.4byte Route1_Layout
	.4byte Route2_Layout
	.4byte Route3_Layout
	.4byte Route4_Layout
	.4byte Route5_Layout
	.4byte Route6_Layout
	.4byte Route7_Layout
	.4byte Route8_Layout
	.4byte Route9_Layout
	.4byte Route10_Layout
	.4byte Route11_Layout
	.4byte Route12_Layout
	.4byte Route13_Layout
	.4byte Route14_Layout
	.4byte Route15_Layout
	.4byte Route16_Layout
	.4byte Route17_Layout
	.4byte Route18_Layout
	.4byte Route19_Layout
	.4byte Route20_Layout
	.4byte Route21_North_Layout
	.4byte Route22_Layout
	.4byte Route23_Layout
	.4byte Route24_Layout
	.4byte Route25_Layout
	.4byte MtMoon_1F_Layout
	.4byte MtMoon_B1F_Layout
	.4byte MtMoon_B2F_Layout
	.4byte ViridianForest_Layout
	.4byte SSAnne_Exterior_Layout
	.4byte SSAnne_1F_Corridor_Layout
	.4byte SSAnne_2F_Corridor_Layout
	.4byte SSAnne_3F_Corridor_Layout
	.4byte SSAnne_B1F_Corridor_Layout
	.4byte SSAnne_Deck_Layout
	.4byte DiglettsCave_B1F_Layout
	.4byte VictoryRoad_1F_Layout
	.4byte VictoryRoad_2F_Layout
	.4byte VictoryRoad_3F_Layout
	.4byte RocketHideout_B1F_Layout
	.4byte RocketHideout_B2F_Layout
	.4byte RocketHideout_B3F_Layout
	.4byte RocketHideout_B4F_Layout
	.4byte SilphCo_1F_Layout
	.4byte SilphCo_2F_Layout
	.4byte SilphCo_3F_Layout
	.4byte SilphCo_4F_Layout
	.4byte SilphCo_5F_Layout
	.4byte SilphCo_6F_Layout
	.4byte SilphCo_7F_Layout
	.4byte SilphCo_8F_Layout
	.4byte SilphCo_9F_Layout
	.4byte SilphCo_10F_Layout
	.4byte SilphCo_11F_Layout
	.4byte PokemonMansion_1F_Layout
	.4byte PokemonMansion_2F_Layout
	.4byte PokemonMansion_3F_Layout
	.4byte PokemonMansion_B1F_Layout
	.4byte SafariZone_Center_Layout
	.4byte SafariZone_East_Layout
	.4byte SafariZone_North_Layout
	.4byte SafariZone_West_Layout
	.4byte CeruleanCave_1F_Layout
	.4byte CeruleanCave_2F_Layout
	.4byte CeruleanCave_B1F_Layout
	.4byte RockTunnel_1F_Layout
	.4byte RockTunnel_B1F_Layout
	.4byte SeafoamIslands_1F_Layout
	.4byte SeafoamIslands_B1F_Layout
	.4byte SeafoamIslands_B2F_Layout
	.4byte SeafoamIslands_B3F_Layout
	.4byte SeafoamIslands_B4F_Layout
	.4byte PokemonTower_1F_Layout
	.4byte PokemonTower_2F_Layout
	.4byte PokemonTower_3F_Layout
	.4byte PokemonTower_4F_Layout
	.4byte PokemonTower_5F_Layout
	.4byte PokemonTower_6F_Layout
	.4byte PokemonTower_7F_Layout
	.4byte PowerPlant_Layout
	.4byte Route25_SeaCottage_Layout
	.4byte SSAnne_Kitchen_Layout
	.4byte SSAnne_CaptainsOffice_Layout
	.4byte UndergroundPath_Entrance_Layout
	.4byte UndergroundPath_EastWestTunnel_Layout
	.4byte UndergroundPath_NorthSouthTunnel_Layout
	.4byte NULL
	.4byte Route12_NorthEntrance_1F_Layout
	.4byte SSAnne_Room1_Layout
	.4byte SSAnne_Room2_Layout
	.4byte CeladonCity_DepartmentStore_Elevator_Layout
	.4byte PewterCity_Museum_1F_Layout
	.4byte PewterCity_Museum_2F_Layout
	.4byte CeruleanCity_House2_Layout
	.4byte CeruleanCity_House1_Layout
	.4byte CeladonCity_Condominiums_1F_Layout
	.4byte CeladonCity_Condominiums_2F_Layout
	.4byte CeladonCity_Condominiums_3F_Layout
	.4byte CeladonCity_Condominiums_Roof_Layout
	.4byte CeladonCity_Condominiums_RoofRoom_Layout
	.4byte CeladonCity_GameCorner_PrizeRoom_Layout
	.4byte CeladonCity_Restaurant_Layout
	.4byte CeladonCity_Hotel_Layout
	.4byte CeladonCity_DepartmentStore_1F_Layout
	.4byte CeladonCity_DepartmentStore_2F_Layout
	.4byte CeladonCity_DepartmentStore_3F_Layout
	.4byte CeladonCity_DepartmentStore_4F_Layout
	.4byte CeladonCity_DepartmentStore_5F_Layout
	.4byte CeladonCity_DepartmentStore_Roof_Layout
	.4byte SafariZone_RestHouse_Layout
	.4byte SafariZone_SecretHouse_Layout
	.4byte FuchsiaCity_SafariZone_Office_Layout
	.4byte FuchsiaCity_WardensHouse_Layout
	.4byte FuchsiaCity_House2_Layout
	.4byte CinnabarIsland_PokemonLab_Entrance_Layout
	.4byte CinnabarIsland_PokemonLab_Lounge_Layout
	.4byte CinnabarIsland_PokemonLab_ResearchRoom_Layout
	.4byte CinnabarIsland_PokemonLab_ExperimentRoom_Layout
	.4byte SaffronCity_Layout
	.4byte SaffronCity_NorthSouthEntrance_Layout
	.4byte SaffronCity_EastWestEntrance_Layout
	.4byte DiglettsCave_NorthEntrance_Layout
	.4byte DiglettsCave_SouthEntrance_Layout
	.4byte IndigoPlateau_PokemonCenter_1F_Layout
	.4byte PokemonLeague_LoreleisRoom_Layout
	.4byte PokemonLeague_BrunosRoom_Layout
	.4byte PokemonLeague_AgathasRoom_Layout
	.4byte PokemonLeague_LancesRoom_Layout
	.4byte PokemonLeague_ChampionsRoom_Layout
	.4byte PokemonLeague_HallOfFame_Layout
	.4byte Route21_South_Layout
	.4byte Entrance_2F_Layout
	.4byte Route2_Entrance_Layout
	.4byte Route22_NorthEntrance_Layout
	.4byte Route16_NorthEntrance_1F_Layout
	.4byte Entrance_1F_Layout
	.4byte RocketHideout_Elevator_Layout
	.4byte SaffronCity_CopycatsHouse_1F_Layout
	.4byte SaffronCity_CopycatsHouse_2F_Layout
	.4byte SaffronCity_Dojo_Layout
	.4byte SilphCo_Elevator_Layout
	.4byte OneIsland_Layout
	.4byte TwoIsland_Layout
	.4byte ThreeIsland_Layout
	.4byte FourIsland_Layout
	.4byte FiveIsland_Layout
	.4byte SevenIsland_Layout
	.4byte SixIsland_Layout
	.4byte OneIsland_KindleRoad_Layout
	.4byte OneIsland_TreasureBeach_Layout
	.4byte TwoIsland_CapeBrink_Layout
	.4byte ThreeIsland_BondBridge_Layout
	.4byte ThreeIsland_Port_Layout
	.4byte Prototype_SeviiIsle_6_Layout
	.4byte Prototype_SeviiIsle_7_Layout
	.4byte Prototype_SeviiIsle_8_Layout
	.4byte Prototype_SeviiIsle_9_Layout
	.4byte FiveIsland_ResortGorgeous_Layout
	.4byte FiveIsland_WaterLabyrinth_Layout
	.4byte FiveIsland_Meadow_Layout
	.4byte FiveIsland_MemorialPillar_Layout
	.4byte SixIsland_OutcastIsland_Layout
	.4byte SixIsland_GreenPath_Layout
	.4byte SixIsland_WaterPath_Layout
	.4byte SixIsland_RuinValley_Layout
	.4byte SevenIsland_TrainerTower_Layout
	.4byte SevenIsland_SevaultCanyon_Entrance_Layout
	.4byte SevenIsland_SevaultCanyon_Layout
	.4byte SevenIsland_TanobyRuins_Layout
	.4byte Prototype_SeviiIsle_22_Layout
	.4byte Prototype_SeviiIsle_23_East_Layout
	.4byte Prototype_SeviiIsle_23_West_Layout
	.4byte Prototype_SeviiIsle_24_Layout
	.4byte UnionRoom_Layout
	.4byte SaffronCity_PokemonTrainerFanClub_Layout
	.4byte SevenIsland_House_Room1_DoorOpen_Layout
	.4byte SevenIsland_House_Room2_Layout
	.4byte ViridianCity_School_Layout
	.4byte CeladonCity_Restaurant_Duplicate_Layout
	.4byte CeladonCity_Hotel_Duplicate_Layout
	.4byte MtEmber_RubyPath_B4F_Layout
	.4byte ThreeIsland_BerryForest_Layout
	.4byte OneIsland_PokemonCenter_1F_Layout
	.4byte TwoIsland_JoyfulGameCorner_Layout
	.4byte VermilionCity_PokemonFanClub_Layout
	.4byte LavenderTown_VolunteerPokemonHouse_Layout
	.4byte Route5_PokemonDayCare_Layout
	.4byte ViridianCity_House_Layout
	.4byte FourIsland_PokemonDayCare_Layout
	.4byte SeafoamIslands_B3F_CurrentStopped_Layout
	.4byte SeafoamIslands_B4F_CurrentStopped_Layout
	.4byte MtEmber_Exterior_Layout
	.4byte MtEmber_Summit_Layout
	.4byte MtEmber_SummitPath_1F_Layout
	.4byte MtEmber_SummitPath_2F_Layout
	.4byte MtEmber_SummitPath_3F_Layout
	.4byte MtEmber_RubyPath_1F_Layout
	.4byte MtEmber_RubyPath_B1F_Layout
	.4byte MtEmber_RubyPath_B2F_Layout
	.4byte MtEmber_RubyPath_B3F_Layout
	.4byte MtEmber_RubyPath_B1F_Stairs_Layout
	.4byte MtEmber_RubyPath_B2F_Stairs_Layout
	.4byte MtEmber_RubyPath_B5F_Layout
	.4byte FiveIsland_RocketWarehouse_Layout
	.4byte FourIsland_IcefallCave_Entrance_Layout
	.4byte FourIsland_IcefallCave_1F_Layout
	.4byte FourIsland_IcefallCave_B1F_Layout
	.4byte FourIsland_IcefallCave_Back_Layout
	.4byte TrainerTower_Lobby_Layout
	.4byte TrainerTower_1F_Layout
	.4byte TrainerTower_2F_Layout
	.4byte TrainerTower_3F_Layout
	.4byte TrainerTower_4F_Layout
	.4byte TrainerTower_5F_Layout
	.4byte TrainerTower_6F_Layout
	.4byte TrainerTower_7F_Layout
	.4byte TrainerTower_8F_Layout
	.4byte TrainerTower_Roof_Layout
	.4byte TrainerTower_Elevator_Layout
	.4byte CeruleanCity_House5_Layout
	.4byte SixIsland_DottedHole_1F_Layout
	.4byte SixIsland_DottedHole_B1F_Layout
	.4byte SixIsland_DottedHole_B2F_Layout
	.4byte SixIsland_DottedHole_B3F_Layout
	.4byte SixIsland_DottedHole_B4F_Layout
	.4byte SixIsland_DottedHole_SapphireRoom_Layout
	.4byte Island_Harbor_Layout
	.4byte OneIsland_PokemonCenter_2F_Layout
	.4byte SixIsland_PatternBush_Layout
	.4byte ThreeIsland_DunsparceTunnel_Layout
	.4byte ThreeIsland_DunsparceTunnel_DugOut_Layout
	.4byte FiveIsland_LostCave_Entrance_Layout
	.4byte FiveIsland_LostCave_Room1_Layout
	.4byte FiveIsland_LostCave_Room2_Layout
	.4byte FiveIsland_LostCave_Room3_Layout
	.4byte FiveIsland_LostCave_Room4_Layout
	.4byte FiveIsland_LostCave_Room5_Layout
	.4byte FiveIsland_LostCave_Room6_Layout
	.4byte FiveIsland_LostCave_Room7_Layout
	.4byte FiveIsland_LostCave_Room8_Layout
	.4byte FiveIsland_LostCave_Room9_Layout
	.4byte FiveIsland_LostCave_Room10_Layout
	.4byte FiveIsland_LostCave_Room11_Layout
	.4byte FiveIsland_LostCave_Room12_Layout
	.4byte FiveIsland_LostCave_Room13_Layout
	.4byte FiveIsland_LostCave_Room14_Layout
	.4byte SevenIsland_TanobyRuins_MoneanChamber_Layout
	.4byte SevenIsland_TanobyRuins_LiptooChamber_Layout
	.4byte SevenIsland_TanobyRuins_WeepthChamber_Layout
	.4byte SevenIsland_TanobyRuins_DilfordChamber_Layout
	.4byte SevenIsland_TanobyRuins_ScufibChamber_Layout
	.4byte SixIsland_AlteringCave_Layout
	.4byte SevenIsland_SevaultCanyon_TanobyKey_Layout
	.4byte BirthIsland_Exterior_Layout
	.4byte NavelRock_Exterior_Layout
	.4byte NavelRock_1F_Layout
	.4byte NavelRock_Summit_Layout
	.4byte NavelRock_Base_Layout
	.4byte NavelRock_SummitPath_2F_Layout
	.4byte NavelRock_SummitPath_3F_Layout
	.4byte NavelRock_SummitPath_4F_Layout
	.4byte NavelRock_SummitPath_5F_Layout
	.4byte NavelRock_BasePath_B1F_Layout
	.4byte NavelRock_BasePath_B2F_Layout
	.4byte NavelRock_BasePath_B3F_Layout
	.4byte NavelRock_BasePath_B4F_Layout
	.4byte NavelRock_BasePath_B5F_Layout
	.4byte NavelRock_BasePath_B6F_Layout
	.4byte NavelRock_BasePath_B7F_Layout
	.4byte NavelRock_BasePath_B8F_Layout
	.4byte NavelRock_BasePath_B9F_Layout
	.4byte NavelRock_BasePath_B10F_Layout
	.4byte NavelRock_BasePath_B11F_Layout
	.4byte SevenIsland_TanobyRuins_RixyChamber_Layout
	.4byte SevenIsland_TanobyRuins_ViapoisChamber_Layout
	.4byte NavelRock_B1F_Layout
	.4byte NavelRock_Fork_Layout
	.4byte TrainerTower_1F_Doubles_Layout
	.4byte TrainerTower_2F_Doubles_Layout
	.4byte TrainerTower_3F_Doubles_Layout
	.4byte TrainerTower_4F_Doubles_Layout
	.4byte TrainerTower_5F_Doubles_Layout
	.4byte TrainerTower_6F_Doubles_Layout
	.4byte TrainerTower_7F_Doubles_Layout
	.4byte TrainerTower_8F_Doubles_Layout
	.4byte TrainerTower_1F_Knockout_Layout
	.4byte TrainerTower_2F_Knockout_Layout
	.4byte TrainerTower_3F_Knockout_Layout
	.4byte TrainerTower_4F_Knockout_Layout
	.4byte TrainerTower_5F_Knockout_Layout
	.4byte TrainerTower_6F_Knockout_Layout
	.4byte TrainerTower_7F_Knockout_Layout
	.4byte TrainerTower_8F_Knockout_Layout
	.4byte SevenIsland_House_Room1_Layout
	.4byte OneIsland_KindleRoad_EmberSpa_Layout
@ ===== END data/layouts/layouts_table.inc =====
@ ===== BEGIN data/maps/headers.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/map_groups.json
@

@ ===== BEGIN data/maps/BattleColosseum_2P/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/BattleColosseum_2P/map.json
@

BattleColosseum_2P:
	.4byte BattleColosseum_2P_Layout
	.4byte BattleColosseum_2P_MapEvents
	.4byte BattleColosseum_2P_MapScripts
	.4byte NULL
	.2byte MUS_POKE_CENTER
	.2byte LAYOUT_BATTLE_COLOSSEUM_2P
	.byte MAPSEC_SPECIAL_AREA
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_LINK

@ ===== END data/maps/BattleColosseum_2P/header.inc =====
@ ===== BEGIN data/maps/TradeCenter/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/TradeCenter/map.json
@

TradeCenter:
	.4byte TradeCenter_Layout
	.4byte TradeCenter_MapEvents
	.4byte TradeCenter_MapScripts
	.4byte NULL
	.2byte MUS_POKE_CENTER
	.2byte LAYOUT_TRADE_CENTER
	.byte MAPSEC_SPECIAL_AREA
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/TradeCenter/header.inc =====
@ ===== BEGIN data/maps/RecordCorner/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/RecordCorner/map.json
@

RecordCorner:
	.4byte RecordCorner_Layout
	.4byte RecordCorner_MapEvents
	.4byte RecordCorner_MapScripts
	.4byte NULL
	.2byte MUS_POKE_CENTER
	.2byte LAYOUT_RECORD_CORNER
	.byte MAPSEC_SPECIAL_AREA
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/RecordCorner/header.inc =====
@ ===== BEGIN data/maps/BattleColosseum_4P/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/BattleColosseum_4P/map.json
@

BattleColosseum_4P:
	.4byte BattleColosseum_4P_Layout
	.4byte BattleColosseum_4P_MapEvents
	.4byte BattleColosseum_4P_MapScripts
	.4byte NULL
	.2byte MUS_POKE_CENTER
	.2byte LAYOUT_BATTLE_COLOSSEUM_4P
	.byte MAPSEC_SPECIAL_AREA
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_LINK

@ ===== END data/maps/BattleColosseum_4P/header.inc =====
@ ===== BEGIN data/maps/UnionRoom/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/UnionRoom/map.json
@

UnionRoom:
	.4byte UnionRoom_Layout
	.4byte UnionRoom_MapEvents
	.4byte UnionRoom_MapScripts
	.4byte NULL
	.2byte MUS_UNION_ROOM
	.2byte LAYOUT_UNION_ROOM
	.byte MAPSEC_SPECIAL_AREA
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_LINK

@ ===== END data/maps/UnionRoom/header.inc =====
@ ===== BEGIN data/maps/ViridianForest/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/ViridianForest/map.json
@

ViridianForest:
	.4byte ViridianForest_Layout
	.4byte ViridianForest_MapEvents
	.4byte ViridianForest_MapScripts
	.4byte NULL
	.2byte MUS_VIRIDIAN_FOREST
	.2byte LAYOUT_VIRIDIAN_FOREST
	.byte MAPSEC_VIRIDIAN_FOREST
	.byte FALSE
	.byte WEATHER_SHADE
	.byte MAP_TYPE_ROUTE
	map_header_flags allow_cycling=TRUE, allow_escaping=TRUE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/ViridianForest/header.inc =====
@ ===== BEGIN data/maps/MtMoon_1F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/MtMoon_1F/map.json
@

MtMoon_1F:
	.4byte MtMoon_1F_Layout
	.4byte MtMoon_1F_MapEvents
	.4byte MtMoon_1F_MapScripts
	.4byte NULL
	.2byte MUS_MT_MOON
	.2byte LAYOUT_MT_MOON_1F
	.byte MAPSEC_MT_MOON
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_UNDERGROUND
	map_header_flags allow_cycling=TRUE, allow_escaping=TRUE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/MtMoon_1F/header.inc =====
@ ===== BEGIN data/maps/MtMoon_B1F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/MtMoon_B1F/map.json
@

MtMoon_B1F:
	.4byte MtMoon_B1F_Layout
	.4byte MtMoon_B1F_MapEvents
	.4byte MtMoon_B1F_MapScripts
	.4byte NULL
	.2byte MUS_MT_MOON
	.2byte LAYOUT_MT_MOON_B1F
	.byte MAPSEC_MT_MOON
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_UNDERGROUND
	map_header_flags allow_cycling=TRUE, allow_escaping=TRUE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/MtMoon_B1F/header.inc =====
@ ===== BEGIN data/maps/MtMoon_B2F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/MtMoon_B2F/map.json
@

MtMoon_B2F:
	.4byte MtMoon_B2F_Layout
	.4byte MtMoon_B2F_MapEvents
	.4byte MtMoon_B2F_MapScripts
	.4byte NULL
	.2byte MUS_MT_MOON
	.2byte LAYOUT_MT_MOON_B2F
	.byte MAPSEC_MT_MOON
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_UNDERGROUND
	map_header_flags allow_cycling=TRUE, allow_escaping=TRUE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/MtMoon_B2F/header.inc =====
@ ===== BEGIN data/maps/SSAnne_Exterior/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SSAnne_Exterior/map.json
@

SSAnne_Exterior:
	.4byte SSAnne_Exterior_Layout
	.4byte SSAnne_Exterior_MapEvents
	.4byte SSAnne_Exterior_MapScripts
	.4byte NULL
	.2byte MUS_SS_ANNE
	.2byte LAYOUT_SSANNE_EXTERIOR
	.byte MAPSEC_S_S_ANNE
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SSAnne_Exterior/header.inc =====
@ ===== BEGIN data/maps/SSAnne_1F_Corridor/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SSAnne_1F_Corridor/map.json
@

SSAnne_1F_Corridor:
	.4byte SSAnne_1F_Corridor_Layout
	.4byte SSAnne_1F_Corridor_MapEvents
	.4byte SSAnne_1F_Corridor_MapScripts
	.4byte NULL
	.2byte MUS_SS_ANNE
	.2byte LAYOUT_SSANNE_1F_CORRIDOR
	.byte MAPSEC_S_S_ANNE
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SSAnne_1F_Corridor/header.inc =====
@ ===== BEGIN data/maps/SSAnne_2F_Corridor/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SSAnne_2F_Corridor/map.json
@

SSAnne_2F_Corridor:
	.4byte SSAnne_2F_Corridor_Layout
	.4byte SSAnne_2F_Corridor_MapEvents
	.4byte SSAnne_2F_Corridor_MapScripts
	.4byte NULL
	.2byte MUS_SS_ANNE
	.2byte LAYOUT_SSANNE_2F_CORRIDOR
	.byte MAPSEC_S_S_ANNE
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SSAnne_2F_Corridor/header.inc =====
@ ===== BEGIN data/maps/SSAnne_3F_Corridor/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SSAnne_3F_Corridor/map.json
@

SSAnne_3F_Corridor:
	.4byte SSAnne_3F_Corridor_Layout
	.4byte SSAnne_3F_Corridor_MapEvents
	.4byte SSAnne_3F_Corridor_MapScripts
	.4byte NULL
	.2byte MUS_SS_ANNE
	.2byte LAYOUT_SSANNE_3F_CORRIDOR
	.byte MAPSEC_S_S_ANNE
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SSAnne_3F_Corridor/header.inc =====
@ ===== BEGIN data/maps/SSAnne_B1F_Corridor/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SSAnne_B1F_Corridor/map.json
@

SSAnne_B1F_Corridor:
	.4byte SSAnne_B1F_Corridor_Layout
	.4byte SSAnne_B1F_Corridor_MapEvents
	.4byte SSAnne_B1F_Corridor_MapScripts
	.4byte NULL
	.2byte MUS_SS_ANNE
	.2byte LAYOUT_SSANNE_B1F_CORRIDOR
	.byte MAPSEC_S_S_ANNE
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SSAnne_B1F_Corridor/header.inc =====
@ ===== BEGIN data/maps/SSAnne_Deck/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SSAnne_Deck/map.json
@

SSAnne_Deck:
	.4byte SSAnne_Deck_Layout
	.4byte SSAnne_Deck_MapEvents
	.4byte SSAnne_Deck_MapScripts
	.4byte NULL
	.2byte MUS_SS_ANNE
	.2byte LAYOUT_SSANNE_DECK
	.byte MAPSEC_S_S_ANNE
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SSAnne_Deck/header.inc =====
@ ===== BEGIN data/maps/SSAnne_Kitchen/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SSAnne_Kitchen/map.json
@

SSAnne_Kitchen:
	.4byte SSAnne_Kitchen_Layout
	.4byte SSAnne_Kitchen_MapEvents
	.4byte SSAnne_Kitchen_MapScripts
	.4byte NULL
	.2byte MUS_SS_ANNE
	.2byte LAYOUT_SSANNE_KITCHEN
	.byte MAPSEC_S_S_ANNE
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SSAnne_Kitchen/header.inc =====
@ ===== BEGIN data/maps/SSAnne_CaptainsOffice/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SSAnne_CaptainsOffice/map.json
@

SSAnne_CaptainsOffice:
	.4byte SSAnne_CaptainsOffice_Layout
	.4byte SSAnne_CaptainsOffice_MapEvents
	.4byte SSAnne_CaptainsOffice_MapScripts
	.4byte NULL
	.2byte MUS_SS_ANNE
	.2byte LAYOUT_SSANNE_CAPTAINS_OFFICE
	.byte MAPSEC_S_S_ANNE
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SSAnne_CaptainsOffice/header.inc =====
@ ===== BEGIN data/maps/SSAnne_1F_Room1/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SSAnne_1F_Room1/map.json
@

SSAnne_1F_Room1:
	.4byte SSAnne_Room1_Layout
	.4byte SSAnne_1F_Room1_MapEvents
	.4byte SSAnne_1F_Room1_MapScripts
	.4byte NULL
	.2byte MUS_SS_ANNE
	.2byte LAYOUT_SSANNE_ROOM1
	.byte MAPSEC_S_S_ANNE
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SSAnne_1F_Room1/header.inc =====
@ ===== BEGIN data/maps/SSAnne_1F_Room2/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SSAnne_1F_Room2/map.json
@

SSAnne_1F_Room2:
	.4byte SSAnne_Room1_Layout
	.4byte SSAnne_1F_Room2_MapEvents
	.4byte SSAnne_1F_Room2_MapScripts
	.4byte NULL
	.2byte MUS_SS_ANNE
	.2byte LAYOUT_SSANNE_ROOM1
	.byte MAPSEC_S_S_ANNE
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SSAnne_1F_Room2/header.inc =====
@ ===== BEGIN data/maps/SSAnne_1F_Room3/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SSAnne_1F_Room3/map.json
@

SSAnne_1F_Room3:
	.4byte SSAnne_Room1_Layout
	.4byte SSAnne_1F_Room3_MapEvents
	.4byte SSAnne_1F_Room3_MapScripts
	.4byte NULL
	.2byte MUS_SS_ANNE
	.2byte LAYOUT_SSANNE_ROOM1
	.byte MAPSEC_S_S_ANNE
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SSAnne_1F_Room3/header.inc =====
@ ===== BEGIN data/maps/SSAnne_1F_Room4/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SSAnne_1F_Room4/map.json
@

SSAnne_1F_Room4:
	.4byte SSAnne_Room1_Layout
	.4byte SSAnne_1F_Room4_MapEvents
	.4byte SSAnne_1F_Room4_MapScripts
	.4byte NULL
	.2byte MUS_SS_ANNE
	.2byte LAYOUT_SSANNE_ROOM1
	.byte MAPSEC_S_S_ANNE
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SSAnne_1F_Room4/header.inc =====
@ ===== BEGIN data/maps/SSAnne_1F_Room5/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SSAnne_1F_Room5/map.json
@

SSAnne_1F_Room5:
	.4byte SSAnne_Room1_Layout
	.4byte SSAnne_1F_Room5_MapEvents
	.4byte SSAnne_1F_Room5_MapScripts
	.4byte NULL
	.2byte MUS_SS_ANNE
	.2byte LAYOUT_SSANNE_ROOM1
	.byte MAPSEC_S_S_ANNE
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SSAnne_1F_Room5/header.inc =====
@ ===== BEGIN data/maps/SSAnne_1F_Room7/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SSAnne_1F_Room7/map.json
@

SSAnne_1F_Room7:
	.4byte SSAnne_Room1_Layout
	.4byte SSAnne_1F_Room7_MapEvents
	.4byte SSAnne_1F_Room7_MapScripts
	.4byte NULL
	.2byte MUS_SS_ANNE
	.2byte LAYOUT_SSANNE_ROOM1
	.byte MAPSEC_S_S_ANNE
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SSAnne_1F_Room7/header.inc =====
@ ===== BEGIN data/maps/SSAnne_2F_Room1/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SSAnne_2F_Room1/map.json
@

SSAnne_2F_Room1:
	.4byte SSAnne_Room2_Layout
	.4byte SSAnne_2F_Room1_MapEvents
	.4byte SSAnne_2F_Room1_MapScripts
	.4byte NULL
	.2byte MUS_SS_ANNE
	.2byte LAYOUT_SSANNE_ROOM2
	.byte MAPSEC_S_S_ANNE
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SSAnne_2F_Room1/header.inc =====
@ ===== BEGIN data/maps/SSAnne_2F_Room2/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SSAnne_2F_Room2/map.json
@

SSAnne_2F_Room2:
	.4byte SSAnne_Room2_Layout
	.4byte SSAnne_2F_Room2_MapEvents
	.4byte SSAnne_2F_Room2_MapScripts
	.4byte NULL
	.2byte MUS_SS_ANNE
	.2byte LAYOUT_SSANNE_ROOM2
	.byte MAPSEC_S_S_ANNE
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SSAnne_2F_Room2/header.inc =====
@ ===== BEGIN data/maps/SSAnne_2F_Room3/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SSAnne_2F_Room3/map.json
@

SSAnne_2F_Room3:
	.4byte SSAnne_Room2_Layout
	.4byte SSAnne_2F_Room3_MapEvents
	.4byte SSAnne_2F_Room3_MapScripts
	.4byte NULL
	.2byte MUS_SS_ANNE
	.2byte LAYOUT_SSANNE_ROOM2
	.byte MAPSEC_S_S_ANNE
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SSAnne_2F_Room3/header.inc =====
@ ===== BEGIN data/maps/SSAnne_2F_Room4/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SSAnne_2F_Room4/map.json
@

SSAnne_2F_Room4:
	.4byte SSAnne_Room2_Layout
	.4byte SSAnne_2F_Room4_MapEvents
	.4byte SSAnne_2F_Room4_MapScripts
	.4byte NULL
	.2byte MUS_SS_ANNE
	.2byte LAYOUT_SSANNE_ROOM2
	.byte MAPSEC_S_S_ANNE
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SSAnne_2F_Room4/header.inc =====
@ ===== BEGIN data/maps/SSAnne_2F_Room5/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SSAnne_2F_Room5/map.json
@

SSAnne_2F_Room5:
	.4byte SSAnne_Room2_Layout
	.4byte SSAnne_2F_Room5_MapEvents
	.4byte SSAnne_2F_Room5_MapScripts
	.4byte NULL
	.2byte MUS_SS_ANNE
	.2byte LAYOUT_SSANNE_ROOM2
	.byte MAPSEC_S_S_ANNE
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SSAnne_2F_Room5/header.inc =====
@ ===== BEGIN data/maps/SSAnne_2F_Room6/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SSAnne_2F_Room6/map.json
@

SSAnne_2F_Room6:
	.4byte SSAnne_Room2_Layout
	.4byte SSAnne_2F_Room6_MapEvents
	.4byte SSAnne_2F_Room6_MapScripts
	.4byte NULL
	.2byte MUS_SS_ANNE
	.2byte LAYOUT_SSANNE_ROOM2
	.byte MAPSEC_S_S_ANNE
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SSAnne_2F_Room6/header.inc =====
@ ===== BEGIN data/maps/SSAnne_B1F_Room1/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SSAnne_B1F_Room1/map.json
@

SSAnne_B1F_Room1:
	.4byte SSAnne_Room2_Layout
	.4byte SSAnne_B1F_Room1_MapEvents
	.4byte SSAnne_B1F_Room1_MapScripts
	.4byte NULL
	.2byte MUS_SS_ANNE
	.2byte LAYOUT_SSANNE_ROOM2
	.byte MAPSEC_S_S_ANNE
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SSAnne_B1F_Room1/header.inc =====
@ ===== BEGIN data/maps/SSAnne_B1F_Room2/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SSAnne_B1F_Room2/map.json
@

SSAnne_B1F_Room2:
	.4byte SSAnne_Room2_Layout
	.4byte SSAnne_B1F_Room2_MapEvents
	.4byte SSAnne_B1F_Room2_MapScripts
	.4byte NULL
	.2byte MUS_SS_ANNE
	.2byte LAYOUT_SSANNE_ROOM2
	.byte MAPSEC_S_S_ANNE
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SSAnne_B1F_Room2/header.inc =====
@ ===== BEGIN data/maps/SSAnne_B1F_Room3/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SSAnne_B1F_Room3/map.json
@

SSAnne_B1F_Room3:
	.4byte SSAnne_Room2_Layout
	.4byte SSAnne_B1F_Room3_MapEvents
	.4byte SSAnne_B1F_Room3_MapScripts
	.4byte NULL
	.2byte MUS_SS_ANNE
	.2byte LAYOUT_SSANNE_ROOM2
	.byte MAPSEC_S_S_ANNE
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SSAnne_B1F_Room3/header.inc =====
@ ===== BEGIN data/maps/SSAnne_B1F_Room4/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SSAnne_B1F_Room4/map.json
@

SSAnne_B1F_Room4:
	.4byte SSAnne_Room2_Layout
	.4byte SSAnne_B1F_Room4_MapEvents
	.4byte SSAnne_B1F_Room4_MapScripts
	.4byte NULL
	.2byte MUS_SS_ANNE
	.2byte LAYOUT_SSANNE_ROOM2
	.byte MAPSEC_S_S_ANNE
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SSAnne_B1F_Room4/header.inc =====
@ ===== BEGIN data/maps/SSAnne_B1F_Room5/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SSAnne_B1F_Room5/map.json
@

SSAnne_B1F_Room5:
	.4byte SSAnne_Room2_Layout
	.4byte SSAnne_B1F_Room5_MapEvents
	.4byte SSAnne_B1F_Room5_MapScripts
	.4byte NULL
	.2byte MUS_SS_ANNE
	.2byte LAYOUT_SSANNE_ROOM2
	.byte MAPSEC_S_S_ANNE
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SSAnne_B1F_Room5/header.inc =====
@ ===== BEGIN data/maps/SSAnne_1F_Room6/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SSAnne_1F_Room6/map.json
@

SSAnne_1F_Room6:
	.4byte SSAnne_Room1_Layout
	.4byte SSAnne_1F_Room6_MapEvents
	.4byte SSAnne_1F_Room6_MapScripts
	.4byte NULL
	.2byte MUS_SS_ANNE
	.2byte LAYOUT_SSANNE_ROOM1
	.byte MAPSEC_S_S_ANNE
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SSAnne_1F_Room6/header.inc =====
@ ===== BEGIN data/maps/UndergroundPath_NorthEntrance/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/UndergroundPath_NorthEntrance/map.json
@

UndergroundPath_NorthEntrance:
	.4byte UndergroundPath_Entrance_Layout
	.4byte UndergroundPath_NorthEntrance_MapEvents
	.4byte UndergroundPath_NorthEntrance_MapScripts
	.4byte NULL
	.2byte MUS_PEWTER
	.2byte LAYOUT_UNDERGROUND_PATH_ENTRANCE
	.byte MAPSEC_UNDERGROUND_PATH
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/UndergroundPath_NorthEntrance/header.inc =====
@ ===== BEGIN data/maps/UndergroundPath_NorthSouthTunnel/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/UndergroundPath_NorthSouthTunnel/map.json
@

UndergroundPath_NorthSouthTunnel:
	.4byte UndergroundPath_NorthSouthTunnel_Layout
	.4byte UndergroundPath_NorthSouthTunnel_MapEvents
	.4byte UndergroundPath_NorthSouthTunnel_MapScripts
	.4byte NULL
	.2byte MUS_ROUTE1
	.2byte LAYOUT_UNDERGROUND_PATH_NORTH_SOUTH_TUNNEL
	.byte MAPSEC_UNDERGROUND_PATH
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=TRUE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/UndergroundPath_NorthSouthTunnel/header.inc =====
@ ===== BEGIN data/maps/UndergroundPath_SouthEntrance/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/UndergroundPath_SouthEntrance/map.json
@

UndergroundPath_SouthEntrance:
	.4byte UndergroundPath_Entrance_Layout
	.4byte UndergroundPath_SouthEntrance_MapEvents
	.4byte UndergroundPath_SouthEntrance_MapScripts
	.4byte NULL
	.2byte MUS_PEWTER
	.2byte LAYOUT_UNDERGROUND_PATH_ENTRANCE
	.byte MAPSEC_UNDERGROUND_PATH
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/UndergroundPath_SouthEntrance/header.inc =====
@ ===== BEGIN data/maps/UndergroundPath_WestEntrance/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/UndergroundPath_WestEntrance/map.json
@

UndergroundPath_WestEntrance:
	.4byte UndergroundPath_Entrance_Layout
	.4byte UndergroundPath_WestEntrance_MapEvents
	.4byte UndergroundPath_WestEntrance_MapScripts
	.4byte NULL
	.2byte MUS_PEWTER
	.2byte LAYOUT_UNDERGROUND_PATH_ENTRANCE
	.byte MAPSEC_UNDERGROUND_PATH_2
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/UndergroundPath_WestEntrance/header.inc =====
@ ===== BEGIN data/maps/UndergroundPath_EastWestTunnel/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/UndergroundPath_EastWestTunnel/map.json
@

UndergroundPath_EastWestTunnel:
	.4byte UndergroundPath_EastWestTunnel_Layout
	.4byte UndergroundPath_EastWestTunnel_MapEvents
	.4byte UndergroundPath_EastWestTunnel_MapScripts
	.4byte NULL
	.2byte MUS_ROUTE1
	.2byte LAYOUT_UNDERGROUND_PATH_EAST_WEST_TUNNEL
	.byte MAPSEC_UNDERGROUND_PATH_2
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=TRUE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/UndergroundPath_EastWestTunnel/header.inc =====
@ ===== BEGIN data/maps/UndergroundPath_EastEntrance/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/UndergroundPath_EastEntrance/map.json
@

UndergroundPath_EastEntrance:
	.4byte UndergroundPath_Entrance_Layout
	.4byte UndergroundPath_EastEntrance_MapEvents
	.4byte UndergroundPath_EastEntrance_MapScripts
	.4byte NULL
	.2byte MUS_PEWTER
	.2byte LAYOUT_UNDERGROUND_PATH_ENTRANCE
	.byte MAPSEC_UNDERGROUND_PATH_2
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/UndergroundPath_EastEntrance/header.inc =====
@ ===== BEGIN data/maps/DiglettsCave_NorthEntrance/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/DiglettsCave_NorthEntrance/map.json
@

DiglettsCave_NorthEntrance:
	.4byte DiglettsCave_NorthEntrance_Layout
	.4byte DiglettsCave_NorthEntrance_MapEvents
	.4byte DiglettsCave_NorthEntrance_MapScripts
	.4byte NULL
	.2byte MUS_VIRIDIAN_FOREST
	.2byte LAYOUT_DIGLETTS_CAVE_NORTH_ENTRANCE
	.byte MAPSEC_DIGLETTS_CAVE
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_UNDERGROUND
	map_header_flags allow_cycling=TRUE, allow_escaping=TRUE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/DiglettsCave_NorthEntrance/header.inc =====
@ ===== BEGIN data/maps/DiglettsCave_B1F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/DiglettsCave_B1F/map.json
@

DiglettsCave_B1F:
	.4byte DiglettsCave_B1F_Layout
	.4byte DiglettsCave_B1F_MapEvents
	.4byte DiglettsCave_B1F_MapScripts
	.4byte NULL
	.2byte MUS_VIRIDIAN_FOREST
	.2byte LAYOUT_DIGLETTS_CAVE_B1F
	.byte MAPSEC_DIGLETTS_CAVE
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_UNDERGROUND
	map_header_flags allow_cycling=TRUE, allow_escaping=TRUE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/DiglettsCave_B1F/header.inc =====
@ ===== BEGIN data/maps/DiglettsCave_SouthEntrance/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/DiglettsCave_SouthEntrance/map.json
@

DiglettsCave_SouthEntrance:
	.4byte DiglettsCave_SouthEntrance_Layout
	.4byte DiglettsCave_SouthEntrance_MapEvents
	.4byte DiglettsCave_SouthEntrance_MapScripts
	.4byte NULL
	.2byte MUS_VIRIDIAN_FOREST
	.2byte LAYOUT_DIGLETTS_CAVE_SOUTH_ENTRANCE
	.byte MAPSEC_DIGLETTS_CAVE
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_UNDERGROUND
	map_header_flags allow_cycling=TRUE, allow_escaping=TRUE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/DiglettsCave_SouthEntrance/header.inc =====
@ ===== BEGIN data/maps/VictoryRoad_1F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/VictoryRoad_1F/map.json
@

VictoryRoad_1F:
	.4byte VictoryRoad_1F_Layout
	.4byte VictoryRoad_1F_MapEvents
	.4byte VictoryRoad_1F_MapScripts
	.4byte NULL
	.2byte MUS_MT_MOON
	.2byte LAYOUT_VICTORY_ROAD_1F
	.byte MAPSEC_KANTO_VICTORY_ROAD
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_UNDERGROUND
	map_header_flags allow_cycling=TRUE, allow_escaping=TRUE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/VictoryRoad_1F/header.inc =====
@ ===== BEGIN data/maps/VictoryRoad_2F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/VictoryRoad_2F/map.json
@

VictoryRoad_2F:
	.4byte VictoryRoad_2F_Layout
	.4byte VictoryRoad_2F_MapEvents
	.4byte VictoryRoad_2F_MapScripts
	.4byte NULL
	.2byte MUS_MT_MOON
	.2byte LAYOUT_VICTORY_ROAD_2F
	.byte MAPSEC_KANTO_VICTORY_ROAD
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_UNDERGROUND
	map_header_flags allow_cycling=TRUE, allow_escaping=TRUE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/VictoryRoad_2F/header.inc =====
@ ===== BEGIN data/maps/VictoryRoad_3F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/VictoryRoad_3F/map.json
@

VictoryRoad_3F:
	.4byte VictoryRoad_3F_Layout
	.4byte VictoryRoad_3F_MapEvents
	.4byte VictoryRoad_3F_MapScripts
	.4byte NULL
	.2byte MUS_MT_MOON
	.2byte LAYOUT_VICTORY_ROAD_3F
	.byte MAPSEC_KANTO_VICTORY_ROAD
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_UNDERGROUND
	map_header_flags allow_cycling=TRUE, allow_escaping=TRUE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/VictoryRoad_3F/header.inc =====
@ ===== BEGIN data/maps/RocketHideout_B1F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/RocketHideout_B1F/map.json
@

RocketHideout_B1F:
	.4byte RocketHideout_B1F_Layout
	.4byte RocketHideout_B1F_MapEvents
	.4byte RocketHideout_B1F_MapScripts
	.4byte NULL
	.2byte MUS_ROCKET_HIDEOUT
	.2byte LAYOUT_ROCKET_HIDEOUT_B1F
	.byte MAPSEC_ROCKET_HIDEOUT
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=TRUE, allow_running=TRUE, show_map_name=TRUE
	.byte -1
	.byte MAP_BATTLE_SCENE_INDOOR_2

@ ===== END data/maps/RocketHideout_B1F/header.inc =====
@ ===== BEGIN data/maps/RocketHideout_B2F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/RocketHideout_B2F/map.json
@

RocketHideout_B2F:
	.4byte RocketHideout_B2F_Layout
	.4byte RocketHideout_B2F_MapEvents
	.4byte RocketHideout_B2F_MapScripts
	.4byte NULL
	.2byte MUS_ROCKET_HIDEOUT
	.2byte LAYOUT_ROCKET_HIDEOUT_B2F
	.byte MAPSEC_ROCKET_HIDEOUT
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=TRUE, allow_running=TRUE, show_map_name=TRUE
	.byte -2
	.byte MAP_BATTLE_SCENE_INDOOR_2

@ ===== END data/maps/RocketHideout_B2F/header.inc =====
@ ===== BEGIN data/maps/RocketHideout_B3F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/RocketHideout_B3F/map.json
@

RocketHideout_B3F:
	.4byte RocketHideout_B3F_Layout
	.4byte RocketHideout_B3F_MapEvents
	.4byte RocketHideout_B3F_MapScripts
	.4byte NULL
	.2byte MUS_ROCKET_HIDEOUT
	.2byte LAYOUT_ROCKET_HIDEOUT_B3F
	.byte MAPSEC_ROCKET_HIDEOUT
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=TRUE, allow_running=TRUE, show_map_name=TRUE
	.byte -3
	.byte MAP_BATTLE_SCENE_INDOOR_2

@ ===== END data/maps/RocketHideout_B3F/header.inc =====
@ ===== BEGIN data/maps/RocketHideout_B4F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/RocketHideout_B4F/map.json
@

RocketHideout_B4F:
	.4byte RocketHideout_B4F_Layout
	.4byte RocketHideout_B4F_MapEvents
	.4byte RocketHideout_B4F_MapScripts
	.4byte NULL
	.2byte MUS_ROCKET_HIDEOUT
	.2byte LAYOUT_ROCKET_HIDEOUT_B4F
	.byte MAPSEC_ROCKET_HIDEOUT
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=TRUE, allow_running=TRUE, show_map_name=TRUE
	.byte -4
	.byte MAP_BATTLE_SCENE_INDOOR_2

@ ===== END data/maps/RocketHideout_B4F/header.inc =====
@ ===== BEGIN data/maps/RocketHideout_Elevator/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/RocketHideout_Elevator/map.json
@

RocketHideout_Elevator:
	.4byte RocketHideout_Elevator_Layout
	.4byte RocketHideout_Elevator_MapEvents
	.4byte RocketHideout_Elevator_MapScripts
	.4byte NULL
	.2byte MUS_ROCKET_HIDEOUT
	.2byte LAYOUT_ROCKET_HIDEOUT_ELEVATOR
	.byte MAPSEC_ROCKET_HIDEOUT
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_INDOOR_2

@ ===== END data/maps/RocketHideout_Elevator/header.inc =====
@ ===== BEGIN data/maps/SilphCo_1F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SilphCo_1F/map.json
@

SilphCo_1F:
	.4byte SilphCo_1F_Layout
	.4byte SilphCo_1F_MapEvents
	.4byte SilphCo_1F_MapScripts
	.4byte NULL
	.2byte MUS_SILPH
	.2byte LAYOUT_SILPH_CO_1F
	.byte MAPSEC_SILPH_CO
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=TRUE, allow_running=TRUE, show_map_name=TRUE
	.byte 1
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SilphCo_1F/header.inc =====
@ ===== BEGIN data/maps/SilphCo_2F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SilphCo_2F/map.json
@

SilphCo_2F:
	.4byte SilphCo_2F_Layout
	.4byte SilphCo_2F_MapEvents
	.4byte SilphCo_2F_MapScripts
	.4byte NULL
	.2byte MUS_SILPH
	.2byte LAYOUT_SILPH_CO_2F
	.byte MAPSEC_SILPH_CO
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=TRUE, allow_running=TRUE, show_map_name=TRUE
	.byte 2
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SilphCo_2F/header.inc =====
@ ===== BEGIN data/maps/SilphCo_3F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SilphCo_3F/map.json
@

SilphCo_3F:
	.4byte SilphCo_3F_Layout
	.4byte SilphCo_3F_MapEvents
	.4byte SilphCo_3F_MapScripts
	.4byte NULL
	.2byte MUS_SILPH
	.2byte LAYOUT_SILPH_CO_3F
	.byte MAPSEC_SILPH_CO
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=TRUE, allow_running=TRUE, show_map_name=TRUE
	.byte 3
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SilphCo_3F/header.inc =====
@ ===== BEGIN data/maps/SilphCo_4F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SilphCo_4F/map.json
@

SilphCo_4F:
	.4byte SilphCo_4F_Layout
	.4byte SilphCo_4F_MapEvents
	.4byte SilphCo_4F_MapScripts
	.4byte NULL
	.2byte MUS_SILPH
	.2byte LAYOUT_SILPH_CO_4F
	.byte MAPSEC_SILPH_CO
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=TRUE, allow_running=TRUE, show_map_name=TRUE
	.byte 4
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SilphCo_4F/header.inc =====
@ ===== BEGIN data/maps/SilphCo_5F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SilphCo_5F/map.json
@

SilphCo_5F:
	.4byte SilphCo_5F_Layout
	.4byte SilphCo_5F_MapEvents
	.4byte SilphCo_5F_MapScripts
	.4byte NULL
	.2byte MUS_SILPH
	.2byte LAYOUT_SILPH_CO_5F
	.byte MAPSEC_SILPH_CO
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=TRUE, allow_running=TRUE, show_map_name=TRUE
	.byte 5
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SilphCo_5F/header.inc =====
@ ===== BEGIN data/maps/SilphCo_6F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SilphCo_6F/map.json
@

SilphCo_6F:
	.4byte SilphCo_6F_Layout
	.4byte SilphCo_6F_MapEvents
	.4byte SilphCo_6F_MapScripts
	.4byte NULL
	.2byte MUS_SILPH
	.2byte LAYOUT_SILPH_CO_6F
	.byte MAPSEC_SILPH_CO
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=TRUE, allow_running=TRUE, show_map_name=TRUE
	.byte 6
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SilphCo_6F/header.inc =====
@ ===== BEGIN data/maps/SilphCo_7F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SilphCo_7F/map.json
@

SilphCo_7F:
	.4byte SilphCo_7F_Layout
	.4byte SilphCo_7F_MapEvents
	.4byte SilphCo_7F_MapScripts
	.4byte NULL
	.2byte MUS_SILPH
	.2byte LAYOUT_SILPH_CO_7F
	.byte MAPSEC_SILPH_CO
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=TRUE, allow_running=TRUE, show_map_name=TRUE
	.byte 7
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SilphCo_7F/header.inc =====
@ ===== BEGIN data/maps/SilphCo_8F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SilphCo_8F/map.json
@

SilphCo_8F:
	.4byte SilphCo_8F_Layout
	.4byte SilphCo_8F_MapEvents
	.4byte SilphCo_8F_MapScripts
	.4byte NULL
	.2byte MUS_SILPH
	.2byte LAYOUT_SILPH_CO_8F
	.byte MAPSEC_SILPH_CO
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=TRUE, allow_running=TRUE, show_map_name=TRUE
	.byte 8
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SilphCo_8F/header.inc =====
@ ===== BEGIN data/maps/SilphCo_9F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SilphCo_9F/map.json
@

SilphCo_9F:
	.4byte SilphCo_9F_Layout
	.4byte SilphCo_9F_MapEvents
	.4byte SilphCo_9F_MapScripts
	.4byte NULL
	.2byte MUS_SILPH
	.2byte LAYOUT_SILPH_CO_9F
	.byte MAPSEC_SILPH_CO
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=TRUE, allow_running=TRUE, show_map_name=TRUE
	.byte 9
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SilphCo_9F/header.inc =====
@ ===== BEGIN data/maps/SilphCo_10F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SilphCo_10F/map.json
@

SilphCo_10F:
	.4byte SilphCo_10F_Layout
	.4byte SilphCo_10F_MapEvents
	.4byte SilphCo_10F_MapScripts
	.4byte NULL
	.2byte MUS_SILPH
	.2byte LAYOUT_SILPH_CO_10F
	.byte MAPSEC_SILPH_CO
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=TRUE, allow_running=TRUE, show_map_name=TRUE
	.byte 10
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SilphCo_10F/header.inc =====
@ ===== BEGIN data/maps/SilphCo_11F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SilphCo_11F/map.json
@

SilphCo_11F:
	.4byte SilphCo_11F_Layout
	.4byte SilphCo_11F_MapEvents
	.4byte SilphCo_11F_MapScripts
	.4byte NULL
	.2byte MUS_SILPH
	.2byte LAYOUT_SILPH_CO_11F
	.byte MAPSEC_SILPH_CO
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=TRUE, allow_running=TRUE, show_map_name=TRUE
	.byte 11
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SilphCo_11F/header.inc =====
@ ===== BEGIN data/maps/SilphCo_Elevator/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SilphCo_Elevator/map.json
@

SilphCo_Elevator:
	.4byte SilphCo_Elevator_Layout
	.4byte SilphCo_Elevator_MapEvents
	.4byte SilphCo_Elevator_MapScripts
	.4byte NULL
	.2byte MUS_SILPH
	.2byte LAYOUT_SILPH_CO_ELEVATOR
	.byte MAPSEC_SILPH_CO
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SilphCo_Elevator/header.inc =====
@ ===== BEGIN data/maps/PokemonMansion_1F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/PokemonMansion_1F/map.json
@

PokemonMansion_1F:
	.4byte PokemonMansion_1F_Layout
	.4byte PokemonMansion_1F_MapEvents
	.4byte PokemonMansion_1F_MapScripts
	.4byte NULL
	.2byte MUS_POKE_MANSION
	.2byte LAYOUT_POKEMON_MANSION_1F
	.byte MAPSEC_POKEMON_MANSION
	.byte FALSE
	.byte WEATHER_SHADE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=TRUE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_INDOOR_2

@ ===== END data/maps/PokemonMansion_1F/header.inc =====
@ ===== BEGIN data/maps/PokemonMansion_2F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/PokemonMansion_2F/map.json
@

PokemonMansion_2F:
	.4byte PokemonMansion_2F_Layout
	.4byte PokemonMansion_2F_MapEvents
	.4byte PokemonMansion_2F_MapScripts
	.4byte NULL
	.2byte MUS_POKE_MANSION
	.2byte LAYOUT_POKEMON_MANSION_2F
	.byte MAPSEC_POKEMON_MANSION
	.byte FALSE
	.byte WEATHER_SHADE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=TRUE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_INDOOR_2

@ ===== END data/maps/PokemonMansion_2F/header.inc =====
@ ===== BEGIN data/maps/PokemonMansion_3F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/PokemonMansion_3F/map.json
@

PokemonMansion_3F:
	.4byte PokemonMansion_3F_Layout
	.4byte PokemonMansion_3F_MapEvents
	.4byte PokemonMansion_3F_MapScripts
	.4byte NULL
	.2byte MUS_POKE_MANSION
	.2byte LAYOUT_POKEMON_MANSION_3F
	.byte MAPSEC_POKEMON_MANSION
	.byte FALSE
	.byte WEATHER_SHADE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=TRUE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_INDOOR_2

@ ===== END data/maps/PokemonMansion_3F/header.inc =====
@ ===== BEGIN data/maps/PokemonMansion_B1F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/PokemonMansion_B1F/map.json
@

PokemonMansion_B1F:
	.4byte PokemonMansion_B1F_Layout
	.4byte PokemonMansion_B1F_MapEvents
	.4byte PokemonMansion_B1F_MapScripts
	.4byte NULL
	.2byte MUS_POKE_MANSION
	.2byte LAYOUT_POKEMON_MANSION_B1F
	.byte MAPSEC_POKEMON_MANSION
	.byte FALSE
	.byte WEATHER_SHADE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=TRUE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_INDOOR_2

@ ===== END data/maps/PokemonMansion_B1F/header.inc =====
@ ===== BEGIN data/maps/SafariZone_Center/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SafariZone_Center/map.json
@

SafariZone_Center:
	.4byte SafariZone_Center_Layout
	.4byte SafariZone_Center_MapEvents
	.4byte SafariZone_Center_MapScripts
	.4byte NULL
	.2byte MUS_EVOLUTION
	.2byte LAYOUT_SAFARI_ZONE_CENTER
	.byte MAPSEC_KANTO_SAFARI_ZONE
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_ROUTE
	map_header_flags allow_cycling=TRUE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SafariZone_Center/header.inc =====
@ ===== BEGIN data/maps/SafariZone_East/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SafariZone_East/map.json
@

SafariZone_East:
	.4byte SafariZone_East_Layout
	.4byte SafariZone_East_MapEvents
	.4byte SafariZone_East_MapScripts
	.4byte NULL
	.2byte MUS_EVOLUTION
	.2byte LAYOUT_SAFARI_ZONE_EAST
	.byte MAPSEC_KANTO_SAFARI_ZONE
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_ROUTE
	map_header_flags allow_cycling=TRUE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SafariZone_East/header.inc =====
@ ===== BEGIN data/maps/SafariZone_North/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SafariZone_North/map.json
@

SafariZone_North:
	.4byte SafariZone_North_Layout
	.4byte SafariZone_North_MapEvents
	.4byte SafariZone_North_MapScripts
	.4byte NULL
	.2byte MUS_EVOLUTION
	.2byte LAYOUT_SAFARI_ZONE_NORTH
	.byte MAPSEC_KANTO_SAFARI_ZONE
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_ROUTE
	map_header_flags allow_cycling=TRUE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SafariZone_North/header.inc =====
@ ===== BEGIN data/maps/SafariZone_West/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SafariZone_West/map.json
@

SafariZone_West:
	.4byte SafariZone_West_Layout
	.4byte SafariZone_West_MapEvents
	.4byte SafariZone_West_MapScripts
	.4byte NULL
	.2byte MUS_EVOLUTION
	.2byte LAYOUT_SAFARI_ZONE_WEST
	.byte MAPSEC_KANTO_SAFARI_ZONE
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_ROUTE
	map_header_flags allow_cycling=TRUE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SafariZone_West/header.inc =====
@ ===== BEGIN data/maps/SafariZone_Center_RestHouse/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SafariZone_Center_RestHouse/map.json
@

SafariZone_Center_RestHouse:
	.4byte SafariZone_RestHouse_Layout
	.4byte SafariZone_Center_RestHouse_MapEvents
	.4byte SafariZone_Center_RestHouse_MapScripts
	.4byte NULL
	.2byte MUS_EVOLUTION
	.2byte LAYOUT_SAFARI_ZONE_REST_HOUSE
	.byte MAPSEC_KANTO_SAFARI_ZONE
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SafariZone_Center_RestHouse/header.inc =====
@ ===== BEGIN data/maps/SafariZone_East_RestHouse/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SafariZone_East_RestHouse/map.json
@

SafariZone_East_RestHouse:
	.4byte SafariZone_RestHouse_Layout
	.4byte SafariZone_East_RestHouse_MapEvents
	.4byte SafariZone_East_RestHouse_MapScripts
	.4byte NULL
	.2byte MUS_EVOLUTION
	.2byte LAYOUT_SAFARI_ZONE_REST_HOUSE
	.byte MAPSEC_KANTO_SAFARI_ZONE
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SafariZone_East_RestHouse/header.inc =====
@ ===== BEGIN data/maps/SafariZone_North_RestHouse/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SafariZone_North_RestHouse/map.json
@

SafariZone_North_RestHouse:
	.4byte SafariZone_RestHouse_Layout
	.4byte SafariZone_North_RestHouse_MapEvents
	.4byte SafariZone_North_RestHouse_MapScripts
	.4byte NULL
	.2byte MUS_EVOLUTION
	.2byte LAYOUT_SAFARI_ZONE_REST_HOUSE
	.byte MAPSEC_KANTO_SAFARI_ZONE
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SafariZone_North_RestHouse/header.inc =====
@ ===== BEGIN data/maps/SafariZone_West_RestHouse/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SafariZone_West_RestHouse/map.json
@

SafariZone_West_RestHouse:
	.4byte SafariZone_RestHouse_Layout
	.4byte SafariZone_West_RestHouse_MapEvents
	.4byte SafariZone_West_RestHouse_MapScripts
	.4byte NULL
	.2byte MUS_EVOLUTION
	.2byte LAYOUT_SAFARI_ZONE_REST_HOUSE
	.byte MAPSEC_KANTO_SAFARI_ZONE
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SafariZone_West_RestHouse/header.inc =====
@ ===== BEGIN data/maps/SafariZone_SecretHouse/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SafariZone_SecretHouse/map.json
@

SafariZone_SecretHouse:
	.4byte SafariZone_SecretHouse_Layout
	.4byte SafariZone_SecretHouse_MapEvents
	.4byte SafariZone_SecretHouse_MapScripts
	.4byte NULL
	.2byte MUS_EVOLUTION
	.2byte LAYOUT_SAFARI_ZONE_SECRET_HOUSE
	.byte MAPSEC_KANTO_SAFARI_ZONE
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SafariZone_SecretHouse/header.inc =====
@ ===== BEGIN data/maps/CeruleanCave_1F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/CeruleanCave_1F/map.json
@

CeruleanCave_1F:
	.4byte CeruleanCave_1F_Layout
	.4byte CeruleanCave_1F_MapEvents
	.4byte CeruleanCave_1F_MapScripts
	.4byte NULL
	.2byte MUS_ROCKET_HIDEOUT
	.2byte LAYOUT_CERULEAN_CAVE_1F
	.byte MAPSEC_CERULEAN_CAVE
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_UNDERGROUND
	map_header_flags allow_cycling=TRUE, allow_escaping=TRUE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/CeruleanCave_1F/header.inc =====
@ ===== BEGIN data/maps/CeruleanCave_2F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/CeruleanCave_2F/map.json
@

CeruleanCave_2F:
	.4byte CeruleanCave_2F_Layout
	.4byte CeruleanCave_2F_MapEvents
	.4byte CeruleanCave_2F_MapScripts
	.4byte NULL
	.2byte MUS_ROCKET_HIDEOUT
	.2byte LAYOUT_CERULEAN_CAVE_2F
	.byte MAPSEC_CERULEAN_CAVE
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_UNDERGROUND
	map_header_flags allow_cycling=TRUE, allow_escaping=TRUE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/CeruleanCave_2F/header.inc =====
@ ===== BEGIN data/maps/CeruleanCave_B1F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/CeruleanCave_B1F/map.json
@

CeruleanCave_B1F:
	.4byte CeruleanCave_B1F_Layout
	.4byte CeruleanCave_B1F_MapEvents
	.4byte CeruleanCave_B1F_MapScripts
	.4byte NULL
	.2byte MUS_ROCKET_HIDEOUT
	.2byte LAYOUT_CERULEAN_CAVE_B1F
	.byte MAPSEC_CERULEAN_CAVE
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_UNDERGROUND
	map_header_flags allow_cycling=TRUE, allow_escaping=TRUE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/CeruleanCave_B1F/header.inc =====
@ ===== BEGIN data/maps/PokemonLeague_LoreleisRoom/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/PokemonLeague_LoreleisRoom/map.json
@

PokemonLeague_LoreleisRoom:
	.4byte PokemonLeague_LoreleisRoom_Layout
	.4byte PokemonLeague_LoreleisRoom_MapEvents
	.4byte PokemonLeague_LoreleisRoom_MapScripts
	.4byte NULL
	.2byte MUS_GYM
	.2byte LAYOUT_POKEMON_LEAGUE_LORELEIS_ROOM
	.byte MAPSEC_POKEMON_LEAGUE
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_LORELEI

@ ===== END data/maps/PokemonLeague_LoreleisRoom/header.inc =====
@ ===== BEGIN data/maps/PokemonLeague_BrunosRoom/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/PokemonLeague_BrunosRoom/map.json
@

PokemonLeague_BrunosRoom:
	.4byte PokemonLeague_BrunosRoom_Layout
	.4byte PokemonLeague_BrunosRoom_MapEvents
	.4byte PokemonLeague_BrunosRoom_MapScripts
	.4byte NULL
	.2byte MUS_ROCKET_HIDEOUT
	.2byte LAYOUT_POKEMON_LEAGUE_BRUNOS_ROOM
	.byte MAPSEC_POKEMON_LEAGUE
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_BRUNO

@ ===== END data/maps/PokemonLeague_BrunosRoom/header.inc =====
@ ===== BEGIN data/maps/PokemonLeague_AgathasRoom/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/PokemonLeague_AgathasRoom/map.json
@

PokemonLeague_AgathasRoom:
	.4byte PokemonLeague_AgathasRoom_Layout
	.4byte PokemonLeague_AgathasRoom_MapEvents
	.4byte PokemonLeague_AgathasRoom_MapScripts
	.4byte NULL
	.2byte MUS_POKE_TOWER
	.2byte LAYOUT_POKEMON_LEAGUE_AGATHAS_ROOM
	.byte MAPSEC_POKEMON_LEAGUE
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_AGATHA

@ ===== END data/maps/PokemonLeague_AgathasRoom/header.inc =====
@ ===== BEGIN data/maps/PokemonLeague_LancesRoom/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/PokemonLeague_LancesRoom/map.json
@

PokemonLeague_LancesRoom:
	.4byte PokemonLeague_LancesRoom_Layout
	.4byte PokemonLeague_LancesRoom_MapEvents
	.4byte PokemonLeague_LancesRoom_MapScripts
	.4byte NULL
	.2byte MUS_VICTORY_ROAD
	.2byte LAYOUT_POKEMON_LEAGUE_LANCES_ROOM
	.byte MAPSEC_POKEMON_LEAGUE
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_LANCE

@ ===== END data/maps/PokemonLeague_LancesRoom/header.inc =====
@ ===== BEGIN data/maps/PokemonLeague_ChampionsRoom/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/PokemonLeague_ChampionsRoom/map.json
@

PokemonLeague_ChampionsRoom:
	.4byte PokemonLeague_ChampionsRoom_Layout
	.4byte PokemonLeague_ChampionsRoom_MapEvents
	.4byte PokemonLeague_ChampionsRoom_MapScripts
	.4byte NULL
	.2byte MUS_VICTORY_ROAD
	.2byte LAYOUT_POKEMON_LEAGUE_CHAMPIONS_ROOM
	.byte MAPSEC_POKEMON_LEAGUE
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/PokemonLeague_ChampionsRoom/header.inc =====
@ ===== BEGIN data/maps/PokemonLeague_HallOfFame/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/PokemonLeague_HallOfFame/map.json
@

PokemonLeague_HallOfFame:
	.4byte PokemonLeague_HallOfFame_Layout
	.4byte PokemonLeague_HallOfFame_MapEvents
	.4byte PokemonLeague_HallOfFame_MapScripts
	.4byte NULL
	.2byte MUS_SLOW_PALLET
	.2byte LAYOUT_POKEMON_LEAGUE_HALL_OF_FAME
	.byte MAPSEC_POKEMON_LEAGUE
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/PokemonLeague_HallOfFame/header.inc =====
@ ===== BEGIN data/maps/RockTunnel_1F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/RockTunnel_1F/map.json
@

RockTunnel_1F:
	.4byte RockTunnel_1F_Layout
	.4byte RockTunnel_1F_MapEvents
	.4byte RockTunnel_1F_MapScripts
	.4byte NULL
	.2byte MUS_MT_MOON
	.2byte LAYOUT_ROCK_TUNNEL_1F
	.byte MAPSEC_ROCK_TUNNEL
	.byte TRUE
	.byte WEATHER_NONE
	.byte MAP_TYPE_UNDERGROUND
	map_header_flags allow_cycling=TRUE, allow_escaping=TRUE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/RockTunnel_1F/header.inc =====
@ ===== BEGIN data/maps/RockTunnel_B1F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/RockTunnel_B1F/map.json
@

RockTunnel_B1F:
	.4byte RockTunnel_B1F_Layout
	.4byte RockTunnel_B1F_MapEvents
	.4byte RockTunnel_B1F_MapScripts
	.4byte NULL
	.2byte MUS_MT_MOON
	.2byte LAYOUT_ROCK_TUNNEL_B1F
	.byte MAPSEC_ROCK_TUNNEL
	.byte TRUE
	.byte WEATHER_NONE
	.byte MAP_TYPE_UNDERGROUND
	map_header_flags allow_cycling=TRUE, allow_escaping=TRUE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/RockTunnel_B1F/header.inc =====
@ ===== BEGIN data/maps/SeafoamIslands_1F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SeafoamIslands_1F/map.json
@

SeafoamIslands_1F:
	.4byte SeafoamIslands_1F_Layout
	.4byte SeafoamIslands_1F_MapEvents
	.4byte SeafoamIslands_1F_MapScripts
	.4byte NULL
	.2byte MUS_VIRIDIAN_FOREST
	.2byte LAYOUT_SEAFOAM_ISLANDS_1F
	.byte MAPSEC_SEAFOAM_ISLANDS
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_UNDERGROUND
	map_header_flags allow_cycling=TRUE, allow_escaping=TRUE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SeafoamIslands_1F/header.inc =====
@ ===== BEGIN data/maps/SeafoamIslands_B1F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SeafoamIslands_B1F/map.json
@

SeafoamIslands_B1F:
	.4byte SeafoamIslands_B1F_Layout
	.4byte SeafoamIslands_B1F_MapEvents
	.4byte SeafoamIslands_B1F_MapScripts
	.4byte NULL
	.2byte MUS_VIRIDIAN_FOREST
	.2byte LAYOUT_SEAFOAM_ISLANDS_B1F
	.byte MAPSEC_SEAFOAM_ISLANDS
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_UNDERGROUND
	map_header_flags allow_cycling=TRUE, allow_escaping=TRUE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SeafoamIslands_B1F/header.inc =====
@ ===== BEGIN data/maps/SeafoamIslands_B2F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SeafoamIslands_B2F/map.json
@

SeafoamIslands_B2F:
	.4byte SeafoamIslands_B2F_Layout
	.4byte SeafoamIslands_B2F_MapEvents
	.4byte SeafoamIslands_B2F_MapScripts
	.4byte NULL
	.2byte MUS_VIRIDIAN_FOREST
	.2byte LAYOUT_SEAFOAM_ISLANDS_B2F
	.byte MAPSEC_SEAFOAM_ISLANDS
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_UNDERGROUND
	map_header_flags allow_cycling=TRUE, allow_escaping=TRUE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SeafoamIslands_B2F/header.inc =====
@ ===== BEGIN data/maps/SeafoamIslands_B3F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SeafoamIslands_B3F/map.json
@

SeafoamIslands_B3F:
	.4byte SeafoamIslands_B3F_Layout
	.4byte SeafoamIslands_B3F_MapEvents
	.4byte SeafoamIslands_B3F_MapScripts
	.4byte NULL
	.2byte MUS_VIRIDIAN_FOREST
	.2byte LAYOUT_SEAFOAM_ISLANDS_B3F
	.byte MAPSEC_SEAFOAM_ISLANDS
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_UNDERGROUND
	map_header_flags allow_cycling=TRUE, allow_escaping=TRUE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SeafoamIslands_B3F/header.inc =====
@ ===== BEGIN data/maps/SeafoamIslands_B4F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SeafoamIslands_B4F/map.json
@

SeafoamIslands_B4F:
	.4byte SeafoamIslands_B4F_Layout
	.4byte SeafoamIslands_B4F_MapEvents
	.4byte SeafoamIslands_B4F_MapScripts
	.4byte NULL
	.2byte MUS_VIRIDIAN_FOREST
	.2byte LAYOUT_SEAFOAM_ISLANDS_B4F
	.byte MAPSEC_SEAFOAM_ISLANDS
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_UNDERGROUND
	map_header_flags allow_cycling=TRUE, allow_escaping=TRUE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SeafoamIslands_B4F/header.inc =====
@ ===== BEGIN data/maps/PokemonTower_1F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/PokemonTower_1F/map.json
@

PokemonTower_1F:
	.4byte PokemonTower_1F_Layout
	.4byte PokemonTower_1F_MapEvents
	.4byte PokemonTower_1F_MapScripts
	.4byte NULL
	.2byte MUS_POKE_TOWER
	.2byte LAYOUT_POKEMON_TOWER_1F
	.byte MAPSEC_POKEMON_TOWER
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=TRUE, allow_running=FALSE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_INDOOR_1

@ ===== END data/maps/PokemonTower_1F/header.inc =====
@ ===== BEGIN data/maps/PokemonTower_2F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/PokemonTower_2F/map.json
@

PokemonTower_2F:
	.4byte PokemonTower_2F_Layout
	.4byte PokemonTower_2F_MapEvents
	.4byte PokemonTower_2F_MapScripts
	.4byte NULL
	.2byte MUS_POKE_TOWER
	.2byte LAYOUT_POKEMON_TOWER_2F
	.byte MAPSEC_POKEMON_TOWER
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=TRUE, allow_running=FALSE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_INDOOR_1

@ ===== END data/maps/PokemonTower_2F/header.inc =====
@ ===== BEGIN data/maps/PokemonTower_3F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/PokemonTower_3F/map.json
@

PokemonTower_3F:
	.4byte PokemonTower_3F_Layout
	.4byte PokemonTower_3F_MapEvents
	.4byte PokemonTower_3F_MapScripts
	.4byte NULL
	.2byte MUS_POKE_TOWER
	.2byte LAYOUT_POKEMON_TOWER_3F
	.byte MAPSEC_POKEMON_TOWER
	.byte FALSE
	.byte WEATHER_FOG_HORIZONTAL
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=TRUE, allow_running=FALSE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_INDOOR_1

@ ===== END data/maps/PokemonTower_3F/header.inc =====
@ ===== BEGIN data/maps/PokemonTower_4F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/PokemonTower_4F/map.json
@

PokemonTower_4F:
	.4byte PokemonTower_4F_Layout
	.4byte PokemonTower_4F_MapEvents
	.4byte PokemonTower_4F_MapScripts
	.4byte NULL
	.2byte MUS_POKE_TOWER
	.2byte LAYOUT_POKEMON_TOWER_4F
	.byte MAPSEC_POKEMON_TOWER
	.byte FALSE
	.byte WEATHER_FOG_HORIZONTAL
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=TRUE, allow_running=FALSE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_INDOOR_1

@ ===== END data/maps/PokemonTower_4F/header.inc =====
@ ===== BEGIN data/maps/PokemonTower_5F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/PokemonTower_5F/map.json
@

PokemonTower_5F:
	.4byte PokemonTower_5F_Layout
	.4byte PokemonTower_5F_MapEvents
	.4byte PokemonTower_5F_MapScripts
	.4byte NULL
	.2byte MUS_POKE_TOWER
	.2byte LAYOUT_POKEMON_TOWER_5F
	.byte MAPSEC_POKEMON_TOWER
	.byte FALSE
	.byte WEATHER_FOG_HORIZONTAL
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=TRUE, allow_running=FALSE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_INDOOR_1

@ ===== END data/maps/PokemonTower_5F/header.inc =====
@ ===== BEGIN data/maps/PokemonTower_6F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/PokemonTower_6F/map.json
@

PokemonTower_6F:
	.4byte PokemonTower_6F_Layout
	.4byte PokemonTower_6F_MapEvents
	.4byte PokemonTower_6F_MapScripts
	.4byte NULL
	.2byte MUS_POKE_TOWER
	.2byte LAYOUT_POKEMON_TOWER_6F
	.byte MAPSEC_POKEMON_TOWER
	.byte FALSE
	.byte WEATHER_FOG_HORIZONTAL
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=TRUE, allow_running=FALSE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_INDOOR_1

@ ===== END data/maps/PokemonTower_6F/header.inc =====
@ ===== BEGIN data/maps/PokemonTower_7F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/PokemonTower_7F/map.json
@

PokemonTower_7F:
	.4byte PokemonTower_7F_Layout
	.4byte PokemonTower_7F_MapEvents
	.4byte PokemonTower_7F_MapScripts
	.4byte NULL
	.2byte MUS_POKE_TOWER
	.2byte LAYOUT_POKEMON_TOWER_7F
	.byte MAPSEC_POKEMON_TOWER
	.byte FALSE
	.byte WEATHER_FOG_HORIZONTAL
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=TRUE, allow_running=FALSE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_INDOOR_1

@ ===== END data/maps/PokemonTower_7F/header.inc =====
@ ===== BEGIN data/maps/PowerPlant/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/PowerPlant/map.json
@

PowerPlant:
	.4byte PowerPlant_Layout
	.4byte PowerPlant_MapEvents
	.4byte PowerPlant_MapScripts
	.4byte NULL
	.2byte MUS_POKE_MANSION
	.2byte LAYOUT_POWER_PLANT
	.byte MAPSEC_POWER_PLANT
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=TRUE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_INDOOR_2

@ ===== END data/maps/PowerPlant/header.inc =====
@ ===== BEGIN data/maps/MtEmber_RubyPath_B4F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/MtEmber_RubyPath_B4F/map.json
@

MtEmber_RubyPath_B4F:
	.4byte MtEmber_RubyPath_B4F_Layout
	.4byte MtEmber_RubyPath_B4F_MapEvents
	.4byte MtEmber_RubyPath_B4F_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_CAVE
	.2byte LAYOUT_MT_EMBER_RUBY_PATH_B4F
	.byte MAPSEC_MT_EMBER
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_UNDERGROUND
	map_header_flags allow_cycling=TRUE, allow_escaping=TRUE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/MtEmber_RubyPath_B4F/header.inc =====
@ ===== BEGIN data/maps/MtEmber_Exterior/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/MtEmber_Exterior/map.json
@

MtEmber_Exterior:
	.4byte MtEmber_Exterior_Layout
	.4byte MtEmber_Exterior_MapEvents
	.4byte MtEmber_Exterior_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_CAVE
	.2byte LAYOUT_MT_EMBER_EXTERIOR
	.byte MAPSEC_MT_EMBER
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_ROUTE
	map_header_flags allow_cycling=TRUE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/MtEmber_Exterior/header.inc =====
@ ===== BEGIN data/maps/MtEmber_SummitPath_1F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/MtEmber_SummitPath_1F/map.json
@

MtEmber_SummitPath_1F:
	.4byte MtEmber_SummitPath_1F_Layout
	.4byte MtEmber_SummitPath_1F_MapEvents
	.4byte MtEmber_SummitPath_1F_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_CAVE
	.2byte LAYOUT_MT_EMBER_SUMMIT_PATH_1F
	.byte MAPSEC_MT_EMBER
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_UNDERGROUND
	map_header_flags allow_cycling=TRUE, allow_escaping=TRUE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/MtEmber_SummitPath_1F/header.inc =====
@ ===== BEGIN data/maps/MtEmber_SummitPath_2F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/MtEmber_SummitPath_2F/map.json
@

MtEmber_SummitPath_2F:
	.4byte MtEmber_SummitPath_2F_Layout
	.4byte MtEmber_SummitPath_2F_MapEvents
	.4byte MtEmber_SummitPath_2F_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_CAVE
	.2byte LAYOUT_MT_EMBER_SUMMIT_PATH_2F
	.byte MAPSEC_MT_EMBER
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_UNDERGROUND
	map_header_flags allow_cycling=TRUE, allow_escaping=TRUE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/MtEmber_SummitPath_2F/header.inc =====
@ ===== BEGIN data/maps/MtEmber_SummitPath_3F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/MtEmber_SummitPath_3F/map.json
@

MtEmber_SummitPath_3F:
	.4byte MtEmber_SummitPath_3F_Layout
	.4byte MtEmber_SummitPath_3F_MapEvents
	.4byte MtEmber_SummitPath_3F_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_CAVE
	.2byte LAYOUT_MT_EMBER_SUMMIT_PATH_3F
	.byte MAPSEC_MT_EMBER
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_UNDERGROUND
	map_header_flags allow_cycling=TRUE, allow_escaping=TRUE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/MtEmber_SummitPath_3F/header.inc =====
@ ===== BEGIN data/maps/MtEmber_Summit/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/MtEmber_Summit/map.json
@

MtEmber_Summit:
	.4byte MtEmber_Summit_Layout
	.4byte MtEmber_Summit_MapEvents
	.4byte MtEmber_Summit_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_CAVE
	.2byte LAYOUT_MT_EMBER_SUMMIT
	.byte MAPSEC_MT_EMBER
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_UNDERGROUND
	map_header_flags allow_cycling=TRUE, allow_escaping=TRUE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/MtEmber_Summit/header.inc =====
@ ===== BEGIN data/maps/MtEmber_RubyPath_B5F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/MtEmber_RubyPath_B5F/map.json
@

MtEmber_RubyPath_B5F:
	.4byte MtEmber_RubyPath_B5F_Layout
	.4byte MtEmber_RubyPath_B5F_MapEvents
	.4byte MtEmber_RubyPath_B5F_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_CAVE
	.2byte LAYOUT_MT_EMBER_RUBY_PATH_B5F
	.byte MAPSEC_MT_EMBER
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_UNDERGROUND
	map_header_flags allow_cycling=TRUE, allow_escaping=TRUE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/MtEmber_RubyPath_B5F/header.inc =====
@ ===== BEGIN data/maps/MtEmber_RubyPath_1F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/MtEmber_RubyPath_1F/map.json
@

MtEmber_RubyPath_1F:
	.4byte MtEmber_RubyPath_1F_Layout
	.4byte MtEmber_RubyPath_1F_MapEvents
	.4byte MtEmber_RubyPath_1F_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_CAVE
	.2byte LAYOUT_MT_EMBER_RUBY_PATH_1F
	.byte MAPSEC_MT_EMBER
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_UNDERGROUND
	map_header_flags allow_cycling=TRUE, allow_escaping=TRUE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/MtEmber_RubyPath_1F/header.inc =====
@ ===== BEGIN data/maps/MtEmber_RubyPath_B1F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/MtEmber_RubyPath_B1F/map.json
@

MtEmber_RubyPath_B1F:
	.4byte MtEmber_RubyPath_B1F_Layout
	.4byte MtEmber_RubyPath_B1F_MapEvents
	.4byte MtEmber_RubyPath_B1F_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_CAVE
	.2byte LAYOUT_MT_EMBER_RUBY_PATH_B1F
	.byte MAPSEC_MT_EMBER
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_UNDERGROUND
	map_header_flags allow_cycling=TRUE, allow_escaping=TRUE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/MtEmber_RubyPath_B1F/header.inc =====
@ ===== BEGIN data/maps/MtEmber_RubyPath_B2F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/MtEmber_RubyPath_B2F/map.json
@

MtEmber_RubyPath_B2F:
	.4byte MtEmber_RubyPath_B2F_Layout
	.4byte MtEmber_RubyPath_B2F_MapEvents
	.4byte MtEmber_RubyPath_B2F_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_CAVE
	.2byte LAYOUT_MT_EMBER_RUBY_PATH_B2F
	.byte MAPSEC_MT_EMBER
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_UNDERGROUND
	map_header_flags allow_cycling=TRUE, allow_escaping=TRUE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/MtEmber_RubyPath_B2F/header.inc =====
@ ===== BEGIN data/maps/MtEmber_RubyPath_B3F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/MtEmber_RubyPath_B3F/map.json
@

MtEmber_RubyPath_B3F:
	.4byte MtEmber_RubyPath_B3F_Layout
	.4byte MtEmber_RubyPath_B3F_MapEvents
	.4byte MtEmber_RubyPath_B3F_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_CAVE
	.2byte LAYOUT_MT_EMBER_RUBY_PATH_B3F
	.byte MAPSEC_MT_EMBER
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_UNDERGROUND
	map_header_flags allow_cycling=TRUE, allow_escaping=TRUE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/MtEmber_RubyPath_B3F/header.inc =====
@ ===== BEGIN data/maps/MtEmber_RubyPath_B1F_Stairs/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/MtEmber_RubyPath_B1F_Stairs/map.json
@

MtEmber_RubyPath_B1F_Stairs:
	.4byte MtEmber_RubyPath_B1F_Stairs_Layout
	.4byte MtEmber_RubyPath_B1F_Stairs_MapEvents
	.4byte MtEmber_RubyPath_B1F_Stairs_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_CAVE
	.2byte LAYOUT_MT_EMBER_RUBY_PATH_B1F_STAIRS
	.byte MAPSEC_MT_EMBER
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_UNDERGROUND
	map_header_flags allow_cycling=TRUE, allow_escaping=TRUE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/MtEmber_RubyPath_B1F_Stairs/header.inc =====
@ ===== BEGIN data/maps/MtEmber_RubyPath_B2F_Stairs/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/MtEmber_RubyPath_B2F_Stairs/map.json
@

MtEmber_RubyPath_B2F_Stairs:
	.4byte MtEmber_RubyPath_B2F_Stairs_Layout
	.4byte MtEmber_RubyPath_B2F_Stairs_MapEvents
	.4byte MtEmber_RubyPath_B2F_Stairs_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_CAVE
	.2byte LAYOUT_MT_EMBER_RUBY_PATH_B2F_STAIRS
	.byte MAPSEC_MT_EMBER
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_UNDERGROUND
	map_header_flags allow_cycling=TRUE, allow_escaping=TRUE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/MtEmber_RubyPath_B2F_Stairs/header.inc =====
@ ===== BEGIN data/maps/ThreeIsland_BerryForest/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/ThreeIsland_BerryForest/map.json
@

ThreeIsland_BerryForest:
	.4byte ThreeIsland_BerryForest_Layout
	.4byte ThreeIsland_BerryForest_MapEvents
	.4byte ThreeIsland_BerryForest_MapScripts
	.4byte NULL
	.2byte MUS_VIRIDIAN_FOREST
	.2byte LAYOUT_THREE_ISLAND_BERRY_FOREST
	.byte MAPSEC_BERRY_FOREST
	.byte FALSE
	.byte WEATHER_SHADE
	.byte MAP_TYPE_ROUTE
	map_header_flags allow_cycling=TRUE, allow_escaping=TRUE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/ThreeIsland_BerryForest/header.inc =====
@ ===== BEGIN data/maps/FourIsland_IcefallCave_Entrance/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FourIsland_IcefallCave_Entrance/map.json
@

FourIsland_IcefallCave_Entrance:
	.4byte FourIsland_IcefallCave_Entrance_Layout
	.4byte FourIsland_IcefallCave_Entrance_MapEvents
	.4byte FourIsland_IcefallCave_Entrance_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_CAVE
	.2byte LAYOUT_FOUR_ISLAND_ICEFALL_CAVE_ENTRANCE
	.byte MAPSEC_ICEFALL_CAVE
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_UNDERGROUND
	map_header_flags allow_cycling=TRUE, allow_escaping=TRUE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/FourIsland_IcefallCave_Entrance/header.inc =====
@ ===== BEGIN data/maps/FourIsland_IcefallCave_1F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FourIsland_IcefallCave_1F/map.json
@

FourIsland_IcefallCave_1F:
	.4byte FourIsland_IcefallCave_1F_Layout
	.4byte FourIsland_IcefallCave_1F_MapEvents
	.4byte FourIsland_IcefallCave_1F_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_CAVE
	.2byte LAYOUT_FOUR_ISLAND_ICEFALL_CAVE_1F
	.byte MAPSEC_ICEFALL_CAVE
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_UNDERGROUND
	map_header_flags allow_cycling=TRUE, allow_escaping=TRUE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/FourIsland_IcefallCave_1F/header.inc =====
@ ===== BEGIN data/maps/FourIsland_IcefallCave_B1F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FourIsland_IcefallCave_B1F/map.json
@

FourIsland_IcefallCave_B1F:
	.4byte FourIsland_IcefallCave_B1F_Layout
	.4byte FourIsland_IcefallCave_B1F_MapEvents
	.4byte FourIsland_IcefallCave_B1F_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_CAVE
	.2byte LAYOUT_FOUR_ISLAND_ICEFALL_CAVE_B1F
	.byte MAPSEC_ICEFALL_CAVE
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_UNDERGROUND
	map_header_flags allow_cycling=TRUE, allow_escaping=TRUE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/FourIsland_IcefallCave_B1F/header.inc =====
@ ===== BEGIN data/maps/FourIsland_IcefallCave_Back/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FourIsland_IcefallCave_Back/map.json
@

FourIsland_IcefallCave_Back:
	.4byte FourIsland_IcefallCave_Back_Layout
	.4byte FourIsland_IcefallCave_Back_MapEvents
	.4byte FourIsland_IcefallCave_Back_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_CAVE
	.2byte LAYOUT_FOUR_ISLAND_ICEFALL_CAVE_BACK
	.byte MAPSEC_ICEFALL_CAVE
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_UNDERGROUND
	map_header_flags allow_cycling=TRUE, allow_escaping=TRUE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/FourIsland_IcefallCave_Back/header.inc =====
@ ===== BEGIN data/maps/FiveIsland_RocketWarehouse/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FiveIsland_RocketWarehouse/map.json
@

FiveIsland_RocketWarehouse:
	.4byte FiveIsland_RocketWarehouse_Layout
	.4byte FiveIsland_RocketWarehouse_MapEvents
	.4byte FiveIsland_RocketWarehouse_MapScripts
	.4byte NULL
	.2byte MUS_ROCKET_HIDEOUT
	.2byte LAYOUT_FIVE_ISLAND_ROCKET_WAREHOUSE
	.byte MAPSEC_ROCKET_WAREHOUSE
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=TRUE, allow_running=FALSE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_INDOOR_2

@ ===== END data/maps/FiveIsland_RocketWarehouse/header.inc =====
@ ===== BEGIN data/maps/SixIsland_DottedHole_1F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SixIsland_DottedHole_1F/map.json
@

SixIsland_DottedHole_1F:
	.4byte SixIsland_DottedHole_1F_Layout
	.4byte SixIsland_DottedHole_1F_MapEvents
	.4byte SixIsland_DottedHole_1F_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_DUNGEON
	.2byte LAYOUT_SIX_ISLAND_DOTTED_HOLE_1F
	.byte MAPSEC_DOTTED_HOLE
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_UNDERGROUND
	map_header_flags allow_cycling=TRUE, allow_escaping=TRUE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SixIsland_DottedHole_1F/header.inc =====
@ ===== BEGIN data/maps/SixIsland_DottedHole_B1F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SixIsland_DottedHole_B1F/map.json
@

SixIsland_DottedHole_B1F:
	.4byte SixIsland_DottedHole_B1F_Layout
	.4byte SixIsland_DottedHole_B1F_MapEvents
	.4byte SixIsland_DottedHole_B1F_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_DUNGEON
	.2byte LAYOUT_SIX_ISLAND_DOTTED_HOLE_B1F
	.byte MAPSEC_DOTTED_HOLE
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_UNDERGROUND
	map_header_flags allow_cycling=TRUE, allow_escaping=TRUE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SixIsland_DottedHole_B1F/header.inc =====
@ ===== BEGIN data/maps/SixIsland_DottedHole_B2F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SixIsland_DottedHole_B2F/map.json
@

SixIsland_DottedHole_B2F:
	.4byte SixIsland_DottedHole_B2F_Layout
	.4byte SixIsland_DottedHole_B2F_MapEvents
	.4byte SixIsland_DottedHole_B2F_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_DUNGEON
	.2byte LAYOUT_SIX_ISLAND_DOTTED_HOLE_B2F
	.byte MAPSEC_DOTTED_HOLE
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_UNDERGROUND
	map_header_flags allow_cycling=TRUE, allow_escaping=TRUE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SixIsland_DottedHole_B2F/header.inc =====
@ ===== BEGIN data/maps/SixIsland_DottedHole_B3F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SixIsland_DottedHole_B3F/map.json
@

SixIsland_DottedHole_B3F:
	.4byte SixIsland_DottedHole_B3F_Layout
	.4byte SixIsland_DottedHole_B3F_MapEvents
	.4byte SixIsland_DottedHole_B3F_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_DUNGEON
	.2byte LAYOUT_SIX_ISLAND_DOTTED_HOLE_B3F
	.byte MAPSEC_DOTTED_HOLE
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_UNDERGROUND
	map_header_flags allow_cycling=TRUE, allow_escaping=TRUE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SixIsland_DottedHole_B3F/header.inc =====
@ ===== BEGIN data/maps/SixIsland_DottedHole_B4F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SixIsland_DottedHole_B4F/map.json
@

SixIsland_DottedHole_B4F:
	.4byte SixIsland_DottedHole_B4F_Layout
	.4byte SixIsland_DottedHole_B4F_MapEvents
	.4byte SixIsland_DottedHole_B4F_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_DUNGEON
	.2byte LAYOUT_SIX_ISLAND_DOTTED_HOLE_B4F
	.byte MAPSEC_DOTTED_HOLE
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_UNDERGROUND
	map_header_flags allow_cycling=TRUE, allow_escaping=TRUE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SixIsland_DottedHole_B4F/header.inc =====
@ ===== BEGIN data/maps/SixIsland_DottedHole_SapphireRoom/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SixIsland_DottedHole_SapphireRoom/map.json
@

SixIsland_DottedHole_SapphireRoom:
	.4byte SixIsland_DottedHole_SapphireRoom_Layout
	.4byte SixIsland_DottedHole_SapphireRoom_MapEvents
	.4byte SixIsland_DottedHole_SapphireRoom_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_DUNGEON
	.2byte LAYOUT_SIX_ISLAND_DOTTED_HOLE_SAPPHIRE_ROOM
	.byte MAPSEC_DOTTED_HOLE
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_UNDERGROUND
	map_header_flags allow_cycling=TRUE, allow_escaping=TRUE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SixIsland_DottedHole_SapphireRoom/header.inc =====
@ ===== BEGIN data/maps/SixIsland_PatternBush/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SixIsland_PatternBush/map.json
@

SixIsland_PatternBush:
	.4byte SixIsland_PatternBush_Layout
	.4byte SixIsland_PatternBush_MapEvents
	.4byte SixIsland_PatternBush_MapScripts
	.4byte NULL
	.2byte MUS_VIRIDIAN_FOREST
	.2byte LAYOUT_SIX_ISLAND_PATTERN_BUSH
	.byte MAPSEC_PATTERN_BUSH
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_ROUTE
	map_header_flags allow_cycling=TRUE, allow_escaping=TRUE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SixIsland_PatternBush/header.inc =====
@ ===== BEGIN data/maps/SixIsland_AlteringCave/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SixIsland_AlteringCave/map.json
@

SixIsland_AlteringCave:
	.4byte SixIsland_AlteringCave_Layout
	.4byte SixIsland_AlteringCave_MapEvents
	.4byte SixIsland_AlteringCave_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_CAVE
	.2byte LAYOUT_SIX_ISLAND_ALTERING_CAVE
	.byte MAPSEC_ALTERING_CAVE
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_UNDERGROUND
	map_header_flags allow_cycling=TRUE, allow_escaping=TRUE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SixIsland_AlteringCave/header.inc =====
@ ===== BEGIN data/maps/NavelRock_Exterior/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/NavelRock_Exterior/map.json
@

NavelRock_Exterior:
	.4byte NavelRock_Exterior_Layout
	.4byte NavelRock_Exterior_MapEvents
	.4byte NavelRock_Exterior_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_ROUTE
	.2byte LAYOUT_NAVEL_ROCK_EXTERIOR
	.byte MAPSEC_NAVEL_ROCK
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_ROUTE
	map_header_flags allow_cycling=TRUE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/NavelRock_Exterior/header.inc =====
@ ===== BEGIN data/maps/TrainerTower_1F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/TrainerTower_1F/map.json
@

TrainerTower_1F:
	.4byte TrainerTower_1F_Layout
	.4byte TrainerTower_1F_MapEvents
	.4byte TrainerTower_1F_MapScripts
	.4byte NULL
	.2byte MUS_TRAINER_TOWER
	.2byte LAYOUT_TRAINER_TOWER_1F
	.byte MAPSEC_TRAINER_TOWER_2
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/TrainerTower_1F/header.inc =====
@ ===== BEGIN data/maps/TrainerTower_2F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/TrainerTower_2F/map.json
@

TrainerTower_2F:
	.4byte TrainerTower_2F_Layout
	.4byte TrainerTower_2F_MapEvents
	.4byte TrainerTower_2F_MapScripts
	.4byte NULL
	.2byte MUS_TRAINER_TOWER
	.2byte LAYOUT_TRAINER_TOWER_2F
	.byte MAPSEC_TRAINER_TOWER_2
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/TrainerTower_2F/header.inc =====
@ ===== BEGIN data/maps/TrainerTower_3F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/TrainerTower_3F/map.json
@

TrainerTower_3F:
	.4byte TrainerTower_3F_Layout
	.4byte TrainerTower_3F_MapEvents
	.4byte TrainerTower_3F_MapScripts
	.4byte NULL
	.2byte MUS_TRAINER_TOWER
	.2byte LAYOUT_TRAINER_TOWER_3F
	.byte MAPSEC_TRAINER_TOWER_2
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/TrainerTower_3F/header.inc =====
@ ===== BEGIN data/maps/TrainerTower_4F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/TrainerTower_4F/map.json
@

TrainerTower_4F:
	.4byte TrainerTower_4F_Layout
	.4byte TrainerTower_4F_MapEvents
	.4byte TrainerTower_4F_MapScripts
	.4byte NULL
	.2byte MUS_TRAINER_TOWER
	.2byte LAYOUT_TRAINER_TOWER_4F
	.byte MAPSEC_TRAINER_TOWER_2
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/TrainerTower_4F/header.inc =====
@ ===== BEGIN data/maps/TrainerTower_5F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/TrainerTower_5F/map.json
@

TrainerTower_5F:
	.4byte TrainerTower_5F_Layout
	.4byte TrainerTower_5F_MapEvents
	.4byte TrainerTower_5F_MapScripts
	.4byte NULL
	.2byte MUS_TRAINER_TOWER
	.2byte LAYOUT_TRAINER_TOWER_5F
	.byte MAPSEC_TRAINER_TOWER_2
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/TrainerTower_5F/header.inc =====
@ ===== BEGIN data/maps/TrainerTower_6F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/TrainerTower_6F/map.json
@

TrainerTower_6F:
	.4byte TrainerTower_6F_Layout
	.4byte TrainerTower_6F_MapEvents
	.4byte TrainerTower_6F_MapScripts
	.4byte NULL
	.2byte MUS_TRAINER_TOWER
	.2byte LAYOUT_TRAINER_TOWER_6F
	.byte MAPSEC_TRAINER_TOWER_2
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/TrainerTower_6F/header.inc =====
@ ===== BEGIN data/maps/TrainerTower_7F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/TrainerTower_7F/map.json
@

TrainerTower_7F:
	.4byte TrainerTower_7F_Layout
	.4byte TrainerTower_7F_MapEvents
	.4byte TrainerTower_7F_MapScripts
	.4byte NULL
	.2byte MUS_TRAINER_TOWER
	.2byte LAYOUT_TRAINER_TOWER_7F
	.byte MAPSEC_TRAINER_TOWER_2
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/TrainerTower_7F/header.inc =====
@ ===== BEGIN data/maps/TrainerTower_8F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/TrainerTower_8F/map.json
@

TrainerTower_8F:
	.4byte TrainerTower_8F_Layout
	.4byte TrainerTower_8F_MapEvents
	.4byte TrainerTower_8F_MapScripts
	.4byte NULL
	.2byte MUS_TRAINER_TOWER
	.2byte LAYOUT_TRAINER_TOWER_8F
	.byte MAPSEC_TRAINER_TOWER_2
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/TrainerTower_8F/header.inc =====
@ ===== BEGIN data/maps/TrainerTower_Roof/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/TrainerTower_Roof/map.json
@

TrainerTower_Roof:
	.4byte TrainerTower_Roof_Layout
	.4byte TrainerTower_Roof_MapEvents
	.4byte TrainerTower_Roof_MapScripts
	.4byte NULL
	.2byte MUS_TRAINER_TOWER
	.2byte LAYOUT_TRAINER_TOWER_ROOF
	.byte MAPSEC_TRAINER_TOWER_2
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/TrainerTower_Roof/header.inc =====
@ ===== BEGIN data/maps/TrainerTower_Lobby/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/TrainerTower_Lobby/map.json
@

TrainerTower_Lobby:
	.4byte TrainerTower_Lobby_Layout
	.4byte TrainerTower_Lobby_MapEvents
	.4byte TrainerTower_Lobby_MapScripts
	.4byte NULL
	.2byte MUS_TRAINER_TOWER
	.2byte LAYOUT_TRAINER_TOWER_LOBBY
	.byte MAPSEC_TRAINER_TOWER_2
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/TrainerTower_Lobby/header.inc =====
@ ===== BEGIN data/maps/TrainerTower_Elevator/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/TrainerTower_Elevator/map.json
@

TrainerTower_Elevator:
	.4byte TrainerTower_Elevator_Layout
	.4byte TrainerTower_Elevator_MapEvents
	.4byte TrainerTower_Elevator_MapScripts
	.4byte NULL
	.2byte MUS_TRAINER_TOWER
	.2byte LAYOUT_TRAINER_TOWER_ELEVATOR
	.byte MAPSEC_TRAINER_TOWER_2
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/TrainerTower_Elevator/header.inc =====
@ ===== BEGIN data/maps/FiveIsland_LostCave_Entrance/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FiveIsland_LostCave_Entrance/map.json
@

FiveIsland_LostCave_Entrance:
	.4byte FiveIsland_LostCave_Entrance_Layout
	.4byte FiveIsland_LostCave_Entrance_MapEvents
	.4byte FiveIsland_LostCave_Entrance_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_CAVE
	.2byte LAYOUT_FIVE_ISLAND_LOST_CAVE_ENTRANCE
	.byte MAPSEC_LOST_CAVE
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_UNDERGROUND
	map_header_flags allow_cycling=TRUE, allow_escaping=TRUE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/FiveIsland_LostCave_Entrance/header.inc =====
@ ===== BEGIN data/maps/FiveIsland_LostCave_Room1/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FiveIsland_LostCave_Room1/map.json
@

FiveIsland_LostCave_Room1:
	.4byte FiveIsland_LostCave_Room1_Layout
	.4byte FiveIsland_LostCave_Room1_MapEvents
	.4byte FiveIsland_LostCave_Room1_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_CAVE
	.2byte LAYOUT_FIVE_ISLAND_LOST_CAVE_ROOM1
	.byte MAPSEC_LOST_CAVE
	.byte FALSE
	.byte WEATHER_FOG_HORIZONTAL
	.byte MAP_TYPE_UNDERGROUND
	map_header_flags allow_cycling=TRUE, allow_escaping=TRUE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/FiveIsland_LostCave_Room1/header.inc =====
@ ===== BEGIN data/maps/FiveIsland_LostCave_Room2/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FiveIsland_LostCave_Room2/map.json
@

FiveIsland_LostCave_Room2:
	.4byte FiveIsland_LostCave_Room2_Layout
	.4byte FiveIsland_LostCave_Room2_MapEvents
	.4byte FiveIsland_LostCave_Room2_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_CAVE
	.2byte LAYOUT_FIVE_ISLAND_LOST_CAVE_ROOM2
	.byte MAPSEC_LOST_CAVE
	.byte FALSE
	.byte WEATHER_FOG_HORIZONTAL
	.byte MAP_TYPE_UNDERGROUND
	map_header_flags allow_cycling=TRUE, allow_escaping=TRUE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/FiveIsland_LostCave_Room2/header.inc =====
@ ===== BEGIN data/maps/FiveIsland_LostCave_Room3/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FiveIsland_LostCave_Room3/map.json
@

FiveIsland_LostCave_Room3:
	.4byte FiveIsland_LostCave_Room3_Layout
	.4byte FiveIsland_LostCave_Room3_MapEvents
	.4byte FiveIsland_LostCave_Room3_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_CAVE
	.2byte LAYOUT_FIVE_ISLAND_LOST_CAVE_ROOM3
	.byte MAPSEC_LOST_CAVE
	.byte FALSE
	.byte WEATHER_FOG_HORIZONTAL
	.byte MAP_TYPE_UNDERGROUND
	map_header_flags allow_cycling=TRUE, allow_escaping=TRUE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/FiveIsland_LostCave_Room3/header.inc =====
@ ===== BEGIN data/maps/FiveIsland_LostCave_Room4/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FiveIsland_LostCave_Room4/map.json
@

FiveIsland_LostCave_Room4:
	.4byte FiveIsland_LostCave_Room4_Layout
	.4byte FiveIsland_LostCave_Room4_MapEvents
	.4byte FiveIsland_LostCave_Room4_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_CAVE
	.2byte LAYOUT_FIVE_ISLAND_LOST_CAVE_ROOM4
	.byte MAPSEC_LOST_CAVE
	.byte FALSE
	.byte WEATHER_FOG_HORIZONTAL
	.byte MAP_TYPE_UNDERGROUND
	map_header_flags allow_cycling=TRUE, allow_escaping=TRUE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/FiveIsland_LostCave_Room4/header.inc =====
@ ===== BEGIN data/maps/FiveIsland_LostCave_Room5/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FiveIsland_LostCave_Room5/map.json
@

FiveIsland_LostCave_Room5:
	.4byte FiveIsland_LostCave_Room5_Layout
	.4byte FiveIsland_LostCave_Room5_MapEvents
	.4byte FiveIsland_LostCave_Room5_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_CAVE
	.2byte LAYOUT_FIVE_ISLAND_LOST_CAVE_ROOM5
	.byte MAPSEC_LOST_CAVE
	.byte FALSE
	.byte WEATHER_FOG_HORIZONTAL
	.byte MAP_TYPE_UNDERGROUND
	map_header_flags allow_cycling=TRUE, allow_escaping=TRUE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/FiveIsland_LostCave_Room5/header.inc =====
@ ===== BEGIN data/maps/FiveIsland_LostCave_Room6/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FiveIsland_LostCave_Room6/map.json
@

FiveIsland_LostCave_Room6:
	.4byte FiveIsland_LostCave_Room6_Layout
	.4byte FiveIsland_LostCave_Room6_MapEvents
	.4byte FiveIsland_LostCave_Room6_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_CAVE
	.2byte LAYOUT_FIVE_ISLAND_LOST_CAVE_ROOM6
	.byte MAPSEC_LOST_CAVE
	.byte FALSE
	.byte WEATHER_FOG_HORIZONTAL
	.byte MAP_TYPE_UNDERGROUND
	map_header_flags allow_cycling=TRUE, allow_escaping=TRUE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/FiveIsland_LostCave_Room6/header.inc =====
@ ===== BEGIN data/maps/FiveIsland_LostCave_Room7/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FiveIsland_LostCave_Room7/map.json
@

FiveIsland_LostCave_Room7:
	.4byte FiveIsland_LostCave_Room7_Layout
	.4byte FiveIsland_LostCave_Room7_MapEvents
	.4byte FiveIsland_LostCave_Room7_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_CAVE
	.2byte LAYOUT_FIVE_ISLAND_LOST_CAVE_ROOM7
	.byte MAPSEC_LOST_CAVE
	.byte FALSE
	.byte WEATHER_FOG_HORIZONTAL
	.byte MAP_TYPE_UNDERGROUND
	map_header_flags allow_cycling=TRUE, allow_escaping=TRUE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/FiveIsland_LostCave_Room7/header.inc =====
@ ===== BEGIN data/maps/FiveIsland_LostCave_Room8/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FiveIsland_LostCave_Room8/map.json
@

FiveIsland_LostCave_Room8:
	.4byte FiveIsland_LostCave_Room8_Layout
	.4byte FiveIsland_LostCave_Room8_MapEvents
	.4byte FiveIsland_LostCave_Room8_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_CAVE
	.2byte LAYOUT_FIVE_ISLAND_LOST_CAVE_ROOM8
	.byte MAPSEC_LOST_CAVE
	.byte FALSE
	.byte WEATHER_FOG_HORIZONTAL
	.byte MAP_TYPE_UNDERGROUND
	map_header_flags allow_cycling=TRUE, allow_escaping=TRUE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/FiveIsland_LostCave_Room8/header.inc =====
@ ===== BEGIN data/maps/FiveIsland_LostCave_Room9/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FiveIsland_LostCave_Room9/map.json
@

FiveIsland_LostCave_Room9:
	.4byte FiveIsland_LostCave_Room9_Layout
	.4byte FiveIsland_LostCave_Room9_MapEvents
	.4byte FiveIsland_LostCave_Room9_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_CAVE
	.2byte LAYOUT_FIVE_ISLAND_LOST_CAVE_ROOM9
	.byte MAPSEC_LOST_CAVE
	.byte FALSE
	.byte WEATHER_FOG_HORIZONTAL
	.byte MAP_TYPE_UNDERGROUND
	map_header_flags allow_cycling=TRUE, allow_escaping=TRUE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/FiveIsland_LostCave_Room9/header.inc =====
@ ===== BEGIN data/maps/FiveIsland_LostCave_Room10/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FiveIsland_LostCave_Room10/map.json
@

FiveIsland_LostCave_Room10:
	.4byte FiveIsland_LostCave_Room10_Layout
	.4byte FiveIsland_LostCave_Room10_MapEvents
	.4byte FiveIsland_LostCave_Room10_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_CAVE
	.2byte LAYOUT_FIVE_ISLAND_LOST_CAVE_ROOM10
	.byte MAPSEC_LOST_CAVE
	.byte FALSE
	.byte WEATHER_FOG_HORIZONTAL
	.byte MAP_TYPE_UNDERGROUND
	map_header_flags allow_cycling=TRUE, allow_escaping=TRUE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/FiveIsland_LostCave_Room10/header.inc =====
@ ===== BEGIN data/maps/FiveIsland_LostCave_Room11/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FiveIsland_LostCave_Room11/map.json
@

FiveIsland_LostCave_Room11:
	.4byte FiveIsland_LostCave_Room11_Layout
	.4byte FiveIsland_LostCave_Room11_MapEvents
	.4byte FiveIsland_LostCave_Room11_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_CAVE
	.2byte LAYOUT_FIVE_ISLAND_LOST_CAVE_ROOM11
	.byte MAPSEC_LOST_CAVE
	.byte FALSE
	.byte WEATHER_FOG_HORIZONTAL
	.byte MAP_TYPE_UNDERGROUND
	map_header_flags allow_cycling=TRUE, allow_escaping=TRUE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/FiveIsland_LostCave_Room11/header.inc =====
@ ===== BEGIN data/maps/FiveIsland_LostCave_Room12/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FiveIsland_LostCave_Room12/map.json
@

FiveIsland_LostCave_Room12:
	.4byte FiveIsland_LostCave_Room12_Layout
	.4byte FiveIsland_LostCave_Room12_MapEvents
	.4byte FiveIsland_LostCave_Room12_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_CAVE
	.2byte LAYOUT_FIVE_ISLAND_LOST_CAVE_ROOM12
	.byte MAPSEC_LOST_CAVE
	.byte FALSE
	.byte WEATHER_FOG_HORIZONTAL
	.byte MAP_TYPE_UNDERGROUND
	map_header_flags allow_cycling=TRUE, allow_escaping=TRUE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/FiveIsland_LostCave_Room12/header.inc =====
@ ===== BEGIN data/maps/FiveIsland_LostCave_Room13/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FiveIsland_LostCave_Room13/map.json
@

FiveIsland_LostCave_Room13:
	.4byte FiveIsland_LostCave_Room13_Layout
	.4byte FiveIsland_LostCave_Room13_MapEvents
	.4byte FiveIsland_LostCave_Room13_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_CAVE
	.2byte LAYOUT_FIVE_ISLAND_LOST_CAVE_ROOM13
	.byte MAPSEC_LOST_CAVE
	.byte FALSE
	.byte WEATHER_FOG_HORIZONTAL
	.byte MAP_TYPE_UNDERGROUND
	map_header_flags allow_cycling=TRUE, allow_escaping=TRUE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/FiveIsland_LostCave_Room13/header.inc =====
@ ===== BEGIN data/maps/FiveIsland_LostCave_Room14/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FiveIsland_LostCave_Room14/map.json
@

FiveIsland_LostCave_Room14:
	.4byte FiveIsland_LostCave_Room14_Layout
	.4byte FiveIsland_LostCave_Room14_MapEvents
	.4byte FiveIsland_LostCave_Room14_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_CAVE
	.2byte LAYOUT_FIVE_ISLAND_LOST_CAVE_ROOM14
	.byte MAPSEC_LOST_CAVE
	.byte FALSE
	.byte WEATHER_FOG_HORIZONTAL
	.byte MAP_TYPE_UNDERGROUND
	map_header_flags allow_cycling=TRUE, allow_escaping=TRUE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/FiveIsland_LostCave_Room14/header.inc =====
@ ===== BEGIN data/maps/SevenIsland_TanobyRuins_MoneanChamber/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SevenIsland_TanobyRuins_MoneanChamber/map.json
@

SevenIsland_TanobyRuins_MoneanChamber:
	.4byte SevenIsland_TanobyRuins_MoneanChamber_Layout
	.4byte SevenIsland_TanobyRuins_MoneanChamber_MapEvents
	.4byte SevenIsland_TanobyRuins_MoneanChamber_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_DUNGEON
	.2byte LAYOUT_SEVEN_ISLAND_TANOBY_RUINS_MONEAN_CHAMBER
	.byte MAPSEC_MONEAN_CHAMBER
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_UNDERGROUND
	map_header_flags allow_cycling=TRUE, allow_escaping=TRUE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_INDOOR_1

@ ===== END data/maps/SevenIsland_TanobyRuins_MoneanChamber/header.inc =====
@ ===== BEGIN data/maps/SevenIsland_TanobyRuins_LiptooChamber/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SevenIsland_TanobyRuins_LiptooChamber/map.json
@

SevenIsland_TanobyRuins_LiptooChamber:
	.4byte SevenIsland_TanobyRuins_LiptooChamber_Layout
	.4byte SevenIsland_TanobyRuins_LiptooChamber_MapEvents
	.4byte SevenIsland_TanobyRuins_LiptooChamber_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_DUNGEON
	.2byte LAYOUT_SEVEN_ISLAND_TANOBY_RUINS_LIPTOO_CHAMBER
	.byte MAPSEC_LIPTOO_CHAMBER
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_UNDERGROUND
	map_header_flags allow_cycling=TRUE, allow_escaping=TRUE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_INDOOR_1

@ ===== END data/maps/SevenIsland_TanobyRuins_LiptooChamber/header.inc =====
@ ===== BEGIN data/maps/SevenIsland_TanobyRuins_WeepthChamber/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SevenIsland_TanobyRuins_WeepthChamber/map.json
@

SevenIsland_TanobyRuins_WeepthChamber:
	.4byte SevenIsland_TanobyRuins_WeepthChamber_Layout
	.4byte SevenIsland_TanobyRuins_WeepthChamber_MapEvents
	.4byte SevenIsland_TanobyRuins_WeepthChamber_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_DUNGEON
	.2byte LAYOUT_SEVEN_ISLAND_TANOBY_RUINS_WEEPTH_CHAMBER
	.byte MAPSEC_WEEPTH_CHAMBER
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_UNDERGROUND
	map_header_flags allow_cycling=TRUE, allow_escaping=TRUE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_INDOOR_1

@ ===== END data/maps/SevenIsland_TanobyRuins_WeepthChamber/header.inc =====
@ ===== BEGIN data/maps/SevenIsland_TanobyRuins_DilfordChamber/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SevenIsland_TanobyRuins_DilfordChamber/map.json
@

SevenIsland_TanobyRuins_DilfordChamber:
	.4byte SevenIsland_TanobyRuins_DilfordChamber_Layout
	.4byte SevenIsland_TanobyRuins_DilfordChamber_MapEvents
	.4byte SevenIsland_TanobyRuins_DilfordChamber_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_DUNGEON
	.2byte LAYOUT_SEVEN_ISLAND_TANOBY_RUINS_DILFORD_CHAMBER
	.byte MAPSEC_DILFORD_CHAMBER
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_UNDERGROUND
	map_header_flags allow_cycling=TRUE, allow_escaping=TRUE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_INDOOR_1

@ ===== END data/maps/SevenIsland_TanobyRuins_DilfordChamber/header.inc =====
@ ===== BEGIN data/maps/SevenIsland_TanobyRuins_ScufibChamber/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SevenIsland_TanobyRuins_ScufibChamber/map.json
@

SevenIsland_TanobyRuins_ScufibChamber:
	.4byte SevenIsland_TanobyRuins_ScufibChamber_Layout
	.4byte SevenIsland_TanobyRuins_ScufibChamber_MapEvents
	.4byte SevenIsland_TanobyRuins_ScufibChamber_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_DUNGEON
	.2byte LAYOUT_SEVEN_ISLAND_TANOBY_RUINS_SCUFIB_CHAMBER
	.byte MAPSEC_SCUFIB_CHAMBER
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_UNDERGROUND
	map_header_flags allow_cycling=TRUE, allow_escaping=TRUE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_INDOOR_1

@ ===== END data/maps/SevenIsland_TanobyRuins_ScufibChamber/header.inc =====
@ ===== BEGIN data/maps/SevenIsland_TanobyRuins_RixyChamber/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SevenIsland_TanobyRuins_RixyChamber/map.json
@

SevenIsland_TanobyRuins_RixyChamber:
	.4byte SevenIsland_TanobyRuins_RixyChamber_Layout
	.4byte SevenIsland_TanobyRuins_RixyChamber_MapEvents
	.4byte SevenIsland_TanobyRuins_RixyChamber_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_DUNGEON
	.2byte LAYOUT_SEVEN_ISLAND_TANOBY_RUINS_RIXY_CHAMBER
	.byte MAPSEC_RIXY_CHAMBER
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_UNDERGROUND
	map_header_flags allow_cycling=TRUE, allow_escaping=TRUE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_INDOOR_1

@ ===== END data/maps/SevenIsland_TanobyRuins_RixyChamber/header.inc =====
@ ===== BEGIN data/maps/SevenIsland_TanobyRuins_ViapoisChamber/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SevenIsland_TanobyRuins_ViapoisChamber/map.json
@

SevenIsland_TanobyRuins_ViapoisChamber:
	.4byte SevenIsland_TanobyRuins_ViapoisChamber_Layout
	.4byte SevenIsland_TanobyRuins_ViapoisChamber_MapEvents
	.4byte SevenIsland_TanobyRuins_ViapoisChamber_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_DUNGEON
	.2byte LAYOUT_SEVEN_ISLAND_TANOBY_RUINS_VIAPOIS_CHAMBER
	.byte MAPSEC_VIAPOIS_CHAMBER
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_UNDERGROUND
	map_header_flags allow_cycling=TRUE, allow_escaping=TRUE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_INDOOR_1

@ ===== END data/maps/SevenIsland_TanobyRuins_ViapoisChamber/header.inc =====
@ ===== BEGIN data/maps/ThreeIsland_DunsparceTunnel/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/ThreeIsland_DunsparceTunnel/map.json
@

ThreeIsland_DunsparceTunnel:
	.4byte ThreeIsland_DunsparceTunnel_Layout
	.4byte ThreeIsland_DunsparceTunnel_MapEvents
	.4byte ThreeIsland_DunsparceTunnel_MapScripts
	.4byte NULL
	.2byte MUS_VIRIDIAN_FOREST
	.2byte LAYOUT_THREE_ISLAND_DUNSPARCE_TUNNEL
	.byte MAPSEC_THREE_ISLE_PATH
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_UNDERGROUND
	map_header_flags allow_cycling=TRUE, allow_escaping=TRUE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/ThreeIsland_DunsparceTunnel/header.inc =====
@ ===== BEGIN data/maps/SevenIsland_SevaultCanyon_TanobyKey/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SevenIsland_SevaultCanyon_TanobyKey/map.json
@

SevenIsland_SevaultCanyon_TanobyKey:
	.4byte SevenIsland_SevaultCanyon_TanobyKey_Layout
	.4byte SevenIsland_SevaultCanyon_TanobyKey_MapEvents
	.4byte SevenIsland_SevaultCanyon_TanobyKey_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_DUNGEON
	.2byte LAYOUT_SEVEN_ISLAND_SEVAULT_CANYON_TANOBY_KEY
	.byte MAPSEC_TANOBY_KEY
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_UNDERGROUND
	map_header_flags allow_cycling=TRUE, allow_escaping=TRUE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_INDOOR_1

@ ===== END data/maps/SevenIsland_SevaultCanyon_TanobyKey/header.inc =====
@ ===== BEGIN data/maps/NavelRock_1F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/NavelRock_1F/map.json
@

NavelRock_1F:
	.4byte NavelRock_1F_Layout
	.4byte NavelRock_1F_MapEvents
	.4byte NavelRock_1F_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_CAVE
	.2byte LAYOUT_NAVEL_ROCK_1F
	.byte MAPSEC_NAVEL_ROCK
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_UNDERGROUND
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/NavelRock_1F/header.inc =====
@ ===== BEGIN data/maps/NavelRock_Summit/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/NavelRock_Summit/map.json
@

NavelRock_Summit:
	.4byte NavelRock_Summit_Layout
	.4byte NavelRock_Summit_MapEvents
	.4byte NavelRock_Summit_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_CAVE
	.2byte LAYOUT_NAVEL_ROCK_SUMMIT
	.byte MAPSEC_NAVEL_ROCK
	.byte FALSE
	.byte WEATHER_SHADE
	.byte MAP_TYPE_UNDERGROUND
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/NavelRock_Summit/header.inc =====
@ ===== BEGIN data/maps/NavelRock_Base/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/NavelRock_Base/map.json
@

NavelRock_Base:
	.4byte NavelRock_Base_Layout
	.4byte NavelRock_Base_MapEvents
	.4byte NavelRock_Base_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_CAVE
	.2byte LAYOUT_NAVEL_ROCK_BASE
	.byte MAPSEC_NAVEL_ROCK
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_UNDERGROUND
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/NavelRock_Base/header.inc =====
@ ===== BEGIN data/maps/NavelRock_SummitPath_2F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/NavelRock_SummitPath_2F/map.json
@

NavelRock_SummitPath_2F:
	.4byte NavelRock_SummitPath_2F_Layout
	.4byte NavelRock_SummitPath_2F_MapEvents
	.4byte NavelRock_SummitPath_2F_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_CAVE
	.2byte LAYOUT_NAVEL_ROCK_SUMMIT_PATH_2F
	.byte MAPSEC_NAVEL_ROCK
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_UNDERGROUND
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/NavelRock_SummitPath_2F/header.inc =====
@ ===== BEGIN data/maps/NavelRock_SummitPath_3F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/NavelRock_SummitPath_3F/map.json
@

NavelRock_SummitPath_3F:
	.4byte NavelRock_SummitPath_3F_Layout
	.4byte NavelRock_SummitPath_3F_MapEvents
	.4byte NavelRock_SummitPath_3F_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_CAVE
	.2byte LAYOUT_NAVEL_ROCK_SUMMIT_PATH_3F
	.byte MAPSEC_NAVEL_ROCK
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_UNDERGROUND
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/NavelRock_SummitPath_3F/header.inc =====
@ ===== BEGIN data/maps/NavelRock_SummitPath_4F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/NavelRock_SummitPath_4F/map.json
@

NavelRock_SummitPath_4F:
	.4byte NavelRock_SummitPath_4F_Layout
	.4byte NavelRock_SummitPath_4F_MapEvents
	.4byte NavelRock_SummitPath_4F_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_CAVE
	.2byte LAYOUT_NAVEL_ROCK_SUMMIT_PATH_4F
	.byte MAPSEC_NAVEL_ROCK
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_UNDERGROUND
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/NavelRock_SummitPath_4F/header.inc =====
@ ===== BEGIN data/maps/NavelRock_SummitPath_5F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/NavelRock_SummitPath_5F/map.json
@

NavelRock_SummitPath_5F:
	.4byte NavelRock_SummitPath_5F_Layout
	.4byte NavelRock_SummitPath_5F_MapEvents
	.4byte NavelRock_SummitPath_5F_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_CAVE
	.2byte LAYOUT_NAVEL_ROCK_SUMMIT_PATH_5F
	.byte MAPSEC_NAVEL_ROCK
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_UNDERGROUND
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/NavelRock_SummitPath_5F/header.inc =====
@ ===== BEGIN data/maps/NavelRock_BasePath_B1F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/NavelRock_BasePath_B1F/map.json
@

NavelRock_BasePath_B1F:
	.4byte NavelRock_BasePath_B1F_Layout
	.4byte NavelRock_BasePath_B1F_MapEvents
	.4byte NavelRock_BasePath_B1F_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_CAVE
	.2byte LAYOUT_NAVEL_ROCK_BASE_PATH_B1F
	.byte MAPSEC_NAVEL_ROCK
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_UNDERGROUND
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/NavelRock_BasePath_B1F/header.inc =====
@ ===== BEGIN data/maps/NavelRock_BasePath_B2F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/NavelRock_BasePath_B2F/map.json
@

NavelRock_BasePath_B2F:
	.4byte NavelRock_BasePath_B2F_Layout
	.4byte NavelRock_BasePath_B2F_MapEvents
	.4byte NavelRock_BasePath_B2F_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_CAVE
	.2byte LAYOUT_NAVEL_ROCK_BASE_PATH_B2F
	.byte MAPSEC_NAVEL_ROCK
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_UNDERGROUND
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/NavelRock_BasePath_B2F/header.inc =====
@ ===== BEGIN data/maps/NavelRock_BasePath_B3F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/NavelRock_BasePath_B3F/map.json
@

NavelRock_BasePath_B3F:
	.4byte NavelRock_BasePath_B3F_Layout
	.4byte NavelRock_BasePath_B3F_MapEvents
	.4byte NavelRock_BasePath_B3F_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_CAVE
	.2byte LAYOUT_NAVEL_ROCK_BASE_PATH_B3F
	.byte MAPSEC_NAVEL_ROCK
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_UNDERGROUND
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/NavelRock_BasePath_B3F/header.inc =====
@ ===== BEGIN data/maps/NavelRock_BasePath_B4F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/NavelRock_BasePath_B4F/map.json
@

NavelRock_BasePath_B4F:
	.4byte NavelRock_BasePath_B4F_Layout
	.4byte NavelRock_BasePath_B4F_MapEvents
	.4byte NavelRock_BasePath_B4F_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_CAVE
	.2byte LAYOUT_NAVEL_ROCK_BASE_PATH_B4F
	.byte MAPSEC_NAVEL_ROCK
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_UNDERGROUND
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/NavelRock_BasePath_B4F/header.inc =====
@ ===== BEGIN data/maps/NavelRock_BasePath_B5F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/NavelRock_BasePath_B5F/map.json
@

NavelRock_BasePath_B5F:
	.4byte NavelRock_BasePath_B5F_Layout
	.4byte NavelRock_BasePath_B5F_MapEvents
	.4byte NavelRock_BasePath_B5F_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_CAVE
	.2byte LAYOUT_NAVEL_ROCK_BASE_PATH_B5F
	.byte MAPSEC_NAVEL_ROCK
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_UNDERGROUND
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/NavelRock_BasePath_B5F/header.inc =====
@ ===== BEGIN data/maps/NavelRock_BasePath_B6F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/NavelRock_BasePath_B6F/map.json
@

NavelRock_BasePath_B6F:
	.4byte NavelRock_BasePath_B6F_Layout
	.4byte NavelRock_BasePath_B6F_MapEvents
	.4byte NavelRock_BasePath_B6F_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_CAVE
	.2byte LAYOUT_NAVEL_ROCK_BASE_PATH_B6F
	.byte MAPSEC_NAVEL_ROCK
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_UNDERGROUND
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/NavelRock_BasePath_B6F/header.inc =====
@ ===== BEGIN data/maps/NavelRock_BasePath_B7F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/NavelRock_BasePath_B7F/map.json
@

NavelRock_BasePath_B7F:
	.4byte NavelRock_BasePath_B7F_Layout
	.4byte NavelRock_BasePath_B7F_MapEvents
	.4byte NavelRock_BasePath_B7F_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_CAVE
	.2byte LAYOUT_NAVEL_ROCK_BASE_PATH_B7F
	.byte MAPSEC_NAVEL_ROCK
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_UNDERGROUND
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/NavelRock_BasePath_B7F/header.inc =====
@ ===== BEGIN data/maps/NavelRock_BasePath_B8F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/NavelRock_BasePath_B8F/map.json
@

NavelRock_BasePath_B8F:
	.4byte NavelRock_BasePath_B8F_Layout
	.4byte NavelRock_BasePath_B8F_MapEvents
	.4byte NavelRock_BasePath_B8F_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_CAVE
	.2byte LAYOUT_NAVEL_ROCK_BASE_PATH_B8F
	.byte MAPSEC_NAVEL_ROCK
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_UNDERGROUND
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/NavelRock_BasePath_B8F/header.inc =====
@ ===== BEGIN data/maps/NavelRock_BasePath_B9F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/NavelRock_BasePath_B9F/map.json
@

NavelRock_BasePath_B9F:
	.4byte NavelRock_BasePath_B9F_Layout
	.4byte NavelRock_BasePath_B9F_MapEvents
	.4byte NavelRock_BasePath_B9F_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_CAVE
	.2byte LAYOUT_NAVEL_ROCK_BASE_PATH_B9F
	.byte MAPSEC_NAVEL_ROCK
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_UNDERGROUND
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/NavelRock_BasePath_B9F/header.inc =====
@ ===== BEGIN data/maps/NavelRock_BasePath_B10F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/NavelRock_BasePath_B10F/map.json
@

NavelRock_BasePath_B10F:
	.4byte NavelRock_BasePath_B10F_Layout
	.4byte NavelRock_BasePath_B10F_MapEvents
	.4byte NavelRock_BasePath_B10F_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_CAVE
	.2byte LAYOUT_NAVEL_ROCK_BASE_PATH_B10F
	.byte MAPSEC_NAVEL_ROCK
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_UNDERGROUND
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/NavelRock_BasePath_B10F/header.inc =====
@ ===== BEGIN data/maps/NavelRock_BasePath_B11F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/NavelRock_BasePath_B11F/map.json
@

NavelRock_BasePath_B11F:
	.4byte NavelRock_BasePath_B11F_Layout
	.4byte NavelRock_BasePath_B11F_MapEvents
	.4byte NavelRock_BasePath_B11F_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_CAVE
	.2byte LAYOUT_NAVEL_ROCK_BASE_PATH_B11F
	.byte MAPSEC_NAVEL_ROCK
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_UNDERGROUND
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/NavelRock_BasePath_B11F/header.inc =====
@ ===== BEGIN data/maps/NavelRock_B1F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/NavelRock_B1F/map.json
@

NavelRock_B1F:
	.4byte NavelRock_B1F_Layout
	.4byte NavelRock_B1F_MapEvents
	.4byte NavelRock_B1F_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_CAVE
	.2byte LAYOUT_NAVEL_ROCK_B1F
	.byte MAPSEC_NAVEL_ROCK
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_UNDERGROUND
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/NavelRock_B1F/header.inc =====
@ ===== BEGIN data/maps/NavelRock_Fork/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/NavelRock_Fork/map.json
@

NavelRock_Fork:
	.4byte NavelRock_Fork_Layout
	.4byte NavelRock_Fork_MapEvents
	.4byte NavelRock_Fork_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_CAVE
	.2byte LAYOUT_NAVEL_ROCK_FORK
	.byte MAPSEC_NAVEL_ROCK
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_UNDERGROUND
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/NavelRock_Fork/header.inc =====
@ ===== BEGIN data/maps/BirthIsland_Exterior/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/BirthIsland_Exterior/map.json
@

BirthIsland_Exterior:
	.4byte BirthIsland_Exterior_Layout
	.4byte BirthIsland_Exterior_MapEvents
	.4byte BirthIsland_Exterior_MapScripts
	.4byte NULL
	.2byte MUS_NONE
	.2byte LAYOUT_BIRTH_ISLAND_EXTERIOR
	.byte MAPSEC_BIRTH_ISLAND
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_ROUTE
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/BirthIsland_Exterior/header.inc =====
@ ===== BEGIN data/maps/OneIsland_KindleRoad_EmberSpa/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/OneIsland_KindleRoad_EmberSpa/map.json
@

OneIsland_KindleRoad_EmberSpa:
	.4byte OneIsland_KindleRoad_EmberSpa_Layout
	.4byte OneIsland_KindleRoad_EmberSpa_MapEvents
	.4byte OneIsland_KindleRoad_EmberSpa_MapScripts
	.4byte NULL
	.2byte MUS_FUCHSIA
	.2byte LAYOUT_ONE_ISLAND_KINDLE_ROAD_EMBER_SPA
	.byte MAPSEC_EMBER_SPA
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_UNDERGROUND
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/OneIsland_KindleRoad_EmberSpa/header.inc =====
@ ===== BEGIN data/maps/BirthIsland_Harbor/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/BirthIsland_Harbor/map.json
@

BirthIsland_Harbor:
	.4byte Island_Harbor_Layout
	.4byte BirthIsland_Harbor_MapEvents
	.4byte BirthIsland_Harbor_MapScripts
	.4byte NULL
	.2byte MUS_NONE
	.2byte LAYOUT_ISLAND_HARBOR
	.byte MAPSEC_BIRTH_ISLAND
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/BirthIsland_Harbor/header.inc =====
@ ===== BEGIN data/maps/NavelRock_Harbor/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/NavelRock_Harbor/map.json
@

NavelRock_Harbor:
	.4byte Island_Harbor_Layout
	.4byte NavelRock_Harbor_MapEvents
	.4byte NavelRock_Harbor_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_ROUTE
	.2byte LAYOUT_ISLAND_HARBOR
	.byte MAPSEC_NAVEL_ROCK
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/NavelRock_Harbor/header.inc =====
@ ===== BEGIN data/maps/PalletTown/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/PalletTown/map.json
@

PalletTown:
	.4byte PalletTown_Layout
	.4byte PalletTown_MapEvents
	.4byte PalletTown_MapScripts
	.4byte PalletTown_MapConnections
	.2byte MUS_PALLET
	.2byte LAYOUT_PALLET_TOWN
	.byte MAPSEC_PALLET_TOWN
	.byte FALSE
	.byte WEATHER_SUNNY
	.byte MAP_TYPE_TOWN
	map_header_flags allow_cycling=TRUE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/PalletTown/header.inc =====
@ ===== BEGIN data/maps/ViridianCity/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/ViridianCity/map.json
@

ViridianCity:
	.4byte ViridianCity_Layout
	.4byte ViridianCity_MapEvents
	.4byte ViridianCity_MapScripts
	.4byte ViridianCity_MapConnections
	.2byte MUS_PEWTER
	.2byte LAYOUT_VIRIDIAN_CITY
	.byte MAPSEC_VIRIDIAN_CITY
	.byte FALSE
	.byte WEATHER_SUNNY
	.byte MAP_TYPE_TOWN
	map_header_flags allow_cycling=TRUE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/ViridianCity/header.inc =====
@ ===== BEGIN data/maps/PewterCity/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/PewterCity/map.json
@

PewterCity:
	.4byte PewterCity_Layout
	.4byte PewterCity_MapEvents
	.4byte PewterCity_MapScripts
	.4byte PewterCity_MapConnections
	.2byte MUS_PEWTER
	.2byte LAYOUT_PEWTER_CITY
	.byte MAPSEC_PEWTER_CITY
	.byte FALSE
	.byte WEATHER_SUNNY
	.byte MAP_TYPE_TOWN
	map_header_flags allow_cycling=TRUE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/PewterCity/header.inc =====
@ ===== BEGIN data/maps/CeruleanCity/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/CeruleanCity/map.json
@

CeruleanCity:
	.4byte CeruleanCity_Layout
	.4byte CeruleanCity_MapEvents
	.4byte CeruleanCity_MapScripts
	.4byte CeruleanCity_MapConnections
	.2byte MUS_FUCHSIA
	.2byte LAYOUT_CERULEAN_CITY
	.byte MAPSEC_CERULEAN_CITY
	.byte FALSE
	.byte WEATHER_SUNNY
	.byte MAP_TYPE_TOWN
	map_header_flags allow_cycling=TRUE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/CeruleanCity/header.inc =====
@ ===== BEGIN data/maps/LavenderTown/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/LavenderTown/map.json
@

LavenderTown:
	.4byte LavenderTown_Layout
	.4byte LavenderTown_MapEvents
	.4byte LavenderTown_MapScripts
	.4byte LavenderTown_MapConnections
	.2byte MUS_LAVENDER
	.2byte LAYOUT_LAVENDER_TOWN
	.byte MAPSEC_LAVENDER_TOWN
	.byte FALSE
	.byte WEATHER_SUNNY
	.byte MAP_TYPE_TOWN
	map_header_flags allow_cycling=TRUE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/LavenderTown/header.inc =====
@ ===== BEGIN data/maps/VermilionCity/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/VermilionCity/map.json
@

VermilionCity:
	.4byte VermilionCity_Layout
	.4byte VermilionCity_MapEvents
	.4byte VermilionCity_MapScripts
	.4byte VermilionCity_MapConnections
	.2byte MUS_VERMILLION
	.2byte LAYOUT_VERMILION_CITY
	.byte MAPSEC_VERMILION_CITY
	.byte FALSE
	.byte WEATHER_SUNNY
	.byte MAP_TYPE_TOWN
	map_header_flags allow_cycling=TRUE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/VermilionCity/header.inc =====
@ ===== BEGIN data/maps/CeladonCity/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/CeladonCity/map.json
@

CeladonCity:
	.4byte CeladonCity_Layout
	.4byte CeladonCity_MapEvents
	.4byte CeladonCity_MapScripts
	.4byte CeladonCity_MapConnections
	.2byte MUS_CELADON
	.2byte LAYOUT_CELADON_CITY
	.byte MAPSEC_CELADON_CITY
	.byte FALSE
	.byte WEATHER_SUNNY
	.byte MAP_TYPE_TOWN
	map_header_flags allow_cycling=TRUE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/CeladonCity/header.inc =====
@ ===== BEGIN data/maps/FuchsiaCity/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FuchsiaCity/map.json
@

FuchsiaCity:
	.4byte FuchsiaCity_Layout
	.4byte FuchsiaCity_MapEvents
	.4byte FuchsiaCity_MapScripts
	.4byte FuchsiaCity_MapConnections
	.2byte MUS_FUCHSIA
	.2byte LAYOUT_FUCHSIA_CITY
	.byte MAPSEC_FUCHSIA_CITY
	.byte FALSE
	.byte WEATHER_SUNNY
	.byte MAP_TYPE_TOWN
	map_header_flags allow_cycling=TRUE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/FuchsiaCity/header.inc =====
@ ===== BEGIN data/maps/CinnabarIsland/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/CinnabarIsland/map.json
@

CinnabarIsland:
	.4byte CinnabarIsland_Layout
	.4byte CinnabarIsland_MapEvents
	.4byte CinnabarIsland_MapScripts
	.4byte CinnabarIsland_MapConnections
	.2byte MUS_CINNABAR
	.2byte LAYOUT_CINNABAR_ISLAND
	.byte MAPSEC_CINNABAR_ISLAND
	.byte FALSE
	.byte WEATHER_SUNNY
	.byte MAP_TYPE_TOWN
	map_header_flags allow_cycling=TRUE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/CinnabarIsland/header.inc =====
@ ===== BEGIN data/maps/IndigoPlateau_Exterior/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/IndigoPlateau_Exterior/map.json
@

IndigoPlateau_Exterior:
	.4byte IndigoPlateau_Exterior_Layout
	.4byte IndigoPlateau_Exterior_MapEvents
	.4byte IndigoPlateau_Exterior_MapScripts
	.4byte IndigoPlateau_Exterior_MapConnections
	.2byte MUS_VICTORY_ROAD
	.2byte LAYOUT_INDIGO_PLATEAU_EXTERIOR
	.byte MAPSEC_INDIGO_PLATEAU
	.byte FALSE
	.byte WEATHER_SUNNY
	.byte MAP_TYPE_TOWN
	map_header_flags allow_cycling=TRUE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/IndigoPlateau_Exterior/header.inc =====
@ ===== BEGIN data/maps/SaffronCity/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SaffronCity/map.json
@

SaffronCity:
	.4byte SaffronCity_Layout
	.4byte SaffronCity_MapEvents
	.4byte SaffronCity_MapScripts
	.4byte NULL
	.2byte MUS_PEWTER
	.2byte LAYOUT_SAFFRON_CITY
	.byte MAPSEC_SAFFRON_CITY
	.byte FALSE
	.byte WEATHER_SUNNY
	.byte MAP_TYPE_TOWN
	map_header_flags allow_cycling=TRUE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SaffronCity/header.inc =====
@ ===== BEGIN data/maps/SaffronCity_Connection/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SaffronCity_Connection/map.json
@

SaffronCity_Connection:
	.4byte SaffronCity_Connection_Layout
	.4byte SaffronCity_Connection_MapEvents
	.4byte SaffronCity_Connection_MapScripts
	.4byte SaffronCity_Connection_MapConnections
	.2byte MUS_PEWTER
	.2byte LAYOUT_SAFFRON_CITY_CONNECTION
	.byte MAPSEC_SAFFRON_CITY
	.byte FALSE
	.byte WEATHER_SUNNY
	.byte MAP_TYPE_TOWN
	map_header_flags allow_cycling=TRUE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SaffronCity_Connection/header.inc =====
@ ===== BEGIN data/maps/OneIsland/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/OneIsland/map.json
@

OneIsland:
	.4byte OneIsland_Layout
	.4byte OneIsland_MapEvents
	.4byte OneIsland_MapScripts
	.4byte OneIsland_MapConnections
	.2byte MUS_SEVII_123
	.2byte LAYOUT_ONE_ISLAND
	.byte MAPSEC_ONE_ISLAND
	.byte FALSE
	.byte WEATHER_SUNNY
	.byte MAP_TYPE_TOWN
	map_header_flags allow_cycling=TRUE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/OneIsland/header.inc =====
@ ===== BEGIN data/maps/TwoIsland/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/TwoIsland/map.json
@

TwoIsland:
	.4byte TwoIsland_Layout
	.4byte TwoIsland_MapEvents
	.4byte TwoIsland_MapScripts
	.4byte TwoIsland_MapConnections
	.2byte MUS_SEVII_123
	.2byte LAYOUT_TWO_ISLAND
	.byte MAPSEC_TWO_ISLAND
	.byte FALSE
	.byte WEATHER_SUNNY
	.byte MAP_TYPE_TOWN
	map_header_flags allow_cycling=TRUE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/TwoIsland/header.inc =====
@ ===== BEGIN data/maps/ThreeIsland/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/ThreeIsland/map.json
@

ThreeIsland:
	.4byte ThreeIsland_Layout
	.4byte ThreeIsland_MapEvents
	.4byte ThreeIsland_MapScripts
	.4byte ThreeIsland_MapConnections
	.2byte MUS_SEVII_123
	.2byte LAYOUT_THREE_ISLAND
	.byte MAPSEC_THREE_ISLAND
	.byte FALSE
	.byte WEATHER_SUNNY
	.byte MAP_TYPE_TOWN
	map_header_flags allow_cycling=TRUE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/ThreeIsland/header.inc =====
@ ===== BEGIN data/maps/FourIsland/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FourIsland/map.json
@

FourIsland:
	.4byte FourIsland_Layout
	.4byte FourIsland_MapEvents
	.4byte FourIsland_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_45
	.2byte LAYOUT_FOUR_ISLAND
	.byte MAPSEC_FOUR_ISLAND
	.byte FALSE
	.byte WEATHER_SUNNY
	.byte MAP_TYPE_TOWN
	map_header_flags allow_cycling=TRUE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/FourIsland/header.inc =====
@ ===== BEGIN data/maps/FiveIsland/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FiveIsland/map.json
@

FiveIsland:
	.4byte FiveIsland_Layout
	.4byte FiveIsland_MapEvents
	.4byte FiveIsland_MapScripts
	.4byte FiveIsland_MapConnections
	.2byte MUS_SEVII_45
	.2byte LAYOUT_FIVE_ISLAND
	.byte MAPSEC_FIVE_ISLAND
	.byte FALSE
	.byte WEATHER_SUNNY
	.byte MAP_TYPE_TOWN
	map_header_flags allow_cycling=TRUE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/FiveIsland/header.inc =====
@ ===== BEGIN data/maps/SevenIsland/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SevenIsland/map.json
@

SevenIsland:
	.4byte SevenIsland_Layout
	.4byte SevenIsland_MapEvents
	.4byte SevenIsland_MapScripts
	.4byte SevenIsland_MapConnections
	.2byte MUS_SEVII_67
	.2byte LAYOUT_SEVEN_ISLAND
	.byte MAPSEC_SEVEN_ISLAND
	.byte FALSE
	.byte WEATHER_SUNNY
	.byte MAP_TYPE_TOWN
	map_header_flags allow_cycling=TRUE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SevenIsland/header.inc =====
@ ===== BEGIN data/maps/SixIsland/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SixIsland/map.json
@

SixIsland:
	.4byte SixIsland_Layout
	.4byte SixIsland_MapEvents
	.4byte SixIsland_MapScripts
	.4byte SixIsland_MapConnections
	.2byte MUS_SEVII_67
	.2byte LAYOUT_SIX_ISLAND
	.byte MAPSEC_SIX_ISLAND
	.byte FALSE
	.byte WEATHER_SUNNY
	.byte MAP_TYPE_TOWN
	map_header_flags allow_cycling=TRUE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SixIsland/header.inc =====
@ ===== BEGIN data/maps/Route1/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route1/map.json
@

Route1:
	.4byte Route1_Layout
	.4byte Route1_MapEvents
	.4byte Route1_MapScripts
	.4byte Route1_MapConnections
	.2byte MUS_ROUTE1
	.2byte LAYOUT_ROUTE1
	.byte MAPSEC_ROUTE_1
	.byte FALSE
	.byte WEATHER_SUNNY
	.byte MAP_TYPE_ROUTE
	map_header_flags allow_cycling=TRUE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/Route1/header.inc =====
@ ===== BEGIN data/maps/Route2/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route2/map.json
@

Route2:
	.4byte Route2_Layout
	.4byte Route2_MapEvents
	.4byte Route2_MapScripts
	.4byte Route2_MapConnections
	.2byte MUS_ROUTE1
	.2byte LAYOUT_ROUTE2
	.byte MAPSEC_ROUTE_2
	.byte FALSE
	.byte WEATHER_SUNNY
	.byte MAP_TYPE_ROUTE
	map_header_flags allow_cycling=TRUE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/Route2/header.inc =====
@ ===== BEGIN data/maps/Route3/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route3/map.json
@

Route3:
	.4byte Route3_Layout
	.4byte Route3_MapEvents
	.4byte Route3_MapScripts
	.4byte Route3_MapConnections
	.2byte MUS_ROUTE3
	.2byte LAYOUT_ROUTE3
	.byte MAPSEC_ROUTE_3
	.byte FALSE
	.byte WEATHER_SUNNY
	.byte MAP_TYPE_ROUTE
	map_header_flags allow_cycling=TRUE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/Route3/header.inc =====
@ ===== BEGIN data/maps/Route4/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route4/map.json
@

Route4:
	.4byte Route4_Layout
	.4byte Route4_MapEvents
	.4byte Route4_MapScripts
	.4byte Route4_MapConnections
	.2byte MUS_ROUTE3
	.2byte LAYOUT_ROUTE4
	.byte MAPSEC_ROUTE_4
	.byte FALSE
	.byte WEATHER_SUNNY
	.byte MAP_TYPE_ROUTE
	map_header_flags allow_cycling=TRUE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/Route4/header.inc =====
@ ===== BEGIN data/maps/Route5/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route5/map.json
@

Route5:
	.4byte Route5_Layout
	.4byte Route5_MapEvents
	.4byte Route5_MapScripts
	.4byte Route5_MapConnections
	.2byte MUS_ROUTE3
	.2byte LAYOUT_ROUTE5
	.byte MAPSEC_ROUTE_5
	.byte FALSE
	.byte WEATHER_SUNNY
	.byte MAP_TYPE_ROUTE
	map_header_flags allow_cycling=TRUE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/Route5/header.inc =====
@ ===== BEGIN data/maps/Route6/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route6/map.json
@

Route6:
	.4byte Route6_Layout
	.4byte Route6_MapEvents
	.4byte Route6_MapScripts
	.4byte Route6_MapConnections
	.2byte MUS_ROUTE3
	.2byte LAYOUT_ROUTE6
	.byte MAPSEC_ROUTE_6
	.byte FALSE
	.byte WEATHER_SUNNY
	.byte MAP_TYPE_ROUTE
	map_header_flags allow_cycling=TRUE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/Route6/header.inc =====
@ ===== BEGIN data/maps/Route7/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route7/map.json
@

Route7:
	.4byte Route7_Layout
	.4byte Route7_MapEvents
	.4byte Route7_MapScripts
	.4byte Route7_MapConnections
	.2byte MUS_ROUTE3
	.2byte LAYOUT_ROUTE7
	.byte MAPSEC_ROUTE_7
	.byte FALSE
	.byte WEATHER_SUNNY
	.byte MAP_TYPE_ROUTE
	map_header_flags allow_cycling=TRUE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/Route7/header.inc =====
@ ===== BEGIN data/maps/Route8/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route8/map.json
@

Route8:
	.4byte Route8_Layout
	.4byte Route8_MapEvents
	.4byte Route8_MapScripts
	.4byte Route8_MapConnections
	.2byte MUS_ROUTE3
	.2byte LAYOUT_ROUTE8
	.byte MAPSEC_ROUTE_8
	.byte FALSE
	.byte WEATHER_SUNNY
	.byte MAP_TYPE_ROUTE
	map_header_flags allow_cycling=TRUE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/Route8/header.inc =====
@ ===== BEGIN data/maps/Route9/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route9/map.json
@

Route9:
	.4byte Route9_Layout
	.4byte Route9_MapEvents
	.4byte Route9_MapScripts
	.4byte Route9_MapConnections
	.2byte MUS_ROUTE3
	.2byte LAYOUT_ROUTE9
	.byte MAPSEC_ROUTE_9
	.byte FALSE
	.byte WEATHER_SUNNY
	.byte MAP_TYPE_ROUTE
	map_header_flags allow_cycling=TRUE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/Route9/header.inc =====
@ ===== BEGIN data/maps/Route10/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route10/map.json
@

Route10:
	.4byte Route10_Layout
	.4byte Route10_MapEvents
	.4byte Route10_MapScripts
	.4byte Route10_MapConnections
	.2byte MUS_ROUTE3
	.2byte LAYOUT_ROUTE10
	.byte MAPSEC_ROUTE_10
	.byte FALSE
	.byte WEATHER_SUNNY
	.byte MAP_TYPE_ROUTE
	map_header_flags allow_cycling=TRUE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/Route10/header.inc =====
@ ===== BEGIN data/maps/Route11/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route11/map.json
@

Route11:
	.4byte Route11_Layout
	.4byte Route11_MapEvents
	.4byte Route11_MapScripts
	.4byte Route11_MapConnections
	.2byte MUS_ROUTE11
	.2byte LAYOUT_ROUTE11
	.byte MAPSEC_ROUTE_11
	.byte FALSE
	.byte WEATHER_SUNNY
	.byte MAP_TYPE_ROUTE
	map_header_flags allow_cycling=TRUE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/Route11/header.inc =====
@ ===== BEGIN data/maps/Route12/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route12/map.json
@

Route12:
	.4byte Route12_Layout
	.4byte Route12_MapEvents
	.4byte Route12_MapScripts
	.4byte Route12_MapConnections
	.2byte MUS_ROUTE11
	.2byte LAYOUT_ROUTE12
	.byte MAPSEC_ROUTE_12
	.byte FALSE
	.byte WEATHER_SUNNY
	.byte MAP_TYPE_ROUTE
	map_header_flags allow_cycling=TRUE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/Route12/header.inc =====
@ ===== BEGIN data/maps/Route13/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route13/map.json
@

Route13:
	.4byte Route13_Layout
	.4byte Route13_MapEvents
	.4byte Route13_MapScripts
	.4byte Route13_MapConnections
	.2byte MUS_ROUTE11
	.2byte LAYOUT_ROUTE13
	.byte MAPSEC_ROUTE_13
	.byte FALSE
	.byte WEATHER_SUNNY
	.byte MAP_TYPE_ROUTE
	map_header_flags allow_cycling=TRUE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/Route13/header.inc =====
@ ===== BEGIN data/maps/Route14/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route14/map.json
@

Route14:
	.4byte Route14_Layout
	.4byte Route14_MapEvents
	.4byte Route14_MapScripts
	.4byte Route14_MapConnections
	.2byte MUS_ROUTE11
	.2byte LAYOUT_ROUTE14
	.byte MAPSEC_ROUTE_14
	.byte FALSE
	.byte WEATHER_SUNNY
	.byte MAP_TYPE_ROUTE
	map_header_flags allow_cycling=TRUE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/Route14/header.inc =====
@ ===== BEGIN data/maps/Route15/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route15/map.json
@

Route15:
	.4byte Route15_Layout
	.4byte Route15_MapEvents
	.4byte Route15_MapScripts
	.4byte Route15_MapConnections
	.2byte MUS_ROUTE11
	.2byte LAYOUT_ROUTE15
	.byte MAPSEC_ROUTE_15
	.byte FALSE
	.byte WEATHER_SUNNY
	.byte MAP_TYPE_ROUTE
	map_header_flags allow_cycling=TRUE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/Route15/header.inc =====
@ ===== BEGIN data/maps/Route16/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route16/map.json
@

Route16:
	.4byte Route16_Layout
	.4byte Route16_MapEvents
	.4byte Route16_MapScripts
	.4byte Route16_MapConnections
	.2byte MUS_ROUTE3
	.2byte LAYOUT_ROUTE16
	.byte MAPSEC_ROUTE_16
	.byte FALSE
	.byte WEATHER_SUNNY
	.byte MAP_TYPE_ROUTE
	map_header_flags allow_cycling=TRUE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/Route16/header.inc =====
@ ===== BEGIN data/maps/Route17/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route17/map.json
@

Route17:
	.4byte Route17_Layout
	.4byte Route17_MapEvents
	.4byte Route17_MapScripts
	.4byte Route17_MapConnections
	.2byte MUS_ROUTE3
	.2byte LAYOUT_ROUTE17
	.byte MAPSEC_ROUTE_17
	.byte FALSE
	.byte WEATHER_SUNNY
	.byte MAP_TYPE_ROUTE
	map_header_flags allow_cycling=TRUE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/Route17/header.inc =====
@ ===== BEGIN data/maps/Route18/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route18/map.json
@

Route18:
	.4byte Route18_Layout
	.4byte Route18_MapEvents
	.4byte Route18_MapScripts
	.4byte Route18_MapConnections
	.2byte MUS_ROUTE3
	.2byte LAYOUT_ROUTE18
	.byte MAPSEC_ROUTE_18
	.byte FALSE
	.byte WEATHER_SUNNY
	.byte MAP_TYPE_ROUTE
	map_header_flags allow_cycling=TRUE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/Route18/header.inc =====
@ ===== BEGIN data/maps/Route19/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route19/map.json
@

Route19:
	.4byte Route19_Layout
	.4byte Route19_MapEvents
	.4byte Route19_MapScripts
	.4byte Route19_MapConnections
	.2byte MUS_ROUTE3
	.2byte LAYOUT_ROUTE19
	.byte MAPSEC_ROUTE_19
	.byte FALSE
	.byte WEATHER_SUNNY
	.byte MAP_TYPE_ROUTE
	map_header_flags allow_cycling=TRUE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/Route19/header.inc =====
@ ===== BEGIN data/maps/Route20/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route20/map.json
@

Route20:
	.4byte Route20_Layout
	.4byte Route20_MapEvents
	.4byte Route20_MapScripts
	.4byte Route20_MapConnections
	.2byte MUS_ROUTE3
	.2byte LAYOUT_ROUTE20
	.byte MAPSEC_ROUTE_20
	.byte FALSE
	.byte WEATHER_SUNNY
	.byte MAP_TYPE_ROUTE
	map_header_flags allow_cycling=TRUE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/Route20/header.inc =====
@ ===== BEGIN data/maps/Route21_North/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route21_North/map.json
@

Route21_North:
	.4byte Route21_North_Layout
	.4byte Route21_North_MapEvents
	.4byte Route21_North_MapScripts
	.4byte Route21_North_MapConnections
	.2byte MUS_ROUTE3
	.2byte LAYOUT_ROUTE21_NORTH
	.byte MAPSEC_ROUTE_21
	.byte FALSE
	.byte WEATHER_SUNNY
	.byte MAP_TYPE_ROUTE
	map_header_flags allow_cycling=TRUE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/Route21_North/header.inc =====
@ ===== BEGIN data/maps/Route21_South/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route21_South/map.json
@

Route21_South:
	.4byte Route21_South_Layout
	.4byte Route21_South_MapEvents
	.4byte Route21_South_MapScripts
	.4byte Route21_South_MapConnections
	.2byte MUS_ROUTE3
	.2byte LAYOUT_ROUTE21_SOUTH
	.byte MAPSEC_ROUTE_21
	.byte FALSE
	.byte WEATHER_SUNNY
	.byte MAP_TYPE_ROUTE
	map_header_flags allow_cycling=TRUE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/Route21_South/header.inc =====
@ ===== BEGIN data/maps/Route22/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route22/map.json
@

Route22:
	.4byte Route22_Layout
	.4byte Route22_MapEvents
	.4byte Route22_MapScripts
	.4byte Route22_MapConnections
	.2byte MUS_ROUTE3
	.2byte LAYOUT_ROUTE22
	.byte MAPSEC_ROUTE_22
	.byte FALSE
	.byte WEATHER_SUNNY
	.byte MAP_TYPE_ROUTE
	map_header_flags allow_cycling=TRUE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/Route22/header.inc =====
@ ===== BEGIN data/maps/Route23/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route23/map.json
@

Route23:
	.4byte Route23_Layout
	.4byte Route23_MapEvents
	.4byte Route23_MapScripts
	.4byte Route23_MapConnections
	.2byte MUS_VICTORY_ROAD
	.2byte LAYOUT_ROUTE23
	.byte MAPSEC_ROUTE_23
	.byte FALSE
	.byte WEATHER_SUNNY
	.byte MAP_TYPE_ROUTE
	map_header_flags allow_cycling=TRUE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/Route23/header.inc =====
@ ===== BEGIN data/maps/Route24/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route24/map.json
@

Route24:
	.4byte Route24_Layout
	.4byte Route24_MapEvents
	.4byte Route24_MapScripts
	.4byte Route24_MapConnections
	.2byte MUS_ROUTE24
	.2byte LAYOUT_ROUTE24
	.byte MAPSEC_ROUTE_24
	.byte FALSE
	.byte WEATHER_SUNNY
	.byte MAP_TYPE_ROUTE
	map_header_flags allow_cycling=TRUE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/Route24/header.inc =====
@ ===== BEGIN data/maps/Route25/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route25/map.json
@

Route25:
	.4byte Route25_Layout
	.4byte Route25_MapEvents
	.4byte Route25_MapScripts
	.4byte Route25_MapConnections
	.2byte MUS_ROUTE24
	.2byte LAYOUT_ROUTE25
	.byte MAPSEC_ROUTE_25
	.byte FALSE
	.byte WEATHER_SUNNY
	.byte MAP_TYPE_ROUTE
	map_header_flags allow_cycling=TRUE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/Route25/header.inc =====
@ ===== BEGIN data/maps/OneIsland_KindleRoad/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/OneIsland_KindleRoad/map.json
@

OneIsland_KindleRoad:
	.4byte OneIsland_KindleRoad_Layout
	.4byte OneIsland_KindleRoad_MapEvents
	.4byte OneIsland_KindleRoad_MapScripts
	.4byte OneIsland_KindleRoad_MapConnections
	.2byte MUS_ROUTE3
	.2byte LAYOUT_ONE_ISLAND_KINDLE_ROAD
	.byte MAPSEC_KINDLE_ROAD
	.byte FALSE
	.byte WEATHER_SUNNY
	.byte MAP_TYPE_ROUTE
	map_header_flags allow_cycling=TRUE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/OneIsland_KindleRoad/header.inc =====
@ ===== BEGIN data/maps/OneIsland_TreasureBeach/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/OneIsland_TreasureBeach/map.json
@

OneIsland_TreasureBeach:
	.4byte OneIsland_TreasureBeach_Layout
	.4byte OneIsland_TreasureBeach_MapEvents
	.4byte OneIsland_TreasureBeach_MapScripts
	.4byte OneIsland_TreasureBeach_MapConnections
	.2byte MUS_ROUTE3
	.2byte LAYOUT_ONE_ISLAND_TREASURE_BEACH
	.byte MAPSEC_TREASURE_BEACH
	.byte FALSE
	.byte WEATHER_SUNNY
	.byte MAP_TYPE_ROUTE
	map_header_flags allow_cycling=TRUE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/OneIsland_TreasureBeach/header.inc =====
@ ===== BEGIN data/maps/TwoIsland_CapeBrink/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/TwoIsland_CapeBrink/map.json
@

TwoIsland_CapeBrink:
	.4byte TwoIsland_CapeBrink_Layout
	.4byte TwoIsland_CapeBrink_MapEvents
	.4byte TwoIsland_CapeBrink_MapScripts
	.4byte TwoIsland_CapeBrink_MapConnections
	.2byte MUS_ROUTE3
	.2byte LAYOUT_TWO_ISLAND_CAPE_BRINK
	.byte MAPSEC_CAPE_BRINK
	.byte FALSE
	.byte WEATHER_SUNNY
	.byte MAP_TYPE_ROUTE
	map_header_flags allow_cycling=TRUE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/TwoIsland_CapeBrink/header.inc =====
@ ===== BEGIN data/maps/ThreeIsland_BondBridge/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/ThreeIsland_BondBridge/map.json
@

ThreeIsland_BondBridge:
	.4byte ThreeIsland_BondBridge_Layout
	.4byte ThreeIsland_BondBridge_MapEvents
	.4byte ThreeIsland_BondBridge_MapScripts
	.4byte ThreeIsland_BondBridge_MapConnections
	.2byte MUS_ROUTE3
	.2byte LAYOUT_THREE_ISLAND_BOND_BRIDGE
	.byte MAPSEC_BOND_BRIDGE
	.byte FALSE
	.byte WEATHER_SUNNY
	.byte MAP_TYPE_ROUTE
	map_header_flags allow_cycling=TRUE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/ThreeIsland_BondBridge/header.inc =====
@ ===== BEGIN data/maps/ThreeIsland_Port/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/ThreeIsland_Port/map.json
@

ThreeIsland_Port:
	.4byte ThreeIsland_Port_Layout
	.4byte ThreeIsland_Port_MapEvents
	.4byte ThreeIsland_Port_MapScripts
	.4byte ThreeIsland_Port_MapConnections
	.2byte MUS_ROUTE3
	.2byte LAYOUT_THREE_ISLAND_PORT
	.byte MAPSEC_THREE_ISLE_PORT
	.byte FALSE
	.byte WEATHER_SUNNY
	.byte MAP_TYPE_ROUTE
	map_header_flags allow_cycling=TRUE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/ThreeIsland_Port/header.inc =====
@ ===== BEGIN data/maps/Prototype_SeviiIsle_6/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Prototype_SeviiIsle_6/map.json
@

Prototype_SeviiIsle_6:
	.4byte Prototype_SeviiIsle_6_Layout
	.4byte Prototype_SeviiIsle_6_MapEvents
	.4byte Prototype_SeviiIsle_6_MapScripts
	.4byte Prototype_SeviiIsle_6_MapConnections
	.2byte MUS_SEVII_ROUTE
	.2byte LAYOUT_PROTOTYPE_SEVII_ISLE_6
	.byte MAPSEC_SEVII_ISLE_6
	.byte FALSE
	.byte WEATHER_SUNNY
	.byte MAP_TYPE_ROUTE
	map_header_flags allow_cycling=TRUE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/Prototype_SeviiIsle_6/header.inc =====
@ ===== BEGIN data/maps/Prototype_SeviiIsle_7/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Prototype_SeviiIsle_7/map.json
@

Prototype_SeviiIsle_7:
	.4byte Prototype_SeviiIsle_7_Layout
	.4byte Prototype_SeviiIsle_7_MapEvents
	.4byte Prototype_SeviiIsle_7_MapScripts
	.4byte Prototype_SeviiIsle_7_MapConnections
	.2byte MUS_SEVII_ROUTE
	.2byte LAYOUT_PROTOTYPE_SEVII_ISLE_7
	.byte MAPSEC_SEVII_ISLE_7
	.byte FALSE
	.byte WEATHER_SUNNY
	.byte MAP_TYPE_ROUTE
	map_header_flags allow_cycling=TRUE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/Prototype_SeviiIsle_7/header.inc =====
@ ===== BEGIN data/maps/Prototype_SeviiIsle_8/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Prototype_SeviiIsle_8/map.json
@

Prototype_SeviiIsle_8:
	.4byte Prototype_SeviiIsle_8_Layout
	.4byte Prototype_SeviiIsle_8_MapEvents
	.4byte Prototype_SeviiIsle_8_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_ROUTE
	.2byte LAYOUT_PROTOTYPE_SEVII_ISLE_8
	.byte MAPSEC_SEVII_ISLE_8
	.byte FALSE
	.byte WEATHER_SUNNY
	.byte MAP_TYPE_ROUTE
	map_header_flags allow_cycling=TRUE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/Prototype_SeviiIsle_8/header.inc =====
@ ===== BEGIN data/maps/Prototype_SeviiIsle_9/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Prototype_SeviiIsle_9/map.json
@

Prototype_SeviiIsle_9:
	.4byte Prototype_SeviiIsle_9_Layout
	.4byte Prototype_SeviiIsle_9_MapEvents
	.4byte Prototype_SeviiIsle_9_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_ROUTE
	.2byte LAYOUT_PROTOTYPE_SEVII_ISLE_9
	.byte MAPSEC_SEVII_ISLE_9
	.byte FALSE
	.byte WEATHER_SUNNY
	.byte MAP_TYPE_ROUTE
	map_header_flags allow_cycling=TRUE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/Prototype_SeviiIsle_9/header.inc =====
@ ===== BEGIN data/maps/FiveIsland_ResortGorgeous/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FiveIsland_ResortGorgeous/map.json
@

FiveIsland_ResortGorgeous:
	.4byte FiveIsland_ResortGorgeous_Layout
	.4byte FiveIsland_ResortGorgeous_MapEvents
	.4byte FiveIsland_ResortGorgeous_MapScripts
	.4byte FiveIsland_ResortGorgeous_MapConnections
	.2byte MUS_SEVII_ROUTE
	.2byte LAYOUT_FIVE_ISLAND_RESORT_GORGEOUS
	.byte MAPSEC_RESORT_GORGEOUS
	.byte FALSE
	.byte WEATHER_SUNNY
	.byte MAP_TYPE_ROUTE
	map_header_flags allow_cycling=TRUE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/FiveIsland_ResortGorgeous/header.inc =====
@ ===== BEGIN data/maps/FiveIsland_WaterLabyrinth/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FiveIsland_WaterLabyrinth/map.json
@

FiveIsland_WaterLabyrinth:
	.4byte FiveIsland_WaterLabyrinth_Layout
	.4byte FiveIsland_WaterLabyrinth_MapEvents
	.4byte FiveIsland_WaterLabyrinth_MapScripts
	.4byte FiveIsland_WaterLabyrinth_MapConnections
	.2byte MUS_SEVII_ROUTE
	.2byte LAYOUT_FIVE_ISLAND_WATER_LABYRINTH
	.byte MAPSEC_WATER_LABYRINTH
	.byte FALSE
	.byte WEATHER_SUNNY
	.byte MAP_TYPE_ROUTE
	map_header_flags allow_cycling=TRUE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/FiveIsland_WaterLabyrinth/header.inc =====
@ ===== BEGIN data/maps/FiveIsland_Meadow/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FiveIsland_Meadow/map.json
@

FiveIsland_Meadow:
	.4byte FiveIsland_Meadow_Layout
	.4byte FiveIsland_Meadow_MapEvents
	.4byte FiveIsland_Meadow_MapScripts
	.4byte FiveIsland_Meadow_MapConnections
	.2byte MUS_SEVII_ROUTE
	.2byte LAYOUT_FIVE_ISLAND_MEADOW
	.byte MAPSEC_FIVE_ISLE_MEADOW
	.byte FALSE
	.byte WEATHER_SUNNY
	.byte MAP_TYPE_ROUTE
	map_header_flags allow_cycling=TRUE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/FiveIsland_Meadow/header.inc =====
@ ===== BEGIN data/maps/FiveIsland_MemorialPillar/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FiveIsland_MemorialPillar/map.json
@

FiveIsland_MemorialPillar:
	.4byte FiveIsland_MemorialPillar_Layout
	.4byte FiveIsland_MemorialPillar_MapEvents
	.4byte FiveIsland_MemorialPillar_MapScripts
	.4byte FiveIsland_MemorialPillar_MapConnections
	.2byte MUS_SEVII_ROUTE
	.2byte LAYOUT_FIVE_ISLAND_MEMORIAL_PILLAR
	.byte MAPSEC_MEMORIAL_PILLAR
	.byte FALSE
	.byte WEATHER_SUNNY
	.byte MAP_TYPE_ROUTE
	map_header_flags allow_cycling=TRUE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/FiveIsland_MemorialPillar/header.inc =====
@ ===== BEGIN data/maps/SixIsland_OutcastIsland/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SixIsland_OutcastIsland/map.json
@

SixIsland_OutcastIsland:
	.4byte SixIsland_OutcastIsland_Layout
	.4byte SixIsland_OutcastIsland_MapEvents
	.4byte SixIsland_OutcastIsland_MapScripts
	.4byte SixIsland_OutcastIsland_MapConnections
	.2byte MUS_SEVII_ROUTE
	.2byte LAYOUT_SIX_ISLAND_OUTCAST_ISLAND
	.byte MAPSEC_OUTCAST_ISLAND
	.byte FALSE
	.byte WEATHER_SUNNY
	.byte MAP_TYPE_ROUTE
	map_header_flags allow_cycling=TRUE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SixIsland_OutcastIsland/header.inc =====
@ ===== BEGIN data/maps/SixIsland_GreenPath/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SixIsland_GreenPath/map.json
@

SixIsland_GreenPath:
	.4byte SixIsland_GreenPath_Layout
	.4byte SixIsland_GreenPath_MapEvents
	.4byte SixIsland_GreenPath_MapScripts
	.4byte SixIsland_GreenPath_MapConnections
	.2byte MUS_SEVII_ROUTE
	.2byte LAYOUT_SIX_ISLAND_GREEN_PATH
	.byte MAPSEC_GREEN_PATH
	.byte FALSE
	.byte WEATHER_SUNNY
	.byte MAP_TYPE_ROUTE
	map_header_flags allow_cycling=TRUE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SixIsland_GreenPath/header.inc =====
@ ===== BEGIN data/maps/SixIsland_WaterPath/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SixIsland_WaterPath/map.json
@

SixIsland_WaterPath:
	.4byte SixIsland_WaterPath_Layout
	.4byte SixIsland_WaterPath_MapEvents
	.4byte SixIsland_WaterPath_MapScripts
	.4byte SixIsland_WaterPath_MapConnections
	.2byte MUS_SEVII_ROUTE
	.2byte LAYOUT_SIX_ISLAND_WATER_PATH
	.byte MAPSEC_WATER_PATH
	.byte FALSE
	.byte WEATHER_SUNNY
	.byte MAP_TYPE_ROUTE
	map_header_flags allow_cycling=TRUE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SixIsland_WaterPath/header.inc =====
@ ===== BEGIN data/maps/SixIsland_RuinValley/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SixIsland_RuinValley/map.json
@

SixIsland_RuinValley:
	.4byte SixIsland_RuinValley_Layout
	.4byte SixIsland_RuinValley_MapEvents
	.4byte SixIsland_RuinValley_MapScripts
	.4byte SixIsland_RuinValley_MapConnections
	.2byte MUS_SEVII_ROUTE
	.2byte LAYOUT_SIX_ISLAND_RUIN_VALLEY
	.byte MAPSEC_RUIN_VALLEY
	.byte FALSE
	.byte WEATHER_SUNNY
	.byte MAP_TYPE_ROUTE
	map_header_flags allow_cycling=TRUE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SixIsland_RuinValley/header.inc =====
@ ===== BEGIN data/maps/SevenIsland_TrainerTower/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SevenIsland_TrainerTower/map.json
@

SevenIsland_TrainerTower:
	.4byte SevenIsland_TrainerTower_Layout
	.4byte SevenIsland_TrainerTower_MapEvents
	.4byte SevenIsland_TrainerTower_MapScripts
	.4byte SevenIsland_TrainerTower_MapConnections
	.2byte MUS_SEVII_ROUTE
	.2byte LAYOUT_SEVEN_ISLAND_TRAINER_TOWER
	.byte MAPSEC_TRAINER_TOWER
	.byte FALSE
	.byte WEATHER_SUNNY
	.byte MAP_TYPE_ROUTE
	map_header_flags allow_cycling=TRUE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SevenIsland_TrainerTower/header.inc =====
@ ===== BEGIN data/maps/SevenIsland_SevaultCanyon_Entrance/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SevenIsland_SevaultCanyon_Entrance/map.json
@

SevenIsland_SevaultCanyon_Entrance:
	.4byte SevenIsland_SevaultCanyon_Entrance_Layout
	.4byte SevenIsland_SevaultCanyon_Entrance_MapEvents
	.4byte SevenIsland_SevaultCanyon_Entrance_MapScripts
	.4byte SevenIsland_SevaultCanyon_Entrance_MapConnections
	.2byte MUS_SEVII_ROUTE
	.2byte LAYOUT_SEVEN_ISLAND_SEVAULT_CANYON_ENTRANCE
	.byte MAPSEC_CANYON_ENTRANCE
	.byte FALSE
	.byte WEATHER_SUNNY
	.byte MAP_TYPE_ROUTE
	map_header_flags allow_cycling=TRUE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SevenIsland_SevaultCanyon_Entrance/header.inc =====
@ ===== BEGIN data/maps/SevenIsland_SevaultCanyon/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SevenIsland_SevaultCanyon/map.json
@

SevenIsland_SevaultCanyon:
	.4byte SevenIsland_SevaultCanyon_Layout
	.4byte SevenIsland_SevaultCanyon_MapEvents
	.4byte SevenIsland_SevaultCanyon_MapScripts
	.4byte SevenIsland_SevaultCanyon_MapConnections
	.2byte MUS_SEVII_ROUTE
	.2byte LAYOUT_SEVEN_ISLAND_SEVAULT_CANYON
	.byte MAPSEC_SEVAULT_CANYON
	.byte FALSE
	.byte WEATHER_SUNNY
	.byte MAP_TYPE_ROUTE
	map_header_flags allow_cycling=TRUE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SevenIsland_SevaultCanyon/header.inc =====
@ ===== BEGIN data/maps/SevenIsland_TanobyRuins/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SevenIsland_TanobyRuins/map.json
@

SevenIsland_TanobyRuins:
	.4byte SevenIsland_TanobyRuins_Layout
	.4byte SevenIsland_TanobyRuins_MapEvents
	.4byte SevenIsland_TanobyRuins_MapScripts
	.4byte SevenIsland_TanobyRuins_MapConnections
	.2byte MUS_SEVII_ROUTE
	.2byte LAYOUT_SEVEN_ISLAND_TANOBY_RUINS
	.byte MAPSEC_TANOBY_RUINS
	.byte FALSE
	.byte WEATHER_SUNNY
	.byte MAP_TYPE_ROUTE
	map_header_flags allow_cycling=TRUE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=TRUE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SevenIsland_TanobyRuins/header.inc =====
@ ===== BEGIN data/maps/PalletTown_PlayersHouse_1F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/PalletTown_PlayersHouse_1F/map.json
@

PalletTown_PlayersHouse_1F:
	.4byte PalletTown_PlayersHouse_1F_Layout
	.4byte PalletTown_PlayersHouse_1F_MapEvents
	.4byte PalletTown_PlayersHouse_1F_MapScripts
	.4byte NULL
	.2byte MUS_PALLET
	.2byte LAYOUT_PALLET_TOWN_PLAYERS_HOUSE_1F
	.byte MAPSEC_PALLET_TOWN
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/PalletTown_PlayersHouse_1F/header.inc =====
@ ===== BEGIN data/maps/PalletTown_PlayersHouse_2F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/PalletTown_PlayersHouse_2F/map.json
@

PalletTown_PlayersHouse_2F:
	.4byte PalletTown_PlayersHouse_2F_Layout
	.4byte PalletTown_PlayersHouse_2F_MapEvents
	.4byte PalletTown_PlayersHouse_2F_MapScripts
	.4byte NULL
	.2byte MUS_PALLET
	.2byte LAYOUT_PALLET_TOWN_PLAYERS_HOUSE_2F
	.byte MAPSEC_PALLET_TOWN
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/PalletTown_PlayersHouse_2F/header.inc =====
@ ===== BEGIN data/maps/PalletTown_RivalsHouse/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/PalletTown_RivalsHouse/map.json
@

PalletTown_RivalsHouse:
	.4byte PalletTown_RivalsHouse_Layout
	.4byte PalletTown_RivalsHouse_MapEvents
	.4byte PalletTown_RivalsHouse_MapScripts
	.4byte NULL
	.2byte MUS_PALLET
	.2byte LAYOUT_PALLET_TOWN_RIVALS_HOUSE
	.byte MAPSEC_PALLET_TOWN
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/PalletTown_RivalsHouse/header.inc =====
@ ===== BEGIN data/maps/PalletTown_ProfessorOaksLab/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/PalletTown_ProfessorOaksLab/map.json
@

PalletTown_ProfessorOaksLab:
	.4byte PalletTown_ProfessorOaksLab_Layout
	.4byte PalletTown_ProfessorOaksLab_MapEvents
	.4byte PalletTown_ProfessorOaksLab_MapScripts
	.4byte NULL
	.2byte MUS_OAK_LAB
	.2byte LAYOUT_PALLET_TOWN_PROFESSOR_OAKS_LAB
	.byte MAPSEC_PALLET_TOWN
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/PalletTown_ProfessorOaksLab/header.inc =====
@ ===== BEGIN data/maps/ViridianCity_House/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/ViridianCity_House/map.json
@

ViridianCity_House:
	.4byte ViridianCity_House_Layout
	.4byte ViridianCity_House_MapEvents
	.4byte ViridianCity_House_MapScripts
	.4byte NULL
	.2byte MUS_PEWTER
	.2byte LAYOUT_VIRIDIAN_CITY_HOUSE
	.byte MAPSEC_VIRIDIAN_CITY
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/ViridianCity_House/header.inc =====
@ ===== BEGIN data/maps/ViridianCity_Gym/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/ViridianCity_Gym/map.json
@

ViridianCity_Gym:
	.4byte ViridianCity_Gym_Layout
	.4byte ViridianCity_Gym_MapEvents
	.4byte ViridianCity_Gym_MapScripts
	.4byte NULL
	.2byte MUS_GYM
	.2byte LAYOUT_VIRIDIAN_CITY_GYM
	.byte MAPSEC_VIRIDIAN_CITY
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_GYM

@ ===== END data/maps/ViridianCity_Gym/header.inc =====
@ ===== BEGIN data/maps/ViridianCity_School/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/ViridianCity_School/map.json
@

ViridianCity_School:
	.4byte ViridianCity_School_Layout
	.4byte ViridianCity_School_MapEvents
	.4byte ViridianCity_School_MapScripts
	.4byte NULL
	.2byte MUS_PEWTER
	.2byte LAYOUT_VIRIDIAN_CITY_SCHOOL
	.byte MAPSEC_VIRIDIAN_CITY
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/ViridianCity_School/header.inc =====
@ ===== BEGIN data/maps/ViridianCity_Mart/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/ViridianCity_Mart/map.json
@

ViridianCity_Mart:
	.4byte Mart_Layout
	.4byte ViridianCity_Mart_MapEvents
	.4byte ViridianCity_Mart_MapScripts
	.4byte NULL
	.2byte MUS_POKE_CENTER
	.2byte LAYOUT_MART
	.byte MAPSEC_VIRIDIAN_CITY
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/ViridianCity_Mart/header.inc =====
@ ===== BEGIN data/maps/ViridianCity_PokemonCenter_1F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/ViridianCity_PokemonCenter_1F/map.json
@

ViridianCity_PokemonCenter_1F:
	.4byte PokemonCenter_1F_Layout
	.4byte ViridianCity_PokemonCenter_1F_MapEvents
	.4byte ViridianCity_PokemonCenter_1F_MapScripts
	.4byte NULL
	.2byte MUS_POKE_CENTER
	.2byte LAYOUT_POKEMON_CENTER_1F
	.byte MAPSEC_VIRIDIAN_CITY
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/ViridianCity_PokemonCenter_1F/header.inc =====
@ ===== BEGIN data/maps/ViridianCity_PokemonCenter_2F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/ViridianCity_PokemonCenter_2F/map.json
@

ViridianCity_PokemonCenter_2F:
	.4byte PokemonCenter_2F_Layout
	.4byte ViridianCity_PokemonCenter_2F_MapEvents
	.4byte ViridianCity_PokemonCenter_2F_MapScripts
	.4byte NULL
	.2byte MUS_POKE_CENTER
	.2byte LAYOUT_POKEMON_CENTER_2F
	.byte MAPSEC_VIRIDIAN_CITY
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/ViridianCity_PokemonCenter_2F/header.inc =====
@ ===== BEGIN data/maps/PewterCity_Museum_1F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/PewterCity_Museum_1F/map.json
@

PewterCity_Museum_1F:
	.4byte PewterCity_Museum_1F_Layout
	.4byte PewterCity_Museum_1F_MapEvents
	.4byte PewterCity_Museum_1F_MapScripts
	.4byte NULL
	.2byte MUS_PEWTER
	.2byte LAYOUT_PEWTER_CITY_MUSEUM_1F
	.byte MAPSEC_PEWTER_CITY
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/PewterCity_Museum_1F/header.inc =====
@ ===== BEGIN data/maps/PewterCity_Museum_2F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/PewterCity_Museum_2F/map.json
@

PewterCity_Museum_2F:
	.4byte PewterCity_Museum_2F_Layout
	.4byte PewterCity_Museum_2F_MapEvents
	.4byte PewterCity_Museum_2F_MapScripts
	.4byte NULL
	.2byte MUS_PEWTER
	.2byte LAYOUT_PEWTER_CITY_MUSEUM_2F
	.byte MAPSEC_PEWTER_CITY
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/PewterCity_Museum_2F/header.inc =====
@ ===== BEGIN data/maps/PewterCity_Gym/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/PewterCity_Gym/map.json
@

PewterCity_Gym:
	.4byte PewterCity_Gym_Layout
	.4byte PewterCity_Gym_MapEvents
	.4byte PewterCity_Gym_MapScripts
	.4byte NULL
	.2byte MUS_GYM
	.2byte LAYOUT_PEWTER_CITY_GYM
	.byte MAPSEC_PEWTER_CITY
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_GYM

@ ===== END data/maps/PewterCity_Gym/header.inc =====
@ ===== BEGIN data/maps/PewterCity_Mart/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/PewterCity_Mart/map.json
@

PewterCity_Mart:
	.4byte Mart_Layout
	.4byte PewterCity_Mart_MapEvents
	.4byte PewterCity_Mart_MapScripts
	.4byte NULL
	.2byte MUS_POKE_CENTER
	.2byte LAYOUT_MART
	.byte MAPSEC_PEWTER_CITY
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/PewterCity_Mart/header.inc =====
@ ===== BEGIN data/maps/PewterCity_House1/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/PewterCity_House1/map.json
@

PewterCity_House1:
	.4byte House2_Layout
	.4byte PewterCity_House1_MapEvents
	.4byte PewterCity_House1_MapScripts
	.4byte NULL
	.2byte MUS_PEWTER
	.2byte LAYOUT_HOUSE2
	.byte MAPSEC_PEWTER_CITY
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/PewterCity_House1/header.inc =====
@ ===== BEGIN data/maps/PewterCity_PokemonCenter_1F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/PewterCity_PokemonCenter_1F/map.json
@

PewterCity_PokemonCenter_1F:
	.4byte PokemonCenter_1F_Layout
	.4byte PewterCity_PokemonCenter_1F_MapEvents
	.4byte PewterCity_PokemonCenter_1F_MapScripts
	.4byte NULL
	.2byte MUS_POKE_CENTER
	.2byte LAYOUT_POKEMON_CENTER_1F
	.byte MAPSEC_PEWTER_CITY
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/PewterCity_PokemonCenter_1F/header.inc =====
@ ===== BEGIN data/maps/PewterCity_PokemonCenter_2F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/PewterCity_PokemonCenter_2F/map.json
@

PewterCity_PokemonCenter_2F:
	.4byte PokemonCenter_2F_Layout
	.4byte PewterCity_PokemonCenter_2F_MapEvents
	.4byte PewterCity_PokemonCenter_2F_MapScripts
	.4byte NULL
	.2byte MUS_POKE_CENTER
	.2byte LAYOUT_POKEMON_CENTER_2F
	.byte MAPSEC_PEWTER_CITY
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/PewterCity_PokemonCenter_2F/header.inc =====
@ ===== BEGIN data/maps/PewterCity_House2/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/PewterCity_House2/map.json
@

PewterCity_House2:
	.4byte House2_Layout
	.4byte PewterCity_House2_MapEvents
	.4byte PewterCity_House2_MapScripts
	.4byte NULL
	.2byte MUS_PEWTER
	.2byte LAYOUT_HOUSE2
	.byte MAPSEC_PEWTER_CITY
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/PewterCity_House2/header.inc =====
@ ===== BEGIN data/maps/CeruleanCity_House1/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/CeruleanCity_House1/map.json
@

CeruleanCity_House1:
	.4byte CeruleanCity_House1_Layout
	.4byte CeruleanCity_House1_MapEvents
	.4byte CeruleanCity_House1_MapScripts
	.4byte NULL
	.2byte MUS_FUCHSIA
	.2byte LAYOUT_CERULEAN_CITY_HOUSE1
	.byte MAPSEC_CERULEAN_CITY
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/CeruleanCity_House1/header.inc =====
@ ===== BEGIN data/maps/CeruleanCity_House2/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/CeruleanCity_House2/map.json
@

CeruleanCity_House2:
	.4byte CeruleanCity_House2_Layout
	.4byte CeruleanCity_House2_MapEvents
	.4byte CeruleanCity_House2_MapScripts
	.4byte NULL
	.2byte MUS_FUCHSIA
	.2byte LAYOUT_CERULEAN_CITY_HOUSE2
	.byte MAPSEC_CERULEAN_CITY
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/CeruleanCity_House2/header.inc =====
@ ===== BEGIN data/maps/CeruleanCity_House3/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/CeruleanCity_House3/map.json
@

CeruleanCity_House3:
	.4byte House1_Layout
	.4byte CeruleanCity_House3_MapEvents
	.4byte CeruleanCity_House3_MapScripts
	.4byte NULL
	.2byte MUS_FUCHSIA
	.2byte LAYOUT_HOUSE1
	.byte MAPSEC_CERULEAN_CITY
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/CeruleanCity_House3/header.inc =====
@ ===== BEGIN data/maps/CeruleanCity_PokemonCenter_1F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/CeruleanCity_PokemonCenter_1F/map.json
@

CeruleanCity_PokemonCenter_1F:
	.4byte PokemonCenter_1F_Layout
	.4byte CeruleanCity_PokemonCenter_1F_MapEvents
	.4byte CeruleanCity_PokemonCenter_1F_MapScripts
	.4byte NULL
	.2byte MUS_POKE_CENTER
	.2byte LAYOUT_POKEMON_CENTER_1F
	.byte MAPSEC_CERULEAN_CITY
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/CeruleanCity_PokemonCenter_1F/header.inc =====
@ ===== BEGIN data/maps/CeruleanCity_PokemonCenter_2F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/CeruleanCity_PokemonCenter_2F/map.json
@

CeruleanCity_PokemonCenter_2F:
	.4byte PokemonCenter_2F_Layout
	.4byte CeruleanCity_PokemonCenter_2F_MapEvents
	.4byte CeruleanCity_PokemonCenter_2F_MapScripts
	.4byte NULL
	.2byte MUS_POKE_CENTER
	.2byte LAYOUT_POKEMON_CENTER_2F
	.byte MAPSEC_CERULEAN_CITY
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/CeruleanCity_PokemonCenter_2F/header.inc =====
@ ===== BEGIN data/maps/CeruleanCity_Gym/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/CeruleanCity_Gym/map.json
@

CeruleanCity_Gym:
	.4byte CeruleanCity_Gym_Layout
	.4byte CeruleanCity_Gym_MapEvents
	.4byte CeruleanCity_Gym_MapScripts
	.4byte NULL
	.2byte MUS_GYM
	.2byte LAYOUT_CERULEAN_CITY_GYM
	.byte MAPSEC_CERULEAN_CITY
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_GYM

@ ===== END data/maps/CeruleanCity_Gym/header.inc =====
@ ===== BEGIN data/maps/CeruleanCity_BikeShop/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/CeruleanCity_BikeShop/map.json
@

CeruleanCity_BikeShop:
	.4byte CeruleanCity_BikeShop_Layout
	.4byte CeruleanCity_BikeShop_MapEvents
	.4byte CeruleanCity_BikeShop_MapScripts
	.4byte NULL
	.2byte MUS_FUCHSIA
	.2byte LAYOUT_CERULEAN_CITY_BIKE_SHOP
	.byte MAPSEC_CERULEAN_CITY
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/CeruleanCity_BikeShop/header.inc =====
@ ===== BEGIN data/maps/CeruleanCity_Mart/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/CeruleanCity_Mart/map.json
@

CeruleanCity_Mart:
	.4byte Mart_Layout
	.4byte CeruleanCity_Mart_MapEvents
	.4byte CeruleanCity_Mart_MapScripts
	.4byte NULL
	.2byte MUS_POKE_CENTER
	.2byte LAYOUT_MART
	.byte MAPSEC_CERULEAN_CITY
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/CeruleanCity_Mart/header.inc =====
@ ===== BEGIN data/maps/CeruleanCity_House4/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/CeruleanCity_House4/map.json
@

CeruleanCity_House4:
	.4byte House1_Layout
	.4byte CeruleanCity_House4_MapEvents
	.4byte CeruleanCity_House4_MapScripts
	.4byte NULL
	.2byte MUS_FUCHSIA
	.2byte LAYOUT_HOUSE1
	.byte MAPSEC_CERULEAN_CITY
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/CeruleanCity_House4/header.inc =====
@ ===== BEGIN data/maps/CeruleanCity_House5/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/CeruleanCity_House5/map.json
@

CeruleanCity_House5:
	.4byte CeruleanCity_House5_Layout
	.4byte CeruleanCity_House5_MapEvents
	.4byte CeruleanCity_House5_MapScripts
	.4byte NULL
	.2byte MUS_FUCHSIA
	.2byte LAYOUT_CERULEAN_CITY_HOUSE5
	.byte MAPSEC_CERULEAN_CITY
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/CeruleanCity_House5/header.inc =====
@ ===== BEGIN data/maps/LavenderTown_PokemonCenter_1F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/LavenderTown_PokemonCenter_1F/map.json
@

LavenderTown_PokemonCenter_1F:
	.4byte PokemonCenter_1F_Layout
	.4byte LavenderTown_PokemonCenter_1F_MapEvents
	.4byte LavenderTown_PokemonCenter_1F_MapScripts
	.4byte NULL
	.2byte MUS_POKE_CENTER
	.2byte LAYOUT_POKEMON_CENTER_1F
	.byte MAPSEC_LAVENDER_TOWN
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/LavenderTown_PokemonCenter_1F/header.inc =====
@ ===== BEGIN data/maps/LavenderTown_PokemonCenter_2F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/LavenderTown_PokemonCenter_2F/map.json
@

LavenderTown_PokemonCenter_2F:
	.4byte PokemonCenter_2F_Layout
	.4byte LavenderTown_PokemonCenter_2F_MapEvents
	.4byte LavenderTown_PokemonCenter_2F_MapScripts
	.4byte NULL
	.2byte MUS_POKE_CENTER
	.2byte LAYOUT_POKEMON_CENTER_2F
	.byte MAPSEC_LAVENDER_TOWN
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/LavenderTown_PokemonCenter_2F/header.inc =====
@ ===== BEGIN data/maps/LavenderTown_VolunteerPokemonHouse/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/LavenderTown_VolunteerPokemonHouse/map.json
@

LavenderTown_VolunteerPokemonHouse:
	.4byte LavenderTown_VolunteerPokemonHouse_Layout
	.4byte LavenderTown_VolunteerPokemonHouse_MapEvents
	.4byte LavenderTown_VolunteerPokemonHouse_MapScripts
	.4byte NULL
	.2byte MUS_LAVENDER
	.2byte LAYOUT_LAVENDER_TOWN_VOLUNTEER_POKEMON_HOUSE
	.byte MAPSEC_LAVENDER_TOWN
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/LavenderTown_VolunteerPokemonHouse/header.inc =====
@ ===== BEGIN data/maps/LavenderTown_House1/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/LavenderTown_House1/map.json
@

LavenderTown_House1:
	.4byte House5_Layout
	.4byte LavenderTown_House1_MapEvents
	.4byte LavenderTown_House1_MapScripts
	.4byte NULL
	.2byte MUS_LAVENDER
	.2byte LAYOUT_HOUSE5
	.byte MAPSEC_LAVENDER_TOWN
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/LavenderTown_House1/header.inc =====
@ ===== BEGIN data/maps/LavenderTown_House2/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/LavenderTown_House2/map.json
@

LavenderTown_House2:
	.4byte House5_Layout
	.4byte LavenderTown_House2_MapEvents
	.4byte LavenderTown_House2_MapScripts
	.4byte NULL
	.2byte MUS_FUCHSIA
	.2byte LAYOUT_HOUSE5
	.byte MAPSEC_LAVENDER_TOWN
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/LavenderTown_House2/header.inc =====
@ ===== BEGIN data/maps/LavenderTown_Mart/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/LavenderTown_Mart/map.json
@

LavenderTown_Mart:
	.4byte Mart_Layout
	.4byte LavenderTown_Mart_MapEvents
	.4byte LavenderTown_Mart_MapScripts
	.4byte NULL
	.2byte MUS_POKE_CENTER
	.2byte LAYOUT_MART
	.byte MAPSEC_LAVENDER_TOWN
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/LavenderTown_Mart/header.inc =====
@ ===== BEGIN data/maps/VermilionCity_House1/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/VermilionCity_House1/map.json
@

VermilionCity_House1:
	.4byte House1_Layout
	.4byte VermilionCity_House1_MapEvents
	.4byte VermilionCity_House1_MapScripts
	.4byte NULL
	.2byte MUS_FUCHSIA
	.2byte LAYOUT_HOUSE1
	.byte MAPSEC_VERMILION_CITY
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/VermilionCity_House1/header.inc =====
@ ===== BEGIN data/maps/VermilionCity_PokemonCenter_1F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/VermilionCity_PokemonCenter_1F/map.json
@

VermilionCity_PokemonCenter_1F:
	.4byte PokemonCenter_1F_Layout
	.4byte VermilionCity_PokemonCenter_1F_MapEvents
	.4byte VermilionCity_PokemonCenter_1F_MapScripts
	.4byte NULL
	.2byte MUS_POKE_CENTER
	.2byte LAYOUT_POKEMON_CENTER_1F
	.byte MAPSEC_VERMILION_CITY
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/VermilionCity_PokemonCenter_1F/header.inc =====
@ ===== BEGIN data/maps/VermilionCity_PokemonCenter_2F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/VermilionCity_PokemonCenter_2F/map.json
@

VermilionCity_PokemonCenter_2F:
	.4byte PokemonCenter_2F_Layout
	.4byte VermilionCity_PokemonCenter_2F_MapEvents
	.4byte VermilionCity_PokemonCenter_2F_MapScripts
	.4byte NULL
	.2byte MUS_POKE_CENTER
	.2byte LAYOUT_POKEMON_CENTER_2F
	.byte MAPSEC_VERMILION_CITY
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/VermilionCity_PokemonCenter_2F/header.inc =====
@ ===== BEGIN data/maps/VermilionCity_PokemonFanClub/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/VermilionCity_PokemonFanClub/map.json
@

VermilionCity_PokemonFanClub:
	.4byte VermilionCity_PokemonFanClub_Layout
	.4byte VermilionCity_PokemonFanClub_MapEvents
	.4byte VermilionCity_PokemonFanClub_MapScripts
	.4byte NULL
	.2byte MUS_VERMILLION
	.2byte LAYOUT_VERMILION_CITY_POKEMON_FAN_CLUB
	.byte MAPSEC_VERMILION_CITY
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/VermilionCity_PokemonFanClub/header.inc =====
@ ===== BEGIN data/maps/VermilionCity_House2/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/VermilionCity_House2/map.json
@

VermilionCity_House2:
	.4byte House1_Layout
	.4byte VermilionCity_House2_MapEvents
	.4byte VermilionCity_House2_MapScripts
	.4byte NULL
	.2byte MUS_VERMILLION
	.2byte LAYOUT_HOUSE1
	.byte MAPSEC_VERMILION_CITY
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/VermilionCity_House2/header.inc =====
@ ===== BEGIN data/maps/VermilionCity_Mart/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/VermilionCity_Mart/map.json
@

VermilionCity_Mart:
	.4byte Mart_Layout
	.4byte VermilionCity_Mart_MapEvents
	.4byte VermilionCity_Mart_MapScripts
	.4byte NULL
	.2byte MUS_POKE_CENTER
	.2byte LAYOUT_MART
	.byte MAPSEC_VERMILION_CITY
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/VermilionCity_Mart/header.inc =====
@ ===== BEGIN data/maps/VermilionCity_Gym/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/VermilionCity_Gym/map.json
@

VermilionCity_Gym:
	.4byte VermilionCity_Gym_Layout
	.4byte VermilionCity_Gym_MapEvents
	.4byte VermilionCity_Gym_MapScripts
	.4byte NULL
	.2byte MUS_GYM
	.2byte LAYOUT_VERMILION_CITY_GYM
	.byte MAPSEC_VERMILION_CITY
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_GYM

@ ===== END data/maps/VermilionCity_Gym/header.inc =====
@ ===== BEGIN data/maps/VermilionCity_House3/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/VermilionCity_House3/map.json
@

VermilionCity_House3:
	.4byte House1_Layout
	.4byte VermilionCity_House3_MapEvents
	.4byte VermilionCity_House3_MapScripts
	.4byte NULL
	.2byte MUS_VERMILLION
	.2byte LAYOUT_HOUSE1
	.byte MAPSEC_VERMILION_CITY
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/VermilionCity_House3/header.inc =====
@ ===== BEGIN data/maps/CeladonCity_DepartmentStore_1F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/CeladonCity_DepartmentStore_1F/map.json
@

CeladonCity_DepartmentStore_1F:
	.4byte CeladonCity_DepartmentStore_1F_Layout
	.4byte CeladonCity_DepartmentStore_1F_MapEvents
	.4byte CeladonCity_DepartmentStore_1F_MapScripts
	.4byte NULL
	.2byte MUS_POKE_CENTER
	.2byte LAYOUT_CELADON_CITY_DEPARTMENT_STORE_1F
	.byte MAPSEC_CELADON_CITY
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=TRUE
	.byte 1
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/CeladonCity_DepartmentStore_1F/header.inc =====
@ ===== BEGIN data/maps/CeladonCity_DepartmentStore_2F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/CeladonCity_DepartmentStore_2F/map.json
@

CeladonCity_DepartmentStore_2F:
	.4byte CeladonCity_DepartmentStore_2F_Layout
	.4byte CeladonCity_DepartmentStore_2F_MapEvents
	.4byte CeladonCity_DepartmentStore_2F_MapScripts
	.4byte NULL
	.2byte MUS_POKE_CENTER
	.2byte LAYOUT_CELADON_CITY_DEPARTMENT_STORE_2F
	.byte MAPSEC_CELADON_CITY
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=TRUE
	.byte 2
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/CeladonCity_DepartmentStore_2F/header.inc =====
@ ===== BEGIN data/maps/CeladonCity_DepartmentStore_3F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/CeladonCity_DepartmentStore_3F/map.json
@

CeladonCity_DepartmentStore_3F:
	.4byte CeladonCity_DepartmentStore_3F_Layout
	.4byte CeladonCity_DepartmentStore_3F_MapEvents
	.4byte CeladonCity_DepartmentStore_3F_MapScripts
	.4byte NULL
	.2byte MUS_POKE_CENTER
	.2byte LAYOUT_CELADON_CITY_DEPARTMENT_STORE_3F
	.byte MAPSEC_CELADON_CITY
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=TRUE
	.byte 3
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/CeladonCity_DepartmentStore_3F/header.inc =====
@ ===== BEGIN data/maps/CeladonCity_DepartmentStore_4F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/CeladonCity_DepartmentStore_4F/map.json
@

CeladonCity_DepartmentStore_4F:
	.4byte CeladonCity_DepartmentStore_4F_Layout
	.4byte CeladonCity_DepartmentStore_4F_MapEvents
	.4byte CeladonCity_DepartmentStore_4F_MapScripts
	.4byte NULL
	.2byte MUS_POKE_CENTER
	.2byte LAYOUT_CELADON_CITY_DEPARTMENT_STORE_4F
	.byte MAPSEC_CELADON_CITY
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=TRUE
	.byte 4
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/CeladonCity_DepartmentStore_4F/header.inc =====
@ ===== BEGIN data/maps/CeladonCity_DepartmentStore_5F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/CeladonCity_DepartmentStore_5F/map.json
@

CeladonCity_DepartmentStore_5F:
	.4byte CeladonCity_DepartmentStore_5F_Layout
	.4byte CeladonCity_DepartmentStore_5F_MapEvents
	.4byte CeladonCity_DepartmentStore_5F_MapScripts
	.4byte NULL
	.2byte MUS_POKE_CENTER
	.2byte LAYOUT_CELADON_CITY_DEPARTMENT_STORE_5F
	.byte MAPSEC_CELADON_CITY
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=TRUE
	.byte 5
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/CeladonCity_DepartmentStore_5F/header.inc =====
@ ===== BEGIN data/maps/CeladonCity_DepartmentStore_Roof/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/CeladonCity_DepartmentStore_Roof/map.json
@

CeladonCity_DepartmentStore_Roof:
	.4byte CeladonCity_DepartmentStore_Roof_Layout
	.4byte CeladonCity_DepartmentStore_Roof_MapEvents
	.4byte CeladonCity_DepartmentStore_Roof_MapScripts
	.4byte NULL
	.2byte MUS_POKE_CENTER
	.2byte LAYOUT_CELADON_CITY_DEPARTMENT_STORE_ROOF
	.byte MAPSEC_CELADON_CITY
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=TRUE
	.byte 127
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/CeladonCity_DepartmentStore_Roof/header.inc =====
@ ===== BEGIN data/maps/CeladonCity_DepartmentStore_Elevator/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/CeladonCity_DepartmentStore_Elevator/map.json
@

CeladonCity_DepartmentStore_Elevator:
	.4byte CeladonCity_DepartmentStore_Elevator_Layout
	.4byte CeladonCity_DepartmentStore_Elevator_MapEvents
	.4byte CeladonCity_DepartmentStore_Elevator_MapScripts
	.4byte NULL
	.2byte MUS_POKE_CENTER
	.2byte LAYOUT_CELADON_CITY_DEPARTMENT_STORE_ELEVATOR
	.byte MAPSEC_CELADON_CITY
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/CeladonCity_DepartmentStore_Elevator/header.inc =====
@ ===== BEGIN data/maps/CeladonCity_Condominiums_1F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/CeladonCity_Condominiums_1F/map.json
@

CeladonCity_Condominiums_1F:
	.4byte CeladonCity_Condominiums_1F_Layout
	.4byte CeladonCity_Condominiums_1F_MapEvents
	.4byte CeladonCity_Condominiums_1F_MapScripts
	.4byte NULL
	.2byte MUS_CELADON
	.2byte LAYOUT_CELADON_CITY_CONDOMINIUMS_1F
	.byte MAPSEC_CELADON_CITY
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/CeladonCity_Condominiums_1F/header.inc =====
@ ===== BEGIN data/maps/CeladonCity_Condominiums_2F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/CeladonCity_Condominiums_2F/map.json
@

CeladonCity_Condominiums_2F:
	.4byte CeladonCity_Condominiums_2F_Layout
	.4byte CeladonCity_Condominiums_2F_MapEvents
	.4byte CeladonCity_Condominiums_2F_MapScripts
	.4byte NULL
	.2byte MUS_CELADON
	.2byte LAYOUT_CELADON_CITY_CONDOMINIUMS_2F
	.byte MAPSEC_CELADON_CITY
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/CeladonCity_Condominiums_2F/header.inc =====
@ ===== BEGIN data/maps/CeladonCity_Condominiums_3F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/CeladonCity_Condominiums_3F/map.json
@

CeladonCity_Condominiums_3F:
	.4byte CeladonCity_Condominiums_3F_Layout
	.4byte CeladonCity_Condominiums_3F_MapEvents
	.4byte CeladonCity_Condominiums_3F_MapScripts
	.4byte NULL
	.2byte MUS_CELADON
	.2byte LAYOUT_CELADON_CITY_CONDOMINIUMS_3F
	.byte MAPSEC_CELADON_CITY
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/CeladonCity_Condominiums_3F/header.inc =====
@ ===== BEGIN data/maps/CeladonCity_Condominiums_Roof/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/CeladonCity_Condominiums_Roof/map.json
@

CeladonCity_Condominiums_Roof:
	.4byte CeladonCity_Condominiums_Roof_Layout
	.4byte CeladonCity_Condominiums_Roof_MapEvents
	.4byte CeladonCity_Condominiums_Roof_MapScripts
	.4byte NULL
	.2byte MUS_CELADON
	.2byte LAYOUT_CELADON_CITY_CONDOMINIUMS_ROOF
	.byte MAPSEC_CELADON_CITY
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/CeladonCity_Condominiums_Roof/header.inc =====
@ ===== BEGIN data/maps/CeladonCity_Condominiums_RoofRoom/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/CeladonCity_Condominiums_RoofRoom/map.json
@

CeladonCity_Condominiums_RoofRoom:
	.4byte CeladonCity_Condominiums_RoofRoom_Layout
	.4byte CeladonCity_Condominiums_RoofRoom_MapEvents
	.4byte CeladonCity_Condominiums_RoofRoom_MapScripts
	.4byte NULL
	.2byte MUS_CELADON
	.2byte LAYOUT_CELADON_CITY_CONDOMINIUMS_ROOF_ROOM
	.byte MAPSEC_CELADON_CITY
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/CeladonCity_Condominiums_RoofRoom/header.inc =====
@ ===== BEGIN data/maps/CeladonCity_PokemonCenter_1F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/CeladonCity_PokemonCenter_1F/map.json
@

CeladonCity_PokemonCenter_1F:
	.4byte PokemonCenter_1F_Layout
	.4byte CeladonCity_PokemonCenter_1F_MapEvents
	.4byte CeladonCity_PokemonCenter_1F_MapScripts
	.4byte NULL
	.2byte MUS_POKE_CENTER
	.2byte LAYOUT_POKEMON_CENTER_1F
	.byte MAPSEC_CELADON_CITY
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/CeladonCity_PokemonCenter_1F/header.inc =====
@ ===== BEGIN data/maps/CeladonCity_PokemonCenter_2F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/CeladonCity_PokemonCenter_2F/map.json
@

CeladonCity_PokemonCenter_2F:
	.4byte PokemonCenter_2F_Layout
	.4byte CeladonCity_PokemonCenter_2F_MapEvents
	.4byte CeladonCity_PokemonCenter_2F_MapScripts
	.4byte NULL
	.2byte MUS_POKE_CENTER
	.2byte LAYOUT_POKEMON_CENTER_2F
	.byte MAPSEC_CELADON_CITY
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/CeladonCity_PokemonCenter_2F/header.inc =====
@ ===== BEGIN data/maps/CeladonCity_GameCorner/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/CeladonCity_GameCorner/map.json
@

CeladonCity_GameCorner:
	.4byte CeladonCity_GameCorner_Layout
	.4byte CeladonCity_GameCorner_MapEvents
	.4byte CeladonCity_GameCorner_MapScripts
	.4byte NULL
	.2byte MUS_GAME_CORNER
	.2byte LAYOUT_CELADON_CITY_GAME_CORNER
	.byte MAPSEC_CELADON_CITY
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/CeladonCity_GameCorner/header.inc =====
@ ===== BEGIN data/maps/CeladonCity_GameCorner_PrizeRoom/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/CeladonCity_GameCorner_PrizeRoom/map.json
@

CeladonCity_GameCorner_PrizeRoom:
	.4byte CeladonCity_GameCorner_PrizeRoom_Layout
	.4byte CeladonCity_GameCorner_PrizeRoom_MapEvents
	.4byte CeladonCity_GameCorner_PrizeRoom_MapScripts
	.4byte NULL
	.2byte MUS_CELADON
	.2byte LAYOUT_CELADON_CITY_GAME_CORNER_PRIZE_ROOM
	.byte MAPSEC_CELADON_CITY
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/CeladonCity_GameCorner_PrizeRoom/header.inc =====
@ ===== BEGIN data/maps/CeladonCity_Gym/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/CeladonCity_Gym/map.json
@

CeladonCity_Gym:
	.4byte CeladonCity_Gym_Layout
	.4byte CeladonCity_Gym_MapEvents
	.4byte CeladonCity_Gym_MapScripts
	.4byte NULL
	.2byte MUS_GYM
	.2byte LAYOUT_CELADON_CITY_GYM
	.byte MAPSEC_CELADON_CITY
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_GYM

@ ===== END data/maps/CeladonCity_Gym/header.inc =====
@ ===== BEGIN data/maps/CeladonCity_Restaurant/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/CeladonCity_Restaurant/map.json
@

CeladonCity_Restaurant:
	.4byte CeladonCity_Restaurant_Layout
	.4byte CeladonCity_Restaurant_MapEvents
	.4byte CeladonCity_Restaurant_MapScripts
	.4byte NULL
	.2byte MUS_CELADON
	.2byte LAYOUT_CELADON_CITY_RESTAURANT
	.byte MAPSEC_CELADON_CITY
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/CeladonCity_Restaurant/header.inc =====
@ ===== BEGIN data/maps/CeladonCity_House1/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/CeladonCity_House1/map.json
@

CeladonCity_House1:
	.4byte House5_Layout
	.4byte CeladonCity_House1_MapEvents
	.4byte CeladonCity_House1_MapScripts
	.4byte NULL
	.2byte MUS_CELADON
	.2byte LAYOUT_HOUSE5
	.byte MAPSEC_CELADON_CITY
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/CeladonCity_House1/header.inc =====
@ ===== BEGIN data/maps/CeladonCity_Hotel/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/CeladonCity_Hotel/map.json
@

CeladonCity_Hotel:
	.4byte CeladonCity_Hotel_Layout
	.4byte CeladonCity_Hotel_MapEvents
	.4byte CeladonCity_Hotel_MapScripts
	.4byte NULL
	.2byte MUS_CELADON
	.2byte LAYOUT_CELADON_CITY_HOTEL
	.byte MAPSEC_CELADON_CITY
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/CeladonCity_Hotel/header.inc =====
@ ===== BEGIN data/maps/FuchsiaCity_SafariZone_Entrance/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FuchsiaCity_SafariZone_Entrance/map.json
@

FuchsiaCity_SafariZone_Entrance:
	.4byte FuchsiaCity_SafariZone_Entrance_Layout
	.4byte FuchsiaCity_SafariZone_Entrance_MapEvents
	.4byte FuchsiaCity_SafariZone_Entrance_MapScripts
	.4byte NULL
	.2byte MUS_FUCHSIA
	.2byte LAYOUT_FUCHSIA_CITY_SAFARI_ZONE_ENTRANCE
	.byte MAPSEC_FUCHSIA_CITY
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/FuchsiaCity_SafariZone_Entrance/header.inc =====
@ ===== BEGIN data/maps/FuchsiaCity_Mart/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FuchsiaCity_Mart/map.json
@

FuchsiaCity_Mart:
	.4byte Mart_Layout
	.4byte FuchsiaCity_Mart_MapEvents
	.4byte FuchsiaCity_Mart_MapScripts
	.4byte NULL
	.2byte MUS_POKE_CENTER
	.2byte LAYOUT_MART
	.byte MAPSEC_FUCHSIA_CITY
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/FuchsiaCity_Mart/header.inc =====
@ ===== BEGIN data/maps/FuchsiaCity_SafariZone_Office/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FuchsiaCity_SafariZone_Office/map.json
@

FuchsiaCity_SafariZone_Office:
	.4byte FuchsiaCity_SafariZone_Office_Layout
	.4byte FuchsiaCity_SafariZone_Office_MapEvents
	.4byte FuchsiaCity_SafariZone_Office_MapScripts
	.4byte NULL
	.2byte MUS_FUCHSIA
	.2byte LAYOUT_FUCHSIA_CITY_SAFARI_ZONE_OFFICE
	.byte MAPSEC_FUCHSIA_CITY
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/FuchsiaCity_SafariZone_Office/header.inc =====
@ ===== BEGIN data/maps/FuchsiaCity_Gym/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FuchsiaCity_Gym/map.json
@

FuchsiaCity_Gym:
	.4byte FuchsiaCity_Gym_Layout
	.4byte FuchsiaCity_Gym_MapEvents
	.4byte FuchsiaCity_Gym_MapScripts
	.4byte NULL
	.2byte MUS_GYM
	.2byte LAYOUT_FUCHSIA_CITY_GYM
	.byte MAPSEC_FUCHSIA_CITY
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_GYM

@ ===== END data/maps/FuchsiaCity_Gym/header.inc =====
@ ===== BEGIN data/maps/FuchsiaCity_House1/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FuchsiaCity_House1/map.json
@

FuchsiaCity_House1:
	.4byte House1_Layout
	.4byte FuchsiaCity_House1_MapEvents
	.4byte FuchsiaCity_House1_MapScripts
	.4byte NULL
	.2byte MUS_FUCHSIA
	.2byte LAYOUT_HOUSE1
	.byte MAPSEC_FUCHSIA_CITY
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/FuchsiaCity_House1/header.inc =====
@ ===== BEGIN data/maps/FuchsiaCity_PokemonCenter_1F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FuchsiaCity_PokemonCenter_1F/map.json
@

FuchsiaCity_PokemonCenter_1F:
	.4byte PokemonCenter_1F_Layout
	.4byte FuchsiaCity_PokemonCenter_1F_MapEvents
	.4byte FuchsiaCity_PokemonCenter_1F_MapScripts
	.4byte NULL
	.2byte MUS_POKE_CENTER
	.2byte LAYOUT_POKEMON_CENTER_1F
	.byte MAPSEC_FUCHSIA_CITY
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/FuchsiaCity_PokemonCenter_1F/header.inc =====
@ ===== BEGIN data/maps/FuchsiaCity_PokemonCenter_2F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FuchsiaCity_PokemonCenter_2F/map.json
@

FuchsiaCity_PokemonCenter_2F:
	.4byte PokemonCenter_2F_Layout
	.4byte FuchsiaCity_PokemonCenter_2F_MapEvents
	.4byte FuchsiaCity_PokemonCenter_2F_MapScripts
	.4byte NULL
	.2byte MUS_POKE_CENTER
	.2byte LAYOUT_POKEMON_CENTER_2F
	.byte MAPSEC_FUCHSIA_CITY
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/FuchsiaCity_PokemonCenter_2F/header.inc =====
@ ===== BEGIN data/maps/FuchsiaCity_WardensHouse/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FuchsiaCity_WardensHouse/map.json
@

FuchsiaCity_WardensHouse:
	.4byte FuchsiaCity_WardensHouse_Layout
	.4byte FuchsiaCity_WardensHouse_MapEvents
	.4byte FuchsiaCity_WardensHouse_MapScripts
	.4byte NULL
	.2byte MUS_FUCHSIA
	.2byte LAYOUT_FUCHSIA_CITY_WARDENS_HOUSE
	.byte MAPSEC_FUCHSIA_CITY
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/FuchsiaCity_WardensHouse/header.inc =====
@ ===== BEGIN data/maps/FuchsiaCity_House2/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FuchsiaCity_House2/map.json
@

FuchsiaCity_House2:
	.4byte FuchsiaCity_House2_Layout
	.4byte FuchsiaCity_House2_MapEvents
	.4byte FuchsiaCity_House2_MapScripts
	.4byte NULL
	.2byte MUS_FUCHSIA
	.2byte LAYOUT_FUCHSIA_CITY_HOUSE2
	.byte MAPSEC_FUCHSIA_CITY
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/FuchsiaCity_House2/header.inc =====
@ ===== BEGIN data/maps/FuchsiaCity_House3/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FuchsiaCity_House3/map.json
@

FuchsiaCity_House3:
	.4byte House1_Layout
	.4byte FuchsiaCity_House3_MapEvents
	.4byte FuchsiaCity_House3_MapScripts
	.4byte NULL
	.2byte MUS_FUCHSIA
	.2byte LAYOUT_HOUSE1
	.byte MAPSEC_FUCHSIA_CITY
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/FuchsiaCity_House3/header.inc =====
@ ===== BEGIN data/maps/CinnabarIsland_Gym/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/CinnabarIsland_Gym/map.json
@

CinnabarIsland_Gym:
	.4byte CinnabarIsland_Gym_Layout
	.4byte CinnabarIsland_Gym_MapEvents
	.4byte CinnabarIsland_Gym_MapScripts
	.4byte NULL
	.2byte MUS_GYM
	.2byte LAYOUT_CINNABAR_ISLAND_GYM
	.byte MAPSEC_CINNABAR_ISLAND
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_GYM

@ ===== END data/maps/CinnabarIsland_Gym/header.inc =====
@ ===== BEGIN data/maps/CinnabarIsland_PokemonLab_Entrance/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/CinnabarIsland_PokemonLab_Entrance/map.json
@

CinnabarIsland_PokemonLab_Entrance:
	.4byte CinnabarIsland_PokemonLab_Entrance_Layout
	.4byte CinnabarIsland_PokemonLab_Entrance_MapEvents
	.4byte CinnabarIsland_PokemonLab_Entrance_MapScripts
	.4byte NULL
	.2byte MUS_CINNABAR
	.2byte LAYOUT_CINNABAR_ISLAND_POKEMON_LAB_ENTRANCE
	.byte MAPSEC_CINNABAR_ISLAND
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/CinnabarIsland_PokemonLab_Entrance/header.inc =====
@ ===== BEGIN data/maps/CinnabarIsland_PokemonLab_Lounge/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/CinnabarIsland_PokemonLab_Lounge/map.json
@

CinnabarIsland_PokemonLab_Lounge:
	.4byte CinnabarIsland_PokemonLab_Lounge_Layout
	.4byte CinnabarIsland_PokemonLab_Lounge_MapEvents
	.4byte CinnabarIsland_PokemonLab_Lounge_MapScripts
	.4byte NULL
	.2byte MUS_CINNABAR
	.2byte LAYOUT_CINNABAR_ISLAND_POKEMON_LAB_LOUNGE
	.byte MAPSEC_CINNABAR_ISLAND
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/CinnabarIsland_PokemonLab_Lounge/header.inc =====
@ ===== BEGIN data/maps/CinnabarIsland_PokemonLab_ResearchRoom/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/CinnabarIsland_PokemonLab_ResearchRoom/map.json
@

CinnabarIsland_PokemonLab_ResearchRoom:
	.4byte CinnabarIsland_PokemonLab_ResearchRoom_Layout
	.4byte CinnabarIsland_PokemonLab_ResearchRoom_MapEvents
	.4byte CinnabarIsland_PokemonLab_ResearchRoom_MapScripts
	.4byte NULL
	.2byte MUS_CINNABAR
	.2byte LAYOUT_CINNABAR_ISLAND_POKEMON_LAB_RESEARCH_ROOM
	.byte MAPSEC_CINNABAR_ISLAND
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/CinnabarIsland_PokemonLab_ResearchRoom/header.inc =====
@ ===== BEGIN data/maps/CinnabarIsland_PokemonLab_ExperimentRoom/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/CinnabarIsland_PokemonLab_ExperimentRoom/map.json
@

CinnabarIsland_PokemonLab_ExperimentRoom:
	.4byte CinnabarIsland_PokemonLab_ExperimentRoom_Layout
	.4byte CinnabarIsland_PokemonLab_ExperimentRoom_MapEvents
	.4byte CinnabarIsland_PokemonLab_ExperimentRoom_MapScripts
	.4byte NULL
	.2byte MUS_CINNABAR
	.2byte LAYOUT_CINNABAR_ISLAND_POKEMON_LAB_EXPERIMENT_ROOM
	.byte MAPSEC_CINNABAR_ISLAND
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/CinnabarIsland_PokemonLab_ExperimentRoom/header.inc =====
@ ===== BEGIN data/maps/CinnabarIsland_PokemonCenter_1F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/CinnabarIsland_PokemonCenter_1F/map.json
@

CinnabarIsland_PokemonCenter_1F:
	.4byte PokemonCenter_1F_Layout
	.4byte CinnabarIsland_PokemonCenter_1F_MapEvents
	.4byte CinnabarIsland_PokemonCenter_1F_MapScripts
	.4byte NULL
	.2byte MUS_POKE_CENTER
	.2byte LAYOUT_POKEMON_CENTER_1F
	.byte MAPSEC_CINNABAR_ISLAND
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/CinnabarIsland_PokemonCenter_1F/header.inc =====
@ ===== BEGIN data/maps/CinnabarIsland_PokemonCenter_2F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/CinnabarIsland_PokemonCenter_2F/map.json
@

CinnabarIsland_PokemonCenter_2F:
	.4byte PokemonCenter_2F_Layout
	.4byte CinnabarIsland_PokemonCenter_2F_MapEvents
	.4byte CinnabarIsland_PokemonCenter_2F_MapScripts
	.4byte NULL
	.2byte MUS_POKE_CENTER
	.2byte LAYOUT_POKEMON_CENTER_2F
	.byte MAPSEC_CINNABAR_ISLAND
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/CinnabarIsland_PokemonCenter_2F/header.inc =====
@ ===== BEGIN data/maps/CinnabarIsland_Mart/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/CinnabarIsland_Mart/map.json
@

CinnabarIsland_Mart:
	.4byte Mart_Layout
	.4byte CinnabarIsland_Mart_MapEvents
	.4byte CinnabarIsland_Mart_MapScripts
	.4byte NULL
	.2byte MUS_POKE_CENTER
	.2byte LAYOUT_MART
	.byte MAPSEC_CINNABAR_ISLAND
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/CinnabarIsland_Mart/header.inc =====
@ ===== BEGIN data/maps/IndigoPlateau_PokemonCenter_1F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/IndigoPlateau_PokemonCenter_1F/map.json
@

IndigoPlateau_PokemonCenter_1F:
	.4byte IndigoPlateau_PokemonCenter_1F_Layout
	.4byte IndigoPlateau_PokemonCenter_1F_MapEvents
	.4byte IndigoPlateau_PokemonCenter_1F_MapScripts
	.4byte NULL
	.2byte MUS_GYM
	.2byte LAYOUT_INDIGO_PLATEAU_POKEMON_CENTER_1F
	.byte MAPSEC_INDIGO_PLATEAU
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_GYM

@ ===== END data/maps/IndigoPlateau_PokemonCenter_1F/header.inc =====
@ ===== BEGIN data/maps/IndigoPlateau_PokemonCenter_2F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/IndigoPlateau_PokemonCenter_2F/map.json
@

IndigoPlateau_PokemonCenter_2F:
	.4byte PokemonCenter_2F_Layout
	.4byte IndigoPlateau_PokemonCenter_2F_MapEvents
	.4byte IndigoPlateau_PokemonCenter_2F_MapScripts
	.4byte NULL
	.2byte MUS_POKE_CENTER
	.2byte LAYOUT_POKEMON_CENTER_2F
	.byte MAPSEC_INDIGO_PLATEAU
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_GYM

@ ===== END data/maps/IndigoPlateau_PokemonCenter_2F/header.inc =====
@ ===== BEGIN data/maps/SaffronCity_CopycatsHouse_1F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SaffronCity_CopycatsHouse_1F/map.json
@

SaffronCity_CopycatsHouse_1F:
	.4byte SaffronCity_CopycatsHouse_1F_Layout
	.4byte SaffronCity_CopycatsHouse_1F_MapEvents
	.4byte SaffronCity_CopycatsHouse_1F_MapScripts
	.4byte NULL
	.2byte MUS_PEWTER
	.2byte LAYOUT_SAFFRON_CITY_COPYCATS_HOUSE_1F
	.byte MAPSEC_SAFFRON_CITY
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SaffronCity_CopycatsHouse_1F/header.inc =====
@ ===== BEGIN data/maps/SaffronCity_CopycatsHouse_2F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SaffronCity_CopycatsHouse_2F/map.json
@

SaffronCity_CopycatsHouse_2F:
	.4byte SaffronCity_CopycatsHouse_2F_Layout
	.4byte SaffronCity_CopycatsHouse_2F_MapEvents
	.4byte SaffronCity_CopycatsHouse_2F_MapScripts
	.4byte NULL
	.2byte MUS_PEWTER
	.2byte LAYOUT_SAFFRON_CITY_COPYCATS_HOUSE_2F
	.byte MAPSEC_SAFFRON_CITY
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SaffronCity_CopycatsHouse_2F/header.inc =====
@ ===== BEGIN data/maps/SaffronCity_Dojo/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SaffronCity_Dojo/map.json
@

SaffronCity_Dojo:
	.4byte SaffronCity_Dojo_Layout
	.4byte SaffronCity_Dojo_MapEvents
	.4byte SaffronCity_Dojo_MapScripts
	.4byte NULL
	.2byte MUS_PEWTER
	.2byte LAYOUT_SAFFRON_CITY_DOJO
	.byte MAPSEC_SAFFRON_CITY
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SaffronCity_Dojo/header.inc =====
@ ===== BEGIN data/maps/SaffronCity_Gym/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SaffronCity_Gym/map.json
@

SaffronCity_Gym:
	.4byte SaffronCity_Gym_Layout
	.4byte SaffronCity_Gym_MapEvents
	.4byte SaffronCity_Gym_MapScripts
	.4byte NULL
	.2byte MUS_GYM
	.2byte LAYOUT_SAFFRON_CITY_GYM
	.byte MAPSEC_SAFFRON_CITY
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=TRUE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_GYM

@ ===== END data/maps/SaffronCity_Gym/header.inc =====
@ ===== BEGIN data/maps/SaffronCity_House/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SaffronCity_House/map.json
@

SaffronCity_House:
	.4byte House5_Layout
	.4byte SaffronCity_House_MapEvents
	.4byte SaffronCity_House_MapScripts
	.4byte NULL
	.2byte MUS_PEWTER
	.2byte LAYOUT_HOUSE5
	.byte MAPSEC_SAFFRON_CITY
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SaffronCity_House/header.inc =====
@ ===== BEGIN data/maps/SaffronCity_Mart/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SaffronCity_Mart/map.json
@

SaffronCity_Mart:
	.4byte Mart_Layout
	.4byte SaffronCity_Mart_MapEvents
	.4byte SaffronCity_Mart_MapScripts
	.4byte NULL
	.2byte MUS_POKE_CENTER
	.2byte LAYOUT_MART
	.byte MAPSEC_SAFFRON_CITY
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SaffronCity_Mart/header.inc =====
@ ===== BEGIN data/maps/SaffronCity_PokemonCenter_1F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SaffronCity_PokemonCenter_1F/map.json
@

SaffronCity_PokemonCenter_1F:
	.4byte PokemonCenter_1F_Layout
	.4byte SaffronCity_PokemonCenter_1F_MapEvents
	.4byte SaffronCity_PokemonCenter_1F_MapScripts
	.4byte NULL
	.2byte MUS_POKE_CENTER
	.2byte LAYOUT_POKEMON_CENTER_1F
	.byte MAPSEC_SAFFRON_CITY
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SaffronCity_PokemonCenter_1F/header.inc =====
@ ===== BEGIN data/maps/SaffronCity_PokemonCenter_2F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SaffronCity_PokemonCenter_2F/map.json
@

SaffronCity_PokemonCenter_2F:
	.4byte PokemonCenter_2F_Layout
	.4byte SaffronCity_PokemonCenter_2F_MapEvents
	.4byte SaffronCity_PokemonCenter_2F_MapScripts
	.4byte NULL
	.2byte MUS_POKE_CENTER
	.2byte LAYOUT_POKEMON_CENTER_2F
	.byte MAPSEC_SAFFRON_CITY
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SaffronCity_PokemonCenter_2F/header.inc =====
@ ===== BEGIN data/maps/SaffronCity_MrPsychicsHouse/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SaffronCity_MrPsychicsHouse/map.json
@

SaffronCity_MrPsychicsHouse:
	.4byte House5_Layout
	.4byte SaffronCity_MrPsychicsHouse_MapEvents
	.4byte SaffronCity_MrPsychicsHouse_MapScripts
	.4byte NULL
	.2byte MUS_PEWTER
	.2byte LAYOUT_HOUSE5
	.byte MAPSEC_SAFFRON_CITY
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SaffronCity_MrPsychicsHouse/header.inc =====
@ ===== BEGIN data/maps/SaffronCity_PokemonTrainerFanClub/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SaffronCity_PokemonTrainerFanClub/map.json
@

SaffronCity_PokemonTrainerFanClub:
	.4byte SaffronCity_PokemonTrainerFanClub_Layout
	.4byte SaffronCity_PokemonTrainerFanClub_MapEvents
	.4byte SaffronCity_PokemonTrainerFanClub_MapScripts
	.4byte NULL
	.2byte MUS_PEWTER
	.2byte LAYOUT_SAFFRON_CITY_POKEMON_TRAINER_FAN_CLUB
	.byte MAPSEC_SAFFRON_CITY
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SaffronCity_PokemonTrainerFanClub/header.inc =====
@ ===== BEGIN data/maps/Route2_ViridianForest_SouthEntrance/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route2_ViridianForest_SouthEntrance/map.json
@

Route2_ViridianForest_SouthEntrance:
	.4byte Route2_Entrance_Layout
	.4byte Route2_ViridianForest_SouthEntrance_MapEvents
	.4byte Route2_ViridianForest_SouthEntrance_MapScripts
	.4byte NULL
	.2byte MUS_PEWTER
	.2byte LAYOUT_ROUTE2_ENTRANCE
	.byte MAPSEC_ROUTE_2
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=TRUE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/Route2_ViridianForest_SouthEntrance/header.inc =====
@ ===== BEGIN data/maps/Route2_House/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route2_House/map.json
@

Route2_House:
	.4byte House2_Layout
	.4byte Route2_House_MapEvents
	.4byte Route2_House_MapScripts
	.4byte NULL
	.2byte MUS_PEWTER
	.2byte LAYOUT_HOUSE2
	.byte MAPSEC_ROUTE_2
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/Route2_House/header.inc =====
@ ===== BEGIN data/maps/Route2_EastBuilding/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route2_EastBuilding/map.json
@

Route2_EastBuilding:
	.4byte Route2_Entrance_Layout
	.4byte Route2_EastBuilding_MapEvents
	.4byte Route2_EastBuilding_MapScripts
	.4byte NULL
	.2byte MUS_PEWTER
	.2byte LAYOUT_ROUTE2_ENTRANCE
	.byte MAPSEC_ROUTE_2
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=TRUE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/Route2_EastBuilding/header.inc =====
@ ===== BEGIN data/maps/Route2_ViridianForest_NorthEntrance/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route2_ViridianForest_NorthEntrance/map.json
@

Route2_ViridianForest_NorthEntrance:
	.4byte Route2_Entrance_Layout
	.4byte Route2_ViridianForest_NorthEntrance_MapEvents
	.4byte Route2_ViridianForest_NorthEntrance_MapScripts
	.4byte NULL
	.2byte MUS_PEWTER
	.2byte LAYOUT_ROUTE2_ENTRANCE
	.byte MAPSEC_ROUTE_2
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=TRUE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/Route2_ViridianForest_NorthEntrance/header.inc =====
@ ===== BEGIN data/maps/Route4_PokemonCenter_1F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route4_PokemonCenter_1F/map.json
@

Route4_PokemonCenter_1F:
	.4byte PokemonCenter_1F_Layout
	.4byte Route4_PokemonCenter_1F_MapEvents
	.4byte Route4_PokemonCenter_1F_MapScripts
	.4byte NULL
	.2byte MUS_POKE_CENTER
	.2byte LAYOUT_POKEMON_CENTER_1F
	.byte MAPSEC_ROUTE_4
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/Route4_PokemonCenter_1F/header.inc =====
@ ===== BEGIN data/maps/Route4_PokemonCenter_2F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route4_PokemonCenter_2F/map.json
@

Route4_PokemonCenter_2F:
	.4byte PokemonCenter_2F_Layout
	.4byte Route4_PokemonCenter_2F_MapEvents
	.4byte Route4_PokemonCenter_2F_MapScripts
	.4byte NULL
	.2byte MUS_POKE_CENTER
	.2byte LAYOUT_POKEMON_CENTER_2F
	.byte MAPSEC_ROUTE_4
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/Route4_PokemonCenter_2F/header.inc =====
@ ===== BEGIN data/maps/Route5_PokemonDayCare/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route5_PokemonDayCare/map.json
@

Route5_PokemonDayCare:
	.4byte Route5_PokemonDayCare_Layout
	.4byte Route5_PokemonDayCare_MapEvents
	.4byte Route5_PokemonDayCare_MapScripts
	.4byte NULL
	.2byte MUS_PEWTER
	.2byte LAYOUT_ROUTE5_POKEMON_DAY_CARE
	.byte MAPSEC_ROUTE_5
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/Route5_PokemonDayCare/header.inc =====
@ ===== BEGIN data/maps/Route5_SouthEntrance/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route5_SouthEntrance/map.json
@

Route5_SouthEntrance:
	.4byte SaffronCity_NorthSouthEntrance_Layout
	.4byte Route5_SouthEntrance_MapEvents
	.4byte Route5_SouthEntrance_MapScripts
	.4byte NULL
	.2byte MUS_PEWTER
	.2byte LAYOUT_SAFFRON_CITY_NORTH_SOUTH_ENTRANCE
	.byte MAPSEC_ROUTE_5
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=TRUE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/Route5_SouthEntrance/header.inc =====
@ ===== BEGIN data/maps/Route6_NorthEntrance/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route6_NorthEntrance/map.json
@

Route6_NorthEntrance:
	.4byte SaffronCity_NorthSouthEntrance_Layout
	.4byte Route6_NorthEntrance_MapEvents
	.4byte Route6_NorthEntrance_MapScripts
	.4byte NULL
	.2byte MUS_PEWTER
	.2byte LAYOUT_SAFFRON_CITY_NORTH_SOUTH_ENTRANCE
	.byte MAPSEC_ROUTE_6
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=TRUE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/Route6_NorthEntrance/header.inc =====
@ ===== BEGIN data/maps/Route6_UnusedHouse/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route6_UnusedHouse/map.json
@

Route6_UnusedHouse:
	.4byte House2_Layout
	.4byte Route6_UnusedHouse_MapEvents
	.4byte Route6_UnusedHouse_MapScripts
	.4byte NULL
	.2byte MUS_ROUTE3
	.2byte LAYOUT_HOUSE2
	.byte MAPSEC_ROUTE_6
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/Route6_UnusedHouse/header.inc =====
@ ===== BEGIN data/maps/Route7_EastEntrance/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route7_EastEntrance/map.json
@

Route7_EastEntrance:
	.4byte SaffronCity_EastWestEntrance_Layout
	.4byte Route7_EastEntrance_MapEvents
	.4byte Route7_EastEntrance_MapScripts
	.4byte NULL
	.2byte MUS_PEWTER
	.2byte LAYOUT_SAFFRON_CITY_EAST_WEST_ENTRANCE
	.byte MAPSEC_ROUTE_7
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=TRUE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/Route7_EastEntrance/header.inc =====
@ ===== BEGIN data/maps/Route8_WestEntrance/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route8_WestEntrance/map.json
@

Route8_WestEntrance:
	.4byte SaffronCity_EastWestEntrance_Layout
	.4byte Route8_WestEntrance_MapEvents
	.4byte Route8_WestEntrance_MapScripts
	.4byte NULL
	.2byte MUS_PEWTER
	.2byte LAYOUT_SAFFRON_CITY_EAST_WEST_ENTRANCE
	.byte MAPSEC_ROUTE_8
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=TRUE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/Route8_WestEntrance/header.inc =====
@ ===== BEGIN data/maps/Route10_PokemonCenter_1F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route10_PokemonCenter_1F/map.json
@

Route10_PokemonCenter_1F:
	.4byte PokemonCenter_1F_Layout
	.4byte Route10_PokemonCenter_1F_MapEvents
	.4byte Route10_PokemonCenter_1F_MapScripts
	.4byte NULL
	.2byte MUS_POKE_CENTER
	.2byte LAYOUT_POKEMON_CENTER_1F
	.byte MAPSEC_ROUTE_10
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/Route10_PokemonCenter_1F/header.inc =====
@ ===== BEGIN data/maps/Route10_PokemonCenter_2F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route10_PokemonCenter_2F/map.json
@

Route10_PokemonCenter_2F:
	.4byte PokemonCenter_2F_Layout
	.4byte Route10_PokemonCenter_2F_MapEvents
	.4byte Route10_PokemonCenter_2F_MapScripts
	.4byte NULL
	.2byte MUS_POKE_CENTER
	.2byte LAYOUT_POKEMON_CENTER_2F
	.byte MAPSEC_ROUTE_10
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/Route10_PokemonCenter_2F/header.inc =====
@ ===== BEGIN data/maps/Route11_EastEntrance_1F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route11_EastEntrance_1F/map.json
@

Route11_EastEntrance_1F:
	.4byte Entrance_1F_Layout
	.4byte Route11_EastEntrance_1F_MapEvents
	.4byte Route11_EastEntrance_1F_MapScripts
	.4byte NULL
	.2byte MUS_VERMILLION
	.2byte LAYOUT_ENTRANCE_1F
	.byte MAPSEC_ROUTE_11
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=TRUE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/Route11_EastEntrance_1F/header.inc =====
@ ===== BEGIN data/maps/Route11_EastEntrance_2F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route11_EastEntrance_2F/map.json
@

Route11_EastEntrance_2F:
	.4byte Entrance_2F_Layout
	.4byte Route11_EastEntrance_2F_MapEvents
	.4byte Route11_EastEntrance_2F_MapScripts
	.4byte NULL
	.2byte MUS_VERMILLION
	.2byte LAYOUT_ENTRANCE_2F
	.byte MAPSEC_ROUTE_11
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/Route11_EastEntrance_2F/header.inc =====
@ ===== BEGIN data/maps/Route12_NorthEntrance_1F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route12_NorthEntrance_1F/map.json
@

Route12_NorthEntrance_1F:
	.4byte Route12_NorthEntrance_1F_Layout
	.4byte Route12_NorthEntrance_1F_MapEvents
	.4byte Route12_NorthEntrance_1F_MapScripts
	.4byte NULL
	.2byte MUS_PEWTER
	.2byte LAYOUT_ROUTE12_NORTH_ENTRANCE_1F
	.byte MAPSEC_ROUTE_12
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=TRUE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/Route12_NorthEntrance_1F/header.inc =====
@ ===== BEGIN data/maps/Route12_NorthEntrance_2F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route12_NorthEntrance_2F/map.json
@

Route12_NorthEntrance_2F:
	.4byte Entrance_2F_Layout
	.4byte Route12_NorthEntrance_2F_MapEvents
	.4byte Route12_NorthEntrance_2F_MapScripts
	.4byte NULL
	.2byte MUS_PEWTER
	.2byte LAYOUT_ENTRANCE_2F
	.byte MAPSEC_ROUTE_12
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/Route12_NorthEntrance_2F/header.inc =====
@ ===== BEGIN data/maps/Route12_FishingHouse/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route12_FishingHouse/map.json
@

Route12_FishingHouse:
	.4byte House4_Layout
	.4byte Route12_FishingHouse_MapEvents
	.4byte Route12_FishingHouse_MapScripts
	.4byte NULL
	.2byte MUS_CELADON
	.2byte LAYOUT_HOUSE4
	.byte MAPSEC_ROUTE_12
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/Route12_FishingHouse/header.inc =====
@ ===== BEGIN data/maps/Route15_WestEntrance_1F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route15_WestEntrance_1F/map.json
@

Route15_WestEntrance_1F:
	.4byte Entrance_1F_Layout
	.4byte Route15_WestEntrance_1F_MapEvents
	.4byte Route15_WestEntrance_1F_MapScripts
	.4byte NULL
	.2byte MUS_PEWTER
	.2byte LAYOUT_ENTRANCE_1F
	.byte MAPSEC_ROUTE_15
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=TRUE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/Route15_WestEntrance_1F/header.inc =====
@ ===== BEGIN data/maps/Route15_WestEntrance_2F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route15_WestEntrance_2F/map.json
@

Route15_WestEntrance_2F:
	.4byte Entrance_2F_Layout
	.4byte Route15_WestEntrance_2F_MapEvents
	.4byte Route15_WestEntrance_2F_MapScripts
	.4byte NULL
	.2byte MUS_PEWTER
	.2byte LAYOUT_ENTRANCE_2F
	.byte MAPSEC_ROUTE_15
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/Route15_WestEntrance_2F/header.inc =====
@ ===== BEGIN data/maps/Route16_House/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route16_House/map.json
@

Route16_House:
	.4byte House1_Layout
	.4byte Route16_House_MapEvents
	.4byte Route16_House_MapScripts
	.4byte NULL
	.2byte MUS_CELADON
	.2byte LAYOUT_HOUSE1
	.byte MAPSEC_ROUTE_16
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/Route16_House/header.inc =====
@ ===== BEGIN data/maps/Route16_NorthEntrance_1F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route16_NorthEntrance_1F/map.json
@

Route16_NorthEntrance_1F:
	.4byte Route16_NorthEntrance_1F_Layout
	.4byte Route16_NorthEntrance_1F_MapEvents
	.4byte Route16_NorthEntrance_1F_MapScripts
	.4byte NULL
	.2byte MUS_PEWTER
	.2byte LAYOUT_ROUTE16_NORTH_ENTRANCE_1F
	.byte MAPSEC_ROUTE_16
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=TRUE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/Route16_NorthEntrance_1F/header.inc =====
@ ===== BEGIN data/maps/Route16_NorthEntrance_2F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route16_NorthEntrance_2F/map.json
@

Route16_NorthEntrance_2F:
	.4byte Entrance_2F_Layout
	.4byte Route16_NorthEntrance_2F_MapEvents
	.4byte Route16_NorthEntrance_2F_MapScripts
	.4byte NULL
	.2byte MUS_PEWTER
	.2byte LAYOUT_ENTRANCE_2F
	.byte MAPSEC_ROUTE_16
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/Route16_NorthEntrance_2F/header.inc =====
@ ===== BEGIN data/maps/Route18_EastEntrance_1F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route18_EastEntrance_1F/map.json
@

Route18_EastEntrance_1F:
	.4byte Entrance_1F_Layout
	.4byte Route18_EastEntrance_1F_MapEvents
	.4byte Route18_EastEntrance_1F_MapScripts
	.4byte NULL
	.2byte MUS_PEWTER
	.2byte LAYOUT_ENTRANCE_1F
	.byte MAPSEC_ROUTE_18
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=TRUE, allow_escaping=FALSE, allow_running=TRUE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/Route18_EastEntrance_1F/header.inc =====
@ ===== BEGIN data/maps/Route18_EastEntrance_2F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route18_EastEntrance_2F/map.json
@

Route18_EastEntrance_2F:
	.4byte Entrance_2F_Layout
	.4byte Route18_EastEntrance_2F_MapEvents
	.4byte Route18_EastEntrance_2F_MapScripts
	.4byte NULL
	.2byte MUS_PEWTER
	.2byte LAYOUT_ENTRANCE_2F
	.byte MAPSEC_ROUTE_18
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/Route18_EastEntrance_2F/header.inc =====
@ ===== BEGIN data/maps/Route19_UnusedHouse/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route19_UnusedHouse/map.json
@

Route19_UnusedHouse:
	.4byte House2_Layout
	.4byte Route19_UnusedHouse_MapEvents
	.4byte Route19_UnusedHouse_MapScripts
	.4byte NULL
	.2byte MUS_ROUTE3
	.2byte LAYOUT_HOUSE2
	.byte MAPSEC_ROUTE_19
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/Route19_UnusedHouse/header.inc =====
@ ===== BEGIN data/maps/Route22_NorthEntrance/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route22_NorthEntrance/map.json
@

Route22_NorthEntrance:
	.4byte Route22_NorthEntrance_Layout
	.4byte Route22_NorthEntrance_MapEvents
	.4byte Route22_NorthEntrance_MapScripts
	.4byte NULL
	.2byte MUS_VIRIDIAN_FOREST
	.2byte LAYOUT_ROUTE22_NORTH_ENTRANCE
	.byte MAPSEC_ROUTE_22
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/Route22_NorthEntrance/header.inc =====
@ ===== BEGIN data/maps/Route23_UnusedHouse/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route23_UnusedHouse/map.json
@

Route23_UnusedHouse:
	.4byte House2_Layout
	.4byte Route23_UnusedHouse_MapEvents
	.4byte Route23_UnusedHouse_MapScripts
	.4byte NULL
	.2byte MUS_VICTORY_ROAD
	.2byte LAYOUT_HOUSE2
	.byte MAPSEC_ROUTE_23
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/Route23_UnusedHouse/header.inc =====
@ ===== BEGIN data/maps/Route25_SeaCottage/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route25_SeaCottage/map.json
@

Route25_SeaCottage:
	.4byte Route25_SeaCottage_Layout
	.4byte Route25_SeaCottage_MapEvents
	.4byte Route25_SeaCottage_MapScripts
	.4byte NULL
	.2byte MUS_FUCHSIA
	.2byte LAYOUT_ROUTE25_SEA_COTTAGE
	.byte MAPSEC_ROUTE_25
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/Route25_SeaCottage/header.inc =====
@ ===== BEGIN data/maps/SevenIsland_House_Room1/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SevenIsland_House_Room1/map.json
@

SevenIsland_House_Room1:
	.4byte SevenIsland_House_Room1_Layout
	.4byte SevenIsland_House_Room1_MapEvents
	.4byte SevenIsland_House_Room1_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_67
	.2byte LAYOUT_SEVEN_ISLAND_HOUSE_ROOM1
	.byte MAPSEC_SEVEN_ISLAND
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_GYM

@ ===== END data/maps/SevenIsland_House_Room1/header.inc =====
@ ===== BEGIN data/maps/SevenIsland_House_Room2/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SevenIsland_House_Room2/map.json
@

SevenIsland_House_Room2:
	.4byte SevenIsland_House_Room2_Layout
	.4byte SevenIsland_House_Room2_MapEvents
	.4byte SevenIsland_House_Room2_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_67
	.2byte LAYOUT_SEVEN_ISLAND_HOUSE_ROOM2
	.byte MAPSEC_SEVEN_ISLAND
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_GYM

@ ===== END data/maps/SevenIsland_House_Room2/header.inc =====
@ ===== BEGIN data/maps/SevenIsland_Mart/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SevenIsland_Mart/map.json
@

SevenIsland_Mart:
	.4byte Mart_Layout
	.4byte SevenIsland_Mart_MapEvents
	.4byte SevenIsland_Mart_MapScripts
	.4byte NULL
	.2byte MUS_POKE_CENTER
	.2byte LAYOUT_MART
	.byte MAPSEC_SEVEN_ISLAND
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SevenIsland_Mart/header.inc =====
@ ===== BEGIN data/maps/SevenIsland_PokemonCenter_1F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SevenIsland_PokemonCenter_1F/map.json
@

SevenIsland_PokemonCenter_1F:
	.4byte PokemonCenter_1F_Layout
	.4byte SevenIsland_PokemonCenter_1F_MapEvents
	.4byte SevenIsland_PokemonCenter_1F_MapScripts
	.4byte NULL
	.2byte MUS_POKE_CENTER
	.2byte LAYOUT_POKEMON_CENTER_1F
	.byte MAPSEC_SEVEN_ISLAND
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SevenIsland_PokemonCenter_1F/header.inc =====
@ ===== BEGIN data/maps/SevenIsland_PokemonCenter_2F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SevenIsland_PokemonCenter_2F/map.json
@

SevenIsland_PokemonCenter_2F:
	.4byte PokemonCenter_2F_Layout
	.4byte SevenIsland_PokemonCenter_2F_MapEvents
	.4byte SevenIsland_PokemonCenter_2F_MapScripts
	.4byte NULL
	.2byte MUS_POKE_CENTER
	.2byte LAYOUT_POKEMON_CENTER_2F
	.byte MAPSEC_SEVEN_ISLAND
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SevenIsland_PokemonCenter_2F/header.inc =====
@ ===== BEGIN data/maps/SevenIsland_UnusedHouse/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SevenIsland_UnusedHouse/map.json
@

SevenIsland_UnusedHouse:
	.4byte House4_Layout
	.4byte SevenIsland_UnusedHouse_MapEvents
	.4byte SevenIsland_UnusedHouse_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_67
	.2byte LAYOUT_HOUSE4
	.byte MAPSEC_SEVEN_ISLAND
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SevenIsland_UnusedHouse/header.inc =====
@ ===== BEGIN data/maps/SevenIsland_Harbor/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SevenIsland_Harbor/map.json
@

SevenIsland_Harbor:
	.4byte Island_Harbor_Layout
	.4byte SevenIsland_Harbor_MapEvents
	.4byte SevenIsland_Harbor_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_67
	.2byte LAYOUT_ISLAND_HARBOR
	.byte MAPSEC_SEVEN_ISLAND
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SevenIsland_Harbor/header.inc =====
@ ===== BEGIN data/maps/OneIsland_PokemonCenter_1F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/OneIsland_PokemonCenter_1F/map.json
@

OneIsland_PokemonCenter_1F:
	.4byte OneIsland_PokemonCenter_1F_Layout
	.4byte OneIsland_PokemonCenter_1F_MapEvents
	.4byte OneIsland_PokemonCenter_1F_MapScripts
	.4byte NULL
	.2byte MUS_NET_CENTER
	.2byte LAYOUT_ONE_ISLAND_POKEMON_CENTER_1F
	.byte MAPSEC_ONE_ISLAND
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/OneIsland_PokemonCenter_1F/header.inc =====
@ ===== BEGIN data/maps/OneIsland_PokemonCenter_2F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/OneIsland_PokemonCenter_2F/map.json
@

OneIsland_PokemonCenter_2F:
	.4byte OneIsland_PokemonCenter_2F_Layout
	.4byte OneIsland_PokemonCenter_2F_MapEvents
	.4byte OneIsland_PokemonCenter_2F_MapScripts
	.4byte NULL
	.2byte MUS_NET_CENTER
	.2byte LAYOUT_ONE_ISLAND_POKEMON_CENTER_2F
	.byte MAPSEC_ONE_ISLAND
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/OneIsland_PokemonCenter_2F/header.inc =====
@ ===== BEGIN data/maps/OneIsland_House1/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/OneIsland_House1/map.json
@

OneIsland_House1:
	.4byte House3_Layout
	.4byte OneIsland_House1_MapEvents
	.4byte OneIsland_House1_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_123
	.2byte LAYOUT_HOUSE3
	.byte MAPSEC_ONE_ISLAND
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/OneIsland_House1/header.inc =====
@ ===== BEGIN data/maps/OneIsland_House2/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/OneIsland_House2/map.json
@

OneIsland_House2:
	.4byte House3_Layout
	.4byte OneIsland_House2_MapEvents
	.4byte OneIsland_House2_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_123
	.2byte LAYOUT_HOUSE3
	.byte MAPSEC_ONE_ISLAND
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/OneIsland_House2/header.inc =====
@ ===== BEGIN data/maps/OneIsland_Harbor/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/OneIsland_Harbor/map.json
@

OneIsland_Harbor:
	.4byte Island_Harbor_Layout
	.4byte OneIsland_Harbor_MapEvents
	.4byte OneIsland_Harbor_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_123
	.2byte LAYOUT_ISLAND_HARBOR
	.byte MAPSEC_ONE_ISLAND
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/OneIsland_Harbor/header.inc =====
@ ===== BEGIN data/maps/TwoIsland_JoyfulGameCorner/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/TwoIsland_JoyfulGameCorner/map.json
@

TwoIsland_JoyfulGameCorner:
	.4byte TwoIsland_JoyfulGameCorner_Layout
	.4byte TwoIsland_JoyfulGameCorner_MapEvents
	.4byte TwoIsland_JoyfulGameCorner_MapScripts
	.4byte NULL
	.2byte MUS_GAME_CORNER
	.2byte LAYOUT_TWO_ISLAND_JOYFUL_GAME_CORNER
	.byte MAPSEC_TWO_ISLAND
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/TwoIsland_JoyfulGameCorner/header.inc =====
@ ===== BEGIN data/maps/TwoIsland_House/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/TwoIsland_House/map.json
@

TwoIsland_House:
	.4byte House3_Layout
	.4byte TwoIsland_House_MapEvents
	.4byte TwoIsland_House_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_123
	.2byte LAYOUT_HOUSE3
	.byte MAPSEC_TWO_ISLAND
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/TwoIsland_House/header.inc =====
@ ===== BEGIN data/maps/TwoIsland_PokemonCenter_1F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/TwoIsland_PokemonCenter_1F/map.json
@

TwoIsland_PokemonCenter_1F:
	.4byte PokemonCenter_1F_Layout
	.4byte TwoIsland_PokemonCenter_1F_MapEvents
	.4byte TwoIsland_PokemonCenter_1F_MapScripts
	.4byte NULL
	.2byte MUS_POKE_CENTER
	.2byte LAYOUT_POKEMON_CENTER_1F
	.byte MAPSEC_TWO_ISLAND
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/TwoIsland_PokemonCenter_1F/header.inc =====
@ ===== BEGIN data/maps/TwoIsland_PokemonCenter_2F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/TwoIsland_PokemonCenter_2F/map.json
@

TwoIsland_PokemonCenter_2F:
	.4byte PokemonCenter_2F_Layout
	.4byte TwoIsland_PokemonCenter_2F_MapEvents
	.4byte TwoIsland_PokemonCenter_2F_MapScripts
	.4byte NULL
	.2byte MUS_POKE_CENTER
	.2byte LAYOUT_POKEMON_CENTER_2F
	.byte MAPSEC_TWO_ISLAND
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/TwoIsland_PokemonCenter_2F/header.inc =====
@ ===== BEGIN data/maps/TwoIsland_Harbor/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/TwoIsland_Harbor/map.json
@

TwoIsland_Harbor:
	.4byte Island_Harbor_Layout
	.4byte TwoIsland_Harbor_MapEvents
	.4byte TwoIsland_Harbor_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_123
	.2byte LAYOUT_ISLAND_HARBOR
	.byte MAPSEC_TWO_ISLAND
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/TwoIsland_Harbor/header.inc =====
@ ===== BEGIN data/maps/ThreeIsland_House1/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/ThreeIsland_House1/map.json
@

ThreeIsland_House1:
	.4byte ThreeIsland_House1_Layout
	.4byte ThreeIsland_House1_MapEvents
	.4byte ThreeIsland_House1_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_123
	.2byte LAYOUT_THREE_ISLAND_HOUSE1
	.byte MAPSEC_THREE_ISLAND
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/ThreeIsland_House1/header.inc =====
@ ===== BEGIN data/maps/ThreeIsland_PokemonCenter_1F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/ThreeIsland_PokemonCenter_1F/map.json
@

ThreeIsland_PokemonCenter_1F:
	.4byte PokemonCenter_1F_Layout
	.4byte ThreeIsland_PokemonCenter_1F_MapEvents
	.4byte ThreeIsland_PokemonCenter_1F_MapScripts
	.4byte NULL
	.2byte MUS_POKE_CENTER
	.2byte LAYOUT_POKEMON_CENTER_1F
	.byte MAPSEC_THREE_ISLAND
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/ThreeIsland_PokemonCenter_1F/header.inc =====
@ ===== BEGIN data/maps/ThreeIsland_PokemonCenter_2F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/ThreeIsland_PokemonCenter_2F/map.json
@

ThreeIsland_PokemonCenter_2F:
	.4byte PokemonCenter_2F_Layout
	.4byte ThreeIsland_PokemonCenter_2F_MapEvents
	.4byte ThreeIsland_PokemonCenter_2F_MapScripts
	.4byte NULL
	.2byte MUS_POKE_CENTER
	.2byte LAYOUT_POKEMON_CENTER_2F
	.byte MAPSEC_THREE_ISLAND
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/ThreeIsland_PokemonCenter_2F/header.inc =====
@ ===== BEGIN data/maps/ThreeIsland_Mart/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/ThreeIsland_Mart/map.json
@

ThreeIsland_Mart:
	.4byte Mart_Layout
	.4byte ThreeIsland_Mart_MapEvents
	.4byte ThreeIsland_Mart_MapScripts
	.4byte NULL
	.2byte MUS_POKE_CENTER
	.2byte LAYOUT_MART
	.byte MAPSEC_THREE_ISLAND
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/ThreeIsland_Mart/header.inc =====
@ ===== BEGIN data/maps/ThreeIsland_House2/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/ThreeIsland_House2/map.json
@

ThreeIsland_House2:
	.4byte House3_Layout
	.4byte ThreeIsland_House2_MapEvents
	.4byte ThreeIsland_House2_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_123
	.2byte LAYOUT_HOUSE3
	.byte MAPSEC_THREE_ISLAND
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/ThreeIsland_House2/header.inc =====
@ ===== BEGIN data/maps/ThreeIsland_House3/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/ThreeIsland_House3/map.json
@

ThreeIsland_House3:
	.4byte House3_Layout
	.4byte ThreeIsland_House3_MapEvents
	.4byte ThreeIsland_House3_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_123
	.2byte LAYOUT_HOUSE3
	.byte MAPSEC_THREE_ISLAND
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/ThreeIsland_House3/header.inc =====
@ ===== BEGIN data/maps/ThreeIsland_House4/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/ThreeIsland_House4/map.json
@

ThreeIsland_House4:
	.4byte House3_Layout
	.4byte ThreeIsland_House4_MapEvents
	.4byte ThreeIsland_House4_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_123
	.2byte LAYOUT_HOUSE3
	.byte MAPSEC_THREE_ISLAND
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/ThreeIsland_House4/header.inc =====
@ ===== BEGIN data/maps/ThreeIsland_House5/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/ThreeIsland_House5/map.json
@

ThreeIsland_House5:
	.4byte House3_Layout
	.4byte ThreeIsland_House5_MapEvents
	.4byte ThreeIsland_House5_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_123
	.2byte LAYOUT_HOUSE3
	.byte MAPSEC_THREE_ISLAND
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/ThreeIsland_House5/header.inc =====
@ ===== BEGIN data/maps/FourIsland_PokemonDayCare/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FourIsland_PokemonDayCare/map.json
@

FourIsland_PokemonDayCare:
	.4byte FourIsland_PokemonDayCare_Layout
	.4byte FourIsland_PokemonDayCare_MapEvents
	.4byte FourIsland_PokemonDayCare_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_45
	.2byte LAYOUT_FOUR_ISLAND_POKEMON_DAY_CARE
	.byte MAPSEC_FOUR_ISLAND
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/FourIsland_PokemonDayCare/header.inc =====
@ ===== BEGIN data/maps/FourIsland_PokemonCenter_1F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FourIsland_PokemonCenter_1F/map.json
@

FourIsland_PokemonCenter_1F:
	.4byte PokemonCenter_1F_Layout
	.4byte FourIsland_PokemonCenter_1F_MapEvents
	.4byte FourIsland_PokemonCenter_1F_MapScripts
	.4byte NULL
	.2byte MUS_POKE_CENTER
	.2byte LAYOUT_POKEMON_CENTER_1F
	.byte MAPSEC_FOUR_ISLAND
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/FourIsland_PokemonCenter_1F/header.inc =====
@ ===== BEGIN data/maps/FourIsland_PokemonCenter_2F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FourIsland_PokemonCenter_2F/map.json
@

FourIsland_PokemonCenter_2F:
	.4byte PokemonCenter_2F_Layout
	.4byte FourIsland_PokemonCenter_2F_MapEvents
	.4byte FourIsland_PokemonCenter_2F_MapScripts
	.4byte NULL
	.2byte MUS_POKE_CENTER
	.2byte LAYOUT_POKEMON_CENTER_2F
	.byte MAPSEC_FOUR_ISLAND
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/FourIsland_PokemonCenter_2F/header.inc =====
@ ===== BEGIN data/maps/FourIsland_House1/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FourIsland_House1/map.json
@

FourIsland_House1:
	.4byte House3_Layout
	.4byte FourIsland_House1_MapEvents
	.4byte FourIsland_House1_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_45
	.2byte LAYOUT_HOUSE3
	.byte MAPSEC_FOUR_ISLAND
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/FourIsland_House1/header.inc =====
@ ===== BEGIN data/maps/FourIsland_LoreleisHouse/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FourIsland_LoreleisHouse/map.json
@

FourIsland_LoreleisHouse:
	.4byte FourIsland_LoreleisHouse_Layout
	.4byte FourIsland_LoreleisHouse_MapEvents
	.4byte FourIsland_LoreleisHouse_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_45
	.2byte LAYOUT_FOUR_ISLAND_LORELEIS_HOUSE
	.byte MAPSEC_FOUR_ISLAND
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/FourIsland_LoreleisHouse/header.inc =====
@ ===== BEGIN data/maps/FourIsland_Harbor/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FourIsland_Harbor/map.json
@

FourIsland_Harbor:
	.4byte Island_Harbor_Layout
	.4byte FourIsland_Harbor_MapEvents
	.4byte FourIsland_Harbor_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_45
	.2byte LAYOUT_ISLAND_HARBOR
	.byte MAPSEC_FOUR_ISLAND
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/FourIsland_Harbor/header.inc =====
@ ===== BEGIN data/maps/FourIsland_House2/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FourIsland_House2/map.json
@

FourIsland_House2:
	.4byte House3_Layout
	.4byte FourIsland_House2_MapEvents
	.4byte FourIsland_House2_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_45
	.2byte LAYOUT_HOUSE3
	.byte MAPSEC_FOUR_ISLAND
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/FourIsland_House2/header.inc =====
@ ===== BEGIN data/maps/FourIsland_Mart/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FourIsland_Mart/map.json
@

FourIsland_Mart:
	.4byte Mart_Layout
	.4byte FourIsland_Mart_MapEvents
	.4byte FourIsland_Mart_MapScripts
	.4byte NULL
	.2byte MUS_POKE_CENTER
	.2byte LAYOUT_MART
	.byte MAPSEC_FOUR_ISLAND
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/FourIsland_Mart/header.inc =====
@ ===== BEGIN data/maps/FiveIsland_PokemonCenter_1F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FiveIsland_PokemonCenter_1F/map.json
@

FiveIsland_PokemonCenter_1F:
	.4byte PokemonCenter_1F_Layout
	.4byte FiveIsland_PokemonCenter_1F_MapEvents
	.4byte FiveIsland_PokemonCenter_1F_MapScripts
	.4byte NULL
	.2byte MUS_POKE_CENTER
	.2byte LAYOUT_POKEMON_CENTER_1F
	.byte MAPSEC_FIVE_ISLAND
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/FiveIsland_PokemonCenter_1F/header.inc =====
@ ===== BEGIN data/maps/FiveIsland_PokemonCenter_2F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FiveIsland_PokemonCenter_2F/map.json
@

FiveIsland_PokemonCenter_2F:
	.4byte PokemonCenter_2F_Layout
	.4byte FiveIsland_PokemonCenter_2F_MapEvents
	.4byte FiveIsland_PokemonCenter_2F_MapScripts
	.4byte NULL
	.2byte MUS_POKE_CENTER
	.2byte LAYOUT_POKEMON_CENTER_2F
	.byte MAPSEC_FIVE_ISLAND
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/FiveIsland_PokemonCenter_2F/header.inc =====
@ ===== BEGIN data/maps/FiveIsland_Harbor/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FiveIsland_Harbor/map.json
@

FiveIsland_Harbor:
	.4byte Island_Harbor_Layout
	.4byte FiveIsland_Harbor_MapEvents
	.4byte FiveIsland_Harbor_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_45
	.2byte LAYOUT_ISLAND_HARBOR
	.byte MAPSEC_FIVE_ISLAND
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/FiveIsland_Harbor/header.inc =====
@ ===== BEGIN data/maps/FiveIsland_House1/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FiveIsland_House1/map.json
@

FiveIsland_House1:
	.4byte House3_Layout
	.4byte FiveIsland_House1_MapEvents
	.4byte FiveIsland_House1_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_45
	.2byte LAYOUT_HOUSE3
	.byte MAPSEC_FIVE_ISLAND
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/FiveIsland_House1/header.inc =====
@ ===== BEGIN data/maps/FiveIsland_House2/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FiveIsland_House2/map.json
@

FiveIsland_House2:
	.4byte House3_Layout
	.4byte FiveIsland_House2_MapEvents
	.4byte FiveIsland_House2_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_45
	.2byte LAYOUT_HOUSE3
	.byte MAPSEC_FIVE_ISLAND
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/FiveIsland_House2/header.inc =====
@ ===== BEGIN data/maps/SixIsland_PokemonCenter_1F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SixIsland_PokemonCenter_1F/map.json
@

SixIsland_PokemonCenter_1F:
	.4byte PokemonCenter_1F_Layout
	.4byte SixIsland_PokemonCenter_1F_MapEvents
	.4byte SixIsland_PokemonCenter_1F_MapScripts
	.4byte NULL
	.2byte MUS_POKE_CENTER
	.2byte LAYOUT_POKEMON_CENTER_1F
	.byte MAPSEC_SIX_ISLAND
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SixIsland_PokemonCenter_1F/header.inc =====
@ ===== BEGIN data/maps/SixIsland_PokemonCenter_2F/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SixIsland_PokemonCenter_2F/map.json
@

SixIsland_PokemonCenter_2F:
	.4byte PokemonCenter_2F_Layout
	.4byte SixIsland_PokemonCenter_2F_MapEvents
	.4byte SixIsland_PokemonCenter_2F_MapScripts
	.4byte NULL
	.2byte MUS_POKE_CENTER
	.2byte LAYOUT_POKEMON_CENTER_2F
	.byte MAPSEC_SIX_ISLAND
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SixIsland_PokemonCenter_2F/header.inc =====
@ ===== BEGIN data/maps/SixIsland_Harbor/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SixIsland_Harbor/map.json
@

SixIsland_Harbor:
	.4byte Island_Harbor_Layout
	.4byte SixIsland_Harbor_MapEvents
	.4byte SixIsland_Harbor_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_67
	.2byte LAYOUT_ISLAND_HARBOR
	.byte MAPSEC_SIX_ISLAND
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SixIsland_Harbor/header.inc =====
@ ===== BEGIN data/maps/SixIsland_House/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SixIsland_House/map.json
@

SixIsland_House:
	.4byte House3_Layout
	.4byte SixIsland_House_MapEvents
	.4byte SixIsland_House_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_67
	.2byte LAYOUT_HOUSE3
	.byte MAPSEC_SIX_ISLAND
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SixIsland_House/header.inc =====
@ ===== BEGIN data/maps/SixIsland_Mart/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SixIsland_Mart/map.json
@

SixIsland_Mart:
	.4byte Mart_Layout
	.4byte SixIsland_Mart_MapEvents
	.4byte SixIsland_Mart_MapScripts
	.4byte NULL
	.2byte MUS_POKE_CENTER
	.2byte LAYOUT_MART
	.byte MAPSEC_SIX_ISLAND
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SixIsland_Mart/header.inc =====
@ ===== BEGIN data/maps/ThreeIsland_Harbor/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/ThreeIsland_Harbor/map.json
@

ThreeIsland_Harbor:
	.4byte Island_Harbor_Layout
	.4byte ThreeIsland_Harbor_MapEvents
	.4byte ThreeIsland_Harbor_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_123
	.2byte LAYOUT_ISLAND_HARBOR
	.byte MAPSEC_THREE_ISLE_PORT
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/ThreeIsland_Harbor/header.inc =====
@ ===== BEGIN data/maps/FiveIsland_ResortGorgeous_House/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FiveIsland_ResortGorgeous_House/map.json
@

FiveIsland_ResortGorgeous_House:
	.4byte FiveIsland_ResortGorgeous_House_Layout
	.4byte FiveIsland_ResortGorgeous_House_MapEvents
	.4byte FiveIsland_ResortGorgeous_House_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_45
	.2byte LAYOUT_FIVE_ISLAND_RESORT_GORGEOUS_HOUSE
	.byte MAPSEC_RESORT_GORGEOUS
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/FiveIsland_ResortGorgeous_House/header.inc =====
@ ===== BEGIN data/maps/TwoIsland_CapeBrink_House/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/TwoIsland_CapeBrink_House/map.json
@

TwoIsland_CapeBrink_House:
	.4byte House3_Layout
	.4byte TwoIsland_CapeBrink_House_MapEvents
	.4byte TwoIsland_CapeBrink_House_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_123
	.2byte LAYOUT_HOUSE3
	.byte MAPSEC_CAPE_BRINK
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/TwoIsland_CapeBrink_House/header.inc =====
@ ===== BEGIN data/maps/SixIsland_WaterPath_House1/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SixIsland_WaterPath_House1/map.json
@

SixIsland_WaterPath_House1:
	.4byte House4_Layout
	.4byte SixIsland_WaterPath_House1_MapEvents
	.4byte SixIsland_WaterPath_House1_MapScripts
	.4byte NULL
	.2byte MUS_FUCHSIA
	.2byte LAYOUT_HOUSE4
	.byte MAPSEC_WATER_PATH
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SixIsland_WaterPath_House1/header.inc =====
@ ===== BEGIN data/maps/SixIsland_WaterPath_House2/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SixIsland_WaterPath_House2/map.json
@

SixIsland_WaterPath_House2:
	.4byte House3_Layout
	.4byte SixIsland_WaterPath_House2_MapEvents
	.4byte SixIsland_WaterPath_House2_MapScripts
	.4byte NULL
	.2byte MUS_FUCHSIA
	.2byte LAYOUT_HOUSE3
	.byte MAPSEC_WATER_PATH
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SixIsland_WaterPath_House2/header.inc =====
@ ===== BEGIN data/maps/SevenIsland_SevaultCanyon_House/header.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SevenIsland_SevaultCanyon_House/map.json
@

SevenIsland_SevaultCanyon_House:
	.4byte House3_Layout
	.4byte SevenIsland_SevaultCanyon_House_MapEvents
	.4byte SevenIsland_SevaultCanyon_House_MapScripts
	.4byte NULL
	.2byte MUS_SEVII_67
	.2byte LAYOUT_HOUSE3
	.byte MAPSEC_SEVAULT_CANYON
	.byte FALSE
	.byte WEATHER_NONE
	.byte MAP_TYPE_INDOOR
	map_header_flags allow_cycling=FALSE, allow_escaping=FALSE, allow_running=FALSE, show_map_name=FALSE
	.byte 0
	.byte MAP_BATTLE_SCENE_NORMAL

@ ===== END data/maps/SevenIsland_SevaultCanyon_House/header.inc =====
@ ===== END data/maps/headers.inc =====
@ ===== BEGIN data/maps/groups.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/map_groups.json
@

gMapGroup_Link::
	.4byte BattleColosseum_2P
	.4byte TradeCenter
	.4byte RecordCorner
	.4byte BattleColosseum_4P
	.4byte UnionRoom

gMapGroup_Dungeons::
	.4byte ViridianForest
	.4byte MtMoon_1F
	.4byte MtMoon_B1F
	.4byte MtMoon_B2F
	.4byte SSAnne_Exterior
	.4byte SSAnne_1F_Corridor
	.4byte SSAnne_2F_Corridor
	.4byte SSAnne_3F_Corridor
	.4byte SSAnne_B1F_Corridor
	.4byte SSAnne_Deck
	.4byte SSAnne_Kitchen
	.4byte SSAnne_CaptainsOffice
	.4byte SSAnne_1F_Room1
	.4byte SSAnne_1F_Room2
	.4byte SSAnne_1F_Room3
	.4byte SSAnne_1F_Room4
	.4byte SSAnne_1F_Room5
	.4byte SSAnne_1F_Room7
	.4byte SSAnne_2F_Room1
	.4byte SSAnne_2F_Room2
	.4byte SSAnne_2F_Room3
	.4byte SSAnne_2F_Room4
	.4byte SSAnne_2F_Room5
	.4byte SSAnne_2F_Room6
	.4byte SSAnne_B1F_Room1
	.4byte SSAnne_B1F_Room2
	.4byte SSAnne_B1F_Room3
	.4byte SSAnne_B1F_Room4
	.4byte SSAnne_B1F_Room5
	.4byte SSAnne_1F_Room6
	.4byte UndergroundPath_NorthEntrance
	.4byte UndergroundPath_NorthSouthTunnel
	.4byte UndergroundPath_SouthEntrance
	.4byte UndergroundPath_WestEntrance
	.4byte UndergroundPath_EastWestTunnel
	.4byte UndergroundPath_EastEntrance
	.4byte DiglettsCave_NorthEntrance
	.4byte DiglettsCave_B1F
	.4byte DiglettsCave_SouthEntrance
	.4byte VictoryRoad_1F
	.4byte VictoryRoad_2F
	.4byte VictoryRoad_3F
	.4byte RocketHideout_B1F
	.4byte RocketHideout_B2F
	.4byte RocketHideout_B3F
	.4byte RocketHideout_B4F
	.4byte RocketHideout_Elevator
	.4byte SilphCo_1F
	.4byte SilphCo_2F
	.4byte SilphCo_3F
	.4byte SilphCo_4F
	.4byte SilphCo_5F
	.4byte SilphCo_6F
	.4byte SilphCo_7F
	.4byte SilphCo_8F
	.4byte SilphCo_9F
	.4byte SilphCo_10F
	.4byte SilphCo_11F
	.4byte SilphCo_Elevator
	.4byte PokemonMansion_1F
	.4byte PokemonMansion_2F
	.4byte PokemonMansion_3F
	.4byte PokemonMansion_B1F
	.4byte SafariZone_Center
	.4byte SafariZone_East
	.4byte SafariZone_North
	.4byte SafariZone_West
	.4byte SafariZone_Center_RestHouse
	.4byte SafariZone_East_RestHouse
	.4byte SafariZone_North_RestHouse
	.4byte SafariZone_West_RestHouse
	.4byte SafariZone_SecretHouse
	.4byte CeruleanCave_1F
	.4byte CeruleanCave_2F
	.4byte CeruleanCave_B1F
	.4byte PokemonLeague_LoreleisRoom
	.4byte PokemonLeague_BrunosRoom
	.4byte PokemonLeague_AgathasRoom
	.4byte PokemonLeague_LancesRoom
	.4byte PokemonLeague_ChampionsRoom
	.4byte PokemonLeague_HallOfFame
	.4byte RockTunnel_1F
	.4byte RockTunnel_B1F
	.4byte SeafoamIslands_1F
	.4byte SeafoamIslands_B1F
	.4byte SeafoamIslands_B2F
	.4byte SeafoamIslands_B3F
	.4byte SeafoamIslands_B4F
	.4byte PokemonTower_1F
	.4byte PokemonTower_2F
	.4byte PokemonTower_3F
	.4byte PokemonTower_4F
	.4byte PokemonTower_5F
	.4byte PokemonTower_6F
	.4byte PokemonTower_7F
	.4byte PowerPlant
	.4byte MtEmber_RubyPath_B4F
	.4byte MtEmber_Exterior
	.4byte MtEmber_SummitPath_1F
	.4byte MtEmber_SummitPath_2F
	.4byte MtEmber_SummitPath_3F
	.4byte MtEmber_Summit
	.4byte MtEmber_RubyPath_B5F
	.4byte MtEmber_RubyPath_1F
	.4byte MtEmber_RubyPath_B1F
	.4byte MtEmber_RubyPath_B2F
	.4byte MtEmber_RubyPath_B3F
	.4byte MtEmber_RubyPath_B1F_Stairs
	.4byte MtEmber_RubyPath_B2F_Stairs
	.4byte ThreeIsland_BerryForest
	.4byte FourIsland_IcefallCave_Entrance
	.4byte FourIsland_IcefallCave_1F
	.4byte FourIsland_IcefallCave_B1F
	.4byte FourIsland_IcefallCave_Back
	.4byte FiveIsland_RocketWarehouse
	.4byte SixIsland_DottedHole_1F
	.4byte SixIsland_DottedHole_B1F
	.4byte SixIsland_DottedHole_B2F
	.4byte SixIsland_DottedHole_B3F
	.4byte SixIsland_DottedHole_B4F
	.4byte SixIsland_DottedHole_SapphireRoom
	.4byte SixIsland_PatternBush
	.4byte SixIsland_AlteringCave

gMapGroup_SpecialArea::
	.4byte NavelRock_Exterior
	.4byte TrainerTower_1F
	.4byte TrainerTower_2F
	.4byte TrainerTower_3F
	.4byte TrainerTower_4F
	.4byte TrainerTower_5F
	.4byte TrainerTower_6F
	.4byte TrainerTower_7F
	.4byte TrainerTower_8F
	.4byte TrainerTower_Roof
	.4byte TrainerTower_Lobby
	.4byte TrainerTower_Elevator
	.4byte FiveIsland_LostCave_Entrance
	.4byte FiveIsland_LostCave_Room1
	.4byte FiveIsland_LostCave_Room2
	.4byte FiveIsland_LostCave_Room3
	.4byte FiveIsland_LostCave_Room4
	.4byte FiveIsland_LostCave_Room5
	.4byte FiveIsland_LostCave_Room6
	.4byte FiveIsland_LostCave_Room7
	.4byte FiveIsland_LostCave_Room8
	.4byte FiveIsland_LostCave_Room9
	.4byte FiveIsland_LostCave_Room10
	.4byte FiveIsland_LostCave_Room11
	.4byte FiveIsland_LostCave_Room12
	.4byte FiveIsland_LostCave_Room13
	.4byte FiveIsland_LostCave_Room14
	.4byte SevenIsland_TanobyRuins_MoneanChamber
	.4byte SevenIsland_TanobyRuins_LiptooChamber
	.4byte SevenIsland_TanobyRuins_WeepthChamber
	.4byte SevenIsland_TanobyRuins_DilfordChamber
	.4byte SevenIsland_TanobyRuins_ScufibChamber
	.4byte SevenIsland_TanobyRuins_RixyChamber
	.4byte SevenIsland_TanobyRuins_ViapoisChamber
	.4byte ThreeIsland_DunsparceTunnel
	.4byte SevenIsland_SevaultCanyon_TanobyKey
	.4byte NavelRock_1F
	.4byte NavelRock_Summit
	.4byte NavelRock_Base
	.4byte NavelRock_SummitPath_2F
	.4byte NavelRock_SummitPath_3F
	.4byte NavelRock_SummitPath_4F
	.4byte NavelRock_SummitPath_5F
	.4byte NavelRock_BasePath_B1F
	.4byte NavelRock_BasePath_B2F
	.4byte NavelRock_BasePath_B3F
	.4byte NavelRock_BasePath_B4F
	.4byte NavelRock_BasePath_B5F
	.4byte NavelRock_BasePath_B6F
	.4byte NavelRock_BasePath_B7F
	.4byte NavelRock_BasePath_B8F
	.4byte NavelRock_BasePath_B9F
	.4byte NavelRock_BasePath_B10F
	.4byte NavelRock_BasePath_B11F
	.4byte NavelRock_B1F
	.4byte NavelRock_Fork
	.4byte BirthIsland_Exterior
	.4byte OneIsland_KindleRoad_EmberSpa
	.4byte BirthIsland_Harbor
	.4byte NavelRock_Harbor

gMapGroup_TownsAndRoutes::
	.4byte PalletTown
	.4byte ViridianCity
	.4byte PewterCity
	.4byte CeruleanCity
	.4byte LavenderTown
	.4byte VermilionCity
	.4byte CeladonCity
	.4byte FuchsiaCity
	.4byte CinnabarIsland
	.4byte IndigoPlateau_Exterior
	.4byte SaffronCity
	.4byte SaffronCity_Connection
	.4byte OneIsland
	.4byte TwoIsland
	.4byte ThreeIsland
	.4byte FourIsland
	.4byte FiveIsland
	.4byte SevenIsland
	.4byte SixIsland
	.4byte Route1
	.4byte Route2
	.4byte Route3
	.4byte Route4
	.4byte Route5
	.4byte Route6
	.4byte Route7
	.4byte Route8
	.4byte Route9
	.4byte Route10
	.4byte Route11
	.4byte Route12
	.4byte Route13
	.4byte Route14
	.4byte Route15
	.4byte Route16
	.4byte Route17
	.4byte Route18
	.4byte Route19
	.4byte Route20
	.4byte Route21_North
	.4byte Route21_South
	.4byte Route22
	.4byte Route23
	.4byte Route24
	.4byte Route25
	.4byte OneIsland_KindleRoad
	.4byte OneIsland_TreasureBeach
	.4byte TwoIsland_CapeBrink
	.4byte ThreeIsland_BondBridge
	.4byte ThreeIsland_Port
	.4byte Prototype_SeviiIsle_6
	.4byte Prototype_SeviiIsle_7
	.4byte Prototype_SeviiIsle_8
	.4byte Prototype_SeviiIsle_9
	.4byte FiveIsland_ResortGorgeous
	.4byte FiveIsland_WaterLabyrinth
	.4byte FiveIsland_Meadow
	.4byte FiveIsland_MemorialPillar
	.4byte SixIsland_OutcastIsland
	.4byte SixIsland_GreenPath
	.4byte SixIsland_WaterPath
	.4byte SixIsland_RuinValley
	.4byte SevenIsland_TrainerTower
	.4byte SevenIsland_SevaultCanyon_Entrance
	.4byte SevenIsland_SevaultCanyon
	.4byte SevenIsland_TanobyRuins

gMapGroup_IndoorPallet::
	.4byte PalletTown_PlayersHouse_1F
	.4byte PalletTown_PlayersHouse_2F
	.4byte PalletTown_RivalsHouse
	.4byte PalletTown_ProfessorOaksLab

gMapGroup_IndoorViridian::
	.4byte ViridianCity_House
	.4byte ViridianCity_Gym
	.4byte ViridianCity_School
	.4byte ViridianCity_Mart
	.4byte ViridianCity_PokemonCenter_1F
	.4byte ViridianCity_PokemonCenter_2F

gMapGroup_IndoorPewter::
	.4byte PewterCity_Museum_1F
	.4byte PewterCity_Museum_2F
	.4byte PewterCity_Gym
	.4byte PewterCity_Mart
	.4byte PewterCity_House1
	.4byte PewterCity_PokemonCenter_1F
	.4byte PewterCity_PokemonCenter_2F
	.4byte PewterCity_House2

gMapGroup_IndoorCerulean::
	.4byte CeruleanCity_House1
	.4byte CeruleanCity_House2
	.4byte CeruleanCity_House3
	.4byte CeruleanCity_PokemonCenter_1F
	.4byte CeruleanCity_PokemonCenter_2F
	.4byte CeruleanCity_Gym
	.4byte CeruleanCity_BikeShop
	.4byte CeruleanCity_Mart
	.4byte CeruleanCity_House4
	.4byte CeruleanCity_House5

gMapGroup_IndoorLavender::
	.4byte LavenderTown_PokemonCenter_1F
	.4byte LavenderTown_PokemonCenter_2F
	.4byte LavenderTown_VolunteerPokemonHouse
	.4byte LavenderTown_House1
	.4byte LavenderTown_House2
	.4byte LavenderTown_Mart

gMapGroup_IndoorVermilion::
	.4byte VermilionCity_House1
	.4byte VermilionCity_PokemonCenter_1F
	.4byte VermilionCity_PokemonCenter_2F
	.4byte VermilionCity_PokemonFanClub
	.4byte VermilionCity_House2
	.4byte VermilionCity_Mart
	.4byte VermilionCity_Gym
	.4byte VermilionCity_House3

gMapGroup_IndoorCeladon::
	.4byte CeladonCity_DepartmentStore_1F
	.4byte CeladonCity_DepartmentStore_2F
	.4byte CeladonCity_DepartmentStore_3F
	.4byte CeladonCity_DepartmentStore_4F
	.4byte CeladonCity_DepartmentStore_5F
	.4byte CeladonCity_DepartmentStore_Roof
	.4byte CeladonCity_DepartmentStore_Elevator
	.4byte CeladonCity_Condominiums_1F
	.4byte CeladonCity_Condominiums_2F
	.4byte CeladonCity_Condominiums_3F
	.4byte CeladonCity_Condominiums_Roof
	.4byte CeladonCity_Condominiums_RoofRoom
	.4byte CeladonCity_PokemonCenter_1F
	.4byte CeladonCity_PokemonCenter_2F
	.4byte CeladonCity_GameCorner
	.4byte CeladonCity_GameCorner_PrizeRoom
	.4byte CeladonCity_Gym
	.4byte CeladonCity_Restaurant
	.4byte CeladonCity_House1
	.4byte CeladonCity_Hotel

gMapGroup_IndoorFuchsia::
	.4byte FuchsiaCity_SafariZone_Entrance
	.4byte FuchsiaCity_Mart
	.4byte FuchsiaCity_SafariZone_Office
	.4byte FuchsiaCity_Gym
	.4byte FuchsiaCity_House1
	.4byte FuchsiaCity_PokemonCenter_1F
	.4byte FuchsiaCity_PokemonCenter_2F
	.4byte FuchsiaCity_WardensHouse
	.4byte FuchsiaCity_House2
	.4byte FuchsiaCity_House3

gMapGroup_IndoorCinnabar::
	.4byte CinnabarIsland_Gym
	.4byte CinnabarIsland_PokemonLab_Entrance
	.4byte CinnabarIsland_PokemonLab_Lounge
	.4byte CinnabarIsland_PokemonLab_ResearchRoom
	.4byte CinnabarIsland_PokemonLab_ExperimentRoom
	.4byte CinnabarIsland_PokemonCenter_1F
	.4byte CinnabarIsland_PokemonCenter_2F
	.4byte CinnabarIsland_Mart

gMapGroup_IndoorIndigoPlateau::
	.4byte IndigoPlateau_PokemonCenter_1F
	.4byte IndigoPlateau_PokemonCenter_2F

gMapGroup_IndoorSaffron::
	.4byte SaffronCity_CopycatsHouse_1F
	.4byte SaffronCity_CopycatsHouse_2F
	.4byte SaffronCity_Dojo
	.4byte SaffronCity_Gym
	.4byte SaffronCity_House
	.4byte SaffronCity_Mart
	.4byte SaffronCity_PokemonCenter_1F
	.4byte SaffronCity_PokemonCenter_2F
	.4byte SaffronCity_MrPsychicsHouse
	.4byte SaffronCity_PokemonTrainerFanClub

gMapGroup_IndoorRoute2::
	.4byte Route2_ViridianForest_SouthEntrance
	.4byte Route2_House
	.4byte Route2_EastBuilding
	.4byte Route2_ViridianForest_NorthEntrance

gMapGroup_IndoorRoute4::
	.4byte Route4_PokemonCenter_1F
	.4byte Route4_PokemonCenter_2F

gMapGroup_IndoorRoute5::
	.4byte Route5_PokemonDayCare
	.4byte Route5_SouthEntrance

gMapGroup_IndoorRoute6::
	.4byte Route6_NorthEntrance
	.4byte Route6_UnusedHouse

gMapGroup_IndoorRoute7::
	.4byte Route7_EastEntrance

gMapGroup_IndoorRoute8::
	.4byte Route8_WestEntrance

gMapGroup_IndoorRoute10::
	.4byte Route10_PokemonCenter_1F
	.4byte Route10_PokemonCenter_2F

gMapGroup_IndoorRoute11::
	.4byte Route11_EastEntrance_1F
	.4byte Route11_EastEntrance_2F

gMapGroup_IndoorRoute12::
	.4byte Route12_NorthEntrance_1F
	.4byte Route12_NorthEntrance_2F
	.4byte Route12_FishingHouse

gMapGroup_IndoorRoute15::
	.4byte Route15_WestEntrance_1F
	.4byte Route15_WestEntrance_2F

gMapGroup_IndoorRoute16::
	.4byte Route16_House
	.4byte Route16_NorthEntrance_1F
	.4byte Route16_NorthEntrance_2F

gMapGroup_IndoorRoute18::
	.4byte Route18_EastEntrance_1F
	.4byte Route18_EastEntrance_2F

gMapGroup_IndoorRoute19::
	.4byte Route19_UnusedHouse

gMapGroup_IndoorRoute22::
	.4byte Route22_NorthEntrance

gMapGroup_IndoorRoute23::
	.4byte Route23_UnusedHouse

gMapGroup_IndoorRoute25::
	.4byte Route25_SeaCottage

gMapGroup_IndoorSevenIsland::
	.4byte SevenIsland_House_Room1
	.4byte SevenIsland_House_Room2
	.4byte SevenIsland_Mart
	.4byte SevenIsland_PokemonCenter_1F
	.4byte SevenIsland_PokemonCenter_2F
	.4byte SevenIsland_UnusedHouse
	.4byte SevenIsland_Harbor

gMapGroup_IndoorOneIsland::
	.4byte OneIsland_PokemonCenter_1F
	.4byte OneIsland_PokemonCenter_2F
	.4byte OneIsland_House1
	.4byte OneIsland_House2
	.4byte OneIsland_Harbor

gMapGroup_IndoorTwoIsland::
	.4byte TwoIsland_JoyfulGameCorner
	.4byte TwoIsland_House
	.4byte TwoIsland_PokemonCenter_1F
	.4byte TwoIsland_PokemonCenter_2F
	.4byte TwoIsland_Harbor

gMapGroup_IndoorThreeIsland::
	.4byte ThreeIsland_House1
	.4byte ThreeIsland_PokemonCenter_1F
	.4byte ThreeIsland_PokemonCenter_2F
	.4byte ThreeIsland_Mart
	.4byte ThreeIsland_House2
	.4byte ThreeIsland_House3
	.4byte ThreeIsland_House4
	.4byte ThreeIsland_House5

gMapGroup_IndoorFourIsland::
	.4byte FourIsland_PokemonDayCare
	.4byte FourIsland_PokemonCenter_1F
	.4byte FourIsland_PokemonCenter_2F
	.4byte FourIsland_House1
	.4byte FourIsland_LoreleisHouse
	.4byte FourIsland_Harbor
	.4byte FourIsland_House2
	.4byte FourIsland_Mart

gMapGroup_IndoorFiveIsland::
	.4byte FiveIsland_PokemonCenter_1F
	.4byte FiveIsland_PokemonCenter_2F
	.4byte FiveIsland_Harbor
	.4byte FiveIsland_House1
	.4byte FiveIsland_House2

gMapGroup_IndoorSixIsland::
	.4byte SixIsland_PokemonCenter_1F
	.4byte SixIsland_PokemonCenter_2F
	.4byte SixIsland_Harbor
	.4byte SixIsland_House
	.4byte SixIsland_Mart

gMapGroup_IndoorThreeIslandRoute::
	.4byte ThreeIsland_Harbor

gMapGroup_IndoorFiveIslandRoute::
	.4byte FiveIsland_ResortGorgeous_House

gMapGroup_IndoorTwoIslandRoute::
	.4byte TwoIsland_CapeBrink_House

gMapGroup_IndoorSixIslandRoute::
	.4byte SixIsland_WaterPath_House1
	.4byte SixIsland_WaterPath_House2

gMapGroup_IndoorSevenIslandRoute::
	.4byte SevenIsland_SevaultCanyon_House

	.align 2
gMapGroups::
	.4byte gMapGroup_Link
	.4byte gMapGroup_Dungeons
	.4byte gMapGroup_SpecialArea
	.4byte gMapGroup_TownsAndRoutes
	.4byte gMapGroup_IndoorPallet
	.4byte gMapGroup_IndoorViridian
	.4byte gMapGroup_IndoorPewter
	.4byte gMapGroup_IndoorCerulean
	.4byte gMapGroup_IndoorLavender
	.4byte gMapGroup_IndoorVermilion
	.4byte gMapGroup_IndoorCeladon
	.4byte gMapGroup_IndoorFuchsia
	.4byte gMapGroup_IndoorCinnabar
	.4byte gMapGroup_IndoorIndigoPlateau
	.4byte gMapGroup_IndoorSaffron
	.4byte gMapGroup_IndoorRoute2
	.4byte gMapGroup_IndoorRoute4
	.4byte gMapGroup_IndoorRoute5
	.4byte gMapGroup_IndoorRoute6
	.4byte gMapGroup_IndoorRoute7
	.4byte gMapGroup_IndoorRoute8
	.4byte gMapGroup_IndoorRoute10
	.4byte gMapGroup_IndoorRoute11
	.4byte gMapGroup_IndoorRoute12
	.4byte gMapGroup_IndoorRoute15
	.4byte gMapGroup_IndoorRoute16
	.4byte gMapGroup_IndoorRoute18
	.4byte gMapGroup_IndoorRoute19
	.4byte gMapGroup_IndoorRoute22
	.4byte gMapGroup_IndoorRoute23
	.4byte gMapGroup_IndoorRoute25
	.4byte gMapGroup_IndoorSevenIsland
	.4byte gMapGroup_IndoorOneIsland
	.4byte gMapGroup_IndoorTwoIsland
	.4byte gMapGroup_IndoorThreeIsland
	.4byte gMapGroup_IndoorFourIsland
	.4byte gMapGroup_IndoorFiveIsland
	.4byte gMapGroup_IndoorSixIsland
	.4byte gMapGroup_IndoorThreeIslandRoute
	.4byte gMapGroup_IndoorFiveIslandRoute
	.4byte gMapGroup_IndoorTwoIslandRoute
	.4byte gMapGroup_IndoorSixIslandRoute
	.4byte gMapGroup_IndoorSevenIslandRoute

@ ===== END data/maps/groups.inc =====
@ ===== BEGIN data/maps/connections.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/map_groups.json
@

@ ===== BEGIN data/maps/PalletTown/connections.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/PalletTown/map.json
@

PalletTown_MapConnectionsList:
	connection up, 0, MAP_ROUTE1
	connection down, 0, MAP_ROUTE21_NORTH

PalletTown_MapConnections:
	.4byte 2
	.4byte PalletTown_MapConnectionsList

@ ===== END data/maps/PalletTown/connections.inc =====
@ ===== BEGIN data/maps/ViridianCity/connections.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/ViridianCity/map.json
@

ViridianCity_MapConnectionsList:
	connection up, 12, MAP_ROUTE2
	connection down, 12, MAP_ROUTE1
	connection left, 10, MAP_ROUTE22

ViridianCity_MapConnections:
	.4byte 3
	.4byte ViridianCity_MapConnectionsList

@ ===== END data/maps/ViridianCity/connections.inc =====
@ ===== BEGIN data/maps/PewterCity/connections.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/PewterCity/map.json
@

PewterCity_MapConnectionsList:
	connection down, 12, MAP_ROUTE2
	connection right, 10, MAP_ROUTE3

PewterCity_MapConnections:
	.4byte 2
	.4byte PewterCity_MapConnectionsList

@ ===== END data/maps/PewterCity/connections.inc =====
@ ===== BEGIN data/maps/CeruleanCity/connections.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/CeruleanCity/map.json
@

CeruleanCity_MapConnectionsList:
	connection up, 12, MAP_ROUTE24
	connection down, 0, MAP_ROUTE5
	connection left, 10, MAP_ROUTE4
	connection right, 10, MAP_ROUTE9

CeruleanCity_MapConnections:
	.4byte 4
	.4byte CeruleanCity_MapConnectionsList

@ ===== END data/maps/CeruleanCity/connections.inc =====
@ ===== BEGIN data/maps/LavenderTown/connections.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/LavenderTown/map.json
@

LavenderTown_MapConnectionsList:
	connection up, 0, MAP_ROUTE10
	connection down, 0, MAP_ROUTE12
	connection left, 0, MAP_ROUTE8

LavenderTown_MapConnections:
	.4byte 3
	.4byte LavenderTown_MapConnectionsList

@ ===== END data/maps/LavenderTown/connections.inc =====
@ ===== BEGIN data/maps/VermilionCity/connections.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/VermilionCity/map.json
@

VermilionCity_MapConnectionsList:
	connection up, 12, MAP_ROUTE6
	connection right, 10, MAP_ROUTE11

VermilionCity_MapConnections:
	.4byte 2
	.4byte VermilionCity_MapConnectionsList

@ ===== END data/maps/VermilionCity/connections.inc =====
@ ===== BEGIN data/maps/CeladonCity/connections.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/CeladonCity/map.json
@

CeladonCity_MapConnectionsList:
	connection left, 10, MAP_ROUTE16
	connection right, 10, MAP_ROUTE7

CeladonCity_MapConnections:
	.4byte 2
	.4byte CeladonCity_MapConnectionsList

@ ===== END data/maps/CeladonCity/connections.inc =====
@ ===== BEGIN data/maps/FuchsiaCity/connections.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FuchsiaCity/map.json
@

FuchsiaCity_MapConnectionsList:
	connection down, 12, MAP_ROUTE19
	connection left, 10, MAP_ROUTE18
	connection right, 10, MAP_ROUTE15

FuchsiaCity_MapConnections:
	.4byte 3
	.4byte FuchsiaCity_MapConnectionsList

@ ===== END data/maps/FuchsiaCity/connections.inc =====
@ ===== BEGIN data/maps/CinnabarIsland/connections.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/CinnabarIsland/map.json
@

CinnabarIsland_MapConnectionsList:
	connection up, 0, MAP_ROUTE21_SOUTH
	connection right, 0, MAP_ROUTE20

CinnabarIsland_MapConnections:
	.4byte 2
	.4byte CinnabarIsland_MapConnectionsList

@ ===== END data/maps/CinnabarIsland/connections.inc =====
@ ===== BEGIN data/maps/IndigoPlateau_Exterior/connections.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/IndigoPlateau_Exterior/map.json
@

IndigoPlateau_Exterior_MapConnectionsList:
	connection down, 0, MAP_ROUTE23

IndigoPlateau_Exterior_MapConnections:
	.4byte 1
	.4byte IndigoPlateau_Exterior_MapConnectionsList

@ ===== END data/maps/IndigoPlateau_Exterior/connections.inc =====
@ ===== BEGIN data/maps/SaffronCity/connections.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SaffronCity/map.json
@

SaffronCity_MapConnectionsList:
	connection up, 0, MAP_ROUTE5
	connection down, 12, MAP_ROUTE6
	connection left, 10, MAP_ROUTE7
	connection right, 10, MAP_ROUTE8

SaffronCity_MapConnections:
	.4byte 4
	.4byte SaffronCity_MapConnectionsList

@ ===== END data/maps/SaffronCity/connections.inc =====
@ ===== BEGIN data/maps/SaffronCity_Connection/connections.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SaffronCity_Connection/map.json
@

SaffronCity_Connection_MapConnectionsList:
	connection up, 0, MAP_ROUTE5
	connection down, 12, MAP_ROUTE6
	connection left, 10, MAP_ROUTE7
	connection right, 10, MAP_ROUTE8

SaffronCity_Connection_MapConnections:
	.4byte 4
	.4byte SaffronCity_Connection_MapConnectionsList

@ ===== END data/maps/SaffronCity_Connection/connections.inc =====
@ ===== BEGIN data/maps/OneIsland/connections.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/OneIsland/map.json
@

OneIsland_MapConnectionsList:
	connection down, 0, MAP_ONE_ISLAND_TREASURE_BEACH
	connection right, -120, MAP_ONE_ISLAND_KINDLE_ROAD

OneIsland_MapConnections:
	.4byte 2
	.4byte OneIsland_MapConnectionsList

@ ===== END data/maps/OneIsland/connections.inc =====
@ ===== BEGIN data/maps/TwoIsland/connections.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/TwoIsland/map.json
@

TwoIsland_MapConnectionsList:
	connection up, 24, MAP_TWO_ISLAND_CAPE_BRINK

TwoIsland_MapConnections:
	.4byte 1
	.4byte TwoIsland_MapConnectionsList

@ ===== END data/maps/TwoIsland/connections.inc =====
@ ===== BEGIN data/maps/ThreeIsland/connections.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/ThreeIsland/map.json
@

ThreeIsland_MapConnectionsList:
	connection down, 0, MAP_THREE_ISLAND_PORT
	connection left, 0, MAP_THREE_ISLAND_BOND_BRIDGE

ThreeIsland_MapConnections:
	.4byte 2
	.4byte ThreeIsland_MapConnectionsList

@ ===== END data/maps/ThreeIsland/connections.inc =====
@ ===== BEGIN data/maps/FiveIsland/connections.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FiveIsland/map.json
@

FiveIsland_MapConnectionsList:
	connection up, -48, MAP_FIVE_ISLAND_WATER_LABYRINTH
	connection right, 0, MAP_FIVE_ISLAND_MEADOW

FiveIsland_MapConnections:
	.4byte 2
	.4byte FiveIsland_MapConnectionsList

@ ===== END data/maps/FiveIsland/connections.inc =====
@ ===== BEGIN data/maps/SevenIsland/connections.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SevenIsland/map.json
@

SevenIsland_MapConnectionsList:
	connection up, -48, MAP_SEVEN_ISLAND_TRAINER_TOWER
	connection down, 0, MAP_SEVEN_ISLAND_SEVAULT_CANYON_ENTRANCE

SevenIsland_MapConnections:
	.4byte 2
	.4byte SevenIsland_MapConnectionsList

@ ===== END data/maps/SevenIsland/connections.inc =====
@ ===== BEGIN data/maps/SixIsland/connections.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SixIsland/map.json
@

SixIsland_MapConnectionsList:
	connection right, -40, MAP_SIX_ISLAND_WATER_PATH

SixIsland_MapConnections:
	.4byte 1
	.4byte SixIsland_MapConnectionsList

@ ===== END data/maps/SixIsland/connections.inc =====
@ ===== BEGIN data/maps/Route1/connections.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route1/map.json
@

Route1_MapConnectionsList:
	connection up, -12, MAP_VIRIDIAN_CITY
	connection down, 0, MAP_PALLET_TOWN

Route1_MapConnections:
	.4byte 2
	.4byte Route1_MapConnectionsList

@ ===== END data/maps/Route1/connections.inc =====
@ ===== BEGIN data/maps/Route2/connections.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route2/map.json
@

Route2_MapConnectionsList:
	connection up, -12, MAP_PEWTER_CITY
	connection down, -12, MAP_VIRIDIAN_CITY

Route2_MapConnections:
	.4byte 2
	.4byte Route2_MapConnectionsList

@ ===== END data/maps/Route2/connections.inc =====
@ ===== BEGIN data/maps/Route3/connections.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route3/map.json
@

Route3_MapConnectionsList:
	connection up, 60, MAP_ROUTE4
	connection left, -10, MAP_PEWTER_CITY

Route3_MapConnections:
	.4byte 2
	.4byte Route3_MapConnectionsList

@ ===== END data/maps/Route3/connections.inc =====
@ ===== BEGIN data/maps/Route4/connections.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route4/map.json
@

Route4_MapConnectionsList:
	connection down, -60, MAP_ROUTE3
	connection right, -10, MAP_CERULEAN_CITY

Route4_MapConnections:
	.4byte 2
	.4byte Route4_MapConnectionsList

@ ===== END data/maps/Route4/connections.inc =====
@ ===== BEGIN data/maps/Route5/connections.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route5/map.json
@

Route5_MapConnectionsList:
	connection up, 0, MAP_CERULEAN_CITY
	connection down, 0, MAP_SAFFRON_CITY_CONNECTION

Route5_MapConnections:
	.4byte 2
	.4byte Route5_MapConnectionsList

@ ===== END data/maps/Route5/connections.inc =====
@ ===== BEGIN data/maps/Route6/connections.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route6/map.json
@

Route6_MapConnectionsList:
	connection up, 0, MAP_SAFFRON_CITY_CONNECTION
	connection down, -12, MAP_VERMILION_CITY

Route6_MapConnections:
	.4byte 2
	.4byte Route6_MapConnectionsList

@ ===== END data/maps/Route6/connections.inc =====
@ ===== BEGIN data/maps/Route7/connections.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route7/map.json
@

Route7_MapConnectionsList:
	connection left, -10, MAP_CELADON_CITY
	connection right, -10, MAP_SAFFRON_CITY_CONNECTION

Route7_MapConnections:
	.4byte 2
	.4byte Route7_MapConnectionsList

@ ===== END data/maps/Route7/connections.inc =====
@ ===== BEGIN data/maps/Route8/connections.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route8/map.json
@

Route8_MapConnectionsList:
	connection left, -10, MAP_SAFFRON_CITY_CONNECTION
	connection right, 0, MAP_LAVENDER_TOWN

Route8_MapConnections:
	.4byte 2
	.4byte Route8_MapConnectionsList

@ ===== END data/maps/Route8/connections.inc =====
@ ===== BEGIN data/maps/Route9/connections.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route9/map.json
@

Route9_MapConnectionsList:
	connection left, -10, MAP_CERULEAN_CITY
	connection right, 0, MAP_ROUTE10

Route9_MapConnections:
	.4byte 2
	.4byte Route9_MapConnectionsList

@ ===== END data/maps/Route9/connections.inc =====
@ ===== BEGIN data/maps/Route10/connections.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route10/map.json
@

Route10_MapConnectionsList:
	connection down, 0, MAP_LAVENDER_TOWN
	connection left, 0, MAP_ROUTE9

Route10_MapConnections:
	.4byte 2
	.4byte Route10_MapConnectionsList

@ ===== END data/maps/Route10/connections.inc =====
@ ===== BEGIN data/maps/Route11/connections.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route11/map.json
@

Route11_MapConnectionsList:
	connection left, -10, MAP_VERMILION_CITY
	connection right, -60, MAP_ROUTE12

Route11_MapConnections:
	.4byte 2
	.4byte Route11_MapConnectionsList

@ ===== END data/maps/Route11/connections.inc =====
@ ===== BEGIN data/maps/Route12/connections.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route12/map.json
@

Route12_MapConnectionsList:
	connection up, 0, MAP_LAVENDER_TOWN
	connection down, -48, MAP_ROUTE13
	connection left, 60, MAP_ROUTE11

Route12_MapConnections:
	.4byte 3
	.4byte Route12_MapConnectionsList

@ ===== END data/maps/Route12/connections.inc =====
@ ===== BEGIN data/maps/Route13/connections.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route13/map.json
@

Route13_MapConnectionsList:
	connection up, 48, MAP_ROUTE12
	connection left, 0, MAP_ROUTE14

Route13_MapConnections:
	.4byte 2
	.4byte Route13_MapConnectionsList

@ ===== END data/maps/Route13/connections.inc =====
@ ===== BEGIN data/maps/Route14/connections.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route14/map.json
@

Route14_MapConnectionsList:
	connection left, 40, MAP_ROUTE15
	connection right, 0, MAP_ROUTE13

Route14_MapConnections:
	.4byte 2
	.4byte Route14_MapConnectionsList

@ ===== END data/maps/Route14/connections.inc =====
@ ===== BEGIN data/maps/Route15/connections.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route15/map.json
@

Route15_MapConnectionsList:
	connection left, -10, MAP_FUCHSIA_CITY
	connection right, -40, MAP_ROUTE14

Route15_MapConnections:
	.4byte 2
	.4byte Route15_MapConnectionsList

@ ===== END data/maps/Route15/connections.inc =====
@ ===== BEGIN data/maps/Route16/connections.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route16/map.json
@

Route16_MapConnectionsList:
	connection down, 0, MAP_ROUTE17
	connection right, -10, MAP_CELADON_CITY

Route16_MapConnections:
	.4byte 2
	.4byte Route16_MapConnectionsList

@ ===== END data/maps/Route16/connections.inc =====
@ ===== BEGIN data/maps/Route17/connections.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route17/map.json
@

Route17_MapConnectionsList:
	connection up, 0, MAP_ROUTE16
	connection down, 0, MAP_ROUTE18

Route17_MapConnections:
	.4byte 2
	.4byte Route17_MapConnectionsList

@ ===== END data/maps/Route17/connections.inc =====
@ ===== BEGIN data/maps/Route18/connections.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route18/map.json
@

Route18_MapConnectionsList:
	connection up, 0, MAP_ROUTE17
	connection right, -10, MAP_FUCHSIA_CITY

Route18_MapConnections:
	.4byte 2
	.4byte Route18_MapConnectionsList

@ ===== END data/maps/Route18/connections.inc =====
@ ===== BEGIN data/maps/Route19/connections.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route19/map.json
@

Route19_MapConnectionsList:
	connection up, -12, MAP_FUCHSIA_CITY
	connection left, 40, MAP_ROUTE20

Route19_MapConnections:
	.4byte 2
	.4byte Route19_MapConnectionsList

@ ===== END data/maps/Route19/connections.inc =====
@ ===== BEGIN data/maps/Route20/connections.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route20/map.json
@

Route20_MapConnectionsList:
	connection left, 0, MAP_CINNABAR_ISLAND
	connection right, -40, MAP_ROUTE19

Route20_MapConnections:
	.4byte 2
	.4byte Route20_MapConnectionsList

@ ===== END data/maps/Route20/connections.inc =====
@ ===== BEGIN data/maps/Route21_North/connections.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route21_North/map.json
@

Route21_North_MapConnectionsList:
	connection up, 0, MAP_PALLET_TOWN
	connection down, 0, MAP_ROUTE21_SOUTH

Route21_North_MapConnections:
	.4byte 2
	.4byte Route21_North_MapConnectionsList

@ ===== END data/maps/Route21_North/connections.inc =====
@ ===== BEGIN data/maps/Route21_South/connections.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route21_South/map.json
@

Route21_South_MapConnectionsList:
	connection up, 0, MAP_ROUTE21_NORTH
	connection down, 0, MAP_CINNABAR_ISLAND

Route21_South_MapConnections:
	.4byte 2
	.4byte Route21_South_MapConnectionsList

@ ===== END data/maps/Route21_South/connections.inc =====
@ ===== BEGIN data/maps/Route22/connections.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route22/map.json
@

Route22_MapConnectionsList:
	connection up, 0, MAP_ROUTE23
	connection right, -10, MAP_VIRIDIAN_CITY

Route22_MapConnections:
	.4byte 2
	.4byte Route22_MapConnectionsList

@ ===== END data/maps/Route22/connections.inc =====
@ ===== BEGIN data/maps/Route23/connections.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route23/map.json
@

Route23_MapConnectionsList:
	connection up, 0, MAP_INDIGO_PLATEAU_EXTERIOR
	connection down, 0, MAP_ROUTE22

Route23_MapConnections:
	.4byte 2
	.4byte Route23_MapConnectionsList

@ ===== END data/maps/Route23/connections.inc =====
@ ===== BEGIN data/maps/Route24/connections.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route24/map.json
@

Route24_MapConnectionsList:
	connection down, -12, MAP_CERULEAN_CITY
	connection right, 0, MAP_ROUTE25

Route24_MapConnections:
	.4byte 2
	.4byte Route24_MapConnectionsList

@ ===== END data/maps/Route24/connections.inc =====
@ ===== BEGIN data/maps/Route25/connections.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route25/map.json
@

Route25_MapConnectionsList:
	connection left, 0, MAP_ROUTE24

Route25_MapConnections:
	.4byte 1
	.4byte Route25_MapConnectionsList

@ ===== END data/maps/Route25/connections.inc =====
@ ===== BEGIN data/maps/OneIsland_KindleRoad/connections.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/OneIsland_KindleRoad/map.json
@

OneIsland_KindleRoad_MapConnectionsList:
	connection left, 120, MAP_ONE_ISLAND

OneIsland_KindleRoad_MapConnections:
	.4byte 1
	.4byte OneIsland_KindleRoad_MapConnectionsList

@ ===== END data/maps/OneIsland_KindleRoad/connections.inc =====
@ ===== BEGIN data/maps/OneIsland_TreasureBeach/connections.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/OneIsland_TreasureBeach/map.json
@

OneIsland_TreasureBeach_MapConnectionsList:
	connection up, 0, MAP_ONE_ISLAND

OneIsland_TreasureBeach_MapConnections:
	.4byte 1
	.4byte OneIsland_TreasureBeach_MapConnectionsList

@ ===== END data/maps/OneIsland_TreasureBeach/connections.inc =====
@ ===== BEGIN data/maps/TwoIsland_CapeBrink/connections.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/TwoIsland_CapeBrink/map.json
@

TwoIsland_CapeBrink_MapConnectionsList:
	connection down, -24, MAP_TWO_ISLAND

TwoIsland_CapeBrink_MapConnections:
	.4byte 1
	.4byte TwoIsland_CapeBrink_MapConnectionsList

@ ===== END data/maps/TwoIsland_CapeBrink/connections.inc =====
@ ===== BEGIN data/maps/ThreeIsland_BondBridge/connections.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/ThreeIsland_BondBridge/map.json
@

ThreeIsland_BondBridge_MapConnectionsList:
	connection right, 0, MAP_THREE_ISLAND

ThreeIsland_BondBridge_MapConnections:
	.4byte 1
	.4byte ThreeIsland_BondBridge_MapConnectionsList

@ ===== END data/maps/ThreeIsland_BondBridge/connections.inc =====
@ ===== BEGIN data/maps/ThreeIsland_Port/connections.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/ThreeIsland_Port/map.json
@

ThreeIsland_Port_MapConnectionsList:
	connection up, 0, MAP_THREE_ISLAND

ThreeIsland_Port_MapConnections:
	.4byte 1
	.4byte ThreeIsland_Port_MapConnectionsList

@ ===== END data/maps/ThreeIsland_Port/connections.inc =====
@ ===== BEGIN data/maps/Prototype_SeviiIsle_6/connections.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Prototype_SeviiIsle_6/map.json
@

Prototype_SeviiIsle_6_MapConnectionsList:
	connection up, 0, MAP_THREE_ISLAND

Prototype_SeviiIsle_6_MapConnections:
	.4byte 1
	.4byte Prototype_SeviiIsle_6_MapConnectionsList

@ ===== END data/maps/Prototype_SeviiIsle_6/connections.inc =====
@ ===== BEGIN data/maps/Prototype_SeviiIsle_7/connections.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Prototype_SeviiIsle_7/map.json
@

Prototype_SeviiIsle_7_MapConnectionsList:
	connection up, 0, MAP_THREE_ISLAND

Prototype_SeviiIsle_7_MapConnections:
	.4byte 1
	.4byte Prototype_SeviiIsle_7_MapConnectionsList

@ ===== END data/maps/Prototype_SeviiIsle_7/connections.inc =====
@ ===== BEGIN data/maps/FiveIsland_ResortGorgeous/connections.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FiveIsland_ResortGorgeous/map.json
@

FiveIsland_ResortGorgeous_MapConnectionsList:
	connection down, -48, MAP_FIVE_ISLAND_WATER_LABYRINTH

FiveIsland_ResortGorgeous_MapConnections:
	.4byte 1
	.4byte FiveIsland_ResortGorgeous_MapConnectionsList

@ ===== END data/maps/FiveIsland_ResortGorgeous/connections.inc =====
@ ===== BEGIN data/maps/FiveIsland_WaterLabyrinth/connections.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FiveIsland_WaterLabyrinth/map.json
@

FiveIsland_WaterLabyrinth_MapConnectionsList:
	connection up, 48, MAP_FIVE_ISLAND_RESORT_GORGEOUS
	connection down, 48, MAP_FIVE_ISLAND

FiveIsland_WaterLabyrinth_MapConnections:
	.4byte 2
	.4byte FiveIsland_WaterLabyrinth_MapConnectionsList

@ ===== END data/maps/FiveIsland_WaterLabyrinth/connections.inc =====
@ ===== BEGIN data/maps/FiveIsland_Meadow/connections.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FiveIsland_Meadow/map.json
@

FiveIsland_Meadow_MapConnectionsList:
	connection left, 0, MAP_FIVE_ISLAND
	connection right, 20, MAP_FIVE_ISLAND_MEMORIAL_PILLAR

FiveIsland_Meadow_MapConnections:
	.4byte 2
	.4byte FiveIsland_Meadow_MapConnectionsList

@ ===== END data/maps/FiveIsland_Meadow/connections.inc =====
@ ===== BEGIN data/maps/FiveIsland_MemorialPillar/connections.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/FiveIsland_MemorialPillar/map.json
@

FiveIsland_MemorialPillar_MapConnectionsList:
	connection left, -20, MAP_FIVE_ISLAND_MEADOW

FiveIsland_MemorialPillar_MapConnections:
	.4byte 1
	.4byte FiveIsland_MemorialPillar_MapConnectionsList

@ ===== END data/maps/FiveIsland_MemorialPillar/connections.inc =====
@ ===== BEGIN data/maps/SixIsland_OutcastIsland/connections.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SixIsland_OutcastIsland/map.json
@

SixIsland_OutcastIsland_MapConnectionsList:
	connection down, 0, MAP_SIX_ISLAND_GREEN_PATH

SixIsland_OutcastIsland_MapConnections:
	.4byte 1
	.4byte SixIsland_OutcastIsland_MapConnectionsList

@ ===== END data/maps/SixIsland_OutcastIsland/connections.inc =====
@ ===== BEGIN data/maps/SixIsland_GreenPath/connections.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SixIsland_GreenPath/map.json
@

SixIsland_GreenPath_MapConnectionsList:
	connection up, 0, MAP_SIX_ISLAND_OUTCAST_ISLAND
	connection right, 0, MAP_SIX_ISLAND_WATER_PATH

SixIsland_GreenPath_MapConnections:
	.4byte 2
	.4byte SixIsland_GreenPath_MapConnectionsList

@ ===== END data/maps/SixIsland_GreenPath/connections.inc =====
@ ===== BEGIN data/maps/SixIsland_WaterPath/connections.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SixIsland_WaterPath/map.json
@

SixIsland_WaterPath_MapConnectionsList:
	connection left, 0, MAP_SIX_ISLAND_GREEN_PATH
	connection left, 40, MAP_SIX_ISLAND
	connection left, 80, MAP_SIX_ISLAND_RUIN_VALLEY

SixIsland_WaterPath_MapConnections:
	.4byte 3
	.4byte SixIsland_WaterPath_MapConnectionsList

@ ===== END data/maps/SixIsland_WaterPath/connections.inc =====
@ ===== BEGIN data/maps/SixIsland_RuinValley/connections.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SixIsland_RuinValley/map.json
@

SixIsland_RuinValley_MapConnectionsList:
	connection right, -80, MAP_SIX_ISLAND_WATER_PATH

SixIsland_RuinValley_MapConnections:
	.4byte 1
	.4byte SixIsland_RuinValley_MapConnectionsList

@ ===== END data/maps/SixIsland_RuinValley/connections.inc =====
@ ===== BEGIN data/maps/SevenIsland_TrainerTower/connections.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SevenIsland_TrainerTower/map.json
@

SevenIsland_TrainerTower_MapConnectionsList:
	connection down, 48, MAP_SEVEN_ISLAND

SevenIsland_TrainerTower_MapConnections:
	.4byte 1
	.4byte SevenIsland_TrainerTower_MapConnectionsList

@ ===== END data/maps/SevenIsland_TrainerTower/connections.inc =====
@ ===== BEGIN data/maps/SevenIsland_SevaultCanyon_Entrance/connections.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SevenIsland_SevaultCanyon_Entrance/map.json
@

SevenIsland_SevaultCanyon_Entrance_MapConnectionsList:
	connection up, 0, MAP_SEVEN_ISLAND
	connection right, 20, MAP_SEVEN_ISLAND_SEVAULT_CANYON

SevenIsland_SevaultCanyon_Entrance_MapConnections:
	.4byte 2
	.4byte SevenIsland_SevaultCanyon_Entrance_MapConnectionsList

@ ===== END data/maps/SevenIsland_SevaultCanyon_Entrance/connections.inc =====
@ ===== BEGIN data/maps/SevenIsland_SevaultCanyon/connections.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SevenIsland_SevaultCanyon/map.json
@

SevenIsland_SevaultCanyon_MapConnectionsList:
	connection down, -48, MAP_SEVEN_ISLAND_TANOBY_RUINS
	connection left, -20, MAP_SEVEN_ISLAND_SEVAULT_CANYON_ENTRANCE

SevenIsland_SevaultCanyon_MapConnections:
	.4byte 2
	.4byte SevenIsland_SevaultCanyon_MapConnectionsList

@ ===== END data/maps/SevenIsland_SevaultCanyon/connections.inc =====
@ ===== BEGIN data/maps/SevenIsland_TanobyRuins/connections.inc =====
@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/SevenIsland_TanobyRuins/map.json
@

SevenIsland_TanobyRuins_MapConnectionsList:
	connection up, 48, MAP_SEVEN_ISLAND_SEVAULT_CANYON

SevenIsland_TanobyRuins_MapConnections:
	.4byte 1
	.4byte SevenIsland_TanobyRuins_MapConnectionsList

@ ===== END data/maps/SevenIsland_TanobyRuins/connections.inc =====
@ ===== BEGIN data/maps/LavenderTown_PokemonCenter_2F/connections.inc =====

@ ===== END data/maps/LavenderTown_PokemonCenter_2F/connections.inc =====
@ ===== BEGIN data/maps/VermilionCity_House2/connections.inc =====

@ ===== END data/maps/VermilionCity_House2/connections.inc =====
@ ===== BEGIN data/maps/VermilionCity_PokemonFanClub/connections.inc =====

@ ===== END data/maps/VermilionCity_PokemonFanClub/connections.inc =====
@ ===== BEGIN data/maps/VermilionCity_PokemonCenter_2F/connections.inc =====

@ ===== END data/maps/VermilionCity_PokemonCenter_2F/connections.inc =====
@ ===== BEGIN data/maps/VermilionCity_PokemonCenter_1F/connections.inc =====

@ ===== END data/maps/VermilionCity_PokemonCenter_1F/connections.inc =====
@ ===== BEGIN data/maps/VermilionCity_House1/connections.inc =====

@ ===== END data/maps/VermilionCity_House1/connections.inc =====
@ ===== BEGIN data/maps/LavenderTown_Mart/connections.inc =====

@ ===== END data/maps/LavenderTown_Mart/connections.inc =====
@ ===== BEGIN data/maps/LavenderTown_House2/connections.inc =====

@ ===== END data/maps/LavenderTown_House2/connections.inc =====
@ ===== BEGIN data/maps/LavenderTown_House1/connections.inc =====

@ ===== END data/maps/LavenderTown_House1/connections.inc =====
@ ===== BEGIN data/maps/LavenderTown_VolunteerPokemonHouse/connections.inc =====

@ ===== END data/maps/LavenderTown_VolunteerPokemonHouse/connections.inc =====
@ ===== BEGIN data/maps/CeladonCity_DepartmentStore_1F/connections.inc =====

@ ===== END data/maps/CeladonCity_DepartmentStore_1F/connections.inc =====
@ ===== BEGIN data/maps/LavenderTown_PokemonCenter_1F/connections.inc =====

@ ===== END data/maps/LavenderTown_PokemonCenter_1F/connections.inc =====
@ ===== BEGIN data/maps/CeruleanCity_House5/connections.inc =====

@ ===== END data/maps/CeruleanCity_House5/connections.inc =====
@ ===== BEGIN data/maps/CeruleanCity_House4/connections.inc =====

@ ===== END data/maps/CeruleanCity_House4/connections.inc =====
@ ===== BEGIN data/maps/VermilionCity_Mart/connections.inc =====

@ ===== END data/maps/VermilionCity_Mart/connections.inc =====
@ ===== BEGIN data/maps/VermilionCity_Gym/connections.inc =====

@ ===== END data/maps/VermilionCity_Gym/connections.inc =====
@ ===== BEGIN data/maps/VermilionCity_House3/connections.inc =====

@ ===== END data/maps/VermilionCity_House3/connections.inc =====
@ ===== BEGIN data/maps/CeruleanCity_PokemonCenter_2F/connections.inc =====

@ ===== END data/maps/CeruleanCity_PokemonCenter_2F/connections.inc =====
@ ===== BEGIN data/maps/CeladonCity_DepartmentStore_2F/connections.inc =====

@ ===== END data/maps/CeladonCity_DepartmentStore_2F/connections.inc =====
@ ===== BEGIN data/maps/CeladonCity_DepartmentStore_3F/connections.inc =====

@ ===== END data/maps/CeladonCity_DepartmentStore_3F/connections.inc =====
@ ===== BEGIN data/maps/CeladonCity_DepartmentStore_4F/connections.inc =====

@ ===== END data/maps/CeladonCity_DepartmentStore_4F/connections.inc =====
@ ===== BEGIN data/maps/CeladonCity_DepartmentStore_5F/connections.inc =====

@ ===== END data/maps/CeladonCity_DepartmentStore_5F/connections.inc =====
@ ===== BEGIN data/maps/CeladonCity_DepartmentStore_Roof/connections.inc =====

@ ===== END data/maps/CeladonCity_DepartmentStore_Roof/connections.inc =====
@ ===== BEGIN data/maps/CeladonCity_DepartmentStore_Elevator/connections.inc =====

@ ===== END data/maps/CeladonCity_DepartmentStore_Elevator/connections.inc =====
@ ===== BEGIN data/maps/CeladonCity_Condominiums_1F/connections.inc =====

@ ===== END data/maps/CeladonCity_Condominiums_1F/connections.inc =====
@ ===== BEGIN data/maps/CeladonCity_Condominiums_2F/connections.inc =====

@ ===== END data/maps/CeladonCity_Condominiums_2F/connections.inc =====
@ ===== BEGIN data/maps/CeladonCity_Condominiums_3F/connections.inc =====

@ ===== END data/maps/CeladonCity_Condominiums_3F/connections.inc =====
@ ===== BEGIN data/maps/CeladonCity_Condominiums_Roof/connections.inc =====

@ ===== END data/maps/CeladonCity_Condominiums_Roof/connections.inc =====
@ ===== BEGIN data/maps/PewterCity_Museum_2F/connections.inc =====

@ ===== END data/maps/PewterCity_Museum_2F/connections.inc =====
@ ===== BEGIN data/maps/Prototype_SeviiIsle_8/connections.inc =====

@ ===== END data/maps/Prototype_SeviiIsle_8/connections.inc =====
@ ===== BEGIN data/maps/CeladonCity_Condominiums_RoofRoom/connections.inc =====

@ ===== END data/maps/CeladonCity_Condominiums_RoofRoom/connections.inc =====
@ ===== BEGIN data/maps/PalletTown_PlayersHouse_1F/connections.inc =====

@ ===== END data/maps/PalletTown_PlayersHouse_1F/connections.inc =====
@ ===== BEGIN data/maps/PalletTown_PlayersHouse_2F/connections.inc =====

@ ===== END data/maps/PalletTown_PlayersHouse_2F/connections.inc =====
@ ===== BEGIN data/maps/PalletTown_RivalsHouse/connections.inc =====

@ ===== END data/maps/PalletTown_RivalsHouse/connections.inc =====
@ ===== BEGIN data/maps/PalletTown_ProfessorOaksLab/connections.inc =====

@ ===== END data/maps/PalletTown_ProfessorOaksLab/connections.inc =====
@ ===== BEGIN data/maps/ViridianCity_House/connections.inc =====

@ ===== END data/maps/ViridianCity_House/connections.inc =====
@ ===== BEGIN data/maps/ViridianCity_Gym/connections.inc =====

@ ===== END data/maps/ViridianCity_Gym/connections.inc =====
@ ===== BEGIN data/maps/ViridianCity_School/connections.inc =====

@ ===== END data/maps/ViridianCity_School/connections.inc =====
@ ===== BEGIN data/maps/ViridianCity_Mart/connections.inc =====

@ ===== END data/maps/ViridianCity_Mart/connections.inc =====
@ ===== BEGIN data/maps/ViridianCity_PokemonCenter_1F/connections.inc =====

@ ===== END data/maps/ViridianCity_PokemonCenter_1F/connections.inc =====
@ ===== BEGIN data/maps/ViridianCity_PokemonCenter_2F/connections.inc =====

@ ===== END data/maps/ViridianCity_PokemonCenter_2F/connections.inc =====
@ ===== BEGIN data/maps/PewterCity_Museum_1F/connections.inc =====

@ ===== END data/maps/PewterCity_Museum_1F/connections.inc =====
@ ===== BEGIN data/maps/CeruleanCity_Mart/connections.inc =====

@ ===== END data/maps/CeruleanCity_Mart/connections.inc =====
@ ===== BEGIN data/maps/PewterCity_Gym/connections.inc =====

@ ===== END data/maps/PewterCity_Gym/connections.inc =====
@ ===== BEGIN data/maps/PewterCity_Mart/connections.inc =====

@ ===== END data/maps/PewterCity_Mart/connections.inc =====
@ ===== BEGIN data/maps/PewterCity_House1/connections.inc =====

@ ===== END data/maps/PewterCity_House1/connections.inc =====
@ ===== BEGIN data/maps/PewterCity_PokemonCenter_1F/connections.inc =====

@ ===== END data/maps/PewterCity_PokemonCenter_1F/connections.inc =====
@ ===== BEGIN data/maps/PewterCity_PokemonCenter_2F/connections.inc =====

@ ===== END data/maps/PewterCity_PokemonCenter_2F/connections.inc =====
@ ===== BEGIN data/maps/PewterCity_House2/connections.inc =====

@ ===== END data/maps/PewterCity_House2/connections.inc =====
@ ===== BEGIN data/maps/CeruleanCity_House1/connections.inc =====

@ ===== END data/maps/CeruleanCity_House1/connections.inc =====
@ ===== BEGIN data/maps/CeruleanCity_House2/connections.inc =====

@ ===== END data/maps/CeruleanCity_House2/connections.inc =====
@ ===== BEGIN data/maps/CeruleanCity_House3/connections.inc =====

@ ===== END data/maps/CeruleanCity_House3/connections.inc =====
@ ===== BEGIN data/maps/CeruleanCity_PokemonCenter_1F/connections.inc =====

@ ===== END data/maps/CeruleanCity_PokemonCenter_1F/connections.inc =====
@ ===== BEGIN data/maps/Prototype_SeviiIsle_9/connections.inc =====

@ ===== END data/maps/Prototype_SeviiIsle_9/connections.inc =====
@ ===== BEGIN data/maps/CeruleanCity_Gym/connections.inc =====

@ ===== END data/maps/CeruleanCity_Gym/connections.inc =====
@ ===== BEGIN data/maps/CeruleanCity_BikeShop/connections.inc =====

@ ===== END data/maps/CeruleanCity_BikeShop/connections.inc =====
@ ===== BEGIN data/maps/SevenIsland_UnusedHouse/connections.inc =====

@ ===== END data/maps/SevenIsland_UnusedHouse/connections.inc =====
@ ===== BEGIN data/maps/ThreeIsland_PokemonCenter_2F/connections.inc =====

@ ===== END data/maps/ThreeIsland_PokemonCenter_2F/connections.inc =====
@ ===== BEGIN data/maps/ThreeIsland_PokemonCenter_1F/connections.inc =====

@ ===== END data/maps/ThreeIsland_PokemonCenter_1F/connections.inc =====
@ ===== BEGIN data/maps/ThreeIsland_House1/connections.inc =====

@ ===== END data/maps/ThreeIsland_House1/connections.inc =====
@ ===== BEGIN data/maps/TwoIsland_Harbor/connections.inc =====

@ ===== END data/maps/TwoIsland_Harbor/connections.inc =====
@ ===== BEGIN data/maps/TwoIsland_PokemonCenter_2F/connections.inc =====

@ ===== END data/maps/TwoIsland_PokemonCenter_2F/connections.inc =====
@ ===== BEGIN data/maps/TwoIsland_PokemonCenter_1F/connections.inc =====

@ ===== END data/maps/TwoIsland_PokemonCenter_1F/connections.inc =====
@ ===== BEGIN data/maps/TwoIsland_House/connections.inc =====

@ ===== END data/maps/TwoIsland_House/connections.inc =====
@ ===== BEGIN data/maps/TwoIsland_JoyfulGameCorner/connections.inc =====

@ ===== END data/maps/TwoIsland_JoyfulGameCorner/connections.inc =====
@ ===== BEGIN data/maps/OneIsland_Harbor/connections.inc =====

@ ===== END data/maps/OneIsland_Harbor/connections.inc =====
@ ===== BEGIN data/maps/OneIsland_House2/connections.inc =====

@ ===== END data/maps/OneIsland_House2/connections.inc =====
@ ===== BEGIN data/maps/OneIsland_House1/connections.inc =====

@ ===== END data/maps/OneIsland_House1/connections.inc =====
@ ===== BEGIN data/maps/OneIsland_PokemonCenter_2F/connections.inc =====

@ ===== END data/maps/OneIsland_PokemonCenter_2F/connections.inc =====
@ ===== BEGIN data/maps/OneIsland_PokemonCenter_1F/connections.inc =====

@ ===== END data/maps/OneIsland_PokemonCenter_1F/connections.inc =====
@ ===== BEGIN data/maps/SevenIsland_Harbor/connections.inc =====

@ ===== END data/maps/SevenIsland_Harbor/connections.inc =====
@ ===== BEGIN data/maps/ThreeIsland_Mart/connections.inc =====

@ ===== END data/maps/ThreeIsland_Mart/connections.inc =====
@ ===== BEGIN data/maps/SevenIsland_PokemonCenter_2F/connections.inc =====

@ ===== END data/maps/SevenIsland_PokemonCenter_2F/connections.inc =====
@ ===== BEGIN data/maps/SevenIsland_PokemonCenter_1F/connections.inc =====

@ ===== END data/maps/SevenIsland_PokemonCenter_1F/connections.inc =====
@ ===== BEGIN data/maps/SevenIsland_Mart/connections.inc =====

@ ===== END data/maps/SevenIsland_Mart/connections.inc =====
@ ===== BEGIN data/maps/SevenIsland_House_Room2/connections.inc =====

@ ===== END data/maps/SevenIsland_House_Room2/connections.inc =====
@ ===== BEGIN data/maps/SevenIsland_House_Room1/connections.inc =====

@ ===== END data/maps/SevenIsland_House_Room1/connections.inc =====
@ ===== BEGIN data/maps/Route25_SeaCottage/connections.inc =====

@ ===== END data/maps/Route25_SeaCottage/connections.inc =====
@ ===== BEGIN data/maps/Route23_UnusedHouse/connections.inc =====

@ ===== END data/maps/Route23_UnusedHouse/connections.inc =====
@ ===== BEGIN data/maps/Route22_NorthEntrance/connections.inc =====

@ ===== END data/maps/Route22_NorthEntrance/connections.inc =====
@ ===== BEGIN data/maps/Route19_UnusedHouse/connections.inc =====

@ ===== END data/maps/Route19_UnusedHouse/connections.inc =====
@ ===== BEGIN data/maps/Route18_EastEntrance_2F/connections.inc =====

@ ===== END data/maps/Route18_EastEntrance_2F/connections.inc =====
@ ===== BEGIN data/maps/Route18_EastEntrance_1F/connections.inc =====

@ ===== END data/maps/Route18_EastEntrance_1F/connections.inc =====
@ ===== BEGIN data/maps/Route16_NorthEntrance_2F/connections.inc =====

@ ===== END data/maps/Route16_NorthEntrance_2F/connections.inc =====
@ ===== BEGIN data/maps/Route16_NorthEntrance_1F/connections.inc =====

@ ===== END data/maps/Route16_NorthEntrance_1F/connections.inc =====
@ ===== BEGIN data/maps/Route16_House/connections.inc =====

@ ===== END data/maps/Route16_House/connections.inc =====
@ ===== BEGIN data/maps/FiveIsland_PokemonCenter_2F/connections.inc =====

@ ===== END data/maps/FiveIsland_PokemonCenter_2F/connections.inc =====
@ ===== BEGIN data/maps/BattleColosseum_2P/connections.inc =====

@ ===== END data/maps/BattleColosseum_2P/connections.inc =====
@ ===== BEGIN data/maps/SixIsland_WaterPath_House2/connections.inc =====

@ ===== END data/maps/SixIsland_WaterPath_House2/connections.inc =====
@ ===== BEGIN data/maps/SixIsland_WaterPath_House1/connections.inc =====

@ ===== END data/maps/SixIsland_WaterPath_House1/connections.inc =====
@ ===== BEGIN data/maps/TwoIsland_CapeBrink_House/connections.inc =====

@ ===== END data/maps/TwoIsland_CapeBrink_House/connections.inc =====
@ ===== BEGIN data/maps/FiveIsland_ResortGorgeous_House/connections.inc =====

@ ===== END data/maps/FiveIsland_ResortGorgeous_House/connections.inc =====
@ ===== BEGIN data/maps/ThreeIsland_Harbor/connections.inc =====

@ ===== END data/maps/ThreeIsland_Harbor/connections.inc =====
@ ===== BEGIN data/maps/SixIsland_Mart/connections.inc =====

@ ===== END data/maps/SixIsland_Mart/connections.inc =====
@ ===== BEGIN data/maps/SixIsland_House/connections.inc =====

@ ===== END data/maps/SixIsland_House/connections.inc =====
@ ===== BEGIN data/maps/SixIsland_Harbor/connections.inc =====

@ ===== END data/maps/SixIsland_Harbor/connections.inc =====
@ ===== BEGIN data/maps/SixIsland_PokemonCenter_2F/connections.inc =====

@ ===== END data/maps/SixIsland_PokemonCenter_2F/connections.inc =====
@ ===== BEGIN data/maps/SixIsland_PokemonCenter_1F/connections.inc =====

@ ===== END data/maps/SixIsland_PokemonCenter_1F/connections.inc =====
@ ===== BEGIN data/maps/FiveIsland_House2/connections.inc =====

@ ===== END data/maps/FiveIsland_House2/connections.inc =====
@ ===== BEGIN data/maps/FiveIsland_House1/connections.inc =====

@ ===== END data/maps/FiveIsland_House1/connections.inc =====
@ ===== BEGIN data/maps/FiveIsland_Harbor/connections.inc =====

@ ===== END data/maps/FiveIsland_Harbor/connections.inc =====
@ ===== BEGIN data/maps/Route15_WestEntrance_2F/connections.inc =====

@ ===== END data/maps/Route15_WestEntrance_2F/connections.inc =====
@ ===== BEGIN data/maps/FiveIsland_PokemonCenter_1F/connections.inc =====

@ ===== END data/maps/FiveIsland_PokemonCenter_1F/connections.inc =====
@ ===== BEGIN data/maps/FourIsland_Mart/connections.inc =====

@ ===== END data/maps/FourIsland_Mart/connections.inc =====
@ ===== BEGIN data/maps/FourIsland_House2/connections.inc =====

@ ===== END data/maps/FourIsland_House2/connections.inc =====
@ ===== BEGIN data/maps/FourIsland_Harbor/connections.inc =====

@ ===== END data/maps/FourIsland_Harbor/connections.inc =====
@ ===== BEGIN data/maps/FourIsland_LoreleisHouse/connections.inc =====

@ ===== END data/maps/FourIsland_LoreleisHouse/connections.inc =====
@ ===== BEGIN data/maps/FourIsland_House1/connections.inc =====

@ ===== END data/maps/FourIsland_House1/connections.inc =====
@ ===== BEGIN data/maps/FourIsland_PokemonCenter_2F/connections.inc =====

@ ===== END data/maps/FourIsland_PokemonCenter_2F/connections.inc =====
@ ===== BEGIN data/maps/FourIsland_PokemonCenter_1F/connections.inc =====

@ ===== END data/maps/FourIsland_PokemonCenter_1F/connections.inc =====
@ ===== BEGIN data/maps/FourIsland_PokemonDayCare/connections.inc =====

@ ===== END data/maps/FourIsland_PokemonDayCare/connections.inc =====
@ ===== BEGIN data/maps/ThreeIsland_House5/connections.inc =====

@ ===== END data/maps/ThreeIsland_House5/connections.inc =====
@ ===== BEGIN data/maps/ThreeIsland_House4/connections.inc =====

@ ===== END data/maps/ThreeIsland_House4/connections.inc =====
@ ===== BEGIN data/maps/ThreeIsland_House3/connections.inc =====

@ ===== END data/maps/ThreeIsland_House3/connections.inc =====
@ ===== BEGIN data/maps/ThreeIsland_House2/connections.inc =====

@ ===== END data/maps/ThreeIsland_House2/connections.inc =====
@ ===== BEGIN data/maps/FuchsiaCity_PokemonCenter_2F/connections.inc =====

@ ===== END data/maps/FuchsiaCity_PokemonCenter_2F/connections.inc =====
@ ===== BEGIN data/maps/SaffronCity_CopycatsHouse_1F/connections.inc =====

@ ===== END data/maps/SaffronCity_CopycatsHouse_1F/connections.inc =====
@ ===== BEGIN data/maps/IndigoPlateau_PokemonCenter_2F/connections.inc =====

@ ===== END data/maps/IndigoPlateau_PokemonCenter_2F/connections.inc =====
@ ===== BEGIN data/maps/IndigoPlateau_PokemonCenter_1F/connections.inc =====

@ ===== END data/maps/IndigoPlateau_PokemonCenter_1F/connections.inc =====
@ ===== BEGIN data/maps/CinnabarIsland_Mart/connections.inc =====

@ ===== END data/maps/CinnabarIsland_Mart/connections.inc =====
@ ===== BEGIN data/maps/CinnabarIsland_PokemonCenter_2F/connections.inc =====

@ ===== END data/maps/CinnabarIsland_PokemonCenter_2F/connections.inc =====
@ ===== BEGIN data/maps/CinnabarIsland_PokemonCenter_1F/connections.inc =====

@ ===== END data/maps/CinnabarIsland_PokemonCenter_1F/connections.inc =====
@ ===== BEGIN data/maps/CinnabarIsland_PokemonLab_ExperimentRoom/connections.inc =====

@ ===== END data/maps/CinnabarIsland_PokemonLab_ExperimentRoom/connections.inc =====
@ ===== BEGIN data/maps/CinnabarIsland_PokemonLab_ResearchRoom/connections.inc =====

@ ===== END data/maps/CinnabarIsland_PokemonLab_ResearchRoom/connections.inc =====
@ ===== BEGIN data/maps/CinnabarIsland_PokemonLab_Lounge/connections.inc =====

@ ===== END data/maps/CinnabarIsland_PokemonLab_Lounge/connections.inc =====
@ ===== BEGIN data/maps/CinnabarIsland_PokemonLab_Entrance/connections.inc =====

@ ===== END data/maps/CinnabarIsland_PokemonLab_Entrance/connections.inc =====
@ ===== BEGIN data/maps/CinnabarIsland_Gym/connections.inc =====

@ ===== END data/maps/CinnabarIsland_Gym/connections.inc =====
@ ===== BEGIN data/maps/FuchsiaCity_House3/connections.inc =====

@ ===== END data/maps/FuchsiaCity_House3/connections.inc =====
@ ===== BEGIN data/maps/FuchsiaCity_House2/connections.inc =====

@ ===== END data/maps/FuchsiaCity_House2/connections.inc =====
@ ===== BEGIN data/maps/FuchsiaCity_WardensHouse/connections.inc =====

@ ===== END data/maps/FuchsiaCity_WardensHouse/connections.inc =====
@ ===== BEGIN data/maps/SaffronCity_CopycatsHouse_2F/connections.inc =====

@ ===== END data/maps/SaffronCity_CopycatsHouse_2F/connections.inc =====
@ ===== BEGIN data/maps/FuchsiaCity_PokemonCenter_1F/connections.inc =====

@ ===== END data/maps/FuchsiaCity_PokemonCenter_1F/connections.inc =====
@ ===== BEGIN data/maps/FuchsiaCity_House1/connections.inc =====

@ ===== END data/maps/FuchsiaCity_House1/connections.inc =====
@ ===== BEGIN data/maps/FuchsiaCity_Gym/connections.inc =====

@ ===== END data/maps/FuchsiaCity_Gym/connections.inc =====
@ ===== BEGIN data/maps/FuchsiaCity_SafariZone_Office/connections.inc =====

@ ===== END data/maps/FuchsiaCity_SafariZone_Office/connections.inc =====
@ ===== BEGIN data/maps/FuchsiaCity_Mart/connections.inc =====

@ ===== END data/maps/FuchsiaCity_Mart/connections.inc =====
@ ===== BEGIN data/maps/FuchsiaCity_SafariZone_Entrance/connections.inc =====

@ ===== END data/maps/FuchsiaCity_SafariZone_Entrance/connections.inc =====
@ ===== BEGIN data/maps/CeladonCity_Hotel/connections.inc =====

@ ===== END data/maps/CeladonCity_Hotel/connections.inc =====
@ ===== BEGIN data/maps/CeladonCity_House1/connections.inc =====

@ ===== END data/maps/CeladonCity_House1/connections.inc =====
@ ===== BEGIN data/maps/CeladonCity_Restaurant/connections.inc =====

@ ===== END data/maps/CeladonCity_Restaurant/connections.inc =====
@ ===== BEGIN data/maps/CeladonCity_Gym/connections.inc =====

@ ===== END data/maps/CeladonCity_Gym/connections.inc =====
@ ===== BEGIN data/maps/CeladonCity_GameCorner_PrizeRoom/connections.inc =====

@ ===== END data/maps/CeladonCity_GameCorner_PrizeRoom/connections.inc =====
@ ===== BEGIN data/maps/CeladonCity_GameCorner/connections.inc =====

@ ===== END data/maps/CeladonCity_GameCorner/connections.inc =====
@ ===== BEGIN data/maps/CeladonCity_PokemonCenter_2F/connections.inc =====

@ ===== END data/maps/CeladonCity_PokemonCenter_2F/connections.inc =====
@ ===== BEGIN data/maps/CeladonCity_PokemonCenter_1F/connections.inc =====

@ ===== END data/maps/CeladonCity_PokemonCenter_1F/connections.inc =====
@ ===== BEGIN data/maps/Route4_PokemonCenter_2F/connections.inc =====

@ ===== END data/maps/Route4_PokemonCenter_2F/connections.inc =====
@ ===== BEGIN data/maps/Route15_WestEntrance_1F/connections.inc =====

@ ===== END data/maps/Route15_WestEntrance_1F/connections.inc =====
@ ===== BEGIN data/maps/Route12_FishingHouse/connections.inc =====

@ ===== END data/maps/Route12_FishingHouse/connections.inc =====
@ ===== BEGIN data/maps/Route12_NorthEntrance_2F/connections.inc =====

@ ===== END data/maps/Route12_NorthEntrance_2F/connections.inc =====
@ ===== BEGIN data/maps/Route12_NorthEntrance_1F/connections.inc =====

@ ===== END data/maps/Route12_NorthEntrance_1F/connections.inc =====
@ ===== BEGIN data/maps/Route11_EastEntrance_2F/connections.inc =====

@ ===== END data/maps/Route11_EastEntrance_2F/connections.inc =====
@ ===== BEGIN data/maps/Route11_EastEntrance_1F/connections.inc =====

@ ===== END data/maps/Route11_EastEntrance_1F/connections.inc =====
@ ===== BEGIN data/maps/Route10_PokemonCenter_2F/connections.inc =====

@ ===== END data/maps/Route10_PokemonCenter_2F/connections.inc =====
@ ===== BEGIN data/maps/Route10_PokemonCenter_1F/connections.inc =====

@ ===== END data/maps/Route10_PokemonCenter_1F/connections.inc =====
@ ===== BEGIN data/maps/Route8_WestEntrance/connections.inc =====

@ ===== END data/maps/Route8_WestEntrance/connections.inc =====
@ ===== BEGIN data/maps/Route7_EastEntrance/connections.inc =====

@ ===== END data/maps/Route7_EastEntrance/connections.inc =====
@ ===== BEGIN data/maps/Route6_UnusedHouse/connections.inc =====

@ ===== END data/maps/Route6_UnusedHouse/connections.inc =====
@ ===== BEGIN data/maps/Route6_NorthEntrance/connections.inc =====

@ ===== END data/maps/Route6_NorthEntrance/connections.inc =====
@ ===== BEGIN data/maps/Route5_SouthEntrance/connections.inc =====

@ ===== END data/maps/Route5_SouthEntrance/connections.inc =====
@ ===== BEGIN data/maps/Route5_PokemonDayCare/connections.inc =====

@ ===== END data/maps/Route5_PokemonDayCare/connections.inc =====
@ ===== BEGIN data/maps/SevenIsland_SevaultCanyon_House/connections.inc =====

@ ===== END data/maps/SevenIsland_SevaultCanyon_House/connections.inc =====
@ ===== BEGIN data/maps/Route4_PokemonCenter_1F/connections.inc =====

@ ===== END data/maps/Route4_PokemonCenter_1F/connections.inc =====
@ ===== BEGIN data/maps/Route2_ViridianForest_NorthEntrance/connections.inc =====

@ ===== END data/maps/Route2_ViridianForest_NorthEntrance/connections.inc =====
@ ===== BEGIN data/maps/Route2_EastBuilding/connections.inc =====

@ ===== END data/maps/Route2_EastBuilding/connections.inc =====
@ ===== BEGIN data/maps/Route2_House/connections.inc =====

@ ===== END data/maps/Route2_House/connections.inc =====
@ ===== BEGIN data/maps/Route2_ViridianForest_SouthEntrance/connections.inc =====

@ ===== END data/maps/Route2_ViridianForest_SouthEntrance/connections.inc =====
@ ===== BEGIN data/maps/SaffronCity_PokemonTrainerFanClub/connections.inc =====

@ ===== END data/maps/SaffronCity_PokemonTrainerFanClub/connections.inc =====
@ ===== BEGIN data/maps/SaffronCity_MrPsychicsHouse/connections.inc =====

@ ===== END data/maps/SaffronCity_MrPsychicsHouse/connections.inc =====
@ ===== BEGIN data/maps/SaffronCity_PokemonCenter_2F/connections.inc =====

@ ===== END data/maps/SaffronCity_PokemonCenter_2F/connections.inc =====
@ ===== BEGIN data/maps/SaffronCity_PokemonCenter_1F/connections.inc =====

@ ===== END data/maps/SaffronCity_PokemonCenter_1F/connections.inc =====
@ ===== BEGIN data/maps/SaffronCity_Mart/connections.inc =====

@ ===== END data/maps/SaffronCity_Mart/connections.inc =====
@ ===== BEGIN data/maps/SaffronCity_House/connections.inc =====

@ ===== END data/maps/SaffronCity_House/connections.inc =====
@ ===== BEGIN data/maps/SaffronCity_Gym/connections.inc =====

@ ===== END data/maps/SaffronCity_Gym/connections.inc =====
@ ===== BEGIN data/maps/SaffronCity_Dojo/connections.inc =====

@ ===== END data/maps/SaffronCity_Dojo/connections.inc =====
@ ===== BEGIN data/maps/SilphCo_8F/connections.inc =====

@ ===== END data/maps/SilphCo_8F/connections.inc =====
@ ===== BEGIN data/maps/SafariZone_North/connections.inc =====

@ ===== END data/maps/SafariZone_North/connections.inc =====
@ ===== BEGIN data/maps/SafariZone_East/connections.inc =====

@ ===== END data/maps/SafariZone_East/connections.inc =====
@ ===== BEGIN data/maps/SafariZone_Center/connections.inc =====

@ ===== END data/maps/SafariZone_Center/connections.inc =====
@ ===== BEGIN data/maps/PokemonMansion_B1F/connections.inc =====

@ ===== END data/maps/PokemonMansion_B1F/connections.inc =====
@ ===== BEGIN data/maps/PokemonMansion_3F/connections.inc =====

@ ===== END data/maps/PokemonMansion_3F/connections.inc =====
@ ===== BEGIN data/maps/PokemonMansion_2F/connections.inc =====

@ ===== END data/maps/PokemonMansion_2F/connections.inc =====
@ ===== BEGIN data/maps/PokemonMansion_1F/connections.inc =====

@ ===== END data/maps/PokemonMansion_1F/connections.inc =====
@ ===== BEGIN data/maps/SilphCo_Elevator/connections.inc =====

@ ===== END data/maps/SilphCo_Elevator/connections.inc =====
@ ===== BEGIN data/maps/SilphCo_11F/connections.inc =====

@ ===== END data/maps/SilphCo_11F/connections.inc =====
@ ===== BEGIN data/maps/SilphCo_10F/connections.inc =====

@ ===== END data/maps/SilphCo_10F/connections.inc =====
@ ===== BEGIN data/maps/SilphCo_9F/connections.inc =====

@ ===== END data/maps/SilphCo_9F/connections.inc =====
@ ===== BEGIN data/maps/SafariZone_West/connections.inc =====

@ ===== END data/maps/SafariZone_West/connections.inc =====
@ ===== BEGIN data/maps/SilphCo_7F/connections.inc =====

@ ===== END data/maps/SilphCo_7F/connections.inc =====
@ ===== BEGIN data/maps/SilphCo_6F/connections.inc =====

@ ===== END data/maps/SilphCo_6F/connections.inc =====
@ ===== BEGIN data/maps/SilphCo_5F/connections.inc =====

@ ===== END data/maps/SilphCo_5F/connections.inc =====
@ ===== BEGIN data/maps/SilphCo_4F/connections.inc =====

@ ===== END data/maps/SilphCo_4F/connections.inc =====
@ ===== BEGIN data/maps/SilphCo_3F/connections.inc =====

@ ===== END data/maps/SilphCo_3F/connections.inc =====
@ ===== BEGIN data/maps/SilphCo_2F/connections.inc =====

@ ===== END data/maps/SilphCo_2F/connections.inc =====
@ ===== BEGIN data/maps/SilphCo_1F/connections.inc =====

@ ===== END data/maps/SilphCo_1F/connections.inc =====
@ ===== BEGIN data/maps/RocketHideout_Elevator/connections.inc =====

@ ===== END data/maps/RocketHideout_Elevator/connections.inc =====
@ ===== BEGIN data/maps/RocketHideout_B4F/connections.inc =====

@ ===== END data/maps/RocketHideout_B4F/connections.inc =====
@ ===== BEGIN data/maps/RocketHideout_B3F/connections.inc =====

@ ===== END data/maps/RocketHideout_B3F/connections.inc =====
@ ===== BEGIN data/maps/RocketHideout_B2F/connections.inc =====

@ ===== END data/maps/RocketHideout_B2F/connections.inc =====
@ ===== BEGIN data/maps/PokemonLeague_AgathasRoom/connections.inc =====

@ ===== END data/maps/PokemonLeague_AgathasRoom/connections.inc =====
@ ===== BEGIN data/maps/PokemonTower_1F/connections.inc =====

@ ===== END data/maps/PokemonTower_1F/connections.inc =====
@ ===== BEGIN data/maps/SeafoamIslands_B4F/connections.inc =====

@ ===== END data/maps/SeafoamIslands_B4F/connections.inc =====
@ ===== BEGIN data/maps/SeafoamIslands_B3F/connections.inc =====

@ ===== END data/maps/SeafoamIslands_B3F/connections.inc =====
@ ===== BEGIN data/maps/SeafoamIslands_B2F/connections.inc =====

@ ===== END data/maps/SeafoamIslands_B2F/connections.inc =====
@ ===== BEGIN data/maps/SeafoamIslands_B1F/connections.inc =====

@ ===== END data/maps/SeafoamIslands_B1F/connections.inc =====
@ ===== BEGIN data/maps/SeafoamIslands_1F/connections.inc =====

@ ===== END data/maps/SeafoamIslands_1F/connections.inc =====
@ ===== BEGIN data/maps/RockTunnel_B1F/connections.inc =====

@ ===== END data/maps/RockTunnel_B1F/connections.inc =====
@ ===== BEGIN data/maps/RockTunnel_1F/connections.inc =====

@ ===== END data/maps/RockTunnel_1F/connections.inc =====
@ ===== BEGIN data/maps/PokemonLeague_HallOfFame/connections.inc =====

@ ===== END data/maps/PokemonLeague_HallOfFame/connections.inc =====
@ ===== BEGIN data/maps/PokemonLeague_ChampionsRoom/connections.inc =====

@ ===== END data/maps/PokemonLeague_ChampionsRoom/connections.inc =====
@ ===== BEGIN data/maps/PokemonLeague_LancesRoom/connections.inc =====

@ ===== END data/maps/PokemonLeague_LancesRoom/connections.inc =====
@ ===== BEGIN data/maps/RocketHideout_B1F/connections.inc =====

@ ===== END data/maps/RocketHideout_B1F/connections.inc =====
@ ===== BEGIN data/maps/PokemonLeague_BrunosRoom/connections.inc =====

@ ===== END data/maps/PokemonLeague_BrunosRoom/connections.inc =====
@ ===== BEGIN data/maps/PokemonLeague_LoreleisRoom/connections.inc =====

@ ===== END data/maps/PokemonLeague_LoreleisRoom/connections.inc =====
@ ===== BEGIN data/maps/CeruleanCave_B1F/connections.inc =====

@ ===== END data/maps/CeruleanCave_B1F/connections.inc =====
@ ===== BEGIN data/maps/CeruleanCave_2F/connections.inc =====

@ ===== END data/maps/CeruleanCave_2F/connections.inc =====
@ ===== BEGIN data/maps/CeruleanCave_1F/connections.inc =====

@ ===== END data/maps/CeruleanCave_1F/connections.inc =====
@ ===== BEGIN data/maps/SafariZone_SecretHouse/connections.inc =====

@ ===== END data/maps/SafariZone_SecretHouse/connections.inc =====
@ ===== BEGIN data/maps/SafariZone_West_RestHouse/connections.inc =====

@ ===== END data/maps/SafariZone_West_RestHouse/connections.inc =====
@ ===== BEGIN data/maps/SafariZone_North_RestHouse/connections.inc =====

@ ===== END data/maps/SafariZone_North_RestHouse/connections.inc =====
@ ===== BEGIN data/maps/SafariZone_East_RestHouse/connections.inc =====

@ ===== END data/maps/SafariZone_East_RestHouse/connections.inc =====
@ ===== BEGIN data/maps/SafariZone_Center_RestHouse/connections.inc =====

@ ===== END data/maps/SafariZone_Center_RestHouse/connections.inc =====
@ ===== BEGIN data/maps/SSAnne_3F_Corridor/connections.inc =====

@ ===== END data/maps/SSAnne_3F_Corridor/connections.inc =====
@ ===== BEGIN data/maps/SSAnne_2F_Room1/connections.inc =====

@ ===== END data/maps/SSAnne_2F_Room1/connections.inc =====
@ ===== BEGIN data/maps/SSAnne_1F_Room7/connections.inc =====

@ ===== END data/maps/SSAnne_1F_Room7/connections.inc =====
@ ===== BEGIN data/maps/SSAnne_1F_Room5/connections.inc =====

@ ===== END data/maps/SSAnne_1F_Room5/connections.inc =====
@ ===== BEGIN data/maps/SSAnne_1F_Room4/connections.inc =====

@ ===== END data/maps/SSAnne_1F_Room4/connections.inc =====
@ ===== BEGIN data/maps/SSAnne_1F_Room3/connections.inc =====

@ ===== END data/maps/SSAnne_1F_Room3/connections.inc =====
@ ===== BEGIN data/maps/SSAnne_1F_Room2/connections.inc =====

@ ===== END data/maps/SSAnne_1F_Room2/connections.inc =====
@ ===== BEGIN data/maps/SSAnne_1F_Room1/connections.inc =====

@ ===== END data/maps/SSAnne_1F_Room1/connections.inc =====
@ ===== BEGIN data/maps/SSAnne_CaptainsOffice/connections.inc =====

@ ===== END data/maps/SSAnne_CaptainsOffice/connections.inc =====
@ ===== BEGIN data/maps/SSAnne_Kitchen/connections.inc =====

@ ===== END data/maps/SSAnne_Kitchen/connections.inc =====
@ ===== BEGIN data/maps/SSAnne_Deck/connections.inc =====

@ ===== END data/maps/SSAnne_Deck/connections.inc =====
@ ===== BEGIN data/maps/SSAnne_B1F_Corridor/connections.inc =====

@ ===== END data/maps/SSAnne_B1F_Corridor/connections.inc =====
@ ===== BEGIN data/maps/SSAnne_2F_Room2/connections.inc =====

@ ===== END data/maps/SSAnne_2F_Room2/connections.inc =====
@ ===== BEGIN data/maps/SSAnne_2F_Corridor/connections.inc =====

@ ===== END data/maps/SSAnne_2F_Corridor/connections.inc =====
@ ===== BEGIN data/maps/SSAnne_1F_Corridor/connections.inc =====

@ ===== END data/maps/SSAnne_1F_Corridor/connections.inc =====
@ ===== BEGIN data/maps/SSAnne_Exterior/connections.inc =====

@ ===== END data/maps/SSAnne_Exterior/connections.inc =====
@ ===== BEGIN data/maps/MtMoon_B2F/connections.inc =====

@ ===== END data/maps/MtMoon_B2F/connections.inc =====
@ ===== BEGIN data/maps/MtMoon_B1F/connections.inc =====

@ ===== END data/maps/MtMoon_B1F/connections.inc =====
@ ===== BEGIN data/maps/MtMoon_1F/connections.inc =====

@ ===== END data/maps/MtMoon_1F/connections.inc =====
@ ===== BEGIN data/maps/ViridianForest/connections.inc =====

@ ===== END data/maps/ViridianForest/connections.inc =====
@ ===== BEGIN data/maps/UnionRoom/connections.inc =====

@ ===== END data/maps/UnionRoom/connections.inc =====
@ ===== BEGIN data/maps/BattleColosseum_4P/connections.inc =====

@ ===== END data/maps/BattleColosseum_4P/connections.inc =====
@ ===== BEGIN data/maps/RecordCorner/connections.inc =====

@ ===== END data/maps/RecordCorner/connections.inc =====
@ ===== BEGIN data/maps/TradeCenter/connections.inc =====

@ ===== END data/maps/TradeCenter/connections.inc =====
@ ===== BEGIN data/maps/UndergroundPath_NorthEntrance/connections.inc =====

@ ===== END data/maps/UndergroundPath_NorthEntrance/connections.inc =====
@ ===== BEGIN data/maps/VictoryRoad_3F/connections.inc =====

@ ===== END data/maps/VictoryRoad_3F/connections.inc =====
@ ===== BEGIN data/maps/VictoryRoad_2F/connections.inc =====

@ ===== END data/maps/VictoryRoad_2F/connections.inc =====
@ ===== BEGIN data/maps/VictoryRoad_1F/connections.inc =====

@ ===== END data/maps/VictoryRoad_1F/connections.inc =====
@ ===== BEGIN data/maps/DiglettsCave_SouthEntrance/connections.inc =====

@ ===== END data/maps/DiglettsCave_SouthEntrance/connections.inc =====
@ ===== BEGIN data/maps/DiglettsCave_B1F/connections.inc =====

@ ===== END data/maps/DiglettsCave_B1F/connections.inc =====
@ ===== BEGIN data/maps/DiglettsCave_NorthEntrance/connections.inc =====

@ ===== END data/maps/DiglettsCave_NorthEntrance/connections.inc =====
@ ===== BEGIN data/maps/UndergroundPath_EastEntrance/connections.inc =====

@ ===== END data/maps/UndergroundPath_EastEntrance/connections.inc =====
@ ===== BEGIN data/maps/UndergroundPath_EastWestTunnel/connections.inc =====

@ ===== END data/maps/UndergroundPath_EastWestTunnel/connections.inc =====
@ ===== BEGIN data/maps/UndergroundPath_WestEntrance/connections.inc =====

@ ===== END data/maps/UndergroundPath_WestEntrance/connections.inc =====
@ ===== BEGIN data/maps/UndergroundPath_SouthEntrance/connections.inc =====

@ ===== END data/maps/UndergroundPath_SouthEntrance/connections.inc =====
@ ===== BEGIN data/maps/UndergroundPath_NorthSouthTunnel/connections.inc =====

@ ===== END data/maps/UndergroundPath_NorthSouthTunnel/connections.inc =====
@ ===== BEGIN data/maps/PokemonTower_2F/connections.inc =====

@ ===== END data/maps/PokemonTower_2F/connections.inc =====
@ ===== BEGIN data/maps/SSAnne_1F_Room6/connections.inc =====

@ ===== END data/maps/SSAnne_1F_Room6/connections.inc =====
@ ===== BEGIN data/maps/SSAnne_B1F_Room5/connections.inc =====

@ ===== END data/maps/SSAnne_B1F_Room5/connections.inc =====
@ ===== BEGIN data/maps/SSAnne_B1F_Room4/connections.inc =====

@ ===== END data/maps/SSAnne_B1F_Room4/connections.inc =====
@ ===== BEGIN data/maps/SSAnne_B1F_Room3/connections.inc =====

@ ===== END data/maps/SSAnne_B1F_Room3/connections.inc =====
@ ===== BEGIN data/maps/SSAnne_B1F_Room2/connections.inc =====

@ ===== END data/maps/SSAnne_B1F_Room2/connections.inc =====
@ ===== BEGIN data/maps/SSAnne_B1F_Room1/connections.inc =====

@ ===== END data/maps/SSAnne_B1F_Room1/connections.inc =====
@ ===== BEGIN data/maps/SSAnne_2F_Room6/connections.inc =====

@ ===== END data/maps/SSAnne_2F_Room6/connections.inc =====
@ ===== BEGIN data/maps/SSAnne_2F_Room5/connections.inc =====

@ ===== END data/maps/SSAnne_2F_Room5/connections.inc =====
@ ===== BEGIN data/maps/SSAnne_2F_Room4/connections.inc =====

@ ===== END data/maps/SSAnne_2F_Room4/connections.inc =====
@ ===== BEGIN data/maps/SSAnne_2F_Room3/connections.inc =====

@ ===== END data/maps/SSAnne_2F_Room3/connections.inc =====
@ ===== BEGIN data/maps/FiveIsland_LostCave_Room13/connections.inc =====

@ ===== END data/maps/FiveIsland_LostCave_Room13/connections.inc =====
@ ===== BEGIN data/maps/NavelRock_1F/connections.inc =====

@ ===== END data/maps/NavelRock_1F/connections.inc =====
@ ===== BEGIN data/maps/SevenIsland_SevaultCanyon_TanobyKey/connections.inc =====

@ ===== END data/maps/SevenIsland_SevaultCanyon_TanobyKey/connections.inc =====
@ ===== BEGIN data/maps/ThreeIsland_DunsparceTunnel/connections.inc =====

@ ===== END data/maps/ThreeIsland_DunsparceTunnel/connections.inc =====
@ ===== BEGIN data/maps/SevenIsland_TanobyRuins_ViapoisChamber/connections.inc =====

@ ===== END data/maps/SevenIsland_TanobyRuins_ViapoisChamber/connections.inc =====
@ ===== BEGIN data/maps/SevenIsland_TanobyRuins_RixyChamber/connections.inc =====

@ ===== END data/maps/SevenIsland_TanobyRuins_RixyChamber/connections.inc =====
@ ===== BEGIN data/maps/SevenIsland_TanobyRuins_ScufibChamber/connections.inc =====

@ ===== END data/maps/SevenIsland_TanobyRuins_ScufibChamber/connections.inc =====
@ ===== BEGIN data/maps/SevenIsland_TanobyRuins_DilfordChamber/connections.inc =====

@ ===== END data/maps/SevenIsland_TanobyRuins_DilfordChamber/connections.inc =====
@ ===== BEGIN data/maps/SevenIsland_TanobyRuins_WeepthChamber/connections.inc =====

@ ===== END data/maps/SevenIsland_TanobyRuins_WeepthChamber/connections.inc =====
@ ===== BEGIN data/maps/SevenIsland_TanobyRuins_LiptooChamber/connections.inc =====

@ ===== END data/maps/SevenIsland_TanobyRuins_LiptooChamber/connections.inc =====
@ ===== BEGIN data/maps/SevenIsland_TanobyRuins_MoneanChamber/connections.inc =====

@ ===== END data/maps/SevenIsland_TanobyRuins_MoneanChamber/connections.inc =====
@ ===== BEGIN data/maps/FiveIsland_LostCave_Room14/connections.inc =====

@ ===== END data/maps/FiveIsland_LostCave_Room14/connections.inc =====
@ ===== BEGIN data/maps/NavelRock_Summit/connections.inc =====

@ ===== END data/maps/NavelRock_Summit/connections.inc =====
@ ===== BEGIN data/maps/FiveIsland_LostCave_Room12/connections.inc =====

@ ===== END data/maps/FiveIsland_LostCave_Room12/connections.inc =====
@ ===== BEGIN data/maps/FiveIsland_LostCave_Room11/connections.inc =====

@ ===== END data/maps/FiveIsland_LostCave_Room11/connections.inc =====
@ ===== BEGIN data/maps/FiveIsland_LostCave_Room10/connections.inc =====

@ ===== END data/maps/FiveIsland_LostCave_Room10/connections.inc =====
@ ===== BEGIN data/maps/FiveIsland_LostCave_Room9/connections.inc =====

@ ===== END data/maps/FiveIsland_LostCave_Room9/connections.inc =====
@ ===== BEGIN data/maps/FiveIsland_LostCave_Room8/connections.inc =====

@ ===== END data/maps/FiveIsland_LostCave_Room8/connections.inc =====
@ ===== BEGIN data/maps/FiveIsland_LostCave_Room7/connections.inc =====

@ ===== END data/maps/FiveIsland_LostCave_Room7/connections.inc =====
@ ===== BEGIN data/maps/FiveIsland_LostCave_Room6/connections.inc =====

@ ===== END data/maps/FiveIsland_LostCave_Room6/connections.inc =====
@ ===== BEGIN data/maps/FiveIsland_LostCave_Room5/connections.inc =====

@ ===== END data/maps/FiveIsland_LostCave_Room5/connections.inc =====
@ ===== BEGIN data/maps/FiveIsland_LostCave_Room4/connections.inc =====

@ ===== END data/maps/FiveIsland_LostCave_Room4/connections.inc =====
@ ===== BEGIN data/maps/FiveIsland_LostCave_Room3/connections.inc =====

@ ===== END data/maps/FiveIsland_LostCave_Room3/connections.inc =====
@ ===== BEGIN data/maps/FiveIsland_LostCave_Room2/connections.inc =====

@ ===== END data/maps/FiveIsland_LostCave_Room2/connections.inc =====
@ ===== BEGIN data/maps/NavelRock_BasePath_B6F/connections.inc =====

@ ===== END data/maps/NavelRock_BasePath_B6F/connections.inc =====
@ ===== BEGIN data/maps/NavelRock_Harbor/connections.inc =====

@ ===== END data/maps/NavelRock_Harbor/connections.inc =====
@ ===== BEGIN data/maps/BirthIsland_Harbor/connections.inc =====

@ ===== END data/maps/BirthIsland_Harbor/connections.inc =====
@ ===== BEGIN data/maps/OneIsland_KindleRoad_EmberSpa/connections.inc =====

@ ===== END data/maps/OneIsland_KindleRoad_EmberSpa/connections.inc =====
@ ===== BEGIN data/maps/BirthIsland_Exterior/connections.inc =====

@ ===== END data/maps/BirthIsland_Exterior/connections.inc =====
@ ===== BEGIN data/maps/NavelRock_Fork/connections.inc =====

@ ===== END data/maps/NavelRock_Fork/connections.inc =====
@ ===== BEGIN data/maps/NavelRock_B1F/connections.inc =====

@ ===== END data/maps/NavelRock_B1F/connections.inc =====
@ ===== BEGIN data/maps/NavelRock_BasePath_B11F/connections.inc =====

@ ===== END data/maps/NavelRock_BasePath_B11F/connections.inc =====
@ ===== BEGIN data/maps/NavelRock_BasePath_B10F/connections.inc =====

@ ===== END data/maps/NavelRock_BasePath_B10F/connections.inc =====
@ ===== BEGIN data/maps/NavelRock_BasePath_B9F/connections.inc =====

@ ===== END data/maps/NavelRock_BasePath_B9F/connections.inc =====
@ ===== BEGIN data/maps/NavelRock_BasePath_B8F/connections.inc =====

@ ===== END data/maps/NavelRock_BasePath_B8F/connections.inc =====
@ ===== BEGIN data/maps/NavelRock_BasePath_B7F/connections.inc =====

@ ===== END data/maps/NavelRock_BasePath_B7F/connections.inc =====
@ ===== BEGIN data/maps/FiveIsland_LostCave_Room1/connections.inc =====

@ ===== END data/maps/FiveIsland_LostCave_Room1/connections.inc =====
@ ===== BEGIN data/maps/NavelRock_BasePath_B5F/connections.inc =====

@ ===== END data/maps/NavelRock_BasePath_B5F/connections.inc =====
@ ===== BEGIN data/maps/NavelRock_BasePath_B4F/connections.inc =====

@ ===== END data/maps/NavelRock_BasePath_B4F/connections.inc =====
@ ===== BEGIN data/maps/NavelRock_BasePath_B3F/connections.inc =====

@ ===== END data/maps/NavelRock_BasePath_B3F/connections.inc =====
@ ===== BEGIN data/maps/NavelRock_BasePath_B2F/connections.inc =====

@ ===== END data/maps/NavelRock_BasePath_B2F/connections.inc =====
@ ===== BEGIN data/maps/NavelRock_BasePath_B1F/connections.inc =====

@ ===== END data/maps/NavelRock_BasePath_B1F/connections.inc =====
@ ===== BEGIN data/maps/NavelRock_SummitPath_5F/connections.inc =====

@ ===== END data/maps/NavelRock_SummitPath_5F/connections.inc =====
@ ===== BEGIN data/maps/NavelRock_SummitPath_4F/connections.inc =====

@ ===== END data/maps/NavelRock_SummitPath_4F/connections.inc =====
@ ===== BEGIN data/maps/NavelRock_SummitPath_3F/connections.inc =====

@ ===== END data/maps/NavelRock_SummitPath_3F/connections.inc =====
@ ===== BEGIN data/maps/NavelRock_SummitPath_2F/connections.inc =====

@ ===== END data/maps/NavelRock_SummitPath_2F/connections.inc =====
@ ===== BEGIN data/maps/NavelRock_Base/connections.inc =====

@ ===== END data/maps/NavelRock_Base/connections.inc =====
@ ===== BEGIN data/maps/MtEmber_Summit/connections.inc =====

@ ===== END data/maps/MtEmber_Summit/connections.inc =====
@ ===== BEGIN data/maps/FourIsland_IcefallCave_B1F/connections.inc =====

@ ===== END data/maps/FourIsland_IcefallCave_B1F/connections.inc =====
@ ===== BEGIN data/maps/FourIsland_IcefallCave_1F/connections.inc =====

@ ===== END data/maps/FourIsland_IcefallCave_1F/connections.inc =====
@ ===== BEGIN data/maps/FourIsland_IcefallCave_Entrance/connections.inc =====

@ ===== END data/maps/FourIsland_IcefallCave_Entrance/connections.inc =====
@ ===== BEGIN data/maps/ThreeIsland_BerryForest/connections.inc =====

@ ===== END data/maps/ThreeIsland_BerryForest/connections.inc =====
@ ===== BEGIN data/maps/MtEmber_RubyPath_B2F_Stairs/connections.inc =====

@ ===== END data/maps/MtEmber_RubyPath_B2F_Stairs/connections.inc =====
@ ===== BEGIN data/maps/MtEmber_RubyPath_B1F_Stairs/connections.inc =====

@ ===== END data/maps/MtEmber_RubyPath_B1F_Stairs/connections.inc =====
@ ===== BEGIN data/maps/MtEmber_RubyPath_B3F/connections.inc =====

@ ===== END data/maps/MtEmber_RubyPath_B3F/connections.inc =====
@ ===== BEGIN data/maps/MtEmber_RubyPath_B2F/connections.inc =====

@ ===== END data/maps/MtEmber_RubyPath_B2F/connections.inc =====
@ ===== BEGIN data/maps/MtEmber_RubyPath_B1F/connections.inc =====

@ ===== END data/maps/MtEmber_RubyPath_B1F/connections.inc =====
@ ===== BEGIN data/maps/MtEmber_RubyPath_1F/connections.inc =====

@ ===== END data/maps/MtEmber_RubyPath_1F/connections.inc =====
@ ===== BEGIN data/maps/MtEmber_RubyPath_B5F/connections.inc =====

@ ===== END data/maps/MtEmber_RubyPath_B5F/connections.inc =====
@ ===== BEGIN data/maps/FourIsland_IcefallCave_Back/connections.inc =====

@ ===== END data/maps/FourIsland_IcefallCave_Back/connections.inc =====
@ ===== BEGIN data/maps/MtEmber_SummitPath_3F/connections.inc =====

@ ===== END data/maps/MtEmber_SummitPath_3F/connections.inc =====
@ ===== BEGIN data/maps/MtEmber_SummitPath_2F/connections.inc =====

@ ===== END data/maps/MtEmber_SummitPath_2F/connections.inc =====
@ ===== BEGIN data/maps/MtEmber_SummitPath_1F/connections.inc =====

@ ===== END data/maps/MtEmber_SummitPath_1F/connections.inc =====
@ ===== BEGIN data/maps/MtEmber_Exterior/connections.inc =====

@ ===== END data/maps/MtEmber_Exterior/connections.inc =====
@ ===== BEGIN data/maps/MtEmber_RubyPath_B4F/connections.inc =====

@ ===== END data/maps/MtEmber_RubyPath_B4F/connections.inc =====
@ ===== BEGIN data/maps/PowerPlant/connections.inc =====

@ ===== END data/maps/PowerPlant/connections.inc =====
@ ===== BEGIN data/maps/PokemonTower_7F/connections.inc =====

@ ===== END data/maps/PokemonTower_7F/connections.inc =====
@ ===== BEGIN data/maps/PokemonTower_6F/connections.inc =====

@ ===== END data/maps/PokemonTower_6F/connections.inc =====
@ ===== BEGIN data/maps/PokemonTower_5F/connections.inc =====

@ ===== END data/maps/PokemonTower_5F/connections.inc =====
@ ===== BEGIN data/maps/PokemonTower_4F/connections.inc =====

@ ===== END data/maps/PokemonTower_4F/connections.inc =====
@ ===== BEGIN data/maps/PokemonTower_3F/connections.inc =====

@ ===== END data/maps/PokemonTower_3F/connections.inc =====
@ ===== BEGIN data/maps/TrainerTower_1F/connections.inc =====

@ ===== END data/maps/TrainerTower_1F/connections.inc =====
@ ===== BEGIN data/maps/FiveIsland_LostCave_Entrance/connections.inc =====

@ ===== END data/maps/FiveIsland_LostCave_Entrance/connections.inc =====
@ ===== BEGIN data/maps/TrainerTower_Elevator/connections.inc =====

@ ===== END data/maps/TrainerTower_Elevator/connections.inc =====
@ ===== BEGIN data/maps/TrainerTower_Lobby/connections.inc =====

@ ===== END data/maps/TrainerTower_Lobby/connections.inc =====
@ ===== BEGIN data/maps/TrainerTower_Roof/connections.inc =====

@ ===== END data/maps/TrainerTower_Roof/connections.inc =====
@ ===== BEGIN data/maps/TrainerTower_8F/connections.inc =====

@ ===== END data/maps/TrainerTower_8F/connections.inc =====
@ ===== BEGIN data/maps/TrainerTower_7F/connections.inc =====

@ ===== END data/maps/TrainerTower_7F/connections.inc =====
@ ===== BEGIN data/maps/TrainerTower_6F/connections.inc =====

@ ===== END data/maps/TrainerTower_6F/connections.inc =====
@ ===== BEGIN data/maps/TrainerTower_5F/connections.inc =====

@ ===== END data/maps/TrainerTower_5F/connections.inc =====
@ ===== BEGIN data/maps/TrainerTower_4F/connections.inc =====

@ ===== END data/maps/TrainerTower_4F/connections.inc =====
@ ===== BEGIN data/maps/TrainerTower_3F/connections.inc =====

@ ===== END data/maps/TrainerTower_3F/connections.inc =====
@ ===== BEGIN data/maps/TrainerTower_2F/connections.inc =====

@ ===== END data/maps/TrainerTower_2F/connections.inc =====
@ ===== BEGIN data/maps/FourIsland/connections.inc =====

@ ===== END data/maps/FourIsland/connections.inc =====
@ ===== BEGIN data/maps/NavelRock_Exterior/connections.inc =====

@ ===== END data/maps/NavelRock_Exterior/connections.inc =====
@ ===== BEGIN data/maps/SixIsland_AlteringCave/connections.inc =====

@ ===== END data/maps/SixIsland_AlteringCave/connections.inc =====
@ ===== BEGIN data/maps/SixIsland_PatternBush/connections.inc =====

@ ===== END data/maps/SixIsland_PatternBush/connections.inc =====
@ ===== BEGIN data/maps/SixIsland_DottedHole_SapphireRoom/connections.inc =====

@ ===== END data/maps/SixIsland_DottedHole_SapphireRoom/connections.inc =====
@ ===== BEGIN data/maps/SixIsland_DottedHole_B4F/connections.inc =====

@ ===== END data/maps/SixIsland_DottedHole_B4F/connections.inc =====
@ ===== BEGIN data/maps/SixIsland_DottedHole_B3F/connections.inc =====

@ ===== END data/maps/SixIsland_DottedHole_B3F/connections.inc =====
@ ===== BEGIN data/maps/SixIsland_DottedHole_B2F/connections.inc =====

@ ===== END data/maps/SixIsland_DottedHole_B2F/connections.inc =====
@ ===== BEGIN data/maps/SixIsland_DottedHole_B1F/connections.inc =====

@ ===== END data/maps/SixIsland_DottedHole_B1F/connections.inc =====
@ ===== BEGIN data/maps/SixIsland_DottedHole_1F/connections.inc =====

@ ===== END data/maps/SixIsland_DottedHole_1F/connections.inc =====
@ ===== BEGIN data/maps/FiveIsland_RocketWarehouse/connections.inc =====

@ ===== END data/maps/FiveIsland_RocketWarehouse/connections.inc =====
@ ===== END data/maps/connections.inc =====
