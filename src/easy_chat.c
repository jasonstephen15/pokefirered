#include "global.h"
#include "gflib.h"
#include "data.h"
#include "easy_chat.h"
#include "event_data.h"
#include "field_message_box.h"
#include "mystery_gift.h"
#include "menu.h"
#include "mail.h"
#include "pokedex.h"
#include "random.h"
#include "strings.h"
#include "constants/easy_chat.h"

struct Unk203A120
{
    u16 numGroups;
    u16 groups[EC_NUM_GROUPS];
    u16 alphabeticalGroups[27];
    u16 alphabeticalWordsByGroup[27][270];
    u8 filler3958[0x2C];
    u16 allWords[270];
    u16 totalWords;
}; /*size = 0x3BA4*/

static EWRAM_DATA struct Unk203A120 * sEasyChatSelectionData = NULL;

static bool8 EC_IsNationalPokedexEnabled(void);
static u16 GetRandomECPokemon(void);
static void PopulateECGroups(void);
static void PopulateAlphabeticalGroups(void);
static u16 GetUnlockedWordsInECGroup(u16);
static u16 GetUnlockedWordsInAlphabeticalGroup(u16);
static bool8 UnlockedECMonOrMove(u16, u8);
static bool32 EC_IsDeoxys(u16 species);
static bool8 IsWordUnlocked(u16 word);

// ===== BEGIN src/data/easy_chat/easy_chat_groups.h =====
#include "easy_chat.h"

// ===== BEGIN src/data/easy_chat/easy_chat_group_pokemon.h =====
static const u16 sEasyChatGroup_Pokemon[] = {
    SPECIES_ABRA,
    SPECIES_ABSOL,
    SPECIES_AGGRON,
    SPECIES_ALAKAZAM,
    SPECIES_ALTARIA,
    SPECIES_ANORITH,
    SPECIES_ARMALDO,
    SPECIES_ARON,
    SPECIES_AZUMARILL,
    SPECIES_AZURILL,
    SPECIES_BAGON,
    SPECIES_BALTOY,
    SPECIES_BANETTE,
    SPECIES_BARBOACH,
    SPECIES_BEAUTIFLY,
    SPECIES_BELDUM,
    SPECIES_BELLOSSOM,
    SPECIES_BLAZIKEN,
    SPECIES_BRELOOM,
    SPECIES_CACNEA,
    SPECIES_CACTURNE,
    SPECIES_CAMERUPT,
    SPECIES_CARVANHA,
    SPECIES_CASCOON,
    SPECIES_CASTFORM,
    SPECIES_CHIMECHO,
    SPECIES_CHINCHOU,
    SPECIES_CLAMPERL,
    SPECIES_CLAYDOL,
    SPECIES_COMBUSKEN,
    SPECIES_CORPHISH,
    SPECIES_CORSOLA,
    SPECIES_CRADILY,
    SPECIES_CRAWDAUNT,
    SPECIES_CROBAT,
    SPECIES_DELCATTY,
    SPECIES_DEOXYS,
    SPECIES_DODRIO,
    SPECIES_DODUO,
    SPECIES_DONPHAN,
    SPECIES_DUSCLOPS,
    SPECIES_DUSKULL,
    SPECIES_DUSTOX,
    SPECIES_ELECTRIKE,
    SPECIES_ELECTRODE,
    SPECIES_EXPLOUD,
    SPECIES_FEEBAS,
    SPECIES_FLYGON,
    SPECIES_GARDEVOIR,
    SPECIES_GEODUDE,
    SPECIES_GIRAFARIG,
    SPECIES_GLALIE,
    SPECIES_GLOOM,
    SPECIES_GOLBAT,
    SPECIES_GOLDEEN,
    SPECIES_GOLDUCK,
    SPECIES_GOLEM,
    SPECIES_GOREBYSS,
    SPECIES_GRAVELER,
    SPECIES_GRIMER,
    SPECIES_GROUDON,
    SPECIES_GROVYLE,
    SPECIES_GRUMPIG,
    SPECIES_GULPIN,
    SPECIES_GYARADOS,
    SPECIES_HARIYAMA,
    SPECIES_HERACROSS,
    SPECIES_HORSEA,
    SPECIES_HUNTAIL,
    SPECIES_IGGLYBUFF,
    SPECIES_ILLUMISE,
    SPECIES_JIGGLYPUFF,
    SPECIES_JIRACHI,
    SPECIES_KADABRA,
    SPECIES_KECLEON,
    SPECIES_KINGDRA,
    SPECIES_KIRLIA,
    SPECIES_KOFFING,
    SPECIES_KYOGRE,
    SPECIES_LAIRON,
    SPECIES_LANTURN,
    SPECIES_LATIAS,
    SPECIES_LATIOS,
    SPECIES_LILEEP,
    SPECIES_LINOONE,
    SPECIES_LOMBRE,
    SPECIES_LOTAD,
    SPECIES_LOUDRED,
    SPECIES_LUDICOLO,
    SPECIES_LUNATONE,
    SPECIES_LUVDISC,
    SPECIES_MACHAMP,
    SPECIES_MACHOKE,
    SPECIES_MACHOP,
    SPECIES_MAGCARGO,
    SPECIES_MAGIKARP,
    SPECIES_MAGNEMITE,
    SPECIES_MAGNETON,
    SPECIES_MAKUHITA,
    SPECIES_MANECTRIC,
    SPECIES_MARILL,
    SPECIES_MARSHTOMP,
    SPECIES_MASQUERAIN,
    SPECIES_MAWILE,
    SPECIES_MEDICHAM,
    SPECIES_MEDITITE,
    SPECIES_METAGROSS,
    SPECIES_METANG,
    SPECIES_MIGHTYENA,
    SPECIES_MILOTIC,
    SPECIES_MINUN,
    SPECIES_MUDKIP,
    SPECIES_MUK,
    SPECIES_NATU,
    SPECIES_NINCADA,
    SPECIES_NINETALES,
    SPECIES_NINJASK,
    SPECIES_NOSEPASS,
    SPECIES_NUMEL,
    SPECIES_NUZLEAF,
    SPECIES_ODDISH,
    SPECIES_PELIPPER,
    SPECIES_PHANPY,
    SPECIES_PICHU,
    SPECIES_PIKACHU,
    SPECIES_PINSIR,
    SPECIES_PLUSLE,
    SPECIES_POOCHYENA,
    SPECIES_PSYDUCK,
    SPECIES_RAICHU,
    SPECIES_RALTS,
    SPECIES_RAYQUAZA,
    SPECIES_REGICE,
    SPECIES_REGIROCK,
    SPECIES_REGISTEEL,
    SPECIES_RELICANTH,
    SPECIES_RHYDON,
    SPECIES_RHYHORN,
    SPECIES_ROSELIA,
    SPECIES_SABLEYE,
    SPECIES_SALAMENCE,
    SPECIES_SANDSHREW,
    SPECIES_SANDSLASH,
    SPECIES_SCEPTILE,
    SPECIES_SEADRA,
    SPECIES_SEAKING,
    SPECIES_SEALEO,
    SPECIES_SEEDOT,
    SPECIES_SEVIPER,
    SPECIES_SHARPEDO,
    SPECIES_SHEDINJA,
    SPECIES_SHELGON,
    SPECIES_SHIFTRY,
    SPECIES_SHROOMISH,
    SPECIES_SHUPPET,
    SPECIES_SILCOON,
    SPECIES_SKARMORY,
    SPECIES_SKITTY,
    SPECIES_SLAKING,
    SPECIES_SLAKOTH,
    SPECIES_SLUGMA,
    SPECIES_SNORUNT,
    SPECIES_SOLROCK,
    SPECIES_SPHEAL,
    SPECIES_SPINDA,
    SPECIES_SPOINK,
    SPECIES_STARMIE,
    SPECIES_STARYU,
    SPECIES_SURSKIT,
    SPECIES_SWABLU,
    SPECIES_SWALOT,
    SPECIES_SWAMPERT,
    SPECIES_SWELLOW,
    SPECIES_TAILLOW,
    SPECIES_TENTACOOL,
    SPECIES_TENTACRUEL,
    SPECIES_TORCHIC,
    SPECIES_TORKOAL,
    SPECIES_TRAPINCH,
    SPECIES_TREECKO,
    SPECIES_TROPIUS,
    SPECIES_VIBRAVA,
    SPECIES_VIGOROTH,
    SPECIES_VILEPLUME,
    SPECIES_VOLBEAT,
    SPECIES_VOLTORB,
    SPECIES_VULPIX,
    SPECIES_WAILMER,
    SPECIES_WAILORD,
    SPECIES_WALREIN,
    SPECIES_WEEZING,
    SPECIES_WHISCASH,
    SPECIES_WHISMUR,
    SPECIES_WIGGLYTUFF,
    SPECIES_WINGULL,
    SPECIES_WOBBUFFET,
    SPECIES_WURMPLE,
    SPECIES_WYNAUT,
    SPECIES_XATU,
    SPECIES_ZANGOOSE,
    SPECIES_ZIGZAGOON,
    SPECIES_ZUBAT,
};
// ===== END src/data/easy_chat/easy_chat_group_pokemon.h =====
// ===== BEGIN src/data/easy_chat/easy_chat_group_trainer.h =====

static const u8 sEasyChatWord_IChooseYou[] = _("I CHOOSE YOU");
static const u8 sEasyChatWord_Gotcha[] = _("GOTCHA");
static const u8 sEasyChatWord_Trade[] = _("TRADE");
static const u8 sEasyChatWord_Sapphire[] = _("SAPPHIRE");
static const u8 sEasyChatWord_Evolve[] = _("EVOLVE");
static const u8 sEasyChatWord_Encyclopedia[] = _("ENCYCLOPEDIA");
static const u8 sEasyChatWord_Nature[] = _("NATURE");
static const u8 sEasyChatWord_Center[] = _("CENTER");
static const u8 sEasyChatWord_Egg[] = _("EGG");
static const u8 sEasyChatWord_Link[] = _("LINK");
static const u8 sEasyChatWord_SpAbility[] = _("SP. ABILITY");
static const u8 sEasyChatWord_Trainer[] = _("TRAINER");
static const u8 sEasyChatWord_Version[] = _("VERSION");
static const u8 sEasyChatWord_Pokenav[] = _("POKéNAV");
static const u8 sEasyChatWord_Pokemon[] = _("POKéMON");
static const u8 sEasyChatWord_Get[] = _("GET");
static const u8 sEasyChatWord_Pokedex[] = _("POKéDEX");
static const u8 sEasyChatWord_Ruby[] = _("RUBY");
static const u8 sEasyChatWord_Level[] = _("LEVEL");
static const u8 sEasyChatWord_Red[] = _("RED");
static const u8 sEasyChatWord_Green[] = _("GREEN");
static const u8 sEasyChatWord_Bag[] = _("BAG");
static const u8 sEasyChatWord_Flame[] = _("FLAME");
static const u8 sEasyChatWord_Gold[] = _("GOLD");
static const u8 sEasyChatWord_Leaf[] = _("LEAF");
static const u8 sEasyChatWord_Silver[] = _("SILVER");

static const struct EasyChatWordInfo sEasyChatGroup_Trainer[] = {
    {
        .text = sEasyChatWord_IChooseYou,
        .alphabeticalOrder = 21,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Gotcha,
        .alphabeticalOrder = 7,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Trade,
        .alphabeticalOrder = 8,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Sapphire,
        .alphabeticalOrder = 5,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Evolve,
        .alphabeticalOrder = 4,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Encyclopedia,
        .alphabeticalOrder = 22,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Nature,
        .alphabeticalOrder = 15,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Center,
        .alphabeticalOrder = 23,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Egg,
        .alphabeticalOrder = 1,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Link,
        .alphabeticalOrder = 20,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_SpAbility,
        .alphabeticalOrder = 0,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Trainer,
        .alphabeticalOrder = 24,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Version,
        .alphabeticalOrder = 18,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Pokenav,
        .alphabeticalOrder = 9,
        .enabled = FALSE
    },
    {
        .text = sEasyChatWord_Pokemon,
        .alphabeticalOrder = 6,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Get,
        .alphabeticalOrder = 16,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Pokedex,
        .alphabeticalOrder = 14,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Ruby,
        .alphabeticalOrder = 13,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Level,
        .alphabeticalOrder = 19,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Red,
        .alphabeticalOrder = 17,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Green,
        .alphabeticalOrder = 3,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Bag,
        .alphabeticalOrder = 25,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Flame,
        .alphabeticalOrder = 10,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Gold,
        .alphabeticalOrder = 2,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Leaf,
        .alphabeticalOrder = 11,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Silver,
        .alphabeticalOrder = 12,
        .enabled = TRUE
    }
};
// ===== END src/data/easy_chat/easy_chat_group_trainer.h =====
// ===== BEGIN src/data/easy_chat/easy_chat_group_status.h =====

static const u8 sEasyChatWord_Dark[] = _("DARK");
static const u8 sEasyChatWord_Stench[] = _("STENCH");
static const u8 sEasyChatWord_ThickFat[] = _("THICK FAT");
static const u8 sEasyChatWord_RainDish[] = _("RAIN DISH");
static const u8 sEasyChatWord_Drizzle[] = _("DRIZZLE");
static const u8 sEasyChatWord_ArenaTrap[] = _("ARENA TRAP");
static const u8 sEasyChatWord_Intimidate[] = _("INTIMIDATE");
static const u8 sEasyChatWord_RockHead[] = _("ROCK HEAD");
static const u8 sEasyChatWord_Color[] = _("COLOR");
static const u8 sEasyChatWord_AltColor[] = _("ALT. COLOR");
static const u8 sEasyChatWord_Rock[] = _("ROCK");
static const u8 sEasyChatWord_Beautiful[] = _("BEAUTIFUL");
static const u8 sEasyChatWord_Beauty[] = _("BEAUTY");
static const u8 sEasyChatWord_AirLock[] = _("AIR LOCK");
static const u8 sEasyChatWord_Psychic[] = _("PSYCHIC");
static const u8 sEasyChatWord_HyperCutter[] = _("HYPER CUTTER");
static const u8 sEasyChatWord_Fighting[] = _("FIGHTING");
static const u8 sEasyChatWord_ShadowTag[] = _("SHADOW TAG");
static const u8 sEasyChatWord_Smart[] = _("SMART");
static const u8 sEasyChatWord_Smartness[] = _("SMARTNESS");
static const u8 sEasyChatWord_SpeedBoost[] = _("SPEED BOOST");
static const u8 sEasyChatWord_Cool[] = _("COOL");
static const u8 sEasyChatWord_Coolness[] = _("COOLNESS");
static const u8 sEasyChatWord_BattleArmor[] = _("BATTLE ARMOR");
static const u8 sEasyChatWord_Cute[] = _("CUTE");
static const u8 sEasyChatWord_Cuteness[] = _("CUTENESS");
static const u8 sEasyChatWord_Sturdy[] = _("STURDY");
static const u8 sEasyChatWord_SuctionCups[] = _("SUCTION CUPS");
static const u8 sEasyChatWord_Grass[] = _("GRASS");
static const u8 sEasyChatWord_ClearBody[] = _("CLEAR BODY");
static const u8 sEasyChatWord_Torrent[] = _("TORRENT");
static const u8 sEasyChatWord_Ghost[] = _("GHOST");
static const u8 sEasyChatWord_Ice[] = _("ICE");
static const u8 sEasyChatWord_Guts[] = _("GUTS");
static const u8 sEasyChatWord_RoughSkin[] = _("ROUGH SKIN");
static const u8 sEasyChatWord_ShellArmor[] = _("SHELL ARMOR");
static const u8 sEasyChatWord_NaturalCure[] = _("NATURAL CURE");
static const u8 sEasyChatWord_Damp[] = _("DAMP");
static const u8 sEasyChatWord_Ground[] = _("GROUND");
static const u8 sEasyChatWord_Limber[] = _("LIMBER");
static const u8 sEasyChatWord_MagnetPull[] = _("MAGNET PULL");
static const u8 sEasyChatWord_WhiteSmoke[] = _("WHITE SMOKE");
static const u8 sEasyChatWord_Synchronize[] = _("SYNCHRONIZE");
static const u8 sEasyChatWord_Overgrow[] = _("OVERGROW");
static const u8 sEasyChatWord_SwiftSwim[] = _("SWIFT SWIM");
static const u8 sEasyChatWord_SandStream[] = _("SAND STREAM");
static const u8 sEasyChatWord_SandVeil[] = _("SAND VEIL");
static const u8 sEasyChatWord_KeenEye[] = _("KEEN EYE");
static const u8 sEasyChatWord_InnerFocus[] = _("INNER FOCUS");
static const u8 sEasyChatWord_Static[] = _("STATIC");
static const u8 sEasyChatWord_Type[] = _("TYPE");
static const u8 sEasyChatWord_Tough[] = _("TOUGH");
static const u8 sEasyChatWord_Toughness[] = _("TOUGHNESS");
static const u8 sEasyChatWord_ShedSkin[] = _("SHED SKIN");
static const u8 sEasyChatWord_HugePower[] = _("HUGE POWER");
static const u8 sEasyChatWord_VoltAbsorb[] = _("VOLT ABSORB");
static const u8 sEasyChatWord_WaterAbsorb[] = _("WATER ABSORB");
static const u8 sEasyChatWord_Electric[] = _("ELECTRIC");
static const u8 sEasyChatWord_Forecast[] = _("FORECAST");
static const u8 sEasyChatWord_SereneGrace[] = _("SERENE GRACE");
static const u8 sEasyChatWord_Poison[] = _("POISON");
static const u8 sEasyChatWord_PoisonPoint[] = _("POISON POINT");
static const u8 sEasyChatWord_Dragon[] = _("DRAGON");
static const u8 sEasyChatWord_Trace[] = _("TRACE");
static const u8 sEasyChatWord_Oblivious[] = _("OBLIVIOUS");
static const u8 sEasyChatWord_Truant[] = _("TRUANT");
static const u8 sEasyChatWord_RunAway[] = _("RUN AWAY");
static const u8 sEasyChatWord_StickyHold[] = _("STICKY HOLD");
static const u8 sEasyChatWord_CloudNine[] = _("CLOUD NINE");
static const u8 sEasyChatWord_Normal[] = _("NORMAL");
static const u8 sEasyChatWord_Steel[] = _("STEEL");
static const u8 sEasyChatWord_Illuminate[] = _("ILLUMINATE");
static const u8 sEasyChatWord_EarlyBird[] = _("EARLY BIRD");
static const u8 sEasyChatWord_Hustle[] = _("HUSTLE");
static const u8 sEasyChatWord_Shine[] = _("SHINE");
static const u8 sEasyChatWord_Flying[] = _("FLYING");
static const u8 sEasyChatWord_Drought[] = _("DROUGHT");
static const u8 sEasyChatWord_Lightningrod[] = _("LIGHTNINGROD");
static const u8 sEasyChatWord_Compoundeyes[] = _("COMPOUNDEYES");
static const u8 sEasyChatWord_MarvelScale[] = _("MARVEL SCALE");
static const u8 sEasyChatWord_WonderGuard[] = _("WONDER GUARD");
static const u8 sEasyChatWord_Insomnia[] = _("INSOMNIA");
static const u8 sEasyChatWord_Levitate[] = _("LEVITATE");
static const u8 sEasyChatWord_Plus[] = _("PLUS");
static const u8 sEasyChatWord_Pressure[] = _("PRESSURE");
static const u8 sEasyChatWord_LiquidOoze[] = _("LIQUID OOZE");
static const u8 sEasyChatWord_ColorChange[] = _("COLOR CHANGE");
static const u8 sEasyChatWord_Soundproof[] = _("SOUNDPROOF");
static const u8 sEasyChatWord_EffectSpore[] = _("EFFECT SPORE");
static const u8 sEasyChatWord_Pkrs[] = _("{PK}RS");
static const u8 sEasyChatWord_Fire[] = _("FIRE");
static const u8 sEasyChatWord_FlameBody[] = _("FLAME BODY");
static const u8 sEasyChatWord_Minus[] = _("MINUS");
static const u8 sEasyChatWord_OwnTempo[] = _("OWN TEMPO");
static const u8 sEasyChatWord_MagmaArmor[] = _("MAGMA ARMOR");
static const u8 sEasyChatWord_Water[] = _("WATER");
static const u8 sEasyChatWord_WaterVeil[] = _("WATER VEIL");
static const u8 sEasyChatWord_Bug[] = _("BUG");
static const u8 sEasyChatWord_Swarm[] = _("SWARM");
static const u8 sEasyChatWord_CuteCharm[] = _("CUTE CHARM");
static const u8 sEasyChatWord_Immunity[] = _("IMMUNITY");
static const u8 sEasyChatWord_Blaze[] = _("BLAZE");
static const u8 sEasyChatWord_Pickup[] = _("PICKUP");
static const u8 sEasyChatWord_Pattern[] = _("PATTERN");
static const u8 sEasyChatWord_FlashFire[] = _("FLASH FIRE");
static const u8 sEasyChatWord_VitalSpirit[] = _("VITAL SPIRIT");
static const u8 sEasyChatWord_Chlorophyll[] = _("CHLOROPHYLL");
static const u8 sEasyChatWord_PurePower[] = _("PURE POWER");
static const u8 sEasyChatWord_ShieldDust[] = _("SHIELD DUST");

static const struct EasyChatWordInfo sEasyChatGroup_Status[] = {
    {
        .text = sEasyChatWord_Dark,
        .alphabeticalOrder = 13,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Stench,
        .alphabeticalOrder = 9,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_ThickFat,
        .alphabeticalOrder = 5,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_RainDish,
        .alphabeticalOrder = 23,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Drizzle,
        .alphabeticalOrder = 11,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_ArenaTrap,
        .alphabeticalOrder = 12,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Intimidate,
        .alphabeticalOrder = 101,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_RockHead,
        .alphabeticalOrder = 97,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Color,
        .alphabeticalOrder = 106,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_AltColor,
        .alphabeticalOrder = 29,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Rock,
        .alphabeticalOrder = 68,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Beautiful,
        .alphabeticalOrder = 8,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Beauty,
        .alphabeticalOrder = 86,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_AirLock,
        .alphabeticalOrder = 78,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Psychic,
        .alphabeticalOrder = 21,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_HyperCutter,
        .alphabeticalOrder = 22,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Fighting,
        .alphabeticalOrder = 24,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_ShadowTag,
        .alphabeticalOrder = 99,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Smart,
        .alphabeticalOrder = 25,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Smartness,
        .alphabeticalOrder = 37,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_SpeedBoost,
        .alphabeticalOrder = 0,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Cool,
        .alphabeticalOrder = 62,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Coolness,
        .alphabeticalOrder = 4,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_BattleArmor,
        .alphabeticalOrder = 76,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Cute,
        .alphabeticalOrder = 72,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Cuteness,
        .alphabeticalOrder = 88,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Sturdy,
        .alphabeticalOrder = 57,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_SuctionCups,
        .alphabeticalOrder = 16,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Grass,
        .alphabeticalOrder = 90,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_ClearBody,
        .alphabeticalOrder = 91,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Torrent,
        .alphabeticalOrder = 104,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Ghost,
        .alphabeticalOrder = 75,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Ice,
        .alphabeticalOrder = 58,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Guts,
        .alphabeticalOrder = 31,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_RoughSkin,
        .alphabeticalOrder = 28,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_ShellArmor,
        .alphabeticalOrder = 38,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_NaturalCure,
        .alphabeticalOrder = 33,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Damp,
        .alphabeticalOrder = 54,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Ground,
        .alphabeticalOrder = 73,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Limber,
        .alphabeticalOrder = 15,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_MagnetPull,
        .alphabeticalOrder = 32,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_WhiteSmoke,
        .alphabeticalOrder = 71,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Synchronize,
        .alphabeticalOrder = 100,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Overgrow,
        .alphabeticalOrder = 48,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_SwiftSwim,
        .alphabeticalOrder = 81,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_SandStream,
        .alphabeticalOrder = 6,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_SandVeil,
        .alphabeticalOrder = 47,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_KeenEye,
        .alphabeticalOrder = 82,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_InnerFocus,
        .alphabeticalOrder = 77,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Static,
        .alphabeticalOrder = 39,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Type,
        .alphabeticalOrder = 85,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Tough,
        .alphabeticalOrder = 94,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Toughness,
        .alphabeticalOrder = 40,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_ShedSkin,
        .alphabeticalOrder = 79,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_HugePower,
        .alphabeticalOrder = 92,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_VoltAbsorb,
        .alphabeticalOrder = 36,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_WaterAbsorb,
        .alphabeticalOrder = 69,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Electric,
        .alphabeticalOrder = 64,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Forecast,
        .alphabeticalOrder = 43,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_SereneGrace,
        .alphabeticalOrder = 93,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Poison,
        .alphabeticalOrder = 103,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_PoisonPoint,
        .alphabeticalOrder = 102,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Dragon,
        .alphabeticalOrder = 89,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Trace,
        .alphabeticalOrder = 83,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Oblivious,
        .alphabeticalOrder = 60,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Truant,
        .alphabeticalOrder = 61,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_RunAway,
        .alphabeticalOrder = 84,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_StickyHold,
        .alphabeticalOrder = 14,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_CloudNine,
        .alphabeticalOrder = 107,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Normal,
        .alphabeticalOrder = 3,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Steel,
        .alphabeticalOrder = 10,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Illuminate,
        .alphabeticalOrder = 7,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_EarlyBird,
        .alphabeticalOrder = 34,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Hustle,
        .alphabeticalOrder = 66,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Shine,
        .alphabeticalOrder = 45,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Flying,
        .alphabeticalOrder = 46,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Drought,
        .alphabeticalOrder = 59,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Lightningrod,
        .alphabeticalOrder = 17,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Compoundeyes,
        .alphabeticalOrder = 53,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_MarvelScale,
        .alphabeticalOrder = 35,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_WonderGuard,
        .alphabeticalOrder = 108,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Insomnia,
        .alphabeticalOrder = 74,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Levitate,
        .alphabeticalOrder = 18,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Plus,
        .alphabeticalOrder = 19,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Pressure,
        .alphabeticalOrder = 87,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_LiquidOoze,
        .alphabeticalOrder = 20,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_ColorChange,
        .alphabeticalOrder = 49,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Soundproof,
        .alphabeticalOrder = 70,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_EffectSpore,
        .alphabeticalOrder = 1,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Pkrs,
        .alphabeticalOrder = 67,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Fire,
        .alphabeticalOrder = 26,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_FlameBody,
        .alphabeticalOrder = 27,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Minus,
        .alphabeticalOrder = 98,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_OwnTempo,
        .alphabeticalOrder = 44,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_MagmaArmor,
        .alphabeticalOrder = 42,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Water,
        .alphabeticalOrder = 2,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_WaterVeil,
        .alphabeticalOrder = 30,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Bug,
        .alphabeticalOrder = 51,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Swarm,
        .alphabeticalOrder = 52,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_CuteCharm,
        .alphabeticalOrder = 63,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Immunity,
        .alphabeticalOrder = 65,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Blaze,
        .alphabeticalOrder = 50,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Pickup,
        .alphabeticalOrder = 105,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Pattern,
        .alphabeticalOrder = 55,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_FlashFire,
        .alphabeticalOrder = 95,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_VitalSpirit,
        .alphabeticalOrder = 56,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Chlorophyll,
        .alphabeticalOrder = 96,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_PurePower,
        .alphabeticalOrder = 41,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_ShieldDust,
        .alphabeticalOrder = 80,
        .enabled = TRUE
    }
};
// ===== END src/data/easy_chat/easy_chat_group_status.h =====
// ===== BEGIN src/data/easy_chat/easy_chat_group_battle.h =====

static const u8 sEasyChatWord_MatchUp[] = _("MATCH UP");
static const u8 sEasyChatWord_Go[] = _("GO");
static const u8 sEasyChatWord_No1[] = _("NO. 1");
static const u8 sEasyChatWord_Decide[] = _("DECIDE");
static const u8 sEasyChatWord_LetMeWin[] = _("LET ME WIN");
static const u8 sEasyChatWord_Wins[] = _("WINS");
static const u8 sEasyChatWord_Win[] = _("WIN");
static const u8 sEasyChatWord_Won[] = _("WON");
static const u8 sEasyChatWord_IfIWin[] = _("IF I WIN");
static const u8 sEasyChatWord_WhenIWin[] = _("WHEN I WIN");
static const u8 sEasyChatWord_CantWin[] = _("CAN'T WIN");
static const u8 sEasyChatWord_CanWin[] = _("CAN WIN");
static const u8 sEasyChatWord_NoMatch[] = _("NO MATCH");
static const u8 sEasyChatWord_Spirit[] = _("SPIRIT");
static const u8 sEasyChatWord_Decided[] = _("DECIDED");
static const u8 sEasyChatWord_TrumpCard[] = _("TRUMP CARD");
static const u8 sEasyChatWord_TakeThat[] = _("TAKE THAT");
static const u8 sEasyChatWord_ComeOn[] = _("COME ON");
static const u8 sEasyChatWord_Attack[] = _("ATTACK");
static const u8 sEasyChatWord_Surrender[] = _("SURRENDER");
static const u8 sEasyChatWord_Gutsy[] = _("GUTSY");
static const u8 sEasyChatWord_Talent[] = _("TALENT");
static const u8 sEasyChatWord_Strategy[] = _("STRATEGY");
static const u8 sEasyChatWord_Smite[] = _("SMITE");
static const u8 sEasyChatWord_Match[] = _("MATCH");
static const u8 sEasyChatWord_Victory[] = _("VICTORY");
static const u8 sEasyChatWord_Offensive[] = _("OFFENSIVE");
static const u8 sEasyChatWord_Sense[] = _("SENSE");
static const u8 sEasyChatWord_Versus[] = _("VERSUS");
static const u8 sEasyChatWord_Fights[] = _("FIGHTS");
static const u8 sEasyChatWord_Power[] = _("POWER");
static const u8 sEasyChatWord_Challenge[] = _("CHALLENGE");
static const u8 sEasyChatWord_Strong[] = _("STRONG");
static const u8 sEasyChatWord_TooStrong[] = _("TOO STRONG");
static const u8 sEasyChatWord_GoEasy[] = _("GO EASY");
static const u8 sEasyChatWord_Foe[] = _("FOE");
static const u8 sEasyChatWord_Genius[] = _("GENIUS");
static const u8 sEasyChatWord_Legend[] = _("LEGEND");
static const u8 sEasyChatWord_Escape[] = _("ESCAPE");
static const u8 sEasyChatWord_Aim[] = _("AIM");
static const u8 sEasyChatWord_Battle[] = _("BATTLE");
static const u8 sEasyChatWord_Fight[] = _("FIGHT");
static const u8 sEasyChatWord_Resuscitate[] = _("RESUSCITATE");
static const u8 sEasyChatWord_Points[] = _("POINTS");
static const u8 sEasyChatWord_Serious[] = _("SERIOUS");
static const u8 sEasyChatWord_GiveUp[] = _("GIVE UP");
static const u8 sEasyChatWord_Loss[] = _("LOSS");
static const u8 sEasyChatWord_IfILose[] = _("IF I LOSE");
static const u8 sEasyChatWord_Lost[] = _("LOST");
static const u8 sEasyChatWord_Lose[] = _("LOSE");
static const u8 sEasyChatWord_Guard[] = _("GUARD");
static const u8 sEasyChatWord_Partner[] = _("PARTNER");
static const u8 sEasyChatWord_Reject[] = _("REJECT");
static const u8 sEasyChatWord_Accept[] = _("ACCEPT");
static const u8 sEasyChatWord_Invincible[] = _("INVINCIBLE");
static const u8 sEasyChatWord_Received[] = _("RECEIVED");
static const u8 sEasyChatWord_Easy[] = _("EASY");
static const u8 sEasyChatWord_Weak[] = _("WEAK");
static const u8 sEasyChatWord_TooWeak[] = _("TOO WEAK");
static const u8 sEasyChatWord_Pushover[] = _("PUSHOVER");
static const u8 sEasyChatWord_Leader[] = _("LEADER");
static const u8 sEasyChatWord_Rule[] = _("RULE");
static const u8 sEasyChatWord_Move[] = _("MOVE");

static const struct EasyChatWordInfo sEasyChatGroup_Battle[] = {
    {
        .text = sEasyChatWord_MatchUp,
        .alphabeticalOrder = 53,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Go,
        .alphabeticalOrder = 39,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_No1,
        .alphabeticalOrder = 18,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Decide,
        .alphabeticalOrder = 40,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_LetMeWin,
        .alphabeticalOrder = 11,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Wins,
        .alphabeticalOrder = 10,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Win,
        .alphabeticalOrder = 31,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Won,
        .alphabeticalOrder = 17,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_IfIWin,
        .alphabeticalOrder = 3,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_WhenIWin,
        .alphabeticalOrder = 14,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_CantWin,
        .alphabeticalOrder = 56,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_CanWin,
        .alphabeticalOrder = 38,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_NoMatch,
        .alphabeticalOrder = 41,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Spirit,
        .alphabeticalOrder = 29,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Decided,
        .alphabeticalOrder = 35,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_TrumpCard,
        .alphabeticalOrder = 36,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_TakeThat,
        .alphabeticalOrder = 45,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_ComeOn,
        .alphabeticalOrder = 1,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Attack,
        .alphabeticalOrder = 34,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Surrender,
        .alphabeticalOrder = 50,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Gutsy,
        .alphabeticalOrder = 20,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Talent,
        .alphabeticalOrder = 47,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Strategy,
        .alphabeticalOrder = 8,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Smite,
        .alphabeticalOrder = 54,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Match,
        .alphabeticalOrder = 60,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Victory,
        .alphabeticalOrder = 37,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Offensive,
        .alphabeticalOrder = 4,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Sense,
        .alphabeticalOrder = 49,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Versus,
        .alphabeticalOrder = 46,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Fights,
        .alphabeticalOrder = 48,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Power,
        .alphabeticalOrder = 24,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Challenge,
        .alphabeticalOrder = 0,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Strong,
        .alphabeticalOrder = 62,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_TooStrong,
        .alphabeticalOrder = 12,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_GoEasy,
        .alphabeticalOrder = 2,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Foe,
        .alphabeticalOrder = 26,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Genius,
        .alphabeticalOrder = 51,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Legend,
        .alphabeticalOrder = 43,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Escape,
        .alphabeticalOrder = 30,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Aim,
        .alphabeticalOrder = 59,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Battle,
        .alphabeticalOrder = 55,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Fight,
        .alphabeticalOrder = 52,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Resuscitate,
        .alphabeticalOrder = 42,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Points,
        .alphabeticalOrder = 61,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Serious,
        .alphabeticalOrder = 27,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_GiveUp,
        .alphabeticalOrder = 44,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Loss,
        .alphabeticalOrder = 23,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_IfILose,
        .alphabeticalOrder = 13,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Lost,
        .alphabeticalOrder = 22,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Lose,
        .alphabeticalOrder = 32,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Guard,
        .alphabeticalOrder = 19,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Partner,
        .alphabeticalOrder = 16,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Reject,
        .alphabeticalOrder = 21,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Accept,
        .alphabeticalOrder = 33,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Invincible,
        .alphabeticalOrder = 58,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Received,
        .alphabeticalOrder = 15,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Easy,
        .alphabeticalOrder = 28,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Weak,
        .alphabeticalOrder = 25,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_TooWeak,
        .alphabeticalOrder = 57,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Pushover,
        .alphabeticalOrder = 9,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Leader,
        .alphabeticalOrder = 6,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Rule,
        .alphabeticalOrder = 5,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Move,
        .alphabeticalOrder = 7,
        .enabled = TRUE
    }
};
// ===== END src/data/easy_chat/easy_chat_group_battle.h =====
// ===== BEGIN src/data/easy_chat/easy_chat_group_greetings.h =====

