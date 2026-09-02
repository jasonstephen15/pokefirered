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
@ ===== BEGIN constants/m4a_constants.inc =====
	.equiv ID_NUMBER, 0x68736d53

	.equiv PCM_DMA_BUF_SIZE, 1584
	.equiv MAX_DIRECTSOUND_CHANNELS, 12

	.equiv C_V, 0x40

	.equiv TONEDATA_TYPE_CGB, 0x07
	.equiv TONEDATA_TYPE_FIX, 0x08
	.equiv TONEDATA_TYPE_REV, 0x10
	.equiv TONEDATA_TYPE_CMP, 0x20
	.equiv TONEDATA_TYPE_SPL, 0x40 @ key split
	.equiv TONEDATA_TYPE_RHY, 0x80 @ rhythm

	.equiv TONEDATA_P_S_PAN,  0xc0

	.equiv SOUND_CHANNEL_SF_START,       0x80
	.equiv SOUND_CHANNEL_SF_STOP,        0x40
	.equiv SOUND_CHANNEL_SF_SPECIAL,     0x20
	.equiv SOUND_CHANNEL_SF_LOOP,        0x10
	.equiv SOUND_CHANNEL_SF_IEC,         0x04
	.equiv SOUND_CHANNEL_SF_ENV,         0x03
	.equiv SOUND_CHANNEL_SF_ENV_ATTACK,  0x03
	.equiv SOUND_CHANNEL_SF_ENV_DECAY,   0x02
	.equiv SOUND_CHANNEL_SF_ENV_SUSTAIN, 0x01
	.equiv SOUND_CHANNEL_SF_ENV_RELEASE, 0x00
	.equiv SOUND_CHANNEL_SF_ON, (SOUND_CHANNEL_SF_START | SOUND_CHANNEL_SF_STOP | SOUND_CHANNEL_SF_IEC | SOUND_CHANNEL_SF_ENV)

	.equiv CGB_CHANNEL_MO_PIT, 0x02
	.equiv CGB_CHANNEL_MO_VOL, 0x01

	.equiv WAVE_DATA_FLAG_LOOP, 0xC0

	.equiv MPT_FLG_VOLSET, 0x01
	.equiv MPT_FLG_VOLCHG, 0x03
	.equiv MPT_FLG_PITSET, 0x04
	.equiv MPT_FLG_PITCHG, 0x0C
	.equiv MPT_FLG_START,  0x40
	.equiv MPT_FLG_EXIST,  0x80

	.macro struct_begin
	.struct 0
	.endm

	.macro struct_field name, size
\name:
	.struct \name + \size
	.endm

	struct_begin
	struct_field o_WaveData_type, 2
	struct_field o_WaveData_d1, 1
	struct_field o_WaveData_flags, 1
	struct_field o_WaveData_freq, 4
	struct_field o_WaveData_loopStart, 4
	struct_field o_WaveData_size, 4
	struct_field o_WaveData_data, 0
	struct_field WaveData_size, 0

	struct_begin
	struct_field o_ToneData_type, 1
	struct_field o_ToneData_key, 1
	struct_field o_ToneData_length, 1
	struct_field o_ToneData_pan_sweep, 1
	struct_field o_ToneData_wav, 4
	struct_field o_ToneData_attack, 1
	struct_field o_ToneData_decay, 1
	struct_field o_ToneData_sustain, 1
	struct_field o_ToneData_release, 1
	struct_field ToneData_size, 0

	struct_begin
	struct_field o_SoundInfo_ident, 4
	struct_field o_SoundInfo_pcmDmaCounter, 1
	struct_field o_SoundInfo_reverb, 1
	struct_field o_SoundInfo_maxChans, 1
	struct_field o_SoundInfo_masterVolume, 1
	struct_field o_SoundInfo_freq, 1
	struct_field o_SoundInfo_mode, 1
	struct_field o_SoundInfo_c15, 1
	struct_field o_SoundInfo_pcmDmaPeriod, 1
	struct_field o_SoundInfo_maxLines, 1
	struct_field o_SoundInfo_gap, 3
	struct_field o_SoundInfo_pcmSamplesPerVBlank, 4
	struct_field o_SoundInfo_pcmFreq, 4
	struct_field o_SoundInfo_divFreq, 4
	struct_field o_SoundInfo_cgbChans, 4
	struct_field o_SoundInfo_MPlayMainHead, 4
	struct_field o_SoundInfo_musicPlayerHead, 4
	struct_field o_SoundInfo_CgbSound, 4
	struct_field o_SoundInfo_CgbOscOff, 4
	struct_field o_SoundInfo_MidiKeyToCgbFreq, 4
	struct_field o_SoundInfo_MPlayJumpTable, 4
	struct_field o_SoundInfo_plynote, 4
	struct_field o_SoundInfo_ExtVolPit, 4
	struct_field o_SoundInfo_gap2, 16
	struct_field o_SoundInfo_chans, MAX_DIRECTSOUND_CHANNELS * 64
	struct_field o_SoundInfo_pcmBuffer, PCM_DMA_BUF_SIZE * 2
	struct_field SoundInfo_size, 0

	struct_begin
	struct_field o_SoundChannel_statusFlags, 1
	struct_field o_SoundChannel_type, 1
	struct_field o_SoundChannel_rightVolume, 1
	struct_field o_SoundChannel_leftVolume, 1
	struct_field o_SoundChannel_attack, 1
	struct_field o_SoundChannel_decay, 1
	struct_field o_SoundChannel_sustain, 1
	struct_field o_SoundChannel_release, 1
	struct_field o_SoundChannel_key, 1
	struct_field o_SoundChannel_envelopeVolume, 1
	struct_field o_SoundChannel_envelopeVolumeRight, 1
	struct_field o_SoundChannel_envelopeVolumeLeft, 1
	struct_field o_SoundChannel_pseudoEchoVolume, 1
	struct_field o_SoundChannel_pseudoEchoLength, 1
	struct_field o_SoundChannel_dummy1, 1
	struct_field o_SoundChannel_dummy2, 1
	struct_field o_SoundChannel_gateTime, 1
	struct_field o_SoundChannel_midiKey, 1
	struct_field o_SoundChannel_velocity, 1
	struct_field o_SoundChannel_priority, 1
	struct_field o_SoundChannel_rhythmPan, 1
	struct_field o_SoundChannel_dummy3, 3
	struct_field o_SoundChannel_count, 4
	struct_field o_SoundChannel_fw, 4
	struct_field o_SoundChannel_frequency, 4
	struct_field o_SoundChannel_wav, 4
	struct_field o_SoundChannel_currentPointer, 4
	struct_field o_SoundChannel_track, 4
	struct_field o_SoundChannel_prevChannelPointer, 4
	struct_field o_SoundChannel_nextChannelPointer, 4
	struct_field o_SoundChannel_dummy4, 4
	struct_field o_SoundChannel_xpi, 2
	struct_field o_SoundChannel_xpc, 2
	struct_field SoundChannel_size, 0

	struct_begin
	struct_field o_MusicPlayerTrack_flags, 1
	struct_field o_MusicPlayerTrack_wait, 1
	struct_field o_MusicPlayerTrack_patternLevel, 1
	struct_field o_MusicPlayerTrack_repN, 1
	struct_field o_MusicPlayerTrack_gateTime, 1
	struct_field o_MusicPlayerTrack_key, 1
	struct_field o_MusicPlayerTrack_velocity, 1
	struct_field o_MusicPlayerTrack_runningStatus, 1
	struct_field o_MusicPlayerTrack_keyM, 1
	struct_field o_MusicPlayerTrack_pitM, 1
	struct_field o_MusicPlayerTrack_keyShift, 1
	struct_field o_MusicPlayerTrack_keyShiftX, 1
	struct_field o_MusicPlayerTrack_tune, 1
	struct_field o_MusicPlayerTrack_pitX, 1
	struct_field o_MusicPlayerTrack_bend, 1
	struct_field o_MusicPlayerTrack_bendRange, 1
	struct_field o_MusicPlayerTrack_volMR, 1
	struct_field o_MusicPlayerTrack_volML, 1
	struct_field o_MusicPlayerTrack_vol, 1
	struct_field o_MusicPlayerTrack_volX, 1
	struct_field o_MusicPlayerTrack_pan, 1
	struct_field o_MusicPlayerTrack_panX, 1
	struct_field o_MusicPlayerTrack_modM, 1
	struct_field o_MusicPlayerTrack_mod, 1
	struct_field o_MusicPlayerTrack_modT, 1
	struct_field o_MusicPlayerTrack_lfoSpeed, 1
	struct_field o_MusicPlayerTrack_lfoSpeedC, 1
	struct_field o_MusicPlayerTrack_lfoDelay, 1
	struct_field o_MusicPlayerTrack_lfoDelayC, 1
	struct_field o_MusicPlayerTrack_priority, 1
	struct_field o_MusicPlayerTrack_pseudoEchoVolume, 1
	struct_field o_MusicPlayerTrack_pseudoEchoLength, 1
	struct_field o_MusicPlayerTrack_chan, 4
	struct_field o_MusicPlayerTrack_ToneData_type, 1
	struct_field o_MusicPlayerTrack_ToneData_key, 1
	struct_field o_MusicPlayerTrack_ToneData_length, 1
	struct_field o_MusicPlayerTrack_ToneData_pan_sweep, 1
	struct_field o_MusicPlayerTrack_ToneData_wav, 4
	struct_field o_MusicPlayerTrack_ToneData_attack, 1
	struct_field o_MusicPlayerTrack_ToneData_decay, 1
	struct_field o_MusicPlayerTrack_ToneData_sustain, 1
	struct_field o_MusicPlayerTrack_ToneData_release, 1
	struct_field o_MusicPlayerTrack_gap, 10
	struct_field o_MusicPlayerTrack_timer, 2
	struct_field o_MusicPlayerTrack_unk_3C, 4
	struct_field o_MusicPlayerTrack_cmdPtr, 4
	struct_field o_MusicPlayerTrack_patternStack, 12
	struct_field MusicPlayerTrack_size, 0

	.equiv o_MusicPlayerTrack_ToneData_keySplitTable, o_MusicPlayerTrack_ToneData_attack

	struct_begin
	struct_field o_MusicPlayerInfo_songHeader, 4
	struct_field o_MusicPlayerInfo_status, 4
	struct_field o_MusicPlayerInfo_trackCount, 1
	struct_field o_MusicPlayerInfo_priority, 1
	struct_field o_MusicPlayerInfo_cmd, 1
	struct_field o_MusicPlayerInfo_unk_B, 1
	struct_field o_MusicPlayerInfo_clock, 4
	struct_field o_MusicPlayerInfo_gap, 8
	struct_field o_MusicPlayerInfo_memAccArea, 4
	struct_field o_MusicPlayerInfo_tempoD, 2
	struct_field o_MusicPlayerInfo_tempoU, 2
	struct_field o_MusicPlayerInfo_tempoI, 2
	struct_field o_MusicPlayerInfo_tempoC, 2
	struct_field o_MusicPlayerInfo_fadeOI, 2
	struct_field o_MusicPlayerInfo_fadeOC, 2
	struct_field o_MusicPlayerInfo_fadeOV, 2
	struct_field o_MusicPlayerInfo_padding, 2
	struct_field o_MusicPlayerInfo_tracks, 4
	struct_field o_MusicPlayerInfo_tone, 4
	struct_field o_MusicPlayerInfo_ident, 4
	struct_field o_MusicPlayerInfo_func, 4
	struct_field o_MusicPlayerInfo_intp, 4
	struct_field MusicPlayerInfo_size, 0

	struct_begin
	struct_field o_CgbChannel_statusFlags, 1
	struct_field o_CgbChannel_type, 1
	struct_field o_CgbChannel_rightVolume, 1
	struct_field o_CgbChannel_leftVolume, 1
	struct_field o_CgbChannel_attack, 1
	struct_field o_CgbChannel_decay, 1
	struct_field o_CgbChannel_sustain, 1
	struct_field o_CgbChannel_release, 1
	struct_field o_CgbChannel_key, 1
	struct_field o_CgbChannel_envelopeVolume, 1
	struct_field o_CgbChannel_envelopeGoal, 1
	struct_field o_CgbChannel_envelopeCounter, 1
	struct_field o_CgbChannel_pseudoEchoVolume, 1
	struct_field o_CgbChannel_pseudoEchoLength, 1
	struct_field o_CgbChannel_dummy1, 1
	struct_field o_CgbChannel_dummy2, 1
	struct_field o_CgbChannel_gateTime, 1
	struct_field o_CgbChannel_midiKey, 1
	struct_field o_CgbChannel_velocity, 1
	struct_field o_CgbChannel_priority, 1
	struct_field o_CgbChannel_rhythmPan, 1
	struct_field o_CgbChannel_dummy3, 3
	struct_field o_CgbChannel_dummy5, 1
	struct_field o_CgbChannel_sustainGoal, 1
	struct_field o_CgbChannel_n4, 1
	struct_field o_CgbChannel_pan, 1
	struct_field o_CgbChannel_panMask, 1
	struct_field o_CgbChannel_modify, 1
	struct_field o_CgbChannel_length, 1
	struct_field o_CgbChannel_sweep, 1
	struct_field o_CgbChannel_frequency, 4
	struct_field o_CgbChannel_wavePointer, 4
	struct_field o_CgbChannel_currentPointer, 4
	struct_field o_CgbChannel_track, 4
	struct_field o_CgbChannel_prevChannelPointer, 4
	struct_field o_CgbChannel_nextChannelPointer, 4
	struct_field o_CgbChannel_dummy4, 8
	struct_field CgbChannel_size, 0
