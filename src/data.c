#include "global.h"
#include "gflib.h"
#include "battle.h"
#include "data.h"
#include "graphics.h"
#include "constants/items.h"
#include "constants/moves.h"
#include "constants/battle_ai.h"
#include "constants/trainers.h"

#define BATTLER_OFFSET(i) (gHeap + 0x8000 + MON_PIC_SIZE * (i))

const struct SpriteFrameImage gBattlerPicTable_PlayerLeft[] =
{
    BATTLER_OFFSET(0), MON_PIC_SIZE,
    BATTLER_OFFSET(1), MON_PIC_SIZE,
    BATTLER_OFFSET(2), MON_PIC_SIZE,
    BATTLER_OFFSET(3), MON_PIC_SIZE,
};

const struct SpriteFrameImage gBattlerPicTable_OpponentLeft[] =
{
    BATTLER_OFFSET(4), MON_PIC_SIZE,
    BATTLER_OFFSET(5), MON_PIC_SIZE,
    BATTLER_OFFSET(6), MON_PIC_SIZE,
    BATTLER_OFFSET(7), MON_PIC_SIZE,
};

const struct SpriteFrameImage gBattlerPicTable_PlayerRight[] =
{
    BATTLER_OFFSET(8),  MON_PIC_SIZE,
    BATTLER_OFFSET(9),  MON_PIC_SIZE,
    BATTLER_OFFSET(10), MON_PIC_SIZE,
    BATTLER_OFFSET(11), MON_PIC_SIZE,
};

const struct SpriteFrameImage gBattlerPicTable_OpponentRight[] =
{
    BATTLER_OFFSET(12), MON_PIC_SIZE,
    BATTLER_OFFSET(13), MON_PIC_SIZE,
    BATTLER_OFFSET(14), MON_PIC_SIZE,
    BATTLER_OFFSET(15), MON_PIC_SIZE,
};

const struct SpriteFrameImage gTrainerBackPicTable_Red[] =
{
    gTrainerBackPic_Red, 0x0800,
    gTrainerBackPic_Red + 0x0800, 0x0800,
    gTrainerBackPic_Red + 0x1000, 0x0800,
    gTrainerBackPic_Red + 0x1800, 0x0800,
    gTrainerBackPic_Red + 0x2000, 0x0800,
};

const struct SpriteFrameImage gTrainerBackPicTable_Leaf[] =
{
    gTrainerBackPic_Leaf, 0x0800,
    gTrainerBackPic_Leaf + 0x0800, 0x0800,
    gTrainerBackPic_Leaf + 0x1000, 0x0800,
    gTrainerBackPic_Leaf + 0x1800, 0x0800,
    gTrainerBackPic_Leaf + 0x2000, 0x0800,
};

const struct SpriteFrameImage gTrainerBackPicTable_Pokedude[] =
{
    gTrainerBackPic_Pokedude, 0x0800,
    gTrainerBackPic_Pokedude + 0x0800, 0x0800,
    gTrainerBackPic_Pokedude + 0x1000, 0x0800,
    gTrainerBackPic_Pokedude + 0x1800, 0x0800,
};

const struct SpriteFrameImage gTrainerBackPicTable_OldMan[] =
{
    gTrainerBackPic_OldMan, 0x0800,
    gTrainerBackPic_OldMan + 0x0800, 0x0800,
    gTrainerBackPic_OldMan + 0x1000, 0x0800,
    gTrainerBackPic_OldMan + 0x1800, 0x0800,
};

const struct SpriteFrameImage gTrainerBackPicTable_RSBrendan[] =
{
    gTrainerBackPic_RSBrendan, 0x0800,
    gTrainerBackPic_RSBrendan + 0x0800, 0x0800,
    gTrainerBackPic_RSBrendan + 0x1000, 0x0800,
    gTrainerBackPic_RSBrendan + 0x1800, 0x0800,
};

const struct SpriteFrameImage gTrainerBackPicTable_RSMay[] =
{
    gTrainerBackPic_RSMay, 0x0800,
    gTrainerBackPic_RSMay + 0x0800, 0x0800,
    gTrainerBackPic_RSMay + 0x1000, 0x0800,
    gTrainerBackPic_RSMay + 0x1800, 0x0800,
};

static const union AnimCmd sAnim_GeneralFrame0[] =
{
    ANIMCMD_FRAME(0, 0),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_GeneralFrame3[] =
{
    ANIMCMD_FRAME(3, 0),
    ANIMCMD_END,
};

// Many of these affine anims seem to go unused, and
// instead SetSpriteRotScale is used to manipulate
// the battler sprites directly (for instance, in AnimTask_SwitchOutShrinkMon).
// Those with explicit indexes are referenced elsewhere.

static const union AffineAnimCmd sAffineAnim_Battler_Normal[] =
{
    AFFINEANIMCMD_FRAME(0x100, 0x100, 0, 0),
    AFFINEANIMCMD_END,
};

static const union AffineAnimCmd sAffineAnim_Battler_Flipped[] =
{
    AFFINEANIMCMD_FRAME(-0x100, 0x0100, 0, 0),
    AFFINEANIMCMD_END,
};

static const union AffineAnimCmd sAffineAnim_Battler_Emerge[] =
{
    AFFINEANIMCMD_FRAME(0x28, 0x28, 0, 0),
    AFFINEANIMCMD_FRAME(0x12, 0x12, 0, 12),
    AFFINEANIMCMD_END,
};

static const union AffineAnimCmd sAffineAnim_Battler_Return[] =
{
    AFFINEANIMCMD_FRAME(-0x2, -0x2, 0, 18),
    AFFINEANIMCMD_FRAME(-0x10, -0x10, 0, 15),
    AFFINEANIMCMD_END,
};

static const union AffineAnimCmd sAffineAnim_Battler_HorizontalSquishLoop[] =
{
    AFFINEANIMCMD_FRAME(0xA0, 0x100, 0, 0),
    AFFINEANIMCMD_FRAME( 0x4,   0x0, 0, 8),
    AFFINEANIMCMD_FRAME(-0x4,   0x0, 0, 8),
    AFFINEANIMCMD_JUMP(1),
};

static const union AffineAnimCmd sAffineAnim_Battler_Grow[] =
{
    AFFINEANIMCMD_FRAME(0x2, 0x2, 0, 20),
    AFFINEANIMCMD_END,
};

static const union AffineAnimCmd sAffineAnim_Battler_Shrink[] =
{
    AFFINEANIMCMD_FRAME(-0x2, -0x2, 0, 20),
    AFFINEANIMCMD_END,
};

static const union AffineAnimCmd sAffineAnim_Battler_BigToSmall[] =
{
    AFFINEANIMCMD_FRAME(0x100, 0x100, 0, 0),
    AFFINEANIMCMD_FRAME(-0x10, -0x10, 0, 9),
    AFFINEANIMCMD_END,
};

static const union AffineAnimCmd sAffineAnim_Battler_GrowLarge[] =
{
    AFFINEANIMCMD_FRAME(0x4, 0x4, 0, 63),
    AFFINEANIMCMD_END,
};

static const union AffineAnimCmd sAffineAnim_Battler_TipRight[] =
{
    AFFINEANIMCMD_FRAME(0x0, 0x0, -3, 5),
    AFFINEANIMCMD_FRAME(0x0, 0x0,  3, 5),
    AFFINEANIMCMD_END,
};

const union AffineAnimCmd *const gAffineAnims_BattleSpritePlayerSide[] =
{
    [BATTLER_AFFINE_NORMAL] = sAffineAnim_Battler_Normal,
    [BATTLER_AFFINE_EMERGE] = sAffineAnim_Battler_Emerge,
    [BATTLER_AFFINE_RETURN] = sAffineAnim_Battler_Return,
    sAffineAnim_Battler_HorizontalSquishLoop,
    sAffineAnim_Battler_Grow,
    sAffineAnim_Battler_Shrink,
    sAffineAnim_Battler_GrowLarge,
    sAffineAnim_Battler_TipRight,
    sAffineAnim_Battler_BigToSmall,
};

static const union AffineAnimCmd sAffineAnim_Battler_SpinShrink[] =
{
    AFFINEANIMCMD_FRAME(-0x4, -0x4, 4, 63),
    AFFINEANIMCMD_END,
};

static const union AffineAnimCmd sAffineAnim_Battler_TipLeft[] =
{
    AFFINEANIMCMD_FRAME(0x0, 0x0,  3, 5),
    AFFINEANIMCMD_FRAME(0x0, 0x0, -3, 5),
    AFFINEANIMCMD_END,
};

static const union AffineAnimCmd sAffineAnim_Battler_RotateUpAndBack[] =
{
    AFFINEANIMCMD_FRAME(0x0, 0x0, -5, 20),
    AFFINEANIMCMD_FRAME(0x0, 0x0,  0, 20),
    AFFINEANIMCMD_FRAME(0x0, 0x0,  5, 20),
    AFFINEANIMCMD_END,
};

static const union AffineAnimCmd sAffineAnim_Battler_Spin[] =
{
    AFFINEANIMCMD_FRAME(0x0, 0x0, 9, 110),
    AFFINEANIMCMD_END,
};

const union AffineAnimCmd *const gAffineAnims_BattleSpriteOpponentSide[] =
{
    [BATTLER_AFFINE_NORMAL] = sAffineAnim_Battler_Normal,
    [BATTLER_AFFINE_EMERGE] = sAffineAnim_Battler_Emerge,
    [BATTLER_AFFINE_RETURN] = sAffineAnim_Battler_Return,
    sAffineAnim_Battler_HorizontalSquishLoop,
    sAffineAnim_Battler_Grow,
    sAffineAnim_Battler_Shrink,
    sAffineAnim_Battler_SpinShrink,
    sAffineAnim_Battler_TipLeft,
    sAffineAnim_Battler_RotateUpAndBack,
    sAffineAnim_Battler_BigToSmall,
    sAffineAnim_Battler_Spin,
};

const union AffineAnimCmd *const gAffineAnims_BattleSpriteContest[] =
{
    [BATTLER_AFFINE_NORMAL] = sAffineAnim_Battler_Flipped,
    [BATTLER_AFFINE_EMERGE] = sAffineAnim_Battler_Emerge,
    [BATTLER_AFFINE_RETURN] = sAffineAnim_Battler_Return,
    sAffineAnim_Battler_HorizontalSquishLoop,
    sAffineAnim_Battler_Grow,
    sAffineAnim_Battler_Shrink,
    sAffineAnim_Battler_SpinShrink,
    sAffineAnim_Battler_TipLeft,
    sAffineAnim_Battler_RotateUpAndBack,
    sAffineAnim_Battler_BigToSmall,
    sAffineAnim_Battler_Spin,
};

static const union AnimCmd sAnim_MonPic_0[] =
{
    ANIMCMD_FRAME(0, 0),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_MonPic_1[] =
{
    ANIMCMD_FRAME(1, 0),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_MonPic_2[] =
{
    ANIMCMD_FRAME(2, 0),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_MonPic_3[] =
{
    ANIMCMD_FRAME(3, 0),
    ANIMCMD_END,
};

const union AnimCmd *const gAnims_MonPic[] =
{
    sAnim_MonPic_0,
    sAnim_MonPic_1,
    sAnim_MonPic_2,
    sAnim_MonPic_3,
};

#define SPECIES_SPRITE(species, sprite) [SPECIES_##species] = {sprite, 0x800, SPECIES_##species}
#define SPECIES_PAL(species, pal) [SPECIES_##species] = {pal, SPECIES_##species}
#define SPECIES_SHINY_PAL(species, pal) [SPECIES_##species] = {pal, SPECIES_##species + SPECIES_SHINY_TAG}

#define TRAINER_SPRITE(trainerPic, sprite, size) [TRAINER_PIC_##trainerPic] = {sprite, size, TRAINER_PIC_##trainerPic}
#define TRAINER_PAL(trainerPic, pal) [TRAINER_PIC_##trainerPic] = {pal, TRAINER_PIC_##trainerPic}

// ===== BEGIN src/data/pokemon_graphics/front_pic_coordinates.h =====
const struct MonCoords gMonFrontPicCoords[] =
{
    [SPECIES_NONE] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 0,
    },
    [SPECIES_BULBASAUR] =
    {
        .size = MON_COORDS_SIZE(40, 40),
        .y_offset = 16,
    },
    [SPECIES_IVYSAUR] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 10,
    },
    [SPECIES_VENUSAUR] =
    {
        .size = MON_COORDS_SIZE(64, 56),
        .y_offset = 4,
    },
    [SPECIES_CHARMANDER] =
    {
        .size = MON_COORDS_SIZE(40, 40),
        .y_offset = 13,
    },
    [SPECIES_CHARMELEON] =
    {
        .size = MON_COORDS_SIZE(56, 48),
        .y_offset = 9,
    },
    [SPECIES_CHARIZARD] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 1,
    },
    [SPECIES_SQUIRTLE] =
    {
        .size = MON_COORDS_SIZE(48, 40),
        .y_offset = 12,
    },
    [SPECIES_WARTORTLE] =
    {
        .size = MON_COORDS_SIZE(56, 48),
        .y_offset = 9,
    },
    [SPECIES_BLASTOISE] =
    {
        .size = MON_COORDS_SIZE(64, 56),
        .y_offset = 5,
    },
    [SPECIES_CATERPIE] =
    {
        .size = MON_COORDS_SIZE(40, 32),
        .y_offset = 16,
    },
    [SPECIES_METAPOD] =
    {
        .size = MON_COORDS_SIZE(40, 32),
        .y_offset = 20,
    },
    [SPECIES_BUTTERFREE] =
    {
        .size = MON_COORDS_SIZE(56, 48),
        .y_offset = 9,
    },
    [SPECIES_WEEDLE] =
    {
        .size = MON_COORDS_SIZE(40, 32),
        .y_offset = 17,
    },
    [SPECIES_KAKUNA] =
    {
        .size = MON_COORDS_SIZE(32, 40),
        .y_offset = 14,
    },
    [SPECIES_BEEDRILL] =
    {
        .size = MON_COORDS_SIZE(64, 48),
        .y_offset = 9,
    },
    [SPECIES_PIDGEY] =
    {
        .size = MON_COORDS_SIZE(40, 40),
        .y_offset = 13,
    },
    [SPECIES_PIDGEOTTO] =
    {
        .size = MON_COORDS_SIZE(48, 56),
        .y_offset = 7,
    },
    [SPECIES_PIDGEOT] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 1,
    },
    [SPECIES_RATTATA] =
    {
        .size = MON_COORDS_SIZE(48, 40),
        .y_offset = 14,
    },
    [SPECIES_RATICATE] =
    {
        .size = MON_COORDS_SIZE(56, 48),
        .y_offset = 11,
    },
    [SPECIES_SPEAROW] =
    {
        .size = MON_COORDS_SIZE(40, 40),
        .y_offset = 12,
    },
    [SPECIES_FEAROW] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 0,
    },
    [SPECIES_EKANS] =
    {
        .size = MON_COORDS_SIZE(48, 40),
        .y_offset = 15,
    },
    [SPECIES_ARBOK] =
    {
        .size = MON_COORDS_SIZE(56, 64),
        .y_offset = 3,
    },
    [SPECIES_PIKACHU] =
    {
        .size = MON_COORDS_SIZE(48, 56),
        .y_offset = 9,
    },
    [SPECIES_RAICHU] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 0,
    },
    [SPECIES_SANDSHREW] =
    {
        .size = MON_COORDS_SIZE(40, 48),
        .y_offset = 11,
    },
    [SPECIES_SANDSLASH] =
    {
        .size = MON_COORDS_SIZE(56, 56),
        .y_offset = 6,
    },
    [SPECIES_NIDORAN_F] =
    {
        .size = MON_COORDS_SIZE(40, 32),
        .y_offset = 16,
    },
    [SPECIES_NIDORINA] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 11,
    },
    [SPECIES_NIDOQUEEN] =
    {
        .size = MON_COORDS_SIZE(56, 64),
        .y_offset = 2,
    },
    [SPECIES_NIDORAN_M] =
    {
        .size = MON_COORDS_SIZE(40, 40),
        .y_offset = 12,
    },
    [SPECIES_NIDORINO] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 8,
    },
    [SPECIES_NIDOKING] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 2,
    },
    [SPECIES_CLEFAIRY] =
    {
        .size = MON_COORDS_SIZE(40, 40),
        .y_offset = 16,
    },
    [SPECIES_CLEFABLE] =
    {
        .size = MON_COORDS_SIZE(48, 56),
        .y_offset = 7,
    },
    [SPECIES_VULPIX] =
    {
        .size = MON_COORDS_SIZE(48, 40),
        .y_offset = 12,
    },
    [SPECIES_NINETALES] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 3,
    },
    [SPECIES_JIGGLYPUFF] =
    {
        .size = MON_COORDS_SIZE(40, 40),
        .y_offset = 16,
    },
    [SPECIES_WIGGLYTUFF] =
    {
        .size = MON_COORDS_SIZE(48, 56),
        .y_offset = 8,
    },
    [SPECIES_ZUBAT] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 13,
    },
    [SPECIES_GOLBAT] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 1,
    },
    [SPECIES_ODDISH] =
    {
        .size = MON_COORDS_SIZE(32, 40),
        .y_offset = 12,
    },
    [SPECIES_GLOOM] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 8,
    },
    [SPECIES_VILEPLUME] =
    {
        .size = MON_COORDS_SIZE(56, 48),
        .y_offset = 10,
    },
    [SPECIES_PARAS] =
    {
        .size = MON_COORDS_SIZE(48, 32),
        .y_offset = 18,
    },
    [SPECIES_PARASECT] =
    {
        .size = MON_COORDS_SIZE(64, 48),
        .y_offset = 8,
    },
    [SPECIES_VENONAT] =
    {
        .size = MON_COORDS_SIZE(40, 56),
        .y_offset = 11,
    },
    [SPECIES_VENOMOTH] =
    {
        .size = MON_COORDS_SIZE(64, 56),
        .y_offset = 8,
    },
    [SPECIES_DIGLETT] =
    {
        .size = MON_COORDS_SIZE(40, 32),
        .y_offset = 17,
    },
    [SPECIES_DUGTRIO] =
    {
        .size = MON_COORDS_SIZE(56, 40),
        .y_offset = 12,
    },
    [SPECIES_MEOWTH] =
    {
        .size = MON_COORDS_SIZE(40, 40),
        .y_offset = 12,
    },
    [SPECIES_PERSIAN] =
    {
        .size = MON_COORDS_SIZE(56, 48),
        .y_offset = 10,
    },
    [SPECIES_PSYDUCK] =
    {
        .size = MON_COORDS_SIZE(40, 48),
        .y_offset = 9,
    },
    [SPECIES_GOLDUCK] =
    {
        .size = MON_COORDS_SIZE(56, 56),
        .y_offset = 6,
    },
    [SPECIES_MANKEY] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 14,
    },
    [SPECIES_PRIMEAPE] =
    {
        .size = MON_COORDS_SIZE(56, 56),
        .y_offset = 6,
    },
    [SPECIES_GROWLITHE] =
    {
        .size = MON_COORDS_SIZE(48, 40),
        .y_offset = 12,
    },
    [SPECIES_ARCANINE] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 2,
    },
    [SPECIES_POLIWAG] =
    {
        .size = MON_COORDS_SIZE(56, 32),
        .y_offset = 16,
    },
    [SPECIES_POLIWHIRL] =
    {
        .size = MON_COORDS_SIZE(56, 48),
        .y_offset = 11,
    },
    [SPECIES_POLIWRATH] =
    {
        .size = MON_COORDS_SIZE(56, 56),
        .y_offset = 7,
    },
    [SPECIES_ABRA] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 11,
    },
    [SPECIES_KADABRA] =
    {
        .size = MON_COORDS_SIZE(64, 56),
        .y_offset = 4,
    },
    [SPECIES_ALAKAZAM] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 1,
    },
    [SPECIES_MACHOP] =
    {
        .size = MON_COORDS_SIZE(32, 48),
        .y_offset = 11,
    },
    [SPECIES_MACHOKE] =
    {
        .size = MON_COORDS_SIZE(56, 56),
        .y_offset = 6,
    },
    [SPECIES_MACHAMP] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 3,
    },
    [SPECIES_BELLSPROUT] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 15,
    },
    [SPECIES_WEEPINBELL] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 11,
    },
    [SPECIES_VICTREEBEL] =
    {
        .size = MON_COORDS_SIZE(56, 56),
        .y_offset = 5,
    },
    [SPECIES_TENTACOOL] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 11,
    },
    [SPECIES_TENTACRUEL] =
    {
        .size = MON_COORDS_SIZE(56, 64),
        .y_offset = 1,
    },
    [SPECIES_GEODUDE] =
    {
        .size = MON_COORDS_SIZE(56, 32),
        .y_offset = 18,
    },
    [SPECIES_GRAVELER] =
    {
        .size = MON_COORDS_SIZE(64, 48),
        .y_offset = 11,
    },
    [SPECIES_GOLEM] =
    {
        .size = MON_COORDS_SIZE(64, 56),
        .y_offset = 7,
    },
    [SPECIES_PONYTA] =
    {
        .size = MON_COORDS_SIZE(48, 56),
        .y_offset = 7,
    },
    [SPECIES_RAPIDASH] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 0,
    },
    [SPECIES_SLOWPOKE] =
    {
        .size = MON_COORDS_SIZE(48, 40),
        .y_offset = 13,
    },
    [SPECIES_SLOWBRO] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 2,
    },
    [SPECIES_MAGNEMITE] =
    {
        .size = MON_COORDS_SIZE(40, 24),
        .y_offset = 22,
    },
    [SPECIES_MAGNETON] =
    {
        .size = MON_COORDS_SIZE(56, 40),
        .y_offset = 16,
    },
    [SPECIES_FARFETCHD] =
    {
        .size = MON_COORDS_SIZE(56, 48),
        .y_offset = 11,
    },
    [SPECIES_DODUO] =
    {
        .size = MON_COORDS_SIZE(48, 56),
        .y_offset = 7,
    },
    [SPECIES_DODRIO] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 1,
    },
    [SPECIES_SEEL] =
    {
        .size = MON_COORDS_SIZE(56, 48),
        .y_offset = 9,
    },
    [SPECIES_DEWGONG] =
    {
        .size = MON_COORDS_SIZE(64, 56),
        .y_offset = 7,
    },
    [SPECIES_GRIMER] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 11,
    },
    [SPECIES_MUK] =
    {
        .size = MON_COORDS_SIZE(64, 48),
        .y_offset = 10,
    },
    [SPECIES_SHELLDER] =
    {
        .size = MON_COORDS_SIZE(40, 40),
        .y_offset = 16,
    },
    [SPECIES_CLOYSTER] =
    {
        .size = MON_COORDS_SIZE(64, 56),
        .y_offset = 4,
    },
    [SPECIES_GASTLY] =
    {
        .size = MON_COORDS_SIZE(56, 56),
        .y_offset = 6,
    },
    [SPECIES_HAUNTER] =
    {
        .size = MON_COORDS_SIZE(64, 56),
        .y_offset = 7,
    },
    [SPECIES_GENGAR] =
    {
        .size = MON_COORDS_SIZE(56, 48),
        .y_offset = 9,
    },
    [SPECIES_ONIX] =
    {
        .size = MON_COORDS_SIZE(56, 64),
        .y_offset = 3,
    },
    [SPECIES_DROWZEE] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 9,
    },
    [SPECIES_HYPNO] =
    {
        .size = MON_COORDS_SIZE(64, 56),
        .y_offset = 4,
    },
    [SPECIES_KRABBY] =
    {
        .size = MON_COORDS_SIZE(56, 40),
        .y_offset = 14,
    },
    [SPECIES_KINGLER] =
    {
        .size = MON_COORDS_SIZE(64, 56),
        .y_offset = 5,
    },
    [SPECIES_VOLTORB] =
    {
        .size = MON_COORDS_SIZE(32, 32),
        .y_offset = 19,
    },
    [SPECIES_ELECTRODE] =
    {
        .size = MON_COORDS_SIZE(40, 40),
        .y_offset = 14,
    },
    [SPECIES_EXEGGCUTE] =
    {
        .size = MON_COORDS_SIZE(56, 48),
        .y_offset = 9,
    },
    [SPECIES_EXEGGUTOR] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 1,
    },
    [SPECIES_CUBONE] =
    {
        .size = MON_COORDS_SIZE(48, 40),
        .y_offset = 13,
    },
    [SPECIES_MAROWAK] =
    {
        .size = MON_COORDS_SIZE(64, 56),
        .y_offset = 13,
    },
    [SPECIES_HITMONLEE] =
    {
        .size = MON_COORDS_SIZE(56, 56),
        .y_offset = 4,
    },
    [SPECIES_HITMONCHAN] =
    {
        .size = MON_COORDS_SIZE(48, 56),
        .y_offset = 4,
    },
    [SPECIES_LICKITUNG] =
    {
        .size = MON_COORDS_SIZE(64, 48),
        .y_offset = 8,
    },
    [SPECIES_KOFFING] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 11,
    },
    [SPECIES_WEEZING] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 7,
    },
    [SPECIES_RHYHORN] =
    {
        .size = MON_COORDS_SIZE(56, 48),
        .y_offset = 9,
    },
    [SPECIES_RHYDON] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 2,
    },
    [SPECIES_CHANSEY] =
    {
        .size = MON_COORDS_SIZE(56, 48),
        .y_offset = 9,
    },
    [SPECIES_TANGELA] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 8,
    },
    [SPECIES_KANGASKHAN] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 0,
    },
    [SPECIES_HORSEA] =
    {
        .size = MON_COORDS_SIZE(32, 40),
        .y_offset = 16,
    },
    [SPECIES_SEADRA] =
    {
        .size = MON_COORDS_SIZE(56, 56),
        .y_offset = 6,
    },
    [SPECIES_GOLDEEN] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 10,
    },
    [SPECIES_SEAKING] =
    {
        .size = MON_COORDS_SIZE(56, 56),
        .y_offset = 4,
    },
    [SPECIES_STARYU] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 13,
    },
    [SPECIES_STARMIE] =
    {
        .size = MON_COORDS_SIZE(48, 56),
        .y_offset = 10,
    },
    [SPECIES_MR_MIME] =
    {
        .size = MON_COORDS_SIZE(56, 48),
        .y_offset = 8,
    },
    [SPECIES_SCYTHER] =
    {
        .size = MON_COORDS_SIZE(56, 64),
        .y_offset = 2,
    },
    [SPECIES_JYNX] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 8,
    },
    [SPECIES_ELECTABUZZ] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 4,
    },
    [SPECIES_MAGMAR] =
    {
        .size = MON_COORDS_SIZE(64, 56),
        .y_offset = 4,
    },
    [SPECIES_PINSIR] =
    {
        .size = MON_COORDS_SIZE(56, 56),
        .y_offset = 4,
    },
    [SPECIES_TAUROS] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 5,
    },
    [SPECIES_MAGIKARP] =
    {
        .size = MON_COORDS_SIZE(56, 56),
        .y_offset = 11,
    },
    [SPECIES_GYARADOS] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 0,
    },
    [SPECIES_LAPRAS] =
    {
        .size = MON_COORDS_SIZE(64, 56),
        .y_offset = 4,
    },
    [SPECIES_DITTO] =
    {
        .size = MON_COORDS_SIZE(40, 32),
        .y_offset = 17,
    },
    [SPECIES_EEVEE] =
    {
        .size = MON_COORDS_SIZE(40, 48),
        .y_offset = 13,
    },
    [SPECIES_VAPOREON] =
    {
        .size = MON_COORDS_SIZE(48, 56),
        .y_offset = 6,
    },
    [SPECIES_JOLTEON] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 10,
    },
    [SPECIES_FLAREON] =
    {
        .size = MON_COORDS_SIZE(56, 48),
        .y_offset = 11,
    },
    [SPECIES_PORYGON] =
    {
        .size = MON_COORDS_SIZE(40, 48),
        .y_offset = 11,
    },
    [SPECIES_OMANYTE] =
    {
        .size = MON_COORDS_SIZE(32, 40),
        .y_offset = 15,
    },
    [SPECIES_OMASTAR] =
    {
        .size = MON_COORDS_SIZE(48, 56),
        .y_offset = 7,
    },
    [SPECIES_KABUTO] =
    {
        .size = MON_COORDS_SIZE(40, 32),
        .y_offset = 20,
    },
    [SPECIES_KABUTOPS] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 3,
    },
    [SPECIES_AERODACTYL] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 1,
    },
    [SPECIES_SNORLAX] =
    {
        .size = MON_COORDS_SIZE(64, 56),
        .y_offset = 5,
    },
    [SPECIES_ARTICUNO] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 0,
    },
    [SPECIES_ZAPDOS] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 4,
    },
    [SPECIES_MOLTRES] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 6,
    },
    [SPECIES_DRATINI] =
    {
        .size = MON_COORDS_SIZE(56, 40),
        .y_offset = 15,
    },
    [SPECIES_DRAGONAIR] =
    {
        .size = MON_COORDS_SIZE(64, 56),
        .y_offset = 6,
    },
    [SPECIES_DRAGONITE] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 0,
    },
    [SPECIES_MEWTWO] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 0,
    },
    [SPECIES_MEW] =
    {
        .size = MON_COORDS_SIZE(56, 56),
        .y_offset = 13,
    },
    [SPECIES_CHIKORITA] =
    {
        .size = MON_COORDS_SIZE(56, 40),
        .y_offset = 13,
    },
    [SPECIES_BAYLEEF] =
    {
        .size = MON_COORDS_SIZE(56, 56),
        .y_offset = 4,
    },
    [SPECIES_MEGANIUM] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 0,
    },
    [SPECIES_CYNDAQUIL] =
    {
        .size = MON_COORDS_SIZE(40, 40),
        .y_offset = 14,
    },
    [SPECIES_QUILAVA] =
    {
        .size = MON_COORDS_SIZE(56, 48),
        .y_offset = 8,
    },
    [SPECIES_TYPHLOSION] =
    {
        .size = MON_COORDS_SIZE(56, 64),
        .y_offset = 0,
    },
    [SPECIES_TOTODILE] =
    {
        .size = MON_COORDS_SIZE(40, 40),
        .y_offset = 15,
    },
    [SPECIES_CROCONAW] =
    {
        .size = MON_COORDS_SIZE(48, 56),
        .y_offset = 6,
    },
    [SPECIES_FERALIGATR] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 0,
    },
    [SPECIES_SENTRET] =
    {
        .size = MON_COORDS_SIZE(32, 56),
        .y_offset = 4,
    },
    [SPECIES_FURRET] =
    {
        .size = MON_COORDS_SIZE(48, 56),
        .y_offset = 7,
    },
    [SPECIES_HOOTHOOT] =
    {
        .size = MON_COORDS_SIZE(40, 40),
        .y_offset = 13,
    },
    [SPECIES_NOCTOWL] =
    {
        .size = MON_COORDS_SIZE(40, 64),
        .y_offset = 3,
    },
    [SPECIES_LEDYBA] =
    {
        .size = MON_COORDS_SIZE(40, 48),
        .y_offset = 12,
    },
    [SPECIES_LEDIAN] =
    {
        .size = MON_COORDS_SIZE(48, 56),
        .y_offset = 4,
    },
    [SPECIES_SPINARAK] =
    {
        .size = MON_COORDS_SIZE(40, 32),
        .y_offset = 19,
    },
    [SPECIES_ARIADOS] =
    {
        .size = MON_COORDS_SIZE(64, 56),
        .y_offset = 5,
    },
    [SPECIES_CROBAT] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 0,
    },
    [SPECIES_CHINCHOU] =
    {
        .size = MON_COORDS_SIZE(56, 40),
        .y_offset = 16,
    },
    [SPECIES_LANTURN] =
    {
        .size = MON_COORDS_SIZE(64, 56),
        .y_offset = 11,
    },
    [SPECIES_PICHU] =
    {
        .size = MON_COORDS_SIZE(32, 40),
        .y_offset = 12,
    },
    [SPECIES_CLEFFA] =
    {
        .size = MON_COORDS_SIZE(32, 32),
        .y_offset = 20,
    },
    [SPECIES_IGGLYBUFF] =
    {
        .size = MON_COORDS_SIZE(32, 32),
        .y_offset = 18,
    },
    [SPECIES_TOGEPI] =
    {
        .size = MON_COORDS_SIZE(24, 32),
        .y_offset = 20,
    },
    [SPECIES_TOGETIC] =
    {
        .size = MON_COORDS_SIZE(32, 48),
        .y_offset = 9,
    },
    [SPECIES_NATU] =
    {
        .size = MON_COORDS_SIZE(32, 32),
        .y_offset = 20,
    },
    [SPECIES_XATU] =
    {
        .size = MON_COORDS_SIZE(32, 56),
        .y_offset = 7,
    },
    [SPECIES_MAREEP] =
    {
        .size = MON_COORDS_SIZE(40, 40),
        .y_offset = 16,
    },
    [SPECIES_FLAAFFY] =
    {
        .size = MON_COORDS_SIZE(40, 48),
        .y_offset = 10,
    },
    [SPECIES_AMPHAROS] =
    {
        .size = MON_COORDS_SIZE(56, 56),
        .y_offset = 5,
    },
    [SPECIES_BELLOSSOM] =
    {
        .size = MON_COORDS_SIZE(32, 40),
        .y_offset = 14,
    },
    [SPECIES_MARILL] =
    {
        .size = MON_COORDS_SIZE(48, 40),
        .y_offset = 14,
    },
    [SPECIES_AZUMARILL] =
    {
        .size = MON_COORDS_SIZE(56, 48),
        .y_offset = 9,
    },
    [SPECIES_SUDOWOODO] =
    {
        .size = MON_COORDS_SIZE(48, 56),
        .y_offset = 6,
    },
    [SPECIES_POLITOED] =
    {
        .size = MON_COORDS_SIZE(48, 56),
        .y_offset = 6,
    },
    [SPECIES_HOPPIP] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 10,
    },
    [SPECIES_SKIPLOOM] =
    {
        .size = MON_COORDS_SIZE(40, 40),
        .y_offset = 15,
    },
    [SPECIES_JUMPLUFF] =
    {
        .size = MON_COORDS_SIZE(56, 56),
        .y_offset = 7,
    },
    [SPECIES_AIPOM] =
    {
        .size = MON_COORDS_SIZE(40, 64),
        .y_offset = 3,
    },
    [SPECIES_SUNKERN] =
    {
        .size = MON_COORDS_SIZE(32, 32),
        .y_offset = 16,
    },
    [SPECIES_SUNFLORA] =
    {
        .size = MON_COORDS_SIZE(40, 48),
        .y_offset = 8,
    },
    [SPECIES_YANMA] =
    {
        .size = MON_COORDS_SIZE(64, 48),
        .y_offset = 10,
    },
    [SPECIES_WOOPER] =
    {
        .size = MON_COORDS_SIZE(40, 32),
        .y_offset = 16,
    },
    [SPECIES_QUAGSIRE] =
    {
        .size = MON_COORDS_SIZE(56, 56),
        .y_offset = 7,
    },
    [SPECIES_ESPEON] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 8,
    },
    [SPECIES_UMBREON] =
    {
        .size = MON_COORDS_SIZE(48, 56),
        .y_offset = 8,
    },
    [SPECIES_MURKROW] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 11,
    },
    [SPECIES_SLOWKING] =
    {
        .size = MON_COORDS_SIZE(40, 64),
        .y_offset = 1,
    },
    [SPECIES_MISDREAVUS] =
    {
        .size = MON_COORDS_SIZE(40, 40),
        .y_offset = 12,
    },
    [SPECIES_UNOWN] =
    {
        .size = MON_COORDS_SIZE(24, 40),
        .y_offset = 15,
    },
    [SPECIES_WOBBUFFET] =
    {
        .size = MON_COORDS_SIZE(56, 56),
        .y_offset = 6,
    },
    [SPECIES_GIRAFARIG] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 3,
    },
    [SPECIES_PINECO] =
    {
        .size = MON_COORDS_SIZE(40, 48),
        .y_offset = 10,
    },
    [SPECIES_FORRETRESS] =
    {
        .size = MON_COORDS_SIZE(56, 48),
        .y_offset = 9,
    },
    [SPECIES_DUNSPARCE] =
    {
        .size = MON_COORDS_SIZE(56, 32),
        .y_offset = 17,
    },
    [SPECIES_GLIGAR] =
    {
        .size = MON_COORDS_SIZE(56, 64),
        .y_offset = 3,
    },
    [SPECIES_STEELIX] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 0,
    },
    [SPECIES_SNUBBULL] =
    {
        .size = MON_COORDS_SIZE(40, 40),
        .y_offset = 13,
    },
    [SPECIES_GRANBULL] =
    {
        .size = MON_COORDS_SIZE(40, 56),
        .y_offset = 6,
    },
    [SPECIES_QWILFISH] =
    {
        .size = MON_COORDS_SIZE(40, 48),
        .y_offset = 10,
    },
    [SPECIES_SCIZOR] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 0,
    },
    [SPECIES_SHUCKLE] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 9,
    },
    [SPECIES_HERACROSS] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 3,
    },
    [SPECIES_SNEASEL] =
    {
        .size = MON_COORDS_SIZE(48, 56),
        .y_offset = 5,
    },
    [SPECIES_TEDDIURSA] =
    {
        .size = MON_COORDS_SIZE(32, 48),
        .y_offset = 11,
    },
    [SPECIES_URSARING] =
    {
        .size = MON_COORDS_SIZE(56, 64),
        .y_offset = 1,
    },
    [SPECIES_SLUGMA] =
    {
        .size = MON_COORDS_SIZE(32, 40),
        .y_offset = 13,
    },
    [SPECIES_MAGCARGO] =
    {
        .size = MON_COORDS_SIZE(40, 56),
        .y_offset = 13,
    },
    [SPECIES_SWINUB] =
    {
        .size = MON_COORDS_SIZE(32, 24),
        .y_offset = 20,
    },
    [SPECIES_PILOSWINE] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 8,
    },
    [SPECIES_CORSOLA] =
    {
        .size = MON_COORDS_SIZE(48, 40),
        .y_offset = 12,
    },
    [SPECIES_REMORAID] =
    {
        .size = MON_COORDS_SIZE(40, 40),
        .y_offset = 14,
    },
    [SPECIES_OCTILLERY] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 10,
    },
    [SPECIES_DELIBIRD] =
    {
        .size = MON_COORDS_SIZE(40, 48),
        .y_offset = 8,
    },
    [SPECIES_MANTINE] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 1,
    },
    [SPECIES_SKARMORY] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 0,
    },
    [SPECIES_HOUNDOUR] =
    {
        .size = MON_COORDS_SIZE(40, 48),
        .y_offset = 11,
    },
    [SPECIES_HOUNDOOM] =
    {
        .size = MON_COORDS_SIZE(56, 56),
        .y_offset = 5,
    },
    [SPECIES_KINGDRA] =
    {
        .size = MON_COORDS_SIZE(56, 64),
        .y_offset = 4,
    },
    [SPECIES_PHANPY] =
    {
        .size = MON_COORDS_SIZE(40, 32),
        .y_offset = 16,
    },
    [SPECIES_DONPHAN] =
    {
        .size = MON_COORDS_SIZE(64, 48),
        .y_offset = 8,
    },
    [SPECIES_PORYGON2] =
    {
        .size = MON_COORDS_SIZE(40, 40),
        .y_offset = 15,
    },
    [SPECIES_STANTLER] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 0,
    },
    [SPECIES_SMEARGLE] =
    {
        .size = MON_COORDS_SIZE(56, 56),
        .y_offset = 6,
    },
    [SPECIES_TYROGUE] =
    {
        .size = MON_COORDS_SIZE(32, 48),
        .y_offset = 9,
    },
    [SPECIES_HITMONTOP] =
    {
        .size = MON_COORDS_SIZE(48, 56),
        .y_offset = 5,
    },
    [SPECIES_SMOOCHUM] =
    {
        .size = MON_COORDS_SIZE(24, 40),
        .y_offset = 15,
    },
    [SPECIES_ELEKID] =
    {
        .size = MON_COORDS_SIZE(56, 48),
        .y_offset = 10,
    },
    [SPECIES_MAGBY] =
    {
        .size = MON_COORDS_SIZE(32, 40),
        .y_offset = 13,
    },
    [SPECIES_MILTANK] =
    {
        .size = MON_COORDS_SIZE(56, 56),
        .y_offset = 4,
    },
    [SPECIES_BLISSEY] =
    {
        .size = MON_COORDS_SIZE(56, 56),
        .y_offset = 6,
    },
    [SPECIES_RAIKOU] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 0,
    },
    [SPECIES_ENTEI] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 0,
    },
    [SPECIES_SUICUNE] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 0,
    },
    [SPECIES_LARVITAR] =
    {
        .size = MON_COORDS_SIZE(32, 48),
        .y_offset = 9,
    },
    [SPECIES_PUPITAR] =
    {
        .size = MON_COORDS_SIZE(40, 48),
        .y_offset = 9,
    },
    [SPECIES_TYRANITAR] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 0,
    },
    [SPECIES_LUGIA] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 0,
    },
    [SPECIES_HO_OH] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 0,
    },
    [SPECIES_CELEBI] =
    {
        .size = MON_COORDS_SIZE(40, 40),
        .y_offset = 14,
    },
    [SPECIES_OLD_UNOWN_B] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 6,
    },
    [SPECIES_OLD_UNOWN_C] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 6,
    },
    [SPECIES_OLD_UNOWN_D] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 6,
    },
    [SPECIES_OLD_UNOWN_E] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 6,
    },
    [SPECIES_OLD_UNOWN_F] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 6,
    },
    [SPECIES_OLD_UNOWN_G] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 6,
    },
    [SPECIES_OLD_UNOWN_H] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 6,
    },
    [SPECIES_OLD_UNOWN_I] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 6,
    },
    [SPECIES_OLD_UNOWN_J] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 6,
    },
    [SPECIES_OLD_UNOWN_K] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 6,
    },
    [SPECIES_OLD_UNOWN_L] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 6,
    },
    [SPECIES_OLD_UNOWN_M] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 6,
    },
    [SPECIES_OLD_UNOWN_N] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 6,
    },
    [SPECIES_OLD_UNOWN_O] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 6,
    },
    [SPECIES_OLD_UNOWN_P] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 6,
    },
    [SPECIES_OLD_UNOWN_Q] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 6,
    },
    [SPECIES_OLD_UNOWN_R] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 6,
    },
    [SPECIES_OLD_UNOWN_S] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 6,
    },
    [SPECIES_OLD_UNOWN_T] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 6,
    },
    [SPECIES_OLD_UNOWN_U] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 6,
    },
    [SPECIES_OLD_UNOWN_V] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 6,
    },
    [SPECIES_OLD_UNOWN_W] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 6,
    },
    [SPECIES_OLD_UNOWN_X] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 6,
    },
    [SPECIES_OLD_UNOWN_Y] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 6,
    },
    [SPECIES_OLD_UNOWN_Z] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 6,
    },
    [SPECIES_TREECKO] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 8,
    },
    [SPECIES_GROVYLE] =
    {
        .size = MON_COORDS_SIZE(64, 56),
        .y_offset = 4,
    },
    [SPECIES_SCEPTILE] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 0,
    },
    [SPECIES_TORCHIC] =
    {
        .size = MON_COORDS_SIZE(40, 48),
        .y_offset = 8,
    },
    [SPECIES_COMBUSKEN] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 1,
    },
    [SPECIES_BLAZIKEN] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 0,
    },
    [SPECIES_MUDKIP] =
    {
        .size = MON_COORDS_SIZE(40, 48),
        .y_offset = 12,
    },
    [SPECIES_MARSHTOMP] =
    {
        .size = MON_COORDS_SIZE(48, 56),
        .y_offset = 6,
    },
    [SPECIES_SWAMPERT] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 0,
    },
    [SPECIES_POOCHYENA] =
    {
        .size = MON_COORDS_SIZE(40, 40),
        .y_offset = 12,
    },
    [SPECIES_MIGHTYENA] =
    {
        .size = MON_COORDS_SIZE(64, 56),
        .y_offset = 4,
    },
    [SPECIES_ZIGZAGOON] =
    {
        .size = MON_COORDS_SIZE(64, 40),
        .y_offset = 15,
    },
    [SPECIES_LINOONE] =
    {
        .size = MON_COORDS_SIZE(56, 64),
        .y_offset = 3,
    },
    [SPECIES_WURMPLE] =
    {
        .size = MON_COORDS_SIZE(32, 40),
        .y_offset = 14,
    },
    [SPECIES_SILCOON] =
    {
        .size = MON_COORDS_SIZE(56, 40),
        .y_offset = 17,
    },
    [SPECIES_BEAUTIFLY] =
    {
        .size = MON_COORDS_SIZE(64, 48),
        .y_offset = 9,
    },
    [SPECIES_CASCOON] =
    {
        .size = MON_COORDS_SIZE(56, 32),
        .y_offset = 16,
    },
    [SPECIES_DUSTOX] =
    {
        .size = MON_COORDS_SIZE(64, 48),
        .y_offset = 15,
    },
    [SPECIES_LOTAD] =
    {
        .size = MON_COORDS_SIZE(48, 40),
        .y_offset = 14,
    },
    [SPECIES_LOMBRE] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 9,
    },
    [SPECIES_LUDICOLO] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 0,
    },
    [SPECIES_SEEDOT] =
    {
        .size = MON_COORDS_SIZE(32, 48),
        .y_offset = 16,
    },
    [SPECIES_NUZLEAF] =
    {
        .size = MON_COORDS_SIZE(40, 48),
        .y_offset = 8,
    },
    [SPECIES_SHIFTRY] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 2,
    },
    [SPECIES_NINCADA] =
    {
        .size = MON_COORDS_SIZE(56, 32),
        .y_offset = 18,
    },
    [SPECIES_NINJASK] =
    {
        .size = MON_COORDS_SIZE(64, 48),
        .y_offset = 10,
    },
    [SPECIES_SHEDINJA] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 10,
    },
    [SPECIES_TAILLOW] =
    {
        .size = MON_COORDS_SIZE(48, 32),
        .y_offset = 16,
    },
    [SPECIES_SWELLOW] =
    {
        .size = MON_COORDS_SIZE(64, 56),
        .y_offset = 6,
    },
    [SPECIES_SHROOMISH] =
    {
        .size = MON_COORDS_SIZE(40, 32),
        .y_offset = 16,
    },
    [SPECIES_BRELOOM] =
    {
        .size = MON_COORDS_SIZE(56, 56),
        .y_offset = 4,
    },
    [SPECIES_SPINDA] =
    {
        .size = MON_COORDS_SIZE(48, 56),
        .y_offset = 8,
    },
    [SPECIES_WINGULL] =
    {
        .size = MON_COORDS_SIZE(64, 32),
        .y_offset = 24,
    },
    [SPECIES_PELIPPER] =
    {
        .size = MON_COORDS_SIZE(56, 56),
        .y_offset = 4,
    },
    [SPECIES_SURSKIT] =
    {
        .size = MON_COORDS_SIZE(48, 40),
        .y_offset = 15,
    },
    [SPECIES_MASQUERAIN] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 1,
    },
    [SPECIES_WAILMER] =
    {
        .size = MON_COORDS_SIZE(56, 40),
        .y_offset = 15,
    },
    [SPECIES_WAILORD] =
    {
        .size = MON_COORDS_SIZE(64, 56),
        .y_offset = 10,
    },
    [SPECIES_SKITTY] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 11,
    },
    [SPECIES_DELCATTY] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 8,
    },
    [SPECIES_KECLEON] =
    {
        .size = MON_COORDS_SIZE(48, 56),
        .y_offset = 7,
    },
    [SPECIES_BALTOY] =
    {
        .size = MON_COORDS_SIZE(40, 40),
        .y_offset = 16,
    },
    [SPECIES_CLAYDOL] =
    {
        .size = MON_COORDS_SIZE(56, 64),
        .y_offset = 6,
    },
    [SPECIES_NOSEPASS] =
    {
        .size = MON_COORDS_SIZE(40, 48),
        .y_offset = 12,
    },
    [SPECIES_TORKOAL] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 2,
    },
    [SPECIES_SABLEYE] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 9,
    },
    [SPECIES_BARBOACH] =
    {
        .size = MON_COORDS_SIZE(32, 48),
        .y_offset = 11,
    },
    [SPECIES_WHISCASH] =
    {
        .size = MON_COORDS_SIZE(56, 48),
        .y_offset = 9,
    },
    [SPECIES_LUVDISC] =
    {
        .size = MON_COORDS_SIZE(32, 48),
        .y_offset = 24,
    },
    [SPECIES_CORPHISH] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 12,
    },
    [SPECIES_CRAWDAUNT] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 1,
    },
    [SPECIES_FEEBAS] =
    {
        .size = MON_COORDS_SIZE(32, 48),
        .y_offset = 13,
    },
    [SPECIES_MILOTIC] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 0,
    },
    [SPECIES_CARVANHA] =
    {
        .size = MON_COORDS_SIZE(48, 56),
        .y_offset = 6,
    },
    [SPECIES_SHARPEDO] =
    {
        .size = MON_COORDS_SIZE(56, 64),
        .y_offset = 3,
    },
    [SPECIES_TRAPINCH] =
    {
        .size = MON_COORDS_SIZE(40, 32),
        .y_offset = 16,
    },
    [SPECIES_VIBRAVA] =
    {
        .size = MON_COORDS_SIZE(64, 48),
        .y_offset = 12,
    },
    [SPECIES_FLYGON] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 1,
    },
    [SPECIES_MAKUHITA] =
    {
        .size = MON_COORDS_SIZE(48, 40),
        .y_offset = 12,
    },
    [SPECIES_HARIYAMA] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 1,
    },
    [SPECIES_ELECTRIKE] =
    {
        .size = MON_COORDS_SIZE(48, 32),
        .y_offset = 18,
    },
    [SPECIES_MANECTRIC] =
    {
        .size = MON_COORDS_SIZE(48, 56),
        .y_offset = 4,
    },
    [SPECIES_NUMEL] =
    {
        .size = MON_COORDS_SIZE(48, 40),
        .y_offset = 15,
    },
    [SPECIES_CAMERUPT] =
    {
        .size = MON_COORDS_SIZE(64, 56),
        .y_offset = 9,
    },
    [SPECIES_SPHEAL] =
    {
        .size = MON_COORDS_SIZE(48, 40),
        .y_offset = 16,
    },
    [SPECIES_SEALEO] =
    {
        .size = MON_COORDS_SIZE(64, 48),
        .y_offset = 10,
    },
    [SPECIES_WALREIN] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 1,
    },
    [SPECIES_CACNEA] =
    {
        .size = MON_COORDS_SIZE(56, 32),
        .y_offset = 16,
    },
    [SPECIES_CACTURNE] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 0,
    },
    [SPECIES_SNORUNT] =
    {
        .size = MON_COORDS_SIZE(40, 48),
        .y_offset = 11,
    },
    [SPECIES_GLALIE] =
    {
        .size = MON_COORDS_SIZE(56, 48),
        .y_offset = 10,
    },
    [SPECIES_LUNATONE] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 9,
    },
    [SPECIES_SOLROCK] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 1,
    },
    [SPECIES_AZURILL] =
    {
        .size = MON_COORDS_SIZE(40, 40),
        .y_offset = 15,
    },
    [SPECIES_SPOINK] =
    {
        .size = MON_COORDS_SIZE(32, 48),
        .y_offset = 9,
    },
    [SPECIES_GRUMPIG] =
    {
        .size = MON_COORDS_SIZE(56, 56),
        .y_offset = 5,
    },
    [SPECIES_PLUSLE] =
    {
        .size = MON_COORDS_SIZE(40, 48),
        .y_offset = 14,
    },
    [SPECIES_MINUN] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 12,
    },
    [SPECIES_MAWILE] =
    {
        .size = MON_COORDS_SIZE(56, 48),
        .y_offset = 8,
    },
    [SPECIES_MEDITITE] =
    {
        .size = MON_COORDS_SIZE(48, 40),
        .y_offset = 12,
    },
    [SPECIES_MEDICHAM] =
    {
        .size = MON_COORDS_SIZE(48, 64),
        .y_offset = 1,
    },
    [SPECIES_SWABLU] =
    {
        .size = MON_COORDS_SIZE(56, 48),
        .y_offset = 17,
    },
    [SPECIES_ALTARIA] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 2,
    },
    [SPECIES_WYNAUT] =
    {
        .size = MON_COORDS_SIZE(40, 40),
        .y_offset = 12,
    },
    [SPECIES_DUSKULL] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 10,
    },
    [SPECIES_DUSCLOPS] =
    {
        .size = MON_COORDS_SIZE(56, 56),
        .y_offset = 5,
    },
    [SPECIES_ROSELIA] =
    {
        .size = MON_COORDS_SIZE(56, 48),
        .y_offset = 8,
    },
    [SPECIES_SLAKOTH] =
    {
        .size = MON_COORDS_SIZE(56, 32),
        .y_offset = 18,
    },
    [SPECIES_VIGOROTH] =
    {
        .size = MON_COORDS_SIZE(56, 64),
        .y_offset = 0,
    },
    [SPECIES_SLAKING] =
    {
        .size = MON_COORDS_SIZE(64, 48),
        .y_offset = 8,
    },
    [SPECIES_GULPIN] =
    {
        .size = MON_COORDS_SIZE(40, 40),
        .y_offset = 18,
    },
    [SPECIES_SWALOT] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 8,
    },
    [SPECIES_TROPIUS] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 0,
    },
    [SPECIES_WHISMUR] =
    {
        .size = MON_COORDS_SIZE(40, 40),
        .y_offset = 14,
    },
    [SPECIES_LOUDRED] =
    {
        .size = MON_COORDS_SIZE(56, 64),
        .y_offset = 3,
    },
    [SPECIES_EXPLOUD] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 1,
    },
    [SPECIES_CLAMPERL] =
    {
        .size = MON_COORDS_SIZE(40, 40),
        .y_offset = 14,
    },
    [SPECIES_HUNTAIL] =
    {
        .size = MON_COORDS_SIZE(56, 64),
        .y_offset = 3,
    },
    [SPECIES_GOREBYSS] =
    {
        .size = MON_COORDS_SIZE(64, 48),
        .y_offset = 11,
    },
    [SPECIES_ABSOL] =
    {
        .size = MON_COORDS_SIZE(48, 64),
        .y_offset = 0,
    },
    [SPECIES_SHUPPET] =
    {
        .size = MON_COORDS_SIZE(40, 48),
        .y_offset = 14,
    },
    [SPECIES_BANETTE] =
    {
        .size = MON_COORDS_SIZE(40, 40),
        .y_offset = 12,
    },
    [SPECIES_SEVIPER] =
    {
        .size = MON_COORDS_SIZE(56, 56),
        .y_offset = 8,
    },
    [SPECIES_ZANGOOSE] =
    {
        .size = MON_COORDS_SIZE(64, 56),
        .y_offset = 5,
    },
    [SPECIES_RELICANTH] =
    {
        .size = MON_COORDS_SIZE(56, 56),
        .y_offset = 11,
    },
    [SPECIES_ARON] =
    {
        .size = MON_COORDS_SIZE(32, 24),
        .y_offset = 20,
    },
    [SPECIES_LAIRON] =
    {
        .size = MON_COORDS_SIZE(56, 40),
        .y_offset = 13,
    },
    [SPECIES_AGGRON] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 0,
    },
    [SPECIES_CASTFORM] =
    {
        .size = MON_COORDS_SIZE(24, 32),
        .y_offset = 17,
    },
    [SPECIES_VOLBEAT] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 8,
    },
    [SPECIES_ILLUMISE] =
    {
        .size = MON_COORDS_SIZE(40, 48),
        .y_offset = 8,
    },
    [SPECIES_LILEEP] =
    {
        .size = MON_COORDS_SIZE(48, 56),
        .y_offset = 7,
    },
    [SPECIES_CRADILY] =
    {
        .size = MON_COORDS_SIZE(56, 64),
        .y_offset = 0,
    },
    [SPECIES_ANORITH] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 8,
    },
    [SPECIES_ARMALDO] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 0,
    },
    [SPECIES_RALTS] =
    {
        .size = MON_COORDS_SIZE(24, 40),
        .y_offset = 15,
    },
    [SPECIES_KIRLIA] =
    {
        .size = MON_COORDS_SIZE(32, 56),
        .y_offset = 6,
    },
    [SPECIES_GARDEVOIR] =
    {
        .size = MON_COORDS_SIZE(56, 64),
        .y_offset = 1,
    },
    [SPECIES_BAGON] =
    {
        .size = MON_COORDS_SIZE(40, 48),
        .y_offset = 11,
    },
    [SPECIES_SHELGON] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 9,
    },
    [SPECIES_SALAMENCE] =
    {
        .size = MON_COORDS_SIZE(64, 56),
        .y_offset = 4,
    },
    [SPECIES_BELDUM] =
    {
        .size = MON_COORDS_SIZE(40, 40),
        .y_offset = 15,
    },
    [SPECIES_METANG] =
    {
        .size = MON_COORDS_SIZE(64, 56),
        .y_offset = 7,
    },
    [SPECIES_METAGROSS] =
    {
        .size = MON_COORDS_SIZE(64, 56),
        .y_offset = 6,
    },
    [SPECIES_REGIROCK] =
    {
        .size = MON_COORDS_SIZE(56, 64),
        .y_offset = 4,
    },
    [SPECIES_REGICE] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 2,
    },
    [SPECIES_REGISTEEL] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 3,
    },
    [SPECIES_KYOGRE] =
    {
        .size = MON_COORDS_SIZE(64, 56),
        .y_offset = 4,
    },
    [SPECIES_GROUDON] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 1,
    },
    [SPECIES_RAYQUAZA] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 0,
    },
    [SPECIES_LATIAS] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 1,
    },
    [SPECIES_LATIOS] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 2,
    },
    [SPECIES_JIRACHI] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 13,
    },
    [SPECIES_DEOXYS] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 1,
    },
    [SPECIES_CHIMECHO] =
    {
        .size = MON_COORDS_SIZE(24, 56),
        .y_offset = 6,
    },
    [SPECIES_EGG] =
    {
        .size = MON_COORDS_SIZE(24, 24),
        .y_offset = 20,
    },
    [SPECIES_UNOWN_B] =
    {
        .size = MON_COORDS_SIZE(24, 32),
        .y_offset = 16,
    },
    [SPECIES_UNOWN_C] =
    {
        .size = MON_COORDS_SIZE(32, 32),
        .y_offset = 16,
    },
    [SPECIES_UNOWN_D] =
    {
        .size = MON_COORDS_SIZE(32, 32),
        .y_offset = 16,
    },
    [SPECIES_UNOWN_E] =
    {
        .size = MON_COORDS_SIZE(32, 32),
        .y_offset = 17,
    },
    [SPECIES_UNOWN_F] =
    {
        .size = MON_COORDS_SIZE(32, 32),
        .y_offset = 17,
    },
    [SPECIES_UNOWN_G] =
    {
        .size = MON_COORDS_SIZE(24, 40),
        .y_offset = 14,
    },
    [SPECIES_UNOWN_H] =
    {
        .size = MON_COORDS_SIZE(32, 32),
        .y_offset = 16,
    },
    [SPECIES_UNOWN_I] =
    {
        .size = MON_COORDS_SIZE(24, 32),
        .y_offset = 16,
    },
    [SPECIES_UNOWN_J] =
    {
        .size = MON_COORDS_SIZE(24, 32),
        .y_offset = 17,
    },
    [SPECIES_UNOWN_K] =
    {
        .size = MON_COORDS_SIZE(32, 32),
        .y_offset = 17,
    },
    [SPECIES_UNOWN_L] =
    {
        .size = MON_COORDS_SIZE(24, 32),
        .y_offset = 19,
    },
    [SPECIES_UNOWN_M] =
    {
        .size = MON_COORDS_SIZE(32, 32),
        .y_offset = 19,
    },
    [SPECIES_UNOWN_N] =
    {
        .size = MON_COORDS_SIZE(32, 24),
        .y_offset = 20,
    },
    [SPECIES_UNOWN_O] =
    {
        .size = MON_COORDS_SIZE(32, 32),
        .y_offset = 16,
    },
    [SPECIES_UNOWN_P] =
    {
        .size = MON_COORDS_SIZE(24, 32),
        .y_offset = 19,
    },
    [SPECIES_UNOWN_Q] =
    {
        .size = MON_COORDS_SIZE(32, 24),
        .y_offset = 21,
    },
    [SPECIES_UNOWN_R] =
    {
        .size = MON_COORDS_SIZE(24, 32),
        .y_offset = 19,
    },
    [SPECIES_UNOWN_S] =
    {
        .size = MON_COORDS_SIZE(32, 40),
        .y_offset = 12,
    },
    [SPECIES_UNOWN_T] =
    {
        .size = MON_COORDS_SIZE(24, 32),
        .y_offset = 18,
    },
    [SPECIES_UNOWN_U] =
    {
        .size = MON_COORDS_SIZE(32, 32),
        .y_offset = 18,
    },
    [SPECIES_UNOWN_V] =
    {
        .size = MON_COORDS_SIZE(32, 32),
        .y_offset = 18,
    },
    [SPECIES_UNOWN_W] =
    {
        .size = MON_COORDS_SIZE(32, 32),
        .y_offset = 19,
    },
    [SPECIES_UNOWN_X] =
    {
        .size = MON_COORDS_SIZE(24, 24),
        .y_offset = 21,
    },
    [SPECIES_UNOWN_Y] =
    {
        .size = MON_COORDS_SIZE(24, 32),
        .y_offset = 17,
    },
    [SPECIES_UNOWN_Z] =
    {
        .size = MON_COORDS_SIZE(24, 32),
        .y_offset = 16,
    },
    [SPECIES_UNOWN_EMARK] =
    {
        .size = MON_COORDS_SIZE(24, 40),
        .y_offset = 15,
    },
    [SPECIES_UNOWN_QMARK] =
    {
        .size = MON_COORDS_SIZE(24, 40),
        .y_offset = 13,
    },
};
// ===== END src/data/pokemon_graphics/front_pic_coordinates.h =====
// ===== BEGIN src/data/pokemon_graphics/front_pic_table.h =====
const struct CompressedSpriteSheet gMonFrontPicTable[] =
{
    SPECIES_SPRITE(NONE, gMonFrontPic_CircledQuestionMark),
    SPECIES_SPRITE(BULBASAUR, gMonFrontPic_Bulbasaur),
    SPECIES_SPRITE(IVYSAUR, gMonFrontPic_Ivysaur),
    SPECIES_SPRITE(VENUSAUR, gMonFrontPic_Venusaur),
    SPECIES_SPRITE(CHARMANDER, gMonFrontPic_Charmander),
    SPECIES_SPRITE(CHARMELEON, gMonFrontPic_Charmeleon),
    SPECIES_SPRITE(CHARIZARD, gMonFrontPic_Charizard),
    SPECIES_SPRITE(SQUIRTLE, gMonFrontPic_Squirtle),
    SPECIES_SPRITE(WARTORTLE, gMonFrontPic_Wartortle),
    SPECIES_SPRITE(BLASTOISE, gMonFrontPic_Blastoise),
    SPECIES_SPRITE(CATERPIE, gMonFrontPic_Caterpie),
    SPECIES_SPRITE(METAPOD, gMonFrontPic_Metapod),
    SPECIES_SPRITE(BUTTERFREE, gMonFrontPic_Butterfree),
    SPECIES_SPRITE(WEEDLE, gMonFrontPic_Weedle),
    SPECIES_SPRITE(KAKUNA, gMonFrontPic_Kakuna),
    SPECIES_SPRITE(BEEDRILL, gMonFrontPic_Beedrill),
    SPECIES_SPRITE(PIDGEY, gMonFrontPic_Pidgey),
    SPECIES_SPRITE(PIDGEOTTO, gMonFrontPic_Pidgeotto),
    SPECIES_SPRITE(PIDGEOT, gMonFrontPic_Pidgeot),
    SPECIES_SPRITE(RATTATA, gMonFrontPic_Rattata),
    SPECIES_SPRITE(RATICATE, gMonFrontPic_Raticate),
    SPECIES_SPRITE(SPEAROW, gMonFrontPic_Spearow),
    SPECIES_SPRITE(FEAROW, gMonFrontPic_Fearow),
    SPECIES_SPRITE(EKANS, gMonFrontPic_Ekans),
    SPECIES_SPRITE(ARBOK, gMonFrontPic_Arbok),
    SPECIES_SPRITE(PIKACHU, gMonFrontPic_Pikachu),
    SPECIES_SPRITE(RAICHU, gMonFrontPic_Raichu),
    SPECIES_SPRITE(SANDSHREW, gMonFrontPic_Sandshrew),
    SPECIES_SPRITE(SANDSLASH, gMonFrontPic_Sandslash),
    SPECIES_SPRITE(NIDORAN_F, gMonFrontPic_NidoranF),
    SPECIES_SPRITE(NIDORINA, gMonFrontPic_Nidorina),
    SPECIES_SPRITE(NIDOQUEEN, gMonFrontPic_Nidoqueen),
    SPECIES_SPRITE(NIDORAN_M, gMonFrontPic_NidoranM),
    SPECIES_SPRITE(NIDORINO, gMonFrontPic_Nidorino),
    SPECIES_SPRITE(NIDOKING, gMonFrontPic_Nidoking),
    SPECIES_SPRITE(CLEFAIRY, gMonFrontPic_Clefairy),
    SPECIES_SPRITE(CLEFABLE, gMonFrontPic_Clefable),
    SPECIES_SPRITE(VULPIX, gMonFrontPic_Vulpix),
    SPECIES_SPRITE(NINETALES, gMonFrontPic_Ninetales),
    SPECIES_SPRITE(JIGGLYPUFF, gMonFrontPic_Jigglypuff),
    SPECIES_SPRITE(WIGGLYTUFF, gMonFrontPic_Wigglytuff),
    SPECIES_SPRITE(ZUBAT, gMonFrontPic_Zubat),
    SPECIES_SPRITE(GOLBAT, gMonFrontPic_Golbat),
    SPECIES_SPRITE(ODDISH, gMonFrontPic_Oddish),
    SPECIES_SPRITE(GLOOM, gMonFrontPic_Gloom),
    SPECIES_SPRITE(VILEPLUME, gMonFrontPic_Vileplume),
    SPECIES_SPRITE(PARAS, gMonFrontPic_Paras),
    SPECIES_SPRITE(PARASECT, gMonFrontPic_Parasect),
    SPECIES_SPRITE(VENONAT, gMonFrontPic_Venonat),
    SPECIES_SPRITE(VENOMOTH, gMonFrontPic_Venomoth),
    SPECIES_SPRITE(DIGLETT, gMonFrontPic_Diglett),
    SPECIES_SPRITE(DUGTRIO, gMonFrontPic_Dugtrio),
    SPECIES_SPRITE(MEOWTH, gMonFrontPic_Meowth),
    SPECIES_SPRITE(PERSIAN, gMonFrontPic_Persian),
    SPECIES_SPRITE(PSYDUCK, gMonFrontPic_Psyduck),
    SPECIES_SPRITE(GOLDUCK, gMonFrontPic_Golduck),
    SPECIES_SPRITE(MANKEY, gMonFrontPic_Mankey),
    SPECIES_SPRITE(PRIMEAPE, gMonFrontPic_Primeape),
    SPECIES_SPRITE(GROWLITHE, gMonFrontPic_Growlithe),
    SPECIES_SPRITE(ARCANINE, gMonFrontPic_Arcanine),
    SPECIES_SPRITE(POLIWAG, gMonFrontPic_Poliwag),
    SPECIES_SPRITE(POLIWHIRL, gMonFrontPic_Poliwhirl),
    SPECIES_SPRITE(POLIWRATH, gMonFrontPic_Poliwrath),
    SPECIES_SPRITE(ABRA, gMonFrontPic_Abra),
    SPECIES_SPRITE(KADABRA, gMonFrontPic_Kadabra),
    SPECIES_SPRITE(ALAKAZAM, gMonFrontPic_Alakazam),
    SPECIES_SPRITE(MACHOP, gMonFrontPic_Machop),
    SPECIES_SPRITE(MACHOKE, gMonFrontPic_Machoke),
    SPECIES_SPRITE(MACHAMP, gMonFrontPic_Machamp),
    SPECIES_SPRITE(BELLSPROUT, gMonFrontPic_Bellsprout),
    SPECIES_SPRITE(WEEPINBELL, gMonFrontPic_Weepinbell),
    SPECIES_SPRITE(VICTREEBEL, gMonFrontPic_Victreebel),
    SPECIES_SPRITE(TENTACOOL, gMonFrontPic_Tentacool),
    SPECIES_SPRITE(TENTACRUEL, gMonFrontPic_Tentacruel),
    SPECIES_SPRITE(GEODUDE, gMonFrontPic_Geodude),
    SPECIES_SPRITE(GRAVELER, gMonFrontPic_Graveler),
    SPECIES_SPRITE(GOLEM, gMonFrontPic_Golem),
    SPECIES_SPRITE(PONYTA, gMonFrontPic_Ponyta),
    SPECIES_SPRITE(RAPIDASH, gMonFrontPic_Rapidash),
    SPECIES_SPRITE(SLOWPOKE, gMonFrontPic_Slowpoke),
    SPECIES_SPRITE(SLOWBRO, gMonFrontPic_Slowbro),
    SPECIES_SPRITE(MAGNEMITE, gMonFrontPic_Magnemite),
    SPECIES_SPRITE(MAGNETON, gMonFrontPic_Magneton),
    SPECIES_SPRITE(FARFETCHD, gMonFrontPic_Farfetchd),
    SPECIES_SPRITE(DODUO, gMonFrontPic_Doduo),
    SPECIES_SPRITE(DODRIO, gMonFrontPic_Dodrio),
    SPECIES_SPRITE(SEEL, gMonFrontPic_Seel),
    SPECIES_SPRITE(DEWGONG, gMonFrontPic_Dewgong),
    SPECIES_SPRITE(GRIMER, gMonFrontPic_Grimer),
    SPECIES_SPRITE(MUK, gMonFrontPic_Muk),
    SPECIES_SPRITE(SHELLDER, gMonFrontPic_Shellder),
    SPECIES_SPRITE(CLOYSTER, gMonFrontPic_Cloyster),
    SPECIES_SPRITE(GASTLY, gMonFrontPic_Gastly),
    SPECIES_SPRITE(HAUNTER, gMonFrontPic_Haunter),
    SPECIES_SPRITE(GENGAR, gMonFrontPic_Gengar),
    SPECIES_SPRITE(ONIX, gMonFrontPic_Onix),
    SPECIES_SPRITE(DROWZEE, gMonFrontPic_Drowzee),
    SPECIES_SPRITE(HYPNO, gMonFrontPic_Hypno),
    SPECIES_SPRITE(KRABBY, gMonFrontPic_Krabby),
    SPECIES_SPRITE(KINGLER, gMonFrontPic_Kingler),
    SPECIES_SPRITE(VOLTORB, gMonFrontPic_Voltorb),
    SPECIES_SPRITE(ELECTRODE, gMonFrontPic_Electrode),
    SPECIES_SPRITE(EXEGGCUTE, gMonFrontPic_Exeggcute),
    SPECIES_SPRITE(EXEGGUTOR, gMonFrontPic_Exeggutor),
    SPECIES_SPRITE(CUBONE, gMonFrontPic_Cubone),
    SPECIES_SPRITE(MAROWAK, gMonFrontPic_Marowak),
    SPECIES_SPRITE(HITMONLEE, gMonFrontPic_Hitmonlee),
    SPECIES_SPRITE(HITMONCHAN, gMonFrontPic_Hitmonchan),
    SPECIES_SPRITE(LICKITUNG, gMonFrontPic_Lickitung),
    SPECIES_SPRITE(KOFFING, gMonFrontPic_Koffing),
    SPECIES_SPRITE(WEEZING, gMonFrontPic_Weezing),
    SPECIES_SPRITE(RHYHORN, gMonFrontPic_Rhyhorn),
    SPECIES_SPRITE(RHYDON, gMonFrontPic_Rhydon),
    SPECIES_SPRITE(CHANSEY, gMonFrontPic_Chansey),
    SPECIES_SPRITE(TANGELA, gMonFrontPic_Tangela),
    SPECIES_SPRITE(KANGASKHAN, gMonFrontPic_Kangaskhan),
    SPECIES_SPRITE(HORSEA, gMonFrontPic_Horsea),
    SPECIES_SPRITE(SEADRA, gMonFrontPic_Seadra),
    SPECIES_SPRITE(GOLDEEN, gMonFrontPic_Goldeen),
    SPECIES_SPRITE(SEAKING, gMonFrontPic_Seaking),
    SPECIES_SPRITE(STARYU, gMonFrontPic_Staryu),
    SPECIES_SPRITE(STARMIE, gMonFrontPic_Starmie),
    SPECIES_SPRITE(MR_MIME, gMonFrontPic_Mrmime),
    SPECIES_SPRITE(SCYTHER, gMonFrontPic_Scyther),
    SPECIES_SPRITE(JYNX, gMonFrontPic_Jynx),
    SPECIES_SPRITE(ELECTABUZZ, gMonFrontPic_Electabuzz),
    SPECIES_SPRITE(MAGMAR, gMonFrontPic_Magmar),
    SPECIES_SPRITE(PINSIR, gMonFrontPic_Pinsir),
    SPECIES_SPRITE(TAUROS, gMonFrontPic_Tauros),
    SPECIES_SPRITE(MAGIKARP, gMonFrontPic_Magikarp),
    SPECIES_SPRITE(GYARADOS, gMonFrontPic_Gyarados),
    SPECIES_SPRITE(LAPRAS, gMonFrontPic_Lapras),
    SPECIES_SPRITE(DITTO, gMonFrontPic_Ditto),
    SPECIES_SPRITE(EEVEE, gMonFrontPic_Eevee),
    SPECIES_SPRITE(VAPOREON, gMonFrontPic_Vaporeon),
    SPECIES_SPRITE(JOLTEON, gMonFrontPic_Jolteon),
    SPECIES_SPRITE(FLAREON, gMonFrontPic_Flareon),
    SPECIES_SPRITE(PORYGON, gMonFrontPic_Porygon),
    SPECIES_SPRITE(OMANYTE, gMonFrontPic_Omanyte),
    SPECIES_SPRITE(OMASTAR, gMonFrontPic_Omastar),
    SPECIES_SPRITE(KABUTO, gMonFrontPic_Kabuto),
    SPECIES_SPRITE(KABUTOPS, gMonFrontPic_Kabutops),
    SPECIES_SPRITE(AERODACTYL, gMonFrontPic_Aerodactyl),
    SPECIES_SPRITE(SNORLAX, gMonFrontPic_Snorlax),
    SPECIES_SPRITE(ARTICUNO, gMonFrontPic_Articuno),
    SPECIES_SPRITE(ZAPDOS, gMonFrontPic_Zapdos),
    SPECIES_SPRITE(MOLTRES, gMonFrontPic_Moltres),
    SPECIES_SPRITE(DRATINI, gMonFrontPic_Dratini),
    SPECIES_SPRITE(DRAGONAIR, gMonFrontPic_Dragonair),
    SPECIES_SPRITE(DRAGONITE, gMonFrontPic_Dragonite),
    SPECIES_SPRITE(MEWTWO, gMonFrontPic_Mewtwo),
    SPECIES_SPRITE(MEW, gMonFrontPic_Mew),
    SPECIES_SPRITE(CHIKORITA, gMonFrontPic_Chikorita),
    SPECIES_SPRITE(BAYLEEF, gMonFrontPic_Bayleef),
    SPECIES_SPRITE(MEGANIUM, gMonFrontPic_Meganium),
    SPECIES_SPRITE(CYNDAQUIL, gMonFrontPic_Cyndaquil),
    SPECIES_SPRITE(QUILAVA, gMonFrontPic_Quilava),
    SPECIES_SPRITE(TYPHLOSION, gMonFrontPic_Typhlosion),
    SPECIES_SPRITE(TOTODILE, gMonFrontPic_Totodile),
    SPECIES_SPRITE(CROCONAW, gMonFrontPic_Croconaw),
    SPECIES_SPRITE(FERALIGATR, gMonFrontPic_Feraligatr),
    SPECIES_SPRITE(SENTRET, gMonFrontPic_Sentret),
    SPECIES_SPRITE(FURRET, gMonFrontPic_Furret),
    SPECIES_SPRITE(HOOTHOOT, gMonFrontPic_Hoothoot),
    SPECIES_SPRITE(NOCTOWL, gMonFrontPic_Noctowl),
    SPECIES_SPRITE(LEDYBA, gMonFrontPic_Ledyba),
    SPECIES_SPRITE(LEDIAN, gMonFrontPic_Ledian),
    SPECIES_SPRITE(SPINARAK, gMonFrontPic_Spinarak),
    SPECIES_SPRITE(ARIADOS, gMonFrontPic_Ariados),
    SPECIES_SPRITE(CROBAT, gMonFrontPic_Crobat),
    SPECIES_SPRITE(CHINCHOU, gMonFrontPic_Chinchou),
    SPECIES_SPRITE(LANTURN, gMonFrontPic_Lanturn),
    SPECIES_SPRITE(PICHU, gMonFrontPic_Pichu),
    SPECIES_SPRITE(CLEFFA, gMonFrontPic_Cleffa),
    SPECIES_SPRITE(IGGLYBUFF, gMonFrontPic_Igglybuff),
    SPECIES_SPRITE(TOGEPI, gMonFrontPic_Togepi),
    SPECIES_SPRITE(TOGETIC, gMonFrontPic_Togetic),
    SPECIES_SPRITE(NATU, gMonFrontPic_Natu),
    SPECIES_SPRITE(XATU, gMonFrontPic_Xatu),
    SPECIES_SPRITE(MAREEP, gMonFrontPic_Mareep),
    SPECIES_SPRITE(FLAAFFY, gMonFrontPic_Flaaffy),
    SPECIES_SPRITE(AMPHAROS, gMonFrontPic_Ampharos),
    SPECIES_SPRITE(BELLOSSOM, gMonFrontPic_Bellossom),
    SPECIES_SPRITE(MARILL, gMonFrontPic_Marill),
    SPECIES_SPRITE(AZUMARILL, gMonFrontPic_Azumarill),
    SPECIES_SPRITE(SUDOWOODO, gMonFrontPic_Sudowoodo),
    SPECIES_SPRITE(POLITOED, gMonFrontPic_Politoed),
    SPECIES_SPRITE(HOPPIP, gMonFrontPic_Hoppip),
    SPECIES_SPRITE(SKIPLOOM, gMonFrontPic_Skiploom),
    SPECIES_SPRITE(JUMPLUFF, gMonFrontPic_Jumpluff),
    SPECIES_SPRITE(AIPOM, gMonFrontPic_Aipom),
    SPECIES_SPRITE(SUNKERN, gMonFrontPic_Sunkern),
    SPECIES_SPRITE(SUNFLORA, gMonFrontPic_Sunflora),
    SPECIES_SPRITE(YANMA, gMonFrontPic_Yanma),
    SPECIES_SPRITE(WOOPER, gMonFrontPic_Wooper),
    SPECIES_SPRITE(QUAGSIRE, gMonFrontPic_Quagsire),
    SPECIES_SPRITE(ESPEON, gMonFrontPic_Espeon),
    SPECIES_SPRITE(UMBREON, gMonFrontPic_Umbreon),
    SPECIES_SPRITE(MURKROW, gMonFrontPic_Murkrow),
    SPECIES_SPRITE(SLOWKING, gMonFrontPic_Slowking),
    SPECIES_SPRITE(MISDREAVUS, gMonFrontPic_Misdreavus),
    SPECIES_SPRITE(UNOWN, gMonFrontPic_UnownA),
    SPECIES_SPRITE(WOBBUFFET, gMonFrontPic_Wobbuffet),
    SPECIES_SPRITE(GIRAFARIG, gMonFrontPic_Girafarig),
    SPECIES_SPRITE(PINECO, gMonFrontPic_Pineco),
    SPECIES_SPRITE(FORRETRESS, gMonFrontPic_Forretress),
    SPECIES_SPRITE(DUNSPARCE, gMonFrontPic_Dunsparce),
    SPECIES_SPRITE(GLIGAR, gMonFrontPic_Gligar),
    SPECIES_SPRITE(STEELIX, gMonFrontPic_Steelix),
    SPECIES_SPRITE(SNUBBULL, gMonFrontPic_Snubbull),
    SPECIES_SPRITE(GRANBULL, gMonFrontPic_Granbull),
    SPECIES_SPRITE(QWILFISH, gMonFrontPic_Qwilfish),
    SPECIES_SPRITE(SCIZOR, gMonFrontPic_Scizor),
    SPECIES_SPRITE(SHUCKLE, gMonFrontPic_Shuckle),
    SPECIES_SPRITE(HERACROSS, gMonFrontPic_Heracross),
    SPECIES_SPRITE(SNEASEL, gMonFrontPic_Sneasel),
    SPECIES_SPRITE(TEDDIURSA, gMonFrontPic_Teddiursa),
    SPECIES_SPRITE(URSARING, gMonFrontPic_Ursaring),
    SPECIES_SPRITE(SLUGMA, gMonFrontPic_Slugma),
    SPECIES_SPRITE(MAGCARGO, gMonFrontPic_Magcargo),
    SPECIES_SPRITE(SWINUB, gMonFrontPic_Swinub),
    SPECIES_SPRITE(PILOSWINE, gMonFrontPic_Piloswine),
    SPECIES_SPRITE(CORSOLA, gMonFrontPic_Corsola),
    SPECIES_SPRITE(REMORAID, gMonFrontPic_Remoraid),
    SPECIES_SPRITE(OCTILLERY, gMonFrontPic_Octillery),
    SPECIES_SPRITE(DELIBIRD, gMonFrontPic_Delibird),
    SPECIES_SPRITE(MANTINE, gMonFrontPic_Mantine),
    SPECIES_SPRITE(SKARMORY, gMonFrontPic_Skarmory),
    SPECIES_SPRITE(HOUNDOUR, gMonFrontPic_Houndour),
    SPECIES_SPRITE(HOUNDOOM, gMonFrontPic_Houndoom),
    SPECIES_SPRITE(KINGDRA, gMonFrontPic_Kingdra),
    SPECIES_SPRITE(PHANPY, gMonFrontPic_Phanpy),
    SPECIES_SPRITE(DONPHAN, gMonFrontPic_Donphan),
    SPECIES_SPRITE(PORYGON2, gMonFrontPic_Porygon2),
    SPECIES_SPRITE(STANTLER, gMonFrontPic_Stantler),
    SPECIES_SPRITE(SMEARGLE, gMonFrontPic_Smeargle),
    SPECIES_SPRITE(TYROGUE, gMonFrontPic_Tyrogue),
    SPECIES_SPRITE(HITMONTOP, gMonFrontPic_Hitmontop),
    SPECIES_SPRITE(SMOOCHUM, gMonFrontPic_Smoochum),
    SPECIES_SPRITE(ELEKID, gMonFrontPic_Elekid),
    SPECIES_SPRITE(MAGBY, gMonFrontPic_Magby),
    SPECIES_SPRITE(MILTANK, gMonFrontPic_Miltank),
    SPECIES_SPRITE(BLISSEY, gMonFrontPic_Blissey),
    SPECIES_SPRITE(RAIKOU, gMonFrontPic_Raikou),
    SPECIES_SPRITE(ENTEI, gMonFrontPic_Entei),
    SPECIES_SPRITE(SUICUNE, gMonFrontPic_Suicune),
    SPECIES_SPRITE(LARVITAR, gMonFrontPic_Larvitar),
    SPECIES_SPRITE(PUPITAR, gMonFrontPic_Pupitar),
    SPECIES_SPRITE(TYRANITAR, gMonFrontPic_Tyranitar),
    SPECIES_SPRITE(LUGIA, gMonFrontPic_Lugia),
    SPECIES_SPRITE(HO_OH, gMonFrontPic_HoOh),
    SPECIES_SPRITE(CELEBI, gMonFrontPic_Celebi),
    SPECIES_SPRITE(OLD_UNOWN_B, gMonFrontPic_DoubleQuestionMark),
    SPECIES_SPRITE(OLD_UNOWN_C, gMonFrontPic_DoubleQuestionMark),
    SPECIES_SPRITE(OLD_UNOWN_D, gMonFrontPic_DoubleQuestionMark),
    SPECIES_SPRITE(OLD_UNOWN_E, gMonFrontPic_DoubleQuestionMark),
    SPECIES_SPRITE(OLD_UNOWN_F, gMonFrontPic_DoubleQuestionMark),
    SPECIES_SPRITE(OLD_UNOWN_G, gMonFrontPic_DoubleQuestionMark),
    SPECIES_SPRITE(OLD_UNOWN_H, gMonFrontPic_DoubleQuestionMark),
    SPECIES_SPRITE(OLD_UNOWN_I, gMonFrontPic_DoubleQuestionMark),
    SPECIES_SPRITE(OLD_UNOWN_J, gMonFrontPic_DoubleQuestionMark),
    SPECIES_SPRITE(OLD_UNOWN_K, gMonFrontPic_DoubleQuestionMark),
    SPECIES_SPRITE(OLD_UNOWN_L, gMonFrontPic_DoubleQuestionMark),
    SPECIES_SPRITE(OLD_UNOWN_M, gMonFrontPic_DoubleQuestionMark),
    SPECIES_SPRITE(OLD_UNOWN_N, gMonFrontPic_DoubleQuestionMark),
    SPECIES_SPRITE(OLD_UNOWN_O, gMonFrontPic_DoubleQuestionMark),
    SPECIES_SPRITE(OLD_UNOWN_P, gMonFrontPic_DoubleQuestionMark),
    SPECIES_SPRITE(OLD_UNOWN_Q, gMonFrontPic_DoubleQuestionMark),
    SPECIES_SPRITE(OLD_UNOWN_R, gMonFrontPic_DoubleQuestionMark),
    SPECIES_SPRITE(OLD_UNOWN_S, gMonFrontPic_DoubleQuestionMark),
    SPECIES_SPRITE(OLD_UNOWN_T, gMonFrontPic_DoubleQuestionMark),
    SPECIES_SPRITE(OLD_UNOWN_U, gMonFrontPic_DoubleQuestionMark),
    SPECIES_SPRITE(OLD_UNOWN_V, gMonFrontPic_DoubleQuestionMark),
    SPECIES_SPRITE(OLD_UNOWN_W, gMonFrontPic_DoubleQuestionMark),
    SPECIES_SPRITE(OLD_UNOWN_X, gMonFrontPic_DoubleQuestionMark),
    SPECIES_SPRITE(OLD_UNOWN_Y, gMonFrontPic_DoubleQuestionMark),
    SPECIES_SPRITE(OLD_UNOWN_Z, gMonFrontPic_DoubleQuestionMark),
    SPECIES_SPRITE(TREECKO, gMonFrontPic_Treecko),
    SPECIES_SPRITE(GROVYLE, gMonFrontPic_Grovyle),
    SPECIES_SPRITE(SCEPTILE, gMonFrontPic_Sceptile),
    SPECIES_SPRITE(TORCHIC, gMonFrontPic_Torchic),
    SPECIES_SPRITE(COMBUSKEN, gMonFrontPic_Combusken),
    SPECIES_SPRITE(BLAZIKEN, gMonFrontPic_Blaziken),
    SPECIES_SPRITE(MUDKIP, gMonFrontPic_Mudkip),
    SPECIES_SPRITE(MARSHTOMP, gMonFrontPic_Marshtomp),
    SPECIES_SPRITE(SWAMPERT, gMonFrontPic_Swampert),
    SPECIES_SPRITE(POOCHYENA, gMonFrontPic_Poochyena),
    SPECIES_SPRITE(MIGHTYENA, gMonFrontPic_Mightyena),
    SPECIES_SPRITE(ZIGZAGOON, gMonFrontPic_Zigzagoon),
    SPECIES_SPRITE(LINOONE, gMonFrontPic_Linoone),
    SPECIES_SPRITE(WURMPLE, gMonFrontPic_Wurmple),
    SPECIES_SPRITE(SILCOON, gMonFrontPic_Silcoon),
    SPECIES_SPRITE(BEAUTIFLY, gMonFrontPic_Beautifly),
    SPECIES_SPRITE(CASCOON, gMonFrontPic_Cascoon),
    SPECIES_SPRITE(DUSTOX, gMonFrontPic_Dustox),
    SPECIES_SPRITE(LOTAD, gMonFrontPic_Lotad),
    SPECIES_SPRITE(LOMBRE, gMonFrontPic_Lombre),
    SPECIES_SPRITE(LUDICOLO, gMonFrontPic_Ludicolo),
    SPECIES_SPRITE(SEEDOT, gMonFrontPic_Seedot),
    SPECIES_SPRITE(NUZLEAF, gMonFrontPic_Nuzleaf),
    SPECIES_SPRITE(SHIFTRY, gMonFrontPic_Shiftry),
    SPECIES_SPRITE(NINCADA, gMonFrontPic_Nincada),
    SPECIES_SPRITE(NINJASK, gMonFrontPic_Ninjask),
    SPECIES_SPRITE(SHEDINJA, gMonFrontPic_Shedinja),
    SPECIES_SPRITE(TAILLOW, gMonFrontPic_Taillow),
    SPECIES_SPRITE(SWELLOW, gMonFrontPic_Swellow),
    SPECIES_SPRITE(SHROOMISH, gMonFrontPic_Shroomish),
    SPECIES_SPRITE(BRELOOM, gMonFrontPic_Breloom),
    SPECIES_SPRITE(SPINDA, gMonFrontPic_Spinda),
    SPECIES_SPRITE(WINGULL, gMonFrontPic_Wingull),
    SPECIES_SPRITE(PELIPPER, gMonFrontPic_Pelipper),
    SPECIES_SPRITE(SURSKIT, gMonFrontPic_Surskit),
    SPECIES_SPRITE(MASQUERAIN, gMonFrontPic_Masquerain),
    SPECIES_SPRITE(WAILMER, gMonFrontPic_Wailmer),
    SPECIES_SPRITE(WAILORD, gMonFrontPic_Wailord),
    SPECIES_SPRITE(SKITTY, gMonFrontPic_Skitty),
    SPECIES_SPRITE(DELCATTY, gMonFrontPic_Delcatty),
    SPECIES_SPRITE(KECLEON, gMonFrontPic_Kecleon),
    SPECIES_SPRITE(BALTOY, gMonFrontPic_Baltoy),
    SPECIES_SPRITE(CLAYDOL, gMonFrontPic_Claydol),
    SPECIES_SPRITE(NOSEPASS, gMonFrontPic_Nosepass),
    SPECIES_SPRITE(TORKOAL, gMonFrontPic_Torkoal),
    SPECIES_SPRITE(SABLEYE, gMonFrontPic_Sableye),
    SPECIES_SPRITE(BARBOACH, gMonFrontPic_Barboach),
    SPECIES_SPRITE(WHISCASH, gMonFrontPic_Whiscash),
    SPECIES_SPRITE(LUVDISC, gMonFrontPic_Luvdisc),
    SPECIES_SPRITE(CORPHISH, gMonFrontPic_Corphish),
    SPECIES_SPRITE(CRAWDAUNT, gMonFrontPic_Crawdaunt),
    SPECIES_SPRITE(FEEBAS, gMonFrontPic_Feebas),
    SPECIES_SPRITE(MILOTIC, gMonFrontPic_Milotic),
    SPECIES_SPRITE(CARVANHA, gMonFrontPic_Carvanha),
    SPECIES_SPRITE(SHARPEDO, gMonFrontPic_Sharpedo),
    SPECIES_SPRITE(TRAPINCH, gMonFrontPic_Trapinch),
    SPECIES_SPRITE(VIBRAVA, gMonFrontPic_Vibrava),
    SPECIES_SPRITE(FLYGON, gMonFrontPic_Flygon),
    SPECIES_SPRITE(MAKUHITA, gMonFrontPic_Makuhita),
    SPECIES_SPRITE(HARIYAMA, gMonFrontPic_Hariyama),
    SPECIES_SPRITE(ELECTRIKE, gMonFrontPic_Electrike),
    SPECIES_SPRITE(MANECTRIC, gMonFrontPic_Manectric),
    SPECIES_SPRITE(NUMEL, gMonFrontPic_Numel),
    SPECIES_SPRITE(CAMERUPT, gMonFrontPic_Camerupt),
    SPECIES_SPRITE(SPHEAL, gMonFrontPic_Spheal),
    SPECIES_SPRITE(SEALEO, gMonFrontPic_Sealeo),
    SPECIES_SPRITE(WALREIN, gMonFrontPic_Walrein),
    SPECIES_SPRITE(CACNEA, gMonFrontPic_Cacnea),
    SPECIES_SPRITE(CACTURNE, gMonFrontPic_Cacturne),
    SPECIES_SPRITE(SNORUNT, gMonFrontPic_Snorunt),
    SPECIES_SPRITE(GLALIE, gMonFrontPic_Glalie),
    SPECIES_SPRITE(LUNATONE, gMonFrontPic_Lunatone),
    SPECIES_SPRITE(SOLROCK, gMonFrontPic_Solrock),
    SPECIES_SPRITE(AZURILL, gMonFrontPic_Azurill),
    SPECIES_SPRITE(SPOINK, gMonFrontPic_Spoink),
    SPECIES_SPRITE(GRUMPIG, gMonFrontPic_Grumpig),
    SPECIES_SPRITE(PLUSLE, gMonFrontPic_Plusle),
    SPECIES_SPRITE(MINUN, gMonFrontPic_Minun),
    SPECIES_SPRITE(MAWILE, gMonFrontPic_Mawile),
    SPECIES_SPRITE(MEDITITE, gMonFrontPic_Meditite),
    SPECIES_SPRITE(MEDICHAM, gMonFrontPic_Medicham),
    SPECIES_SPRITE(SWABLU, gMonFrontPic_Swablu),
    SPECIES_SPRITE(ALTARIA, gMonFrontPic_Altaria),
    SPECIES_SPRITE(WYNAUT, gMonFrontPic_Wynaut),
    SPECIES_SPRITE(DUSKULL, gMonFrontPic_Duskull),
    SPECIES_SPRITE(DUSCLOPS, gMonFrontPic_Dusclops),
    SPECIES_SPRITE(ROSELIA, gMonFrontPic_Roselia),
    SPECIES_SPRITE(SLAKOTH, gMonFrontPic_Slakoth),
    SPECIES_SPRITE(VIGOROTH, gMonFrontPic_Vigoroth),
    SPECIES_SPRITE(SLAKING, gMonFrontPic_Slaking),
    SPECIES_SPRITE(GULPIN, gMonFrontPic_Gulpin),
    SPECIES_SPRITE(SWALOT, gMonFrontPic_Swalot),
    SPECIES_SPRITE(TROPIUS, gMonFrontPic_Tropius),
    SPECIES_SPRITE(WHISMUR, gMonFrontPic_Whismur),
    SPECIES_SPRITE(LOUDRED, gMonFrontPic_Loudred),
    SPECIES_SPRITE(EXPLOUD, gMonFrontPic_Exploud),
    SPECIES_SPRITE(CLAMPERL, gMonFrontPic_Clamperl),
    SPECIES_SPRITE(HUNTAIL, gMonFrontPic_Huntail),
    SPECIES_SPRITE(GOREBYSS, gMonFrontPic_Gorebyss),
    SPECIES_SPRITE(ABSOL, gMonFrontPic_Absol),
    SPECIES_SPRITE(SHUPPET, gMonFrontPic_Shuppet),
    SPECIES_SPRITE(BANETTE, gMonFrontPic_Banette),
    SPECIES_SPRITE(SEVIPER, gMonFrontPic_Seviper),
    SPECIES_SPRITE(ZANGOOSE, gMonFrontPic_Zangoose),
    SPECIES_SPRITE(RELICANTH, gMonFrontPic_Relicanth),
    SPECIES_SPRITE(ARON, gMonFrontPic_Aron),
    SPECIES_SPRITE(LAIRON, gMonFrontPic_Lairon),
    SPECIES_SPRITE(AGGRON, gMonFrontPic_Aggron),
    SPECIES_SPRITE(CASTFORM, gMonFrontPic_Castform),
    SPECIES_SPRITE(VOLBEAT, gMonFrontPic_Volbeat),
    SPECIES_SPRITE(ILLUMISE, gMonFrontPic_Illumise),
    SPECIES_SPRITE(LILEEP, gMonFrontPic_Lileep),
    SPECIES_SPRITE(CRADILY, gMonFrontPic_Cradily),
    SPECIES_SPRITE(ANORITH, gMonFrontPic_Anorith),
    SPECIES_SPRITE(ARMALDO, gMonFrontPic_Armaldo),
    SPECIES_SPRITE(RALTS, gMonFrontPic_Ralts),
    SPECIES_SPRITE(KIRLIA, gMonFrontPic_Kirlia),
    SPECIES_SPRITE(GARDEVOIR, gMonFrontPic_Gardevoir),
    SPECIES_SPRITE(BAGON, gMonFrontPic_Bagon),
    SPECIES_SPRITE(SHELGON, gMonFrontPic_Shelgon),
    SPECIES_SPRITE(SALAMENCE, gMonFrontPic_Salamence),
    SPECIES_SPRITE(BELDUM, gMonFrontPic_Beldum),
    SPECIES_SPRITE(METANG, gMonFrontPic_Metang),
    SPECIES_SPRITE(METAGROSS, gMonFrontPic_Metagross),
    SPECIES_SPRITE(REGIROCK, gMonFrontPic_Regirock),
    SPECIES_SPRITE(REGICE, gMonFrontPic_Regice),
    SPECIES_SPRITE(REGISTEEL, gMonFrontPic_Registeel),
    SPECIES_SPRITE(KYOGRE, gMonFrontPic_Kyogre),
    SPECIES_SPRITE(GROUDON, gMonFrontPic_Groudon),
    SPECIES_SPRITE(RAYQUAZA, gMonFrontPic_Rayquaza),
    SPECIES_SPRITE(LATIAS, gMonFrontPic_Latias),
    SPECIES_SPRITE(LATIOS, gMonFrontPic_Latios),
    SPECIES_SPRITE(JIRACHI, gMonFrontPic_Jirachi),
    SPECIES_SPRITE(DEOXYS, gMonFrontPic_Deoxys),
    SPECIES_SPRITE(CHIMECHO, gMonFrontPic_Chimecho),
    SPECIES_SPRITE(EGG, gMonFrontPic_Egg),
    SPECIES_SPRITE(UNOWN_B, gMonFrontPic_UnownB),
    SPECIES_SPRITE(UNOWN_C, gMonFrontPic_UnownC),
    SPECIES_SPRITE(UNOWN_D, gMonFrontPic_UnownD),
    SPECIES_SPRITE(UNOWN_E, gMonFrontPic_UnownE),
    SPECIES_SPRITE(UNOWN_F, gMonFrontPic_UnownF),
    SPECIES_SPRITE(UNOWN_G, gMonFrontPic_UnownG),
    SPECIES_SPRITE(UNOWN_H, gMonFrontPic_UnownH),
    SPECIES_SPRITE(UNOWN_I, gMonFrontPic_UnownI),
    SPECIES_SPRITE(UNOWN_J, gMonFrontPic_UnownJ),
    SPECIES_SPRITE(UNOWN_K, gMonFrontPic_UnownK),
    SPECIES_SPRITE(UNOWN_L, gMonFrontPic_UnownL),
    SPECIES_SPRITE(UNOWN_M, gMonFrontPic_UnownM),
    SPECIES_SPRITE(UNOWN_N, gMonFrontPic_UnownN),
    SPECIES_SPRITE(UNOWN_O, gMonFrontPic_UnownO),
    SPECIES_SPRITE(UNOWN_P, gMonFrontPic_UnownP),
    SPECIES_SPRITE(UNOWN_Q, gMonFrontPic_UnownQ),
    SPECIES_SPRITE(UNOWN_R, gMonFrontPic_UnownR),
    SPECIES_SPRITE(UNOWN_S, gMonFrontPic_UnownS),
    SPECIES_SPRITE(UNOWN_T, gMonFrontPic_UnownT),
    SPECIES_SPRITE(UNOWN_U, gMonFrontPic_UnownU),
    SPECIES_SPRITE(UNOWN_V, gMonFrontPic_UnownV),
    SPECIES_SPRITE(UNOWN_W, gMonFrontPic_UnownW),
    SPECIES_SPRITE(UNOWN_X, gMonFrontPic_UnownX),
    SPECIES_SPRITE(UNOWN_Y, gMonFrontPic_UnownY),
    SPECIES_SPRITE(UNOWN_Z, gMonFrontPic_UnownZ),
    SPECIES_SPRITE(UNOWN_EMARK, gMonFrontPic_UnownExclamationMark),
    SPECIES_SPRITE(UNOWN_QMARK, gMonFrontPic_UnownQuestionMark),
};
// ===== END src/data/pokemon_graphics/front_pic_table.h =====
// ===== BEGIN src/data/pokemon_graphics/back_pic_coordinates.h =====
const struct MonCoords gMonBackPicCoords[] =
{
    [SPECIES_NONE] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 0,
    },
    [SPECIES_BULBASAUR] =
    {
        .size = MON_COORDS_SIZE(48, 32),
        .y_offset = 16,
    },
    [SPECIES_IVYSAUR] =
    {
        .size = MON_COORDS_SIZE(56, 48),
        .y_offset = 10,
    },
    [SPECIES_VENUSAUR] =
    {
        .size = MON_COORDS_SIZE(64, 48),
        .y_offset = 10,
    },
    [SPECIES_CHARMANDER] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 10,
    },
    [SPECIES_CHARMELEON] =
    {
        .size = MON_COORDS_SIZE(56, 56),
        .y_offset = 7,
    },
    [SPECIES_CHARIZARD] =
    {
        .size = MON_COORDS_SIZE(64, 56),
        .y_offset = 4,
    },
    [SPECIES_SQUIRTLE] =
    {
        .size = MON_COORDS_SIZE(56, 40),
        .y_offset = 15,
    },
    [SPECIES_WARTORTLE] =
    {
        .size = MON_COORDS_SIZE(64, 48),
        .y_offset = 10,
    },
    [SPECIES_BLASTOISE] =
    {
        .size = MON_COORDS_SIZE(64, 48),
        .y_offset = 10,
    },
    [SPECIES_CATERPIE] =
    {
        .size = MON_COORDS_SIZE(40, 40),
        .y_offset = 15,
    },
    [SPECIES_METAPOD] =
    {
        .size = MON_COORDS_SIZE(48, 40),
        .y_offset = 12,
    },
    [SPECIES_BUTTERFREE] =
    {
        .size = MON_COORDS_SIZE(64, 56),
        .y_offset = 4,
    },
    [SPECIES_WEEDLE] =
    {
        .size = MON_COORDS_SIZE(40, 48),
        .y_offset = 11,
    },
    [SPECIES_KAKUNA] =
    {
        .size = MON_COORDS_SIZE(32, 48),
        .y_offset = 10,
    },
    [SPECIES_BEEDRILL] =
    {
        .size = MON_COORDS_SIZE(64, 48),
        .y_offset = 9,
    },
    [SPECIES_PIDGEY] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 8,
    },
    [SPECIES_PIDGEOTTO] =
    {
        .size = MON_COORDS_SIZE(64, 40),
        .y_offset = 12,
    },
    [SPECIES_PIDGEOT] =
    {
        .size = MON_COORDS_SIZE(64, 56),
        .y_offset = 6,
    },
    [SPECIES_RATTATA] =
    {
        .size = MON_COORDS_SIZE(56, 40),
        .y_offset = 13,
    },
    [SPECIES_RATICATE] =
    {
        .size = MON_COORDS_SIZE(56, 40),
        .y_offset = 13,
    },
    [SPECIES_SPEAROW] =
    {
        .size = MON_COORDS_SIZE(48, 40),
        .y_offset = 12,
    },
    [SPECIES_FEAROW] =
    {
        .size = MON_COORDS_SIZE(64, 56),
        .y_offset = 5,
    },
    [SPECIES_EKANS] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 9,
    },
    [SPECIES_ARBOK] =
    {
        .size = MON_COORDS_SIZE(56, 56),
        .y_offset = 4,
    },
    [SPECIES_PIKACHU] =
    {
        .size = MON_COORDS_SIZE(56, 56),
        .y_offset = 7,
    },
    [SPECIES_RAICHU] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 8,
    },
    [SPECIES_SANDSHREW] =
    {
        .size = MON_COORDS_SIZE(48, 40),
        .y_offset = 13,
    },
    [SPECIES_SANDSLASH] =
    {
        .size = MON_COORDS_SIZE(64, 48),
        .y_offset = 9,
    },
    [SPECIES_NIDORAN_F] =
    {
        .size = MON_COORDS_SIZE(40, 40),
        .y_offset = 12,
    },
    [SPECIES_NIDORINA] =
    {
        .size = MON_COORDS_SIZE(64, 48),
        .y_offset = 10,
    },
    [SPECIES_NIDOQUEEN] =
    {
        .size = MON_COORDS_SIZE(56, 56),
        .y_offset = 6,
    },
    [SPECIES_NIDORAN_M] =
    {
        .size = MON_COORDS_SIZE(40, 48),
        .y_offset = 8,
    },
    [SPECIES_NIDORINO] =
    {
        .size = MON_COORDS_SIZE(64, 48),
        .y_offset = 9,
    },
    [SPECIES_NIDOKING] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 3,
    },
    [SPECIES_CLEFAIRY] =
    {
        .size = MON_COORDS_SIZE(48, 40),
        .y_offset = 13,
    },
    [SPECIES_CLEFABLE] =
    {
        .size = MON_COORDS_SIZE(56, 48),
        .y_offset = 10,
    },
    [SPECIES_VULPIX] =
    {
        .size = MON_COORDS_SIZE(56, 48),
        .y_offset = 9,
    },
    [SPECIES_NINETALES] =
    {
        .size = MON_COORDS_SIZE(64, 56),
        .y_offset = 4,
    },
    [SPECIES_JIGGLYPUFF] =
    {
        .size = MON_COORDS_SIZE(48, 40),
        .y_offset = 13,
    },
    [SPECIES_WIGGLYTUFF] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 8,
    },
    [SPECIES_ZUBAT] =
    {
        .size = MON_COORDS_SIZE(56, 48),
        .y_offset = 11,
    },
    [SPECIES_GOLBAT] =
    {
        .size = MON_COORDS_SIZE(64, 56),
        .y_offset = 6,
    },
    [SPECIES_ODDISH] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 8,
    },
    [SPECIES_GLOOM] =
    {
        .size = MON_COORDS_SIZE(56, 48),
        .y_offset = 11,
    },
    [SPECIES_VILEPLUME] =
    {
        .size = MON_COORDS_SIZE(64, 56),
        .y_offset = 7,
    },
    [SPECIES_PARAS] =
    {
        .size = MON_COORDS_SIZE(48, 24),
        .y_offset = 20,
    },
    [SPECIES_PARASECT] =
    {
        .size = MON_COORDS_SIZE(64, 56),
        .y_offset = 7,
    },
    [SPECIES_VENONAT] =
    {
        .size = MON_COORDS_SIZE(56, 56),
        .y_offset = 6,
    },
    [SPECIES_VENOMOTH] =
    {
        .size = MON_COORDS_SIZE(56, 56),
        .y_offset = 4,
    },
    [SPECIES_DIGLETT] =
    {
        .size = MON_COORDS_SIZE(40, 32),
        .y_offset = 16,
    },
    [SPECIES_DUGTRIO] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 11,
    },
    [SPECIES_MEOWTH] =
    {
        .size = MON_COORDS_SIZE(48, 40),
        .y_offset = 12,
    },
    [SPECIES_PERSIAN] =
    {
        .size = MON_COORDS_SIZE(64, 56),
        .y_offset = 7,
    },
    [SPECIES_PSYDUCK] =
    {
        .size = MON_COORDS_SIZE(48, 56),
        .y_offset = 7,
    },
    [SPECIES_GOLDUCK] =
    {
        .size = MON_COORDS_SIZE(56, 56),
        .y_offset = 5,
    },
    [SPECIES_MANKEY] =
    {
        .size = MON_COORDS_SIZE(56, 48),
        .y_offset = 11,
    },
    [SPECIES_PRIMEAPE] =
    {
        .size = MON_COORDS_SIZE(56, 56),
        .y_offset = 7,
    },
    [SPECIES_GROWLITHE] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 8,
    },
    [SPECIES_ARCANINE] =
    {
        .size = MON_COORDS_SIZE(64, 56),
        .y_offset = 6,
    },
    [SPECIES_POLIWAG] =
    {
        .size = MON_COORDS_SIZE(56, 32),
        .y_offset = 16,
    },
    [SPECIES_POLIWHIRL] =
    {
        .size = MON_COORDS_SIZE(48, 40),
        .y_offset = 13,
    },
    [SPECIES_POLIWRATH] =
    {
        .size = MON_COORDS_SIZE(64, 48),
        .y_offset = 10,
    },
    [SPECIES_ABRA] =
    {
        .size = MON_COORDS_SIZE(40, 40),
        .y_offset = 12,
    },
    [SPECIES_KADABRA] =
    {
        .size = MON_COORDS_SIZE(64, 48),
        .y_offset = 9,
    },
    [SPECIES_ALAKAZAM] =
    {
        .size = MON_COORDS_SIZE(64, 56),
        .y_offset = 6,
    },
    [SPECIES_MACHOP] =
    {
        .size = MON_COORDS_SIZE(48, 40),
        .y_offset = 12,
    },
    [SPECIES_MACHOKE] =
    {
        .size = MON_COORDS_SIZE(56, 48),
        .y_offset = 9,
    },
    [SPECIES_MACHAMP] =
    {
        .size = MON_COORDS_SIZE(48, 56),
        .y_offset = 4,
    },
    [SPECIES_BELLSPROUT] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 10,
    },
    [SPECIES_WEEPINBELL] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 9,
    },
    [SPECIES_VICTREEBEL] =
    {
        .size = MON_COORDS_SIZE(64, 56),
        .y_offset = 6,
    },
    [SPECIES_TENTACOOL] =
    {
        .size = MON_COORDS_SIZE(40, 48),
        .y_offset = 10,
    },
    [SPECIES_TENTACRUEL] =
    {
        .size = MON_COORDS_SIZE(64, 48),
        .y_offset = 11,
    },
    [SPECIES_GEODUDE] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 11,
    },
    [SPECIES_GRAVELER] =
    {
        .size = MON_COORDS_SIZE(56, 40),
        .y_offset = 12,
    },
    [SPECIES_GOLEM] =
    {
        .size = MON_COORDS_SIZE(64, 32),
        .y_offset = 16,
    },
    [SPECIES_PONYTA] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 9,
    },
    [SPECIES_RAPIDASH] =
    {
        .size = MON_COORDS_SIZE(64, 56),
        .y_offset = 5,
    },
    [SPECIES_SLOWPOKE] =
    {
        .size = MON_COORDS_SIZE(64, 40),
        .y_offset = 14,
    },
    [SPECIES_SLOWBRO] =
    {
        .size = MON_COORDS_SIZE(64, 48),
        .y_offset = 10,
    },
    [SPECIES_MAGNEMITE] =
    {
        .size = MON_COORDS_SIZE(32, 24),
        .y_offset = 20,
    },
    [SPECIES_MAGNETON] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 10,
    },
    [SPECIES_FARFETCHD] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 10,
    },
    [SPECIES_DODUO] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 8,
    },
    [SPECIES_DODRIO] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 1,
    },
    [SPECIES_SEEL] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 10,
    },
    [SPECIES_DEWGONG] =
    {
        .size = MON_COORDS_SIZE(56, 56),
        .y_offset = 5,
    },
    [SPECIES_GRIMER] =
    {
        .size = MON_COORDS_SIZE(56, 40),
        .y_offset = 13,
    },
    [SPECIES_MUK] =
    {
        .size = MON_COORDS_SIZE(64, 40),
        .y_offset = 13,
    },
    [SPECIES_SHELLDER] =
    {
        .size = MON_COORDS_SIZE(56, 48),
        .y_offset = 11,
    },
    [SPECIES_CLOYSTER] =
    {
        .size = MON_COORDS_SIZE(64, 56),
        .y_offset = 6,
    },
    [SPECIES_GASTLY] =
    {
        .size = MON_COORDS_SIZE(64, 40),
        .y_offset = 14,
    },
    [SPECIES_HAUNTER] =
    {
        .size = MON_COORDS_SIZE(56, 48),
        .y_offset = 9,
    },
    [SPECIES_GENGAR] =
    {
        .size = MON_COORDS_SIZE(64, 48),
        .y_offset = 10,
    },
    [SPECIES_ONIX] =
    {
        .size = MON_COORDS_SIZE(56, 64),
        .y_offset = 0,
    },
    [SPECIES_DROWZEE] =
    {
        .size = MON_COORDS_SIZE(48, 40),
        .y_offset = 13,
    },
    [SPECIES_HYPNO] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 9,
    },
    [SPECIES_KRABBY] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 10,
    },
    [SPECIES_KINGLER] =
    {
        .size = MON_COORDS_SIZE(56, 56),
        .y_offset = 4,
    },
    [SPECIES_VOLTORB] =
    {
        .size = MON_COORDS_SIZE(40, 40),
        .y_offset = 14,
    },
    [SPECIES_ELECTRODE] =
    {
        .size = MON_COORDS_SIZE(48, 40),
        .y_offset = 13,
    },
    [SPECIES_EXEGGCUTE] =
    {
        .size = MON_COORDS_SIZE(48, 40),
        .y_offset = 13,
    },
    [SPECIES_EXEGGUTOR] =
    {
        .size = MON_COORDS_SIZE(64, 56),
        .y_offset = 7,
    },
    [SPECIES_CUBONE] =
    {
        .size = MON_COORDS_SIZE(56, 48),
        .y_offset = 10,
    },
    [SPECIES_MAROWAK] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 8,
    },
    [SPECIES_HITMONLEE] =
    {
        .size = MON_COORDS_SIZE(48, 40),
        .y_offset = 12,
    },
    [SPECIES_HITMONCHAN] =
    {
        .size = MON_COORDS_SIZE(48, 40),
        .y_offset = 12,
    },
    [SPECIES_LICKITUNG] =
    {
        .size = MON_COORDS_SIZE(64, 40),
        .y_offset = 14,
    },
    [SPECIES_KOFFING] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 9,
    },
    [SPECIES_WEEZING] =
    {
        .size = MON_COORDS_SIZE(64, 40),
        .y_offset = 12,
    },
    [SPECIES_RHYHORN] =
    {
        .size = MON_COORDS_SIZE(64, 40),
        .y_offset = 12,
    },
    [SPECIES_RHYDON] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 3,
    },
    [SPECIES_CHANSEY] =
    {
        .size = MON_COORDS_SIZE(64, 40),
        .y_offset = 14,
    },
    [SPECIES_TANGELA] =
    {
        .size = MON_COORDS_SIZE(64, 40),
        .y_offset = 14,
    },
    [SPECIES_KANGASKHAN] =
    {
        .size = MON_COORDS_SIZE(56, 56),
        .y_offset = 5,
    },
    [SPECIES_HORSEA] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 9,
    },
    [SPECIES_SEADRA] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 8,
    },
    [SPECIES_GOLDEEN] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 8,
    },
    [SPECIES_SEAKING] =
    {
        .size = MON_COORDS_SIZE(56, 48),
        .y_offset = 11,
    },
    [SPECIES_STARYU] =
    {
        .size = MON_COORDS_SIZE(56, 40),
        .y_offset = 13,
    },
    [SPECIES_STARMIE] =
    {
        .size = MON_COORDS_SIZE(64, 40),
        .y_offset = 14,
    },
    [SPECIES_MR_MIME] =
    {
        .size = MON_COORDS_SIZE(64, 40),
        .y_offset = 13,
    },
    [SPECIES_SCYTHER] =
    {
        .size = MON_COORDS_SIZE(64, 56),
        .y_offset = 4,
    },
    [SPECIES_JYNX] =
    {
        .size = MON_COORDS_SIZE(64, 40),
        .y_offset = 13,
    },
    [SPECIES_ELECTABUZZ] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 8,
    },
    [SPECIES_MAGMAR] =
    {
        .size = MON_COORDS_SIZE(56, 56),
        .y_offset = 7,
    },
    [SPECIES_PINSIR] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 9,
    },
    [SPECIES_TAUROS] =
    {
        .size = MON_COORDS_SIZE(64, 40),
        .y_offset = 13,
    },
    [SPECIES_MAGIKARP] =
    {
        .size = MON_COORDS_SIZE(56, 48),
        .y_offset = 9,
    },
    [SPECIES_GYARADOS] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 0,
    },
    [SPECIES_LAPRAS] =
    {
        .size = MON_COORDS_SIZE(56, 56),
        .y_offset = 4,
    },
    [SPECIES_DITTO] =
    {
        .size = MON_COORDS_SIZE(40, 32),
        .y_offset = 17,
    },
    [SPECIES_EEVEE] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 10,
    },
    [SPECIES_VAPOREON] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 10,
    },
    [SPECIES_JOLTEON] =
    {
        .size = MON_COORDS_SIZE(64, 56),
        .y_offset = 6,
    },
    [SPECIES_FLAREON] =
    {
        .size = MON_COORDS_SIZE(48, 56),
        .y_offset = 5,
    },
    [SPECIES_PORYGON] =
    {
        .size = MON_COORDS_SIZE(48, 40),
        .y_offset = 13,
    },
    [SPECIES_OMANYTE] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 10,
    },
    [SPECIES_OMASTAR] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 8,
    },
    [SPECIES_KABUTO] =
    {
        .size = MON_COORDS_SIZE(48, 40),
        .y_offset = 13,
    },
    [SPECIES_KABUTOPS] =
    {
        .size = MON_COORDS_SIZE(56, 56),
        .y_offset = 5,
    },
    [SPECIES_AERODACTYL] =
    {
        .size = MON_COORDS_SIZE(64, 48),
        .y_offset = 8,
    },
    [SPECIES_SNORLAX] =
    {
        .size = MON_COORDS_SIZE(64, 48),
        .y_offset = 11,
    },
    [SPECIES_ARTICUNO] =
    {
        .size = MON_COORDS_SIZE(48, 40),
        .y_offset = 12,
    },
    [SPECIES_ZAPDOS] =
    {
        .size = MON_COORDS_SIZE(56, 48),
        .y_offset = 11,
    },
    [SPECIES_MOLTRES] =
    {
        .size = MON_COORDS_SIZE(64, 56),
        .y_offset = 4,
    },
    [SPECIES_DRATINI] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 9,
    },
    [SPECIES_DRAGONAIR] =
    {
        .size = MON_COORDS_SIZE(56, 64),
        .y_offset = 0,
    },
    [SPECIES_DRAGONITE] =
    {
        .size = MON_COORDS_SIZE(64, 56),
        .y_offset = 6,
    },
    [SPECIES_MEWTWO] =
    {
        .size = MON_COORDS_SIZE(56, 64),
        .y_offset = 1,
    },
    [SPECIES_MEW] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 1,
    },
    [SPECIES_CHIKORITA] =
    {
        .size = MON_COORDS_SIZE(40, 48),
        .y_offset = 10,
    },
    [SPECIES_BAYLEEF] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 8,
    },
    [SPECIES_MEGANIUM] =
    {
        .size = MON_COORDS_SIZE(56, 64),
        .y_offset = 0,
    },
    [SPECIES_CYNDAQUIL] =
    {
        .size = MON_COORDS_SIZE(56, 48),
        .y_offset = 9,
    },
    [SPECIES_QUILAVA] =
    {
        .size = MON_COORDS_SIZE(64, 56),
        .y_offset = 4,
    },
    [SPECIES_TYPHLOSION] =
    {
        .size = MON_COORDS_SIZE(64, 56),
        .y_offset = 4,
    },
    [SPECIES_TOTODILE] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 11,
    },
    [SPECIES_CROCONAW] =
    {
        .size = MON_COORDS_SIZE(48, 56),
        .y_offset = 7,
    },
    [SPECIES_FERALIGATR] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 1,
    },
    [SPECIES_SENTRET] =
    {
        .size = MON_COORDS_SIZE(48, 56),
        .y_offset = 5,
    },
    [SPECIES_FURRET] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 8,
    },
    [SPECIES_HOOTHOOT] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 8,
    },
    [SPECIES_NOCTOWL] =
    {
        .size = MON_COORDS_SIZE(48, 64),
        .y_offset = 3,
    },
    [SPECIES_LEDYBA] =
    {
        .size = MON_COORDS_SIZE(56, 48),
        .y_offset = 11,
    },
    [SPECIES_LEDIAN] =
    {
        .size = MON_COORDS_SIZE(56, 56),
        .y_offset = 7,
    },
    [SPECIES_SPINARAK] =
    {
        .size = MON_COORDS_SIZE(56, 24),
        .y_offset = 21,
    },
    [SPECIES_ARIADOS] =
    {
        .size = MON_COORDS_SIZE(64, 48),
        .y_offset = 11,
    },
    [SPECIES_CROBAT] =
    {
        .size = MON_COORDS_SIZE(64, 56),
        .y_offset = 5,
    },
    [SPECIES_CHINCHOU] =
    {
        .size = MON_COORDS_SIZE(64, 48),
        .y_offset = 8,
    },
    [SPECIES_LANTURN] =
    {
        .size = MON_COORDS_SIZE(64, 48),
        .y_offset = 8,
    },
    [SPECIES_PICHU] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 11,
    },
    [SPECIES_CLEFFA] =
    {
        .size = MON_COORDS_SIZE(48, 40),
        .y_offset = 15,
    },
    [SPECIES_IGGLYBUFF] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 11,
    },
    [SPECIES_TOGEPI] =
    {
        .size = MON_COORDS_SIZE(40, 32),
        .y_offset = 16,
    },
    [SPECIES_TOGETIC] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 8,
    },
    [SPECIES_NATU] =
    {
        .size = MON_COORDS_SIZE(40, 32),
        .y_offset = 17,
    },
    [SPECIES_XATU] =
    {
        .size = MON_COORDS_SIZE(56, 48),
        .y_offset = 8,
    },
    [SPECIES_MAREEP] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 9,
    },
    [SPECIES_FLAAFFY] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 9,
    },
    [SPECIES_AMPHAROS] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 1,
    },
    [SPECIES_BELLOSSOM] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 11,
    },
    [SPECIES_MARILL] =
    {
        .size = MON_COORDS_SIZE(56, 40),
        .y_offset = 12,
    },
    [SPECIES_AZUMARILL] =
    {
        .size = MON_COORDS_SIZE(64, 48),
        .y_offset = 8,
    },
    [SPECIES_SUDOWOODO] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 8,
    },
    [SPECIES_POLITOED] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 9,
    },
    [SPECIES_HOPPIP] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 11,
    },
    [SPECIES_SKIPLOOM] =
    {
        .size = MON_COORDS_SIZE(48, 40),
        .y_offset = 13,
    },
    [SPECIES_JUMPLUFF] =
    {
        .size = MON_COORDS_SIZE(64, 56),
        .y_offset = 4,
    },
    [SPECIES_AIPOM] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 9,
    },
    [SPECIES_SUNKERN] =
    {
        .size = MON_COORDS_SIZE(40, 48),
        .y_offset = 10,
    },
    [SPECIES_SUNFLORA] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 8,
    },
    [SPECIES_YANMA] =
    {
        .size = MON_COORDS_SIZE(56, 56),
        .y_offset = 4,
    },
    [SPECIES_WOOPER] =
    {
        .size = MON_COORDS_SIZE(64, 40),
        .y_offset = 15,
    },
    [SPECIES_QUAGSIRE] =
    {
        .size = MON_COORDS_SIZE(56, 48),
        .y_offset = 8,
    },
    [SPECIES_ESPEON] =
    {
        .size = MON_COORDS_SIZE(56, 48),
        .y_offset = 11,
    },
    [SPECIES_UMBREON] =
    {
        .size = MON_COORDS_SIZE(64, 56),
        .y_offset = 4,
    },
    [SPECIES_MURKROW] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 9,
    },
    [SPECIES_SLOWKING] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 8,
    },
    [SPECIES_MISDREAVUS] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 10,
    },
    [SPECIES_UNOWN] =
    {
        .size = MON_COORDS_SIZE(24, 48),
        .y_offset = 8,
    },
    [SPECIES_WOBBUFFET] =
    {
        .size = MON_COORDS_SIZE(56, 40),
        .y_offset = 12,
    },
    [SPECIES_GIRAFARIG] =
    {
        .size = MON_COORDS_SIZE(64, 56),
        .y_offset = 5,
    },
    [SPECIES_PINECO] =
    {
        .size = MON_COORDS_SIZE(48, 40),
        .y_offset = 15,
    },
    [SPECIES_FORRETRESS] =
    {
        .size = MON_COORDS_SIZE(64, 32),
        .y_offset = 16,
    },
    [SPECIES_DUNSPARCE] =
    {
        .size = MON_COORDS_SIZE(64, 40),
        .y_offset = 15,
    },
    [SPECIES_GLIGAR] =
    {
        .size = MON_COORDS_SIZE(64, 56),
        .y_offset = 5,
    },
    [SPECIES_STEELIX] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 0,
    },
    [SPECIES_SNUBBULL] =
    {
        .size = MON_COORDS_SIZE(56, 48),
        .y_offset = 10,
    },
    [SPECIES_GRANBULL] =
    {
        .size = MON_COORDS_SIZE(64, 56),
        .y_offset = 5,
    },
    [SPECIES_QWILFISH] =
    {
        .size = MON_COORDS_SIZE(56, 56),
        .y_offset = 7,
    },
    [SPECIES_SCIZOR] =
    {
        .size = MON_COORDS_SIZE(56, 56),
        .y_offset = 4,
    },
    [SPECIES_SHUCKLE] =
    {
        .size = MON_COORDS_SIZE(40, 48),
        .y_offset = 11,
    },
    [SPECIES_HERACROSS] =
    {
        .size = MON_COORDS_SIZE(56, 56),
        .y_offset = 4,
    },
    [SPECIES_SNEASEL] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 8,
    },
    [SPECIES_TEDDIURSA] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 8,
    },
    [SPECIES_URSARING] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 3,
    },
    [SPECIES_SLUGMA] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 8,
    },
    [SPECIES_MAGCARGO] =
    {
        .size = MON_COORDS_SIZE(56, 48),
        .y_offset = 9,
    },
    [SPECIES_SWINUB] =
    {
        .size = MON_COORDS_SIZE(48, 24),
        .y_offset = 21,
    },
    [SPECIES_PILOSWINE] =
    {
        .size = MON_COORDS_SIZE(56, 40),
        .y_offset = 13,
    },
    [SPECIES_CORSOLA] =
    {
        .size = MON_COORDS_SIZE(48, 40),
        .y_offset = 12,
    },
    [SPECIES_REMORAID] =
    {
        .size = MON_COORDS_SIZE(56, 40),
        .y_offset = 13,
    },
    [SPECIES_OCTILLERY] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 10,
    },
    [SPECIES_DELIBIRD] =
    {
        .size = MON_COORDS_SIZE(48, 56),
        .y_offset = 6,
    },
    [SPECIES_MANTINE] =
    {
        .size = MON_COORDS_SIZE(64, 56),
        .y_offset = 7,
    },
    [SPECIES_SKARMORY] =
    {
        .size = MON_COORDS_SIZE(64, 56),
        .y_offset = 4,
    },
    [SPECIES_HOUNDOUR] =
    {
        .size = MON_COORDS_SIZE(40, 40),
        .y_offset = 12,
    },
    [SPECIES_HOUNDOOM] =
    {
        .size = MON_COORDS_SIZE(64, 56),
        .y_offset = 7,
    },
    [SPECIES_KINGDRA] =
    {
        .size = MON_COORDS_SIZE(64, 56),
        .y_offset = 6,
    },
    [SPECIES_PHANPY] =
    {
        .size = MON_COORDS_SIZE(48, 40),
        .y_offset = 14,
    },
    [SPECIES_DONPHAN] =
    {
        .size = MON_COORDS_SIZE(64, 40),
        .y_offset = 13,
    },
    [SPECIES_PORYGON2] =
    {
        .size = MON_COORDS_SIZE(56, 48),
        .y_offset = 10,
    },
    [SPECIES_STANTLER] =
    {
        .size = MON_COORDS_SIZE(56, 64),
        .y_offset = 3,
    },
    [SPECIES_SMEARGLE] =
    {
        .size = MON_COORDS_SIZE(56, 48),
        .y_offset = 10,
    },
    [SPECIES_TYROGUE] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 8,
    },
    [SPECIES_HITMONTOP] =
    {
        .size = MON_COORDS_SIZE(64, 56),
        .y_offset = 5,
    },
    [SPECIES_SMOOCHUM] =
    {
        .size = MON_COORDS_SIZE(40, 48),
        .y_offset = 9,
    },
    [SPECIES_ELEKID] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 8,
    },
    [SPECIES_MAGBY] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 11,
    },
    [SPECIES_MILTANK] =
    {
        .size = MON_COORDS_SIZE(64, 56),
        .y_offset = 7,
    },
    [SPECIES_BLISSEY] =
    {
        .size = MON_COORDS_SIZE(64, 40),
        .y_offset = 13,
    },
    [SPECIES_RAIKOU] =
    {
        .size = MON_COORDS_SIZE(64, 48),
        .y_offset = 10,
    },
    [SPECIES_ENTEI] =
    {
        .size = MON_COORDS_SIZE(64, 56),
        .y_offset = 6,
    },
    [SPECIES_SUICUNE] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 3,
    },
    [SPECIES_LARVITAR] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 8,
    },
    [SPECIES_PUPITAR] =
    {
        .size = MON_COORDS_SIZE(48, 56),
        .y_offset = 5,
    },
    [SPECIES_TYRANITAR] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 0,
    },
    [SPECIES_LUGIA] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 1,
    },
    [SPECIES_HO_OH] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 1,
    },
    [SPECIES_CELEBI] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 8,
    },
    [SPECIES_OLD_UNOWN_B] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 1,
    },
    [SPECIES_OLD_UNOWN_C] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 1,
    },
    [SPECIES_OLD_UNOWN_D] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 1,
    },
    [SPECIES_OLD_UNOWN_E] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 1,
    },
    [SPECIES_OLD_UNOWN_F] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 1,
    },
    [SPECIES_OLD_UNOWN_G] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 1,
    },
    [SPECIES_OLD_UNOWN_H] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 1,
    },
    [SPECIES_OLD_UNOWN_I] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 1,
    },
    [SPECIES_OLD_UNOWN_J] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 1,
    },
    [SPECIES_OLD_UNOWN_K] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 1,
    },
    [SPECIES_OLD_UNOWN_L] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 1,
    },
    [SPECIES_OLD_UNOWN_M] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 1,
    },
    [SPECIES_OLD_UNOWN_N] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 1,
    },
    [SPECIES_OLD_UNOWN_O] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 1,
    },
    [SPECIES_OLD_UNOWN_P] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 1,
    },
    [SPECIES_OLD_UNOWN_Q] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 1,
    },
    [SPECIES_OLD_UNOWN_R] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 1,
    },
    [SPECIES_OLD_UNOWN_S] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 1,
    },
    [SPECIES_OLD_UNOWN_T] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 1,
    },
    [SPECIES_OLD_UNOWN_U] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 1,
    },
    [SPECIES_OLD_UNOWN_V] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 1,
    },
    [SPECIES_OLD_UNOWN_W] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 1,
    },
    [SPECIES_OLD_UNOWN_X] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 1,
    },
    [SPECIES_OLD_UNOWN_Y] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 1,
    },
    [SPECIES_OLD_UNOWN_Z] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 1,
    },
    [SPECIES_TREECKO] =
    {
        .size = MON_COORDS_SIZE(64, 56),
        .y_offset = 6,
    },
    [SPECIES_GROVYLE] =
    {
        .size = MON_COORDS_SIZE(64, 48),
        .y_offset = 8,
    },
    [SPECIES_SCEPTILE] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 1,
    },
    [SPECIES_TORCHIC] =
    {
        .size = MON_COORDS_SIZE(48, 56),
        .y_offset = 5,
    },
    [SPECIES_COMBUSKEN] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 0,
    },
    [SPECIES_BLAZIKEN] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 0,
    },
    [SPECIES_MUDKIP] =
    {
        .size = MON_COORDS_SIZE(56, 56),
        .y_offset = 5,
    },
    [SPECIES_MARSHTOMP] =
    {
        .size = MON_COORDS_SIZE(64, 56),
        .y_offset = 4,
    },
    [SPECIES_SWAMPERT] =
    {
        .size = MON_COORDS_SIZE(64, 56),
        .y_offset = 5,
    },
    [SPECIES_POOCHYENA] =
    {
        .size = MON_COORDS_SIZE(56, 48),
        .y_offset = 9,
    },
    [SPECIES_MIGHTYENA] =
    {
        .size = MON_COORDS_SIZE(64, 56),
        .y_offset = 4,
    },
    [SPECIES_ZIGZAGOON] =
    {
        .size = MON_COORDS_SIZE(56, 48),
        .y_offset = 11,
    },
    [SPECIES_LINOONE] =
    {
        .size = MON_COORDS_SIZE(64, 40),
        .y_offset = 15,
    },
    [SPECIES_WURMPLE] =
    {
        .size = MON_COORDS_SIZE(56, 48),
        .y_offset = 11,
    },
    [SPECIES_SILCOON] =
    {
        .size = MON_COORDS_SIZE(64, 24),
        .y_offset = 21,
    },
    [SPECIES_BEAUTIFLY] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 0,
    },
    [SPECIES_CASCOON] =
    {
        .size = MON_COORDS_SIZE(56, 24),
        .y_offset = 20,
    },
    [SPECIES_DUSTOX] =
    {
        .size = MON_COORDS_SIZE(64, 24),
        .y_offset = 20,
    },
    [SPECIES_LOTAD] =
    {
        .size = MON_COORDS_SIZE(56, 40),
        .y_offset = 15,
    },
    [SPECIES_LOMBRE] =
    {
        .size = MON_COORDS_SIZE(64, 48),
        .y_offset = 8,
    },
    [SPECIES_LUDICOLO] =
    {
        .size = MON_COORDS_SIZE(64, 48),
        .y_offset = 10,
    },
    [SPECIES_SEEDOT] =
    {
        .size = MON_COORDS_SIZE(64, 48),
        .y_offset = 9,
    },
    [SPECIES_NUZLEAF] =
    {
        .size = MON_COORDS_SIZE(56, 48),
        .y_offset = 10,
    },
    [SPECIES_SHIFTRY] =
    {
        .size = MON_COORDS_SIZE(64, 48),
        .y_offset = 8,
    },
    [SPECIES_NINCADA] =
    {
        .size = MON_COORDS_SIZE(64, 24),
        .y_offset = 20,
    },
    [SPECIES_NINJASK] =
    {
        .size = MON_COORDS_SIZE(64, 48),
        .y_offset = 8,
    },
    [SPECIES_SHEDINJA] =
    {
        .size = MON_COORDS_SIZE(56, 56),
        .y_offset = 6,
    },
    [SPECIES_TAILLOW] =
    {
        .size = MON_COORDS_SIZE(48, 32),
        .y_offset = 17,
    },
    [SPECIES_SWELLOW] =
    {
        .size = MON_COORDS_SIZE(64, 48),
        .y_offset = 8,
    },
    [SPECIES_SHROOMISH] =
    {
        .size = MON_COORDS_SIZE(64, 40),
        .y_offset = 13,
    },
    [SPECIES_BRELOOM] =
    {
        .size = MON_COORDS_SIZE(64, 56),
        .y_offset = 4,
    },
    [SPECIES_SPINDA] =
    {
        .size = MON_COORDS_SIZE(56, 56),
        .y_offset = 4,
    },
    [SPECIES_WINGULL] =
    {
        .size = MON_COORDS_SIZE(64, 40),
        .y_offset = 14,
    },
    [SPECIES_PELIPPER] =
    {
        .size = MON_COORDS_SIZE(64, 56),
        .y_offset = 6,
    },
    [SPECIES_SURSKIT] =
    {
        .size = MON_COORDS_SIZE(64, 48),
        .y_offset = 11,
    },
    [SPECIES_MASQUERAIN] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 0,
    },
    [SPECIES_WAILMER] =
    {
        .size = MON_COORDS_SIZE(64, 24),
        .y_offset = 21,
    },
    [SPECIES_WAILORD] =
    {
        .size = MON_COORDS_SIZE(64, 24),
        .y_offset = 22,
    },
    [SPECIES_SKITTY] =
    {
        .size = MON_COORDS_SIZE(64, 48),
        .y_offset = 10,
    },
    [SPECIES_DELCATTY] =
    {
        .size = MON_COORDS_SIZE(64, 48),
        .y_offset = 8,
    },
    [SPECIES_KECLEON] =
    {
        .size = MON_COORDS_SIZE(64, 56),
        .y_offset = 6,
    },
    [SPECIES_BALTOY] =
    {
        .size = MON_COORDS_SIZE(64, 48),
        .y_offset = 8,
    },
    [SPECIES_CLAYDOL] =
    {
        .size = MON_COORDS_SIZE(64, 56),
        .y_offset = 7,
    },
    [SPECIES_NOSEPASS] =
    {
        .size = MON_COORDS_SIZE(64, 40),
        .y_offset = 12,
    },
    [SPECIES_TORKOAL] =
    {
        .size = MON_COORDS_SIZE(64, 48),
        .y_offset = 10,
    },
    [SPECIES_SABLEYE] =
    {
        .size = MON_COORDS_SIZE(56, 48),
        .y_offset = 8,
    },
    [SPECIES_BARBOACH] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 10,
    },
    [SPECIES_WHISCASH] =
    {
        .size = MON_COORDS_SIZE(64, 48),
        .y_offset = 10,
    },
    [SPECIES_LUVDISC] =
    {
        .size = MON_COORDS_SIZE(32, 48),
        .y_offset = 10,
    },
    [SPECIES_CORPHISH] =
    {
        .size = MON_COORDS_SIZE(56, 56),
        .y_offset = 7,
    },
    [SPECIES_CRAWDAUNT] =
    {
        .size = MON_COORDS_SIZE(64, 56),
        .y_offset = 5,
    },
    [SPECIES_FEEBAS] =
    {
        .size = MON_COORDS_SIZE(48, 56),
        .y_offset = 7,
    },
    [SPECIES_MILOTIC] =
    {
        .size = MON_COORDS_SIZE(48, 64),
        .y_offset = 2,
    },
    [SPECIES_CARVANHA] =
    {
        .size = MON_COORDS_SIZE(64, 56),
        .y_offset = 7,
    },
    [SPECIES_SHARPEDO] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 2,
    },
    [SPECIES_TRAPINCH] =
    {
        .size = MON_COORDS_SIZE(56, 40),
        .y_offset = 14,
    },
    [SPECIES_VIBRAVA] =
    {
        .size = MON_COORDS_SIZE(56, 32),
        .y_offset = 17,
    },
    [SPECIES_FLYGON] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 2,
    },
    [SPECIES_MAKUHITA] =
    {
        .size = MON_COORDS_SIZE(56, 48),
        .y_offset = 11,
    },
    [SPECIES_HARIYAMA] =
    {
        .size = MON_COORDS_SIZE(64, 56),
        .y_offset = 7,
    },
    [SPECIES_ELECTRIKE] =
    {
        .size = MON_COORDS_SIZE(64, 32),
        .y_offset = 16,
    },
    [SPECIES_MANECTRIC] =
    {
        .size = MON_COORDS_SIZE(64, 56),
        .y_offset = 4,
    },
    [SPECIES_NUMEL] =
    {
        .size = MON_COORDS_SIZE(64, 48),
        .y_offset = 11,
    },
    [SPECIES_CAMERUPT] =
    {
        .size = MON_COORDS_SIZE(64, 32),
        .y_offset = 19,
    },
    [SPECIES_SPHEAL] =
    {
        .size = MON_COORDS_SIZE(48, 32),
        .y_offset = 18,
    },
    [SPECIES_SEALEO] =
    {
        .size = MON_COORDS_SIZE(64, 48),
        .y_offset = 10,
    },
    [SPECIES_WALREIN] =
    {
        .size = MON_COORDS_SIZE(64, 56),
        .y_offset = 6,
    },
    [SPECIES_CACNEA] =
    {
        .size = MON_COORDS_SIZE(64, 40),
        .y_offset = 15,
    },
    [SPECIES_CACTURNE] =
    {
        .size = MON_COORDS_SIZE(64, 56),
        .y_offset = 7,
    },
    [SPECIES_SNORUNT] =
    {
        .size = MON_COORDS_SIZE(56, 48),
        .y_offset = 10,
    },
    [SPECIES_GLALIE] =
    {
        .size = MON_COORDS_SIZE(64, 40),
        .y_offset = 12,
    },
    [SPECIES_LUNATONE] =
    {
        .size = MON_COORDS_SIZE(64, 56),
        .y_offset = 5,
    },
    [SPECIES_SOLROCK] =
    {
        .size = MON_COORDS_SIZE(64, 56),
        .y_offset = 5,
    },
    [SPECIES_AZURILL] =
    {
        .size = MON_COORDS_SIZE(64, 48),
        .y_offset = 10,
    },
    [SPECIES_SPOINK] =
    {
        .size = MON_COORDS_SIZE(40, 48),
        .y_offset = 11,
    },
    [SPECIES_GRUMPIG] =
    {
        .size = MON_COORDS_SIZE(64, 56),
        .y_offset = 4,
    },
    [SPECIES_PLUSLE] =
    {
        .size = MON_COORDS_SIZE(56, 48),
        .y_offset = 8,
    },
    [SPECIES_MINUN] =
    {
        .size = MON_COORDS_SIZE(56, 48),
        .y_offset = 8,
    },
    [SPECIES_MAWILE] =
    {
        .size = MON_COORDS_SIZE(64, 56),
        .y_offset = 4,
    },
    [SPECIES_MEDITITE] =
    {
        .size = MON_COORDS_SIZE(56, 48),
        .y_offset = 11,
    },
    [SPECIES_MEDICHAM] =
    {
        .size = MON_COORDS_SIZE(48, 64),
        .y_offset = 3,
    },
    [SPECIES_SWABLU] =
    {
        .size = MON_COORDS_SIZE(64, 48),
        .y_offset = 9,
    },
    [SPECIES_ALTARIA] =
    {
        .size = MON_COORDS_SIZE(64, 56),
        .y_offset = 6,
    },
    [SPECIES_WYNAUT] =
    {
        .size = MON_COORDS_SIZE(56, 56),
        .y_offset = 7,
    },
    [SPECIES_DUSKULL] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 11,
    },
    [SPECIES_DUSCLOPS] =
    {
        .size = MON_COORDS_SIZE(64, 48),
        .y_offset = 8,
    },
    [SPECIES_ROSELIA] =
    {
        .size = MON_COORDS_SIZE(64, 48),
        .y_offset = 8,
    },
    [SPECIES_SLAKOTH] =
    {
        .size = MON_COORDS_SIZE(64, 40),
        .y_offset = 15,
    },
    [SPECIES_VIGOROTH] =
    {
        .size = MON_COORDS_SIZE(64, 48),
        .y_offset = 10,
    },
    [SPECIES_SLAKING] =
    {
        .size = MON_COORDS_SIZE(64, 48),
        .y_offset = 8,
    },
    [SPECIES_GULPIN] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 11,
    },
    [SPECIES_SWALOT] =
    {
        .size = MON_COORDS_SIZE(56, 56),
        .y_offset = 6,
    },
    [SPECIES_TROPIUS] =
    {
        .size = MON_COORDS_SIZE(64, 56),
        .y_offset = 7,
    },
    [SPECIES_WHISMUR] =
    {
        .size = MON_COORDS_SIZE(64, 40),
        .y_offset = 13,
    },
    [SPECIES_LOUDRED] =
    {
        .size = MON_COORDS_SIZE(64, 48),
        .y_offset = 9,
    },
    [SPECIES_EXPLOUD] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 3,
    },
    [SPECIES_CLAMPERL] =
    {
        .size = MON_COORDS_SIZE(64, 40),
        .y_offset = 13,
    },
    [SPECIES_HUNTAIL] =
    {
        .size = MON_COORDS_SIZE(48, 64),
        .y_offset = 2,
    },
    [SPECIES_GOREBYSS] =
    {
        .size = MON_COORDS_SIZE(56, 56),
        .y_offset = 5,
    },
    [SPECIES_ABSOL] =
    {
        .size = MON_COORDS_SIZE(56, 64),
        .y_offset = 3,
    },
    [SPECIES_SHUPPET] =
    {
        .size = MON_COORDS_SIZE(56, 56),
        .y_offset = 6,
    },
    [SPECIES_BANETTE] =
    {
        .size = MON_COORDS_SIZE(48, 40),
        .y_offset = 12,
    },
    [SPECIES_SEVIPER] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 3,
    },
    [SPECIES_ZANGOOSE] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 1,
    },
    [SPECIES_RELICANTH] =
    {
        .size = MON_COORDS_SIZE(64, 48),
        .y_offset = 10,
    },
    [SPECIES_ARON] =
    {
        .size = MON_COORDS_SIZE(40, 32),
        .y_offset = 17,
    },
    [SPECIES_LAIRON] =
    {
        .size = MON_COORDS_SIZE(64, 32),
        .y_offset = 17,
    },
    [SPECIES_AGGRON] =
    {
        .size = MON_COORDS_SIZE(64, 56),
        .y_offset = 7,
    },
    [SPECIES_CASTFORM] =
    {
        .size = MON_COORDS_SIZE(32, 40),
        .y_offset = 13,
    },
    [SPECIES_VOLBEAT] =
    {
        .size = MON_COORDS_SIZE(56, 48),
        .y_offset = 8,
    },
    [SPECIES_ILLUMISE] =
    {
        .size = MON_COORDS_SIZE(48, 56),
        .y_offset = 6,
    },
    [SPECIES_LILEEP] =
    {
        .size = MON_COORDS_SIZE(64, 48),
        .y_offset = 9,
    },
    [SPECIES_CRADILY] =
    {
        .size = MON_COORDS_SIZE(56, 56),
        .y_offset = 4,
    },
    [SPECIES_ANORITH] =
    {
        .size = MON_COORDS_SIZE(64, 24),
        .y_offset = 23,
    },
    [SPECIES_ARMALDO] =
    {
        .size = MON_COORDS_SIZE(56, 56),
        .y_offset = 5,
    },
    [SPECIES_RALTS] =
    {
        .size = MON_COORDS_SIZE(32, 40),
        .y_offset = 13,
    },
    [SPECIES_KIRLIA] =
    {
        .size = MON_COORDS_SIZE(40, 56),
        .y_offset = 6,
    },
    [SPECIES_GARDEVOIR] =
    {
        .size = MON_COORDS_SIZE(56, 56),
        .y_offset = 4,
    },
    [SPECIES_BAGON] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 8,
    },
    [SPECIES_SHELGON] =
    {
        .size = MON_COORDS_SIZE(64, 40),
        .y_offset = 13,
    },
    [SPECIES_SALAMENCE] =
    {
        .size = MON_COORDS_SIZE(56, 56),
        .y_offset = 6,
    },
    [SPECIES_BELDUM] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 10,
    },
    [SPECIES_METANG] =
    {
        .size = MON_COORDS_SIZE(64, 32),
        .y_offset = 16,
    },
    [SPECIES_METAGROSS] =
    {
        .size = MON_COORDS_SIZE(64, 24),
        .y_offset = 20,
    },
    [SPECIES_REGIROCK] =
    {
        .size = MON_COORDS_SIZE(64, 48),
        .y_offset = 10,
    },
    [SPECIES_REGICE] =
    {
        .size = MON_COORDS_SIZE(64, 40),
        .y_offset = 14,
    },
    [SPECIES_REGISTEEL] =
    {
        .size = MON_COORDS_SIZE(64, 40),
        .y_offset = 14,
    },
    [SPECIES_KYOGRE] =
    {
        .size = MON_COORDS_SIZE(64, 32),
        .y_offset = 19,
    },
    [SPECIES_GROUDON] =
    {
        .size = MON_COORDS_SIZE(64, 56),
        .y_offset = 7,
    },
    [SPECIES_RAYQUAZA] =
    {
        .size = MON_COORDS_SIZE(56, 64),
        .y_offset = 0,
    },
    [SPECIES_LATIAS] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 2,
    },
    [SPECIES_LATIOS] =
    {
        .size = MON_COORDS_SIZE(64, 64),
        .y_offset = 3,
    },
    [SPECIES_JIRACHI] =
    {
        .size = MON_COORDS_SIZE(64, 56),
        .y_offset = 5,
    },
    [SPECIES_DEOXYS] =
    {
        .size = MON_COORDS_SIZE(64, 56),
        .y_offset = 7,
    },
    [SPECIES_CHIMECHO] =
    {
        .size = MON_COORDS_SIZE(32, 56),
        .y_offset = 7,
    },
    [SPECIES_EGG] =
    {
        .size = MON_COORDS_SIZE(24, 48),
        .y_offset = 10,
    },
    [SPECIES_UNOWN_B] =
    {
        .size = MON_COORDS_SIZE(40, 48),
        .y_offset = 9,
    },
    [SPECIES_UNOWN_C] =
    {
        .size = MON_COORDS_SIZE(48, 56),
        .y_offset = 6,
    },
    [SPECIES_UNOWN_D] =
    {
        .size = MON_COORDS_SIZE(40, 48),
        .y_offset = 8,
    },
    [SPECIES_UNOWN_E] =
    {
        .size = MON_COORDS_SIZE(40, 48),
        .y_offset = 10,
    },
    [SPECIES_UNOWN_F] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 10,
    },
    [SPECIES_UNOWN_G] =
    {
        .size = MON_COORDS_SIZE(40, 56),
        .y_offset = 5,
    },
    [SPECIES_UNOWN_H] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 8,
    },
    [SPECIES_UNOWN_I] =
    {
        .size = MON_COORDS_SIZE(24, 56),
        .y_offset = 7,
    },
    [SPECIES_UNOWN_J] =
    {
        .size = MON_COORDS_SIZE(32, 48),
        .y_offset = 9,
    },
    [SPECIES_UNOWN_K] =
    {
        .size = MON_COORDS_SIZE(40, 56),
        .y_offset = 7,
    },
    [SPECIES_UNOWN_L] =
    {
        .size = MON_COORDS_SIZE(32, 48),
        .y_offset = 10,
    },
    [SPECIES_UNOWN_M] =
    {
        .size = MON_COORDS_SIZE(48, 40),
        .y_offset = 13,
    },
    [SPECIES_UNOWN_N] =
    {
        .size = MON_COORDS_SIZE(48, 40),
        .y_offset = 13,
    },
    [SPECIES_UNOWN_O] =
    {
        .size = MON_COORDS_SIZE(48, 48),
        .y_offset = 8,
    },
    [SPECIES_UNOWN_P] =
    {
        .size = MON_COORDS_SIZE(32, 48),
        .y_offset = 10,
    },
    [SPECIES_UNOWN_Q] =
    {
        .size = MON_COORDS_SIZE(40, 40),
        .y_offset = 15,
    },
    [SPECIES_UNOWN_R] =
    {
        .size = MON_COORDS_SIZE(32, 40),
        .y_offset = 12,
    },
    [SPECIES_UNOWN_S] =
    {
        .size = MON_COORDS_SIZE(40, 56),
        .y_offset = 4,
    },
    [SPECIES_UNOWN_T] =
    {
        .size = MON_COORDS_SIZE(32, 40),
        .y_offset = 13,
    },
    [SPECIES_UNOWN_U] =
    {
        .size = MON_COORDS_SIZE(48, 40),
        .y_offset = 13,
    },
    [SPECIES_UNOWN_V] =
    {
        .size = MON_COORDS_SIZE(40, 48),
        .y_offset = 11,
    },
    [SPECIES_UNOWN_W] =
    {
        .size = MON_COORDS_SIZE(40, 40),
        .y_offset = 13,
    },
    [SPECIES_UNOWN_X] =
    {
        .size = MON_COORDS_SIZE(40, 40),
        .y_offset = 15,
    },
    [SPECIES_UNOWN_Y] =
    {
        .size = MON_COORDS_SIZE(32, 48),
        .y_offset = 10,
    },
    [SPECIES_UNOWN_Z] =
    {
        .size = MON_COORDS_SIZE(32, 48),
        .y_offset = 10,
    },
    [SPECIES_UNOWN_EMARK] =
    {
        .size = MON_COORDS_SIZE(24, 56),
        .y_offset = 6,
    },
    [SPECIES_UNOWN_QMARK] =
    {
        .size = MON_COORDS_SIZE(32, 56),
        .y_offset = 6,
    },
};

// ===== END src/data/pokemon_graphics/back_pic_coordinates.h =====
// ===== BEGIN src/data/pokemon_graphics/back_pic_table.h =====
const struct CompressedSpriteSheet gMonBackPicTable[] =
{
    SPECIES_SPRITE(NONE, gMonBackPic_CircledQuestionMark),
    SPECIES_SPRITE(BULBASAUR, gMonBackPic_Bulbasaur),
    SPECIES_SPRITE(IVYSAUR, gMonBackPic_Ivysaur),
    SPECIES_SPRITE(VENUSAUR, gMonBackPic_Venusaur),
    SPECIES_SPRITE(CHARMANDER, gMonBackPic_Charmander),
    SPECIES_SPRITE(CHARMELEON, gMonBackPic_Charmeleon),
    SPECIES_SPRITE(CHARIZARD, gMonBackPic_Charizard),
    SPECIES_SPRITE(SQUIRTLE, gMonBackPic_Squirtle),
    SPECIES_SPRITE(WARTORTLE, gMonBackPic_Wartortle),
    SPECIES_SPRITE(BLASTOISE, gMonBackPic_Blastoise),
    SPECIES_SPRITE(CATERPIE, gMonBackPic_Caterpie),
    SPECIES_SPRITE(METAPOD, gMonBackPic_Metapod),
    SPECIES_SPRITE(BUTTERFREE, gMonBackPic_Butterfree),
    SPECIES_SPRITE(WEEDLE, gMonBackPic_Weedle),
    SPECIES_SPRITE(KAKUNA, gMonBackPic_Kakuna),
    SPECIES_SPRITE(BEEDRILL, gMonBackPic_Beedrill),
    SPECIES_SPRITE(PIDGEY, gMonBackPic_Pidgey),
    SPECIES_SPRITE(PIDGEOTTO, gMonBackPic_Pidgeotto),
    SPECIES_SPRITE(PIDGEOT, gMonBackPic_Pidgeot),
    SPECIES_SPRITE(RATTATA, gMonBackPic_Rattata),
    SPECIES_SPRITE(RATICATE, gMonBackPic_Raticate),
    SPECIES_SPRITE(SPEAROW, gMonBackPic_Spearow),
    SPECIES_SPRITE(FEAROW, gMonBackPic_Fearow),
    SPECIES_SPRITE(EKANS, gMonBackPic_Ekans),
    SPECIES_SPRITE(ARBOK, gMonBackPic_Arbok),
    SPECIES_SPRITE(PIKACHU, gMonBackPic_Pikachu),
    SPECIES_SPRITE(RAICHU, gMonBackPic_Raichu),
    SPECIES_SPRITE(SANDSHREW, gMonBackPic_Sandshrew),
    SPECIES_SPRITE(SANDSLASH, gMonBackPic_Sandslash),
    SPECIES_SPRITE(NIDORAN_F, gMonBackPic_NidoranF),
    SPECIES_SPRITE(NIDORINA, gMonBackPic_Nidorina),
    SPECIES_SPRITE(NIDOQUEEN, gMonBackPic_Nidoqueen),
    SPECIES_SPRITE(NIDORAN_M, gMonBackPic_NidoranM),
    SPECIES_SPRITE(NIDORINO, gMonBackPic_Nidorino),
    SPECIES_SPRITE(NIDOKING, gMonBackPic_Nidoking),
    SPECIES_SPRITE(CLEFAIRY, gMonBackPic_Clefairy),
    SPECIES_SPRITE(CLEFABLE, gMonBackPic_Clefable),
    SPECIES_SPRITE(VULPIX, gMonBackPic_Vulpix),
    SPECIES_SPRITE(NINETALES, gMonBackPic_Ninetales),
    SPECIES_SPRITE(JIGGLYPUFF, gMonBackPic_Jigglypuff),
    SPECIES_SPRITE(WIGGLYTUFF, gMonBackPic_Wigglytuff),
    SPECIES_SPRITE(ZUBAT, gMonBackPic_Zubat),
    SPECIES_SPRITE(GOLBAT, gMonBackPic_Golbat),
    SPECIES_SPRITE(ODDISH, gMonBackPic_Oddish),
    SPECIES_SPRITE(GLOOM, gMonBackPic_Gloom),
    SPECIES_SPRITE(VILEPLUME, gMonBackPic_Vileplume),
    SPECIES_SPRITE(PARAS, gMonBackPic_Paras),
    SPECIES_SPRITE(PARASECT, gMonBackPic_Parasect),
    SPECIES_SPRITE(VENONAT, gMonBackPic_Venonat),
    SPECIES_SPRITE(VENOMOTH, gMonBackPic_Venomoth),
    SPECIES_SPRITE(DIGLETT, gMonBackPic_Diglett),
    SPECIES_SPRITE(DUGTRIO, gMonBackPic_Dugtrio),
    SPECIES_SPRITE(MEOWTH, gMonBackPic_Meowth),
    SPECIES_SPRITE(PERSIAN, gMonBackPic_Persian),
    SPECIES_SPRITE(PSYDUCK, gMonBackPic_Psyduck),
    SPECIES_SPRITE(GOLDUCK, gMonBackPic_Golduck),
    SPECIES_SPRITE(MANKEY, gMonBackPic_Mankey),
    SPECIES_SPRITE(PRIMEAPE, gMonBackPic_Primeape),
    SPECIES_SPRITE(GROWLITHE, gMonBackPic_Growlithe),
    SPECIES_SPRITE(ARCANINE, gMonBackPic_Arcanine),
    SPECIES_SPRITE(POLIWAG, gMonBackPic_Poliwag),
    SPECIES_SPRITE(POLIWHIRL, gMonBackPic_Poliwhirl),
    SPECIES_SPRITE(POLIWRATH, gMonBackPic_Poliwrath),
    SPECIES_SPRITE(ABRA, gMonBackPic_Abra),
    SPECIES_SPRITE(KADABRA, gMonBackPic_Kadabra),
    SPECIES_SPRITE(ALAKAZAM, gMonBackPic_Alakazam),
    SPECIES_SPRITE(MACHOP, gMonBackPic_Machop),
    SPECIES_SPRITE(MACHOKE, gMonBackPic_Machoke),
    SPECIES_SPRITE(MACHAMP, gMonBackPic_Machamp),
    SPECIES_SPRITE(BELLSPROUT, gMonBackPic_Bellsprout),
    SPECIES_SPRITE(WEEPINBELL, gMonBackPic_Weepinbell),
    SPECIES_SPRITE(VICTREEBEL, gMonBackPic_Victreebel),
    SPECIES_SPRITE(TENTACOOL, gMonBackPic_Tentacool),
    SPECIES_SPRITE(TENTACRUEL, gMonBackPic_Tentacruel),
    SPECIES_SPRITE(GEODUDE, gMonBackPic_Geodude),
    SPECIES_SPRITE(GRAVELER, gMonBackPic_Graveler),
    SPECIES_SPRITE(GOLEM, gMonBackPic_Golem),
    SPECIES_SPRITE(PONYTA, gMonBackPic_Ponyta),
    SPECIES_SPRITE(RAPIDASH, gMonBackPic_Rapidash),
    SPECIES_SPRITE(SLOWPOKE, gMonBackPic_Slowpoke),
    SPECIES_SPRITE(SLOWBRO, gMonBackPic_Slowbro),
    SPECIES_SPRITE(MAGNEMITE, gMonBackPic_Magnemite),
    SPECIES_SPRITE(MAGNETON, gMonBackPic_Magneton),
    SPECIES_SPRITE(FARFETCHD, gMonBackPic_Farfetchd),
    SPECIES_SPRITE(DODUO, gMonBackPic_Doduo),
    SPECIES_SPRITE(DODRIO, gMonBackPic_Dodrio),
    SPECIES_SPRITE(SEEL, gMonBackPic_Seel),
    SPECIES_SPRITE(DEWGONG, gMonBackPic_Dewgong),
    SPECIES_SPRITE(GRIMER, gMonBackPic_Grimer),
    SPECIES_SPRITE(MUK, gMonBackPic_Muk),
    SPECIES_SPRITE(SHELLDER, gMonBackPic_Shellder),
    SPECIES_SPRITE(CLOYSTER, gMonBackPic_Cloyster),
    SPECIES_SPRITE(GASTLY, gMonBackPic_Gastly),
    SPECIES_SPRITE(HAUNTER, gMonBackPic_Haunter),
    SPECIES_SPRITE(GENGAR, gMonBackPic_Gengar),
    SPECIES_SPRITE(ONIX, gMonBackPic_Onix),
    SPECIES_SPRITE(DROWZEE, gMonBackPic_Drowzee),
    SPECIES_SPRITE(HYPNO, gMonBackPic_Hypno),
    SPECIES_SPRITE(KRABBY, gMonBackPic_Krabby),
    SPECIES_SPRITE(KINGLER, gMonBackPic_Kingler),
    SPECIES_SPRITE(VOLTORB, gMonBackPic_Voltorb),
    SPECIES_SPRITE(ELECTRODE, gMonBackPic_Electrode),
    SPECIES_SPRITE(EXEGGCUTE, gMonBackPic_Exeggcute),
    SPECIES_SPRITE(EXEGGUTOR, gMonBackPic_Exeggutor),
    SPECIES_SPRITE(CUBONE, gMonBackPic_Cubone),
    SPECIES_SPRITE(MAROWAK, gMonBackPic_Marowak),
    SPECIES_SPRITE(HITMONLEE, gMonBackPic_Hitmonlee),
    SPECIES_SPRITE(HITMONCHAN, gMonBackPic_Hitmonchan),
    SPECIES_SPRITE(LICKITUNG, gMonBackPic_Lickitung),
    SPECIES_SPRITE(KOFFING, gMonBackPic_Koffing),
    SPECIES_SPRITE(WEEZING, gMonBackPic_Weezing),
    SPECIES_SPRITE(RHYHORN, gMonBackPic_Rhyhorn),
    SPECIES_SPRITE(RHYDON, gMonBackPic_Rhydon),
    SPECIES_SPRITE(CHANSEY, gMonBackPic_Chansey),
    SPECIES_SPRITE(TANGELA, gMonBackPic_Tangela),
    SPECIES_SPRITE(KANGASKHAN, gMonBackPic_Kangaskhan),
    SPECIES_SPRITE(HORSEA, gMonBackPic_Horsea),
    SPECIES_SPRITE(SEADRA, gMonBackPic_Seadra),
    SPECIES_SPRITE(GOLDEEN, gMonBackPic_Goldeen),
    SPECIES_SPRITE(SEAKING, gMonBackPic_Seaking),
    SPECIES_SPRITE(STARYU, gMonBackPic_Staryu),
    SPECIES_SPRITE(STARMIE, gMonBackPic_Starmie),
    SPECIES_SPRITE(MR_MIME, gMonBackPic_Mrmime),
    SPECIES_SPRITE(SCYTHER, gMonBackPic_Scyther),
    SPECIES_SPRITE(JYNX, gMonBackPic_Jynx),
    SPECIES_SPRITE(ELECTABUZZ, gMonBackPic_Electabuzz),
    SPECIES_SPRITE(MAGMAR, gMonBackPic_Magmar),
    SPECIES_SPRITE(PINSIR, gMonBackPic_Pinsir),
    SPECIES_SPRITE(TAUROS, gMonBackPic_Tauros),
    SPECIES_SPRITE(MAGIKARP, gMonBackPic_Magikarp),
    SPECIES_SPRITE(GYARADOS, gMonBackPic_Gyarados),
    SPECIES_SPRITE(LAPRAS, gMonBackPic_Lapras),
    SPECIES_SPRITE(DITTO, gMonBackPic_Ditto),
    SPECIES_SPRITE(EEVEE, gMonBackPic_Eevee),
    SPECIES_SPRITE(VAPOREON, gMonBackPic_Vaporeon),
    SPECIES_SPRITE(JOLTEON, gMonBackPic_Jolteon),
    SPECIES_SPRITE(FLAREON, gMonBackPic_Flareon),
    SPECIES_SPRITE(PORYGON, gMonBackPic_Porygon),
    SPECIES_SPRITE(OMANYTE, gMonBackPic_Omanyte),
    SPECIES_SPRITE(OMASTAR, gMonBackPic_Omastar),
    SPECIES_SPRITE(KABUTO, gMonBackPic_Kabuto),
    SPECIES_SPRITE(KABUTOPS, gMonBackPic_Kabutops),
    SPECIES_SPRITE(AERODACTYL, gMonBackPic_Aerodactyl),
    SPECIES_SPRITE(SNORLAX, gMonBackPic_Snorlax),
    SPECIES_SPRITE(ARTICUNO, gMonBackPic_Articuno),
    SPECIES_SPRITE(ZAPDOS, gMonBackPic_Zapdos),
    SPECIES_SPRITE(MOLTRES, gMonBackPic_Moltres),
    SPECIES_SPRITE(DRATINI, gMonBackPic_Dratini),
    SPECIES_SPRITE(DRAGONAIR, gMonBackPic_Dragonair),
    SPECIES_SPRITE(DRAGONITE, gMonBackPic_Dragonite),
    SPECIES_SPRITE(MEWTWO, gMonBackPic_Mewtwo),
    SPECIES_SPRITE(MEW, gMonBackPic_Mew),
    SPECIES_SPRITE(CHIKORITA, gMonBackPic_Chikorita),
    SPECIES_SPRITE(BAYLEEF, gMonBackPic_Bayleef),
    SPECIES_SPRITE(MEGANIUM, gMonBackPic_Meganium),
    SPECIES_SPRITE(CYNDAQUIL, gMonBackPic_Cyndaquil),
    SPECIES_SPRITE(QUILAVA, gMonBackPic_Quilava),
    SPECIES_SPRITE(TYPHLOSION, gMonBackPic_Typhlosion),
    SPECIES_SPRITE(TOTODILE, gMonBackPic_Totodile),
    SPECIES_SPRITE(CROCONAW, gMonBackPic_Croconaw),
    SPECIES_SPRITE(FERALIGATR, gMonBackPic_Feraligatr),
    SPECIES_SPRITE(SENTRET, gMonBackPic_Sentret),
    SPECIES_SPRITE(FURRET, gMonBackPic_Furret),
    SPECIES_SPRITE(HOOTHOOT, gMonBackPic_Hoothoot),
    SPECIES_SPRITE(NOCTOWL, gMonBackPic_Noctowl),
    SPECIES_SPRITE(LEDYBA, gMonBackPic_Ledyba),
    SPECIES_SPRITE(LEDIAN, gMonBackPic_Ledian),
    SPECIES_SPRITE(SPINARAK, gMonBackPic_Spinarak),
    SPECIES_SPRITE(ARIADOS, gMonBackPic_Ariados),
    SPECIES_SPRITE(CROBAT, gMonBackPic_Crobat),
    SPECIES_SPRITE(CHINCHOU, gMonBackPic_Chinchou),
    SPECIES_SPRITE(LANTURN, gMonBackPic_Lanturn),
    SPECIES_SPRITE(PICHU, gMonBackPic_Pichu),
    SPECIES_SPRITE(CLEFFA, gMonBackPic_Cleffa),
    SPECIES_SPRITE(IGGLYBUFF, gMonBackPic_Igglybuff),
    SPECIES_SPRITE(TOGEPI, gMonBackPic_Togepi),
    SPECIES_SPRITE(TOGETIC, gMonBackPic_Togetic),
    SPECIES_SPRITE(NATU, gMonBackPic_Natu),
    SPECIES_SPRITE(XATU, gMonBackPic_Xatu),
    SPECIES_SPRITE(MAREEP, gMonBackPic_Mareep),
    SPECIES_SPRITE(FLAAFFY, gMonBackPic_Flaaffy),
    SPECIES_SPRITE(AMPHAROS, gMonBackPic_Ampharos),
    SPECIES_SPRITE(BELLOSSOM, gMonBackPic_Bellossom),
    SPECIES_SPRITE(MARILL, gMonBackPic_Marill),
    SPECIES_SPRITE(AZUMARILL, gMonBackPic_Azumarill),
    SPECIES_SPRITE(SUDOWOODO, gMonBackPic_Sudowoodo),
    SPECIES_SPRITE(POLITOED, gMonBackPic_Politoed),
    SPECIES_SPRITE(HOPPIP, gMonBackPic_Hoppip),
    SPECIES_SPRITE(SKIPLOOM, gMonBackPic_Skiploom),
    SPECIES_SPRITE(JUMPLUFF, gMonBackPic_Jumpluff),
    SPECIES_SPRITE(AIPOM, gMonBackPic_Aipom),
    SPECIES_SPRITE(SUNKERN, gMonBackPic_Sunkern),
    SPECIES_SPRITE(SUNFLORA, gMonBackPic_Sunflora),
    SPECIES_SPRITE(YANMA, gMonBackPic_Yanma),
    SPECIES_SPRITE(WOOPER, gMonBackPic_Wooper),
    SPECIES_SPRITE(QUAGSIRE, gMonBackPic_Quagsire),
    SPECIES_SPRITE(ESPEON, gMonBackPic_Espeon),
    SPECIES_SPRITE(UMBREON, gMonBackPic_Umbreon),
    SPECIES_SPRITE(MURKROW, gMonBackPic_Murkrow),
    SPECIES_SPRITE(SLOWKING, gMonBackPic_Slowking),
    SPECIES_SPRITE(MISDREAVUS, gMonBackPic_Misdreavus),
    SPECIES_SPRITE(UNOWN, gMonBackPic_UnownA),
    SPECIES_SPRITE(WOBBUFFET, gMonBackPic_Wobbuffet),
    SPECIES_SPRITE(GIRAFARIG, gMonBackPic_Girafarig),
    SPECIES_SPRITE(PINECO, gMonBackPic_Pineco),
    SPECIES_SPRITE(FORRETRESS, gMonBackPic_Forretress),
    SPECIES_SPRITE(DUNSPARCE, gMonBackPic_Dunsparce),
    SPECIES_SPRITE(GLIGAR, gMonBackPic_Gligar),
    SPECIES_SPRITE(STEELIX, gMonBackPic_Steelix),
    SPECIES_SPRITE(SNUBBULL, gMonBackPic_Snubbull),
    SPECIES_SPRITE(GRANBULL, gMonBackPic_Granbull),
    SPECIES_SPRITE(QWILFISH, gMonBackPic_Qwilfish),
    SPECIES_SPRITE(SCIZOR, gMonBackPic_Scizor),
    SPECIES_SPRITE(SHUCKLE, gMonBackPic_Shuckle),
    SPECIES_SPRITE(HERACROSS, gMonBackPic_Heracross),
    SPECIES_SPRITE(SNEASEL, gMonBackPic_Sneasel),
    SPECIES_SPRITE(TEDDIURSA, gMonBackPic_Teddiursa),
    SPECIES_SPRITE(URSARING, gMonBackPic_Ursaring),
    SPECIES_SPRITE(SLUGMA, gMonBackPic_Slugma),
    SPECIES_SPRITE(MAGCARGO, gMonBackPic_Magcargo),
    SPECIES_SPRITE(SWINUB, gMonBackPic_Swinub),
    SPECIES_SPRITE(PILOSWINE, gMonBackPic_Piloswine),
    SPECIES_SPRITE(CORSOLA, gMonBackPic_Corsola),
    SPECIES_SPRITE(REMORAID, gMonBackPic_Remoraid),
    SPECIES_SPRITE(OCTILLERY, gMonBackPic_Octillery),
    SPECIES_SPRITE(DELIBIRD, gMonBackPic_Delibird),
    SPECIES_SPRITE(MANTINE, gMonBackPic_Mantine),
    SPECIES_SPRITE(SKARMORY, gMonBackPic_Skarmory),
    SPECIES_SPRITE(HOUNDOUR, gMonBackPic_Houndour),
    SPECIES_SPRITE(HOUNDOOM, gMonBackPic_Houndoom),
    SPECIES_SPRITE(KINGDRA, gMonBackPic_Kingdra),
    SPECIES_SPRITE(PHANPY, gMonBackPic_Phanpy),
    SPECIES_SPRITE(DONPHAN, gMonBackPic_Donphan),
    SPECIES_SPRITE(PORYGON2, gMonBackPic_Porygon2),
    SPECIES_SPRITE(STANTLER, gMonBackPic_Stantler),
    SPECIES_SPRITE(SMEARGLE, gMonBackPic_Smeargle),
    SPECIES_SPRITE(TYROGUE, gMonBackPic_Tyrogue),
    SPECIES_SPRITE(HITMONTOP, gMonBackPic_Hitmontop),
    SPECIES_SPRITE(SMOOCHUM, gMonBackPic_Smoochum),
    SPECIES_SPRITE(ELEKID, gMonBackPic_Elekid),
    SPECIES_SPRITE(MAGBY, gMonBackPic_Magby),
    SPECIES_SPRITE(MILTANK, gMonBackPic_Miltank),
    SPECIES_SPRITE(BLISSEY, gMonBackPic_Blissey),
    SPECIES_SPRITE(RAIKOU, gMonBackPic_Raikou),
    SPECIES_SPRITE(ENTEI, gMonBackPic_Entei),
    SPECIES_SPRITE(SUICUNE, gMonBackPic_Suicune),
    SPECIES_SPRITE(LARVITAR, gMonBackPic_Larvitar),
    SPECIES_SPRITE(PUPITAR, gMonBackPic_Pupitar),
    SPECIES_SPRITE(TYRANITAR, gMonBackPic_Tyranitar),
    SPECIES_SPRITE(LUGIA, gMonBackPic_Lugia),
    SPECIES_SPRITE(HO_OH, gMonBackPic_HoOh),
    SPECIES_SPRITE(CELEBI, gMonBackPic_Celebi),
    SPECIES_SPRITE(OLD_UNOWN_B, gMonBackPic_DoubleQuestionMark),
    SPECIES_SPRITE(OLD_UNOWN_C, gMonBackPic_DoubleQuestionMark),
    SPECIES_SPRITE(OLD_UNOWN_D, gMonBackPic_DoubleQuestionMark),
    SPECIES_SPRITE(OLD_UNOWN_E, gMonBackPic_DoubleQuestionMark),
    SPECIES_SPRITE(OLD_UNOWN_F, gMonBackPic_DoubleQuestionMark),
    SPECIES_SPRITE(OLD_UNOWN_G, gMonBackPic_DoubleQuestionMark),
    SPECIES_SPRITE(OLD_UNOWN_H, gMonBackPic_DoubleQuestionMark),
    SPECIES_SPRITE(OLD_UNOWN_I, gMonBackPic_DoubleQuestionMark),
    SPECIES_SPRITE(OLD_UNOWN_J, gMonBackPic_DoubleQuestionMark),
    SPECIES_SPRITE(OLD_UNOWN_K, gMonBackPic_DoubleQuestionMark),
    SPECIES_SPRITE(OLD_UNOWN_L, gMonBackPic_DoubleQuestionMark),
    SPECIES_SPRITE(OLD_UNOWN_M, gMonBackPic_DoubleQuestionMark),
    SPECIES_SPRITE(OLD_UNOWN_N, gMonBackPic_DoubleQuestionMark),
    SPECIES_SPRITE(OLD_UNOWN_O, gMonBackPic_DoubleQuestionMark),
    SPECIES_SPRITE(OLD_UNOWN_P, gMonBackPic_DoubleQuestionMark),
    SPECIES_SPRITE(OLD_UNOWN_Q, gMonBackPic_DoubleQuestionMark),
    SPECIES_SPRITE(OLD_UNOWN_R, gMonBackPic_DoubleQuestionMark),
    SPECIES_SPRITE(OLD_UNOWN_S, gMonBackPic_DoubleQuestionMark),
    SPECIES_SPRITE(OLD_UNOWN_T, gMonBackPic_DoubleQuestionMark),
    SPECIES_SPRITE(OLD_UNOWN_U, gMonBackPic_DoubleQuestionMark),
    SPECIES_SPRITE(OLD_UNOWN_V, gMonBackPic_DoubleQuestionMark),
    SPECIES_SPRITE(OLD_UNOWN_W, gMonBackPic_DoubleQuestionMark),
    SPECIES_SPRITE(OLD_UNOWN_X, gMonBackPic_DoubleQuestionMark),
    SPECIES_SPRITE(OLD_UNOWN_Y, gMonBackPic_DoubleQuestionMark),
    SPECIES_SPRITE(OLD_UNOWN_Z, gMonBackPic_DoubleQuestionMark),
    SPECIES_SPRITE(TREECKO, gMonBackPic_Treecko),
    SPECIES_SPRITE(GROVYLE, gMonBackPic_Grovyle),
    SPECIES_SPRITE(SCEPTILE, gMonBackPic_Sceptile),
    SPECIES_SPRITE(TORCHIC, gMonBackPic_Torchic),
    SPECIES_SPRITE(COMBUSKEN, gMonBackPic_Combusken),
    SPECIES_SPRITE(BLAZIKEN, gMonBackPic_Blaziken),
    SPECIES_SPRITE(MUDKIP, gMonBackPic_Mudkip),
    SPECIES_SPRITE(MARSHTOMP, gMonBackPic_Marshtomp),
    SPECIES_SPRITE(SWAMPERT, gMonBackPic_Swampert),
    SPECIES_SPRITE(POOCHYENA, gMonBackPic_Poochyena),
    SPECIES_SPRITE(MIGHTYENA, gMonBackPic_Mightyena),
    SPECIES_SPRITE(ZIGZAGOON, gMonBackPic_Zigzagoon),
    SPECIES_SPRITE(LINOONE, gMonBackPic_Linoone),
    SPECIES_SPRITE(WURMPLE, gMonBackPic_Wurmple),
    SPECIES_SPRITE(SILCOON, gMonBackPic_Silcoon),
    SPECIES_SPRITE(BEAUTIFLY, gMonBackPic_Beautifly),
    SPECIES_SPRITE(CASCOON, gMonBackPic_Cascoon),
    SPECIES_SPRITE(DUSTOX, gMonBackPic_Dustox),
    SPECIES_SPRITE(LOTAD, gMonBackPic_Lotad),
    SPECIES_SPRITE(LOMBRE, gMonBackPic_Lombre),
    SPECIES_SPRITE(LUDICOLO, gMonBackPic_Ludicolo),
    SPECIES_SPRITE(SEEDOT, gMonBackPic_Seedot),
    SPECIES_SPRITE(NUZLEAF, gMonBackPic_Nuzleaf),
    SPECIES_SPRITE(SHIFTRY, gMonBackPic_Shiftry),
    SPECIES_SPRITE(NINCADA, gMonBackPic_Nincada),
    SPECIES_SPRITE(NINJASK, gMonBackPic_Ninjask),
    SPECIES_SPRITE(SHEDINJA, gMonBackPic_Shedinja),
    SPECIES_SPRITE(TAILLOW, gMonBackPic_Taillow),
    SPECIES_SPRITE(SWELLOW, gMonBackPic_Swellow),
    SPECIES_SPRITE(SHROOMISH, gMonBackPic_Shroomish),
    SPECIES_SPRITE(BRELOOM, gMonBackPic_Breloom),
    SPECIES_SPRITE(SPINDA, gMonBackPic_Spinda),
    SPECIES_SPRITE(WINGULL, gMonBackPic_Wingull),
    SPECIES_SPRITE(PELIPPER, gMonBackPic_Pelipper),
    SPECIES_SPRITE(SURSKIT, gMonBackPic_Surskit),
    SPECIES_SPRITE(MASQUERAIN, gMonBackPic_Masquerain),
    SPECIES_SPRITE(WAILMER, gMonBackPic_Wailmer),
    SPECIES_SPRITE(WAILORD, gMonBackPic_Wailord),
    SPECIES_SPRITE(SKITTY, gMonBackPic_Skitty),
    SPECIES_SPRITE(DELCATTY, gMonBackPic_Delcatty),
    SPECIES_SPRITE(KECLEON, gMonBackPic_Kecleon),
    SPECIES_SPRITE(BALTOY, gMonBackPic_Baltoy),
    SPECIES_SPRITE(CLAYDOL, gMonBackPic_Claydol),
    SPECIES_SPRITE(NOSEPASS, gMonBackPic_Nosepass),
    SPECIES_SPRITE(TORKOAL, gMonBackPic_Torkoal),
    SPECIES_SPRITE(SABLEYE, gMonBackPic_Sableye),
    SPECIES_SPRITE(BARBOACH, gMonBackPic_Barboach),
    SPECIES_SPRITE(WHISCASH, gMonBackPic_Whiscash),
    SPECIES_SPRITE(LUVDISC, gMonBackPic_Luvdisc),
    SPECIES_SPRITE(CORPHISH, gMonBackPic_Corphish),
    SPECIES_SPRITE(CRAWDAUNT, gMonBackPic_Crawdaunt),
    SPECIES_SPRITE(FEEBAS, gMonBackPic_Feebas),
    SPECIES_SPRITE(MILOTIC, gMonBackPic_Milotic),
    SPECIES_SPRITE(CARVANHA, gMonBackPic_Carvanha),
    SPECIES_SPRITE(SHARPEDO, gMonBackPic_Sharpedo),
    SPECIES_SPRITE(TRAPINCH, gMonBackPic_Trapinch),
    SPECIES_SPRITE(VIBRAVA, gMonBackPic_Vibrava),
    SPECIES_SPRITE(FLYGON, gMonBackPic_Flygon),
    SPECIES_SPRITE(MAKUHITA, gMonBackPic_Makuhita),
    SPECIES_SPRITE(HARIYAMA, gMonBackPic_Hariyama),
    SPECIES_SPRITE(ELECTRIKE, gMonBackPic_Electrike),
    SPECIES_SPRITE(MANECTRIC, gMonBackPic_Manectric),
    SPECIES_SPRITE(NUMEL, gMonBackPic_Numel),
    SPECIES_SPRITE(CAMERUPT, gMonBackPic_Camerupt),
    SPECIES_SPRITE(SPHEAL, gMonBackPic_Spheal),
    SPECIES_SPRITE(SEALEO, gMonBackPic_Sealeo),
    SPECIES_SPRITE(WALREIN, gMonBackPic_Walrein),
    SPECIES_SPRITE(CACNEA, gMonBackPic_Cacnea),
    SPECIES_SPRITE(CACTURNE, gMonBackPic_Cacturne),
    SPECIES_SPRITE(SNORUNT, gMonBackPic_Snorunt),
    SPECIES_SPRITE(GLALIE, gMonBackPic_Glalie),
    SPECIES_SPRITE(LUNATONE, gMonBackPic_Lunatone),
    SPECIES_SPRITE(SOLROCK, gMonBackPic_Solrock),
    SPECIES_SPRITE(AZURILL, gMonBackPic_Azurill),
    SPECIES_SPRITE(SPOINK, gMonBackPic_Spoink),
    SPECIES_SPRITE(GRUMPIG, gMonBackPic_Grumpig),
    SPECIES_SPRITE(PLUSLE, gMonBackPic_Plusle),
    SPECIES_SPRITE(MINUN, gMonBackPic_Minun),
    SPECIES_SPRITE(MAWILE, gMonBackPic_Mawile),
    SPECIES_SPRITE(MEDITITE, gMonBackPic_Meditite),
    SPECIES_SPRITE(MEDICHAM, gMonBackPic_Medicham),
    SPECIES_SPRITE(SWABLU, gMonBackPic_Swablu),
    SPECIES_SPRITE(ALTARIA, gMonBackPic_Altaria),
    SPECIES_SPRITE(WYNAUT, gMonBackPic_Wynaut),
    SPECIES_SPRITE(DUSKULL, gMonBackPic_Duskull),
    SPECIES_SPRITE(DUSCLOPS, gMonBackPic_Dusclops),
    SPECIES_SPRITE(ROSELIA, gMonBackPic_Roselia),
    SPECIES_SPRITE(SLAKOTH, gMonBackPic_Slakoth),
    SPECIES_SPRITE(VIGOROTH, gMonBackPic_Vigoroth),
    SPECIES_SPRITE(SLAKING, gMonBackPic_Slaking),
    SPECIES_SPRITE(GULPIN, gMonBackPic_Gulpin),
    SPECIES_SPRITE(SWALOT, gMonBackPic_Swalot),
    SPECIES_SPRITE(TROPIUS, gMonBackPic_Tropius),
    SPECIES_SPRITE(WHISMUR, gMonBackPic_Whismur),
    SPECIES_SPRITE(LOUDRED, gMonBackPic_Loudred),
    SPECIES_SPRITE(EXPLOUD, gMonBackPic_Exploud),
    SPECIES_SPRITE(CLAMPERL, gMonBackPic_Clamperl),
    SPECIES_SPRITE(HUNTAIL, gMonBackPic_Huntail),
    SPECIES_SPRITE(GOREBYSS, gMonBackPic_Gorebyss),
    SPECIES_SPRITE(ABSOL, gMonBackPic_Absol),
    SPECIES_SPRITE(SHUPPET, gMonBackPic_Shuppet),
    SPECIES_SPRITE(BANETTE, gMonBackPic_Banette),
    SPECIES_SPRITE(SEVIPER, gMonBackPic_Seviper),
    SPECIES_SPRITE(ZANGOOSE, gMonBackPic_Zangoose),
    SPECIES_SPRITE(RELICANTH, gMonBackPic_Relicanth),
    SPECIES_SPRITE(ARON, gMonBackPic_Aron),
    SPECIES_SPRITE(LAIRON, gMonBackPic_Lairon),
    SPECIES_SPRITE(AGGRON, gMonBackPic_Aggron),
    SPECIES_SPRITE(CASTFORM, gMonBackPic_Castform),
    SPECIES_SPRITE(VOLBEAT, gMonBackPic_Volbeat),
    SPECIES_SPRITE(ILLUMISE, gMonBackPic_Illumise),
    SPECIES_SPRITE(LILEEP, gMonBackPic_Lileep),
    SPECIES_SPRITE(CRADILY, gMonBackPic_Cradily),
    SPECIES_SPRITE(ANORITH, gMonBackPic_Anorith),
    SPECIES_SPRITE(ARMALDO, gMonBackPic_Armaldo),
    SPECIES_SPRITE(RALTS, gMonBackPic_Ralts),
    SPECIES_SPRITE(KIRLIA, gMonBackPic_Kirlia),
    SPECIES_SPRITE(GARDEVOIR, gMonBackPic_Gardevoir),
    SPECIES_SPRITE(BAGON, gMonBackPic_Bagon),
    SPECIES_SPRITE(SHELGON, gMonBackPic_Shelgon),
    SPECIES_SPRITE(SALAMENCE, gMonBackPic_Salamence),
    SPECIES_SPRITE(BELDUM, gMonBackPic_Beldum),
    SPECIES_SPRITE(METANG, gMonBackPic_Metang),
    SPECIES_SPRITE(METAGROSS, gMonBackPic_Metagross),
    SPECIES_SPRITE(REGIROCK, gMonBackPic_Regirock),
    SPECIES_SPRITE(REGICE, gMonBackPic_Regice),
    SPECIES_SPRITE(REGISTEEL, gMonBackPic_Registeel),
    SPECIES_SPRITE(KYOGRE, gMonBackPic_Kyogre),
    SPECIES_SPRITE(GROUDON, gMonBackPic_Groudon),
    SPECIES_SPRITE(RAYQUAZA, gMonBackPic_Rayquaza),
    SPECIES_SPRITE(LATIAS, gMonBackPic_Latias),
    SPECIES_SPRITE(LATIOS, gMonBackPic_Latios),
    SPECIES_SPRITE(JIRACHI, gMonBackPic_Jirachi),
    SPECIES_SPRITE(DEOXYS, gMonBackPic_Deoxys),
    SPECIES_SPRITE(CHIMECHO, gMonBackPic_Chimecho),
    SPECIES_SPRITE(EGG, gMonFrontPic_Egg),
    SPECIES_SPRITE(UNOWN_B, gMonBackPic_UnownB),
    SPECIES_SPRITE(UNOWN_C, gMonBackPic_UnownC),
    SPECIES_SPRITE(UNOWN_D, gMonBackPic_UnownD),
    SPECIES_SPRITE(UNOWN_E, gMonBackPic_UnownE),
    SPECIES_SPRITE(UNOWN_F, gMonBackPic_UnownF),
    SPECIES_SPRITE(UNOWN_G, gMonBackPic_UnownG),
    SPECIES_SPRITE(UNOWN_H, gMonBackPic_UnownH),
    SPECIES_SPRITE(UNOWN_I, gMonBackPic_UnownI),
    SPECIES_SPRITE(UNOWN_J, gMonBackPic_UnownJ),
    SPECIES_SPRITE(UNOWN_K, gMonBackPic_UnownK),
    SPECIES_SPRITE(UNOWN_L, gMonBackPic_UnownL),
    SPECIES_SPRITE(UNOWN_M, gMonBackPic_UnownM),
    SPECIES_SPRITE(UNOWN_N, gMonBackPic_UnownN),
    SPECIES_SPRITE(UNOWN_O, gMonBackPic_UnownO),
    SPECIES_SPRITE(UNOWN_P, gMonBackPic_UnownP),
    SPECIES_SPRITE(UNOWN_Q, gMonBackPic_UnownQ),
    SPECIES_SPRITE(UNOWN_R, gMonBackPic_UnownR),
    SPECIES_SPRITE(UNOWN_S, gMonBackPic_UnownS),
    SPECIES_SPRITE(UNOWN_T, gMonBackPic_UnownT),
    SPECIES_SPRITE(UNOWN_U, gMonBackPic_UnownU),
    SPECIES_SPRITE(UNOWN_V, gMonBackPic_UnownV),
    SPECIES_SPRITE(UNOWN_W, gMonBackPic_UnownW),
    SPECIES_SPRITE(UNOWN_X, gMonBackPic_UnownX),
    SPECIES_SPRITE(UNOWN_Y, gMonBackPic_UnownY),
    SPECIES_SPRITE(UNOWN_Z, gMonBackPic_UnownZ),
    SPECIES_SPRITE(UNOWN_EMARK, gMonBackPic_UnownExclamationMark),
    SPECIES_SPRITE(UNOWN_QMARK, gMonBackPic_UnownQuestionMark),
};
// ===== END src/data/pokemon_graphics/back_pic_table.h =====
// ===== BEGIN src/data/pokemon_graphics/palette_table.h =====
const struct CompressedSpritePalette gMonPaletteTable[] =
{
    SPECIES_PAL(NONE, gMonPalette_CircledQuestionMark),
    SPECIES_PAL(BULBASAUR, gMonPalette_Bulbasaur),
    SPECIES_PAL(IVYSAUR, gMonPalette_Ivysaur),
    SPECIES_PAL(VENUSAUR, gMonPalette_Venusaur),
    SPECIES_PAL(CHARMANDER, gMonPalette_Charmander),
    SPECIES_PAL(CHARMELEON, gMonPalette_Charmeleon),
    SPECIES_PAL(CHARIZARD, gMonPalette_Charizard),
    SPECIES_PAL(SQUIRTLE, gMonPalette_Squirtle),
    SPECIES_PAL(WARTORTLE, gMonPalette_Wartortle),
    SPECIES_PAL(BLASTOISE, gMonPalette_Blastoise),
    SPECIES_PAL(CATERPIE, gMonPalette_Caterpie),
    SPECIES_PAL(METAPOD, gMonPalette_Metapod),
    SPECIES_PAL(BUTTERFREE, gMonPalette_Butterfree),
    SPECIES_PAL(WEEDLE, gMonPalette_Weedle),
    SPECIES_PAL(KAKUNA, gMonPalette_Kakuna),
    SPECIES_PAL(BEEDRILL, gMonPalette_Beedrill),
    SPECIES_PAL(PIDGEY, gMonPalette_Pidgey),
    SPECIES_PAL(PIDGEOTTO, gMonPalette_Pidgeotto),
    SPECIES_PAL(PIDGEOT, gMonPalette_Pidgeot),
    SPECIES_PAL(RATTATA, gMonPalette_Rattata),
    SPECIES_PAL(RATICATE, gMonPalette_Raticate),
    SPECIES_PAL(SPEAROW, gMonPalette_Spearow),
    SPECIES_PAL(FEAROW, gMonPalette_Fearow),
    SPECIES_PAL(EKANS, gMonPalette_Ekans),
    SPECIES_PAL(ARBOK, gMonPalette_Arbok),
    SPECIES_PAL(PIKACHU, gMonPalette_Pikachu),
    SPECIES_PAL(RAICHU, gMonPalette_Raichu),
    SPECIES_PAL(SANDSHREW, gMonPalette_Sandshrew),
    SPECIES_PAL(SANDSLASH, gMonPalette_Sandslash),
    SPECIES_PAL(NIDORAN_F, gMonPalette_NidoranF),
    SPECIES_PAL(NIDORINA, gMonPalette_Nidorina),
    SPECIES_PAL(NIDOQUEEN, gMonPalette_Nidoqueen),
    SPECIES_PAL(NIDORAN_M, gMonPalette_NidoranM),
    SPECIES_PAL(NIDORINO, gMonPalette_Nidorino),
    SPECIES_PAL(NIDOKING, gMonPalette_Nidoking),
    SPECIES_PAL(CLEFAIRY, gMonPalette_Clefairy),
    SPECIES_PAL(CLEFABLE, gMonPalette_Clefable),
    SPECIES_PAL(VULPIX, gMonPalette_Vulpix),
    SPECIES_PAL(NINETALES, gMonPalette_Ninetales),
    SPECIES_PAL(JIGGLYPUFF, gMonPalette_Jigglypuff),
    SPECIES_PAL(WIGGLYTUFF, gMonPalette_Wigglytuff),
    SPECIES_PAL(ZUBAT, gMonPalette_Zubat),
    SPECIES_PAL(GOLBAT, gMonPalette_Golbat),
    SPECIES_PAL(ODDISH, gMonPalette_Oddish),
    SPECIES_PAL(GLOOM, gMonPalette_Gloom),
    SPECIES_PAL(VILEPLUME, gMonPalette_Vileplume),
    SPECIES_PAL(PARAS, gMonPalette_Paras),
    SPECIES_PAL(PARASECT, gMonPalette_Parasect),
    SPECIES_PAL(VENONAT, gMonPalette_Venonat),
    SPECIES_PAL(VENOMOTH, gMonPalette_Venomoth),
    SPECIES_PAL(DIGLETT, gMonPalette_Diglett),
    SPECIES_PAL(DUGTRIO, gMonPalette_Dugtrio),
    SPECIES_PAL(MEOWTH, gMonPalette_Meowth),
    SPECIES_PAL(PERSIAN, gMonPalette_Persian),
    SPECIES_PAL(PSYDUCK, gMonPalette_Psyduck),
    SPECIES_PAL(GOLDUCK, gMonPalette_Golduck),
    SPECIES_PAL(MANKEY, gMonPalette_Mankey),
    SPECIES_PAL(PRIMEAPE, gMonPalette_Primeape),
    SPECIES_PAL(GROWLITHE, gMonPalette_Growlithe),
    SPECIES_PAL(ARCANINE, gMonPalette_Arcanine),
    SPECIES_PAL(POLIWAG, gMonPalette_Poliwag),
    SPECIES_PAL(POLIWHIRL, gMonPalette_Poliwhirl),
    SPECIES_PAL(POLIWRATH, gMonPalette_Poliwrath),
    SPECIES_PAL(ABRA, gMonPalette_Abra),
    SPECIES_PAL(KADABRA, gMonPalette_Kadabra),
    SPECIES_PAL(ALAKAZAM, gMonPalette_Alakazam),
    SPECIES_PAL(MACHOP, gMonPalette_Machop),
    SPECIES_PAL(MACHOKE, gMonPalette_Machoke),
    SPECIES_PAL(MACHAMP, gMonPalette_Machamp),
    SPECIES_PAL(BELLSPROUT, gMonPalette_Bellsprout),
    SPECIES_PAL(WEEPINBELL, gMonPalette_Weepinbell),
    SPECIES_PAL(VICTREEBEL, gMonPalette_Victreebel),
    SPECIES_PAL(TENTACOOL, gMonPalette_Tentacool),
    SPECIES_PAL(TENTACRUEL, gMonPalette_Tentacruel),
    SPECIES_PAL(GEODUDE, gMonPalette_Geodude),
    SPECIES_PAL(GRAVELER, gMonPalette_Graveler),
    SPECIES_PAL(GOLEM, gMonPalette_Golem),
    SPECIES_PAL(PONYTA, gMonPalette_Ponyta),
    SPECIES_PAL(RAPIDASH, gMonPalette_Rapidash),
    SPECIES_PAL(SLOWPOKE, gMonPalette_Slowpoke),
    SPECIES_PAL(SLOWBRO, gMonPalette_Slowbro),
    SPECIES_PAL(MAGNEMITE, gMonPalette_Magnemite),
    SPECIES_PAL(MAGNETON, gMonPalette_Magneton),
    SPECIES_PAL(FARFETCHD, gMonPalette_Farfetchd),
    SPECIES_PAL(DODUO, gMonPalette_Doduo),
    SPECIES_PAL(DODRIO, gMonPalette_Dodrio),
    SPECIES_PAL(SEEL, gMonPalette_Seel),
    SPECIES_PAL(DEWGONG, gMonPalette_Dewgong),
    SPECIES_PAL(GRIMER, gMonPalette_Grimer),
    SPECIES_PAL(MUK, gMonPalette_Muk),
    SPECIES_PAL(SHELLDER, gMonPalette_Shellder),
    SPECIES_PAL(CLOYSTER, gMonPalette_Cloyster),
    SPECIES_PAL(GASTLY, gMonPalette_Gastly),
    SPECIES_PAL(HAUNTER, gMonPalette_Haunter),
    SPECIES_PAL(GENGAR, gMonPalette_Gengar),
    SPECIES_PAL(ONIX, gMonPalette_Onix),
    SPECIES_PAL(DROWZEE, gMonPalette_Drowzee),
    SPECIES_PAL(HYPNO, gMonPalette_Hypno),
    SPECIES_PAL(KRABBY, gMonPalette_Krabby),
    SPECIES_PAL(KINGLER, gMonPalette_Kingler),
    SPECIES_PAL(VOLTORB, gMonPalette_Voltorb),
    SPECIES_PAL(ELECTRODE, gMonPalette_Electrode),
    SPECIES_PAL(EXEGGCUTE, gMonPalette_Exeggcute),
    SPECIES_PAL(EXEGGUTOR, gMonPalette_Exeggutor),
    SPECIES_PAL(CUBONE, gMonPalette_Cubone),
    SPECIES_PAL(MAROWAK, gMonPalette_Marowak),
    SPECIES_PAL(HITMONLEE, gMonPalette_Hitmonlee),
    SPECIES_PAL(HITMONCHAN, gMonPalette_Hitmonchan),
    SPECIES_PAL(LICKITUNG, gMonPalette_Lickitung),
    SPECIES_PAL(KOFFING, gMonPalette_Koffing),
    SPECIES_PAL(WEEZING, gMonPalette_Weezing),
    SPECIES_PAL(RHYHORN, gMonPalette_Rhyhorn),
    SPECIES_PAL(RHYDON, gMonPalette_Rhydon),
    SPECIES_PAL(CHANSEY, gMonPalette_Chansey),
    SPECIES_PAL(TANGELA, gMonPalette_Tangela),
    SPECIES_PAL(KANGASKHAN, gMonPalette_Kangaskhan),
    SPECIES_PAL(HORSEA, gMonPalette_Horsea),
    SPECIES_PAL(SEADRA, gMonPalette_Seadra),
    SPECIES_PAL(GOLDEEN, gMonPalette_Goldeen),
    SPECIES_PAL(SEAKING, gMonPalette_Seaking),
    SPECIES_PAL(STARYU, gMonPalette_Staryu),
    SPECIES_PAL(STARMIE, gMonPalette_Starmie),
    SPECIES_PAL(MR_MIME, gMonPalette_Mrmime),
    SPECIES_PAL(SCYTHER, gMonPalette_Scyther),
    SPECIES_PAL(JYNX, gMonPalette_Jynx),
    SPECIES_PAL(ELECTABUZZ, gMonPalette_Electabuzz),
    SPECIES_PAL(MAGMAR, gMonPalette_Magmar),
    SPECIES_PAL(PINSIR, gMonPalette_Pinsir),
    SPECIES_PAL(TAUROS, gMonPalette_Tauros),
    SPECIES_PAL(MAGIKARP, gMonPalette_Magikarp),
    SPECIES_PAL(GYARADOS, gMonPalette_Gyarados),
    SPECIES_PAL(LAPRAS, gMonPalette_Lapras),
    SPECIES_PAL(DITTO, gMonPalette_Ditto),
    SPECIES_PAL(EEVEE, gMonPalette_Eevee),
    SPECIES_PAL(VAPOREON, gMonPalette_Vaporeon),
    SPECIES_PAL(JOLTEON, gMonPalette_Jolteon),
    SPECIES_PAL(FLAREON, gMonPalette_Flareon),
    SPECIES_PAL(PORYGON, gMonPalette_Porygon),
    SPECIES_PAL(OMANYTE, gMonPalette_Omanyte),
    SPECIES_PAL(OMASTAR, gMonPalette_Omastar),
    SPECIES_PAL(KABUTO, gMonPalette_Kabuto),
    SPECIES_PAL(KABUTOPS, gMonPalette_Kabutops),
    SPECIES_PAL(AERODACTYL, gMonPalette_Aerodactyl),
    SPECIES_PAL(SNORLAX, gMonPalette_Snorlax),
    SPECIES_PAL(ARTICUNO, gMonPalette_Articuno),
    SPECIES_PAL(ZAPDOS, gMonPalette_Zapdos),
    SPECIES_PAL(MOLTRES, gMonPalette_Moltres),
    SPECIES_PAL(DRATINI, gMonPalette_Dratini),
    SPECIES_PAL(DRAGONAIR, gMonPalette_Dragonair),
    SPECIES_PAL(DRAGONITE, gMonPalette_Dragonite),
    SPECIES_PAL(MEWTWO, gMonPalette_Mewtwo),
    SPECIES_PAL(MEW, gMonPalette_Mew),
    SPECIES_PAL(CHIKORITA, gMonPalette_Chikorita),
    SPECIES_PAL(BAYLEEF, gMonPalette_Bayleef),
    SPECIES_PAL(MEGANIUM, gMonPalette_Meganium),
    SPECIES_PAL(CYNDAQUIL, gMonPalette_Cyndaquil),
    SPECIES_PAL(QUILAVA, gMonPalette_Quilava),
    SPECIES_PAL(TYPHLOSION, gMonPalette_Typhlosion),
    SPECIES_PAL(TOTODILE, gMonPalette_Totodile),
    SPECIES_PAL(CROCONAW, gMonPalette_Croconaw),
    SPECIES_PAL(FERALIGATR, gMonPalette_Feraligatr),
    SPECIES_PAL(SENTRET, gMonPalette_Sentret),
    SPECIES_PAL(FURRET, gMonPalette_Furret),
    SPECIES_PAL(HOOTHOOT, gMonPalette_Hoothoot),
    SPECIES_PAL(NOCTOWL, gMonPalette_Noctowl),
    SPECIES_PAL(LEDYBA, gMonPalette_Ledyba),
    SPECIES_PAL(LEDIAN, gMonPalette_Ledian),
    SPECIES_PAL(SPINARAK, gMonPalette_Spinarak),
    SPECIES_PAL(ARIADOS, gMonPalette_Ariados),
    SPECIES_PAL(CROBAT, gMonPalette_Crobat),
    SPECIES_PAL(CHINCHOU, gMonPalette_Chinchou),
    SPECIES_PAL(LANTURN, gMonPalette_Lanturn),
    SPECIES_PAL(PICHU, gMonPalette_Pichu),
    SPECIES_PAL(CLEFFA, gMonPalette_Cleffa),
    SPECIES_PAL(IGGLYBUFF, gMonPalette_Igglybuff),
    SPECIES_PAL(TOGEPI, gMonPalette_Togepi),
    SPECIES_PAL(TOGETIC, gMonPalette_Togetic),
    SPECIES_PAL(NATU, gMonPalette_Natu),
    SPECIES_PAL(XATU, gMonPalette_Xatu),
    SPECIES_PAL(MAREEP, gMonPalette_Mareep),
    SPECIES_PAL(FLAAFFY, gMonPalette_Flaaffy),
    SPECIES_PAL(AMPHAROS, gMonPalette_Ampharos),
    SPECIES_PAL(BELLOSSOM, gMonPalette_Bellossom),
    SPECIES_PAL(MARILL, gMonPalette_Marill),
    SPECIES_PAL(AZUMARILL, gMonPalette_Azumarill),
    SPECIES_PAL(SUDOWOODO, gMonPalette_Sudowoodo),
    SPECIES_PAL(POLITOED, gMonPalette_Politoed),
    SPECIES_PAL(HOPPIP, gMonPalette_Hoppip),
    SPECIES_PAL(SKIPLOOM, gMonPalette_Skiploom),
    SPECIES_PAL(JUMPLUFF, gMonPalette_Jumpluff),
    SPECIES_PAL(AIPOM, gMonPalette_Aipom),
    SPECIES_PAL(SUNKERN, gMonPalette_Sunkern),
    SPECIES_PAL(SUNFLORA, gMonPalette_Sunflora),
    SPECIES_PAL(YANMA, gMonPalette_Yanma),
    SPECIES_PAL(WOOPER, gMonPalette_Wooper),
    SPECIES_PAL(QUAGSIRE, gMonPalette_Quagsire),
    SPECIES_PAL(ESPEON, gMonPalette_Espeon),
    SPECIES_PAL(UMBREON, gMonPalette_Umbreon),
    SPECIES_PAL(MURKROW, gMonPalette_Murkrow),
    SPECIES_PAL(SLOWKING, gMonPalette_Slowking),
    SPECIES_PAL(MISDREAVUS, gMonPalette_Misdreavus),
    SPECIES_PAL(UNOWN, gMonPalette_Unown),
    SPECIES_PAL(WOBBUFFET, gMonPalette_Wobbuffet),
    SPECIES_PAL(GIRAFARIG, gMonPalette_Girafarig),
    SPECIES_PAL(PINECO, gMonPalette_Pineco),
    SPECIES_PAL(FORRETRESS, gMonPalette_Forretress),
    SPECIES_PAL(DUNSPARCE, gMonPalette_Dunsparce),
    SPECIES_PAL(GLIGAR, gMonPalette_Gligar),
    SPECIES_PAL(STEELIX, gMonPalette_Steelix),
    SPECIES_PAL(SNUBBULL, gMonPalette_Snubbull),
    SPECIES_PAL(GRANBULL, gMonPalette_Granbull),
    SPECIES_PAL(QWILFISH, gMonPalette_Qwilfish),
    SPECIES_PAL(SCIZOR, gMonPalette_Scizor),
    SPECIES_PAL(SHUCKLE, gMonPalette_Shuckle),
    SPECIES_PAL(HERACROSS, gMonPalette_Heracross),
    SPECIES_PAL(SNEASEL, gMonPalette_Sneasel),
    SPECIES_PAL(TEDDIURSA, gMonPalette_Teddiursa),
    SPECIES_PAL(URSARING, gMonPalette_Ursaring),
    SPECIES_PAL(SLUGMA, gMonPalette_Slugma),
    SPECIES_PAL(MAGCARGO, gMonPalette_Magcargo),
    SPECIES_PAL(SWINUB, gMonPalette_Swinub),
    SPECIES_PAL(PILOSWINE, gMonPalette_Piloswine),
    SPECIES_PAL(CORSOLA, gMonPalette_Corsola),
    SPECIES_PAL(REMORAID, gMonPalette_Remoraid),
    SPECIES_PAL(OCTILLERY, gMonPalette_Octillery),
    SPECIES_PAL(DELIBIRD, gMonPalette_Delibird),
    SPECIES_PAL(MANTINE, gMonPalette_Mantine),
    SPECIES_PAL(SKARMORY, gMonPalette_Skarmory),
    SPECIES_PAL(HOUNDOUR, gMonPalette_Houndour),
    SPECIES_PAL(HOUNDOOM, gMonPalette_Houndoom),
    SPECIES_PAL(KINGDRA, gMonPalette_Kingdra),
    SPECIES_PAL(PHANPY, gMonPalette_Phanpy),
    SPECIES_PAL(DONPHAN, gMonPalette_Donphan),
    SPECIES_PAL(PORYGON2, gMonPalette_Porygon2),
    SPECIES_PAL(STANTLER, gMonPalette_Stantler),
    SPECIES_PAL(SMEARGLE, gMonPalette_Smeargle),
    SPECIES_PAL(TYROGUE, gMonPalette_Tyrogue),
    SPECIES_PAL(HITMONTOP, gMonPalette_Hitmontop),
    SPECIES_PAL(SMOOCHUM, gMonPalette_Smoochum),
    SPECIES_PAL(ELEKID, gMonPalette_Elekid),
    SPECIES_PAL(MAGBY, gMonPalette_Magby),
    SPECIES_PAL(MILTANK, gMonPalette_Miltank),
    SPECIES_PAL(BLISSEY, gMonPalette_Blissey),
    SPECIES_PAL(RAIKOU, gMonPalette_Raikou),
    SPECIES_PAL(ENTEI, gMonPalette_Entei),
    SPECIES_PAL(SUICUNE, gMonPalette_Suicune),
    SPECIES_PAL(LARVITAR, gMonPalette_Larvitar),
    SPECIES_PAL(PUPITAR, gMonPalette_Pupitar),
    SPECIES_PAL(TYRANITAR, gMonPalette_Tyranitar),
    SPECIES_PAL(LUGIA, gMonPalette_Lugia),
    SPECIES_PAL(HO_OH, gMonPalette_HoOh),
    SPECIES_PAL(CELEBI, gMonPalette_Celebi),
    SPECIES_PAL(OLD_UNOWN_B, gMonPalette_DoubleQuestionMark),
    SPECIES_PAL(OLD_UNOWN_C, gMonPalette_DoubleQuestionMark),
    SPECIES_PAL(OLD_UNOWN_D, gMonPalette_DoubleQuestionMark),
    SPECIES_PAL(OLD_UNOWN_E, gMonPalette_DoubleQuestionMark),
    SPECIES_PAL(OLD_UNOWN_F, gMonPalette_DoubleQuestionMark),
    SPECIES_PAL(OLD_UNOWN_G, gMonPalette_DoubleQuestionMark),
    SPECIES_PAL(OLD_UNOWN_H, gMonPalette_DoubleQuestionMark),
    SPECIES_PAL(OLD_UNOWN_I, gMonPalette_DoubleQuestionMark),
    SPECIES_PAL(OLD_UNOWN_J, gMonPalette_DoubleQuestionMark),
    SPECIES_PAL(OLD_UNOWN_K, gMonPalette_DoubleQuestionMark),
    SPECIES_PAL(OLD_UNOWN_L, gMonPalette_DoubleQuestionMark),
    SPECIES_PAL(OLD_UNOWN_M, gMonPalette_DoubleQuestionMark),
    SPECIES_PAL(OLD_UNOWN_N, gMonPalette_DoubleQuestionMark),
    SPECIES_PAL(OLD_UNOWN_O, gMonPalette_DoubleQuestionMark),
    SPECIES_PAL(OLD_UNOWN_P, gMonPalette_DoubleQuestionMark),
    SPECIES_PAL(OLD_UNOWN_Q, gMonPalette_DoubleQuestionMark),
    SPECIES_PAL(OLD_UNOWN_R, gMonPalette_DoubleQuestionMark),
    SPECIES_PAL(OLD_UNOWN_S, gMonPalette_DoubleQuestionMark),
    SPECIES_PAL(OLD_UNOWN_T, gMonPalette_DoubleQuestionMark),
    SPECIES_PAL(OLD_UNOWN_U, gMonPalette_DoubleQuestionMark),
    SPECIES_PAL(OLD_UNOWN_V, gMonPalette_DoubleQuestionMark),
    SPECIES_PAL(OLD_UNOWN_W, gMonPalette_DoubleQuestionMark),
    SPECIES_PAL(OLD_UNOWN_X, gMonPalette_DoubleQuestionMark),
    SPECIES_PAL(OLD_UNOWN_Y, gMonPalette_DoubleQuestionMark),
    SPECIES_PAL(OLD_UNOWN_Z, gMonPalette_DoubleQuestionMark),
    SPECIES_PAL(TREECKO, gMonPalette_Treecko),
    SPECIES_PAL(GROVYLE, gMonPalette_Grovyle),
    SPECIES_PAL(SCEPTILE, gMonPalette_Sceptile),
    SPECIES_PAL(TORCHIC, gMonPalette_Torchic),
    SPECIES_PAL(COMBUSKEN, gMonPalette_Combusken),
    SPECIES_PAL(BLAZIKEN, gMonPalette_Blaziken),
    SPECIES_PAL(MUDKIP, gMonPalette_Mudkip),
    SPECIES_PAL(MARSHTOMP, gMonPalette_Marshtomp),
    SPECIES_PAL(SWAMPERT, gMonPalette_Swampert),
    SPECIES_PAL(POOCHYENA, gMonPalette_Poochyena),
    SPECIES_PAL(MIGHTYENA, gMonPalette_Mightyena),
    SPECIES_PAL(ZIGZAGOON, gMonPalette_Zigzagoon),
    SPECIES_PAL(LINOONE, gMonPalette_Linoone),
    SPECIES_PAL(WURMPLE, gMonPalette_Wurmple),
    SPECIES_PAL(SILCOON, gMonPalette_Silcoon),
    SPECIES_PAL(BEAUTIFLY, gMonPalette_Beautifly),
    SPECIES_PAL(CASCOON, gMonPalette_Cascoon),
    SPECIES_PAL(DUSTOX, gMonPalette_Dustox),
    SPECIES_PAL(LOTAD, gMonPalette_Lotad),
    SPECIES_PAL(LOMBRE, gMonPalette_Lombre),
    SPECIES_PAL(LUDICOLO, gMonPalette_Ludicolo),
    SPECIES_PAL(SEEDOT, gMonPalette_Seedot),
    SPECIES_PAL(NUZLEAF, gMonPalette_Nuzleaf),
    SPECIES_PAL(SHIFTRY, gMonPalette_Shiftry),
    SPECIES_PAL(NINCADA, gMonPalette_Nincada),
    SPECIES_PAL(NINJASK, gMonPalette_Ninjask),
    SPECIES_PAL(SHEDINJA, gMonPalette_Shedinja),
    SPECIES_PAL(TAILLOW, gMonPalette_Taillow),
    SPECIES_PAL(SWELLOW, gMonPalette_Swellow),
    SPECIES_PAL(SHROOMISH, gMonPalette_Shroomish),
    SPECIES_PAL(BRELOOM, gMonPalette_Breloom),
    SPECIES_PAL(SPINDA, gMonPalette_Spinda),
    SPECIES_PAL(WINGULL, gMonPalette_Wingull),
    SPECIES_PAL(PELIPPER, gMonPalette_Pelipper),
    SPECIES_PAL(SURSKIT, gMonPalette_Surskit),
    SPECIES_PAL(MASQUERAIN, gMonPalette_Masquerain),
    SPECIES_PAL(WAILMER, gMonPalette_Wailmer),
    SPECIES_PAL(WAILORD, gMonPalette_Wailord),
    SPECIES_PAL(SKITTY, gMonPalette_Skitty),
    SPECIES_PAL(DELCATTY, gMonPalette_Delcatty),
    SPECIES_PAL(KECLEON, gMonPalette_Kecleon),
    SPECIES_PAL(BALTOY, gMonPalette_Baltoy),
    SPECIES_PAL(CLAYDOL, gMonPalette_Claydol),
    SPECIES_PAL(NOSEPASS, gMonPalette_Nosepass),
    SPECIES_PAL(TORKOAL, gMonPalette_Torkoal),
    SPECIES_PAL(SABLEYE, gMonPalette_Sableye),
    SPECIES_PAL(BARBOACH, gMonPalette_Barboach),
    SPECIES_PAL(WHISCASH, gMonPalette_Whiscash),
    SPECIES_PAL(LUVDISC, gMonPalette_Luvdisc),
    SPECIES_PAL(CORPHISH, gMonPalette_Corphish),
    SPECIES_PAL(CRAWDAUNT, gMonPalette_Crawdaunt),
    SPECIES_PAL(FEEBAS, gMonPalette_Feebas),
    SPECIES_PAL(MILOTIC, gMonPalette_Milotic),
    SPECIES_PAL(CARVANHA, gMonPalette_Carvanha),
    SPECIES_PAL(SHARPEDO, gMonPalette_Sharpedo),
    SPECIES_PAL(TRAPINCH, gMonPalette_Trapinch),
    SPECIES_PAL(VIBRAVA, gMonPalette_Vibrava),
    SPECIES_PAL(FLYGON, gMonPalette_Flygon),
    SPECIES_PAL(MAKUHITA, gMonPalette_Makuhita),
    SPECIES_PAL(HARIYAMA, gMonPalette_Hariyama),
    SPECIES_PAL(ELECTRIKE, gMonPalette_Electrike),
    SPECIES_PAL(MANECTRIC, gMonPalette_Manectric),
    SPECIES_PAL(NUMEL, gMonPalette_Numel),
    SPECIES_PAL(CAMERUPT, gMonPalette_Camerupt),
    SPECIES_PAL(SPHEAL, gMonPalette_Spheal),
    SPECIES_PAL(SEALEO, gMonPalette_Sealeo),
    SPECIES_PAL(WALREIN, gMonPalette_Walrein),
    SPECIES_PAL(CACNEA, gMonPalette_Cacnea),
    SPECIES_PAL(CACTURNE, gMonPalette_Cacturne),
    SPECIES_PAL(SNORUNT, gMonPalette_Snorunt),
    SPECIES_PAL(GLALIE, gMonPalette_Glalie),
    SPECIES_PAL(LUNATONE, gMonPalette_Lunatone),
    SPECIES_PAL(SOLROCK, gMonPalette_Solrock),
    SPECIES_PAL(AZURILL, gMonPalette_Azurill),
    SPECIES_PAL(SPOINK, gMonPalette_Spoink),
    SPECIES_PAL(GRUMPIG, gMonPalette_Grumpig),
    SPECIES_PAL(PLUSLE, gMonPalette_Plusle),
    SPECIES_PAL(MINUN, gMonPalette_Minun),
    SPECIES_PAL(MAWILE, gMonPalette_Mawile),
    SPECIES_PAL(MEDITITE, gMonPalette_Meditite),
    SPECIES_PAL(MEDICHAM, gMonPalette_Medicham),
    SPECIES_PAL(SWABLU, gMonPalette_Swablu),
    SPECIES_PAL(ALTARIA, gMonPalette_Altaria),
    SPECIES_PAL(WYNAUT, gMonPalette_Wynaut),
    SPECIES_PAL(DUSKULL, gMonPalette_Duskull),
    SPECIES_PAL(DUSCLOPS, gMonPalette_Dusclops),
    SPECIES_PAL(ROSELIA, gMonPalette_Roselia),
    SPECIES_PAL(SLAKOTH, gMonPalette_Slakoth),
    SPECIES_PAL(VIGOROTH, gMonPalette_Vigoroth),
    SPECIES_PAL(SLAKING, gMonPalette_Slaking),
    SPECIES_PAL(GULPIN, gMonPalette_Gulpin),
    SPECIES_PAL(SWALOT, gMonPalette_Swalot),
    SPECIES_PAL(TROPIUS, gMonPalette_Tropius),
    SPECIES_PAL(WHISMUR, gMonPalette_Whismur),
    SPECIES_PAL(LOUDRED, gMonPalette_Loudred),
    SPECIES_PAL(EXPLOUD, gMonPalette_Exploud),
    SPECIES_PAL(CLAMPERL, gMonPalette_Clamperl),
    SPECIES_PAL(HUNTAIL, gMonPalette_Huntail),
    SPECIES_PAL(GOREBYSS, gMonPalette_Gorebyss),
    SPECIES_PAL(ABSOL, gMonPalette_Absol),
    SPECIES_PAL(SHUPPET, gMonPalette_Shuppet),
    SPECIES_PAL(BANETTE, gMonPalette_Banette),
    SPECIES_PAL(SEVIPER, gMonPalette_Seviper),
    SPECIES_PAL(ZANGOOSE, gMonPalette_Zangoose),
    SPECIES_PAL(RELICANTH, gMonPalette_Relicanth),
    SPECIES_PAL(ARON, gMonPalette_Aron),
    SPECIES_PAL(LAIRON, gMonPalette_Lairon),
    SPECIES_PAL(AGGRON, gMonPalette_Aggron),
    SPECIES_PAL(CASTFORM, gMonPalette_Castform),
    SPECIES_PAL(VOLBEAT, gMonPalette_Volbeat),
    SPECIES_PAL(ILLUMISE, gMonPalette_Illumise),
    SPECIES_PAL(LILEEP, gMonPalette_Lileep),
    SPECIES_PAL(CRADILY, gMonPalette_Cradily),
    SPECIES_PAL(ANORITH, gMonPalette_Anorith),
    SPECIES_PAL(ARMALDO, gMonPalette_Armaldo),
    SPECIES_PAL(RALTS, gMonPalette_Ralts),
    SPECIES_PAL(KIRLIA, gMonPalette_Kirlia),
    SPECIES_PAL(GARDEVOIR, gMonPalette_Gardevoir),
    SPECIES_PAL(BAGON, gMonPalette_Bagon),
    SPECIES_PAL(SHELGON, gMonPalette_Shelgon),
    SPECIES_PAL(SALAMENCE, gMonPalette_Salamence),
    SPECIES_PAL(BELDUM, gMonPalette_Beldum),
    SPECIES_PAL(METANG, gMonPalette_Metang),
    SPECIES_PAL(METAGROSS, gMonPalette_Metagross),
    SPECIES_PAL(REGIROCK, gMonPalette_Regirock),
    SPECIES_PAL(REGICE, gMonPalette_Regice),
    SPECIES_PAL(REGISTEEL, gMonPalette_Registeel),
    SPECIES_PAL(KYOGRE, gMonPalette_Kyogre),
    SPECIES_PAL(GROUDON, gMonPalette_Groudon),
    SPECIES_PAL(RAYQUAZA, gMonPalette_Rayquaza),
    SPECIES_PAL(LATIAS, gMonPalette_Latias),
    SPECIES_PAL(LATIOS, gMonPalette_Latios),
    SPECIES_PAL(JIRACHI, gMonPalette_Jirachi),
    SPECIES_PAL(DEOXYS, gMonPalette_Deoxys),
    SPECIES_PAL(CHIMECHO, gMonPalette_Chimecho),
    SPECIES_PAL(EGG, gMonPalette_Egg),
    SPECIES_PAL(UNOWN_B, gMonPalette_Unown),
    SPECIES_PAL(UNOWN_C, gMonPalette_Unown),
    SPECIES_PAL(UNOWN_D, gMonPalette_Unown),
    SPECIES_PAL(UNOWN_E, gMonPalette_Unown),
    SPECIES_PAL(UNOWN_F, gMonPalette_Unown),
    SPECIES_PAL(UNOWN_G, gMonPalette_Unown),
    SPECIES_PAL(UNOWN_H, gMonPalette_Unown),
    SPECIES_PAL(UNOWN_I, gMonPalette_Unown),
    SPECIES_PAL(UNOWN_J, gMonPalette_Unown),
    SPECIES_PAL(UNOWN_K, gMonPalette_Unown),
    SPECIES_PAL(UNOWN_L, gMonPalette_Unown),
    SPECIES_PAL(UNOWN_M, gMonPalette_Unown),
    SPECIES_PAL(UNOWN_N, gMonPalette_Unown),
    SPECIES_PAL(UNOWN_O, gMonPalette_Unown),
    SPECIES_PAL(UNOWN_P, gMonPalette_Unown),
    SPECIES_PAL(UNOWN_Q, gMonPalette_Unown),
    SPECIES_PAL(UNOWN_R, gMonPalette_Unown),
    SPECIES_PAL(UNOWN_S, gMonPalette_Unown),
    SPECIES_PAL(UNOWN_T, gMonPalette_Unown),
    SPECIES_PAL(UNOWN_U, gMonPalette_Unown),
    SPECIES_PAL(UNOWN_V, gMonPalette_Unown),
    SPECIES_PAL(UNOWN_W, gMonPalette_Unown),
    SPECIES_PAL(UNOWN_X, gMonPalette_Unown),
    SPECIES_PAL(UNOWN_Y, gMonPalette_Unown),
    SPECIES_PAL(UNOWN_Z, gMonPalette_Unown),
    SPECIES_PAL(UNOWN_EMARK, gMonPalette_Unown),
    SPECIES_PAL(UNOWN_QMARK, gMonPalette_Unown),
};
// ===== END src/data/pokemon_graphics/palette_table.h =====
// ===== BEGIN src/data/pokemon_graphics/shiny_palette_table.h =====
const struct CompressedSpritePalette gMonShinyPaletteTable[] =
{
    SPECIES_SHINY_PAL(NONE, gMonShinyPalette_CircledQuestionMark),
    SPECIES_SHINY_PAL(BULBASAUR, gMonShinyPalette_Bulbasaur),
    SPECIES_SHINY_PAL(IVYSAUR, gMonShinyPalette_Ivysaur),
    SPECIES_SHINY_PAL(VENUSAUR, gMonShinyPalette_Venusaur),
    SPECIES_SHINY_PAL(CHARMANDER, gMonShinyPalette_Charmander),
    SPECIES_SHINY_PAL(CHARMELEON, gMonShinyPalette_Charmeleon),
    SPECIES_SHINY_PAL(CHARIZARD, gMonShinyPalette_Charizard),
    SPECIES_SHINY_PAL(SQUIRTLE, gMonShinyPalette_Squirtle),
    SPECIES_SHINY_PAL(WARTORTLE, gMonShinyPalette_Wartortle),
    SPECIES_SHINY_PAL(BLASTOISE, gMonShinyPalette_Blastoise),
    SPECIES_SHINY_PAL(CATERPIE, gMonShinyPalette_Caterpie),
    SPECIES_SHINY_PAL(METAPOD, gMonShinyPalette_Metapod),
    SPECIES_SHINY_PAL(BUTTERFREE, gMonShinyPalette_Butterfree),
    SPECIES_SHINY_PAL(WEEDLE, gMonShinyPalette_Weedle),
    SPECIES_SHINY_PAL(KAKUNA, gMonShinyPalette_Kakuna),
    SPECIES_SHINY_PAL(BEEDRILL, gMonShinyPalette_Beedrill),
    SPECIES_SHINY_PAL(PIDGEY, gMonShinyPalette_Pidgey),
    SPECIES_SHINY_PAL(PIDGEOTTO, gMonShinyPalette_Pidgeotto),
    SPECIES_SHINY_PAL(PIDGEOT, gMonShinyPalette_Pidgeot),
    SPECIES_SHINY_PAL(RATTATA, gMonShinyPalette_Rattata),
    SPECIES_SHINY_PAL(RATICATE, gMonShinyPalette_Raticate),
    SPECIES_SHINY_PAL(SPEAROW, gMonShinyPalette_Spearow),
    SPECIES_SHINY_PAL(FEAROW, gMonShinyPalette_Fearow),
    SPECIES_SHINY_PAL(EKANS, gMonShinyPalette_Ekans),
    SPECIES_SHINY_PAL(ARBOK, gMonShinyPalette_Arbok),
    SPECIES_SHINY_PAL(PIKACHU, gMonShinyPalette_Pikachu),
    SPECIES_SHINY_PAL(RAICHU, gMonShinyPalette_Raichu),
    SPECIES_SHINY_PAL(SANDSHREW, gMonShinyPalette_Sandshrew),
    SPECIES_SHINY_PAL(SANDSLASH, gMonShinyPalette_Sandslash),
    SPECIES_SHINY_PAL(NIDORAN_F, gMonShinyPalette_NidoranF),
    SPECIES_SHINY_PAL(NIDORINA, gMonShinyPalette_Nidorina),
    SPECIES_SHINY_PAL(NIDOQUEEN, gMonShinyPalette_Nidoqueen),
    SPECIES_SHINY_PAL(NIDORAN_M, gMonShinyPalette_NidoranM),
    SPECIES_SHINY_PAL(NIDORINO, gMonShinyPalette_Nidorino),
    SPECIES_SHINY_PAL(NIDOKING, gMonShinyPalette_Nidoking),
    SPECIES_SHINY_PAL(CLEFAIRY, gMonShinyPalette_Clefairy),
    SPECIES_SHINY_PAL(CLEFABLE, gMonShinyPalette_Clefable),
    SPECIES_SHINY_PAL(VULPIX, gMonShinyPalette_Vulpix),
    SPECIES_SHINY_PAL(NINETALES, gMonShinyPalette_Ninetales),
    SPECIES_SHINY_PAL(JIGGLYPUFF, gMonShinyPalette_Jigglypuff),
    SPECIES_SHINY_PAL(WIGGLYTUFF, gMonShinyPalette_Wigglytuff),
    SPECIES_SHINY_PAL(ZUBAT, gMonShinyPalette_Zubat),
    SPECIES_SHINY_PAL(GOLBAT, gMonShinyPalette_Golbat),
    SPECIES_SHINY_PAL(ODDISH, gMonShinyPalette_Oddish),
    SPECIES_SHINY_PAL(GLOOM, gMonShinyPalette_Gloom),
    SPECIES_SHINY_PAL(VILEPLUME, gMonShinyPalette_Vileplume),
    SPECIES_SHINY_PAL(PARAS, gMonShinyPalette_Paras),
    SPECIES_SHINY_PAL(PARASECT, gMonShinyPalette_Parasect),
    SPECIES_SHINY_PAL(VENONAT, gMonShinyPalette_Venonat),
    SPECIES_SHINY_PAL(VENOMOTH, gMonShinyPalette_Venomoth),
    SPECIES_SHINY_PAL(DIGLETT, gMonShinyPalette_Diglett),
    SPECIES_SHINY_PAL(DUGTRIO, gMonShinyPalette_Dugtrio),
    SPECIES_SHINY_PAL(MEOWTH, gMonShinyPalette_Meowth),
    SPECIES_SHINY_PAL(PERSIAN, gMonShinyPalette_Persian),
    SPECIES_SHINY_PAL(PSYDUCK, gMonShinyPalette_Psyduck),
    SPECIES_SHINY_PAL(GOLDUCK, gMonShinyPalette_Golduck),
    SPECIES_SHINY_PAL(MANKEY, gMonShinyPalette_Mankey),
    SPECIES_SHINY_PAL(PRIMEAPE, gMonShinyPalette_Primeape),
    SPECIES_SHINY_PAL(GROWLITHE, gMonShinyPalette_Growlithe),
    SPECIES_SHINY_PAL(ARCANINE, gMonShinyPalette_Arcanine),
    SPECIES_SHINY_PAL(POLIWAG, gMonShinyPalette_Poliwag),
    SPECIES_SHINY_PAL(POLIWHIRL, gMonShinyPalette_Poliwhirl),
    SPECIES_SHINY_PAL(POLIWRATH, gMonShinyPalette_Poliwrath),
    SPECIES_SHINY_PAL(ABRA, gMonShinyPalette_Abra),
    SPECIES_SHINY_PAL(KADABRA, gMonShinyPalette_Kadabra),
    SPECIES_SHINY_PAL(ALAKAZAM, gMonShinyPalette_Alakazam),
    SPECIES_SHINY_PAL(MACHOP, gMonShinyPalette_Machop),
    SPECIES_SHINY_PAL(MACHOKE, gMonShinyPalette_Machoke),
    SPECIES_SHINY_PAL(MACHAMP, gMonShinyPalette_Machamp),
    SPECIES_SHINY_PAL(BELLSPROUT, gMonShinyPalette_Bellsprout),
    SPECIES_SHINY_PAL(WEEPINBELL, gMonShinyPalette_Weepinbell),
    SPECIES_SHINY_PAL(VICTREEBEL, gMonShinyPalette_Victreebel),
    SPECIES_SHINY_PAL(TENTACOOL, gMonShinyPalette_Tentacool),
    SPECIES_SHINY_PAL(TENTACRUEL, gMonShinyPalette_Tentacruel),
    SPECIES_SHINY_PAL(GEODUDE, gMonShinyPalette_Geodude),
    SPECIES_SHINY_PAL(GRAVELER, gMonShinyPalette_Graveler),
    SPECIES_SHINY_PAL(GOLEM, gMonShinyPalette_Golem),
    SPECIES_SHINY_PAL(PONYTA, gMonShinyPalette_Ponyta),
    SPECIES_SHINY_PAL(RAPIDASH, gMonShinyPalette_Rapidash),
    SPECIES_SHINY_PAL(SLOWPOKE, gMonShinyPalette_Slowpoke),
    SPECIES_SHINY_PAL(SLOWBRO, gMonShinyPalette_Slowbro),
    SPECIES_SHINY_PAL(MAGNEMITE, gMonShinyPalette_Magnemite),
    SPECIES_SHINY_PAL(MAGNETON, gMonShinyPalette_Magneton),
    SPECIES_SHINY_PAL(FARFETCHD, gMonShinyPalette_Farfetchd),
    SPECIES_SHINY_PAL(DODUO, gMonShinyPalette_Doduo),
    SPECIES_SHINY_PAL(DODRIO, gMonShinyPalette_Dodrio),
    SPECIES_SHINY_PAL(SEEL, gMonShinyPalette_Seel),
    SPECIES_SHINY_PAL(DEWGONG, gMonShinyPalette_Dewgong),
    SPECIES_SHINY_PAL(GRIMER, gMonShinyPalette_Grimer),
    SPECIES_SHINY_PAL(MUK, gMonShinyPalette_Muk),
    SPECIES_SHINY_PAL(SHELLDER, gMonShinyPalette_Shellder),
    SPECIES_SHINY_PAL(CLOYSTER, gMonShinyPalette_Cloyster),
    SPECIES_SHINY_PAL(GASTLY, gMonShinyPalette_Gastly),
    SPECIES_SHINY_PAL(HAUNTER, gMonShinyPalette_Haunter),
    SPECIES_SHINY_PAL(GENGAR, gMonShinyPalette_Gengar),
    SPECIES_SHINY_PAL(ONIX, gMonShinyPalette_Onix),
    SPECIES_SHINY_PAL(DROWZEE, gMonShinyPalette_Drowzee),
    SPECIES_SHINY_PAL(HYPNO, gMonShinyPalette_Hypno),
    SPECIES_SHINY_PAL(KRABBY, gMonShinyPalette_Krabby),
    SPECIES_SHINY_PAL(KINGLER, gMonShinyPalette_Kingler),
    SPECIES_SHINY_PAL(VOLTORB, gMonShinyPalette_Voltorb),
    SPECIES_SHINY_PAL(ELECTRODE, gMonShinyPalette_Electrode),
    SPECIES_SHINY_PAL(EXEGGCUTE, gMonShinyPalette_Exeggcute),
    SPECIES_SHINY_PAL(EXEGGUTOR, gMonShinyPalette_Exeggutor),
    SPECIES_SHINY_PAL(CUBONE, gMonShinyPalette_Cubone),
    SPECIES_SHINY_PAL(MAROWAK, gMonShinyPalette_Marowak),
    SPECIES_SHINY_PAL(HITMONLEE, gMonShinyPalette_Hitmonlee),
    SPECIES_SHINY_PAL(HITMONCHAN, gMonShinyPalette_Hitmonchan),
    SPECIES_SHINY_PAL(LICKITUNG, gMonShinyPalette_Lickitung),
    SPECIES_SHINY_PAL(KOFFING, gMonShinyPalette_Koffing),
    SPECIES_SHINY_PAL(WEEZING, gMonShinyPalette_Weezing),
    SPECIES_SHINY_PAL(RHYHORN, gMonShinyPalette_Rhyhorn),
    SPECIES_SHINY_PAL(RHYDON, gMonShinyPalette_Rhydon),
    SPECIES_SHINY_PAL(CHANSEY, gMonShinyPalette_Chansey),
    SPECIES_SHINY_PAL(TANGELA, gMonShinyPalette_Tangela),
    SPECIES_SHINY_PAL(KANGASKHAN, gMonShinyPalette_Kangaskhan),
    SPECIES_SHINY_PAL(HORSEA, gMonShinyPalette_Horsea),
    SPECIES_SHINY_PAL(SEADRA, gMonShinyPalette_Seadra),
    SPECIES_SHINY_PAL(GOLDEEN, gMonShinyPalette_Goldeen),
    SPECIES_SHINY_PAL(SEAKING, gMonShinyPalette_Seaking),
    SPECIES_SHINY_PAL(STARYU, gMonShinyPalette_Staryu),
    SPECIES_SHINY_PAL(STARMIE, gMonShinyPalette_Starmie),
    SPECIES_SHINY_PAL(MR_MIME, gMonShinyPalette_Mrmime),
    SPECIES_SHINY_PAL(SCYTHER, gMonShinyPalette_Scyther),
    SPECIES_SHINY_PAL(JYNX, gMonShinyPalette_Jynx),
    SPECIES_SHINY_PAL(ELECTABUZZ, gMonShinyPalette_Electabuzz),
    SPECIES_SHINY_PAL(MAGMAR, gMonShinyPalette_Magmar),
    SPECIES_SHINY_PAL(PINSIR, gMonShinyPalette_Pinsir),
    SPECIES_SHINY_PAL(TAUROS, gMonShinyPalette_Tauros),
    SPECIES_SHINY_PAL(MAGIKARP, gMonShinyPalette_Magikarp),
    SPECIES_SHINY_PAL(GYARADOS, gMonShinyPalette_Gyarados),
    SPECIES_SHINY_PAL(LAPRAS, gMonShinyPalette_Lapras),
    SPECIES_SHINY_PAL(DITTO, gMonShinyPalette_Ditto),
    SPECIES_SHINY_PAL(EEVEE, gMonShinyPalette_Eevee),
    SPECIES_SHINY_PAL(VAPOREON, gMonShinyPalette_Vaporeon),
    SPECIES_SHINY_PAL(JOLTEON, gMonShinyPalette_Jolteon),
    SPECIES_SHINY_PAL(FLAREON, gMonShinyPalette_Flareon),
    SPECIES_SHINY_PAL(PORYGON, gMonShinyPalette_Porygon),
    SPECIES_SHINY_PAL(OMANYTE, gMonShinyPalette_Omanyte),
    SPECIES_SHINY_PAL(OMASTAR, gMonShinyPalette_Omastar),
    SPECIES_SHINY_PAL(KABUTO, gMonShinyPalette_Kabuto),
    SPECIES_SHINY_PAL(KABUTOPS, gMonShinyPalette_Kabutops),
    SPECIES_SHINY_PAL(AERODACTYL, gMonShinyPalette_Aerodactyl),
    SPECIES_SHINY_PAL(SNORLAX, gMonShinyPalette_Snorlax),
    SPECIES_SHINY_PAL(ARTICUNO, gMonShinyPalette_Articuno),
    SPECIES_SHINY_PAL(ZAPDOS, gMonShinyPalette_Zapdos),
    SPECIES_SHINY_PAL(MOLTRES, gMonShinyPalette_Moltres),
    SPECIES_SHINY_PAL(DRATINI, gMonShinyPalette_Dratini),
    SPECIES_SHINY_PAL(DRAGONAIR, gMonShinyPalette_Dragonair),
    SPECIES_SHINY_PAL(DRAGONITE, gMonShinyPalette_Dragonite),
    SPECIES_SHINY_PAL(MEWTWO, gMonShinyPalette_Mewtwo),
    SPECIES_SHINY_PAL(MEW, gMonShinyPalette_Mew),
    SPECIES_SHINY_PAL(CHIKORITA, gMonShinyPalette_Chikorita),
    SPECIES_SHINY_PAL(BAYLEEF, gMonShinyPalette_Bayleef),
    SPECIES_SHINY_PAL(MEGANIUM, gMonShinyPalette_Meganium),
    SPECIES_SHINY_PAL(CYNDAQUIL, gMonShinyPalette_Cyndaquil),
    SPECIES_SHINY_PAL(QUILAVA, gMonShinyPalette_Quilava),
    SPECIES_SHINY_PAL(TYPHLOSION, gMonShinyPalette_Typhlosion),
    SPECIES_SHINY_PAL(TOTODILE, gMonShinyPalette_Totodile),
    SPECIES_SHINY_PAL(CROCONAW, gMonShinyPalette_Croconaw),
    SPECIES_SHINY_PAL(FERALIGATR, gMonShinyPalette_Feraligatr),
    SPECIES_SHINY_PAL(SENTRET, gMonShinyPalette_Sentret),
    SPECIES_SHINY_PAL(FURRET, gMonShinyPalette_Furret),
    SPECIES_SHINY_PAL(HOOTHOOT, gMonShinyPalette_Hoothoot),
    SPECIES_SHINY_PAL(NOCTOWL, gMonShinyPalette_Noctowl),
    SPECIES_SHINY_PAL(LEDYBA, gMonShinyPalette_Ledyba),
    SPECIES_SHINY_PAL(LEDIAN, gMonShinyPalette_Ledian),
    SPECIES_SHINY_PAL(SPINARAK, gMonShinyPalette_Spinarak),
    SPECIES_SHINY_PAL(ARIADOS, gMonShinyPalette_Ariados),
    SPECIES_SHINY_PAL(CROBAT, gMonShinyPalette_Crobat),
    SPECIES_SHINY_PAL(CHINCHOU, gMonShinyPalette_Chinchou),
    SPECIES_SHINY_PAL(LANTURN, gMonShinyPalette_Lanturn),
    SPECIES_SHINY_PAL(PICHU, gMonShinyPalette_Pichu),
    SPECIES_SHINY_PAL(CLEFFA, gMonShinyPalette_Cleffa),
    SPECIES_SHINY_PAL(IGGLYBUFF, gMonShinyPalette_Igglybuff),
    SPECIES_SHINY_PAL(TOGEPI, gMonShinyPalette_Togepi),
    SPECIES_SHINY_PAL(TOGETIC, gMonShinyPalette_Togetic),
    SPECIES_SHINY_PAL(NATU, gMonShinyPalette_Natu),
    SPECIES_SHINY_PAL(XATU, gMonShinyPalette_Xatu),
    SPECIES_SHINY_PAL(MAREEP, gMonShinyPalette_Mareep),
    SPECIES_SHINY_PAL(FLAAFFY, gMonShinyPalette_Flaaffy),
    SPECIES_SHINY_PAL(AMPHAROS, gMonShinyPalette_Ampharos),
    SPECIES_SHINY_PAL(BELLOSSOM, gMonShinyPalette_Bellossom),
    SPECIES_SHINY_PAL(MARILL, gMonShinyPalette_Marill),
    SPECIES_SHINY_PAL(AZUMARILL, gMonShinyPalette_Azumarill),
    SPECIES_SHINY_PAL(SUDOWOODO, gMonShinyPalette_Sudowoodo),
    SPECIES_SHINY_PAL(POLITOED, gMonShinyPalette_Politoed),
    SPECIES_SHINY_PAL(HOPPIP, gMonShinyPalette_Hoppip),
    SPECIES_SHINY_PAL(SKIPLOOM, gMonShinyPalette_Skiploom),
    SPECIES_SHINY_PAL(JUMPLUFF, gMonShinyPalette_Jumpluff),
    SPECIES_SHINY_PAL(AIPOM, gMonShinyPalette_Aipom),
    SPECIES_SHINY_PAL(SUNKERN, gMonShinyPalette_Sunkern),
    SPECIES_SHINY_PAL(SUNFLORA, gMonShinyPalette_Sunflora),
    SPECIES_SHINY_PAL(YANMA, gMonShinyPalette_Yanma),
    SPECIES_SHINY_PAL(WOOPER, gMonShinyPalette_Wooper),
    SPECIES_SHINY_PAL(QUAGSIRE, gMonShinyPalette_Quagsire),
    SPECIES_SHINY_PAL(ESPEON, gMonShinyPalette_Espeon),
    SPECIES_SHINY_PAL(UMBREON, gMonShinyPalette_Umbreon),
    SPECIES_SHINY_PAL(MURKROW, gMonShinyPalette_Murkrow),
    SPECIES_SHINY_PAL(SLOWKING, gMonShinyPalette_Slowking),
    SPECIES_SHINY_PAL(MISDREAVUS, gMonShinyPalette_Misdreavus),
    SPECIES_SHINY_PAL(UNOWN, gMonShinyPalette_Unown),
    SPECIES_SHINY_PAL(WOBBUFFET, gMonShinyPalette_Wobbuffet),
    SPECIES_SHINY_PAL(GIRAFARIG, gMonShinyPalette_Girafarig),
    SPECIES_SHINY_PAL(PINECO, gMonShinyPalette_Pineco),
    SPECIES_SHINY_PAL(FORRETRESS, gMonShinyPalette_Forretress),
    SPECIES_SHINY_PAL(DUNSPARCE, gMonShinyPalette_Dunsparce),
    SPECIES_SHINY_PAL(GLIGAR, gMonShinyPalette_Gligar),
    SPECIES_SHINY_PAL(STEELIX, gMonShinyPalette_Steelix),
    SPECIES_SHINY_PAL(SNUBBULL, gMonShinyPalette_Snubbull),
    SPECIES_SHINY_PAL(GRANBULL, gMonShinyPalette_Granbull),
    SPECIES_SHINY_PAL(QWILFISH, gMonShinyPalette_Qwilfish),
    SPECIES_SHINY_PAL(SCIZOR, gMonShinyPalette_Scizor),
    SPECIES_SHINY_PAL(SHUCKLE, gMonShinyPalette_Shuckle),
    SPECIES_SHINY_PAL(HERACROSS, gMonShinyPalette_Heracross),
    SPECIES_SHINY_PAL(SNEASEL, gMonShinyPalette_Sneasel),
    SPECIES_SHINY_PAL(TEDDIURSA, gMonShinyPalette_Teddiursa),
    SPECIES_SHINY_PAL(URSARING, gMonShinyPalette_Ursaring),
    SPECIES_SHINY_PAL(SLUGMA, gMonShinyPalette_Slugma),
    SPECIES_SHINY_PAL(MAGCARGO, gMonShinyPalette_Magcargo),
    SPECIES_SHINY_PAL(SWINUB, gMonShinyPalette_Swinub),
    SPECIES_SHINY_PAL(PILOSWINE, gMonShinyPalette_Piloswine),
    SPECIES_SHINY_PAL(CORSOLA, gMonShinyPalette_Corsola),
    SPECIES_SHINY_PAL(REMORAID, gMonShinyPalette_Remoraid),
    SPECIES_SHINY_PAL(OCTILLERY, gMonShinyPalette_Octillery),
    SPECIES_SHINY_PAL(DELIBIRD, gMonShinyPalette_Delibird),
    SPECIES_SHINY_PAL(MANTINE, gMonShinyPalette_Mantine),
    SPECIES_SHINY_PAL(SKARMORY, gMonShinyPalette_Skarmory),
    SPECIES_SHINY_PAL(HOUNDOUR, gMonShinyPalette_Houndour),
    SPECIES_SHINY_PAL(HOUNDOOM, gMonShinyPalette_Houndoom),
    SPECIES_SHINY_PAL(KINGDRA, gMonShinyPalette_Kingdra),
    SPECIES_SHINY_PAL(PHANPY, gMonShinyPalette_Phanpy),
    SPECIES_SHINY_PAL(DONPHAN, gMonShinyPalette_Donphan),
    SPECIES_SHINY_PAL(PORYGON2, gMonShinyPalette_Porygon2),
    SPECIES_SHINY_PAL(STANTLER, gMonShinyPalette_Stantler),
    SPECIES_SHINY_PAL(SMEARGLE, gMonShinyPalette_Smeargle),
    SPECIES_SHINY_PAL(TYROGUE, gMonShinyPalette_Tyrogue),
    SPECIES_SHINY_PAL(HITMONTOP, gMonShinyPalette_Hitmontop),
    SPECIES_SHINY_PAL(SMOOCHUM, gMonShinyPalette_Smoochum),
    SPECIES_SHINY_PAL(ELEKID, gMonShinyPalette_Elekid),
    SPECIES_SHINY_PAL(MAGBY, gMonShinyPalette_Magby),
    SPECIES_SHINY_PAL(MILTANK, gMonShinyPalette_Miltank),
    SPECIES_SHINY_PAL(BLISSEY, gMonShinyPalette_Blissey),
    SPECIES_SHINY_PAL(RAIKOU, gMonShinyPalette_Raikou),
    SPECIES_SHINY_PAL(ENTEI, gMonShinyPalette_Entei),
    SPECIES_SHINY_PAL(SUICUNE, gMonShinyPalette_Suicune),
    SPECIES_SHINY_PAL(LARVITAR, gMonShinyPalette_Larvitar),
    SPECIES_SHINY_PAL(PUPITAR, gMonShinyPalette_Pupitar),
    SPECIES_SHINY_PAL(TYRANITAR, gMonShinyPalette_Tyranitar),
    SPECIES_SHINY_PAL(LUGIA, gMonShinyPalette_Lugia),
    SPECIES_SHINY_PAL(HO_OH, gMonShinyPalette_HoOh),
    SPECIES_SHINY_PAL(CELEBI, gMonShinyPalette_Celebi),
    SPECIES_SHINY_PAL(OLD_UNOWN_B, gMonShinyPalette_DoubleQuestionMark),
    SPECIES_SHINY_PAL(OLD_UNOWN_C, gMonShinyPalette_DoubleQuestionMark),
    SPECIES_SHINY_PAL(OLD_UNOWN_D, gMonShinyPalette_DoubleQuestionMark),
    SPECIES_SHINY_PAL(OLD_UNOWN_E, gMonShinyPalette_DoubleQuestionMark),
    SPECIES_SHINY_PAL(OLD_UNOWN_F, gMonShinyPalette_DoubleQuestionMark),
    SPECIES_SHINY_PAL(OLD_UNOWN_G, gMonShinyPalette_DoubleQuestionMark),
    SPECIES_SHINY_PAL(OLD_UNOWN_H, gMonShinyPalette_DoubleQuestionMark),
    SPECIES_SHINY_PAL(OLD_UNOWN_I, gMonShinyPalette_DoubleQuestionMark),
    SPECIES_SHINY_PAL(OLD_UNOWN_J, gMonShinyPalette_DoubleQuestionMark),
    SPECIES_SHINY_PAL(OLD_UNOWN_K, gMonShinyPalette_DoubleQuestionMark),
    SPECIES_SHINY_PAL(OLD_UNOWN_L, gMonShinyPalette_DoubleQuestionMark),
    SPECIES_SHINY_PAL(OLD_UNOWN_M, gMonShinyPalette_DoubleQuestionMark),
    SPECIES_SHINY_PAL(OLD_UNOWN_N, gMonShinyPalette_DoubleQuestionMark),
    SPECIES_SHINY_PAL(OLD_UNOWN_O, gMonShinyPalette_DoubleQuestionMark),
    SPECIES_SHINY_PAL(OLD_UNOWN_P, gMonShinyPalette_DoubleQuestionMark),
    SPECIES_SHINY_PAL(OLD_UNOWN_Q, gMonShinyPalette_DoubleQuestionMark),
    SPECIES_SHINY_PAL(OLD_UNOWN_R, gMonShinyPalette_DoubleQuestionMark),
    SPECIES_SHINY_PAL(OLD_UNOWN_S, gMonShinyPalette_DoubleQuestionMark),
    SPECIES_SHINY_PAL(OLD_UNOWN_T, gMonShinyPalette_DoubleQuestionMark),
    SPECIES_SHINY_PAL(OLD_UNOWN_U, gMonShinyPalette_DoubleQuestionMark),
    SPECIES_SHINY_PAL(OLD_UNOWN_V, gMonShinyPalette_DoubleQuestionMark),
    SPECIES_SHINY_PAL(OLD_UNOWN_W, gMonShinyPalette_DoubleQuestionMark),
    SPECIES_SHINY_PAL(OLD_UNOWN_X, gMonShinyPalette_DoubleQuestionMark),
    SPECIES_SHINY_PAL(OLD_UNOWN_Y, gMonShinyPalette_DoubleQuestionMark),
    SPECIES_SHINY_PAL(OLD_UNOWN_Z, gMonShinyPalette_DoubleQuestionMark),
    SPECIES_SHINY_PAL(TREECKO, gMonShinyPalette_Treecko),
    SPECIES_SHINY_PAL(GROVYLE, gMonShinyPalette_Grovyle),
    SPECIES_SHINY_PAL(SCEPTILE, gMonShinyPalette_Sceptile),
    SPECIES_SHINY_PAL(TORCHIC, gMonShinyPalette_Torchic),
    SPECIES_SHINY_PAL(COMBUSKEN, gMonShinyPalette_Combusken),
    SPECIES_SHINY_PAL(BLAZIKEN, gMonShinyPalette_Blaziken),
    SPECIES_SHINY_PAL(MUDKIP, gMonShinyPalette_Mudkip),
    SPECIES_SHINY_PAL(MARSHTOMP, gMonShinyPalette_Marshtomp),
    SPECIES_SHINY_PAL(SWAMPERT, gMonShinyPalette_Swampert),
    SPECIES_SHINY_PAL(POOCHYENA, gMonShinyPalette_Poochyena),
    SPECIES_SHINY_PAL(MIGHTYENA, gMonShinyPalette_Mightyena),
    SPECIES_SHINY_PAL(ZIGZAGOON, gMonShinyPalette_Zigzagoon),
    SPECIES_SHINY_PAL(LINOONE, gMonShinyPalette_Linoone),
    SPECIES_SHINY_PAL(WURMPLE, gMonShinyPalette_Wurmple),
    SPECIES_SHINY_PAL(SILCOON, gMonShinyPalette_Silcoon),
    SPECIES_SHINY_PAL(BEAUTIFLY, gMonShinyPalette_Beautifly),
    SPECIES_SHINY_PAL(CASCOON, gMonShinyPalette_Cascoon),
    SPECIES_SHINY_PAL(DUSTOX, gMonShinyPalette_Dustox),
    SPECIES_SHINY_PAL(LOTAD, gMonShinyPalette_Lotad),
    SPECIES_SHINY_PAL(LOMBRE, gMonShinyPalette_Lombre),
    SPECIES_SHINY_PAL(LUDICOLO, gMonShinyPalette_Ludicolo),
    SPECIES_SHINY_PAL(SEEDOT, gMonShinyPalette_Seedot),
    SPECIES_SHINY_PAL(NUZLEAF, gMonShinyPalette_Nuzleaf),
    SPECIES_SHINY_PAL(SHIFTRY, gMonShinyPalette_Shiftry),
    SPECIES_SHINY_PAL(NINCADA, gMonShinyPalette_Nincada),
    SPECIES_SHINY_PAL(NINJASK, gMonShinyPalette_Ninjask),
    SPECIES_SHINY_PAL(SHEDINJA, gMonShinyPalette_Shedinja),
    SPECIES_SHINY_PAL(TAILLOW, gMonShinyPalette_Taillow),
    SPECIES_SHINY_PAL(SWELLOW, gMonShinyPalette_Swellow),
    SPECIES_SHINY_PAL(SHROOMISH, gMonShinyPalette_Shroomish),
    SPECIES_SHINY_PAL(BRELOOM, gMonShinyPalette_Breloom),
    SPECIES_SHINY_PAL(SPINDA, gMonShinyPalette_Spinda),
    SPECIES_SHINY_PAL(WINGULL, gMonShinyPalette_Wingull),
    SPECIES_SHINY_PAL(PELIPPER, gMonShinyPalette_Pelipper),
    SPECIES_SHINY_PAL(SURSKIT, gMonShinyPalette_Surskit),
    SPECIES_SHINY_PAL(MASQUERAIN, gMonShinyPalette_Masquerain),
    SPECIES_SHINY_PAL(WAILMER, gMonShinyPalette_Wailmer),
    SPECIES_SHINY_PAL(WAILORD, gMonShinyPalette_Wailord),
    SPECIES_SHINY_PAL(SKITTY, gMonShinyPalette_Skitty),
    SPECIES_SHINY_PAL(DELCATTY, gMonShinyPalette_Delcatty),
    SPECIES_SHINY_PAL(KECLEON, gMonShinyPalette_Kecleon),
    SPECIES_SHINY_PAL(BALTOY, gMonShinyPalette_Baltoy),
    SPECIES_SHINY_PAL(CLAYDOL, gMonShinyPalette_Claydol),
    SPECIES_SHINY_PAL(NOSEPASS, gMonShinyPalette_Nosepass),
    SPECIES_SHINY_PAL(TORKOAL, gMonShinyPalette_Torkoal),
    SPECIES_SHINY_PAL(SABLEYE, gMonShinyPalette_Sableye),
    SPECIES_SHINY_PAL(BARBOACH, gMonShinyPalette_Barboach),
    SPECIES_SHINY_PAL(WHISCASH, gMonShinyPalette_Whiscash),
    SPECIES_SHINY_PAL(LUVDISC, gMonShinyPalette_Luvdisc),
    SPECIES_SHINY_PAL(CORPHISH, gMonShinyPalette_Corphish),
    SPECIES_SHINY_PAL(CRAWDAUNT, gMonShinyPalette_Crawdaunt),
    SPECIES_SHINY_PAL(FEEBAS, gMonShinyPalette_Feebas),
    SPECIES_SHINY_PAL(MILOTIC, gMonShinyPalette_Milotic),
    SPECIES_SHINY_PAL(CARVANHA, gMonShinyPalette_Carvanha),
    SPECIES_SHINY_PAL(SHARPEDO, gMonShinyPalette_Sharpedo),
    SPECIES_SHINY_PAL(TRAPINCH, gMonShinyPalette_Trapinch),
    SPECIES_SHINY_PAL(VIBRAVA, gMonShinyPalette_Vibrava),
    SPECIES_SHINY_PAL(FLYGON, gMonShinyPalette_Flygon),
    SPECIES_SHINY_PAL(MAKUHITA, gMonShinyPalette_Makuhita),
    SPECIES_SHINY_PAL(HARIYAMA, gMonShinyPalette_Hariyama),
    SPECIES_SHINY_PAL(ELECTRIKE, gMonShinyPalette_Electrike),
    SPECIES_SHINY_PAL(MANECTRIC, gMonShinyPalette_Manectric),
    SPECIES_SHINY_PAL(NUMEL, gMonShinyPalette_Numel),
    SPECIES_SHINY_PAL(CAMERUPT, gMonShinyPalette_Camerupt),
    SPECIES_SHINY_PAL(SPHEAL, gMonShinyPalette_Spheal),
    SPECIES_SHINY_PAL(SEALEO, gMonShinyPalette_Sealeo),
    SPECIES_SHINY_PAL(WALREIN, gMonShinyPalette_Walrein),
    SPECIES_SHINY_PAL(CACNEA, gMonShinyPalette_Cacnea),
    SPECIES_SHINY_PAL(CACTURNE, gMonShinyPalette_Cacturne),
    SPECIES_SHINY_PAL(SNORUNT, gMonShinyPalette_Snorunt),
    SPECIES_SHINY_PAL(GLALIE, gMonShinyPalette_Glalie),
    SPECIES_SHINY_PAL(LUNATONE, gMonShinyPalette_Lunatone),
    SPECIES_SHINY_PAL(SOLROCK, gMonShinyPalette_Solrock),
    SPECIES_SHINY_PAL(AZURILL, gMonShinyPalette_Azurill),
    SPECIES_SHINY_PAL(SPOINK, gMonShinyPalette_Spoink),
    SPECIES_SHINY_PAL(GRUMPIG, gMonShinyPalette_Grumpig),
    SPECIES_SHINY_PAL(PLUSLE, gMonShinyPalette_Plusle),
    SPECIES_SHINY_PAL(MINUN, gMonShinyPalette_Minun),
    SPECIES_SHINY_PAL(MAWILE, gMonShinyPalette_Mawile),
    SPECIES_SHINY_PAL(MEDITITE, gMonShinyPalette_Meditite),
    SPECIES_SHINY_PAL(MEDICHAM, gMonShinyPalette_Medicham),
    SPECIES_SHINY_PAL(SWABLU, gMonShinyPalette_Swablu),
    SPECIES_SHINY_PAL(ALTARIA, gMonShinyPalette_Altaria),
    SPECIES_SHINY_PAL(WYNAUT, gMonShinyPalette_Wynaut),
    SPECIES_SHINY_PAL(DUSKULL, gMonShinyPalette_Duskull),
    SPECIES_SHINY_PAL(DUSCLOPS, gMonShinyPalette_Dusclops),
    SPECIES_SHINY_PAL(ROSELIA, gMonShinyPalette_Roselia),
    SPECIES_SHINY_PAL(SLAKOTH, gMonShinyPalette_Slakoth),
    SPECIES_SHINY_PAL(VIGOROTH, gMonShinyPalette_Vigoroth),
    SPECIES_SHINY_PAL(SLAKING, gMonShinyPalette_Slaking),
    SPECIES_SHINY_PAL(GULPIN, gMonShinyPalette_Gulpin),
    SPECIES_SHINY_PAL(SWALOT, gMonShinyPalette_Swalot),
    SPECIES_SHINY_PAL(TROPIUS, gMonShinyPalette_Tropius),
    SPECIES_SHINY_PAL(WHISMUR, gMonShinyPalette_Whismur),
    SPECIES_SHINY_PAL(LOUDRED, gMonShinyPalette_Loudred),
    SPECIES_SHINY_PAL(EXPLOUD, gMonShinyPalette_Exploud),
    SPECIES_SHINY_PAL(CLAMPERL, gMonShinyPalette_Clamperl),
    SPECIES_SHINY_PAL(HUNTAIL, gMonShinyPalette_Huntail),
    SPECIES_SHINY_PAL(GOREBYSS, gMonShinyPalette_Gorebyss),
    SPECIES_SHINY_PAL(ABSOL, gMonShinyPalette_Absol),
    SPECIES_SHINY_PAL(SHUPPET, gMonShinyPalette_Shuppet),
    SPECIES_SHINY_PAL(BANETTE, gMonShinyPalette_Banette),
    SPECIES_SHINY_PAL(SEVIPER, gMonShinyPalette_Seviper),
    SPECIES_SHINY_PAL(ZANGOOSE, gMonShinyPalette_Zangoose),
    SPECIES_SHINY_PAL(RELICANTH, gMonShinyPalette_Relicanth),
    SPECIES_SHINY_PAL(ARON, gMonShinyPalette_Aron),
    SPECIES_SHINY_PAL(LAIRON, gMonShinyPalette_Lairon),
    SPECIES_SHINY_PAL(AGGRON, gMonShinyPalette_Aggron),
    SPECIES_SHINY_PAL(CASTFORM, gMonShinyPalette_Castform),
    SPECIES_SHINY_PAL(VOLBEAT, gMonShinyPalette_Volbeat),
    SPECIES_SHINY_PAL(ILLUMISE, gMonShinyPalette_Illumise),
    SPECIES_SHINY_PAL(LILEEP, gMonShinyPalette_Lileep),
    SPECIES_SHINY_PAL(CRADILY, gMonShinyPalette_Cradily),
    SPECIES_SHINY_PAL(ANORITH, gMonShinyPalette_Anorith),
    SPECIES_SHINY_PAL(ARMALDO, gMonShinyPalette_Armaldo),
    SPECIES_SHINY_PAL(RALTS, gMonShinyPalette_Ralts),
    SPECIES_SHINY_PAL(KIRLIA, gMonShinyPalette_Kirlia),
    SPECIES_SHINY_PAL(GARDEVOIR, gMonShinyPalette_Gardevoir),
    SPECIES_SHINY_PAL(BAGON, gMonShinyPalette_Bagon),
    SPECIES_SHINY_PAL(SHELGON, gMonShinyPalette_Shelgon),
    SPECIES_SHINY_PAL(SALAMENCE, gMonShinyPalette_Salamence),
    SPECIES_SHINY_PAL(BELDUM, gMonShinyPalette_Beldum),
    SPECIES_SHINY_PAL(METANG, gMonShinyPalette_Metang),
    SPECIES_SHINY_PAL(METAGROSS, gMonShinyPalette_Metagross),
    SPECIES_SHINY_PAL(REGIROCK, gMonShinyPalette_Regirock),
    SPECIES_SHINY_PAL(REGICE, gMonShinyPalette_Regice),
    SPECIES_SHINY_PAL(REGISTEEL, gMonShinyPalette_Registeel),
    SPECIES_SHINY_PAL(KYOGRE, gMonShinyPalette_Kyogre),
    SPECIES_SHINY_PAL(GROUDON, gMonShinyPalette_Groudon),
    SPECIES_SHINY_PAL(RAYQUAZA, gMonShinyPalette_Rayquaza),
    SPECIES_SHINY_PAL(LATIAS, gMonShinyPalette_Latias),
    SPECIES_SHINY_PAL(LATIOS, gMonShinyPalette_Latios),
    SPECIES_SHINY_PAL(JIRACHI, gMonShinyPalette_Jirachi),
    SPECIES_SHINY_PAL(DEOXYS, gMonShinyPalette_Deoxys),
    SPECIES_SHINY_PAL(CHIMECHO, gMonShinyPalette_Chimecho),
    SPECIES_SHINY_PAL(EGG, gMonPalette_Egg),
    SPECIES_SHINY_PAL(UNOWN_B, gMonShinyPalette_Unown),
    SPECIES_SHINY_PAL(UNOWN_C, gMonShinyPalette_Unown),
    SPECIES_SHINY_PAL(UNOWN_D, gMonShinyPalette_Unown),
    SPECIES_SHINY_PAL(UNOWN_E, gMonShinyPalette_Unown),
    SPECIES_SHINY_PAL(UNOWN_F, gMonShinyPalette_Unown),
    SPECIES_SHINY_PAL(UNOWN_G, gMonShinyPalette_Unown),
    SPECIES_SHINY_PAL(UNOWN_H, gMonShinyPalette_Unown),
    SPECIES_SHINY_PAL(UNOWN_I, gMonShinyPalette_Unown),
    SPECIES_SHINY_PAL(UNOWN_J, gMonShinyPalette_Unown),
    SPECIES_SHINY_PAL(UNOWN_K, gMonShinyPalette_Unown),
    SPECIES_SHINY_PAL(UNOWN_L, gMonShinyPalette_Unown),
    SPECIES_SHINY_PAL(UNOWN_M, gMonShinyPalette_Unown),
    SPECIES_SHINY_PAL(UNOWN_N, gMonShinyPalette_Unown),
    SPECIES_SHINY_PAL(UNOWN_O, gMonShinyPalette_Unown),
    SPECIES_SHINY_PAL(UNOWN_P, gMonShinyPalette_Unown),
    SPECIES_SHINY_PAL(UNOWN_Q, gMonShinyPalette_Unown),
    SPECIES_SHINY_PAL(UNOWN_R, gMonShinyPalette_Unown),
    SPECIES_SHINY_PAL(UNOWN_S, gMonShinyPalette_Unown),
    SPECIES_SHINY_PAL(UNOWN_T, gMonShinyPalette_Unown),
    SPECIES_SHINY_PAL(UNOWN_U, gMonShinyPalette_Unown),
    SPECIES_SHINY_PAL(UNOWN_V, gMonShinyPalette_Unown),
    SPECIES_SHINY_PAL(UNOWN_W, gMonShinyPalette_Unown),
    SPECIES_SHINY_PAL(UNOWN_X, gMonShinyPalette_Unown),
    SPECIES_SHINY_PAL(UNOWN_Y, gMonShinyPalette_Unown),
    SPECIES_SHINY_PAL(UNOWN_Z, gMonShinyPalette_Unown),
    SPECIES_SHINY_PAL(UNOWN_EMARK, gMonShinyPalette_Unown),
    SPECIES_SHINY_PAL(UNOWN_QMARK, gMonShinyPalette_Unown),
};
// ===== END src/data/pokemon_graphics/shiny_palette_table.h =====

// ===== BEGIN src/data/trainer_graphics/front_pic_anims.h =====
static const union AnimCmd *const sAnims_AquaLeaderArchie[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_AquaGruntM[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_AquaGruntF[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_RSAromaLady[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_RSRuinManiac[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_Interviewer[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_RSTuberF[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_RSTuberM[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_RSCooltrainerM[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_RSCooltrainerF[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_HexManiac[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_RSLady[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_RSBeauty[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_RichBoy[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_RSPokemaniac[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_RSSwimmerM[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_RSBlackBelt[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_Guitarist[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_Kindler[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_RSCamper[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_BugManiac[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_RSPsychicM[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_RSPsychicF[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_RSGentleman[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_EliteFourSidney[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_EliteFourPhoebe[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_LeaderRoxanne[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_LeaderBrawly[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_LeaderTateAndLiza[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_SchoolKidM[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_SchoolKidF[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_SrAndJr[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_PokefanM[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_PokefanF[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_ExpertM[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_ExpertF[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_RSYoungster[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_ChampionSteven[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_RSFisherman[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_CyclingTriathleteM[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_CyclingTriathleteF[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_RunningTriathleteM[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_RunningTriathleteF[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_SwimmingTriathleteM[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_SwimmingTriathleteF[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_DragonTamer[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_RSBirdKeeper[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_NinjaBoy[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_BattleGirl[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_ParasolLady[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_RSSwimmerF[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_RSPicnicker[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_RSTwins[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_RSSailor[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_Collector[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_Wally[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_RSBrendan1[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_RSMay1[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_RSPokemonBreederM[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_RSPokemonBreederF[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_RSPokemonRangerM[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_RSPokemonRangerF[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_MagmaLeaderMaxie[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_MagmaGruntM[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_MagmaGruntF[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_RSLass[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_RSBugCatcher[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_RSHiker[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_RSYoungCouple[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_OldCouple[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_RSSisAndBro[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_AquaAdminM[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_AquaAdminF[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_MagmaAdminM[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_MagmaAdminF[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_LeaderWattson[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_LeaderFlannery[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_LeaderNorman[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_LeaderWinona[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_LeaderWallace[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_EliteFourGlacia[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_EliteFourDrake[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_Youngster[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_BugCatcher[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_Lass[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_Sailor[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_Camper[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_Picnicker[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_Pokemaniac[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_SuperNerd[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_Hiker[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_Biker[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_Burglar[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_Engineer[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_Fisherman[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_SwimmerM[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_CueBall[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_Gamer[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_Beauty[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_SwimmerF[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_PsychicM[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_Rocker[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_Juggler[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_Tamer[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_BirdKeeper[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_BlackBelt[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_RivalEarly[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_Scientist[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_LeaderGiovanni[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_RocketGruntM[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_CooltrainerM[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_CooltrainerF[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_EliteFourLorelei[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_EliteFourBruno[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_EliteFourAgatha[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_EliteFourLance[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_LeaderBrock[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_LeaderMisty[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_LeaderLtSurge[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_LeaderErika[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_LeaderKoga[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_LeaderBlaine[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_LeaderSabrina[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_Gentleman[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_RivalLate[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_ChampionRival[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_Channeler[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_Twins[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_CoolCouple[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_YoungCouple[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_CrushKin[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_SisAndBro[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_ProfessorOak[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_RSBrendan2[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_RSMay2[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_Red[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_Leaf[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_RocketGruntF[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_PsychicF[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_CrushGirl[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_TuberF[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_PokemonBreeder[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_PokemonRangerM[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_PokemonRangerF[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_AromaLady[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_RuinManiac[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_Lady[] =
{
    sAnim_GeneralFrame0,
};

static const union AnimCmd *const sAnims_Painter[] =
{
    sAnim_GeneralFrame0,
};

const union AnimCmd *const *const gTrainerFrontAnimsPtrTable[] =
{
    [TRAINER_PIC_AQUA_LEADER_ARCHIE]    = sAnims_AquaLeaderArchie,
    [TRAINER_PIC_AQUA_GRUNT_M]          = sAnims_AquaGruntM,
    [TRAINER_PIC_AQUA_GRUNT_F]          = sAnims_AquaGruntF,
    [TRAINER_PIC_RS_AROMA_LADY]         = sAnims_RSAromaLady,
    [TRAINER_PIC_RS_RUIN_MANIAC]        = sAnims_RSRuinManiac,
    [TRAINER_PIC_INTERVIEWER]           = sAnims_Interviewer,
    [TRAINER_PIC_RS_TUBER_F]            = sAnims_RSTuberF,
    [TRAINER_PIC_RS_TUBER_M]            = sAnims_RSTuberM,
    [TRAINER_PIC_RS_COOLTRAINER_M]      = sAnims_RSCooltrainerM,
    [TRAINER_PIC_RS_COOLTRAINER_F]      = sAnims_RSCooltrainerF,
    [TRAINER_PIC_HEX_MANIAC]            = sAnims_HexManiac,
    [TRAINER_PIC_RS_LADY]               = sAnims_RSLady,
    [TRAINER_PIC_RS_BEAUTY]             = sAnims_RSBeauty,
    [TRAINER_PIC_RICH_BOY]              = sAnims_RichBoy,
    [TRAINER_PIC_RS_POKEMANIAC]         = sAnims_RSPokemaniac,
    [TRAINER_PIC_RS_SWIMMER_M]          = sAnims_RSSwimmerM,
    [TRAINER_PIC_RS_BLACK_BELT]         = sAnims_RSBlackBelt,
    [TRAINER_PIC_GUITARIST]             = sAnims_Guitarist,
    [TRAINER_PIC_KINDLER]               = sAnims_Kindler,
    [TRAINER_PIC_RS_CAMPER]             = sAnims_RSCamper,
    [TRAINER_PIC_BUG_MANIAC]            = sAnims_BugManiac,
    [TRAINER_PIC_RS_PSYCHIC_M]          = sAnims_RSPsychicM,
    [TRAINER_PIC_RS_PSYCHIC_F]          = sAnims_RSPsychicF,
    [TRAINER_PIC_RS_GENTLEMAN]          = sAnims_RSGentleman,
    [TRAINER_PIC_ELITE_FOUR_SIDNEY]     = sAnims_EliteFourSidney,
    [TRAINER_PIC_ELITE_FOUR_PHOEBE]     = sAnims_EliteFourPhoebe,
    [TRAINER_PIC_LEADER_ROXANNE]        = sAnims_LeaderRoxanne,
    [TRAINER_PIC_LEADER_BRAWLY]         = sAnims_LeaderBrawly,
    [TRAINER_PIC_LEADER_TATE_AND_LIZA]  = sAnims_LeaderTateAndLiza,
    [TRAINER_PIC_SCHOOL_KID_M]          = sAnims_SchoolKidM,
    [TRAINER_PIC_SCHOOL_KID_F]          = sAnims_SchoolKidF,
    [TRAINER_PIC_SR_AND_JR]             = sAnims_SrAndJr,
    [TRAINER_PIC_POKEFAN_M]             = sAnims_PokefanM,
    [TRAINER_PIC_POKEFAN_F]             = sAnims_PokefanF,
    [TRAINER_PIC_EXPERT_M]              = sAnims_ExpertM,
    [TRAINER_PIC_EXPERT_F]              = sAnims_ExpertF,
    [TRAINER_PIC_RS_YOUNGSTER]          = sAnims_RSYoungster,
    [TRAINER_PIC_CHAMPION_STEVEN]       = sAnims_ChampionSteven,
    [TRAINER_PIC_RS_FISHERMAN]          = sAnims_RSFisherman,
    [TRAINER_PIC_CYCLING_TRIATHLETE_M]  = sAnims_CyclingTriathleteM,
    [TRAINER_PIC_CYCLING_TRIATHLETE_F]  = sAnims_CyclingTriathleteF,
    [TRAINER_PIC_RUNNING_TRIATHLETE_M]  = sAnims_RunningTriathleteM,
    [TRAINER_PIC_RUNNING_TRIATHLETE_F]  = sAnims_RunningTriathleteF,
    [TRAINER_PIC_SWIMMING_TRIATHLETE_M] = sAnims_SwimmingTriathleteM,
    [TRAINER_PIC_SWIMMING_TRIATHLETE_F] = sAnims_SwimmingTriathleteF,
    [TRAINER_PIC_DRAGON_TAMER]          = sAnims_DragonTamer,
    [TRAINER_PIC_RS_BIRD_KEEPER]        = sAnims_RSBirdKeeper,
    [TRAINER_PIC_NINJA_BOY]             = sAnims_NinjaBoy,
    [TRAINER_PIC_BATTLE_GIRL]           = sAnims_BattleGirl,
    [TRAINER_PIC_PARASOL_LADY]          = sAnims_ParasolLady,
    [TRAINER_PIC_RS_SWIMMER_F]          = sAnims_RSSwimmerF,
    [TRAINER_PIC_RS_PICNICKER]          = sAnims_RSPicnicker,
    [TRAINER_PIC_RS_TWINS]              = sAnims_RSTwins,
    [TRAINER_PIC_RS_SAILOR]             = sAnims_RSSailor,
    [TRAINER_PIC_COLLECTOR]             = sAnims_Collector,
    [TRAINER_PIC_WALLY]                 = sAnims_Wally,
    [TRAINER_PIC_RS_BRENDAN_1]          = sAnims_RSBrendan1,
    [TRAINER_PIC_RS_MAY_1]              = sAnims_RSMay1,
    [TRAINER_PIC_RS_POKEMON_BREEDER_M]  = sAnims_RSPokemonBreederM,
    [TRAINER_PIC_RS_POKEMON_BREEDER_F]  = sAnims_RSPokemonBreederF,
    [TRAINER_PIC_RS_POKEMON_RANGER_M]   = sAnims_RSPokemonRangerM,
    [TRAINER_PIC_RS_POKEMON_RANGER_F]   = sAnims_RSPokemonRangerF,
    [TRAINER_PIC_MAGMA_LEADER_MAXIE]    = sAnims_MagmaLeaderMaxie,
    [TRAINER_PIC_MAGMA_GRUNT_M]         = sAnims_MagmaGruntM,
    [TRAINER_PIC_MAGMA_GRUNT_F]         = sAnims_MagmaGruntF,
    [TRAINER_PIC_RS_LASS]               = sAnims_RSLass,
    [TRAINER_PIC_RS_BUG_CATCHER]        = sAnims_RSBugCatcher,
    [TRAINER_PIC_RS_HIKER]              = sAnims_RSHiker,
    [TRAINER_PIC_RS_YOUNG_COUPLE]       = sAnims_RSYoungCouple,
    [TRAINER_PIC_OLD_COUPLE]            = sAnims_OldCouple,
    [TRAINER_PIC_RS_SIS_AND_BRO]        = sAnims_RSSisAndBro,
    [TRAINER_PIC_AQUA_ADMIN_M]          = sAnims_AquaAdminM,
    [TRAINER_PIC_AQUA_ADMIN_F]          = sAnims_AquaAdminF,
    [TRAINER_PIC_MAGMA_ADMIN_M]         = sAnims_MagmaAdminM,
    [TRAINER_PIC_MAGMA_ADMIN_F]         = sAnims_MagmaAdminF,
    [TRAINER_PIC_LEADER_WATTSON]        = sAnims_LeaderWattson,
    [TRAINER_PIC_LEADER_FLANNERY]       = sAnims_LeaderFlannery,
    [TRAINER_PIC_LEADER_NORMAN]         = sAnims_LeaderNorman,
    [TRAINER_PIC_LEADER_WINONA]         = sAnims_LeaderWinona,
    [TRAINER_PIC_LEADER_WALLACE]        = sAnims_LeaderWallace,
    [TRAINER_PIC_ELITE_FOUR_GLACIA]     = sAnims_EliteFourGlacia,
    [TRAINER_PIC_ELITE_FOUR_DRAKE]      = sAnims_EliteFourDrake,
    [TRAINER_PIC_YOUNGSTER]             = sAnims_Youngster,
    [TRAINER_PIC_BUG_CATCHER]           = sAnims_BugCatcher,
    [TRAINER_PIC_LASS]                  = sAnims_Lass,
    [TRAINER_PIC_SAILOR]                = sAnims_Sailor,
    [TRAINER_PIC_CAMPER]                = sAnims_Camper,
    [TRAINER_PIC_PICNICKER]             = sAnims_Picnicker,
    [TRAINER_PIC_POKEMANIAC]            = sAnims_Pokemaniac,
    [TRAINER_PIC_SUPER_NERD]            = sAnims_SuperNerd,
    [TRAINER_PIC_HIKER]                 = sAnims_Hiker,
    [TRAINER_PIC_BIKER]                 = sAnims_Biker,
    [TRAINER_PIC_BURGLAR]               = sAnims_Burglar,
    [TRAINER_PIC_ENGINEER]              = sAnims_Engineer,
    [TRAINER_PIC_FISHERMAN]             = sAnims_Fisherman,
    [TRAINER_PIC_SWIMMER_M]             = sAnims_SwimmerM,
    [TRAINER_PIC_CUE_BALL]              = sAnims_CueBall,
    [TRAINER_PIC_GAMER]                 = sAnims_Gamer,
    [TRAINER_PIC_BEAUTY]                = sAnims_Beauty,
    [TRAINER_PIC_SWIMMER_F]             = sAnims_SwimmerF,
    [TRAINER_PIC_PSYCHIC_M]             = sAnims_PsychicM,
    [TRAINER_PIC_ROCKER]                = sAnims_Rocker,
    [TRAINER_PIC_JUGGLER]               = sAnims_Juggler,
    [TRAINER_PIC_TAMER]                 = sAnims_Tamer,
    [TRAINER_PIC_BIRD_KEEPER]           = sAnims_BirdKeeper,
    [TRAINER_PIC_BLACK_BELT]            = sAnims_BlackBelt,
    [TRAINER_PIC_RIVAL_EARLY]           = sAnims_RivalEarly,
    [TRAINER_PIC_SCIENTIST]             = sAnims_Scientist,
    [TRAINER_PIC_LEADER_GIOVANNI]       = sAnims_LeaderGiovanni,
    [TRAINER_PIC_ROCKET_GRUNT_M]        = sAnims_RocketGruntM,
    [TRAINER_PIC_COOLTRAINER_M]         = sAnims_CooltrainerM,
    [TRAINER_PIC_COOLTRAINER_F]         = sAnims_CooltrainerF,
    [TRAINER_PIC_ELITE_FOUR_LORELEI]    = sAnims_EliteFourLorelei,
    [TRAINER_PIC_ELITE_FOUR_BRUNO]      = sAnims_EliteFourBruno,
    [TRAINER_PIC_ELITE_FOUR_AGATHA]     = sAnims_EliteFourAgatha,
    [TRAINER_PIC_ELITE_FOUR_LANCE]      = sAnims_EliteFourLance,
    [TRAINER_PIC_LEADER_BROCK]          = sAnims_LeaderBrock,
    [TRAINER_PIC_LEADER_MISTY]          = sAnims_LeaderMisty,
    [TRAINER_PIC_LEADER_LT_SURGE]       = sAnims_LeaderLtSurge,
    [TRAINER_PIC_LEADER_ERIKA]          = sAnims_LeaderErika,
    [TRAINER_PIC_LEADER_KOGA]           = sAnims_LeaderKoga,
    [TRAINER_PIC_LEADER_BLAINE]         = sAnims_LeaderBlaine,
    [TRAINER_PIC_LEADER_SABRINA]        = sAnims_LeaderSabrina,
    [TRAINER_PIC_GENTLEMAN]             = sAnims_Gentleman,
    [TRAINER_PIC_RIVAL_LATE]            = sAnims_RivalLate,
    [TRAINER_PIC_CHAMPION_RIVAL]        = sAnims_ChampionRival,
    [TRAINER_PIC_CHANNELER]             = sAnims_Channeler,
    [TRAINER_PIC_TWINS]                 = sAnims_Twins,
    [TRAINER_PIC_COOL_COUPLE]           = sAnims_CoolCouple,
    [TRAINER_PIC_YOUNG_COUPLE]          = sAnims_YoungCouple,
    [TRAINER_PIC_CRUSH_KIN]             = sAnims_CrushKin,
    [TRAINER_PIC_SIS_AND_BRO]           = sAnims_SisAndBro,
    [TRAINER_PIC_PROFESSOR_OAK]         = sAnims_ProfessorOak,
    [TRAINER_PIC_RS_BRENDAN_2]          = sAnims_RSBrendan2,
    [TRAINER_PIC_RS_MAY_2]              = sAnims_RSMay2,
    [TRAINER_PIC_RED]                   = sAnims_Red,
    [TRAINER_PIC_LEAF]                  = sAnims_Leaf,
    [TRAINER_PIC_ROCKET_GRUNT_F]        = sAnims_RocketGruntF,
    [TRAINER_PIC_PSYCHIC_F]             = sAnims_PsychicF,
    [TRAINER_PIC_CRUSH_GIRL]            = sAnims_CrushGirl,
    [TRAINER_PIC_TUBER_F]               = sAnims_TuberF,
    [TRAINER_PIC_POKEMON_BREEDER]       = sAnims_PokemonBreeder,
    [TRAINER_PIC_POKEMON_RANGER_M]      = sAnims_PokemonRangerM,
    [TRAINER_PIC_POKEMON_RANGER_F]      = sAnims_PokemonRangerF,
    [TRAINER_PIC_AROMA_LADY]            = sAnims_AromaLady,
    [TRAINER_PIC_RUIN_MANIAC]           = sAnims_RuinManiac,
    [TRAINER_PIC_LADY]                  = sAnims_Lady,
    [TRAINER_PIC_PAINTER]               = sAnims_Painter,
};
// ===== END src/data/trainer_graphics/front_pic_anims.h =====
// ===== BEGIN src/data/trainer_graphics/front_pic_tables.h =====
const struct MonCoords gTrainerFrontPicCoords[] =
{
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 2},
    {.size = 8, .y_offset = 2},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 2},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 2},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
    {.size = 8, .y_offset = 1},
};

const struct CompressedSpriteSheet gTrainerFrontPicTable[] =
{
    TRAINER_SPRITE(AQUA_LEADER_ARCHIE, gTrainerFrontPic_AquaLeaderArchie, 0x800),
    TRAINER_SPRITE(AQUA_GRUNT_M, gTrainerFrontPic_AquaGruntM, 0x800),
    TRAINER_SPRITE(AQUA_GRUNT_F, gTrainerFrontPic_AquaGruntF, 0x800),
    TRAINER_SPRITE(RS_AROMA_LADY, gTrainerFrontPic_RSAromaLady, 0x800),
    TRAINER_SPRITE(RS_RUIN_MANIAC, gTrainerFrontPic_RSRuinManiac, 0x800),
    TRAINER_SPRITE(INTERVIEWER, gTrainerFrontPic_Interviewer, 0x800),
    TRAINER_SPRITE(RS_TUBER_F, gTrainerFrontPic_RSTuberF, 0x800),
    TRAINER_SPRITE(RS_TUBER_M, gTrainerFrontPic_TuberM, 0x800),
    TRAINER_SPRITE(RS_COOLTRAINER_M, gTrainerFrontPic_RSCooltrainerM, 0x800),
    TRAINER_SPRITE(RS_COOLTRAINER_F, gTrainerFrontPic_RSCooltrainerF, 0x800),
    TRAINER_SPRITE(HEX_MANIAC, gTrainerFrontPic_HexManiac, 0x800),
    TRAINER_SPRITE(RS_LADY, gTrainerFrontPic_RSLady, 0x800),
    TRAINER_SPRITE(RS_BEAUTY, gTrainerFrontPic_RSBeauty, 0x800),
    TRAINER_SPRITE(RICH_BOY, gTrainerFrontPic_RichBoy, 0x800),
    TRAINER_SPRITE(RS_POKEMANIAC, gTrainerFrontPic_RSPokeManiac, 0x800),
    TRAINER_SPRITE(RS_SWIMMER_M, gTrainerFrontPic_RSSwimmerM, 0x800),
    TRAINER_SPRITE(RS_BLACK_BELT, gTrainerFrontPic_RSBlackBelt, 0x800),
    TRAINER_SPRITE(GUITARIST, gTrainerFrontPic_Guitarist, 0x800),
    TRAINER_SPRITE(KINDLER, gTrainerFrontPic_Kindler, 0x800),
    TRAINER_SPRITE(RS_CAMPER, gTrainerFrontPic_RSCamper, 0x800),
    TRAINER_SPRITE(BUG_MANIAC, gTrainerFrontPic_BugManiac, 0x800),
    TRAINER_SPRITE(RS_PSYCHIC_M, gTrainerFrontPic_RSPsychicM, 0x800),
    TRAINER_SPRITE(RS_PSYCHIC_F, gTrainerFrontPic_RSPsychicF, 0x800),
    TRAINER_SPRITE(RS_GENTLEMAN, gTrainerFrontPic_RSGentleman, 0x800),
    TRAINER_SPRITE(ELITE_FOUR_SIDNEY, gTrainerFrontPic_EliteFourSidney, 0x800),
    TRAINER_SPRITE(ELITE_FOUR_PHOEBE, gTrainerFrontPic_EliteFourPhoebe, 0x800),
    TRAINER_SPRITE(LEADER_ROXANNE, gTrainerFrontPic_LeaderRoxanne, 0x800),
    TRAINER_SPRITE(LEADER_BRAWLY, gTrainerFrontPic_LeaderBrawly, 0x800),
    TRAINER_SPRITE(LEADER_TATE_AND_LIZA, gTrainerFrontPic_LeaderTateAndLiza, 0x800),
    TRAINER_SPRITE(SCHOOL_KID_M, gTrainerFrontPic_SchoolKidM, 0x800),
    TRAINER_SPRITE(SCHOOL_KID_F, gTrainerFrontPic_SchoolKidF, 0x800),
    TRAINER_SPRITE(SR_AND_JR, gTrainerFrontPic_SrAndJr, 0x1000),
    TRAINER_SPRITE(POKEFAN_M, gTrainerFrontPic_PokefanM, 0x1000),
    TRAINER_SPRITE(POKEFAN_F, gTrainerFrontPic_PokefanF, 0x800),
    TRAINER_SPRITE(EXPERT_M, gTrainerFrontPic_ExpertM, 0x800),
    TRAINER_SPRITE(EXPERT_F, gTrainerFrontPic_ExpertF, 0x800),
    TRAINER_SPRITE(RS_YOUNGSTER, gTrainerFrontPic_RSYoungster, 0x800),
    TRAINER_SPRITE(CHAMPION_STEVEN, gTrainerFrontPic_ChampionSteven, 0x800),
    TRAINER_SPRITE(RS_FISHERMAN, gTrainerFrontPic_RSFisherman, 0x800),
    TRAINER_SPRITE(CYCLING_TRIATHLETE_M, gTrainerFrontPic_CyclingTriathleteM, 0x1000),
    TRAINER_SPRITE(CYCLING_TRIATHLETE_F, gTrainerFrontPic_CyclingTriathleteF, 0x800),
    TRAINER_SPRITE(RUNNING_TRIATHLETE_M, gTrainerFrontPic_RunningTriathleteM, 0x800),
    TRAINER_SPRITE(RUNNING_TRIATHLETE_F, gTrainerFrontPic_RunningTriathleteF, 0x800),
    TRAINER_SPRITE(SWIMMING_TRIATHLETE_M, gTrainerFrontPic_SwimmingTriathleteM, 0x800),
    TRAINER_SPRITE(SWIMMING_TRIATHLETE_F, gTrainerFrontPic_SwimmingTriathleteF, 0x800),
    TRAINER_SPRITE(DRAGON_TAMER, gTrainerFrontPic_DragonTamer, 0x800),
    TRAINER_SPRITE(RS_BIRD_KEEPER, gTrainerFrontPic_RSBirdKeeper, 0x800),
    TRAINER_SPRITE(NINJA_BOY, gTrainerFrontPic_NinjaBoy, 0x800),
    TRAINER_SPRITE(BATTLE_GIRL, gTrainerFrontPic_BattleGirl, 0x1000),
    TRAINER_SPRITE(PARASOL_LADY, gTrainerFrontPic_ParasolLady, 0x800),
    TRAINER_SPRITE(RS_SWIMMER_F, gTrainerFrontPic_RSSwimmerF, 0x800),
    TRAINER_SPRITE(RS_PICNICKER, gTrainerFrontPic_RSPicnicker, 0x800),
    TRAINER_SPRITE(RS_TWINS, gTrainerFrontPic_RSTwins, 0x800),
    TRAINER_SPRITE(RS_SAILOR, gTrainerFrontPic_RSSailor, 0x800),
    TRAINER_SPRITE(COLLECTOR, gTrainerFrontPic_Collector, 0x800),
    TRAINER_SPRITE(WALLY, gTrainerFrontPic_Wally, 0x800),
    TRAINER_SPRITE(RS_BRENDAN_1, gTrainerFrontPic_RSBrendan1, 0x800),
    TRAINER_SPRITE(RS_MAY_1, gTrainerFrontPic_RSMay1, 0x800),
    TRAINER_SPRITE(RS_POKEMON_BREEDER_M, gTrainerFrontPic_RSPokemonBreederM, 0x800),
    TRAINER_SPRITE(RS_POKEMON_BREEDER_F, gTrainerFrontPic_RSPokemonBreederF, 0x800),
    TRAINER_SPRITE(RS_POKEMON_RANGER_M, gTrainerFrontPic_RSPokemonRangerM, 0x800),
    TRAINER_SPRITE(RS_POKEMON_RANGER_F, gTrainerFrontPic_RSPokemonRangerF, 0x800),
    TRAINER_SPRITE(MAGMA_LEADER_MAXIE, gTrainerFrontPic_MagmaLeaderMaxie, 0x800),
    TRAINER_SPRITE(MAGMA_GRUNT_M, gTrainerFrontPic_MagmaGruntM, 0x800),
    TRAINER_SPRITE(MAGMA_GRUNT_F, gTrainerFrontPic_MagmaGruntF, 0x800),
    TRAINER_SPRITE(RS_LASS, gTrainerFrontPic_RSLass, 0x800),
    TRAINER_SPRITE(RS_BUG_CATCHER, gTrainerFrontPic_RSBugCatcher, 0x800),
    TRAINER_SPRITE(RS_HIKER, gTrainerFrontPic_RSHiker, 0x800),
    TRAINER_SPRITE(RS_YOUNG_COUPLE, gTrainerFrontPic_RSYoungCouple, 0x800),
    TRAINER_SPRITE(OLD_COUPLE, gTrainerFrontPic_OldCouple, 0x800),
    TRAINER_SPRITE(RS_SIS_AND_BRO, gTrainerFrontPic_RSSisAndBro, 0x800),
    TRAINER_SPRITE(AQUA_ADMIN_M, gTrainerFrontPic_AquaAdminM, 0x800),
    TRAINER_SPRITE(AQUA_ADMIN_F, gTrainerFrontPic_AquaAdminF, 0x800),
    TRAINER_SPRITE(MAGMA_ADMIN_M, gTrainerFrontPic_MagmaAdminM, 0x800),
    TRAINER_SPRITE(MAGMA_ADMIN_F, gTrainerFrontPic_MagmaAdminF, 0x800),
    TRAINER_SPRITE(LEADER_WATTSON, gTrainerFrontPic_LeaderWattson, 0x800),
    TRAINER_SPRITE(LEADER_FLANNERY, gTrainerFrontPic_LeaderFlannery, 0x800),
    TRAINER_SPRITE(LEADER_NORMAN, gTrainerFrontPic_LeaderNorman, 0x800),
    TRAINER_SPRITE(LEADER_WINONA, gTrainerFrontPic_LeaderWinona, 0x800),
    TRAINER_SPRITE(LEADER_WALLACE, gTrainerFrontPic_LeaderWallace, 0x800),
    TRAINER_SPRITE(ELITE_FOUR_GLACIA, gTrainerFrontPic_EliteFourGlacia, 0x800),
    TRAINER_SPRITE(ELITE_FOUR_DRAKE, gTrainerFrontPic_EliteFourDrake, 0x800),
    TRAINER_SPRITE(YOUNGSTER, gTrainerFrontPic_Youngster, 0x800),
    TRAINER_SPRITE(BUG_CATCHER, gTrainerFrontPic_BugCatcher, 0x800),
    TRAINER_SPRITE(LASS, gTrainerFrontPic_Lass, 0x800),
    TRAINER_SPRITE(SAILOR, gTrainerFrontPic_Sailor, 0x800),
    TRAINER_SPRITE(CAMPER, gTrainerFrontPic_Camper, 0x800),
    TRAINER_SPRITE(PICNICKER, gTrainerFrontPic_Picnicker, 0x800),
    TRAINER_SPRITE(POKEMANIAC, gTrainerFrontPic_PokeManiac, 0x800),
    TRAINER_SPRITE(SUPER_NERD, gTrainerFrontPic_SuperNerd, 0x800),
    TRAINER_SPRITE(HIKER, gTrainerFrontPic_Hiker, 0x800),
    TRAINER_SPRITE(BIKER, gTrainerFrontPic_Biker, 0x800),
    TRAINER_SPRITE(BURGLAR, gTrainerFrontPic_Burglar, 0x800),
    TRAINER_SPRITE(ENGINEER, gTrainerFrontPic_Engineer, 0x800),
    TRAINER_SPRITE(FISHERMAN, gTrainerFrontPic_Fisherman, 0x800),
    TRAINER_SPRITE(SWIMMER_M, gTrainerFrontPic_SwimmerM, 0x800),
    TRAINER_SPRITE(CUE_BALL, gTrainerFrontPic_CueBall, 0x800),
    TRAINER_SPRITE(GAMER, gTrainerFrontPic_Gamer, 0x800),
    TRAINER_SPRITE(BEAUTY, gTrainerFrontPic_Beauty, 0x800),
    TRAINER_SPRITE(SWIMMER_F, gTrainerFrontPic_SwimmerF, 0x800),
    TRAINER_SPRITE(PSYCHIC_M, gTrainerFrontPic_PsychicM, 0x800),
    TRAINER_SPRITE(ROCKER, gTrainerFrontPic_Rocker, 0x800),
    TRAINER_SPRITE(JUGGLER, gTrainerFrontPic_Juggler, 0x800),
    TRAINER_SPRITE(TAMER, gTrainerFrontPic_Tamer, 0x800),
    TRAINER_SPRITE(BIRD_KEEPER, gTrainerFrontPic_BirdKeeper, 0x800),
    TRAINER_SPRITE(BLACK_BELT, gTrainerFrontPic_BlackBelt, 0x800),
    TRAINER_SPRITE(RIVAL_EARLY, gTrainerFrontPic_RivalEarly, 0x800),
    TRAINER_SPRITE(SCIENTIST, gTrainerFrontPic_Scientist, 0x800),
    TRAINER_SPRITE(LEADER_GIOVANNI, gTrainerFrontPic_LeaderGiovanni, 0x800),
    TRAINER_SPRITE(ROCKET_GRUNT_M, gTrainerFrontPic_RocketGruntM, 0x800),
    TRAINER_SPRITE(COOLTRAINER_M, gTrainerFrontPic_CooltrainerM, 0x800),
    TRAINER_SPRITE(COOLTRAINER_F, gTrainerFrontPic_CooltrainerF, 0x800),
    TRAINER_SPRITE(ELITE_FOUR_LORELEI, gTrainerFrontPic_EliteFourLorelei, 0x800),
    TRAINER_SPRITE(ELITE_FOUR_BRUNO, gTrainerFrontPic_EliteFourBruno, 0x800),
    TRAINER_SPRITE(ELITE_FOUR_AGATHA, gTrainerFrontPic_EliteFourAgatha, 0x800),
    TRAINER_SPRITE(ELITE_FOUR_LANCE, gTrainerFrontPic_EliteFourLance, 0x800),
    TRAINER_SPRITE(LEADER_BROCK, gTrainerFrontPic_LeaderBrock, 0x800),
    TRAINER_SPRITE(LEADER_MISTY, gTrainerFrontPic_LeaderMisty, 0x800),
    TRAINER_SPRITE(LEADER_LT_SURGE, gTrainerFrontPic_LeaderLtSurge, 0x800),
    TRAINER_SPRITE(LEADER_ERIKA, gTrainerFrontPic_LeaderErika, 0x800),
    TRAINER_SPRITE(LEADER_KOGA, gTrainerFrontPic_LeaderKoga, 0x800),
    TRAINER_SPRITE(LEADER_BLAINE, gTrainerFrontPic_LeaderBlaine, 0x800),
    TRAINER_SPRITE(LEADER_SABRINA, gTrainerFrontPic_LeaderSabrina, 0x800),
    TRAINER_SPRITE(GENTLEMAN, gTrainerFrontPic_Gentleman, 0x800),
    TRAINER_SPRITE(RIVAL_LATE, gTrainerFrontPic_RivalLate, 0x800),
    TRAINER_SPRITE(CHAMPION_RIVAL, gTrainerFrontPic_ChampionRival, 0x800),
    TRAINER_SPRITE(CHANNELER, gTrainerFrontPic_Channeler, 0x800),
    TRAINER_SPRITE(TWINS, gTrainerFrontPic_Twins, 0x800),
    TRAINER_SPRITE(COOL_COUPLE, gTrainerFrontPic_CoolCouple, 0x800),
    TRAINER_SPRITE(YOUNG_COUPLE, gTrainerFrontPic_YoungCouple, 0x800),
    TRAINER_SPRITE(CRUSH_KIN, gTrainerFrontPic_CrushKin, 0x800),
    TRAINER_SPRITE(SIS_AND_BRO, gTrainerFrontPic_SisAndBro, 0x800),
    TRAINER_SPRITE(PROFESSOR_OAK, gTrainerFrontPic_ProfessorOak, 0x800),
    TRAINER_SPRITE(RS_BRENDAN_2, gTrainerFrontPic_RSBrendan2, 0x800),
    TRAINER_SPRITE(RS_MAY_2, gTrainerFrontPic_RSMay2, 0x800),
    TRAINER_SPRITE(RED, gTrainerFrontPic_Red, 0x800),
    TRAINER_SPRITE(LEAF, gTrainerFrontPic_Leaf, 0x800),
    TRAINER_SPRITE(ROCKET_GRUNT_F, gTrainerFrontPic_RocketGruntF, 0x800),
    TRAINER_SPRITE(PSYCHIC_F, gTrainerFrontPic_PsychicF, 0x800),
    TRAINER_SPRITE(CRUSH_GIRL, gTrainerFrontPic_CrushGirl, 0x800),
    TRAINER_SPRITE(TUBER_F, gTrainerFrontPic_TuberF, 0x800),
    TRAINER_SPRITE(POKEMON_BREEDER, gTrainerFrontPic_PokemonBreeder, 0x800),
    TRAINER_SPRITE(POKEMON_RANGER_M, gTrainerFrontPic_PokemonRangerM, 0x800),
    TRAINER_SPRITE(POKEMON_RANGER_F, gTrainerFrontPic_PokemonRangerF, 0x800),
    TRAINER_SPRITE(AROMA_LADY, gTrainerFrontPic_AromaLady, 0x800),
    TRAINER_SPRITE(RUIN_MANIAC, gTrainerFrontPic_RuinManiac, 0x800),
    TRAINER_SPRITE(LADY, gTrainerFrontPic_Lady, 0x800),
    TRAINER_SPRITE(PAINTER, gTrainerFrontPic_Painter, 0x800),
};

const struct CompressedSpritePalette gTrainerFrontPicPaletteTable[] =
{
    TRAINER_PAL(AQUA_LEADER_ARCHIE, gTrainerPalette_AquaLeaderArchie),
    TRAINER_PAL(AQUA_GRUNT_M, gTrainerPalette_AquaGruntM),
    TRAINER_PAL(AQUA_GRUNT_F, gTrainerPalette_AquaGruntF),
    TRAINER_PAL(RS_AROMA_LADY, gTrainerPalette_RSAromaLady),
    TRAINER_PAL(RS_RUIN_MANIAC, gTrainerPalette_RSRuinManiac),
    TRAINER_PAL(INTERVIEWER, gTrainerPalette_Interviewer),
    TRAINER_PAL(RS_TUBER_F, gTrainerPalette_RSTuberF),
    TRAINER_PAL(RS_TUBER_M, gTrainerPalette_TuberM),
    TRAINER_PAL(RS_COOLTRAINER_M, gTrainerPalette_RSCooltrainerM),
    TRAINER_PAL(RS_COOLTRAINER_F, gTrainerPalette_RSCooltrainerF),
    TRAINER_PAL(HEX_MANIAC, gTrainerPalette_HexManiac),
    TRAINER_PAL(RS_LADY, gTrainerPalette_RSLady),
    TRAINER_PAL(RS_BEAUTY, gTrainerPalette_RSBeauty),
    TRAINER_PAL(RICH_BOY, gTrainerPalette_RichBoy),
    TRAINER_PAL(RS_POKEMANIAC, gTrainerPalette_RSPokeManiac),
    TRAINER_PAL(RS_SWIMMER_M, gTrainerPalette_RSSwimmerM),
    TRAINER_PAL(RS_BLACK_BELT, gTrainerPalette_RSBlackBelt),
    TRAINER_PAL(GUITARIST, gTrainerPalette_Guitarist),
    TRAINER_PAL(KINDLER, gTrainerPalette_Kindler),
    TRAINER_PAL(RS_CAMPER, gTrainerPalette_RSCamper),
    TRAINER_PAL(BUG_MANIAC, gTrainerPalette_BugManiac),
    TRAINER_PAL(RS_PSYCHIC_M, gTrainerPalette_RSPsychicM),
    TRAINER_PAL(RS_PSYCHIC_F, gTrainerPalette_RSPsychicF),
    TRAINER_PAL(RS_GENTLEMAN, gTrainerPalette_RSGentleman),
    TRAINER_PAL(ELITE_FOUR_SIDNEY, gTrainerPalette_EliteFourSidney),
    TRAINER_PAL(ELITE_FOUR_PHOEBE, gTrainerPalette_EliteFourPhoebe),
    TRAINER_PAL(LEADER_ROXANNE, gTrainerPalette_LeaderRoxanne),
    TRAINER_PAL(LEADER_BRAWLY, gTrainerPalette_LeaderBrawly),
    TRAINER_PAL(LEADER_TATE_AND_LIZA, gTrainerPalette_LeaderTateAndLiza),
    TRAINER_PAL(SCHOOL_KID_M, gTrainerPalette_SchoolKidM),
    TRAINER_PAL(SCHOOL_KID_F, gTrainerPalette_SchoolKidF),
    TRAINER_PAL(SR_AND_JR, gTrainerPalette_SrAndJr),
    TRAINER_PAL(POKEFAN_M, gTrainerPalette_PokefanM),
    TRAINER_PAL(POKEFAN_F, gTrainerPalette_PokefanF),
    TRAINER_PAL(EXPERT_M, gTrainerPalette_ExpertM),
    TRAINER_PAL(EXPERT_F, gTrainerPalette_ExpertF),
    TRAINER_PAL(RS_YOUNGSTER, gTrainerPalette_RSYoungster),
    TRAINER_PAL(CHAMPION_STEVEN, gTrainerPalette_ChampionSteven),
    TRAINER_PAL(RS_FISHERMAN, gTrainerPalette_RSFisherman),
    TRAINER_PAL(CYCLING_TRIATHLETE_M, gTrainerPalette_CyclingTriathleteM),
    TRAINER_PAL(CYCLING_TRIATHLETE_F, gTrainerPalette_CyclingTriathleteF),
    TRAINER_PAL(RUNNING_TRIATHLETE_M, gTrainerPalette_RunningTriathleteM),
    TRAINER_PAL(RUNNING_TRIATHLETE_F, gTrainerPalette_RunningTriathleteF),
    TRAINER_PAL(SWIMMING_TRIATHLETE_M, gTrainerPalette_SwimmingTriathleteM),
    TRAINER_PAL(SWIMMING_TRIATHLETE_F, gTrainerPalette_SwimmingTriathleteF),
    TRAINER_PAL(DRAGON_TAMER, gTrainerPalette_DragonTamer),
    TRAINER_PAL(RS_BIRD_KEEPER, gTrainerPalette_RSBirdKeeper),
    TRAINER_PAL(NINJA_BOY, gTrainerPalette_NinjaBoy),
    TRAINER_PAL(BATTLE_GIRL, gTrainerPalette_BattleGirl),
    TRAINER_PAL(PARASOL_LADY, gTrainerPalette_ParasolLady),
    TRAINER_PAL(RS_SWIMMER_F, gTrainerPalette_RSSwimmerF),
    TRAINER_PAL(RS_PICNICKER, gTrainerPalette_RSPicnicker),
    TRAINER_PAL(RS_TWINS, gTrainerPalette_RSTwins),
    TRAINER_PAL(RS_SAILOR, gTrainerPalette_RSSailor),
    TRAINER_PAL(COLLECTOR, gTrainerPalette_Collector),
    TRAINER_PAL(WALLY, gTrainerPalette_Wally),
    TRAINER_PAL(RS_BRENDAN_1, gTrainerPalette_RSBrendan1),
    TRAINER_PAL(RS_MAY_1, gTrainerPalette_RSMay1),
    TRAINER_PAL(RS_POKEMON_BREEDER_M, gTrainerPalette_RSPokemonBreederM),
    TRAINER_PAL(RS_POKEMON_BREEDER_F, gTrainerPalette_RSPokemonBreederF),
    TRAINER_PAL(RS_POKEMON_RANGER_M, gTrainerPalette_RSPokemonRangerM),
    TRAINER_PAL(RS_POKEMON_RANGER_F, gTrainerPalette_RSPokemonRangerF),
    TRAINER_PAL(MAGMA_LEADER_MAXIE, gTrainerPalette_MagmaLeaderMaxie),
    TRAINER_PAL(MAGMA_GRUNT_M, gTrainerPalette_MagmaGruntM),
    TRAINER_PAL(MAGMA_GRUNT_F, gTrainerPalette_MagmaGruntF),
    TRAINER_PAL(RS_LASS, gTrainerPalette_RSLass),
    TRAINER_PAL(RS_BUG_CATCHER, gTrainerPalette_RSBugCatcher),
    TRAINER_PAL(RS_HIKER, gTrainerPalette_RSHiker),
    TRAINER_PAL(RS_YOUNG_COUPLE, gTrainerPalette_RSYoungCouple),
    TRAINER_PAL(OLD_COUPLE, gTrainerPalette_OldCouple),
    TRAINER_PAL(RS_SIS_AND_BRO, gTrainerPalette_RSSisAndBro),
    TRAINER_PAL(AQUA_ADMIN_M, gTrainerPalette_AquaAdminM),
    TRAINER_PAL(AQUA_ADMIN_F, gTrainerPalette_AquaAdminF),
    TRAINER_PAL(MAGMA_ADMIN_M, gTrainerPalette_MagmaAdminM),
    TRAINER_PAL(MAGMA_ADMIN_F, gTrainerPalette_MagmaAdminF),
    TRAINER_PAL(LEADER_WATTSON, gTrainerPalette_LeaderWattson),
    TRAINER_PAL(LEADER_FLANNERY, gTrainerPalette_LeaderFlannery),
    TRAINER_PAL(LEADER_NORMAN, gTrainerPalette_LeaderNorman),
    TRAINER_PAL(LEADER_WINONA, gTrainerPalette_LeaderWinona),
    TRAINER_PAL(LEADER_WALLACE, gTrainerPalette_LeaderWallace),
    TRAINER_PAL(ELITE_FOUR_GLACIA, gTrainerPalette_EliteFourGlacia),
    TRAINER_PAL(ELITE_FOUR_DRAKE, gTrainerPalette_EliteFourDrake),
    TRAINER_PAL(YOUNGSTER, gTrainerPalette_Youngster),
    TRAINER_PAL(BUG_CATCHER, gTrainerPalette_BugCatcher),
    TRAINER_PAL(LASS, gTrainerPalette_Lass),
    TRAINER_PAL(SAILOR, gTrainerPalette_Sailor),
    TRAINER_PAL(CAMPER, gTrainerPalette_Camper),
    TRAINER_PAL(PICNICKER, gTrainerPalette_Picnicker),
    TRAINER_PAL(POKEMANIAC, gTrainerPalette_PokeManiac),
    TRAINER_PAL(SUPER_NERD, gTrainerPalette_SuperNerd),
    TRAINER_PAL(HIKER, gTrainerPalette_Hiker),
    TRAINER_PAL(BIKER, gTrainerPalette_Biker),
    TRAINER_PAL(BURGLAR, gTrainerPalette_Burglar),
    TRAINER_PAL(ENGINEER, gTrainerPalette_Engineer),
    TRAINER_PAL(FISHERMAN, gTrainerPalette_Fisherman),
    TRAINER_PAL(SWIMMER_M, gTrainerPalette_SwimmerM),
    TRAINER_PAL(CUE_BALL, gTrainerPalette_CueBall),
    TRAINER_PAL(GAMER, gTrainerPalette_Gamer),
    TRAINER_PAL(BEAUTY, gTrainerPalette_Beauty),
    TRAINER_PAL(SWIMMER_F, gTrainerPalette_SwimmerF),
    TRAINER_PAL(PSYCHIC_M, gTrainerPalette_PsychicM),
    TRAINER_PAL(ROCKER, gTrainerPalette_Rocker),
    TRAINER_PAL(JUGGLER, gTrainerPalette_Juggler),
    TRAINER_PAL(TAMER, gTrainerPalette_Tamer),
    TRAINER_PAL(BIRD_KEEPER, gTrainerPalette_BirdKeeper),
    TRAINER_PAL(BLACK_BELT, gTrainerPalette_BlackBelt),
    TRAINER_PAL(RIVAL_EARLY, gTrainerPalette_RivalEarly),
    TRAINER_PAL(SCIENTIST, gTrainerPalette_Scientist),
    TRAINER_PAL(LEADER_GIOVANNI, gTrainerPalette_LeaderGiovanni),
    TRAINER_PAL(ROCKET_GRUNT_M, gTrainerPalette_RocketGruntM),
    TRAINER_PAL(COOLTRAINER_M, gTrainerPalette_CooltrainerM),
    TRAINER_PAL(COOLTRAINER_F, gTrainerPalette_CooltrainerF),
    TRAINER_PAL(ELITE_FOUR_LORELEI, gTrainerPalette_EliteFourLorelei),
    TRAINER_PAL(ELITE_FOUR_BRUNO, gTrainerPalette_EliteFourBruno),
    TRAINER_PAL(ELITE_FOUR_AGATHA, gTrainerPalette_EliteFourAgatha),
    TRAINER_PAL(ELITE_FOUR_LANCE, gTrainerPalette_EliteFourLance),
    TRAINER_PAL(LEADER_BROCK, gTrainerPalette_LeaderBrock),
    TRAINER_PAL(LEADER_MISTY, gTrainerPalette_LeaderMisty),
    TRAINER_PAL(LEADER_LT_SURGE, gTrainerPalette_LeaderLtSurge),
    TRAINER_PAL(LEADER_ERIKA, gTrainerPalette_LeaderErika),
    TRAINER_PAL(LEADER_KOGA, gTrainerPalette_LeaderKoga),
    TRAINER_PAL(LEADER_BLAINE, gTrainerPalette_LeaderBlaine),
    TRAINER_PAL(LEADER_SABRINA, gTrainerPalette_LeaderSabrina),
    TRAINER_PAL(GENTLEMAN, gTrainerPalette_Gentleman),
    TRAINER_PAL(RIVAL_LATE, gTrainerPalette_RivalLate),
    TRAINER_PAL(CHAMPION_RIVAL, gTrainerPalette_ChampionRival),
    TRAINER_PAL(CHANNELER, gTrainerPalette_Channeler),
    TRAINER_PAL(TWINS, gTrainerPalette_Twins),
    TRAINER_PAL(COOL_COUPLE, gTrainerPalette_CoolCouple),
    TRAINER_PAL(YOUNG_COUPLE, gTrainerPalette_YoungCouple),
    TRAINER_PAL(CRUSH_KIN, gTrainerPalette_CrushKin),
    TRAINER_PAL(SIS_AND_BRO, gTrainerPalette_SisAndBro),
    TRAINER_PAL(PROFESSOR_OAK, gTrainerPalette_ProfessorOak),
    TRAINER_PAL(RS_BRENDAN_2, gTrainerPalette_RSBrendan2),
    TRAINER_PAL(RS_MAY_2, gTrainerPalette_RSMay2),
    TRAINER_PAL(RED, gTrainerPalette_Red),
    TRAINER_PAL(LEAF, gTrainerPalette_Leaf),
    TRAINER_PAL(ROCKET_GRUNT_F, gTrainerPalette_RocketGruntF),
    TRAINER_PAL(PSYCHIC_F, gTrainerPalette_PsychicF),
    TRAINER_PAL(CRUSH_GIRL, gTrainerPalette_CrushGirl),
    TRAINER_PAL(TUBER_F, gTrainerPalette_TuberF),
    TRAINER_PAL(POKEMON_BREEDER, gTrainerPalette_PokemonBreeder),
    TRAINER_PAL(POKEMON_RANGER_M, gTrainerPalette_PokemonRangerM),
    TRAINER_PAL(POKEMON_RANGER_F, gTrainerPalette_PokemonRangerF),
    TRAINER_PAL(AROMA_LADY, gTrainerPalette_AromaLady),
    TRAINER_PAL(RUIN_MANIAC, gTrainerPalette_RuinManiac),
    TRAINER_PAL(LADY, gTrainerPalette_Lady),
    TRAINER_PAL(PAINTER, gTrainerPalette_Painter),
};
// ===== END src/data/trainer_graphics/front_pic_tables.h =====
// ===== BEGIN src/data/trainer_graphics/back_pic_anims.h =====
static const union AnimCmd sAnimCmd_Red_1[] = {
    ANIMCMD_FRAME(1, 20),
    ANIMCMD_FRAME(2, 6),
    ANIMCMD_FRAME(3, 6),
    ANIMCMD_FRAME(4, 24),
    ANIMCMD_FRAME(0, 1),
    ANIMCMD_END
};

static const union AnimCmd sAnimCmd_Leaf_1[] = {
    ANIMCMD_FRAME(1, 20),
    ANIMCMD_FRAME(2, 6),
    ANIMCMD_FRAME(3, 6),
    ANIMCMD_FRAME(4, 24),
    ANIMCMD_FRAME(0, 1),
    ANIMCMD_END
};

static const union AnimCmd sAnimCmd_Pokedude_1[] = {
    ANIMCMD_FRAME(1, 24),
    ANIMCMD_FRAME(2, 9),
    ANIMCMD_FRAME(3, 24),
    ANIMCMD_FRAME(0, 9),
    ANIMCMD_END
};

static const union AnimCmd sAnimCmd_OldMan_1[] = {
    ANIMCMD_FRAME(1, 24),
    ANIMCMD_FRAME(2, 9),
    ANIMCMD_FRAME(3, 24),
    ANIMCMD_FRAME(0, 9),
    ANIMCMD_END
};

static const union AnimCmd sAnimCmd_RSBrendan_1[] = {
    ANIMCMD_FRAME(0, 24),
    ANIMCMD_FRAME(1, 9),
    ANIMCMD_FRAME(2, 24),
    ANIMCMD_FRAME(0, 9),
    ANIMCMD_FRAME(3, 50),
    ANIMCMD_END
};

static const union AnimCmd sAnimCmd_RSMay_1[] = {
    ANIMCMD_FRAME(0, 24),
    ANIMCMD_FRAME(1, 9),
    ANIMCMD_FRAME(2, 24),
    ANIMCMD_FRAME(0, 9),
    ANIMCMD_FRAME(3, 50),
    ANIMCMD_END
};

const union AnimCmd *const sBackAnims_Red[] = {
    sAnim_GeneralFrame0,
    sAnimCmd_Red_1
};

const union AnimCmd *const sBackAnims_Leaf[] = {
    sAnim_GeneralFrame0,
    sAnimCmd_Leaf_1
};

const union AnimCmd *const sBackAnims_Pokedude[] = {
    sAnim_GeneralFrame0,
    sAnimCmd_Pokedude_1
};

const union AnimCmd *const sBackAnims_OldMan[] = {
    sAnim_GeneralFrame0,
    sAnimCmd_OldMan_1
};

const union AnimCmd *const sBackAnims_RSBrendan[] = {
    sAnim_GeneralFrame3,
    sAnimCmd_RSBrendan_1
};

const union AnimCmd *const sBackAnims_RSMay[] = {
    sAnim_GeneralFrame3,
    sAnimCmd_RSMay_1
};

const union AnimCmd *const *const gTrainerBackAnimsPtrTable[] = {
    sBackAnims_Red,
    sBackAnims_Leaf,
    sBackAnims_RSBrendan,
    sBackAnims_RSMay,
    sBackAnims_Pokedude,
    sBackAnims_OldMan
};
// ===== END src/data/trainer_graphics/back_pic_anims.h =====
// ===== BEGIN src/data/trainer_graphics/back_pic_tables.h =====
const struct MonCoords gTrainerBackPicCoords[] = {
    [TRAINER_BACK_PIC_RED] = {.size = 8, .y_offset = 5},
    [TRAINER_BACK_PIC_LEAF] = {.size = 8, .y_offset = 5},
    [TRAINER_BACK_PIC_RUBY_SAPPHIRE_BRENDAN] = {.size = 8, .y_offset = 4},
    [TRAINER_BACK_PIC_RUBY_SAPPHIRE_MAY] = {.size = 8, .y_offset = 4},
    [TRAINER_BACK_PIC_POKEDUDE] = {.size = 8, .y_offset = 4},
    [TRAINER_BACK_PIC_OLD_MAN] = {.size = 8, .y_offset = 4}
};

const struct CompressedSpriteSheet gTrainerBackPicTable[] = {
    { (const u32 *)gTrainerBackPic_Red, 0x2800, 0 },
    { (const u32 *)gTrainerBackPic_Leaf, 0x2800, 1 },
    { (const u32 *)gTrainerBackPic_RSBrendan, 0x2000, 2 },
    { (const u32 *)gTrainerBackPic_RSMay, 0x2000, 3 },
    { (const u32 *)gTrainerBackPic_Pokedude, 0x2000, 4 },
    { (const u32 *)gTrainerBackPic_OldMan, 0x2000, 5 }
};

const struct CompressedSpritePalette gTrainerBackPicPaletteTable[] = {
    { gTrainerPalette_RedBackPic, 0 },
    { gTrainerPalette_LeafBackPic, 1 },
    { gTrainerPalette_RSBrendan1, 2 },
    { gTrainerPalette_RSMay1, 3 },
    { gTrainerPalette_PokedudeBackPic, 4 },
    { gTrainerPalette_OldManBackPic, 5 }
};
// ===== END src/data/trainer_graphics/back_pic_tables.h =====

// ===== BEGIN src/data/pokemon_graphics/enemy_mon_elevation.h =====
// This determines how much higher above the usual position the enemy Pokémon
// is during battle. Species that float or fly have nonzero values.
const u8 gEnemyMonElevation[NUM_SPECIES] =
{
    [SPECIES_BUTTERFREE] = 8,
    [SPECIES_BEEDRILL] = 8,
    [SPECIES_PIDGEOT] = 4,
    [SPECIES_FEAROW] = 6,
    [SPECIES_ZUBAT] = 8,
    [SPECIES_GOLBAT] = 8,
    [SPECIES_VENOMOTH] = 8,
    [SPECIES_GEODUDE] = 16,
    [SPECIES_MAGNEMITE] = 16,
    [SPECIES_MAGNETON] = 8,
    [SPECIES_GASTLY] = 4,
    [SPECIES_HAUNTER] = 4,
    [SPECIES_VOLTORB] = 10,
    [SPECIES_ELECTRODE] = 12,
    [SPECIES_KOFFING] = 8,
    [SPECIES_WEEZING] = 6,
    [SPECIES_AERODACTYL] = 7,
    [SPECIES_ARTICUNO] = 6,
    [SPECIES_ZAPDOS] = 8,
    [SPECIES_MOLTRES] = 5,
    [SPECIES_DRAGONITE] = 6,
    [SPECIES_MEW] = 8,
    [SPECIES_LEDIAN] = 8,
    [SPECIES_CROBAT] = 6,
    [SPECIES_HOPPIP] = 11,
    [SPECIES_SKIPLOOM] = 12,
    [SPECIES_JUMPLUFF] = 9,
    [SPECIES_YANMA] = 8,
    [SPECIES_MISDREAVUS] = 8,
    [SPECIES_UNOWN] = 8,
    [SPECIES_GLIGAR] = 6,
    [SPECIES_LUGIA] = 6,
    [SPECIES_HO_OH] = 6,
    [SPECIES_CELEBI] = 15,
    [SPECIES_BEAUTIFLY] = 8,
    [SPECIES_DUSTOX] = 10,
    [SPECIES_NINJASK] = 10,
    [SPECIES_SHEDINJA] = 8,
    [SPECIES_WINGULL] = 16,
    [SPECIES_PELIPPER] = 8,
    [SPECIES_MASQUERAIN] = 10,
    [SPECIES_BALTOY] = 4,
    [SPECIES_CLAYDOL] = 10,
    [SPECIES_FLYGON] = 7,
    [SPECIES_GLALIE] = 12,
    [SPECIES_LUNATONE] = 13,
    [SPECIES_SOLROCK] = 4,
    [SPECIES_SWABLU] = 12,
    [SPECIES_ALTARIA] = 8,
    [SPECIES_DUSKULL] = 9,
    [SPECIES_SHUPPET] = 12,
    [SPECIES_BANETTE] = 8,
    [SPECIES_CASTFORM] = 16,
    [SPECIES_BELDUM] = 8,
    [SPECIES_RAYQUAZA] = 6,
    [SPECIES_LATIAS] = 6,
    [SPECIES_LATIOS] = 6,
    [SPECIES_JIRACHI] = 12,
    [SPECIES_DEOXYS] = 8,
    [SPECIES_CHIMECHO] = 12,
};
// ===== END src/data/pokemon_graphics/enemy_mon_elevation.h =====

// ===== BEGIN src/data/trainer_parties.h =====
// Trainer party data exists for all of the RS trainer classes, but
// are only filled with one of the following placeholder pokemon.
// The actual FRLG trainer party data starts after these.
#define DUMMY_TRAINER_MON           \
    {                               \
        .lvl = 5,                   \
        .species = SPECIES_EKANS,   \
    }

#define DUMMY_TRAINER_MON_IV        \
    {                               \
        .iv = 100,                  \
        .lvl = 5,                   \
        .species = SPECIES_EKANS,   \
    }

// Copy of Swimmer Male Finn's party
#define DUMMY_TRAINER_STARMIE       \
    {                               \
        .lvl = 38,                  \
        .species = SPECIES_STARMIE, \
    }

static const struct TrainerMonNoItemDefaultMoves sParty_AquaLeader[] = {DUMMY_TRAINER_MON};
static const struct TrainerMonNoItemDefaultMoves sParty_AquaGruntM[] = {DUMMY_TRAINER_MON};
static const struct TrainerMonNoItemDefaultMoves sParty_AquaGruntF[] = {DUMMY_TRAINER_MON};
static const struct TrainerMonNoItemDefaultMoves sParty_RSAromaLady[] = {DUMMY_TRAINER_MON};
static const struct TrainerMonNoItemDefaultMoves sParty_RSRuinManiac[] = {DUMMY_TRAINER_MON};
static const struct TrainerMonNoItemDefaultMoves sParty_Interviewer[] = {DUMMY_TRAINER_MON};
static const struct TrainerMonNoItemDefaultMoves sParty_RSTuberF[] = {DUMMY_TRAINER_STARMIE};
static const struct TrainerMonNoItemDefaultMoves sParty_RSTuberM[] = {DUMMY_TRAINER_STARMIE};
static const struct TrainerMonNoItemDefaultMoves sParty_RSCooltrainerM[] = {DUMMY_TRAINER_MON_IV};
static const struct TrainerMonNoItemDefaultMoves sParty_RSCooltrainerF[] = {DUMMY_TRAINER_MON_IV};
static const struct TrainerMonNoItemDefaultMoves sParty_HexManiac[] = {DUMMY_TRAINER_MON};
static const struct TrainerMonNoItemDefaultMoves sParty_RSLady[] = {DUMMY_TRAINER_MON};
static const struct TrainerMonNoItemDefaultMoves sParty_RSBeauty[] = {DUMMY_TRAINER_MON};
static const struct TrainerMonNoItemDefaultMoves sParty_RichBoy[] = {DUMMY_TRAINER_MON};
static const struct TrainerMonNoItemDefaultMoves sParty_RSPokemaniac[] = {DUMMY_TRAINER_MON};
static const struct TrainerMonNoItemDefaultMoves sParty_RSSwimmerM[] = {DUMMY_TRAINER_MON};
static const struct TrainerMonNoItemDefaultMoves sParty_RSBlackBelt[] = {DUMMY_TRAINER_MON_IV};
static const struct TrainerMonNoItemDefaultMoves sParty_Guitarist[] = {DUMMY_TRAINER_MON};
static const struct TrainerMonNoItemDefaultMoves sParty_Kindler[] = {DUMMY_TRAINER_MON};
static const struct TrainerMonNoItemDefaultMoves sParty_RSCamper[] = {DUMMY_TRAINER_MON};
static const struct TrainerMonNoItemDefaultMoves sParty_BugManiac[] = {DUMMY_TRAINER_MON};
static const struct TrainerMonNoItemDefaultMoves sParty_RSPsychicM[] = {DUMMY_TRAINER_MON};
static const struct TrainerMonNoItemDefaultMoves sParty_RSPsychicF[] = {DUMMY_TRAINER_MON};
static const struct TrainerMonNoItemDefaultMoves sParty_RSGentleman[] = {DUMMY_TRAINER_MON};
static const struct TrainerMonNoItemDefaultMoves sParty_EliteFourSidney[] = {DUMMY_TRAINER_MON};
static const struct TrainerMonNoItemDefaultMoves sParty_EliteFourPhoebe[] = {DUMMY_TRAINER_MON};
static const struct TrainerMonNoItemDefaultMoves sParty_LeaderRoxanne[] = {DUMMY_TRAINER_MON};
static const struct TrainerMonNoItemDefaultMoves sParty_LeaderBrawly[] = {DUMMY_TRAINER_MON};
static const struct TrainerMonNoItemDefaultMoves sParty_LeaderTateLiza[] = {DUMMY_TRAINER_MON};
static const struct TrainerMonNoItemDefaultMoves sParty_SchoolKidM[] = {DUMMY_TRAINER_MON};
static const struct TrainerMonNoItemDefaultMoves sParty_SchoolKidF[] = {DUMMY_TRAINER_MON};
static const struct TrainerMonNoItemDefaultMoves sParty_SrAndJr[] = {DUMMY_TRAINER_MON};
static const struct TrainerMonNoItemDefaultMoves sParty_PokefanM[] = {DUMMY_TRAINER_MON};
static const struct TrainerMonNoItemDefaultMoves sParty_PokefanF[] = {DUMMY_TRAINER_MON};
static const struct TrainerMonNoItemDefaultMoves sParty_ExpertM[] = {DUMMY_TRAINER_MON};
static const struct TrainerMonNoItemDefaultMoves sParty_ExpertF[] = {DUMMY_TRAINER_MON};
static const struct TrainerMonNoItemDefaultMoves sParty_RSYoungster[] = {DUMMY_TRAINER_MON};
static const struct TrainerMonNoItemDefaultMoves sParty_RSChampion[] = {DUMMY_TRAINER_MON};
static const struct TrainerMonNoItemDefaultMoves sParty_RSFisherman[] = {DUMMY_TRAINER_MON};
static const struct TrainerMonNoItemDefaultMoves sParty_CyclingTriathleteM[] = {DUMMY_TRAINER_MON};
static const struct TrainerMonNoItemDefaultMoves sParty_CyclingTriathleteF[] = {DUMMY_TRAINER_MON};
static const struct TrainerMonNoItemDefaultMoves sParty_RunningTriathleteM[] = {DUMMY_TRAINER_MON};
static const struct TrainerMonNoItemDefaultMoves sParty_RunningTriathleteF[] = {DUMMY_TRAINER_MON};
static const struct TrainerMonNoItemDefaultMoves sParty_SwimmingTriathleteM[] = {DUMMY_TRAINER_MON};
static const struct TrainerMonNoItemDefaultMoves sParty_SwimmingTriathleteF[] = {DUMMY_TRAINER_MON};
static const struct TrainerMonNoItemDefaultMoves sParty_DragonTamer[] = {DUMMY_TRAINER_MON};
static const struct TrainerMonNoItemDefaultMoves sParty_RSBirdKeeper[] = {DUMMY_TRAINER_MON};
static const struct TrainerMonNoItemDefaultMoves sParty_NinjaBoy[] = {DUMMY_TRAINER_MON};
static const struct TrainerMonNoItemDefaultMoves sParty_BattleGirl[] = {DUMMY_TRAINER_MON};
static const struct TrainerMonNoItemDefaultMoves sParty_ParasolLady[] = {DUMMY_TRAINER_MON};
static const struct TrainerMonNoItemDefaultMoves sParty_RSSwimmerF[] = {DUMMY_TRAINER_MON};
static const struct TrainerMonNoItemDefaultMoves sParty_RSPicnicker[] = {DUMMY_TRAINER_MON};
static const struct TrainerMonNoItemDefaultMoves sParty_RSTwins[] = {DUMMY_TRAINER_MON};
static const struct TrainerMonNoItemDefaultMoves sParty_RSSailor[] = {DUMMY_TRAINER_MON};
static const struct TrainerMonNoItemDefaultMoves sParty_BoarderM[] = {DUMMY_TRAINER_MON};
static const struct TrainerMonNoItemDefaultMoves sParty_BoarderF[] = {DUMMY_TRAINER_MON};
static const struct TrainerMonNoItemDefaultMoves sParty_Collector[] = {DUMMY_TRAINER_MON};
static const struct TrainerMonNoItemDefaultMoves sParty_Wally[] = {DUMMY_TRAINER_MON};
static const struct TrainerMonNoItemDefaultMoves sParty_Brendan[] = {DUMMY_TRAINER_MON};
static const struct TrainerMonNoItemDefaultMoves sParty_Brendan2[] = {DUMMY_TRAINER_MON};
static const struct TrainerMonNoItemDefaultMoves sParty_Brendan3[] = {DUMMY_TRAINER_MON};
static const struct TrainerMonNoItemDefaultMoves sParty_May[] = {DUMMY_TRAINER_MON};
static const struct TrainerMonNoItemDefaultMoves sParty_May2[] = {DUMMY_TRAINER_MON};
static const struct TrainerMonNoItemDefaultMoves sParty_May3[] = {DUMMY_TRAINER_MON};
static const struct TrainerMonNoItemDefaultMoves sParty_RSPkmnBreederM[] = {DUMMY_TRAINER_MON};
static const struct TrainerMonNoItemDefaultMoves sParty_RSPkmnBreederF[] = {DUMMY_TRAINER_MON};
static const struct TrainerMonNoItemDefaultMoves sParty_RSPkmnRangerM[] = {DUMMY_TRAINER_MON_IV};
static const struct TrainerMonNoItemDefaultMoves sParty_RSPkmnRangerF[] = {DUMMY_TRAINER_MON_IV};
static const struct TrainerMonNoItemDefaultMoves sParty_MagmaLeader[] = {DUMMY_TRAINER_MON};
static const struct TrainerMonNoItemDefaultMoves sParty_MagmaGruntM[] = {DUMMY_TRAINER_MON};
static const struct TrainerMonNoItemDefaultMoves sParty_MagmaGruntF[] = {DUMMY_TRAINER_MON};
static const struct TrainerMonNoItemDefaultMoves sParty_RSLass[] = {DUMMY_TRAINER_MON};
static const struct TrainerMonNoItemDefaultMoves sParty_RSBugCatcher[] = {DUMMY_TRAINER_MON};
static const struct TrainerMonNoItemDefaultMoves sParty_RSHiker[] = {DUMMY_TRAINER_MON};
static const struct TrainerMonNoItemDefaultMoves sParty_RSYoungCouple[] = {DUMMY_TRAINER_MON, DUMMY_TRAINER_MON};
static const struct TrainerMonNoItemDefaultMoves sParty_OldCouple[] = {DUMMY_TRAINER_MON};
static const struct TrainerMonNoItemDefaultMoves sParty_RSSisAndBro[] = {DUMMY_TRAINER_MON};
static const struct TrainerMonNoItemDefaultMoves sParty_AquaAdminMatt[] = {DUMMY_TRAINER_MON};
static const struct TrainerMonNoItemDefaultMoves sParty_AquaAdminShelly[] = {DUMMY_TRAINER_MON};
static const struct TrainerMonNoItemDefaultMoves sParty_MagmaAdminTabitha[] = {DUMMY_TRAINER_MON};
static const struct TrainerMonNoItemDefaultMoves sParty_MagmaAdminCourtney[] = {DUMMY_TRAINER_MON};
static const struct TrainerMonNoItemDefaultMoves sParty_LeaderWattson[] = {DUMMY_TRAINER_MON};
static const struct TrainerMonNoItemDefaultMoves sParty_LeaderFlannery[] = {DUMMY_TRAINER_MON};
static const struct TrainerMonNoItemDefaultMoves sParty_LeaderNorman[] = {DUMMY_TRAINER_MON};
static const struct TrainerMonNoItemDefaultMoves sParty_LeaderWinona[] = {DUMMY_TRAINER_MON};
static const struct TrainerMonNoItemDefaultMoves sParty_LeaderWallace[] = {DUMMY_TRAINER_MON};
static const struct TrainerMonNoItemDefaultMoves sParty_EliteFourGlacia[] = {DUMMY_TRAINER_MON};
static const struct TrainerMonNoItemDefaultMoves sParty_EliteFourDrake[] = {DUMMY_TRAINER_MON};

// Start of actual trainer data
static const struct TrainerMonNoItemDefaultMoves sParty_YoungsterBen[] = {
    {
        .iv = 0,
        .lvl = 11,
        .species = SPECIES_RATTATA,
    },
    {
        .iv = 0,
        .lvl = 11,
        .species = SPECIES_EKANS,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_YoungsterCalvin[] = {
    {
        .iv = 0,
        .lvl = 14,
        .species = SPECIES_SPEAROW,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_YoungsterJosh[] = {
    {
        .iv = 0,
        .lvl = 10,
        .species = SPECIES_RATTATA,
    },
    {
        .iv = 0,
        .lvl = 10,
        .species = SPECIES_RATTATA,
    },
    {
        .iv = 0,
        .lvl = 10,
        .species = SPECIES_ZUBAT,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_YoungsterTimmy[] = {
    {
        .iv = 0,
        .lvl = 14,
        .species = SPECIES_SANDSHREW,
    },
    {
        .iv = 0,
        .lvl = 14,
        .species = SPECIES_EKANS,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_YoungsterJoey[] = {
    {
        .iv = 0,
        .lvl = 15,
        .species = SPECIES_RATTATA,
    },
    {
        .iv = 0,
        .lvl = 15,
        .species = SPECIES_SPEAROW,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_YoungsterDan[] = {
    {
        .iv = 0,
        .lvl = 17,
        .species = SPECIES_SLOWPOKE,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_YoungsterChad[] = {
    {
        .iv = 0,
        .lvl = 14,
        .species = SPECIES_EKANS,
    },
    {
        .iv = 0,
        .lvl = 14,
        .species = SPECIES_SANDSHREW,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_YoungsterTyler[] = {
    {
        .iv = 0,
        .lvl = 21,
        .species = SPECIES_NIDORAN_M,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_YoungsterEddie[] = {
    {
        .iv = 0,
        .lvl = 21,
        .species = SPECIES_EKANS,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_YoungsterDillon[] = {
    {
        .iv = 0,
        .lvl = 19,
        .species = SPECIES_SANDSHREW,
    },
    {
        .iv = 0,
        .lvl = 19,
        .species = SPECIES_ZUBAT,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_YoungsterYasu[] = {
    {
        .iv = 0,
        .lvl = 17,
        .species = SPECIES_RATTATA,
    },
    {
        .iv = 0,
        .lvl = 17,
        .species = SPECIES_RATTATA,
    },
    {
        .iv = 0,
        .lvl = 17,
        .species = SPECIES_RATICATE,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_YoungsterDave[] = {
    {
        .iv = 0,
        .lvl = 18,
        .species = SPECIES_NIDORAN_M,
    },
    {
        .iv = 0,
        .lvl = 18,
        .species = SPECIES_NIDORINO,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_YoungsterBen2[] = {
    {
        .iv = 20,
        .lvl = 17,
        .species = SPECIES_RATTATA,
    },
    {
        .iv = 20,
        .lvl = 17,
        .species = SPECIES_EKANS,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_BugCatcherRick[] = {
    {
        .iv = 0,
        .lvl = 6,
        .species = SPECIES_WEEDLE,
    },
    {
        .iv = 0,
        .lvl = 6,
        .species = SPECIES_CATERPIE,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_BugCatcherDoug[] = {
    {
        .iv = 0,
        .lvl = 7,
        .species = SPECIES_WEEDLE,
    },
    {
        .iv = 0,
        .lvl = 7,
        .species = SPECIES_KAKUNA,
    },
    {
        .iv = 0,
        .lvl = 7,
        .species = SPECIES_WEEDLE,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_BugCatcherSammy[] = {
    {
        .iv = 0,
        .lvl = 9,
        .species = SPECIES_WEEDLE,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_BugCatcherColton[] = {
    {
        .iv = 0,
        .lvl = 10,
        .species = SPECIES_CATERPIE,
    },
    {
        .iv = 0,
        .lvl = 10,
        .species = SPECIES_WEEDLE,
    },
    {
        .iv = 0,
        .lvl = 10,
        .species = SPECIES_CATERPIE,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_BugCatcherGreg[] = {
    {
        .iv = 0,
        .lvl = 9,
        .species = SPECIES_WEEDLE,
    },
    {
        .iv = 0,
        .lvl = 9,
        .species = SPECIES_KAKUNA,
    },
    {
        .iv = 0,
        .lvl = 9,
        .species = SPECIES_CATERPIE,
    },
    {
        .iv = 0,
        .lvl = 9,
        .species = SPECIES_METAPOD,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_BugCatcherJames[] = {
    {
        .iv = 0,
        .lvl = 11,
        .species = SPECIES_CATERPIE,
    },
    {
        .iv = 0,
        .lvl = 11,
        .species = SPECIES_METAPOD,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_BugCatcherKent[] = {
    {
        .iv = 0,
        .lvl = 11,
        .species = SPECIES_WEEDLE,
    },
    {
        .iv = 0,
        .lvl = 11,
        .species = SPECIES_KAKUNA,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_BugCatcherRobby[] = {
    {
        .iv = 0,
        .lvl = 10,
        .species = SPECIES_CATERPIE,
    },
    {
        .iv = 0,
        .lvl = 10,
        .species = SPECIES_METAPOD,
    },
    {
        .iv = 0,
        .lvl = 10,
        .species = SPECIES_CATERPIE,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_BugCatcherCale[] = {
    {
        .iv = 0,
        .lvl = 10,
        .species = SPECIES_CATERPIE,
    },
    {
        .iv = 0,
        .lvl = 10,
        .species = SPECIES_WEEDLE,
    },
    {
        .iv = 0,
        .lvl = 10,
        .species = SPECIES_METAPOD,
    },
    {
        .iv = 0,
        .lvl = 10,
        .species = SPECIES_KAKUNA,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_BugCatcherKeigo[] = {
    {
        .iv = 0,
        .lvl = 16,
        .species = SPECIES_WEEDLE,
    },
    {
        .iv = 0,
        .lvl = 16,
        .species = SPECIES_CATERPIE,
    },
    {
        .iv = 0,
        .lvl = 16,
        .species = SPECIES_WEEDLE,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_BugCatcherElijah[] = {
    {
        .iv = 0,
        .lvl = 20,
        .species = SPECIES_BUTTERFREE,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_BugCatcher2[] = {
    {
        .iv = 0,
        .lvl = 18,
        .species = SPECIES_METAPOD,
    },
    {
        .iv = 0,
        .lvl = 18,
        .species = SPECIES_CATERPIE,
    },
    {
        .iv = 0,
        .lvl = 18,
        .species = SPECIES_VENONAT,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_BugCatcherBrent[] = {
    {
        .iv = 0,
        .lvl = 19,
        .species = SPECIES_BEEDRILL,
    },
    {
        .iv = 0,
        .lvl = 19,
        .species = SPECIES_BEEDRILL,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_BugCatcherConner[] = {
    {
        .iv = 0,
        .lvl = 20,
        .species = SPECIES_CATERPIE,
    },
    {
        .iv = 0,
        .lvl = 20,
        .species = SPECIES_WEEDLE,
    },
    {
        .iv = 0,
        .lvl = 20,
        .species = SPECIES_VENONAT,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_LassJanice[] = {
    {
        .iv = 0,
        .lvl = 9,
        .species = SPECIES_PIDGEY,
    },
    {
        .iv = 0,
        .lvl = 9,
        .species = SPECIES_PIDGEY,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_LassSally[] = {
    {
        .iv = 0,
        .lvl = 10,
        .species = SPECIES_RATTATA,
    },
    {
        .iv = 0,
        .lvl = 10,
        .species = SPECIES_NIDORAN_F,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_LassRobin[] = {
    {
        .iv = 0,
        .lvl = 14,
        .species = SPECIES_JIGGLYPUFF,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_LassCrissy[] = {
    {
        .iv = 0,
        .lvl = 31,
        .species = SPECIES_PARAS,
    },
    {
        .iv = 0,
        .lvl = 31,
        .species = SPECIES_PARAS,
    },
    {
        .iv = 0,
        .lvl = 31,
        .species = SPECIES_PARASECT,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_LassMiriam[] = {
    {
        .iv = 0,
        .lvl = 11,
        .species = SPECIES_ODDISH,
    },
    {
        .iv = 0,
        .lvl = 11,
        .species = SPECIES_BELLSPROUT,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_LassIris[] = {
    {
        .iv = 0,
        .lvl = 14,
        .species = SPECIES_CLEFAIRY,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_LassReli[] = {
    {
        .iv = 0,
        .lvl = 16,
        .species = SPECIES_NIDORAN_M,
    },
    {
        .iv = 0,
        .lvl = 16,
        .species = SPECIES_NIDORAN_F,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_LassAli[] = {
    {
        .iv = 0,
        .lvl = 12,
        .species = SPECIES_PIDGEY,
    },
    {
        .iv = 0,
        .lvl = 12,
        .species = SPECIES_ODDISH,
    },
    {
        .iv = 0,
        .lvl = 12,
        .species = SPECIES_BELLSPROUT,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_Lass2[] = {
    {
        .iv = 0,
        .lvl = 15,
        .species = SPECIES_NIDORAN_M,
    },
    {
        .iv = 0,
        .lvl = 15,
        .species = SPECIES_NIDORAN_F,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_LassHaley[] = {
    {
        .iv = 0,
        .lvl = 13,
        .species = SPECIES_ODDISH,
    },
    {
        .iv = 0,
        .lvl = 13,
        .species = SPECIES_PIDGEY,
    },
    {
        .iv = 0,
        .lvl = 13,
        .species = SPECIES_ODDISH,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_LassAnn[] = {
    {
        .iv = 0,
        .lvl = 18,
        .species = SPECIES_PIDGEY,
    },
    {
        .iv = 0,
        .lvl = 18,
        .species = SPECIES_NIDORAN_F,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_LassDawn[] = {
    {
        .iv = 0,
        .lvl = 18,
        .species = SPECIES_RATTATA,
    },
    {
        .iv = 0,
        .lvl = 18,
        .species = SPECIES_PIKACHU,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_LassPaige[] = {
    {
        .iv = 0,
        .lvl = 23,
        .species = SPECIES_NIDORAN_F,
    },
    {
        .iv = 0,
        .lvl = 23,
        .species = SPECIES_NIDORINA,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_LassAndrea[] = {
    {
        .iv = 0,
        .lvl = 24,
        .species = SPECIES_MEOWTH,
    },
    {
        .iv = 0,
        .lvl = 24,
        .species = SPECIES_MEOWTH,
    },
    {
        .iv = 0,
        .lvl = 24,
        .species = SPECIES_MEOWTH,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_LassMegan[] = {
    {
        .iv = 0,
        .lvl = 19,
        .species = SPECIES_PIDGEY,
    },
    {
        .iv = 0,
        .lvl = 19,
        .species = SPECIES_RATTATA,
    },
    {
        .iv = 0,
        .lvl = 19,
        .species = SPECIES_NIDORAN_M,
    },
    {
        .iv = 0,
        .lvl = 19,
        .species = SPECIES_MEOWTH,
    },
    {
        .iv = 0,
        .lvl = 19,
        .species = SPECIES_PIKACHU,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_LassJulia[] = {
    {
        .iv = 0,
        .lvl = 22,
        .species = SPECIES_CLEFAIRY,
    },
    {
        .iv = 0,
        .lvl = 22,
        .species = SPECIES_CLEFAIRY,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_LassKay[] = {
    {
        .iv = 0,
        .lvl = 23,
        .species = SPECIES_BELLSPROUT,
    },
    {
        .iv = 0,
        .lvl = 23,
        .species = SPECIES_WEEPINBELL,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_LassLisa[] = {
    {
        .iv = 0,
        .lvl = 23,
        .species = SPECIES_ODDISH,
    },
    {
        .iv = 0,
        .lvl = 23,
        .species = SPECIES_GLOOM,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_SailorEdmond[] = {
    {
        .iv = 0,
        .lvl = 18,
        .species = SPECIES_MACHOP,
    },
    {
        .iv = 0,
        .lvl = 18,
        .species = SPECIES_SHELLDER,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_SailorTrevor[] = {
    {
        .iv = 0,
        .lvl = 17,
        .species = SPECIES_MACHOP,
    },
    {
        .iv = 0,
        .lvl = 17,
        .species = SPECIES_TENTACOOL,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_SailorLeonard[] = {
    {
        .iv = 0,
        .lvl = 21,
        .species = SPECIES_SHELLDER,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_SailorDuncan[] = {
    {
        .iv = 0,
        .lvl = 17,
        .species = SPECIES_HORSEA,
    },
    {
        .iv = 0,
        .lvl = 17,
        .species = SPECIES_SHELLDER,
    },
    {
        .iv = 0,
        .lvl = 17,
        .species = SPECIES_TENTACOOL,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_SailorHuey[] = {
    {
        .iv = 0,
        .lvl = 18,
        .species = SPECIES_TENTACOOL,
    },
    {
        .iv = 0,
        .lvl = 18,
        .species = SPECIES_STARYU,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_SailorDylan[] = {
    {
        .iv = 0,
        .lvl = 17,
        .species = SPECIES_HORSEA,
    },
    {
        .iv = 0,
        .lvl = 17,
        .species = SPECIES_HORSEA,
    },
    {
        .iv = 0,
        .lvl = 17,
        .species = SPECIES_HORSEA,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_SailorPhillip[] = {
    {
        .iv = 0,
        .lvl = 20,
        .species = SPECIES_MACHOP,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_SailorDwayne[] = {
    {
        .iv = 0,
        .lvl = 21,
        .species = SPECIES_PIKACHU,
    },
    {
        .iv = 0,
        .lvl = 21,
        .species = SPECIES_PIKACHU,
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_CamperLiam[] = {
    {
        .iv = 0,
        .lvl = 10,
        .species = SPECIES_GEODUDE,
        .moves = {MOVE_TACKLE, MOVE_DEFENSE_CURL, MOVE_NONE, MOVE_NONE},
    },
    {
        .iv = 0,
        .lvl = 11,
        .species = SPECIES_SANDSHREW,
        .moves = {MOVE_SCRATCH, MOVE_DEFENSE_CURL, MOVE_SAND_ATTACK, MOVE_NONE},
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_CamperShane[] = {
    {
        .iv = 0,
        .lvl = 14,
        .species = SPECIES_RATTATA,
    },
    {
        .iv = 0,
        .lvl = 14,
        .species = SPECIES_EKANS,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_CamperEthan[] = {
    {
        .iv = 0,
        .lvl = 18,
        .species = SPECIES_MANKEY,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_CamperRicky[] = {
    {
        .iv = 0,
        .lvl = 20,
        .species = SPECIES_SQUIRTLE,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_CamperJeff[] = {
    {
        .iv = 0,
        .lvl = 16,
        .species = SPECIES_SPEAROW,
    },
    {
        .iv = 0,
        .lvl = 16,
        .species = SPECIES_RATICATE,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_Camper2[] = {DUMMY_TRAINER_MON};

static const struct TrainerMonNoItemDefaultMoves sParty_CamperChris[] = {
    {
        .iv = 0,
        .lvl = 21,
        .species = SPECIES_GROWLITHE,
    },
    {
        .iv = 0,
        .lvl = 21,
        .species = SPECIES_CHARMANDER,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_CamperDrew[] = {
    {
        .iv = 0,
        .lvl = 19,
        .species = SPECIES_RATTATA,
    },
    {
        .iv = 0,
        .lvl = 19,
        .species = SPECIES_SANDSHREW,
    },
    {
        .iv = 0,
        .lvl = 19,
        .species = SPECIES_EKANS,
    },
    {
        .iv = 0,
        .lvl = 19,
        .species = SPECIES_SANDSHREW,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_PicnickerDiana[] = {
    {
        .iv = 0,
        .lvl = 19,
        .species = SPECIES_GOLDEEN,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_PicnickerNancy[] = {
    {
        .iv = 0,
        .lvl = 16,
        .species = SPECIES_RATTATA,
    },
    {
        .iv = 0,
        .lvl = 16,
        .species = SPECIES_PIKACHU,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_PicnickerIsabelle[] = {
    {
        .iv = 0,
        .lvl = 16,
        .species = SPECIES_PIDGEY,
    },
    {
        .iv = 0,
        .lvl = 16,
        .species = SPECIES_PIDGEY,
    },
    {
        .iv = 0,
        .lvl = 16,
        .species = SPECIES_PIDGEY,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_PicnickerKelsey[] = {
    {
        .iv = 0,
        .lvl = 15,
        .species = SPECIES_NIDORAN_M,
    },
    {
        .iv = 0,
        .lvl = 15,
        .species = SPECIES_NIDORAN_F,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_PicnickerAlicia[] = {
    {
        .iv = 0,
        .lvl = 18,
        .species = SPECIES_ODDISH,
    },
    {
        .iv = 0,
        .lvl = 18,
        .species = SPECIES_BELLSPROUT,
    },
    {
        .iv = 0,
        .lvl = 18,
        .species = SPECIES_ODDISH,
    },
    {
        .iv = 0,
        .lvl = 18,
        .species = SPECIES_BELLSPROUT,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_PicnickerCaitlin[] = {
    {
        .iv = 0,
        .lvl = 23,
        .species = SPECIES_MEOWTH,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_PicnickerHeidi[] = {
    {
        .iv = 0,
        .lvl = 20,
        .species = SPECIES_PIKACHU,
    },
    {
        .iv = 0,
        .lvl = 20,
        .species = SPECIES_CLEFAIRY,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_PicnickerCarol[] = {
    {
        .iv = 0,
        .lvl = 21,
        .species = SPECIES_PIDGEY,
    },
    {
        .iv = 0,
        .lvl = 21,
        .species = SPECIES_PIDGEOTTO,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_PicnickerSofia[] = {
    {
        .iv = 0,
        .lvl = 21,
        .species = SPECIES_JIGGLYPUFF,
    },
    {
        .iv = 0,
        .lvl = 21,
        .species = SPECIES_PIDGEY,
    },
    {
        .iv = 0,
        .lvl = 21,
        .species = SPECIES_MEOWTH,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_PicnickerMartha[] = {
    {
        .iv = 0,
        .lvl = 22,
        .species = SPECIES_ODDISH,
    },
    {
        .iv = 0,
        .lvl = 22,
        .species = SPECIES_BULBASAUR,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_PicnickerTina[] = {
    {
        .iv = 0,
        .lvl = 24,
        .species = SPECIES_BULBASAUR,
    },
    {
        .iv = 0,
        .lvl = 24,
        .species = SPECIES_IVYSAUR,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_PicnickerHannah[] = {
    {
        .iv = 0,
        .lvl = 24,
        .species = SPECIES_PIDGEY,
    },
    {
        .iv = 0,
        .lvl = 24,
        .species = SPECIES_MEOWTH,
    },
    {
        .iv = 0,
        .lvl = 24,
        .species = SPECIES_RATTATA,
    },
    {
        .iv = 0,
        .lvl = 24,
        .species = SPECIES_PIKACHU,
    },
    {
        .iv = 0,
        .lvl = 24,
        .species = SPECIES_MEOWTH,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_PokemaniacMark[] = {
    {
        .iv = 30,
        .lvl = 29,
        .species = SPECIES_RHYHORN,
    },
    {
        .iv = 30,
        .lvl = 29,
        .species = SPECIES_LICKITUNG,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_PokemaniacHerman[] = {
    {
        .iv = 30,
        .lvl = 20,
        .species = SPECIES_CUBONE,
    },
    {
        .iv = 30,
        .lvl = 20,
        .species = SPECIES_SLOWPOKE,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_PokemaniacCooper[] = {
    {
        .iv = 30,
        .lvl = 20,
        .species = SPECIES_SLOWPOKE,
    },
    {
        .iv = 30,
        .lvl = 20,
        .species = SPECIES_SLOWPOKE,
    },
    {
        .iv = 30,
        .lvl = 20,
        .species = SPECIES_SLOWPOKE,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_PokemaniacSteve[] = {
    {
        .iv = 30,
        .lvl = 22,
        .species = SPECIES_CHARMANDER,
    },
    {
        .iv = 30,
        .lvl = 22,
        .species = SPECIES_CUBONE,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_PokemaniacWinston[] = {
    {
        .iv = 30,
        .lvl = 25,
        .species = SPECIES_SLOWPOKE,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_PokemaniacDawson[] = {
    {
        .iv = 30,
        .lvl = 40,
        .species = SPECIES_CHARMELEON,
    },
    {
        .iv = 30,
        .lvl = 40,
        .species = SPECIES_LAPRAS,
    },
    {
        .iv = 30,
        .lvl = 40,
        .species = SPECIES_LICKITUNG,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_PokemaniacAshton[] = {
    {
        .iv = 30,
        .lvl = 23,
        .species = SPECIES_CUBONE,
    },
    {
        .iv = 30,
        .lvl = 23,
        .species = SPECIES_SLOWPOKE,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_SuperNerdJovan[] = {
    {
        .iv = 0,
        .lvl = 11,
        .species = SPECIES_MAGNEMITE,
    },
    {
        .iv = 0,
        .lvl = 11,
        .species = SPECIES_VOLTORB,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_SuperNerdMiguel[] = {
    {
        .iv = 0,
        .lvl = 12,
        .species = SPECIES_GRIMER,
    },
    {
        .iv = 0,
        .lvl = 12,
        .species = SPECIES_VOLTORB,
    },
    {
        .iv = 0,
        .lvl = 12,
        .species = SPECIES_KOFFING,
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_SuperNerdAidan[] = {
    {
        .iv = 0,
        .lvl = 20,
        .species = SPECIES_VOLTORB,
        .moves = {MOVE_SONIC_BOOM, MOVE_SCREECH, MOVE_TACKLE, MOVE_CHARGE},
    },
    {
        .iv = 0,
        .lvl = 20,
        .species = SPECIES_KOFFING,
        .moves = {MOVE_SLUDGE, MOVE_SMOG, MOVE_TACKLE, MOVE_POISON_GAS},
    },
    {
        .iv = 0,
        .lvl = 20,
        .species = SPECIES_VOLTORB,
        .moves = {MOVE_SONIC_BOOM, MOVE_SCREECH, MOVE_TACKLE, MOVE_CHARGE},
    },
    {
        .iv = 0,
        .lvl = 20,
        .species = SPECIES_MAGNEMITE,
        .moves = {MOVE_SONIC_BOOM, MOVE_SUPERSONIC, MOVE_THUNDER_SHOCK, MOVE_TACKLE},
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_SuperNerdGlenn[] = {
    {
        .iv = 0,
        .lvl = 22,
        .species = SPECIES_GRIMER,
    },
    {
        .iv = 0,
        .lvl = 22,
        .species = SPECIES_MUK,
    },
    {
        .iv = 0,
        .lvl = 22,
        .species = SPECIES_GRIMER,
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_SuperNerdLeslie[] = {
    {
        .iv = 0,
        .lvl = 26,
        .species = SPECIES_KOFFING,
        .moves = {MOVE_SLUDGE, MOVE_SMOKESCREEN, MOVE_SMOG, MOVE_SELF_DESTRUCT},
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_SuperNerd1[] = {
    {
        .iv = 0,
        .lvl = 22,
        .species = SPECIES_KOFFING,
    },
    {
        .iv = 0,
        .lvl = 22,
        .species = SPECIES_MAGNEMITE,
    },
    {
        .iv = 0,
        .lvl = 22,
        .species = SPECIES_WEEZING,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_SuperNerd2[] = {
    {
        .iv = 0,
        .lvl = 20,
        .species = SPECIES_MAGNEMITE,
    },
    {
        .iv = 0,
        .lvl = 20,
        .species = SPECIES_MAGNEMITE,
    },
    {
        .iv = 0,
        .lvl = 20,
        .species = SPECIES_KOFFING,
    },
    {
        .iv = 0,
        .lvl = 20,
        .species = SPECIES_MAGNEMITE,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_SuperNerd3[] = {
    {
        .iv = 0,
        .lvl = 24,
        .species = SPECIES_MAGNEMITE,
    },
    {
        .iv = 0,
        .lvl = 24,
        .species = SPECIES_VOLTORB,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_SuperNerdErik[] = {
    {
        .iv = 0,
        .lvl = 36,
        .species = SPECIES_VULPIX,
    },
    {
        .iv = 0,
        .lvl = 36,
        .species = SPECIES_VULPIX,
    },
    {
        .iv = 0,
        .lvl = 36,
        .species = SPECIES_NINETALES,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_SuperNerdAvery[] = {
    {
        .iv = 0,
        .lvl = 34,
        .species = SPECIES_PONYTA,
    },
    {
        .iv = 0,
        .lvl = 34,
        .species = SPECIES_CHARMANDER,
    },
    {
        .iv = 0,
        .lvl = 34,
        .species = SPECIES_VULPIX,
    },
    {
        .iv = 0,
        .lvl = 34,
        .species = SPECIES_GROWLITHE,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_SuperNerdDerek[] = {
    {
        .iv = 0,
        .lvl = 41,
        .species = SPECIES_RAPIDASH,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_SuperNerdZac[] = {
    {
        .iv = 0,
        .lvl = 37,
        .species = SPECIES_GROWLITHE,
    },
    {
        .iv = 0,
        .lvl = 37,
        .species = SPECIES_VULPIX,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_HikerMarcos[] = {
    {
        .iv = 0,
        .lvl = 10,
        .species = SPECIES_GEODUDE,
    },
    {
        .iv = 0,
        .lvl = 10,
        .species = SPECIES_GEODUDE,
    },
    {
        .iv = 0,
        .lvl = 10,
        .species = SPECIES_ONIX,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_HikerFranklin[] = {
    {
        .iv = 0,
        .lvl = 15,
        .species = SPECIES_MACHOP,
    },
    {
        .iv = 0,
        .lvl = 15,
        .species = SPECIES_GEODUDE,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_HikerNob[] = {
    {
        .iv = 0,
        .lvl = 13,
        .species = SPECIES_GEODUDE,
    },
    {
        .iv = 0,
        .lvl = 13,
        .species = SPECIES_GEODUDE,
    },
    {
        .iv = 0,
        .lvl = 13,
        .species = SPECIES_MACHOP,
    },
    {
        .iv = 0,
        .lvl = 13,
        .species = SPECIES_GEODUDE,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_HikerWayne[] = {
    {
        .iv = 0,
        .lvl = 17,
        .species = SPECIES_ONIX,
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_HikerAlan[] = {
    {
        .iv = 0,
        .lvl = 21,
        .species = SPECIES_GEODUDE,
        .moves = {MOVE_MAGNITUDE, MOVE_ROCK_THROW, MOVE_MUD_SPORT, MOVE_DEFENSE_CURL},
    },
    {
        .iv = 0,
        .lvl = 21,
        .species = SPECIES_ONIX,
        .moves = {MOVE_HARDEN, MOVE_ROCK_THROW, MOVE_BIND, MOVE_SCREECH},
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_HikerBrice[] = {
    {
        .iv = 0,
        .lvl = 20,
        .species = SPECIES_GEODUDE,
    },
    {
        .iv = 0,
        .lvl = 20,
        .species = SPECIES_MACHOP,
    },
    {
        .iv = 0,
        .lvl = 20,
        .species = SPECIES_GEODUDE,
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_HikerClark[] = {
    {
        .iv = 0,
        .lvl = 21,
        .species = SPECIES_GEODUDE,
        .moves = {MOVE_MAGNITUDE, MOVE_ROCK_THROW, MOVE_MUD_SPORT, MOVE_DEFENSE_CURL},
    },
    {
        .iv = 0,
        .lvl = 21,
        .species = SPECIES_ONIX,
        .moves = {MOVE_HARDEN, MOVE_ROCK_THROW, MOVE_BIND, MOVE_SCREECH},
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_HikerTrent[] = {
    {
        .iv = 0,
        .lvl = 19,
        .species = SPECIES_ONIX,
    },
    {
        .iv = 0,
        .lvl = 19,
        .species = SPECIES_GRAVELER,
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_HikerDudley[] = {
    {
        .iv = 0,
        .lvl = 21,
        .species = SPECIES_GEODUDE,
        .moves = {MOVE_MAGNITUDE, MOVE_ROCK_THROW, MOVE_MUD_SPORT, MOVE_DEFENSE_CURL},
    },
    {
        .iv = 0,
        .lvl = 21,
        .species = SPECIES_GEODUDE,
        .moves = {MOVE_MAGNITUDE, MOVE_ROCK_THROW, MOVE_MUD_SPORT, MOVE_DEFENSE_CURL},
    },
    {
        .iv = 0,
        .lvl = 21,
        .species = SPECIES_GRAVELER,
        .moves = {MOVE_MAGNITUDE, MOVE_ROCK_THROW, MOVE_MUD_SPORT, MOVE_DEFENSE_CURL},
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_HikerAllen[] = {
    {
        .iv = 0,
        .lvl = 25,
        .species = SPECIES_GEODUDE,
        .moves = {MOVE_MAGNITUDE, MOVE_ROCK_THROW, MOVE_MUD_SPORT, MOVE_DEFENSE_CURL},
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_HikerEric[] = {
    {
        .iv = 0,
        .lvl = 20,
        .species = SPECIES_MACHOP,
    },
    {
        .iv = 0,
        .lvl = 20,
        .species = SPECIES_ONIX,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_HikerLenny[] = {
    {
        .iv = 0,
        .lvl = 19,
        .species = SPECIES_GEODUDE,
    },
    {
        .iv = 0,
        .lvl = 19,
        .species = SPECIES_MACHOP,
    },
    {
        .iv = 0,
        .lvl = 19,
        .species = SPECIES_GEODUDE,
    },
    {
        .iv = 0,
        .lvl = 19,
        .species = SPECIES_GEODUDE,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_HikerOliver[] = {
    {
        .iv = 0,
        .lvl = 20,
        .species = SPECIES_ONIX,
    },
    {
        .iv = 0,
        .lvl = 20,
        .species = SPECIES_ONIX,
    },
    {
        .iv = 0,
        .lvl = 20,
        .species = SPECIES_GEODUDE,
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_HikerLucas[] = {
    {
        .iv = 0,
        .lvl = 21,
        .species = SPECIES_GEODUDE,
        .moves = {MOVE_MAGNITUDE, MOVE_ROCK_THROW, MOVE_MUD_SPORT, MOVE_DEFENSE_CURL},
    },
    {
        .iv = 0,
        .lvl = 21,
        .species = SPECIES_GRAVELER,
        .moves = {MOVE_MAGNITUDE, MOVE_ROCK_THROW, MOVE_MUD_SPORT, MOVE_DEFENSE_CURL},
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_BikerJared[] = {
    {
        .iv = 0,
        .lvl = 28,
        .species = SPECIES_KOFFING,
        .moves = {MOVE_SMOKESCREEN, MOVE_SLUDGE, MOVE_SMOG, MOVE_POISON_GAS},
    },
    {
        .iv = 0,
        .lvl = 28,
        .species = SPECIES_KOFFING,
        .moves = {MOVE_SMOKESCREEN, MOVE_SLUDGE, MOVE_SMOG, MOVE_TACKLE},
    },
    {
        .iv = 0,
        .lvl = 28,
        .species = SPECIES_KOFFING,
        .moves = {MOVE_SMOKESCREEN, MOVE_SLUDGE, MOVE_SMOG, MOVE_TACKLE},
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_BikerMalik[] = {
    {
        .iv = 0,
        .lvl = 29,
        .species = SPECIES_KOFFING,
        .moves = {MOVE_SMOKESCREEN, MOVE_SLUDGE, MOVE_SMOG, MOVE_TACKLE},
    },
    {
        .iv = 0,
        .lvl = 29,
        .species = SPECIES_GRIMER,
        .moves = {MOVE_SCREECH, MOVE_MINIMIZE, MOVE_SLUDGE, MOVE_DISABLE},
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_BikerErnest[] = {
    {
        .iv = 0,
        .lvl = 25,
        .species = SPECIES_KOFFING,
        .moves = {MOVE_SMOKESCREEN, MOVE_SLUDGE, MOVE_SMOG, MOVE_TACKLE},
    },
    {
        .iv = 0,
        .lvl = 25,
        .species = SPECIES_KOFFING,
        .moves = {MOVE_SMOKESCREEN, MOVE_SLUDGE, MOVE_SMOG, MOVE_TACKLE},
    },
    {
        .iv = 0,
        .lvl = 25,
        .species = SPECIES_WEEZING,
        .moves = {MOVE_SMOKESCREEN, MOVE_SLUDGE, MOVE_SMOG, MOVE_TACKLE},
    },
    {
        .iv = 0,
        .lvl = 25,
        .species = SPECIES_KOFFING,
        .moves = {MOVE_SMOKESCREEN, MOVE_SLUDGE, MOVE_SMOG, MOVE_TACKLE},
    },
    {
        .iv = 0,
        .lvl = 25,
        .species = SPECIES_GRIMER,
        .moves = {MOVE_MINIMIZE, MOVE_SLUDGE, MOVE_DISABLE, MOVE_POUND},
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_BikerAlex[] = {
    {
        .iv = 0,
        .lvl = 28,
        .species = SPECIES_KOFFING,
        .moves = {MOVE_SMOKESCREEN, MOVE_SLUDGE, MOVE_SMOG, MOVE_TACKLE},
    },
    {
        .iv = 0,
        .lvl = 28,
        .species = SPECIES_GRIMER,
        .moves = {MOVE_SCREECH, MOVE_MINIMIZE, MOVE_SLUDGE, MOVE_DISABLE},
    },
    {
        .iv = 0,
        .lvl = 28,
        .species = SPECIES_WEEZING,
        .moves = {MOVE_SMOKESCREEN, MOVE_SLUDGE, MOVE_SMOG, MOVE_TACKLE},
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_BikerLao[] = {
    {
        .iv = 0,
        .lvl = 29,
        .species = SPECIES_GRIMER,
        .moves = {MOVE_SCREECH, MOVE_MINIMIZE, MOVE_SLUDGE, MOVE_DISABLE},
    },
    {
        .iv = 0,
        .lvl = 29,
        .species = SPECIES_KOFFING,
        .moves = {MOVE_SMOKESCREEN, MOVE_SLUDGE, MOVE_SMOG, MOVE_TACKLE},
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_Biker1[] = {DUMMY_TRAINER_MON};

static const struct TrainerMonNoItemDefaultMoves sParty_BikerHideo[] = {
    {
        .iv = 0,
        .lvl = 33,
        .species = SPECIES_WEEZING,
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_BikerRuben[] = {
    {
        .iv = 0,
        .lvl = 28,
        .species = SPECIES_WEEZING,
        .moves = {MOVE_SMOKESCREEN, MOVE_SLUDGE, MOVE_SMOG, MOVE_TACKLE},
    },
    {
        .iv = 0,
        .lvl = 28,
        .species = SPECIES_KOFFING,
        .moves = {MOVE_SMOKESCREEN, MOVE_SLUDGE, MOVE_SMOG, MOVE_TACKLE},
    },
    {
        .iv = 0,
        .lvl = 28,
        .species = SPECIES_WEEZING,
        .moves = {MOVE_SMOKESCREEN, MOVE_SLUDGE, MOVE_SMOG, MOVE_TACKLE},
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_BikerBilly[] = {
    {
        .iv = 0,
        .lvl = 33,
        .species = SPECIES_MUK,
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_BikerNikolas[] = {
    {
        .iv = 0,
        .lvl = 29,
        .species = SPECIES_VOLTORB,
        .moves = {MOVE_SPARK, MOVE_SONIC_BOOM, MOVE_SCREECH, MOVE_CHARGE},
    },
    {
        .iv = 0,
        .lvl = 29,
        .species = SPECIES_VOLTORB,
        .moves = {MOVE_SPARK, MOVE_SONIC_BOOM, MOVE_SCREECH, MOVE_CHARGE},
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_BikerJaxon[] = {
    {
        .iv = 0,
        .lvl = 29,
        .species = SPECIES_WEEZING,
        .moves = {MOVE_SLUDGE, MOVE_SMOKESCREEN, MOVE_SMOG, MOVE_TACKLE},
    },
    {
        .iv = 0,
        .lvl = 29,
        .species = SPECIES_MUK,
        .moves = {MOVE_SCREECH, MOVE_MINIMIZE, MOVE_SLUDGE, MOVE_DISABLE},
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_BikerWilliam[] = {
    {
        .iv = 0,
        .lvl = 25,
        .species = SPECIES_KOFFING,
        .moves = {MOVE_SMOKESCREEN, MOVE_SLUDGE, MOVE_SMOG, MOVE_TACKLE},
    },
    {
        .iv = 0,
        .lvl = 25,
        .species = SPECIES_WEEZING,
        .moves = {MOVE_SMOKESCREEN, MOVE_SLUDGE, MOVE_SMOG, MOVE_TACKLE},
    },
    {
        .iv = 0,
        .lvl = 25,
        .species = SPECIES_KOFFING,
        .moves = {MOVE_SMOKESCREEN, MOVE_SLUDGE, MOVE_SMOG, MOVE_TACKLE},
    },
    {
        .iv = 0,
        .lvl = 25,
        .species = SPECIES_KOFFING,
        .moves = {MOVE_SMOKESCREEN, MOVE_SLUDGE, MOVE_SMOG, MOVE_TACKLE},
    },
    {
        .iv = 0,
        .lvl = 25,
        .species = SPECIES_WEEZING,
        .moves = {MOVE_SMOKESCREEN, MOVE_SLUDGE, MOVE_SELF_DESTRUCT, MOVE_TACKLE},
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_BikerLukas[] = {
    {
        .iv = 0,
        .lvl = 26,
        .species = SPECIES_KOFFING,
        .moves = {MOVE_SMOKESCREEN, MOVE_SLUDGE, MOVE_SMOG, MOVE_TACKLE},
    },
    {
        .iv = 0,
        .lvl = 26,
        .species = SPECIES_KOFFING,
        .moves = {MOVE_SMOKESCREEN, MOVE_SLUDGE, MOVE_SMOG, MOVE_TACKLE},
    },
    {
        .iv = 0,
        .lvl = 26,
        .species = SPECIES_GRIMER,
        .moves = {MOVE_SCREECH, MOVE_MINIMIZE, MOVE_SLUDGE, MOVE_DISABLE},
    },
    {
        .iv = 0,
        .lvl = 26,
        .species = SPECIES_KOFFING,
        .moves = {MOVE_SMOKESCREEN, MOVE_SLUDGE, MOVE_SMOG, MOVE_TACKLE},
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_BikerIsaac[] = {
    {
        .iv = 0,
        .lvl = 28,
        .species = SPECIES_GRIMER,
        .moves = {MOVE_SCREECH, MOVE_MINIMIZE, MOVE_SLUDGE, MOVE_DISABLE},
    },
    {
        .iv = 0,
        .lvl = 28,
        .species = SPECIES_GRIMER,
        .moves = {MOVE_SCREECH, MOVE_MINIMIZE, MOVE_SLUDGE, MOVE_DISABLE},
    },
    {
        .iv = 0,
        .lvl = 28,
        .species = SPECIES_KOFFING,
        .moves = {MOVE_SMOKESCREEN, MOVE_SLUDGE, MOVE_SMOG, MOVE_TACKLE},
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_BikerGerald[] = {
    {
        .iv = 0,
        .lvl = 29,
        .species = SPECIES_KOFFING,
        .moves = {MOVE_SMOKESCREEN, MOVE_SLUDGE, MOVE_SMOG, MOVE_TACKLE},
    },
    {
        .iv = 0,
        .lvl = 29,
        .species = SPECIES_MUK,
        .moves = {MOVE_SCREECH, MOVE_MINIMIZE, MOVE_SLUDGE, MOVE_DISABLE},
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_Burglar1[] = {
    {
        .iv = 0,
        .lvl = 29,
        .species = SPECIES_GROWLITHE,
    },
    {
        .iv = 0,
        .lvl = 29,
        .species = SPECIES_VULPIX,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_Burglar2[] = {
    {
        .iv = 0,
        .lvl = 33,
        .species = SPECIES_GROWLITHE,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_Burglar3[] = {
    {
        .iv = 0,
        .lvl = 28,
        .species = SPECIES_VULPIX,
    },
    {
        .iv = 0,
        .lvl = 28,
        .species = SPECIES_CHARMANDER,
    },
    {
        .iv = 0,
        .lvl = 28,
        .species = SPECIES_PONYTA,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_BurglarQuinn[] = {
    {
        .iv = 0,
        .lvl = 36,
        .species = SPECIES_GROWLITHE,
    },
    {
        .iv = 0,
        .lvl = 36,
        .species = SPECIES_VULPIX,
    },
    {
        .iv = 0,
        .lvl = 36,
        .species = SPECIES_NINETALES,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_BurglarRamon[] = {
    {
        .iv = 0,
        .lvl = 41,
        .species = SPECIES_PONYTA,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_BurglarDusty[] = {
    {
        .iv = 0,
        .lvl = 37,
        .species = SPECIES_VULPIX,
    },
    {
        .iv = 0,
        .lvl = 37,
        .species = SPECIES_GROWLITHE,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_BurglarArnie[] = {
    {
        .iv = 0,
        .lvl = 34,
        .species = SPECIES_CHARMANDER,
    },
    {
        .iv = 0,
        .lvl = 34,
        .species = SPECIES_CHARMELEON,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_Burglar4[] = {
    {
        .iv = 0,
        .lvl = 34,
        .species = SPECIES_CHARMANDER,
    },
    {
        .iv = 0,
        .lvl = 34,
        .species = SPECIES_CHARMELEON,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_BurglarSimon[] = {
    {
        .iv = 0,
        .lvl = 38,
        .species = SPECIES_NINETALES,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_BurglarLewis[] = {
    {
        .iv = 0,
        .lvl = 34,
        .species = SPECIES_GROWLITHE,
    },
    {
        .iv = 0,
        .lvl = 34,
        .species = SPECIES_PONYTA,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_EngineerBaily[] = {
    {
        .iv = 0,
        .lvl = 21,
        .species = SPECIES_VOLTORB,
    },
    {
        .iv = 0,
        .lvl = 21,
        .species = SPECIES_MAGNEMITE,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_EngineerBraxton[] = {
    {
        .iv = 0,
        .lvl = 21,
        .species = SPECIES_MAGNEMITE,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_EngineerBernie[] = {
    {
        .iv = 0,
        .lvl = 18,
        .species = SPECIES_MAGNEMITE,
    },
    {
        .iv = 0,
        .lvl = 18,
        .species = SPECIES_MAGNEMITE,
    },
    {
        .iv = 0,
        .lvl = 18,
        .species = SPECIES_MAGNETON,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_FishermanDale[] = {
    {
        .iv = 0,
        .lvl = 17,
        .species = SPECIES_GOLDEEN,
    },
    {
        .iv = 0,
        .lvl = 17,
        .species = SPECIES_TENTACOOL,
    },
    {
        .iv = 0,
        .lvl = 17,
        .species = SPECIES_GOLDEEN,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_FishermanBarny[] = {
    {
        .iv = 0,
        .lvl = 17,
        .species = SPECIES_TENTACOOL,
    },
    {
        .iv = 0,
        .lvl = 17,
        .species = SPECIES_STARYU,
    },
    {
        .iv = 0,
        .lvl = 17,
        .species = SPECIES_SHELLDER,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_FishermanNed[] = {
    {
        .iv = 0,
        .lvl = 22,
        .species = SPECIES_GOLDEEN,
    },
    {
        .iv = 0,
        .lvl = 22,
        .species = SPECIES_POLIWAG,
    },
    {
        .iv = 0,
        .lvl = 22,
        .species = SPECIES_GOLDEEN,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_FishermanChip[] = {
    {
        .iv = 0,
        .lvl = 24,
        .species = SPECIES_TENTACOOL,
    },
    {
        .iv = 0,
        .lvl = 24,
        .species = SPECIES_GOLDEEN,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_FishermanHank[] = {
    {
        .iv = 0,
        .lvl = 27,
        .species = SPECIES_GOLDEEN,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_FishermanElliot[] = {
    {
        .iv = 0,
        .lvl = 21,
        .species = SPECIES_POLIWAG,
    },
    {
        .iv = 0,
        .lvl = 21,
        .species = SPECIES_SHELLDER,
    },
    {
        .iv = 0,
        .lvl = 21,
        .species = SPECIES_GOLDEEN,
    },
    {
        .iv = 0,
        .lvl = 21,
        .species = SPECIES_HORSEA,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_FishermanRonald[] = {
    {
        .iv = 0,
        .lvl = 28,
        .species = SPECIES_SEAKING,
    },
    {
        .iv = 0,
        .lvl = 28,
        .species = SPECIES_GOLDEEN,
    },
    {
        .iv = 0,
        .lvl = 28,
        .species = SPECIES_SEAKING,
    },
    {
        .iv = 0,
        .lvl = 28,
        .species = SPECIES_SEAKING,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_FishermanClaude[] = {
    {
        .iv = 0,
        .lvl = 31,
        .species = SPECIES_SHELLDER,
    },
    {
        .iv = 0,
        .lvl = 31,
        .species = SPECIES_CLOYSTER,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_FishermanWade[] = {
    {
        .iv = 0,
        .lvl = 27,
        .species = SPECIES_MAGIKARP,
    },
    {
        .iv = 0,
        .lvl = 27,
        .species = SPECIES_MAGIKARP,
    },
    {
        .iv = 0,
        .lvl = 27,
        .species = SPECIES_MAGIKARP,
    },
    {
        .iv = 0,
        .lvl = 27,
        .species = SPECIES_MAGIKARP,
    },
    {
        .iv = 0,
        .lvl = 27,
        .species = SPECIES_MAGIKARP,
    },
    {
        .iv = 0,
        .lvl = 27,
        .species = SPECIES_MAGIKARP,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_FishermanNolan[] = {
    {
        .iv = 0,
        .lvl = 33,
        .species = SPECIES_SEAKING,
    },
    {
        .iv = 0,
        .lvl = 33,
        .species = SPECIES_GOLDEEN,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_FishermanAndrew[] = {
    {
        .iv = 0,
        .lvl = 24,
        .species = SPECIES_MAGIKARP,
    },
    {
        .iv = 0,
        .lvl = 24,
        .species = SPECIES_MAGIKARP,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_SwimmerMaleLuis[] = {
    {
        .iv = 0,
        .lvl = 16,
        .species = SPECIES_HORSEA,
    },
    {
        .iv = 0,
        .lvl = 16,
        .species = SPECIES_SHELLDER,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_SwimmerMaleRichard[] = {
    {
        .iv = 0,
        .lvl = 30,
        .species = SPECIES_TENTACOOL,
    },
    {
        .iv = 0,
        .lvl = 30,
        .species = SPECIES_SHELLDER,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_SwimmerMaleReece[] = {
    {
        .iv = 0,
        .lvl = 29,
        .species = SPECIES_GOLDEEN,
    },
    {
        .iv = 0,
        .lvl = 29,
        .species = SPECIES_HORSEA,
    },
    {
        .iv = 0,
        .lvl = 29,
        .species = SPECIES_STARYU,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_SwimmerMaleMatthew[] = {
    {
        .iv = 0,
        .lvl = 30,
        .species = SPECIES_POLIWAG,
    },
    {
        .iv = 0,
        .lvl = 30,
        .species = SPECIES_POLIWHIRL,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_SwimmerMaleDouglas[] = {
    {
        .iv = 0,
        .lvl = 27,
        .species = SPECIES_HORSEA,
    },
    {
        .iv = 0,
        .lvl = 27,
        .species = SPECIES_TENTACOOL,
    },
    {
        .iv = 0,
        .lvl = 27,
        .species = SPECIES_TENTACOOL,
    },
    {
        .iv = 0,
        .lvl = 27,
        .species = SPECIES_GOLDEEN,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_SwimmerMaleDavid[] = {
    {
        .iv = 0,
        .lvl = 29,
        .species = SPECIES_GOLDEEN,
    },
    {
        .iv = 0,
        .lvl = 29,
        .species = SPECIES_SHELLDER,
    },
    {
        .iv = 0,
        .lvl = 29,
        .species = SPECIES_SEAKING,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_SwimmerMaleTony[] = {
    {
        .iv = 0,
        .lvl = 30,
        .species = SPECIES_HORSEA,
    },
    {
        .iv = 0,
        .lvl = 30,
        .species = SPECIES_HORSEA,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_SwimmerMaleAxle[] = {
    {
        .iv = 0,
        .lvl = 27,
        .species = SPECIES_TENTACOOL,
    },
    {
        .iv = 0,
        .lvl = 27,
        .species = SPECIES_TENTACOOL,
    },
    {
        .iv = 0,
        .lvl = 27,
        .species = SPECIES_STARYU,
    },
    {
        .iv = 0,
        .lvl = 27,
        .species = SPECIES_HORSEA,
    },
    {
        .iv = 0,
        .lvl = 27,
        .species = SPECIES_TENTACRUEL,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_SwimmerMaleBarry[] = {
    {
        .iv = 0,
        .lvl = 31,
        .species = SPECIES_SHELLDER,
    },
    {
        .iv = 0,
        .lvl = 31,
        .species = SPECIES_CLOYSTER,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_SwimmerMaleDean[] = {
    {
        .iv = 0,
        .lvl = 35,
        .species = SPECIES_STARYU,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_SwimmerMaleDarrin[] = {
    {
        .iv = 0,
        .lvl = 28,
        .species = SPECIES_HORSEA,
    },
    {
        .iv = 0,
        .lvl = 28,
        .species = SPECIES_HORSEA,
    },
    {
        .iv = 0,
        .lvl = 28,
        .species = SPECIES_SEADRA,
    },
    {
        .iv = 0,
        .lvl = 28,
        .species = SPECIES_HORSEA,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_SwimmerMaleSpencer[] = {
    {
        .iv = 0,
        .lvl = 33,
        .species = SPECIES_SEADRA,
    },
    {
        .iv = 0,
        .lvl = 33,
        .species = SPECIES_TENTACRUEL,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_SwimmerMaleJack[] = {
    {
        .iv = 0,
        .lvl = 37,
        .species = SPECIES_STARMIE,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_SwimmerMaleJerome[] = {
    {
        .iv = 0,
        .lvl = 33,
        .species = SPECIES_STARYU,
    },
    {
        .iv = 0,
        .lvl = 33,
        .species = SPECIES_WARTORTLE,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_SwimmerMaleRoland[] = {
    {
        .iv = 0,
        .lvl = 32,
        .species = SPECIES_POLIWHIRL,
    },
    {
        .iv = 0,
        .lvl = 32,
        .species = SPECIES_TENTACOOL,
    },
    {
        .iv = 0,
        .lvl = 32,
        .species = SPECIES_SEADRA,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_CueBallKoji[] = {
    {
        .iv = 0,
        .lvl = 28,
        .species = SPECIES_MACHOP,
    },
    {
        .iv = 0,
        .lvl = 28,
        .species = SPECIES_MANKEY,
    },
    {
        .iv = 0,
        .lvl = 28,
        .species = SPECIES_MACHOP,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_CueBallLuke[] = {
    {
        .iv = 0,
        .lvl = 29,
        .species = SPECIES_MANKEY,
    },
    {
        .iv = 0,
        .lvl = 29,
        .species = SPECIES_MACHOP,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_CueBallCamron[] = {
    {
        .iv = 0,
        .lvl = 29,
        .species = SPECIES_MANKEY,
    },
    {
        .iv = 0,
        .lvl = 29,
        .species = SPECIES_MACHOP,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_CueBallRaul[] = {
    {
        .iv = 0,
        .lvl = 29,
        .species = SPECIES_MANKEY,
    },
    {
        .iv = 0,
        .lvl = 29,
        .species = SPECIES_PRIMEAPE,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_CueBallIsaiah[] = {
    {
        .iv = 0,
        .lvl = 29,
        .species = SPECIES_MACHOP,
    },
    {
        .iv = 0,
        .lvl = 29,
        .species = SPECIES_MACHAMP,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_CueBallZeek[] = {
    {
        .iv = 0,
        .lvl = 33,
        .species = SPECIES_MACHOKE,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_CueBallJamal[] = {
    {
        .iv = 0,
        .lvl = 26,
        .species = SPECIES_MANKEY,
    },
    {
        .iv = 0,
        .lvl = 26,
        .species = SPECIES_MANKEY,
    },
    {
        .iv = 0,
        .lvl = 26,
        .species = SPECIES_MACHAMP,
    },
    {
        .iv = 0,
        .lvl = 26,
        .species = SPECIES_MACHOP,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_CueBallCorey[] = {
    {
        .iv = 0,
        .lvl = 29,
        .species = SPECIES_PRIMEAPE,
    },
    {
        .iv = 0,
        .lvl = 29,
        .species = SPECIES_MACHOKE,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_CueBallChase[] = {
    {
        .iv = 0,
        .lvl = 31,
        .species = SPECIES_TENTACOOL,
    },
    {
        .iv = 0,
        .lvl = 31,
        .species = SPECIES_TENTACOOL,
    },
    {
        .iv = 0,
        .lvl = 31,
        .species = SPECIES_TENTACRUEL,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_GamerHugo[] = {
    {
        .iv = 0,
        .lvl = 18,
        .species = SPECIES_POLIWAG,
    },
    {
        .iv = 0,
        .lvl = 18,
        .species = SPECIES_HORSEA,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_GamerJasper[] = {
    {
        .iv = 0,
        .lvl = 18,
        .species = SPECIES_BELLSPROUT,
    },
    {
        .iv = 0,
        .lvl = 18,
        .species = SPECIES_ODDISH,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_GamerDirk[] = {
    {
        .iv = 0,
        .lvl = 18,
        .species = SPECIES_VOLTORB,
    },
    {
        .iv = 0,
        .lvl = 18,
        .species = SPECIES_MAGNEMITE,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_GamerDarian[] = {
    {
        .iv = 0,
        .lvl = 18,
        .species = SPECIES_GROWLITHE,
    },
    {
        .iv = 0,
        .lvl = 18,
        .species = SPECIES_VULPIX,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_GamerStan[] = {
    {
        .iv = 0,
        .lvl = 22,
        .species = SPECIES_POLIWAG,
    },
    {
        .iv = 0,
        .lvl = 22,
        .species = SPECIES_POLIWAG,
    },
    {
        .iv = 0,
        .lvl = 22,
        .species = SPECIES_POLIWHIRL,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_Gamer1[] = {DUMMY_TRAINER_MON};

static const struct TrainerMonNoItemDefaultMoves sParty_GamerRich[] = {
    {
        .iv = 0,
        .lvl = 24,
        .species = SPECIES_GROWLITHE,
    },
    {
        .iv = 0,
        .lvl = 24,
        .species = SPECIES_VULPIX,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_BeautyBridget[] = {
    {
        .iv = 0,
        .lvl = 21,
        .species = SPECIES_ODDISH,
    },
    {
        .iv = 0,
        .lvl = 21,
        .species = SPECIES_BELLSPROUT,
    },
    {
        .iv = 0,
        .lvl = 21,
        .species = SPECIES_ODDISH,
    },
    {
        .iv = 0,
        .lvl = 21,
        .species = SPECIES_BELLSPROUT,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_BeautyTamia[] = {
    {
        .iv = 0,
        .lvl = 24,
        .species = SPECIES_BELLSPROUT,
    },
    {
        .iv = 0,
        .lvl = 24,
        .species = SPECIES_BELLSPROUT,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_BeautyLori[] = {
    {
        .iv = 0,
        .lvl = 24,
        .species = SPECIES_EXEGGCUTE,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_BeautyLola[] = {
    {
        .iv = 0,
        .lvl = 27,
        .species = SPECIES_RATTATA,
    },
    {
        .iv = 0,
        .lvl = 27,
        .species = SPECIES_PIKACHU,
    },
    {
        .iv = 0,
        .lvl = 27,
        .species = SPECIES_RATTATA,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_BeautySheila[] = {
    {
        .iv = 0,
        .lvl = 29,
        .species = SPECIES_CLEFAIRY,
    },
    {
        .iv = 0,
        .lvl = 29,
        .species = SPECIES_MEOWTH,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_SwimmerFemaleTiffany[] = {
    {
        .iv = 0,
        .lvl = 35,
        .species = SPECIES_SEAKING,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_SwimmerFemaleNora[] = {
    {
        .iv = 0,
        .lvl = 30,
        .species = SPECIES_SHELLDER,
    },
    {
        .iv = 0,
        .lvl = 30,
        .species = SPECIES_SHELLDER,
    },
    {
        .iv = 0,
        .lvl = 30,
        .species = SPECIES_CLOYSTER,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_SwimmerFemaleMelissa[] = {
    {
        .iv = 0,
        .lvl = 31,
        .species = SPECIES_POLIWAG,
    },
    {
        .iv = 0,
        .lvl = 31,
        .species = SPECIES_SEAKING,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_BeautyGrace[] = {
    {
        .iv = 0,
        .lvl = 29,
        .species = SPECIES_PIDGEOTTO,
    },
    {
        .iv = 0,
        .lvl = 29,
        .species = SPECIES_WIGGLYTUFF,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_BeautyOlivia[] = {
    {
        .iv = 0,
        .lvl = 29,
        .species = SPECIES_BULBASAUR,
    },
    {
        .iv = 0,
        .lvl = 29,
        .species = SPECIES_IVYSAUR,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_BeautyLauren[] = {
    {
        .iv = 0,
        .lvl = 33,
        .species = SPECIES_WEEPINBELL,
    },
    {
        .iv = 0,
        .lvl = 33,
        .species = SPECIES_BELLSPROUT,
    },
    {
        .iv = 0,
        .lvl = 33,
        .species = SPECIES_WEEPINBELL,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_SwimmerFemaleAnya[] = {
    {
        .iv = 0,
        .lvl = 27,
        .species = SPECIES_POLIWAG,
    },
    {
        .iv = 0,
        .lvl = 27,
        .species = SPECIES_GOLDEEN,
    },
    {
        .iv = 0,
        .lvl = 27,
        .species = SPECIES_SEAKING,
    },
    {
        .iv = 0,
        .lvl = 27,
        .species = SPECIES_GOLDEEN,
    },
    {
        .iv = 0,
        .lvl = 27,
        .species = SPECIES_POLIWAG,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_SwimmerFemaleAlice[] = {
    {
        .iv = 0,
        .lvl = 30,
        .species = SPECIES_GOLDEEN,
    },
    {
        .iv = 0,
        .lvl = 30,
        .species = SPECIES_SEAKING,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_SwimmerFemaleConnie[] = {
    {
        .iv = 0,
        .lvl = 29,
        .species = SPECIES_STARYU,
    },
    {
        .iv = 0,
        .lvl = 29,
        .species = SPECIES_STARYU,
    },
    {
        .iv = 0,
        .lvl = 29,
        .species = SPECIES_STARYU,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_SwimmerFemaleShirley[] = {
    {
        .iv = 0,
        .lvl = 30,
        .species = SPECIES_SEADRA,
    },
    {
        .iv = 0,
        .lvl = 30,
        .species = SPECIES_HORSEA,
    },
    {
        .iv = 0,
        .lvl = 30,
        .species = SPECIES_SEADRA,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_PsychicJohan[] = {
    {
        .iv = 50,
        .lvl = 31,
        .species = SPECIES_KADABRA,
    },
    {
        .iv = 50,
        .lvl = 31,
        .species = SPECIES_SLOWPOKE,
    },
    {
        .iv = 50,
        .lvl = 31,
        .species = SPECIES_MR_MIME,
    },
    {
        .iv = 50,
        .lvl = 31,
        .species = SPECIES_KADABRA,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_PsychicTyron[] = {
    {
        .iv = 50,
        .lvl = 34,
        .species = SPECIES_MR_MIME,
    },
    {
        .iv = 50,
        .lvl = 34,
        .species = SPECIES_KADABRA,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_PsychicCameron[] = {
    {
        .iv = 50,
        .lvl = 33,
        .species = SPECIES_SLOWPOKE,
    },
    {
        .iv = 50,
        .lvl = 33,
        .species = SPECIES_SLOWPOKE,
    },
    {
        .iv = 50,
        .lvl = 33,
        .species = SPECIES_SLOWBRO,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_PsychicPreston[] = {
    {
        .iv = 50,
        .lvl = 38,
        .species = SPECIES_SLOWBRO,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_RockerRandall[] = {
    {
        .iv = 0,
        .lvl = 20,
        .species = SPECIES_VOLTORB,
    },
    {
        .iv = 0,
        .lvl = 20,
        .species = SPECIES_MAGNEMITE,
    },
    {
        .iv = 0,
        .lvl = 20,
        .species = SPECIES_VOLTORB,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_RockerLuca[] = {
    {
        .iv = 0,
        .lvl = 29,
        .species = SPECIES_VOLTORB,
    },
    {
        .iv = 0,
        .lvl = 29,
        .species = SPECIES_ELECTRODE,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_JugglerDalton[] = {
    {
        .iv = 0,
        .lvl = 29,
        .species = SPECIES_KADABRA,
    },
    {
        .iv = 0,
        .lvl = 29,
        .species = SPECIES_MR_MIME,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_JugglerNelson[] = {
    {
        .iv = 0,
        .lvl = 41,
        .species = SPECIES_DROWZEE,
    },
    {
        .iv = 0,
        .lvl = 41,
        .species = SPECIES_HYPNO,
    },
    {
        .iv = 0,
        .lvl = 41,
        .species = SPECIES_KADABRA,
    },
    {
        .iv = 0,
        .lvl = 41,
        .species = SPECIES_KADABRA,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_JugglerKirk[] = {
    {
        .iv = 0,
        .lvl = 31,
        .species = SPECIES_DROWZEE,
    },
    {
        .iv = 0,
        .lvl = 31,
        .species = SPECIES_DROWZEE,
    },
    {
        .iv = 0,
        .lvl = 31,
        .species = SPECIES_KADABRA,
    },
    {
        .iv = 0,
        .lvl = 31,
        .species = SPECIES_DROWZEE,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_JugglerShawn[] = {
    {
        .iv = 0,
        .lvl = 34,
        .species = SPECIES_DROWZEE,
    },
    {
        .iv = 0,
        .lvl = 34,
        .species = SPECIES_HYPNO,
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_JugglerGregory[] = {
    {
        .iv = 0,
        .lvl = 48,
        .species = SPECIES_MR_MIME,
        .moves = {MOVE_PSYCHIC, MOVE_ROLE_PLAY, MOVE_DOUBLE_SLAP, MOVE_ENCORE},
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_JugglerEdward[] = {
    {
        .iv = 0,
        .lvl = 46,
        .species = SPECIES_VOLTORB,
        .moves = {MOVE_SWIFT, MOVE_LIGHT_SCREEN, MOVE_SPARK, MOVE_SONIC_BOOM},
    },
    {
        .iv = 0,
        .lvl = 46,
        .species = SPECIES_VOLTORB,
        .moves = {MOVE_SWIFT, MOVE_LIGHT_SCREEN, MOVE_SPARK, MOVE_SONIC_BOOM},
    },
    {
        .iv = 0,
        .lvl = 47,
        .species = SPECIES_ELECTRODE,
        .moves = {MOVE_SWIFT, MOVE_SPARK, MOVE_SELF_DESTRUCT, MOVE_SONIC_BOOM},
    },
    {
        .iv = 0,
        .lvl = 48,
        .species = SPECIES_MR_MIME,
        .moves = {MOVE_PSYCHIC, MOVE_ROLE_PLAY, MOVE_REFLECT, MOVE_ENCORE},
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_JugglerKayden[] = {
    {
        .iv = 0,
        .lvl = 38,
        .species = SPECIES_HYPNO,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_JugglerNate[] = {
    {
        .iv = 0,
        .lvl = 34,
        .species = SPECIES_DROWZEE,
    },
    {
        .iv = 0,
        .lvl = 34,
        .species = SPECIES_KADABRA,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_TamerPhil[] = {
    {
        .iv = 40,
        .lvl = 34,
        .species = SPECIES_SANDSLASH,
    },
    {
        .iv = 40,
        .lvl = 34,
        .species = SPECIES_ARBOK,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_TamerEdgar[] = {
    {
        .iv = 40,
        .lvl = 33,
        .species = SPECIES_ARBOK,
    },
    {
        .iv = 40,
        .lvl = 33,
        .species = SPECIES_SANDSLASH,
    },
    {
        .iv = 40,
        .lvl = 33,
        .species = SPECIES_ARBOK,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_TamerJason[] = {
    {
        .iv = 40,
        .lvl = 43,
        .species = SPECIES_RHYHORN,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_TamerCole[] = {
    {
        .iv = 40,
        .lvl = 39,
        .species = SPECIES_ARBOK,
    },
    {
        .iv = 40,
        .lvl = 39,
        .species = SPECIES_TAUROS,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_TamerVincent[] = {
    {
        .iv = 40,
        .lvl = 44,
        .species = SPECIES_PERSIAN,
    },
    {
        .iv = 40,
        .lvl = 44,
        .species = SPECIES_GOLDUCK,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_TamerJohn[] = {
    {
        .iv = 40,
        .lvl = 42,
        .species = SPECIES_RHYHORN,
    },
    {
        .iv = 40,
        .lvl = 42,
        .species = SPECIES_PRIMEAPE,
    },
    {
        .iv = 40,
        .lvl = 42,
        .species = SPECIES_ARBOK,
    },
    {
        .iv = 40,
        .lvl = 42,
        .species = SPECIES_TAUROS,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_BirdKeeperSebastian[] = {
    {
        .iv = 0,
        .lvl = 29,
        .species = SPECIES_PIDGEY,
    },
    {
        .iv = 0,
        .lvl = 29,
        .species = SPECIES_PIDGEOTTO,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_BirdKeeperPerry[] = {
    {
        .iv = 0,
        .lvl = 25,
        .species = SPECIES_SPEAROW,
    },
    {
        .iv = 0,
        .lvl = 25,
        .species = SPECIES_PIDGEY,
    },
    {
        .iv = 0,
        .lvl = 25,
        .species = SPECIES_PIDGEY,
    },
    {
        .iv = 0,
        .lvl = 25,
        .species = SPECIES_SPEAROW,
    },
    {
        .iv = 0,
        .lvl = 25,
        .species = SPECIES_SPEAROW,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_BirdKeeperRobert[] = {
    {
        .iv = 0,
        .lvl = 26,
        .species = SPECIES_PIDGEY,
    },
    {
        .iv = 0,
        .lvl = 26,
        .species = SPECIES_PIDGEOTTO,
    },
    {
        .iv = 0,
        .lvl = 26,
        .species = SPECIES_SPEAROW,
    },
    {
        .iv = 0,
        .lvl = 26,
        .species = SPECIES_FEAROW,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_BirdKeeperDonald[] = {
    {
        .iv = 0,
        .lvl = 33,
        .species = SPECIES_FARFETCHD,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_BirdKeeperBenny[] = {
    {
        .iv = 0,
        .lvl = 29,
        .species = SPECIES_SPEAROW,
    },
    {
        .iv = 0,
        .lvl = 29,
        .species = SPECIES_FEAROW,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_BirdKeeperEdwin[] = {
    {
        .iv = 0,
        .lvl = 26,
        .species = SPECIES_PIDGEOTTO,
    },
    {
        .iv = 0,
        .lvl = 26,
        .species = SPECIES_FARFETCHD,
    },
    {
        .iv = 0,
        .lvl = 26,
        .species = SPECIES_DODUO,
    },
    {
        .iv = 0,
        .lvl = 26,
        .species = SPECIES_PIDGEY,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_BirdKeeperChester[] = {
    {
        .iv = 0,
        .lvl = 28,
        .species = SPECIES_DODRIO,
    },
    {
        .iv = 0,
        .lvl = 28,
        .species = SPECIES_DODUO,
    },
    {
        .iv = 0,
        .lvl = 28,
        .species = SPECIES_DODUO,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_BirdKeeperWilton[] = {
    {
        .iv = 0,
        .lvl = 29,
        .species = SPECIES_SPEAROW,
    },
    {
        .iv = 0,
        .lvl = 29,
        .species = SPECIES_FEAROW,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_BirdKeeperRamiro[] = {
    {
        .iv = 0,
        .lvl = 34,
        .species = SPECIES_DODRIO,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_BirdKeeperJacob[] = {
    {
        .iv = 0,
        .lvl = 26,
        .species = SPECIES_SPEAROW,
    },
    {
        .iv = 0,
        .lvl = 26,
        .species = SPECIES_SPEAROW,
    },
    {
        .iv = 0,
        .lvl = 26,
        .species = SPECIES_FEAROW,
    },
    {
        .iv = 0,
        .lvl = 26,
        .species = SPECIES_SPEAROW,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_BirdKeeperRoger[] = {
    {
        .iv = 0,
        .lvl = 30,
        .species = SPECIES_FEAROW,
    },
    {
        .iv = 0,
        .lvl = 30,
        .species = SPECIES_FEAROW,
    },
    {
        .iv = 0,
        .lvl = 30,
        .species = SPECIES_PIDGEOTTO,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_BirdKeeperReed[] = {
    {
        .iv = 0,
        .lvl = 39,
        .species = SPECIES_PIDGEOTTO,
    },
    {
        .iv = 0,
        .lvl = 39,
        .species = SPECIES_PIDGEOTTO,
    },
    {
        .iv = 0,
        .lvl = 39,
        .species = SPECIES_PIDGEY,
    },
    {
        .iv = 0,
        .lvl = 39,
        .species = SPECIES_PIDGEOTTO,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_BirdKeeperKeith[] = {
    {
        .iv = 0,
        .lvl = 39,
        .species = SPECIES_FARFETCHD,
    },
    {
        .iv = 0,
        .lvl = 39,
        .species = SPECIES_FEAROW,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_BirdKeeperCarter[] = {
    {
        .iv = 0,
        .lvl = 28,
        .species = SPECIES_PIDGEY,
    },
    {
        .iv = 0,
        .lvl = 28,
        .species = SPECIES_DODUO,
    },
    {
        .iv = 0,
        .lvl = 28,
        .species = SPECIES_PIDGEOTTO,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_BirdKeeperMitch[] = {
    {
        .iv = 0,
        .lvl = 26,
        .species = SPECIES_PIDGEY,
    },
    {
        .iv = 0,
        .lvl = 26,
        .species = SPECIES_SPEAROW,
    },
    {
        .iv = 0,
        .lvl = 26,
        .species = SPECIES_PIDGEY,
    },
    {
        .iv = 0,
        .lvl = 26,
        .species = SPECIES_FEAROW,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_BirdKeeperBeck[] = {
    {
        .iv = 0,
        .lvl = 29,
        .species = SPECIES_PIDGEOTTO,
    },
    {
        .iv = 0,
        .lvl = 29,
        .species = SPECIES_FEAROW,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_BirdKeeperMarlon[] = {
    {
        .iv = 0,
        .lvl = 28,
        .species = SPECIES_SPEAROW,
    },
    {
        .iv = 0,
        .lvl = 28,
        .species = SPECIES_DODUO,
    },
    {
        .iv = 0,
        .lvl = 28,
        .species = SPECIES_FEAROW,
    },
};

static const struct TrainerMonItemDefaultMoves sParty_BlackBeltKoichi[] = {
    {
        .iv = 100,
        .lvl = 37,
        .species = SPECIES_HITMONLEE,
        .heldItem = ITEM_BLACK_BELT,
    },
    {
        .iv = 100,
        .lvl = 37,
        .species = SPECIES_HITMONCHAN,
        .heldItem = ITEM_BLACK_BELT,
    },
};

static const struct TrainerMonItemDefaultMoves sParty_BlackBeltMike[] = {
    {
        .iv = 100,
        .lvl = 31,
        .species = SPECIES_MANKEY,
        .heldItem = ITEM_BLACK_BELT,
    },
    {
        .iv = 100,
        .lvl = 31,
        .species = SPECIES_MANKEY,
        .heldItem = ITEM_BLACK_BELT,
    },
    {
        .iv = 100,
        .lvl = 31,
        .species = SPECIES_PRIMEAPE,
        .heldItem = ITEM_BLACK_BELT,
    },
};

static const struct TrainerMonItemDefaultMoves sParty_BlackBeltHideki[] = {
    {
        .iv = 100,
        .lvl = 32,
        .species = SPECIES_MACHOP,
        .heldItem = ITEM_BLACK_BELT,
    },
    {
        .iv = 100,
        .lvl = 32,
        .species = SPECIES_MACHOKE,
        .heldItem = ITEM_BLACK_BELT,
    },
};

static const struct TrainerMonItemDefaultMoves sParty_BlackBeltAaron[] = {
    {
        .iv = 100,
        .lvl = 36,
        .species = SPECIES_PRIMEAPE,
        .heldItem = ITEM_BLACK_BELT,
    },
};

static const struct TrainerMonItemDefaultMoves sParty_BlackBeltHitoshi[] = {
    {
        .iv = 100,
        .lvl = 31,
        .species = SPECIES_MACHOP,
        .heldItem = ITEM_BLACK_BELT,
    },
    {
        .iv = 100,
        .lvl = 31,
        .species = SPECIES_MANKEY,
        .heldItem = ITEM_BLACK_BELT,
    },
    {
        .iv = 100,
        .lvl = 31,
        .species = SPECIES_PRIMEAPE,
        .heldItem = ITEM_BLACK_BELT,
    },
};

static const struct TrainerMonItemDefaultMoves sParty_BlackBeltAtsushi[] = {
    {
        .iv = 100,
        .lvl = 40,
        .species = SPECIES_MACHOP,
        .heldItem = ITEM_BLACK_BELT,
    },
    {
        .iv = 100,
        .lvl = 40,
        .species = SPECIES_MACHOKE,
        .heldItem = ITEM_BLACK_BELT,
    },
};

static const struct TrainerMonItemDefaultMoves sParty_BlackBeltKiyo[] = {
    {
        .iv = 100,
        .lvl = 43,
        .species = SPECIES_MACHOKE,
        .heldItem = ITEM_BLACK_BELT,
    },
};

static const struct TrainerMonItemDefaultMoves sParty_BlackBeltTakashi[] = {
    {
        .iv = 100,
        .lvl = 38,
        .species = SPECIES_MACHOKE,
        .heldItem = ITEM_BLACK_BELT,
    },
    {
        .iv = 100,
        .lvl = 38,
        .species = SPECIES_MACHOP,
        .heldItem = ITEM_BLACK_BELT,
    },
    {
        .iv = 100,
        .lvl = 38,
        .species = SPECIES_MACHOKE,
        .heldItem = ITEM_BLACK_BELT,
    },
};

static const struct TrainerMonItemDefaultMoves sParty_BlackBeltDaisuke[] = {
    {
        .iv = 100,
        .lvl = 43,
        .species = SPECIES_MACHOKE,
        .heldItem = ITEM_BLACK_BELT,
    },
    {
        .iv = 100,
        .lvl = 43,
        .species = SPECIES_MACHOP,
        .heldItem = ITEM_BLACK_BELT,
    },
    {
        .iv = 100,
        .lvl = 43,
        .species = SPECIES_MACHOKE,
        .heldItem = ITEM_BLACK_BELT,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_RivalOaksLabSquirtle[] = {
    {
        .iv = 0,
        .lvl = 5,
        .species = SPECIES_SQUIRTLE,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_RivalOaksLabBulbasaur[] = {
    {
        .iv = 0,
        .lvl = 5,
        .species = SPECIES_BULBASAUR,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_RivalOaksLabCharmander[] = {
    {
        .iv = 0,
        .lvl = 5,
        .species = SPECIES_CHARMANDER,
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_RivalRoute22EarlySquirtle[] = {
    {
        .iv = 50,
        .lvl = 9,
        .species = SPECIES_PIDGEY,
        .moves = {MOVE_TACKLE, MOVE_SAND_ATTACK, MOVE_NONE, MOVE_NONE},
    },
    {
        .iv = 50,
        .lvl = 9,
        .species = SPECIES_SQUIRTLE,
        .moves = {MOVE_TACKLE, MOVE_TAIL_WHIP, MOVE_NONE, MOVE_NONE},
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_RivalRoute22EarlyBulbasaur[] = {
    {
        .iv = 50,
        .lvl = 9,
        .species = SPECIES_PIDGEY,
        .moves = {MOVE_TACKLE, MOVE_SAND_ATTACK, MOVE_NONE, MOVE_NONE},
    },
    {
        .iv = 50,
        .lvl = 9,
        .species = SPECIES_BULBASAUR,
        .moves = {MOVE_TACKLE, MOVE_GROWL, MOVE_NONE, MOVE_NONE},
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_RivalRoute22EarlyCharmander[] = {
    {
        .iv = 50,
        .lvl = 9,
        .species = SPECIES_PIDGEY,
        .moves = {MOVE_TACKLE, MOVE_SAND_ATTACK, MOVE_NONE, MOVE_NONE},
    },
    {
        .iv = 50,
        .lvl = 9,
        .species = SPECIES_CHARMANDER,
        .moves = {MOVE_SCRATCH, MOVE_GROWL, MOVE_NONE, MOVE_NONE},
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_RivalCeruleanSquirtle[] = {
    {
        .iv = 50,
        .lvl = 17,
        .species = SPECIES_PIDGEOTTO,
        .moves = {MOVE_TACKLE, MOVE_SAND_ATTACK, MOVE_GUST, MOVE_QUICK_ATTACK},
    },
    {
        .iv = 50,
        .lvl = 16,
        .species = SPECIES_ABRA,
        .moves = {MOVE_TELEPORT, MOVE_NONE, MOVE_NONE, MOVE_NONE},
    },
    {
        .iv = 50,
        .lvl = 15,
        .species = SPECIES_RATTATA,
        .moves = {MOVE_TACKLE, MOVE_TAIL_WHIP, MOVE_QUICK_ATTACK, MOVE_NONE},
    },
    {
        .iv = 100,
        .lvl = 18,
        .species = SPECIES_SQUIRTLE,
        .moves = {MOVE_TACKLE, MOVE_TAIL_WHIP, MOVE_WITHDRAW, MOVE_WATER_GUN},
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_RivalCeruleanBulbasaur[] = {
    {
        .iv = 50,
        .lvl = 17,
        .species = SPECIES_PIDGEOTTO,
        .moves = {MOVE_TACKLE, MOVE_SAND_ATTACK, MOVE_GUST, MOVE_QUICK_ATTACK},
    },
    {
        .iv = 50,
        .lvl = 16,
        .species = SPECIES_ABRA,
        .moves = {MOVE_TELEPORT, MOVE_NONE, MOVE_NONE, MOVE_NONE},
    },
    {
        .iv = 50,
        .lvl = 15,
        .species = SPECIES_RATTATA,
        .moves = {MOVE_TACKLE, MOVE_TAIL_WHIP, MOVE_QUICK_ATTACK, MOVE_NONE},
    },
    {
        .iv = 100,
        .lvl = 18,
        .species = SPECIES_BULBASAUR,
        .moves = {MOVE_SLEEP_POWDER, MOVE_POISON_POWDER, MOVE_VINE_WHIP, MOVE_LEECH_SEED},
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_RivalCeruleanCharmander[] = {
    {
        .iv = 50,
        .lvl = 17,
        .species = SPECIES_PIDGEOTTO,
        .moves = {MOVE_TACKLE, MOVE_SAND_ATTACK, MOVE_GUST, MOVE_QUICK_ATTACK},
    },
    {
        .iv = 50,
        .lvl = 16,
        .species = SPECIES_ABRA,
        .moves = {MOVE_TELEPORT, MOVE_NONE, MOVE_NONE, MOVE_NONE},
    },
    {
        .iv = 50,
        .lvl = 15,
        .species = SPECIES_RATTATA,
        .moves = {MOVE_TACKLE, MOVE_TAIL_WHIP, MOVE_QUICK_ATTACK, MOVE_NONE},
    },
    {
        .iv = 100,
        .lvl = 18,
        .species = SPECIES_CHARMANDER,
        .moves = {MOVE_METAL_CLAW, MOVE_EMBER, MOVE_GROWL, MOVE_SCRATCH},
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_ScientistTed[] = {
    {
        .iv = 0,
        .lvl = 29,
        .species = SPECIES_ELECTRODE,
    },
    {
        .iv = 0,
        .lvl = 29,
        .species = SPECIES_WEEZING,
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_ScientistConnor[] = {
    {
        .iv = 0,
        .lvl = 26,
        .species = SPECIES_GRIMER,
        .moves = {MOVE_SCREECH, MOVE_MINIMIZE, MOVE_SLUDGE, MOVE_DISABLE},
    },
    {
        .iv = 0,
        .lvl = 26,
        .species = SPECIES_WEEZING,
        .moves = {MOVE_SMOKESCREEN, MOVE_SLUDGE, MOVE_SMOG, MOVE_TACKLE},
    },
    {
        .iv = 0,
        .lvl = 26,
        .species = SPECIES_KOFFING,
        .moves = {MOVE_SMOKESCREEN, MOVE_SLUDGE, MOVE_SMOG, MOVE_SELF_DESTRUCT},
    },
    {
        .iv = 0,
        .lvl = 26,
        .species = SPECIES_WEEZING,
        .moves = {MOVE_SMOKESCREEN, MOVE_SLUDGE, MOVE_SMOG, MOVE_TACKLE},
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_ScientistJerry[] = {
    {
        .iv = 0,
        .lvl = 28,
        .species = SPECIES_MAGNEMITE,
    },
    {
        .iv = 0,
        .lvl = 28,
        .species = SPECIES_VOLTORB,
    },
    {
        .iv = 0,
        .lvl = 28,
        .species = SPECIES_MAGNETON,
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_ScientistJose[] = {
    {
        .iv = 0,
        .lvl = 29,
        .species = SPECIES_ELECTRODE,
        .moves = {MOVE_SPARK, MOVE_SONIC_BOOM, MOVE_SCREECH, MOVE_TACKLE},
    },
    {
        .iv = 0,
        .lvl = 29,
        .species = SPECIES_WEEZING,
        .moves = {MOVE_SMOKESCREEN, MOVE_SLUDGE, MOVE_SMOG, MOVE_TACKLE},
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_ScientistRodney[] = {
    {
        .iv = 0,
        .lvl = 33,
        .species = SPECIES_ELECTRODE,
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_ScientistBeau[] = {
    {
        .iv = 0,
        .lvl = 26,
        .species = SPECIES_MAGNETON,
        .moves = {MOVE_SPARK, MOVE_THUNDER_WAVE, MOVE_SONIC_BOOM, MOVE_SUPERSONIC},
    },
    {
        .iv = 0,
        .lvl = 26,
        .species = SPECIES_KOFFING,
        .moves = {MOVE_SMOKESCREEN, MOVE_SLUDGE, MOVE_SMOG, MOVE_TACKLE},
    },
    {
        .iv = 0,
        .lvl = 26,
        .species = SPECIES_WEEZING,
        .moves = {MOVE_SMOKESCREEN, MOVE_SLUDGE, MOVE_SMOG, MOVE_TACKLE},
    },
    {
        .iv = 0,
        .lvl = 26,
        .species = SPECIES_MAGNEMITE,
        .moves = {MOVE_SPARK, MOVE_THUNDER_WAVE, MOVE_SONIC_BOOM, MOVE_SUPERSONIC},
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_ScientistTaylor[] = {
    {
        .iv = 0,
        .lvl = 25,
        .species = SPECIES_VOLTORB,
        .moves = {MOVE_SPARK, MOVE_SONIC_BOOM, MOVE_SCREECH, MOVE_TACKLE},
    },
    {
        .iv = 0,
        .lvl = 25,
        .species = SPECIES_KOFFING,
        .moves = {MOVE_SMOKESCREEN, MOVE_SLUDGE, MOVE_SMOG, MOVE_TACKLE},
    },
    {
        .iv = 0,
        .lvl = 25,
        .species = SPECIES_MAGNETON,
        .moves = {MOVE_THUNDER_WAVE, MOVE_SONIC_BOOM, MOVE_SUPERSONIC, MOVE_THUNDER_SHOCK},
    },
    {
        .iv = 0,
        .lvl = 25,
        .species = SPECIES_MAGNEMITE,
        .moves = {MOVE_THUNDER_WAVE, MOVE_SONIC_BOOM, MOVE_SUPERSONIC, MOVE_THUNDER_SHOCK},
    },
    {
        .iv = 0,
        .lvl = 25,
        .species = SPECIES_KOFFING,
        .moves = {MOVE_SMOKESCREEN, MOVE_SLUDGE, MOVE_SMOG, MOVE_SELF_DESTRUCT},
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_ScientistJoshua[] = {
    {
        .iv = 0,
        .lvl = 29,
        .species = SPECIES_ELECTRODE,
    },
    {
        .iv = 0,
        .lvl = 29,
        .species = SPECIES_MUK,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_ScientistParker[] = {
    {
        .iv = 0,
        .lvl = 29,
        .species = SPECIES_GRIMER,
    },
    {
        .iv = 0,
        .lvl = 29,
        .species = SPECIES_ELECTRODE,
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_ScientistEd[] = {
    {
        .iv = 0,
        .lvl = 28,
        .species = SPECIES_VOLTORB,
        .moves = {MOVE_SPARK, MOVE_SONIC_BOOM, MOVE_SCREECH, MOVE_TACKLE},
    },
    {
        .iv = 0,
        .lvl = 28,
        .species = SPECIES_KOFFING,
        .moves = {MOVE_SMOKESCREEN, MOVE_SLUDGE, MOVE_TACKLE, MOVE_SMOG},
    },
    {
        .iv = 0,
        .lvl = 28,
        .species = SPECIES_MAGNETON,
        .moves = {MOVE_SPARK, MOVE_THUNDER_WAVE, MOVE_SONIC_BOOM, MOVE_SUPERSONIC},
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_ScientistTravis[] = {
    {
        .iv = 0,
        .lvl = 29,
        .species = SPECIES_MAGNEMITE,
    },
    {
        .iv = 0,
        .lvl = 29,
        .species = SPECIES_KOFFING,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_ScientistBraydon[] = {
    {
        .iv = 0,
        .lvl = 33,
        .species = SPECIES_MAGNEMITE,
    },
    {
        .iv = 0,
        .lvl = 33,
        .species = SPECIES_MAGNETON,
    },
    {
        .iv = 0,
        .lvl = 33,
        .species = SPECIES_VOLTORB,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_ScientistIvan[] = {
    {
        .iv = 0,
        .lvl = 34,
        .species = SPECIES_MAGNEMITE,
    },
    {
        .iv = 0,
        .lvl = 34,
        .species = SPECIES_ELECTRODE,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_BossGiovanni[] = {
    {
        .iv = 250,
        .lvl = 25,
        .species = SPECIES_ONIX,
    },
    {
        .iv = 250,
        .lvl = 24,
        .species = SPECIES_RHYHORN,
    },
    {
        .iv = 250,
        .lvl = 29,
        .species = SPECIES_KANGASKHAN,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_BossGiovanni2[] = {
    {
        .iv = 250,
        .lvl = 37,
        .species = SPECIES_NIDORINO,
    },
    {
        .iv = 250,
        .lvl = 35,
        .species = SPECIES_KANGASKHAN,
    },
    {
        .iv = 250,
        .lvl = 37,
        .species = SPECIES_RHYHORN,
    },
    {
        .iv = 250,
        .lvl = 41,
        .species = SPECIES_NIDOQUEEN,
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_LeaderGiovanni[] = {
    {
        .iv = 0,
        .lvl = 45,
        .species = SPECIES_RHYHORN,
        .moves = {MOVE_TAKE_DOWN, MOVE_ROCK_BLAST, MOVE_SCARY_FACE, MOVE_EARTHQUAKE},
    },
    {
        .iv = 0,
        .lvl = 42,
        .species = SPECIES_DUGTRIO,
        .moves = {MOVE_SLASH, MOVE_SAND_TOMB, MOVE_MUD_SLAP, MOVE_EARTHQUAKE},
    },
    {
        .iv = 0,
        .lvl = 44,
        .species = SPECIES_NIDOQUEEN,
        .moves = {MOVE_BODY_SLAM, MOVE_DOUBLE_KICK, MOVE_POISON_STING, MOVE_EARTHQUAKE},
    },
    {
        .iv = 0,
        .lvl = 45,
        .species = SPECIES_NIDOKING,
        .moves = {MOVE_THRASH, MOVE_DOUBLE_KICK, MOVE_POISON_STING, MOVE_EARTHQUAKE},
    },
    {
        .iv = 0,
        .lvl = 50,
        .species = SPECIES_RHYHORN,
        .moves = {MOVE_TAKE_DOWN, MOVE_ROCK_BLAST, MOVE_SCARY_FACE, MOVE_EARTHQUAKE},
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_TeamRocketGrunt[] = {
    {
        .iv = 0,
        .lvl = 13,
        .species = SPECIES_RATTATA,
    },
    {
        .iv = 0,
        .lvl = 13,
        .species = SPECIES_ZUBAT,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_TeamRocketGrunt2[] = {
    {
        .iv = 0,
        .lvl = 11,
        .species = SPECIES_SANDSHREW,
    },
    {
        .iv = 0,
        .lvl = 11,
        .species = SPECIES_RATTATA,
    },
    {
        .iv = 0,
        .lvl = 11,
        .species = SPECIES_ZUBAT,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_TeamRocketGrunt3[] = {
    {
        .iv = 0,
        .lvl = 11,
        .species = SPECIES_ZUBAT,
    },
    {
        .iv = 0,
        .lvl = 11,
        .species = SPECIES_EKANS,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_TeamRocketGrunt4[] = {
    {
        .iv = 0,
        .lvl = 13,
        .species = SPECIES_RATTATA,
    },
    {
        .iv = 0,
        .lvl = 13,
        .species = SPECIES_SANDSHREW,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_TeamRocketGrunt5[] = {
    {
        .iv = 0,
        .lvl = 17,
        .species = SPECIES_MACHOP,
    },
    {
        .iv = 0,
        .lvl = 17,
        .species = SPECIES_DROWZEE,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_TeamRocketGrunt6[] = {
    {
        .iv = 0,
        .lvl = 15,
        .species = SPECIES_EKANS,
    },
    {
        .iv = 0,
        .lvl = 15,
        .species = SPECIES_ZUBAT,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_TeamRocketGrunt7[] = {
    {
        .iv = 0,
        .lvl = 20,
        .species = SPECIES_RATICATE,
    },
    {
        .iv = 0,
        .lvl = 20,
        .species = SPECIES_ZUBAT,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_TeamRocketGrunt8[] = {
    {
        .iv = 0,
        .lvl = 21,
        .species = SPECIES_DROWZEE,
    },
    {
        .iv = 0,
        .lvl = 21,
        .species = SPECIES_MACHOP,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_TeamRocketGrunt9[] = {
    {
        .iv = 0,
        .lvl = 21,
        .species = SPECIES_RATICATE,
    },
    {
        .iv = 0,
        .lvl = 21,
        .species = SPECIES_RATICATE,
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_TeamRocketGrunt10[] = {
    {
        .iv = 0,
        .lvl = 20,
        .species = SPECIES_GRIMER,
        .moves = {MOVE_MINIMIZE, MOVE_SLUDGE, MOVE_DISABLE, MOVE_HARDEN},
    },
    {
        .iv = 0,
        .lvl = 20,
        .species = SPECIES_KOFFING,
        .moves = {MOVE_SMOG, MOVE_TACKLE, MOVE_POISON_GAS, MOVE_NONE},
    },
    {
        .iv = 0,
        .lvl = 20,
        .species = SPECIES_KOFFING,
        .moves = {MOVE_SMOG, MOVE_TACKLE, MOVE_POISON_GAS, MOVE_NONE},
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_TeamRocketGrunt11[] = {
    {
        .iv = 0,
        .lvl = 19,
        .species = SPECIES_RATTATA,
    },
    {
        .iv = 0,
        .lvl = 19,
        .species = SPECIES_RATICATE,
    },
    {
        .iv = 0,
        .lvl = 19,
        .species = SPECIES_RATICATE,
    },
    {
        .iv = 0,
        .lvl = 19,
        .species = SPECIES_RATTATA,
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_TeamRocketGrunt12[] = {
    {
        .iv = 0,
        .lvl = 22,
        .species = SPECIES_GRIMER,
        .moves = {MOVE_MINIMIZE, MOVE_SLUDGE, MOVE_DISABLE, MOVE_HARDEN},
    },
    {
        .iv = 0,
        .lvl = 22,
        .species = SPECIES_KOFFING,
        .moves = {MOVE_SLUDGE, MOVE_SMOG, MOVE_TACKLE, MOVE_POISON_GAS},
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_TeamRocketGrunt13[] = {
    {
        .iv = 0,
        .lvl = 17,
        .species = SPECIES_ZUBAT,
        .moves = {MOVE_BITE, MOVE_ASTONISH, MOVE_SUPERSONIC, MOVE_LEECH_LIFE},
    },
    {
        .iv = 0,
        .lvl = 17,
        .species = SPECIES_KOFFING,
        .moves = {MOVE_SMOG, MOVE_TACKLE, MOVE_POISON_GAS, MOVE_NONE},
    },
    {
        .iv = 0,
        .lvl = 17,
        .species = SPECIES_GRIMER,
        .moves = {MOVE_SLUDGE, MOVE_DISABLE, MOVE_HARDEN, MOVE_POUND},
    },
    {
        .iv = 0,
        .lvl = 17,
        .species = SPECIES_ZUBAT,
        .moves = {MOVE_BITE, MOVE_ASTONISH, MOVE_SUPERSONIC, MOVE_LEECH_LIFE},
    },
    {
        .iv = 0,
        .lvl = 17,
        .species = SPECIES_RATICATE,
        .moves = {MOVE_HYPER_FANG, MOVE_QUICK_ATTACK, MOVE_TAIL_WHIP, MOVE_TACKLE},
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_TeamRocketGrunt14[] = {
    {
        .iv = 0,
        .lvl = 20,
        .species = SPECIES_RATTATA,
    },
    {
        .iv = 0,
        .lvl = 20,
        .species = SPECIES_RATICATE,
    },
    {
        .iv = 0,
        .lvl = 20,
        .species = SPECIES_DROWZEE,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_TeamRocketGrunt15[] = {
    {
        .iv = 0,
        .lvl = 21,
        .species = SPECIES_MACHOP,
    },
    {
        .iv = 0,
        .lvl = 21,
        .species = SPECIES_MACHOP,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_TeamRocketGrunt16[] = {
    {
        .iv = 0,
        .lvl = 23,
        .species = SPECIES_SANDSHREW,
    },
    {
        .iv = 0,
        .lvl = 23,
        .species = SPECIES_EKANS,
    },
    {
        .iv = 0,
        .lvl = 23,
        .species = SPECIES_SANDSLASH,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_TeamRocketGrunt17[] = {
    {
        .iv = 0,
        .lvl = 23,
        .species = SPECIES_EKANS,
    },
    {
        .iv = 0,
        .lvl = 23,
        .species = SPECIES_SANDSHREW,
    },
    {
        .iv = 0,
        .lvl = 23,
        .species = SPECIES_ARBOK,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_TeamRocketGrunt18[] = {
    {
        .iv = 0,
        .lvl = 21,
        .species = SPECIES_KOFFING,
    },
    {
        .iv = 0,
        .lvl = 21,
        .species = SPECIES_ZUBAT,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_TeamRocketGrunt19[] = {
    {
        .iv = 0,
        .lvl = 25,
        .species = SPECIES_ZUBAT,
    },
    {
        .iv = 0,
        .lvl = 25,
        .species = SPECIES_ZUBAT,
    },
    {
        .iv = 0,
        .lvl = 25,
        .species = SPECIES_GOLBAT,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_TeamRocketGrunt20[] = {
    {
        .iv = 0,
        .lvl = 26,
        .species = SPECIES_KOFFING,
    },
    {
        .iv = 0,
        .lvl = 26,
        .species = SPECIES_DROWZEE,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_TeamRocketGrunt21[] = {
    {
        .iv = 0,
        .lvl = 23,
        .species = SPECIES_ZUBAT,
    },
    {
        .iv = 0,
        .lvl = 23,
        .species = SPECIES_RATTATA,
    },
    {
        .iv = 0,
        .lvl = 23,
        .species = SPECIES_RATICATE,
    },
    {
        .iv = 0,
        .lvl = 23,
        .species = SPECIES_ZUBAT,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_TeamRocketGrunt22[] = {
    {
        .iv = 0,
        .lvl = 26,
        .species = SPECIES_DROWZEE,
    },
    {
        .iv = 0,
        .lvl = 26,
        .species = SPECIES_KOFFING,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_TeamRocketGrunt23[] = {
    {
        .iv = 0,
        .lvl = 29,
        .species = SPECIES_CUBONE,
    },
    {
        .iv = 0,
        .lvl = 29,
        .species = SPECIES_ZUBAT,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_TeamRocketGrunt24[] = {
    {
        .iv = 0,
        .lvl = 25,
        .species = SPECIES_GOLBAT,
    },
    {
        .iv = 0,
        .lvl = 25,
        .species = SPECIES_ZUBAT,
    },
    {
        .iv = 0,
        .lvl = 25,
        .species = SPECIES_ZUBAT,
    },
    {
        .iv = 0,
        .lvl = 25,
        .species = SPECIES_RATICATE,
    },
    {
        .iv = 0,
        .lvl = 25,
        .species = SPECIES_ZUBAT,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_TeamRocketGrunt25[] = {
    {
        .iv = 0,
        .lvl = 28,
        .species = SPECIES_RATICATE,
    },
    {
        .iv = 0,
        .lvl = 28,
        .species = SPECIES_HYPNO,
    },
    {
        .iv = 0,
        .lvl = 28,
        .species = SPECIES_RATICATE,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_TeamRocketGrunt26[] = {
    {
        .iv = 0,
        .lvl = 29,
        .species = SPECIES_MACHOP,
    },
    {
        .iv = 0,
        .lvl = 29,
        .species = SPECIES_DROWZEE,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_TeamRocketGrunt27[] = {
    {
        .iv = 0,
        .lvl = 28,
        .species = SPECIES_EKANS,
    },
    {
        .iv = 0,
        .lvl = 28,
        .species = SPECIES_ZUBAT,
    },
    {
        .iv = 0,
        .lvl = 28,
        .species = SPECIES_CUBONE,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_TeamRocketGrunt28[] = {
    {
        .iv = 0,
        .lvl = 33,
        .species = SPECIES_ARBOK,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_TeamRocketGrunt29[] = {
    {
        .iv = 0,
        .lvl = 33,
        .species = SPECIES_HYPNO,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_TeamRocketGrunt30[] = {
    {
        .iv = 0,
        .lvl = 29,
        .species = SPECIES_MACHOP,
    },
    {
        .iv = 0,
        .lvl = 29,
        .species = SPECIES_MACHOKE,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_TeamRocketGrunt31[] = {
    {
        .iv = 0,
        .lvl = 28,
        .species = SPECIES_ZUBAT,
    },
    {
        .iv = 0,
        .lvl = 28,
        .species = SPECIES_ZUBAT,
    },
    {
        .iv = 0,
        .lvl = 28,
        .species = SPECIES_GOLBAT,
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_TeamRocketGrunt32[] = {
    {
        .iv = 0,
        .lvl = 26,
        .species = SPECIES_RATICATE,
        .moves = {MOVE_SCARY_FACE, MOVE_HYPER_FANG, MOVE_QUICK_ATTACK, MOVE_TAIL_WHIP},
    },
    {
        .iv = 0,
        .lvl = 26,
        .species = SPECIES_ARBOK,
        .moves = {MOVE_GLARE, MOVE_BITE, MOVE_POISON_STING, MOVE_LEER},
    },
    {
        .iv = 0,
        .lvl = 26,
        .species = SPECIES_KOFFING,
        .moves = {MOVE_SMOKESCREEN, MOVE_SLUDGE, MOVE_SMOG, MOVE_TACKLE},
    },
    {
        .iv = 0,
        .lvl = 26,
        .species = SPECIES_GOLBAT,
        .moves = {MOVE_WING_ATTACK, MOVE_BITE, MOVE_ASTONISH, MOVE_SUPERSONIC},
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_TeamRocketGrunt33[] = {
    {
        .iv = 0,
        .lvl = 29,
        .species = SPECIES_CUBONE,
    },
    {
        .iv = 0,
        .lvl = 29,
        .species = SPECIES_CUBONE,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_TeamRocketGrunt34[] = {
    {
        .iv = 0,
        .lvl = 29,
        .species = SPECIES_SANDSHREW,
    },
    {
        .iv = 0,
        .lvl = 29,
        .species = SPECIES_SANDSLASH,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_TeamRocketGrunt35[] = {
    {
        .iv = 0,
        .lvl = 26,
        .species = SPECIES_RATICATE,
    },
    {
        .iv = 0,
        .lvl = 26,
        .species = SPECIES_ZUBAT,
    },
    {
        .iv = 0,
        .lvl = 26,
        .species = SPECIES_GOLBAT,
    },
    {
        .iv = 0,
        .lvl = 26,
        .species = SPECIES_RATTATA,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_TeamRocketGrunt36[] = {
    {
        .iv = 0,
        .lvl = 28,
        .species = SPECIES_WEEZING,
    },
    {
        .iv = 0,
        .lvl = 28,
        .species = SPECIES_GOLBAT,
    },
    {
        .iv = 0,
        .lvl = 28,
        .species = SPECIES_KOFFING,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_TeamRocketGrunt37[] = {
    {
        .iv = 0,
        .lvl = 28,
        .species = SPECIES_DROWZEE,
    },
    {
        .iv = 0,
        .lvl = 28,
        .species = SPECIES_GRIMER,
    },
    {
        .iv = 0,
        .lvl = 28,
        .species = SPECIES_MACHOP,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_TeamRocketGrunt38[] = {
    {
        .iv = 0,
        .lvl = 28,
        .species = SPECIES_GOLBAT,
    },
    {
        .iv = 0,
        .lvl = 28,
        .species = SPECIES_DROWZEE,
    },
    {
        .iv = 0,
        .lvl = 28,
        .species = SPECIES_HYPNO,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_TeamRocketGrunt39[] = {
    {
        .iv = 0,
        .lvl = 33,
        .species = SPECIES_MACHOKE,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_TeamRocketGrunt40[] = {
    {
        .iv = 0,
        .lvl = 25,
        .species = SPECIES_RATTATA,
    },
    {
        .iv = 0,
        .lvl = 25,
        .species = SPECIES_RATTATA,
    },
    {
        .iv = 0,
        .lvl = 25,
        .species = SPECIES_ZUBAT,
    },
    {
        .iv = 0,
        .lvl = 25,
        .species = SPECIES_RATTATA,
    },
    {
        .iv = 0,
        .lvl = 25,
        .species = SPECIES_EKANS,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_TeamRocketGrunt41[] = {
    {
        .iv = 0,
        .lvl = 32,
        .species = SPECIES_CUBONE,
    },
    {
        .iv = 0,
        .lvl = 32,
        .species = SPECIES_DROWZEE,
    },
    {
        .iv = 0,
        .lvl = 32,
        .species = SPECIES_MAROWAK,
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_CooltrainerSamuel[] = {
    {
        .iv = 100,
        .lvl = 37,
        .species = SPECIES_SANDSLASH,
        .moves = {MOVE_SLASH, MOVE_SWIFT, MOVE_SAND_ATTACK, MOVE_POISON_STING},
    },
    {
        .iv = 100,
        .lvl = 37,
        .species = SPECIES_SANDSLASH,
        .moves = {MOVE_SLASH, MOVE_SWIFT, MOVE_SAND_ATTACK, MOVE_POISON_STING},
    },
    {
        .iv = 100,
        .lvl = 38,
        .species = SPECIES_RHYHORN,
        .moves = {MOVE_TAKE_DOWN, MOVE_ROCK_BLAST, MOVE_FURY_ATTACK, MOVE_SCARY_FACE},
    },
    {
        .iv = 100,
        .lvl = 39,
        .species = SPECIES_NIDORINO,
        .moves = {MOVE_FURY_ATTACK, MOVE_HORN_ATTACK, MOVE_POISON_STING, MOVE_DOUBLE_KICK},
    },
    {
        .iv = 100,
        .lvl = 39,
        .species = SPECIES_NIDOKING,
        .moves = {MOVE_THRASH, MOVE_DOUBLE_KICK, MOVE_POISON_STING, MOVE_FOCUS_ENERGY},
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_CooltrainerGeorge[] = {
    {
        .iv = 100,
        .lvl = 42,
        .species = SPECIES_EXEGGUTOR,
        .moves = {MOVE_EGG_BOMB, MOVE_CONFUSION, MOVE_STUN_SPORE, MOVE_SLEEP_POWDER},
    },
    {
        .iv = 100,
        .lvl = 42,
        .species = SPECIES_SANDSLASH,
        .moves = {MOVE_FURY_SWIPES, MOVE_SWIFT, MOVE_POISON_STING, MOVE_SAND_ATTACK},
    },
    {
        .iv = 100,
        .lvl = 42,
        .species = SPECIES_CLOYSTER,
        .moves = {MOVE_SPIKE_CANNON, MOVE_SPIKES, MOVE_AURORA_BEAM, MOVE_SUPERSONIC},
    },
    {
        .iv = 100,
        .lvl = 42,
        .species = SPECIES_ELECTRODE,
        .moves = {MOVE_SPARK, MOVE_SONIC_BOOM, MOVE_SCREECH, MOVE_LIGHT_SCREEN},
    },
    {
        .iv = 100,
        .lvl = 42,
        .species = SPECIES_ARCANINE,
        .moves = {MOVE_FLAME_WHEEL, MOVE_ROAR, MOVE_BITE, MOVE_TAKE_DOWN},
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_CooltrainerColby[] = {
    {
        .iv = 100,
        .lvl = 41,
        .species = SPECIES_KINGLER,
        .moves = {MOVE_GUILLOTINE, MOVE_STOMP, MOVE_MUD_SHOT, MOVE_BUBBLE},
    },
    {
        .iv = 100,
        .lvl = 42,
        .species = SPECIES_POLIWHIRL,
        .moves = {MOVE_BODY_SLAM, MOVE_DOUBLE_SLAP, MOVE_WATER_GUN, MOVE_HYPNOSIS},
    },
    {
        .iv = 100,
        .lvl = 42,
        .species = SPECIES_TENTACRUEL,
        .moves = {MOVE_BARRIER, MOVE_WRAP, MOVE_BUBBLE_BEAM, MOVE_ACID},
    },
    {
        .iv = 100,
        .lvl = 42,
        .species = SPECIES_SEADRA,
        .moves = {MOVE_WATER_GUN, MOVE_SMOKESCREEN, MOVE_TWISTER, MOVE_LEER},
    },
    {
        .iv = 100,
        .lvl = 43,
        .species = SPECIES_BLASTOISE,
        .moves = {MOVE_WATER_GUN, MOVE_BITE, MOVE_RAPID_SPIN, MOVE_RAIN_DANCE},
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_CooltrainerPaul[] = {
    {
        .iv = 100,
        .lvl = 42,
        .species = SPECIES_SLOWPOKE,
        .moves = {MOVE_HEADBUTT, MOVE_CONFUSION, MOVE_WATER_GUN, MOVE_DISABLE},
    },
    {
        .iv = 100,
        .lvl = 42,
        .species = SPECIES_SHELLDER,
        .moves = {MOVE_AURORA_BEAM, MOVE_CLAMP, MOVE_SUPERSONIC, MOVE_LEER},
    },
    {
        .iv = 100,
        .lvl = 42,
        .species = SPECIES_KINGLER,
        .moves = {MOVE_GUILLOTINE, MOVE_STOMP, MOVE_MUD_SHOT, MOVE_BUBBLE},
    },
    {
        .iv = 100,
        .lvl = 42,
        .species = SPECIES_STARMIE,
        .moves = {MOVE_BUBBLE_BEAM, MOVE_SWIFT, MOVE_RECOVER, MOVE_RAPID_SPIN},
    },
    {
        .iv = 100,
        .lvl = 42,
        .species = SPECIES_GOLDUCK,
        .moves = {MOVE_CONFUSION, MOVE_SCRATCH, MOVE_SCREECH, MOVE_DISABLE},
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_CooltrainerRolando[] = {
    {
        .iv = 100,
        .lvl = 42,
        .species = SPECIES_RATICATE,
        .moves = {MOVE_SUPER_FANG, MOVE_PURSUIT, MOVE_SCARY_FACE, MOVE_QUICK_ATTACK},
    },
    {
        .iv = 100,
        .lvl = 42,
        .species = SPECIES_IVYSAUR,
        .moves = {MOVE_RAZOR_LEAF, MOVE_SLEEP_POWDER, MOVE_SWEET_SCENT, MOVE_SYNTHESIS},
    },
    {
        .iv = 100,
        .lvl = 42,
        .species = SPECIES_WARTORTLE,
        .moves = {MOVE_WATER_GUN, MOVE_BITE, MOVE_RAPID_SPIN, MOVE_TAIL_WHIP},
    },
    {
        .iv = 100,
        .lvl = 42,
        .species = SPECIES_CHARMELEON,
        .moves = {MOVE_FLAMETHROWER, MOVE_SLASH, MOVE_SMOKESCREEN, MOVE_SCARY_FACE},
    },
    {
        .iv = 100,
        .lvl = 42,
        .species = SPECIES_CHARIZARD,
        .moves = {MOVE_FLAMETHROWER, MOVE_WING_ATTACK, MOVE_SMOKESCREEN, MOVE_SCARY_FACE},
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_CooltrainerGilbert[] = {
    {
        .iv = 100,
        .lvl = 42,
        .species = SPECIES_PIDGEOTTO,
        .moves = {MOVE_WING_ATTACK, MOVE_FEATHER_DANCE, MOVE_WHIRLWIND, MOVE_QUICK_ATTACK},
    },
    {
        .iv = 100,
        .lvl = 42,
        .species = SPECIES_FEAROW,
        .moves = {MOVE_DRILL_PECK, MOVE_MIRROR_MOVE, MOVE_PURSUIT, MOVE_LEER},
    },
    {
        .iv = 100,
        .lvl = 42,
        .species = SPECIES_PERSIAN,
        .moves = {MOVE_PAY_DAY, MOVE_FAINT_ATTACK, MOVE_SCREECH, MOVE_BITE},
    },
    {
        .iv = 100,
        .lvl = 42,
        .species = SPECIES_LICKITUNG,
        .moves = {MOVE_SLAM, MOVE_DISABLE, MOVE_WRAP, MOVE_SUPERSONIC},
    },
    {
        .iv = 100,
        .lvl = 42,
        .species = SPECIES_TAUROS,
        .moves = {MOVE_HORN_ATTACK, MOVE_SCARY_FACE, MOVE_SWAGGER, MOVE_TAIL_WHIP},
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_CooltrainerOwen[] = {
    {
        .iv = 100,
        .lvl = 42,
        .species = SPECIES_NIDORINO,
        .moves = {MOVE_SCRATCH, MOVE_POISON_STING, MOVE_DOUBLE_KICK, MOVE_BITE},
    },
    {
        .iv = 100,
        .lvl = 42,
        .species = SPECIES_NIDORINA,
        .moves = {MOVE_HORN_ATTACK, MOVE_POISON_STING, MOVE_DOUBLE_KICK, MOVE_LEER},
    },
    {
        .iv = 100,
        .lvl = 42,
        .species = SPECIES_RATICATE,
        .moves = {MOVE_SUPER_FANG, MOVE_PURSUIT, MOVE_SCARY_FACE, MOVE_QUICK_ATTACK},
    },
    {
        .iv = 100,
        .lvl = 42,
        .species = SPECIES_SANDSLASH,
        .moves = {MOVE_FURY_SWIPES, MOVE_SWIFT, MOVE_SLASH, MOVE_POISON_STING},
    },
    {
        .iv = 100,
        .lvl = 42,
        .species = SPECIES_RHYHORN,
        .moves = {MOVE_ROCK_BLAST, MOVE_SCARY_FACE, MOVE_STOMP, MOVE_TAIL_WHIP},
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_CooltrainerBerke[] = {
    {
        .iv = 100,
        .lvl = 42,
        .species = SPECIES_SEEL,
        .moves = {MOVE_TAKE_DOWN, MOVE_AURORA_BEAM, MOVE_ICY_WIND, MOVE_GROWL},
    },
    {
        .iv = 100,
        .lvl = 42,
        .species = SPECIES_GRAVELER,
        .moves = {MOVE_ROCK_BLAST, MOVE_MAGNITUDE, MOVE_ROCK_THROW, MOVE_MUD_SPORT},
    },
    {
        .iv = 100,
        .lvl = 42,
        .species = SPECIES_KINGLER,
        .moves = {MOVE_GUILLOTINE, MOVE_STOMP, MOVE_MUD_SHOT, MOVE_BUBBLE},
    },
    {
        .iv = 100,
        .lvl = 42,
        .species = SPECIES_ONIX,
        .moves = {MOVE_SLAM, MOVE_SANDSTORM, MOVE_DRAGON_BREATH, MOVE_ROCK_THROW},
    },
    {
        .iv = 100,
        .lvl = 42,
        .species = SPECIES_CLOYSTER,
        .moves = {MOVE_SPIKE_CANNON, MOVE_AURORA_BEAM, MOVE_SUPERSONIC, MOVE_PROTECT},
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_CooltrainerYuji[] = {
    {
        .iv = 100,
        .lvl = 38,
        .species = SPECIES_SANDSLASH,
        .moves = {MOVE_SLASH, MOVE_SWIFT, MOVE_SAND_ATTACK, MOVE_POISON_STING},
    },
    {
        .iv = 100,
        .lvl = 38,
        .species = SPECIES_GRAVELER,
        .moves = {MOVE_ROCK_BLAST, MOVE_MAGNITUDE, MOVE_MUD_SPORT, MOVE_DEFENSE_CURL},
    },
    {
        .iv = 100,
        .lvl = 38,
        .species = SPECIES_ONIX,
        .moves = {MOVE_DRAGON_BREATH, MOVE_SANDSTORM, MOVE_ROCK_THROW, MOVE_BIND},
    },
    {
        .iv = 100,
        .lvl = 38,
        .species = SPECIES_GRAVELER,
        .moves = {MOVE_ROCK_BLAST, MOVE_MAGNITUDE, MOVE_ROLLOUT, MOVE_DEFENSE_CURL},
    },
    {
        .iv = 100,
        .lvl = 38,
        .species = SPECIES_MAROWAK,
        .moves = {MOVE_BONEMERANG, MOVE_HEADBUTT, MOVE_LEER, MOVE_GROWL},
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_CooltrainerWarren[] = {
    {
        .iv = 100,
        .lvl = 37,
        .species = SPECIES_MAROWAK,
        .moves = {MOVE_BONEMERANG, MOVE_HEADBUTT, MOVE_LEER, MOVE_GROWL},
    },
    {
        .iv = 100,
        .lvl = 37,
        .species = SPECIES_MAROWAK,
        .moves = {MOVE_BONEMERANG, MOVE_HEADBUTT, MOVE_LEER, MOVE_GROWL},
    },
    {
        .iv = 100,
        .lvl = 38,
        .species = SPECIES_RHYHORN,
        .moves = {MOVE_TAKE_DOWN, MOVE_ROCK_BLAST, MOVE_FURY_ATTACK, MOVE_SCARY_FACE},
    },
    {
        .iv = 100,
        .lvl = 39,
        .species = SPECIES_NIDORINA,
        .moves = {MOVE_FURY_SWIPES, MOVE_BITE, MOVE_POISON_STING, MOVE_DOUBLE_KICK},
    },
    {
        .iv = 100,
        .lvl = 39,
        .species = SPECIES_NIDOQUEEN,
        .moves = {MOVE_BODY_SLAM, MOVE_BITE, MOVE_POISON_STING, MOVE_DOUBLE_KICK},
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_CooltrainerMary[] = {
    {
        .iv = 100,
        .lvl = 22,
        .species = SPECIES_BELLSPROUT,
        .moves = {MOVE_WRAP, MOVE_STUN_SPORE, MOVE_POISON_POWDER, MOVE_GROWTH},
    },
    {
        .iv = 100,
        .lvl = 22,
        .species = SPECIES_ODDISH,
        .moves = {MOVE_POISON_POWDER, MOVE_STUN_SPORE, MOVE_ABSORB, MOVE_SWEET_SCENT},
    },
    {
        .iv = 100,
        .lvl = 22,
        .species = SPECIES_WEEPINBELL,
        .moves = {MOVE_VINE_WHIP, MOVE_STUN_SPORE, MOVE_POISON_POWDER, MOVE_GROWTH},
    },
    {
        .iv = 100,
        .lvl = 22,
        .species = SPECIES_GLOOM,
        .moves = {MOVE_ABSORB, MOVE_STUN_SPORE, MOVE_POISON_POWDER, MOVE_SWEET_SCENT},
    },
    {
        .iv = 100,
        .lvl = 22,
        .species = SPECIES_IVYSAUR,
        .moves = {MOVE_RAZOR_LEAF, MOVE_SLEEP_POWDER, MOVE_VINE_WHIP, MOVE_LEECH_SEED},
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_CooltrainerCaroline[] = {
    {
        .iv = 100,
        .lvl = 42,
        .species = SPECIES_BELLSPROUT,
        .moves = {MOVE_RAZOR_LEAF, MOVE_ACID, MOVE_STUN_SPORE, MOVE_POISON_POWDER},
    },
    {
        .iv = 100,
        .lvl = 42,
        .species = SPECIES_WEEPINBELL,
        .moves = {MOVE_RAZOR_LEAF, MOVE_ACID, MOVE_SLEEP_POWDER, MOVE_POISON_POWDER},
    },
    {
        .iv = 100,
        .lvl = 42,
        .species = SPECIES_VICTREEBEL,
        .moves = {MOVE_RAZOR_LEAF, MOVE_ACID, MOVE_STUN_SPORE, MOVE_SLEEP_POWDER},
    },
    {
        .iv = 100,
        .lvl = 42,
        .species = SPECIES_PARAS,
        .moves = {MOVE_GROWTH, MOVE_SLASH, MOVE_LEECH_LIFE, MOVE_STUN_SPORE},
    },
    {
        .iv = 100,
        .lvl = 42,
        .species = SPECIES_PARASECT,
        .moves = {MOVE_SPORE, MOVE_SLASH, MOVE_LEECH_LIFE, MOVE_POISON_POWDER},
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_CooltrainerAlexa[] = {
    {
        .iv = 100,
        .lvl = 42,
        .species = SPECIES_CLEFAIRY,
        .moves = {MOVE_LIGHT_SCREEN, MOVE_COSMIC_POWER, MOVE_DOUBLE_SLAP, MOVE_ENCORE},
    },
    {
        .iv = 100,
        .lvl = 42,
        .species = SPECIES_JIGGLYPUFF,
        .moves = {MOVE_SING, MOVE_BODY_SLAM, MOVE_ROLLOUT, MOVE_DISABLE},
    },
    {
        .iv = 100,
        .lvl = 42,
        .species = SPECIES_PERSIAN,
        .moves = {MOVE_PAY_DAY, MOVE_FAINT_ATTACK, MOVE_BITE, MOVE_SCREECH},
    },
    {
        .iv = 100,
        .lvl = 42,
        .species = SPECIES_DEWGONG,
        .moves = {MOVE_SHEER_COLD, MOVE_TAKE_DOWN, MOVE_REST, MOVE_AURORA_BEAM},
    },
    {
        .iv = 100,
        .lvl = 42,
        .species = SPECIES_CHANSEY,
        .moves = {MOVE_SING, MOVE_EGG_BOMB, MOVE_SOFT_BOILED, MOVE_MINIMIZE},
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_CooltrainerShannon[] = {
    {
        .iv = 100,
        .lvl = 42,
        .species = SPECIES_BEEDRILL,
        .moves = {MOVE_PIN_MISSILE, MOVE_TWINEEDLE, MOVE_AGILITY, MOVE_PURSUIT},
    },
    {
        .iv = 100,
        .lvl = 42,
        .species = SPECIES_BUTTERFREE,
        .moves = {MOVE_SAFEGUARD, MOVE_PSYBEAM, MOVE_GUST, MOVE_SUPERSONIC},
    },
    {
        .iv = 100,
        .lvl = 42,
        .species = SPECIES_PARASECT,
        .moves = {MOVE_SPORE, MOVE_LEECH_LIFE, MOVE_SLASH, MOVE_GROWTH},
    },
    {
        .iv = 100,
        .lvl = 42,
        .species = SPECIES_VENONAT,
        .moves = {MOVE_PSYBEAM, MOVE_STUN_SPORE, MOVE_LEECH_LIFE, MOVE_DISABLE},
    },
    {
        .iv = 100,
        .lvl = 42,
        .species = SPECIES_VENOMOTH,
        .moves = {MOVE_PSYBEAM, MOVE_GUST, MOVE_SUPERSONIC, MOVE_LEECH_LIFE},
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_CooltrainerNaomi[] = {
    {
        .iv = 100,
        .lvl = 42,
        .species = SPECIES_PERSIAN,
        .moves = {MOVE_FURY_SWIPES, MOVE_SCREECH, MOVE_FAINT_ATTACK, MOVE_PAY_DAY},
    },
    {
        .iv = 100,
        .lvl = 42,
        .species = SPECIES_PONYTA,
        .moves = {MOVE_AGILITY, MOVE_TAKE_DOWN, MOVE_FIRE_SPIN, MOVE_STOMP},
    },
    {
        .iv = 100,
        .lvl = 42,
        .species = SPECIES_RAPIDASH,
        .moves = {MOVE_FURY_ATTACK, MOVE_FIRE_SPIN, MOVE_STOMP, MOVE_GROWL},
    },
    {
        .iv = 100,
        .lvl = 42,
        .species = SPECIES_VULPIX,
        .moves = {MOVE_FLAMETHROWER, MOVE_CONFUSE_RAY, MOVE_QUICK_ATTACK, MOVE_IMPRISON},
    },
    {
        .iv = 100,
        .lvl = 42,
        .species = SPECIES_NINETALES,
        .moves = {MOVE_SAFEGUARD, MOVE_WILL_O_WISP, MOVE_CONFUSE_RAY, MOVE_FIRE_SPIN},
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_CooltrainerBrooke[] = {
    {
        .iv = 100,
        .lvl = 42,
        .species = SPECIES_TANGELA,
        .moves = {MOVE_SLAM, MOVE_BIND, MOVE_MEGA_DRAIN, MOVE_INGRAIN},
    },
    {
        .iv = 100,
        .lvl = 42,
        .species = SPECIES_GLOOM,
        .moves = {MOVE_ACID, MOVE_MOONLIGHT, MOVE_SLEEP_POWDER, MOVE_STUN_SPORE},
    },
    {
        .iv = 100,
        .lvl = 42,
        .species = SPECIES_VILEPLUME,
        .moves = {MOVE_MEGA_DRAIN, MOVE_ACID, MOVE_STUN_SPORE, MOVE_AROMATHERAPY},
    },
    {
        .iv = 100,
        .lvl = 42,
        .species = SPECIES_IVYSAUR,
        .moves = {MOVE_RAZOR_LEAF, MOVE_SWEET_SCENT, MOVE_GROWL, MOVE_LEECH_SEED},
    },
    {
        .iv = 100,
        .lvl = 42,
        .species = SPECIES_VENUSAUR,
        .moves = {MOVE_RAZOR_LEAF, MOVE_GROWTH, MOVE_SLEEP_POWDER, MOVE_POISON_POWDER},
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_CooltrainerAustina[] = {
    {
        .iv = 100,
        .lvl = 42,
        .species = SPECIES_RHYHORN,
        .moves = {MOVE_HORN_DRILL, MOVE_ROCK_BLAST, MOVE_SCARY_FACE, MOVE_STOMP},
    },
    {
        .iv = 100,
        .lvl = 42,
        .species = SPECIES_NIDORINA,
        .moves = {MOVE_DOUBLE_KICK, MOVE_FURY_SWIPES, MOVE_BITE, MOVE_FLATTER},
    },
    {
        .iv = 100,
        .lvl = 42,
        .species = SPECIES_NIDOQUEEN,
        .moves = {MOVE_BODY_SLAM, MOVE_DOUBLE_KICK, MOVE_BITE, MOVE_GROWL},
    },
    {
        .iv = 100,
        .lvl = 42,
        .species = SPECIES_NIDORINO,
        .moves = {MOVE_HORN_ATTACK, MOVE_POISON_STING, MOVE_FOCUS_ENERGY, MOVE_LEER},
    },
    {
        .iv = 100,
        .lvl = 42,
        .species = SPECIES_NIDOKING,
        .moves = {MOVE_THRASH, MOVE_DOUBLE_KICK, MOVE_POISON_STING, MOVE_PECK},
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_CooltrainerJulie[] = {
    {
        .iv = 100,
        .lvl = 42,
        .species = SPECIES_PERSIAN,
        .moves = {MOVE_FURY_SWIPES, MOVE_BITE, MOVE_SCREECH, MOVE_FAINT_ATTACK},
    },
    {
        .iv = 100,
        .lvl = 42,
        .species = SPECIES_NINETALES,
        .moves = {MOVE_FLAMETHROWER, MOVE_WILL_O_WISP, MOVE_CONFUSE_RAY, MOVE_GRUDGE},
    },
    {
        .iv = 100,
        .lvl = 42,
        .species = SPECIES_RAPIDASH,
        .moves = {MOVE_FURY_ATTACK, MOVE_FIRE_SPIN, MOVE_TAKE_DOWN, MOVE_AGILITY},
    },
    {
        .iv = 100,
        .lvl = 42,
        .species = SPECIES_PIKACHU,
        .moves = {MOVE_THUNDERBOLT, MOVE_THUNDER_WAVE, MOVE_DOUBLE_TEAM, MOVE_QUICK_ATTACK},
    },
    {
        .iv = 100,
        .lvl = 42,
        .species = SPECIES_RAICHU,
        .moves = {MOVE_THUNDER, MOVE_THUNDER_WAVE, MOVE_SLAM, MOVE_DOUBLE_TEAM},
    },
};

static const struct TrainerMonItemCustomMoves sParty_EliteFourLorelei[] = {
    {
        .iv = 250,
        .lvl = 52,
        .species = SPECIES_DEWGONG,
        .heldItem = ITEM_NONE,
        .moves = {MOVE_ICE_BEAM, MOVE_SURF, MOVE_HAIL, MOVE_SAFEGUARD},
    },
    {
        .iv = 250,
        .lvl = 51,
        .species = SPECIES_CLOYSTER,
        .heldItem = ITEM_NONE,
        .moves = {MOVE_SPIKES, MOVE_PROTECT, MOVE_HAIL, MOVE_DIVE},
    },
    {
        .iv = 250,
        .lvl = 52,
        .species = SPECIES_SLOWBRO,
        .heldItem = ITEM_NONE,
        .moves = {MOVE_ICE_BEAM, MOVE_SURF, MOVE_AMNESIA, MOVE_YAWN},
    },
    {
        .iv = 250,
        .lvl = 54,
        .species = SPECIES_JYNX,
        .heldItem = ITEM_NONE,
        .moves = {MOVE_ICE_PUNCH, MOVE_DOUBLE_SLAP, MOVE_LOVELY_KISS, MOVE_ATTRACT},
    },
    {
        .iv = 250,
        .lvl = 54,
        .species = SPECIES_LAPRAS,
        .heldItem = ITEM_SITRUS_BERRY,
        .moves = {MOVE_CONFUSE_RAY, MOVE_ICE_BEAM, MOVE_SURF, MOVE_BODY_SLAM},
    },
};

static const struct TrainerMonItemCustomMoves sParty_EliteFourBruno[] = {
    {
        .iv = 250,
        .lvl = 51,
        .species = SPECIES_ONIX,
        .heldItem = ITEM_NONE,
        .moves = {MOVE_EARTHQUAKE, MOVE_ROCK_TOMB, MOVE_IRON_TAIL, MOVE_ROAR},
    },
    {
        .iv = 250,
        .lvl = 53,
        .species = SPECIES_HITMONCHAN,
        .heldItem = ITEM_NONE,
        .moves = {MOVE_SKY_UPPERCUT, MOVE_MACH_PUNCH, MOVE_ROCK_TOMB, MOVE_COUNTER},
    },
    {
        .iv = 250,
        .lvl = 53,
        .species = SPECIES_HITMONLEE,
        .heldItem = ITEM_NONE,
        .moves = {MOVE_MEGA_KICK, MOVE_FORESIGHT, MOVE_BRICK_BREAK, MOVE_FACADE},
    },
    {
        .iv = 250,
        .lvl = 54,
        .species = SPECIES_ONIX,
        .heldItem = ITEM_NONE,
        .moves = {MOVE_DOUBLE_EDGE, MOVE_EARTHQUAKE, MOVE_IRON_TAIL, MOVE_SAND_TOMB},
    },
    {
        .iv = 250,
        .lvl = 56,
        .species = SPECIES_MACHAMP,
        .heldItem = ITEM_SITRUS_BERRY,
        .moves = {MOVE_CROSS_CHOP, MOVE_BULK_UP, MOVE_SCARY_FACE, MOVE_ROCK_TOMB},
    },
};

static const struct TrainerMonItemCustomMoves sParty_EliteFourAgatha[] = {
    {
        .iv = 250,
        .lvl = 54,
        .species = SPECIES_GENGAR,
        .heldItem = ITEM_NONE,
        .moves = {MOVE_SHADOW_PUNCH, MOVE_CONFUSE_RAY, MOVE_TOXIC, MOVE_DOUBLE_TEAM},
    },
    {
        .iv = 250,
        .lvl = 54,
        .species = SPECIES_GOLBAT,
        .heldItem = ITEM_NONE,
        .moves = {MOVE_CONFUSE_RAY, MOVE_POISON_FANG, MOVE_AIR_CUTTER, MOVE_BITE},
    },
    {
        .iv = 250,
        .lvl = 53,
        .species = SPECIES_HAUNTER,
        .heldItem = ITEM_NONE,
        .moves = {MOVE_HYPNOSIS, MOVE_DREAM_EATER, MOVE_CURSE, MOVE_MEAN_LOOK},
    },
    {
        .iv = 250,
        .lvl = 56,
        .species = SPECIES_ARBOK,
        .heldItem = ITEM_NONE,
        .moves = {MOVE_SLUDGE_BOMB, MOVE_SCREECH, MOVE_IRON_TAIL, MOVE_BITE},
    },
    {
        .iv = 250,
        .lvl = 58,
        .species = SPECIES_GENGAR,
        .heldItem = ITEM_SITRUS_BERRY,
        .moves = {MOVE_SHADOW_BALL, MOVE_SLUDGE_BOMB, MOVE_HYPNOSIS, MOVE_NIGHTMARE},
    },
};

static const struct TrainerMonItemCustomMoves sParty_EliteFourLance[] = {
    {
        .iv = 250,
        .lvl = 56,
        .species = SPECIES_GYARADOS,
        .heldItem = ITEM_NONE,
        .moves = {MOVE_HYPER_BEAM, MOVE_DRAGON_RAGE, MOVE_TWISTER, MOVE_BITE},
    },
    {
        .iv = 250,
        .lvl = 54,
        .species = SPECIES_DRAGONAIR,
        .heldItem = ITEM_NONE,
        .moves = {MOVE_HYPER_BEAM, MOVE_SAFEGUARD, MOVE_DRAGON_RAGE, MOVE_OUTRAGE},
    },
    {
        .iv = 250,
        .lvl = 54,
        .species = SPECIES_DRAGONAIR,
        .heldItem = ITEM_NONE,
        .moves = {MOVE_HYPER_BEAM, MOVE_SAFEGUARD, MOVE_THUNDER_WAVE, MOVE_OUTRAGE},
    },
    {
        .iv = 250,
        .lvl = 58,
        .species = SPECIES_AERODACTYL,
        .heldItem = ITEM_NONE,
        .moves = {MOVE_HYPER_BEAM, MOVE_ANCIENT_POWER, MOVE_WING_ATTACK, MOVE_SCARY_FACE},
    },
    {
        .iv = 250,
        .lvl = 60,
        .species = SPECIES_DRAGONITE,
        .heldItem = ITEM_SITRUS_BERRY,
        .moves = {MOVE_HYPER_BEAM, MOVE_SAFEGUARD, MOVE_OUTRAGE, MOVE_WING_ATTACK},
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_LeaderBrock[] = {
    {
        .iv = 0,
        .lvl = 12,
        .species = SPECIES_GEODUDE,
        .moves = {MOVE_TACKLE, MOVE_DEFENSE_CURL, MOVE_NONE, MOVE_NONE},
    },
    {
        .iv = 0,
        .lvl = 14,
        .species = SPECIES_ONIX,
        .moves = {MOVE_TACKLE, MOVE_BIND, MOVE_ROCK_TOMB, MOVE_NONE},
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_LeaderMisty[] = {
    {
        .iv = 0,
        .lvl = 18,
        .species = SPECIES_STARYU,
        .moves = {MOVE_TACKLE, MOVE_HARDEN, MOVE_RECOVER, MOVE_WATER_PULSE},
    },
    {
        .iv = 0,
        .lvl = 21,
        .species = SPECIES_STARMIE,
        .moves = {MOVE_SWIFT, MOVE_RECOVER, MOVE_RAPID_SPIN, MOVE_WATER_PULSE},
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_LeaderLtSurge[] = {
    {
        .iv = 0,
        .lvl = 21,
        .species = SPECIES_VOLTORB,
        .moves = {MOVE_SONIC_BOOM, MOVE_TACKLE, MOVE_SCREECH, MOVE_SHOCK_WAVE},
    },
    {
        .iv = 0,
        .lvl = 18,
        .species = SPECIES_PIKACHU,
        .moves = {MOVE_QUICK_ATTACK, MOVE_THUNDER_WAVE, MOVE_DOUBLE_TEAM, MOVE_SHOCK_WAVE},
    },
    {
        .iv = 0,
        .lvl = 24,
        .species = SPECIES_RAICHU,
        .moves = {MOVE_QUICK_ATTACK, MOVE_THUNDER_WAVE, MOVE_DOUBLE_TEAM, MOVE_SHOCK_WAVE},
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_LeaderErika[] = {
    {
        .iv = 0,
        .lvl = 29,
        .species = SPECIES_VICTREEBEL,
        .moves = {MOVE_STUN_SPORE, MOVE_ACID, MOVE_POISON_POWDER, MOVE_GIGA_DRAIN},
    },
    {
        .iv = 0,
        .lvl = 24,
        .species = SPECIES_TANGELA,
        .moves = {MOVE_POISON_POWDER, MOVE_CONSTRICT, MOVE_INGRAIN, MOVE_GIGA_DRAIN},
    },
    {
        .iv = 0,
        .lvl = 29,
        .species = SPECIES_VILEPLUME,
        .moves = {MOVE_SLEEP_POWDER, MOVE_ACID, MOVE_STUN_SPORE, MOVE_GIGA_DRAIN},
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_LeaderKoga[] = {
    {
        .iv = 0,
        .lvl = 37,
        .species = SPECIES_KOFFING,
        .moves = {MOVE_SELF_DESTRUCT, MOVE_SLUDGE, MOVE_SMOKESCREEN, MOVE_TOXIC},
    },
    {
        .iv = 0,
        .lvl = 39,
        .species = SPECIES_MUK,
        .moves = {MOVE_MINIMIZE, MOVE_SLUDGE, MOVE_ACID_ARMOR, MOVE_TOXIC},
    },
    {
        .iv = 0,
        .lvl = 37,
        .species = SPECIES_KOFFING,
        .moves = {MOVE_SELF_DESTRUCT, MOVE_SLUDGE, MOVE_SMOKESCREEN, MOVE_TOXIC},
    },
    {
        .iv = 0,
        .lvl = 43,
        .species = SPECIES_WEEZING,
        .moves = {MOVE_TACKLE, MOVE_SLUDGE, MOVE_SMOKESCREEN, MOVE_TOXIC},
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_LeaderBlaine[] = {
    {
        .iv = 0,
        .lvl = 42,
        .species = SPECIES_GROWLITHE,
        .moves = {MOVE_BITE, MOVE_ROAR, MOVE_TAKE_DOWN, MOVE_FIRE_BLAST},
    },
    {
        .iv = 0,
        .lvl = 40,
        .species = SPECIES_PONYTA,
        .moves = {MOVE_STOMP, MOVE_BOUNCE, MOVE_FIRE_SPIN, MOVE_FIRE_BLAST},
    },
    {
        .iv = 0,
        .lvl = 42,
        .species = SPECIES_RAPIDASH,
        .moves = {MOVE_STOMP, MOVE_BOUNCE, MOVE_FIRE_SPIN, MOVE_FIRE_BLAST},
    },
    {
        .iv = 0,
        .lvl = 47,
        .species = SPECIES_ARCANINE,
        .moves = {MOVE_BITE, MOVE_ROAR, MOVE_TAKE_DOWN, MOVE_FIRE_BLAST},
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_LeaderSabrina[] = {
    {
        .iv = 0,
        .lvl = 38,
        .species = SPECIES_KADABRA,
        .moves = {MOVE_PSYBEAM, MOVE_REFLECT, MOVE_FUTURE_SIGHT, MOVE_CALM_MIND},
    },
    {
        .iv = 0,
        .lvl = 37,
        .species = SPECIES_MR_MIME,
        .moves = {MOVE_BARRIER, MOVE_PSYBEAM, MOVE_BATON_PASS, MOVE_CALM_MIND},
    },
    {
        .iv = 0,
        .lvl = 38,
        .species = SPECIES_VENOMOTH,
        .moves = {MOVE_PSYBEAM, MOVE_GUST, MOVE_LEECH_LIFE, MOVE_SUPERSONIC},
    },
    {
        .iv = 0,
        .lvl = 43,
        .species = SPECIES_ALAKAZAM,
        .moves = {MOVE_PSYCHIC, MOVE_RECOVER, MOVE_FUTURE_SIGHT, MOVE_CALM_MIND},
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_GentlemanThomas[] = {
    {
        .iv = 0,
        .lvl = 18,
        .species = SPECIES_GROWLITHE,
    },
    {
        .iv = 0,
        .lvl = 18,
        .species = SPECIES_GROWLITHE,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_GentlemanArthur[] = {
    {
        .iv = 0,
        .lvl = 19,
        .species = SPECIES_NIDORAN_M,
    },
    {
        .iv = 0,
        .lvl = 19,
        .species = SPECIES_NIDORAN_F,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_GentlemanTucker[] = {
    {
        .iv = 0,
        .lvl = 23,
        .species = SPECIES_PIKACHU,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_GentlemanNorton[] = {
    {
        .iv = 0,
        .lvl = 48,
        .species = SPECIES_PERSIAN,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_GentlemanWalter[] = {
    {
        .iv = 0,
        .lvl = 17,
        .species = SPECIES_GROWLITHE,
    },
    {
        .iv = 0,
        .lvl = 17,
        .species = SPECIES_PONYTA,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_RivalSsAnneSquirtle[] = {
    {
        .iv = 50,
        .lvl = 19,
        .species = SPECIES_PIDGEOTTO,
    },
    {
        .iv = 50,
        .lvl = 16,
        .species = SPECIES_RATICATE,
    },
    {
        .iv = 50,
        .lvl = 18,
        .species = SPECIES_KADABRA,
    },
    {
        .iv = 100,
        .lvl = 20,
        .species = SPECIES_WARTORTLE,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_RivalSsAnneBulbasaur[] = {
    {
        .iv = 50,
        .lvl = 19,
        .species = SPECIES_PIDGEOTTO,
    },
    {
        .iv = 50,
        .lvl = 16,
        .species = SPECIES_RATICATE,
    },
    {
        .iv = 50,
        .lvl = 18,
        .species = SPECIES_KADABRA,
    },
    {
        .iv = 100,
        .lvl = 20,
        .species = SPECIES_IVYSAUR,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_RivalSsAnneCharmander[] = {
    {
        .iv = 50,
        .lvl = 19,
        .species = SPECIES_PIDGEOTTO,
    },
    {
        .iv = 50,
        .lvl = 16,
        .species = SPECIES_RATICATE,
    },
    {
        .iv = 50,
        .lvl = 18,
        .species = SPECIES_KADABRA,
    },
    {
        .iv = 100,
        .lvl = 20,
        .species = SPECIES_CHARMELEON,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_RivalPokemonTowerSquirtle[] = {
    {
        .iv = 100,
        .lvl = 25,
        .species = SPECIES_PIDGEOTTO,
    },
    {
        .iv = 100,
        .lvl = 23,
        .species = SPECIES_GROWLITHE,
    },
    {
        .iv = 100,
        .lvl = 22,
        .species = SPECIES_EXEGGCUTE,
    },
    {
        .iv = 100,
        .lvl = 20,
        .species = SPECIES_KADABRA,
    },
    {
        .iv = 100,
        .lvl = 25,
        .species = SPECIES_WARTORTLE,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_RivalPokemonTowerBulbasaur[] = {
    {
        .iv = 100,
        .lvl = 25,
        .species = SPECIES_PIDGEOTTO,
    },
    {
        .iv = 100,
        .lvl = 23,
        .species = SPECIES_GYARADOS,
    },
    {
        .iv = 100,
        .lvl = 22,
        .species = SPECIES_GROWLITHE,
    },
    {
        .iv = 100,
        .lvl = 20,
        .species = SPECIES_KADABRA,
    },
    {
        .iv = 100,
        .lvl = 25,
        .species = SPECIES_IVYSAUR,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_RivalPokemonTowerCharmander[] = {
    {
        .iv = 100,
        .lvl = 25,
        .species = SPECIES_PIDGEOTTO,
    },
    {
        .iv = 100,
        .lvl = 23,
        .species = SPECIES_EXEGGCUTE,
    },
    {
        .iv = 100,
        .lvl = 22,
        .species = SPECIES_GYARADOS,
    },
    {
        .iv = 100,
        .lvl = 20,
        .species = SPECIES_KADABRA,
    },
    {
        .iv = 100,
        .lvl = 25,
        .species = SPECIES_CHARMELEON,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_RivalSilphSquirtle[] = {
    {
        .iv = 100,
        .lvl = 37,
        .species = SPECIES_PIDGEOT,
    },
    {
        .iv = 100,
        .lvl = 38,
        .species = SPECIES_GROWLITHE,
    },
    {
        .iv = 100,
        .lvl = 35,
        .species = SPECIES_EXEGGCUTE,
    },
    {
        .iv = 100,
        .lvl = 35,
        .species = SPECIES_ALAKAZAM,
    },
    {
        .iv = 150,
        .lvl = 40,
        .species = SPECIES_BLASTOISE,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_RivalSilphBulbasaur[] = {
    {
        .iv = 100,
        .lvl = 37,
        .species = SPECIES_PIDGEOT,
    },
    {
        .iv = 100,
        .lvl = 38,
        .species = SPECIES_GYARADOS,
    },
    {
        .iv = 100,
        .lvl = 35,
        .species = SPECIES_GROWLITHE,
    },
    {
        .iv = 100,
        .lvl = 35,
        .species = SPECIES_ALAKAZAM,
    },
    {
        .iv = 150,
        .lvl = 40,
        .species = SPECIES_VENUSAUR,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_RivalSilphCharmander[] = {
    {
        .iv = 100,
        .lvl = 37,
        .species = SPECIES_PIDGEOT,
    },
    {
        .iv = 100,
        .lvl = 38,
        .species = SPECIES_EXEGGCUTE,
    },
    {
        .iv = 100,
        .lvl = 35,
        .species = SPECIES_GYARADOS,
    },
    {
        .iv = 100,
        .lvl = 35,
        .species = SPECIES_ALAKAZAM,
    },
    {
        .iv = 150,
        .lvl = 40,
        .species = SPECIES_CHARIZARD,
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_RivalRoute22LateSquirtle[] = {
    {
        .iv = 150,
        .lvl = 47,
        .species = SPECIES_PIDGEOT,
        .moves = {MOVE_FEATHER_DANCE, MOVE_WING_ATTACK, MOVE_GUST, MOVE_QUICK_ATTACK},
    },
    {
        .iv = 150,
        .lvl = 45,
        .species = SPECIES_RHYHORN,
        .moves = {MOVE_TAKE_DOWN, MOVE_HORN_DRILL, MOVE_ROCK_BLAST, MOVE_FURY_ATTACK},
    },
    {
        .iv = 150,
        .lvl = 45,
        .species = SPECIES_GROWLITHE,
        .moves = {MOVE_FLAME_WHEEL, MOVE_TAKE_DOWN, MOVE_LEER, MOVE_AGILITY},
    },
    {
        .iv = 150,
        .lvl = 45,
        .species = SPECIES_EXEGGCUTE,
        .moves = {MOVE_SOLAR_BEAM, MOVE_SLEEP_POWDER, MOVE_POISON_POWDER, MOVE_STUN_SPORE},
    },
    {
        .iv = 150,
        .lvl = 47,
        .species = SPECIES_ALAKAZAM,
        .moves = {MOVE_PSYCHIC, MOVE_CALM_MIND, MOVE_FUTURE_SIGHT, MOVE_DISABLE},
    },
    {
        .iv = 250,
        .lvl = 53,
        .species = SPECIES_BLASTOISE,
        .moves = {MOVE_WATER_GUN, MOVE_RAIN_DANCE, MOVE_BITE, MOVE_RAPID_SPIN},
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_RivalRoute22LateBulbasaur[] = {
    {
        .iv = 150,
        .lvl = 47,
        .species = SPECIES_PIDGEOT,
        .moves = {MOVE_FEATHER_DANCE, MOVE_WING_ATTACK, MOVE_GUST, MOVE_QUICK_ATTACK},
    },
    {
        .iv = 150,
        .lvl = 45,
        .species = SPECIES_RHYHORN,
        .moves = {MOVE_TAKE_DOWN, MOVE_HORN_DRILL, MOVE_ROCK_BLAST, MOVE_FURY_ATTACK},
    },
    {
        .iv = 150,
        .lvl = 45,
        .species = SPECIES_GYARADOS,
        .moves = {MOVE_HYDRO_PUMP, MOVE_TWISTER, MOVE_LEER, MOVE_RAIN_DANCE},
    },
    {
        .iv = 150,
        .lvl = 45,
        .species = SPECIES_GROWLITHE,
        .moves = {MOVE_FLAME_WHEEL, MOVE_TAKE_DOWN, MOVE_LEER, MOVE_AGILITY},
    },
    {
        .iv = 150,
        .lvl = 47,
        .species = SPECIES_ALAKAZAM,
        .moves = {MOVE_PSYCHIC, MOVE_CALM_MIND, MOVE_FUTURE_SIGHT, MOVE_DISABLE},
    },
    {
        .iv = 250,
        .lvl = 53,
        .species = SPECIES_VENUSAUR,
        .moves = {MOVE_RAZOR_LEAF, MOVE_SWEET_SCENT, MOVE_GROWTH, MOVE_SYNTHESIS},
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_RivalRoute22LateCharmander[] = {
    {
        .iv = 150,
        .lvl = 47,
        .species = SPECIES_PIDGEOT,
        .moves = {MOVE_FEATHER_DANCE, MOVE_WING_ATTACK, MOVE_GUST, MOVE_QUICK_ATTACK},
    },
    {
        .iv = 150,
        .lvl = 45,
        .species = SPECIES_RHYHORN,
        .moves = {MOVE_TAKE_DOWN, MOVE_HORN_DRILL, MOVE_ROCK_BLAST, MOVE_FURY_ATTACK},
    },
    {
        .iv = 150,
        .lvl = 45,
        .species = SPECIES_EXEGGCUTE,
        .moves = {MOVE_SOLAR_BEAM, MOVE_SLEEP_POWDER, MOVE_POISON_POWDER, MOVE_STUN_SPORE},
    },
    {
        .iv = 150,
        .lvl = 45,
        .species = SPECIES_GYARADOS,
        .moves = {MOVE_HYDRO_PUMP, MOVE_TWISTER, MOVE_LEER, MOVE_RAIN_DANCE},
    },
    {
        .iv = 150,
        .lvl = 47,
        .species = SPECIES_ALAKAZAM,
        .moves = {MOVE_PSYCHIC, MOVE_CALM_MIND, MOVE_FUTURE_SIGHT, MOVE_DISABLE},
    },
    {
        .iv = 250,
        .lvl = 53,
        .species = SPECIES_CHARIZARD,
        .moves = {MOVE_FLAMETHROWER, MOVE_WING_ATTACK, MOVE_SLASH, MOVE_SCARY_FACE},
    },
};

static const struct TrainerMonItemCustomMoves sParty_ChampionFirstSquirtle[] = {
    {
        .iv = 255,
        .lvl = 59,
        .species = SPECIES_PIDGEOT,
        .heldItem = ITEM_NONE,
        .moves = {MOVE_AERIAL_ACE, MOVE_FEATHER_DANCE, MOVE_SAND_ATTACK, MOVE_WHIRLWIND},
    },
    {
        .iv = 255,
        .lvl = 57,
        .species = SPECIES_ALAKAZAM,
        .heldItem = ITEM_NONE,
        .moves = {MOVE_PSYCHIC, MOVE_FUTURE_SIGHT, MOVE_RECOVER, MOVE_REFLECT},
    },
    {
        .iv = 255,
        .lvl = 59,
        .species = SPECIES_RHYDON,
        .heldItem = ITEM_NONE,
        .moves = {MOVE_TAKE_DOWN, MOVE_EARTHQUAKE, MOVE_ROCK_TOMB, MOVE_SCARY_FACE},
    },
    {
        .iv = 255,
        .lvl = 59,
        .species = SPECIES_ARCANINE,
        .heldItem = ITEM_NONE,
        .moves = {MOVE_EXTREME_SPEED, MOVE_FLAMETHROWER, MOVE_ROAR, MOVE_BITE},
    },
    {
        .iv = 255,
        .lvl = 61,
        .species = SPECIES_EXEGGUTOR,
        .heldItem = ITEM_NONE,
        .moves = {MOVE_GIGA_DRAIN, MOVE_EGG_BOMB, MOVE_SLEEP_POWDER, MOVE_LIGHT_SCREEN},
    },
    {
        .iv = 255,
        .lvl = 63,
        .species = SPECIES_BLASTOISE,
        .heldItem = ITEM_SITRUS_BERRY,
        .moves = {MOVE_HYDRO_PUMP, MOVE_RAIN_DANCE, MOVE_SKULL_BASH, MOVE_BITE},
    },
};

static const struct TrainerMonItemCustomMoves sParty_ChampionFirstBulbasaur[] = {
    {
        .iv = 255,
        .lvl = 59,
        .species = SPECIES_PIDGEOT,
        .heldItem = ITEM_NONE,
        .moves = {MOVE_AERIAL_ACE, MOVE_FEATHER_DANCE, MOVE_SAND_ATTACK, MOVE_WHIRLWIND},
    },
    {
        .iv = 255,
        .lvl = 57,
        .species = SPECIES_ALAKAZAM,
        .heldItem = ITEM_NONE,
        .moves = {MOVE_PSYCHIC, MOVE_FUTURE_SIGHT, MOVE_RECOVER, MOVE_REFLECT},
    },
    {
        .iv = 255,
        .lvl = 59,
        .species = SPECIES_RHYDON,
        .heldItem = ITEM_NONE,
        .moves = {MOVE_TAKE_DOWN, MOVE_EARTHQUAKE, MOVE_ROCK_TOMB, MOVE_SCARY_FACE},
    },
    {
        .iv = 255,
        .lvl = 59,
        .species = SPECIES_GYARADOS,
        .heldItem = ITEM_NONE,
        .moves = {MOVE_HYDRO_PUMP, MOVE_DRAGON_RAGE, MOVE_BITE, MOVE_THRASH},
    },
    {
        .iv = 255,
        .lvl = 61,
        .species = SPECIES_ARCANINE,
        .heldItem = ITEM_NONE,
        .moves = {MOVE_EXTREME_SPEED, MOVE_FLAMETHROWER, MOVE_ROAR, MOVE_BITE},
    },
    {
        .iv = 255,
        .lvl = 63,
        .species = SPECIES_VENUSAUR,
        .heldItem = ITEM_SITRUS_BERRY,
        .moves = {MOVE_SOLAR_BEAM, MOVE_SYNTHESIS, MOVE_SUNNY_DAY, MOVE_GROWTH},
    },
};

static const struct TrainerMonItemCustomMoves sParty_ChampionFirstCharmander[] = {
    {
        .iv = 255,
        .lvl = 59,
        .species = SPECIES_PIDGEOT,
        .heldItem = ITEM_NONE,
        .moves = {MOVE_AERIAL_ACE, MOVE_FEATHER_DANCE, MOVE_SAND_ATTACK, MOVE_WHIRLWIND},
    },
    {
        .iv = 255,
        .lvl = 57,
        .species = SPECIES_ALAKAZAM,
        .heldItem = ITEM_NONE,
        .moves = {MOVE_PSYCHIC, MOVE_FUTURE_SIGHT, MOVE_RECOVER, MOVE_REFLECT},
    },
    {
        .iv = 255,
        .lvl = 59,
        .species = SPECIES_RHYDON,
        .heldItem = ITEM_NONE,
        .moves = {MOVE_TAKE_DOWN, MOVE_EARTHQUAKE, MOVE_ROCK_TOMB, MOVE_SCARY_FACE},
    },
    {
        .iv = 255,
        .lvl = 59,
        .species = SPECIES_EXEGGUTOR,
        .heldItem = ITEM_NONE,
        .moves = {MOVE_GIGA_DRAIN, MOVE_EGG_BOMB, MOVE_SLEEP_POWDER, MOVE_LIGHT_SCREEN},
    },
    {
        .iv = 255,
        .lvl = 61,
        .species = SPECIES_GYARADOS,
        .heldItem = ITEM_NONE,
        .moves = {MOVE_HYDRO_PUMP, MOVE_DRAGON_RAGE, MOVE_BITE, MOVE_THRASH},
    },
    {
        .iv = 255,
        .lvl = 63,
        .species = SPECIES_CHARIZARD,
        .heldItem = ITEM_SITRUS_BERRY,
        .moves = {MOVE_FIRE_BLAST, MOVE_AERIAL_ACE, MOVE_SLASH, MOVE_FIRE_SPIN},
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_ChannelerPatricia[] = {
    {
        .iv = 0,
        .lvl = 22,
        .species = SPECIES_GASTLY,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_ChannelerCarly[] = {
    {
        .iv = 0,
        .lvl = 24,
        .species = SPECIES_GASTLY,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_ChannelerHope[] = {
    {
        .iv = 0,
        .lvl = 23,
        .species = SPECIES_GASTLY,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_ChannelerPaula[] = {
    {
        .iv = 0,
        .lvl = 24,
        .species = SPECIES_GASTLY,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_ChannelerLaurel[] = {
    {
        .iv = 0,
        .lvl = 23,
        .species = SPECIES_GASTLY,
    },
    {
        .iv = 0,
        .lvl = 23,
        .species = SPECIES_GASTLY,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_ChannelerJody[] = {
    {
        .iv = 0,
        .lvl = 22,
        .species = SPECIES_GASTLY,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_ChannelerTammy[] = {
    {
        .iv = 0,
        .lvl = 23,
        .species = SPECIES_HAUNTER,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_ChannelerRuth[] = {
    {
        .iv = 0,
        .lvl = 22,
        .species = SPECIES_GASTLY,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_ChannelerKarina[] = {
    {
        .iv = 0,
        .lvl = 24,
        .species = SPECIES_GASTLY,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_ChannelerJanae[] = {
    {
        .iv = 0,
        .lvl = 22,
        .species = SPECIES_GASTLY,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_ChannelerAngelica[] = {
    {
        .iv = 0,
        .lvl = 22,
        .species = SPECIES_GASTLY,
    },
    {
        .iv = 0,
        .lvl = 22,
        .species = SPECIES_GASTLY,
    },
    {
        .iv = 0,
        .lvl = 22,
        .species = SPECIES_GASTLY,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_ChannelerEmilia[] = {
    {
        .iv = 0,
        .lvl = 24,
        .species = SPECIES_GASTLY,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_ChannelerJennifer[] = {
    {
        .iv = 0,
        .lvl = 24,
        .species = SPECIES_GASTLY,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_Channeler1[] = {
    {
        .iv = 0,
        .lvl = 23,
        .species = SPECIES_HAUNTER,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_Channeler2[] = {
    {
        .iv = 0,
        .lvl = 24,
        .species = SPECIES_GASTLY,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_Channeler3[] = {
    {
        .iv = 0,
        .lvl = 22,
        .species = SPECIES_GASTLY,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_Channeler4[] = {
    {
        .iv = 0,
        .lvl = 24,
        .species = SPECIES_GASTLY,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_Channeler5[] = {
    {
        .iv = 0,
        .lvl = 22,
        .species = SPECIES_HAUNTER,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_Channeler6[] = {
    {
        .iv = 0,
        .lvl = 22,
        .species = SPECIES_GASTLY,
    },
    {
        .iv = 0,
        .lvl = 22,
        .species = SPECIES_GASTLY,
    },
    {
        .iv = 0,
        .lvl = 22,
        .species = SPECIES_GASTLY,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_Channeler7[] = {
    {
        .iv = 0,
        .lvl = 24,
        .species = SPECIES_GASTLY,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_Channeler8[] = {
    {
        .iv = 0,
        .lvl = 24,
        .species = SPECIES_GASTLY,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_ChannelerAmanda[] = {
    {
        .iv = 0,
        .lvl = 34,
        .species = SPECIES_GASTLY,
    },
    {
        .iv = 0,
        .lvl = 34,
        .species = SPECIES_HAUNTER,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_ChannelerStacy[] = {
    {
        .iv = 0,
        .lvl = 38,
        .species = SPECIES_HAUNTER,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_ChannelerTasha[] = {
    {
        .iv = 0,
        .lvl = 33,
        .species = SPECIES_GASTLY,
    },
    {
        .iv = 0,
        .lvl = 33,
        .species = SPECIES_GASTLY,
    },
    {
        .iv = 0,
        .lvl = 33,
        .species = SPECIES_HAUNTER,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_HikerJeremy[] = {
    {
        .iv = 0,
        .lvl = 20,
        .species = SPECIES_MACHOP,
    },
    {
        .iv = 0,
        .lvl = 20,
        .species = SPECIES_ONIX,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_PicnickerAlma[] = {
    {
        .iv = 0,
        .lvl = 28,
        .species = SPECIES_GOLDEEN,
    },
    {
        .iv = 0,
        .lvl = 28,
        .species = SPECIES_POLIWAG,
    },
    {
        .iv = 0,
        .lvl = 28,
        .species = SPECIES_HORSEA,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_PicnickerSusie[] = {
    {
        .iv = 0,
        .lvl = 24,
        .species = SPECIES_PIDGEY,
    },
    {
        .iv = 0,
        .lvl = 24,
        .species = SPECIES_MEOWTH,
    },
    {
        .iv = 0,
        .lvl = 24,
        .species = SPECIES_RATTATA,
    },
    {
        .iv = 0,
        .lvl = 24,
        .species = SPECIES_PIKACHU,
    },
    {
        .iv = 0,
        .lvl = 24,
        .species = SPECIES_MEOWTH,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_PicnickerValerie[] = {
    {
        .iv = 0,
        .lvl = 30,
        .species = SPECIES_POLIWAG,
    },
    {
        .iv = 0,
        .lvl = 30,
        .species = SPECIES_POLIWAG,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_PicnickerGwen[] = {
    {
        .iv = 0,
        .lvl = 27,
        .species = SPECIES_PIDGEY,
    },
    {
        .iv = 0,
        .lvl = 27,
        .species = SPECIES_MEOWTH,
    },
    {
        .iv = 0,
        .lvl = 27,
        .species = SPECIES_PIDGEY,
    },
    {
        .iv = 0,
        .lvl = 27,
        .species = SPECIES_PIDGEOTTO,
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_BikerVirgil[] = {
    {
        .iv = 0,
        .lvl = 28,
        .species = SPECIES_WEEZING,
        .moves = {MOVE_SMOKESCREEN, MOVE_SLUDGE, MOVE_SMOG, MOVE_TACKLE},
    },
    {
        .iv = 0,
        .lvl = 28,
        .species = SPECIES_KOFFING,
        .moves = {MOVE_SMOKESCREEN, MOVE_SLUDGE, MOVE_SMOG, MOVE_TACKLE},
    },
    {
        .iv = 0,
        .lvl = 28,
        .species = SPECIES_WEEZING,
        .moves = {MOVE_SMOKESCREEN, MOVE_SLUDGE, MOVE_SMOG, MOVE_TACKLE},
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_CamperFlint[] = {
    {
        .iv = 0,
        .lvl = 14,
        .species = SPECIES_RATTATA,
    },
    {
        .iv = 0,
        .lvl = 14,
        .species = SPECIES_EKANS,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_PicnickerMissy[] = {
    {
        .iv = 0,
        .lvl = 31,
        .species = SPECIES_GOLDEEN,
    },
    {
        .iv = 0,
        .lvl = 31,
        .species = SPECIES_SEAKING,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_PicnickerIrene[] = {
    {
        .iv = 0,
        .lvl = 30,
        .species = SPECIES_TENTACOOL,
    },
    {
        .iv = 0,
        .lvl = 30,
        .species = SPECIES_HORSEA,
    },
    {
        .iv = 0,
        .lvl = 30,
        .species = SPECIES_SEEL,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_PicnickerDana[] = {
    {
        .iv = 0,
        .lvl = 20,
        .species = SPECIES_MEOWTH,
    },
    {
        .iv = 0,
        .lvl = 20,
        .species = SPECIES_ODDISH,
    },
    {
        .iv = 0,
        .lvl = 20,
        .species = SPECIES_PIDGEY,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_PicnickerAriana[] = {
    {
        .iv = 0,
        .lvl = 19,
        .species = SPECIES_PIDGEY,
    },
    {
        .iv = 0,
        .lvl = 19,
        .species = SPECIES_RATTATA,
    },
    {
        .iv = 0,
        .lvl = 19,
        .species = SPECIES_RATTATA,
    },
    {
        .iv = 0,
        .lvl = 19,
        .species = SPECIES_BELLSPROUT,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_PicnickerLeah[] = {
    {
        .iv = 0,
        .lvl = 22,
        .species = SPECIES_BELLSPROUT,
    },
    {
        .iv = 0,
        .lvl = 22,
        .species = SPECIES_CLEFAIRY,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_CamperJustin[] = {
    {
        .iv = 0,
        .lvl = 29,
        .species = SPECIES_NIDORAN_M,
    },
    {
        .iv = 0,
        .lvl = 29,
        .species = SPECIES_NIDORINO,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_PicnickerYazmin[] = {
    {
        .iv = 0,
        .lvl = 29,
        .species = SPECIES_BELLSPROUT,
    },
    {
        .iv = 0,
        .lvl = 29,
        .species = SPECIES_ODDISH,
    },
    {
        .iv = 0,
        .lvl = 29,
        .species = SPECIES_TANGELA,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_PicnickerKindra[] = {
    {
        .iv = 0,
        .lvl = 28,
        .species = SPECIES_GLOOM,
    },
    {
        .iv = 0,
        .lvl = 28,
        .species = SPECIES_ODDISH,
    },
    {
        .iv = 0,
        .lvl = 28,
        .species = SPECIES_ODDISH,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_PicnickerBecky[] = {
    {
        .iv = 0,
        .lvl = 29,
        .species = SPECIES_PIKACHU,
    },
    {
        .iv = 0,
        .lvl = 29,
        .species = SPECIES_RAICHU,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_PicnickerCelia[] = {
    {
        .iv = 0,
        .lvl = 33,
        .species = SPECIES_CLEFAIRY,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_GentlemanBrooks[] = {
    {
        .iv = 0,
        .lvl = 23,
        .species = SPECIES_PIKACHU,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_GentlemanLamar[] = {
    {
        .iv = 0,
        .lvl = 17,
        .species = SPECIES_GROWLITHE,
    },
    {
        .iv = 0,
        .lvl = 17,
        .species = SPECIES_PONYTA,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_TwinsEliAnne[] = {
    {
        .iv = 0,
        .lvl = 22,
        .species = SPECIES_CLEFAIRY,
    },
    {
        .iv = 0,
        .lvl = 22,
        .species = SPECIES_JIGGLYPUFF,
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_CoolCoupleRayTyra[] = {
    {
        .iv = 100,
        .lvl = 45,
        .species = SPECIES_NIDOQUEEN,
        .moves = {MOVE_SUPERPOWER, MOVE_BODY_SLAM, MOVE_DOUBLE_KICK, MOVE_POISON_STING},
    },
    {
        .iv = 100,
        .lvl = 45,
        .species = SPECIES_NIDOKING,
        .moves = {MOVE_MEGAHORN, MOVE_THRASH, MOVE_DOUBLE_KICK, MOVE_POISON_STING},
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_YoungCoupleGiaJes[] = {
    {
        .iv = 0,
        .lvl = 24,
        .species = SPECIES_NIDORAN_M,
    },
    {
        .iv = 0,
        .lvl = 24,
        .species = SPECIES_NIDORAN_F,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_TwinsKiriJan[] = {
    {
        .iv = 0,
        .lvl = 29,
        .species = SPECIES_CHARMANDER,
    },
    {
        .iv = 0,
        .lvl = 29,
        .species = SPECIES_SQUIRTLE,
    },
};

static const struct TrainerMonItemDefaultMoves sParty_CrushKinRonMya[] = {
    {
        .iv = 50,
        .lvl = 29,
        .species = SPECIES_HITMONCHAN,
        .heldItem = ITEM_BLACK_BELT,
    },
    {
        .iv = 50,
        .lvl = 29,
        .species = SPECIES_HITMONLEE,
        .heldItem = ITEM_BLACK_BELT,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_YoungCoupleLeaJed[] = {
    {
        .iv = 0,
        .lvl = 29,
        .species = SPECIES_RAPIDASH,
    },
    {
        .iv = 0,
        .lvl = 29,
        .species = SPECIES_NINETALES,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_SisAndBroLiaLuc[] = {
    {
        .iv = 0,
        .lvl = 30,
        .species = SPECIES_GOLDEEN,
    },
    {
        .iv = 0,
        .lvl = 30,
        .species = SPECIES_SEAKING,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_SisAndBroLilIan[] = {
    {
        .iv = 0,
        .lvl = 33,
        .species = SPECIES_SEADRA,
    },
    {
        .iv = 0,
        .lvl = 33,
        .species = SPECIES_STARMIE,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_BugCatcher3[] = {DUMMY_TRAINER_MON};
static const struct TrainerMonNoItemDefaultMoves sParty_BugCatcher4[] = {DUMMY_TRAINER_MON};
static const struct TrainerMonNoItemDefaultMoves sParty_BugCatcher5[] = {DUMMY_TRAINER_MON};
static const struct TrainerMonNoItemDefaultMoves sParty_BugCatcher6[] = {DUMMY_TRAINER_MON};
static const struct TrainerMonNoItemDefaultMoves sParty_BugCatcher7[] = {DUMMY_TRAINER_MON};
static const struct TrainerMonNoItemDefaultMoves sParty_BugCatcher8[] = {DUMMY_TRAINER_MON};

static const struct TrainerMonNoItemDefaultMoves sParty_YoungsterBen3[] = {
    {
        .iv = 60,
        .lvl = 28,
        .species = SPECIES_RATICATE,
    },
    {
        .iv = 60,
        .lvl = 28,
        .species = SPECIES_EKANS,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_YoungsterBen4[] = {
    {
        .iv = 120,
        .lvl = 48,
        .species = SPECIES_RATICATE,
    },
    {
        .iv = 120,
        .lvl = 48,
        .species = SPECIES_ARBOK,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_YoungsterChad2[] = {
    {
        .iv = 20,
        .lvl = 20,
        .species = SPECIES_EKANS,
    },
    {
        .iv = 20,
        .lvl = 20,
        .species = SPECIES_SANDSHREW,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_LassReli2[] = {
    {
        .iv = 20,
        .lvl = 20,
        .species = SPECIES_PIDGEY,
    },
    {
        .iv = 20,
        .lvl = 20,
        .species = SPECIES_NIDORAN_F,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_LassReli3[] = {
    {
        .iv = 60,
        .lvl = 28,
        .species = SPECIES_PIDGEOTTO,
    },
    {
        .iv = 60,
        .lvl = 28,
        .species = SPECIES_NIDORINA,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_YoungsterTimmy2[] = {
    {
        .iv = 20,
        .lvl = 19,
        .species = SPECIES_RATICATE,
    },
    {
        .iv = 20,
        .lvl = 19,
        .species = SPECIES_EKANS,
    },
    {
        .iv = 20,
        .lvl = 19,
        .species = SPECIES_ZUBAT,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_YoungsterTimmy3[] = {
    {
        .iv = 60,
        .lvl = 27,
        .species = SPECIES_RATICATE,
    },
    {
        .iv = 60,
        .lvl = 27,
        .species = SPECIES_EKANS,
    },
    {
        .iv = 60,
        .lvl = 27,
        .species = SPECIES_GOLBAT,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_YoungsterTimmy4[] = {
    {
        .iv = 120,
        .lvl = 52,
        .species = SPECIES_RATICATE,
    },
    {
        .iv = 120,
        .lvl = 52,
        .species = SPECIES_ARBOK,
    },
    {
        .iv = 120,
        .lvl = 52,
        .species = SPECIES_GOLBAT,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_YoungsterChad3[] = {
    {
        .iv = 60,
        .lvl = 28,
        .species = SPECIES_ARBOK,
    },
    {
        .iv = 60,
        .lvl = 28,
        .species = SPECIES_SANDSHREW,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_LassJanice2[] = {
    {
        .iv = 20,
        .lvl = 20,
        .species = SPECIES_PIDGEOTTO,
    },
    {
        .iv = 20,
        .lvl = 20,
        .species = SPECIES_PIDGEOTTO,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_LassJanice3[] = {
    {
        .iv = 60,
        .lvl = 28,
        .species = SPECIES_PIDGEOTTO,
    },
    {
        .iv = 60,
        .lvl = 28,
        .species = SPECIES_PIDGEOTTO,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_YoungsterChad4[] = {
    {
        .iv = 80,
        .lvl = 48,
        .species = SPECIES_ARBOK,
    },
    {
        .iv = 80,
        .lvl = 48,
        .species = SPECIES_SANDSLASH,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_HikerFranklin2[] = {
    {
        .iv = 40,
        .lvl = 25,
        .species = SPECIES_MACHOKE,
    },
    {
        .iv = 40,
        .lvl = 25,
        .species = SPECIES_GRAVELER,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_PkmnProfProfOak[] = {DUMMY_TRAINER_MON};
static const struct TrainerMonNoItemDefaultMoves sParty_PlayerBrendan[] = {DUMMY_TRAINER_MON};
static const struct TrainerMonNoItemDefaultMoves sParty_PlayerMay[] = {DUMMY_TRAINER_MON};
static const struct TrainerMonNoItemDefaultMoves sParty_PlayerRed[] = {DUMMY_TRAINER_MON};
static const struct TrainerMonNoItemDefaultMoves sParty_PlayerLeaf[] = {DUMMY_TRAINER_MON};

static const struct TrainerMonNoItemDefaultMoves sParty_TeamRocketGrunt42[] = {
    {
        .iv = 0,
        .lvl = 49,
        .species = SPECIES_HOUNDOUR,
    },
    {
        .iv = 0,
        .lvl = 49,
        .species = SPECIES_HOUNDOUR,
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_PsychicJaclyn[] = {
    {
        .iv = 100,
        .lvl = 48,
        .species = SPECIES_NATU,
        .moves = {MOVE_NIGHT_SHADE, MOVE_CONFUSE_RAY, MOVE_FUTURE_SIGHT, MOVE_WISH},
    },
    {
        .iv = 100,
        .lvl = 48,
        .species = SPECIES_SLOWBRO,
        .moves = {MOVE_PSYCHIC, MOVE_HEADBUTT, MOVE_AMNESIA, MOVE_YAWN},
    },
    {
        .iv = 100,
        .lvl = 49,
        .species = SPECIES_KADABRA,
        .moves = {MOVE_PSYCHIC, MOVE_FUTURE_SIGHT, MOVE_RECOVER, MOVE_REFLECT},
    },
};

static const struct TrainerMonItemDefaultMoves sParty_CrushGirlSharon[] = {
    {
        .iv = 50,
        .lvl = 37,
        .species = SPECIES_MANKEY,
        .heldItem = ITEM_BLACK_BELT,
    },
    {
        .iv = 50,
        .lvl = 37,
        .species = SPECIES_PRIMEAPE,
        .heldItem = ITEM_BLACK_BELT,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_TuberAmira[] = {
    {
        .iv = 0,
        .lvl = 34,
        .species = SPECIES_POLIWAG,
    },
    {
        .iv = 0,
        .lvl = 35,
        .species = SPECIES_POLIWHIRL,
    },
    {
        .iv = 0,
        .lvl = 34,
        .species = SPECIES_POLIWAG,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_PkmnBreederAlize[] = {
    {
        .iv = 30,
        .lvl = 48,
        .species = SPECIES_PIKACHU,
    },
    {
        .iv = 30,
        .lvl = 48,
        .species = SPECIES_CLEFAIRY,
    },
    {
        .iv = 30,
        .lvl = 48,
        .species = SPECIES_MARILL,
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_PkmnRangerNicolas[] = {
    {
        .iv = 100,
        .lvl = 51,
        .species = SPECIES_WEEPINBELL,
        .moves = {MOVE_RAZOR_LEAF, MOVE_ACID, MOVE_SWEET_SCENT, MOVE_WRAP},
    },
    {
        .iv = 100,
        .lvl = 51,
        .species = SPECIES_VICTREEBEL,
        .moves = {MOVE_RAZOR_LEAF, MOVE_ACID, MOVE_SLEEP_POWDER, MOVE_STUN_SPORE},
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_PkmnRangerMadeline[] = {
    {
        .iv = 100,
        .lvl = 51,
        .species = SPECIES_GLOOM,
        .moves = {MOVE_PETAL_DANCE, MOVE_ACID, MOVE_SWEET_SCENT, MOVE_POISON_POWDER},
    },
    {
        .iv = 100,
        .lvl = 51,
        .species = SPECIES_VILEPLUME,
        .moves = {MOVE_PETAL_DANCE, MOVE_MOONLIGHT, MOVE_ACID, MOVE_STUN_SPORE},
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_AromaLadyNikki[] = {
    {
        .iv = 0,
        .lvl = 37,
        .species = SPECIES_BELLSPROUT,
    },
    {
        .iv = 0,
        .lvl = 37,
        .species = SPECIES_WEEPINBELL,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_RuinManiacStanly[] = {
    {
        .iv = 0,
        .lvl = 48,
        .species = SPECIES_GRAVELER,
    },
    {
        .iv = 0,
        .lvl = 48,
        .species = SPECIES_ONIX,
    },
    {
        .iv = 0,
        .lvl = 48,
        .species = SPECIES_GRAVELER,
    },
};

static const struct TrainerMonItemDefaultMoves sParty_LadyJacki[] = {
    {
        .iv = 0,
        .lvl = 48,
        .species = SPECIES_HOPPIP,
        .heldItem = ITEM_STARDUST,
    },
    {
        .iv = 0,
        .lvl = 50,
        .species = SPECIES_SKIPLOOM,
        .heldItem = ITEM_STARDUST,
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_PainterDaisy[] = {
    {
        .iv = 50,
        .lvl = 50,
        .species = SPECIES_SMEARGLE,
        .moves = {MOVE_DYNAMIC_PUNCH, MOVE_DIZZY_PUNCH, MOVE_FOCUS_PUNCH, MOVE_MEGA_PUNCH},
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_BikerGoon[] = {
    {
        .iv = 0,
        .lvl = 37,
        .species = SPECIES_KOFFING,
        .moves = {MOVE_HAZE, MOVE_SMOKESCREEN, MOVE_SLUDGE, MOVE_TACKLE},
    },
    {
        .iv = 0,
        .lvl = 37,
        .species = SPECIES_GRIMER,
        .moves = {MOVE_ACID_ARMOR, MOVE_SCREECH, MOVE_MINIMIZE, MOVE_SLUDGE},
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_BikerGoon2[] = {
    {
        .iv = 0,
        .lvl = 38,
        .species = SPECIES_KOFFING,
        .moves = {MOVE_HAZE, MOVE_SMOKESCREEN, MOVE_SLUDGE, MOVE_TACKLE},
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_BikerGoon3[] = {
    {
        .iv = 0,
        .lvl = 38,
        .species = SPECIES_GRIMER,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_Biker2[] = {DUMMY_TRAINER_MON};

static const struct TrainerMonNoItemDefaultMoves sParty_BugCatcherAnthony[] = {
    {
        .iv = 0,
        .lvl = 7,
        .species = SPECIES_CATERPIE,
    },
    {
        .iv = 0,
        .lvl = 8,
        .species = SPECIES_CATERPIE,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_BugCatcherCharlie[] = {
    {
        .iv = 0,
        .lvl = 7,
        .species = SPECIES_METAPOD,
    },
    {
        .iv = 0,
        .lvl = 7,
        .species = SPECIES_CATERPIE,
    },
    {
        .iv = 0,
        .lvl = 7,
        .species = SPECIES_METAPOD,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_TwinsEliAnne2[] = {
    {
        .iv = 60,
        .lvl = 28,
        .species = SPECIES_CLEFAIRY,
    },
    {
        .iv = 60,
        .lvl = 28,
        .species = SPECIES_JIGGLYPUFF,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_YoungsterJohnson[] = {
    {
        .iv = 0,
        .lvl = 33,
        .species = SPECIES_EKANS,
    },
    {
        .iv = 0,
        .lvl = 33,
        .species = SPECIES_EKANS,
    },
    {
        .iv = 0,
        .lvl = 34,
        .species = SPECIES_RATICATE,
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_BikerRicardo[] = {
    {
        .iv = 0,
        .lvl = 22,
        .species = SPECIES_KOFFING,
        .moves = {MOVE_SLUDGE, MOVE_SMOG, MOVE_TACKLE, MOVE_POISON_GAS},
    },
    {
        .iv = 0,
        .lvl = 22,
        .species = SPECIES_KOFFING,
        .moves = {MOVE_SLUDGE, MOVE_SMOG, MOVE_TACKLE, MOVE_POISON_GAS},
    },
    {
        .iv = 0,
        .lvl = 23,
        .species = SPECIES_GRIMER,
        .moves = {MOVE_MINIMIZE, MOVE_SLUDGE, MOVE_DISABLE, MOVE_POUND},
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_BikerJaren[] = {
    {
        .iv = 0,
        .lvl = 24,
        .species = SPECIES_GRIMER,
    },
    {
        .iv = 0,
        .lvl = 24,
        .species = SPECIES_GRIMER,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_TeamRocketGrunt43[] = {
    {
        .iv = 0,
        .lvl = 37,
        .species = SPECIES_CUBONE,
    },
    {
        .iv = 0,
        .lvl = 37,
        .species = SPECIES_MAROWAK,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_TeamRocketGrunt44[] = {
    {
        .iv = 0,
        .lvl = 35,
        .species = SPECIES_RATTATA,
    },
    {
        .iv = 0,
        .lvl = 35,
        .species = SPECIES_RATICATE,
    },
    {
        .iv = 0,
        .lvl = 35,
        .species = SPECIES_SANDSHREW,
    },
    {
        .iv = 0,
        .lvl = 35,
        .species = SPECIES_SANDSLASH,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_TeamRocketGrunt45[] = {
    {
        .iv = 0,
        .lvl = 38,
        .species = SPECIES_ZUBAT,
    },
    {
        .iv = 0,
        .lvl = 38,
        .species = SPECIES_ZUBAT,
    },
    {
        .iv = 0,
        .lvl = 38,
        .species = SPECIES_GOLBAT,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_TeamRocketGrunt46[] = {
    {
        .iv = 0,
        .lvl = 48,
        .species = SPECIES_MUK,
    },
    {
        .iv = 0,
        .lvl = 48,
        .species = SPECIES_GOLBAT,
    },
    {
        .iv = 0,
        .lvl = 48,
        .species = SPECIES_RATICATE,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_TeamRocketGrunt47[] = {
    {
        .iv = 0,
        .lvl = 48,
        .species = SPECIES_MACHOP,
    },
    {
        .iv = 0,
        .lvl = 48,
        .species = SPECIES_MACHOP,
    },
    {
        .iv = 0,
        .lvl = 48,
        .species = SPECIES_MACHOKE,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_TeamRocketGrunt48[] = {
    {
        .iv = 0,
        .lvl = 49,
        .species = SPECIES_HYPNO,
    },
    {
        .iv = 0,
        .lvl = 49,
        .species = SPECIES_HYPNO,
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_TeamRocketAdmin[] = {
    {
        .iv = 150,
        .lvl = 52,
        .species = SPECIES_MUK,
        .moves = {MOVE_SLUDGE_BOMB, MOVE_SCREECH, MOVE_MINIMIZE, MOVE_ROCK_TOMB},
    },
    {
        .iv = 150,
        .lvl = 53,
        .species = SPECIES_ARBOK,
        .moves = {MOVE_SLUDGE_BOMB, MOVE_BITE, MOVE_EARTHQUAKE, MOVE_IRON_TAIL},
    },
    {
        .iv = 150,
        .lvl = 54,
        .species = SPECIES_VILEPLUME,
        .moves = {MOVE_SLUDGE_BOMB, MOVE_GIGA_DRAIN, MOVE_SLEEP_POWDER, MOVE_STUN_SPORE},
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_TeamRocketAdmin2[] = {
    {
        .iv = 200,
        .lvl = 53,
        .species = SPECIES_GOLBAT,
        .moves = {MOVE_CONFUSE_RAY, MOVE_SLUDGE_BOMB, MOVE_AIR_CUTTER, MOVE_SHADOW_BALL},
    },
    {
        .iv = 200,
        .lvl = 54,
        .species = SPECIES_WEEZING,
        .moves = {MOVE_SLUDGE_BOMB, MOVE_THUNDERBOLT, MOVE_EXPLOSION, MOVE_SHADOW_BALL},
    },
    {
        .iv = 200,
        .lvl = 55,
        .species = SPECIES_HOUNDOOM,
        .moves = {MOVE_FLAMETHROWER, MOVE_CRUNCH, MOVE_IRON_TAIL, MOVE_SHADOW_BALL},
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_ScientistGideon[] = {
    {
        .iv = 0,
        .lvl = 46,
        .species = SPECIES_VOLTORB,
        .moves = {MOVE_SWIFT, MOVE_SCREECH, MOVE_SPARK, MOVE_SONIC_BOOM},
    },
    {
        .iv = 0,
        .lvl = 46,
        .species = SPECIES_ELECTRODE,
        .moves = {MOVE_SPARK, MOVE_SONIC_BOOM, MOVE_SCREECH, MOVE_CHARGE},
    },
    {
        .iv = 0,
        .lvl = 46,
        .species = SPECIES_MAGNEMITE,
        .moves = {MOVE_SCREECH, MOVE_SWIFT, MOVE_SPARK, MOVE_THUNDER_WAVE},
    },
    {
        .iv = 0,
        .lvl = 46,
        .species = SPECIES_MAGNETON,
        .moves = {MOVE_TRI_ATTACK, MOVE_SPARK, MOVE_THUNDER_WAVE, MOVE_SONIC_BOOM},
    },
    {
        .iv = 0,
        .lvl = 46,
        .species = SPECIES_PORYGON,
        .moves = {MOVE_TRI_ATTACK, MOVE_CONVERSION, MOVE_RECOVER, MOVE_PSYBEAM},
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_SwimmerFemaleAmara[] = {
    {
        .iv = 0,
        .lvl = 36,
        .species = SPECIES_SEEL,
    },
    {
        .iv = 0,
        .lvl = 36,
        .species = SPECIES_SEEL,
    },
    {
        .iv = 0,
        .lvl = 36,
        .species = SPECIES_DEWGONG,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_SwimmerFemaleMaria[] = {
    {
        .iv = 0,
        .lvl = 37,
        .species = SPECIES_SEADRA,
    },
    {
        .iv = 0,
        .lvl = 37,
        .species = SPECIES_SEADRA,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_SwimmerFemaleAbigail[] = {
    {
        .iv = 0,
        .lvl = 35,
        .species = SPECIES_PSYDUCK,
    },
    {
        .iv = 0,
        .lvl = 36,
        .species = SPECIES_PSYDUCK,
    },
    {
        .iv = 0,
        .lvl = 37,
        .species = SPECIES_GOLDUCK,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_SwimmerMaleFinn[] = {
    {
        .iv = 0,
        .lvl = 38,
        .species = SPECIES_STARMIE,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_SwimmerMaleGarrett[] = {
    {
        .iv = 0,
        .lvl = 35,
        .species = SPECIES_SHELLDER,
    },
    {
        .iv = 0,
        .lvl = 35,
        .species = SPECIES_CLOYSTER,
    },
    {
        .iv = 0,
        .lvl = 38,
        .species = SPECIES_WARTORTLE,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_FishermanTommy[] = {
    {
        .iv = 0,
        .lvl = 33,
        .species = SPECIES_GOLDEEN,
    },
    {
        .iv = 0,
        .lvl = 33,
        .species = SPECIES_GOLDEEN,
    },
    {
        .iv = 0,
        .lvl = 35,
        .species = SPECIES_SEAKING,
    },
    {
        .iv = 0,
        .lvl = 35,
        .species = SPECIES_SEAKING,
    },
    {
        .iv = 0,
        .lvl = 35,
        .species = SPECIES_SEAKING,
    },
};

static const struct TrainerMonItemDefaultMoves sParty_CrushGirlTanya[] = {
    {
        .iv = 50,
        .lvl = 38,
        .species = SPECIES_HITMONLEE,
        .heldItem = ITEM_BLACK_BELT,
    },
    {
        .iv = 50,
        .lvl = 38,
        .species = SPECIES_HITMONCHAN,
        .heldItem = ITEM_BLACK_BELT,
    },
};

static const struct TrainerMonItemDefaultMoves sParty_BlackBeltShea[] = {
    {
        .iv = 100,
        .lvl = 38,
        .species = SPECIES_MACHOP,
        .heldItem = ITEM_BLACK_BELT,
    },
    {
        .iv = 100,
        .lvl = 38,
        .species = SPECIES_MACHOKE,
        .heldItem = ITEM_BLACK_BELT,
    },
};

static const struct TrainerMonItemDefaultMoves sParty_BlackBeltHugh[] = {
    {
        .iv = 100,
        .lvl = 37,
        .species = SPECIES_MACHOP,
        .heldItem = ITEM_BLACK_BELT,
    },
    {
        .iv = 100,
        .lvl = 37,
        .species = SPECIES_MACHOKE,
        .heldItem = ITEM_BLACK_BELT,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_CamperBryce[] = {
    {
        .iv = 0,
        .lvl = 36,
        .species = SPECIES_NIDORINO,
    },
    {
        .iv = 0,
        .lvl = 36,
        .species = SPECIES_RATICATE,
    },
    {
        .iv = 0,
        .lvl = 36,
        .species = SPECIES_SANDSLASH,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_PicnickerClaire[] = {
    {
        .iv = 0,
        .lvl = 35,
        .species = SPECIES_MEOWTH,
    },
    {
        .iv = 0,
        .lvl = 35,
        .species = SPECIES_MEOWTH,
    },
    {
        .iv = 0,
        .lvl = 35,
        .species = SPECIES_PIKACHU,
    },
    {
        .iv = 0,
        .lvl = 35,
        .species = SPECIES_CLEFAIRY,
    },
};

static const struct TrainerMonItemDefaultMoves sParty_CrushKinMikKia[] = {
    {
        .iv = 50,
        .lvl = 39,
        .species = SPECIES_MACHOKE,
        .heldItem = ITEM_BLACK_BELT,
    },
    {
        .iv = 50,
        .lvl = 39,
        .species = SPECIES_PRIMEAPE,
        .heldItem = ITEM_BLACK_BELT,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_AromaLadyViolet[] = {
    {
        .iv = 0,
        .lvl = 36,
        .species = SPECIES_BULBASAUR,
    },
    {
        .iv = 0,
        .lvl = 36,
        .species = SPECIES_IVYSAUR,
    },
    {
        .iv = 0,
        .lvl = 36,
        .species = SPECIES_IVYSAUR,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_TuberAlexis[] = {
    {
        .iv = 0,
        .lvl = 34,
        .species = SPECIES_STARYU,
    },
    {
        .iv = 0,
        .lvl = 34,
        .species = SPECIES_STARYU,
    },
    {
        .iv = 0,
        .lvl = 34,
        .species = SPECIES_KRABBY,
    },
    {
        .iv = 0,
        .lvl = 34,
        .species = SPECIES_KRABBY,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_TwinsJoyMeg[] = {
    {
        .iv = 0,
        .lvl = 37,
        .species = SPECIES_CLEFAIRY,
    },
    {
        .iv = 0,
        .lvl = 37,
        .species = SPECIES_CLEFAIRY,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_SwimmerFemaleTisha[] = {
    {
        .iv = 0,
        .lvl = 38,
        .species = SPECIES_KINGLER,
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_PainterCelina[] = {
    {
        .iv = 50,
        .lvl = 50,
        .species = SPECIES_SMEARGLE,
        .moves = {MOVE_FLY, MOVE_DIG, MOVE_DIVE, MOVE_BOUNCE},
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_PainterRayna[] = {
    {
        .iv = 50,
        .lvl = 50,
        .species = SPECIES_SMEARGLE,
        .moves = {MOVE_CROSS_CHOP, MOVE_MEGAHORN, MOVE_DOUBLE_EDGE, MOVE_SELF_DESTRUCT},
    },
};

static const struct TrainerMonItemDefaultMoves sParty_LadyGillian[] = {
    {
        .iv = 0,
        .lvl = 47,
        .species = SPECIES_MAREEP,
        .heldItem = ITEM_STARDUST,
    },
    {
        .iv = 0,
        .lvl = 48,
        .species = SPECIES_MAREEP,
        .heldItem = ITEM_STARDUST,
    },
    {
        .iv = 0,
        .lvl = 49,
        .species = SPECIES_FLAAFFY,
        .heldItem = ITEM_NUGGET,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_YoungsterDestin[] = {
    {
        .iv = 0,
        .lvl = 48,
        .species = SPECIES_RATICATE,
    },
    {
        .iv = 0,
        .lvl = 48,
        .species = SPECIES_PIDGEOTTO,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_SwimmerMaleToby[] = {
    {
        .iv = 0,
        .lvl = 48,
        .species = SPECIES_POLIWHIRL,
    },
    {
        .iv = 0,
        .lvl = 48,
        .species = SPECIES_TENTACOOL,
    },
    {
        .iv = 0,
        .lvl = 48,
        .species = SPECIES_TENTACRUEL,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_TeamRocketGrunt49[] = {
    {
        .iv = 0,
        .lvl = 48,
        .species = SPECIES_RATTATA,
    },
    {
        .iv = 0,
        .lvl = 48,
        .species = SPECIES_GRIMER,
    },
    {
        .iv = 0,
        .lvl = 48,
        .species = SPECIES_MUK,
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_TeamRocketGrunt50[] = {
    {
        .iv = 0,
        .lvl = 49,
        .species = SPECIES_KOFFING,
        .moves = {MOVE_MEMENTO, MOVE_HAZE, MOVE_SMOKESCREEN, MOVE_SLUDGE},
    },
    {
        .iv = 0,
        .lvl = 49,
        .species = SPECIES_WEEZING,
        .moves = {MOVE_HAZE, MOVE_SMOKESCREEN, MOVE_SLUDGE, MOVE_SELF_DESTRUCT},
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_TeamRocketGrunt51[] = {
    {
        .iv = 50,
        .lvl = 48,
        .species = SPECIES_EKANS,
    },
    {
        .iv = 50,
        .lvl = 48,
        .species = SPECIES_GLOOM,
    },
    {
        .iv = 50,
        .lvl = 48,
        .species = SPECIES_GLOOM,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_BirdKeeperMilo[] = {
    {
        .iv = 0,
        .lvl = 47,
        .species = SPECIES_PIDGEY,
    },
    {
        .iv = 0,
        .lvl = 49,
        .species = SPECIES_PIDGEOTTO,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_BirdKeeperChaz[] = {
    {
        .iv = 0,
        .lvl = 47,
        .species = SPECIES_SPEAROW,
    },
    {
        .iv = 0,
        .lvl = 49,
        .species = SPECIES_FEAROW,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_BirdKeeperHarold[] = {
    {
        .iv = 0,
        .lvl = 47,
        .species = SPECIES_HOOTHOOT,
    },
    {
        .iv = 0,
        .lvl = 49,
        .species = SPECIES_NOCTOWL,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_FishermanTylor[] = {
    {
        .iv = 0,
        .lvl = 49,
        .species = SPECIES_QWILFISH,
    },
    {
        .iv = 0,
        .lvl = 49,
        .species = SPECIES_QWILFISH,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_SwimmerMaleMymo[] = {
    {
        .iv = 0,
        .lvl = 49,
        .species = SPECIES_KINGLER,
    },
    {
        .iv = 0,
        .lvl = 49,
        .species = SPECIES_WARTORTLE,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_SwimmerFemaleNicole[] = {
    {
        .iv = 0,
        .lvl = 50,
        .species = SPECIES_MARILL,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_SisAndBroAvaGeb[] = {
    {
        .iv = 0,
        .lvl = 50,
        .species = SPECIES_POLIWHIRL,
    },
    {
        .iv = 0,
        .lvl = 50,
        .species = SPECIES_STARMIE,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_AromaLadyRose[] = {
    {
        .iv = 0,
        .lvl = 49,
        .species = SPECIES_SUNKERN,
    },
    {
        .iv = 0,
        .lvl = 49,
        .species = SPECIES_SUNFLORA,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_SwimmerMaleSamir[] = {
    {
        .iv = 0,
        .lvl = 50,
        .species = SPECIES_GYARADOS,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_SwimmerFemaleDenise[] = {
    {
        .iv = 0,
        .lvl = 49,
        .species = SPECIES_CHINCHOU,
    },
    {
        .iv = 0,
        .lvl = 49,
        .species = SPECIES_LANTURN,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_TwinsMiuMia[] = {
    {
        .iv = 0,
        .lvl = 50,
        .species = SPECIES_PIKACHU,
    },
    {
        .iv = 0,
        .lvl = 50,
        .species = SPECIES_PIKACHU,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_HikerEarl[] = {
    {
        .iv = 0,
        .lvl = 49,
        .species = SPECIES_ONIX,
    },
    {
        .iv = 0,
        .lvl = 49,
        .species = SPECIES_MACHOKE,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_RuinManiacFoster[] = {
    {
        .iv = 0,
        .lvl = 50,
        .species = SPECIES_GOLEM,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_RuinManiacLarry[] = {
    {
        .iv = 0,
        .lvl = 49,
        .species = SPECIES_MACHOKE,
    },
    {
        .iv = 0,
        .lvl = 49,
        .species = SPECIES_MACHOKE,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_HikerDaryl[] = {
    {
        .iv = 0,
        .lvl = 50,
        .species = SPECIES_SUDOWOODO,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_PokemaniacHector[] = {
    {
        .iv = 30,
        .lvl = 49,
        .species = SPECIES_RHYHORN,
    },
    {
        .iv = 30,
        .lvl = 49,
        .species = SPECIES_KANGASKHAN,
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_PsychicDario[] = {
    {
        .iv = 100,
        .lvl = 52,
        .species = SPECIES_GIRAFARIG,
        .moves = {MOVE_CRUNCH, MOVE_PSYBEAM, MOVE_ODOR_SLEUTH, MOVE_AGILITY},
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_PsychicRodette[] = {
    {
        .iv = 100,
        .lvl = 48,
        .species = SPECIES_NATU,
        .moves = {MOVE_NIGHT_SHADE, MOVE_CONFUSE_RAY, MOVE_WISH, MOVE_FUTURE_SIGHT},
    },
    {
        .iv = 100,
        .lvl = 48,
        .species = SPECIES_DROWZEE,
        .moves = {MOVE_PSYCHIC, MOVE_DISABLE, MOVE_PSYCH_UP, MOVE_FUTURE_SIGHT},
    },
    {
        .iv = 100,
        .lvl = 50,
        .species = SPECIES_HYPNO,
        .moves = {MOVE_PSYCHIC, MOVE_HYPNOSIS, MOVE_PSYCH_UP, MOVE_FUTURE_SIGHT},
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_AromaLadyMiah[] = {
    {
        .iv = 0,
        .lvl = 50,
        .species = SPECIES_BELLOSSOM,
    },
    {
        .iv = 0,
        .lvl = 50,
        .species = SPECIES_BELLOSSOM,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_YoungCoupleEveJon[] = {
    {
        .iv = 0,
        .lvl = 50,
        .species = SPECIES_GOLDUCK,
    },
    {
        .iv = 0,
        .lvl = 50,
        .species = SPECIES_PSYDUCK,
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_JugglerMason[] = {
    {
        .iv = 0,
        .lvl = 47,
        .species = SPECIES_VOLTORB,
        .moves = {MOVE_SWIFT, MOVE_LIGHT_SCREEN, MOVE_SPARK, MOVE_SONIC_BOOM},
    },
    {
        .iv = 0,
        .lvl = 47,
        .species = SPECIES_PINECO,
        .moves = {MOVE_SPIKES, MOVE_BIDE, MOVE_RAPID_SPIN, MOVE_TAKE_DOWN},
    },
    {
        .iv = 0,
        .lvl = 47,
        .species = SPECIES_VOLTORB,
        .moves = {MOVE_SWIFT, MOVE_LIGHT_SCREEN, MOVE_SPARK, MOVE_SONIC_BOOM},
    },
    {
        .iv = 0,
        .lvl = 47,
        .species = SPECIES_PINECO,
        .moves = {MOVE_SPIKES, MOVE_BIDE, MOVE_RAPID_SPIN, MOVE_EXPLOSION},
    },
};

static const struct TrainerMonItemDefaultMoves sParty_CrushGirlCyndy[] = {
    {
        .iv = 50,
        .lvl = 48,
        .species = SPECIES_PRIMEAPE,
        .heldItem = ITEM_BLACK_BELT,
    },
    {
        .iv = 50,
        .lvl = 48,
        .species = SPECIES_HITMONTOP,
        .heldItem = ITEM_BLACK_BELT,
    },
    {
        .iv = 50,
        .lvl = 48,
        .species = SPECIES_MACHOKE,
        .heldItem = ITEM_BLACK_BELT,
    },
};

static const struct TrainerMonItemDefaultMoves sParty_CrushGirlJocelyn[] = {
    {
        .iv = 50,
        .lvl = 38,
        .species = SPECIES_HITMONCHAN,
        .heldItem = ITEM_BLACK_BELT,
    },
    {
        .iv = 50,
        .lvl = 38,
        .species = SPECIES_HITMONCHAN,
        .heldItem = ITEM_BLACK_BELT,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_TamerEvan[] = {
    {
        .iv = 40,
        .lvl = 48,
        .species = SPECIES_SANDSLASH,
    },
    {
        .iv = 40,
        .lvl = 48,
        .species = SPECIES_LICKITUNG,
    },
    {
        .iv = 40,
        .lvl = 49,
        .species = SPECIES_URSARING,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_PokemaniacMark2[] = {
    {
        .iv = 90,
        .lvl = 33,
        .species = SPECIES_RHYHORN,
    },
    {
        .iv = 90,
        .lvl = 33,
        .species = SPECIES_LICKITUNG,
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_PkmnRangerLogan[] = {
    {
        .iv = 100,
        .lvl = 37,
        .species = SPECIES_EXEGGCUTE,
        .moves = {MOVE_SLEEP_POWDER, MOVE_POISON_POWDER, MOVE_STUN_SPORE, MOVE_CONFUSION},
    },
    {
        .iv = 100,
        .lvl = 40,
        .species = SPECIES_EXEGGUTOR,
        .moves = {MOVE_EGG_BOMB, MOVE_STOMP, MOVE_CONFUSION, MOVE_HYPNOSIS},
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_PkmnRangerJackson[] = {
    {
        .iv = 100,
        .lvl = 49,
        .species = SPECIES_TANGELA,
        .moves = {MOVE_SLAM, MOVE_MEGA_DRAIN, MOVE_BIND, MOVE_INGRAIN},
    },
    {
        .iv = 100,
        .lvl = 49,
        .species = SPECIES_EXEGGCUTE,
        .moves = {MOVE_CONFUSION, MOVE_POISON_POWDER, MOVE_BARRAGE, MOVE_REFLECT},
    },
    {
        .iv = 100,
        .lvl = 49,
        .species = SPECIES_EXEGGUTOR,
        .moves = {MOVE_CONFUSION, MOVE_EGG_BOMB, MOVE_SLEEP_POWDER, MOVE_STOMP},
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_PkmnRangerBeth[] = {
    {
        .iv = 100,
        .lvl = 38,
        .species = SPECIES_BELLSPROUT,
    },
    {
        .iv = 100,
        .lvl = 38,
        .species = SPECIES_GLOOM,
    },
    {
        .iv = 100,
        .lvl = 38,
        .species = SPECIES_GLOOM,
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_PkmnRangerKatelyn[] = {
    {
        .iv = 100,
        .lvl = 52,
        .species = SPECIES_CHANSEY,
        .moves = {MOVE_EGG_BOMB, MOVE_DEFENSE_CURL, MOVE_MINIMIZE, MOVE_SOFT_BOILED},
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_CooltrainerLeroy[] = {
    {
        .iv = 100,
        .lvl = 47,
        .species = SPECIES_RHYDON,
        .moves = {MOVE_TAKE_DOWN, MOVE_HORN_DRILL, MOVE_ROCK_BLAST, MOVE_SCARY_FACE},
    },
    {
        .iv = 100,
        .lvl = 48,
        .species = SPECIES_SLOWBRO,
        .moves = {MOVE_PSYCHIC, MOVE_HEADBUTT, MOVE_AMNESIA, MOVE_DISABLE},
    },
    {
        .iv = 100,
        .lvl = 47,
        .species = SPECIES_KANGASKHAN,
        .moves = {MOVE_DIZZY_PUNCH, MOVE_BITE, MOVE_ENDURE, MOVE_REVERSAL},
    },
    {
        .iv = 100,
        .lvl = 48,
        .species = SPECIES_MACHOKE,
        .moves = {MOVE_CROSS_CHOP, MOVE_VITAL_THROW, MOVE_REVENGE, MOVE_SEISMIC_TOSS},
    },
    {
        .iv = 100,
        .lvl = 50,
        .species = SPECIES_URSARING,
        .moves = {MOVE_SLASH, MOVE_FAINT_ATTACK, MOVE_SNORE, MOVE_REST},
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_CooltrainerMichelle[] = {
    {
        .iv = 100,
        .lvl = 47,
        .species = SPECIES_PERSIAN,
        .moves = {MOVE_SLASH, MOVE_SCREECH, MOVE_FAINT_ATTACK, MOVE_BITE},
    },
    {
        .iv = 100,
        .lvl = 47,
        .species = SPECIES_DEWGONG,
        .moves = {MOVE_ICE_BEAM, MOVE_TAKE_DOWN, MOVE_ICY_WIND, MOVE_GROWL},
    },
    {
        .iv = 100,
        .lvl = 48,
        .species = SPECIES_NINETALES,
        .moves = {MOVE_FLAMETHROWER, MOVE_CONFUSE_RAY, MOVE_WILL_O_WISP, MOVE_GRUDGE},
    },
    {
        .iv = 100,
        .lvl = 48,
        .species = SPECIES_RAPIDASH,
        .moves = {MOVE_BOUNCE, MOVE_AGILITY, MOVE_FIRE_SPIN, MOVE_TAKE_DOWN},
    },
    {
        .iv = 100,
        .lvl = 50,
        .species = SPECIES_GIRAFARIG,
        .moves = {MOVE_CRUNCH, MOVE_PSYBEAM, MOVE_STOMP, MOVE_ODOR_SLEUTH},
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_CoolCoupleLexNya[] = {
    {
        .iv = 100,
        .lvl = 52,
        .species = SPECIES_MILTANK,
        .moves = {MOVE_BODY_SLAM, MOVE_MILK_DRINK, MOVE_GROWL, MOVE_DEFENSE_CURL},
    },
    {
        .iv = 100,
        .lvl = 52,
        .species = SPECIES_TAUROS,
        .moves = {MOVE_THRASH, MOVE_HORN_ATTACK, MOVE_PURSUIT, MOVE_SWAGGER},
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_RuinManiacBrandon[] = {
    {
        .iv = 0,
        .lvl = 50,
        .species = SPECIES_ONIX,
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_RuinManiacBenjamin[] = {
    {
        .iv = 0,
        .lvl = 48,
        .species = SPECIES_GEODUDE,
        .moves = {MOVE_EARTHQUAKE, MOVE_ROCK_BLAST, MOVE_ROLLOUT, MOVE_SELF_DESTRUCT},
    },
    {
        .iv = 0,
        .lvl = 48,
        .species = SPECIES_GRAVELER,
        .moves = {MOVE_EARTHQUAKE, MOVE_ROCK_BLAST, MOVE_ROCK_THROW, MOVE_SELF_DESTRUCT},
    },
    {
        .iv = 0,
        .lvl = 48,
        .species = SPECIES_GRAVELER,
        .moves = {MOVE_EARTHQUAKE, MOVE_ROCK_BLAST, MOVE_ROCK_THROW, MOVE_SELF_DESTRUCT},
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_PainterEdna[] = {
    {
        .iv = 50,
        .lvl = 50,
        .species = SPECIES_SMEARGLE,
        .moves = {MOVE_FAKE_OUT, MOVE_EXTREME_SPEED, MOVE_PROTECT, MOVE_QUICK_ATTACK},
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_GentlemanClifford[] = {
    {
        .iv = 0,
        .lvl = 49,
        .species = SPECIES_MAROWAK,
    },
    {
        .iv = 0,
        .lvl = 49,
        .species = SPECIES_GOLDUCK,
    },
};

static const struct TrainerMonItemCustomMoves sParty_LadySelphy[] = {
    {
        .iv = 0,
        .lvl = 49,
        .species = SPECIES_PERSIAN,
        .heldItem = ITEM_NUGGET,
        .moves = {MOVE_PAY_DAY, MOVE_BITE, MOVE_TAUNT, MOVE_TORMENT},
    },
    {
        .iv = 0,
        .lvl = 49,
        .species = SPECIES_PERSIAN,
        .heldItem = ITEM_NUGGET,
        .moves = {MOVE_PAY_DAY, MOVE_SCRATCH, MOVE_TORMENT, MOVE_TAUNT},
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_RuinManiacLawson[] = {
    {
        .iv = 0,
        .lvl = 47,
        .species = SPECIES_ONIX,
    },
    {
        .iv = 0,
        .lvl = 48,
        .species = SPECIES_GRAVELER,
    },
    {
        .iv = 0,
        .lvl = 49,
        .species = SPECIES_MAROWAK,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_PsychicLaura[] = {
    {
        .iv = 100,
        .lvl = 48,
        .species = SPECIES_NATU,
    },
    {
        .iv = 100,
        .lvl = 48,
        .species = SPECIES_NATU,
    },
    {
        .iv = 100,
        .lvl = 49,
        .species = SPECIES_XATU,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_PkmnBreederBethany[] = {
    {
        .iv = 30,
        .lvl = 50,
        .species = SPECIES_CHANSEY,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_PkmnBreederAllison[] = {
    {
        .iv = 30,
        .lvl = 48,
        .species = SPECIES_CLEFAIRY,
    },
    {
        .iv = 30,
        .lvl = 48,
        .species = SPECIES_CLEFAIRY,
    },
    {
        .iv = 30,
        .lvl = 48,
        .species = SPECIES_CLEFABLE,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_BugCatcherGarret[] = {
    {
        .iv = 0,
        .lvl = 49,
        .species = SPECIES_HERACROSS,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_BugCatcherJonah[] = {
    {
        .iv = 0,
        .lvl = 45,
        .species = SPECIES_YANMA,
    },
    {
        .iv = 0,
        .lvl = 45,
        .species = SPECIES_BEEDRILL,
    },
    {
        .iv = 0,
        .lvl = 46,
        .species = SPECIES_YANMA,
    },
    {
        .iv = 0,
        .lvl = 47,
        .species = SPECIES_BEEDRILL,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_BugCatcherVance[] = {
    {
        .iv = 0,
        .lvl = 48,
        .species = SPECIES_VENONAT,
    },
    {
        .iv = 0,
        .lvl = 48,
        .species = SPECIES_VENOMOTH,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_YoungsterNash[] = {
    {
        .iv = 0,
        .lvl = 47,
        .species = SPECIES_WEEPINBELL,
    },
    {
        .iv = 0,
        .lvl = 47,
        .species = SPECIES_WEEPINBELL,
    },
    {
        .iv = 0,
        .lvl = 49,
        .species = SPECIES_VICTREEBEL,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_YoungsterCordell[] = {
    {
        .iv = 0,
        .lvl = 48,
        .species = SPECIES_FARFETCHD,
    },
    {
        .iv = 0,
        .lvl = 48,
        .species = SPECIES_FARFETCHD,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_LassDalia[] = {
    {
        .iv = 0,
        .lvl = 46,
        .species = SPECIES_HOPPIP,
    },
    {
        .iv = 0,
        .lvl = 47,
        .species = SPECIES_HOPPIP,
    },
    {
        .iv = 0,
        .lvl = 47,
        .species = SPECIES_SKIPLOOM,
    },
    {
        .iv = 0,
        .lvl = 48,
        .species = SPECIES_SKIPLOOM,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_LassJoana[] = {
    {
        .iv = 0,
        .lvl = 49,
        .species = SPECIES_SNUBBULL,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_CamperRiley[] = {
    {
        .iv = 0,
        .lvl = 49,
        .species = SPECIES_PINSIR,
    },
    {
        .iv = 0,
        .lvl = 50,
        .species = SPECIES_HERACROSS,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_PicnickerMarcy[] = {
    {
        .iv = 0,
        .lvl = 48,
        .species = SPECIES_PARAS,
    },
    {
        .iv = 0,
        .lvl = 48,
        .species = SPECIES_PARAS,
    },
    {
        .iv = 0,
        .lvl = 49,
        .species = SPECIES_PARASECT,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_RuinManiacLayton[] = {
    {
        .iv = 0,
        .lvl = 48,
        .species = SPECIES_SANDSLASH,
    },
    {
        .iv = 0,
        .lvl = 48,
        .species = SPECIES_ONIX,
    },
    {
        .iv = 0,
        .lvl = 48,
        .species = SPECIES_SANDSLASH,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_PicnickerKelsey2[] = {
    {
        .iv = 20,
        .lvl = 21,
        .species = SPECIES_NIDORAN_M,
    },
    {
        .iv = 20,
        .lvl = 21,
        .species = SPECIES_NIDORAN_F,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_PicnickerKelsey3[] = {
    {
        .iv = 60,
        .lvl = 29,
        .species = SPECIES_NIDORINO,
    },
    {
        .iv = 60,
        .lvl = 29,
        .species = SPECIES_NIDORINA,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_PicnickerKelsey4[] = {
    {
        .iv = 80,
        .lvl = 49,
        .species = SPECIES_NIDORINO,
    },
    {
        .iv = 80,
        .lvl = 49,
        .species = SPECIES_NIDORINA,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_CamperRicky2[] = {
    {
        .iv = 20,
        .lvl = 22,
        .species = SPECIES_SQUIRTLE,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_CamperRicky3[] = {
    {
        .iv = 60,
        .lvl = 30,
        .species = SPECIES_WARTORTLE,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_CamperRicky4[] = {
    {
        .iv = 120,
        .lvl = 55,
        .species = SPECIES_WARTORTLE,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_CamperJeff2[] = {
    {
        .iv = 20,
        .lvl = 21,
        .species = SPECIES_SPEAROW,
    },
    {
        .iv = 20,
        .lvl = 21,
        .species = SPECIES_RATICATE,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_CamperJeff3[] = {
    {
        .iv = 60,
        .lvl = 29,
        .species = SPECIES_FEAROW,
    },
    {
        .iv = 60,
        .lvl = 29,
        .species = SPECIES_RATICATE,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_CamperJeff4[] = {
    {
        .iv = 120,
        .lvl = 54,
        .species = SPECIES_FEAROW,
    },
    {
        .iv = 120,
        .lvl = 54,
        .species = SPECIES_RATICATE,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_PicnickerIsabelle2[] = {
    {
        .iv = 20,
        .lvl = 21,
        .species = SPECIES_PIDGEOTTO,
    },
    {
        .iv = 20,
        .lvl = 21,
        .species = SPECIES_PIDGEOTTO,
    },
    {
        .iv = 20,
        .lvl = 18,
        .species = SPECIES_PIDGEY,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_PicnickerIsabelle3[] = {
    {
        .iv = 60,
        .lvl = 29,
        .species = SPECIES_PIDGEOTTO,
    },
    {
        .iv = 60,
        .lvl = 29,
        .species = SPECIES_PIDGEOTTO,
    },
    {
        .iv = 60,
        .lvl = 26,
        .species = SPECIES_PIDGEOTTO,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_PicnickerIsabelle4[] = {
    {
        .iv = 80,
        .lvl = 47,
        .species = SPECIES_PIDGEOTTO,
    },
    {
        .iv = 80,
        .lvl = 47,
        .species = SPECIES_PIDGEOTTO,
    },
    {
        .iv = 80,
        .lvl = 50,
        .species = SPECIES_PIDGEOT,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_YoungsterYasu2[] = {
    {
        .iv = 40,
        .lvl = 22,
        .species = SPECIES_RATTATA,
    },
    {
        .iv = 40,
        .lvl = 22,
        .species = SPECIES_RATICATE,
    },
    {
        .iv = 40,
        .lvl = 22,
        .species = SPECIES_RATICATE,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_YoungsterYasu3[] = {
    {
        .iv = 80,
        .lvl = 47,
        .species = SPECIES_RATICATE,
    },
    {
        .iv = 80,
        .lvl = 47,
        .species = SPECIES_RATICATE,
    },
    {
        .iv = 80,
        .lvl = 47,
        .species = SPECIES_RATICATE,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_EngineerBernie2[] = {
    {
        .iv = 60,
        .lvl = 28,
        .species = SPECIES_MAGNETON,
    },
    {
        .iv = 60,
        .lvl = 28,
        .species = SPECIES_MAGNETON,
    },
    {
        .iv = 60,
        .lvl = 28,
        .species = SPECIES_MAGNETON,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_GamerDarian2[] = {
    {
        .iv = 60,
        .lvl = 29,
        .species = SPECIES_GROWLITHE,
    },
    {
        .iv = 60,
        .lvl = 29,
        .species = SPECIES_VULPIX,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_CamperChris2[] = {
    {
        .iv = 40,
        .lvl = 24,
        .species = SPECIES_GROWLITHE,
    },
    {
        .iv = 40,
        .lvl = 24,
        .species = SPECIES_CHARMANDER,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_CamperChris3[] = {
    {
        .iv = 60,
        .lvl = 29,
        .species = SPECIES_GROWLITHE,
    },
    {
        .iv = 60,
        .lvl = 29,
        .species = SPECIES_CHARMELEON,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_CamperChris4[] = {
    {
        .iv = 120,
        .lvl = 54,
        .species = SPECIES_ARCANINE,
    },
    {
        .iv = 120,
        .lvl = 54,
        .species = SPECIES_CHARMELEON,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_PicnickerAlicia2[] = {
    {
        .iv = 40,
        .lvl = 25,
        .species = SPECIES_MEOWTH,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_PicnickerAlicia3[] = {
    {
        .iv = 60,
        .lvl = 30,
        .species = SPECIES_PERSIAN,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_PicnickerAlicia4[] = {
    {
        .iv = 120,
        .lvl = 55,
        .species = SPECIES_PERSIAN,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_HikerJeremy2[] = {
    {
        .iv = 60,
        .lvl = 30,
        .species = SPECIES_MACHOKE,
    },
    {
        .iv = 60,
        .lvl = 28,
        .species = SPECIES_ONIX,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_PokemaniacMark3[] = {
    {
        .iv = 150,
        .lvl = 54,
        .species = SPECIES_RHYDON,
    },
    {
        .iv = 150,
        .lvl = 54,
        .species = SPECIES_LICKITUNG,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_PokemaniacHerman2[] = {
    {
        .iv = 90,
        .lvl = 29,
        .species = SPECIES_MAROWAK,
    },
    {
        .iv = 90,
        .lvl = 29,
        .species = SPECIES_SLOWBRO,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_PokemaniacHerman3[] = {
    {
        .iv = 150,
        .lvl = 54,
        .species = SPECIES_MAROWAK,
    },
    {
        .iv = 150,
        .lvl = 54,
        .species = SPECIES_SLOWBRO,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_HikerTrent2[] = {
    {
        .iv = 60,
        .lvl = 31,
        .species = SPECIES_ONIX,
    },
    {
        .iv = 60,
        .lvl = 31,
        .species = SPECIES_GRAVELER,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_LassMegan2[] = {
    {
        .iv = 40,
        .lvl = 22,
        .species = SPECIES_PIDGEOTTO,
    },
    {
        .iv = 40,
        .lvl = 22,
        .species = SPECIES_RATICATE,
    },
    {
        .iv = 40,
        .lvl = 23,
        .species = SPECIES_NIDORAN_M,
    },
    {
        .iv = 40,
        .lvl = 21,
        .species = SPECIES_MEOWTH,
    },
    {
        .iv = 40,
        .lvl = 22,
        .species = SPECIES_PIKACHU,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_LassMegan3[] = {
    {
        .iv = 80,
        .lvl = 46,
        .species = SPECIES_PIDGEOT,
    },
    {
        .iv = 80,
        .lvl = 47,
        .species = SPECIES_RATICATE,
    },
    {
        .iv = 80,
        .lvl = 47,
        .species = SPECIES_NIDORINO,
    },
    {
        .iv = 80,
        .lvl = 47,
        .species = SPECIES_PERSIAN,
    },
    {
        .iv = 80,
        .lvl = 48,
        .species = SPECIES_RAICHU,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_SuperNerdGlenn2[] = {
    {
        .iv = 60,
        .lvl = 28,
        .species = SPECIES_MUK,
    },
    {
        .iv = 60,
        .lvl = 28,
        .species = SPECIES_MUK,
    },
    {
        .iv = 60,
        .lvl = 28,
        .species = SPECIES_MUK,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_GamerRich2[] = {
    {
        .iv = 60,
        .lvl = 30,
        .species = SPECIES_GROWLITHE,
    },
    {
        .iv = 60,
        .lvl = 30,
        .species = SPECIES_VULPIX,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_BikerJaren2[] = {
    {
        .iv = 60,
        .lvl = 28,
        .species = SPECIES_MUK,
    },
    {
        .iv = 60,
        .lvl = 30,
        .species = SPECIES_MUK,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_FishermanElliot2[] = {
    {
        .iv = 60,
        .lvl = 28,
        .species = SPECIES_POLIWHIRL,
    },
    {
        .iv = 60,
        .lvl = 28,
        .species = SPECIES_CLOYSTER,
    },
    {
        .iv = 60,
        .lvl = 28,
        .species = SPECIES_SEAKING,
    },
    {
        .iv = 60,
        .lvl = 28,
        .species = SPECIES_SEADRA,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_RockerLuca2[] = {
    {
        .iv = 60,
        .lvl = 33,
        .species = SPECIES_ELECTRODE,
    },
    {
        .iv = 60,
        .lvl = 33,
        .species = SPECIES_ELECTRODE,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_BeautySheila2[] = {
    {
        .iv = 80,
        .lvl = 49,
        .species = SPECIES_CLEFAIRY,
    },
    {
        .iv = 80,
        .lvl = 49,
        .species = SPECIES_PERSIAN,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_BirdKeeperRobert2[] = {
    {
        .iv = 60,
        .lvl = 28,
        .species = SPECIES_PIDGEOTTO,
    },
    {
        .iv = 60,
        .lvl = 28,
        .species = SPECIES_PIDGEOTTO,
    },
    {
        .iv = 60,
        .lvl = 28,
        .species = SPECIES_FEAROW,
    },
    {
        .iv = 60,
        .lvl = 28,
        .species = SPECIES_FEAROW,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_BirdKeeperRobert3[] = {
    {
        .iv = 80,
        .lvl = 47,
        .species = SPECIES_PIDGEOT,
    },
    {
        .iv = 80,
        .lvl = 47,
        .species = SPECIES_PIDGEOT,
    },
    {
        .iv = 80,
        .lvl = 47,
        .species = SPECIES_FEAROW,
    },
    {
        .iv = 80,
        .lvl = 47,
        .species = SPECIES_FEAROW,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_PicnickerSusie2[] = {
    {
        .iv = 60,
        .lvl = 27,
        .species = SPECIES_PIDGEOTTO,
    },
    {
        .iv = 60,
        .lvl = 27,
        .species = SPECIES_MEOWTH,
    },
    {
        .iv = 60,
        .lvl = 27,
        .species = SPECIES_RATICATE,
    },
    {
        .iv = 60,
        .lvl = 27,
        .species = SPECIES_PIKACHU,
    },
    {
        .iv = 60,
        .lvl = 27,
        .species = SPECIES_MEOWTH,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_PicnickerSusie3[] = {
    {
        .iv = 80,
        .lvl = 47,
        .species = SPECIES_PIDGEOTTO,
    },
    {
        .iv = 80,
        .lvl = 47,
        .species = SPECIES_PERSIAN,
    },
    {
        .iv = 80,
        .lvl = 47,
        .species = SPECIES_RATICATE,
    },
    {
        .iv = 80,
        .lvl = 47,
        .species = SPECIES_PIKACHU,
    },
    {
        .iv = 80,
        .lvl = 47,
        .species = SPECIES_PERSIAN,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_PicnickerSusie4[] = {
    {
        .iv = 120,
        .lvl = 52,
        .species = SPECIES_PIDGEOT,
    },
    {
        .iv = 120,
        .lvl = 52,
        .species = SPECIES_PERSIAN,
    },
    {
        .iv = 120,
        .lvl = 52,
        .species = SPECIES_RATICATE,
    },
    {
        .iv = 120,
        .lvl = 52,
        .species = SPECIES_RAICHU,
    },
    {
        .iv = 120,
        .lvl = 52,
        .species = SPECIES_PERSIAN,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_BikerLukas2[] = {
    {
        .iv = 80,
        .lvl = 47,
        .species = SPECIES_KOFFING,
    },
    {
        .iv = 80,
        .lvl = 47,
        .species = SPECIES_KOFFING,
    },
    {
        .iv = 80,
        .lvl = 47,
        .species = SPECIES_MUK,
    },
    {
        .iv = 80,
        .lvl = 47,
        .species = SPECIES_WEEZING,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_BirdKeeperBenny2[] = {
    {
        .iv = 60,
        .lvl = 32,
        .species = SPECIES_FEAROW,
    },
    {
        .iv = 60,
        .lvl = 32,
        .species = SPECIES_FEAROW,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_BirdKeeperBenny3[] = {
    {
        .iv = 80,
        .lvl = 49,
        .species = SPECIES_FEAROW,
    },
    {
        .iv = 80,
        .lvl = 49,
        .species = SPECIES_FEAROW,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_BirdKeeperMarlon2[] = {
    {
        .iv = 60,
        .lvl = 30,
        .species = SPECIES_FEAROW,
    },
    {
        .iv = 60,
        .lvl = 30,
        .species = SPECIES_DODUO,
    },
    {
        .iv = 60,
        .lvl = 30,
        .species = SPECIES_FEAROW,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_BirdKeeperMarlon3[] = {
    {
        .iv = 80,
        .lvl = 48,
        .species = SPECIES_FEAROW,
    },
    {
        .iv = 80,
        .lvl = 48,
        .species = SPECIES_DODRIO,
    },
    {
        .iv = 80,
        .lvl = 48,
        .species = SPECIES_FEAROW,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_BeautyGrace2[] = {
    {
        .iv = 80,
        .lvl = 49,
        .species = SPECIES_PIDGEOT,
    },
    {
        .iv = 80,
        .lvl = 49,
        .species = SPECIES_WIGGLYTUFF,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_BirdKeeperChester2[] = {
    {
        .iv = 60,
        .lvl = 30,
        .species = SPECIES_DODRIO,
    },
    {
        .iv = 60,
        .lvl = 30,
        .species = SPECIES_DODRIO,
    },
    {
        .iv = 60,
        .lvl = 30,
        .species = SPECIES_DODUO,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_BirdKeeperChester3[] = {
    {
        .iv = 80,
        .lvl = 48,
        .species = SPECIES_DODRIO,
    },
    {
        .iv = 80,
        .lvl = 48,
        .species = SPECIES_DODRIO,
    },
    {
        .iv = 80,
        .lvl = 48,
        .species = SPECIES_DODRIO,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_PicnickerBecky2[] = {
    {
        .iv = 60,
        .lvl = 32,
        .species = SPECIES_PIKACHU,
    },
    {
        .iv = 60,
        .lvl = 32,
        .species = SPECIES_RAICHU,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_PicnickerBecky3[] = {
    {
        .iv = 80,
        .lvl = 49,
        .species = SPECIES_PIKACHU,
    },
    {
        .iv = 80,
        .lvl = 49,
        .species = SPECIES_RAICHU,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_PicnickerBecky4[] = {
    {
        .iv = 120,
        .lvl = 54,
        .species = SPECIES_RAICHU,
    },
    {
        .iv = 120,
        .lvl = 54,
        .species = SPECIES_RAICHU,
    },
};

static const struct TrainerMonItemDefaultMoves sParty_CrushKinRonMya2[] = {
    {
        .iv = 110,
        .lvl = 33,
        .species = SPECIES_HITMONCHAN,
        .heldItem = ITEM_BLACK_BELT,
    },
    {
        .iv = 110,
        .lvl = 33,
        .species = SPECIES_HITMONLEE,
        .heldItem = ITEM_BLACK_BELT,
    },
};

static const struct TrainerMonItemDefaultMoves sParty_CrushKinRonMya3[] = {
    {
        .iv = 130,
        .lvl = 51,
        .species = SPECIES_HITMONCHAN,
        .heldItem = ITEM_BLACK_BELT,
    },
    {
        .iv = 130,
        .lvl = 51,
        .species = SPECIES_HITMONLEE,
        .heldItem = ITEM_BLACK_BELT,
    },
};

static const struct TrainerMonItemDefaultMoves sParty_CrushKinRonMya4[] = {
    {
        .iv = 170,
        .lvl = 56,
        .species = SPECIES_HITMONCHAN,
        .heldItem = ITEM_BLACK_BELT,
    },
    {
        .iv = 170,
        .lvl = 56,
        .species = SPECIES_HITMONLEE,
        .heldItem = ITEM_BLACK_BELT,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_BikerRuben2[] = {
    {
        .iv = 80,
        .lvl = 48,
        .species = SPECIES_WEEZING,
    },
    {
        .iv = 80,
        .lvl = 48,
        .species = SPECIES_WEEZING,
    },
    {
        .iv = 80,
        .lvl = 48,
        .species = SPECIES_WEEZING,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_CueBallCamron2[] = {
    {
        .iv = 80,
        .lvl = 49,
        .species = SPECIES_PRIMEAPE,
    },
    {
        .iv = 80,
        .lvl = 49,
        .species = SPECIES_MACHOKE,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_BikerJaxon2[] = {
    {
        .iv = 80,
        .lvl = 49,
        .species = SPECIES_WEEZING,
    },
    {
        .iv = 80,
        .lvl = 49,
        .species = SPECIES_MUK,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_CueBallIsaiah2[] = {
    {
        .iv = 80,
        .lvl = 49,
        .species = SPECIES_MACHOKE,
    },
    {
        .iv = 80,
        .lvl = 49,
        .species = SPECIES_MACHAMP,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_CueBallCorey2[] = {
    {
        .iv = 80,
        .lvl = 49,
        .species = SPECIES_PRIMEAPE,
    },
    {
        .iv = 80,
        .lvl = 49,
        .species = SPECIES_MACHAMP,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_BirdKeeperJacob2[] = {
    {
        .iv = 60,
        .lvl = 28,
        .species = SPECIES_FEAROW,
    },
    {
        .iv = 60,
        .lvl = 28,
        .species = SPECIES_SPEAROW,
    },
    {
        .iv = 60,
        .lvl = 28,
        .species = SPECIES_FEAROW,
    },
    {
        .iv = 60,
        .lvl = 28,
        .species = SPECIES_SPEAROW,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_BirdKeeperJacob3[] = {
    {
        .iv = 80,
        .lvl = 47,
        .species = SPECIES_FEAROW,
    },
    {
        .iv = 80,
        .lvl = 47,
        .species = SPECIES_FEAROW,
    },
    {
        .iv = 80,
        .lvl = 47,
        .species = SPECIES_FEAROW,
    },
    {
        .iv = 80,
        .lvl = 47,
        .species = SPECIES_FEAROW,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_SwimmerFemaleAlice2[] = {
    {
        .iv = 80,
        .lvl = 49,
        .species = SPECIES_SEAKING,
    },
    {
        .iv = 80,
        .lvl = 49,
        .species = SPECIES_SEAKING,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_SwimmerMaleDarrin2[] = {
    {
        .iv = 120,
        .lvl = 52,
        .species = SPECIES_SEADRA,
    },
    {
        .iv = 120,
        .lvl = 52,
        .species = SPECIES_SEADRA,
    },
    {
        .iv = 120,
        .lvl = 52,
        .species = SPECIES_SEADRA,
    },
    {
        .iv = 120,
        .lvl = 52,
        .species = SPECIES_SEADRA,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_PicnickerMissy2[] = {
    {
        .iv = 80,
        .lvl = 49,
        .species = SPECIES_SEAKING,
    },
    {
        .iv = 80,
        .lvl = 49,
        .species = SPECIES_SEAKING,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_PicnickerMissy3[] = {
    {
        .iv = 120,
        .lvl = 54,
        .species = SPECIES_SEAKING,
    },
    {
        .iv = 120,
        .lvl = 54,
        .species = SPECIES_SEAKING,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_FishermanWade2[] = {
    {
        .iv = 80,
        .lvl = 47,
        .species = SPECIES_MAGIKARP,
    },
    {
        .iv = 80,
        .lvl = 47,
        .species = SPECIES_MAGIKARP,
    },
    {
        .iv = 80,
        .lvl = 47,
        .species = SPECIES_MAGIKARP,
    },
    {
        .iv = 80,
        .lvl = 47,
        .species = SPECIES_MAGIKARP,
    },
    {
        .iv = 80,
        .lvl = 47,
        .species = SPECIES_MAGIKARP,
    },
    {
        .iv = 80,
        .lvl = 47,
        .species = SPECIES_MAGIKARP,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_SwimmerMaleJack2[] = {
    {
        .iv = 80,
        .lvl = 50,
        .species = SPECIES_STARMIE,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_SisAndBroLilIan2[] = {
    {
        .iv = 80,
        .lvl = 50,
        .species = SPECIES_SEADRA,
    },
    {
        .iv = 80,
        .lvl = 50,
        .species = SPECIES_STARMIE,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_SisAndBroLilIan3[] = {
    {
        .iv = 120,
        .lvl = 55,
        .species = SPECIES_SEADRA,
    },
    {
        .iv = 120,
        .lvl = 55,
        .species = SPECIES_STARMIE,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_SwimmerMaleFinn2[] = {
    {
        .iv = 80,
        .lvl = 50,
        .species = SPECIES_STARMIE,
    },
};

static const struct TrainerMonItemDefaultMoves sParty_CrushGirlSharon2[] = {
    {
        .iv = 130,
        .lvl = 50,
        .species = SPECIES_MANKEY,
        .heldItem = ITEM_BLACK_BELT,
    },
    {
        .iv = 130,
        .lvl = 50,
        .species = SPECIES_PRIMEAPE,
        .heldItem = ITEM_BLACK_BELT,
    },
};

static const struct TrainerMonItemDefaultMoves sParty_CrushGirlSharon3[] = {
    {
        .iv = 170,
        .lvl = 55,
        .species = SPECIES_PRIMEAPE,
        .heldItem = ITEM_BLACK_BELT,
    },
    {
        .iv = 170,
        .lvl = 55,
        .species = SPECIES_PRIMEAPE,
        .heldItem = ITEM_BLACK_BELT,
    },
};

static const struct TrainerMonItemDefaultMoves sParty_CrushGirlTanya2[] = {
    {
        .iv = 130,
        .lvl = 50,
        .species = SPECIES_HITMONLEE,
        .heldItem = ITEM_BLACK_BELT,
    },
    {
        .iv = 130,
        .lvl = 50,
        .species = SPECIES_HITMONCHAN,
        .heldItem = ITEM_BLACK_BELT,
    },
};

static const struct TrainerMonItemDefaultMoves sParty_CrushGirlTanya3[] = {
    {
        .iv = 170,
        .lvl = 55,
        .species = SPECIES_HITMONLEE,
        .heldItem = ITEM_BLACK_BELT,
    },
    {
        .iv = 170,
        .lvl = 55,
        .species = SPECIES_HITMONCHAN,
        .heldItem = ITEM_BLACK_BELT,
    },
};

static const struct TrainerMonItemDefaultMoves sParty_BlackBeltShea2[] = {
    {
        .iv = 180,
        .lvl = 50,
        .species = SPECIES_MACHOKE,
        .heldItem = ITEM_BLACK_BELT,
    },
    {
        .iv = 180,
        .lvl = 50,
        .species = SPECIES_MACHOKE,
        .heldItem = ITEM_BLACK_BELT,
    },
};

static const struct TrainerMonItemDefaultMoves sParty_BlackBeltShea3[] = {
    {
        .iv = 220,
        .lvl = 55,
        .species = SPECIES_MACHOKE,
        .heldItem = ITEM_BLACK_BELT,
    },
    {
        .iv = 220,
        .lvl = 55,
        .species = SPECIES_MACHAMP,
        .heldItem = ITEM_BLACK_BELT,
    },
};

static const struct TrainerMonItemDefaultMoves sParty_BlackBeltHugh2[] = {
    {
        .iv = 180,
        .lvl = 50,
        .species = SPECIES_MACHOKE,
        .heldItem = ITEM_BLACK_BELT,
    },
    {
        .iv = 180,
        .lvl = 50,
        .species = SPECIES_MACHOKE,
        .heldItem = ITEM_BLACK_BELT,
    },
};

static const struct TrainerMonItemDefaultMoves sParty_BlackBeltHugh3[] = {
    {
        .iv = 220,
        .lvl = 55,
        .species = SPECIES_MACHOKE,
        .heldItem = ITEM_BLACK_BELT,
    },
    {
        .iv = 220,
        .lvl = 55,
        .species = SPECIES_MACHAMP,
        .heldItem = ITEM_BLACK_BELT,
    },
};

static const struct TrainerMonItemDefaultMoves sParty_CrushKinMikKia2[] = {
    {
        .iv = 130,
        .lvl = 51,
        .species = SPECIES_MACHOKE,
        .heldItem = ITEM_BLACK_BELT,
    },
    {
        .iv = 130,
        .lvl = 51,
        .species = SPECIES_PRIMEAPE,
        .heldItem = ITEM_BLACK_BELT,
    },
};

static const struct TrainerMonItemDefaultMoves sParty_CrushKinMikKia3[] = {
    {
        .iv = 170,
        .lvl = 56,
        .species = SPECIES_MACHAMP,
        .heldItem = ITEM_BLACK_BELT,
    },
    {
        .iv = 170,
        .lvl = 56,
        .species = SPECIES_PRIMEAPE,
        .heldItem = ITEM_BLACK_BELT,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_TuberAmira2[] = {
    {
        .iv = 80,
        .lvl = 47,
        .species = SPECIES_POLIWHIRL,
    },
    {
        .iv = 80,
        .lvl = 47,
        .species = SPECIES_POLIWHIRL,
    },
    {
        .iv = 80,
        .lvl = 47,
        .species = SPECIES_POLIWHIRL,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_TwinsJoyMeg2[] = {
    {
        .iv = 80,
        .lvl = 49,
        .species = SPECIES_CLEFAIRY,
    },
    {
        .iv = 80,
        .lvl = 49,
        .species = SPECIES_CLEFAIRY,
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_PainterRayna2[] = {
    {
        .iv = 120,
        .lvl = 54,
        .species = SPECIES_SMEARGLE,
        .moves = {MOVE_CROSS_CHOP, MOVE_MEGAHORN, MOVE_DOUBLE_EDGE, MOVE_SELF_DESTRUCT},
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_YoungsterDestin2[] = {
    {
        .iv = 120,
        .lvl = 53,
        .species = SPECIES_RATICATE,
    },
    {
        .iv = 120,
        .lvl = 53,
        .species = SPECIES_PIDGEOT,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_PkmnBreederAlize2[] = {
    {
        .iv = 150,
        .lvl = 53,
        .species = SPECIES_PIKACHU,
    },
    {
        .iv = 150,
        .lvl = 53,
        .species = SPECIES_CLEFAIRY,
    },
    {
        .iv = 150,
        .lvl = 53,
        .species = SPECIES_MARILL,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_YoungCoupleGiaJes2[] = {
    {
        .iv = 60,
        .lvl = 30,
        .species = SPECIES_NIDORINA,
    },
    {
        .iv = 60,
        .lvl = 30,
        .species = SPECIES_NIDORINO,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_YoungCoupleGiaJes3[] = {
    {
        .iv = 120,
        .lvl = 55,
        .species = SPECIES_NIDOKING,
    },
    {
        .iv = 120,
        .lvl = 55,
        .species = SPECIES_NIDOQUEEN,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_BirdKeeperMilo2[] = {
    {
        .iv = 120,
        .lvl = 53,
        .species = SPECIES_PIDGEOTTO,
    },
    {
        .iv = 120,
        .lvl = 55,
        .species = SPECIES_PIDGEOT,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_BirdKeeperChaz2[] = {
    {
        .iv = 120,
        .lvl = 53,
        .species = SPECIES_FEAROW,
    },
    {
        .iv = 120,
        .lvl = 55,
        .species = SPECIES_FEAROW,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_BirdKeeperHarold2[] = {
    {
        .iv = 120,
        .lvl = 53,
        .species = SPECIES_NOCTOWL,
    },
    {
        .iv = 120,
        .lvl = 55,
        .species = SPECIES_NOCTOWL,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_SwimmerFemaleNicole2[] = {
    {
        .iv = 120,
        .lvl = 54,
        .species = SPECIES_MARILL,
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_PsychicJaclyn2[] = {
    {
        .iv = 220,
        .lvl = 52,
        .species = SPECIES_NATU,
        .moves = {MOVE_PSYCHIC, MOVE_CONFUSE_RAY, MOVE_FUTURE_SIGHT, MOVE_WISH},
    },
    {
        .iv = 220,
        .lvl = 52,
        .species = SPECIES_SLOWBRO,
        .moves = {MOVE_PSYCHIC, MOVE_HEADBUTT, MOVE_AMNESIA, MOVE_YAWN},
    },
    {
        .iv = 220,
        .lvl = 54,
        .species = SPECIES_KADABRA,
        .moves = {MOVE_PSYCHIC, MOVE_FUTURE_SIGHT, MOVE_RECOVER, MOVE_REFLECT},
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_SwimmerMaleSamir2[] = {
    {
        .iv = 120,
        .lvl = 55,
        .species = SPECIES_GYARADOS,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_HikerEarl2[] = {
    {
        .iv = 120,
        .lvl = 54,
        .species = SPECIES_ONIX,
    },
    {
        .iv = 120,
        .lvl = 54,
        .species = SPECIES_MACHAMP,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_RuinManiacLarry2[] = {
    {
        .iv = 120,
        .lvl = 54,
        .species = SPECIES_MACHOKE,
    },
    {
        .iv = 120,
        .lvl = 54,
        .species = SPECIES_MACHOKE,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_PokemaniacHector2[] = {
    {
        .iv = 150,
        .lvl = 55,
        .species = SPECIES_RHYDON,
    },
    {
        .iv = 150,
        .lvl = 55,
        .species = SPECIES_KANGASKHAN,
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_PsychicDario2[] = {
    {
        .iv = 220,
        .lvl = 56,
        .species = SPECIES_GIRAFARIG,
        .moves = {MOVE_CRUNCH, MOVE_PSYBEAM, MOVE_ODOR_SLEUTH, MOVE_AGILITY},
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_PsychicRodette2[] = {
    {
        .iv = 220,
        .lvl = 53,
        .species = SPECIES_NATU,
        .moves = {MOVE_PSYCHIC, MOVE_CONFUSE_RAY, MOVE_WISH, MOVE_FUTURE_SIGHT},
    },
    {
        .iv = 220,
        .lvl = 53,
        .species = SPECIES_HYPNO,
        .moves = {MOVE_PSYCHIC, MOVE_DISABLE, MOVE_PSYCH_UP, MOVE_FUTURE_SIGHT},
    },
    {
        .iv = 220,
        .lvl = 53,
        .species = SPECIES_HYPNO,
        .moves = {MOVE_PSYCHIC, MOVE_HYPNOSIS, MOVE_PSYCH_UP, MOVE_FUTURE_SIGHT},
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_JugglerMason2[] = {
    {
        .iv = 120,
        .lvl = 52,
        .species = SPECIES_ELECTRODE,
    },
    {
        .iv = 120,
        .lvl = 52,
        .species = SPECIES_PINECO,
    },
    {
        .iv = 120,
        .lvl = 52,
        .species = SPECIES_ELECTRODE,
    },
    {
        .iv = 120,
        .lvl = 52,
        .species = SPECIES_PINECO,
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_PkmnRangerNicolas2[] = {
    {
        .iv = 220,
        .lvl = 55,
        .species = SPECIES_VICTREEBEL,
        .moves = {MOVE_RAZOR_LEAF, MOVE_ACID, MOVE_STUN_SPORE, MOVE_WRAP},
    },
    {
        .iv = 220,
        .lvl = 55,
        .species = SPECIES_VICTREEBEL,
        .moves = {MOVE_RAZOR_LEAF, MOVE_ACID, MOVE_SLEEP_POWDER, MOVE_SLAM},
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_PkmnRangerMadeline2[] = {
    {
        .iv = 220,
        .lvl = 55,
        .species = SPECIES_VILEPLUME,
        .moves = {MOVE_PETAL_DANCE, MOVE_MOONLIGHT, MOVE_ACID, MOVE_SLEEP_POWDER},
    },
    {
        .iv = 220,
        .lvl = 55,
        .species = SPECIES_VILEPLUME,
        .moves = {MOVE_PETAL_DANCE, MOVE_MOONLIGHT, MOVE_ACID, MOVE_STUN_SPORE},
    },
};

static const struct TrainerMonItemDefaultMoves sParty_CrushGirlCyndy2[] = {
    {
        .iv = 170,
        .lvl = 54,
        .species = SPECIES_PRIMEAPE,
        .heldItem = ITEM_BLACK_BELT,
    },
    {
        .iv = 170,
        .lvl = 54,
        .species = SPECIES_HITMONTOP,
        .heldItem = ITEM_BLACK_BELT,
    },
    {
        .iv = 170,
        .lvl = 54,
        .species = SPECIES_MACHAMP,
        .heldItem = ITEM_BLACK_BELT,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_TamerEvan2[] = {
    {
        .iv = 160,
        .lvl = 52,
        .species = SPECIES_SANDSLASH,
    },
    {
        .iv = 160,
        .lvl = 52,
        .species = SPECIES_LICKITUNG,
    },
    {
        .iv = 160,
        .lvl = 55,
        .species = SPECIES_URSARING,
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_PkmnRangerJackson2[] = {
    {
        .iv = 220,
        .lvl = 53,
        .species = SPECIES_TANGELA,
        .moves = {MOVE_SLAM, MOVE_MEGA_DRAIN, MOVE_BIND, MOVE_INGRAIN},
    },
    {
        .iv = 220,
        .lvl = 54,
        .species = SPECIES_EXEGGUTOR,
        .moves = {MOVE_CONFUSION, MOVE_EGG_BOMB, MOVE_STUN_SPORE, MOVE_REFLECT},
    },
    {
        .iv = 220,
        .lvl = 55,
        .species = SPECIES_EXEGGUTOR,
        .moves = {MOVE_CONFUSION, MOVE_EGG_BOMB, MOVE_SLEEP_POWDER, MOVE_STOMP},
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_PkmnRangerKatelyn2[] = {
    {
        .iv = 220,
        .lvl = 56,
        .species = SPECIES_CHANSEY,
        .moves = {MOVE_EGG_BOMB, MOVE_DEFENSE_CURL, MOVE_MINIMIZE, MOVE_SOFT_BOILED},
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_CooltrainerLeroy2[] = {
    {
        .iv = 220,
        .lvl = 52,
        .species = SPECIES_RHYDON,
        .moves = {MOVE_EARTHQUAKE, MOVE_HORN_DRILL, MOVE_ROCK_BLAST, MOVE_SCARY_FACE},
    },
    {
        .iv = 220,
        .lvl = 54,
        .species = SPECIES_SLOWBRO,
        .moves = {MOVE_PSYCHIC, MOVE_HEADBUTT, MOVE_AMNESIA, MOVE_DISABLE},
    },
    {
        .iv = 220,
        .lvl = 52,
        .species = SPECIES_KANGASKHAN,
        .moves = {MOVE_DIZZY_PUNCH, MOVE_BITE, MOVE_ENDURE, MOVE_REVERSAL},
    },
    {
        .iv = 220,
        .lvl = 52,
        .species = SPECIES_MACHAMP,
        .moves = {MOVE_CROSS_CHOP, MOVE_VITAL_THROW, MOVE_REVENGE, MOVE_SEISMIC_TOSS},
    },
    {
        .iv = 220,
        .lvl = 55,
        .species = SPECIES_URSARING,
        .moves = {MOVE_SLASH, MOVE_FAINT_ATTACK, MOVE_SNORE, MOVE_REST},
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_CooltrainerMichelle2[] = {
    {
        .iv = 220,
        .lvl = 53,
        .species = SPECIES_PERSIAN,
        .moves = {MOVE_SLASH, MOVE_SCREECH, MOVE_FAINT_ATTACK, MOVE_BITE},
    },
    {
        .iv = 220,
        .lvl = 53,
        .species = SPECIES_DEWGONG,
        .moves = {MOVE_ICE_BEAM, MOVE_TAKE_DOWN, MOVE_ICY_WIND, MOVE_SHEER_COLD},
    },
    {
        .iv = 220,
        .lvl = 54,
        .species = SPECIES_NINETALES,
        .moves = {MOVE_FLAMETHROWER, MOVE_CONFUSE_RAY, MOVE_WILL_O_WISP, MOVE_GRUDGE},
    },
    {
        .iv = 220,
        .lvl = 54,
        .species = SPECIES_RAPIDASH,
        .moves = {MOVE_BOUNCE, MOVE_AGILITY, MOVE_FIRE_SPIN, MOVE_TAKE_DOWN},
    },
    {
        .iv = 220,
        .lvl = 56,
        .species = SPECIES_GIRAFARIG,
        .moves = {MOVE_CRUNCH, MOVE_PSYBEAM, MOVE_STOMP, MOVE_ODOR_SLEUTH},
    },
};

static const struct TrainerMonNoItemCustomMoves sParty_CoolCoupleLexNya2[] = {
    {
        .iv = 220,
        .lvl = 57,
        .species = SPECIES_MILTANK,
        .moves = {MOVE_BODY_SLAM, MOVE_MILK_DRINK, MOVE_GROWL, MOVE_DEFENSE_CURL},
    },
    {
        .iv = 220,
        .lvl = 57,
        .species = SPECIES_TAUROS,
        .moves = {MOVE_TAKE_DOWN, MOVE_SCARY_FACE, MOVE_PURSUIT, MOVE_SWAGGER},
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_BugCatcherColton2[] = {
    {
        .iv = 20,
        .lvl = 19,
        .species = SPECIES_METAPOD,
    },
    {
        .iv = 20,
        .lvl = 19,
        .species = SPECIES_WEEDLE,
    },
    {
        .iv = 20,
        .lvl = 19,
        .species = SPECIES_METAPOD,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_BugCatcherColton3[] = {
    {
        .iv = 60,
        .lvl = 27,
        .species = SPECIES_BUTTERFREE,
    },
    {
        .iv = 60,
        .lvl = 27,
        .species = SPECIES_KAKUNA,
    },
    {
        .iv = 60,
        .lvl = 27,
        .species = SPECIES_BUTTERFREE,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_BugCatcherColton4[] = {
    {
        .iv = 120,
        .lvl = 51,
        .species = SPECIES_BUTTERFREE,
    },
    {
        .iv = 120,
        .lvl = 54,
        .species = SPECIES_BEEDRILL,
    },
    {
        .iv = 120,
        .lvl = 51,
        .species = SPECIES_BUTTERFREE,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_SwimmerMaleMatthew2[] = {
    {
        .iv = 80,
        .lvl = 49,
        .species = SPECIES_POLIWHIRL,
    },
    {
        .iv = 80,
        .lvl = 49,
        .species = SPECIES_POLIWRATH,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_SwimmerMaleTony2[] = {
    {
        .iv = 80,
        .lvl = 49,
        .species = SPECIES_SEADRA,
    },
    {
        .iv = 80,
        .lvl = 49,
        .species = SPECIES_SEADRA,
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_SwimmerFemaleMelissa2[] = {
    {
        .iv = 80,
        .lvl = 49,
        .species = SPECIES_POLIWHIRL,
    },
    {
        .iv = 80,
        .lvl = 49,
        .species = SPECIES_SEAKING,
    },
};

static const struct TrainerMonItemCustomMoves sParty_EliteFourLorelei2[] = {
    {
        .iv = 255,
        .lvl = 64,
        .species = SPECIES_DEWGONG,
        .heldItem = ITEM_NONE,
        .moves = {MOVE_ICE_BEAM, MOVE_SURF, MOVE_SIGNAL_BEAM, MOVE_DOUBLE_TEAM},
    },
    {
        .iv = 255,
        .lvl = 63,
        .species = SPECIES_CLOYSTER,
        .heldItem = ITEM_NONE,
        .moves = {MOVE_ICE_BEAM, MOVE_SURF, MOVE_SUPERSONIC, MOVE_RAIN_DANCE},
    },
    {
        .iv = 255,
        .lvl = 63,
        .species = SPECIES_PILOSWINE,
        .heldItem = ITEM_NONE,
        .moves = {MOVE_BLIZZARD, MOVE_EARTHQUAKE, MOVE_DOUBLE_EDGE, MOVE_ROCK_SLIDE},
    },
    {
        .iv = 255,
        .lvl = 66,
        .species = SPECIES_JYNX,
        .heldItem = ITEM_NONE,
        .moves = {MOVE_ICE_BEAM, MOVE_PSYCHIC, MOVE_LOVELY_KISS, MOVE_ATTRACT},
    },
    {
        .iv = 255,
        .lvl = 66,
        .species = SPECIES_LAPRAS,
        .heldItem = ITEM_CHERI_BERRY,
        .moves = {MOVE_ICE_BEAM, MOVE_SURF, MOVE_PSYCHIC, MOVE_THUNDER},
    },
};

static const struct TrainerMonItemCustomMoves sParty_EliteFourBruno2[] = {
    {
        .iv = 255,
        .lvl = 65,
        .species = SPECIES_STEELIX,
        .heldItem = ITEM_NONE,
        .moves = {MOVE_EARTHQUAKE, MOVE_IRON_TAIL, MOVE_CRUNCH, MOVE_ROCK_TOMB},
    },
    {
        .iv = 255,
        .lvl = 65,
        .species = SPECIES_HITMONCHAN,
        .heldItem = ITEM_NONE,
        .moves = {MOVE_SKY_UPPERCUT, MOVE_MACH_PUNCH, MOVE_ROCK_SLIDE, MOVE_COUNTER},
    },
    {
        .iv = 255,
        .lvl = 65,
        .species = SPECIES_HITMONLEE,
        .heldItem = ITEM_NONE,
        .moves = {MOVE_MEGA_KICK, MOVE_FORESIGHT, MOVE_EARTHQUAKE, MOVE_ROCK_SLIDE},
    },
    {
        .iv = 255,
        .lvl = 66,
        .species = SPECIES_STEELIX,
        .heldItem = ITEM_NONE,
        .moves = {MOVE_EARTHQUAKE, MOVE_IRON_TAIL, MOVE_CRUNCH, MOVE_DRAGON_BREATH},
    },
    {
        .iv = 255,
        .lvl = 68,
        .species = SPECIES_MACHAMP,
        .heldItem = ITEM_PERSIM_BERRY,
        .moves = {MOVE_CROSS_CHOP, MOVE_EARTHQUAKE, MOVE_BRICK_BREAK, MOVE_ROCK_SLIDE},
    },
};

static const struct TrainerMonItemCustomMoves sParty_EliteFourAgatha2[] = {
    {
        .iv = 255,
        .lvl = 66,
        .species = SPECIES_GENGAR,
        .heldItem = ITEM_NONE,
        .moves = {MOVE_SHADOW_BALL, MOVE_PSYCHIC, MOVE_CONFUSE_RAY, MOVE_HYPNOSIS},
    },
    {
        .iv = 255,
        .lvl = 66,
        .species = SPECIES_CROBAT,
        .heldItem = ITEM_NONE,
        .moves = {MOVE_SLUDGE_BOMB, MOVE_AIR_CUTTER, MOVE_SHADOW_BALL, MOVE_CONFUSE_RAY},
    },
    {
        .iv = 255,
        .lvl = 65,
        .species = SPECIES_MISDREAVUS,
        .heldItem = ITEM_NONE,
        .moves = {MOVE_SHADOW_BALL, MOVE_PSYCHIC, MOVE_THUNDERBOLT, MOVE_ATTRACT},
    },
    {
        .iv = 255,
        .lvl = 68,
        .species = SPECIES_ARBOK,
        .heldItem = ITEM_NONE,
        .moves = {MOVE_SLUDGE_BOMB, MOVE_EARTHQUAKE, MOVE_GIGA_DRAIN, MOVE_DOUBLE_TEAM},
    },
    {
        .iv = 255,
        .lvl = 70,
        .species = SPECIES_GENGAR,
        .heldItem = ITEM_CHESTO_BERRY,
        .moves = {MOVE_SHADOW_BALL, MOVE_PSYCHIC, MOVE_THUNDERBOLT, MOVE_SLUDGE_BOMB},
    },
};

static const struct TrainerMonItemCustomMoves sParty_EliteFourLance2[] = {
    {
        .iv = 255,
        .lvl = 68,
        .species = SPECIES_GYARADOS,
        .heldItem = ITEM_NONE,
        .moves = {MOVE_HYPER_BEAM, MOVE_DRAGON_DANCE, MOVE_EARTHQUAKE, MOVE_THUNDER_WAVE},
    },
    {
        .iv = 255,
        .lvl = 66,
        .species = SPECIES_DRAGONITE,
        .heldItem = ITEM_NONE,
        .moves = {MOVE_HYPER_BEAM, MOVE_EARTHQUAKE, MOVE_DRAGON_CLAW, MOVE_FLAMETHROWER},
    },
    {
        .iv = 255,
        .lvl = 66,
        .species = SPECIES_KINGDRA,
        .heldItem = ITEM_NONE,
        .moves = {MOVE_HYPER_BEAM, MOVE_DRAGON_DANCE, MOVE_SURF, MOVE_ICE_BEAM},
    },
    {
        .iv = 255,
        .lvl = 70,
        .species = SPECIES_AERODACTYL,
        .heldItem = ITEM_NONE,
        .moves = {MOVE_HYPER_BEAM, MOVE_ANCIENT_POWER, MOVE_AERIAL_ACE, MOVE_EARTHQUAKE},
    },
    {
        .iv = 255,
        .lvl = 72,
        .species = SPECIES_DRAGONITE,
        .heldItem = ITEM_PERSIM_BERRY,
        .moves = {MOVE_HYPER_BEAM, MOVE_OUTRAGE, MOVE_THUNDERBOLT, MOVE_ICE_BEAM},
    },
};

static const struct TrainerMonItemCustomMoves sParty_ChampionRematchSquirtle[] = {
    {
        .iv = 255,
        .lvl = 72,
        .species = SPECIES_HERACROSS,
        .heldItem = ITEM_NONE,
        .moves = {MOVE_MEGAHORN, MOVE_EARTHQUAKE, MOVE_COUNTER, MOVE_ROCK_TOMB},
    },
    {
        .iv = 255,
        .lvl = 73,
        .species = SPECIES_ALAKAZAM,
        .heldItem = ITEM_NONE,
        .moves = {MOVE_PSYCHIC, MOVE_SHADOW_BALL, MOVE_CALM_MIND, MOVE_REFLECT},
    },
    {
        .iv = 255,
        .lvl = 72,
        .species = SPECIES_TYRANITAR,
        .heldItem = ITEM_NONE,
        .moves = {MOVE_CRUNCH, MOVE_EARTHQUAKE, MOVE_THUNDERBOLT, MOVE_AERIAL_ACE},
    },
    {
        .iv = 255,
        .lvl = 73,
        .species = SPECIES_ARCANINE,
        .heldItem = ITEM_NONE,
        .moves = {MOVE_EXTREME_SPEED, MOVE_OVERHEAT, MOVE_AERIAL_ACE, MOVE_IRON_TAIL},
    },
    {
        .iv = 255,
        .lvl = 73,
        .species = SPECIES_EXEGGUTOR,
        .heldItem = ITEM_NONE,
        .moves = {MOVE_GIGA_DRAIN, MOVE_PSYCHIC, MOVE_SLEEP_POWDER, MOVE_LIGHT_SCREEN},
    },
    {
        .iv = 255,
        .lvl = 75,
        .species = SPECIES_BLASTOISE,
        .heldItem = ITEM_SITRUS_BERRY,
        .moves = {MOVE_HYDRO_PUMP, MOVE_ICE_BEAM, MOVE_EARTHQUAKE, MOVE_RAIN_DANCE},
    },
};

static const struct TrainerMonItemCustomMoves sParty_ChampionRematchBulbasaur[] = {
    {
        .iv = 255,
        .lvl = 72,
        .species = SPECIES_HERACROSS,
        .heldItem = ITEM_NONE,
        .moves = {MOVE_MEGAHORN, MOVE_EARTHQUAKE, MOVE_COUNTER, MOVE_ROCK_TOMB},
    },
    {
        .iv = 255,
        .lvl = 73,
        .species = SPECIES_ALAKAZAM,
        .heldItem = ITEM_NONE,
        .moves = {MOVE_PSYCHIC, MOVE_SHADOW_BALL, MOVE_CALM_MIND, MOVE_REFLECT},
    },
    {
        .iv = 255,
        .lvl = 72,
        .species = SPECIES_TYRANITAR,
        .heldItem = ITEM_NONE,
        .moves = {MOVE_CRUNCH, MOVE_EARTHQUAKE, MOVE_THUNDERBOLT, MOVE_AERIAL_ACE},
    },
    {
        .iv = 255,
        .lvl = 73,
        .species = SPECIES_GYARADOS,
        .heldItem = ITEM_NONE,
        .moves = {MOVE_HYDRO_PUMP, MOVE_DRAGON_DANCE, MOVE_EARTHQUAKE, MOVE_HYPER_BEAM},
    },
    {
        .iv = 255,
        .lvl = 73,
        .species = SPECIES_ARCANINE,
        .heldItem = ITEM_NONE,
        .moves = {MOVE_EXTREME_SPEED, MOVE_OVERHEAT, MOVE_AERIAL_ACE, MOVE_IRON_TAIL},
    },
    {
        .iv = 255,
        .lvl = 75,
        .species = SPECIES_VENUSAUR,
        .heldItem = ITEM_SITRUS_BERRY,
        .moves = {MOVE_SOLAR_BEAM, MOVE_SLUDGE_BOMB, MOVE_EARTHQUAKE, MOVE_SUNNY_DAY},
    },
};

static const struct TrainerMonItemCustomMoves sParty_ChampionRematchCharmander[] = {
    {
        .iv = 255,
        .lvl = 72,
        .species = SPECIES_HERACROSS,
        .heldItem = ITEM_NONE,
        .moves = {MOVE_MEGAHORN, MOVE_EARTHQUAKE, MOVE_COUNTER, MOVE_ROCK_TOMB},
    },
    {
        .iv = 255,
        .lvl = 73,
        .species = SPECIES_ALAKAZAM,
        .heldItem = ITEM_NONE,
        .moves = {MOVE_PSYCHIC, MOVE_SHADOW_BALL, MOVE_CALM_MIND, MOVE_REFLECT},
    },
    {
        .iv = 255,
        .lvl = 72,
        .species = SPECIES_TYRANITAR,
        .heldItem = ITEM_NONE,
        .moves = {MOVE_CRUNCH, MOVE_EARTHQUAKE, MOVE_THUNDERBOLT, MOVE_AERIAL_ACE},
    },
    {
        .iv = 255,
        .lvl = 73,
        .species = SPECIES_EXEGGUTOR,
        .heldItem = ITEM_NONE,
        .moves = {MOVE_GIGA_DRAIN, MOVE_PSYCHIC, MOVE_SLEEP_POWDER, MOVE_LIGHT_SCREEN},
    },
    {
        .iv = 255,
        .lvl = 73,
        .species = SPECIES_GYARADOS,
        .heldItem = ITEM_NONE,
        .moves = {MOVE_HYDRO_PUMP, MOVE_DRAGON_DANCE, MOVE_EARTHQUAKE, MOVE_HYPER_BEAM},
    },
    {
        .iv = 255,
        .lvl = 75,
        .species = SPECIES_CHARIZARD,
        .heldItem = ITEM_SITRUS_BERRY,
        .moves = {MOVE_FIRE_BLAST, MOVE_DRAGON_CLAW, MOVE_AERIAL_ACE, MOVE_EARTHQUAKE},
    },
};

static const struct TrainerMonNoItemDefaultMoves sParty_CueBallPaxton[] = {
    {
        .iv = 50,
        .lvl = 39,
        .species = SPECIES_WEEZING,
    },
    {
        .iv = 50,
        .lvl = 39,
        .species = SPECIES_MUK,
    },
};
// ===== END src/data/trainer_parties.h =====
// ===== BEGIN src/data/text/trainer_class_names.h =====
const u8 gTrainerClassNames[][13] = {
    [TRAINER_CLASS_NONE]                = _("{PKMN} TRAINER"),
    [TRAINER_CLASS_PKMN_TRAINER_UNUSED] = _("{PKMN} TRAINER"),
    [TRAINER_CLASS_AQUA_LEADER]         = _("AQUA LEADER"),
    [TRAINER_CLASS_TEAM_AQUA]           = _("TEAM AQUA"),
    [TRAINER_CLASS_RS_AROMA_LADY]       = _("AROMA LADY"),
    [TRAINER_CLASS_RS_RUIN_MANIAC]      = _("RUIN MANIAC"),
    [TRAINER_CLASS_INTERVIEWER]         = _("INTERVIEWER"),
    [TRAINER_CLASS_RS_TUBER_F]          = _("TUBER"),
    [TRAINER_CLASS_RS_TUBER_M]          = _("TUBER"),
    [TRAINER_CLASS_RS_COOLTRAINER]      = _("COOLTRAINER"),
    [TRAINER_CLASS_HEX_MANIAC]          = _("HEX MANIAC"),
    [TRAINER_CLASS_RS_LADY]             = _("LADY"),
    [TRAINER_CLASS_RS_BEAUTY]           = _("BEAUTY"),
    [TRAINER_CLASS_RICH_BOY]            = _("RICH BOY"),
    [TRAINER_CLASS_RS_POKEMANIAC]       = _("POKéMANIAC"),
    [TRAINER_CLASS_RS_SWIMMER_M]        = _("SWIMMER♂"),
    [TRAINER_CLASS_RS_BLACK_BELT]       = _("BLACK BELT"),
    [TRAINER_CLASS_GUITARIST]           = _("GUITARIST"),
    [TRAINER_CLASS_KINDLER]             = _("KINDLER"),
    [TRAINER_CLASS_RS_CAMPER]           = _("CAMPER"),
    [TRAINER_CLASS_BUG_MANIAC]          = _("BUG MANIAC"),
    [TRAINER_CLASS_RS_PSYCHIC]          = _("PSYCHIC"),
    [TRAINER_CLASS_RS_GENTLEMAN]        = _("GENTLEMAN"),
    [TRAINER_CLASS_RS_ELITE_FOUR]       = _("ELITE FOUR"),
    [TRAINER_CLASS_RS_LEADER]           = _("LEADER"),
    [TRAINER_CLASS_SCHOOL_KID]          = _("SCHOOL KID"),
    [TRAINER_CLASS_SR_AND_JR]           = _("SR. AND JR."),
    [TRAINER_CLASS_POKEFAN]             = _("POKéFAN"),
    [TRAINER_CLASS_EXPERT]              = _("EXPERT"),
    [TRAINER_CLASS_RS_YOUNGSTER]        = _("YOUNGSTER"),
    [TRAINER_CLASS_RS_CHAMPION]         = _("CHAMPION"),
    [TRAINER_CLASS_RS_FISHERMAN]        = _("FISHERMAN"),
    [TRAINER_CLASS_TRIATHLETE]          = _("TRIATHLETE"),
    [TRAINER_CLASS_DRAGON_TAMER]        = _("DRAGON TAMER"),
    [TRAINER_CLASS_RS_BIRD_KEEPER]      = _("BIRD KEEPER"),
    [TRAINER_CLASS_NINJA_BOY]           = _("NINJA BOY"),
    [TRAINER_CLASS_BATTLE_GIRL]         = _("BATTLE GIRL"),
    [TRAINER_CLASS_PARASOL_LADY]        = _("PARASOL LADY"),
    [TRAINER_CLASS_RS_SWIMMER_F]        = _("SWIMMER♀"),
    [TRAINER_CLASS_RS_PICNICKER]        = _("PICNICKER"),
    [TRAINER_CLASS_RS_TWINS]            = _("TWINS"),
    [TRAINER_CLASS_RS_SAILOR]           = _("SAILOR"),
    [TRAINER_CLASS_BOARDER]             = _("BOARDER"),
    [TRAINER_CLASS_COLLECTOR]           = _("COLLECTOR"),
    [TRAINER_CLASS_PKMN_TRAINER]        = _("{PKMN} TRAINER"),
    [TRAINER_CLASS_RS_PKMN_BREEDER]     = _("{PKMN} BREEDER"),
    [TRAINER_CLASS_RS_PKMN_RANGER]      = _("{PKMN} RANGER"),
    [TRAINER_CLASS_MAGMA_LEADER]        = _("MAGMA LEADER"),
    [TRAINER_CLASS_TEAM_MAGMA]          = _("TEAM MAGMA"),
    [TRAINER_CLASS_RS_LASS]             = _("LASS"),
    [TRAINER_CLASS_RS_BUG_CATCHER]      = _("BUG CATCHER"),
    [TRAINER_CLASS_RS_HIKER]            = _("HIKER"),
    [TRAINER_CLASS_RS_YOUNG_COUPLE]     = _("YOUNG COUPLE"),
    [TRAINER_CLASS_OLD_COUPLE]          = _("OLD COUPLE"),
    [TRAINER_CLASS_RS_SIS_AND_BRO]      = _("SIS AND BRO"),
    [TRAINER_CLASS_AQUA_ADMIN]          = _("AQUA ADMIN"),
    [TRAINER_CLASS_MAGMA_ADMIN]         = _("MAGMA ADMIN"),
    [TRAINER_CLASS_YOUNGSTER]           = _("YOUNGSTER"),
    [TRAINER_CLASS_BUG_CATCHER]         = _("BUG CATCHER"),
    [TRAINER_CLASS_LASS]                = _("LASS"),
    [TRAINER_CLASS_SAILOR]              = _("SAILOR"),
    [TRAINER_CLASS_CAMPER]              = _("CAMPER"),
    [TRAINER_CLASS_PICNICKER]           = _("PICNICKER"),
    [TRAINER_CLASS_POKEMANIAC]          = _("POKéMANIAC"),
    [TRAINER_CLASS_SUPER_NERD]          = _("SUPER NERD"),
    [TRAINER_CLASS_HIKER]               = _("HIKER"),
    [TRAINER_CLASS_BIKER]               = _("BIKER"),
    [TRAINER_CLASS_BURGLAR]             = _("BURGLAR"),
    [TRAINER_CLASS_ENGINEER]            = _("ENGINEER"),
    [TRAINER_CLASS_FISHERMAN]           = _("FISHERMAN"),
    [TRAINER_CLASS_SWIMMER_M]           = _("SWIMMER♂"),
    [TRAINER_CLASS_CUE_BALL]            = _("CUE BALL"),
    [TRAINER_CLASS_GAMER]               = _("GAMER"),
    [TRAINER_CLASS_BEAUTY]              = _("BEAUTY"),
    [TRAINER_CLASS_SWIMMER_F]           = _("SWIMMER♀"),
    [TRAINER_CLASS_PSYCHIC]             = _("PSYCHIC"),
    [TRAINER_CLASS_ROCKER]              = _("ROCKER"),
    [TRAINER_CLASS_JUGGLER]             = _("JUGGLER"),
    [TRAINER_CLASS_TAMER]               = _("TAMER"),
    [TRAINER_CLASS_BIRD_KEEPER]         = _("BIRD KEEPER"),
    [TRAINER_CLASS_BLACK_BELT]          = _("BLACK BELT"),
    [TRAINER_CLASS_RIVAL_EARLY]         = _("RIVAL"),
    [TRAINER_CLASS_SCIENTIST]           = _("SCIENTIST"),
    [TRAINER_CLASS_BOSS]                = _("BOSS"),
    [TRAINER_CLASS_LEADER]              = _("LEADER"),
    [TRAINER_CLASS_TEAM_ROCKET]         = _("TEAM ROCKET"),
    [TRAINER_CLASS_COOLTRAINER]         = _("COOLTRAINER"),
    [TRAINER_CLASS_ELITE_FOUR]          = _("ELITE FOUR"),
    [TRAINER_CLASS_GENTLEMAN]           = _("GENTLEMAN"),
    [TRAINER_CLASS_RIVAL_LATE]          = _("RIVAL"),
    [TRAINER_CLASS_CHAMPION]            = _("CHAMPION"),
    [TRAINER_CLASS_CHANNELER]           = _("CHANNELER"),
    [TRAINER_CLASS_TWINS]               = _("TWINS"),
    [TRAINER_CLASS_COOL_COUPLE]         = _("COOL COUPLE"),
    [TRAINER_CLASS_YOUNG_COUPLE]        = _("YOUNG COUPLE"),
    [TRAINER_CLASS_CRUSH_KIN]           = _("CRUSH KIN"),
    [TRAINER_CLASS_SIS_AND_BRO]         = _("SIS AND BRO"),
    [TRAINER_CLASS_PKMN_PROF]           = _("{PKMN} PROF."),
    [TRAINER_CLASS_PLAYER]              = _("PLAYER"),
    [TRAINER_CLASS_CRUSH_GIRL]          = _("CRUSH GIRL"),
    [TRAINER_CLASS_TUBER]               = _("TUBER"),
    [TRAINER_CLASS_PKMN_BREEDER]        = _("{PKMN} BREEDER"),
    [TRAINER_CLASS_PKMN_RANGER]         = _("{PKMN} RANGER"),
    [TRAINER_CLASS_AROMA_LADY]          = _("AROMA LADY"),
    [TRAINER_CLASS_RUIN_MANIAC]         = _("RUIN MANIAC"),
    [TRAINER_CLASS_LADY]                = _("LADY"),
    [TRAINER_CLASS_PAINTER]             = _("PAINTER"),
};
// ===== END src/data/text/trainer_class_names.h =====
// ===== BEGIN src/data/trainers.h =====
const struct Trainer gTrainers[] = {
    [TRAINER_NONE] = {
        .trainerName = _(""),
    },
    [TRAINER_AQUA_LEADER] = {
        .trainerClass = TRAINER_CLASS_AQUA_LEADER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .trainerPic = TRAINER_PIC_AQUA_LEADER_ARCHIE,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_AquaLeader),
    },
    [TRAINER_AQUA_GRUNT_M] = {
        .trainerClass = TRAINER_CLASS_TEAM_AQUA,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .trainerPic = TRAINER_PIC_AQUA_GRUNT_M,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_AquaGruntM),
    },
    [TRAINER_AQUA_GRUNT_F] = {
        .trainerClass = TRAINER_CLASS_TEAM_AQUA,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .trainerPic = TRAINER_PIC_AQUA_GRUNT_F,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_AquaGruntF),
    },
    [TRAINER_RS_AROMA_LADY] = {
        .trainerClass = TRAINER_CLASS_RS_AROMA_LADY,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_RS_AROMA_LADY,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_RSAromaLady),
    },
    [TRAINER_RS_RUIN_MANIAC] = {
        .trainerClass = TRAINER_CLASS_RS_RUIN_MANIAC,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_RS_RUIN_MANIAC,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_RSRuinManiac),
    },
    [TRAINER_INTERVIEWER] = {
        .trainerClass = TRAINER_CLASS_INTERVIEWER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_INTERVIEWER,
        .trainerPic = TRAINER_PIC_INTERVIEWER,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_Interviewer),
    },
    [TRAINER_RS_TUBER_F] = {
        .trainerClass = TRAINER_CLASS_RS_TUBER_F,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_GIRL,
        .trainerPic = TRAINER_PIC_RS_TUBER_F,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_RSTuberF),
    },
    [TRAINER_RS_TUBER_M] = {
        .trainerClass = TRAINER_CLASS_RS_TUBER_M,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_RS_TUBER_M,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_RSTuberM),
    },
    [TRAINER_RS_COOLTRAINER_M] = {
        .trainerClass = TRAINER_CLASS_RS_COOLTRAINER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_RS_COOLTRAINER_M,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_RSCooltrainerM),
    },
    [TRAINER_RS_COOLTRAINER_F] = {
        .trainerClass = TRAINER_CLASS_RS_COOLTRAINER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_RS_COOLTRAINER_F,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_RSCooltrainerF),
    },
    [TRAINER_HEX_MANIAC] = {
        .trainerClass = TRAINER_CLASS_HEX_MANIAC,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_HEX_MANIAC,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_HexManiac),
    },
    [TRAINER_RS_LADY] = {
        .trainerClass = TRAINER_CLASS_RS_LADY,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_RS_LADY,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_RSLady),
    },
    [TRAINER_RS_BEAUTY] = {
        .trainerClass = TRAINER_CLASS_RS_BEAUTY,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_RS_BEAUTY,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_RSBeauty),
    },
    [TRAINER_RICH_BOY] = {
        .trainerClass = TRAINER_CLASS_RICH_BOY,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_RICH,
        .trainerPic = TRAINER_PIC_RICH_BOY,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_RichBoy),
    },
    [TRAINER_RS_POKEMANIAC] = {
        .trainerClass = TRAINER_CLASS_RS_POKEMANIAC,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_RS_POKEMANIAC,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_RSPokemaniac),
    },
    [TRAINER_RS_SWIMMER_M] = {
        .trainerClass = TRAINER_CLASS_RS_SWIMMER_M,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_RS_SWIMMER_M,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_RSSwimmerM),
    },
    [TRAINER_RS_BLACK_BELT] = {
        .trainerClass = TRAINER_CLASS_RS_BLACK_BELT,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RS_BLACK_BELT,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_RSBlackBelt),
    },
    [TRAINER_GUITARIST] = {
        .trainerClass = TRAINER_CLASS_GUITARIST,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_GUITARIST,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_Guitarist),
    },
    [TRAINER_KINDLER] = {
        .trainerClass = TRAINER_CLASS_KINDLER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_KINDLER,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_Kindler),
    },
    [TRAINER_RS_CAMPER] = {
        .trainerClass = TRAINER_CLASS_RS_CAMPER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_RS_CAMPER,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_RSCamper),
    },
    [TRAINER_BUG_MANIAC] = {
        .trainerClass = TRAINER_CLASS_BUG_MANIAC,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_BUG_MANIAC,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_BugManiac),
    },
    [TRAINER_RS_PSYCHIC_M] = {
        .trainerClass = TRAINER_CLASS_RS_PSYCHIC,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RS_PSYCHIC_M,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_RSPsychicM),
    },
    [TRAINER_RS_PSYCHIC_F] = {
        .trainerClass = TRAINER_CLASS_RS_PSYCHIC,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_RS_PSYCHIC_F,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_RSPsychicF),
    },
    [TRAINER_RS_GENTLEMAN] = {
        .trainerClass = TRAINER_CLASS_RS_GENTLEMAN,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_RICH,
        .trainerPic = TRAINER_PIC_RS_GENTLEMAN,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_RSGentleman),
    },
    [TRAINER_ELITE_FOUR_SIDNEY] = {
        .trainerClass = TRAINER_CLASS_RS_ELITE_FOUR,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_ELITE_FOUR,
        .trainerPic = TRAINER_PIC_ELITE_FOUR_SIDNEY,
        .trainerName = _("SIDNEY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_EliteFourSidney),
    },
    [TRAINER_ELITE_FOUR_PHOEBE] = {
        .trainerClass = TRAINER_CLASS_RS_ELITE_FOUR,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_ELITE_FOUR,
        .trainerPic = TRAINER_PIC_ELITE_FOUR_PHOEBE,
        .trainerName = _("PHOEBE"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_EliteFourPhoebe),
    },
    [TRAINER_LEADER_ROXANNE] = {
        .trainerClass = TRAINER_CLASS_RS_LEADER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_LEADER_ROXANNE,
        .trainerName = _("ROXANNE"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_LeaderRoxanne),
    },
    [TRAINER_LEADER_BRAWLY] = {
        .trainerClass = TRAINER_CLASS_RS_LEADER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_LEADER_BRAWLY,
        .trainerName = _("BRAWLY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_LeaderBrawly),
    },
    [TRAINER_LEADER_TATE_LIZA] = {
        .trainerClass = TRAINER_CLASS_RS_LEADER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_LEADER_TATE_AND_LIZA,
        .trainerName = _("TATE&LIZA"),
        .items = {},
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_LeaderTateLiza),
    },
    [TRAINER_SCHOOL_KID_M] = {
        .trainerClass = TRAINER_CLASS_SCHOOL_KID,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_SCHOOL_KID_M,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_SchoolKidM),
    },
    [TRAINER_SCHOOL_KID_F] = {
        .trainerClass = TRAINER_CLASS_SCHOOL_KID,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_SCHOOL_KID_F,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_SchoolKidF),
    },
    [TRAINER_SR_AND_JR] = {
        .trainerClass = TRAINER_CLASS_SR_AND_JR,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_TWINS,
        .trainerPic = TRAINER_PIC_SR_AND_JR,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_SrAndJr),
    },
    [TRAINER_POKEFAN_M] = {
        .trainerClass = TRAINER_CLASS_POKEFAN,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_TWINS,
        .trainerPic = TRAINER_PIC_POKEFAN_M,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_PokefanM),
    },
    [TRAINER_POKEFAN_F] = {
        .trainerClass = TRAINER_CLASS_POKEFAN,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_TWINS,
        .trainerPic = TRAINER_PIC_POKEFAN_F,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_PokefanF),
    },
    [TRAINER_EXPERT_M] = {
        .trainerClass = TRAINER_CLASS_EXPERT,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_EXPERT_M,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_ExpertM),
    },
    [TRAINER_EXPERT_F] = {
        .trainerClass = TRAINER_CLASS_EXPERT,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_EXPERT_F,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_ExpertF),
    },
    [TRAINER_RS_YOUNGSTER] = {
        .trainerClass = TRAINER_CLASS_RS_YOUNGSTER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_RS_YOUNGSTER,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_RSYoungster),
    },
    [TRAINER_RS_CHAMPION] = {
        .trainerClass = TRAINER_CLASS_RS_CHAMPION,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_CHAMPION_STEVEN,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_RSChampion),
    },
    [TRAINER_RS_FISHERMAN] = {
        .trainerClass = TRAINER_CLASS_RS_FISHERMAN,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_RS_FISHERMAN,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_RSFisherman),
    },
    [TRAINER_CYCLING_TRIATHLETE_M] = {
        .trainerClass = TRAINER_CLASS_TRIATHLETE,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_CYCLING_TRIATHLETE_M,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_CyclingTriathleteM),
    },
    [TRAINER_CYCLING_TRIATHLETE_F] = {
        .trainerClass = TRAINER_CLASS_TRIATHLETE,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_CYCLING_TRIATHLETE_F,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_CyclingTriathleteF),
    },
    [TRAINER_RUNNING_TRIATHLETE_M] = {
        .trainerClass = TRAINER_CLASS_TRIATHLETE,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_RUNNING_TRIATHLETE_M,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_RunningTriathleteM),
    },
    [TRAINER_RUNNING_TRIATHLETE_F] = {
        .trainerClass = TRAINER_CLASS_TRIATHLETE,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_RUNNING_TRIATHLETE_F,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_RunningTriathleteF),
    },
    [TRAINER_SWIMMING_TRIATHLETE_M] = {
        .trainerClass = TRAINER_CLASS_TRIATHLETE,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_SWIMMING_TRIATHLETE_M,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_SwimmingTriathleteM),
    },
    [TRAINER_SWIMMING_TRIATHLETE_F] = {
        .trainerClass = TRAINER_CLASS_TRIATHLETE,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_SWIMMING_TRIATHLETE_F,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_SwimmingTriathleteF),
    },
    [TRAINER_DRAGON_TAMER] = {
        .trainerClass = TRAINER_CLASS_DRAGON_TAMER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_DRAGON_TAMER,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_DragonTamer),
    },
    [TRAINER_RS_BIRD_KEEPER] = {
        .trainerClass = TRAINER_CLASS_RS_BIRD_KEEPER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_RS_BIRD_KEEPER,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_RSBirdKeeper),
    },
    [TRAINER_NINJA_BOY] = {
        .trainerClass = TRAINER_CLASS_NINJA_BOY,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_NINJA_BOY,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_NinjaBoy),
    },
    [TRAINER_BATTLE_GIRL] = {
        .trainerClass = TRAINER_CLASS_BATTLE_GIRL,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_BATTLE_GIRL,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_BattleGirl),
    },
    [TRAINER_PARASOL_LADY] = {
        .trainerClass = TRAINER_CLASS_PARASOL_LADY,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_PARASOL_LADY,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_ParasolLady),
    },
    [TRAINER_RS_SWIMMER_F] = {
        .trainerClass = TRAINER_CLASS_RS_SWIMMER_F,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_RS_SWIMMER_F,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_RSSwimmerF),
    },
    [TRAINER_RS_PICNICKER] = {
        .trainerClass = TRAINER_CLASS_RS_PICNICKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_GIRL,
        .trainerPic = TRAINER_PIC_RS_PICNICKER,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_RSPicnicker),
    },
    [TRAINER_RS_TWINS] = {
        .trainerClass = TRAINER_CLASS_RS_TWINS,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_TWINS,
        .trainerPic = TRAINER_PIC_RS_TWINS,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_RSTwins),
    },
    [TRAINER_RS_SAILOR] = {
        .trainerClass = TRAINER_CLASS_RS_SAILOR,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_RS_SAILOR,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_RSSailor),
    },
    [TRAINER_BOARDER_M] = {
        .trainerClass = TRAINER_CLASS_BOARDER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_RS_YOUNGSTER,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_BoarderM),
    },
    [TRAINER_BOARDER_F] = {
        .trainerClass = TRAINER_CLASS_BOARDER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_RS_YOUNGSTER,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_BoarderF),
    },
    [TRAINER_COLLECTOR] = {
        .trainerClass = TRAINER_CLASS_COLLECTOR,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_COLLECTOR,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_Collector),
    },
    [TRAINER_WALLY] = {
        .trainerClass = TRAINER_CLASS_PKMN_TRAINER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_WALLY,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_Wally),
    },
    [TRAINER_BRENDAN] = {
        .trainerClass = TRAINER_CLASS_PKMN_TRAINER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_RS_BRENDAN_1,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_Brendan),
    },
    [TRAINER_BRENDAN_2] = {
        .trainerClass = TRAINER_CLASS_PKMN_TRAINER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_RS_BRENDAN_1,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_Brendan2),
    },
    [TRAINER_BRENDAN_3] = {
        .trainerClass = TRAINER_CLASS_PKMN_TRAINER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_RS_BRENDAN_1,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_Brendan3),
    },
    [TRAINER_MAY] = {
        .trainerClass = TRAINER_CLASS_PKMN_TRAINER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_RS_MAY_1,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_May),
    },
    [TRAINER_MAY_2] = {
        .trainerClass = TRAINER_CLASS_PKMN_TRAINER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_RS_MAY_1,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_May2),
    },
    [TRAINER_MAY_3] = {
        .trainerClass = TRAINER_CLASS_PKMN_TRAINER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_RS_MAY_1,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_May3),
    },
    [TRAINER_RS_PKMN_BREEDER_M] = {
        .trainerClass = TRAINER_CLASS_RS_PKMN_BREEDER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_RS_POKEMON_BREEDER_M,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_RSPkmnBreederM),
    },
    [TRAINER_RS_PKMN_BREEDER_F] = {
        .trainerClass = TRAINER_CLASS_RS_PKMN_BREEDER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_RS_POKEMON_BREEDER_F,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_RSPkmnBreederF),
    },
    [TRAINER_RS_PKMN_RANGER_M] = {
        .trainerClass = TRAINER_CLASS_RS_PKMN_RANGER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_RS_POKEMON_RANGER_M,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_RSPkmnRangerM),
    },
    [TRAINER_RS_PKMN_RANGER_F] = {
        .trainerClass = TRAINER_CLASS_RS_PKMN_RANGER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_RS_POKEMON_RANGER_F,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_RSPkmnRangerF),
    },
    [TRAINER_MAGMA_LEADER] = {
        .trainerClass = TRAINER_CLASS_MAGMA_LEADER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MAGMA,
        .trainerPic = TRAINER_PIC_MAGMA_LEADER_MAXIE,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_MagmaLeader),
    },
    [TRAINER_MAGMA_GRUNT_M] = {
        .trainerClass = TRAINER_CLASS_TEAM_MAGMA,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MAGMA,
        .trainerPic = TRAINER_PIC_MAGMA_GRUNT_M,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_MagmaGruntM),
    },
    [TRAINER_MAMGA_GRUNT_F] = {
        .trainerClass = TRAINER_CLASS_TEAM_MAGMA,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MAGMA,
        .trainerPic = TRAINER_PIC_MAGMA_GRUNT_F,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_MagmaGruntF),
    },
    [TRAINER_RS_LASS] = {
        .trainerClass = TRAINER_CLASS_RS_LASS,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_RS_LASS,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_RSLass),
    },
    [TRAINER_RS_BUG_CATCHER] = {
        .trainerClass = TRAINER_CLASS_RS_BUG_CATCHER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_RS_BUG_CATCHER,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_RSBugCatcher),
    },
    [TRAINER_RS_HIKER] = {
        .trainerClass = TRAINER_CLASS_RS_HIKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_RS_HIKER,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_RSHiker),
    },
    [TRAINER_RS_YOUNG_COUPLE] = {
        .trainerClass = TRAINER_CLASS_RS_YOUNG_COUPLE,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_GIRL,
        .trainerPic = TRAINER_PIC_RS_YOUNG_COUPLE,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_RSYoungCouple),
    },
    [TRAINER_OLD_COUPLE] = {
        .trainerClass = TRAINER_CLASS_OLD_COUPLE,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_OLD_COUPLE,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_OldCouple),
    },
    [TRAINER_RS_SIS_AND_BRO] = {
        .trainerClass = TRAINER_CLASS_RS_SIS_AND_BRO,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_RS_SIS_AND_BRO,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_RSSisAndBro),
    },
    [TRAINER_AQUA_ADMIN_MATT] = {
        .trainerClass = TRAINER_CLASS_AQUA_ADMIN,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .trainerPic = TRAINER_PIC_AQUA_ADMIN_M,
        .trainerName = _("MATT"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_AquaAdminMatt),
    },
    [TRAINER_AQUA_ADMIN_SHELLY] = {
        .trainerClass = TRAINER_CLASS_AQUA_ADMIN,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .trainerPic = TRAINER_PIC_AQUA_ADMIN_F,
        .trainerName = _("SHELLY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_AquaAdminShelly),
    },
    [TRAINER_MAGMA_ADMIN_TABITHA] = {
        .trainerClass = TRAINER_CLASS_MAGMA_ADMIN,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MAGMA,
        .trainerPic = TRAINER_PIC_MAGMA_ADMIN_M,
        .trainerName = _("TABITHA"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_MagmaAdminTabitha),
    },
    [TRAINER_MAGMA_ADMIN_COURTNEY] = {
        .trainerClass = TRAINER_CLASS_MAGMA_ADMIN,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MAGMA,
        .trainerPic = TRAINER_PIC_MAGMA_ADMIN_F,
        .trainerName = _("COURTNEY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_MagmaAdminCourtney),
    },
    [TRAINER_LEADER_WATTSON] = {
        .trainerClass = TRAINER_CLASS_RS_LEADER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_LEADER_WATTSON,
        .trainerName = _("WATTSON"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_LeaderWattson),
    },
    [TRAINER_LEADER_FLANNERY] = {
        .trainerClass = TRAINER_CLASS_RS_LEADER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_LEADER_FLANNERY,
        .trainerName = _("FLANNERY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_LeaderFlannery),
    },
    [TRAINER_LEADER_NORMAN] = {
        .trainerClass = TRAINER_CLASS_RS_LEADER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_LEADER_NORMAN,
        .trainerName = _("NORMAN"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_LeaderNorman),
    },
    [TRAINER_LEADER_WINONA] = {
        .trainerClass = TRAINER_CLASS_RS_LEADER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_LEADER_WINONA,
        .trainerName = _("WINONA"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_LeaderWinona),
    },
    [TRAINER_LEADER_WALLACE] = {
        .trainerClass = TRAINER_CLASS_RS_LEADER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_LEADER_WALLACE,
        .trainerName = _("WALLACE"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_LeaderWallace),
    },
    [TRAINER_ELITE_FOUR_GLACIA] = {
        .trainerClass = TRAINER_CLASS_RS_ELITE_FOUR,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_ELITE_FOUR,
        .trainerPic = TRAINER_PIC_ELITE_FOUR_GLACIA,
        .trainerName = _("GLACIA"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_EliteFourGlacia),
    },
    [TRAINER_ELITE_FOUR_DRAKE] = {
        .trainerClass = TRAINER_CLASS_RS_ELITE_FOUR,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_ELITE_FOUR,
        .trainerPic = TRAINER_PIC_ELITE_FOUR_DRAKE,
        .trainerName = _("DRAKE"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_EliteFourDrake),
    },
    [TRAINER_YOUNGSTER_BEN] = {
        .trainerClass = TRAINER_CLASS_YOUNGSTER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_YOUNGSTER,
        .trainerName = _("BEN"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_YoungsterBen),
    },
    [TRAINER_YOUNGSTER_CALVIN] = {
        .trainerClass = TRAINER_CLASS_YOUNGSTER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_YOUNGSTER,
        .trainerName = _("CALVIN"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_YoungsterCalvin),
    },
    [TRAINER_YOUNGSTER_JOSH] = {
        .trainerClass = TRAINER_CLASS_YOUNGSTER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_YOUNGSTER,
        .trainerName = _("JOSH"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_YoungsterJosh),
    },
    [TRAINER_YOUNGSTER_TIMMY] = {
        .trainerClass = TRAINER_CLASS_YOUNGSTER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_YOUNGSTER,
        .trainerName = _("TIMMY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_YoungsterTimmy),
    },
    [TRAINER_YOUNGSTER_JOEY] = {
        .trainerClass = TRAINER_CLASS_YOUNGSTER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_YOUNGSTER,
        .trainerName = _("JOEY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_YoungsterJoey),
    },
    [TRAINER_YOUNGSTER_DAN] = {
        .trainerClass = TRAINER_CLASS_YOUNGSTER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_YOUNGSTER,
        .trainerName = _("DAN"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_YoungsterDan),
    },
    [TRAINER_YOUNGSTER_CHAD] = {
        .trainerClass = TRAINER_CLASS_YOUNGSTER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_YOUNGSTER,
        .trainerName = _("CHAD"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_YoungsterChad),
    },
    [TRAINER_YOUNGSTER_TYLER] = {
        .trainerClass = TRAINER_CLASS_YOUNGSTER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_YOUNGSTER,
        .trainerName = _("TYLER"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_YoungsterTyler),
    },
    [TRAINER_YOUNGSTER_EDDIE] = {
        .trainerClass = TRAINER_CLASS_YOUNGSTER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_YOUNGSTER,
        .trainerName = _("EDDIE"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_YoungsterEddie),
    },
    [TRAINER_YOUNGSTER_DILLON] = {
        .trainerClass = TRAINER_CLASS_YOUNGSTER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_YOUNGSTER,
        .trainerName = _("DILLON"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_YoungsterDillon),
    },
    [TRAINER_YOUNGSTER_YASU] = {
        .trainerClass = TRAINER_CLASS_YOUNGSTER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_YOUNGSTER,
        .trainerName = _("YASU"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_YoungsterYasu),
    },
    [TRAINER_YOUNGSTER_DAVE] = {
        .trainerClass = TRAINER_CLASS_YOUNGSTER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_YOUNGSTER,
        .trainerName = _("DAVE"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_YoungsterDave),
    },
    [TRAINER_YOUNGSTER_BEN_2] = {
        .trainerClass = TRAINER_CLASS_YOUNGSTER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_YOUNGSTER,
        .trainerName = _("BEN"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_YoungsterBen2),
    },
    [TRAINER_BUG_CATCHER_RICK] = {
        .trainerClass = TRAINER_CLASS_BUG_CATCHER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BUG_CATCHER,
        .trainerName = _("RICK"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_BugCatcherRick),
    },
    [TRAINER_BUG_CATCHER_DOUG] = {
        .trainerClass = TRAINER_CLASS_BUG_CATCHER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BUG_CATCHER,
        .trainerName = _("DOUG"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_BugCatcherDoug),
    },
    [TRAINER_BUG_CATCHER_SAMMY] = {
        .trainerClass = TRAINER_CLASS_BUG_CATCHER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BUG_CATCHER,
        .trainerName = _("SAMMY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_BugCatcherSammy),
    },
    [TRAINER_BUG_CATCHER_COLTON] = {
        .trainerClass = TRAINER_CLASS_BUG_CATCHER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BUG_CATCHER,
        .trainerName = _("COLTON"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_BugCatcherColton),
    },
    [TRAINER_BUG_CATCHER_GREG] = {
        .trainerClass = TRAINER_CLASS_BUG_CATCHER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BUG_CATCHER,
        .trainerName = _("GREG"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_BugCatcherGreg),
    },
    [TRAINER_BUG_CATCHER_JAMES] = {
        .trainerClass = TRAINER_CLASS_BUG_CATCHER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BUG_CATCHER,
        .trainerName = _("JAMES"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_BugCatcherJames),
    },
    [TRAINER_BUG_CATCHER_KENT] = {
        .trainerClass = TRAINER_CLASS_BUG_CATCHER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BUG_CATCHER,
        .trainerName = _("KENT"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_BugCatcherKent),
    },
    [TRAINER_BUG_CATCHER_ROBBY] = {
        .trainerClass = TRAINER_CLASS_BUG_CATCHER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BUG_CATCHER,
        .trainerName = _("ROBBY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_BugCatcherRobby),
    },
    [TRAINER_BUG_CATCHER_CALE] = {
        .trainerClass = TRAINER_CLASS_BUG_CATCHER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BUG_CATCHER,
        .trainerName = _("CALE"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_BugCatcherCale),
    },
    [TRAINER_BUG_CATCHER_KEIGO] = {
        .trainerClass = TRAINER_CLASS_BUG_CATCHER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BUG_CATCHER,
        .trainerName = _("KEIGO"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_BugCatcherKeigo),
    },
    [TRAINER_BUG_CATCHER_ELIJAH] = {
        .trainerClass = TRAINER_CLASS_BUG_CATCHER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BUG_CATCHER,
        .trainerName = _("ELIJAH"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_BugCatcherElijah),
    },
    [TRAINER_BUG_CATCHER_2] = {
        .trainerClass = TRAINER_CLASS_BUG_CATCHER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BUG_CATCHER,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_BugCatcher2),
    },
    [TRAINER_BUG_CATCHER_BRENT] = {
        .trainerClass = TRAINER_CLASS_BUG_CATCHER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BUG_CATCHER,
        .trainerName = _("BRENT"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_BugCatcherBrent),
    },
    [TRAINER_BUG_CATCHER_CONNER] = {
        .trainerClass = TRAINER_CLASS_BUG_CATCHER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BUG_CATCHER,
        .trainerName = _("CONNER"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_BugCatcherConner),
    },
    [TRAINER_LASS_JANICE] = {
        .trainerClass = TRAINER_CLASS_LASS,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_FEMALE | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_LASS,
        .trainerName = _("JANICE"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_LassJanice),
    },
    [TRAINER_LASS_SALLY] = {
        .trainerClass = TRAINER_CLASS_LASS,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_FEMALE | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_LASS,
        .trainerName = _("SALLY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_LassSally),
    },
    [TRAINER_LASS_ROBIN] = {
        .trainerClass = TRAINER_CLASS_LASS,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_FEMALE | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_LASS,
        .trainerName = _("ROBIN"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_LassRobin),
    },
    [TRAINER_LASS_CRISSY] = {
        .trainerClass = TRAINER_CLASS_LASS,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_FEMALE | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_LASS,
        .trainerName = _("CRISSY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_LassCrissy),
    },
    [TRAINER_LASS_MIRIAM] = {
        .trainerClass = TRAINER_CLASS_LASS,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_FEMALE | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_LASS,
        .trainerName = _("MIRIAM"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_LassMiriam),
    },
    [TRAINER_LASS_IRIS] = {
        .trainerClass = TRAINER_CLASS_LASS,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_FEMALE | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_LASS,
        .trainerName = _("IRIS"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_LassIris),
    },
    [TRAINER_LASS_RELI] = {
        .trainerClass = TRAINER_CLASS_LASS,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_FEMALE | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_LASS,
        .trainerName = _("RELI"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_LassReli),
    },
    [TRAINER_LASS_ALI] = {
        .trainerClass = TRAINER_CLASS_LASS,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_FEMALE | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_LASS,
        .trainerName = _("ALI"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_LassAli),
    },
    [TRAINER_LASS_2] = {
        .trainerClass = TRAINER_CLASS_LASS,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_FEMALE | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_LASS,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_Lass2),
    },
    [TRAINER_LASS_HALEY] = {
        .trainerClass = TRAINER_CLASS_LASS,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_FEMALE | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_LASS,
        .trainerName = _("HALEY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_LassHaley),
    },
    [TRAINER_LASS_ANN] = {
        .trainerClass = TRAINER_CLASS_LASS,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_FEMALE | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_LASS,
        .trainerName = _("ANN"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_LassAnn),
    },
    [TRAINER_LASS_DAWN] = {
        .trainerClass = TRAINER_CLASS_LASS,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_FEMALE | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_LASS,
        .trainerName = _("DAWN"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_LassDawn),
    },
    [TRAINER_LASS_PAIGE] = {
        .trainerClass = TRAINER_CLASS_LASS,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_FEMALE | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_LASS,
        .trainerName = _("PAIGE"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_LassPaige),
    },
    [TRAINER_LASS_ANDREA] = {
        .trainerClass = TRAINER_CLASS_LASS,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_FEMALE | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_LASS,
        .trainerName = _("ANDREA"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_LassAndrea),
    },
    [TRAINER_LASS_MEGAN] = {
        .trainerClass = TRAINER_CLASS_LASS,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_FEMALE | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_LASS,
        .trainerName = _("MEGAN"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_LassMegan),
    },
    [TRAINER_LASS_JULIA] = {
        .trainerClass = TRAINER_CLASS_LASS,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_FEMALE | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_LASS,
        .trainerName = _("JULIA"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_LassJulia),
    },
    [TRAINER_LASS_KAY] = {
        .trainerClass = TRAINER_CLASS_LASS,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_FEMALE | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_LASS,
        .trainerName = _("KAY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_LassKay),
    },
    [TRAINER_LASS_LISA] = {
        .trainerClass = TRAINER_CLASS_LASS,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_FEMALE | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_LASS,
        .trainerName = _("LISA"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_LassLisa),
    },
    [TRAINER_SAILOR_EDMOND] = {
        .trainerClass = TRAINER_CLASS_SAILOR,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_SAILOR,
        .trainerName = _("EDMOND"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_SailorEdmond),
    },
    [TRAINER_SAILOR_TREVOR] = {
        .trainerClass = TRAINER_CLASS_SAILOR,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_SAILOR,
        .trainerName = _("TREVOR"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_SailorTrevor),
    },
    [TRAINER_SAILOR_LEONARD] = {
        .trainerClass = TRAINER_CLASS_SAILOR,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_SAILOR,
        .trainerName = _("LEONARD"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_SailorLeonard),
    },
    [TRAINER_SAILOR_DUNCAN] = {
        .trainerClass = TRAINER_CLASS_SAILOR,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_SAILOR,
        .trainerName = _("DUNCAN"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_SailorDuncan),
    },
    [TRAINER_SAILOR_HUEY] = {
        .trainerClass = TRAINER_CLASS_SAILOR,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_SAILOR,
        .trainerName = _("HUEY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_SailorHuey),
    },
    [TRAINER_SAILOR_DYLAN] = {
        .trainerClass = TRAINER_CLASS_SAILOR,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_SAILOR,
        .trainerName = _("DYLAN"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_SailorDylan),
    },
    [TRAINER_SAILOR_PHILLIP] = {
        .trainerClass = TRAINER_CLASS_SAILOR,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_SAILOR,
        .trainerName = _("PHILLIP"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_SailorPhillip),
    },
    [TRAINER_SAILOR_DWAYNE] = {
        .trainerClass = TRAINER_CLASS_SAILOR,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_SAILOR,
        .trainerName = _("DWAYNE"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_SailorDwayne),
    },
    [TRAINER_CAMPER_LIAM] = {
        .trainerClass = TRAINER_CLASS_CAMPER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_CAMPER,
        .trainerName = _("LIAM"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_CamperLiam),
    },
    [TRAINER_CAMPER_SHANE] = {
        .trainerClass = TRAINER_CLASS_CAMPER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_CAMPER,
        .trainerName = _("SHANE"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_CamperShane),
    },
    [TRAINER_CAMPER_ETHAN] = {
        .trainerClass = TRAINER_CLASS_CAMPER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_CAMPER,
        .trainerName = _("ETHAN"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_CamperEthan),
    },
    [TRAINER_CAMPER_RICKY] = {
        .trainerClass = TRAINER_CLASS_CAMPER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_CAMPER,
        .trainerName = _("RICKY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_CamperRicky),
    },
    [TRAINER_CAMPER_JEFF] = {
        .trainerClass = TRAINER_CLASS_CAMPER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_CAMPER,
        .trainerName = _("JEFF"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_CamperJeff),
    },
    [TRAINER_CAMPER_2] = {
        .trainerClass = TRAINER_CLASS_CAMPER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_CAMPER,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_Camper2),
    },
    [TRAINER_CAMPER_CHRIS] = {
        .trainerClass = TRAINER_CLASS_CAMPER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_CAMPER,
        .trainerName = _("CHRIS"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_CamperChris),
    },
    [TRAINER_CAMPER_DREW] = {
        .trainerClass = TRAINER_CLASS_CAMPER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_CAMPER,
        .trainerName = _("DREW"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_CamperDrew),
    },
    [TRAINER_PICNICKER_DIANA] = {
        .trainerClass = TRAINER_CLASS_PICNICKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_GIRL | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = _("DIANA"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_PicnickerDiana),
    },
    [TRAINER_PICNICKER_NANCY] = {
        .trainerClass = TRAINER_CLASS_PICNICKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_GIRL | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = _("NANCY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_PicnickerNancy),
    },
    [TRAINER_PICNICKER_ISABELLE] = {
        .trainerClass = TRAINER_CLASS_PICNICKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_GIRL | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = _("ISABELLE"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_PicnickerIsabelle),
    },
    [TRAINER_PICNICKER_KELSEY] = {
        .trainerClass = TRAINER_CLASS_PICNICKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_GIRL | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = _("KELSEY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_PicnickerKelsey),
    },
    [TRAINER_PICNICKER_ALICIA] = {
        .trainerClass = TRAINER_CLASS_PICNICKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_GIRL | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = _("ALICIA"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_PicnickerAlicia),
    },
    [TRAINER_PICNICKER_CAITLIN] = {
        .trainerClass = TRAINER_CLASS_PICNICKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_GIRL | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = _("CAITLIN"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_PicnickerCaitlin),
    },
    [TRAINER_PICNICKER_HEIDI] = {
        .trainerClass = TRAINER_CLASS_PICNICKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_GIRL | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = _("HEIDI"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_PicnickerHeidi),
    },
    [TRAINER_PICNICKER_CAROL] = {
        .trainerClass = TRAINER_CLASS_PICNICKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_GIRL | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = _("CAROL"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_PicnickerCarol),
    },
    [TRAINER_PICNICKER_SOFIA] = {
        .trainerClass = TRAINER_CLASS_PICNICKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_GIRL | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = _("SOFIA"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_PicnickerSofia),
    },
    [TRAINER_PICNICKER_MARTHA] = {
        .trainerClass = TRAINER_CLASS_PICNICKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_GIRL | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = _("MARTHA"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_PicnickerMartha),
    },
    [TRAINER_PICNICKER_TINA] = {
        .trainerClass = TRAINER_CLASS_PICNICKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_GIRL | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = _("TINA"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_PicnickerTina),
    },
    [TRAINER_PICNICKER_HANNAH] = {
        .trainerClass = TRAINER_CLASS_PICNICKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_GIRL | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = _("HANNAH"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_PicnickerHannah),
    },
    [TRAINER_POKEMANIAC_MARK] = {
        .trainerClass = TRAINER_CLASS_POKEMANIAC,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_POKEMANIAC,
        .trainerName = _("MARK"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_PokemaniacMark),
    },
    [TRAINER_POKEMANIAC_HERMAN] = {
        .trainerClass = TRAINER_CLASS_POKEMANIAC,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_POKEMANIAC,
        .trainerName = _("HERMAN"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_PokemaniacHerman),
    },
    [TRAINER_POKEMANIAC_COOPER] = {
        .trainerClass = TRAINER_CLASS_POKEMANIAC,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_POKEMANIAC,
        .trainerName = _("COOPER"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_PokemaniacCooper),
    },
    [TRAINER_POKEMANIAC_STEVE] = {
        .trainerClass = TRAINER_CLASS_POKEMANIAC,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_POKEMANIAC,
        .trainerName = _("STEVE"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_PokemaniacSteve),
    },
    [TRAINER_POKEMANIAC_WINSTON] = {
        .trainerClass = TRAINER_CLASS_POKEMANIAC,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_POKEMANIAC,
        .trainerName = _("WINSTON"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_PokemaniacWinston),
    },
    [TRAINER_POKEMANIAC_DAWSON] = {
        .trainerClass = TRAINER_CLASS_POKEMANIAC,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_POKEMANIAC,
        .trainerName = _("DAWSON"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_PokemaniacDawson),
    },
    [TRAINER_POKEMANIAC_ASHTON] = {
        .trainerClass = TRAINER_CLASS_POKEMANIAC,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_POKEMANIAC,
        .trainerName = _("ASHTON"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_PokemaniacAshton),
    },
    [TRAINER_SUPER_NERD_JOVAN] = {
        .trainerClass = TRAINER_CLASS_SUPER_NERD,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_SUPER_NERD,
        .trainerName = _("JOVAN"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_SuperNerdJovan),
    },
    [TRAINER_SUPER_NERD_MIGUEL] = {
        .trainerClass = TRAINER_CLASS_SUPER_NERD,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_SUPER_NERD,
        .trainerName = _("MIGUEL"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_SuperNerdMiguel),
    },
    [TRAINER_SUPER_NERD_AIDAN] = {
        .trainerClass = TRAINER_CLASS_SUPER_NERD,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_SUPER_NERD,
        .trainerName = _("AIDAN"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_SuperNerdAidan),
    },
    [TRAINER_SUPER_NERD_GLENN] = {
        .trainerClass = TRAINER_CLASS_SUPER_NERD,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_SUPER_NERD,
        .trainerName = _("GLENN"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_SuperNerdGlenn),
    },
    [TRAINER_SUPER_NERD_LESLIE] = {
        .trainerClass = TRAINER_CLASS_SUPER_NERD,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_SUPER_NERD,
        .trainerName = _("LESLIE"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_SuperNerdLeslie),
    },
    [TRAINER_SUPER_NERD_1] = {
        .trainerClass = TRAINER_CLASS_SUPER_NERD,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_SUPER_NERD,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_SuperNerd1),
    },
    [TRAINER_SUPER_NERD_2] = {
        .trainerClass = TRAINER_CLASS_SUPER_NERD,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_SUPER_NERD,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_SuperNerd2),
    },
    [TRAINER_SUPER_NERD_3] = {
        .trainerClass = TRAINER_CLASS_SUPER_NERD,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_SUPER_NERD,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_SuperNerd3),
    },
    [TRAINER_SUPER_NERD_ERIK] = {
        .trainerClass = TRAINER_CLASS_SUPER_NERD,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_SUPER_NERD,
        .trainerName = _("ERIK"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_SuperNerdErik),
    },
    [TRAINER_SUPER_NERD_AVERY] = {
        .trainerClass = TRAINER_CLASS_SUPER_NERD,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_SUPER_NERD,
        .trainerName = _("AVERY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_SuperNerdAvery),
    },
    [TRAINER_SUPER_NERD_DEREK] = {
        .trainerClass = TRAINER_CLASS_SUPER_NERD,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_SUPER_NERD,
        .trainerName = _("DEREK"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_SuperNerdDerek),
    },
    [TRAINER_SUPER_NERD_ZAC] = {
        .trainerClass = TRAINER_CLASS_SUPER_NERD,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_SUPER_NERD,
        .trainerName = _("ZAC"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_SuperNerdZac),
    },
    [TRAINER_HIKER_MARCOS] = {
        .trainerClass = TRAINER_CLASS_HIKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_HIKER,
        .trainerName = _("MARCOS"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_HikerMarcos),
    },
    [TRAINER_HIKER_FRANKLIN] = {
        .trainerClass = TRAINER_CLASS_HIKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_HIKER,
        .trainerName = _("FRANKLIN"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_HikerFranklin),
    },
    [TRAINER_HIKER_NOB] = {
        .trainerClass = TRAINER_CLASS_HIKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_HIKER,
        .trainerName = _("NOB"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_HikerNob),
    },
    [TRAINER_HIKER_WAYNE] = {
        .trainerClass = TRAINER_CLASS_HIKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_HIKER,
        .trainerName = _("WAYNE"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_HikerWayne),
    },
    [TRAINER_HIKER_ALAN] = {
        .trainerClass = TRAINER_CLASS_HIKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_HIKER,
        .trainerName = _("ALAN"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_HikerAlan),
    },
    [TRAINER_HIKER_BRICE] = {
        .trainerClass = TRAINER_CLASS_HIKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_HIKER,
        .trainerName = _("BRICE"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_HikerBrice),
    },
    [TRAINER_HIKER_CLARK] = {
        .trainerClass = TRAINER_CLASS_HIKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_HIKER,
        .trainerName = _("CLARK"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_HikerClark),
    },
    [TRAINER_HIKER_TRENT] = {
        .trainerClass = TRAINER_CLASS_HIKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_HIKER,
        .trainerName = _("TRENT"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_HikerTrent),
    },
    [TRAINER_HIKER_DUDLEY] = {
        .trainerClass = TRAINER_CLASS_HIKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_HIKER,
        .trainerName = _("DUDLEY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_HikerDudley),
    },
    [TRAINER_HIKER_ALLEN] = {
        .trainerClass = TRAINER_CLASS_HIKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_HIKER,
        .trainerName = _("ALLEN"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_HikerAllen),
    },
    [TRAINER_HIKER_ERIC] = {
        .trainerClass = TRAINER_CLASS_HIKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_HIKER,
        .trainerName = _("ERIC"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_HikerEric),
    },
    [TRAINER_HIKER_LENNY] = {
        .trainerClass = TRAINER_CLASS_HIKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_HIKER,
        .trainerName = _("LENNY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_HikerLenny),
    },
    [TRAINER_HIKER_OLIVER] = {
        .trainerClass = TRAINER_CLASS_HIKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_HIKER,
        .trainerName = _("OLIVER"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_HikerOliver),
    },
    [TRAINER_HIKER_LUCAS] = {
        .trainerClass = TRAINER_CLASS_HIKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_HIKER,
        .trainerName = _("LUCAS"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_HikerLucas),
    },
    [TRAINER_BIKER_JARED] = {
        .trainerClass = TRAINER_CLASS_BIKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BIKER,
        .trainerName = _("JARED"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_BikerJared),
    },
    [TRAINER_BIKER_MALIK] = {
        .trainerClass = TRAINER_CLASS_BIKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BIKER,
        .trainerName = _("MALIK"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_BikerMalik),
    },
    [TRAINER_BIKER_ERNEST] = {
        .trainerClass = TRAINER_CLASS_BIKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BIKER,
        .trainerName = _("ERNEST"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_BikerErnest),
    },
    [TRAINER_BIKER_ALEX] = {
        .trainerClass = TRAINER_CLASS_BIKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BIKER,
        .trainerName = _("ALEX"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_BikerAlex),
    },
    [TRAINER_BIKER_LAO] = {
        .trainerClass = TRAINER_CLASS_BIKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BIKER,
        .trainerName = _("LAO"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_BikerLao),
    },
    [TRAINER_BIKER_1] = {
        .trainerClass = TRAINER_CLASS_BIKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BIKER,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_Biker1),
    },
    [TRAINER_BIKER_HIDEO] = {
        .trainerClass = TRAINER_CLASS_BIKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BIKER,
        .trainerName = _("HIDEO"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_BikerHideo),
    },
    [TRAINER_BIKER_RUBEN] = {
        .trainerClass = TRAINER_CLASS_BIKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BIKER,
        .trainerName = _("RUBEN"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_BikerRuben),
    },
    [TRAINER_BIKER_BILLY] = {
        .trainerClass = TRAINER_CLASS_BIKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BIKER,
        .trainerName = _("BILLY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_BikerBilly),
    },
    [TRAINER_BIKER_NIKOLAS] = {
        .trainerClass = TRAINER_CLASS_BIKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BIKER,
        .trainerName = _("NIKOLAS"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_BikerNikolas),
    },
    [TRAINER_BIKER_JAXON] = {
        .trainerClass = TRAINER_CLASS_BIKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BIKER,
        .trainerName = _("JAXON"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_BikerJaxon),
    },
    [TRAINER_BIKER_WILLIAM] = {
        .trainerClass = TRAINER_CLASS_BIKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BIKER,
        .trainerName = _("WILLIAM"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_BikerWilliam),
    },
    [TRAINER_BIKER_LUKAS] = {
        .trainerClass = TRAINER_CLASS_BIKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BIKER,
        .trainerName = _("LUKAS"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_BikerLukas),
    },
    [TRAINER_BIKER_ISAAC] = {
        .trainerClass = TRAINER_CLASS_BIKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BIKER,
        .trainerName = _("ISAAC"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_BikerIsaac),
    },
    [TRAINER_BIKER_GERALD] = {
        .trainerClass = TRAINER_CLASS_BIKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BIKER,
        .trainerName = _("GERALD"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_BikerGerald),
    },
    [TRAINER_BURGLAR_1] = {
        .trainerClass = TRAINER_CLASS_BURGLAR,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_BURGLAR,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_Burglar1),
    },
    [TRAINER_BURGLAR_2] = {
        .trainerClass = TRAINER_CLASS_BURGLAR,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_BURGLAR,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_Burglar2),
    },
    [TRAINER_BURGLAR_3] = {
        .trainerClass = TRAINER_CLASS_BURGLAR,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_BURGLAR,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_Burglar3),
    },
    [TRAINER_BURGLAR_QUINN] = {
        .trainerClass = TRAINER_CLASS_BURGLAR,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_BURGLAR,
        .trainerName = _("QUINN"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_BurglarQuinn),
    },
    [TRAINER_BURGLAR_RAMON] = {
        .trainerClass = TRAINER_CLASS_BURGLAR,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_BURGLAR,
        .trainerName = _("RAMON"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_BurglarRamon),
    },
    [TRAINER_BURGLAR_DUSTY] = {
        .trainerClass = TRAINER_CLASS_BURGLAR,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_BURGLAR,
        .trainerName = _("DUSTY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_BurglarDusty),
    },
    [TRAINER_BURGLAR_ARNIE] = {
        .trainerClass = TRAINER_CLASS_BURGLAR,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_BURGLAR,
        .trainerName = _("ARNIE"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_BurglarArnie),
    },
    [TRAINER_BURGLAR_4] = {
        .trainerClass = TRAINER_CLASS_BURGLAR,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_BURGLAR,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_Burglar4),
    },
    [TRAINER_BURGLAR_SIMON] = {
        .trainerClass = TRAINER_CLASS_BURGLAR,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_BURGLAR,
        .trainerName = _("SIMON"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_BurglarSimon),
    },
    [TRAINER_BURGLAR_LEWIS] = {
        .trainerClass = TRAINER_CLASS_BURGLAR,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_BURGLAR,
        .trainerName = _("LEWIS"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_BurglarLewis),
    },
    [TRAINER_ENGINEER_BAILY] = {
        .trainerClass = TRAINER_CLASS_ENGINEER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_ENGINEER,
        .trainerName = _("BAILY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_EngineerBaily),
    },
    [TRAINER_ENGINEER_BRAXTON] = {
        .trainerClass = TRAINER_CLASS_ENGINEER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_ENGINEER,
        .trainerName = _("BRAXTON"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_EngineerBraxton),
    },
    [TRAINER_ENGINEER_BERNIE] = {
        .trainerClass = TRAINER_CLASS_ENGINEER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_ENGINEER,
        .trainerName = _("BERNIE"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_EngineerBernie),
    },
    [TRAINER_FISHERMAN_DALE] = {
        .trainerClass = TRAINER_CLASS_FISHERMAN,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_FISHERMAN,
        .trainerName = _("DALE"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_FishermanDale),
    },
    [TRAINER_FISHERMAN_BARNY] = {
        .trainerClass = TRAINER_CLASS_FISHERMAN,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_FISHERMAN,
        .trainerName = _("BARNY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_FishermanBarny),
    },
    [TRAINER_FISHERMAN_NED] = {
        .trainerClass = TRAINER_CLASS_FISHERMAN,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_FISHERMAN,
        .trainerName = _("NED"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_FishermanNed),
    },
    [TRAINER_FISHERMAN_CHIP] = {
        .trainerClass = TRAINER_CLASS_FISHERMAN,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_FISHERMAN,
        .trainerName = _("CHIP"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_FishermanChip),
    },
    [TRAINER_FISHERMAN_HANK] = {
        .trainerClass = TRAINER_CLASS_FISHERMAN,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_FISHERMAN,
        .trainerName = _("HANK"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_FishermanHank),
    },
    [TRAINER_FISHERMAN_ELLIOT] = {
        .trainerClass = TRAINER_CLASS_FISHERMAN,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_FISHERMAN,
        .trainerName = _("ELLIOT"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_FishermanElliot),
    },
    [TRAINER_FISHERMAN_RONALD] = {
        .trainerClass = TRAINER_CLASS_FISHERMAN,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_FISHERMAN,
        .trainerName = _("RONALD"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_FishermanRonald),
    },
    [TRAINER_FISHERMAN_CLAUDE] = {
        .trainerClass = TRAINER_CLASS_FISHERMAN,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_FISHERMAN,
        .trainerName = _("CLAUDE"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_FishermanClaude),
    },
    [TRAINER_FISHERMAN_WADE] = {
        .trainerClass = TRAINER_CLASS_FISHERMAN,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_FISHERMAN,
        .trainerName = _("WADE"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_FishermanWade),
    },
    [TRAINER_FISHERMAN_NOLAN] = {
        .trainerClass = TRAINER_CLASS_FISHERMAN,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_FISHERMAN,
        .trainerName = _("NOLAN"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_FishermanNolan),
    },
    [TRAINER_FISHERMAN_ANDREW] = {
        .trainerClass = TRAINER_CLASS_FISHERMAN,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_FISHERMAN,
        .trainerName = _("ANDREW"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_FishermanAndrew),
    },
    [TRAINER_SWIMMER_MALE_LUIS] = {
        .trainerClass = TRAINER_CLASS_SWIMMER_M,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = _("LUIS"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_SwimmerMaleLuis),
    },
    [TRAINER_SWIMMER_MALE_RICHARD] = {
        .trainerClass = TRAINER_CLASS_SWIMMER_M,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = _("RICHARD"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_SwimmerMaleRichard),
    },
    [TRAINER_SWIMMER_MALE_REECE] = {
        .trainerClass = TRAINER_CLASS_SWIMMER_M,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = _("REECE"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_SwimmerMaleReece),
    },
    [TRAINER_SWIMMER_MALE_MATTHEW] = {
        .trainerClass = TRAINER_CLASS_SWIMMER_M,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = _("MATTHEW"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_SwimmerMaleMatthew),
    },
    [TRAINER_SWIMMER_MALE_DOUGLAS] = {
        .trainerClass = TRAINER_CLASS_SWIMMER_M,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = _("DOUGLAS"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_SwimmerMaleDouglas),
    },
    [TRAINER_SWIMMER_MALE_DAVID] = {
        .trainerClass = TRAINER_CLASS_SWIMMER_M,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = _("DAVID"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_SwimmerMaleDavid),
    },
    [TRAINER_SWIMMER_MALE_TONY] = {
        .trainerClass = TRAINER_CLASS_SWIMMER_M,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = _("TONY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_SwimmerMaleTony),
    },
    [TRAINER_SWIMMER_MALE_AXLE] = {
        .trainerClass = TRAINER_CLASS_SWIMMER_M,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = _("AXLE"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_SwimmerMaleAxle),
    },
    [TRAINER_SWIMMER_MALE_BARRY] = {
        .trainerClass = TRAINER_CLASS_SWIMMER_M,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = _("BARRY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_SwimmerMaleBarry),
    },
    [TRAINER_SWIMMER_MALE_DEAN] = {
        .trainerClass = TRAINER_CLASS_SWIMMER_M,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = _("DEAN"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_SwimmerMaleDean),
    },
    [TRAINER_SWIMMER_MALE_DARRIN] = {
        .trainerClass = TRAINER_CLASS_SWIMMER_M,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = _("DARRIN"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_SwimmerMaleDarrin),
    },
    [TRAINER_SWIMMER_MALE_SPENCER] = {
        .trainerClass = TRAINER_CLASS_SWIMMER_M,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = _("SPENCER"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_SwimmerMaleSpencer),
    },
    [TRAINER_SWIMMER_MALE_JACK] = {
        .trainerClass = TRAINER_CLASS_SWIMMER_M,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = _("JACK"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_SwimmerMaleJack),
    },
    [TRAINER_SWIMMER_MALE_JEROME] = {
        .trainerClass = TRAINER_CLASS_SWIMMER_M,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = _("JEROME"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_SwimmerMaleJerome),
    },
    [TRAINER_SWIMMER_MALE_ROLAND] = {
        .trainerClass = TRAINER_CLASS_SWIMMER_M,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = _("ROLAND"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_SwimmerMaleRoland),
    },
    [TRAINER_CUE_BALL_KOJI] = {
        .trainerClass = TRAINER_CLASS_CUE_BALL,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_CUE_BALL,
        .trainerName = _("KOJI"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_CueBallKoji),
    },
    [TRAINER_CUE_BALL_LUKE] = {
        .trainerClass = TRAINER_CLASS_CUE_BALL,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_CUE_BALL,
        .trainerName = _("LUKE"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_CueBallLuke),
    },
    [TRAINER_CUE_BALL_CAMRON] = {
        .trainerClass = TRAINER_CLASS_CUE_BALL,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_CUE_BALL,
        .trainerName = _("CAMRON"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_CueBallCamron),
    },
    [TRAINER_CUE_BALL_RAUL] = {
        .trainerClass = TRAINER_CLASS_CUE_BALL,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_CUE_BALL,
        .trainerName = _("RAUL"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_CueBallRaul),
    },
    [TRAINER_CUE_BALL_ISAIAH] = {
        .trainerClass = TRAINER_CLASS_CUE_BALL,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_CUE_BALL,
        .trainerName = _("ISAIAH"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_CueBallIsaiah),
    },
    [TRAINER_CUE_BALL_ZEEK] = {
        .trainerClass = TRAINER_CLASS_CUE_BALL,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_CUE_BALL,
        .trainerName = _("ZEEK"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_CueBallZeek),
    },
    [TRAINER_CUE_BALL_JAMAL] = {
        .trainerClass = TRAINER_CLASS_CUE_BALL,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_CUE_BALL,
        .trainerName = _("JAMAL"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_CueBallJamal),
    },
    [TRAINER_CUE_BALL_COREY] = {
        .trainerClass = TRAINER_CLASS_CUE_BALL,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_CUE_BALL,
        .trainerName = _("COREY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_CueBallCorey),
    },
    [TRAINER_CUE_BALL_CHASE] = {
        .trainerClass = TRAINER_CLASS_CUE_BALL,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_CUE_BALL,
        .trainerName = _("CHASE"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_CueBallChase),
    },
    [TRAINER_GAMER_HUGO] = {
        .trainerClass = TRAINER_CLASS_GAMER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_GAMER,
        .trainerName = _("HUGO"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_GamerHugo),
    },
    [TRAINER_GAMER_JASPER] = {
        .trainerClass = TRAINER_CLASS_GAMER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_GAMER,
        .trainerName = _("JASPER"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_GamerJasper),
    },
    [TRAINER_GAMER_DIRK] = {
        .trainerClass = TRAINER_CLASS_GAMER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_GAMER,
        .trainerName = _("DIRK"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_GamerDirk),
    },
    [TRAINER_GAMER_DARIAN] = {
        .trainerClass = TRAINER_CLASS_GAMER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_GAMER,
        .trainerName = _("DARIAN"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_GamerDarian),
    },
    [TRAINER_GAMER_STAN] = {
        .trainerClass = TRAINER_CLASS_GAMER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_GAMER,
        .trainerName = _("STAN"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_GamerStan),
    },
    [TRAINER_GAMER_1] = {
        .trainerClass = TRAINER_CLASS_GAMER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_GAMER,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_Gamer1),
    },
    [TRAINER_GAMER_RICH] = {
        .trainerClass = TRAINER_CLASS_GAMER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_GAMER,
        .trainerName = _("RICH"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_GamerRich),
    },
    [TRAINER_BEAUTY_BRIDGET] = {
        .trainerClass = TRAINER_CLASS_BEAUTY,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_FEMALE | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_BEAUTY,
        .trainerName = _("BRIDGET"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_BeautyBridget),
    },
    [TRAINER_BEAUTY_TAMIA] = {
        .trainerClass = TRAINER_CLASS_BEAUTY,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_FEMALE | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_BEAUTY,
        .trainerName = _("TAMIA"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_BeautyTamia),
    },
    [TRAINER_BEAUTY_LORI] = {
        .trainerClass = TRAINER_CLASS_BEAUTY,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_FEMALE | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_BEAUTY,
        .trainerName = _("LORI"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_BeautyLori),
    },
    [TRAINER_BEAUTY_LOLA] = {
        .trainerClass = TRAINER_CLASS_BEAUTY,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_FEMALE | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_BEAUTY,
        .trainerName = _("LOLA"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_BeautyLola),
    },
    [TRAINER_BEAUTY_SHEILA] = {
        .trainerClass = TRAINER_CLASS_BEAUTY,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_FEMALE | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_BEAUTY,
        .trainerName = _("SHEILA"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_BeautySheila),
    },
    [TRAINER_SWIMMER_FEMALE_TIFFANY] = {
        .trainerClass = TRAINER_CLASS_SWIMMER_F,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_FEMALE | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_SWIMMER_F,
        .trainerName = _("TIFFANY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_SwimmerFemaleTiffany),
    },
    [TRAINER_SWIMMER_FEMALE_NORA] = {
        .trainerClass = TRAINER_CLASS_SWIMMER_F,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_FEMALE | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_SWIMMER_F,
        .trainerName = _("NORA"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_SwimmerFemaleNora),
    },
    [TRAINER_SWIMMER_FEMALE_MELISSA] = {
        .trainerClass = TRAINER_CLASS_SWIMMER_F,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_FEMALE | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_SWIMMER_F,
        .trainerName = _("MELISSA"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_SwimmerFemaleMelissa),
    },
    [TRAINER_BEAUTY_GRACE] = {
        .trainerClass = TRAINER_CLASS_BEAUTY,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_FEMALE | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_BEAUTY,
        .trainerName = _("GRACE"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_BeautyGrace),
    },
    [TRAINER_BEAUTY_OLIVIA] = {
        .trainerClass = TRAINER_CLASS_BEAUTY,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_FEMALE | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_BEAUTY,
        .trainerName = _("OLIVIA"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_BeautyOlivia),
    },
    [TRAINER_BEAUTY_LAUREN] = {
        .trainerClass = TRAINER_CLASS_BEAUTY,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_FEMALE | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_SWIMMER_F,
        .trainerName = _("LAUREN"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_BeautyLauren),
    },
    [TRAINER_SWIMMER_FEMALE_ANYA] = {
        .trainerClass = TRAINER_CLASS_SWIMMER_F,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_FEMALE | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_SWIMMER_F,
        .trainerName = _("ANYA"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_SwimmerFemaleAnya),
    },
    [TRAINER_SWIMMER_FEMALE_ALICE] = {
        .trainerClass = TRAINER_CLASS_SWIMMER_F,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_FEMALE | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_SWIMMER_F,
        .trainerName = _("ALICE"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_SwimmerFemaleAlice),
    },
    [TRAINER_SWIMMER_FEMALE_CONNIE] = {
        .trainerClass = TRAINER_CLASS_SWIMMER_F,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_FEMALE | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_SWIMMER_F,
        .trainerName = _("CONNIE"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_SwimmerFemaleConnie),
    },
    [TRAINER_SWIMMER_FEMALE_SHIRLEY] = {
        .trainerClass = TRAINER_CLASS_SWIMMER_F,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_FEMALE | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_SWIMMER_F,
        .trainerName = _("SHIRLEY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_SwimmerFemaleShirley),
    },
    [TRAINER_PSYCHIC_JOHAN] = {
        .trainerClass = TRAINER_CLASS_PSYCHIC,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_PSYCHIC_M,
        .trainerName = _("JOHAN"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_PsychicJohan),
    },
    [TRAINER_PSYCHIC_TYRON] = {
        .trainerClass = TRAINER_CLASS_PSYCHIC,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_PSYCHIC_M,
        .trainerName = _("TYRON"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_PsychicTyron),
    },
    [TRAINER_PSYCHIC_CAMERON] = {
        .trainerClass = TRAINER_CLASS_PSYCHIC,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_PSYCHIC_M,
        .trainerName = _("CAMERON"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_PsychicCameron),
    },
    [TRAINER_PSYCHIC_PRESTON] = {
        .trainerClass = TRAINER_CLASS_PSYCHIC,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_PSYCHIC_M,
        .trainerName = _("PRESTON"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_PsychicPreston),
    },
    [TRAINER_ROCKER_RANDALL] = {
        .trainerClass = TRAINER_CLASS_ROCKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_ROCKER,
        .trainerName = _("RANDALL"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_RockerRandall),
    },
    [TRAINER_ROCKER_LUCA] = {
        .trainerClass = TRAINER_CLASS_ROCKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_ROCKER,
        .trainerName = _("LUCA"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_RockerLuca),
    },
    [TRAINER_JUGGLER_DALTON] = {
        .trainerClass = TRAINER_CLASS_JUGGLER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_JUGGLER,
        .trainerName = _("DALTON"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_JugglerDalton),
    },
    [TRAINER_JUGGLER_NELSON] = {
        .trainerClass = TRAINER_CLASS_JUGGLER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_JUGGLER,
        .trainerName = _("NELSON"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_JugglerNelson),
    },
    [TRAINER_JUGGLER_KIRK] = {
        .trainerClass = TRAINER_CLASS_JUGGLER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_JUGGLER,
        .trainerName = _("KIRK"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_JugglerKirk),
    },
    [TRAINER_JUGGLER_SHAWN] = {
        .trainerClass = TRAINER_CLASS_JUGGLER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_JUGGLER,
        .trainerName = _("SHAWN"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_JugglerShawn),
    },
    [TRAINER_JUGGLER_GREGORY] = {
        .trainerClass = TRAINER_CLASS_JUGGLER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_JUGGLER,
        .trainerName = _("GREGORY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_JugglerGregory),
    },
    [TRAINER_JUGGLER_EDWARD] = {
        .trainerClass = TRAINER_CLASS_JUGGLER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_JUGGLER,
        .trainerName = _("EDWARD"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_JugglerEdward),
    },
    [TRAINER_JUGGLER_KAYDEN] = {
        .trainerClass = TRAINER_CLASS_JUGGLER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_JUGGLER,
        .trainerName = _("KAYDEN"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_JugglerKayden),
    },
    [TRAINER_JUGGLER_NATE] = {
        .trainerClass = TRAINER_CLASS_JUGGLER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_JUGGLER,
        .trainerName = _("NATE"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_JugglerNate),
    },
    [TRAINER_TAMER_PHIL] = {
        .trainerClass = TRAINER_CLASS_TAMER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_TAMER,
        .trainerName = _("PHIL"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_TamerPhil),
    },
    [TRAINER_TAMER_EDGAR] = {
        .trainerClass = TRAINER_CLASS_TAMER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_TAMER,
        .trainerName = _("EDGAR"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_TamerEdgar),
    },
    [TRAINER_TAMER_JASON] = {
        .trainerClass = TRAINER_CLASS_TAMER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_TAMER,
        .trainerName = _("JASON"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_TamerJason),
    },
    [TRAINER_TAMER_COLE] = {
        .trainerClass = TRAINER_CLASS_TAMER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_TAMER,
        .trainerName = _("COLE"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_TamerCole),
    },
    [TRAINER_TAMER_VINCENT] = {
        .trainerClass = TRAINER_CLASS_TAMER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_TAMER,
        .trainerName = _("VINCENT"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_TamerVincent),
    },
    [TRAINER_TAMER_JOHN] = {
        .trainerClass = TRAINER_CLASS_TAMER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_TAMER,
        .trainerName = _("JOHN"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_TamerJohn),
    },
    [TRAINER_BIRD_KEEPER_SEBASTIAN] = {
        .trainerClass = TRAINER_CLASS_BIRD_KEEPER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_BIRD_KEEPER,
        .trainerName = _("SEBASTIAN"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_BirdKeeperSebastian),
    },
    [TRAINER_BIRD_KEEPER_PERRY] = {
        .trainerClass = TRAINER_CLASS_BIRD_KEEPER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_BIRD_KEEPER,
        .trainerName = _("PERRY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_BirdKeeperPerry),
    },
    [TRAINER_BIRD_KEEPER_ROBERT] = {
        .trainerClass = TRAINER_CLASS_BIRD_KEEPER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_BIRD_KEEPER,
        .trainerName = _("ROBERT"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_BirdKeeperRobert),
    },
    [TRAINER_BIRD_KEEPER_DONALD] = {
        .trainerClass = TRAINER_CLASS_BIRD_KEEPER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_BIRD_KEEPER,
        .trainerName = _("DONALD"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_BirdKeeperDonald),
    },
    [TRAINER_BIRD_KEEPER_BENNY] = {
        .trainerClass = TRAINER_CLASS_BIRD_KEEPER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_BIRD_KEEPER,
        .trainerName = _("BENNY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_BirdKeeperBenny),
    },
    [TRAINER_BIRD_KEEPER_EDWIN] = {
        .trainerClass = TRAINER_CLASS_BIRD_KEEPER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_BIRD_KEEPER,
        .trainerName = _("EDWIN"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_BirdKeeperEdwin),
    },
    [TRAINER_BIRD_KEEPER_CHESTER] = {
        .trainerClass = TRAINER_CLASS_BIRD_KEEPER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_BIRD_KEEPER,
        .trainerName = _("CHESTER"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_BirdKeeperChester),
    },
    [TRAINER_BIRD_KEEPER_WILTON] = {
        .trainerClass = TRAINER_CLASS_BIRD_KEEPER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_BIRD_KEEPER,
        .trainerName = _("WILTON"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_BirdKeeperWilton),
    },
    [TRAINER_BIRD_KEEPER_RAMIRO] = {
        .trainerClass = TRAINER_CLASS_BIRD_KEEPER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_BIRD_KEEPER,
        .trainerName = _("RAMIRO"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_BirdKeeperRamiro),
    },
    [TRAINER_BIRD_KEEPER_JACOB] = {
        .trainerClass = TRAINER_CLASS_BIRD_KEEPER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_BIRD_KEEPER,
        .trainerName = _("JACOB"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_BirdKeeperJacob),
    },
    [TRAINER_BIRD_KEEPER_ROGER] = {
        .trainerClass = TRAINER_CLASS_BIRD_KEEPER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_BIRD_KEEPER,
        .trainerName = _("ROGER"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_BirdKeeperRoger),
    },
    [TRAINER_BIRD_KEEPER_REED] = {
        .trainerClass = TRAINER_CLASS_BIRD_KEEPER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_BIRD_KEEPER,
        .trainerName = _("REED"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_BirdKeeperReed),
    },
    [TRAINER_BIRD_KEEPER_KEITH] = {
        .trainerClass = TRAINER_CLASS_BIRD_KEEPER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_BIRD_KEEPER,
        .trainerName = _("KEITH"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_BirdKeeperKeith),
    },
    [TRAINER_BIRD_KEEPER_CARTER] = {
        .trainerClass = TRAINER_CLASS_BIRD_KEEPER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_BIRD_KEEPER,
        .trainerName = _("CARTER"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_BirdKeeperCarter),
    },
    [TRAINER_BIRD_KEEPER_MITCH] = {
        .trainerClass = TRAINER_CLASS_BIRD_KEEPER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_BIRD_KEEPER,
        .trainerName = _("MITCH"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_BirdKeeperMitch),
    },
    [TRAINER_BIRD_KEEPER_BECK] = {
        .trainerClass = TRAINER_CLASS_BIRD_KEEPER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_BIRD_KEEPER,
        .trainerName = _("BECK"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_BirdKeeperBeck),
    },
    [TRAINER_BIRD_KEEPER_MARLON] = {
        .trainerClass = TRAINER_CLASS_BIRD_KEEPER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_BIRD_KEEPER,
        .trainerName = _("MARLON"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_BirdKeeperMarlon),
    },
    [TRAINER_BLACK_BELT_KOICHI] = {
        .trainerClass = TRAINER_CLASS_BLACK_BELT,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_BLACK_BELT,
        .trainerName = _("KOICHI"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = ITEM_DEFAULT_MOVES(sParty_BlackBeltKoichi),
    },
    [TRAINER_BLACK_BELT_MIKE] = {
        .trainerClass = TRAINER_CLASS_BLACK_BELT,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_BLACK_BELT,
        .trainerName = _("MIKE"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = ITEM_DEFAULT_MOVES(sParty_BlackBeltMike),
    },
    [TRAINER_BLACK_BELT_HIDEKI] = {
        .trainerClass = TRAINER_CLASS_BLACK_BELT,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_BLACK_BELT,
        .trainerName = _("HIDEKI"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = ITEM_DEFAULT_MOVES(sParty_BlackBeltHideki),
    },
    [TRAINER_BLACK_BELT_AARON] = {
        .trainerClass = TRAINER_CLASS_BLACK_BELT,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_BLACK_BELT,
        .trainerName = _("AARON"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = ITEM_DEFAULT_MOVES(sParty_BlackBeltAaron),
    },
    [TRAINER_BLACK_BELT_HITOSHI] = {
        .trainerClass = TRAINER_CLASS_BLACK_BELT,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_BLACK_BELT,
        .trainerName = _("HITOSHI"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = ITEM_DEFAULT_MOVES(sParty_BlackBeltHitoshi),
    },
    [TRAINER_BLACK_BELT_ATSUSHI] = {
        .trainerClass = TRAINER_CLASS_BLACK_BELT,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_BLACK_BELT,
        .trainerName = _("ATSUSHI"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = ITEM_DEFAULT_MOVES(sParty_BlackBeltAtsushi),
    },
    [TRAINER_BLACK_BELT_KIYO] = {
        .trainerClass = TRAINER_CLASS_BLACK_BELT,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_BLACK_BELT,
        .trainerName = _("KIYO"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = ITEM_DEFAULT_MOVES(sParty_BlackBeltKiyo),
    },
    [TRAINER_BLACK_BELT_TAKASHI] = {
        .trainerClass = TRAINER_CLASS_BLACK_BELT,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_BLACK_BELT,
        .trainerName = _("TAKASHI"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = ITEM_DEFAULT_MOVES(sParty_BlackBeltTakashi),
    },
    [TRAINER_BLACK_BELT_DAISUKE] = {
        .trainerClass = TRAINER_CLASS_BLACK_BELT,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_BLACK_BELT,
        .trainerName = _("DAISUKE"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = ITEM_DEFAULT_MOVES(sParty_BlackBeltDaisuke),
    },
    [TRAINER_RIVAL_OAKS_LAB_SQUIRTLE] = {
        .trainerClass = TRAINER_CLASS_RIVAL_EARLY,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_RIVAL_EARLY,
        .trainerName = _("TERRY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_RivalOaksLabSquirtle),
    },
    [TRAINER_RIVAL_OAKS_LAB_BULBASAUR] = {
        .trainerClass = TRAINER_CLASS_RIVAL_EARLY,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_RIVAL_EARLY,
        .trainerName = _("TERRY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_RivalOaksLabBulbasaur),
    },
    [TRAINER_RIVAL_OAKS_LAB_CHARMANDER] = {
        .trainerClass = TRAINER_CLASS_RIVAL_EARLY,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_RIVAL_EARLY,
        .trainerName = _("TERRY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_RivalOaksLabCharmander),
    },
    [TRAINER_RIVAL_ROUTE22_EARLY_SQUIRTLE] = {
        .trainerClass = TRAINER_CLASS_RIVAL_EARLY,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_RIVAL_EARLY,
        .trainerName = _("TERRY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_RivalRoute22EarlySquirtle),
    },
    [TRAINER_RIVAL_ROUTE22_EARLY_BULBASAUR] = {
        .trainerClass = TRAINER_CLASS_RIVAL_EARLY,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_RIVAL_EARLY,
        .trainerName = _("TERRY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_RivalRoute22EarlyBulbasaur),
    },
    [TRAINER_RIVAL_ROUTE22_EARLY_CHARMANDER] = {
        .trainerClass = TRAINER_CLASS_RIVAL_EARLY,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_RIVAL_EARLY,
        .trainerName = _("TERRY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_RivalRoute22EarlyCharmander),
    },
    [TRAINER_RIVAL_CERULEAN_SQUIRTLE] = {
        .trainerClass = TRAINER_CLASS_RIVAL_EARLY,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_RIVAL_EARLY,
        .trainerName = _("TERRY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_RivalCeruleanSquirtle),
    },
    [TRAINER_RIVAL_CERULEAN_BULBASAUR] = {
        .trainerClass = TRAINER_CLASS_RIVAL_EARLY,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_RIVAL_EARLY,
        .trainerName = _("TERRY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_RivalCeruleanBulbasaur),
    },
    [TRAINER_RIVAL_CERULEAN_CHARMANDER] = {
        .trainerClass = TRAINER_CLASS_RIVAL_EARLY,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_RIVAL_EARLY,
        .trainerName = _("TERRY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_RivalCeruleanCharmander),
    },
    [TRAINER_SCIENTIST_TED] = {
        .trainerClass = TRAINER_CLASS_SCIENTIST,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_SCIENTIST,
        .trainerName = _("TED"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_ScientistTed),
    },
    [TRAINER_SCIENTIST_CONNOR] = {
        .trainerClass = TRAINER_CLASS_SCIENTIST,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_SCIENTIST,
        .trainerName = _("CONNOR"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_ScientistConnor),
    },
    [TRAINER_SCIENTIST_JERRY] = {
        .trainerClass = TRAINER_CLASS_SCIENTIST,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_SCIENTIST,
        .trainerName = _("JERRY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_ScientistJerry),
    },
    [TRAINER_SCIENTIST_JOSE] = {
        .trainerClass = TRAINER_CLASS_SCIENTIST,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_SCIENTIST,
        .trainerName = _("JOSE"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_ScientistJose),
    },
    [TRAINER_SCIENTIST_RODNEY] = {
        .trainerClass = TRAINER_CLASS_SCIENTIST,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_SCIENTIST,
        .trainerName = _("RODNEY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_ScientistRodney),
    },
    [TRAINER_SCIENTIST_BEAU] = {
        .trainerClass = TRAINER_CLASS_SCIENTIST,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_SCIENTIST,
        .trainerName = _("BEAU"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_ScientistBeau),
    },
    [TRAINER_SCIENTIST_TAYLOR] = {
        .trainerClass = TRAINER_CLASS_SCIENTIST,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_SCIENTIST,
        .trainerName = _("TAYLOR"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_ScientistTaylor),
    },
    [TRAINER_SCIENTIST_JOSHUA] = {
        .trainerClass = TRAINER_CLASS_SCIENTIST,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_SCIENTIST,
        .trainerName = _("JOSHUA"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_ScientistJoshua),
    },
    [TRAINER_SCIENTIST_PARKER] = {
        .trainerClass = TRAINER_CLASS_SCIENTIST,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_SCIENTIST,
        .trainerName = _("PARKER"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_ScientistParker),
    },
    [TRAINER_SCIENTIST_ED] = {
        .trainerClass = TRAINER_CLASS_SCIENTIST,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_SCIENTIST,
        .trainerName = _("ED"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_ScientistEd),
    },
    [TRAINER_SCIENTIST_TRAVIS] = {
        .trainerClass = TRAINER_CLASS_SCIENTIST,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_SCIENTIST,
        .trainerName = _("TRAVIS"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_ScientistTravis),
    },
    [TRAINER_SCIENTIST_BRAYDON] = {
        .trainerClass = TRAINER_CLASS_SCIENTIST,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_SCIENTIST,
        .trainerName = _("BRAYDON"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_ScientistBraydon),
    },
    [TRAINER_SCIENTIST_IVAN] = {
        .trainerClass = TRAINER_CLASS_SCIENTIST,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_SCIENTIST,
        .trainerName = _("IVAN"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_ScientistIvan),
    },
    [TRAINER_BOSS_GIOVANNI] = {
        .trainerClass = TRAINER_CLASS_BOSS,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .trainerPic = TRAINER_PIC_LEADER_GIOVANNI,
        .trainerName = _("GIOVANNI"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_BossGiovanni),
    },
    [TRAINER_BOSS_GIOVANNI_2] = {
        .trainerClass = TRAINER_CLASS_BOSS,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .trainerPic = TRAINER_PIC_LEADER_GIOVANNI,
        .trainerName = _("GIOVANNI"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_BossGiovanni2),
    },
    [TRAINER_LEADER_GIOVANNI] = {
        .trainerClass = TRAINER_CLASS_LEADER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .trainerPic = TRAINER_PIC_LEADER_GIOVANNI,
        .trainerName = _("GIOVANNI"),
        .items = {ITEM_HYPER_POTION, ITEM_HYPER_POTION, ITEM_FULL_HEAL},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_LeaderGiovanni),
    },
    [TRAINER_TEAM_ROCKET_GRUNT] = {
        .trainerClass = TRAINER_CLASS_TEAM_ROCKET,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_TeamRocketGrunt),
    },
    [TRAINER_TEAM_ROCKET_GRUNT_2] = {
        .trainerClass = TRAINER_CLASS_TEAM_ROCKET,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_TeamRocketGrunt2),
    },
    [TRAINER_TEAM_ROCKET_GRUNT_3] = {
        .trainerClass = TRAINER_CLASS_TEAM_ROCKET,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_TeamRocketGrunt3),
    },
    [TRAINER_TEAM_ROCKET_GRUNT_4] = {
        .trainerClass = TRAINER_CLASS_TEAM_ROCKET,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_TeamRocketGrunt4),
    },
    [TRAINER_TEAM_ROCKET_GRUNT_5] = {
        .trainerClass = TRAINER_CLASS_TEAM_ROCKET,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_TeamRocketGrunt5),
    },
    [TRAINER_TEAM_ROCKET_GRUNT_6] = {
        .trainerClass = TRAINER_CLASS_TEAM_ROCKET,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_TeamRocketGrunt6),
    },
    [TRAINER_TEAM_ROCKET_GRUNT_7] = {
        .trainerClass = TRAINER_CLASS_TEAM_ROCKET,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_TeamRocketGrunt7),
    },
    [TRAINER_TEAM_ROCKET_GRUNT_8] = {
        .trainerClass = TRAINER_CLASS_TEAM_ROCKET,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_TeamRocketGrunt8),
    },
    [TRAINER_TEAM_ROCKET_GRUNT_9] = {
        .trainerClass = TRAINER_CLASS_TEAM_ROCKET,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_TeamRocketGrunt9),
    },
    [TRAINER_TEAM_ROCKET_GRUNT_10] = {
        .trainerClass = TRAINER_CLASS_TEAM_ROCKET,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_TeamRocketGrunt10),
    },
    [TRAINER_TEAM_ROCKET_GRUNT_11] = {
        .trainerClass = TRAINER_CLASS_TEAM_ROCKET,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_TeamRocketGrunt11),
    },
    [TRAINER_TEAM_ROCKET_GRUNT_12] = {
        .trainerClass = TRAINER_CLASS_TEAM_ROCKET,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_TeamRocketGrunt12),
    },
    [TRAINER_TEAM_ROCKET_GRUNT_13] = {
        .trainerClass = TRAINER_CLASS_TEAM_ROCKET,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_TeamRocketGrunt13),
    },
    [TRAINER_TEAM_ROCKET_GRUNT_14] = {
        .trainerClass = TRAINER_CLASS_TEAM_ROCKET,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_TeamRocketGrunt14),
    },
    [TRAINER_TEAM_ROCKET_GRUNT_15] = {
        .trainerClass = TRAINER_CLASS_TEAM_ROCKET,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_TeamRocketGrunt15),
    },
    [TRAINER_TEAM_ROCKET_GRUNT_16] = {
        .trainerClass = TRAINER_CLASS_TEAM_ROCKET,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_TeamRocketGrunt16),
    },
    [TRAINER_TEAM_ROCKET_GRUNT_17] = {
        .trainerClass = TRAINER_CLASS_TEAM_ROCKET,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_TeamRocketGrunt17),
    },
    [TRAINER_TEAM_ROCKET_GRUNT_18] = {
        .trainerClass = TRAINER_CLASS_TEAM_ROCKET,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_TeamRocketGrunt18),
    },
    [TRAINER_TEAM_ROCKET_GRUNT_19] = {
        .trainerClass = TRAINER_CLASS_TEAM_ROCKET,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_TeamRocketGrunt19),
    },
    [TRAINER_TEAM_ROCKET_GRUNT_20] = {
        .trainerClass = TRAINER_CLASS_TEAM_ROCKET,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_TeamRocketGrunt20),
    },
    [TRAINER_TEAM_ROCKET_GRUNT_21] = {
        .trainerClass = TRAINER_CLASS_TEAM_ROCKET,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_TeamRocketGrunt21),
    },
    [TRAINER_TEAM_ROCKET_GRUNT_22] = {
        .trainerClass = TRAINER_CLASS_TEAM_ROCKET,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_TeamRocketGrunt22),
    },
    [TRAINER_TEAM_ROCKET_GRUNT_23] = {
        .trainerClass = TRAINER_CLASS_TEAM_ROCKET,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_TeamRocketGrunt23),
    },
    [TRAINER_TEAM_ROCKET_GRUNT_24] = {
        .trainerClass = TRAINER_CLASS_TEAM_ROCKET,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_TeamRocketGrunt24),
    },
    [TRAINER_TEAM_ROCKET_GRUNT_25] = {
        .trainerClass = TRAINER_CLASS_TEAM_ROCKET,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_TeamRocketGrunt25),
    },
    [TRAINER_TEAM_ROCKET_GRUNT_26] = {
        .trainerClass = TRAINER_CLASS_TEAM_ROCKET,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_TeamRocketGrunt26),
    },
    [TRAINER_TEAM_ROCKET_GRUNT_27] = {
        .trainerClass = TRAINER_CLASS_TEAM_ROCKET,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_TeamRocketGrunt27),
    },
    [TRAINER_TEAM_ROCKET_GRUNT_28] = {
        .trainerClass = TRAINER_CLASS_TEAM_ROCKET,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_TeamRocketGrunt28),
    },
    [TRAINER_TEAM_ROCKET_GRUNT_29] = {
        .trainerClass = TRAINER_CLASS_TEAM_ROCKET,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_TeamRocketGrunt29),
    },
    [TRAINER_TEAM_ROCKET_GRUNT_30] = {
        .trainerClass = TRAINER_CLASS_TEAM_ROCKET,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_TeamRocketGrunt30),
    },
    [TRAINER_TEAM_ROCKET_GRUNT_31] = {
        .trainerClass = TRAINER_CLASS_TEAM_ROCKET,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_TeamRocketGrunt31),
    },
    [TRAINER_TEAM_ROCKET_GRUNT_32] = {
        .trainerClass = TRAINER_CLASS_TEAM_ROCKET,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_TeamRocketGrunt32),
    },
    [TRAINER_TEAM_ROCKET_GRUNT_33] = {
        .trainerClass = TRAINER_CLASS_TEAM_ROCKET,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_TeamRocketGrunt33),
    },
    [TRAINER_TEAM_ROCKET_GRUNT_34] = {
        .trainerClass = TRAINER_CLASS_TEAM_ROCKET,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_TeamRocketGrunt34),
    },
    [TRAINER_TEAM_ROCKET_GRUNT_35] = {
        .trainerClass = TRAINER_CLASS_TEAM_ROCKET,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_TeamRocketGrunt35),
    },
    [TRAINER_TEAM_ROCKET_GRUNT_36] = {
        .trainerClass = TRAINER_CLASS_TEAM_ROCKET,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_TeamRocketGrunt36),
    },
    [TRAINER_TEAM_ROCKET_GRUNT_37] = {
        .trainerClass = TRAINER_CLASS_TEAM_ROCKET,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_TeamRocketGrunt37),
    },
    [TRAINER_TEAM_ROCKET_GRUNT_38] = {
        .trainerClass = TRAINER_CLASS_TEAM_ROCKET,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_TeamRocketGrunt38),
    },
    [TRAINER_TEAM_ROCKET_GRUNT_39] = {
        .trainerClass = TRAINER_CLASS_TEAM_ROCKET,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_TeamRocketGrunt39),
    },
    [TRAINER_TEAM_ROCKET_GRUNT_40] = {
        .trainerClass = TRAINER_CLASS_TEAM_ROCKET,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_TeamRocketGrunt40),
    },
    [TRAINER_TEAM_ROCKET_GRUNT_41] = {
        .trainerClass = TRAINER_CLASS_TEAM_ROCKET,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_TeamRocketGrunt41),
    },
    [TRAINER_COOLTRAINER_SAMUEL] = {
        .trainerClass = TRAINER_CLASS_COOLTRAINER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_COOLTRAINER_M,
        .trainerName = _("SAMUEL"),
        .items = {ITEM_SUPER_POTION},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_CooltrainerSamuel),
    },
    [TRAINER_COOLTRAINER_GEORGE] = {
        .trainerClass = TRAINER_CLASS_COOLTRAINER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_COOLTRAINER_M,
        .trainerName = _("GEORGE"),
        .items = {ITEM_HYPER_POTION},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_CooltrainerGeorge),
    },
    [TRAINER_COOLTRAINER_COLBY] = {
        .trainerClass = TRAINER_CLASS_COOLTRAINER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_COOLTRAINER_M,
        .trainerName = _("COLBY"),
        .items = {ITEM_HYPER_POTION},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_CooltrainerColby),
    },
    [TRAINER_COOLTRAINER_PAUL] = {
        .trainerClass = TRAINER_CLASS_COOLTRAINER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_COOLTRAINER_M,
        .trainerName = _("PAUL"),
        .items = {ITEM_FULL_RESTORE},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_CooltrainerPaul),
    },
    [TRAINER_COOLTRAINER_ROLANDO] = {
        .trainerClass = TRAINER_CLASS_COOLTRAINER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_COOLTRAINER_M,
        .trainerName = _("ROLANDO"),
        .items = {ITEM_HYPER_POTION},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_CooltrainerRolando),
    },
    [TRAINER_COOLTRAINER_GILBERT] = {
        .trainerClass = TRAINER_CLASS_COOLTRAINER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_COOLTRAINER_M,
        .trainerName = _("GILBERT"),
        .items = {ITEM_HYPER_POTION},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_CooltrainerGilbert),
    },
    [TRAINER_COOLTRAINER_OWEN] = {
        .trainerClass = TRAINER_CLASS_COOLTRAINER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_COOLTRAINER_M,
        .trainerName = _("OWEN"),
        .items = {ITEM_HYPER_POTION},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_CooltrainerOwen),
    },
    [TRAINER_COOLTRAINER_BERKE] = {
        .trainerClass = TRAINER_CLASS_COOLTRAINER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_COOLTRAINER_M,
        .trainerName = _("BERKE"),
        .items = {ITEM_FULL_RESTORE},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_CooltrainerBerke),
    },
    [TRAINER_COOLTRAINER_YUJI] = {
        .trainerClass = TRAINER_CLASS_COOLTRAINER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_COOLTRAINER_M,
        .trainerName = _("YUJI"),
        .items = {ITEM_HYPER_POTION},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_CooltrainerYuji),
    },
    [TRAINER_COOLTRAINER_WARREN] = {
        .trainerClass = TRAINER_CLASS_COOLTRAINER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_COOLTRAINER_M,
        .trainerName = _("WARREN"),
        .items = {ITEM_HYPER_POTION},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_CooltrainerWarren),
    },
    [TRAINER_COOLTRAINER_MARY] = {
        .trainerClass = TRAINER_CLASS_COOLTRAINER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_COOL | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_COOLTRAINER_F,
        .trainerName = _("MARY"),
        .items = {ITEM_SUPER_POTION},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_CooltrainerMary),
    },
    [TRAINER_COOLTRAINER_CAROLINE] = {
        .trainerClass = TRAINER_CLASS_COOLTRAINER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_COOL | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_COOLTRAINER_F,
        .trainerName = _("CAROLINE"),
        .items = {ITEM_HYPER_POTION},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_CooltrainerCaroline),
    },
    [TRAINER_COOLTRAINER_ALEXA] = {
        .trainerClass = TRAINER_CLASS_COOLTRAINER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_COOL | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_COOLTRAINER_F,
        .trainerName = _("ALEXA"),
        .items = {ITEM_FULL_RESTORE},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_CooltrainerAlexa),
    },
    [TRAINER_COOLTRAINER_SHANNON] = {
        .trainerClass = TRAINER_CLASS_COOLTRAINER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_COOL | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_COOLTRAINER_F,
        .trainerName = _("SHANNON"),
        .items = {ITEM_FULL_RESTORE},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_CooltrainerShannon),
    },
    [TRAINER_COOLTRAINER_NAOMI] = {
        .trainerClass = TRAINER_CLASS_COOLTRAINER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_COOL | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_COOLTRAINER_F,
        .trainerName = _("NAOMI"),
        .items = {ITEM_HYPER_POTION},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_CooltrainerNaomi),
    },
    [TRAINER_COOLTRAINER_BROOKE] = {
        .trainerClass = TRAINER_CLASS_COOLTRAINER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_COOL | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_COOLTRAINER_F,
        .trainerName = _("BROOKE"),
        .items = {ITEM_FULL_RESTORE},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_CooltrainerBrooke),
    },
    [TRAINER_COOLTRAINER_AUSTINA] = {
        .trainerClass = TRAINER_CLASS_COOLTRAINER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_COOL | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_COOLTRAINER_F,
        .trainerName = _("AUSTINA"),
        .items = {ITEM_FULL_RESTORE},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_CooltrainerAustina),
    },
    [TRAINER_COOLTRAINER_JULIE] = {
        .trainerClass = TRAINER_CLASS_COOLTRAINER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_COOL | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_COOLTRAINER_F,
        .trainerName = _("JULIE"),
        .items = {ITEM_HYPER_POTION},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_CooltrainerJulie),
    },
    [TRAINER_ELITE_FOUR_LORELEI] = {
        .trainerClass = TRAINER_CLASS_ELITE_FOUR,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_ELITE_FOUR | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_ELITE_FOUR_LORELEI,
        .trainerName = _("LORELEI"),
        .items = {ITEM_FULL_RESTORE, ITEM_FULL_RESTORE},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = ITEM_CUSTOM_MOVES(sParty_EliteFourLorelei),
    },
    [TRAINER_ELITE_FOUR_BRUNO] = {
        .trainerClass = TRAINER_CLASS_ELITE_FOUR,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_ELITE_FOUR,
        .trainerPic = TRAINER_PIC_ELITE_FOUR_BRUNO,
        .trainerName = _("BRUNO"),
        .items = {ITEM_FULL_RESTORE, ITEM_FULL_RESTORE},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = ITEM_CUSTOM_MOVES(sParty_EliteFourBruno),
    },
    [TRAINER_ELITE_FOUR_AGATHA] = {
        .trainerClass = TRAINER_CLASS_ELITE_FOUR,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_ELITE_FOUR | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_ELITE_FOUR_AGATHA,
        .trainerName = _("AGATHA"),
        .items = {ITEM_FULL_RESTORE, ITEM_FULL_RESTORE},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = ITEM_CUSTOM_MOVES(sParty_EliteFourAgatha),
    },
    [TRAINER_ELITE_FOUR_LANCE] = {
        .trainerClass = TRAINER_CLASS_ELITE_FOUR,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_ELITE_FOUR,
        .trainerPic = TRAINER_PIC_ELITE_FOUR_LANCE,
        .trainerName = _("LANCE"),
        .items = {ITEM_FULL_RESTORE, ITEM_FULL_RESTORE},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = ITEM_CUSTOM_MOVES(sParty_EliteFourLance),
    },
    [TRAINER_LEADER_BROCK] = {
        .trainerClass = TRAINER_CLASS_LEADER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_LEADER_BROCK,
        .trainerName = _("BROCK"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_LeaderBrock),
    },
    [TRAINER_LEADER_MISTY] = {
        .trainerClass = TRAINER_CLASS_LEADER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_FEMALE | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_LEADER_MISTY,
        .trainerName = _("MISTY"),
        .items = {ITEM_SUPER_POTION},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_LeaderMisty),
    },
    [TRAINER_LEADER_LT_SURGE] = {
        .trainerClass = TRAINER_CLASS_LEADER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_LEADER_LT_SURGE,
        .trainerName = _("LT. SURGE"),
        .items = {ITEM_SUPER_POTION, ITEM_FULL_HEAL},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_LeaderLtSurge),
    },
    [TRAINER_LEADER_ERIKA] = {
        .trainerClass = TRAINER_CLASS_LEADER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_FEMALE | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_LEADER_ERIKA,
        .trainerName = _("ERIKA"),
        .items = {ITEM_HYPER_POTION, ITEM_FULL_HEAL},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_LeaderErika),
    },
    [TRAINER_LEADER_KOGA] = {
        .trainerClass = TRAINER_CLASS_LEADER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_LEADER_KOGA,
        .trainerName = _("KOGA"),
        .items = {ITEM_HYPER_POTION, ITEM_HYPER_POTION, ITEM_FULL_HEAL},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_LeaderKoga),
    },
    [TRAINER_LEADER_BLAINE] = {
        .trainerClass = TRAINER_CLASS_LEADER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_LEADER_BLAINE,
        .trainerName = _("BLAINE"),
        .items = {ITEM_HYPER_POTION, ITEM_HYPER_POTION, ITEM_FULL_HEAL},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_LeaderBlaine),
    },
    [TRAINER_LEADER_SABRINA] = {
        .trainerClass = TRAINER_CLASS_LEADER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_FEMALE | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_LEADER_SABRINA,
        .trainerName = _("SABRINA"),
        .items = {ITEM_HYPER_POTION, ITEM_HYPER_POTION, ITEM_FULL_HEAL},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_LeaderSabrina),
    },
    [TRAINER_GENTLEMAN_THOMAS] = {
        .trainerClass = TRAINER_CLASS_GENTLEMAN,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_RICH,
        .trainerPic = TRAINER_PIC_GENTLEMAN,
        .trainerName = _("THOMAS"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_GentlemanThomas),
    },
    [TRAINER_GENTLEMAN_ARTHUR] = {
        .trainerClass = TRAINER_CLASS_GENTLEMAN,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_RICH,
        .trainerPic = TRAINER_PIC_GENTLEMAN,
        .trainerName = _("ARTHUR"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_GentlemanArthur),
    },
    [TRAINER_GENTLEMAN_TUCKER] = {
        .trainerClass = TRAINER_CLASS_GENTLEMAN,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_RICH,
        .trainerPic = TRAINER_PIC_GENTLEMAN,
        .trainerName = _("TUCKER"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_GentlemanTucker),
    },
    [TRAINER_GENTLEMAN_NORTON] = {
        .trainerClass = TRAINER_CLASS_GENTLEMAN,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_RICH,
        .trainerPic = TRAINER_PIC_GENTLEMAN,
        .trainerName = _("NORTON"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_GentlemanNorton),
    },
    [TRAINER_GENTLEMAN_WALTER] = {
        .trainerClass = TRAINER_CLASS_GENTLEMAN,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_RICH,
        .trainerPic = TRAINER_PIC_GENTLEMAN,
        .trainerName = _("WALTER"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_GentlemanWalter),
    },
    [TRAINER_RIVAL_SS_ANNE_SQUIRTLE] = {
        .trainerClass = TRAINER_CLASS_RIVAL_LATE,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_RIVAL_LATE,
        .trainerName = _("TERRY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_RivalSsAnneSquirtle),
    },
    [TRAINER_RIVAL_SS_ANNE_BULBASAUR] = {
        .trainerClass = TRAINER_CLASS_RIVAL_LATE,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_RIVAL_LATE,
        .trainerName = _("TERRY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_RivalSsAnneBulbasaur),
    },
    [TRAINER_RIVAL_SS_ANNE_CHARMANDER] = {
        .trainerClass = TRAINER_CLASS_RIVAL_LATE,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_RIVAL_LATE,
        .trainerName = _("TERRY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_RivalSsAnneCharmander),
    },
    [TRAINER_RIVAL_POKEMON_TOWER_SQUIRTLE] = {
        .trainerClass = TRAINER_CLASS_RIVAL_LATE,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_RIVAL_LATE,
        .trainerName = _("TERRY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_RivalPokemonTowerSquirtle),
    },
    [TRAINER_RIVAL_POKEMON_TOWER_BULBASAUR] = {
        .trainerClass = TRAINER_CLASS_RIVAL_LATE,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_RIVAL_LATE,
        .trainerName = _("TERRY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_RivalPokemonTowerBulbasaur),
    },
    [TRAINER_RIVAL_POKEMON_TOWER_CHARMANDER] = {
        .trainerClass = TRAINER_CLASS_RIVAL_LATE,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_RIVAL_LATE,
        .trainerName = _("TERRY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_RivalPokemonTowerCharmander),
    },
    [TRAINER_RIVAL_SILPH_SQUIRTLE] = {
        .trainerClass = TRAINER_CLASS_RIVAL_LATE,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_RIVAL_LATE,
        .trainerName = _("TERRY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_RivalSilphSquirtle),
    },
    [TRAINER_RIVAL_SILPH_BULBASAUR] = {
        .trainerClass = TRAINER_CLASS_RIVAL_LATE,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_RIVAL_LATE,
        .trainerName = _("TERRY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_RivalSilphBulbasaur),
    },
    [TRAINER_RIVAL_SILPH_CHARMANDER] = {
        .trainerClass = TRAINER_CLASS_RIVAL_LATE,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_RIVAL_LATE,
        .trainerName = _("TERRY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_RivalSilphCharmander),
    },
    [TRAINER_RIVAL_ROUTE22_LATE_SQUIRTLE] = {
        .trainerClass = TRAINER_CLASS_RIVAL_LATE,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_RIVAL_LATE,
        .trainerName = _("TERRY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_RivalRoute22LateSquirtle),
    },
    [TRAINER_RIVAL_ROUTE22_LATE_BULBASAUR] = {
        .trainerClass = TRAINER_CLASS_RIVAL_LATE,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_RIVAL_LATE,
        .trainerName = _("TERRY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_RivalRoute22LateBulbasaur),
    },
    [TRAINER_RIVAL_ROUTE22_LATE_CHARMANDER] = {
        .trainerClass = TRAINER_CLASS_RIVAL_LATE,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_RIVAL_LATE,
        .trainerName = _("TERRY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_RivalRoute22LateCharmander),
    },
    [TRAINER_CHAMPION_FIRST_SQUIRTLE] = {
        .trainerClass = TRAINER_CLASS_CHAMPION,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_CHAMPION_RIVAL,
        .trainerName = _("TERRY"),
        .items = {ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = ITEM_CUSTOM_MOVES(sParty_ChampionFirstSquirtle),
    },
    [TRAINER_CHAMPION_FIRST_BULBASAUR] = {
        .trainerClass = TRAINER_CLASS_CHAMPION,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_CHAMPION_RIVAL,
        .trainerName = _("TERRY"),
        .items = {ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = ITEM_CUSTOM_MOVES(sParty_ChampionFirstBulbasaur),
    },
    [TRAINER_CHAMPION_FIRST_CHARMANDER] = {
        .trainerClass = TRAINER_CLASS_CHAMPION,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_CHAMPION_RIVAL,
        .trainerName = _("TERRY"),
        .items = {ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = ITEM_CUSTOM_MOVES(sParty_ChampionFirstCharmander),
    },
    [TRAINER_CHANNELER_PATRICIA] = {
        .trainerClass = TRAINER_CLASS_CHANNELER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_CHANNELER,
        .trainerName = _("PATRICIA"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_ChannelerPatricia),
    },
    [TRAINER_CHANNELER_CARLY] = {
        .trainerClass = TRAINER_CLASS_CHANNELER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_CHANNELER,
        .trainerName = _("CARLY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_ChannelerCarly),
    },
    [TRAINER_CHANNELER_HOPE] = {
        .trainerClass = TRAINER_CLASS_CHANNELER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_CHANNELER,
        .trainerName = _("HOPE"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_ChannelerHope),
    },
    [TRAINER_CHANNELER_PAULA] = {
        .trainerClass = TRAINER_CLASS_CHANNELER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_CHANNELER,
        .trainerName = _("PAULA"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_ChannelerPaula),
    },
    [TRAINER_CHANNELER_LAUREL] = {
        .trainerClass = TRAINER_CLASS_CHANNELER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_CHANNELER,
        .trainerName = _("LAUREL"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_ChannelerLaurel),
    },
    [TRAINER_CHANNELER_JODY] = {
        .trainerClass = TRAINER_CLASS_CHANNELER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_CHANNELER,
        .trainerName = _("JODY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_ChannelerJody),
    },
    [TRAINER_CHANNELER_TAMMY] = {
        .trainerClass = TRAINER_CLASS_CHANNELER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_CHANNELER,
        .trainerName = _("TAMMY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_ChannelerTammy),
    },
    [TRAINER_CHANNELER_RUTH] = {
        .trainerClass = TRAINER_CLASS_CHANNELER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_CHANNELER,
        .trainerName = _("RUTH"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_ChannelerRuth),
    },
    [TRAINER_CHANNELER_KARINA] = {
        .trainerClass = TRAINER_CLASS_CHANNELER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_CHANNELER,
        .trainerName = _("KARINA"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_ChannelerKarina),
    },
    [TRAINER_CHANNELER_JANAE] = {
        .trainerClass = TRAINER_CLASS_CHANNELER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_CHANNELER,
        .trainerName = _("JANAE"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_ChannelerJanae),
    },
    [TRAINER_CHANNELER_ANGELICA] = {
        .trainerClass = TRAINER_CLASS_CHANNELER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_CHANNELER,
        .trainerName = _("ANGELICA"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_ChannelerAngelica),
    },
    [TRAINER_CHANNELER_EMILIA] = {
        .trainerClass = TRAINER_CLASS_CHANNELER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_CHANNELER,
        .trainerName = _("EMILIA"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_ChannelerEmilia),
    },
    [TRAINER_CHANNELER_JENNIFER] = {
        .trainerClass = TRAINER_CLASS_CHANNELER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_CHANNELER,
        .trainerName = _("JENNIFER"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_ChannelerJennifer),
    },
    [TRAINER_CHANNELER_1] = {
        .trainerClass = TRAINER_CLASS_CHANNELER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_CHANNELER,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_Channeler1),
    },
    [TRAINER_CHANNELER_2] = {
        .trainerClass = TRAINER_CLASS_CHANNELER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_CHANNELER,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_Channeler2),
    },
    [TRAINER_CHANNELER_3] = {
        .trainerClass = TRAINER_CLASS_CHANNELER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_CHANNELER,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_Channeler3),
    },
    [TRAINER_CHANNELER_4] = {
        .trainerClass = TRAINER_CLASS_CHANNELER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_CHANNELER,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_Channeler4),
    },
    [TRAINER_CHANNELER_5] = {
        .trainerClass = TRAINER_CLASS_CHANNELER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_CHANNELER,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_Channeler5),
    },
    [TRAINER_CHANNELER_6] = {
        .trainerClass = TRAINER_CLASS_CHANNELER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_CHANNELER,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_Channeler6),
    },
    [TRAINER_CHANNELER_7] = {
        .trainerClass = TRAINER_CLASS_CHANNELER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_CHANNELER,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_Channeler7),
    },
    [TRAINER_CHANNELER_8] = {
        .trainerClass = TRAINER_CLASS_CHANNELER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_CHANNELER,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_Channeler8),
    },
    [TRAINER_CHANNELER_AMANDA] = {
        .trainerClass = TRAINER_CLASS_CHANNELER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_CHANNELER,
        .trainerName = _("AMANDA"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_ChannelerAmanda),
    },
    [TRAINER_CHANNELER_STACY] = {
        .trainerClass = TRAINER_CLASS_CHANNELER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_CHANNELER,
        .trainerName = _("STACY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_ChannelerStacy),
    },
    [TRAINER_CHANNELER_TASHA] = {
        .trainerClass = TRAINER_CLASS_CHANNELER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_CHANNELER,
        .trainerName = _("TASHA"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_ChannelerTasha),
    },
    [TRAINER_HIKER_JEREMY] = {
        .trainerClass = TRAINER_CLASS_HIKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_HIKER,
        .trainerName = _("JEREMY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_HikerJeremy),
    },
    [TRAINER_PICNICKER_ALMA] = {
        .trainerClass = TRAINER_CLASS_PICNICKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_GIRL | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = _("ALMA"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_PicnickerAlma),
    },
    [TRAINER_PICNICKER_SUSIE] = {
        .trainerClass = TRAINER_CLASS_PICNICKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_GIRL | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = _("SUSIE"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_PicnickerSusie),
    },
    [TRAINER_PICNICKER_VALERIE] = {
        .trainerClass = TRAINER_CLASS_PICNICKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_GIRL | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = _("VALERIE"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_PicnickerValerie),
    },
    [TRAINER_PICNICKER_GWEN] = {
        .trainerClass = TRAINER_CLASS_PICNICKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_GIRL | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = _("GWEN"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_PicnickerGwen),
    },
    [TRAINER_BIKER_VIRGIL] = {
        .trainerClass = TRAINER_CLASS_BIKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BIKER,
        .trainerName = _("VIRGIL"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_BikerVirgil),
    },
    [TRAINER_CAMPER_FLINT] = {
        .trainerClass = TRAINER_CLASS_CAMPER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_CAMPER,
        .trainerName = _("FLINT"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_CamperFlint),
    },
    [TRAINER_PICNICKER_MISSY] = {
        .trainerClass = TRAINER_CLASS_PICNICKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_GIRL | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = _("MISSY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_PicnickerMissy),
    },
    [TRAINER_PICNICKER_IRENE] = {
        .trainerClass = TRAINER_CLASS_PICNICKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_GIRL | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = _("IRENE"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_PicnickerIrene),
    },
    [TRAINER_PICNICKER_DANA] = {
        .trainerClass = TRAINER_CLASS_PICNICKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_GIRL | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = _("DANA"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_PicnickerDana),
    },
    [TRAINER_PICNICKER_ARIANA] = {
        .trainerClass = TRAINER_CLASS_PICNICKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_GIRL | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = _("ARIANA"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_PicnickerAriana),
    },
    [TRAINER_PICNICKER_LEAH] = {
        .trainerClass = TRAINER_CLASS_PICNICKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_GIRL | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = _("LEAH"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_PicnickerLeah),
    },
    [TRAINER_CAMPER_JUSTIN] = {
        .trainerClass = TRAINER_CLASS_CAMPER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_CAMPER,
        .trainerName = _("JUSTIN"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_CamperJustin),
    },
    [TRAINER_PICNICKER_YAZMIN] = {
        .trainerClass = TRAINER_CLASS_PICNICKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_GIRL | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = _("YAZMIN"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_PicnickerYazmin),
    },
    [TRAINER_PICNICKER_KINDRA] = {
        .trainerClass = TRAINER_CLASS_PICNICKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_GIRL | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = _("KINDRA"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_PicnickerKindra),
    },
    [TRAINER_PICNICKER_BECKY] = {
        .trainerClass = TRAINER_CLASS_PICNICKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_GIRL | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = _("BECKY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_PicnickerBecky),
    },
    [TRAINER_PICNICKER_CELIA] = {
        .trainerClass = TRAINER_CLASS_PICNICKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_GIRL | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = _("CELIA"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_PicnickerCelia),
    },
    [TRAINER_GENTLEMAN_BROOKS] = {
        .trainerClass = TRAINER_CLASS_GENTLEMAN,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_RICH,
        .trainerPic = TRAINER_PIC_GENTLEMAN,
        .trainerName = _("BROOKS"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_GentlemanBrooks),
    },
    [TRAINER_GENTLEMAN_LAMAR] = {
        .trainerClass = TRAINER_CLASS_GENTLEMAN,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_RICH,
        .trainerPic = TRAINER_PIC_GENTLEMAN,
        .trainerName = _("LAMAR"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_GentlemanLamar),
    },
    [TRAINER_TWINS_ELI_ANNE] = {
        .trainerClass = TRAINER_CLASS_TWINS,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_TWINS,
        .trainerPic = TRAINER_PIC_TWINS,
        .trainerName = _("ELI & ANNE"),
        .items = {},
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_TwinsEliAnne),
    },
    [TRAINER_COOL_COUPLE_RAY_TYRA] = {
        .trainerClass = TRAINER_CLASS_COOL_COUPLE,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_COOL_COUPLE,
        .trainerName = _("RAY & TYRA"),
        .items = {},
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_CoolCoupleRayTyra),
    },
    [TRAINER_YOUNG_COUPLE_GIA_JES] = {
        .trainerClass = TRAINER_CLASS_YOUNG_COUPLE,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_GIRL,
        .trainerPic = TRAINER_PIC_YOUNG_COUPLE,
        .trainerName = _("GIA & JES"),
        .items = {},
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_YoungCoupleGiaJes),
    },
    [TRAINER_TWINS_KIRI_JAN] = {
        .trainerClass = TRAINER_CLASS_TWINS,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_TWINS,
        .trainerPic = TRAINER_PIC_TWINS,
        .trainerName = _("KIRI & JAN"),
        .items = {},
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_TwinsKiriJan),
    },
    [TRAINER_CRUSH_KIN_RON_MYA] = {
        .trainerClass = TRAINER_CLASS_CRUSH_KIN,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_CRUSH_KIN,
        .trainerName = _("RON & MYA"),
        .items = {},
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = ITEM_DEFAULT_MOVES(sParty_CrushKinRonMya),
    },
    [TRAINER_YOUNG_COUPLE_LEA_JED] = {
        .trainerClass = TRAINER_CLASS_YOUNG_COUPLE,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_GIRL,
        .trainerPic = TRAINER_PIC_YOUNG_COUPLE,
        .trainerName = _("LEA & JED"),
        .items = {},
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_YoungCoupleLeaJed),
    },
    [TRAINER_SIS_AND_BRO_LIA_LUC] = {
        .trainerClass = TRAINER_CLASS_SIS_AND_BRO,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SIS_AND_BRO,
        .trainerName = _("LIA & LUC"),
        .items = {},
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_SisAndBroLiaLuc),
    },
    [TRAINER_SIS_AND_BRO_LIL_IAN] = {
        .trainerClass = TRAINER_CLASS_SIS_AND_BRO,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SIS_AND_BRO,
        .trainerName = _("LIL & IAN"),
        .items = {},
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_SisAndBroLilIan),
    },
    [TRAINER_BUG_CATCHER_3] = {
        .trainerClass = TRAINER_CLASS_BUG_CATCHER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BUG_CATCHER,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_BugCatcher3),
    },
    [TRAINER_BUG_CATCHER_4] = {
        .trainerClass = TRAINER_CLASS_BUG_CATCHER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BUG_CATCHER,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_BugCatcher4),
    },
    [TRAINER_BUG_CATCHER_5] = {
        .trainerClass = TRAINER_CLASS_BUG_CATCHER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BUG_CATCHER,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_BugCatcher5),
    },
    [TRAINER_BUG_CATCHER_6] = {
        .trainerClass = TRAINER_CLASS_BUG_CATCHER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BUG_CATCHER,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_BugCatcher6),
    },
    [TRAINER_BUG_CATCHER_7] = {
        .trainerClass = TRAINER_CLASS_BUG_CATCHER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BUG_CATCHER,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_BugCatcher7),
    },
    [TRAINER_BUG_CATCHER_8] = {
        .trainerClass = TRAINER_CLASS_BUG_CATCHER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BUG_CATCHER,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_BugCatcher8),
    },
    [TRAINER_YOUNGSTER_BEN_3] = {
        .trainerClass = TRAINER_CLASS_YOUNGSTER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_YOUNGSTER,
        .trainerName = _("BEN"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_YoungsterBen3),
    },
    [TRAINER_YOUNGSTER_BEN_4] = {
        .trainerClass = TRAINER_CLASS_YOUNGSTER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_YOUNGSTER,
        .trainerName = _("BEN"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_YoungsterBen4),
    },
    [TRAINER_YOUNGSTER_CHAD_2] = {
        .trainerClass = TRAINER_CLASS_YOUNGSTER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_YOUNGSTER,
        .trainerName = _("CHAD"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_YoungsterChad2),
    },
    [TRAINER_LASS_RELI_2] = {
        .trainerClass = TRAINER_CLASS_LASS,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_FEMALE | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_LASS,
        .trainerName = _("RELI"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_LassReli2),
    },
    [TRAINER_LASS_RELI_3] = {
        .trainerClass = TRAINER_CLASS_LASS,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_FEMALE | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_LASS,
        .trainerName = _("RELI"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_LassReli3),
    },
    [TRAINER_YOUNGSTER_TIMMY_2] = {
        .trainerClass = TRAINER_CLASS_YOUNGSTER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_YOUNGSTER,
        .trainerName = _("TIMMY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_YoungsterTimmy2),
    },
    [TRAINER_YOUNGSTER_TIMMY_3] = {
        .trainerClass = TRAINER_CLASS_YOUNGSTER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_YOUNGSTER,
        .trainerName = _("TIMMY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_YoungsterTimmy3),
    },
    [TRAINER_YOUNGSTER_TIMMY_4] = {
        .trainerClass = TRAINER_CLASS_YOUNGSTER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_YOUNGSTER,
        .trainerName = _("TIMMY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_YoungsterTimmy4),
    },
    [TRAINER_YOUNGSTER_CHAD_3] = {
        .trainerClass = TRAINER_CLASS_YOUNGSTER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_YOUNGSTER,
        .trainerName = _("CHAD"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_YoungsterChad3),
    },
    [TRAINER_LASS_JANICE_2] = {
        .trainerClass = TRAINER_CLASS_LASS,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_FEMALE | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_LASS,
        .trainerName = _("JANICE"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_LassJanice2),
    },
    [TRAINER_LASS_JANICE_3] = {
        .trainerClass = TRAINER_CLASS_LASS,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_FEMALE | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_LASS,
        .trainerName = _("JANICE"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_LassJanice3),
    },
    [TRAINER_YOUNGSTER_CHAD_4] = {
        .trainerClass = TRAINER_CLASS_YOUNGSTER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_YOUNGSTER,
        .trainerName = _("CHAD"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_YoungsterChad4),
    },
    [TRAINER_HIKER_FRANKLIN_2] = {
        .trainerClass = TRAINER_CLASS_HIKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_HIKER,
        .trainerName = _("FRANKLIN"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_HikerFranklin2),
    },
    [TRAINER_PKMN_PROF_PROF_OAK] = {
        .trainerClass = TRAINER_CLASS_PKMN_PROF,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_PROFESSOR_OAK,
        .trainerName = _("PROF. OAK"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_PkmnProfProfOak),
    },
    [TRAINER_PLAYER_BRENDAN] = {
        .trainerClass = TRAINER_CLASS_PLAYER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_RS_BRENDAN_2,
        .trainerName = _("BRENDAN"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_PlayerBrendan),
    },
    [TRAINER_PLAYER_MAY] = {
        .trainerClass = TRAINER_CLASS_PLAYER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_RS_MAY_2,
        .trainerName = _("MAY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_PlayerMay),
    },
    [TRAINER_PLAYER_RED] = {
        .trainerClass = TRAINER_CLASS_PLAYER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_RED,
        .trainerName = _("RED"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_PlayerRed),
    },
    [TRAINER_PLAYER_LEAF] = {
        .trainerClass = TRAINER_CLASS_PLAYER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_LEAF,
        .trainerName = _("LEAF"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_PlayerLeaf),
    },
    [TRAINER_TEAM_ROCKET_GRUNT_42] = {
        .trainerClass = TRAINER_CLASS_TEAM_ROCKET,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_F,
        .trainerName = _("GRUNT"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_TeamRocketGrunt42),
    },
    [TRAINER_PSYCHIC_JACLYN] = {
        .trainerClass = TRAINER_CLASS_PSYCHIC,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_INTENSE | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_PSYCHIC_F,
        .trainerName = _("JACLYN"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_PsychicJaclyn),
    },
    [TRAINER_CRUSH_GIRL_SHARON] = {
        .trainerClass = TRAINER_CLASS_CRUSH_GIRL,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_CRUSH_GIRL,
        .trainerName = _("SHARON"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = ITEM_DEFAULT_MOVES(sParty_CrushGirlSharon),
    },
    [TRAINER_TUBER_AMIRA] = {
        .trainerClass = TRAINER_CLASS_TUBER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_GIRL,
        .trainerPic = TRAINER_PIC_TUBER_F,
        .trainerName = _("AMIRA"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_TuberAmira),
    },
    [TRAINER_PKMN_BREEDER_ALIZE] = {
        .trainerClass = TRAINER_CLASS_PKMN_BREEDER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_POKEMON_BREEDER,
        .trainerName = _("ALIZE"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_PkmnBreederAlize),
    },
    [TRAINER_PKMN_RANGER_NICOLAS] = {
        .trainerClass = TRAINER_CLASS_PKMN_RANGER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_POKEMON_RANGER_M,
        .trainerName = _("NICOLAS"),
        .items = {ITEM_FULL_RESTORE},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_PkmnRangerNicolas),
    },
    [TRAINER_PKMN_RANGER_MADELINE] = {
        .trainerClass = TRAINER_CLASS_PKMN_RANGER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_COOL | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_POKEMON_RANGER_F,
        .trainerName = _("MADELINE"),
        .items = {ITEM_FULL_RESTORE},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_PkmnRangerMadeline),
    },
    [TRAINER_AROMA_LADY_NIKKI] = {
        .trainerClass = TRAINER_CLASS_AROMA_LADY,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_FEMALE | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_AROMA_LADY,
        .trainerName = _("NIKKI"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_AromaLadyNikki),
    },
    [TRAINER_RUIN_MANIAC_STANLY] = {
        .trainerClass = TRAINER_CLASS_RUIN_MANIAC,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_RUIN_MANIAC,
        .trainerName = _("STANLY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_RuinManiacStanly),
    },
    [TRAINER_LADY_JACKI] = {
        .trainerClass = TRAINER_CLASS_LADY,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_LADY,
        .trainerName = _("JACKI"),
        .items = {ITEM_FULL_RESTORE},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = ITEM_DEFAULT_MOVES(sParty_LadyJacki),
    },
    [TRAINER_PAINTER_DAISY] = {
        .trainerClass = TRAINER_CLASS_PAINTER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_PAINTER,
        .trainerName = _("DAISY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_PainterDaisy),
    },
    [TRAINER_BIKER_GOON] = {
        .trainerClass = TRAINER_CLASS_BIKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BIKER,
        .trainerName = _("GOON"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_BikerGoon),
    },
    [TRAINER_BIKER_GOON_2] = {
        .trainerClass = TRAINER_CLASS_BIKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BIKER,
        .trainerName = _("GOON"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_BikerGoon2),
    },
    [TRAINER_BIKER_GOON_3] = {
        .trainerClass = TRAINER_CLASS_BIKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BIKER,
        .trainerName = _("GOON"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_BikerGoon3),
    },
    [TRAINER_BIKER_2] = {
        .trainerClass = TRAINER_CLASS_BIKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BIKER,
        .trainerName = _(""),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_Biker2),
    },
    [TRAINER_BUG_CATCHER_ANTHONY] = {
        .trainerClass = TRAINER_CLASS_BUG_CATCHER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BUG_CATCHER,
        .trainerName = _("ANTHONY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_BugCatcherAnthony),
    },
    [TRAINER_BUG_CATCHER_CHARLIE] = {
        .trainerClass = TRAINER_CLASS_BUG_CATCHER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BUG_CATCHER,
        .trainerName = _("CHARLIE"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_BugCatcherCharlie),
    },
    [TRAINER_TWINS_ELI_ANNE_2] = {
        .trainerClass = TRAINER_CLASS_TWINS,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_TWINS,
        .trainerPic = TRAINER_PIC_TWINS,
        .trainerName = _("ELI & ANNE"),
        .items = {},
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_TwinsEliAnne2),
    },
    [TRAINER_YOUNGSTER_JOHNSON] = {
        .trainerClass = TRAINER_CLASS_YOUNGSTER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_YOUNGSTER,
        .trainerName = _("JOHNSON"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_YoungsterJohnson),
    },
    [TRAINER_BIKER_RICARDO] = {
        .trainerClass = TRAINER_CLASS_BIKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BIKER,
        .trainerName = _("RICARDO"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_BikerRicardo),
    },
    [TRAINER_BIKER_JAREN] = {
        .trainerClass = TRAINER_CLASS_BIKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BIKER,
        .trainerName = _("JAREN"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_BikerJaren),
    },
    [TRAINER_TEAM_ROCKET_GRUNT_43] = {
        .trainerClass = TRAINER_CLASS_TEAM_ROCKET,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_TeamRocketGrunt43),
    },
    [TRAINER_TEAM_ROCKET_GRUNT_44] = {
        .trainerClass = TRAINER_CLASS_TEAM_ROCKET,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_TeamRocketGrunt44),
    },
    [TRAINER_TEAM_ROCKET_GRUNT_45] = {
        .trainerClass = TRAINER_CLASS_TEAM_ROCKET,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_TeamRocketGrunt45),
    },
    [TRAINER_TEAM_ROCKET_GRUNT_46] = {
        .trainerClass = TRAINER_CLASS_TEAM_ROCKET,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_TeamRocketGrunt46),
    },
    [TRAINER_TEAM_ROCKET_GRUNT_47] = {
        .trainerClass = TRAINER_CLASS_TEAM_ROCKET,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_TeamRocketGrunt47),
    },
    [TRAINER_TEAM_ROCKET_GRUNT_48] = {
        .trainerClass = TRAINER_CLASS_TEAM_ROCKET,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_TeamRocketGrunt48),
    },
    [TRAINER_TEAM_ROCKET_ADMIN] = {
        .trainerClass = TRAINER_CLASS_TEAM_ROCKET,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_F,
        .trainerName = _("ADMIN"),
        .items = {ITEM_HYPER_POTION},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_TeamRocketAdmin),
    },
    [TRAINER_TEAM_ROCKET_ADMIN_2] = {
        .trainerClass = TRAINER_CLASS_TEAM_ROCKET,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("ADMIN"),
        .items = {ITEM_HYPER_POTION},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_TeamRocketAdmin2),
    },
    [TRAINER_SCIENTIST_GIDEON] = {
        .trainerClass = TRAINER_CLASS_SCIENTIST,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_SCIENTIST,
        .trainerName = _("GIDEON"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_ScientistGideon),
    },
    [TRAINER_SWIMMER_FEMALE_AMARA] = {
        .trainerClass = TRAINER_CLASS_SWIMMER_F,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_FEMALE | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_SWIMMER_F,
        .trainerName = _("AMARA"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_SwimmerFemaleAmara),
    },
    [TRAINER_SWIMMER_FEMALE_MARIA] = {
        .trainerClass = TRAINER_CLASS_SWIMMER_F,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_FEMALE | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_SWIMMER_F,
        .trainerName = _("MARIA"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_SwimmerFemaleMaria),
    },
    [TRAINER_SWIMMER_FEMALE_ABIGAIL] = {
        .trainerClass = TRAINER_CLASS_SWIMMER_F,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_FEMALE | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_SWIMMER_F,
        .trainerName = _("ABIGAIL"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_SwimmerFemaleAbigail),
    },
    [TRAINER_SWIMMER_MALE_FINN] = {
        .trainerClass = TRAINER_CLASS_SWIMMER_M,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = _("FINN"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_SwimmerMaleFinn),
    },
    [TRAINER_SWIMMER_MALE_GARRETT] = {
        .trainerClass = TRAINER_CLASS_SWIMMER_M,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = _("GARRETT"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_SwimmerMaleGarrett),
    },
    [TRAINER_FISHERMAN_TOMMY] = {
        .trainerClass = TRAINER_CLASS_FISHERMAN,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_FISHERMAN,
        .trainerName = _("TOMMY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_FishermanTommy),
    },
    [TRAINER_CRUSH_GIRL_TANYA] = {
        .trainerClass = TRAINER_CLASS_CRUSH_GIRL,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_CRUSH_GIRL,
        .trainerName = _("TANYA"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = ITEM_DEFAULT_MOVES(sParty_CrushGirlTanya),
    },
    [TRAINER_BLACK_BELT_SHEA] = {
        .trainerClass = TRAINER_CLASS_BLACK_BELT,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_BLACK_BELT,
        .trainerName = _("SHEA"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = ITEM_DEFAULT_MOVES(sParty_BlackBeltShea),
    },
    [TRAINER_BLACK_BELT_HUGH] = {
        .trainerClass = TRAINER_CLASS_BLACK_BELT,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_BLACK_BELT,
        .trainerName = _("HUGH"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = ITEM_DEFAULT_MOVES(sParty_BlackBeltHugh),
    },
    [TRAINER_CAMPER_BRYCE] = {
        .trainerClass = TRAINER_CLASS_CAMPER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_CAMPER,
        .trainerName = _("BRYCE"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_CamperBryce),
    },
    [TRAINER_PICNICKER_CLAIRE] = {
        .trainerClass = TRAINER_CLASS_PICNICKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_GIRL | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = _("CLAIRE"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_PicnickerClaire),
    },
    [TRAINER_CRUSH_KIN_MIK_KIA] = {
        .trainerClass = TRAINER_CLASS_CRUSH_KIN,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_CRUSH_KIN,
        .trainerName = _("MIK & KIA"),
        .items = {},
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = ITEM_DEFAULT_MOVES(sParty_CrushKinMikKia),
    },
    [TRAINER_AROMA_LADY_VIOLET] = {
        .trainerClass = TRAINER_CLASS_AROMA_LADY,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_FEMALE | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_AROMA_LADY,
        .trainerName = _("VIOLET"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_AromaLadyViolet),
    },
    [TRAINER_TUBER_ALEXIS] = {
        .trainerClass = TRAINER_CLASS_TUBER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_GIRL,
        .trainerPic = TRAINER_PIC_TUBER_F,
        .trainerName = _("ALEXIS"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_TuberAlexis),
    },
    [TRAINER_TWINS_JOY_MEG] = {
        .trainerClass = TRAINER_CLASS_TWINS,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_TWINS,
        .trainerPic = TRAINER_PIC_TWINS,
        .trainerName = _("JOY & MEG"),
        .items = {},
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_TwinsJoyMeg),
    },
    [TRAINER_SWIMMER_FEMALE_TISHA] = {
        .trainerClass = TRAINER_CLASS_SWIMMER_F,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_FEMALE | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_SWIMMER_F,
        .trainerName = _("TISHA"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_SwimmerFemaleTisha),
    },
    [TRAINER_PAINTER_CELINA] = {
        .trainerClass = TRAINER_CLASS_PAINTER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_PAINTER,
        .trainerName = _("CELINA"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_PainterCelina),
    },
    [TRAINER_PAINTER_RAYNA] = {
        .trainerClass = TRAINER_CLASS_PAINTER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_PAINTER,
        .trainerName = _("RAYNA"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_PainterRayna),
    },
    [TRAINER_LADY_GILLIAN] = {
        .trainerClass = TRAINER_CLASS_LADY,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_LADY,
        .trainerName = _("GILLIAN"),
        .items = {ITEM_FULL_RESTORE},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = ITEM_DEFAULT_MOVES(sParty_LadyGillian),
    },
    [TRAINER_YOUNGSTER_DESTIN] = {
        .trainerClass = TRAINER_CLASS_YOUNGSTER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_YOUNGSTER,
        .trainerName = _("DESTIN"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_YoungsterDestin),
    },
    [TRAINER_SWIMMER_MALE_TOBY] = {
        .trainerClass = TRAINER_CLASS_SWIMMER_M,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = _("TOBY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_SwimmerMaleToby),
    },
    [TRAINER_TEAM_ROCKET_GRUNT_49] = {
        .trainerClass = TRAINER_CLASS_TEAM_ROCKET,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_TeamRocketGrunt49),
    },
    [TRAINER_TEAM_ROCKET_GRUNT_50] = {
        .trainerClass = TRAINER_CLASS_TEAM_ROCKET,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_M,
        .trainerName = _("GRUNT"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_TeamRocketGrunt50),
    },
    [TRAINER_TEAM_ROCKET_GRUNT_51] = {
        .trainerClass = TRAINER_CLASS_TEAM_ROCKET,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_AQUA,
        .trainerPic = TRAINER_PIC_ROCKET_GRUNT_F,
        .trainerName = _("GRUNT"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_TeamRocketGrunt51),
    },
    [TRAINER_BIRD_KEEPER_MILO] = {
        .trainerClass = TRAINER_CLASS_BIRD_KEEPER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_BIRD_KEEPER,
        .trainerName = _("MILO"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_BirdKeeperMilo),
    },
    [TRAINER_BIRD_KEEPER_CHAZ] = {
        .trainerClass = TRAINER_CLASS_BIRD_KEEPER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_BIRD_KEEPER,
        .trainerName = _("CHAZ"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_BirdKeeperChaz),
    },
    [TRAINER_BIRD_KEEPER_HAROLD] = {
        .trainerClass = TRAINER_CLASS_BIRD_KEEPER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_BIRD_KEEPER,
        .trainerName = _("HAROLD"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_BirdKeeperHarold),
    },
    [TRAINER_FISHERMAN_TYLOR] = {
        .trainerClass = TRAINER_CLASS_FISHERMAN,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_FISHERMAN,
        .trainerName = _("TYLOR"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_FishermanTylor),
    },
    [TRAINER_SWIMMER_MALE_MYMO] = {
        .trainerClass = TRAINER_CLASS_SWIMMER_M,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = _("MYMO"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_SwimmerMaleMymo),
    },
    [TRAINER_SWIMMER_FEMALE_NICOLE] = {
        .trainerClass = TRAINER_CLASS_SWIMMER_F,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_FEMALE | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_SWIMMER_F,
        .trainerName = _("NICOLE"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_SwimmerFemaleNicole),
    },
    [TRAINER_SIS_AND_BRO_AVA_GEB] = {
        .trainerClass = TRAINER_CLASS_SIS_AND_BRO,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SIS_AND_BRO,
        .trainerName = _("AVA & GEB"),
        .items = {},
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_SisAndBroAvaGeb),
    },
    [TRAINER_AROMA_LADY_ROSE] = {
        .trainerClass = TRAINER_CLASS_AROMA_LADY,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_FEMALE | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_AROMA_LADY,
        .trainerName = _("ROSE"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_AromaLadyRose),
    },
    [TRAINER_SWIMMER_MALE_SAMIR] = {
        .trainerClass = TRAINER_CLASS_SWIMMER_M,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = _("SAMIR"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_SwimmerMaleSamir),
    },
    [TRAINER_SWIMMER_FEMALE_DENISE] = {
        .trainerClass = TRAINER_CLASS_SWIMMER_F,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_FEMALE | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_SWIMMER_F,
        .trainerName = _("DENISE"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_SwimmerFemaleDenise),
    },
    [TRAINER_TWINS_MIU_MIA] = {
        .trainerClass = TRAINER_CLASS_TWINS,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_TWINS,
        .trainerPic = TRAINER_PIC_TWINS,
        .trainerName = _("MIU & MIA"),
        .items = {},
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_TwinsMiuMia),
    },
    [TRAINER_HIKER_EARL] = {
        .trainerClass = TRAINER_CLASS_HIKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_HIKER,
        .trainerName = _("EARL"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_HikerEarl),
    },
    [TRAINER_RUIN_MANIAC_FOSTER] = {
        .trainerClass = TRAINER_CLASS_RUIN_MANIAC,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_RUIN_MANIAC,
        .trainerName = _("FOSTER"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_RuinManiacFoster),
    },
    [TRAINER_RUIN_MANIAC_LARRY] = {
        .trainerClass = TRAINER_CLASS_RUIN_MANIAC,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_RUIN_MANIAC,
        .trainerName = _("LARRY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_RuinManiacLarry),
    },
    [TRAINER_HIKER_DARYL] = {
        .trainerClass = TRAINER_CLASS_HIKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_HIKER,
        .trainerName = _("DARYL"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_HikerDaryl),
    },
    [TRAINER_POKEMANIAC_HECTOR] = {
        .trainerClass = TRAINER_CLASS_POKEMANIAC,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_POKEMANIAC,
        .trainerName = _("HECTOR"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_PokemaniacHector),
    },
    [TRAINER_PSYCHIC_DARIO] = {
        .trainerClass = TRAINER_CLASS_PSYCHIC,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_PSYCHIC_M,
        .trainerName = _("DARIO"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_PsychicDario),
    },
    [TRAINER_PSYCHIC_RODETTE] = {
        .trainerClass = TRAINER_CLASS_PSYCHIC,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_INTENSE | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_PSYCHIC_F,
        .trainerName = _("RODETTE"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_PsychicRodette),
    },
    [TRAINER_AROMA_LADY_MIAH] = {
        .trainerClass = TRAINER_CLASS_AROMA_LADY,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_FEMALE | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_AROMA_LADY,
        .trainerName = _("MIAH"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_AromaLadyMiah),
    },
    [TRAINER_YOUNG_COUPLE_EVE_JON] = {
        .trainerClass = TRAINER_CLASS_YOUNG_COUPLE,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_GIRL,
        .trainerPic = TRAINER_PIC_YOUNG_COUPLE,
        .trainerName = _("EVE & JON"),
        .items = {},
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_YoungCoupleEveJon),
    },
    [TRAINER_JUGGLER_MASON] = {
        .trainerClass = TRAINER_CLASS_JUGGLER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_JUGGLER,
        .trainerName = _("MASON"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_JugglerMason),
    },
    [TRAINER_CRUSH_GIRL_CYNDY] = {
        .trainerClass = TRAINER_CLASS_CRUSH_GIRL,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_CRUSH_GIRL,
        .trainerName = _("CYNDY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = ITEM_DEFAULT_MOVES(sParty_CrushGirlCyndy),
    },
    [TRAINER_CRUSH_GIRL_JOCELYN] = {
        .trainerClass = TRAINER_CLASS_CRUSH_GIRL,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_CRUSH_GIRL,
        .trainerName = _("JOCELYN"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = ITEM_DEFAULT_MOVES(sParty_CrushGirlJocelyn),
    },
    [TRAINER_TAMER_EVAN] = {
        .trainerClass = TRAINER_CLASS_TAMER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_TAMER,
        .trainerName = _("EVAN"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_TamerEvan),
    },
    [TRAINER_POKEMANIAC_MARK_2] = {
        .trainerClass = TRAINER_CLASS_POKEMANIAC,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_POKEMANIAC,
        .trainerName = _("MARK"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_PokemaniacMark2),
    },
    [TRAINER_PKMN_RANGER_LOGAN] = {
        .trainerClass = TRAINER_CLASS_PKMN_RANGER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_POKEMON_RANGER_M,
        .trainerName = _("LOGAN"),
        .items = {ITEM_FULL_RESTORE},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_PkmnRangerLogan),
    },
    [TRAINER_PKMN_RANGER_JACKSON] = {
        .trainerClass = TRAINER_CLASS_PKMN_RANGER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_POKEMON_RANGER_M,
        .trainerName = _("JACKSON"),
        .items = {ITEM_FULL_RESTORE},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_PkmnRangerJackson),
    },
    [TRAINER_PKMN_RANGER_BETH] = {
        .trainerClass = TRAINER_CLASS_PKMN_RANGER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_COOL | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_POKEMON_RANGER_F,
        .trainerName = _("BETH"),
        .items = {ITEM_FULL_RESTORE},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_PkmnRangerBeth),
    },
    [TRAINER_PKMN_RANGER_KATELYN] = {
        .trainerClass = TRAINER_CLASS_PKMN_RANGER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_COOL | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_POKEMON_RANGER_F,
        .trainerName = _("KATELYN"),
        .items = {ITEM_FULL_RESTORE},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_PkmnRangerKatelyn),
    },
    [TRAINER_COOLTRAINER_LEROY] = {
        .trainerClass = TRAINER_CLASS_COOLTRAINER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_COOLTRAINER_M,
        .trainerName = _("LEROY"),
        .items = {ITEM_FULL_RESTORE},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_CooltrainerLeroy),
    },
    [TRAINER_COOLTRAINER_MICHELLE] = {
        .trainerClass = TRAINER_CLASS_COOLTRAINER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_COOL | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_COOLTRAINER_F,
        .trainerName = _("MICHELLE"),
        .items = {ITEM_HYPER_POTION},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_CooltrainerMichelle),
    },
    [TRAINER_COOL_COUPLE_LEX_NYA] = {
        .trainerClass = TRAINER_CLASS_COOL_COUPLE,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_COOL_COUPLE,
        .trainerName = _("LEX & NYA"),
        .items = {ITEM_FULL_RESTORE, ITEM_FULL_RESTORE},
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_CoolCoupleLexNya),
    },
    [TRAINER_RUIN_MANIAC_BRANDON] = {
        .trainerClass = TRAINER_CLASS_RUIN_MANIAC,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_RUIN_MANIAC,
        .trainerName = _("BRANDON"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_RuinManiacBrandon),
    },
    [TRAINER_RUIN_MANIAC_BENJAMIN] = {
        .trainerClass = TRAINER_CLASS_RUIN_MANIAC,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_RUIN_MANIAC,
        .trainerName = _("BENJAMIN"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_RuinManiacBenjamin),
    },
    [TRAINER_PAINTER_EDNA] = {
        .trainerClass = TRAINER_CLASS_PAINTER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_PAINTER,
        .trainerName = _("EDNA"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_PainterEdna),
    },
    [TRAINER_GENTLEMAN_CLIFFORD] = {
        .trainerClass = TRAINER_CLASS_GENTLEMAN,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_RICH,
        .trainerPic = TRAINER_PIC_GENTLEMAN,
        .trainerName = _("CLIFFORD"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_GentlemanClifford),
    },
    [TRAINER_LADY_SELPHY] = {
        .trainerClass = TRAINER_CLASS_LADY,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_LADY,
        .trainerName = _("SELPHY"),
        .items = {ITEM_FULL_RESTORE},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = ITEM_CUSTOM_MOVES(sParty_LadySelphy),
    },
    [TRAINER_RUIN_MANIAC_LAWSON] = {
        .trainerClass = TRAINER_CLASS_RUIN_MANIAC,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_RUIN_MANIAC,
        .trainerName = _("LAWSON"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_RuinManiacLawson),
    },
    [TRAINER_PSYCHIC_LAURA] = {
        .trainerClass = TRAINER_CLASS_PSYCHIC,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_INTENSE | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_PSYCHIC_F,
        .trainerName = _("LAURA"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_PsychicLaura),
    },
    [TRAINER_PKMN_BREEDER_BETHANY] = {
        .trainerClass = TRAINER_CLASS_PKMN_BREEDER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_POKEMON_BREEDER,
        .trainerName = _("BETHANY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_PkmnBreederBethany),
    },
    [TRAINER_PKMN_BREEDER_ALLISON] = {
        .trainerClass = TRAINER_CLASS_PKMN_BREEDER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_POKEMON_BREEDER,
        .trainerName = _("ALLISON"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_PkmnBreederAllison),
    },
    [TRAINER_BUG_CATCHER_GARRET] = {
        .trainerClass = TRAINER_CLASS_BUG_CATCHER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BUG_CATCHER,
        .trainerName = _("GARRET"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_BugCatcherGarret),
    },
    [TRAINER_BUG_CATCHER_JONAH] = {
        .trainerClass = TRAINER_CLASS_BUG_CATCHER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BUG_CATCHER,
        .trainerName = _("JONAH"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_BugCatcherJonah),
    },
    [TRAINER_BUG_CATCHER_VANCE] = {
        .trainerClass = TRAINER_CLASS_BUG_CATCHER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BUG_CATCHER,
        .trainerName = _("VANCE"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_BugCatcherVance),
    },
    [TRAINER_YOUNGSTER_NASH] = {
        .trainerClass = TRAINER_CLASS_YOUNGSTER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_YOUNGSTER,
        .trainerName = _("NASH"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_YoungsterNash),
    },
    [TRAINER_YOUNGSTER_CORDELL] = {
        .trainerClass = TRAINER_CLASS_YOUNGSTER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_YOUNGSTER,
        .trainerName = _("CORDELL"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_YoungsterCordell),
    },
    [TRAINER_LASS_DALIA] = {
        .trainerClass = TRAINER_CLASS_LASS,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_FEMALE | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_LASS,
        .trainerName = _("DALIA"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_LassDalia),
    },
    [TRAINER_LASS_JOANA] = {
        .trainerClass = TRAINER_CLASS_LASS,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_FEMALE | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_LASS,
        .trainerName = _("JOANA"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_LassJoana),
    },
    [TRAINER_CAMPER_RILEY] = {
        .trainerClass = TRAINER_CLASS_CAMPER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_CAMPER,
        .trainerName = _("RILEY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_CamperRiley),
    },
    [TRAINER_PICNICKER_MARCY] = {
        .trainerClass = TRAINER_CLASS_PICNICKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_GIRL | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = _("MARCY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_PicnickerMarcy),
    },
    [TRAINER_RUIN_MANIAC_LAYTON] = {
        .trainerClass = TRAINER_CLASS_RUIN_MANIAC,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_RUIN_MANIAC,
        .trainerName = _("LAYTON"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_RuinManiacLayton),
    },
    [TRAINER_PICNICKER_KELSEY_2] = {
        .trainerClass = TRAINER_CLASS_PICNICKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_GIRL | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = _("KELSEY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_PicnickerKelsey2),
    },
    [TRAINER_PICNICKER_KELSEY_3] = {
        .trainerClass = TRAINER_CLASS_PICNICKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_GIRL | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = _("KELSEY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_PicnickerKelsey3),
    },
    [TRAINER_PICNICKER_KELSEY_4] = {
        .trainerClass = TRAINER_CLASS_PICNICKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_GIRL | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = _("KELSEY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_PicnickerKelsey4),
    },
    [TRAINER_CAMPER_RICKY_2] = {
        .trainerClass = TRAINER_CLASS_CAMPER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_CAMPER,
        .trainerName = _("RICKY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_CamperRicky2),
    },
    [TRAINER_CAMPER_RICKY_3] = {
        .trainerClass = TRAINER_CLASS_CAMPER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_CAMPER,
        .trainerName = _("RICKY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_CamperRicky3),
    },
    [TRAINER_CAMPER_RICKY_4] = {
        .trainerClass = TRAINER_CLASS_CAMPER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_CAMPER,
        .trainerName = _("RICKY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_CamperRicky4),
    },
    [TRAINER_CAMPER_JEFF_2] = {
        .trainerClass = TRAINER_CLASS_CAMPER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_CAMPER,
        .trainerName = _("JEFF"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_CamperJeff2),
    },
    [TRAINER_CAMPER_JEFF_3] = {
        .trainerClass = TRAINER_CLASS_CAMPER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_CAMPER,
        .trainerName = _("JEFF"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_CamperJeff3),
    },
    [TRAINER_CAMPER_JEFF_4] = {
        .trainerClass = TRAINER_CLASS_CAMPER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_CAMPER,
        .trainerName = _("JEFF"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_CamperJeff4),
    },
    [TRAINER_PICNICKER_ISABELLE_2] = {
        .trainerClass = TRAINER_CLASS_PICNICKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_GIRL | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = _("ISABELLE"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_PicnickerIsabelle2),
    },
    [TRAINER_PICNICKER_ISABELLE_3] = {
        .trainerClass = TRAINER_CLASS_PICNICKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_GIRL | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = _("ISABELLE"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_PicnickerIsabelle3),
    },
    [TRAINER_PICNICKER_ISABELLE_4] = {
        .trainerClass = TRAINER_CLASS_PICNICKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_GIRL | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = _("ISABELLE"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_PicnickerIsabelle4),
    },
    [TRAINER_YOUNGSTER_YASU_2] = {
        .trainerClass = TRAINER_CLASS_YOUNGSTER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_YOUNGSTER,
        .trainerName = _("YASU"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_YoungsterYasu2),
    },
    [TRAINER_YOUNGSTER_YASU_3] = {
        .trainerClass = TRAINER_CLASS_YOUNGSTER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_YOUNGSTER,
        .trainerName = _("YASU"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_YoungsterYasu3),
    },
    [TRAINER_ENGINEER_BERNIE_2] = {
        .trainerClass = TRAINER_CLASS_ENGINEER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_ENGINEER,
        .trainerName = _("BERNIE"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_EngineerBernie2),
    },
    [TRAINER_GAMER_DARIAN_2] = {
        .trainerClass = TRAINER_CLASS_GAMER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_GAMER,
        .trainerName = _("DARIAN"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_GamerDarian2),
    },
    [TRAINER_CAMPER_CHRIS_2] = {
        .trainerClass = TRAINER_CLASS_CAMPER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_CAMPER,
        .trainerName = _("CHRIS"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_CamperChris2),
    },
    [TRAINER_CAMPER_CHRIS_3] = {
        .trainerClass = TRAINER_CLASS_CAMPER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_CAMPER,
        .trainerName = _("CHRIS"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_CamperChris3),
    },
    [TRAINER_CAMPER_CHRIS_4] = {
        .trainerClass = TRAINER_CLASS_CAMPER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_CAMPER,
        .trainerName = _("CHRIS"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_CamperChris4),
    },
    [TRAINER_PICNICKER_ALICIA_2] = {
        .trainerClass = TRAINER_CLASS_PICNICKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_GIRL | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = _("ALICIA"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_PicnickerAlicia2),
    },
    [TRAINER_PICNICKER_ALICIA_3] = {
        .trainerClass = TRAINER_CLASS_PICNICKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_GIRL | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = _("ALICIA"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_PicnickerAlicia3),
    },
    [TRAINER_PICNICKER_ALICIA_4] = {
        .trainerClass = TRAINER_CLASS_PICNICKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_GIRL | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = _("ALICIA"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_PicnickerAlicia4),
    },
    [TRAINER_HIKER_JEREMY_2] = {
        .trainerClass = TRAINER_CLASS_HIKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_HIKER,
        .trainerName = _("JEREMY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_HikerJeremy2),
    },
    [TRAINER_POKEMANIAC_MARK_3] = {
        .trainerClass = TRAINER_CLASS_POKEMANIAC,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_POKEMANIAC,
        .trainerName = _("MARK"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_PokemaniacMark3),
    },
    [TRAINER_POKEMANIAC_HERMAN_2] = {
        .trainerClass = TRAINER_CLASS_POKEMANIAC,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_POKEMANIAC,
        .trainerName = _("HERMAN"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_PokemaniacHerman2),
    },
    [TRAINER_POKEMANIAC_HERMAN_3] = {
        .trainerClass = TRAINER_CLASS_POKEMANIAC,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_POKEMANIAC,
        .trainerName = _("HERMAN"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_PokemaniacHerman3),
    },
    [TRAINER_HIKER_TRENT_2] = {
        .trainerClass = TRAINER_CLASS_HIKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_HIKER,
        .trainerName = _("TRENT"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_HikerTrent2),
    },
    [TRAINER_LASS_MEGAN_2] = {
        .trainerClass = TRAINER_CLASS_LASS,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_FEMALE | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_LASS,
        .trainerName = _("MEGAN"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_LassMegan2),
    },
    [TRAINER_LASS_MEGAN_3] = {
        .trainerClass = TRAINER_CLASS_LASS,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_FEMALE | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_LASS,
        .trainerName = _("MEGAN"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_LassMegan3),
    },
    [TRAINER_SUPER_NERD_GLENN_2] = {
        .trainerClass = TRAINER_CLASS_SUPER_NERD,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_SUPER_NERD,
        .trainerName = _("GLENN"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_SuperNerdGlenn2),
    },
    [TRAINER_GAMER_RICH_2] = {
        .trainerClass = TRAINER_CLASS_GAMER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_GAMER,
        .trainerName = _("RICH"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_GamerRich2),
    },
    [TRAINER_BIKER_JAREN_2] = {
        .trainerClass = TRAINER_CLASS_BIKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BIKER,
        .trainerName = _("JAREN"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_BikerJaren2),
    },
    [TRAINER_FISHERMAN_ELLIOT_2] = {
        .trainerClass = TRAINER_CLASS_FISHERMAN,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_FISHERMAN,
        .trainerName = _("ELLIOT"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_FishermanElliot2),
    },
    [TRAINER_ROCKER_LUCA_2] = {
        .trainerClass = TRAINER_CLASS_ROCKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_ROCKER,
        .trainerName = _("LUCA"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_RockerLuca2),
    },
    [TRAINER_BEAUTY_SHEILA_2] = {
        .trainerClass = TRAINER_CLASS_BEAUTY,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_FEMALE | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_BEAUTY,
        .trainerName = _("SHEILA"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_BeautySheila2),
    },
    [TRAINER_BIRD_KEEPER_ROBERT_2] = {
        .trainerClass = TRAINER_CLASS_BIRD_KEEPER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_BIRD_KEEPER,
        .trainerName = _("ROBERT"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_BirdKeeperRobert2),
    },
    [TRAINER_BIRD_KEEPER_ROBERT_3] = {
        .trainerClass = TRAINER_CLASS_BIRD_KEEPER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_BIRD_KEEPER,
        .trainerName = _("ROBERT"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_BirdKeeperRobert3),
    },
    [TRAINER_PICNICKER_SUSIE_2] = {
        .trainerClass = TRAINER_CLASS_PICNICKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_GIRL | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = _("SUSIE"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_PicnickerSusie2),
    },
    [TRAINER_PICNICKER_SUSIE_3] = {
        .trainerClass = TRAINER_CLASS_PICNICKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_GIRL | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = _("SUSIE"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_PicnickerSusie3),
    },
    [TRAINER_PICNICKER_SUSIE_4] = {
        .trainerClass = TRAINER_CLASS_PICNICKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_GIRL | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = _("SUSIE"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_PicnickerSusie4),
    },
    [TRAINER_BIKER_LUKAS_2] = {
        .trainerClass = TRAINER_CLASS_BIKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BIKER,
        .trainerName = _("LUKAS"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_BikerLukas2),
    },
    [TRAINER_BIRD_KEEPER_BENNY_2] = {
        .trainerClass = TRAINER_CLASS_BIRD_KEEPER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_BIRD_KEEPER,
        .trainerName = _("BENNY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_BirdKeeperBenny2),
    },
    [TRAINER_BIRD_KEEPER_BENNY_3] = {
        .trainerClass = TRAINER_CLASS_BIRD_KEEPER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_BIRD_KEEPER,
        .trainerName = _("BENNY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_BirdKeeperBenny3),
    },
    [TRAINER_BIRD_KEEPER_MARLON_2] = {
        .trainerClass = TRAINER_CLASS_BIRD_KEEPER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_BIRD_KEEPER,
        .trainerName = _("MARLON"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_BirdKeeperMarlon2),
    },
    [TRAINER_BIRD_KEEPER_MARLON_3] = {
        .trainerClass = TRAINER_CLASS_BIRD_KEEPER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_BIRD_KEEPER,
        .trainerName = _("MARLON"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_BirdKeeperMarlon3),
    },
    [TRAINER_BEAUTY_GRACE_2] = {
        .trainerClass = TRAINER_CLASS_BEAUTY,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_FEMALE | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_BEAUTY,
        .trainerName = _("GRACE"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_BeautyGrace2),
    },
    [TRAINER_BIRD_KEEPER_CHESTER_2] = {
        .trainerClass = TRAINER_CLASS_BIRD_KEEPER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_BIRD_KEEPER,
        .trainerName = _("CHESTER"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_BirdKeeperChester2),
    },
    [TRAINER_BIRD_KEEPER_CHESTER_3] = {
        .trainerClass = TRAINER_CLASS_BIRD_KEEPER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_BIRD_KEEPER,
        .trainerName = _("CHESTER"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_BirdKeeperChester3),
    },
    [TRAINER_PICNICKER_BECKY_2] = {
        .trainerClass = TRAINER_CLASS_PICNICKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_GIRL | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = _("BECKY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_PicnickerBecky2),
    },
    [TRAINER_PICNICKER_BECKY_3] = {
        .trainerClass = TRAINER_CLASS_PICNICKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_GIRL | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = _("BECKY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_PicnickerBecky3),
    },
    [TRAINER_PICNICKER_BECKY_4] = {
        .trainerClass = TRAINER_CLASS_PICNICKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_GIRL | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = _("BECKY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_PicnickerBecky4),
    },
    [TRAINER_CRUSH_KIN_RON_MYA_2] = {
        .trainerClass = TRAINER_CLASS_CRUSH_KIN,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_CRUSH_KIN,
        .trainerName = _("RON & MYA"),
        .items = {},
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = ITEM_DEFAULT_MOVES(sParty_CrushKinRonMya2),
    },
    [TRAINER_CRUSH_KIN_RON_MYA_3] = {
        .trainerClass = TRAINER_CLASS_CRUSH_KIN,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_CRUSH_KIN,
        .trainerName = _("RON & MYA"),
        .items = {},
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = ITEM_DEFAULT_MOVES(sParty_CrushKinRonMya3),
    },
    [TRAINER_CRUSH_KIN_RON_MYA_4] = {
        .trainerClass = TRAINER_CLASS_CRUSH_KIN,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_CRUSH_KIN,
        .trainerName = _("RON & MYA"),
        .items = {},
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = ITEM_DEFAULT_MOVES(sParty_CrushKinRonMya4),
    },
    [TRAINER_BIKER_RUBEN_2] = {
        .trainerClass = TRAINER_CLASS_BIKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BIKER,
        .trainerName = _("RUBEN"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_BikerRuben2),
    },
    [TRAINER_CUE_BALL_CAMRON_2] = {
        .trainerClass = TRAINER_CLASS_CUE_BALL,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_CUE_BALL,
        .trainerName = _("CAMRON"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_CueBallCamron2),
    },
    [TRAINER_BIKER_JAXON_2] = {
        .trainerClass = TRAINER_CLASS_BIKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BIKER,
        .trainerName = _("JAXON"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_BikerJaxon2),
    },
    [TRAINER_CUE_BALL_ISAIAH_2] = {
        .trainerClass = TRAINER_CLASS_CUE_BALL,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_CUE_BALL,
        .trainerName = _("ISAIAH"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_CueBallIsaiah2),
    },
    [TRAINER_CUE_BALL_COREY_2] = {
        .trainerClass = TRAINER_CLASS_CUE_BALL,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_CUE_BALL,
        .trainerName = _("COREY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_CueBallCorey2),
    },
    [TRAINER_BIRD_KEEPER_JACOB_2] = {
        .trainerClass = TRAINER_CLASS_BIRD_KEEPER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_BIRD_KEEPER,
        .trainerName = _("JACOB"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_BirdKeeperJacob2),
    },
    [TRAINER_BIRD_KEEPER_JACOB_3] = {
        .trainerClass = TRAINER_CLASS_BIRD_KEEPER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_BIRD_KEEPER,
        .trainerName = _("JACOB"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_BirdKeeperJacob3),
    },
    [TRAINER_SWIMMER_FEMALE_ALICE_2] = {
        .trainerClass = TRAINER_CLASS_SWIMMER_F,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_FEMALE | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_SWIMMER_F,
        .trainerName = _("ALICE"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_SwimmerFemaleAlice2),
    },
    [TRAINER_SWIMMER_MALE_DARRIN_2] = {
        .trainerClass = TRAINER_CLASS_SWIMMER_M,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = _("DARRIN"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_SwimmerMaleDarrin2),
    },
    [TRAINER_PICNICKER_MISSY_2] = {
        .trainerClass = TRAINER_CLASS_PICNICKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_GIRL | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = _("MISSY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_PicnickerMissy2),
    },
    [TRAINER_PICNICKER_MISSY_3] = {
        .trainerClass = TRAINER_CLASS_PICNICKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_GIRL | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_PICNICKER,
        .trainerName = _("MISSY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_PicnickerMissy3),
    },
    [TRAINER_FISHERMAN_WADE_2] = {
        .trainerClass = TRAINER_CLASS_FISHERMAN,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_FISHERMAN,
        .trainerName = _("WADE"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_FishermanWade2),
    },
    [TRAINER_SWIMMER_MALE_JACK_2] = {
        .trainerClass = TRAINER_CLASS_SWIMMER_M,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = _("JACK"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_SwimmerMaleJack2),
    },
    [TRAINER_SIS_AND_BRO_LIL_IAN_2] = {
        .trainerClass = TRAINER_CLASS_SIS_AND_BRO,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SIS_AND_BRO,
        .trainerName = _("LIL & IAN"),
        .items = {},
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_SisAndBroLilIan2),
    },
    [TRAINER_SIS_AND_BRO_LIL_IAN_3] = {
        .trainerClass = TRAINER_CLASS_SIS_AND_BRO,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SIS_AND_BRO,
        .trainerName = _("LIL & IAN"),
        .items = {},
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_SisAndBroLilIan3),
    },
    [TRAINER_SWIMMER_MALE_FINN_2] = {
        .trainerClass = TRAINER_CLASS_SWIMMER_M,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = _("FINN"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_SwimmerMaleFinn2),
    },
    [TRAINER_CRUSH_GIRL_SHARON_2] = {
        .trainerClass = TRAINER_CLASS_CRUSH_GIRL,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_CRUSH_GIRL,
        .trainerName = _("SHARON"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = ITEM_DEFAULT_MOVES(sParty_CrushGirlSharon2),
    },
    [TRAINER_CRUSH_GIRL_SHARON_3] = {
        .trainerClass = TRAINER_CLASS_CRUSH_GIRL,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_CRUSH_GIRL,
        .trainerName = _("SHARON"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = ITEM_DEFAULT_MOVES(sParty_CrushGirlSharon3),
    },
    [TRAINER_CRUSH_GIRL_TANYA_2] = {
        .trainerClass = TRAINER_CLASS_CRUSH_GIRL,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_CRUSH_GIRL,
        .trainerName = _("TANYA"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = ITEM_DEFAULT_MOVES(sParty_CrushGirlTanya2),
    },
    [TRAINER_CRUSH_GIRL_TANYA_3] = {
        .trainerClass = TRAINER_CLASS_CRUSH_GIRL,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_CRUSH_GIRL,
        .trainerName = _("TANYA"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = ITEM_DEFAULT_MOVES(sParty_CrushGirlTanya3),
    },
    [TRAINER_BLACK_BELT_SHEA_2] = {
        .trainerClass = TRAINER_CLASS_BLACK_BELT,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_BLACK_BELT,
        .trainerName = _("SHEA"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = ITEM_DEFAULT_MOVES(sParty_BlackBeltShea2),
    },
    [TRAINER_BLACK_BELT_SHEA_3] = {
        .trainerClass = TRAINER_CLASS_BLACK_BELT,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_BLACK_BELT,
        .trainerName = _("SHEA"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = ITEM_DEFAULT_MOVES(sParty_BlackBeltShea3),
    },
    [TRAINER_BLACK_BELT_HUGH_2] = {
        .trainerClass = TRAINER_CLASS_BLACK_BELT,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_BLACK_BELT,
        .trainerName = _("HUGH"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = ITEM_DEFAULT_MOVES(sParty_BlackBeltHugh2),
    },
    [TRAINER_BLACK_BELT_HUGH_3] = {
        .trainerClass = TRAINER_CLASS_BLACK_BELT,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_BLACK_BELT,
        .trainerName = _("HUGH"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = ITEM_DEFAULT_MOVES(sParty_BlackBeltHugh3),
    },
    [TRAINER_CRUSH_KIN_MIK_KIA_2] = {
        .trainerClass = TRAINER_CLASS_CRUSH_KIN,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_CRUSH_KIN,
        .trainerName = _("MIK & KIA"),
        .items = {},
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = ITEM_DEFAULT_MOVES(sParty_CrushKinMikKia2),
    },
    [TRAINER_CRUSH_KIN_MIK_KIA_3] = {
        .trainerClass = TRAINER_CLASS_CRUSH_KIN,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_CRUSH_KIN,
        .trainerName = _("MIK & KIA"),
        .items = {},
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = ITEM_DEFAULT_MOVES(sParty_CrushKinMikKia3),
    },
    [TRAINER_TUBER_AMIRA_2] = {
        .trainerClass = TRAINER_CLASS_TUBER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_GIRL,
        .trainerPic = TRAINER_PIC_TUBER_F,
        .trainerName = _("AMIRA"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_TuberAmira2),
    },
    [TRAINER_TWINS_JOY_MEG_2] = {
        .trainerClass = TRAINER_CLASS_TWINS,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_TWINS,
        .trainerPic = TRAINER_PIC_TWINS,
        .trainerName = _("JOY & MEG"),
        .items = {},
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_TwinsJoyMeg2),
    },
    [TRAINER_PAINTER_RAYNA_2] = {
        .trainerClass = TRAINER_CLASS_PAINTER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_PAINTER,
        .trainerName = _("RAYNA"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_PainterRayna2),
    },
    [TRAINER_YOUNGSTER_DESTIN_2] = {
        .trainerClass = TRAINER_CLASS_YOUNGSTER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_YOUNGSTER,
        .trainerName = _("DESTIN"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_YoungsterDestin2),
    },
    [TRAINER_PKMN_BREEDER_ALIZE_2] = {
        .trainerClass = TRAINER_CLASS_PKMN_BREEDER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_FEMALE,
        .trainerPic = TRAINER_PIC_POKEMON_BREEDER,
        .trainerName = _("ALIZE"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_PkmnBreederAlize2),
    },
    [TRAINER_YOUNG_COUPLE_GIA_JES_2] = {
        .trainerClass = TRAINER_CLASS_YOUNG_COUPLE,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_GIRL,
        .trainerPic = TRAINER_PIC_YOUNG_COUPLE,
        .trainerName = _("GIA & JES"),
        .items = {},
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_YoungCoupleGiaJes2),
    },
    [TRAINER_YOUNG_COUPLE_GIA_JES_3] = {
        .trainerClass = TRAINER_CLASS_YOUNG_COUPLE,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_GIRL,
        .trainerPic = TRAINER_PIC_YOUNG_COUPLE,
        .trainerName = _("GIA & JES"),
        .items = {},
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_YoungCoupleGiaJes3),
    },
    [TRAINER_BIRD_KEEPER_MILO_2] = {
        .trainerClass = TRAINER_CLASS_BIRD_KEEPER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_BIRD_KEEPER,
        .trainerName = _("MILO"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_BirdKeeperMilo2),
    },
    [TRAINER_BIRD_KEEPER_CHAZ_2] = {
        .trainerClass = TRAINER_CLASS_BIRD_KEEPER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_BIRD_KEEPER,
        .trainerName = _("CHAZ"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_BirdKeeperChaz2),
    },
    [TRAINER_BIRD_KEEPER_HAROLD_2] = {
        .trainerClass = TRAINER_CLASS_BIRD_KEEPER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_BIRD_KEEPER,
        .trainerName = _("HAROLD"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_BirdKeeperHarold2),
    },
    [TRAINER_SWIMMER_FEMALE_NICOLE_2] = {
        .trainerClass = TRAINER_CLASS_SWIMMER_F,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_FEMALE | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_SWIMMER_F,
        .trainerName = _("NICOLE"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_SwimmerFemaleNicole2),
    },
    [TRAINER_PSYCHIC_JACLYN_2] = {
        .trainerClass = TRAINER_CLASS_PSYCHIC,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_INTENSE | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_PSYCHIC_F,
        .trainerName = _("JACLYN"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_PsychicJaclyn2),
    },
    [TRAINER_SWIMMER_MALE_SAMIR_2] = {
        .trainerClass = TRAINER_CLASS_SWIMMER_M,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = _("SAMIR"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_SwimmerMaleSamir2),
    },
    [TRAINER_HIKER_EARL_2] = {
        .trainerClass = TRAINER_CLASS_HIKER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_HIKER,
        .trainerName = _("EARL"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_HikerEarl2),
    },
    [TRAINER_RUIN_MANIAC_LARRY_2] = {
        .trainerClass = TRAINER_CLASS_RUIN_MANIAC,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_RUIN_MANIAC,
        .trainerName = _("LARRY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_RuinManiacLarry2),
    },
    [TRAINER_POKEMANIAC_HECTOR_2] = {
        .trainerClass = TRAINER_CLASS_POKEMANIAC,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS,
        .trainerPic = TRAINER_PIC_POKEMANIAC,
        .trainerName = _("HECTOR"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_PokemaniacHector2),
    },
    [TRAINER_PSYCHIC_DARIO_2] = {
        .trainerClass = TRAINER_CLASS_PSYCHIC,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_PSYCHIC_M,
        .trainerName = _("DARIO"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_PsychicDario2),
    },
    [TRAINER_PSYCHIC_RODETTE_2] = {
        .trainerClass = TRAINER_CLASS_PSYCHIC,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_INTENSE | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_PSYCHIC_F,
        .trainerName = _("RODETTE"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_PsychicRodette2),
    },
    [TRAINER_JUGGLER_MASON_2] = {
        .trainerClass = TRAINER_CLASS_JUGGLER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_JUGGLER,
        .trainerName = _("MASON"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_JugglerMason2),
    },
    [TRAINER_PKMN_RANGER_NICOLAS_2] = {
        .trainerClass = TRAINER_CLASS_PKMN_RANGER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_POKEMON_RANGER_M,
        .trainerName = _("NICOLAS"),
        .items = {ITEM_FULL_RESTORE},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_PkmnRangerNicolas2),
    },
    [TRAINER_PKMN_RANGER_MADELINE_2] = {
        .trainerClass = TRAINER_CLASS_PKMN_RANGER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_COOL | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_POKEMON_RANGER_F,
        .trainerName = _("MADELINE"),
        .items = {ITEM_FULL_RESTORE},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_PkmnRangerMadeline2),
    },
    [TRAINER_CRUSH_GIRL_CYNDY_2] = {
        .trainerClass = TRAINER_CLASS_CRUSH_GIRL,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_INTENSE,
        .trainerPic = TRAINER_PIC_CRUSH_GIRL,
        .trainerName = _("CYNDY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = ITEM_DEFAULT_MOVES(sParty_CrushGirlCyndy2),
    },
    [TRAINER_TAMER_EVAN_2] = {
        .trainerClass = TRAINER_CLASS_TAMER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_HIKER,
        .trainerPic = TRAINER_PIC_TAMER,
        .trainerName = _("EVAN"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_TamerEvan2),
    },
    [TRAINER_PKMN_RANGER_JACKSON_2] = {
        .trainerClass = TRAINER_CLASS_PKMN_RANGER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_POKEMON_RANGER_M,
        .trainerName = _("JACKSON"),
        .items = {ITEM_FULL_RESTORE},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_PkmnRangerJackson2),
    },
    [TRAINER_PKMN_RANGER_KATELYN_2] = {
        .trainerClass = TRAINER_CLASS_PKMN_RANGER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_COOL | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_POKEMON_RANGER_F,
        .trainerName = _("KATELYN"),
        .items = {ITEM_FULL_RESTORE},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_PkmnRangerKatelyn2),
    },
    [TRAINER_COOLTRAINER_LEROY_2] = {
        .trainerClass = TRAINER_CLASS_COOLTRAINER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_COOLTRAINER_M,
        .trainerName = _("LEROY"),
        .items = {ITEM_FULL_RESTORE},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_CooltrainerLeroy2),
    },
    [TRAINER_COOLTRAINER_MICHELLE_2] = {
        .trainerClass = TRAINER_CLASS_COOLTRAINER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_COOL | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_COOLTRAINER_F,
        .trainerName = _("MICHELLE"),
        .items = {ITEM_HYPER_POTION},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_CooltrainerMichelle2),
    },
    [TRAINER_COOL_COUPLE_LEX_NYA_2] = {
        .trainerClass = TRAINER_CLASS_COOL_COUPLE,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_COOL,
        .trainerPic = TRAINER_PIC_COOL_COUPLE,
        .trainerName = _("LEX & NYA"),
        .items = {ITEM_FULL_RESTORE, ITEM_FULL_RESTORE},
        .doubleBattle = TRUE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = NO_ITEM_CUSTOM_MOVES(sParty_CoolCoupleLexNya2),
    },
    [TRAINER_BUG_CATCHER_COLTON_2] = {
        .trainerClass = TRAINER_CLASS_BUG_CATCHER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BUG_CATCHER,
        .trainerName = _("COLTON"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_BugCatcherColton2),
    },
    [TRAINER_BUG_CATCHER_COLTON_3] = {
        .trainerClass = TRAINER_CLASS_BUG_CATCHER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BUG_CATCHER,
        .trainerName = _("COLTON"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_BugCatcherColton3),
    },
    [TRAINER_BUG_CATCHER_COLTON_4] = {
        .trainerClass = TRAINER_CLASS_BUG_CATCHER,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_BUG_CATCHER,
        .trainerName = _("COLTON"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_BugCatcherColton4),
    },
    [TRAINER_SWIMMER_MALE_MATTHEW_2] = {
        .trainerClass = TRAINER_CLASS_SWIMMER_M,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = _("MATTHEW"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_SwimmerMaleMatthew2),
    },
    [TRAINER_SWIMMER_MALE_TONY_2] = {
        .trainerClass = TRAINER_CLASS_SWIMMER_M,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_SWIMMER,
        .trainerPic = TRAINER_PIC_SWIMMER_M,
        .trainerName = _("TONY"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_SwimmerMaleTony2),
    },
    [TRAINER_SWIMMER_FEMALE_MELISSA_2] = {
        .trainerClass = TRAINER_CLASS_SWIMMER_F,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_FEMALE | F_TRAINER_FEMALE,
        .trainerPic = TRAINER_PIC_SWIMMER_F,
        .trainerName = _("MELISSA"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_SwimmerFemaleMelissa2),
    },
    [TRAINER_ELITE_FOUR_LORELEI_2] = {
        .trainerClass = TRAINER_CLASS_ELITE_FOUR,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_ELITE_FOUR,
        .trainerPic = TRAINER_PIC_ELITE_FOUR_LORELEI,
        .trainerName = _("LORELEI"),
        .items = {ITEM_FULL_RESTORE, ITEM_FULL_RESTORE},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = ITEM_CUSTOM_MOVES(sParty_EliteFourLorelei2),
    },
    [TRAINER_ELITE_FOUR_BRUNO_2] = {
        .trainerClass = TRAINER_CLASS_ELITE_FOUR,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_ELITE_FOUR,
        .trainerPic = TRAINER_PIC_ELITE_FOUR_BRUNO,
        .trainerName = _("BRUNO"),
        .items = {ITEM_FULL_RESTORE, ITEM_FULL_RESTORE},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = ITEM_CUSTOM_MOVES(sParty_EliteFourBruno2),
    },
    [TRAINER_ELITE_FOUR_AGATHA_2] = {
        .trainerClass = TRAINER_CLASS_ELITE_FOUR,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_ELITE_FOUR,
        .trainerPic = TRAINER_PIC_ELITE_FOUR_AGATHA,
        .trainerName = _("AGATHA"),
        .items = {ITEM_FULL_RESTORE, ITEM_FULL_RESTORE},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = ITEM_CUSTOM_MOVES(sParty_EliteFourAgatha2),
    },
    [TRAINER_ELITE_FOUR_LANCE_2] = {
        .trainerClass = TRAINER_CLASS_ELITE_FOUR,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_ELITE_FOUR,
        .trainerPic = TRAINER_PIC_ELITE_FOUR_LANCE,
        .trainerName = _("LANCE"),
        .items = {ITEM_FULL_RESTORE, ITEM_FULL_RESTORE},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = ITEM_CUSTOM_MOVES(sParty_EliteFourLance2),
    },
    [TRAINER_CHAMPION_REMATCH_SQUIRTLE] = {
        .trainerClass = TRAINER_CLASS_CHAMPION,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_CHAMPION_RIVAL,
        .trainerName = _("TERRY"),
        .items = {ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = ITEM_CUSTOM_MOVES(sParty_ChampionRematchSquirtle),
    },
    [TRAINER_CHAMPION_REMATCH_BULBASAUR] = {
        .trainerClass = TRAINER_CLASS_CHAMPION,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_CHAMPION_RIVAL,
        .trainerName = _("TERRY"),
        .items = {ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = ITEM_CUSTOM_MOVES(sParty_ChampionRematchBulbasaur),
    },
    [TRAINER_CHAMPION_REMATCH_CHARMANDER] = {
        .trainerClass = TRAINER_CLASS_CHAMPION,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_CHAMPION_RIVAL,
        .trainerName = _("TERRY"),
        .items = {ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE, ITEM_FULL_RESTORE},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY,
        .party = ITEM_CUSTOM_MOVES(sParty_ChampionRematchCharmander),
    },
    [TRAINER_CUE_BALL_PAXTON] = {
        .trainerClass = TRAINER_CLASS_CUE_BALL,
        .encounterMusic_gender = TRAINER_ENCOUNTER_MUSIC_MALE,
        .trainerPic = TRAINER_PIC_CUE_BALL,
        .trainerName = _("PAXTON"),
        .items = {},
        .doubleBattle = FALSE,
        .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE,
        .party = NO_ITEM_DEFAULT_MOVES(sParty_CueBallPaxton),
    },
};
// ===== END src/data/trainers.h =====
// ===== BEGIN src/data/text/species_names.h =====
const u8 gSpeciesNames[][POKEMON_NAME_LENGTH + 1] = {
    [SPECIES_NONE] = _("??????????"),
    [SPECIES_BULBASAUR] = _("BULBASAUR"),
    [SPECIES_IVYSAUR] = _("IVYSAUR"),
    [SPECIES_VENUSAUR] = _("VENUSAUR"),
    [SPECIES_CHARMANDER] = _("CHARMANDER"),
    [SPECIES_CHARMELEON] = _("CHARMELEON"),
    [SPECIES_CHARIZARD] = _("CHARIZARD"),
    [SPECIES_SQUIRTLE] = _("SQUIRTLE"),
    [SPECIES_WARTORTLE] = _("WARTORTLE"),
    [SPECIES_BLASTOISE] = _("BLASTOISE"),
    [SPECIES_CATERPIE] = _("CATERPIE"),
    [SPECIES_METAPOD] = _("METAPOD"),
    [SPECIES_BUTTERFREE] = _("BUTTERFREE"),
    [SPECIES_WEEDLE] = _("WEEDLE"),
    [SPECIES_KAKUNA] = _("KAKUNA"),
    [SPECIES_BEEDRILL] = _("BEEDRILL"),
    [SPECIES_PIDGEY] = _("PIDGEY"),
    [SPECIES_PIDGEOTTO] = _("PIDGEOTTO"),
    [SPECIES_PIDGEOT] = _("PIDGEOT"),
    [SPECIES_RATTATA] = _("RATTATA"),
    [SPECIES_RATICATE] = _("RATICATE"),
    [SPECIES_SPEAROW] = _("SPEAROW"),
    [SPECIES_FEAROW] = _("FEAROW"),
    [SPECIES_EKANS] = _("EKANS"),
    [SPECIES_ARBOK] = _("ARBOK"),
    [SPECIES_PIKACHU] = _("PIKACHU"),
    [SPECIES_RAICHU] = _("RAICHU"),
    [SPECIES_SANDSHREW] = _("SANDSHREW"),
    [SPECIES_SANDSLASH] = _("SANDSLASH"),
    [SPECIES_NIDORAN_F] = _("NIDORAN♀"),
    [SPECIES_NIDORINA] = _("NIDORINA"),
    [SPECIES_NIDOQUEEN] = _("NIDOQUEEN"),
    [SPECIES_NIDORAN_M] = _("NIDORAN♂"),
    [SPECIES_NIDORINO] = _("NIDORINO"),
    [SPECIES_NIDOKING] = _("NIDOKING"),
    [SPECIES_CLEFAIRY] = _("CLEFAIRY"),
    [SPECIES_CLEFABLE] = _("CLEFABLE"),
    [SPECIES_VULPIX] = _("VULPIX"),
    [SPECIES_NINETALES] = _("NINETALES"),
    [SPECIES_JIGGLYPUFF] = _("JIGGLYPUFF"),
    [SPECIES_WIGGLYTUFF] = _("WIGGLYTUFF"),
    [SPECIES_ZUBAT] = _("ZUBAT"),
    [SPECIES_GOLBAT] = _("GOLBAT"),
    [SPECIES_ODDISH] = _("ODDISH"),
    [SPECIES_GLOOM] = _("GLOOM"),
    [SPECIES_VILEPLUME] = _("VILEPLUME"),
    [SPECIES_PARAS] = _("PARAS"),
    [SPECIES_PARASECT] = _("PARASECT"),
    [SPECIES_VENONAT] = _("VENONAT"),
    [SPECIES_VENOMOTH] = _("VENOMOTH"),
    [SPECIES_DIGLETT] = _("DIGLETT"),
    [SPECIES_DUGTRIO] = _("DUGTRIO"),
    [SPECIES_MEOWTH] = _("MEOWTH"),
    [SPECIES_PERSIAN] = _("PERSIAN"),
    [SPECIES_PSYDUCK] = _("PSYDUCK"),
    [SPECIES_GOLDUCK] = _("GOLDUCK"),
    [SPECIES_MANKEY] = _("MANKEY"),
    [SPECIES_PRIMEAPE] = _("PRIMEAPE"),
    [SPECIES_GROWLITHE] = _("GROWLITHE"),
    [SPECIES_ARCANINE] = _("ARCANINE"),
    [SPECIES_POLIWAG] = _("POLIWAG"),
    [SPECIES_POLIWHIRL] = _("POLIWHIRL"),
    [SPECIES_POLIWRATH] = _("POLIWRATH"),
    [SPECIES_ABRA] = _("ABRA"),
    [SPECIES_KADABRA] = _("KADABRA"),
    [SPECIES_ALAKAZAM] = _("ALAKAZAM"),
    [SPECIES_MACHOP] = _("MACHOP"),
    [SPECIES_MACHOKE] = _("MACHOKE"),
    [SPECIES_MACHAMP] = _("MACHAMP"),
    [SPECIES_BELLSPROUT] = _("BELLSPROUT"),
    [SPECIES_WEEPINBELL] = _("WEEPINBELL"),
    [SPECIES_VICTREEBEL] = _("VICTREEBEL"),
    [SPECIES_TENTACOOL] = _("TENTACOOL"),
    [SPECIES_TENTACRUEL] = _("TENTACRUEL"),
    [SPECIES_GEODUDE] = _("GEODUDE"),
    [SPECIES_GRAVELER] = _("GRAVELER"),
    [SPECIES_GOLEM] = _("GOLEM"),
    [SPECIES_PONYTA] = _("PONYTA"),
    [SPECIES_RAPIDASH] = _("RAPIDASH"),
    [SPECIES_SLOWPOKE] = _("SLOWPOKE"),
    [SPECIES_SLOWBRO] = _("SLOWBRO"),
    [SPECIES_MAGNEMITE] = _("MAGNEMITE"),
    [SPECIES_MAGNETON] = _("MAGNETON"),
    [SPECIES_FARFETCHD] = _("FARFETCH'D"),
    [SPECIES_DODUO] = _("DODUO"),
    [SPECIES_DODRIO] = _("DODRIO"),
    [SPECIES_SEEL] = _("SEEL"),
    [SPECIES_DEWGONG] = _("DEWGONG"),
    [SPECIES_GRIMER] = _("GRIMER"),
    [SPECIES_MUK] = _("MUK"),
    [SPECIES_SHELLDER] = _("SHELLDER"),
    [SPECIES_CLOYSTER] = _("CLOYSTER"),
    [SPECIES_GASTLY] = _("GASTLY"),
    [SPECIES_HAUNTER] = _("HAUNTER"),
    [SPECIES_GENGAR] = _("GENGAR"),
    [SPECIES_ONIX] = _("ONIX"),
    [SPECIES_DROWZEE] = _("DROWZEE"),
    [SPECIES_HYPNO] = _("HYPNO"),
    [SPECIES_KRABBY] = _("KRABBY"),
    [SPECIES_KINGLER] = _("KINGLER"),
    [SPECIES_VOLTORB] = _("VOLTORB"),
    [SPECIES_ELECTRODE] = _("ELECTRODE"),
    [SPECIES_EXEGGCUTE] = _("EXEGGCUTE"),
    [SPECIES_EXEGGUTOR] = _("EXEGGUTOR"),
    [SPECIES_CUBONE] = _("CUBONE"),
    [SPECIES_MAROWAK] = _("MAROWAK"),
    [SPECIES_HITMONLEE] = _("HITMONLEE"),
    [SPECIES_HITMONCHAN] = _("HITMONCHAN"),
    [SPECIES_LICKITUNG] = _("LICKITUNG"),
    [SPECIES_KOFFING] = _("KOFFING"),
    [SPECIES_WEEZING] = _("WEEZING"),
    [SPECIES_RHYHORN] = _("RHYHORN"),
    [SPECIES_RHYDON] = _("RHYDON"),
    [SPECIES_CHANSEY] = _("CHANSEY"),
    [SPECIES_TANGELA] = _("TANGELA"),
    [SPECIES_KANGASKHAN] = _("KANGASKHAN"),
    [SPECIES_HORSEA] = _("HORSEA"),
    [SPECIES_SEADRA] = _("SEADRA"),
    [SPECIES_GOLDEEN] = _("GOLDEEN"),
    [SPECIES_SEAKING] = _("SEAKING"),
    [SPECIES_STARYU] = _("STARYU"),
    [SPECIES_STARMIE] = _("STARMIE"),
    [SPECIES_MR_MIME] = _("MR. MIME"),
    [SPECIES_SCYTHER] = _("SCYTHER"),
    [SPECIES_JYNX] = _("JYNX"),
    [SPECIES_ELECTABUZZ] = _("ELECTABUZZ"),
    [SPECIES_MAGMAR] = _("MAGMAR"),
    [SPECIES_PINSIR] = _("PINSIR"),
    [SPECIES_TAUROS] = _("TAUROS"),
    [SPECIES_MAGIKARP] = _("MAGIKARP"),
    [SPECIES_GYARADOS] = _("GYARADOS"),
    [SPECIES_LAPRAS] = _("LAPRAS"),
    [SPECIES_DITTO] = _("DITTO"),
    [SPECIES_EEVEE] = _("EEVEE"),
    [SPECIES_VAPOREON] = _("VAPOREON"),
    [SPECIES_JOLTEON] = _("JOLTEON"),
    [SPECIES_FLAREON] = _("FLAREON"),
    [SPECIES_PORYGON] = _("PORYGON"),
    [SPECIES_OMANYTE] = _("OMANYTE"),
    [SPECIES_OMASTAR] = _("OMASTAR"),
    [SPECIES_KABUTO] = _("KABUTO"),
    [SPECIES_KABUTOPS] = _("KABUTOPS"),
    [SPECIES_AERODACTYL] = _("AERODACTYL"),
    [SPECIES_SNORLAX] = _("SNORLAX"),
    [SPECIES_ARTICUNO] = _("ARTICUNO"),
    [SPECIES_ZAPDOS] = _("ZAPDOS"),
    [SPECIES_MOLTRES] = _("MOLTRES"),
    [SPECIES_DRATINI] = _("DRATINI"),
    [SPECIES_DRAGONAIR] = _("DRAGONAIR"),
    [SPECIES_DRAGONITE] = _("DRAGONITE"),
    [SPECIES_MEWTWO] = _("MEWTWO"),
    [SPECIES_MEW] = _("MEW"),
    [SPECIES_CHIKORITA] = _("CHIKORITA"),
    [SPECIES_BAYLEEF] = _("BAYLEEF"),
    [SPECIES_MEGANIUM] = _("MEGANIUM"),
    [SPECIES_CYNDAQUIL] = _("CYNDAQUIL"),
    [SPECIES_QUILAVA] = _("QUILAVA"),
    [SPECIES_TYPHLOSION] = _("TYPHLOSION"),
    [SPECIES_TOTODILE] = _("TOTODILE"),
    [SPECIES_CROCONAW] = _("CROCONAW"),
    [SPECIES_FERALIGATR] = _("FERALIGATR"),
    [SPECIES_SENTRET] = _("SENTRET"),
    [SPECIES_FURRET] = _("FURRET"),
    [SPECIES_HOOTHOOT] = _("HOOTHOOT"),
    [SPECIES_NOCTOWL] = _("NOCTOWL"),
    [SPECIES_LEDYBA] = _("LEDYBA"),
    [SPECIES_LEDIAN] = _("LEDIAN"),
    [SPECIES_SPINARAK] = _("SPINARAK"),
    [SPECIES_ARIADOS] = _("ARIADOS"),
    [SPECIES_CROBAT] = _("CROBAT"),
    [SPECIES_CHINCHOU] = _("CHINCHOU"),
    [SPECIES_LANTURN] = _("LANTURN"),
    [SPECIES_PICHU] = _("PICHU"),
    [SPECIES_CLEFFA] = _("CLEFFA"),
    [SPECIES_IGGLYBUFF] = _("IGGLYBUFF"),
    [SPECIES_TOGEPI] = _("TOGEPI"),
    [SPECIES_TOGETIC] = _("TOGETIC"),
    [SPECIES_NATU] = _("NATU"),
    [SPECIES_XATU] = _("XATU"),
    [SPECIES_MAREEP] = _("MAREEP"),
    [SPECIES_FLAAFFY] = _("FLAAFFY"),
    [SPECIES_AMPHAROS] = _("AMPHAROS"),
    [SPECIES_BELLOSSOM] = _("BELLOSSOM"),
    [SPECIES_MARILL] = _("MARILL"),
    [SPECIES_AZUMARILL] = _("AZUMARILL"),
    [SPECIES_SUDOWOODO] = _("SUDOWOODO"),
    [SPECIES_POLITOED] = _("POLITOED"),
    [SPECIES_HOPPIP] = _("HOPPIP"),
    [SPECIES_SKIPLOOM] = _("SKIPLOOM"),
    [SPECIES_JUMPLUFF] = _("JUMPLUFF"),
    [SPECIES_AIPOM] = _("AIPOM"),
    [SPECIES_SUNKERN] = _("SUNKERN"),
    [SPECIES_SUNFLORA] = _("SUNFLORA"),
    [SPECIES_YANMA] = _("YANMA"),
    [SPECIES_WOOPER] = _("WOOPER"),
    [SPECIES_QUAGSIRE] = _("QUAGSIRE"),
    [SPECIES_ESPEON] = _("ESPEON"),
    [SPECIES_UMBREON] = _("UMBREON"),
    [SPECIES_MURKROW] = _("MURKROW"),
    [SPECIES_SLOWKING] = _("SLOWKING"),
    [SPECIES_MISDREAVUS] = _("MISDREAVUS"),
    [SPECIES_UNOWN] = _("UNOWN"),
    [SPECIES_WOBBUFFET] = _("WOBBUFFET"),
    [SPECIES_GIRAFARIG] = _("GIRAFARIG"),
    [SPECIES_PINECO] = _("PINECO"),
    [SPECIES_FORRETRESS] = _("FORRETRESS"),
    [SPECIES_DUNSPARCE] = _("DUNSPARCE"),
    [SPECIES_GLIGAR] = _("GLIGAR"),
    [SPECIES_STEELIX] = _("STEELIX"),
    [SPECIES_SNUBBULL] = _("SNUBBULL"),
    [SPECIES_GRANBULL] = _("GRANBULL"),
    [SPECIES_QWILFISH] = _("QWILFISH"),
    [SPECIES_SCIZOR] = _("SCIZOR"),
    [SPECIES_SHUCKLE] = _("SHUCKLE"),
    [SPECIES_HERACROSS] = _("HERACROSS"),
    [SPECIES_SNEASEL] = _("SNEASEL"),
    [SPECIES_TEDDIURSA] = _("TEDDIURSA"),
    [SPECIES_URSARING] = _("URSARING"),
    [SPECIES_SLUGMA] = _("SLUGMA"),
    [SPECIES_MAGCARGO] = _("MAGCARGO"),
    [SPECIES_SWINUB] = _("SWINUB"),
    [SPECIES_PILOSWINE] = _("PILOSWINE"),
    [SPECIES_CORSOLA] = _("CORSOLA"),
    [SPECIES_REMORAID] = _("REMORAID"),
    [SPECIES_OCTILLERY] = _("OCTILLERY"),
    [SPECIES_DELIBIRD] = _("DELIBIRD"),
    [SPECIES_MANTINE] = _("MANTINE"),
    [SPECIES_SKARMORY] = _("SKARMORY"),
    [SPECIES_HOUNDOUR] = _("HOUNDOUR"),
    [SPECIES_HOUNDOOM] = _("HOUNDOOM"),
    [SPECIES_KINGDRA] = _("KINGDRA"),
    [SPECIES_PHANPY] = _("PHANPY"),
    [SPECIES_DONPHAN] = _("DONPHAN"),
    [SPECIES_PORYGON2] = _("PORYGON2"),
    [SPECIES_STANTLER] = _("STANTLER"),
    [SPECIES_SMEARGLE] = _("SMEARGLE"),
    [SPECIES_TYROGUE] = _("TYROGUE"),
    [SPECIES_HITMONTOP] = _("HITMONTOP"),
    [SPECIES_SMOOCHUM] = _("SMOOCHUM"),
    [SPECIES_ELEKID] = _("ELEKID"),
    [SPECIES_MAGBY] = _("MAGBY"),
    [SPECIES_MILTANK] = _("MILTANK"),
    [SPECIES_BLISSEY] = _("BLISSEY"),
    [SPECIES_RAIKOU] = _("RAIKOU"),
    [SPECIES_ENTEI] = _("ENTEI"),
    [SPECIES_SUICUNE] = _("SUICUNE"),
    [SPECIES_LARVITAR] = _("LARVITAR"),
    [SPECIES_PUPITAR] = _("PUPITAR"),
    [SPECIES_TYRANITAR] = _("TYRANITAR"),
    [SPECIES_LUGIA] = _("LUGIA"),
    [SPECIES_HO_OH] = _("HO-OH"),
    [SPECIES_CELEBI] = _("CELEBI"),
    [SPECIES_OLD_UNOWN_B] = _("?"),
    [SPECIES_OLD_UNOWN_C] = _("?"),
    [SPECIES_OLD_UNOWN_D] = _("?"),
    [SPECIES_OLD_UNOWN_E] = _("?"),
    [SPECIES_OLD_UNOWN_F] = _("?"),
    [SPECIES_OLD_UNOWN_G] = _("?"),
    [SPECIES_OLD_UNOWN_H] = _("?"),
    [SPECIES_OLD_UNOWN_I] = _("?"),
    [SPECIES_OLD_UNOWN_J] = _("?"),
    [SPECIES_OLD_UNOWN_K] = _("?"),
    [SPECIES_OLD_UNOWN_L] = _("?"),
    [SPECIES_OLD_UNOWN_M] = _("?"),
    [SPECIES_OLD_UNOWN_N] = _("?"),
    [SPECIES_OLD_UNOWN_O] = _("?"),
    [SPECIES_OLD_UNOWN_P] = _("?"),
    [SPECIES_OLD_UNOWN_Q] = _("?"),
    [SPECIES_OLD_UNOWN_R] = _("?"),
    [SPECIES_OLD_UNOWN_S] = _("?"),
    [SPECIES_OLD_UNOWN_T] = _("?"),
    [SPECIES_OLD_UNOWN_U] = _("?"),
    [SPECIES_OLD_UNOWN_V] = _("?"),
    [SPECIES_OLD_UNOWN_W] = _("?"),
    [SPECIES_OLD_UNOWN_X] = _("?"),
    [SPECIES_OLD_UNOWN_Y] = _("?"),
    [SPECIES_OLD_UNOWN_Z] = _("?"),
    [SPECIES_TREECKO] = _("TREECKO"),
    [SPECIES_GROVYLE] = _("GROVYLE"),
    [SPECIES_SCEPTILE] = _("SCEPTILE"),
    [SPECIES_TORCHIC] = _("TORCHIC"),
    [SPECIES_COMBUSKEN] = _("COMBUSKEN"),
    [SPECIES_BLAZIKEN] = _("BLAZIKEN"),
    [SPECIES_MUDKIP] = _("MUDKIP"),
    [SPECIES_MARSHTOMP] = _("MARSHTOMP"),
    [SPECIES_SWAMPERT] = _("SWAMPERT"),
    [SPECIES_POOCHYENA] = _("POOCHYENA"),
    [SPECIES_MIGHTYENA] = _("MIGHTYENA"),
    [SPECIES_ZIGZAGOON] = _("ZIGZAGOON"),
    [SPECIES_LINOONE] = _("LINOONE"),
    [SPECIES_WURMPLE] = _("WURMPLE"),
    [SPECIES_SILCOON] = _("SILCOON"),
    [SPECIES_BEAUTIFLY] = _("BEAUTIFLY"),
    [SPECIES_CASCOON] = _("CASCOON"),
    [SPECIES_DUSTOX] = _("DUSTOX"),
    [SPECIES_LOTAD] = _("LOTAD"),
    [SPECIES_LOMBRE] = _("LOMBRE"),
    [SPECIES_LUDICOLO] = _("LUDICOLO"),
    [SPECIES_SEEDOT] = _("SEEDOT"),
    [SPECIES_NUZLEAF] = _("NUZLEAF"),
    [SPECIES_SHIFTRY] = _("SHIFTRY"),
    [SPECIES_NINCADA] = _("NINCADA"),
    [SPECIES_NINJASK] = _("NINJASK"),
    [SPECIES_SHEDINJA] = _("SHEDINJA"),
    [SPECIES_TAILLOW] = _("TAILLOW"),
    [SPECIES_SWELLOW] = _("SWELLOW"),
    [SPECIES_SHROOMISH] = _("SHROOMISH"),
    [SPECIES_BRELOOM] = _("BRELOOM"),
    [SPECIES_SPINDA] = _("SPINDA"),
    [SPECIES_WINGULL] = _("WINGULL"),
    [SPECIES_PELIPPER] = _("PELIPPER"),
    [SPECIES_SURSKIT] = _("SURSKIT"),
    [SPECIES_MASQUERAIN] = _("MASQUERAIN"),
    [SPECIES_WAILMER] = _("WAILMER"),
    [SPECIES_WAILORD] = _("WAILORD"),
    [SPECIES_SKITTY] = _("SKITTY"),
    [SPECIES_DELCATTY] = _("DELCATTY"),
    [SPECIES_KECLEON] = _("KECLEON"),
    [SPECIES_BALTOY] = _("BALTOY"),
    [SPECIES_CLAYDOL] = _("CLAYDOL"),
    [SPECIES_NOSEPASS] = _("NOSEPASS"),
    [SPECIES_TORKOAL] = _("TORKOAL"),
    [SPECIES_SABLEYE] = _("SABLEYE"),
    [SPECIES_BARBOACH] = _("BARBOACH"),
    [SPECIES_WHISCASH] = _("WHISCASH"),
    [SPECIES_LUVDISC] = _("LUVDISC"),
    [SPECIES_CORPHISH] = _("CORPHISH"),
    [SPECIES_CRAWDAUNT] = _("CRAWDAUNT"),
    [SPECIES_FEEBAS] = _("FEEBAS"),
    [SPECIES_MILOTIC] = _("MILOTIC"),
    [SPECIES_CARVANHA] = _("CARVANHA"),
    [SPECIES_SHARPEDO] = _("SHARPEDO"),
    [SPECIES_TRAPINCH] = _("TRAPINCH"),
    [SPECIES_VIBRAVA] = _("VIBRAVA"),
    [SPECIES_FLYGON] = _("FLYGON"),
    [SPECIES_MAKUHITA] = _("MAKUHITA"),
    [SPECIES_HARIYAMA] = _("HARIYAMA"),
    [SPECIES_ELECTRIKE] = _("ELECTRIKE"),
    [SPECIES_MANECTRIC] = _("MANECTRIC"),
    [SPECIES_NUMEL] = _("NUMEL"),
    [SPECIES_CAMERUPT] = _("CAMERUPT"),
    [SPECIES_SPHEAL] = _("SPHEAL"),
    [SPECIES_SEALEO] = _("SEALEO"),
    [SPECIES_WALREIN] = _("WALREIN"),
    [SPECIES_CACNEA] = _("CACNEA"),
    [SPECIES_CACTURNE] = _("CACTURNE"),
    [SPECIES_SNORUNT] = _("SNORUNT"),
    [SPECIES_GLALIE] = _("GLALIE"),
    [SPECIES_LUNATONE] = _("LUNATONE"),
    [SPECIES_SOLROCK] = _("SOLROCK"),
    [SPECIES_AZURILL] = _("AZURILL"),
    [SPECIES_SPOINK] = _("SPOINK"),
    [SPECIES_GRUMPIG] = _("GRUMPIG"),
    [SPECIES_PLUSLE] = _("PLUSLE"),
    [SPECIES_MINUN] = _("MINUN"),
    [SPECIES_MAWILE] = _("MAWILE"),
    [SPECIES_MEDITITE] = _("MEDITITE"),
    [SPECIES_MEDICHAM] = _("MEDICHAM"),
    [SPECIES_SWABLU] = _("SWABLU"),
    [SPECIES_ALTARIA] = _("ALTARIA"),
    [SPECIES_WYNAUT] = _("WYNAUT"),
    [SPECIES_DUSKULL] = _("DUSKULL"),
    [SPECIES_DUSCLOPS] = _("DUSCLOPS"),
    [SPECIES_ROSELIA] = _("ROSELIA"),
    [SPECIES_SLAKOTH] = _("SLAKOTH"),
    [SPECIES_VIGOROTH] = _("VIGOROTH"),
    [SPECIES_SLAKING] = _("SLAKING"),
    [SPECIES_GULPIN] = _("GULPIN"),
    [SPECIES_SWALOT] = _("SWALOT"),
    [SPECIES_TROPIUS] = _("TROPIUS"),
    [SPECIES_WHISMUR] = _("WHISMUR"),
    [SPECIES_LOUDRED] = _("LOUDRED"),
    [SPECIES_EXPLOUD] = _("EXPLOUD"),
    [SPECIES_CLAMPERL] = _("CLAMPERL"),
    [SPECIES_HUNTAIL] = _("HUNTAIL"),
    [SPECIES_GOREBYSS] = _("GOREBYSS"),
    [SPECIES_ABSOL] = _("ABSOL"),
    [SPECIES_SHUPPET] = _("SHUPPET"),
    [SPECIES_BANETTE] = _("BANETTE"),
    [SPECIES_SEVIPER] = _("SEVIPER"),
    [SPECIES_ZANGOOSE] = _("ZANGOOSE"),
    [SPECIES_RELICANTH] = _("RELICANTH"),
    [SPECIES_ARON] = _("ARON"),
    [SPECIES_LAIRON] = _("LAIRON"),
    [SPECIES_AGGRON] = _("AGGRON"),
    [SPECIES_CASTFORM] = _("CASTFORM"),
    [SPECIES_VOLBEAT] = _("VOLBEAT"),
    [SPECIES_ILLUMISE] = _("ILLUMISE"),
    [SPECIES_LILEEP] = _("LILEEP"),
    [SPECIES_CRADILY] = _("CRADILY"),
    [SPECIES_ANORITH] = _("ANORITH"),
    [SPECIES_ARMALDO] = _("ARMALDO"),
    [SPECIES_RALTS] = _("RALTS"),
    [SPECIES_KIRLIA] = _("KIRLIA"),
    [SPECIES_GARDEVOIR] = _("GARDEVOIR"),
    [SPECIES_BAGON] = _("BAGON"),
    [SPECIES_SHELGON] = _("SHELGON"),
    [SPECIES_SALAMENCE] = _("SALAMENCE"),
    [SPECIES_BELDUM] = _("BELDUM"),
    [SPECIES_METANG] = _("METANG"),
    [SPECIES_METAGROSS] = _("METAGROSS"),
    [SPECIES_REGIROCK] = _("REGIROCK"),
    [SPECIES_REGICE] = _("REGICE"),
    [SPECIES_REGISTEEL] = _("REGISTEEL"),
    [SPECIES_KYOGRE] = _("KYOGRE"),
    [SPECIES_GROUDON] = _("GROUDON"),
    [SPECIES_RAYQUAZA] = _("RAYQUAZA"),
    [SPECIES_LATIAS] = _("LATIAS"),
    [SPECIES_LATIOS] = _("LATIOS"),
    [SPECIES_JIRACHI] = _("JIRACHI"),
    [SPECIES_DEOXYS] = _("DEOXYS"),
    [SPECIES_CHIMECHO] = _("CHIMECHO"),
};
// ===== END src/data/text/species_names.h =====
// ===== BEGIN src/data/text/move_names.h =====
const u8 gMoveNames[MOVES_COUNT][MOVE_NAME_LENGTH + 1] = {
    [MOVE_NONE]          = _("-$$$$$$"),
    [MOVE_POUND]         = _("POUND"),
    [MOVE_KARATE_CHOP]   = _("KARATE CHOP"),
    [MOVE_DOUBLE_SLAP]   = _("DOUBLESLAP"),
    [MOVE_COMET_PUNCH]   = _("COMET PUNCH"),
    [MOVE_MEGA_PUNCH]    = _("MEGA PUNCH"),
    [MOVE_PAY_DAY]       = _("PAY DAY"),
    [MOVE_FIRE_PUNCH]    = _("FIRE PUNCH"),
    [MOVE_ICE_PUNCH]     = _("ICE PUNCH"),
    [MOVE_THUNDER_PUNCH] = _("THUNDERPUNCH"),
    [MOVE_SCRATCH]       = _("SCRATCH"),
    [MOVE_VICE_GRIP]     = _("VICEGRIP"),
    [MOVE_GUILLOTINE]    = _("GUILLOTINE"),
    [MOVE_RAZOR_WIND]    = _("RAZOR WIND"),
    [MOVE_SWORDS_DANCE]  = _("SWORDS DANCE"),
    [MOVE_CUT]           = _("CUT"),
    [MOVE_GUST]          = _("GUST"),
    [MOVE_WING_ATTACK]   = _("WING ATTACK"),
    [MOVE_WHIRLWIND]     = _("WHIRLWIND"),
    [MOVE_FLY]           = _("FLY"),
    [MOVE_BIND]          = _("BIND"),
    [MOVE_SLAM]          = _("SLAM"),
    [MOVE_VINE_WHIP]     = _("VINE WHIP"),
    [MOVE_STOMP]         = _("STOMP"),
    [MOVE_DOUBLE_KICK]   = _("DOUBLE KICK"),
    [MOVE_MEGA_KICK]     = _("MEGA KICK"),
    [MOVE_JUMP_KICK]     = _("JUMP KICK"),
    [MOVE_ROLLING_KICK]  = _("ROLLING KICK"),
    [MOVE_SAND_ATTACK]   = _("SAND-ATTACK"),
    [MOVE_HEADBUTT]      = _("HEADBUTT"),
    [MOVE_HORN_ATTACK]   = _("HORN ATTACK"),
    [MOVE_FURY_ATTACK]   = _("FURY ATTACK"),
    [MOVE_HORN_DRILL]    = _("HORN DRILL"),
    [MOVE_TACKLE]        = _("TACKLE"),
    [MOVE_BODY_SLAM]     = _("BODY SLAM"),
    [MOVE_WRAP]          = _("WRAP"),
    [MOVE_TAKE_DOWN]     = _("TAKE DOWN"),
    [MOVE_THRASH]        = _("THRASH"),
    [MOVE_DOUBLE_EDGE]   = _("DOUBLE-EDGE"),
    [MOVE_TAIL_WHIP]     = _("TAIL WHIP"),
    [MOVE_POISON_STING]  = _("POISON STING"),
    [MOVE_TWINEEDLE]     = _("TWINEEDLE"),
    [MOVE_PIN_MISSILE]   = _("PIN MISSILE"),
    [MOVE_LEER]          = _("LEER"),
    [MOVE_BITE]          = _("BITE"),
    [MOVE_GROWL]         = _("GROWL"),
    [MOVE_ROAR]          = _("ROAR"),
    [MOVE_SING]          = _("SING"),
    [MOVE_SUPERSONIC]    = _("SUPERSONIC"),
    [MOVE_SONIC_BOOM]    = _("SONICBOOM"),
    [MOVE_DISABLE]       = _("DISABLE"),
    [MOVE_ACID]          = _("ACID"),
    [MOVE_EMBER]         = _("EMBER"),
    [MOVE_FLAMETHROWER]  = _("FLAMETHROWER"),
    [MOVE_MIST]          = _("MIST"),
    [MOVE_WATER_GUN]     = _("WATER GUN"),
    [MOVE_HYDRO_PUMP]    = _("HYDRO PUMP"),
    [MOVE_SURF]          = _("SURF"),
    [MOVE_ICE_BEAM]      = _("ICE BEAM"),
    [MOVE_BLIZZARD]      = _("BLIZZARD"),
    [MOVE_PSYBEAM]       = _("PSYBEAM"),
    [MOVE_BUBBLE_BEAM]   = _("BUBBLEBEAM"),
    [MOVE_AURORA_BEAM]   = _("AURORA BEAM"),
    [MOVE_HYPER_BEAM]    = _("HYPER BEAM"),
    [MOVE_PECK]          = _("PECK"),
    [MOVE_DRILL_PECK]    = _("DRILL PECK"),
    [MOVE_SUBMISSION]    = _("SUBMISSION"),
    [MOVE_LOW_KICK]      = _("LOW KICK"),
    [MOVE_COUNTER]       = _("COUNTER"),
    [MOVE_SEISMIC_TOSS]  = _("SEISMIC TOSS"),
    [MOVE_STRENGTH]      = _("STRENGTH"),
    [MOVE_ABSORB]        = _("ABSORB"),
    [MOVE_MEGA_DRAIN]    = _("MEGA DRAIN"),
    [MOVE_LEECH_SEED]    = _("LEECH SEED"),
    [MOVE_GROWTH]        = _("GROWTH"),
    [MOVE_RAZOR_LEAF]    = _("RAZOR LEAF"),
    [MOVE_SOLAR_BEAM]    = _("SOLARBEAM"),
    [MOVE_POISON_POWDER] = _("POISONPOWDER"),
    [MOVE_STUN_SPORE]    = _("STUN SPORE"),
    [MOVE_SLEEP_POWDER]  = _("SLEEP POWDER"),
    [MOVE_PETAL_DANCE]   = _("PETAL DANCE"),
    [MOVE_STRING_SHOT]   = _("STRING SHOT"),
    [MOVE_DRAGON_RAGE]   = _("DRAGON RAGE"),
    [MOVE_FIRE_SPIN]     = _("FIRE SPIN"),
    [MOVE_THUNDER_SHOCK] = _("THUNDERSHOCK"),
    [MOVE_THUNDERBOLT]   = _("THUNDERBOLT"),
    [MOVE_THUNDER_WAVE]  = _("THUNDER WAVE"),
    [MOVE_THUNDER]       = _("THUNDER"),
    [MOVE_ROCK_THROW]    = _("ROCK THROW"),
    [MOVE_EARTHQUAKE]    = _("EARTHQUAKE"),
    [MOVE_FISSURE]       = _("FISSURE"),
    [MOVE_DIG]           = _("DIG"),
    [MOVE_TOXIC]         = _("TOXIC"),
    [MOVE_CONFUSION]     = _("CONFUSION"),
    [MOVE_PSYCHIC]       = _("PSYCHIC"),
    [MOVE_HYPNOSIS]      = _("HYPNOSIS"),
    [MOVE_MEDITATE]      = _("MEDITATE"),
    [MOVE_AGILITY]       = _("AGILITY"),
    [MOVE_QUICK_ATTACK]  = _("QUICK ATTACK"),
    [MOVE_RAGE]          = _("RAGE"),
    [MOVE_TELEPORT]      = _("TELEPORT"),
    [MOVE_NIGHT_SHADE]   = _("NIGHT SHADE"),
    [MOVE_MIMIC]         = _("MIMIC"),
    [MOVE_SCREECH]       = _("SCREECH"),
    [MOVE_DOUBLE_TEAM]   = _("DOUBLE TEAM"),
    [MOVE_RECOVER]       = _("RECOVER"),
    [MOVE_HARDEN]        = _("HARDEN"),
    [MOVE_MINIMIZE]      = _("MINIMIZE"),
    [MOVE_SMOKESCREEN]   = _("SMOKESCREEN"),
    [MOVE_CONFUSE_RAY]   = _("CONFUSE RAY"),
    [MOVE_WITHDRAW]      = _("WITHDRAW"),
    [MOVE_DEFENSE_CURL]  = _("DEFENSE CURL"),
    [MOVE_BARRIER]       = _("BARRIER"),
    [MOVE_LIGHT_SCREEN]  = _("LIGHT SCREEN"),
    [MOVE_HAZE]          = _("HAZE"),
    [MOVE_REFLECT]       = _("REFLECT"),
    [MOVE_FOCUS_ENERGY]  = _("FOCUS ENERGY"),
    [MOVE_BIDE]          = _("BIDE"),
    [MOVE_METRONOME]     = _("METRONOME"),
    [MOVE_MIRROR_MOVE]   = _("MIRROR MOVE"),
    [MOVE_SELF_DESTRUCT] = _("SELFDESTRUCT"),
    [MOVE_EGG_BOMB]      = _("EGG BOMB"),
    [MOVE_LICK]          = _("LICK"),
    [MOVE_SMOG]          = _("SMOG"),
    [MOVE_SLUDGE]        = _("SLUDGE"),
    [MOVE_BONE_CLUB]     = _("BONE CLUB"),
    [MOVE_FIRE_BLAST]    = _("FIRE BLAST"),
    [MOVE_WATERFALL]     = _("WATERFALL"),
    [MOVE_CLAMP]         = _("CLAMP"),
    [MOVE_SWIFT]         = _("SWIFT"),
    [MOVE_SKULL_BASH]    = _("SKULL BASH"),
    [MOVE_SPIKE_CANNON]  = _("SPIKE CANNON"),
    [MOVE_CONSTRICT]     = _("CONSTRICT"),
    [MOVE_AMNESIA]       = _("AMNESIA"),
    [MOVE_KINESIS]       = _("KINESIS"),
    [MOVE_SOFT_BOILED]   = _("SOFTBOILED"),
    [MOVE_HI_JUMP_KICK]  = _("HI JUMP KICK"),
    [MOVE_GLARE]         = _("GLARE"),
    [MOVE_DREAM_EATER]   = _("DREAM EATER"),
    [MOVE_POISON_GAS]    = _("POISON GAS"),
    [MOVE_BARRAGE]       = _("BARRAGE"),
    [MOVE_LEECH_LIFE]    = _("LEECH LIFE"),
    [MOVE_LOVELY_KISS]   = _("LOVELY KISS"),
    [MOVE_SKY_ATTACK]    = _("SKY ATTACK"),
    [MOVE_TRANSFORM]     = _("TRANSFORM"),
    [MOVE_BUBBLE]        = _("BUBBLE"),
    [MOVE_DIZZY_PUNCH]   = _("DIZZY PUNCH"),
    [MOVE_SPORE]         = _("SPORE"),
    [MOVE_FLASH]         = _("FLASH"),
    [MOVE_PSYWAVE]       = _("PSYWAVE"),
    [MOVE_SPLASH]        = _("SPLASH"),
    [MOVE_ACID_ARMOR]    = _("ACID ARMOR"),
    [MOVE_CRABHAMMER]    = _("CRABHAMMER"),
    [MOVE_EXPLOSION]     = _("EXPLOSION"),
    [MOVE_FURY_SWIPES]   = _("FURY SWIPES"),
    [MOVE_BONEMERANG]    = _("BONEMERANG"),
    [MOVE_REST]          = _("REST"),
    [MOVE_ROCK_SLIDE]    = _("ROCK SLIDE"),
    [MOVE_HYPER_FANG]    = _("HYPER FANG"),
    [MOVE_SHARPEN]       = _("SHARPEN"),
    [MOVE_CONVERSION]    = _("CONVERSION"),
    [MOVE_TRI_ATTACK]    = _("TRI ATTACK"),
    [MOVE_SUPER_FANG]    = _("SUPER FANG"),
    [MOVE_SLASH]         = _("SLASH"),
    [MOVE_SUBSTITUTE]    = _("SUBSTITUTE"),
    [MOVE_STRUGGLE]      = _("STRUGGLE"),
    [MOVE_SKETCH]        = _("SKETCH"),
    [MOVE_TRIPLE_KICK]   = _("TRIPLE KICK"),
    [MOVE_THIEF]         = _("THIEF"),
    [MOVE_SPIDER_WEB]    = _("SPIDER WEB"),
    [MOVE_MIND_READER]   = _("MIND READER"),
    [MOVE_NIGHTMARE]     = _("NIGHTMARE"),
    [MOVE_FLAME_WHEEL]   = _("FLAME WHEEL"),
    [MOVE_SNORE]         = _("SNORE"),
    [MOVE_CURSE]         = _("CURSE"),
    [MOVE_FLAIL]         = _("FLAIL"),
    [MOVE_CONVERSION_2]  = _("CONVERSION 2"),
    [MOVE_AEROBLAST]     = _("AEROBLAST"),
    [MOVE_COTTON_SPORE]  = _("COTTON SPORE"),
    [MOVE_REVERSAL]      = _("REVERSAL"),
    [MOVE_SPITE]         = _("SPITE"),
    [MOVE_POWDER_SNOW]   = _("POWDER SNOW"),
    [MOVE_PROTECT]       = _("PROTECT"),
    [MOVE_MACH_PUNCH]    = _("MACH PUNCH"),
    [MOVE_SCARY_FACE]    = _("SCARY FACE"),
    [MOVE_FAINT_ATTACK]  = _("FAINT ATTACK"),
    [MOVE_SWEET_KISS]    = _("SWEET KISS"),
    [MOVE_BELLY_DRUM]    = _("BELLY DRUM"),
    [MOVE_SLUDGE_BOMB]   = _("SLUDGE BOMB"),
    [MOVE_MUD_SLAP]      = _("MUD-SLAP"),
    [MOVE_OCTAZOOKA]     = _("OCTAZOOKA"),
    [MOVE_SPIKES]        = _("SPIKES"),
    [MOVE_ZAP_CANNON]    = _("ZAP CANNON"),
    [MOVE_FORESIGHT]     = _("FORESIGHT"),
    [MOVE_DESTINY_BOND]  = _("DESTINY BOND"),
    [MOVE_PERISH_SONG]   = _("PERISH SONG"),
    [MOVE_ICY_WIND]      = _("ICY WIND"),
    [MOVE_DETECT]        = _("DETECT"),
    [MOVE_BONE_RUSH]     = _("BONE RUSH"),
    [MOVE_LOCK_ON]       = _("LOCK-ON"),
    [MOVE_OUTRAGE]       = _("OUTRAGE"),
    [MOVE_SANDSTORM]     = _("SANDSTORM"),
    [MOVE_GIGA_DRAIN]    = _("GIGA DRAIN"),
    [MOVE_ENDURE]        = _("ENDURE"),
    [MOVE_CHARM]         = _("CHARM"),
    [MOVE_ROLLOUT]       = _("ROLLOUT"),
    [MOVE_FALSE_SWIPE]   = _("FALSE SWIPE"),
    [MOVE_SWAGGER]       = _("SWAGGER"),
    [MOVE_MILK_DRINK]    = _("MILK DRINK"),
    [MOVE_SPARK]         = _("SPARK"),
    [MOVE_FURY_CUTTER]   = _("FURY CUTTER"),
    [MOVE_STEEL_WING]    = _("STEEL WING"),
    [MOVE_MEAN_LOOK]     = _("MEAN LOOK"),
    [MOVE_ATTRACT]       = _("ATTRACT"),
    [MOVE_SLEEP_TALK]    = _("SLEEP TALK"),
    [MOVE_HEAL_BELL]     = _("HEAL BELL"),
    [MOVE_RETURN]        = _("RETURN"),
    [MOVE_PRESENT]       = _("PRESENT"),
    [MOVE_FRUSTRATION]   = _("FRUSTRATION"),
    [MOVE_SAFEGUARD]     = _("SAFEGUARD"),
    [MOVE_PAIN_SPLIT]    = _("PAIN SPLIT"),
    [MOVE_SACRED_FIRE]   = _("SACRED FIRE"),
    [MOVE_MAGNITUDE]     = _("MAGNITUDE"),
    [MOVE_DYNAMIC_PUNCH] = _("DYNAMICPUNCH"),
    [MOVE_MEGAHORN]      = _("MEGAHORN"),
    [MOVE_DRAGON_BREATH] = _("DRAGONBREATH"),
    [MOVE_BATON_PASS]    = _("BATON PASS"),
    [MOVE_ENCORE]        = _("ENCORE"),
    [MOVE_PURSUIT]       = _("PURSUIT"),
    [MOVE_RAPID_SPIN]    = _("RAPID SPIN"),
    [MOVE_SWEET_SCENT]   = _("SWEET SCENT"),
    [MOVE_IRON_TAIL]     = _("IRON TAIL"),
    [MOVE_METAL_CLAW]    = _("METAL CLAW"),
    [MOVE_VITAL_THROW]   = _("VITAL THROW"),
    [MOVE_MORNING_SUN]   = _("MORNING SUN"),
    [MOVE_SYNTHESIS]     = _("SYNTHESIS"),
    [MOVE_MOONLIGHT]     = _("MOONLIGHT"),
    [MOVE_HIDDEN_POWER]  = _("HIDDEN POWER"),
    [MOVE_CROSS_CHOP]    = _("CROSS CHOP"),
    [MOVE_TWISTER]       = _("TWISTER"),
    [MOVE_RAIN_DANCE]    = _("RAIN DANCE"),
    [MOVE_SUNNY_DAY]     = _("SUNNY DAY"),
    [MOVE_CRUNCH]        = _("CRUNCH"),
    [MOVE_MIRROR_COAT]   = _("MIRROR COAT"),
    [MOVE_PSYCH_UP]      = _("PSYCH UP"),
    [MOVE_EXTREME_SPEED] = _("EXTREMESPEED"),
    [MOVE_ANCIENT_POWER] = _("ANCIENTPOWER"),
    [MOVE_SHADOW_BALL]   = _("SHADOW BALL"),
    [MOVE_FUTURE_SIGHT]  = _("FUTURE SIGHT"),
    [MOVE_ROCK_SMASH]    = _("ROCK SMASH"),
    [MOVE_WHIRLPOOL]     = _("WHIRLPOOL"),
    [MOVE_BEAT_UP]       = _("BEAT UP"),
    [MOVE_FAKE_OUT]      = _("FAKE OUT"),
    [MOVE_UPROAR]        = _("UPROAR"),
    [MOVE_STOCKPILE]     = _("STOCKPILE"),
    [MOVE_SPIT_UP]       = _("SPIT UP"),
    [MOVE_SWALLOW]       = _("SWALLOW"),
    [MOVE_HEAT_WAVE]     = _("HEAT WAVE"),
    [MOVE_HAIL]          = _("HAIL"),
    [MOVE_TORMENT]       = _("TORMENT"),
    [MOVE_FLATTER]       = _("FLATTER"),
    [MOVE_WILL_O_WISP]   = _("WILL-O-WISP"),
    [MOVE_MEMENTO]       = _("MEMENTO"),
    [MOVE_FACADE]        = _("FACADE"),
    [MOVE_FOCUS_PUNCH]   = _("FOCUS PUNCH"),
    [MOVE_SMELLING_SALT] = _("SMELLINGSALT"),
    [MOVE_FOLLOW_ME]     = _("FOLLOW ME"),
    [MOVE_NATURE_POWER]  = _("NATURE POWER"),
    [MOVE_CHARGE]        = _("CHARGE"),
    [MOVE_TAUNT]         = _("TAUNT"),
    [MOVE_HELPING_HAND]  = _("HELPING HAND"),
    [MOVE_TRICK]         = _("TRICK"),
    [MOVE_ROLE_PLAY]     = _("ROLE PLAY"),
    [MOVE_WISH]          = _("WISH"),
    [MOVE_ASSIST]        = _("ASSIST"),
    [MOVE_INGRAIN]       = _("INGRAIN"),
    [MOVE_SUPERPOWER]    = _("SUPERPOWER"),
    [MOVE_MAGIC_COAT]    = _("MAGIC COAT"),
    [MOVE_RECYCLE]       = _("RECYCLE"),
    [MOVE_REVENGE]       = _("REVENGE"),
    [MOVE_BRICK_BREAK]   = _("BRICK BREAK"),
    [MOVE_YAWN]          = _("YAWN"),
    [MOVE_KNOCK_OFF]     = _("KNOCK OFF"),
    [MOVE_ENDEAVOR]      = _("ENDEAVOR"),
    [MOVE_ERUPTION]      = _("ERUPTION"),
    [MOVE_SKILL_SWAP]    = _("SKILL SWAP"),
    [MOVE_IMPRISON]      = _("IMPRISON"),
    [MOVE_REFRESH]       = _("REFRESH"),
    [MOVE_GRUDGE]        = _("GRUDGE"),
    [MOVE_SNATCH]        = _("SNATCH"),
    [MOVE_SECRET_POWER]  = _("SECRET POWER"),
    [MOVE_DIVE]          = _("DIVE"),
    [MOVE_ARM_THRUST]    = _("ARM THRUST"),
    [MOVE_CAMOUFLAGE]    = _("CAMOUFLAGE"),
    [MOVE_TAIL_GLOW]     = _("TAIL GLOW"),
    [MOVE_LUSTER_PURGE]  = _("LUSTER PURGE"),
    [MOVE_MIST_BALL]     = _("MIST BALL"),
    [MOVE_FEATHER_DANCE] = _("FEATHERDANCE"),
    [MOVE_TEETER_DANCE]  = _("TEETER DANCE"),
    [MOVE_BLAZE_KICK]    = _("BLAZE KICK"),
    [MOVE_MUD_SPORT]     = _("MUD SPORT"),
    [MOVE_ICE_BALL]      = _("ICE BALL"),
    [MOVE_NEEDLE_ARM]    = _("NEEDLE ARM"),
    [MOVE_SLACK_OFF]     = _("SLACK OFF"),
    [MOVE_HYPER_VOICE]   = _("HYPER VOICE"),
    [MOVE_POISON_FANG]   = _("POISON FANG"),
    [MOVE_CRUSH_CLAW]    = _("CRUSH CLAW"),
    [MOVE_BLAST_BURN]    = _("BLAST BURN"),
    [MOVE_HYDRO_CANNON]  = _("HYDRO CANNON"),
    [MOVE_METEOR_MASH]   = _("METEOR MASH"),
    [MOVE_ASTONISH]      = _("ASTONISH"),
    [MOVE_WEATHER_BALL]  = _("WEATHER BALL"),
    [MOVE_AROMATHERAPY]  = _("AROMATHERAPY"),
    [MOVE_FAKE_TEARS]    = _("FAKE TEARS"),
    [MOVE_AIR_CUTTER]    = _("AIR CUTTER"),
    [MOVE_OVERHEAT]      = _("OVERHEAT"),
    [MOVE_ODOR_SLEUTH]   = _("ODOR SLEUTH"),
    [MOVE_ROCK_TOMB]     = _("ROCK TOMB"),
    [MOVE_SILVER_WIND]   = _("SILVER WIND"),
    [MOVE_METAL_SOUND]   = _("METAL SOUND"),
    [MOVE_GRASS_WHISTLE] = _("GRASSWHISTLE"),
    [MOVE_TICKLE]        = _("TICKLE"),
    [MOVE_COSMIC_POWER]  = _("COSMIC POWER"),
    [MOVE_WATER_SPOUT]   = _("WATER SPOUT"),
    [MOVE_SIGNAL_BEAM]   = _("SIGNAL BEAM"),
    [MOVE_SHADOW_PUNCH]  = _("SHADOW PUNCH"),
    [MOVE_EXTRASENSORY]  = _("EXTRASENSORY"),
    [MOVE_SKY_UPPERCUT]  = _("SKY UPPERCUT"),
    [MOVE_SAND_TOMB]     = _("SAND TOMB"),
    [MOVE_SHEER_COLD]    = _("SHEER COLD"),
    [MOVE_MUDDY_WATER]   = _("MUDDY WATER"),
    [MOVE_BULLET_SEED]   = _("BULLET SEED"),
    [MOVE_AERIAL_ACE]    = _("AERIAL ACE"),
    [MOVE_ICICLE_SPEAR]  = _("ICICLE SPEAR"),
    [MOVE_IRON_DEFENSE]  = _("IRON DEFENSE"),
    [MOVE_BLOCK]         = _("BLOCK"),
    [MOVE_HOWL]          = _("HOWL"),
    [MOVE_DRAGON_CLAW]   = _("DRAGON CLAW"),
    [MOVE_FRENZY_PLANT]  = _("FRENZY PLANT"),
    [MOVE_BULK_UP]       = _("BULK UP"),
    [MOVE_BOUNCE]        = _("BOUNCE"),
    [MOVE_MUD_SHOT]      = _("MUD SHOT"),
    [MOVE_POISON_TAIL]   = _("POISON TAIL"),
    [MOVE_COVET]         = _("COVET"),
    [MOVE_VOLT_TACKLE]   = _("VOLT TACKLE"),
    [MOVE_MAGICAL_LEAF]  = _("MAGICAL LEAF"),
    [MOVE_WATER_SPORT]   = _("WATER SPORT"),
    [MOVE_CALM_MIND]     = _("CALM MIND"),
    [MOVE_LEAF_BLADE]    = _("LEAF BLADE"),
    [MOVE_DRAGON_DANCE]  = _("DRAGON DANCE"),
    [MOVE_ROCK_BLAST]    = _("ROCK BLAST"),
    [MOVE_SHOCK_WAVE]    = _("SHOCK WAVE"),
    [MOVE_WATER_PULSE]   = _("WATER PULSE"),
    [MOVE_DOOM_DESIRE]   = _("DOOM DESIRE"),
    [MOVE_PSYCHO_BOOST]  = _("PSYCHO BOOST")
};
// ===== END src/data/text/move_names.h =====