static const u8 sEasyChatWord_Thanks[] = _("THANKS");
static const u8 sEasyChatWord_Yes[] = _("YES");
static const u8 sEasyChatWord_HereGoes[] = _("HERE GOES");
static const u8 sEasyChatWord_HereICome[] = _("HERE I COME");
static const u8 sEasyChatWord_HereItIs[] = _("HERE IT IS");
static const u8 sEasyChatWord_Yeah[] = _("YEAH");
static const u8 sEasyChatWord_Welcome[] = _("WELCOME");
static const u8 sEasyChatWord_Oi[] = _("OI");
static const u8 sEasyChatWord_HowDo[] = _("HOW DO");
static const u8 sEasyChatWord_Congrats[] = _("CONGRATS");
static const u8 sEasyChatWord_GiveMe[] = _("GIVE ME");
static const u8 sEasyChatWord_Sorry[] = _("SORRY");
static const u8 sEasyChatWord_Apologize[] = _("APOLOGIZE");
static const u8 sEasyChatWord_Forgive[] = _("FORGIVE");
static const u8 sEasyChatWord_HeyThere[] = _("HEY, THERE");
static const u8 sEasyChatWord_Hello[] = _("HELLO");
static const u8 sEasyChatWord_GoodBye[] = _("GOOD-BYE");
static const u8 sEasyChatWord_ThankYou[] = _("THANK YOU");
static const u8 sEasyChatWord_IveArrived[] = _("I'VE ARRIVED");
static const u8 sEasyChatWord_Pardon[] = _("PARDON");
static const u8 sEasyChatWord_Excuse[] = _("EXCUSE");
static const u8 sEasyChatWord_SeeYa[] = _("SEE YA");
static const u8 sEasyChatWord_ExcuseMe[] = _("EXCUSE ME");
static const u8 sEasyChatWord_WellThen[] = _("WELL, THEN");
static const u8 sEasyChatWord_GoAhead[] = _("GO AHEAD");
static const u8 sEasyChatWord_Appreciate[] = _("APPRECIATE");
static const u8 sEasyChatWord_HeyQues[] = _("HEY?");
static const u8 sEasyChatWord_WhatsUpQues[] = _("WHAT'S UP?");
static const u8 sEasyChatWord_HuhQues[] = _("HUH?");
static const u8 sEasyChatWord_No[] = _("NO");
static const u8 sEasyChatWord_Hi[] = _("HI");
static const u8 sEasyChatWord_YeahYeah[] = _("YEAH, YEAH");
static const u8 sEasyChatWord_ByeBye[] = _("BYE-BYE");
static const u8 sEasyChatWord_MeetYou[] = _("MEET YOU");
static const u8 sEasyChatWord_Hey[] = _("HEY");
static const u8 sEasyChatWord_Smell[] = _("SMELL");
static const u8 sEasyChatWord_Listening[] = _("LISTENING");
static const u8 sEasyChatWord_HooHah[] = _("HOO-HAH");
static const u8 sEasyChatWord_Yahoo[] = _("YAHOO");
static const u8 sEasyChatWord_Yo[] = _("YO");
static const u8 sEasyChatWord_ComeOver[] = _("COME OVER");
static const u8 sEasyChatWord_CountOn[] = _("COUNT ON");

static const struct EasyChatWordInfo sEasyChatGroup_Greetings[] = {
    {
        .text = sEasyChatWord_Thanks,
        .alphabeticalOrder = 12,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Yes,
        .alphabeticalOrder = 25,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_HereGoes,
        .alphabeticalOrder = 32,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_HereICome,
        .alphabeticalOrder = 40,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_HereItIs,
        .alphabeticalOrder = 9,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Yeah,
        .alphabeticalOrder = 41,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Welcome,
        .alphabeticalOrder = 20,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Oi,
        .alphabeticalOrder = 22,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_HowDo,
        .alphabeticalOrder = 13,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Congrats,
        .alphabeticalOrder = 10,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_GiveMe,
        .alphabeticalOrder = 24,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Sorry,
        .alphabeticalOrder = 16,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Apologize,
        .alphabeticalOrder = 15,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Forgive,
        .alphabeticalOrder = 2,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_HeyThere,
        .alphabeticalOrder = 3,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Hello,
        .alphabeticalOrder = 4,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_GoodBye,
        .alphabeticalOrder = 34,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_ThankYou,
        .alphabeticalOrder = 14,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_IveArrived,
        .alphabeticalOrder = 26,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Pardon,
        .alphabeticalOrder = 30,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Excuse,
        .alphabeticalOrder = 37,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_SeeYa,
        .alphabeticalOrder = 8,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_ExcuseMe,
        .alphabeticalOrder = 28,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_WellThen,
        .alphabeticalOrder = 18,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_GoAhead,
        .alphabeticalOrder = 36,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Appreciate,
        .alphabeticalOrder = 33,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_HeyQues,
        .alphabeticalOrder = 29,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_WhatsUpQues,
        .alphabeticalOrder = 7,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_HuhQues,
        .alphabeticalOrder = 19,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_No,
        .alphabeticalOrder = 21,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Hi,
        .alphabeticalOrder = 35,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_YeahYeah,
        .alphabeticalOrder = 11,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_ByeBye,
        .alphabeticalOrder = 17,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_MeetYou,
        .alphabeticalOrder = 0,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Hey,
        .alphabeticalOrder = 6,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Smell,
        .alphabeticalOrder = 23,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Listening,
        .alphabeticalOrder = 27,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_HooHah,
        .alphabeticalOrder = 38,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Yahoo,
        .alphabeticalOrder = 5,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Yo,
        .alphabeticalOrder = 31,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_ComeOver,
        .alphabeticalOrder = 1,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_CountOn,
        .alphabeticalOrder = 39,
        .enabled = TRUE
    }
};
// ===== END src/data/easy_chat/easy_chat_group_greetings.h =====
// ===== BEGIN src/data/easy_chat/easy_chat_group_people.h =====

static const u8 sEasyChatWord_Opponent[] = _("OPPONENT");
static const u8 sEasyChatWord_I[] = _("I");
static const u8 sEasyChatWord_You[] = _("YOU");
static const u8 sEasyChatWord_Yours[] = _("YOURS");
static const u8 sEasyChatWord_Son[] = _("SON");
static const u8 sEasyChatWord_Your[] = _("YOUR");
static const u8 sEasyChatWord_Youre[] = _("YOU'RE");
static const u8 sEasyChatWord_Youve[] = _("YOU'VE");
static const u8 sEasyChatWord_Mother[] = _("MOTHER");
static const u8 sEasyChatWord_Grandfather[] = _("GRANDFATHER");
static const u8 sEasyChatWord_Uncle[] = _("UNCLE");
static const u8 sEasyChatWord_Father[] = _("FATHER");
static const u8 sEasyChatWord_Boy[] = _("BOY");
static const u8 sEasyChatWord_Adult[] = _("ADULT");
static const u8 sEasyChatWord_Brother[] = _("BROTHER");
static const u8 sEasyChatWord_Sister[] = _("SISTER");
static const u8 sEasyChatWord_Grandmother[] = _("GRANDMOTHER");
static const u8 sEasyChatWord_Aunt[] = _("AUNT");
static const u8 sEasyChatWord_Parent[] = _("PARENT");
static const u8 sEasyChatWord_Man[] = _("MAN");
static const u8 sEasyChatWord_Me[] = _("ME");
static const u8 sEasyChatWord_Girl[] = _("GIRL");
static const u8 sEasyChatWord_Babe[] = _("BABE");
static const u8 sEasyChatWord_Family[] = _("FAMILY");
static const u8 sEasyChatWord_Her[] = _("HER");
static const u8 sEasyChatWord_Him[] = _("HIM");
static const u8 sEasyChatWord_He[] = _("HE");
static const u8 sEasyChatWord_Place[] = _("PLACE");
static const u8 sEasyChatWord_Daughter[] = _("DAUGHTER");
static const u8 sEasyChatWord_His[] = _("HIS");
static const u8 sEasyChatWord_Hes[] = _("HE'S");
static const u8 sEasyChatWord_Arent[] = _("AREN'T");
static const u8 sEasyChatWord_Siblings[] = _("SIBLINGS");
static const u8 sEasyChatWord_Kid[] = _("KID");
static const u8 sEasyChatWord_Children[] = _("CHILDREN");
static const u8 sEasyChatWord_Mr[] = _("MR.");
static const u8 sEasyChatWord_Mrs[] = _("MRS.");
static const u8 sEasyChatWord_Myself[] = _("MYSELF");
static const u8 sEasyChatWord_IWas[] = _("I WAS");
static const u8 sEasyChatWord_ToMe[] = _("TO ME");
static const u8 sEasyChatWord_My[] = _("MY");
static const u8 sEasyChatWord_IAm[] = _("I AM");
static const u8 sEasyChatWord_Ive[] = _("I'VE");
static const u8 sEasyChatWord_Who[] = _("WHO");
static const u8 sEasyChatWord_Someone[] = _("SOMEONE");
static const u8 sEasyChatWord_WhoWas[] = _("WHO WAS");
static const u8 sEasyChatWord_ToWhom[] = _("TO WHOM");
static const u8 sEasyChatWord_Whose[] = _("WHOSE");
static const u8 sEasyChatWord_WhoIs[] = _("WHO IS");
static const u8 sEasyChatWord_Its[] = _("IT'S");
static const u8 sEasyChatWord_Lady[] = _("LADY");
static const u8 sEasyChatWord_Friend[] = _("FRIEND");
static const u8 sEasyChatWord_Ally[] = _("ALLY");
static const u8 sEasyChatWord_Person[] = _("PERSON");
static const u8 sEasyChatWord_Dude[] = _("DUDE");
static const u8 sEasyChatWord_They[] = _("THEY");
static const u8 sEasyChatWord_TheyWere[] = _("THEY WERE");
static const u8 sEasyChatWord_ToThem[] = _("TO THEM");
static const u8 sEasyChatWord_Their[] = _("THEIR");
static const u8 sEasyChatWord_Theyre[] = _("THEY'RE");
static const u8 sEasyChatWord_Theyve[] = _("THEY'VE");
static const u8 sEasyChatWord_We[] = _("WE");
static const u8 sEasyChatWord_Been[] = _("BEEN");
static const u8 sEasyChatWord_ToUs[] = _("TO US");
static const u8 sEasyChatWord_Our[] = _("OUR");
static const u8 sEasyChatWord_WeAre[] = _("WE'RE");
static const u8 sEasyChatWord_Rival[] = _("RIVAL");
static const u8 sEasyChatWord_Weve[] = _("WE'VE");
static const u8 sEasyChatWord_Woman[] = _("WOMAN");
static const u8 sEasyChatWord_She[] = _("SHE");
static const u8 sEasyChatWord_SheWas[] = _("SHE WAS");
static const u8 sEasyChatWord_ToHer[] = _("TO HER");
static const u8 sEasyChatWord_Hers[] = _("HERS");
static const u8 sEasyChatWord_SheIs[] = _("SHE IS");
static const u8 sEasyChatWord_Some[] = _("SOME");

static const struct EasyChatWordInfo sEasyChatGroup_People[] = {
    {
        .text = sEasyChatWord_Opponent,
        .alphabeticalOrder = 13,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_I,
        .alphabeticalOrder = 52,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_You,
        .alphabeticalOrder = 31,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Yours,
        .alphabeticalOrder = 17,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Son,
        .alphabeticalOrder = 22,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Your,
        .alphabeticalOrder = 62,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Youre,
        .alphabeticalOrder = 12,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Youve,
        .alphabeticalOrder = 14,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Mother,
        .alphabeticalOrder = 34,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Grandfather,
        .alphabeticalOrder = 28,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Uncle,
        .alphabeticalOrder = 54,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Father,
        .alphabeticalOrder = 23,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Boy,
        .alphabeticalOrder = 11,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Adult,
        .alphabeticalOrder = 51,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Brother,
        .alphabeticalOrder = 21,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Sister,
        .alphabeticalOrder = 9,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Grandmother,
        .alphabeticalOrder = 16,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Aunt,
        .alphabeticalOrder = 26,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Parent,
        .alphabeticalOrder = 30,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Man,
        .alphabeticalOrder = 24,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Me,
        .alphabeticalOrder = 72,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Girl,
        .alphabeticalOrder = 25,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Babe,
        .alphabeticalOrder = 29,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Family,
        .alphabeticalOrder = 1,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Her,
        .alphabeticalOrder = 41,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Him,
        .alphabeticalOrder = 38,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_He,
        .alphabeticalOrder = 42,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Place,
        .alphabeticalOrder = 49,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Daughter,
        .alphabeticalOrder = 33,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_His,
        .alphabeticalOrder = 50,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Hes,
        .alphabeticalOrder = 19,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Arent,
        .alphabeticalOrder = 20,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Siblings,
        .alphabeticalOrder = 8,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Kid,
        .alphabeticalOrder = 35,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Children,
        .alphabeticalOrder = 36,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Mr,
        .alphabeticalOrder = 40,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Mrs,
        .alphabeticalOrder = 37,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Myself,
        .alphabeticalOrder = 0,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_IWas,
        .alphabeticalOrder = 64,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_ToMe,
        .alphabeticalOrder = 18,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_My,
        .alphabeticalOrder = 53,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_IAm,
        .alphabeticalOrder = 27,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Ive,
        .alphabeticalOrder = 66,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Who,
        .alphabeticalOrder = 69,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Someone,
        .alphabeticalOrder = 73,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_WhoWas,
        .alphabeticalOrder = 70,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_ToWhom,
        .alphabeticalOrder = 32,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Whose,
        .alphabeticalOrder = 15,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_WhoIs,
        .alphabeticalOrder = 74,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Its,
        .alphabeticalOrder = 44,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Lady,
        .alphabeticalOrder = 4,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Friend,
        .alphabeticalOrder = 58,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Ally,
        .alphabeticalOrder = 55,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Person,
        .alphabeticalOrder = 56,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Dude,
        .alphabeticalOrder = 59,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_They,
        .alphabeticalOrder = 60,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_TheyWere,
        .alphabeticalOrder = 71,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_ToThem,
        .alphabeticalOrder = 39,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Their,
        .alphabeticalOrder = 57,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Theyre,
        .alphabeticalOrder = 63,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Theyve,
        .alphabeticalOrder = 46,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_We,
        .alphabeticalOrder = 10,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Been,
        .alphabeticalOrder = 61,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_ToUs,
        .alphabeticalOrder = 65,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Our,
        .alphabeticalOrder = 67,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_WeAre,
        .alphabeticalOrder = 43,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Rival,
        .alphabeticalOrder = 48,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Weve,
        .alphabeticalOrder = 45,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Woman,
        .alphabeticalOrder = 47,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_She,
        .alphabeticalOrder = 68,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_SheWas,
        .alphabeticalOrder = 2,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_ToHer,
        .alphabeticalOrder = 6,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Hers,
        .alphabeticalOrder = 7,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_SheIs,
        .alphabeticalOrder = 5,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Some,
        .alphabeticalOrder = 3,
        .enabled = TRUE
    }
};
// ===== END src/data/easy_chat/easy_chat_group_people.h =====
// ===== BEGIN src/data/easy_chat/easy_chat_group_voices.h =====

static const u8 sEasyChatWord_Excl[] = _("!");
static const u8 sEasyChatWord_ExclExcl[] = _("!!");
static const u8 sEasyChatWord_QuesExcl[] = _("?!");
static const u8 sEasyChatWord_Ques[] = _("?");
static const u8 sEasyChatWord_Ellipsis[] = _("…");
static const u8 sEasyChatWord_EllipsisExcl[] = _("…!");
static const u8 sEasyChatWord_EllipsisEllipsisEllipsis[] = _("………");
static const u8 sEasyChatWord_Dash[] = _("-");
static const u8 sEasyChatWord_DashDashDash[] = _("- - -");
static const u8 sEasyChatWord_UhOh[] = _("UH-OH");
static const u8 sEasyChatWord_Waaah[] = _("WAAAH");
static const u8 sEasyChatWord_Ahaha[] = _("AHAHA");
static const u8 sEasyChatWord_OhQues[] = _("OH?");
static const u8 sEasyChatWord_Nope[] = _("NOPE");
static const u8 sEasyChatWord_Urgh[] = _("URGH");
static const u8 sEasyChatWord_Hmm[] = _("HMM");
static const u8 sEasyChatWord_Whoah[] = _("WHOAH");
static const u8 sEasyChatWord_WroooaarExcl[] = _("WROOOAAR!");
static const u8 sEasyChatWord_Wow[] = _("WOW");
static const u8 sEasyChatWord_Giggle[] = _("GIGGLE");
static const u8 sEasyChatWord_Sigh[] = _("SIGH");
static const u8 sEasyChatWord_Unbelievable[] = _("UNBELIEVABLE");
static const u8 sEasyChatWord_Cries[] = _("CRIES");
static const u8 sEasyChatWord_Agree[] = _("AGREE");
static const u8 sEasyChatWord_EhQues[] = _("EH?");
static const u8 sEasyChatWord_Cry[] = _("CRY");
static const u8 sEasyChatWord_Ehehe[] = _("EHEHE");
static const u8 sEasyChatWord_OiOiOi[] = _("OI, OI, OI");
static const u8 sEasyChatWord_OhYeah[] = _("OH, YEAH");
static const u8 sEasyChatWord_Oh[] = _("OH");
static const u8 sEasyChatWord_Oops[] = _("OOPS");
static const u8 sEasyChatWord_Shocked[] = _("SHOCKED");
static const u8 sEasyChatWord_Eek[] = _("EEK");
static const u8 sEasyChatWord_Graaah[] = _("GRAAAH");
static const u8 sEasyChatWord_Gwahahaha[] = _("GWAHAHAHA");
static const u8 sEasyChatWord_Way[] = _("WAY");
static const u8 sEasyChatWord_Tch[] = _("TCH");
static const u8 sEasyChatWord_Hehe[] = _("HEHE");
static const u8 sEasyChatWord_Hah[] = _("HAH");
static const u8 sEasyChatWord_Yup[] = _("YUP");
static const u8 sEasyChatWord_Hahaha[] = _("HAHAHA");
static const u8 sEasyChatWord_Aiyeeh[] = _("AIYEEH");
static const u8 sEasyChatWord_Hiyah[] = _("HIYAH");
static const u8 sEasyChatWord_Fufufu[] = _("FUFUFU");
static const u8 sEasyChatWord_Lol[] = _("LOL");
static const u8 sEasyChatWord_Snort[] = _("SNORT");
static const u8 sEasyChatWord_Humph[] = _("HUMPH");
static const u8 sEasyChatWord_Hehehe[] = _("HEHEHE");
static const u8 sEasyChatWord_Heh[] = _("HEH");
static const u8 sEasyChatWord_Hohoho[] = _("HOHOHO");
static const u8 sEasyChatWord_UhHuh[] = _("UH-HUH");
static const u8 sEasyChatWord_OhDear[] = _("OH, DEAR");
static const u8 sEasyChatWord_Arrgh[] = _("ARRGH");
static const u8 sEasyChatWord_Mufufu[] = _("MUFUFU");
static const u8 sEasyChatWord_Mmm[] = _("MMM");
static const u8 sEasyChatWord_OhKay[] = _("OH-KAY");
static const u8 sEasyChatWord_Okay[] = _("OKAY");
static const u8 sEasyChatWord_Lalala[] = _("LALALA");
static const u8 sEasyChatWord_Yay[] = _("YAY");
static const u8 sEasyChatWord_Aww[] = _("AWW");
static const u8 sEasyChatWord_Wowee[] = _("WOWEE");
static const u8 sEasyChatWord_Gwah[] = _("GWAH");
static const u8 sEasyChatWord_Wahahaha[] = _("WAHAHAHA");

static const struct EasyChatWordInfo sEasyChatGroup_Voices[] = {
    {
        .text = sEasyChatWord_Excl,
        .alphabeticalOrder = 0,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_ExclExcl,
        .alphabeticalOrder = 1,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_QuesExcl,
        .alphabeticalOrder = 7,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Ques,
        .alphabeticalOrder = 8,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Ellipsis,
        .alphabeticalOrder = 4,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_EllipsisExcl,
        .alphabeticalOrder = 5,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_EllipsisEllipsisEllipsis,
        .alphabeticalOrder = 6,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Dash,
        .alphabeticalOrder = 3,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_DashDashDash,
        .alphabeticalOrder = 2,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_UhOh,
        .alphabeticalOrder = 23,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Waaah,
        .alphabeticalOrder = 11,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Ahaha,
        .alphabeticalOrder = 41,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_OhQues,
        .alphabeticalOrder = 52,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Nope,
        .alphabeticalOrder = 59,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Urgh,
        .alphabeticalOrder = 22,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Hmm,
        .alphabeticalOrder = 25,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Whoah,
        .alphabeticalOrder = 32,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_WroooaarExcl,
        .alphabeticalOrder = 24,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Wow,
        .alphabeticalOrder = 26,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Giggle,
        .alphabeticalOrder = 43,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Sigh,
        .alphabeticalOrder = 19,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Unbelievable,
        .alphabeticalOrder = 33,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Cries,
        .alphabeticalOrder = 61,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Agree,
        .alphabeticalOrder = 34,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_EhQues,
        .alphabeticalOrder = 38,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Cry,
        .alphabeticalOrder = 40,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Ehehe,
        .alphabeticalOrder = 48,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_OiOiOi,
        .alphabeticalOrder = 37,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_OhYeah,
        .alphabeticalOrder = 47,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Oh,
        .alphabeticalOrder = 42,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Oops,
        .alphabeticalOrder = 15,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Shocked,
        .alphabeticalOrder = 49,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Eek,
        .alphabeticalOrder = 46,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Graaah,
        .alphabeticalOrder = 57,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Gwahahaha,
        .alphabeticalOrder = 44,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Way,
        .alphabeticalOrder = 54,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Tch,
        .alphabeticalOrder = 53,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Hehe,
        .alphabeticalOrder = 13,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Hah,
        .alphabeticalOrder = 29,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Yup,
        .alphabeticalOrder = 51,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Hahaha,
        .alphabeticalOrder = 28,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Aiyeeh,
        .alphabeticalOrder = 55,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Hiyah,
        .alphabeticalOrder = 12,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Fufufu,
        .alphabeticalOrder = 27,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Lol,
        .alphabeticalOrder = 56,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Snort,
        .alphabeticalOrder = 30,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Humph,
        .alphabeticalOrder = 31,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Hehehe,
        .alphabeticalOrder = 20,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Heh,
        .alphabeticalOrder = 45,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Hohoho,
        .alphabeticalOrder = 36,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_UhHuh,
        .alphabeticalOrder = 50,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_OhDear,
        .alphabeticalOrder = 9,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Arrgh,
        .alphabeticalOrder = 21,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Mufufu,
        .alphabeticalOrder = 14,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Mmm,
        .alphabeticalOrder = 10,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_OhKay,
        .alphabeticalOrder = 62,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Okay,
        .alphabeticalOrder = 35,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Lalala,
        .alphabeticalOrder = 16,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Yay,
        .alphabeticalOrder = 18,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Aww,
        .alphabeticalOrder = 60,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Wowee,
        .alphabeticalOrder = 17,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Gwah,
        .alphabeticalOrder = 58,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Wahahaha,
        .alphabeticalOrder = 39,
        .enabled = TRUE
    }
};
// ===== END src/data/easy_chat/easy_chat_group_voices.h =====
// ===== BEGIN src/data/easy_chat/easy_chat_group_speech.h =====

static const u8 sEasyChatWord_Listen[] = _("LISTEN");
static const u8 sEasyChatWord_NotVery[] = _("NOT VERY");
static const u8 sEasyChatWord_Mean[] = _("MEAN");
static const u8 sEasyChatWord_Lie[] = _("LIE");
static const u8 sEasyChatWord_Lay[] = _("LAY");
static const u8 sEasyChatWord_Recommend[] = _("RECOMMEND");
static const u8 sEasyChatWord_Nitwit[] = _("NITWIT");
static const u8 sEasyChatWord_Quite[] = _("QUITE");
static const u8 sEasyChatWord_From[] = _("FROM");
static const u8 sEasyChatWord_Feeling[] = _("FEELING");
static const u8 sEasyChatWord_But[] = _("BUT");
static const u8 sEasyChatWord_However[] = _("HOWEVER");
static const u8 sEasyChatWord_Case[] = _("CASE");
static const u8 sEasyChatWord_The[] = _("THE");
static const u8 sEasyChatWord_Miss[] = _("MISS");
static const u8 sEasyChatWord_How[] = _("HOW");
static const u8 sEasyChatWord_Hit[] = _("HIT");
static const u8 sEasyChatWord_Enough[] = _("ENOUGH");
static const u8 sEasyChatWord_ALot[] = _("A LOT");
static const u8 sEasyChatWord_ALittle[] = _("A LITTLE");
static const u8 sEasyChatWord_Absolutely[] = _("ABSOLUTELY");
static const u8 sEasyChatWord_And[] = _("AND");
static const u8 sEasyChatWord_Only[] = _("ONLY");
static const u8 sEasyChatWord_Around[] = _("AROUND");
static const u8 sEasyChatWord_Probably[] = _("PROBABLY");
static const u8 sEasyChatWord_If[] = _("IF");
static const u8 sEasyChatWord_Very[] = _("VERY");
static const u8 sEasyChatWord_ATinyBit[] = _("A TINY BIT");
static const u8 sEasyChatWord_Wild[] = _("WILD");
static const u8 sEasyChatWord_Thats[] = _("THAT'S");
static const u8 sEasyChatWord_Just[] = _("JUST");
static const u8 sEasyChatWord_EvenSo[] = _("EVEN SO,");
static const u8 sEasyChatWord_MustBe[] = _("MUST BE");
static const u8 sEasyChatWord_Naturally[] = _("NATURALLY");
static const u8 sEasyChatWord_ForNow[] = _("FOR NOW,");
static const u8 sEasyChatWord_Understood[] = _("UNDERSTOOD");
static const u8 sEasyChatWord_Joking[] = _("JOKING");
static const u8 sEasyChatWord_Ready[] = _("READY");
static const u8 sEasyChatWord_Something[] = _("SOMETHING");
static const u8 sEasyChatWord_Somehow[] = _("SOMEHOW");
static const u8 sEasyChatWord_Although[] = _("ALTHOUGH");
static const u8 sEasyChatWord_Also[] = _("ALSO");
static const u8 sEasyChatWord_Perfect[] = _("PERFECT");
static const u8 sEasyChatWord_AsMuchAs[] = _("AS MUCH AS");
static const u8 sEasyChatWord_Really[] = _("REALLY");
static const u8 sEasyChatWord_Truly[] = _("TRULY");
static const u8 sEasyChatWord_Seriously[] = _("SERIOUSLY");
static const u8 sEasyChatWord_Totally[] = _("TOTALLY");
static const u8 sEasyChatWord_Until[] = _("UNTIL");
static const u8 sEasyChatWord_AsIf[] = _("AS IF");
static const u8 sEasyChatWord_Mood[] = _("MOOD");
static const u8 sEasyChatWord_Rather[] = _("RATHER");
static const u8 sEasyChatWord_Awfully[] = _("AWFULLY");
static const u8 sEasyChatWord_Mode[] = _("MODE");
static const u8 sEasyChatWord_More[] = _("MORE");
static const u8 sEasyChatWord_TooLate[] = _("TOO LATE");
static const u8 sEasyChatWord_Finally[] = _("FINALLY");
static const u8 sEasyChatWord_Any[] = _("ANY");
static const u8 sEasyChatWord_Instead[] = _("INSTEAD");
static const u8 sEasyChatWord_Fantastic[] = _("FANTASTIC");

static const struct EasyChatWordInfo sEasyChatGroup_Speech[] = {
    {
        .text = sEasyChatWord_Listen,
        .alphabeticalOrder = 19,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_NotVery,
        .alphabeticalOrder = 18,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Mean,
        .alphabeticalOrder = 27,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Lie,
        .alphabeticalOrder = 20,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Lay,
        .alphabeticalOrder = 41,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Recommend,
        .alphabeticalOrder = 40,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Nitwit,
        .alphabeticalOrder = 21,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Quite,
        .alphabeticalOrder = 57,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_From,
        .alphabeticalOrder = 23,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Feeling,
        .alphabeticalOrder = 49,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_But,
        .alphabeticalOrder = 43,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_However,
        .alphabeticalOrder = 52,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Case,
        .alphabeticalOrder = 10,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_The,
        .alphabeticalOrder = 12,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Miss,
        .alphabeticalOrder = 17,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_How,
        .alphabeticalOrder = 31,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Hit,
        .alphabeticalOrder = 59,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Enough,
        .alphabeticalOrder = 9,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_ALot,
        .alphabeticalOrder = 56,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_ALittle,
        .alphabeticalOrder = 34,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Absolutely,
        .alphabeticalOrder = 8,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_And,
        .alphabeticalOrder = 16,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Only,
        .alphabeticalOrder = 15,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Around,
        .alphabeticalOrder = 11,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Probably,
        .alphabeticalOrder = 25,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_If,
        .alphabeticalOrder = 58,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Very,
        .alphabeticalOrder = 36,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_ATinyBit,
        .alphabeticalOrder = 30,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Wild,
        .alphabeticalOrder = 4,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Thats,
        .alphabeticalOrder = 3,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Just,
        .alphabeticalOrder = 0,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_EvenSo,
        .alphabeticalOrder = 2,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_MustBe,
        .alphabeticalOrder = 14,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Naturally,
        .alphabeticalOrder = 53,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_ForNow,
        .alphabeticalOrder = 50,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Understood,
        .alphabeticalOrder = 54,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Joking,
        .alphabeticalOrder = 32,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Ready,
        .alphabeticalOrder = 33,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Something,
        .alphabeticalOrder = 6,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Somehow,
        .alphabeticalOrder = 1,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Although,
        .alphabeticalOrder = 22,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Also,
        .alphabeticalOrder = 42,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Perfect,
        .alphabeticalOrder = 24,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_AsMuchAs,
        .alphabeticalOrder = 7,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Really,
        .alphabeticalOrder = 51,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Truly,
        .alphabeticalOrder = 37,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Seriously,
        .alphabeticalOrder = 44,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Totally,
        .alphabeticalOrder = 5,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Until,
        .alphabeticalOrder = 46,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_AsIf,
        .alphabeticalOrder = 39,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Mood,
        .alphabeticalOrder = 38,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Rather,
        .alphabeticalOrder = 29,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Awfully,
        .alphabeticalOrder = 13,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Mode,
        .alphabeticalOrder = 55,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_More,
        .alphabeticalOrder = 47,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_TooLate,
        .alphabeticalOrder = 45,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Finally,
        .alphabeticalOrder = 35,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Any,
        .alphabeticalOrder = 48,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Instead,
        .alphabeticalOrder = 26,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Fantastic,
        .alphabeticalOrder = 28,
        .enabled = TRUE
    }
};
// ===== END src/data/easy_chat/easy_chat_group_speech.h =====
// ===== BEGIN src/data/easy_chat/easy_chat_group_endings.h =====

