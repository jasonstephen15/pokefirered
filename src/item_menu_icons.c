#include "global.h"
#include "gflib.h"
#include "decompress.h"
#include "graphics.h"
#include "item_menu_icons.h"
#include "constants/items.h"

enum {
    TAG_BAG = 100,
    TAG_SWAP_LINE,
    TAG_ITEM_ICON,
    TAG_ITEM_ICON_ALT,
};

#define NUM_SWAP_LINE_SPRITES 9

// Indexes for sItemMenuIconSpriteIds
enum {
    SPR_BAG,
    SPR_SWAP_LINE_START,
    SPR_ITEM_ICON = SPR_SWAP_LINE_START + NUM_SWAP_LINE_SPRITES,
    SPR_ITEM_ICON_ALT,
    SPR_COUNT
};

enum {
    ANIM_SWAP_LINE_START,
    ANIM_SWAP_LINE_MID,
    ANIM_SWAP_LINE_END,
};

enum {
    AFFINEANIM_BAG_IDLE,
    AFFINEANIM_BAG_SHAKE,
};

static EWRAM_DATA u8 sItemMenuIconSpriteIds[SPR_COUNT] = {0};
static EWRAM_DATA void *sItemIconTilesBuffer = NULL;
static EWRAM_DATA void *sItemIconTilesBufferPadded = NULL;

static void SpriteCB_BagVisualSwitchingPockets(struct Sprite *sprite);
static void SpriteCB_ShakeBagSprite(struct Sprite *sprite);

static const struct OamData sOamData_Bag = {
    .affineMode = ST_OAM_AFFINE_NORMAL,
    .shape = SPRITE_SHAPE(64x64),
    .size = SPRITE_SIZE(64x64),
    .priority = 1,
    .paletteNum = 0
};

static const union AnimCmd sAnim_Bag_OpenPokeBallsPocket[] = {
    ANIMCMD_FRAME(   0, 5),
    ANIMCMD_FRAME(0x40, 0),
    ANIMCMD_END
};

static const union AnimCmd sAnim_Bag_OpenItemsPocket[] = {
    ANIMCMD_FRAME(   0, 5),
    ANIMCMD_FRAME(0x80, 0),
    ANIMCMD_END
};

static const union AnimCmd sAnim_Bag_OpenKeyItemsPocket[] = {
    ANIMCMD_FRAME(   0, 5),
    ANIMCMD_FRAME(0xc0, 0),
    ANIMCMD_END
};

static const union AnimCmd *const sAnims_Bag[] = {
    [POCKET_ITEMS - 1]      = sAnim_Bag_OpenItemsPocket,
    [POCKET_KEY_ITEMS - 1]  = sAnim_Bag_OpenKeyItemsPocket,
    [POCKET_POKE_BALLS - 1] = sAnim_Bag_OpenPokeBallsPocket,
};

static const union AffineAnimCmd sAffineAnim_BagIdle[] = {
    AFFINEANIMCMD_FRAME(0x100, 0x100, 0, 0),
    AFFINEANIMCMD_END
};

static const union AffineAnimCmd sAffineAnim_BagShake[] = {
    AFFINEANIMCMD_FRAME(0, 0, -2, 2),
    AFFINEANIMCMD_FRAME(0, 0,  2, 4),
    AFFINEANIMCMD_FRAME(0, 0, -2, 4),
    AFFINEANIMCMD_FRAME(0, 0,  2, 2),
    AFFINEANIMCMD_END
};

static const union AffineAnimCmd *const sAffineAnimTable_Bag[] = {
    [AFFINEANIM_BAG_IDLE]  = sAffineAnim_BagIdle,
    [AFFINEANIM_BAG_SHAKE] = sAffineAnim_BagShake
};

const struct CompressedSpriteSheet gSpriteSheet_BagMale = {
    .data = gBagMale_Gfx,
    .size = 0x2000,
    .tag = TAG_BAG
};

const struct CompressedSpriteSheet gSpriteSheet_BagFemale = {
    .data = gBagFemale_Gfx,
    .size = 0x2000,
    .tag = TAG_BAG
};

const struct CompressedSpritePalette gSpritePalette_Bag = {
    .data = gBag_Pal,
    .tag = TAG_BAG
};

static const struct SpriteTemplate sSpriteTemplate_Bag = {
    .tileTag = TAG_BAG,
    .paletteTag = TAG_BAG,
    .oam = &sOamData_Bag,
    .anims = sAnims_Bag,
    .images = NULL,
    .affineAnims = sAffineAnimTable_Bag,
    .callback = SpriteCallbackDummy
};

static const struct OamData sOamData_SwapLine = {
    .affineMode = ST_OAM_AFFINE_OFF,
    .shape = SPRITE_SHAPE(16x16),
    .size = SPRITE_SIZE(16x16),
    .priority = 1,
    .paletteNum = 1
};

static const union AnimCmd sAnim_SwapLine_Start[] = {
    ANIMCMD_FRAME(0, 0),
    ANIMCMD_END
};

static const union AnimCmd sAnim_SwapLine_Mid[] = {
    ANIMCMD_FRAME(4, 0),
    ANIMCMD_END
};

static const union AnimCmd sAnim_SwapLine_End[] = {
    ANIMCMD_FRAME(0, 0, .hFlip = TRUE),
    ANIMCMD_END
};

static const union AnimCmd *const sAnims_SwapLine[] = {
    [ANIM_SWAP_LINE_START] = sAnim_SwapLine_Start,
    [ANIM_SWAP_LINE_MID]   = sAnim_SwapLine_Mid,
    [ANIM_SWAP_LINE_END]   = sAnim_SwapLine_End
};

const struct CompressedSpriteSheet gBagSwapSpriteSheet = {
    .data = gSwapLine_Gfx,
    .size = 0x100,
    .tag = TAG_SWAP_LINE
};

const struct CompressedSpritePalette gBagSwapSpritePalette = {
    .data = gSwapLine_Pal,
    .tag = TAG_SWAP_LINE
};

static const struct SpriteTemplate sSpriteTemplate_SwapLine = {
    .tileTag = TAG_SWAP_LINE,
    .paletteTag = TAG_SWAP_LINE,
    .oam = &sOamData_SwapLine,
    .anims = sAnims_SwapLine,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy
};

static const struct OamData sOamData_ItemIcon = {
    .affineMode = ST_OAM_AFFINE_OFF,
    .shape = SPRITE_SHAPE(32x32),
    .size = SPRITE_SIZE(32x32),
    .priority = 1,
    .paletteNum = 2
};

static const union AnimCmd sAnim_ItemIcon[] = {
    ANIMCMD_FRAME(0, 0),
    ANIMCMD_END
};

static const union AnimCmd *const sAnims_ItemIcon[] = {
    sAnim_ItemIcon
};

static const struct SpriteTemplate sSpriteTemplate_ItemIcon = {
    .tileTag = TAG_ITEM_ICON,
    .paletteTag = TAG_ITEM_ICON,
    .oam = &sOamData_ItemIcon,
    .anims = sAnims_ItemIcon,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy
};