@ ===== END constants/m4a_constants.inc =====

	.syntax unified

	.text

	thumb_func_start umul3232H32
umul3232H32:
	adr r2, __umul3232H32
	bx r2
	.arm
__umul3232H32:
	umull r2, r3, r0, r1
	add r0, r3, 0
	bx lr
	thumb_func_end umul3232H32

	thumb_func_start SoundMain
SoundMain:
	ldr r0, lt_SOUND_INFO_PTR
	ldr r0, [r0]
	ldr r2, lt_ID_NUMBER
	ldr r3, [r0, o_SoundInfo_ident]
	cmp r2, r3
	beq SoundMain_1
	bx lr @ Exit the function if ident doesn't match ID_NUMBER.
SoundMain_1:
	adds r3, 1
	str r3, [r0, o_SoundInfo_ident]
	push {r4-r7,lr}
	mov r1, r8
	mov r2, r9
	mov r3, r10
	mov r4, r11
	push {r0-r4}
	sub sp, 0x18
	ldrb r1, [r0, o_SoundInfo_maxLines]
	cmp r1, 0 @ if maxLines is 0, there is no maximum
	beq SoundMain_3
	ldr r2, lt_REG_VCOUNT
	ldrb r2, [r2]
	cmp r2, VCOUNT_VBLANK
	bhs SoundMain_2
	adds r2, TOTAL_SCANLINES
SoundMain_2:
	adds r1, r2
SoundMain_3:
	str r1, [sp, 0x14]
	ldr r3, [r0, o_SoundInfo_MPlayMainHead]
	cmp r3, 0
	beq SoundMain_4
	ldr r0, [r0, o_SoundInfo_musicPlayerHead]
	bl _081DD25E
	ldr r0, [sp, 0x18]
SoundMain_4:
	ldr r3, [r0, o_SoundInfo_CgbSound]
	bl _081DD25E
	ldr r0, [sp, 0x18]
	ldr r3, [r0, o_SoundInfo_pcmSamplesPerVBlank]
	mov r8, r3
	ldr r5, lt_o_SoundInfo_pcmBuffer
	adds r5, r0
	ldrb r4, [r0, o_SoundInfo_pcmDmaCounter]
	subs r7, r4, 1
	bls SoundMain_5
	ldrb r1, [r0, o_SoundInfo_pcmDmaPeriod]
	subs r1, r7
	mov r2, r8
	muls r2, r1
	adds r5, r2
SoundMain_5:
	str r5, [sp, 0x8]
	ldr r6, lt_PCM_DMA_BUF_SIZE
	ldr r3, lt_SoundMainRAM_Buffer
	bx r3

	.align 2, 0
lt_SOUND_INFO_PTR:        .word SOUND_INFO_PTR
lt_ID_NUMBER:             .word ID_NUMBER
lt_SoundMainRAM_Buffer:   .word SoundMainRAM_Buffer + 1
lt_REG_VCOUNT:            .word REG_VCOUNT
lt_o_SoundInfo_pcmBuffer: .word o_SoundInfo_pcmBuffer
lt_PCM_DMA_BUF_SIZE:      .word PCM_DMA_BUF_SIZE
	thumb_func_end SoundMain

	thumb_func_start SoundMainRAM
SoundMainRAM:
	ldrb r3, [r0, o_SoundInfo_reverb]
	cmp r3, 0
	beq SoundMainRAM_NoReverb
	adr r1, SoundMainRAM_Reverb
	bx r1
	.arm
SoundMainRAM_Reverb:
	cmp r4, 0x2
	addeq r7, r0, o_SoundInfo_pcmBuffer
	addne r7, r5, r8
	mov r4, r8
_081DCEC4:
	ldrsb r0, [r5, r6]
	ldrsb r1, [r5]
	add r0, r0, r1
	ldrsb r1, [r7, r6]
	add r0, r0, r1
	ldrsb r1, [r7], 0x1
	add r0, r0, r1
	mul r1, r0, r3
	mov r0, r1, asr 9
	tst r0, 0x80
	addne r0, r0, 0x1
	strb r0, [r5, r6]
	strb r0, [r5], 0x1
	subs r4, r4, 0x1
	bgt _081DCEC4
	adr r0, _081DCF36 + 1 @ plus 1 because THUMB
	bx r0
	.thumb
SoundMainRAM_NoReverb:
	movs r0, 0
	mov r1, r8
	adds r6, r5
	lsrs r1, 3
	bcc SoundMainRAM_NoReverb_Ok
	stm r5!, {r0}
	stm r6!, {r0}
SoundMainRAM_NoReverb_Ok:
	lsrs r1, 1
	bcc SoundMainRAM_NoReverb_Loop
	stm r5!, {r0}
	stm r6!, {r0}
	stm r5!, {r0}
	stm r6!, {r0}
SoundMainRAM_NoReverb_Loop:
	stm r5!, {r0}
	stm r6!, {r0}
	stm r5!, {r0}
	stm r6!, {r0}
	stm r5!, {r0}
	stm r6!, {r0}
	stm r5!, {r0}
	stm r6!, {r0}
	subs r1, 1
	bgt SoundMainRAM_NoReverb_Loop
_081DCF36:
	ldr r4, [sp, 0x18]
	ldr r0, [r4, o_SoundInfo_divFreq]
	mov r12, r0
	ldrb r0, [r4, o_SoundInfo_maxChans]
	adds r4, o_SoundInfo_chans

SoundMainRAM_ChanLoop:
	str r0, [sp, 0x4]
	ldr r3, [r4, o_SoundChannel_wav]
	ldr r0, [sp, 0x14]
	cmp r0, 0
	beq _081DCF60
	ldr r1, =REG_VCOUNT
	ldrb r1, [r1]
	cmp r1, VCOUNT_VBLANK
	bhs _081DCF54
	adds r1, TOTAL_SCANLINES
_081DCF54:
	cmp r1, r0
	blo _081DCF60
	b _081DD24A

	.pool

_081DCF60:
	ldrb r6, [r4, o_SoundChannel_statusFlags]
	movs r0, SOUND_CHANNEL_SF_ON
	tst r0, r6
	bne _081DCF6A
	b _081DD240
_081DCF6A:
	movs r0, SOUND_CHANNEL_SF_START
	tst r0, r6
	beq _081DCFA0
	movs r0, SOUND_CHANNEL_SF_STOP
	tst r0, r6
	bne _081DCFB0
	movs r6, SOUND_CHANNEL_SF_ENV_ATTACK
	strb r6, [r4, o_SoundChannel_statusFlags]
	adds r0, r3, 0
	adds r0, o_WaveData_data
	ldr r1, [r4, o_SoundChannel_count]
	adds r0, r1
	str r0, [r4, o_SoundChannel_currentPointer]
	ldr r0, [r3, o_WaveData_size]
	subs r0, r1
	str r0, [r4, o_SoundChannel_count]
	movs r5, 0
	strb r5, [r4, o_SoundChannel_envelopeVolume]
	str r5, [r4, o_SoundChannel_fw]
	ldrb r2, [r3, o_WaveData_flags]
	movs r0, WAVE_DATA_FLAG_LOOP
	tst r0, r2
	beq _081DCFF8
	movs r0, SOUND_CHANNEL_SF_LOOP
	orrs r6, r0
	strb r6, [r4, o_SoundChannel_statusFlags]
	b _081DCFF8