static const u8 sEasyChatWord_Will[] = _("WILL");
static const u8 sEasyChatWord_WillBeHere[] = _("WILL BE HERE");
static const u8 sEasyChatWord_Or[] = _("OR");
static const u8 sEasyChatWord_Times[] = _("TIMES");
static const u8 sEasyChatWord_Wonder[] = _("WONDER");
static const u8 sEasyChatWord_IsItQues[] = _("IS IT?");
static const u8 sEasyChatWord_Be[] = _("BE");
static const u8 sEasyChatWord_Gimme[] = _("GIMME");
static const u8 sEasyChatWord_Could[] = _("COULD");
static const u8 sEasyChatWord_LikelyTo[] = _("LIKELY TO");
static const u8 sEasyChatWord_Would[] = _("WOULD");
static const u8 sEasyChatWord_Is[] = _("IS");
static const u8 sEasyChatWord_IsntItQues[] = _("ISN'T IT?");
static const u8 sEasyChatWord_Lets[] = _("LET'S");
static const u8 sEasyChatWord_Other[] = _("OTHER");
static const u8 sEasyChatWord_Are[] = _("ARE");
static const u8 sEasyChatWord_Was[] = _("WAS");
static const u8 sEasyChatWord_Were[] = _("WERE");
static const u8 sEasyChatWord_Those[] = _("THOSE");
static const u8 sEasyChatWord_Isnt[] = _("ISN'T");
static const u8 sEasyChatWord_Wont[] = _("WON'T");
static const u8 sEasyChatWord_Cant[] = _("CAN'T");
static const u8 sEasyChatWord_Can[] = _("CAN");
static const u8 sEasyChatWord_Dont[] = _("DON'T");
static const u8 sEasyChatWord_Do[] = _("DO");
static const u8 sEasyChatWord_Does[] = _("DOES");
static const u8 sEasyChatWord_Whom[] = _("WHOM");
static const u8 sEasyChatWord_Which[] = _("WHICH");
static const u8 sEasyChatWord_Wasnt[] = _("WASN'T");
static const u8 sEasyChatWord_Werent[] = _("WEREN'T");
static const u8 sEasyChatWord_Have[] = _("HAVE");
static const u8 sEasyChatWord_Havent[] = _("HAVEN'T");
static const u8 sEasyChatWord_A[] = _("A");
static const u8 sEasyChatWord_An[] = _("AN");
static const u8 sEasyChatWord_Not[] = _("NOT");
static const u8 sEasyChatWord_There[] = _("THERE");
static const u8 sEasyChatWord_OkQues[] = _("OK?");
static const u8 sEasyChatWord_So[] = _("SO");
static const u8 sEasyChatWord_Maybe[] = _("MAYBE");
static const u8 sEasyChatWord_About[] = _("ABOUT");
static const u8 sEasyChatWord_Over[] = _("OVER");
static const u8 sEasyChatWord_It[] = _("IT");
static const u8 sEasyChatWord_All[] = _("ALL");
static const u8 sEasyChatWord_For[] = _("FOR");
static const u8 sEasyChatWord_On[] = _("ON");
static const u8 sEasyChatWord_Off[] = _("OFF");
static const u8 sEasyChatWord_As[] = _("AS");
static const u8 sEasyChatWord_To[] = _("TO");
static const u8 sEasyChatWord_With[] = _("WITH");
static const u8 sEasyChatWord_Better[] = _("BETTER");
static const u8 sEasyChatWord_Ever[] = _("EVER");
static const u8 sEasyChatWord_Since[] = _("SINCE");
static const u8 sEasyChatWord_Of[] = _("OF");
static const u8 sEasyChatWord_BelongsTo[] = _("BELONGS TO");
static const u8 sEasyChatWord_At[] = _("AT");
static const u8 sEasyChatWord_In[] = _("IN");
static const u8 sEasyChatWord_Out[] = _("OUT");
static const u8 sEasyChatWord_Too[] = _("TOO");
static const u8 sEasyChatWord_Like[] = _("LIKE");
static const u8 sEasyChatWord_Did[] = _("DID");
static const u8 sEasyChatWord_Didnt[] = _("DIDN'T");
static const u8 sEasyChatWord_Doesnt[] = _("DOESN'T");
static const u8 sEasyChatWord_Without[] = _("WITHOUT");
static const u8 sEasyChatWord_After[] = _("AFTER");
static const u8 sEasyChatWord_Before[] = _("BEFORE");
static const u8 sEasyChatWord_While[] = _("WHILE");
static const u8 sEasyChatWord_Than[] = _("THAN");
static const u8 sEasyChatWord_Once[] = _("ONCE");
static const u8 sEasyChatWord_Anywhere[] = _("ANYWHERE");

static const struct EasyChatWordInfo sEasyChatGroup_Endings[] = {
    {
        .text = sEasyChatWord_Will,
        .alphabeticalOrder = 32,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_WillBeHere,
        .alphabeticalOrder = 39,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Or,
        .alphabeticalOrder = 63,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Times,
        .alphabeticalOrder = 42,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Wonder,
        .alphabeticalOrder = 33,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_IsItQues,
        .alphabeticalOrder = 68,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Be,
        .alphabeticalOrder = 15,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Gimme,
        .alphabeticalOrder = 46,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Could,
        .alphabeticalOrder = 54,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_LikelyTo,
        .alphabeticalOrder = 6,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Would,
        .alphabeticalOrder = 64,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Is,
        .alphabeticalOrder = 53,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_IsntItQues,
        .alphabeticalOrder = 49,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Lets,
        .alphabeticalOrder = 22,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Other,
        .alphabeticalOrder = 21,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Are,
        .alphabeticalOrder = 8,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Was,
        .alphabeticalOrder = 59,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Were,
        .alphabeticalOrder = 60,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Those,
        .alphabeticalOrder = 24,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Isnt,
        .alphabeticalOrder = 25,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Wont,
        .alphabeticalOrder = 61,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Cant,
        .alphabeticalOrder = 23,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Can,
        .alphabeticalOrder = 50,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Dont,
        .alphabeticalOrder = 43,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Do,
        .alphabeticalOrder = 7,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Does,
        .alphabeticalOrder = 30,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Whom,
        .alphabeticalOrder = 31,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Which,
        .alphabeticalOrder = 55,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Wasnt,
        .alphabeticalOrder = 11,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Werent,
        .alphabeticalOrder = 5,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Have,
        .alphabeticalOrder = 19,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Havent,
        .alphabeticalOrder = 12,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_A,
        .alphabeticalOrder = 41,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_An,
        .alphabeticalOrder = 13,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Not,
        .alphabeticalOrder = 58,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_There,
        .alphabeticalOrder = 9,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_OkQues,
        .alphabeticalOrder = 38,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_So,
        .alphabeticalOrder = 34,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Maybe,
        .alphabeticalOrder = 52,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_About,
        .alphabeticalOrder = 45,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Over,
        .alphabeticalOrder = 36,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_It,
        .alphabeticalOrder = 44,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_All,
        .alphabeticalOrder = 67,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_For,
        .alphabeticalOrder = 2,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_On,
        .alphabeticalOrder = 14,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Off,
        .alphabeticalOrder = 56,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_As,
        .alphabeticalOrder = 40,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_To,
        .alphabeticalOrder = 51,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_With,
        .alphabeticalOrder = 37,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Better,
        .alphabeticalOrder = 66,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Ever,
        .alphabeticalOrder = 35,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Since,
        .alphabeticalOrder = 18,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Of,
        .alphabeticalOrder = 3,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_BelongsTo,
        .alphabeticalOrder = 47,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_At,
        .alphabeticalOrder = 57,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_In,
        .alphabeticalOrder = 16,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Out,
        .alphabeticalOrder = 28,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Too,
        .alphabeticalOrder = 17,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Like,
        .alphabeticalOrder = 29,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Did,
        .alphabeticalOrder = 27,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Didnt,
        .alphabeticalOrder = 65,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Doesnt,
        .alphabeticalOrder = 26,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Without,
        .alphabeticalOrder = 0,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_After,
        .alphabeticalOrder = 1,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Before,
        .alphabeticalOrder = 48,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_While,
        .alphabeticalOrder = 62,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Than,
        .alphabeticalOrder = 20,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Once,
        .alphabeticalOrder = 4,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Anywhere,
        .alphabeticalOrder = 10,
        .enabled = TRUE
    }
};
// ===== END src/data/easy_chat/easy_chat_group_endings.h =====
// ===== BEGIN src/data/easy_chat/easy_chat_group_feelings.h =====

static const u8 sEasyChatWord_Meet[] = _("MEET");
static const u8 sEasyChatWord_Play[] = _("PLAY");
static const u8 sEasyChatWord_Hurried[] = _("HURRIED");
static const u8 sEasyChatWord_Goes[] = _("GOES");
static const u8 sEasyChatWord_Giddy[] = _("GIDDY");
static const u8 sEasyChatWord_Happy[] = _("HAPPY");
static const u8 sEasyChatWord_Happiness[] = _("HAPPINESS");
static const u8 sEasyChatWord_Excite[] = _("EXCITE");
static const u8 sEasyChatWord_Important[] = _("IMPORTANT");
static const u8 sEasyChatWord_Funny[] = _("FUNNY");
static const u8 sEasyChatWord_Got[] = _("GOT");
static const u8 sEasyChatWord_GoHome[] = _("GO HOME");
static const u8 sEasyChatWord_Disappointed[] = _("DISAPPOINTED");
static const u8 sEasyChatWord_Disappoints[] = _("DISAPPOINTS");
static const u8 sEasyChatWord_Sad[] = _("SAD");
static const u8 sEasyChatWord_Try[] = _("TRY");
static const u8 sEasyChatWord_Tries[] = _("TRIES");
static const u8 sEasyChatWord_Hears[] = _("HEARS");
static const u8 sEasyChatWord_Think[] = _("THINK");
static const u8 sEasyChatWord_Hear[] = _("HEAR");
static const u8 sEasyChatWord_Wants[] = _("WANTS");
static const u8 sEasyChatWord_Misheard[] = _("MISHEARD");
static const u8 sEasyChatWord_Dislike[] = _("DISLIKE");
static const u8 sEasyChatWord_Angry[] = _("ANGRY");
static const u8 sEasyChatWord_Anger[] = _("ANGER");
static const u8 sEasyChatWord_Scary[] = _("SCARY");
static const u8 sEasyChatWord_Lonesome[] = _("LONESOME");
static const u8 sEasyChatWord_Disappoint[] = _("DISAPPOINT");
static const u8 sEasyChatWord_Joy[] = _("JOY");
static const u8 sEasyChatWord_Gets[] = _("GETS");
static const u8 sEasyChatWord_Never[] = _("NEVER");
static const u8 sEasyChatWord_Darn[] = _("DARN");
static const u8 sEasyChatWord_Downcast[] = _("DOWNCAST");
static const u8 sEasyChatWord_Incredible[] = _("INCREDIBLE");
static const u8 sEasyChatWord_Likes[] = _("LIKES");
static const u8 sEasyChatWord_Dislikes[] = _("DISLIKES");
static const u8 sEasyChatWord_Boring[] = _("BORING");
static const u8 sEasyChatWord_Care[] = _("CARE");
static const u8 sEasyChatWord_Cares[] = _("CARES");
static const u8 sEasyChatWord_AllRight[] = _("ALL RIGHT");
static const u8 sEasyChatWord_Adore[] = _("ADORE");
static const u8 sEasyChatWord_Disaster[] = _("DISASTER");
static const u8 sEasyChatWord_Enjoy[] = _("ENJOY");
static const u8 sEasyChatWord_Enjoys[] = _("ENJOYS");
static const u8 sEasyChatWord_Eat[] = _("EAT");
static const u8 sEasyChatWord_Lacking[] = _("LACKING");
static const u8 sEasyChatWord_Bad[] = _("BAD");
static const u8 sEasyChatWord_Hard[] = _("HARD");
static const u8 sEasyChatWord_Terrible[] = _("TERRIBLE");
static const u8 sEasyChatWord_Should[] = _("SHOULD");
static const u8 sEasyChatWord_Nice[] = _("NICE");
static const u8 sEasyChatWord_Drink[] = _("DRINK");
static const u8 sEasyChatWord_Surprise[] = _("SURPRISE");
static const u8 sEasyChatWord_Fear[] = _("FEAR");
static const u8 sEasyChatWord_Want[] = _("WANT");
static const u8 sEasyChatWord_Wait[] = _("WAIT");
static const u8 sEasyChatWord_Satisfied[] = _("SATISFIED");
static const u8 sEasyChatWord_See[] = _("SEE");
static const u8 sEasyChatWord_Rare[] = _("RARE");
static const u8 sEasyChatWord_Negative[] = _("NEGATIVE");
static const u8 sEasyChatWord_Done[] = _("DONE");
static const u8 sEasyChatWord_Danger[] = _("DANGER");
static const u8 sEasyChatWord_Defeated[] = _("DEFEATED");
static const u8 sEasyChatWord_Beat[] = _("BEAT");
static const u8 sEasyChatWord_Great[] = _("GREAT");
static const u8 sEasyChatWord_Romantic[] = _("ROMANTIC");
static const u8 sEasyChatWord_Question[] = _("QUESTION");
static const u8 sEasyChatWord_Understand[] = _("UNDERSTAND");
static const u8 sEasyChatWord_Understands[] = _("UNDERSTANDS");

static const struct EasyChatWordInfo sEasyChatGroup_Feelings[] = {
    {
        .text = sEasyChatWord_Meet,
        .alphabeticalOrder = 40,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Play,
        .alphabeticalOrder = 39,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Hurried,
        .alphabeticalOrder = 24,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Goes,
        .alphabeticalOrder = 23,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Giddy,
        .alphabeticalOrder = 46,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Happy,
        .alphabeticalOrder = 63,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Happiness,
        .alphabeticalOrder = 36,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Excite,
        .alphabeticalOrder = 37,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Important,
        .alphabeticalOrder = 38,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Funny,
        .alphabeticalOrder = 61,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Got,
        .alphabeticalOrder = 31,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_GoHome,
        .alphabeticalOrder = 62,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Disappointed,
        .alphabeticalOrder = 27,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Disappoints,
        .alphabeticalOrder = 12,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Sad,
        .alphabeticalOrder = 13,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Try,
        .alphabeticalOrder = 41,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Tries,
        .alphabeticalOrder = 22,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Hears,
        .alphabeticalOrder = 35,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Think,
        .alphabeticalOrder = 60,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Hear,
        .alphabeticalOrder = 32,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Wants,
        .alphabeticalOrder = 51,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Misheard,
        .alphabeticalOrder = 44,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Dislike,
        .alphabeticalOrder = 42,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Angry,
        .alphabeticalOrder = 43,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Anger,
        .alphabeticalOrder = 7,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Scary,
        .alphabeticalOrder = 53,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Lonesome,
        .alphabeticalOrder = 9,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Disappoint,
        .alphabeticalOrder = 29,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Joy,
        .alphabeticalOrder = 4,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Gets,
        .alphabeticalOrder = 11,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Never,
        .alphabeticalOrder = 3,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Darn,
        .alphabeticalOrder = 10,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Downcast,
        .alphabeticalOrder = 64,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Incredible,
        .alphabeticalOrder = 6,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Likes,
        .alphabeticalOrder = 5,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Dislikes,
        .alphabeticalOrder = 47,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Boring,
        .alphabeticalOrder = 19,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Care,
        .alphabeticalOrder = 17,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Cares,
        .alphabeticalOrder = 2,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_AllRight,
        .alphabeticalOrder = 8,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Adore,
        .alphabeticalOrder = 33,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Disaster,
        .alphabeticalOrder = 28,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Enjoy,
        .alphabeticalOrder = 45,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Enjoys,
        .alphabeticalOrder = 34,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Eat,
        .alphabeticalOrder = 26,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Lacking,
        .alphabeticalOrder = 0,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Bad,
        .alphabeticalOrder = 21,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Hard,
        .alphabeticalOrder = 59,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Terrible,
        .alphabeticalOrder = 30,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Should,
        .alphabeticalOrder = 50,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Nice,
        .alphabeticalOrder = 1,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Drink,
        .alphabeticalOrder = 66,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Surprise,
        .alphabeticalOrder = 58,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Fear,
        .alphabeticalOrder = 65,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Want,
        .alphabeticalOrder = 14,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Wait,
        .alphabeticalOrder = 56,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Satisfied,
        .alphabeticalOrder = 25,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_See,
        .alphabeticalOrder = 57,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Rare,
        .alphabeticalOrder = 49,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Negative,
        .alphabeticalOrder = 52,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Done,
        .alphabeticalOrder = 48,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Danger,
        .alphabeticalOrder = 18,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Defeated,
        .alphabeticalOrder = 16,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Beat,
        .alphabeticalOrder = 15,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Great,
        .alphabeticalOrder = 67,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Romantic,
        .alphabeticalOrder = 68,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Question,
        .alphabeticalOrder = 55,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Understand,
        .alphabeticalOrder = 54,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Understands,
        .alphabeticalOrder = 20,
        .enabled = TRUE
    }
};
// ===== END src/data/easy_chat/easy_chat_group_feelings.h =====
// ===== BEGIN src/data/easy_chat/easy_chat_group_conditions.h =====

static const u8 sEasyChatWord_Hot[] = _("HOT");
static const u8 sEasyChatWord_Exists[] = _("EXISTS");
static const u8 sEasyChatWord_Excess[] = _("EXCESS");
static const u8 sEasyChatWord_Approved[] = _("APPROVED");
static const u8 sEasyChatWord_Has[] = _("HAS");
static const u8 sEasyChatWord_Good[] = _("GOOD");
static const u8 sEasyChatWord_Less[] = _("LESS");
static const u8 sEasyChatWord_Momentum[] = _("MOMENTUM");
static const u8 sEasyChatWord_Going[] = _("GOING");
static const u8 sEasyChatWord_Weird[] = _("WEIRD");
static const u8 sEasyChatWord_Busy[] = _("BUSY");
static const u8 sEasyChatWord_Together[] = _("TOGETHER");
static const u8 sEasyChatWord_Full[] = _("FULL");
static const u8 sEasyChatWord_Absent[] = _("ABSENT");
static const u8 sEasyChatWord_Being[] = _("BEING");
static const u8 sEasyChatWord_Need[] = _("NEED");
static const u8 sEasyChatWord_Tasty[] = _("TASTY");
static const u8 sEasyChatWord_Skilled[] = _("SKILLED");
static const u8 sEasyChatWord_Noisy[] = _("NOISY");
static const u8 sEasyChatWord_Big[] = _("BIG");
static const u8 sEasyChatWord_Late[] = _("LATE");
static const u8 sEasyChatWord_Close[] = _("CLOSE");
static const u8 sEasyChatWord_Docile[] = _("DOCILE");
static const u8 sEasyChatWord_Amusing[] = _("AMUSING");
static const u8 sEasyChatWord_Entertaining[] = _("ENTERTAINING");
static const u8 sEasyChatWord_Perfection[] = _("PERFECTION");
static const u8 sEasyChatWord_Pretty[] = _("PRETTY");
static const u8 sEasyChatWord_Healthy[] = _("HEALTHY");
static const u8 sEasyChatWord_Excellent[] = _("EXCELLENT");
static const u8 sEasyChatWord_UpsideDown[] = _("UPSIDE DOWN");
static const u8 sEasyChatWord_Cold[] = _("COLD");
static const u8 sEasyChatWord_Refreshing[] = _("REFRESHING");
static const u8 sEasyChatWord_Unavoidable[] = _("UNAVOIDABLE");
static const u8 sEasyChatWord_Much[] = _("MUCH");
static const u8 sEasyChatWord_Overwhelming[] = _("OVERWHELMING");
static const u8 sEasyChatWord_Fabulous[] = _("FABULOUS");
static const u8 sEasyChatWord_Else[] = _("ELSE");
static const u8 sEasyChatWord_Expensive[] = _("EXPENSIVE");
static const u8 sEasyChatWord_Correct[] = _("CORRECT");
static const u8 sEasyChatWord_Impossible[] = _("IMPOSSIBLE");
static const u8 sEasyChatWord_Small[] = _("SMALL");
static const u8 sEasyChatWord_Different[] = _("DIFFERENT");
static const u8 sEasyChatWord_Tired[] = _("TIRED");
static const u8 sEasyChatWord_Skill[] = _("SKILL");
static const u8 sEasyChatWord_Top[] = _("TOP");
static const u8 sEasyChatWord_NonStop[] = _("NON-STOP");
static const u8 sEasyChatWord_Preposterous[] = _("PREPOSTEROUS");
static const u8 sEasyChatWord_None[] = _("NONE");
static const u8 sEasyChatWord_Nothing[] = _("NOTHING");
static const u8 sEasyChatWord_Natural[] = _("NATURAL");
static const u8 sEasyChatWord_Becomes[] = _("BECOMES");
static const u8 sEasyChatWord_Lukewarm[] = _("LUKEWARM");
static const u8 sEasyChatWord_Fast[] = _("FAST");
static const u8 sEasyChatWord_Low[] = _("LOW");
static const u8 sEasyChatWord_Awful[] = _("AWFUL");
static const u8 sEasyChatWord_Alone[] = _("ALONE");
static const u8 sEasyChatWord_Bored[] = _("BORED");
static const u8 sEasyChatWord_Secret[] = _("SECRET");
static const u8 sEasyChatWord_Mystery[] = _("MYSTERY");
static const u8 sEasyChatWord_Lacks[] = _("LACKS");
static const u8 sEasyChatWord_Best[] = _("BEST");
static const u8 sEasyChatWord_Lousy[] = _("LOUSY");
static const u8 sEasyChatWord_Mistake[] = _("MISTAKE");
static const u8 sEasyChatWord_Kind[] = _("KIND");
static const u8 sEasyChatWord_Well[] = _("WELL");
static const u8 sEasyChatWord_Weakened[] = _("WEAKENED");
static const u8 sEasyChatWord_Simple[] = _("SIMPLE");
static const u8 sEasyChatWord_Seems[] = _("SEEMS");
static const u8 sEasyChatWord_Badly[] = _("BADLY");

static const struct EasyChatWordInfo sEasyChatGroup_Conditions[] = {
    {
        .text = sEasyChatWord_Hot,
        .alphabeticalOrder = 13,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Exists,
        .alphabeticalOrder = 55,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Excess,
        .alphabeticalOrder = 23,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Approved,
        .alphabeticalOrder = 3,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Has,
        .alphabeticalOrder = 54,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Good,
        .alphabeticalOrder = 68,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Less,
        .alphabeticalOrder = 50,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Momentum,
        .alphabeticalOrder = 14,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Going,
        .alphabeticalOrder = 60,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Weird,
        .alphabeticalOrder = 19,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Busy,
        .alphabeticalOrder = 56,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Together,
        .alphabeticalOrder = 10,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Full,
        .alphabeticalOrder = 21,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Absent,
        .alphabeticalOrder = 30,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Being,
        .alphabeticalOrder = 38,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Need,
        .alphabeticalOrder = 41,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Tasty,
        .alphabeticalOrder = 22,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Skilled,
        .alphabeticalOrder = 36,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Noisy,
        .alphabeticalOrder = 24,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Big,
        .alphabeticalOrder = 28,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Late,
        .alphabeticalOrder = 2,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Close,
        .alphabeticalOrder = 1,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Docile,
        .alphabeticalOrder = 37,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Amusing,
        .alphabeticalOrder = 35,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Entertaining,
        .alphabeticalOrder = 52,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Perfection,
        .alphabeticalOrder = 12,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Pretty,
        .alphabeticalOrder = 8,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Healthy,
        .alphabeticalOrder = 5,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Excellent,
        .alphabeticalOrder = 4,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_UpsideDown,
        .alphabeticalOrder = 27,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Cold,
        .alphabeticalOrder = 0,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Refreshing,
        .alphabeticalOrder = 39,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Unavoidable,
        .alphabeticalOrder = 63,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Much,
        .alphabeticalOrder = 59,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Overwhelming,
        .alphabeticalOrder = 20,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Fabulous,
        .alphabeticalOrder = 6,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Else,
        .alphabeticalOrder = 61,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Expensive,
        .alphabeticalOrder = 53,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Correct,
        .alphabeticalOrder = 51,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Impossible,
        .alphabeticalOrder = 62,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Small,
        .alphabeticalOrder = 7,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Different,
        .alphabeticalOrder = 33,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Tired,
        .alphabeticalOrder = 58,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Skill,
        .alphabeticalOrder = 49,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Top,
        .alphabeticalOrder = 15,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_NonStop,
        .alphabeticalOrder = 18,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Preposterous,
        .alphabeticalOrder = 45,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_None,
        .alphabeticalOrder = 47,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Nothing,
        .alphabeticalOrder = 48,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Natural,
        .alphabeticalOrder = 34,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Becomes,
        .alphabeticalOrder = 25,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Lukewarm,
        .alphabeticalOrder = 46,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Fast,
        .alphabeticalOrder = 26,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Low,
        .alphabeticalOrder = 31,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Awful,
        .alphabeticalOrder = 57,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Alone,
        .alphabeticalOrder = 67,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Bored,
        .alphabeticalOrder = 66,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Secret,
        .alphabeticalOrder = 43,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Mystery,
        .alphabeticalOrder = 17,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Lacks,
        .alphabeticalOrder = 40,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Best,
        .alphabeticalOrder = 16,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Lousy,
        .alphabeticalOrder = 42,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Mistake,
        .alphabeticalOrder = 11,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Kind,
        .alphabeticalOrder = 44,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Well,
        .alphabeticalOrder = 32,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Weakened,
        .alphabeticalOrder = 29,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Simple,
        .alphabeticalOrder = 65,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Seems,
        .alphabeticalOrder = 9,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Badly,
        .alphabeticalOrder = 64,
        .enabled = TRUE
    }
};
// ===== END src/data/easy_chat/easy_chat_group_conditions.h =====
// ===== BEGIN src/data/easy_chat/easy_chat_group_actions.h =====

static const u8 sEasyChatWord_Meets[] = _("MEETS");
static const u8 sEasyChatWord_Concede[] = _("CONCEDE");
static const u8 sEasyChatWord_Give[] = _("GIVE");
static const u8 sEasyChatWord_Gives[] = _("GIVES");
static const u8 sEasyChatWord_Played[] = _("PLAYED");
static const u8 sEasyChatWord_Plays[] = _("PLAYS");
static const u8 sEasyChatWord_Collect[] = _("COLLECT");
static const u8 sEasyChatWord_Walking[] = _("WALKING");
static const u8 sEasyChatWord_Walks[] = _("WALKS");
static const u8 sEasyChatWord_Says[] = _("SAYS");
static const u8 sEasyChatWord_Went[] = _("WENT");
static const u8 sEasyChatWord_Said[] = _("SAID");
static const u8 sEasyChatWord_WakeUp[] = _("WAKE UP");
static const u8 sEasyChatWord_WakesUp[] = _("WAKES UP");
static const u8 sEasyChatWord_Angers[] = _("ANGERS");
static const u8 sEasyChatWord_Teach[] = _("TEACH");
static const u8 sEasyChatWord_Teaches[] = _("TEACHES");
static const u8 sEasyChatWord_Please[] = _("PLEASE");
static const u8 sEasyChatWord_Learn[] = _("LEARN");
static const u8 sEasyChatWord_Change[] = _("CHANGE");
static const u8 sEasyChatWord_Story[] = _("STORY");
static const u8 sEasyChatWord_Trust[] = _("TRUST");
static const u8 sEasyChatWord_Lavish[] = _("LAVISH");
static const u8 sEasyChatWord_Listens[] = _("LISTENS");
static const u8 sEasyChatWord_Hearing[] = _("HEARING");
static const u8 sEasyChatWord_Trains[] = _("TRAINS");
static const u8 sEasyChatWord_Choose[] = _("CHOOSE");
static const u8 sEasyChatWord_Come[] = _("COME");
static const u8 sEasyChatWord_Came[] = _("CAME");
static const u8 sEasyChatWord_Search[] = _("SEARCH");
static const u8 sEasyChatWord_Make[] = _("MAKE");
static const u8 sEasyChatWord_Cause[] = _("CAUSE");
static const u8 sEasyChatWord_Know[] = _("KNOW");
static const u8 sEasyChatWord_Knows[] = _("KNOWS");
static const u8 sEasyChatWord_Refuse[] = _("REFUSE");
static const u8 sEasyChatWord_Stores[] = _("STORES");
static const u8 sEasyChatWord_Brag[] = _("BRAG");
static const u8 sEasyChatWord_Ignorant[] = _("IGNORANT");
static const u8 sEasyChatWord_Thinks[] = _("THINKS");
static const u8 sEasyChatWord_Believe[] = _("BELIEVE");
static const u8 sEasyChatWord_Slide[] = _("SLIDE");
static const u8 sEasyChatWord_Eats[] = _("EATS");
static const u8 sEasyChatWord_Use[] = _("USE");
static const u8 sEasyChatWord_Uses[] = _("USES");
static const u8 sEasyChatWord_Using[] = _("USING");
static const u8 sEasyChatWord_Couldnt[] = _("COULDN'T");
static const u8 sEasyChatWord_Capable[] = _("CAPABLE");
static const u8 sEasyChatWord_Disappear[] = _("DISAPPEAR");
static const u8 sEasyChatWord_Appear[] = _("APPEAR");
static const u8 sEasyChatWord_Throw[] = _("THROW");
static const u8 sEasyChatWord_Worry[] = _("WORRY");
static const u8 sEasyChatWord_Slept[] = _("SLEPT");
static const u8 sEasyChatWord_Sleep[] = _("SLEEP");
static const u8 sEasyChatWord_Release[] = _("RELEASE");
static const u8 sEasyChatWord_Drinks[] = _("DRINKS");
static const u8 sEasyChatWord_Runs[] = _("RUNS");
static const u8 sEasyChatWord_Run[] = _("RUN");
static const u8 sEasyChatWord_Works[] = _("WORKS");
static const u8 sEasyChatWord_Working[] = _("WORKING");
static const u8 sEasyChatWord_Talking[] = _("TALKING");
static const u8 sEasyChatWord_Talk[] = _("TALK");
static const u8 sEasyChatWord_Sink[] = _("SINK");
static const u8 sEasyChatWord_Smack[] = _("SMACK");
static const u8 sEasyChatWord_Pretend[] = _("PRETEND");
static const u8 sEasyChatWord_Praise[] = _("PRAISE");
static const u8 sEasyChatWord_Overdo[] = _("OVERDO");
static const u8 sEasyChatWord_Show[] = _("SHOW");
static const u8 sEasyChatWord_Looks[] = _("LOOKS");
static const u8 sEasyChatWord_Sees[] = _("SEES");
static const u8 sEasyChatWord_Seek[] = _("SEEK");
static const u8 sEasyChatWord_Own[] = _("OWN");
static const u8 sEasyChatWord_Take[] = _("TAKE");
static const u8 sEasyChatWord_Allow[] = _("ALLOW");
static const u8 sEasyChatWord_Forget[] = _("FORGET");
static const u8 sEasyChatWord_Forgets[] = _("FORGETS");
static const u8 sEasyChatWord_Appears[] = _("APPEARS");
static const u8 sEasyChatWord_Faint[] = _("FAINT");
static const u8 sEasyChatWord_Fainted[] = _("FAINTED");

static const struct EasyChatWordInfo sEasyChatGroup_Actions[] = {
    {
        .text = sEasyChatWord_Meets,
        .alphabeticalOrder = 72,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Concede,
        .alphabeticalOrder = 14,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Give,
        .alphabeticalOrder = 48,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Gives,
        .alphabeticalOrder = 75,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Played,
        .alphabeticalOrder = 39,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Plays,
        .alphabeticalOrder = 36,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Collect,
        .alphabeticalOrder = 28,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Walking,
        .alphabeticalOrder = 46,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Walks,
        .alphabeticalOrder = 31,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Says,
        .alphabeticalOrder = 19,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Went,
        .alphabeticalOrder = 26,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Said,
        .alphabeticalOrder = 6,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_WakeUp,
        .alphabeticalOrder = 27,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_WakesUp,
        .alphabeticalOrder = 1,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Angers,
        .alphabeticalOrder = 45,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Teach,
        .alphabeticalOrder = 47,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Teaches,
        .alphabeticalOrder = 54,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Please,
        .alphabeticalOrder = 41,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Learn,
        .alphabeticalOrder = 76,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Change,
        .alphabeticalOrder = 77,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Story,
        .alphabeticalOrder = 73,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Trust,
        .alphabeticalOrder = 74,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Lavish,
        .alphabeticalOrder = 2,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Listens,
        .alphabeticalOrder = 3,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Hearing,
        .alphabeticalOrder = 24,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Trains,
        .alphabeticalOrder = 37,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Choose,
        .alphabeticalOrder = 32,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Come,
        .alphabeticalOrder = 33,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Came,
        .alphabeticalOrder = 22,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Search,
        .alphabeticalOrder = 18,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Make,
        .alphabeticalOrder = 23,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Cause,
        .alphabeticalOrder = 67,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Know,
        .alphabeticalOrder = 30,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Knows,
        .alphabeticalOrder = 0,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Refuse,
        .alphabeticalOrder = 65,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Stores,
        .alphabeticalOrder = 70,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Brag,
        .alphabeticalOrder = 4,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Ignorant,
        .alphabeticalOrder = 5,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Thinks,
        .alphabeticalOrder = 17,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Believe,
        .alphabeticalOrder = 64,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Slide,
        .alphabeticalOrder = 63,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Eats,
        .alphabeticalOrder = 34,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Use,
        .alphabeticalOrder = 53,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Uses,
        .alphabeticalOrder = 56,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Using,
        .alphabeticalOrder = 55,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Couldnt,
        .alphabeticalOrder = 11,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Capable,
        .alphabeticalOrder = 9,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Disappear,
        .alphabeticalOrder = 29,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Appear,
        .alphabeticalOrder = 69,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Throw,
        .alphabeticalOrder = 68,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Worry,
        .alphabeticalOrder = 66,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Slept,
        .alphabeticalOrder = 61,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Sleep,
        .alphabeticalOrder = 52,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Release,
        .alphabeticalOrder = 51,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Drinks,
        .alphabeticalOrder = 40,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Runs,
        .alphabeticalOrder = 62,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Run,
        .alphabeticalOrder = 35,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Works,
        .alphabeticalOrder = 20,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Working,
        .alphabeticalOrder = 71,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Talking,
        .alphabeticalOrder = 60,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Talk,
        .alphabeticalOrder = 59,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Sink,
        .alphabeticalOrder = 15,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Smack,
        .alphabeticalOrder = 16,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Pretend,
        .alphabeticalOrder = 38,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Praise,
        .alphabeticalOrder = 49,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Overdo,
        .alphabeticalOrder = 25,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Show,
        .alphabeticalOrder = 21,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Looks,
        .alphabeticalOrder = 42,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Sees,
        .alphabeticalOrder = 43,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Seek,
        .alphabeticalOrder = 44,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Own,
        .alphabeticalOrder = 12,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Take,
        .alphabeticalOrder = 13,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Allow,
        .alphabeticalOrder = 7,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Forget,
        .alphabeticalOrder = 8,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Forgets,
        .alphabeticalOrder = 10,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Appears,
        .alphabeticalOrder = 58,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Faint,
        .alphabeticalOrder = 57,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Fainted,
        .alphabeticalOrder = 50,
        .enabled = TRUE
    }
};
// ===== END src/data/easy_chat/easy_chat_group_actions.h =====
// ===== BEGIN src/data/easy_chat/easy_chat_group_lifestyle.h =====

