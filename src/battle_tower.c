#include "global.h"
#include "battle_tower.h"
#include "random.h"
#include "text.h"
#include "event_data.h"
#include "string_util.h"
#include "battle_message.h"
#include "data.h"
#include "pokedex.h"
#include "overworld.h"
#include "battle_transition.h"
#include "easy_chat.h"
#include "battle_setup.h"
#include "battle_main.h"
#include "task.h"
#include "battle.h"
#include "party_menu.h"
#include "new_game.h"
#include "save.h"
#include "item.h"
#include "script_pokemon_util.h"
#include "constants/items.h"
#include "constants/moves.h"
#include "constants/pokemon.h"
#include "constants/event_objects.h"

static EWRAM_DATA u16 sSpecialVar_0x8004_Copy = 0;

#define TakeBravoTrainerBattleTowerOffTheAir()
#define ewram160FB (*((u8 *)&gBattleStruct->field_DA))

static void ResetBattleTowerStreak(u8 levelType);
static void SetBattleTowerTrainerGfxId(u8 trainerClass);
static void CheckMonBattleTowerBanlist(u16 species, u16 heldItem, u16 hp, u8 battleTowerLevelType, u8 monLevel, u16 *validPartySpecies, u16 *validPartyHeldItems, u8 *numValid);
static void SaveCurrentWinStreak(void);
static void ValidateBattleTowerRecordChecksums(void);
static void SetBattleTowerRecordChecksum(struct BattleTowerRecord * record);
static void ClearBattleTowerRecord(struct BattleTowerRecord * record);
static void PopulateBravoTrainerBattleTowerLostData(void);
static u16 GetCurrentBattleTowerWinStreak(u8 levelType);
static void SetEReaderTrainerChecksum(struct BattleTowerEReaderTrainer * eReaderTrainer);
static void PrintEReaderTrainerFarewellMessage(void);

// unknown unused data
static const u8 sUnused[] = {
    5, 4, 1, 16, 4, 2, 5, 6,
    3, 16, 6, 4, 0, 1, 2, 3,
    0, 2, 3
};

static const u8 sText_100[] = _("100");

static const struct BattleTowerTrainer sBattleTowerTrainers[] =
{

};

static const u16 sBattleTowerHeldItems[] = {
    ITEM_NONE,
    ITEM_KINGS_ROCK,
    ITEM_SITRUS_BERRY,
    ITEM_ORAN_BERRY,
    ITEM_CHESTO_BERRY,
    ITEM_HARD_STONE,
    ITEM_FOCUS_BAND,
    ITEM_PERSIM_BERRY,
    ITEM_MIRACLE_SEED,
    ITEM_BERRY_JUICE,
    ITEM_MACHO_BRACE,
    ITEM_SILVER_POWDER,
    ITEM_CHERI_BERRY,
    ITEM_BLACK_GLASSES,
    ITEM_BLACK_BELT,
    ITEM_SOUL_DEW,
    ITEM_CHOICE_BAND,
    ITEM_MAGNET,
    ITEM_SILK_SCARF,
    ITEM_WHITE_HERB,
    ITEM_DEEP_SEA_SCALE,
    ITEM_DEEP_SEA_TOOTH,
    ITEM_MYSTIC_WATER,
    ITEM_SHARP_BEAK,
    ITEM_QUICK_CLAW,
    ITEM_LEFTOVERS,
    ITEM_RAWST_BERRY,
    ITEM_LIGHT_BALL,
    ITEM_POISON_BARB,
    ITEM_NEVER_MELT_ICE,
    ITEM_ASPEAR_BERRY,
    ITEM_SPELL_TAG,
    ITEM_BRIGHT_POWDER,
    ITEM_LEPPA_BERRY,
    ITEM_SCOPE_LENS,
    ITEM_TWISTED_SPOON,
    ITEM_METAL_COAT,
    ITEM_MENTAL_HERB,
    ITEM_CHARCOAL,
    ITEM_PECHA_BERRY,
    ITEM_SOFT_SAND,
    ITEM_LUM_BERRY,
    ITEM_DRAGON_SCALE,
    ITEM_DRAGON_FANG,
    ITEM_IAPAPA_BERRY,
    ITEM_WIKI_BERRY,
    ITEM_SEA_INCENSE,
    ITEM_SHELL_BELL,
    ITEM_SALAC_BERRY,
    ITEM_LANSAT_BERRY,
    ITEM_APICOT_BERRY,
    ITEM_STARF_BERRY,
    ITEM_LIECHI_BERRY,
    ITEM_STICK,
    ITEM_LAX_INCENSE,
    ITEM_AGUAV_BERRY,
    ITEM_FIGY_BERRY,
    ITEM_THICK_CLUB,
    ITEM_MAGO_BERRY,
    ITEM_METAL_POWDER,
    ITEM_PETAYA_BERRY,
    ITEM_LUCKY_PUNCH,
    ITEM_GANLON_BERRY
};