_081DCFA0:
	ldrb r5, [r4, o_SoundChannel_envelopeVolume]
	movs r0, SOUND_CHANNEL_SF_IEC
	tst r0, r6
	beq _081DCFB6
	ldrb r0, [r4, o_SoundChannel_pseudoEchoLength]
	subs r0, 1
	strb r0, [r4, o_SoundChannel_pseudoEchoLength]
	bhi _081DD006
_081DCFB0:
	movs r0, 0
	strb r0, [r4, o_SoundChannel_statusFlags]
	b _081DD240
_081DCFB6:
	movs r0, SOUND_CHANNEL_SF_STOP
	tst r0, r6
	beq _081DCFD6
	ldrb r0, [r4, o_SoundChannel_release]
	muls r5, r0
	lsrs r5, 8
	ldrb r0, [r4, o_SoundChannel_pseudoEchoVolume]
	cmp r5, r0
	bhi _081DD006
_081DCFC8:
	ldrb r5, [r4, o_SoundChannel_pseudoEchoVolume]
	cmp r5, 0
	beq _081DCFB0
	movs r0, SOUND_CHANNEL_SF_IEC
	orrs r6, r0
	strb r6, [r4, o_SoundChannel_statusFlags]
	b _081DD006
_081DCFD6:
	movs r2, SOUND_CHANNEL_SF_ENV
	ands r2, r6
	cmp r2, SOUND_CHANNEL_SF_ENV_DECAY
	bne _081DCFF4
	ldrb r0, [r4, o_SoundChannel_decay]
	muls r5, r0
	lsrs r5, 8
	ldrb r0, [r4, o_SoundChannel_sustain]
	cmp r5, r0
	bhi _081DD006
	adds r5, r0, 0
	beq _081DCFC8
	subs r6, 0x1
	strb r6, [r4, o_SoundChannel_statusFlags]
	b _081DD006
_081DCFF4:
	cmp r2, SOUND_CHANNEL_SF_ENV_ATTACK
	bne _081DD006
_081DCFF8:
	ldrb r0, [r4, o_SoundChannel_attack]
	adds r5, r0
	cmp r5, 0xFF
	bcc _081DD006
	movs r5, 0xFF
	subs r6, 0x1
	strb r6, [r4, o_SoundChannel_statusFlags]
_081DD006:
	strb r5, [r4, o_SoundChannel_envelopeVolume]
	ldr r0, [sp, 0x18]
	ldrb r0, [r0, o_SoundChannel_release]
	adds r0, 0x1
	muls r0, r5
	lsrs r5, r0, 4
	ldrb r0, [r4, o_SoundChannel_rightVolume]
	muls r0, r5
	lsrs r0, 8
	strb r0, [r4, o_SoundChannel_envelopeVolumeRight]
	ldrb r0, [r4, o_SoundChannel_leftVolume]
	muls r0, r5
	lsrs r0, 8
	strb r0, [r4, o_SoundChannel_envelopeVolumeLeft]
	movs r0, SOUND_CHANNEL_SF_LOOP
	ands r0, r6
	str r0, [sp, 0x10]
	beq _081DD03A
	adds r0, r3, 0
	adds r0, o_WaveData_data
	ldr r1, [r3, o_WaveData_loopStart]
	adds r0, r1
	str r0, [sp, 0xC]
	ldr r0, [r3, o_WaveData_size]
	subs r0, r1
	str r0, [sp, 0x10]
_081DD03A:
	ldr r5, [sp, 0x8]
	ldr r2, [r4, o_SoundChannel_count]
	ldr r3, [r4, o_SoundChannel_currentPointer]
	adr r0, _081DD044
	bx r0
	.arm
_081DD044:
	str r8, [sp]
	ldr r9, [r4, o_SoundChannel_fw]
	ldrb r10, [r4, o_SoundChannel_envelopeVolumeRight]
	ldrb r11, [r4, o_SoundChannel_envelopeVolumeLeft]
	ldrb r0, [r4, o_SoundChannel_type]
	tst r0, TONEDATA_TYPE_CMP | TONEDATA_TYPE_REV
	beq _081DD068
	bl SoundMainRAM_Unk1
	b _081DD228
_081DD068:
	mov r10, r10, lsl 16
	mov r11, r11, lsl 16
	ldrb r0, [r4, o_SoundChannel_type]
	tst r0, 0x8
	beq _081DD19C
_081DD07C:
	cmp r2, 0x4
	ble _081DD0EC
	subs r2, r2, r8
	movgt r9, 0
	bgt _081DD0A8
	mov r9, r8
	add r2, r2, r8
	sub r8, r2, 0x4
	sub r9, r9, r8
	ands r2, r2, 0x3
	moveq r2, 0x4
_081DD0A8:
	ldr r6, [r5]
	ldr r7, [r5, PCM_DMA_BUF_SIZE]
_081DD0B0:
	ldrsb r0, [r3], 0x1
	mul r1, r10, r0
	bic r1, r1, 0xFF0000
	add r6, r1, r6, ror 8
	mul r1, r11, r0
	bic r1, r1, 0xFF0000
	add r7, r1, r7, ror 8
	adds r5, r5, 0x40000000
	bcc _081DD0B0
	str r7, [r5, PCM_DMA_BUF_SIZE]
	str r6, [r5], 0x4
	subs r8, r8, 0x4
	bgt _081DD0A8
	adds r8, r8, r9
	beq _081DD22C
_081DD0EC:
	ldr r6, [r5]
	ldr r7, [r5, PCM_DMA_BUF_SIZE]
_081DD0F4:
	ldrsb r0, [r3], 0x1
	mul r1, r10, r0
	bic r1, r1, 0xFF0000
	add r6, r1, r6, ror 8
	mul r1, r11, r0
	bic r1, r1, 0xFF0000
	add r7, r1, r7, ror 8
	subs r2, r2, 0x1
	beq _081DD164
_081DD118:
	adds r5, r5, 0x40000000
	bcc _081DD0F4
	str r7, [r5, PCM_DMA_BUF_SIZE]
	str r6, [r5], 0x4
	subs r8, r8, 0x4
	bgt _081DD07C
	b _081DD22C
_081DD134:
	ldr r0, [sp, 0x18]
	cmp r0, 0
	beq _081DD158
	ldr r3, [sp, 0x14]
	rsb lr, r2, 0
_081DD148:
	adds r2, r0, r2
	bgt _081DD1FC
	sub lr, lr, r0
	b _081DD148
_081DD158:
	pop {r4,r12}
	mov r2, 0
	b _081DD174
_081DD164:
	ldr r2, [sp, 0x10]
	cmp r2, 0
	ldrne r3, [sp, 0xC]
	bne _081DD118
_081DD174:
	strb r2, [r4, o_SoundChannel_statusFlags]
	mov r0, r5, lsr 30
	bic r5, r5, 0xC0000000
	rsb r0, r0, 0x3
	mov r0, r0, lsl 3
	mov r6, r6, ror r0
	mov r7, r7, ror r0
	str r7, [r5, PCM_DMA_BUF_SIZE]
	str r6, [r5], 0x4
	b _081DD234
_081DD19C:
	push {r4,r12}
	ldr r1, [r4, o_SoundChannel_frequency]
	mul r4, r12, r1
	ldrsb r0, [r3]
	ldrsb r1, [r3, 0x1]!
	sub r1, r1, r0
_081DD1B4:
	ldr r6, [r5]
	ldr r7, [r5, PCM_DMA_BUF_SIZE]
_081DD1BC:
	mul lr, r9, r1
	add lr, r0, lr, asr 23
	mul r12, r10, lr
	bic r12, r12, 0xFF0000
	add r6, r12, r6, ror 8
	mul r12, r11, lr
	bic r12, r12, 0xFF0000
	add r7, r12, r7, ror 8
	add r9, r9, r4
	movs lr, r9, lsr 23
	beq _081DD208
	bic r9, r9, 0x3F800000
	subs r2, r2, lr
	ble _081DD134
	subs lr, lr, 0x1
	addeq r0, r0, r1
_081DD1FC:
	ldrsbne r0, [r3, lr]!
	ldrsb r1, [r3, 0x1]!
	sub r1, r1, r0
_081DD208:
	adds r5, r5, 0x40000000
	bcc _081DD1BC
	str r7, [r5, PCM_DMA_BUF_SIZE]
	str r6, [r5], 0x4
	subs r8, r8, 0x4
	bgt _081DD1B4
	sub r3, r3, 0x1
	pop {r4,r12}
_081DD228:
	str r9, [r4, o_SoundChannel_fw]
_081DD22C:
	str r2, [r4, o_SoundChannel_count]
	str r3, [r4, o_SoundChannel_currentPointer]
_081DD234:
	ldr r8, [sp]
	add r0, pc, 0x1
	bx r0
	.thumb
_081DD240:
	ldr r0, [sp, 0x4]
	subs r0, 1
	ble _081DD24A
	adds r4, SoundChannel_size
	b SoundMainRAM_ChanLoop
_081DD24A:
	ldr r0, [sp, 0x18]
	ldr r3, =ID_NUMBER
	str r3, [r0]
	add sp, 0x1C
	pop {r0-r7}
	mov r8, r0
	mov r9, r1
	mov r10, r2
	mov r11, r3
	pop {r3}
_081DD25E:
	bx r3
	.pool
	thumb_func_end SoundMainRAM

@ Not present in GBA SDK 3.0
	arm_func_start SoundMainRAM_Unk1
SoundMainRAM_Unk1:
	ldr r6, [r4, o_SoundChannel_wav]
	ldrb r0, [r4, o_SoundChannel_statusFlags]
	tst r0, SOUND_CHANNEL_SF_SPECIAL
	bne _081DD2B4
	orr r0, r0, SOUND_CHANNEL_SF_SPECIAL
	strb r0, [r4, o_SoundChannel_statusFlags]
	ldrb r0, [r4, o_SoundChannel_type]
	tst r0, TONEDATA_TYPE_REV
	beq _081DD29C
	ldr r1, [r6, o_WaveData_size]
	add r1, r1, r6, lsl 1
	add r1, r1, 0x20
	sub r3, r1, r3
	str r3, [r4, o_SoundChannel_currentPointer]