static const u8 sEasyChatWord_Chores[] = _("CHORES");
static const u8 sEasyChatWord_Home[] = _("HOME");
static const u8 sEasyChatWord_Money[] = _("MONEY");
static const u8 sEasyChatWord_Allowance[] = _("ALLOWANCE");
static const u8 sEasyChatWord_Bath[] = _("BATH");
static const u8 sEasyChatWord_Conversation[] = _("CONVERSATION");
static const u8 sEasyChatWord_School[] = _("SCHOOL");
static const u8 sEasyChatWord_Commemorate[] = _("COMMEMORATE");
static const u8 sEasyChatWord_Habit[] = _("HABIT");
static const u8 sEasyChatWord_Group[] = _("GROUP");
static const u8 sEasyChatWord_Word[] = _("WORD");
static const u8 sEasyChatWord_Store[] = _("STORE");
static const u8 sEasyChatWord_Service[] = _("SERVICE");
static const u8 sEasyChatWord_Work[] = _("WORK");
static const u8 sEasyChatWord_System[] = _("SYSTEM");
static const u8 sEasyChatWord_Train[] = _("TRAIN");
static const u8 sEasyChatWord_Class[] = _("CLASS");
static const u8 sEasyChatWord_Lessons[] = _("LESSONS");
static const u8 sEasyChatWord_Information[] = _("INFORMATION");
static const u8 sEasyChatWord_Living[] = _("LIVING");
static const u8 sEasyChatWord_Teacher[] = _("TEACHER");
static const u8 sEasyChatWord_Tournament[] = _("TOURNAMENT");
static const u8 sEasyChatWord_Letter[] = _("LETTER");
static const u8 sEasyChatWord_Event[] = _("EVENT");
static const u8 sEasyChatWord_Digital[] = _("DIGITAL");
static const u8 sEasyChatWord_Test[] = _("TEST");
static const u8 sEasyChatWord_DeptStore[] = _("DEPT. STORE");
static const u8 sEasyChatWord_Television[] = _("TELEVISION");
static const u8 sEasyChatWord_Phone[] = _("PHONE");
static const u8 sEasyChatWord_Item[] = _("ITEM");
static const u8 sEasyChatWord_Name[] = _("NAME");
static const u8 sEasyChatWord_News[] = _("NEWS");
static const u8 sEasyChatWord_Popular[] = _("POPULAR");
static const u8 sEasyChatWord_Party[] = _("PARTY");
static const u8 sEasyChatWord_Study[] = _("STUDY");
static const u8 sEasyChatWord_Machine[] = _("MACHINE");
static const u8 sEasyChatWord_Mail[] = _("MAIL");
static const u8 sEasyChatWord_Message[] = _("MESSAGE");
static const u8 sEasyChatWord_Promise[] = _("PROMISE");
static const u8 sEasyChatWord_Dream[] = _("DREAM");
static const u8 sEasyChatWord_Kindergarten[] = _("KINDERGARTEN");
static const u8 sEasyChatWord_Life[] = _("LIFE");
static const u8 sEasyChatWord_Radio[] = _("RADIO");
static const u8 sEasyChatWord_Rental[] = _("RENTAL");
static const u8 sEasyChatWord_World[] = _("WORLD");

static const struct EasyChatWordInfo sEasyChatGroup_Lifestyle[] = {
    {
        .text = sEasyChatWord_Chores,
        .alphabeticalOrder = 3,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Home,
        .alphabeticalOrder = 4,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Money,
        .alphabeticalOrder = 0,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Allowance,
        .alphabeticalOrder = 16,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Bath,
        .alphabeticalOrder = 7,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Conversation,
        .alphabeticalOrder = 5,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_School,
        .alphabeticalOrder = 26,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Commemorate,
        .alphabeticalOrder = 24,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Habit,
        .alphabeticalOrder = 39,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Group,
        .alphabeticalOrder = 23,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Word,
        .alphabeticalOrder = 9,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Store,
        .alphabeticalOrder = 8,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Service,
        .alphabeticalOrder = 1,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Work,
        .alphabeticalOrder = 18,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_System,
        .alphabeticalOrder = 29,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Train,
        .alphabeticalOrder = 40,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Class,
        .alphabeticalOrder = 17,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Lessons,
        .alphabeticalOrder = 22,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Information,
        .alphabeticalOrder = 41,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Living,
        .alphabeticalOrder = 19,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Teacher,
        .alphabeticalOrder = 35,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Tournament,
        .alphabeticalOrder = 36,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Letter,
        .alphabeticalOrder = 37,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Event,
        .alphabeticalOrder = 2,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Digital,
        .alphabeticalOrder = 30,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Test,
        .alphabeticalOrder = 31,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_DeptStore,
        .alphabeticalOrder = 33,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Television,
        .alphabeticalOrder = 28,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Phone,
        .alphabeticalOrder = 32,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Item,
        .alphabeticalOrder = 38,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Name,
        .alphabeticalOrder = 42,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_News,
        .alphabeticalOrder = 43,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Popular,
        .alphabeticalOrder = 6,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Party,
        .alphabeticalOrder = 12,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Study,
        .alphabeticalOrder = 11,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Machine,
        .alphabeticalOrder = 34,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Mail,
        .alphabeticalOrder = 14,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Message,
        .alphabeticalOrder = 20,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Promise,
        .alphabeticalOrder = 27,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Dream,
        .alphabeticalOrder = 25,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Kindergarten,
        .alphabeticalOrder = 21,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Life,
        .alphabeticalOrder = 15,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Radio,
        .alphabeticalOrder = 10,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Rental,
        .alphabeticalOrder = 13,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_World,
        .alphabeticalOrder = 44,
        .enabled = TRUE
    }
};
// ===== END src/data/easy_chat/easy_chat_group_lifestyle.h =====
// ===== BEGIN src/data/easy_chat/easy_chat_group_hobbies.h =====

static const u8 sEasyChatWord_Idol[] = _("IDOL");
static const u8 sEasyChatWord_Anime[] = _("ANIME");
static const u8 sEasyChatWord_Song[] = _("SONG");
static const u8 sEasyChatWord_Movie[] = _("MOVIE");
static const u8 sEasyChatWord_Sweets[] = _("SWEETS");
static const u8 sEasyChatWord_Chat[] = _("CHAT");
static const u8 sEasyChatWord_ChildsPlay[] = _("CHILD'S PLAY");
static const u8 sEasyChatWord_Toys[] = _("TOYS");
static const u8 sEasyChatWord_Music[] = _("MUSIC");
static const u8 sEasyChatWord_Cards[] = _("CARDS");
static const u8 sEasyChatWord_Shopping[] = _("SHOPPING");
static const u8 sEasyChatWord_Camera[] = _("CAMERA");
static const u8 sEasyChatWord_Viewing[] = _("VIEWING");
static const u8 sEasyChatWord_Spectator[] = _("SPECTATOR");
static const u8 sEasyChatWord_Gourmet[] = _("GOURMET");
static const u8 sEasyChatWord_Game[] = _("GAME");
static const u8 sEasyChatWord_Rpg[] = _("RPG");
static const u8 sEasyChatWord_Collection[] = _("COLLECTION");
static const u8 sEasyChatWord_Complete[] = _("COMPLETE");
static const u8 sEasyChatWord_Magazine[] = _("MAGAZINE");
static const u8 sEasyChatWord_Walk[] = _("WALK");
static const u8 sEasyChatWord_Bike[] = _("BIKE");
static const u8 sEasyChatWord_Hobby[] = _("HOBBY");
static const u8 sEasyChatWord_Sports[] = _("SPORTS");
static const u8 sEasyChatWord_Software[] = _("SOFTWARE");
static const u8 sEasyChatWord_Songs[] = _("SONGS");
static const u8 sEasyChatWord_Diet[] = _("DIET");
static const u8 sEasyChatWord_Treasure[] = _("TREASURE");
static const u8 sEasyChatWord_Travel[] = _("TRAVEL");
static const u8 sEasyChatWord_Dance[] = _("DANCE");
static const u8 sEasyChatWord_Channel[] = _("CHANNEL");
static const u8 sEasyChatWord_Making[] = _("MAKING");
static const u8 sEasyChatWord_Fishing[] = _("FISHING");
static const u8 sEasyChatWord_Date[] = _("DATE");
static const u8 sEasyChatWord_Design[] = _("DESIGN");
static const u8 sEasyChatWord_Locomotive[] = _("LOCOMOTIVE");
static const u8 sEasyChatWord_PlushDoll[] = _("PLUSH DOLL");
static const u8 sEasyChatWord_Pc[] = _("PC");
static const u8 sEasyChatWord_Flowers[] = _("FLOWERS");
static const u8 sEasyChatWord_Hero[] = _("HERO");
static const u8 sEasyChatWord_Nap[] = _("NAP");
static const u8 sEasyChatWord_Heroine[] = _("HEROINE");
static const u8 sEasyChatWord_Fashion[] = _("FASHION");
static const u8 sEasyChatWord_Adventure[] = _("ADVENTURE");
static const u8 sEasyChatWord_Board[] = _("BOARD");
static const u8 sEasyChatWord_Ball[] = _("BALL");
static const u8 sEasyChatWord_Book[] = _("BOOK");
static const u8 sEasyChatWord_Festival[] = _("FESTIVAL");
static const u8 sEasyChatWord_Comics[] = _("COMICS");
static const u8 sEasyChatWord_Holiday[] = _("HOLIDAY");
static const u8 sEasyChatWord_Plans[] = _("PLANS");
static const u8 sEasyChatWord_Trendy[] = _("TRENDY");
static const u8 sEasyChatWord_Vacation[] = _("VACATION");
static const u8 sEasyChatWord_Look[] = _("LOOK");

static const struct EasyChatWordInfo sEasyChatGroup_Hobbies[] = {
    {
        .text = sEasyChatWord_Idol,
        .alphabeticalOrder = 43,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Anime,
        .alphabeticalOrder = 1,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Song,
        .alphabeticalOrder = 45,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Movie,
        .alphabeticalOrder = 21,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Sweets,
        .alphabeticalOrder = 44,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Chat,
        .alphabeticalOrder = 46,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_ChildsPlay,
        .alphabeticalOrder = 11,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Toys,
        .alphabeticalOrder = 9,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Music,
        .alphabeticalOrder = 30,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Cards,
        .alphabeticalOrder = 5,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Shopping,
        .alphabeticalOrder = 6,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Camera,
        .alphabeticalOrder = 17,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Viewing,
        .alphabeticalOrder = 48,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Spectator,
        .alphabeticalOrder = 18,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Gourmet,
        .alphabeticalOrder = 29,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Game,
        .alphabeticalOrder = 33,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Rpg,
        .alphabeticalOrder = 34,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Collection,
        .alphabeticalOrder = 26,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Complete,
        .alphabeticalOrder = 42,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Magazine,
        .alphabeticalOrder = 47,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Walk,
        .alphabeticalOrder = 32,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Bike,
        .alphabeticalOrder = 38,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Hobby,
        .alphabeticalOrder = 15,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Sports,
        .alphabeticalOrder = 14,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Software,
        .alphabeticalOrder = 39,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Songs,
        .alphabeticalOrder = 41,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Diet,
        .alphabeticalOrder = 22,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Treasure,
        .alphabeticalOrder = 49,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Travel,
        .alphabeticalOrder = 0,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Dance,
        .alphabeticalOrder = 35,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Channel,
        .alphabeticalOrder = 53,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Making,
        .alphabeticalOrder = 19,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Fishing,
        .alphabeticalOrder = 31,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Date,
        .alphabeticalOrder = 3,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Design,
        .alphabeticalOrder = 8,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Locomotive,
        .alphabeticalOrder = 40,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_PlushDoll,
        .alphabeticalOrder = 37,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Pc,
        .alphabeticalOrder = 50,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Flowers,
        .alphabeticalOrder = 36,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Hero,
        .alphabeticalOrder = 16,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Nap,
        .alphabeticalOrder = 10,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Heroine,
        .alphabeticalOrder = 24,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Fashion,
        .alphabeticalOrder = 2,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Adventure,
        .alphabeticalOrder = 25,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Board,
        .alphabeticalOrder = 13,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Ball,
        .alphabeticalOrder = 23,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Book,
        .alphabeticalOrder = 4,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Festival,
        .alphabeticalOrder = 7,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Comics,
        .alphabeticalOrder = 28,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Holiday,
        .alphabeticalOrder = 27,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Plans,
        .alphabeticalOrder = 51,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Trendy,
        .alphabeticalOrder = 52,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Vacation,
        .alphabeticalOrder = 12,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Look,
        .alphabeticalOrder = 20,
        .enabled = TRUE
    }
};
// ===== END src/data/easy_chat/easy_chat_group_hobbies.h =====
// ===== BEGIN src/data/easy_chat/easy_chat_group_time.h =====

static const u8 sEasyChatWord_Fall[] = _("FALL");
static const u8 sEasyChatWord_Morning[] = _("MORNING");
static const u8 sEasyChatWord_Tomorrow[] = _("TOMORROW");
static const u8 sEasyChatWord_Last[] = _("LAST");
static const u8 sEasyChatWord_Day[] = _("DAY");
static const u8 sEasyChatWord_Sometime[] = _("SOMETIME");
static const u8 sEasyChatWord_Always[] = _("ALWAYS");
static const u8 sEasyChatWord_Current[] = _("CURRENT");
static const u8 sEasyChatWord_Forever[] = _("FOREVER");
static const u8 sEasyChatWord_Days[] = _("DAYS");
static const u8 sEasyChatWord_End[] = _("END");
static const u8 sEasyChatWord_Tuesday[] = _("TUESDAY");
static const u8 sEasyChatWord_Yesterday[] = _("YESTERDAY");
static const u8 sEasyChatWord_Today[] = _("TODAY");
static const u8 sEasyChatWord_Friday[] = _("FRIDAY");
static const u8 sEasyChatWord_Monday[] = _("MONDAY");
static const u8 sEasyChatWord_Later[] = _("LATER");
static const u8 sEasyChatWord_Earlier[] = _("EARLIER");
static const u8 sEasyChatWord_Another[] = _("ANOTHER");
static const u8 sEasyChatWord_Time[] = _("TIME");
static const u8 sEasyChatWord_Finish[] = _("FINISH");
static const u8 sEasyChatWord_Wednesday[] = _("WEDNESDAY");
static const u8 sEasyChatWord_Soon[] = _("SOON");
static const u8 sEasyChatWord_Start[] = _("START");
static const u8 sEasyChatWord_Month[] = _("MONTH");
static const u8 sEasyChatWord_Stop[] = _("STOP");
static const u8 sEasyChatWord_Now[] = _("NOW");
static const u8 sEasyChatWord_Final[] = _("FINAL");
static const u8 sEasyChatWord_Next[] = _("NEXT");
static const u8 sEasyChatWord_Age[] = _("AGE");
static const u8 sEasyChatWord_Saturday[] = _("SATURDAY");
static const u8 sEasyChatWord_Summer[] = _("SUMMER");
static const u8 sEasyChatWord_Sunday[] = _("SUNDAY");
static const u8 sEasyChatWord_Beginning[] = _("BEGINNING");
static const u8 sEasyChatWord_Spring[] = _("SPRING");
static const u8 sEasyChatWord_Daytime[] = _("DAYTIME");
static const u8 sEasyChatWord_Winter[] = _("WINTER");
static const u8 sEasyChatWord_Daily[] = _("DAILY");
static const u8 sEasyChatWord_Olden[] = _("OLDEN");
static const u8 sEasyChatWord_Almost[] = _("ALMOST");
static const u8 sEasyChatWord_Nearly[] = _("NEARLY");
static const u8 sEasyChatWord_Thursday[] = _("THURSDAY");
static const u8 sEasyChatWord_Nighttime[] = _("NIGHTTIME");
static const u8 sEasyChatWord_Night[] = _("NIGHT");
static const u8 sEasyChatWord_Week[] = _("WEEK");

static const struct EasyChatWordInfo sEasyChatGroup_Time[] = {
    {
        .text = sEasyChatWord_Fall,
        .alphabeticalOrder = 29,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Morning,
        .alphabeticalOrder = 39,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Tomorrow,
        .alphabeticalOrder = 6,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Last,
        .alphabeticalOrder = 18,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Day,
        .alphabeticalOrder = 33,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Sometime,
        .alphabeticalOrder = 7,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Always,
        .alphabeticalOrder = 37,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Current,
        .alphabeticalOrder = 4,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Forever,
        .alphabeticalOrder = 9,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Days,
        .alphabeticalOrder = 35,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_End,
        .alphabeticalOrder = 17,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Tuesday,
        .alphabeticalOrder = 10,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Yesterday,
        .alphabeticalOrder = 0,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Today,
        .alphabeticalOrder = 27,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Friday,
        .alphabeticalOrder = 20,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Monday,
        .alphabeticalOrder = 8,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Later,
        .alphabeticalOrder = 14,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Earlier,
        .alphabeticalOrder = 3,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Another,
        .alphabeticalOrder = 16,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Time,
        .alphabeticalOrder = 15,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Finish,
        .alphabeticalOrder = 24,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Wednesday,
        .alphabeticalOrder = 1,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Soon,
        .alphabeticalOrder = 40,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Start,
        .alphabeticalOrder = 28,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Month,
        .alphabeticalOrder = 43,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Stop,
        .alphabeticalOrder = 42,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Now,
        .alphabeticalOrder = 26,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Final,
        .alphabeticalOrder = 38,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Next,
        .alphabeticalOrder = 30,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Age,
        .alphabeticalOrder = 5,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Saturday,
        .alphabeticalOrder = 22,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Summer,
        .alphabeticalOrder = 34,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Sunday,
        .alphabeticalOrder = 23,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Beginning,
        .alphabeticalOrder = 25,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Spring,
        .alphabeticalOrder = 31,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Daytime,
        .alphabeticalOrder = 32,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Winter,
        .alphabeticalOrder = 41,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Daily,
        .alphabeticalOrder = 19,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Olden,
        .alphabeticalOrder = 13,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Almost,
        .alphabeticalOrder = 2,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Nearly,
        .alphabeticalOrder = 11,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Thursday,
        .alphabeticalOrder = 21,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Nighttime,
        .alphabeticalOrder = 44,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Night,
        .alphabeticalOrder = 36,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Week,
        .alphabeticalOrder = 12,
        .enabled = TRUE
    }
};
// ===== END src/data/easy_chat/easy_chat_group_time.h =====
// ===== BEGIN src/data/easy_chat/easy_chat_group_misc.h =====

static const u8 sEasyChatWord_Highs[] = _("HIGHS");
static const u8 sEasyChatWord_Lows[] = _("LOWS");
static const u8 sEasyChatWord_Um[] = _("UM");
static const u8 sEasyChatWord_Rear[] = _("REAR");
static const u8 sEasyChatWord_Things[] = _("THINGS");
static const u8 sEasyChatWord_Thing[] = _("THING");
static const u8 sEasyChatWord_Below[] = _("BELOW");
static const u8 sEasyChatWord_Above[] = _("ABOVE");
static const u8 sEasyChatWord_Back[] = _("BACK");
static const u8 sEasyChatWord_High[] = _("HIGH");
static const u8 sEasyChatWord_Here[] = _("HERE");
static const u8 sEasyChatWord_Inside[] = _("INSIDE");
static const u8 sEasyChatWord_Outside[] = _("OUTSIDE");
static const u8 sEasyChatWord_Beside[] = _("BESIDE");
static const u8 sEasyChatWord_ThisIsItExcl[] = _("THIS IS IT!");
static const u8 sEasyChatWord_This[] = _("THIS");
static const u8 sEasyChatWord_Every[] = _("EVERY");
static const u8 sEasyChatWord_These[] = _("THESE");
static const u8 sEasyChatWord_TheseWere[] = _("THESE WERE");
static const u8 sEasyChatWord_Down[] = _("DOWN");
static const u8 sEasyChatWord_That[] = _("THAT");
static const u8 sEasyChatWord_ThoseAre[] = _("THOSE ARE");
static const u8 sEasyChatWord_ThoseWere[] = _("THOSE WERE");
static const u8 sEasyChatWord_ThatsItExcl[] = _("THAT'S IT!");
static const u8 sEasyChatWord_Am[] = _("AM");
static const u8 sEasyChatWord_ThatWas[] = _("THAT WAS");
static const u8 sEasyChatWord_Front[] = _("FRONT");
static const u8 sEasyChatWord_Up[] = _("UP");
static const u8 sEasyChatWord_Choice[] = _("CHOICE");
static const u8 sEasyChatWord_Far[] = _("FAR");
static const u8 sEasyChatWord_Away[] = _("AWAY");
static const u8 sEasyChatWord_Near[] = _("NEAR");
static const u8 sEasyChatWord_Where[] = _("WHERE");
static const u8 sEasyChatWord_When[] = _("WHEN");
static const u8 sEasyChatWord_What[] = _("WHAT");
static const u8 sEasyChatWord_Deep[] = _("DEEP");
static const u8 sEasyChatWord_Shallow[] = _("SHALLOW");
static const u8 sEasyChatWord_Why[] = _("WHY");
static const u8 sEasyChatWord_Confused[] = _("CONFUSED");
static const u8 sEasyChatWord_Opposite[] = _("OPPOSITE");
static const u8 sEasyChatWord_Left[] = _("LEFT");
static const u8 sEasyChatWord_Right[] = _("RIGHT");

static const struct EasyChatWordInfo sEasyChatGroup_Misc[] = {
    {
        .text = sEasyChatWord_Highs,
        .alphabeticalOrder = 7,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Lows,
        .alphabeticalOrder = 24,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Um,
        .alphabeticalOrder = 30,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Rear,
        .alphabeticalOrder = 8,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Things,
        .alphabeticalOrder = 6,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Thing,
        .alphabeticalOrder = 13,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Below,
        .alphabeticalOrder = 28,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Above,
        .alphabeticalOrder = 38,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Back,
        .alphabeticalOrder = 35,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_High,
        .alphabeticalOrder = 19,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Here,
        .alphabeticalOrder = 16,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Inside,
        .alphabeticalOrder = 29,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Outside,
        .alphabeticalOrder = 26,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Beside,
        .alphabeticalOrder = 10,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_ThisIsItExcl,
        .alphabeticalOrder = 9,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_This,
        .alphabeticalOrder = 0,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Every,
        .alphabeticalOrder = 11,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_These,
        .alphabeticalOrder = 40,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_TheseWere,
        .alphabeticalOrder = 1,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Down,
        .alphabeticalOrder = 31,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_That,
        .alphabeticalOrder = 39,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_ThoseAre,
        .alphabeticalOrder = 12,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_ThoseWere,
        .alphabeticalOrder = 3,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_ThatsItExcl,
        .alphabeticalOrder = 41,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Am,
        .alphabeticalOrder = 36,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_ThatWas,
        .alphabeticalOrder = 20,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Front,
        .alphabeticalOrder = 25,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Up,
        .alphabeticalOrder = 23,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Choice,
        .alphabeticalOrder = 17,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Far,
        .alphabeticalOrder = 18,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Away,
        .alphabeticalOrder = 5,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Near,
        .alphabeticalOrder = 4,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Where,
        .alphabeticalOrder = 15,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_When,
        .alphabeticalOrder = 14,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_What,
        .alphabeticalOrder = 21,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Deep,
        .alphabeticalOrder = 22,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Shallow,
        .alphabeticalOrder = 2,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Why,
        .alphabeticalOrder = 27,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Confused,
        .alphabeticalOrder = 34,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Opposite,
        .alphabeticalOrder = 33,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Left,
        .alphabeticalOrder = 32,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Right,
        .alphabeticalOrder = 37,
        .enabled = TRUE
    }
};
// ===== END src/data/easy_chat/easy_chat_group_misc.h =====
// ===== BEGIN src/data/easy_chat/easy_chat_group_adjectives.h =====

static const u8 sEasyChatWord_Wandering[] = _("WANDERING");
static const u8 sEasyChatWord_Rickety[] = _("RICKETY");
static const u8 sEasyChatWord_RockSolid[] = _("ROCK-SOLID");
static const u8 sEasyChatWord_Hungry[] = _("HUNGRY");
static const u8 sEasyChatWord_Tight[] = _("TIGHT");
static const u8 sEasyChatWord_Ticklish[] = _("TICKLISH");
static const u8 sEasyChatWord_Twirling[] = _("TWIRLING");
static const u8 sEasyChatWord_Spiraling[] = _("SPIRALING");
static const u8 sEasyChatWord_Thirsty[] = _("THIRSTY");
static const u8 sEasyChatWord_Lolling[] = _("LOLLING");
static const u8 sEasyChatWord_Silky[] = _("SILKY");
static const u8 sEasyChatWord_Sadly[] = _("SADLY");
static const u8 sEasyChatWord_Hopeless[] = _("HOPELESS");
static const u8 sEasyChatWord_Useless[] = _("USELESS");
static const u8 sEasyChatWord_Drooling[] = _("DROOLING");
static const u8 sEasyChatWord_Exciting[] = _("EXCITING");
static const u8 sEasyChatWord_Thick[] = _("THICK");
static const u8 sEasyChatWord_Smooth[] = _("SMOOTH");
static const u8 sEasyChatWord_Slimy[] = _("SLIMY");
static const u8 sEasyChatWord_Thin[] = _("THIN");
static const u8 sEasyChatWord_Break[] = _("BREAK");
static const u8 sEasyChatWord_Voracious[] = _("VORACIOUS");
static const u8 sEasyChatWord_Scatter[] = _("SCATTER");
static const u8 sEasyChatWord_Awesome[] = _("AWESOME");
static const u8 sEasyChatWord_Wimpy[] = _("WIMPY");
static const u8 sEasyChatWord_Wobbly[] = _("WOBBLY");
static const u8 sEasyChatWord_Shaky[] = _("SHAKY");
static const u8 sEasyChatWord_Ripped[] = _("RIPPED");
static const u8 sEasyChatWord_Shredded[] = _("SHREDDED");
static const u8 sEasyChatWord_Increasing[] = _("INCREASING");
static const u8 sEasyChatWord_Yet[] = _("YET");
static const u8 sEasyChatWord_Destroyed[] = _("DESTROYED");
static const u8 sEasyChatWord_Fiery[] = _("FIERY");
static const u8 sEasyChatWord_LoveyDovey[] = _("LOVEY-DOVEY");
static const u8 sEasyChatWord_Happily[] = _("HAPPILY");
static const u8 sEasyChatWord_Anticipation[] = _("ANTICIPATION");

static const struct EasyChatWordInfo sEasyChatGroup_Adjectives[] = {
    {
        .text = sEasyChatWord_Wandering,
        .alphabeticalOrder = 35,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Rickety,
        .alphabeticalOrder = 23,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_RockSolid,
        .alphabeticalOrder = 20,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Hungry,
        .alphabeticalOrder = 31,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Tight,
        .alphabeticalOrder = 14,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Ticklish,
        .alphabeticalOrder = 15,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Twirling,
        .alphabeticalOrder = 32,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Spiraling,
        .alphabeticalOrder = 34,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Thirsty,
        .alphabeticalOrder = 12,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Lolling,
        .alphabeticalOrder = 3,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Silky,
        .alphabeticalOrder = 29,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Sadly,
        .alphabeticalOrder = 9,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Hopeless,
        .alphabeticalOrder = 33,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Useless,
        .alphabeticalOrder = 1,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Drooling,
        .alphabeticalOrder = 27,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Exciting,
        .alphabeticalOrder = 2,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Thick,
        .alphabeticalOrder = 11,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Smooth,
        .alphabeticalOrder = 22,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Slimy,
        .alphabeticalOrder = 26,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Thin,
        .alphabeticalOrder = 28,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Break,
        .alphabeticalOrder = 10,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Voracious,
        .alphabeticalOrder = 18,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Scatter,
        .alphabeticalOrder = 17,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Awesome,
        .alphabeticalOrder = 7,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Wimpy,
        .alphabeticalOrder = 16,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Wobbly,
        .alphabeticalOrder = 19,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Shaky,
        .alphabeticalOrder = 8,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Ripped,
        .alphabeticalOrder = 5,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Shredded,
        .alphabeticalOrder = 4,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Increasing,
        .alphabeticalOrder = 6,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Yet,
        .alphabeticalOrder = 13,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Destroyed,
        .alphabeticalOrder = 21,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Fiery,
        .alphabeticalOrder = 0,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_LoveyDovey,
        .alphabeticalOrder = 24,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Happily,
        .alphabeticalOrder = 25,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Anticipation,
        .alphabeticalOrder = 30,
        .enabled = TRUE
    }
};
// ===== END src/data/easy_chat/easy_chat_group_adjectives.h =====
// ===== BEGIN src/data/easy_chat/easy_chat_group_events.h =====

static const u8 sEasyChatWord_Appeal[] = _("APPEAL");
static const u8 sEasyChatWord_Events[] = _("EVENTS");
static const u8 sEasyChatWord_StayAtHome[] = _("STAY-AT-HOME");
static const u8 sEasyChatWord_Berry[] = _("BERRY");
static const u8 sEasyChatWord_Contest[] = _("CONTEST");
static const u8 sEasyChatWord_Mc[] = _("MC");
static const u8 sEasyChatWord_Judge[] = _("JUDGE");
static const u8 sEasyChatWord_Super[] = _("SUPER");
static const u8 sEasyChatWord_Stage[] = _("STAGE");
static const u8 sEasyChatWord_HallOfFame[] = _("HALL OF FAME");
static const u8 sEasyChatWord_Evolution[] = _("EVOLUTION");
static const u8 sEasyChatWord_Hyper[] = _("HYPER");
static const u8 sEasyChatWord_BattleTower[] = _("BATTLE TOWER");
static const u8 sEasyChatWord_Leaders[] = _("LEADERS");
static const u8 sEasyChatWord_BattleRoom[] = _("BATTLE ROOM");
static const u8 sEasyChatWord_Hidden[] = _("HIDDEN");
static const u8 sEasyChatWord_SecretBase[] = _("SECRET BASE");
static const u8 sEasyChatWord_Blend[] = _("BLEND");
static const u8 sEasyChatWord_POKEBLOCK[] = _("{POKEBLOCK}");
static const u8 sEasyChatWord_Master[] = _("MASTER");
static const u8 sEasyChatWord_Rank[] = _("RANK");
static const u8 sEasyChatWord_Ribbon[] = _("RIBBON");
static const u8 sEasyChatWord_Crush[] = _("CRUSH");
static const u8 sEasyChatWord_Direct[] = _("DIRECT");
static const u8 sEasyChatWord_Tower[] = _("TOWER");
static const u8 sEasyChatWord_Union[] = _("UNION");
static const u8 sEasyChatWord_Room[] = _("ROOM");
static const u8 sEasyChatWord_Wireless[] = _("WIRELESS");

static const struct EasyChatWordInfo sEasyChatGroup_Events[] = {
    {
        .text = sEasyChatWord_Appeal,
        .alphabeticalOrder = 0,
        .enabled = FALSE
    },
    {
        .text = sEasyChatWord_Events,
        .alphabeticalOrder = 14,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_StayAtHome,
        .alphabeticalOrder = 12,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Berry,
        .alphabeticalOrder = 3,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Contest,
        .alphabeticalOrder = 17,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Mc,
        .alphabeticalOrder = 4,
        .enabled = FALSE
    },
    {
        .text = sEasyChatWord_Judge,
        .alphabeticalOrder = 22,
        .enabled = FALSE
    },
    {
        .text = sEasyChatWord_Super,
        .alphabeticalOrder = 23,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Stage,
        .alphabeticalOrder = 1,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_HallOfFame,
        .alphabeticalOrder = 10,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Evolution,
        .alphabeticalOrder = 9,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Hyper,
        .alphabeticalOrder = 15,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_BattleTower,
        .alphabeticalOrder = 11,
        .enabled = FALSE
    },
    {
        .text = sEasyChatWord_Leaders,
        .alphabeticalOrder = 6,
        .enabled = FALSE
    },
    {
        .text = sEasyChatWord_BattleRoom,
        .alphabeticalOrder = 13,
        .enabled = FALSE
    },
    {
        .text = sEasyChatWord_Hidden,
        .alphabeticalOrder = 19,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_SecretBase,
        .alphabeticalOrder = 5,
        .enabled = FALSE
    },
    {
        .text = sEasyChatWord_Blend,
        .alphabeticalOrder = 18,
        .enabled = FALSE
    },
    {
        .text = sEasyChatWord_POKEBLOCK,
        .alphabeticalOrder = 20,
        .enabled = FALSE
    },
    {
        .text = sEasyChatWord_Master,
        .alphabeticalOrder = 21,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Rank,
        .alphabeticalOrder = 26,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Ribbon,
        .alphabeticalOrder = 16,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Crush,
        .alphabeticalOrder = 8,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Direct,
        .alphabeticalOrder = 2,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Tower,
        .alphabeticalOrder = 7,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Union,
        .alphabeticalOrder = 24,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Room,
        .alphabeticalOrder = 25,
        .enabled = TRUE
    },
    {
        .text = sEasyChatWord_Wireless,
        .alphabeticalOrder = 27,
        .enabled = TRUE
    }
};
// ===== END src/data/easy_chat/easy_chat_group_events.h =====
// ===== BEGIN src/data/easy_chat/easy_chat_group_move_1.h =====
#include "constants/moves.h"