// ===== BEGIN src/data/item_icon_table.h =====
static const u32 *const sItemIconTable[ITEMS_COUNT + 1][2] =
{
    [ITEM_NONE]           = {gItemIcon_QuestionMark, gItemIconPalette_QuestionMark},
    // Pokeballs
    [ITEM_MASTER_BALL]    = {gItemIcon_MasterBall, gItemIconPalette_MasterBall},
    [ITEM_ULTRA_BALL]     = {gItemIcon_UltraBall, gItemIconPalette_UltraBall},
    [ITEM_GREAT_BALL]     = {gItemIcon_GreatBall, gItemIconPalette_GreatBall},
    [ITEM_POKE_BALL]      = {gItemIcon_PokeBall, gItemIconPalette_PokeBall},
    [ITEM_SAFARI_BALL]    = {gItemIcon_SafariBall, gItemIconPalette_SafariBall},
    [ITEM_NET_BALL]       = {gItemIcon_NetBall, gItemIconPalette_NetBall},
    [ITEM_DIVE_BALL]      = {gItemIcon_DiveBall, gItemIconPalette_DiveBall},
    [ITEM_NEST_BALL]      = {gItemIcon_NestBall, gItemIconPalette_NestBall},
    [ITEM_REPEAT_BALL]    = {gItemIcon_RepeatBall, gItemIconPalette_RepeatBall},
    [ITEM_TIMER_BALL]     = {gItemIcon_TimerBall, gItemIconPalette_RepeatBall},
    [ITEM_LUXURY_BALL]    = {gItemIcon_LuxuryBall, gItemIconPalette_LuxuryBall},
    [ITEM_PREMIER_BALL]   = {gItemIcon_PremierBall, gItemIconPalette_LuxuryBall},
    // Medicine
    [ITEM_POTION]         = {gItemIcon_Potion, gItemIconPalette_Potion},
    [ITEM_ANTIDOTE]       = {gItemIcon_Antidote, gItemIconPalette_Antidote},
    [ITEM_BURN_HEAL]      = {gItemIcon_StatusHeal, gItemIconPalette_BurnHeal},
    [ITEM_ICE_HEAL]       = {gItemIcon_StatusHeal, gItemIconPalette_IceHeal},
    [ITEM_AWAKENING]      = {gItemIcon_StatusHeal, gItemIconPalette_Awakening},
    [ITEM_PARALYZE_HEAL]  = {gItemIcon_StatusHeal, gItemIconPalette_ParalyzeHeal},
    [ITEM_FULL_RESTORE]   = {gItemIcon_LargePotion, gItemIconPalette_FullRestore},
    [ITEM_MAX_POTION]     = {gItemIcon_LargePotion, gItemIconPalette_MaxPotion},
    [ITEM_HYPER_POTION]   = {gItemIcon_Potion, gItemIconPalette_HyperPotion},
    [ITEM_SUPER_POTION]   = {gItemIcon_Potion, gItemIconPalette_SuperPotion},
    [ITEM_FULL_HEAL]      = {gItemIcon_FullHeal, gItemIconPalette_FullHeal},
    [ITEM_REVIVE]         = {gItemIcon_Revive, gItemIconPalette_Revive},
    [ITEM_MAX_REVIVE]     = {gItemIcon_MaxRevive, gItemIconPalette_Revive},
    [ITEM_FRESH_WATER]    = {gItemIcon_FreshWater, gItemIconPalette_FreshWater},
    [ITEM_SODA_POP]       = {gItemIcon_SodaPop, gItemIconPalette_SodaPop},
    [ITEM_LEMONADE]       = {gItemIcon_Lemonade, gItemIconPalette_Lemonade},
    [ITEM_MOOMOO_MILK]    = {gItemIcon_MoomooMilk, gItemIconPalette_MoomooMilk},
    [ITEM_ENERGY_POWDER]  = {gItemIcon_Powder, gItemIconPalette_EnergyPowder},
    [ITEM_ENERGY_ROOT]    = {gItemIcon_EnergyRoot, gItemIconPalette_EnergyRoot},
    [ITEM_HEAL_POWDER]    = {gItemIcon_Powder, gItemIconPalette_HealPowder},
    [ITEM_REVIVAL_HERB]   = {gItemIcon_RevivalHerb, gItemIconPalette_RevivalHerb},
    [ITEM_ETHER]          = {gItemIcon_Ether, gItemIconPalette_Ether},
    [ITEM_MAX_ETHER]      = {gItemIcon_Ether, gItemIconPalette_MaxEther},
    [ITEM_ELIXIR]         = {gItemIcon_Ether, gItemIconPalette_Elixir},
    [ITEM_MAX_ELIXIR]     = {gItemIcon_Ether, gItemIconPalette_MaxElixir},
    [ITEM_LAVA_COOKIE]    = {gItemIcon_LavaCookie, gItemIconPalette_LavaCookieAndLetter},
    [ITEM_BLUE_FLUTE]     = {gItemIcon_Flute, gItemIconPalette_BlueFlute},
    [ITEM_YELLOW_FLUTE]   = {gItemIcon_Flute, gItemIconPalette_YellowFlute},
    [ITEM_RED_FLUTE]      = {gItemIcon_Flute, gItemIconPalette_RedFlute},
    [ITEM_BLACK_FLUTE]    = {gItemIcon_Flute, gItemIconPalette_BlackFlute},
    [ITEM_WHITE_FLUTE]    = {gItemIcon_Flute, gItemIconPalette_WhiteFlute},
    [ITEM_BERRY_JUICE]    = {gItemIcon_BerryJuice, gItemIconPalette_BerryJuice},
    [ITEM_SACRED_ASH]     = {gItemIcon_SacredAsh, gItemIconPalette_SacredAsh},
    // Collectibles
    [ITEM_SHOAL_SALT]     = {gItemIcon_Powder, gItemIconPalette_ShoalSalt},
    [ITEM_SHOAL_SHELL]    = {gItemIcon_ShoalShell, gItemIconPalette_Shell},
    [ITEM_RED_SHARD]      = {gItemIcon_Shard, gItemIconPalette_RedShard},
    [ITEM_BLUE_SHARD]     = {gItemIcon_Shard, gItemIconPalette_BlueShard},
    [ITEM_YELLOW_SHARD]   = {gItemIcon_Shard, gItemIconPalette_YellowShard},
    [ITEM_GREEN_SHARD]    = {gItemIcon_Shard, gItemIconPalette_GreenShard},
    // ????????
    [ITEM_034]            = {gItemIcon_QuestionMark, gItemIconPalette_QuestionMark},
    [ITEM_035]            = {gItemIcon_QuestionMark, gItemIconPalette_QuestionMark},
    [ITEM_036]            = {gItemIcon_QuestionMark, gItemIconPalette_QuestionMark},
    [ITEM_037]            = {gItemIcon_QuestionMark, gItemIconPalette_QuestionMark},
    [ITEM_038]            = {gItemIcon_QuestionMark, gItemIconPalette_QuestionMark},
    [ITEM_039]            = {gItemIcon_QuestionMark, gItemIconPalette_QuestionMark},
    [ITEM_03A]            = {gItemIcon_QuestionMark, gItemIconPalette_QuestionMark},
    [ITEM_03B]            = {gItemIcon_QuestionMark, gItemIconPalette_QuestionMark},
    [ITEM_03C]            = {gItemIcon_QuestionMark, gItemIconPalette_QuestionMark},
    [ITEM_03D]            = {gItemIcon_QuestionMark, gItemIconPalette_QuestionMark},
    [ITEM_03E]            = {gItemIcon_QuestionMark, gItemIconPalette_QuestionMark},
    // Vitamins
    [ITEM_HP_UP]          = {gItemIcon_HPUp, gItemIconPalette_HPUp},
    [ITEM_PROTEIN]        = {gItemIcon_Vitamin, gItemIconPalette_Protein},
    [ITEM_IRON]           = {gItemIcon_Vitamin, gItemIconPalette_Iron},
    [ITEM_CARBOS]         = {gItemIcon_Vitamin, gItemIconPalette_Carbos},
    [ITEM_CALCIUM]        = {gItemIcon_Vitamin, gItemIconPalette_Calcium},
    [ITEM_RARE_CANDY]     = {gItemIcon_RareCandy, gItemIconPalette_RareCandy},
    [ITEM_PP_UP]          = {gItemIcon_PPUp, gItemIconPalette_PPUp},
    [ITEM_ZINC]           = {gItemIcon_Vitamin, gItemIconPalette_Zinc},
    [ITEM_PP_MAX]         = {gItemIcon_PPMax, gItemIconPalette_PPMax},
    // ????????
    [ITEM_048]            = {gItemIcon_QuestionMark, gItemIconPalette_QuestionMark},
    // Battle items
    [ITEM_GUARD_SPEC]     = {gItemIcon_BattleStatItem, gItemIconPalette_GuardSpec},
    [ITEM_DIRE_HIT]       = {gItemIcon_BattleStatItem, gItemIconPalette_DireHit},
    [ITEM_X_ATTACK]       = {gItemIcon_BattleStatItem, gItemIconPalette_XAttack},
    [ITEM_X_DEFEND]       = {gItemIcon_BattleStatItem, gItemIconPalette_XDefend},
    [ITEM_X_SPEED]        = {gItemIcon_BattleStatItem, gItemIconPalette_XSpeed},
    [ITEM_X_ACCURACY]     = {gItemIcon_BattleStatItem, gItemIconPalette_XAccuracy},
    [ITEM_X_SPECIAL]      = {gItemIcon_BattleStatItem, gItemIconPalette_XSpecial},
    [ITEM_POKE_DOLL]      = {gItemIcon_PokeDoll, gItemIconPalette_PokeDoll},
    [ITEM_FLUFFY_TAIL]    = {gItemIcon_FluffyTail, gItemIconPalette_FluffyTail},
    // ????????
    [ITEM_052]            = {gItemIcon_QuestionMark, gItemIconPalette_QuestionMark},
    // Field items
    [ITEM_SUPER_REPEL]    = {gItemIcon_Repel, gItemIconPalette_SuperRepel},
    [ITEM_MAX_REPEL]      = {gItemIcon_Repel, gItemIconPalette_MaxRepel},
    [ITEM_ESCAPE_ROPE]    = {gItemIcon_EscapeRope, gItemIconPalette_EscapeRope},
    [ITEM_REPEL]          = {gItemIcon_Repel, gItemIconPalette_Repel},
    // ????????
    [ITEM_057]            = {gItemIcon_QuestionMark, gItemIconPalette_QuestionMark},
    [ITEM_058]            = {gItemIcon_QuestionMark, gItemIconPalette_QuestionMark},
    [ITEM_059]            = {gItemIcon_QuestionMark, gItemIconPalette_QuestionMark},
    [ITEM_05A]            = {gItemIcon_QuestionMark, gItemIconPalette_QuestionMark},
    [ITEM_05B]            = {gItemIcon_QuestionMark, gItemIconPalette_QuestionMark},
    [ITEM_05C]            = {gItemIcon_QuestionMark, gItemIconPalette_QuestionMark},
    // Evolution stones
    [ITEM_SUN_STONE]      = {gItemIcon_SunStone, gItemIconPalette_SunStone},
    [ITEM_MOON_STONE]     = {gItemIcon_MoonStone, gItemIconPalette_MoonStone},
    [ITEM_FIRE_STONE]     = {gItemIcon_FireStone, gItemIconPalette_FireStone},
    [ITEM_THUNDER_STONE]  = {gItemIcon_ThunderStone, gItemIconPalette_ThunderStone},
    [ITEM_WATER_STONE]    = {gItemIcon_WaterStone, gItemIconPalette_WaterStone},
    [ITEM_LEAF_STONE]     = {gItemIcon_LeafStone, gItemIconPalette_LeafStone},
    // ????????
    [ITEM_063]            = {gItemIcon_QuestionMark, gItemIconPalette_QuestionMark},
    [ITEM_064]            = {gItemIcon_QuestionMark, gItemIconPalette_QuestionMark},
    [ITEM_065]            = {gItemIcon_QuestionMark, gItemIconPalette_QuestionMark},
    [ITEM_066]            = {gItemIcon_QuestionMark, gItemIconPalette_QuestionMark},
    // Valuables
    [ITEM_TINY_MUSHROOM]  = {gItemIcon_TinyMushroom, gItemIconPalette_Mushroom},
    [ITEM_BIG_MUSHROOM]   = {gItemIcon_BigMushroom, gItemIconPalette_Mushroom},
    [ITEM_069]            = {gItemIcon_QuestionMark, gItemIconPalette_QuestionMark},
    [ITEM_PEARL]          = {gItemIcon_Pearl, gItemIconPalette_Pearl},
    [ITEM_BIG_PEARL]      = {gItemIcon_BigPearl, gItemIconPalette_Pearl},
    [ITEM_STARDUST]       = {gItemIcon_Stardust, gItemIconPalette_Star},
    [ITEM_STAR_PIECE]     = {gItemIcon_StarPiece, gItemIconPalette_Star},
    [ITEM_NUGGET]         = {gItemIcon_Nugget, gItemIconPalette_Nugget},
    [ITEM_HEART_SCALE]    = {gItemIcon_HeartScale, gItemIconPalette_HeartScale},
    // ????????
    [ITEM_070]            = {gItemIcon_QuestionMark, gItemIconPalette_QuestionMark},
    [ITEM_071]            = {gItemIcon_QuestionMark, gItemIconPalette_QuestionMark},
    [ITEM_072]            = {gItemIcon_QuestionMark, gItemIconPalette_QuestionMark},
    [ITEM_073]            = {gItemIcon_QuestionMark, gItemIconPalette_QuestionMark},
    [ITEM_074]            = {gItemIcon_QuestionMark, gItemIconPalette_QuestionMark},
    [ITEM_075]            = {gItemIcon_QuestionMark, gItemIconPalette_QuestionMark},
    [ITEM_076]            = {gItemIcon_QuestionMark, gItemIconPalette_QuestionMark},
    [ITEM_077]            = {gItemIcon_QuestionMark, gItemIconPalette_QuestionMark},
    [ITEM_078]            = {gItemIcon_QuestionMark, gItemIconPalette_QuestionMark},
    // Mail
    [ITEM_ORANGE_MAIL]    = {gItemIcon_OrangeMail, gItemIconPalette_OrangeMail},
    [ITEM_HARBOR_MAIL]    = {gItemIcon_HarborMail, gItemIconPalette_HarborMail},
    [ITEM_GLITTER_MAIL]   = {gItemIcon_GlitterMail, gItemIconPalette_GlitterMail},
    [ITEM_MECH_MAIL]      = {gItemIcon_MechMail, gItemIconPalette_MechMail},
    [ITEM_WOOD_MAIL]      = {gItemIcon_WoodMail, gItemIconPalette_WoodMail},
    [ITEM_WAVE_MAIL]      = {gItemIcon_WaveMail, gItemIconPalette_WaveMail},
    [ITEM_BEAD_MAIL]      = {gItemIcon_BeadMail, gItemIconPalette_BeadMail},
    [ITEM_SHADOW_MAIL]    = {gItemIcon_ShadowMail, gItemIconPalette_ShadowMail},
    [ITEM_TROPIC_MAIL]    = {gItemIcon_TropicMail, gItemIconPalette_TropicMail},
    [ITEM_DREAM_MAIL]     = {gItemIcon_DreamMail, gItemIconPalette_DreamMail},
    [ITEM_FAB_MAIL]       = {gItemIcon_FabMail, gItemIconPalette_FabMail},
    [ITEM_RETRO_MAIL]     = {gItemIcon_RetroMail, gItemIconPalette_RetroMail},
    // Berries
    [ITEM_CHERI_BERRY]    = {gItemIcon_CheriBerry, gItemIconPalette_CheriBerry},
    [ITEM_CHESTO_BERRY]   = {gItemIcon_ChestoBerry, gItemIconPalette_ChestoBerry},
    [ITEM_PECHA_BERRY]    = {gItemIcon_PechaBerry, gItemIconPalette_PechaBerry},
    [ITEM_RAWST_BERRY]    = {gItemIcon_RawstBerry, gItemIconPalette_RawstBerry},
    [ITEM_ASPEAR_BERRY]   = {gItemIcon_AspearBerry, gItemIconPalette_AspearBerry},
    [ITEM_LEPPA_BERRY]    = {gItemIcon_LeppaBerry, gItemIconPalette_LeppaBerry},
    [ITEM_ORAN_BERRY]     = {gItemIcon_OranBerry, gItemIconPalette_OranBerry},
    [ITEM_PERSIM_BERRY]   = {gItemIcon_PersimBerry, gItemIconPalette_PersimBerry},
    [ITEM_LUM_BERRY]      = {gItemIcon_LumBerry, gItemIconPalette_LumBerry},
    [ITEM_SITRUS_BERRY]   = {gItemIcon_SitrusBerry, gItemIconPalette_SitrusBerry},
    [ITEM_FIGY_BERRY]     = {gItemIcon_FigyBerry, gItemIconPalette_FigyBerry},
    [ITEM_WIKI_BERRY]     = {gItemIcon_WikiBerry, gItemIconPalette_WikiBerry},
    [ITEM_MAGO_BERRY]     = {gItemIcon_MagoBerry, gItemIconPalette_MagoBerry},
    [ITEM_AGUAV_BERRY]    = {gItemIcon_AguavBerry, gItemIconPalette_AguavBerry},
    [ITEM_IAPAPA_BERRY]   = {gItemIcon_IapapaBerry, gItemIconPalette_IapapaBerry},
    [ITEM_RAZZ_BERRY]     = {gItemIcon_RazzBerry, gItemIconPalette_RazzBerry},
    [ITEM_BLUK_BERRY]     = {gItemIcon_BlukBerry, gItemIconPalette_BlukBerry},
    [ITEM_NANAB_BERRY]    = {gItemIcon_NanabBerry, gItemIconPalette_NanabBerry},
    [ITEM_WEPEAR_BERRY]   = {gItemIcon_WepearBerry, gItemIconPalette_WepearBerry},
    [ITEM_PINAP_BERRY]    = {gItemIcon_PinapBerry, gItemIconPalette_PinapBerry},
    [ITEM_POMEG_BERRY]    = {gItemIcon_PomegBerry, gItemIconPalette_PomegBerry},
    [ITEM_KELPSY_BERRY]   = {gItemIcon_KelpsyBerry, gItemIconPalette_KelpsyBerry},
    [ITEM_QUALOT_BERRY]   = {gItemIcon_QualotBerry, gItemIconPalette_QualotBerry},
    [ITEM_HONDEW_BERRY]   = {gItemIcon_HondewBerry, gItemIconPalette_HondewBerry},
    [ITEM_GREPA_BERRY]    = {gItemIcon_GrepaBerry, gItemIconPalette_GrepaBerry},
    [ITEM_TAMATO_BERRY]   = {gItemIcon_TamatoBerry, gItemIconPalette_TamatoBerry},
    [ITEM_CORNN_BERRY]    = {gItemIcon_CornnBerry, gItemIconPalette_CornnBerry},
    [ITEM_MAGOST_BERRY]   = {gItemIcon_MagostBerry, gItemIconPalette_MagostBerry},
    [ITEM_RABUTA_BERRY]   = {gItemIcon_RabutaBerry, gItemIconPalette_RabutaBerry},
    [ITEM_NOMEL_BERRY]    = {gItemIcon_NomelBerry, gItemIconPalette_NomelBerry},
    [ITEM_SPELON_BERRY]   = {gItemIcon_SpelonBerry, gItemIconPalette_SpelonBerry},
    [ITEM_PAMTRE_BERRY]   = {gItemIcon_PamtreBerry, gItemIconPalette_PamtreBerry},
    [ITEM_WATMEL_BERRY]   = {gItemIcon_WatmelBerry, gItemIconPalette_WatmelBerry},
    [ITEM_DURIN_BERRY]    = {gItemIcon_DurinBerry, gItemIconPalette_DurinBerry},
    [ITEM_BELUE_BERRY]    = {gItemIcon_BelueBerry, gItemIconPalette_BelueBerry},
    [ITEM_LIECHI_BERRY]   = {gItemIcon_LiechiBerry, gItemIconPalette_LiechiBerry},
    [ITEM_GANLON_BERRY]   = {gItemIcon_GanlonBerry, gItemIconPalette_GanlonBerry},
    [ITEM_SALAC_BERRY]    = {gItemIcon_SalacBerry, gItemIconPalette_SalacBerry},
    [ITEM_PETAYA_BERRY]   = {gItemIcon_PetayaBerry, gItemIconPalette_PetayaBerry},
    [ITEM_APICOT_BERRY]   = {gItemIcon_ApicotBerry, gItemIconPalette_ApicotBerry},
    [ITEM_LANSAT_BERRY]   = {gItemIcon_LansatBerry, gItemIconPalette_LansatBerry},
    [ITEM_STARF_BERRY]    = {gItemIcon_StarfBerry, gItemIconPalette_StarfBerry},
    [ITEM_ENIGMA_BERRY]   = {gItemIcon_EnigmaBerry, gItemIconPalette_EnigmaBerry},
    [ITEM_UNUSED_BERRY_1] = {gItemIcon_QuestionMark, gItemIconPalette_QuestionMark},
    [ITEM_UNUSED_BERRY_2] = {gItemIcon_QuestionMark, gItemIconPalette_QuestionMark},
    [ITEM_UNUSED_BERRY_3] = {gItemIcon_QuestionMark, gItemIconPalette_QuestionMark},
    // Hold items
    [ITEM_BRIGHT_POWDER]  = {gItemIcon_BrightPowder, gItemIconPalette_BrightPowder},
    [ITEM_WHITE_HERB]     = {gItemIcon_InBattleHerb, gItemIconPalette_WhiteHerb},
    [ITEM_MACHO_BRACE]    = {gItemIcon_MachoBrace, gItemIconPalette_MachoBrace},
    [ITEM_EXP_SHARE]      = {gItemIcon_ExpShare, gItemIconPalette_ExpShare},
    [ITEM_QUICK_CLAW]     = {gItemIcon_QuickClaw, gItemIconPalette_QuickClaw},
    [ITEM_SOOTHE_BELL]    = {gItemIcon_SootheBell, gItemIconPalette_SootheBell},
    [ITEM_MENTAL_HERB]    = {gItemIcon_InBattleHerb, gItemIconPalette_MentalHerb},
    [ITEM_CHOICE_BAND]    = {gItemIcon_ChoiceBand, gItemIconPalette_ChoiceBand},
    [ITEM_KINGS_ROCK]     = {gItemIcon_KingsRock, gItemIconPalette_KingsRock},
    [ITEM_SILVER_POWDER]  = {gItemIcon_SilverPowder, gItemIconPalette_SilverPowder},
    [ITEM_AMULET_COIN]    = {gItemIcon_AmuletCoin, gItemIconPalette_AmuletCoin},
    [ITEM_CLEANSE_TAG]    = {gItemIcon_CleanseTag, gItemIconPalette_CleanseTag},
    [ITEM_SOUL_DEW]       = {gItemIcon_SoulDew, gItemIconPalette_SoulDew},
    [ITEM_DEEP_SEA_TOOTH] = {gItemIcon_DeepSeaTooth, gItemIconPalette_DeepSeaTooth},
    [ITEM_DEEP_SEA_SCALE] = {gItemIcon_DeepSeaScale, gItemIconPalette_DeepSeaScale},
    [ITEM_SMOKE_BALL]     = {gItemIcon_SmokeBall, gItemIconPalette_SmokeBall},
    [ITEM_EVERSTONE]      = {gItemIcon_Everstone, gItemIconPalette_Everstone},
    [ITEM_FOCUS_BAND]     = {gItemIcon_FocusBand, gItemIconPalette_FocusBand},
    [ITEM_LUCKY_EGG]      = {gItemIcon_LuckyEgg, gItemIconPalette_LuckyEgg},
    [ITEM_SCOPE_LENS]     = {gItemIcon_ScopeLens, gItemIconPalette_ScopeLens},
    [ITEM_METAL_COAT]     = {gItemIcon_MetalCoat, gItemIconPalette_MetalCoat},
    [ITEM_LEFTOVERS]      = {gItemIcon_Leftovers, gItemIconPalette_Leftovers},
    [ITEM_DRAGON_SCALE]   = {gItemIcon_DragonScale, gItemIconPalette_DragonScale},
    [ITEM_LIGHT_BALL]     = {gItemIcon_LightBall, gItemIconPalette_LightBall},
    [ITEM_SOFT_SAND]      = {gItemIcon_SoftSand, gItemIconPalette_SoftSand},
    [ITEM_HARD_STONE]     = {gItemIcon_HardStone, gItemIconPalette_HardStone},
    [ITEM_MIRACLE_SEED]   = {gItemIcon_MiracleSeed, gItemIconPalette_MiracleSeed},
    [ITEM_BLACK_GLASSES]  = {gItemIcon_BlackGlasses, gItemIconPalette_BlackTypeEnhancingItem},
    [ITEM_BLACK_BELT]     = {gItemIcon_BlackBelt, gItemIconPalette_BlackTypeEnhancingItem},
    [ITEM_MAGNET]         = {gItemIcon_Magnet, gItemIconPalette_Magnet},
    [ITEM_MYSTIC_WATER]   = {gItemIcon_MysticWater, gItemIconPalette_MysticWater},
    [ITEM_SHARP_BEAK]     = {gItemIcon_SharpBeak, gItemIconPalette_SharpBeak},
    [ITEM_POISON_BARB]    = {gItemIcon_PoisonBarb, gItemIconPalette_PoisonBarb},
    [ITEM_NEVER_MELT_ICE] = {gItemIcon_NeverMeltIce, gItemIconPalette_NeverMeltIce},
    [ITEM_SPELL_TAG]      = {gItemIcon_SpellTag, gItemIconPalette_SpellTag},
    [ITEM_TWISTED_SPOON]  = {gItemIcon_TwistedSpoon, gItemIconPalette_TwistedSpoon},
    [ITEM_CHARCOAL]       = {gItemIcon_Charcoal, gItemIconPalette_Charcoal},
    [ITEM_DRAGON_FANG]    = {gItemIcon_DragonFang, gItemIconPalette_DragonFang},
    [ITEM_SILK_SCARF]     = {gItemIcon_SilkScarf, gItemIconPalette_SilkScarf},
    [ITEM_UP_GRADE]       = {gItemIcon_UpGrade, gItemIconPalette_UpGrade},
    [ITEM_SHELL_BELL]     = {gItemIcon_ShellBell, gItemIconPalette_Shell},
    [ITEM_SEA_INCENSE]    = {gItemIcon_SeaIncense, gItemIconPalette_SeaIncense},
    [ITEM_LAX_INCENSE]    = {gItemIcon_LaxIncense, gItemIconPalette_LaxIncense},
    [ITEM_LUCKY_PUNCH]    = {gItemIcon_LuckyPunch, gItemIconPalette_LuckyPunch},
    [ITEM_METAL_POWDER]   = {gItemIcon_MetalPowder, gItemIconPalette_MetalPowder},
    [ITEM_THICK_CLUB]     = {gItemIcon_ThickClub, gItemIconPalette_ThickClub},
    [ITEM_STICK]          = {gItemIcon_Stick, gItemIconPalette_Stick},
    // ????????
    [ITEM_0E2]            = {gItemIcon_QuestionMark, gItemIconPalette_QuestionMark},
    [ITEM_0E3]            = {gItemIcon_QuestionMark, gItemIconPalette_QuestionMark},
    [ITEM_0E4]            = {gItemIcon_QuestionMark, gItemIconPalette_QuestionMark},
    [ITEM_0E5]            = {gItemIcon_QuestionMark, gItemIconPalette_QuestionMark},
    [ITEM_0E6]            = {gItemIcon_QuestionMark, gItemIconPalette_QuestionMark},
    [ITEM_0E7]            = {gItemIcon_QuestionMark, gItemIconPalette_QuestionMark},
    [ITEM_0E8]            = {gItemIcon_QuestionMark, gItemIconPalette_QuestionMark},
    [ITEM_0E9]            = {gItemIcon_QuestionMark, gItemIconPalette_QuestionMark},
    [ITEM_0EA]            = {gItemIcon_QuestionMark, gItemIconPalette_QuestionMark},
    [ITEM_0EB]            = {gItemIcon_QuestionMark, gItemIconPalette_QuestionMark},
    [ITEM_0EC]            = {gItemIcon_QuestionMark, gItemIconPalette_QuestionMark},
    [ITEM_0ED]            = {gItemIcon_QuestionMark, gItemIconPalette_QuestionMark},
    [ITEM_0EE]            = {gItemIcon_QuestionMark, gItemIconPalette_QuestionMark},
    [ITEM_0EF]            = {gItemIcon_QuestionMark, gItemIconPalette_QuestionMark},
    [ITEM_0F0]            = {gItemIcon_QuestionMark, gItemIconPalette_QuestionMark},
    [ITEM_0F1]            = {gItemIcon_QuestionMark, gItemIconPalette_QuestionMark},
    [ITEM_0F2]            = {gItemIcon_QuestionMark, gItemIconPalette_QuestionMark},
    [ITEM_0F3]            = {gItemIcon_QuestionMark, gItemIconPalette_QuestionMark},
    [ITEM_0F4]            = {gItemIcon_QuestionMark, gItemIconPalette_QuestionMark},
    [ITEM_0F5]            = {gItemIcon_QuestionMark, gItemIconPalette_QuestionMark},
    [ITEM_0F6]            = {gItemIcon_QuestionMark, gItemIconPalette_QuestionMark},
    [ITEM_0F7]            = {gItemIcon_QuestionMark, gItemIconPalette_QuestionMark},
    [ITEM_0F8]            = {gItemIcon_QuestionMark, gItemIconPalette_QuestionMark},
    [ITEM_0F9]            = {gItemIcon_QuestionMark, gItemIconPalette_QuestionMark},
    [ITEM_0FA]            = {gItemIcon_QuestionMark, gItemIconPalette_QuestionMark},
    [ITEM_0FB]            = {gItemIcon_QuestionMark, gItemIconPalette_QuestionMark},
    [ITEM_0FC]            = {gItemIcon_QuestionMark, gItemIconPalette_QuestionMark},
    [ITEM_0FD]            = {gItemIcon_QuestionMark, gItemIconPalette_QuestionMark},
    // Contest hold items
    [ITEM_RED_SCARF]      = {gItemIcon_Scarf, gItemIconPalette_RedScarf},
    [ITEM_BLUE_SCARF]     = {gItemIcon_Scarf, gItemIconPalette_BlueScarf},
    [ITEM_PINK_SCARF]     = {gItemIcon_Scarf, gItemIconPalette_PinkScarf},
    [ITEM_GREEN_SCARF]    = {gItemIcon_Scarf, gItemIconPalette_GreenScarf},
    [ITEM_YELLOW_SCARF]   = {gItemIcon_Scarf, gItemIconPalette_YellowScarf},
    // Key items
    [ITEM_MACH_BIKE]      = {gItemIcon_MachBike, gItemIconPalette_MachBike},
    [ITEM_COIN_CASE]      = {gItemIcon_CoinCase, gItemIconPalette_CoinCase},
    [ITEM_ITEMFINDER]     = {gItemIcon_Itemfinder, gItemIconPalette_Itemfinder},
    [ITEM_OLD_ROD]        = {gItemIcon_OldRod, gItemIconPalette_OldRod},
    [ITEM_GOOD_ROD]       = {gItemIcon_GoodRod, gItemIconPalette_GoodRod},
    [ITEM_SUPER_ROD]      = {gItemIcon_SuperRod, gItemIconPalette_SuperRod},
    [ITEM_SS_TICKET]      = {gItemIcon_SSTicket, gItemIconPalette_SSTicket},
    [ITEM_CONTEST_PASS]   = {gItemIcon_ContestPass, gItemIconPalette_ContestPass},
    [ITEM_10B]            = {gItemIcon_QuestionMark, gItemIconPalette_QuestionMark},
    [ITEM_WAILMER_PAIL]   = {gItemIcon_WailmerPail, gItemIconPalette_WailmerPail},
    [ITEM_DEVON_GOODS]    = {gItemIcon_DevonGoods, gItemIconPalette_DevonGoods},
    [ITEM_SOOT_SACK]      = {gItemIcon_SootSack, gItemIconPalette_SootSack},
    [ITEM_BASEMENT_KEY]   = {gItemIcon_BasementKey, gItemIconPalette_OldKey},
    [ITEM_ACRO_BIKE]      = {gItemIcon_AcroBike, gItemIconPalette_AcroBike},
    [ITEM_POKEBLOCK_CASE] = {gItemIcon_PokeblockCase, gItemIconPalette_PokeblockCase},
    [ITEM_LETTER]         = {gItemIcon_Letter, gItemIconPalette_LavaCookieAndLetter},
    [ITEM_EON_TICKET]     = {gItemIcon_EonTicket, gItemIconPalette_EonTicket},
    [ITEM_RED_ORB]        = {gItemIcon_Orb, gItemIconPalette_RedOrb},
    [ITEM_BLUE_ORB]       = {gItemIcon_Orb, gItemIconPalette_BlueOrb},
    [ITEM_SCANNER]        = {gItemIcon_Scanner, gItemIconPalette_Scanner},
    [ITEM_GO_GOGGLES]     = {gItemIcon_GoGoggles, gItemIconPalette_GoGoggles},
    [ITEM_METEORITE]      = {gItemIcon_Meteorite, gItemIconPalette_Meteorite},
    [ITEM_ROOM_1_KEY]     = {gItemIcon_Room1Key, gItemIconPalette_Key},
    [ITEM_ROOM_2_KEY]     = {gItemIcon_Room2Key, gItemIconPalette_Key},
    [ITEM_ROOM_4_KEY]     = {gItemIcon_Room4Key, gItemIconPalette_Key},
    [ITEM_ROOM_6_KEY]     = {gItemIcon_Room6Key, gItemIconPalette_Key},
    [ITEM_STORAGE_KEY]    = {gItemIcon_StorageKey, gItemIconPalette_OldKey},
    [ITEM_ROOT_FOSSIL]    = {gItemIcon_RootFossil, gItemIconPalette_HoennFossil},
    [ITEM_CLAW_FOSSIL]    = {gItemIcon_ClawFossil, gItemIconPalette_HoennFossil},
    [ITEM_DEVON_SCOPE]    = {gItemIcon_DevonScope, gItemIconPalette_DevonScope},
    // TMs / HMs
    [ITEM_TM01]           = {gItemIcon_TMHM, gItemIconPalette_FightingTMHM},
    [ITEM_TM02]           = {gItemIcon_TMHM, gItemIconPalette_DragonTMHM},
    [ITEM_TM03]           = {gItemIcon_TMHM, gItemIconPalette_WaterTMHM},
    [ITEM_TM04]           = {gItemIcon_TMHM, gItemIconPalette_PsychicTMHM},
    [ITEM_TM05]           = {gItemIcon_TMHM, gItemIconPalette_NormalTMHM},
    [ITEM_TM06]           = {gItemIcon_TMHM, gItemIconPalette_PoisonTMHM},
    [ITEM_TM07]           = {gItemIcon_TMHM, gItemIconPalette_IceTMHM},
    [ITEM_TM08]           = {gItemIcon_TMHM, gItemIconPalette_FightingTMHM},
    [ITEM_TM09]           = {gItemIcon_TMHM, gItemIconPalette_GrassTMHM},
    [ITEM_TM10]           = {gItemIcon_TMHM, gItemIconPalette_NormalTMHM},
    [ITEM_TM11]           = {gItemIcon_TMHM, gItemIconPalette_FireTMHM},
    [ITEM_TM12]           = {gItemIcon_TMHM, gItemIconPalette_DarkTMHM},
    [ITEM_TM13]           = {gItemIcon_TMHM, gItemIconPalette_IceTMHM},
    [ITEM_TM14]           = {gItemIcon_TMHM, gItemIconPalette_IceTMHM},
    [ITEM_TM15]           = {gItemIcon_TMHM, gItemIconPalette_NormalTMHM},
    [ITEM_TM16]           = {gItemIcon_TMHM, gItemIconPalette_PsychicTMHM},
    [ITEM_TM17]           = {gItemIcon_TMHM, gItemIconPalette_NormalTMHM},
    [ITEM_TM18]           = {gItemIcon_TMHM, gItemIconPalette_WaterTMHM},
    [ITEM_TM19]           = {gItemIcon_TMHM, gItemIconPalette_GrassTMHM},
    [ITEM_TM20]           = {gItemIcon_TMHM, gItemIconPalette_NormalTMHM},
    [ITEM_TM21]           = {gItemIcon_TMHM, gItemIconPalette_NormalTMHM},
    [ITEM_TM22]           = {gItemIcon_TMHM, gItemIconPalette_GrassTMHM},
    [ITEM_TM23]           = {gItemIcon_TMHM, gItemIconPalette_SteelTMHM},
    [ITEM_TM24]           = {gItemIcon_TMHM, gItemIconPalette_ElectricTMHM},
    [ITEM_TM25]           = {gItemIcon_TMHM, gItemIconPalette_ElectricTMHM},
    [ITEM_TM26]           = {gItemIcon_TMHM, gItemIconPalette_GroundTMHM},
    [ITEM_TM27]           = {gItemIcon_TMHM, gItemIconPalette_NormalTMHM},
    [ITEM_TM28]           = {gItemIcon_TMHM, gItemIconPalette_GroundTMHM},
    [ITEM_TM29]           = {gItemIcon_TMHM, gItemIconPalette_PsychicTMHM},
    [ITEM_TM30]           = {gItemIcon_TMHM, gItemIconPalette_GhostTMHM},
    [ITEM_TM31]           = {gItemIcon_TMHM, gItemIconPalette_FightingTMHM},
    [ITEM_TM32]           = {gItemIcon_TMHM, gItemIconPalette_NormalTMHM},
    [ITEM_TM33]           = {gItemIcon_TMHM, gItemIconPalette_PsychicTMHM},
    [ITEM_TM34]           = {gItemIcon_TMHM, gItemIconPalette_ElectricTMHM},
    [ITEM_TM35]           = {gItemIcon_TMHM, gItemIconPalette_FireTMHM},
    [ITEM_TM36]           = {gItemIcon_TMHM, gItemIconPalette_PoisonTMHM},
    [ITEM_TM37]           = {gItemIcon_TMHM, gItemIconPalette_RockTMHM},
    [ITEM_TM38]           = {gItemIcon_TMHM, gItemIconPalette_FireTMHM},
    [ITEM_TM39]           = {gItemIcon_TMHM, gItemIconPalette_RockTMHM},
    [ITEM_TM40]           = {gItemIcon_TMHM, gItemIconPalette_FlyingTMHM},
    [ITEM_TM41]           = {gItemIcon_TMHM, gItemIconPalette_DarkTMHM},
    [ITEM_TM42]           = {gItemIcon_TMHM, gItemIconPalette_NormalTMHM},
    [ITEM_TM43]           = {gItemIcon_TMHM, gItemIconPalette_NormalTMHM},
    [ITEM_TM44]           = {gItemIcon_TMHM, gItemIconPalette_PsychicTMHM},
    [ITEM_TM45]           = {gItemIcon_TMHM, gItemIconPalette_NormalTMHM},
    [ITEM_TM46]           = {gItemIcon_TMHM, gItemIconPalette_DarkTMHM},
    [ITEM_TM47]           = {gItemIcon_TMHM, gItemIconPalette_SteelTMHM},
    [ITEM_TM48]           = {gItemIcon_TMHM, gItemIconPalette_PsychicTMHM},
    [ITEM_TM49]           = {gItemIcon_TMHM, gItemIconPalette_DarkTMHM},
    [ITEM_TM50]           = {gItemIcon_TMHM, gItemIconPalette_FireTMHM},
    [ITEM_HM01]           = {gItemIcon_TMHM, gItemIconPalette_NormalTMHM},
    [ITEM_HM02]           = {gItemIcon_TMHM, gItemIconPalette_FlyingTMHM},
    [ITEM_HM03]           = {gItemIcon_TMHM, gItemIconPalette_WaterTMHM},
    [ITEM_HM04]           = {gItemIcon_TMHM, gItemIconPalette_NormalTMHM},
    [ITEM_HM05]           = {gItemIcon_TMHM, gItemIconPalette_NormalTMHM},
    [ITEM_HM06]           = {gItemIcon_TMHM, gItemIconPalette_FightingTMHM},
    [ITEM_HM07]           = {gItemIcon_TMHM, gItemIconPalette_WaterTMHM},
    [ITEM_HM08]           = {gItemIcon_TMHM, gItemIconPalette_WaterTMHM},
    // ????????
    [ITEM_15B]            = {gItemIcon_QuestionMark, gItemIconPalette_QuestionMark},
    [ITEM_15C]            = {gItemIcon_QuestionMark, gItemIconPalette_QuestionMark},
    // FireRed/LeafGreen key items
    [ITEM_OAKS_PARCEL]    = {gItemIcon_OaksParcel, gItemIconPalette_OaksParcel},
    [ITEM_POKE_FLUTE]     = {gItemIcon_PokeFlute, gItemIconPalette_PokeFlute},
    [ITEM_SECRET_KEY]     = {gItemIcon_SecretKey, gItemIconPalette_SecretKey},
    [ITEM_BIKE_VOUCHER]   = {gItemIcon_BikeVoucher, gItemIconPalette_BikeVoucher},
    [ITEM_GOLD_TEETH]     = {gItemIcon_GoldTeeth, gItemIconPalette_GoldTeeth},
    [ITEM_OLD_AMBER]      = {gItemIcon_OldAmber, gItemIconPalette_OldAmber},
    [ITEM_CARD_KEY]       = {gItemIcon_CardKey, gItemIconPalette_CardKey},
    [ITEM_LIFT_KEY]       = {gItemIcon_LiftKey, gItemIconPalette_Key},
    [ITEM_HELIX_FOSSIL]   = {gItemIcon_HelixFossil, gItemIconPalette_KantoFossil},
    [ITEM_DOME_FOSSIL]    = {gItemIcon_DomeFossil, gItemIconPalette_KantoFossil},
    [ITEM_SILPH_SCOPE]    = {gItemIcon_SilphScope, gItemIconPalette_SilphScope},
    [ITEM_BICYCLE]        = {gItemIcon_Bicycle, gItemIconPalette_Bicycle},
    [ITEM_TOWN_MAP]       = {gItemIcon_TownMap, gItemIconPalette_TownMap},
    [ITEM_VS_SEEKER]      = {gItemIcon_VSSeeker, gItemIconPalette_VSSeeker},
    [ITEM_FAME_CHECKER]   = {gItemIcon_FameChecker, gItemIconPalette_FameChecker},
    [ITEM_TM_CASE]        = {gItemIcon_TMCase, gItemIconPalette_TMCase},
    [ITEM_BERRY_POUCH]    = {gItemIcon_BerryPouch, gItemIconPalette_BerryPouch},
    [ITEM_TEACHY_TV]      = {gItemIcon_TeachyTV, gItemIconPalette_TeachyTV},
    [ITEM_TRI_PASS]       = {gItemIcon_TriPass, gItemIconPalette_TriPass},
    [ITEM_RAINBOW_PASS]   = {gItemIcon_RainbowPass, gItemIconPalette_RainbowPass},
    [ITEM_TEA]            = {gItemIcon_Tea, gItemIconPalette_Tea},
    [ITEM_MYSTIC_TICKET]  = {gItemIcon_MysticTicket, gItemIconPalette_MysticTicket},
    [ITEM_AURORA_TICKET]  = {gItemIcon_AuroraTicket, gItemIconPalette_AuroraTicket},
    [ITEM_POWDER_JAR]     = {gItemIcon_PowderJar, gItemIconPalette_PowderJar},
    [ITEM_RUBY]           = {gItemIcon_Gem, gItemIconPalette_Ruby},
    [ITEM_SAPPHIRE]       = {gItemIcon_Gem, gItemIconPalette_Sapphire},
    // Return to field arrow
    [ITEMS_COUNT]         = {gItemIcon_ReturnToFieldArrow, gItemIconPalette_ReturnToFieldArrow},
};
// ===== END src/data/item_icon_table.h =====