_081DD29C:
	ldrh r0, [r6, o_WaveData_type]
	cmp r0, 0
	beq _081DD2B4
	sub r3, r3, r6
	sub r3, r3, 0x10
	str r3, [r4, o_SoundChannel_currentPointer]
_081DD2B4:
	push {r8,r12,lr}
	mov r10, r10, lsl 16
	mov r11, r11, lsl 16
	ldr r1, [r4, o_SoundChannel_frequency]
	ldrb r0, [r4, o_SoundChannel_type]
	tst r0, TONEDATA_TYPE_FIX
	movne r8, 0x800000
	muleq r8, r12, r1
	ldrh r0, [r6, o_WaveData_type]
	cmp r0, 0
	beq _081DD468
	mov r0, 0xFF000000
	str r0, [r4, o_SoundChannel_xpi]
	ldrb r0, [r4, o_SoundChannel_type]
	tst r0, TONEDATA_TYPE_REV
	bne _081DD3C0
	bl SoundMainRAM_Unk2
	mov r0, r1
	add r3, r3, 0x1
	bl SoundMainRAM_Unk2
	sub r1, r1, r0
_081DD308:
	ldr r6, [r5]
	ldr r7, [r5, PCM_DMA_BUF_SIZE]
_081DD310:
	mul lr, r9, r1
	add lr, r0, lr, asr 23
	mul r12, r10, lr
	bic r12, r12, 0xFF0000
	add r6, r12, r6, ror 8
	mul r12, r11, lr
	bic r12, r12, 0xFF0000
	add r7, r12, r7, ror 8
	add r9, r9, r8
	movs lr, r9, lsr 23
	beq _081DD370
	bic r9, r9, 0x3F800000
	subs r2, r2, lr
	ble _081DD398
	subs lr, lr, 0x1
	bne _081DD358
	add r0, r0, r1
	b _081DD364
_081DD358:
	add r3, r3, lr
	bl SoundMainRAM_Unk2
	mov r0, r1
_081DD364:
	add r3, r3, 0x1
	bl SoundMainRAM_Unk2
	sub r1, r1, r0
_081DD370:
	adds r5, r5, 0x40000000
	bcc _081DD310
	str r7, [r5, PCM_DMA_BUF_SIZE]
	str r6, [r5], 0x4
	ldr r6, [sp]
	subs r6, r6, 0x4
	str r6, [sp]
	bgt _081DD308
	sub r3, r3, 0x1
	b _081DD4F0
_081DD398:
	ldr r0, [sp, 0x1C]
	cmp r0, 0
	beq _081DD4F4
	ldr r3, [r4, o_SoundChannel_wav]
	ldr r3, [r3, o_WaveData_loopStart]
	rsb lr, r2, 0
_081DD3B0:
	adds r2, r2, r0
	bgt _081DD358
	sub lr, lr, r0
	b _081DD3B0
_081DD3C0:
	sub r3, r3, 0x1
	bl SoundMainRAM_Unk2
	mov r0, r1
	sub r3, r3, 0x1
	bl SoundMainRAM_Unk2
	sub r1, r1, r0
_081DD3D8:
	ldr r6, [r5]
	ldr r7, [r5, PCM_DMA_BUF_SIZE]
_081DD3E0:
	mul lr, r9, r1
	add lr, r0, lr, asr 23
	mul r12, r10, lr
	bic r12, r12, 0xFF0000
	add r6, r12, r6, ror 8
	mul r12, r11, lr
	bic r12, r12, 0xFF0000
	add r7, r12, r7, ror 8
	add r9, r9, r8
	movs lr, r9, lsr 23
	beq _081DD440
	bic r9, r9, 0x3F800000
	subs r2, r2, lr
	ble _081DD4F4
	subs lr, lr, 0x1
	bne _081DD428
	add r0, r0, r1
	b _081DD434
_081DD428:
	sub r3, r3, lr
	bl SoundMainRAM_Unk2
	mov r0, r1
_081DD434:
	sub r3, r3, 0x1
	bl SoundMainRAM_Unk2
	sub r1, r1, r0
_081DD440:
	adds r5, r5, 0x40000000
	bcc _081DD3E0
	str r7, [r5, PCM_DMA_BUF_SIZE]
	str r6, [r5], 0x4
	ldr r6, [sp]
	subs r6, r6, 0x4
	str r6, [sp]
	bgt _081DD3D8
	add r3, r3, 0x2
	b _081DD4F0
_081DD468:
	ldrb r0, [r4, o_SoundChannel_type]
	tst r0, TONEDATA_TYPE_REV
	beq _081DD4F0
	ldrsb r0, [r3, -0x1]!
	ldrsb r1, [r3, -0x1]
	sub r1, r1, r0
_081DD480:
	ldr r6, [r5]
	ldr r7, [r5, 0x630]
_081DD488:
	mul lr, r9, r1
	add lr, r0, lr, asr 23
	mul r12, r10, lr
	bic r12, r12, 0xFF0000
	add r6, r12, r6, ror 8
	mul r12, r11, lr
	bic r12, r12, 0xFF0000
	add r7, r12, r7, ror 8
	add r9, r9, r8
	movs lr, r9, lsr 23
	beq _081DD4CC
	bic r9, r9, 0x3F800000
	subs r2, r2, lr
	ble _081DD4F4
	ldrsb r0, [r3, -lr]!
	ldrsb r1, [r3, -0x1]
	sub r1, r1, r0
_081DD4CC:
	adds r5, r5, 0x40000000
	bcc _081DD488
	str r7, [r5, 0x630]
	str r6, [r5], 0x4
	ldr r6, [sp]
	subs r6, r6, 0x4
	str r6, [sp]
	bgt _081DD480
	add r3, r3, 0x1
_081DD4F0:
	pop {r8,r12,pc}
_081DD4F4:
	mov r2, 0
	strb r2, [r4, o_SoundChannel_statusFlags]
	mov r0, r5, lsr 30
	bic r5, r5, 0xC0000000
	rsb r0, r0, 0x3
	mov r0, r0, lsl 3
	mov r6, r6, ror r0
	mov r7, r7, ror r0
	str r7, [r5, 0x630]
	str r6, [r5], 0x4
	pop {r8,r12,pc}
	arm_func_end SoundMainRAM_Unk1

@ Not present in GBA SDK 3.0
	arm_func_start SoundMainRAM_Unk2
SoundMainRAM_Unk2:
	push {r0,r2,r5-r7,lr}
	mov r0, r3, lsr 6
	ldr r1, [r4, o_SoundChannel_xpi]
	cmp r0, r1
	beq _081DD594
	str r0, [r4, o_SoundChannel_xpi]
	mov r1, 0x21
	mul r2, r1, r0
	ldr r1, [r4, o_SoundChannel_wav]
	add r2, r2, r1
	add r2, r2, 0x10
	ldr r5, =sDecodingBuffer
	ldr r6, =gDeltaEncodingTable
	mov r7, 0x40
	ldrb lr, [r2], 1
	strb lr, [r5], 1
	ldrb r1, [r2], 1
	b _081DD57C
_081DD568:
	ldrb r1, [r2], 1
	mov r0, r1, lsr 4
	ldrsb r0, [r6, r0]
	add lr, lr, r0
	strb lr, [r5], 1
_081DD57C:
	and r0, r1, 0xF
	ldrsb r0, [r6, r0]
	add lr, lr, r0
	strb lr, [r5], 1
	subs r7, r7, 2
	bgt _081DD568
_081DD594:
	ldr r5, =sDecodingBuffer
	and r0, r3, 0x3F
	ldrsb r1, [r5, r0]
	pop {r0,r2,r5-r7,pc}
	.pool
	arm_func_end SoundMainRAM_Unk2

	thumb_func_start SoundMainBTM
SoundMainBTM:
	mov r12, r4
	movs r1, 0
	movs r2, 0
	movs r3, 0
	movs r4, 0
	stm r0!, {r1-r4}
	stm r0!, {r1-r4}
	stm r0!, {r1-r4}
	stm r0!, {r1-r4}
	mov r4, r12
	bx lr
	thumb_func_end SoundMainBTM

	thumb_func_start RealClearChain
RealClearChain:
	ldr r3, [r0, o_SoundChannel_track]
	cmp r3, 0
	beq _081DD5E2
	ldr r1, [r0, o_SoundChannel_nextChannelPointer]
	ldr r2, [r0, o_SoundChannel_prevChannelPointer]
	cmp r2, 0
	beq _081DD5D6
	str r1, [r2, o_SoundChannel_nextChannelPointer]
	b _081DD5D8
_081DD5D6:
	str r1, [r3, o_MusicPlayerTrack_chan]
_081DD5D8:
	cmp r1, 0
	beq _081DD5DE
	str r2, [r1, o_SoundChannel_prevChannelPointer]
_081DD5DE:
	movs r1, 0
	str r1, [r0, o_SoundChannel_track]
_081DD5E2:
	bx lr
	thumb_func_end RealClearChain

	thumb_func_start ply_fine
ply_fine:
	push {r4,r5,lr}
	adds r5, r1, 0
	ldr r4, [r5, o_MusicPlayerTrack_chan]
	cmp r4, 0
	beq ply_fine_done
ply_fine_loop:
	ldrb r1, [r4, o_SoundChannel_statusFlags]
	movs r0, SOUND_CHANNEL_SF_ON
	tst r0, r1
	beq ply_fine_ok
	movs r0, SOUND_CHANNEL_SF_STOP
	orrs r1, r0
	strb r1, [r4, o_SoundChannel_statusFlags]
ply_fine_ok:
	adds r0, r4, 0
	bl RealClearChain
	ldr r4, [r4, o_SoundChannel_nextChannelPointer]
	cmp r4, 0
	bne ply_fine_loop
ply_fine_done:
	movs r0, 0
	strb r0, [r5, o_MusicPlayerTrack_flags]
	pop {r4,r5}
	pop {r0}
	bx r0
	thumb_func_end ply_fine

	thumb_func_start MPlayJumpTableCopy
MPlayJumpTableCopy:
	mov r12, lr
	movs r1, 0x24
	ldr r2, lt_MPlayJumpTableTemplate
MPlayJumpTableCopy_Loop:
	ldr r3, [r2]
	bl chk_adr_r2
	stm r0!, {r3}
	adds r2, 0x4
	subs r1, 0x1
	bgt MPlayJumpTableCopy_Loop
	bx r12
	thumb_func_end MPlayJumpTableCopy

	.align 2, 0
	.thumb_func