static const u16 sEasyChatGroup_Move1[] = {
    MOVE_ABSORB,
    MOVE_AEROBLAST,
    MOVE_AGILITY,
    MOVE_AIR_CUTTER,
    MOVE_ANCIENT_POWER,
    MOVE_AROMATHERAPY,
    MOVE_ASTONISH,
    MOVE_AURORA_BEAM,
    MOVE_BIDE,
    MOVE_BIND,
    MOVE_BITE,
    MOVE_BRICK_BREAK,
    MOVE_BUBBLE,
    MOVE_CHARGE,
    MOVE_CHARM,
    MOVE_CLAMP,
    MOVE_CONFUSE_RAY,
    MOVE_CONSTRICT,
    MOVE_COSMIC_POWER,
    MOVE_COUNTER,
    MOVE_CRABHAMMER,
    MOVE_CROSS_CHOP,
    MOVE_CRUNCH,
    MOVE_CUT,
    MOVE_DIG,
    MOVE_DISABLE,
    MOVE_DOUBLE_TEAM,
    MOVE_DOUBLE_EDGE,
    MOVE_DOUBLE_SLAP,
    MOVE_EARTHQUAKE,
    MOVE_ENCORE,
    MOVE_ENDEAVOR,
    MOVE_ENDURE,
    MOVE_EXTRASENSORY,
    MOVE_EXTREME_SPEED,
    MOVE_FACADE,
    MOVE_FAKE_TEARS,
    MOVE_FISSURE,
    MOVE_FLAIL,
    MOVE_FLAME_WHEEL,
    MOVE_FLAMETHROWER,
    MOVE_FLATTER,
    MOVE_FLY,
    MOVE_FOCUS_ENERGY,
    MOVE_FOCUS_PUNCH,
    MOVE_FOLLOW_ME,
    MOVE_GIGA_DRAIN,
    MOVE_GRASS_WHISTLE,
    MOVE_GROWTH,
    MOVE_GRUDGE,
    MOVE_GUST,
    MOVE_HAIL,
    MOVE_HARDEN,
    MOVE_HAZE,
    MOVE_HEADBUTT,
    MOVE_HEAL_BELL,
    MOVE_HYPNOSIS,
    MOVE_ICE_BALL,
    MOVE_ICY_WIND,
    MOVE_IRON_TAIL,
    MOVE_KARATE_CHOP,
    MOVE_KINESIS,
    MOVE_LEECH_LIFE,
    MOVE_LICK,
    MOVE_LOVELY_KISS,
    MOVE_LOW_KICK,
    MOVE_MEAN_LOOK,
    MOVE_MEMENTO,
    MOVE_METAL_SOUND,
    MOVE_METEOR_MASH,
    MOVE_MIND_READER,
    MOVE_MIRROR_MOVE,
    MOVE_MIST,
    MOVE_MORNING_SUN,
    MOVE_NATURE_POWER,
    MOVE_NIGHTMARE,
    MOVE_OCTAZOOKA,
    MOVE_ODOR_SLEUTH,
    MOVE_OUTRAGE,
    MOVE_OVERHEAT,
    MOVE_PAIN_SPLIT,
    MOVE_POWDER_SNOW,
    MOVE_PSYBEAM,
    MOVE_PSYCH_UP,
    MOVE_PSYCHIC,
    MOVE_PSYCHO_BOOST,
    MOVE_PSYWAVE,
    MOVE_PURSUIT,
    MOVE_RAGE,
    MOVE_RAIN_DANCE,
    MOVE_RAPID_SPIN,
    MOVE_RAZOR_WIND,
    MOVE_RECOVER,
    MOVE_RETURN,
    MOVE_REVERSAL,
    MOVE_ROCK_SLIDE,
    MOVE_ROCK_SMASH,
    MOVE_ROCK_THROW,
    MOVE_ROCK_TOMB,
    MOVE_ROLLOUT,
    MOVE_SACRED_FIRE,
    MOVE_SAFEGUARD,
    MOVE_SAND_TOMB,
    MOVE_SAND_ATTACK,
    MOVE_SANDSTORM,
    MOVE_SCARY_FACE,
    MOVE_SCREECH,
    MOVE_SELF_DESTRUCT,
    MOVE_SHADOW_BALL,
    MOVE_SHADOW_PUNCH,
    MOVE_SHARPEN,
    MOVE_SHEER_COLD,
    MOVE_SIGNAL_BEAM,
    MOVE_SILVER_WIND,
    MOVE_SING,
    MOVE_SKETCH,
    MOVE_SKILL_SWAP,
    MOVE_SKY_ATTACK,
    MOVE_SKY_UPPERCUT,
    MOVE_SLASH,
    MOVE_SMELLING_SALT,
    MOVE_SMOG,
    MOVE_SMOKESCREEN,
    MOVE_SNORE,
    MOVE_SOLAR_BEAM,
    MOVE_SONIC_BOOM,
    MOVE_SPARK,
    MOVE_SPIDER_WEB,
    MOVE_SPITE,
    MOVE_SPORE,
    MOVE_STRENGTH,
    MOVE_STRING_SHOT,
    MOVE_STUN_SPORE,
    MOVE_SUBMISSION,
    MOVE_SUPER_FANG,
    MOVE_SWAGGER,
    MOVE_SWEET_SCENT,
    MOVE_SWIFT,
    MOVE_SYNTHESIS,
    MOVE_TAIL_WHIP,
    MOVE_THRASH,
    MOVE_THUNDER,
    MOVE_THUNDERBOLT,
    MOVE_THUNDER_PUNCH,
    MOVE_TICKLE,
    MOVE_TORMENT,
    MOVE_UPROAR,
    MOVE_VITAL_THROW,
    MOVE_WATER_SPOUT,
    MOVE_WEATHER_BALL,
    MOVE_WHIRLPOOL,
    MOVE_WILL_O_WISP,
    MOVE_WITHDRAW,
    MOVE_YAWN,
};
// ===== END src/data/easy_chat/easy_chat_group_move_1.h =====
// ===== BEGIN src/data/easy_chat/easy_chat_group_move_2.h =====
#include "constants/moves.h"

static const u16 sEasyChatGroup_Move2[] = {
    MOVE_ACID,
    MOVE_ACID_ARMOR,
    MOVE_AERIAL_ACE,
    MOVE_AMNESIA,
    MOVE_ARM_THRUST,
    MOVE_ASSIST,
    MOVE_ATTRACT,
    MOVE_BARRAGE,
    MOVE_BARRIER,
    MOVE_BATON_PASS,
    MOVE_BEAT_UP,
    MOVE_BELLY_DRUM,
    MOVE_BLAST_BURN,
    MOVE_BLAZE_KICK,
    MOVE_BLIZZARD,
    MOVE_BLOCK,
    MOVE_BODY_SLAM,
    MOVE_BONE_CLUB,
    MOVE_BONE_RUSH,
    MOVE_BONEMERANG,
    MOVE_BOUNCE,
    MOVE_BUBBLE_BEAM,
    MOVE_BULK_UP,
    MOVE_BULLET_SEED,
    MOVE_CALM_MIND,
    MOVE_CAMOUFLAGE,
    MOVE_COMET_PUNCH,
    MOVE_CONFUSION,
    MOVE_CONVERSION,
    MOVE_CONVERSION_2,
    MOVE_COTTON_SPORE,
    MOVE_COVET,
    MOVE_CRUSH_CLAW,
    MOVE_CURSE,
    MOVE_DEFENSE_CURL,
    MOVE_DESTINY_BOND,
    MOVE_DETECT,
    MOVE_DIVE,
    MOVE_DIZZY_PUNCH,
    MOVE_DOOM_DESIRE,
    MOVE_DOUBLE_KICK,
    MOVE_DRAGON_CLAW,
    MOVE_DRAGON_DANCE,
    MOVE_DRAGON_RAGE,
    MOVE_DRAGON_BREATH,
    MOVE_DREAM_EATER,
    MOVE_DRILL_PECK,
    MOVE_DYNAMIC_PUNCH,
    MOVE_EGG_BOMB,
    MOVE_EMBER,
    MOVE_ERUPTION,
    MOVE_EXPLOSION,
    MOVE_FAINT_ATTACK,
    MOVE_FAKE_OUT,
    MOVE_FALSE_SWIPE,
    MOVE_FEATHER_DANCE,
    MOVE_FIRE_BLAST,
    MOVE_FIRE_PUNCH,
    MOVE_FIRE_SPIN,
    MOVE_FLASH,
    MOVE_FORESIGHT,
    MOVE_FRENZY_PLANT,
    MOVE_FRUSTRATION,
    MOVE_FURY_ATTACK,
    MOVE_FURY_CUTTER,
    MOVE_FURY_SWIPES,
    MOVE_FUTURE_SIGHT,
    MOVE_GLARE,
    MOVE_GROWL,
    MOVE_GUILLOTINE,
    MOVE_HEAT_WAVE,
    MOVE_HELPING_HAND,
    MOVE_HI_JUMP_KICK,
    MOVE_HIDDEN_POWER,
    MOVE_HORN_ATTACK,
    MOVE_HORN_DRILL,
    MOVE_HOWL,
    MOVE_HYDRO_CANNON,
    MOVE_HYDRO_PUMP,
    MOVE_HYPER_BEAM,
    MOVE_HYPER_FANG,
    MOVE_HYPER_VOICE,
    MOVE_ICE_BEAM,
    MOVE_ICE_PUNCH,
    MOVE_ICICLE_SPEAR,
    MOVE_IMPRISON,
    MOVE_INGRAIN,
    MOVE_IRON_DEFENSE,
    MOVE_JUMP_KICK,
    MOVE_KNOCK_OFF,
    MOVE_LEAF_BLADE,
    MOVE_LEECH_SEED,
    MOVE_LEER,
    MOVE_LIGHT_SCREEN,
    MOVE_LOCK_ON,
    MOVE_LUSTER_PURGE,
    MOVE_MACH_PUNCH,
    MOVE_MAGIC_COAT,
    MOVE_MAGICAL_LEAF,
    MOVE_MAGNITUDE,
    MOVE_MEDITATE,
    MOVE_MEGA_DRAIN,
    MOVE_MEGA_KICK,
    MOVE_MEGA_PUNCH,
    MOVE_MEGAHORN,
    MOVE_METAL_CLAW,
    MOVE_METRONOME,
    MOVE_MILK_DRINK,
    MOVE_MIMIC,
    MOVE_MINIMIZE,
    MOVE_MIRROR_COAT,
    MOVE_MIST_BALL,
    MOVE_MOONLIGHT,
    MOVE_MUD_SHOT,
    MOVE_MUD_SPORT,
    MOVE_MUD_SLAP,
    MOVE_MUDDY_WATER,
    MOVE_NEEDLE_ARM,
    MOVE_NIGHT_SHADE,
    MOVE_PAY_DAY,
    MOVE_PECK,
    MOVE_PERISH_SONG,
    MOVE_PETAL_DANCE,
    MOVE_PIN_MISSILE,
    MOVE_POISON_FANG,
    MOVE_POISON_GAS,
    MOVE_POISON_STING,
    MOVE_POISON_TAIL,
    MOVE_POISON_POWDER,
    MOVE_POUND,
    MOVE_PRESENT,
    MOVE_PROTECT,
    MOVE_QUICK_ATTACK,
    MOVE_RAZOR_LEAF,
    MOVE_RECYCLE,
    MOVE_REFLECT,
    MOVE_REFRESH,
    MOVE_REST,
    MOVE_REVENGE,
    MOVE_ROAR,
    MOVE_ROCK_BLAST,
    MOVE_ROLE_PLAY,
    MOVE_ROLLING_KICK,
    MOVE_SCRATCH,
    MOVE_SECRET_POWER,
    MOVE_SEISMIC_TOSS,
    MOVE_SHOCK_WAVE,
    MOVE_SKULL_BASH,
    MOVE_SLACK_OFF,
    MOVE_SLAM,
    MOVE_SLEEP_POWDER,
    MOVE_SLEEP_TALK,
    MOVE_SLUDGE,
    MOVE_SLUDGE_BOMB,
    MOVE_SNATCH,
    MOVE_SOFT_BOILED,
    MOVE_SPIKE_CANNON,
    MOVE_SPIKES,
    MOVE_SPIT_UP,
    MOVE_SPLASH,
    MOVE_STEEL_WING,
    MOVE_STOCKPILE,
    MOVE_STOMP,
    MOVE_STRUGGLE,
    MOVE_SUBSTITUTE,
    MOVE_SUNNY_DAY,
    MOVE_SUPERPOWER,
    MOVE_SUPERSONIC,
    MOVE_SURF,
    MOVE_SWALLOW,
    MOVE_SWEET_KISS,
    MOVE_SWORDS_DANCE,
    MOVE_TACKLE,
    MOVE_TAIL_GLOW,
    MOVE_TAKE_DOWN,
    MOVE_TAUNT,
    MOVE_TEETER_DANCE,
    MOVE_TELEPORT,
    MOVE_THIEF,
    MOVE_THUNDER_WAVE,
    MOVE_THUNDER_SHOCK,
    MOVE_TOXIC,
    MOVE_TRANSFORM,
    MOVE_TRI_ATTACK,
    MOVE_TRICK,
    MOVE_TRIPLE_KICK,
    MOVE_TWINEEDLE,
    MOVE_TWISTER,
    MOVE_VICE_GRIP,
    MOVE_VINE_WHIP,
    MOVE_VOLT_TACKLE,
    MOVE_WATER_GUN,
    MOVE_WATER_PULSE,
    MOVE_WATER_SPORT,
    MOVE_WATERFALL,
    MOVE_WHIRLWIND,
    MOVE_WING_ATTACK,
    MOVE_WISH,
    MOVE_WRAP,
    MOVE_ZAP_CANNON,
};
// ===== END src/data/easy_chat/easy_chat_group_move_2.h =====
// ===== BEGIN src/data/easy_chat/easy_chat_group_trendy_saying.h =====

static const u8 sEasyChatWord_KthxBye[] = _("KTHX, BYE.");
static const u8 sEasyChatWord_YesSirExcl[] = _("YES, SIR!");
static const u8 sEasyChatWord_AvantGarde[] = _("AVANT GARDE");
static const u8 sEasyChatWord_Couple[] = _("COUPLE");
static const u8 sEasyChatWord_MuchObliged[] = _("MUCH OBLIGED");
static const u8 sEasyChatWord_YeehawExcl[] = _("YEEHAW!");
static const u8 sEasyChatWord_Mega[] = _("MEGA");
static const u8 sEasyChatWord_1HitKOExcl[] = _("1-HIT KO!");
static const u8 sEasyChatWord_Destiny[] = _("DESTINY");
static const u8 sEasyChatWord_Cancel[] = _("CANCEL");
static const u8 sEasyChatWord_New[] = _("NEW");
static const u8 sEasyChatWord_Flatten[] = _("FLATTEN");
static const u8 sEasyChatWord_Kidding[] = _("KIDDING");
static const u8 sEasyChatWord_Loser[] = _("LOSER");
static const u8 sEasyChatWord_Losing[] = _("LOSING");
static const u8 sEasyChatWord_Happening[] = _("HAPPENING");
static const u8 sEasyChatWord_HipAnd[] = _("HIP AND");
static const u8 sEasyChatWord_Shake[] = _("SHAKE");
static const u8 sEasyChatWord_Shady[] = _("SHADY");
static const u8 sEasyChatWord_Upbeat[] = _("UPBEAT");
static const u8 sEasyChatWord_Modern[] = _("MODERN");
static const u8 sEasyChatWord_SmellYa[] = _("SMELL YA");
static const u8 sEasyChatWord_Bang[] = _("BANG");
static const u8 sEasyChatWord_Knockout[] = _("KNOCKOUT");
static const u8 sEasyChatWord_Hassle[] = _("HASSLE");
static const u8 sEasyChatWord_Winner[] = _("WINNER");
static const u8 sEasyChatWord_Fever[] = _("FEVER");
static const u8 sEasyChatWord_Wannabe[] = _("WANNABE");
static const u8 sEasyChatWord_Baby[] = _("BABY");
static const u8 sEasyChatWord_Heart[] = _("HEART");
static const u8 sEasyChatWord_Old[] = _("OLD");
static const u8 sEasyChatWord_Young[] = _("YOUNG");
static const u8 sEasyChatWord_Ugly[] = _("UGLY");

static const struct EasyChatWordInfo sEasyChatGroup_TrendySaying[] = {
    {
        .text = sEasyChatWord_KthxBye,
        .alphabeticalOrder = 7,
        .enabled = FALSE
    },
    {
        .text = sEasyChatWord_YesSirExcl,
        .alphabeticalOrder = 2,
        .enabled = FALSE
    },
    {
        .text = sEasyChatWord_AvantGarde,
        .alphabeticalOrder = 28,
        .enabled = FALSE
    },
    {
        .text = sEasyChatWord_Couple,
        .alphabeticalOrder = 22,
        .enabled = FALSE
    },
    {
        .text = sEasyChatWord_MuchObliged,
        .alphabeticalOrder = 9,
        .enabled = FALSE
    },
    {
        .text = sEasyChatWord_YeehawExcl,
        .alphabeticalOrder = 3,
        .enabled = FALSE
    },
    {
        .text = sEasyChatWord_Mega,
        .alphabeticalOrder = 8,
        .enabled = FALSE
    },
    {
        .text = sEasyChatWord_1HitKOExcl,
        .alphabeticalOrder = 26,
        .enabled = FALSE
    },
    {
        .text = sEasyChatWord_Destiny,
        .alphabeticalOrder = 11,
        .enabled = FALSE
    },
    {
        .text = sEasyChatWord_Cancel,
        .alphabeticalOrder = 15,
        .enabled = FALSE
    },
    {
        .text = sEasyChatWord_New,
        .alphabeticalOrder = 24,
        .enabled = FALSE
    },
    {
        .text = sEasyChatWord_Flatten,
        .alphabeticalOrder = 29,
        .enabled = FALSE
    },
    {
        .text = sEasyChatWord_Kidding,
        .alphabeticalOrder = 16,
        .enabled = FALSE
    },
    {
        .text = sEasyChatWord_Loser,
        .alphabeticalOrder = 12,
        .enabled = FALSE
    },
    {
        .text = sEasyChatWord_Losing,
        .alphabeticalOrder = 23,
        .enabled = FALSE
    },
    {
        .text = sEasyChatWord_Happening,
        .alphabeticalOrder = 0,
        .enabled = FALSE
    },
    {
        .text = sEasyChatWord_HipAnd,
        .alphabeticalOrder = 13,
        .enabled = FALSE
    },
    {
        .text = sEasyChatWord_Shake,
        .alphabeticalOrder = 14,
        .enabled = FALSE
    },
    {
        .text = sEasyChatWord_Shady,
        .alphabeticalOrder = 6,
        .enabled = FALSE
    },
    {
        .text = sEasyChatWord_Upbeat,
        .alphabeticalOrder = 20,
        .enabled = FALSE
    },
    {
        .text = sEasyChatWord_Modern,
        .alphabeticalOrder = 4,
        .enabled = FALSE
    },
    {
        .text = sEasyChatWord_SmellYa,
        .alphabeticalOrder = 10,
        .enabled = FALSE
    },
    {
        .text = sEasyChatWord_Bang,
        .alphabeticalOrder = 30,
        .enabled = FALSE
    },
    {
        .text = sEasyChatWord_Knockout,
        .alphabeticalOrder = 18,
        .enabled = FALSE
    },
    {
        .text = sEasyChatWord_Hassle,
        .alphabeticalOrder = 17,
        .enabled = FALSE
    },
    {
        .text = sEasyChatWord_Winner,
        .alphabeticalOrder = 21,
        .enabled = FALSE
    },
    {
        .text = sEasyChatWord_Fever,
        .alphabeticalOrder = 32,
        .enabled = FALSE
    },
    {
        .text = sEasyChatWord_Wannabe,
        .alphabeticalOrder = 19,
        .enabled = FALSE
    },
    {
        .text = sEasyChatWord_Baby,
        .alphabeticalOrder = 27,
        .enabled = FALSE
    },
    {
        .text = sEasyChatWord_Heart,
        .alphabeticalOrder = 25,
        .enabled = FALSE
    },
    {
        .text = sEasyChatWord_Old,
        .alphabeticalOrder = 5,
        .enabled = FALSE
    },
    {
        .text = sEasyChatWord_Young,
        .alphabeticalOrder = 1,
        .enabled = FALSE
    },
    {
        .text = sEasyChatWord_Ugly,
        .alphabeticalOrder = 31,
        .enabled = FALSE
    }
};
// ===== END src/data/easy_chat/easy_chat_group_trendy_saying.h =====
// ===== BEGIN src/data/easy_chat/easy_chat_group_pokemon2.h =====
static const u16 sEasyChatGroup_Pokemon2[] = {
	SPECIES_ABRA,
	SPECIES_AERODACTYL,
	SPECIES_AIPOM,
	SPECIES_ALAKAZAM,
	SPECIES_AMPHAROS,
	SPECIES_ARBOK,
	SPECIES_ARCANINE,
	SPECIES_ARIADOS,
	SPECIES_ARTICUNO,
	SPECIES_AZUMARILL,
	SPECIES_BAYLEEF,
	SPECIES_BEEDRILL,
	SPECIES_BELLOSSOM,
	SPECIES_BELLSPROUT,
	SPECIES_BLASTOISE,
	SPECIES_BLISSEY,
	SPECIES_BULBASAUR,
	SPECIES_BUTTERFREE,
	SPECIES_CATERPIE,
	SPECIES_CELEBI,
	SPECIES_CHANSEY,
	SPECIES_CHARIZARD,
	SPECIES_CHARMANDER,
	SPECIES_CHARMELEON,
	SPECIES_CHIKORITA,
	SPECIES_CHINCHOU,
	SPECIES_CLEFABLE,
	SPECIES_CLEFAIRY,
	SPECIES_CLEFFA,
	SPECIES_CLOYSTER,
	SPECIES_CORSOLA,
	SPECIES_CROBAT,
	SPECIES_CROCONAW,
	SPECIES_CUBONE,
	SPECIES_CYNDAQUIL,
	SPECIES_DELIBIRD,
	SPECIES_DEWGONG,
	SPECIES_DIGLETT,
	SPECIES_DITTO,
	SPECIES_DODRIO,
	SPECIES_DODUO,
	SPECIES_DONPHAN,
	SPECIES_DRAGONAIR,
	SPECIES_DRAGONITE,
	SPECIES_DRATINI,
	SPECIES_DROWZEE,
	SPECIES_DUGTRIO,
	SPECIES_DUNSPARCE,
	SPECIES_EEVEE,
	SPECIES_EKANS,
	SPECIES_ELECTABUZZ,
	SPECIES_ELECTRODE,
	SPECIES_ELEKID,
	SPECIES_ENTEI,
	SPECIES_ESPEON,
	SPECIES_EXEGGCUTE,
	SPECIES_EXEGGUTOR,
	SPECIES_FARFETCHD,
	SPECIES_FEAROW,
	SPECIES_FERALIGATR,
	SPECIES_FLAAFFY,
	SPECIES_FLAREON,
	SPECIES_FORRETRESS,
	SPECIES_FURRET,
	SPECIES_GASTLY,
	SPECIES_GENGAR,
	SPECIES_GEODUDE,
	SPECIES_GIRAFARIG,
	SPECIES_GLIGAR,
	SPECIES_GLOOM,
	SPECIES_GOLBAT,
	SPECIES_GOLDEEN,
	SPECIES_GOLDUCK,
	SPECIES_GOLEM,
	SPECIES_GRANBULL,
	SPECIES_GRAVELER,
	SPECIES_GRIMER,
	SPECIES_GROWLITHE,
	SPECIES_GYARADOS,
	SPECIES_HAUNTER,
	SPECIES_HERACROSS,
	SPECIES_HITMONCHAN,
	SPECIES_HITMONLEE,
	SPECIES_HITMONTOP,
	SPECIES_HO_OH,
	SPECIES_HOOTHOOT,
	SPECIES_HOPPIP,
	SPECIES_HORSEA,
	SPECIES_HOUNDOOM,
	SPECIES_HOUNDOUR,
	SPECIES_HYPNO,
	SPECIES_IGGLYBUFF,
	SPECIES_IVYSAUR,
	SPECIES_JIGGLYPUFF,
	SPECIES_JOLTEON,
	SPECIES_JUMPLUFF,
	SPECIES_JYNX,
	SPECIES_KABUTO,
	SPECIES_KABUTOPS,
	SPECIES_KADABRA,
	SPECIES_KAKUNA,
	SPECIES_KANGASKHAN,
	SPECIES_KINGDRA,
	SPECIES_KINGLER,
	SPECIES_KOFFING,
	SPECIES_KRABBY,
	SPECIES_LANTURN,
	SPECIES_LAPRAS,
	SPECIES_LARVITAR,
	SPECIES_LEDIAN,
	SPECIES_LEDYBA,
	SPECIES_LICKITUNG,
	SPECIES_LUGIA,
	SPECIES_MACHAMP,
	SPECIES_MACHOKE,
	SPECIES_MACHOP,
	SPECIES_MAGBY,
	SPECIES_MAGCARGO,
	SPECIES_MAGIKARP,
	SPECIES_MAGMAR,
	SPECIES_MAGNEMITE,
	SPECIES_MAGNETON,
	SPECIES_MANKEY,
	SPECIES_MANTINE,
	SPECIES_MAREEP,
	SPECIES_MARILL,
	SPECIES_MAROWAK,
	SPECIES_MEGANIUM,
	SPECIES_MEOWTH,
	SPECIES_METAPOD,
	SPECIES_MEW,
	SPECIES_MEWTWO,
	SPECIES_MILTANK,
	SPECIES_MISDREAVUS,
	SPECIES_MOLTRES,
	SPECIES_MR_MIME,
	SPECIES_MUK,
	SPECIES_MURKROW,
	SPECIES_NATU,
	SPECIES_NIDOKING,
	SPECIES_NIDOQUEEN,
	SPECIES_NIDORAN_F,
	SPECIES_NIDORAN_M,
	SPECIES_NIDORINA,
	SPECIES_NIDORINO,
	SPECIES_NINETALES,
	SPECIES_NOCTOWL,
	SPECIES_OCTILLERY,
	SPECIES_ODDISH,
	SPECIES_OMANYTE,
	SPECIES_OMASTAR,
	SPECIES_ONIX,
	SPECIES_PARAS,
	SPECIES_PARASECT,
	SPECIES_PERSIAN,
	SPECIES_PHANPY,
	SPECIES_PICHU,
	SPECIES_PIDGEOT,
	SPECIES_PIDGEOTTO,
	SPECIES_PIDGEY,
	SPECIES_PIKACHU,
	SPECIES_PILOSWINE,
	SPECIES_PINECO,
	SPECIES_PINSIR,
	SPECIES_POLITOED,
	SPECIES_POLIWAG,
	SPECIES_POLIWHIRL,
	SPECIES_POLIWRATH,
	SPECIES_PONYTA,
	SPECIES_PORYGON,
	SPECIES_PORYGON2,
	SPECIES_PRIMEAPE,
	SPECIES_PSYDUCK,
	SPECIES_PUPITAR,
	SPECIES_QUAGSIRE,
	SPECIES_QUILAVA,
	SPECIES_QWILFISH,
	SPECIES_RAICHU,
	SPECIES_RAIKOU,
	SPECIES_RAPIDASH,
	SPECIES_RATICATE,
	SPECIES_RATTATA,
	SPECIES_REMORAID,
	SPECIES_RHYDON,
	SPECIES_RHYHORN,
	SPECIES_SANDSHREW,
	SPECIES_SANDSLASH,
	SPECIES_SCIZOR,
	SPECIES_SCYTHER,
	SPECIES_SEADRA,
	SPECIES_SEAKING,
	SPECIES_SEEL,
	SPECIES_SENTRET,
	SPECIES_SHELLDER,
	SPECIES_SHUCKLE,
	SPECIES_SKARMORY,
	SPECIES_SKIPLOOM,
	SPECIES_SLOWBRO,
	SPECIES_SLOWKING,
	SPECIES_SLOWPOKE,
	SPECIES_SLUGMA,
	SPECIES_SMEARGLE,
	SPECIES_SMOOCHUM,
	SPECIES_SNEASEL,
	SPECIES_SNORLAX,
	SPECIES_SNUBBULL,
	SPECIES_SPEAROW,
	SPECIES_SPINARAK,
	SPECIES_SQUIRTLE,
	SPECIES_STANTLER,
	SPECIES_STARMIE,
	SPECIES_STARYU,
	SPECIES_STEELIX,
	SPECIES_SUDOWOODO,
	SPECIES_SUICUNE,
	SPECIES_SUNFLORA,
	SPECIES_SUNKERN,
	SPECIES_SWINUB,
	SPECIES_TANGELA,
	SPECIES_TAUROS,
	SPECIES_TEDDIURSA,
	SPECIES_TENTACOOL,
	SPECIES_TENTACRUEL,
	SPECIES_TOGEPI,
	SPECIES_TOGETIC,
	SPECIES_TOTODILE,
	SPECIES_TYPHLOSION,
	SPECIES_TYRANITAR,
	SPECIES_TYROGUE,
	SPECIES_UMBREON,
	SPECIES_UNOWN,
	SPECIES_URSARING,
	SPECIES_VAPOREON,
	SPECIES_VENOMOTH,
	SPECIES_VENONAT,
	SPECIES_VENUSAUR,
	SPECIES_VICTREEBEL,
	SPECIES_VILEPLUME,
	SPECIES_VOLTORB,
	SPECIES_VULPIX,
	SPECIES_WARTORTLE,
	SPECIES_WEEDLE,
	SPECIES_WEEPINBELL,
	SPECIES_WEEZING,
	SPECIES_WIGGLYTUFF,
	SPECIES_WOBBUFFET,
	SPECIES_WOOPER,
	SPECIES_XATU,
	SPECIES_YANMA,
	SPECIES_ZAPDOS,
	SPECIES_ZUBAT,
};
// ===== END src/data/easy_chat/easy_chat_group_pokemon2.h =====

static const struct EasyChatGroup sEasyChatGroups[] = {
    {
        .wordData = {.valueList = sEasyChatGroup_Pokemon},
        .numWords = 202,
        .numEnabledWords = 202
    },
    {
        .wordData = {.words = sEasyChatGroup_Trainer},
        .numWords = 26,
        .numEnabledWords = 25
    },
    {
        .wordData = {.words = sEasyChatGroup_Status},
        .numWords = 109,
        .numEnabledWords = 109
    },
    {
        .wordData = {.words = sEasyChatGroup_Battle},
        .numWords = 63,
        .numEnabledWords = 63
    },
    {
        .wordData = {.words = sEasyChatGroup_Greetings},
        .numWords = 42,
        .numEnabledWords = 42
    },
    {
        .wordData = {.words = sEasyChatGroup_People},
        .numWords = 75,
        .numEnabledWords = 75
    },
    {
        .wordData = {.words = sEasyChatGroup_Voices},
        .numWords = 63,
        .numEnabledWords = 63
    },
    {
        .wordData = {.words = sEasyChatGroup_Speech},
        .numWords = 60,
        .numEnabledWords = 60
    },
    {
        .wordData = {.words = sEasyChatGroup_Endings},
        .numWords = 69,
        .numEnabledWords = 69
    },
    {
        .wordData = {.words = sEasyChatGroup_Feelings},
        .numWords = 69,
        .numEnabledWords = 69
    },
    {
        .wordData = {.words = sEasyChatGroup_Conditions},
        .numWords = 69,
        .numEnabledWords = 69
    },
    {
        .wordData = {.words = sEasyChatGroup_Actions},
        .numWords = 78,
        .numEnabledWords = 78
    },
    {
        .wordData = {.words = sEasyChatGroup_Lifestyle},
        .numWords = 45,
        .numEnabledWords = 45
    },
    {
        .wordData = {.words = sEasyChatGroup_Hobbies},
        .numWords = 54,
        .numEnabledWords = 54
    },
    {
        .wordData = {.words = sEasyChatGroup_Time},
        .numWords = 45,
        .numEnabledWords = 45
    },
    {
        .wordData = {.words = sEasyChatGroup_Misc},
        .numWords = 42,
        .numEnabledWords = 42
    },
    {
        .wordData = {.words = sEasyChatGroup_Adjectives},
        .numWords = 36,
        .numEnabledWords = 36
    },
    {
        .wordData = {.words = sEasyChatGroup_Events},
        .numWords = 28,
        .numEnabledWords = 19
    },
    {
        .wordData = {.valueList = sEasyChatGroup_Move1},
        .numWords = 154,
        .numEnabledWords = 154
    },
    {
        .wordData = {.valueList = sEasyChatGroup_Move2},
        .numWords = 200,
        .numEnabledWords = 200
    },
    {
        .wordData = {.words = sEasyChatGroup_TrendySaying},
        .numWords = 33,
        .numEnabledWords = 0
    },
    {
        .wordData = {.valueList = sEasyChatGroup_Pokemon2},
        .numWords = 251,
        .numEnabledWords = 251
    },
};
// ===== END src/data/easy_chat/easy_chat_groups.h =====
// ===== BEGIN src/data/easy_chat/easy_chat_words_by_letter.h =====
#include "easy_chat.h"
#include "constants/easy_chat.h"

static const u16 sEasyChatWordsByLetter_Others[] = {
    EC_WORD_EXCL,
    EC_WORD_EXCL_EXCL,
    EC_WORD_DASH,
    EC_WORD_DASH_DASH_DASH,
    EC_WORD_ELLIPSIS,
    EC_WORD_ELLIPSIS_EXCL,
    EC_WORD_ELLIPSIS_ELLIPSIS_ELLIPSIS,
    EC_WORD_1_HIT_KO_EXCL,
    EC_WORD_QUES,
    EC_WORD_QUES_EXCL,
};