void ResetItemMenuIconState(void)
{
    u16 i;

    for (i = 0; i < SPR_COUNT; i++)
        sItemMenuIconSpriteIds[i] = SPRITE_NONE;
}

void CreateBagSprite(u8 animNum)
{
    sItemMenuIconSpriteIds[SPR_BAG] = CreateSprite(&sSpriteTemplate_Bag, 40, 68, 0);
    SetBagVisualPocketId(animNum);
}

void SetBagVisualPocketId(u8 animNum)
{
    struct Sprite *sprite = &gSprites[sItemMenuIconSpriteIds[SPR_BAG]];
    sprite->y2 = -5;
    sprite->callback = SpriteCB_BagVisualSwitchingPockets;
    StartSpriteAnim(sprite, animNum);
}

static void SpriteCB_BagVisualSwitchingPockets(struct Sprite *sprite)
{
    if (sprite->y2 != 0)
        sprite->y2++;
    else
        sprite->callback = SpriteCallbackDummy;
}

void ShakeBagSprite(void)
{
    struct Sprite *sprite = &gSprites[sItemMenuIconSpriteIds[SPR_BAG]];
    if (sprite->affineAnimEnded)
    {
        StartSpriteAffineAnim(sprite, AFFINEANIM_BAG_SHAKE);
        sprite->callback = SpriteCB_ShakeBagSprite;
    }
}