ldrb_r3_r2:
	ldrb r3, [r2]

@ This attempts to protect against reading anything from the BIOS ROM
@ besides the jump table template.
@ It assumes that the jump table template is located at the end of the ROM.
	.thumb_func
chk_adr_r2:
	push {r0}
	lsrs r0, r2, 25
	bne chk_adr_r2_done @ if adr >= 0x2000000 (i.e. not in BIOS ROM), accept it
	ldr r0, lt_MPlayJumpTableTemplate
	cmp r2, r0
	blo chk_adr_r2_reject @ if adr < gMPlayJumpTableTemplate, reject it
	lsrs r0, r2, 14
	beq chk_adr_r2_done @ if adr < 0x40000 (i.e. in BIOS ROM), accept it
chk_adr_r2_reject:
	movs r3, 0
chk_adr_r2_done:
	pop {r0}
	bx lr

	.align 2, 0
lt_MPlayJumpTableTemplate: .word gMPlayJumpTableTemplate

	thumb_func_start ld_r3_tp_adr_i
ld_r3_tp_adr_i:
	ldr r2, [r1, o_MusicPlayerTrack_cmdPtr]
_081DD64A:
	adds r3, r2, 0x1
	str r3, [r1, o_MusicPlayerTrack_cmdPtr]
	ldrb r3, [r2]
	b chk_adr_r2
	thumb_func_end ld_r3_tp_adr_i

	thumb_func_start ply_goto
ply_goto:
	push {lr}
ply_goto_1:
	ldr r2, [r1, o_MusicPlayerTrack_cmdPtr]
	ldrb r0, [r2, 0x3]
	lsls r0, 8
	ldrb r3, [r2, 0x2]
	orrs r0, r3
	lsls r0, 8
	ldrb r3, [r2, 0x1]
	orrs r0, r3
	lsls r0, 8
	bl ldrb_r3_r2
	orrs r0, r3
	str r0, [r1, o_MusicPlayerTrack_cmdPtr]
	pop {r0}
	bx r0
	thumb_func_end ply_goto

	thumb_func_start ply_patt
ply_patt:
	ldrb r2, [r1, o_MusicPlayerTrack_patternLevel]
	cmp r2, 3
	bhs ply_patt_done
	lsls r2, 2
	adds r3, r1, r2
	ldr r2, [r1, o_MusicPlayerTrack_cmdPtr]
	adds r2, 0x4
	str r2, [r3, o_MusicPlayerTrack_patternStack]
	ldrb r2, [r1, o_MusicPlayerTrack_patternLevel]
	adds r2, 1
	strb r2, [r1, o_MusicPlayerTrack_patternLevel]
	b ply_goto
ply_patt_done:
	b ply_fine
	thumb_func_end ply_patt

	thumb_func_start ply_pend
ply_pend:
	ldrb r2, [r1, o_MusicPlayerTrack_patternLevel]
	cmp r2, 0
	beq ply_pend_done
	subs r2, 1
	strb r2, [r1, o_MusicPlayerTrack_patternLevel]
	lsls r2, 2
	adds r3, r1, r2
	ldr r2, [r3, o_MusicPlayerTrack_patternStack]
	str r2, [r1, o_MusicPlayerTrack_cmdPtr]
ply_pend_done:
	bx lr
	thumb_func_end ply_pend

	thumb_func_start ply_rept
ply_rept:
	push {lr}
	ldr r2, [r1, o_MusicPlayerTrack_cmdPtr]
	ldrb r3, [r2]
	cmp r3, 0
	bne ply_rept_1
	adds r2, 1
	str r2, [r1, o_MusicPlayerTrack_cmdPtr]
	b ply_goto_1
ply_rept_1:
	ldrb r3, [r1, o_MusicPlayerTrack_repN]
	adds r3, 1
	strb r3, [r1, o_MusicPlayerTrack_repN]
	mov r12, r3
	bl ld_r3_tp_adr_i
	cmp r12, r3
	bhs ply_rept_2
	b ply_goto_1
ply_rept_2:
	movs r3, 0
	strb r3, [r1, o_MusicPlayerTrack_repN]
	adds r2, 5
	str r2, [r1, o_MusicPlayerTrack_cmdPtr]
	pop {r0}
	bx r0
	thumb_func_end ply_rept

	thumb_func_start ply_prio
ply_prio:
	mov r12, lr
	bl ld_r3_tp_adr_i
	strb r3, [r1, o_MusicPlayerTrack_priority]
	bx r12
	thumb_func_end ply_prio

	thumb_func_start ply_tempo
ply_tempo:
	mov r12, lr
	bl ld_r3_tp_adr_i
	lsls r3, 1
	strh r3, [r0, o_MusicPlayerInfo_tempoD]
	ldrh r2, [r0, o_MusicPlayerInfo_tempoU]
	muls r3, r2
	lsrs r3, 8
	strh r3, [r0, o_MusicPlayerInfo_tempoI]
	bx r12
	thumb_func_end ply_tempo

	thumb_func_start ply_keysh
ply_keysh:
	mov r12, lr
	bl ld_r3_tp_adr_i
	strb r3, [r1, o_MusicPlayerTrack_keyShift]
	ldrb r3, [r1, o_MusicPlayerTrack_flags]
	movs r2, 0xC
	orrs r3, r2
	strb r3, [r1, o_MusicPlayerTrack_flags]
	bx r12
	thumb_func_end ply_keysh

	thumb_func_start ply_voice
ply_voice:
	mov r12, lr
	ldr r2, [r1, o_MusicPlayerTrack_cmdPtr]
	ldrb r3, [r2]
	adds r2, 1
	str r2, [r1, o_MusicPlayerTrack_cmdPtr]
	lsls r2, r3, 1
	adds r2, r3
	lsls r2, 2
	ldr r3, [r0, o_MusicPlayerInfo_tone]
	adds r2, r3
	ldr r3, [r2, o_ToneData_type]
	bl chk_adr_r2
	str r3, [r1, o_MusicPlayerTrack_ToneData_type]
	ldr r3, [r2, o_ToneData_wav]
	bl chk_adr_r2
	str r3, [r1, o_MusicPlayerTrack_ToneData_wav]
	ldr r3, [r2, o_ToneData_attack]
	bl chk_adr_r2
	str r3, [r1, o_MusicPlayerTrack_ToneData_attack]
	bx r12
	thumb_func_end ply_voice

	thumb_func_start ply_vol
ply_vol:
	mov r12, lr
	bl ld_r3_tp_adr_i
	strb r3, [r1, o_MusicPlayerTrack_vol]
	ldrb r3, [r1, o_MusicPlayerTrack_flags]
	movs r2, MPT_FLG_VOLCHG
	orrs r3, r2
	strb r3, [r1, o_MusicPlayerTrack_flags]
	bx r12
	thumb_func_end ply_vol

	thumb_func_start ply_pan
ply_pan:
	mov r12, lr
	bl ld_r3_tp_adr_i
	subs r3, C_V
	strb r3, [r1, o_MusicPlayerTrack_pan]
	ldrb r3, [r1, o_MusicPlayerTrack_flags]
	movs r2, MPT_FLG_VOLCHG
	orrs r3, r2
	strb r3, [r1, o_MusicPlayerTrack_flags]
	bx r12
	thumb_func_end ply_pan

	thumb_func_start ply_bend
ply_bend:
	mov r12, lr
	bl ld_r3_tp_adr_i
	subs r3, C_V
	strb r3, [r1, o_MusicPlayerTrack_bend]
	ldrb r3, [r1, o_MusicPlayerTrack_flags]
	movs r2, MPT_FLG_PITCHG
	orrs r3, r2
	strb r3, [r1, o_MusicPlayerTrack_flags]
	bx r12
	thumb_func_end ply_bend

	thumb_func_start ply_bendr
ply_bendr:
	mov r12, lr
	bl ld_r3_tp_adr_i
	strb r3, [r1, o_MusicPlayerTrack_bendRange]
	ldrb r3, [r1, o_MusicPlayerTrack_flags]
	movs r2, MPT_FLG_PITCHG
	orrs r3, r2
	strb r3, [r1, o_MusicPlayerTrack_flags]
	bx r12
	thumb_func_end ply_bendr

	thumb_func_start ply_lfodl
ply_lfodl:
	mov r12, lr
	bl ld_r3_tp_adr_i
	strb r3, [r1, o_MusicPlayerTrack_lfoDelay]
	bx r12
	thumb_func_end ply_lfodl

	thumb_func_start ply_modt
ply_modt:
	mov r12, lr
	bl ld_r3_tp_adr_i
	ldrb r0, [r1, o_MusicPlayerTrack_modT]
	cmp r0, r3
	beq _081DD7AA
	strb r3, [r1, o_MusicPlayerTrack_modT]
	ldrb r3, [r1, o_MusicPlayerTrack_flags]
	movs r2, MPT_FLG_VOLCHG | MPT_FLG_PITCHG
	orrs r3, r2
	strb r3, [r1, o_MusicPlayerTrack_flags]
_081DD7AA:
	bx r12
	thumb_func_end ply_modt

	thumb_func_start ply_tune
ply_tune:
	mov r12, lr
	bl ld_r3_tp_adr_i
	subs r3, C_V
	strb r3, [r1, o_MusicPlayerTrack_tune]
	ldrb r3, [r1, o_MusicPlayerTrack_flags]
	movs r2, MPT_FLG_PITCHG
	orrs r3, r2
	strb r3, [r1, o_MusicPlayerTrack_flags]
	bx r12
	thumb_func_end ply_tune

	thumb_func_start ply_port
ply_port:
	mov r12, lr
	ldr r2, [r1, o_MusicPlayerTrack_cmdPtr]
	ldrb r3, [r2]
	adds r2, 1
	ldr r0, =REG_SOUND1CNT_L @ sound register base address
	adds r0, r3
	bl _081DD64A
	strb r3, [r0]
	bx r12
	.pool
	thumb_func_end ply_port

	thumb_func_start m4aSoundVSync