static const u16 sEasyChatWordsByLetter_A[] = {
    EC_WORD_A,
    EC_WORD_A_LITTLE,
    EC_WORD_A_LOT,
    EC_WORD_A_TINY_BIT,
    EC_WORD_ABOUT,
    EC_WORD_ABOVE,
    -1, 2, // Doubled pokemon species name
    EC_POKEMON2(ABRA),
    EC_POKEMON(ABRA),
    EC_WORD_ABSENT,
    EC_POKEMON2(ABSOL),
    EC_WORD_ABSOLUTELY,
    EC_MOVE(ABSORB),
    EC_WORD_ACCEPT,
    EC_MOVE2(ACID),
    EC_MOVE2(ACID_ARMOR),
    EC_WORD_ADORE,
    EC_WORD_ADULT,
    EC_WORD_ADVENTURE,
    EC_MOVE2(AERIAL_ACE),
    EC_MOVE(AEROBLAST),
    EC_POKEMON(AERODACTYL),
    EC_WORD_AFTER,
    EC_WORD_AGE,
    EC_POKEMON2(AGGRON),
    EC_MOVE(AGILITY),
    EC_WORD_AGREE,
    EC_WORD_AHAHA,
    EC_WORD_AIM,
    EC_POKEMON(AIPOM),
    EC_MOVE(AIR_CUTTER),
    EC_WORD_AIR_LOCK,
    EC_WORD_AIYEEH,
    -1, 2, // Doubled pokemon species name
    EC_POKEMON2(ALAKAZAM),
    EC_POKEMON(ALAKAZAM),
    EC_WORD_ALL,
    EC_WORD_ALL_RIGHT,
    EC_WORD_ALLOW,
    EC_WORD_ALLOWANCE,
    EC_WORD_ALLY,
    EC_WORD_ALMOST,
    EC_WORD_ALONE,
    EC_WORD_ALSO,
    EC_WORD_ALT_COLOR,
    EC_POKEMON2(ALTARIA),
    EC_WORD_ALTHOUGH,
    EC_WORD_ALWAYS,
    EC_WORD_AM,
    EC_MOVE2(AMNESIA),
    EC_POKEMON(AMPHAROS),
    EC_WORD_AMUSING,
    EC_WORD_AN,
    EC_MOVE(ANCIENT_POWER),
    EC_WORD_AND,
    EC_WORD_ANGER,
    EC_WORD_ANGERS,
    EC_WORD_ANGRY,
    EC_WORD_ANIME,
    EC_POKEMON2(ANORITH),
    EC_WORD_ANOTHER,
    EC_WORD_ANTICIPATION,
    EC_WORD_ANY,
    EC_WORD_ANYWHERE,
    EC_WORD_APOLOGIZE,
    EC_WORD_APPEAL,
    EC_WORD_APPEAR,
    EC_WORD_APPEARS,
    EC_WORD_APPRECIATE,
    EC_WORD_APPROVED,
    EC_POKEMON(ARBOK),
    EC_POKEMON(ARCANINE),
    EC_WORD_ARE,
    EC_WORD_AREN_T,
    EC_WORD_ARENA_TRAP,
    EC_POKEMON(ARIADOS),
    EC_MOVE2(ARM_THRUST),
    EC_POKEMON2(ARMALDO),
    EC_MOVE(AROMATHERAPY),
    EC_POKEMON2(ARON),
    EC_WORD_AROUND,
    EC_WORD_ARRGH,
    EC_POKEMON(ARTICUNO),
    EC_WORD_AS,
    EC_WORD_AS_IF,
    EC_WORD_AS_MUCH_AS,
    EC_MOVE2(ASSIST),
    EC_MOVE(ASTONISH),
    EC_WORD_AT,
    EC_WORD_ATTACK,
    EC_MOVE2(ATTRACT),
    EC_WORD_AUNT,
    EC_MOVE(AURORA_BEAM),
    EC_WORD_AVANT_GARDE,
    EC_WORD_AWAY,
    EC_WORD_AWESOME,
    EC_WORD_AWFUL,
    EC_WORD_AWFULLY,
    EC_WORD_AWW,
    -1, 2, // Doubled pokemon species name
    EC_POKEMON2(AZUMARILL),
    EC_POKEMON(AZUMARILL),
    EC_POKEMON2(AZURILL),
};

static const u16 sEasyChatWordsByLetter_B[] = {
    EC_WORD_BABE,
    EC_WORD_BABY,
    EC_WORD_BACK,
    EC_WORD_BAD,
    EC_WORD_BADLY,
    EC_WORD_BAG,
    EC_POKEMON2(BAGON),
    EC_WORD_BALL,
    EC_POKEMON2(BALTOY),
    EC_POKEMON2(BANETTE),
    EC_WORD_BANG,
    EC_POKEMON2(BARBOACH),
    EC_MOVE2(BARRAGE),
    EC_MOVE2(BARRIER),
    EC_WORD_BATH,
    EC_MOVE2(BATON_PASS),
    EC_WORD_BATTLE,
    EC_WORD_BATTLE_ARMOR,
    EC_WORD_BATTLE_ROOM,
    EC_WORD_BATTLE_TOWER,
    EC_POKEMON(BAYLEEF),
    EC_WORD_BE,
    EC_WORD_BEAT,
    EC_MOVE2(BEAT_UP),
    EC_POKEMON2(BEAUTIFLY),
    EC_WORD_BEAUTIFUL,
    EC_WORD_BEAUTY,
    EC_WORD_BECOMES,
    EC_POKEMON(BEEDRILL),
    EC_WORD_BEEN,
    EC_WORD_BEFORE,
    EC_WORD_BEGINNING,
    EC_WORD_BEING,
    EC_POKEMON2(BELDUM),
    EC_WORD_BELIEVE,
    -1, 2, // Doubled pokemon species name
    EC_POKEMON2(BELLOSSOM),
    EC_POKEMON(BELLOSSOM),
    EC_POKEMON(BELLSPROUT),
    EC_MOVE2(BELLY_DRUM),
    EC_WORD_BELONGS_TO,
    EC_WORD_BELOW,
    EC_WORD_BERRY,
    EC_WORD_BESIDE,
    EC_WORD_BEST,
    EC_WORD_BETTER,
    EC_MOVE(BIDE),
    EC_WORD_BIG,
    EC_WORD_BIKE,
    EC_MOVE(BIND),
    EC_MOVE(BITE),
    EC_MOVE2(BLAST_BURN),
    EC_POKEMON(BLASTOISE),
    EC_WORD_BLAZE,
    EC_MOVE2(BLAZE_KICK),
    EC_POKEMON2(BLAZIKEN),
    EC_WORD_BLEND,
    EC_POKEMON(BLISSEY),
    EC_MOVE2(BLIZZARD),
    EC_MOVE2(BLOCK),
    EC_WORD_BOARD,
    EC_MOVE2(BODY_SLAM),
    EC_MOVE2(BONE_CLUB),
    EC_MOVE2(BONE_RUSH),
    EC_MOVE2(BONEMERANG),
    EC_WORD_BOOK,
    EC_WORD_BORED,
    EC_WORD_BORING,
    EC_MOVE2(BOUNCE),
    EC_WORD_BOY,
    EC_WORD_BRAG,
    EC_WORD_BREAK,
    EC_POKEMON2(BRELOOM),
    EC_MOVE(BRICK_BREAK),
    EC_WORD_BROTHER,
    EC_MOVE(BUBBLE),
    EC_MOVE2(BUBBLE_BEAM),
    EC_WORD_BUG,
    EC_POKEMON(BULBASAUR),
    EC_MOVE2(BULK_UP),
    EC_MOVE2(BULLET_SEED),
    EC_WORD_BUSY,
    EC_WORD_BUT,
    EC_POKEMON(BUTTERFREE),
    EC_WORD_BYE_BYE,
};

static const u16 sEasyChatWordsByLetter_C[] = {
    EC_POKEMON2(CACNEA),
    EC_POKEMON2(CACTURNE),
    EC_MOVE2(CALM_MIND),
    EC_WORD_CAME,
    EC_WORD_CAMERA,
    EC_POKEMON2(CAMERUPT),
    EC_MOVE2(CAMOUFLAGE),
    EC_WORD_CAN,
    EC_WORD_CAN_WIN,
    EC_WORD_CAN_T,
    EC_WORD_CAN_T_WIN,
    EC_WORD_CANCEL,
    EC_WORD_CAPABLE,
    EC_WORD_CARDS,
    EC_WORD_CARE,
    EC_WORD_CARES,
    EC_POKEMON2(CARVANHA),
    EC_POKEMON2(CASCOON),
    EC_WORD_CASE,
    EC_POKEMON2(CASTFORM),
    EC_POKEMON(CATERPIE),
    EC_WORD_CAUSE,
    EC_POKEMON(CELEBI),
    EC_WORD_CENTER,
    EC_WORD_CHALLENGE,
    EC_WORD_CHANGE,
    EC_WORD_CHANNEL,
    EC_POKEMON(CHANSEY),
    EC_MOVE(CHARGE),
    EC_POKEMON(CHARIZARD),
    EC_MOVE(CHARM),
    EC_POKEMON(CHARMANDER),
    EC_POKEMON(CHARMELEON),
    EC_WORD_CHAT,
    EC_POKEMON(CHIKORITA),
    EC_WORD_CHILD_S_PLAY,
    EC_WORD_CHILDREN,
    EC_POKEMON2(CHIMECHO),
    -1, 2, // Doubled pokemon species name
    EC_POKEMON2(CHINCHOU),
    EC_POKEMON(CHINCHOU),
    EC_WORD_CHLOROPHYLL,
    EC_WORD_CHOICE,
    EC_WORD_CHOOSE,
    EC_WORD_CHORES,
    EC_MOVE(CLAMP),
    EC_POKEMON2(CLAMPERL),
    EC_WORD_CLASS,
    EC_POKEMON2(CLAYDOL),
    EC_WORD_CLEAR_BODY,
    EC_POKEMON(CLEFABLE),
    EC_POKEMON(CLEFAIRY),
    EC_POKEMON(CLEFFA),
    EC_WORD_CLOSE,
    EC_WORD_CLOUD_NINE,
    EC_POKEMON(CLOYSTER),
    EC_WORD_COLD,
    EC_WORD_COLLECT,
    EC_WORD_COLLECTION,
    EC_WORD_COLOR,
    EC_WORD_COLOR_CHANGE,
    EC_POKEMON2(COMBUSKEN),
    EC_WORD_COME,
    EC_WORD_COME_ON,
    EC_WORD_COME_OVER,
    EC_MOVE2(COMET_PUNCH),
    EC_WORD_COMICS,
    EC_WORD_COMMEMORATE,
    EC_WORD_COMPLETE,
    EC_WORD_COMPOUNDEYES,
    EC_WORD_CONCEDE,
    EC_MOVE(CONFUSE_RAY),
    EC_WORD_CONFUSED,
    EC_MOVE2(CONFUSION),
    EC_WORD_CONGRATS,
    EC_MOVE(CONSTRICT),
    EC_WORD_CONTEST,
    EC_WORD_CONVERSATION,
    EC_MOVE2(CONVERSION),
    EC_MOVE2(CONVERSION_2),
    EC_WORD_COOL,
    EC_WORD_COOLNESS,
    EC_POKEMON2(CORPHISH),
    EC_WORD_CORRECT,
    -1, 2, // Doubled pokemon species name
    EC_POKEMON2(CORSOLA),
    EC_POKEMON(CORSOLA),
    EC_MOVE(COSMIC_POWER),
    EC_MOVE2(COTTON_SPORE),
    EC_WORD_COULD,
    EC_WORD_COULDN_T,
    EC_WORD_COUNT_ON,
    EC_MOVE(COUNTER),
    EC_WORD_COUPLE,
    EC_MOVE2(COVET),
    EC_MOVE(CRABHAMMER),
    EC_POKEMON2(CRADILY),
    EC_POKEMON2(CRAWDAUNT),
    EC_WORD_CRIES,
    -1, 2, // Doubled pokemon species name
    EC_POKEMON2(CROBAT),
    EC_POKEMON(CROBAT),
    EC_POKEMON(CROCONAW),
    EC_MOVE(CROSS_CHOP),
    EC_MOVE(CRUNCH),
    EC_WORD_CRUSH,
    EC_MOVE2(CRUSH_CLAW),
    EC_WORD_CRY,
    EC_POKEMON(CUBONE),
    EC_WORD_CURRENT,
    EC_MOVE2(CURSE),
    EC_MOVE(CUT),
    EC_WORD_CUTE,
    EC_WORD_CUTE_CHARM,
    EC_WORD_CUTENESS,
    EC_POKEMON(CYNDAQUIL),
};

static const u16 sEasyChatWordsByLetter_D[] = {
    EC_WORD_DAILY,
    EC_WORD_DAMP,
    EC_WORD_DANCE,
    EC_WORD_DANGER,
    EC_WORD_DARK,
    EC_WORD_DARN,
    EC_WORD_DATE,
    EC_WORD_DAUGHTER,
    EC_WORD_DAY,
    EC_WORD_DAYS,
    EC_WORD_DAYTIME,
    EC_WORD_DECIDE,
    EC_WORD_DECIDED,
    EC_WORD_DEEP,
    EC_WORD_DEFEATED,
    EC_MOVE2(DEFENSE_CURL),
    EC_POKEMON2(DELCATTY),
    EC_POKEMON(DELIBIRD),
    EC_POKEMON2(DEOXYS),
    EC_WORD_DEPT_STORE,
    EC_WORD_DESIGN,
    EC_WORD_DESTINY,
    EC_MOVE2(DESTINY_BOND),
    EC_WORD_DESTROYED,
    EC_MOVE2(DETECT),
    EC_POKEMON(DEWGONG),
    EC_WORD_DID,
    EC_WORD_DIDN_T,
    EC_WORD_DIET,
    EC_WORD_DIFFERENT,
    EC_MOVE(DIG),
    EC_WORD_DIGITAL,
    EC_POKEMON(DIGLETT),
    EC_WORD_DIRECT,
    EC_MOVE(DISABLE),
    EC_WORD_DISAPPEAR,
    EC_WORD_DISAPPOINT,
    EC_WORD_DISAPPOINTED,
    EC_WORD_DISAPPOINTS,
    EC_WORD_DISASTER,
    EC_WORD_DISLIKE,
    EC_WORD_DISLIKES,
    EC_POKEMON(DITTO),
    EC_MOVE2(DIVE),
    EC_MOVE2(DIZZY_PUNCH),
    EC_WORD_DO,
    EC_WORD_DOCILE,
    -1, 2, // Doubled pokemon species name
    EC_POKEMON2(DODRIO),
    EC_POKEMON(DODRIO),
    -1, 2, // Doubled pokemon species name
    EC_POKEMON2(DODUO),
    EC_POKEMON(DODUO),
    EC_WORD_DOES,
    EC_WORD_DOESN_T,
    EC_WORD_DON_T,
    EC_WORD_DONE,
    -1, 2, // Doubled pokemon species name
    EC_POKEMON2(DONPHAN),
    EC_POKEMON(DONPHAN),
    EC_MOVE2(DOOM_DESIRE),
    EC_MOVE2(DOUBLE_KICK),
    EC_MOVE(DOUBLE_TEAM),
    EC_MOVE(DOUBLE_EDGE),
    EC_MOVE(DOUBLE_SLAP),
    EC_WORD_DOWN,
    EC_WORD_DOWNCAST,
    EC_WORD_DRAGON,
    EC_MOVE2(DRAGON_CLAW),
    EC_MOVE2(DRAGON_DANCE),
    EC_MOVE2(DRAGON_RAGE),
    EC_POKEMON(DRAGONAIR),
    EC_MOVE2(DRAGON_BREATH),
    EC_POKEMON(DRAGONITE),
    EC_POKEMON(DRATINI),
    EC_WORD_DREAM,
    EC_MOVE2(DREAM_EATER),
    EC_MOVE2(DRILL_PECK),
    EC_WORD_DRINK,
    EC_WORD_DRINKS,
    EC_WORD_DRIZZLE,
    EC_WORD_DROOLING,
    EC_WORD_DROUGHT,
    EC_POKEMON(DROWZEE),
    EC_WORD_DUDE,
    EC_POKEMON(DUGTRIO),
    EC_POKEMON(DUNSPARCE),
    EC_POKEMON2(DUSCLOPS),
    EC_POKEMON2(DUSKULL),
    EC_POKEMON2(DUSTOX),
    EC_MOVE2(DYNAMIC_PUNCH),
};

static const u16 sEasyChatWordsByLetter_E[] = {
    EC_WORD_EARLIER,
    EC_WORD_EARLY_BIRD,
    EC_MOVE(EARTHQUAKE),
    EC_WORD_EASY,
    EC_WORD_EAT,
    EC_WORD_EATS,
    EC_WORD_EEK,
    EC_POKEMON(EEVEE),
    EC_WORD_EFFECT_SPORE,
    EC_WORD_EGG,
    EC_MOVE2(EGG_BOMB),
    EC_WORD_EH_QUES,
    EC_WORD_EHEHE,
    EC_POKEMON(EKANS),
    EC_POKEMON(ELECTABUZZ),
    EC_WORD_ELECTRIC,
    EC_POKEMON2(ELECTRIKE),
    -1, 2, // Doubled pokemon species name
    EC_POKEMON2(ELECTRODE),
    EC_POKEMON(ELECTRODE),
    EC_POKEMON(ELEKID),
    EC_WORD_ELSE,
    EC_MOVE2(EMBER),
    EC_MOVE(ENCORE),
    EC_WORD_ENCYCLOPEDIA,
    EC_WORD_END,
    EC_MOVE(ENDEAVOR),
    EC_MOVE(ENDURE),
    EC_WORD_ENJOY,
    EC_WORD_ENJOYS,
    EC_WORD_ENOUGH,
    EC_POKEMON(ENTEI),
    EC_WORD_ENTERTAINING,
    EC_MOVE2(ERUPTION),
    EC_WORD_ESCAPE,
    EC_POKEMON(ESPEON),
    EC_WORD_EVEN_SO,
    EC_WORD_EVENT,
    EC_WORD_EVENTS,
    EC_WORD_EVER,
    EC_WORD_EVERY,
    EC_WORD_EVOLUTION,
    EC_WORD_EVOLVE,
    EC_WORD_EXCELLENT,
    EC_WORD_EXCESS,
    EC_WORD_EXCITE,
    EC_WORD_EXCITING,
    EC_WORD_EXCUSE,
    EC_WORD_EXCUSE_ME,
    EC_POKEMON(EXEGGCUTE),
    EC_POKEMON(EXEGGUTOR),
    EC_WORD_EXISTS,
    EC_WORD_EXPENSIVE,
    EC_MOVE2(EXPLOSION),
    EC_POKEMON2(EXPLOUD),
    EC_MOVE(EXTRASENSORY),
    EC_MOVE(EXTREME_SPEED),
};

static const u16 sEasyChatWordsByLetter_F[] = {
    EC_WORD_FABULOUS,
    EC_MOVE(FACADE),
    EC_WORD_FAINT,
    EC_MOVE2(FAINT_ATTACK),
    EC_WORD_FAINTED,
    EC_MOVE2(FAKE_OUT),
    EC_MOVE(FAKE_TEARS),
    EC_WORD_FALL,
    EC_MOVE2(FALSE_SWIPE),
    EC_WORD_FAMILY,
    EC_WORD_FANTASTIC,
    EC_WORD_FAR,
    EC_POKEMON(FARFETCHD),
    EC_WORD_FASHION,
    EC_WORD_FAST,
    EC_WORD_FATHER,
    EC_WORD_FEAR,
    EC_POKEMON(FEAROW),
    EC_MOVE2(FEATHER_DANCE),
    EC_POKEMON2(FEEBAS),
    EC_WORD_FEELING,
    EC_POKEMON(FERALIGATR),
    EC_WORD_FESTIVAL,
    EC_WORD_FEVER,
    EC_WORD_FIERY,
    EC_WORD_FIGHT,
    EC_WORD_FIGHTING,
    EC_WORD_FIGHTS,
    EC_WORD_FINAL,
    EC_WORD_FINALLY,
    EC_WORD_FINISH,
    EC_WORD_FIRE,
    EC_MOVE2(FIRE_BLAST),
    EC_MOVE2(FIRE_PUNCH),
    EC_MOVE2(FIRE_SPIN),
    EC_WORD_FISHING,
    EC_MOVE(FISSURE),
    EC_POKEMON(FLAAFFY),
    EC_MOVE(FLAIL),
    EC_WORD_FLAME,
    EC_WORD_FLAME_BODY,
    EC_MOVE(FLAME_WHEEL),
    EC_MOVE(FLAMETHROWER),
    EC_POKEMON(FLAREON),
    EC_MOVE2(FLASH),
    EC_WORD_FLASH_FIRE,
    EC_WORD_FLATTEN,
    EC_MOVE(FLATTER),
    EC_WORD_FLOWERS,
    EC_MOVE(FLY),
    EC_POKEMON2(FLYGON),
    EC_WORD_FLYING,
    EC_MOVE(FOCUS_ENERGY),
    EC_MOVE(FOCUS_PUNCH),
    EC_WORD_FOE,
    EC_MOVE(FOLLOW_ME),
    EC_WORD_FOR,
    EC_WORD_FOR_NOW,
    EC_WORD_FORECAST,
    EC_MOVE2(FORESIGHT),
    EC_WORD_FOREVER,
    EC_WORD_FORGET,
    EC_WORD_FORGETS,
    EC_WORD_FORGIVE,
    EC_POKEMON(FORRETRESS),
    EC_MOVE2(FRENZY_PLANT),
    EC_WORD_FRIDAY,
    EC_WORD_FRIEND,
    EC_WORD_FROM,
    EC_WORD_FRONT,
    EC_MOVE2(FRUSTRATION),
    EC_WORD_FUFUFU,
    EC_WORD_FULL,
    EC_WORD_FUNNY,
    EC_POKEMON(FURRET),
    EC_MOVE2(FURY_ATTACK),
    EC_MOVE2(FURY_CUTTER),
    EC_MOVE2(FURY_SWIPES),
    EC_MOVE2(FUTURE_SIGHT),
};

static const u16 sEasyChatWordsByLetter_G[] = {
    EC_WORD_GAME,
    EC_POKEMON2(GARDEVOIR),
    EC_POKEMON(GASTLY),
    EC_POKEMON(GENGAR),
    EC_WORD_GENIUS,
    -1, 2, // Doubled pokemon species name
    EC_POKEMON2(GEODUDE),
    EC_POKEMON(GEODUDE),
    EC_WORD_GET,
    EC_WORD_GETS,
    EC_WORD_GHOST,
    EC_WORD_GIDDY,
    EC_MOVE(GIGA_DRAIN),
    EC_WORD_GIGGLE,
    EC_WORD_GIMME,
    -1, 2, // Doubled pokemon species name
    EC_POKEMON2(GIRAFARIG),
    EC_POKEMON(GIRAFARIG),
    EC_WORD_GIRL,
    EC_WORD_GIVE,
    EC_WORD_GIVE_ME,
    EC_WORD_GIVE_UP,
    EC_WORD_GIVES,
    EC_POKEMON2(GLALIE),
    EC_MOVE2(GLARE),
    EC_POKEMON(GLIGAR),
    -1, 2, // Doubled pokemon species name
    EC_POKEMON2(GLOOM),
    EC_POKEMON(GLOOM),
    EC_WORD_GO,
    EC_WORD_GO_AHEAD,
    EC_WORD_GO_EASY,
    EC_WORD_GO_HOME,
    EC_WORD_GOES,
    EC_WORD_GOING,
    -1, 2, // Doubled pokemon species name
    EC_POKEMON2(GOLBAT),
    EC_POKEMON(GOLBAT),
    EC_WORD_GOLD,
    -1, 2, // Doubled pokemon species name
    EC_POKEMON2(GOLDEEN),
    EC_POKEMON(GOLDEEN),
    -1, 2, // Doubled pokemon species name
    EC_POKEMON2(GOLDUCK),
    EC_POKEMON(GOLDUCK),
    -1, 2, // Doubled pokemon species name
    EC_POKEMON2(GOLEM),
    EC_POKEMON(GOLEM),
    EC_WORD_GOOD,
    EC_WORD_GOOD_BYE,
    EC_POKEMON2(GOREBYSS),
    EC_WORD_GOT,
    EC_WORD_GOTCHA,
    EC_WORD_GOURMET,
    EC_WORD_GRAAAH,
    EC_POKEMON(GRANBULL),
    EC_WORD_GRANDFATHER,
    EC_WORD_GRANDMOTHER,
    EC_WORD_GRASS,
    EC_MOVE(GRASS_WHISTLE),
    -1, 2, // Doubled pokemon species name
    EC_POKEMON2(GRAVELER),
    EC_POKEMON(GRAVELER),
    EC_WORD_GREAT,
    EC_WORD_GREEN,
    -1, 2, // Doubled pokemon species name
    EC_POKEMON2(GRIMER),
    EC_POKEMON(GRIMER),
    EC_POKEMON2(GROUDON),
    EC_WORD_GROUND,
    EC_WORD_GROUP,
    EC_POKEMON2(GROVYLE),
    EC_MOVE2(GROWL),
    EC_POKEMON(GROWLITHE),
    EC_MOVE(GROWTH),
    EC_MOVE(GRUDGE),
    EC_POKEMON2(GRUMPIG),
    EC_WORD_GUARD,
    EC_MOVE2(GUILLOTINE),
    EC_POKEMON2(GULPIN),
    EC_MOVE(GUST),
    EC_WORD_GUTS,
    EC_WORD_GUTSY,
    EC_WORD_GWAH,
    EC_WORD_GWAHAHAHA,
    -1, 2, // Doubled pokemon species name
    EC_POKEMON2(GYARADOS),
    EC_POKEMON(GYARADOS),
};

static const u16 sEasyChatWordsByLetter_H[] = {
    EC_WORD_HABIT,
    EC_WORD_HAH,
    EC_WORD_HAHAHA,
    EC_MOVE(HAIL),
    EC_WORD_HALL_OF_FAME,
    EC_WORD_HAPPENING,
    EC_WORD_HAPPILY,
    EC_WORD_HAPPINESS,
    EC_WORD_HAPPY,
    EC_WORD_HARD,
    EC_MOVE(HARDEN),
    EC_POKEMON2(HARIYAMA),
    EC_WORD_HAS,
    EC_WORD_HASSLE,
    EC_POKEMON(HAUNTER),
    EC_WORD_HAVE,
    EC_WORD_HAVEN_T,
    EC_MOVE(HAZE),
    EC_WORD_HE,
    EC_WORD_HE_S,
    EC_MOVE(HEADBUTT),
    EC_MOVE(HEAL_BELL),
    EC_WORD_HEALTHY,
    EC_WORD_HEAR,
    EC_WORD_HEARING,
    EC_WORD_HEARS,
    EC_WORD_HEART,
    EC_MOVE2(HEAT_WAVE),
    EC_WORD_HEH,
    EC_WORD_HEHE,
    EC_WORD_HEHEHE,
    EC_WORD_HELLO,
    EC_MOVE2(HELPING_HAND),
    EC_WORD_HER,
    -1, 2, // Doubled pokemon species name
    EC_POKEMON2(HERACROSS),
    EC_POKEMON(HERACROSS),
    EC_WORD_HERE,
    EC_WORD_HERE_GOES,
    EC_WORD_HERE_I_COME,
    EC_WORD_HERE_IT_IS,
    EC_WORD_HERO,
    EC_WORD_HEROINE,
    EC_WORD_HERS,
    EC_WORD_HEY,
    EC_WORD_HEY_THERE,
    EC_WORD_HEY_QUES,
    EC_WORD_HI,
    EC_MOVE2(HI_JUMP_KICK),
    EC_WORD_HIDDEN,
    EC_MOVE2(HIDDEN_POWER),
    EC_WORD_HIGH,
    EC_WORD_HIGHS,
    EC_WORD_HIM,
    EC_WORD_HIP_AND,
    EC_WORD_HIS,
    EC_WORD_HIT,
    EC_POKEMON(HITMONCHAN),
    EC_POKEMON(HITMONLEE),
    EC_POKEMON(HITMONTOP),
    EC_WORD_HIYAH,
    EC_WORD_HMM,
    EC_POKEMON(HO_OH),
    EC_WORD_HOBBY,
    EC_WORD_HOHOHO,
    EC_WORD_HOLIDAY,
    EC_WORD_HOME,
    EC_WORD_HOO_HAH,
    EC_POKEMON(HOOTHOOT),
    EC_WORD_HOPELESS,
    EC_POKEMON(HOPPIP),
    EC_MOVE2(HORN_ATTACK),
    EC_MOVE2(HORN_DRILL),
    -1, 2, // Doubled pokemon species name
    EC_POKEMON2(HORSEA),
    EC_POKEMON(HORSEA),
    EC_WORD_HOT,
    EC_POKEMON(HOUNDOOM),
    EC_POKEMON(HOUNDOUR),
    EC_WORD_HOW,
    EC_WORD_HOW_DO,
    EC_WORD_HOWEVER,
    EC_MOVE2(HOWL),
    EC_WORD_HUGE_POWER,
    EC_WORD_HUH_QUES,
    EC_WORD_HUMPH,
    EC_WORD_HUNGRY,
    EC_POKEMON2(HUNTAIL),
    EC_WORD_HURRIED,
    EC_WORD_HUSTLE,
    EC_MOVE2(HYDRO_CANNON),
    EC_MOVE2(HYDRO_PUMP),
    EC_WORD_HYPER,
    EC_MOVE2(HYPER_BEAM),
    EC_WORD_HYPER_CUTTER,
    EC_MOVE2(HYPER_FANG),
    EC_MOVE2(HYPER_VOICE),
    EC_POKEMON(HYPNO),
    EC_MOVE(HYPNOSIS),
};

static const u16 sEasyChatWordsByLetter_I[] = {
    EC_WORD_I,
    EC_WORD_I_AM,
    EC_WORD_I_CHOOSE_YOU,
    EC_WORD_I_WAS,
    EC_WORD_I_VE,
    EC_WORD_I_VE_ARRIVED,
    EC_WORD_ICE,
    EC_MOVE(ICE_BALL),
    EC_MOVE2(ICE_BEAM),
    EC_MOVE2(ICE_PUNCH),
    EC_MOVE2(ICICLE_SPEAR),
    EC_MOVE(ICY_WIND),
    EC_WORD_IDOL,
    EC_WORD_IF,
    EC_WORD_IF_I_LOSE,
    EC_WORD_IF_I_WIN,
    -1, 2, // Doubled pokemon species name
    EC_POKEMON2(IGGLYBUFF),
    EC_POKEMON(IGGLYBUFF),
    EC_WORD_IGNORANT,
    EC_WORD_ILLUMINATE,
    EC_POKEMON2(ILLUMISE),
    EC_WORD_IMMUNITY,
    EC_WORD_IMPORTANT,
    EC_WORD_IMPOSSIBLE,
    EC_MOVE2(IMPRISON),
    EC_WORD_IN,
    EC_WORD_INCREASING,
    EC_WORD_INCREDIBLE,
    EC_WORD_INFORMATION,
    EC_MOVE2(INGRAIN),
    EC_WORD_INNER_FOCUS,
    EC_WORD_INSIDE,
    EC_WORD_INSOMNIA,
    EC_WORD_INSTEAD,
    EC_WORD_INTIMIDATE,
    EC_WORD_INVINCIBLE,
    EC_MOVE2(IRON_DEFENSE),
    EC_MOVE(IRON_TAIL),
    EC_WORD_IS,
    EC_WORD_IS_IT_QUES,
    EC_WORD_ISN_T,
    EC_WORD_ISN_T_IT_QUES,
    EC_WORD_IT,
    EC_WORD_IT_S,
    EC_WORD_ITEM,
    EC_POKEMON(IVYSAUR),
};

static const u16 sEasyChatWordsByLetter_J[] = {
    -1, 2, // Doubled pokemon species name
    EC_POKEMON2(JIGGLYPUFF),
    EC_POKEMON(JIGGLYPUFF),
    EC_POKEMON2(JIRACHI),
    EC_WORD_JOKING,
    EC_POKEMON(JOLTEON),
    EC_WORD_JOY,
    EC_WORD_JUDGE,
    EC_MOVE2(JUMP_KICK),
    EC_POKEMON(JUMPLUFF),
    EC_WORD_JUST,
    EC_POKEMON(JYNX),
};

static const u16 sEasyChatWordsByLetter_K[] = {
    EC_POKEMON(KABUTO),
    EC_POKEMON(KABUTOPS),
    -1, 2, // Doubled pokemon species name
    EC_POKEMON2(KADABRA),
    EC_POKEMON(KADABRA),
    EC_POKEMON(KAKUNA),
    EC_POKEMON(KANGASKHAN),
    EC_MOVE(KARATE_CHOP),
    EC_POKEMON2(KECLEON),
    EC_WORD_KEEN_EYE,
    EC_WORD_KID,
    EC_WORD_KIDDING,
    EC_WORD_KIND,
    EC_WORD_KINDERGARTEN,
    EC_MOVE(KINESIS),
    -1, 2, // Doubled pokemon species name
    EC_POKEMON2(KINGDRA),
    EC_POKEMON(KINGDRA),
    EC_POKEMON(KINGLER),
    EC_POKEMON2(KIRLIA),
    EC_MOVE2(KNOCK_OFF),
    EC_WORD_KNOCKOUT,
    EC_WORD_KNOW,
    EC_WORD_KNOWS,
    -1, 2, // Doubled pokemon species name
    EC_POKEMON2(KOFFING),
    EC_POKEMON(KOFFING),
    EC_POKEMON(KRABBY),
    EC_WORD_KTHX_BYE,
    EC_POKEMON2(KYOGRE),
};