static void SpriteCB_ShakeBagSprite(struct Sprite *sprite)
{
    if (sprite->affineAnimEnded)
    {
        StartSpriteAffineAnim(sprite, AFFINEANIM_BAG_IDLE);
        sprite->callback = SpriteCallbackDummy;
    }
}

void CreateSwapLine(void)
{
    u8 i;
    u8 * spriteIds = &sItemMenuIconSpriteIds[SPR_SWAP_LINE_START];

    for (i = 0; i < NUM_SWAP_LINE_SPRITES; i++)
    {
        spriteIds[i] = CreateSprite(&sSpriteTemplate_SwapLine, i * 16 + 96, 7, 0);
        switch (i)
        {
        case 0:
            // ANIM_SWAP_LINE_START, by default
            break;
        case NUM_SWAP_LINE_SPRITES - 1:
            StartSpriteAnim(&gSprites[spriteIds[i]], ANIM_SWAP_LINE_END);
            break;
        default:
            StartSpriteAnim(&gSprites[spriteIds[i]], ANIM_SWAP_LINE_MID);
            break;
        }
        gSprites[spriteIds[i]].invisible = TRUE;
    }
}

void SetSwapLineInvisibility(bool8 invisible)
{
    u8 i;
    u8 * spriteIds = &sItemMenuIconSpriteIds[SPR_SWAP_LINE_START];

    for (i = 0; i < NUM_SWAP_LINE_SPRITES; i++)
        gSprites[spriteIds[i]].invisible = invisible;
}