m4aSoundVSync:
	ldr r0, lt2_SOUND_INFO_PTR
	ldr r0, [r0]

	@ Exit the function if ident is not ID_NUMBER or ID_NUMBER+1.
	ldr r2, lt2_ID_NUMBER
	ldr r3, [r0, o_SoundInfo_ident]
	subs r3, r2
	cmp r3, 1
	bhi m4aSoundVSync_Done

	@ Decrement the PCM DMA counter. If it reaches 0, we need to do a DMA.
	ldrb r1, [r0, o_SoundInfo_pcmDmaCounter]
	subs r1, 1
	strb r1, [r0, o_SoundInfo_pcmDmaCounter]
	bgt m4aSoundVSync_Done

	@ Reload the PCM DMA counter.
	ldrb r1, [r0, o_SoundInfo_pcmDmaPeriod]
	strb r1, [r0, o_SoundInfo_pcmDmaCounter]

	ldr r2, =REG_DMA1

	ldr r1, [r2, 0x8] @ DMA1CNT
	lsls r1, 7
	bcc m4aSoundVSync_SkipDMA1 @ branch if repeat bit isn't set

	ldr r1, =((DMA_ENABLE | DMA_START_NOW | DMA_32BIT | DMA_SRC_INC | DMA_DEST_FIXED) << 16) | 4
	str r1, [r2, 0x8] @ DMA1CNT

m4aSoundVSync_SkipDMA1:
	ldr r1, [r2, 0xC + 0x8] @ DMA2CNT
	lsls r1, 7
	bcc m4aSoundVSync_SkipDMA2 @ branch if repeat bit isn't set

	ldr r1, =((DMA_ENABLE | DMA_START_NOW | DMA_32BIT | DMA_SRC_INC | DMA_DEST_FIXED) << 16) | 4
	str r1, [r2, 0xC + 0x8] @ DMA2CNT

m4aSoundVSync_SkipDMA2:

	@ turn off DMA1/DMA2
	movs r1, DMA_32BIT >> 8
	lsls r1, 8
	strh r1, [r2, 0xA]       @ DMA1CNT_H
	strh r1, [r2, 0xC + 0xA] @ DMA2CNT_H

	@ turn on DMA1/DMA2 direct-sound FIFO mode
	movs r1, (DMA_ENABLE | DMA_START_SPECIAL | DMA_32BIT | DMA_REPEAT) >> 8
	lsls r1, 8 @ LSB is 0, so DMA_SRC_INC is used (destination is always fixed in FIFO mode)
	strh r1, [r2, 0xA]       @ DMA1CNT_H
	strh r1, [r2, 0xC + 0xA] @ DMA2CNT_H

m4aSoundVSync_Done:
	bx lr

	.pool
	thumb_func_end m4aSoundVSync

	thumb_func_start MPlayMain
MPlayMain:
	ldr r2, lt2_ID_NUMBER
	ldr r3, [r0, o_MusicPlayerInfo_ident]
	cmp r2, r3
	beq _081DD82E
	bx lr
_081DD82E:
	adds r3, 0x1
	str r3, [r0, o_MusicPlayerInfo_ident]
	push {r0,lr}
	ldr r3, [r0, o_MusicPlayerInfo_func]
	cmp r3, 0
	beq _081DD840
	ldr r0, [r0, o_MusicPlayerInfo_intp]
	bl call_r3
_081DD840:
	pop {r0}
	push {r4-r7}
	mov r4, r8
	mov r5, r9
	mov r6, r10
	mov r7, r11
	push {r4-r7}
	adds r7, r0, 0
	ldr r0, [r7, o_MusicPlayerInfo_status]
	cmp r0, 0
	bge _081DD858
	b _081DDA6C
_081DD858:
	ldr r0, lt2_SOUND_INFO_PTR
	ldr r0, [r0]
	mov r8, r0
	adds r0, r7, 0
	bl FadeOutBody
	ldr r0, [r7, o_MusicPlayerInfo_status]
	cmp r0, 0
	bge _081DD86C
	b _081DDA6C
_081DD86C:
	ldrh r0, [r7, o_MusicPlayerInfo_tempoC]
	ldrh r1, [r7, o_MusicPlayerInfo_tempoI]
	adds r0, r1
	b _081DD9BC
_081DD874:
	ldrb r6, [r7, o_MusicPlayerInfo_trackCount]
	ldr r5, [r7, o_MusicPlayerInfo_tracks]
	movs r3, 0x1
	movs r4, 0
_081DD87C:
	ldrb r0, [r5, o_MusicPlayerTrack_flags]
	movs r1, MPT_FLG_EXIST
	tst r1, r0
	bne _081DD886
	b _081DD998
_081DD886:
	mov r10, r3
	orrs r4, r3
	mov r11, r4
	ldr r4, [r5, o_MusicPlayerTrack_chan]
	cmp r4, 0
	beq _081DD8BA
_081DD892:
	ldrb r1, [r4, o_SoundChannel_statusFlags]
	movs r0, SOUND_CHANNEL_SF_ON
	tst r0, r1
	beq _081DD8AE
	ldrb r0, [r4, o_SoundChannel_gateTime]
	cmp r0, 0
	beq _081DD8B4
	subs r0, 0x1
	strb r0, [r4, o_SoundChannel_gateTime]
	bne _081DD8B4
	movs r0, SOUND_CHANNEL_SF_STOP
	orrs r1, r0
	strb r1, [r4, o_SoundChannel_statusFlags]
	b _081DD8B4
_081DD8AE:
	adds r0, r4, 0
	bl ClearChain
_081DD8B4:
	ldr r4, [r4, o_SoundChannel_nextChannelPointer]
	cmp r4, 0
	bne _081DD892
_081DD8BA:
	ldrb r3, [r5, o_MusicPlayerTrack_flags]
	movs r0, MPT_FLG_START
	tst r0, r3
	beq _081DD938
	adds r0, r5, 0
	bl Clear64byte
	movs r0, MPT_FLG_EXIST
	strb r0, [r5, o_MusicPlayerTrack_flags]
	movs r0, 0x2
	strb r0, [r5, o_MusicPlayerTrack_bendRange]
	movs r0, 0x40
	strb r0, [r5, o_MusicPlayerTrack_volX]
	movs r0, 0x16
	strb r0, [r5, o_MusicPlayerTrack_lfoSpeed]
	movs r0, 0x1
	adds r1, r5, 0x6
	strb r0, [r1, o_MusicPlayerTrack_ToneData_type - 0x6]
	b _081DD938
_081DD8E0:
	ldr r2, [r5, o_MusicPlayerTrack_cmdPtr]
	ldrb r1, [r2]
	cmp r1, 0x80
	bhs _081DD8EC
	ldrb r1, [r5, o_MusicPlayerTrack_runningStatus]
	b _081DD8F6
_081DD8EC:
	adds r2, 0x1
	str r2, [r5, o_MusicPlayerTrack_cmdPtr]
	cmp r1, 0xBD
	bcc _081DD8F6
	strb r1, [r5, o_MusicPlayerTrack_runningStatus]
_081DD8F6:
	cmp r1, 0xCF
	bcc _081DD90C
	mov r0, r8
	ldr r3, [r0, o_SoundInfo_plynote]
	adds r0, r1, 0
	subs r0, 0xCF
	adds r1, r7, 0
	adds r2, r5, 0
	bl call_r3
	b _081DD938
_081DD90C:
	cmp r1, 0xB0
	bls _081DD92E
	adds r0, r1, 0
	subs r0, 0xB1
	strb r0, [r7, o_MusicPlayerInfo_cmd]
	mov r3, r8
	ldr r3, [r3, o_SoundInfo_MPlayJumpTable]
	lsls r0, 2
	ldr r3, [r3, r0]
	adds r0, r7, 0
	adds r1, r5, 0
	bl call_r3
	ldrb r0, [r5, o_MusicPlayerTrack_flags]
	cmp r0, 0
	beq _081DD994
	b _081DD938
_081DD92E:
	ldr r0, lt_gClockTable
	subs r1, 0x80
	adds r1, r0
	ldrb r0, [r1]
	strb r0, [r5, o_MusicPlayerTrack_wait]
_081DD938:
	ldrb r0, [r5, o_MusicPlayerTrack_wait]
	cmp r0, 0
	beq _081DD8E0
	subs r0, 0x1
	strb r0, [r5, o_MusicPlayerTrack_wait]
	ldrb r1, [r5, o_MusicPlayerTrack_lfoSpeed]
	cmp r1, 0
	beq _081DD994
	ldrb r0, [r5, o_MusicPlayerTrack_mod]
	cmp r0, 0
	beq _081DD994
	ldrb r0, [r5, o_MusicPlayerTrack_lfoDelayC]
	cmp r0, 0
	beq _081DD95A
	subs r0, 0x1
	strb r0, [r5, o_MusicPlayerTrack_lfoDelayC]
	b _081DD994
_081DD95A:
	ldrb r0, [r5, o_MusicPlayerTrack_lfoSpeedC]
	adds r0, r1
	strb r0, [r5, o_MusicPlayerTrack_lfoSpeedC]
	adds r1, r0, 0
	subs r0, 0x40
	lsls r0, 24
	bpl _081DD96E
	lsls r2, r1, 24
	asrs r2, 24
	b _081DD972
_081DD96E:
	movs r0, 0x80
	subs r2, r0, r1
_081DD972:
	ldrb r0, [r5, o_MusicPlayerTrack_mod]
	muls r0, r2
	asrs r2, r0, 6
	ldrb r0, [r5, o_MusicPlayerTrack_modM]
	eors r0, r2
	lsls r0, 24
	beq _081DD994
	strb r2, [r5, o_MusicPlayerTrack_modM]
	ldrb r0, [r5]
	ldrb r1, [r5, o_MusicPlayerTrack_modT]
	cmp r1, 0
	bne _081DD98E
	movs r1, MPT_FLG_PITCHG
	b _081DD990
_081DD98E:
	movs r1, MPT_FLG_VOLCHG
_081DD990:
	orrs r0, r1
	strb r0, [r5, o_MusicPlayerTrack_flags]
_081DD994:
	mov r3, r10
	mov r4, r11
_081DD998:
	subs r6, 0x1
	ble _081DD9A4
	movs r0, MusicPlayerTrack_size
	adds r5, r0
	lsls r3, 1
	b _081DD87C
_081DD9A4:
	ldr r0, [r7, o_MusicPlayerInfo_clock]
	adds r0, 0x1
	str r0, [r7, o_MusicPlayerInfo_clock]
	cmp r4, 0
	bne _081DD9B6
	movs r0, 0x80
	lsls r0, 24
	str r0, [r7, o_MusicPlayerInfo_status]
	b _081DDA6C