static const u16 sEasyChatWordsByLetter_L[] = {
    EC_WORD_LACKING,
    EC_WORD_LACKS,
    EC_WORD_LADY,
    EC_POKEMON2(LAIRON),
    EC_WORD_LALALA,
    -1, 2, // Doubled pokemon species name
    EC_POKEMON2(LANTURN),
    EC_POKEMON(LANTURN),
    EC_POKEMON(LAPRAS),
    EC_POKEMON(LARVITAR),
    EC_WORD_LAST,
    EC_WORD_LATE,
    EC_WORD_LATER,
    EC_POKEMON2(LATIAS),
    EC_POKEMON2(LATIOS),
    EC_WORD_LAVISH,
    EC_WORD_LAY,
    EC_WORD_LEADER,
    EC_WORD_LEADERS,
    EC_WORD_LEAF,
    EC_MOVE2(LEAF_BLADE),
    EC_WORD_LEARN,
    EC_POKEMON(LEDIAN),
    EC_POKEMON(LEDYBA),
    EC_MOVE(LEECH_LIFE),
    EC_MOVE2(LEECH_SEED),
    EC_MOVE2(LEER),
    EC_WORD_LEFT,
    EC_WORD_LEGEND,
    EC_WORD_LESS,
    EC_WORD_LESSONS,
    EC_WORD_LET_ME_WIN,
    EC_WORD_LET_S,
    EC_WORD_LETTER,
    EC_WORD_LEVEL,
    EC_WORD_LEVITATE,
    EC_MOVE(LICK),
    EC_POKEMON(LICKITUNG),
    EC_WORD_LIE,
    EC_WORD_LIFE,
    EC_MOVE2(LIGHT_SCREEN),
    EC_WORD_LIGHTNINGROD,
    EC_WORD_LIKE,
    EC_WORD_LIKELY_TO,
    EC_WORD_LIKES,
    EC_POKEMON2(LILEEP),
    EC_WORD_LIMBER,
    EC_WORD_LINK,
    EC_POKEMON2(LINOONE),
    EC_WORD_LIQUID_OOZE,
    EC_WORD_LISTEN,
    EC_WORD_LISTENING,
    EC_WORD_LISTENS,
    EC_WORD_LIVING,
    EC_MOVE2(LOCK_ON),
    EC_WORD_LOCOMOTIVE,
    EC_WORD_LOL,
    EC_WORD_LOLLING,
    EC_POKEMON2(LOMBRE),
    EC_WORD_LONESOME,
    EC_WORD_LOOK,
    EC_WORD_LOOKS,
    EC_WORD_LOSE,
    EC_WORD_LOSER,
    EC_WORD_LOSING,
    EC_WORD_LOSS,
    EC_WORD_LOST,
    EC_POKEMON2(LOTAD),
    EC_POKEMON2(LOUDRED),
    EC_WORD_LOUSY,
    EC_MOVE(LOVELY_KISS),
    EC_WORD_LOVEY_DOVEY,
    EC_WORD_LOW,
    EC_MOVE(LOW_KICK),
    EC_WORD_LOWS,
    EC_POKEMON2(LUDICOLO),
    EC_POKEMON(LUGIA),
    EC_WORD_LUKEWARM,
    EC_POKEMON2(LUNATONE),
    EC_MOVE2(LUSTER_PURGE),
    EC_POKEMON2(LUVDISC),
};

static const u16 sEasyChatWordsByLetter_M[] = {
    EC_MOVE2(MACH_PUNCH),
    -1, 2, // Doubled pokemon species name
    EC_POKEMON2(MACHAMP),
    EC_POKEMON(MACHAMP),
    EC_WORD_MACHINE,
    -1, 2, // Doubled pokemon species name
    EC_POKEMON2(MACHOKE),
    EC_POKEMON(MACHOKE),
    -1, 2, // Doubled pokemon species name
    EC_POKEMON2(MACHOP),
    EC_POKEMON(MACHOP),
    EC_WORD_MAGAZINE,
    EC_POKEMON(MAGBY),
    -1, 2, // Doubled pokemon species name
    EC_POKEMON2(MAGCARGO),
    EC_POKEMON(MAGCARGO),
    EC_MOVE2(MAGIC_COAT),
    EC_MOVE2(MAGICAL_LEAF),
    -1, 2, // Doubled pokemon species name
    EC_POKEMON2(MAGIKARP),
    EC_POKEMON(MAGIKARP),
    EC_WORD_MAGMA_ARMOR,
    EC_POKEMON(MAGMAR),
    -1, 2, // Doubled pokemon species name
    EC_POKEMON2(MAGNEMITE),
    EC_POKEMON(MAGNEMITE),
    EC_WORD_MAGNET_PULL,
    -1, 2, // Doubled pokemon species name
    EC_POKEMON2(MAGNETON),
    EC_POKEMON(MAGNETON),
    EC_MOVE2(MAGNITUDE),
    EC_WORD_MAIL,
    EC_WORD_MAKE,
    EC_WORD_MAKING,
    EC_POKEMON2(MAKUHITA),
    EC_WORD_MAN,
    EC_POKEMON2(MANECTRIC),
    EC_POKEMON(MANKEY),
    EC_POKEMON(MANTINE),
    EC_POKEMON(MAREEP),
    -1, 2, // Doubled pokemon species name
    EC_POKEMON2(MARILL),
    EC_POKEMON(MARILL),
    EC_POKEMON(MAROWAK),
    EC_POKEMON2(MARSHTOMP),
    EC_WORD_MARVEL_SCALE,
    EC_POKEMON2(MASQUERAIN),
    EC_WORD_MASTER,
    EC_WORD_MATCH,
    EC_WORD_MATCH_UP,
    EC_POKEMON2(MAWILE),
    EC_WORD_MAYBE,
    EC_WORD_MC,
    EC_WORD_ME,
    EC_WORD_MEAN,
    EC_MOVE(MEAN_LOOK),
    EC_POKEMON2(MEDICHAM),
    EC_MOVE2(MEDITATE),
    EC_POKEMON2(MEDITITE),
    EC_WORD_MEET,
    EC_WORD_MEET_YOU,
    EC_WORD_MEETS,
    EC_WORD_MEGA,
    EC_MOVE2(MEGA_DRAIN),
    EC_MOVE2(MEGA_KICK),
    EC_MOVE2(MEGA_PUNCH),
    EC_MOVE2(MEGAHORN),
    EC_POKEMON(MEGANIUM),
    EC_MOVE(MEMENTO),
    EC_POKEMON(MEOWTH),
    EC_WORD_MESSAGE,
    EC_POKEMON2(METAGROSS),
    EC_MOVE2(METAL_CLAW),
    EC_MOVE(METAL_SOUND),
    EC_POKEMON2(METANG),
    EC_POKEMON(METAPOD),
    EC_MOVE(METEOR_MASH),
    EC_MOVE2(METRONOME),
    EC_POKEMON(MEW),
    EC_POKEMON(MEWTWO),
    EC_POKEMON2(MIGHTYENA),
    EC_MOVE2(MILK_DRINK),
    EC_POKEMON2(MILOTIC),
    EC_POKEMON(MILTANK),
    EC_MOVE2(MIMIC),
    EC_MOVE(MIND_READER),
    EC_MOVE2(MINIMIZE),
    EC_POKEMON2(MINUN),
    EC_WORD_MINUS,
    EC_MOVE2(MIRROR_COAT),
    EC_MOVE(MIRROR_MOVE),
    EC_POKEMON(MISDREAVUS),
    EC_WORD_MISHEARD,
    EC_WORD_MISS,
    EC_MOVE(MIST),
    EC_MOVE2(MIST_BALL),
    EC_WORD_MISTAKE,
    EC_WORD_MMM,
    EC_WORD_MODE,
    EC_WORD_MODERN,
    EC_POKEMON(MOLTRES),
    EC_WORD_MOMENTUM,
    EC_WORD_MONDAY,
    EC_WORD_MONEY,
    EC_WORD_MONTH,
    EC_WORD_MOOD,
    EC_MOVE2(MOONLIGHT),
    EC_WORD_MORE,
    EC_WORD_MORNING,
    EC_MOVE(MORNING_SUN),
    EC_WORD_MOTHER,
    EC_WORD_MOVE,
    EC_WORD_MOVIE,
    EC_WORD_MR,
    EC_POKEMON(MR_MIME),
    EC_WORD_MRS,
    EC_WORD_MUCH,
    EC_WORD_MUCH_OBLIGED,
    EC_MOVE2(MUD_SHOT),
    EC_MOVE2(MUD_SPORT),
    EC_MOVE2(MUD_SLAP),
    EC_MOVE2(MUDDY_WATER),
    EC_POKEMON2(MUDKIP),
    EC_WORD_MUFUFU,
    -1, 2, // Doubled pokemon species name
    EC_POKEMON2(MUK),
    EC_POKEMON(MUK),
    EC_POKEMON(MURKROW),
    EC_WORD_MUSIC,
    EC_WORD_MUST_BE,
    EC_WORD_MY,
    EC_WORD_MYSELF,
    EC_WORD_MYSTERY,
};

static const u16 sEasyChatWordsByLetter_N[] = {
    EC_WORD_NAME,
    EC_WORD_NAP,
    -1, 2, // Doubled pokemon species name
    EC_POKEMON2(NATU),
    EC_POKEMON(NATU),
    EC_WORD_NATURAL,
    EC_WORD_NATURAL_CURE,
    EC_WORD_NATURALLY,
    EC_WORD_NATURE,
    EC_MOVE(NATURE_POWER),
    EC_WORD_NEAR,
    EC_WORD_NEARLY,
    EC_WORD_NEED,
    EC_MOVE2(NEEDLE_ARM),
    EC_WORD_NEGATIVE,
    EC_WORD_NEVER,
    EC_WORD_NEW,
    EC_WORD_NEWS,
    EC_WORD_NEXT,
    EC_WORD_NICE,
    EC_POKEMON(NIDOKING),
    EC_POKEMON(NIDOQUEEN),
    EC_POKEMON(NIDORAN_F),
    EC_POKEMON(NIDORAN_M),
    EC_POKEMON(NIDORINA),
    EC_POKEMON(NIDORINO),
    EC_WORD_NIGHT,
    EC_MOVE2(NIGHT_SHADE),
    EC_MOVE(NIGHTMARE),
    EC_WORD_NIGHTTIME,
    EC_POKEMON2(NINCADA),
    -1, 2, // Doubled pokemon species name
    EC_POKEMON2(NINETALES),
    EC_POKEMON(NINETALES),
    EC_POKEMON2(NINJASK),
    EC_WORD_NITWIT,
    EC_WORD_NO,
    EC_WORD_NO_MATCH,
    EC_WORD_NO_1,
    EC_POKEMON(NOCTOWL),
    EC_WORD_NOISY,
    EC_WORD_NON_STOP,
    EC_WORD_NONE,
    EC_WORD_NOPE,
    EC_WORD_NORMAL,
    EC_POKEMON2(NOSEPASS),
    EC_WORD_NOT,
    EC_WORD_NOT_VERY,
    EC_WORD_NOTHING,
    EC_WORD_NOW,
    EC_POKEMON2(NUMEL),
    EC_POKEMON2(NUZLEAF),
};

static const u16 sEasyChatWordsByLetter_O[] = {
    EC_WORD_OBLIVIOUS,
    EC_MOVE(OCTAZOOKA),
    EC_POKEMON(OCTILLERY),
    -1, 2, // Doubled pokemon species name
    EC_POKEMON2(ODDISH),
    EC_POKEMON(ODDISH),
    EC_MOVE(ODOR_SLEUTH),
    EC_WORD_OF,
    EC_WORD_OFF,
    EC_WORD_OFFENSIVE,
    EC_WORD_OH,
    EC_WORD_OH_DEAR,
    EC_WORD_OH_YEAH,
    EC_WORD_OH_KAY,
    EC_WORD_OH_QUES,
    EC_WORD_OI,
    EC_WORD_OI_OI_OI,
    EC_WORD_OK_QUES,
    EC_WORD_OKAY,
    EC_WORD_OLD,
    EC_WORD_OLDEN,
    EC_POKEMON(OMANYTE),
    EC_POKEMON(OMASTAR),
    EC_WORD_ON,
    EC_WORD_ONCE,
    EC_POKEMON(ONIX),
    EC_WORD_ONLY,
    EC_WORD_OOPS,
    EC_WORD_OPPONENT,
    EC_WORD_OPPOSITE,
    EC_WORD_OR,
    EC_WORD_OTHER,
    EC_WORD_OUR,
    EC_WORD_OUT,
    EC_MOVE(OUTRAGE),
    EC_WORD_OUTSIDE,
    EC_WORD_OVER,
    EC_WORD_OVERDO,
    EC_WORD_OVERGROW,
    EC_MOVE(OVERHEAT),
    EC_WORD_OVERWHELMING,
    EC_WORD_OWN,
    EC_WORD_OWN_TEMPO,
};

static const u16 sEasyChatWordsByLetter_P[] = {
    EC_MOVE(PAIN_SPLIT),
    EC_POKEMON(PARAS),
    EC_POKEMON(PARASECT),
    EC_WORD_PARDON,
    EC_WORD_PARENT,
    EC_WORD_PARTNER,
    EC_WORD_PARTY,
    EC_WORD_PATTERN,
    EC_MOVE2(PAY_DAY),
    EC_WORD_PC,
    EC_MOVE2(PECK),
    EC_POKEMON2(PELIPPER),
    EC_WORD_PERFECT,
    EC_WORD_PERFECTION,
    EC_MOVE2(PERISH_SONG),
    EC_POKEMON(PERSIAN),
    EC_WORD_PERSON,
    EC_MOVE2(PETAL_DANCE),
    -1, 2, // Doubled pokemon species name
    EC_POKEMON2(PHANPY),
    EC_POKEMON(PHANPY),
    EC_WORD_PHONE,
    -1, 2, // Doubled pokemon species name
    EC_POKEMON2(PICHU),
    EC_POKEMON(PICHU),
    EC_WORD_PICKUP,
    EC_POKEMON(PIDGEOT),
    EC_POKEMON(PIDGEOTTO),
    EC_POKEMON(PIDGEY),
    -1, 2, // Doubled pokemon species name
    EC_POKEMON2(PIKACHU),
    EC_POKEMON(PIKACHU),
    EC_POKEMON(PILOSWINE),
    EC_MOVE2(PIN_MISSILE),
    EC_POKEMON(PINECO),
    -1, 2, // Doubled pokemon species name
    EC_POKEMON2(PINSIR),
    EC_POKEMON(PINSIR),
    EC_WORD_PKRS,
    EC_WORD_PLACE,
    EC_WORD_PLANS,
    EC_WORD_PLAY,
    EC_WORD_PLAYED,
    EC_WORD_PLAYS,
    EC_WORD_PLEASE,
    EC_WORD_PLUS,
    EC_WORD_PLUSH_DOLL,
    EC_POKEMON2(PLUSLE),
    EC_WORD_POINTS,
    EC_WORD_POISON,
    EC_MOVE2(POISON_FANG),
    EC_MOVE2(POISON_GAS),
    EC_WORD_POISON_POINT,
    EC_MOVE2(POISON_STING),
    EC_MOVE2(POISON_TAIL),
    EC_MOVE2(POISON_POWDER),
    EC_WORD_POKEBLOCK,
    EC_WORD_POKEDEX,
    EC_WORD_POKEMON,
    EC_WORD_POKENAV,
    EC_POKEMON(POLITOED),
    EC_POKEMON(POLIWAG),
    EC_POKEMON(POLIWHIRL),
    EC_POKEMON(POLIWRATH),
    EC_POKEMON(PONYTA),
    EC_POKEMON2(POOCHYENA),
    EC_WORD_POPULAR,
    EC_POKEMON(PORYGON),
    EC_POKEMON(PORYGON2),
    EC_MOVE2(POUND),
    EC_MOVE(POWDER_SNOW),
    EC_WORD_POWER,
    EC_WORD_PRAISE,
    EC_WORD_PREPOSTEROUS,
    EC_MOVE2(PRESENT),
    EC_WORD_PRESSURE,
    EC_WORD_PRETEND,
    EC_WORD_PRETTY,
    EC_POKEMON(PRIMEAPE),
    EC_WORD_PROBABLY,
    EC_WORD_PROMISE,
    EC_MOVE2(PROTECT),
    EC_MOVE(PSYBEAM),
    EC_MOVE(PSYCH_UP),
    -1, 2, // Doubled pokemon species name
    EC_WORD_PSYCHIC,
    EC_MOVE(PSYCHIC),
    EC_MOVE(PSYCHO_BOOST),
    -1, 2, // Doubled pokemon species name
    EC_POKEMON2(PSYDUCK),
    EC_POKEMON(PSYDUCK),
    EC_MOVE(PSYWAVE),
    EC_POKEMON(PUPITAR),
    EC_WORD_PURE_POWER,
    EC_MOVE(PURSUIT),
    EC_WORD_PUSHOVER,
};

static const u16 sEasyChatWordsByLetter_Q[] = {
    EC_POKEMON(QUAGSIRE),
    EC_WORD_QUESTION,
    EC_MOVE2(QUICK_ATTACK),
    EC_POKEMON(QUILAVA),
    EC_WORD_QUITE,
    EC_POKEMON(QWILFISH),
};

static const u16 sEasyChatWordsByLetter_R[] = {
    EC_WORD_RADIO,
    EC_MOVE(RAGE),
    -1, 2, // Doubled pokemon species name
    EC_POKEMON2(RAICHU),
    EC_POKEMON(RAICHU),
    EC_POKEMON(RAIKOU),
    EC_MOVE(RAIN_DANCE),
    EC_WORD_RAIN_DISH,
    EC_POKEMON2(RALTS),
    EC_WORD_RANK,
    EC_MOVE(RAPID_SPIN),
    EC_POKEMON(RAPIDASH),
    EC_WORD_RARE,
    EC_WORD_RATHER,
    EC_POKEMON(RATICATE),
    EC_POKEMON(RATTATA),
    EC_POKEMON2(RAYQUAZA),
    EC_MOVE2(RAZOR_LEAF),
    EC_MOVE(RAZOR_WIND),
    EC_WORD_READY,
    EC_WORD_REALLY,
    EC_WORD_REAR,
    EC_WORD_RECEIVED,
    EC_WORD_RECOMMEND,
    EC_MOVE(RECOVER),
    EC_MOVE2(RECYCLE),
    EC_WORD_RED,
    EC_MOVE2(REFLECT),
    EC_MOVE2(REFRESH),
    EC_WORD_REFRESHING,
    EC_WORD_REFUSE,
    EC_POKEMON2(REGICE),
    EC_POKEMON2(REGIROCK),
    EC_POKEMON2(REGISTEEL),
    EC_WORD_REJECT,
    EC_WORD_RELEASE,
    EC_POKEMON2(RELICANTH),
    EC_POKEMON(REMORAID),
    EC_WORD_RENTAL,
    EC_MOVE2(REST),
    EC_WORD_RESUSCITATE,
    EC_MOVE(RETURN),
    EC_MOVE2(REVENGE),
    EC_MOVE(REVERSAL),
    -1, 2, // Doubled pokemon species name
    EC_POKEMON2(RHYDON),
    EC_POKEMON(RHYDON),
    -1, 2, // Doubled pokemon species name
    EC_POKEMON2(RHYHORN),
    EC_POKEMON(RHYHORN),
    EC_WORD_RIBBON,
    EC_WORD_RICKETY,
    EC_WORD_RIGHT,
    EC_WORD_RIPPED,
    EC_WORD_RIVAL,
    EC_MOVE2(ROAR),
    EC_WORD_ROCK,
    EC_MOVE2(ROCK_BLAST),
    EC_WORD_ROCK_HEAD,
    EC_MOVE(ROCK_SLIDE),
    EC_MOVE(ROCK_SMASH),
    EC_MOVE(ROCK_THROW),
    EC_MOVE(ROCK_TOMB),
    EC_WORD_ROCK_SOLID,
    EC_MOVE2(ROLE_PLAY),
    EC_MOVE2(ROLLING_KICK),
    EC_MOVE(ROLLOUT),
    EC_WORD_ROMANTIC,
    EC_WORD_ROOM,
    EC_POKEMON2(ROSELIA),
    EC_WORD_ROUGH_SKIN,
    EC_WORD_RPG,
    EC_WORD_RUBY,
    EC_WORD_RULE,
    EC_WORD_RUN,
    EC_WORD_RUN_AWAY,
    EC_WORD_RUNS,
};

static const u16 sEasyChatWordsByLetter_S[] = {
    EC_POKEMON2(SABLEYE),
    EC_MOVE(SACRED_FIRE),
    EC_WORD_SAD,
    EC_WORD_SADLY,
    EC_MOVE(SAFEGUARD),
    EC_WORD_SAID,
    EC_POKEMON2(SALAMENCE),
    EC_WORD_SAND_STREAM,
    EC_MOVE(SAND_TOMB),
    EC_WORD_SAND_VEIL,
    EC_MOVE(SAND_ATTACK),
    -1, 2, // Doubled pokemon species name
    EC_POKEMON2(SANDSHREW),
    EC_POKEMON(SANDSHREW),
    -1, 2, // Doubled pokemon species name
    EC_POKEMON2(SANDSLASH),
    EC_POKEMON(SANDSLASH),
    EC_MOVE(SANDSTORM),
    EC_WORD_SAPPHIRE,
    EC_WORD_SATISFIED,
    EC_WORD_SATURDAY,
    EC_WORD_SAYS,
    EC_WORD_SCARY,
    EC_MOVE(SCARY_FACE),
    EC_WORD_SCATTER,
    EC_POKEMON2(SCEPTILE),
    EC_WORD_SCHOOL,
    EC_POKEMON(SCIZOR),
    EC_MOVE2(SCRATCH),
    EC_MOVE(SCREECH),
    EC_POKEMON(SCYTHER),
    -1, 2, // Doubled pokemon species name
    EC_POKEMON2(SEADRA),
    EC_POKEMON(SEADRA),
    -1, 2, // Doubled pokemon species name
    EC_POKEMON2(SEAKING),
    EC_POKEMON(SEAKING),
    EC_POKEMON2(SEALEO),
    EC_WORD_SEARCH,
    EC_WORD_SECRET,
    EC_WORD_SECRET_BASE,
    EC_MOVE2(SECRET_POWER),
    EC_WORD_SEE,
    EC_WORD_SEE_YA,
    EC_POKEMON2(SEEDOT),
    EC_WORD_SEEK,
    EC_POKEMON(SEEL),
    EC_WORD_SEEMS,
    EC_WORD_SEES,
    EC_MOVE2(SEISMIC_TOSS),
    EC_MOVE(SELF_DESTRUCT),
    EC_WORD_SENSE,
    EC_POKEMON(SENTRET),
    EC_WORD_SERENE_GRACE,
    EC_WORD_SERIOUS,
    EC_WORD_SERIOUSLY,
    EC_WORD_SERVICE,
    EC_POKEMON2(SEVIPER),
    EC_MOVE(SHADOW_BALL),
    EC_MOVE(SHADOW_PUNCH),
    EC_WORD_SHADOW_TAG,
    EC_WORD_SHADY,
    EC_WORD_SHAKE,
    EC_WORD_SHAKY,
    EC_WORD_SHALLOW,
    EC_POKEMON2(SHARPEDO),
    EC_MOVE(SHARPEN),
    EC_WORD_SHE,
    EC_WORD_SHE_IS,
    EC_WORD_SHE_WAS,
    EC_WORD_SHED_SKIN,
    EC_POKEMON2(SHEDINJA),
    EC_MOVE(SHEER_COLD),
    EC_POKEMON2(SHELGON),
    EC_WORD_SHELL_ARMOR,
    EC_POKEMON(SHELLDER),
    EC_WORD_SHIELD_DUST,
    EC_POKEMON2(SHIFTRY),
    EC_WORD_SHINE,
    EC_MOVE2(SHOCK_WAVE),
    EC_WORD_SHOCKED,
    EC_WORD_SHOPPING,
    EC_WORD_SHOULD,
    EC_WORD_SHOW,
    EC_WORD_SHREDDED,
    EC_POKEMON2(SHROOMISH),
    EC_POKEMON(SHUCKLE),
    EC_POKEMON2(SHUPPET),
    EC_WORD_SIBLINGS,
    EC_WORD_SIGH,
    EC_MOVE(SIGNAL_BEAM),
    EC_POKEMON2(SILCOON),
    EC_WORD_SILKY,
    EC_WORD_SILVER,
    EC_MOVE(SILVER_WIND),
    EC_WORD_SIMPLE,
    EC_WORD_SINCE,
    EC_MOVE(SING),
    EC_WORD_SINK,
    EC_WORD_SISTER,
    -1, 2, // Doubled pokemon species name
    EC_POKEMON2(SKARMORY),
    EC_POKEMON(SKARMORY),
    EC_MOVE(SKETCH),
    EC_WORD_SKILL,
    EC_MOVE(SKILL_SWAP),
    EC_WORD_SKILLED,
    EC_POKEMON(SKIPLOOM),
    EC_POKEMON2(SKITTY),
    EC_MOVE2(SKULL_BASH),
    EC_MOVE(SKY_ATTACK),
    EC_MOVE(SKY_UPPERCUT),
    EC_MOVE2(SLACK_OFF),
    EC_POKEMON2(SLAKING),
    EC_POKEMON2(SLAKOTH),
    EC_MOVE2(SLAM),
    EC_MOVE(SLASH),
    EC_WORD_SLEEP,
    EC_MOVE2(SLEEP_POWDER),
    EC_MOVE2(SLEEP_TALK),
    EC_WORD_SLEPT,
    EC_WORD_SLIDE,
    EC_WORD_SLIMY,
    EC_POKEMON(SLOWBRO),
    EC_POKEMON(SLOWKING),
    EC_POKEMON(SLOWPOKE),
    EC_MOVE2(SLUDGE),
    EC_MOVE2(SLUDGE_BOMB),
    -1, 2, // Doubled pokemon species name
    EC_POKEMON2(SLUGMA),
    EC_POKEMON(SLUGMA),
    EC_WORD_SMACK,
    EC_WORD_SMALL,
    EC_WORD_SMART,
    EC_WORD_SMARTNESS,
    EC_POKEMON(SMEARGLE),
    EC_WORD_SMELL,
    EC_WORD_SMELL_YA,
    EC_MOVE(SMELLING_SALT),
    EC_WORD_SMITE,
    EC_MOVE(SMOG),
    EC_MOVE(SMOKESCREEN),
    EC_POKEMON(SMOOCHUM),
    EC_WORD_SMOOTH,
    EC_MOVE2(SNATCH),
    EC_POKEMON(SNEASEL),
    EC_MOVE(SNORE),
    EC_POKEMON(SNORLAX),
    EC_WORD_SNORT,
    EC_POKEMON2(SNORUNT),
    EC_POKEMON(SNUBBULL),
    EC_WORD_SO,
    EC_MOVE2(SOFT_BOILED),
    EC_WORD_SOFTWARE,
    EC_MOVE(SOLAR_BEAM),
    EC_POKEMON2(SOLROCK),
    EC_WORD_SOME,
    EC_WORD_SOMEHOW,
    EC_WORD_SOMEONE,
    EC_WORD_SOMETHING,
    EC_WORD_SOMETIME,
    EC_WORD_SON,
    EC_WORD_SONG,
    EC_WORD_SONGS,
    EC_MOVE(SONIC_BOOM),
    EC_WORD_SOON,
    EC_WORD_SORRY,
    EC_WORD_SOUNDPROOF,
    EC_WORD_SP_ABILITY,
    EC_MOVE(SPARK),
    EC_POKEMON(SPEAROW),
    EC_WORD_SPECTATOR,
    EC_WORD_SPEED_BOOST,
    EC_POKEMON2(SPHEAL),
    EC_MOVE(SPIDER_WEB),
    EC_MOVE2(SPIKE_CANNON),
    EC_MOVE2(SPIKES),
    EC_POKEMON(SPINARAK),
    EC_POKEMON2(SPINDA),
    EC_WORD_SPIRALING,
    EC_WORD_SPIRIT,
    EC_MOVE2(SPIT_UP),
    EC_MOVE(SPITE),
    EC_MOVE2(SPLASH),
    EC_POKEMON2(SPOINK),
    EC_MOVE(SPORE),
    EC_WORD_SPORTS,
    EC_WORD_SPRING,
    EC_POKEMON(SQUIRTLE),
    EC_WORD_STAGE,
    EC_POKEMON(STANTLER),
    -1, 2, // Doubled pokemon species name
    EC_POKEMON2(STARMIE),
    EC_POKEMON(STARMIE),
    EC_WORD_START,
    -1, 2, // Doubled pokemon species name
    EC_POKEMON2(STARYU),
    EC_POKEMON(STARYU),
    EC_WORD_STATIC,
    EC_WORD_STAY_AT_HOME,
    EC_WORD_STEEL,
    EC_MOVE2(STEEL_WING),
    EC_POKEMON(STEELIX),
    EC_WORD_STENCH,
    EC_WORD_STICKY_HOLD,
    EC_MOVE2(STOCKPILE),
    EC_MOVE2(STOMP),
    EC_WORD_STOP,
    EC_WORD_STORE,
    EC_WORD_STORES,
    EC_WORD_STORY,
    EC_WORD_STRATEGY,
    EC_MOVE(STRENGTH),
    EC_MOVE(STRING_SHOT),
    EC_WORD_STRONG,
    EC_MOVE2(STRUGGLE),
    EC_WORD_STUDY,
    EC_MOVE(STUN_SPORE),
    EC_WORD_STURDY,
    EC_MOVE(SUBMISSION),
    EC_MOVE2(SUBSTITUTE),
    EC_WORD_SUCTION_CUPS,
    EC_POKEMON(SUDOWOODO),
    EC_POKEMON(SUICUNE),
    EC_WORD_SUMMER,
    EC_WORD_SUNDAY,
    EC_POKEMON(SUNFLORA),
    EC_POKEMON(SUNKERN),
    EC_MOVE2(SUNNY_DAY),
    EC_WORD_SUPER,
    EC_MOVE(SUPER_FANG),
    EC_MOVE2(SUPERPOWER),
    EC_MOVE2(SUPERSONIC),
    EC_MOVE2(SURF),
    EC_WORD_SURPRISE,
    EC_WORD_SURRENDER,
    EC_POKEMON2(SURSKIT),
    EC_POKEMON2(SWABLU),
    EC_MOVE(SWAGGER),
    EC_MOVE2(SWALLOW),
    EC_POKEMON2(SWALOT),
    EC_POKEMON2(SWAMPERT),
    EC_WORD_SWARM,
    EC_MOVE2(SWEET_KISS),
    EC_MOVE(SWEET_SCENT),
    EC_WORD_SWEETS,
    EC_POKEMON2(SWELLOW),
    EC_MOVE(SWIFT),
    EC_WORD_SWIFT_SWIM,
    EC_POKEMON(SWINUB),
    EC_MOVE2(SWORDS_DANCE),
    EC_WORD_SYNCHRONIZE,
    EC_MOVE(SYNTHESIS),
    EC_WORD_SYSTEM,
};

static const u16 sEasyChatWordsByLetter_T[] = {
    EC_MOVE2(TACKLE),
    EC_MOVE2(TAIL_GLOW),
    EC_MOVE(TAIL_WHIP),
    EC_POKEMON2(TAILLOW),
    EC_WORD_TAKE,
    EC_MOVE2(TAKE_DOWN),
    EC_WORD_TAKE_THAT,
    EC_WORD_TALENT,
    EC_WORD_TALK,
    EC_WORD_TALKING,
    EC_POKEMON(TANGELA),
    EC_WORD_TASTY,
    EC_MOVE2(TAUNT),
    EC_POKEMON(TAUROS),
    EC_WORD_TCH,
    EC_WORD_TEACH,
    EC_WORD_TEACHER,
    EC_WORD_TEACHES,
    EC_POKEMON(TEDDIURSA),
    EC_MOVE2(TEETER_DANCE),
    EC_MOVE2(TELEPORT),
    EC_WORD_TELEVISION,
    -1, 2, // Doubled pokemon species name
    EC_POKEMON2(TENTACOOL),
    EC_POKEMON(TENTACOOL),
    -1, 2, // Doubled pokemon species name
    EC_POKEMON2(TENTACRUEL),
    EC_POKEMON(TENTACRUEL),
    EC_WORD_TERRIBLE,
    EC_WORD_TEST,
    EC_WORD_THAN,
    EC_WORD_THANK_YOU,
    EC_WORD_THANKS,
    EC_WORD_THAT,
    EC_WORD_THAT_WAS,
    EC_WORD_THAT_S,
    EC_WORD_THAT_S_IT_EXCL,
    EC_WORD_THE,
    EC_WORD_THEIR,
    EC_WORD_THERE,
    EC_WORD_THESE,
    EC_WORD_THESE_WERE,
    EC_WORD_THEY,
    EC_WORD_THEY_WERE,
    EC_WORD_THEY_RE,
    EC_WORD_THEY_VE,
    EC_WORD_THICK,
    EC_WORD_THICK_FAT,
    EC_MOVE2(THIEF),
    EC_WORD_THIN,
    EC_WORD_THING,
    EC_WORD_THINGS,
    EC_WORD_THINK,
    EC_WORD_THINKS,
    EC_WORD_THIRSTY,
    EC_WORD_THIS,
    EC_WORD_THIS_IS_IT_EXCL,
    EC_WORD_THOSE,
    EC_WORD_THOSE_ARE,
    EC_WORD_THOSE_WERE,
    EC_MOVE(THRASH),
    EC_WORD_THROW,
    EC_MOVE(THUNDER),
    EC_MOVE2(THUNDER_WAVE),
    EC_MOVE(THUNDERBOLT),
    EC_MOVE(THUNDER_PUNCH),
    EC_MOVE2(THUNDER_SHOCK),
    EC_WORD_THURSDAY,
    EC_MOVE(TICKLE),
    EC_WORD_TICKLISH,
    EC_WORD_TIGHT,
    EC_WORD_TIME,
    EC_WORD_TIMES,
    EC_WORD_TIRED,
    EC_WORD_TO,
    EC_WORD_TO_HER,
    EC_WORD_TO_ME,
    EC_WORD_TO_THEM,
    EC_WORD_TO_US,
    EC_WORD_TO_WHOM,
    EC_WORD_TODAY,
    EC_POKEMON(TOGEPI),
    EC_WORD_TOGETHER,
    EC_POKEMON(TOGETIC),
    EC_WORD_TOMORROW,
    EC_WORD_TOO,
    EC_WORD_TOO_LATE,
    EC_WORD_TOO_STRONG,
    EC_WORD_TOO_WEAK,
    EC_WORD_TOP,
    EC_POKEMON2(TORCHIC),
    EC_POKEMON2(TORKOAL),
    EC_MOVE(TORMENT),
    EC_WORD_TORRENT,
    EC_WORD_TOTALLY,
    EC_POKEMON(TOTODILE),
    EC_WORD_TOUGH,
    EC_WORD_TOUGHNESS,
    EC_WORD_TOURNAMENT,
    EC_WORD_TOWER,
    EC_MOVE2(TOXIC),
    EC_WORD_TOYS,
    EC_WORD_TRACE,
    EC_WORD_TRADE,
    EC_WORD_TRAIN,
    EC_WORD_TRAINER,
    EC_WORD_TRAINS,
    EC_MOVE2(TRANSFORM),
    EC_POKEMON2(TRAPINCH),
    EC_WORD_TRAVEL,
    EC_WORD_TREASURE,
    EC_POKEMON2(TREECKO),
    EC_WORD_TRENDY,
    EC_MOVE2(TRI_ATTACK),
    EC_MOVE2(TRICK),
    EC_WORD_TRIES,
    EC_MOVE2(TRIPLE_KICK),
    EC_POKEMON2(TROPIUS),
    EC_WORD_TRUANT,
    EC_WORD_TRULY,
    EC_WORD_TRUMP_CARD,
    EC_WORD_TRUST,
    EC_WORD_TRY,
    EC_WORD_TUESDAY,
    EC_MOVE2(TWINEEDLE),
    EC_WORD_TWIRLING,
    EC_MOVE2(TWISTER),
    EC_WORD_TYPE,
    EC_POKEMON(TYPHLOSION),
    EC_POKEMON(TYRANITAR),
    EC_POKEMON(TYROGUE),
};