void UpdateSwapLinePos(s16 x, u16 y)
{
    u8 i;
    u8 * spriteIds = &sItemMenuIconSpriteIds[SPR_SWAP_LINE_START];

    for (i = 0; i < NUM_SWAP_LINE_SPRITES; i++)
    {
        gSprites[spriteIds[i]].x2 = x;
        gSprites[spriteIds[i]].y = y + 7;
    }
}

static bool8 TryAllocItemIconTilesBuffers(void)
{
    void ** ptr1, ** ptr2;

    ptr1 = &sItemIconTilesBuffer;
    *ptr1 = Alloc(0x120);
    if (*ptr1 == NULL)
        return FALSE;
    ptr2 = &sItemIconTilesBufferPadded;
    *ptr2 = AllocZeroed(0x200);
    if (*ptr2 == NULL)
    {
        Free(*ptr1);
        return FALSE;
    }
    return TRUE;
}

void CopyItemIconPicTo4x4Buffer(const void *src, void *dest)
{
    u8 i;

    for (i = 0; i < 3; i++)
        CpuCopy16(src + 0x60 * i, dest + 0x80 * i, 0x60);
}

u8 AddItemIconObject(u16 tilesTag, u16 paletteTag, u16 itemId)
{
    struct SpriteTemplate template;
    struct SpriteSheet spriteSheet;
    struct CompressedSpritePalette spritePalette;
    u8 spriteId;

    if (!TryAllocItemIconTilesBuffers())
        return MAX_SPRITES;

    LZDecompressWram(GetItemIconGfxPtr(itemId, ITEMICON_TILES), sItemIconTilesBuffer);
    CopyItemIconPicTo4x4Buffer(sItemIconTilesBuffer, sItemIconTilesBufferPadded);
    spriteSheet.data = sItemIconTilesBufferPadded;
    spriteSheet.size = 0x200;
    spriteSheet.tag = tilesTag;
    LoadSpriteSheet(&spriteSheet);

    spritePalette.data = GetItemIconGfxPtr(itemId, ITEMICON_PAL);
    spritePalette.tag = paletteTag;
    LoadCompressedSpritePalette(&spritePalette);

    CpuCopy16(&sSpriteTemplate_ItemIcon, &template, sizeof(struct SpriteTemplate));
    template.tileTag = tilesTag;
    template.paletteTag = paletteTag;
    spriteId = CreateSprite(&template, 0, 0, 0);

    Free(sItemIconTilesBuffer);
    Free(sItemIconTilesBufferPadded);
    return spriteId;
}