_081DD9B6:
	str r4, [r7, o_MusicPlayerInfo_status]
	ldrh r0, [r7, o_MusicPlayerInfo_tempoC]
	subs r0, 150
_081DD9BC:
	strh r0, [r7, o_MusicPlayerInfo_tempoC]
	cmp r0, 150
	bcc _081DD9C4
	b _081DD874
_081DD9C4:
	ldrb r2, [r7, o_MusicPlayerInfo_trackCount]
	ldr r5, [r7, o_MusicPlayerInfo_tracks]
_081DD9C8:
	ldrb r0, [r5, o_MusicPlayerTrack_flags]
	movs r1, 0x80
	tst r1, r0
	beq _081DDA62
	movs r1, MPT_FLG_VOLCHG | MPT_FLG_PITCHG
	tst r1, r0
	beq _081DDA62
	mov r9, r2
	adds r0, r7, 0
	adds r1, r5, 0
	bl TrkVolPitSet
	ldr r4, [r5, o_MusicPlayerTrack_chan]
	cmp r4, 0
	beq _081DDA58
_081DD9E6:
	ldrb r1, [r4, o_SoundChannel_statusFlags]
	movs r0, SOUND_CHANNEL_SF_ON
	tst r0, r1
	bne _081DD9F6
	adds r0, r4, 0
	bl ClearChain
	b _081DDA52
_081DD9F6:
	ldrb r0, [r4, o_SoundChannel_type]
	movs r6, TONEDATA_TYPE_CGB
	ands r6, r0
	ldrb r3, [r5, o_MusicPlayerTrack_flags]
	movs r0, MPT_FLG_VOLCHG
	tst r0, r3
	beq _081DDA14
	bl ChnVolSetAsm
	cmp r6, 0
	beq _081DDA14
	ldrb r0, [r4, o_CgbChannel_modify]
	movs r1, CGB_CHANNEL_MO_VOL
	orrs r0, r1
	strb r0, [r4, o_CgbChannel_modify]
_081DDA14:
	ldrb r3, [r5, o_MusicPlayerTrack_flags]
	movs r0, MPT_FLG_PITCHG
	tst r0, r3
	beq _081DDA52
	ldrb r1, [r4, o_SoundChannel_key]
	movs r0, o_MusicPlayerTrack_keyM
	ldrsb r0, [r5, r0]
	adds r2, r1, r0
	bpl _081DDA28
	movs r2, 0
_081DDA28:
	cmp r6, 0
	beq _081DDA46
	mov r0, r8
	ldr r3, [r0, o_SoundInfo_MidiKeyToCgbFreq]
	adds r1, r2, 0
	ldrb r2, [r5, o_MusicPlayerTrack_pitM]
	adds r0, r6, 0
	bl call_r3
	str r0, [r4, o_CgbChannel_frequency]
	ldrb r0, [r4, o_CgbChannel_modify]
	movs r1, CGB_CHANNEL_MO_PIT
	orrs r0, r1
	strb r0, [r4, o_CgbChannel_modify]
	b _081DDA52
_081DDA46:
	adds r1, r2, 0
	ldrb r2, [r5, o_MusicPlayerTrack_pitM]
	ldr r0, [r4, o_SoundChannel_wav]
	bl MidiKeyToFreq
	str r0, [r4, o_SoundChannel_frequency]
_081DDA52:
	ldr r4, [r4, o_SoundChannel_nextChannelPointer]
	cmp r4, 0
	bne _081DD9E6
_081DDA58:
	ldrb r0, [r5, o_MusicPlayerTrack_flags]
	movs r1, 0xF0
	ands r0, r1
	strb r0, [r5, o_MusicPlayerTrack_flags]
	mov r2, r9
_081DDA62:
	subs r2, 0x1
	ble _081DDA6C
	movs r0, MusicPlayerTrack_size
	adds r5, r0
	bgt _081DD9C8
_081DDA6C:
	ldr r0, lt2_ID_NUMBER
	str r0, [r7, o_MusicPlayerInfo_ident]
	pop {r0-r7}
	mov r8, r0
	mov r9, r1
	mov r10, r2
	mov r11, r3
	pop {r3}

call_r3:
	bx r3

	.align 2, 0
lt_gClockTable:     .word gClockTable
lt2_SOUND_INFO_PTR: .word SOUND_INFO_PTR
lt2_ID_NUMBER:      .word ID_NUMBER
	thumb_func_end MPlayMain

	thumb_func_start TrackStop
TrackStop:
	push {r4-r6,lr}
	adds r5, r1, 0
	ldrb r1, [r5, o_MusicPlayerTrack_flags]
	movs r0, MPT_FLG_EXIST
	tst r0, r1
	beq TrackStop_Done
	ldr r4, [r5, o_MusicPlayerTrack_chan]
	cmp r4, 0
	beq TrackStop_3
	movs r6, 0
TrackStop_Loop:
	ldrb r0, [r4, o_SoundChannel_statusFlags]
	cmp r0, 0
	beq TrackStop_2
	ldrb r0, [r4, o_SoundChannel_type]
	movs r3, TONEDATA_TYPE_CGB
	ands r0, r3
	beq TrackStop_1
	ldr r3, =SOUND_INFO_PTR
	ldr r3, [r3]
	ldr r3, [r3, o_SoundInfo_CgbOscOff]
	bl call_r3
TrackStop_1:
	strb r6, [r4, o_SoundChannel_statusFlags]
TrackStop_2:
	str r6, [r4, o_SoundChannel_track]
	ldr r4, [r4, o_SoundChannel_nextChannelPointer]
	cmp r4, 0
	bne TrackStop_Loop
TrackStop_3:
	str r4, [r5, o_MusicPlayerTrack_chan]
TrackStop_Done:
	pop {r4-r6}
	pop {r0}
	bx r0
	.pool
	thumb_func_end TrackStop

	thumb_func_start ChnVolSetAsm
ChnVolSetAsm:
	ldrb r1, [r4, o_SoundChannel_velocity]
	movs r0, o_SoundChannel_rhythmPan
	ldrsb r2, [r4, r0]
	movs r3, 0x80
	adds r3, r2
	muls r3, r1
	ldrb r0, [r5, o_MusicPlayerTrack_volMR]
	muls r0, r3
	asrs r0, 14
	cmp r0, 0xFF
	bls _081DDAE8
	movs r0, 0xFF
_081DDAE8:
	strb r0, [r4, o_SoundChannel_rightVolume]
	movs r3, 0x7F
	subs r3, r2
	muls r3, r1
	ldrb r0, [r5, o_MusicPlayerTrack_volML]
	muls r0, r3
	asrs r0, 14
	cmp r0, 0xFF
	bls _081DDAFC
	movs r0, 0xFF
_081DDAFC:
	strb r0, [r4, o_SoundChannel_leftVolume]
	bx lr
	thumb_func_end ChnVolSetAsm

	thumb_func_start ply_note
ply_note:
	push {r4-r7,lr}
	mov r4, r8
	mov r5, r9
	mov r6, r10
	mov r7, r11
	push {r4-r7}
	sub sp, 0x18
	str r1, [sp]
	adds r5, r2, 0
	ldr r1, =SOUND_INFO_PTR
	ldr r1, [r1]
	str r1, [sp, 0x4]
	ldr r1, =gClockTable
	adds r0, r1
	ldrb r0, [r0]
	strb r0, [r5, o_MusicPlayerTrack_gateTime]
	ldr r3, [r5, o_MusicPlayerTrack_cmdPtr]
	ldrb r0, [r3]
	cmp r0, 0x80
	bhs _081DDB46
	strb r0, [r5, o_MusicPlayerTrack_key]
	adds r3, 0x1
	ldrb r0, [r3]
	cmp r0, 0x80
	bhs _081DDB44
	strb r0, [r5, o_MusicPlayerTrack_velocity]
	adds r3, 0x1
	ldrb r0, [r3]
	cmp r0, 0x80
	bhs _081DDB44
	ldrb r1, [r5, o_MusicPlayerTrack_gateTime]
	adds r1, r0
	strb r1, [r5, o_MusicPlayerTrack_gateTime]
	adds r3, 0x1
_081DDB44:
	str r3, [r5, o_MusicPlayerTrack_cmdPtr]
_081DDB46:
	movs r0, 0
	str r0, [sp, 0x14]
	adds r4, r5, 0
	adds r4, o_MusicPlayerTrack_ToneData_type
	ldrb r2, [r4]
	movs r0, TONEDATA_TYPE_RHY | TONEDATA_TYPE_SPL
	tst r0, r2
	beq _081DDB98
	ldrb r3, [r5, o_MusicPlayerTrack_key]
	movs r0, TONEDATA_TYPE_SPL
	tst r0, r2
	beq _081DDB66
	ldr r1, [r5, o_MusicPlayerTrack_ToneData_keySplitTable]
	adds r1, r3
	ldrb r0, [r1]
	b _081DDB68
_081DDB66:
	adds r0, r3, 0
_081DDB68:
	lsls r1, r0, 1
	adds r1, r0
	lsls r1, 2
	ldr r0, [r5, o_MusicPlayerTrack_ToneData_wav]
	adds r1, r0
	mov r9, r1
	mov r6, r9
	ldrb r1, [r6]
	movs r0, TONEDATA_TYPE_SPL | TONEDATA_TYPE_RHY
	tst r0, r1
	beq _081DDB80
	b _081DDCEA
_081DDB80:
	movs r0, TONEDATA_TYPE_RHY
	tst r0, r2
	beq _081DDB9C
	ldrb r1, [r6, o_ToneData_pan_sweep]
	movs r0, 0x80
	tst r0, r1
	beq _081DDB94
	subs r1, TONEDATA_P_S_PAN
	lsls r1, 1
	str r1, [sp, 0x14]
_081DDB94:
	ldrb r3, [r6, o_SoundChannel_type]
	b _081DDB9C
_081DDB98:
	mov r9, r4
	ldrb r3, [r5, o_MusicPlayerTrack_key]
_081DDB9C:
	str r3, [sp, 0x8]
	ldr r6, [sp]
	ldrb r1, [r6, o_MusicPlayerInfo_priority]
	ldrb r0, [r5, o_MusicPlayerTrack_priority]
	adds r0, r1
	cmp r0, 0xFF
	bls _081DDBAC
	movs r0, 0xFF