// ===== BEGIN src/data/battle_tower/level_50_mons.h =====
const struct BattleTowerPokemonTemplate gBattleTowerLevel50Mons[] =
{
	{
		.species = SPECIES_PIKACHU,
		.heldItem = BATTLE_TOWER_ITEM_ORAN_BERRY,
		.teamFlags = 0x42,
		.moves = {
			MOVE_QUICK_ATTACK,
			MOVE_THUNDER_WAVE,
			MOVE_THUNDER_SHOCK,
			MOVE_GROWL
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_DEFENSE,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_BEAUTIFLY,
		.heldItem = BATTLE_TOWER_ITEM_MIRACLE_SEED,
		.teamFlags = 0x41,
		.moves = {
			MOVE_ABSORB,
			MOVE_STUN_SPORE,
			MOVE_GUST,
			MOVE_SAFEGUARD
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED | F_EV_SPREAD_DEFENSE | F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_BRAVE,
	},
	{
		.species = SPECIES_SWELLOW,
		.heldItem = BATTLE_TOWER_ITEM_SHARP_BEAK,
		.teamFlags = 0x07,
		.moves = {
			MOVE_PECK,
			MOVE_WING_ATTACK,
			MOVE_AERIAL_ACE,
			MOVE_AGILITY
		},
		.evSpread = F_EV_SPREAD_ATTACK,
		.nature = NATURE_GENTLE,
	},
	{
		.species = SPECIES_WALREIN,
		.heldItem = BATTLE_TOWER_ITEM_SCOPE_LENS,
		.teamFlags = 0x0B,
		.moves = {
			MOVE_HAIL,
			MOVE_ENCORE,
			MOVE_ICE_BALL,
			MOVE_TOXIC
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_ADAMANT,
	},
	{
		.species = SPECIES_SEAKING,
		.heldItem = BATTLE_TOWER_ITEM_MYSTIC_WATER,
		.teamFlags = 0x07,
		.moves = {
			MOVE_PECK,
			MOVE_FLAIL,
			MOVE_FURY_ATTACK,
			MOVE_SURF
		},
		.evSpread = F_EV_SPREAD_SPEED,
		.nature = NATURE_HASTY,
	},
	{
		.species = SPECIES_TORCHIC,
		.heldItem = BATTLE_TOWER_ITEM_KINGS_ROCK,
		.teamFlags = 0x42,
		.moves = {
			MOVE_FIRE_SPIN,
			MOVE_PROTECT,
			MOVE_SAND_ATTACK,
			MOVE_SLASH
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_SP_ATTACK,
		.nature = NATURE_RELAXED,
	},
	{
		.species = SPECIES_MASQUERAIN,
		.heldItem = BATTLE_TOWER_ITEM_WHITE_HERB,
		.teamFlags = 0x41,
		.moves = {
			MOVE_STUN_SPORE,
			MOVE_WATER_SPORT,
			MOVE_QUICK_ATTACK,
			MOVE_GUST
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_IMPISH,
	},
	{
		.species = SPECIES_ILLUMISE,
		.heldItem = BATTLE_TOWER_ITEM_NONE,
		.teamFlags = 0x41,
		.moves = {
			MOVE_FLATTER,
			MOVE_COVET,
			MOVE_WISH,
			MOVE_FACADE
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_DEFENSE,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_DELCATTY,
		.heldItem = BATTLE_TOWER_ITEM_SILK_SCARF,
		.teamFlags = 0x42,
		.moves = {
			MOVE_ATTRACT,
			MOVE_TAIL_WHIP,
			MOVE_FAINT_ATTACK,
			MOVE_DIG
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_LONELY,
	},
	{
		.species = SPECIES_KECLEON,
		.heldItem = BATTLE_TOWER_ITEM_PERSIM_BERRY,
		.teamFlags = 0x0B,
		.moves = {
			MOVE_TAIL_WHIP,
			MOVE_SLASH,
			MOVE_LICK,
			MOVE_SCREECH
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_DEFENSE,
		.nature = NATURE_BRAVE,
	},
	{
		.species = SPECIES_MIGHTYENA,
		.heldItem = BATTLE_TOWER_ITEM_PECHA_BERRY,
		.teamFlags = 0x05,
		.moves = {
			MOVE_BITE,
			MOVE_TAKE_DOWN,
			MOVE_ROAR,
			MOVE_HOWL
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_ATTACK,
		.nature = NATURE_DOCILE,
	},
	{
		.species = SPECIES_SLAKING,
		.heldItem = BATTLE_TOWER_ITEM_BLACK_GLASSES,
		.teamFlags = 0x05,
		.moves = {
			MOVE_FAINT_ATTACK,
			MOVE_COUNTER,
			MOVE_SCRATCH,
			MOVE_TAUNT
		},
		.evSpread = F_EV_SPREAD_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_LAX,
	},
	{
		.species = SPECIES_MACHOKE,
		.heldItem = BATTLE_TOWER_ITEM_CHESTO_BERRY,
		.teamFlags = 0x05,
		.moves = {
			MOVE_LEER,
			MOVE_DIG,
			MOVE_LOW_KICK,
			MOVE_FOCUS_PUNCH
		},
		.evSpread = F_EV_SPREAD_SPEED,
		.nature = NATURE_TIMID,
	},
	{
		.species = SPECIES_RHYDON,
		.heldItem = BATTLE_TOWER_ITEM_PERSIM_BERRY,
		.teamFlags = 0x05,
		.moves = {
			MOVE_STRENGTH,
			MOVE_ROCK_TOMB,
			MOVE_STOMP,
			MOVE_ROCK_SMASH
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_HP,
		.nature = NATURE_QUIRKY,
	},
	{
		.species = SPECIES_CACTURNE,
		.heldItem = BATTLE_TOWER_ITEM_POISON_BARB,
		.teamFlags = 0x0B,
		.moves = {
			MOVE_POISON_STING,
			MOVE_GROWTH,
			MOVE_ABSORB,
			MOVE_SOLAR_BEAM
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_ZIGZAGOON,
		.heldItem = BATTLE_TOWER_ITEM_KINGS_ROCK,
		.teamFlags = 0x0A,
		.moves = {
			MOVE_FLAIL,
			MOVE_SAND_ATTACK,
			MOVE_REST,
			MOVE_SURF
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_ATTACK,
		.nature = NATURE_SASSY,
	},
	{
		.species = SPECIES_DODRIO,
		.heldItem = BATTLE_TOWER_ITEM_SHARP_BEAK,
		.teamFlags = 0x03,
		.moves = {
			MOVE_PURSUIT,
			MOVE_TRI_ATTACK,
			MOVE_GROWL,
			MOVE_AGILITY
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED | F_EV_SPREAD_DEFENSE | F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_SERIOUS,
	},
	{
		.species = SPECIES_WHISCASH,
		.heldItem = BATTLE_TOWER_ITEM_QUICK_CLAW,
		.teamFlags = 0x0B,
		.moves = {
			MOVE_WATER_GUN,
			MOVE_AMNESIA,
			MOVE_MAGNITUDE,
			MOVE_MUD_SLAP
		},
		.evSpread = F_EV_SPREAD_DEFENSE | F_EV_SPREAD_ATTACK,
		.nature = NATURE_LAX,
	},
	{
		.species = SPECIES_NINJASK,
		.heldItem = BATTLE_TOWER_ITEM_SILVER_POWDER,
		.teamFlags = 0x41,
		.moves = {
			MOVE_SAND_ATTACK,
			MOVE_FURY_CUTTER,
			MOVE_AGILITY,
			MOVE_HARDEN
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_SPEED | F_EV_SPREAD_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_QUIET,
	},
	{
		.species = SPECIES_DUSCLOPS,
		.heldItem = BATTLE_TOWER_ITEM_PECHA_BERRY,
		.teamFlags = 0x01,
		.moves = {
			MOVE_PROTECT,
			MOVE_NIGHT_SHADE,
			MOVE_ASTONISH,
			MOVE_WILL_O_WISP
		},
		.evSpread = F_EV_SPREAD_HP,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_CAMERUPT,
		.heldItem = BATTLE_TOWER_ITEM_CHARCOAL,
		.teamFlags = 0x07,
		.moves = {
			MOVE_DIG,
			MOVE_EMBER,
			MOVE_GROWL,
			MOVE_ROCK_SMASH
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_ATTACK,
		.nature = NATURE_BOLD,
	},
	{
		.species = SPECIES_SPINDA,
		.heldItem = BATTLE_TOWER_ITEM_CHERI_BERRY,
		.teamFlags = 0x4A,
		.moves = {
			MOVE_TEETER_DANCE,
			MOVE_FLAIL,
			MOVE_PSYCH_UP,
			MOVE_DOUBLE_EDGE
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_HP,
		.nature = NATURE_CALM,
	},
	{
		.species = SPECIES_SEVIPER,
		.heldItem = BATTLE_TOWER_ITEM_POISON_BARB,
		.teamFlags = 0x09,
		.moves = {
			MOVE_SCREECH,
			MOVE_GLARE,
			MOVE_DIG,
			MOVE_POISON_FANG
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_DEFENSE,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_FLYGON,
		.heldItem = BATTLE_TOWER_ITEM_QUICK_CLAW,
		.teamFlags = 0x49,
		.moves = {
			MOVE_SAND_ATTACK,
			MOVE_SAND_TOMB,
			MOVE_FACADE,
			MOVE_TOXIC
		},
		.evSpread = F_EV_SPREAD_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_AZUMARILL,
		.heldItem = BATTLE_TOWER_ITEM_WHITE_HERB,
		.teamFlags = 0x42,
		.moves = {
			MOVE_BUBBLE_BEAM,
			MOVE_TAIL_WHIP,
			MOVE_RAIN_DANCE,
			MOVE_ROLLOUT
		},
		.evSpread = F_EV_SPREAD_DEFENSE | F_EV_SPREAD_ATTACK,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_ZANGOOSE,
		.heldItem = BATTLE_TOWER_ITEM_MENTAL_HERB,
		.teamFlags = 0x07,
		.moves = {
			MOVE_STRENGTH,
			MOVE_TAUNT,
			MOVE_CRUSH_CLAW,
			MOVE_DETECT
		},
		.evSpread = F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_MEDICHAM,
		.heldItem = BATTLE_TOWER_ITEM_SCOPE_LENS,
		.teamFlags = 0x07,
		.moves = {
			MOVE_REVERSAL,
			MOVE_MEDITATE,
			MOVE_CONFUSION,
			MOVE_FACADE
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_DEFENSE,
		.nature = NATURE_HASTY,
	},
	{
		.species = SPECIES_ROSELIA,
		.heldItem = BATTLE_TOWER_ITEM_MIRACLE_SEED,
		.teamFlags = 0x0A,
		.moves = {
			MOVE_GROWTH,
			MOVE_MEGA_DRAIN,
			MOVE_TOXIC,
			MOVE_CUT
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_SP_ATTACK,
		.nature = NATURE_NAUGHTY,
	},
	{
		.species = SPECIES_SWALOT,
		.heldItem = BATTLE_TOWER_ITEM_LUM_BERRY,
		.teamFlags = 0x0B,
		.moves = {
			MOVE_STOCKPILE,
			MOVE_SPIT_UP,
			MOVE_SLUDGE,
			MOVE_POISON_GAS
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED | F_EV_SPREAD_DEFENSE | F_EV_SPREAD_ATTACK,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_MAGNETON,
		.heldItem = BATTLE_TOWER_ITEM_MAGNET,
		.teamFlags = 0x0B,
		.moves = {
			MOVE_SUPERSONIC,
			MOVE_THUNDER_WAVE,
			MOVE_SCREECH,
			MOVE_TRI_ATTACK
		},
		.evSpread = F_EV_SPREAD_SPEED,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_GARDEVOIR,
		.heldItem = BATTLE_TOWER_ITEM_TWISTED_SPOON,
		.teamFlags = 0x09,
		.moves = {
			MOVE_CONFUSION,
			MOVE_TOXIC,
			MOVE_TORMENT,
			MOVE_PROTECT
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_HP,
		.nature = NATURE_BOLD,
	},
	{
		.species = SPECIES_RELICANTH,
		.heldItem = BATTLE_TOWER_ITEM_MYSTIC_WATER,
		.teamFlags = 0x01,
		.moves = {
			MOVE_SURF,
			MOVE_ANCIENT_POWER,
			MOVE_ROCK_TOMB,
			MOVE_HARDEN
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_DEFENSE,
		.nature = NATURE_TIMID,
	},
	{
		.species = SPECIES_NINETALES,
		.heldItem = BATTLE_TOWER_ITEM_RAWST_BERRY,
		.teamFlags = 0x03,
		.moves = {
			MOVE_CONFUSE_RAY,
			MOVE_FIRE_SPIN,
			MOVE_QUICK_ATTACK,
			MOVE_FLAMETHROWER
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_DEFENSE | F_EV_SPREAD_ATTACK,
		.nature = NATURE_HASTY,
	},
	{
		.species = SPECIES_SHARPEDO,
		.heldItem = BATTLE_TOWER_ITEM_BLACK_GLASSES,
		.teamFlags = 0x05,
		.moves = {
			MOVE_BITE,
			MOVE_SKULL_BASH,
			MOVE_RAIN_DANCE,
			MOVE_SURF
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED | F_EV_SPREAD_ATTACK,
		.nature = NATURE_RELAXED,
	},
	{
		.species = SPECIES_GIRAFARIG,
		.heldItem = BATTLE_TOWER_ITEM_KINGS_ROCK,
		.teamFlags = 0x03,
		.moves = {
			MOVE_STRENGTH,
			MOVE_PSYBEAM,
			MOVE_AGILITY,
			MOVE_EARTHQUAKE
		},
		.evSpread = F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_IMPISH,
	},
	{
		.species = SPECIES_PELIPPER,
		.heldItem = BATTLE_TOWER_ITEM_SITRUS_BERRY,
		.teamFlags = 0x0B,
		.moves = {
			MOVE_MIST,
			MOVE_STOCKPILE,
			MOVE_SWALLOW,
			MOVE_SPIT_UP
		},
		.evSpread = F_EV_SPREAD_DEFENSE,
		.nature = NATURE_QUIRKY,
	},
	{
		.species = SPECIES_SABLEYE,
		.heldItem = BATTLE_TOWER_ITEM_CHERI_BERRY,
		.teamFlags = 0x09,
		.moves = {
			MOVE_SHADOW_BALL,
			MOVE_NIGHT_SHADE,
			MOVE_SNATCH,
			MOVE_FAKE_OUT
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_ATTACK,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_LUNATONE,
		.heldItem = BATTLE_TOWER_ITEM_HARD_STONE,
		.teamFlags = 0x0B,
		.moves = {
			MOVE_COSMIC_POWER,
			MOVE_SANDSTORM,
			MOVE_PSYCHIC,
			MOVE_ROCK_THROW
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_DEFENSE,
		.nature = NATURE_GENTLE,
	},
	{
		.species = SPECIES_LUDICOLO,
		.heldItem = BATTLE_TOWER_ITEM_NONE,
		.teamFlags = 0x0B,
		.moves = {
			MOVE_THIEF,
			MOVE_FAKE_OUT,
			MOVE_SURF,
			MOVE_RAIN_DANCE
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_ATTACK,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_GRUMPIG,
		.heldItem = BATTLE_TOWER_ITEM_SALAC_BERRY,
		.teamFlags = 0x0B,
		.moves = {
			MOVE_ODOR_SLEUTH,
			MOVE_CONFUSE_RAY,
			MOVE_MAGIC_COAT,
			MOVE_PSYCHIC
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_DEFENSE,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_BRELOOM,
		.heldItem = BATTLE_TOWER_ITEM_QUICK_CLAW,
		.teamFlags = 0x0B,
		.moves = {
			MOVE_CUT,
			MOVE_LEECH_SEED,
			MOVE_MEGA_DRAIN,
			MOVE_STUN_SPORE
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_DEFENSE,
		.nature = NATURE_SASSY,
	},
	{
		.species = SPECIES_WAILORD,
		.heldItem = BATTLE_TOWER_ITEM_MYSTIC_WATER,
		.teamFlags = 0x03,
		.moves = {
			MOVE_WATER_SPOUT,
			MOVE_ROLLOUT,
			MOVE_MIST,
			MOVE_RAIN_DANCE
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_DEFENSE,
		.nature = NATURE_GENTLE,
	},
	{
		.species = SPECIES_WEEZING,
		.heldItem = BATTLE_TOWER_ITEM_POISON_BARB,
		.teamFlags = 0x05,
		.moves = {
			MOVE_SMOG,
			MOVE_SELF_DESTRUCT,
			MOVE_TOXIC,
			MOVE_SLUDGE_BOMB
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_DEFENSE,
		.nature = NATURE_BASHFUL,
	},
	{
		.species = SPECIES_KADABRA,
		.heldItem = BATTLE_TOWER_ITEM_LEPPA_BERRY,
		.teamFlags = 0x0B,
		.moves = {
			MOVE_FUTURE_SIGHT,
			MOVE_FOCUS_PUNCH,
			MOVE_SKILL_SWAP,
			MOVE_SNATCH
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_DEFENSE,
		.nature = NATURE_CAREFUL,
	},
	{
		.species = SPECIES_MANECTRIC,
		.heldItem = BATTLE_TOWER_ITEM_MAGNET,
		.teamFlags = 0x07,
		.moves = {
			MOVE_THUNDER_WAVE,
			MOVE_BITE,
			MOVE_SPARK,
			MOVE_QUICK_ATTACK
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK,
		.nature = NATURE_RASH,
	},
	{
		.species = SPECIES_RAICHU,
		.heldItem = BATTLE_TOWER_ITEM_ASPEAR_BERRY,
		.teamFlags = 0x03,
		.moves = {
			MOVE_QUICK_ATTACK,
			MOVE_AGILITY,
			MOVE_LIGHT_SCREEN,
			MOVE_THUNDERBOLT
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_HP,
		.nature = NATURE_QUIET,
	},
	{
		.species = SPECIES_XATU,
		.heldItem = BATTLE_TOWER_ITEM_TWISTED_SPOON,
		.teamFlags = 0x03,
		.moves = {
			MOVE_NIGHT_SHADE,
			MOVE_PECK,
			MOVE_CONFUSE_RAY,
			MOVE_FUTURE_SIGHT
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED | F_EV_SPREAD_DEFENSE,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_LOUDRED,
		.heldItem = BATTLE_TOWER_ITEM_SITRUS_BERRY,
		.teamFlags = 0x05,
		.moves = {
			MOVE_UPROAR,
			MOVE_STOMP,
			MOVE_SCREECH,
			MOVE_EARTHQUAKE
		},
		.evSpread = F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_MODEST,
	},
	{
		.species = SPECIES_SOLROCK,
		.heldItem = BATTLE_TOWER_ITEM_LEFTOVERS,
		.teamFlags = 0x03,
		.moves = {
			MOVE_ROCK_THROW,
			MOVE_SUNNY_DAY,
			MOVE_SOLAR_BEAM,
			MOVE_SANDSTORM
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_DEFENSE,
		.nature = NATURE_MILD,
	},
	{
		.species = SPECIES_CLAYDOL,
		.heldItem = BATTLE_TOWER_ITEM_BRIGHT_POWDER,
		.teamFlags = 0x03,
		.moves = {
			MOVE_SANDSTORM,
			MOVE_REFLECT,
			MOVE_ROCK_TOMB,
			MOVE_STRENGTH
		},
		.evSpread = F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_SERIOUS,
	},
	{
		.species = SPECIES_CRAWDAUNT,
		.heldItem = BATTLE_TOWER_ITEM_SCOPE_LENS,
		.teamFlags = 0x03,
		.moves = {
			MOVE_WATER_PULSE,
			MOVE_KNOCK_OFF,
			MOVE_HARDEN,
			MOVE_CUT
		},
		.evSpread = F_EV_SPREAD_HP,
		.nature = NATURE_JOLLY,
	},
	{
		.species = SPECIES_GOLBAT,
		.heldItem = BATTLE_TOWER_ITEM_WHITE_HERB,
		.teamFlags = 0x09,
		.moves = {
			MOVE_CONFUSE_RAY,
			MOVE_WING_ATTACK,
			MOVE_MEAN_LOOK,
			MOVE_BITE
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_SPEED,
		.nature = NATURE_BRAVE,
	},
	{
		.species = SPECIES_BELLOSSOM,
		.heldItem = BATTLE_TOWER_ITEM_MIRACLE_SEED,
		.teamFlags = 0x0A,
		.moves = {
			MOVE_SOLAR_BEAM,
			MOVE_PETAL_DANCE,
			MOVE_SWEET_SCENT,
			MOVE_BULLET_SEED
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED | F_EV_SPREAD_DEFENSE | F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_NAIVE,
	},
	{
		.species = SPECIES_DONPHAN,
		.heldItem = BATTLE_TOWER_ITEM_KINGS_ROCK,
		.teamFlags = 0x05,
		.moves = {
			MOVE_ROCK_SMASH,
			MOVE_RAPID_SPIN,
			MOVE_FLAIL,
			MOVE_HORN_ATTACK
		},
		.evSpread = F_EV_SPREAD_DEFENSE | F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_IMPISH,
	},
	{
		.species = SPECIES_NOSEPASS,
		.heldItem = BATTLE_TOWER_ITEM_PERSIM_BERRY,
		.teamFlags = 0x0B,
		.moves = {
			MOVE_SANDSTORM,
			MOVE_ROCK_SLIDE,
			MOVE_BLOCK,
			MOVE_THUNDER_WAVE
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_SPEED | F_EV_SPREAD_DEFENSE,
		.nature = NATURE_JOLLY,
	},
	{
		.species = SPECIES_PINSIR,
		.heldItem = BATTLE_TOWER_ITEM_CHESTO_BERRY,
		.teamFlags = 0x05,
		.moves = {
			MOVE_SWORDS_DANCE,
			MOVE_HARDEN,
			MOVE_CUT,
			MOVE_SEISMIC_TOSS
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_DEFENSE,
		.nature = NATURE_DOCILE,
	},
	{
		.species = SPECIES_GOLDUCK,
		.heldItem = BATTLE_TOWER_ITEM_BRIGHT_POWDER,
		.teamFlags = 0x0B,
		.moves = {
			MOVE_DISABLE,
			MOVE_PSYCH_UP,
			MOVE_WATER_PULSE,
			MOVE_BRICK_BREAK
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED | F_EV_SPREAD_DEFENSE,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_SHIFTRY,
		.heldItem = BATTLE_TOWER_ITEM_MENTAL_HERB,
		.teamFlags = 0x07,
		.moves = {
			MOVE_TORMENT,
			MOVE_EXTRASENSORY,
			MOVE_SOLAR_BEAM,
			MOVE_AERIAL_ACE
		},
		.evSpread = F_EV_SPREAD_DEFENSE,
		.nature = NATURE_NAIVE,
	},
	{
		.species = SPECIES_DUSTOX,
		.heldItem = BATTLE_TOWER_ITEM_SILVER_POWDER,
		.teamFlags = 0x01,
		.moves = {
			MOVE_CONFUSION,
			MOVE_SILVER_WIND,
			MOVE_PSYBEAM,
			MOVE_WHIRLWIND
		},
		.evSpread = F_EV_SPREAD_SPEED,
		.nature = NATURE_SERIOUS,
	},
	{
		.species = SPECIES_SHUPPET,
		.heldItem = BATTLE_TOWER_ITEM_SCOPE_LENS,
		.teamFlags = 0x03,
		.moves = {
			MOVE_WILL_O_WISP,
			MOVE_NIGHT_SHADE,
			MOVE_FAINT_ATTACK,
			MOVE_CURSE
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_DEFENSE,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_SEAKING,
		.heldItem = BATTLE_TOWER_ITEM_MYSTIC_WATER,
		.teamFlags = 0x07,
		.moves = {
			MOVE_RAIN_DANCE,
			MOVE_SURF,
			MOVE_HORN_ATTACK,
			MOVE_HORN_DRILL
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE,
		.nature = NATURE_LONELY,
	},
	{
		.species = SPECIES_SKARMORY,
		.heldItem = BATTLE_TOWER_ITEM_SITRUS_BERRY,
		.teamFlags = 0x07,
		.moves = {
			MOVE_STEEL_WING,
			MOVE_SAND_ATTACK,
			MOVE_SWIFT,
			MOVE_AGILITY
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_DEFENSE,
		.nature = NATURE_RELAXED,
	},
	{
		.species = SPECIES_TORKOAL,
		.heldItem = BATTLE_TOWER_ITEM_FOCUS_BAND,
		.teamFlags = 0x43,
		.moves = {
			MOVE_FLAMETHROWER,
			MOVE_IRON_DEFENSE,
			MOVE_BODY_SLAM,
			MOVE_PROTECT
		},
		.evSpread = F_EV_SPREAD_DEFENSE | F_EV_SPREAD_ATTACK,
		.nature = NATURE_NAUGHTY,
	},
	{
		.species = SPECIES_GOLEM,
		.heldItem = BATTLE_TOWER_ITEM_SOFT_SAND,
		.teamFlags = 0x05,
		.moves = {
			MOVE_MAGNITUDE,
			MOVE_EXPLOSION,
			MOVE_STRENGTH,
			MOVE_SANDSTORM
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_ATTACK,
		.nature = NATURE_DOCILE,
	},
	{
		.species = SPECIES_GARDEVOIR,
		.heldItem = BATTLE_TOWER_ITEM_TWISTED_SPOON,
		.teamFlags = 0x41,
		.moves = {
			MOVE_REFLECT,
			MOVE_PSYCHIC,
			MOVE_IMPRISON,
			MOVE_TOXIC
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_DEFENSE,
		.nature = NATURE_HASTY,
	},
	{
		.species = SPECIES_SANDSLASH,
		.heldItem = BATTLE_TOWER_ITEM_BRIGHT_POWDER,
		.teamFlags = 0x07,
		.moves = {
			MOVE_SANDSTORM,
			MOVE_SLASH,
			MOVE_EARTHQUAKE,
			MOVE_SWIFT
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_DEFENSE,
		.nature = NATURE_ADAMANT,
	},
	{
		.species = SPECIES_WOBBUFFET,
		.heldItem = BATTLE_TOWER_ITEM_SALAC_BERRY,
		.teamFlags = 0x0B,
		.moves = {
			MOVE_COUNTER,
			MOVE_MIRROR_COAT,
			MOVE_SAFEGUARD,
			MOVE_DESTINY_BOND
		},
		.evSpread = F_EV_SPREAD_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_CALM,
	},
	{
		.species = SPECIES_TENTACRUEL,
		.heldItem = BATTLE_TOWER_ITEM_CHERI_BERRY,
		.teamFlags = 0x05,
		.moves = {
			MOVE_CONSTRICT,
			MOVE_SURF,
			MOVE_HYPER_BEAM,
			MOVE_SCREECH
		},
		.evSpread = F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_IMPISH,
	},
	{
		.species = SPECIES_TROPIUS,
		.heldItem = BATTLE_TOWER_ITEM_LEFTOVERS,
		.teamFlags = 0x05,
		.moves = {
			MOVE_SUNNY_DAY,
			MOVE_SOLAR_BEAM,
			MOVE_SYNTHESIS,
			MOVE_RAZOR_LEAF
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_DEFENSE,
		.nature = NATURE_DOCILE,
	},
	{
		.species = SPECIES_MAWILE,
		.heldItem = BATTLE_TOWER_ITEM_METAL_COAT,
		.teamFlags = 0x43,
		.moves = {
			MOVE_IRON_DEFENSE,
			MOVE_SLUDGE_BOMB,
			MOVE_CRUNCH,
			MOVE_STRENGTH
		},
		.evSpread = F_EV_SPREAD_ATTACK,
		.nature = NATURE_CALM,
	},
	{
		.species = SPECIES_MUK,
		.heldItem = BATTLE_TOWER_ITEM_RAWST_BERRY,
		.teamFlags = 0x09,
		.moves = {
			MOVE_SLUDGE,
			MOVE_ACID_ARMOR,
			MOVE_GIGA_DRAIN,
			MOVE_DISABLE
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_DEFENSE | F_EV_SPREAD_ATTACK,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_MAGCARGO,
		.heldItem = BATTLE_TOWER_ITEM_CHARCOAL,
		.teamFlags = 0x0D,
		.moves = {
			MOVE_FLAMETHROWER,
			MOVE_ROCK_THROW,
			MOVE_HARDEN,
			MOVE_AMNESIA
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_SP_ATTACK,
		.nature = NATURE_NAUGHTY,
	},
	{
		.species = SPECIES_LINOONE,
		.heldItem = BATTLE_TOWER_ITEM_PECHA_BERRY,
		.teamFlags = 0x07,
		.moves = {
			MOVE_HEADBUTT,
			MOVE_TAIL_WHIP,
			MOVE_SURF,
			MOVE_DIG
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_DEFENSE | F_EV_SPREAD_ATTACK,
		.nature = NATURE_QUIRKY,
	},
	{
		.species = SPECIES_ELECTRODE,
		.heldItem = BATTLE_TOWER_ITEM_ASPEAR_BERRY,
		.teamFlags = 0x05,
		.moves = {
			MOVE_LIGHT_SCREEN,
			MOVE_THUNDERBOLT,
			MOVE_SWIFT,
			MOVE_ROLLOUT
		},
		.evSpread = F_EV_SPREAD_SPEED,
		.nature = NATURE_SERIOUS,
	},
	{
		.species = SPECIES_DUSCLOPS,
		.heldItem = BATTLE_TOWER_ITEM_SPELL_TAG,
		.teamFlags = 0x09,
		.moves = {
			MOVE_MEAN_LOOK,
			MOVE_NIGHT_SHADE,
			MOVE_SKILL_SWAP,
			MOVE_SHADOW_BALL
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_SPEED | F_EV_SPREAD_HP,
		.nature = NATURE_NAIVE,
	},
	{
		.species = SPECIES_VILEPLUME,
		.heldItem = BATTLE_TOWER_ITEM_MIRACLE_SEED,
		.teamFlags = 0x0A,
		.moves = {
			MOVE_TOXIC,
			MOVE_MOONLIGHT,
			MOVE_GIGA_DRAIN,
			MOVE_STUN_SPORE
		},
		.evSpread = F_EV_SPREAD_HP,
		.nature = NATURE_DOCILE,
	},
	{
		.species = SPECIES_CROBAT,
		.heldItem = BATTLE_TOWER_ITEM_LEPPA_BERRY,
		.teamFlags = 0x05,
		.moves = {
			MOVE_BITE,
			MOVE_HAZE,
			MOVE_WING_ATTACK,
			MOVE_STEEL_WING
		},
		.evSpread = F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_TIMID,
	},
	{
		.species = SPECIES_CORSOLA,
		.heldItem = BATTLE_TOWER_ITEM_SCOPE_LENS,
		.teamFlags = 0x0A,
		.moves = {
			MOVE_RECOVER,
			MOVE_MIRROR_COAT,
			MOVE_HAIL,
			MOVE_SURF
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_DEFENSE,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_STARMIE,
		.heldItem = BATTLE_TOWER_ITEM_MYSTIC_WATER,
		.teamFlags = 0x0B,
		.moves = {
			MOVE_RAPID_SPIN,
			MOVE_WATER_PULSE,
			MOVE_REFLECT,
			MOVE_SKILL_SWAP
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_EXPLOUD,
		.heldItem = BATTLE_TOWER_ITEM_LEFTOVERS,
		.teamFlags = 0x41,
		.moves = {
			MOVE_HYPER_BEAM,
			MOVE_HOWL,
			MOVE_UPROAR,
			MOVE_EARTHQUAKE
		},
		.evSpread = F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_ALAKAZAM,
		.heldItem = BATTLE_TOWER_ITEM_TWISTED_SPOON,
		.teamFlags = 0x0B,
		.moves = {
			MOVE_PSYBEAM,
			MOVE_SNATCH,
			MOVE_REFLECT,
			MOVE_HYPER_BEAM
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_RELAXED,
	},
	{
		.species = SPECIES_HERACROSS,
		.heldItem = BATTLE_TOWER_ITEM_QUICK_CLAW,
		.teamFlags = 0x05,
		.moves = {
			MOVE_HORN_ATTACK,
			MOVE_COUNTER,
			MOVE_REVERSAL,
			MOVE_LEER
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_BOLD,
	},
	{
		.species = SPECIES_CASTFORM,
		.heldItem = BATTLE_TOWER_ITEM_SITRUS_BERRY,
		.teamFlags = 0x0B,
		.moves = {
			MOVE_WEATHER_BALL,
			MOVE_SUNNY_DAY,
			MOVE_RAIN_DANCE,
			MOVE_HAIL
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_LAX,
	},
	{
		.species = SPECIES_VIGOROTH,
		.heldItem = BATTLE_TOWER_ITEM_FOCUS_BAND,
		.teamFlags = 0x05,
		.moves = {
			MOVE_FOCUS_PUNCH,
			MOVE_REVERSAL,
			MOVE_COUNTER,
			MOVE_TAUNT
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_DUSKULL,
		.heldItem = BATTLE_TOWER_ITEM_BRIGHT_POWDER,
		.teamFlags = 0x09,
		.moves = {
			MOVE_TOXIC,
			MOVE_CONFUSE_RAY,
			MOVE_SHADOW_BALL,
			MOVE_WILL_O_WISP
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_LANTURN,
		.heldItem = BATTLE_TOWER_ITEM_QUICK_CLAW,
		.teamFlags = 0x07,
		.moves = {
			MOVE_FLAIL,
			MOVE_SURF,
			MOVE_SPARK,
			MOVE_TAKE_DOWN
		},
		.evSpread = F_EV_SPREAD_SPEED,
		.nature = NATURE_SASSY,
	},
	{
		.species = SPECIES_HARIYAMA,
		.heldItem = BATTLE_TOWER_ITEM_KINGS_ROCK,
		.teamFlags = 0x05,
		.moves = {
			MOVE_STRENGTH,
			MOVE_FAKE_OUT,
			MOVE_FACADE,
			MOVE_SAND_ATTACK
		},
		.evSpread = F_EV_SPREAD_SPEED,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_KINGDRA,
		.heldItem = BATTLE_TOWER_ITEM_MYSTIC_WATER,
		.teamFlags = 0x43,
		.moves = {
			MOVE_AGILITY,
			MOVE_DIVE,
			MOVE_ICE_BEAM,
			MOVE_PROTECT
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_ATTACK,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_GYARADOS,
		.heldItem = BATTLE_TOWER_ITEM_DRAGON_FANG,
		.teamFlags = 0x41,
		.moves = {
			MOVE_RAIN_DANCE,
			MOVE_SURF,
			MOVE_WATER_PULSE,
			MOVE_HYPER_BEAM
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED | F_EV_SPREAD_DEFENSE | F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_IMPISH,
	},
	{
		.species = SPECIES_AGGRON,
		.heldItem = BATTLE_TOWER_ITEM_METAL_COAT,
		.teamFlags = 0x45,
		.moves = {
			MOVE_EARTHQUAKE,
			MOVE_BRICK_BREAK,
			MOVE_METAL_CLAW,
			MOVE_ROAR
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_DEFENSE,
		.nature = NATURE_RELAXED,
	},
	{
		.species = SPECIES_ABSOL,
		.heldItem = BATTLE_TOWER_ITEM_KINGS_ROCK,
		.teamFlags = 0xC7,
		.moves = {
			MOVE_SWORDS_DANCE,
			MOVE_IRON_TAIL,
			MOVE_SLASH,
			MOVE_FACADE
		},
		.evSpread = F_EV_SPREAD_ATTACK,
		.nature = NATURE_LAX,
	},
	{
		.species = SPECIES_SWELLOW,
		.heldItem = BATTLE_TOWER_ITEM_SHARP_BEAK,
		.teamFlags = 0x0F,
		.moves = {
			MOVE_DOUBLE_TEAM,
			MOVE_FLY,
			MOVE_TOXIC,
			MOVE_STEEL_WING
		},
		.evSpread = 0,
		.nature = NATURE_HASTY,
	},
	{
		.species = SPECIES_MACHAMP,
		.heldItem = BATTLE_TOWER_ITEM_BLACK_BELT,
		.teamFlags = 0x05,
		.moves = {
			MOVE_STRENGTH,
			MOVE_CROSS_CHOP,
			MOVE_EARTHQUAKE,
			MOVE_FLAMETHROWER
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_DEFENSE,
		.nature = NATURE_HASTY,
	},
	{
		.species = SPECIES_SWAMPERT,
		.heldItem = BATTLE_TOWER_ITEM_NEVER_MELT_ICE,
		.teamFlags = 0x41,
		.moves = {
			MOVE_PROTECT,
			MOVE_ICE_BEAM,
			MOVE_HYPER_BEAM,
			MOVE_SURF
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED | F_EV_SPREAD_DEFENSE | F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_DOCILE,
	},
	{
		.species = SPECIES_SCEPTILE,
		.heldItem = BATTLE_TOWER_ITEM_MIRACLE_SEED,
		.teamFlags = 0x41,
		.moves = {
			MOVE_LEAF_BLADE,
			MOVE_DRAGON_CLAW,
			MOVE_AGILITY,
			MOVE_PROTECT
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED | F_EV_SPREAD_DEFENSE | F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_DOCILE,
	},
	{
		.species = SPECIES_BLAZIKEN,
		.heldItem = BATTLE_TOWER_ITEM_CHARCOAL,
		.teamFlags = 0x41,
		.moves = {
			MOVE_BLAZE_KICK,
			MOVE_MIRROR_MOVE,
			MOVE_EARTHQUAKE,
			MOVE_PROTECT
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED | F_EV_SPREAD_DEFENSE | F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_DOCILE,
	},
	{
		.species = SPECIES_ALTARIA,
		.heldItem = BATTLE_TOWER_ITEM_DRAGON_FANG,
		.teamFlags = 0x43,
		.moves = {
			MOVE_DRAGON_CLAW,
			MOVE_DRAGON_DANCE,
			MOVE_TOXIC,
			MOVE_DOUBLE_TEAM
		},
		.evSpread = F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_DOCILE,
	},
	{
		.species = SPECIES_LUDICOLO,
		.heldItem = BATTLE_TOWER_ITEM_BLACK_BELT,
		.teamFlags = 0x43,
		.moves = {
			MOVE_BRICK_BREAK,
			MOVE_WATER_PULSE,
			MOVE_RAIN_DANCE,
			MOVE_FOCUS_PUNCH
		},
		.evSpread = F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_HASTY,
	},
	{
		.species = SPECIES_SABLEYE,
		.heldItem = BATTLE_TOWER_ITEM_SPELL_TAG,
		.teamFlags = 0x49,
		.moves = {
			MOVE_SHADOW_BALL,
			MOVE_SNATCH,
			MOVE_DIG,
			MOVE_CONFUSE_RAY
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_DEFENSE,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_ZANGOOSE,
		.heldItem = BATTLE_TOWER_ITEM_BLACK_GLASSES,
		.teamFlags = 0x0F,
		.moves = {
			MOVE_FACADE,
			MOVE_THUNDERBOLT,
			MOVE_CRUSH_CLAW,
			MOVE_DETECT
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_HP,
		.nature = NATURE_CALM,
	},
	{
		.species = SPECIES_LINOONE,
		.heldItem = BATTLE_TOWER_ITEM_CHESTO_BERRY,
		.teamFlags = 0x0F,
		.moves = {
			MOVE_IRON_TAIL,
			MOVE_HEADBUTT,
			MOVE_ATTRACT,
			MOVE_ICE_BEAM
		},
		.evSpread = F_EV_SPREAD_DEFENSE | F_EV_SPREAD_ATTACK,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_WHISCASH,
		.heldItem = BATTLE_TOWER_ITEM_SOFT_SAND,
		.teamFlags = 0x07,
		.moves = {
			MOVE_MUD_SLAP,
			MOVE_EARTHQUAKE,
			MOVE_SURF,
			MOVE_AMNESIA
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_SPEED | F_EV_SPREAD_HP,
		.nature = NATURE_BOLD,
	},
	{
		.species = SPECIES_SOLROCK,
		.heldItem = BATTLE_TOWER_ITEM_HARD_STONE,
		.teamFlags = 0x43,
		.moves = {
			MOVE_EARTHQUAKE,
			MOVE_LIGHT_SCREEN,
			MOVE_ROCK_SLIDE,
			MOVE_CONFUSION
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_BASHFUL,
	},
	{
		.species = SPECIES_STARMIE,
		.heldItem = BATTLE_TOWER_ITEM_BRIGHT_POWDER,
		.teamFlags = 0x03,
		.moves = {
			MOVE_RECOVER,
			MOVE_RAIN_DANCE,
			MOVE_SURF,
			MOVE_CONFUSE_RAY
		},
		.evSpread = F_EV_SPREAD_DEFENSE | F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_NAIVE,
	},
	{
		.species = SPECIES_CACTURNE,
		.heldItem = BATTLE_TOWER_ITEM_LEFTOVERS,
		.teamFlags = 0x0F,
		.moves = {
			MOVE_INGRAIN,
			MOVE_LEECH_SEED,
			MOVE_PROTECT,
			MOVE_FRUSTRATION
		},
		.evSpread = 0,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_SHIFTRY,
		.heldItem = BATTLE_TOWER_ITEM_FOCUS_BAND,
		.teamFlags = 0x05,
		.moves = {
			MOVE_FRUSTRATION,
			MOVE_HYPER_BEAM,
			MOVE_GIGA_DRAIN,
			MOVE_TORMENT
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED | F_EV_SPREAD_DEFENSE,
		.nature = NATURE_ADAMANT,
	},
	{
		.species = SPECIES_MANECTRIC,
		.heldItem = BATTLE_TOWER_ITEM_MAGNET,
		.teamFlags = 0x0F,
		.moves = {
			MOVE_THUNDER,
			MOVE_THUNDER_WAVE,
			MOVE_IRON_TAIL,
			MOVE_ROAR
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_ADAMANT,
	},
	{
		.species = SPECIES_KECLEON,
		.heldItem = BATTLE_TOWER_ITEM_BRIGHT_POWDER,
		.teamFlags = 0xC3,
		.moves = {
			MOVE_THUNDERBOLT,
			MOVE_FOCUS_PUNCH,
			MOVE_IRON_TAIL,
			MOVE_FLAMETHROWER
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_QUIET,
	},
	{
		.species = SPECIES_PINSIR,
		.heldItem = BATTLE_TOWER_ITEM_SOFT_SAND,
		.teamFlags = 0x8D,
		.moves = {
			MOVE_GUILLOTINE,
			MOVE_SUBMISSION,
			MOVE_EARTHQUAKE,
			MOVE_ROCK_TOMB
		},
		.evSpread = F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_METANG,
		.heldItem = BATTLE_TOWER_ITEM_METAL_COAT,
		.teamFlags = 0x05,
		.moves = {
			MOVE_EARTHQUAKE,
			MOVE_SHADOW_BALL,
			MOVE_PSYCHIC,
			MOVE_METEOR_MASH
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_DEFENSE | F_EV_SPREAD_ATTACK,
		.nature = NATURE_IMPISH,
	},
	{
		.species = SPECIES_CLAYDOL,
		.heldItem = BATTLE_TOWER_ITEM_PECHA_BERRY,
		.teamFlags = 0x43,
		.moves = {
			MOVE_EARTHQUAKE,
			MOVE_SELF_DESTRUCT,
			MOVE_SANDSTORM,
			MOVE_PROTECT
		},
		.evSpread = F_EV_SPREAD_DEFENSE | F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_LAX,
	},
	{
		.species = SPECIES_MASQUERAIN,
		.heldItem = BATTLE_TOWER_ITEM_PERSIM_BERRY,
		.teamFlags = 0x0A,
		.moves = {
			MOVE_TOXIC,
			MOVE_SILVER_WIND,
			MOVE_ATTRACT,
			MOVE_ICE_BEAM
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_SP_ATTACK,
		.nature = NATURE_QUIET,
	},
	{
		.species = SPECIES_RELICANTH,
		.heldItem = BATTLE_TOWER_ITEM_LIECHI_BERRY,
		.teamFlags = 0xC5,
		.moves = {
			MOVE_ROCK_TOMB,
			MOVE_DOUBLE_EDGE,
			MOVE_SURF,
			MOVE_EARTHQUAKE
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_ATTACK,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_WALREIN,
		.heldItem = BATTLE_TOWER_ITEM_SALAC_BERRY,
		.teamFlags = 0x0D,
		.moves = {
			MOVE_SURF,
			MOVE_ENCORE,
			MOVE_BLIZZARD,
			MOVE_HYPER_BEAM
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_ATTACK,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_WAILORD,
		.heldItem = BATTLE_TOWER_ITEM_APICOT_BERRY,
		.teamFlags = 0x0B,
		.moves = {
			MOVE_WATER_SPOUT,
			MOVE_REST,
			MOVE_AMNESIA,
			MOVE_HAIL
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_DEFENSE,
		.nature = NATURE_HASTY,
	},
	{
		.species = SPECIES_GIRAFARIG,
		.heldItem = BATTLE_TOWER_ITEM_GANLON_BERRY,
		.teamFlags = 0x4F,
		.moves = {
			MOVE_DOUBLE_TEAM,
			MOVE_CRUNCH,
			MOVE_PSYCHIC,
			MOVE_EARTHQUAKE
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_DEFENSE | F_EV_SPREAD_ATTACK,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_MEDICHAM,
		.heldItem = BATTLE_TOWER_ITEM_APICOT_BERRY,
		.teamFlags = 0x4B,
		.moves = {
			MOVE_CALM_MIND,
			MOVE_REVERSAL,
			MOVE_ROCK_TOMB,
			MOVE_PSYCHIC
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED | F_EV_SPREAD_DEFENSE | F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_RELAXED,
	},
	{
		.species = SPECIES_TROPIUS,
		.heldItem = BATTLE_TOWER_ITEM_MENTAL_HERB,
		.teamFlags = 0xC7,
		.moves = {
			MOVE_EARTHQUAKE,
			MOVE_SYNTHESIS,
			MOVE_RAZOR_LEAF,
			MOVE_HYPER_BEAM
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_SPEED | F_EV_SPREAD_ATTACK,
		.nature = NATURE_BOLD,
	},
	{
		.species = SPECIES_NINJASK,
		.heldItem = BATTLE_TOWER_ITEM_SCOPE_LENS,
		.teamFlags = 0x05,
		.moves = {
			MOVE_DOUBLE_TEAM,
			MOVE_SLASH,
			MOVE_SWORDS_DANCE,
			MOVE_LEECH_LIFE
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_LAX,
	},
	{
		.species = SPECIES_CAMERUPT,
		.heldItem = BATTLE_TOWER_ITEM_CHARCOAL,
		.teamFlags = 0x0D,
		.moves = {
			MOVE_EARTHQUAKE,
			MOVE_OVERHEAT,
			MOVE_SUNNY_DAY,
			MOVE_ROCK_SLIDE
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_CAREFUL,
	},
	{
		.species = SPECIES_SHARPEDO,
		.heldItem = BATTLE_TOWER_ITEM_KINGS_ROCK,
		.teamFlags = 0x05,
		.moves = {
			MOVE_CRUNCH,
			MOVE_SURF,
			MOVE_EARTHQUAKE,
			MOVE_PROTECT
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED | F_EV_SPREAD_ATTACK,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_WIGGLYTUFF,
		.heldItem = BATTLE_TOWER_ITEM_SALAC_BERRY,
		.teamFlags = 0x0E,
		.moves = {
			MOVE_PROTECT,
			MOVE_TOXIC,
			MOVE_DOUBLE_TEAM,
			MOVE_DIG
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_DEFENSE,
		.nature = NATURE_LAX,
	},
	{
		.species = SPECIES_SEVIPER,
		.heldItem = BATTLE_TOWER_ITEM_POISON_BARB,
		.teamFlags = 0x05,
		.moves = {
			MOVE_SLUDGE_BOMB,
			MOVE_HAZE,
			MOVE_CRUNCH,
			MOVE_FLAMETHROWER
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_ATTACK,
		.nature = NATURE_NAIVE,
	},
	{
		.species = SPECIES_CRADILY,
		.heldItem = BATTLE_TOWER_ITEM_LEFTOVERS,
		.teamFlags = 0xC1,
		.moves = {
			MOVE_ROCK_TOMB,
			MOVE_CONFUSE_RAY,
			MOVE_INGRAIN,
			MOVE_EARTHQUAKE
		},
		.evSpread = F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_ARMALDO,
		.heldItem = BATTLE_TOWER_ITEM_RAWST_BERRY,
		.teamFlags = 0xC1,
		.moves = {
			MOVE_EARTHQUAKE,
			MOVE_SANDSTORM,
			MOVE_PROTECT,
			MOVE_SLASH
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_DEFENSE | F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_MAGNETON,
		.heldItem = BATTLE_TOWER_ITEM_PERSIM_BERRY,
		.teamFlags = 0x0D,
		.moves = {
			MOVE_ZAP_CANNON,
			MOVE_SUPERSONIC,
			MOVE_TOXIC,
			MOVE_PROTECT
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED,
		.nature = NATURE_ADAMANT,
	},
	{
		.species = SPECIES_LANTURN,
		.heldItem = BATTLE_TOWER_ITEM_QUICK_CLAW,
		.teamFlags = 0x06,
		.moves = {
			MOVE_THUNDER,
			MOVE_SURF,
			MOVE_ICE_BEAM,
			MOVE_RAIN_DANCE
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_DEFENSE,
		.nature = NATURE_ADAMANT,
	},
	{
		.species = SPECIES_SWALOT,
		.heldItem = BATTLE_TOWER_ITEM_CHERI_BERRY,
		.teamFlags = 0x8B,
		.moves = {
			MOVE_SLUDGE_BOMB,
			MOVE_SNATCH,
			MOVE_ENCORE,
			MOVE_BODY_SLAM
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_ATTACK,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_SKARMORY,
		.heldItem = BATTLE_TOWER_ITEM_METAL_COAT,
		.teamFlags = 0x81,
		.moves = {
			MOVE_STEEL_WING,
			MOVE_AGILITY,
			MOVE_TORMENT,
			MOVE_FACADE
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_LAX,
	},
	{
		.species = SPECIES_DONPHAN,
		.heldItem = BATTLE_TOWER_ITEM_WHITE_HERB,
		.teamFlags = 0x0D,
		.moves = {
			MOVE_EARTHQUAKE,
			MOVE_FLAIL,
			MOVE_ROAR,
			MOVE_IRON_TAIL
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_HERACROSS,
		.heldItem = BATTLE_TOWER_ITEM_FOCUS_BAND,
		.teamFlags = 0x41,
		.moves = {
			MOVE_FACADE,
			MOVE_REVERSAL,
			MOVE_MEGAHORN,
			MOVE_EARTHQUAKE
		},
		.evSpread = F_EV_SPREAD_DEFENSE | F_EV_SPREAD_ATTACK,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_BANETTE,
		.heldItem = BATTLE_TOWER_ITEM_PETAYA_BERRY,
		.teamFlags = 0x83,
		.moves = {
			MOVE_SHADOW_BALL,
			MOVE_HYPER_BEAM,
			MOVE_THUNDERBOLT,
			MOVE_SKILL_SWAP
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_DEFENSE,
		.nature = NATURE_CAREFUL,
	},
	{
		.species = SPECIES_SANDSLASH,
		.heldItem = BATTLE_TOWER_ITEM_BRIGHT_POWDER,
		.teamFlags = 0x0F,
		.moves = {
			MOVE_SANDSTORM,
			MOVE_TOXIC,
			MOVE_SLASH,
			MOVE_EARTHQUAKE
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_LAX,
	},
	{
		.species = SPECIES_CRAWDAUNT,
		.heldItem = BATTLE_TOWER_ITEM_SCOPE_LENS,
		.teamFlags = 0x05,
		.moves = {
			MOVE_GUILLOTINE,
			MOVE_CRABHAMMER,
			MOVE_BLIZZARD,
			MOVE_SLUDGE_BOMB
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED | F_EV_SPREAD_DEFENSE | F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_DOCILE,
	},
	{
		.species = SPECIES_GRUMPIG,
		.heldItem = BATTLE_TOWER_ITEM_TWISTED_SPOON,
		.teamFlags = 0x8B,
		.moves = {
			MOVE_MAGIC_COAT,
			MOVE_PSYCHIC,
			MOVE_REFLECT,
			MOVE_CONFUSE_RAY
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_LONELY,
	},
	{
		.species = SPECIES_RHYDON,
		.heldItem = BATTLE_TOWER_ITEM_CHOICE_BAND,
		.teamFlags = 0x45,
		.moves = {
			MOVE_IRON_TAIL,
			MOVE_EARTHQUAKE,
			MOVE_SURF,
			MOVE_FIRE_BLAST
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_SP_ATTACK,
		.nature = NATURE_RASH,
	},
	{
		.species = SPECIES_ALAKAZAM,
		.heldItem = BATTLE_TOWER_ITEM_PETAYA_BERRY,
		.teamFlags = 0x8B,
		.moves = {
			MOVE_PSYCHIC,
			MOVE_REFLECT,
			MOVE_RECOVER,
			MOVE_SKILL_SWAP
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_DEFENSE,
		.nature = NATURE_HASTY,
	},
	{
		.species = SPECIES_DUSCLOPS,
		.heldItem = BATTLE_TOWER_ITEM_SITRUS_BERRY,
		.teamFlags = 0x41,
		.moves = {
			MOVE_SHADOW_BALL,
			MOVE_WILL_O_WISP,
			MOVE_BLIZZARD,
			MOVE_PSYCHIC
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_ATTACK,
		.nature = NATURE_CAREFUL,
	},
	{
		.species = SPECIES_TORKOAL,
		.heldItem = BATTLE_TOWER_ITEM_LEFTOVERS,
		.teamFlags = 0x09,
		.moves = {
			MOVE_FLAMETHROWER,
			MOVE_AMNESIA,
			MOVE_IRON_TAIL,
			MOVE_REST
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_SP_ATTACK,
		.nature = NATURE_NAIVE,
	},
	{
		.species = SPECIES_ELECTRODE,
		.heldItem = BATTLE_TOWER_ITEM_LUM_BERRY,
		.teamFlags = 0x09,
		.moves = {
			MOVE_SCREECH,
			MOVE_EXPLOSION,
			MOVE_MIRROR_COAT,
			MOVE_PROTECT
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_HP,
		.nature = NATURE_RASH,
	},
	{
		.species = SPECIES_BRELOOM,
		.heldItem = BATTLE_TOWER_ITEM_LIECHI_BERRY,
		.teamFlags = 0x0B,
		.moves = {
			MOVE_IRON_TAIL,
			MOVE_FOCUS_PUNCH,
			MOVE_DOUBLE_TEAM,
			MOVE_LEECH_SEED
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_LAX,
	},
	{
		.species = SPECIES_MUK,
		.heldItem = BATTLE_TOWER_ITEM_POISON_BARB,
		.teamFlags = 0x05,
		.moves = {
			MOVE_SLUDGE_BOMB,
			MOVE_THUNDERBOLT,
			MOVE_FLAMETHROWER,
			MOVE_FOCUS_PUNCH
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_NAIVE,
	},
	{
		.species = SPECIES_WEEZING,
		.heldItem = BATTLE_TOWER_ITEM_QUICK_CLAW,
		.teamFlags = 0x05,
		.moves = {
			MOVE_EXPLOSION,
			MOVE_SLUDGE_BOMB,
			MOVE_SHADOW_BALL,
			MOVE_FLAMETHROWER
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_NAIVE,
	},
	{
		.species = SPECIES_RAICHU,
		.heldItem = BATTLE_TOWER_ITEM_SCOPE_LENS,
		.teamFlags = 0x4E,
		.moves = {
			MOVE_THUNDERBOLT,
			MOVE_DOUBLE_TEAM,
			MOVE_FOCUS_PUNCH,
			MOVE_ATTRACT
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED | F_EV_SPREAD_DEFENSE | F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_JOLLY,
	},
	{
		.species = SPECIES_TENTACRUEL,
		.heldItem = BATTLE_TOWER_ITEM_MYSTIC_WATER,
		.teamFlags = 0x09,
		.moves = {
			MOVE_DOUBLE_TEAM,
			MOVE_TOXIC,
			MOVE_SURF,
			MOVE_SLUDGE_BOMB
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_BOLD,
	},
	{
		.species = SPECIES_EXPLOUD,
		.heldItem = BATTLE_TOWER_ITEM_CHOICE_BAND,
		.teamFlags = 0x05,
		.moves = {
			MOVE_BLIZZARD,
			MOVE_FLAMETHROWER,
			MOVE_EARTHQUAKE,
			MOVE_RETURN
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_BASHFUL,
	},
	{
		.species = SPECIES_XATU,
		.heldItem = BATTLE_TOWER_ITEM_WHITE_HERB,
		.teamFlags = 0x43,
		.moves = {
			MOVE_PSYCHIC,
			MOVE_REST,
			MOVE_CONFUSE_RAY,
			MOVE_TOXIC
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED,
		.nature = NATURE_BRAVE,
	},
	{
		.species = SPECIES_GOLEM,
		.heldItem = BATTLE_TOWER_ITEM_SALAC_BERRY,
		.teamFlags = 0x05,
		.moves = {
			MOVE_EXPLOSION,
			MOVE_EARTHQUAKE,
			MOVE_ROCK_TOMB,
			MOVE_FLAMETHROWER
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_IMPISH,
	},
	{
		.species = SPECIES_GOLDUCK,
		.heldItem = BATTLE_TOWER_ITEM_PECHA_BERRY,
		.teamFlags = 0x83,
		.moves = {
			MOVE_SURF,
			MOVE_ATTRACT,
			MOVE_CALM_MIND,
			MOVE_BLIZZARD
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED | F_EV_SPREAD_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_HASTY,
	},
	{
		.species = SPECIES_NINETALES,
		.heldItem = BATTLE_TOWER_ITEM_CHARCOAL,
		.teamFlags = 0x4A,
		.moves = {
			MOVE_FLAMETHROWER,
			MOVE_ATTRACT,
			MOVE_TOXIC,
			MOVE_CONFUSE_RAY
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_DEFENSE,
		.nature = NATURE_QUIET,
	},
	{
		.species = SPECIES_KINGDRA,
		.heldItem = BATTLE_TOWER_ITEM_CHESTO_BERRY,
		.teamFlags = 0x13,
		.moves = {
			MOVE_DOUBLE_TEAM,
			MOVE_REST,
			MOVE_SURF,
			MOVE_DRAGON_BREATH
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_DEFENSE,
		.nature = NATURE_ADAMANT,
	},
	{
		.species = SPECIES_SLAKING,
		.heldItem = BATTLE_TOWER_ITEM_LEFTOVERS,
		.teamFlags = 0x03,
		.moves = {
			MOVE_CURSE,
			MOVE_AMNESIA,
			MOVE_YAWN,
			MOVE_FOCUS_PUNCH
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_DEFENSE,
		.nature = NATURE_LAX,
	},
	{
		.species = SPECIES_GYARADOS,
		.heldItem = BATTLE_TOWER_ITEM_CHERI_BERRY,
		.teamFlags = 0x03,
		.moves = {
			MOVE_THUNDER,
			MOVE_EARTHQUAKE,
			MOVE_HYDRO_PUMP,
			MOVE_RAIN_DANCE
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_SP_ATTACK,
		.nature = NATURE_NAUGHTY,
	},
	{
		.species = SPECIES_HARIYAMA,
		.heldItem = BATTLE_TOWER_ITEM_SALAC_BERRY,
		.teamFlags = 0x21,
		.moves = {
			MOVE_BELLY_DRUM,
			MOVE_ENDURE,
			MOVE_EARTHQUAKE,
			MOVE_REVERSAL
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_SPEED,
		.nature = NATURE_SASSY,
	},
	{
		.species = SPECIES_ABSOL,
		.heldItem = BATTLE_TOWER_ITEM_KINGS_ROCK,
		.teamFlags = 0xC3,
		.moves = {
			MOVE_FAINT_ATTACK,
			MOVE_DOUBLE_EDGE,
			MOVE_SHADOW_BALL,
			MOVE_FLAMETHROWER
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_SPEED | F_EV_SPREAD_DEFENSE,
		.nature = NATURE_RELAXED,
	},
	{
		.species = SPECIES_ALTARIA,
		.heldItem = BATTLE_TOWER_ITEM_SITRUS_BERRY,
		.teamFlags = 0x83,
		.moves = {
			MOVE_DRAGON_DANCE,
			MOVE_MIRROR_MOVE,
			MOVE_DRAGON_CLAW,
			MOVE_EARTHQUAKE
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED,
		.nature = NATURE_RASH,
	},
	{
		.species = SPECIES_MACHAMP,
		.heldItem = BATTLE_TOWER_ITEM_BLACK_BELT,
		.teamFlags = 0x11,
		.moves = {
			MOVE_CROSS_CHOP,
			MOVE_FOCUS_PUNCH,
			MOVE_ROCK_TOMB,
			MOVE_ENCORE
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_SPEED,
		.nature = NATURE_SASSY,
	},
	{
		.species = SPECIES_FLYGON,
		.heldItem = BATTLE_TOWER_ITEM_DRAGON_FANG,
		.teamFlags = 0x43,
		.moves = {
			MOVE_CRUNCH,
			MOVE_DRAGON_CLAW,
			MOVE_EARTHQUAKE,
			MOVE_FLAMETHROWER
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_NAIVE,
	},
	{
		.species = SPECIES_BLAZIKEN,
		.heldItem = BATTLE_TOWER_ITEM_PETAYA_BERRY,
		.teamFlags = 0x33,
		.moves = {
			MOVE_COUNTER,
			MOVE_ROCK_SLIDE,
			MOVE_FOCUS_PUNCH,
			MOVE_FLAMETHROWER
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_ATTACK,
		.nature = NATURE_GENTLE,
	},
	{
		.species = SPECIES_GLALIE,
		.heldItem = BATTLE_TOWER_ITEM_NEVER_MELT_ICE,
		.teamFlags = 0x81,
		.moves = {
			MOVE_BLIZZARD,
			MOVE_CRUNCH,
			MOVE_ICY_WIND,
			MOVE_DOUBLE_TEAM
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED | F_EV_SPREAD_DEFENSE | F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_JOLLY,
	},
	{
		.species = SPECIES_HUNTAIL,
		.heldItem = BATTLE_TOWER_ITEM_MYSTIC_WATER,
		.teamFlags = 0xA1,
		.moves = {
			MOVE_RAIN_DANCE,
			MOVE_HYDRO_PUMP,
			MOVE_CRUNCH,
			MOVE_BLIZZARD
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_QUIET,
	},
	{
		.species = SPECIES_MILOTIC,
		.heldItem = BATTLE_TOWER_ITEM_GANLON_BERRY,
		.teamFlags = 0xD3,
		.moves = {
			MOVE_SURF,
			MOVE_ATTRACT,
			MOVE_RECOVER,
			MOVE_TOXIC
		},
		.evSpread = F_EV_SPREAD_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_HASTY,
	},
	{
		.species = SPECIES_GOREBYSS,
		.heldItem = BATTLE_TOWER_ITEM_PECHA_BERRY,
		.teamFlags = 0x83,
		.moves = {
			MOVE_PSYCHIC,
			MOVE_SURF,
			MOVE_BLIZZARD,
			MOVE_SHADOW_BALL
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_ADAMANT,
	},
	{
		.species = SPECIES_SCEPTILE,
		.heldItem = BATTLE_TOWER_ITEM_SCOPE_LENS,
		.teamFlags = 0x53,
		.moves = {
			MOVE_LEAF_BLADE,
			MOVE_ENDEAVOR,
			MOVE_EARTHQUAKE,
			MOVE_ROCK_TOMB
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_SPEED,
		.nature = NATURE_BASHFUL,
	},
	{
		.species = SPECIES_SWAMPERT,
		.heldItem = BATTLE_TOWER_ITEM_LEFTOVERS,
		.teamFlags = 0x53,
		.moves = {
			MOVE_EARTHQUAKE,
			MOVE_SURF,
			MOVE_MUD_SHOT,
			MOVE_BLIZZARD
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_NAIVE,
	},
	{
		.species = SPECIES_AGGRON,
		.heldItem = BATTLE_TOWER_ITEM_MENTAL_HERB,
		.teamFlags = 0x41,
		.moves = {
			MOVE_DOUBLE_EDGE,
			MOVE_FLAMETHROWER,
			MOVE_IRON_TAIL,
			MOVE_BLIZZARD
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_BOLD,
	},
	{
		.species = SPECIES_CRADILY,
		.heldItem = BATTLE_TOWER_ITEM_BRIGHT_POWDER,
		.teamFlags = 0xE1,
		.moves = {
			MOVE_STOCKPILE,
			MOVE_SPIT_UP,
			MOVE_SWALLOW,
			MOVE_DOUBLE_TEAM
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_LAX,
	},
	{
		.species = SPECIES_ARMALDO,
		.heldItem = BATTLE_TOWER_ITEM_QUICK_CLAW,
		.teamFlags = 0xC1,
		.moves = {
			MOVE_EARTHQUAKE,
			MOVE_HYPER_BEAM,
			MOVE_SLASH,
			MOVE_SWORDS_DANCE
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_LAX,
	},
	{
		.species = SPECIES_BRELOOM,
		.heldItem = BATTLE_TOWER_ITEM_SHELL_BELL,
		.teamFlags = 0x82,
		.moves = {
			MOVE_FOCUS_PUNCH,
			MOVE_COUNTER,
			MOVE_MACH_PUNCH,
			MOVE_SNATCH
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_LAX,
	},
	{
		.species = SPECIES_LUDICOLO,
		.heldItem = BATTLE_TOWER_ITEM_PETAYA_BERRY,
		.teamFlags = 0x83,
		.moves = {
			MOVE_RAIN_DANCE,
			MOVE_SURF,
			MOVE_PROTECT,
			MOVE_TOXIC
		},
		.evSpread = F_EV_SPREAD_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_HASTY,
	},
	{
		.species = SPECIES_SHIFTRY,
		.heldItem = BATTLE_TOWER_ITEM_SCOPE_LENS,
		.teamFlags = 0x03,
		.moves = {
			MOVE_TORMENT,
			MOVE_FAINT_ATTACK,
			MOVE_SHADOW_BALL,
			MOVE_EXPLOSION
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_NAIVE,
	},
	{
		.species = SPECIES_TROPIUS,
		.heldItem = BATTLE_TOWER_ITEM_APICOT_BERRY,
		.teamFlags = 0xC3,
		.moves = {
			MOVE_SUNNY_DAY,
			MOVE_SYNTHESIS,
			MOVE_SOLAR_BEAM,
			MOVE_LEECH_SEED
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_DEFENSE,
		.nature = NATURE_QUIET,
	},
	{
		.species = SPECIES_GRUMPIG,
		.heldItem = BATTLE_TOWER_ITEM_MACHO_BRACE,
		.teamFlags = 0x23,
		.moves = {
			MOVE_TRICK,
			MOVE_SKILL_SWAP,
			MOVE_PSYCHIC,
			MOVE_REST
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_TORKOAL,
		.heldItem = BATTLE_TOWER_ITEM_LUM_BERRY,
		.teamFlags = 0x81,
		.moves = {
			MOVE_IRON_DEFENSE,
			MOVE_TOXIC,
			MOVE_REST,
			MOVE_FLAMETHROWER
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_NAIVE,
	},
	{
		.species = SPECIES_MANECTRIC,
		.heldItem = BATTLE_TOWER_ITEM_NONE,
		.teamFlags = 0x03,
		.moves = {
			MOVE_THUNDERBOLT,
			MOVE_CRUNCH,
			MOVE_ROAR,
			MOVE_THIEF
		},
		.evSpread = F_EV_SPREAD_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_HASTY,
	},
	{
		.species = SPECIES_PINSIR,
		.heldItem = BATTLE_TOWER_ITEM_LEPPA_BERRY,
		.teamFlags = 0x61,
		.moves = {
			MOVE_GUILLOTINE,
			MOVE_EARTHQUAKE,
			MOVE_DOUBLE_TEAM,
			MOVE_ROCK_TOMB
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_LAX,
	},
	{
		.species = SPECIES_STARMIE,
		.heldItem = BATTLE_TOWER_ITEM_CHESTO_BERRY,
		.teamFlags = 0x93,
		.moves = {
			MOVE_LIGHT_SCREEN,
			MOVE_THUNDERBOLT,
			MOVE_SURF,
			MOVE_REST
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_ADAMANT,
	},
	{
		.species = SPECIES_HERACROSS,
		.heldItem = BATTLE_TOWER_ITEM_SALAC_BERRY,
		.teamFlags = 0x51,
		.moves = {
			MOVE_MEGAHORN,
			MOVE_REVERSAL,
			MOVE_EARTHQUAKE,
			MOVE_COUNTER
		},
		.evSpread = F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_WALREIN,
		.heldItem = BATTLE_TOWER_ITEM_NEVER_MELT_ICE,
		.teamFlags = 0x83,
		.moves = {
			MOVE_BLIZZARD,
			MOVE_EARTHQUAKE,
			MOVE_SURF,
			MOVE_ROCK_SLIDE
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_CAREFUL,
	},
	{
		.species = SPECIES_ALAKAZAM,
		.heldItem = BATTLE_TOWER_ITEM_SITRUS_BERRY,
		.teamFlags = 0x13,
		.moves = {
			MOVE_PSYCHIC,
			MOVE_RECOVER,
			MOVE_ENCORE,
			MOVE_SNATCH
		},
		.evSpread = F_EV_SPREAD_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_HASTY,
	},
	{
		.species = SPECIES_MILOTIC,
		.heldItem = BATTLE_TOWER_ITEM_APICOT_BERRY,
		.teamFlags = 0x93,
		.moves = {
			MOVE_SURF,
			MOVE_BLIZZARD,
			MOVE_RECOVER,
			MOVE_DOUBLE_TEAM
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_HP,
		.nature = NATURE_QUIET,
	},
	{
		.species = SPECIES_REGICE,
		.heldItem = BATTLE_TOWER_ITEM_CHESTO_BERRY,
		.teamFlags = 0x11,
		.moves = {
			MOVE_REST,
			MOVE_CURSE,
			MOVE_BLIZZARD,
			MOVE_EARTHQUAKE
		},
		.evSpread = F_EV_SPREAD_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_MILD,
	},
	{
		.species = SPECIES_REGISTEEL,
		.heldItem = BATTLE_TOWER_ITEM_LUM_BERRY,
		.teamFlags = 0x11,
		.moves = {
			MOVE_REST,
			MOVE_IRON_DEFENSE,
			MOVE_THUNDERBOLT,
			MOVE_EARTHQUAKE
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_ATTACK,
		.nature = NATURE_MILD,
	},
	{
		.species = SPECIES_REGIROCK,
		.heldItem = BATTLE_TOWER_ITEM_QUICK_CLAW,
		.teamFlags = 0x91,
		.moves = {
			MOVE_ROCK_TOMB,
			MOVE_EARTHQUAKE,
			MOVE_THUNDERBOLT,
			MOVE_EXPLOSION
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_HP,
		.nature = NATURE_SASSY,
	},
	{
		.species = SPECIES_DUSCLOPS,
		.heldItem = BATTLE_TOWER_ITEM_SPELL_TAG,
		.teamFlags = 0x20,
		.moves = {
			MOVE_SHADOW_BALL,
			MOVE_EARTHQUAKE,
			MOVE_BLIZZARD,
			MOVE_DESTINY_BOND
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED,
		.nature = NATURE_NAUGHTY,
	},
	{
		.species = SPECIES_SEAKING,
		.heldItem = BATTLE_TOWER_ITEM_LEPPA_BERRY,
		.teamFlags = 0xB2,
		.moves = {
			MOVE_HORN_DRILL,
			MOVE_AGILITY,
			MOVE_SLEEP_TALK,
			MOVE_REST
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_BRAVE,
	},
	{
		.species = SPECIES_CAMERUPT,
		.heldItem = BATTLE_TOWER_ITEM_BRIGHT_POWDER,
		.teamFlags = 0x00,
		.moves = {
			MOVE_EARTHQUAKE,
			MOVE_ERUPTION,
			MOVE_ROCK_SLIDE,
			MOVE_FLAMETHROWER
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_NAIVE,
	},
	{
		.species = SPECIES_LANTURN,
		.heldItem = BATTLE_TOWER_ITEM_SALAC_BERRY,
		.teamFlags = 0x82,
		.moves = {
			MOVE_THUNDERBOLT,
			MOVE_SURF,
			MOVE_THUNDER_WAVE,
			MOVE_BLIZZARD
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED | F_EV_SPREAD_HP,
		.nature = NATURE_BRAVE,
	},
	{
		.species = SPECIES_WEEZING,
		.heldItem = BATTLE_TOWER_ITEM_SALAC_BERRY,
		.teamFlags = 0x20,
		.moves = {
			MOVE_SLUDGE_BOMB,
			MOVE_THUNDERBOLT,
			MOVE_FIRE_BLAST,
			MOVE_EXPLOSION
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_HP,
		.nature = NATURE_SERIOUS,
	},
	{
		.species = SPECIES_WHISCASH,
		.heldItem = BATTLE_TOWER_ITEM_PETAYA_BERRY,
		.teamFlags = 0x41,
		.moves = {
			MOVE_EARTHQUAKE,
			MOVE_SURF,
			MOVE_ROCK_TOMB,
			MOVE_ATTRACT
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_DEFENSE | F_EV_SPREAD_ATTACK,
		.nature = NATURE_RELAXED,
	},
	{
		.species = SPECIES_AGGRON,
		.heldItem = BATTLE_TOWER_ITEM_LIECHI_BERRY,
		.teamFlags = 0x11,
		.moves = {
			MOVE_DOUBLE_EDGE,
			MOVE_EARTHQUAKE,
			MOVE_SURF,
			MOVE_DRAGON_CLAW
		},
		.evSpread = F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_GENTLE,
	},
	{
		.species = SPECIES_CACTURNE,
		.heldItem = BATTLE_TOWER_ITEM_SCOPE_LENS,
		.teamFlags = 0x63,
		.moves = {
			MOVE_DYNAMIC_PUNCH,
			MOVE_COUNTER,
			MOVE_FAINT_ATTACK,
			MOVE_GIGA_DRAIN
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_ATTACK,
		.nature = NATURE_RELAXED,
	},
	{
		.species = SPECIES_SHARPEDO,
		.heldItem = BATTLE_TOWER_ITEM_KINGS_ROCK,
		.teamFlags = 0x01,
		.moves = {
			MOVE_CRUNCH,
			MOVE_DOUBLE_EDGE,
			MOVE_SURF,
			MOVE_SWAGGER
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_ATTACK,
		.nature = NATURE_SASSY,
	},
	{
		.species = SPECIES_ABSOL,
		.heldItem = BATTLE_TOWER_ITEM_SALAC_BERRY,
		.teamFlags = 0x82,
		.moves = {
			MOVE_DOUBLE_EDGE,
			MOVE_FACADE,
			MOVE_SWORDS_DANCE,
			MOVE_QUICK_ATTACK
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_WAILORD,
		.heldItem = BATTLE_TOWER_ITEM_LEPPA_BERRY,
		.teamFlags = 0x23,
		.moves = {
			MOVE_HYDRO_PUMP,
			MOVE_EARTHQUAKE,
			MOVE_ATTRACT,
			MOVE_FISSURE
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_HP,
		.nature = NATURE_TIMID,
	},
	{
		.species = SPECIES_TENTACRUEL,
		.heldItem = BATTLE_TOWER_ITEM_SITRUS_BERRY,
		.teamFlags = 0x21,
		.moves = {
			MOVE_HYDRO_PUMP,
			MOVE_SLUDGE_BOMB,
			MOVE_GIGA_DRAIN,
			MOVE_MIRROR_COAT
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_HP,
		.nature = NATURE_RASH,
	},
	{
		.species = SPECIES_LUDICOLO,
		.heldItem = BATTLE_TOWER_ITEM_LEFTOVERS,
		.teamFlags = 0xA2,
		.moves = {
			MOVE_RAIN_DANCE,
			MOVE_SURF,
			MOVE_TOXIC,
			MOVE_DOUBLE_TEAM
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_WOBBUFFET,
		.heldItem = BATTLE_TOWER_ITEM_LEFTOVERS,
		.teamFlags = 0x23,
		.moves = {
			MOVE_ENCORE,
			MOVE_COUNTER,
			MOVE_MIRROR_COAT,
			MOVE_DESTINY_BOND
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_HP,
		.nature = NATURE_SERIOUS,
	},
	{
		.species = SPECIES_RHYDON,
		.heldItem = BATTLE_TOWER_ITEM_QUICK_CLAW,
		.teamFlags = 0x21,
		.moves = {
			MOVE_EARTHQUAKE,
			MOVE_MEGAHORN,
			MOVE_HORN_DRILL,
			MOVE_ROCK_SLIDE
		},
		.evSpread = F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_GENTLE,
	},
	{
		.species = SPECIES_GLALIE,
		.heldItem = BATTLE_TOWER_ITEM_SALAC_BERRY,
		.teamFlags = 0x21,
		.moves = {
			MOVE_CRUNCH,
			MOVE_BLIZZARD,
			MOVE_HAIL,
			MOVE_EARTHQUAKE
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_HP,
		.nature = NATURE_SERIOUS,
	},
	{
		.species = SPECIES_SCEPTILE,
		.heldItem = BATTLE_TOWER_ITEM_SCOPE_LENS,
		.teamFlags = 0x13,
		.moves = {
			MOVE_LEAF_BLADE,
			MOVE_EARTHQUAKE,
			MOVE_DRAGON_CLAW,
			MOVE_CRUNCH
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_SPEED,
		.nature = NATURE_BRAVE,
	},
	{
		.species = SPECIES_BLAZIKEN,
		.heldItem = BATTLE_TOWER_ITEM_LIECHI_BERRY,
		.teamFlags = 0x17,
		.moves = {
			MOVE_BLAZE_KICK,
			MOVE_ROCK_TOMB,
			MOVE_ENDURE,
			MOVE_REVERSAL
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_HP,
		.nature = NATURE_RASH,
	},
	{
		.species = SPECIES_SWAMPERT,
		.heldItem = BATTLE_TOWER_ITEM_SHELL_BELL,
		.teamFlags = 0x17,
		.moves = {
			MOVE_SURF,
			MOVE_EARTHQUAKE,
			MOVE_MUD_SHOT,
			MOVE_BLIZZARD
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_ATTACK,
		.nature = NATURE_SERIOUS,
	},
	{
		.species = SPECIES_GARDEVOIR,
		.heldItem = BATTLE_TOWER_ITEM_SALAC_BERRY,
		.teamFlags = 0x19,
		.moves = {
			MOVE_PSYCHIC,
			MOVE_THUNDERBOLT,
			MOVE_DESTINY_BOND,
			MOVE_WILL_O_WISP
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED,
		.nature = NATURE_BRAVE,
	},
	{
		.species = SPECIES_BRELOOM,
		.heldItem = BATTLE_TOWER_ITEM_SALAC_BERRY,
		.teamFlags = 0xF6,
		.moves = {
			MOVE_SPORE,
			MOVE_FOCUS_PUNCH,
			MOVE_BRICK_BREAK,
			MOVE_SLUDGE_BOMB
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_ATTACK,
		.nature = NATURE_SASSY,
	},
	{
		.species = SPECIES_ALAKAZAM,
		.heldItem = BATTLE_TOWER_ITEM_GANLON_BERRY,
		.teamFlags = 0x1B,
		.moves = {
			MOVE_PSYCHIC,
			MOVE_THUNDER_PUNCH,
			MOVE_REFLECT,
			MOVE_RECOVER
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_HP,
		.nature = NATURE_HASTY,
	},
	{
		.species = SPECIES_SHIFTRY,
		.heldItem = BATTLE_TOWER_ITEM_CHESTO_BERRY,
		.teamFlags = 0x89,
		.moves = {
			MOVE_FAINT_ATTACK,
			MOVE_SHADOW_BALL,
			MOVE_DOUBLE_TEAM,
			MOVE_REST
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_ATTACK,
		.nature = NATURE_SERIOUS,
	},
	{
		.species = SPECIES_HARIYAMA,
		.heldItem = BATTLE_TOWER_ITEM_SCOPE_LENS,
		.teamFlags = 0x85,
		.moves = {
			MOVE_CROSS_CHOP,
			MOVE_EARTHQUAKE,
			MOVE_FACADE,
			MOVE_FAKE_OUT
		},
		.evSpread = F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_GENTLE,
	},
	{
		.species = SPECIES_CROBAT,
		.heldItem = BATTLE_TOWER_ITEM_BRIGHT_POWDER,
		.teamFlags = 0x49,
		.moves = {
			MOVE_ATTRACT,
			MOVE_CONFUSE_RAY,
			MOVE_BITE,
			MOVE_DOUBLE_TEAM
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_ATTACK,
		.nature = NATURE_SASSY,
	},
	{
		.species = SPECIES_MACHAMP,
		.heldItem = BATTLE_TOWER_ITEM_SCOPE_LENS,
		.teamFlags = 0x15,
		.moves = {
			MOVE_CROSS_CHOP,
			MOVE_FLAMETHROWER,
			MOVE_EARTHQUAKE,
			MOVE_ROCK_SLIDE
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_HP,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_MANECTRIC,
		.heldItem = BATTLE_TOWER_ITEM_PETAYA_BERRY,
		.teamFlags = 0x0B,
		.moves = {
			MOVE_THUNDERBOLT,
			MOVE_THUNDER_WAVE,
			MOVE_ROAR,
			MOVE_CRUNCH
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED,
		.nature = NATURE_BRAVE,
	},
	{
		.species = SPECIES_ELECTRODE,
		.heldItem = BATTLE_TOWER_ITEM_LUM_BERRY,
		.teamFlags = 0x27,
		.moves = {
			MOVE_THUNDERBOLT,
			MOVE_PROTECT,
			MOVE_MIRROR_COAT,
			MOVE_EXPLOSION
		},
		.evSpread = F_EV_SPREAD_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_BASHFUL,
	},
	{
		.species = SPECIES_MUK,
		.heldItem = BATTLE_TOWER_ITEM_QUICK_CLAW,
		.teamFlags = 0x05,
		.moves = {
			MOVE_SLUDGE_BOMB,
			MOVE_FLAMETHROWER,
			MOVE_THUNDERBOLT,
			MOVE_EXPLOSION
		},
		.evSpread = F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_GENTLE,
	},
	{
		.species = SPECIES_FLYGON,
		.heldItem = BATTLE_TOWER_ITEM_PETAYA_BERRY,
		.teamFlags = 0x4D,
		.moves = {
			MOVE_DRAGON_CLAW,
			MOVE_EARTHQUAKE,
			MOVE_FLAMETHROWER,
			MOVE_CRUNCH
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED,
		.nature = NATURE_SERIOUS,
	},
	{
		.species = SPECIES_STARMIE,
		.heldItem = BATTLE_TOWER_ITEM_APICOT_BERRY,
		.teamFlags = 0x1B,
		.moves = {
			MOVE_SURF,
			MOVE_THUNDERBOLT,
			MOVE_RECOVER,
			MOVE_CONFUSE_RAY
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED,
		.nature = NATURE_BRAVE,
	},
	{
		.species = SPECIES_DODRIO,
		.heldItem = BATTLE_TOWER_ITEM_LIECHI_BERRY,
		.teamFlags = 0x2B,
		.moves = {
			MOVE_DRILL_PECK,
			MOVE_TRI_ATTACK,
			MOVE_AGILITY,
			MOVE_FACADE
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_ATTACK,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_RAICHU,
		.heldItem = BATTLE_TOWER_ITEM_FOCUS_BAND,
		.teamFlags = 0x0A,
		.moves = {
			MOVE_THUNDERBOLT,
			MOVE_THUNDER_WAVE,
			MOVE_REVERSAL,
			MOVE_ATTRACT
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED,
		.nature = NATURE_SERIOUS,
	},
	{
		.species = SPECIES_GOLDUCK,
		.heldItem = BATTLE_TOWER_ITEM_LIECHI_BERRY,
		.teamFlags = 0x0A,
		.moves = {
			MOVE_SURF,
			MOVE_CROSS_CHOP,
			MOVE_ICE_BEAM,
			MOVE_HYPER_BEAM
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_ATTACK,
		.nature = NATURE_SERIOUS,
	},
	{
		.species = SPECIES_HERACROSS,
		.heldItem = BATTLE_TOWER_ITEM_LIECHI_BERRY,
		.teamFlags = 0x54,
		.moves = {
			MOVE_MEGAHORN,
			MOVE_ROCK_TOMB,
			MOVE_ENDURE,
			MOVE_REVERSAL
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_ATTACK,
		.nature = NATURE_SASSY,
	},
	{
		.species = SPECIES_WALREIN,
		.heldItem = BATTLE_TOWER_ITEM_CHESTO_BERRY,
		.teamFlags = 0x06,
		.moves = {
			MOVE_SURF,
			MOVE_ICE_BEAM,
			MOVE_EARTHQUAKE,
			MOVE_REST
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_NAIVE,
	},
	{
		.species = SPECIES_KINGDRA,
		.heldItem = BATTLE_TOWER_ITEM_CHESTO_BERRY,
		.teamFlags = 0x1D,
		.moves = {
			MOVE_SURF,
			MOVE_TOXIC,
			MOVE_PROTECT,
			MOVE_REST
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_ADAMANT,
	},
	{
		.species = SPECIES_SALAMENCE,
		.heldItem = BATTLE_TOWER_ITEM_LUM_BERRY,
		.teamFlags = 0x9C,
		.moves = {
			MOVE_DRAGON_CLAW,
			MOVE_EARTHQUAKE,
			MOVE_CRUNCH,
			MOVE_REST
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_ADAMANT,
	},
	{
		.species = SPECIES_METAGROSS,
		.heldItem = BATTLE_TOWER_ITEM_SHELL_BELL,
		.teamFlags = 0x15,
		.moves = {
			MOVE_METEOR_MASH,
			MOVE_PSYCHIC,
			MOVE_EARTHQUAKE,
			MOVE_LIGHT_SCREEN
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_REGIROCK,
		.heldItem = BATTLE_TOWER_ITEM_BRIGHT_POWDER,
		.teamFlags = 0xB5,
		.moves = {
			MOVE_EARTHQUAKE,
			MOVE_ANCIENT_POWER,
			MOVE_FOCUS_PUNCH,
			MOVE_EXPLOSION
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_ATTACK,
		.nature = NATURE_GENTLE,
	},
	{
		.species = SPECIES_REGICE,
		.heldItem = BATTLE_TOWER_ITEM_CHESTO_BERRY,
		.teamFlags = 0x96,
		.moves = {
			MOVE_ICE_BEAM,
			MOVE_THUNDERBOLT,
			MOVE_DOUBLE_TEAM,
			MOVE_REST
		},
		.evSpread = F_EV_SPREAD_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_HASTY,
	},
	{
		.species = SPECIES_REGISTEEL,
		.heldItem = BATTLE_TOWER_ITEM_QUICK_CLAW,
		.teamFlags = 0x94,
		.moves = {
			MOVE_METAL_CLAW,
			MOVE_EARTHQUAKE,
			MOVE_THUNDERBOLT,
			MOVE_EXPLOSION
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_ATTACK,
		.nature = NATURE_GENTLE,
	},
	{
		.species = SPECIES_LATIAS,
		.heldItem = BATTLE_TOWER_ITEM_LUM_BERRY,
		.teamFlags = 0x96,
		.moves = {
			MOVE_MIST_BALL,
			MOVE_THUNDERBOLT,
			MOVE_REST,
			MOVE_DRAGON_CLAW
		},
		.evSpread = F_EV_SPREAD_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_MILD,
	},
	{
		.species = SPECIES_LATIOS,
		.heldItem = BATTLE_TOWER_ITEM_APICOT_BERRY,
		.teamFlags = 0x95,
		.moves = {
			MOVE_LUSTER_PURGE,
			MOVE_REFLECT,
			MOVE_RECOVER,
			MOVE_DRAGON_CLAW
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED,
		.nature = NATURE_BRAVE,
	},
	{
		.species = SPECIES_MILOTIC,
		.heldItem = BATTLE_TOWER_ITEM_LEFTOVERS,
		.teamFlags = 0x96,
		.moves = {
			MOVE_SURF,
			MOVE_TOXIC,
			MOVE_RECOVER,
			MOVE_MIRROR_COAT
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_SPEED | F_EV_SPREAD_DEFENSE,
		.nature = NATURE_BRAVE,
	},
	{
		.species = SPECIES_SLAKING,
		.heldItem = BATTLE_TOWER_ITEM_CHOICE_BAND,
		.teamFlags = 0x05,
		.moves = {
			MOVE_HYPER_BEAM,
			MOVE_EARTHQUAKE,
			MOVE_NONE,
			MOVE_NONE
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_ATTACK,
		.nature = NATURE_SERIOUS,
	},
	{
		.species = SPECIES_SCEPTILE,
		.heldItem = BATTLE_TOWER_ITEM_LEFTOVERS,
		.teamFlags = 0x1F,
		.moves = {
			MOVE_GIGA_DRAIN,
			MOVE_DOUBLE_TEAM,
			MOVE_LEECH_SEED,
			MOVE_ATTRACT
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_QUIET,
	},
	{
		.species = SPECIES_BLAZIKEN,
		.heldItem = BATTLE_TOWER_ITEM_CHESTO_BERRY,
		.teamFlags = 0x17,
		.moves = {
			MOVE_BLAZE_KICK,
			MOVE_EARTHQUAKE,
			MOVE_ROCK_SLIDE,
			MOVE_REST
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED,
		.nature = NATURE_BRAVE,
	},
	{
		.species = SPECIES_SWAMPERT,
		.heldItem = BATTLE_TOWER_ITEM_SHELL_BELL,
		.teamFlags = 0x17,
		.moves = {
			MOVE_MUDDY_WATER,
			MOVE_MUD_SHOT,
			MOVE_MIRROR_COAT,
			MOVE_ICE_BEAM
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_GARDEVOIR,
		.heldItem = BATTLE_TOWER_ITEM_SALAC_BERRY,
		.teamFlags = 0x7B,
		.moves = {
			MOVE_PSYCHIC,
			MOVE_SHADOW_BALL,
			MOVE_DESTINY_BOND,
			MOVE_SNATCH
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED | F_EV_SPREAD_DEFENSE,
		.nature = NATURE_RELAXED,
	},
	{
		.species = SPECIES_BRELOOM,
		.heldItem = BATTLE_TOWER_ITEM_SALAC_BERRY,
		.teamFlags = 0x56,
		.moves = {
			MOVE_SPORE,
			MOVE_COUNTER,
			MOVE_IRON_TAIL,
			MOVE_GIGA_DRAIN
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_ATTACK,
		.nature = NATURE_SASSY,
	},
	{
		.species = SPECIES_ALAKAZAM,
		.heldItem = BATTLE_TOWER_ITEM_BRIGHT_POWDER,
		.teamFlags = 0x0A,
		.moves = {
			MOVE_PSYCHIC,
			MOVE_THUNDER_PUNCH,
			MOVE_FIRE_PUNCH,
			MOVE_RECOVER
		},
		.evSpread = F_EV_SPREAD_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_HASTY,
	},
	{
		.species = SPECIES_HARIYAMA,
		.heldItem = BATTLE_TOWER_ITEM_FOCUS_BAND,
		.teamFlags = 0x05,
		.moves = {
			MOVE_CROSS_CHOP,
			MOVE_ROCK_TOMB,
			MOVE_ENDURE,
			MOVE_REVERSAL
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_SASSY,
	},
	{
		.species = SPECIES_GYARADOS,
		.heldItem = BATTLE_TOWER_ITEM_SHELL_BELL,
		.teamFlags = 0x0C,
		.moves = {
			MOVE_HYPER_BEAM,
			MOVE_THUNDERBOLT,
			MOVE_EARTHQUAKE,
			MOVE_ICE_BEAM
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_ATTACK,
		.nature = NATURE_BOLD,
	},
	{
		.species = SPECIES_CROBAT,
		.heldItem = BATTLE_TOWER_ITEM_BRIGHT_POWDER,
		.teamFlags = 0x49,
		.moves = {
			MOVE_TOXIC,
			MOVE_CONFUSE_RAY,
			MOVE_ATTRACT,
			MOVE_PROTECT
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_SPEED,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_MACHAMP,
		.heldItem = BATTLE_TOWER_ITEM_SCOPE_LENS,
		.teamFlags = 0x15,
		.moves = {
			MOVE_CROSS_CHOP,
			MOVE_COUNTER,
			MOVE_EARTHQUAKE,
			MOVE_FACADE
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_HP,
		.nature = NATURE_SERIOUS,
	},
	{
		.species = SPECIES_MANECTRIC,
		.heldItem = BATTLE_TOWER_ITEM_CHESTO_BERRY,
		.teamFlags = 0x63,
		.moves = {
			MOVE_THUNDER,
			MOVE_THUNDER_WAVE,
			MOVE_REST,
			MOVE_CRUNCH
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_HP,
		.nature = NATURE_BRAVE,
	},
	{
		.species = SPECIES_ELECTRODE,
		.heldItem = BATTLE_TOWER_ITEM_SALAC_BERRY,
		.teamFlags = 0x07,
		.moves = {
			MOVE_THUNDERBOLT,
			MOVE_SCREECH,
			MOVE_MIRROR_COAT,
			MOVE_EXPLOSION
		},
		.evSpread = F_EV_SPREAD_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_MODEST,
	},
	{
		.species = SPECIES_MUK,
		.heldItem = BATTLE_TOWER_ITEM_LIECHI_BERRY,
		.teamFlags = 0x45,
		.moves = {
			MOVE_SLUDGE_BOMB,
			MOVE_GIGA_DRAIN,
			MOVE_ROCK_TOMB,
			MOVE_EXPLOSION
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_HP,
		.nature = NATURE_RASH,
	},
	{
		.species = SPECIES_FLYGON,
		.heldItem = BATTLE_TOWER_ITEM_LUM_BERRY,
		.teamFlags = 0x4D,
		.moves = {
			MOVE_DRAGON_CLAW,
			MOVE_EARTHQUAKE,
			MOVE_IRON_TAIL,
			MOVE_ROCK_TOMB
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_ATTACK,
		.nature = NATURE_IMPISH,
	},
	{
		.species = SPECIES_STARMIE,
		.heldItem = BATTLE_TOWER_ITEM_CHESTO_BERRY,
		.teamFlags = 0x1B,
		.moves = {
			MOVE_LIGHT_SCREEN,
			MOVE_THUNDERBOLT,
			MOVE_SURF,
			MOVE_REST
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED,
		.nature = NATURE_QUIET,
	},
	{
		.species = SPECIES_NINETALES,
		.heldItem = BATTLE_TOWER_ITEM_SITRUS_BERRY,
		.teamFlags = 0x0A,
		.moves = {
			MOVE_CONFUSE_RAY,
			MOVE_OVERHEAT,
			MOVE_FLAMETHROWER,
			MOVE_IRON_TAIL
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED,
		.nature = NATURE_QUIET,
	},
	{
		.species = SPECIES_GOLEM,
		.heldItem = BATTLE_TOWER_ITEM_SALAC_BERRY,
		.teamFlags = 0x25,
		.moves = {
			MOVE_EARTHQUAKE,
			MOVE_ROAR,
			MOVE_FIRE_BLAST,
			MOVE_EXPLOSION
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_SPEED,
		.nature = NATURE_SERIOUS,
	},
	{
		.species = SPECIES_GOLDUCK,
		.heldItem = BATTLE_TOWER_ITEM_PETAYA_BERRY,
		.teamFlags = 0x27,
		.moves = {
			MOVE_HYDRO_PUMP,
			MOVE_CROSS_CHOP,
			MOVE_BLIZZARD,
			MOVE_PSYCH_UP
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_ATTACK,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_HERACROSS,
		.heldItem = BATTLE_TOWER_ITEM_SALAC_BERRY,
		.teamFlags = 0x55,
		.moves = {
			MOVE_MEGAHORN,
			MOVE_EARTHQUAKE,
			MOVE_COUNTER,
			MOVE_REVERSAL
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_ATTACK,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_WALREIN,
		.heldItem = BATTLE_TOWER_ITEM_SALAC_BERRY,
		.teamFlags = 0x36,
		.moves = {
			MOVE_SURF,
			MOVE_BLIZZARD,
			MOVE_ROCK_SLIDE,
			MOVE_SHEER_COLD
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_HP,
		.nature = NATURE_SERIOUS,
	},
	{
		.species = SPECIES_KINGDRA,
		.heldItem = BATTLE_TOWER_ITEM_LEFTOVERS,
		.teamFlags = 0x5C,
		.moves = {
			MOVE_HYDRO_PUMP,
			MOVE_PROTECT,
			MOVE_DRAGON_BREATH,
			MOVE_DOUBLE_TEAM
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_ADAMANT,
	},
	{
		.species = SPECIES_SALAMENCE,
		.heldItem = BATTLE_TOWER_ITEM_KINGS_ROCK,
		.teamFlags = 0x9D,
		.moves = {
			MOVE_DRAGON_CLAW,
			MOVE_EARTHQUAKE,
			MOVE_FLAMETHROWER,
			MOVE_ROCK_TOMB
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED,
		.nature = NATURE_SERIOUS,
	},
	{
		.species = SPECIES_METAGROSS,
		.heldItem = BATTLE_TOWER_ITEM_QUICK_CLAW,
		.teamFlags = 0x15,
		.moves = {
			MOVE_METEOR_MASH,
			MOVE_PSYCHIC,
			MOVE_EARTHQUAKE,
			MOVE_HYPER_BEAM
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_ATTACK,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_REGIROCK,
		.heldItem = BATTLE_TOWER_ITEM_QUICK_CLAW,
		.teamFlags = 0x95,
		.moves = {
			MOVE_EARTHQUAKE,
			MOVE_ROCK_TOMB,
			MOVE_FACADE,
			MOVE_EXPLOSION
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_ATTACK,
		.nature = NATURE_GENTLE,
	},
	{
		.species = SPECIES_REGICE,
		.heldItem = BATTLE_TOWER_ITEM_SHELL_BELL,
		.teamFlags = 0x96,
		.moves = {
			MOVE_BLIZZARD,
			MOVE_THUNDERBOLT,
			MOVE_HAIL,
			MOVE_EXPLOSION
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_DEFENSE,
		.nature = NATURE_CAREFUL,
	},
	{
		.species = SPECIES_REGISTEEL,
		.heldItem = BATTLE_TOWER_ITEM_QUICK_CLAW,
		.teamFlags = 0x94,
		.moves = {
			MOVE_METAL_CLAW,
			MOVE_EARTHQUAKE,
			MOVE_ANCIENT_POWER,
			MOVE_EXPLOSION
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_ATTACK,
		.nature = NATURE_GENTLE,
	},
	{
		.species = SPECIES_LATIAS,
		.heldItem = BATTLE_TOWER_ITEM_APICOT_BERRY,
		.teamFlags = 0x96,
		.moves = {
			MOVE_MIST_BALL,
			MOVE_REFLECT,
			MOVE_RECOVER,
			MOVE_DRAGON_CLAW
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_HP,
		.nature = NATURE_BRAVE,
	},
	{
		.species = SPECIES_LATIOS,
		.heldItem = BATTLE_TOWER_ITEM_SHELL_BELL,
		.teamFlags = 0x95,
		.moves = {
			MOVE_LUSTER_PURGE,
			MOVE_ICE_BEAM,
			MOVE_RECOVER,
			MOVE_DRAGON_CLAW
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED,
		.nature = NATURE_QUIET,
	},
	{
		.species = SPECIES_MILOTIC,
		.heldItem = BATTLE_TOWER_ITEM_APICOT_BERRY,
		.teamFlags = 0xD6,
		.moves = {
			MOVE_SURF,
			MOVE_ICE_BEAM,
			MOVE_RECOVER,
			MOVE_DOUBLE_TEAM
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_ADAMANT,
	},
	{
		.species = SPECIES_KECLEON,
		.heldItem = BATTLE_TOWER_ITEM_CHOICE_BAND,
		.teamFlags = 0x69,
		.moves = {
			MOVE_TRICK,
			MOVE_REST,
			MOVE_IRON_TAIL,
			MOVE_DISABLE
		},
		.evSpread = F_EV_SPREAD_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_QUIRKY,
	},
	{
		.species = SPECIES_SCEPTILE,
		.heldItem = BATTLE_TOWER_ITEM_CHESTO_BERRY,
		.teamFlags = 0x5F,
		.moves = {
			MOVE_LEAF_BLADE,
			MOVE_EARTHQUAKE,
			MOVE_REST,
			MOVE_CRUNCH
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_SPEED | F_EV_SPREAD_DEFENSE,
		.nature = NATURE_BRAVE,
	},
	{
		.species = SPECIES_BLAZIKEN,
		.heldItem = BATTLE_TOWER_ITEM_LUM_BERRY,
		.teamFlags = 0x7F,
		.moves = {
			MOVE_FOCUS_PUNCH,
			MOVE_COUNTER,
			MOVE_SWAGGER,
			MOVE_ROCK_TOMB
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_HP,
		.nature = NATURE_SASSY,
	},
	{
		.species = SPECIES_SWAMPERT,
		.heldItem = BATTLE_TOWER_ITEM_LUM_BERRY,
		.teamFlags = 0x57,
		.moves = {
			MOVE_IRON_TAIL,
			MOVE_CURSE,
			MOVE_DOUBLE_TEAM,
			MOVE_REST
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_LAX,
	},
	{
		.species = SPECIES_GARDEVOIR,
		.heldItem = BATTLE_TOWER_ITEM_CHESTO_BERRY,
		.teamFlags = 0x3B,
		.moves = {
			MOVE_SHADOW_BALL,
			MOVE_PSYCHIC,
			MOVE_REST,
			MOVE_IMPRISON
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_HP,
		.nature = NATURE_BRAVE,
	},
	{
		.species = SPECIES_BRELOOM,
		.heldItem = BATTLE_TOWER_ITEM_SALAC_BERRY,
		.teamFlags = 0x56,
		.moves = {
			MOVE_SPORE,
			MOVE_FOCUS_PUNCH,
			MOVE_SLUDGE_BOMB,
			MOVE_IRON_TAIL
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_ATTACK,
		.nature = NATURE_SASSY,
	},
	{
		.species = SPECIES_ALAKAZAM,
		.heldItem = BATTLE_TOWER_ITEM_CHOICE_BAND,
		.teamFlags = 0x1A,
		.moves = {
			MOVE_PSYCHIC,
			MOVE_TRICK,
			MOVE_RECOVER,
			MOVE_SNATCH
		},
		.evSpread = F_EV_SPREAD_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_HASTY,
	},
	{
		.species = SPECIES_HARIYAMA,
		.heldItem = BATTLE_TOWER_ITEM_SALAC_BERRY,
		.teamFlags = 0x65,
		.moves = {
			MOVE_REVENGE,
			MOVE_COUNTER,
			MOVE_FOCUS_PUNCH,
			MOVE_REVERSAL
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_HP,
		.nature = NATURE_SASSY,
	},
	{
		.species = SPECIES_LUDICOLO,
		.heldItem = BATTLE_TOWER_ITEM_LEFTOVERS,
		.teamFlags = 0x54,
		.moves = {
			MOVE_RAIN_DANCE,
			MOVE_PROTECT,
			MOVE_TOXIC,
			MOVE_SURF
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_QUIET,
	},
	{
		.species = SPECIES_CROBAT,
		.heldItem = BATTLE_TOWER_ITEM_BRIGHT_POWDER,
		.teamFlags = 0x4B,
		.moves = {
			MOVE_SLUDGE_BOMB,
			MOVE_BITE,
			MOVE_AIR_CUTTER,
			MOVE_SHADOW_BALL
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED,
		.nature = NATURE_BRAVE,
	},
	{
		.species = SPECIES_MACHAMP,
		.heldItem = BATTLE_TOWER_ITEM_SCOPE_LENS,
		.teamFlags = 0x75,
		.moves = {
			MOVE_CROSS_CHOP,
			MOVE_ROCK_SLIDE,
			MOVE_DYNAMIC_PUNCH,
			MOVE_ROCK_TOMB
		},
		.evSpread = F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_MANECTRIC,
		.heldItem = BATTLE_TOWER_ITEM_PETAYA_BERRY,
		.teamFlags = 0x0A,
		.moves = {
			MOVE_THUNDERBOLT,
			MOVE_THUNDER_WAVE,
			MOVE_ATTRACT,
			MOVE_CRUNCH
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_QUIET,
	},
	{
		.species = SPECIES_ELECTRODE,
		.heldItem = BATTLE_TOWER_ITEM_LIECHI_BERRY,
		.teamFlags = 0x64,
		.moves = {
			MOVE_THUNDER,
			MOVE_DOUBLE_TEAM,
			MOVE_MIRROR_COAT,
			MOVE_EXPLOSION
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_HP,
		.nature = NATURE_BASHFUL,
	},
	{
		.species = SPECIES_MUK,
		.heldItem = BATTLE_TOWER_ITEM_SALAC_BERRY,
		.teamFlags = 0x49,
		.moves = {
			MOVE_SLUDGE_BOMB,
			MOVE_FLAMETHROWER,
			MOVE_THUNDERBOLT,
			MOVE_SHADOW_PUNCH
		},
		.evSpread = F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_GENTLE,
	},
	{
		.species = SPECIES_FLYGON,
		.heldItem = BATTLE_TOWER_ITEM_BRIGHT_POWDER,
		.teamFlags = 0xCD,
		.moves = {
			MOVE_PROTECT,
			MOVE_DIG,
			MOVE_TOXIC,
			MOVE_SANDSTORM
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_LAX,
	},
	{
		.species = SPECIES_STARMIE,
		.heldItem = BATTLE_TOWER_ITEM_KINGS_ROCK,
		.teamFlags = 0x5B,
		.moves = {
			MOVE_SURF,
			MOVE_THUNDERBOLT,
			MOVE_BLIZZARD,
			MOVE_PSYCHIC
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED,
		.nature = NATURE_BRAVE,
	},
	{
		.species = SPECIES_LUDICOLO,
		.heldItem = BATTLE_TOWER_ITEM_LEFTOVERS,
		.teamFlags = 0x1A,
		.moves = {
			MOVE_RAIN_DANCE,
			MOVE_LEECH_SEED,
			MOVE_DIVE,
			MOVE_PROTECT
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_SPEED,
		.nature = NATURE_BRAVE,
	},
	{
		.species = SPECIES_RAICHU,
		.heldItem = BATTLE_TOWER_ITEM_LIECHI_BERRY,
		.teamFlags = 0x4A,
		.moves = {
			MOVE_THUNDER,
			MOVE_REVERSAL,
			MOVE_FACADE,
			MOVE_IRON_TAIL
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_DEFENSE | F_EV_SPREAD_ATTACK,
		.nature = NATURE_TIMID,
	},
	{
		.species = SPECIES_GOLDUCK,
		.heldItem = BATTLE_TOWER_ITEM_SALAC_BERRY,
		.teamFlags = 0x0A,
		.moves = {
			MOVE_SURF,
			MOVE_PSYCHIC,
			MOVE_ICE_BEAM,
			MOVE_IRON_TAIL
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED,
		.nature = NATURE_DOCILE,
	},
	{
		.species = SPECIES_HERACROSS,
		.heldItem = BATTLE_TOWER_ITEM_LIECHI_BERRY,
		.teamFlags = 0x15,
		.moves = {
			MOVE_MEGAHORN,
			MOVE_EARTHQUAKE,
			MOVE_FACADE,
			MOVE_ROCK_TOMB
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_DEFENSE | F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_WALREIN,
		.heldItem = BATTLE_TOWER_ITEM_LEPPA_BERRY,
		.teamFlags = 0x26,
		.moves = {
			MOVE_SURF,
			MOVE_ICE_BEAM,
			MOVE_FISSURE,
			MOVE_SHEER_COLD
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_KINGDRA,
		.heldItem = BATTLE_TOWER_ITEM_SHELL_BELL,
		.teamFlags = 0x4D,
		.moves = {
			MOVE_HYDRO_PUMP,
			MOVE_BLIZZARD,
			MOVE_HYPER_BEAM,
			MOVE_DISABLE
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_QUIET,
	},
	{
		.species = SPECIES_SALAMENCE,
		.heldItem = BATTLE_TOWER_ITEM_PETAYA_BERRY,
		.teamFlags = 0x9C,
		.moves = {
			MOVE_DRAGON_CLAW,
			MOVE_EARTHQUAKE,
			MOVE_FIRE_BLAST,
			MOVE_HYDRO_PUMP
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED,
		.nature = NATURE_NAUGHTY,
	},
	{
		.species = SPECIES_METAGROSS,
		.heldItem = BATTLE_TOWER_ITEM_LIECHI_BERRY,
		.teamFlags = 0xB5,
		.moves = {
			MOVE_METEOR_MASH,
			MOVE_PSYCHIC,
			MOVE_PURSUIT,
			MOVE_ROCK_TOMB
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_SPEED,
		.nature = NATURE_BRAVE,
	},
	{
		.species = SPECIES_REGIROCK,
		.heldItem = BATTLE_TOWER_ITEM_APICOT_BERRY,
		.teamFlags = 0x95,
		.moves = {
			MOVE_EARTHQUAKE,
			MOVE_TOXIC,
			MOVE_SUPERPOWER,
			MOVE_REST
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_HP,
		.nature = NATURE_SERIOUS,
	},
	{
		.species = SPECIES_REGICE,
		.heldItem = BATTLE_TOWER_ITEM_LAX_INCENSE,
		.teamFlags = 0x96,
		.moves = {
			MOVE_ICE_BEAM,
			MOVE_THUNDERBOLT,
			MOVE_ANCIENT_POWER,
			MOVE_EXPLOSION
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_DEFENSE,
		.nature = NATURE_RASH,
	},
	{
		.species = SPECIES_REGISTEEL,
		.heldItem = BATTLE_TOWER_ITEM_LEFTOVERS,
		.teamFlags = 0xB4,
		.moves = {
			MOVE_CURSE,
			MOVE_AMNESIA,
			MOVE_RETURN,
			MOVE_REST
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_LAX,
	},
	{
		.species = SPECIES_LATIAS,
		.heldItem = BATTLE_TOWER_ITEM_SHELL_BELL,
		.teamFlags = 0x92,
		.moves = {
			MOVE_MIST_BALL,
			MOVE_THUNDERBOLT,
			MOVE_EARTHQUAKE,
			MOVE_ICE_BEAM
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED,
		.nature = NATURE_QUIET,
	},
	{
		.species = SPECIES_LATIOS,
		.heldItem = BATTLE_TOWER_ITEM_SHELL_BELL,
		.teamFlags = 0x91,
		.moves = {
			MOVE_LUSTER_PURGE,
			MOVE_THUNDERBOLT,
			MOVE_EARTHQUAKE,
			MOVE_SURF
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED,
		.nature = NATURE_QUIET,
	},
	{
		.species = SPECIES_MILOTIC,
		.heldItem = BATTLE_TOWER_ITEM_BRIGHT_POWDER,
		.teamFlags = 0xB2,
		.moves = {
			MOVE_SURF,
			MOVE_ICE_BEAM,
			MOVE_RECOVER,
			MOVE_ATTRACT
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED,
		.nature = NATURE_BRAVE,
	},
	{
		.species = SPECIES_SLAKING,
		.heldItem = BATTLE_TOWER_ITEM_SALAC_BERRY,
		.teamFlags = 0x65,
		.moves = {
			MOVE_YAWN,
			MOVE_SLASH,
			MOVE_COUNTER,
			MOVE_HYPER_BEAM
		},
		.evSpread = F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_DOCILE,
	},
	{
		.species = SPECIES_SCEPTILE,
		.heldItem = BATTLE_TOWER_ITEM_SHELL_BELL,
		.teamFlags = 0xDF,
		.moves = {
			MOVE_LEAF_BLADE,
			MOVE_DETECT,
			MOVE_DRAGON_CLAW,
			MOVE_CRUNCH
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_BLAZIKEN,
		.heldItem = BATTLE_TOWER_ITEM_SALAC_BERRY,
		.teamFlags = 0xD7,
		.moves = {
			MOVE_BLAZE_KICK,
			MOVE_SKY_UPPERCUT,
			MOVE_EARTHQUAKE,
			MOVE_ROCK_SLIDE
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_ATTACK,
		.nature = NATURE_DOCILE,
	},
	{
		.species = SPECIES_SWAMPERT,
		.heldItem = BATTLE_TOWER_ITEM_PETAYA_BERRY,
		.teamFlags = 0x5F,
		.moves = {
			MOVE_SURF,
			MOVE_EARTHQUAKE,
			MOVE_ICE_BEAM,
			MOVE_ROCK_TOMB
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED | F_EV_SPREAD_HP,
		.nature = NATURE_SASSY,
	},
	{
		.species = SPECIES_SHEDINJA,
		.heldItem = BATTLE_TOWER_ITEM_BRIGHT_POWDER,
		.teamFlags = 0xDB,
		.moves = {
			MOVE_CONFUSE_RAY,
			MOVE_SHADOW_BALL,
			MOVE_TOXIC,
			MOVE_HYPER_BEAM
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_ATTACK,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_METAGROSS,
		.heldItem = BATTLE_TOWER_ITEM_QUICK_CLAW,
		.teamFlags = 0x94,
		.moves = {
			MOVE_METEOR_MASH,
			MOVE_PSYCHIC,
			MOVE_SHADOW_BALL,
			MOVE_EARTHQUAKE
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_ATTACK,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_GRUMPIG,
		.heldItem = BATTLE_TOWER_ITEM_MACHO_BRACE,
		.teamFlags = 0x4B,
		.moves = {
			MOVE_PSYCHIC,
			MOVE_CONFUSE_RAY,
			MOVE_TRICK,
			MOVE_REFLECT
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_QUIET,
	},
	{
		.species = SPECIES_LATIAS,
		.heldItem = BATTLE_TOWER_ITEM_LUM_BERRY,
		.teamFlags = 0x92,
		.moves = {
			MOVE_MIST_BALL,
			MOVE_RECOVER,
			MOVE_ATTRACT,
			MOVE_DRAGON_CLAW
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_ADAMANT,
	},
	{
		.species = SPECIES_LATIOS,
		.heldItem = BATTLE_TOWER_ITEM_KINGS_ROCK,
		.teamFlags = 0x91,
		.moves = {
			MOVE_LUSTER_PURGE,
			MOVE_THUNDERBOLT,
			MOVE_ICE_BEAM,
			MOVE_DRAGON_CLAW
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_STARMIE,
		.heldItem = BATTLE_TOWER_ITEM_LUM_BERRY,
		.teamFlags = 0x1A,
		.moves = {
			MOVE_SURF,
			MOVE_THUNDERBOLT,
			MOVE_PSYCHIC,
			MOVE_ICE_BEAM
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED,
		.nature = NATURE_QUIET,
	},
	{
		.species = SPECIES_MACHAMP,
		.heldItem = BATTLE_TOWER_ITEM_SCOPE_LENS,
		.teamFlags = 0x14,
		.moves = {
			MOVE_CROSS_CHOP,
			MOVE_COUNTER,
			MOVE_ROCK_TOMB,
			MOVE_FLAMETHROWER
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_HARDY,
	},
};
// ===== END src/data/battle_tower/level_50_mons.h =====
// ===== BEGIN src/data/battle_tower/level_100_mons.h =====
const struct BattleTowerPokemonTemplate gBattleTowerLevel100Mons[] =
{
	{
		.species = SPECIES_LINOONE,
		.heldItem = BATTLE_TOWER_ITEM_RAWST_BERRY,
		.teamFlags = 0x42,
		.moves = {
			MOVE_SLASH,
			MOVE_GROWL,
			MOVE_TAIL_WHIP,
			MOVE_SAND_ATTACK
		},
		.evSpread = F_EV_SPREAD_SPEED,
		.nature = NATURE_SERIOUS,
	},
	{
		.species = SPECIES_MIGHTYENA,
		.heldItem = BATTLE_TOWER_ITEM_SITRUS_BERRY,
		.teamFlags = 0x41,
		.moves = {
			MOVE_BITE,
			MOVE_HOWL,
			MOVE_ODOR_SLEUTH,
			MOVE_SCARY_FACE
		},
		.evSpread = F_EV_SPREAD_ATTACK,
		.nature = NATURE_NAIVE,
	},
	{
		.species = SPECIES_BEAUTIFLY,
		.heldItem = BATTLE_TOWER_ITEM_PERSIM_BERRY,
		.teamFlags = 0x41,
		.moves = {
			MOVE_GIGA_DRAIN,
			MOVE_GUST,
			MOVE_STUN_SPORE,
			MOVE_PROTECT
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_ATTACK,
		.nature = NATURE_CAREFUL,
	},
	{
		.species = SPECIES_DUSTOX,
		.heldItem = BATTLE_TOWER_ITEM_PECHA_BERRY,
		.teamFlags = 0x41,
		.moves = {
			MOVE_PSYBEAM,
			MOVE_GUST,
			MOVE_DOUBLE_TEAM,
			MOVE_SILVER_WIND
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_DEFENSE,
		.nature = NATURE_RELAXED,
	},
	{
		.species = SPECIES_LOMBRE,
		.heldItem = BATTLE_TOWER_ITEM_CHESTO_BERRY,
		.teamFlags = 0x03,
		.moves = {
			MOVE_ASTONISH,
			MOVE_GROWL,
			MOVE_MEGA_DRAIN,
			MOVE_SURF
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_LONELY,
	},
	{
		.species = SPECIES_NUZLEAF,
		.heldItem = BATTLE_TOWER_ITEM_WHITE_HERB,
		.teamFlags = 0x01,
		.moves = {
			MOVE_BULLET_SEED,
			MOVE_RAZOR_WIND,
			MOVE_FAINT_ATTACK,
			MOVE_GROWTH
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_ATTACK,
		.nature = NATURE_DOCILE,
	},
	{
		.species = SPECIES_SWELLOW,
		.heldItem = BATTLE_TOWER_ITEM_SHARP_BEAK,
		.teamFlags = 0x42,
		.moves = {
			MOVE_AERIAL_ACE,
			MOVE_GROWL,
			MOVE_ENDEAVOR,
			MOVE_FOCUS_ENERGY
		},
		.evSpread = F_EV_SPREAD_ATTACK,
		.nature = NATURE_GENTLE,
	},
	{
		.species = SPECIES_PELIPPER,
		.heldItem = BATTLE_TOWER_ITEM_MYSTIC_WATER,
		.teamFlags = 0x02,
		.moves = {
			MOVE_SURF,
			MOVE_WATER_SPORT,
			MOVE_PROTECT,
			MOVE_SUPERSONIC
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK,
		.nature = NATURE_MILD,
	},
	{
		.species = SPECIES_BRELOOM,
		.heldItem = BATTLE_TOWER_ITEM_KINGS_ROCK,
		.teamFlags = 0x42,
		.moves = {
			MOVE_MACH_PUNCH,
			MOVE_MEGA_DRAIN,
			MOVE_HEADBUTT,
			MOVE_STUN_SPORE
		},
		.evSpread = F_EV_SPREAD_ATTACK,
		.nature = NATURE_GENTLE,
	},
	{
		.species = SPECIES_NINJASK,
		.heldItem = BATTLE_TOWER_ITEM_RAWST_BERRY,
		.teamFlags = 0x41,
		.moves = {
			MOVE_SCRATCH,
			MOVE_SCREECH,
			MOVE_LEECH_LIFE,
			MOVE_FLASH
		},
		.evSpread = F_EV_SPREAD_DEFENSE | F_EV_SPREAD_ATTACK,
		.nature = NATURE_SERIOUS,
	},
	{
		.species = SPECIES_CROBAT,
		.heldItem = BATTLE_TOWER_ITEM_SITRUS_BERRY,
		.teamFlags = 0x01,
		.moves = {
			MOVE_BITE,
			MOVE_FLY,
			MOVE_SUPERSONIC,
			MOVE_HAZE
		},
		.evSpread = F_EV_SPREAD_DEFENSE | F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_IMPISH,
	},
	{
		.species = SPECIES_MAWILE,
		.heldItem = BATTLE_TOWER_ITEM_METAL_COAT,
		.teamFlags = 0x03,
		.moves = {
			MOVE_VICE_GRIP,
			MOVE_SWEET_SCENT,
			MOVE_ASTONISH,
			MOVE_STRENGTH
		},
		.evSpread = F_EV_SPREAD_ATTACK,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_NOSEPASS,
		.heldItem = BATTLE_TOWER_ITEM_SITRUS_BERRY,
		.teamFlags = 0x01,
		.moves = {
			MOVE_ROCK_THROW,
			MOVE_SANDSTORM,
			MOVE_HARDEN,
			MOVE_PROTECT
		},
		.evSpread = F_EV_SPREAD_ATTACK,
		.nature = NATURE_IMPISH,
	},
	{
		.species = SPECIES_DELCATTY,
		.heldItem = BATTLE_TOWER_ITEM_SITRUS_BERRY,
		.teamFlags = 0x42,
		.moves = {
			MOVE_DOUBLE_SLAP,
			MOVE_TAIL_WHIP,
			MOVE_ATTRACT,
			MOVE_CHARM
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_DEFENSE,
		.nature = NATURE_BOLD,
	},
	{
		.species = SPECIES_CAMERUPT,
		.heldItem = BATTLE_TOWER_ITEM_CHARCOAL,
		.teamFlags = 0x01,
		.moves = {
			MOVE_EMBER,
			MOVE_TAKE_DOWN,
			MOVE_GROWL,
			MOVE_SANDSTORM
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE,
		.nature = NATURE_RASH,
	},
	{
		.species = SPECIES_MUK,
		.heldItem = BATTLE_TOWER_ITEM_ORAN_BERRY,
		.teamFlags = 0x01,
		.moves = {
			MOVE_POISON_GAS,
			MOVE_MINIMIZE,
			MOVE_SLUDGE,
			MOVE_SCREECH
		},
		.evSpread = F_EV_SPREAD_HP,
		.nature = NATURE_CALM,
	},
	{
		.species = SPECIES_SANDSLASH,
		.heldItem = BATTLE_TOWER_ITEM_SOFT_SAND,
		.teamFlags = 0x03,
		.moves = {
			MOVE_SLASH,
			MOVE_SAND_ATTACK,
			MOVE_DEFENSE_CURL,
			MOVE_SWIFT
		},
		.evSpread = F_EV_SPREAD_DEFENSE | F_EV_SPREAD_ATTACK,
		.nature = NATURE_DOCILE,
	},
	{
		.species = SPECIES_SPINDA,
		.heldItem = BATTLE_TOWER_ITEM_SILK_SCARF,
		.teamFlags = 0x42,
		.moves = {
			MOVE_UPROAR,
			MOVE_WATER_PULSE,
			MOVE_THRASH,
			MOVE_SAFEGUARD
		},
		.evSpread = F_EV_SPREAD_SPEED,
		.nature = NATURE_TIMID,
	},
	{
		.species = SPECIES_WHISCASH,
		.heldItem = BATTLE_TOWER_ITEM_CHESTO_BERRY,
		.teamFlags = 0x01,
		.moves = {
			MOVE_TICKLE,
			MOVE_MUD_SPORT,
			MOVE_WATER_GUN,
			MOVE_WATER_SPORT
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_DEFENSE,
		.nature = NATURE_HASTY,
	},
	{
		.species = SPECIES_CACTURNE,
		.heldItem = BATTLE_TOWER_ITEM_POISON_BARB,
		.teamFlags = 0x01,
		.moves = {
			MOVE_POISON_STING,
			MOVE_PIN_MISSILE,
			MOVE_ABSORB,
			MOVE_COTTON_SPORE
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_ATTACK,
		.nature = NATURE_NAIVE,
	},
	{
		.species = SPECIES_JIGGLYPUFF,
		.heldItem = BATTLE_TOWER_ITEM_BRIGHT_POWDER,
		.teamFlags = 0x42,
		.moves = {
			MOVE_SING,
			MOVE_ROLLOUT,
			MOVE_POUND,
			MOVE_LIGHT_SCREEN
		},
		.evSpread = F_EV_SPREAD_HP,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_MARILL,
		.heldItem = BATTLE_TOWER_ITEM_MYSTIC_WATER,
		.teamFlags = 0x42,
		.moves = {
			MOVE_BUBBLE_BEAM,
			MOVE_DEFENSE_CURL,
			MOVE_RAIN_DANCE,
			MOVE_IRON_TAIL
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE,
		.nature = NATURE_QUIET,
	},
	{
		.species = SPECIES_MAGNETON,
		.heldItem = BATTLE_TOWER_ITEM_RAWST_BERRY,
		.teamFlags = 0x01,
		.moves = {
			MOVE_THUNDER_SHOCK,
			MOVE_SUPERSONIC,
			MOVE_FLASH,
			MOVE_SCREECH
		},
		.evSpread = F_EV_SPREAD_SPEED,
		.nature = NATURE_CAREFUL,
	},
	{
		.species = SPECIES_CARVANHA,
		.heldItem = BATTLE_TOWER_ITEM_KINGS_ROCK,
		.teamFlags = 0x01,
		.moves = {
			MOVE_BITE,
			MOVE_RAGE,
			MOVE_SCARY_FACE,
			MOVE_LEER
		},
		.evSpread = F_EV_SPREAD_ATTACK,
		.nature = NATURE_QUIRKY,
	},
	{
		.species = SPECIES_KECLEON,
		.heldItem = BATTLE_TOWER_ITEM_PERSIM_BERRY,
		.teamFlags = 0x03,
		.moves = {
			MOVE_THIEF,
			MOVE_LICK,
			MOVE_BIND,
			MOVE_FURY_SWIPES
		},
		.evSpread = F_EV_SPREAD_DEFENSE,
		.nature = NATURE_JOLLY,
	},
	{
		.species = SPECIES_NINETALES,
		.heldItem = BATTLE_TOWER_ITEM_CHARCOAL,
		.teamFlags = 0x02,
		.moves = {
			MOVE_EMBER,
			MOVE_CONFUSE_RAY,
			MOVE_FIRE_SPIN,
			MOVE_SAFEGUARD
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK,
		.nature = NATURE_LONELY,
	},
	{
		.species = SPECIES_RAICHU,
		.heldItem = BATTLE_TOWER_ITEM_PERSIM_BERRY,
		.teamFlags = 0x42,
		.moves = {
			MOVE_SHOCK_WAVE,
			MOVE_GROWL,
			MOVE_DOUBLE_TEAM,
			MOVE_LIGHT_SCREEN
		},
		.evSpread = F_EV_SPREAD_DEFENSE,
		.nature = NATURE_NAIVE,
	},
	{
		.species = SPECIES_SEALEO,
		.heldItem = BATTLE_TOWER_ITEM_NEVER_MELT_ICE,
		.teamFlags = 0x01,
		.moves = {
			MOVE_ICE_BALL,
			MOVE_WATER_GUN,
			MOVE_ENCORE,
			MOVE_HAIL
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_ATTACK,
		.nature = NATURE_LAX,
	},
	{
		.species = SPECIES_GRAVELER,
		.heldItem = BATTLE_TOWER_ITEM_HARD_STONE,
		.teamFlags = 0x01,
		.moves = {
			MOVE_ROCK_THROW,
			MOVE_MUD_SPORT,
			MOVE_SANDSTORM,
			MOVE_ROCK_TOMB
		},
		.evSpread = F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_GENTLE,
	},
	{
		.species = SPECIES_SHUPPET,
		.heldItem = BATTLE_TOWER_ITEM_SPELL_TAG,
		.teamFlags = 0x03,
		.moves = {
			MOVE_NIGHT_SHADE,
			MOVE_WILL_O_WISP,
			MOVE_SCREECH,
			MOVE_KNOCK_OFF
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK,
		.nature = NATURE_QUIET,
	},
	{
		.species = SPECIES_LUVDISC,
		.heldItem = BATTLE_TOWER_ITEM_SITRUS_BERRY,
		.teamFlags = 0x0A,
		.moves = {
			MOVE_ATTRACT,
			MOVE_FLAIL,
			MOVE_SWEET_KISS,
			MOVE_WATER_PULSE
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK,
		.nature = NATURE_ADAMANT,
	},
	{
		.species = SPECIES_LANTURN,
		.heldItem = BATTLE_TOWER_ITEM_CHERI_BERRY,
		.teamFlags = 0x0A,
		.moves = {
			MOVE_THUNDER_WAVE,
			MOVE_SUPERSONIC,
			MOVE_WATER_GUN,
			MOVE_SPARK
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_BOLD,
	},
	{
		.species = SPECIES_CORSOLA,
		.heldItem = BATTLE_TOWER_ITEM_SITRUS_BERRY,
		.teamFlags = 0x0A,
		.moves = {
			MOVE_MIRROR_COAT,
			MOVE_BUBBLE,
			MOVE_HARDEN,
			MOVE_LIGHT_SCREEN
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_DEFENSE,
		.nature = NATURE_TIMID,
	},
	{
		.species = SPECIES_WAILMER,
		.heldItem = BATTLE_TOWER_ITEM_SITRUS_BERRY,
		.teamFlags = 0x05,
		.moves = {
			MOVE_SURF,
			MOVE_ROAR,
			MOVE_GROWL,
			MOVE_MIST
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED | F_EV_SPREAD_ATTACK,
		.nature = NATURE_SASSY,
	},
	{
		.species = SPECIES_RHYDON,
		.heldItem = BATTLE_TOWER_ITEM_FOCUS_BAND,
		.teamFlags = 0x05,
		.moves = {
			MOVE_TAKE_DOWN,
			MOVE_SCARY_FACE,
			MOVE_TAIL_WHIP,
			MOVE_ROAR
		},
		.evSpread = F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_DODRIO,
		.heldItem = BATTLE_TOWER_ITEM_SHARP_BEAK,
		.teamFlags = 0x05,
		.moves = {
			MOVE_FURY_ATTACK,
			MOVE_PURSUIT,
			MOVE_AERIAL_ACE,
			MOVE_AGILITY
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_ATTACK,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_GOLDUCK,
		.heldItem = BATTLE_TOWER_ITEM_QUICK_CLAW,
		.teamFlags = 0x05,
		.moves = {
			MOVE_FURY_SWIPES,
			MOVE_TAIL_WHIP,
			MOVE_DISABLE,
			MOVE_PSYCH_UP
		},
		.evSpread = F_EV_SPREAD_ATTACK,
		.nature = NATURE_RELAXED,
	},
	{
		.species = SPECIES_BELLOSSOM,
		.heldItem = BATTLE_TOWER_ITEM_MIRACLE_SEED,
		.teamFlags = 0x0A,
		.moves = {
			MOVE_GIGA_DRAIN,
			MOVE_POISON_POWDER,
			MOVE_STUN_SPORE,
			MOVE_ACID
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK,
		.nature = NATURE_BOLD,
	},
	{
		.species = SPECIES_TROPIUS,
		.heldItem = BATTLE_TOWER_ITEM_KINGS_ROCK,
		.teamFlags = 0x05,
		.moves = {
			MOVE_STOMP,
			MOVE_RAZOR_LEAF,
			MOVE_GUST,
			MOVE_SYNTHESIS
		},
		.evSpread = F_EV_SPREAD_ATTACK,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_SABLEYE,
		.heldItem = BATTLE_TOWER_ITEM_SPELL_TAG,
		.teamFlags = 0x0A,
		.moves = {
			MOVE_NIGHT_SHADE,
			MOVE_FAKE_OUT,
			MOVE_PSYCH_UP,
			MOVE_DETECT
		},
		.evSpread = F_EV_SPREAD_SPEED,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_ELECTRODE,
		.heldItem = BATTLE_TOWER_ITEM_FOCUS_BAND,
		.teamFlags = 0x03,
		.moves = {
			MOVE_SONIC_BOOM,
			MOVE_SCREECH,
			MOVE_SPARK,
			MOVE_SELF_DESTRUCT
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_DEFENSE,
		.nature = NATURE_QUIRKY,
	},
	{
		.species = SPECIES_TENTACRUEL,
		.heldItem = BATTLE_TOWER_ITEM_POISON_BARB,
		.teamFlags = 0x01,
		.moves = {
			MOVE_ACID,
			MOVE_WATER_PULSE,
			MOVE_BARRIER,
			MOVE_WRAP
		},
		.evSpread = F_EV_SPREAD_SPEED,
		.nature = NATURE_HASTY,
	},
	{
		.species = SPECIES_CLAYDOL,
		.heldItem = BATTLE_TOWER_ITEM_SOFT_SAND,
		.teamFlags = 0x05,
		.moves = {
			MOVE_ANCIENT_POWER,
			MOVE_MUD_SLAP,
			MOVE_RAPID_SPIN,
			MOVE_CONFUSION
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_DEFENSE,
		.nature = NATURE_QUIET,
	},
	{
		.species = SPECIES_GRUMPIG,
		.heldItem = BATTLE_TOWER_ITEM_SITRUS_BERRY,
		.teamFlags = 0x0A,
		.moves = {
			MOVE_PSYBEAM,
			MOVE_PSYCH_UP,
			MOVE_BOUNCE,
			MOVE_MAGIC_COAT
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_DEFENSE,
		.nature = NATURE_NAUGHTY,
	},
	{
		.species = SPECIES_CRAWDAUNT,
		.heldItem = BATTLE_TOWER_ITEM_MENTAL_HERB,
		.teamFlags = 0x05,
		.moves = {
			MOVE_CRABHAMMER,
			MOVE_BUBBLE_BEAM,
			MOVE_BRICK_BREAK,
			MOVE_PROTECT
		},
		.evSpread = F_EV_SPREAD_ATTACK,
		.nature = NATURE_CALM,
	},
	{
		.species = SPECIES_SEVIPER,
		.heldItem = BATTLE_TOWER_ITEM_POISON_BARB,
		.teamFlags = 0x01,
		.moves = {
			MOVE_POISON_TAIL,
			MOVE_GLARE,
			MOVE_WRAP,
			MOVE_THIEF
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_DEFENSE,
		.nature = NATURE_CAREFUL,
	},
	{
		.species = SPECIES_ZANGOOSE,
		.heldItem = BATTLE_TOWER_ITEM_SITRUS_BERRY,
		.teamFlags = 0x05,
		.moves = {
			MOVE_FURY_CUTTER,
			MOVE_LEER,
			MOVE_QUICK_ATTACK,
			MOVE_DETECT
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_ATTACK,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_ALTARIA,
		.heldItem = BATTLE_TOWER_ITEM_DRAGON_FANG,
		.teamFlags = 0x03,
		.moves = {
			MOVE_DRAGON_BREATH,
			MOVE_SING,
			MOVE_SAFEGUARD,
			MOVE_TAKE_DOWN
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_ATTACK,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_ROSELIA,
		.heldItem = BATTLE_TOWER_ITEM_CHESTO_BERRY,
		.teamFlags = 0x0A,
		.moves = {
			MOVE_LEECH_SEED,
			MOVE_MEGA_DRAIN,
			MOVE_GROWTH,
			MOVE_STUN_SPORE
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_SP_ATTACK,
		.nature = NATURE_NAUGHTY,
	},
	{
		.species = SPECIES_VOLBEAT,
		.heldItem = BATTLE_TOWER_ITEM_BRIGHT_POWDER,
		.teamFlags = 0x09,
		.moves = {
			MOVE_SIGNAL_BEAM,
			MOVE_CONFUSE_RAY,
			MOVE_DOUBLE_TEAM,
			MOVE_LIGHT_SCREEN
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_DEFENSE,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_ILLUMISE,
		.heldItem = BATTLE_TOWER_ITEM_SITRUS_BERRY,
		.teamFlags = 0x09,
		.moves = {
			MOVE_CHARM,
			MOVE_ENCORE,
			MOVE_SOLAR_BEAM,
			MOVE_ATTRACT
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED,
		.nature = NATURE_QUIET,
	},
	{
		.species = SPECIES_MANECTRIC,
		.heldItem = BATTLE_TOWER_ITEM_MAGNET,
		.teamFlags = 0x03,
		.moves = {
			MOVE_BITE,
			MOVE_HOWL,
			MOVE_THUNDER_WAVE,
			MOVE_SPARK
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED,
		.nature = NATURE_SERIOUS,
	},
	{
		.species = SPECIES_MAWILE,
		.heldItem = BATTLE_TOWER_ITEM_SITRUS_BERRY,
		.teamFlags = 0x0A,
		.moves = {
			MOVE_CRUNCH,
			MOVE_IRON_DEFENSE,
			MOVE_TORMENT,
			MOVE_SANDSTORM
		},
		.evSpread = F_EV_SPREAD_DEFENSE | F_EV_SPREAD_ATTACK,
		.nature = NATURE_RASH,
	},
	{
		.species = SPECIES_HARIYAMA,
		.heldItem = BATTLE_TOWER_ITEM_KINGS_ROCK,
		.teamFlags = 0x05,
		.moves = {
			MOVE_ARM_THRUST,
			MOVE_FAKE_OUT,
			MOVE_WHIRLWIND,
			MOVE_REVERSAL
		},
		.evSpread = F_EV_SPREAD_ATTACK,
		.nature = NATURE_GENTLE,
	},
	{
		.species = SPECIES_SKARMORY,
		.heldItem = BATTLE_TOWER_ITEM_METAL_COAT,
		.teamFlags = 0x01,
		.moves = {
			MOVE_STEEL_WING,
			MOVE_AGILITY,
			MOVE_TAUNT,
			MOVE_FLY
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED,
		.nature = NATURE_NAIVE,
	},
	{
		.species = SPECIES_TORKOAL,
		.heldItem = BATTLE_TOWER_ITEM_PECHA_BERRY,
		.teamFlags = 0x03,
		.moves = {
			MOVE_FIRE_SPIN,
			MOVE_SMOKESCREEN,
			MOVE_BODY_SLAM,
			MOVE_AMNESIA
		},
		.evSpread = F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_MILD,
	},
	{
		.species = SPECIES_GYARADOS,
		.heldItem = BATTLE_TOWER_ITEM_PERSIM_BERRY,
		.teamFlags = 0x05,
		.moves = {
			MOVE_THRASH,
			MOVE_DRAGON_RAGE,
			MOVE_TWISTER,
			MOVE_HYDRO_PUMP
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_QUIRKY,
	},
	{
		.species = SPECIES_MIGHTYENA,
		.heldItem = BATTLE_TOWER_ITEM_SITRUS_BERRY,
		.teamFlags = 0x05,
		.moves = {
			MOVE_CRUNCH,
			MOVE_HOWL,
			MOVE_IRON_TAIL,
			MOVE_TORMENT
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK,
		.nature = NATURE_QUIRKY,
	},
	{
		.species = SPECIES_LINOONE,
		.heldItem = BATTLE_TOWER_ITEM_CHERI_BERRY,
		.teamFlags = 0x06,
		.moves = {
			MOVE_SLASH,
			MOVE_ATTRACT,
			MOVE_SHOCK_WAVE,
			MOVE_TOXIC
		},
		.evSpread = F_EV_SPREAD_ATTACK,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_MASQUERAIN,
		.heldItem = BATTLE_TOWER_ITEM_SITRUS_BERRY,
		.teamFlags = 0x0A,
		.moves = {
			MOVE_TOXIC,
			MOVE_STUN_SPORE,
			MOVE_SUNNY_DAY,
			MOVE_SOLAR_BEAM
		},
		.evSpread = F_EV_SPREAD_DEFENSE | F_EV_SPREAD_ATTACK,
		.nature = NATURE_LAX,
	},
	{
		.species = SPECIES_SCEPTILE,
		.heldItem = BATTLE_TOWER_ITEM_LUM_BERRY,
		.teamFlags = 0x06,
		.moves = {
			MOVE_BULLET_SEED,
			MOVE_SLAM,
			MOVE_SCREECH,
			MOVE_DETECT
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED,
		.nature = NATURE_RELAXED,
	},
	{
		.species = SPECIES_BLAZIKEN,
		.heldItem = BATTLE_TOWER_ITEM_KINGS_ROCK,
		.teamFlags = 0x06,
		.moves = {
			MOVE_DOUBLE_KICK,
			MOVE_FLAMETHROWER,
			MOVE_DOUBLE_TEAM,
			MOVE_ROAR
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_ATTACK,
		.nature = NATURE_GENTLE,
	},
	{
		.species = SPECIES_SWAMPERT,
		.heldItem = BATTLE_TOWER_ITEM_SITRUS_BERRY,
		.teamFlags = 0x49,
		.moves = {
			MOVE_SURF,
			MOVE_MUD_SHOT,
			MOVE_MUD_SPORT,
			MOVE_RAIN_DANCE
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_SP_ATTACK,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_SALAMENCE,
		.heldItem = BATTLE_TOWER_ITEM_DRAGON_FANG,
		.teamFlags = 0x49,
		.moves = {
			MOVE_DRAGON_BREATH,
			MOVE_FLY,
			MOVE_TOXIC,
			MOVE_FACADE
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_CALM,
	},
	{
		.species = SPECIES_KINGDRA,
		.heldItem = BATTLE_TOWER_ITEM_PERSIM_BERRY,
		.teamFlags = 0x49,
		.moves = {
			MOVE_SURF,
			MOVE_ICE_BEAM,
			MOVE_SMOKESCREEN,
			MOVE_RAIN_DANCE
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED,
		.nature = NATURE_SERIOUS,
	},
	{
		.species = SPECIES_CORSOLA,
		.heldItem = BATTLE_TOWER_ITEM_PERSIM_BERRY,
		.teamFlags = 0x03,
		.moves = {
			MOVE_ANCIENT_POWER,
			MOVE_MIRROR_COAT,
			MOVE_SAFEGUARD,
			MOVE_REFLECT
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_DEFENSE,
		.nature = NATURE_BOLD,
	},
	{
		.species = SPECIES_RHYDON,
		.heldItem = BATTLE_TOWER_ITEM_FOCUS_BAND,
		.teamFlags = 0x41,
		.moves = {
			MOVE_EARTHQUAKE,
			MOVE_IRON_TAIL,
			MOVE_ROAR,
			MOVE_THUNDERBOLT
		},
		.evSpread = F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_HASTY,
	},
	{
		.species = SPECIES_HERACROSS,
		.heldItem = BATTLE_TOWER_ITEM_KINGS_ROCK,
		.teamFlags = 0x06,
		.moves = {
			MOVE_MEGAHORN,
			MOVE_COUNTER,
			MOVE_PROTECT,
			MOVE_LEER
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_ATTACK,
		.nature = NATURE_GENTLE,
	},
	{
		.species = SPECIES_GIRAFARIG,
		.heldItem = BATTLE_TOWER_ITEM_LUM_BERRY,
		.teamFlags = 0x09,
		.moves = {
			MOVE_PSYCHIC,
			MOVE_CRUNCH,
			MOVE_BATON_PASS,
			MOVE_AGILITY
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED | F_EV_SPREAD_HP,
		.nature = NATURE_ADAMANT,
	},
	{
		.species = SPECIES_XATU,
		.heldItem = BATTLE_TOWER_ITEM_LUM_BERRY,
		.teamFlags = 0x09,
		.moves = {
			MOVE_PSYCHIC,
			MOVE_FLY,
			MOVE_CONFUSE_RAY,
			MOVE_TOXIC
		},
		.evSpread = F_EV_SPREAD_SPEED,
		.nature = NATURE_BASHFUL,
	},
	{
		.species = SPECIES_DODRIO,
		.heldItem = BATTLE_TOWER_ITEM_SHARP_BEAK,
		.teamFlags = 0x03,
		.moves = {
			MOVE_DRILL_PECK,
			MOVE_TRI_ATTACK,
			MOVE_PURSUIT,
			MOVE_TORMENT
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_ATTACK,
		.nature = NATURE_SERIOUS,
	},
	{
		.species = SPECIES_VILEPLUME,
		.heldItem = BATTLE_TOWER_ITEM_SITRUS_BERRY,
		.teamFlags = 0x89,
		.moves = {
			MOVE_POISON_POWDER,
			MOVE_STUN_SPORE,
			MOVE_SLEEP_POWDER,
			MOVE_PETAL_DANCE
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_MODEST,
	},
	{
		.species = SPECIES_MEDICHAM,
		.heldItem = BATTLE_TOWER_ITEM_TWISTED_SPOON,
		.teamFlags = 0x06,
		.moves = {
			MOVE_FOCUS_PUNCH,
			MOVE_LIGHT_SCREEN,
			MOVE_BULK_UP,
			MOVE_PSYCHIC
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED | F_EV_SPREAD_DEFENSE,
		.nature = NATURE_JOLLY,
	},
	{
		.species = SPECIES_ABSOL,
		.heldItem = BATTLE_TOWER_ITEM_SITRUS_BERRY,
		.teamFlags = 0x06,
		.moves = {
			MOVE_SLASH,
			MOVE_SWORDS_DANCE,
			MOVE_DOUBLE_TEAM,
			MOVE_ATTRACT
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_HP,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_DUSCLOPS,
		.heldItem = BATTLE_TOWER_ITEM_SPELL_TAG,
		.teamFlags = 0x4B,
		.moves = {
			MOVE_CONFUSE_RAY,
			MOVE_WILL_O_WISP,
			MOVE_NIGHT_SHADE,
			MOVE_DISABLE
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_DEFENSE,
		.nature = NATURE_LAX,
	},
	{
		.species = SPECIES_SHUPPET,
		.heldItem = BATTLE_TOWER_ITEM_SPELL_TAG,
		.teamFlags = 0x43,
		.moves = {
			MOVE_GRUDGE,
			MOVE_SHADOW_BALL,
			MOVE_CURSE,
			MOVE_KNOCK_OFF
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK,
		.nature = NATURE_IMPISH,
	},
	{
		.species = SPECIES_CASTFORM,
		.heldItem = BATTLE_TOWER_ITEM_LUM_BERRY,
		.teamFlags = 0x82,
		.moves = {
			MOVE_WEATHER_BALL,
			MOVE_HAIL,
			MOVE_SUNNY_DAY,
			MOVE_RAIN_DANCE
		},
		.evSpread = F_EV_SPREAD_SPEED,
		.nature = NATURE_MODEST,
	},
	{
		.species = SPECIES_MILOTIC,
		.heldItem = BATTLE_TOWER_ITEM_DRAGON_FANG,
		.teamFlags = 0x02,
		.moves = {
			MOVE_SURF,
			MOVE_REFRESH,
			MOVE_RECOVER,
			MOVE_RAIN_DANCE
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_SP_ATTACK,
		.nature = NATURE_ADAMANT,
	},
	{
		.species = SPECIES_SHARPEDO,
		.heldItem = BATTLE_TOWER_ITEM_PERSIM_BERRY,
		.teamFlags = 0x01,
		.moves = {
			MOVE_CRUNCH,
			MOVE_FOCUS_ENERGY,
			MOVE_SCARY_FACE,
			MOVE_SCREECH
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_ATTACK,
		.nature = NATURE_LAX,
	},
	{
		.species = SPECIES_FLYGON,
		.heldItem = BATTLE_TOWER_ITEM_CHERI_BERRY,
		.teamFlags = 0x06,
		.moves = {
			MOVE_EARTHQUAKE,
			MOVE_SAND_ATTACK,
			MOVE_DRAGON_BREATH,
			MOVE_SAND_TOMB
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_ATTACK,
		.nature = NATURE_NAUGHTY,
	},
	{
		.species = SPECIES_TRAPINCH,
		.heldItem = BATTLE_TOWER_ITEM_SITRUS_BERRY,
		.teamFlags = 0x09,
		.moves = {
			MOVE_TOXIC,
			MOVE_SAND_TOMB,
			MOVE_CRUNCH,
			MOVE_DOUBLE_TEAM
		},
		.evSpread = F_EV_SPREAD_ATTACK,
		.nature = NATURE_DOCILE,
	},
	{
		.species = SPECIES_LUNATONE,
		.heldItem = BATTLE_TOWER_ITEM_BRIGHT_POWDER,
		.teamFlags = 0x43,
		.moves = {
			MOVE_PSYCHIC,
			MOVE_ROCK_THROW,
			MOVE_HYPNOSIS,
			MOVE_LIGHT_SCREEN
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_SP_ATTACK,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_SOLROCK,
		.heldItem = BATTLE_TOWER_ITEM_PECHA_BERRY,
		.teamFlags = 0x43,
		.moves = {
			MOVE_SOLAR_BEAM,
			MOVE_SUNNY_DAY,
			MOVE_COSMIC_POWER,
			MOVE_CALM_MIND
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_DEFENSE,
		.nature = NATURE_QUIET,
	},
	{
		.species = SPECIES_BALTOY,
		.heldItem = BATTLE_TOWER_ITEM_SITRUS_BERRY,
		.teamFlags = 0x43,
		.moves = {
			MOVE_PSYCHIC,
			MOVE_EARTHQUAKE,
			MOVE_REFLECT,
			MOVE_SELF_DESTRUCT
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_BASHFUL,
	},
	{
		.species = SPECIES_CRAWDAUNT,
		.heldItem = BATTLE_TOWER_ITEM_QUICK_CLAW,
		.teamFlags = 0x06,
		.moves = {
			MOVE_CRABHAMMER,
			MOVE_SURF,
			MOVE_PROTECT,
			MOVE_BRICK_BREAK
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_RASH,
	},
	{
		.species = SPECIES_WHISCASH,
		.heldItem = BATTLE_TOWER_ITEM_ASPEAR_BERRY,
		.teamFlags = 0x06,
		.moves = {
			MOVE_EARTHQUAKE,
			MOVE_TICKLE,
			MOVE_AMNESIA,
			MOVE_SURF
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_HP,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_SEVIPER,
		.heldItem = BATTLE_TOWER_ITEM_SITRUS_BERRY,
		.teamFlags = 0x09,
		.moves = {
			MOVE_POISON_TAIL,
			MOVE_CRUNCH,
			MOVE_GIGA_DRAIN,
			MOVE_HAZE
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_ATTACK,
		.nature = NATURE_RELAXED,
	},
	{
		.species = SPECIES_MAGCARGO,
		.heldItem = BATTLE_TOWER_ITEM_BRIGHT_POWDER,
		.teamFlags = 0x89,
		.moves = {
			MOVE_FLAMETHROWER,
			MOVE_LIGHT_SCREEN,
			MOVE_AMNESIA,
			MOVE_ROCK_SLIDE
		},
		.evSpread = F_EV_SPREAD_ATTACK,
		.nature = NATURE_SASSY,
	},
	{
		.species = SPECIES_MACHAMP,
		.heldItem = BATTLE_TOWER_ITEM_BLACK_BELT,
		.teamFlags = 0x09,
		.moves = {
			MOVE_KARATE_CHOP,
			MOVE_SEISMIC_TOSS,
			MOVE_BRICK_BREAK,
			MOVE_LOW_KICK
		},
		.evSpread = F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_GENTLE,
	},
	{
		.species = SPECIES_SWALOT,
		.heldItem = BATTLE_TOWER_ITEM_SITRUS_BERRY,
		.teamFlags = 0x86,
		.moves = {
			MOVE_YAWN,
			MOVE_WATER_PULSE,
			MOVE_SHADOW_BALL,
			MOVE_SLUDGE_BOMB
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_NAUGHTY,
	},
	{
		.species = SPECIES_SCEPTILE,
		.heldItem = BATTLE_TOWER_ITEM_SITRUS_BERRY,
		.teamFlags = 0x0C,
		.moves = {
			MOVE_LEAF_BLADE,
			MOVE_GIGA_DRAIN,
			MOVE_FURY_CUTTER,
			MOVE_DETECT
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED | F_EV_SPREAD_HP,
		.nature = NATURE_NAIVE,
	},
	{
		.species = SPECIES_BLAZIKEN,
		.heldItem = BATTLE_TOWER_ITEM_SCOPE_LENS,
		.teamFlags = 0x0C,
		.moves = {
			MOVE_BLAZE_KICK,
			MOVE_FLAMETHROWER,
			MOVE_PROTECT,
			MOVE_QUICK_ATTACK
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED | F_EV_SPREAD_ATTACK,
		.nature = NATURE_DOCILE,
	},
	{
		.species = SPECIES_SWAMPERT,
		.heldItem = BATTLE_TOWER_ITEM_BRIGHT_POWDER,
		.teamFlags = 0x4C,
		.moves = {
			MOVE_SURF,
			MOVE_MUD_SHOT,
			MOVE_MUD_SLAP,
			MOVE_DOUBLE_TEAM
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED | F_EV_SPREAD_HP,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_MIGHTYENA,
		.heldItem = BATTLE_TOWER_ITEM_BLACK_GLASSES,
		.teamFlags = 0x04,
		.moves = {
			MOVE_CRUNCH,
			MOVE_HOWL,
			MOVE_SWAGGER,
			MOVE_SHADOW_BALL
		},
		.evSpread = F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_CALM,
	},
	{
		.species = SPECIES_LINOONE,
		.heldItem = BATTLE_TOWER_ITEM_CHESTO_BERRY,
		.teamFlags = 0x04,
		.moves = {
			MOVE_SLASH,
			MOVE_REST,
			MOVE_BELLY_DRUM,
			MOVE_THUNDERBOLT
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_ATTACK,
		.nature = NATURE_MILD,
	},
	{
		.species = SPECIES_BEAUTIFLY,
		.heldItem = BATTLE_TOWER_ITEM_LUM_BERRY,
		.teamFlags = 0x08,
		.moves = {
			MOVE_GIGA_DRAIN,
			MOVE_ATTRACT,
			MOVE_MORNING_SUN,
			MOVE_STUN_SPORE
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_HASTY,
	},
	{
		.species = SPECIES_DUSTOX,
		.heldItem = BATTLE_TOWER_ITEM_SITRUS_BERRY,
		.teamFlags = 0x08,
		.moves = {
			MOVE_PSYCHIC,
			MOVE_SILVER_WIND,
			MOVE_MOONLIGHT,
			MOVE_TOXIC
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_CAREFUL,
	},
	{
		.species = SPECIES_LUDICOLO,
		.heldItem = BATTLE_TOWER_ITEM_LUM_BERRY,
		.teamFlags = 0x0C,
		.moves = {
			MOVE_FAKE_OUT,
			MOVE_HYDRO_PUMP,
			MOVE_ICE_BEAM,
			MOVE_UPROAR
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_QUIET,
	},
	{
		.species = SPECIES_SHIFTRY,
		.heldItem = BATTLE_TOWER_ITEM_PERSIM_BERRY,
		.teamFlags = 0x0C,
		.moves = {
			MOVE_FRUSTRATION,
			MOVE_GIGA_DRAIN,
			MOVE_TORMENT,
			MOVE_SWAGGER
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED | F_EV_SPREAD_ATTACK,
		.nature = NATURE_RELAXED,
	},
	{
		.species = SPECIES_SWELLOW,
		.heldItem = BATTLE_TOWER_ITEM_LUM_BERRY,
		.teamFlags = 0x88,
		.moves = {
			MOVE_FLY,
			MOVE_ENDEAVOR,
			MOVE_AERIAL_ACE,
			MOVE_TOXIC
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_ATTACK,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_GARDEVOIR,
		.heldItem = BATTLE_TOWER_ITEM_BLACK_GLASSES,
		.teamFlags = 0x4A,
		.moves = {
			MOVE_HYPNOSIS,
			MOVE_DREAM_EATER,
			MOVE_PSYCHIC,
			MOVE_DOUBLE_TEAM
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED,
		.nature = NATURE_CAREFUL,
	},
	{
		.species = SPECIES_BRELOOM,
		.heldItem = BATTLE_TOWER_ITEM_BRIGHT_POWDER,
		.teamFlags = 0x0C,
		.moves = {
			MOVE_DYNAMIC_PUNCH,
			MOVE_MIND_READER,
			MOVE_SNATCH,
			MOVE_MEGA_DRAIN
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_ADAMANT,
	},
	{
		.species = SPECIES_VIGOROTH,
		.heldItem = BATTLE_TOWER_ITEM_QUICK_CLAW,
		.teamFlags = 0x04,
		.moves = {
			MOVE_SLASH,
			MOVE_UPROAR,
			MOVE_ENCORE,
			MOVE_FACADE
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_DEFENSE | F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_CALM,
	},
	{
		.species = SPECIES_NINJASK,
		.heldItem = BATTLE_TOWER_ITEM_SILVER_POWDER,
		.teamFlags = 0x04,
		.moves = {
			MOVE_FURY_CUTTER,
			MOVE_GIGA_DRAIN,
			MOVE_SWORDS_DANCE,
			MOVE_DOUBLE_TEAM
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_SASSY,
	},
	{
		.species = SPECIES_SHEDINJA,
		.heldItem = BATTLE_TOWER_ITEM_QUICK_CLAW,
		.teamFlags = 0xCA,
		.moves = {
			MOVE_CONFUSE_RAY,
			MOVE_SOLAR_BEAM,
			MOVE_SUNNY_DAY,
			MOVE_GRUDGE
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED | F_EV_SPREAD_DEFENSE,
		.nature = NATURE_JOLLY,
	},
	{
		.species = SPECIES_LOUDRED,
		.heldItem = BATTLE_TOWER_ITEM_PECHA_BERRY,
		.teamFlags = 0x04,
		.moves = {
			MOVE_HYPER_VOICE,
			MOVE_HOWL,
			MOVE_SHADOW_BALL,
			MOVE_TORMENT
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_HARIYAMA,
		.heldItem = BATTLE_TOWER_ITEM_KINGS_ROCK,
		.teamFlags = 0x04,
		.moves = {
			MOVE_ARM_THRUST,
			MOVE_BULK_UP,
			MOVE_BRICK_BREAK,
			MOVE_HIDDEN_POWER
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_DEFENSE | F_EV_SPREAD_ATTACK,
		.nature = NATURE_BASHFUL,
	},
	{
		.species = SPECIES_ALAKAZAM,
		.heldItem = BATTLE_TOWER_ITEM_TWISTED_SPOON,
		.teamFlags = 0x88,
		.moves = {
			MOVE_PSYCHIC,
			MOVE_SHADOW_BALL,
			MOVE_FUTURE_SIGHT,
			MOVE_DISABLE
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED | F_EV_SPREAD_HP,
		.nature = NATURE_QUIET,
	},
	{
		.species = SPECIES_CROBAT,
		.heldItem = BATTLE_TOWER_ITEM_CHERI_BERRY,
		.teamFlags = 0x88,
		.moves = {
			MOVE_CONFUSE_RAY,
			MOVE_TOXIC,
			MOVE_MEAN_LOOK,
			MOVE_SNATCH
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_MAWILE,
		.heldItem = BATTLE_TOWER_ITEM_METAL_COAT,
		.teamFlags = 0x04,
		.moves = {
			MOVE_CRUNCH,
			MOVE_IRON_DEFENSE,
			MOVE_FAKE_TEARS,
			MOVE_POISON_FANG
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_ATTACK,
		.nature = NATURE_NAIVE,
	},
	{
		.species = SPECIES_AGGRON,
		.heldItem = BATTLE_TOWER_ITEM_METAL_COAT,
		.teamFlags = 0x45,
		.moves = {
			MOVE_METAL_CLAW,
			MOVE_FLAMETHROWER,
			MOVE_METAL_SOUND,
			MOVE_ICE_BEAM
		},
		.evSpread = F_EV_SPREAD_DEFENSE | F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_GOLEM,
		.heldItem = BATTLE_TOWER_ITEM_SOFT_SAND,
		.teamFlags = 0xC5,
		.moves = {
			MOVE_ROLLOUT,
			MOVE_DEFENSE_CURL,
			MOVE_DOUBLE_TEAM,
			MOVE_SELF_DESTRUCT
		},
		.evSpread = F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_MANECTRIC,
		.heldItem = BATTLE_TOWER_ITEM_MAGNET,
		.teamFlags = 0x04,
		.moves = {
			MOVE_THUNDER,
			MOVE_RAIN_DANCE,
			MOVE_THUNDER_WAVE,
			MOVE_CHARGE
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_HP,
		.nature = NATURE_CAREFUL,
	},
	{
		.species = SPECIES_VOLBEAT,
		.heldItem = BATTLE_TOWER_ITEM_SILVER_POWDER,
		.teamFlags = 0x08,
		.moves = {
			MOVE_CONFUSE_RAY,
			MOVE_SIGNAL_BEAM,
			MOVE_MOONLIGHT,
			MOVE_TAIL_GLOW
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_HP,
		.nature = NATURE_DOCILE,
	},
	{
		.species = SPECIES_ILLUMISE,
		.heldItem = BATTLE_TOWER_ITEM_SILVER_POWDER,
		.teamFlags = 0x08,
		.moves = {
			MOVE_THUNDERBOLT,
			MOVE_FLATTER,
			MOVE_WISH,
			MOVE_ENCORE
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_HP,
		.nature = NATURE_QUIET,
	},
	{
		.species = SPECIES_MASQUERAIN,
		.heldItem = BATTLE_TOWER_ITEM_PERSIM_BERRY,
		.teamFlags = 0x88,
		.moves = {
			MOVE_GIGA_DRAIN,
			MOVE_SILVER_WIND,
			MOVE_STUN_SPORE,
			MOVE_TOXIC
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_SP_ATTACK,
		.nature = NATURE_NAIVE,
	},
	{
		.species = SPECIES_ROSELIA,
		.heldItem = BATTLE_TOWER_ITEM_MIRACLE_SEED,
		.teamFlags = 0x08,
		.moves = {
			MOVE_PETAL_DANCE,
			MOVE_GROWTH,
			MOVE_SYNTHESIS,
			MOVE_GRASS_WHISTLE
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_IMPISH,
	},
	{
		.species = SPECIES_DELCATTY,
		.heldItem = BATTLE_TOWER_ITEM_SITRUS_BERRY,
		.teamFlags = 0x08,
		.moves = {
			MOVE_SING,
			MOVE_ATTRACT,
			MOVE_DOUBLE_SLAP,
			MOVE_HEAL_BELL
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_TIMID,
	},
	{
		.species = SPECIES_SEAKING,
		.heldItem = BATTLE_TOWER_ITEM_MYSTIC_WATER,
		.teamFlags = 0x88,
		.moves = {
			MOVE_RAIN_DANCE,
			MOVE_SURF,
			MOVE_ATTRACT,
			MOVE_ICE_BEAM
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_SP_ATTACK,
		.nature = NATURE_BRAVE,
	},
	{
		.species = SPECIES_GYARADOS,
		.heldItem = BATTLE_TOWER_ITEM_DRAGON_FANG,
		.teamFlags = 0x8C,
		.moves = {
			MOVE_HYDRO_PUMP,
			MOVE_EARTHQUAKE,
			MOVE_DRAGON_RAGE,
			MOVE_PROTECT
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_CALM,
	},
	{
		.species = SPECIES_SWALOT,
		.heldItem = BATTLE_TOWER_ITEM_LEFTOVERS,
		.teamFlags = 0x42,
		.moves = {
			MOVE_STOCKPILE,
			MOVE_SWALLOW,
			MOVE_SPIT_UP,
			MOVE_YAWN
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_NAUGHTY,
	},
	{
		.species = SPECIES_MAGCARGO,
		.heldItem = BATTLE_TOWER_ITEM_ASPEAR_BERRY,
		.teamFlags = 0x41,
		.moves = {
			MOVE_ROCK_SLIDE,
			MOVE_FIRE_BLAST,
			MOVE_BODY_SLAM,
			MOVE_LIGHT_SCREEN
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_LONELY,
	},
	{
		.species = SPECIES_MUK,
		.heldItem = BATTLE_TOWER_ITEM_POISON_BARB,
		.teamFlags = 0xC3,
		.moves = {
			MOVE_SLUDGE_BOMB,
			MOVE_FLAMETHROWER,
			MOVE_ACID_ARMOR,
			MOVE_DISABLE
		},
		.evSpread = F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_NAIVE,
	},
	{
		.species = SPECIES_SPINDA,
		.heldItem = BATTLE_TOWER_ITEM_SILK_SCARF,
		.teamFlags = 0x42,
		.moves = {
			MOVE_DIZZY_PUNCH,
			MOVE_TEETER_DANCE,
			MOVE_PSYCH_UP,
			MOVE_FACADE
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_MODEST,
	},
	{
		.species = SPECIES_ALTARIA,
		.heldItem = BATTLE_TOWER_ITEM_DRAGON_FANG,
		.teamFlags = 0x03,
		.moves = {
			MOVE_DRAGON_CLAW,
			MOVE_DRAGON_BREATH,
			MOVE_DRAGON_DANCE,
			MOVE_REFRESH
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_RASH,
	},
	{
		.species = SPECIES_ZANGOOSE,
		.heldItem = BATTLE_TOWER_ITEM_SITRUS_BERRY,
		.teamFlags = 0x03,
		.moves = {
			MOVE_CRUSH_CLAW,
			MOVE_TAUNT,
			MOVE_SWORDS_DANCE,
			MOVE_DETECT
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_QUIRKY,
	},
	{
		.species = SPECIES_SEVIPER,
		.heldItem = BATTLE_TOWER_ITEM_LUM_BERRY,
		.teamFlags = 0x41,
		.moves = {
			MOVE_SWAGGER,
			MOVE_TAUNT,
			MOVE_GLARE,
			MOVE_POISON_TAIL
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_CAREFUL,
	},
	{
		.species = SPECIES_GRUMPIG,
		.heldItem = BATTLE_TOWER_ITEM_SITRUS_BERRY,
		.teamFlags = 0x42,
		.moves = {
			MOVE_TOXIC,
			MOVE_BOUNCE,
			MOVE_CONFUSE_RAY,
			MOVE_ATTRACT
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_HP,
		.nature = NATURE_BRAVE,
	},
	{
		.species = SPECIES_CACTURNE,
		.heldItem = BATTLE_TOWER_ITEM_MIRACLE_SEED,
		.teamFlags = 0x41,
		.moves = {
			MOVE_NEEDLE_ARM,
			MOVE_INGRAIN,
			MOVE_SPIKES,
			MOVE_COTTON_SPORE
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_SASSY,
	},
	{
		.species = SPECIES_CLAYDOL,
		.heldItem = BATTLE_TOWER_ITEM_CHESTO_BERRY,
		.teamFlags = 0x03,
		.moves = {
			MOVE_EARTHQUAKE,
			MOVE_SANDSTORM,
			MOVE_COSMIC_POWER,
			MOVE_EXPLOSION
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_LAX,
	},
	{
		.species = SPECIES_TENTACRUEL,
		.heldItem = BATTLE_TOWER_ITEM_MENTAL_HERB,
		.teamFlags = 0xC1,
		.moves = {
			MOVE_SLUDGE_BOMB,
			MOVE_HYDRO_PUMP,
			MOVE_BARRIER,
			MOVE_SUPERSONIC
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_SPEED | F_EV_SPREAD_HP,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_WIGGLYTUFF,
		.heldItem = BATTLE_TOWER_ITEM_RAWST_BERRY,
		.teamFlags = 0xC3,
		.moves = {
			MOVE_SING,
			MOVE_FOCUS_PUNCH,
			MOVE_DISABLE,
			MOVE_FACADE
		},
		.evSpread = F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_ADAMANT,
	},
	{
		.species = SPECIES_AZUMARILL,
		.heldItem = BATTLE_TOWER_ITEM_CHERI_BERRY,
		.teamFlags = 0xC2,
		.moves = {
			MOVE_SURF,
			MOVE_ATTRACT,
			MOVE_DEFENSE_CURL,
			MOVE_ROLLOUT
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_RASH,
	},
	{
		.species = SPECIES_ELECTRODE,
		.heldItem = BATTLE_TOWER_ITEM_CHERI_BERRY,
		.teamFlags = 0xC3,
		.moves = {
			MOVE_THUNDERBOLT,
			MOVE_MIRROR_COAT,
			MOVE_LIGHT_SCREEN,
			MOVE_SELF_DESTRUCT
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_SPEED | F_EV_SPREAD_DEFENSE,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_MILOTIC,
		.heldItem = BATTLE_TOWER_ITEM_BRIGHT_POWDER,
		.teamFlags = 0x42,
		.moves = {
			MOVE_HYDRO_PUMP,
			MOVE_ATTRACT,
			MOVE_RECOVER,
			MOVE_REFRESH
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_JOLLY,
	},
	{
		.species = SPECIES_KECLEON,
		.heldItem = BATTLE_TOWER_ITEM_SITRUS_BERRY,
		.teamFlags = 0x43,
		.moves = {
			MOVE_SKILL_SWAP,
			MOVE_ANCIENT_POWER,
			MOVE_WATER_PULSE,
			MOVE_THUNDERBOLT
		},
		.evSpread = F_EV_SPREAD_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_NAUGHTY,
	},
	{
		.species = SPECIES_DUSCLOPS,
		.heldItem = BATTLE_TOWER_ITEM_LEFTOVERS,
		.teamFlags = 0x43,
		.moves = {
			MOVE_CONFUSE_RAY,
			MOVE_CURSE,
			MOVE_REST,
			MOVE_MEAN_LOOK
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_BASHFUL,
	},
	{
		.species = SPECIES_ABSOL,
		.heldItem = BATTLE_TOWER_ITEM_LUM_BERRY,
		.teamFlags = 0x41,
		.moves = {
			MOVE_SLASH,
			MOVE_SWORDS_DANCE,
			MOVE_DOUBLE_TEAM,
			MOVE_SNATCH
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_DOCILE,
	},
	{
		.species = SPECIES_NINETALES,
		.heldItem = BATTLE_TOWER_ITEM_APICOT_BERRY,
		.teamFlags = 0xC2,
		.moves = {
			MOVE_FLAMETHROWER,
			MOVE_CONFUSE_RAY,
			MOVE_DOUBLE_TEAM,
			MOVE_WILL_O_WISP
		},
		.evSpread = F_EV_SPREAD_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_TIMID,
	},
	{
		.species = SPECIES_PIKACHU,
		.heldItem = BATTLE_TOWER_ITEM_LIGHT_BALL,
		.teamFlags = 0xC2,
		.moves = {
			MOVE_THUNDER_WAVE,
			MOVE_THUNDER,
			MOVE_RAIN_DANCE,
			MOVE_ATTRACT
		},
		.evSpread = F_EV_SPREAD_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_HASTY,
	},
	{
		.species = SPECIES_VILEPLUME,
		.heldItem = BATTLE_TOWER_ITEM_ASPEAR_BERRY,
		.teamFlags = 0xC3,
		.moves = {
			MOVE_GIGA_DRAIN,
			MOVE_SLEEP_POWDER,
			MOVE_MOONLIGHT,
			MOVE_SLUDGE_BOMB
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_DEFENSE | F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_DONPHAN,
		.heldItem = BATTLE_TOWER_ITEM_PERSIM_BERRY,
		.teamFlags = 0x41,
		.moves = {
			MOVE_EARTHQUAKE,
			MOVE_DOUBLE_EDGE,
			MOVE_IRON_TAIL,
			MOVE_FISSURE
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_QUIRKY,
	},
	{
		.species = SPECIES_STARMIE,
		.heldItem = BATTLE_TOWER_ITEM_CHERI_BERRY,
		.teamFlags = 0xC3,
		.moves = {
			MOVE_CONFUSE_RAY,
			MOVE_ICE_BEAM,
			MOVE_RECOVER,
			MOVE_DOUBLE_TEAM
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_SPEED | F_EV_SPREAD_DEFENSE,
		.nature = NATURE_HASTY,
	},
	{
		.species = SPECIES_WALREIN,
		.heldItem = BATTLE_TOWER_ITEM_NEVER_MELT_ICE,
		.teamFlags = 0x43,
		.moves = {
			MOVE_ICE_BEAM,
			MOVE_BODY_SLAM,
			MOVE_ENCORE,
			MOVE_HAIL
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_LAX,
	},
	{
		.species = SPECIES_RELICANTH,
		.heldItem = BATTLE_TOWER_ITEM_LEFTOVERS,
		.teamFlags = 0x41,
		.moves = {
			MOVE_YAWN,
			MOVE_MUD_SPORT,
			MOVE_DOUBLE_EDGE,
			MOVE_SANDSTORM
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_LONELY,
	},
	{
		.species = SPECIES_KINGDRA,
		.heldItem = BATTLE_TOWER_ITEM_BRIGHT_POWDER,
		.teamFlags = 0x43,
		.moves = {
			MOVE_RAIN_DANCE,
			MOVE_ICE_BEAM,
			MOVE_HYDRO_PUMP,
			MOVE_AGILITY
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_CRADILY,
		.heldItem = BATTLE_TOWER_ITEM_LEFTOVERS,
		.teamFlags = 0x43,
		.moves = {
			MOVE_CONFUSE_RAY,
			MOVE_INGRAIN,
			MOVE_ANCIENT_POWER,
			MOVE_GIGA_DRAIN
		},
		.evSpread = F_EV_SPREAD_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_MILD,
	},
	{
		.species = SPECIES_ARMALDO,
		.heldItem = BATTLE_TOWER_ITEM_SITRUS_BERRY,
		.teamFlags = 0x43,
		.moves = {
			MOVE_SLASH,
			MOVE_ROCK_SLIDE,
			MOVE_EARTHQUAKE,
			MOVE_WATER_PULSE
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_NAIVE,
	},
	{
		.species = SPECIES_METAGROSS,
		.heldItem = BATTLE_TOWER_ITEM_METAL_COAT,
		.teamFlags = 0x41,
		.moves = {
			MOVE_METAL_CLAW,
			MOVE_PSYCHIC,
			MOVE_LIGHT_SCREEN,
			MOVE_AGILITY
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_GENTLE,
	},
	{
		.species = SPECIES_SALAMENCE,
		.heldItem = BATTLE_TOWER_ITEM_LUM_BERRY,
		.teamFlags = 0x42,
		.moves = {
			MOVE_DRAGON_BREATH,
			MOVE_CRUNCH,
			MOVE_FLAMETHROWER,
			MOVE_AERIAL_ACE
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_SPEED | F_EV_SPREAD_DEFENSE,
		.nature = NATURE_HASTY,
	},
	{
		.species = SPECIES_MIGHTYENA,
		.heldItem = BATTLE_TOWER_ITEM_LIECHI_BERRY,
		.teamFlags = 0x01,
		.moves = {
			MOVE_CRUNCH,
			MOVE_YAWN,
			MOVE_FACADE,
			MOVE_HOWL
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_GENTLE,
	},
	{
		.species = SPECIES_LINOONE,
		.heldItem = BATTLE_TOWER_ITEM_SALAC_BERRY,
		.teamFlags = 0x02,
		.moves = {
			MOVE_HYPER_BEAM,
			MOVE_FACADE,
			MOVE_ATTRACT,
			MOVE_TRICK
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_LUDICOLO,
		.heldItem = BATTLE_TOWER_ITEM_LUM_BERRY,
		.teamFlags = 0x03,
		.moves = {
			MOVE_SURF,
			MOVE_FOCUS_PUNCH,
			MOVE_FAKE_OUT,
			MOVE_SYNTHESIS
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_DEFENSE | F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_TIMID,
	},
	{
		.species = SPECIES_EXPLOUD,
		.heldItem = BATTLE_TOWER_ITEM_LIECHI_BERRY,
		.teamFlags = 0x01,
		.moves = {
			MOVE_UPROAR,
			MOVE_EARTHQUAKE,
			MOVE_ICE_BEAM,
			MOVE_FLAMETHROWER
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_ATTACK,
		.nature = NATURE_DOCILE,
	},
	{
		.species = SPECIES_SWELLOW,
		.heldItem = BATTLE_TOWER_ITEM_LANSAT_BERRY,
		.teamFlags = 0x02,
		.moves = {
			MOVE_FACADE,
			MOVE_SUPERSONIC,
			MOVE_WING_ATTACK,
			MOVE_ENDEAVOR
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_NAIVE,
	},
	{
		.species = SPECIES_PELIPPER,
		.heldItem = BATTLE_TOWER_ITEM_QUICK_CLAW,
		.teamFlags = 0x82,
		.moves = {
			MOVE_STOCKPILE,
			MOVE_SWALLOW,
			MOVE_SPIT_UP,
			MOVE_ATTRACT
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_BRELOOM,
		.heldItem = BATTLE_TOWER_ITEM_FOCUS_BAND,
		.teamFlags = 0x01,
		.moves = {
			MOVE_DYNAMIC_PUNCH,
			MOVE_COUNTER,
			MOVE_BULK_UP,
			MOVE_MIND_READER
		},
		.evSpread = F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_SHEDINJA,
		.heldItem = BATTLE_TOWER_ITEM_LUM_BERRY,
		.teamFlags = 0x01,
		.moves = {
			MOVE_RETURN,
			MOVE_DOUBLE_TEAM,
			MOVE_TOXIC,
			MOVE_SHADOW_BALL
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_ATTACK,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_EXPLOUD,
		.heldItem = BATTLE_TOWER_ITEM_SITRUS_BERRY,
		.teamFlags = 0x01,
		.moves = {
			MOVE_HYPER_BEAM,
			MOVE_SUPERSONIC,
			MOVE_FLAMETHROWER,
			MOVE_ICE_BEAM
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_ATTACK,
		.nature = NATURE_GENTLE,
	},
	{
		.species = SPECIES_HARIYAMA,
		.heldItem = BATTLE_TOWER_ITEM_SCOPE_LENS,
		.teamFlags = 0x01,
		.moves = {
			MOVE_CROSS_CHOP,
			MOVE_COUNTER,
			MOVE_FACADE,
			MOVE_FAKE_OUT
		},
		.evSpread = F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_GENTLE,
	},
	{
		.species = SPECIES_ALAKAZAM,
		.heldItem = BATTLE_TOWER_ITEM_PETAYA_BERRY,
		.teamFlags = 0x83,
		.moves = {
			MOVE_PSYCHIC,
			MOVE_ENCORE,
			MOVE_DISABLE,
			MOVE_RECOVER
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED,
		.nature = NATURE_QUIET,
	},
	{
		.species = SPECIES_CROBAT,
		.heldItem = BATTLE_TOWER_ITEM_SCOPE_LENS,
		.teamFlags = 0x81,
		.moves = {
			MOVE_CONFUSE_RAY,
			MOVE_AIR_CUTTER,
			MOVE_TORMENT,
			MOVE_DOUBLE_TEAM
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_ATTACK,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_SABLEYE,
		.heldItem = BATTLE_TOWER_ITEM_LEFTOVERS,
		.teamFlags = 0x83,
		.moves = {
			MOVE_TOXIC,
			MOVE_DETECT,
			MOVE_RECOVER,
			MOVE_TORMENT
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_RELAXED,
	},
	{
		.species = SPECIES_MAWILE,
		.heldItem = BATTLE_TOWER_ITEM_CHESTO_BERRY,
		.teamFlags = 0x02,
		.moves = {
			MOVE_CRUNCH,
			MOVE_SWORDS_DANCE,
			MOVE_IRON_DEFENSE,
			MOVE_REST
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_DEFENSE | F_EV_SPREAD_ATTACK,
		.nature = NATURE_GENTLE,
	},
	{
		.species = SPECIES_AGGRON,
		.heldItem = BATTLE_TOWER_ITEM_SITRUS_BERRY,
		.teamFlags = 0x01,
		.moves = {
			MOVE_DOUBLE_EDGE,
			MOVE_IRON_DEFENSE,
			MOVE_ROAR,
			MOVE_EARTHQUAKE
		},
		.evSpread = F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_GENTLE,
	},
	{
		.species = SPECIES_GOLEM,
		.heldItem = BATTLE_TOWER_ITEM_SALAC_BERRY,
		.teamFlags = 0x01,
		.moves = {
			MOVE_EARTHQUAKE,
			MOVE_ROCK_SLIDE,
			MOVE_FLAMETHROWER,
			MOVE_FACADE
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_GENTLE,
	},
	{
		.species = SPECIES_NOSEPASS,
		.heldItem = BATTLE_TOWER_ITEM_SITRUS_BERRY,
		.teamFlags = 0x81,
		.moves = {
			MOVE_THUNDER_WAVE,
			MOVE_ROCK_SLIDE,
			MOVE_TORMENT,
			MOVE_ATTRACT
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_NAIVE,
	},
	{
		.species = SPECIES_MANECTRIC,
		.heldItem = BATTLE_TOWER_ITEM_PETAYA_BERRY,
		.teamFlags = 0x02,
		.moves = {
			MOVE_THUNDER,
			MOVE_CRUNCH,
			MOVE_THUNDER_WAVE,
			MOVE_QUICK_ATTACK
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED | F_EV_SPREAD_ATTACK,
		.nature = NATURE_JOLLY,
	},
	{
		.species = SPECIES_ROSELIA,
		.heldItem = BATTLE_TOWER_ITEM_LEFTOVERS,
		.teamFlags = 0x82,
		.moves = {
			MOVE_GRASS_WHISTLE,
			MOVE_LEECH_SEED,
			MOVE_GIGA_DRAIN,
			MOVE_GROWTH
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED | F_EV_SPREAD_HP,
		.nature = NATURE_QUIET,
	},
	{
		.species = SPECIES_DELCATTY,
		.heldItem = BATTLE_TOWER_ITEM_STARF_BERRY,
		.teamFlags = 0x02,
		.moves = {
			MOVE_ASSIST,
			MOVE_SING,
			MOVE_ATTRACT,
			MOVE_SUBSTITUTE
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_DOCILE,
	},
	{
		.species = SPECIES_TROPIUS,
		.heldItem = BATTLE_TOWER_ITEM_SCOPE_LENS,
		.teamFlags = 0xC2,
		.moves = {
			MOVE_RAZOR_LEAF,
			MOVE_EARTHQUAKE,
			MOVE_ATTRACT,
			MOVE_SYNTHESIS
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_ATTACK,
		.nature = NATURE_JOLLY,
	},
	{
		.species = SPECIES_SWALOT,
		.heldItem = BATTLE_TOWER_ITEM_LIECHI_BERRY,
		.teamFlags = 0x03,
		.moves = {
			MOVE_YAWN,
			MOVE_SLUDGE_BOMB,
			MOVE_ATTRACT,
			MOVE_ICE_BEAM
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_GENTLE,
	},
	{
		.species = SPECIES_MACHAMP,
		.heldItem = BATTLE_TOWER_ITEM_BLACK_BELT,
		.teamFlags = 0x01,
		.moves = {
			MOVE_CROSS_CHOP,
			MOVE_BULK_UP,
			MOVE_LOW_KICK,
			MOVE_BRICK_BREAK
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_BASHFUL,
	},
	{
		.species = SPECIES_CAMERUPT,
		.heldItem = BATTLE_TOWER_ITEM_SITRUS_BERRY,
		.teamFlags = 0x40,
		.moves = {
			MOVE_ERUPTION,
			MOVE_EARTHQUAKE,
			MOVE_ROCK_SLIDE,
			MOVE_OVERHEAT
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_NAIVE,
	},
	{
		.species = SPECIES_MAGCARGO,
		.heldItem = BATTLE_TOWER_ITEM_BRIGHT_POWDER,
		.teamFlags = 0x03,
		.moves = {
			MOVE_FLAMETHROWER,
			MOVE_ROCK_SLIDE,
			MOVE_EARTHQUAKE,
			MOVE_REFLECT
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_WEEZING,
		.heldItem = BATTLE_TOWER_ITEM_SALAC_BERRY,
		.teamFlags = 0x81,
		.moves = {
			MOVE_WILL_O_WISP,
			MOVE_HYPER_BEAM,
			MOVE_THUNDERBOLT,
			MOVE_DESTINY_BOND
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED | F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_LAX,
	},
	{
		.species = SPECIES_SPINDA,
		.heldItem = BATTLE_TOWER_ITEM_CHOICE_BAND,
		.teamFlags = 0x82,
		.moves = {
			MOVE_TRICK,
			MOVE_TEETER_DANCE,
			MOVE_FOCUS_PUNCH,
			MOVE_FACADE
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_SPEED | F_EV_SPREAD_DEFENSE,
		.nature = NATURE_TIMID,
	},
	{
		.species = SPECIES_SKARMORY,
		.heldItem = BATTLE_TOWER_ITEM_SALAC_BERRY,
		.teamFlags = 0x01,
		.moves = {
			MOVE_DRILL_PECK,
			MOVE_STEEL_WING,
			MOVE_TORMENT,
			MOVE_PROTECT
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_ALTARIA,
		.heldItem = BATTLE_TOWER_ITEM_QUICK_CLAW,
		.teamFlags = 0x02,
		.moves = {
			MOVE_SING,
			MOVE_DRAGON_CLAW,
			MOVE_ICE_BEAM,
			MOVE_EARTHQUAKE
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_GRUMPIG,
		.heldItem = BATTLE_TOWER_ITEM_LUM_BERRY,
		.teamFlags = 0x82,
		.moves = {
			MOVE_PSYCHIC,
			MOVE_CONFUSE_RAY,
			MOVE_CALM_MIND,
			MOVE_REST
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED | F_EV_SPREAD_HP,
		.nature = NATURE_QUIET,
	},
	{
		.species = SPECIES_SHIFTRY,
		.heldItem = BATTLE_TOWER_ITEM_QUICK_CLAW,
		.teamFlags = 0x20,
		.moves = {
			MOVE_SWAGGER,
			MOVE_FRUSTRATION,
			MOVE_ATTRACT,
			MOVE_EXPLOSION
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_CLAYDOL,
		.heldItem = BATTLE_TOWER_ITEM_LIECHI_BERRY,
		.teamFlags = 0x20,
		.moves = {
			MOVE_COSMIC_POWER,
			MOVE_PSYCHIC,
			MOVE_EARTHQUAKE,
			MOVE_EXPLOSION
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_ATTACK,
		.nature = NATURE_RELAXED,
	},
	{
		.species = SPECIES_HARIYAMA,
		.heldItem = BATTLE_TOWER_ITEM_CHESTO_BERRY,
		.teamFlags = 0x33,
		.moves = {
			MOVE_EARTHQUAKE,
			MOVE_COUNTER,
			MOVE_BELLY_DRUM,
			MOVE_REST
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_ATTACK,
		.nature = NATURE_SASSY,
	},
	{
		.species = SPECIES_NOSEPASS,
		.heldItem = BATTLE_TOWER_ITEM_LIECHI_BERRY,
		.teamFlags = 0x20,
		.moves = {
			MOVE_ROCK_SLIDE,
			MOVE_THUNDER_WAVE,
			MOVE_EARTHQUAKE,
			MOVE_EXPLOSION
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_LAX,
	},
	{
		.species = SPECIES_DUSCLOPS,
		.heldItem = BATTLE_TOWER_ITEM_SALAC_BERRY,
		.teamFlags = 0x33,
		.moves = {
			MOVE_SHADOW_PUNCH,
			MOVE_WILL_O_WISP,
			MOVE_CONFUSE_RAY,
			MOVE_DESTINY_BOND
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_HP,
		.nature = NATURE_SASSY,
	},
	{
		.species = SPECIES_SEAKING,
		.heldItem = BATTLE_TOWER_ITEM_LEPPA_BERRY,
		.teamFlags = 0x20,
		.moves = {
			MOVE_HORN_DRILL,
			MOVE_AGILITY,
			MOVE_SLEEP_TALK,
			MOVE_REST
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_BRAVE,
	},
	{
		.species = SPECIES_CAMERUPT,
		.heldItem = BATTLE_TOWER_ITEM_BRIGHT_POWDER,
		.teamFlags = 0x73,
		.moves = {
			MOVE_EARTHQUAKE,
			MOVE_ERUPTION,
			MOVE_ROCK_SLIDE,
			MOVE_FISSURE
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_NAIVE,
	},
	{
		.species = SPECIES_LANTURN,
		.heldItem = BATTLE_TOWER_ITEM_LUM_BERRY,
		.teamFlags = 0x13,
		.moves = {
			MOVE_THUNDERBOLT,
			MOVE_SURF,
			MOVE_THUNDER_WAVE,
			MOVE_CONFUSE_RAY
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_QUIET,
	},
	{
		.species = SPECIES_WEEZING,
		.heldItem = BATTLE_TOWER_ITEM_SALAC_BERRY,
		.teamFlags = 0x33,
		.moves = {
			MOVE_SLUDGE_BOMB,
			MOVE_THUNDERBOLT,
			MOVE_FIRE_BLAST,
			MOVE_EXPLOSION
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_WHISCASH,
		.heldItem = BATTLE_TOWER_ITEM_LEPPA_BERRY,
		.teamFlags = 0x20,
		.moves = {
			MOVE_EARTHQUAKE,
			MOVE_SURF,
			MOVE_SPARK,
			MOVE_FISSURE
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_SPEED | F_EV_SPREAD_ATTACK,
		.nature = NATURE_RELAXED,
	},
	{
		.species = SPECIES_AGGRON,
		.heldItem = BATTLE_TOWER_ITEM_LIECHI_BERRY,
		.teamFlags = 0x51,
		.moves = {
			MOVE_DOUBLE_EDGE,
			MOVE_EARTHQUAKE,
			MOVE_SURF,
			MOVE_DRAGON_CLAW
		},
		.evSpread = F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_GENTLE,
	},
	{
		.species = SPECIES_KECLEON,
		.heldItem = BATTLE_TOWER_ITEM_CHOICE_BAND,
		.teamFlags = 0x12,
		.moves = {
			MOVE_TRICK,
			MOVE_FOCUS_PUNCH,
			MOVE_ATTRACT,
			MOVE_SNATCH
		},
		.evSpread = F_EV_SPREAD_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_MILD,
	},
	{
		.species = SPECIES_SHARPEDO,
		.heldItem = BATTLE_TOWER_ITEM_KINGS_ROCK,
		.teamFlags = 0x11,
		.moves = {
			MOVE_CRUNCH,
			MOVE_DOUBLE_EDGE,
			MOVE_SURF,
			MOVE_SWAGGER
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_ATTACK,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_ABSOL,
		.heldItem = BATTLE_TOWER_ITEM_SALAC_BERRY,
		.teamFlags = 0x12,
		.moves = {
			MOVE_DOUBLE_EDGE,
			MOVE_FACADE,
			MOVE_SWORDS_DANCE,
			MOVE_QUICK_ATTACK
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_WAILORD,
		.heldItem = BATTLE_TOWER_ITEM_LEPPA_BERRY,
		.teamFlags = 0x72,
		.moves = {
			MOVE_HYDRO_PUMP,
			MOVE_EARTHQUAKE,
			MOVE_ATTRACT,
			MOVE_FISSURE
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_HP,
		.nature = NATURE_TIMID,
	},
	{
		.species = SPECIES_TENTACRUEL,
		.heldItem = BATTLE_TOWER_ITEM_LEFTOVERS,
		.teamFlags = 0x20,
		.moves = {
			MOVE_HYDRO_PUMP,
			MOVE_SLUDGE_BOMB,
			MOVE_BARRIER,
			MOVE_MIRROR_COAT
		},
		.evSpread = F_EV_SPREAD_DEFENSE | F_EV_SPREAD_ATTACK,
		.nature = NATURE_JOLLY,
	},
	{
		.species = SPECIES_SABLEYE,
		.heldItem = BATTLE_TOWER_ITEM_LEFTOVERS,
		.teamFlags = 0x32,
		.moves = {
			MOVE_SHADOW_BALL,
			MOVE_TOXIC,
			MOVE_RECOVER,
			MOVE_DOUBLE_TEAM
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_WOBBUFFET,
		.heldItem = BATTLE_TOWER_ITEM_LEFTOVERS,
		.teamFlags = 0x20,
		.moves = {
			MOVE_ENCORE,
			MOVE_COUNTER,
			MOVE_MIRROR_COAT,
			MOVE_DESTINY_BOND
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_MILD,
	},
	{
		.species = SPECIES_RHYDON,
		.heldItem = BATTLE_TOWER_ITEM_QUICK_CLAW,
		.teamFlags = 0x71,
		.moves = {
			MOVE_EARTHQUAKE,
			MOVE_MEGAHORN,
			MOVE_BRICK_BREAK,
			MOVE_HORN_DRILL
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_GENTLE,
	},
	{
		.species = SPECIES_GLALIE,
		.heldItem = BATTLE_TOWER_ITEM_SALAC_BERRY,
		.teamFlags = 0x31,
		.moves = {
			MOVE_CRUNCH,
			MOVE_BLIZZARD,
			MOVE_HAIL,
			MOVE_SHEER_COLD
		},
		.evSpread = F_EV_SPREAD_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_BASHFUL,
	},
	{
		.species = SPECIES_SCEPTILE,
		.heldItem = BATTLE_TOWER_ITEM_SCOPE_LENS,
		.teamFlags = 0x8C,
		.moves = {
			MOVE_LEAF_BLADE,
			MOVE_EARTHQUAKE,
			MOVE_DRAGON_CLAW,
			MOVE_CRUNCH
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_DEFENSE,
		.nature = NATURE_QUIET,
	},
	{
		.species = SPECIES_BLAZIKEN,
		.heldItem = BATTLE_TOWER_ITEM_SALAC_BERRY,
		.teamFlags = 0x8C,
		.moves = {
			MOVE_BLAZE_KICK,
			MOVE_COUNTER,
			MOVE_ENDURE,
			MOVE_REVERSAL
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED | F_EV_SPREAD_HP,
		.nature = NATURE_DOCILE,
	},
	{
		.species = SPECIES_SWAMPERT,
		.heldItem = BATTLE_TOWER_ITEM_SHELL_BELL,
		.teamFlags = 0x8C,
		.moves = {
			MOVE_SURF,
			MOVE_EARTHQUAKE,
			MOVE_MIRROR_COAT,
			MOVE_BLIZZARD
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_CAREFUL,
	},
	{
		.species = SPECIES_GARDEVOIR,
		.heldItem = BATTLE_TOWER_ITEM_SALAC_BERRY,
		.teamFlags = 0x1A,
		.moves = {
			MOVE_PSYCHIC,
			MOVE_THUNDERBOLT,
			MOVE_DESTINY_BOND,
			MOVE_SNATCH
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED | F_EV_SPREAD_DEFENSE,
		.nature = NATURE_BRAVE,
	},
	{
		.species = SPECIES_BRELOOM,
		.heldItem = BATTLE_TOWER_ITEM_LUM_BERRY,
		.teamFlags = 0x15,
		.moves = {
			MOVE_SPORE,
			MOVE_FOCUS_PUNCH,
			MOVE_MACH_PUNCH,
			MOVE_ATTRACT
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_ATTACK,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_ALAKAZAM,
		.heldItem = BATTLE_TOWER_ITEM_BRIGHT_POWDER,
		.teamFlags = 0x58,
		.moves = {
			MOVE_PSYCHIC,
			MOVE_FIRE_PUNCH,
			MOVE_ICE_PUNCH,
			MOVE_RECOVER
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED,
		.nature = NATURE_HASTY,
	},
	{
		.species = SPECIES_HARIYAMA,
		.heldItem = BATTLE_TOWER_ITEM_SCOPE_LENS,
		.teamFlags = 0x15,
		.moves = {
			MOVE_CROSS_CHOP,
			MOVE_EARTHQUAKE,
			MOVE_FACADE,
			MOVE_FAKE_OUT
		},
		.evSpread = F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_GENTLE,
	},
	{
		.species = SPECIES_GYARADOS,
		.heldItem = BATTLE_TOWER_ITEM_SHELL_BELL,
		.teamFlags = 0x55,
		.moves = {
			MOVE_HYPER_BEAM,
			MOVE_EARTHQUAKE,
			MOVE_SURF,
			MOVE_ICE_BEAM
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_ATTACK,
		.nature = NATURE_BOLD,
	},
	{
		.species = SPECIES_CROBAT,
		.heldItem = BATTLE_TOWER_ITEM_BRIGHT_POWDER,
		.teamFlags = 0x58,
		.moves = {
			MOVE_SLUDGE_BOMB,
			MOVE_CONFUSE_RAY,
			MOVE_AIR_CUTTER,
			MOVE_DOUBLE_TEAM
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_SPEED | F_EV_SPREAD_ATTACK,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_MACHAMP,
		.heldItem = BATTLE_TOWER_ITEM_SCOPE_LENS,
		.teamFlags = 0x5D,
		.moves = {
			MOVE_CROSS_CHOP,
			MOVE_FLAMETHROWER,
			MOVE_EARTHQUAKE,
			MOVE_ROCK_SLIDE
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_MANECTRIC,
		.heldItem = BATTLE_TOWER_ITEM_LUM_BERRY,
		.teamFlags = 0x1A,
		.moves = {
			MOVE_THUNDERBOLT,
			MOVE_THUNDER_WAVE,
			MOVE_ROAR,
			MOVE_CRUNCH
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED,
		.nature = NATURE_QUIET,
	},
	{
		.species = SPECIES_ELECTRODE,
		.heldItem = BATTLE_TOWER_ITEM_LUM_BERRY,
		.teamFlags = 0x60,
		.moves = {
			MOVE_THUNDERBOLT,
			MOVE_PROTECT,
			MOVE_MIRROR_COAT,
			MOVE_EXPLOSION
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_DEFENSE | F_EV_SPREAD_ATTACK,
		.nature = NATURE_BASHFUL,
	},
	{
		.species = SPECIES_MUK,
		.heldItem = BATTLE_TOWER_ITEM_QUICK_CLAW,
		.teamFlags = 0x64,
		.moves = {
			MOVE_SLUDGE_BOMB,
			MOVE_FLAMETHROWER,
			MOVE_THUNDERBOLT,
			MOVE_EXPLOSION
		},
		.evSpread = F_EV_SPREAD_DEFENSE | F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_GENTLE,
	},
	{
		.species = SPECIES_FLYGON,
		.heldItem = BATTLE_TOWER_ITEM_LUM_BERRY,
		.teamFlags = 0x1C,
		.moves = {
			MOVE_DRAGON_CLAW,
			MOVE_EARTHQUAKE,
			MOVE_FLAMETHROWER,
			MOVE_CRUNCH
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED | F_EV_SPREAD_ATTACK,
		.nature = NATURE_TIMID,
	},
	{
		.species = SPECIES_STARMIE,
		.heldItem = BATTLE_TOWER_ITEM_LUM_BERRY,
		.teamFlags = 0x5C,
		.moves = {
			MOVE_SURF,
			MOVE_THUNDERBOLT,
			MOVE_RECOVER,
			MOVE_CONFUSE_RAY
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED | F_EV_SPREAD_HP,
		.nature = NATURE_QUIET,
	},
	{
		.species = SPECIES_NINETALES,
		.heldItem = BATTLE_TOWER_ITEM_LUM_BERRY,
		.teamFlags = 0x4A,
		.moves = {
			MOVE_CONFUSE_RAY,
			MOVE_TOXIC,
			MOVE_FIRE_SPIN,
			MOVE_HEAT_WAVE
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED,
		.nature = NATURE_QUIET,
	},
	{
		.species = SPECIES_RAICHU,
		.heldItem = BATTLE_TOWER_ITEM_FOCUS_BAND,
		.teamFlags = 0x5A,
		.moves = {
			MOVE_THUNDERBOLT,
			MOVE_THUNDER_WAVE,
			MOVE_REVERSAL,
			MOVE_IRON_TAIL
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED | F_EV_SPREAD_DEFENSE,
		.nature = NATURE_TIMID,
	},
	{
		.species = SPECIES_GOLDUCK,
		.heldItem = BATTLE_TOWER_ITEM_LIECHI_BERRY,
		.teamFlags = 0x55,
		.moves = {
			MOVE_SURF,
			MOVE_CROSS_CHOP,
			MOVE_ICE_BEAM,
			MOVE_DIG
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_ATTACK,
		.nature = NATURE_JOLLY,
	},
	{
		.species = SPECIES_HERACROSS,
		.heldItem = BATTLE_TOWER_ITEM_SALAC_BERRY,
		.teamFlags = 0x5D,
		.moves = {
			MOVE_MEGAHORN,
			MOVE_EARTHQUAKE,
			MOVE_ENDURE,
			MOVE_REVERSAL
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_ATTACK,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_WALREIN,
		.heldItem = BATTLE_TOWER_ITEM_QUICK_CLAW,
		.teamFlags = 0x26,
		.moves = {
			MOVE_SURF,
			MOVE_ICE_BEAM,
			MOVE_EARTHQUAKE,
			MOVE_SHEER_COLD
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_DEFENSE | F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_CAREFUL,
	},
	{
		.species = SPECIES_KINGDRA,
		.heldItem = BATTLE_TOWER_ITEM_CHESTO_BERRY,
		.teamFlags = 0x5B,
		.moves = {
			MOVE_SURF,
			MOVE_ICE_BEAM,
			MOVE_DRAGON_BREATH,
			MOVE_REST
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_SP_ATTACK,
		.nature = NATURE_QUIET,
	},
	{
		.species = SPECIES_SALAMENCE,
		.heldItem = BATTLE_TOWER_ITEM_LUM_BERRY,
		.teamFlags = 0x0D,
		.moves = {
			MOVE_DRAGON_CLAW,
			MOVE_EARTHQUAKE,
			MOVE_CRUNCH,
			MOVE_FIRE_BLAST
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED,
		.nature = NATURE_NAUGHTY,
	},
	{
		.species = SPECIES_METAGROSS,
		.heldItem = BATTLE_TOWER_ITEM_SALAC_BERRY,
		.teamFlags = 0x3D,
		.moves = {
			MOVE_METEOR_MASH,
			MOVE_PSYCHIC,
			MOVE_EARTHQUAKE,
			MOVE_ROCK_TOMB
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_ATTACK,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_REGIROCK,
		.heldItem = BATTLE_TOWER_ITEM_BRIGHT_POWDER,
		.teamFlags = 0x3C,
		.moves = {
			MOVE_EARTHQUAKE,
			MOVE_ANCIENT_POWER,
			MOVE_THUNDERBOLT,
			MOVE_EXPLOSION
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_GENTLE,
	},
	{
		.species = SPECIES_REGICE,
		.heldItem = BATTLE_TOWER_ITEM_LAX_INCENSE,
		.teamFlags = 0x3C,
		.moves = {
			MOVE_ICE_BEAM,
			MOVE_THUNDERBOLT,
			MOVE_EARTHQUAKE,
			MOVE_EXPLOSION
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_CAREFUL,
	},
	{
		.species = SPECIES_REGISTEEL,
		.heldItem = BATTLE_TOWER_ITEM_QUICK_CLAW,
		.teamFlags = 0x3C,
		.moves = {
			MOVE_METAL_CLAW,
			MOVE_EARTHQUAKE,
			MOVE_THUNDERBOLT,
			MOVE_EXPLOSION
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_GENTLE,
	},
	{
		.species = SPECIES_LATIAS,
		.heldItem = BATTLE_TOWER_ITEM_LUM_BERRY,
		.teamFlags = 0x0E,
		.moves = {
			MOVE_MIST_BALL,
			MOVE_THUNDERBOLT,
			MOVE_RECOVER,
			MOVE_DRAGON_CLAW
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED,
		.nature = NATURE_QUIET,
	},
	{
		.species = SPECIES_LATIOS,
		.heldItem = BATTLE_TOWER_ITEM_PETAYA_BERRY,
		.teamFlags = 0x0D,
		.moves = {
			MOVE_LUSTER_PURGE,
			MOVE_THUNDERBOLT,
			MOVE_RECOVER,
			MOVE_DRAGON_CLAW
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED,
		.nature = NATURE_QUIET,
	},
	{
		.species = SPECIES_MILOTIC,
		.heldItem = BATTLE_TOWER_ITEM_LEFTOVERS,
		.teamFlags = 0x1A,
		.moves = {
			MOVE_SURF,
			MOVE_TOXIC,
			MOVE_RECOVER,
			MOVE_MIRROR_COAT
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED | F_EV_SPREAD_HP,
		.nature = NATURE_BRAVE,
	},
	{
		.species = SPECIES_SLAKING,
		.heldItem = BATTLE_TOWER_ITEM_LUM_BERRY,
		.teamFlags = 0x15,
		.moves = {
			MOVE_YAWN,
			MOVE_FOCUS_PUNCH,
			MOVE_COUNTER,
			MOVE_SLACK_OFF
		},
		.evSpread = F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_DOCILE,
	},
	{
		.species = SPECIES_SCEPTILE,
		.heldItem = BATTLE_TOWER_ITEM_LEFTOVERS,
		.teamFlags = 0x8C,
		.moves = {
			MOVE_GIGA_DRAIN,
			MOVE_DOUBLE_TEAM,
			MOVE_LEECH_SEED,
			MOVE_ATTRACT
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_QUIET,
	},
	{
		.species = SPECIES_BLAZIKEN,
		.heldItem = BATTLE_TOWER_ITEM_SCOPE_LENS,
		.teamFlags = 0x8C,
		.moves = {
			MOVE_BLAZE_KICK,
			MOVE_EARTHQUAKE,
			MOVE_ROCK_SLIDE,
			MOVE_QUICK_ATTACK
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED | F_EV_SPREAD_ATTACK,
		.nature = NATURE_DOCILE,
	},
	{
		.species = SPECIES_SWAMPERT,
		.heldItem = BATTLE_TOWER_ITEM_LEFTOVERS,
		.teamFlags = 0x8C,
		.moves = {
			MOVE_MUDDY_WATER,
			MOVE_MUD_SHOT,
			MOVE_MIRROR_COAT,
			MOVE_ICE_BEAM
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_SP_ATTACK,
		.nature = NATURE_CAREFUL,
	},
	{
		.species = SPECIES_GARDEVOIR,
		.heldItem = BATTLE_TOWER_ITEM_SALAC_BERRY,
		.teamFlags = 0x0A,
		.moves = {
			MOVE_PSYCHIC,
			MOVE_THUNDERBOLT,
			MOVE_HYPNOSIS,
			MOVE_DREAM_EATER
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_RELAXED,
	},
	{
		.species = SPECIES_BRELOOM,
		.heldItem = BATTLE_TOWER_ITEM_SALAC_BERRY,
		.teamFlags = 0x05,
		.moves = {
			MOVE_SPORE,
			MOVE_COUNTER,
			MOVE_SKY_UPPERCUT,
			MOVE_GIGA_DRAIN
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_DOCILE,
	},
	{
		.species = SPECIES_ALAKAZAM,
		.heldItem = BATTLE_TOWER_ITEM_BRIGHT_POWDER,
		.teamFlags = 0x58,
		.moves = {
			MOVE_PSYCHIC,
			MOVE_THUNDER_PUNCH,
			MOVE_FIRE_PUNCH,
			MOVE_RECOVER
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_DEFENSE,
		.nature = NATURE_HASTY,
	},
	{
		.species = SPECIES_HARIYAMA,
		.heldItem = BATTLE_TOWER_ITEM_FOCUS_BAND,
		.teamFlags = 0x04,
		.moves = {
			MOVE_CROSS_CHOP,
			MOVE_COUNTER,
			MOVE_ENDURE,
			MOVE_REVERSAL
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_GENTLE,
	},
	{
		.species = SPECIES_GYARADOS,
		.heldItem = BATTLE_TOWER_ITEM_SHELL_BELL,
		.teamFlags = 0x44,
		.moves = {
			MOVE_HYPER_BEAM,
			MOVE_THUNDERBOLT,
			MOVE_EARTHQUAKE,
			MOVE_ICE_BEAM
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_ATTACK,
		.nature = NATURE_BOLD,
	},
	{
		.species = SPECIES_CROBAT,
		.heldItem = BATTLE_TOWER_ITEM_BRIGHT_POWDER,
		.teamFlags = 0x48,
		.moves = {
			MOVE_TOXIC,
			MOVE_CONFUSE_RAY,
			MOVE_ATTRACT,
			MOVE_FLY
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_SPEED,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_MACHAMP,
		.heldItem = BATTLE_TOWER_ITEM_SCOPE_LENS,
		.teamFlags = 0x5D,
		.moves = {
			MOVE_CROSS_CHOP,
			MOVE_COUNTER,
			MOVE_EARTHQUAKE,
			MOVE_FACADE
		},
		.evSpread = F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_MANECTRIC,
		.heldItem = BATTLE_TOWER_ITEM_PETAYA_BERRY,
		.teamFlags = 0x0A,
		.moves = {
			MOVE_THUNDER,
			MOVE_THUNDER_WAVE,
			MOVE_QUICK_ATTACK,
			MOVE_CRUNCH
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED,
		.nature = NATURE_QUIET,
	},
	{
		.species = SPECIES_ELECTRODE,
		.heldItem = BATTLE_TOWER_ITEM_SALAC_BERRY,
		.teamFlags = 0x60,
		.moves = {
			MOVE_THUNDERBOLT,
			MOVE_LIGHT_SCREEN,
			MOVE_MIRROR_COAT,
			MOVE_EXPLOSION
		},
		.evSpread = F_EV_SPREAD_DEFENSE | F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_BASHFUL,
	},
	{
		.species = SPECIES_MUK,
		.heldItem = BATTLE_TOWER_ITEM_QUICK_CLAW,
		.teamFlags = 0x64,
		.moves = {
			MOVE_SLUDGE_BOMB,
			MOVE_GIGA_DRAIN,
			MOVE_FLAMETHROWER,
			MOVE_EXPLOSION
		},
		.evSpread = F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_GENTLE,
	},
	{
		.species = SPECIES_FLYGON,
		.heldItem = BATTLE_TOWER_ITEM_SHELL_BELL,
		.teamFlags = 0x1C,
		.moves = {
			MOVE_DRAGON_CLAW,
			MOVE_EARTHQUAKE,
			MOVE_IRON_TAIL,
			MOVE_CRUNCH
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_ATTACK,
		.nature = NATURE_TIMID,
	},
	{
		.species = SPECIES_STARMIE,
		.heldItem = BATTLE_TOWER_ITEM_APICOT_BERRY,
		.teamFlags = 0x5C,
		.moves = {
			MOVE_BLIZZARD,
			MOVE_THUNDERBOLT,
			MOVE_PSYCHIC,
			MOVE_RECOVER
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED,
		.nature = NATURE_QUIET,
	},
	{
		.species = SPECIES_DODRIO,
		.heldItem = BATTLE_TOWER_ITEM_LIECHI_BERRY,
		.teamFlags = 0x5A,
		.moves = {
			MOVE_DRILL_PECK,
			MOVE_TRI_ATTACK,
			MOVE_AGILITY,
			MOVE_FACADE
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_ATTACK,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_RAICHU,
		.heldItem = BATTLE_TOWER_ITEM_PETAYA_BERRY,
		.teamFlags = 0x4A,
		.moves = {
			MOVE_THUNDERBOLT,
			MOVE_THUNDER_WAVE,
			MOVE_ATTRACT,
			MOVE_FOCUS_PUNCH
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED | F_EV_SPREAD_DEFENSE,
		.nature = NATURE_TIMID,
	},
	{
		.species = SPECIES_GOLDUCK,
		.heldItem = BATTLE_TOWER_ITEM_PETAYA_BERRY,
		.teamFlags = 0x45,
		.moves = {
			MOVE_HYDRO_PUMP,
			MOVE_CROSS_CHOP,
			MOVE_BLIZZARD,
			MOVE_ATTRACT
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED | F_EV_SPREAD_ATTACK,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_HERACROSS,
		.heldItem = BATTLE_TOWER_ITEM_LIECHI_BERRY,
		.teamFlags = 0x5D,
		.moves = {
			MOVE_MEGAHORN,
			MOVE_EARTHQUAKE,
			MOVE_COUNTER,
			MOVE_REVERSAL
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_ATTACK,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_WALREIN,
		.heldItem = BATTLE_TOWER_ITEM_LEFTOVERS,
		.teamFlags = 0x26,
		.moves = {
			MOVE_SURF,
			MOVE_BLIZZARD,
			MOVE_ROCK_SLIDE,
			MOVE_SHEER_COLD
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_CAREFUL,
	},
	{
		.species = SPECIES_KINGDRA,
		.heldItem = BATTLE_TOWER_ITEM_LEFTOVERS,
		.teamFlags = 0x5C,
		.moves = {
			MOVE_HYDRO_PUMP,
			MOVE_ICE_BEAM,
			MOVE_DRAGON_BREATH,
			MOVE_ATTRACT
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_QUIET,
	},
	{
		.species = SPECIES_SALAMENCE,
		.heldItem = BATTLE_TOWER_ITEM_KINGS_ROCK,
		.teamFlags = 0x1D,
		.moves = {
			MOVE_DRAGON_CLAW,
			MOVE_EARTHQUAKE,
			MOVE_CRUNCH,
			MOVE_ROCK_TOMB
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_ATTACK,
		.nature = NATURE_RELAXED,
	},
	{
		.species = SPECIES_METAGROSS,
		.heldItem = BATTLE_TOWER_ITEM_QUICK_CLAW,
		.teamFlags = 0x3D,
		.moves = {
			MOVE_METEOR_MASH,
			MOVE_PSYCHIC,
			MOVE_EARTHQUAKE,
			MOVE_SHADOW_BALL
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_ATTACK,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_REGIROCK,
		.heldItem = BATTLE_TOWER_ITEM_QUICK_CLAW,
		.teamFlags = 0x3C,
		.moves = {
			MOVE_EARTHQUAKE,
			MOVE_THUNDERBOLT,
			MOVE_FOCUS_PUNCH,
			MOVE_EXPLOSION
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_GENTLE,
	},
	{
		.species = SPECIES_REGICE,
		.heldItem = BATTLE_TOWER_ITEM_BRIGHT_POWDER,
		.teamFlags = 0x3C,
		.moves = {
			MOVE_ICE_BEAM,
			MOVE_THUNDERBOLT,
			MOVE_HAIL,
			MOVE_EXPLOSION
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_DEFENSE,
		.nature = NATURE_CAREFUL,
	},
	{
		.species = SPECIES_REGISTEEL,
		.heldItem = BATTLE_TOWER_ITEM_SALAC_BERRY,
		.teamFlags = 0x3C,
		.moves = {
			MOVE_METAL_CLAW,
			MOVE_EARTHQUAKE,
			MOVE_ANCIENT_POWER,
			MOVE_EXPLOSION
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_DEFENSE | F_EV_SPREAD_ATTACK,
		.nature = NATURE_GENTLE,
	},
	{
		.species = SPECIES_LATIAS,
		.heldItem = BATTLE_TOWER_ITEM_BRIGHT_POWDER,
		.teamFlags = 0x1E,
		.moves = {
			MOVE_MIST_BALL,
			MOVE_ICE_BEAM,
			MOVE_RECOVER,
			MOVE_DRAGON_CLAW
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_QUIET,
	},
	{
		.species = SPECIES_LATIOS,
		.heldItem = BATTLE_TOWER_ITEM_LAX_INCENSE,
		.teamFlags = 0x1D,
		.moves = {
			MOVE_LUSTER_PURGE,
			MOVE_ICE_BEAM,
			MOVE_RECOVER,
			MOVE_DRAGON_CLAW
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_QUIET,
	},
	{
		.species = SPECIES_MILOTIC,
		.heldItem = BATTLE_TOWER_ITEM_PETAYA_BERRY,
		.teamFlags = 0x1A,
		.moves = {
			MOVE_HYDRO_PUMP,
			MOVE_ICE_BEAM,
			MOVE_RECOVER,
			MOVE_MIRROR_COAT
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_BRAVE,
	},
	{
		.species = SPECIES_SLAKING,
		.heldItem = BATTLE_TOWER_ITEM_LUM_BERRY,
		.teamFlags = 0x15,
		.moves = {
			MOVE_YAWN,
			MOVE_FOCUS_PUNCH,
			MOVE_COUNTER,
			MOVE_PURSUIT
		},
		.evSpread = F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_DOCILE,
	},
	{
		.species = SPECIES_SCEPTILE,
		.heldItem = BATTLE_TOWER_ITEM_PETAYA_BERRY,
		.teamFlags = 0x8C,
		.moves = {
			MOVE_LEAF_BLADE,
			MOVE_ROCK_TOMB,
			MOVE_DRAGON_CLAW,
			MOVE_CRUNCH
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_BLAZIKEN,
		.heldItem = BATTLE_TOWER_ITEM_GANLON_BERRY,
		.teamFlags = 0x8C,
		.moves = {
			MOVE_FOCUS_PUNCH,
			MOVE_COUNTER,
			MOVE_SWAGGER,
			MOVE_ROCK_TOMB
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_ATTACK,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_SWAMPERT,
		.heldItem = BATTLE_TOWER_ITEM_SHELL_BELL,
		.teamFlags = 0x8C,
		.moves = {
			MOVE_SURF,
			MOVE_ICE_BEAM,
			MOVE_ATTRACT,
			MOVE_REST
		},
		.evSpread = F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_CAREFUL,
	},
	{
		.species = SPECIES_GARDEVOIR,
		.heldItem = BATTLE_TOWER_ITEM_LAX_INCENSE,
		.teamFlags = 0x0A,
		.moves = {
			MOVE_PSYCHIC,
			MOVE_THUNDERBOLT,
			MOVE_ATTRACT,
			MOVE_WILL_O_WISP
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_BRELOOM,
		.heldItem = BATTLE_TOWER_ITEM_LUM_BERRY,
		.teamFlags = 0x05,
		.moves = {
			MOVE_SPORE,
			MOVE_FOCUS_PUNCH,
			MOVE_MACH_PUNCH,
			MOVE_COUNTER
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_SPEED | F_EV_SPREAD_ATTACK,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_ALAKAZAM,
		.heldItem = BATTLE_TOWER_ITEM_CHOICE_BAND,
		.teamFlags = 0x58,
		.moves = {
			MOVE_PSYCHIC,
			MOVE_TRICK,
			MOVE_RECOVER,
			MOVE_SNATCH
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_HASTY,
	},
	{
		.species = SPECIES_HARIYAMA,
		.heldItem = BATTLE_TOWER_ITEM_FOCUS_BAND,
		.teamFlags = 0x05,
		.moves = {
			MOVE_REVENGE,
			MOVE_COUNTER,
			MOVE_FOCUS_PUNCH,
			MOVE_REVERSAL
		},
		.evSpread = F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_GENTLE,
	},
	{
		.species = SPECIES_LUDICOLO,
		.heldItem = BATTLE_TOWER_ITEM_LEFTOVERS,
		.teamFlags = 0x0A,
		.moves = {
			MOVE_RAIN_DANCE,
			MOVE_LEECH_SEED,
			MOVE_GIGA_DRAIN,
			MOVE_DIVE
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_QUIET,
	},
	{
		.species = SPECIES_CROBAT,
		.heldItem = BATTLE_TOWER_ITEM_BRIGHT_POWDER,
		.teamFlags = 0x48,
		.moves = {
			MOVE_SLUDGE_BOMB,
			MOVE_CONFUSE_RAY,
			MOVE_SHADOW_BALL,
			MOVE_SNATCH
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_ATTACK,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_MACHAMP,
		.heldItem = BATTLE_TOWER_ITEM_SCOPE_LENS,
		.teamFlags = 0x5D,
		.moves = {
			MOVE_CROSS_CHOP,
			MOVE_FIRE_BLAST,
			MOVE_LOW_KICK,
			MOVE_ROCK_TOMB
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_ATTACK,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_MANECTRIC,
		.heldItem = BATTLE_TOWER_ITEM_LUM_BERRY,
		.teamFlags = 0x08,
		.moves = {
			MOVE_THUNDERBOLT,
			MOVE_THUNDER_WAVE,
			MOVE_ATTRACT,
			MOVE_CRUNCH
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED | F_EV_SPREAD_ATTACK,
		.nature = NATURE_QUIET,
	},
	{
		.species = SPECIES_ELECTRODE,
		.heldItem = BATTLE_TOWER_ITEM_LIECHI_BERRY,
		.teamFlags = 0x60,
		.moves = {
			MOVE_THUNDER,
			MOVE_SWIFT,
			MOVE_MIRROR_COAT,
			MOVE_EXPLOSION
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_DEFENSE,
		.nature = NATURE_BASHFUL,
	},
	{
		.species = SPECIES_MUK,
		.heldItem = BATTLE_TOWER_ITEM_SALAC_BERRY,
		.teamFlags = 0x64,
		.moves = {
			MOVE_SLUDGE_BOMB,
			MOVE_FLAMETHROWER,
			MOVE_THUNDERBOLT,
			MOVE_SHADOW_PUNCH
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_GENTLE,
	},
	{
		.species = SPECIES_FLYGON,
		.heldItem = BATTLE_TOWER_ITEM_LAX_INCENSE,
		.teamFlags = 0x0C,
		.moves = {
			MOVE_DRAGON_CLAW,
			MOVE_EARTHQUAKE,
			MOVE_FIRE_BLAST,
			MOVE_SANDSTORM
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED | F_EV_SPREAD_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_TIMID,
	},
	{
		.species = SPECIES_STARMIE,
		.heldItem = BATTLE_TOWER_ITEM_PETAYA_BERRY,
		.teamFlags = 0x4C,
		.moves = {
			MOVE_SURF,
			MOVE_THUNDERBOLT,
			MOVE_ICE_BEAM,
			MOVE_PSYCHIC
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED | F_EV_SPREAD_HP,
		.nature = NATURE_QUIET,
	},
	{
		.species = SPECIES_LUDICOLO,
		.heldItem = BATTLE_TOWER_ITEM_LEFTOVERS,
		.teamFlags = 0x4A,
		.moves = {
			MOVE_LEECH_SEED,
			MOVE_ATTRACT,
			MOVE_DOUBLE_TEAM,
			MOVE_PROTECT
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_QUIET,
	},
	{
		.species = SPECIES_SKARMORY,
		.heldItem = BATTLE_TOWER_ITEM_LEFTOVERS,
		.teamFlags = 0x4B,
		.moves = {
			MOVE_DRILL_PECK,
			MOVE_STEEL_WING,
			MOVE_ATTRACT,
			MOVE_PURSUIT
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_SPEED,
		.nature = NATURE_SASSY,
	},
	{
		.species = SPECIES_GOLDUCK,
		.heldItem = BATTLE_TOWER_ITEM_SCOPE_LENS,
		.teamFlags = 0x49,
		.moves = {
			MOVE_SURF,
			MOVE_PSYCHIC,
			MOVE_ICE_BEAM,
			MOVE_CROSS_CHOP
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_JOLLY,
	},
	{
		.species = SPECIES_HERACROSS,
		.heldItem = BATTLE_TOWER_ITEM_QUICK_CLAW,
		.teamFlags = 0x5D,
		.moves = {
			MOVE_MEGAHORN,
			MOVE_EARTHQUAKE,
			MOVE_FOCUS_PUNCH,
			MOVE_ROCK_TOMB
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_DEFENSE | F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_WALREIN,
		.heldItem = BATTLE_TOWER_ITEM_LEPPA_BERRY,
		.teamFlags = 0x26,
		.moves = {
			MOVE_SURF,
			MOVE_ICE_BEAM,
			MOVE_FISSURE,
			MOVE_SHEER_COLD
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_KINGDRA,
		.heldItem = BATTLE_TOWER_ITEM_SALAC_BERRY,
		.teamFlags = 0x5C,
		.moves = {
			MOVE_SURF,
			MOVE_BLIZZARD,
			MOVE_HYPER_BEAM,
			MOVE_FLAIL
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED,
		.nature = NATURE_BRAVE,
	},
	{
		.species = SPECIES_SALAMENCE,
		.heldItem = BATTLE_TOWER_ITEM_PETAYA_BERRY,
		.teamFlags = 0x1D,
		.moves = {
			MOVE_DRAGON_CLAW,
			MOVE_EARTHQUAKE,
			MOVE_FIRE_BLAST,
			MOVE_HYDRO_PUMP
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED,
		.nature = NATURE_NAUGHTY,
	},
	{
		.species = SPECIES_METAGROSS,
		.heldItem = BATTLE_TOWER_ITEM_LIECHI_BERRY,
		.teamFlags = 0x3D,
		.moves = {
			MOVE_METEOR_MASH,
			MOVE_PSYCHIC,
			MOVE_EARTHQUAKE,
			MOVE_HYPER_BEAM
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_SP_ATTACK,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_REGIROCK,
		.heldItem = BATTLE_TOWER_ITEM_SALAC_BERRY,
		.teamFlags = 0x3C,
		.moves = {
			MOVE_EARTHQUAKE,
			MOVE_THUNDERBOLT,
			MOVE_SUPERPOWER,
			MOVE_EXPLOSION
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_ATTACK,
		.nature = NATURE_GENTLE,
	},
	{
		.species = SPECIES_REGICE,
		.heldItem = BATTLE_TOWER_ITEM_LAX_INCENSE,
		.teamFlags = 0x3C,
		.moves = {
			MOVE_ICE_BEAM,
			MOVE_THUNDERBOLT,
			MOVE_ANCIENT_POWER,
			MOVE_EXPLOSION
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_DEFENSE | F_EV_SPREAD_ATTACK,
		.nature = NATURE_CAREFUL,
	},
	{
		.species = SPECIES_REGISTEEL,
		.heldItem = BATTLE_TOWER_ITEM_LEFTOVERS,
		.teamFlags = 0x3C,
		.moves = {
			MOVE_METAL_CLAW,
			MOVE_THUNDERBOLT,
			MOVE_HYPER_BEAM,
			MOVE_EXPLOSION
		},
		.evSpread = F_EV_SPREAD_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_GENTLE,
	},
	{
		.species = SPECIES_LATIAS,
		.heldItem = BATTLE_TOWER_ITEM_APICOT_BERRY,
		.teamFlags = 0x1E,
		.moves = {
			MOVE_MIST_BALL,
			MOVE_THUNDERBOLT,
			MOVE_EARTHQUAKE,
			MOVE_ICE_BEAM
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED | F_EV_SPREAD_ATTACK,
		.nature = NATURE_QUIET,
	},
	{
		.species = SPECIES_LATIOS,
		.heldItem = BATTLE_TOWER_ITEM_GANLON_BERRY,
		.teamFlags = 0x1D,
		.moves = {
			MOVE_LUSTER_PURGE,
			MOVE_THUNDERBOLT,
			MOVE_EARTHQUAKE,
			MOVE_ICE_BEAM
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED | F_EV_SPREAD_ATTACK,
		.nature = NATURE_QUIET,
	},
	{
		.species = SPECIES_MILOTIC,
		.heldItem = BATTLE_TOWER_ITEM_APICOT_BERRY,
		.teamFlags = 0x1A,
		.moves = {
			MOVE_SURF,
			MOVE_ICE_BEAM,
			MOVE_RECOVER,
			MOVE_ATTRACT
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_BRAVE,
	},
	{
		.species = SPECIES_ALTARIA,
		.heldItem = BATTLE_TOWER_ITEM_GANLON_BERRY,
		.teamFlags = 0x0A,
		.moves = {
			MOVE_DRAGON_CLAW,
			MOVE_ICE_BEAM,
			MOVE_SING,
			MOVE_FLAMETHROWER
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED | F_EV_SPREAD_DEFENSE,
		.nature = NATURE_QUIET,
	},
	{
		.species = SPECIES_SCEPTILE,
		.heldItem = BATTLE_TOWER_ITEM_BRIGHT_POWDER,
		.teamFlags = 0x9C,
		.moves = {
			MOVE_LEAF_BLADE,
			MOVE_DETECT,
			MOVE_DRAGON_CLAW,
			MOVE_CRUNCH
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_BLAZIKEN,
		.heldItem = BATTLE_TOWER_ITEM_SALAC_BERRY,
		.teamFlags = 0x9C,
		.moves = {
			MOVE_BLAZE_KICK,
			MOVE_SKY_UPPERCUT,
			MOVE_EARTHQUAKE,
			MOVE_ROCK_SLIDE
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_ATTACK,
		.nature = NATURE_DOCILE,
	},
	{
		.species = SPECIES_SWAMPERT,
		.heldItem = BATTLE_TOWER_ITEM_PETAYA_BERRY,
		.teamFlags = 0x9C,
		.moves = {
			MOVE_SURF,
			MOVE_EARTHQUAKE,
			MOVE_ICE_BEAM,
			MOVE_ROCK_TOMB
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_HP,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_SHEDINJA,
		.heldItem = BATTLE_TOWER_ITEM_BRIGHT_POWDER,
		.teamFlags = 0x20,
		.moves = {
			MOVE_CONFUSE_RAY,
			MOVE_SHADOW_BALL,
			MOVE_TOXIC,
			MOVE_GRUDGE
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_ATTACK,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_METAGROSS,
		.heldItem = BATTLE_TOWER_ITEM_LEFTOVERS,
		.teamFlags = 0x1D,
		.moves = {
			MOVE_METEOR_MASH,
			MOVE_EARTHQUAKE,
			MOVE_DOUBLE_TEAM,
			MOVE_PROTECT
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_DEFENSE | F_EV_SPREAD_HP,
		.nature = NATURE_NAIVE,
	},
	{
		.species = SPECIES_ALAKAZAM,
		.heldItem = BATTLE_TOWER_ITEM_LEFTOVERS,
		.teamFlags = 0x58,
		.moves = {
			MOVE_PSYCHIC,
			MOVE_THUNDER_PUNCH,
			MOVE_ICE_PUNCH,
			MOVE_FIRE_PUNCH
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED,
		.nature = NATURE_HASTY,
	},
	{
		.species = SPECIES_LATIAS,
		.heldItem = BATTLE_TOWER_ITEM_LEFTOVERS,
		.teamFlags = 0x1E,
		.moves = {
			MOVE_MIST_BALL,
			MOVE_THUNDERBOLT,
			MOVE_ICE_BEAM,
			MOVE_DRAGON_CLAW
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED,
		.nature = NATURE_QUIET,
	},
	{
		.species = SPECIES_LATIOS,
		.heldItem = BATTLE_TOWER_ITEM_SHELL_BELL,
		.teamFlags = 0x1D,
		.moves = {
			MOVE_LUSTER_PURGE,
			MOVE_THUNDERBOLT,
			MOVE_ICE_BEAM,
			MOVE_DRAGON_CLAW
		},
		.evSpread = F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_SPEED,
		.nature = NATURE_HARDY,
	},
	{
		.species = SPECIES_SALAMENCE,
		.heldItem = BATTLE_TOWER_ITEM_SHELL_BELL,
		.teamFlags = 0x1D,
		.moves = {
			MOVE_DRAGON_CLAW,
			MOVE_FLAMETHROWER,
			MOVE_EARTHQUAKE,
			MOVE_AERIAL_ACE
		},
		.evSpread = F_EV_SPREAD_SP_DEFENSE | F_EV_SPREAD_SP_ATTACK | F_EV_SPREAD_DEFENSE,
		.nature = NATURE_RELAXED,
	},
	{
		.species = SPECIES_MACHAMP,
		.heldItem = BATTLE_TOWER_ITEM_LIECHI_BERRY,
		.teamFlags = 0x5D,
		.moves = {
			MOVE_CROSS_CHOP,
			MOVE_EARTHQUAKE,
			MOVE_LOW_KICK,
			MOVE_ROCK_SLIDE
		},
		.evSpread = F_EV_SPREAD_SPEED | F_EV_SPREAD_ATTACK,
		.nature = NATURE_HARDY,
	},
};
// ===== END src/data/battle_tower/level_100_mons.h =====

static const u8 sMaleTrainerClasses[] =
{

};

static const u8 sFemaleTrainerClasses[] =
{

};

static const u8 sMaleTrainerGfx[] =
{

};

static const u8 sFemaleTrainerGfx[] =
{

};

const u16 gBattleTowerBannedSpecies[] = {
    SPECIES_MEW,
    SPECIES_MEWTWO,
    SPECIES_HO_OH,
    SPECIES_LUGIA,
    SPECIES_CELEBI,
    SPECIES_KYOGRE,
    SPECIES_GROUDON,
    SPECIES_RAYQUAZA,
    SPECIES_JIRACHI,
    SPECIES_DEOXYS,
    0xFFFF
};

static const u16 sShortStreakPrizes[] = {
    ITEM_HP_UP,
    ITEM_PROTEIN,
    ITEM_IRON,
    ITEM_CALCIUM,
    ITEM_CARBOS,
    ITEM_ZINC
};

static const u16 sLongStreakPrizes[] = {
    ITEM_BRIGHT_POWDER,
    ITEM_WHITE_HERB,
    ITEM_QUICK_CLAW,
    ITEM_LEFTOVERS,
    ITEM_MENTAL_HERB,
    ITEM_KINGS_ROCK,
    ITEM_FOCUS_BAND,
    ITEM_SCOPE_LENS,
    ITEM_CHOICE_BAND
};

void BattleTowerMapScript2(void)
{
    u8 count = 0;
    s32 levelType;

    for (levelType = 0; levelType < 2; levelType++)
    {
        switch (gSaveBlock2Ptr->battleTower.var_4AE[levelType])
        {
        default:
        case 0:
            ResetBattleTowerStreak(levelType);
            if (count == 0)
                VarSet(VAR_TEMP_0, 5);
            break;
        case 1:
            ResetBattleTowerStreak(levelType);
            VarSet(VAR_TEMP_0, BTSPECIAL_RESULT_SAVE_SCUM);
            count++;
            break;
        case 3:
            break;
        case 4:
            VarSet(VAR_TEMP_0, BTSPECIAL_RESULT_WON7);
            count++;
            break;
        case 5:
            VarSet(VAR_TEMP_0, BTSPECIAL_RESULT_LOST);
            count++;
            break;
        case 6:
            break;
        case 2:
            VarSet(VAR_TEMP_0, BTSPECIAL_RESULT_QUICKSAVE);
            count++;
            break;
        }
    }
    if (gSaveBlock2Ptr->battleTower.var_4AE[0] == 3 && gSaveBlock2Ptr->battleTower.var_4AE[1] == 3)
        VarSet(VAR_TEMP_0, BTSPECIAL_RESULT_INACTIVE);
    ValidateBattleTowerRecordChecksums();
}

static void ResetBattleTowerStreak(u8 levelType)
{
    gSaveBlock2Ptr->battleTower.var_4AE[levelType] = 0;
    gSaveBlock2Ptr->battleTower.curChallengeBattleNum[levelType] = 1;
    gSaveBlock2Ptr->battleTower.curStreakChallengesNum[levelType] = 1;
}

static bool8 ShouldBattleEReaderTrainer(u8 levelType, u16 winStreak)
{
    u8 trainerTeamLevel;
    u8 monLevel;
    s32 i;
    u16 validPartySpecies[6];
    u16 validPartyHeldItems[6];
    u8 numValid;

    numValid = 0;

    ValidateEReaderTrainer();

    if (gSpecialVar_Result != 0 || gSaveBlock2Ptr->battleTower.ereaderTrainer.winStreak != winStreak)
        return FALSE;

    if (levelType != 0)
        trainerTeamLevel = 100;
    else
        trainerTeamLevel = 50;

    for (i = 0; i < 3; i++)
    {
        monLevel = gSaveBlock2Ptr->battleTower.ereaderTrainer.party[i].level;
        if (gSaveBlock2Ptr->battleTower.ereaderTrainer.party[i].level != trainerTeamLevel)
            return FALSE;

        CheckMonBattleTowerBanlist(
            gSaveBlock2Ptr->battleTower.ereaderTrainer.party[i].species,
            gSaveBlock2Ptr->battleTower.ereaderTrainer.party[i].heldItem,
            1,
            levelType,
            monLevel,
            validPartySpecies,
            validPartyHeldItems,
            &numValid);
    }

    return (numValid == 3);
}

static bool8 ChooseSpecialBattleTowerTrainer(void)
{
    s32 recordIndex, i;
    u8 battleTowerLevelType;
    u16 winStreak;
    bool8 retVal;
    s32 numCandidates;
    u32 trainerIds[5];

    numCandidates = 0;
    battleTowerLevelType = gSaveBlock2Ptr->battleTower.battleTowerLevelType;

    winStreak = GetCurrentBattleTowerWinStreak(battleTowerLevelType);
    if (ShouldBattleEReaderTrainer(battleTowerLevelType, winStreak))
    {
        gSaveBlock2Ptr->battleTower.battleTowerTrainerId = BATTLE_TOWER_EREADER_TRAINER_ID;
        retVal = TRUE;
    }
    else
    {
        // Check if one of the battle tower trainers from record mixing should be the next trainer.
        for (recordIndex = 0; recordIndex < 5; recordIndex++)
        {
            struct BattleTowerRecord *record = &gSaveBlock2Ptr->battleTower.records[recordIndex];
            u32 recordHasData = 0;
            u32 checksum = 0;

            for (i = 0; i < sizeof(struct BattleTowerRecord) / sizeof(u32) - 1; i++)
            {
                recordHasData |= ((u32 *) record)[i];
                checksum += ((u32 *) record)[i];
            }

            if (gSaveBlock2Ptr->battleTower.records[recordIndex].winStreak == winStreak
                && gSaveBlock2Ptr->battleTower.records[recordIndex].battleTowerLevelType == battleTowerLevelType
                && recordHasData
                && gSaveBlock2Ptr->battleTower.records[recordIndex].checksum == checksum)
            {
                trainerIds[numCandidates] = recordIndex;
                numCandidates++;
            }
        }

        if (numCandidates == 0)
        {
            retVal = FALSE;
        }
        else
        {
            gSaveBlock2Ptr->battleTower.battleTowerTrainerId =
                trainerIds[Random() % numCandidates] + BATTLE_TOWER_RECORD_MIXING_TRAINER_BASE_ID;
            retVal = TRUE;
        }
    }
    return retVal;
}

void ChooseNextBattleTowerTrainer(void)
{
    int i;
    u16 trainerId;
    bool8 levelType;

    levelType = gSaveBlock2Ptr->battleTower.battleTowerLevelType;
    if (ChooseSpecialBattleTowerTrainer())
    {
        SetBattleTowerTrainerGfxId(gSaveBlock2Ptr->battleTower.battleTowerTrainerId);
        gSaveBlock2Ptr->battleTower.battledTrainerIds[gSaveBlock2Ptr->battleTower.curChallengeBattleNum[levelType] - 1] = gSaveBlock2Ptr->battleTower.battleTowerTrainerId;
        return;
    }

    if (gSaveBlock2Ptr->battleTower.curStreakChallengesNum[levelType] <= 7)
    {
        if (gSaveBlock2Ptr->battleTower.curChallengeBattleNum[levelType] == 7)
        {
            do
            {
                trainerId = ((Random() & 0xFF) * 5) >> 7;
                trainerId += (gSaveBlock2Ptr->battleTower.curStreakChallengesNum[levelType] - 1) * 10 + 20;

                // Ensure trainer wasn't previously fought in this challenge.
                for (i = 0; i < gSaveBlock2Ptr->battleTower.curChallengeBattleNum[levelType] - 1 && gSaveBlock2Ptr->battleTower.battledTrainerIds[i] != trainerId; i++);
            }
            while (i != gSaveBlock2Ptr->battleTower.curChallengeBattleNum[levelType] - 1);
            gSaveBlock2Ptr->battleTower.battleTowerTrainerId = trainerId;
        }
        else
        {
            do
            {
                trainerId = (((Random() & 0xFF) * 5) >> 6);
                trainerId += (gSaveBlock2Ptr->battleTower.curStreakChallengesNum[levelType] - 1) * 10;

                // Ensure trainer wasn't previously fought in this challenge.
                for (i = 0; i < gSaveBlock2Ptr->battleTower.curChallengeBattleNum[levelType] - 1 && gSaveBlock2Ptr->battleTower.battledTrainerIds[i] != trainerId; i++);
            }
            while (i != gSaveBlock2Ptr->battleTower.curChallengeBattleNum[levelType] - 1);
            gSaveBlock2Ptr->battleTower.battleTowerTrainerId = trainerId;
        }
    }
    else
    {
        do
        {
            trainerId = (((Random() & 0xFF) * 30) >> 8) + 70;

            // Ensure trainer wasn't previously fought in this challenge.
            for (i = 0; i < gSaveBlock2Ptr->battleTower.curChallengeBattleNum[levelType] - 1 && gSaveBlock2Ptr->battleTower.battledTrainerIds[i] != trainerId; i++);
        }
        while (i != gSaveBlock2Ptr->battleTower.curChallengeBattleNum[levelType] - 1);
        gSaveBlock2Ptr->battleTower.battleTowerTrainerId = trainerId;
    }

    SetBattleTowerTrainerGfxId(gSaveBlock2Ptr->battleTower.battleTowerTrainerId);
    // Don't bother saving this trainer, since it's the last one in the challenge.
    if (gSaveBlock2Ptr->battleTower.curChallengeBattleNum[levelType] < 7)
        gSaveBlock2Ptr->battleTower.battledTrainerIds[gSaveBlock2Ptr->battleTower.curChallengeBattleNum[levelType] - 1] = gSaveBlock2Ptr->battleTower.battleTowerTrainerId;
}

static void SetBattleTowerTrainerGfxId(u8 trainerClass)
{
    VarSet(VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_YOUNGSTER);
}

void SetEReaderTrainerGfxId(void)
{
    SetBattleTowerTrainerGfxId(BATTLE_TOWER_EREADER_TRAINER_ID);
}

// Unreferenced; formerly used by Record Mixing in R/S
static void UpdateOrInsertReceivedBattleTowerRecord(struct BattleTowerRecord * record0)
{
    s32 i;
    s32 j;
    s32 k;
    s32 l = 0;
    struct BattleTowerRecord * record = record0;

    u16 winStreaks[6];
    u16 indices[6];

    for (i = 0; i < 5; i++)
    {
        k = 0;
        for (j = 0; j < 4; j++)
        {
            if (gSaveBlock2Ptr->battleTower.records[i].trainerId[j] != record->trainerId[j])
                break;
        }
        if (j == 4)
        {
            for (k = 0; k < 7; k++)
            {
                if (gSaveBlock2Ptr->battleTower.records[i].name[j] != record->name[j])
                    break;
                if (record->name[j] == EOS)
                {
                    k = 7;
                    break;
                }
            }
        }
        if (k == 7)
            break;
    }

    if (i < 5)
    {
        gSaveBlock2Ptr->battleTower.records[i] = *record;
        return;
    }

    for (i = 0; i < 5; i++)
    {
        if (gSaveBlock2Ptr->battleTower.records[i].winStreak == 0)
            break;
    }

    if (i < 5)
    {
        gSaveBlock2Ptr->battleTower.records[i] = *record;
        return;
    }

    winStreaks[0] = gSaveBlock2Ptr->battleTower.records[0].winStreak;
    indices[0] = 0;
    l++;

    for (i = 1; i < 5; i++)
    {
        for (j = 0; j < l; j++)
        {
            if (gSaveBlock2Ptr->battleTower.records[i].winStreak < winStreaks[j])
            {
                j = 0;
                l = 1;
                winStreaks[0] = gSaveBlock2Ptr->battleTower.records[i].winStreak;
                indices[0] = i;
                break;
            }
            if (gSaveBlock2Ptr->battleTower.records[i].winStreak > winStreaks[j])
                break;
        }
        if (j == l)
        {
            winStreaks[l] = gSaveBlock2Ptr->battleTower.records[i].winStreak;
            indices[l] = i;
            l++;
        }
    }
    i = Random() % l;
    gSaveBlock2Ptr->battleTower.records[indices[i]] = *record;
}

u8 GetBattleTowerTrainerFrontSpriteId(void)
{
    if (gSaveBlock2Ptr->battleTower.battleTowerTrainerId == BATTLE_TOWER_EREADER_TRAINER_ID)
    {
        return gFacilityClassToPicIndex[gSaveBlock2Ptr->battleTower.ereaderTrainer.trainerClass];
    }
    else if (gSaveBlock2Ptr->battleTower.battleTowerTrainerId < BATTLE_TOWER_RECORD_MIXING_TRAINER_BASE_ID)
    {
        return gFacilityClassToPicIndex[sBattleTowerTrainers[gSaveBlock2Ptr->battleTower.battleTowerTrainerId].trainerClass];
    }
    else
    {
        return gFacilityClassToPicIndex[gSaveBlock2Ptr->battleTower.records[gSaveBlock2Ptr->battleTower.battleTowerTrainerId - BATTLE_TOWER_RECORD_MIXING_TRAINER_BASE_ID].trainerClass];
    }
}

u8 GetBattleTowerTrainerClassNameId(void)
{
    if (gSaveBlock2Ptr->battleTower.battleTowerTrainerId == BATTLE_TOWER_EREADER_TRAINER_ID)
    {
        return gFacilityClassToTrainerClass[gSaveBlock2Ptr->battleTower.ereaderTrainer.trainerClass];
    }
    else if (gSaveBlock2Ptr->battleTower.battleTowerTrainerId >= BATTLE_TOWER_RECORD_MIXING_TRAINER_BASE_ID)
    {
        return gFacilityClassToTrainerClass[gSaveBlock2Ptr->battleTower.records[gSaveBlock2Ptr->battleTower.battleTowerTrainerId - BATTLE_TOWER_RECORD_MIXING_TRAINER_BASE_ID].trainerClass];
    }
    else
    {
        return gFacilityClassToTrainerClass[sBattleTowerTrainers[gSaveBlock2Ptr->battleTower.battleTowerTrainerId].trainerClass];
    }
}

void GetBattleTowerTrainerName(u8 *dest)
{
    s32 i;
    if (gSaveBlock2Ptr->battleTower.battleTowerTrainerId == BATTLE_TOWER_EREADER_TRAINER_ID)
    {
        for (i = 0; i < 7; i++)
            dest[i] = gSaveBlock2Ptr->battleTower.ereaderTrainer.name[i];
    }
    else if (gSaveBlock2Ptr->battleTower.battleTowerTrainerId < BATTLE_TOWER_RECORD_MIXING_TRAINER_BASE_ID)
    {
        for (i = 0; i < 3; i++)
            dest[i] = sBattleTowerTrainers[gSaveBlock2Ptr->battleTower.battleTowerTrainerId].name[i];
    }
    else
    {
        for (i = 0; i < 7; i++)
            dest[i] = gSaveBlock2Ptr->battleTower.records[gSaveBlock2Ptr->battleTower.battleTowerTrainerId - BATTLE_TOWER_RECORD_MIXING_TRAINER_BASE_ID].name[i];
    }
    dest[i] = EOS;
}

static void FillBattleTowerTrainerParty(void)
{
    s32 partyIndex;
    s32 i;
    u16 chosenMonIndices[3];
    u8 friendship;
    u8 level;
    u8 fixedIV;
    u8 battleMonsOffset;
    u8 monPoolSize;
    u8 teamFlags;
    const struct BattleTowerPokemonTemplate *battleTowerMons;

    battleMonsOffset = 0;
    monPoolSize = 60;
    friendship = 255;

    ZeroEnemyPartyMons();

    // Different trainers have access to different sets of pokemon to use in battle.
    // The pokemon later in gBattleTowerLevel100Mons or gBattleTowerLevel50Mons are
    // stronger. Additionally, the later trainers' pokemon are granted higher IVs.
    if (gSaveBlock2Ptr->battleTower.battleTowerTrainerId < 20)
    {
        fixedIV = 6;
    }
    else if (gSaveBlock2Ptr->battleTower.battleTowerTrainerId < 30)
    {
        fixedIV = 9;
        battleMonsOffset = 30;
    }
    else if (gSaveBlock2Ptr->battleTower.battleTowerTrainerId < 40)
    {
        fixedIV = 12;
        battleMonsOffset = 60;
    }
    else if (gSaveBlock2Ptr->battleTower.battleTowerTrainerId < 50)
    {
        fixedIV = 15;
        battleMonsOffset = 90;
    }
    else if (gSaveBlock2Ptr->battleTower.battleTowerTrainerId < 60)
    {
        fixedIV = 18;
        battleMonsOffset = 120;
    }
    else if (gSaveBlock2Ptr->battleTower.battleTowerTrainerId < 70)
    {
        fixedIV = 21;
        battleMonsOffset = 150;
    }
    else if (gSaveBlock2Ptr->battleTower.battleTowerTrainerId < 80)
    {
        fixedIV = 31;
        battleMonsOffset = 180;
    }
    else if (gSaveBlock2Ptr->battleTower.battleTowerTrainerId < BATTLE_TOWER_RECORD_MIXING_TRAINER_BASE_ID)
    {
        fixedIV = 31;
        battleMonsOffset = 200;
        monPoolSize = 100;
    }
    else if (gSaveBlock2Ptr->battleTower.battleTowerTrainerId == BATTLE_TOWER_EREADER_TRAINER_ID)
    {
        // Load E-Reader trainer's party.
        do
        {
            for (partyIndex = 0; partyIndex < 3; partyIndex++)
                CreateBattleTowerMon(&gEnemyParty[partyIndex], &gSaveBlock2Ptr->battleTower.ereaderTrainer.party[partyIndex]);
            return;
        } while (0);
    }
    else
    {
        // Load a battle tower record's party. (From record mixing)
        for (partyIndex = 0; partyIndex < 3; partyIndex++)
        {
            CreateBattleTowerMon(
                &gEnemyParty[partyIndex],
                &gSaveBlock2Ptr->battleTower.records[gSaveBlock2Ptr->battleTower.battleTowerTrainerId - BATTLE_TOWER_RECORD_MIXING_TRAINER_BASE_ID].party[partyIndex]);
        }
        return;
    }

    // Use the appropriate list of pokemon and level depending on the
    // current challenge type. (level 50 or level 100 challenge)
    if (gSaveBlock2Ptr->battleTower.battleTowerLevelType != 0)
    {
        battleTowerMons = gBattleTowerLevel100Mons;
        level = 100;
    }
    else
    {
        battleTowerMons = gBattleTowerLevel50Mons;
        level = 50;
    }

    teamFlags = sBattleTowerTrainers[gSaveBlock2Ptr->battleTower.battleTowerTrainerId].teamFlags;

    // Attempt to fill the trainer's party with random Pokemon until 3 have been
    // successfully chosen. The trainer's party may not have duplicate pokemon species
    // or duplicate held items. Each pokemon must have all of the trainer's team flags
    // set, as well.  If any of those conditions are not met, then the loop starts over
    // and another pokemon is chosen at random.
    partyIndex = 0;
    while (partyIndex != 3)
    {
        // Pick a random pokemon index based on the number of pokemon available to choose from
        // and the starting offset in the battle tower pokemon array.
        s32 battleMonIndex = ((Random() & 0xFF) * monPoolSize) / 256 + battleMonsOffset;

        // Ensure the chosen pokemon has compatible team flags with the trainer.
        if (teamFlags == 0 || (battleTowerMons[battleMonIndex].teamFlags & teamFlags) == teamFlags)
        {
            // Ensure this pokemon species isn't a duplicate.
            for (i = 0; i < partyIndex; i++)
            {
                if (GetMonData(&gEnemyParty[i], MON_DATA_SPECIES, NULL) == battleTowerMons[battleMonIndex].species)
                    break;
            }

            if (i != partyIndex)
                continue;

            // Ensure this pokemon's held item isn't a duplicate.
            for (i = 0; i < partyIndex; i++)
            {
                if (GetMonData(&gEnemyParty[i], MON_DATA_HELD_ITEM, NULL) != ITEM_NONE
                    && GetMonData(&gEnemyParty[i], MON_DATA_HELD_ITEM, NULL) == sBattleTowerHeldItems[battleTowerMons[battleMonIndex].heldItem])
                    break;
            }

            if (i != partyIndex)
                continue;

            // Ensure this exact pokemon index isn't a duplicate. This check doesn't seem necessary
            // because the species and held items were already checked directly above. Perhaps this
            // is leftover code before the logic for duplicate species and held items was added.
            //for (i = 0; i < partyIndex && chosenMonIndices[i] != battleMonIndex; i++);
            for (i = 0; i < partyIndex; i++)
            {
                if (chosenMonIndices[i] == battleMonIndex)
                    break;
            }

            if (i != partyIndex)
                continue;

            chosenMonIndices[partyIndex] = battleMonIndex;

            // Place the chosen pokemon into the trainer's party.
            CreateMonWithEVSpread(
                &gEnemyParty[partyIndex],
                battleTowerMons[battleMonIndex].species,
                level,
                fixedIV,
                battleTowerMons[battleMonIndex].evSpread);

            // Give the chosen pokemon its specified moves.
            for (i = 0; i < 4; i++)
            {
                SetMonMoveSlot(&gEnemyParty[partyIndex], battleTowerMons[battleMonIndex].moves[i], i);
                if (battleTowerMons[battleMonIndex].moves[i] == MOVE_FRUSTRATION)
                    friendship = 0;  // MOVE_FRUSTRATION is more powerful the lower the pokemon's friendship is.
            }

            SetMonData(&gEnemyParty[partyIndex], MON_DATA_FRIENDSHIP, &friendship);
            SetMonData(&gEnemyParty[partyIndex], MON_DATA_HELD_ITEM, &sBattleTowerHeldItems[battleTowerMons[battleMonIndex].heldItem]);

            // The pokemon was successfully added to the trainer's party, so it's safe to move on to
            // the next party slot.
            partyIndex++;
        }
    }
}

static u8 AppendBattleTowerBannedSpeciesName(u16 species, u8 count)
{
    if (GetSetPokedexFlag(SpeciesToNationalPokedexNum(species), FLAG_GET_CAUGHT))
    {
        if (count == 0)
            StringAppend(gStringVar1, gText_BattleTowerBan_Space);
        count++;
        StringAppend(gStringVar1, gSpeciesNames[species]);
        switch (count)
        {
        case 2:
            StringAppend(gStringVar1, gText_BattleTowerBan_Newline2);
            break;
        case 5:
        case 8:
        case 11:
            StringAppend(gStringVar1, gText_BattleTowerBan_Newline1);
            break;
        default:
            StringAppend(gStringVar1, gText_BattleTowerBan_Space);
            break;
        }
    }
    return count;
}

static void CheckMonBattleTowerBanlist(u16 species, u16 heldItem, u16 hp, u8 battleTowerLevelType, u8 monLevel, u16 *validPartySpecies, u16 *validPartyHeldItems, u8 *numValid)
{
    s32 i;
    u32 counter = 0;

    if (species == SPECIES_EGG || species == SPECIES_NONE)
        return;

    while (1)
    {
        if (gBattleTowerBannedSpecies[counter] == 0xFFFF)
            break;

        if (gBattleTowerBannedSpecies[counter] == species)
            break;

        counter++;
    }

    if (gBattleTowerBannedSpecies[counter] != 0xFFFF)
        return;

    if (battleTowerLevelType == 0 && monLevel > 50)
        return;

    for (i = 0; i < *numValid && validPartySpecies[i] != species ; i++);
    if (i != *numValid)
        return;

    if (heldItem != ITEM_NONE)
    {
        for (i = 0; i < *numValid && validPartyHeldItems[i] != heldItem ; i++);
        if (i != *numValid)
            return;
    }

    validPartySpecies[*numValid] = species;
    validPartyHeldItems[*numValid] = heldItem;
    *numValid = *numValid + 1;
}

void CheckPartyBattleTowerBanlist(void)
{
    s32 i;
    u16 species2;
    u16 heldItem;
    u8 level;
    u16 hp;
    u32 numBanlistCaught;
    u16 validPartySpecies[6];
    u16 validPartyHeldItems[6];
    u8 counter;

    counter = 0;

    for (i = 0; i < PARTY_SIZE; i++)
    {
        species2 = GetMonData(&gPlayerParty[i], MON_DATA_SPECIES_OR_EGG);
        heldItem = GetMonData(&gPlayerParty[i], MON_DATA_HELD_ITEM);
        level = GetMonData(&gPlayerParty[i], MON_DATA_LEVEL);
        hp = GetMonData(&gPlayerParty[i], MON_DATA_HP);

        CheckMonBattleTowerBanlist(species2, heldItem, hp, gSpecialVar_Result, level, validPartySpecies, validPartyHeldItems, &counter);
    }

    if (counter < 3)
    {
        gStringVar1[0] = EOS;
        gSpecialVar_0x8004 = 1;
        counter = 0;

        for (i = 0; gBattleTowerBannedSpecies[i] != 0xFFFF; i++)
            counter = AppendBattleTowerBannedSpeciesName(gBattleTowerBannedSpecies[i], counter);

        i = StringLength(gStringVar1);
        gStringVar1[i - 1] = EOS;
        if (counter < 3)
            StringAppend(gStringVar1, gText_BattleTowerBan_Is1);
        else
            StringAppend(gStringVar1, gText_BattleTowerBan_Is2);
    }
    else
    {
        gSpecialVar_0x8004 = 0;
        gSaveBlock2Ptr->battleTower.battleTowerLevelType = gSpecialVar_Result;
    }
}

static void BufferBattleTowerTrainerMessage(const u16 *greeting)
{
    s32 i;
    if (EC_DoesEasyChatStringFitOnLine(greeting, 3, 2, 18))
    {
        ConvertEasyChatWordsToString(gStringVar4, greeting, 2, 3);
        i = 0;
        while (gStringVar4[i++] != CHAR_NEWLINE)
            ;
        while (gStringVar4[i] != CHAR_NEWLINE)
            i++;
        gStringVar4[i] = CHAR_PROMPT_SCROLL;
    }
    else
    {
        ConvertEasyChatWordsToString(gStringVar4, greeting, 3, 2);
    }
}

void PrintBattleTowerTrainerGreeting(void)
{
    if (gSaveBlock2Ptr->battleTower.battleTowerTrainerId == BATTLE_TOWER_EREADER_TRAINER_ID)
        BufferBattleTowerTrainerMessage(gSaveBlock2Ptr->battleTower.ereaderTrainer.greeting);
    else if (gSaveBlock2Ptr->battleTower.battleTowerTrainerId < BATTLE_TOWER_RECORD_MIXING_TRAINER_BASE_ID)
        BufferBattleTowerTrainerMessage(sBattleTowerTrainers[gSaveBlock2Ptr->battleTower.battleTowerTrainerId].greeting);
    else
        BufferBattleTowerTrainerMessage(gSaveBlock2Ptr->battleTower.records[gSaveBlock2Ptr->battleTower.battleTowerTrainerId - BATTLE_TOWER_RECORD_MIXING_TRAINER_BASE_ID].greeting);
}

static void CB2_FinishEReaderBattle(void)
{
    s32 i;
    u16 heldItem;

    switch (sSpecialVar_0x8004_Copy)
    {
    case 0:
        break;
    case 1:
        for (i = 0; i < PARTY_SIZE; i++)
        {
            heldItem = GetMonData(&gSaveBlock1Ptr->playerParty[i], MON_DATA_HELD_ITEM);
            SetMonData(&gPlayerParty[i], MON_DATA_HELD_ITEM, &heldItem);
        }
        break;
    case 2:
        PrintEReaderTrainerFarewellMessage();
        break;
    }

    SetMainCallback2(CB2_ReturnToFieldContinueScriptPlayMapMusic);
}

static void Task_WaitBT(u8 taskId)
{
    if (IsBattleTransitionDone() == TRUE)
    {
        gMain.savedCallback = CB2_FinishEReaderBattle;
        CleanupOverworldWindowsAndTilemaps();
        SetMainCallback2(CB2_InitBattle);
        DestroyTask(taskId);
    }
}


void StartSpecialBattle(void)
{
    s32 i;
    u16 heldItem;
    u8 transition;

    sSpecialVar_0x8004_Copy = gSpecialVar_0x8004;
    switch (sSpecialVar_0x8004_Copy)
    {
    case 0: // battle tower battle
        gBattleTypeFlags = (BATTLE_TYPE_BATTLE_TOWER | BATTLE_TYPE_TRAINER);
        gTrainerBattleOpponent_A = 0;

        FillBattleTowerTrainerParty();

        CreateTask(Task_WaitBT, 1);
        PlayMapChosenOrBattleBGM(0);
        transition = BattleSetup_GetBattleTowerBattleTransition();
        BattleTransition_StartOnField(transition);
        break;
    case 1: // secret base battle
        for (i = 0; i < PARTY_SIZE; i++)
        {
            heldItem = GetMonData(&gPlayerParty[i], MON_DATA_HELD_ITEM);
            SetMonData(&gSaveBlock1Ptr->playerParty[i], MON_DATA_HELD_ITEM, &heldItem);
        }

        CreateTask(Task_WaitBT, 1);
        PlayMapChosenOrBattleBGM(0);
        transition = BattleSetup_GetBattleTowerBattleTransition();
        BattleTransition_StartOnField(transition);
        break;
    case 2: // e-reader trainer battle
        ZeroEnemyPartyMons();

        for (i = 0; i < 3; i++)
            CreateBattleTowerMon(&gEnemyParty[i], &gSaveBlock2Ptr->battleTower.ereaderTrainer.party[i]);

        gBattleTypeFlags = (BATTLE_TYPE_EREADER_TRAINER | BATTLE_TYPE_TRAINER);
        gTrainerBattleOpponent_A = 0;

        CreateTask(Task_WaitBT, 1);
        PlayMapChosenOrBattleBGM(0);
        transition = BattleSetup_GetBattleTowerBattleTransition();
        BattleTransition_StartOnField(transition);
        break;
    }
}

void SetBattleTowerProperty(void)
{
    s32 i;
    u8 battleTowerLevelType = gSaveBlock2Ptr->battleTower.battleTowerLevelType;

    switch (gSpecialVar_0x8004)
    {
    case 0:
        ewram160FB = gSaveBlock2Ptr->battleTower.var_4AE[battleTowerLevelType];
        gSaveBlock2Ptr->battleTower.var_4AE[battleTowerLevelType] = gSpecialVar_0x8005;
        break;
    case 1:
        gSaveBlock2Ptr->battleTower.battleTowerLevelType = gSpecialVar_0x8005;
        break;
    case 2:
        gSaveBlock2Ptr->battleTower.curChallengeBattleNum[battleTowerLevelType] = gSpecialVar_0x8005;
        break;
    case 3:
        gSaveBlock2Ptr->battleTower.curStreakChallengesNum[battleTowerLevelType] = gSpecialVar_0x8005;
        break;
    case 4:
        gSaveBlock2Ptr->battleTower.battleTowerTrainerId = gSpecialVar_0x8005;
        break;
    case 5:
        for (i = 0; i < 3; i++)
            gSaveBlock2Ptr->battleTower.selectedPartyMons[i] = gSelectedOrderFromParty[i];
        break;
    case 6:
        if (gSaveBlock2Ptr->battleTower.battleTowerTrainerId == BATTLE_TOWER_EREADER_TRAINER_ID)
            ClearEReaderTrainer(&gSaveBlock2Ptr->battleTower.ereaderTrainer);
        if (gSaveBlock2Ptr->battleTower.totalBattleTowerWins < 9999)
            gSaveBlock2Ptr->battleTower.totalBattleTowerWins++;
        gSaveBlock2Ptr->battleTower.curChallengeBattleNum[battleTowerLevelType]++;
        SaveCurrentWinStreak();
        gSpecialVar_Result = gSaveBlock2Ptr->battleTower.curChallengeBattleNum[battleTowerLevelType];
        gStringVar1[0] = gSaveBlock2Ptr->battleTower.curChallengeBattleNum[battleTowerLevelType] + 0xA1;
        gStringVar1[1] = 0xFF;
        break;
    case 7:
        if (gSaveBlock2Ptr->battleTower.curStreakChallengesNum[battleTowerLevelType] < 1430)
            gSaveBlock2Ptr->battleTower.curStreakChallengesNum[battleTowerLevelType]++;
        SaveCurrentWinStreak();
        gSpecialVar_Result = gSaveBlock2Ptr->battleTower.curStreakChallengesNum[battleTowerLevelType];
        break;
    case 8:
        gSaveBlock2Ptr->battleTower.unk_554 = gSpecialVar_0x8005;
        break;
    case 9:
        break;
    case 10:
        SetGameStat(GAME_STAT_BATTLE_TOWER_BEST_STREAK, gSaveBlock2Ptr->battleTower.bestBattleTowerWinStreak);
        break;
    case 11:
        if (gSaveBlock2Ptr->battleTower.var_4AE[battleTowerLevelType] != 3)
            ResetBattleTowerStreak(battleTowerLevelType);
        break;
    case 12:
        gSaveBlock2Ptr->battleTower.var_4AE[battleTowerLevelType] = ewram160FB;
        break;
    case 13:
        gSaveBlock2Ptr->battleTower.currentWinStreaks[battleTowerLevelType] = GetCurrentBattleTowerWinStreak(battleTowerLevelType);
        break;
    case 14:
        gSaveBlock2Ptr->battleTower.lastStreakLevelType = gSaveBlock2Ptr->battleTower.battleTowerLevelType;
        break;
    }
}

void BattleTowerUtil(void)
{
    u8 battleTowerLevelType = gSaveBlock2Ptr->battleTower.battleTowerLevelType;

    switch (gSpecialVar_0x8004)
    {
    case 0:
        gSpecialVar_Result = gSaveBlock2Ptr->battleTower.var_4AE[battleTowerLevelType];
        break;
    case 1:
        gSpecialVar_Result = gSaveBlock2Ptr->battleTower.battleTowerLevelType;
        break;
    case 2:
        gSpecialVar_Result = gSaveBlock2Ptr->battleTower.curChallengeBattleNum[battleTowerLevelType];
        break;
    case 3:
        gSpecialVar_Result = gSaveBlock2Ptr->battleTower.curStreakChallengesNum[battleTowerLevelType];
        break;
    case 4:
        gSpecialVar_Result = gSaveBlock2Ptr->battleTower.battleTowerTrainerId;
        break;
    case 5:
    case 6:
    case 7:
        break;
    case 8:
        gSpecialVar_Result = gSaveBlock2Ptr->battleTower.unk_554;
        break;
    case 9:
        gSpecialVar_Result = GetCurrentBattleTowerWinStreak(battleTowerLevelType);
        break;
    case 10:
        SetGameStat(GAME_STAT_BATTLE_TOWER_BEST_STREAK, gSaveBlock2Ptr->battleTower.bestBattleTowerWinStreak);
        break;
    case 11:
        ResetBattleTowerStreak(battleTowerLevelType);
        break;
    case 12:
        gSaveBlock2Ptr->battleTower.var_4AE[battleTowerLevelType] = ewram160FB;
        break;
    case 13:
        gSaveBlock2Ptr->battleTower.currentWinStreaks[battleTowerLevelType] = GetCurrentBattleTowerWinStreak(battleTowerLevelType);
        break;
    case 14:
        gSaveBlock2Ptr->battleTower.lastStreakLevelType = gSaveBlock2Ptr->battleTower.battleTowerLevelType;
        break;
    }
}

void SetBattleTowerParty(void)
{
    s32 i;

    for (i = 0; i < 3; i++)
        gSelectedOrderFromParty[i] = gSaveBlock2Ptr->battleTower.selectedPartyMons[i];

    ReducePlayerPartyToThree();
}

static void SaveCurrentWinStreak(void)
{
    u8 levelType = gSaveBlock2Ptr->battleTower.battleTowerLevelType;
    u16 streak = GetCurrentBattleTowerWinStreak(levelType);

    if (gSaveBlock2Ptr->battleTower.recordWinStreaks[levelType] < streak)
        gSaveBlock2Ptr->battleTower.recordWinStreaks[levelType] = streak;

    if (gSaveBlock2Ptr->battleTower.recordWinStreaks[0] > gSaveBlock2Ptr->battleTower.recordWinStreaks[1])
    {
        streak = gSaveBlock2Ptr->battleTower.recordWinStreaks[0];
        SetGameStat(GAME_STAT_BATTLE_TOWER_BEST_STREAK, streak);

        if (streak > 9999)
            gSaveBlock2Ptr->battleTower.bestBattleTowerWinStreak = 9999;
        else
            gSaveBlock2Ptr->battleTower.bestBattleTowerWinStreak = streak;
    }
    else
    {
        streak = gSaveBlock2Ptr->battleTower.recordWinStreaks[1];
        SetGameStat(GAME_STAT_BATTLE_TOWER_BEST_STREAK, streak);

        if (streak > 9999)
            gSaveBlock2Ptr->battleTower.bestBattleTowerWinStreak = 9999;
        else
            gSaveBlock2Ptr->battleTower.bestBattleTowerWinStreak = streak;
    }
}

static void SetPlayerBattleTowerRecord(void)
{
    s32 i;
    u8 trainerClass;
    struct BattleTowerRecord *playerRecord = &gSaveBlock2Ptr->battleTower.playerRecord;
    u8 battleTowerLevelType = gSaveBlock2Ptr->battleTower.battleTowerLevelType;

    if (gSaveBlock2Ptr->playerGender != MALE)
    {
        trainerClass = sFemaleTrainerClasses[(gSaveBlock2Ptr->playerTrainerId[0] + gSaveBlock2Ptr->playerTrainerId[1]
                                              + gSaveBlock2Ptr->playerTrainerId[2] + gSaveBlock2Ptr->playerTrainerId[3]) % NELEMS(sFemaleTrainerClasses)];
    }
    else
    {
        trainerClass = sMaleTrainerClasses[(gSaveBlock2Ptr->playerTrainerId[0] + gSaveBlock2Ptr->playerTrainerId[1]
                                            + gSaveBlock2Ptr->playerTrainerId[2] + gSaveBlock2Ptr->playerTrainerId[3]) % NELEMS(sMaleTrainerClasses)];
    }

    playerRecord->battleTowerLevelType = battleTowerLevelType;
    playerRecord->trainerClass = trainerClass;

    CopyTrainerId(playerRecord->trainerId, gSaveBlock2Ptr->playerTrainerId);
    StringCopy_PlayerName(playerRecord->name, gSaveBlock2Ptr->playerName);

    playerRecord->winStreak = GetCurrentBattleTowerWinStreak(battleTowerLevelType);

    for (i = 0; i < 6; i++)
        playerRecord->greeting[i] = gSaveBlock1Ptr->easyChatBattleStart[i];

    for (i = 0; i < 3; i++)
        ConvertPokemonToBattleTowerPokemon(&gPlayerParty[gSaveBlock2Ptr->battleTower.selectedPartyMons[i] - 1],
                                           &playerRecord->party[i]);

    SetBattleTowerRecordChecksum(&gSaveBlock2Ptr->battleTower.playerRecord);
    SaveCurrentWinStreak();
}

void SaveBattleTowerProgress(void)
{
    u8 battleTowerLevelType = gSaveBlock2Ptr->battleTower.battleTowerLevelType;

    if (gSpecialVar_0x8004 == 3 || gSpecialVar_0x8004 == 0)
    {
        if (gSaveBlock2Ptr->battleTower.curStreakChallengesNum[battleTowerLevelType] > 1
            || gSaveBlock2Ptr->battleTower.curChallengeBattleNum[battleTowerLevelType] > 1)
            SetPlayerBattleTowerRecord();
    }

    PopulateBravoTrainerBattleTowerLostData();

    gSaveBlock2Ptr->battleTower.battleOutcome = gBattleOutcome;

    if (gSpecialVar_0x8004 != 3)
        gSaveBlock2Ptr->battleTower.var_4AE[battleTowerLevelType] = gSpecialVar_0x8004;

    VarSet(VAR_TEMP_0, BTSPECIAL_TEST);
    gSaveBlock2Ptr->battleTower.unk_554 = 1;
    TrySavingData(SAVE_EREADER);
}

void BattleTower_SoftReset(void)
{
    DoSoftReset();
}

static void ValidateBattleTowerRecordChecksums(void)
{
    u32 i;
    s32 recordIndex;
    struct BattleTowerRecord *record;
    u32 checksum;

    record = &gSaveBlock2Ptr->battleTower.playerRecord;
    checksum = 0;
    for (i = 0; i < (sizeof(struct BattleTowerRecord) / sizeof(u32)) - 1; i++)
        checksum += ((u32 *)record)[i];

    if (gSaveBlock2Ptr->battleTower.playerRecord.checksum != checksum)
        ClearBattleTowerRecord(&gSaveBlock2Ptr->battleTower.playerRecord);

    for (recordIndex = 0; recordIndex < 5; recordIndex++)
    {
        record = &gSaveBlock2Ptr->battleTower.records[recordIndex];
        checksum = 0;
        for (i = 0; i < (sizeof(struct BattleTowerRecord) / sizeof(u32)) - 1; i++)
            checksum += ((u32 *)record)[i];

        if (gSaveBlock2Ptr->battleTower.records[recordIndex].checksum != checksum)
            ClearBattleTowerRecord(&gSaveBlock2Ptr->battleTower.records[recordIndex]);
    }
}

static void SetBattleTowerRecordChecksum(struct BattleTowerRecord *record)
{
    u32 i;

    record->checksum = 0;
    for (i = 0; i < (sizeof(struct BattleTowerRecord) / sizeof(u32)) - 1; i++)
        record->checksum += ((u32 *)record)[i];
}

static void ClearBattleTowerRecord(struct BattleTowerRecord *record)
{
    u32 i;

    for (i = 0; i < sizeof(struct BattleTowerRecord) / sizeof(u32); i++)
        ((u32 *)record)[i] = 0;
}

static void PopulateBravoTrainerBattleTowerLostData(void)
{
    s32 i;

    GetBattleTowerTrainerName(gSaveBlock2Ptr->battleTower.defeatedByTrainerName);
    gSaveBlock2Ptr->battleTower.defeatedBySpecies = gBattleMons[1].species;
    gSaveBlock2Ptr->battleTower.firstMonSpecies = gBattleMons[0].species;

    for (i = 0; i < POKEMON_NAME_LENGTH; i++)
        gSaveBlock2Ptr->battleTower.firstMonNickname[i] = gBattleMons[0].nickname[i];
}

static u16 GetCurrentBattleTowerWinStreak(u8 battleTowerLevelType)
{
    u16 winStreak = ((gSaveBlock2Ptr->battleTower.curStreakChallengesNum[battleTowerLevelType] - 1) * 7 - 1)
                    + gSaveBlock2Ptr->battleTower.curChallengeBattleNum[battleTowerLevelType];

    if (winStreak > 9999)
        return 9999;
    else
        return winStreak;
}

void DetermineBattleTowerPrize(void)
{
    u8 levelType = gSaveBlock2Ptr->battleTower.battleTowerLevelType;

    if (gSaveBlock2Ptr->battleTower.curStreakChallengesNum[levelType] - 1 > 5)
        gSaveBlock2Ptr->battleTower.prizeItem = sLongStreakPrizes[Random() % NELEMS(sLongStreakPrizes)];
    else
        gSaveBlock2Ptr->battleTower.prizeItem = sShortStreakPrizes[Random() % NELEMS(sShortStreakPrizes)];
}

void GiveBattleTowerPrize(void)
{
    u8 battleTowerLevelType = gSaveBlock2Ptr->battleTower.battleTowerLevelType;

    if (AddBagItem(gSaveBlock2Ptr->battleTower.prizeItem, 1) == TRUE)
    {
        CopyItemName(gSaveBlock2Ptr->battleTower.prizeItem, gStringVar1);
        gSpecialVar_Result = 1;
    }
    else
    {
        gSpecialVar_Result = 0;
        gSaveBlock2Ptr->battleTower.var_4AE[battleTowerLevelType] = 6;
    }
}

void AwardBattleTowerRibbons(void)
{
    s32 i;
    u32 partyIndex;
    struct Pokemon *pokemon;
    u8 ribbonType;
    u8 battleTowerLevelType = gSaveBlock2Ptr->battleTower.battleTowerLevelType;

    if (battleTowerLevelType != 0)
        ribbonType = MON_DATA_VICTORY_RIBBON;
    else
        ribbonType = MON_DATA_WINNING_RIBBON;

    gSpecialVar_Result = 0;

    if (GetCurrentBattleTowerWinStreak(battleTowerLevelType) > 55)
    {
        for (i = 0; i < 3; i++)
        {
            partyIndex = gSaveBlock2Ptr->battleTower.selectedPartyMons[i] - 1;
            pokemon = &gPlayerParty[partyIndex];
            if (!GetMonData(pokemon, ribbonType))
            {
                gSpecialVar_Result = 1;
                SetMonData(pokemon, ribbonType, &gSpecialVar_Result);
            }
        }
    }

    if (gSpecialVar_Result != 0)
        IncrementGameStat(GAME_STAT_RECEIVED_RIBBONS);
}

// This is a leftover debugging function that is used to populate the E-Reader
// trainer with the player's current data.
static void Debug_FillEReaderTrainerWithPlayerData(void)
{
    struct BattleTowerEReaderTrainer *ereaderTrainer;
    s32 i;
    s32 j;

    ereaderTrainer = &gSaveBlock2Ptr->battleTower.ereaderTrainer;

    if (gSaveBlock2Ptr->playerGender != MALE)
    {
        ereaderTrainer->trainerClass = sFemaleTrainerClasses[(gSaveBlock2Ptr->playerTrainerId[0] + gSaveBlock2Ptr->playerTrainerId[1]
                                                              + gSaveBlock2Ptr->playerTrainerId[2] + gSaveBlock2Ptr->playerTrainerId[3]) % NELEMS(sFemaleTrainerClasses)];
    }
    else
    {
        ereaderTrainer->trainerClass = sMaleTrainerClasses[(gSaveBlock2Ptr->playerTrainerId[0] + gSaveBlock2Ptr->playerTrainerId[1]
                                                            + gSaveBlock2Ptr->playerTrainerId[2] + gSaveBlock2Ptr->playerTrainerId[3]) % NELEMS(sMaleTrainerClasses)];
    }

    CopyTrainerId(ereaderTrainer->trainerId, gSaveBlock2Ptr->playerTrainerId);
    StringCopy_PlayerName(ereaderTrainer->name, gSaveBlock2Ptr->playerName);

    ereaderTrainer->winStreak = 1;

    j = 7;
    for (i = 0; i < 6; i++)
    {
        ereaderTrainer->greeting[i] = gSaveBlock1Ptr->easyChatBattleStart[i];
        ereaderTrainer->farewellPlayerLost[i] = j;
        ereaderTrainer->farewellPlayerWon[i] = j + 6;
        j++;
    }

    for (i = 0; i < 3; i++)
        ConvertPokemonToBattleTowerPokemon(&gPlayerParty[i], &ereaderTrainer->party[i]);

    SetEReaderTrainerChecksum(ereaderTrainer);
}

u8 GetEreaderTrainerFrontSpriteId(void)
{
    return gFacilityClassToPicIndex[gSaveBlock2Ptr->battleTower.ereaderTrainer.trainerClass];
}

u8 GetEreaderTrainerClassId(void)
{
    return gFacilityClassToTrainerClass[gSaveBlock2Ptr->battleTower.ereaderTrainer.trainerClass];
}

void CopyEReaderTrainerName5(u8 *trainerName)
{
    s32 i;

    for (i = 0; i < 5; i++)
        trainerName[i] = gSaveBlock2Ptr->battleTower.ereaderTrainer.name[i];

    trainerName[i] = EOS;
}

// Checks if the saved E-Reader trainer is valid.
void ValidateEReaderTrainer(void)
{
    u32 i;
    u32 checksum;
    struct BattleTowerEReaderTrainer *ereaderTrainer;

    gSpecialVar_Result = 0;
    ereaderTrainer = &gSaveBlock2Ptr->battleTower.ereaderTrainer;

    checksum = 0;
    for (i = 0; i < sizeof(struct BattleTowerEReaderTrainer) / sizeof(u32) - 1; i++)
        checksum |= ((u32 *)ereaderTrainer)[i];

    if (checksum == 0)
    {
        gSpecialVar_Result = 1;
        return;
    }

    checksum = 0;
    for (i = 0; i < sizeof(struct BattleTowerEReaderTrainer) / sizeof(u32) - 1; i++)
        checksum += ((u32 *)ereaderTrainer)[i];

    if (gSaveBlock2Ptr->battleTower.ereaderTrainer.checksum != checksum)
    {
        ClearEReaderTrainer(&gSaveBlock2Ptr->battleTower.ereaderTrainer);
        gSpecialVar_Result = 1;
    }
}

static void SetEReaderTrainerChecksum(struct BattleTowerEReaderTrainer *ereaderTrainer)
{
    s32 i;

    ereaderTrainer->checksum = 0;
    for (i = 0; i < sizeof(struct BattleTowerEReaderTrainer) / sizeof(u32) - 1; i++)
        ereaderTrainer->checksum += ((u32 *)ereaderTrainer)[i];
}

void ClearEReaderTrainer(struct BattleTowerEReaderTrainer *ereaderTrainer)
{
    u32 i;

    for (i = 0; i < sizeof(struct BattleTowerEReaderTrainer) / sizeof(u32); i++)
        ((u32 *)ereaderTrainer)[i] = 0;
}

void BufferEReaderTrainerGreeting(void)
{
    BufferBattleTowerTrainerMessage(gSaveBlock2Ptr->battleTower.ereaderTrainer.greeting);
}

static void PrintEReaderTrainerFarewellMessage(void)
{
    if (gBattleOutcome == B_OUTCOME_DREW)
        gStringVar4[0] = EOS;
    else if (gBattleOutcome == B_OUTCOME_WON)
        BufferBattleTowerTrainerMessage(gSaveBlock2Ptr->battleTower.ereaderTrainer.farewellPlayerWon);
    else
        BufferBattleTowerTrainerMessage(gSaveBlock2Ptr->battleTower.ereaderTrainer.farewellPlayerLost);
}

void Dummy_TryEnableBravoTrainerBattleTower(void)
{
    s32 i;

    for (i = 0; i < 2; i++)
    {
        if (gSaveBlock2Ptr->battleTower.var_4AE[i] == 1)
            TakeBravoTrainerBattleTowerOffTheAir();
    }
}