u8 AddItemIconObjectWithCustomObjectTemplate(const struct SpriteTemplate * origTemplate, u16 tilesTag, u16 paletteTag, u16 itemId)
{
    struct SpriteTemplate template;
    struct SpriteSheet spriteSheet;
    struct CompressedSpritePalette spritePalette;
    u8 spriteId;

    if (!TryAllocItemIconTilesBuffers())
        return MAX_SPRITES;

    LZDecompressWram(GetItemIconGfxPtr(itemId, ITEMICON_TILES), sItemIconTilesBuffer);
    CopyItemIconPicTo4x4Buffer(sItemIconTilesBuffer, sItemIconTilesBufferPadded);
    spriteSheet.data = sItemIconTilesBufferPadded;
    spriteSheet.size = 0x200;
    spriteSheet.tag = tilesTag;
    LoadSpriteSheet(&spriteSheet);

    spritePalette.data = GetItemIconGfxPtr(itemId, ITEMICON_PAL);
    spritePalette.tag = paletteTag;
    LoadCompressedSpritePalette(&spritePalette);

    CpuCopy16(origTemplate, &template, sizeof(struct SpriteTemplate));
    template.tileTag = tilesTag;
    template.paletteTag = paletteTag;
    spriteId = CreateSprite(&template, 0, 0, 0);

    Free(sItemIconTilesBuffer);
    Free(sItemIconTilesBufferPadded);
    return spriteId;
}