_081DDBAC:
	str r0, [sp, 0x10]
	mov r6, r9
	ldrb r0, [r6, o_ToneData_type]
	movs r6, TONEDATA_TYPE_CGB
	ands r6, r0
	str r6, [sp, 0xC]
	beq _081DDBEC
	ldr r0, [sp, 0x4]
	ldr r4, [r0, o_SoundInfo_cgbChans]
	cmp r4, 0
	bne _081DDBC4
	b _081DDCEA
_081DDBC4:
	subs r6, 0x1
	lsls r0, r6, 6
	adds r4, r0
	ldrb r1, [r4, o_CgbChannel_statusFlags]
	movs r0, SOUND_CHANNEL_SF_ON
	tst r0, r1
	beq _081DDC40
	movs r0, SOUND_CHANNEL_SF_STOP
	tst r0, r1
	bne _081DDC40
	ldrb r1, [r4, o_CgbChannel_priority]
	ldr r0, [sp, 0x10]
	cmp r1, r0
	bcc _081DDC40
	beq _081DDBE4
	b _081DDCEA
_081DDBE4:
	ldr r0, [r4, o_CgbChannel_track]
	cmp r0, r5
	bcs _081DDC40
	b _081DDCEA
_081DDBEC:
	ldr r6, [sp, 0x10]
	adds r7, r5, 0
	movs r2, 0
	mov r8, r2
	ldr r4, [sp, 0x4]
	ldrb r3, [r4, o_SoundInfo_maxChans]
	adds r4, o_SoundInfo_chans
_081DDBFA:
	ldrb r1, [r4, o_SoundChannel_statusFlags]
	movs r0, SOUND_CHANNEL_SF_ON
	tst r0, r1
	beq _081DDC40
	movs r0, SOUND_CHANNEL_SF_STOP
	tst r0, r1
	beq _081DDC14
	cmp r2, 0
	bne _081DDC18
	adds r2, 0x1
	ldrb r6, [r4, o_SoundChannel_priority]
	ldr r7, [r4, o_SoundChannel_track]
	b _081DDC32
_081DDC14:
	cmp r2, 0
	bne _081DDC34
_081DDC18:
	ldrb r0, [r4, o_SoundChannel_priority]
	cmp r0, r6
	bcs _081DDC24
	adds r6, r0, 0
	ldr r7, [r4, o_SoundChannel_track]
	b _081DDC32
_081DDC24:
	bhi _081DDC34
	ldr r0, [r4, o_SoundChannel_track]
	cmp r0, r7
	bls _081DDC30
	adds r7, r0, 0
	b _081DDC32
_081DDC30:
	bcc _081DDC34
_081DDC32:
	mov r8, r4
_081DDC34:
	adds r4, SoundChannel_size
	subs r3, 0x1
	bgt _081DDBFA
	mov r4, r8
	cmp r4, 0
	beq _081DDCEA
_081DDC40:
	adds r0, r4, 0
	bl ClearChain
	movs r1, 0
	str r1, [r4, o_SoundChannel_prevChannelPointer]
	ldr r3, [r5, o_MusicPlayerTrack_chan]
	str r3, [r4, o_SoundChannel_nextChannelPointer]
	cmp r3, 0
	beq _081DDC54
	str r4, [r3, o_SoundChannel_prevChannelPointer]
_081DDC54:
	str r4, [r5, o_MusicPlayerTrack_chan]
	str r5, [r4, o_SoundChannel_track]
	ldrb r0, [r5, o_MusicPlayerTrack_lfoDelay]
	strb r0, [r5, o_MusicPlayerTrack_lfoDelayC]
	cmp r0, r1
	beq _081DDC66
	adds r1, r5, 0
	bl clear_modM
_081DDC66:
	ldr r0, [sp]
	adds r1, r5, 0
	bl TrkVolPitSet
	ldr r0, [r5, o_MusicPlayerTrack_gateTime]
	str r0, [r4, o_SoundChannel_gateTime]
	ldr r0, [sp, 0x10]
	strb r0, [r4, o_SoundChannel_priority]
	ldr r0, [sp, 0x8]
	strb r0, [r4, o_SoundChannel_key]
	ldr r0, [sp, 0x14]
	strb r0, [r4, o_SoundChannel_rhythmPan]
	mov r6, r9
	ldrb r0, [r6, o_ToneData_type]
	strb r0, [r4, o_SoundChannel_type]
	ldr r7, [r6, o_ToneData_wav]
	str r7, [r4, o_SoundChannel_wav]
	ldr r0, [r6, o_ToneData_attack]
	str r0, [r4, o_SoundChannel_attack]
	ldrh r0, [r5, o_MusicPlayerTrack_pseudoEchoVolume]
	strh r0, [r4, o_SoundChannel_pseudoEchoVolume]
	bl ChnVolSetAsm
	ldrb r1, [r4, o_SoundChannel_key]
	movs r0, o_MusicPlayerTrack_keyM
	ldrsb r0, [r5, r0]
	adds r3, r1, r0
	bpl _081DDCA0
	movs r3, 0
_081DDCA0:
	ldr r6, [sp, 0xC]
	cmp r6, 0
	beq _081DDCCE
	mov r6, r9
	ldrb r0, [r6, o_ToneData_length]
	strb r0, [r4, o_CgbChannel_length]
	ldrb r1, [r6, o_ToneData_pan_sweep]
	movs r0, 0x80
	tst r0, r1
	bne _081DDCBA
	movs r0, 0x70
	tst r0, r1
	bne _081DDCBC
_081DDCBA:
	movs r1, 0x8
_081DDCBC:
	strb r1, [r4, o_CgbChannel_sweep]
	ldrb r2, [r5, o_MusicPlayerTrack_pitM]
	adds r1, r3, 0
	ldr r0, [sp, 0xC]
	ldr r3, [sp, 0x4]
	ldr r3, [r3, o_SoundInfo_MidiKeyToCgbFreq]
	bl call_r3
	b _081DDCDC
_081DDCCE:
	ldr r0, [r5, o_MusicPlayerTrack_unk_3C]
	str r0, [r4, o_SoundChannel_count]
	ldrb r2, [r5, o_MusicPlayerTrack_pitM]
	adds r1, r3, 0
	adds r0, r7, 0
	bl MidiKeyToFreq
_081DDCDC:
	str r0, [r4, o_SoundChannel_frequency]
	movs r0, SOUND_CHANNEL_SF_START
	strb r0, [r4, o_SoundChannel_statusFlags]
	ldrb r1, [r5, o_MusicPlayerTrack_flags]
	movs r0, 0xF0
	ands r0, r1
	strb r0, [r5, o_MusicPlayerTrack_flags]
_081DDCEA:
	add sp, 0x18
	pop {r0-r7}
	mov r8, r0
	mov r9, r1
	mov r10, r2
	mov r11, r3
	pop {r0}
	bx r0
	.pool
	thumb_func_end ply_note

	thumb_func_start ply_endtie
ply_endtie:
	push {r4,r5}
	ldr r2, [r1, o_MusicPlayerTrack_cmdPtr]
	ldrb r3, [r2]
	cmp r3, 0x80
	bhs _081DDD16
	strb r3, [r1, o_MusicPlayerTrack_key]
	adds r2, 0x1
	str r2, [r1, o_MusicPlayerTrack_cmdPtr]
	b _081DDD18
_081DDD16:
	ldrb r3, [r1, o_MusicPlayerTrack_key]
_081DDD18:
	ldr r1, [r1, o_MusicPlayerTrack_chan]
	cmp r1, 0
	beq _081DDD40
	movs r4, SOUND_CHANNEL_SF_START | SOUND_CHANNEL_SF_ENV
	movs r5, SOUND_CHANNEL_SF_STOP
_081DDD22:
	ldrb r2, [r1, o_SoundChannel_statusFlags]
	tst r2, r4
	beq _081DDD3A
	tst r2, r5
	bne _081DDD3A
	ldrb r0, [r1, o_SoundChannel_midiKey]
	cmp r0, r3
	bne _081DDD3A
	movs r0, SOUND_CHANNEL_SF_STOP
	orrs r2, r0
	strb r2, [r1, o_SoundChannel_statusFlags]
	b _081DDD40
_081DDD3A:
	ldr r1, [r1, o_SoundChannel_nextChannelPointer]
	cmp r1, 0
	bne _081DDD22
_081DDD40:
	pop {r4,r5}
	bx lr
	thumb_func_end ply_endtie

	thumb_func_start clear_modM
clear_modM:
	movs r2, 0
	strb r2, [r1, o_MusicPlayerTrack_modM]
	strb r2, [r1, o_MusicPlayerTrack_lfoSpeedC]
	ldrb r2, [r1, o_MusicPlayerTrack_modT]
	cmp r2, 0
	bne _081DDD54
	movs r2, MPT_FLG_PITCHG
	b _081DDD56
_081DDD54:
	movs r2, MPT_FLG_VOLCHG
_081DDD56:
	ldrb r3, [r1, o_MusicPlayerTrack_flags]
	orrs r3, r2
	strb r3, [r1, o_MusicPlayerTrack_flags]
	bx lr
	thumb_func_end clear_modM

	thumb_func_start ld_r3_tp_adr_i
ld_r3_tp_adr_i_unchecked:
	ldr r2, [r1, o_MusicPlayerTrack_cmdPtr]
	adds r3, r2, 1
	str r3, [r1, o_MusicPlayerTrack_cmdPtr]
	ldrb r3, [r2]
	bx lr
	thumb_func_end ld_r3_tp_adr_i

	thumb_func_start ply_lfos
ply_lfos:
	mov r12, lr
	bl ld_r3_tp_adr_i_unchecked
	strb r3, [r1, o_MusicPlayerTrack_lfoSpeed]
	cmp r3, 0
	bne _081DDD7C
	bl clear_modM
_081DDD7C:
	bx r12
	thumb_func_end ply_lfos

	thumb_func_start ply_mod
ply_mod:
	mov r12, lr
	bl ld_r3_tp_adr_i_unchecked
	strb r3, [r1, o_MusicPlayerTrack_mod]
	cmp r3, 0
	bne _081DDD90
	bl clear_modM
_081DDD90:
	bx r12
	thumb_func_end ply_mod

	.align 2, 0 @ Don't pad with nop.

	.bss
	.align 3
sDecodingBuffer: @ Used as a buffer for audio decoded from compressed DPCM
	.space 0x40
	.size sDecodingBuffer, .-sDecodingBuffer
