@ These are event scripts. They should not be moved to C.

#include "constants/global.h"
#include "constants/flags.h"
#include "constants/moves.h"
#include "constants/songs.h"
#include "constants/species.h"
#include "constants/vars.h"
#include "constants/items.h"
#include "constants/region_map_sections.h"
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
@ ===== BEGIN asm/macros/event.inc =====
	@ Does nothing.
	.macro nop
	.byte 0x00
	.endm

	@ Does nothing.
	.macro nop1
	.byte 0x01
	.endm

	@ Terminates script execution.
	.macro end
	.byte 0x02
	.endm

	@ Jumps back to after the last-executed call statement, and continues script execution from there.
	.macro return
	.byte 0x03
	.endm

	@ Jumps to destination and continues script execution from there. The location of the calling script is remembered and can be returned to later.
	.macro call destination:req
	.byte 0x04
	.4byte \destination
	.endm

	@ Jumps to destination and continues script execution from there.
	.macro goto destination:req
	.byte 0x05
	.4byte \destination
	.endm

	@ If the result of the last comparison matches condition (see Comparison operators), jumps to destination and continues script execution from there.
	.macro goto_if condition:req, destination:req
	.byte 0x06
	.byte \condition
	.4byte \destination
	.endm

	@ If the result of the last comparison matches condition (see Comparison operators), calls destination.
	.macro call_if condition:req, destination:req
	.byte 0x07
	.byte \condition
	.4byte \destination
	.endm

	@ Jumps to the script in gStdScripts at index function.
	.macro gotostd function:req
	.byte 0x08
	.byte \function
	.endm

	@ Callstd ids
	STD_OBTAIN_ITEM = 0
	STD_FIND_ITEM = 1

	MSGBOX_NPC = 2
	MSGBOX_SIGN = 3
	MSGBOX_DEFAULT = 4
	MSGBOX_YESNO = 5
	MSGBOX_AUTOCLOSE = 6

	STD_OBTAIN_DECORATION = 7
	STD_PUT_ITEM_AWAY = 8
	STD_RECEIVED_ITEM = 9

	@ Calls the script in gStdScripts at index function.
	.macro callstd function:req
	.byte 0x09
	.byte \function
	.endm

	@ If the result of the last comparison matches condition (see Comparison operators), jumps to the script in gStdScripts at index function.
	.macro gotostd_if condition:req, function:req
	.byte 0x0a
	.byte \condition
	.byte \function
	.endm

	@ If the result of the last comparison matches condition (see Comparison operators), calls the script in gStdScripts at index function.
	.macro callstd_if condition:req, function:req
	.byte 0x0b
	.byte \condition
	.byte \function
	.endm

	@ Equivalent to the 'return' command for a RAM script.
	.macro returnram
	.byte 0x0c
	.endm

	@ Equivalent to the 'end' command for a RAM script.
	.macro endram
	.byte 0x0d
	.endm

	@ Sets the Mystery Event script status (MEVENT_STATUS_*).
	.macro setmysteryeventstatus value:req
	.byte 0x0e
	.byte \value
	.endm

	@ Sets the value at the specified script data index to a fixed 4-byte value.
	.macro loadword destIndex:req, value:req
	.byte 0x0f
	.byte \destIndex
	.4byte \value
	.endm

	@ Sets the value at the specified script data index to a fixed byte value.
	.macro loadbyte destIndex:req, value:req
	.byte 0x10
	.byte \destIndex
	.byte \value
	.endm

	@ Sets the value at the specified pointer.
	.macro setptr value:req, ptr:req
	.byte 0x11
	.byte \value
	.4byte \ptr
	.endm

	@ Sets the value at the specified script data index to the value at pointer 'source'.
	.macro loadbytefromptr destIndex:req, source:req
	.byte 0x12
	.byte \destIndex
	.4byte \source
	.endm

	@ Sets the value at pointer 'destination' to the contents of the script data at 'srcIndex'.
	.macro setptrbyte srcIndex:req, destination:req
	.byte 0x13
	.byte \srcIndex
	.4byte \destination
	.endm

	@ Copies the contents of the script data from one index to another.
	.macro copylocal destIndex:req, srcIndex:req
	.byte 0x14
	.byte \destIndex
	.byte \srcIndex
	.endm

	@ Copies the byte at source to destination, replacing whatever byte was previously there.
	.macro copybyte destination:req, source:req
	.byte 0x15
	.4byte \destination
	.4byte \source
	.endm

	@ Changes the value of destination to value.
	.macro setvar destination:req, value:req
	.byte 0x16
	.2byte \destination
	.2byte \value
	.endm

	@ Changes the value of destination by adding value to it. Overflow is not prevented (0xFFFF + 1 = 0x0000).
	.macro addvar destination:req, value:req
	.byte 0x17
	.2byte \destination
	.2byte \value
	.endm

	@ Changes the value of destination by subtracting value to it. Overflow is not prevented (0x0000 - 1 = 0xFFFF).
	.macro subvar destination:req, value:req
	.byte 0x18
	.2byte \destination
	.2byte \value
	.endm

	@ Copies the value of source into destination.
	.macro copyvar destination:req, source:req
	.byte 0x19
	.2byte \destination
	.2byte \source
	.endm

	@ If source is not a variable, then this function acts like setvar. Otherwise, it acts like copyvar.
	.macro setorcopyvar destination:req, source:req
	.byte 0x1a
	.2byte \destination
	.2byte \source
	.endm

	@ Compares the values of the script data at indexes 'local1' and 'local2'.
	@ The result is stored in comparisonResult to be acted on by goto_if / call_if
	.macro compare_local_to_local local1:req, local2:req
	.byte 0x1b
	.byte \local1
	.byte \local2
	.endm

	@ Compares the value of the script data at index 'local' to a fixed value.
	@ The result is stored in comparisonResult to be acted on by goto_if / call_if
	.macro compare_local_to_value local:req, value:req
	.byte 0x1c
	.byte \local
	.byte \value
	.endm

	@ Compares the value of the script data at index 'local' to the value at 'ptr'
	@ The result is stored in comparisonResult to be acted on by goto_if / call_if
	.macro compare_local_to_ptr local:req, ptr:req
	.byte 0x1d
	.byte \local
	.4byte \ptr
	.endm

	@ Compares the value at 'ptr' to the value of the script data at index 'local'.
	@ The result is stored in comparisonResult to be acted on by goto_if / call_if
	.macro compare_ptr_to_local ptr:req, local:req
	.byte 0x1e
	.4byte \ptr
	.byte \local
	.endm

	@ Compares the value at 'ptr' to a fixed value.
	@ The result is stored in comparisonResult to be acted on by goto_if / call_if
	.macro compare_ptr_to_value ptr:req, value:req
	.byte 0x1f
	.4byte \ptr
	.byte \value
	.endm

	@ Compares the value at 'ptr1' to the value at 'ptr2'.
	@ The result is stored in comparisonResult to be acted on by goto_if / call_if
	.macro compare_ptr_to_ptr ptr1:req, ptr2:req
	.byte 0x20
	.4byte \ptr1
	.4byte \ptr2
	.endm

	@ Compares the value of 'var' to a fixed value.
	@ The result is stored in comparisonResult to be acted on by goto_if / call_if
	.macro compare_var_to_value var:req, value:req
	.byte 0x21
	.2byte \var
	.2byte \value
	.endm

	@ Compares the value of 'var1' to the value of 'var2'.
	@ The result is stored in comparisonResult to be acted on by goto_if / call_if
	.macro compare_var_to_var var1:req, var2:req
	.byte 0x22
	.2byte \var1
	.2byte \var2
	.endm

	@ Generic compare macro which attempts to deduce argument types based on their values
	@ Any values between VARS_START to VARS_END and SPECIAL_VARS_START to SPECIAL_VARS_END are considered event variable identifiers
	.macro compare var:req, arg:req
		.if ((\arg >= VARS_START && \arg <= VARS_END) || (\arg >= SPECIAL_VARS_START && \arg <= SPECIAL_VARS_END))
			compare_var_to_var \var, \arg
		.else
			compare_var_to_value \var, \arg
		.endif
	.endm

	@ Calls the native C function stored at func.
	.macro callnative func:req
	.byte 0x23
	.4byte \func
	.endm

	@ Replaces the script with the function stored at func. Execution returns to the bytecode script when func returns TRUE.
	.macro gotonative func:req
	.byte 0x24
	.4byte \func
	.endm

	@ Calls a function listed in the table in data/specials.inc.
	.macro special function:req
	.byte 0x25
	.2byte SPECIAL_\function
	.endm

	@ Calls a function listed in the table in data/specials.inc.
	@ That function's output (if any) will be written to the variable specified by 'output'.
	.macro specialvar output:req, function:req
	.byte 0x26
	.2byte \output
	.2byte SPECIAL_\function
	.endm

	@ Blocks script execution until a command or C code manually unblocks it. Generally used with specific 
	@ commands and specials. Calling ScriptContext_Enable for instance will allow execution to continue.
	.macro waitstate
	.byte 0x27
	.endm

	@ Blocks script execution for frames. (Pokemon Emerald runs at just shy of 60 frames per second.)
	.macro delay frames:req
	.byte 0x28
	.2byte \frames
	.endm

	@ Sets flag to TRUE.
	.macro setflag flag:req
	.byte 0x29
	.2byte \flag
	.endm

	@ Sets flag to FALSE.
	.macro clearflag flag:req
	.byte 0x2a
	.2byte \flag
	.endm

	@ Compares flag to TRUE and stores the result in comparisonResult to be used by goto_if, etc
	@ See additional _if_unset and _if_set macros
	.macro checkflag flag:req
	.byte 0x2b
	.2byte \flag
	.endm

	@ In FRLG, this command is a nop. In RSE, initializes the RTC's local time offset to the given hour and minute.
	.macro initclock hour:req, minute:req
	.byte 0x2c
	.2byte \hour
	.2byte \minute
	.endm

	@ In FRLG, this command is a nop. In RSE, updates local time using the RTC and runs time based events.
	.macro dotimebasedevents
	.byte 0x2d
	.endm

	@ Sets the values of variables VAR_0x8000, VAR_0x8001, and VAR_0x8002 to 0. In RSE, they'd get the current hour, minute, and second respectively.
	.macro gettime
	.byte 0x2e
	.endm

	@ Plays the specified sound. Only one sound may play at a time, with newer ones interrupting older ones.
	.macro playse song:req
	.byte 0x2f
	.2byte \song
	.endm

	@ Blocks script execution until the currently-playing sound (triggered by playse) finishes playing.
	.macro waitse
	.byte 0x30
	.endm

	@ Plays the fanfare specified by the song number. If the specified song is not a fanfare it will instead play the first song in sFanfares.
	.macro playfanfare song:req
	.byte 0x31
	.2byte \song
	.endm

	@ Blocks script execution until all currently-playing fanfares finish.
	.macro waitfanfare
	.byte 0x32
	.endm

	@ Plays the specified song. If save_song is TRUE, the
	@ specified song will be saved as if savebgm was called with it.
	.macro playbgm song:req, save_song:req
	.byte 0x33
	.2byte \song
	.byte \save_song
	.endm

	@ Saves the specified song to be played later. Saved music may be played when Overworld_PlaySpecialMapMusic is called. This occurs on
	@ exiting most warps.
	.macro savebgm song:req
	.byte 0x34
	.2byte \song
	.endm

	@ Crossfades the currently-playing song into the map's default song.
	.macro fadedefaultbgm
	.byte 0x35
	.endm

	@ Crossfades the currently-playing song into the specified song.
	.macro fadenewbgm song:req
	.byte 0x36
	.2byte \song
	.endm

	@ Fades out the currently-playing song.
	.macro fadeoutbgm speed:req
	.byte 0x37
	.byte \speed
	.endm

	@ Fades the previously-playing song back in.
	.macro fadeinbgm speed:req
	.byte 0x38
	.byte \speed
	.endm

	@ Helper macro for warp commands that formats their arguments.
	@ It allows warp macros to either provide 1. a valid id for which warp location to use,
	@ or 2. a pair of x/y coordinates to use. Both may be provided but at least one will be
	@ ignored by SetPlayerCoordsFromWarp. If none are provided it will use dummy arguments,
	@ and the warp will send the player to the center of the map.
	@ Examples of valid inputs for a warp command:
	@ - warp MAP, x, y
	@ - warp MAP, warpId
	@ - warp MAP
	@ - warp MAP, warpId, x, y
	.macro formatwarp map:req, a, b, c
	map \map
	.ifb \a @ No arguments provided, use dummy warpId and coords.
		.byte WARP_ID_NONE
		.2byte -1 @ x
		.2byte -1 @ y
	.else
	.ifb \b @ Only one argument provided, treat it as a warpId and use dummy coords.
		.byte \a   @ warpId
		.2byte -1  @ x
		.2byte -1  @ y
	.else
	.ifb \c @ Only two arguments provided, treat them as a coord pair and use dummy warpId.
		.byte WARP_ID_NONE
		.2byte \a  @ x
		.2byte \b  @ y
	.else @ All three arguments provided. Output them and let the warp sort out which to use.
		.byte \a  @ warpId
		.2byte \b @ x
		.2byte \c @ y
	.endif
	.endif
	.endif
	.endm

	@ Warps the player to the specified map.
	@ Warp commands can be given either the id of which warp location to go to on the destination map
	@ or a pair of x/y coordinates to go to directly on the destination map.
	.macro warp map:req, a, b, c
	.byte 0x39
	formatwarp \map, \a, \b, \c
	.endm

	@ Warps the player to the specified map without playing a sound effect.
	@ Warp commands can be given either the id of which warp location to go to on the destination map
	@ or a pair of x/y coordinates to go to directly on the destination map.
	.macro warpsilent map:req, a, b, c
	.byte 0x3a
	formatwarp \map, \a, \b, \c
	.endm

	@ Warps the player to the specified map and plays a door opening animation before stepping upwards into it.
	@ Warp commands can be given either the id of which warp location to go to on the destination map
	@ or a pair of x/y coordinates to go to directly on the destination map.
	.macro warpdoor map:req, a, b, c
	.byte 0x3b
	formatwarp \map, \a, \b, \c
	.endm

	@ Warps the player to another map using a hole animation. If the specified map is MAP_UNDEFINED it will instead
	@ use the map set by setholewarp. In either case the target coordinates on the destination map will be the
	@ player's current position.
	.macro warphole map:req
	.byte 0x3c
	map \map
	.endm

	@ Warps the player to the specified map using a teleport effect. Effect is similar to warpspinenter but
	@ this warp has a fade out first and doesn't maintain the original facing direction.
	@ Warp commands can be given either the id of which warp location to go to on the destination map
	@ or a pair of x/y coordinates to go to directly on the destination map.
	.macro warpteleport map:req, a, b, c
	.byte 0x3d
	formatwarp \map, \a, \b, \c
	.endm

	@ Sets the warp destination to be used later.
	@ Warp commands can be given either the id of which warp location to go to on the destination map
	@ or a pair of x/y coordinates to go to directly on the destination map.
	.macro setwarp map:req, a, b, c
	.byte 0x3e
	formatwarp \map, \a, \b, \c
	.endm

	@ Sets the dynamic warp destination. Warps with a destination map of MAP_DYNAMIC will target this destination.
	@ Warp commands can be given either the id of which warp location to go to on the destination map
	@ or a pair of x/y coordinates to go to directly on the destination map.
	.macro setdynamicwarp map:req, a, b, c
	.byte 0x3f
	formatwarp \map, \a, \b, \c
	.endm

	@ Sets the destination that diving or emerging from a dive will take the player to. Note that this only
	@ applies if the current map does not have a dive/emerge connection. If it does have a corresponding
	@ map connection then that map and the player's current coordinates will be used as the destination instead.
	@ Warp commands can be given either the id of which warp location to go to on the destination map
	@ or a pair of x/y coordinates to go to directly on the destination map.
	.macro setdivewarp map:req, a, b, c
	.byte 0x40
	formatwarp \map, \a, \b, \c
	.endm

	@ Sets the destination that falling into a hole will take the player to.
	@ While it does accept and set the x/y coordinates and warpId, they are ultimately ignored.
	@ This is only used to set the map the player should fall to. The exact location on the
	@ map to fall to is determined by warphole.
	@ Warp commands can be given either the id of which warp location to go to on the destination map
	@ or a pair of x/y coordinates to go to directly on the destination map.
	.macro setholewarp map:req, a=0, b=0, c
	.byte 0x41
	formatwarp \map, \a, \b, \c
	.endm

	@ Retrieves the player's zero-indexed x- and y-coordinates in the map, and stores them in the specified variables.
	.macro getplayerxy x:req, y:req
	.byte 0x42
	.2byte \x
	.2byte \y
	.endm

	@ Retrieves the number of Pokemon in the player's party, and stores that number in VAR_RESULT.
	.macro getpartysize
	.byte 0x43
	.endm

	@ Attempts to add quantity of the specified item to the player's Bag. If the player has enough room, the item will
	@ be added and VAR_RESULT will be set to TRUE; otherwise, VAR_RESULT is set to FALSE.
	.macro additem itemId:req, quantity=1
	.byte 0x44
	.2byte \itemId
	.2byte \quantity
	.endm

	@ Removes quantity of the specified item from the player's Bag. If the player has fewer than 'quantity' in their bag
	@ then none will be removed and VAR_RESULT will be set to FALSE. Otherwise it will be set to TRUE.
	.macro removeitem itemId:req, quantity=1
	.byte 0x45
	.2byte \itemId
	.2byte \quantity
	.endm

	@ Checks if the player has enough space in their Bag to hold quantity more of the specified item. Sets VAR_RESULT to
	@ TRUE if there is room, or FALSE is there is no room.
	.macro checkitemspace itemId:req, quantity=1
	.byte 0x46
	.2byte \itemId
	.2byte \quantity
	.endm

	@ Checks if the player has quantity or more of the specified item in their Bag. Sets VAR_RESULT to TRUE if the player has
	@ enough of the item, or FALSE if they have fewer than quantity of the item.
	.macro checkitem itemId:req, quantity=1
	.byte 0x47
	.2byte \itemId
	.2byte \quantity
	.endm

	@ Checks which Bag pocket the specified item belongs in, and writes the pocket value (POCKET_*) to VAR_RESULT.
	@ This is used to show the name of the proper Bag pocket when the player receives an item via callstd.
	.macro checkitemtype itemId:req
	.byte 0x48
	.2byte \itemId
	.endm

	@ Adds quantity of the specified item to the player's PC.
	.macro addpcitem itemId:req, quantity=1
	.byte 0x49
	.2byte \itemId
	.2byte \quantity
	.endm

	@ Checks for quantity of the specified item in the player's PC.
	.macro checkpcitem itemId:req, quantity=1
	.byte 0x4a
	.2byte \itemId
	.2byte \quantity
	.endm

	@ In FRLG, this command is a nop. In RSE, adds a decoration to the player's PC.
	.macro adddecoration decoration:req
	.byte 0x4b
	.2byte \decoration
	.endm

	@ In FRLG, this command is a nop. In RSE, removes a decoration from the player's PC.
	.macro removedecoration decoration:req
	.byte 0x4c
	.2byte \decoration
	.endm

	@ In FRLG, this command is a nop. In RSE, checks for decoration in the player's PC.
	.macro checkdecor decoration:req
	.byte 0x4d
	.2byte \decoration
	.endm

	@ In FRLG, this command is a nop. In RSE, checks if the player has enough space in their PC to hold the decoration.
	.macro checkdecorspace decoration:req
	.byte 0x4e
	.2byte \decoration
	.endm

	@ Applies the movement data at movements to the specified (localId) object. If no map is specified, then the current map is used.
	.macro applymovement localId:req, movements:req, map
		.ifb \map
			.byte 0x4f
			.2byte \localId
			.4byte \movements
		.else
			@ Really only useful if the object has followed from one map to another (e.g. Wally during the catching event).
			.byte 0x50
			.2byte \localId
			.4byte \movements
			map \map
		.endif
	.endm

	@ Blocks script execution until the movements being applied to the specified (localId) object finish.
	@ If localId is LOCALID_NONE (0), then the id of the last-moved object will be used instead.
	@ If the specified object is not currently being manipulated with applymovement, then this command does nothing.
	@ If no map is specified, then the current map is used.
	.macro waitmovement localId=LOCALID_NONE, map
		.ifb \map
			.byte 0x51
			.2byte \localId
		.else
			.byte 0x52
			.2byte \localId
			map \map
		.endif
	.endm

	@ Attempts to despawn the specified (localId) object on the specified map.
	@ It also sets the object's visibility flag if it has one.
	@ If no map is specified, then the current map is used.
	.macro removeobject localId:req, map
		.ifb \map
			.byte 0x53
			.2byte \localId
		.else
			.byte 0x54
			.2byte \localId
			map \map
		.endif
	.endm

	@ Attempts to spawn the specified (localId) object the specified map.
	@ Note that unlike removeobject this does not modify the object's flag.
	@ If no map is specified, then the current map is used.
	.macro addobject localId:req, map
		.ifb \map
			.byte 0x55
			.2byte \localId
		.else
			.byte 0x56
			.2byte \localId
			map \map
		.endif
	.endm

	@ Sets the specified (localId) object's position on the current map.
	.macro setobjectxy localId:req, x:req, y:req
	.byte 0x57
	.2byte \localId
	.2byte \x
	.2byte \y
	.endm

	@ Sets the specified object's invisibility to FALSE.
	.macro showobjectat localId:req, map:req
	.byte 0x58
	.2byte \localId
	map \map
	.endm

	@ Sets the specified object's invisibility to TRUE.
	.macro hideobjectat localId:req, map:req
	.byte 0x59
	.2byte \localId
	map \map
	.endm

	@ Turns the currently selected object (if there is one) to face the player.
	.macro faceplayer
	.byte 0x5a
	.endm

	@ Turns the specified object in the specified direction.
	.macro turnobject localId:req, direction:req
	.byte 0x5b
	.2byte \localId
	.byte \direction
	.endm

	@ Configures the arguments for a trainer battle, then jumps to the appropriate script in scripts/trainer_battle.inc
	.macro trainerbattle type:req, trainer:req, local_id:req, pointer1:req, pointer2, pointer3, pointer4
		.byte 0x5c
		.byte \type
		.2byte \trainer
		.2byte \local_id
		.if \type == TRAINER_BATTLE_SINGLE
			.4byte \pointer1 @ text
			.4byte \pointer2 @ text
		.elseif \type == TRAINER_BATTLE_CONTINUE_SCRIPT_NO_MUSIC
			.4byte \pointer1 @ text
			.4byte \pointer2 @ text
			.4byte \pointer3 @ event script
		.elseif \type == TRAINER_BATTLE_CONTINUE_SCRIPT
			.4byte \pointer1 @ text
			.4byte \pointer2 @ text
			.4byte \pointer3 @ event script
		.elseif \type == TRAINER_BATTLE_SINGLE_NO_INTRO_TEXT
			.4byte \pointer1 @ text
		.elseif \type == TRAINER_BATTLE_DOUBLE
			.4byte \pointer1 @ text
			.4byte \pointer2 @ text
			.4byte \pointer3 @ text
		.elseif \type == TRAINER_BATTLE_REMATCH
			.4byte \pointer1 @ text
			.4byte \pointer2 @ text
		.elseif \type == TRAINER_BATTLE_CONTINUE_SCRIPT_DOUBLE
			.4byte \pointer1 @ text
			.4byte \pointer2 @ text
			.4byte \pointer3 @ text
			.4byte \pointer4 @ event script
		.elseif \type == TRAINER_BATTLE_REMATCH_DOUBLE
			.4byte \pointer1 @ text
			.4byte \pointer2 @ text
			.4byte \pointer3 @ text
		.elseif \type == TRAINER_BATTLE_CONTINUE_SCRIPT_DOUBLE_NO_MUSIC
			.4byte \pointer1 @ text
			.4byte \pointer2 @ text
			.4byte \pointer3 @ text
			.4byte \pointer4 @ event script
		.elseif \type == TRAINER_BATTLE_EARLY_RIVAL
			.4byte \pointer1 @ text
			.4byte \pointer2 @ text
		.endif
	.endm

	NO_MUSIC = FALSE

	@ Starts a single trainer battle. Takes a trainer, intro text, loss text, and an optional event script.
	@ When used with an event script, you can also pass in an optional flag to disable music
	.macro trainerbattle_single trainer:req, intro_text:req, lose_text:req, event_script=FALSE, music=TRUE
	.if \event_script == FALSE
	trainerbattle TRAINER_BATTLE_SINGLE, \trainer, 0, \intro_text, \lose_text
	.elseif \music == TRUE
	trainerbattle TRAINER_BATTLE_CONTINUE_SCRIPT, \trainer, 0, \intro_text, \lose_text, \event_script
	.else
	trainerbattle TRAINER_BATTLE_CONTINUE_SCRIPT_NO_MUSIC, \trainer, 0, \intro_text, \lose_text, \event_script
	.endif
	.endm

	@ Starts a double trainer battle. Takes a trainer, intro text, loss text, text for when you have too few pokemon
	@ and an optional event script. When used with an event script you can pass in an optional flag to disable music
	.macro trainerbattle_double trainer:req, intro_text:req, lose_text:req, not_enough_pkmn_text:req, event_script=FALSE, music=TRUE
	.if \event_script == FALSE
	trainerbattle TRAINER_BATTLE_DOUBLE, \trainer, 0, \intro_text, \lose_text, \not_enough_pkmn_text
	.elseif \music == TRUE
	trainerbattle TRAINER_BATTLE_CONTINUE_SCRIPT_DOUBLE, \trainer, 0, \intro_text, \lose_text, \not_enough_pkmn_text, \event_script
	.else
	trainerbattle TRAINER_BATTLE_CONTINUE_SCRIPT_DOUBLE_NO_MUSIC, \trainer, 0, \intro_text, \lose_text, \not_enough_pkmn_text, \event_script
	.endif
	.endm

	@ Starts a rematch battle, takes a trainer, intro text and loss text
	.macro trainerbattle_rematch trainer:req, intro_text:req, lose_text:req
	trainerbattle TRAINER_BATTLE_REMATCH, \trainer, 0, \intro_text, \lose_text
	.endm

	@ Starts a rematch double battle. Takes a trainer, intro text, loss text, and text for when you have too few pokemon
	.macro trainerbattle_rematch_double trainer:req, intro_text:req, lose_text:req, not_enough_pkmn_text:req
	trainerbattle TRAINER_BATTLE_REMATCH_DOUBLE, \trainer, 0, \intro_text, \lose_text, \not_enough_pkmn_text
	.endm

	@ Starts a trainer battle, skipping intro text. Takes a trainer and loss text
	.macro trainerbattle_no_intro trainer:req, lose_text:req
	trainerbattle TRAINER_BATTLE_SINGLE_NO_INTRO_TEXT, \trainer, 0, \lose_text
	.endm

	@ Starts a trainer battle with victory text if the player loses. If flags is nonzero, the player will be healed after battle (and its assumed to be the tutorial battle)
	.macro trainerbattle_earlyrival trainer:req, flags:req, defeat_text:req, victory_text:req
	trainerbattle TRAINER_BATTLE_EARLY_RIVAL, \trainer, \flags, \defeat_text, \victory_text
	.endm

	@ Starts a trainer battle using the battle information stored in RAM (usually by the scripts in trainer_battle.inc, which
	@ are run by trainerbattle), and blocks script execution until the battle finishes.
	.macro dotrainerbattle
	.byte 0x5d
	.endm

	@ Goes to address after the trainerbattle command (called by the battle functions, see battle_setup.c)
	.macro gotopostbattlescript
	.byte 0x5e
	.endm

	@ Goes to address specified in the trainerbattle command (called by the battle functions, see battle_setup.c)
	.macro gotobeatenscript
	.byte 0x5f
	.endm

	@ Checks if the trainer has been defeated by the player (by comparing the flag 'trainer + TRAINER_FLAGS_START' to TRUE).
	.macro checktrainerflag trainer:req
	.byte 0x60
	.2byte \trainer
	.endm

	@ Sets the trainer flag (trainer + TRAINER_FLAGS_START) to TRUE (defeated).
	.macro settrainerflag trainer:req
	.byte 0x61
	.2byte \trainer
	.endm

	@ Sets the trainer flag (trainer + TRAINER_FLAGS_START) to FALSE (not defeated).
	.macro cleartrainerflag trainer:req
	.byte 0x62
	.2byte \trainer
	.endm

	@ Sets the coordinates of an object's template, so that if the sprite goes off screen
	@ it'll still be there when it comes back on screen.
	.macro setobjectxyperm localId:req, x:req, y:req
	.byte 0x63
	.2byte \localId
	.2byte \x
	.2byte \y
	.endm

	@ Copies a live object event's xy position to its template, so that if the sprite goes off screen
	@ it'll still be there when it comes back on screen.
	.macro copyobjectxytoperm localId:req
	.byte 0x64
	.2byte \localId
	.endm

	@ Sets the movement type (MOVEMENT_TYPE_*) for an object's template.
	.macro setobjectmovementtype localId:req, movementType:req
	.byte 0x65
	.2byte \localId
	.byte \movementType
	.endm

	@ If a standard message box (or its text) is being drawn on-screen, this command blocks script execution until the
	@ box and its text have been fully drawn.
	.macro waitmessage
	.byte 0x66
	.endm

	@ Starts displaying a standard message box containing the specified text. If text is a pointer, then the string at
	@ that offset will be loaded and used. If text is NULL, then the value of script data 0 will be treated as
	@ a pointer to the text. The 'loadword 0' in msgbox sets this value, for instance.
	.macro message text:req
	.byte 0x67
	.4byte \text
	.endm

	@ Closes the current message box.
	.macro closemessage
	.byte 0x68
	.endm

	@ Freezes all objects immediately except the player. The player is frozen once their movement is finished.
	.macro lockall
	.byte 0x69
	.endm

	@ Freezes all objects immediately except the player and the selected object. The player and selected object are frozen once their movement is finished.
	.macro lock
	.byte 0x6a
	.endm

	@ Resumes normal movement for all objects on-screen, and closes any standard message boxes that are still open.
	.macro releaseall
	.byte 0x6b
	.endm

	@ Resumes normal movement for the selected object (if there is one) and the player. Also closes any standard message boxes that are still open.
	.macro release
	.byte 0x6c
	.endm

	@ Blocks script execution until the player presses the A or B button.
	.macro waitbuttonpress
	.byte 0x6d
	.endm

	@ Displays a YES/NO multichoice box at the specified coordinates, and blocks script execution until the user makes a selection.
	@ Their selection is stored in VAR_RESULT as NO (0) or YES (1). Pressing B is equivalent to answering NO
	.macro yesnobox x:req, y:req
	.byte 0x6e
	.byte \x
	.byte \y
	.endm

	@ Displays a multichoice box from which the user can choose a selection, and blocks script execution until a selection is made.
	@ Lists of options are predefined (sMultichoiceLists) and the one to be used is specified with multichoiceId.
	@ If ignoreBPress is set to a non-zero value, then the user will not be allowed to back out of the multichoice with the B button.
	.macro multichoice x:req, y:req, multichoiceId:req, ignoreBPress:req
	.byte 0x6f
	.byte \x
	.byte \y
	.byte \multichoiceId
	.byte \ignoreBPress
	.endm

	@ Displays a multichoice box from which the user can choose a selection, and blocks script execution until a selection is made.
	@ Lists of options are predefined (sMultichoiceLists) and the one to be used is specified with multichoiceId.
	@ The default argument determines the initial position of the cursor when the box is first opened; it is zero-indexed, and if it is too large, it is treated as 0.
	@ If ignoreBPress is set to a non-zero value, then the user will not be allowed to back out of the multichoice with the B button.
	.macro multichoicedefault x:req, y:req, multichoiceId:req, default:req, ignoreBPress:req
	.byte 0x70
	.byte \x
	.byte \y
	.byte \multichoiceId
	.byte \default
	.byte \ignoreBPress
	.endm

	@ Displays a multichoice box from which the user can choose a selection, and blocks script execution until a selection is made.
	@ Lists of options are predefined (sMultichoiceLists) and the one to be used is specified with multichoiceId.
	@ The per_row argument determines how many list items will be shown on a single row of the box.
	@ If ignoreBPress is set to a non-zero value, then the user will not be allowed to back out of the multichoice with the B button.
	.macro multichoicegrid x:req, y:req, multichoiceId:req, per_row:req, ignoreBPress:req
	.byte 0x71
	.byte \x
	.byte \y
	.byte \multichoiceId
	.byte \per_row
	.byte \ignoreBPress
	.endm

	@ In FRLG, this command is a nop.
	.macro drawbox
	.byte 0x72
	.endm

	@ In FRLG, this command is a nop. Still consumes parameters.
	.macro erasebox left:req, top:req, right:req, bottom:req
	.byte 0x73
	.byte \left
	.byte \top
	.byte \right
	.byte \bottom
	.endm

	@ In FRLG, this command is a nop. Still consumes parameters.
	.macro drawboxtext left:req, top:req, multichoiceId:req, ignoreBPress:req
	.byte 0x74
	.byte \left
	.byte \top
	.byte \multichoiceId
	.byte \ignoreBPress
	.endm

	@ Displays a box containing the front sprite for the specified Pokemon species and plays its cry.
	.macro showmonpic species:req, x:req, y:req
	.byte 0x75
	.2byte \species
	.byte \x
	.byte \y
	.endm

	@ Hides the box displayed by showmonpic.
	.macro hidemonpic
	.byte 0x76
	.endm

	@ In FRLG, this command is a nop. In RSE, draws an image of the winner of the contest. winnerId is any CONTEST_WINNER_* constant.
	.macro showcontestpainting winnerId:req
	.byte 0x77
	.byte \winnerId
	.endm

	@ Displays the given string as braille text in a standard message box. The string should use the .braille directive
	@ to convert text to braille, and be preceded by brailleformat. The brailleformat data is skipped over (in RS, these
	@ bytes determined the box's size and position, but in Emerald these are calculated automatically).
	.macro braillemessage text:req
	.byte 0x78
	.4byte \text
	.endm

	@ Formatting for the braille window, to be put at the start of a pointer used by braillemessage.
	.macro brailleformat winLeft:req, winTop:req, winRight:req, winBottom:req, textLeft:req, textTop:req
	.byte \winLeft
	.byte \winTop
	.byte \winRight
	.byte \winBottom
	.byte \textLeft
	.byte \textTop
	.endm

	@ Gives the player a Pokémon of the specified species and level, holding the specified item. The trailing 0s are unused parameters.
	@ VAR_RESULT will be set to MON_GIVEN_TO_PARTY, MON_GIVEN_TO_PC, or MON_CANT_GIVE depending on the outcome. 
	.macro givemon species:req, level:req, item=ITEM_NONE
	.byte 0x79
	.2byte \species
	.byte \level
	.2byte \item
	.4byte 0
	.4byte 0
	.byte 0
	.endm

	@ Gives the player an Egg of the specified species.
	@ VAR_RESULT will be set to MON_GIVEN_TO_PARTY, MON_GIVEN_TO_PC, or MON_CANT_GIVE depending on the outcome. 
	.macro giveegg species:req
	.byte 0x7a
	.2byte \species
	.endm

	@ Replaces the move at 'slot' of the Pokémon in the player's party at 'partyIndex' with the specified move.
	@ If a value greater than PARTY_SIZE is given for partyIndex it will use the last Pokémon in the party instead.
	@ Note that this means in vanilla a value equal to PARTY_SIZE for partyIndex will go out of bounds.
	.macro setmonmove partyIndex:req, slot:req, move:req
	.byte 0x7b
	.byte \partyIndex
	.byte \slot
	.2byte \move
	.endm

	@ Checks if at least one Pokemon in the player's party knows the specified move. If so, VAR_RESULT is set to the
	@ (zero-indexed) slot number of the first Pokemon that knows the move. If not, VAR_RESULT is set to PARTY_SIZE.
	@ VAR_0x8004 is also set to this Pokemon's species.
	.macro checkpartymove move:req
	.byte 0x7c
	.2byte \move
	.endm

	@ Converts STR_VAR_1, STR_VAR_2, or STR_VAR_3 to its corresponding index into sScriptStringVars (0, 1, or 2).
	@ If given anything else it will output it directly.
	@ Note: Because the STR_VAR_# arguments given to this macro are not part of a processed string they are not
	@       replaced with their charmap values, they are just passed as the literal characters "STR_VAR_#".
	.macro stringvar id:req
	.if \id == STR_VAR_1
		.byte 0
	.elseif \id == STR_VAR_2
		.byte 1
	.elseif \id == STR_VAR_3
		.byte 2
	.else
		.byte \id
	.endif
	.endm

	@ Writes the name of the given Pokemon species to the specified buffer.
	.macro bufferspeciesname stringVarId:req, species:req
	.byte 0x7d
	stringvar \stringVarId
	.2byte \species
	.endm

	@ Writes the name of the species of the first Pokemon in the player's party to the specified buffer.
	.macro bufferleadmonspeciesname stringVarId:req
	.byte 0x7e
	stringvar \stringVarId
	.endm

	@ Writes the nickname of the Pokemon in 'slot' (zero-indexed) of the player's party to the specified buffer.
	@ If an empty or invalid slot is specified, ten spaces ("") are written to the buffer.
	.macro bufferpartymonnick stringVarId:req, slot:req
	.byte 0x7f
	stringvar \stringVarId
	.2byte \slot
	.endm

	@ Writes the name of the specified item to the specified buffer. If itemId is >= ITEMS_COUNT,
	@ then the name of ITEM_NONE ("????????") is buffered instead.
	.macro bufferitemname stringVarId:req, item:req
	.byte 0x80
	stringvar \stringVarId
	.2byte \item
	.endm

	@ In FRLG, this command is a nop. In RSE, writes the name of the specified decoration to the specified buffer.
	.macro bufferdecorationname stringVarId:req, decoration:req
	.byte 0x81
	stringvar \stringVarId
	.2byte \decoration
	.endm

	@ Writes the name of the specified move to the specified buffer.
	.macro buffermovename stringVarId:req, move:req
	.byte 0x82
	stringvar \stringVarId
	.2byte \move
	.endm

	@ Converts the value of input to a decimal string, and writes that string to the specified buffer.
	.macro buffernumberstring stringVarId:req, input:req
	.byte 0x83
	stringvar \stringVarId
	.2byte \input
	.endm

	@ Writes the given standard string (STDSTRING_*) to the specified buffer. Invalid std string ids are not handled.
	.macro bufferstdstring stringVarId:req, index:req
	.byte 0x84
	stringvar \stringVarId
	.2byte \index
	.endm

	@ Copies the string at the given pointer to the specified buffer.
	.macro bufferstring stringVarId:req, text:req
	.byte 0x85
	stringvar \stringVarId
	.4byte \text
	.endm

	@ Opens the Pokemart system, offering the specified products for sale.
	@ Products should be a list of .2byte item values preceded by an .align 2
	.macro pokemart products:req
	.byte 0x86
	.4byte \products
	.endm

	@ Opens the Pokemart system and treats the list of items as decorations.
	@ Products should be a list of .2byte decoration values preceded by an .align 2
	.macro pokemartdecoration products:req
	.byte 0x87
	.4byte \products
	.endm

	@ Identical to pokemartdecoration, but with slight changes to the clerk dialogue. See uses of MART_TYPE_DECOR2.
	.macro pokemartdecoration2 products:req
	.byte 0x88
	.4byte \products
	.endm

	@ Starts up the slot machine minigame. id is a SLOT_MACHINE_* value that influences probabilities of certain reel outcomes.
	.macro playslotmachine id:req
	.byte 0x89
	.2byte \id
	.endm

	@ In FRLG, this command is a nop. In RSE, sets a berry tree's berry and growth stage.
	.macro setberrytree treeId:req, berry:req, growthStage:req
	.byte 0x8a
	.byte \treeId
	.byte \berry
	.byte \growthStage
	.endm

	@ In FRLG, this command is a nop. In RSE, opens the party menu to select a Pokemon for a contest.
	.macro choosecontestmon
	.byte 0x8b
	.endm

	@ In FRLG, this command is a nop. In RSE, starts the appeals round of a contest.
	.macro startcontest
	.byte 0x8c
	.endm

	@ In FRLG, this command is a nop. In RSE, shows the results screen of a contest.
	.macro showcontestresults
	.byte 0x8d
	.endm

	@ In FRLG, this command is a nop. In RSE, starts communication to initialize a link contest.
	.macro contestlinktransfer
	.byte 0x8e
	.endm

	@ Stores a random integer between 0 and limit (exclusive of limit) in VAR_RESULT.
	.macro random limit:req
	.byte 0x8f
	.2byte \limit
	.endm

	@ Adds value to the player's money. If adding 'value' money would exceed MAX_MONEY, the player's money is set to MAX_MONEY.
	@ If 'disable' is set to anything but 0 then this command does nothing.
	.macro addmoney value:req, disable=0
	.byte 0x90
	.4byte \value
	.byte \disable
	.endm

	@ Subtracts value from the player's money. If the player has less than 'value' money, their money is set to 0.
	@ If 'disable' is set to anything but 0 then this command does nothing.
	.macro removemoney value:req, disable=0
	.byte 0x91
	.4byte \value
	.byte \disable
	.endm

	@ Checks if the player has money >= value. VAR_RESULT is set to TRUE if the player has enough money, or FALSE if they do not.
	@ If 'disable' is set to anything but 0 then this command does nothing.
	.macro checkmoney value:req, disable=0
	.byte 0x92
	.4byte \value
	.byte \disable
	.endm

	@ Creates a window showing how much money the player has.
	@ If 'disable' is set to anything but 0 then this command does nothing.
	.macro showmoneybox x:req, y:req, disable=0
	.byte 0x93
	.byte \x
	.byte \y
	.byte \disable
	.endm

	@ Destroys the window created by showmoneybox. Consumption of the x and y arguments was dummied out.
	.macro hidemoneybox
	.byte 0x94
	.byte 0  @ \x
	.byte 0  @ \y
	.endm

	@ Updates the window created by showmoneybox. Consumption of the x and y arguments was dummied out.
	@ If 'disable' is set to anything but 0 then this command does nothing.
	.macro updatemoneybox disable=0
	.byte 0x95
	.byte 0  @ \x
	.byte 0  @ \y
	.byte \disable
	.endm

	@ In FRLG, this command is a nop. In RSE, gets whether the effects of the specified PokeNews program are active.
	.macro getpokenewsactive newsKind:req
	.byte 0x96
	.2byte \newsKind
	.endm

	@ Fades the screen to and from black and white. Modes are FADE_(TO/FROM)_(WHITE/BLACK)
	.macro fadescreen mode:req
	.byte 0x97
	.byte \mode
	.endm

	@ Fades the screen to and from black and white. Modes are FADE_(TO/FROM)_(WHITE/BLACK)
	.macro fadescreenspeed mode:req, speed:req
	.byte 0x98
	.byte \mode
	.byte \speed
	.endm

	@ Sets the flash level. A level of 0 is fully bright, a level of 1 is the largest flash radius, a level
	@ of 7 is the smallest flash radius, a level of 8 is fully black.
	.macro setflashlevel level:req
	.byte 0x99
	.2byte \level
	.endm

	@ Animates the flash radius from its current size to the size it would be at the specified level.
	@ Note that this does not actually change the current flash level. It's typically used just before a setflashlevel.
	.macro animateflash level:req
	.byte 0x9a
	.byte \level
	.endm

	@ Automatically scrolls through the message without player input and at a fixed speed.
	.macro messageautoscroll text:req
	.byte 0x9b
	.4byte \text
	.endm

	@ Executes the specified field effect animation (FLDEFF_*).
	.macro dofieldeffect animation:req
	.byte 0x9c
	.2byte \animation
	.endm

	@ Sets the field effect argument at index 'argNum' to 'value.'
	.macro setfieldeffectargument argNum:req, value:req
	.byte 0x9d
	.byte \argNum
	.2byte \value
	.endm

	@ Blocks script execution until all playing field effect animations complete.
	.macro waitfieldeffect animation:req
	.byte 0x9e
	.2byte \animation
	.endm

	@ Sets which healing place the player will return to if all of the Pokemon in their party faint.
	.macro setrespawn heallocation:req
	.byte 0x9f
	.2byte \heallocation
	.endm

	@ Checks the player's gender. Stores the result (MALE (0) or FEMALE (1)) in VAR_RESULT.
	.macro checkplayergender
	.byte 0xa0
	.endm

	@ Plays the cry of the given species. Mode is any CRY_MODE_* constant.
	@ You can use waitmoncry to block script execution until the cry finishes.
	.macro playmoncry species:req, mode:req
	.byte 0xa1
	.2byte \species
	.2byte \mode
	.endm

	@ Set the metatile at (x, y) on the current map to the given metatile and impassability.
	.macro setmetatile x:req, y:req, metatileId:req, impassable:req
	.byte 0xa2
	.2byte \x
	.2byte \y
	.2byte \metatileId
	.2byte \impassable
	.endm

	@ Queues a weather change to the default weather for the map.
	.macro resetweather
	.byte 0xa3
	.endm

	@ Queues a weather change to type weather.
	.macro setweather type:req
	.byte 0xa4
	.2byte \type
	.endm

	@ Executes the weather change queued with resetweather or setweather. The current weather will smoothly fade into the queued weather.
	.macro doweather
	.byte 0xa5
	.endm

	@ Enables the overworld task specified by stepCbId (STEP_CB_*). Only 1 can be active at a time. See src/field_tasks.c for more.
	.macro setstepcallback stepCbId:req
	.byte 0xa6
	.byte \stepCbId
	.endm

	@ Sets the current map layout to the one specified by index (LAYOUT_*).
	@ This should be done before the layout is loaded, typically in the ON_TRANSITION map script.
	.macro setmaplayoutindex index:req
	.byte 0xa7
	.2byte \index
	.endm

	@ Sets the specified object's sprite's subpriority, and sets fixedPriority to TRUE.
	@ Only used to hide the player and Briney behind the boat.
	.macro setobjectsubpriority localId:req, map:req, subpriority:req
	.byte 0xa8
	.2byte \localId
	map \map
	.byte \subpriority
	.endm

	@ Sets the specified object's fixedPriority to FALSE. Does not change the subpriority field.
	.macro resetobjectsubpriority localId:req, map:req
	.byte 0xa9
	.2byte \localId
	map \map
	.endm

	@ Creates a sprite with object graphics. Used when creating large groups of static NPCs that exceed the object event limit.
	@ The specified id can be used to refer to the sprite again later with turnvobject.
	.macro createvobject graphicsId:req, id:req, x:req, y:req, elevation=3, direction=DIR_SOUTH
	.byte 0xaa
	.byte \graphicsId
	.byte \id
	.2byte \x
	.2byte \y
	.byte \elevation
	.byte \direction
	.endm

	@ Turns a sprite created with createvobject.
	.macro turnvobject id:req, direction:req
	.byte 0xab
	.byte \id
	.byte \direction
	.endm

	@ Opens the door metatile at (x, y) with an animation.
	.macro opendoor x:req, y:req
	.byte 0xac
	.2byte \x
	.2byte \y
	.endm

	@ Closes the door metatile at (x, y) with an animation.
	.macro closedoor x:req, y:req
	.byte 0xad
	.2byte \x
	.2byte \y
	.endm

	@ Waits for the door animation started with opendoor or closedoor to finish.
	.macro waitdooranim
	.byte 0xae
	.endm

	@ Sets the door metatile at (x, y) to be open without an animation.
	.macro setdooropen x:req, y:req
	.byte 0xaf
	.2byte \x
	.2byte \y
	.endm

	@ Sets the door metatile at (x, y) to be closed without an animation.
	.macro setdoorclosed x:req, y:req
	.byte 0xb0
	.2byte \x
	.2byte \y
	.endm

	@ In FRLG, this command is a nop. It is implemented but unused in Ruby/Sapphire.
	.macro addelevmenuitem a:req, b:req, c:req, d:req
	.byte 0xb1
	.byte \a
	.2byte \b
	.2byte \c
	.2byte \d
	.endm

	@ In FRLG, this command is a nop. It is implemented but unused in Ruby/Sapphire.
	.macro showelevmenu
	.byte 0xb2
	.endm

	@ Gets the number of coins the player has and stores it in the variable 'out'.
	.macro checkcoins out:req
	.byte 0xb3
	.2byte \out
	.endm

	@ Gives 'count' coins to the player, up to a total of MAX_COINS. 
	@ If the player already has MAX_COINS then VAR_RESULT is set to TRUE, otherwise it is set to FALSE.
	.macro addcoins count:req
	.byte 0xb4
	.2byte \count
	.endm

	@ Takes 'count' coins from the player.
	@ If the player has fewer than 'count' coins then no coins are taken and VAR_RESULT is set to TRUE.
	@ Otherwise VAR_RESULT is set to FALSE.
	.macro removecoins count:req
	.byte 0xb5
	.2byte \count
	.endm

	@ Prepares to start a wild battle against a 'species' at 'level' holding 'item'. Running this command will not affect
	@ normal wild battles. You start the prepared battle with dowildbattle.
	.macro setwildbattle species:req, level:req, item=ITEM_NONE
	.byte 0xb6
	.2byte \species
	.byte \level
	.2byte \item
	.endm

	@ Starts a wild battle against the Pokemon generated by setwildbattle. Blocks script execution until the battle finishes.
	.macro dowildbattle
	.byte 0xb7
	.endm

	@ Sets a relative address to be used by the other vcommands as part of a Mystery Gift script.
	.macro setvaddress pointer:req
	.byte 0xb8
	.4byte \pointer
	.endm

	@ Equivalent to goto using the relative address set by setvaddress.
	.macro vgoto destination:req
	.byte 0xb9
	.4byte \destination
	.endm

	@ Equivalent to call using the relative address set by setvaddress.
	.macro vcall destination:req
	.byte 0xba
	.4byte \destination
	.endm

	@ Equivalent to goto_if using the relative address set by setvaddress.
	.macro vgoto_if condition:req, destination:req
	.byte 0xbb
	.byte \condition
	.4byte \destination
	.endm

	@ Equivalent to call_if using the relative address set by setvaddress.
	.macro vcall_if condition:req, destination:req
	.byte 0xbc
	.byte \condition
	.4byte \destination
	.endm

	@ Equivalent to message using the relative address set by setvaddress.
	.macro vmessage text:req
	.byte 0xbd
	.4byte \text
	.endm

	@ Expands the given text at the pointer (- the relative address set by setvaddress) into gStringVar4
	.macro vbuffermessage text:req
	.byte 0xbe
	.4byte \text
	.endm

	@ Equivalent to bufferstring using the relative address set by setvaddress.
	.macro vbufferstring stringVarIndex:req, text:req
	.byte 0xbf
	stringvar \stringVarIndex
	.4byte \text
	.endm

	@ Create a window showing how many Coins the player has.
	.macro showcoinsbox x:req, y:req
	.byte 0xc0
	.byte \x
	.byte \y
	.endm

	@ Destroys the window created by showcoins. It consumes its arguments but doesn't use them.
	.macro hidecoinsbox x:req, y:req
	.byte 0xc1
	.byte \x
	.byte \y
	.endm

	@ Updates the window created by showcoins. It consumes its arguments but doesn't use them.
	.macro updatecoinsbox x:req, y:req
	.byte 0xc2
	.byte \x
	.byte \y
	.endm

	@ Increases the value of the specified game stat by 1. The maximum value of a stat is 0xFFFFFF. See include/constants/game_stat.h
	.macro incrementgamestat stat:req
	.byte 0xc3
	.byte \stat
	.endm

	@ Sets the destination that using an Escape Rope or Dig will take the player to.
	@ Warp commands can be given either the id of which warp location to go to on the destination map
	@ or a pair of x/y coordinates to go to directly on the destination map.
	.macro setescapewarp map:req, a, b, c
	.byte 0xc4
	formatwarp \map, \a, \b, \c
	.endm

	@ Blocks script execution until cry finishes.
	.macro waitmoncry
	.byte 0xc5
	.endm

	@ Writes the name of the specified PC box to the specified buffer.
	.macro bufferboxname stringVarId:req, box:req
	.byte 0xc6
	stringvar \stringVarId
	.2byte \box
	.endm

	@ Sets the color of the text in standard message boxes. color is any NPC_TEXT_COLOR_* constant.
	@ The color will be reset to NPC_TEXT_COLOR_DEFAULT whenever ProcessPlayerFieldInput is called.
	.macro textcolor color:req
	.byte 0xc7
	.byte \color
	.endm

	@ Displays the help menu with the given text.
	.macro loadhelp msg:req
	.byte 0xc8
	.4byte \msg
	.endm

	@ Erases the help menu
	.macro unloadhelp
	.byte 0xc9
	.endm

	@ After using this command, all standard message boxes will use the signpost frame.
	.macro signmsg
	.byte 0xca
	.endm

	@ Ends the effects of signmsg, returning message box frames to normal.
	.macro normalmsg
	.byte 0xcb
	.endm

	@ Reads the value of the specified game stat and compares it to the specified value.
	@ Sets the script comparisonResult to 0 if stat < value, 1 if stat == value, and 2 if stat > value.
	.macro comparestat statId:req, value:req
	.byte 0xcc
	.byte \statId
	.4byte \value
	.endm

	@ Sets the modernFatefulEncounter bit for the Pokemon in the specified slot of the player's party.
	.macro setmonmodernfatefulencounter slot:req
	.byte 0xcd
	.2byte \slot
	.endm

	@ Checks if the modernFatefulEncounter bit is set for the Pokemon in the specified slot of the player's party. If it isn't set,
	@ VAR_RESULT is TRUE. If the bit is set (or if the specified slot is empty or invalid), VAR_RESULT is FALSE.
	.macro checkmonmodernfatefulencounter slot:req
	.byte 0xce
	.2byte \slot
	.endm

	@ Jumps to the ram script saved from a Wonder Card. If there is no valid saved Wonder Card or if the
	@ ram script is invalid then this does nothing.
	.macro trywondercardscript
	.byte 0xcf
	.endm

	@ Sets worldmapflag to 1. This allows the player to Fly to the corresponding map, if that map has a flightspot.
	.macro setworldmapflag worldmapflag:req
	.byte 0xd0
	.2byte \worldmapflag
	.endm

	@ Warps the player to the specified map using a teleport effect. Effect is similar to warpteleport, but
	@ this warp has no fade out and maintains the original facing direction.
	@ Warp commands can be given either the id of which warp location to go to on the destination map
	@ or a pair of x/y coordinates to go to directly on the destination map.
	.macro warpspinenter map:req, a, b, c
	.byte 0xd1
	formatwarp \map, \a, \b, \c
	.endm

	@ Changes the location where the player caught the Pokemon in the specified slot of their party.
	.macro setmonmetlocation slot:req, location:req
	.byte 0xd2
	.2byte \slot
	.byte \location
	.endm

	@ Gets the width of the specified message in the Braille font and sets the result to VAR_0x8004.
	.macro getbraillestringwidth msg:req
	.byte 0xd3
	.4byte \msg
	.endm

	@ Writes the name of the specified item to the specified buffer. If 'item' is a Berry or ITEM_POKE_BALL
	@ and if the quantity is 2 or more, the buffered string will be pluralized ("IES" or "S" appended).
	@ If the specified item is >= ITEMS_COUNT then the name of ITEM_NONE ("????????") is buffered instead.
	.macro bufferitemnameplural stringVarId:req, item:req, quantity:req
	.byte 0xd4
	stringvar \stringVarId
	.2byte \item
	.2byte \quantity
	.endm


@ Supplementary

	.macro goto_if_unset flag:req, dest:req
	checkflag \flag
	goto_if FALSE, \dest
	.endm

	.macro goto_if_set flag:req, dest:req
	checkflag \flag
	goto_if TRUE, \dest
	.endm

	@ Allows 'compare' followed by a conditional goto/call to be combined into a single statement.
	@ The following are examples of the two acceptable formats this facilitates:
	@ compare VAR_RESULT, TRUE
	@ goto_if_eq MyScript
	@ - or -
	@ goto_if_eq VAR_RESULT, TRUE, MyScript
	@
	@ The first two arguments to this macro are the base command, e.g. 'goto_if 1' for goto_if_eq.
	@ The remaining arguments 'a, b, c' depend on the format:
	@ For a single statement, 'a' and 'b' are the values to compare and 'c' is the destination pointer.
	@ For a statement preceded by a compare, 'a' is the destination pointer and 'b/c' are not provided.
	.macro trycompare jump:req, condition:req, a:req, b, c
	.ifnb \c
		compare \a, \b
		\jump \condition, \c
	.else
		\jump \condition, \a
	.endif
	.endm

	.macro goto_if_lt a:req, b, c @ LESS THAN
	trycompare goto_if, 0, \a, \b, \c
	.endm

	.macro goto_if_eq a:req, b, c @ EQUAL
	trycompare goto_if, 1, \a, \b, \c
	.endm

	.macro goto_if_gt a:req, b, c @ GREATER THAN
	trycompare goto_if, 2, \a, \b, \c
	.endm

	.macro goto_if_le a:req, b, c @ LESS THAN OR EQUAL
	trycompare goto_if, 3, \a, \b, \c
	.endm

	.macro goto_if_ge a:req, b, c @ GREATER THAN OR EQUAL
	trycompare goto_if, 4, \a, \b, \c
	.endm

	.macro goto_if_ne a:req, b, c @ NOT EQUAL
	trycompare goto_if, 5, \a, \b, \c
	.endm

	.macro call_if_unset flag:req, dest:req
	checkflag \flag
	call_if FALSE, \dest
	.endm

	.macro call_if_set flag:req, dest:req
	checkflag \flag
	call_if TRUE, \dest
	.endm

	.macro call_if_lt a:req, b, c @ LESS THAN
	trycompare call_if, 0, \a, \b, \c
	.endm

	.macro call_if_eq a:req, b, c @ EQUAL
	trycompare call_if, 1, \a, \b, \c
	.endm

	.macro call_if_gt a:req, b, c @ GREATER THAN
	trycompare call_if, 2, \a, \b, \c
	.endm

	.macro call_if_le a:req, b, c @ LESS THAN OR EQUAL
	trycompare call_if, 3, \a, \b, \c
	.endm

	.macro call_if_ge a:req, b, c @ GREATER THAN OR EQUAL
	trycompare call_if, 4, \a, \b, \c
	.endm

	.macro call_if_ne a:req, b, c @ NOT EQUAL
	trycompare call_if, 5, \a, \b, \c
	.endm

	.macro vgoto_if_eq a:req, b, c
	trycompare vgoto_if, TRUE, \a, \b, \c
	.endm

	.macro vgoto_if_ne a:req, b, c
	trycompare vgoto_if, FALSE, \a, \b, \c
	.endm

	.macro vgoto_if_set flag:req, dest:req
	checkflag \flag
	vgoto_if TRUE, \dest
	.endm

	.macro vgoto_if_unset flag:req, dest:req
	checkflag \flag
	vgoto_if FALSE, \dest
	.endm

	.macro goto_if_defeated trainer:req, dest:req
	checktrainerflag \trainer
	goto_if TRUE, \dest
	.endm

	.macro goto_if_not_defeated trainer:req, dest:req
	checktrainerflag \trainer
	goto_if FALSE, \dest
	.endm

	.macro call_if_defeated trainer:req, dest:req
	checktrainerflag \trainer
	call_if TRUE, \dest
	.endm

	.macro call_if_not_defeated trainer:req, dest:req
	checktrainerflag \trainer
	call_if FALSE, \dest
	.endm

	.macro switch var:req
	copyvar VAR_0x8000, \var
	.endm

	.macro case condition:req, dest:req
	compare VAR_0x8000, \condition
	goto_if_eq \dest
	.endm

	YES = 1
	NO  = 0

	@ Buffers the given text and calls the relevant standard message script (see gStdScripts).
	.macro msgbox text:req, type=MSGBOX_DEFAULT
	loadword 0, \text
	callstd \type
	.endm

	@ Gives 'amount' of the specified 'item' to the player and prints a message with fanfare.
	@ If the player doesn't have space for all the items then as many are added as possible, the
	@ message indicates there is no room, and VAR_RESULT is set to FALSE. 
	@ Otherwise VAR_RESULT is set to TRUE, and the message indicates they have received the item(s).
	.macro giveitem item:req, amount=1
	setorcopyvar VAR_0x8000, \item
	setorcopyvar VAR_0x8001, \amount
	callstd STD_OBTAIN_ITEM
	.endm

	@ For picking up items in the overworld. Similar to giveitem, but with different language and
	@ sets the flag of the last-talked to object (the item the player picked up).
	.macro finditem item:req, amount=1
	setorcopyvar VAR_0x8000, \item
	setorcopyvar VAR_0x8001, \amount
	callstd STD_FIND_ITEM
	.endm

	@ Prints the message "{PLAYER} put the {ITEM} in the {POCKET}." The item name is pluralized, if applicable.
	.macro putitemaway item:req, amount=1
	setorcopyvar VAR_0x8000, \item
	setorcopyvar VAR_0x8001, \amount
	callstd STD_PUT_ITEM_AWAY
	.endm

	@ Prints the provided message after playing the fanfare music (can only be MUS_LEVEL_UP or MUS_OBTAIN_KEY_ITEM).
	@ It then prints the message shown by using putitemaway.
	.macro msgreceiveditem msg:req, item:req, amount=1, fanfare=MUS_LEVEL_UP
	loadword 0, \msg
	setorcopyvar VAR_0x8000, \item
	setorcopyvar VAR_0x8001, \amount
	setorcopyvar VAR_0x8002, \fanfare
	callstd STD_RECEIVED_ITEM
	.endm

	@ Adds the specified item to the bag, then prints a message with fanfare. See description of msgreceiveditem.
	.macro giveitem_msg msg:req, item:req, amount=1, fanfare=MUS_LEVEL_UP
	additem \item, \amount
	msgreceiveditem \msg, \item, \amount, \fanfare
	.endm

	@ Depends on the provided function. With the default argument, unlocks the specified entry in the Fame Checker.
	.macro famechecker person:req, index:req, function=SetFlavorTextFlagFromSpecialVars
	setvar VAR_0x8004, \person
	setvar VAR_0x8005, \index
	special \function
	.endm

	@ Sets the 'defeated' flag for all trainers in the specified gym.
	.macro set_gym_trainers gym:req
	setvar VAR_0x8008, \gym
	call EventScript_SetGymTrainers
	.endm

	@ Jumps to dest if the Quest Log is currently showing playback scenes (dest is usually a release/end)
	.macro goto_if_questlog dest:req
	special GetQuestLogState
	compare VAR_RESULT, 2
	goto_if_eq \dest
	.endm

	@ Prints a braille message, then waits for users input.
	.macro braillemessage_wait text:req
	setvar VAR_0x8006, 0
	braillemessage \text
	getbraillestringwidth \text
	call EventScript_BrailleCursorWaitButton
	.endm

	@ Creates a Pokémon with the modernFatefulEncounter bit set for an encounter
	.macro seteventmon species:req, level:req, item=ITEM_NONE
	setvar VAR_0x8004, \species
	setvar VAR_0x8005, \level
	setvar VAR_0x8006, \item
	special CreateEnemyEventMon
	.endm
@ ===== END asm/macros/event.inc =====
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
	
	.align 2
MysteryEventScript_StampCard::
	setvaddress MysteryEventScript_StampCard
	setorcopyvar VAR_RESULT, 1
	specialvar VAR_0x8008, GetMysteryGiftCardStat
	setorcopyvar VAR_RESULT, 0
	specialvar VAR_0x8009, GetMysteryGiftCardStat
	subvar VAR_0x8008, VAR_0x8009
	buffernumberstring STR_VAR_1, VAR_0x8008
	lock
	faceplayer
	vmessage sText_MysteryGiftStampCard
	waitmessage
	waitbuttonpress
	release
	end

sText_MysteryGiftStampCard:
	.string "Thank you for using the STAMP CARD\n"
	.string "System.\p"
	.string "You have {STR_VAR_1} more to collect to\n"
	.string "fill your STAMP CARD.$"

MysteryEventScript_SurfPichu::
	setvaddress MysteryEventScript_SurfPichu
	vgoto_if_unset FLAG_MYSTERY_GIFT_DONE, SurfPichu_GiveIfPossible
	returnram

SurfPichu_GiveIfPossible:
	specialvar VAR_EVENT_PICHU_SLOT, CalculatePlayerPartyCount
	vgoto_if_eq VAR_EVENT_PICHU_SLOT, PARTY_SIZE, SurfPichu_FullParty
	setflag FLAG_MYSTERY_GIFT_DONE
	vcall SurfPichu_GiveEgg
	lock
	faceplayer
	vmessage sText_MysteryGiftEgg
	waitmessage
	waitbuttonpress
	playfanfare MUS_OBTAIN_ITEM
	waitfanfare
	release
	end

SurfPichu_FullParty:
	lock
	faceplayer
	vmessage sText_FullParty
	waitmessage
	waitbuttonpress
	release
	end

SurfPichu_GiveEgg:
	giveegg SPECIES_PICHU
	setmonmodernfatefulencounter VAR_EVENT_PICHU_SLOT
	setmonmetlocation VAR_EVENT_PICHU_SLOT, METLOC_FATEFUL_ENCOUNTER
	vgoto_if_eq VAR_EVENT_PICHU_SLOT, 1, SurfPichu_Slot1
	vgoto_if_eq VAR_EVENT_PICHU_SLOT, 2, SurfPichu_Slot2
	vgoto_if_eq VAR_EVENT_PICHU_SLOT, 3, SurfPichu_Slot3
	vgoto_if_eq VAR_EVENT_PICHU_SLOT, 4, SurfPichu_Slot4
	vgoto_if_eq VAR_EVENT_PICHU_SLOT, 5, SurfPichu_Slot5
	return

SurfPichu_Slot1:
	setmonmove 1, 2, MOVE_SURF
	return

SurfPichu_Slot2:
	setmonmove 2, 2, MOVE_SURF
	return

SurfPichu_Slot3:
	setmonmove 3, 2, MOVE_SURF
	return

SurfPichu_Slot4:
	setmonmove 4, 2, MOVE_SURF
	return

SurfPichu_Slot5:
	setmonmove 5, 2, MOVE_SURF
	return

sText_MysteryGiftEgg:
	.string "Thank you for using the MYSTERY\n"
	.string "GIFT System.\p"
	.string "From the POKéMON CENTER we\n"
	.string "have a gift - a POKéMON EGG!\p"
	.string "Please raise it with love and\n"
	.string "kindness.$"

sText_FullParty:
	.string "Oh, your party appears to be full.\p"
	.string "Please come see me after storing\n"
	.string "a POKéMON on a PC.$"

MysteryEventScript_VisitingTrainer::
	setvaddress MysteryEventScript_VisitingTrainer
	special ValidateEReaderTrainer
	vgoto_if_eq VAR_RESULT, 0, MysteryEventScript_VisitingTrainerArrived
	lock
	faceplayer
	vmessage sText_MysteryGiftVisitingTrainer
	waitmessage
	waitbuttonpress
	release
	end

MysteryEventScript_VisitingTrainerArrived:
	lock
	faceplayer
	vmessage sText_MysteryGiftVisitingTrainer_2
	waitmessage
	waitbuttonpress
	release
	end

sText_MysteryGiftVisitingTrainer:
	.string "Thank you for using the MYSTERY\n"
	.string "GIFT System.\p"
	.string "By holding this WONDER CARD, you\n"
	.string "may take part in a survey at a\l"
	.string "POKéMON MART.\p"
	.string "Use these surveys to invite\n"
	.string "TRAINERS to the SEVII ISLANDS.\p"
	.string "…Let me give you a secret\n"
	.string "password for a survey:\p"
	.string "“GIVE ME\n"
	.string "AWESOME TRAINER”\p"
	.string "Write that in on a survey and send\n"
	.string "it to the WIRELESS\l"
	.string "COMMUNICATION SYSTEM.$"

sText_MysteryGiftVisitingTrainer_2:
	.string "Thank you for using the MYSTERY\n"
	.string "GIFT System.\p"
	.string "A TRAINER has arrived in the SEVII\n"
	.string "ISLANDS looking for you.\p"
	.string "We hope you will enjoy\n"
	.string "battling the visiting TRAINER.\p"
	.string "You may invite other TRAINERS by\n"
	.string "entering other passwords.\p"
	.string "Try looking for other passwords\n"
	.string "that may work.$"

MysteryEventScript_BattleCard::
	setvaddress MysteryEventScript_BattleCard
	vgoto_if_set FLAG_MYSTERY_GIFT_DONE, MysteryEventScript_BattleCardInfo
	setorcopyvar VAR_RESULT, 2
	specialvar VAR_0x8008, GetMysteryGiftCardStat
	vgoto_if_ne VAR_0x8008, 3, MysteryEventScript_BattleCardInfo
	lock
	faceplayer
	vmessage sText_MysteryGiftBattleCountCard_2
	waitmessage
	waitbuttonpress
	giveitem ITEM_POTION
	release
	setflag FLAG_MYSTERY_GIFT_DONE
	end

MysteryEventScript_BattleCardInfo:
	lock
	faceplayer
	vmessage sText_MysteryGiftBattleCountCard
	waitmessage
	waitbuttonpress
	release
	end

sText_MysteryGiftBattleCountCard:
	.string "Thank you for using the MYSTERY\n"
	.string "GIFT System.\p"
	.string "Your BATTLE COUNT CARD keeps\n"
	.string "track of your battle record against\l"
	.string "TRAINERS with the same CARD.\p"
	.string "Look for and battle TRAINERS who\n"
	.string "have the same CARD as you.\p"
	.string "You may check the overall rankings\n"
	.string "by reading the NEWS.\p"
	.string "Please do give it a try!$"

sText_MysteryGiftBattleCountCard_2:
	.string "Thank you for using the MYSTERY\n"
	.string "GIFT System.\p"
	.string "Congratulations!\p"
	.string "You have won a prize for winning\n"
	.string "three battles!\p"
	.string "We hope you will be inspired to\n"
	.string "battle some more.$"

MysteryEventScript_AuroraTicket::
	setvaddress MysteryEventScript_AuroraTicket
	lock
	faceplayer
	vgoto_if_set FLAG_RECEIVED_AURORA_TICKET, AuroraTicket_Obtained
	vgoto_if_set FLAG_FOUGHT_DEOXYS, AuroraTicket_Obtained
	checkitem ITEM_AURORA_TICKET, 1
	vgoto_if_eq VAR_RESULT, TRUE, AuroraTicket_Obtained
	vmessage sText_AuroraTicket1
	waitmessage
	waitbuttonpress
	checkitemspace ITEM_AURORA_TICKET, 1
	vgoto_if_eq VAR_RESULT, FALSE, AuroraTicket_NoBagSpace
	giveitem ITEM_AURORA_TICKET
	setflag FLAG_ENABLE_SHIP_BIRTH_ISLAND
	setflag FLAG_RECEIVED_AURORA_TICKET
	vmessage sText_AuroraTicket2
	waitmessage
	waitbuttonpress
	release
	end

AuroraTicket_NoBagSpace:
	vmessage sText_AuroraTicketNoPlace
	waitmessage
	waitbuttonpress
	release
	end

AuroraTicket_Obtained:
	vmessage sText_AuroraTicketGot
	waitmessage
	waitbuttonpress
	release
	end

sText_AuroraTicket1:
	.string "Thank you for using the MYSTERY\n"
	.string "GIFT System.\p"
	.string "You must be {PLAYER}.\n"
	.string "There is a ticket here for you.$"

sText_AuroraTicket2:
	.string "It appears to be for use at the\n"
	.string "VERMILION CITY port.\p"
	.string "Why not give it a try and see what\n"
	.string "it is about?$"

sText_AuroraTicketGot:
	.string "Thank you for using the MYSTERY\n"
	.string "GIFT System.$"

sText_AuroraTicketNoPlace:
	.string "Oh, I'm sorry, {PLAYER}. Your BAG's\n"
	.string "KEY ITEMS POCKET is full.\p"
	.string "Please store something on your PC,\n"
	.string "then come back for this.$"

MysteryEventScript_MysticTicket::
	setvaddress MysteryEventScript_MysticTicket
	lock
	faceplayer
	vgoto_if_set FLAG_RECEIVED_MYSTIC_TICKET, MysticTicket_Obtained
	vgoto_if_set FLAG_FOUGHT_LUGIA, MysticTicket_Obtained
	vgoto_if_set FLAG_FOUGHT_HO_OH, MysticTicket_Obtained
	checkitem ITEM_MYSTIC_TICKET, 1
	vgoto_if_eq VAR_RESULT, TRUE, MysticTicket_Obtained
	vmessage sText_MysticTicket2
	waitmessage
	waitbuttonpress
	checkitemspace ITEM_MYSTIC_TICKET, 1
	vgoto_if_eq VAR_RESULT, FALSE, MysticTicket_NoBagSpace
	giveitem ITEM_MYSTIC_TICKET
	setflag FLAG_ENABLE_SHIP_NAVEL_ROCK
	setflag FLAG_RECEIVED_MYSTIC_TICKET
	vmessage sText_MysticTicket1
	waitmessage
	waitbuttonpress
	release
	end

MysticTicket_NoBagSpace:
	vmessage sText_MysticTicketNoPlace
	waitmessage
	waitbuttonpress
	release
	end

MysticTicket_Obtained:
	vmessage sText_MysticTicketGot
	waitmessage
	waitbuttonpress
	release
	end

sText_MysticTicket2:
	.string "Thank you for using the MYSTERY\n"
	.string "GIFT System.\p"
	.string "You must be {PLAYER}.\n"
	.string "There is a ticket here for you.$"

sText_MysticTicket1:
	.string "It appears to be for use at the\n"
	.string "VERMILION CITY port.\p"
	.string "Why not give it a try and see what\n"
	.string "it is about?$"

sText_MysticTicketGot:
	.string "Thank you for using the MYSTERY\n"
	.string "GIFT System.$"

sText_MysticTicketNoPlace:
	.string "Oh, I'm sorry, {PLAYER}. Your BAG's\n"
	.string "KEY ITEMS POCKET is full.\p"
	.string "Please store something on your PC,\n"
	.string "then come back for this.$"

MysteryEventScript_AlteringCave::
	setvaddress MysteryEventScript_AlteringCave
	addvar VAR_ALTERING_CAVE_WILD_SET, 1
	vgoto_if_ne VAR_ALTERING_CAVE_WILD_SET, 10, MysteryEventScript_AlteringCave_
	setvar VAR_ALTERING_CAVE_WILD_SET, 0
MysteryEventScript_AlteringCave_:
	lock
	faceplayer
	vmessage sText_MysteryGiftAlteringCave
	waitmessage
	waitbuttonpress
	release
	end

sText_MysteryGiftAlteringCave:
	.string "Thank you for using the MYSTERY\n"
	.string "GIFT System.\p"
	.string "Recently, there have been rumors\n"
	.string "of rare POKéMON appearances.\p"
	.string "The rumors are about ALTERING\n"
	.string "CAVE on OUTCAST ISLAND.\p"
	.string "Why not visit there and check if\n"
	.string "the rumors are indeed true?$"