void CreateItemMenuIcon(u16 itemId, u8 idx)
{
    u8 * spriteIds = &sItemMenuIconSpriteIds[SPR_ITEM_ICON];
    u8 spriteId;

    if (spriteIds[idx] == SPRITE_NONE)
    {
        // Either TAG_ITEM_ICON or TAG_ITEM_ICON_ALT
        FreeSpriteTilesByTag(TAG_ITEM_ICON + idx);
        FreeSpritePaletteByTag(TAG_ITEM_ICON + idx);
        spriteId = AddItemIconObject(TAG_ITEM_ICON + idx, TAG_ITEM_ICON + idx, itemId);
        if (spriteId != MAX_SPRITES)
        {
            spriteIds[idx] = spriteId;
            gSprites[spriteId].x2 = 24;
            gSprites[spriteId].y2 = 140;
        }
    }
}

void DestroyItemMenuIcon(u8 idx)
{
    u8 * spriteIds = &sItemMenuIconSpriteIds[SPR_ITEM_ICON];

    if (spriteIds[idx] != SPRITE_NONE)
    {
        DestroySpriteAndFreeResources(&gSprites[spriteIds[idx]]);
        spriteIds[idx] = SPRITE_NONE;
    }
}

// attrId is either ITEMICON_TILES or ITEMICON_PAL
const u32 *GetItemIconGfxPtr(u16 itemId, u8 attrId)
{
    if (itemId > ITEMS_COUNT)
        itemId = ITEM_NONE;
    return sItemIconTable[itemId][attrId];
}

void CreateBerryPouchItemIcon(u16 itemId, u8 idx)
{
    u8 * spriteIds = &sItemMenuIconSpriteIds[SPR_ITEM_ICON];
    u8 spriteId;

    if (spriteIds[idx] == SPRITE_NONE)
    {
        // Either TAG_ITEM_ICON or TAG_ITEM_ICON_ALT
        FreeSpriteTilesByTag(TAG_ITEM_ICON + idx);
        FreeSpritePaletteByTag(TAG_ITEM_ICON + idx);
        spriteId = AddItemIconObject(TAG_ITEM_ICON + idx, TAG_ITEM_ICON + idx, itemId);
        if (spriteId != MAX_SPRITES)
        {
            spriteIds[idx] = spriteId;
            gSprites[spriteId].x2 = 24;
            gSprites[spriteId].y2 = 147; // This value is the only difference from CreateItemMenuIcon
        }
    }
}
