#include "constants/battle.h"
#include "constants/battle_anim.h"
#include "constants/battle_string_ids.h"
#include "constants/rgb.h"
#include "constants/songs.h"
#include "constants/sound.h"
#include "constants/moves.h"
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
@ ===== BEGIN asm/macros/battle_anim_script.inc =====
@ commands

	.macro loadspritegfx tag:req
	.byte 0x0
	.2byte \tag
	.endm

	.macro unloadspritegfx tag:req
	.byte 0x1
	.2byte \tag
	.endm

.macro createsprite template:req, anim_battler:req, subpriority_offset:req, argv:vararg
	.byte 0x02
	.4byte \template
	.if \anim_battler == ANIM_TARGET
	.byte ANIMSPRITE_IS_TARGET | (\subpriority_offset & 0x7F)
	.else
	.byte (\subpriority_offset & 0x7F)
	.endif
	.byte (.Lsprite_\@_2 - .Lsprite_\@_1) / 2
.Lsprite_\@_1:
	.2byte \argv
.Lsprite_\@_2:
	.endm

	.macro createvisualtask addr:req, priority:req, argv:vararg
	.byte 0x03
	.4byte \addr
	.byte \priority
	.byte (.Lcreatetask_\@_2 - .Lcreatetask_\@_1) / 2
.Lcreatetask_\@_1:
	.2byte \argv
.Lcreatetask_\@_2:
	.endm

	.macro delay frames:req
	.byte 0x4
	.byte \frames
	.endm

	.macro waitforvisualfinish
	.byte 0x5
	.endm

	.macro nop
	.byte 0x6
	.endm

	.macro nop2
	.byte 0x7
	.endm

	.macro end
	.byte 0x8
	.endm

	.macro playse se:req
	.byte 0x9
	.2byte \se
	.endm

	.macro monbg battler:req
	.byte 0xa
	.byte \battler
	.endm

	.macro clearmonbg battler:req
	.byte 0xb
	.byte \battler
	.endm

	.macro setalpha eva:req, evb:req
	.byte 0x0C
	.2byte ((\evb) << 8) | (\eva)
	.endm

	.macro blendoff
	.byte 0xd
	.endm

	.macro call ptr:req
	.byte 0xe
	.4byte \ptr
	.endm

	.macro return
	.byte 0xf
	.endm

	.macro setarg argId:req, value:req
	.byte 0x10
	.byte \argId
	.2byte \value
	.endm

	.macro choosetwoturnanim ptr1:req, ptr2:req
	.byte 0x11
	.4byte \ptr1
	.4byte \ptr2
	.endm

	.macro jumpifmoveturn value:req, ptr:req
	.byte 0x12
	.byte \value
	.4byte \ptr
	.endm

	.macro goto ptr:req
	.byte 0x13
	.4byte \ptr
	.endm

	.macro fadetobg bg:req
	.byte 0x14
	.byte \bg
	.endm

	.macro restorebg
	.byte 0x15
	.endm

	.macro waitbgfadeout
	.byte 0x16
	.endm

	.macro waitbgfadein
	.byte 0x17
	.endm

	.macro changebg bg:req
	.byte 0x18
	.byte \bg
	.endm

	.macro playsewithpan se:req, pan:req
	.byte 0x19
	.2byte \se
	.byte \pan
	.endm

	.macro setpan pan:req
	.byte 0x1a
	.byte \pan
	.endm

	.macro panse se:req, currentPan:req, targetPan:req, incrementPan:req, delay:req
	.byte 0x1b
	.2byte \se
	.byte \currentPan
	.byte \targetPan
	.byte \incrementPan
	.byte \delay
	.endm

	.macro loopsewithpan se:req, pan:req, wait:req, times:req
	.byte 0x1c
	.2byte \se
	.byte \pan
	.byte \wait
	.byte \times
	.endm

	.macro waitplaysewithpan se:req, pan:req, wait:req
	.byte 0x1d
	.2byte \se
	.byte \pan
	.byte \wait
	.endm

	.macro setbldcnt bldcnt:req
	.byte 0x1e
	.2byte \bldcnt
	.endm

	.macro createsoundtask addr:req, argv:vararg
	.byte 0x1F
	.4byte \addr
	.byte (.Lcreatetask_1F_\@_2 - .Lcreatetask_1F_\@_1) / 2
.Lcreatetask_1F_\@_1:
	.2byte \argv
.Lcreatetask_1F_\@_2:
	.endm

	.macro waitsound
	.byte 0x20
	.endm

	.macro jumpargeq argId:req, value:req, ptr:req
	.byte 0x21
	.byte \argId
	.2byte \value
	.4byte \ptr
	.endm

	.macro monbg_static battler:req
	.byte 0x22
	.byte \battler
	.endm

	.macro clearmonbg_static battler:req
	.byte 0x23
	.byte \battler
	.endm

	.macro jumpifcontest ptr:req
	.byte 0x24
	.4byte \ptr
	.endm

	.macro fadetobgfromset bgOpponent:req, bgPlayer:req, bgContest:req
	.byte 0x25
	.byte \bgOpponent
	.byte \bgPlayer
	.byte \bgContest
	.endm

	.macro panse_adjustnone se:req, currentPan:req, targetPan:req, incrementPan:req, delay:req
	.byte 0x26
	.2byte \se
	.byte \currentPan
	.byte \targetPan
	.byte \incrementPan
	.byte \delay
	.endm

	.macro panse_adjustall se:req, currentPan:req, targetPan:req, incrementPan:req, delay:req
	.byte 0x27
	.2byte \se
	.byte \currentPan
	.byte \targetPan
	.byte \incrementPan
	.byte \delay
	.endm

	.macro splitbgprio battler:req
	.byte 0x28
	.byte \battler
	.endm

	.macro splitbgprio_all
	.byte 0x29
	.endm

	.macro splitbgprio_foes battler:req
	.byte 0x2a
	.byte \battler
	.endm

	.macro invisible battler:req
	.byte 0x2b
	.byte \battler
	.endm

	.macro visible battler:req
	.byte 0x2c
	.byte \battler
	.endm

	.macro teamattack_moveback battler:req
	.byte 0x2d
	.byte \battler
	.endm

	.macro teamattack_movefwd battler:req
	.byte 0x2e
	.byte \battler
	.endm

	.macro stopsound
	.byte 0x2f
	.endm
	
@ useful macros
	.macro jumpreteq value:req, ptr:req
	jumpargeq ARG_RET_ID, \value, \ptr
	.endm
	
	.macro jumprettrue ptr:req
	jumpreteq TRUE, \ptr
	.endm
	
	.macro jumpretfalse ptr:req
	jumpreteq FALSE, \ptr
	.endm
@ ===== END asm/macros/battle_anim_script.inc =====
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

	.section script_data, "aw", %progbits

	.align 2
gMovesWithQuietBGM::
	.2byte MOVE_SING
	.2byte MOVE_PERISH_SONG
	.2byte MOVE_GRASS_WHISTLE
	.2byte 0xFFFF

	.align 2
gBattleAnims_Moves::
	.4byte Move_NONE
	.4byte Move_POUND
	.4byte Move_KARATE_CHOP
	.4byte Move_DOUBLE_SLAP
	.4byte Move_COMET_PUNCH
	.4byte Move_MEGA_PUNCH
	.4byte Move_PAY_DAY
	.4byte Move_FIRE_PUNCH
	.4byte Move_ICE_PUNCH
	.4byte Move_THUNDER_PUNCH
	.4byte Move_SCRATCH
	.4byte Move_VICE_GRIP
	.4byte Move_GUILLOTINE
	.4byte Move_RAZOR_WIND
	.4byte Move_SWORDS_DANCE
	.4byte Move_CUT
	.4byte Move_GUST
	.4byte Move_WING_ATTACK
	.4byte Move_WHIRLWIND
	.4byte Move_FLY
	.4byte Move_BIND
	.4byte Move_SLAM
	.4byte Move_VINE_WHIP
	.4byte Move_STOMP
	.4byte Move_DOUBLE_KICK
	.4byte Move_MEGA_KICK
	.4byte Move_JUMP_KICK
	.4byte Move_ROLLING_KICK
	.4byte Move_SAND_ATTACK
	.4byte Move_HEADBUTT
	.4byte Move_HORN_ATTACK
	.4byte Move_FURY_ATTACK
	.4byte Move_HORN_DRILL
	.4byte Move_TACKLE
	.4byte Move_BODY_SLAM
	.4byte Move_WRAP
	.4byte Move_TAKE_DOWN
	.4byte Move_THRASH
	.4byte Move_DOUBLE_EDGE
	.4byte Move_TAIL_WHIP
	.4byte Move_POISON_STING
	.4byte Move_TWINEEDLE
	.4byte Move_PIN_MISSILE
	.4byte Move_LEER
	.4byte Move_BITE
	.4byte Move_GROWL
	.4byte Move_ROAR
	.4byte Move_SING
	.4byte Move_SUPERSONIC
	.4byte Move_SONIC_BOOM
	.4byte Move_DISABLE
	.4byte Move_ACID
	.4byte Move_EMBER
	.4byte Move_FLAMETHROWER
	.4byte Move_MIST
	.4byte Move_WATER_GUN
	.4byte Move_HYDRO_PUMP
	.4byte Move_SURF
	.4byte Move_ICE_BEAM
	.4byte Move_BLIZZARD
	.4byte Move_PSYBEAM
	.4byte Move_BUBBLE_BEAM
	.4byte Move_AURORA_BEAM
	.4byte Move_HYPER_BEAM
	.4byte Move_PECK
	.4byte Move_DRILL_PECK
	.4byte Move_SUBMISSION
	.4byte Move_LOW_KICK
	.4byte Move_COUNTER
	.4byte Move_SEISMIC_TOSS
	.4byte Move_STRENGTH
	.4byte Move_ABSORB
	.4byte Move_MEGA_DRAIN
	.4byte Move_LEECH_SEED
	.4byte Move_GROWTH
	.4byte Move_RAZOR_LEAF
	.4byte Move_SOLAR_BEAM
	.4byte Move_POISON_POWDER
	.4byte Move_STUN_SPORE
	.4byte Move_SLEEP_POWDER
	.4byte Move_PETAL_DANCE
	.4byte Move_STRING_SHOT
	.4byte Move_DRAGON_RAGE
	.4byte Move_FIRE_SPIN
	.4byte Move_THUNDER_SHOCK
	.4byte Move_THUNDERBOLT
	.4byte Move_THUNDER_WAVE
	.4byte Move_THUNDER
	.4byte Move_ROCK_THROW
	.4byte Move_EARTHQUAKE
	.4byte Move_FISSURE
	.4byte Move_DIG
	.4byte Move_TOXIC
	.4byte Move_CONFUSION
	.4byte Move_PSYCHIC
	.4byte Move_HYPNOSIS
	.4byte Move_MEDITATE
	.4byte Move_AGILITY
	.4byte Move_QUICK_ATTACK
	.4byte Move_RAGE
	.4byte Move_TELEPORT
	.4byte Move_NIGHT_SHADE
	.4byte Move_MIMIC
	.4byte Move_SCREECH
	.4byte Move_DOUBLE_TEAM
	.4byte Move_RECOVER
	.4byte Move_HARDEN
	.4byte Move_MINIMIZE
	.4byte Move_SMOKESCREEN
	.4byte Move_CONFUSE_RAY
	.4byte Move_WITHDRAW
	.4byte Move_DEFENSE_CURL
	.4byte Move_BARRIER
	.4byte Move_LIGHT_SCREEN
	.4byte Move_HAZE
	.4byte Move_REFLECT
	.4byte Move_FOCUS_ENERGY
	.4byte Move_BIDE
	.4byte Move_METRONOME
	.4byte Move_MIRROR_MOVE
	.4byte Move_SELF_DESTRUCT
	.4byte Move_EGG_BOMB
	.4byte Move_LICK
	.4byte Move_SMOG
	.4byte Move_SLUDGE
	.4byte Move_BONE_CLUB
	.4byte Move_FIRE_BLAST
	.4byte Move_WATERFALL
	.4byte Move_CLAMP
	.4byte Move_SWIFT
	.4byte Move_SKULL_BASH
	.4byte Move_SPIKE_CANNON
	.4byte Move_CONSTRICT
	.4byte Move_AMNESIA
	.4byte Move_KINESIS
	.4byte Move_SOFT_BOILED
	.4byte Move_HI_JUMP_KICK
	.4byte Move_GLARE
	.4byte Move_DREAM_EATER
	.4byte Move_POISON_GAS
	.4byte Move_BARRAGE
	.4byte Move_LEECH_LIFE
	.4byte Move_LOVELY_KISS
	.4byte Move_SKY_ATTACK
	.4byte Move_TRANSFORM
	.4byte Move_BUBBLE
	.4byte Move_DIZZY_PUNCH
	.4byte Move_SPORE
	.4byte Move_FLASH
	.4byte Move_PSYWAVE
	.4byte Move_SPLASH
	.4byte Move_ACID_ARMOR
	.4byte Move_CRABHAMMER
	.4byte Move_EXPLOSION
	.4byte Move_FURY_SWIPES
	.4byte Move_BONEMERANG
	.4byte Move_REST
	.4byte Move_ROCK_SLIDE
	.4byte Move_HYPER_FANG
	.4byte Move_SHARPEN
	.4byte Move_CONVERSION
	.4byte Move_TRI_ATTACK
	.4byte Move_SUPER_FANG
	.4byte Move_SLASH
	.4byte Move_SUBSTITUTE
	.4byte Move_STRUGGLE
	.4byte Move_SKETCH
	.4byte Move_TRIPLE_KICK
	.4byte Move_THIEF
	.4byte Move_SPIDER_WEB
	.4byte Move_MIND_READER
	.4byte Move_NIGHTMARE
	.4byte Move_FLAME_WHEEL
	.4byte Move_SNORE
	.4byte Move_CURSE
	.4byte Move_FLAIL
	.4byte Move_CONVERSION_2
	.4byte Move_AEROBLAST
	.4byte Move_COTTON_SPORE
	.4byte Move_REVERSAL
	.4byte Move_SPITE
	.4byte Move_POWDER_SNOW
	.4byte Move_PROTECT
	.4byte Move_MACH_PUNCH
	.4byte Move_SCARY_FACE
	.4byte Move_FAINT_ATTACK
	.4byte Move_SWEET_KISS
	.4byte Move_BELLY_DRUM
	.4byte Move_SLUDGE_BOMB
	.4byte Move_MUD_SLAP
	.4byte Move_OCTAZOOKA
	.4byte Move_SPIKES
	.4byte Move_ZAP_CANNON
	.4byte Move_FORESIGHT
	.4byte Move_DESTINY_BOND
	.4byte Move_PERISH_SONG
	.4byte Move_ICY_WIND
	.4byte Move_DETECT
	.4byte Move_BONE_RUSH
	.4byte Move_LOCK_ON
	.4byte Move_OUTRAGE
	.4byte Move_SANDSTORM
	.4byte Move_GIGA_DRAIN
	.4byte Move_ENDURE
	.4byte Move_CHARM
	.4byte Move_ROLLOUT
	.4byte Move_FALSE_SWIPE
	.4byte Move_SWAGGER
	.4byte Move_MILK_DRINK
	.4byte Move_SPARK
	.4byte Move_FURY_CUTTER
	.4byte Move_STEEL_WING
	.4byte Move_MEAN_LOOK
	.4byte Move_ATTRACT
	.4byte Move_SLEEP_TALK
	.4byte Move_HEAL_BELL
	.4byte Move_RETURN
	.4byte Move_PRESENT
	.4byte Move_FRUSTRATION
	.4byte Move_SAFEGUARD
	.4byte Move_PAIN_SPLIT
	.4byte Move_SACRED_FIRE
	.4byte Move_MAGNITUDE
	.4byte Move_DYNAMIC_PUNCH
	.4byte Move_MEGAHORN
	.4byte Move_DRAGON_BREATH
	.4byte Move_BATON_PASS
	.4byte Move_ENCORE
	.4byte Move_PURSUIT
	.4byte Move_RAPID_SPIN
	.4byte Move_SWEET_SCENT
	.4byte Move_IRON_TAIL
	.4byte Move_METAL_CLAW
	.4byte Move_VITAL_THROW
	.4byte Move_MORNING_SUN
	.4byte Move_SYNTHESIS
	.4byte Move_MOONLIGHT
	.4byte Move_HIDDEN_POWER
	.4byte Move_CROSS_CHOP
	.4byte Move_TWISTER
	.4byte Move_RAIN_DANCE
	.4byte Move_SUNNY_DAY
	.4byte Move_CRUNCH
	.4byte Move_MIRROR_COAT
	.4byte Move_PSYCH_UP
	.4byte Move_EXTREME_SPEED
	.4byte Move_ANCIENT_POWER
	.4byte Move_SHADOW_BALL
	.4byte Move_FUTURE_SIGHT
	.4byte Move_ROCK_SMASH
	.4byte Move_WHIRLPOOL
	.4byte Move_BEAT_UP
	.4byte Move_FAKE_OUT
	.4byte Move_UPROAR
	.4byte Move_STOCKPILE
	.4byte Move_SPIT_UP
	.4byte Move_SWALLOW
	.4byte Move_HEAT_WAVE
	.4byte Move_HAIL
	.4byte Move_TORMENT
	.4byte Move_FLATTER
	.4byte Move_WILL_O_WISP
	.4byte Move_MEMENTO
	.4byte Move_FACADE
	.4byte Move_FOCUS_PUNCH
	.4byte Move_SMELLING_SALT
	.4byte Move_FOLLOW_ME
	.4byte Move_NATURE_POWER
	.4byte Move_CHARGE
	.4byte Move_TAUNT
	.4byte Move_HELPING_HAND
	.4byte Move_TRICK
	.4byte Move_ROLE_PLAY
	.4byte Move_WISH
	.4byte Move_ASSIST
	.4byte Move_INGRAIN
	.4byte Move_SUPERPOWER
	.4byte Move_MAGIC_COAT
	.4byte Move_RECYCLE
	.4byte Move_REVENGE
	.4byte Move_BRICK_BREAK
	.4byte Move_YAWN
	.4byte Move_KNOCK_OFF
	.4byte Move_ENDEAVOR
	.4byte Move_ERUPTION
	.4byte Move_SKILL_SWAP
	.4byte Move_IMPRISON
	.4byte Move_REFRESH
	.4byte Move_GRUDGE
	.4byte Move_SNATCH
	.4byte Move_SECRET_POWER
	.4byte Move_DIVE
	.4byte Move_ARM_THRUST
	.4byte Move_CAMOUFLAGE
	.4byte Move_TAIL_GLOW
	.4byte Move_LUSTER_PURGE
	.4byte Move_MIST_BALL
	.4byte Move_FEATHER_DANCE
	.4byte Move_TEETER_DANCE
	.4byte Move_BLAZE_KICK
	.4byte Move_MUD_SPORT
	.4byte Move_ICE_BALL
	.4byte Move_NEEDLE_ARM
	.4byte Move_SLACK_OFF
	.4byte Move_HYPER_VOICE
	.4byte Move_POISON_FANG
	.4byte Move_CRUSH_CLAW
	.4byte Move_BLAST_BURN
	.4byte Move_HYDRO_CANNON
	.4byte Move_METEOR_MASH
	.4byte Move_ASTONISH
	.4byte Move_WEATHER_BALL
	.4byte Move_AROMATHERAPY
	.4byte Move_FAKE_TEARS
	.4byte Move_AIR_CUTTER
	.4byte Move_OVERHEAT
	.4byte Move_ODOR_SLEUTH
	.4byte Move_ROCK_TOMB
	.4byte Move_SILVER_WIND
	.4byte Move_METAL_SOUND
	.4byte Move_GRASS_WHISTLE
	.4byte Move_TICKLE
	.4byte Move_COSMIC_POWER
	.4byte Move_WATER_SPOUT
	.4byte Move_SIGNAL_BEAM
	.4byte Move_SHADOW_PUNCH
	.4byte Move_EXTRASENSORY
	.4byte Move_SKY_UPPERCUT
	.4byte Move_SAND_TOMB
	.4byte Move_SHEER_COLD
	.4byte Move_MUDDY_WATER
	.4byte Move_BULLET_SEED
	.4byte Move_AERIAL_ACE
	.4byte Move_ICICLE_SPEAR
	.4byte Move_IRON_DEFENSE
	.4byte Move_BLOCK
	.4byte Move_HOWL
	.4byte Move_DRAGON_CLAW
	.4byte Move_FRENZY_PLANT
	.4byte Move_BULK_UP
	.4byte Move_BOUNCE
	.4byte Move_MUD_SHOT
	.4byte Move_POISON_TAIL
	.4byte Move_COVET
	.4byte Move_VOLT_TACKLE
	.4byte Move_MAGICAL_LEAF
	.4byte Move_WATER_SPORT
	.4byte Move_CALM_MIND
	.4byte Move_LEAF_BLADE
	.4byte Move_DRAGON_DANCE
	.4byte Move_ROCK_BLAST
	.4byte Move_SHOCK_WAVE
	.4byte Move_WATER_PULSE
	.4byte Move_DOOM_DESIRE
	.4byte Move_PSYCHO_BOOST
	.4byte Move_COUNT @ cannot be reached, because last move is Psycho Boost

	.align 2
gBattleAnims_StatusConditions::
	.4byte Status_Poison                    @ B_ANIM_STATUS_PSN
	.4byte Status_Confusion                 @ B_ANIM_STATUS_CONFUSION
	.4byte Status_Burn                      @ B_ANIM_STATUS_BRN
	.4byte Status_Infatuation               @ B_ANIM_STATUS_INFATUATION
	.4byte Status_Sleep                     @ B_ANIM_STATUS_SLP
	.4byte Status_Paralysis                 @ B_ANIM_STATUS_PRZ
	.4byte Status_Freeze                    @ B_ANIM_STATUS_FRZ
	.4byte Status_Curse                     @ B_ANIM_STATUS_CURSED
	.4byte Status_Nightmare                 @ B_ANIM_STATUS_NIGHTMARE

	.align 2
gBattleAnims_General::
	.4byte General_CastformChange           @ B_ANIM_CASTFORM_CHANGE
	.4byte General_StatsChange              @ B_ANIM_STATS_CHANGE
	.4byte General_SubstituteFade           @ B_ANIM_SUBSTITUTE_FADE
	.4byte General_SubstituteAppear         @ B_ANIM_SUBSTITUTE_APPEAR
	.4byte General_BaitThrow                @ B_ANIM_BAIT_THROW
	.4byte General_ItemKnockoff             @ B_ANIM_ITEM_KNOCKOFF
	.4byte General_TurnTrap                 @ B_ANIM_TURN_TRAP
	.4byte General_HeldItemEffect           @ B_ANIM_HELD_ITEM_EFFECT
	.4byte General_SmokeballEscape          @ B_ANIM_SMOKEBALL_ESCAPE
	.4byte General_FocusBand                @ B_ANIM_FOCUS_BAND
	.4byte General_Rain                     @ B_ANIM_RAIN_CONTINUES
	.4byte General_Sun                      @ B_ANIM_SUN_CONTINUES
	.4byte General_Sandstorm                @ B_ANIM_SANDSTORM_CONTINUES
	.4byte General_Hail                     @ B_ANIM_HAIL_CONTINUES
	.4byte General_LeechSeedDrain           @ B_ANIM_LEECH_SEED_DRAIN
	.4byte General_MonHit                   @ B_ANIM_MON_HIT
	.4byte General_ItemSteal                @ B_ANIM_ITEM_STEAL
	.4byte General_SnatchMove               @ B_ANIM_SNATCH_MOVE
	.4byte General_FutureSightHit           @ B_ANIM_FUTURE_SIGHT_HIT
	.4byte General_DoomDesireHit            @ B_ANIM_DOOM_DESIRE_HIT
	.4byte General_FocusPunchSetUp          @ B_ANIM_FOCUS_PUNCH_SETUP
	.4byte General_IngrainHeal              @ B_ANIM_INGRAIN_HEAL
	.4byte General_WishHeal                 @ B_ANIM_WISH_HEAL
	.4byte General_MonScared                @ B_ANIM_MON_SCARED
	.4byte General_GhostGetOut              @ B_ANIM_GHOST_GET_OUT
	.4byte General_SilphScoped              @ B_ANIM_SILPH_SCOPED
	.4byte General_SafariRockThrow          @ B_ANIM_ROCK_THROW
	.4byte General_SafariReaction           @ B_ANIM_SAFARI_REACTION

	.align 2
gBattleAnims_Special::
	.4byte Special_LevelUp                  @ B_ANIM_LVL_UP
	.4byte Special_SwitchOutPlayerMon       @ B_ANIM_SWITCH_OUT_PLAYER_MON
	.4byte Special_SwitchOutOpponentMon     @ B_ANIM_SWITCH_OUT_OPPONENT_MON
	.4byte Special_BallThrow                @ B_ANIM_BALL_THROW
	.4byte Special_BallThrowWithTrainer     @ B_ANIM_BALL_THROW_WITH_TRAINER
	.4byte Special_SubstituteToMon          @ B_ANIM_SUBSTITUTE_TO_MON
	.4byte Special_MonToSubstitute          @ B_ANIM_MON_TO_SUBSTITUTE

Move_NONE:
Move_MIRROR_MOVE:
Move_POUND:
	loadspritegfx ANIM_TAG_IMPACT
	monbg ANIM_TARGET
	setalpha 12, 8
	playsewithpan SE_M_DOUBLE_SLAP, SOUND_PAN_TARGET
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 2, 0, 0, ANIM_TARGET, 2
	createvisualtask AnimTask_ShakeMon, 2, ANIM_TARGET, 3, 0, 6, 1
	waitforvisualfinish
	clearmonbg ANIM_TARGET
	blendoff
	end

Move_DOUBLE_SLAP:
	loadspritegfx ANIM_TAG_IMPACT
	monbg ANIM_TARGET
	setalpha 12, 8
	choosetwoturnanim DoubleSlapLeft, DoubleSlapRight

DoubleSlapContinue:
	createvisualtask AnimTask_ShakeMon, 2, ANIM_TARGET, 3, 0, 6, 1
	playsewithpan SE_M_DOUBLE_SLAP, SOUND_PAN_TARGET
	waitforvisualfinish
	clearmonbg ANIM_TARGET
	blendoff
	end

DoubleSlapLeft:
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 2, -8, 0, ANIM_TARGET, 2
	goto DoubleSlapContinue

DoubleSlapRight:
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 2, 8, 0, ANIM_TARGET, 2
	goto DoubleSlapContinue

Move_POISON_POWDER:
	loadspritegfx ANIM_TAG_POISON_POWDER
	loadspritegfx ANIM_TAG_POISON_BUBBLE
	loopsewithpan SE_M_POISON_POWDER, SOUND_PAN_TARGET, 10, 6
	createsprite gPoisonPowderParticleSpriteTemplate, ANIM_TARGET, 2, -30, -22, 117, 80, 5, 1
	createsprite gPoisonPowderParticleSpriteTemplate, ANIM_TARGET, 2, 10, -22, 117, 80, -5, 1
	createsprite gPoisonPowderParticleSpriteTemplate, ANIM_TARGET, 2, -25, -22, 117, 112, 5, 3
	delay 15
	createsprite gPoisonPowderParticleSpriteTemplate, ANIM_TARGET, 2, -5, -22, 117, 80, -5, 1
	createsprite gPoisonPowderParticleSpriteTemplate, ANIM_TARGET, 2, 5, -22, 117, 96, 5, 1
	createsprite gPoisonPowderParticleSpriteTemplate, ANIM_TARGET, 2, 0, -22, 117, 69, -5, 1
	createsprite gPoisonPowderParticleSpriteTemplate, ANIM_TARGET, 2, -15, -22, 117, 112, 5, 2
	delay 30
	createsprite gPoisonPowderParticleSpriteTemplate, ANIM_TARGET, 2, -15, -22, 117, 112, 5, 2
	createsprite gPoisonPowderParticleSpriteTemplate, ANIM_TARGET, 2, 15, -22, 117, 80, -5, 1
	createsprite gPoisonPowderParticleSpriteTemplate, ANIM_TARGET, 2, -10, -22, 117, 96, 7, 2
	createsprite gPoisonPowderParticleSpriteTemplate, ANIM_TARGET, 2, -5, -22, 117, 90, -8, 0
	delay 20
	createsprite gPoisonPowderParticleSpriteTemplate, ANIM_TARGET, 2, -10, -22, 117, 80, -5, 1
	createsprite gPoisonPowderParticleSpriteTemplate, ANIM_TARGET, 2, 0, -22, 117, 89, 5, 2
	createsprite gPoisonPowderParticleSpriteTemplate, ANIM_TARGET, 2, 20, -22, 117, 112, -8, 2
	createsprite gPoisonPowderParticleSpriteTemplate, ANIM_TARGET, 2, 5, -22, 117, 80, 5, 1
	waitforvisualfinish
	end

Move_STUN_SPORE:
	loadspritegfx ANIM_TAG_STUN_SPORE
	loopsewithpan SE_M_POISON_POWDER, SOUND_PAN_TARGET, 10, 6
	createsprite gStunSporeParticleSpriteTemplate, ANIM_TARGET, 2, -30, -22, 117, 80, 5, 1
	createsprite gStunSporeParticleSpriteTemplate, ANIM_TARGET, 2, 10, -22, 117, 80, -5, 1
	createsprite gStunSporeParticleSpriteTemplate, ANIM_TARGET, 2, -25, -22, 117, 112, 5, 3
	delay 15
	createsprite gStunSporeParticleSpriteTemplate, ANIM_TARGET, 2, -5, -22, 117, 80, -5, 1
	createsprite gStunSporeParticleSpriteTemplate, ANIM_TARGET, 2, 5, -22, 117, 96, 5, 1
	createsprite gStunSporeParticleSpriteTemplate, ANIM_TARGET, 2, 0, -22, 117, 69, -5, 1
	createsprite gStunSporeParticleSpriteTemplate, ANIM_TARGET, 2, -15, -22, 117, 112, 5, 2
	delay 30
	createsprite gStunSporeParticleSpriteTemplate, ANIM_TARGET, 2, -15, -22, 117, 112, 5, 2
	createsprite gStunSporeParticleSpriteTemplate, ANIM_TARGET, 2, 15, -22, 117, 80, -5, 1
	createsprite gStunSporeParticleSpriteTemplate, ANIM_TARGET, 2, -10, -22, 117, 96, 7, 2
	createsprite gStunSporeParticleSpriteTemplate, ANIM_TARGET, 2, -5, -22, 117, 90, -8, 0
	delay 20
	createsprite gStunSporeParticleSpriteTemplate, ANIM_TARGET, 2, -10, -22, 117, 80, -5, 1
	createsprite gStunSporeParticleSpriteTemplate, ANIM_TARGET, 2, 0, -22, 117, 89, 5, 2
	createsprite gStunSporeParticleSpriteTemplate, ANIM_TARGET, 2, 20, -22, 117, 112, -8, 2
	createsprite gStunSporeParticleSpriteTemplate, ANIM_TARGET, 2, 5, -22, 117, 80, 5, 1
	waitforvisualfinish
	end

Move_SLEEP_POWDER:
	loadspritegfx ANIM_TAG_SLEEP_POWDER
	loopsewithpan SE_M_POISON_POWDER, SOUND_PAN_TARGET, 10, 6
	createsprite gSleepPowderParticleSpriteTemplate, ANIM_TARGET, 2, -30, -22, 117, 80, 5, 1
	createsprite gSleepPowderParticleSpriteTemplate, ANIM_TARGET, 2, 10, -22, 117, 80, -5, 1
	createsprite gSleepPowderParticleSpriteTemplate, ANIM_TARGET, 2, -25, -22, 117, 112, 5, 3
	delay 15
	createsprite gSleepPowderParticleSpriteTemplate, ANIM_TARGET, 2, -5, -22, 117, 80, -5, 1
	createsprite gSleepPowderParticleSpriteTemplate, ANIM_TARGET, 2, 5, -22, 117, 96, 5, 1
	createsprite gSleepPowderParticleSpriteTemplate, ANIM_TARGET, 2, 0, -22, 117, 69, -5, 1
	createsprite gSleepPowderParticleSpriteTemplate, ANIM_TARGET, 2, -15, -22, 117, 112, 5, 2
	delay 30
	createsprite gSleepPowderParticleSpriteTemplate, ANIM_TARGET, 2, -15, -22, 117, 112, 5, 2
	createsprite gSleepPowderParticleSpriteTemplate, ANIM_TARGET, 2, 15, -22, 117, 80, -5, 1
	createsprite gSleepPowderParticleSpriteTemplate, ANIM_TARGET, 2, -10, -22, 117, 96, 7, 2
	createsprite gSleepPowderParticleSpriteTemplate, ANIM_TARGET, 2, -5, -22, 117, 90, -8, 0
	delay 20
	createsprite gSleepPowderParticleSpriteTemplate, ANIM_TARGET, 2, -10, -22, 117, 80, -5, 1
	createsprite gSleepPowderParticleSpriteTemplate, ANIM_TARGET, 2, 0, -22, 117, 89, 5, 2
	createsprite gSleepPowderParticleSpriteTemplate, ANIM_TARGET, 2, 20, -22, 117, 112, -8, 2
	createsprite gSleepPowderParticleSpriteTemplate, ANIM_TARGET, 2, 5, -22, 117, 80, 5, 1
	waitforvisualfinish
	end

Move_SWIFT:
	loadspritegfx ANIM_TAG_YELLOW_STAR
	loadspritegfx ANIM_TAG_IMPACT
	monbg ANIM_DEF_PARTNER
	setalpha 12, 8
	playsewithpan SE_M_SWIFT, SOUND_PAN_ATTACKER
	createsprite gSwiftStarSpriteTemplate, ANIM_TARGET, 3, 20, -10, 20, 0, 22, 20, 1
	delay 5
	playsewithpan SE_M_SWIFT, SOUND_PAN_ATTACKER
	createsprite gSwiftStarSpriteTemplate, ANIM_TARGET, 3, 20, -10, 20, 5, 22, -18, 1
	delay 5
	playsewithpan SE_M_SWIFT, SOUND_PAN_ATTACKER
	createsprite gSwiftStarSpriteTemplate, ANIM_TARGET, 3, 20, -10, 20, -10, 22, 15, 1
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_TARGET, 2, 0, 18, 1
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_DEF_PARTNER, 2, 0, 18, 1
	delay 5
	playsewithpan SE_M_SWIFT, SOUND_PAN_ATTACKER
	createsprite gSwiftStarSpriteTemplate, ANIM_TARGET, 3, 20, -10, 20, 0, 22, -20, 1
	delay 5
	playsewithpan SE_M_SWIFT, SOUND_PAN_ATTACKER
	createsprite gSwiftStarSpriteTemplate, ANIM_TARGET, 3, 20, -10, 20, 0, 22, 12, 1
	delay 5
	waitforvisualfinish
	clearmonbg ANIM_DEF_PARTNER
	blendoff
	end

Move_STRENGTH:
	loadspritegfx ANIM_TAG_IMPACT
	monbg ANIM_DEF_PARTNER
	setalpha 12, 8
	playsewithpan SE_M_TAKE_DOWN, SOUND_PAN_ATTACKER
	createvisualtask AnimTask_ShakeAndSinkMon, 5, ANIM_ATTACKER, 2, 0, 96, 30
	waitforvisualfinish
	delay 10
	createsprite gSlideMonToOriginalPosSpriteTemplate, ANIM_ATTACKER, 2, 0, 0, 4
	createvisualtask AnimTask_TranslateMonEllipticalRespectSide, 2, ANIM_TARGET, 18, 6, 2, 4
	delay 4
	playsewithpan SE_M_MEGA_KICK2, SOUND_PAN_TARGET
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 3, 16, 12, ANIM_TARGET, 1
	delay 4
	playsewithpan SE_M_MEGA_KICK2, SOUND_PAN_TARGET
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 3, -16, -12, ANIM_TARGET, 1
	delay 4
	playsewithpan SE_M_MEGA_KICK2, SOUND_PAN_TARGET
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 3, 3, 4, ANIM_TARGET, 1
	waitforvisualfinish
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_TARGET, 2, 0, 8, 1
	waitforvisualfinish
	clearmonbg ANIM_DEF_PARTNER
	blendoff
	end

Move_TACKLE:
	loadspritegfx ANIM_TAG_IMPACT
	monbg ANIM_TARGET
	setalpha 12, 8
	createsprite gHorizontalLungeSpriteTemplate, ANIM_ATTACKER, 2, 4, 4
	delay 6
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 2, 0, 0, ANIM_TARGET, 2
	createvisualtask AnimTask_ShakeMon, 2, ANIM_TARGET, 3, 0, 6, 1
	playsewithpan SE_M_COMET_PUNCH, SOUND_PAN_TARGET
	waitforvisualfinish
	clearmonbg ANIM_TARGET
	blendoff
	end

Move_BODY_SLAM:
	loadspritegfx ANIM_TAG_IMPACT
	monbg ANIM_DEF_PARTNER
	setalpha 12, 8
	playsewithpan SE_M_TAKE_DOWN, SOUND_PAN_ATTACKER
	createsprite gVerticalDipSpriteTemplate, ANIM_ATTACKER, 2, 6, 1, ANIM_ATTACKER
	waitforvisualfinish
	delay 11
	createsprite gSlideMonToOffsetSpriteTemplate, ANIM_ATTACKER, 2, 0, 26, 0, 0, 5
	delay 6
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 4, -10, 0, ANIM_TARGET, 0
	loopsewithpan SE_M_MEGA_KICK2, SOUND_PAN_TARGET, 10, 2
	delay 1
	createsprite gSlideMonToOffsetSpriteTemplate, ANIM_ATTACKER, 2, 1, -28, 0, 0, 3
	waitforvisualfinish
	createvisualtask AnimTask_ShakeMonInPlace, 2, ANIM_TARGET, 4, 0, 12, 1
	waitforvisualfinish
	delay 10
	createsprite gSlideMonToOriginalPosSpriteTemplate, ANIM_ATTACKER, 2, 0, 0, 6
	delay 5
	createsprite gSlideMonToOriginalPosSpriteTemplate, ANIM_ATTACKER, 2, 1, 0, 6
	waitforvisualfinish
	clearmonbg ANIM_DEF_PARTNER
	blendoff
	end

Move_SUPERSONIC:
	loadspritegfx ANIM_TAG_GOLD_RING
	monbg ANIM_ATK_PARTNER
	splitbgprio_foes ANIM_ATTACKER
	setalpha 12, 8
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_ATTACKER, 2, 0, 8, 1
	call SupersonicRing
	call SupersonicRing
	call SupersonicRing
	call SupersonicRing
	call SupersonicRing
	call SupersonicRing
	waitforvisualfinish
	clearmonbg ANIM_ATK_PARTNER
	blendoff
	end

SupersonicRing:
	playsewithpan SE_M_SUPERSONIC, SOUND_PAN_ATTACKER
	createsprite gSupersonicRingSpriteTemplate, ANIM_TARGET, 2, 16, 0, 0, 0, 30, 0
	delay 2
	return

Move_SCREECH:
	loadspritegfx ANIM_TAG_PURPLE_RING
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_ATTACKER, 3, 0, 2, 1
	call ScreechRing
	call ScreechRing
	delay 16
	createvisualtask AnimTask_SwayMon, 5, 0, 6, 2048, 2, ANIM_TARGET
	waitforvisualfinish
	end

ScreechRing:
	playsewithpan SE_M_SCREECH, SOUND_PAN_ATTACKER
	createsprite gScreechRingSpriteTemplate, ANIM_TARGET, 2, 16, 0, 0, 0, 30, 0
	delay 2
	return

Move_FLAME_WHEEL:
	loadspritegfx ANIM_TAG_SMALL_EMBER
	monbg ANIM_DEF_PARTNER
	splitbgprio_foes ANIM_TARGET
	createsprite gFireSpiralOutwardSpriteTemplate, ANIM_ATTACKER, 3, 0, 0, 56, 0
	playsewithpan SE_M_FLAME_WHEEL, SOUND_PAN_ATTACKER
	delay 2
	createsprite gFireSpiralOutwardSpriteTemplate, ANIM_ATTACKER, 3, 0, 0, 56, 4
	playsewithpan SE_M_FLAME_WHEEL, SOUND_PAN_ATTACKER
	delay 2
	createsprite gFireSpiralOutwardSpriteTemplate, ANIM_ATTACKER, 3, 0, 0, 56, 8
	playsewithpan SE_M_FLAME_WHEEL, SOUND_PAN_ATTACKER
	delay 2
	createsprite gFireSpiralOutwardSpriteTemplate, ANIM_ATTACKER, 3, 0, 0, 56, 12
	playsewithpan SE_M_FLAME_WHEEL, SOUND_PAN_ATTACKER
	delay 2
	createsprite gFireSpiralOutwardSpriteTemplate, ANIM_ATTACKER, 3, 0, 0, 56, 16
	playsewithpan SE_M_FLAME_WHEEL, SOUND_PAN_ATTACKER
	delay 2
	createsprite gFireSpiralOutwardSpriteTemplate, ANIM_ATTACKER, 3, 0, 0, 56, 20
	playsewithpan SE_M_FLAME_WHEEL, SOUND_PAN_ATTACKER
	delay 2
	createsprite gFireSpiralOutwardSpriteTemplate, ANIM_ATTACKER, 3, 0, 0, 56, 24
	playsewithpan SE_M_FLAME_WHEEL, SOUND_PAN_ATTACKER
	waitforvisualfinish
	createsprite gSlideMonToOffsetSpriteTemplate, ANIM_ATTACKER, 2, 0, 24, 0, 0, 6
	delay 4
	createvisualtask AnimTask_ShakeMon, 2, ANIM_TARGET, 5, 0, 8, 1
	createvisualtask AnimTask_BlendMonInAndOut, 3, ANIM_TARGET, RGB_RED, 12, 1, 1
	playsewithpan SE_M_FLAME_WHEEL2, SOUND_PAN_TARGET
	call FireSpreadEffect
	delay 7
	createsprite gSlideMonToOriginalPosSpriteTemplate, ANIM_ATTACKER, 2, 0, 0, 9
	waitforvisualfinish
	clearmonbg ANIM_DEF_PARTNER
	end

FlameWheel1: @ Unused
	createsprite gFireSpiralOutwardSpriteTemplate, ANIM_ATTACKER, 3, 0, 0, 50
	delay 4
	return

Move_PIN_MISSILE:
	loadspritegfx ANIM_TAG_NEEDLE
	loadspritegfx ANIM_TAG_IMPACT
	monbg ANIM_TARGET
	splitbgprio ANIM_TARGET
	setalpha 12, 8
	playsewithpan SE_M_JUMP_KICK, SOUND_PAN_ATTACKER
	createsprite gPinMissileSpriteTemplate, ANIM_ATTACKER, 2, 20, -8, -8, -8, 20, -32
	delay 15
	createsprite gPinMissileSpriteTemplate, ANIM_ATTACKER, 2, 20, -8, 8, 8, 20, -40
	delay 4
	playsewithpan SE_M_HORN_ATTACK, SOUND_PAN_TARGET
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 3, -8, -8, ANIM_TARGET, 2
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_TARGET, 3, 0, 2, 1
	delay 9
	createsprite gPinMissileSpriteTemplate, ANIM_ATTACKER, 2, 20, -8, 0, 0, 20, -32
	delay 4
	playsewithpan SE_M_HORN_ATTACK, SOUND_PAN_TARGET
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 3, 8, 8, ANIM_TARGET, 2
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_TARGET, 3, 0, 2, 1
	delay 14
	playsewithpan SE_M_HORN_ATTACK, SOUND_PAN_TARGET
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 3, 0, 0, ANIM_TARGET, 2
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_TARGET, 3, 0, 2, 1
	waitforvisualfinish
	clearmonbg ANIM_TARGET
	blendoff
	end

Move_ICICLE_SPEAR:
	loadspritegfx ANIM_TAG_ICICLE_SPEAR
	loadspritegfx ANIM_TAG_IMPACT
	monbg ANIM_TARGET
	splitbgprio ANIM_TARGET
	setalpha 12, 8
	playsewithpan SE_M_ICY_WIND, SOUND_PAN_ATTACKER
	createsprite gIcicleSpearSpriteTemplate, ANIM_ATTACKER, 2, 20, -8, -8, -8, 20, -32
	delay 15
	createsprite gIcicleSpearSpriteTemplate, ANIM_ATTACKER, 2, 20, -8, 8, 8, 20, -40
	delay 4
	playsewithpan SE_M_HORN_ATTACK, SOUND_PAN_TARGET
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 3, -8, -8, ANIM_TARGET, 2
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_TARGET, 3, 0, 2, 1
	delay 9
	createsprite gIcicleSpearSpriteTemplate, ANIM_ATTACKER, 2, 20, -8, 0, 0, 20, -32
	delay 4
	playsewithpan SE_M_HORN_ATTACK, SOUND_PAN_TARGET
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 3, 8, 8, ANIM_TARGET, 2
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_TARGET, 3, 0, 2, 1
	delay 14
	playsewithpan SE_M_HORN_ATTACK, SOUND_PAN_TARGET
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 3, 0, 0, ANIM_TARGET, 2
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_TARGET, 3, 0, 2, 1
	waitforvisualfinish
	clearmonbg ANIM_TARGET
	blendoff
	end

Move_TAKE_DOWN:
	loadspritegfx ANIM_TAG_IMPACT
	monbg ANIM_DEF_PARTNER
	setalpha 12, 8
	playsewithpan SE_M_TAKE_DOWN, SOUND_PAN_ATTACKER
	createvisualtask AnimTask_WindUpLunge, 5, ANIM_ATTACKER, -24, 8, 23, 10, 40, 10
	delay 35
	createsprite gComplexPaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG | F_PAL_BATTLERS, 3, 1, RGB_BLACK, 10, RGB_BLACK, 0
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 4, -10, 0, ANIM_TARGET, 0
	playsewithpan SE_M_MEGA_KICK2, SOUND_PAN_TARGET
	delay 1
	createsprite gSlideMonToOffsetSpriteTemplate, ANIM_ATTACKER, 2, 1, -16, 0, 0, 4
	waitforvisualfinish
	createvisualtask AnimTask_ShakeMonInPlace, 2, ANIM_TARGET, 4, 0, 12, 1
	waitforvisualfinish
	delay 2
	createsprite gSlideMonToOriginalPosSpriteTemplate, ANIM_ATTACKER, 2, 0, 0, 5
	delay 3
	createsprite gSlideMonToOriginalPosSpriteTemplate, ANIM_ATTACKER, 2, 1, 0, 7
	waitforvisualfinish
	clearmonbg ANIM_DEF_PARTNER
	blendoff
	end

Move_DOUBLE_EDGE:
	loadspritegfx ANIM_TAG_IMPACT
	playsewithpan SE_M_SWIFT, SOUND_PAN_ATTACKER
	createsprite gComplexPaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_ATTACKER, 4, 2, RGB_WHITE, 10, RGB_BLACK, 0
	waitforvisualfinish
	delay 10
	playsewithpan SE_M_SWAGGER, SOUND_PAN_ATTACKER
	waitplaysewithpan SE_M_SWAGGER, SOUND_PAN_ATTACKER, 8
	createvisualtask AnimTask_TranslateMonEllipticalRespectSide, 2, ANIM_ATTACKER, 18, 6, 2, 4
	waitforvisualfinish
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG, 0, 16, 16, RGB_WHITE
	createsprite gSlideMonToOffsetSpriteTemplate, ANIM_ATTACKER, 2, 0, 20, 0, 0, 4
	delay 3
	waitforvisualfinish
	playsewithpan SE_M_MEGA_KICK2, SOUND_PAN_TARGET
	createsprite gBasicHitSplatSpriteTemplate, ANIM_TARGET, 4, -10, 0, ANIM_TARGET, 0
	createsprite gSlideMonToOffsetSpriteTemplate, ANIM_ATTACKER, 2, 1, -32, 0, 0, 3
	waitforvisualfinish
	createvisualtask AnimTask_RotateMonSpriteToSide, 2, 8, -256, ANIM_ATTACKER, 0
	createvisualtask AnimTask_RotateMonSpriteToSide, 2, 8, -256, ANIM_TARGET, 0
	createvisualtask AnimTask_ShakeMonInPlace, 2, ANIM_ATTACKER, 4, 0, 12, 1
	createvisualtask AnimTask_ShakeMonInPlace, 2, ANIM_TARGET, 4, 0, 12, 1
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG, 2, 16, 0, RGB_WHITE
	waitforvisualfinish
	createvisualtask AnimTask_RotateMonSpriteToSide, 2, 8, -256, ANIM_ATTACKER, 1
	createvisualtask AnimTask_RotateMonSpriteToSide, 2, 8, -256, ANIM_TARGET, 1
	waitforvisualfinish
	createsprite gSlideMonToOriginalPosSpriteTemplate, ANIM_ATTACKER, 2, 0, 0, 5
	delay 3
	createsprite gSlideMonToOriginalPosSpriteTemplate, ANIM_ATTACKER, 2, 1, 0, 7
	waitforvisualfinish
	end

Move_POISON_STING:
	loadspritegfx ANIM_TAG_NEEDLE
	loadspritegfx ANIM_TAG_IMPACT
	loadspritegfx ANIM_TAG_POISON_BUBBLE
	monbg ANIM_TARGET
	splitbgprio ANIM_TARGET
	setalpha 12, 8
	playsewithpan SE_M_RAZOR_WIND2, SOUND_PAN_ATTACKER
	createsprite gLinearStingerSpriteTemplate, ANIM_TARGET, 2, 20, 0, -8, 0, 20
	waitforvisualfinish
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 3, 0, 0, ANIM_TARGET, 2
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_TARGET, 2, 0, 5, 1
	playsewithpan SE_M_HORN_ATTACK, SOUND_PAN_TARGET
	waitforvisualfinish
	call PoisonBubblesEffect
	waitforvisualfinish
	clearmonbg ANIM_TARGET
	blendoff
	end

Move_TWINEEDLE:
	loadspritegfx ANIM_TAG_NEEDLE
	loadspritegfx ANIM_TAG_IMPACT
	monbg ANIM_TARGET
	splitbgprio ANIM_TARGET
	setalpha 12, 8
	loopsewithpan SE_M_RAZOR_WIND2, SOUND_PAN_ATTACKER, 6, 2
	createsprite gLinearStingerSpriteTemplate, ANIM_TARGET, 2, 10, -4, 0, -4, 20
	createsprite gLinearStingerSpriteTemplate, ANIM_TARGET, 2, 20, 12, 10, 12, 20
	delay 20
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_TARGET, 2, 0, 5, 1
	createsprite gHandleInvertHitSplatSpriteTemplate, ANIM_ATTACKER, 3, 0, -4, 1, 3
	loopsewithpan SE_M_HORN_ATTACK, SOUND_PAN_TARGET, 5, 2
	delay 1
	createsprite gHandleInvertHitSplatSpriteTemplate, ANIM_ATTACKER, 3, 10, 12, 1, 3
	waitforvisualfinish
	clearmonbg ANIM_TARGET
	blendoff
	end

Move_FIRE_BLAST:
	loadspritegfx ANIM_TAG_SMALL_EMBER
	createsoundtask SoundTask_FireBlast, SE_M_FLAME_WHEEL, SE_M_FLAME_WHEEL2
	call FireBlastRing
	call FireBlastRing
	call FireBlastRing
	delay 24
	createvisualtask AnimTask_BlendBattleAnimPal, 10, F_PAL_BG, 3, 0, 8, RGB_BLACK
	waitforvisualfinish
	delay 19
	createvisualtask AnimTask_ShakeMon, 2, ANIM_TARGET, 5, 0, 20, 1
	call FireBlastCross
	delay 3
	call FireBlastCross
	delay 3
	call FireBlastCross
	delay 3
	call FireBlastCross
	delay 3
	call FireBlastCross
	delay 3
	call FireBlastCross
	delay 3
	call FireBlastCross
	delay 3
	call FireBlastCross
	delay 3
	call FireBlastCross
	waitforvisualfinish
	createvisualtask AnimTask_BlendBattleAnimPal, 10, F_PAL_BG, 2, 8, 0, RGB_BLACK
	waitforvisualfinish
	end

FireBlastRing:
	createsprite gFireBlastRingSpriteTemplate, ANIM_TARGET, 2, 0, 0, 0
	createsprite gFireBlastRingSpriteTemplate, ANIM_TARGET, 2, 0, 0, 51
	createsprite gFireBlastRingSpriteTemplate, ANIM_TARGET, 2, 0, 0, 102
	createsprite gFireBlastRingSpriteTemplate, ANIM_TARGET, 2, 0, 0, 153
	createsprite gFireBlastRingSpriteTemplate, ANIM_TARGET, 2, 0, 0, 204
	delay 5
	return

FireBlastCross:
	createsprite gFireBlastCrossSpriteTemplate, ANIM_TARGET, 2, 0, 0, 10, 0, -2
	createsprite gFireBlastCrossSpriteTemplate, ANIM_TARGET, 2, 0, 0, 13, -2, 0
	createsprite gFireBlastCrossSpriteTemplate, ANIM_TARGET, 2, 0, 0, 13, 2, 0
	createsprite gFireBlastCrossSpriteTemplate, ANIM_TARGET, 2, 0, 0, 15, -2, 2
	createsprite gFireBlastCrossSpriteTemplate, ANIM_TARGET, 2, 0, 0, 15, 2, 2
	return

Move_LEECH_SEED:
	loadspritegfx ANIM_TAG_SEED
	playsewithpan SE_M_POISON_POWDER, SOUND_PAN_ATTACKER
	createsprite gLeechSeedSpriteTemplate, ANIM_TARGET, 2, 15, 0, 0, 24, 35, -32
	delay 8
	playsewithpan SE_M_POISON_POWDER, SOUND_PAN_ATTACKER
	createsprite gLeechSeedSpriteTemplate, ANIM_TARGET, 2, 15, 0, -16, 24, 35, -40
	delay 8
	playsewithpan SE_M_POISON_POWDER, SOUND_PAN_ATTACKER
	createsprite gLeechSeedSpriteTemplate, ANIM_TARGET, 2, 15, 0, 16, 24, 35, -37
	delay 12
	loopsewithpan SE_M_TAIL_WHIP, SOUND_PAN_TARGET, 10, 8
	waitforvisualfinish
	end

Move_EMBER:
	loadspritegfx ANIM_TAG_SMALL_EMBER
	loopsewithpan SE_M_EMBER, SOUND_PAN_ATTACKER, 5, 2
	createsprite gEmberSpriteTemplate, ANIM_TARGET, 2, 20, 0, -16, 24, 20, 1
	delay 4
	createsprite gEmberSpriteTemplate, ANIM_TARGET, 2, 20, 0, 0, 24, 20, 1
	delay 4
	createsprite gEmberSpriteTemplate, ANIM_TARGET, 2, 20, 0, 16, 24, 20, 1
	delay 16
	playsewithpan SE_M_FLAME_WHEEL, SOUND_PAN_TARGET
	call EmberFireHit
	call EmberFireHit
	call EmberFireHit
	end

EmberFireHit:
	createsprite gEmberFlareSpriteTemplate, ANIM_TARGET, 2, -24, 24, 24, 24, 20, ANIM_TARGET, 1
	delay 4
	return

Move_MEGA_PUNCH:
	loadspritegfx ANIM_TAG_IMPACT
	loadspritegfx ANIM_TAG_HANDS_AND_FEET
	monbg ANIM_TARGET
	delay 2
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG, 0, 0, 16, RGB_BLACK
	setalpha 12, 8
	playsewithpan SE_M_MEGA_KICK, SOUND_PAN_TARGET
	createsprite gMegaPunchKickSpriteTemplate, ANIM_ATTACKER, 3, 0, 0, 0, 50
	createvisualtask AnimTask_BlendBattleAnimPal, 10, F_PAL_TARGET, 2, 0, 7, RGB_WHITE
	delay 50
	call SetImpactBackground
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 2, 0, 0, ANIM_TARGET, 0
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_TARGET, 4, 0, 22, 1
	createvisualtask AnimTask_BlendBattleAnimPal, 10, F_PAL_TARGET, 2, 0, 0, RGB_WHITE
	createsprite gComplexPaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG | F_PAL_BATTLERS, 3, 1, RGB_BLACK, 8, RGB_BLACK, 0
	playsewithpan SE_M_VITAL_THROW2, SOUND_PAN_TARGET
	waitforvisualfinish
	clearmonbg ANIM_TARGET
	blendoff
	delay 2
	restorebg
	waitbgfadein
	end

SetImpactBackground:
	delay 2
	createvisualtask AnimTask_IsContest, 2
	jumprettrue SetImpactContestsBG
	createvisualtask AnimTask_IsTargetPlayerSide, 2
	jumpretfalse SetImpactOpponentBG
	jumprettrue SetImpactPlayerBG
SetImpactBackgroundRet:
	return

SetImpactOpponentBG:
	changebg BG_IMPACT_OPPONENT
	goto SetImpactBackgroundRet

SetImpactPlayerBG:
	changebg BG_IMPACT_PLAYER
	goto SetImpactBackgroundRet

SetImpactContestsBG:
	changebg BG_IMPACT_CONTESTS
	goto SetImpactBackgroundRet

Move_MEGA_KICK:
	loadspritegfx ANIM_TAG_IMPACT
	loadspritegfx ANIM_TAG_HANDS_AND_FEET
	monbg ANIM_TARGET
	delay 2
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG, 0, 0, 16, RGB_BLACK
	setalpha 12, 8
	playsewithpan SE_M_MEGA_KICK, SOUND_PAN_TARGET
	createsprite gMegaPunchKickSpriteTemplate, ANIM_ATTACKER, 3, 0, 0, 1, 50
	createvisualtask AnimTask_BlendBattleAnimPal, 10, F_PAL_TARGET, 2, 0, 7, RGB_WHITE
	delay 50
	playsewithpan SE_M_MEGA_KICK2, SOUND_PAN_TARGET
	call SetImpactBackground
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 2, 0, 0, ANIM_TARGET, 0
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_TARGET, 4, 0, 22, 1
	createvisualtask AnimTask_BlendBattleAnimPal, 10, F_PAL_TARGET, 2, 0, 0, RGB_WHITE
	createsprite gComplexPaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG | F_PAL_BATTLERS, 3, 1, RGB_BLACK, 8, RGB_BLACK, 0
	waitforvisualfinish
	clearmonbg ANIM_TARGET
	blendoff
	delay 2
	restorebg
	waitbgfadein
	end

Move_COMET_PUNCH:
	loadspritegfx ANIM_TAG_IMPACT
	loadspritegfx ANIM_TAG_HANDS_AND_FEET
	monbg ANIM_TARGET
	setalpha 12, 8
	choosetwoturnanim CometPunchLeft, CometPunchRight

CometPunchContinue:
	createvisualtask AnimTask_ShakeMon, 2, ANIM_TARGET, 3, 0, 6, 1
	playsewithpan SE_M_COMET_PUNCH, SOUND_PAN_TARGET
	waitforvisualfinish
	clearmonbg ANIM_TARGET
	blendoff
	end

CometPunchLeft:
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 2, -8, -8, ANIM_TARGET, 2
	createsprite gFistFootSpriteTemplate, ANIM_ATTACKER, 3, -8, 0, 8, 1, 0
	goto CometPunchContinue

CometPunchRight:
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 2, 8, -8, ANIM_TARGET, 2
	createsprite gFistFootSpriteTemplate, ANIM_ATTACKER, 3, 8, 0, 8, 1, 0
	goto CometPunchContinue

Move_SONIC_BOOM:
	loadspritegfx ANIM_TAG_AIR_WAVE
	loadspritegfx ANIM_TAG_IMPACT
	monbg ANIM_DEF_PARTNER
	splitbgprio ANIM_TARGET
	setalpha 12, 8
	call SonicBoomProjectile
	call SonicBoomProjectile
	call SonicBoomProjectile
	createvisualtask AnimTask_ShakeMon, 2, ANIM_TARGET, 3, 0, 10, 1
	call SonicBoomHit
	waitforvisualfinish
	clearmonbg ANIM_DEF_PARTNER
	blendoff
	end

SonicBoomProjectile:
	playsewithpan SE_M_RAZOR_WIND2, SOUND_PAN_ATTACKER
	createsprite gSonicBoomSpriteTemplate, ANIM_TARGET, 2, 16, 0, 0, 0, 15
	delay 4
	return

SonicBoomHit:
	createsprite gBasicHitSplatSpriteTemplate, ANIM_TARGET, 3, 0, 0, ANIM_TARGET, 2
	delay 4
	return

Move_THUNDER_SHOCK:
	loadspritegfx ANIM_TAG_SPARK
	loadspritegfx ANIM_TAG_SPARK_2
	createvisualtask AnimTask_BlendBattleAnimPal, 10, F_PAL_BG, 0, 0, 6, RGB_BLACK
	waitforvisualfinish
	delay 10
	createvisualtask AnimTask_ElectricBolt, 5, 0, -44, 0
	playsewithpan SE_M_THUNDERBOLT, SOUND_PAN_TARGET
	delay 9
	createvisualtask AnimTask_BlendBattleAnimPal, 10, F_PAL_TARGET, 0, 0, 13, RGB_BLACK
	waitforvisualfinish
	createvisualtask AnimTask_BlendBattleAnimPal, 10, F_PAL_TARGET, 0, 13, 0, RGB_BLACK
	waitforvisualfinish
	delay 20
	call ElectricityEffect
	waitforvisualfinish
	delay 20
	createvisualtask AnimTask_BlendBattleAnimPal, 10, F_PAL_BG, 0, 6, 0, RGB_BLACK
	waitforvisualfinish
	end

Move_THUNDERBOLT:
	loadspritegfx ANIM_TAG_SPARK
	loadspritegfx ANIM_TAG_SHOCK_3
	loadspritegfx ANIM_TAG_SPARK_2
	createvisualtask AnimTask_BlendBattleAnimPal, 10, F_PAL_BG, 0, 0, 6, RGB_BLACK
	waitforvisualfinish
	delay 10
	createvisualtask AnimTask_ElectricBolt, 5, 24, -52, 0
	playsewithpan SE_M_THUNDERBOLT, SOUND_PAN_TARGET
	delay 7
	createvisualtask AnimTask_ElectricBolt, 5, -24, -52, 0
	playsewithpan SE_M_THUNDERBOLT, SOUND_PAN_TARGET
	delay 7
	createvisualtask AnimTask_ElectricBolt, 5, 0, -60, 1
	playsewithpan SE_M_THUNDERBOLT, SOUND_PAN_TARGET
	delay 9
	createvisualtask AnimTask_BlendBattleAnimPal, 10, F_PAL_TARGET, 0, 0, 13, RGB_BLACK
	waitforvisualfinish
	createvisualtask AnimTask_BlendBattleAnimPal, 10, F_PAL_TARGET, 0, 13, 0, RGB_BLACK
	waitforvisualfinish
	delay 20
	createsprite gThunderboltOrbSpriteTemplate, ANIM_TARGET, 3, 44, 0, 0, 3
	createsprite gSparkElectricityFlashingSpriteTemplate, ANIM_TARGET, 4, 0, 0, 32, 44, 0, 40, 0, -32765
	createsprite gSparkElectricityFlashingSpriteTemplate, ANIM_TARGET, 4, 0, 0, 32, 44, 64, 40, 1, -32765
	createsprite gSparkElectricityFlashingSpriteTemplate, ANIM_TARGET, 4, 0, 0, 32, 44, 128, 40, 0, -32765
	createsprite gSparkElectricityFlashingSpriteTemplate, ANIM_TARGET, 4, 0, 0, 32, 44, 192, 40, 2, -32765
	createsprite gSparkElectricityFlashingSpriteTemplate, ANIM_TARGET, 4, 0, 0, 16, 44, 32, 40, 0, -32765
	createsprite gSparkElectricityFlashingSpriteTemplate, ANIM_TARGET, 4, 0, 0, 16, 44, 96, 40, 1, -32765
	createsprite gSparkElectricityFlashingSpriteTemplate, ANIM_TARGET, 4, 0, 0, 16, 44, 160, 40, 0, -32765
	createsprite gSparkElectricityFlashingSpriteTemplate, ANIM_TARGET, 4, 0, 0, 16, 44, 224, 40, 2, -32765
	playsewithpan SE_M_HYPER_BEAM, SOUND_PAN_TARGET
	delay 0
	createvisualtask AnimTask_BlendBattleAnimPal, 10, F_PAL_BG, 0, 2, 2, RGB_BLACK
	delay 6
	createvisualtask AnimTask_BlendBattleAnimPal, 10, F_PAL_BG, 0, 6, 6, RGB_BLACK
	delay 6
	createvisualtask AnimTask_BlendBattleAnimPal, 10, F_PAL_BG, 0, 2, 2, RGB_BLACK
	delay 6
	createvisualtask AnimTask_BlendBattleAnimPal, 10, F_PAL_BG, 0, 6, 6, RGB_BLACK
	waitforvisualfinish
	delay 20
	waitplaysewithpan SE_M_THUNDERBOLT2, SOUND_PAN_TARGET, 19
	call ElectricityEffect
	waitforvisualfinish
	delay 20
	createvisualtask AnimTask_BlendBattleAnimPal, 10, F_PAL_BG, 0, 6, 0, RGB_BLACK
	waitforvisualfinish
	end

Move_THUNDER_WAVE:
	loadspritegfx ANIM_TAG_SPARK
	loadspritegfx ANIM_TAG_SPARK_2
	loadspritegfx ANIM_TAG_SPARK_H
	createvisualtask AnimTask_BlendBattleAnimPal, 10, F_PAL_BG, 0, 0, 6, RGB_BLACK
	waitforvisualfinish
	delay 10
	createvisualtask AnimTask_ElectricBolt, 5, 0, -48, 0
	playsewithpan SE_M_THUNDER_WAVE, SOUND_PAN_TARGET
	delay 20
	loopsewithpan SE_M_THUNDERBOLT2, SOUND_PAN_TARGET, 10, 4
	createsprite gThunderWaveSpriteTemplate, ANIM_TARGET, 2, -16, -16
	delay 4
	createsprite gThunderWaveSpriteTemplate, ANIM_TARGET, 2, -16, 0
	delay 4
	createsprite gThunderWaveSpriteTemplate, ANIM_TARGET, 2, -16, 16
	waitforvisualfinish
	createvisualtask AnimTask_BlendBattleAnimPal, 10, F_PAL_BG, 0, 6, 0, RGB_BLACK
	waitforvisualfinish
	end

Move_BEAT_UP:
	loadspritegfx ANIM_TAG_IMPACT
	loadspritegfx ANIM_TAG_HANDS_AND_FEET
	monbg ANIM_TARGET
	setalpha 12, 8
	choosetwoturnanim BeatUpLeft, BeatUpRight

BeatUpContinue:
	waitforvisualfinish
	clearmonbg ANIM_TARGET
	blendoff
	end

BeatUpLeft:
	createsprite gBasicHitSplatSpriteTemplate, ANIM_TARGET, 2, -20, -20, ANIM_TARGET, 2
	createsprite gFistFootSpriteTemplate, ANIM_TARGET, 3, -20, -12, 8, 1, 0
	createvisualtask AnimTask_ShakeMon, 2, ANIM_TARGET, 3, 0, 6, 1
	playsewithpan SE_M_VITAL_THROW2, SOUND_PAN_TARGET
	delay 8
	createsprite gBasicHitSplatSpriteTemplate, ANIM_TARGET, 2, 8, 0, ANIM_TARGET, 2
	createsprite gFistFootSpriteTemplate, ANIM_TARGET, 3, 8, 8, 8, 1, 0
	createvisualtask AnimTask_ShakeMon, 2, ANIM_TARGET, 3, 0, 6, 1
	playsewithpan SE_M_VITAL_THROW2, SOUND_PAN_TARGET
	goto BeatUpContinue

BeatUpRight:
	createsprite gBasicHitSplatSpriteTemplate, ANIM_TARGET, 2, 12, -20, ANIM_TARGET, 2
	createsprite gFistFootSpriteTemplate, ANIM_TARGET, 3, 12, -12, 8, 1, 0
	createvisualtask AnimTask_ShakeMon, 2, ANIM_TARGET, 3, 0, 6, 1
	playsewithpan SE_M_VITAL_THROW2, SOUND_PAN_TARGET
	delay 8
	createsprite gBasicHitSplatSpriteTemplate, ANIM_TARGET, 2, -12, 0, ANIM_TARGET, 2
	createsprite gFistFootSpriteTemplate, ANIM_TARGET, 3, -12, 8, 8, 1, 0
	createvisualtask AnimTask_ShakeMon, 2, ANIM_TARGET, 3, 0, 6, 1
	playsewithpan SE_M_VITAL_THROW2, SOUND_PAN_TARGET
	goto BeatUpContinue

Move_STOMP:
	loadspritegfx ANIM_TAG_HANDS_AND_FEET
	loadspritegfx ANIM_TAG_IMPACT
	monbg ANIM_TARGET
	setalpha 12, 8
	playsewithpan SE_M_DOUBLE_TEAM, SOUND_PAN_TARGET
	createsprite gStompFootSpriteTemplate, ANIM_ATTACKER, 3, 0, -32, 15
	delay 19
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 2, 0, -8, ANIM_TARGET, 1
	createvisualtask AnimTask_ShakeMon, 2, ANIM_TARGET, 0, 4, 9, 1
	playsewithpan SE_M_MEGA_KICK2, SOUND_PAN_TARGET
	waitforvisualfinish
	clearmonbg ANIM_TARGET
	blendoff
	end

Move_TAIL_WHIP:
	loopsewithpan SE_M_TAIL_WHIP, SOUND_PAN_ATTACKER, 24, 3
	createvisualtask AnimTask_TranslateMonEllipticalRespectSide, 2, ANIM_ATTACKER, 12, 4, 2, 3
	waitforvisualfinish
	end

Move_CUT:
	loadspritegfx ANIM_TAG_CUT
	monbg ANIM_TARGET
	setalpha 12, 8
	playsewithpan SE_M_CUT, SOUND_PAN_TARGET
	createsprite gCuttingSliceSpriteTemplate, ANIM_ATTACKER, 2, 40, -32, 0
	delay 5
	createvisualtask AnimTask_ShakeMon, 2, ANIM_TARGET, 0, 3, 10, 1
	waitforvisualfinish
	clearmonbg ANIM_TARGET
	blendoff
	waitforvisualfinish
	end

Move_HIDDEN_POWER:
	loadspritegfx ANIM_TAG_RED_ORB
	playsewithpan SE_M_TAKE_DOWN, SOUND_PAN_ATTACKER
	createvisualtask AnimTask_ScaleMonAndRestore, 5, -7, -7, 11, ANIM_ATTACKER, 0
	waitforvisualfinish
	delay 30
	createvisualtask AnimTask_BlendMonInAndOut, 5, ANIM_ATTACKER, RGB(31, 31, 19), 12, 5, 1
	delay 4
	createvisualtask AnimTask_ScaleMonAndRestore, 5, -7, -7, 11, ANIM_ATTACKER, 0
	playsewithpan SE_M_REVERSAL, SOUND_PAN_ATTACKER
	createsprite gHiddenPowerOrbSpriteTemplate, ANIM_ATTACKER, 2, 26, 0
	createsprite gHiddenPowerOrbSpriteTemplate, ANIM_ATTACKER, 2, 26, 42
	createsprite gHiddenPowerOrbSpriteTemplate, ANIM_ATTACKER, 2, 26, 84
	createsprite gHiddenPowerOrbSpriteTemplate, ANIM_ATTACKER, 2, 26, 126
	createsprite gHiddenPowerOrbSpriteTemplate, ANIM_ATTACKER, 2, 26, 168
	createsprite gHiddenPowerOrbSpriteTemplate, ANIM_ATTACKER, 2, 26, 210
	delay 52
	setarg 7, 0xFFFF
	playsewithpan SE_M_REFLECT, SOUND_PAN_ATTACKER
	createvisualtask AnimTask_ScaleMonAndRestore, 5, -7, -7, 11, ANIM_ATTACKER, 0
	createsprite gHiddenPowerOrbScatterSpriteTemplate, ANIM_TARGET, 2, 0
	createsprite gHiddenPowerOrbScatterSpriteTemplate, ANIM_TARGET, 2, 32
	createsprite gHiddenPowerOrbScatterSpriteTemplate, ANIM_TARGET, 2, 64
	createsprite gHiddenPowerOrbScatterSpriteTemplate, ANIM_TARGET, 2, 96
	createsprite gHiddenPowerOrbScatterSpriteTemplate, ANIM_TARGET, 2, 128
	createsprite gHiddenPowerOrbScatterSpriteTemplate, ANIM_TARGET, 2, 160
	createsprite gHiddenPowerOrbScatterSpriteTemplate, ANIM_TARGET, 2, 192
	createsprite gHiddenPowerOrbScatterSpriteTemplate, ANIM_TARGET, 2, 224
	end

Move_REVERSAL:
	loadspritegfx ANIM_TAG_BLUE_ORB
	loadspritegfx ANIM_TAG_HANDS_AND_FEET
	loadspritegfx ANIM_TAG_IMPACT
	playsewithpan SE_M_DETECT, SOUND_PAN_ATTACKER
	createsprite gComplexPaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG | F_PAL_BATTLERS, 3, 3, RGB_WHITE, 8, RGB_BLACK, 0
	waitforvisualfinish
	delay 30
	createvisualtask AnimTask_BlendColorCycle, 2, F_PAL_BG | F_PAL_BATTLERS, 3, 2, 0, 10, RGB_WHITE
	delay 10
	playsewithpan SE_M_REVERSAL, SOUND_PAN_ATTACKER
	createsprite gReversalOrbSpriteTemplate, ANIM_ATTACKER, 2, 26, 0
	createsprite gReversalOrbSpriteTemplate, ANIM_ATTACKER, 2, 26, 42
	createsprite gReversalOrbSpriteTemplate, ANIM_ATTACKER, 2, 26, 84
	createsprite gReversalOrbSpriteTemplate, ANIM_ATTACKER, 2, 26, 126
	createsprite gReversalOrbSpriteTemplate, ANIM_ATTACKER, 2, 26, 168
	createsprite gReversalOrbSpriteTemplate, ANIM_ATTACKER, 2, 26, 210
	waitforvisualfinish
	delay 20
	createsprite gHorizontalLungeSpriteTemplate, ANIM_ATTACKER, 2, 6, 4
	delay 8
	playsewithpan SE_M_VITAL_THROW2, SOUND_PAN_TARGET
	createsprite gComplexPaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG | F_PAL_BATTLERS, 3, 1, RGB_WHITE, 8, RGB_BLACK, 0
	createsprite gFistFootSpriteTemplate, ANIM_TARGET, 4, 0, 0, 10, 1, 0
	createsprite gBasicHitSplatSpriteTemplate, ANIM_TARGET, 3, 0, 0, ANIM_TARGET, 1
	createvisualtask AnimTask_ShakeTargetBasedOnMovePowerOrDmg, 5, FALSE, 1, 8, 1, 0
	end

Move_PURSUIT:
	loadspritegfx ANIM_TAG_IMPACT
	monbg ANIM_TARGET
	fadetobg BG_DARK
	waitbgfadein
	delay 0
	setalpha 12, 8
	choosetwoturnanim PursuitNormal, PursuitOnSwitchout

PursuitContinue:
	waitforvisualfinish
	clearmonbg ANIM_TARGET
	blendoff
	delay 0
	restorebg
	waitbgfadein
	end

PursuitNormal:
	playsewithpan SE_M_COMET_PUNCH, SOUND_PAN_TARGET
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 3, 0, 0, ANIM_TARGET, 2
	createvisualtask AnimTask_ShakeTargetBasedOnMovePowerOrDmg, 5, FALSE, 1, 6, 1, 0
	goto PursuitContinue

PursuitOnSwitchout:
	playsewithpan SE_M_COMET_PUNCH, SOUND_PAN_TARGET
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 3, 0, 0, ANIM_TARGET, 1
	createvisualtask AnimTask_ShakeTargetBasedOnMovePowerOrDmg, 5, FALSE, 1, 6, 1, 0
	goto PursuitContinue

Move_SPIKE_CANNON:
	loadspritegfx ANIM_TAG_NEEDLE
	loadspritegfx ANIM_TAG_IMPACT
	monbg ANIM_TARGET
	splitbgprio ANIM_TARGET
	setalpha 12, 8
	createvisualtask AnimTask_WindUpLunge, 5, ANIM_ATTACKER, -4, 0, 4, 6, 8, 4
	waitforvisualfinish
	loopsewithpan SE_M_RAZOR_WIND2, SOUND_PAN_ATTACKER, 5, 3
	createsprite gSlideMonToOriginalPosSpriteTemplate, ANIM_ATTACKER, 2, 0, 0, 5
	createsprite gLinearStingerSpriteTemplate, ANIM_ATTACKER, 2, 10, -8, -8, -8, 20
	createsprite gLinearStingerSpriteTemplate, ANIM_ATTACKER, 2, 18, 0, 0, 0, 20
	createsprite gLinearStingerSpriteTemplate, ANIM_ATTACKER, 2, 26, 8, 8, 8, 20
	waitforvisualfinish
	createsprite gHandleInvertHitSplatSpriteTemplate, ANIM_ATTACKER, 3, -8, -8, 1, 2
	createsprite gHandleInvertHitSplatSpriteTemplate, ANIM_ATTACKER, 3, 0, 0, 1, 2
	createsprite gHandleInvertHitSplatSpriteTemplate, ANIM_ATTACKER, 3, 8, 8, 1, 2
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_TARGET, 3, 0, 7, 1
	loopsewithpan SE_M_HORN_ATTACK, SOUND_PAN_TARGET, 5, 3
	waitforvisualfinish
	clearmonbg ANIM_TARGET
	blendoff
	end

Move_SWORDS_DANCE:
	loadspritegfx ANIM_TAG_SWORD
	monbg ANIM_ATTACKER
	setalpha 12, 8
	playsewithpan SE_M_SWORDS_DANCE, SOUND_PAN_ATTACKER
	createvisualtask AnimTask_TranslateMonEllipticalRespectSide, 2, ANIM_ATTACKER, 16, 6, 1, 4
	createsprite gSwordsDanceBladeSpriteTemplate, ANIM_ATTACKER, 2, 0, 0
	delay 22
	createvisualtask AnimTask_FlashAnimTagWithColor, 2, ANIM_TAG_SWORD, 2, 2, RGB(18, 31, 31), 16, 0, 0
	waitforvisualfinish
	clearmonbg ANIM_ATTACKER
	blendoff
	delay 1
	end

Move_PSYCH_UP:
	loadspritegfx ANIM_TAG_SPIRAL
	monbg ANIM_ATK_PARTNER
	createvisualtask AnimTask_BlendColorCycleExclude, 2, 1, 2, 6, 1, 11, RGB_BLACK
	setalpha 12, 8
	loopsewithpan SE_M_PSYBEAM2, SOUND_PAN_ATTACKER, 5, 10
	createsprite gPsychUpSpiralSpriteTemplate, ANIM_ATTACKER, 2, 0, 0, 0, 0
	createvisualtask AnimTask_SwayMon, 5, 0, 5, 2560, 8, ANIM_ATTACKER
	delay 127
	delay 4
	playsewithpan SE_M_PSYBEAM, SOUND_PAN_ATTACKER
	createvisualtask AnimTask_ScaleMonAndRestore, 5, -5, -5, 10, ANIM_ATTACKER, 1
	createvisualtask AnimTask_BlendBattleAnimPal, 9, F_PAL_ATTACKER, 2, 10, 0, RGB_YELLOW
	delay 30
	clearmonbg ANIM_ATK_PARTNER
	blendoff
	waitforvisualfinish
	end

Move_DIZZY_PUNCH:
	loadspritegfx ANIM_TAG_DUCK
	loadspritegfx ANIM_TAG_HANDS_AND_FEET
	loadspritegfx ANIM_TAG_IMPACT
	monbg ANIM_TARGET
	setalpha 12, 8
	call DizzyPunchLunge
	createsprite gFistFootSpriteTemplate, ANIM_TARGET, 5, 16, 8, 20, 1, 0
	createsprite gBasicHitSplatSpriteTemplate, ANIM_TARGET, 4, 16, 0, ANIM_TARGET, 1
	playsewithpan SE_M_COMET_PUNCH, SOUND_PAN_TARGET
	createsprite gDizzyPunchDuckSpriteTemplate, ANIM_TARGET, 3, 16, 8, 160, -32
	createsprite gDizzyPunchDuckSpriteTemplate, ANIM_TARGET, 3, 16, 8, -256, -40
	createsprite gDizzyPunchDuckSpriteTemplate, ANIM_TARGET, 3, 16, 8, 128, -16
	createsprite gDizzyPunchDuckSpriteTemplate, ANIM_TARGET, 3, 16, 8, 416, -38
	createsprite gDizzyPunchDuckSpriteTemplate, ANIM_TARGET, 3, 16, 8, -128, -22
	createsprite gDizzyPunchDuckSpriteTemplate, ANIM_TARGET, 3, 16, 8, -384, -31
	delay 10
	call DizzyPunchLunge
	createsprite gFistFootSpriteTemplate, ANIM_TARGET, 5, -16, -8, 20, 1, 0
	createsprite gBasicHitSplatSpriteTemplate, ANIM_TARGET, 4, -16, -16, ANIM_TARGET, 1
	playsewithpan SE_M_VITAL_THROW2, SOUND_PAN_TARGET
	createsprite gDizzyPunchDuckSpriteTemplate, ANIM_TARGET, 3, -16, -8, 160, -32
	createsprite gDizzyPunchDuckSpriteTemplate, ANIM_TARGET, 3, -16, -8, -256, -40
	createsprite gDizzyPunchDuckSpriteTemplate, ANIM_TARGET, 3, -16, -8, 128, -16
	createsprite gDizzyPunchDuckSpriteTemplate, ANIM_TARGET, 3, -16, -8, 416, -38
	createsprite gDizzyPunchDuckSpriteTemplate, ANIM_TARGET, 3, -16, -8, -128, -22
	createsprite gDizzyPunchDuckSpriteTemplate, ANIM_TARGET, 3, -16, -8, -384, -31
	waitforvisualfinish
	clearmonbg ANIM_TARGET
	blendoff
	end

DizzyPunchLunge:
	createsprite gHorizontalLungeSpriteTemplate, ANIM_ATTACKER, 2, 6, 4
	delay 6
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_TARGET, 3, 0, 7, 1
	return

Move_FIRE_SPIN:
	loadspritegfx ANIM_TAG_SMALL_EMBER
	playsewithpan SE_M_SACRED_FIRE2, SOUND_PAN_TARGET
	createvisualtask AnimTask_ShakeMon, 5, ANIM_TARGET, 0, 2, 47, 1
	call FireSpinEffect
	call FireSpinEffect
	call FireSpinEffect
	waitforvisualfinish
	end

FireSpinEffect:
	createsprite gFireSpinSpriteTemplate, ANIM_TARGET, 2, 0, 28, 528, 30, 13, 50, ANIM_TARGET
	delay 2
	createsprite gFireSpinSpriteTemplate, ANIM_TARGET, 2, 0, 32, 480, 20, 16, -46, ANIM_TARGET
	delay 2
	createsprite gFireSpinSpriteTemplate, ANIM_TARGET, 2, 0, 33, 576, 20, 8, 42, ANIM_TARGET
	delay 2
	createsprite gFireSpinSpriteTemplate, ANIM_TARGET, 2, 0, 31, 400, 25, 11, -42, ANIM_TARGET
	delay 2
	createsprite gFireSpinSpriteTemplate, ANIM_TARGET, 2, 0, 28, 512, 25, 16, 46, ANIM_TARGET
	delay 2
	createsprite gFireSpinSpriteTemplate, ANIM_TARGET, 2, 0, 33, 464, 30, 15, -50, ANIM_TARGET
	delay 2
	return

Move_FURY_CUTTER:
	loadspritegfx ANIM_TAG_CUT
	monbg ANIM_TARGET
	setalpha 12, 8
	playsewithpan SE_M_RAZOR_WIND, SOUND_PAN_TARGET
	createvisualtask AnimTask_IsFuryCutterHitRight, 2
	jumpretfalse FuryCutterLeft
	goto FuryCutterRight

FuryCutterContinue:
	createvisualtask AnimTask_GetFuryCutterHitCount, 2
	jumpreteq 1, FuryCutterContinue2
	jumpreteq 2, FuryCutterMedium
	jumpreteq 3, FuryCutterStrong
	goto FuryCutterStrongest

FuryCutterContinue2:
	delay 5
	createvisualtask AnimTask_ShakeMon, 2, ANIM_TARGET, 0, 3, 10, 1
	waitforvisualfinish
	clearmonbg ANIM_TARGET
	blendoff
	waitforvisualfinish
	end

FuryCutterLeft:
	createsprite gCuttingSliceSpriteTemplate, ANIM_ATTACKER, 2, 40, -32, 0
	goto FuryCutterContinue

FuryCutterRight:
	createsprite gCuttingSliceSpriteTemplate, ANIM_ATTACKER, 2, 40, -32, 1
	goto FuryCutterContinue

FuryCutterMedium:
	createsprite gComplexPaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG | F_PAL_BATTLERS, 3, 1, RGB(9, 8, 10), 4, RGB_BLACK, 0
	goto FuryCutterContinue2

FuryCutterStrong:
	createsprite gComplexPaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG | F_PAL_BATTLERS, 3, 3, RGB(9, 8, 10), 4, RGB_BLACK, 0
	goto FuryCutterContinue2

FuryCutterStrongest:
	createsprite gComplexPaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG | F_PAL_BATTLERS, 3, 3, RGB(9, 8, 10), 4, RGB_BLACK, 0
	goto FuryCutterContinue2

Move_SELF_DESTRUCT:
	loadspritegfx ANIM_TAG_EXPLOSION
	createvisualtask AnimTask_BlendBattleAnimPal, 10, F_PAL_ATTACKER, 1, 0, 9, RGB_RED
	createvisualtask AnimTask_ShakeMon2, 5, 4, 6, 0, 38, 1
	createvisualtask AnimTask_ShakeMon2, 5, 5, 6, 0, 38, 1
	createvisualtask AnimTask_ShakeMon2, 5, 6, 6, 0, 38, 1
	createvisualtask AnimTask_ShakeMon2, 5, 7, 6, 0, 38, 1
	createvisualtask AnimTask_ShakeMon2, 5, 8, 6, 0, 38, 1
	call SelfDestructExplode
	call SelfDestructExplode
	waitforvisualfinish
	createvisualtask AnimTask_BlendBattleAnimPal, 10, F_PAL_ATTACKER, 1, 9, 0, RGB_RED
	end

SelfDestructExplode:
	playsewithpan SE_M_SELF_DESTRUCT, SOUND_PAN_ATTACKER
	createsprite gExplosionSpriteTemplate, ANIM_ATTACKER, 3, 0, 0, 0, 1
	delay 6
	playsewithpan SE_M_SELF_DESTRUCT, SOUND_PAN_ATTACKER
	createsprite gExplosionSpriteTemplate, ANIM_ATTACKER, 3, 24, -24, 0, 1
	delay 6
	playsewithpan SE_M_SELF_DESTRUCT, SOUND_PAN_ATTACKER
	createsprite gExplosionSpriteTemplate, ANIM_ATTACKER, 3, -16, 16, 0, 1
	delay 6
	playsewithpan SE_M_SELF_DESTRUCT, SOUND_PAN_ATTACKER
	createsprite gExplosionSpriteTemplate, ANIM_ATTACKER, 3, -24, -12, 0, 1
	delay 6
	playsewithpan SE_M_SELF_DESTRUCT, SOUND_PAN_ATTACKER
	createsprite gExplosionSpriteTemplate, ANIM_ATTACKER, 3, 16, 16, 0, 1
	delay 6
	return

Move_SLAM:
	loadspritegfx ANIM_TAG_SLAM_HIT
	loadspritegfx ANIM_TAG_IMPACT
	monbg ANIM_TARGET
	setalpha 12, 8
	playsewithpan SE_M_COMET_PUNCH, SOUND_PAN_ATTACKER
	createsprite gSlideMonToOffsetSpriteTemplate, ANIM_ATTACKER, 2, 0, 20, 3, 0, 4
	delay 1
	createsprite gSlamHitSpriteTemplate, ANIM_ATTACKER, 2, 0, 0
	delay 3
	playsewithpan SE_M_MEGA_KICK2, SOUND_PAN_TARGET
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 3, 0, 0, ANIM_TARGET, 1
	createsprite gSlideMonToOffsetSpriteTemplate, ANIM_ATTACKER, 2, 1, -12, 10, 0, 3
	createsprite gSlideMonToOriginalPosSpriteTemplate, ANIM_ATTACKER, 2, 0, 0, 5
	delay 3
	createvisualtask AnimTask_ShakeMonInPlace, 2, ANIM_TARGET, 0, 3, 6, 1
	waitforvisualfinish
	delay 5
	createsprite gSlideMonToOriginalPosSpriteTemplate, ANIM_ATTACKER, 2, 1, 0, 6
	waitforvisualfinish
	clearmonbg ANIM_TARGET
	blendoff
	end

Move_VINE_WHIP:
	loadspritegfx ANIM_TAG_WHIP_HIT
	playsewithpan SE_M_JUMP_KICK, SOUND_PAN_ATTACKER
	createsprite gHorizontalLungeSpriteTemplate, ANIM_ATTACKER, 2, 4, 6
	delay 6
	playsewithpan SE_M_SCRATCH, SOUND_PAN_TARGET
	createsprite gVineWhipSpriteTemplate, ANIM_TARGET, 2, 0, 0
	delay 6
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_TARGET, 2, 0, 6, 1
	end

Move_DRILL_PECK:
	loadspritegfx ANIM_TAG_IMPACT
	loadspritegfx ANIM_TAG_WHIRLWIND_LINES
	createsprite gBowMonSpriteTemplate, ANIM_ATTACKER, 2, 0
	playsewithpan SE_M_HEADBUTT, SOUND_PAN_ATTACKER
	waitforvisualfinish
	delay 2
	createsprite gBowMonSpriteTemplate, ANIM_ATTACKER, 2, 1
	delay 2
	loopsewithpan SE_M_HORN_ATTACK, SOUND_PAN_TARGET, 4, 8
	createvisualtask AnimTask_DrillPeckHitSplats, 5
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_TARGET, 4, 0, 18, 1
	waitforvisualfinish
	createsprite gBowMonSpriteTemplate, ANIM_ATTACKER, 2, 2
	waitforvisualfinish
	createsprite gSlideMonToOriginalPosSpriteTemplate, ANIM_ATTACKER, 2, 0, 0, 6
	waitforvisualfinish
	end

Move_WATERFALL:
	loadspritegfx ANIM_TAG_WATER_IMPACT
	loadspritegfx ANIM_TAG_SMALL_BUBBLES
	loadspritegfx ANIM_TAG_ICE_CRYSTALS
	monbg ANIM_DEF_PARTNER
	setalpha 12, 8
	createvisualtask AnimTask_ShakeMon, 5, ANIM_ATTACKER, 0, 2, 23, 1
	delay 5
	playsewithpan SE_M_CRABHAMMER, SOUND_PAN_ATTACKER
	createsprite gSmallBubblePairSpriteTemplate, ANIM_ATTACKER, 2, 10, 10, 25, ANIM_ATTACKER
	delay 4
	playsewithpan SE_M_CRABHAMMER, SOUND_PAN_ATTACKER
	createsprite gSmallBubblePairSpriteTemplate, ANIM_ATTACKER, 2, -15, 0, 25, ANIM_ATTACKER
	delay 4
	playsewithpan SE_M_CRABHAMMER, SOUND_PAN_ATTACKER
	createsprite gSmallBubblePairSpriteTemplate, ANIM_ATTACKER, 2, 20, 10, 25, ANIM_ATTACKER
	delay 4
	playsewithpan SE_M_CRABHAMMER, SOUND_PAN_ATTACKER
	createsprite gSmallBubblePairSpriteTemplate, ANIM_ATTACKER, 2, 0, -10, 25, ANIM_ATTACKER
	delay 4
	playsewithpan SE_M_CRABHAMMER, SOUND_PAN_ATTACKER
	createsprite gSmallBubblePairSpriteTemplate, ANIM_ATTACKER, 2, -10, 15, 25, ANIM_ATTACKER
	delay 4
	playsewithpan SE_M_CRABHAMMER, SOUND_PAN_ATTACKER
	createsprite gSmallBubblePairSpriteTemplate, ANIM_ATTACKER, 2, 25, 20, 25, ANIM_ATTACKER
	delay 4
	playsewithpan SE_M_CRABHAMMER, SOUND_PAN_ATTACKER
	createsprite gSmallBubblePairSpriteTemplate, ANIM_ATTACKER, 2, -20, 20, 25, ANIM_ATTACKER
	delay 4
	playsewithpan SE_M_CRABHAMMER, SOUND_PAN_ATTACKER
	createsprite gSmallBubblePairSpriteTemplate, ANIM_ATTACKER, 2, 12, 0, 25, ANIM_ATTACKER
	waitforvisualfinish
	delay 10
	createsprite gHorizontalLungeSpriteTemplate, ANIM_ATTACKER, 2, 6, 5
	delay 6
	call RisingWaterHitEffect
	waitforvisualfinish
	clearmonbg ANIM_DEF_PARTNER
	blendoff
	end

RisingWaterHitEffect:
	playsewithpan SE_M_WATERFALL, SOUND_PAN_TARGET
	createvisualtask AnimTask_ShakeMon2, 5, ANIM_TARGET, 4, 0, 17, 1
	createsprite gWaterHitSplatSpriteTemplate, ANIM_ATTACKER, 3, 0, 20, ANIM_TARGET, 1
	createsprite gSmallDriftingBubblesSpriteTemplate, ANIM_ATTACKER, 4, 0, 20
	createsprite gSmallDriftingBubblesSpriteTemplate, ANIM_ATTACKER, 4, 0, 20
	delay 2
	createsprite gWaterHitSplatSpriteTemplate, ANIM_ATTACKER, 3, 0, 15, ANIM_TARGET, 1
	createsprite gSmallDriftingBubblesSpriteTemplate, ANIM_ATTACKER, 4, 0, 15
	createsprite gSmallDriftingBubblesSpriteTemplate, ANIM_ATTACKER, 4, 0, 15
	delay 2
	createsprite gWaterHitSplatSpriteTemplate, ANIM_ATTACKER, 3, 0, 10, ANIM_TARGET, 1
	createsprite gSmallDriftingBubblesSpriteTemplate, ANIM_ATTACKER, 4, 0, 10
	createsprite gSmallDriftingBubblesSpriteTemplate, ANIM_ATTACKER, 4, 0, 10
	delay 2
	createsprite gWaterHitSplatSpriteTemplate, ANIM_ATTACKER, 3, 0, 5, ANIM_TARGET, 1
	createsprite gSmallDriftingBubblesSpriteTemplate, ANIM_ATTACKER, 4, 0, 5
	createsprite gSmallDriftingBubblesSpriteTemplate, ANIM_ATTACKER, 4, 0, 5
	delay 2
	createsprite gWaterHitSplatSpriteTemplate, ANIM_ATTACKER, 3, 0, 0, ANIM_TARGET, 1
	createsprite gSmallDriftingBubblesSpriteTemplate, ANIM_ATTACKER, 4, 0, 0
	createsprite gSmallDriftingBubblesSpriteTemplate, ANIM_ATTACKER, 4, 0, 0
	delay 2
	createsprite gWaterHitSplatSpriteTemplate, ANIM_ATTACKER, 3, 0, -5, ANIM_TARGET, 1
	createsprite gSmallDriftingBubblesSpriteTemplate, ANIM_ATTACKER, 4, 0, -5
	createsprite gSmallDriftingBubblesSpriteTemplate, ANIM_ATTACKER, 4, 0, -5
	delay 2
	createsprite gWaterHitSplatSpriteTemplate, ANIM_ATTACKER, 3, 0, -10, ANIM_TARGET, 1
	createsprite gSmallDriftingBubblesSpriteTemplate, ANIM_ATTACKER, 4, 0, -10
	createsprite gSmallDriftingBubblesSpriteTemplate, ANIM_ATTACKER, 4, 0, -10
	delay 2
	createsprite gWaterHitSplatSpriteTemplate, ANIM_ATTACKER, 3, 0, -15, ANIM_TARGET, 1
	createsprite gSmallDriftingBubblesSpriteTemplate, ANIM_ATTACKER, 4, 0, -15
	createsprite gSmallDriftingBubblesSpriteTemplate, ANIM_ATTACKER, 4, 0, -15
	delay 2
	createsprite gWaterHitSplatSpriteTemplate, ANIM_ATTACKER, 3, 0, -20, ANIM_TARGET, 1
	createsprite gSmallDriftingBubblesSpriteTemplate, ANIM_ATTACKER, 4, 0, -20
	createsprite gSmallDriftingBubblesSpriteTemplate, ANIM_ATTACKER, 4, 0, -20
	return

Move_EXPLOSION:
	loadspritegfx ANIM_TAG_EXPLOSION
.if REVISION >= 0xA
	createsprite gComplexPaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG, 8, 9, RGB(26, 8, 8), 8, RGB_BLACK, 5
.else
	createsprite gComplexPaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG, 8, 9, RGB(26, 8, 8), 8, RGB_BLACK, 8
.endif
	createvisualtask AnimTask_ShakeMon2, 5, 4, 8, 0, 40, 1
	createvisualtask AnimTask_ShakeMon2, 5, 5, 8, 0, 40, 1
	createvisualtask AnimTask_ShakeMon2, 5, 6, 8, 0, 40, 1
	createvisualtask AnimTask_ShakeMon2, 5, 7, 8, 0, 40, 1
	createvisualtask AnimTask_ShakeMon2, 5, 8, 8, 0, 40, 1
	call Explosion1
	call Explosion1
	waitforvisualfinish
	createvisualtask AnimTask_BlendBattleAnimPal, 10, F_PAL_BG, 1, 16, 16, RGB_WHITE
	delay 50
	createvisualtask AnimTask_BlendBattleAnimPal, 10, F_PAL_BG, 3, 16, 0, RGB_WHITE
	end

Explosion1:
	playsewithpan SE_M_EXPLOSION, SOUND_PAN_ATTACKER
	createsprite gExplosionSpriteTemplate, ANIM_ATTACKER, 3, 0, 0, 0, 1
	delay 6
	playsewithpan SE_M_EXPLOSION, SOUND_PAN_ATTACKER
	createsprite gExplosionSpriteTemplate, ANIM_ATTACKER, 3, 24, -24, 0, 1
	delay 6
	playsewithpan SE_M_EXPLOSION, SOUND_PAN_ATTACKER
	createsprite gExplosionSpriteTemplate, ANIM_ATTACKER, 3, -16, 16, 0, 1
	delay 6
	playsewithpan SE_M_EXPLOSION, SOUND_PAN_ATTACKER
	createsprite gExplosionSpriteTemplate, ANIM_ATTACKER, 3, -24, -12, 0, 1
	delay 6
	playsewithpan SE_M_EXPLOSION, SOUND_PAN_ATTACKER
	createsprite gExplosionSpriteTemplate, ANIM_ATTACKER, 3, 16, 16, 0, 1
	delay 6
	return

Move_DEFENSE_CURL:
	loadspritegfx ANIM_TAG_ECLIPSING_ORB
	loopsewithpan SE_M_TRI_ATTACK, SOUND_PAN_ATTACKER, 18, 3
	createvisualtask AnimTask_SetGrayscaleOrOriginalPal, 5, ANIM_ATTACKER, 0
	createvisualtask AnimTask_DefenseCurlDeformMon, 5
	waitforvisualfinish
	createsprite gEclipsingOrbSpriteTemplate, ANIM_ATTACKER, 2, 0, 6, 0, 1
	waitforvisualfinish
	createvisualtask AnimTask_SetGrayscaleOrOriginalPal, 5, ANIM_ATTACKER, 1
	waitforvisualfinish
	end

Move_PROTECT:
	loadspritegfx ANIM_TAG_PROTECT
	monbg ANIM_ATK_PARTNER
	splitbgprio ANIM_ATTACKER
	waitplaysewithpan SE_M_REFLECT, SOUND_PAN_ATTACKER, 16
	createsprite gProtectSpriteTemplate, ANIM_ATTACKER, 2, 24, 0, 90
	waitforvisualfinish
	clearmonbg ANIM_ATK_PARTNER
	end

Move_DETECT:
	loadspritegfx ANIM_TAG_SPARKLE_4
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG, 2, 0, 9, RGB_BLACK
	waitforvisualfinish
	createvisualtask AnimTask_BlendBattleAnimPal, 10, F_PAL_ATTACKER, 1, 0, 9, RGB_WHITE
	delay 18
	playsewithpan SE_M_DETECT, SOUND_PAN_ATTACKER
	createsprite gSpinningSparkleSpriteTemplate, ANIM_ATTACKER, 13, 20, -20
	waitforvisualfinish
	delay 10
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG, 2, 9, 0, RGB_BLACK
	createvisualtask AnimTask_BlendBattleAnimPal, 10, F_PAL_ATTACKER, 2, 9, 0, RGB_WHITE
	waitforvisualfinish
	end

Move_FRUSTRATION:
	loadspritegfx ANIM_TAG_IMPACT
	loadspritegfx ANIM_TAG_ANGER
	monbg ANIM_DEF_PARTNER
	setalpha 12, 8
	createvisualtask AnimTask_GetFrustrationPowerLevel, 1
	jumpreteq 0, Frustration_Strongest
	jumpreteq 1, Frustration_Strong
	jumpreteq 2, Frustration_Medium
	goto Frustration_Weak

Frustration_Continue:
	waitforvisualfinish
	clearmonbg ANIM_DEF_PARTNER
	blendoff
	end

Frustration_Strongest:
	playsewithpan SE_M_DRAGON_RAGE, SOUND_PAN_ATTACKER
	createvisualtask AnimTask_ShakeMon2, 5, ANIM_ATTACKER, 1, 0, 15, 1
	createvisualtask AnimTask_BlendBattleAnimPal, 10, F_PAL_ATTACKER, 3, 0, 9, RGB_RED
	waitforvisualfinish
	delay 20
	playsewithpan SE_M_SWAGGER2, SOUND_PAN_ATTACKER
	createsprite gAngerMarkSpriteTemplate, ANIM_ATTACKER, 2, 0, 20, -28
	waitforvisualfinish
	playsewithpan SE_M_SWAGGER2, SOUND_PAN_ATTACKER
	createsprite gAngerMarkSpriteTemplate, ANIM_ATTACKER, 2, 0, 20, -28
	waitforvisualfinish
	delay 10
	createvisualtask AnimTask_SwayMon, 5, 0, 16, 6144, 8, ANIM_ATTACKER
	delay 5
	createvisualtask AnimTask_ShakeMon2, 5, ANIM_TARGET, 4, 0, 30, 1
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 3, 0, 0, ANIM_TARGET, 0
	playsewithpan SE_M_COMET_PUNCH, SOUND_PAN_TARGET
	delay 5
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 3, 24, 8, ANIM_TARGET, 0
	playsewithpan SE_M_COMET_PUNCH, SOUND_PAN_TARGET
	delay 5
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 3, -24, -16, ANIM_TARGET, 0
	playsewithpan SE_M_COMET_PUNCH, SOUND_PAN_TARGET
	delay 5
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 3, 8, 4, ANIM_TARGET, 0
	playsewithpan SE_M_COMET_PUNCH, SOUND_PAN_TARGET
	delay 5
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 3, -16, 19, ANIM_TARGET, 0
	playsewithpan SE_M_COMET_PUNCH, SOUND_PAN_TARGET
	delay 5
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 3, 18, -18, ANIM_TARGET, 0
	playsewithpan SE_M_COMET_PUNCH, SOUND_PAN_TARGET
	waitforvisualfinish
	createvisualtask AnimTask_BlendBattleAnimPal, 10, F_PAL_ATTACKER, 3, 9, 0, RGB_RED
	goto Frustration_Continue

Frustration_Strong:
	playsewithpan SE_M_DRAGON_RAGE, SOUND_PAN_ATTACKER
	createvisualtask AnimTask_ShakeMon2, 5, ANIM_ATTACKER, 1, 0, 15, 1
	createvisualtask AnimTask_BlendBattleAnimPal, 10, F_PAL_ATTACKER, 3, 0, 9, RGB_RED
	waitforvisualfinish
	delay 20
	playsewithpan SE_M_SWAGGER2, SOUND_PAN_ATTACKER
	createsprite gAngerMarkSpriteTemplate, ANIM_ATTACKER, 2, 0, 20, -28
	waitforvisualfinish
	delay 5
	createvisualtask AnimTask_StrongFrustrationGrowAndShrink, 5
	delay 7
	playsewithpan SE_M_COMET_PUNCH, SOUND_PAN_TARGET
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 3, 0, 8, ANIM_TARGET, 1
	createvisualtask AnimTask_ShakeMon2, 5, ANIM_TARGET, 4, 0, 6, 1
	delay 14
	playsewithpan SE_M_COMET_PUNCH, SOUND_PAN_TARGET
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 3, 12, -6, ANIM_TARGET, 1
	createvisualtask AnimTask_ShakeMon2, 5, ANIM_TARGET, 4, 0, 6, 1
	delay 14
	playsewithpan SE_M_COMET_PUNCH, SOUND_PAN_TARGET
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 3, -12, -6, ANIM_TARGET, 1
	createvisualtask AnimTask_ShakeMon2, 5, ANIM_TARGET, 4, 0, 6, 1
	waitforvisualfinish
	createvisualtask AnimTask_BlendBattleAnimPal, 10, F_PAL_ATTACKER, 3, 9, 0, RGB_RED
	goto Frustration_Continue

Frustration_Medium:
	playsewithpan SE_M_SWAGGER2, SOUND_PAN_ATTACKER
	createsprite gAngerMarkSpriteTemplate, ANIM_ATTACKER, 2, 0, 20, -28
	waitforvisualfinish
	delay 5
	createsprite gHorizontalLungeSpriteTemplate, ANIM_ATTACKER, 2, 4, 4
	delay 6
	playsewithpan SE_M_COMET_PUNCH, SOUND_PAN_TARGET
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 2, 10, 4, ANIM_TARGET, 1
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_TARGET, 3, 0, 6, 1
	waitforvisualfinish
	createsprite gHorizontalLungeSpriteTemplate, ANIM_ATTACKER, 2, 4, 4
	delay 6
	playsewithpan SE_M_COMET_PUNCH, SOUND_PAN_TARGET
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 2, -10, -4, ANIM_TARGET, 2
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_TARGET, 3, 0, 6, 1
	goto Frustration_Continue

Frustration_Weak:
	createsprite gWeakFrustrationAngerMarkSpriteTemplate, ANIM_ATTACKER, 2, 20, -28
	waitforvisualfinish
	delay 10
	createsprite gHorizontalLungeSpriteTemplate, ANIM_ATTACKER, 2, 10, 2
	delay 12
	playsewithpan SE_M_COMET_PUNCH, SOUND_PAN_TARGET
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 2, 0, 0, ANIM_TARGET, 2
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_TARGET, 1, 0, 6, 1
	goto Frustration_Continue

Move_SAFEGUARD:
	loadspritegfx ANIM_TAG_GUARD_RING
	monbg ANIM_ATK_PARTNER
	setalpha 8, 8
	playsewithpan SE_M_MILK_DRINK, SOUND_PAN_ATTACKER
	createsprite gGuardRingSpriteTemplate, ANIM_ATTACKER, 2
	delay 4
	createsprite gGuardRingSpriteTemplate, ANIM_ATTACKER, 2
	delay 4
	createsprite gGuardRingSpriteTemplate, ANIM_ATTACKER, 2
	waitforvisualfinish
	playsewithpan SE_SHINY, SOUND_PAN_ATTACKER
	createvisualtask AnimTask_BlendColorCycle, 2, F_PAL_ATK_SIDE, 0, 2, 0, 10, RGB_WHITE
	waitforvisualfinish
	clearmonbg ANIM_ATK_PARTNER
	blendoff
	end

Move_PAIN_SPLIT:
	loadspritegfx ANIM_TAG_PAIN_SPLIT
	createsprite gPainSplitProjectileSpriteTemplate, ANIM_ATTACKER, 2, -8, -42, ANIM_ATTACKER
	createsprite gPainSplitProjectileSpriteTemplate, ANIM_TARGET, 2, -8, -42, ANIM_TARGET
	delay 10
	playsewithpan SE_M_SWAGGER2, 0
	createvisualtask AnimTask_PainSplitMovement, 2, ANIM_ATTACKER, 0
	createvisualtask AnimTask_PainSplitMovement, 2, ANIM_TARGET, 0
	waitforvisualfinish
	createsprite gPainSplitProjectileSpriteTemplate, ANIM_ATTACKER, 2, -24, -42, ANIM_ATTACKER
	createsprite gPainSplitProjectileSpriteTemplate, ANIM_TARGET, 2, -24, -42, ANIM_TARGET
	delay 10
	playsewithpan SE_M_SWAGGER2, 0
	createvisualtask AnimTask_PainSplitMovement, 2, ANIM_ATTACKER, 1
	createvisualtask AnimTask_PainSplitMovement, 2, ANIM_TARGET, 1
	waitforvisualfinish
	createsprite gPainSplitProjectileSpriteTemplate, ANIM_ATTACKER, 2, 8, -42, ANIM_ATTACKER
	createsprite gPainSplitProjectileSpriteTemplate, ANIM_TARGET, 2, 8, -42, ANIM_TARGET
	delay 10
	playsewithpan SE_M_SWAGGER2, 0
	createvisualtask AnimTask_PainSplitMovement, 2, ANIM_ATTACKER, 2
	createvisualtask AnimTask_PainSplitMovement, 2, ANIM_TARGET, 2
	end

Move_VICE_GRIP:
	loadspritegfx ANIM_TAG_CUT
	loadspritegfx ANIM_TAG_IMPACT
	monbg ANIM_DEF_PARTNER
	setalpha 12, 8
	playsewithpan SE_M_VICEGRIP, SOUND_PAN_TARGET
	createsprite gViceGripSpriteTemplate, ANIM_ATTACKER, 2, 0
	createsprite gViceGripSpriteTemplate, ANIM_ATTACKER, 2, 1
	delay 9
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 1, 0, 0, ANIM_TARGET, 2
	createvisualtask AnimTask_ShakeMon2, 5, ANIM_TARGET, 2, 0, 5, 1
	waitforvisualfinish
	clearmonbg ANIM_DEF_PARTNER
	blendoff
	end

Move_GUILLOTINE:
	loadspritegfx ANIM_TAG_CUT
	loadspritegfx ANIM_TAG_IMPACT
	monbg ANIM_DEF_PARTNER
	setalpha 12, 8
	fadetobgfromset BG_GUILLOTINE_OPPONENT, BG_GUILLOTINE_PLAYER, BG_GUILLOTINE_CONTESTS
	waitbgfadein
	playsewithpan SE_M_VICEGRIP, SOUND_PAN_TARGET
	createsprite gGuillotineSpriteTemplate, ANIM_ATTACKER, 2, 0
	createsprite gGuillotineSpriteTemplate, ANIM_ATTACKER, 2, 1
	createvisualtask AnimTask_BlendBattleAnimPal, 10, F_PAL_TARGET, 2, 0, 16, RGB_BLACK
	delay 9
	createvisualtask AnimTask_ShakeMon2, 5, ANIM_TARGET, 2, 0, 23, 1
	delay 46
	createvisualtask AnimTask_ShakeMon2, 5, ANIM_TARGET, 4, 0, 8, 1
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 3, 0, 0, ANIM_TARGET, 0
	createsprite gComplexPaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG | F_PAL_BATTLERS, 3, 1, RGB_BLACK, 8, RGB_BLACK, 0
	playsewithpan SE_M_RAZOR_WIND, SOUND_PAN_TARGET
	waitforvisualfinish
	clearmonbg ANIM_DEF_PARTNER
	blendoff
	restorebg
	waitbgfadein
	end

Move_PAY_DAY:
	loadspritegfx ANIM_TAG_COIN
	loadspritegfx ANIM_TAG_IMPACT
	monbg ANIM_TARGET
	splitbgprio ANIM_TARGET
	setalpha 12, 8
	playsewithpan SE_M_RAZOR_WIND2, SOUND_PAN_ATTACKER
	createsprite gCoinThrowSpriteTemplate, ANIM_ATTACKER, 2, 20, 0, 0, 0, 1152
	waitforvisualfinish
	playsewithpan SE_M_PAY_DAY, SOUND_PAN_TARGET
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 1, 0, 0, ANIM_TARGET, 2
	createsprite gFallingCoinSpriteTemplate, ANIM_ATTACKER, 2
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_TARGET, 1, 0, 6, 1
	waitforvisualfinish
	clearmonbg ANIM_TARGET
	blendoff
	end

Move_OUTRAGE:
	loadspritegfx ANIM_TAG_SMALL_EMBER
	loopsewithpan SE_M_DRAGON_RAGE, SOUND_PAN_ATTACKER, 8, 3
	createvisualtask AnimTask_BlendColorCycle, 2, F_PAL_BG | F_PAL_ATTACKER | F_PAL_TARGET, 2, 5, 3, 8, RGB(14, 13, 0)
	createvisualtask AnimTask_TranslateMonEllipticalRespectSide, 2, ANIM_ATTACKER, 12, 6, 5, 4
	delay 0
	createsprite gOutrageFlameSpriteTemplate, ANIM_TARGET, 2, 0, 0, 30, 1280, 0, 3
	delay 0
	createsprite gOutrageFlameSpriteTemplate, ANIM_TARGET, 2, 0, 0, 30, -1280, 0, 3
	delay 0
	createsprite gOutrageFlameSpriteTemplate, ANIM_TARGET, 2, 0, 0, 30, 0, 1280, 3
	delay 0
	createsprite gOutrageFlameSpriteTemplate, ANIM_TARGET, 2, 0, 0, 30, 0, -1280, 3
	delay 0
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_TARGET, 2, 0, 40, 1
	createsprite gOutrageFlameSpriteTemplate, ANIM_TARGET, 2, 0, 0, 30, 1280, 768, 3
	delay 0
	createsprite gOutrageFlameSpriteTemplate, ANIM_TARGET, 2, 0, 0, 30, -1280, 768, 3
	delay 0
	createsprite gOutrageFlameSpriteTemplate, ANIM_TARGET, 2, 0, 0, 30, 1280, -768, 3
	delay 0
	createsprite gOutrageFlameSpriteTemplate, ANIM_TARGET, 2, 0, 0, 30, -1280, -768, 3
	delay 0
	createsprite gOutrageFlameSpriteTemplate, ANIM_TARGET, 2, 0, 0, 30, 1280, 0, 3
	call OutrageFlames
	call OutrageFlames
	waitforvisualfinish
	end

OutrageFlames:
	delay 3
	createsprite gOutrageFlameSpriteTemplate, ANIM_TARGET, 2, 0, 0, 30, -1280, 0, 3
	delay 0
	createsprite gOutrageFlameSpriteTemplate, ANIM_TARGET, 2, 0, 0, 30, 0, 1280, 3
	delay 0
	createsprite gOutrageFlameSpriteTemplate, ANIM_TARGET, 2, 0, 0, 30, 0, -1280, 3
	delay 0
	createsprite gOutrageFlameSpriteTemplate, ANIM_TARGET, 2, 0, 0, 30, 1280, 768, 3
	delay 0
	createsprite gOutrageFlameSpriteTemplate, ANIM_TARGET, 2, 0, 0, 30, -1280, 768, 3
	delay 0
	createsprite gOutrageFlameSpriteTemplate, ANIM_TARGET, 2, 0, 0, 30, 1280, -768, 3
	delay 0
	createsprite gOutrageFlameSpriteTemplate, ANIM_TARGET, 2, 0, 0, 30, -1280, -768, 3
	return

Move_SPARK:
	loadspritegfx ANIM_TAG_IMPACT
	loadspritegfx ANIM_TAG_SPARK_2
	delay 0
	createvisualtask AnimTask_BlendColorCycle, 2, F_PAL_BG | F_PAL_ATTACKER, -31, 1, 5, 5, RGB(31, 31, 22)
	playsewithpan SE_M_THUNDERBOLT2, SOUND_PAN_ATTACKER
	createsprite gSparkElectricitySpriteTemplate, ANIM_ATTACKER, 0, 32, 24, 190, 12, ANIM_ATTACKER, 1, 0
	delay 0
	createsprite gSparkElectricitySpriteTemplate, ANIM_ATTACKER, 0, 80, 24, 22, 12, ANIM_ATTACKER, 1, 0
	createsprite gSparkElectricitySpriteTemplate, ANIM_ATTACKER, 0, 156, 24, 121, 13, ANIM_ATTACKER, 1, 1
	delay 0
	createvisualtask AnimTask_BlendColorCycle, 2, F_PAL_BG | F_PAL_ATTACKER, -31, 1, 0, 0, RGB(31, 31, 22)
	delay 10
	createvisualtask AnimTask_BlendColorCycle, 2, F_PAL_BG | F_PAL_ATTACKER, -31, 1, 5, 5, RGB(31, 31, 22)
	playsewithpan SE_M_THUNDERBOLT2, SOUND_PAN_ATTACKER
	createsprite gSparkElectricitySpriteTemplate, ANIM_ATTACKER, 0, 100, 24, 60, 10, ANIM_ATTACKER, 1, 0
	createsprite gSparkElectricitySpriteTemplate, ANIM_ATTACKER, 0, 170, 24, 42, 11, ANIM_ATTACKER, 1, 1
	delay 0
	createsprite gSparkElectricitySpriteTemplate, ANIM_ATTACKER, 0, 238, 24, 165, 10, ANIM_ATTACKER, 1, 1
	delay 0
	createvisualtask AnimTask_BlendColorCycle, 2, F_PAL_BG | F_PAL_ATTACKER, -31, 1, 0, 0, RGB(31, 31, 22)
	delay 20
	createvisualtask AnimTask_BlendColorCycle, 2, F_PAL_BG | F_PAL_ATTACKER, -31, 1, 7, 7, RGB(31, 31, 22)
	playsewithpan SE_M_THUNDERBOLT2, SOUND_PAN_ATTACKER
	createsprite gSparkElectricityFlashingSpriteTemplate, ANIM_ATTACKER, 4, 0, 0, 32, 12, 0, 20, 0, 0
	createsprite gSparkElectricityFlashingSpriteTemplate, ANIM_ATTACKER, 4, 0, 0, 32, 12, 64, 20, 1, 0
	createsprite gSparkElectricityFlashingSpriteTemplate, ANIM_ATTACKER, 4, 0, 0, 32, 12, 128, 20, 0, 0
	createsprite gSparkElectricityFlashingSpriteTemplate, ANIM_ATTACKER, 4, 0, 0, 32, 12, 192, 20, 2, 0
	createsprite gSparkElectricityFlashingSpriteTemplate, ANIM_ATTACKER, 4, 0, 0, 16, 12, 32, 20, 0, 0
	createsprite gSparkElectricityFlashingSpriteTemplate, ANIM_ATTACKER, 4, 0, 0, 16, 12, 96, 20, 1, 0
	createsprite gSparkElectricityFlashingSpriteTemplate, ANIM_ATTACKER, 4, 0, 0, 16, 12, 160, 20, 0, 0
	createsprite gSparkElectricityFlashingSpriteTemplate, ANIM_ATTACKER, 4, 0, 0, 16, 12, 224, 20, 2, 0
	delay 4
	waitforvisualfinish
	createvisualtask AnimTask_BlendColorCycle, 2, F_PAL_BG | F_PAL_ATTACKER, -31, 1, 0, 0, RGB(31, 31, 22)
	createsprite gHorizontalLungeSpriteTemplate, ANIM_ATTACKER, 2, 4, 4
	delay 4
	playsewithpan SE_M_HYPER_BEAM, SOUND_PAN_TARGET
	createsprite gBasicHitSplatSpriteTemplate, ANIM_TARGET, 2, 0, 0, ANIM_TARGET, 2
	createvisualtask AnimTask_ShakeMon, 2, ANIM_TARGET, 3, 0, 6, 1
	waitforvisualfinish
	createvisualtask AnimTask_BlendColorCycle, 2, F_PAL_TARGET, -31, 2, 0, 6, RGB(31, 31, 22)
	call ElectricityEffect
	waitforvisualfinish
	end

Move_ATTRACT:
	loadspritegfx ANIM_TAG_RED_HEART
	loopsewithpan SE_M_CHARM, SOUND_PAN_ATTACKER, 12, 3
	createvisualtask AnimTask_SwayMon, 5, 0, 12, 4096, 4, ANIM_ATTACKER
	delay 15
	createsprite gRedHeartProjectileSpriteTemplate, ANIM_TARGET, 3, 20, -8
	waitforvisualfinish
	playsewithpan SE_M_ATTRACT, SOUND_PAN_TARGET
	createsprite gRedHeartBurstSpriteTemplate, ANIM_TARGET, 3, 160, -32
	createsprite gRedHeartBurstSpriteTemplate, ANIM_TARGET, 3, -256, -40
	createsprite gRedHeartBurstSpriteTemplate, ANIM_TARGET, 3, 128, -16
	createsprite gRedHeartBurstSpriteTemplate, ANIM_TARGET, 3, 416, -38
	createsprite gRedHeartBurstSpriteTemplate, ANIM_TARGET, 3, -128, -22
	createsprite gRedHeartBurstSpriteTemplate, ANIM_TARGET, 3, -384, -31
	waitforvisualfinish
	waitplaysewithpan SE_M_ATTRACT2, 0, 15
	createvisualtask AnimTask_HeartsBackground, 5
	createsprite gRedHeartRisingSpriteTemplate, ANIM_ATTACKER, 40, 16, 256, 0
	createsprite gRedHeartRisingSpriteTemplate, ANIM_ATTACKER, 40, 224, 240, 15
	createsprite gRedHeartRisingSpriteTemplate, ANIM_ATTACKER, 40, 126, 272, 30
	createsprite gRedHeartRisingSpriteTemplate, ANIM_ATTACKER, 40, 80, 224, 45
	createsprite gRedHeartRisingSpriteTemplate, ANIM_ATTACKER, 40, 170, 272, 60
	createsprite gRedHeartRisingSpriteTemplate, ANIM_ATTACKER, 40, 40, 256, 75
	createsprite gRedHeartRisingSpriteTemplate, ANIM_ATTACKER, 40, 112, 256, 90
	createsprite gRedHeartRisingSpriteTemplate, ANIM_ATTACKER, 40, 200, 272, 90
	delay 75
	createvisualtask AnimTask_BlendColorCycle, 2, F_PAL_TARGET, 4, 4, 0, 10, RGB(31, 25, 27)
	end

Move_GROWTH:
	call GrowthEffect
	waitforvisualfinish
	call GrowthEffect
	waitforvisualfinish
	end

GrowthEffect:
	createvisualtask AnimTask_BlendColorCycle, 2, F_PAL_ATTACKER, 0, 2, 0, 8, RGB_WHITE
	playsewithpan SE_M_TAKE_DOWN, SOUND_PAN_ATTACKER
	createvisualtask AnimTask_ScaleMonAndRestore, 5, -3, -3, 16, ANIM_ATTACKER, 0
	return

Move_WHIRLWIND:
	loadspritegfx ANIM_TAG_WHIRLWIND_LINES
	createsprite gWhirlwindLineSpriteTemplate, ANIM_ATTACKER, 2, 0, -8, ANIM_TARGET, 60, 0
	createsprite gWhirlwindLineSpriteTemplate, ANIM_ATTACKER, 2, 0, 0, ANIM_TARGET, 60, 1
	createsprite gWhirlwindLineSpriteTemplate, ANIM_ATTACKER, 2, 0, 8, ANIM_TARGET, 60, 2
	createsprite gWhirlwindLineSpriteTemplate, ANIM_ATTACKER, 2, 0, 16, ANIM_TARGET, 60, 3
	createsprite gWhirlwindLineSpriteTemplate, ANIM_ATTACKER, 2, 0, 24, ANIM_TARGET, 60, 4
	createsprite gWhirlwindLineSpriteTemplate, ANIM_ATTACKER, 2, 0, 32, ANIM_TARGET, 60, 0
	delay 5
	loopsewithpan SE_M_DOUBLE_TEAM, SOUND_PAN_TARGET, 10, 4
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_TARGET, 4, 0, 15, 1
	delay 29
	createvisualtask AnimTask_TranslateMonEllipticalRespectSide, 2, ANIM_TARGET, 12, 6, 1, 5
	delay 7
	playsewithpan SE_M_STRING_SHOT, SOUND_PAN_TARGET
	createvisualtask AnimTask_SlideOffScreen, 5, ANIM_TARGET, 8
	waitforvisualfinish
	end

Move_CONFUSE_RAY:
	loadspritegfx ANIM_TAG_YELLOW_BALL
	monbg ANIM_DEF_PARTNER
	fadetobg BG_GHOST
	waitbgfadein
	createvisualtask SoundTask_AdjustPanningVar, 2, SOUND_PAN_ATTACKER, SOUND_PAN_TARGET, 2, 0
	createvisualtask AnimTask_BlendColorCycleByTag, 2, ANIM_TAG_YELLOW_BALL, 0, 6, 0, 14, RGB(31, 10, 0)
	createsprite gConfuseRayBallBounceSpriteTemplate, ANIM_TARGET, 2, 28, 0, 288
	waitforvisualfinish
	setalpha 8, 8
	playsewithpan SE_M_STRING_SHOT2, SOUND_PAN_TARGET
	createsprite gConfuseRayBallSpiralSpriteTemplate, ANIM_TARGET, 2, 0, -16
	waitforvisualfinish
	delay 0
	blendoff
	clearmonbg ANIM_DEF_PARTNER
	restorebg
	waitbgfadein
	end

Move_LOCK_ON:
	loadspritegfx ANIM_TAG_LOCK_ON
	createsprite gLockOnTargetSpriteTemplate, ANIM_ATTACKER, 40
	createsprite gLockOnMoveTargetSpriteTemplate, ANIM_ATTACKER, 40, 1
	createsprite gLockOnMoveTargetSpriteTemplate, ANIM_ATTACKER, 40, 2
	createsprite gLockOnMoveTargetSpriteTemplate, ANIM_ATTACKER, 40, 3
	createsprite gLockOnMoveTargetSpriteTemplate, ANIM_ATTACKER, 40, 4  @ Also transitions to red target
	delay 120
	setarg 7, 0xFFFF  @ Signal target to flash/disappear
	waitforvisualfinish
	end

Move_MEAN_LOOK:
	loadspritegfx ANIM_TAG_EYE
	monbg ANIM_DEF_PARTNER
	playsewithpan SE_M_PSYBEAM, SOUND_PAN_ATTACKER
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG, 1, 0, 16, RGB_BLACK
	loopsewithpan SE_M_CONFUSE_RAY, SOUND_PAN_TARGET, 15, 4
	waitplaysewithpan SE_M_LEER, SOUND_PAN_TARGET, 85
	createsprite gMeanLookEyeSpriteTemplate, ANIM_ATTACKER, 2
	delay 120
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG, 2, 16, 0, RGB_BLACK
	delay 30
	clearmonbg ANIM_DEF_PARTNER
	waitforvisualfinish
	end

Move_ROCK_THROW:
	loadspritegfx ANIM_TAG_ROCKS
	createsprite gShakeMonOrTerrainSpriteTemplate, ANIM_TARGET, 2, 6, 1, 15, 1
	createsprite gFallingRockSpriteTemplate, ANIM_TARGET, 2, 0, 1, 0, 0
	playsewithpan SE_M_ROCK_THROW, SOUND_PAN_TARGET
	delay 6
	createsprite gFallingRockSpriteTemplate, ANIM_TARGET, 2, 19, 1, 10, 0
	playsewithpan SE_M_ROCK_THROW, SOUND_PAN_TARGET
	delay 6
	createsprite gFallingRockSpriteTemplate, ANIM_TARGET, 2, -23, 2, -10, 0
	playsewithpan SE_M_ROCK_THROW, SOUND_PAN_TARGET
	createvisualtask AnimTask_ShakeMon, 2, ANIM_TARGET, 0, 5, 20, 1
	delay 6
	createsprite gFallingRockSpriteTemplate, ANIM_TARGET, 2, -15, 1, -10, 0
	playsewithpan SE_M_ROCK_THROW, SOUND_PAN_TARGET
	delay 6
	createsprite gFallingRockSpriteTemplate, ANIM_TARGET, 2, 23, 2, 10, 0
	playsewithpan SE_M_ROCK_THROW, SOUND_PAN_TARGET
	waitforvisualfinish
	end

Move_ROCK_SLIDE:
	loadspritegfx ANIM_TAG_ROCKS
	monbg ANIM_DEF_PARTNER
	createsprite gShakeMonOrTerrainSpriteTemplate, ANIM_ATTACKER, 2, 7, 1, 11, 1
	createsprite gFallingRockSpriteTemplate, ANIM_TARGET, 2, -5, 1, -5, 1
	playsewithpan SE_M_ROCK_THROW, SOUND_PAN_TARGET
	delay 2
	createsprite gFallingRockSpriteTemplate, ANIM_TARGET, 2, 5, 0, 6, 1
	playsewithpan SE_M_ROCK_THROW, SOUND_PAN_TARGET
	delay 2
	createsprite gFallingRockSpriteTemplate, ANIM_TARGET, 2, 19, 1, 10, 1
	playsewithpan SE_M_ROCK_THROW, SOUND_PAN_TARGET
	delay 2
	createsprite gFallingRockSpriteTemplate, ANIM_TARGET, 2, -23, 2, -10, 1
	playsewithpan SE_M_ROCK_THROW, SOUND_PAN_TARGET
	createvisualtask AnimTask_ShakeMon, 2, ANIM_TARGET, 0, 5, 50, 1
	createvisualtask AnimTask_ShakeMon, 2, ANIM_DEF_PARTNER, 0, 5, 50, 1
	delay 2
	call RockSlideRocks
	call RockSlideRocks
	waitforvisualfinish
	clearmonbg ANIM_DEF_PARTNER
	end

RockSlideRocks:
	createsprite gFallingRockSpriteTemplate, ANIM_TARGET, 2, -20, 0, -10, 1
	playsewithpan SE_M_ROCK_THROW, SOUND_PAN_TARGET
	delay 2
	createsprite gFallingRockSpriteTemplate, ANIM_TARGET, 2, 28, 1, 10, 1
	playsewithpan SE_M_ROCK_THROW, SOUND_PAN_TARGET
	delay 2
	createsprite gFallingRockSpriteTemplate, ANIM_TARGET, 2, -10, 1, -5, 1
	playsewithpan SE_M_ROCK_THROW, SOUND_PAN_TARGET
	delay 2
	createsprite gFallingRockSpriteTemplate, ANIM_TARGET, 2, 10, 0, 6, 1
	playsewithpan SE_M_ROCK_THROW, SOUND_PAN_TARGET
	delay 2
	createsprite gFallingRockSpriteTemplate, ANIM_TARGET, 2, 24, 1, 10, 1
	playsewithpan SE_M_ROCK_THROW, SOUND_PAN_TARGET
	delay 2
	createsprite gFallingRockSpriteTemplate, ANIM_TARGET, 2, -32, 2, -10, 1
	playsewithpan SE_M_ROCK_THROW, SOUND_PAN_TARGET
	delay 2
	createsprite gFallingRockSpriteTemplate, ANIM_TARGET, 2, -20, 0, -10, 1
	playsewithpan SE_M_ROCK_THROW, SOUND_PAN_TARGET
	delay 2
	createsprite gFallingRockSpriteTemplate, ANIM_TARGET, 2, 30, 2, 10, 1
	playsewithpan SE_M_ROCK_THROW, SOUND_PAN_TARGET
	delay 2
	return

Move_THIEF:
	loadspritegfx ANIM_TAG_IMPACT
	monbg ANIM_TARGET
	delay 1
	fadetobg BG_DARK
	waitbgfadein
	setalpha 12, 8
	createsprite gHorizontalLungeSpriteTemplate, ANIM_ATTACKER, 2, 6, 4
	delay 6
	playsewithpan SE_M_VITAL_THROW, SOUND_PAN_TARGET
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 2, 0, 0, ANIM_TARGET, 2
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_TARGET, 1, 0, 8, 1
	waitforvisualfinish
	delay 20
	clearmonbg ANIM_TARGET
	blendoff
	restorebg
	waitbgfadein
	end

Move_BUBBLE_BEAM:
	loadspritegfx ANIM_TAG_BUBBLE
	loadspritegfx ANIM_TAG_SMALL_BUBBLES
	monbg ANIM_TARGET
	splitbgprio ANIM_TARGET
	setalpha 12, 8
	delay 1
	call BulbblebeamCreateBubbles
	createvisualtask AnimTask_SwayMon, 5, 0, 3, 3072, 8, ANIM_TARGET
	call BulbblebeamCreateBubbles
	call BulbblebeamCreateBubbles
	waitforvisualfinish
	call WaterBubblesEffectShort
	waitforvisualfinish
	clearmonbg ANIM_TARGET
	blendoff
	end

BulbblebeamCreateBubbles:
	createsprite gWaterBubbleProjectileSpriteTemplate, ANIM_ATTACKER, 2, 18, 0, 35, 70, 0, 256, 50
	playsewithpan SE_M_BUBBLE, SOUND_PAN_ATTACKER
	delay 3
	createsprite gWaterBubbleProjectileSpriteTemplate, ANIM_ATTACKER, 2, 18, 0, 20, 40, -10, 256, 50
	playsewithpan SE_M_BUBBLE, SOUND_PAN_ATTACKER
	delay 3
	createsprite gWaterBubbleProjectileSpriteTemplate, ANIM_ATTACKER, 2, 18, 0, 10, -60, 0, 256, 50
	playsewithpan SE_M_BUBBLE, SOUND_PAN_ATTACKER
	delay 3
	createsprite gWaterBubbleProjectileSpriteTemplate, ANIM_ATTACKER, 2, 18, 0, 15, -15, 10, 256, 50
	playsewithpan SE_M_BUBBLE, SOUND_PAN_ATTACKER
	delay 3
	createsprite gWaterBubbleProjectileSpriteTemplate, ANIM_ATTACKER, 2, 18, 0, 30, 10, -10, 256, 50
	playsewithpan SE_M_BUBBLE, SOUND_PAN_ATTACKER
	delay 3
	createsprite gWaterBubbleProjectileSpriteTemplate, ANIM_ATTACKER, 2, 18, 0, 25, -30, 10, 256, 50
	playsewithpan SE_M_BUBBLE, SOUND_PAN_ATTACKER
	delay 3
	return

Move_ICY_WIND:
	loadspritegfx ANIM_TAG_ICE_CRYSTALS
	loadspritegfx ANIM_TAG_ICE_SPIKES
	monbg ANIM_DEF_PARTNER
	createvisualtask AnimTask_BlendBattleAnimPal, 10, F_PAL_BG | F_PAL_ATK_SIDE, 4, 0, 4, RGB_BLACK
	fadetobg BG_ICE
	waitbgfadeout
	playsewithpan SE_M_ICY_WIND, 0
	waitbgfadein
	waitforvisualfinish
	panse SE_M_GUST, SOUND_PAN_ATTACKER, SOUND_PAN_TARGET, +2, 0
	call IcyWindSwirlingSnowballs
	delay 5
	call IcyWindSwirlingSnowballs
	playsewithpan SE_M_GUST2, SOUND_PAN_TARGET
	delay 55
	call IceSpikesEffectLong
	waitforvisualfinish
	clearmonbg ANIM_DEF_PARTNER
	restorebg
	waitbgfadeout
	createvisualtask AnimTask_BlendBattleAnimPal, 10, F_PAL_BG | F_PAL_ATK_SIDE, 4, 4, 0, RGB_BLACK
	waitbgfadein
	end

IcyWindSwirlingSnowballs:
	createsprite gSwirlingSnowballSpriteTemplate, ANIM_TARGET, 40, 0, 0, 0, 0, 72, 1
	delay 5
	createsprite gSwirlingSnowballSpriteTemplate, ANIM_TARGET, 40, 0, 10, 0, 10, 72, 1
	delay 5
	createsprite gSwirlingSnowballSpriteTemplate, ANIM_TARGET, 40, 0, -10, 0, -10, 72, 1
	delay 5
	createsprite gSwirlingSnowballSpriteTemplate, ANIM_TARGET, 40, 0, 15, 0, 15, 72, 1
	delay 5
	createsprite gSwirlingSnowballSpriteTemplate, ANIM_TARGET, 40, 0, -5, 0, -5, 72, 1
	return

Move_SMOKESCREEN:
	loadspritegfx ANIM_TAG_BLACK_SMOKE
	loadspritegfx ANIM_TAG_BLACK_BALL
	playsewithpan SE_M_DOUBLE_TEAM, SOUND_PAN_ATTACKER
	createsprite gBlackBallSpriteTemplate, ANIM_TARGET, 2, 20, 0, 0, 0, 35, -25
	waitforvisualfinish
	createvisualtask AnimTask_SmokescreenImpact, 2
	delay 2
	playsewithpan SE_M_SAND_ATTACK, SOUND_PAN_TARGET
	createsprite gBlackSmokeSpriteTemplate, ANIM_TARGET, 4, 0, -12, 104, 0, 75
	createsprite gBlackSmokeSpriteTemplate, ANIM_TARGET, 4, 0, -12, 72, 1, 75
	createsprite gBlackSmokeSpriteTemplate, ANIM_TARGET, 4, 0, -6, 56, 1, 75
	createsprite gBlackSmokeSpriteTemplate, ANIM_TARGET, 4, 0, -6, 88, 0, 75
	createsprite gBlackSmokeSpriteTemplate, ANIM_TARGET, 4, 0, 0, 56, 0, 75
	createsprite gBlackSmokeSpriteTemplate, ANIM_TARGET, 4, 0, 0, 88, 1, 75
	createsprite gBlackSmokeSpriteTemplate, ANIM_TARGET, 4, 0, 6, 72, 0, 75
	createsprite gBlackSmokeSpriteTemplate, ANIM_TARGET, 4, 0, 6, 104, 1, 75
	createsprite gBlackSmokeSpriteTemplate, ANIM_TARGET, 4, 0, 12, 72, 0, 75
	createsprite gBlackSmokeSpriteTemplate, ANIM_TARGET, 4, 0, 12, 56, 1, 75
	createsprite gBlackSmokeSpriteTemplate, ANIM_TARGET, 4, 0, 18, 80, 0, 75
	createsprite gBlackSmokeSpriteTemplate, ANIM_TARGET, 4, 0, 18, 72, 1, 75
	waitforvisualfinish
	end

Move_CONVERSION:
	loadspritegfx ANIM_TAG_CONVERSION
	monbg ANIM_ATK_PARTNER
	splitbgprio ANIM_ATTACKER
	setalpha 16, 0
	delay 0
	playsewithpan SE_M_SWIFT, SOUND_PAN_ATTACKER
	createsprite gConversionSpriteTemplate, ANIM_ATTACKER, 2, -24, -24
	delay 3
	createsprite gConversionSpriteTemplate, ANIM_ATTACKER, 2, -8, -24
	delay 3
	createsprite gConversionSpriteTemplate, ANIM_ATTACKER, 2, 8, -24
	delay 3
	createsprite gConversionSpriteTemplate, ANIM_ATTACKER, 2, 24, -24
	delay 3
	playsewithpan SE_M_SWIFT, SOUND_PAN_ATTACKER
	createsprite gConversionSpriteTemplate, ANIM_ATTACKER, 2, -24, -8
	delay 3
	createsprite gConversionSpriteTemplate, ANIM_ATTACKER, 2, -8, -8
	delay 3
	createsprite gConversionSpriteTemplate, ANIM_ATTACKER, 2, 8, -8
	delay 3
	createsprite gConversionSpriteTemplate, ANIM_ATTACKER, 2, 24, -8
	delay 3
	playsewithpan SE_M_SWIFT, SOUND_PAN_ATTACKER
	createsprite gConversionSpriteTemplate, ANIM_ATTACKER, 2, -24, 8
	delay 3
	createsprite gConversionSpriteTemplate, ANIM_ATTACKER, 2, -8, 8
	delay 3
	createsprite gConversionSpriteTemplate, ANIM_ATTACKER, 2, 8, 8
	delay 3
	createsprite gConversionSpriteTemplate, ANIM_ATTACKER, 2, 24, 8
	delay 3
	playsewithpan SE_M_SWIFT, SOUND_PAN_ATTACKER
	createsprite gConversionSpriteTemplate, ANIM_ATTACKER, 2, -24, 24
	delay 3
	createsprite gConversionSpriteTemplate, ANIM_ATTACKER, 2, -8, 24
	delay 3
	createsprite gConversionSpriteTemplate, ANIM_ATTACKER, 2, 8, 24
	delay 3
	createsprite gConversionSpriteTemplate, ANIM_ATTACKER, 2, 24, 24
	delay 20
	playsewithpan SE_M_BARRIER, SOUND_PAN_ATTACKER
	createvisualtask AnimTask_FlashAnimTagWithColor, 2, ANIM_TAG_CONVERSION, 1, 1, RGB(31, 31, 13), 12, 0, 0
	delay 6
	createvisualtask AnimTask_ConversionAlphaBlend, 5
	waitforvisualfinish
	delay 1
	clearmonbg ANIM_ATK_PARTNER
	blendoff
	end

Move_CONVERSION_2:
	loadspritegfx ANIM_TAG_CONVERSION
	monbg ANIM_DEF_PARTNER
	splitbgprio_foes ANIM_TARGET
	setalpha 0, 16
	delay 0
	playsewithpan SE_M_BARRIER, SOUND_PAN_TARGET
	createsprite gConversion2SpriteTemplate, ANIM_ATTACKER, 2, -24, -24, 60
	createsprite gConversion2SpriteTemplate, ANIM_ATTACKER, 2, -8, -24, 65
	createsprite gConversion2SpriteTemplate, ANIM_ATTACKER, 2, 8, -24, 70
	createsprite gConversion2SpriteTemplate, ANIM_ATTACKER, 2, 24, -24, 75
	createsprite gConversion2SpriteTemplate, ANIM_ATTACKER, 2, -24, -8, 80
	createsprite gConversion2SpriteTemplate, ANIM_ATTACKER, 2, -8, -8, 85
	createsprite gConversion2SpriteTemplate, ANIM_ATTACKER, 2, 8, -8, 90
	createsprite gConversion2SpriteTemplate, ANIM_ATTACKER, 2, 24, -8, 95
	createsprite gConversion2SpriteTemplate, ANIM_ATTACKER, 2, -24, 8, 100
	createsprite gConversion2SpriteTemplate, ANIM_ATTACKER, 2, -8, 8, 105
	createsprite gConversion2SpriteTemplate, ANIM_ATTACKER, 2, 8, 8, 110
	createsprite gConversion2SpriteTemplate, ANIM_ATTACKER, 2, 24, 8, 115
	createsprite gConversion2SpriteTemplate, ANIM_ATTACKER, 2, -24, 24, 120
	createsprite gConversion2SpriteTemplate, ANIM_ATTACKER, 2, -8, 24, 125
	createsprite gConversion2SpriteTemplate, ANIM_ATTACKER, 2, 8, 24, 130
	createsprite gConversion2SpriteTemplate, ANIM_ATTACKER, 2, 24, 24, 135
	createvisualtask AnimTask_Conversion2AlphaBlend, 5
	delay 60
	playsewithpan SE_M_SWIFT, SOUND_PAN_TARGET
	delay 10
	playsewithpan SE_M_SWIFT, SOUND_PAN_TARGET
	delay 10
	playsewithpan SE_M_SWIFT, SOUND_PAN_TARGET
	delay 10
	playsewithpan SE_M_SWIFT, SOUND_PAN_TARGET
	delay 10
	playsewithpan SE_M_SWIFT, SOUND_PAN_TARGET
	delay 10
	playsewithpan SE_M_SWIFT, SOUND_PAN_TARGET
	delay 10
	playsewithpan SE_M_SWIFT, SOUND_PAN_TARGET
	delay 10
	playsewithpan SE_M_SWIFT, SOUND_PAN_TARGET
	waitforvisualfinish
	clearmonbg ANIM_DEF_PARTNER
	blendoff
	end

Move_ROLLING_KICK:
	loadspritegfx ANIM_TAG_HANDS_AND_FEET
	loadspritegfx ANIM_TAG_IMPACT
	monbg ANIM_TARGET
	setalpha 12, 8
	createvisualtask AnimTask_TranslateMonEllipticalRespectSide, 2, ANIM_ATTACKER, 18, 6, 1, 4
	playsewithpan SE_M_DOUBLE_TEAM, SOUND_PAN_ATTACKER
	delay 6
	playsewithpan SE_M_DOUBLE_TEAM, SOUND_PAN_ATTACKER
	waitforvisualfinish
	createsprite gSlideMonToOffsetSpriteTemplate, ANIM_ATTACKER, 2, 0, 20, 0, 0, 4
	createsprite gSlidingKickSpriteTemplate, ANIM_ATTACKER, 2, -24, 0, 48, 10, 160, 0
	delay 5
	playsewithpan SE_M_VITAL_THROW2, SOUND_PAN_TARGET
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 2, -8, 0, ANIM_TARGET, 2
	createvisualtask AnimTask_ShakeMon, 2, ANIM_TARGET, 5, 0, 6, 1
	waitforvisualfinish
	createsprite gSlideMonToOriginalPosSpriteTemplate, ANIM_ATTACKER, 2, 0, 1, 8
	clearmonbg ANIM_TARGET
	blendoff
	end

Move_HEADBUTT:
	loadspritegfx ANIM_TAG_IMPACT
	createsprite gBowMonSpriteTemplate, ANIM_ATTACKER, 2, 0
	playsewithpan SE_M_HEADBUTT, SOUND_PAN_ATTACKER
	waitforvisualfinish
	delay 2
	createsprite gBowMonSpriteTemplate, ANIM_ATTACKER, 2, 1
	waitforvisualfinish
	createvisualtask AnimTask_ShakeMonInPlace, 2, ANIM_ATTACKER, 2, 0, 4, 1
	createvisualtask AnimTask_ShakeMon, 2, ANIM_TARGET, 5, 0, 6, 1
	createsprite gBowMonSpriteTemplate, ANIM_ATTACKER, 2, 2
	createsprite gFlashingHitSplatSpriteTemplate, ANIM_TARGET, 3, 0, 0, ANIM_TARGET, 1
	playsewithpan SE_M_VITAL_THROW2, SOUND_PAN_TARGET
	waitforvisualfinish
	end

Move_HORN_ATTACK:
	loadspritegfx ANIM_TAG_IMPACT
	loadspritegfx ANIM_TAG_HORN_HIT
	createsprite gBowMonSpriteTemplate, ANIM_ATTACKER, 2, 0
	playsewithpan SE_M_HEADBUTT, SOUND_PAN_ATTACKER
	waitforvisualfinish
	delay 2
	createsprite gBowMonSpriteTemplate, ANIM_ATTACKER, 2, 1
	createsprite gHornHitSpriteTemplate, ANIM_TARGET, 4, 0, 0, 10
	waitforvisualfinish
	createvisualtask AnimTask_ShakeMonInPlace, 2, ANIM_ATTACKER, 2, 0, 4, 1
	createvisualtask AnimTask_ShakeMon, 2, ANIM_TARGET, 5, 0, 6, 1
	createsprite gBowMonSpriteTemplate, ANIM_ATTACKER, 2, 2
	createsprite gFlashingHitSplatSpriteTemplate, ANIM_TARGET, 3, 0, 0, ANIM_TARGET, 1
	playsewithpan SE_M_HORN_ATTACK, SOUND_PAN_TARGET
	waitforvisualfinish
	end

Move_FURY_ATTACK:
	loadspritegfx ANIM_TAG_IMPACT
	loadspritegfx ANIM_TAG_HORN_HIT
	createvisualtask AnimTask_RotateMonSpriteToSide, 2, 4, 256, ANIM_ATTACKER, 2
	choosetwoturnanim FuryAttackRight, FuryAttackLeft

FuryAttackContinue:
	createvisualtask AnimTask_ShakeMon, 2, ANIM_TARGET, 5, 0, 6, 1
	waitforvisualfinish
	end

FuryAttackRight:
	createsprite gHornHitSpriteTemplate, ANIM_TARGET, 4, 8, 8, 10
	waitforvisualfinish
	createsprite gFlashingHitSplatSpriteTemplate, ANIM_TARGET, 3, 0, 0, ANIM_TARGET, 1
	playsewithpan SE_M_HORN_ATTACK, SOUND_PAN_TARGET
	goto FuryAttackContinue

FuryAttackLeft:
	createsprite gHornHitSpriteTemplate, ANIM_TARGET, 4, -8, -8, 10
	waitforvisualfinish
	createsprite gFlashingHitSplatSpriteTemplate, ANIM_TARGET, 3, 0, 0, ANIM_TARGET, 1
	playsewithpan SE_M_HORN_ATTACK, SOUND_PAN_TARGET
	goto FuryAttackContinue

Move_HORN_DRILL:
	loadspritegfx ANIM_TAG_IMPACT
	loadspritegfx ANIM_TAG_HORN_HIT
	jumpifcontest HornDrillInContest
	fadetobg BG_DRILL
	waitbgfadeout
	createvisualtask AnimTask_StartSlidingBg, 5, -2304, 768, 1, -1
HornDrillContinue:
	waitbgfadein
	setalpha 12, 8
	createsprite gBowMonSpriteTemplate, ANIM_ATTACKER, 2, 0
	playsewithpan SE_M_HEADBUTT, SOUND_PAN_ATTACKER
	waitforvisualfinish
	delay 2
	createsprite gBowMonSpriteTemplate, ANIM_ATTACKER, 2, 1
	createsprite gHornHitSpriteTemplate, ANIM_TARGET, 4, 0, 0, 12
	waitforvisualfinish
	playse SE_BANG
	createvisualtask AnimTask_ShakeMonInPlace, 2, ANIM_ATTACKER, 2, 0, 40, 1
	createvisualtask AnimTask_ShakeMonInPlace, 2, ANIM_TARGET, 10, 0, 40, 1
	createsprite gFlashingHitSplatSpriteTemplate, ANIM_TARGET, 3, 0, 0, ANIM_TARGET, 3
	playsewithpan SE_M_HORN_ATTACK, SOUND_PAN_TARGET
	delay 4
	createsprite gFlashingHitSplatSpriteTemplate, ANIM_TARGET, 3, 0, 2, ANIM_TARGET, 3
	playsewithpan SE_M_HORN_ATTACK, SOUND_PAN_TARGET
	delay 4
	createsprite gFlashingHitSplatSpriteTemplate, ANIM_TARGET, 3, -4, 3, ANIM_TARGET, 3
	playsewithpan SE_M_HORN_ATTACK, SOUND_PAN_TARGET
	delay 4
	createsprite gFlashingHitSplatSpriteTemplate, ANIM_TARGET, 3, -8, -5, ANIM_TARGET, 3
	playsewithpan SE_M_HORN_ATTACK, SOUND_PAN_TARGET
	delay 4
	createsprite gFlashingHitSplatSpriteTemplate, ANIM_TARGET, 3, 4, -12, ANIM_TARGET, 3
	playsewithpan SE_M_HORN_ATTACK, SOUND_PAN_TARGET
	delay 4
	createsprite gFlashingHitSplatSpriteTemplate, ANIM_TARGET, 3, 16, 0, ANIM_TARGET, 3
	playsewithpan SE_M_HORN_ATTACK, SOUND_PAN_TARGET
	delay 4
	createsprite gFlashingHitSplatSpriteTemplate, ANIM_TARGET, 3, 5, 18, ANIM_TARGET, 3
	playsewithpan SE_M_HORN_ATTACK, SOUND_PAN_TARGET
	delay 4
	createsprite gFlashingHitSplatSpriteTemplate, ANIM_TARGET, 3, -17, 12, ANIM_TARGET, 2
	playsewithpan SE_M_HORN_ATTACK, SOUND_PAN_TARGET
	delay 4
	createsprite gFlashingHitSplatSpriteTemplate, ANIM_TARGET, 3, -21, -15, ANIM_TARGET, 2
	playsewithpan SE_M_HORN_ATTACK, SOUND_PAN_TARGET
	delay 4
	createsprite gFlashingHitSplatSpriteTemplate, ANIM_TARGET, 3, 8, -27, ANIM_TARGET, 2
	playsewithpan SE_M_HORN_ATTACK, SOUND_PAN_TARGET
	delay 4
	createsprite gFlashingHitSplatSpriteTemplate, ANIM_TARGET, 3, 32, 0, ANIM_TARGET, 2
	playsewithpan SE_M_HORN_ATTACK, SOUND_PAN_TARGET
	delay 4
	createsprite gBowMonSpriteTemplate, ANIM_ATTACKER, 2, 2
	waitforvisualfinish
	restorebg
	waitbgfadeout
	setarg 7, 0xFFFF
	waitbgfadein
	end

HornDrillInContest:
	fadetobg BG_DRILL_CONTESTS
	waitbgfadeout
	createvisualtask AnimTask_StartSlidingBg, 5, 2304, 768, 0, -1
	goto HornDrillContinue

Move_THRASH:
	loadspritegfx ANIM_TAG_IMPACT
	loadspritegfx ANIM_TAG_HANDS_AND_FEET
	createvisualtask AnimTask_ThrashMoveMonHorizontal, 2
	createvisualtask AnimTask_ThrashMoveMonVertical, 2
	createsprite gFistFootRandomPosSpriteTemplate, ANIM_TARGET, 3, 1, 10, 0
	createvisualtask AnimTask_ShakeMonInPlace, 2, ANIM_TARGET, 4, 0, 7, 1
	playsewithpan SE_M_COMET_PUNCH, SOUND_PAN_TARGET
	delay 28
	createsprite gFistFootRandomPosSpriteTemplate, ANIM_TARGET, 3, 1, 10, 1
	createvisualtask AnimTask_ShakeMonInPlace, 2, ANIM_TARGET, 4, 0, 7, 1
	playsewithpan SE_M_VITAL_THROW2, SOUND_PAN_TARGET
	delay 28
	createsprite gFistFootRandomPosSpriteTemplate, ANIM_TARGET, 3, 1, 10, 3
	createvisualtask AnimTask_ShakeMonInPlace, 2, ANIM_TARGET, 8, 0, 16, 1
	playsewithpan SE_M_MEGA_KICK2, SOUND_PAN_TARGET
	end

Move_SING:
	loadspritegfx ANIM_TAG_MUSIC_NOTES
	monbg ANIM_DEF_PARTNER
	createvisualtask AnimTask_MusicNotesRainbowBlend, 2
	waitforvisualfinish
	panse SE_M_SING, SOUND_PAN_ATTACKER, SOUND_PAN_TARGET, +2, 0
	createsprite gWavyMusicNotesSpriteTemplate, ANIM_TARGET, 2, 7, 0, 12
	delay 5
	createsprite gWavyMusicNotesSpriteTemplate, ANIM_TARGET, 2, 6, 1, 12
	delay 5
	createsprite gWavyMusicNotesSpriteTemplate, ANIM_TARGET, 2, 1, 2, 12
	delay 5
	createsprite gWavyMusicNotesSpriteTemplate, ANIM_TARGET, 2, 2, 3, 12
	delay 5
	createsprite gWavyMusicNotesSpriteTemplate, ANIM_TARGET, 2, 3, 0, 12
	delay 4
	createsprite gWavyMusicNotesSpriteTemplate, ANIM_TARGET, 2, 2, 1, 12
	delay 4
	createsprite gWavyMusicNotesSpriteTemplate, ANIM_TARGET, 2, 5, 2, 12
	delay 4
	createsprite gWavyMusicNotesSpriteTemplate, ANIM_TARGET, 2, 6, 3, 12
	delay 4
	createsprite gWavyMusicNotesSpriteTemplate, ANIM_TARGET, 2, 2, 0, 12
	delay 4
	createsprite gWavyMusicNotesSpriteTemplate, ANIM_TARGET, 2, 2, 1, 12
	delay 4
	createsprite gWavyMusicNotesSpriteTemplate, ANIM_TARGET, 2, 1, 2, 12
	delay 4
	createsprite gWavyMusicNotesSpriteTemplate, ANIM_TARGET, 2, 5, 3, 12
	delay 4
	waitforvisualfinish
	clearmonbg ANIM_DEF_PARTNER
	createvisualtask AnimTask_MusicNotesClearRainbowBlend, 2
	waitforvisualfinish
	end

Move_LOW_KICK:
	loadspritegfx ANIM_TAG_HANDS_AND_FEET
	loadspritegfx ANIM_TAG_IMPACT
	createsprite gSlideMonToOffsetSpriteTemplate, ANIM_ATTACKER, 2, 0, 20, 0, 0, 4
	createsprite gSlidingKickSpriteTemplate, ANIM_TARGET, 2, -24, 28, 40, 8, 160, 0
	delay 4
	createsprite gBasicHitSplatSpriteTemplate, ANIM_TARGET, 2, -8, 8, ANIM_TARGET, 2
	createvisualtask AnimTask_RotateMonSpriteToSide, 2, 6, 384, ANIM_TARGET, 2
	playsewithpan SE_M_VITAL_THROW2, SOUND_PAN_TARGET
	waitforvisualfinish
	createsprite gSlideMonToOriginalPosSpriteTemplate, ANIM_ATTACKER, 2, 0, 1, 4
	end

Move_EARTHQUAKE:
	createvisualtask AnimTask_HorizontalShake, 5, (MAX_BATTLERS_COUNT + 1), 10, 50
	createvisualtask AnimTask_HorizontalShake, 5, MAX_BATTLERS_COUNT, 10, 50
	playsewithpan SE_M_EARTHQUAKE, 0
	delay 10
	createsprite gComplexPaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG, 3, 1, RGB_BLACK, 14, RGB_WHITE, 14
	delay 16
	createsprite gComplexPaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG, 3, 1, RGB_BLACK, 14, RGB_WHITE, 14
	end

Move_FISSURE:
	loadspritegfx ANIM_TAG_MUD_SAND
	createvisualtask AnimTask_HorizontalShake, 3, (MAX_BATTLERS_COUNT + 1), 10, 50
	createvisualtask AnimTask_HorizontalShake, 3, ANIM_TARGET, 10, 50
	playsewithpan SE_M_EARTHQUAKE, SOUND_PAN_TARGET
	delay 8
	call FissureDirtPlumeFar
	delay 15
	createsprite gComplexPaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG, 3, 1, RGB_BLACK, 14, RGB_WHITE, 14
	delay 15
	call FissureDirtPlumeClose
	delay 15
	createsprite gComplexPaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG, 3, 1, RGB_BLACK, 14, RGB_WHITE, 14
	delay 15
	call FissureDirtPlumeFar
	delay 50
	fadetobg BG_FISSURE
	waitbgfadeout
	createvisualtask AnimTask_PositionFissureBgOnBattler, 5, ANIM_TARGET, 5, -1
	waitbgfadein
	delay 40
	restorebg
	waitbgfadeout
	setarg 7, -1
	waitbgfadein
	end

FissureDirtPlumeFar:
	createsprite gDirtPlumeSpriteTemplate, ANIM_TARGET, 2, 1, 0, 12, -48, -16, 24
	createsprite gDirtPlumeSpriteTemplate, ANIM_TARGET, 2, 1, 0, 16, -16, -10, 24
	createsprite gDirtPlumeSpriteTemplate, ANIM_TARGET, 2, 1, 1, 14, -52, -18, 24
	createsprite gDirtPlumeSpriteTemplate, ANIM_TARGET, 2, 1, 1, 12, -32, -16, 24
	playsewithpan SE_M_DIG, SOUND_PAN_TARGET
	return

FissureDirtPlumeClose:
	createsprite gDirtPlumeSpriteTemplate, ANIM_TARGET, 2, 1, 0, 12, -24, -16, 24
	createsprite gDirtPlumeSpriteTemplate, ANIM_TARGET, 2, 1, 0, 16, -38, -10, 24
	createsprite gDirtPlumeSpriteTemplate, ANIM_TARGET, 2, 1, 1, 14, -20, -18, 24
	createsprite gDirtPlumeSpriteTemplate, ANIM_TARGET, 2, 1, 1, 12, -36, -16, 24
	playsewithpan SE_M_DIG, SOUND_PAN_TARGET
	return

Move_DIG:
	choosetwoturnanim DigSetUp, DigUnleash
DigEnd:
	end

DigSetUp:
	loadspritegfx ANIM_TAG_MUD_SAND
	loadspritegfx ANIM_TAG_DIRT_MOUND
	createsprite gDirtMoundSpriteTemplate, ANIM_ATTACKER, 1, 0, 0, 180
	createsprite gDirtMoundSpriteTemplate, ANIM_ATTACKER, 1, 0, 1, 180
	monbg_static ANIM_ATTACKER
	delay 1
	createvisualtask AnimTask_DigDownMovement, 2, FALSE
	delay 6
	call DigThrowDirt
	call DigThrowDirt
	call DigThrowDirt
	call DigThrowDirt
	call DigThrowDirt
	waitforvisualfinish
	clearmonbg_static ANIM_ATTACKER
	delay 1
	createvisualtask AnimTask_DigDownMovement, 2, TRUE
	goto DigEnd

DigUnleash:
	loadspritegfx ANIM_TAG_IMPACT
	loadspritegfx ANIM_TAG_DIRT_MOUND
	createvisualtask AnimTask_DigUpMovement, 2, FALSE
	waitforvisualfinish
	monbg ANIM_ATTACKER
	createsprite gDirtMoundSpriteTemplate, ANIM_ATTACKER, 1, 0, 0, 48
	createsprite gDirtMoundSpriteTemplate, ANIM_ATTACKER, 1, 0, 1, 48
	delay 1
	createvisualtask AnimTask_DigUpMovement, 2, TRUE
	delay 16
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 2, -8, 0, ANIM_TARGET, 2
	createvisualtask AnimTask_ShakeMon, 2, ANIM_TARGET, 5, 0, 6, 1
	playsewithpan SE_M_MEGA_KICK2, SOUND_PAN_ATTACKER
	clearmonbg ANIM_ATTACKER
	goto DigEnd

DigThrowDirt:
	createsprite gDirtPlumeSpriteTemplate, ANIM_ATTACKER, 2, 0, 0, 12, 4, -16, 18
	createsprite gDirtPlumeSpriteTemplate, ANIM_ATTACKER, 2, 0, 0, 16, 4, -10, 18
	createsprite gDirtPlumeSpriteTemplate, ANIM_ATTACKER, 2, 0, 1, 14, 4, -18, 18
	createsprite gDirtPlumeSpriteTemplate, ANIM_ATTACKER, 2, 0, 1, 12, 4, -16, 18
	playsewithpan SE_M_DIG, SOUND_PAN_ATTACKER
	delay 32
	return

Move_MEDITATE:
	call SetPsychicBackground
	createvisualtask AnimTask_MeditateStretchAttacker, 2
	playsewithpan SE_M_HEADBUTT, SOUND_PAN_ATTACKER
	delay 16
	playsewithpan SE_M_TAKE_DOWN, SOUND_PAN_ATTACKER
	waitforvisualfinish
	call UnsetPsychicBackground
	end

Move_AGILITY:
	monbg ANIM_ATK_PARTNER
	setalpha 12, 8
	createvisualtask AnimTask_TranslateMonEllipticalRespectSide, 2, ANIM_ATTACKER, 24, 6, 4, 4
	createvisualtask AnimTask_TraceMonBlended, 2, 0, 4, 7, 10
	playsewithpan SE_M_DOUBLE_TEAM, SOUND_PAN_ATTACKER
	delay 12
	playsewithpan SE_M_DOUBLE_TEAM, SOUND_PAN_ATTACKER
	delay 12
	playsewithpan SE_M_DOUBLE_TEAM, SOUND_PAN_ATTACKER
	delay 12
	playsewithpan SE_M_DOUBLE_TEAM, SOUND_PAN_ATTACKER
	delay 12
	playsewithpan SE_M_DOUBLE_TEAM, SOUND_PAN_ATTACKER
	delay 12
	waitforvisualfinish
	clearmonbg ANIM_ATK_PARTNER
	blendoff
	delay 1
	end

Move_QUICK_ATTACK:
	loadspritegfx ANIM_TAG_IMPACT
	monbg ANIM_ATK_PARTNER
	setalpha 12, 8
	createvisualtask AnimTask_TranslateMonEllipticalRespectSide, 2, ANIM_ATTACKER, 24, 6, 1, 5
	createvisualtask AnimTask_TraceMonBlended, 2, 0, 4, 7, 3
	playsewithpan SE_M_JUMP_KICK, SOUND_PAN_ATTACKER
	delay 4
	createvisualtask AnimTask_ShakeMon, 2, ANIM_TARGET, 5, 0, 6, 1
	createsprite gBasicHitSplatSpriteTemplate, ANIM_TARGET, 4, 0, 0, ANIM_TARGET, 1
	playsewithpan SE_M_VITAL_THROW2, SOUND_PAN_TARGET
	waitforvisualfinish
	clearmonbg ANIM_ATK_PARTNER
	blendoff
	waitforvisualfinish
	end

Move_RAGE:
	loadspritegfx ANIM_TAG_IMPACT
	loadspritegfx ANIM_TAG_ANGER
	monbg ANIM_TARGET
	setalpha 12, 8
	createvisualtask AnimTask_BlendMonInAndOut, 3, ANIM_ATTACKER, RGB_RED, 10, 0, 2
	createsprite gAngerMarkSpriteTemplate, ANIM_ATTACKER, 2, 0, -20, -28
	playsewithpan SE_M_SWAGGER2, SOUND_PAN_ATTACKER
	delay 20
	createsprite gAngerMarkSpriteTemplate, ANIM_ATTACKER, 2, 0, 20, -28
	playsewithpan SE_M_SWAGGER2, SOUND_PAN_ATTACKER
	waitforvisualfinish
	createsprite gHorizontalLungeSpriteTemplate, ANIM_ATTACKER, 2, 4, 6
	delay 4
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 2, 0, 0, ANIM_TARGET, 2
	createvisualtask AnimTask_ShakeTargetBasedOnMovePowerOrDmg, 2, TRUE, 1, 10, 1, 0
	playsewithpan SE_M_VITAL_THROW2, SOUND_PAN_TARGET
	waitforvisualfinish
	clearmonbg ANIM_TARGET
	end

Move_TELEPORT:
	call SetPsychicBackground
	createvisualtask AnimTask_Teleport, 2
	playsewithpan SE_M_TELEPORT, SOUND_PAN_ATTACKER
	delay 15
	call UnsetPsychicBackground
	waitforvisualfinish
	end

Move_DOUBLE_TEAM:
	monbg ANIM_ATK_PARTNER
	setalpha 12, 8
	createvisualtask AnimTask_DoubleTeam, 2
	playsewithpan SE_M_DOUBLE_TEAM, SOUND_PAN_ATTACKER
	delay 32
	playsewithpan SE_M_DOUBLE_TEAM, SOUND_PAN_ATTACKER
	delay 24
	playsewithpan SE_M_DOUBLE_TEAM, SOUND_PAN_ATTACKER
	delay 16
	playsewithpan SE_M_DOUBLE_TEAM, SOUND_PAN_ATTACKER
	delay 8
	playsewithpan SE_M_DOUBLE_TEAM, SOUND_PAN_ATTACKER
	delay 8
	playsewithpan SE_M_DOUBLE_TEAM, SOUND_PAN_ATTACKER
	delay 8
	playsewithpan SE_M_DOUBLE_TEAM, SOUND_PAN_ATTACKER
	delay 8
	playsewithpan SE_M_DOUBLE_TEAM, SOUND_PAN_ATTACKER
	delay 8
	playsewithpan SE_M_DOUBLE_TEAM, SOUND_PAN_ATTACKER
	waitforvisualfinish
	clearmonbg ANIM_ATK_PARTNER
	blendoff
	delay 1
	end

Move_MINIMIZE:
	setalpha 10, 8
	createvisualtask AnimTask_Minimize, 2
	loopsewithpan SE_M_MINIMIZE, SOUND_PAN_ATTACKER, 34, 3
	waitforvisualfinish
	blendoff
	end

Move_METRONOME:
	loadspritegfx ANIM_TAG_FINGER
	loadspritegfx ANIM_TAG_THOUGHT_BUBBLE
	createsprite gThoughtBubbleSpriteTemplate, ANIM_ATTACKER, 11, 0, 100
	playsewithpan SE_M_METRONOME, SOUND_PAN_ATTACKER
	delay 6
	createsprite gMetronomeFingerSpriteTemplate, ANIM_ATTACKER, 12, 0
	delay 24
	loopsewithpan SE_M_TAIL_WHIP, SOUND_PAN_ATTACKER, 22, 3
	waitforvisualfinish
	end

Move_SKULL_BASH:
	choosetwoturnanim SkullBashSetUp, SkullBashAttack
SkullBashEnd:
	end

SkullBashSetUp:
	call SkullBashSetUpHeadDown
	call SkullBashSetUpHeadDown
	waitforvisualfinish
	goto SkullBashEnd

SkullBashSetUpHeadDown:
	createsprite gSlideMonToOffsetAndBackSpriteTemplate, ANIM_ATTACKER, 2, ANIM_ATTACKER, -24, 0, 0, 10, 0
	playsewithpan SE_M_TAKE_DOWN, SOUND_PAN_ATTACKER
	waitforvisualfinish
	createvisualtask AnimTask_RotateMonSpriteToSide, 2, 16, 96, ANIM_ATTACKER, 2
	waitforvisualfinish
	createsprite gSlideMonToOffsetAndBackSpriteTemplate, ANIM_ATTACKER, 2, ANIM_ATTACKER, 24, 0, 0, 10, 1
	waitforvisualfinish
	return

SkullBashAttack:
	loadspritegfx ANIM_TAG_IMPACT
	createvisualtask AnimTask_SkullBashPosition, 2, 0
	playsewithpan SE_M_TAKE_DOWN, SOUND_PAN_ATTACKER
	waitforvisualfinish
	playse SE_BANG
	createsprite gComplexPaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG, 3, 1, RGB_BLACK, 14, RGB_WHITE, 14
	createvisualtask AnimTask_ShakeMonInPlace, 2, ANIM_ATTACKER, 2, 0, 40, 1
	createvisualtask AnimTask_ShakeMonInPlace, 2, ANIM_TARGET, 10, 0, 40, 1
	createsprite gFlashingHitSplatSpriteTemplate, ANIM_TARGET, 4, 0, 0, ANIM_TARGET, 0
	loopsewithpan SE_M_MEGA_KICK2, SOUND_PAN_TARGET, 8, 3
	waitforvisualfinish
	createvisualtask AnimTask_SkullBashPosition, 2, 1
	goto SkullBashEnd

Move_AMNESIA:
	loadspritegfx ANIM_TAG_AMNESIA
	call SetPsychicBackground
	delay 8
	createsprite gQuestionMarkSpriteTemplate, ANIM_ATTACKER, 20
	playsewithpan SE_M_METRONOME, SOUND_PAN_ATTACKER
	delay 54
	loopsewithpan SE_M_METRONOME, SOUND_PAN_ATTACKER, 16, 3
	waitforvisualfinish
	call UnsetPsychicBackground
	end

Move_KINESIS:
	loadspritegfx ANIM_TAG_ALERT
	loadspritegfx ANIM_TAG_BENT_SPOON
	playsewithpan SE_M_PSYBEAM, SOUND_PAN_ATTACKER
	call SetPsychicBackground
	createsprite gBentSpoonSpriteTemplate, ANIM_ATTACKER, 20
	createsprite gKinesisZapEnergySpriteTemplate, ANIM_ATTACKER, 19, 32, -8, 0
	createsprite gKinesisZapEnergySpriteTemplate, ANIM_ATTACKER, 19, 32, 16, 1
	loopsewithpan SE_M_CONFUSE_RAY, SOUND_PAN_ATTACKER, 21, 2
	delay 60
	playsewithpan SE_M_DIZZY_PUNCH, SOUND_PAN_ATTACKER
	delay 30
	loopsewithpan SE_M_DIZZY_PUNCH, SOUND_PAN_ATTACKER, 20, 2
	delay 70
	playsewithpan SE_M_SWAGGER2, SOUND_PAN_ATTACKER
	waitforvisualfinish
	call UnsetPsychicBackground
	end

Move_GLARE:
	loadspritegfx ANIM_TAG_SMALL_RED_EYE
	loadspritegfx ANIM_TAG_EYE_SPARKLE
	createvisualtask AnimTask_GlareEyeDots, 5, 0
	playsewithpan SE_M_PSYBEAM2, SOUND_PAN_ATTACKER
	waitforvisualfinish
	createvisualtask AnimTask_BlendBattleAnimPal, 5, F_PAL_BG, 0, 0, 16, RGB_BLACK
	waitforvisualfinish
	createsprite gEyeSparkleSpriteTemplate, ANIM_ATTACKER, 0, -16, -8
	createsprite gEyeSparkleSpriteTemplate, ANIM_ATTACKER, 0, 16, -8
	createvisualtask AnimTask_ScaryFace, 5
	playsewithpan SE_M_LEER, SOUND_PAN_ATTACKER
	delay 2
	createvisualtask AnimTask_ShakeTargetInPattern, 3, 20, 1, FALSE
	waitforvisualfinish
	createvisualtask AnimTask_BlendBattleAnimPal, 5, F_PAL_BG, 0, 16, 0, RGB_BLACK
	end

Move_BARRAGE:
	loadspritegfx ANIM_TAG_RED_BALL
	createvisualtask AnimTask_BarrageBall, 3
	playsewithpan SE_M_SWAGGER, SOUND_PAN_ATTACKER
	delay 24
	createsprite gShakeMonOrTerrainSpriteTemplate, ANIM_ATTACKER, 2, 8, 1, 40, 1
	createvisualtask AnimTask_ShakeMon, 3, ANIM_TARGET, 0, 4, 20, 1
	createvisualtask AnimTask_ShakeMon, 3, ANIM_DEF_PARTNER, 0, 4, 20, 1
	loopsewithpan SE_M_STRENGTH, SOUND_PAN_TARGET, 8, 2
	end

Move_SKY_ATTACK:
	choosetwoturnanim SkyAttackSetUp, SkyAttackUnleash
SkyAttackEnd:
	end

SkyAttackSetUp:
	monbg ANIM_DEF_PARTNER
	setalpha 12, 11
	createvisualtask AnimTask_GetTargetIsAttackerPartner, 5, ARG_RET_ID
	jumpretfalse SkyAttackSetUpAgainstOpponent
	goto SkyAttackSetUpAgainstPartner

SkyAttackSetUpAgainstOpponent:
	createvisualtask AnimTask_BlendBattleAnimPal, 10, F_PAL_BG | F_PAL_ATK_SIDE | F_PAL_DEF_PARTNER, 1, 0, 12, RGB_BLACK
	waitforvisualfinish
	delay 12
	createvisualtask AnimTask_BlendBattleAnimPal, 10, F_PAL_ATTACKER, 1, 8, 0, RGB_BLACK
	createvisualtask AnimTask_HorizontalShake, 5, ANIM_ATTACKER, 2, 16
	loopsewithpan SE_M_STAT_INCREASE, SOUND_PAN_ATTACKER, 4, 8
	createvisualtask AnimTask_BlendBattleAnimPal, 10, F_PAL_ATTACKER, 1, 0, 15, RGB_WHITE
	delay 20
	createvisualtask AnimTask_BlendBattleAnimPal, 10, F_PAL_ATTACKER, 1, 15, 0, RGB_WHITE
	waitforvisualfinish
	createvisualtask AnimTask_BlendBattleAnimPal, 10, F_PAL_BG | F_PAL_ATK_PARTNER | F_PAL_DEF_PARTNER, 1, 8, 0, RGB_BLACK
	waitforvisualfinish
	clearmonbg ANIM_DEF_PARTNER
	blendoff
	goto SkyAttackEnd

SkyAttackSetUpAgainstPartner:
	createvisualtask AnimTask_BlendBattleAnimPalExclude, 10, ANIM_TARGET, 1, 0, 12, RGB_BLACK
	waitforvisualfinish
	delay 12
	createvisualtask AnimTask_BlendBattleAnimPal, 10, F_PAL_ATTACKER, 1, 8, 0, RGB_BLACK
	createvisualtask AnimTask_HorizontalShake, 5, ANIM_ATTACKER, 2, 16
	playsewithpan SE_M_STAT_INCREASE, SOUND_PAN_ATTACKER
	delay 8
	createvisualtask AnimTask_BlendBattleAnimPal, 10, F_PAL_ATTACKER, 1, 0, 15, RGB_WHITE
	delay 20
	createvisualtask AnimTask_BlendBattleAnimPal, 10, F_PAL_ATTACKER, 1, 15, 0, RGB_WHITE
	waitforvisualfinish
	createvisualtask AnimTask_BlendBattleAnimPalExclude, 10, 4, 1, 8, 0, RGB_BLACK
	waitforvisualfinish
	clearmonbg ANIM_DEF_PARTNER
	blendoff
	goto SkyAttackEnd

SkyAttackUnleash:
	loadspritegfx ANIM_TAG_IMPACT
	loadspritegfx ANIM_TAG_BIRD
	call SetSkyBg
	monbg ANIM_ATTACKER
	createvisualtask AnimTask_BlendBattleAnimPal, 10, F_PAL_ATTACKER, 0, 0, 16, RGB_WHITE
	delay 4
	createvisualtask AnimTask_AttackerFadeToInvisible, 5, 0
	waitforvisualfinish
	createvisualtask SoundTask_PlaySE2WithPanning, 5, SE_M_SKY_UPPERCUT, SOUND_PAN_ATTACKER
	createsprite gSkyAttackBirdSpriteTemplate, ANIM_TARGET, 2
	delay 14
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_TARGET, 10, 0, 18, 1
	createvisualtask SoundTask_PlaySE1WithPanning, 5, SE_M_MEGA_KICK2, SOUND_PAN_TARGET
	delay 20
	createvisualtask AnimTask_AttackerFadeFromInvisible, 5, 1
	delay 2
	createvisualtask AnimTask_BlendBattleAnimPal, 10, F_PAL_ATTACKER, 0, 15, 0, RGB_WHITE
	waitforvisualfinish
	clearmonbg ANIM_ATTACKER
	call UnsetSkyBg
	goto SkyAttackEnd

Move_FLASH:
	playsewithpan SE_M_LEER, SOUND_PAN_ATTACKER
	createvisualtask AnimTask_Flash, 2
	waitforvisualfinish
	end

Move_SPLASH:
	createvisualtask AnimTask_Splash, 2, 0, 3
	delay 8
	loopsewithpan SE_M_TAIL_WHIP, SOUND_PAN_ATTACKER, 38, 3
	waitforvisualfinish
	end

Move_ACID_ARMOR:
	monbg ANIM_ATTACKER
	setalpha 15, 0
	createvisualtask AnimTask_AcidArmor, 2, ANIM_ATTACKER
	playsewithpan SE_M_ACID_ARMOR, SOUND_PAN_ATTACKER
	waitforvisualfinish
	blendoff
	clearmonbg ANIM_ATTACKER
	delay 1
	end

Move_SHARPEN:
	loadspritegfx ANIM_TAG_SPHERE_TO_CUBE
	createsprite gSharpenSphereSpriteTemplate, ANIM_ATTACKER, 2
	waitforvisualfinish
	end

Move_SUPER_FANG:
	loadspritegfx ANIM_TAG_FANG_ATTACK
	createvisualtask AnimTask_ShakeMonInPlace, 2, ANIM_ATTACKER, 1, 0, 20, 1
	playsewithpan SE_M_DRAGON_RAGE, SOUND_PAN_ATTACKER
	waitforvisualfinish
	createvisualtask AnimTask_ShakeMonInPlace, 2, ANIM_ATTACKER, 3, 0, 48, 1
	createvisualtask AnimTask_BlendMonInAndOut, 2, ANIM_ATTACKER, RGB(31, 6, 1), 12, 4, 1
	waitforvisualfinish
	delay 20
	createsprite gHorizontalLungeSpriteTemplate, ANIM_ATTACKER, 2, 4, 4
	delay 4
	createsprite gSuperFangSpriteTemplate, ANIM_TARGET, 2
	playsewithpan SE_M_BITE, SOUND_PAN_TARGET
	delay 8
	createsprite gComplexPaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG, 3, 1, RGB(31, 2, 2), 14, RGB_WHITE, 14
	createvisualtask AnimTask_ShakeMon, 2, ANIM_TARGET, 0, 7, 12, 1
	waitforvisualfinish
	blendoff
	end

Move_SLASH:
	loadspritegfx ANIM_TAG_SLASH
	createsprite gSlashSliceSpriteTemplate, ANIM_TARGET, 2, 1, -8, 0
	playsewithpan SE_M_RAZOR_WIND, SOUND_PAN_TARGET
	delay 4
	createsprite gSlashSliceSpriteTemplate, ANIM_TARGET, 2, 1, 8, 0
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_TARGET, 4, 0, 18, 1
	playsewithpan SE_M_RAZOR_WIND, SOUND_PAN_TARGET
	waitforvisualfinish
	end

Move_STRUGGLE:
	loadspritegfx ANIM_TAG_IMPACT
	loadspritegfx ANIM_TAG_MOVEMENT_WAVES
	monbg ANIM_TARGET
	setalpha 12, 8
	createvisualtask AnimTask_ShakeMonInPlace, 2, ANIM_ATTACKER, 3, 0, 12, 4
	createsprite gMovementWavesSpriteTemplate, ANIM_ATTACKER, 2, 0, 0, 2
	createsprite gMovementWavesSpriteTemplate, ANIM_ATTACKER, 2, 0, 1, 2
	loopsewithpan SE_M_HEADBUTT, SOUND_PAN_ATTACKER, 12, 4
	waitforvisualfinish
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 3, 0, 0, ANIM_TARGET, 2
	createvisualtask AnimTask_ShakeMonInPlace, 2, ANIM_TARGET, 3, 0, 6, 1
	playsewithpan SE_M_MEGA_KICK2, SOUND_PAN_TARGET
	waitforvisualfinish
	clearmonbg ANIM_TARGET
	blendoff
	end

Move_SKETCH:
	loadspritegfx ANIM_TAG_PENCIL
	monbg ANIM_TARGET
	createvisualtask AnimTask_SketchDrawMon, 2
	createsprite gPencilSpriteTemplate, ANIM_TARGET, 2
	waitforvisualfinish
	clearmonbg ANIM_TARGET
	createvisualtask AnimTask_Splash, 2, 0, 2
	loopsewithpan SE_M_TAIL_WHIP, SOUND_PAN_ATTACKER, 38, 2
	end

Move_NIGHTMARE:
	fadetobg BG_GHOST
	waitbgfadein
	jumpifcontest NightmareInContest
	monbg ANIM_DEF_PARTNER
	createvisualtask AnimTask_NightmareClone, 2
	createvisualtask AnimTask_ShakeMon, 2, ANIM_TARGET, 3, 0, 40, 1
	playsewithpan SE_M_NIGHTMARE, SOUND_PAN_TARGET
	waitforvisualfinish
	clearmonbg ANIM_DEF_PARTNER
	restorebg
	waitbgfadein
	end

NightmareInContest:
	createvisualtask AnimTask_BlendMonInAndOut, 2, ANIM_ATTACKER, RGB_WHITE, 10, 2, 1
	createvisualtask AnimTask_ShakeMon, 2, ANIM_ATTACKER, 3, 0, 32, 1
	playsewithpan SE_M_NIGHTMARE, SOUND_PAN_TARGET
	waitforvisualfinish
	restorebg
	waitbgfadein
	end

Move_FLAIL:
	loadspritegfx ANIM_TAG_IMPACT
	monbg ANIM_TARGET
	setalpha 12, 8
	createvisualtask AnimTask_FlailMovement, 2, ANIM_ATTACKER
	loopsewithpan SE_M_HEADBUTT, SOUND_PAN_ATTACKER, 8, 2
	waitforvisualfinish
	createsprite gRandomPosHitSplatSpriteTemplate, ANIM_TARGET, 3, ANIM_TARGET, 3
	createvisualtask AnimTask_ShakeTargetBasedOnMovePowerOrDmg, 2, FALSE, 1, 30, 1, 0
	playsewithpan SE_M_MEGA_KICK2, SOUND_PAN_TARGET
	waitforvisualfinish
	clearmonbg ANIM_TARGET
	blendoff
	end

Move_SPITE:
	fadetobg BG_GHOST
	playsewithpan SE_M_PSYBEAM, SOUND_PAN_ATTACKER
	waitbgfadein
	monbg ANIM_DEF_PARTNER
	createvisualtask AnimTask_BlendColorCycle, 2, F_PAL_ATTACKER, 2, 6, 0, 8, RGB_WHITE
	createvisualtask AnimTask_SpiteTargetShadow, 2
	loopsewithpan SE_M_PSYBEAM, SOUND_PAN_TARGET, 20, 3
	waitforvisualfinish
	restorebg
	waitbgfadein
	clearmonbg ANIM_TARGET
	end

Move_MACH_PUNCH:
	loadspritegfx ANIM_TAG_IMPACT
	loadspritegfx ANIM_TAG_HANDS_AND_FEET
	monbg ANIM_ATK_PARTNER
	createvisualtask AnimTask_GetAttackerSide, 2
	jumprettrue MachPunchAgainstPlayer
	fadetobg BG_HIGHSPEED_OPPONENT
MachPunchContinue:
	waitbgfadeout
	createvisualtask AnimTask_StartSlidingBg, 5, -2304, 0, 1, -1
	waitbgfadein
	delay 0
	setalpha 9, 8
	createvisualtask AnimTask_AttackerPunchWithTrace, 2, RGB(8, 9, 28), 10
	playsewithpan SE_M_JUMP_KICK, SOUND_PAN_ATTACKER
	delay 6
	createsprite gBasicHitSplatSpriteTemplate, ANIM_TARGET, 3, 0, 0, ANIM_TARGET, 1
	createsprite gFistFootSpriteTemplate, ANIM_TARGET, 4, 0, 0, 8, 1, 0
	playsewithpan SE_M_COMET_PUNCH, SOUND_PAN_TARGET
	createvisualtask AnimTask_ShakeMon, 2, ANIM_TARGET, 3, 0, 6, 1
	waitforvisualfinish
	clearmonbg ANIM_ATK_PARTNER
	blendoff
	restorebg
	waitbgfadeout
	setarg 7, 0xFFFF
	waitbgfadein
	end

MachPunchAgainstPlayer:
	fadetobg BG_HIGHSPEED_PLAYER
	goto MachPunchContinue

Move_FORESIGHT:
	loadspritegfx ANIM_TAG_MAGNIFYING_GLASS
	monbg ANIM_DEF_PARTNER
	splitbgprio ANIM_TARGET
	setalpha 16, 0
	createsprite gForesightMagnifyingGlassSpriteTemplate, ANIM_TARGET, 2, ANIM_TARGET
	delay 17
	loopsewithpan SE_M_SKETCH, SOUND_PAN_TARGET, 16, 4
	delay 48
	delay 24
	playsewithpan SE_M_SKETCH, SOUND_PAN_TARGET
	delay 10
	createvisualtask AnimTask_BlendMonInAndOut, 5, ANIM_TARGET, RGB_WHITE, 12, 2, 1
	playsewithpan SE_M_DETECT, SOUND_PAN_TARGET
	waitforvisualfinish
	blendoff
	clearmonbg ANIM_DEF_PARTNER
	end

Move_DESTINY_BOND:
	loadspritegfx ANIM_TAG_WHITE_SHADOW
	fadetobg BG_GHOST
	playsewithpan SE_M_PSYBEAM, SOUND_PAN_ATTACKER
	waitbgfadein
	createvisualtask AnimTask_DestinyBondWhiteShadow, 5, 0, 48
	playsewithpan SE_M_CONFUSE_RAY, SOUND_PAN_ATTACKER
	delay 48
	createvisualtask AnimTask_ShakeMonInPlace, 2, ANIM_ATTACKER, 2, 0, 24, 1
	createvisualtask AnimTask_BlendBattleAnimPalExclude, 2, 6, 1, 0, 12, RGB(29, 29, 29)
	delay 24
	createvisualtask AnimTask_BlendBattleAnimPalExclude, 2, 6, 1, 12, 0, RGB(29, 29, 29)
	playsewithpan SE_M_NIGHTMARE, SOUND_PAN_TARGET
	waitforvisualfinish
	restorebg
	waitbgfadein
	blendoff
	clearmonbg 5
	end

Move_ENDURE:
	loadspritegfx ANIM_TAG_FOCUS_ENERGY
	playsewithpan SE_M_DRAGON_RAGE, SOUND_PAN_ATTACKER
	call EndureEffect
	delay 8
	createvisualtask AnimTask_BlendColorCycle, 2, F_PAL_ATTACKER, 2, 2, 0, 11, RGB_RED
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_ATTACKER, 1, 0, 32, 1
	call EndureEffect
	delay 8
	call EndureEffect
	waitforvisualfinish
	end

EndureEffect:
	createsprite gEndureEnergySpriteTemplate, ANIM_ATTACKER, 2, 0, -24, 26, 2
	delay 4
	createsprite gEndureEnergySpriteTemplate, ANIM_ATTACKER, 2, 0, 14, 28, 1
	delay 4
	createsprite gEndureEnergySpriteTemplate, ANIM_ATTACKER, 2, 0, -5, 10, 2
	delay 4
	createsprite gEndureEnergySpriteTemplate, ANIM_ATTACKER, 2, 0, 28, 26, 3
	delay 4
	createsprite gEndureEnergySpriteTemplate, ANIM_ATTACKER, 2, 0, -12, 0, 1
	return

Move_CHARM:
	loadspritegfx ANIM_TAG_MAGENTA_HEART
	createvisualtask AnimTask_RockMonBackAndForth, 5, ANIM_ATTACKER, 2, 0
	createsprite gMagentaHeartSpriteTemplate, ANIM_ATTACKER, 3, 0, 20
	playsewithpan SE_M_CHARM, SOUND_PAN_ATTACKER
	delay 15
	createsprite gMagentaHeartSpriteTemplate, ANIM_ATTACKER, 3, -20, 20
	playsewithpan SE_M_CHARM, SOUND_PAN_ATTACKER
	delay 15
	createsprite gMagentaHeartSpriteTemplate, ANIM_ATTACKER, 3, 20, 20
	playsewithpan SE_M_CHARM, SOUND_PAN_ATTACKER
	waitforvisualfinish
	end

Move_ROLLOUT:
	loadspritegfx ANIM_TAG_IMPACT
	loadspritegfx ANIM_TAG_MUD_SAND
	loadspritegfx ANIM_TAG_ROCKS
	monbg ANIM_DEF_PARTNER
	splitbgprio ANIM_TARGET
	setalpha 12, 8
	createvisualtask AnimTask_Rollout, 2
	waitforvisualfinish
	createvisualtask AnimTask_ShakeTargetBasedOnMovePowerOrDmg, 2, FALSE, 1, 30, 1, 0
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 4, 0, 0, ANIM_TARGET, 2
	playsewithpan SE_M_MEGA_KICK2, SOUND_PAN_TARGET
	waitforvisualfinish
	clearmonbg ANIM_DEF_PARTNER
	blendoff
	end

Move_FALSE_SWIPE:
	loadspritegfx ANIM_TAG_SLASH_2
	loadspritegfx ANIM_TAG_IMPACT
	createsprite gFalseSwipeSliceSpriteTemplate, ANIM_TARGET, 2
	playsewithpan SE_M_VITAL_THROW, SOUND_PAN_TARGET
	delay 16
	createsprite gFalseSwipePositionedSliceSpriteTemplate, ANIM_TARGET, 2, 0
	playsewithpan SE_M_DOUBLE_TEAM, SOUND_PAN_TARGET
	delay 2
	createsprite gFalseSwipePositionedSliceSpriteTemplate, ANIM_TARGET, 2, 16
	delay 2
	createsprite gFalseSwipePositionedSliceSpriteTemplate, ANIM_TARGET, 2, 32
	playsewithpan SE_M_DOUBLE_TEAM, SOUND_PAN_TARGET
	delay 2
	createsprite gFalseSwipePositionedSliceSpriteTemplate, ANIM_TARGET, 2, 48
	delay 2
	createsprite gFalseSwipePositionedSliceSpriteTemplate, ANIM_TARGET, 2, 64
	playsewithpan SE_M_DOUBLE_TEAM, SOUND_PAN_TARGET
	delay 2
	createsprite gFalseSwipePositionedSliceSpriteTemplate, ANIM_TARGET, 2, 80
	delay 2
	waitforvisualfinish
	createvisualtask AnimTask_ShakeMon, 2, ANIM_TARGET, 5, 0, 6, 1
	createsprite gBasicHitSplatSpriteTemplate, ANIM_TARGET, 4, 0, 0, ANIM_TARGET, 3
	playsewithpan SE_M_COMET_PUNCH, SOUND_PAN_TARGET
	end

Move_SWAGGER:
	loadspritegfx ANIM_TAG_BREATH
	loadspritegfx ANIM_TAG_ANGER
	createvisualtask AnimTask_GrowAndShrink, 2
	playsewithpan SE_M_SWAGGER, SOUND_PAN_ATTACKER
	waitforvisualfinish
	createsprite gBreathPuffSpriteTemplate, ANIM_ATTACKER, 2
	loopsewithpan SE_M_SWAGGER, SOUND_PAN_ATTACKER, 4, 2
	waitforvisualfinish
	delay 24
	createsprite gAngerMarkSpriteTemplate, ANIM_TARGET, 2, 1, -20, -28
	playsewithpan SE_M_SWAGGER2, SOUND_PAN_TARGET
	delay 12
	createsprite gAngerMarkSpriteTemplate, ANIM_TARGET, 2, 1, 20, -28
	playsewithpan SE_M_SWAGGER2, SOUND_PAN_TARGET
	waitforvisualfinish
	end

Move_MILK_DRINK:
	loadspritegfx ANIM_TAG_MILK_BOTTLE
	loadspritegfx ANIM_TAG_THIN_RING
	loadspritegfx ANIM_TAG_BLUE_STAR
	monbg ANIM_TARGET
	createsprite gMilkBottleSpriteTemplate, ANIM_ATTACKER, 2
	delay 40
	playsewithpan SE_M_CRABHAMMER, SOUND_PAN_ATTACKER
	delay 12
	playsewithpan SE_M_CRABHAMMER, SOUND_PAN_ATTACKER
	delay 20
	playsewithpan SE_M_CRABHAMMER, SOUND_PAN_ATTACKER
	waitforvisualfinish
	createsprite gThinRingExpandingSpriteTemplate, ANIM_ATTACKER, 3, 0, 0, 1, 0
	playsewithpan SE_M_MILK_DRINK, SOUND_PAN_ATTACKER
	waitforvisualfinish
	clearmonbg ANIM_TARGET
	call HealingEffect2
	waitforvisualfinish
	end

Move_MAGNITUDE:
	createvisualtask AnimTask_IsPowerOver99, 2
	waitforvisualfinish
	jumpargeq 15, FALSE, MagnitudeRegular
	jumpargeq 15, TRUE, MagnitudeIntense
MagnitudeEnd:
	end

MagnitudeRegular:
	createvisualtask AnimTask_HorizontalShake, 5, (MAX_BATTLERS_COUNT + 1), 0, 50
	createvisualtask AnimTask_HorizontalShake, 5, MAX_BATTLERS_COUNT, 0, 50
	loopsewithpan SE_M_STRENGTH, SOUND_PAN_TARGET, 8, 10
	goto MagnitudeEnd

MagnitudeIntense:
	createvisualtask AnimTask_HorizontalShake, 5, (MAX_BATTLERS_COUNT + 1), 0, 50
	createvisualtask AnimTask_HorizontalShake, 5, MAX_BATTLERS_COUNT, 0, 50
	loopsewithpan SE_M_STRENGTH, SOUND_PAN_TARGET, 8, 10
	delay 10
	createsprite gComplexPaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG, 3, 1, RGB_BLACK, 14, RGB_WHITE, 14
	delay 16
	createsprite gComplexPaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG, 3, 1, RGB_BLACK, 14, RGB_WHITE, 14
	goto MagnitudeEnd

Move_RAPID_SPIN:
	loadspritegfx ANIM_TAG_IMPACT
	loadspritegfx ANIM_TAG_RAPID_SPIN
	monbg ANIM_ATTACKER
	createsprite gRapidSpinSpriteTemplate, ANIM_ATTACKER, 2, 0, 0, 32, -32, 40, -2
	createvisualtask AnimTask_RapinSpinMonElevation, 2, 0, 2, 0
	loopsewithpan SE_M_RAZOR_WIND2, SOUND_PAN_ATTACKER, 8, 4
	waitforvisualfinish
	createsprite gBasicHitSplatSpriteTemplate, ANIM_TARGET, 2, 0, 0, ANIM_TARGET, 2
	createvisualtask AnimTask_ShakeTargetBasedOnMovePowerOrDmg, 2, FALSE, 1, 10, 1, 0
	playsewithpan SE_M_DOUBLE_SLAP, SOUND_PAN_TARGET
	waitforvisualfinish
	delay 8
	createvisualtask AnimTask_RapinSpinMonElevation, 2, 0, 2, 1
	loopsewithpan SE_M_RAZOR_WIND2, SOUND_PAN_ATTACKER, 8, 4
	waitforvisualfinish
	clearmonbg ANIM_ATTACKER
	end

Move_MOONLIGHT:
	loadspritegfx ANIM_TAG_MOON
	loadspritegfx ANIM_TAG_GREEN_SPARKLE
	loadspritegfx ANIM_TAG_BLUE_STAR
	setalpha 0, 16
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG, 1, 0, 16, RGB_BLACK
	waitforvisualfinish
	createsprite gMoonSpriteTemplate, ANIM_ATTACKER, 2, 120, 56
	createvisualtask AnimTask_AlphaFadeIn, 3, 0, 16, 16, 0, 1
	playsewithpan SE_M_MOONLIGHT, 0
	delay 30
	createsprite gMoonlightSparkleSpriteTemplate, ANIM_ATTACKER, 40, -12, 0
	delay 30
	createsprite gMoonlightSparkleSpriteTemplate, ANIM_ATTACKER, 40, -24, 0
	delay 30
	createsprite gMoonlightSparkleSpriteTemplate, ANIM_ATTACKER, 40, 21, 0
	delay 30
	createsprite gMoonlightSparkleSpriteTemplate, ANIM_ATTACKER, 40, 0, 0
	delay 30
	createsprite gMoonlightSparkleSpriteTemplate, ANIM_ATTACKER, 40, 10, 0
	delay 20
	createvisualtask AnimTask_MoonlightEndFade, 2
	waitforvisualfinish
	call HealingEffect
	waitforvisualfinish
	end

Move_EXTREME_SPEED:
	loadspritegfx ANIM_TAG_SPEED_DUST
	loadspritegfx ANIM_TAG_IMPACT
	createvisualtask AnimTask_GetAttackerSide, 2
	jumprettrue ExtremeSpeedAgainstPlayer
	fadetobg BG_HIGHSPEED_OPPONENT
ExtremeSpeedContinue:
	waitbgfadeout
	createvisualtask AnimTask_StartSlidingBg, 5, -2304, 0, 1, -1
	waitbgfadein
	createvisualtask AnimTask_AttackerStretchAndDisappear, 2
	loopsewithpan SE_M_RAZOR_WIND2, SOUND_PAN_ATTACKER, 8, 3
	waitforvisualfinish
	delay 1
	createvisualtask AnimTask_SetAttackerInvisibleWaitForSignal, 2
	monbg ANIM_TARGET
	setalpha 12, 8
	delay 18
	createvisualtask AnimTask_ExtremeSpeedImpact, 2
	delay 2
	playsewithpan SE_M_COMET_PUNCH, SOUND_PAN_TARGET
	createsprite gMonEdgeHitSplatSpriteTemplate, ANIM_TARGET, 2, ANIM_TARGET, 0, -12, 3
	delay 10
	playsewithpan SE_M_COMET_PUNCH, SOUND_PAN_TARGET
	createsprite gMonEdgeHitSplatSpriteTemplate, ANIM_TARGET, 2, ANIM_TARGET, 0, 12, 3
	delay 10
	playsewithpan SE_M_VITAL_THROW2, SOUND_PAN_TARGET
	createsprite gMonEdgeHitSplatSpriteTemplate, ANIM_TARGET, 2, ANIM_TARGET, 0, 0, 3
	waitforvisualfinish
	createvisualtask AnimTask_SpeedDust, 2
	delay 10
	createvisualtask AnimTask_ExtremeSpeedMonReappear, 2
	loopsewithpan SE_M_DOUBLE_TEAM, SOUND_PAN_ATTACKER, 8, 4
	waitforvisualfinish
	restorebg
	waitbgfadeout
	setarg 7, 0xFFFF
	waitbgfadein
	clearmonbg ANIM_TARGET
	blendoff
	delay 1
	setarg 7, 0x1000
	delay 1
	end

ExtremeSpeedAgainstPlayer:
	fadetobg BG_HIGHSPEED_PLAYER
	goto ExtremeSpeedContinue

Move_UPROAR:
	loadspritegfx ANIM_TAG_JAGGED_MUSIC_NOTE
	loadspritegfx ANIM_TAG_THIN_RING
	monbg ANIM_DEF_PARTNER
	createvisualtask AnimTask_UproarDistortion, 2, 0
	createsprite gUproarRingSpriteTemplate, ANIM_ATTACKER, 3, 0, 0, 0, 0, 31, 8
	playsewithpan SE_M_UPROAR, SOUND_PAN_ATTACKER
	createsprite gJaggedMusicNoteSpriteTemplate, ANIM_ATTACKER, 2, 0, 29, -12, 0
	createsprite gJaggedMusicNoteSpriteTemplate, ANIM_ATTACKER, 2, 0, -12, -29, 1
	delay 16
	createvisualtask AnimTask_UproarDistortion, 2, 0
	createsprite gUproarRingSpriteTemplate, ANIM_ATTACKER, 3, 0, 0, 0, 0, 31, 8
	playsewithpan SE_M_UPROAR, SOUND_PAN_ATTACKER
	createsprite gJaggedMusicNoteSpriteTemplate, ANIM_ATTACKER, 2, 0, 12, -29, 1
	createsprite gJaggedMusicNoteSpriteTemplate, ANIM_ATTACKER, 2, 0, -29, -12, 0
	delay 16
	createvisualtask AnimTask_UproarDistortion, 2, 0
	createsprite gUproarRingSpriteTemplate, ANIM_ATTACKER, 3, 0, 0, 0, 0, 31, 8
	playsewithpan SE_M_UPROAR, SOUND_PAN_ATTACKER
	createsprite gJaggedMusicNoteSpriteTemplate, ANIM_ATTACKER, 2, 0, 24, -24, 1
	createsprite gJaggedMusicNoteSpriteTemplate, ANIM_ATTACKER, 2, 0, -24, -24, 0
	waitforvisualfinish
	clearmonbg ANIM_DEF_PARTNER
	end

Move_HEAT_WAVE:
	loadspritegfx ANIM_TAG_FLYING_DIRT
	createvisualtask AnimTask_BlendParticle, 5, ANIM_TAG_FLYING_DIRT, 0, 6, 6, RGB_RED
	createvisualtask AnimTask_LoadSandstormBackground, 5, TRUE
	createvisualtask AnimTask_BlendBackground, 6, 6, RGB_RED
	panse SE_M_HEAT_WAVE, SOUND_PAN_ATTACKER, SOUND_PAN_TARGET, +2, 0
	delay 4
	createvisualtask AnimTask_MoveHeatWaveTargets, 5
	delay 12
	createsprite gFlyingSandCrescentSpriteTemplate, ANIM_ATTACKER, 40, 10, 2304, 96, 1
	delay 10
	createsprite gFlyingSandCrescentSpriteTemplate, ANIM_ATTACKER, 40, 90, 2048, 96, 1
	delay 10
	createsprite gFlyingSandCrescentSpriteTemplate, ANIM_ATTACKER, 40, 50, 2560, 96, 1
	delay 10
	createsprite gFlyingSandCrescentSpriteTemplate, ANIM_ATTACKER, 40, 20, 2304, 96, 1
	delay 10
	createsprite gFlyingSandCrescentSpriteTemplate, ANIM_ATTACKER, 40, 70, 1984, 96, 1
	delay 10
	createsprite gFlyingSandCrescentSpriteTemplate, ANIM_ATTACKER, 40, 0, 2816, 96, 1
	delay 10
	createsprite gFlyingSandCrescentSpriteTemplate, ANIM_ATTACKER, 40, 60, 2560, 96, 1
	end

@ Also used by Hail weather
Move_HAIL:
	loadspritegfx ANIM_TAG_HAIL
	loadspritegfx ANIM_TAG_ICE_CRYSTALS
	createvisualtask AnimTask_BlendBattleAnimPal, 10, F_PAL_BG, 3, 0, 6, RGB_BLACK
	waitforvisualfinish
	createvisualtask AnimTask_Hail, 5
	loopsewithpan SE_M_HAIL, 0, 8, 10
	waitforvisualfinish
	createvisualtask AnimTask_BlendBattleAnimPal, 10, F_PAL_BG, 3, 6, 0, RGB_BLACK
	end

Move_TORMENT:
	loadspritegfx ANIM_TAG_ANGER
	loadspritegfx ANIM_TAG_THOUGHT_BUBBLE
	createvisualtask AnimTask_TormentAttacker, 2
	waitforvisualfinish
	createvisualtask AnimTask_BlendMonInAndOut, 2, ANIM_TARGET, RGB_RED, 10, 1, 1
	createsprite gAngerMarkSpriteTemplate, ANIM_TARGET, 2, 1, -20, -28
	playsewithpan SE_M_SWAGGER2, SOUND_PAN_TARGET
	delay 20
	createsprite gAngerMarkSpriteTemplate, ANIM_TARGET, 2, 1, 20, -28
	playsewithpan SE_M_SWAGGER2, SOUND_PAN_TARGET
	end

Move_MEMENTO:
	setalpha 0, 16
	delay 1
	createvisualtask AnimTask_InitMementoShadow, 2
	delay 1
	createvisualtask AnimTask_MoveAttackerMementoShadow, 5
	playsewithpan SE_M_PSYBEAM, SOUND_PAN_ATTACKER
	delay 48
	playsewithpan SE_M_PSYBEAM2, SOUND_PAN_ATTACKER
	waitforvisualfinish
	createvisualtask AnimTask_MementoHandleBg, 2
	delay 12
	setalpha 0, 16
	delay 1
	monbg_static ANIM_TARGET
	createvisualtask AnimTask_MoveTargetMementoShadow, 5
	playsewithpan SE_M_PSYBEAM, SOUND_PAN_TARGET
	waitforvisualfinish
	clearmonbg_static ANIM_TARGET
	delay 1
	blendoff
	delay 1
	end

Move_FACADE:
	loadspritegfx ANIM_TAG_SWEAT_DROP
	createvisualtask AnimTask_SquishAndSweatDroplets, 2, ANIM_ATTACKER, 3
	createvisualtask AnimTask_FacadeColorBlend, 2, ANIM_ATTACKER, 72
	loopsewithpan SE_M_SWAGGER, SOUND_PAN_ATTACKER, 24, 3
	end

Move_SMELLING_SALT:
	loadspritegfx ANIM_TAG_TAG_HAND
	loadspritegfx ANIM_TAG_SMELLINGSALT_EFFECT
	createsprite gSmellingSaltsHandSpriteTemplate, ANIM_TARGET, 2, ANIM_TARGET, 0, 2
	createsprite gSmellingSaltsHandSpriteTemplate, ANIM_TARGET, 2, ANIM_TARGET, 1, 2
	delay 32
	createvisualtask AnimTask_SmellingSaltsSquish, 3, ANIM_TARGET, 2
	loopsewithpan SE_M_DOUBLE_SLAP, SOUND_PAN_TARGET, 12, 2
	waitforvisualfinish
	delay 4
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_TARGET, 2, 0, 6, 2
	createsprite gSmellingSaltExclamationSpriteTemplate, ANIM_TARGET, 2, ANIM_TARGET, 8, 3
	loopsewithpan SE_M_SWAGGER2, SOUND_PAN_TARGET, 16, 3
	end

Move_FOLLOW_ME:
	loadspritegfx ANIM_TAG_FINGER
	createsprite gFollowMeFingerSpriteTemplate, ANIM_ATTACKER, 2, 0
	playsewithpan SE_M_TAIL_WHIP, SOUND_PAN_ATTACKER
	delay 18
	playsewithpan SE_M_ATTRACT, SOUND_PAN_ATTACKER
	delay 71
	loopsewithpan SE_M_TAIL_WHIP, SOUND_PAN_ATTACKER, 22, 3
	end

Move_CHARGE:
	loadspritegfx ANIM_TAG_ELECTRIC_ORBS
	loadspritegfx ANIM_TAG_CIRCLE_OF_LIGHT
	loadspritegfx ANIM_TAG_ELECTRICITY
	monbg ANIM_ATTACKER
	setalpha 12, 8
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG, 2, 0, 4, RGB_BLACK
	waitforvisualfinish
	createvisualtask AnimTask_ElectricChargingParticles, 2, ANIM_ATTACKER, 60, 2, 12
	playsewithpan SE_M_CHARGE, SOUND_PAN_ATTACKER
	delay 30
	playsewithpan SE_M_CHARGE, SOUND_PAN_ATTACKER
	delay 30
	playsewithpan SE_M_CHARGE, SOUND_PAN_ATTACKER
	createsprite gGrowingChargeOrbSpriteTemplate, ANIM_ATTACKER, 2, 0
	delay 25
	playsewithpan SE_M_CHARGE, SOUND_PAN_ATTACKER
	delay 20
	playsewithpan SE_M_CHARGE, SOUND_PAN_ATTACKER
	delay 15
	playsewithpan SE_M_CHARGE, SOUND_PAN_ATTACKER
	delay 10
	delay 6
	loopsewithpan SE_M_CHARGE, SOUND_PAN_ATTACKER, 6, 5
	waitforvisualfinish
	createsprite gElectricPuffSpriteTemplate, ANIM_ATTACKER, 2, 0, 16, 16
	delay 2
	createsprite gElectricPuffSpriteTemplate, ANIM_ATTACKER, 2, 0, -16, -16
	playsewithpan SE_M_THUNDERBOLT2, SOUND_PAN_ATTACKER
	waitforvisualfinish
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG, 4, 4, 0, RGB_BLACK
	clearmonbg ANIM_ATTACKER
	blendoff
	end

Move_TAUNT:
	loadspritegfx ANIM_TAG_FINGER_2
	loadspritegfx ANIM_TAG_THOUGHT_BUBBLE
	loadspritegfx ANIM_TAG_ANGER
	createsprite gThoughtBubbleSpriteTemplate, ANIM_ATTACKER, 11, 0, 45
	playsewithpan SE_M_METRONOME, SOUND_PAN_ATTACKER
	delay 6
	createsprite gTauntFingerSpriteTemplate, ANIM_ATTACKER, 12, 0
	delay 4
	loopsewithpan SE_M_TAIL_WHIP, SOUND_PAN_ATTACKER, 16, 2
	waitforvisualfinish
	delay 8
	createsprite gAngerMarkSpriteTemplate, ANIM_TARGET, 2, 1, -20, -28
	playsewithpan SE_M_SWAGGER2, SOUND_PAN_TARGET
	waitforvisualfinish
	delay 12
	createsprite gAngerMarkSpriteTemplate, ANIM_TARGET, 2, 1, 20, -28
	playsewithpan SE_M_SWAGGER2, SOUND_PAN_TARGET
	end

Move_HELPING_HAND:
	loadspritegfx ANIM_TAG_TAG_HAND
	createvisualtask AnimTask_HelpingHandAttackerMovement, 5
	createsprite gHelpingHandClapSpriteTemplate, ANIM_ATTACKER, 40, 0
	createsprite gHelpingHandClapSpriteTemplate, ANIM_ATTACKER, 40, 1
	delay 19
	playsewithpan SE_M_ENCORE, 0
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_ATK_PARTNER, 2, 0, 5, 1
	delay 14
	playsewithpan SE_M_ENCORE, 0
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_ATK_PARTNER, 2, 0, 5, 1
	delay 20
	playsewithpan SE_M_ENCORE, 0
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_ATK_PARTNER, 3, 0, 10, 1
	createvisualtask AnimTask_BlendMonInAndOut, 2, ANIM_ATK_PARTNER, RGB_YELLOW, 12, 1, 1
	end

Move_ASSIST:
	loadspritegfx ANIM_TAG_PAW_PRINT
	createsprite gAssistPawprintSpriteTemplate, ANIM_ATTACKER, 50, 112, -16, 140, 128, 36
	delay 2
	createsprite gAssistPawprintSpriteTemplate, ANIM_ATTACKER, 50, 208, 128, -16, 48, 36
	playsewithpan SE_M_SCRATCH, 0
	delay 2
	createsprite gAssistPawprintSpriteTemplate, ANIM_ATTACKER, 50, -16, 112, 256, -16, 36
	playsewithpan SE_M_SCRATCH, 0
	delay 2
	createsprite gAssistPawprintSpriteTemplate, ANIM_ATTACKER, 50, 108, 128, 84, -16, 36
	playsewithpan SE_M_SCRATCH, 0
	delay 2
	createsprite gAssistPawprintSpriteTemplate, ANIM_ATTACKER, 50, -16, 56, 256, 56, 36
	playsewithpan SE_M_SCRATCH, 0
	end

Move_SUPERPOWER:
	loadspritegfx ANIM_TAG_CIRCLE_OF_LIGHT
	loadspritegfx ANIM_TAG_METEOR
	loadspritegfx ANIM_TAG_FLAT_ROCK
	monbg ANIM_ATK_PARTNER
	splitbgprio ANIM_ATTACKER
	setalpha 12, 8
	createsprite gSuperpowerOrbSpriteTemplate, ANIM_TARGET, 2, ANIM_ATTACKER
	playsewithpan SE_M_MEGA_KICK, SOUND_PAN_ATTACKER
	delay 20
	createsprite gShakeMonOrTerrainSpriteTemplate, ANIM_ATTACKER, 2, 4, 1, 180, 1
	createvisualtask SoundTask_PlaySE2WithPanning, 5, SE_M_EARTHQUAKE, 0
	delay 40
	createsprite gSuperpowerRockSpriteTemplate, ANIM_ATTACKER, 41, 200, 96, 1, 120
	delay 8
	createsprite gSuperpowerRockSpriteTemplate, ANIM_ATTACKER, 41, 20, 248, 4, 112
	delay 8
	createsprite gSuperpowerRockSpriteTemplate, ANIM_ATTACKER, 41, 130, 160, 2, 104
	delay 8
	createsprite gSuperpowerRockSpriteTemplate, ANIM_ATTACKER, 41, 160, 192, 0, 96
	delay 8
	createsprite gSuperpowerRockSpriteTemplate, ANIM_ATTACKER, 41, 60, 288, 3, 88
	delay 74
	createsprite gSuperpowerFireballSpriteTemplate, ANIM_TARGET, 3, ANIM_ATTACKER
	playsewithpan SE_M_SWAGGER, SOUND_PAN_ATTACKER
	delay 16
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_TARGET, 8, 0, 16, 1
	playsewithpan SE_M_MEGA_KICK2, SOUND_PAN_TARGET
	waitforvisualfinish
	clearmonbg ANIM_ATK_PARTNER
	blendoff
	delay 1
	end

Move_RECYCLE:
	loadspritegfx ANIM_TAG_RECYCLE
	monbg ANIM_ATTACKER
	setalpha 0, 16
	delay 1
	createsprite gRecycleSpriteTemplate, ANIM_ATTACKER, 2
	loopsewithpan SE_M_TAKE_DOWN, SOUND_PAN_ATTACKER, 24, 3
	waitforvisualfinish
	createvisualtask AnimTask_BlendMonInAndOut, 5, ANIM_ATTACKER, RGB_WHITE, 12, 2, 1
	playsewithpan SE_M_TAKE_DOWN, SOUND_PAN_ATTACKER
	waitforvisualfinish
	blendoff
	clearmonbg ANIM_ATTACKER
	delay 1
	end

Move_BRICK_BREAK:
	loadspritegfx ANIM_TAG_BLUE_LIGHT_WALL
	loadspritegfx ANIM_TAG_IMPACT
	loadspritegfx ANIM_TAG_HANDS_AND_FEET
	loadspritegfx ANIM_TAG_TORN_METAL
	choosetwoturnanim BrickBreakNormal, BrickBreakShatteredWall

BrickBreakNormal:
	monbg ANIM_TARGET
	setalpha 12, 8
	createsprite gHorizontalLungeSpriteTemplate, ANIM_ATTACKER, 2, 3, 8
	delay 4
	delay 1
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 3, -18, -18, ANIM_TARGET, 1
	createsprite gFistFootSpriteTemplate, ANIM_ATTACKER, 2, -18, -18, 10, 1, 0
	playsewithpan SE_M_VITAL_THROW, SOUND_PAN_TARGET
	delay 20
	createsprite gHorizontalLungeSpriteTemplate, ANIM_ATTACKER, 2, 3, 8
	delay 5
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 3, 18, 18, ANIM_TARGET, 1
	createsprite gFistFootSpriteTemplate, ANIM_ATTACKER, 2, 18, 18, 10, 1, 0
	playsewithpan SE_M_VITAL_THROW, SOUND_PAN_TARGET
	delay 20
	createvisualtask AnimTask_WindUpLunge, 2, ANIM_ATTACKER, -24, 0, 24, 10, 24, 3
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG, 2, 0, 6, RGB_BLACK
	delay 37
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 3, 0, 0, ANIM_TARGET, 1
	createsprite gFistFootSpriteTemplate, ANIM_ATTACKER, 2, 0, 0, 10, 1, 0
	playsewithpan SE_M_VITAL_THROW2, SOUND_PAN_TARGET
	waitforvisualfinish
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG, 2, 6, 0, RGB_BLACK
	waitforvisualfinish
	clearmonbg ANIM_TARGET
	end

BrickBreakShatteredWall:
	monbg ANIM_TARGET
	setalpha 12, 8
	createsprite gHorizontalLungeSpriteTemplate, ANIM_ATTACKER, 2, 3, 8
	delay 4
	createsprite gBrickBreakWallSpriteTemplate, ANIM_ATTACKER, 3, ANIM_TARGET, 0, 0, 90, 10
	delay 1
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 3, -18, -18, ANIM_TARGET, 1
	createsprite gFistFootSpriteTemplate, ANIM_ATTACKER, 2, -18, -18, 10, 1, 0
	playsewithpan SE_M_VITAL_THROW, SOUND_PAN_TARGET
	delay 20
	createsprite gHorizontalLungeSpriteTemplate, ANIM_ATTACKER, 2, 3, 8
	delay 5
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 3, 18, 18, ANIM_TARGET, 1
	createsprite gFistFootSpriteTemplate, ANIM_ATTACKER, 2, 18, 18, 10, 1, 0
	playsewithpan SE_M_VITAL_THROW, SOUND_PAN_TARGET
	delay 20
	createvisualtask AnimTask_WindUpLunge, 2, ANIM_ATTACKER, -24, 0, 24, 10, 24, 3
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG, 2, 0, 6, RGB_BLACK
	delay 37
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 3, 0, 0, ANIM_TARGET, 1
	createsprite gFistFootSpriteTemplate, ANIM_ATTACKER, 2, 0, 0, 10, 1, 0
	playsewithpan SE_M_VITAL_THROW2, SOUND_PAN_TARGET
	waitforvisualfinish
	createsprite gBrickBreakWallShardSpriteTemplate, ANIM_ATTACKER, 2, ANIM_TARGET, 0, -8, -12
	createsprite gBrickBreakWallShardSpriteTemplate, ANIM_ATTACKER, 2, ANIM_TARGET, 1, 8, -12
	createsprite gBrickBreakWallShardSpriteTemplate, ANIM_ATTACKER, 2, ANIM_TARGET, 2, -8, 12
	createsprite gBrickBreakWallShardSpriteTemplate, ANIM_ATTACKER, 2, ANIM_TARGET, 3, 8, 12
	playsewithpan SE_M_BRICK_BREAK, SOUND_PAN_TARGET
	waitforvisualfinish
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG, 2, 6, 0, RGB_BLACK
	waitforvisualfinish
	clearmonbg ANIM_TARGET
	end

Move_YAWN:
	loadspritegfx ANIM_TAG_PINK_CLOUD
	createvisualtask AnimTask_DeepInhale, 2, ANIM_ATTACKER
	playsewithpan SE_M_YAWN, SOUND_PAN_ATTACKER
	waitforvisualfinish
	createsprite gYawnCloudSpriteTemplate, ANIM_TARGET, 5, 2
	playsewithpan SE_M_SPIT_UP, SOUND_PAN_ATTACKER
	delay 4
	createsprite gYawnCloudSpriteTemplate, ANIM_TARGET, 5, 1
	delay 4
	createsprite gYawnCloudSpriteTemplate, ANIM_TARGET, 5, 0
	waitforvisualfinish
	createvisualtask AnimTask_DeepInhale, 2, ANIM_TARGET
	playsewithpan SE_M_YAWN, SOUND_PAN_TARGET
	end

Move_ENDEAVOR:
	loadspritegfx ANIM_TAG_SWEAT_DROP
	loadspritegfx ANIM_TAG_IMPACT
	createvisualtask AnimTask_SquishAndSweatDroplets, 2, ANIM_ATTACKER, 2
	loopsewithpan SE_M_TAIL_WHIP, SOUND_PAN_ATTACKER, 24, 2
	createvisualtask AnimTask_BlendMonInAndOut, 5, ANIM_ATTACKER, RGB(31, 21, 0), 12, 1, 2
	delay 6
	createvisualtask AnimTask_ShakeTargetBasedOnMovePowerOrDmg, 5, FALSE, 1, 8, 1, 0
	createsprite gBasicHitSplatSpriteTemplate, ANIM_TARGET, 2, 12, -12, ANIM_TARGET, 2
	playsewithpan SE_M_DOUBLE_SLAP, SOUND_PAN_TARGET
	delay 24
	createvisualtask AnimTask_ShakeTargetBasedOnMovePowerOrDmg, 5, FALSE, 1, 8, 1, 0
	createsprite gBasicHitSplatSpriteTemplate, ANIM_TARGET, 2, -12, 12, ANIM_TARGET, 2
	playsewithpan SE_M_COMET_PUNCH, SOUND_PAN_TARGET
	end

Move_ERUPTION:
	loadspritegfx ANIM_TAG_WARM_ROCK
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG | F_PAL_BATTLERS, 2, 0, 4, RGB_RED
	waitforvisualfinish
	createvisualtask AnimTask_EruptionLaunchRocks, 2
	waitplaysewithpan SE_M_EXPLOSION, SOUND_PAN_ATTACKER, 60
	waitforvisualfinish
	createvisualtask AnimTask_EruptionLaunchRocks, 2
	waitplaysewithpan SE_M_EXPLOSION, SOUND_PAN_ATTACKER, 60
	waitforvisualfinish
	delay 30
	createsprite gEruptionFallingRockSpriteTemplate, ANIM_ATTACKER, 40, 200, -32, 0, 100, 0
	createsprite gEruptionFallingRockSpriteTemplate, ANIM_ATTACKER, 40, 30, -32, 16, 90, 1
	createsprite gEruptionFallingRockSpriteTemplate, ANIM_ATTACKER, 40, 150, -32, 32, 60, 2
	createsprite gEruptionFallingRockSpriteTemplate, ANIM_ATTACKER, 40, 90, -32, 48, 80, 3
	createsprite gEruptionFallingRockSpriteTemplate, ANIM_ATTACKER, 40, 110, -32, 64, 50, 0
	createsprite gEruptionFallingRockSpriteTemplate, ANIM_ATTACKER, 40, 60, -32, 80, 70, 1
	delay 22
	createvisualtask AnimTask_HorizontalShake, 5, (MAX_BATTLERS_COUNT + 1), 8, 60
	createvisualtask AnimTask_HorizontalShake, 5, MAX_BATTLERS_COUNT, 8, 60
	loopsewithpan SE_M_ROCK_THROW, SOUND_PAN_TARGET, 16, 12
	delay 80
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 40, F_PAL_BG | F_PAL_BATTLERS, 4, 4, 0, RGB_RED
	end

Move_SKILL_SWAP:
	loadspritegfx ANIM_TAG_BLUEGREEN_ORB
	call SetPsychicBackground
	createvisualtask AnimTask_SkillSwap, 3, ANIM_TARGET
	createvisualtask AnimTask_BlendMonInAndOut, 5, ANIM_TARGET, RGB_WHITE, 12, 3, 1
	loopsewithpan SE_M_REVERSAL, SOUND_PAN_ATTACKER, 24, 3
	delay 16
	createvisualtask AnimTask_SkillSwap, 3, ANIM_ATTACKER
	createvisualtask AnimTask_BlendMonInAndOut, 5, ANIM_ATTACKER, RGB_WHITE, 12, 3, 1
	waitforvisualfinish
	call UnsetPsychicBackground
	end

Move_IMPRISON:
	loadspritegfx ANIM_TAG_HOLLOW_ORB
	loadspritegfx ANIM_TAG_X_SIGN
	call SetPsychicBackground
	monbg ANIM_DEF_PARTNER
	createvisualtask AnimTask_ImprisonOrbs, 5
	delay 8
	loopsewithpan SE_M_HORN_ATTACK, SOUND_PAN_ATTACKER, 8, 5
	waitforvisualfinish
	delay 4
	createsprite gRedXSpriteTemplate, ANIM_ATTACKER, 5, ANIM_ATTACKER, 40
	createvisualtask AnimTask_HorizontalShake, 5, MAX_BATTLERS_COUNT, 1, 10
	playsewithpan SE_M_HYPER_BEAM, SOUND_PAN_ATTACKER
	clearmonbg ANIM_DEF_PARTNER
	call UnsetPsychicBackground
	end

Move_GRUDGE:
	loadspritegfx ANIM_TAG_PURPLE_FLAME
	monbg ANIM_ATTACKER
	splitbgprio_all
	fadetobg BG_GHOST
	playsewithpan SE_M_PSYBEAM, SOUND_PAN_ATTACKER
	waitbgfadein
	createvisualtask AnimTask_GrudgeFlames, 3
	loopsewithpan SE_M_EMBER, SOUND_PAN_ATTACKER, 16, 4
	delay 10
	delay 80
	playsewithpan SE_M_NIGHTMARE, SOUND_PAN_TARGET
	waitforvisualfinish
	restorebg
	waitbgfadein
	clearmonbg ANIM_ATTACKER
	end

Move_CAMOUFLAGE:
	monbg ANIM_ATK_PARTNER
	splitbgprio ANIM_ATTACKER
	setalpha 16, 0
	createvisualtask AnimTask_SetCamouflageBlend, 5, F_PAL_ATTACKER, 3, 0, 14
	delay 16
	createvisualtask AnimTask_AttackerFadeToInvisible, 2, 4
	playsewithpan SE_M_FAINT_ATTACK, SOUND_PAN_ATTACKER
	waitforvisualfinish
	delay 8
	createvisualtask AnimTask_SetCamouflageBlend, 5, F_PAL_ATTACKER, 0, 0, 0
	waitforvisualfinish
	createvisualtask AnimTask_AttackerFadeFromInvisible, 2, 1
	waitforvisualfinish
	blendoff
	clearmonbg ANIM_ATK_PARTNER
	end

Move_TAIL_GLOW:
	loadspritegfx ANIM_TAG_CIRCLE_OF_LIGHT
	monbg ANIM_ATTACKER
	setalpha 12, 8
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG, 2, 0, 4, RGB_BLACK
	waitforvisualfinish
	createsprite gTailGlowOrbSpriteTemplate, ANIM_ATTACKER, 66, ANIM_ATTACKER
	delay 18
	loopsewithpan SE_M_MORNING_SUN, SOUND_PAN_ATTACKER, 16, 6
	waitforvisualfinish
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG, 4, 4, 0, RGB_BLACK
	clearmonbg ANIM_ATTACKER
	blendoff
	delay 1
	end

Move_LUSTER_PURGE:
	loadspritegfx ANIM_TAG_WHITE_CIRCLE_OF_LIGHT
	loadspritegfx ANIM_TAG_IMPACT
	fadetobg BG_PSYCHIC
	waitbgfadeout
	createvisualtask AnimTask_FadeScreenToWhite, 5
	waitbgfadein
	monbg ANIM_ATTACKER
	setalpha 12, 8
	playsewithpan SE_M_SOLAR_BEAM, SOUND_PAN_ATTACKER
	createsprite gLusterPurgeCircleSpriteTemplate, ANIM_ATTACKER, 41, 0, 0, 0, 0
	delay 20
	createvisualtask AnimTask_BlendBattleAnimPalExclude, 5, 5, 2, 0, 16, RGB_WHITEALPHA
	createvisualtask AnimTask_BlendParticle, 5, ANIM_TAG_WHITE_CIRCLE_OF_LIGHT, 2, 0, 16, RGB_WHITEALPHA
	waitforvisualfinish
	createvisualtask AnimTask_BlendParticle, 5, ANIM_TAG_IMPACT, 0, 12, 12, RGB(0, 0, 23)
	waitforvisualfinish
	createsprite gRandomPosHitSplatSpriteTemplate, ANIM_TARGET, 3, 1, 2
	createvisualtask SoundTask_PlaySE1WithPanning, 5, SE_M_HYPER_BEAM, SOUND_PAN_TARGET
	delay 3
	createsprite gRandomPosHitSplatSpriteTemplate, ANIM_TARGET, 3, 1, 2
	createvisualtask SoundTask_PlaySE1WithPanning, 5, SE_M_HYPER_BEAM, SOUND_PAN_TARGET
	delay 3
	createsprite gRandomPosHitSplatSpriteTemplate, ANIM_TARGET, 3, 1, 2
	createvisualtask SoundTask_PlaySE1WithPanning, 5, SE_M_HYPER_BEAM, SOUND_PAN_TARGET
	delay 3
	createsprite gRandomPosHitSplatSpriteTemplate, ANIM_TARGET, 3, 1, 2
	createvisualtask SoundTask_PlaySE1WithPanning, 5, SE_M_HYPER_BEAM, SOUND_PAN_TARGET
	delay 3
	createsprite gRandomPosHitSplatSpriteTemplate, ANIM_TARGET, 3, 1, 2
	createvisualtask SoundTask_PlaySE1WithPanning, 5, SE_M_HYPER_BEAM, SOUND_PAN_TARGET
	delay 3
	createsprite gRandomPosHitSplatSpriteTemplate, ANIM_TARGET, 3, 1, 2
	createvisualtask SoundTask_PlaySE1WithPanning, 5, SE_M_HYPER_BEAM, SOUND_PAN_TARGET
	waitforvisualfinish
	createvisualtask AnimTask_BlendBattleAnimPalExclude, 5, 5, 2, 16, 0, RGB_WHITEALPHA
	createvisualtask AnimTask_HorizontalShake, 5, ANIM_TARGET, 5, 14
	waitforvisualfinish
	clearmonbg ANIM_ATTACKER
	blendoff
	call UnsetPsychicBackground
	end

Move_MIST_BALL:
	loadspritegfx ANIM_TAG_SMALL_BUBBLES
	loadspritegfx ANIM_TAG_WHITE_FEATHER
	delay 0
	playsewithpan SE_M_STRING_SHOT, SOUND_PAN_ATTACKER
	createsprite gMistBallSpriteTemplate, ANIM_TARGET, 0, 0, 0, 0, 0, 30, 0
	waitforvisualfinish
	playsewithpan SE_M_SAND_ATTACK, SOUND_PAN_TARGET
	createvisualtask AnimTask_ShakeMon, 2, ANIM_TARGET, 5, 0, 10, 0
	createsprite gComplexPaletteBlendSpriteTemplate, ANIM_ATTACKER, 0, F_PAL_BG, 1, 1, RGB(23, 16, 31), 16, RGB_WHITE, 16
	delay 0
	playsewithpan SE_M_HAZE, 0
	createvisualtask AnimTask_MistBallFog, 5
	createvisualtask AnimTask_BlendBattleAnimPal, 10, F_PAL_TARGET, 3, 0, 16, RGB_WHITE
	delay 8
	createvisualtask AnimTask_ShakeMon, 2, ANIM_TARGET, 4, 0, 70, 0
	delay 70
	createvisualtask AnimTask_BlendBattleAnimPal, 10, F_PAL_TARGET, 2, 16, 0, RGB_WHITE
	end

Move_FEATHER_DANCE:
	loadspritegfx ANIM_TAG_WHITE_FEATHER
	monbg ANIM_DEF_PARTNER
	splitbgprio_all
	playsewithpan SE_M_PETAL_DANCE, SOUND_PAN_TARGET
	delay 0
	createsprite gFallingFeatherSpriteTemplate, ANIM_TARGET, 0, 0, -16, 64, 2, 104, 11304, 32, 1
	delay 6
	createsprite gFallingFeatherSpriteTemplate, ANIM_TARGET, 0, 0, -16, 32, 2, 104, 11304, 32, 1
	createsprite gFallingFeatherSpriteTemplate, ANIM_TARGET, 0, 0, -16, 0, 2, 104, 11304, 32, 1
	delay 6
	createsprite gFallingFeatherSpriteTemplate, ANIM_TARGET, 0, 0, -16, 224, 2, 104, 11304, 32, 1
	createsprite gFallingFeatherSpriteTemplate, ANIM_TARGET, 0, 0, -16, 128, 2, 104, 11304, 32, 1
	delay 6
	createsprite gFallingFeatherSpriteTemplate, ANIM_TARGET, 0, 0, -16, 192, 2, 104, 11304, 32, 1
	createsprite gFallingFeatherSpriteTemplate, ANIM_TARGET, 0, 0, -16, 160, 2, 104, 11304, 32, 1
	delay 6
	createsprite gFallingFeatherSpriteTemplate, ANIM_TARGET, 0, 0, -16, 96, 2, 104, 11304, 32, 1
	waitforvisualfinish
	clearmonbg ANIM_DEF_PARTNER
	end

Move_TEETER_DANCE:
	loadspritegfx ANIM_TAG_MUSIC_NOTES
	loadspritegfx ANIM_TAG_DUCK
	createvisualtask AnimTask_TeeterDanceMovement, 5
	createsprite gFastFlyingMusicNotesSpriteTemplate, ANIM_ATTACKER, 2, 0, 16, -2
	playsewithpan SE_M_TEETER_DANCE, SOUND_PAN_ATTACKER
	delay 24
	createsprite gFastFlyingMusicNotesSpriteTemplate, ANIM_ATTACKER, 2, 0, 0, -2
	playsewithpan SE_M_TEETER_DANCE, SOUND_PAN_ATTACKER
	delay 24
	createsprite gFastFlyingMusicNotesSpriteTemplate, ANIM_ATTACKER, 2, 0, -16, -2
	playsewithpan SE_M_TEETER_DANCE, SOUND_PAN_ATTACKER
	delay 24
	createsprite gFastFlyingMusicNotesSpriteTemplate, ANIM_ATTACKER, 2, 1, -8, -2
	playsewithpan SE_M_TEETER_DANCE, SOUND_PAN_ATTACKER
	delay 24
	createsprite gFastFlyingMusicNotesSpriteTemplate, ANIM_ATTACKER, 2, 2, 8, -2
	playsewithpan SE_M_TEETER_DANCE, SOUND_PAN_ATTACKER
	end

Move_MUD_SPORT:
	loadspritegfx ANIM_TAG_MUD_SAND
	createvisualtask AnimTask_Splash, 2, 0, 6
	delay 24
	createsprite gMudsportMudSpriteTemplate, ANIM_TARGET, 2, 0, -4, -16
	createsprite gMudsportMudSpriteTemplate, ANIM_TARGET, 2, 0, 4, -12
	playsewithpan SE_M_DIG, SOUND_PAN_ATTACKER
	delay 32
	createsprite gMudsportMudSpriteTemplate, ANIM_TARGET, 2, 0, -3, -12
	createsprite gMudsportMudSpriteTemplate, ANIM_TARGET, 2, 0, 5, -14
	playsewithpan SE_M_DIG, SOUND_PAN_ATTACKER
	delay 32
	createsprite gMudsportMudSpriteTemplate, ANIM_TARGET, 2, 0, -5, -18
	createsprite gMudsportMudSpriteTemplate, ANIM_TARGET, 2, 0, 3, -14
	playsewithpan SE_M_DIG, SOUND_PAN_ATTACKER
	delay 16
	createsprite gMudsportMudSpriteTemplate, ANIM_TARGET, 2, 1, 220, 60
	waitplaysewithpan SE_M_BUBBLE2, 0, 15
	delay 2
	createsprite gMudsportMudSpriteTemplate, ANIM_TARGET, 2, 1, 60, 100
	waitplaysewithpan SE_M_BUBBLE2, 0, 25
	delay 2
	createsprite gMudsportMudSpriteTemplate, ANIM_TARGET, 2, 1, 140, 55
	waitplaysewithpan SE_M_BUBBLE2, 0, 14
	delay 2
	createsprite gMudsportMudSpriteTemplate, ANIM_TARGET, 2, 1, 180, 50
	waitplaysewithpan SE_M_BUBBLE2, 0, 10
	delay 2
	createsprite gMudsportMudSpriteTemplate, ANIM_TARGET, 2, 1, 20, 90
	waitplaysewithpan SE_M_BUBBLE2, 0, 22
	delay 2
	createsprite gMudsportMudSpriteTemplate, ANIM_TARGET, 2, 1, 90, 90
	waitplaysewithpan SE_M_BUBBLE2, 0, 22
	delay 2
	createsprite gMudsportMudSpriteTemplate, ANIM_TARGET, 2, 1, 160, 60
	waitplaysewithpan SE_M_BUBBLE2, 0, 15
	delay 2
	createsprite gMudsportMudSpriteTemplate, ANIM_TARGET, 2, 1, 30, 90
	waitplaysewithpan SE_M_BUBBLE2, 0, 22
	delay 2
	createsprite gMudsportMudSpriteTemplate, ANIM_TARGET, 2, 1, 120, 60
	waitplaysewithpan SE_M_BUBBLE2, 0, 15
	delay 2
	createsprite gMudsportMudSpriteTemplate, ANIM_TARGET, 2, 1, 200, 40
	waitplaysewithpan SE_M_BUBBLE2, 0, 10
	end

Move_NEEDLE_ARM:
	loadspritegfx ANIM_TAG_GREEN_SPIKE
	loadspritegfx ANIM_TAG_IMPACT
	loadspritegfx ANIM_TAG_HANDS_AND_FEET
	loopsewithpan SE_M_HORN_ATTACK, SOUND_PAN_TARGET, 2, 16
	createsprite gNeedleArmSpikeSpriteTemplate, ANIM_TARGET, 2, 1, 0, 0, -32, 16
	delay 2
	createsprite gNeedleArmSpikeSpriteTemplate, ANIM_TARGET, 2, 1, 0, 22, -22, 16
	delay 2
	createsprite gNeedleArmSpikeSpriteTemplate, ANIM_TARGET, 2, 1, 0, 30, 0, 16
	delay 2
	createsprite gNeedleArmSpikeSpriteTemplate, ANIM_TARGET, 2, 1, 0, 20, 20, 16
	delay 2
	createsprite gNeedleArmSpikeSpriteTemplate, ANIM_TARGET, 2, 1, 0, 0, 28, 16
	delay 2
	createsprite gNeedleArmSpikeSpriteTemplate, ANIM_TARGET, 2, 1, 0, -19, 19, 16
	delay 2
	createsprite gNeedleArmSpikeSpriteTemplate, ANIM_TARGET, 2, 1, 0, -27, 0, 16
	delay 2
	createsprite gNeedleArmSpikeSpriteTemplate, ANIM_TARGET, 2, 1, 0, -18, -18, 16
	delay 2
	createsprite gNeedleArmSpikeSpriteTemplate, ANIM_TARGET, 2, 1, 0, 0, -25, 16
	delay 2
	createsprite gNeedleArmSpikeSpriteTemplate, ANIM_TARGET, 2, 1, 0, 17, -17, 16
	delay 2
	createsprite gNeedleArmSpikeSpriteTemplate, ANIM_TARGET, 2, 1, 0, 23, 0, 16
	delay 2
	createsprite gNeedleArmSpikeSpriteTemplate, ANIM_TARGET, 2, 1, 0, 16, 16, 16
	waitforvisualfinish
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_TARGET, 4, 0, 18, 1
	createsprite gBasicHitSplatSpriteTemplate, ANIM_TARGET, 3, 0, 0, ANIM_TARGET, 1
	createsprite gFistFootSpriteTemplate, ANIM_TARGET, 4, 0, 0, 8, 1, 0
	playsewithpan SE_M_VITAL_THROW2, SOUND_PAN_TARGET
	createsprite gNeedleArmSpikeSpriteTemplate, ANIM_TARGET, 2, 1, 1, 0, -24, 10
	createsprite gNeedleArmSpikeSpriteTemplate, ANIM_TARGET, 2, 1, 1, 17, -17, 10
	createsprite gNeedleArmSpikeSpriteTemplate, ANIM_TARGET, 2, 1, 1, 24, 0, 10
	createsprite gNeedleArmSpikeSpriteTemplate, ANIM_TARGET, 2, 1, 1, 17, 17, 10
	createsprite gNeedleArmSpikeSpriteTemplate, ANIM_TARGET, 2, 1, 1, 0, 24, 10
	createsprite gNeedleArmSpikeSpriteTemplate, ANIM_TARGET, 2, 1, 1, -17, 17, 10
	createsprite gNeedleArmSpikeSpriteTemplate, ANIM_TARGET, 2, 1, 1, -24, 0, 10
	createsprite gNeedleArmSpikeSpriteTemplate, ANIM_TARGET, 2, 1, 1, -17, -17, 10
	end

Move_SLACK_OFF:
	loadspritegfx ANIM_TAG_BLUE_STAR
	createvisualtask AnimTask_SlackOffSquish, 2, ANIM_ATTACKER
	playsewithpan SE_M_YAWN, SOUND_PAN_ATTACKER
	waitforvisualfinish
	call HealingEffect
	waitforvisualfinish
	end

Move_CRUSH_CLAW:
	loadspritegfx ANIM_TAG_BLUE_LIGHT_WALL
	loadspritegfx ANIM_TAG_CLAW_SLASH
	loadspritegfx ANIM_TAG_TORN_METAL
	monbg ANIM_TARGET
	setalpha 12, 8
	createsprite gHorizontalLungeSpriteTemplate, ANIM_ATTACKER, 2, 6, 4
	delay 4
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_TARGET, 2, 0, 18, 1
	createsprite gClawSlashSpriteTemplate, ANIM_TARGET, 2, -10, -10, 0
	createsprite gClawSlashSpriteTemplate, ANIM_TARGET, 2, -10, 10, 0
	playsewithpan SE_M_RAZOR_WIND, SOUND_PAN_TARGET
	delay 12
	createsprite gClawSlashSpriteTemplate, ANIM_TARGET, 2, 10, -10, 1
	createsprite gClawSlashSpriteTemplate, ANIM_TARGET, 2, 10, 10, 1
	playsewithpan SE_M_RAZOR_WIND, SOUND_PAN_TARGET
	waitforvisualfinish
	waitforvisualfinish  @ Redundant
	blendoff
	clearmonbg ANIM_TARGET
	end

Move_AROMATHERAPY:
	playsewithpan SE_M_PETAL_DANCE, 0
	loadspritegfx ANIM_TAG_FLOWER
	loadspritegfx ANIM_TAG_THIN_RING
	loadspritegfx ANIM_TAG_SPARKLE_2
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 0, F_PAL_BG, 0, 0, 7, RGB(13, 31, 12)
	delay 1
	monbg ANIM_ATTACKER
	delay 1
	createsprite gAromatherapySmallFlowerSpriteTemplate, ANIM_ATTACKER, 0, 24, 16, 0, 2, 2, 0, 0
	createsprite gAromatherapySmallFlowerSpriteTemplate, ANIM_ATTACKER, 66, 64, 24, 0, 3, 1, 1, 0
	createsprite gAromatherapyBigFlowerSpriteTemplate, ANIM_ATTACKER, 0, 16, 24, 0, 2, 1, 0, 0
	delay 20
	createsprite gAromatherapySmallFlowerSpriteTemplate, ANIM_ATTACKER, 66, 48, 12, 0, 4, 3, 1, 0
	createsprite gAromatherapySmallFlowerSpriteTemplate, ANIM_ATTACKER, 0, 100, 16, 0, 3, 2, 0, 0
	createsprite gAromatherapySmallFlowerSpriteTemplate, ANIM_ATTACKER, 0, 74, 24, 180, 3, 2, 0, 0
	delay 10
	createsprite gAromatherapySmallFlowerSpriteTemplate, ANIM_ATTACKER, 66, 80, 30, 0, 4, 1, 1, 0
	createsprite gAromatherapySmallFlowerSpriteTemplate, ANIM_ATTACKER, 0, 128, 12, 0, 3, 3, 0, 0
	createsprite gAromatherapyBigFlowerSpriteTemplate, ANIM_ATTACKER, 0, 90, 16, 0, 2, 1, 0, 0
	waitforvisualfinish
	clearmonbg ANIM_ATTACKER
	delay 1
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 0, F_PAL_BG, 0, 7, 0, RGB(13, 31, 12)
	delay 1
	playsewithpan SE_M_STAT_INCREASE, SOUND_PAN_ATTACKER
	createvisualtask AnimTask_StatusClearedEffect, 2, 1
	waitforvisualfinish
	playsewithpan SE_M_MORNING_SUN, SOUND_PAN_ATTACKER
	createsprite gSparklingStarsSpriteTemplate, ANIM_ATTACKER, 16, -15, 0, 0, 0, 32, 60, 1
	delay 8
	createsprite gSparklingStarsSpriteTemplate, ANIM_ATTACKER, 16, 12, -5, 0, 0, 32, 60, 1
	waitforvisualfinish
	playsewithpan SE_SHINY, SOUND_PAN_ATTACKER
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 0, F_PAL_BG | F_PAL_ATK_SIDE | F_PAL_ANIM_1, 3, 10, 0, RGB(13, 31, 12)
	createsprite gBlendThinRingExpandingSpriteTemplate, ANIM_ATTACKER, 16, 0, 0, 0, 1
	waitforvisualfinish
	end

Move_FAKE_TEARS:
	loadspritegfx ANIM_TAG_SMALL_BUBBLES
	loadspritegfx ANIM_TAG_THOUGHT_BUBBLE
	loadspritegfx ANIM_TAG_MUSIC_NOTES
	createvisualtask AnimTask_BlendParticle, 5, ANIM_TAG_SMALL_BUBBLES, 0, 4, 4, RGB(12, 11, 31)
	waitforvisualfinish
	createvisualtask AnimTask_RockMonBackAndForth, 5, ANIM_ATTACKER, 2, 1
	loopsewithpan SE_M_TAIL_WHIP, SOUND_PAN_ATTACKER, 12, 4
	delay 8
	createsprite gTearDropSpriteTemplate, ANIM_ATTACKER, 2, 0, 0
	createsprite gTearDropSpriteTemplate, ANIM_ATTACKER, 2, 0, 1
	delay 8
	createsprite gTearDropSpriteTemplate, ANIM_ATTACKER, 2, 0, 2
	createsprite gTearDropSpriteTemplate, ANIM_ATTACKER, 2, 0, 3
	delay 8
	createsprite gTearDropSpriteTemplate, ANIM_ATTACKER, 2, 0, 0
	createsprite gTearDropSpriteTemplate, ANIM_ATTACKER, 2, 0, 1
	delay 8
	createsprite gTearDropSpriteTemplate, ANIM_ATTACKER, 2, 0, 2
	createsprite gTearDropSpriteTemplate, ANIM_ATTACKER, 2, 0, 3
	waitforvisualfinish
	end

Move_AIR_CUTTER:
	loadspritegfx ANIM_TAG_AIR_WAVE
	loadspritegfx ANIM_TAG_CUT
	loadspritegfx ANIM_TAG_IMPACT
	delay 0
	monbg ANIM_DEF_PARTNER
	setalpha 12, 8
	delay 0
	createvisualtask AnimTask_AirCutterProjectile, 2, 32, -24, 6 * 256, 2, 128  @ 6 * 256 == Q_8_8(6)
	waitforvisualfinish
	playsewithpan SE_M_CUT, SOUND_PAN_TARGET
	createsprite gAirCutterSliceSpriteTemplate, ANIM_ATTACKER, 2, 40, -32, 0, 2
	delay 5
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_TARGET, 2, 0, 8, 1
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_DEF_PARTNER, 2, 0, 8, 1
	waitforvisualfinish
	blendoff
	clearmonbg ANIM_DEF_PARTNER
	delay 0
	end

Move_ODOR_SLEUTH:
	monbg ANIM_TARGET
	createvisualtask AnimTask_OdorSleuthMovement, 5
	delay 24
	createsprite gHorizontalLungeSpriteTemplate, ANIM_ATTACKER, 2, 3, 4
	playsewithpan SE_M_SWAGGER, SOUND_PAN_ATTACKER
	delay 6
	createsprite gHorizontalLungeSpriteTemplate, ANIM_ATTACKER, 2, 3, 4
	playsewithpan SE_M_SWAGGER, SOUND_PAN_ATTACKER
	waitforvisualfinish
	clearmonbg ANIM_TARGET
	delay 1
	createsprite gComplexPaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG, 3, 1, RGB_WHITEALPHA, 16, RGB_WHITEALPHA, 0
	playsewithpan SE_M_LEER, SOUND_PAN_ATTACKER
	end

Move_GRASS_WHISTLE:
	loadspritegfx ANIM_TAG_MUSIC_NOTES
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG, 2, 0, 4, RGB(18, 31, 12)
	waitforvisualfinish
	createvisualtask AnimTask_MusicNotesRainbowBlend, 2
	waitforvisualfinish
	panse SE_M_GRASSWHISTLE, SOUND_PAN_ATTACKER, SOUND_PAN_TARGET, +2, 0
	createsprite gWavyMusicNotesSpriteTemplate, ANIM_TARGET, 2, 7, 1, 0
	delay 5
	createsprite gWavyMusicNotesSpriteTemplate, ANIM_TARGET, 2, 6, 1, 0
	delay 5
	createsprite gWavyMusicNotesSpriteTemplate, ANIM_TARGET, 2, 1, 1, 0
	delay 5
	createsprite gWavyMusicNotesSpriteTemplate, ANIM_TARGET, 2, 2, 1, 0
	delay 5
	createsprite gWavyMusicNotesSpriteTemplate, ANIM_TARGET, 2, 3, 1, 0
	delay 4
	createsprite gWavyMusicNotesSpriteTemplate, ANIM_TARGET, 2, 2, 1, 0
	delay 4
	createsprite gWavyMusicNotesSpriteTemplate, ANIM_TARGET, 2, 5, 1, 0
	delay 4
	createsprite gWavyMusicNotesSpriteTemplate, ANIM_TARGET, 2, 6, 1, 0
	delay 4
	createsprite gWavyMusicNotesSpriteTemplate, ANIM_TARGET, 2, 2, 1, 0
	delay 4
	createsprite gWavyMusicNotesSpriteTemplate, ANIM_TARGET, 2, 2, 1, 0
	delay 4
	createsprite gWavyMusicNotesSpriteTemplate, ANIM_TARGET, 2, 1, 1, 0
	delay 4
	createsprite gWavyMusicNotesSpriteTemplate, ANIM_TARGET, 2, 5, 1, 0
	delay 4
	waitforvisualfinish
	createvisualtask AnimTask_MusicNotesClearRainbowBlend, 2
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG, 4, 4, 0, RGB(18, 31, 12)
	waitforvisualfinish
	end

Move_TICKLE:
	loadspritegfx ANIM_TAG_EYE_SPARKLE
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_ATTACKER, 0, 0, 16, RGB_BLACK
	waitforvisualfinish
	createsprite gEyeSparkleSpriteTemplate, ANIM_ATTACKER, 0, -16, -8
	createsprite gEyeSparkleSpriteTemplate, ANIM_ATTACKER, 0, 16, -8
	playsewithpan SE_M_DETECT, SOUND_PAN_ATTACKER
	waitforvisualfinish
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_ATTACKER, 0, 16, 0, RGB_BLACK
	waitforvisualfinish
	delay 20
	createvisualtask AnimTask_SwayMon, 3, 0, 6, 1280, 3, ANIM_ATTACKER
	delay 12
	createvisualtask AnimTask_RockMonBackAndForth, 3, ANIM_TARGET, 6, 2
	loopsewithpan SE_M_TAIL_WHIP, SOUND_PAN_TARGET, 8, 8
	waitforvisualfinish
	end

Move_WATER_SPOUT:
	loadspritegfx ANIM_TAG_GLOWY_BLUE_ORB
	loadspritegfx ANIM_TAG_WATER_IMPACT
	monbg ANIM_DEF_PARTNER
	setalpha 12, 8
	createvisualtask AnimTask_WaterSpoutLaunch, 5
	playsewithpan SE_M_HEADBUTT, SOUND_PAN_ATTACKER
	delay 44
	playsewithpan SE_M_DIVE, SOUND_PAN_ATTACKER
	waitforvisualfinish
	delay 16
	createvisualtask AnimTask_WaterSpoutRain, 5
	playsewithpan SE_M_SURF, SOUND_PAN_TARGET
	clearmonbg ANIM_DEF_PARTNER
	blendoff
	end

Move_SHADOW_PUNCH:
	loadspritegfx ANIM_TAG_IMPACT
	loadspritegfx ANIM_TAG_HANDS_AND_FEET
	fadetobg BG_GHOST
	waitbgfadein
	monbg ANIM_ATK_PARTNER
	setalpha 9, 8
	createvisualtask AnimTask_AttackerPunchWithTrace, 2, RGB_BLACK, 13
	playsewithpan SE_M_JUMP_KICK, SOUND_PAN_ATTACKER
	delay 6
	createsprite gBasicHitSplatSpriteTemplate, ANIM_TARGET, 3, 0, 0, ANIM_TARGET, 1
	createsprite gFistFootSpriteTemplate, ANIM_TARGET, 4, 0, 0, 8, 1, 0
	playsewithpan SE_M_COMET_PUNCH, SOUND_PAN_TARGET
	createvisualtask AnimTask_ShakeMon, 2, ANIM_TARGET, 3, 0, 6, 1
	waitforvisualfinish
	clearmonbg ANIM_ATK_PARTNER
	blendoff
	restorebg
	waitbgfadein
	end

Move_EXTRASENSORY:
	call SetPsychicBackground
	monbg ANIM_DEF_PARTNER
	setalpha 12, 8
	createvisualtask AnimTask_BlendMonInAndOut, 5, ANIM_ATTACKER, RGB(27, 27, 0), 12, 1, 1
	createvisualtask AnimTask_ExtrasensoryDistortion, 5, 0
	playsewithpan SE_M_BIND, SOUND_PAN_TARGET
	waitforvisualfinish
	createvisualtask AnimTask_BlendMonInAndOut, 5, ANIM_ATTACKER, RGB(27, 27, 0), 12, 1, 1
	createvisualtask AnimTask_ExtrasensoryDistortion, 5, 1
	playsewithpan SE_M_BIND, SOUND_PAN_TARGET
	waitforvisualfinish
	createvisualtask AnimTask_TransparentCloneGrowAndShrink, 5, ANIM_ATTACKER
	createvisualtask AnimTask_ExtrasensoryDistortion, 5, 2
	playsewithpan SE_M_LEER, SOUND_PAN_ATTACKER
	waitforvisualfinish
	blendoff
	clearmonbg ANIM_DEF_PARTNER
	call UnsetPsychicBackground
	end

Move_AERIAL_ACE:
	loadspritegfx ANIM_TAG_CUT
	monbg ANIM_TARGET
	setalpha 12, 8
	createvisualtask AnimTask_TranslateMonEllipticalRespectSide, 2, ANIM_ATTACKER, 24, 6, 1, 5
	createvisualtask AnimTask_TraceMonBlended, 2, 0, 4, 7, 3
	createsprite gCuttingSliceSpriteTemplate, ANIM_ATTACKER, 2, 40, -32, 0
	playsewithpan SE_M_RAZOR_WIND2, SOUND_PAN_ATTACKER
	delay 5
	createvisualtask AnimTask_ShakeMon, 2, ANIM_TARGET, 0, 3, 10, 1
	createsprite gComplexPaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG | F_PAL_BATTLERS, 3, 1, RGB_BLACK, 10, RGB_BLACK, 0
	playsewithpan SE_M_RAZOR_WIND, SOUND_PAN_TARGET
	waitforvisualfinish
	clearmonbg ANIM_TARGET
	blendoff
	end

Move_IRON_DEFENSE:
	loopsewithpan SE_SHINY, SOUND_PAN_ATTACKER, 28, 2
	createvisualtask AnimTask_MetallicShine, 5, 0, 0, 0
	createsprite gComplexPaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG, 8, 2, RGB_WHITEALPHA, 14, RGB_WHITEALPHA, 0
	waitforvisualfinish
	end

Move_BLOCK:
	loadspritegfx ANIM_TAG_X_SIGN
	createsprite gBlockXSpriteTemplate, ANIM_TARGET, 66
	playsewithpan SE_M_SWAGGER, SOUND_PAN_TARGET
	end

Move_HOWL:
	loadspritegfx ANIM_TAG_NOISE_LINE
	createvisualtask AnimTask_DeepInhale, 2, 0
	delay 12
	call RoarEffect
	createvisualtask SoundTask_PlayCryHighPitch, 2, ANIM_ATTACKER, 3
	waitforvisualfinish
	delay 30
	end

Move_BULK_UP:
	loadspritegfx ANIM_TAG_BREATH
	createvisualtask AnimTask_GrowAndShrink, 2
	playsewithpan SE_M_SWAGGER, SOUND_PAN_ATTACKER
	waitforvisualfinish
	createsprite gBreathPuffSpriteTemplate, ANIM_ATTACKER, 2
	loopsewithpan SE_M_SWAGGER, SOUND_PAN_ATTACKER, 4, 2
	waitforvisualfinish
	end

Move_COVET:
	loadspritegfx ANIM_TAG_MAGENTA_HEART
	loadspritegfx ANIM_TAG_ITEM_BAG
	createvisualtask AnimTask_RockMonBackAndForth, 5, ANIM_ATTACKER, 2, 0
	createsprite gMagentaHeartSpriteTemplate, ANIM_ATTACKER, 3, 0, 20
	playsewithpan SE_M_CHARM, SOUND_PAN_ATTACKER
	delay 15
	createsprite gMagentaHeartSpriteTemplate, ANIM_ATTACKER, 3, -20, 20
	playsewithpan SE_M_CHARM, SOUND_PAN_ATTACKER
	delay 15
	createsprite gMagentaHeartSpriteTemplate, ANIM_ATTACKER, 3, 20, 20
	playsewithpan SE_M_CHARM, SOUND_PAN_ATTACKER
	waitforvisualfinish
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_TARGET, 2, 0, 8, 1
	loopsewithpan SE_M_DIZZY_PUNCH, SOUND_PAN_TARGET, 4, 3
	end

Move_VOLT_TACKLE:
	loadspritegfx ANIM_TAG_SPARK
	loadspritegfx ANIM_TAG_CIRCLE_OF_LIGHT
	loadspritegfx ANIM_TAG_ELECTRICITY
	monbg ANIM_ATTACKER
	setalpha 12, 8
	createvisualtask AnimTask_BlendBattleAnimPal, 10, F_PAL_BG, 0, 0, 8, RGB_BLACK
	waitforvisualfinish
	createsprite gVoltTackleOrbSlideSpriteTemplate, ANIM_ATTACKER, 1
	playsewithpan SE_M_CHARGE, SOUND_PAN_ATTACKER
	waitforvisualfinish
	clearmonbg ANIM_ATTACKER
	blendoff
	delay 8
	createvisualtask AnimTask_VoltTackleBolt, 5, 0
	playsewithpan SE_M_THUNDERBOLT, SOUND_PAN_ATTACKER
	waitforvisualfinish
	createvisualtask AnimTask_VoltTackleBolt, 5, 1
	playsewithpan SE_M_THUNDERBOLT, SOUND_PAN_TARGET
	waitforvisualfinish
	createvisualtask AnimTask_VoltTackleBolt, 5, 2
	playsewithpan SE_M_THUNDERBOLT, SOUND_PAN_ATTACKER
	waitforvisualfinish
	createvisualtask AnimTask_VoltTackleBolt, 5, 3
	playsewithpan SE_M_THUNDERBOLT, SOUND_PAN_TARGET
	waitforvisualfinish
	createvisualtask AnimTask_VoltTackleBolt, 5, 4
	playsewithpan SE_M_THUNDERBOLT, SOUND_PAN_ATTACKER
	delay 8
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_TARGET, 10, 0, 18, 1
	playsewithpan SE_M_SELF_DESTRUCT, SOUND_PAN_TARGET
	createsprite gElectricPuffSpriteTemplate, ANIM_ATTACKER, 2, 1, 16, 16
	delay 2
	createsprite gElectricPuffSpriteTemplate, ANIM_ATTACKER, 2, 1, -16, -16
	delay 8
	createvisualtask AnimTask_VoltTackleAttackerReappear, 5
	waitforvisualfinish
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_ATTACKER, 3, 0, 9, 1
	playsewithpan SE_M_THUNDERBOLT2, SOUND_PAN_ATTACKER
	createsprite gElectricPuffSpriteTemplate, ANIM_ATTACKER, 2, 0, 16, 16
	delay 2
	createsprite gElectricPuffSpriteTemplate, ANIM_ATTACKER, 2, 0, -16, -16
	waitforvisualfinish
	createvisualtask AnimTask_BlendBattleAnimPal, 10, F_PAL_BG, 0, 8, 0, RGB_BLACK
	waitforvisualfinish
	end

Move_WATER_SPORT:
	loadspritegfx ANIM_TAG_GLOWY_BLUE_ORB
	createvisualtask AnimTask_WaterSport, 5
	delay 8
	playsewithpan SE_M_SURF, SOUND_PAN_ATTACKER
	delay 44
	playsewithpan SE_M_SURF, SOUND_PAN_ATTACKER
	delay 44
	playsewithpan SE_M_SURF, SOUND_PAN_ATTACKER
	delay 44
	panse SE_M_SURF, SOUND_PAN_ATTACKER, SOUND_PAN_TARGET, +2, 0
	end

Move_CALM_MIND:
	loadspritegfx ANIM_TAG_THIN_RING
	monbg ANIM_ATK_PARTNER
	createvisualtask AnimTask_BlendBattleAnimPalExclude, 5, ANIM_ATTACKER, 0, 0, 16, RGB_BLACK
	waitforvisualfinish
	createvisualtask AnimTask_SetAllNonAttackersInvisiblity, 5, TRUE
	waitforvisualfinish
	createsprite gThinRingShrinkingSpriteTemplate, ANIM_ATTACKER, 40, 0, 0, 0, 0
	playsewithpan SE_M_SUPERSONIC, SOUND_PAN_ATTACKER
	delay 14
	createsprite gThinRingShrinkingSpriteTemplate, ANIM_ATTACKER, 40, 0, 0, 0, 0
	playsewithpan SE_M_SUPERSONIC, SOUND_PAN_ATTACKER
	delay 14
	createsprite gThinRingShrinkingSpriteTemplate, ANIM_ATTACKER, 40, 0, 0, 0, 0
	playsewithpan SE_M_SUPERSONIC, SOUND_PAN_ATTACKER
	waitforvisualfinish
	createvisualtask AnimTask_SetAllNonAttackersInvisiblity, 5, FALSE
	visible ANIM_ATTACKER  @ Redundant
	waitforvisualfinish
	createvisualtask AnimTask_BlendBattleAnimPalExclude, 5, ANIM_ATTACKER, 0, 16, 0, RGB_BLACK
	waitforvisualfinish
	clearmonbg ANIM_ATK_PARTNER
	end

Move_LEAF_BLADE:
	loadspritegfx ANIM_TAG_LEAF
	loadspritegfx ANIM_TAG_CROSS_IMPACT
	createvisualtask AnimTask_LeafBlade, 5
	delay 2
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_TARGET, 2, 0, 8, 1
	playsewithpan SE_M_CUT, SOUND_PAN_TARGET
	delay 50
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_TARGET, 2, 0, 8, 1
	playsewithpan SE_M_CUT, SOUND_PAN_TARGET
	delay 50
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_TARGET, 2, 0, 8, 1
	playsewithpan SE_M_CUT, SOUND_PAN_TARGET
	waitforvisualfinish
	monbg ANIM_TARGET
	setalpha 12, 8
	delay 12
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_TARGET, 8, 0, 18, 1
	createsprite gCrossImpactSpriteTemplate, ANIM_TARGET, 2, 0, 0, 1, 36
	playsewithpan SE_M_LEER, SOUND_PAN_TARGET
	waitforvisualfinish
	clearmonbg ANIM_TARGET
	blendoff
	end

Move_DRAGON_DANCE:
	loadspritegfx ANIM_TAG_HOLLOW_ORB
	monbg ANIM_ATTACKER
	splitbgprio ANIM_ATTACKER
	delay 1
	createvisualtask AnimTask_DragonDanceWaver, 5
	playsewithpan SE_M_TELEPORT, SOUND_PAN_ATTACKER
	delay 8
	createvisualtask AnimTask_BlendPalInAndOutByTag, 5, ANIM_TAG_HOLLOW_ORB, RGB(0, 0, 19), 14, 0, 3
	createsprite gDragonDanceOrbSpriteTemplate, ANIM_ATTACKER, 2, 0
	createsprite gDragonDanceOrbSpriteTemplate, ANIM_ATTACKER, 2, 43
	createsprite gDragonDanceOrbSpriteTemplate, ANIM_ATTACKER, 2, 85
	createsprite gDragonDanceOrbSpriteTemplate, ANIM_ATTACKER, 2, 128
	createsprite gDragonDanceOrbSpriteTemplate, ANIM_ATTACKER, 2, 170
	createsprite gDragonDanceOrbSpriteTemplate, ANIM_ATTACKER, 2, 213
	delay 30
	playsewithpan SE_M_TELEPORT, SOUND_PAN_ATTACKER
	delay 30
	playsewithpan SE_M_TELEPORT, SOUND_PAN_ATTACKER
	waitforvisualfinish
	clearmonbg ANIM_ATTACKER
	delay 1
	end

Move_SHOCK_WAVE:
	loadspritegfx ANIM_TAG_ELECTRIC_ORBS
	loadspritegfx ANIM_TAG_CIRCLE_OF_LIGHT
	loadspritegfx ANIM_TAG_SPARK
	loadspritegfx ANIM_TAG_LIGHTNING
	monbg ANIM_ATTACKER
	setalpha 12, 8
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG, 2, 0, 4, RGB_BLACK
	waitforvisualfinish
	createvisualtask AnimTask_ElectricChargingParticles, 2, ANIM_ATTACKER, 20, 0, 2
	playsewithpan SE_M_CHARGE, SOUND_PAN_ATTACKER
	delay 12
	createsprite gGrowingShockWaveOrbSpriteTemplate, ANIM_ATTACKER, 2
	delay 30
	createvisualtask AnimTask_ShockWaveProgressingBolt, 5
	delay 12
	waitforvisualfinish
	createvisualtask AnimTask_ShockWaveLightning, 5
	playsewithpan SE_M_TRI_ATTACK2, SOUND_PAN_TARGET
	waitforvisualfinish
	createvisualtask AnimTask_ShakeMon, 2, ANIM_TARGET, 0, 6, 18, 1
	createvisualtask AnimTask_BlendBattleAnimPal, 5, F_PAL_BG, 3, 16, 0, RGB_WHITE
	createvisualtask AnimTask_BlendBattleAnimPal, 5, F_PAL_TARGET, 0, 16, 16, RGB_BLACK
	delay 4
	createvisualtask AnimTask_BlendBattleAnimPal, 5, F_PAL_TARGET, 0, 0, 0, RGB_BLACK
	waitforvisualfinish
	clearmonbg ANIM_ATTACKER
	blendoff
	end

Move_HARDEN:
	loopsewithpan SE_M_HARDEN, SOUND_PAN_ATTACKER, 28, 2
	createvisualtask AnimTask_MetallicShine, 5, 0, 0, 0
	waitforvisualfinish
	end

Move_BELLY_DRUM:
	loadspritegfx ANIM_TAG_MUSIC_NOTES
	loadspritegfx ANIM_TAG_PURPLE_HAND_OUTLINE
	createvisualtask AnimTask_MusicNotesRainbowBlend, 2
	waitforvisualfinish
	call BellyDrumRight
	createsprite gSlowFlyingMusicNotesSpriteTemplate, ANIM_ATTACKER, 2, 0, 0, 0, 0
	playsewithpan SE_M_BELLY_DRUM, SOUND_PAN_ATTACKER
	delay 15
	call BellyDrumLeft
	createsprite gSlowFlyingMusicNotesSpriteTemplate, ANIM_ATTACKER, 2, 1, 1, 1, 0
	playsewithpan SE_M_BELLY_DRUM, SOUND_PAN_ATTACKER
	delay 15
	call BellyDrumRight
	createsprite gSlowFlyingMusicNotesSpriteTemplate, ANIM_ATTACKER, 2, 0, 3, 3, 128
	playsewithpan SE_M_BELLY_DRUM, SOUND_PAN_ATTACKER
	delay 7
	call BellyDrumLeft
	createsprite gSlowFlyingMusicNotesSpriteTemplate, ANIM_ATTACKER, 2, 1, 2, 0, 128
	playsewithpan SE_M_BELLY_DRUM, SOUND_PAN_ATTACKER
	delay 7
	call BellyDrumRight
	createsprite gSlowFlyingMusicNotesSpriteTemplate, ANIM_ATTACKER, 2, 0, 1, 1, 0
	playsewithpan SE_M_BELLY_DRUM, SOUND_PAN_ATTACKER
	delay 7
	call BellyDrumLeft
	createsprite gSlowFlyingMusicNotesSpriteTemplate, ANIM_ATTACKER, 2, 1, 0, 3, 0
	playsewithpan SE_M_BELLY_DRUM, SOUND_PAN_ATTACKER
	waitforvisualfinish
	createvisualtask AnimTask_MusicNotesClearRainbowBlend, 2
	waitforvisualfinish
	end

BellyDrumLeft:
	createsprite gBellyDrumHandSpriteTemplate, ANIM_ATTACKER, 3, 0
	createvisualtask AnimTask_ShakeMon, 2, ANIM_ATTACKER, 0, 8, 2, 1
	return

BellyDrumRight:
	createsprite gBellyDrumHandSpriteTemplate, ANIM_ATTACKER, 3, 1
	createvisualtask AnimTask_ShakeMon, 2, ANIM_ATTACKER, 0, 8, 2, 1
	return

Move_MIND_READER:
	loadspritegfx ANIM_TAG_TEAL_ALERT
	loadspritegfx ANIM_TAG_OPENING_EYE
	loadspritegfx ANIM_TAG_ROUND_WHITE_HALO
	monbg 4
	playsewithpan SE_M_CONFUSE_RAY, SOUND_PAN_TARGET
	createsprite gOpeningEyeSpriteTemplate, ANIM_ATTACKER, 5, 0, 0, 1, 0
	createsprite gWhiteHaloSpriteTemplate, ANIM_ATTACKER, 5
	delay 40
	playsewithpan SE_M_LEER, SOUND_PAN_TARGET
	createvisualtask AnimTask_BlendColorCycle, 2, F_PAL_BG, 1, 2, 0, 10, RGB_BLACK
	call MindReaderEyeSpikeEffect
	waitforvisualfinish
	clearmonbg 4
	end

MindReaderEyeSpikeEffect:
	createsprite gTealAlertSpriteTemplate, ANIM_ATTACKER, 4, 70, 0, 6
	createsprite gTealAlertSpriteTemplate, ANIM_ATTACKER, 4, 40, 40, 6
	createsprite gTealAlertSpriteTemplate, ANIM_ATTACKER, 4, 10, -60, 6
	createsprite gTealAlertSpriteTemplate, ANIM_ATTACKER, 4, -50, -40, 6
	createsprite gTealAlertSpriteTemplate, ANIM_ATTACKER, 4, -40, 40, 6
	createsprite gTealAlertSpriteTemplate, ANIM_ATTACKER, 4, 50, -50, 6
	delay 2
	createsprite gTealAlertSpriteTemplate, ANIM_ATTACKER, 4, 50, -30, 6
	createsprite gTealAlertSpriteTemplate, ANIM_ATTACKER, 4, 60, 10, 6
	createsprite gTealAlertSpriteTemplate, ANIM_ATTACKER, 4, 0, 60, 6
	createsprite gTealAlertSpriteTemplate, ANIM_ATTACKER, 4, 0, -40, 6
	createsprite gTealAlertSpriteTemplate, ANIM_ATTACKER, 4, -60, 20, 6
	createsprite gTealAlertSpriteTemplate, ANIM_ATTACKER, 4, -60, -30, 6
	delay 2
	createsprite gTealAlertSpriteTemplate, ANIM_ATTACKER, 4, -50, 50, 6
	createsprite gTealAlertSpriteTemplate, ANIM_ATTACKER, 4, -60, 20, 6
	createsprite gTealAlertSpriteTemplate, ANIM_ATTACKER, 4, -40, -40, 6
	createsprite gTealAlertSpriteTemplate, ANIM_ATTACKER, 4, 20, -60, 6
	createsprite gTealAlertSpriteTemplate, ANIM_ATTACKER, 4, 50, -50, 6
	createsprite gTealAlertSpriteTemplate, ANIM_ATTACKER, 4, 35, 40, 6
	delay 2
	return

Move_ICE_PUNCH:
	monbg ANIM_DEF_PARTNER
	setalpha 12, 8
	loadspritegfx ANIM_TAG_ICE_CRYSTALS
	loadspritegfx ANIM_TAG_IMPACT
	loadspritegfx ANIM_TAG_HANDS_AND_FEET
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG, 1, 0, 7, RGB_BLACK
	createvisualtask AnimTask_BlendBattleAnimPal, 10, F_PAL_TARGET, 2, 0, 9, RGB(12, 26, 31)
	delay 20
	playsewithpan SE_M_STRING_SHOT, SOUND_PAN_TARGET
	createsprite gIceCrystalSpiralInwardSmall, ANIM_ATTACKER, 2, 0
	createsprite gIceCrystalSpiralInwardSmall, ANIM_ATTACKER, 2, 64
	createsprite gIceCrystalSpiralInwardSmall, ANIM_ATTACKER, 2, 128
	createsprite gIceCrystalSpiralInwardSmall, ANIM_ATTACKER, 2, 192
	delay 5
	createsprite gIceCrystalSpiralInwardLarge, ANIM_ATTACKER, 2, 32
	createsprite gIceCrystalSpiralInwardLarge, ANIM_ATTACKER, 2, 96
	createsprite gIceCrystalSpiralInwardLarge, ANIM_ATTACKER, 2, 160
	createsprite gIceCrystalSpiralInwardLarge, ANIM_ATTACKER, 2, 224
	delay 17
	createsprite gFistFootSpriteTemplate, ANIM_ATTACKER, 4, 0, -10, 8, 1, 0
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 3, 0, -10, ANIM_TARGET, 1
	playsewithpan SE_M_COMET_PUNCH, SOUND_PAN_TARGET
	delay 2
	createvisualtask AnimTask_ShakeMon, 5, ANIM_TARGET, 0, 5, 3, 1
	waitforvisualfinish
	delay 15
	call IceCrystalEffectShort
	delay 5
	createvisualtask AnimTask_BlendBattleAnimPal, 10, F_PAL_TARGET, 2, 9, 0, RGB(12, 26, 31)
	waitforvisualfinish
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG, 0, 7, 0, RGB_BLACK
	waitforvisualfinish
	clearmonbg ANIM_DEF_PARTNER
	blendoff
	end

Move_REST:
	playsewithpan SE_M_SNORE, SOUND_PAN_ATTACKER
	loadspritegfx ANIM_TAG_LETTER_Z
	createsprite gSleepLetterZSpriteTemplate, ANIM_ATTACKER, 2, 4, -10, 16, 0, 0
	delay 20
	createsprite gSleepLetterZSpriteTemplate, ANIM_ATTACKER, 2, 4, -10, 16, 0, 0
	delay 20
	createsprite gSleepLetterZSpriteTemplate, ANIM_ATTACKER, 2, 4, -10, 16, 0, 0
	waitforvisualfinish
	end

Move_CONFUSION:
	monbg ANIM_DEF_PARTNER
	call SetPsychicBackground
	setalpha 8, 8
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_ATTACKER, 1, 0, 10, 1
	createvisualtask AnimTask_BlendColorCycle, 2, F_PAL_ATTACKER, 0, 2, 0, 8, RGB_WHITE
	waitforvisualfinish
	playsewithpan SE_M_SUPERSONIC, SOUND_PAN_TARGET
	createvisualtask AnimTask_ShakeMon, 2, ANIM_TARGET, 3, 0, 15, 1
	createvisualtask AnimTask_ScaleMonAndRestore, 5, -4, -4, 15, ANIM_TARGET, 1
	waitforvisualfinish
	clearmonbg ANIM_DEF_PARTNER
	blendoff
	delay 1
	call UnsetPsychicBackground
	end

Move_PSYCHIC:
	monbg ANIM_DEF_PARTNER
	call SetPsychicBackground
	setalpha 8, 8
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_ATTACKER, 1, 0, 10, 1
	createvisualtask AnimTask_BlendColorCycle, 2, F_PAL_ATTACKER, 0, 2, 0, 8, RGB(31, 23, 0)
	waitforvisualfinish
	loopsewithpan SE_M_SUPERSONIC, SOUND_PAN_TARGET, 10, 3
	createvisualtask AnimTask_ShakeMon, 2, ANIM_TARGET, 5, 0, 15, 1
	createvisualtask AnimTask_ScaleMonAndRestore, 5, -6, -6, 15, ANIM_TARGET, 1
	waitforvisualfinish
	clearmonbg ANIM_DEF_PARTNER
	blendoff
	delay 1
	call UnsetPsychicBackground
	end

Move_FUTURE_SIGHT:
	goto FutureSight

FutureSightContinue:
	waitforvisualfinish
	delay 1
	call UnsetPsychicBackground
	end

FutureSight:
	monbg ANIM_ATK_PARTNER
	playsewithpan SE_M_PSYBEAM, SOUND_PAN_ATTACKER
	call SetPsychicBackground
	setalpha 8, 8
	playsewithpan SE_M_SUPERSONIC, SOUND_PAN_ATTACKER
	createvisualtask AnimTask_BlendColorCycle, 2, F_PAL_ATTACKER, 0, 2, 0, 8, RGB_WHITE
	createvisualtask AnimTask_ScaleMonAndRestore, 5, -4, -4, 15, ANIM_ATTACKER, 1
	waitforvisualfinish
	clearmonbg ANIM_ATK_PARTNER
	blendoff
	goto FutureSightContinue

UnusedFutureSightHit:
	monbg ANIM_DEF_PARTNER
	playsewithpan SE_M_PSYBEAM, SOUND_PAN_ATTACKER
	call SetPsychicBackground
	setalpha 8, 8
	playsewithpan SE_M_SUPERSONIC, SOUND_PAN_TARGET
	waitplaysewithpan SE_M_SUPERSONIC, SOUND_PAN_TARGET, 8
	createvisualtask AnimTask_ShakeMon, 2, ANIM_TARGET, 4, 0, 15, 1
	createvisualtask AnimTask_ScaleMonAndRestore, 5, -5, -5, 15, ANIM_TARGET, 1
	waitforvisualfinish
	createvisualtask AnimTask_ShakeMon, 2, ANIM_TARGET, 4, 0, 24, 1
	waitforvisualfinish
	clearmonbg ANIM_DEF_PARTNER
	blendoff
	goto FutureSightContinue

Move_THUNDER:
	loadspritegfx ANIM_TAG_LIGHTNING
	fadetobg BG_THUNDER
	waitbgfadeout
	createvisualtask AnimTask_StartSlidingBg, 5, -256, 0, 1, -1
	waitbgfadein
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG, 2, 0, 16, RGB_BLACK
	delay 16
	createvisualtask AnimTask_InvertScreenColor, 2, 257, 257, 257
	playsewithpan SE_M_THUNDER_WAVE, SOUND_PAN_TARGET
	delay 1
	createsprite gLightningSpriteTemplate, ANIM_TARGET, 2, 16, -36
	delay 1
	createsprite gLightningSpriteTemplate, ANIM_TARGET, 2, 16, -20
	delay 1
	createsprite gLightningSpriteTemplate, ANIM_TARGET, 2, 16, 12
	delay 20
	createsprite gLightningSpriteTemplate, ANIM_TARGET, 6, -16, -32
	playsewithpan SE_M_THUNDER_WAVE, SOUND_PAN_TARGET
	delay 1
	createsprite gLightningSpriteTemplate, ANIM_TARGET, 6, -16, -16
	delay 1
	createsprite gLightningSpriteTemplate, ANIM_TARGET, 6, -16, 16
	playsewithpan SE_M_THUNDER_WAVE, SOUND_PAN_TARGET
	delay 5
	createvisualtask AnimTask_InvertScreenColor, 2, 257, 257, 257
	delay 1
	createsprite gLightningSpriteTemplate, ANIM_TARGET, 2, 24, -32
	delay 1
	createsprite gLightningSpriteTemplate, ANIM_TARGET, 2, 24, -16
	delay 1
	createsprite gLightningSpriteTemplate, ANIM_TARGET, 2, 24, 16
	delay 30
	createvisualtask AnimTask_InvertScreenColor, 2, 257, 257, 257
	delay 5
	createvisualtask AnimTask_InvertScreenColor, 2, 257, 257, 257
	delay 1
	createsprite gLightningSpriteTemplate, ANIM_TARGET, 2, 0, -32
	playsewithpan SE_M_TRI_ATTACK2, SOUND_PAN_TARGET
	delay 1
	createsprite gLightningSpriteTemplate, ANIM_TARGET, 2, 0, -16
	delay 1
	createsprite gLightningSpriteTemplate, ANIM_TARGET, 2, 0, 16
	delay 10
	createvisualtask AnimTask_InvertScreenColor, 2, 257, 257, 257
	delay 1
	createvisualtask AnimTask_ShakeTargetInPattern, 2, 30, 3, TRUE, 0
	delay 2
	createvisualtask AnimTask_InvertScreenColor, 2, 257, 257, 257
	delay 1
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_TARGET, 2, F_PAL_BG, 2, 16, 0, RGB_BLACK
	waitforvisualfinish
	restorebg
	waitbgfadeout
	setarg 7, 0xFFFF
	waitbgfadein
	end

Move_THUNDER_PUNCH:
	loadspritegfx ANIM_TAG_IMPACT
	loadspritegfx ANIM_TAG_HANDS_AND_FEET
	loadspritegfx ANIM_TAG_LIGHTNING
	monbg ANIM_TARGET
	setalpha 12, 8
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG, 2, 0, 16, RGB_BLACK
	waitforvisualfinish
	playsewithpan SE_M_COMET_PUNCH, SOUND_PAN_TARGET
	createsprite gFistFootSpriteTemplate, ANIM_TARGET, 4, 0, 0, 8, 1, 0
	createsprite gBasicHitSplatSpriteTemplate, ANIM_TARGET, 3, 0, 0, ANIM_TARGET, 1
	delay 1
	createvisualtask AnimTask_InvertScreenColor, 2, 257, 257, 257
	delay 1
	createsprite gLightningSpriteTemplate, ANIM_TARGET, 2, 0, -48
	delay 1
	createsprite gLightningSpriteTemplate, ANIM_ATTACKER, 2, 0, -16
	delay 1
	createsprite gLightningSpriteTemplate, ANIM_ATTACKER, 2, 0, 16
	delay 1
	playsewithpan SE_M_TRI_ATTACK2, SOUND_PAN_TARGET
	createvisualtask AnimTask_InvertScreenColor, 2, 257, 257, 257
	delay 2
	createvisualtask AnimTask_ShakeMon, 2, ANIM_TARGET, 0, 3, 15, 1
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 3, 0, 0, ANIM_TARGET, 2
	delay 1
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG, 2, 16, 0, RGB_BLACK
	delay 20
	waitforvisualfinish
	clearmonbg ANIM_TARGET
	blendoff
	end

Move_SACRED_FIRE:
	loadspritegfx ANIM_TAG_FIRE
	loadspritegfx ANIM_TAG_FIRE_PLUME
	loopsewithpan SE_M_SACRED_FIRE, SOUND_PAN_ATTACKER, 7, 5
	createsprite gFirePlumeSpriteTemplate, ANIM_ATTACKER, 2, -32, 0, 50, 5, -2, 0
	delay 1
	createsprite gFirePlumeSpriteTemplate, ANIM_ATTACKER, 66, -20, -10, 50, 5, -1, -1
	delay 1
	createsprite gFirePlumeSpriteTemplate, ANIM_ATTACKER, 66, 0, -16, 50, 5, 0, -1
	delay 1
	createsprite gFirePlumeSpriteTemplate, ANIM_ATTACKER, 66, 20, -10, 50, 5, 1, -1
	delay 1
	createsprite gFirePlumeSpriteTemplate, ANIM_ATTACKER, 2, 32, 0, 50, 5, 2, 0
	delay 1
	createsprite gFirePlumeSpriteTemplate, ANIM_ATTACKER, 2, 20, 10, 50, 5, 1, 1
	delay 1
	createvisualtask AnimTask_InvertScreenColor, 2, 257, 257, 257
	delay 1
	createsprite gFirePlumeSpriteTemplate, ANIM_ATTACKER, 2, 0, 16, 50, 5, 0, 1
	delay 1
	createsprite gFirePlumeSpriteTemplate, ANIM_ATTACKER, 2, -20, 10, 50, 5, -1, 1
	createvisualtask AnimTask_InvertScreenColor, 2, 257, 257, 257
	delay 1
	waitforvisualfinish
	playsewithpan SE_M_SACRED_FIRE2, SOUND_PAN_TARGET
	createsprite gLargeFlameSpriteTemplate, ANIM_TARGET, 2, -16, 0, 70, 16, 0, 1
	delay 10
	playsewithpan SE_M_SACRED_FIRE2, SOUND_PAN_TARGET
	createsprite gLargeFlameSpriteTemplate, ANIM_TARGET, 2, 0, 0, 70, 16, 0, 1
	delay 10
	playsewithpan SE_M_SACRED_FIRE2, SOUND_PAN_TARGET
	createsprite gLargeFlameSpriteTemplate, ANIM_TARGET, 2, 16, 0, 80, 16, 0, 1
	delay 1
	createvisualtask AnimTask_InvertScreenColor, 2, 257, 257, 257
	delay 1
	waitforvisualfinish
	createvisualtask AnimTask_InvertScreenColor, 2, 257, 257, 257
	delay 1
	playsewithpan SE_M_FLAME_WHEEL2, SOUND_PAN_TARGET
	createsprite gLargeFlameScatterSpriteTemplate, ANIM_TARGET, 2, 0, 0, 30, 30, -1, 0
	delay 1
	createsprite gLargeFlameScatterSpriteTemplate, ANIM_TARGET, 2, 0, 0, 30, 30, 0, 1
	delay 1
	createsprite gLargeFlameScatterSpriteTemplate, ANIM_TARGET, 2, 0, 0, 30, 30, -1, -1
	delay 1
	createsprite gLargeFlameScatterSpriteTemplate, ANIM_TARGET, 2, 0, 0, 30, 30, 2, 1
	delay 1
	createsprite gLargeFlameScatterSpriteTemplate, ANIM_TARGET, 2, 0, 0, 30, 30, 1, -1
	delay 1
	createsprite gLargeFlameScatterSpriteTemplate, ANIM_TARGET, 2, 0, 0, 30, 30, -1, 1
	delay 1
	createsprite gLargeFlameScatterSpriteTemplate, ANIM_TARGET, 2, 0, 0, 30, 30, 1, -2
	delay 1
	createsprite gLargeFlameScatterSpriteTemplate, ANIM_TARGET, 2, 0, 0, 30, 30, 3, 1
	waitforvisualfinish
	end

Move_SCRATCH:
	loadspritegfx ANIM_TAG_SCRATCH
	monbg ANIM_TARGET
	setalpha 12, 8
	playsewithpan SE_M_SCRATCH, SOUND_PAN_TARGET
	createsprite gScratchSpriteTemplate, ANIM_ATTACKER, 2, 0, 0, 1, 0
	createvisualtask AnimTask_ShakeMon, 2, ANIM_TARGET, 3, 0, 6, 1
	waitforvisualfinish
	clearmonbg ANIM_TARGET
	blendoff
	waitforvisualfinish
	end

Move_DRAGON_BREATH:
	loadspritegfx ANIM_TAG_SMALL_EMBER
	monbg ANIM_DEF_PARTNER
	splitbgprio ANIM_TARGET
	loopsewithpan SE_M_FLAME_WHEEL, SOUND_PAN_ATTACKER, 7, 7
	createsprite gDragonBreathFireSpriteTemplate, ANIM_TARGET, 2, 0, 0, 0, 0, 20
	delay 2
	createsprite gDragonBreathFireSpriteTemplate, ANIM_TARGET, 2, 0, 0, 0, 0, 20
	delay 2
	createvisualtask AnimTask_BlendBattleAnimPal, 10, F_PAL_TARGET, 1, 0, 9, RGB_RED
	createsprite gDragonBreathFireSpriteTemplate, ANIM_TARGET, 2, 0, 0, 0, 0, 20
	delay 2
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_TARGET, 2, 0, 21, 1
	createsprite gDragonBreathFireSpriteTemplate, ANIM_TARGET, 2, 0, 0, 0, 0, 20
	delay 2
	createsprite gDragonBreathFireSpriteTemplate, ANIM_TARGET, 2, 0, 0, 0, 0, 20
	delay 2
	createsprite gDragonBreathFireSpriteTemplate, ANIM_TARGET, 2, 0, 0, 0, 0, 20
	delay 2
	createsprite gDragonBreathFireSpriteTemplate, ANIM_TARGET, 2, 0, 0, 0, 0, 20
	delay 2
	createsprite gDragonBreathFireSpriteTemplate, ANIM_TARGET, 2, 0, 0, 0, 0, 20
	delay 2
	createsprite gDragonBreathFireSpriteTemplate, ANIM_TARGET, 2, 0, 0, 0, 0, 20
	delay 2
	createsprite gDragonBreathFireSpriteTemplate, ANIM_TARGET, 2, 0, 0, 0, 0, 20
	delay 2
	createsprite gDragonBreathFireSpriteTemplate, ANIM_TARGET, 2, 0, 0, 0, 0, 20
	waitforvisualfinish
	createvisualtask AnimTask_BlendBattleAnimPal, 10, F_PAL_TARGET, 1, 9, 0, RGB_RED
	waitforvisualfinish
	clearmonbg ANIM_DEF_PARTNER
	end

Move_ROAR:
	loadspritegfx ANIM_TAG_NOISE_LINE
	monbg ANIM_ATTACKER
	splitbgprio ANIM_ATTACKER
	setalpha 8, 8
	createvisualtask SoundTask_PlayDoubleCry, 2, ANIM_ATTACKER, DOUBLE_CRY_ROAR
	createvisualtask AnimTask_ScaleMonAndRestore, 5, -5, -5, 10, ANIM_ATTACKER, 1
	call RoarEffect
	delay 20
	createvisualtask AnimTask_SlideOffScreen, 5, ANIM_TARGET, 2
	waitforvisualfinish
	clearmonbg ANIM_ATTACKER
	blendoff
	waitforvisualfinish
	createvisualtask SoundTask_WaitForCry, 5
	waitforvisualfinish
	end

RoarEffect:
	createsprite gRoarNoiseLineSpriteTemplate, ANIM_ATTACKER, 2, 24, -8, 0
	createsprite gRoarNoiseLineSpriteTemplate, ANIM_ATTACKER, 2, 24, 0, 2
	createsprite gRoarNoiseLineSpriteTemplate, ANIM_ATTACKER, 2, 24, 8, 1
	delay 15
	createsprite gRoarNoiseLineSpriteTemplate, ANIM_ATTACKER, 2, 24, -8, 0
	createsprite gRoarNoiseLineSpriteTemplate, ANIM_ATTACKER, 2, 24, 0, 2
	createsprite gRoarNoiseLineSpriteTemplate, ANIM_ATTACKER, 2, 24, 8, 1
	return

Move_GROWL:
	loadspritegfx ANIM_TAG_NOISE_LINE
	createvisualtask SoundTask_PlayDoubleCry, 2, ANIM_ATTACKER, DOUBLE_CRY_GROWL
	call RoarEffect
	delay 10
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_TARGET, 1, 0, 9, 1
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_DEF_PARTNER, 1, 0, 9, 1
	waitforvisualfinish
	createvisualtask SoundTask_WaitForCry, 5
	waitforvisualfinish
	end

Move_SNORE:
	loadspritegfx ANIM_TAG_SNORE_Z
	monbg ANIM_ATK_PARTNER
	setalpha 8, 8
	call SnoreEffect
	delay 30
	call SnoreEffect
	waitforvisualfinish
	clearmonbg ANIM_ATK_PARTNER
	blendoff
	end

SnoreEffect:
	playsewithpan SE_M_SNORE, SOUND_PAN_ATTACKER
	createvisualtask AnimTask_ScaleMonAndRestore, 5, -7, -7, 7, ANIM_ATTACKER, 1
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_TARGET, 4, 0, 7, 1
	createsprite gShakeMonOrTerrainSpriteTemplate, ANIM_ATTACKER, 2, 6, 1, 14, 0, 0
	createsprite gSnoreZSpriteTemplate, ANIM_ATTACKER, 2, 0, 0, -42, -38, 24, 0, 0
	createsprite gSnoreZSpriteTemplate, ANIM_ATTACKER, 2, 0, 0, 0, -42, 24, 0, 0
	createsprite gSnoreZSpriteTemplate, ANIM_ATTACKER, 2, 0, 0, 42, -38, 24, 0, 0
	return

Move_LIGHT_SCREEN:
	loadspritegfx ANIM_TAG_SPARKLE_3
	loadspritegfx ANIM_TAG_GREEN_LIGHT_WALL
	setalpha 0, 16
	waitplaysewithpan SE_M_REFLECT, SOUND_PAN_ATTACKER, 15
	createsprite gLightScreenWallSpriteTemplate, ANIM_ATTACKER, 1, 40, 0, ANIM_TAG_GREEN_LIGHT_WALL
	delay 10
	call SpecialScreenSparkle
	waitforvisualfinish
	delay 1
	blendoff
	end

SpecialScreenSparkle:
	createsprite gSpecialScreenSparkleSpriteTemplate, ANIM_ATTACKER, 2, 23, 0, ANIM_ATTACKER, TRUE
	delay 6
	createsprite gSpecialScreenSparkleSpriteTemplate, ANIM_ATTACKER, 2, 31, -8, ANIM_ATTACKER, TRUE
	delay 5
	createsprite gSpecialScreenSparkleSpriteTemplate, ANIM_ATTACKER, 2, 30, 20, ANIM_ATTACKER, TRUE
	delay 7
	createsprite gSpecialScreenSparkleSpriteTemplate, ANIM_ATTACKER, 2, 10, -15, ANIM_ATTACKER, TRUE
	delay 6
	createsprite gSpecialScreenSparkleSpriteTemplate, ANIM_ATTACKER, 2, 20, 10, ANIM_ATTACKER, TRUE
	delay 6
	createsprite gSpecialScreenSparkleSpriteTemplate, ANIM_ATTACKER, 2, 10, 18, ANIM_ATTACKER, TRUE
	return

Move_MIRROR_COAT:
	loadspritegfx ANIM_TAG_SPARKLE_3
	loadspritegfx ANIM_TAG_RED_LIGHT_WALL
	setalpha 0, 16
	createsprite gMirrorCoatWallSpriteTemplate, ANIM_ATTACKER, 1, 40, 0, ANIM_TAG_RED_LIGHT_WALL
	delay 10
	playsewithpan SE_M_REFLECT, SOUND_PAN_ATTACKER
	call SpecialScreenSparkle
	waitforvisualfinish
	delay 1
	blendoff
	end

Move_REFLECT:
	loadspritegfx ANIM_TAG_SPARKLE_4
	loadspritegfx ANIM_TAG_BLUE_LIGHT_WALL
	setalpha 0, 16
	waitplaysewithpan SE_M_REFLECT, SOUND_PAN_ATTACKER, 15
	createsprite gReflectWallSpriteTemplate, ANIM_ATTACKER, 1, 40, 0, ANIM_TAG_BLUE_LIGHT_WALL
	delay 20
	createsprite gReflectSparkleSpriteTemplate, ANIM_ATTACKER, 2, 30, 0, ANIM_ATTACKER, TRUE
	delay 7
	createsprite gReflectSparkleSpriteTemplate, ANIM_ATTACKER, 2, 19, -12, ANIM_ATTACKER, TRUE
	delay 7
	createsprite gReflectSparkleSpriteTemplate, ANIM_ATTACKER, 2, 10, 20, ANIM_ATTACKER, TRUE
	waitforvisualfinish
	delay 1
	blendoff
	end

Move_BARRIER:
	loadspritegfx ANIM_TAG_GRAY_LIGHT_WALL
	setalpha 0, 16
	waitplaysewithpan SE_M_BARRIER, SOUND_PAN_ATTACKER, 15
	createsprite gBarrierWallSpriteTemplate, ANIM_ATTACKER, 3, 40, 0, ANIM_TAG_GRAY_LIGHT_WALL
	waitforvisualfinish
	delay 1
	blendoff
	end

Move_BUBBLE:
	loadspritegfx ANIM_TAG_BUBBLE
	loadspritegfx ANIM_TAG_SMALL_BUBBLES
	monbg ANIM_TARGET
	setalpha 12, 8
	delay 1
	createsprite gWaterBubbleProjectileSpriteTemplate, ANIM_ATTACKER, 2, 18, 0, 15, -15, 10, 128, 100
	playsewithpan SE_M_BUBBLE, SOUND_PAN_ATTACKER
	waitplaysewithpan SE_M_BUBBLE2, SOUND_PAN_TARGET, 100
	delay 6
	createsprite gWaterBubbleProjectileSpriteTemplate, ANIM_ATTACKER, 2, 18, 0, 35, 37, 40, 128, 100
	playsewithpan SE_M_BUBBLE, SOUND_PAN_ATTACKER
	waitplaysewithpan SE_M_BUBBLE2, SOUND_PAN_TARGET, 100
	delay 6
	createsprite gWaterBubbleProjectileSpriteTemplate, ANIM_ATTACKER, 2, 18, 0, 10, -37, 30, 128, 100
	playsewithpan SE_M_BUBBLE, SOUND_PAN_ATTACKER
	waitplaysewithpan SE_M_BUBBLE2, SOUND_PAN_TARGET, 100
	delay 6
	createsprite gWaterBubbleProjectileSpriteTemplate, ANIM_ATTACKER, 2, 18, 0, 30, 10, 15, 128, 100
	playsewithpan SE_M_BUBBLE, SOUND_PAN_ATTACKER
	waitplaysewithpan SE_M_BUBBLE2, SOUND_PAN_TARGET, 100
	delay 6
	createsprite gWaterBubbleProjectileSpriteTemplate, ANIM_ATTACKER, 2, 18, 0, 20, 33, 20, 128, 100
	playsewithpan SE_M_BUBBLE, SOUND_PAN_ATTACKER
	waitplaysewithpan SE_M_BUBBLE2, SOUND_PAN_TARGET, 100
	delay 6
	createsprite gWaterBubbleProjectileSpriteTemplate, ANIM_ATTACKER, 2, 18, 0, 25, -30, 10, 128, 100
	playsewithpan SE_M_BUBBLE, SOUND_PAN_ATTACKER
	waitplaysewithpan SE_M_BUBBLE2, SOUND_PAN_TARGET, 100
	waitforvisualfinish
	call WaterBubblesEffectLong
	waitforvisualfinish
	clearmonbg ANIM_TARGET
	blendoff
	end

Move_SMOG:
	loadspritegfx ANIM_TAG_PURPLE_GAS_CLOUD
	monbg ANIM_DEF_PARTNER
	splitbgprio_all
	setalpha 12, 8
	loopsewithpan SE_M_MIST, SOUND_PAN_TARGET, 17, 10
	call SmogCloud
	call SmogCloud
	call SmogCloud
	call SmogCloud
	call SmogCloud
	call SmogCloud
	call SmogCloud
	delay 120
	loopsewithpan SE_M_TOXIC, SOUND_PAN_TARGET, 18, 2
	createvisualtask AnimTask_BlendColorCycle, 2, F_PAL_TARGET, 2, 2, 0, 12, RGB(26, 0, 26)
	delay 10
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_TARGET, 2, 0, 15, 1
	waitforvisualfinish
	clearmonbg ANIM_DEF_PARTNER
	blendoff
	end

SmogCloud:
	createsprite gSmogCloudSpriteTemplate, ANIM_ATTACKER, 2, 0, -24, 48, 240, 1, 0
	delay 7
	return

Move_FAINT_ATTACK:
	loadspritegfx ANIM_TAG_IMPACT
	monbg ANIM_ATTACKER
	fadetobg BG_DARK
	waitbgfadein
	delay 0
	playsewithpan SE_M_FAINT_ATTACK, SOUND_PAN_ATTACKER
	createvisualtask AnimTask_TranslateMonEllipticalRespectSide, 2, ANIM_ATTACKER, 18, 6, 1, 3
	createvisualtask AnimTask_AttackerFadeToInvisible, 2, 1
	waitforvisualfinish
	clearmonbg ANIM_ATTACKER
	invisible ANIM_ATTACKER
	delay 1
	createvisualtask AnimTask_SetAttackerInvisibleWaitForSignal, 2
	monbg ANIM_TARGET
	setalpha 12, 8
	delay 1
	playsewithpan SE_M_VITAL_THROW2, SOUND_PAN_TARGET
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 2, 0, 0, ANIM_TARGET, 1
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_TARGET, 2, 0, 9, 1
	waitforvisualfinish
	clearmonbg ANIM_TARGET
	blendoff
	delay 1
	setarg 7, 0x1000
	delay 32
	createvisualtask AnimTask_InitAttackerFadeFromInvisible, 2
	monbg ANIM_ATTACKER
	createvisualtask AnimTask_AttackerFadeFromInvisible, 2, 1
	waitforvisualfinish
	clearmonbg ANIM_ATTACKER
	delay 1
	restorebg
	waitbgfadein
	end

Move_SAND_ATTACK:
	loadspritegfx ANIM_TAG_MUD_SAND
	monbg ANIM_ATK_PARTNER
	splitbgprio ANIM_ATTACKER
	setalpha 12, 8
	playsewithpan SE_M_SAND_ATTACK, SOUND_PAN_ATTACKER
	createsprite gSlideMonToOffsetSpriteTemplate, ANIM_ATTACKER, 2, 0, -10, 0, 0, 3
	waitforvisualfinish
	createsprite gSlideMonToOriginalPosSpriteTemplate, ANIM_ATTACKER, 2, 0, 0, 2
	call SandAttackDirt
	call SandAttackDirt
	call SandAttackDirt
	call SandAttackDirt
	call SandAttackDirt
	call SandAttackDirt
	waitforvisualfinish
	clearmonbg ANIM_ATK_PARTNER
	blendoff
	end

SandAttackDirt:
	createsprite gSandAttackDirtSpriteTemplate, ANIM_TARGET, 2, 15, 15, 20, 0, 0
	createsprite gSandAttackDirtSpriteTemplate, ANIM_TARGET, 2, 15, 15, 20, 10, 10
	createsprite gSandAttackDirtSpriteTemplate, ANIM_TARGET, 2, 15, 15, 20, -10, -10
	createsprite gSandAttackDirtSpriteTemplate, ANIM_TARGET, 2, 15, 15, 20, 20, 5
	createsprite gSandAttackDirtSpriteTemplate, ANIM_TARGET, 2, 15, 15, 20, -20, -5
	delay 2
	return

Move_MUD_SLAP:
	loadspritegfx ANIM_TAG_MUD_SAND
	playsewithpan SE_M_SAND_ATTACK, SOUND_PAN_ATTACKER
	createsprite gSlideMonToOffsetSpriteTemplate, ANIM_ATTACKER, 2, 0, -10, 0, 0, 3
	waitforvisualfinish
	createsprite gSlideMonToOriginalPosSpriteTemplate, ANIM_ATTACKER, 2, 0, 0, 2
	call MudSlapMud
	call MudSlapMud
	call MudSlapMud
	call MudSlapMud
	call MudSlapMud
	call MudSlapMud
	waitforvisualfinish
	end

MudSlapMud:
	createsprite gMudSlapMudSpriteTemplate, ANIM_TARGET, 2, 15, 15, 20, 0, 0
	createsprite gMudSlapMudSpriteTemplate, ANIM_TARGET, 2, 15, 15, 20, 10, 5
	createsprite gMudSlapMudSpriteTemplate, ANIM_TARGET, 2, 15, 15, 20, -10, -5
	createsprite gMudSlapMudSpriteTemplate, ANIM_TARGET, 2, 15, 15, 20, 20, 10
	createsprite gMudSlapMudSpriteTemplate, ANIM_TARGET, 2, 15, 15, 20, -20, -10
	delay 2
	return

Move_DRAGON_RAGE:
	loadspritegfx ANIM_TAG_SMALL_EMBER
	loadspritegfx ANIM_TAG_FIRE_PLUME
	playsewithpan SE_M_DRAGON_RAGE, SOUND_PAN_ATTACKER
	createvisualtask AnimTask_ShakeMon, 5, ANIM_ATTACKER, 0, 2, 40, 1
	waitforvisualfinish
	createsprite gSlideMonToOffsetSpriteTemplate, ANIM_TARGET, 2, 0, 15, 0, 0, 4
	waitforvisualfinish
	createsprite gDragonRageFireSpitSpriteTemplate, ANIM_TARGET, 2, 30, 15, 0, 10, 10
	waitforvisualfinish
	loopsewithpan SE_M_FLAME_WHEEL2, SOUND_PAN_TARGET, 11, 3
	createvisualtask AnimTask_ShakeMon, 5, ANIM_TARGET, 0, 3, 25, 1
	createsprite gDragonRageFirePlumeSpriteTemplate, ANIM_TARGET, 66, 1, 5, 0
	delay 1
	createsprite gDragonRageFirePlumeSpriteTemplate, ANIM_TARGET, 66, 1, -10, -15
	delay 1
	createsprite gDragonRageFirePlumeSpriteTemplate, ANIM_TARGET, 2, 1, 0, 25
	delay 1
	createsprite gDragonRageFirePlumeSpriteTemplate, ANIM_TARGET, 66, 1, 15, 5
	delay 1
	createsprite gDragonRageFirePlumeSpriteTemplate, ANIM_TARGET, 66, 1, -25, 0
	delay 1
	createsprite gDragonRageFirePlumeSpriteTemplate, ANIM_TARGET, 2, 1, 30, 30
	delay 1
	createsprite gDragonRageFirePlumeSpriteTemplate, ANIM_TARGET, 2, 1, -27, 25
	delay 1
	createsprite gDragonRageFirePlumeSpriteTemplate, ANIM_TARGET, 66, 1, 0, 8
	waitforvisualfinish
	createsprite gSlideMonToOriginalPosSpriteTemplate, ANIM_TARGET, 66, 0, 0, 4
	waitforvisualfinish
	end

Move_RAIN_DANCE:
	loadspritegfx ANIM_TAG_RAIN_DROPS
	playsewithpan SE_M_RAIN_DANCE, SOUND_PAN_ATTACKER
	createvisualtask AnimTask_BlendBattleAnimPal, 10, F_PAL_BG | F_PAL_BATTLERS_2, 2, 0, 4, RGB_BLACK
	waitforvisualfinish
	createvisualtask AnimTask_CreateRaindrops, 2, 0, 3, 120
	createvisualtask AnimTask_CreateRaindrops, 2, 0, 3, 120
	delay 120
	delay 30
	waitforvisualfinish
	createvisualtask AnimTask_BlendBattleAnimPal, 10, F_PAL_BG | F_PAL_BATTLERS_2, 2, 4, 0, RGB_BLACK
	waitforvisualfinish
	end

Move_BITE:
	loadspritegfx ANIM_TAG_SHARP_TEETH
	loadspritegfx ANIM_TAG_IMPACT
	monbg ANIM_TARGET
	setalpha 12, 8
	playsewithpan SE_M_BITE, SOUND_PAN_TARGET
	createsprite gSharpTeethSpriteTemplate, ANIM_ATTACKER, 2, 0, -32, 0, 0, 819, 10
	createsprite gSharpTeethSpriteTemplate, ANIM_ATTACKER, 2, 0, 32, 4, 0, -819, 10
	delay 10
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 2, 0, 0, ANIM_TARGET, 2
	createvisualtask AnimTask_ShakeMon, 5, ANIM_TARGET, 0, 4, 7, 1
	waitforvisualfinish
	clearmonbg ANIM_TARGET
	blendoff
	delay 1
	end

Move_CRUNCH:
	loadspritegfx ANIM_TAG_SHARP_TEETH
	loadspritegfx ANIM_TAG_IMPACT
	monbg ANIM_TARGET
	fadetobg BG_DARK
	waitbgfadein
	setalpha 12, 8
	playsewithpan SE_M_BITE, SOUND_PAN_TARGET
	createsprite gSharpTeethSpriteTemplate, ANIM_ATTACKER, 2, -32, -32, 1, 819, 819, 10
	createsprite gSharpTeethSpriteTemplate, ANIM_ATTACKER, 2, 32, 32, 5, -819, -819, 10
	delay 10
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 2, -8, 0, ANIM_TARGET, 1
	createvisualtask AnimTask_ShakeMon, 5, ANIM_TARGET, 0, 7, 5, 2
	waitforvisualfinish
	playsewithpan SE_M_BITE, SOUND_PAN_TARGET
	createsprite gSharpTeethSpriteTemplate, ANIM_ATTACKER, 2, 32, -32, 7, -819, 819, 10
	createsprite gSharpTeethSpriteTemplate, ANIM_ATTACKER, 2, -32, 32, 3, 819, -819, 10
	delay 10
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 2, 8, 0, ANIM_TARGET, 1
	createvisualtask AnimTask_ShakeMon, 5, ANIM_TARGET, 0, 8, 4, 2
	waitforvisualfinish
	clearmonbg ANIM_TARGET
	blendoff
	delay 1
	restorebg
	waitbgfadein
	end

Move_CLAMP:
	loadspritegfx ANIM_TAG_CLAMP
	loadspritegfx ANIM_TAG_IMPACT
	monbg ANIM_TARGET
	setalpha 12, 8
	playsewithpan SE_M_VICEGRIP, SOUND_PAN_TARGET
	createsprite gClampJawSpriteTemplate, ANIM_ATTACKER, 2, -32, 0, 2, 819, 0, 10
	createsprite gClampJawSpriteTemplate, ANIM_ATTACKER, 2, 32, 0, 6, -819, 0, 10
	delay 10
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 2, 0, 0, ANIM_TARGET, 2
	createvisualtask AnimTask_ShakeMon, 5, ANIM_TARGET, 3, 0, 5, 1
	waitforvisualfinish
	clearmonbg ANIM_TARGET
	blendoff
	waitforvisualfinish
	end

Move_ICE_BEAM:
	monbg ANIM_TARGET
	splitbgprio ANIM_TARGET
	setalpha 12, 8
	loadspritegfx ANIM_TAG_ICE_CRYSTALS
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG, 1, 0, 7, RGB_BLACK
	waitforvisualfinish
	createsoundtask SoundTask_LoopSEAdjustPanning, SE_M_BUBBLE_BEAM2, SOUND_PAN_ATTACKER, SOUND_PAN_TARGET, 4, 4, 0, 10
	createsprite gIceBeamOuterCrystalSpriteTemplate, ANIM_ATTACKER, 2, 20, 12, 0, 12, 20
	createsprite gIceBeamOuterCrystalSpriteTemplate, ANIM_ATTACKER, 2, 20, -12, 0, -12, 20
	delay 1
	call IceBeamCreateCrystals
	call IceBeamCreateCrystals
	call IceBeamCreateCrystals
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_TARGET, -31, 0, 7, RGB(0, 20, 31)
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_TARGET, 2, 0, 25, 1
	call IceBeamCreateCrystals
	call IceBeamCreateCrystals
	call IceBeamCreateCrystals
	call IceBeamCreateCrystals
	call IceBeamCreateCrystals
	call IceBeamCreateCrystals
	call IceBeamCreateCrystals
	call IceBeamCreateCrystals
	createsprite gIceBeamInnerCrystalSpriteTemplate, ANIM_ATTACKER, 2, 20, 0, 0, 0, 11
	delay 1
	createsprite gIceBeamInnerCrystalSpriteTemplate, ANIM_ATTACKER, 2, 20, 0, 0, 0, 11
	waitforvisualfinish
	delay 20
	call IceCrystalEffectShort
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_TARGET, 5, 7, 0, RGB(0, 20, 31)
	waitforvisualfinish
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG, 0, 7, 0, RGB_BLACK
	waitforvisualfinish
	clearmonbg ANIM_TARGET
	blendoff
	end

IceBeamCreateCrystals:
	createsprite gIceBeamOuterCrystalSpriteTemplate, ANIM_ATTACKER, 2, 20, 12, 0, 12, 20
	createsprite gIceBeamOuterCrystalSpriteTemplate, ANIM_ATTACKER, 2, 20, -12, 0, -12, 20
	createsprite gIceBeamInnerCrystalSpriteTemplate, ANIM_ATTACKER, 2, 20, 0, 0, 0, 11
	delay 1
	return

Move_WITHDRAW:
	playsewithpan SE_M_HEADBUTT, SOUND_PAN_ATTACKER
	createvisualtask AnimTask_Withdraw, 5
	waitforvisualfinish
	end

Move_AURORA_BEAM:
	loadspritegfx ANIM_TAG_RAINBOW_RINGS
	fadetobg BG_AURORA
	waitbgfadein
	playsewithpan SE_M_BUBBLE_BEAM, SOUND_PAN_ATTACKER
	setarg 7, 0
	createvisualtask AnimTask_RotateAuroraRingColors, 10, 130
	call AuroraBeamCreateRings
	createvisualtask AnimTask_ShakeMon2, 5, ANIM_TARGET, 1, 0, 17, 1
	call AuroraBeamCreateRings
	call AuroraBeamCreateRings
	call AuroraBeamCreateRings
	setarg 7, 0xFFFF
	createsoundtask SoundTask_LoopSEAdjustPanning, SE_M_BUBBLE_BEAM2, SOUND_PAN_ATTACKER, SOUND_PAN_TARGET, 3, 6, 0, 10
	createvisualtask AnimTask_ShakeMon2, 5, ANIM_TARGET, 2, 0, 40, 1
	call AuroraBeamCreateRings
	call AuroraBeamCreateRings
	call AuroraBeamCreateRings
	call AuroraBeamCreateRings
	call AuroraBeamCreateRings
	call AuroraBeamCreateRings
	waitforvisualfinish
	restorebg
	waitbgfadein
	end

AuroraBeamCreateRings:
	createsprite gAuroraBeamRingSpriteTemplate, ANIM_TARGET, 2, 20, 0, 0, 0, 17
	delay 1
	createsprite gAuroraBeamRingSpriteTemplate, ANIM_TARGET, 2, 20, 0, 0, 0, 17
	delay 1
	createsprite gAuroraBeamRingSpriteTemplate, ANIM_TARGET, 2, 20, 0, 0, 0, 17
	delay 1
	createsprite gAuroraBeamRingSpriteTemplate, ANIM_TARGET, 2, 20, 0, 0, 0, 17
	delay 1
	return

Move_SOLAR_BEAM:
	loadspritegfx ANIM_TAG_ORBS
	choosetwoturnanim SolarBeamSetUp, SolarBeamUnleash

SolarBeamEnd:
	waitforvisualfinish
	end

SolarBeamSetUp:
	monbg ANIM_ATK_PARTNER
	setalpha 12, 8
	createvisualtask AnimTask_BlendColorCycle, 2, F_PAL_ATTACKER, 1, 4, 0, 11, RGB(31, 31, 11)
	playsewithpan SE_M_MEGA_KICK, SOUND_PAN_ATTACKER
	call SolarBeamAbsorbEffect
	waitforvisualfinish
	clearmonbg ANIM_ATK_PARTNER
	blendoff
	goto SolarBeamEnd

SolarBeamAbsorbEffect:
	createsprite gPowerAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 2, 40, 40, 16
	delay 2
	createsprite gPowerAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 2, -40, -40, 16
	delay 2
	createsprite gPowerAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 2, 0, 40, 16
	delay 2
	createsprite gPowerAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 2, 0, -40, 16
	delay 2
	createsprite gPowerAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 2, 40, -20, 16
	delay 2
	createsprite gPowerAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 2, 40, 20, 16
	delay 2
	createsprite gPowerAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 2, -40, -20, 16
	delay 2
	createsprite gPowerAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 2, -40, 20, 16
	delay 2
	createsprite gPowerAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 2, -20, 30, 16
	delay 2
	createsprite gPowerAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 2, 20, -30, 16
	delay 2
	createsprite gPowerAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 2, -20, -30, 16
	delay 2
	createsprite gPowerAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 2, 20, 30, 16
	delay 2
	createsprite gPowerAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 2, -40, 0, 16
	delay 2
	createsprite gPowerAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 2, 40, 0, 16
	delay 2
	return

SolarBeamUnleash:
	call SetSolarBeamBg
	panse SE_M_SOLAR_BEAM, SOUND_PAN_ATTACKER, SOUND_PAN_TARGET, +2, 0
	createvisualtask AnimTask_CreateSmallSolarBeamOrbs, 5
	createsprite gSolarBeamBigOrbSpriteTemplate, ANIM_TARGET, 3, 15, 0, 20, 0
	delay 4
	createsprite gSolarBeamBigOrbSpriteTemplate, ANIM_TARGET, 3, 15, 0, 20, 1
	delay 4
	createvisualtask AnimTask_BlendBattleAnimPal, 10, F_PAL_TARGET, 1, 0, 10, RGB(25, 31, 0)
	createsprite gSolarBeamBigOrbSpriteTemplate, ANIM_TARGET, 3, 15, 0, 20, 2
	delay 4
	createvisualtask AnimTask_ShakeMon2, 5, ANIM_TARGET, 2, 0, 65, 1
	createsprite gSolarBeamBigOrbSpriteTemplate, ANIM_TARGET, 3, 15, 0, 20, 3
	delay 4
	createsprite gSolarBeamBigOrbSpriteTemplate, ANIM_TARGET, 3, 15, 0, 20, 4
	delay 4
	createsprite gSolarBeamBigOrbSpriteTemplate, ANIM_TARGET, 3, 15, 0, 20, 5
	delay 4
	createsprite gSolarBeamBigOrbSpriteTemplate, ANIM_TARGET, 3, 15, 0, 20, 6
	delay 4
	call SolarBeamUnleash1
	call SolarBeamUnleash1
	waitforvisualfinish
	createvisualtask AnimTask_BlendBattleAnimPal, 10, F_PAL_TARGET, 1, 10, 0, RGB(25, 31, 0)
	call UnsetSolarBeamBg
	goto SolarBeamEnd

SolarBeamUnleash1:
	createsprite gSolarBeamBigOrbSpriteTemplate, ANIM_TARGET, 3, 15, 0, 20, 0
	delay 4
	createsprite gSolarBeamBigOrbSpriteTemplate, ANIM_TARGET, 3, 15, 0, 20, 1
	delay 4
	createsprite gSolarBeamBigOrbSpriteTemplate, ANIM_TARGET, 3, 15, 0, 20, 2
	delay 4
	createsprite gSolarBeamBigOrbSpriteTemplate, ANIM_TARGET, 3, 15, 0, 20, 3
	delay 4
	createsprite gSolarBeamBigOrbSpriteTemplate, ANIM_TARGET, 3, 15, 0, 20, 4
	delay 4
	createsprite gSolarBeamBigOrbSpriteTemplate, ANIM_TARGET, 3, 15, 0, 20, 5
	delay 4
	createsprite gSolarBeamBigOrbSpriteTemplate, ANIM_TARGET, 3, 15, 0, 20, 6
	delay 4
	return

Move_BLIZZARD:
	loadspritegfx ANIM_TAG_ICE_CRYSTALS
	monbg ANIM_DEF_PARTNER
	createvisualtask AnimTask_GetAttackerSide, 2
	jumprettrue BlizzardAgainstPlayer
	fadetobg BG_HIGHSPEED_OPPONENT
BlizzardContinue:
	waitbgfadeout
	createvisualtask AnimTask_StartSlidingBg, 5, -2304, 0, 1, -1
	waitbgfadein
	waitforvisualfinish
	panse SE_M_BLIZZARD, SOUND_PAN_ATTACKER, SOUND_PAN_TARGET, +2, 0
	call BlizzardIceCrystals
	call BlizzardIceCrystals
	playsewithpan SE_M_BLIZZARD2, SOUND_PAN_TARGET
	waitforvisualfinish
	call IceCrystalEffectLong
	waitforvisualfinish
	clearmonbg ANIM_DEF_PARTNER
	delay 20
	restorebg
	waitbgfadeout
	setarg 7, 0xFFFF
	waitbgfadein
	end

BlizzardIceCrystals:
	createsprite gSwirlingSnowballSpriteTemplate, ANIM_ATTACKER, 40, 0, -10, 0, -10, 72, 1
	createsprite gBlizzardIceCrystalSpriteTemplate, ANIM_ATTACKER, 40, 0, 0, 0, 0, 80, 0, 0, 1
	delay 3
	createsprite gSwirlingSnowballSpriteTemplate, ANIM_ATTACKER, 40, 0, -15, 0, -15, 72, 1
	createsprite gBlizzardIceCrystalSpriteTemplate, ANIM_ATTACKER, 40, 0, -10, 0, -10, 80, 0, 0, 1
	delay 3
	createsprite gSwirlingSnowballSpriteTemplate, ANIM_ATTACKER, 40, 0, -5, 0, -5, 72, 1
	createsprite gBlizzardIceCrystalSpriteTemplate, ANIM_ATTACKER, 40, 0, 10, 0, 10, 80, 0, 0, 1
	delay 3
	createsprite gSwirlingSnowballSpriteTemplate, ANIM_ATTACKER, 40, 0, -10, 0, -10, 72, 1
	createsprite gBlizzardIceCrystalSpriteTemplate, ANIM_ATTACKER, 40, 0, -20, 0, -20, 80, 0, 0, 1
	delay 3
	createsprite gSwirlingSnowballSpriteTemplate, ANIM_ATTACKER, 40, 0, -20, 0, -20, 72, 1
	createsprite gBlizzardIceCrystalSpriteTemplate, ANIM_ATTACKER, 40, 0, 15, 0, 15, 80, 0, 0, 1
	delay 3
	createsprite gSwirlingSnowballSpriteTemplate, ANIM_ATTACKER, 40, 0, -15, 0, -15, 72, 1
	createsprite gBlizzardIceCrystalSpriteTemplate, ANIM_ATTACKER, 40, 0, -20, 0, -20, 80, 0, 0, 1
	delay 3
	createsprite gSwirlingSnowballSpriteTemplate, ANIM_ATTACKER, 40, 0, -25, 0, -25, 72, 1
	createsprite gBlizzardIceCrystalSpriteTemplate, ANIM_ATTACKER, 40, 0, 20, 0, 20, 80, 0, 0, 1
	delay 3
	return

BlizzardAgainstPlayer:
	fadetobg BG_HIGHSPEED_PLAYER
	goto BlizzardContinue

Move_POWDER_SNOW:
	loadspritegfx ANIM_TAG_ICE_CRYSTALS
	monbg ANIM_DEF_PARTNER
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG | F_PAL_BATTLERS, 1, 0, 3, RGB_BLACK
	waitforvisualfinish
	panse SE_M_GUST, SOUND_PAN_ATTACKER, SOUND_PAN_TARGET, +2, 0
	call PowderSnowSnowballs
	call PowderSnowSnowballs
	playsewithpan SE_M_GUST2, SOUND_PAN_TARGET
	waitforvisualfinish
	waitsound
	call IceCrystalEffectLong
	waitforvisualfinish
	clearmonbg ANIM_DEF_PARTNER
	delay 20
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG | F_PAL_BATTLERS, 1, 3, 0, RGB_BLACK
	end

PowderSnowSnowballs:
	createsprite gPowderSnowSnowballSpriteTemplate, ANIM_ATTACKER, 40, 0, 0, 0, 0, 56, 4, 4, 1
	delay 3
	createsprite gPowderSnowSnowballSpriteTemplate, ANIM_ATTACKER, 40, 0, -10, 0, -10, 56, 4, 4, 1
	delay 3
	createsprite gPowderSnowSnowballSpriteTemplate, ANIM_ATTACKER, 40, 0, 10, 0, 10, 56, -4, 3, 1
	delay 3
	createsprite gPowderSnowSnowballSpriteTemplate, ANIM_ATTACKER, 40, 0, -20, 0, -20, 56, -4, 5, 1
	delay 3
	createsprite gPowderSnowSnowballSpriteTemplate, ANIM_ATTACKER, 40, 0, 15, 0, 15, 56, 4, 4, 1
	delay 3
	createsprite gPowderSnowSnowballSpriteTemplate, ANIM_ATTACKER, 40, 0, -20, 0, -20, 56, 4, 4, 1
	delay 3
	createsprite gPowderSnowSnowballSpriteTemplate, ANIM_ATTACKER, 40, 0, 20, 0, 20, 56, 4, 4, 1
	delay 3
	return

Move_HYDRO_PUMP:
	loadspritegfx ANIM_TAG_WATER_ORB
	loadspritegfx ANIM_TAG_WATER_IMPACT
	monbg ANIM_DEF_PARTNER
	splitbgprio ANIM_TARGET
	setalpha 12, 8
	createvisualtask AnimTask_ShakeMon, 5, ANIM_ATTACKER, 0, 2, 40, 1
	delay 6
	panse SE_M_HYDRO_PUMP, SOUND_PAN_ATTACKER, SOUND_PAN_TARGET, +2, 0
	createvisualtask AnimTask_StartSinAnimTimer, 5, 100
	call HydroPumpBeams
	call HydroPumpBeams
	call HydroPumpBeams
	createvisualtask AnimTask_ShakeMon, 5, ANIM_TARGET, 3, 0, 37, 1
	call HydroPumpHitSplats
	call HydroPumpBeams
	call HydroPumpBeams
	call HydroPumpHitSplats
	call HydroPumpBeams
	call HydroPumpBeams
	call HydroPumpHitSplats
	call HydroPumpBeams
	call HydroPumpBeams
	call HydroPumpHitSplats
	call HydroPumpBeams
	call HydroPumpBeams
	call HydroPumpHitSplats
	delay 1
	delay 1
	call HydroPumpHitSplats
	waitforvisualfinish
	clearmonbg ANIM_DEF_PARTNER
	blendoff
	end

HydroPumpBeams:
	createsprite gHydroPumpOrbSpriteTemplate, ANIM_ATTACKER, 3, 10, 10, 0, 16
	createsprite gHydroPumpOrbSpriteTemplate, ANIM_ATTACKER, 3, 10, 10, 0, -16
	delay 1
	createsprite gHydroPumpOrbSpriteTemplate, ANIM_ATTACKER, 3, 10, 10, 0, 16
	createsprite gHydroPumpOrbSpriteTemplate, ANIM_ATTACKER, 3, 10, 10, 0, -16
	delay 1
	return

HydroPumpHitSplats	:
	createsprite gWaterHitSplatSpriteTemplate, ANIM_ATTACKER, 4, 0, 15, ANIM_TARGET, 1
	createsprite gWaterHitSplatSpriteTemplate, ANIM_ATTACKER, 4, 0, -15, ANIM_TARGET, 1
	return

Move_SIGNAL_BEAM:
	loadspritegfx ANIM_TAG_GLOWY_RED_ORB
	loadspritegfx ANIM_TAG_GLOWY_GREEN_ORB
	loadspritegfx ANIM_TAG_DUCK
	createvisualtask AnimTask_ShakeMon, 5, ANIM_ATTACKER, 0, 2, 25, 1
	delay 6
	panse SE_M_BUBBLE_BEAM, SOUND_PAN_ATTACKER, SOUND_PAN_TARGET, +1, 0
	createvisualtask AnimTask_StartSinAnimTimer, 5, 100
	call SignalBeamOrbs
	call SignalBeamOrbs
	call SignalBeamOrbs
	call SignalBeamOrbs
	call SignalBeamOrbs
	call SignalBeamOrbs
	createvisualtask AnimTask_ShakeMon, 5, ANIM_TARGET, 3, 0, 25, 1
	createsprite gComplexPaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_TARGET, 8, 5, RGB_RED, 8, RGB(1, 30, 0), 8
	call SignalBeamOrbs
	call SignalBeamOrbs
	call SignalBeamOrbs
	call SignalBeamOrbs
	call SignalBeamOrbs
	call SignalBeamOrbs
	call SignalBeamOrbs
	call SignalBeamOrbs
	call SignalBeamOrbs
	call SignalBeamOrbs
	call SignalBeamOrbs
	call SignalBeamOrbs
	call SignalBeamOrbs
	call SignalBeamOrbs
	call SignalBeamOrbs
	call SignalBeamOrbs
	call SignalBeamOrbs
	waitforvisualfinish
	end

SignalBeamOrbs:
	createsprite gSignalBeamRedOrbSpriteTemplate, ANIM_TARGET, 3, 10, 10, 0, 16
	createsprite gSignalBeamGreenOrbSpriteTemplate, ANIM_TARGET, 3, 10, 10, 0, -16
	delay 1
	return

Move_ABSORB:
	loadspritegfx ANIM_TAG_ORBS
	loadspritegfx ANIM_TAG_BLUE_STAR
	loadspritegfx ANIM_TAG_IMPACT
	monbg ANIM_DEF_PARTNER
	splitbgprio_foes ANIM_TARGET
	setalpha 12, 8
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG, 1, 0, 4, RGB(13, 31, 12)
	waitforvisualfinish
	playsewithpan SE_M_ABSORB, SOUND_PAN_TARGET
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 2, 0, 0, ANIM_TARGET, 2
	delay 2
	createvisualtask AnimTask_ShakeMon, 5, ANIM_TARGET, 0, 5, 5, 1
	waitforvisualfinish
	delay 3
	call AbsorbEffect
	waitforvisualfinish
	delay 15
	call HealingEffect
	waitforvisualfinish
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG, 1, 4, 0, RGB(13, 31, 12)
	waitforvisualfinish
	clearmonbg ANIM_DEF_PARTNER
	blendoff
	end

AbsorbEffect:
	playsewithpan SE_M_CRABHAMMER, SOUND_PAN_TARGET
	createsprite gAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 3, 0, 5, 8, 26
	delay 4
	playsewithpan SE_M_CRABHAMMER, SOUND_PAN_TARGET
	createsprite gAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 3, 10, -5, -8, 26
	delay 4
	playsewithpan SE_M_CRABHAMMER, SOUND_PAN_TARGET
	createsprite gAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 3, -5, 15, 16, 33
	delay 4
	playsewithpan SE_M_CRABHAMMER, SOUND_PAN_TARGET
	createsprite gAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 3, 0, -15, -16, 36
	delay 4
	playsewithpan SE_M_CRABHAMMER, SOUND_PAN_TARGET
	createsprite gAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 3, 0, 5, 8, 26
	delay 4
	playsewithpan SE_M_CRABHAMMER, SOUND_PAN_TARGET
	createsprite gAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 3, 10, -5, -8, 26
	delay 4
	playsewithpan SE_M_CRABHAMMER, SOUND_PAN_TARGET
	createsprite gAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 3, -10, 20, 20, 39
	delay 4
	playsewithpan SE_M_CRABHAMMER, SOUND_PAN_TARGET
	createsprite gAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 3, 5, -18, -20, 35
	delay 4
	return

Move_MEGA_DRAIN:
	loadspritegfx ANIM_TAG_ORBS
	loadspritegfx ANIM_TAG_BLUE_STAR
	loadspritegfx ANIM_TAG_IMPACT
	monbg ANIM_DEF_PARTNER
	splitbgprio_foes ANIM_TARGET
	setalpha 12, 8
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG, 1, 0, 8, RGB(13, 31, 12)
	waitforvisualfinish
	playsewithpan SE_M_ABSORB, SOUND_PAN_TARGET
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 2, 0, 0, ANIM_TARGET, 1
	delay 2
	createvisualtask AnimTask_ShakeMon, 5, ANIM_TARGET, 0, 5, 5, 1
	waitforvisualfinish
	delay 3
	call MegaDrainAbsorbEffect
	waitforvisualfinish
	delay 15
	call HealingEffect
	waitforvisualfinish
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG, 1, 8, 0, RGB(13, 31, 12)
	waitforvisualfinish
	clearmonbg ANIM_DEF_PARTNER
	blendoff
	end

MegaDrainAbsorbEffect:
	playsewithpan SE_M_BUBBLE3, SOUND_PAN_TARGET
	createsprite gAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 3, 0, 5, 8, 26
	createsprite gAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 3, 5, -18, -20, 35
	delay 4
	playsewithpan SE_M_BUBBLE3, SOUND_PAN_TARGET
	createsprite gAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 3, 10, -5, -8, 26
	createsprite gAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 3, -10, 20, 20, 39
	delay 4
	playsewithpan SE_M_BUBBLE3, SOUND_PAN_TARGET
	createsprite gAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 3, -5, 15, 16, 33
	createsprite gAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 3, 10, -5, -8, 26
	delay 4
	playsewithpan SE_M_BUBBLE3, SOUND_PAN_TARGET
	createsprite gAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 3, 0, -15, -16, 36
	createsprite gAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 3, 0, 5, 8, 26
	delay 4
	playsewithpan SE_M_BUBBLE3, SOUND_PAN_TARGET
	createsprite gAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 3, 0, 5, 8, 26
	createsprite gAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 3, 0, -15, -16, 36
	delay 4
	playsewithpan SE_M_BUBBLE3, SOUND_PAN_TARGET
	createsprite gAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 3, 10, -5, -8, 26
	createsprite gAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 3, -5, 15, 16, 33
	delay 4
	playsewithpan SE_M_BUBBLE3, SOUND_PAN_TARGET
	createsprite gAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 3, -10, 20, 20, 39
	createsprite gAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 3, 10, -5, -8, 26
	delay 4
	playsewithpan SE_M_BUBBLE3, SOUND_PAN_TARGET
	createsprite gAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 3, 0, 5, 8, 26
	createsprite gAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 3, 5, -18, -20, 35
	delay 4
	return

Move_GIGA_DRAIN:
	loadspritegfx ANIM_TAG_ORBS
	loadspritegfx ANIM_TAG_BLUE_STAR
	loadspritegfx ANIM_TAG_IMPACT
	monbg ANIM_DEF_PARTNER
	splitbgprio_foes ANIM_TARGET
	setalpha 12, 8
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG, 1, 0, 12, RGB(13, 31, 12)
	waitforvisualfinish
	playsewithpan SE_M_ABSORB, SOUND_PAN_TARGET
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 2, 0, 0, ANIM_TARGET, 0
	delay 2
	createvisualtask AnimTask_ShakeMon, 5, ANIM_TARGET, 0, 5, 5, 1
	waitforvisualfinish
	delay 3
	call GigaDrainAbsorbEffect
	waitforvisualfinish
	delay 15
	call HealingEffect
	waitforvisualfinish
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG, 1, 12, 0, RGB(13, 31, 12)
	waitforvisualfinish
	clearmonbg ANIM_DEF_PARTNER
	blendoff
	end

GigaDrainAbsorbEffect:
	playsewithpan SE_M_GIGA_DRAIN, SOUND_PAN_TARGET
	createsprite gAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 3, 0, 5, 8, 26
	createsprite gAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 3, 5, -18, -40, 35
	createsprite gAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 3, -10, 20, 20, 39
	delay 4
	playsewithpan SE_M_GIGA_DRAIN, SOUND_PAN_TARGET
	createsprite gAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 3, 0, 5, 28, 26
	createsprite gAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 3, 10, -5, -8, 26
	createsprite gAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 3, -10, 20, 40, 39
	delay 4
	playsewithpan SE_M_GIGA_DRAIN, SOUND_PAN_TARGET
	createsprite gAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 3, 10, -5, -8, 26
	createsprite gAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 3, -5, 15, 16, 33
	createsprite gAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 3, 10, -5, -32, 26
	delay 4
	playsewithpan SE_M_GIGA_DRAIN, SOUND_PAN_TARGET
	createsprite gAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 3, 0, -15, -16, 36
	createsprite gAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 3, 0, 5, 8, 26
	createsprite gAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 3, 10, -5, -8, 26
	delay 4
	playsewithpan SE_M_GIGA_DRAIN, SOUND_PAN_TARGET
	createsprite gAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 3, -5, 15, 16, 33
	createsprite gAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 3, 0, -15, -16, 36
	createsprite gAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 3, 0, 5, 8, 26
	delay 4
	playsewithpan SE_M_GIGA_DRAIN, SOUND_PAN_TARGET
	createsprite gAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 3, 0, 5, 8, 26
	createsprite gAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 3, -5, 15, 16, 33
	createsprite gAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 3, 10, -5, -40, 26
	delay 4
	playsewithpan SE_M_GIGA_DRAIN, SOUND_PAN_TARGET
	createsprite gAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 3, -5, 15, 36, 33
	createsprite gAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 3, 10, -5, -8, 26
	createsprite gAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 3, -10, 20, 20, 39
	delay 4
	playsewithpan SE_M_GIGA_DRAIN, SOUND_PAN_TARGET
	createsprite gAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 3, 0, 5, 8, 26
	createsprite gAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 3, 0, 5, 8, 26
	createsprite gAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 3, 5, -18, -20, 35
	delay 4
	return

Move_LEECH_LIFE:
	loadspritegfx ANIM_TAG_NEEDLE
	loadspritegfx ANIM_TAG_ORBS
	delay 1
	loadspritegfx ANIM_TAG_BLUE_STAR
	loadspritegfx ANIM_TAG_IMPACT
	monbg ANIM_DEF_PARTNER
	splitbgprio_foes ANIM_TARGET
	setalpha 12, 8
	delay 1
	createsprite gLeechLifeNeedleSpriteTemplate, ANIM_ATTACKER, 2, -20, 15, 12
	waitforvisualfinish
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 2, 0, 0, ANIM_TARGET, 2
	playsewithpan SE_M_ABSORB, SOUND_PAN_TARGET
	delay 2
	createvisualtask AnimTask_ShakeMon, 5, ANIM_TARGET, 0, 5, 5, 1
	waitforvisualfinish
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG, 1, 0, 7, RGB_BLACK
	waitforvisualfinish
	call AbsorbEffect
	waitforvisualfinish
	delay 15
	call HealingEffect
	waitforvisualfinish
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG, 1, 7, 0, RGB_BLACK
	waitforvisualfinish
	clearmonbg ANIM_DEF_PARTNER
	blendoff
	end

Move_SYNTHESIS:
	loadspritegfx ANIM_TAG_BLUE_STAR
	loadspritegfx ANIM_TAG_SPARKLE_2
	createvisualtask AnimTask_BlendColorCycle, 2, F_PAL_ATTACKER, 2, 2, 0, 16, RGB(27, 31, 18)
	playsewithpan SE_M_MEGA_KICK, SOUND_PAN_ATTACKER
	call GrantingStarsEffect
	waitforvisualfinish
	call HealingEffect
	waitforvisualfinish
	end

Move_TOXIC:
	loadspritegfx ANIM_TAG_TOXIC_BUBBLE
	loadspritegfx ANIM_TAG_POISON_BUBBLE
	call ToxicBubbles
	call ToxicBubbles
	waitforvisualfinish
	delay 15
	call PoisonBubblesEffect
	waitforvisualfinish
	end

ToxicBubbles:
	createsprite gToxicBubbleSpriteTemplate, ANIM_TARGET, 2, -24, 16, 1, 1
	playsewithpan SE_M_TOXIC, SOUND_PAN_TARGET
	delay 15
	createsprite gToxicBubbleSpriteTemplate, ANIM_TARGET, 2, 8, 16, 1, 1
	playsewithpan SE_M_TOXIC, SOUND_PAN_TARGET
	delay 15
	createsprite gToxicBubbleSpriteTemplate, ANIM_TARGET, 2, -8, 16, 1, 1
	playsewithpan SE_M_TOXIC, SOUND_PAN_TARGET
	delay 15
	createsprite gToxicBubbleSpriteTemplate, ANIM_TARGET, 2, 24, 16, 1, 1
	playsewithpan SE_M_TOXIC, SOUND_PAN_TARGET
	delay 15
	return

Move_SLUDGE:
	loadspritegfx ANIM_TAG_POISON_BUBBLE
	playsewithpan SE_M_BUBBLE3, SOUND_PAN_ATTACKER
	createsprite gSludgeProjectileSpriteTemplate, ANIM_TARGET, 2, 20, 0, 40, 0
	waitforvisualfinish
	createvisualtask AnimTask_ShakeMon, 5, ANIM_TARGET, 3, 0, 5, 1
	createvisualtask AnimTask_BlendColorCycle, 2, F_PAL_TARGET, 1, 2, 0, 12, RGB(30, 0, 31)
	call PoisonBubblesEffect
	waitforvisualfinish
	end

Move_SLUDGE_BOMB:
	loadspritegfx ANIM_TAG_POISON_BUBBLE
	call SludgeBombProjectile
	call SludgeBombProjectile
	call SludgeBombProjectile
	call SludgeBombProjectile
	call SludgeBombProjectile
	call SludgeBombProjectile
	call SludgeBombProjectile
	call SludgeBombProjectile
	call SludgeBombProjectile
	call SludgeBombProjectile
	createvisualtask AnimTask_ShakeMon2, 5, ANIM_TARGET, 3, 0, 15, 1
	createvisualtask AnimTask_BlendColorCycle, 2, F_PAL_TARGET, 1, 2, 0, 12, RGB(30, 0, 31)
	createsprite gSludgeBombHitParticleSpriteTemplate, ANIM_TARGET, 2, 42, 27, 20
	createsprite gSludgeBombHitParticleSpriteTemplate, ANIM_TARGET, 2, -27, 44, 20
	createsprite gSludgeBombHitParticleSpriteTemplate, ANIM_TARGET, 2, 39, -28, 20
	createsprite gSludgeBombHitParticleSpriteTemplate, ANIM_TARGET, 2, -42, -42, 20
	playsewithpan SE_M_DIG, SOUND_PAN_TARGET
	delay 5
	createsprite gSludgeBombHitParticleSpriteTemplate, ANIM_TARGET, 2, 0, 40, 20
	createsprite gSludgeBombHitParticleSpriteTemplate, ANIM_TARGET, 2, -8, -44, 20
	createsprite gSludgeBombHitParticleSpriteTemplate, ANIM_TARGET, 2, -46, -28, 20
	createsprite gSludgeBombHitParticleSpriteTemplate, ANIM_TARGET, 2, 46, 9, 20
	playsewithpan SE_M_DIG, SOUND_PAN_TARGET
	delay 5
	createsprite gSludgeBombHitParticleSpriteTemplate, ANIM_TARGET, 2, 42, 0, 20
	createsprite gSludgeBombHitParticleSpriteTemplate, ANIM_TARGET, 2, -43, -12, 20
	createsprite gSludgeBombHitParticleSpriteTemplate, ANIM_TARGET, 2, 16, -46, 20
	createsprite gSludgeBombHitParticleSpriteTemplate, ANIM_TARGET, 2, -16, 44, 20
	playsewithpan SE_M_DIG, SOUND_PAN_TARGET
	delay 0
	waitsound
	waitforvisualfinish
	call PoisonBubblesEffect
	waitforvisualfinish
	end

SludgeBombProjectile:
	playsewithpan SE_M_BUBBLE3, SOUND_PAN_ATTACKER
	createsprite gSludgeProjectileSpriteTemplate, ANIM_TARGET, 2, 20, 0, 40, 0
	delay 3
	return

Move_ACID:
	loadspritegfx ANIM_TAG_POISON_BUBBLE
	monbg ANIM_DEF_PARTNER
	createsprite gAcidPoisonBubbleSpriteTemplate, ANIM_TARGET, 2, 20, 0, 40, 1, 0, 0
	playsewithpan SE_M_BUBBLE3, SOUND_PAN_ATTACKER
	delay 5
	createsprite gAcidPoisonBubbleSpriteTemplate, ANIM_TARGET, 2, 20, 0, 40, 1, 24, 0
	playsewithpan SE_M_BUBBLE3, SOUND_PAN_ATTACKER
	delay 5
	createsprite gAcidPoisonBubbleSpriteTemplate, ANIM_TARGET, 2, 20, 0, 40, 1, -24, 0
	playsewithpan SE_M_BUBBLE3, SOUND_PAN_ATTACKER
	delay 15
	createvisualtask AnimTask_ShakeMon2, 5, ANIM_TARGET, 2, 0, 10, 1
	createvisualtask AnimTask_ShakeMon2, 5, ANIM_DEF_PARTNER, 2, 0, 10, 1
	createvisualtask AnimTask_BlendColorCycle, 2, F_PAL_DEF_SIDE, 2, 2, 0, 12, RGB(30, 0, 31)
	createsprite gAcidPoisonDropletSpriteTemplate, ANIM_TARGET, 2, 0, -22, 0, 15, 55
	playsewithpan SE_M_BUBBLE, SOUND_PAN_TARGET
	delay 10
	createsprite gAcidPoisonDropletSpriteTemplate, ANIM_TARGET, 2, -26, -24, 0, 15, 55
	playsewithpan SE_M_BUBBLE, SOUND_PAN_TARGET
	delay 10
	createsprite gAcidPoisonDropletSpriteTemplate, ANIM_TARGET, 2, 15, -27, 0, 15, 50
	playsewithpan SE_M_BUBBLE, SOUND_PAN_TARGET
	delay 10
	createsprite gAcidPoisonDropletSpriteTemplate, ANIM_TARGET, 2, -15, -17, 0, 10, 45
	playsewithpan SE_M_BUBBLE, SOUND_PAN_TARGET
	delay 10
	createsprite gAcidPoisonDropletSpriteTemplate, ANIM_TARGET, 2, 27, -22, 0, 15, 50
	playsewithpan SE_M_BUBBLE, SOUND_PAN_TARGET
	waitforvisualfinish
	clearmonbg ANIM_DEF_PARTNER
	end

Move_BONEMERANG:
	loadspritegfx ANIM_TAG_BONE
	loadspritegfx ANIM_TAG_IMPACT
	monbg ANIM_DEF_PARTNER
	splitbgprio ANIM_TARGET
	setalpha 12, 8
	playsewithpan SE_M_BONEMERANG, SOUND_PAN_ATTACKER
	createsprite gBonemerangSpriteTemplate, ANIM_ATTACKER, 2
	delay 20
	playsewithpan SE_M_HORN_ATTACK, SOUND_PAN_TARGET
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 2, 0, 0, ANIM_TARGET, 1
	createvisualtask AnimTask_ShakeMon, 5, ANIM_TARGET, 5, 0, 5, 1
	delay 17
	playsewithpan SE_M_VITAL_THROW, SOUND_PAN_ATTACKER
	createsprite gHorizontalLungeSpriteTemplate, ANIM_ATTACKER, 2, 6, -4
	waitforvisualfinish
	clearmonbg ANIM_DEF_PARTNER
	blendoff
	end

Move_BONE_CLUB:
	loadspritegfx ANIM_TAG_BONE
	loadspritegfx ANIM_TAG_IMPACT
	monbg ANIM_DEF_PARTNER
	splitbgprio ANIM_TARGET
	setalpha 12, 8
	playsewithpan SE_M_BONEMERANG, SOUND_PAN_TARGET
	createsprite gSpinningBoneSpriteTemplate, ANIM_ATTACKER, 2, -42, -25, 0, 0, 15
	delay 12
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 2, 0, 0, ANIM_TARGET, 1
	createvisualtask AnimTask_ShakeMon, 5, ANIM_TARGET, 0, 5, 5, 1
	createsprite gComplexPaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG | F_PAL_ATTACKER | F_PAL_TARGET, 5, 1, RGB_BLACK, 10, RGB_BLACK, 0
	playsewithpan SE_M_VITAL_THROW2, SOUND_PAN_TARGET
	waitforvisualfinish
	clearmonbg ANIM_DEF_PARTNER
	blendoff
	end

Move_BONE_RUSH:
	loadspritegfx ANIM_TAG_BONE
	loadspritegfx ANIM_TAG_IMPACT
	monbg ANIM_DEF_PARTNER
	setalpha 12, 8
	playsewithpan SE_M_BONEMERANG, SOUND_PAN_TARGET
	createsprite gSpinningBoneSpriteTemplate, ANIM_ATTACKER, 2, -42, -25, 0, 0, 15
	delay 12
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 2, 0, 0, ANIM_TARGET, 2
	createvisualtask AnimTask_ShakeMon, 5, ANIM_TARGET, 0, 3, 5, 1
	playsewithpan SE_M_HORN_ATTACK, SOUND_PAN_TARGET
	waitforvisualfinish
	clearmonbg ANIM_DEF_PARTNER
	blendoff
	end

Move_SPIKES:
	loadspritegfx ANIM_TAG_SPIKES
	monbg ANIM_DEF_PARTNER
	playsewithpan SE_M_JUMP_KICK, SOUND_PAN_ATTACKER
	waitplaysewithpan SE_M_HORN_ATTACK, SOUND_PAN_TARGET, 28
	createsprite gSpikesSpriteTemplate, ANIM_TARGET, 2, 20, 0, 0, 24, 30
	delay 10
	playsewithpan SE_M_JUMP_KICK, SOUND_PAN_ATTACKER
	waitplaysewithpan SE_M_HORN_ATTACK, SOUND_PAN_TARGET, 28
	createsprite gSpikesSpriteTemplate, ANIM_TARGET, 2, 20, 0, -24, 24, 30
	delay 10
	waitplaysewithpan SE_M_HORN_ATTACK, SOUND_PAN_TARGET, 28
	createsprite gSpikesSpriteTemplate, ANIM_TARGET, 2, 20, 0, 24, 24, 30
	waitforvisualfinish
	clearmonbg ANIM_DEF_PARTNER
	end

Move_MEGAHORN:
	loadspritegfx ANIM_TAG_HORN_HIT_2
	loadspritegfx ANIM_TAG_IMPACT
	monbg ANIM_DEF_PARTNER
	playsewithpan SE_M_DRAGON_RAGE, SOUND_PAN_ATTACKER
	jumpifcontest MegahornInContest
	fadetobg BG_DRILL
	waitbgfadeout
	createvisualtask AnimTask_StartSlidingBg, 5, -2304, 768, 1, -1
MegahornContinue:
	waitbgfadein
	setalpha 12, 8
	createvisualtask AnimTask_ShakeMon, 5, ANIM_ATTACKER, 2, 0, 15, 1
	waitforvisualfinish
	delay 10
	createsprite gSlideMonToOffsetSpriteTemplate, ANIM_ATTACKER, 2, 0, 24, 0, 0, 6
	delay 3
	createsprite gMegahornHornSpriteTemplate, ANIM_ATTACKER, 3, -42, 25, 0, 0, 6
	delay 4
	playsewithpan SE_M_VICEGRIP, SOUND_PAN_TARGET
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 2, 0, 0, ANIM_TARGET, 0
	createsprite gSlideMonToOffsetSpriteTemplate, ANIM_ATTACKER, 2, 1, -16, 4, 1, 4
	waitforvisualfinish
	createvisualtask AnimTask_ShakeMonInPlace, 2, ANIM_TARGET, -4, 1, 12, 1
	createsprite gComplexPaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG | F_PAL_ATTACKER | F_PAL_TARGET, 5, 1, RGB_WHITE, 10, RGB_BLACK, 0
	delay 10
	createsprite gSlideMonToOriginalPosSpriteTemplate, ANIM_ATTACKER, 2, 0, 0, 11
	delay 3
	createsprite gSlideMonToOriginalPosSpriteTemplate, ANIM_ATTACKER, 2, 1, 0, 7
	waitforvisualfinish
	waitforvisualfinish  @ Redundant
	clearmonbg ANIM_DEF_PARTNER
	blendoff
	restorebg
	waitbgfadeout
	setarg 7, 0xFFFF
	waitbgfadein
	end

MegahornInContest:
	fadetobg BG_DRILL_CONTESTS
	waitbgfadeout
	createvisualtask AnimTask_StartSlidingBg, 5, 2304, 768, 0, -1
	goto MegahornContinue

Move_GUST:
	loadspritegfx ANIM_TAG_GUST
	loadspritegfx ANIM_TAG_IMPACT
	monbg ANIM_DEF_PARTNER
	splitbgprio ANIM_TARGET
	setalpha 12, 8
	playsewithpan SE_M_GUST, SOUND_PAN_TARGET
	createsprite gEllipticalGustSpriteTemplate, ANIM_ATTACKER, 2, 0, -16
	createvisualtask AnimTask_AnimateGustTornadoPalette, 5, 1, 70
	waitforvisualfinish
	createvisualtask AnimTask_ShakeMon2, 5, ANIM_TARGET, 1, 0, 7, 1
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 2, 0, 0, ANIM_TARGET, 2
	playsewithpan SE_M_GUST2, SOUND_PAN_TARGET
	waitforvisualfinish
	clearmonbg ANIM_DEF_PARTNER
	blendoff
	end

Move_WING_ATTACK:
	loadspritegfx ANIM_TAG_GUST
	loadspritegfx ANIM_TAG_IMPACT
	monbg ANIM_DEF_PARTNER
	splitbgprio ANIM_TARGET
	setalpha 12, 8
	loopsewithpan SE_M_WING_ATTACK, SOUND_PAN_ATTACKER, 20, 2
	createvisualtask AnimTask_TranslateMonElliptical, 2, 0, 12, 4, 1, 4
	createvisualtask AnimTask_AnimateGustTornadoPalette, 5, 1, 70
	createsprite gGustToTargetSpriteTemplate, ANIM_ATTACKER, 2, -25, 0, 0, 0, 20
	createsprite gGustToTargetSpriteTemplate, ANIM_ATTACKER, 2, 25, 0, 0, 0, 20
	delay 24
	createsprite gSlideMonToOffsetSpriteTemplate, ANIM_ATTACKER, 2, 0, 24, 0, 0, 9
	delay 17
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 2, 16, 0, ANIM_TARGET, 1
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 2, -16, 0, ANIM_TARGET, 1
	loopsewithpan SE_M_DOUBLE_SLAP, SOUND_PAN_TARGET, 5, 2
	waitforvisualfinish
	createsprite gSlideMonToOriginalPosSpriteTemplate, ANIM_ATTACKER, 2, 0, 0, 11
	waitforvisualfinish
	clearmonbg ANIM_DEF_PARTNER
	blendoff
	end

Move_PECK:
	loadspritegfx ANIM_TAG_IMPACT
	playsewithpan SE_M_HORN_ATTACK, SOUND_PAN_TARGET
	createvisualtask AnimTask_RotateMonToSideAndRestore, 2, 3, -768, ANIM_TARGET, 2
	createsprite gFlashingHitSplatSpriteTemplate, ANIM_TARGET, 3, -12, 0, ANIM_TARGET, 3
	waitforvisualfinish
	end

Move_AEROBLAST:
	loadspritegfx ANIM_TAG_AIR_WAVE_2
	loadspritegfx ANIM_TAG_IMPACT
	monbg ANIM_DEF_PARTNER
	call SetSkyBg
	splitbgprio ANIM_TARGET
	setalpha 12, 8
	call AeroblastBeam
	createvisualtask AnimTask_ShakeMon, 5, ANIM_TARGET, 5, 0, 50, 1
	call AeroblastBeam
	call AeroblastBeam
	call AeroblastBeam
	call AeroblastBeam
	waitforvisualfinish
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 2, 0, 0, ANIM_TARGET, 0
	playsewithpan SE_M_RAZOR_WIND, SOUND_PAN_TARGET
	waitforvisualfinish
	clearmonbg ANIM_DEF_PARTNER
	blendoff
	delay 0
	call UnsetSkyBg
	end

AeroblastBeam:
	playsewithpan SE_M_JUMP_KICK, SOUND_PAN_ATTACKER
	createsprite gAirWaveCrescentSpriteTemplate, ANIM_ATTACKER, 2, 14, -12, 0, -12, 15, 0, 0
	createsprite gAirWaveCrescentSpriteTemplate, ANIM_ATTACKER, 2, 26, 8, 12, 8, 15, 0, 0
	delay 3
	playsewithpan SE_M_JUMP_KICK, SOUND_PAN_ATTACKER
	createsprite gAirWaveCrescentSpriteTemplate, ANIM_ATTACKER, 2, 14, -12, 0, -12, 15, 1, 0
	createsprite gAirWaveCrescentSpriteTemplate, ANIM_ATTACKER, 2, 26, 8, 12, 8, 15, 1, 0
	delay 3
	playsewithpan SE_M_JUMP_KICK, SOUND_PAN_ATTACKER
	createsprite gAirWaveCrescentSpriteTemplate, ANIM_ATTACKER, 2, 14, -12, 0, -12, 15, 2, 0
	createsprite gAirWaveCrescentSpriteTemplate, ANIM_ATTACKER, 2, 26, 8, 12, 8, 15, 2, 0
	delay 3
	playsewithpan SE_M_JUMP_KICK, SOUND_PAN_ATTACKER
	createsprite gAirWaveCrescentSpriteTemplate, ANIM_ATTACKER, 2, 14, -12, 0, -12, 15, 3, 0
	createsprite gAirWaveCrescentSpriteTemplate, ANIM_ATTACKER, 2, 26, 8, 12, 8, 15, 3, 0
	delay 3
	return

Move_WATER_GUN:
	loadspritegfx ANIM_TAG_SMALL_BUBBLES
	loadspritegfx ANIM_TAG_WATER_IMPACT
	monbg ANIM_DEF_PARTNER
	splitbgprio ANIM_TARGET
	setalpha 12, 8
	createsprite gWaterGunProjectileSpriteTemplate, ANIM_ATTACKER, 2, 20, 0, 0, 0, 40, -25
	playsewithpan SE_M_BUBBLE, SOUND_PAN_ATTACKER
	waitforvisualfinish
	createvisualtask AnimTask_ShakeMon2, 5, ANIM_TARGET, 1, 0, 8, 1
	createsprite gWaterHitSplatSpriteTemplate, ANIM_ATTACKER, 4, 0, 0, ANIM_TARGET, 2
	createsprite gWaterGunDropletSpriteTemplate, ANIM_ATTACKER, 2, 0, -15, 0, 15, 55
	playsewithpan SE_M_CRABHAMMER, SOUND_PAN_TARGET
	delay 10
	createsprite gWaterGunDropletSpriteTemplate, ANIM_ATTACKER, 2, 15, -20, 0, 15, 50
	playsewithpan SE_M_CRABHAMMER, SOUND_PAN_TARGET
	delay 10
	createsprite gWaterGunDropletSpriteTemplate, ANIM_ATTACKER, 2, -15, -10, 0, 10, 45
	playsewithpan SE_M_CRABHAMMER, SOUND_PAN_TARGET
	waitforvisualfinish
	clearmonbg ANIM_DEF_PARTNER
	blendoff
	end

Move_CRABHAMMER:
	loadspritegfx ANIM_TAG_ICE_CRYSTALS
	loadspritegfx ANIM_TAG_WATER_IMPACT
	monbg ANIM_DEF_PARTNER
	setalpha 12, 8
	createsprite gWaterHitSplatSpriteTemplate, ANIM_ATTACKER, 4, 0, 0, ANIM_TARGET, 0
	playsewithpan SE_M_VITAL_THROW2, SOUND_PAN_TARGET
	delay 1
	createsprite gComplexPaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG | F_PAL_BATTLERS, 3, 1, RGB(13, 21, 31), 10, RGB_BLACK, 0
	createsprite gSlideMonToOffsetSpriteTemplate, ANIM_ATTACKER, 2, 1, -24, 0, 0, 4
	waitforvisualfinish
	delay 8
	waitforvisualfinish
	createsprite gSlideMonToOriginalPosSpriteTemplate, ANIM_ATTACKER, 2, 1, 0, 4
	waitforvisualfinish
	loopsewithpan SE_M_CRABHAMMER, SOUND_PAN_TARGET, 20, 3
	createvisualtask AnimTask_ShakeMon, 5, ANIM_TARGET, 0, 4, 8, 1
	createsprite gSmallBubblePairSpriteTemplate, ANIM_ATTACKER, 2, 10, 10, 20, ANIM_TARGET
	delay 4
	createsprite gSmallBubblePairSpriteTemplate, ANIM_ATTACKER, 2, 20, -20, 20, ANIM_TARGET
	delay 4
	createsprite gSmallBubblePairSpriteTemplate, ANIM_ATTACKER, 2, -15, 15, 20, ANIM_TARGET
	delay 4
	createsprite gSmallBubblePairSpriteTemplate, ANIM_ATTACKER, 2, 0, 0, 20, ANIM_TARGET
	delay 4
	createsprite gSmallBubblePairSpriteTemplate, ANIM_ATTACKER, 2, -10, -20, 20, ANIM_TARGET
	delay 4
	createsprite gSmallBubblePairSpriteTemplate, ANIM_ATTACKER, 2, 16, -8, 20, ANIM_TARGET
	delay 4
	createsprite gSmallBubblePairSpriteTemplate, ANIM_ATTACKER, 2, 5, 8, 20, ANIM_TARGET
	delay 4
	createsprite gSmallBubblePairSpriteTemplate, ANIM_ATTACKER, 2, -16, 0, 20, ANIM_TARGET
	waitforvisualfinish
	clearmonbg ANIM_DEF_PARTNER
	blendoff
	end

Move_SURF:
	createvisualtask AnimTask_CreateSurfWave, 2, FALSE
	delay 24
	panse SE_M_SURF, SOUND_PAN_ATTACKER, SOUND_PAN_TARGET, +2, 0
	waitforvisualfinish
	end

Move_FLAMETHROWER:
	loadspritegfx ANIM_TAG_SMALL_EMBER
	monbg ANIM_DEF_PARTNER
	splitbgprio ANIM_TARGET
	setalpha 12, 8
	createvisualtask AnimTask_ShakeMon, 5, ANIM_ATTACKER, 0, 2, 46, 1
	delay 6
	createvisualtask AnimTask_StartSinAnimTimer, 5, 100
	panse SE_M_FLAMETHROWER, SOUND_PAN_ATTACKER, SOUND_PAN_TARGET, +2, 0
	call FlamethrowerCreateFlames
	call FlamethrowerCreateFlames
	call FlamethrowerCreateFlames
	createvisualtask AnimTask_ShakeMon, 5, ANIM_TARGET, 3, 0, 43, 1
	call FlamethrowerCreateFlames
	call FlamethrowerCreateFlames
	call FlamethrowerCreateFlames
	call FlamethrowerCreateFlames
	call FlamethrowerCreateFlames
	call FlamethrowerCreateFlames
	call FlamethrowerCreateFlames
	call FlamethrowerCreateFlames
	waitforvisualfinish
	clearmonbg ANIM_DEF_PARTNER
	blendoff
	end

FlamethrowerCreateFlames:
	createsprite gFlamethrowerFlameSpriteTemplate, ANIM_ATTACKER, 3, 10, 10, 0, 16
	delay 2
	createsprite gFlamethrowerFlameSpriteTemplate, ANIM_ATTACKER, 3, 10, 10, 0, 16
	delay 2
	return

@ Also used by Sandstorm weather
Move_SANDSTORM:
	loadspritegfx ANIM_TAG_FLYING_DIRT
	playsewithpan SE_M_SANDSTORM, 0
	createvisualtask AnimTask_LoadSandstormBackground, 5, FALSE
	delay 16
	createsprite gFlyingSandCrescentSpriteTemplate, ANIM_ATTACKER, 40, 10, 2304, 96, 0
	delay 10
	createsprite gFlyingSandCrescentSpriteTemplate, ANIM_ATTACKER, 40, 90, 2048, 96, 0
	delay 10
	createsprite gFlyingSandCrescentSpriteTemplate, ANIM_ATTACKER, 40, 50, 2560, 96, 0
	delay 10
	createsprite gFlyingSandCrescentSpriteTemplate, ANIM_ATTACKER, 40, 20, 2304, 96, 0
	delay 10
	createsprite gFlyingSandCrescentSpriteTemplate, ANIM_ATTACKER, 40, 70, 1984, 96, 0
	delay 10
	createsprite gFlyingSandCrescentSpriteTemplate, ANIM_ATTACKER, 40, 0, 2816, 96, 0
	delay 10
	createsprite gFlyingSandCrescentSpriteTemplate, ANIM_ATTACKER, 40, 60, 2560, 96, 0
	end

Move_WHIRLPOOL:
	loadspritegfx ANIM_TAG_WATER_ORB
	monbg ANIM_DEF_PARTNER
	splitbgprio ANIM_TARGET
	setalpha 12, 8
	delay 0
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 0, F_PAL_TARGET, 2, 0, 7, RGB(0, 13, 23)
	playsewithpan SE_M_WHIRLPOOL, SOUND_PAN_TARGET
	createvisualtask AnimTask_ShakeMon, 5, ANIM_TARGET, 0, 2, 50, 1
	call WhirlpoolEffect
	call WhirlpoolEffect
	call WhirlpoolEffect
	delay 12
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 0, F_PAL_TARGET, 2, 7, 0, RGB(0, 13, 23)
	waitforvisualfinish
	clearmonbg ANIM_DEF_PARTNER
	end

WhirlpoolEffect:
	createsprite gWhirlpoolSpriteTemplate, ANIM_TARGET, 2, 0, 28, 384, 50, 8, 50, ANIM_TARGET
	delay 2
	createsprite gWhirlpoolSpriteTemplate, ANIM_TARGET, 2, 0, 32, 240, 40, 11, -46, ANIM_TARGET
	delay 2
	createsprite gWhirlpoolSpriteTemplate, ANIM_TARGET, 2, 0, 33, 416, 40, 4, 42, ANIM_TARGET
	delay 2
	createsprite gWhirlpoolSpriteTemplate, ANIM_TARGET, 2, 0, 31, 288, 45, 6, -42, ANIM_TARGET
	delay 2
	createsprite gWhirlpoolSpriteTemplate, ANIM_TARGET, 2, 0, 28, 448, 45, 11, 46, ANIM_TARGET
	delay 2
	createsprite gWhirlpoolSpriteTemplate, ANIM_TARGET, 2, 0, 33, 464, 50, 10, -50, ANIM_TARGET
	delay 2
	return

Move_FLY:
	loadspritegfx ANIM_TAG_ROUND_SHADOW
	loadspritegfx ANIM_TAG_IMPACT
	choosetwoturnanim FlySetUp, FlyUnleash

FlyEnd:
	waitforvisualfinish
	end

FlySetUp:
	playsewithpan SE_M_FLY, SOUND_PAN_ATTACKER
	createsprite gFlyBallUpSpriteTemplate, ANIM_ATTACKER, 2, 0, 0, 13, 336
	goto FlyEnd

FlyUnleash:
	monbg ANIM_DEF_PARTNER
	setalpha 12, 8
	playsewithpan SE_M_DOUBLE_TEAM, SOUND_PAN_ATTACKER
	createsprite gFlyBallAttackSpriteTemplate, ANIM_ATTACKER, 2, 20
	delay 20
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 2, 0, 0, ANIM_TARGET, 0
	createvisualtask AnimTask_ShakeMon, 5, ANIM_TARGET, 6, 0, 8, 1
	playsewithpan SE_M_RAZOR_WIND, SOUND_PAN_TARGET
	waitforvisualfinish
	clearmonbg ANIM_DEF_PARTNER
	blendoff
	goto FlyEnd

Move_BOUNCE:
	loadspritegfx ANIM_TAG_ROUND_SHADOW
	loadspritegfx ANIM_TAG_IMPACT
	choosetwoturnanim BounceSetUp, BounceUnleash
BounceEnd:
	end

BounceSetUp:
	playsewithpan SE_M_TELEPORT, SOUND_PAN_ATTACKER
	createsprite gBounceBallShrinkSpriteTemplate, ANIM_ATTACKER, 2, 0, 0
	goto BounceEnd

BounceUnleash:
	monbg ANIM_DEF_PARTNER
	setalpha 12, 8
	playsewithpan SE_M_SWAGGER, SOUND_PAN_TARGET
	createsprite gBounceBallLandSpriteTemplate, ANIM_TARGET, 3
	delay 7
	playsewithpan SE_M_MEGA_KICK2, SOUND_PAN_TARGET
	createsprite gBasicHitSplatSpriteTemplate, ANIM_TARGET, 2, 0, 0, ANIM_TARGET, 0
	createvisualtask AnimTask_ShakeMon, 5, ANIM_TARGET, 0, 5, 11, 1
	waitforvisualfinish
	clearmonbg ANIM_DEF_PARTNER
	blendoff
	goto BounceEnd

Move_KARATE_CHOP:
	loadspritegfx ANIM_TAG_HANDS_AND_FEET
	loadspritegfx ANIM_TAG_IMPACT
	monbg ANIM_DEF_PARTNER
	splitbgprio ANIM_TARGET
	setalpha 12, 8
	playsewithpan SE_M_DOUBLE_TEAM, SOUND_PAN_TARGET
	createsprite gKarateChopSpriteTemplate, ANIM_ATTACKER, 2, -16, 0, 0, 0, 10, 1, 3, 0
	waitforvisualfinish
	playsewithpan SE_M_COMET_PUNCH, SOUND_PAN_TARGET
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 3, 0, 0, ANIM_TARGET, 2
	createvisualtask AnimTask_ShakeMon, 5, ANIM_TARGET, 4, 0, 6, 1
	waitforvisualfinish
	clearmonbg ANIM_DEF_PARTNER
	blendoff
	end

Move_CROSS_CHOP:
	loadspritegfx ANIM_TAG_HANDS_AND_FEET
	loadspritegfx ANIM_TAG_CROSS_IMPACT
	monbg ANIM_DEF_PARTNER
	setalpha 12, 8
	playsewithpan SE_M_MEGA_KICK, SOUND_PAN_TARGET
	createsprite gCrossChopHandSpriteTemplate, ANIM_ATTACKER, 2, 0, 0, 0
	createsprite gCrossChopHandSpriteTemplate, ANIM_ATTACKER, 2, 0, 0, 1
	delay 40
	playsewithpan SE_M_RAZOR_WIND, SOUND_PAN_TARGET
	createsprite gComplexPaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG | F_PAL_BATTLERS, 3, 1, RGB_WHITE, 10, RGB_BLACK, 10
	createsprite gCrossImpactSpriteTemplate, ANIM_ATTACKER, 3, 0, 0, 1, 20
	createvisualtask AnimTask_ShakeMon, 5, ANIM_TARGET, 7, 0, 9, 1
	waitforvisualfinish
	clearmonbg ANIM_DEF_PARTNER
	blendoff
	end

Move_JUMP_KICK:
	loadspritegfx ANIM_TAG_HANDS_AND_FEET
	loadspritegfx ANIM_TAG_IMPACT
	monbg ANIM_DEF_PARTNER
	setalpha 12, 8
	createsprite gHorizontalLungeSpriteTemplate, ANIM_ATTACKER, 2, 4, 4
	delay 3
	createsprite gJumpKickSpriteTemplate, ANIM_ATTACKER, 2, -16, 8, 0, 0, 10, ANIM_TARGET, 1, 1
	playsewithpan SE_M_JUMP_KICK, SOUND_PAN_TARGET
	waitforvisualfinish
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 1, 0, 0, ANIM_TARGET, 1
	createvisualtask AnimTask_ShakeMon, 5, ANIM_TARGET, 5, 0, 7, 1
	playsewithpan SE_M_COMET_PUNCH, SOUND_PAN_TARGET
	waitforvisualfinish
	clearmonbg ANIM_DEF_PARTNER
	blendoff
	end

Move_HI_JUMP_KICK:
	loadspritegfx ANIM_TAG_HANDS_AND_FEET
	loadspritegfx ANIM_TAG_IMPACT
	monbg ANIM_DEF_PARTNER
	setalpha 12, 8
	createsprite gSlideMonToOffsetSpriteTemplate, ANIM_ATTACKER, 2, 0, -24, 0, 0, 8
	waitforvisualfinish
	delay 10
	createsprite gSlideMonToOriginalPosSpriteTemplate, ANIM_ATTACKER, 2, 0, 0, 3
	delay 2
	createsprite gJumpKickSpriteTemplate, ANIM_ATTACKER, 2, -16, 8, 0, 0, 10, ANIM_TARGET, 1, 1
	playsewithpan SE_M_JUMP_KICK, SOUND_PAN_TARGET
	waitforvisualfinish
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 2, 0, 0, ANIM_TARGET, 1
	playsewithpan SE_M_VITAL_THROW2, SOUND_PAN_TARGET
	createsprite gSlideMonToOffsetSpriteTemplate, ANIM_ATTACKER, 2, 1, -28, 0, 0, 3
	delay 3
	createvisualtask AnimTask_ShakeMonInPlace, 2, ANIM_TARGET, 3, 0, 11, 1
	waitforvisualfinish
	delay 5
	createsprite gSlideMonToOriginalPosSpriteTemplate, ANIM_ATTACKER, 2, 1, 0, 6
	waitforvisualfinish
	clearmonbg ANIM_DEF_PARTNER
	blendoff
	end

Move_DOUBLE_KICK:
	loadspritegfx ANIM_TAG_HANDS_AND_FEET
	loadspritegfx ANIM_TAG_IMPACT
	monbg ANIM_DEF_PARTNER
	setalpha 12, 8
	createsprite gFistFootRandomPosSpriteTemplate, ANIM_ATTACKER, 3, 1, 20, 1
	createvisualtask AnimTask_ShakeMon, 5, ANIM_TARGET, 4, 0, 6, 1
	playsewithpan SE_M_VITAL_THROW2, SOUND_PAN_TARGET
	waitforvisualfinish
	waitforvisualfinish  @ Redundant
	clearmonbg ANIM_DEF_PARTNER
	blendoff
	end

Move_TRIPLE_KICK:
	loadspritegfx ANIM_TAG_HANDS_AND_FEET
	loadspritegfx ANIM_TAG_IMPACT
	monbg ANIM_DEF_PARTNER
	setalpha 12, 8
	playsewithpan SE_M_VITAL_THROW2, SOUND_PAN_TARGET
	jumpifmoveturn 0, TripleKickLeft
	jumpifmoveturn 1, TripleKickRight
	goto TripleKickCenter

TripleKickContinue:
	waitforvisualfinish
	clearmonbg ANIM_DEF_PARTNER
	blendoff
	end

TripleKickLeft:
	createsprite gFistFootSpriteTemplate, ANIM_TARGET, 4, -16, -8, 20, 1, 1
	createsprite gBasicHitSplatSpriteTemplate, ANIM_TARGET, 3, -16, -16, ANIM_TARGET, 2
	createvisualtask AnimTask_ShakeMon, 5, ANIM_TARGET, 4, 0, 6, 1
	goto TripleKickContinue

TripleKickRight:
	createsprite gFistFootSpriteTemplate, ANIM_TARGET, 4, 8, 8, 20, 1, 1
	createsprite gBasicHitSplatSpriteTemplate, ANIM_TARGET, 3, 8, 0, ANIM_TARGET, 2
	createvisualtask AnimTask_ShakeMon, 5, ANIM_TARGET, 4, 0, 6, 1
	goto TripleKickContinue

TripleKickCenter:
	createsprite gFistFootSpriteTemplate, ANIM_TARGET, 4, 0, 0, 20, 1, 1
	createsprite gBasicHitSplatSpriteTemplate, ANIM_TARGET, 3, 0, -8, ANIM_TARGET, 1
	createvisualtask AnimTask_ShakeMon, 5, ANIM_TARGET, 6, 0, 8, 1
	goto TripleKickContinue

Move_DYNAMIC_PUNCH:
	loadspritegfx ANIM_TAG_HANDS_AND_FEET
	loadspritegfx ANIM_TAG_IMPACT
	loadspritegfx ANIM_TAG_EXPLOSION
	loadspritegfx ANIM_TAG_EXPLOSION_6
	delay 1
	monbg ANIM_DEF_PARTNER
	setalpha 12, 8
	playsewithpan SE_M_VITAL_THROW2, SOUND_PAN_TARGET
	createsprite gFistFootSpriteTemplate, ANIM_TARGET, 3, 0, 0, 20, 1, 0
	createsprite gBasicHitSplatSpriteTemplate, ANIM_TARGET, 2, 0, 0, ANIM_TARGET, 0
	createvisualtask AnimTask_ShakeMon, 5, ANIM_TARGET, 5, 0, 7, 1
	delay 1
	waitsound
	playsewithpan SE_M_SELF_DESTRUCT, SOUND_PAN_TARGET
	createvisualtask AnimTask_ShakeMon2, 5, ANIM_TARGET, 5, 0, 28, 1
	createsprite gExplosionSpriteTemplate, ANIM_ATTACKER, 3, 0, 0, 1, 1
	delay 6
	playsewithpan SE_M_SELF_DESTRUCT, SOUND_PAN_TARGET
	createsprite gExplosionSpriteTemplate, ANIM_ATTACKER, 3, 24, -24, 1, 1
	delay 6
	playsewithpan SE_M_SELF_DESTRUCT, SOUND_PAN_TARGET
	createsprite gExplosionSpriteTemplate, ANIM_ATTACKER, 3, -16, 16, 1, 1
	delay 6
	playsewithpan SE_M_SELF_DESTRUCT, SOUND_PAN_TARGET
	createsprite gExplosionSpriteTemplate, ANIM_ATTACKER, 3, -24, -12, 1, 1
	delay 6
	playsewithpan SE_M_SELF_DESTRUCT, SOUND_PAN_TARGET
	createsprite gExplosionSpriteTemplate, ANIM_ATTACKER, 3, 16, 16, 1, 1
	waitforvisualfinish
	clearmonbg ANIM_DEF_PARTNER
	blendoff
	end

Move_COUNTER:
	loadspritegfx ANIM_TAG_IMPACT
	loadspritegfx ANIM_TAG_HANDS_AND_FEET
	monbg ANIM_DEF_PARTNER
	setalpha 12, 8
	createvisualtask AnimTask_TranslateMonEllipticalRespectSide, 2, ANIM_ATTACKER, 18, 6, 1, 4
	playsewithpan SE_M_VITAL_THROW, SOUND_PAN_ATTACKER
	waitforvisualfinish
	createsprite gSlideMonToOffsetSpriteTemplate, ANIM_ATTACKER, 2, 0, 20, 0, 0, 4
	delay 4
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 2, -15, 18, ANIM_TARGET, 0
	playsewithpan SE_M_VITAL_THROW2, SOUND_PAN_TARGET
	delay 1
	createvisualtask AnimTask_ShakeMon, 2, ANIM_TARGET, 5, 0, 25, 1
	createsprite gFistFootSpriteTemplate, ANIM_ATTACKER, 3, -15, 18, 8, 1, 0
	delay 3
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 2, 0, -4, ANIM_TARGET, 0
	playsewithpan SE_M_VITAL_THROW2, SOUND_PAN_TARGET
	delay 1
	createsprite gFistFootSpriteTemplate, ANIM_ATTACKER, 3, 0, -4, 8, 1, 0
	delay 3
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 2, 15, 9, ANIM_TARGET, 0
	playsewithpan SE_M_VITAL_THROW2, SOUND_PAN_TARGET
	delay 1
	createsprite gFistFootSpriteTemplate, ANIM_ATTACKER, 3, 15, 9, 8, 1, 0
	delay 5
	createsprite gSlideMonToOriginalPosSpriteTemplate, ANIM_ATTACKER, 2, 0, 0, 5
	waitforvisualfinish
	clearmonbg ANIM_DEF_PARTNER
	blendoff
	end

Move_VITAL_THROW:
	loadspritegfx ANIM_TAG_IMPACT
	monbg ANIM_DEF_PARTNER
	setalpha 12, 8
	playsewithpan SE_M_VITAL_THROW, SOUND_PAN_ATTACKER
	createvisualtask AnimTask_TranslateMonEllipticalRespectSide, 2, ANIM_ATTACKER, 12, 4, 1, 2
	waitforvisualfinish
	createsprite gSlideMonToOffsetSpriteTemplate, ANIM_ATTACKER, 2, 0, 20, 0, 0, 4
	delay 2
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 3, 0, 0, ANIM_TARGET, 1
	playsewithpan SE_M_VITAL_THROW2, SOUND_PAN_TARGET
	delay 1
	createsprite gSlideMonToOffsetSpriteTemplate, ANIM_ATTACKER, 2, 1, -24, 0, 0, 4
	waitforvisualfinish
	delay 3
	createsprite gSlideMonToOriginalPosSpriteTemplate, ANIM_ATTACKER, 2, 0, 0, 7
	delay 11
	createsprite gSlideMonToOriginalPosSpriteTemplate, ANIM_ATTACKER, 2, 1, 0, 10
	waitforvisualfinish
	clearmonbg ANIM_DEF_PARTNER
	blendoff
	end

Move_ROCK_SMASH:
	loadspritegfx ANIM_TAG_ROCKS
	loadspritegfx ANIM_TAG_IMPACT
	loadspritegfx ANIM_TAG_HANDS_AND_FEET
	monbg ANIM_DEF_PARTNER
	setalpha 12, 8
	delay 1
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 3, 0, 0, ANIM_TARGET, 1
	createsprite gFistFootSpriteTemplate, ANIM_ATTACKER, 2, 0, 0, 8, 1, 0
	playsewithpan SE_M_VITAL_THROW2, SOUND_PAN_TARGET
	createvisualtask AnimTask_ShakeMon, 2, ANIM_TARGET, 3, 0, 5, 1
	waitforvisualfinish
	playsewithpan SE_M_ROCK_THROW, SOUND_PAN_TARGET
	createsprite gRockFragmentSpriteTemplate, ANIM_ATTACKER, 2, 0, 0, 20, 24, 14, 2
	createsprite gRockFragmentSpriteTemplate, ANIM_ATTACKER, 2, 5, 0, -20, 24, 14, 1
	createsprite gRockFragmentSpriteTemplate, ANIM_ATTACKER, 2, 0, 5, 20, -24, 14, 2
	createsprite gRockFragmentSpriteTemplate, ANIM_ATTACKER, 2, -5, 0, -20, -24, 14, 2
	createsprite gRockFragmentSpriteTemplate, ANIM_ATTACKER, 2, 0, -5, 30, 18, 8, 2
	createsprite gRockFragmentSpriteTemplate, ANIM_ATTACKER, 2, 0, 0, 30, -18, 8, 2
	createsprite gRockFragmentSpriteTemplate, ANIM_ATTACKER, 2, 0, 0, -30, 18, 8, 2
	createsprite gRockFragmentSpriteTemplate, ANIM_ATTACKER, 2, 0, 0, -30, -18, 8, 2
	createvisualtask AnimTask_ShakeMon, 2, ANIM_TARGET, 0, 3, 7, 1
	waitforvisualfinish
	clearmonbg ANIM_DEF_PARTNER
	blendoff
	end

Move_SUBMISSION:
	loadspritegfx ANIM_TAG_IMPACT
	monbg ANIM_DEF_PARTNER
	setalpha 12, 8
	playsewithpan SE_M_DOUBLE_TEAM, SOUND_PAN_ATTACKER
	waitplaysewithpan SE_M_COMET_PUNCH, SOUND_PAN_TARGET, 10
	waitplaysewithpan SE_M_DOUBLE_TEAM, SOUND_PAN_ATTACKER, 20
	waitplaysewithpan SE_M_COMET_PUNCH, SOUND_PAN_TARGET, 30
	waitplaysewithpan SE_M_DOUBLE_TEAM, SOUND_PAN_ATTACKER, 40
	waitplaysewithpan SE_M_COMET_PUNCH, SOUND_PAN_TARGET, 50
	waitplaysewithpan SE_M_DOUBLE_TEAM, SOUND_PAN_ATTACKER, 60
	waitplaysewithpan SE_M_COMET_PUNCH, SOUND_PAN_TARGET, 70
	waitplaysewithpan SE_M_DOUBLE_TEAM, SOUND_PAN_ATTACKER, 80
	waitplaysewithpan SE_M_COMET_PUNCH, SOUND_PAN_TARGET, 90
	createvisualtask AnimTask_TranslateMonElliptical, 2, 0, -18, 6, 6, 4
	createvisualtask AnimTask_TranslateMonElliptical, 2, 1, 18, 6, 6, 4
	call SubmissionHit
	call SubmissionHit
	call SubmissionHit
	waitforvisualfinish
	clearmonbg ANIM_DEF_PARTNER
	blendoff
	end

SubmissionHit:
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 3, 0, -12, ANIM_TARGET, 1
	delay 8
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 3, -12, 8, ANIM_TARGET, 1
	delay 8
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 3, 12, 0, ANIM_TARGET, 1
	delay 8
	return

@ Also used by Sunny weather
Move_SUNNY_DAY:
	loadspritegfx ANIM_TAG_SUNLIGHT
	monbg ANIM_ATK_PARTNER
	setalpha 13, 3
	createvisualtask AnimTask_BlendBattleAnimPal, 10, F_PAL_BG | F_PAL_BATTLERS_2, 1, 0, 6, RGB_WHITE
	waitforvisualfinish
	panse_adjustnone SE_M_PETAL_DANCE, SOUND_PAN_ATTACKER, SOUND_PAN_TARGET, +1, 0
	call SunnyDayLightRay
	call SunnyDayLightRay
	call SunnyDayLightRay
	call SunnyDayLightRay
	waitforvisualfinish
	createvisualtask AnimTask_BlendBattleAnimPal, 10, F_PAL_BG | F_PAL_BATTLERS_2, 1, 6, 0, RGB_WHITE
	waitforvisualfinish
	clearmonbg ANIM_ATK_PARTNER
	blendoff
	end

SunnyDayLightRay:
	createsprite gSunlightRaySpriteTemplate, ANIM_ATTACKER, 40
	delay 6
	return

Move_COTTON_SPORE:
	loadspritegfx ANIM_TAG_SPORE
	monbg ANIM_DEF_PARTNER
	splitbgprio ANIM_TARGET
	loopsewithpan SE_M_POISON_POWDER, SOUND_PAN_TARGET, 18, 10
	call CreateCottonSpores
	call CreateCottonSpores
	call CreateCottonSpores
	waitforvisualfinish
	clearmonbg ANIM_DEF_PARTNER
	end

CreateCottonSpores:
	createsprite gSporeParticleSpriteTemplate, ANIM_ATTACKER, 2, 0, -20, 85, 80, 0
	delay 12
	createsprite gSporeParticleSpriteTemplate, ANIM_ATTACKER, 2, 0, -10, 170, 80, 0
	delay 12
	createsprite gSporeParticleSpriteTemplate, ANIM_ATTACKER, 2, 0, -15, 0, 80, 0
	delay 12
	return

Move_SPORE:
	loadspritegfx ANIM_TAG_SPORE
	monbg ANIM_DEF_PARTNER
	setalpha 12, 8
	createvisualtask AnimTask_SporeDoubleBattle, 2
	loopsewithpan SE_M_POISON_POWDER, SOUND_PAN_TARGET, 16, 11
	call CreateSpore
	call CreateSpore
	call CreateSpore
	waitforvisualfinish
	delay 1
	clearmonbg ANIM_DEF_PARTNER
	blendoff
	end

CreateSpore:
	createsprite gSporeParticleSpriteTemplate, ANIM_TARGET, 2, 0, -20, 85, 80, 1
	delay 12
	createsprite gSporeParticleSpriteTemplate, ANIM_TARGET, 2, 0, -10, 170, 80, 1
	delay 12
	createsprite gSporeParticleSpriteTemplate, ANIM_TARGET, 2, 0, -15, 0, 80, 1
	delay 12
	return

Move_PETAL_DANCE:
	loadspritegfx ANIM_TAG_FLOWER
	loadspritegfx ANIM_TAG_IMPACT
	monbg ANIM_DEF_PARTNER
	setalpha 12, 8
	playsewithpan SE_M_PETAL_DANCE, SOUND_PAN_ATTACKER
	createvisualtask AnimTask_TranslateMonEllipticalRespectSide, 2, ANIM_ATTACKER, 12, 6, 6, 3
	createsprite gPetalDanceBigFlowerSpriteTemplate, ANIM_ATTACKER, 2, 0, -24, 8, 140
	createsprite gPetalDanceSmallFlowerSpriteTemplate, ANIM_ATTACKER, 2, 16, -24, 8, 100
	createsprite gPetalDanceSmallFlowerSpriteTemplate, ANIM_ATTACKER, 2, -16, -24, 8, 100
	delay 15
	createsprite gPetalDanceBigFlowerSpriteTemplate, ANIM_ATTACKER, 2, 0, -24, 8, 140
	createsprite gPetalDanceSmallFlowerSpriteTemplate, ANIM_ATTACKER, 2, 32, -24, 8, 100
	createsprite gPetalDanceSmallFlowerSpriteTemplate, ANIM_ATTACKER, 2, -32, -24, 8, 100
	delay 15
	createsprite gPetalDanceBigFlowerSpriteTemplate, ANIM_ATTACKER, 2, 0, -24, 8, 140
	createsprite gPetalDanceSmallFlowerSpriteTemplate, ANIM_ATTACKER, 2, 24, -24, 8, 100
	createsprite gPetalDanceSmallFlowerSpriteTemplate, ANIM_ATTACKER, 2, -24, -24, 8, 100
	delay 30
	createsprite gPetalDanceSmallFlowerSpriteTemplate, ANIM_ATTACKER, 2, 16, -24, 0, 100
	createsprite gPetalDanceSmallFlowerSpriteTemplate, ANIM_ATTACKER, 2, -16, -24, 0, 100
	delay 30
	createsprite gPetalDanceSmallFlowerSpriteTemplate, ANIM_ATTACKER, 2, 20, -16, 14, 80
	createsprite gPetalDanceSmallFlowerSpriteTemplate, ANIM_ATTACKER, 2, -20, -14, 16, 80
	waitforvisualfinish
	createsprite gSlideMonToOffsetSpriteTemplate, ANIM_ATTACKER, 2, 0, 24, 0, 0, 5
	delay 3
	playsewithpan SE_M_MEGA_KICK2, SOUND_PAN_TARGET
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 3, 0, 0, ANIM_TARGET, 0
	createvisualtask AnimTask_ShakeMon, 2, ANIM_TARGET, 6, 0, 8, 1
	waitforvisualfinish
	delay 8
	createsprite gSlideMonToOriginalPosSpriteTemplate, ANIM_ATTACKER, 2, 0, 0, 7
	waitforvisualfinish
	clearmonbg ANIM_DEF_PARTNER
	blendoff
	end

Move_RAZOR_LEAF:
	loadspritegfx ANIM_TAG_LEAF
	loadspritegfx ANIM_TAG_RAZOR_LEAF
	loadspritegfx ANIM_TAG_IMPACT
	monbg ANIM_DEF_PARTNER
	setalpha 12, 8
	delay 1
	loopsewithpan SE_M_POISON_POWDER, SOUND_PAN_ATTACKER, 10, 5
	createsprite gRazorLeafParticleSpriteTemplate, ANIM_ATTACKER, 2, -3, -2, 10
	delay 2
	createsprite gRazorLeafParticleSpriteTemplate, ANIM_ATTACKER, 2, -1, -1, 15
	delay 2
	createsprite gRazorLeafParticleSpriteTemplate, ANIM_ATTACKER, 2, -4, -4, 7
	delay 2
	createsprite gRazorLeafParticleSpriteTemplate, ANIM_ATTACKER, 2, 3, -3, 11
	delay 2
	createsprite gRazorLeafParticleSpriteTemplate, ANIM_ATTACKER, 2, -1, -6, 8
	delay 2
	createsprite gRazorLeafParticleSpriteTemplate, ANIM_ATTACKER, 2, 2, -1, 12
	delay 2
	createsprite gRazorLeafParticleSpriteTemplate, ANIM_ATTACKER, 2, -3, -4, 13
	delay 2
	createsprite gRazorLeafParticleSpriteTemplate, ANIM_ATTACKER, 2, 4, -5, 7
	delay 2
	createsprite gRazorLeafParticleSpriteTemplate, ANIM_ATTACKER, 2, 2, -6, 11
	delay 2
	createsprite gRazorLeafParticleSpriteTemplate, ANIM_ATTACKER, 2, -3, -5, 8
	delay 60
	playsewithpan SE_M_RAZOR_WIND2, SOUND_PAN_ATTACKER
	createsprite gRazorLeafCutterSpriteTemplate, ANIM_TARGET, 3, 20, -10, 20, 0, 22, 20, 1
	createsprite gRazorLeafCutterSpriteTemplate, ANIM_TARGET, 3, 20, -10, 20, 0, 22, -20, 1
	delay 20
	playsewithpan SE_M_RAZOR_WIND, SOUND_PAN_TARGET
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_TARGET, 2, 0, 8, 1
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_DEF_PARTNER, 2, 0, 8, 1
	waitforvisualfinish
	clearmonbg ANIM_DEF_PARTNER
	blendoff
	end

Move_NATURE_POWER:
	@ No actual animation, uses the animation of a move from sNaturePowerMoves instead

Move_ANCIENT_POWER:
	loadspritegfx ANIM_TAG_ROCKS
	loadspritegfx ANIM_TAG_IMPACT
	monbg ANIM_DEF_PARTNER
	setalpha 12, 8
	createsprite gShakeMonOrTerrainSpriteTemplate, ANIM_ATTACKER, 2, 4, 1, 10, 1
	createsprite gAncientPowerRockSpriteTemplate, ANIM_ATTACKER, 2, 20, 32, -48, 50, 2
	createsprite gAncientPowerRockSpriteTemplate, ANIM_ATTACKER, 2, 0, 32, -38, 25, 5
	createsprite gAncientPowerRockSpriteTemplate, ANIM_ATTACKER, 2, 32, 32, -28, 40, 3
	createsprite gAncientPowerRockSpriteTemplate, ANIM_ATTACKER, 2, -20, 32, -48, 50, 2
	createsprite gAncientPowerRockSpriteTemplate, ANIM_ATTACKER, 2, 20, 32, -28, 60, 1
	createsprite gAncientPowerRockSpriteTemplate, ANIM_ATTACKER, 2, 0, 32, -28, 30, 4
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_ATTACKER, 1, 0, 30, 1
	playsewithpan SE_M_DRAGON_RAGE, SOUND_PAN_ATTACKER
	delay 10
	createsprite gAncientPowerRockSpriteTemplate, ANIM_ATTACKER, 2, 15, 32, -48, 25, 5
	createsprite gAncientPowerRockSpriteTemplate, ANIM_ATTACKER, 2, -10, 32, -42, 30, 4
	delay 10
	createsprite gAncientPowerRockSpriteTemplate, ANIM_ATTACKER, 2, 0, 32, -42, 25, 5
	createsprite gAncientPowerRockSpriteTemplate, ANIM_ATTACKER, 2, -25, 32, -48, 30, 4
	waitforvisualfinish
	createsprite gSlideMonToOffsetSpriteTemplate, ANIM_ATTACKER, 2, 0, 16, 0, 0, 4
	delay 3
	playsewithpan SE_M_SELF_DESTRUCT, SOUND_PAN_TARGET
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 3, 0, 0, ANIM_TARGET, 1
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_TARGET, 3, 0, 6, 1
	waitforvisualfinish
	createsprite gSlideMonToOriginalPosSpriteTemplate, ANIM_ATTACKER, 2, 0, 0, 7
	waitforvisualfinish
	clearmonbg ANIM_DEF_PARTNER
	blendoff
	end

Move_OCTAZOOKA:
	loadspritegfx ANIM_TAG_GRAY_SMOKE
	loadspritegfx ANIM_TAG_BLACK_BALL
	playsewithpan SE_M_MEGA_KICK2, SOUND_PAN_ATTACKER
	createsprite gOctazookaBallSpriteTemplate, ANIM_TARGET, 2, 20, 0, 0, 0, 20, 0
	waitforvisualfinish
	playsewithpan SE_M_SELF_DESTRUCT, SOUND_PAN_TARGET
	createsprite gOctazookaSmokeSpriteTemplate, ANIM_TARGET, 2, 8, 8, 1, 0
	delay 2
	createsprite gOctazookaSmokeSpriteTemplate, ANIM_TARGET, 2, -8, -8, 1, 0
	delay 2
	createsprite gOctazookaSmokeSpriteTemplate, ANIM_TARGET, 2, 8, -8, 1, 0
	delay 2
	createsprite gOctazookaSmokeSpriteTemplate, ANIM_TARGET, 2, -8, 8, 1, 0
	waitforvisualfinish
	end

Move_MIST:
	loadspritegfx ANIM_TAG_MIST_CLOUD
	monbg ANIM_ATK_PARTNER
	setalpha 12, 8
	loopsewithpan SE_M_MIST, SOUND_PAN_ATTACKER, 20, 15
	call MistCloud
	call MistCloud
	call MistCloud
	call MistCloud
	call MistCloud
	call MistCloud
	call MistCloud
	delay 32
	createvisualtask AnimTask_BlendColorCycle, 2, F_PAL_ATK_SIDE, 8, 2, 0, 14, RGB_WHITE
	waitforvisualfinish
	clearmonbg ANIM_ATK_PARTNER
	blendoff
	end

MistCloud:
	createsprite gMistCloudSpriteTemplate, ANIM_ATTACKER, 2, 0, -24, 48, 240, 0, 1
	delay 7
	return

Move_HAZE:
	waitforvisualfinish
	playsewithpan SE_M_HAZE, 0
	createvisualtask AnimTask_HazeScrollingFog, 5
	delay 30
	createvisualtask AnimTask_BlendBattleAnimPal, 10, F_PAL_BATTLERS_2, 2, 0, 16, RGB_BLACK
	delay 90
	createvisualtask AnimTask_BlendBattleAnimPal, 10, F_PAL_BATTLERS_2, 1, 16, 0, RGB_BLACK
	end

Move_FIRE_PUNCH:
	loadspritegfx ANIM_TAG_HANDS_AND_FEET
	loadspritegfx ANIM_TAG_SMALL_EMBER
	loadspritegfx ANIM_TAG_IMPACT
	monbg ANIM_DEF_PARTNER
	setalpha 12, 8
	createvisualtask AnimTask_BlendBattleAnimPal, 10, F_PAL_TARGET, 2, 0, 9, RGB_RED
	createsprite gFireSpiralInwardSpriteTemplate, ANIM_TARGET, 1, 0
	createsprite gFireSpiralInwardSpriteTemplate, ANIM_TARGET, 1, 64
	createsprite gFireSpiralInwardSpriteTemplate, ANIM_TARGET, 1, 128
	createsprite gFireSpiralInwardSpriteTemplate, ANIM_TARGET, 1, 196
	playsewithpan SE_M_FLAME_WHEEL, SOUND_PAN_TARGET
	waitforvisualfinish
	createsprite gFistFootSpriteTemplate, ANIM_TARGET, 3, 0, 0, 8, 1, 0
	createsprite gBasicHitSplatSpriteTemplate, ANIM_TARGET, 2, 0, 0, ANIM_TARGET, 1
	createvisualtask AnimTask_ShakeMon, 2, ANIM_TARGET, 0, 3, 15, 1
	call FireSpreadEffect
	delay 4
	playsewithpan SE_M_FIRE_PUNCH, SOUND_PAN_TARGET
	waitforvisualfinish
	createvisualtask AnimTask_BlendBattleAnimPal, 10, F_PAL_TARGET, 0, 9, 0, RGB_RED
	waitforvisualfinish
	clearmonbg ANIM_DEF_PARTNER
	blendoff
	end

FireSpreadEffect:
	createsprite gFireSpreadSpriteTemplate, ANIM_TARGET, 1, 0, 10, 192, 176, 40
	createsprite gFireSpreadSpriteTemplate, ANIM_TARGET, 1, 0, 10, -192, 240, 40
	createsprite gFireSpreadSpriteTemplate, ANIM_TARGET, 1, 0, 10, 192, -160, 40
	createsprite gFireSpreadSpriteTemplate, ANIM_TARGET, 1, 0, 10, -192, -112, 40
	createsprite gFireSpreadSpriteTemplate, ANIM_TARGET, 1, 0, 10, 160, 48, 40
	createsprite gFireSpreadSpriteTemplate, ANIM_TARGET, 1, 0, 10, -224, -32, 40
	createsprite gFireSpreadSpriteTemplate, ANIM_TARGET, 1, 0, 10, 112, -128, 40
	return

Move_LEER:
	loadspritegfx ANIM_TAG_LEER
	monbg ANIM_ATTACKER
	splitbgprio ANIM_ATTACKER
	setalpha 8, 8
	playsewithpan SE_M_LEER, SOUND_PAN_ATTACKER
	createsprite gLeerSpriteTemplate, ANIM_ATTACKER, 2, 24, -12
	createvisualtask AnimTask_ScaleMonAndRestore, 5, -5, -5, 10, ANIM_ATTACKER, 1
	waitforvisualfinish
	delay 10
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_TARGET, 1, 0, 9, 1
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_DEF_PARTNER, 1, 0, 9, 1
	waitforvisualfinish
	clearmonbg ANIM_ATTACKER
	blendoff
	delay 1
	waitforvisualfinish
	end

Move_DREAM_EATER:
	loadspritegfx ANIM_TAG_ORBS
	loadspritegfx ANIM_TAG_BLUE_STAR
	monbg ANIM_DEF_PARTNER
	splitbgprio_foes ANIM_TARGET
	playsewithpan SE_M_PSYBEAM, SOUND_PAN_ATTACKER
	call SetPsychicBackground
	setalpha 8, 8
	playsewithpan SE_M_MINIMIZE, SOUND_PAN_TARGET
	createvisualtask AnimTask_ShakeMon, 2, ANIM_TARGET, 5, 0, 15, 1
	createvisualtask AnimTask_ScaleMonAndRestore, 5, -6, -6, 15, ANIM_TARGET, 1
	waitforvisualfinish
	setalpha 12, 8
	createvisualtask AnimTask_ShakeMon, 2, ANIM_TARGET, 0, 2, 25, 1
	call DreamEaterAbsorb
	waitforvisualfinish
	delay 15
	call HealingEffect
	waitforvisualfinish
	clearmonbg ANIM_DEF_PARTNER
	blendoff
	delay 1
	call UnsetPsychicBackground
	end

DreamEaterAbsorb:
	playsewithpan SE_M_SWAGGER, SOUND_PAN_TARGET
	createsprite gAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 3, 0, 5, 8, 26
	createsprite gAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 3, 5, -18, -40, 35
	createsprite gAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 3, -10, 20, 20, 39
	delay 4
	playsewithpan SE_M_SWAGGER, SOUND_PAN_TARGET
	createsprite gAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 3, 0, 5, 28, 26
	createsprite gAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 3, 10, -5, -8, 26
	createsprite gAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 3, -10, 20, 40, 39
	delay 4
	playsewithpan SE_M_SWAGGER, SOUND_PAN_TARGET
	createsprite gAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 3, 10, -5, -8, 26
	createsprite gAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 3, -5, 15, 16, 33
	createsprite gAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 3, 10, -5, -32, 26
	delay 4
	playsewithpan SE_M_SWAGGER, SOUND_PAN_TARGET
	createsprite gAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 3, 0, -15, -16, 36
	createsprite gAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 3, 0, 5, 8, 26
	createsprite gAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 3, 10, -5, -8, 26
	delay 4
	playsewithpan SE_M_SWAGGER, SOUND_PAN_TARGET
	createsprite gAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 3, -5, 15, 16, 33
	createsprite gAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 3, 0, -15, -16, 36
	createsprite gAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 3, 0, 5, 8, 26
	delay 4
	playsewithpan SE_M_SWAGGER, SOUND_PAN_TARGET
	createsprite gAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 3, 0, 5, 8, 26
	createsprite gAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 3, -5, 15, 16, 33
	createsprite gAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 3, 10, -5, -40, 26
	delay 4
	playsewithpan SE_M_SWAGGER, SOUND_PAN_TARGET
	createsprite gAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 3, -5, 15, 36, 33
	createsprite gAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 3, 10, -5, -8, 26
	createsprite gAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 3, -10, 20, 20, 39
	delay 4
	playsewithpan SE_M_SWAGGER, SOUND_PAN_TARGET
	createsprite gAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 3, 0, 5, 8, 26
	createsprite gAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 3, 0, 5, 8, 26
	createsprite gAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 3, 5, -18, -20, 35
	delay 4
	return

Move_POISON_GAS:
	loadspritegfx ANIM_TAG_PURPLE_GAS_CLOUD
	loadspritegfx ANIM_TAG_POISON_BUBBLE
	delay 0
	monbg ANIM_DEF_PARTNER
	splitbgprio_all
	setalpha 12, 8
	delay 0
	playsewithpan SE_M_MIST, SOUND_PAN_ATTACKER
	createsprite gPoisonGasCloudSpriteTemplate, ANIM_TARGET, 0, 64, 0, 0, -32, -6, 4192, 1072, 0
	delay 4
	playsewithpan SE_M_MIST, SOUND_PAN_ATTACKER
	createsprite gPoisonGasCloudSpriteTemplate, ANIM_TARGET, 0, 64, 0, 0, -32, -6, 4192, 1072, 0
	delay 4
	playsewithpan SE_M_MIST, SOUND_PAN_ATTACKER
	createsprite gPoisonGasCloudSpriteTemplate, ANIM_TARGET, 0, 64, 0, 0, -32, -6, 4192, 1072, 0
	delay 4
	playsewithpan SE_M_MIST, SOUND_PAN_ATTACKER
	createsprite gPoisonGasCloudSpriteTemplate, ANIM_TARGET, 0, 64, 0, 0, -32, -6, 4192, 1072, 0
	delay 4
	playsewithpan SE_M_MIST, SOUND_PAN_ATTACKER
	createsprite gPoisonGasCloudSpriteTemplate, ANIM_TARGET, 0, 64, 0, 0, -32, -6, 4192, 1072, 0
	delay 4
	playsewithpan SE_M_MIST, SOUND_PAN_ATTACKER
	createsprite gPoisonGasCloudSpriteTemplate, ANIM_TARGET, 0, 64, 0, 0, -32, -6, 4192, 1072, 0
	delay 40
	loopsewithpan SE_M_MIST, SOUND_PAN_TARGET, 28, 6
	createvisualtask AnimTask_BlendColorCycle, 2, F_PAL_TARGET, 6, 2, 0, 12, RGB(26, 0, 26)
	waitforvisualfinish
	blendoff
	clearmonbg ANIM_DEF_PARTNER
	delay 0
	end

Move_BIND:
	createvisualtask AnimTask_SwayMon, 5, 0, 6, 3328, 4, ANIM_ATTACKER
	goto BindWrap

BindWrap:
	playsewithpan SE_M_BIND, SOUND_PAN_TARGET
	call BindWrapSqueezeTarget
	call BindWrapSqueezeTarget
	waitforvisualfinish
	end

BindWrapSqueezeTarget:
	createvisualtask AnimTask_ScaleMonAndRestore, 5, 10, -5, 5, ANIM_TARGET, 0
	delay 16
	return

Move_WRAP:
	createvisualtask AnimTask_TranslateMonEllipticalRespectSide, 2, ANIM_ATTACKER, 6, 4, 2, 4
	goto BindWrap

Move_PSYBEAM:
	loadspritegfx ANIM_TAG_GOLD_RING
	playsewithpan SE_M_PSYBEAM, SOUND_PAN_ATTACKER
	call SetPsychicBackground
	createsoundtask SoundTask_LoopSEAdjustPanning, SE_M_PSYBEAM2, SOUND_PAN_ATTACKER, SOUND_PAN_TARGET, 3, 4, 0, 15
	call PsybeamRings
	call PsybeamRings
	createvisualtask AnimTask_SwayMon, 5, 0, 6, 2048, 4, ANIM_TARGET
	createvisualtask AnimTask_BlendColorCycle, 2, F_PAL_TARGET, 2, 2, 0, 12, RGB(31, 18, 31)
	call PsybeamRings
	call PsybeamRings
	call PsybeamRings
	call PsybeamRings
	call PsybeamRings
	call PsybeamRings
	call PsybeamRings
	call PsybeamRings
	call PsybeamRings
	waitforvisualfinish
	delay 1
	call UnsetPsychicBackground
	end

PsybeamRings:
	createsprite gGoldRingSpriteTemplate, ANIM_TARGET, 2, 16, 0, 0, 0, 13, 0
	delay 4
	return

Move_HYPNOSIS:
	loadspritegfx ANIM_TAG_GOLD_RING
	call SetPsychicBackground
	call HypnosisRings
	call HypnosisRings
	call HypnosisRings
	createvisualtask AnimTask_BlendColorCycle, 2, F_PAL_TARGET, 2, 2, 0, 12, RGB(31, 18, 31)
	waitforvisualfinish
	delay 1
	call UnsetPsychicBackground
	end

HypnosisRings:
	playsewithpan SE_M_SUPERSONIC, SOUND_PAN_ATTACKER
	createsprite gGoldRingSpriteTemplate, ANIM_TARGET, 2, 0, 8, 0, 8, 27, 0
	createsprite gGoldRingSpriteTemplate, ANIM_TARGET, 2, 16, -8, 0, -8, 27, 0
	delay 6
	return

Move_PSYWAVE:
	loadspritegfx ANIM_TAG_BLUE_RING
	playsewithpan SE_M_PSYBEAM, SOUND_PAN_ATTACKER
	call SetPsychicBackground
	createvisualtask AnimTask_StartSinAnimTimer, 5, 100
	createsoundtask SoundTask_LoopSEAdjustPanning, SE_M_TELEPORT, SOUND_PAN_ATTACKER, SOUND_PAN_TARGET, 2, 9, 0, 10
	call PsywaveRings
	call PsywaveRings
	createvisualtask AnimTask_BlendColorCycle, 2, F_PAL_TARGET, 1, 4, 0, 12, RGB(31, 18, 31)
	call PsywaveRings
	call PsywaveRings
	call PsywaveRings
	call PsywaveRings
	waitforvisualfinish
	delay 1
	call UnsetPsychicBackground
	end

PsywaveRings:
	createsprite gPsywaveRingSpriteTemplate, ANIM_TARGET, 3, 10, 10, 0, 16
	delay 4
	createsprite gPsywaveRingSpriteTemplate, ANIM_TARGET, 3, 10, 10, 0, 16
	delay 4
	return

Move_ZAP_CANNON:
	loadspritegfx ANIM_TAG_BLACK_BALL_2
	loadspritegfx ANIM_TAG_SPARK_2
	playsewithpan SE_M_THUNDER_WAVE, SOUND_PAN_ATTACKER
	createsprite gZapCannonBallSpriteTemplate, ANIM_TARGET, 3, 10, 0, 0, 0, 30, 0
	createsprite gZapCannonSparkSpriteTemplate, ANIM_TARGET, 4, 10, 0, 16, 30, 0, 40, 0
	createsprite gZapCannonSparkSpriteTemplate, ANIM_TARGET, 4, 10, 0, 16, 30, 64, 40, 1
	createsprite gZapCannonSparkSpriteTemplate, ANIM_TARGET, 4, 10, 0, 16, 30, 128, 40, 0
	createsprite gZapCannonSparkSpriteTemplate, ANIM_TARGET, 4, 10, 0, 16, 30, 192, 40, 2
	createsprite gZapCannonSparkSpriteTemplate, ANIM_TARGET, 4, 10, 0, 8, 30, 32, 40, 0
	createsprite gZapCannonSparkSpriteTemplate, ANIM_TARGET, 4, 10, 0, 8, 30, 96, 40, 1
	createsprite gZapCannonSparkSpriteTemplate, ANIM_TARGET, 4, 10, 0, 8, 30, 160, 40, 0
	createsprite gZapCannonSparkSpriteTemplate, ANIM_TARGET, 4, 10, 0, 8, 30, 224, 40, 2
	waitforvisualfinish
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_TARGET, 4, 0, 5, 1
	delay 15
	waitplaysewithpan SE_M_THUNDERBOLT2, SOUND_PAN_TARGET, 19
	call ElectricityEffect
	waitforvisualfinish
	end

Move_STEEL_WING:
	loadspritegfx ANIM_TAG_GUST
	loadspritegfx ANIM_TAG_IMPACT
	loopsewithpan SE_M_HARDEN, SOUND_PAN_ATTACKER, 28, 2
	createvisualtask AnimTask_MetallicShine, 5, 0, 0, 0
	waitforvisualfinish
	monbg ANIM_DEF_PARTNER
	splitbgprio ANIM_TARGET
	setalpha 12, 8
	loopsewithpan SE_M_WING_ATTACK, SOUND_PAN_ATTACKER, 20, 2
	createvisualtask AnimTask_TranslateMonElliptical, 2, 0, 12, 4, 1, 4
	createvisualtask AnimTask_AnimateGustTornadoPalette, 5, 1, 70
	createsprite gGustToTargetSpriteTemplate, ANIM_ATTACKER, 2, -25, 0, 0, 0, 20
	createsprite gGustToTargetSpriteTemplate, ANIM_ATTACKER, 2, 25, 0, 0, 0, 20
	delay 24
	createsprite gSlideMonToOffsetSpriteTemplate, ANIM_ATTACKER, 2, 0, 24, 0, 0, 9
	delay 17
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 2, 16, 0, ANIM_TARGET, 1
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 2, -16, 0, ANIM_TARGET, 1
	playsewithpan SE_M_RAZOR_WIND, SOUND_PAN_TARGET
	waitforvisualfinish
	createsprite gSlideMonToOriginalPosSpriteTemplate, ANIM_ATTACKER, 2, 0, 0, 11
	waitforvisualfinish
	clearmonbg ANIM_DEF_PARTNER
	blendoff
	end

Move_IRON_TAIL:
	loadspritegfx ANIM_TAG_IMPACT
	loopsewithpan SE_M_HARDEN, SOUND_PAN_ATTACKER, 28, 2
	createvisualtask AnimTask_MetallicShine, 5, 1, 0, 0
	waitforvisualfinish
	monbg ANIM_TARGET
	setalpha 12, 8
	createsprite gHorizontalLungeSpriteTemplate, ANIM_ATTACKER, 2, 4, 4
	delay 6
	createsprite gBasicHitSplatSpriteTemplate, ANIM_TARGET, 2, 0, 0, ANIM_TARGET, 2
	createvisualtask AnimTask_ShakeMon, 2, ANIM_TARGET, 3, 0, 6, 1
	playsewithpan SE_M_VITAL_THROW2, SOUND_PAN_TARGET
	waitforvisualfinish
	createvisualtask AnimTask_SetGrayscaleOrOriginalPal, 5, ANIM_ATTACKER, 1
	clearmonbg ANIM_TARGET
	blendoff
	waitforvisualfinish
	end

Move_POISON_TAIL:
	loadspritegfx ANIM_TAG_IMPACT
	loadspritegfx ANIM_TAG_POISON_BUBBLE
	loopsewithpan SE_M_HARDEN, SOUND_PAN_ATTACKER, 28, 2
	createvisualtask AnimTask_MetallicShine, 5, 1, 1, RGB(24, 6, 23)
	waitforvisualfinish
	monbg ANIM_TARGET
	setalpha 12, 8
	createsprite gHorizontalLungeSpriteTemplate, ANIM_ATTACKER, 2, 4, 4
	delay 6
	createsprite gBasicHitSplatSpriteTemplate, ANIM_TARGET, 2, 0, 0, ANIM_TARGET, 2
	createvisualtask AnimTask_ShakeMon, 2, ANIM_TARGET, 3, 0, 6, 1
	playsewithpan SE_M_VITAL_THROW2, SOUND_PAN_TARGET
	waitforvisualfinish
	createvisualtask AnimTask_SetGrayscaleOrOriginalPal, 5, ANIM_ATTACKER, 1
	clearmonbg ANIM_TARGET
	blendoff
	call PoisonBubblesEffect
	waitforvisualfinish
	end

Move_METAL_CLAW:
	loadspritegfx ANIM_TAG_CLAW_SLASH
	loopsewithpan SE_M_HARDEN, SOUND_PAN_ATTACKER, 28, 2
	createvisualtask AnimTask_MetallicShine, 5, 0, 0, 0
	waitforvisualfinish
	createsprite gHorizontalLungeSpriteTemplate, ANIM_ATTACKER, 2, 6, 4
	delay 2
	playsewithpan SE_M_RAZOR_WIND, SOUND_PAN_TARGET
	createsprite gClawSlashSpriteTemplate, ANIM_TARGET, 2, -10, -10, 0
	createsprite gClawSlashSpriteTemplate, ANIM_TARGET, 2, -10, 10, 0
	createsprite gShakeMonOrTerrainSpriteTemplate, ANIM_ATTACKER, 2, -4, 1, 10, 3, 1
	delay 8
	createsprite gHorizontalLungeSpriteTemplate, ANIM_ATTACKER, 2, 6, 4
	delay 2
	playsewithpan SE_M_RAZOR_WIND, SOUND_PAN_TARGET
	createsprite gClawSlashSpriteTemplate, ANIM_TARGET, 2, 10, -10, 1
	createsprite gClawSlashSpriteTemplate, ANIM_TARGET, 2, 10, 10, 1
	createsprite gShakeMonOrTerrainSpriteTemplate, ANIM_ATTACKER, 2, -4, 1, 10, 3, 1
	waitforvisualfinish
	end

Move_NIGHT_SHADE:
	monbg ANIM_ATTACKER
	splitbgprio ANIM_ATTACKER
	playsewithpan SE_M_PSYBEAM, SOUND_PAN_ATTACKER
	fadetobg BG_GHOST
	waitbgfadein
	delay 10
	playsewithpan SE_M_LEER, SOUND_PAN_ATTACKER
	createvisualtask AnimTask_NightShadeClone, 5, 85
	delay 70
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_TARGET, 2, 0, 12, 1
	createvisualtask AnimTask_BlendColorCycle, 2, F_PAL_TARGET, 0, 2, 0, 13, RGB_BLACK
	waitforvisualfinish
	clearmonbg ANIM_ATTACKER
	delay 1
	restorebg
	waitbgfadein
	end

Move_EGG_BOMB:
	loadspritegfx ANIM_TAG_EXPLOSION
	loadspritegfx ANIM_TAG_LARGE_FRESH_EGG
	playsewithpan SE_M_TAIL_WHIP, SOUND_PAN_ATTACKER
	createsprite gEggThrowSpriteTemplate, ANIM_TARGET, 2, 10, 0, 0, 0, 25, -32
	waitforvisualfinish
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_TARGET, 4, 0, 16, 1
	createsprite gExplosionSpriteTemplate, ANIM_TARGET, 4, 6, 5, 1, 0
	playsewithpan SE_M_SELF_DESTRUCT, SOUND_PAN_TARGET
	delay 3
	createsprite gExplosionSpriteTemplate, ANIM_TARGET, 4, -16, -15, 1, 0
	playsewithpan SE_M_SELF_DESTRUCT, SOUND_PAN_TARGET
	delay 3
	createsprite gExplosionSpriteTemplate, ANIM_TARGET, 4, 16, -5, 1, 0
	playsewithpan SE_M_SELF_DESTRUCT, SOUND_PAN_TARGET
	delay 3
	createsprite gExplosionSpriteTemplate, ANIM_TARGET, 4, -12, 18, 1, 0
	playsewithpan SE_M_SELF_DESTRUCT, SOUND_PAN_TARGET
	delay 3
	createsprite gExplosionSpriteTemplate, ANIM_TARGET, 4, 0, 5, 1, 0
	playsewithpan SE_M_SELF_DESTRUCT, SOUND_PAN_TARGET
	delay 3
	waitforvisualfinish
	end

Move_SHADOW_BALL:
	loadspritegfx ANIM_TAG_SHADOW_BALL
	fadetobg BG_GHOST
	waitbgfadein
	delay 15
	createsoundtask SoundTask_LoopSEAdjustPanning, SE_M_MIST, SOUND_PAN_ATTACKER, SOUND_PAN_TARGET, 5, 5, 0, 5
	createsprite gShadowBallSpriteTemplate, ANIM_TARGET, 2, 16, 16, 8
	waitforvisualfinish
	playsewithpan SE_M_SAND_ATTACK, SOUND_PAN_TARGET
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_TARGET, 4, 0, 8, 1
	waitforvisualfinish
	restorebg
	waitbgfadein
	end

Move_LICK:
	loadspritegfx ANIM_TAG_LICK
	delay 15
	playsewithpan SE_M_LICK, SOUND_PAN_TARGET
	createsprite gLickSpriteTemplate, ANIM_TARGET, 2, 0, 0
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_TARGET, 1, 0, 16, 1
	waitforvisualfinish
	end

Move_FOCUS_ENERGY:
	loadspritegfx ANIM_TAG_FOCUS_ENERGY
	playsewithpan SE_M_DRAGON_RAGE, SOUND_PAN_ATTACKER
	call EndureEffect
	delay 8
	createvisualtask AnimTask_BlendColorCycle, 2, F_PAL_ATTACKER, 2, 2, 0, 11, RGB_WHITE
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_ATTACKER, 1, 0, 32, 1
	call EndureEffect
	delay 8
	call EndureEffect
	waitforvisualfinish
	end

Move_BIDE:
	choosetwoturnanim BideSetUp, BideUnleash
	end

BideSetUp:
	loopsewithpan SE_M_TAKE_DOWN, SOUND_PAN_ATTACKER, 9, 2
	createvisualtask AnimTask_BlendColorCycle, 2, F_PAL_ATTACKER, 2, 2, 0, 11, RGB_RED
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_ATTACKER, 1, 0, 32, 1
	waitforvisualfinish
	end

BideUnleash:
	loadspritegfx ANIM_TAG_IMPACT
	monbg ANIM_DEF_PARTNER
	setalpha 12, 8
	loopsewithpan SE_M_TAKE_DOWN, SOUND_PAN_ATTACKER, 9, 2
	createvisualtask AnimTask_BlendBattleAnimPal, 10, F_PAL_ATTACKER, 2, 0, 11, RGB_RED
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_ATTACKER, 1, 0, 32, 1
	waitforvisualfinish
	createsprite gSlideMonToOffsetSpriteTemplate, ANIM_ATTACKER, 2, 0, 24, 0, 0, 4
	waitforvisualfinish
	createvisualtask AnimTask_ShakeMonInPlace, 2, ANIM_ATTACKER, 2, 0, 12, 1
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_TARGET, 3, 0, 16, 1
	playsewithpan SE_M_COMET_PUNCH, SOUND_PAN_TARGET
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 1, 18, -8, ANIM_TARGET, 1
	delay 5
	playsewithpan SE_M_COMET_PUNCH, SOUND_PAN_TARGET
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 1, -18, 8, ANIM_TARGET, 1
	delay 5
	playsewithpan SE_M_COMET_PUNCH, SOUND_PAN_TARGET
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 1, -8, -5, ANIM_TARGET, 1
	waitforvisualfinish
	delay 5
	createsprite gSlideMonToOriginalPosSpriteTemplate, ANIM_ATTACKER, 2, 0, 0, 7
	waitforvisualfinish
	createvisualtask AnimTask_BlendBattleAnimPal, 10, F_PAL_ATTACKER, 2, 11, 0, RGB_RED
	waitforvisualfinish
	clearmonbg ANIM_DEF_PARTNER
	blendoff
	end

Move_STRING_SHOT:
	loadspritegfx ANIM_TAG_STRING
	loadspritegfx ANIM_TAG_WEB_THREAD
	monbg ANIM_DEF_PARTNER
	delay 0
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 5, F_PAL_BG, 2, 0, 9, RGB_BLACK
	waitforvisualfinish
	loopsewithpan SE_M_STRING_SHOT, SOUND_PAN_ATTACKER, 9, 6
	call StringShotThread
	call StringShotThread
	call StringShotThread
	call StringShotThread
	call StringShotThread
	call StringShotThread
	call StringShotThread
	call StringShotThread
	call StringShotThread
	call StringShotThread
	call StringShotThread
	call StringShotThread
	call StringShotThread
	call StringShotThread
	call StringShotThread
	call StringShotThread
	call StringShotThread
	call StringShotThread
	waitforvisualfinish
	playsewithpan SE_M_STRING_SHOT2, SOUND_PAN_TARGET
	createsprite gStringWrapSpriteTemplate, ANIM_TARGET, 2, 0, 10
	delay 4
	createsprite gStringWrapSpriteTemplate, ANIM_TARGET, 2, 0, -2
	delay 4
	createsprite gStringWrapSpriteTemplate, ANIM_TARGET, 2, 0, 22
	waitforvisualfinish
	clearmonbg ANIM_DEF_PARTNER
	delay 1
	waitforvisualfinish
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 5, F_PAL_BG, 2, 9, 0, RGB_BLACK
	end

StringShotThread:
	createsprite gWebThreadSpriteTemplate, ANIM_TARGET, 2, 20, 0, 512, 20, 1
	delay 1
	return

Move_SPIDER_WEB:
	loadspritegfx ANIM_TAG_SPIDER_WEB
	loadspritegfx ANIM_TAG_WEB_THREAD
	monbg ANIM_DEF_PARTNER
	delay 0
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 5, F_PAL_BG, 2, 0, 9, RGB_BLACK
	waitforvisualfinish
	splitbgprio ANIM_TARGET
	loopsewithpan SE_M_STRING_SHOT, SOUND_PAN_ATTACKER, 9, 6
	call SpiderWebThread
	call SpiderWebThread
	call SpiderWebThread
	call SpiderWebThread
	call SpiderWebThread
	call SpiderWebThread
	call SpiderWebThread
	call SpiderWebThread
	call SpiderWebThread
	call SpiderWebThread
	call SpiderWebThread
	call SpiderWebThread
	call SpiderWebThread
	call SpiderWebThread
	waitforvisualfinish
	playsewithpan SE_M_STRING_SHOT2, SOUND_PAN_TARGET
	createsprite gSpiderWebSpriteTemplate, ANIM_ATTACKER, 2
	waitforvisualfinish
	clearmonbg ANIM_DEF_PARTNER
	delay 1
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 5, F_PAL_BG, 2, 9, 0, RGB_BLACK
	end

SpiderWebThread:
	createsprite gWebThreadSpriteTemplate, ANIM_TARGET, 2, 20, 0, 512, 20, 0
	delay 1
	return

Move_RAZOR_WIND:
	choosetwoturnanim RazorWindSetUp, RazorWindUnleash

RazorWindEnd:
	waitforvisualfinish
	end

RazorWindSetUp:
	loadspritegfx ANIM_TAG_GUST
	playsewithpan SE_M_GUST, SOUND_PAN_ATTACKER
	createsprite gRazorWindTornadoSpriteTemplate, ANIM_ATTACKER, 2, 32, 0, 16, 16, 0, 7, 40
	createsprite gRazorWindTornadoSpriteTemplate, ANIM_ATTACKER, 2, 32, 0, 16, 16, 85, 7, 40
	createsprite gRazorWindTornadoSpriteTemplate, ANIM_ATTACKER, 2, 32, 0, 16, 16, 170, 7, 40
	waitforvisualfinish
	playsewithpan SE_M_GUST2, SOUND_PAN_ATTACKER
	goto RazorWindEnd

RazorWindUnleash:
	loadspritegfx ANIM_TAG_AIR_WAVE_2
	loadspritegfx ANIM_TAG_IMPACT
	monbg ANIM_TARGET
	setalpha 12, 8
	playsewithpan SE_M_RAZOR_WIND2, SOUND_PAN_ATTACKER
	createsprite gAirWaveCrescentSpriteTemplate, ANIM_ATTACKER, 2, 14, 8, 0, 0, 22, 2, 1
	delay 2
	playsewithpan SE_M_RAZOR_WIND2, SOUND_PAN_ATTACKER
	createsprite gAirWaveCrescentSpriteTemplate, ANIM_ATTACKER, 2, 14, -8, 16, 14, 22, 1, 1
	delay 2
	playsewithpan SE_M_RAZOR_WIND2, SOUND_PAN_ATTACKER
	createsprite gAirWaveCrescentSpriteTemplate, ANIM_ATTACKER, 2, 14, 12, -16, -14, 22, 0, 1
	delay 17
	playsewithpan SE_M_RAZOR_WIND, SOUND_PAN_TARGET
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_TARGET, 2, 0, 10, 1
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_DEF_PARTNER, 2, 0, 10, 1
	waitforvisualfinish
	clearmonbg ANIM_TARGET
	blendoff
	goto RazorWindEnd

Move_DISABLE:
	loadspritegfx ANIM_TAG_SPARKLE_4
	monbg ANIM_TARGET
	splitbgprio ANIM_TARGET
	setalpha 8, 8
	playsewithpan SE_M_DETECT, SOUND_PAN_ATTACKER
	createsprite gSpinningSparkleSpriteTemplate, ANIM_ATTACKER, 13, 24, -16
	waitforvisualfinish
	createvisualtask AnimTask_GrowAndGrayscale, 5
	loopsewithpan SE_M_BIND, SOUND_PAN_TARGET, 15, 4
	waitforvisualfinish
	delay 1
	clearmonbg ANIM_TARGET
	blendoff
	end

Move_RECOVER:
	loadspritegfx ANIM_TAG_ORBS
	loadspritegfx ANIM_TAG_BLUE_STAR
	monbg ANIM_ATK_PARTNER
	setalpha 12, 8
	loopsewithpan SE_M_MEGA_KICK, SOUND_PAN_ATTACKER, 13, 3
	createvisualtask AnimTask_BlendColorCycle, 2, F_PAL_ATTACKER, 0, 6, 0, 11, RGB(31, 31, 11)
	call RecoverAbsorbEffect
	call RecoverAbsorbEffect
	call RecoverAbsorbEffect
	waitforvisualfinish
	clearmonbg ANIM_ATK_PARTNER
	blendoff
	delay 1
	call HealingEffect
	waitforvisualfinish
	end

RecoverAbsorbEffect:
	createsprite gPowerAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 2, 40, -10, 13
	delay 3
	createsprite gPowerAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 2, -35, -10, 13
	delay 3
	createsprite gPowerAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 2, 15, -40, 13
	delay 3
	createsprite gPowerAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 2, -10, -32, 13
	delay 3
	createsprite gPowerAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 2, 25, -20, 13
	delay 3
	createsprite gPowerAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 2, -40, -20, 13
	delay 3
	createsprite gPowerAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 2, 5, -40, 13
	delay 3
	return

Move_MIMIC:
	loadspritegfx ANIM_TAG_ORBS
	monbg_static ANIM_DEF_PARTNER
	setalpha 11, 5
	panse SE_M_MINIMIZE, SOUND_PAN_TARGET, SOUND_PAN_ATTACKER, -3, 0
	createvisualtask AnimTask_ShrinkTargetCopy, 5, 128, 24
	delay 15
	createsprite gMimicOrbSpriteTemplate, ANIM_TARGET, 2, -12, 24
	delay 10
	setarg 7, 0xFFFF
	waitforvisualfinish
	playsewithpan SE_M_TAKE_DOWN, SOUND_PAN_ATTACKER
	createvisualtask AnimTask_BlendColorCycle, 2, F_PAL_ATTACKER, 0, 2, 0, 11, RGB_WHITE
	waitforvisualfinish
	clearmonbg_static ANIM_DEF_PARTNER
	blendoff
	end

Move_CONSTRICT:
	loadspritegfx ANIM_TAG_TENDRILS
	loopsewithpan SE_M_SCRATCH, SOUND_PAN_TARGET, 6, 4
	createsprite gConstrictBindingSpriteTemplate, ANIM_TARGET, 4, 0, 16, 0, 2
	delay 7
	createsprite gConstrictBindingSpriteTemplate, ANIM_TARGET, 3, 0, 0, 0, 2
	createsprite gConstrictBindingSpriteTemplate, ANIM_TARGET, 2, 0, 8, 1, 2
	delay 7
	createsprite gConstrictBindingSpriteTemplate, ANIM_TARGET, 3, 0, -8, 1, 2
	delay 8
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_TARGET, 3, 0, 6, 1
	delay 20
	playsewithpan SE_M_BIND, SOUND_PAN_TARGET
	setarg 7, 0xFFFF
	waitforvisualfinish
	end

Move_CURSE:
	choosetwoturnanim CurseGhost, CurseStats

CurseGhost:
	loadspritegfx ANIM_TAG_NAIL
	loadspritegfx ANIM_TAG_GHOSTLY_SPIRIT
	monbg ANIM_ATK_PARTNER
	createvisualtask AnimTask_CurseStretchingBlackBg, 5
	waitforvisualfinish
	delay 20
	createsprite gCurseNailSpriteTemplate, ANIM_ATTACKER, 2
	delay 60
	call CurseGhostShakeFromNail
	delay 41
	call CurseGhostShakeFromNail
	delay 41
	call CurseGhostShakeFromNail
	waitforvisualfinish
	clearmonbg ANIM_ATK_PARTNER
	delay 1
	monbg ANIM_DEF_PARTNER
	playsewithpan SE_M_NIGHTMARE, SOUND_PAN_TARGET
	createsprite gCurseGhostSpriteTemplate, ANIM_TARGET, 2
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_TARGET, 2, 0, 14, 1
	waitforvisualfinish
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG, 1, 16, 0, RGB_BLACK
	waitforvisualfinish
	clearmonbg ANIM_DEF_PARTNER
	end

CurseGhostShakeFromNail:
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_ATTACKER, 4, 0, 10, 0
	playsewithpan SE_M_BIND, SOUND_PAN_ATTACKER
	return

CurseStats:
	createvisualtask AnimTask_SwayMon, 5, 0, 10, 1536, 3, ANIM_ATTACKER
	waitforvisualfinish
	delay 10
	call CurseStats1
	waitforvisualfinish
	end

CurseStats1:
	playsewithpan SE_M_DRAGON_RAGE, SOUND_PAN_ATTACKER
	createvisualtask AnimTask_DrawFallingWhiteLinesOnAttacker, 5
	createvisualtask AnimTask_BlendColorCycle, 5, F_PAL_ATTACKER, 4, 2, 0, 10, RGB_RED
	return

Move_SOFT_BOILED:
	loadspritegfx ANIM_TAG_BREAKING_EGG
	loadspritegfx ANIM_TAG_THIN_RING
	loadspritegfx ANIM_TAG_BLUE_STAR
	monbg ANIM_ATK_PARTNER
	playsewithpan SE_M_TAIL_WHIP, SOUND_PAN_ATTACKER
	createvisualtask AnimTask_ShakeMon, 2, ANIM_ATTACKER, 0, 2, 6, 1
	createsprite gSoftBoiledEggSpriteTemplate, ANIM_ATTACKER, 4, 0, 16, 0
	createsprite gSoftBoiledEggSpriteTemplate, ANIM_ATTACKER, 4, 0, 16, 1
	delay 120
	delay 7
	playsewithpan SE_M_HORN_ATTACK, SOUND_PAN_ATTACKER
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG | F_PAL_BATTLERS, 3, 10, 0, RGB(12, 24, 30)
	createsprite gThinRingExpandingSpriteTemplate, ANIM_ATTACKER, 3, 31, 16, 0, 1
	delay 8
	createsprite gThinRingExpandingSpriteTemplate, ANIM_ATTACKER, 3, 31, 16, 0, 1
	delay 60
	setarg 7, 0xFFFF
	waitforvisualfinish
	clearmonbg ANIM_ATK_PARTNER
	call HealingEffect2
	end

Move_HEAL_BELL:
	loadspritegfx ANIM_TAG_BELL
	loadspritegfx ANIM_TAG_MUSIC_NOTES_2
	loadspritegfx ANIM_TAG_THIN_RING
	createvisualtask AnimTask_BlendBattleAnimPal, 10, F_PAL_ATK_SIDE, 0, 0, 10, RGB_WHITE
	waitforvisualfinish
	createvisualtask AnimTask_LoadMusicNotesPals, 5
	createsprite gBellSpriteTemplate, ANIM_ATTACKER, 2, 0, -24, 0, 1
	delay 12
	createsprite gHealBellMusicNoteSpriteTemplate, ANIM_ATTACKER, 40, 0, -24, 48, -18, 35, 0, 0
	createsprite gHealBellMusicNoteSpriteTemplate, ANIM_ATTACKER, 40, 0, -24, -48, 20, 30, 1, 1
	createsprite gHealBellMusicNoteSpriteTemplate, ANIM_ATTACKER, 40, 0, -24, -38, -29, 30, 2, 2
	createsprite gHealBellMusicNoteSpriteTemplate, ANIM_ATTACKER, 40, 0, -24, 36, 18, 30, 3, 3
	call HealBellRing
	delay 33
	createsprite gHealBellMusicNoteSpriteTemplate, ANIM_ATTACKER, 40, 0, -24, 19, 26, 35, 4, 4
	createsprite gHealBellMusicNoteSpriteTemplate, ANIM_ATTACKER, 40, 0, -24, -34, -12, 30, 5, 5
	createsprite gHealBellMusicNoteSpriteTemplate, ANIM_ATTACKER, 40, 0, -24, 41, -20, 34, 6, 2
	createsprite gHealBellMusicNoteSpriteTemplate, ANIM_ATTACKER, 40, 0, -24, -15, 26, 32, 7, 0
	call HealBellRing
	delay 33
	createsprite gHealBellMusicNoteSpriteTemplate, ANIM_ATTACKER, 40, 0, -24, -48, 18, 31, 0, 2
	createsprite gHealBellMusicNoteSpriteTemplate, ANIM_ATTACKER, 40, 0, -24, 48, -20, 30, 2, 5
	createsprite gHealBellMusicNoteSpriteTemplate, ANIM_ATTACKER, 40, 0, -24, 38, 29, 33, 4, 3
	createsprite gHealBellMusicNoteSpriteTemplate, ANIM_ATTACKER, 40, 0, -24, -36, -18, 30, 6, 1
	call HealBellRing
	waitforvisualfinish
	createvisualtask AnimTask_FreeMusicNotesPals, 5
	waitforvisualfinish
	unloadspritegfx ANIM_TAG_BELL
	unloadspritegfx ANIM_TAG_MUSIC_NOTES_2
	unloadspritegfx ANIM_TAG_THIN_RING
	loadspritegfx ANIM_TAG_SPARKLE_2
	playsewithpan SE_M_MORNING_SUN, SOUND_PAN_ATTACKER
	createsprite gSparklingStarsSpriteTemplate, ANIM_ATTACKER, 16, -15, 0, 0, 0, 32, 60, 1
	delay 8
	createsprite gSparklingStarsSpriteTemplate, ANIM_ATTACKER, 16, 12, -5, 0, 0, 32, 60, 1
	waitforvisualfinish
	unloadspritegfx ANIM_TAG_SPARKLE_2
	loadspritegfx ANIM_TAG_THIN_RING
	playsewithpan SE_SHINY, SOUND_PAN_ATTACKER
	createvisualtask AnimTask_BlendBattleAnimPalExclude, 10, 4, 3, 10, 0, RGB(12, 24, 30)
	createvisualtask AnimTask_BlendBattleAnimPal, 10, F_PAL_ATK_SIDE, 3, 10, 0, RGB_WHITE
	createsprite gBlendThinRingExpandingSpriteTemplate, ANIM_ATTACKER, 16, 0, 0, 0, 1
	end

HealBellRing:
	createvisualtask AnimTask_BlendBattleAnimPalExclude, 10, 4, 3, 8, 0, RGB(12, 24, 30)
	createvisualtask AnimTask_BlendBattleAnimPal, 10, F_PAL_ATK_SIDE, 3, 2, 10, RGB_WHITE
	createsprite gThinRingExpandingSpriteTemplate, ANIM_ATTACKER, 40, 0, -24, 0, 1
	playsewithpan SE_M_HEAL_BELL, SOUND_PAN_ATTACKER
	return

Move_FAKE_OUT:
	playsewithpan SE_M_FLATTER, 0
	createvisualtask AnimTask_FakeOut, 5
	waitforvisualfinish
	playsewithpan SE_M_SKETCH, SOUND_PAN_TARGET
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_TARGET, 4, 0, 5, 1
	createvisualtask AnimTask_StretchTargetUp, 3
	waitforvisualfinish
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG, 3, 16, 0, RGB_WHITE
	end

Move_SCARY_FACE:
	loadspritegfx ANIM_TAG_EYE_SPARKLE
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG | F_PAL_ATK_SIDE | F_PAL_DEF_PARTNER, 3, 0, 16, RGB_BLACK
	playsewithpan SE_M_PSYBEAM, SOUND_PAN_ATTACKER
	waitforvisualfinish
	delay 10
	playsewithpan SE_M_LEER, SOUND_PAN_ATTACKER
	createvisualtask AnimTask_ScaryFace, 5
	delay 13
	createsprite gEyeSparkleSpriteTemplate, ANIM_ATTACKER, 0, -16, -8
	createsprite gEyeSparkleSpriteTemplate, ANIM_ATTACKER, 0, 16, -8
	waitforvisualfinish
	createvisualtask AnimTask_ShakeTargetInPattern, 3, 20, 1, FALSE
	playsewithpan SE_M_STRING_SHOT2, SOUND_PAN_TARGET
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG | F_PAL_ATK_SIDE | F_PAL_DEF_PARTNER, 3, 16, 0, RGB_BLACK
	waitforvisualfinish
	end

Move_SWEET_KISS:
	loadspritegfx ANIM_TAG_RED_HEART
	loadspritegfx ANIM_TAG_ANGEL
	createsprite gAngelSpriteTemplate, ANIM_TARGET, 2, 16, -48
	playsewithpan SE_M_HEAL_BELL, SOUND_PAN_TARGET
	delay 23
	playsewithpan SE_M_HEAL_BELL, SOUND_PAN_TARGET
	delay 23
	playsewithpan SE_M_HEAL_BELL, SOUND_PAN_TARGET
	waitforvisualfinish
	createsprite gRedHeartBurstSpriteTemplate, ANIM_TARGET, 3, 160, -30
	playsewithpan SE_M_ATTRACT, SOUND_PAN_TARGET
	createsprite gRedHeartBurstSpriteTemplate, ANIM_TARGET, 3, -256, -42
	createsprite gRedHeartBurstSpriteTemplate, ANIM_TARGET, 3, 128, -14
	createsprite gRedHeartBurstSpriteTemplate, ANIM_TARGET, 3, 416, -38
	createsprite gRedHeartBurstSpriteTemplate, ANIM_TARGET, 3, -128, -22
	createsprite gRedHeartBurstSpriteTemplate, ANIM_TARGET, 3, -384, -31
	end

Move_LOVELY_KISS:
	loadspritegfx ANIM_TAG_PINK_HEART
	loadspritegfx ANIM_TAG_DEVIL
	createsprite gDevilSpriteTemplate, ANIM_TARGET, 2, 0, -24
	playsewithpan SE_M_PSYBEAM2, SOUND_PAN_TARGET
	waitforvisualfinish
	playsewithpan SE_M_ATTRACT, SOUND_PAN_TARGET
	createsprite gPinkHeartSpriteTemplate, ANIM_TARGET, 3, -256, -42
	createsprite gPinkHeartSpriteTemplate, ANIM_TARGET, 3, 128, -14
	createsprite gPinkHeartSpriteTemplate, ANIM_TARGET, 3, 416, -38
	createsprite gPinkHeartSpriteTemplate, ANIM_TARGET, 3, -128, -22
	end

Move_FURY_SWIPES:
	loadspritegfx ANIM_TAG_SWIPE
	createsprite gHorizontalLungeSpriteTemplate, ANIM_ATTACKER, 2, 5, 5
	delay 4
	playsewithpan SE_M_SCRATCH, SOUND_PAN_TARGET
	createsprite gFurySwipesSpriteTemplate, ANIM_TARGET, 2, 16, 0, 1
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_TARGET, 3, 0, 5, 1
	delay 10
	createsprite gHorizontalLungeSpriteTemplate, ANIM_TARGET, 2, 5, 5
	delay 4
	playsewithpan SE_M_SCRATCH, SOUND_PAN_TARGET
	createsprite gFurySwipesSpriteTemplate, ANIM_TARGET, 2, -16, 0, 0
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_TARGET, 4, 0, 7, 1
	end

Move_INGRAIN:
	loadspritegfx ANIM_TAG_ROOTS
	loadspritegfx ANIM_TAG_ORBS
	createsprite gIngrainRootSpriteTemplate, ANIM_ATTACKER, 2, 16, 26, -1, 2, 150
	playsewithpan SE_M_SCRATCH, SOUND_PAN_ATTACKER
	delay 10
	createsprite gIngrainRootSpriteTemplate, ANIM_ATTACKER, 2, -32, 20, 1, 1, 140
	playsewithpan SE_M_SCRATCH, SOUND_PAN_ATTACKER
	delay 10
	createsprite gIngrainRootSpriteTemplate, ANIM_ATTACKER, 2, 32, 22, 1, 0, 130
	playsewithpan SE_M_SCRATCH, SOUND_PAN_ATTACKER
	delay 10
	createsprite gIngrainRootSpriteTemplate, ANIM_ATTACKER, 2, -16, 25, -1, 3, 120
	playsewithpan SE_M_SCRATCH, SOUND_PAN_ATTACKER
	delay 40
	createsprite gIngrainOrbSpriteTemplate, ANIM_ATTACKER, 3, 32, 26, -1, 3, 30
	delay 5
	playsewithpan SE_M_BUBBLE3, SOUND_PAN_ATTACKER
	delay 5
	createsprite gIngrainOrbSpriteTemplate, ANIM_ATTACKER, 3, -48, 20, 1, 2, 30
	playsewithpan SE_M_BUBBLE3, SOUND_PAN_ATTACKER
	delay 5
	playsewithpan SE_M_BUBBLE3, SOUND_PAN_ATTACKER
	delay 5
	createsprite gIngrainOrbSpriteTemplate, ANIM_ATTACKER, 3, 48, 26, -2, 3, 18
	playsewithpan SE_M_BUBBLE3, SOUND_PAN_ATTACKER
	delay 10
	waitforvisualfinish
	end

Move_PRESENT:
	loadspritegfx ANIM_TAG_ITEM_BAG
	createvisualtask AnimTask_IsHealingMove, 2
	createsprite gPresentSpriteTemplate, ANIM_TARGET, 2, 0, -5, 10, 2, -1
	playsewithpan SE_M_TAIL_WHIP, SOUND_PAN_ATTACKER
	delay 14
	playsewithpan SE_M_BUBBLE2, SOUND_PAN_ATTACKER
	delay 14
	playsewithpan SE_M_BUBBLE2, 0
	delay 20
	playsewithpan SE_M_BUBBLE2, SOUND_PAN_TARGET
	waitforvisualfinish
	jumpretfalse PresentDamage
	jumprettrue PresentHeal
	end

PresentDamage:
	loadspritegfx ANIM_TAG_EXPLOSION
	playsewithpan SE_M_SELF_DESTRUCT, SOUND_PAN_TARGET
	createsprite gExplosionSpriteTemplate, ANIM_TARGET, 3, 0, 0, 1, 1
	delay 6
	playsewithpan SE_M_SELF_DESTRUCT, SOUND_PAN_TARGET
	createsprite gExplosionSpriteTemplate, ANIM_TARGET, 3, 24, -24, 1, 1
	delay 6
	playsewithpan SE_M_SELF_DESTRUCT, SOUND_PAN_TARGET
	createsprite gExplosionSpriteTemplate, ANIM_TARGET, 3, -16, 16, 1, 1
	delay 6
	playsewithpan SE_M_SELF_DESTRUCT, SOUND_PAN_TARGET
	createsprite gExplosionSpriteTemplate, ANIM_TARGET, 3, -24, -12, 1, 1
	delay 6
	playsewithpan SE_M_SELF_DESTRUCT, SOUND_PAN_TARGET
	createsprite gExplosionSpriteTemplate, ANIM_TARGET, 3, 16, 16, 1, 1
	end

PresentHeal:
	loadspritegfx ANIM_TAG_GREEN_SPARKLE
	loadspritegfx ANIM_TAG_BLUE_STAR
	playsewithpan SE_M_MORNING_SUN, SOUND_PAN_TARGET
	createsprite gPresentHealParticleSpriteTemplate, ANIM_TARGET, 4, -16, 32, -3, 1
	delay 3
	createsprite gPresentHealParticleSpriteTemplate, ANIM_TARGET, 4, 16, 32, -3, -1
	delay 3
	createsprite gPresentHealParticleSpriteTemplate, ANIM_TARGET, 4, 32, 32, -3, 1
	delay 3
	createsprite gPresentHealParticleSpriteTemplate, ANIM_TARGET, 4, -32, 32, -3, 1
	delay 3
	createsprite gPresentHealParticleSpriteTemplate, ANIM_TARGET, 4, 0, 32, -3, 1
	delay 3
	createsprite gPresentHealParticleSpriteTemplate, ANIM_TARGET, 4, -8, 32, -3, 1
	delay 3
	createsprite gPresentHealParticleSpriteTemplate, ANIM_TARGET, 4, -8, 32, -3, 1
	delay 3
	createsprite gPresentHealParticleSpriteTemplate, ANIM_TARGET, 4, 24, 32, -3, 1
	delay 3
	createsprite gPresentHealParticleSpriteTemplate, ANIM_TARGET, 4, -24, 32, -3, 1
	waitforvisualfinish
	waitsound
	call HealingEffect2
	end

Move_BATON_PASS:
	loadspritegfx ANIM_TAG_POKEBALL
	playsewithpan SE_M_BATON_PASS, SOUND_PAN_ATTACKER
	createvisualtask AnimTask_BlendColorCycle, 2, F_PAL_BG | F_PAL_BATTLERS, 1, 2, 0, 11, RGB(31, 22, 30)
	createsprite gBatonPassPokeballSpriteTemplate, ANIM_ATTACKER, 2
	end

Move_PERISH_SONG:
	loadspritegfx ANIM_TAG_MUSIC_NOTES_2
	createsprite gPerishSongMusicNoteSpriteTemplate, ANIM_ATTACKER, 4, 0, 0, 0
	createsprite gPerishSongMusicNoteSpriteTemplate, ANIM_ATTACKER, 4, 1, 1, 16
	createsprite gPerishSongMusicNoteSpriteTemplate, ANIM_ATTACKER, 4, 2, 1, 32
	createsprite gPerishSongMusicNoteSpriteTemplate, ANIM_ATTACKER, 4, 3, 2, 48
	createsprite gPerishSongMusicNoteSpriteTemplate, ANIM_ATTACKER, 4, 4, 2, 64
	createsprite gPerishSongMusicNoteSpriteTemplate, ANIM_ATTACKER, 4, 5, 0, 80
	createsprite gPerishSongMusicNoteSpriteTemplate, ANIM_ATTACKER, 4, 6, 0, 96
	createsprite gPerishSongMusicNoteSpriteTemplate, ANIM_ATTACKER, 4, 7, 1, 112
	createsprite gPerishSongMusicNoteSpriteTemplate, ANIM_ATTACKER, 4, 8, 2, 128
	createsprite gPerishSongMusicNoteSpriteTemplate, ANIM_ATTACKER, 4, 9, 0, 144
	createsprite gPerishSongMusicNoteSpriteTemplate, ANIM_ATTACKER, 4, 10, 2, 160
	createsprite gPerishSongMusicNoteSpriteTemplate, ANIM_ATTACKER, 4, 11, 0, 176
	createsprite gPerishSongMusicNoteSpriteTemplate, ANIM_ATTACKER, 4, 12, 1, 192
	createsprite gPerishSongMusicNoteSpriteTemplate, ANIM_ATTACKER, 4, 13, 3, 208
	createsprite gPerishSongMusicNoteSpriteTemplate, ANIM_ATTACKER, 4, 14, 3, 224
	createsprite gPerishSongMusicNoteSpriteTemplate, ANIM_ATTACKER, 4, 15, 0, 240
	createsprite gPerishSongMusicNote2SpriteTemplate, ANIM_ATTACKER, 4, 15, 0, 0
	delay 20
	panse SE_M_PERISH_SONG, SOUND_PAN_ATTACKER, SOUND_PAN_TARGET, +2, 0
	delay 80
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG, 3, 0, 16, RGB_BLACK
	createvisualtask AnimTask_SetGrayscaleOrOriginalPal, 5, 4, 0
	createvisualtask AnimTask_SetGrayscaleOrOriginalPal, 5, 5, 0
	createvisualtask AnimTask_SetGrayscaleOrOriginalPal, 5, 6, 0
	createvisualtask AnimTask_SetGrayscaleOrOriginalPal, 5, 7, 0
	delay 100
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG, 3, 16, 0, RGB_BLACK
	createvisualtask AnimTask_SetGrayscaleOrOriginalPal, 5, 4, 1
	createvisualtask AnimTask_SetGrayscaleOrOriginalPal, 5, 5, 1
	createvisualtask AnimTask_SetGrayscaleOrOriginalPal, 5, 6, 1
	createvisualtask AnimTask_SetGrayscaleOrOriginalPal, 5, 7, 1
	waitforvisualfinish
	end

Move_SLEEP_TALK:
	loadspritegfx ANIM_TAG_LETTER_Z
	createvisualtask AnimTask_SwayMon, 5, 0, 4, 4096, 2, ANIM_ATTACKER
	delay 20
	createsprite gLetterZSpriteTemplate, ANIM_TARGET, 2, 0, 20, 5, -1
	playsewithpan SE_M_SNORE, SOUND_PAN_ATTACKER
	delay 6
	createsprite gLetterZSpriteTemplate, ANIM_TARGET, 2, 0, 20, 5, -1
	delay 6
	createsprite gLetterZSpriteTemplate, ANIM_TARGET, 2, 0, 20, 5, -1
	delay 20
	createsprite gLetterZSpriteTemplate, ANIM_TARGET, 2, 0, 20, 5, -5
	playsewithpan SE_M_SNORE, SOUND_PAN_ATTACKER
	delay 6
	createsprite gLetterZSpriteTemplate, ANIM_TARGET, 2, 0, 20, 5, -5
	delay 6
	createsprite gLetterZSpriteTemplate, ANIM_TARGET, 2, 0, 20, 5, -5
	delay 20
	createsprite gLetterZSpriteTemplate, ANIM_TARGET, 2, 0, 20, 5, -3
	playsewithpan SE_M_SNORE, SOUND_PAN_ATTACKER
	delay 6
	createsprite gLetterZSpriteTemplate, ANIM_TARGET, 2, 0, 20, 5, -3
	delay 6
	createsprite gLetterZSpriteTemplate, ANIM_TARGET, 2, 0, 20, 5, -3
	waitforvisualfinish
	end

Move_HYPER_FANG:
	loadspritegfx ANIM_TAG_FANG_ATTACK
	playsewithpan SE_M_BITE, SOUND_PAN_TARGET
	delay 1
	delay 2
	createvisualtask AnimTask_IsContest, 2
	jumprettrue HyperFangInContest
	createvisualtask AnimTask_IsTargetPlayerSide, 2
	jumpretfalse HyperFangOnOpponent
	goto HyperFangOnPlayer

HyperFangContinue:
	waitbgfadeout
	createsprite gFangSpriteTemplate, ANIM_TARGET, 2
	waitbgfadein
	createvisualtask AnimTask_ShakeMon, 3, ANIM_TARGET, 0, 10, 10, 1
	playsewithpan SE_M_LEER, SOUND_PAN_TARGET
	delay 20
	restorebg
	waitbgfadein
	waitforvisualfinish
	end

HyperFangOnOpponent:
	fadetobg BG_IMPACT_OPPONENT
	goto HyperFangContinue

HyperFangOnPlayer:
	fadetobg BG_IMPACT_PLAYER
	goto HyperFangContinue

HyperFangInContest:
	fadetobg BG_IMPACT_CONTESTS
	goto HyperFangContinue

Move_TRI_ATTACK:
	loadspritegfx ANIM_TAG_TRI_ATTACK_TRIANGLE
	createsprite gTriAttackTriangleSpriteTemplate, ANIM_TARGET, 2, 16, 0
	playsewithpan SE_M_TRI_ATTACK, SOUND_PAN_ATTACKER
	delay 20
	playsewithpan SE_M_TRI_ATTACK, SOUND_PAN_ATTACKER
	delay 20
	createsoundtask SoundTask_LoopSEAdjustPanning, SE_M_TRI_ATTACK, SOUND_PAN_ATTACKER, SOUND_PAN_TARGET, 5, 6, 0, 7
	waitforvisualfinish
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG, 2, 0, 16, RGB_BLACK
	delay 16
	loadspritegfx ANIM_TAG_FIRE
	createsprite gLargeFlameScatterSpriteTemplate, ANIM_TARGET, 2, 0, 0, 30, 30, -1, 0
	playsewithpan SE_M_FLAME_WHEEL2, SOUND_PAN_TARGET
	createsprite gLargeFlameScatterSpriteTemplate, ANIM_TARGET, 2, 0, 0, 30, 30, 0, 1
	delay 1
	createsprite gLargeFlameScatterSpriteTemplate, ANIM_TARGET, 2, 0, 0, 30, 30, -1, -1
	delay 1
	createsprite gLargeFlameScatterSpriteTemplate, ANIM_TARGET, 2, 0, 0, 30, 30, 2, 1
	delay 1
	createsprite gLargeFlameScatterSpriteTemplate, ANIM_TARGET, 2, 0, 0, 30, 30, 1, -1
	delay 1
	createsprite gLargeFlameScatterSpriteTemplate, ANIM_TARGET, 2, 0, 0, 30, 30, -1, 1
	delay 1
	createsprite gLargeFlameScatterSpriteTemplate, ANIM_TARGET, 2, 0, 0, 30, 30, 1, -2
	delay 1
	createsprite gLargeFlameScatterSpriteTemplate, ANIM_TARGET, 2, 0, 0, 30, 30, 3, 1
	delay 2
	createvisualtask AnimTask_ShakeTargetInPattern, 2, 20, 3, TRUE, 1
	waitforvisualfinish
	loadspritegfx ANIM_TAG_LIGHTNING
	createvisualtask AnimTask_InvertScreenColor, 2, 257, 257, 257
	playsewithpan SE_M_TRI_ATTACK2, SOUND_PAN_TARGET
	createsprite gLightningSpriteTemplate, ANIM_TARGET, 2, 0, -48
	delay 1
	createsprite gLightningSpriteTemplate, ANIM_TARGET, 2, 0, -16
	delay 1
	createsprite gLightningSpriteTemplate, ANIM_TARGET, 2, 0, 16
	delay 20
	createvisualtask AnimTask_ShakeTargetInPattern, 2, 20, 3, TRUE, 0
	delay 2
	createvisualtask AnimTask_InvertScreenColor, 2, 257, 257, 257
	waitforvisualfinish
	loadspritegfx ANIM_TAG_ICE_CRYSTALS
	call IceCrystalEffectShort
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG, 2, 16, 0, RGB_BLACK
	waitforvisualfinish
	end

Move_WILL_O_WISP:
	loadspritegfx ANIM_TAG_WISP_FIRE
	loadspritegfx ANIM_TAG_WISP_ORB
	monbg ANIM_DEF_PARTNER
	splitbgprio_foes ANIM_TARGET
	playsewithpan SE_M_EMBER, SOUND_PAN_ATTACKER
	waitplaysewithpan SE_M_EMBER, SOUND_PAN_ATTACKER, 10
	createvisualtask SoundTask_AdjustPanningVar, 2, SOUND_PAN_ATTACKER, SOUND_PAN_ATTACKER, 1, 0
	createsprite gWillOWispOrbSpriteTemplate, ANIM_ATTACKER, 2, 0, 0, 0
	delay 3
	createsprite gWillOWispOrbSpriteTemplate, ANIM_ATTACKER, 3, 0, 0, 1
	delay 3
	createsprite gWillOWispOrbSpriteTemplate, ANIM_ATTACKER, 4, 0, 0, 2
	delay 3
	createsprite gWillOWispOrbSpriteTemplate, ANIM_ATTACKER, 4, 0, 0, 3
	delay 40
	createvisualtask SoundTask_AdjustPanningVar, 2, SOUND_PAN_ATTACKER, SOUND_PAN_TARGET, 2, 0
	waitforvisualfinish
	splitbgprio_all
	playsewithpan SE_M_FLAME_WHEEL2, SOUND_PAN_TARGET
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_TARGET, 4, 0, 13, 1
	createsprite gWillOWispFireSpriteTemplate, ANIM_ATTACKER, 2, 0
	createsprite gWillOWispFireSpriteTemplate, ANIM_ATTACKER, 2, 42
	createsprite gWillOWispFireSpriteTemplate, ANIM_ATTACKER, 2, 84
	createsprite gWillOWispFireSpriteTemplate, ANIM_ATTACKER, 2, 126
	createsprite gWillOWispFireSpriteTemplate, ANIM_ATTACKER, 2, 168
	createsprite gWillOWispFireSpriteTemplate, ANIM_ATTACKER, 2, 210
	waitforvisualfinish
	clearmonbg ANIM_DEF_PARTNER
	end

Move_ENCORE:
	loadspritegfx ANIM_TAG_SPOTLIGHT
	loadspritegfx ANIM_TAG_TAG_HAND
	createvisualtask AnimTask_CreateSpotlight, 2
	createvisualtask AnimTask_HardwarePaletteFade, 2, 248, 3, 0, 10, 0
	waitforvisualfinish
	createsprite gSpotlightSpriteTemplate, ANIM_TARGET, 2, 0, -8
	createsprite gClappingHandSpriteTemplate, ANIM_ATTACKER, 2, -2, 0, 0, 0, 9
	createsprite gClappingHandSpriteTemplate, ANIM_ATTACKER, 2, 2, 0, 1, 0, 9
	createsprite gClappingHand2SpriteTemplate, ANIM_ATTACKER, 3, -2, 0, 0, 0, 9
	createsprite gClappingHand2SpriteTemplate, ANIM_ATTACKER, 3, 2, 0, 1, 0, 9
	delay 16
	createvisualtask SoundTask_PlaySE2WithPanning, 5, SE_M_ENCORE2, SOUND_PAN_TARGET
	createvisualtask AnimTask_SwayMon, 5, 1, 8, 1536, 5, ANIM_TARGET
	waitforvisualfinish
	createvisualtask AnimTask_HardwarePaletteFade, 2, 248, 3, 10, 0, 1
	waitforvisualfinish
	createvisualtask AnimTask_RemoveSpotlight, 2
	end

Move_TRICK:
	loadspritegfx ANIM_TAG_ITEM_BAG
	loadspritegfx ANIM_TAG_SPEED_DUST
	createsprite gTrickBagSpriteTemplate, ANIM_ATTACKER, 2, -40, 80
	createsprite gTrickBagSpriteTemplate, ANIM_ATTACKER, 2, -40, 208
	delay 16
	playsewithpan SE_M_SKETCH, 0
	createvisualtask AnimTask_StretchTargetUp, 3
	createvisualtask AnimTask_StretchAttackerUp, 3
	delay 30
	playsewithpan SE_M_DOUBLE_TEAM, 0
	delay 24
	playsewithpan SE_M_DOUBLE_TEAM, 0
	delay 16
	playsewithpan SE_M_DOUBLE_TEAM, 0
	delay 16
	playsewithpan SE_M_DOUBLE_TEAM, 0
	delay 16
	playsewithpan SE_M_DOUBLE_TEAM, 0
	delay 16
	playsewithpan SE_M_DOUBLE_TEAM, 0
	delay 16
	playsewithpan SE_M_ATTRACT, 0
	createvisualtask AnimTask_ShakeMon, 3, ANIM_ATTACKER, 5, 0, 7, 2
	createvisualtask AnimTask_ShakeMon, 3, ANIM_TARGET, 5, 0, 7, 2
	waitforvisualfinish
	end

Move_WISH:
	loadspritegfx ANIM_TAG_GOLD_STARS
	loadspritegfx ANIM_TAG_SPARKLE_2
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG, 3, 0, 10, RGB_BLACK
	waitforvisualfinish
	panse_adjustall SE_M_REFLECT, SOUND_PAN_TARGET, SOUND_PAN_ATTACKER, -3, 0
	createsprite gWishStarSpriteTemplate, ANIM_ATTACKER, 40
	waitforvisualfinish
	delay 60
	loopsewithpan SE_M_HEAL_BELL, SOUND_PAN_ATTACKER, 16, 3
	call GrantingStarsEffect
	waitforvisualfinish
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG, 3, 10, 0, RGB_BLACK
	waitforvisualfinish
	end

Move_STOCKPILE:
	loadspritegfx ANIM_TAG_GRAY_ORB
	playsewithpan SE_M_MEGA_KICK, SOUND_PAN_ATTACKER
	createvisualtask AnimTask_BlendColorCycle, 2, F_PAL_ATTACKER, 8, 1, 0, 12, RGB_WHITE
	createvisualtask AnimTask_StockpileDeformMon, 5
	call StockpileAbsorb
	call StockpileAbsorb
	waitforvisualfinish
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_ATTACKER, 0, 12, 0, RGB_WHITE
	end

StockpileAbsorb:
	createsprite gStockpileAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 2, 55, 55, 13
	delay 1
	createsprite gStockpileAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 2, -55, -55, 13
	delay 1
	createsprite gStockpileAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 2, 0, 55, 13
	delay 1
	createsprite gStockpileAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 2, 0, -55, 13
	delay 1
	createsprite gStockpileAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 2, 55, -34, 13
	delay 1
	createsprite gStockpileAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 2, 55, 34, 13
	delay 1
	createsprite gStockpileAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 2, -55, -34, 13
	delay 1
	createsprite gStockpileAbsorptionOrbSpriteTemplate, ANIM_ATTACKER, 2, -55, 34, 13
	delay 1
	return

Move_SPIT_UP:
	loadspritegfx ANIM_TAG_RED_ORB_2
	loadspritegfx ANIM_TAG_IMPACT
	playsewithpan SE_M_TAKE_DOWN, SOUND_PAN_ATTACKER
	createvisualtask AnimTask_SpitUpDeformMon, 5
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_ATTACKER, 1, 0, 8, 2
	delay 45
	playsewithpan SE_M_SPIT_UP, SOUND_PAN_ATTACKER
	delay 3
	createsprite gSpitUpOrbSpriteTemplate, ANIM_ATTACKER, 2, 0, 12
	createsprite gSpitUpOrbSpriteTemplate, ANIM_ATTACKER, 2, 32, 12
	createsprite gSpitUpOrbSpriteTemplate, ANIM_ATTACKER, 2, 64, 12
	createsprite gSpitUpOrbSpriteTemplate, ANIM_ATTACKER, 2, 96, 12
	createsprite gSpitUpOrbSpriteTemplate, ANIM_ATTACKER, 2, 128, 12
	createsprite gSpitUpOrbSpriteTemplate, ANIM_ATTACKER, 2, 160, 12
	createsprite gSpitUpOrbSpriteTemplate, ANIM_ATTACKER, 2, 192, 12
	createsprite gSpitUpOrbSpriteTemplate, ANIM_ATTACKER, 2, 224, 12
	delay 5
	jumpifmoveturn 2, SpitUpStrong
	jumpifmoveturn 3, SpitUpStrongest
SpitUpContinue:
	delay 5
	createvisualtask AnimTask_ShakeTargetBasedOnMovePowerOrDmg, 2, FALSE, 1, 8, 1, 0
	playsewithpan SE_M_DOUBLE_SLAP, SOUND_PAN_TARGET
	createsprite gFlashingHitSplatSpriteTemplate, ANIM_TARGET, 3, -12, 10, ANIM_TARGET, 1
	delay 5
	playsewithpan SE_M_DOUBLE_SLAP, SOUND_PAN_TARGET
	createsprite gFlashingHitSplatSpriteTemplate, ANIM_TARGET, 3, 12, -10, ANIM_TARGET, 1
	waitforvisualfinish
	end

SpitUpStrong:
	createsprite gSpitUpOrbSpriteTemplate, ANIM_ATTACKER, 2, 16
	createsprite gSpitUpOrbSpriteTemplate, ANIM_ATTACKER, 2, 80
	createsprite gSpitUpOrbSpriteTemplate, ANIM_ATTACKER, 2, 144
	createsprite gSpitUpOrbSpriteTemplate, ANIM_ATTACKER, 2, 208
	goto SpitUpContinue

SpitUpStrongest:
	createsprite gSpitUpOrbSpriteTemplate, ANIM_ATTACKER, 2, 16
	createsprite gSpitUpOrbSpriteTemplate, ANIM_ATTACKER, 2, 48
	createsprite gSpitUpOrbSpriteTemplate, ANIM_ATTACKER, 2, 80
	createsprite gSpitUpOrbSpriteTemplate, ANIM_ATTACKER, 2, 112
	createsprite gSpitUpOrbSpriteTemplate, ANIM_ATTACKER, 2, 144
	createsprite gSpitUpOrbSpriteTemplate, ANIM_ATTACKER, 2, 176
	createsprite gSpitUpOrbSpriteTemplate, ANIM_ATTACKER, 2, 208
	createsprite gSpitUpOrbSpriteTemplate, ANIM_ATTACKER, 2, 240
	goto SpitUpContinue

Move_SWALLOW:
	loadspritegfx ANIM_TAG_BLUE_ORB
	loadspritegfx ANIM_TAG_BLUE_STAR
	playsewithpan SE_M_TAKE_DOWN, SOUND_PAN_ATTACKER
	createvisualtask AnimTask_SwallowDeformMon, 5
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_ATTACKER, 1, 0, 8, 2
	delay 38
	playsewithpan SE_M_SPIT_UP, SOUND_PAN_ATTACKER
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_ATTACKER, 2, 0, 12, 1
	call SwallowEffect
	jumpifmoveturn 2, SwallowGood
	jumpifmoveturn 3, SwallowBest
SwallowContinue:
	waitforvisualfinish
	call HealingEffect
	end

SwallowEffect:
	createsprite gSwallowBlueOrbSpriteTemplate, ANIM_ATTACKER, 2, 0, -8
	delay 1
	createsprite gSwallowBlueOrbSpriteTemplate, ANIM_ATTACKER, 2, -24, -8
	delay 1
	createsprite gSwallowBlueOrbSpriteTemplate, ANIM_ATTACKER, 2, 16, -8
	delay 1
	createsprite gSwallowBlueOrbSpriteTemplate, ANIM_ATTACKER, 2, -16, -8
	delay 1
	createsprite gSwallowBlueOrbSpriteTemplate, ANIM_ATTACKER, 2, 24, -8
	delay 1
	return

SwallowGood:
	call SwallowEffect
	goto SwallowContinue

SwallowBest:
	call SwallowEffect
	call SwallowEffect
	goto SwallowContinue

Move_TRANSFORM:
	monbg ANIM_ATTACKER
	playsewithpan SE_M_TELEPORT, SOUND_PAN_ATTACKER
	waitplaysewithpan SE_M_MINIMIZE, SOUND_PAN_ATTACKER, 48
	createvisualtask AnimTask_TransformMon, 2, 0
	waitforvisualfinish
	clearmonbg ANIM_ATTACKER
	end

Move_MORNING_SUN:
	loadspritegfx ANIM_TAG_GREEN_STAR
	loadspritegfx ANIM_TAG_BLUE_STAR
	createvisualtask AnimTask_MorningSunLightBeam, 5
	delay 8
	createvisualtask AnimTask_BlendBattleAnimPal, 10, F_PAL_BG | F_PAL_BATTLERS_2, 8, 0, 12, RGB_WHITE
	delay 14
	call MorningSunStar
	call MorningSunStar
	call MorningSunStar
	call MorningSunStar
	call MorningSunStar
	call MorningSunStar
	call MorningSunStar
	call MorningSunStar
	call MorningSunStar
	call MorningSunStar
	call MorningSunStar
	call MorningSunStar
	call MorningSunStar
	call MorningSunStar
	call MorningSunStar
	createvisualtask AnimTask_BlendBattleAnimPal, 10, F_PAL_BG | F_PAL_BATTLERS_2, 3, 12, 0, RGB_WHITE
	waitforvisualfinish
	waitsound
	call HealingEffect
	end

MorningSunStar:
	createsprite gGreenStarSpriteTemplate, ANIM_ATTACKER, 2, 30, 640
	delay 5
	return

Move_SWEET_SCENT:
	loadspritegfx ANIM_TAG_PINK_PETAL
	playsewithpan SE_M_SWEET_SCENT, SOUND_PAN_ATTACKER
	createsprite gSweetScentPetalSpriteTemplate, ANIM_ATTACKER, 2, 100, 0, 100
	delay 25
	setpan 0
	call SweetScentEffect
	createsprite gSweetScentPetalSpriteTemplate, ANIM_ATTACKER, 2, 55, 0
	setpan SOUND_PAN_TARGET
	createvisualtask AnimTask_BlendColorCycle, 2, F_PAL_DEF_SIDE, 1, 5, 5, 13, RGB(31, 21, 21)
	call SweetScentEffect
	waitforvisualfinish
	end

SweetScentEffect:
	createsprite gSweetScentPetalSpriteTemplate, ANIM_ATTACKER, 2, 70, 1, 64
	delay 2
	createsprite gSweetScentPetalSpriteTemplate, ANIM_ATTACKER, 2, 60, 0, 64
	delay 5
	createsprite gSweetScentPetalSpriteTemplate, ANIM_ATTACKER, 2, 80, 1, 64
	delay 2
	createsprite gSweetScentPetalSpriteTemplate, ANIM_ATTACKER, 2, 58, 0, 120
	delay 2
	createsprite gSweetScentPetalSpriteTemplate, ANIM_ATTACKER, 2, 100, 0, 120
	delay 2
	createsprite gSweetScentPetalSpriteTemplate, ANIM_ATTACKER, 2, 90, 0, 64
	delay 2
	createsprite gSweetScentPetalSpriteTemplate, ANIM_ATTACKER, 2, 48, 0, 64
	delay 2
	createsprite gSweetScentPetalSpriteTemplate, ANIM_ATTACKER, 2, 95, 1, 80
	delay 2
	createsprite gSweetScentPetalSpriteTemplate, ANIM_ATTACKER, 2, 100, 0, 120
	delay 2
	createsprite gSweetScentPetalSpriteTemplate, ANIM_ATTACKER, 2, 75, 1, 64
	delay 2
	createsprite gSweetScentPetalSpriteTemplate, ANIM_ATTACKER, 2, 85, 0, 120
	delay 2
	return

Move_HYPER_BEAM:
	loadspritegfx ANIM_TAG_ORBS
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG, 4, 0, 16, RGB_BLACK
	waitforvisualfinish
	delay 10
	playsewithpan SE_M_HYPER_BEAM, SOUND_PAN_ATTACKER
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_ATTACKER, 1, 0, 4, 1
	waitforvisualfinish
	delay 30
	createsoundtask SoundTask_LoopSEAdjustPanning, SE_M_HYPER_BEAM2, SOUND_PAN_ATTACKER, SOUND_PAN_TARGET, 1, 15, 0, 5
	createvisualtask AnimTask_ShakeMon, 2, ANIM_ATTACKER, 0, 4, 50, 1
	createvisualtask AnimTask_FlashAnimTagWithColor, 2, ANIM_TAG_ORBS, 1, 12, RGB(31, 0, 0), 16, 0, 0
	call HyperBeamOrbs
	call HyperBeamOrbs
	call HyperBeamOrbs
	call HyperBeamOrbs
	call HyperBeamOrbs
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_TARGET, 4, 0, 50, 1
	createvisualtask AnimTask_BlendBattleAnimPal, 10, F_PAL_TARGET, 2, 0, 11, RGB(25, 25, 25)
	call HyperBeamOrbs
	call HyperBeamOrbs
	call HyperBeamOrbs
	call HyperBeamOrbs
	call HyperBeamOrbs
	call HyperBeamOrbs
	call HyperBeamOrbs
	call HyperBeamOrbs
	call HyperBeamOrbs
	call HyperBeamOrbs
	call HyperBeamOrbs
	call HyperBeamOrbs
	call HyperBeamOrbs
	call HyperBeamOrbs
	call HyperBeamOrbs
	call HyperBeamOrbs
	call HyperBeamOrbs
	call HyperBeamOrbs
	call HyperBeamOrbs
	call HyperBeamOrbs
	call HyperBeamOrbs
	createvisualtask AnimTask_BlendBattleAnimPal, 10, F_PAL_TARGET, 2, 11, 0, RGB(25, 25, 25)
	waitforvisualfinish
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG, 4, 16, 0, RGB_BLACK
	end

HyperBeamOrbs:
	createsprite gHyperBeamOrbSpriteTemplate, ANIM_TARGET, 2
	createsprite gHyperBeamOrbSpriteTemplate, ANIM_TARGET, 2
	delay 1
	return

Move_FLATTER:
	loadspritegfx ANIM_TAG_SPOTLIGHT
	loadspritegfx ANIM_TAG_CONFETTI
	createvisualtask SoundTask_PlaySE2WithPanning, 5, SE_M_ENCORE2, SOUND_PAN_TARGET
	createvisualtask AnimTask_CreateSpotlight, 2
	createvisualtask AnimTask_HardwarePaletteFade, 2, 248, 3, 0, 10, 0
	waitforvisualfinish
	createsprite gFlatterSpotlightSpriteTemplate, ANIM_TARGET, 2, 0, -8, 80
	delay 0
	createsprite gVerticalDipSpriteTemplate, ANIM_ATTACKER, 2, 5, 2, ANIM_TARGET
	delay 10
	createsprite gVerticalDipSpriteTemplate, ANIM_ATTACKER, 2, 5, 2, ANIM_TARGET
	delay 0
	createvisualtask SoundTask_PlaySE1WithPanning, 5, SE_M_FLATTER, SOUND_PAN_ATTACKER
	call CreateFlatterConfetti
	call CreateFlatterConfetti
	call CreateFlatterConfetti
	call CreateFlatterConfetti
	call CreateFlatterConfetti
	call CreateFlatterConfetti
	call CreateFlatterConfetti
	call CreateFlatterConfetti
	call CreateFlatterConfetti
	call CreateFlatterConfetti
	call CreateFlatterConfetti
	call CreateFlatterConfetti
	call CreateFlatterConfetti
	call CreateFlatterConfetti
	call CreateFlatterConfetti
	call CreateFlatterConfetti
	call CreateFlatterConfetti
	call CreateFlatterConfetti
	call CreateFlatterConfetti
	delay 5
	createvisualtask SoundTask_PlaySE1WithPanning, 5, SE_M_FLATTER, SOUND_PAN_TARGET
	waitforvisualfinish
	createvisualtask AnimTask_HardwarePaletteFade, 2, 248, 3, 10, 0, 1
	waitforvisualfinish
	createvisualtask AnimTask_RemoveSpotlight, 2
	end

CreateFlatterConfetti:
	createsprite gFlatterConfettiSpriteTemplate, ANIM_ATTACKER, 40, ANIM_ATTACKER
	createsprite gFlatterConfettiSpriteTemplate, ANIM_ATTACKER, 40, ANIM_TARGET
	return

Move_ROLE_PLAY:
	monbg ANIM_ATK_PARTNER
	createvisualtask AnimTask_BlendBattleAnimPal, 10, F_PAL_TARGET, 2, 0, 16, RGB_WHITE
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG, 2, 0, 10, RGB_BLACK
	waitforvisualfinish
	playsewithpan SE_M_TRI_ATTACK, SOUND_PAN_ATTACKER
	waitplaysewithpan SE_M_DETECT, SOUND_PAN_ATTACKER, 30
	createvisualtask AnimTask_RolePlaySilhouette, 2
	waitforvisualfinish
	clearmonbg ANIM_ATK_PARTNER
	createvisualtask AnimTask_BlendBattleAnimPal, 10, F_PAL_TARGET, 2, 16, 0, RGB_WHITE
	delay 8
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG, 2, 10, 0, RGB_BLACK
	end

Move_REFRESH:
	loadspritegfx ANIM_TAG_THIN_RING
	loadspritegfx ANIM_TAG_SPARKLE_2
	playsewithpan SE_M_STAT_INCREASE, SOUND_PAN_ATTACKER
	createvisualtask AnimTask_StatusClearedEffect, 2, 0
	waitforvisualfinish
	playsewithpan SE_M_MORNING_SUN, SOUND_PAN_ATTACKER
	call GrantingStarsEffect
	waitforvisualfinish
	playsewithpan SE_SHINY, SOUND_PAN_ATTACKER
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG | F_PAL_BATTLERS, 3, 10, 0, RGB(12, 24, 30)
	createsprite gThinRingExpandingSpriteTemplate, ANIM_ATTACKER, 3, 0, 0, 0, 0
	end

Move_BLAZE_KICK:
	loadspritegfx ANIM_TAG_IMPACT
	loadspritegfx ANIM_TAG_HANDS_AND_FEET
	loadspritegfx ANIM_TAG_SMALL_EMBER
	monbg ANIM_TARGET
	setalpha 12, 8
	playsewithpan SE_M_FLAME_WHEEL, SOUND_PAN_TARGET
	createsprite gSpinningHandOrFootSpriteTemplate, ANIM_TARGET, 3, 0, 0, 1, 30
	createvisualtask AnimTask_BlendBattleAnimPal, 10, F_PAL_TARGET, 2, 0, 7, RGB_WHITE
	delay 30
	playsewithpan SE_M_FIRE_PUNCH, SOUND_PAN_TARGET
	createsprite gBasicHitSplatSpriteTemplate, ANIM_TARGET, 2, 0, 0, ANIM_TARGET, 0
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_TARGET, 3, 0, 14, 1
	createvisualtask AnimTask_BlendBattleAnimPal, 10, F_PAL_TARGET, 2, 0, 0, RGB_WHITE
	createsprite gComplexPaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG | F_PAL_BATTLERS, 3, 1, RGB_BLACK, 8, RGB_BLACK, 0
	call FireSpreadEffect
	waitforvisualfinish
	clearmonbg ANIM_TARGET
	blendoff
	end

Move_HYPER_VOICE:
	loadspritegfx ANIM_TAG_THIN_RING
	call HyperVoiceEffect
	waitforvisualfinish
	delay 8
	call HyperVoiceEffect
	waitforvisualfinish
	end

HyperVoiceEffect:
	createvisualtask SoundTask_PlayCryWithEcho, 5
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG | F_PAL_BATTLERS, 3, 8, 0, RGB_YELLOW
	createvisualtask AnimTask_ScaleMonAndRestore, 5, -5, -5, 5, ANIM_ATTACKER, 0
	createsprite gHyperVoiceRingSpriteTemplate, ANIM_ATTACKER, 0, 45, 0, 0, 0, 0, 0, 1
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_TARGET, 1, 0, 6, 1
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_DEF_PARTNER, 1, 0, 6, 1
	createvisualtask AnimTask_ShakeBattleTerrain, 2, 1, 0, 6, 1
	createvisualtask SoundTask_WaitForCry, 5
	return

Move_SAND_TOMB:
	loadspritegfx ANIM_TAG_MUD_SAND
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 0, F_PAL_TARGET, 2, 0, 7, RGB(19, 17, 0)
	createvisualtask AnimTask_ShakeMon, 5, ANIM_TARGET, 0, 2, 43, 1
	playsewithpan SE_M_SAND_TOMB, SOUND_PAN_TARGET
	call SandTombSwirlingDirt
	call SandTombSwirlingDirt
	call SandTombSwirlingDirt
	delay 22
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 0, F_PAL_TARGET, 2, 7, 0, RGB(19, 17, 0)
	waitforvisualfinish
	end

SandTombSwirlingDirt:
	createsprite gSwirlingDirtSpriteTemplate, ANIM_TARGET, 2, 0, 32, 528, 30, 10, 50, ANIM_TARGET
	delay 2
	createsprite gSwirlingDirtSpriteTemplate, ANIM_TARGET, 2, 0, 36, 480, 20, 13, -46, ANIM_TARGET
	delay 2
	createsprite gSwirlingDirtSpriteTemplate, ANIM_TARGET, 2, 0, 37, 576, 20, 5, 42, ANIM_TARGET
	delay 2
	createsprite gSwirlingDirtSpriteTemplate, ANIM_TARGET, 2, 0, 35, 400, 25, 8, -42, ANIM_TARGET
	delay 2
	createsprite gSwirlingDirtSpriteTemplate, ANIM_TARGET, 2, 0, 32, 512, 25, 13, 46, ANIM_TARGET
	delay 2
	createsprite gSwirlingDirtSpriteTemplate, ANIM_TARGET, 2, 0, 37, 464, 30, 12, -50, ANIM_TARGET
	delay 2
	return

Move_SHEER_COLD:
	fadetobg BG_ICE
	waitbgfadeout
	playsewithpan SE_M_ICY_WIND, 0
	waitbgfadein
	loadspritegfx ANIM_TAG_ICE_CUBE
	monbg ANIM_DEF_PARTNER
	splitbgprio ANIM_TARGET
	setalpha 12, 8
	createvisualtask AnimTask_FrozenIceCube, 2
	waitplaysewithpan SE_M_HAIL, SOUND_PAN_TARGET, 17
	waitforvisualfinish
	clearmonbg ANIM_DEF_PARTNER
	blendoff
	restorebg
	waitbgfadein
	end

Move_ARM_THRUST:
	loadspritegfx ANIM_TAG_HANDS_AND_FEET
	loadspritegfx ANIM_TAG_IMPACT
	splitbgprio ANIM_TARGET
	setalpha 12, 8
	createvisualtask AnimTask_RotateMonSpriteToSide, 5, 8, 5, ANIM_ATTACKER, 0
	delay 6
	createsprite gHorizontalLungeSpriteTemplate, ANIM_ATTACKER, 2, 4, 3
	delay 4
	playsewithpan SE_M_SWAGGER, SOUND_PAN_TARGET
	createsprite gArmThrustHandSpriteTemplate, ANIM_TARGET, 2, 10, -8, 14, 3
	waitforvisualfinish
	createvisualtask AnimTask_RotateMonSpriteToSide, 5, 8, 5, ANIM_ATTACKER, 1
	playsewithpan SE_M_DOUBLE_SLAP, SOUND_PAN_TARGET
	choosetwoturnanim ArmThrustRight, ArmThrustLeft

ArmThrustContinue:
	createvisualtask AnimTask_ShakeMon, 5, ANIM_TARGET, 4, 0, 6, 1
	waitforvisualfinish
	blendoff
	end

ArmThrustRight:
	createsprite gBasicHitSplatSpriteTemplate, ANIM_TARGET, 2, 8, 0, ANIM_TARGET, 2
	goto ArmThrustContinue

ArmThrustLeft:
	createsprite gBasicHitSplatSpriteTemplate, ANIM_TARGET, 2, -8, 0, ANIM_TARGET, 2
	goto ArmThrustContinue

Move_MUDDY_WATER:
	panse SE_M_WHIRLPOOL, SOUND_PAN_ATTACKER, SOUND_PAN_TARGET, +2, 0
	createvisualtask AnimTask_CreateSurfWave, 2, TRUE
	waitforvisualfinish
	end

Move_BULLET_SEED:
	loadspritegfx ANIM_TAG_SEED
	createsprite gBulletSeedSpriteTemplate, ANIM_TARGET, 2, 20, 0
	delay 5
	createsprite gBulletSeedSpriteTemplate, ANIM_TARGET, 2, 20, 0
	delay 5
	createsprite gBulletSeedSpriteTemplate, ANIM_TARGET, 2, 20, 0
	delay 5
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_TARGET, 2, 0, 30, 1
	createsprite gBulletSeedSpriteTemplate, ANIM_TARGET, 2, 20, 0
	delay 5
	createsprite gBulletSeedSpriteTemplate, ANIM_TARGET, 2, 20, 0
	delay 5
	createsprite gBulletSeedSpriteTemplate, ANIM_TARGET, 2, 20, 0
	delay 5
	createsprite gBulletSeedSpriteTemplate, ANIM_TARGET, 2, 20, 0
	delay 5
	createsprite gBulletSeedSpriteTemplate, ANIM_TARGET, 2, 20, 0
	delay 5
	createsprite gBulletSeedSpriteTemplate, ANIM_TARGET, 2, 20, 0
	delay 5
	createsprite gBulletSeedSpriteTemplate, ANIM_TARGET, 2, 20, 0
	waitforvisualfinish
	end

Move_DRAGON_CLAW:
	loadspritegfx ANIM_TAG_SMALL_EMBER
	loadspritegfx ANIM_TAG_CLAW_SLASH
	playsewithpan SE_M_SACRED_FIRE2, SOUND_PAN_ATTACKER
	createvisualtask AnimTask_BlendBattleAnimPal, 10, F_PAL_ATTACKER, 4, 0, 8, RGB(31, 19, 0)
	createvisualtask AnimTask_ShakeMon, 5, ANIM_ATTACKER, 0, 2, 15, 1
	call DragonClawFireSpiral
	call DragonClawFireSpiral
	createsprite gHorizontalLungeSpriteTemplate, ANIM_ATTACKER, 2, 6, 4
	createsprite gFireSpinSpriteTemplate, ANIM_ATTACKER, 2, 0, 28, 528, 30, 13, 50, ANIM_ATTACKER
	delay 2
	createvisualtask SoundTask_PlaySE1WithPanning, 5, SE_M_RAZOR_WIND, SOUND_PAN_TARGET
	createsprite gClawSlashSpriteTemplate, ANIM_TARGET, 2, -10, -10, 0
	createsprite gClawSlashSpriteTemplate, ANIM_TARGET, 2, -10, 10, 0
	createsprite gShakeMonOrTerrainSpriteTemplate, ANIM_ATTACKER, 2, -4, 1, 10, 3, 1
	createsprite gFireSpinSpriteTemplate, ANIM_ATTACKER, 2, 0, 32, 480, 20, 16, -46, ANIM_ATTACKER
	delay 2
	createsprite gFireSpinSpriteTemplate, ANIM_ATTACKER, 2, 0, 33, 576, 20, 8, 42, ANIM_ATTACKER
	delay 2
	createsprite gFireSpinSpriteTemplate, ANIM_ATTACKER, 2, 0, 31, 400, 25, 11, -42, ANIM_ATTACKER
	delay 2
	createsprite gHorizontalLungeSpriteTemplate, ANIM_ATTACKER, 2, 6, 4
	createsprite gFireSpinSpriteTemplate, ANIM_ATTACKER, 2, 0, 28, 512, 25, 16, 46, ANIM_ATTACKER
	delay 2
	createvisualtask SoundTask_PlaySE1WithPanning, 5, SE_M_RAZOR_WIND, SOUND_PAN_TARGET
	createsprite gClawSlashSpriteTemplate, ANIM_TARGET, 2, 10, -10, 1
	createsprite gClawSlashSpriteTemplate, ANIM_TARGET, 2, 10, 10, 1
	createsprite gShakeMonOrTerrainSpriteTemplate, ANIM_ATTACKER, 2, -4, 1, 10, 3, 1
	createsprite gFireSpinSpriteTemplate, ANIM_ATTACKER, 2, 0, 33, 464, 30, 15, -50, ANIM_ATTACKER
	delay 2
	createsprite gFireSpinSpriteTemplate, ANIM_ATTACKER, 2, 0, 28, 528, 30, 13, 50, ANIM_ATTACKER
	delay 2
	createsprite gFireSpinSpriteTemplate, ANIM_ATTACKER, 2, 0, 32, 480, 20, 16, -46, ANIM_ATTACKER
	delay 2
	createsprite gFireSpinSpriteTemplate, ANIM_ATTACKER, 2, 0, 33, 576, 20, 8, 42, ANIM_ATTACKER
	delay 2
	createsprite gFireSpinSpriteTemplate, ANIM_ATTACKER, 2, 0, 31, 400, 25, 11, -42, ANIM_ATTACKER
	delay 2
	createsprite gFireSpinSpriteTemplate, ANIM_ATTACKER, 2, 0, 28, 512, 25, 16, 46, ANIM_ATTACKER
	delay 2
	createsprite gFireSpinSpriteTemplate, ANIM_ATTACKER, 2, 0, 33, 464, 30, 15, -50, ANIM_ATTACKER
	createvisualtask AnimTask_BlendBattleAnimPal, 10, F_PAL_ATTACKER, 4, 8, 0, RGB(31, 19, 0)
	waitforvisualfinish
	end

DragonClawFireSpiral:
	createsprite gFireSpinSpriteTemplate, ANIM_ATTACKER, 2, 0, 28, 528, 30, 13, 50, ANIM_ATTACKER
	delay 2
	createsprite gFireSpinSpriteTemplate, ANIM_ATTACKER, 2, 0, 32, 480, 20, 16, -46, ANIM_ATTACKER
	delay 2
	createsprite gFireSpinSpriteTemplate, ANIM_ATTACKER, 2, 0, 33, 576, 20, 8, 42, ANIM_ATTACKER
	delay 2
	createsprite gFireSpinSpriteTemplate, ANIM_ATTACKER, 2, 0, 31, 400, 25, 11, -42, ANIM_ATTACKER
	delay 2
	createsprite gFireSpinSpriteTemplate, ANIM_ATTACKER, 2, 0, 28, 512, 25, 16, 46, ANIM_ATTACKER
	delay 2
	createsprite gFireSpinSpriteTemplate, ANIM_ATTACKER, 2, 0, 33, 464, 30, 15, -50, ANIM_ATTACKER
	delay 2
	return

	end

Move_MUD_SHOT:
	loadspritegfx ANIM_TAG_BROWN_ORB
	monbg ANIM_DEF_PARTNER
	splitbgprio ANIM_TARGET
	setalpha 12, 8
	createvisualtask AnimTask_ShakeMon, 5, ANIM_ATTACKER, 0, 2, 46, 1
	delay 6
	createvisualtask AnimTask_StartSinAnimTimer, 5, 100
	panse SE_M_WHIRLPOOL, SOUND_PAN_ATTACKER, SOUND_PAN_TARGET, +1, 0
	call MudShotOrbs
	call MudShotOrbs
	call MudShotOrbs
	createvisualtask AnimTask_ShakeMon, 5, ANIM_TARGET, 3, 0, 43, 1
	call MudShotOrbs
	call MudShotOrbs
	call MudShotOrbs
	call MudShotOrbs
	call MudShotOrbs
	call MudShotOrbs
	call MudShotOrbs
	call MudShotOrbs
	waitforvisualfinish
	clearmonbg ANIM_DEF_PARTNER
	blendoff
	end

MudShotOrbs:
	createsprite gMudShotOrbSpriteTemplate, ANIM_ATTACKER, 3, 10, 10, 0, 16
	delay 2
	createsprite gMudShotOrbSpriteTemplate, ANIM_ATTACKER, 3, 10, 10, 0, 16
	delay 2
	return

Move_METEOR_MASH:
	loadspritegfx ANIM_TAG_GOLD_STARS
	loadspritegfx ANIM_TAG_IMPACT
	loadspritegfx ANIM_TAG_HANDS_AND_FEET
	panse SE_M_BARRIER, SOUND_PAN_ATTACKER, SOUND_PAN_TARGET, +3, 0
	fadetobg BG_COSMIC
	waitbgfadein
	waitforvisualfinish
	createsprite gMeteorMashStarSpriteTemplate, ANIM_TARGET, 3, -48, -64, 72, 32, 30
	delay 10
	createsprite gMeteorMashStarSpriteTemplate, ANIM_TARGET, 3, -112, -64, 8, 32, 30
	delay 40
	createsprite gSpinningHandOrFootSpriteTemplate, ANIM_TARGET, 3, 0, 0, 0, 30
	createsprite gMeteorMashStarSpriteTemplate, ANIM_TARGET, 3, -80, -64, 40, 32, 30
	delay 20
	playsewithpan SE_M_VITAL_THROW2, SOUND_PAN_TARGET
	createsprite gBasicHitSplatSpriteTemplate, ANIM_TARGET, 3, 0, 0, ANIM_TARGET, 1
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_TARGET, 5, 0, 20, 1
	waitforvisualfinish
	delay 10
	restorebg
	waitbgfadein
	waitforvisualfinish
	end

Move_REVENGE:
	loadspritegfx ANIM_TAG_PURPLE_SCRATCH
	monbg ANIM_TARGET
	setalpha 12, 8
	playsewithpan SE_M_TAKE_DOWN, SOUND_PAN_ATTACKER
	createsprite gRevengeSmallScratchSpriteTemplate, ANIM_ATTACKER, 2, 10, -10
	waitforvisualfinish
	createvisualtask AnimTask_BlendColorCycle, 2, F_PAL_ATTACKER, 0, 4, 2, 8, RGB_RED
	waitforvisualfinish
	unloadspritegfx ANIM_TAG_PURPLE_SCRATCH
	loadspritegfx ANIM_TAG_PURPLE_SWIPE
	createsprite gHorizontalLungeSpriteTemplate, ANIM_ATTACKER, 2, 6, 4
	delay 4
	playsewithpan SE_M_SWAGGER, SOUND_PAN_TARGET
	createsprite gRevengeBigScratchSpriteTemplate, ANIM_TARGET, 2, 10, -10
	waitforvisualfinish
	unloadspritegfx ANIM_TAG_PURPLE_SWIPE
	loadspritegfx ANIM_TAG_IMPACT
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_TARGET, 3, 0, 10, 1
	createsprite gPersistHitSplatSpriteTemplate, ANIM_TARGET, 3, -10, -8, ANIM_TARGET, 1, 8
	playsewithpan SE_M_VITAL_THROW2, SOUND_PAN_TARGET
	delay 8
	createsprite gPersistHitSplatSpriteTemplate, ANIM_TARGET, 3, 10, 8, ANIM_TARGET, 1, 8
	playsewithpan SE_M_MEGA_KICK2, SOUND_PAN_TARGET
	waitforvisualfinish
	clearmonbg ANIM_TARGET
	blendoff
	end

Move_POISON_FANG:
	loadspritegfx ANIM_TAG_FANG_ATTACK
	loadspritegfx ANIM_TAG_POISON_BUBBLE
	playsewithpan SE_M_BITE, SOUND_PAN_TARGET
	createsprite gFangSpriteTemplate, ANIM_TARGET, 2
	delay 10
	createvisualtask AnimTask_ShakeMon, 3, ANIM_TARGET, 3, 0, 10, 1
	waitforvisualfinish
	createvisualtask AnimTask_BlendColorCycle, 2, F_PAL_TARGET, 0, 4, 0, 12, RGB(26, 0, 26)
	call PoisonBubblesEffect
	waitforvisualfinish
	end

Move_SUBSTITUTE:
	playsewithpan SE_M_ATTRACT, SOUND_PAN_ATTACKER
	createvisualtask AnimTask_MonToSubstitute, 2
	end

Move_FRENZY_PLANT:
	loadspritegfx ANIM_TAG_ROOTS
	loadspritegfx ANIM_TAG_IMPACT
	monbg ANIM_TARGET
	splitbgprio ANIM_TARGET
	setalpha 12, 8
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 0, F_PAL_BG, 2, 0, 5, RGB_BLACK
	waitforvisualfinish
	createsprite gFrenzyPlantRootSpriteTemplate, ANIM_ATTACKER, 2, 10, 8, 2, 0, 0, 100
	playsewithpan SE_M_SCRATCH, SOUND_PAN_ATTACKER
	delay 5
	createsprite gFrenzyPlantRootSpriteTemplate, ANIM_ATTACKER, 2, 20, -8, -2, 0, 1, 95
	playsewithpan SE_M_SCRATCH, -43
	delay 5
	createsprite gFrenzyPlantRootSpriteTemplate, ANIM_ATTACKER, 2, 30, 8, -4, 0, 0, 90
	playsewithpan SE_M_SCRATCH, -22
	delay 5
	createsprite gFrenzyPlantRootSpriteTemplate, ANIM_ATTACKER, 2, 40, -8, 4, 0, 1, 85
	playsewithpan SE_M_SCRATCH, 0
	delay 5
	createsprite gFrenzyPlantRootSpriteTemplate, ANIM_ATTACKER, 2, 50, 8, 0, 0, 0, 85
	playsewithpan SE_M_SCRATCH, +21
	delay 5
	createsprite gFrenzyPlantRootSpriteTemplate, ANIM_ATTACKER, 2, 60, -8, -2, 0, 1, 85
	playsewithpan SE_M_SCRATCH, +42
	delay 5
	createsprite gFrenzyPlantRootSpriteTemplate, ANIM_ATTACKER, 2, 75, 8, 0, 0, 0, 85
	playsewithpan SE_M_SCRATCH, SOUND_PAN_TARGET
	delay 5
	createsprite gFrenzyPlantRootSpriteTemplate, ANIM_ATTACKER, 2, 85, 16, 6, 0, 3, 80
	playsewithpan SE_M_SCRATCH, SOUND_PAN_TARGET
	delay 5
	createsprite gFrenzyPlantRootSpriteTemplate, ANIM_ATTACKER, 2, 85, -16, -6, 0, 2, 75
	playsewithpan SE_M_SCRATCH, SOUND_PAN_TARGET
	delay 5
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 2, -10, -10, ANIM_TARGET, 3
	playsewithpan SE_M_DOUBLE_SLAP, SOUND_PAN_TARGET
	createvisualtask AnimTask_ShakeMon, 3, ANIM_TARGET, 8, 0, 20, 1
	delay 3
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 2, 10, 8, ANIM_TARGET, 3
	playsewithpan SE_M_DOUBLE_SLAP, SOUND_PAN_TARGET
	delay 3
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 2, 10, -3, ANIM_TARGET, 2
	playsewithpan SE_M_DOUBLE_SLAP, SOUND_PAN_TARGET
	delay 3
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 2, -3, 1, ANIM_TARGET, 2
	playsewithpan SE_M_DOUBLE_SLAP, SOUND_PAN_TARGET
	delay 2
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 2, -10, 1, ANIM_TARGET, 1
	playsewithpan SE_M_DOUBLE_SLAP, SOUND_PAN_TARGET
	delay 2
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 2, 0, 10, ANIM_TARGET, 1
	playsewithpan SE_M_DOUBLE_SLAP, SOUND_PAN_TARGET
	waitforvisualfinish
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 0, F_PAL_BG, 2, 5, 0, RGB_BLACK
	waitforvisualfinish
	clearmonbg ANIM_TARGET
	blendoff
	end

Move_METAL_SOUND:
	loadspritegfx ANIM_TAG_METAL_SOUND_WAVES
	monbg ANIM_DEF_PARTNER
	splitbgprio_foes ANIM_TARGET
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_ATTACKER, 2, 0, 8, 1
	call MetalSoundRings
	call MetalSoundRings
	call MetalSoundRings
	call MetalSoundRings
	waitforvisualfinish
	clearmonbg ANIM_DEF_PARTNER
	delay 0
	waitforvisualfinish
	end

MetalSoundRings:
	panse SE_M_SCREECH, SOUND_PAN_ATTACKER, SOUND_PAN_TARGET, +2, 0
	createsprite gMetalSoundSpriteTemplate, ANIM_TARGET, 2, 16, 0, 0, 0, 30, 0
	delay 2
	return

Move_FOCUS_PUNCH:
	goto FocusPunch

FocusPunchEnd:
	waitforvisualfinish
	end

FocusPunch:
	loadspritegfx ANIM_TAG_IMPACT
	loadspritegfx ANIM_TAG_HANDS_AND_FEET
	delay 1
	createvisualtask AnimTask_IsContest, 2
	jumprettrue FocusPunchInContest
	createvisualtask AnimTask_IsTargetPlayerSide, 2
	jumpretfalse FocusPunchOnOpponent
	jumprettrue FocusPunchOnPlayer
FocusPunchContinue:
	waitbgfadein
	monbg ANIM_DEF_PARTNER
	setalpha 12, 8
	playsewithpan SE_M_SWAGGER, SOUND_PAN_TARGET
	createsprite gFocusPunchFistSpriteTemplate, ANIM_TARGET, 2
	delay 10
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 2, -10, -8, ANIM_TARGET, 0
	createvisualtask AnimTask_ShakeMon, 5, ANIM_TARGET, 8, 0, 24, 1
	delay 8
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 2, 10, 2, ANIM_TARGET, 0
	playsewithpan SE_M_VITAL_THROW2, SOUND_PAN_TARGET
	delay 8
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 2, 10, -6, ANIM_TARGET, 0
	playsewithpan SE_M_VITAL_THROW2, SOUND_PAN_TARGET
	delay 8
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 2, 0, 8, ANIM_TARGET, 0
	playsewithpan SE_M_MEGA_KICK2, SOUND_PAN_TARGET
	waitforvisualfinish
	restorebg
	waitbgfadein
	clearmonbg ANIM_DEF_PARTNER
	blendoff
	goto FocusPunchEnd

FocusPunchOnOpponent:
	fadetobg BG_IMPACT_OPPONENT
	goto FocusPunchContinue

FocusPunchOnPlayer:
	fadetobg BG_IMPACT_PLAYER
	goto FocusPunchContinue

FocusPunchInContest:
	fadetobg BG_IMPACT_CONTESTS
	goto FocusPunchContinue

Move_RETURN:
	loadspritegfx ANIM_TAG_IMPACT
	monbg ANIM_DEF_PARTNER
	setalpha 12, 8
	createvisualtask AnimTask_GetReturnPowerLevel, 2
	delay 2
	jumpreteq 0, ReturnWeak
	jumpreteq 1, ReturnMedium
	jumpreteq 2, ReturnStrong
	jumpreteq 3, ReturnStrongest
ReturnContinue:
	waitforvisualfinish
	clearmonbg ANIM_DEF_PARTNER
	blendoff
	end

ReturnWeak:
	createsprite gVerticalDipSpriteTemplate, ANIM_ATTACKER, 2, 16, 1, ANIM_ATTACKER
	createvisualtask SoundTask_PlaySE2WithPanning, 5, SE_M_TAIL_WHIP, SOUND_PAN_ATTACKER
	waitforvisualfinish
	createsprite gVerticalDipSpriteTemplate, ANIM_ATTACKER, 2, 16, 1, ANIM_ATTACKER
	createvisualtask SoundTask_PlaySE2WithPanning, 5, SE_M_TAIL_WHIP, SOUND_PAN_ATTACKER
	delay 5
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 2, -10, -8, ANIM_TARGET, 2
	createvisualtask SoundTask_PlaySE1WithPanning, 5, SE_M_COMET_PUNCH, SOUND_PAN_TARGET
	goto ReturnContinue

ReturnMedium:
	createsprite gVerticalDipSpriteTemplate, ANIM_ATTACKER, 2, 6, 1, ANIM_ATTACKER
	createvisualtask SoundTask_PlaySE2WithPanning, 5, SE_M_TAIL_WHIP, SOUND_PAN_ATTACKER
	waitforvisualfinish
	createsprite gVerticalDipSpriteTemplate, ANIM_ATTACKER, 2, 6, 1, ANIM_ATTACKER
	createvisualtask SoundTask_PlaySE2WithPanning, 5, SE_M_TAIL_WHIP, SOUND_PAN_ATTACKER
	waitforvisualfinish
	delay 11
	createsprite gHorizontalLungeSpriteTemplate, ANIM_ATTACKER, 2, 5, 4
	delay 6
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 3, 0, 0, ANIM_TARGET, 2
	createvisualtask SoundTask_PlaySE1WithPanning, 5, SE_M_MEGA_KICK2, SOUND_PAN_TARGET
	goto ReturnContinue

ReturnStrong:
	createsprite gVerticalDipSpriteTemplate, ANIM_ATTACKER, 2, 6, 1, ANIM_ATTACKER
	createvisualtask SoundTask_PlaySE2WithPanning, 5, SE_M_TAIL_WHIP, SOUND_PAN_ATTACKER
	waitforvisualfinish
	createsprite gVerticalDipSpriteTemplate, ANIM_ATTACKER, 2, 6, 1, ANIM_ATTACKER
	createvisualtask SoundTask_PlaySE2WithPanning, 5, SE_M_TAIL_WHIP, SOUND_PAN_ATTACKER
	waitforvisualfinish
	createsprite gVerticalDipSpriteTemplate, ANIM_ATTACKER, 2, 6, 1, ANIM_ATTACKER
	createvisualtask SoundTask_PlaySE2WithPanning, 5, SE_M_TAIL_WHIP, SOUND_PAN_ATTACKER
	waitforvisualfinish
	createsprite gVerticalDipSpriteTemplate, ANIM_ATTACKER, 2, 6, 1, ANIM_ATTACKER
	createvisualtask SoundTask_PlaySE2WithPanning, 5, SE_M_TAIL_WHIP, SOUND_PAN_ATTACKER
	waitforvisualfinish
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 2, -10, -8, ANIM_TARGET, 2
	createvisualtask SoundTask_PlaySE1WithPanning, 5, SE_M_VITAL_THROW2, SOUND_PAN_TARGET
	createvisualtask AnimTask_ShakeMon, 5, ANIM_TARGET, 6, 0, 8, 1
	delay 8
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 2, 10, 10, ANIM_TARGET, 2
	createvisualtask SoundTask_PlaySE1WithPanning, 5, SE_M_VITAL_THROW2, SOUND_PAN_TARGET
	createvisualtask AnimTask_ShakeMon, 5, ANIM_TARGET, 6, 0, 8, 1
	delay 8
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 2, 3, -5, ANIM_TARGET, 2
	createvisualtask SoundTask_PlaySE1WithPanning, 5, SE_M_VITAL_THROW2, SOUND_PAN_TARGET
	createvisualtask AnimTask_ShakeMon, 5, ANIM_TARGET, 6, 0, 8, 1
	delay 8
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 2, -5, 3, ANIM_TARGET, 2
	createvisualtask SoundTask_PlaySE1WithPanning, 5, SE_M_VITAL_THROW2, SOUND_PAN_TARGET
	createvisualtask AnimTask_ShakeMon, 5, ANIM_TARGET, 6, 0, 8, 1
	goto ReturnContinue

ReturnStrongest:
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG, 0, 0, 6, RGB_BLACK
	waitforvisualfinish
	createsprite gVerticalDipSpriteTemplate, ANIM_ATTACKER, 2, 16, 1, ANIM_ATTACKER
	createvisualtask SoundTask_PlaySE2WithPanning, 5, SE_M_TAIL_WHIP, SOUND_PAN_ATTACKER
	delay 8
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 2, 3, -5, ANIM_TARGET, 2
	createvisualtask SoundTask_PlaySE1WithPanning, 5, SE_M_VITAL_THROW2, SOUND_PAN_TARGET
	waitforvisualfinish
	createsprite gVerticalDipSpriteTemplate, ANIM_ATTACKER, 2, 12, 1, ANIM_ATTACKER
	createvisualtask SoundTask_PlaySE2WithPanning, 5, SE_M_TAIL_WHIP, SOUND_PAN_ATTACKER
	delay 5
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 2, -10, -8, ANIM_TARGET, 2
	createvisualtask SoundTask_PlaySE1WithPanning, 5, SE_M_VITAL_THROW2, SOUND_PAN_TARGET
	createvisualtask AnimTask_ShakeMon, 5, ANIM_TARGET, 6, 0, 8, 1
	waitforvisualfinish
	delay 4
	createsprite gVerticalDipSpriteTemplate, ANIM_ATTACKER, 2, 8, 1, ANIM_ATTACKER
	createvisualtask SoundTask_PlaySE2WithPanning, 5, SE_M_TAIL_WHIP, SOUND_PAN_ATTACKER
	delay 5
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 2, -10, -8, ANIM_TARGET, 2
	createvisualtask SoundTask_PlaySE1WithPanning, 5, SE_M_VITAL_THROW2, SOUND_PAN_TARGET
	createvisualtask AnimTask_ShakeMon, 5, ANIM_TARGET, 6, 0, 8, 1
	waitforvisualfinish
	delay 2
	createvisualtask AnimTask_TraceMonBlended, 2, 0, 4, 5, 1
	createsprite gVerticalDipSpriteTemplate, ANIM_ATTACKER, 2, 4, 1, ANIM_ATTACKER
	createvisualtask SoundTask_PlaySE2WithPanning, 5, SE_M_TAIL_WHIP, SOUND_PAN_ATTACKER
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 2, -10, -8, ANIM_TARGET, 2
	createvisualtask SoundTask_PlaySE1WithPanning, 5, SE_M_VITAL_THROW2, SOUND_PAN_TARGET
	createvisualtask AnimTask_ShakeMon, 5, ANIM_TARGET, 6, 0, 8, 1
	createvisualtask AnimTask_TraceMonBlended, 2, 0, 4, 5, 1
	waitforvisualfinish
	createsprite gVerticalDipSpriteTemplate, ANIM_ATTACKER, 2, 4, 2, ANIM_ATTACKER
	createvisualtask SoundTask_PlaySE2WithPanning, 5, SE_M_TAIL_WHIP, SOUND_PAN_ATTACKER
	delay 5
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 2, -10, -8, ANIM_TARGET, 2
	createvisualtask SoundTask_PlaySE1WithPanning, 5, SE_M_VITAL_THROW2, SOUND_PAN_TARGET
	createvisualtask AnimTask_ShakeMon, 5, ANIM_TARGET, 6, 0, 8, 1
	createvisualtask AnimTask_TraceMonBlended, 2, 0, 4, 5, 1
	waitforvisualfinish
	call ReturnStrongestHit
	call ReturnStrongestHit
	call ReturnStrongestHit
	call ReturnStrongestHit
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 2, -10, -8, ANIM_TARGET, 0
	createvisualtask SoundTask_PlaySE1WithPanning, 5, SE_M_MEGA_KICK2, SOUND_PAN_TARGET
	createvisualtask AnimTask_ShakeMon, 5, ANIM_TARGET, 8, 0, 24, 1
	delay 6
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 2, 10, 10, ANIM_TARGET, 0
	createvisualtask SoundTask_PlaySE1WithPanning, 5, SE_M_MEGA_KICK2, SOUND_PAN_TARGET
	delay 6
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 2, 3, -5, ANIM_TARGET, 0
	createvisualtask SoundTask_PlaySE1WithPanning, 5, SE_M_MEGA_KICK2, SOUND_PAN_TARGET
	delay 6
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 2, -5, 3, ANIM_TARGET, 0
	createvisualtask SoundTask_PlaySE1WithPanning, 5, SE_M_MEGA_KICK2, SOUND_PAN_TARGET
	waitforvisualfinish
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG, 0, 6, 0, RGB_BLACK
	goto ReturnContinue

ReturnStrongestHit:
	createsprite gVerticalDipSpriteTemplate, ANIM_ATTACKER, 2, 4, 3, ANIM_ATTACKER
	createvisualtask SoundTask_PlaySE2WithPanning, 5, SE_M_TAIL_WHIP, SOUND_PAN_ATTACKER
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 2, 0, 0, ANIM_TARGET, 2
	createvisualtask SoundTask_PlaySE1WithPanning, 5, SE_M_VITAL_THROW2, SOUND_PAN_TARGET
	createvisualtask AnimTask_ShakeMon, 5, ANIM_TARGET, 6, 0, 8, 1
	createvisualtask AnimTask_TraceMonBlended, 2, 0, 4, 5, 1
	waitforvisualfinish
	return

Move_COSMIC_POWER:
	loadspritegfx ANIM_TAG_SPARKLE_2
	createvisualtask SoundTask_PlaySE2WithPanning, 5, SE_M_COSMIC_POWER, 0
	playsewithpan SE_M_COSMIC_POWER, 0
	createvisualtask AnimTask_BlendNonAttackerPalettes, 2, 0, 0, 15, RGB_BLACK
	waitforvisualfinish
	fadetobg BG_COSMIC
	waitbgfadeout
	createvisualtask AnimTask_StartSlidingBg, 2, 0, 128, 0, -1
	waitbgfadein
	delay 70
	createvisualtask SoundTask_PlaySE1WithPanning, 5, SE_M_MORNING_SUN, SOUND_PAN_ATTACKER
	createsprite gGrantingStarsSpriteTemplate, ANIM_ATTACKER, 2, -15, 0, 0, 0, 32, 60
	delay 8
	createsprite gGrantingStarsSpriteTemplate, ANIM_ATTACKER, 2, 12, -5, 0, 0, 32, 60
	delay 40
	createvisualtask AnimTask_BlendNonAttackerPalettes, 2, 0, 15, 0, RGB_BLACK
	waitforvisualfinish
	restorebg
	waitbgfadeout
	setarg 7, 0xFFFF
	waitbgfadein
	waitforvisualfinish
	end

Move_BLAST_BURN:
	loadspritegfx ANIM_TAG_FIRE_PLUME
	loadspritegfx ANIM_TAG_IMPACT
	monbg ANIM_DEF_PARTNER
	setalpha 12, 8
	playsewithpan SE_M_SACRED_FIRE, SOUND_PAN_ATTACKER
	createsprite gFirePlumeSpriteTemplate, ANIM_ATTACKER, 2, -32, 0, 24, 0, 0, 0
	createsprite gFirePlumeSpriteTemplate, ANIM_ATTACKER, 2, -20, -10, 24, 0, 0, 0
	createsprite gFirePlumeSpriteTemplate, ANIM_ATTACKER, 66, 0, -16, 24, 0, 0, 0
	createsprite gFirePlumeSpriteTemplate, ANIM_ATTACKER, 66, 20, -10, 24, 0, 0, 0
	createsprite gFirePlumeSpriteTemplate, ANIM_ATTACKER, 66, 32, 0, 24, 0, 0, 0
	createsprite gFirePlumeSpriteTemplate, ANIM_ATTACKER, 66, 20, 10, 24, 0, 0, 0
	createsprite gFirePlumeSpriteTemplate, ANIM_ATTACKER, 2, 0, 16, 24, 0, 0, 0
	createsprite gFirePlumeSpriteTemplate, ANIM_ATTACKER, 2, -20, 10, 24, 0, 0, 0
	delay 25
	playsewithpan SE_M_FLAME_WHEEL2, SOUND_PAN_ATTACKER
	createsprite gFirePlumeSpriteTemplate, ANIM_ATTACKER, 2, -64, 0, 24, 0, 0, 0
	createsprite gFirePlumeSpriteTemplate, ANIM_ATTACKER, 6, -40, -20, 24, 0, 0, 0
	createsprite gFirePlumeSpriteTemplate, ANIM_ATTACKER, 70, 0, -32, 24, 0, 0, 0
	createsprite gFirePlumeSpriteTemplate, ANIM_ATTACKER, 70, 40, -20, 24, 0, 0, 0
	createvisualtask AnimTask_ShakeMon, 5, ANIM_TARGET, 6, 0, 8, 1
	createsprite gFirePlumeSpriteTemplate, ANIM_ATTACKER, 66, 64, 0, 24, 0, 0, 0
	createsprite gFirePlumeSpriteTemplate, ANIM_ATTACKER, 66, 40, 20, 24, 0, 0, 0
	createsprite gFirePlumeSpriteTemplate, ANIM_ATTACKER, 2, 0, 32, 24, 0, 0, 0
	createsprite gFirePlumeSpriteTemplate, ANIM_ATTACKER, 2, -40, 20, 24, 0, 0, 0
	createvisualtask AnimTask_InvertScreenColor, 2, 257, 257, 257
	delay 25
	playsewithpan SE_M_FLAME_WHEEL2, SOUND_PAN_ATTACKER
	createsprite gFirePlumeSpriteTemplate, ANIM_ATTACKER, 2, -96, 0, 24, 0, 0, 0
	createsprite gFirePlumeSpriteTemplate, ANIM_ATTACKER, 6, -60, -30, 24, 0, 0, 0
	createsprite gFirePlumeSpriteTemplate, ANIM_ATTACKER, 70, 0, -48, 24, 0, 0, 0
	createsprite gFirePlumeSpriteTemplate, ANIM_ATTACKER, 70, 60, -30, 24, 0, 0, 0
	createsprite gBasicHitSplatSpriteTemplate, ANIM_TARGET, 2, -4, 3, ANIM_TARGET, 0
	createvisualtask AnimTask_ShakeMon, 5, ANIM_TARGET, 12, 0, 20, 1
	createvisualtask AnimTask_ShakeBattleTerrain, 2, 2, 0, 10, 1
	createsprite gFirePlumeSpriteTemplate, ANIM_ATTACKER, 66, 96, 0, 24, 0, 0, 0
	createsprite gFirePlumeSpriteTemplate, ANIM_ATTACKER, 66, 60, 30, 24, 0, 0, 0
	createsprite gFirePlumeSpriteTemplate, ANIM_ATTACKER, 2, 0, 48, 24, 0, 0, 0
	createsprite gFirePlumeSpriteTemplate, ANIM_ATTACKER, 2, -60, 30, 24, 0, 0, 0
	createvisualtask AnimTask_InvertScreenColor, 2, 257, 257, 257
	waitforvisualfinish
	clearmonbg ANIM_DEF_PARTNER
	blendoff
	end

Move_ROCK_TOMB:
	loadspritegfx ANIM_TAG_X_SIGN
	loadspritegfx ANIM_TAG_ROCKS
	createvisualtask AnimTask_ShakeBattleTerrain, 2, 2, 0, 10, 1
	waitforvisualfinish
	createsprite gRockTombRockSpriteTemplate, ANIM_TARGET, 2, 20, 12, 64, 114, 0
	delay 8
	createvisualtask AnimTask_ShakeBattleTerrain, 2, 0, 2, 3, 1
	playsewithpan SE_M_STRENGTH, SOUND_PAN_TARGET
	delay 8
	createsprite gRockTombRockSpriteTemplate, ANIM_TARGET, 2, -20, 12, 64, 98, 0
	delay 8
	createvisualtask AnimTask_ShakeBattleTerrain, 2, 0, 2, 3, 1
	playsewithpan SE_M_STRENGTH, SOUND_PAN_TARGET
	delay 8
	createsprite gRockTombRockSpriteTemplate, ANIM_TARGET, 66, 3, 6, 64, 82, 0
	delay 8
	createvisualtask AnimTask_ShakeBattleTerrain, 2, 0, 2, 3, 1
	playsewithpan SE_M_STRENGTH, SOUND_PAN_TARGET
	delay 8
	createsprite gRockTombRockSpriteTemplate, ANIM_TARGET, 2, -3, 13, 64, 66, 0
	delay 8
	createvisualtask AnimTask_ShakeBattleTerrain, 2, 0, 2, 3, 1
	playsewithpan SE_M_STRENGTH, SOUND_PAN_TARGET
	delay 24
	playsewithpan SE_M_HYPER_BEAM, SOUND_PAN_TARGET
	createsprite gRedXSpriteTemplate, ANIM_TARGET, 5, ANIM_TARGET, 50
	createvisualtask AnimTask_ShakeMon, 5, ANIM_TARGET, 3, 0, 20, 1
	createvisualtask AnimTask_ShakeBattleTerrain, 2, 2, 0, 10, 1
	waitforvisualfinish
	end

Move_SILVER_WIND:
	loadspritegfx ANIM_TAG_SPARKLE_6
	panse SE_M_GUST, SOUND_PAN_ATTACKER, SOUND_PAN_TARGET, +2, 0
	playsewithpan SE_M_MORNING_SUN, 0
	delay 0
	monbg ANIM_DEF_PARTNER
	splitbgprio_all
	delay 0
	createvisualtask AnimTask_BlendBattleAnimPalExclude, 10, ANIM_TARGET, 0, 0, 4, RGB_BLACK
	createvisualtask AnimTask_GetTargetSide, 2
	jumprettrue SilverWindOnPlayer
	fadetobg BG_BUG_OPPONENT
	waitbgfadeout
	createvisualtask AnimTask_StartSlidingBg, 5, 1536, 0, 0, -1
SilverWindContinue:
	delay 0
	createvisualtask AnimTask_BlendBattleAnimPal, 10, F_PAL_BG, 0, 4, 4, RGB_BLACK
	waitbgfadein
	createsprite gSilverWindBigSparkSpriteTemplate, ANIM_TARGET, 66, -32, 16, 0, 6, 2, 3, 1
	createsprite gSilverWindBigSparkSpriteTemplate, ANIM_TARGET, 66, -8, 18, 64, 3, 2, 2, 1
	createsprite gSilverWindBigSparkSpriteTemplate, ANIM_ATTACKER, 120, -24, 18, 90, 5, 1, 2, 1
	createsprite gSilverWindBigSparkSpriteTemplate, ANIM_ATTACKER, 120, -40, 14, 128, 4, 1, 2, 1
	delay 0
	createsprite gSilverWindMediumSparkSpriteTemplate, ANIM_TARGET, 66, -32, 16, 0, 6, 2, 3, 1
	createsprite gSilverWindMediumSparkSpriteTemplate, ANIM_TARGET, 66, -8, 18, 64, 3, 2, 2, 1
	createsprite gSilverWindMediumSparkSpriteTemplate, ANIM_ATTACKER, 120, -24, 18, 90, 5, 1, 2, 1
	createsprite gSilverWindMediumSparkSpriteTemplate, ANIM_ATTACKER, 120, -40, 14, 128, 4, 1, 2, 1
	delay 0
	createsprite gSilverWindSmallSparkSpriteTemplate, ANIM_TARGET, 66, -32, 16, 0, 6, 2, 3, 1
	createsprite gSilverWindSmallSparkSpriteTemplate, ANIM_TARGET, 66, -8, 18, 64, 3, 2, 2, 1
	createsprite gSilverWindSmallSparkSpriteTemplate, ANIM_ATTACKER, 120, -24, 18, 90, 5, 1, 2, 1
	createsprite gSilverWindSmallSparkSpriteTemplate, ANIM_ATTACKER, 120, -40, 14, 128, 4, 1, 2, 1
	delay 6
	createsprite gSilverWindBigSparkSpriteTemplate, ANIM_TARGET, 66, -4, 16, 0, 6, 1, 2, 1
	createsprite gSilverWindBigSparkSpriteTemplate, ANIM_TARGET, 66, -16, 12, 192, 5, 2, 3, 1
	delay 0
	createsprite gSilverWindMediumSparkSpriteTemplate, ANIM_TARGET, 66, -4, 16, 0, 6, 1, 2, 1
	createsprite gSilverWindMediumSparkSpriteTemplate, ANIM_TARGET, 66, -16, 12, 192, 5, 2, 3, 1
	delay 0
	createsprite gSilverWindSmallSparkSpriteTemplate, ANIM_TARGET, 66, -4, 16, 0, 6, 1, 2, 1
	createsprite gSilverWindSmallSparkSpriteTemplate, ANIM_TARGET, 66, -16, 12, 192, 5, 2, 3, 1
	waitforvisualfinish
	playsewithpan SE_M_GUST2, SOUND_PAN_TARGET
	clearmonbg ANIM_DEF_PARTNER
	delay 0
	restorebg
	waitbgfadeout
	createvisualtask AnimTask_BlendBattleAnimPalExclude, 10, ANIM_TARGET, 0, 4, 0, RGB_BLACK
	setarg 7, 0xFFFF
	waitbgfadein
	end

SilverWindOnPlayer:
	fadetobg BG_BUG_PLAYER
	waitbgfadeout
	createvisualtask AnimTask_StartSlidingBg, 5, -1536, 0, 0, -1
	goto SilverWindContinue

Move_SNATCH:
	playsewithpan SE_M_TAKE_DOWN, SOUND_PAN_ATTACKER
	createvisualtask AnimTask_WindUpLunge, 5, ANIM_ATTACKER, -12, 4, 10, 10, 12, 6
	end

Move_DIVE:
	loadspritegfx ANIM_TAG_SPLASH
	loadspritegfx ANIM_TAG_SWEAT_BEAD
	choosetwoturnanim DiveSetUp, DiveAttack

DiveSetUp:
	loadspritegfx ANIM_TAG_ROUND_SHADOW
	playsewithpan SE_M_HEADBUTT, SOUND_PAN_ATTACKER
	createsprite gDiveBallSpriteTemplate, ANIM_ATTACKER, 2, 0, 0, 13, 336
	waitforvisualfinish
	playsewithpan SE_M_DIVE, SOUND_PAN_ATTACKER
	createsprite gDiveWaterSplashSpriteTemplate, ANIM_ATTACKER, 3, 0
	call DiveSetUpWaterDroplets
	call DiveSetUpWaterDroplets
	call DiveSetUpWaterDroplets
	call DiveSetUpWaterDroplets
	call DiveSetUpWaterDroplets
	end

DiveSetUpWaterDroplets:
	createsprite gSprayWaterDropletSpriteTemplate, ANIM_ATTACKER, 5, 0, 0
	createsprite gSprayWaterDropletSpriteTemplate, ANIM_ATTACKER, 5, 1, 0
	return

DiveAttack:
	loadspritegfx ANIM_TAG_WATER_IMPACT
	loadspritegfx ANIM_TAG_SMALL_BUBBLES
	monbg ANIM_DEF_PARTNER
	setalpha 12, 8
	playsewithpan SE_M_EXPLOSION, SOUND_PAN_TARGET
	createsprite gDiveWaterSplashSpriteTemplate, ANIM_TARGET, 3, 1
	call DiveAttackWaterDroplets
	call DiveAttackWaterDroplets
	call DiveAttackWaterDroplets
	call DiveAttackWaterDroplets
	call DiveAttackWaterDroplets
	delay 12
	call RisingWaterHitEffect
	waitforvisualfinish
	visible ANIM_ATTACKER
	clearmonbg ANIM_DEF_PARTNER
	blendoff
	end

DiveAttackWaterDroplets:
	createsprite gSprayWaterDropletSpriteTemplate, ANIM_TARGET, 5, 0, 1
	createsprite gSprayWaterDropletSpriteTemplate, ANIM_TARGET, 5, 1, 1
	return

Move_ROCK_BLAST:
	loadspritegfx ANIM_TAG_ROCKS
	loadspritegfx ANIM_TAG_IMPACT
	createsprite gHorizontalLungeSpriteTemplate, ANIM_ATTACKER, 2, 4, 6
	delay 3
	playsewithpan SE_M_SWAGGER, SOUND_PAN_ATTACKER
	createsprite gRockBlastRockSpriteTemplate, ANIM_TARGET, 2, 16, 0, 0, 0, 25, 257
	waitforvisualfinish
	createsprite gBasicHitSplatSpriteTemplate, ANIM_TARGET, 3, 0, 0, ANIM_TARGET, 1
	playsewithpan SE_M_ROCK_THROW, SOUND_PAN_TARGET
	createsprite gRockFragmentSpriteTemplate, ANIM_TARGET, 2, 0, 0, 20, 24, 14, 2
	createvisualtask AnimTask_ShakeMon, 2, ANIM_TARGET, 3, 0, 5, 1
	createsprite gRockFragmentSpriteTemplate, ANIM_TARGET, 2, 5, 0, -20, 24, 14, 1
	createsprite gRockFragmentSpriteTemplate, ANIM_TARGET, 2, 0, 5, 20, -24, 14, 2
	createsprite gRockFragmentSpriteTemplate, ANIM_TARGET, 2, -5, 0, -20, -24, 14, 2
	waitforvisualfinish
	end

Move_OVERHEAT:
	loadspritegfx ANIM_TAG_SMALL_EMBER
	loadspritegfx ANIM_TAG_IMPACT
	monbg ANIM_DEF_PARTNER
	setalpha 12, 18
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG, 1, 0, 5, RGB(28, 0, 0)
	waitforvisualfinish
	createvisualtask AnimTask_AllocBackupPalBuffer, 5
	waitforvisualfinish
	createvisualtask AnimTask_CopyPalUnfadedToBackup, 5, 0, 1
	delay 1
	createvisualtask AnimTask_CopyPalFadedToUnfaded, 5, 0
	delay 1
	playsewithpan SE_M_DRAGON_RAGE, SOUND_PAN_ATTACKER
	createvisualtask AnimTask_CopyPalUnfadedToBackup, 5, 1, 0
	delay 1
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_ATTACKER, 1, 0, 13, RGB(28, 0, 0)
	createvisualtask AnimTask_ShakeMon, 5, ANIM_ATTACKER, 2, 0, 15, 1
	waitforvisualfinish
	playsewithpan SE_M_FLAME_WHEEL2, SOUND_PAN_ATTACKER
	createsprite gOverheatFlameSpriteTemplate, ANIM_ATTACKER, 2, 1, 0, 30, 25, -20
	createsprite gOverheatFlameSpriteTemplate, ANIM_ATTACKER, 2, 1, 32, 30, 25, -20
	createsprite gOverheatFlameSpriteTemplate, ANIM_ATTACKER, 2, 1, 64, 30, 25, -20
	createsprite gOverheatFlameSpriteTemplate, ANIM_ATTACKER, 2, 1, 96, 30, 25, -20
	createsprite gOverheatFlameSpriteTemplate, ANIM_ATTACKER, 2, 1, 128, 30, 25, -20
	createsprite gOverheatFlameSpriteTemplate, ANIM_ATTACKER, 66, 1, 160, 30, 25, -20
	createsprite gOverheatFlameSpriteTemplate, ANIM_ATTACKER, 66, 1, 192, 30, 25, -20
	createsprite gOverheatFlameSpriteTemplate, ANIM_ATTACKER, 66, 1, 224, 30, 25, -20
	delay 5
	createsprite gOverheatFlameSpriteTemplate, ANIM_ATTACKER, 2, 1, 0, 30, 25, 0
	createsprite gOverheatFlameSpriteTemplate, ANIM_ATTACKER, 2, 1, 32, 30, 25, 0
	createsprite gOverheatFlameSpriteTemplate, ANIM_ATTACKER, 2, 1, 64, 30, 25, 0
	createsprite gOverheatFlameSpriteTemplate, ANIM_ATTACKER, 2, 1, 96, 30, 25, 0
	createsprite gOverheatFlameSpriteTemplate, ANIM_ATTACKER, 2, 1, 128, 30, 25, 0
	createsprite gOverheatFlameSpriteTemplate, ANIM_ATTACKER, 66, 1, 160, 30, 25, 0
	createsprite gOverheatFlameSpriteTemplate, ANIM_ATTACKER, 66, 1, 192, 30, 25, 0
	createsprite gOverheatFlameSpriteTemplate, ANIM_ATTACKER, 66, 1, 224, 30, 25, 0
	delay 5
	createsprite gOverheatFlameSpriteTemplate, ANIM_ATTACKER, 2, 1, 0, 30, 25, 10
	createsprite gOverheatFlameSpriteTemplate, ANIM_ATTACKER, 2, 1, 32, 30, 25, 10
	createsprite gOverheatFlameSpriteTemplate, ANIM_ATTACKER, 2, 1, 64, 30, 25, 10
	createsprite gOverheatFlameSpriteTemplate, ANIM_ATTACKER, 2, 1, 96, 30, 25, 10
	createsprite gOverheatFlameSpriteTemplate, ANIM_ATTACKER, 2, 1, 128, 30, 25, 10
	createsprite gOverheatFlameSpriteTemplate, ANIM_ATTACKER, 66, 1, 160, 30, 25, 10
	createsprite gOverheatFlameSpriteTemplate, ANIM_ATTACKER, 66, 1, 192, 30, 25, 10
	createsprite gOverheatFlameSpriteTemplate, ANIM_ATTACKER, 66, 1, 224, 30, 25, 10
	delay 5
	waitforvisualfinish
	createsprite gBasicHitSplatSpriteTemplate, ANIM_TARGET, 3, -5, 3, ANIM_TARGET, 0
	playsewithpan SE_M_FIRE_PUNCH, SOUND_PAN_TARGET
	createvisualtask AnimTask_ShakeMon, 2, ANIM_TARGET, 10, 0, 25, 1
	delay 6
	createsprite gBasicHitSplatSpriteTemplate, ANIM_TARGET, 3, 8, -5, ANIM_TARGET, 0
	playsewithpan SE_M_FIRE_PUNCH, SOUND_PAN_TARGET
	delay 8
	createsprite gBasicHitSplatSpriteTemplate, ANIM_TARGET, 3, 10, 10, ANIM_TARGET, 0
	playsewithpan SE_M_FIRE_PUNCH, SOUND_PAN_TARGET
	delay 8
	createsprite gBasicHitSplatSpriteTemplate, ANIM_TARGET, 3, 0, 0, ANIM_TARGET, 0
	playsewithpan SE_M_FIRE_PUNCH, SOUND_PAN_TARGET
	createvisualtask AnimTask_CopyPalFadedToUnfaded, 5, 1
	delay 1
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_ATTACKER, -1, 0, 13, RGB(18, 18, 18)
	createvisualtask AnimTask_ShakeMon, 5, ANIM_ATTACKER, 3, 0, 15, 1
	waitforvisualfinish
	createvisualtask AnimTask_CopyPalUnfadedFromBackup, 5, 0, 1
	delay 1
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG, 1, 5, 0, RGB(28, 0, 0)
	waitforvisualfinish
	clearmonbg ANIM_DEF_PARTNER
	blendoff
	waitforvisualfinish
	delay 15
	createvisualtask AnimTask_CopyPalUnfadedFromBackup, 5, 1, 0
	delay 1
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_ATTACKER, 0, 13, 0, RGB(18, 18, 18)
	waitforvisualfinish
	createvisualtask AnimTask_FreeBackupPalBuffer, 5
	waitforvisualfinish
	end

Move_HYDRO_CANNON:
	loadspritegfx ANIM_TAG_WATER_ORB
	loadspritegfx ANIM_TAG_WATER_IMPACT
	monbg ANIM_DEF_PARTNER
	setalpha 12, 8
	playsewithpan SE_M_SURF, SOUND_PAN_ATTACKER
	createsprite gHydroCannonChargeSpriteTemplate, ANIM_TARGET, 2
	delay 10
	createvisualtask AnimTask_InvertScreenColor, 2, 257, 257, 257
	delay 30
	panse SE_M_HYDRO_PUMP, SOUND_PAN_ATTACKER, SOUND_PAN_TARGET, +2, 0
	call HydroCannonBeam
	createvisualtask AnimTask_ShakeMon, 5, ANIM_TARGET, 10, 0, 40, 1
	createsprite gWaterHitSplatSpriteTemplate, ANIM_TARGET, 2, 0, 0, ANIM_TARGET, 0
	call HydroCannonBeam
	createsprite gWaterHitSplatSpriteTemplate, ANIM_TARGET, 2, 0, 0, ANIM_TARGET, 0
	call HydroCannonBeam
	createsprite gWaterHitSplatSpriteTemplate, ANIM_TARGET, 2, 0, 0, ANIM_TARGET, 0
	call HydroCannonBeam
	createsprite gWaterHitSplatSpriteTemplate, ANIM_TARGET, 2, 0, 0, ANIM_TARGET, 0
	call HydroCannonBeam
	createsprite gWaterHitSplatSpriteTemplate, ANIM_TARGET, 2, 0, 0, ANIM_TARGET, 0
	call HydroCannonBeam
	createsprite gWaterHitSplatSpriteTemplate, ANIM_TARGET, 2, 0, 0, ANIM_TARGET, 0
	waitforvisualfinish
	createvisualtask AnimTask_InvertScreenColor, 2, 257, 257, 257
	waitforvisualfinish
	clearmonbg ANIM_DEF_PARTNER
	blendoff
	end

HydroCannonBeam:
	createsprite gHydroCannonBeamSpriteTemplate, ANIM_TARGET, 2, 10, -10, 0, 0, 15, 257
	delay 1
	createsprite gHydroCannonBeamSpriteTemplate, ANIM_TARGET, 2, 10, -10, 0, 0, 15, 257
	delay 1
	createsprite gHydroCannonBeamSpriteTemplate, ANIM_TARGET, 2, 10, -10, 0, 0, 15, 257
	delay 1
	createsprite gHydroCannonBeamSpriteTemplate, ANIM_TARGET, 2, 10, -10, 0, 0, 15, 257
	delay 1
	createsprite gHydroCannonBeamSpriteTemplate, ANIM_TARGET, 2, 10, -10, 0, 0, 15, 257
	return

Move_ASTONISH:
	loadspritegfx ANIM_TAG_SWEAT_BEAD
	playsewithpan SE_M_ENCORE, SOUND_PAN_ATTACKER
	createsprite gHorizontalLungeSpriteTemplate, ANIM_ATTACKER, 2, 4, 6
	delay 25
	createsprite gSprayWaterDropletSpriteTemplate, ANIM_TARGET, 5, 0, 1
	playsewithpan SE_M_SKETCH, SOUND_PAN_TARGET
	createsprite gSprayWaterDropletSpriteTemplate, ANIM_TARGET, 5, 1, 1
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_TARGET, 4, 0, 5, 1
	createvisualtask AnimTask_StretchTargetUp, 3
	waitforvisualfinish
	end

Move_SEISMIC_TOSS:
	loadspritegfx ANIM_TAG_IMPACT
	loadspritegfx ANIM_TAG_ROCKS
	setarg 7, 0
	monbg ANIM_DEF_PARTNER
	setalpha 12, 8
	waitforvisualfinish
	createvisualtask AnimTask_GetSeismicTossDamageLevel, 3
	delay 1
	fadetobg BG_IN_AIR
	waitbgfadeout
	createvisualtask AnimTask_MoveSeismicTossBg, 3
	playsewithpan SE_M_SKY_UPPERCUT, 0
	waitbgfadein
	waitforvisualfinish
	createvisualtask AnimTask_SeismicTossBgAccelerateDownAtEnd, 3
	jumpreteq 0, SeismicTossWeak
	jumpreteq 1, SeismicTossMedium
	jumpreteq 2, SeismicTossStrong
SeismicTossContinue:
	restorebg
	waitbgfadeout
	setarg 7, 0xFFF
	waitbgfadein
	clearmonbg ANIM_DEF_PARTNER
	blendoff
	end

SeismicTossWeak:
	call SeismicTossRockScatter1
	delay 16
	call SeismicTossRockScatter2
	goto SeismicTossContinue

SeismicTossMedium:
	call SeismicTossRockScatter1
	delay 14
	call SeismicTossRockScatter2
	delay 14
	call SeismicTossRockScatter1
	goto SeismicTossContinue

SeismicTossStrong:
	call SeismicTossRockScatter2
	delay 10
	call SeismicTossRockScatter1
	delay 10
	call SeismicTossRockScatter2
	delay 10
	call SeismicTossRockScatter1
	goto SeismicTossContinue

SeismicTossRockScatter1:
	createsprite gBasicHitSplatSpriteTemplate, ANIM_TARGET, 3, -10, -8, ANIM_TARGET, 1
	playsewithpan SE_M_STRENGTH, SOUND_PAN_TARGET
	createvisualtask AnimTask_ShakeMon, 2, ANIM_TARGET, 0, 3, 5, 1
	createsprite gRockScatterSpriteTemplate, ANIM_TARGET, 2, -12, 27, 2, 3
	createsprite gRockScatterSpriteTemplate, ANIM_TARGET, 2, 8, 28, 3, 4
	createsprite gRockScatterSpriteTemplate, ANIM_TARGET, 2, -4, 30, 2, 3
	createsprite gRockScatterSpriteTemplate, ANIM_TARGET, 2, 12, 25, 4, 4
	return

SeismicTossRockScatter2:
	createsprite gBasicHitSplatSpriteTemplate, ANIM_TARGET, 3, 10, -8, ANIM_TARGET, 1
	playsewithpan SE_M_ROCK_THROW, SOUND_PAN_TARGET
	createvisualtask AnimTask_ShakeMon, 2, ANIM_TARGET, 0, 3, 5, 1
	createsprite gRockScatterSpriteTemplate, ANIM_TARGET, 2, -12, 32, 3, 4
	createsprite gRockScatterSpriteTemplate, ANIM_TARGET, 2, 8, 31, 2, 2
	createsprite gRockScatterSpriteTemplate, ANIM_TARGET, 2, -4, 28, 2, 3
	createsprite gRockScatterSpriteTemplate, ANIM_TARGET, 2, 12, 30, 4, 3
	return

Move_MAGIC_COAT:
	loadspritegfx ANIM_TAG_ORANGE_LIGHT_WALL
	setalpha 0, 16
	waitplaysewithpan SE_M_BARRIER, SOUND_PAN_ATTACKER, 15
	createsprite gMagicCoatWallSpriteTemplate, ANIM_ATTACKER, 3, 40, 0, ANIM_TAG_ORANGE_LIGHT_WALL
	waitforvisualfinish
	delay 1
	blendoff
	end

Move_WATER_PULSE:
	loadspritegfx ANIM_TAG_SMALL_BUBBLES
	loadspritegfx ANIM_TAG_BLUE_RING_2
	monbg ANIM_TARGET
	splitbgprio ANIM_TARGET
	playsewithpan SE_M_BUBBLE3, SOUND_PAN_ATTACKER
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG, 0, 0, 7, RGB(0, 25, 28)
	delay 10
	createsprite gWaterPulseBubbleSpriteTemplate, ANIM_ATTACKER, 66, 100, 100, 8, 1, 20, 40, 0
	createsprite gWaterPulseBubbleSpriteTemplate, ANIM_ATTACKER, 66, 20, 100, 16, 2, 10, 35, 1
	createsprite gWaterPulseBubbleSpriteTemplate, ANIM_ATTACKER, 66, 200, 80, 8, 1, 40, 20, 0
	createsprite gWaterPulseBubbleSpriteTemplate, ANIM_ATTACKER, 66, 80, 60, 10, 3, 20, 50, 0
	createsprite gWaterPulseBubbleSpriteTemplate, ANIM_ATTACKER, 66, 140, 100, 16, 1, 20, 30, 1
	playsewithpan SE_M_BUBBLE3, SOUND_PAN_TARGET
	waitforvisualfinish
	playsewithpan SE_M_GIGA_DRAIN, SOUND_PAN_ATTACKER
	createsprite gWaterPulseRingSpriteTemplate, ANIM_TARGET, 2, 0, 0, 40, 15
	delay 5
	playsewithpan SE_M_GIGA_DRAIN, SOUND_PAN_ATTACKER
	createsprite gWaterPulseRingSpriteTemplate, ANIM_TARGET, 2, 0, 0, 40, 15
	delay 5
	playsewithpan SE_M_GIGA_DRAIN, SOUND_PAN_ATTACKER
	createsprite gWaterPulseRingSpriteTemplate, ANIM_TARGET, 2, 0, 0, 40, 15
	delay 13
	createvisualtask AnimTask_ShakeMon, 2, ANIM_TARGET, 0, 8, 18, 1
	waitforvisualfinish
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG, 1, 7, 0, RGB(0, 25, 28)
	waitforvisualfinish
	clearmonbg ANIM_DEF_PARTNER
	end

Move_PSYCHO_BOOST:
	loadspritegfx ANIM_TAG_CIRCLE_OF_LIGHT
	monbg ANIM_ATK_PARTNER
	fadetobg BG_PSYCHIC
	waitbgfadeout
	createvisualtask AnimTask_FadeScreenToWhite, 5
	waitbgfadein
	delay 6
	createvisualtask AnimTask_BlendColorCycle, 2, F_PAL_BG, 2, 8, 0, 10, RGB_BLACK
	delay 0
	splitbgprio ANIM_ATTACKER
	setalpha 8, 8
	delay 10
	createvisualtask AnimTask_ShakeMon, 2, ANIM_ATTACKER, 3, 0, 240, 0
	loopsewithpan SE_M_PSYBEAM2, SOUND_PAN_ATTACKER, 14, 10
	createsprite gPsychoBoostOrbSpriteTemplate, ANIM_ATTACKER, 2
	delay 110
	loopsewithpan SE_M_PSYBEAM2, SOUND_PAN_ATTACKER, 7, 10
	waitforvisualfinish
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_TARGET, -8, 1, 24, 1
	playsewithpan SE_M_LEER, SOUND_PAN_TARGET
	waitforvisualfinish
	clearmonbg ANIM_ATK_PARTNER
	blendoff
	call UnsetPsychicBackground
	end

Move_KNOCK_OFF:
	loadspritegfx ANIM_TAG_SLAM_HIT_2
	loadspritegfx ANIM_TAG_IMPACT
	createsprite gHorizontalLungeSpriteTemplate, ANIM_ATTACKER, 2, 4, 6
	delay 4
	playsewithpan SE_M_VITAL_THROW, SOUND_PAN_TARGET
	createsprite gKnockOffStrikeSpriteTemplate, ANIM_TARGET, 2, -16, -16
	delay 8
	createsprite gComplexPaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG | F_PAL_BATTLERS, 5, 1, RGB_WHITE, 10, RGB_BLACK, 0
	createsprite gBasicHitSplatSpriteTemplate, ANIM_TARGET, 3, 0, 0, ANIM_TARGET, 2
	playsewithpan SE_M_COMET_PUNCH, SOUND_PAN_TARGET
	createsprite gSlideMonToOffsetSpriteTemplate, ANIM_ATTACKER, 2, 1, -12, 10, 0, 3
	createsprite gSlideMonToOriginalPosSpriteTemplate, ANIM_ATTACKER, 2, 0, 0, 5
	delay 3
	createvisualtask AnimTask_ShakeMonInPlace, 2, ANIM_TARGET, 0, 3, 6, 1
	delay 5
	createsprite gSlideMonToOriginalPosSpriteTemplate, ANIM_ATTACKER, 2, 1, 0, 6
	delay 10
	waitforvisualfinish
	end

Move_DOOM_DESIRE:
	createvisualtask GetIsDoomDesireHitTurn, 2
	delay 1
	monbg ANIM_ATK_PARTNER
	createvisualtask AnimTask_SetGrayscaleOrOriginalPal, 5, ANIM_TARGET, FALSE
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG, 1, 0, 4, RGB_BLACK
	waitforvisualfinish
	setalpha 8, 8
	playsewithpan SE_M_PSYBEAM, SOUND_PAN_ATTACKER
	createvisualtask AnimTask_ScaleMonAndRestore, 5, -4, -4, 15, ANIM_ATTACKER, 1
	waitforvisualfinish
	delay 20
	createvisualtask AnimTask_SetGrayscaleOrOriginalPal, 5, ANIM_TARGET, TRUE
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG, 1, 4, 0, RGB_BLACK
	waitforvisualfinish
	clearmonbg ANIM_ATK_PARTNER
	blendoff
	end

UnusedDoomDesireHit:
	loadspritegfx ANIM_TAG_EXPLOSION
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG, 3, 0, 16, RGB_WHITE
	waitforvisualfinish
	delay 10
	createvisualtask AnimTask_DoomDesireLightBeam, 5
	delay 5
	playsewithpan SE_M_CONFUSE_RAY, SOUND_PAN_ATTACKER
	delay 10
	playsewithpan SE_M_CONFUSE_RAY, 0
	delay 10
	playsewithpan SE_M_CONFUSE_RAY, SOUND_PAN_TARGET
	delay 23
	createvisualtask AnimTask_ShakeMonInPlace, 2, ANIM_TARGET, 10, 0, 20, 1
	playsewithpan SE_M_SELF_DESTRUCT, SOUND_PAN_TARGET
	createsprite gExplosionSpriteTemplate, ANIM_ATTACKER, 3, 0, 0, 1, 1
	delay 6
	playsewithpan SE_M_SELF_DESTRUCT, SOUND_PAN_TARGET
	createsprite gExplosionSpriteTemplate, ANIM_ATTACKER, 3, 24, -24, 1, 1
	delay 6
	playsewithpan SE_M_SELF_DESTRUCT, SOUND_PAN_TARGET
	createsprite gExplosionSpriteTemplate, ANIM_ATTACKER, 3, -16, 16, 1, 1
	delay 6
	playsewithpan SE_M_SELF_DESTRUCT, SOUND_PAN_TARGET
	createsprite gExplosionSpriteTemplate, ANIM_ATTACKER, 3, -24, -12, 1, 1
	delay 6
	playsewithpan SE_M_SELF_DESTRUCT, SOUND_PAN_TARGET
	createsprite gExplosionSpriteTemplate, ANIM_ATTACKER, 3, 16, 16, 1, 1
	waitforvisualfinish
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG, 3, 16, 0, RGB_WHITE
	waitforvisualfinish
	end

Move_SKY_UPPERCUT:
	loadspritegfx ANIM_TAG_IMPACT
	monbg ANIM_DEF_PARTNER
	splitbgprio ANIM_TARGET
	fadetobg BG_IN_AIR
	waitbgfadeout
	playsewithpan SE_M_SKY_UPPERCUT, SOUND_PAN_ATTACKER
	createvisualtask AnimTask_MoveSkyUppercutBg, 5, 55
	waitbgfadein
	setalpha 12, 8
	delay 38
	createsprite gSlideMonToOffsetSpriteTemplate, ANIM_ATTACKER, 2, 0, 28, 0, 0, 5
	delay 4
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_TARGET, 4, 0, 6, 1
	playsewithpan SE_M_VITAL_THROW2, SOUND_PAN_TARGET
	createsprite gBasicHitSplatSpriteTemplate, ANIM_TARGET, 3, -28, 28, ANIM_TARGET, 1
	delay 1
	playsewithpan SE_M_VITAL_THROW2, SOUND_PAN_TARGET
	createsprite gBasicHitSplatSpriteTemplate, ANIM_TARGET, 3, -15, 8, ANIM_TARGET, 1
	playsewithpan SE_M_VITAL_THROW2, SOUND_PAN_TARGET
	delay 1
	playsewithpan SE_M_VITAL_THROW2, SOUND_PAN_TARGET
	createsprite gBasicHitSplatSpriteTemplate, ANIM_TARGET, 3, -5, -12, ANIM_TARGET, 1
	delay 1
	playsewithpan SE_M_VITAL_THROW2, SOUND_PAN_TARGET
	createsprite gBasicHitSplatSpriteTemplate, ANIM_TARGET, 3, 0, -32, ANIM_TARGET, 1
	delay 1
	playsewithpan SE_M_VITAL_THROW2, SOUND_PAN_TARGET
	createsprite gBasicHitSplatSpriteTemplate, ANIM_TARGET, 3, 5, -52, ANIM_TARGET, 1
	createsprite gSlideMonToOffsetSpriteTemplate, ANIM_ATTACKER, 2, 1, -26, 16, 1, 4
	delay 4
	createvisualtask AnimTask_ShakeMonInPlace, 2, ANIM_TARGET, 0, 3, 6, 1
	delay 30
	createsprite gSlideMonToOriginalPosSpriteTemplate, ANIM_ATTACKER, 2, 0, 0, 6
	delay 4
	createsprite gSlideMonToOriginalPosSpriteTemplate, ANIM_ATTACKER, 2, 1, 0, 6
	clearmonbg ANIM_DEF_PARTNER
	blendoff
	restorebg
	waitbgfadeout
	setarg 7, 0xFFFF
	waitbgfadein
	end

Move_SECRET_POWER:
	createvisualtask AnimTask_GetBattleTerrain, 5
	jumpargeq 0, BATTLE_TERRAIN_GRASS,      Move_NEEDLE_ARM
	jumpargeq 0, BATTLE_TERRAIN_LONG_GRASS, Move_MAGICAL_LEAF
	jumpargeq 0, BATTLE_TERRAIN_SAND,       Move_MUD_SHOT
	jumpargeq 0, BATTLE_TERRAIN_UNDERWATER, Move_WATERFALL
	jumpargeq 0, BATTLE_TERRAIN_WATER,      Move_SURF
	jumpargeq 0, BATTLE_TERRAIN_POND,       Move_BUBBLE_BEAM
	jumpargeq 0, BATTLE_TERRAIN_MOUNTAIN,   Move_ROCK_THROW
	jumpargeq 0, BATTLE_TERRAIN_CAVE,       Move_BITE
	jumpargeq 0, BATTLE_TERRAIN_BUILDING,   Move_STRENGTH
	goto Move_SLAM

Move_TWISTER:
	loadspritegfx ANIM_TAG_LEAF
	loadspritegfx ANIM_TAG_IMPACT
	loadspritegfx ANIM_TAG_ROCKS
	monbg ANIM_DEF_PARTNER
	splitbgprio ANIM_TARGET
	playsewithpan SE_M_TWISTER, SOUND_PAN_TARGET
	createsprite gTwisterLeafSpriteTemplate, ANIM_TARGET, 2, 120, 70, 5, 70, 30
	delay 1
	createsprite gTwisterLeafSpriteTemplate, ANIM_TARGET, 2, 115, 55, 6, 60, 25
	delay 1
	createsprite gTwisterLeafSpriteTemplate, ANIM_TARGET, 2, 115, 60, 7, 60, 30
	createsprite gTwisterLeafSpriteTemplate, ANIM_TARGET, 2, 115, 55, 10, 60, 30
	delay 3
	createsprite gTwisterRockSpriteTemplate, ANIM_TARGET, 2, 100, 50, 4, 50, 26
	delay 1
	createsprite gTwisterLeafSpriteTemplate, ANIM_TARGET, 2, 105, 25, 8, 60, 20
	delay 1
	createsprite gTwisterLeafSpriteTemplate, ANIM_TARGET, 2, 115, 40, 10, 48, 30
	delay 3
	createsprite gTwisterRockSpriteTemplate, ANIM_TARGET, 2, 120, 30, 6, 45, 25
	createsprite gTwisterLeafSpriteTemplate, ANIM_TARGET, 2, 115, 35, 10, 60, 30
	delay 3
	createsprite gTwisterRockSpriteTemplate, ANIM_TARGET, 2, 105, 20, 8, 40, 0
	delay 3
	createsprite gTwisterLeafSpriteTemplate, ANIM_TARGET, 2, 20, 255, 15, 32, 0
	createsprite gTwisterLeafSpriteTemplate, ANIM_TARGET, 2, 110, 10, 8, 32, 20
	waitforvisualfinish
	createsprite gBasicHitSplatSpriteTemplate, ANIM_TARGET, 3, -32, -16, ANIM_TARGET, 3
	playsewithpan SE_M_COMET_PUNCH, SOUND_PAN_TARGET
	createvisualtask AnimTask_ShakeMonInPlace, 2, ANIM_TARGET, 3, 0, 12, 1
	createvisualtask AnimTask_ShakeMonInPlace, 2, ANIM_DEF_PARTNER, 3, 0, 12, 1
	delay 4
	createsprite gRandomPosHitSplatSpriteTemplate, ANIM_TARGET, 3, 1, 3
	playsewithpan SE_M_COMET_PUNCH, SOUND_PAN_TARGET
	delay 4
	createsprite gRandomPosHitSplatSpriteTemplate, ANIM_TARGET, 3, 1, 3
	playsewithpan SE_M_COMET_PUNCH, SOUND_PAN_TARGET
	delay 4
	createsprite gBasicHitSplatSpriteTemplate, ANIM_TARGET, 3, 32, 20, ANIM_TARGET, 3
	playsewithpan SE_M_COMET_PUNCH, SOUND_PAN_TARGET
	waitforvisualfinish
	clearmonbg ANIM_DEF_PARTNER
	blendoff
	end

Move_MAGICAL_LEAF:
	loadspritegfx ANIM_TAG_LEAF
	loadspritegfx ANIM_TAG_RAZOR_LEAF
	loadspritegfx ANIM_TAG_IMPACT
	monbg ANIM_DEF_PARTNER
	setalpha 12, 8
	delay 1
	loopsewithpan SE_M_POISON_POWDER, SOUND_PAN_ATTACKER, 10, 5
	createvisualtask AnimTask_CycleMagicalLeafPal, 5
	createsprite gRazorLeafParticleSpriteTemplate, ANIM_ATTACKER, 2, -3, -2, 10
	delay 2
	createsprite gRazorLeafParticleSpriteTemplate, ANIM_ATTACKER, 2, -1, -1, 15
	delay 2
	createsprite gRazorLeafParticleSpriteTemplate, ANIM_ATTACKER, 2, -4, -4, 7
	delay 2
	createsprite gRazorLeafParticleSpriteTemplate, ANIM_ATTACKER, 2, 3, -3, 11
	delay 2
	createsprite gRazorLeafParticleSpriteTemplate, ANIM_ATTACKER, 2, -1, -6, 8
	delay 2
	createsprite gRazorLeafParticleSpriteTemplate, ANIM_ATTACKER, 2, 2, -1, 12
	delay 2
	createsprite gRazorLeafParticleSpriteTemplate, ANIM_ATTACKER, 2, -3, -4, 13
	delay 2
	createsprite gRazorLeafParticleSpriteTemplate, ANIM_ATTACKER, 2, 4, -5, 7
	delay 2
	createsprite gRazorLeafParticleSpriteTemplate, ANIM_ATTACKER, 2, 2, -6, 11
	delay 2
	createsprite gRazorLeafParticleSpriteTemplate, ANIM_ATTACKER, 2, -3, -5, 8
	delay 60
	playsewithpan SE_M_RAZOR_WIND2, SOUND_PAN_ATTACKER
	createsprite gRazorLeafCutterSpriteTemplate, ANIM_TARGET, 3, 20, -10, 20, 0, 32, 20, 0
	createsprite gRazorLeafCutterSpriteTemplate, ANIM_TARGET, 3, 20, -10, 20, 0, 32, -20, 0
	delay 30
	playsewithpan SE_M_RAZOR_WIND, SOUND_PAN_TARGET
	createsprite gBasicHitSplatSpriteTemplate, ANIM_TARGET, 4, -10, -4, ANIM_TARGET, 2
	createsprite gBasicHitSplatSpriteTemplate, ANIM_TARGET, 4, 10, 4, ANIM_TARGET, 2
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_TARGET, 2, 0, 8, 1
	delay 20
	setarg 7, 0xFFFF
	waitforvisualfinish
	clearmonbg ANIM_DEF_PARTNER
	blendoff
	end

Move_ICE_BALL:
	loadspritegfx ANIM_TAG_ICE_CHUNK
	loadspritegfx ANIM_TAG_ICE_CRYSTALS
	createvisualtask AnimTask_GetRolloutCounter, 5, 0
	jumpargeq 0, 4, IceBallSetIceBg
IceBallContinue:
	playsewithpan SE_M_ICY_WIND, SOUND_PAN_ATTACKER
	createsprite gIceBallChunkSpriteTemplate, ANIM_TARGET, 2, 15, 0, -12, -16, 30, -40
	delay 28
	playsewithpan SE_M_BRICK_BREAK, SOUND_PAN_TARGET
	createvisualtask AnimTask_GetRolloutCounter, 5, 0
	jumpargeq 0, 0, IceBallWeakest
	jumpargeq 0, 1, IceBallWeak
	jumpargeq 0, 2, IceBallMediun
	jumpargeq 0, 3, IceBallStrong
	jumpargeq 0, 4, IceBallStrongest
IceBallContinue2:
	createvisualtask AnimTask_GetRolloutCounter, 5, 0
	jumpargeq 0, 4, IceBallUnsetIceBg
IceBallEnd:
	end

IceBallSetIceBg:
	fadetobg BG_ICE
	goto IceBallContinue

IceBallUnsetIceBg:
	waitbgfadein
	delay 45
	restorebg
	waitbgfadein
	goto IceBallEnd

IceBallWeakest:
	createvisualtask AnimTask_ShakeTargetBasedOnMovePowerOrDmg, 2, FALSE, 1, 8, 1, 0
	call IceBallImpactShard
	call IceBallImpactShard
	call IceBallImpactShard
	call IceBallImpactShard
	call IceBallImpactShard
	goto IceBallContinue2

IceBallWeak:
	createvisualtask AnimTask_ShakeTargetBasedOnMovePowerOrDmg, 2, FALSE, 1, 10, 1, 0
	call IceBallImpactShard
	call IceBallImpactShard
	call IceBallImpactShard
	call IceBallImpactShard
	call IceBallImpactShard
	call IceBallImpactShard
	call IceBallImpactShard
	goto IceBallContinue2

IceBallMediun:
	createvisualtask AnimTask_ShakeTargetBasedOnMovePowerOrDmg, 2, FALSE, 1, 14, 1, 0
	call IceBallImpactShard
	call IceBallImpactShard
	call IceBallImpactShard
	call IceBallImpactShard
	call IceBallImpactShard
	call IceBallImpactShard
	call IceBallImpactShard
	call IceBallImpactShard
	call IceBallImpactShard
	goto IceBallContinue2

IceBallStrong:
	createvisualtask AnimTask_ShakeTargetBasedOnMovePowerOrDmg, 2, FALSE, 1, 18, 1, 0
	call IceBallImpactShard
	call IceBallImpactShard
	call IceBallImpactShard
	call IceBallImpactShard
	call IceBallImpactShard
	call IceBallImpactShard
	call IceBallImpactShard
	call IceBallImpactShard
	call IceBallImpactShard
	call IceBallImpactShard
	goto IceBallContinue2

IceBallStrongest:
	createvisualtask AnimTask_ShakeTargetBasedOnMovePowerOrDmg, 2, FALSE, 1, 30, 1, 0
	call IceBallImpactShard
	call IceBallImpactShard
	call IceBallImpactShard
	call IceBallImpactShard
	call IceBallImpactShard
	call IceBallImpactShard
	call IceBallImpactShard
	call IceBallImpactShard
	call IceBallImpactShard
	call IceBallImpactShard
	goto IceBallContinue2

IceBallImpactShard:
	createsprite gIceBallImpactShardSpriteTemplate, ANIM_TARGET, 4, -12, -16
	return

Move_WEATHER_BALL:
	loadspritegfx ANIM_TAG_WEATHER_BALL
	createsprite gVerticalDipSpriteTemplate, ANIM_ATTACKER, 2, 8, 1, ANIM_ATTACKER
	delay 8
	playsewithpan SE_M_SWAGGER, SOUND_PAN_ATTACKER
	createsprite gWeatherBallUpSpriteTemplate, ANIM_ATTACKER, 2
	waitforvisualfinish
	delay 15
	playsewithpan SE_M_DETECT, 0
	createsprite gComplexPaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG | F_PAL_BATTLERS, 5, 1, RGB_WHITE, 10, RGB_BLACK, 0
	waitforvisualfinish
	createvisualtask AnimTask_GetWeather, 2
	delay 1
	jumpreteq ANIM_WEATHER_NONE, WeatherBallNormal
	jumpreteq ANIM_WEATHER_SUN, WeatherBallFire
	jumpreteq ANIM_WEATHER_RAIN, WeatherBallWater
	jumpreteq ANIM_WEATHER_SANDSTORM, WeatherBallSandstorm
	jumpreteq ANIM_WEATHER_HAIL, WeatherBallIce
WeatherBallNormal:
	loadspritegfx ANIM_TAG_IMPACT
	createsprite gWeatherBallNormalDownSpriteTemplate, ANIM_TARGET, 2, -30, -100, 25, 1, 0, 0
	waitforvisualfinish
	playsewithpan SE_M_MEGA_KICK2, SOUND_PAN_TARGET
	createsprite gBasicHitSplatSpriteTemplate, ANIM_TARGET, 4, -10, 0, ANIM_TARGET, 2
	createvisualtask AnimTask_ShakeMon, 2, ANIM_TARGET, 0, 3, 8, 1
	waitforvisualfinish
	end

WeatherBallFire:
	loadspritegfx ANIM_TAG_SMALL_EMBER
	createsprite gWeatherBallFireDownSpriteTemplate, ANIM_TARGET, 2, -30, -100, 25, 1, 40, 10
	playsewithpan SE_M_FLAME_WHEEL, SOUND_PAN_TARGET
	delay 10
	createsprite gWeatherBallFireDownSpriteTemplate, ANIM_TARGET, 2, -30, -100, 25, 1, -40, 20
	playsewithpan SE_M_FLAME_WHEEL, SOUND_PAN_TARGET
	delay 10
	createsprite gWeatherBallFireDownSpriteTemplate, ANIM_TARGET, 2, -30, -100, 25, 1, 0, 0
	playsewithpan SE_M_FLAME_WHEEL, SOUND_PAN_TARGET
	waitforvisualfinish
	playsewithpan SE_M_FLAME_WHEEL2, SOUND_PAN_TARGET
	createvisualtask AnimTask_ShakeMon, 2, ANIM_TARGET, 0, 3, 8, 1
	waitforvisualfinish
	end

WeatherBallWater:
	loadspritegfx ANIM_TAG_SMALL_BUBBLES
	createsprite gWeatherBallWaterDownSpriteTemplate, ANIM_TARGET, 2, -30, -100, 25, 1, 50, 10
	playsewithpan SE_M_CRABHAMMER, SOUND_PAN_TARGET
	delay 8
	createsprite gWeatherBallWaterDownSpriteTemplate, ANIM_TARGET, 2, -30, -100, 25, 1, -20, 20
	playsewithpan SE_M_CRABHAMMER, SOUND_PAN_TARGET
	delay 13
	createsprite gWeatherBallWaterDownSpriteTemplate, ANIM_TARGET, 2, -30, -100, 25, 1, 0, 0
	playsewithpan SE_M_CRABHAMMER, SOUND_PAN_TARGET
	waitforvisualfinish
	createvisualtask AnimTask_ShakeMon, 2, ANIM_TARGET, 0, 3, 8, 1
	playsewithpan SE_M_GIGA_DRAIN, SOUND_PAN_TARGET
	waitforvisualfinish
	end

WeatherBallSandstorm:
	loadspritegfx ANIM_TAG_ROCKS
	createsprite gWeatherBallRockDownSpriteTemplate, ANIM_TARGET, 2, -30, -100, 25, 1, 30, 0
	playsewithpan SE_M_ROCK_THROW, SOUND_PAN_TARGET
	delay 5
	createsprite gWeatherBallRockDownSpriteTemplate, ANIM_TARGET, 2, -30, -100, 25, 1, -40, 20
	playsewithpan SE_M_ROCK_THROW, SOUND_PAN_TARGET
	delay 14
	createsprite gWeatherBallRockDownSpriteTemplate, ANIM_TARGET, 2, -30, -100, 25, 1, 0, 0
	playsewithpan SE_M_ROCK_THROW, SOUND_PAN_TARGET
	waitforvisualfinish
	playsewithpan SE_M_STRENGTH, SOUND_PAN_TARGET
	createsprite gRockScatterSpriteTemplate, ANIM_TARGET, 2, -12, 27, 2, 3
	createsprite gRockScatterSpriteTemplate, ANIM_TARGET, 2, 8, 28, 3, 4
	createsprite gRockScatterSpriteTemplate, ANIM_TARGET, 2, -4, 30, 2, 3
	createsprite gRockScatterSpriteTemplate, ANIM_TARGET, 2, 12, 25, 4, 4
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_TARGET, 2, 0, 8, 1
	waitforvisualfinish
	end

WeatherBallIce:
	loadspritegfx ANIM_TAG_HAIL
	loadspritegfx ANIM_TAG_ICE_CRYSTALS
	createsprite gWeatherBallIceDownSpriteTemplate, ANIM_TARGET, 2, -30, -100, 25, 25, -40, 20
	playsewithpan SE_M_HAIL, SOUND_PAN_TARGET
	delay 10
	createsprite gWeatherBallIceDownSpriteTemplate, ANIM_TARGET, 2, -30, -100, 25, 25, 40, 0
	playsewithpan SE_M_HAIL, SOUND_PAN_TARGET
	delay 10
	createsprite gWeatherBallIceDownSpriteTemplate, ANIM_TARGET, 2, -30, -100, 25, 25, 0, 0
	playsewithpan SE_M_HAIL, SOUND_PAN_TARGET
	waitforvisualfinish
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_TARGET, 2, 0, 8, 1
	playsewithpan SE_M_ICY_WIND, SOUND_PAN_TARGET
	call IceCrystalEffectShort
	waitforvisualfinish
	end

Move_COUNT:
	loadspritegfx ANIM_TAG_IMPACT
	monbg ANIM_TARGET
	setalpha 12, 8
	playsewithpan SE_M_DOUBLE_SLAP, SOUND_PAN_TARGET
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 2, 0, 0, ANIM_TARGET, 2
	createvisualtask AnimTask_ShakeMon, 2, ANIM_TARGET, 3, 0, 6, 1
	waitforvisualfinish
	clearmonbg ANIM_TARGET
	blendoff
	end

IceCrystalEffectShort:
	createsprite gIceCrystalHitLargeSpriteTemplate, ANIM_TARGET, 2, -10, -10, 0
	playsewithpan SE_M_ICY_WIND, SOUND_PAN_TARGET
	delay 4
	createsprite gIceCrystalHitSmallSpriteTemplate, ANIM_TARGET, 2, 10, 20, 0
	playsewithpan SE_M_ICY_WIND, SOUND_PAN_TARGET
	delay 4
	createsprite gIceCrystalHitLargeSpriteTemplate, ANIM_TARGET, 2, -5, 10, 0
	playsewithpan SE_M_ICY_WIND, SOUND_PAN_TARGET
	delay 4
	createsprite gIceCrystalHitSmallSpriteTemplate, ANIM_TARGET, 2, 17, -12, 0
	playsewithpan SE_M_ICY_WIND, SOUND_PAN_TARGET
	delay 4
	createsprite gIceCrystalHitSmallSpriteTemplate, ANIM_TARGET, 2, -15, 15, 0
	playsewithpan SE_M_ICY_WIND, SOUND_PAN_TARGET
	delay 4
	createsprite gIceCrystalHitSmallSpriteTemplate, ANIM_TARGET, 2, 0, 0, 0
	playsewithpan SE_M_ICY_WIND, SOUND_PAN_TARGET
	delay 4
	createsprite gIceCrystalHitLargeSpriteTemplate, ANIM_TARGET, 2, 20, 2, 0
	playsewithpan SE_M_ICY_WIND, SOUND_PAN_TARGET
	return

IceCrystalEffectLong:
	createsprite gIceCrystalHitLargeSpriteTemplate, ANIM_TARGET, 2, -10, -10, 1
	playsewithpan SE_M_ICY_WIND, SOUND_PAN_TARGET
	delay 4
	createsprite gIceCrystalHitSmallSpriteTemplate, ANIM_TARGET, 2, 10, 20, 1
	playsewithpan SE_M_ICY_WIND, SOUND_PAN_TARGET
	delay 4
	createsprite gIceCrystalHitLargeSpriteTemplate, ANIM_TARGET, 2, -29, 0, 1
	playsewithpan SE_M_ICY_WIND, SOUND_PAN_TARGET
	delay 4
	createsprite gIceCrystalHitSmallSpriteTemplate, ANIM_TARGET, 2, 29, -20, 1
	playsewithpan SE_M_ICY_WIND, SOUND_PAN_TARGET
	delay 4
	createsprite gIceCrystalHitLargeSpriteTemplate, ANIM_TARGET, 2, -5, 10, 1
	playsewithpan SE_M_ICY_WIND, SOUND_PAN_TARGET
	delay 4
	createsprite gIceCrystalHitSmallSpriteTemplate, ANIM_TARGET, 2, 17, -12, 1
	playsewithpan SE_M_ICY_WIND, SOUND_PAN_TARGET
	delay 4
	createsprite gIceCrystalHitLargeSpriteTemplate, ANIM_TARGET, 2, -20, 0, 1
	playsewithpan SE_M_ICY_WIND, SOUND_PAN_TARGET
	delay 4
	createsprite gIceCrystalHitSmallSpriteTemplate, ANIM_TARGET, 2, -15, 15, 1
	playsewithpan SE_M_ICY_WIND, SOUND_PAN_TARGET
	delay 4
	createsprite gIceCrystalHitSmallSpriteTemplate, ANIM_TARGET, 2, 26, -5, 1
	playsewithpan SE_M_ICY_WIND, SOUND_PAN_TARGET
	delay 4
	createsprite gIceCrystalHitSmallSpriteTemplate, ANIM_TARGET, 2, 0, 0, 1
	playsewithpan SE_M_ICY_WIND, SOUND_PAN_TARGET
	delay 4
	createsprite gIceCrystalHitLargeSpriteTemplate, ANIM_TARGET, 2, 20, 2, 1
	playsewithpan SE_M_ICY_WIND, SOUND_PAN_TARGET
	return

IceSpikesEffectShort: @ Unused
	loopsewithpan SE_M_ICY_WIND, SOUND_PAN_TARGET, 6, 4
	createsprite gIceGroundSpikeSpriteTemplate, ANIM_TARGET, 2, 0, 24, 0
	delay 4
	createsprite gIceGroundSpikeSpriteTemplate, ANIM_TARGET, 2, 8, 24, 0
	createsprite gIceGroundSpikeSpriteTemplate, ANIM_TARGET, 2, -8, 24, 0
	delay 4
	createsprite gIceGroundSpikeSpriteTemplate, ANIM_TARGET, 2, 16, 24, 0
	createsprite gIceGroundSpikeSpriteTemplate, ANIM_TARGET, 2, -16, 24, 0
	delay 4
	createsprite gIceGroundSpikeSpriteTemplate, ANIM_TARGET, 2, 24, 24, 0
	createsprite gIceGroundSpikeSpriteTemplate, ANIM_TARGET, 2, -24, 24, 0
	delay 4
	createsprite gIceGroundSpikeSpriteTemplate, ANIM_TARGET, 2, 32, 24, 0
	createsprite gIceGroundSpikeSpriteTemplate, ANIM_TARGET, 2, -32, 24, 0
	return

IceSpikesEffectLong:
	loopsewithpan SE_M_ICY_WIND, SOUND_PAN_TARGET, 6, 4
	createsprite gIceGroundSpikeSpriteTemplate, ANIM_TARGET, 2, 0, 24, 1
	delay 4
	createsprite gIceGroundSpikeSpriteTemplate, ANIM_TARGET, 2, 8, 24, 1
	createsprite gIceGroundSpikeSpriteTemplate, ANIM_TARGET, 2, -8, 24, 1
	delay 4
	createsprite gIceGroundSpikeSpriteTemplate, ANIM_TARGET, 2, 16, 24, 1
	createsprite gIceGroundSpikeSpriteTemplate, ANIM_TARGET, 2, -16, 24, 1
	delay 4
	createsprite gIceGroundSpikeSpriteTemplate, ANIM_TARGET, 2, 24, 24, 1
	createsprite gIceGroundSpikeSpriteTemplate, ANIM_TARGET, 2, -24, 24, 1
	delay 4
	createsprite gIceGroundSpikeSpriteTemplate, ANIM_TARGET, 2, 32, 24, 1
	createsprite gIceGroundSpikeSpriteTemplate, ANIM_TARGET, 2, -32, 24, 1
	delay 4
	createsprite gIceGroundSpikeSpriteTemplate, ANIM_TARGET, 2, 40, 24, 1
	createsprite gIceGroundSpikeSpriteTemplate, ANIM_TARGET, 2, -40, 24, 1
	delay 4
	createsprite gIceGroundSpikeSpriteTemplate, ANIM_TARGET, 2, 48, 24, 1
	createsprite gIceGroundSpikeSpriteTemplate, ANIM_TARGET, 2, -48, 24, 1
	return

GrantingStarsEffect:
	createsprite gGrantingStarsSpriteTemplate, ANIM_ATTACKER, 2, -15, 0, 0, 0, 32, 60
	delay 8
	createsprite gGrantingStarsSpriteTemplate, ANIM_ATTACKER, 2, 12, -5, 0, 0, 32, 60
	delay 8
	return

HealingEffect:
	playsewithpan SE_M_ABSORB_2, SOUND_PAN_ATTACKER
	createsprite gHealingBlueStarSpriteTemplate, ANIM_ATTACKER, 2, 0, -5, 0, 0
	delay 7
	createsprite gHealingBlueStarSpriteTemplate, ANIM_ATTACKER, 2, -15, 10, 0, 0
	delay 7
	createsprite gHealingBlueStarSpriteTemplate, ANIM_ATTACKER, 2, -15, -15, 0, 0
	delay 7
	createsprite gHealingBlueStarSpriteTemplate, ANIM_ATTACKER, 2, 10, -5, 0, 0
	delay 7
	return

HealingEffect2:
	playsewithpan SE_M_ABSORB_2, SOUND_PAN_TARGET
	createsprite gHealingBlueStarSpriteTemplate, ANIM_TARGET, 2, 0, -5, 1, 0
	delay 7
	createsprite gHealingBlueStarSpriteTemplate, ANIM_TARGET, 2, -15, 10, 1, 0
	delay 7
	createsprite gHealingBlueStarSpriteTemplate, ANIM_TARGET, 2, -15, -15, 1, 0
	delay 7
	createsprite gHealingBlueStarSpriteTemplate, ANIM_TARGET, 2, 10, -5, 1, 0
	delay 7
	return

PoisonBubblesEffect:
	createsprite gPoisonBubbleSpriteTemplate, ANIM_TARGET, 2, 10, 10, 0
	playsewithpan SE_M_TOXIC, SOUND_PAN_TARGET
	delay 6
	createsprite gPoisonBubbleSpriteTemplate, ANIM_TARGET, 2, 20, -20, 0
	playsewithpan SE_M_TOXIC, SOUND_PAN_TARGET
	delay 6
	createsprite gPoisonBubbleSpriteTemplate, ANIM_TARGET, 2, -20, 15, 0
	playsewithpan SE_M_TOXIC, SOUND_PAN_TARGET
	delay 6
	createsprite gPoisonBubbleSpriteTemplate, ANIM_TARGET, 2, 0, 0, 0
	playsewithpan SE_M_TOXIC, SOUND_PAN_TARGET
	delay 6
	createsprite gPoisonBubbleSpriteTemplate, ANIM_TARGET, 2, -20, -20, 0
	playsewithpan SE_M_TOXIC, SOUND_PAN_TARGET
	delay 6
	createsprite gPoisonBubbleSpriteTemplate, ANIM_TARGET, 2, 16, -8, 0
	playsewithpan SE_M_TOXIC, SOUND_PAN_TARGET
	return

WaterBubblesEffectShort:
	createsprite gWaterBubbleSpriteTemplate, ANIM_ATTACKER, 2, 10, 10, 0
	playsewithpan SE_M_BUBBLE3, SOUND_PAN_TARGET
	delay 6
	createsprite gWaterBubbleSpriteTemplate, ANIM_ATTACKER, 2, 20, -20, 0
	playsewithpan SE_M_BUBBLE3, SOUND_PAN_TARGET
	delay 6
	createsprite gWaterBubbleSpriteTemplate, ANIM_ATTACKER, 2, -20, 15, 0
	playsewithpan SE_M_BUBBLE3, SOUND_PAN_TARGET
	delay 6
	createsprite gWaterBubbleSpriteTemplate, ANIM_ATTACKER, 2, 0, 0, 0
	playsewithpan SE_M_BUBBLE3, SOUND_PAN_TARGET
	delay 6
	createsprite gWaterBubbleSpriteTemplate, ANIM_ATTACKER, 2, -20, -20, 0
	playsewithpan SE_M_BUBBLE3, SOUND_PAN_TARGET
	delay 6
	createsprite gWaterBubbleSpriteTemplate, ANIM_ATTACKER, 2, 16, -8, 0
	playsewithpan SE_M_BUBBLE3, SOUND_PAN_TARGET
	return

WaterBubblesEffectLong:
	createsprite gWaterBubbleSpriteTemplate, ANIM_ATTACKER, 2, 10, 10, 1
	playsewithpan SE_M_BUBBLE3, SOUND_PAN_TARGET
	delay 6
	createsprite gWaterBubbleSpriteTemplate, ANIM_ATTACKER, 2, -28, -10, 1
	playsewithpan SE_M_BUBBLE3, SOUND_PAN_TARGET
	delay 6
	createsprite gWaterBubbleSpriteTemplate, ANIM_ATTACKER, 2, 20, -20, 1
	playsewithpan SE_M_BUBBLE3, SOUND_PAN_TARGET
	delay 6
	createsprite gWaterBubbleSpriteTemplate, ANIM_ATTACKER, 2, -20, 15, 1
	playsewithpan SE_M_BUBBLE3, SOUND_PAN_TARGET
	delay 6
	createsprite gWaterBubbleSpriteTemplate, ANIM_ATTACKER, 2, 0, 0, 1
	playsewithpan SE_M_BUBBLE3, SOUND_PAN_TARGET
	delay 6
	createsprite gWaterBubbleSpriteTemplate, ANIM_ATTACKER, 2, 27, 8, 1
	playsewithpan SE_M_BUBBLE3, SOUND_PAN_TARGET
	delay 6
	createsprite gWaterBubbleSpriteTemplate, ANIM_ATTACKER, 2, -20, -20, 1
	playsewithpan SE_M_BUBBLE3, SOUND_PAN_TARGET
	delay 6
	createsprite gWaterBubbleSpriteTemplate, ANIM_ATTACKER, 2, 16, -8, 1
	playsewithpan SE_M_BUBBLE3, SOUND_PAN_TARGET
	return

ElectricityEffect:
	playsewithpan SE_M_THUNDERBOLT2, SOUND_PAN_TARGET
	createsprite gElectricitySpriteTemplate, ANIM_TARGET, 2, 5, 0, 5, 0
	delay 2
	createsprite gElectricitySpriteTemplate, ANIM_TARGET, 2, -5, 10, 5, 1
	delay 2
	createsprite gElectricitySpriteTemplate, ANIM_TARGET, 2, 15, 20, 5, 2
	delay 2
	createsprite gElectricitySpriteTemplate, ANIM_TARGET, 2, -15, -10, 5, 0
	delay 2
	createsprite gElectricitySpriteTemplate, ANIM_TARGET, 2, 25, 0, 5, 1
	delay 2
	createsprite gElectricitySpriteTemplate, ANIM_TARGET, 2, -8, 8, 5, 2
	delay 2
	createsprite gElectricitySpriteTemplate, ANIM_TARGET, 2, 2, -8, 5, 0
	delay 2
	createsprite gElectricitySpriteTemplate, ANIM_TARGET, 2, -20, 15, 5, 1
	return

ConfusionEffect:
	loopsewithpan SE_M_DIZZY_PUNCH, SOUND_PAN_TARGET, 13, 6
	createsprite gConfusionDuckSpriteTemplate, ANIM_TARGET, 2, 0, -15, 0, 3, 90
	createsprite gConfusionDuckSpriteTemplate, ANIM_TARGET, 2, 0, -15, 51, 3, 90
	createsprite gConfusionDuckSpriteTemplate, ANIM_TARGET, 2, 0, -15, 102, 3, 90
	createsprite gConfusionDuckSpriteTemplate, ANIM_TARGET, 2, 0, -15, 153, 3, 90
	createsprite gConfusionDuckSpriteTemplate, ANIM_TARGET, 2, 0, -15, 204, 3, 90
	return

SetPsychicBackground:
	fadetobg BG_PSYCHIC
	waitbgfadeout
	createvisualtask AnimTask_SetPsychicBackground, 5
	waitbgfadein
	return

UnsetPsychicBackground:
	restorebg
	waitbgfadeout
	setarg 7, 0xFFFF
	waitbgfadein
	return

SetSkyBg:
	jumpifcontest SetSkyBgContest
	fadetobg BG_SKY
	waitbgfadeout
	createvisualtask AnimTask_StartSlidingBg, 5, -2304, 768, 1, -1
SetSkyBgContinue:
	waitbgfadein
	return

SetSkyBgContest:
	fadetobg BG_SKY_CONTESTS
	waitbgfadeout
	createvisualtask AnimTask_StartSlidingBg, 5, 2304, 768, 0, -1
	goto SetSkyBgContinue

UnsetSkyBg:
	restorebg
	waitbgfadeout
	setarg 7, 0xFFFF
	waitbgfadein
	return

SetSolarBeamBg:
	createvisualtask AnimTask_IsContest, 2
	jumprettrue SetSolarBeamBgContest
	createvisualtask AnimTask_IsTargetPlayerSide, 2
	jumpretfalse SetSolarBeamBgOpponent
	goto SetSolarBeamBgPlayer

SetSolarBeamBgContinue:
	waitbgfadein
	return

SetSolarBeamBgContest:
	fadetobg BG_SOLAR_BEAM_CONTESTS
	goto SetSolarBeamBgContinue

SetSolarBeamBgPlayer:
	fadetobg BG_SOLAR_BEAM_PLAYER
	goto SetSolarBeamBgContinue

SetSolarBeamBgOpponent:
	fadetobg BG_SOLAR_BEAM_OPPONENT
	goto SetSolarBeamBgContinue

UnsetSolarBeamBg:
	restorebg
	waitbgfadein
	return

Status_Poison:
	loopsewithpan SE_M_TOXIC, SOUND_PAN_TARGET, 13, 6
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_ATTACKER, 1, 0, 18, 2
	createvisualtask AnimTask_BlendColorCycle, 2, F_PAL_ATTACKER, 2, 2, 0, 12, RGB(30, 0, 31)
	end

Status_Confusion:
	loadspritegfx ANIM_TAG_DUCK
	call ConfusionEffect
	end

Status_Burn:
	loadspritegfx ANIM_TAG_SMALL_EMBER
	playsewithpan SE_M_FLAME_WHEEL, SOUND_PAN_TARGET
	call BurnFlame
	call BurnFlame
	call BurnFlame
	waitforvisualfinish
	end

BurnFlame:
	createsprite gBurnFlameSpriteTemplate, ANIM_TARGET, 2, -24, 24, 24, 24, 20, 1, 1
	delay 4
	return

Status_Infatuation:
	loadspritegfx ANIM_TAG_MAGENTA_HEART
	playsewithpan SE_M_CHARM, SOUND_PAN_ATTACKER
	createsprite gMagentaHeartSpriteTemplate, ANIM_ATTACKER, 3, 0, 20
	delay 15
	playsewithpan SE_M_CHARM, SOUND_PAN_ATTACKER
	createsprite gMagentaHeartSpriteTemplate, ANIM_ATTACKER, 3, -20, 20
	delay 15
	playsewithpan SE_M_CHARM, SOUND_PAN_ATTACKER
	createsprite gMagentaHeartSpriteTemplate, ANIM_ATTACKER, 3, 20, 20
	end

Status_Sleep:
	loadspritegfx ANIM_TAG_LETTER_Z
	playsewithpan SE_M_SNORE, SOUND_PAN_ATTACKER
	createsprite gSleepLetterZSpriteTemplate, ANIM_ATTACKER, 2, 4, -10, 16, 0, 0
	delay 30
	createsprite gSleepLetterZSpriteTemplate, ANIM_ATTACKER, 2, 4, -10, 16, 0, 0
	end

Status_Paralysis:
	loadspritegfx ANIM_TAG_SPARK_2
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_ATTACKER, 1, 0, 10, 1
	call ElectricityEffect
	end

Status_Freeze:
	playsewithpan SE_M_ICY_WIND, 0
	loadspritegfx ANIM_TAG_ICE_CUBE
	monbg ANIM_DEF_PARTNER
	splitbgprio ANIM_TARGET
	waitplaysewithpan SE_M_HAIL, SOUND_PAN_TARGET, 17
	createvisualtask AnimTask_FrozenIceCube, 2
	waitforvisualfinish
	clearmonbg ANIM_DEF_PARTNER
	end

Status_Curse:
	loadspritegfx ANIM_TAG_GHOSTLY_SPIRIT
	monbg ANIM_DEF_PARTNER
	playsewithpan SE_M_NIGHTMARE, SOUND_PAN_TARGET
	createsprite gCurseGhostSpriteTemplate, ANIM_TARGET, 2
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_TARGET, 2, 0, 14, 1
	waitforvisualfinish
	clearmonbg ANIM_DEF_PARTNER
	end

Status_Nightmare:
	loadspritegfx ANIM_TAG_DEVIL
	monbg ANIM_DEF_PARTNER
	playsewithpan SE_M_NIGHTMARE, SOUND_PAN_TARGET
	createsprite gNightmareDevilSpriteTemplate, ANIM_TARGET, 2
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_TARGET, 2, 0, 14, 1
	waitforvisualfinish
	clearmonbg ANIM_DEF_PARTNER
	end

General_CastformChange:
	createvisualtask AnimTask_IsMonInvisible, 2
	jumpreteq TRUE, CastformChangeSkipAnim
	goto CastformChangeContinue

CastformChangeContinue:
	monbg ANIM_ATTACKER
	playsewithpan SE_M_TELEPORT, SOUND_PAN_ATTACKER
	waitplaysewithpan SE_M_MINIMIZE, SOUND_PAN_ATTACKER, 48
	createvisualtask AnimTask_TransformMon, 2, 1
	waitforvisualfinish
	clearmonbg ANIM_ATTACKER
	end

CastformChangeSkipAnim:
	createvisualtask AnimTask_CastformGfxChange, 2, 1
	end

General_StatsChange:
	createvisualtask AnimTask_StatsChange, 5
	waitforvisualfinish
	end

General_SubstituteFade:
	monbg ANIM_ATTACKER
	createvisualtask AnimTask_SubstituteFadeToInvisible, 5
	createvisualtask AnimTask_BlendBattleAnimPal, 10, F_PAL_ATTACKER, 0, 0, 16, RGB_WHITE
	waitforvisualfinish
	delay 1
	clearmonbg ANIM_ATTACKER
	delay 2
	blendoff
	createvisualtask AnimTask_BlendBattleAnimPal, 10, F_PAL_ATTACKER, 0, 0, 0, RGB_WHITE
	createvisualtask AnimTask_SwapMonSpriteToFromSubstitute, 2, TRUE
	end

General_SubstituteAppear:
	createvisualtask AnimTask_MonToSubstitute, 2
	end

General_BaitThrow:
	createvisualtask AnimTask_SafariOrGhost_DecideAnimSides, 2, 0
	createvisualtask AnimTask_LoadBaitGfx, 2
	delay 0
	waitplaysewithpan SE_M_JUMP_KICK, SOUND_PAN_ATTACKER, 22
	createsprite gSafariBaitSpriteTemplate, ANIM_TARGET, 3, -18, 12, 0, 32
	delay 50
	loopsewithpan SE_M_TAIL_WHIP, SOUND_PAN_TARGET, 19, 2
	createvisualtask AnimTask_SwayMon, 5, 1, 8, 1536, 2, ANIM_TARGET
	waitforvisualfinish
	createvisualtask AnimTask_FreeBaitGfx, 2
	end

General_ItemKnockoff:
	loadspritegfx ANIM_TAG_ITEM_BAG
	createsprite gKnockOffItemSpriteTemplate, ANIM_TARGET, 2
	end

General_TurnTrap:
	createvisualtask AnimTask_GetTrappedMoveAnimId, 5
	jumpargeq 0, TRAP_ANIM_FIRE_SPIN, Status_FireSpin
	jumpargeq 0, TRAP_ANIM_WHIRLPOOL, Status_Whirlpool
	jumpargeq 0, TRAP_ANIM_CLAMP,     Status_Clamp
	jumpargeq 0, TRAP_ANIM_SAND_TOMB, Status_SandTomb
	goto Status_BindWrap

Status_BindWrap:
	loadspritegfx ANIM_TAG_TENDRILS
	loopsewithpan SE_M_SCRATCH, SOUND_PAN_TARGET, 6, 2
	createsprite gConstrictBindingSpriteTemplate, ANIM_TARGET, 4, 0, 16, 0, 1
	delay 7
	createsprite gConstrictBindingSpriteTemplate, ANIM_TARGET, 2, 0, 8, 1, 1
	delay 3
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_TARGET, 2, 0, 8, 1
	delay 20
	setarg 7, 0xFFFF
	playsewithpan SE_M_BIND, SOUND_PAN_TARGET
	waitforvisualfinish
	end

Status_FireSpin:
	loadspritegfx ANIM_TAG_SMALL_EMBER
	playsewithpan SE_M_SACRED_FIRE2, SOUND_PAN_TARGET
	createvisualtask AnimTask_ShakeMon, 5, ANIM_TARGET, 0, 2, 30, 1
	call FireSpinEffect
	call FireSpinEffect
	waitforvisualfinish
	stopsound
	end

Status_Whirlpool:
	loadspritegfx ANIM_TAG_WATER_ORB
	monbg ANIM_DEF_PARTNER
	splitbgprio ANIM_TARGET
	setalpha 12, 8
	delay 0
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 0, F_PAL_TARGET, 2, 0, 7, RGB(0, 13, 23)
	playsewithpan SE_M_WHIRLPOOL, SOUND_PAN_TARGET
	createvisualtask AnimTask_ShakeMon, 5, ANIM_TARGET, 0, 2, 30, 1
	call WhirlpoolEffect
	call WhirlpoolEffect
	delay 12
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 0, F_PAL_TARGET, 2, 7, 0, RGB(0, 13, 23)
	waitforvisualfinish
	stopsound
	clearmonbg ANIM_DEF_PARTNER
	end

Status_Clamp:
	loadspritegfx ANIM_TAG_CLAMP
	loadspritegfx ANIM_TAG_IMPACT
	monbg ANIM_TARGET
	setalpha 12, 8
	playsewithpan SE_M_VICEGRIP, SOUND_PAN_TARGET
	createsprite gClampJawSpriteTemplate, ANIM_ATTACKER, 2, -32, 0, 2, 819, 0, 10
	createsprite gClampJawSpriteTemplate, ANIM_ATTACKER, 2, 32, 0, 6, -819, 0, 10
	delay 10
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 2, 0, 0, ANIM_TARGET, 2
	createvisualtask AnimTask_ShakeMon, 5, ANIM_TARGET, 3, 0, 5, 1
	waitforvisualfinish
	clearmonbg ANIM_TARGET
	blendoff
	waitforvisualfinish
	end

Status_SandTomb:
	loadspritegfx ANIM_TAG_MUD_SAND
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 0, F_PAL_TARGET, 2, 0, 7, RGB(19, 17, 0)
	createvisualtask AnimTask_ShakeMon, 5, ANIM_TARGET, 0, 2, 30, 1
	playsewithpan SE_M_SAND_TOMB, SOUND_PAN_TARGET
	call SandTombSwirlingDirt
	call SandTombSwirlingDirt
	delay 22
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 0, F_PAL_TARGET, 2, 7, 0, RGB(19, 17, 0)
	waitforvisualfinish
	stopsound
	end

General_HeldItemEffect:
	loadspritegfx ANIM_TAG_THIN_RING
	loadspritegfx ANIM_TAG_SPARKLE_2
	delay 0
	playsewithpan SE_M_TAKE_DOWN, SOUND_PAN_ATTACKER
	createvisualtask AnimTask_RotateMonToSideAndRestore, 2, 16, 128, ANIM_ATTACKER, 2
	waitforvisualfinish
	playsewithpan SE_M_TAKE_DOWN, SOUND_PAN_ATTACKER
	createvisualtask AnimTask_RotateMonToSideAndRestore, 2, 16, 128, ANIM_ATTACKER, 2
	waitforvisualfinish
	playsewithpan SE_M_TAKE_DOWN, SOUND_PAN_ATTACKER
	createvisualtask AnimTask_RotateMonToSideAndRestore, 2, 16, 128, ANIM_ATTACKER, 2
	waitforvisualfinish
	playsewithpan SE_M_MORNING_SUN, SOUND_PAN_ATTACKER
	call GrantingStarsEffect
	waitforvisualfinish
	playsewithpan SE_SHINY, SOUND_PAN_ATTACKER
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_ATTACKER, 3, 7, 0, RGB(17, 31, 25)
	createsprite gThinRingExpandingSpriteTemplate, ANIM_ATTACKER, 3, 0, 0, 0, 0
	waitforvisualfinish
	end

General_SmokeballEscape:
	loadspritegfx ANIM_TAG_PINK_CLOUD
	monbg ANIM_ATTACKER
	setalpha 12, 4
	delay 0
	playsewithpan SE_BALL_OPEN, SOUND_PAN_TARGET
	createsprite gSmokeBallEscapeCloudSpriteTemplate, ANIM_TARGET, 0, 0, 32, 28, 30
	delay 4
	playsewithpan SE_BALL_OPEN, SOUND_PAN_TARGET
	createsprite gSmokeBallEscapeCloudSpriteTemplate, ANIM_ATTACKER, 127, 2, 12, 20, 30
	delay 12
	playsewithpan SE_BALL_OPEN, SOUND_PAN_TARGET
	createsprite gSmokeBallEscapeCloudSpriteTemplate, ANIM_ATTACKER, 126, 2, -28, 4, 30
	delay 12
	playsewithpan SE_BALL_OPEN, SOUND_PAN_TARGET
	createsprite gSmokeBallEscapeCloudSpriteTemplate, ANIM_ATTACKER, 124, 2, 14, -20, 30
	delay 4
	playsewithpan SE_BALL_OPEN, SOUND_PAN_TARGET
	createvisualtask AnimTask_AttackerFadeToInvisible, 2, 2
	createsprite gSmokeBallEscapeCloudSpriteTemplate, ANIM_ATTACKER, 123, 3, 4, 4, 30
	delay 14
	playsewithpan SE_BALL_OPEN, SOUND_PAN_TARGET
	createsprite gSmokeBallEscapeCloudSpriteTemplate, ANIM_ATTACKER, 122, 3, -14, 18, 46
	delay 0
	createsprite gSmokeBallEscapeCloudSpriteTemplate, ANIM_ATTACKER, 121, 3, 14, -14, 46
	delay 0
	createsprite gSmokeBallEscapeCloudSpriteTemplate, ANIM_ATTACKER, 120, 3, -12, -10, 46
	delay 0
	createsprite gSmokeBallEscapeCloudSpriteTemplate, ANIM_ATTACKER, 119, 3, 14, 14, 46
	delay 0
	createsprite gSmokeBallEscapeCloudSpriteTemplate, ANIM_ATTACKER, 118, 3, 0, 0, 46
	waitforvisualfinish
	clearmonbg ANIM_ATTACKER
	invisible ANIM_ATTACKER
	delay 0
	blendoff
	end

General_FocusBand:
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 0, F_PAL_ATTACKER, 7, 0, 9, RGB_RED
	playsewithpan SE_M_DRAGON_RAGE, SOUND_PAN_ATTACKER
	createvisualtask AnimTask_SlideMonForFocusBand, 5, 30, 128, 0, 1, 2, 0, 1
	waitforvisualfinish
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 0, F_PAL_ATTACKER, 4, 9, 0, RGB_RED
	waitforvisualfinish
	delay 6
	createsprite gSlideMonToOriginalPosSpriteTemplate, ANIM_ATTACKER, 0, 0, 0, 15
	end

General_Rain:
	loadspritegfx ANIM_TAG_RAIN_DROPS
	playsewithpan SE_M_RAIN_DANCE, SOUND_PAN_ATTACKER
	createvisualtask AnimTask_BlendBattleAnimPal, 10, F_PAL_BG | F_PAL_BATTLERS_2, 2, 0, 4, RGB_BLACK
	waitforvisualfinish
	createvisualtask AnimTask_CreateRaindrops, 2, 0, 3, 60
	createvisualtask AnimTask_CreateRaindrops, 2, 0, 3, 60
	delay 50
	waitforvisualfinish
	createvisualtask AnimTask_BlendBattleAnimPal, 10, F_PAL_BG | F_PAL_BATTLERS_2, 2, 4, 0, RGB_BLACK
	waitforvisualfinish
	end

General_Sun:
	goto Move_SUNNY_DAY

General_Sandstorm:
	goto Move_SANDSTORM

General_Hail:
	goto Move_HAIL

General_LeechSeedDrain:
	createvisualtask AnimTask_GetBattlersFromArg, 5
	delay 0
	goto Move_ABSORB

General_MonHit:
	loadspritegfx ANIM_TAG_IMPACT
	monbg ANIM_TARGET
	setalpha 12, 8
	playsewithpan SE_M_DOUBLE_SLAP, SOUND_PAN_TARGET
	createsprite gBasicHitSplatSpriteTemplate, ANIM_ATTACKER, 2, 0, 0, ANIM_TARGET, 2
	createvisualtask AnimTask_ShakeMon, 2, ANIM_TARGET, 3, 0, 6, 1
	waitforvisualfinish
	clearmonbg ANIM_TARGET
	blendoff
	end

General_ItemSteal:
	loadspritegfx ANIM_TAG_ITEM_BAG
	createvisualtask AnimTask_SetAnimAttackerAndTargetForEffectAtk, 2
	createvisualtask AnimTask_SetTargetToEffectBattler, 2  @ Redundant with above
	delay 1
	createsprite gItemStealSpriteTemplate, ANIM_ATTACKER, 2, 0, -5, 10, 2, -1
	end

General_SnatchMove:
	loadspritegfx ANIM_TAG_ITEM_BAG
	createvisualtask AnimTask_SetAnimAttackerAndTargetForEffectTgt, 2
	call SnatchMoveTrySwapFromSubstitute
	delay 1
	createvisualtask AnimTask_SwayMon, 2, 0, 5, 5120, 4, ANIM_TARGET
	waitforvisualfinish
	createvisualtask AnimTask_IsTargetSameSide, 2
	jumpretfalse SnatchOpposingMonMove
	goto SnatchPartnerMonMove

SnatchMoveContinue:
	waitforvisualfinish
	call SnatchMoveTrySwapToSubstitute
	end

SnatchOpposingMonMove:
	playsewithpan SE_M_DOUBLE_TEAM, SOUND_PAN_ATTACKER
	createvisualtask AnimTask_SnatchOpposingMonMove, 2
	goto SnatchMoveContinue

SnatchPartnerMonMove:
	playsewithpan SE_M_DOUBLE_TEAM, SOUND_PAN_ATTACKER
	createvisualtask AnimTask_SnatchPartnerMove, 2
	goto SnatchMoveContinue

General_FutureSightHit:
	createvisualtask AnimTask_SetAnimTargetToBattlerTarget, 2
	monbg ANIM_DEF_PARTNER
	playsewithpan SE_M_PSYBEAM, SOUND_PAN_ATTACKER
	call SetPsychicBackground
	setalpha 8, 8
	playsewithpan SE_M_SUPERSONIC, SOUND_PAN_TARGET
	waitplaysewithpan SE_M_SUPERSONIC, SOUND_PAN_TARGET, 8
	createvisualtask AnimTask_ShakeMon, 2, ANIM_TARGET, 4, 0, 15, 1
	createvisualtask AnimTask_ScaleMonAndRestore, 5, -5, -5, 15, ANIM_TARGET, 1
	waitforvisualfinish
	createvisualtask AnimTask_ShakeMon, 2, ANIM_TARGET, 4, 0, 24, 1
	waitforvisualfinish
	clearmonbg ANIM_DEF_PARTNER
	blendoff
	waitforvisualfinish
	delay 1
	call UnsetPsychicBackground
	end

General_DoomDesireHit:
	createvisualtask AnimTask_SetAnimTargetToBattlerTarget, 2
	loadspritegfx ANIM_TAG_EXPLOSION
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG, 3, 0, 16, RGB_WHITE
	waitforvisualfinish
	delay 10
	createvisualtask AnimTask_DoomDesireLightBeam, 5
	delay 9
	playsewithpan SE_M_CONFUSE_RAY, SOUND_PAN_ATTACKER
	delay 9
	playsewithpan SE_M_CONFUSE_RAY, 0
	delay 9
	playsewithpan SE_M_CONFUSE_RAY, SOUND_PAN_TARGET
	delay 25
	createvisualtask AnimTask_ShakeMonInPlace, 2, ANIM_TARGET, 10, 0, 20, 1
	playsewithpan SE_M_SELF_DESTRUCT, SOUND_PAN_TARGET
	createsprite gExplosionSpriteTemplate, ANIM_ATTACKER, 3, 0, 0, 1, 1
	delay 6
	playsewithpan SE_M_SELF_DESTRUCT, SOUND_PAN_TARGET
	createsprite gExplosionSpriteTemplate, ANIM_ATTACKER, 3, 24, -24, 1, 1
	delay 6
	playsewithpan SE_M_SELF_DESTRUCT, SOUND_PAN_TARGET
	createsprite gExplosionSpriteTemplate, ANIM_ATTACKER, 3, -16, 16, 1, 1
	delay 6
	playsewithpan SE_M_SELF_DESTRUCT, SOUND_PAN_TARGET
	createsprite gExplosionSpriteTemplate, ANIM_ATTACKER, 3, -24, -12, 1, 1
	delay 6
	playsewithpan SE_M_SELF_DESTRUCT, SOUND_PAN_TARGET
	createsprite gExplosionSpriteTemplate, ANIM_ATTACKER, 3, 16, 16, 1, 1
	waitforvisualfinish
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG, 3, 16, 0, RGB_WHITE
	waitforvisualfinish
	end

General_FocusPunchSetUp:
	loadspritegfx ANIM_TAG_FOCUS_ENERGY
	playsewithpan SE_M_DRAGON_RAGE, SOUND_PAN_ATTACKER
	call EndureEffect
	delay 8
	createvisualtask AnimTask_BlendColorCycle, 2, F_PAL_ATTACKER, 2, 2, 0, 11, RGB_RED
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_ATTACKER, 1, 0, 32, 1
	call EndureEffect
	delay 8
	call EndureEffect
	waitforvisualfinish
	end

General_IngrainHeal:
	loadspritegfx ANIM_TAG_ORBS
	loadspritegfx ANIM_TAG_BLUE_STAR
	monbg ANIM_DEF_PARTNER
	setalpha 12, 8
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG, 1, 0, 4, RGB(13, 31, 12)
	waitforvisualfinish
	delay 3
	call AbsorbEffect
	waitforvisualfinish
	delay 15
	call HealingEffect
	waitforvisualfinish
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG, 1, 4, 0, RGB(13, 31, 12)
	waitforvisualfinish
	clearmonbg ANIM_DEF_PARTNER
	blendoff
	end

General_WishHeal:
	loadspritegfx ANIM_TAG_BLUE_STAR
	loadspritegfx ANIM_TAG_SPARKLE_2
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG, 3, 0, 10, RGB_BLACK
	waitforvisualfinish
	playsewithpan SE_M_MEGA_KICK, SOUND_PAN_ATTACKER
	call GrantingStarsEffect
	waitforvisualfinish
	call HealingEffect
	waitforvisualfinish
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 2, F_PAL_BG, 3, 10, 0, RGB_BLACK
	end

General_MonScared:
	createvisualtask AnimTask_SafariOrGhost_DecideAnimSides, 2, 1
	waitforvisualfinish
	loadspritegfx ANIM_TAG_SWEAT_BEAD
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 0, F_PAL_TARGET, 2, 0, 10, RGB(0, 23, 25)
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_TARGET, 2, 0, 10, 1
	delay 20
	createsprite gSprayWaterDropletSpriteTemplate, ANIM_TARGET, 5, 0, 1
	playsewithpan SE_M_SKETCH, SOUND_PAN_TARGET
	createsprite gSprayWaterDropletSpriteTemplate, ANIM_TARGET, 5, 1, 1
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_TARGET, 4, 0, 5, 1
	createvisualtask AnimTask_StretchTargetUp, 3
	waitforvisualfinish
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 0, F_PAL_TARGET, 2, 10, 0, RGB(0, 23, 25)
	waitforvisualfinish
	end

General_GhostGetOut:
	createvisualtask AnimTask_SafariOrGhost_DecideAnimSides, 2, 1
	waitforvisualfinish
	fadetobg BG_GHOST
	waitbgfadeout
	monbg_static ANIM_ATTACKER
	createvisualtask AnimTask_GhostGetOut, 2
	waitbgfadein
	loopsewithpan SE_M_PSYBEAM, SOUND_PAN_TARGET, 20, 3
	waitforvisualfinish
	clearmonbg_static ANIM_ATTACKER
	delay 1
	loadspritegfx ANIM_TAG_SWEAT_BEAD
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 0, F_PAL_TARGET, -1, 0, 6, RGB(21, 22, 26)
	createsprite gSprayWaterDropletSpriteTemplate, ANIM_TARGET, 5, 0, 1
	createsprite gSprayWaterDropletSpriteTemplate, ANIM_TARGET, 5, 1, 1
	createvisualtask AnimTask_ShakeMon2, 2, ANIM_TARGET, 4, 0, 5, 1
	createvisualtask AnimTask_StretchTargetUp, 3
	waitforvisualfinish
	createsprite gSimplePaletteBlendSpriteTemplate, ANIM_ATTACKER, 0, F_PAL_TARGET, -1, 6, 0, RGB(21, 22, 26)
	waitforvisualfinish
	restorebg
	waitbgfadein
	end

General_SilphScoped:
	monbg ANIM_ATTACKER
	playsewithpan SE_M_TELEPORT, SOUND_PAN_ATTACKER
	waitplaysewithpan SE_M_MINIMIZE, SOUND_PAN_ATTACKER, 48
	createvisualtask AnimTask_TransformMon, 2, 255
	waitsound
	waitforvisualfinish
	clearmonbg ANIM_ATTACKER
	end

General_SafariRockThrow:
	createvisualtask AnimTask_SafariOrGhost_DecideAnimSides, 2, 0
	waitforvisualfinish
	loadspritegfx ANIM_TAG_ROCKS
	loadspritegfx ANIM_TAG_IMPACT
	delay 0
	waitplaysewithpan SE_M_JUMP_KICK, SOUND_PAN_ATTACKER, 22
	createsprite gSafariRockTemplate, ANIM_TARGET, 3, -17, 14, 8, 0
	delay 50
	monbg ANIM_DEF_PARTNER
	setalpha 12, 8
	delay 0
	playsewithpan SE_M_DOUBLE_SLAP, SOUND_PAN_TARGET
	createsprite gBasicHitSplatSpriteTemplate, ANIM_TARGET, 2, -4, -20, 1, 2
	waitforvisualfinish
	clearmonbg ANIM_DEF_PARTNER
	blendoff
	waitforvisualfinish
	end

General_SafariReaction:
	createvisualtask AnimTask_SafariGetReaction, 2
	waitforvisualfinish
	jumpreteq B_MSG_MON_WATCHING, SafariReaction_WatchingCarefully
	jumpreteq B_MSG_MON_ANGRY, SafariReaction_Angry
	jumpreteq B_MSG_MON_EATING, SafariReaction_Eating
	end

SafariReaction_WatchingCarefully:
	playsewithpan SE_M_TAKE_DOWN, SOUND_PAN_TARGET
	createvisualtask AnimTask_RotateMonToSideAndRestore, 2, 16, 96, 0, 2
	waitforvisualfinish
	playsewithpan SE_M_TAKE_DOWN, SOUND_PAN_TARGET
	createvisualtask AnimTask_RotateMonToSideAndRestore, 2, 16, -96, 0, 2
	end

SafariReaction_Angry:
	loadspritegfx ANIM_TAG_ANGER
	createsprite gAngerMarkSpriteTemplate, ANIM_TARGET, 2, 1, 20, -20
	playsewithpan SE_M_SWAGGER2, SOUND_PAN_TARGET
	waitforvisualfinish
	delay 12
	createsprite gAngerMarkSpriteTemplate, ANIM_TARGET, 2, 1, -20, -20
	playsewithpan SE_M_SWAGGER2, SOUND_PAN_TARGET
	end

SafariReaction_Eating:
	playsewithpan SE_M_TAKE_DOWN, SOUND_PAN_TARGET
	createvisualtask AnimTask_RotateMonToSideAndRestore, 2, 8, 136, 0, 2
	waitforvisualfinish
	playsewithpan SE_M_TAKE_DOWN, SOUND_PAN_TARGET
	createvisualtask AnimTask_RotateMonToSideAndRestore, 2, 8, 136, 0, 2
	end

SnatchMoveTrySwapFromSubstitute:
	createvisualtask AnimTask_IsAttackerBehindSubstitute, 2
	jumprettrue SnatchMoveSwapSubstituteForMon
SnatchMoveTrySwapFromSubstituteEnd:
	waitforvisualfinish
	return

SnatchMoveSwapSubstituteForMon:
	createvisualtask AnimTask_SwapMonSpriteToFromSubstitute, 2, TRUE
	waitforvisualfinish
	goto SnatchMoveTrySwapFromSubstituteEnd

SnatchMoveTrySwapToSubstitute:
	createvisualtask AnimTask_IsAttackerBehindSubstitute, 2
	jumprettrue SnatchMoveSwapMonForSubstitute
SnatchMoveTrySwapToSubstituteEnd:
	waitforvisualfinish
	return

SnatchMoveSwapMonForSubstitute:
	createvisualtask AnimTask_SwapMonSpriteToFromSubstitute, 2, FALSE
	waitforvisualfinish
	goto SnatchMoveTrySwapToSubstituteEnd

@ Healthbox blue flash effect on level up
Special_LevelUp:
	playsewithpan SE_EXP_MAX, 0
	createvisualtask AnimTask_LoadHealthboxPalsForLevelUp, 2
	delay 0
	createvisualtask AnimTask_FlashHealthboxOnLevelUp, 5, 0, 0
	waitforvisualfinish
	createvisualtask AnimTask_FreeHealthboxPalsForLevelUp, 2
	end

Special_SwitchOutPlayerMon:
	createvisualtask AnimTask_SwitchOutBallEffect, 2
	delay 10
	createvisualtask AnimTask_SwitchOutShrinkMon, 2
	end

Special_SwitchOutOpponentMon:
	createvisualtask AnimTask_SwitchOutBallEffect, 2
	delay 10
	createvisualtask AnimTask_SwitchOutShrinkMon, 2
	end

Special_BallThrow:
	createvisualtask AnimTask_LoadBallGfx, 2
	delay 0
	playsewithpan SE_BALL_THROW, 0
	createvisualtask AnimTask_ThrowBall, 2
	createvisualtask AnimTask_IsBallBlockedByTrainerOrDodged, 2
	jumpreteq -1, BallThrowTrainerBlock
	jumpreteq -2, BallThrowGhostDodged
BallThrowEnd:
	waitforvisualfinish
	createvisualtask AnimTask_FreeBallGfx, 2
	end

BallThrowTrainerBlock:
	loadspritegfx ANIM_TAG_IMPACT
	delay 25
	monbg ANIM_DEF_PARTNER
	setalpha 12, 8
	delay 0
	playsewithpan SE_M_DOUBLE_SLAP, SOUND_PAN_TARGET
	createsprite gBasicHitSplatSpriteTemplate, ANIM_TARGET, 2, -4, -20, ANIM_TARGET, 2
	waitforvisualfinish
	clearmonbg ANIM_DEF_PARTNER
	blendoff
	goto BallThrowEnd

BallThrowGhostDodged:
	delay 16
	createvisualtask AnimTask_WindUpLunge, 2, ANIM_TARGET, 48, 6, 16, 48, -48, 16
	playsewithpan SE_M_TAKE_DOWN, SOUND_PAN_TARGET
	waitplaysewithpan SE_M_TAKE_DOWN, SOUND_PAN_TARGET, 48
	waitforvisualfinish
	goto BallThrowEnd

Special_BallThrowWithTrainer:
	createvisualtask AnimTask_LoadBallGfx, 2
	delay 0
	createvisualtask AnimTask_ThrowBallSpecial, 2
	waitforvisualfinish
	createvisualtask AnimTask_FreeBallGfx, 2
	end

Special_SubstituteToMon:
	createvisualtask AnimTask_SwapMonSpriteToFromSubstitute, 2, TRUE
	end

Special_MonToSubstitute:
	createvisualtask AnimTask_SwapMonSpriteToFromSubstitute, 2, FALSE
	end