static const u16 sEasyChatWordsByLetter_U[] = {
    EC_WORD_UGLY,
    EC_WORD_UH_HUH,
    EC_WORD_UH_OH,
    EC_WORD_UM,
    EC_POKEMON(UMBREON),
    EC_WORD_UNAVOIDABLE,
    EC_WORD_UNBELIEVABLE,
    EC_WORD_UNCLE,
    EC_WORD_UNDERSTAND,
    EC_WORD_UNDERSTANDS,
    EC_WORD_UNDERSTOOD,
    EC_WORD_UNION,
    EC_POKEMON(UNOWN),
    EC_WORD_UNTIL,
    EC_WORD_UP,
    EC_WORD_UPBEAT,
    EC_MOVE(UPROAR),
    EC_WORD_UPSIDE_DOWN,
    EC_WORD_URGH,
    EC_POKEMON(URSARING),
    EC_WORD_USE,
    EC_WORD_USELESS,
    EC_WORD_USES,
    EC_WORD_USING,
};

static const u16 sEasyChatWordsByLetter_V[] = {
    EC_WORD_VACATION,
    EC_POKEMON(VAPOREON),
    EC_POKEMON(VENOMOTH),
    EC_POKEMON(VENONAT),
    EC_POKEMON(VENUSAUR),
    EC_WORD_VERSION,
    EC_WORD_VERSUS,
    EC_WORD_VERY,
    EC_POKEMON2(VIBRAVA),
    EC_MOVE2(VICE_GRIP),
    EC_WORD_VICTORY,
    EC_POKEMON(VICTREEBEL),
    EC_WORD_VIEWING,
    EC_POKEMON2(VIGOROTH),
    -1, 2, // Doubled pokemon species name
    EC_POKEMON2(VILEPLUME),
    EC_POKEMON(VILEPLUME),
    EC_MOVE2(VINE_WHIP),
    EC_WORD_VITAL_SPIRIT,
    EC_MOVE(VITAL_THROW),
    EC_POKEMON2(VOLBEAT),
    EC_WORD_VOLT_ABSORB,
    EC_MOVE2(VOLT_TACKLE),
    -1, 2, // Doubled pokemon species name
    EC_POKEMON2(VOLTORB),
    EC_POKEMON(VOLTORB),
    EC_WORD_VORACIOUS,
    -1, 2, // Doubled pokemon species name
    EC_POKEMON2(VULPIX),
    EC_POKEMON(VULPIX),
};

static const u16 sEasyChatWordsByLetter_W[] = {
    EC_WORD_WAAAH,
    EC_WORD_WAHAHAHA,
    EC_POKEMON2(WAILMER),
    EC_POKEMON2(WAILORD),
    EC_WORD_WAIT,
    EC_WORD_WAKE_UP,
    EC_WORD_WAKES_UP,
    EC_WORD_WALK,
    EC_WORD_WALKING,
    EC_WORD_WALKS,
    EC_POKEMON2(WALREIN),
    EC_WORD_WANDERING,
    EC_WORD_WANNABE,
    EC_WORD_WANT,
    EC_WORD_WANTS,
    EC_POKEMON(WARTORTLE),
    EC_WORD_WAS,
    EC_WORD_WASN_T,
    EC_WORD_WATER,
    EC_WORD_WATER_ABSORB,
    EC_MOVE2(WATER_GUN),
    EC_MOVE2(WATER_PULSE),
    EC_MOVE2(WATER_SPORT),
    EC_MOVE(WATER_SPOUT),
    EC_WORD_WATER_VEIL,
    EC_MOVE2(WATERFALL),
    EC_WORD_WAY,
    EC_WORD_WE,
    EC_WORD_WE_RE,
    EC_WORD_WE_VE,
    EC_WORD_WEAK,
    EC_WORD_WEAKENED,
    EC_MOVE(WEATHER_BALL),
    EC_WORD_WEDNESDAY,
    EC_POKEMON(WEEDLE),
    EC_WORD_WEEK,
    EC_POKEMON(WEEPINBELL),
    -1, 2, // Doubled pokemon species name
    EC_POKEMON2(WEEZING),
    EC_POKEMON(WEEZING),
    EC_WORD_WEIRD,
    EC_WORD_WELCOME,
    EC_WORD_WELL,
    EC_WORD_WELL_THEN,
    EC_WORD_WENT,
    EC_WORD_WERE,
    EC_WORD_WEREN_T,
    EC_WORD_WHAT,
    EC_WORD_WHAT_S_UP_QUES,
    EC_WORD_WHEN,
    EC_WORD_WHEN_I_WIN,
    EC_WORD_WHERE,
    EC_WORD_WHICH,
    EC_WORD_WHILE,
    EC_MOVE(WHIRLPOOL),
    EC_MOVE2(WHIRLWIND),
    EC_POKEMON2(WHISCASH),
    EC_POKEMON2(WHISMUR),
    EC_WORD_WHITE_SMOKE,
    EC_WORD_WHO,
    EC_WORD_WHO_IS,
    EC_WORD_WHO_WAS,
    EC_WORD_WHOAH,
    EC_WORD_WHOM,
    EC_WORD_WHOSE,
    EC_WORD_WHY,
    -1, 2, // Doubled pokemon species name
    EC_POKEMON2(WIGGLYTUFF),
    EC_POKEMON(WIGGLYTUFF),
    EC_WORD_WILD,
    EC_WORD_WILL,
    EC_WORD_WILL_BE_HERE,
    EC_MOVE(WILL_O_WISP),
    EC_WORD_WIMPY,
    EC_WORD_WIN,
    EC_MOVE2(WING_ATTACK),
    EC_POKEMON2(WINGULL),
    EC_WORD_WINNER,
    EC_WORD_WINS,
    EC_WORD_WINTER,
    EC_WORD_WIRELESS,
    EC_MOVE2(WISH),
    EC_WORD_WITH,
    EC_MOVE(WITHDRAW),
    EC_WORD_WITHOUT,
    EC_WORD_WOBBLY,
    -1, 2, // Doubled pokemon species name
    EC_POKEMON2(WOBBUFFET),
    EC_POKEMON(WOBBUFFET),
    EC_WORD_WOMAN,
    EC_WORD_WON,
    EC_WORD_WON_T,
    EC_WORD_WONDER,
    EC_WORD_WONDER_GUARD,
    EC_POKEMON(WOOPER),
    EC_WORD_WORD,
    EC_WORD_WORK,
    EC_WORD_WORKING,
    EC_WORD_WORKS,
    EC_WORD_WORLD,
    EC_WORD_WORRY,
    EC_WORD_WOULD,
    EC_WORD_WOW,
    EC_WORD_WOWEE,
    EC_MOVE2(WRAP),
    EC_WORD_WROOOAAR_EXCL,
    EC_POKEMON2(WURMPLE),
    EC_POKEMON2(WYNAUT),
};

static const u16 sEasyChatWordsByLetter_X[] = {
    -1, 2, // Doubled pokemon species name
    EC_POKEMON2(XATU),
    EC_POKEMON(XATU),
};

static const u16 sEasyChatWordsByLetter_Y[] = {
    EC_WORD_YAHOO,
    EC_POKEMON(YANMA),
    EC_MOVE(YAWN),
    EC_WORD_YAY,
    EC_WORD_YEAH,
    EC_WORD_YEAH_YEAH,
    EC_WORD_YEEHAW_EXCL,
    EC_WORD_YES,
    EC_WORD_YES_SIR_EXCL,
    EC_WORD_YESTERDAY,
    EC_WORD_YET,
    EC_WORD_YO,
    EC_WORD_YOU,
    EC_WORD_YOU_RE,
    EC_WORD_YOU_VE,
    EC_WORD_YOUNG,
    EC_WORD_YOUR,
    EC_WORD_YOURS,
    EC_WORD_YUP,
};

static const u16 sEasyChatWordsByLetter_Z[] = {
    EC_POKEMON2(ZANGOOSE),
    EC_MOVE2(ZAP_CANNON),
    EC_POKEMON(ZAPDOS),
    EC_POKEMON2(ZIGZAGOON),
    -1, 2, // Doubled pokemon species name
    EC_POKEMON2(ZUBAT),
    EC_POKEMON(ZUBAT),
};

static const struct EasyChatWordsByLetter sEasyChatWordsByLetterPointers[] = {
    {
        .words = sEasyChatWordsByLetter_Others,
        .numWords = 10,
    },
    {
        .words = sEasyChatWordsByLetter_A,
        .numWords = 106,
    },
    {
        .words = sEasyChatWordsByLetter_B,
        .numWords = 86,
    },
    {
        .words = sEasyChatWordsByLetter_C,
        .numWords = 119,
    },
    {
        .words = sEasyChatWordsByLetter_D,
        .numWords = 94,
    },
    {
        .words = sEasyChatWordsByLetter_E,
        .numWords = 58,
    },
    {
        .words = sEasyChatWordsByLetter_F,
        .numWords = 79,
    },
    {
        .words = sEasyChatWordsByLetter_G,
        .numWords = 98,
    },
    {
        .words = sEasyChatWordsByLetter_H,
        .numWords = 101,
    },
    {
        .words = sEasyChatWordsByLetter_I,
        .numWords = 48,
    },
    {
        .words = sEasyChatWordsByLetter_J,
        .numWords = 13,
    },
    {
        .words = sEasyChatWordsByLetter_K,
        .numWords = 33,
    },
    {
        .words = sEasyChatWordsByLetter_L,
        .numWords = 82,
    },
    {
        .words = sEasyChatWordsByLetter_M,
        .numWords = 142,
    },
    {
        .words = sEasyChatWordsByLetter_N,
        .numWords = 54,
    },
    {
        .words = sEasyChatWordsByLetter_O,
        .numWords = 44,
    },
    {
        .words = sEasyChatWordsByLetter_P,
        .numWords = 102,
    },
    {
        .words = sEasyChatWordsByLetter_Q,
        .numWords = 6,
    },
    {
        .words = sEasyChatWordsByLetter_R,
        .numWords = 80,
    },
    {
        .words = sEasyChatWordsByLetter_S,
        .numWords = 262,
    },
    {
        .words = sEasyChatWordsByLetter_T,
        .numWords = 133,
    },
    {
        .words = sEasyChatWordsByLetter_U,
        .numWords = 24,
    },
    {
        .words = sEasyChatWordsByLetter_V,
        .numWords = 33,
    },
    {
        .words = sEasyChatWordsByLetter_W,
        .numWords = 111,
    },
    {
        .words = sEasyChatWordsByLetter_X,
        .numWords = 4,
    },
    {
        .words = sEasyChatWordsByLetter_Y,
        .numWords = 19,
    },
    {
        .words = sEasyChatWordsByLetter_Z,
        .numWords = 8,
    },
};
// ===== END src/data/easy_chat/easy_chat_words_by_letter.h =====

static const u8 *const sEasyChatGroupNamePointers[] = {
    [EC_GROUP_POKEMON] = gEasyChatGroupName_Pokemon,
    [EC_GROUP_TRAINER] = gEasyChatGroupName_Trainer,
    [EC_GROUP_STATUS] = gEasyChatGroupName_Status,
    [EC_GROUP_BATTLE] = gEasyChatGroupName_Battle,
    [EC_GROUP_GREETINGS] = gEasyChatGroupName_Greetings,
    [EC_GROUP_PEOPLE] = gEasyChatGroupName_People,
    [EC_GROUP_VOICES] = gEasyChatGroupName_Voices,
    [EC_GROUP_SPEECH] = gEasyChatGroupName_Speech,
    [EC_GROUP_ENDINGS] = gEasyChatGroupName_Endings,
    [EC_GROUP_FEELINGS] = gEasyChatGroupName_Feelings,
    [EC_GROUP_CONDITIONS] = gEasyChatGroupName_Conditions,
    [EC_GROUP_ACTIONS] = gEasyChatGroupName_Actions,
    [EC_GROUP_LIFESTYLE] = gEasyChatGroupName_Lifestyle,
    [EC_GROUP_HOBBIES] = gEasyChatGroupName_Hobbies,
    [EC_GROUP_TIME] = gEasyChatGroupName_Time,
    [EC_GROUP_MISC] = gEasyChatGroupName_Misc,
    [EC_GROUP_ADJECTIVES] = gEasyChatGroupName_Adjectives,
    [EC_GROUP_EVENTS] = gEasyChatGroupName_Events,
    [EC_GROUP_MOVE_1] = gEasyChatGroupName_Move1,
    [EC_GROUP_MOVE_2] = gEasyChatGroupName_Move2,
    [EC_GROUP_TRENDY_SAYING] = gEasyChatGroupName_TrendySaying,
    [EC_GROUP_POKEMON_2] = gEasyChatGroupName_Pokemon2,
};

static const u16 sDefaultProfileWords[] = {
    EC_WORD_I_AM,
    EC_WORD_A,
    EC_WORD_POKEMON,
    EC_WORD_FRIEND,
};

static const u16 sDefaultBattleStartWords[] = {
    EC_WORD_ARE,
    EC_WORD_YOU,
    EC_WORD_READY,
    EC_WORD_QUES,
    EC_WORD_HERE_I_COME,
    EC_WORD_EXCL,
};

static const u16 sDeoxysValue[] = {
    SPECIES_DEOXYS,
};

static bool8 IsECGroupUnlocked(u8 groupId)
{
    switch (groupId)
    {
    case EC_GROUP_TRENDY_SAYING:
        return FALSE;
    case EC_GROUP_EVENTS:
    case EC_GROUP_MOVE_1:
    case EC_GROUP_MOVE_2:
        return FlagGet(FLAG_SYS_GAME_CLEAR);
    case EC_GROUP_POKEMON:
        return EC_IsNationalPokedexEnabled();
    default:
        return TRUE;
    }
}

static u16 EasyChat_GetNumWordsInGroup(u8 groupId)
{
    if (groupId == EC_GROUP_POKEMON)
        return GetNationalPokedexCount(FLAG_GET_SEEN);

    if (IsECGroupUnlocked(groupId))
        return sEasyChatGroups[groupId].numEnabledWords;

    return 0;
}

static bool8 IsECWordInvalid(u16 easyChatWord)
{
    u16 i;
    u8 groupId;
    u32 index;
    u16 numWords;
    const u16 *list;
    if (easyChatWord == EC_WORD_UNDEFINED)
        return FALSE;

    groupId = EC_GROUP(easyChatWord);
    index = EC_INDEX(easyChatWord);
    if (groupId >= EC_NUM_GROUPS)
        return TRUE;

    numWords = sEasyChatGroups[groupId].numWords;
    switch (groupId)
    {
    case EC_GROUP_POKEMON:
    case EC_GROUP_POKEMON_2:
    case EC_GROUP_MOVE_1:
    case EC_GROUP_MOVE_2:
        list = sEasyChatGroups[groupId].wordData.valueList;
        for (i = 0; i < numWords; i++)
        {
            if (index == list[i])
                return FALSE;
        }
        return TRUE;
    default:
        if (index >= numWords)
            return TRUE;
        else
            return FALSE;
    }
}

static const u8 *GetEasyChatWord(u8 groupId, u16 index)
{
    switch (groupId)
    {
    case EC_GROUP_POKEMON:
    case EC_GROUP_POKEMON_2:
        return gSpeciesNames[index];
    case EC_GROUP_MOVE_1:
    case EC_GROUP_MOVE_2:
        return gMoveNames[index];
    default:
        return sEasyChatGroups[groupId].wordData.words[index].text;
    }
}

u8 *CopyEasyChatWord(u8 *dest, u16 easyChatWord)
{
    u8 *resultStr;
    if (IsECWordInvalid(easyChatWord))
    {
        resultStr = StringCopy(dest, gText_ThreeQuestionMarks);
    }
    else if (easyChatWord != EC_WORD_UNDEFINED)
    {
        u16 index = EC_INDEX(easyChatWord);
        u8 groupId = EC_GROUP(easyChatWord);
        resultStr = StringCopy(dest, GetEasyChatWord(groupId, index));
    }
    else
    {
        *dest = EOS;
        resultStr = dest;
    }

    return resultStr;
}

u8 *ConvertEasyChatWordsToString(u8 *dest, const u16 *src, u16 columns, u16 rows)
{
    u16 i, j;
    u16 numColumns = columns - 1;

    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < numColumns; j++)
        {
            dest = CopyEasyChatWord(dest, *src);
            if (*src != EC_WORD_UNDEFINED)
            {
                *dest = CHAR_SPACE;
                dest++;
            }

            src++;
        }

        dest = CopyEasyChatWord(dest, *(src++));
        *dest = CHAR_NEWLINE;
        dest++;
    }

    dest--;
    *dest = EOS;
    return dest;
}

static u16 GetEasyChatWordStringLength(u16 easyChatWord)
{
    if (easyChatWord == EC_WORD_UNDEFINED)
        return 0;

    if (IsECWordInvalid(easyChatWord))
    {
        return StringLength(gText_ThreeQuestionMarks);
    }
    else
    {
        u16 index = EC_INDEX(easyChatWord);
        u8 groupId = EC_GROUP(easyChatWord);
        return StringLength(GetEasyChatWord(groupId, index));
    }
}

bool8 EC_DoesEasyChatStringFitOnLine(const u16 *easyChatWords, u8 columns, u8 rows, u16 maxLength)
{
    u8 i, j;

    for (i = 0; i < rows; i++)
    {
        u16 totalLength = columns - 1;
        for (j = 0; j < columns; j++)
            totalLength += GetEasyChatWordStringLength(*(easyChatWords++));

        if (totalLength > maxLength)
            return TRUE;
    }

    return FALSE;
}

static u16 GetRandomWordFromGroup(u16 groupId)
{
    u16 index = Random() % sEasyChatGroups[groupId].numWords;
    if (groupId == EC_GROUP_POKEMON_2
     || groupId == EC_GROUP_POKEMON
     || groupId == EC_GROUP_MOVE_1
     || groupId == EC_GROUP_MOVE_2)
    {
        index = sEasyChatGroups[groupId].wordData.valueList[index];
    }

    return EC_WORD(groupId, index);
}

static u16 GetRandomWordFromAnyGroup(u16 groupId)
{
    if (!IsECGroupUnlocked(groupId))
        return EC_WORD_UNDEFINED;

    if (groupId == EC_GROUP_POKEMON)
        return GetRandomECPokemon();

    return GetRandomWordFromGroup(groupId);
}

void ShowEasyChatMessage(void)
{
    u16 *easyChatWords;
    int columns, rows;
    switch (gSpecialVar_0x8004)
    {
    case 0:
        easyChatWords = gSaveBlock1Ptr->easyChatProfile;
        columns = 2;
        rows = 2;
        break;
    case 1:
        easyChatWords = gSaveBlock1Ptr->easyChatBattleStart;
        if (EC_DoesEasyChatStringFitOnLine(gSaveBlock1Ptr->easyChatBattleStart, 3, 2, 18))
        {
            columns = 2;
            rows = 3;
        }
        else
        {
            columns = 3;
            rows = 2;
        }
        break;
    case 2:
        easyChatWords = gSaveBlock1Ptr->easyChatBattleWon;
        columns = 3;
        rows = 2;
        break;
    case 3:
        easyChatWords = gSaveBlock1Ptr->easyChatBattleLost;
        columns = 3;
        rows = 2;
        break;
    default:
        return;
    }

    ConvertEasyChatWordsToString(gStringVar4, easyChatWords, columns, rows);
    ShowFieldAutoScrollMessage(gStringVar4);
}

void BufferRandomHobbyOrLifestyleString(void)
{
    int groupId = Random() & 1 ? EC_GROUP_HOBBIES : EC_GROUP_LIFESTYLE;
    u16 easyChatWord = GetRandomWordFromAnyGroup(groupId);
    CopyEasyChatWord(gStringVar2, easyChatWord);
}

static bool8 IsTrendySayingUnlocked(u8 additionalPhraseId)
{
    int byteOffset = additionalPhraseId / 8;
    int shift = additionalPhraseId % 8;
    return (gSaveBlock1Ptr->additionalPhrases[byteOffset] >> shift) & 1;
}

void EnableRareWord(u8 additionalPhraseId)
{
    if (additionalPhraseId < 33)
    {
        int byteOffset = additionalPhraseId / 8;
        int shift = additionalPhraseId % 8;
        gSaveBlock1Ptr->additionalPhrases[byteOffset] |= 1 << shift;
    }
}

static u8 GetNumUnlockedTrendySayings(void)
{
    u8 i;
    u8 numAdditionalPhrasesUnlocked;

    for (i = 0, numAdditionalPhrasesUnlocked = 0; i < 33; i++)
    {
        if (IsTrendySayingUnlocked(i))
            numAdditionalPhrasesUnlocked++;
    }

    return numAdditionalPhrasesUnlocked;
}

static u16 UnlockRandomTrendySaying(void)
{
    u16 i;
    u16 additionalPhraseId;
    u8 numAdditionalPhrasesUnlocked = GetNumUnlockedTrendySayings();
    if (numAdditionalPhrasesUnlocked == 33)
        return EC_WORD_UNDEFINED;

    additionalPhraseId = Random() % (33 - numAdditionalPhrasesUnlocked);
    for (i = 0; i < 33; i++)
    {
        if (!IsTrendySayingUnlocked(i))
        {
            if (additionalPhraseId)
            {
                additionalPhraseId--;
            }
            else
            {
                EnableRareWord(i);
                return EC_WORD(EC_GROUP_TRENDY_SAYING, i);
            }
        }
    }

    return EC_WORD_UNDEFINED;
}

static u16 GetRandomUnlockedTrendySaying(void)
{
    u16 i;
    u16 additionalPhraseId = GetNumUnlockedTrendySayings();
    if (additionalPhraseId == 0)
        return EC_WORD_UNDEFINED;

    additionalPhraseId = Random() % additionalPhraseId;
    for (i = 0; i < 33; i++)
    {
        if (IsTrendySayingUnlocked(i))
        {
            if (additionalPhraseId)
                additionalPhraseId--;
            else
                return EC_WORD(EC_GROUP_TRENDY_SAYING, i);
        }
    }

    return EC_WORD_UNDEFINED;
}

static bool8 EC_IsNationalPokedexEnabled(void)
{
    return IsNationalPokedexEnabled();
}

static u16 GetRandomECPokemon(void)
{
    u16 i;
    u16 numWords;
    const u16 *species;
    u16 index = EasyChat_GetNumWordsInGroup(EC_GROUP_POKEMON_2);
    if (index == 0)
        return EC_WORD_UNDEFINED;

    index = Random() % index;
    species = sEasyChatGroups[EC_GROUP_POKEMON_2].wordData.valueList;
    numWords = sEasyChatGroups[EC_GROUP_POKEMON_2].numWords;
    for (i = 0; i < numWords; i++)
    {
        u16 dexNum = SpeciesToNationalPokedexNum(*species);
        if (GetSetPokedexFlag(dexNum, FLAG_GET_SEEN))
        {
            if (index)
                index--;
            else
                return EC_WORD(EC_GROUP_POKEMON_2, *species);
        }

        species++;
    }

    return EC_WORD_UNDEFINED;
}

void InitEasyChatPhrases(void)
{
    u16 i, j;

    for (i = 0; i < 4; i++)
        gSaveBlock1Ptr->easyChatProfile[i] = sDefaultProfileWords[i];

    for (i = 0; i < 6; i++)
        gSaveBlock1Ptr->easyChatBattleStart[i] = sDefaultBattleStartWords[i];

    for (i = 0; i < 6; i++)
    {
        gSaveBlock1Ptr->easyChatBattleWon[i] = EC_WORD_UNDEFINED;
        gSaveBlock1Ptr->easyChatBattleLost[i] = EC_WORD_UNDEFINED;
    }

    for (i = 0; i < MAIL_COUNT; i++)
    {
        for (j = 0; j < MAIL_WORDS_COUNT; j++)
            gSaveBlock1Ptr->mail[i].words[j] = EC_WORD_UNDEFINED;
    }

#ifndef UBFIX
    // BUG: This is supposed to clear 64 bits, but this loop is clearing 64 bytes.
    // However, this bug has no resulting effect on gameplay because only the
    // Mauville old man data is corrupted, which is initialized directly after
    // this function is called when starting a new game.
    for (i = 0; i < 64; i++)
        gSaveBlock1Ptr->additionalPhrases[i] = 0;
#else
    for (i = 0; i < NELEMS(gSaveBlock1Ptr->additionalPhrases); i++)
        gSaveBlock1Ptr->additionalPhrases[i] = 0;
#endif
}

void InitQuestionnaireWords(void)
{
    s32 i;
    u16 *ptr = GetQuestionnaireWordsPtr();
    for (i = 0; i < NUM_QUESTIONNAIRE_WORDS; i++)
        ptr[i] = EC_WORD_UNDEFINED;
}

bool8 InitEasyChatSelection(void)
{
    sEasyChatSelectionData = Alloc(sizeof(*sEasyChatSelectionData));
    if (sEasyChatSelectionData == NULL)
        return FALSE;

    PopulateECGroups();
    PopulateAlphabeticalGroups();
    return TRUE;
}

void DestroyEasyChatSelectionData(void)
{
    if (sEasyChatSelectionData != NULL)
        Free(sEasyChatSelectionData);
}

static void PopulateECGroups(void)
{
    int i;

    sEasyChatSelectionData->numGroups = 0;
    if (GetNationalPokedexCount(FLAG_GET_SEEN))
        sEasyChatSelectionData->groups[sEasyChatSelectionData->numGroups++] = EC_GROUP_POKEMON;

    for (i = EC_GROUP_TRAINER; i <= EC_GROUP_ADJECTIVES; i++)
        sEasyChatSelectionData->groups[sEasyChatSelectionData->numGroups++] = i;

    if (FlagGet(FLAG_SYS_GAME_CLEAR))
    {
        sEasyChatSelectionData->groups[sEasyChatSelectionData->numGroups++] = EC_GROUP_EVENTS;
        sEasyChatSelectionData->groups[sEasyChatSelectionData->numGroups++] = EC_GROUP_MOVE_1;
        sEasyChatSelectionData->groups[sEasyChatSelectionData->numGroups++] = EC_GROUP_MOVE_2;
    }

    if (IsNationalPokedexEnabled())
        sEasyChatSelectionData->groups[sEasyChatSelectionData->numGroups++] = EC_GROUP_POKEMON_2;
}

u8 GetNumDisplayableGroups(void)
{
    return sEasyChatSelectionData->numGroups;
}

u8 GetSelectedGroupByIndex(u8 index)
{
    if (index >= sEasyChatSelectionData->numGroups)
        return EC_NUM_GROUPS;
    else
        return sEasyChatSelectionData->groups[index];
}

// Unused
static u8 *BufferEasyChatWordGroupName(u8 *dest, u8 groupId, u16 totalChars)
{
    u16 i;
    u8 *str = StringCopy(dest, sEasyChatGroupNamePointers[groupId]);
    for (i = str - dest; i < totalChars; i++)
    {
        *str = CHAR_SPACE;
        str++;
    }

    *str = EOS;
    return str;
}

const u8 *GetEasyChatWordGroupName(u8 groupId)
{
    return sEasyChatGroupNamePointers[groupId];
}

u8 *CopyEasyChatWordPadded(u8 *dest, u16 easyChatWord, u16 totalChars)
{
    u16 i;
    u8 *str = CopyEasyChatWord(dest, easyChatWord);
    for (i = str - dest; i < totalChars; i++)
    {
        *str = CHAR_SPACE;
        str++;
    }

    *str = EOS;
    return str;
}

static void PopulateAlphabeticalGroups(void)
{
    static int i;
    static int j;
    static int k;
    static int index;
    static int numWords;
    static int numToProcess;
    static const u16 *words;

    for (i = 0; i < 27; i++)
    {
        numWords = sEasyChatWordsByLetterPointers[i].numWords;
        words = sEasyChatWordsByLetterPointers[i].words;
        sEasyChatSelectionData->alphabeticalGroups[i] = 0;
        index = 0;
        for (j = 0; j < numWords; )
        {
            if (*words == EC_WORD_UNDEFINED)
            {
                words++;
                numToProcess = *words++;
                j += 2;
            }
            else
            {
                numToProcess = 1;
            }

            for (k = 0; k < numToProcess; k++)
            {
                if (IsWordUnlocked(words[k]))
                {
                    sEasyChatSelectionData->alphabeticalWordsByGroup[i][index++] = words[k];
                    sEasyChatSelectionData->alphabeticalGroups[i]++;
                    break;
                }
            }

            words += numToProcess;
            j += numToProcess;
        }
    }
}

void GetUnlockedECWords(bool32 isAlphabetical, u16 groupId)
{
    if (!isAlphabetical)
        sEasyChatSelectionData->totalWords = GetUnlockedWordsInECGroup(groupId);
    else
        sEasyChatSelectionData->totalWords = GetUnlockedWordsInAlphabeticalGroup(groupId);
}

u16 GetDisplayedWordByIndex(u16 index)
{
    if (index >= sEasyChatSelectionData->totalWords)
        return EC_WORD_UNDEFINED;
    else
        return sEasyChatSelectionData->allWords[index];
}

u16 GetNumDisplayedWords(void)
{
    return sEasyChatSelectionData->totalWords;
}

static u16 GetUnlockedWordsInECGroup(u16 groupId)
{
    u16 i;
    u16 totalWords;
    const u16 *list;
    const struct EasyChatWordInfo * wordInfo;
    u16 numWords = sEasyChatGroups[groupId].numWords;

    if (groupId == EC_GROUP_POKEMON_2 || groupId == EC_GROUP_POKEMON
     || groupId == EC_GROUP_MOVE_1  || groupId == EC_GROUP_MOVE_2)
    {
        list = sEasyChatGroups[groupId].wordData.valueList;
        for (i = 0, totalWords = 0; i < numWords; i++)
        {
            if (UnlockedECMonOrMove(list[i], groupId))
                sEasyChatSelectionData->allWords[totalWords++] = EC_WORD(groupId, list[i]);
        }

        return totalWords;
    }
    else
    {
        wordInfo = sEasyChatGroups[groupId].wordData.words;
        for (i = 0, totalWords = 0; i < numWords; i++)
        {
            u16 alphabeticalOrder = wordInfo[i].alphabeticalOrder;
            if (UnlockedECMonOrMove(alphabeticalOrder, groupId))
                sEasyChatSelectionData->allWords[totalWords++] = EC_WORD(groupId, alphabeticalOrder);
        }

        return totalWords;
    }
}

static u16 GetUnlockedWordsInAlphabeticalGroup(u16 alphabeticalGroup)
{
    u16 i;
    u16 totalWords;

    for (i = 0, totalWords = 0; i < sEasyChatSelectionData->alphabeticalGroups[alphabeticalGroup]; i++)
        sEasyChatSelectionData->allWords[totalWords++] = sEasyChatSelectionData->alphabeticalWordsByGroup[alphabeticalGroup][i];

    return totalWords;
}

static bool8 IsGroupSelectable(u8 groupIdx)
{
    int i;
    for (i = 0; i < sEasyChatSelectionData->numGroups; i++)
    {
        if (sEasyChatSelectionData->groups[i] == groupIdx)
            return TRUE;
    }

    return FALSE;
}

static bool8 UnlockedECMonOrMove(u16 wordIndex, u8 groupId)
{
    switch (groupId)
    {
    case EC_GROUP_POKEMON:
        return GetSetPokedexFlag(SpeciesToNationalPokedexNum(wordIndex), FLAG_GET_SEEN);
    case EC_GROUP_POKEMON_2:
        if (EC_IsDeoxys(wordIndex))
            return GetSetPokedexFlag(SpeciesToNationalPokedexNum(wordIndex), FLAG_GET_SEEN);
        return TRUE;
    case EC_GROUP_MOVE_1:
    case EC_GROUP_MOVE_2:
        return TRUE;
    default:
        return sEasyChatGroups[groupId].wordData.words[wordIndex].enabled;
    }
}

static bool32 EC_IsDeoxys(u16 species)
{
    u32 i;
    for (i = 0; i < NELEMS(sDeoxysValue); i++)
    {
        if (sDeoxysValue[i] == species)
            return TRUE;
    }

    return FALSE;
}

static bool8 IsWordUnlocked(u16 easyChatWord)
{
    u8 groupId = EC_GROUP(easyChatWord);
    u32 index = EC_INDEX(easyChatWord);
    if (!IsGroupSelectable(groupId))
        return FALSE;
    else
        return UnlockedECMonOrMove(index, groupId);
}
