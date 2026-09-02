#include "global.h"
#include "gflib.h"
#include "event_data.h"
#include "event_object_movement.h"
#include "field_camera.h"
#include "field_control_avatar.h"
#include "field_effect.h"
#include "field_effect_helpers.h"
#include "field_player_avatar.h"
#include "fieldmap.h"
#include "metatile_behavior.h"
#include "overworld.h"
#include "quest_log.h"
#include "random.h"
#include "script.h"
#include "trainer_see.h"
#include "trig.h"
#include "constants/maps.h"
#include "constants/event_object_movement.h"
#include "constants/event_objects.h"
#include "constants/trainer_types.h"
#include "constants/union_room.h"

static void MoveCoordsInDirection(u32, s16 *, s16 *, s16, s16);
static bool8 ObjectEventExecSingleMovementAction(struct ObjectEvent *, struct Sprite *);
static u8 GetCollisionInDirection(struct ObjectEvent *, u8);
static u32 GetCopyDirection(u8, u32, u32);
static void TryEnableObjectEventAnim(struct ObjectEvent *, struct Sprite *);
static void ObjectEventExecHeldMovementAction(struct ObjectEvent *, struct Sprite *);
static void UpdateObjectEventSpriteAnimPause(struct ObjectEvent *, struct Sprite *);
static bool8 IsCoordOutsideObjectEventMovementRange(struct ObjectEvent *, s16, s16);
static bool8 IsMetatileDirectionallyImpassable(struct ObjectEvent *, s16, s16, u8);
static bool8 DoesObjectCollideWithObjectAt(struct ObjectEvent *, s16, s16);
static void CalcWhetherObjectIsOffscreen(struct ObjectEvent *, struct Sprite *);
static void UpdateObjEventSpriteVisibility(struct ObjectEvent *, struct Sprite *);
static void ObjectEventUpdateMetatileBehaviors(struct ObjectEvent *);
static void GetGroundEffectFlags_Reflection(struct ObjectEvent *, u32 *);
static void GetGroundEffectFlags_TallGrassOnSpawn(struct ObjectEvent *, u32 *);
static void GetGroundEffectFlags_LongGrassOnSpawn(struct ObjectEvent *, u32 *);
static void GetGroundEffectFlags_SandHeap(struct ObjectEvent *, u32 *);
static void GetGroundEffectFlags_ShallowFlowingWater(struct ObjectEvent *, u32 *);
static void GetGroundEffectFlags_ShortGrass(struct ObjectEvent *, u32 *);
static void GetGroundEffectFlags_HotSprings(struct ObjectEvent *, u32 *);
static void GetGroundEffectFlags_TallGrassOnBeginStep(struct ObjectEvent *, u32 *);
static void GetGroundEffectFlags_LongGrassOnBeginStep(struct ObjectEvent *, u32 *);
static void GetGroundEffectFlags_Tracks(struct ObjectEvent *, u32 *);
static void GetGroundEffectFlags_Puddle(struct ObjectEvent *, u32 *);
static void GetGroundEffectFlags_Ripple(struct ObjectEvent *, u32 *);
static void GetGroundEffectFlags_Seaweed(struct ObjectEvent *, u32 *);
static void GetGroundEffectFlags_JumpLanding(struct ObjectEvent *, u32 *);
static u8 ObjectEventCheckForReflectiveSurface(struct ObjectEvent *);
static u8 GetReflectionTypeByMetatileBehavior(u32);
static void InitObjectPriorityByElevation(struct Sprite *sprite, u8 elevation);
static void ObjectEventUpdateSubpriority(struct ObjectEvent *, struct Sprite *);
static void DoTracksGroundEffect_None(struct ObjectEvent *, struct Sprite *, u8);
static void DoTracksGroundEffect_Footprints(struct ObjectEvent *, struct Sprite *, u8);
static void DoTracksGroundEffect_BikeTireTracks(struct ObjectEvent *, struct Sprite *, u8);
static void DoRippleFieldEffect(struct ObjectEvent *, struct Sprite *);
static void DoGroundEffects_OnSpawn(struct ObjectEvent *, struct Sprite *);
static void DoGroundEffects_OnBeginStep(struct ObjectEvent *, struct Sprite *);
static void DoGroundEffects_OnFinishStep(struct ObjectEvent *, struct Sprite *);
static void CreateReflectionEffectSprites(void);
static u8 GetObjectEventIdByLocalId(u8);
static u8 GetObjectEventIdByLocalIdAndMapInternal(u8, u8, u8);
static bool8 GetAvailableObjectEventId(u16, u8, u8, u8 *);
static void SetObjectEventDynamicGraphicsId(struct ObjectEvent *);
static void RemoveObjectEventInternal(struct ObjectEvent *);
static u16 GetObjectEventFlagIdByObjectEventId(u8);
static void UpdateObjectEventVisibility(struct ObjectEvent *, struct Sprite *);
static void MakeObjectTemplateFromObjectEventTemplate(const struct ObjectEventTemplate *, struct SpriteTemplate *, const struct SubspriteTable **);
static void GetObjectEventMovingCameraOffset(s16 *, s16 *);
static const struct ObjectEventTemplate *GetObjectEventTemplateByLocalIdAndMap(u8, u8, u8);
static void LoadObjectEventPalette(u16);
static void RemoveObjectEventIfOutsideView(struct ObjectEvent *);
static void SpawnObjectEventOnReturnToField(u8 objectEventId, s16 x, s16 y);
static void SetPlayerAvatarObjectEventIdAndObjectId(u8, u8);
static void ResetObjectEventFldEffData(struct ObjectEvent *);
static u8 TryLoadObjectPalette(const struct SpritePalette *spritePalette);
static u8 FindObjectEventPaletteIndexByTag(u16);
static bool8 ObjectEventDoesElevationMatch(struct ObjectEvent *, u8);
static bool8 IsElevationMismatchAt(u8 elevation, s16 x, s16 y);
static bool8 AreElevationsCompatible(u8 a, u8 b);
static void ObjectCB_CameraObject(struct Sprite *);
static void CameraObject_0(struct Sprite *);
static void CameraObject_1(struct Sprite *);
static void CameraObject_2(struct Sprite *);
static const struct ObjectEventTemplate *FindObjectEventTemplateByLocalId(u8 localId, const struct ObjectEventTemplate *templates, u8 count);
static void ClearObjectEventMovement(struct ObjectEvent *, struct Sprite *);
static void ObjectEventSetSingleMovement(struct ObjectEvent *, struct Sprite *, u8);
static bool8 ShouldInitObjectEventStateFromTemplate(const struct ObjectEventTemplate *, u8, s16, s16);
static bool8 TemplateIsObstacleAndWithinView(const struct ObjectEventTemplate *, s16, s16);
static bool8 TemplateIsObstacleAndVisibleFromConnectingMap(const struct ObjectEventTemplate *, s16, s16);
static void SetHideObstacleFlag(const struct ObjectEventTemplate *);
static bool8 MovementType_Disguise_Callback(struct ObjectEvent *, struct Sprite *);
static bool8 MovementType_Buried_Callback(struct ObjectEvent *, struct Sprite *);
static u8 MovementType_RaiseHandAndStop_Callback(struct ObjectEvent *, struct Sprite *);
static u8 MovementType_RaiseHandAndJump_Callback(struct ObjectEvent *, struct Sprite *);
static u8 MovementType_RaiseHandAndSwim_Callback(struct ObjectEvent *, struct Sprite *);
static void QuestLogObjectEventExecHeldMovementAction(struct ObjectEvent *, struct Sprite *);
static void VirtualObject_UpdateAnim(struct Sprite *sprite);
static void MovementType_None(struct Sprite *);
static void MovementType_LookAround(struct Sprite *);
static void MovementType_WanderAround(struct Sprite *);
static void MovementType_WanderUpAndDown(struct Sprite *);
static void MovementType_WanderLeftAndRight(struct Sprite *);
static void MovementType_FaceDirection(struct Sprite *);
static void MovementType_FaceDownAndUp(struct Sprite *);
static void MovementType_FaceLeftAndRight(struct Sprite *);
static void MovementType_FaceUpAndLeft(struct Sprite *);
static void MovementType_FaceUpAndRight(struct Sprite *);
static void MovementType_FaceDownAndLeft(struct Sprite *);
static void MovementType_FaceDownAndRight(struct Sprite *);
static void MovementType_FaceDownUpAndLeft(struct Sprite *);
static void MovementType_FaceDownUpAndRight(struct Sprite *);
static void MovementType_FaceUpRightAndLeft(struct Sprite *);
static void MovementType_FaceDownRightAndLeft(struct Sprite *);
static void MovementType_RotateCounterclockwise(struct Sprite *);
static void MovementType_RotateClockwise(struct Sprite *);
static void MovementType_WalkBackAndForth(struct Sprite *);
static void MovementType_WalkSequenceUpRightLeftDown(struct Sprite *);
static void MovementType_WalkSequenceRightLeftDownUp(struct Sprite *);
static void MovementType_WalkSequenceDownUpRightLeft(struct Sprite *);
static void MovementType_WalkSequenceLeftDownUpRight(struct Sprite *);
static void MovementType_WalkSequenceUpLeftRightDown(struct Sprite *);
static void MovementType_WalkSequenceLeftRightDownUp(struct Sprite *);
static void MovementType_WalkSequenceDownUpLeftRight(struct Sprite *);
static void MovementType_WalkSequenceRightDownUpLeft(struct Sprite *);
static void MovementType_WalkSequenceLeftUpDownRight(struct Sprite *);
static void MovementType_WalkSequenceUpDownRightLeft(struct Sprite *);
static void MovementType_WalkSequenceRightLeftUpDown(struct Sprite *);
static void MovementType_WalkSequenceDownRightLeftUp(struct Sprite *);
static void MovementType_WalkSequenceRightUpDownLeft(struct Sprite *);
static void MovementType_WalkSequenceUpDownLeftRight(struct Sprite *);
static void MovementType_WalkSequenceLeftRightUpDown(struct Sprite *);
static void MovementType_WalkSequenceDownLeftRightUp(struct Sprite *);
static void MovementType_WalkSequenceUpLeftDownRight(struct Sprite *);
static void MovementType_WalkSequenceDownRightUpLeft(struct Sprite *);
static void MovementType_WalkSequenceLeftDownRightUp(struct Sprite *);
static void MovementType_WalkSequenceRightUpLeftDown(struct Sprite *);
static void MovementType_WalkSequenceUpRightDownLeft(struct Sprite *);
static void MovementType_WalkSequenceDownLeftUpRight(struct Sprite *);
static void MovementType_WalkSequenceLeftUpRightDown(struct Sprite *);
static void MovementType_WalkSequenceRightDownLeftUp(struct Sprite *);
static void MovementType_CopyPlayer(struct Sprite *);
static void MovementType_TreeDisguise(struct Sprite *);
static void MovementType_MountainDisguise(struct Sprite *);
static void MovementType_CopyPlayerInGrass(struct Sprite *);
static void MovementType_Buried(struct Sprite *);
static void MovementType_WalkInPlace(struct Sprite *);
static void MovementType_WalkInPlaceFast(struct Sprite *);
static void MovementType_JogInPlace(struct Sprite *);
static void MovementType_Invisible(struct Sprite *);
static void MovementType_RaiseHandAndStop(struct Sprite *);
static void MovementType_RaiseHandAndJump(struct Sprite *);
static void MovementType_RaiseHandAndSwim(struct Sprite *);
static void MovementType_WanderAroundSlower(struct Sprite *);

enum {
    MOVE_SPEED_NORMAL, // walking
    MOVE_SPEED_FAST_1, // running / surfing / sliding (ice tile)
    MOVE_SPEED_FAST_2, // water current / bicycle
    MOVE_SPEED_FASTER, // going down cycling road on bicycle
    MOVE_SPEED_FASTEST,
};

enum {
    JUMP_DISTANCE_IN_PLACE,
    JUMP_DISTANCE_NORMAL,
    JUMP_DISTANCE_FAR,
};

#define movement_type_def(setup, table)                                                          \
static u8 setup##_callback(struct ObjectEvent *, struct Sprite *);                               \
void setup(struct Sprite *sprite)                                                                \
{                                                                                                \
    UpdateObjectEventCurrentMovement(&gObjectEvents[sprite->data[0]], sprite, setup##_callback); \
}                                                                                                \
static u8 setup##_callback(struct ObjectEvent *objectEvent, struct Sprite *sprite)               \
{                                                                                                \
    return table[sprite->data[1]](objectEvent, sprite);                                          \
}

#define movement_type_empty_callback(setup)                                                      \
static u8 setup##_callback(struct ObjectEvent *, struct Sprite *);                               \
void setup(struct Sprite *sprite)                                                                \
{                                                                                                \
    UpdateObjectEventCurrentMovement(&gObjectEvents[sprite->data[0]], sprite, setup##_callback); \
}                                                                                                \
static u8 setup##_callback(struct ObjectEvent *objectEvent, struct Sprite *sprite)               \
{                                                                                                \
    return 0;                                                                                    \
}

EWRAM_DATA u8 sCurrentReflectionType = 0;
EWRAM_DATA u16 sCurrentSpecialObjectPaletteTag = 0;

const u8 gReflectionEffectPaletteMap[16] = {
    [PALSLOT_PLAYER]                 = PALSLOT_PLAYER_REFLECTION,
    [PALSLOT_PLAYER_REFLECTION]      = PALSLOT_PLAYER_REFLECTION,
    [PALSLOT_NPC_1]                  = PALSLOT_NPC_1_REFLECTION,
    [PALSLOT_NPC_2]                  = PALSLOT_NPC_2_REFLECTION,
    [PALSLOT_NPC_3]                  = PALSLOT_NPC_3_REFLECTION,
    [PALSLOT_NPC_4]                  = PALSLOT_NPC_4_REFLECTION,
    [PALSLOT_NPC_1_REFLECTION]       = PALSLOT_NPC_1_REFLECTION,
    [PALSLOT_NPC_2_REFLECTION]       = PALSLOT_NPC_2_REFLECTION,
    [PALSLOT_NPC_3_REFLECTION]       = PALSLOT_NPC_3_REFLECTION,
    [PALSLOT_NPC_4_REFLECTION]       = PALSLOT_NPC_4_REFLECTION,
    [PALSLOT_NPC_SPECIAL]            = PALSLOT_NPC_SPECIAL_REFLECTION,
    [PALSLOT_NPC_SPECIAL_REFLECTION] = PALSLOT_NPC_SPECIAL_REFLECTION
};

static const struct SpriteTemplate gCameraSpriteTemplate = {
    .tileTag = 0, 
    .paletteTag = TAG_NONE,
    .oam = &gDummyOamData, 
    .anims = gDummySpriteAnimTable, 
    .images = NULL, 
    .affineAnims = gDummySpriteAffineAnimTable, 
    .callback = ObjectCB_CameraObject
};

void (*const gCameraObjectFuncs[])(struct Sprite *) = {
    CameraObject_0,
    CameraObject_1,
    CameraObject_2,
};

// ===== BEGIN src/data/object_events/object_event_graphics.h =====
const u16 gObjectEventPal_Player[] = INCBIN_U16("assets/graphics.bin", 0x19D54, 0x20);
const u16 gObjectEventPal_PlayerUnused[] = INCBIN_U16("assets/graphics.bin", 0x19D74, 0x20); // Identical except for the transparency
const u16 gObjectEventPaletteNull1[16] = {};
const u16 gObjectEventPaletteNull2[16] = {};
const u16 gObjectEventPaletteNull3[16] = {};
const u16 gObjectEventPaletteNull4[16] = {};
const u16 gObjectEventPaletteNull5[16] = {};
const u16 gObjectEventPaletteNull6[16] = {};
const u16 gObjectEventPaletteNull7[16] = {};
const u16 gObjectEventPaletteNull8[16] = {};
const u16 gObjectEventPaletteNull9[16] = {};
const u16 gObjectEventPaletteNull10[16] = {};
const u16 gObjectEventPaletteNull11[16] = {};
const u16 gObjectEventPaletteNull12[16] = {};
const u16 gObjectEventPaletteNull13[16] = {};
const u16 gObjectEventPaletteNull14[16] = {};
const u16 gObjectEventPic_RedNormal[] = INCBIN_U16("assets/graphics.bin", 0x19D94, 0x900);
const u16 gObjectEventPic_RedSurfRun[] = INCBIN_U16("assets/graphics.bin", 0x1A694, 0xE00);
const u16 gObjectEventPic_GreenNormal[] = INCBIN_U16("assets/graphics.bin", 0x1B494, 0x900);
const u16 gObjectEventPic_GreenSurfRun[] = INCBIN_U16("assets/graphics.bin", 0x1BD94, 0xE00);
const u16 gObjectEventPal_PlayerReflection[] = INCBIN_U16("assets/graphics.bin", 0x1CB94, 0x20);
const u16 gObjectEventPal_BridgeReflection[] = INCBIN_U16("assets/graphics.bin", 0x1CBB4, 0x20);
const u16 gObjectEventPic_RedItem[] = INCBIN_U16("assets/graphics.bin", 0x1CBD4, 0x900);
const u16 gObjectEventPic_GreenItem[] = INCBIN_U16("assets/graphics.bin", 0x1D4D4, 0x900);
const u16 gObjectEventPic_RedSurf[] = INCBIN_U16("assets/graphics.bin", 0x1DDD4, 0x1200);
const u16 gObjectEventPic_GreenSurf[] = INCBIN_U16("assets/graphics.bin", 0x1EFD4, 0x1200);
const u16 gObjectEventPic_RedBike[] = INCBIN_U16("assets/graphics.bin", 0x201D4, 0x1200);
const u16 gObjectEventPic_RedVSSeekerBike[] = INCBIN_U16("assets/graphics.bin", 0x213D4, 0xC00);
const u16 gObjectEventPic_GreenBike[] = INCBIN_U16("assets/graphics.bin", 0x21FD4, 0x1200);
const u16 gObjectEventPic_GreenVSSeekerBike[] = INCBIN_U16("assets/graphics.bin", 0x231D4, 0xC00);
const u16 gObjectEventPic_RSBrendan[] = INCBIN_U16("assets/graphics.bin", 0x23DD4, 0x900);
const u16 gObjectEventPic_RSMay[] = INCBIN_U16("assets/graphics.bin", 0x246D4, 0x900);
const u16 gObjectEventPic_RedFish[] = INCBIN_U16("assets/graphics.bin", 0x24FD4, 0x1800);
const u16 gObjectEventPic_GreenFish[] = INCBIN_U16("assets/graphics.bin", 0x267D4, 0x1800);
const u16 gObjectEventPic_Pokedex[] = INCBIN_U16("assets/graphics.bin", 0x27FD4, 0x80);
const u16 gObjectEventPic_TownMap[] = INCBIN_U16("assets/graphics.bin", 0x28054, 0x100);
const u16 gObjectEventPic_UnusedMan[] = INCBIN_U16("assets/graphics.bin", 0x28154, 0x300); // Unused
const u16 gObjectEventPic_Giovanni[] = INCBIN_U16("assets/graphics.bin", 0x28454, 0x900);
const u16 gObjectEventPic_Blaine[] = INCBIN_U16("assets/graphics.bin", 0x28D54, 0x300);
const u16 gObjectEventPic_Sabrina[] = INCBIN_U16("assets/graphics.bin", 0x29054, 0x300);
const u16 gObjectEventPic_Daisy[] = INCBIN_U16("assets/graphics.bin", 0x29354, 0x900);
const u16 gObjectEventPic_Lorelei[] = INCBIN_U16("assets/graphics.bin", 0x29C54, 0x900);
const u16 gObjectEventPic_Erika[] = INCBIN_U16("assets/graphics.bin", 0x2A554, 0x300);
const u16 gObjectEventPic_Koga[] = INCBIN_U16("assets/graphics.bin", 0x2A854, 0x300);
const u16 gObjectEventPic_Brock[] = INCBIN_U16("assets/graphics.bin", 0x2AB54, 0x300);
const u16 gObjectEventPic_LtSurge[] = INCBIN_U16("assets/graphics.bin", 0x2AE54, 0x300);
const u16 gObjectEventPic_Bill[] = INCBIN_U16("assets/graphics.bin", 0x2B154, 0x900);
const u16 gObjectEventPal_NpcBlue[] = INCBIN_U16("assets/graphics.bin", 0x2BA54, 0x20);
const u16 gObjectEventPal_NpcPink[] = INCBIN_U16("assets/graphics.bin", 0x2BA74, 0x20);
const u16 gObjectEventPal_NpcGreen[] = INCBIN_U16("assets/graphics.bin", 0x2BA94, 0x20);
const u16 gObjectEventPal_NpcWhite[] = INCBIN_U16("assets/graphics.bin", 0x2BAB4, 0x20);
const u16 gObjectEventPal_NpcBlueReflection[] = INCBIN_U16("assets/graphics.bin", 0x2BAD4, 0x20);
const u16 gObjectEventPal_NpcPinkReflection[] = INCBIN_U16("assets/graphics.bin", 0x2BAF4, 0x20);
const u16 gObjectEventPal_NpcGreenReflection[] = INCBIN_U16("assets/graphics.bin", 0x2BB14, 0x20);
const u16 gObjectEventPal_NpcWhiteReflection[] = INCBIN_U16("assets/graphics.bin", 0x2BB34, 0x20);
const u16 gObjectEventPic_LittleBoy[] = INCBIN_U16("assets/graphics.bin", 0x2BB54, 0x480);
const u16 gObjectEventPic_LittleGirl[] = INCBIN_U16("assets/graphics.bin", 0x2BFD4, 0x500);
const u16 gObjectEventPic_SittingBoy[] = INCBIN_U16("assets/graphics.bin", 0x2C4D4, 0x300);
const u16 gObjectEventPic_Lass[] = INCBIN_U16("assets/graphics.bin", 0x2C7D4, 0xA00);
const u16 gObjectEventPic_Youngster[] = INCBIN_U16("assets/graphics.bin", 0x2D1D4, 0xA00);
const u16 gObjectEventPic_Boy[] = INCBIN_U16("assets/graphics.bin", 0x2DBD4, 0xA00);
const u16 gObjectEventPic_Woman1[] = INCBIN_U16("assets/graphics.bin", 0x2E5D4, 0xA00);
const u16 gObjectEventPic_Woman3[] = INCBIN_U16("assets/graphics.bin", 0x2EFD4, 0x900);
const u16 gObjectEventPic_BugCatcher[] = INCBIN_U16("assets/graphics.bin", 0x2F8D4, 0xA00);
const u16 gObjectEventPic_CrushGirl[] = INCBIN_U16("assets/graphics.bin", 0x302D4, 0xA00);
const u16 gObjectEventPic_RichBoy[] = INCBIN_U16("assets/graphics.bin", 0x30CD4, 0x900); // Unused
const u16 gObjectEventPic_FatMan[] = INCBIN_U16("assets/graphics.bin", 0x315D4, 0x900);
const u16 gObjectEventPic_BaldingMan[] = INCBIN_U16("assets/graphics.bin", 0x31ED4, 0xA00);
const u16 gObjectEventPic_Woman2[] = INCBIN_U16("assets/graphics.bin", 0x328D4, 0xA00);
const u16 gObjectEventPic_OldMan1[] = INCBIN_U16("assets/graphics.bin", 0x332D4, 0xA00);
const u16 gObjectEventPic_OldManLyingDown[] = INCBIN_U16("assets/graphics.bin", 0x33CD4, 0x200);
const u16 gObjectEventPic_WorkerM[] = INCBIN_U16("assets/graphics.bin", 0x33ED4, 0xA00);
const u16 gObjectEventPic_WorkerF[] = INCBIN_U16("assets/graphics.bin", 0x348D4, 0xA00);
const u16 gObjectEventPic_Beauty[] = INCBIN_U16("assets/graphics.bin", 0x352D4, 0xA00);
const u16 gObjectEventPic_Chef[] = INCBIN_U16("assets/graphics.bin", 0x35CD4, 0x900);
const u16 gObjectEventPic_OldMan2[] = INCBIN_U16("assets/graphics.bin", 0x365D4, 0x900);
const u16 gObjectEventPic_OldWoman[] = INCBIN_U16("assets/graphics.bin", 0x36ED4, 0x900);
const u16 gObjectEventPic_Camper[] = INCBIN_U16("assets/graphics.bin", 0x377D4, 0xA00);
const u16 gObjectEventPic_Picnicker[] = INCBIN_U16("assets/graphics.bin", 0x381D4, 0xA00);
const u16 gObjectEventPic_CooltrainerM[] = INCBIN_U16("assets/graphics.bin", 0x38BD4, 0xA00);
const u16 gObjectEventPic_CooltrainerF[] = INCBIN_U16("assets/graphics.bin", 0x395D4, 0xA00);
const u16 gObjectEventPic_Psyduck[] = INCBIN_U16("assets/graphics.bin", 0x39FD4, 0x180);
const u16 gObjectEventPic_PokeManiac[] = INCBIN_U16("assets/graphics.bin", 0x3A154, 0xA00);
const u16 gObjectEventPic_Channeler[] = INCBIN_U16("assets/graphics.bin", 0x3AB54, 0xA00);
const u16 gObjectEventPic_RocketF[] = INCBIN_U16("assets/graphics.bin", 0x3B554, 0x900);
const u16 gObjectEventPic_SwimmerMWater[] = INCBIN_U16("assets/graphics.bin", 0x3BE54, 0xA00);
const u16 gObjectEventPic_SwimmerFWater[] = INCBIN_U16("assets/graphics.bin", 0x3C854, 0xA00);
const u16 gObjectEventPic_SwimmerMLand[] = INCBIN_U16("assets/graphics.bin", 0x3D254, 0xA00);
const u16 gObjectEventPic_SwimmerFLand[] = INCBIN_U16("assets/graphics.bin", 0x3DC54, 0xA00);
const u16 gObjectEventPic_BlackBelt[] = INCBIN_U16("assets/graphics.bin", 0x3E654, 0xA00);
const u16 gObjectEventPic_Scientist[] = INCBIN_U16("assets/graphics.bin", 0x3F054, 0xA00);
const u16 gObjectEventPic_Gentleman[] = INCBIN_U16("assets/graphics.bin", 0x3FA54, 0xA00);
const u16 gObjectEventPic_Sailor[] = INCBIN_U16("assets/graphics.bin", 0x40454, 0xA00);
const u16 gObjectEventPic_Captain[] = INCBIN_U16("assets/graphics.bin", 0x40E54, 0x900);
const u16 gObjectEventPic_Fisher[] = INCBIN_U16("assets/graphics.bin", 0x41754, 0xA00);
const u16 gObjectEventPic_TeachyTVHost[] = INCBIN_U16("assets/graphics.bin", 0x42154, 0x900);
const u16 gObjectEventPic_UnusedWoman[] = INCBIN_U16("assets/graphics.bin", 0x42A54, 0x900);
const u16 gObjectEventPic_TuberF[] = INCBIN_U16("assets/graphics.bin", 0x43354, 0x500);
const u16 gObjectEventPic_TuberMWater[] = INCBIN_U16("assets/graphics.bin", 0x43854, 0x500);
const u16 gObjectEventPic_TuberMLand[] = INCBIN_U16("assets/graphics.bin", 0x43D54, 0x500);
const u16 gObjectEventPic_Hiker[] = INCBIN_U16("assets/graphics.bin", 0x44254, 0xA00);
const u16 gObjectEventPic_Biker[] = INCBIN_U16("assets/graphics.bin", 0x44C54, 0x1400);
const u16 gObjectEventPic_GymGuy[] = INCBIN_U16("assets/graphics.bin", 0x46054, 0x900);
const u16 gObjectEventPic_Man[] = INCBIN_U16("assets/graphics.bin", 0x46954, 0xA00);
const u16 gObjectEventPic_Rocker[] = INCBIN_U16("assets/graphics.bin", 0x47354, 0xA00);
const u16 gObjectEventPic_ProfOak[] = INCBIN_U16("assets/graphics.bin", 0x47D54, 0x900);
const u16 gObjectEventPic_Blue[] = INCBIN_U16("assets/graphics.bin", 0x48654, 0x900);
const u16 gObjectEventPic_Nurse[] = INCBIN_U16("assets/graphics.bin", 0x48F54, 0x400);
const u16 gObjectEventPic_CableClubReceptionist[] = INCBIN_U16("assets/graphics.bin", 0x49354, 0x300);
const u16 gObjectEventPic_UnionRoomReceptionist[] = INCBIN_U16("assets/graphics.bin", 0x49654, 0x300);
const u16 gObjectEventPic_UnusedMaleReceptionist[] = INCBIN_U16("assets/graphics.bin", 0x49954, 0x300);
const u16 gObjectEventPic_ItemBall[] = INCBIN_U16("assets/graphics.bin", 0x49C54, 0x80);
const u16 gObjectEventPic_MrFuji[] = INCBIN_U16("assets/graphics.bin", 0x49CD4, 0x900);
const u16 gObjectEventPic_Bruno[] = INCBIN_U16("assets/graphics.bin", 0x4A5D4, 0x300);
const u16 gObjectEventPic_Clerk[] = INCBIN_U16("assets/graphics.bin", 0x4A8D4, 0x900);
const u16 gObjectEventPic_MGDeliveryman[] = INCBIN_U16("assets/graphics.bin", 0x4B1D4, 0x300);
const u16 gObjectEventPic_TrainerTowerDude[] = INCBIN_U16("assets/graphics.bin", 0x4B4D4, 0x300);
const u16 gObjectEventPic_Cameraman[] = INCBIN_U16("assets/graphics.bin", 0x4B7D4, 0x900); // Unused
const u16 gObjectEventPic_RocketM[] = INCBIN_U16("assets/graphics.bin", 0x4C0D4, 0x900);
const u16 gObjectEventPic_Celio[] = INCBIN_U16("assets/graphics.bin", 0x4C9D4, 0x900);
const u16 gObjectEventPic_Lapras[] = INCBIN_U16("assets/graphics.bin", 0x4D2D4, 0x180);
const u16 gObjectEventPic_Zapdos[] = INCBIN_U16("assets/graphics.bin", 0x4D454, 0x200);
const u16 gObjectEventPic_Moltres[] = INCBIN_U16("assets/graphics.bin", 0x4D654, 0x200);
const u16 gObjectEventPic_Articuno[] = INCBIN_U16("assets/graphics.bin", 0x4D854, 0x200);
const u16 gObjectEventPic_Mewtwo[] = INCBIN_U16("assets/graphics.bin", 0x4DA54, 0x80);
const u16 gObjectEventPic_Mew[] = INCBIN_U16("assets/graphics.bin", 0x4DAD4, 0x80);
const u16 gObjectEventPic_Entei[] = INCBIN_U16("assets/graphics.bin", 0x4DB54, 0x80);
const u16 gObjectEventPic_Raikou[] = INCBIN_U16("assets/graphics.bin", 0x4DBD4, 0x80);
const u16 gObjectEventPic_Suicune[] = INCBIN_U16("assets/graphics.bin", 0x4DC54, 0x80);
const u16 gObjectEventPic_Lugia[] = INCBIN_U16("assets/graphics.bin", 0x4DCD4, 0x400);
const u16 gObjectEventPic_HoOh[] = INCBIN_U16("assets/graphics.bin", 0x4E0D4, 0x400);
const u16 gObjectEventPic_Celebi[] = INCBIN_U16("assets/graphics.bin", 0x4E4D4, 0x80);
const u16 gObjectEventPic_DeoxysD[] = INCBIN_U16("assets/graphics.bin", 0x4E554, 0x400);
const u16 gObjectEventPic_DeoxysA[] = INCBIN_U16("assets/graphics.bin", 0x4E954, 0x400);
const u16 gObjectEventPic_DeoxysN[] = INCBIN_U16("assets/graphics.bin", 0x4ED54, 0x400);
const u16 gObjectEventPic_Agatha[] = INCBIN_U16("assets/graphics.bin", 0x4F154, 0x300);
const u16 gObjectEventPic_Misty[] = INCBIN_U16("assets/graphics.bin", 0x4F454, 0x300);
const u16 gObjectEventPic_Lance[] = INCBIN_U16("assets/graphics.bin", 0x4F754, 0x300);
const u16 gObjectEventPic_GBAKid[] = INCBIN_U16("assets/graphics.bin", 0x4FA54, 0x300);
const u16 gObjectEventPic_Mom[] = INCBIN_U16("assets/graphics.bin", 0x4FD54, 0x300);
const u16 gObjectEventPic_Pidgeot[] = INCBIN_U16("assets/graphics.bin", 0x50054, 0x180);
const u16 gObjectEventPic_Omanyte[] = INCBIN_U16("assets/graphics.bin", 0x501D4, 0x180);
const u16 gObjectEventPic_Kangaskhan[] = INCBIN_U16("assets/graphics.bin", 0x50354, 0x180);
const u16 gObjectEventPic_NidoranF[] = INCBIN_U16("assets/graphics.bin", 0x504D4, 0x180);
const u16 gObjectEventPic_NidoranM[] = INCBIN_U16("assets/graphics.bin", 0x50654, 0x180);
const u16 gObjectEventPic_Nidorino[] = INCBIN_U16("assets/graphics.bin", 0x507D4, 0x180);
const u16 gObjectEventPic_Meowth[] = INCBIN_U16("assets/graphics.bin", 0x50954, 0x180);
const u16 gObjectEventPic_Seel[] = INCBIN_U16("assets/graphics.bin", 0x50AD4, 0x180);
const u16 gObjectEventPic_Voltorb[] = INCBIN_U16("assets/graphics.bin", 0x50C54, 0x180);
const u16 gObjectEventPic_Slowpoke[] = INCBIN_U16("assets/graphics.bin", 0x50DD4, 0x180);
const u16 gObjectEventPic_Slowbro[] = INCBIN_U16("assets/graphics.bin", 0x50F54, 0x180);
const u16 gObjectEventPic_Machop[] = INCBIN_U16("assets/graphics.bin", 0x510D4, 0x180);
const u16 gObjectEventPic_Wigglytuff[] = INCBIN_U16("assets/graphics.bin", 0x51254, 0x180);
const u16 gObjectEventPic_Doduo[] = INCBIN_U16("assets/graphics.bin", 0x513D4, 0x180);
const u16 gObjectEventPic_Fearow[] = INCBIN_U16("assets/graphics.bin", 0x51554, 0x180);
const u16 gObjectEventPic_Kabuto[] = INCBIN_U16("assets/graphics.bin", 0x516D4, 0x180);
const u16 gObjectEventPic_Machoke[] = INCBIN_U16("assets/graphics.bin", 0x51854, 0x180);
const u16 gObjectEventPic_Snorlax[] = INCBIN_U16("assets/graphics.bin", 0x519D4, 0x200);
const u16 gObjectEventPic_Spearow[] = INCBIN_U16("assets/graphics.bin", 0x51BD4, 0x180);
const u16 gObjectEventPic_Cubone[] = INCBIN_U16("assets/graphics.bin", 0x51D54, 0x180);
const u16 gObjectEventPic_Poliwrath[] = INCBIN_U16("assets/graphics.bin", 0x51ED4, 0x180);
const u16 gObjectEventPic_Chansey[] = INCBIN_U16("assets/graphics.bin", 0x52054, 0x180);
const u16 gObjectEventPic_Pikachu[] = INCBIN_U16("assets/graphics.bin", 0x521D4, 0x180);
const u16 gObjectEventPic_Jigglypuff[] = INCBIN_U16("assets/graphics.bin", 0x52354, 0x180);
const u16 gObjectEventPic_Pidgey[] = INCBIN_U16("assets/graphics.bin", 0x524D4, 0x180);
const u16 gObjectEventPic_Clefairy[] = INCBIN_U16("assets/graphics.bin", 0x52654, 0x180);
const u16 gObjectEventPic_CutTree[] = INCBIN_U16("assets/graphics.bin", 0x527D4, 0x200);
const u16 gObjectEventPic_RockSmashRock[] = INCBIN_U16("assets/graphics.bin", 0x529D4, 0x200);
const u16 gObjectEventPic_StrengthBoulder[] = INCBIN_U16("assets/graphics.bin", 0x52BD4, 0x80);
const u16 gObjectEventPic_Fossil[] = INCBIN_U16("assets/graphics.bin", 0x52C54, 0x80);
const u16 gObjectEventPic_Ruby[] = INCBIN_U16("assets/graphics.bin", 0x52CD4, 0x80);
const u16 gObjectEventPic_Sapphire[] = INCBIN_U16("assets/graphics.bin", 0x52D54, 0x80);
const u16 gObjectEventPic_OldAmber[] = INCBIN_U16("assets/graphics.bin", 0x52DD4, 0x80);
const u16 gObjectEventPic_GymSign[] = INCBIN_U16("assets/graphics.bin", 0x52E54, 0x100);
const u16 gObjectEventPic_Sign[] = INCBIN_U16("assets/graphics.bin", 0x52F54, 0x80);
const u16 gObjectEventPic_WoodenSign[] = INCBIN_U16("assets/graphics.bin", 0x52FD4, 0x80);
const u16 gObjectEventPic_Clipboard[] = INCBIN_U16("assets/graphics.bin", 0x53054, 0x80);
const u16 gObjectEventPal_Meteorite[] = INCBIN_U16("assets/graphics.bin", 0x530D4, 0x20);
const u16 gObjectEventPic_BirthIslandStone[] = INCBIN_U16("assets/graphics.bin", 0x530F4, 0x200);
const u16 gObjectEventPic_LaprasDoll[] = INCBIN_U16("assets/graphics.bin", 0x532F4, 0x200);
const u16 gObjectEventPal_Seagallop[] = INCBIN_U16("assets/graphics.bin", 0x534F4, 0x20);
const u16 gObjectEventPic_Seagallop[] = INCBIN_U16("assets/graphics.bin", 0x53514, 0x800);
const u16 gObjectEventPal_SSAnne[] = INCBIN_U16("assets/graphics.bin", 0x53D14, 0x20);
const u16 gObjectEventPic_SSAnne[] = INCBIN_U16("assets/graphics.bin", 0x53D34, 0x1000);
const u16 gObjectEventPic_SurfBlob[] = INCBIN_U16("assets/graphics.bin", 0x54D34, 0xC00);
const u16 gObjectEventPic_Policeman[] = INCBIN_U16("assets/graphics.bin", 0x55934, 0x900);
const u16 gObjectEventPal_RSQuintyPlump[] = INCBIN_U16("assets/graphics.bin", 0x56234, 0x20);
const u16 gObjectEventPal_RSQuintyPlumpReflection[] = INCBIN_U16("assets/graphics.bin", 0x56254, 0x20);
const u16 gFieldEffectObjectPic_ShadowSmall[] = INCBIN_U16("assets/graphics.bin", 0x56274, 0x20);
const u16 gFieldEffectObjectPic_ShadowMedium[] = INCBIN_U16("assets/graphics.bin", 0x56294, 0x40);
const u16 gFieldEffectObjectPic_ShadowLarge[] = INCBIN_U16("assets/graphics.bin", 0x562D4, 0x80);
const u16 gFieldEffectObjectPic_ShadowExtraLarge[] = INCBIN_U16("assets/graphics.bin", 0x56354, 0x400);
const u16 sFiller1[0x90] = {};
const u16 gFieldEffectObjectPic_CutGrass[] = INCBIN_U16("assets/graphics.bin", 0x56754, 0x20);
const u16 gFieldEffectObjectPic_CutGrass2[] = INCBIN_U16("assets/graphics.bin", 0x56754, 0x20); // Unused
const u16 gFieldEffectPal_CutGrass[] = INCBIN_U16("assets/graphics.bin", 0x56774, 0x20);
const u16 gFieldEffectObjectPic_Ripple[] = INCBIN_U16("assets/graphics.bin", 0x56794, 0x280);
const u16 gFieldEffectObjectPic_Ash[] = INCBIN_U16("assets/graphics.bin", 0x56A14, 0x280);
const u16 gFieldEffectObjectPic_Arrow[] = INCBIN_U16("assets/graphics.bin", 0x56C94, 0x400);
const u16 gFieldEffectObjectPalette0[] = INCBIN_U16("assets/graphics.bin", 0x57094, 0x20);
const u16 gFieldEffectObjectPalette1[] = INCBIN_U16("assets/graphics.bin", 0x570B4, 0x20);
const u16 sFiller2[0x10] = {};
const u16 gFieldEffectObjectPic_GroundImpactDust[] = INCBIN_U16("assets/graphics.bin", 0x570D4, 0xC0);
const u16 gFieldEffectObjectPic_UnusedGrass3[] = INCBIN_U16("assets/graphics.bin", 0x57194, 0xC0); // Unused
const u16 gFieldEffectObjectPic_JumpTallGrass[] = INCBIN_U16("assets/graphics.bin", 0x57254, 0x100);
const u16 gFieldEffectObjectPic_UnusedGrass4[] = INCBIN_U16("assets/graphics.bin", 0x57354, 0x200); // Unused
const u16 gFieldEffectObjectPic_JumpLongGrass[] = INCBIN_U16("assets/graphics.bin", 0x57554, 0x300);
const u16 gFieldEffectObjectPic_UnusedGrass[] = INCBIN_U16("assets/graphics.bin", 0x57854, 0x480);
const u16 gFieldEffectObjectPic_UnusedGrass2[] = INCBIN_U16("assets/graphics.bin", 0x57CD4, 0x200);
const u16 gFieldEffectObjectPic_LongGrass[] = INCBIN_U16("assets/graphics.bin", 0x57ED4, 0x200);
const u16 gFieldEffectObjectPic_TallGrass[] = INCBIN_U16("assets/graphics.bin", 0x580D4, 0x280);
const u16 gFieldEffectObjectPic_ShortGrass[] = INCBIN_U16("assets/graphics.bin", 0x58354, 0x100);
const u16 gFieldEffectObjectPic_SandFootprints[] = INCBIN_U16("assets/graphics.bin", 0x58454, 0x100);
const u16 gFieldEffectObjectPic_DeepSandFootprints[] = INCBIN_U16("assets/graphics.bin", 0x58554, 0x100);
const u16 gFieldEffectObjectPic_BikeTireTracks[] = INCBIN_U16("assets/graphics.bin", 0x58654, 0x200);
const u16 gFieldEffectObjectPic_UnusedSand[] = INCBIN_U16("assets/graphics.bin", 0x58854, 0x200);
const u16 gFieldEffectObjectPic_SandPile[] = INCBIN_U16("assets/graphics.bin", 0x58A54, 0xC0);
const u16 gFieldEffectObjectPic_JumpBigSplash[] = INCBIN_U16("assets/graphics.bin", 0x58B14, 0x200);
const u16 gFieldEffectObjectPic_Splash[] = INCBIN_U16("assets/graphics.bin", 0x58D14, 0x80);
const u16 gFieldEffectObjectPic_JumpSmallSplash[] = INCBIN_U16("assets/graphics.bin", 0x58D94, 0xC0);
const u16 gFieldEffectObjectPic_WaterSurfacing[] = INCBIN_U16("assets/graphics.bin", 0x58E54, 0x280);
const u16 gFieldEffectObjectPic_TreeDisguise[] = INCBIN_U16("assets/graphics.bin", 0x590D4, 0x700);
const u16 gFieldEffectObjectPic_MountainDisguise[] = INCBIN_U16("assets/graphics.bin", 0x597D4, 0x700);
const u16 gFieldEffectObjectPic_SandDisguisePlaceholder[] = INCBIN_U16("assets/graphics.bin", 0x59ED4, 0x700);
const u16 gFieldEffectObjectPic_HotSpringsWater[] = INCBIN_U16("assets/graphics.bin", 0x5A5D4, 0x80);
const u16 gFieldEffectPal_Ash[] = INCBIN_U16("assets/graphics.bin", 0x5A654, 0x20);
const u16 gFieldEffectObjectPic_AshPuff[] = INCBIN_U16("assets/graphics.bin", 0x5A674, 0x280);
const u16 gFieldEffectObjectPic_AshLaunch[] = INCBIN_U16("assets/graphics.bin", 0x5A8F4, 0x280);
const u16 gFieldEffectObjectPic_Bubbles[] = INCBIN_U16("assets/graphics.bin", 0x5AB74, 0x800);
const u16 gFieldEffectObjectPic_SmallSparkle[] = INCBIN_U16("assets/graphics.bin", 0x5B374, 0x100);
const u16 gFieldEffectPal_SmallSparkle[] = INCBIN_U16("assets/graphics.bin", 0x5B474, 0x20);
const u16 gFieldEffectObjectPic_Bird[] = INCBIN_U16("assets/graphics.bin", 0x5B494, 0x2800);
// ===== END src/data/object_events/object_event_graphics.h =====

static void (*const sMovementTypeCallbacks[MOVEMENT_TYPES_COUNT])(struct Sprite *) = {
    [MOVEMENT_TYPE_NONE]                                  = MovementType_None,
    [MOVEMENT_TYPE_LOOK_AROUND]                           = MovementType_LookAround,
    [MOVEMENT_TYPE_WANDER_AROUND]                         = MovementType_WanderAround,
    [MOVEMENT_TYPE_WANDER_UP_AND_DOWN]                    = MovementType_WanderUpAndDown,
    [MOVEMENT_TYPE_WANDER_DOWN_AND_UP]                    = MovementType_WanderUpAndDown,
    [MOVEMENT_TYPE_WANDER_LEFT_AND_RIGHT]                 = MovementType_WanderLeftAndRight,
    [MOVEMENT_TYPE_WANDER_RIGHT_AND_LEFT]                 = MovementType_WanderLeftAndRight,
    [MOVEMENT_TYPE_FACE_UP]                               = MovementType_FaceDirection,
    [MOVEMENT_TYPE_FACE_DOWN]                             = MovementType_FaceDirection,
    [MOVEMENT_TYPE_FACE_LEFT]                             = MovementType_FaceDirection,
    [MOVEMENT_TYPE_FACE_RIGHT]                            = MovementType_FaceDirection,
    [MOVEMENT_TYPE_PLAYER]                                = MovementType_Player,
    [MOVEMENT_TYPE_BERRY_TREE_GROWTH]                     = NULL,
    [MOVEMENT_TYPE_FACE_DOWN_AND_UP]                      = MovementType_FaceDownAndUp,
    [MOVEMENT_TYPE_FACE_LEFT_AND_RIGHT]                   = MovementType_FaceLeftAndRight,
    [MOVEMENT_TYPE_FACE_UP_AND_LEFT]                      = MovementType_FaceUpAndLeft,
    [MOVEMENT_TYPE_FACE_UP_AND_RIGHT]                     = MovementType_FaceUpAndRight,
    [MOVEMENT_TYPE_FACE_DOWN_AND_LEFT]                    = MovementType_FaceDownAndLeft,
    [MOVEMENT_TYPE_FACE_DOWN_AND_RIGHT]                   = MovementType_FaceDownAndRight,
    [MOVEMENT_TYPE_FACE_DOWN_UP_AND_LEFT]                 = MovementType_FaceDownUpAndLeft,
    [MOVEMENT_TYPE_FACE_DOWN_UP_AND_RIGHT]                = MovementType_FaceDownUpAndRight,
    [MOVEMENT_TYPE_FACE_UP_LEFT_AND_RIGHT]                = MovementType_FaceUpRightAndLeft,
    [MOVEMENT_TYPE_FACE_DOWN_LEFT_AND_RIGHT]              = MovementType_FaceDownRightAndLeft,
    [MOVEMENT_TYPE_ROTATE_COUNTERCLOCKWISE]               = MovementType_RotateCounterclockwise,
    [MOVEMENT_TYPE_ROTATE_CLOCKWISE]                      = MovementType_RotateClockwise,
    [MOVEMENT_TYPE_WALK_UP_AND_DOWN]                      = MovementType_WalkBackAndForth,
    [MOVEMENT_TYPE_WALK_DOWN_AND_UP]                      = MovementType_WalkBackAndForth,
    [MOVEMENT_TYPE_WALK_LEFT_AND_RIGHT]                   = MovementType_WalkBackAndForth,
    [MOVEMENT_TYPE_WALK_RIGHT_AND_LEFT]                   = MovementType_WalkBackAndForth,
    [MOVEMENT_TYPE_WALK_SEQUENCE_UP_RIGHT_LEFT_DOWN]      = MovementType_WalkSequenceUpRightLeftDown,
    [MOVEMENT_TYPE_WALK_SEQUENCE_RIGHT_LEFT_DOWN_UP]      = MovementType_WalkSequenceRightLeftDownUp,
    [MOVEMENT_TYPE_WALK_SEQUENCE_DOWN_UP_RIGHT_LEFT]      = MovementType_WalkSequenceDownUpRightLeft,
    [MOVEMENT_TYPE_WALK_SEQUENCE_LEFT_DOWN_UP_RIGHT]      = MovementType_WalkSequenceLeftDownUpRight,
    [MOVEMENT_TYPE_WALK_SEQUENCE_UP_LEFT_RIGHT_DOWN]      = MovementType_WalkSequenceUpLeftRightDown,
    [MOVEMENT_TYPE_WALK_SEQUENCE_LEFT_RIGHT_DOWN_UP]      = MovementType_WalkSequenceLeftRightDownUp,
    [MOVEMENT_TYPE_WALK_SEQUENCE_DOWN_UP_LEFT_RIGHT]      = MovementType_WalkSequenceDownUpLeftRight,
    [MOVEMENT_TYPE_WALK_SEQUENCE_RIGHT_DOWN_UP_LEFT]      = MovementType_WalkSequenceRightDownUpLeft,
    [MOVEMENT_TYPE_WALK_SEQUENCE_LEFT_UP_DOWN_RIGHT]      = MovementType_WalkSequenceLeftUpDownRight,
    [MOVEMENT_TYPE_WALK_SEQUENCE_UP_DOWN_RIGHT_LEFT]      = MovementType_WalkSequenceUpDownRightLeft,
    [MOVEMENT_TYPE_WALK_SEQUENCE_RIGHT_LEFT_UP_DOWN]      = MovementType_WalkSequenceRightLeftUpDown,
    [MOVEMENT_TYPE_WALK_SEQUENCE_DOWN_RIGHT_LEFT_UP]      = MovementType_WalkSequenceDownRightLeftUp,
    [MOVEMENT_TYPE_WALK_SEQUENCE_RIGHT_UP_DOWN_LEFT]      = MovementType_WalkSequenceRightUpDownLeft,
    [MOVEMENT_TYPE_WALK_SEQUENCE_UP_DOWN_LEFT_RIGHT]      = MovementType_WalkSequenceUpDownLeftRight,
    [MOVEMENT_TYPE_WALK_SEQUENCE_LEFT_RIGHT_UP_DOWN]      = MovementType_WalkSequenceLeftRightUpDown,
    [MOVEMENT_TYPE_WALK_SEQUENCE_DOWN_LEFT_RIGHT_UP]      = MovementType_WalkSequenceDownLeftRightUp,
    [MOVEMENT_TYPE_WALK_SEQUENCE_UP_LEFT_DOWN_RIGHT]      = MovementType_WalkSequenceUpLeftDownRight,
    [MOVEMENT_TYPE_WALK_SEQUENCE_DOWN_RIGHT_UP_LEFT]      = MovementType_WalkSequenceDownRightUpLeft,
    [MOVEMENT_TYPE_WALK_SEQUENCE_LEFT_DOWN_RIGHT_UP]      = MovementType_WalkSequenceLeftDownRightUp,
    [MOVEMENT_TYPE_WALK_SEQUENCE_RIGHT_UP_LEFT_DOWN]      = MovementType_WalkSequenceRightUpLeftDown,
    [MOVEMENT_TYPE_WALK_SEQUENCE_UP_RIGHT_DOWN_LEFT]      = MovementType_WalkSequenceUpRightDownLeft,
    [MOVEMENT_TYPE_WALK_SEQUENCE_DOWN_LEFT_UP_RIGHT]      = MovementType_WalkSequenceDownLeftUpRight,
    [MOVEMENT_TYPE_WALK_SEQUENCE_LEFT_UP_RIGHT_DOWN]      = MovementType_WalkSequenceLeftUpRightDown,
    [MOVEMENT_TYPE_WALK_SEQUENCE_RIGHT_DOWN_LEFT_UP]      = MovementType_WalkSequenceRightDownLeftUp,
    [MOVEMENT_TYPE_COPY_PLAYER]                           = MovementType_CopyPlayer,
    [MOVEMENT_TYPE_COPY_PLAYER_OPPOSITE]                  = MovementType_CopyPlayer,
    [MOVEMENT_TYPE_COPY_PLAYER_COUNTERCLOCKWISE]          = MovementType_CopyPlayer,
    [MOVEMENT_TYPE_COPY_PLAYER_CLOCKWISE]                 = MovementType_CopyPlayer,
    [MOVEMENT_TYPE_TREE_DISGUISE]                         = MovementType_TreeDisguise,
    [MOVEMENT_TYPE_MOUNTAIN_DISGUISE]                     = MovementType_MountainDisguise,
    [MOVEMENT_TYPE_COPY_PLAYER_IN_GRASS]                  = MovementType_CopyPlayerInGrass,
    [MOVEMENT_TYPE_COPY_PLAYER_OPPOSITE_IN_GRASS]         = MovementType_CopyPlayerInGrass,
    [MOVEMENT_TYPE_COPY_PLAYER_COUNTERCLOCKWISE_IN_GRASS] = MovementType_CopyPlayerInGrass,
    [MOVEMENT_TYPE_COPY_PLAYER_CLOCKWISE_IN_GRASS]        = MovementType_CopyPlayerInGrass,
    [MOVEMENT_TYPE_BURIED]                                = MovementType_Buried,
    [MOVEMENT_TYPE_WALK_IN_PLACE_DOWN]                    = MovementType_WalkInPlace,
    [MOVEMENT_TYPE_WALK_IN_PLACE_UP]                      = MovementType_WalkInPlace,
    [MOVEMENT_TYPE_WALK_IN_PLACE_LEFT]                    = MovementType_WalkInPlace,
    [MOVEMENT_TYPE_WALK_IN_PLACE_RIGHT]                   = MovementType_WalkInPlace,
    [MOVEMENT_TYPE_WALK_IN_PLACE_FAST_DOWN]               = MovementType_WalkInPlaceFast,
    [MOVEMENT_TYPE_WALK_IN_PLACE_FAST_UP]                 = MovementType_WalkInPlaceFast,
    [MOVEMENT_TYPE_WALK_IN_PLACE_FAST_LEFT]               = MovementType_WalkInPlaceFast,
    [MOVEMENT_TYPE_WALK_IN_PLACE_FAST_RIGHT]              = MovementType_WalkInPlaceFast,
    [MOVEMENT_TYPE_JOG_IN_PLACE_DOWN]                     = MovementType_JogInPlace,
    [MOVEMENT_TYPE_JOG_IN_PLACE_UP]                       = MovementType_JogInPlace,
    [MOVEMENT_TYPE_JOG_IN_PLACE_LEFT]                     = MovementType_JogInPlace,
    [MOVEMENT_TYPE_JOG_IN_PLACE_RIGHT]                    = MovementType_JogInPlace,
    [MOVEMENT_TYPE_INVISIBLE]                             = MovementType_Invisible,
    [MOVEMENT_TYPE_RAISE_HAND_AND_STOP]                   = MovementType_RaiseHandAndStop,
    [MOVEMENT_TYPE_RAISE_HAND_AND_JUMP]                   = MovementType_RaiseHandAndJump,
    [MOVEMENT_TYPE_RAISE_HAND_AND_SWIM]                   = MovementType_RaiseHandAndSwim,
    [MOVEMENT_TYPE_WANDER_AROUND_SLOWER]                  = MovementType_WanderAroundSlower,
};

static const bool8 gRangedMovementTypes[MOVEMENT_TYPES_COUNT] = {
    [MOVEMENT_TYPE_WANDER_AROUND] = TRUE,
    [MOVEMENT_TYPE_WANDER_UP_AND_DOWN] = TRUE,
    [MOVEMENT_TYPE_WANDER_DOWN_AND_UP] = TRUE,
    [MOVEMENT_TYPE_WANDER_LEFT_AND_RIGHT] = TRUE,
    [MOVEMENT_TYPE_WANDER_RIGHT_AND_LEFT] = TRUE,
    [MOVEMENT_TYPE_WALK_UP_AND_DOWN] = TRUE,
    [MOVEMENT_TYPE_WALK_DOWN_AND_UP] = TRUE,
    [MOVEMENT_TYPE_WALK_LEFT_AND_RIGHT] = TRUE,
    [MOVEMENT_TYPE_WALK_RIGHT_AND_LEFT] = TRUE,
    [MOVEMENT_TYPE_WALK_SEQUENCE_UP_RIGHT_LEFT_DOWN] = TRUE,
    [MOVEMENT_TYPE_WALK_SEQUENCE_RIGHT_LEFT_DOWN_UP] = TRUE,
    [MOVEMENT_TYPE_WALK_SEQUENCE_DOWN_UP_RIGHT_LEFT] = TRUE,
    [MOVEMENT_TYPE_WALK_SEQUENCE_LEFT_DOWN_UP_RIGHT] = TRUE,
    [MOVEMENT_TYPE_WALK_SEQUENCE_UP_LEFT_RIGHT_DOWN] = TRUE,
    [MOVEMENT_TYPE_WALK_SEQUENCE_LEFT_RIGHT_DOWN_UP] = TRUE,
    [MOVEMENT_TYPE_WALK_SEQUENCE_DOWN_UP_LEFT_RIGHT] = TRUE,
    [MOVEMENT_TYPE_WALK_SEQUENCE_RIGHT_DOWN_UP_LEFT] = TRUE,
    [MOVEMENT_TYPE_WALK_SEQUENCE_LEFT_UP_DOWN_RIGHT] = TRUE,
    [MOVEMENT_TYPE_WALK_SEQUENCE_UP_DOWN_RIGHT_LEFT] = TRUE,
    [MOVEMENT_TYPE_WALK_SEQUENCE_RIGHT_LEFT_UP_DOWN] = TRUE,
    [MOVEMENT_TYPE_WALK_SEQUENCE_DOWN_RIGHT_LEFT_UP] = TRUE,
    [MOVEMENT_TYPE_WALK_SEQUENCE_RIGHT_UP_DOWN_LEFT] = TRUE,
    [MOVEMENT_TYPE_WALK_SEQUENCE_UP_DOWN_LEFT_RIGHT] = TRUE,
    [MOVEMENT_TYPE_WALK_SEQUENCE_LEFT_RIGHT_UP_DOWN] = TRUE,
    [MOVEMENT_TYPE_WALK_SEQUENCE_DOWN_LEFT_RIGHT_UP] = TRUE,
    [MOVEMENT_TYPE_WALK_SEQUENCE_UP_LEFT_DOWN_RIGHT] = TRUE,
    [MOVEMENT_TYPE_WALK_SEQUENCE_DOWN_RIGHT_UP_LEFT] = TRUE,
    [MOVEMENT_TYPE_WALK_SEQUENCE_LEFT_DOWN_RIGHT_UP] = TRUE,
    [MOVEMENT_TYPE_WALK_SEQUENCE_RIGHT_UP_LEFT_DOWN] = TRUE,
    [MOVEMENT_TYPE_WALK_SEQUENCE_UP_RIGHT_DOWN_LEFT] = TRUE,
    [MOVEMENT_TYPE_WALK_SEQUENCE_DOWN_LEFT_UP_RIGHT] = TRUE,
    [MOVEMENT_TYPE_WALK_SEQUENCE_LEFT_UP_RIGHT_DOWN] = TRUE,
    [MOVEMENT_TYPE_WALK_SEQUENCE_RIGHT_DOWN_LEFT_UP] = TRUE,
    [MOVEMENT_TYPE_COPY_PLAYER] = TRUE,
    [MOVEMENT_TYPE_COPY_PLAYER_OPPOSITE] = TRUE,
    [MOVEMENT_TYPE_COPY_PLAYER_COUNTERCLOCKWISE] = TRUE,
    [MOVEMENT_TYPE_COPY_PLAYER_CLOCKWISE] = TRUE,
    [MOVEMENT_TYPE_COPY_PLAYER_IN_GRASS] = TRUE,
    [MOVEMENT_TYPE_COPY_PLAYER_OPPOSITE_IN_GRASS] = TRUE,
    [MOVEMENT_TYPE_COPY_PLAYER_COUNTERCLOCKWISE_IN_GRASS] = TRUE,
    [MOVEMENT_TYPE_COPY_PLAYER_CLOCKWISE_IN_GRASS] = TRUE,
    [MOVEMENT_TYPE_WANDER_AROUND_SLOWER] = TRUE,
};

static const u8 gInitialMovementTypeFacingDirections[MOVEMENT_TYPES_COUNT] = {
    [MOVEMENT_TYPE_NONE] = DIR_SOUTH,
    [MOVEMENT_TYPE_LOOK_AROUND] = DIR_SOUTH,
    [MOVEMENT_TYPE_WANDER_AROUND] = DIR_SOUTH,
    [MOVEMENT_TYPE_WANDER_UP_AND_DOWN] = DIR_NORTH,
    [MOVEMENT_TYPE_WANDER_DOWN_AND_UP] = DIR_SOUTH,
    [MOVEMENT_TYPE_WANDER_LEFT_AND_RIGHT] = DIR_WEST,
    [MOVEMENT_TYPE_WANDER_RIGHT_AND_LEFT] = DIR_EAST,
    [MOVEMENT_TYPE_FACE_UP] = DIR_NORTH,
    [MOVEMENT_TYPE_FACE_DOWN] = DIR_SOUTH,
    [MOVEMENT_TYPE_FACE_LEFT] = DIR_WEST,
    [MOVEMENT_TYPE_FACE_RIGHT] = DIR_EAST,
    [MOVEMENT_TYPE_PLAYER] = DIR_SOUTH,
    [MOVEMENT_TYPE_BERRY_TREE_GROWTH] = DIR_SOUTH,
    [MOVEMENT_TYPE_FACE_DOWN_AND_UP] = DIR_SOUTH,
    [MOVEMENT_TYPE_FACE_LEFT_AND_RIGHT] = DIR_WEST,
    [MOVEMENT_TYPE_FACE_UP_AND_LEFT] = DIR_NORTH,
    [MOVEMENT_TYPE_FACE_UP_AND_RIGHT] = DIR_NORTH,
    [MOVEMENT_TYPE_FACE_DOWN_AND_LEFT] = DIR_SOUTH,
    [MOVEMENT_TYPE_FACE_DOWN_AND_RIGHT] = DIR_SOUTH,
    [MOVEMENT_TYPE_FACE_DOWN_UP_AND_LEFT] = DIR_SOUTH,
    [MOVEMENT_TYPE_FACE_DOWN_UP_AND_RIGHT] = DIR_SOUTH,
    [MOVEMENT_TYPE_FACE_UP_LEFT_AND_RIGHT] = DIR_NORTH,
    [MOVEMENT_TYPE_FACE_DOWN_LEFT_AND_RIGHT] = DIR_SOUTH,
    [MOVEMENT_TYPE_ROTATE_COUNTERCLOCKWISE] = DIR_SOUTH,
    [MOVEMENT_TYPE_ROTATE_CLOCKWISE] = DIR_SOUTH,
    [MOVEMENT_TYPE_WALK_UP_AND_DOWN] = DIR_NORTH,
    [MOVEMENT_TYPE_WALK_DOWN_AND_UP] = DIR_SOUTH,
    [MOVEMENT_TYPE_WALK_LEFT_AND_RIGHT] = DIR_WEST,
    [MOVEMENT_TYPE_WALK_RIGHT_AND_LEFT] = DIR_EAST,
    [MOVEMENT_TYPE_WALK_SEQUENCE_UP_RIGHT_LEFT_DOWN] = DIR_NORTH,
    [MOVEMENT_TYPE_WALK_SEQUENCE_RIGHT_LEFT_DOWN_UP] = DIR_EAST,
    [MOVEMENT_TYPE_WALK_SEQUENCE_DOWN_UP_RIGHT_LEFT] = DIR_SOUTH,
    [MOVEMENT_TYPE_WALK_SEQUENCE_LEFT_DOWN_UP_RIGHT] = DIR_WEST,
    [MOVEMENT_TYPE_WALK_SEQUENCE_UP_LEFT_RIGHT_DOWN] = DIR_NORTH,
    [MOVEMENT_TYPE_WALK_SEQUENCE_LEFT_RIGHT_DOWN_UP] = DIR_WEST,
    [MOVEMENT_TYPE_WALK_SEQUENCE_DOWN_UP_LEFT_RIGHT] = DIR_SOUTH,
    [MOVEMENT_TYPE_WALK_SEQUENCE_RIGHT_DOWN_UP_LEFT] = DIR_EAST,
    [MOVEMENT_TYPE_WALK_SEQUENCE_LEFT_UP_DOWN_RIGHT] = DIR_WEST,
    [MOVEMENT_TYPE_WALK_SEQUENCE_UP_DOWN_RIGHT_LEFT] = DIR_NORTH,
    [MOVEMENT_TYPE_WALK_SEQUENCE_RIGHT_LEFT_UP_DOWN] = DIR_EAST,
    [MOVEMENT_TYPE_WALK_SEQUENCE_DOWN_RIGHT_LEFT_UP] = DIR_SOUTH,
    [MOVEMENT_TYPE_WALK_SEQUENCE_RIGHT_UP_DOWN_LEFT] = DIR_EAST,
    [MOVEMENT_TYPE_WALK_SEQUENCE_UP_DOWN_LEFT_RIGHT] = DIR_NORTH,
    [MOVEMENT_TYPE_WALK_SEQUENCE_LEFT_RIGHT_UP_DOWN] = DIR_WEST,
    [MOVEMENT_TYPE_WALK_SEQUENCE_DOWN_LEFT_RIGHT_UP] = DIR_SOUTH,
    [MOVEMENT_TYPE_WALK_SEQUENCE_UP_LEFT_DOWN_RIGHT] = DIR_NORTH,
    [MOVEMENT_TYPE_WALK_SEQUENCE_DOWN_RIGHT_UP_LEFT] = DIR_SOUTH,
    [MOVEMENT_TYPE_WALK_SEQUENCE_LEFT_DOWN_RIGHT_UP] = DIR_WEST,
    [MOVEMENT_TYPE_WALK_SEQUENCE_RIGHT_UP_LEFT_DOWN] = DIR_EAST,
    [MOVEMENT_TYPE_WALK_SEQUENCE_UP_RIGHT_DOWN_LEFT] = DIR_NORTH,
    [MOVEMENT_TYPE_WALK_SEQUENCE_DOWN_LEFT_UP_RIGHT] = DIR_SOUTH,
    [MOVEMENT_TYPE_WALK_SEQUENCE_LEFT_UP_RIGHT_DOWN] = DIR_WEST,
    [MOVEMENT_TYPE_WALK_SEQUENCE_RIGHT_DOWN_LEFT_UP] = DIR_EAST,
    [MOVEMENT_TYPE_COPY_PLAYER] = DIR_NORTH,
    [MOVEMENT_TYPE_COPY_PLAYER_OPPOSITE] = DIR_SOUTH,
    [MOVEMENT_TYPE_COPY_PLAYER_COUNTERCLOCKWISE] = DIR_WEST,
    [MOVEMENT_TYPE_COPY_PLAYER_CLOCKWISE] = DIR_EAST,
    [MOVEMENT_TYPE_TREE_DISGUISE] = DIR_SOUTH,
    [MOVEMENT_TYPE_MOUNTAIN_DISGUISE] = DIR_SOUTH,
    [MOVEMENT_TYPE_COPY_PLAYER_IN_GRASS] = DIR_NORTH,
    [MOVEMENT_TYPE_COPY_PLAYER_OPPOSITE_IN_GRASS] = DIR_SOUTH,
    [MOVEMENT_TYPE_COPY_PLAYER_COUNTERCLOCKWISE_IN_GRASS] = DIR_WEST,
    [MOVEMENT_TYPE_COPY_PLAYER_CLOCKWISE_IN_GRASS] = DIR_EAST,
    [MOVEMENT_TYPE_BURIED] = DIR_SOUTH,
    [MOVEMENT_TYPE_WALK_IN_PLACE_DOWN] = DIR_SOUTH,
    [MOVEMENT_TYPE_WALK_IN_PLACE_UP] = DIR_NORTH,
    [MOVEMENT_TYPE_WALK_IN_PLACE_LEFT] = DIR_WEST,
    [MOVEMENT_TYPE_WALK_IN_PLACE_RIGHT] = DIR_EAST,
    [MOVEMENT_TYPE_WALK_IN_PLACE_FAST_DOWN] = DIR_SOUTH,
    [MOVEMENT_TYPE_WALK_IN_PLACE_FAST_UP] = DIR_NORTH,
    [MOVEMENT_TYPE_WALK_IN_PLACE_FAST_LEFT] = DIR_WEST,
    [MOVEMENT_TYPE_WALK_IN_PLACE_FAST_RIGHT] = DIR_EAST,
    [MOVEMENT_TYPE_JOG_IN_PLACE_DOWN] = DIR_SOUTH,
    [MOVEMENT_TYPE_JOG_IN_PLACE_UP] = DIR_NORTH,
    [MOVEMENT_TYPE_JOG_IN_PLACE_LEFT] = DIR_WEST,
    [MOVEMENT_TYPE_JOG_IN_PLACE_RIGHT] = DIR_EAST,
    [MOVEMENT_TYPE_INVISIBLE] = DIR_SOUTH,
    [MOVEMENT_TYPE_RAISE_HAND_AND_STOP] = DIR_SOUTH,
    [MOVEMENT_TYPE_RAISE_HAND_AND_JUMP] = DIR_SOUTH,
    [MOVEMENT_TYPE_RAISE_HAND_AND_SWIM] = DIR_SOUTH,
    [MOVEMENT_TYPE_WANDER_AROUND_SLOWER] = DIR_SOUTH,
};

#define OBJ_EVENT_PAL_TAG_PLAYER_RED                  0x1100
#define OBJ_EVENT_PAL_TAG_PLAYER_RED_REFLECTION       0x1101
#define OBJ_EVENT_PAL_TAG_BRIDGE_REFLECTION           0x1102
#define OBJ_EVENT_PAL_TAG_NPC_BLUE                    0x1103
#define OBJ_EVENT_PAL_TAG_NPC_PINK                    0x1104
#define OBJ_EVENT_PAL_TAG_NPC_GREEN                   0x1105
#define OBJ_EVENT_PAL_TAG_NPC_WHITE                   0x1106
#define OBJ_EVENT_PAL_TAG_NPC_BLUE_REFLECTION         0x1107
#define OBJ_EVENT_PAL_TAG_NPC_PINK_REFLECTION         0x1108
#define OBJ_EVENT_PAL_TAG_NPC_GREEN_REFLECTION        0x1109
#define OBJ_EVENT_PAL_TAG_NPC_WHITE_REFLECTION        0x110A
#define OBJ_EVENT_PAL_TAG_RS_QUINTY_PLUMP             0x110B
#define OBJ_EVENT_PAL_TAG_RS_QUINTY_PLUMP_REFLECTION  0x110C
#define OBJ_EVENT_PAL_TAG_RS_TRUCK                    0x110D
#define OBJ_EVENT_PAL_TAG_RS_MACHOKE                  0x110E
#define OBJ_EVENT_PAL_TAG_RS_POOCHYENA                0x110F
#define OBJ_EVENT_PAL_TAG_PLAYER_GREEN                0x1110
#define OBJ_EVENT_PAL_TAG_PLAYER_GREEN_REFLECTION     0x1111
#define OBJ_EVENT_PAL_TAG_RS_MOVING_BOX               0x1112
#define OBJ_EVENT_PAL_TAG_METEORITE                   0x1113
#define OBJ_EVENT_PAL_TAG_SEAGALLOP                   0x1114
#define OBJ_EVENT_PAL_TAG_SS_ANNE                     0x1115
#define OBJ_EVENT_PAL_TAG_RS_PLAYER_UNDERWATER        0x1116
#define OBJ_EVENT_PAL_TAG_RS_KYOGRE                   0x1117
#define OBJ_EVENT_PAL_TAG_RS_KYOGRE_REFLECTION        0x1118
#define OBJ_EVENT_PAL_TAG_RS_GROUDON                  0x1119
#define OBJ_EVENT_PAL_TAG_RS_GROUDON_REFLECTION       0x111A
#define OBJ_EVENT_PAL_TAG_RS_SUBMARINE_SHADOW         0x111B
#define OBJ_EVENT_PAL_TAG_NONE                        0x11FF

// ===== BEGIN src/data/object_events/object_event_graphics_info_pointers.h =====
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_RedNormal;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_RedBike;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_RedSurf;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_RedFieldMove;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_RedFish;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_RedVSSeeker;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_RedVSSeekerBike;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_GreenNormal;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_GreenBike;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_GreenSurf;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_GreenFieldMove;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_GreenFish;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_GreenVSSeeker;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_GreenVSSeekerBike;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_RSBrendan;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_RSMay;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_LittleBoy;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_LittleGirl;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Youngster;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Boy;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_BugCatcher;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_SittingBoy;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Lass;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Woman1;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_CrushGirl;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Man;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Rocker;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_FatMan;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Woman2;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Beauty;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_BaldingMan;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Woman3;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_OldMan1;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_OldMan2;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_OldManLyingDown;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_OldWoman;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_TuberMWater;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_TuberF;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_TuberMLand;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Camper;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Picnicker;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_CooltrainerM;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_CooltrainerF;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_SwimmerMWater;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_SwimmerFWater;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_SwimmerMLand;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_SwimmerFLand;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_WorkerM;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_WorkerF;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_RocketM;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_RocketF;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_GBAKid;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_PokeManiac;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Biker;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_BlackBelt;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Scientist;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Hiker;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Fisher;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Channeler;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Chef;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Policeman;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Gentleman;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Sailor;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Captain;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Nurse;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_CableClubReceptionist;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_UnionRoomReceptionist;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_UnusedMaleReceptionist;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Clerk;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_MGDeliveryman;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_TrainerTowerDude;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_ProfOak;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Blue;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Bill;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Lance;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Agatha;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Daisy;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Lorelei;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_MrFuji;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Bruno;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Brock;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Misty;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_LtSurge;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Erika;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Koga;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Sabrina;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Blaine;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Giovanni;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Mom;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Celio;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_TeachyTVHost;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_GymGuy;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_ItemBall;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_TownMap;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Pokedex;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_CutTree;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_RockSmashRock;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_StrengthBoulder;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Fossil;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Ruby;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Sapphire;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_OldAmber;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_GymSign;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Sign;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_TrainerTips;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Clipboard;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Meteorite;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_LaprasDoll;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Seagallop;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Snorlax;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Spearow;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Cubone;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Poliwrath;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Clefairy;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Pidgeot;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Jigglypuff;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Pidgey;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Chansey;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Omanyte;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Kangaskhan;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Pikachu;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Psyduck;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_NidoranF;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_NidoranM;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Nidorino;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Meowth;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Seel;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Voltorb;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Slowpoke;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Slowbro;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Machop;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Wigglytuff;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Doduo;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Fearow;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Machoke;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Lapras;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Zapdos;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Moltres;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Articuno;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Mewtwo;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Mew;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Entei;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Suicune;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Raikou;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Lugia;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_HoOh;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Celebi;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Kabuto;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_DeoxysD;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_DeoxysA;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_DeoxysN;
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_SSAnne;


const struct ObjectEventGraphicsInfo *const gObjectEventGraphicsInfoPointers[NUM_OBJ_EVENT_GFX] = {
    [OBJ_EVENT_GFX_RED_NORMAL]               = &gObjectEventGraphicsInfo_RedNormal,
    [OBJ_EVENT_GFX_RED_BIKE]                 = &gObjectEventGraphicsInfo_RedBike,
    [OBJ_EVENT_GFX_RED_SURF]                 = &gObjectEventGraphicsInfo_RedSurf,
    [OBJ_EVENT_GFX_RED_FIELD_MOVE]           = &gObjectEventGraphicsInfo_RedFieldMove,
    [OBJ_EVENT_GFX_RED_FISH]                 = &gObjectEventGraphicsInfo_RedFish,
    [OBJ_EVENT_GFX_RED_VS_SEEKER]            = &gObjectEventGraphicsInfo_RedVSSeeker,
    [OBJ_EVENT_GFX_RED_VS_SEEKER_BIKE]       = &gObjectEventGraphicsInfo_RedVSSeekerBike,
    [OBJ_EVENT_GFX_GREEN_NORMAL]             = &gObjectEventGraphicsInfo_GreenNormal,
    [OBJ_EVENT_GFX_GREEN_BIKE]               = &gObjectEventGraphicsInfo_GreenBike,
    [OBJ_EVENT_GFX_GREEN_SURF]               = &gObjectEventGraphicsInfo_GreenSurf,
    [OBJ_EVENT_GFX_GREEN_FIELD_MOVE]         = &gObjectEventGraphicsInfo_GreenFieldMove,
    [OBJ_EVENT_GFX_GREEN_FISH]               = &gObjectEventGraphicsInfo_GreenFish,
    [OBJ_EVENT_GFX_GREEN_VS_SEEKER]          = &gObjectEventGraphicsInfo_GreenVSSeeker,
    [OBJ_EVENT_GFX_GREEN_VS_SEEKER_BIKE]     = &gObjectEventGraphicsInfo_GreenVSSeekerBike,
    [OBJ_EVENT_GFX_RS_BRENDAN]               = &gObjectEventGraphicsInfo_RSBrendan,
    [OBJ_EVENT_GFX_RS_MAY]                   = &gObjectEventGraphicsInfo_RSMay,
    [OBJ_EVENT_GFX_LITTLE_BOY]               = &gObjectEventGraphicsInfo_LittleBoy,
    [OBJ_EVENT_GFX_LITTLE_GIRL]              = &gObjectEventGraphicsInfo_LittleGirl,
    [OBJ_EVENT_GFX_YOUNGSTER]                = &gObjectEventGraphicsInfo_Youngster,
    [OBJ_EVENT_GFX_BOY]                      = &gObjectEventGraphicsInfo_Boy,
    [OBJ_EVENT_GFX_BUG_CATCHER]              = &gObjectEventGraphicsInfo_BugCatcher,
    [OBJ_EVENT_GFX_SITTING_BOY]              = &gObjectEventGraphicsInfo_SittingBoy,
    [OBJ_EVENT_GFX_LASS]                     = &gObjectEventGraphicsInfo_Lass,
    [OBJ_EVENT_GFX_WOMAN_1]                  = &gObjectEventGraphicsInfo_Woman1,
    [OBJ_EVENT_GFX_CRUSH_GIRL]               = &gObjectEventGraphicsInfo_CrushGirl,
    [OBJ_EVENT_GFX_MAN]                      = &gObjectEventGraphicsInfo_Man,
    [OBJ_EVENT_GFX_ROCKER]                   = &gObjectEventGraphicsInfo_Rocker,
    [OBJ_EVENT_GFX_FAT_MAN]                  = &gObjectEventGraphicsInfo_FatMan,
    [OBJ_EVENT_GFX_WOMAN_2]                  = &gObjectEventGraphicsInfo_Woman2,
    [OBJ_EVENT_GFX_BEAUTY]                   = &gObjectEventGraphicsInfo_Beauty,
    [OBJ_EVENT_GFX_BALDING_MAN]              = &gObjectEventGraphicsInfo_BaldingMan,
    [OBJ_EVENT_GFX_WOMAN_3]                  = &gObjectEventGraphicsInfo_Woman3,
    [OBJ_EVENT_GFX_OLD_MAN_1]                = &gObjectEventGraphicsInfo_OldMan1,
    [OBJ_EVENT_GFX_OLD_MAN_2]                = &gObjectEventGraphicsInfo_OldMan2,
    [OBJ_EVENT_GFX_OLD_MAN_LYING_DOWN]       = &gObjectEventGraphicsInfo_OldManLyingDown,
    [OBJ_EVENT_GFX_OLD_WOMAN]                = &gObjectEventGraphicsInfo_OldWoman,
    [OBJ_EVENT_GFX_TUBER_M_WATER]            = &gObjectEventGraphicsInfo_TuberMWater,
    [OBJ_EVENT_GFX_TUBER_F]                  = &gObjectEventGraphicsInfo_TuberF,
    [OBJ_EVENT_GFX_TUBER_M_LAND]             = &gObjectEventGraphicsInfo_TuberMLand,
    [OBJ_EVENT_GFX_CAMPER]                   = &gObjectEventGraphicsInfo_Camper,
    [OBJ_EVENT_GFX_PICNICKER]                = &gObjectEventGraphicsInfo_Picnicker,
    [OBJ_EVENT_GFX_COOLTRAINER_M]            = &gObjectEventGraphicsInfo_CooltrainerM,
    [OBJ_EVENT_GFX_COOLTRAINER_F]            = &gObjectEventGraphicsInfo_CooltrainerF,
    [OBJ_EVENT_GFX_SWIMMER_M_WATER]          = &gObjectEventGraphicsInfo_SwimmerMWater,
    [OBJ_EVENT_GFX_SWIMMER_F_WATER]          = &gObjectEventGraphicsInfo_SwimmerFWater,
    [OBJ_EVENT_GFX_SWIMMER_M_LAND]           = &gObjectEventGraphicsInfo_SwimmerMLand,
    [OBJ_EVENT_GFX_SWIMMER_F_LAND]           = &gObjectEventGraphicsInfo_SwimmerFLand,
    [OBJ_EVENT_GFX_WORKER_M]                 = &gObjectEventGraphicsInfo_WorkerM,
    [OBJ_EVENT_GFX_WORKER_F]                 = &gObjectEventGraphicsInfo_WorkerF,
    [OBJ_EVENT_GFX_ROCKET_M]                 = &gObjectEventGraphicsInfo_RocketM,
    [OBJ_EVENT_GFX_ROCKET_F]                 = &gObjectEventGraphicsInfo_RocketF,
    [OBJ_EVENT_GFX_GBA_KID]                  = &gObjectEventGraphicsInfo_GBAKid,
    [OBJ_EVENT_GFX_POKE_MANIAC]              = &gObjectEventGraphicsInfo_PokeManiac,
    [OBJ_EVENT_GFX_BIKER]                    = &gObjectEventGraphicsInfo_Biker,
    [OBJ_EVENT_GFX_BLACK_BELT]               = &gObjectEventGraphicsInfo_BlackBelt,
    [OBJ_EVENT_GFX_SCIENTIST]                = &gObjectEventGraphicsInfo_Scientist,
    [OBJ_EVENT_GFX_HIKER]                    = &gObjectEventGraphicsInfo_Hiker,
    [OBJ_EVENT_GFX_FISHER]                   = &gObjectEventGraphicsInfo_Fisher,
    [OBJ_EVENT_GFX_CHANNELER]                = &gObjectEventGraphicsInfo_Channeler,
    [OBJ_EVENT_GFX_CHEF]                     = &gObjectEventGraphicsInfo_Chef,
    [OBJ_EVENT_GFX_POLICEMAN]                = &gObjectEventGraphicsInfo_Policeman,
    [OBJ_EVENT_GFX_GENTLEMAN]                = &gObjectEventGraphicsInfo_Gentleman,
    [OBJ_EVENT_GFX_SAILOR]                   = &gObjectEventGraphicsInfo_Sailor,
    [OBJ_EVENT_GFX_CAPTAIN]                  = &gObjectEventGraphicsInfo_Captain,
    [OBJ_EVENT_GFX_NURSE]                    = &gObjectEventGraphicsInfo_Nurse,
    [OBJ_EVENT_GFX_CABLE_CLUB_RECEPTIONIST]  = &gObjectEventGraphicsInfo_CableClubReceptionist,
    [OBJ_EVENT_GFX_UNION_ROOM_RECEPTIONIST]  = &gObjectEventGraphicsInfo_UnionRoomReceptionist,
    [OBJ_EVENT_GFX_UNUSED_MALE_RECEPTIONIST] = &gObjectEventGraphicsInfo_UnusedMaleReceptionist,
    [OBJ_EVENT_GFX_CLERK]                    = &gObjectEventGraphicsInfo_Clerk,
    [OBJ_EVENT_GFX_MG_DELIVERYMAN]           = &gObjectEventGraphicsInfo_MGDeliveryman,
    [OBJ_EVENT_GFX_TRAINER_TOWER_DUDE]       = &gObjectEventGraphicsInfo_TrainerTowerDude,
    [OBJ_EVENT_GFX_PROF_OAK]                 = &gObjectEventGraphicsInfo_ProfOak,
    [OBJ_EVENT_GFX_BLUE]                     = &gObjectEventGraphicsInfo_Blue,
    [OBJ_EVENT_GFX_BILL]                     = &gObjectEventGraphicsInfo_Bill,
    [OBJ_EVENT_GFX_LANCE]                    = &gObjectEventGraphicsInfo_Lance,
    [OBJ_EVENT_GFX_AGATHA]                   = &gObjectEventGraphicsInfo_Agatha,
    [OBJ_EVENT_GFX_DAISY]                    = &gObjectEventGraphicsInfo_Daisy,
    [OBJ_EVENT_GFX_LORELEI]                  = &gObjectEventGraphicsInfo_Lorelei,
    [OBJ_EVENT_GFX_MR_FUJI]                  = &gObjectEventGraphicsInfo_MrFuji,
    [OBJ_EVENT_GFX_BRUNO]                    = &gObjectEventGraphicsInfo_Bruno,
    [OBJ_EVENT_GFX_BROCK]                    = &gObjectEventGraphicsInfo_Brock,
    [OBJ_EVENT_GFX_MISTY]                    = &gObjectEventGraphicsInfo_Misty,
    [OBJ_EVENT_GFX_LT_SURGE]                 = &gObjectEventGraphicsInfo_LtSurge,
    [OBJ_EVENT_GFX_ERIKA]                    = &gObjectEventGraphicsInfo_Erika,
    [OBJ_EVENT_GFX_KOGA]                     = &gObjectEventGraphicsInfo_Koga,
    [OBJ_EVENT_GFX_SABRINA]                  = &gObjectEventGraphicsInfo_Sabrina,
    [OBJ_EVENT_GFX_BLAINE]                   = &gObjectEventGraphicsInfo_Blaine,
    [OBJ_EVENT_GFX_GIOVANNI]                 = &gObjectEventGraphicsInfo_Giovanni,
    [OBJ_EVENT_GFX_MOM]                      = &gObjectEventGraphicsInfo_Mom,
    [OBJ_EVENT_GFX_CELIO]                    = &gObjectEventGraphicsInfo_Celio,
    [OBJ_EVENT_GFX_TEACHY_TV_HOST]           = &gObjectEventGraphicsInfo_TeachyTVHost,
    [OBJ_EVENT_GFX_GYM_GUY]                  = &gObjectEventGraphicsInfo_GymGuy,
    [OBJ_EVENT_GFX_ITEM_BALL]                = &gObjectEventGraphicsInfo_ItemBall,
    [OBJ_EVENT_GFX_TOWN_MAP]                 = &gObjectEventGraphicsInfo_TownMap,
    [OBJ_EVENT_GFX_POKEDEX]                  = &gObjectEventGraphicsInfo_Pokedex,
    [OBJ_EVENT_GFX_CUT_TREE]                 = &gObjectEventGraphicsInfo_CutTree,
    [OBJ_EVENT_GFX_ROCK_SMASH_ROCK]          = &gObjectEventGraphicsInfo_RockSmashRock,
    [OBJ_EVENT_GFX_PUSHABLE_BOULDER]         = &gObjectEventGraphicsInfo_StrengthBoulder,
    [OBJ_EVENT_GFX_FOSSIL]                   = &gObjectEventGraphicsInfo_Fossil,
    [OBJ_EVENT_GFX_RUBY]                     = &gObjectEventGraphicsInfo_Ruby,
    [OBJ_EVENT_GFX_SAPPHIRE]                 = &gObjectEventGraphicsInfo_Sapphire,
    [OBJ_EVENT_GFX_OLD_AMBER]                = &gObjectEventGraphicsInfo_OldAmber,
    [OBJ_EVENT_GFX_GYM_SIGN]                 = &gObjectEventGraphicsInfo_GymSign,
    [OBJ_EVENT_GFX_SIGN]                     = &gObjectEventGraphicsInfo_Sign,
    [OBJ_EVENT_GFX_TRAINER_TIPS]             = &gObjectEventGraphicsInfo_TrainerTips,
    [OBJ_EVENT_GFX_CLIPBOARD]                = &gObjectEventGraphicsInfo_Clipboard,
    [OBJ_EVENT_GFX_METEORITE]                = &gObjectEventGraphicsInfo_Meteorite,
    [OBJ_EVENT_GFX_LAPRAS_DOLL]              = &gObjectEventGraphicsInfo_LaprasDoll,
    [OBJ_EVENT_GFX_SEAGALLOP]                = &gObjectEventGraphicsInfo_Seagallop,
    [OBJ_EVENT_GFX_SNORLAX]                  = &gObjectEventGraphicsInfo_Snorlax,
    [OBJ_EVENT_GFX_SPEAROW]                  = &gObjectEventGraphicsInfo_Spearow,
    [OBJ_EVENT_GFX_CUBONE]                   = &gObjectEventGraphicsInfo_Cubone,
    [OBJ_EVENT_GFX_POLIWRATH]                = &gObjectEventGraphicsInfo_Poliwrath,
    [OBJ_EVENT_GFX_CLEFAIRY]                 = &gObjectEventGraphicsInfo_Clefairy,
    [OBJ_EVENT_GFX_PIDGEOT]                  = &gObjectEventGraphicsInfo_Pidgeot,
    [OBJ_EVENT_GFX_JIGGLYPUFF]               = &gObjectEventGraphicsInfo_Jigglypuff,
    [OBJ_EVENT_GFX_PIDGEY]                   = &gObjectEventGraphicsInfo_Pidgey,
    [OBJ_EVENT_GFX_CHANSEY]                  = &gObjectEventGraphicsInfo_Chansey,
    [OBJ_EVENT_GFX_OMANYTE]                  = &gObjectEventGraphicsInfo_Omanyte,
    [OBJ_EVENT_GFX_KANGASKHAN]               = &gObjectEventGraphicsInfo_Kangaskhan,
    [OBJ_EVENT_GFX_PIKACHU]                  = &gObjectEventGraphicsInfo_Pikachu,
    [OBJ_EVENT_GFX_PSYDUCK]                  = &gObjectEventGraphicsInfo_Psyduck,
    [OBJ_EVENT_GFX_NIDORAN_F]                = &gObjectEventGraphicsInfo_NidoranF,
    [OBJ_EVENT_GFX_NIDORAN_M]                = &gObjectEventGraphicsInfo_NidoranM,
    [OBJ_EVENT_GFX_NIDORINO]                 = &gObjectEventGraphicsInfo_Nidorino,
    [OBJ_EVENT_GFX_MEOWTH]                   = &gObjectEventGraphicsInfo_Meowth,
    [OBJ_EVENT_GFX_SEEL]                     = &gObjectEventGraphicsInfo_Seel,
    [OBJ_EVENT_GFX_VOLTORB]                  = &gObjectEventGraphicsInfo_Voltorb,
    [OBJ_EVENT_GFX_SLOWPOKE]                 = &gObjectEventGraphicsInfo_Slowpoke,
    [OBJ_EVENT_GFX_SLOWBRO]                  = &gObjectEventGraphicsInfo_Slowbro,
    [OBJ_EVENT_GFX_MACHOP]                   = &gObjectEventGraphicsInfo_Machop,
    [OBJ_EVENT_GFX_WIGGLYTUFF]               = &gObjectEventGraphicsInfo_Wigglytuff,
    [OBJ_EVENT_GFX_DODUO]                    = &gObjectEventGraphicsInfo_Doduo,
    [OBJ_EVENT_GFX_FEAROW]                   = &gObjectEventGraphicsInfo_Fearow,
    [OBJ_EVENT_GFX_MACHOKE]                  = &gObjectEventGraphicsInfo_Machoke,
    [OBJ_EVENT_GFX_LAPRAS]                   = &gObjectEventGraphicsInfo_Lapras,
    [OBJ_EVENT_GFX_ZAPDOS]                   = &gObjectEventGraphicsInfo_Zapdos,
    [OBJ_EVENT_GFX_MOLTRES]                  = &gObjectEventGraphicsInfo_Moltres,
    [OBJ_EVENT_GFX_ARTICUNO]                 = &gObjectEventGraphicsInfo_Articuno,
    [OBJ_EVENT_GFX_MEWTWO]                   = &gObjectEventGraphicsInfo_Mewtwo,
    [OBJ_EVENT_GFX_MEW]                      = &gObjectEventGraphicsInfo_Mew,
    [OBJ_EVENT_GFX_ENTEI]                    = &gObjectEventGraphicsInfo_Entei,
    [OBJ_EVENT_GFX_SUICUNE]                  = &gObjectEventGraphicsInfo_Suicune,
    [OBJ_EVENT_GFX_RAIKOU]                   = &gObjectEventGraphicsInfo_Raikou,
    [OBJ_EVENT_GFX_LUGIA]                    = &gObjectEventGraphicsInfo_Lugia,
    [OBJ_EVENT_GFX_HO_OH]                    = &gObjectEventGraphicsInfo_HoOh,
    [OBJ_EVENT_GFX_CELEBI]                   = &gObjectEventGraphicsInfo_Celebi,
    [OBJ_EVENT_GFX_KABUTO]                   = &gObjectEventGraphicsInfo_Kabuto,
    [OBJ_EVENT_GFX_DEOXYS_D]                 = &gObjectEventGraphicsInfo_DeoxysD,
    [OBJ_EVENT_GFX_DEOXYS_A]                 = &gObjectEventGraphicsInfo_DeoxysA,
    [OBJ_EVENT_GFX_DEOXYS_N]                 = &gObjectEventGraphicsInfo_DeoxysN,
    [OBJ_EVENT_GFX_SS_ANNE]                  = &gObjectEventGraphicsInfo_SSAnne,
};
// ===== END src/data/object_events/object_event_graphics_info_pointers.h =====
// ===== BEGIN src/data/field_effects/field_effect_object_template_pointers.h =====
const struct SpriteTemplate gFieldEffectObjectTemplate_ShadowSmall;
const struct SpriteTemplate gFieldEffectObjectTemplate_ShadowMedium;
const struct SpriteTemplate gFieldEffectObjectTemplate_ShadowLarge;
const struct SpriteTemplate gFieldEffectObjectTemplate_ShadowExtraLarge;
const struct SpriteTemplate gFieldEffectObjectTemplate_TallGrass;
const struct SpriteTemplate gFieldEffectObjectTemplate_Ripple;
const struct SpriteTemplate gFieldEffectObjectTemplate_Ash;
const struct SpriteTemplate gFieldEffectObjectTemplate_SurfBlob;
const struct SpriteTemplate gFieldEffectObjectTemplate_Arrow;
const struct SpriteTemplate gFieldEffectObjectTemplate_GroundImpactDust;
const struct SpriteTemplate gFieldEffectObjectTemplate_JumpTallGrass;
const struct SpriteTemplate gFieldEffectObjectTemplate_SandFootprints;
const struct SpriteTemplate gFieldEffectObjectTemplate_JumpBigSplash;
const struct SpriteTemplate gFieldEffectObjectTemplate_Splash;
const struct SpriteTemplate gFieldEffectObjectTemplate_JumpSmallSplash;
const struct SpriteTemplate gFieldEffectObjectTemplate_LongGrass;
const struct SpriteTemplate gFieldEffectObjectTemplate_JumpLongGrass;
const struct SpriteTemplate gFieldEffectObjectTemplate_UnusedGrass;
const struct SpriteTemplate gFieldEffectObjectTemplate_UnusedGrass2;
const struct SpriteTemplate gFieldEffectObjectTemplate_UnusedSand;
const struct SpriteTemplate gFieldEffectObjectTemplate_WaterSurfacing;
const struct SpriteTemplate gFieldEffectObjectTemplate_ReflectionDistortion;
const struct SpriteTemplate gFieldEffectObjectTemplate_DeepSandFootprints;
/*const struct SpriteTemplate gFieldEffectObjectTemplate_Sparkle;*/
const struct SpriteTemplate gFieldEffectObjectTemplate_TreeDisguise;
const struct SpriteTemplate gFieldEffectObjectTemplate_MountainDisguise;
const struct SpriteTemplate gFieldEffectObjectTemplate_Bird;
const struct SpriteTemplate gFieldEffectObjectTemplate_BikeTireTracks;
const struct SpriteTemplate gFieldEffectObjectTemplate_SandDisguisePlaceholder;
const struct SpriteTemplate gFieldEffectObjectTemplate_SandPile;
const struct SpriteTemplate gFieldEffectObjectTemplate_ShortGrass;
const struct SpriteTemplate gFieldEffectObjectTemplate_HotSpringsWater;
const struct SpriteTemplate gFieldEffectObjectTemplate_AshPuff;
const struct SpriteTemplate gFieldEffectObjectTemplate_AshLaunch;
const struct SpriteTemplate gFieldEffectObjectTemplate_Bubbles;
const struct SpriteTemplate gFieldEffectObjectTemplate_SmallSparkle;

const struct SpriteTemplate *const gFieldEffectObjectTemplatePointers[] = {
    [FLDEFFOBJ_SHADOW_S]              = &gFieldEffectObjectTemplate_ShadowSmall,
    [FLDEFFOBJ_SHADOW_M]              = &gFieldEffectObjectTemplate_ShadowMedium,
    [FLDEFFOBJ_SHADOW_L]              = &gFieldEffectObjectTemplate_ShadowLarge,
    [FLDEFFOBJ_SHADOW_XL]             = &gFieldEffectObjectTemplate_ShadowExtraLarge,
    [FLDEFFOBJ_TALL_GRASS]            = &gFieldEffectObjectTemplate_TallGrass,
    [FLDEFFOBJ_RIPPLE]                = &gFieldEffectObjectTemplate_Ripple,
    [FLDEFFOBJ_ASH]                   = &gFieldEffectObjectTemplate_Ash,
    [FLDEFFOBJ_SURF_BLOB]             = &gFieldEffectObjectTemplate_SurfBlob,
    [FLDEFFOBJ_ARROW]                 = &gFieldEffectObjectTemplate_Arrow,
    [FLDEFFOBJ_GROUND_IMPACT_DUST]    = &gFieldEffectObjectTemplate_GroundImpactDust,
    [FLDEFFOBJ_JUMP_TALL_GRASS]       = &gFieldEffectObjectTemplate_JumpTallGrass,
    [FLDEFFOBJ_SAND_FOOTPRINTS]       = &gFieldEffectObjectTemplate_SandFootprints,
    [FLDEFFOBJ_JUMP_BIG_SPLASH]       = &gFieldEffectObjectTemplate_JumpBigSplash,
    [FLDEFFOBJ_SPLASH]                = &gFieldEffectObjectTemplate_Splash,
    [FLDEFFOBJ_JUMP_SMALL_SPLASH]     = &gFieldEffectObjectTemplate_JumpSmallSplash,
    [FLDEFFOBJ_LONG_GRASS]            = &gFieldEffectObjectTemplate_LongGrass,
    [FLDEFFOBJ_JUMP_LONG_GRASS]       = &gFieldEffectObjectTemplate_JumpLongGrass,
    [FLDEFFOBJ_UNUSED_GRASS]          = &gFieldEffectObjectTemplate_UnusedGrass,
    [FLDEFFOBJ_UNUSED_GRASS_2]        = &gFieldEffectObjectTemplate_UnusedGrass2,
    [FLDEFFOBJ_UNUSED_SAND]           = &gFieldEffectObjectTemplate_UnusedSand,
    [FLDEFFOBJ_WATER_SURFACING]       = &gFieldEffectObjectTemplate_WaterSurfacing,
    [FLDEFFOBJ_REFLECTION_DISTORTION] = &gFieldEffectObjectTemplate_ReflectionDistortion,
    [FLDEFFOBJ_SPARKLE]               = NULL,
    [FLDEFFOBJ_DEEP_SAND_FOOTPRINTS]  = &gFieldEffectObjectTemplate_DeepSandFootprints,
    [FLDEFFOBJ_TREE_DISGUISE]         = &gFieldEffectObjectTemplate_TreeDisguise,
    [FLDEFFOBJ_MOUNTAIN_DISGUISE]     = &gFieldEffectObjectTemplate_MountainDisguise,
    [FLDEFFOBJ_BIRD]                  = &gFieldEffectObjectTemplate_Bird,
    [FLDEFFOBJ_BIKE_TIRE_TRACKS]      = &gFieldEffectObjectTemplate_BikeTireTracks,
    [FLDEFFOBJ_SAND_DISGUISE]         = &gFieldEffectObjectTemplate_SandDisguisePlaceholder,
    [FLDEFFOBJ_SAND_PILE]             = &gFieldEffectObjectTemplate_SandPile,
    [FLDEFFOBJ_SHORT_GRASS]           = &gFieldEffectObjectTemplate_ShortGrass,
    [FLDEFFOBJ_HOT_SPRINGS_WATER]     = &gFieldEffectObjectTemplate_HotSpringsWater,
    [FLDEFFOBJ_ASH_PUFF]              = &gFieldEffectObjectTemplate_AshPuff,
    [FLDEFFOBJ_ASH_LAUNCH]            = &gFieldEffectObjectTemplate_AshLaunch,
    [FLDEFFOBJ_BUBBLES]               = &gFieldEffectObjectTemplate_Bubbles,
    [FLDEFFOBJ_SMALL_SPARKLE]         = &gFieldEffectObjectTemplate_SmallSparkle,
};
// ===== END src/data/field_effects/field_effect_object_template_pointers.h =====
// ===== BEGIN src/data/object_events/object_event_pic_tables.h =====
static const struct SpriteFrameImage sPicTable_RedNormal[] = {
    overworld_frame(gObjectEventPic_RedNormal, 2, 4, 0),
    overworld_frame(gObjectEventPic_RedNormal, 2, 4, 1),
    overworld_frame(gObjectEventPic_RedNormal, 2, 4, 2),
    overworld_frame(gObjectEventPic_RedNormal, 2, 4, 3),
    overworld_frame(gObjectEventPic_RedNormal, 2, 4, 4),
    overworld_frame(gObjectEventPic_RedNormal, 2, 4, 5),
    overworld_frame(gObjectEventPic_RedNormal, 2, 4, 6),
    overworld_frame(gObjectEventPic_RedNormal, 2, 4, 7),
    overworld_frame(gObjectEventPic_RedNormal, 2, 4, 8),
    overworld_frame(gObjectEventPic_RedSurfRun, 2, 4, 3),
    overworld_frame(gObjectEventPic_RedSurfRun, 2, 4, 4),
    overworld_frame(gObjectEventPic_RedSurfRun, 2, 4, 5),
    overworld_frame(gObjectEventPic_RedSurfRun, 2, 4, 6),
    overworld_frame(gObjectEventPic_RedSurfRun, 2, 4, 7),
    overworld_frame(gObjectEventPic_RedSurfRun, 2, 4, 8),
    overworld_frame(gObjectEventPic_RedSurfRun, 2, 4, 9),
    overworld_frame(gObjectEventPic_RedSurfRun, 2, 4, 10),
    overworld_frame(gObjectEventPic_RedSurfRun, 2, 4, 11),
    overworld_frame(gObjectEventPic_RedSurfRun, 2, 4, 12),
    overworld_frame(gObjectEventPic_RedSurfRun, 2, 4, 13),
};

static const struct SpriteFrameImage sPicTable_RedBike[] = {
    overworld_frame(gObjectEventPic_RedBike, 4, 4, 0),
    overworld_frame(gObjectEventPic_RedBike, 4, 4, 1),
    overworld_frame(gObjectEventPic_RedBike, 4, 4, 2),
    overworld_frame(gObjectEventPic_RedBike, 4, 4, 3),
    overworld_frame(gObjectEventPic_RedBike, 4, 4, 4),
    overworld_frame(gObjectEventPic_RedBike, 4, 4, 5),
    overworld_frame(gObjectEventPic_RedBike, 4, 4, 6),
    overworld_frame(gObjectEventPic_RedBike, 4, 4, 7),
    overworld_frame(gObjectEventPic_RedBike, 4, 4, 8),
};

static const struct SpriteFrameImage sPicTable_GreenNormal[] = {
    overworld_frame(gObjectEventPic_GreenNormal, 2, 4, 0),
    overworld_frame(gObjectEventPic_GreenNormal, 2, 4, 1),
    overworld_frame(gObjectEventPic_GreenNormal, 2, 4, 2),
    overworld_frame(gObjectEventPic_GreenNormal, 2, 4, 3),
    overworld_frame(gObjectEventPic_GreenNormal, 2, 4, 4),
    overworld_frame(gObjectEventPic_GreenNormal, 2, 4, 5),
    overworld_frame(gObjectEventPic_GreenNormal, 2, 4, 6),
    overworld_frame(gObjectEventPic_GreenNormal, 2, 4, 7),
    overworld_frame(gObjectEventPic_GreenNormal, 2, 4, 8),
    overworld_frame(gObjectEventPic_GreenSurfRun, 2, 4, 3),
    overworld_frame(gObjectEventPic_GreenSurfRun, 2, 4, 4),
    overworld_frame(gObjectEventPic_GreenSurfRun, 2, 4, 5),
    overworld_frame(gObjectEventPic_GreenSurfRun, 2, 4, 6),
    overworld_frame(gObjectEventPic_GreenSurfRun, 2, 4, 7),
    overworld_frame(gObjectEventPic_GreenSurfRun, 2, 4, 8),
    overworld_frame(gObjectEventPic_GreenSurfRun, 2, 4, 9),
    overworld_frame(gObjectEventPic_GreenSurfRun, 2, 4, 10),
    overworld_frame(gObjectEventPic_GreenSurfRun, 2, 4, 11),
    overworld_frame(gObjectEventPic_GreenSurfRun, 2, 4, 12),
    overworld_frame(gObjectEventPic_GreenSurfRun, 2, 4, 13),
};

static const struct SpriteFrameImage sPicTable_GreenBike[] = {
    overworld_frame(gObjectEventPic_GreenBike, 4, 4, 0),
    overworld_frame(gObjectEventPic_GreenBike, 4, 4, 1),
    overworld_frame(gObjectEventPic_GreenBike, 4, 4, 2),
    overworld_frame(gObjectEventPic_GreenBike, 4, 4, 3),
    overworld_frame(gObjectEventPic_GreenBike, 4, 4, 4),
    overworld_frame(gObjectEventPic_GreenBike, 4, 4, 5),
    overworld_frame(gObjectEventPic_GreenBike, 4, 4, 6),
    overworld_frame(gObjectEventPic_GreenBike, 4, 4, 7),
    overworld_frame(gObjectEventPic_GreenBike, 4, 4, 8),
};

static const struct SpriteFrameImage sPicTable_RedSurf[] = {
    overworld_frame(gObjectEventPic_RedSurfRun, 2, 4, 0),
    overworld_frame(gObjectEventPic_RedSurfRun, 2, 4, 1),
    overworld_frame(gObjectEventPic_RedSurfRun, 2, 4, 2),
    overworld_frame(gObjectEventPic_RedSurfRun, 2, 4, 0),
    overworld_frame(gObjectEventPic_RedSurfRun, 2, 4, 0),
    overworld_frame(gObjectEventPic_RedSurfRun, 2, 4, 1),
    overworld_frame(gObjectEventPic_RedSurfRun, 2, 4, 1),
    overworld_frame(gObjectEventPic_RedSurfRun, 2, 4, 2),
    overworld_frame(gObjectEventPic_RedSurfRun, 2, 4, 2),
    overworld_frame(gObjectEventPic_RedSurfRun, 2, 4, 0),
    overworld_frame(gObjectEventPic_RedSurfRun, 2, 4, 1),
    overworld_frame(gObjectEventPic_RedSurfRun, 2, 4, 2),
};

static const struct SpriteFrameImage sPicTable_GreenSurf[] = {
    overworld_frame(gObjectEventPic_GreenSurfRun, 2, 4, 0),
    overworld_frame(gObjectEventPic_GreenSurfRun, 2, 4, 1),
    overworld_frame(gObjectEventPic_GreenSurfRun, 2, 4, 2),
    overworld_frame(gObjectEventPic_GreenSurfRun, 2, 4, 0),
    overworld_frame(gObjectEventPic_GreenSurfRun, 2, 4, 0),
    overworld_frame(gObjectEventPic_GreenSurfRun, 2, 4, 1),
    overworld_frame(gObjectEventPic_GreenSurfRun, 2, 4, 1),
    overworld_frame(gObjectEventPic_GreenSurfRun, 2, 4, 2),
    overworld_frame(gObjectEventPic_GreenSurfRun, 2, 4, 2),
    overworld_frame(gObjectEventPic_GreenSurfRun, 2, 4, 0),
    overworld_frame(gObjectEventPic_GreenSurfRun, 2, 4, 1),
    overworld_frame(gObjectEventPic_GreenSurfRun, 2, 4, 2),
};

static const struct SpriteFrameImage sPicTable_RedItem[] = {
    overworld_frame(gObjectEventPic_RedItem, 2, 4, 0),
    overworld_frame(gObjectEventPic_RedItem, 2, 4, 1),
    overworld_frame(gObjectEventPic_RedItem, 2, 4, 2),
    overworld_frame(gObjectEventPic_RedItem, 2, 4, 3),
    overworld_frame(gObjectEventPic_RedItem, 2, 4, 4),
    overworld_frame(gObjectEventPic_RedItem, 2, 4, 5),
    overworld_frame(gObjectEventPic_RedItem, 2, 4, 6),
    overworld_frame(gObjectEventPic_RedItem, 2, 4, 7),
    overworld_frame(gObjectEventPic_RedItem, 2, 4, 8),
};

static const struct SpriteFrameImage sPicTable_GreenItem[] = {
    overworld_frame(gObjectEventPic_GreenItem, 2, 4, 0),
    overworld_frame(gObjectEventPic_GreenItem, 2, 4, 1),
    overworld_frame(gObjectEventPic_GreenItem, 2, 4, 2),
    overworld_frame(gObjectEventPic_GreenItem, 2, 4, 3),
    overworld_frame(gObjectEventPic_GreenItem, 2, 4, 4),
    overworld_frame(gObjectEventPic_GreenItem, 2, 4, 5),
    overworld_frame(gObjectEventPic_GreenItem, 2, 4, 6),
    overworld_frame(gObjectEventPic_GreenItem, 2, 4, 7),
    overworld_frame(gObjectEventPic_GreenItem, 2, 4, 8),
};

static const struct SpriteFrameImage sPicTable_RedVSSeekerBike[] = {
    overworld_frame(gObjectEventPic_RedVSSeekerBike, 4, 4, 0),
    overworld_frame(gObjectEventPic_RedVSSeekerBike, 4, 4, 1),
    overworld_frame(gObjectEventPic_RedVSSeekerBike, 4, 4, 2),
    overworld_frame(gObjectEventPic_RedVSSeekerBike, 4, 4, 3),
    overworld_frame(gObjectEventPic_RedVSSeekerBike, 4, 4, 4),
    overworld_frame(gObjectEventPic_RedVSSeekerBike, 4, 4, 5),
};

static const struct SpriteFrameImage sPicTable_GreenVSSeekerBike[] = {
    overworld_frame(gObjectEventPic_GreenVSSeekerBike, 4, 4, 0),
    overworld_frame(gObjectEventPic_GreenVSSeekerBike, 4, 4, 1),
    overworld_frame(gObjectEventPic_GreenVSSeekerBike, 4, 4, 2),
    overworld_frame(gObjectEventPic_GreenVSSeekerBike, 4, 4, 3),
    overworld_frame(gObjectEventPic_GreenVSSeekerBike, 4, 4, 4),
    overworld_frame(gObjectEventPic_GreenVSSeekerBike, 4, 4, 5),
};

static const struct SpriteFrameImage sPicTable_RSBrendan[] = {
    overworld_frame(gObjectEventPic_RSBrendan, 2, 4, 0),
    overworld_frame(gObjectEventPic_RSBrendan, 2, 4, 1),
    overworld_frame(gObjectEventPic_RSBrendan, 2, 4, 2),
    overworld_frame(gObjectEventPic_RSBrendan, 2, 4, 3),
    overworld_frame(gObjectEventPic_RSBrendan, 2, 4, 4),
    overworld_frame(gObjectEventPic_RSBrendan, 2, 4, 5),
    overworld_frame(gObjectEventPic_RSBrendan, 2, 4, 6),
    overworld_frame(gObjectEventPic_RSBrendan, 2, 4, 7),
    overworld_frame(gObjectEventPic_RSBrendan, 2, 4, 8),
    overworld_frame(gObjectEventPic_RSMay, 2, 4, 0),
};

static const struct SpriteFrameImage sPicTable_RSMay[] = {
    overworld_frame(gObjectEventPic_RSMay, 2, 4, 0),
    overworld_frame(gObjectEventPic_RSMay, 2, 4, 1),
    overworld_frame(gObjectEventPic_RSMay, 2, 4, 2),
    overworld_frame(gObjectEventPic_RSMay, 2, 4, 3),
    overworld_frame(gObjectEventPic_RSMay, 2, 4, 4),
    overworld_frame(gObjectEventPic_RSMay, 2, 4, 5),
    overworld_frame(gObjectEventPic_RSMay, 2, 4, 6),
    overworld_frame(gObjectEventPic_RSMay, 2, 4, 7),
    overworld_frame(gObjectEventPic_RSMay, 2, 4, 8),
    overworld_frame(gObjectEventPic_RedFish, 2, 4, 0),
};

static const struct SpriteFrameImage sPicTable_Policeman[] = {
    overworld_frame(gObjectEventPic_Policeman, 2, 4, 0),
    overworld_frame(gObjectEventPic_Policeman, 2, 4, 1),
    overworld_frame(gObjectEventPic_Policeman, 2, 4, 2),
    overworld_frame(gObjectEventPic_Policeman, 2, 4, 3),
    overworld_frame(gObjectEventPic_Policeman, 2, 4, 4),
    overworld_frame(gObjectEventPic_Policeman, 2, 4, 5),
    overworld_frame(gObjectEventPic_Policeman, 2, 4, 6),
    overworld_frame(gObjectEventPic_Policeman, 2, 4, 7),
    overworld_frame(gObjectEventPic_Policeman, 2, 4, 8),
};

static const struct SpriteFrameImage sPicTable_LittleBoy[] = {
    overworld_frame(gObjectEventPic_LittleBoy, 2, 2, 0),
    overworld_frame(gObjectEventPic_LittleBoy, 2, 2, 1),
    overworld_frame(gObjectEventPic_LittleBoy, 2, 2, 2),
    overworld_frame(gObjectEventPic_LittleBoy, 2, 2, 3),
    overworld_frame(gObjectEventPic_LittleBoy, 2, 2, 4),
    overworld_frame(gObjectEventPic_LittleBoy, 2, 2, 5),
    overworld_frame(gObjectEventPic_LittleBoy, 2, 2, 6),
    overworld_frame(gObjectEventPic_LittleBoy, 2, 2, 7),
    overworld_frame(gObjectEventPic_LittleBoy, 2, 2, 8),
};

static const struct SpriteFrameImage sPicTable_LittleGirl[] = {
    overworld_frame(gObjectEventPic_LittleGirl, 2, 2, 0),
    overworld_frame(gObjectEventPic_LittleGirl, 2, 2, 1),
    overworld_frame(gObjectEventPic_LittleGirl, 2, 2, 2),
    overworld_frame(gObjectEventPic_LittleGirl, 2, 2, 3),
    overworld_frame(gObjectEventPic_LittleGirl, 2, 2, 4),
    overworld_frame(gObjectEventPic_LittleGirl, 2, 2, 5),
    overworld_frame(gObjectEventPic_LittleGirl, 2, 2, 6),
    overworld_frame(gObjectEventPic_LittleGirl, 2, 2, 7),
    overworld_frame(gObjectEventPic_LittleGirl, 2, 2, 8),
    overworld_frame(gObjectEventPic_LittleGirl, 2, 2, 9),
};

static const struct SpriteFrameImage sPicTable_SittingBoy[] = {
    overworld_frame(gObjectEventPic_SittingBoy, 2, 4, 0),
    overworld_frame(gObjectEventPic_SittingBoy, 2, 4, 2),
    overworld_frame(gObjectEventPic_SittingBoy, 2, 4, 1),
    overworld_frame(gObjectEventPic_SittingBoy, 2, 4, 0),
    overworld_frame(gObjectEventPic_SittingBoy, 2, 4, 0),
    overworld_frame(gObjectEventPic_SittingBoy, 2, 4, 2),
    overworld_frame(gObjectEventPic_SittingBoy, 2, 4, 2),
    overworld_frame(gObjectEventPic_SittingBoy, 2, 4, 1),
    overworld_frame(gObjectEventPic_SittingBoy, 2, 4, 1),
};

static const struct SpriteFrameImage sPicTable_Lass[] = {
    overworld_frame(gObjectEventPic_Lass, 2, 4, 0),
    overworld_frame(gObjectEventPic_Lass, 2, 4, 1),
    overworld_frame(gObjectEventPic_Lass, 2, 4, 2),
    overworld_frame(gObjectEventPic_Lass, 2, 4, 3),
    overworld_frame(gObjectEventPic_Lass, 2, 4, 4),
    overworld_frame(gObjectEventPic_Lass, 2, 4, 5),
    overworld_frame(gObjectEventPic_Lass, 2, 4, 6),
    overworld_frame(gObjectEventPic_Lass, 2, 4, 7),
    overworld_frame(gObjectEventPic_Lass, 2, 4, 8),
    overworld_frame(gObjectEventPic_Lass, 2, 4, 9),
};

static const struct SpriteFrameImage sPicTable_Youngster[] = {
    overworld_frame(gObjectEventPic_Youngster, 2, 4, 0),
    overworld_frame(gObjectEventPic_Youngster, 2, 4, 1),
    overworld_frame(gObjectEventPic_Youngster, 2, 4, 2),
    overworld_frame(gObjectEventPic_Youngster, 2, 4, 3),
    overworld_frame(gObjectEventPic_Youngster, 2, 4, 4),
    overworld_frame(gObjectEventPic_Youngster, 2, 4, 5),
    overworld_frame(gObjectEventPic_Youngster, 2, 4, 6),
    overworld_frame(gObjectEventPic_Youngster, 2, 4, 7),
    overworld_frame(gObjectEventPic_Youngster, 2, 4, 8),
    overworld_frame(gObjectEventPic_Youngster, 2, 4, 9),
};

static const struct SpriteFrameImage sPicTable_Woman1[] = {
    overworld_frame(gObjectEventPic_Woman1, 2, 4, 0),
    overworld_frame(gObjectEventPic_Woman1, 2, 4, 1),
    overworld_frame(gObjectEventPic_Woman1, 2, 4, 2),
    overworld_frame(gObjectEventPic_Woman1, 2, 4, 3),
    overworld_frame(gObjectEventPic_Woman1, 2, 4, 4),
    overworld_frame(gObjectEventPic_Woman1, 2, 4, 5),
    overworld_frame(gObjectEventPic_Woman1, 2, 4, 6),
    overworld_frame(gObjectEventPic_Woman1, 2, 4, 7),
    overworld_frame(gObjectEventPic_Woman1, 2, 4, 8),
    overworld_frame(gObjectEventPic_Woman1, 2, 4, 9),
};

static const struct SpriteFrameImage sPicTable_Woman3[] = {
    overworld_frame(gObjectEventPic_Woman3, 2, 4, 0),
    overworld_frame(gObjectEventPic_Woman3, 2, 4, 1),
    overworld_frame(gObjectEventPic_Woman3, 2, 4, 2),
    overworld_frame(gObjectEventPic_Woman3, 2, 4, 3),
    overworld_frame(gObjectEventPic_Woman3, 2, 4, 4),
    overworld_frame(gObjectEventPic_Woman3, 2, 4, 5),
    overworld_frame(gObjectEventPic_Woman3, 2, 4, 6),
    overworld_frame(gObjectEventPic_Woman3, 2, 4, 7),
    overworld_frame(gObjectEventPic_Woman3, 2, 4, 8),
};

static const struct SpriteFrameImage sPicTable_CrushGirl[] = {
    overworld_frame(gObjectEventPic_CrushGirl, 2, 4, 0),
    overworld_frame(gObjectEventPic_CrushGirl, 2, 4, 1),
    overworld_frame(gObjectEventPic_CrushGirl, 2, 4, 2),
    overworld_frame(gObjectEventPic_CrushGirl, 2, 4, 3),
    overworld_frame(gObjectEventPic_CrushGirl, 2, 4, 4),
    overworld_frame(gObjectEventPic_CrushGirl, 2, 4, 5),
    overworld_frame(gObjectEventPic_CrushGirl, 2, 4, 6),
    overworld_frame(gObjectEventPic_CrushGirl, 2, 4, 7),
    overworld_frame(gObjectEventPic_CrushGirl, 2, 4, 8),
    overworld_frame(gObjectEventPic_CrushGirl, 2, 4, 9),
};

static const struct SpriteFrameImage sPicTable_BugCatcher[] = {
    overworld_frame(gObjectEventPic_BugCatcher, 2, 4, 0),
    overworld_frame(gObjectEventPic_BugCatcher, 2, 4, 1),
    overworld_frame(gObjectEventPic_BugCatcher, 2, 4, 2),
    overworld_frame(gObjectEventPic_BugCatcher, 2, 4, 3),
    overworld_frame(gObjectEventPic_BugCatcher, 2, 4, 4),
    overworld_frame(gObjectEventPic_BugCatcher, 2, 4, 5),
    overworld_frame(gObjectEventPic_BugCatcher, 2, 4, 6),
    overworld_frame(gObjectEventPic_BugCatcher, 2, 4, 7),
    overworld_frame(gObjectEventPic_BugCatcher, 2, 4, 8),
    overworld_frame(gObjectEventPic_BugCatcher, 2, 4, 9),
};

static const struct SpriteFrameImage sPicTable_FatMan[] = {
    overworld_frame(gObjectEventPic_FatMan, 2, 4, 0),
    overworld_frame(gObjectEventPic_FatMan, 2, 4, 1),
    overworld_frame(gObjectEventPic_FatMan, 2, 4, 2),
    overworld_frame(gObjectEventPic_FatMan, 2, 4, 3),
    overworld_frame(gObjectEventPic_FatMan, 2, 4, 4),
    overworld_frame(gObjectEventPic_FatMan, 2, 4, 5),
    overworld_frame(gObjectEventPic_FatMan, 2, 4, 6),
    overworld_frame(gObjectEventPic_FatMan, 2, 4, 7),
    overworld_frame(gObjectEventPic_FatMan, 2, 4, 8),
};

static const struct SpriteFrameImage sPicTable_BaldingMan[] = {
    overworld_frame(gObjectEventPic_BaldingMan, 2, 4, 0),
    overworld_frame(gObjectEventPic_BaldingMan, 2, 4, 1),
    overworld_frame(gObjectEventPic_BaldingMan, 2, 4, 2),
    overworld_frame(gObjectEventPic_BaldingMan, 2, 4, 3),
    overworld_frame(gObjectEventPic_BaldingMan, 2, 4, 4),
    overworld_frame(gObjectEventPic_BaldingMan, 2, 4, 5),
    overworld_frame(gObjectEventPic_BaldingMan, 2, 4, 6),
    overworld_frame(gObjectEventPic_BaldingMan, 2, 4, 7),
    overworld_frame(gObjectEventPic_BaldingMan, 2, 4, 8),
    overworld_frame(gObjectEventPic_BaldingMan, 2, 4, 9),
};

static const struct SpriteFrameImage sPicTable_Woman2[] = {
    overworld_frame(gObjectEventPic_Woman2, 2, 4, 0),
    overworld_frame(gObjectEventPic_Woman2, 2, 4, 1),
    overworld_frame(gObjectEventPic_Woman2, 2, 4, 2),
    overworld_frame(gObjectEventPic_Woman2, 2, 4, 3),
    overworld_frame(gObjectEventPic_Woman2, 2, 4, 4),
    overworld_frame(gObjectEventPic_Woman2, 2, 4, 5),
    overworld_frame(gObjectEventPic_Woman2, 2, 4, 6),
    overworld_frame(gObjectEventPic_Woman2, 2, 4, 7),
    overworld_frame(gObjectEventPic_Woman2, 2, 4, 8),
    overworld_frame(gObjectEventPic_Woman2, 2, 4, 9),
};

static const struct SpriteFrameImage sPicTable_OldMan1[] = {
    overworld_frame(gObjectEventPic_OldMan1, 2, 4, 0),
    overworld_frame(gObjectEventPic_OldMan1, 2, 4, 1),
    overworld_frame(gObjectEventPic_OldMan1, 2, 4, 2),
    overworld_frame(gObjectEventPic_OldMan1, 2, 4, 3),
    overworld_frame(gObjectEventPic_OldMan1, 2, 4, 4),
    overworld_frame(gObjectEventPic_OldMan1, 2, 4, 5),
    overworld_frame(gObjectEventPic_OldMan1, 2, 4, 6),
    overworld_frame(gObjectEventPic_OldMan1, 2, 4, 7),
    overworld_frame(gObjectEventPic_OldMan1, 2, 4, 8),
    overworld_frame(gObjectEventPic_OldMan1, 2, 4, 9),
};

static const struct SpriteFrameImage sPicTable_WorkerM[] = {
    overworld_frame(gObjectEventPic_WorkerM, 2, 4, 0),
    overworld_frame(gObjectEventPic_WorkerM, 2, 4, 1),
    overworld_frame(gObjectEventPic_WorkerM, 2, 4, 2),
    overworld_frame(gObjectEventPic_WorkerM, 2, 4, 3),
    overworld_frame(gObjectEventPic_WorkerM, 2, 4, 4),
    overworld_frame(gObjectEventPic_WorkerM, 2, 4, 5),
    overworld_frame(gObjectEventPic_WorkerM, 2, 4, 6),
    overworld_frame(gObjectEventPic_WorkerM, 2, 4, 7),
    overworld_frame(gObjectEventPic_WorkerM, 2, 4, 8),
};

static const struct SpriteFrameImage sPicTable_WorkerF[] = {
    overworld_frame(gObjectEventPic_WorkerF, 2, 4, 0),
    overworld_frame(gObjectEventPic_WorkerF, 2, 4, 1),
    overworld_frame(gObjectEventPic_WorkerF, 2, 4, 2),
    overworld_frame(gObjectEventPic_WorkerF, 2, 4, 3),
    overworld_frame(gObjectEventPic_WorkerF, 2, 4, 4),
    overworld_frame(gObjectEventPic_WorkerF, 2, 4, 5),
    overworld_frame(gObjectEventPic_WorkerF, 2, 4, 6),
    overworld_frame(gObjectEventPic_WorkerF, 2, 4, 7),
    overworld_frame(gObjectEventPic_WorkerF, 2, 4, 8),
};

static const struct SpriteFrameImage sPicTable_Beauty[] = {
    overworld_frame(gObjectEventPic_Beauty, 2, 4, 0),
    overworld_frame(gObjectEventPic_Beauty, 2, 4, 1),
    overworld_frame(gObjectEventPic_Beauty, 2, 4, 2),
    overworld_frame(gObjectEventPic_Beauty, 2, 4, 3),
    overworld_frame(gObjectEventPic_Beauty, 2, 4, 4),
    overworld_frame(gObjectEventPic_Beauty, 2, 4, 5),
    overworld_frame(gObjectEventPic_Beauty, 2, 4, 6),
    overworld_frame(gObjectEventPic_Beauty, 2, 4, 7),
    overworld_frame(gObjectEventPic_Beauty, 2, 4, 8),
    overworld_frame(gObjectEventPic_Beauty, 2, 4, 9),
};

static const struct SpriteFrameImage sPicTable_Chef[] = {
    overworld_frame(gObjectEventPic_Chef, 2, 4, 0),
    overworld_frame(gObjectEventPic_Chef, 2, 4, 1),
    overworld_frame(gObjectEventPic_Chef, 2, 4, 2),
    overworld_frame(gObjectEventPic_Chef, 2, 4, 3),
    overworld_frame(gObjectEventPic_Chef, 2, 4, 4),
    overworld_frame(gObjectEventPic_Chef, 2, 4, 5),
    overworld_frame(gObjectEventPic_Chef, 2, 4, 6),
    overworld_frame(gObjectEventPic_Chef, 2, 4, 7),
    overworld_frame(gObjectEventPic_Chef, 2, 4, 8),
};

static const struct SpriteFrameImage sPicTable_OldMan2[] = {
    overworld_frame(gObjectEventPic_OldMan2, 2, 4, 0),
    overworld_frame(gObjectEventPic_OldMan2, 2, 4, 1),
    overworld_frame(gObjectEventPic_OldMan2, 2, 4, 2),
    overworld_frame(gObjectEventPic_OldMan2, 2, 4, 0),
    overworld_frame(gObjectEventPic_OldMan2, 2, 4, 0),
    overworld_frame(gObjectEventPic_OldMan2, 2, 4, 1),
    overworld_frame(gObjectEventPic_OldMan2, 2, 4, 1),
    overworld_frame(gObjectEventPic_OldMan2, 2, 4, 2),
    overworld_frame(gObjectEventPic_OldMan2, 2, 4, 2),
    overworld_frame(gObjectEventPic_OldWoman, 2, 4, 0),
};

static const struct SpriteFrameImage sPicTable_OldManLyingDown[] = {
    overworld_frame(gObjectEventPic_OldManLyingDown, 4, 4, 0),
    overworld_frame(gObjectEventPic_OldManLyingDown, 4, 4, 0),
    overworld_frame(gObjectEventPic_OldManLyingDown, 4, 4, 0),
    overworld_frame(gObjectEventPic_OldManLyingDown, 4, 4, 0),
    overworld_frame(gObjectEventPic_OldManLyingDown, 4, 4, 0),
    overworld_frame(gObjectEventPic_OldManLyingDown, 4, 4, 0),
    overworld_frame(gObjectEventPic_OldManLyingDown, 4, 4, 0),
    overworld_frame(gObjectEventPic_OldManLyingDown, 4, 4, 0),
    overworld_frame(gObjectEventPic_OldManLyingDown, 4, 4, 0),
};

static const struct SpriteFrameImage sPicTable_OldWoman[] = {
    overworld_frame(gObjectEventPic_OldWoman, 2, 4, 0),
    overworld_frame(gObjectEventPic_OldWoman, 2, 4, 1),
    overworld_frame(gObjectEventPic_OldWoman, 2, 4, 2),
    overworld_frame(gObjectEventPic_OldWoman, 2, 4, 3),
    overworld_frame(gObjectEventPic_OldWoman, 2, 4, 4),
    overworld_frame(gObjectEventPic_OldWoman, 2, 4, 5),
    overworld_frame(gObjectEventPic_OldWoman, 2, 4, 6),
    overworld_frame(gObjectEventPic_OldWoman, 2, 4, 7),
    overworld_frame(gObjectEventPic_OldWoman, 2, 4, 8),
};

static const struct SpriteFrameImage sPicTable_Camper[] = {
    overworld_frame(gObjectEventPic_Camper, 2, 4, 0),
    overworld_frame(gObjectEventPic_Camper, 2, 4, 1),
    overworld_frame(gObjectEventPic_Camper, 2, 4, 2),
    overworld_frame(gObjectEventPic_Camper, 2, 4, 3),
    overworld_frame(gObjectEventPic_Camper, 2, 4, 4),
    overworld_frame(gObjectEventPic_Camper, 2, 4, 5),
    overworld_frame(gObjectEventPic_Camper, 2, 4, 6),
    overworld_frame(gObjectEventPic_Camper, 2, 4, 7),
    overworld_frame(gObjectEventPic_Camper, 2, 4, 8),
    overworld_frame(gObjectEventPic_Camper, 2, 4, 9),
};

static const struct SpriteFrameImage sPicTable_Picnicker[] = {
    overworld_frame(gObjectEventPic_Picnicker, 2, 4, 0),
    overworld_frame(gObjectEventPic_Picnicker, 2, 4, 1),
    overworld_frame(gObjectEventPic_Picnicker, 2, 4, 2),
    overworld_frame(gObjectEventPic_Picnicker, 2, 4, 3),
    overworld_frame(gObjectEventPic_Picnicker, 2, 4, 4),
    overworld_frame(gObjectEventPic_Picnicker, 2, 4, 5),
    overworld_frame(gObjectEventPic_Picnicker, 2, 4, 6),
    overworld_frame(gObjectEventPic_Picnicker, 2, 4, 7),
    overworld_frame(gObjectEventPic_Picnicker, 2, 4, 8),
    overworld_frame(gObjectEventPic_Picnicker, 2, 4, 9),
};

static const struct SpriteFrameImage sPicTable_CooltrainerM[] = {
    overworld_frame(gObjectEventPic_CooltrainerM, 2, 4, 0),
    overworld_frame(gObjectEventPic_CooltrainerM, 2, 4, 1),
    overworld_frame(gObjectEventPic_CooltrainerM, 2, 4, 2),
    overworld_frame(gObjectEventPic_CooltrainerM, 2, 4, 3),
    overworld_frame(gObjectEventPic_CooltrainerM, 2, 4, 4),
    overworld_frame(gObjectEventPic_CooltrainerM, 2, 4, 5),
    overworld_frame(gObjectEventPic_CooltrainerM, 2, 4, 6),
    overworld_frame(gObjectEventPic_CooltrainerM, 2, 4, 7),
    overworld_frame(gObjectEventPic_CooltrainerM, 2, 4, 8),
    overworld_frame(gObjectEventPic_CooltrainerM, 2, 4, 9),
};

static const struct SpriteFrameImage sPicTable_CooltrainerF[] = {
    overworld_frame(gObjectEventPic_CooltrainerF, 2, 4, 0),
    overworld_frame(gObjectEventPic_CooltrainerF, 2, 4, 1),
    overworld_frame(gObjectEventPic_CooltrainerF, 2, 4, 2),
    overworld_frame(gObjectEventPic_CooltrainerF, 2, 4, 3),
    overworld_frame(gObjectEventPic_CooltrainerF, 2, 4, 4),
    overworld_frame(gObjectEventPic_CooltrainerF, 2, 4, 5),
    overworld_frame(gObjectEventPic_CooltrainerF, 2, 4, 6),
    overworld_frame(gObjectEventPic_CooltrainerF, 2, 4, 7),
    overworld_frame(gObjectEventPic_CooltrainerF, 2, 4, 8),
    overworld_frame(gObjectEventPic_CooltrainerF, 2, 4, 9),
};

static const struct SpriteFrameImage sPicTable_Boy[] = {
    overworld_frame(gObjectEventPic_Boy, 2, 4, 0),
    overworld_frame(gObjectEventPic_Boy, 2, 4, 1),
    overworld_frame(gObjectEventPic_Boy, 2, 4, 2),
    overworld_frame(gObjectEventPic_Boy, 2, 4, 3),
    overworld_frame(gObjectEventPic_Boy, 2, 4, 4),
    overworld_frame(gObjectEventPic_Boy, 2, 4, 5),
    overworld_frame(gObjectEventPic_Boy, 2, 4, 6),
    overworld_frame(gObjectEventPic_Boy, 2, 4, 7),
    overworld_frame(gObjectEventPic_Boy, 2, 4, 8),
    overworld_frame(gObjectEventPic_Boy, 2, 4, 9),
};

static const struct SpriteFrameImage sPicTable_PokeManiac[] = {
    overworld_frame(gObjectEventPic_PokeManiac, 2, 4, 0),
    overworld_frame(gObjectEventPic_PokeManiac, 2, 4, 1),
    overworld_frame(gObjectEventPic_PokeManiac, 2, 4, 2),
    overworld_frame(gObjectEventPic_PokeManiac, 2, 4, 3),
    overworld_frame(gObjectEventPic_PokeManiac, 2, 4, 4),
    overworld_frame(gObjectEventPic_PokeManiac, 2, 4, 5),
    overworld_frame(gObjectEventPic_PokeManiac, 2, 4, 6),
    overworld_frame(gObjectEventPic_PokeManiac, 2, 4, 7),
    overworld_frame(gObjectEventPic_PokeManiac, 2, 4, 8),
    overworld_frame(gObjectEventPic_PokeManiac, 2, 4, 9),
};

static const struct SpriteFrameImage sPicTable_Channeler[] = {
    overworld_frame(gObjectEventPic_Channeler, 2, 4, 0),
    overworld_frame(gObjectEventPic_Channeler, 2, 4, 1),
    overworld_frame(gObjectEventPic_Channeler, 2, 4, 2),
    overworld_frame(gObjectEventPic_Channeler, 2, 4, 3),
    overworld_frame(gObjectEventPic_Channeler, 2, 4, 4),
    overworld_frame(gObjectEventPic_Channeler, 2, 4, 5),
    overworld_frame(gObjectEventPic_Channeler, 2, 4, 6),
    overworld_frame(gObjectEventPic_Channeler, 2, 4, 7),
    overworld_frame(gObjectEventPic_Channeler, 2, 4, 8),
    overworld_frame(gObjectEventPic_Channeler, 2, 4, 9),
};

static const struct SpriteFrameImage sPicTable_RocketF[] = {
    overworld_frame(gObjectEventPic_RocketF, 2, 4, 0),
    overworld_frame(gObjectEventPic_RocketF, 2, 4, 1),
    overworld_frame(gObjectEventPic_RocketF, 2, 4, 2),
    overworld_frame(gObjectEventPic_RocketF, 2, 4, 3),
    overworld_frame(gObjectEventPic_RocketF, 2, 4, 4),
    overworld_frame(gObjectEventPic_RocketF, 2, 4, 5),
    overworld_frame(gObjectEventPic_RocketF, 2, 4, 6),
    overworld_frame(gObjectEventPic_RocketF, 2, 4, 7),
    overworld_frame(gObjectEventPic_RocketF, 2, 4, 8),
};

static const struct SpriteFrameImage sPicTable_SwimmerMWater[] = {
    overworld_frame(gObjectEventPic_SwimmerMWater, 2, 4, 0),
    overworld_frame(gObjectEventPic_SwimmerMWater, 2, 4, 1),
    overworld_frame(gObjectEventPic_SwimmerMWater, 2, 4, 2),
    overworld_frame(gObjectEventPic_SwimmerMWater, 2, 4, 3),
    overworld_frame(gObjectEventPic_SwimmerMWater, 2, 4, 4),
    overworld_frame(gObjectEventPic_SwimmerMWater, 2, 4, 5),
    overworld_frame(gObjectEventPic_SwimmerMWater, 2, 4, 6),
    overworld_frame(gObjectEventPic_SwimmerMWater, 2, 4, 7),
    overworld_frame(gObjectEventPic_SwimmerMWater, 2, 4, 8),
    overworld_frame(gObjectEventPic_SwimmerMWater, 2, 4, 9),
};

static const struct SpriteFrameImage sPicTable_SwimmerFWater[] = {
    overworld_frame(gObjectEventPic_SwimmerFWater, 2, 4, 0),
    overworld_frame(gObjectEventPic_SwimmerFWater, 2, 4, 1),
    overworld_frame(gObjectEventPic_SwimmerFWater, 2, 4, 2),
    overworld_frame(gObjectEventPic_SwimmerFWater, 2, 4, 3),
    overworld_frame(gObjectEventPic_SwimmerFWater, 2, 4, 4),
    overworld_frame(gObjectEventPic_SwimmerFWater, 2, 4, 5),
    overworld_frame(gObjectEventPic_SwimmerFWater, 2, 4, 6),
    overworld_frame(gObjectEventPic_SwimmerFWater, 2, 4, 7),
    overworld_frame(gObjectEventPic_SwimmerFWater, 2, 4, 8),
    overworld_frame(gObjectEventPic_SwimmerFWater, 2, 4, 9),
};

static const struct SpriteFrameImage sPicTable_SwimmerMLand[] = {
    overworld_frame(gObjectEventPic_SwimmerMLand, 2, 4, 0),
    overworld_frame(gObjectEventPic_SwimmerMLand, 2, 4, 1),
    overworld_frame(gObjectEventPic_SwimmerMLand, 2, 4, 2),
    overworld_frame(gObjectEventPic_SwimmerMLand, 2, 4, 3),
    overworld_frame(gObjectEventPic_SwimmerMLand, 2, 4, 4),
    overworld_frame(gObjectEventPic_SwimmerMLand, 2, 4, 5),
    overworld_frame(gObjectEventPic_SwimmerMLand, 2, 4, 6),
    overworld_frame(gObjectEventPic_SwimmerMLand, 2, 4, 7),
    overworld_frame(gObjectEventPic_SwimmerMLand, 2, 4, 8),
    overworld_frame(gObjectEventPic_SwimmerMLand, 2, 4, 9),
};

static const struct SpriteFrameImage sPicTable_SwimmerFLand[] = {
    overworld_frame(gObjectEventPic_SwimmerFLand, 2, 4, 0),
    overworld_frame(gObjectEventPic_SwimmerFLand, 2, 4, 1),
    overworld_frame(gObjectEventPic_SwimmerFLand, 2, 4, 2),
    overworld_frame(gObjectEventPic_SwimmerFLand, 2, 4, 3),
    overworld_frame(gObjectEventPic_SwimmerFLand, 2, 4, 4),
    overworld_frame(gObjectEventPic_SwimmerFLand, 2, 4, 5),
    overworld_frame(gObjectEventPic_SwimmerFLand, 2, 4, 6),
    overworld_frame(gObjectEventPic_SwimmerFLand, 2, 4, 7),
    overworld_frame(gObjectEventPic_SwimmerFLand, 2, 4, 8),
    overworld_frame(gObjectEventPic_SwimmerFLand, 2, 4, 9),
};

static const struct SpriteFrameImage sPicTable_BlackBelt[] = {
    overworld_frame(gObjectEventPic_BlackBelt, 2, 4, 0),
    overworld_frame(gObjectEventPic_BlackBelt, 2, 4, 1),
    overworld_frame(gObjectEventPic_BlackBelt, 2, 4, 2),
    overworld_frame(gObjectEventPic_BlackBelt, 2, 4, 3),
    overworld_frame(gObjectEventPic_BlackBelt, 2, 4, 4),
    overworld_frame(gObjectEventPic_BlackBelt, 2, 4, 5),
    overworld_frame(gObjectEventPic_BlackBelt, 2, 4, 6),
    overworld_frame(gObjectEventPic_BlackBelt, 2, 4, 7),
    overworld_frame(gObjectEventPic_BlackBelt, 2, 4, 8),
    overworld_frame(gObjectEventPic_BlackBelt, 2, 4, 9),
};

static const struct SpriteFrameImage sPicTable_Scientist[] = {
    overworld_frame(gObjectEventPic_Scientist, 2, 4, 0),
    overworld_frame(gObjectEventPic_Scientist, 2, 4, 1),
    overworld_frame(gObjectEventPic_Scientist, 2, 4, 2),
    overworld_frame(gObjectEventPic_Scientist, 2, 4, 3),
    overworld_frame(gObjectEventPic_Scientist, 2, 4, 4),
    overworld_frame(gObjectEventPic_Scientist, 2, 4, 5),
    overworld_frame(gObjectEventPic_Scientist, 2, 4, 6),
    overworld_frame(gObjectEventPic_Scientist, 2, 4, 7),
    overworld_frame(gObjectEventPic_Scientist, 2, 4, 8),
    overworld_frame(gObjectEventPic_Scientist, 2, 4, 9),
};

static const struct SpriteFrameImage sPicTable_Gentleman[] = {
    overworld_frame(gObjectEventPic_Gentleman, 2, 4, 0),
    overworld_frame(gObjectEventPic_Gentleman, 2, 4, 1),
    overworld_frame(gObjectEventPic_Gentleman, 2, 4, 2),
    overworld_frame(gObjectEventPic_Gentleman, 2, 4, 3),
    overworld_frame(gObjectEventPic_Gentleman, 2, 4, 4),
    overworld_frame(gObjectEventPic_Gentleman, 2, 4, 5),
    overworld_frame(gObjectEventPic_Gentleman, 2, 4, 6),
    overworld_frame(gObjectEventPic_Gentleman, 2, 4, 7),
    overworld_frame(gObjectEventPic_Gentleman, 2, 4, 8),
    overworld_frame(gObjectEventPic_Gentleman, 2, 4, 9),
};

static const struct SpriteFrameImage sPicTable_Sailor[] = {
    overworld_frame(gObjectEventPic_Sailor, 2, 4, 0),
    overworld_frame(gObjectEventPic_Sailor, 2, 4, 1),
    overworld_frame(gObjectEventPic_Sailor, 2, 4, 2),
    overworld_frame(gObjectEventPic_Sailor, 2, 4, 3),
    overworld_frame(gObjectEventPic_Sailor, 2, 4, 4),
    overworld_frame(gObjectEventPic_Sailor, 2, 4, 5),
    overworld_frame(gObjectEventPic_Sailor, 2, 4, 6),
    overworld_frame(gObjectEventPic_Sailor, 2, 4, 7),
    overworld_frame(gObjectEventPic_Sailor, 2, 4, 8),
    overworld_frame(gObjectEventPic_Sailor, 2, 4, 9),
};

static const struct SpriteFrameImage sPicTable_Captain[] = {
    overworld_frame(gObjectEventPic_Captain, 2, 4, 0),
    overworld_frame(gObjectEventPic_Captain, 2, 4, 1),
    overworld_frame(gObjectEventPic_Captain, 2, 4, 2),
    overworld_frame(gObjectEventPic_Captain, 2, 4, 3),
    overworld_frame(gObjectEventPic_Captain, 2, 4, 4),
    overworld_frame(gObjectEventPic_Captain, 2, 4, 5),
    overworld_frame(gObjectEventPic_Captain, 2, 4, 6),
    overworld_frame(gObjectEventPic_Captain, 2, 4, 7),
    overworld_frame(gObjectEventPic_Captain, 2, 4, 8),
};

static const struct SpriteFrameImage sPicTable_Fisher[] = {
    overworld_frame(gObjectEventPic_Fisher, 2, 4, 0),
    overworld_frame(gObjectEventPic_Fisher, 2, 4, 1),
    overworld_frame(gObjectEventPic_Fisher, 2, 4, 2),
    overworld_frame(gObjectEventPic_Fisher, 2, 4, 3),
    overworld_frame(gObjectEventPic_Fisher, 2, 4, 4),
    overworld_frame(gObjectEventPic_Fisher, 2, 4, 5),
    overworld_frame(gObjectEventPic_Fisher, 2, 4, 6),
    overworld_frame(gObjectEventPic_Fisher, 2, 4, 7),
    overworld_frame(gObjectEventPic_Fisher, 2, 4, 8),
    overworld_frame(gObjectEventPic_Fisher, 2, 4, 9),
};

static const struct SpriteFrameImage sPicTable_TeachyTVHost[] = {
    overworld_frame(gObjectEventPic_TeachyTVHost, 2, 4, 0),
    overworld_frame(gObjectEventPic_TeachyTVHost, 2, 4, 1),
    overworld_frame(gObjectEventPic_TeachyTVHost, 2, 4, 2),
    overworld_frame(gObjectEventPic_TeachyTVHost, 2, 4, 3),
    overworld_frame(gObjectEventPic_TeachyTVHost, 2, 4, 4),
    overworld_frame(gObjectEventPic_TeachyTVHost, 2, 4, 5),
    overworld_frame(gObjectEventPic_TeachyTVHost, 2, 4, 6),
    overworld_frame(gObjectEventPic_TeachyTVHost, 2, 4, 7),
    overworld_frame(gObjectEventPic_TeachyTVHost, 2, 4, 8),
};

static const struct SpriteFrameImage sPicTable_UnusedWoman[] = {
    overworld_frame(gObjectEventPic_UnusedWoman, 2, 4, 0),
    overworld_frame(gObjectEventPic_UnusedWoman, 2, 4, 1),
    overworld_frame(gObjectEventPic_UnusedWoman, 2, 4, 2),
    overworld_frame(gObjectEventPic_UnusedWoman, 2, 4, 3),
    overworld_frame(gObjectEventPic_UnusedWoman, 2, 4, 4),
    overworld_frame(gObjectEventPic_UnusedWoman, 2, 4, 5),
    overworld_frame(gObjectEventPic_UnusedWoman, 2, 4, 6),
    overworld_frame(gObjectEventPic_UnusedWoman, 2, 4, 7),
    overworld_frame(gObjectEventPic_UnusedWoman, 2, 4, 8),
};

static const struct SpriteFrameImage sPicTable_TuberF[] = {
    overworld_frame(gObjectEventPic_TuberF, 2, 2, 0),
    overworld_frame(gObjectEventPic_TuberF, 2, 2, 1),
    overworld_frame(gObjectEventPic_TuberF, 2, 2, 2),
    overworld_frame(gObjectEventPic_TuberF, 2, 2, 3),
    overworld_frame(gObjectEventPic_TuberF, 2, 2, 4),
    overworld_frame(gObjectEventPic_TuberF, 2, 2, 5),
    overworld_frame(gObjectEventPic_TuberF, 2, 2, 6),
    overworld_frame(gObjectEventPic_TuberF, 2, 2, 7),
    overworld_frame(gObjectEventPic_TuberF, 2, 2, 8),
    overworld_frame(gObjectEventPic_TuberF, 2, 2, 9),
};

static const struct SpriteFrameImage sPicTable_TuberMWater[] = {
    overworld_frame(gObjectEventPic_TuberMWater, 2, 2, 0),
    overworld_frame(gObjectEventPic_TuberMWater, 2, 2, 1),
    overworld_frame(gObjectEventPic_TuberMWater, 2, 2, 2),
    overworld_frame(gObjectEventPic_TuberMWater, 2, 2, 3),
    overworld_frame(gObjectEventPic_TuberMWater, 2, 2, 4),
    overworld_frame(gObjectEventPic_TuberMWater, 2, 2, 5),
    overworld_frame(gObjectEventPic_TuberMWater, 2, 2, 6),
    overworld_frame(gObjectEventPic_TuberMWater, 2, 2, 7),
    overworld_frame(gObjectEventPic_TuberMWater, 2, 2, 8),
    overworld_frame(gObjectEventPic_TuberMWater, 2, 2, 9),
};

static const struct SpriteFrameImage sPicTable_TuberMLand[] = {
    overworld_frame(gObjectEventPic_TuberMLand, 2, 2, 0),
    overworld_frame(gObjectEventPic_TuberMLand, 2, 2, 1),
    overworld_frame(gObjectEventPic_TuberMLand, 2, 2, 2),
    overworld_frame(gObjectEventPic_TuberMLand, 2, 2, 3),
    overworld_frame(gObjectEventPic_TuberMLand, 2, 2, 4),
    overworld_frame(gObjectEventPic_TuberMLand, 2, 2, 5),
    overworld_frame(gObjectEventPic_TuberMLand, 2, 2, 6),
    overworld_frame(gObjectEventPic_TuberMLand, 2, 2, 7),
    overworld_frame(gObjectEventPic_TuberMLand, 2, 2, 8),
    overworld_frame(gObjectEventPic_TuberMLand, 2, 2, 9),
};

static const struct SpriteFrameImage sPicTable_Hiker[] = {
    overworld_frame(gObjectEventPic_Hiker, 2, 4, 0),
    overworld_frame(gObjectEventPic_Hiker, 2, 4, 1),
    overworld_frame(gObjectEventPic_Hiker, 2, 4, 2),
    overworld_frame(gObjectEventPic_Hiker, 2, 4, 3),
    overworld_frame(gObjectEventPic_Hiker, 2, 4, 4),
    overworld_frame(gObjectEventPic_Hiker, 2, 4, 5),
    overworld_frame(gObjectEventPic_Hiker, 2, 4, 6),
    overworld_frame(gObjectEventPic_Hiker, 2, 4, 7),
    overworld_frame(gObjectEventPic_Hiker, 2, 4, 8),
    overworld_frame(gObjectEventPic_Hiker, 2, 4, 9),
};

static const struct SpriteFrameImage sPicTable_Biker[] = {
    overworld_frame(gObjectEventPic_Biker, 4, 4, 0),
    overworld_frame(gObjectEventPic_Biker, 4, 4, 1),
    overworld_frame(gObjectEventPic_Biker, 4, 4, 2),
    overworld_frame(gObjectEventPic_Biker, 4, 4, 3),
    overworld_frame(gObjectEventPic_Biker, 4, 4, 4),
    overworld_frame(gObjectEventPic_Biker, 4, 4, 5),
    overworld_frame(gObjectEventPic_Biker, 4, 4, 6),
    overworld_frame(gObjectEventPic_Biker, 4, 4, 7),
    overworld_frame(gObjectEventPic_Biker, 4, 4, 8),
    overworld_frame(gObjectEventPic_Biker, 4, 4, 9),
};

static const struct SpriteFrameImage sPicTable_GymGuy[] = {
    overworld_frame(gObjectEventPic_GymGuy, 2, 4, 0),
    overworld_frame(gObjectEventPic_GymGuy, 2, 4, 1),
    overworld_frame(gObjectEventPic_GymGuy, 2, 4, 2),
    overworld_frame(gObjectEventPic_GymGuy, 2, 4, 3),
    overworld_frame(gObjectEventPic_GymGuy, 2, 4, 4),
    overworld_frame(gObjectEventPic_GymGuy, 2, 4, 5),
    overworld_frame(gObjectEventPic_GymGuy, 2, 4, 6),
    overworld_frame(gObjectEventPic_GymGuy, 2, 4, 7),
    overworld_frame(gObjectEventPic_GymGuy, 2, 4, 8),
};

static const struct SpriteFrameImage sPicTable_Nurse[] = {
    overworld_frame(gObjectEventPic_Nurse, 2, 4, 0),
    overworld_frame(gObjectEventPic_Nurse, 2, 4, 1),
    overworld_frame(gObjectEventPic_Nurse, 2, 4, 2),
    overworld_frame(gObjectEventPic_Nurse, 2, 4, 0),
    overworld_frame(gObjectEventPic_Nurse, 2, 4, 0),
    overworld_frame(gObjectEventPic_Nurse, 2, 4, 1),
    overworld_frame(gObjectEventPic_Nurse, 2, 4, 1),
    overworld_frame(gObjectEventPic_Nurse, 2, 4, 2),
    overworld_frame(gObjectEventPic_Nurse, 2, 4, 2),
    overworld_frame(gObjectEventPic_Nurse, 2, 4, 3),
};

static const struct SpriteFrameImage sPicTable_UnusedMaleReceptionist[] = {
    overworld_frame(gObjectEventPic_UnusedMaleReceptionist, 2, 4, 0),
    overworld_frame(gObjectEventPic_UnusedMaleReceptionist, 2, 4, 1),
    overworld_frame(gObjectEventPic_UnusedMaleReceptionist, 2, 4, 2),
    overworld_frame(gObjectEventPic_UnusedMaleReceptionist, 2, 4, 0),
    overworld_frame(gObjectEventPic_UnusedMaleReceptionist, 2, 4, 0),
    overworld_frame(gObjectEventPic_UnusedMaleReceptionist, 2, 4, 1),
    overworld_frame(gObjectEventPic_UnusedMaleReceptionist, 2, 4, 1),
    overworld_frame(gObjectEventPic_UnusedMaleReceptionist, 2, 4, 2),
    overworld_frame(gObjectEventPic_UnusedMaleReceptionist, 2, 4, 2),
};

static const struct SpriteFrameImage sPicTable_ItemBall[] = {
    overworld_frame(gObjectEventPic_ItemBall, 2, 2, 0),
};

static const struct SpriteFrameImage sPicTable_ProfOak[] = {
    overworld_frame(gObjectEventPic_ProfOak, 2, 4, 0),
    overworld_frame(gObjectEventPic_ProfOak, 2, 4, 1),
    overworld_frame(gObjectEventPic_ProfOak, 2, 4, 2),
    overworld_frame(gObjectEventPic_ProfOak, 2, 4, 3),
    overworld_frame(gObjectEventPic_ProfOak, 2, 4, 4),
    overworld_frame(gObjectEventPic_ProfOak, 2, 4, 5),
    overworld_frame(gObjectEventPic_ProfOak, 2, 4, 6),
    overworld_frame(gObjectEventPic_ProfOak, 2, 4, 7),
    overworld_frame(gObjectEventPic_ProfOak, 2, 4, 8),
};

static const struct SpriteFrameImage sPicTable_Man[] = {
    overworld_frame(gObjectEventPic_Man, 2, 4, 0),
    overworld_frame(gObjectEventPic_Man, 2, 4, 1),
    overworld_frame(gObjectEventPic_Man, 2, 4, 2),
    overworld_frame(gObjectEventPic_Man, 2, 4, 3),
    overworld_frame(gObjectEventPic_Man, 2, 4, 4),
    overworld_frame(gObjectEventPic_Man, 2, 4, 5),
    overworld_frame(gObjectEventPic_Man, 2, 4, 6),
    overworld_frame(gObjectEventPic_Man, 2, 4, 7),
    overworld_frame(gObjectEventPic_Man, 2, 4, 8),
    overworld_frame(gObjectEventPic_Man, 2, 4, 9),
};

static const struct SpriteFrameImage sPicTable_Rocker[] = {
    overworld_frame(gObjectEventPic_Rocker, 2, 4, 0),
    overworld_frame(gObjectEventPic_Rocker, 2, 4, 1),
    overworld_frame(gObjectEventPic_Rocker, 2, 4, 2),
    overworld_frame(gObjectEventPic_Rocker, 2, 4, 3),
    overworld_frame(gObjectEventPic_Rocker, 2, 4, 4),
    overworld_frame(gObjectEventPic_Rocker, 2, 4, 5),
    overworld_frame(gObjectEventPic_Rocker, 2, 4, 6),
    overworld_frame(gObjectEventPic_Rocker, 2, 4, 7),
    overworld_frame(gObjectEventPic_Rocker, 2, 4, 8),
    overworld_frame(gObjectEventPic_Rocker, 2, 4, 9),
};

static const struct SpriteFrameImage sPicTable_MrFuji[] = {
    overworld_frame(gObjectEventPic_MrFuji, 2, 4, 0),
    overworld_frame(gObjectEventPic_MrFuji, 2, 4, 1),
    overworld_frame(gObjectEventPic_MrFuji, 2, 4, 2),
    overworld_frame(gObjectEventPic_MrFuji, 2, 4, 3),
    overworld_frame(gObjectEventPic_MrFuji, 2, 4, 4),
    overworld_frame(gObjectEventPic_MrFuji, 2, 4, 5),
    overworld_frame(gObjectEventPic_MrFuji, 2, 4, 6),
    overworld_frame(gObjectEventPic_MrFuji, 2, 4, 7),
    overworld_frame(gObjectEventPic_MrFuji, 2, 4, 8),
};

static const struct SpriteFrameImage sPicTable_Bruno[] = {
    overworld_frame(gObjectEventPic_Bruno, 2, 4, 0),
    overworld_frame(gObjectEventPic_Bruno, 2, 4, 1),
    overworld_frame(gObjectEventPic_Bruno, 2, 4, 2),
    overworld_frame(gObjectEventPic_Bruno, 2, 4, 0),
    overworld_frame(gObjectEventPic_Bruno, 2, 4, 0),
    overworld_frame(gObjectEventPic_Bruno, 2, 4, 1),
    overworld_frame(gObjectEventPic_Bruno, 2, 4, 1),
    overworld_frame(gObjectEventPic_Bruno, 2, 4, 2),
    overworld_frame(gObjectEventPic_Bruno, 2, 4, 2),
};

static const struct SpriteFrameImage sPicTable_CutTree[] = {
    overworld_frame(gObjectEventPic_CutTree, 2, 2, 0),
    overworld_frame(gObjectEventPic_CutTree, 2, 2, 1),
    overworld_frame(gObjectEventPic_CutTree, 2, 2, 2),
    overworld_frame(gObjectEventPic_CutTree, 2, 2, 3),
};

static const struct SpriteFrameImage sPicTable_Clerk[] = {
    overworld_frame(gObjectEventPic_Clerk, 2, 4, 0),
    overworld_frame(gObjectEventPic_Clerk, 2, 4, 1),
    overworld_frame(gObjectEventPic_Clerk, 2, 4, 2),
    overworld_frame(gObjectEventPic_Clerk, 2, 4, 3),
    overworld_frame(gObjectEventPic_Clerk, 2, 4, 4),
    overworld_frame(gObjectEventPic_Clerk, 2, 4, 5),
    overworld_frame(gObjectEventPic_Clerk, 2, 4, 6),
    overworld_frame(gObjectEventPic_Clerk, 2, 4, 7),
    overworld_frame(gObjectEventPic_Clerk, 2, 4, 8),
};

static const struct SpriteFrameImage sPicTable_MGDeliveryman[] = {
    overworld_frame(gObjectEventPic_MGDeliveryman, 2, 4, 0),
    overworld_frame(gObjectEventPic_MGDeliveryman, 2, 4, 1),
    overworld_frame(gObjectEventPic_MGDeliveryman, 2, 4, 2),
    overworld_frame(gObjectEventPic_MGDeliveryman, 2, 4, 0),
    overworld_frame(gObjectEventPic_MGDeliveryman, 2, 4, 0),
    overworld_frame(gObjectEventPic_MGDeliveryman, 2, 4, 1),
    overworld_frame(gObjectEventPic_MGDeliveryman, 2, 4, 1),
    overworld_frame(gObjectEventPic_MGDeliveryman, 2, 4, 2),
    overworld_frame(gObjectEventPic_MGDeliveryman, 2, 4, 2),
};

static const struct SpriteFrameImage sPicTable_TrainerTowerDude[] = {
    overworld_frame(gObjectEventPic_TrainerTowerDude, 2, 4, 0),
    overworld_frame(gObjectEventPic_TrainerTowerDude, 2, 4, 1),
    overworld_frame(gObjectEventPic_TrainerTowerDude, 2, 4, 2),
    overworld_frame(gObjectEventPic_TrainerTowerDude, 2, 4, 0),
    overworld_frame(gObjectEventPic_TrainerTowerDude, 2, 4, 0),
    overworld_frame(gObjectEventPic_TrainerTowerDude, 2, 4, 1),
    overworld_frame(gObjectEventPic_TrainerTowerDude, 2, 4, 1),
    overworld_frame(gObjectEventPic_TrainerTowerDude, 2, 4, 2),
    overworld_frame(gObjectEventPic_TrainerTowerDude, 2, 4, 2),
};

static const struct SpriteFrameImage sPicTable_CableClubReceptionist[] = {
    overworld_frame(gObjectEventPic_CableClubReceptionist, 2, 4, 0),
    overworld_frame(gObjectEventPic_CableClubReceptionist, 2, 4, 1),
    overworld_frame(gObjectEventPic_CableClubReceptionist, 2, 4, 2),
    overworld_frame(gObjectEventPic_CableClubReceptionist, 2, 4, 0),
    overworld_frame(gObjectEventPic_CableClubReceptionist, 2, 4, 0),
    overworld_frame(gObjectEventPic_CableClubReceptionist, 2, 4, 1),
    overworld_frame(gObjectEventPic_CableClubReceptionist, 2, 4, 1),
    overworld_frame(gObjectEventPic_CableClubReceptionist, 2, 4, 2),
    overworld_frame(gObjectEventPic_CableClubReceptionist, 2, 4, 2),
};

static const struct SpriteFrameImage sPicTable_UnionRoomReceptionist[] = {
    overworld_frame(gObjectEventPic_UnionRoomReceptionist, 2, 4, 0),
    overworld_frame(gObjectEventPic_UnionRoomReceptionist, 2, 4, 1),
    overworld_frame(gObjectEventPic_UnionRoomReceptionist, 2, 4, 2),
    overworld_frame(gObjectEventPic_UnionRoomReceptionist, 2, 4, 0),
    overworld_frame(gObjectEventPic_UnionRoomReceptionist, 2, 4, 0),
    overworld_frame(gObjectEventPic_UnionRoomReceptionist, 2, 4, 1),
    overworld_frame(gObjectEventPic_UnionRoomReceptionist, 2, 4, 1),
    overworld_frame(gObjectEventPic_UnionRoomReceptionist, 2, 4, 2),
    overworld_frame(gObjectEventPic_UnionRoomReceptionist, 2, 4, 2),
};

static const struct SpriteFrameImage sPicTable_RockSmashRock[] = {
    overworld_frame(gObjectEventPic_RockSmashRock, 2, 2, 0),
    overworld_frame(gObjectEventPic_RockSmashRock, 2, 2, 1),
    overworld_frame(gObjectEventPic_RockSmashRock, 2, 2, 2),
    overworld_frame(gObjectEventPic_RockSmashRock, 2, 2, 3),
};

static const struct SpriteFrameImage sPicTable_StrengthBoulder[] = {
    overworld_frame(gObjectEventPic_StrengthBoulder, 2, 2, 0),
};

static const struct SpriteFrameImage sPicTable_RocketM[] = {
    overworld_frame(gObjectEventPic_RocketM, 2, 4, 0),
    overworld_frame(gObjectEventPic_RocketM, 2, 4, 1),
    overworld_frame(gObjectEventPic_RocketM, 2, 4, 2),
    overworld_frame(gObjectEventPic_RocketM, 2, 4, 3),
    overworld_frame(gObjectEventPic_RocketM, 2, 4, 4),
    overworld_frame(gObjectEventPic_RocketM, 2, 4, 5),
    overworld_frame(gObjectEventPic_RocketM, 2, 4, 6),
    overworld_frame(gObjectEventPic_RocketM, 2, 4, 7),
    overworld_frame(gObjectEventPic_RocketM, 2, 4, 8),
};

static const struct SpriteFrameImage sPicTable_Celio[] = {
    overworld_frame(gObjectEventPic_Celio, 2, 4, 0),
    overworld_frame(gObjectEventPic_Celio, 2, 4, 1),
    overworld_frame(gObjectEventPic_Celio, 2, 4, 2),
    overworld_frame(gObjectEventPic_Celio, 2, 4, 3),
    overworld_frame(gObjectEventPic_Celio, 2, 4, 4),
    overworld_frame(gObjectEventPic_Celio, 2, 4, 5),
    overworld_frame(gObjectEventPic_Celio, 2, 4, 6),
    overworld_frame(gObjectEventPic_Celio, 2, 4, 7),
    overworld_frame(gObjectEventPic_Celio, 2, 4, 8),
};

static const struct SpriteFrameImage sPicTable_Agatha[] = {
    overworld_frame(gObjectEventPic_Agatha, 2, 4, 0),
    overworld_frame(gObjectEventPic_Agatha, 2, 4, 1),
    overworld_frame(gObjectEventPic_Agatha, 2, 4, 2),
    overworld_frame(gObjectEventPic_Agatha, 2, 4, 0),
    overworld_frame(gObjectEventPic_Agatha, 2, 4, 0),
    overworld_frame(gObjectEventPic_Agatha, 2, 4, 1),
    overworld_frame(gObjectEventPic_Agatha, 2, 4, 1),
    overworld_frame(gObjectEventPic_Agatha, 2, 4, 2),
    overworld_frame(gObjectEventPic_Agatha, 2, 4, 2),
};

static const struct SpriteFrameImage sPicTable_Brock[] = {
    overworld_frame(gObjectEventPic_Brock, 2, 4, 0),
    overworld_frame(gObjectEventPic_Brock, 2, 4, 1),
    overworld_frame(gObjectEventPic_Brock, 2, 4, 2),
    overworld_frame(gObjectEventPic_Brock, 2, 4, 0),
    overworld_frame(gObjectEventPic_Brock, 2, 4, 0),
    overworld_frame(gObjectEventPic_Brock, 2, 4, 1),
    overworld_frame(gObjectEventPic_Brock, 2, 4, 1),
    overworld_frame(gObjectEventPic_Brock, 2, 4, 2),
    overworld_frame(gObjectEventPic_Brock, 2, 4, 2),
};

static const struct SpriteFrameImage sPicTable_Misty[] = {
    overworld_frame(gObjectEventPic_Misty, 2, 4, 0),
    overworld_frame(gObjectEventPic_Misty, 2, 4, 1),
    overworld_frame(gObjectEventPic_Misty, 2, 4, 2),
    overworld_frame(gObjectEventPic_Misty, 2, 4, 0),
    overworld_frame(gObjectEventPic_Misty, 2, 4, 0),
    overworld_frame(gObjectEventPic_Misty, 2, 4, 1),
    overworld_frame(gObjectEventPic_Misty, 2, 4, 1),
    overworld_frame(gObjectEventPic_Misty, 2, 4, 2),
    overworld_frame(gObjectEventPic_Misty, 2, 4, 2),
};

static const struct SpriteFrameImage sPicTable_LtSurge[] = {
    overworld_frame(gObjectEventPic_LtSurge, 2, 4, 0),
    overworld_frame(gObjectEventPic_LtSurge, 2, 4, 1),
    overworld_frame(gObjectEventPic_LtSurge, 2, 4, 2),
    overworld_frame(gObjectEventPic_LtSurge, 2, 4, 0),
    overworld_frame(gObjectEventPic_LtSurge, 2, 4, 0),
    overworld_frame(gObjectEventPic_LtSurge, 2, 4, 1),
    overworld_frame(gObjectEventPic_LtSurge, 2, 4, 1),
    overworld_frame(gObjectEventPic_LtSurge, 2, 4, 2),
    overworld_frame(gObjectEventPic_LtSurge, 2, 4, 2),
};

static const struct SpriteFrameImage sPicTable_Erika[] = {
    overworld_frame(gObjectEventPic_Erika, 2, 4, 0),
    overworld_frame(gObjectEventPic_Erika, 2, 4, 1),
    overworld_frame(gObjectEventPic_Erika, 2, 4, 2),
    overworld_frame(gObjectEventPic_Erika, 2, 4, 0),
    overworld_frame(gObjectEventPic_Erika, 2, 4, 0),
    overworld_frame(gObjectEventPic_Erika, 2, 4, 1),
    overworld_frame(gObjectEventPic_Erika, 2, 4, 1),
    overworld_frame(gObjectEventPic_Erika, 2, 4, 2),
    overworld_frame(gObjectEventPic_Erika, 2, 4, 2),
};

static const struct SpriteFrameImage sPicTable_Koga[] = {
    overworld_frame(gObjectEventPic_Koga, 2, 4, 0),
    overworld_frame(gObjectEventPic_Koga, 2, 4, 1),
    overworld_frame(gObjectEventPic_Koga, 2, 4, 2),
    overworld_frame(gObjectEventPic_Koga, 2, 4, 0),
    overworld_frame(gObjectEventPic_Koga, 2, 4, 0),
    overworld_frame(gObjectEventPic_Koga, 2, 4, 1),
    overworld_frame(gObjectEventPic_Koga, 2, 4, 1),
    overworld_frame(gObjectEventPic_Koga, 2, 4, 2),
    overworld_frame(gObjectEventPic_Koga, 2, 4, 2),
};

static const struct SpriteFrameImage sPicTable_Giovanni[] = {
    overworld_frame(gObjectEventPic_Giovanni, 2, 4, 0),
    overworld_frame(gObjectEventPic_Giovanni, 2, 4, 1),
    overworld_frame(gObjectEventPic_Giovanni, 2, 4, 2),
    overworld_frame(gObjectEventPic_Giovanni, 2, 4, 3),
    overworld_frame(gObjectEventPic_Giovanni, 2, 4, 4),
    overworld_frame(gObjectEventPic_Giovanni, 2, 4, 5),
    overworld_frame(gObjectEventPic_Giovanni, 2, 4, 6),
    overworld_frame(gObjectEventPic_Giovanni, 2, 4, 7),
    overworld_frame(gObjectEventPic_Giovanni, 2, 4, 8),
};

static const struct SpriteFrameImage sPicTable_Blaine[] = {
    overworld_frame(gObjectEventPic_Blaine, 2, 4, 0),
    overworld_frame(gObjectEventPic_Blaine, 2, 4, 1),
    overworld_frame(gObjectEventPic_Blaine, 2, 4, 2),
    overworld_frame(gObjectEventPic_Blaine, 2, 4, 0),
    overworld_frame(gObjectEventPic_Blaine, 2, 4, 0),
    overworld_frame(gObjectEventPic_Blaine, 2, 4, 1),
    overworld_frame(gObjectEventPic_Blaine, 2, 4, 1),
    overworld_frame(gObjectEventPic_Blaine, 2, 4, 2),
    overworld_frame(gObjectEventPic_Blaine, 2, 4, 2),
};

static const struct SpriteFrameImage sPicTable_Sabrina[] = {
    overworld_frame(gObjectEventPic_Sabrina, 2, 4, 0),
    overworld_frame(gObjectEventPic_Sabrina, 2, 4, 1),
    overworld_frame(gObjectEventPic_Sabrina, 2, 4, 2),
    overworld_frame(gObjectEventPic_Sabrina, 2, 4, 0),
    overworld_frame(gObjectEventPic_Sabrina, 2, 4, 0),
    overworld_frame(gObjectEventPic_Sabrina, 2, 4, 1),
    overworld_frame(gObjectEventPic_Sabrina, 2, 4, 1),
    overworld_frame(gObjectEventPic_Sabrina, 2, 4, 2),
    overworld_frame(gObjectEventPic_Sabrina, 2, 4, 2),
};

static const struct SpriteFrameImage sPicTable_Bill[] = {
    overworld_frame(gObjectEventPic_Bill, 2, 4, 0),
    overworld_frame(gObjectEventPic_Bill, 2, 4, 1),
    overworld_frame(gObjectEventPic_Bill, 2, 4, 2),
    overworld_frame(gObjectEventPic_Bill, 2, 4, 3),
    overworld_frame(gObjectEventPic_Bill, 2, 4, 4),
    overworld_frame(gObjectEventPic_Bill, 2, 4, 5),
    overworld_frame(gObjectEventPic_Bill, 2, 4, 6),
    overworld_frame(gObjectEventPic_Bill, 2, 4, 7),
    overworld_frame(gObjectEventPic_Bill, 2, 4, 8),
};

static const struct SpriteFrameImage sPicTable_Daisy[] = {
    overworld_frame(gObjectEventPic_Daisy, 2, 4, 0),
    overworld_frame(gObjectEventPic_Daisy, 2, 4, 1),
    overworld_frame(gObjectEventPic_Daisy, 2, 4, 2),
    overworld_frame(gObjectEventPic_Daisy, 2, 4, 3),
    overworld_frame(gObjectEventPic_Daisy, 2, 4, 4),
    overworld_frame(gObjectEventPic_Daisy, 2, 4, 5),
    overworld_frame(gObjectEventPic_Daisy, 2, 4, 6),
    overworld_frame(gObjectEventPic_Daisy, 2, 4, 7),
    overworld_frame(gObjectEventPic_Daisy, 2, 4, 8),
};

static const struct SpriteFrameImage sPicTable_Lorelei[] = {
    overworld_frame(gObjectEventPic_Lorelei, 2, 4, 0),
    overworld_frame(gObjectEventPic_Lorelei, 2, 4, 1),
    overworld_frame(gObjectEventPic_Lorelei, 2, 4, 2),
    overworld_frame(gObjectEventPic_Lorelei, 2, 4, 3),
    overworld_frame(gObjectEventPic_Lorelei, 2, 4, 4),
    overworld_frame(gObjectEventPic_Lorelei, 2, 4, 5),
    overworld_frame(gObjectEventPic_Lorelei, 2, 4, 6),
    overworld_frame(gObjectEventPic_Lorelei, 2, 4, 7),
    overworld_frame(gObjectEventPic_Lorelei, 2, 4, 8),
};

static const struct SpriteFrameImage sPicTable_Lance[] = {
    overworld_frame(gObjectEventPic_Lance, 2, 4, 0),
    overworld_frame(gObjectEventPic_Lance, 2, 4, 1),
    overworld_frame(gObjectEventPic_Lance, 2, 4, 2),
    overworld_frame(gObjectEventPic_Lance, 2, 4, 0),
    overworld_frame(gObjectEventPic_Lance, 2, 4, 0),
    overworld_frame(gObjectEventPic_Lance, 2, 4, 1),
    overworld_frame(gObjectEventPic_Lance, 2, 4, 1),
    overworld_frame(gObjectEventPic_Lance, 2, 4, 2),
    overworld_frame(gObjectEventPic_Lance, 2, 4, 2),
};

static const struct SpriteFrameImage sPicTable_Blue[] = {
    overworld_frame(gObjectEventPic_Blue, 2, 4, 0),
    overworld_frame(gObjectEventPic_Blue, 2, 4, 1),
    overworld_frame(gObjectEventPic_Blue, 2, 4, 2),
    overworld_frame(gObjectEventPic_Blue, 2, 4, 3),
    overworld_frame(gObjectEventPic_Blue, 2, 4, 4),
    overworld_frame(gObjectEventPic_Blue, 2, 4, 5),
    overworld_frame(gObjectEventPic_Blue, 2, 4, 6),
    overworld_frame(gObjectEventPic_Blue, 2, 4, 7),
    overworld_frame(gObjectEventPic_Blue, 2, 4, 8),
};

static const struct SpriteFrameImage sPicTable_RedFish[] = {
    overworld_frame(gObjectEventPic_RedFish, 4, 4, 0),
    overworld_frame(gObjectEventPic_RedFish, 4, 4, 1),
    overworld_frame(gObjectEventPic_RedFish, 4, 4, 2),
    overworld_frame(gObjectEventPic_RedFish, 4, 4, 3),
    overworld_frame(gObjectEventPic_RedFish, 4, 4, 4),
    overworld_frame(gObjectEventPic_RedFish, 4, 4, 5),
    overworld_frame(gObjectEventPic_RedFish, 4, 4, 6),
    overworld_frame(gObjectEventPic_RedFish, 4, 4, 7),
    overworld_frame(gObjectEventPic_RedFish, 4, 4, 8),
    overworld_frame(gObjectEventPic_RedFish, 4, 4, 9),
    overworld_frame(gObjectEventPic_RedFish, 4, 4, 10),
    overworld_frame(gObjectEventPic_RedFish, 4, 4, 11),
};

static const struct SpriteFrameImage sPicTable_GreenFish[] = {
    overworld_frame(gObjectEventPic_GreenFish, 4, 4, 0),
    overworld_frame(gObjectEventPic_GreenFish, 4, 4, 1),
    overworld_frame(gObjectEventPic_GreenFish, 4, 4, 2),
    overworld_frame(gObjectEventPic_GreenFish, 4, 4, 3),
    overworld_frame(gObjectEventPic_GreenFish, 4, 4, 4),
    overworld_frame(gObjectEventPic_GreenFish, 4, 4, 5),
    overworld_frame(gObjectEventPic_GreenFish, 4, 4, 6),
    overworld_frame(gObjectEventPic_GreenFish, 4, 4, 7),
    overworld_frame(gObjectEventPic_GreenFish, 4, 4, 8),
    overworld_frame(gObjectEventPic_GreenFish, 4, 4, 9),
    overworld_frame(gObjectEventPic_GreenFish, 4, 4, 10),
    overworld_frame(gObjectEventPic_GreenFish, 4, 4, 11),
};

static const struct SpriteFrameImage sPicTable_TownMap[] = {
    overworld_frame(gObjectEventPic_TownMap, 2, 4, 0),
};

static const struct SpriteFrameImage sPicTable_Pokedex[] = {
    overworld_frame(gObjectEventPic_Pokedex, 2, 2, 0),
};

static const struct SpriteFrameImage sPicTable_GBAKid[] = {
    overworld_frame(gObjectEventPic_GBAKid, 2, 4, 0),
    overworld_frame(gObjectEventPic_GBAKid, 2, 4, 1),
    overworld_frame(gObjectEventPic_GBAKid, 2, 4, 2),
    overworld_frame(gObjectEventPic_GBAKid, 2, 4, 0),
    overworld_frame(gObjectEventPic_GBAKid, 2, 4, 0),
    overworld_frame(gObjectEventPic_GBAKid, 2, 4, 1),
    overworld_frame(gObjectEventPic_GBAKid, 2, 4, 1),
    overworld_frame(gObjectEventPic_GBAKid, 2, 4, 2),
    overworld_frame(gObjectEventPic_GBAKid, 2, 4, 2),
};

static const struct SpriteFrameImage sPicTable_Fossil[] = {
    overworld_frame(gObjectEventPic_Fossil, 2, 2, 0),
};

static const struct SpriteFrameImage sPicTable_Ruby[] = {
    overworld_frame(gObjectEventPic_Ruby, 2, 2, 0),
};

static const struct SpriteFrameImage sPicTable_Sapphire[] = {
    overworld_frame(gObjectEventPic_Sapphire, 2, 2, 0),
};

static const struct SpriteFrameImage sPicTable_OldAmber[] = {
    overworld_frame(gObjectEventPic_OldAmber, 2, 2, 0),
};

static const struct SpriteFrameImage sPicTable_GymSign[] = {
    overworld_frame(gObjectEventPic_GymSign, 2, 4, 0),
};

static const struct SpriteFrameImage sPicTable_Sign[] = {
    overworld_frame(gObjectEventPic_Sign, 2, 2, 0),
};

static const struct SpriteFrameImage sPicTable_WoodenSign[] = {
    overworld_frame(gObjectEventPic_WoodenSign, 2, 2, 0),
};

static const struct SpriteFrameImage sPicTable_Clipboard[] = {
    overworld_frame(gObjectEventPic_Clipboard, 2, 2, 0),
};

static const struct SpriteFrameImage sPicTable_BirthIslandStone[] = {
    overworld_frame(gObjectEventPic_BirthIslandStone, 4, 4, 0),
};

static const struct SpriteFrameImage sPicTable_LaprasDoll[] = {
    overworld_frame(gObjectEventPic_LaprasDoll, 4, 4, 0),
};

static const struct SpriteFrameImage sPicTable_Seagallop[] = {
    overworld_frame(gObjectEventPic_Seagallop, 4, 16, 0),
    overworld_frame(gObjectEventPic_Seagallop, 4, 16, 0),
    overworld_frame(gObjectEventPic_Seagallop, 4, 16, 0),
    overworld_frame(gObjectEventPic_Seagallop, 4, 16, 0),
    overworld_frame(gObjectEventPic_Seagallop, 4, 16, 0),
    overworld_frame(gObjectEventPic_Seagallop, 4, 16, 0),
    overworld_frame(gObjectEventPic_Seagallop, 4, 16, 0),
    overworld_frame(gObjectEventPic_Seagallop, 4, 16, 0),
    overworld_frame(gObjectEventPic_Seagallop, 4, 16, 0),
};

static const struct SpriteFrameImage sPicTable_SSAnne[] = {
    overworld_frame(gObjectEventPic_SSAnne, 8, 16, 0),
    overworld_frame(gObjectEventPic_SSAnne, 8, 16, 0),
    overworld_frame(gObjectEventPic_SSAnne, 8, 16, 0),
    overworld_frame(gObjectEventPic_SSAnne, 8, 16, 0),
    overworld_frame(gObjectEventPic_SSAnne, 8, 16, 0),
    overworld_frame(gObjectEventPic_SSAnne, 8, 16, 0),
    overworld_frame(gObjectEventPic_SSAnne, 8, 16, 0),
    overworld_frame(gObjectEventPic_SSAnne, 8, 16, 0),
    overworld_frame(gObjectEventPic_SSAnne, 8, 16, 0),
};

static const struct SpriteFrameImage sPicTable_Snorlax[] = {
    overworld_frame(gObjectEventPic_Snorlax, 4, 4, 0),
    overworld_frame(gObjectEventPic_Snorlax, 4, 4, 0),
    overworld_frame(gObjectEventPic_Snorlax, 4, 4, 0),
    overworld_frame(gObjectEventPic_Snorlax, 4, 4, 0),
    overworld_frame(gObjectEventPic_Snorlax, 4, 4, 0),
    overworld_frame(gObjectEventPic_Snorlax, 4, 4, 0),
    overworld_frame(gObjectEventPic_Snorlax, 4, 4, 0),
    overworld_frame(gObjectEventPic_Snorlax, 4, 4, 0),
    overworld_frame(gObjectEventPic_Snorlax, 4, 4, 0),
};

static const struct SpriteFrameImage sPicTable_Spearow[] = {
    overworld_frame(gObjectEventPic_Spearow, 2, 2, 0),
    overworld_frame(gObjectEventPic_Spearow, 2, 2, 1),
    overworld_frame(gObjectEventPic_Spearow, 2, 2, 2),
    overworld_frame(gObjectEventPic_Spearow, 2, 2, 0),
    overworld_frame(gObjectEventPic_Spearow, 2, 2, 0),
    overworld_frame(gObjectEventPic_Spearow, 2, 2, 1),
    overworld_frame(gObjectEventPic_Spearow, 2, 2, 1),
    overworld_frame(gObjectEventPic_Spearow, 2, 2, 2),
    overworld_frame(gObjectEventPic_Spearow, 2, 2, 2),
};

static const struct SpriteFrameImage sPicTable_Pidgeot[] = {
    overworld_frame(gObjectEventPic_Pidgeot, 2, 2, 0),
    overworld_frame(gObjectEventPic_Pidgeot, 2, 2, 1),
    overworld_frame(gObjectEventPic_Pidgeot, 2, 2, 2),
    overworld_frame(gObjectEventPic_Pidgeot, 2, 2, 0),
    overworld_frame(gObjectEventPic_Pidgeot, 2, 2, 0),
    overworld_frame(gObjectEventPic_Pidgeot, 2, 2, 1),
    overworld_frame(gObjectEventPic_Pidgeot, 2, 2, 1),
    overworld_frame(gObjectEventPic_Pidgeot, 2, 2, 2),
    overworld_frame(gObjectEventPic_Pidgeot, 2, 2, 2),
};

static const struct SpriteFrameImage sPicTable_Omanyte[] = {
    overworld_frame(gObjectEventPic_Omanyte, 2, 2, 0),
    overworld_frame(gObjectEventPic_Omanyte, 2, 2, 1),
    overworld_frame(gObjectEventPic_Omanyte, 2, 2, 2),
    overworld_frame(gObjectEventPic_Omanyte, 2, 2, 0),
    overworld_frame(gObjectEventPic_Omanyte, 2, 2, 0),
    overworld_frame(gObjectEventPic_Omanyte, 2, 2, 1),
    overworld_frame(gObjectEventPic_Omanyte, 2, 2, 1),
    overworld_frame(gObjectEventPic_Omanyte, 2, 2, 2),
    overworld_frame(gObjectEventPic_Omanyte, 2, 2, 2),
};

static const struct SpriteFrameImage sPicTable_Kangaskhan[] = {
    overworld_frame(gObjectEventPic_Kangaskhan, 2, 2, 0),
    overworld_frame(gObjectEventPic_Kangaskhan, 2, 2, 1),
    overworld_frame(gObjectEventPic_Kangaskhan, 2, 2, 2),
    overworld_frame(gObjectEventPic_Kangaskhan, 2, 2, 0),
    overworld_frame(gObjectEventPic_Kangaskhan, 2, 2, 0),
    overworld_frame(gObjectEventPic_Kangaskhan, 2, 2, 1),
    overworld_frame(gObjectEventPic_Kangaskhan, 2, 2, 1),
    overworld_frame(gObjectEventPic_Kangaskhan, 2, 2, 2),
    overworld_frame(gObjectEventPic_Kangaskhan, 2, 2, 2),
};

static const struct SpriteFrameImage sPicTable_Psyduck[] = {
    overworld_frame(gObjectEventPic_Psyduck, 2, 2, 0),
    overworld_frame(gObjectEventPic_Psyduck, 2, 2, 1),
    overworld_frame(gObjectEventPic_Psyduck, 2, 2, 2),
    overworld_frame(gObjectEventPic_Psyduck, 2, 2, 0),
    overworld_frame(gObjectEventPic_Psyduck, 2, 2, 0),
    overworld_frame(gObjectEventPic_Psyduck, 2, 2, 1),
    overworld_frame(gObjectEventPic_Psyduck, 2, 2, 1),
    overworld_frame(gObjectEventPic_Psyduck, 2, 2, 2),
    overworld_frame(gObjectEventPic_Psyduck, 2, 2, 2),
};

static const struct SpriteFrameImage sPicTable_NidoranF[] = {
    overworld_frame(gObjectEventPic_NidoranF, 2, 2, 0),
    overworld_frame(gObjectEventPic_NidoranF, 2, 2, 1),
    overworld_frame(gObjectEventPic_NidoranF, 2, 2, 2),
    overworld_frame(gObjectEventPic_NidoranF, 2, 2, 0),
    overworld_frame(gObjectEventPic_NidoranF, 2, 2, 0),
    overworld_frame(gObjectEventPic_NidoranF, 2, 2, 1),
    overworld_frame(gObjectEventPic_NidoranF, 2, 2, 1),
    overworld_frame(gObjectEventPic_NidoranF, 2, 2, 2),
    overworld_frame(gObjectEventPic_NidoranF, 2, 2, 2),
};

static const struct SpriteFrameImage sPicTable_NidoranM[] = {
    overworld_frame(gObjectEventPic_NidoranM, 2, 2, 0),
    overworld_frame(gObjectEventPic_NidoranM, 2, 2, 1),
    overworld_frame(gObjectEventPic_NidoranM, 2, 2, 2),
    overworld_frame(gObjectEventPic_NidoranM, 2, 2, 0),
    overworld_frame(gObjectEventPic_NidoranM, 2, 2, 0),
    overworld_frame(gObjectEventPic_NidoranM, 2, 2, 1),
    overworld_frame(gObjectEventPic_NidoranM, 2, 2, 1),
    overworld_frame(gObjectEventPic_NidoranM, 2, 2, 2),
    overworld_frame(gObjectEventPic_NidoranM, 2, 2, 2),
};

static const struct SpriteFrameImage sPicTable_Nidorino[] = {
    overworld_frame(gObjectEventPic_Nidorino, 2, 2, 0),
    overworld_frame(gObjectEventPic_Nidorino, 2, 2, 1),
    overworld_frame(gObjectEventPic_Nidorino, 2, 2, 2),
    overworld_frame(gObjectEventPic_Nidorino, 2, 2, 0),
    overworld_frame(gObjectEventPic_Nidorino, 2, 2, 0),
    overworld_frame(gObjectEventPic_Nidorino, 2, 2, 1),
    overworld_frame(gObjectEventPic_Nidorino, 2, 2, 1),
    overworld_frame(gObjectEventPic_Nidorino, 2, 2, 2),
    overworld_frame(gObjectEventPic_Nidorino, 2, 2, 2),
};

static const struct SpriteFrameImage sPicTable_Meowth[] = {
    overworld_frame(gObjectEventPic_Meowth, 2, 2, 0),
    overworld_frame(gObjectEventPic_Meowth, 2, 2, 1),
    overworld_frame(gObjectEventPic_Meowth, 2, 2, 2),
    overworld_frame(gObjectEventPic_Meowth, 2, 2, 0),
    overworld_frame(gObjectEventPic_Meowth, 2, 2, 0),
    overworld_frame(gObjectEventPic_Meowth, 2, 2, 1),
    overworld_frame(gObjectEventPic_Meowth, 2, 2, 1),
    overworld_frame(gObjectEventPic_Meowth, 2, 2, 2),
    overworld_frame(gObjectEventPic_Meowth, 2, 2, 2),
};

static const struct SpriteFrameImage sPicTable_Seel[] = {
    overworld_frame(gObjectEventPic_Seel, 2, 2, 0),
    overworld_frame(gObjectEventPic_Seel, 2, 2, 1),
    overworld_frame(gObjectEventPic_Seel, 2, 2, 2),
    overworld_frame(gObjectEventPic_Seel, 2, 2, 0),
    overworld_frame(gObjectEventPic_Seel, 2, 2, 0),
    overworld_frame(gObjectEventPic_Seel, 2, 2, 1),
    overworld_frame(gObjectEventPic_Seel, 2, 2, 1),
    overworld_frame(gObjectEventPic_Seel, 2, 2, 2),
    overworld_frame(gObjectEventPic_Seel, 2, 2, 2),
};

static const struct SpriteFrameImage sPicTable_Voltorb[] = {
    overworld_frame(gObjectEventPic_Voltorb, 2, 2, 0),
    overworld_frame(gObjectEventPic_Voltorb, 2, 2, 1),
    overworld_frame(gObjectEventPic_Voltorb, 2, 2, 2),
    overworld_frame(gObjectEventPic_Voltorb, 2, 2, 0),
    overworld_frame(gObjectEventPic_Voltorb, 2, 2, 0),
    overworld_frame(gObjectEventPic_Voltorb, 2, 2, 1),
    overworld_frame(gObjectEventPic_Voltorb, 2, 2, 1),
    overworld_frame(gObjectEventPic_Voltorb, 2, 2, 2),
    overworld_frame(gObjectEventPic_Voltorb, 2, 2, 2),
};

static const struct SpriteFrameImage sPicTable_Slowpoke[] = {
    overworld_frame(gObjectEventPic_Slowpoke, 2, 2, 0),
    overworld_frame(gObjectEventPic_Slowpoke, 2, 2, 1),
    overworld_frame(gObjectEventPic_Slowpoke, 2, 2, 2),
    overworld_frame(gObjectEventPic_Slowpoke, 2, 2, 0),
    overworld_frame(gObjectEventPic_Slowpoke, 2, 2, 0),
    overworld_frame(gObjectEventPic_Slowpoke, 2, 2, 1),
    overworld_frame(gObjectEventPic_Slowpoke, 2, 2, 1),
    overworld_frame(gObjectEventPic_Slowpoke, 2, 2, 2),
    overworld_frame(gObjectEventPic_Slowpoke, 2, 2, 2),
};

static const struct SpriteFrameImage sPicTable_Slowbro[] = {
    overworld_frame(gObjectEventPic_Slowbro, 2, 2, 0),
    overworld_frame(gObjectEventPic_Slowbro, 2, 2, 1),
    overworld_frame(gObjectEventPic_Slowbro, 2, 2, 2),
    overworld_frame(gObjectEventPic_Slowbro, 2, 2, 0),
    overworld_frame(gObjectEventPic_Slowbro, 2, 2, 0),
    overworld_frame(gObjectEventPic_Slowbro, 2, 2, 1),
    overworld_frame(gObjectEventPic_Slowbro, 2, 2, 1),
    overworld_frame(gObjectEventPic_Slowbro, 2, 2, 2),
    overworld_frame(gObjectEventPic_Slowbro, 2, 2, 2),
};

static const struct SpriteFrameImage sPicTable_Machop[] = {
    overworld_frame(gObjectEventPic_Machop, 2, 2, 0),
    overworld_frame(gObjectEventPic_Machop, 2, 2, 1),
    overworld_frame(gObjectEventPic_Machop, 2, 2, 2),
    overworld_frame(gObjectEventPic_Machop, 2, 2, 0),
    overworld_frame(gObjectEventPic_Machop, 2, 2, 0),
    overworld_frame(gObjectEventPic_Machop, 2, 2, 1),
    overworld_frame(gObjectEventPic_Machop, 2, 2, 1),
    overworld_frame(gObjectEventPic_Machop, 2, 2, 2),
    overworld_frame(gObjectEventPic_Machop, 2, 2, 2),
};

static const struct SpriteFrameImage sPicTable_Wigglytuff[] = {
    overworld_frame(gObjectEventPic_Wigglytuff, 2, 2, 0),
    overworld_frame(gObjectEventPic_Wigglytuff, 2, 2, 1),
    overworld_frame(gObjectEventPic_Wigglytuff, 2, 2, 2),
    overworld_frame(gObjectEventPic_Wigglytuff, 2, 2, 0),
    overworld_frame(gObjectEventPic_Wigglytuff, 2, 2, 0),
    overworld_frame(gObjectEventPic_Wigglytuff, 2, 2, 1),
    overworld_frame(gObjectEventPic_Wigglytuff, 2, 2, 1),
    overworld_frame(gObjectEventPic_Wigglytuff, 2, 2, 2),
    overworld_frame(gObjectEventPic_Wigglytuff, 2, 2, 2),
};

static const struct SpriteFrameImage sPicTable_Doduo[] = {
    overworld_frame(gObjectEventPic_Doduo, 2, 2, 0),
    overworld_frame(gObjectEventPic_Doduo, 2, 2, 1),
    overworld_frame(gObjectEventPic_Doduo, 2, 2, 2),
    overworld_frame(gObjectEventPic_Doduo, 2, 2, 0),
    overworld_frame(gObjectEventPic_Doduo, 2, 2, 0),
    overworld_frame(gObjectEventPic_Doduo, 2, 2, 1),
    overworld_frame(gObjectEventPic_Doduo, 2, 2, 1),
    overworld_frame(gObjectEventPic_Doduo, 2, 2, 2),
    overworld_frame(gObjectEventPic_Doduo, 2, 2, 2),
};

static const struct SpriteFrameImage sPicTable_Fearow[] = {
    overworld_frame(gObjectEventPic_Fearow, 2, 2, 0),
    overworld_frame(gObjectEventPic_Fearow, 2, 2, 1),
    overworld_frame(gObjectEventPic_Fearow, 2, 2, 2),
    overworld_frame(gObjectEventPic_Fearow, 2, 2, 0),
    overworld_frame(gObjectEventPic_Fearow, 2, 2, 0),
    overworld_frame(gObjectEventPic_Fearow, 2, 2, 1),
    overworld_frame(gObjectEventPic_Fearow, 2, 2, 1),
    overworld_frame(gObjectEventPic_Fearow, 2, 2, 2),
    overworld_frame(gObjectEventPic_Fearow, 2, 2, 2),
};

static const struct SpriteFrameImage sPicTable_Lapras[] = {
    overworld_frame(gObjectEventPic_Lapras, 2, 2, 0),
    overworld_frame(gObjectEventPic_Lapras, 2, 2, 1),
    overworld_frame(gObjectEventPic_Lapras, 2, 2, 2),
    overworld_frame(gObjectEventPic_Lapras, 2, 2, 0),
    overworld_frame(gObjectEventPic_Lapras, 2, 2, 0),
    overworld_frame(gObjectEventPic_Lapras, 2, 2, 1),
    overworld_frame(gObjectEventPic_Lapras, 2, 2, 1),
    overworld_frame(gObjectEventPic_Lapras, 2, 2, 2),
    overworld_frame(gObjectEventPic_Lapras, 2, 2, 2),
};

static const struct SpriteFrameImage sPicTable_Zapdos[] = {
    overworld_frame(gObjectEventPic_Zapdos, 4, 4, 0),
    overworld_frame(gObjectEventPic_Zapdos, 4, 4, 0),
    overworld_frame(gObjectEventPic_Zapdos, 4, 4, 0),
    overworld_frame(gObjectEventPic_Zapdos, 4, 4, 0),
    overworld_frame(gObjectEventPic_Zapdos, 4, 4, 0),
    overworld_frame(gObjectEventPic_Zapdos, 4, 4, 0),
    overworld_frame(gObjectEventPic_Zapdos, 4, 4, 0),
    overworld_frame(gObjectEventPic_Zapdos, 4, 4, 0),
    overworld_frame(gObjectEventPic_Zapdos, 4, 4, 0),
};

static const struct SpriteFrameImage sPicTable_Moltres[] = {
    overworld_frame(gObjectEventPic_Moltres, 4, 4, 0),
    overworld_frame(gObjectEventPic_Moltres, 4, 4, 0),
    overworld_frame(gObjectEventPic_Moltres, 4, 4, 0),
    overworld_frame(gObjectEventPic_Moltres, 4, 4, 0),
    overworld_frame(gObjectEventPic_Moltres, 4, 4, 0),
    overworld_frame(gObjectEventPic_Moltres, 4, 4, 0),
    overworld_frame(gObjectEventPic_Moltres, 4, 4, 0),
    overworld_frame(gObjectEventPic_Moltres, 4, 4, 0),
    overworld_frame(gObjectEventPic_Moltres, 4, 4, 0),
};

static const struct SpriteFrameImage sPicTable_Articuno[] = {
    overworld_frame(gObjectEventPic_Articuno, 4, 4, 0),
    overworld_frame(gObjectEventPic_Articuno, 4, 4, 0),
    overworld_frame(gObjectEventPic_Articuno, 4, 4, 0),
    overworld_frame(gObjectEventPic_Articuno, 4, 4, 0),
    overworld_frame(gObjectEventPic_Articuno, 4, 4, 0),
    overworld_frame(gObjectEventPic_Articuno, 4, 4, 0),
    overworld_frame(gObjectEventPic_Articuno, 4, 4, 0),
    overworld_frame(gObjectEventPic_Articuno, 4, 4, 0),
    overworld_frame(gObjectEventPic_Articuno, 4, 4, 0),
};

static const struct SpriteFrameImage sPicTable_DeoxysD[] = {
    overworld_frame(gObjectEventPic_DeoxysD, 4, 4, 0),
    overworld_frame(gObjectEventPic_DeoxysD, 4, 4, 0),
    overworld_frame(gObjectEventPic_DeoxysD, 4, 4, 0),
    overworld_frame(gObjectEventPic_DeoxysD, 4, 4, 0),
    overworld_frame(gObjectEventPic_DeoxysD, 4, 4, 1),
    overworld_frame(gObjectEventPic_DeoxysD, 4, 4, 0),
    overworld_frame(gObjectEventPic_DeoxysD, 4, 4, 1),
    overworld_frame(gObjectEventPic_DeoxysD, 4, 4, 0),
    overworld_frame(gObjectEventPic_DeoxysD, 4, 4, 1),
};

static const struct SpriteFrameImage sPicTable_DeoxysA[] = {
    overworld_frame(gObjectEventPic_DeoxysA, 4, 4, 0),
    overworld_frame(gObjectEventPic_DeoxysA, 4, 4, 0),
    overworld_frame(gObjectEventPic_DeoxysA, 4, 4, 0),
    overworld_frame(gObjectEventPic_DeoxysA, 4, 4, 0),
    overworld_frame(gObjectEventPic_DeoxysA, 4, 4, 1),
    overworld_frame(gObjectEventPic_DeoxysA, 4, 4, 0),
    overworld_frame(gObjectEventPic_DeoxysA, 4, 4, 1),
    overworld_frame(gObjectEventPic_DeoxysA, 4, 4, 0),
    overworld_frame(gObjectEventPic_DeoxysA, 4, 4, 1),
};

static const struct SpriteFrameImage sPicTable_DeoxysN[] = {
    overworld_frame(gObjectEventPic_DeoxysN, 4, 4, 0),
    overworld_frame(gObjectEventPic_DeoxysN, 4, 4, 0),
    overworld_frame(gObjectEventPic_DeoxysN, 4, 4, 0),
    overworld_frame(gObjectEventPic_DeoxysN, 4, 4, 0),
    overworld_frame(gObjectEventPic_DeoxysN, 4, 4, 1),
    overworld_frame(gObjectEventPic_DeoxysN, 4, 4, 0),
    overworld_frame(gObjectEventPic_DeoxysN, 4, 4, 1),
    overworld_frame(gObjectEventPic_DeoxysN, 4, 4, 0),
    overworld_frame(gObjectEventPic_DeoxysN, 4, 4, 1),
};

static const struct SpriteFrameImage sPicTable_Mewtwo[] = {
    overworld_frame(gObjectEventPic_Mewtwo, 2, 2, 0),
    overworld_frame(gObjectEventPic_Mewtwo, 2, 2, 0),
    overworld_frame(gObjectEventPic_Mewtwo, 2, 2, 0),
    overworld_frame(gObjectEventPic_Mewtwo, 2, 2, 0),
    overworld_frame(gObjectEventPic_Mewtwo, 2, 2, 0),
    overworld_frame(gObjectEventPic_Mewtwo, 2, 2, 0),
    overworld_frame(gObjectEventPic_Mewtwo, 2, 2, 0),
    overworld_frame(gObjectEventPic_Mewtwo, 2, 2, 0),
    overworld_frame(gObjectEventPic_Mewtwo, 2, 2, 0),
};

static const struct SpriteFrameImage sPicTable_Mew[] = {
    overworld_frame(gObjectEventPic_Mew, 2, 2, 0),
    overworld_frame(gObjectEventPic_Mew, 2, 2, 0),
    overworld_frame(gObjectEventPic_Mew, 2, 2, 0),
    overworld_frame(gObjectEventPic_Mew, 2, 2, 0),
    overworld_frame(gObjectEventPic_Mew, 2, 2, 0),
    overworld_frame(gObjectEventPic_Mew, 2, 2, 0),
    overworld_frame(gObjectEventPic_Mew, 2, 2, 0),
    overworld_frame(gObjectEventPic_Mew, 2, 2, 0),
    overworld_frame(gObjectEventPic_Mew, 2, 2, 0),
};

static const struct SpriteFrameImage sPicTable_Entei[] = {
    overworld_frame(gObjectEventPic_Entei, 2, 2, 0),
    overworld_frame(gObjectEventPic_Entei, 2, 2, 0),
    overworld_frame(gObjectEventPic_Entei, 2, 2, 0),
    overworld_frame(gObjectEventPic_Entei, 2, 2, 0),
    overworld_frame(gObjectEventPic_Entei, 2, 2, 0),
    overworld_frame(gObjectEventPic_Entei, 2, 2, 0),
    overworld_frame(gObjectEventPic_Entei, 2, 2, 0),
    overworld_frame(gObjectEventPic_Entei, 2, 2, 0),
    overworld_frame(gObjectEventPic_Entei, 2, 2, 0),
};

static const struct SpriteFrameImage sPicTable_Raikou[] = {
    overworld_frame(gObjectEventPic_Raikou, 2, 2, 0),
    overworld_frame(gObjectEventPic_Raikou, 2, 2, 0),
    overworld_frame(gObjectEventPic_Raikou, 2, 2, 0),
    overworld_frame(gObjectEventPic_Raikou, 2, 2, 0),
    overworld_frame(gObjectEventPic_Raikou, 2, 2, 0),
    overworld_frame(gObjectEventPic_Raikou, 2, 2, 0),
    overworld_frame(gObjectEventPic_Raikou, 2, 2, 0),
    overworld_frame(gObjectEventPic_Raikou, 2, 2, 0),
    overworld_frame(gObjectEventPic_Raikou, 2, 2, 0),
};

static const struct SpriteFrameImage sPicTable_Suicune[] = {
    overworld_frame(gObjectEventPic_Suicune, 2, 2, 0),
    overworld_frame(gObjectEventPic_Suicune, 2, 2, 0),
    overworld_frame(gObjectEventPic_Suicune, 2, 2, 0),
    overworld_frame(gObjectEventPic_Suicune, 2, 2, 0),
    overworld_frame(gObjectEventPic_Suicune, 2, 2, 0),
    overworld_frame(gObjectEventPic_Suicune, 2, 2, 0),
    overworld_frame(gObjectEventPic_Suicune, 2, 2, 0),
    overworld_frame(gObjectEventPic_Suicune, 2, 2, 0),
    overworld_frame(gObjectEventPic_Suicune, 2, 2, 0),
};

static const struct SpriteFrameImage sPicTable_Lugia[] = {
    overworld_frame(gObjectEventPic_Lugia, 4, 4, 0),
    overworld_frame(gObjectEventPic_Lugia, 4, 4, 0),
    overworld_frame(gObjectEventPic_Lugia, 4, 4, 0),
    overworld_frame(gObjectEventPic_Lugia, 4, 4, 0),
    overworld_frame(gObjectEventPic_Lugia, 4, 4, 1),
    overworld_frame(gObjectEventPic_Lugia, 4, 4, 0),
    overworld_frame(gObjectEventPic_Lugia, 4, 4, 1),
    overworld_frame(gObjectEventPic_Lugia, 4, 4, 0),
    overworld_frame(gObjectEventPic_Lugia, 4, 4, 1),
};

static const struct SpriteFrameImage sPicTable_HoOh[] = {
    overworld_frame(gObjectEventPic_HoOh, 4, 4, 0),
    overworld_frame(gObjectEventPic_HoOh, 4, 4, 0),
    overworld_frame(gObjectEventPic_HoOh, 4, 4, 0),
    overworld_frame(gObjectEventPic_HoOh, 4, 4, 0),
    overworld_frame(gObjectEventPic_HoOh, 4, 4, 1),
    overworld_frame(gObjectEventPic_HoOh, 4, 4, 0),
    overworld_frame(gObjectEventPic_HoOh, 4, 4, 1),
    overworld_frame(gObjectEventPic_HoOh, 4, 4, 0),
    overworld_frame(gObjectEventPic_HoOh, 4, 4, 1),
};

static const struct SpriteFrameImage sPicTable_Celebi[] = {
    overworld_frame(gObjectEventPic_Celebi, 2, 2, 0),
    overworld_frame(gObjectEventPic_Celebi, 2, 2, 0),
    overworld_frame(gObjectEventPic_Celebi, 2, 2, 0),
    overworld_frame(gObjectEventPic_Celebi, 2, 2, 0),
    overworld_frame(gObjectEventPic_Celebi, 2, 2, 0),
    overworld_frame(gObjectEventPic_Celebi, 2, 2, 0),
    overworld_frame(gObjectEventPic_Celebi, 2, 2, 0),
    overworld_frame(gObjectEventPic_Celebi, 2, 2, 0),
    overworld_frame(gObjectEventPic_Celebi, 2, 2, 0),
};

static const struct SpriteFrameImage sPicTable_Cubone[] = {
    overworld_frame(gObjectEventPic_Cubone, 2, 2, 0),
    overworld_frame(gObjectEventPic_Cubone, 2, 2, 1),
    overworld_frame(gObjectEventPic_Cubone, 2, 2, 2),
    overworld_frame(gObjectEventPic_Cubone, 2, 2, 0),
    overworld_frame(gObjectEventPic_Cubone, 2, 2, 0),
    overworld_frame(gObjectEventPic_Cubone, 2, 2, 1),
    overworld_frame(gObjectEventPic_Cubone, 2, 2, 1),
    overworld_frame(gObjectEventPic_Cubone, 2, 2, 2),
    overworld_frame(gObjectEventPic_Cubone, 2, 2, 2),
};

static const struct SpriteFrameImage sPicTable_Poliwrath[] = {
    overworld_frame(gObjectEventPic_Poliwrath, 2, 2, 0),
    overworld_frame(gObjectEventPic_Poliwrath, 2, 2, 1),
    overworld_frame(gObjectEventPic_Poliwrath, 2, 2, 2),
    overworld_frame(gObjectEventPic_Poliwrath, 2, 2, 0),
    overworld_frame(gObjectEventPic_Poliwrath, 2, 2, 0),
    overworld_frame(gObjectEventPic_Poliwrath, 2, 2, 1),
    overworld_frame(gObjectEventPic_Poliwrath, 2, 2, 1),
    overworld_frame(gObjectEventPic_Poliwrath, 2, 2, 2),
    overworld_frame(gObjectEventPic_Poliwrath, 2, 2, 2),
};

static const struct SpriteFrameImage sPicTable_Chansey[] = {
    overworld_frame(gObjectEventPic_Chansey, 2, 2, 0),
    overworld_frame(gObjectEventPic_Chansey, 2, 2, 1),
    overworld_frame(gObjectEventPic_Chansey, 2, 2, 2),
    overworld_frame(gObjectEventPic_Chansey, 2, 2, 0),
    overworld_frame(gObjectEventPic_Chansey, 2, 2, 0),
    overworld_frame(gObjectEventPic_Chansey, 2, 2, 1),
    overworld_frame(gObjectEventPic_Chansey, 2, 2, 1),
    overworld_frame(gObjectEventPic_Chansey, 2, 2, 2),
    overworld_frame(gObjectEventPic_Chansey, 2, 2, 2),
};

static const struct SpriteFrameImage sPicTable_Pikachu[] = {
    overworld_frame(gObjectEventPic_Pikachu, 2, 2, 0),
    overworld_frame(gObjectEventPic_Pikachu, 2, 2, 1),
    overworld_frame(gObjectEventPic_Pikachu, 2, 2, 2),
    overworld_frame(gObjectEventPic_Pikachu, 2, 2, 0),
    overworld_frame(gObjectEventPic_Pikachu, 2, 2, 0),
    overworld_frame(gObjectEventPic_Pikachu, 2, 2, 1),
    overworld_frame(gObjectEventPic_Pikachu, 2, 2, 1),
    overworld_frame(gObjectEventPic_Pikachu, 2, 2, 2),
    overworld_frame(gObjectEventPic_Pikachu, 2, 2, 2),
};

static const struct SpriteFrameImage sPicTable_Jigglypuff[] = {
    overworld_frame(gObjectEventPic_Jigglypuff, 2, 2, 0),
    overworld_frame(gObjectEventPic_Jigglypuff, 2, 2, 1),
    overworld_frame(gObjectEventPic_Jigglypuff, 2, 2, 2),
    overworld_frame(gObjectEventPic_Jigglypuff, 2, 2, 0),
    overworld_frame(gObjectEventPic_Jigglypuff, 2, 2, 0),
    overworld_frame(gObjectEventPic_Jigglypuff, 2, 2, 1),
    overworld_frame(gObjectEventPic_Jigglypuff, 2, 2, 1),
    overworld_frame(gObjectEventPic_Jigglypuff, 2, 2, 2),
    overworld_frame(gObjectEventPic_Jigglypuff, 2, 2, 2),
};

static const struct SpriteFrameImage sPicTable_Pidgey[] = {
    overworld_frame(gObjectEventPic_Pidgey, 2, 2, 0),
    overworld_frame(gObjectEventPic_Pidgey, 2, 2, 1),
    overworld_frame(gObjectEventPic_Pidgey, 2, 2, 2),
    overworld_frame(gObjectEventPic_Pidgey, 2, 2, 0),
    overworld_frame(gObjectEventPic_Pidgey, 2, 2, 0),
    overworld_frame(gObjectEventPic_Pidgey, 2, 2, 1),
    overworld_frame(gObjectEventPic_Pidgey, 2, 2, 1),
    overworld_frame(gObjectEventPic_Pidgey, 2, 2, 2),
    overworld_frame(gObjectEventPic_Pidgey, 2, 2, 2),
};

static const struct SpriteFrameImage sPicTable_Clefairy[] = {
    overworld_frame(gObjectEventPic_Clefairy, 2, 2, 0),
    overworld_frame(gObjectEventPic_Clefairy, 2, 2, 1),
    overworld_frame(gObjectEventPic_Clefairy, 2, 2, 2),
    overworld_frame(gObjectEventPic_Clefairy, 2, 2, 0),
    overworld_frame(gObjectEventPic_Clefairy, 2, 2, 0),
    overworld_frame(gObjectEventPic_Clefairy, 2, 2, 1),
    overworld_frame(gObjectEventPic_Clefairy, 2, 2, 1),
    overworld_frame(gObjectEventPic_Clefairy, 2, 2, 2),
    overworld_frame(gObjectEventPic_Clefairy, 2, 2, 2),
};

static const struct SpriteFrameImage sPicTable_Machoke[] = {
    overworld_frame(gObjectEventPic_Machoke, 2, 2, 0),
    overworld_frame(gObjectEventPic_Machoke, 2, 2, 1),
    overworld_frame(gObjectEventPic_Machoke, 2, 2, 2),
    overworld_frame(gObjectEventPic_Machoke, 2, 2, 0),
    overworld_frame(gObjectEventPic_Machoke, 2, 2, 0),
    overworld_frame(gObjectEventPic_Machoke, 2, 2, 1),
    overworld_frame(gObjectEventPic_Machoke, 2, 2, 1),
    overworld_frame(gObjectEventPic_Machoke, 2, 2, 2),
    overworld_frame(gObjectEventPic_Machoke, 2, 2, 2),
};

static const struct SpriteFrameImage sPicTable_Kabuto[] = {
    overworld_frame(gObjectEventPic_Kabuto, 2, 2, 0),
    overworld_frame(gObjectEventPic_Kabuto, 2, 2, 1),
    overworld_frame(gObjectEventPic_Kabuto, 2, 2, 2),
    overworld_frame(gObjectEventPic_Kabuto, 2, 2, 0),
    overworld_frame(gObjectEventPic_Kabuto, 2, 2, 0),
    overworld_frame(gObjectEventPic_Kabuto, 2, 2, 1),
    overworld_frame(gObjectEventPic_Kabuto, 2, 2, 1),
    overworld_frame(gObjectEventPic_Kabuto, 2, 2, 2),
    overworld_frame(gObjectEventPic_Kabuto, 2, 2, 2),
};

static const struct SpriteFrameImage sPicTable_Mom[] = {
    overworld_frame(gObjectEventPic_Mom, 2, 4, 0),
    overworld_frame(gObjectEventPic_Mom, 2, 4, 1),
    overworld_frame(gObjectEventPic_Mom, 2, 4, 2),
    overworld_frame(gObjectEventPic_Mom, 2, 4, 0),
    overworld_frame(gObjectEventPic_Mom, 2, 4, 0),
    overworld_frame(gObjectEventPic_Mom, 2, 4, 1),
    overworld_frame(gObjectEventPic_Mom, 2, 4, 1),
    overworld_frame(gObjectEventPic_Mom, 2, 4, 2),
    overworld_frame(gObjectEventPic_Mom, 2, 4, 2),
};
// ===== END src/data/object_events/object_event_pic_tables.h =====
// ===== BEGIN src/data/object_events/object_event_anims.h =====
static const union AnimCmd sAnim_StayStill[] = {
    ANIMCMD_FRAME(0, 8),
    ANIMCMD_FRAME(0, 8),
    ANIMCMD_FRAME(0, 8),
    ANIMCMD_FRAME(0, 8),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_QuintyPlumpFaceSouth[] = {
    ANIMCMD_FRAME(0, 16),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_QuintyPlumpFaceNorth[] = {
    ANIMCMD_FRAME(1, 16),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_QuintyPlumpFaceWest[] = {
    ANIMCMD_FRAME(2, 16),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_QuintyPlumpFaceEast[] = {
    ANIMCMD_FRAME(2, 16, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_QuintyPlumpGoSouth[] = {
    ANIMCMD_FRAME(3, 8),
    ANIMCMD_FRAME(0, 8),
    ANIMCMD_FRAME(3, 8, .hFlip = TRUE),
    ANIMCMD_FRAME(0, 8),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_QuintyPlumpGoNorth[] = {
    ANIMCMD_FRAME(4, 8),
    ANIMCMD_FRAME(1, 8),
    ANIMCMD_FRAME(4, 8, .hFlip = TRUE),
    ANIMCMD_FRAME(1, 8),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_QuintyPlumpGoWest[] = {
    ANIMCMD_FRAME(5, 8),
    ANIMCMD_FRAME(2, 8),
    ANIMCMD_FRAME(6, 8),
    ANIMCMD_FRAME(2, 8),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_QuintyPlumpGoEast[] = {
    ANIMCMD_FRAME(5, 8, .hFlip = TRUE),
    ANIMCMD_FRAME(2, 8, .hFlip = TRUE),
    ANIMCMD_FRAME(6, 8, .hFlip = TRUE),
    ANIMCMD_FRAME(2, 8, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_QuintyPlumpGoFastSouth[] = {
    ANIMCMD_FRAME(3, 4),
    ANIMCMD_FRAME(0, 4),
    ANIMCMD_FRAME(3, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(0, 4),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_QuintyPlumpGoFastNorth[] = {
    ANIMCMD_FRAME(4, 4),
    ANIMCMD_FRAME(1, 4),
    ANIMCMD_FRAME(4, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(1, 4),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_QuintyPlumpGoFastWest[] = {
    ANIMCMD_FRAME(5, 4),
    ANIMCMD_FRAME(2, 4),
    ANIMCMD_FRAME(6, 4),
    ANIMCMD_FRAME(2, 4),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_QuintyPlumpGoFastEast[] = {
    ANIMCMD_FRAME(5, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(2, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(6, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(2, 4, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_QuintyPlumpGoFasterSouth[] = {
    ANIMCMD_FRAME(3, 2),
    ANIMCMD_FRAME(0, 2),
    ANIMCMD_FRAME(3, 2, .hFlip = TRUE),
    ANIMCMD_FRAME(0, 2),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_QuintyPlumpGoFasterNorth[] = {
    ANIMCMD_FRAME(4, 2),
    ANIMCMD_FRAME(1, 2),
    ANIMCMD_FRAME(4, 2, .hFlip = TRUE),
    ANIMCMD_FRAME(1, 2),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_QuintyPlumpGoFasterWest[] = {
    ANIMCMD_FRAME(5, 2),
    ANIMCMD_FRAME(2, 2),
    ANIMCMD_FRAME(6, 2),
    ANIMCMD_FRAME(2, 2),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_QuintyPlumpGoFasterEast[] = {
    ANIMCMD_FRAME(5, 2, .hFlip = TRUE),
    ANIMCMD_FRAME(2, 2, .hFlip = TRUE),
    ANIMCMD_FRAME(6, 2, .hFlip = TRUE),
    ANIMCMD_FRAME(2, 2, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_QuintyPlumpGoFastestSouth[] = {
    ANIMCMD_FRAME(3, 1),
    ANIMCMD_FRAME(0, 1),
    ANIMCMD_FRAME(3, 1, .hFlip = TRUE),
    ANIMCMD_FRAME(0, 1),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_QuintyPlumpGoFastestNorth[] = {
    ANIMCMD_FRAME(4, 1),
    ANIMCMD_FRAME(1, 1),
    ANIMCMD_FRAME(4, 1, .hFlip = TRUE),
    ANIMCMD_FRAME(1, 1),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_QuintyPlumpGoFastestWest[] = {
    ANIMCMD_FRAME(5, 1),
    ANIMCMD_FRAME(2, 1),
    ANIMCMD_FRAME(6, 1),
    ANIMCMD_FRAME(2, 1),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_QuintyPlumpGoFastestEast[] = {
    ANIMCMD_FRAME(5, 1, .hFlip = TRUE),
    ANIMCMD_FRAME(2, 1, .hFlip = TRUE),
    ANIMCMD_FRAME(6, 1, .hFlip = TRUE),
    ANIMCMD_FRAME(2, 1, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_FaceSouth[] = {
    ANIMCMD_FRAME(0, 16),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_FaceNorth[] = {
    ANIMCMD_FRAME(1, 16),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_FaceWest[] = {
    ANIMCMD_FRAME(2, 16),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_FaceEast[] = {
    ANIMCMD_FRAME(2, 16, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_GoSouth[] = {
    ANIMCMD_FRAME(3, 8),
    ANIMCMD_FRAME(0, 8),
    ANIMCMD_FRAME(4, 8),
    ANIMCMD_FRAME(0, 8),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_GoNorth[] = {
    ANIMCMD_FRAME(5, 8),
    ANIMCMD_FRAME(1, 8),
    ANIMCMD_FRAME(6, 8),
    ANIMCMD_FRAME(1, 8),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_GoWest[] = {
    ANIMCMD_FRAME(7, 8),
    ANIMCMD_FRAME(2, 8),
    ANIMCMD_FRAME(8, 8),
    ANIMCMD_FRAME(2, 8),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_GoEast[] = {
    ANIMCMD_FRAME(7, 8, .hFlip = TRUE),
    ANIMCMD_FRAME(2, 8, .hFlip = TRUE),
    ANIMCMD_FRAME(8, 8, .hFlip = TRUE),
    ANIMCMD_FRAME(2, 8, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_GoFastSouth[] = {
    ANIMCMD_FRAME(3, 4),
    ANIMCMD_FRAME(0, 4),
    ANIMCMD_FRAME(4, 4),
    ANIMCMD_FRAME(0, 4),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_GoFastNorth[] = {
    ANIMCMD_FRAME(5, 4),
    ANIMCMD_FRAME(1, 4),
    ANIMCMD_FRAME(6, 4),
    ANIMCMD_FRAME(1, 4),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_GoFastWest[] = {
    ANIMCMD_FRAME(7, 4),
    ANIMCMD_FRAME(2, 4),
    ANIMCMD_FRAME(8, 4),
    ANIMCMD_FRAME(2, 4),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_GoFastEast[] = {
    ANIMCMD_FRAME(7, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(2, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(8, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(2, 4, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_GoFasterSouth[] = {
    ANIMCMD_FRAME(3, 2),
    ANIMCMD_FRAME(0, 2),
    ANIMCMD_FRAME(4, 2),
    ANIMCMD_FRAME(0, 2),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_GoFasterNorth[] = {
    ANIMCMD_FRAME(5, 2),
    ANIMCMD_FRAME(1, 2),
    ANIMCMD_FRAME(6, 2),
    ANIMCMD_FRAME(1, 2),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_GoFasterWest[] = {
    ANIMCMD_FRAME(7, 2),
    ANIMCMD_FRAME(2, 2),
    ANIMCMD_FRAME(8, 2),
    ANIMCMD_FRAME(2, 2),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_GoFasterEast[] = {
    ANIMCMD_FRAME(7, 2, .hFlip = TRUE),
    ANIMCMD_FRAME(2, 2, .hFlip = TRUE),
    ANIMCMD_FRAME(8, 2, .hFlip = TRUE),
    ANIMCMD_FRAME(2, 2, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_GoFastestSouth[] = {
    ANIMCMD_FRAME(3, 1),
    ANIMCMD_FRAME(0, 1),
    ANIMCMD_FRAME(4, 1),
    ANIMCMD_FRAME(0, 1),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_GoFastestNorth[] = {
    ANIMCMD_FRAME(5, 1),
    ANIMCMD_FRAME(1, 1),
    ANIMCMD_FRAME(6, 1),
    ANIMCMD_FRAME(1, 1),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_GoFastestWest[] = {
    ANIMCMD_FRAME(7, 1),
    ANIMCMD_FRAME(2, 1),
    ANIMCMD_FRAME(8, 1),
    ANIMCMD_FRAME(2, 1),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_GoFastestEast[] = {
    ANIMCMD_FRAME(7, 1, .hFlip = TRUE),
    ANIMCMD_FRAME(2, 1, .hFlip = TRUE),
    ANIMCMD_FRAME(8, 1, .hFlip = TRUE),
    ANIMCMD_FRAME(2, 1, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

// For indicating a VS Seeker rematch
static const union AnimCmd sAnim_RaiseHand[] = {
    ANIMCMD_FRAME(9, 0),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_HoOhFlapWings[] = {
    ANIMCMD_FRAME(3, 8),
    ANIMCMD_FRAME(4, 8),
    ANIMCMD_FRAME(3, 8),
    ANIMCMD_FRAME(4, 8),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_HoOhStayStill[] = {
    ANIMCMD_FRAME(3, 16),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_SurfFaceSouth[] = {
    ANIMCMD_FRAME(0, 60),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_SurfFaceNorth[] = {
    ANIMCMD_FRAME(1, 60),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_SurfFaceWest[] = {
    ANIMCMD_FRAME(2, 60),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_SurfFaceEast[] = {
    ANIMCMD_FRAME(2, 60, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_UnknownFaceSouth[] = {
    ANIMCMD_FRAME(0, 16),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_UnknownFaceNorth[] = {
    ANIMCMD_FRAME(1, 16),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_UnknownFaceWest[] = {
    ANIMCMD_FRAME(2, 16),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_UnknownFaceEast[] = {
    ANIMCMD_FRAME(2, 16, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_UnknownGoSouth[] = {
    ANIMCMD_FRAME(3, 4),
    ANIMCMD_FRAME(4, 4),
    ANIMCMD_FRAME(3, 4),
    ANIMCMD_FRAME(0, 4),
    ANIMCMD_FRAME(5, 4),
    ANIMCMD_FRAME(6, 4),
    ANIMCMD_FRAME(5, 4),
    ANIMCMD_FRAME(0, 4),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_UnknownGoNorth[] = {
    ANIMCMD_FRAME(7, 4),
    ANIMCMD_FRAME(8, 4),
    ANIMCMD_FRAME(7, 4),
    ANIMCMD_FRAME(1, 4),
    ANIMCMD_FRAME(9, 4),
    ANIMCMD_FRAME(10, 4),
    ANIMCMD_FRAME(9, 4),
    ANIMCMD_FRAME(1, 4),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_UnknownGoWest[] = {
    ANIMCMD_FRAME(11, 4),
    ANIMCMD_FRAME(12, 4),
    ANIMCMD_FRAME(11, 4),
    ANIMCMD_FRAME(2, 4),
    ANIMCMD_FRAME(13, 4),
    ANIMCMD_FRAME(14, 4),
    ANIMCMD_FRAME(13, 4),
    ANIMCMD_FRAME(2, 4),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_UnknownGoEast[] = {
    ANIMCMD_FRAME(11, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(12, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(11, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(2, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(13, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(14, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(13, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(2, 4, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_UnknownGoFastNorth[] = {
    ANIMCMD_FRAME(3, 2),
    ANIMCMD_FRAME(4, 2),
    ANIMCMD_FRAME(3, 2),
    ANIMCMD_FRAME(0, 2),
    ANIMCMD_FRAME(5, 2),
    ANIMCMD_FRAME(6, 2),
    ANIMCMD_FRAME(5, 2),
    ANIMCMD_FRAME(0, 2),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_UnknownGoFastSouth[] = {
    ANIMCMD_FRAME(7, 2),
    ANIMCMD_FRAME(8, 2),
    ANIMCMD_FRAME(7, 2),
    ANIMCMD_FRAME(1, 2),
    ANIMCMD_FRAME(9, 2),
    ANIMCMD_FRAME(10, 2),
    ANIMCMD_FRAME(9, 2),
    ANIMCMD_FRAME(1, 2),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_UnknownGoFastWest[] = {
    ANIMCMD_FRAME(11, 2),
    ANIMCMD_FRAME(12, 2),
    ANIMCMD_FRAME(11, 2),
    ANIMCMD_FRAME(2, 2),
    ANIMCMD_FRAME(13, 2),
    ANIMCMD_FRAME(14, 2),
    ANIMCMD_FRAME(13, 2),
    ANIMCMD_FRAME(2, 2),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_UnknownGoFastEast[] = {
    ANIMCMD_FRAME(11, 2, .hFlip = TRUE),
    ANIMCMD_FRAME(12, 2, .hFlip = TRUE),
    ANIMCMD_FRAME(11, 2, .hFlip = TRUE),
    ANIMCMD_FRAME(2, 2, .hFlip = TRUE),
    ANIMCMD_FRAME(13, 2, .hFlip = TRUE),
    ANIMCMD_FRAME(14, 2, .hFlip = TRUE),
    ANIMCMD_FRAME(13, 2, .hFlip = TRUE),
    ANIMCMD_FRAME(2, 2, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_UnknownGoFasterNorth[] = {
    ANIMCMD_FRAME(3, 1),
    ANIMCMD_FRAME(4, 1),
    ANIMCMD_FRAME(3, 1),
    ANIMCMD_FRAME(0, 1),
    ANIMCMD_FRAME(5, 1),
    ANIMCMD_FRAME(6, 1),
    ANIMCMD_FRAME(5, 1),
    ANIMCMD_FRAME(0, 1),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_UnknownGoFasterSouth[] = {
    ANIMCMD_FRAME(7, 1),
    ANIMCMD_FRAME(8, 1),
    ANIMCMD_FRAME(7, 1),
    ANIMCMD_FRAME(1, 1),
    ANIMCMD_FRAME(9, 1),
    ANIMCMD_FRAME(10, 1),
    ANIMCMD_FRAME(9, 1),
    ANIMCMD_FRAME(1, 1),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_UnknownGoFasterWest[] = {
    ANIMCMD_FRAME(11, 1),
    ANIMCMD_FRAME(12, 1),
    ANIMCMD_FRAME(11, 1),
    ANIMCMD_FRAME(2, 1),
    ANIMCMD_FRAME(13, 1),
    ANIMCMD_FRAME(14, 1),
    ANIMCMD_FRAME(13, 1),
    ANIMCMD_FRAME(2, 1),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_UnknownGoFasterEast[] = {
    ANIMCMD_FRAME(11, 1, .hFlip = TRUE),
    ANIMCMD_FRAME(12, 1, .hFlip = TRUE),
    ANIMCMD_FRAME(11, 1, .hFlip = TRUE),
    ANIMCMD_FRAME(2, 1, .hFlip = TRUE),
    ANIMCMD_FRAME(13, 1, .hFlip = TRUE),
    ANIMCMD_FRAME(14, 1, .hFlip = TRUE),
    ANIMCMD_FRAME(13, 1, .hFlip = TRUE),
    ANIMCMD_FRAME(2, 1, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_UnknownGoFastestNorth[] = {
    ANIMCMD_FRAME(3, 0),
    ANIMCMD_FRAME(4, 0),
    ANIMCMD_FRAME(3, 0),
    ANIMCMD_FRAME(0, 0),
    ANIMCMD_FRAME(5, 0),
    ANIMCMD_FRAME(6, 0),
    ANIMCMD_FRAME(5, 0),
    ANIMCMD_FRAME(0, 0),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_UnknownGoFastestSouth[] = {
    ANIMCMD_FRAME(7, 0),
    ANIMCMD_FRAME(8, 0),
    ANIMCMD_FRAME(7, 0),
    ANIMCMD_FRAME(1, 0),
    ANIMCMD_FRAME(9, 0),
    ANIMCMD_FRAME(10, 0),
    ANIMCMD_FRAME(9, 0),
    ANIMCMD_FRAME(1, 0),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_UnknownGoFastestWest[] = {
    ANIMCMD_FRAME(11, 0),
    ANIMCMD_FRAME(12, 0),
    ANIMCMD_FRAME(11, 0),
    ANIMCMD_FRAME(2, 0),
    ANIMCMD_FRAME(13, 0),
    ANIMCMD_FRAME(14, 0),
    ANIMCMD_FRAME(13, 0),
    ANIMCMD_FRAME(2, 0),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_UnknownGoFastestEast[] = {
    ANIMCMD_FRAME(11, 0, .hFlip = TRUE),
    ANIMCMD_FRAME(12, 0, .hFlip = TRUE),
    ANIMCMD_FRAME(11, 0, .hFlip = TRUE),
    ANIMCMD_FRAME(2, 0, .hFlip = TRUE),
    ANIMCMD_FRAME(13, 0, .hFlip = TRUE),
    ANIMCMD_FRAME(14, 0, .hFlip = TRUE),
    ANIMCMD_FRAME(13, 0, .hFlip = TRUE),
    ANIMCMD_FRAME(2, 0, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_SpinSouth[] = {
    ANIMCMD_FRAME(0, 2),
    ANIMCMD_FRAME(2, 2, .hFlip = TRUE),
    ANIMCMD_FRAME(1, 2),
    ANIMCMD_FRAME(2, 2),
    ANIMCMD_LOOP(1),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_SpinNorth[] = {
    ANIMCMD_FRAME(1, 2),
    ANIMCMD_FRAME(2, 2),
    ANIMCMD_FRAME(0, 2),
    ANIMCMD_FRAME(2, 2, .hFlip = TRUE),
    ANIMCMD_LOOP(1),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_SpinWest[] = {
    ANIMCMD_FRAME(2, 2, .hFlip = TRUE), // Starts by facing East?
    ANIMCMD_FRAME(1, 2),
    ANIMCMD_FRAME(2, 2),
    ANIMCMD_FRAME(0, 2),
    ANIMCMD_LOOP(1),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_SpinEast[] = {
    ANIMCMD_FRAME(2, 2), // Starts by facing West?
    ANIMCMD_FRAME(0, 2),
    ANIMCMD_FRAME(2, 2, .hFlip = TRUE),
    ANIMCMD_FRAME(1, 2),
    ANIMCMD_LOOP(1),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_ShakeHeadOrWalkInPlace[] = {
    ANIMCMD_FRAME(18, 16),
    ANIMCMD_FRAME(0, 16),
    ANIMCMD_FRAME(19, 16),
    ANIMCMD_FRAME(0, 32),
    ANIMCMD_LOOP(1),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_RunSouth[] = {
    ANIMCMD_FRAME(9, 5),
    ANIMCMD_FRAME(10, 3),
    ANIMCMD_FRAME(9, 5),
    ANIMCMD_FRAME(11, 3),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_RunNorth[] = {
    ANIMCMD_FRAME(12, 5),
    ANIMCMD_FRAME(13, 3),
    ANIMCMD_FRAME(12, 5),
    ANIMCMD_FRAME(14, 3),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_RunWest[] = {
    ANIMCMD_FRAME(15, 5),
    ANIMCMD_FRAME(16, 3),
    ANIMCMD_FRAME(15, 5),
    ANIMCMD_FRAME(17, 3),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_RunEast[] = {
    ANIMCMD_FRAME(15, 5, .hFlip = TRUE),
    ANIMCMD_FRAME(16, 3, .hFlip = TRUE),
    ANIMCMD_FRAME(15, 5, .hFlip = TRUE),
    ANIMCMD_FRAME(17, 3, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_FieldMove[] = {
    ANIMCMD_FRAME(0, 4),
    ANIMCMD_FRAME(1, 4),
    ANIMCMD_FRAME(2, 4),
    ANIMCMD_FRAME(3, 4),
    ANIMCMD_FRAME(4, 8),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_VSSeeker[] = {
    ANIMCMD_FRAME(0, 4),
    ANIMCMD_FRAME(1, 4),
    ANIMCMD_FRAME(5, 4),
    ANIMCMD_FRAME(6, 4),
    ANIMCMD_LOOP(0),
    ANIMCMD_FRAME(7, 4),
    ANIMCMD_FRAME(8, 4),
    ANIMCMD_LOOP(6),
    ANIMCMD_FRAME(6, 4),
    ANIMCMD_FRAME(1, 4),
    ANIMCMD_FRAME(0, 4),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_VSSeekerBike[] = {
    ANIMCMD_FRAME(0, 4),
    ANIMCMD_FRAME(1, 4),
    ANIMCMD_FRAME(2, 4),
    ANIMCMD_FRAME(3, 4),
    ANIMCMD_LOOP(0),
    ANIMCMD_FRAME(4, 4),
    ANIMCMD_FRAME(5, 4),
    ANIMCMD_LOOP(6),
    ANIMCMD_FRAME(3, 4),
    ANIMCMD_FRAME(2, 4),
    ANIMCMD_FRAME(1, 4),
    ANIMCMD_FRAME(0, 4),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_GetOnOffSurfSouth[] = {
    ANIMCMD_FRAME(9, 32),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_GetOnOffSurfNorth[] = {
    ANIMCMD_FRAME(10, 32),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_GetOnOffSurfWest[] = {
    ANIMCMD_FRAME(11, 32),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_GetOnOffSurfEast[] = {
    ANIMCMD_FRAME(11, 32, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_BunnyHopBackWheelSouth[] = {
    ANIMCMD_FRAME(15, 4),
    ANIMCMD_FRAME(16, 4),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_BunnyHopBackWheelNorth[] = {
    ANIMCMD_FRAME(19, 4),
    ANIMCMD_FRAME(20, 4),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_BunnyHopBackWheelWest[] = {
    ANIMCMD_FRAME(23, 4),
    ANIMCMD_FRAME(24, 4),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_BunnyHopBackWheelEast[] = {
    ANIMCMD_FRAME(23, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(24, 4, .hFlip = TRUE),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_BunnyHopFrontWheelSouth[] = {
    ANIMCMD_FRAME(17, 4),
    ANIMCMD_FRAME(18, 4),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_BunnyHopFrontWheelNorth[] = {
    ANIMCMD_FRAME(21, 4),
    ANIMCMD_FRAME(22, 4),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_BunnyHopFrontWheelWest[] = {
    ANIMCMD_FRAME(25, 4),
    ANIMCMD_FRAME(26, 4),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_BunnyHopFrontWheelEast[] = {
    ANIMCMD_FRAME(25, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(26, 4, .hFlip = TRUE),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_StandingWheelieBackWheelSouth[] = {
    ANIMCMD_FRAME(15, 4),
    ANIMCMD_FRAME(0, 4),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_StandingWheelieBackWheelNorth[] = {
    ANIMCMD_FRAME(19, 4),
    ANIMCMD_FRAME(1, 4),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_StandingWheelieBackWheelWest[] = {
    ANIMCMD_FRAME(23, 4),
    ANIMCMD_FRAME(2, 4),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_StandingWheelieBackWheelEast[] = {
    ANIMCMD_FRAME(23, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(2, 4, .hFlip = TRUE),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_StandingWheelieFrontWheelSouth[] = {
    ANIMCMD_FRAME(17, 4),
    ANIMCMD_FRAME(0, 4),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_StandingWheelieFrontWheelNorth[] = {
    ANIMCMD_FRAME(21, 4),
    ANIMCMD_FRAME(1, 4),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_StandingWheelieFrontWheelWest[] = {
    ANIMCMD_FRAME(25, 4),
    ANIMCMD_FRAME(2, 4),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_StandingWheelieFrontWheelEast[] = {
    ANIMCMD_FRAME(25, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(2, 4, .hFlip = TRUE),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_MovingWheelieSouth[] = {
    ANIMCMD_FRAME(27, 4),
    ANIMCMD_FRAME(16, 4),
    ANIMCMD_FRAME(28, 4),
    ANIMCMD_FRAME(16, 4),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_MovingWheelieNorth[] = {
    ANIMCMD_FRAME(29, 4),
    ANIMCMD_FRAME(20, 4),
    ANIMCMD_FRAME(30, 4),
    ANIMCMD_FRAME(20, 4),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_MovingWheelieWest[] = {
    ANIMCMD_FRAME(31, 4),
    ANIMCMD_FRAME(24, 4),
    ANIMCMD_FRAME(32, 4),
    ANIMCMD_FRAME(24, 4),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_MovingWheelieEast[] = {
    ANIMCMD_FRAME(31, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(24, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(32, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(24, 4, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_BerryTreeStage0[] = {
    ANIMCMD_FRAME(0, 32),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_BerryTreeStage1[] = {
    ANIMCMD_FRAME(1, 32),
    ANIMCMD_FRAME(2, 32),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_BerryTreeStage2[] = {
    ANIMCMD_FRAME(3, 48),
    ANIMCMD_FRAME(4, 48),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_BerryTreeStage3[] = {
    ANIMCMD_FRAME(5, 32),
    ANIMCMD_FRAME(5, 32),
    ANIMCMD_FRAME(6, 32),
    ANIMCMD_FRAME(6, 32),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_BerryTreeStage4[] = {
    ANIMCMD_FRAME(7, 48),
    ANIMCMD_FRAME(7, 48),
    ANIMCMD_FRAME(8, 48),
    ANIMCMD_FRAME(8, 48),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_NurseBow[] = {
    ANIMCMD_FRAME(0, 8),
    ANIMCMD_FRAME(9, 32),
    ANIMCMD_FRAME(0, 8),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_RockBreak[] = {
    ANIMCMD_FRAME(0, 8),
    ANIMCMD_FRAME(1, 8),
    ANIMCMD_FRAME(2, 8),
    ANIMCMD_FRAME(3, 8),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_TreeCut[] = {
    ANIMCMD_FRAME(0, 6),
    ANIMCMD_FRAME(1, 6),
    ANIMCMD_FRAME(2, 6),
    ANIMCMD_FRAME(3, 6),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_TakeOutRodSouth[] = {
    ANIMCMD_FRAME(8, 4),
    ANIMCMD_FRAME(9, 4),
    ANIMCMD_FRAME(10, 4),
    ANIMCMD_FRAME(11, 4),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_TakeOutRodNorth[] = {
    ANIMCMD_FRAME(4, 4),
    ANIMCMD_FRAME(5, 4),
    ANIMCMD_FRAME(6, 4),
    ANIMCMD_FRAME(7, 4),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_TakeOutRodWest[] = {
    ANIMCMD_FRAME(0, 4),
    ANIMCMD_FRAME(1, 4),
    ANIMCMD_FRAME(2, 4),
    ANIMCMD_FRAME(3, 4),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_TakeOutRodEast[] = {
    ANIMCMD_FRAME(0, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(1, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(2, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(3, 4, .hFlip = TRUE),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_PutAwayRodSouth[] = {
    ANIMCMD_FRAME(11, 4),
    ANIMCMD_FRAME(10, 6),
    ANIMCMD_FRAME(9, 6),
    ANIMCMD_FRAME(8, 6),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_PutAwayRodNorth[] = {
    ANIMCMD_FRAME(7, 4),
    ANIMCMD_FRAME(6, 6),
    ANIMCMD_FRAME(5, 6),
    ANIMCMD_FRAME(4, 6),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_PutAwayRodWest[] = {
    ANIMCMD_FRAME(3, 4),
    ANIMCMD_FRAME(2, 4),
    ANIMCMD_FRAME(1, 4),
    ANIMCMD_FRAME(0, 4),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_PutAwayRodEast[] = {
    ANIMCMD_FRAME(3, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(2, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(1, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(0, 4, .hFlip = TRUE),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_HookedPokemonSouth[] = {
    ANIMCMD_FRAME(10, 6),
    ANIMCMD_FRAME(11, 6),
    ANIMCMD_LOOP(1),
    ANIMCMD_FRAME(11, 30),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_HookedPokemonNorth[] = {
    ANIMCMD_FRAME(6, 6),
    ANIMCMD_FRAME(7, 6),
    ANIMCMD_LOOP(1),
    ANIMCMD_FRAME(7, 30),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_HookedPokemonWest[] = {
    ANIMCMD_FRAME(2, 6),
    ANIMCMD_FRAME(3, 6),
    ANIMCMD_LOOP(1),
    ANIMCMD_FRAME(3, 30),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_HookedPokemonEast[] = {
    ANIMCMD_FRAME(2, 6, .hFlip = TRUE),
    ANIMCMD_FRAME(3, 6, .hFlip = TRUE),
    ANIMCMD_LOOP(1),
    ANIMCMD_FRAME(3, 30, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

// Unused
static const union AffineAnimCmd sAffineAnim_KyogreGroudon_GoSouthStart[] = {
    AFFINEANIMCMD_FRAME(0, 0, 1, 1),
    AFFINEANIMCMD_FRAME(0, 0, 0, 1),
    AFFINEANIMCMD_FRAME(0, 0, 0, 1),
    AFFINEANIMCMD_FRAME(0, 0, 0, 1),
    AFFINEANIMCMD_LOOP(7),
    AFFINEANIMCMD_JUMP(0),
};

// Unused
static const union AffineAnimCmd sAffineAnim_KyogreGroudon_GoSouth[] = {
    AFFINEANIMCMD_FRAME(0, 0, -1, 1),
    AFFINEANIMCMD_FRAME(0, 0, 0, 1),
    AFFINEANIMCMD_LOOP(15),
    AFFINEANIMCMD_FRAME(0, 0, 1, 1),
    AFFINEANIMCMD_FRAME(0, 0, 0, 1),
    AFFINEANIMCMD_LOOP(15),
    AFFINEANIMCMD_JUMP(0),
};

static const union AnimCmd *const sAnimTable_Inanimate[] = {
    [ANIM_STAY_STILL] = sAnim_StayStill
};

// Leftover from Ruby/Sapphire
static const union AnimCmd *const sAnimTable_QuintyPlump[] = {
    [ANIM_STD_FACE_SOUTH] = sAnim_QuintyPlumpFaceSouth,
    [ANIM_STD_FACE_NORTH] = sAnim_QuintyPlumpFaceNorth,
    [ANIM_STD_FACE_WEST] = sAnim_QuintyPlumpFaceWest,
    [ANIM_STD_FACE_EAST] = sAnim_QuintyPlumpFaceEast,
    [ANIM_STD_GO_SOUTH] = sAnim_QuintyPlumpGoSouth,
    [ANIM_STD_GO_NORTH] = sAnim_QuintyPlumpGoNorth,
    [ANIM_STD_GO_WEST] = sAnim_QuintyPlumpGoWest,
    [ANIM_STD_GO_EAST] = sAnim_QuintyPlumpGoEast,
    [ANIM_STD_GO_FAST_SOUTH] = sAnim_QuintyPlumpGoFastSouth,
    [ANIM_STD_GO_FAST_NORTH] = sAnim_QuintyPlumpGoFastNorth,
    [ANIM_STD_GO_FAST_WEST] = sAnim_QuintyPlumpGoFastWest,
    [ANIM_STD_GO_FAST_EAST] = sAnim_QuintyPlumpGoFastEast,
    [ANIM_STD_GO_FASTER_SOUTH] = sAnim_QuintyPlumpGoFasterSouth,
    [ANIM_STD_GO_FASTER_NORTH] = sAnim_QuintyPlumpGoFasterNorth,
    [ANIM_STD_GO_FASTER_WEST] = sAnim_QuintyPlumpGoFasterWest,
    [ANIM_STD_GO_FASTER_EAST] = sAnim_QuintyPlumpGoFasterEast,
    [ANIM_STD_GO_FASTEST_SOUTH] = sAnim_QuintyPlumpGoFastestSouth,
    [ANIM_STD_GO_FASTEST_NORTH] = sAnim_QuintyPlumpGoFastestNorth,
    [ANIM_STD_GO_FASTEST_WEST] = sAnim_QuintyPlumpGoFastestWest,
    [ANIM_STD_GO_FASTEST_EAST] = sAnim_QuintyPlumpGoFastestEast,
};

static const union AnimCmd *const sAnimTable_Standard[] = {
    [ANIM_STD_FACE_SOUTH] = sAnim_FaceSouth,
    [ANIM_STD_FACE_NORTH] = sAnim_FaceNorth,
    [ANIM_STD_FACE_WEST] = sAnim_FaceWest,
    [ANIM_STD_FACE_EAST] = sAnim_FaceEast,
    [ANIM_STD_GO_SOUTH] = sAnim_GoSouth,
    [ANIM_STD_GO_NORTH] = sAnim_GoNorth,
    [ANIM_STD_GO_WEST] = sAnim_GoWest,
    [ANIM_STD_GO_EAST] = sAnim_GoEast,
    [ANIM_STD_GO_FAST_SOUTH] = sAnim_GoFastSouth,
    [ANIM_STD_GO_FAST_NORTH] = sAnim_GoFastNorth,
    [ANIM_STD_GO_FAST_WEST] = sAnim_GoFastWest,
    [ANIM_STD_GO_FAST_EAST] = sAnim_GoFastEast,
    [ANIM_STD_GO_FASTER_SOUTH] = sAnim_GoFasterSouth,
    [ANIM_STD_GO_FASTER_NORTH] = sAnim_GoFasterNorth,
    [ANIM_STD_GO_FASTER_WEST] = sAnim_GoFasterWest,
    [ANIM_STD_GO_FASTER_EAST] = sAnim_GoFasterEast,
    [ANIM_STD_GO_FASTEST_SOUTH] = sAnim_GoFastestSouth,
    [ANIM_STD_GO_FASTEST_NORTH] = sAnim_GoFastestNorth,
    [ANIM_STD_GO_FASTEST_WEST] = sAnim_GoFastestWest,
    [ANIM_STD_GO_FASTEST_EAST] = sAnim_GoFastestEast,
    [ANIM_RAISE_HAND] = sAnim_RaiseHand,
};

static const union AnimCmd *const sAnimTable_HoOh[] = {
    [ANIM_STD_FACE_SOUTH] = sAnim_FaceSouth,
    [ANIM_STD_FACE_NORTH] = sAnim_FaceNorth,
    [ANIM_STD_FACE_WEST] = sAnim_FaceWest,
    [ANIM_STD_FACE_EAST] = sAnim_FaceEast,
    [ANIM_STD_GO_SOUTH] = sAnim_HoOhFlapWings,
    [ANIM_STD_GO_NORTH] = sAnim_HoOhStayStill,
    [ANIM_STD_GO_WEST] = sAnim_GoWest,
    [ANIM_STD_GO_EAST] = sAnim_GoEast,
    [ANIM_STD_GO_FAST_SOUTH] = sAnim_GoFastSouth,
    [ANIM_STD_GO_FAST_NORTH] = sAnim_GoFastNorth,
    [ANIM_STD_GO_FAST_WEST] = sAnim_GoFastWest,
    [ANIM_STD_GO_FAST_EAST] = sAnim_GoFastEast,
    [ANIM_STD_GO_FASTER_SOUTH] = sAnim_GoFasterSouth,
    [ANIM_STD_GO_FASTER_NORTH] = sAnim_GoFasterNorth,
    [ANIM_STD_GO_FASTER_WEST] = sAnim_GoFasterWest,
    [ANIM_STD_GO_FASTER_EAST] = sAnim_GoFasterEast,
    [ANIM_STD_GO_FASTEST_SOUTH] = sAnim_GoFastestSouth,
    [ANIM_STD_GO_FASTEST_NORTH] = sAnim_GoFastestNorth,
    [ANIM_STD_GO_FASTEST_WEST] = sAnim_GoFastestWest,
    [ANIM_STD_GO_FASTEST_EAST] = sAnim_GoFastestEast,
    [ANIM_RAISE_HAND] = sAnim_RaiseHand,
};

static const union AnimCmd *const sAnimTable_Unknown[] = {
    [ANIM_STD_FACE_SOUTH] = sAnim_UnknownFaceSouth,
    [ANIM_STD_FACE_NORTH] = sAnim_UnknownFaceNorth,
    [ANIM_STD_FACE_WEST] = sAnim_UnknownFaceWest,
    [ANIM_STD_FACE_EAST] = sAnim_UnknownFaceEast,
    [ANIM_STD_GO_SOUTH] = sAnim_UnknownGoSouth,
    [ANIM_STD_GO_NORTH] = sAnim_UnknownGoNorth,
    [ANIM_STD_GO_WEST] = sAnim_UnknownGoWest,
    [ANIM_STD_GO_EAST] = sAnim_UnknownGoEast,
    [ANIM_STD_GO_FAST_SOUTH] = sAnim_UnknownGoFastNorth,
    [ANIM_STD_GO_FAST_NORTH] = sAnim_UnknownGoFastSouth,
    [ANIM_STD_GO_FAST_WEST] = sAnim_UnknownGoFastWest,
    [ANIM_STD_GO_FAST_EAST] = sAnim_UnknownGoFastEast,
    [ANIM_STD_GO_FASTER_SOUTH] = sAnim_UnknownGoFasterNorth,
    [ANIM_STD_GO_FASTER_NORTH] = sAnim_UnknownGoFasterSouth,
    [ANIM_STD_GO_FASTER_WEST] = sAnim_UnknownGoFasterWest,
    [ANIM_STD_GO_FASTER_EAST] = sAnim_UnknownGoFasterEast,
    [ANIM_STD_GO_FASTEST_SOUTH] = sAnim_UnknownGoFastestNorth,
    [ANIM_STD_GO_FASTEST_NORTH] = sAnim_UnknownGoFastestSouth,
    [ANIM_STD_GO_FASTEST_WEST] = sAnim_UnknownGoFastestWest,
    [ANIM_STD_GO_FASTEST_EAST] = sAnim_UnknownGoFastestEast,
    [ANIM_RUN_SOUTH] = sAnim_RunSouth,
    [ANIM_RUN_NORTH] = sAnim_RunNorth,
    [ANIM_RUN_WEST] = sAnim_RunWest,
    [ANIM_RUN_EAST] = sAnim_RunEast,
};

static const union AnimCmd *const sAnimTable_RedGreenNormal[] = {
    [ANIM_STD_FACE_SOUTH] = sAnim_FaceSouth,
    [ANIM_STD_FACE_NORTH] = sAnim_FaceNorth,
    [ANIM_STD_FACE_WEST] = sAnim_FaceWest,
    [ANIM_STD_FACE_EAST] = sAnim_FaceEast,
    [ANIM_STD_GO_SOUTH] = sAnim_GoSouth,
    [ANIM_STD_GO_NORTH] = sAnim_GoNorth,
    [ANIM_STD_GO_WEST] = sAnim_GoWest,
    [ANIM_STD_GO_EAST] = sAnim_GoEast,
    [ANIM_STD_GO_FAST_SOUTH] = sAnim_GoFastSouth,
    [ANIM_STD_GO_FAST_NORTH] = sAnim_GoFastNorth,
    [ANIM_STD_GO_FAST_WEST] = sAnim_GoFastWest,
    [ANIM_STD_GO_FAST_EAST] = sAnim_GoFastEast,
    [ANIM_STD_GO_FASTER_SOUTH] = sAnim_GoFasterSouth,
    [ANIM_STD_GO_FASTER_NORTH] = sAnim_GoFasterNorth,
    [ANIM_STD_GO_FASTER_WEST] = sAnim_GoFasterWest,
    [ANIM_STD_GO_FASTER_EAST] = sAnim_GoFasterEast,
    [ANIM_STD_GO_FASTEST_SOUTH] = sAnim_GoFastestSouth,
    [ANIM_STD_GO_FASTEST_NORTH] = sAnim_GoFastestNorth,
    [ANIM_STD_GO_FASTEST_WEST] = sAnim_GoFastestWest,
    [ANIM_STD_GO_FASTEST_EAST] = sAnim_GoFastestEast,
    [ANIM_RUN_SOUTH] = sAnim_RunSouth,
    [ANIM_RUN_NORTH] = sAnim_RunNorth,
    [ANIM_RUN_WEST] = sAnim_RunWest,
    [ANIM_RUN_EAST] = sAnim_RunEast,
    [ANIM_SPIN_SOUTH] = sAnim_SpinSouth,
    [ANIM_SPIN_NORTH] = sAnim_SpinNorth,
    [ANIM_SPIN_WEST] = sAnim_SpinWest,
    [ANIM_SPIN_EAST] = sAnim_SpinEast,
    [ANIM_SHAKE_HEAD_OR_WALK_IN_PLACE] = sAnim_ShakeHeadOrWalkInPlace,
};

// Leftover from Ruby/Sapphire
static const union AnimCmd *const sAnimTable_AcroBike[] = {
    [ANIM_STD_FACE_SOUTH] = sAnim_FaceSouth,
    [ANIM_STD_FACE_NORTH] = sAnim_FaceNorth,
    [ANIM_STD_FACE_WEST] = sAnim_FaceWest,
    [ANIM_STD_FACE_EAST] = sAnim_FaceEast,
    [ANIM_STD_GO_SOUTH] = sAnim_GoSouth,
    [ANIM_STD_GO_NORTH] = sAnim_GoNorth,
    [ANIM_STD_GO_WEST] = sAnim_GoWest,
    [ANIM_STD_GO_EAST] = sAnim_GoEast,
    [ANIM_STD_GO_FAST_SOUTH] = sAnim_GoFastSouth,
    [ANIM_STD_GO_FAST_NORTH] = sAnim_GoFastNorth,
    [ANIM_STD_GO_FAST_WEST] = sAnim_GoFastWest,
    [ANIM_STD_GO_FAST_EAST] = sAnim_GoFastEast,
    [ANIM_STD_GO_FASTER_SOUTH] = sAnim_GoFasterSouth,
    [ANIM_STD_GO_FASTER_NORTH] = sAnim_GoFasterNorth,
    [ANIM_STD_GO_FASTER_WEST] = sAnim_GoFasterWest,
    [ANIM_STD_GO_FASTER_EAST] = sAnim_GoFasterEast,
    [ANIM_STD_GO_FASTEST_SOUTH] = sAnim_GoFastestSouth,
    [ANIM_STD_GO_FASTEST_NORTH] = sAnim_GoFastestNorth,
    [ANIM_STD_GO_FASTEST_WEST] = sAnim_GoFastestWest,
    [ANIM_STD_GO_FASTEST_EAST] = sAnim_GoFastestEast,
    [ANIM_BUNNY_HOP_BACK_WHEEL_SOUTH] = sAnim_BunnyHopBackWheelSouth,
    [ANIM_BUNNY_HOP_BACK_WHEEL_NORTH] = sAnim_BunnyHopBackWheelNorth,
    [ANIM_BUNNY_HOP_BACK_WHEEL_WEST] = sAnim_BunnyHopBackWheelWest,
    [ANIM_BUNNY_HOP_BACK_WHEEL_EAST] = sAnim_BunnyHopBackWheelEast,
    [ANIM_BUNNY_HOP_FRONT_WHEEL_SOUTH] = sAnim_BunnyHopFrontWheelSouth,
    [ANIM_BUNNY_HOP_FRONT_WHEEL_NORTH] = sAnim_BunnyHopFrontWheelNorth,
    [ANIM_BUNNY_HOP_FRONT_WHEEL_WEST] = sAnim_BunnyHopFrontWheelWest,
    [ANIM_BUNNY_HOP_FRONT_WHEEL_EAST] = sAnim_BunnyHopFrontWheelEast,
    [ANIM_STANDING_WHEELIE_BACK_WHEEL_SOUTH] = sAnim_StandingWheelieBackWheelSouth,
    [ANIM_STANDING_WHEELIE_BACK_WHEEL_NORTH] = sAnim_StandingWheelieBackWheelNorth,
    [ANIM_STANDING_WHEELIE_BACK_WHEEL_WEST] = sAnim_StandingWheelieBackWheelWest,
    [ANIM_STANDING_WHEELIE_BACK_WHEEL_EAST] = sAnim_StandingWheelieBackWheelEast,
    [ANIM_STANDING_WHEELIE_FRONT_WHEEL_SOUTH] = sAnim_StandingWheelieFrontWheelSouth,
    [ANIM_STANDING_WHEELIE_FRONT_WHEEL_NORTH] = sAnim_StandingWheelieFrontWheelNorth,
    [ANIM_STANDING_WHEELIE_FRONT_WHEEL_WEST] = sAnim_StandingWheelieFrontWheelWest,
    [ANIM_STANDING_WHEELIE_FRONT_WHEEL_EAST] = sAnim_StandingWheelieFrontWheelEast,
    [ANIM_MOVING_WHEELIE_SOUTH] = sAnim_MovingWheelieSouth,
    [ANIM_MOVING_WHEELIE_NORTH] = sAnim_MovingWheelieNorth,
    [ANIM_MOVING_WHEELIE_WEST] = sAnim_MovingWheelieWest,
    [ANIM_MOVING_WHEELIE_EAST] = sAnim_MovingWheelieEast,
};

static const union AnimCmd *const sAnimTable_RedGreenSurf[] = {
    [ANIM_STD_FACE_SOUTH] = sAnim_SurfFaceSouth,
    [ANIM_STD_FACE_NORTH] = sAnim_SurfFaceNorth,
    [ANIM_STD_FACE_WEST] = sAnim_SurfFaceWest,
    [ANIM_STD_FACE_EAST] = sAnim_SurfFaceEast,
    [ANIM_STD_GO_SOUTH] = sAnim_SurfFaceSouth,
    [ANIM_STD_GO_NORTH] = sAnim_SurfFaceNorth,
    [ANIM_STD_GO_WEST] = sAnim_SurfFaceWest,
    [ANIM_STD_GO_EAST] = sAnim_SurfFaceEast,
    [ANIM_STD_GO_FAST_SOUTH] = sAnim_SurfFaceSouth,
    [ANIM_STD_GO_FAST_NORTH] = sAnim_SurfFaceNorth,
    [ANIM_STD_GO_FAST_WEST] = sAnim_SurfFaceWest,
    [ANIM_STD_GO_FAST_EAST] = sAnim_SurfFaceEast,
    [ANIM_STD_GO_FASTER_SOUTH] = sAnim_SurfFaceSouth,
    [ANIM_STD_GO_FASTER_NORTH] = sAnim_SurfFaceNorth,
    [ANIM_STD_GO_FASTER_WEST] = sAnim_SurfFaceWest,
    [ANIM_STD_GO_FASTER_EAST] = sAnim_SurfFaceEast,
    [ANIM_STD_GO_FASTEST_SOUTH] = sAnim_SurfFaceSouth,
    [ANIM_STD_GO_FASTEST_NORTH] = sAnim_SurfFaceNorth,
    [ANIM_STD_GO_FASTEST_WEST] = sAnim_SurfFaceWest,
    [ANIM_STD_GO_FASTEST_EAST] = sAnim_SurfFaceEast,
    [ANIM_GET_ON_OFF_POKEMON_SOUTH] = sAnim_GetOnOffSurfSouth,
    [ANIM_GET_ON_OFF_POKEMON_NORTH] = sAnim_GetOnOffSurfNorth,
    [ANIM_GET_ON_OFF_POKEMON_WEST] = sAnim_GetOnOffSurfWest,
    [ANIM_GET_ON_OFF_POKEMON_EAST] = sAnim_GetOnOffSurfEast,
};

static const union AnimCmd *const sAnimTable_Nurse[] = {
    [ANIM_STD_FACE_SOUTH] = sAnim_FaceSouth,
    [ANIM_STD_FACE_NORTH] = sAnim_FaceNorth,
    [ANIM_STD_FACE_WEST] = sAnim_FaceWest,
    [ANIM_STD_FACE_EAST] = sAnim_FaceEast,
    [ANIM_STD_GO_SOUTH] = sAnim_GoSouth,
    [ANIM_STD_GO_NORTH] = sAnim_GoNorth,
    [ANIM_STD_GO_WEST] = sAnim_GoWest,
    [ANIM_STD_GO_EAST] = sAnim_GoEast,
    [ANIM_STD_GO_FAST_SOUTH] = sAnim_GoFastSouth,
    [ANIM_STD_GO_FAST_NORTH] = sAnim_GoFastNorth,
    [ANIM_STD_GO_FAST_WEST] = sAnim_GoFastWest,
    [ANIM_STD_GO_FAST_EAST] = sAnim_GoFastEast,
    [ANIM_STD_GO_FASTER_SOUTH] = sAnim_GoFasterSouth,
    [ANIM_STD_GO_FASTER_NORTH] = sAnim_GoFasterNorth,
    [ANIM_STD_GO_FASTER_WEST]  = sAnim_GoFasterWest,
    [ANIM_STD_GO_FASTER_EAST]  = sAnim_GoFasterEast,
    [ANIM_STD_GO_FASTEST_SOUTH] = sAnim_GoFastestSouth,
    [ANIM_STD_GO_FASTEST_NORTH] = sAnim_GoFastestNorth,
    [ANIM_STD_GO_FASTEST_WEST] = sAnim_GoFastestWest,
    [ANIM_STD_GO_FASTEST_EAST] = sAnim_GoFastestEast,
    [ANIM_NURSE_BOW] = sAnim_NurseBow,
};

static const union AnimCmd *const sAnimTable_RedGreenFieldMove[] = {
    [ANIM_FIELD_MOVE] = sAnim_FieldMove,
};

static const union AnimCmd *const sAnimTable_RedGreenVSSeeker[] = {
    [ANIM_VS_SEEKER] = sAnim_VSSeeker,
};

static const union AnimCmd *const sAnimTable_RedGreenVSSeekerBike[] = {
    [ANIM_VS_SEEKER] = sAnim_VSSeekerBike,
};

// Unused
static const union AnimCmd *const sAnimTable_BerryTree[] = {
    sAnim_BerryTreeStage0,
    sAnim_BerryTreeStage1,
    sAnim_BerryTreeStage2,
    sAnim_BerryTreeStage3,
    sAnim_BerryTreeStage4,
};

static const union AnimCmd *const sAnimTable_RockSmashRock[] = {
    [ANIM_STAY_STILL] = sAnim_StayStill,
    [ANIM_REMOVE_OBSTACLE] = sAnim_RockBreak,
};

static const union AnimCmd *const sAnimTable_CutTree[] = {
    [ANIM_STAY_STILL] = sAnim_StayStill,
    [ANIM_REMOVE_OBSTACLE] = sAnim_TreeCut,
};

static const union AnimCmd *const sAnimTable_RedGreenFish[] = {
    [ANIM_TAKE_OUT_ROD_SOUTH] = sAnim_TakeOutRodSouth,
    [ANIM_TAKE_OUT_ROD_NORTH] = sAnim_TakeOutRodNorth,
    [ANIM_TAKE_OUT_ROD_WEST] = sAnim_TakeOutRodWest,
    [ANIM_TAKE_OUT_ROD_EAST] = sAnim_TakeOutRodEast,
    [ANIM_PUT_AWAY_ROD_SOUTH] = sAnim_PutAwayRodSouth,
    [ANIM_PUT_AWAY_ROD_NORTH] = sAnim_PutAwayRodNorth,
    [ANIM_PUT_AWAY_ROD_WEST] = sAnim_PutAwayRodWest,
    [ANIM_PUT_AWAY_ROD_EAST] = sAnim_PutAwayRodEast,
    [ANIM_HOOKED_POKEMON_SOUTH] = sAnim_HookedPokemonSouth,
    [ANIM_HOOKED_POKEMON_NORTH] = sAnim_HookedPokemonNorth,
    [ANIM_HOOKED_POKEMON_WEST] = sAnim_HookedPokemonWest,
    [ANIM_HOOKED_POKEMON_EAST] = sAnim_HookedPokemonEast,
};

static const struct StepAnimTable sStepAnimTables[] = {
    {
        .anims = sAnimTable_QuintyPlump,
        .animPos = {1, 3, 0, 2},
    },
    {
        .anims = sAnimTable_Standard,
        .animPos = {1, 3, 0, 2},
    },
    {
        .anims = sAnimTable_RedGreenNormal,
        .animPos = {1, 3, 0, 2},
    },
    {
        .anims = sAnimTable_AcroBike,
        .animPos = {1, 3, 0, 2},
    },
    {
        .anims = sAnimTable_RedGreenSurf,
        .animPos = {1, 3, 0, 2},
    },
    {
        .anims = sAnimTable_Nurse,
        .animPos = {1, 3, 0, 2},
    },
    {
        .anims = sAnimTable_RedGreenFish,
        .animPos = {1, 3, 0, 2},
    },
    {
        .anims = sAnimTable_Unknown,
        .animPos = {3, 7, 0, 4},
    },
    {}
};
// ===== END src/data/object_events/object_event_anims.h =====
// ===== BEGIN src/data/object_events/base_oam.h =====
const struct OamData gObjectEventBaseOam_8x8 = {
    .shape = SPRITE_SHAPE(8x8),
    .size = SPRITE_SIZE(8x8),
    .priority = 2
};

const struct OamData gObjectEventBaseOam_16x8 = {
    .shape = SPRITE_SHAPE(16x8),
    .size = SPRITE_SIZE(16x8),
    .priority = 2
};

const struct OamData gObjectEventBaseOam_16x16 = {
    .shape = SPRITE_SHAPE(16x16),
    .size = SPRITE_SIZE(16x16),
    .priority = 2
};

const struct OamData gObjectEventBaseOam_32x16 = {
    .shape = SPRITE_SHAPE(32x16),
    .size = SPRITE_SIZE(32x16),
    .priority = 2
};

const struct OamData gObjectEventBaseOam_32x8 = {
    .shape = SPRITE_SHAPE(32x8),
    .size = SPRITE_SIZE(32x8),
    .priority = 2
};

const struct OamData gObjectEventBaseOam_64x32 = {
    .shape = SPRITE_SHAPE(64x32),
    .size = SPRITE_SIZE(64x32),
    .priority = 2
};

const struct OamData gObjectEventBaseOam_16x32 = {
    .shape = SPRITE_SHAPE(16x32),
    .size = SPRITE_SIZE(16x32),
    .priority = 2
};

const struct OamData gObjectEventBaseOam_32x32 = {
    .shape = SPRITE_SHAPE(32x32),
    .size = SPRITE_SIZE(32x32),
    .priority = 2
};

const struct OamData gObjectEventBaseOam_64x64 = {
    .shape = SPRITE_SHAPE(64x64),
    .size = SPRITE_SIZE(64x64),
    .priority = 2
};
// ===== END src/data/object_events/base_oam.h =====
// ===== BEGIN src/data/object_events/object_event_subsprites.h =====
const struct Subsprite gObjectEventSpriteOamTable_16x16_0[] = {
    {
        .x = -8,
        .y = -8,
        .shape = SPRITE_SHAPE(16x16),
        .size = SPRITE_SIZE(16x16),
        .tileOffset = 0,
        .priority = 2
    }
};

const struct Subsprite gObjectEventSpriteOamTable_16x16_1[] = {
    {
        .x = -8,
        .y = -8,
        .shape = SPRITE_SHAPE(16x16),
        .size = SPRITE_SIZE(16x16),
        .tileOffset = 0,
        .priority = 1
    }
};

const struct Subsprite gObjectEventSpriteOamTable_16x16_2[] = {
    {
        .x = -8,
        .y = -8,
        .shape = SPRITE_SHAPE(16x8),
        .size = SPRITE_SIZE(16x8),
        .tileOffset = 0,
        .priority = 2
    },
    {
        .x = -8,
        .y = 0,
        .shape = SPRITE_SHAPE(16x8),
        .size = SPRITE_SIZE(16x8),
        .tileOffset = 2,
        .priority = 3
    }
};

const struct Subsprite gObjectEventSpriteOamTable_16x16_3[] = {
    {
        .x = -8,
        .y = -8,
        .shape = SPRITE_SHAPE(16x16),
        .size = SPRITE_SIZE(16x16),
        .tileOffset = 0,
        .priority = 2
    },
    {
        .x = -8,
        .y = -8,
        .shape = SPRITE_SHAPE(16x16),
        .size = SPRITE_SIZE(16x16),
        .tileOffset = 0,
        .priority = 3
    }
};

const struct Subsprite gObjectEventSpriteOamTable_16x16_4[] = {
    {
        .x = -8,
        .y = -8,
        .shape = SPRITE_SHAPE(16x16),
        .size = SPRITE_SIZE(16x16),
        .tileOffset = 0,
        .priority = 1
    },
    {
        .x = -8,
        .y = -8,
        .shape = SPRITE_SHAPE(16x16),
        .size = SPRITE_SIZE(16x16),
        .tileOffset = 0,
        .priority = 3
    }
};

const struct SubspriteTable gObjectEventSpriteOamTables_16x16[] = {
    {0, NULL},
    {1, gObjectEventSpriteOamTable_16x16_0},
    {1, gObjectEventSpriteOamTable_16x16_1},
    {2, gObjectEventSpriteOamTable_16x16_2},
    {2, gObjectEventSpriteOamTable_16x16_3},
    {2, gObjectEventSpriteOamTable_16x16_4},
};

const struct Subsprite gObjectEventSpriteOamTable_16x32_0[] = {
    {
        .x = -8,
        .y = -16,
        .shape = SPRITE_SHAPE(16x32),
        .size = SPRITE_SIZE(16x32),
        .tileOffset = 0,
        .priority = 2
    }
};

const struct Subsprite gObjectEventSpriteOamTable_16x32_1[] = {
    {
        .x = -8,
        .y = -16,
        .shape = SPRITE_SHAPE(16x32),
        .size = SPRITE_SIZE(16x32),
        .tileOffset = 0,
        .priority = 1
    }
};

const struct Subsprite gObjectEventSpriteOamTable_16x32_2[] = {
    {
        .x = -8,
        .y = -16,
        .shape = SPRITE_SHAPE(16x16),
        .size = SPRITE_SIZE(16x16),
        .tileOffset = 0,
        .priority = 2
    },
    {
        .x = -8,
        .y = 0,
        .shape = SPRITE_SHAPE(16x8),
        .size = SPRITE_SIZE(16x8),
        .tileOffset = 4,
        .priority = 2
    },
    {
        .x = -8,
        .y = 8,
        .shape = SPRITE_SHAPE(16x8),
        .size = SPRITE_SIZE(16x8),
        .tileOffset = 6,
        .priority = 3
    }
};

const struct Subsprite gObjectEventSpriteOamTable_16x32_3[] = {
    {
        .x = -8,
        .y = -16,
        .shape = SPRITE_SHAPE(16x16),
        .size = SPRITE_SIZE(16x16),
        .tileOffset = 0,
        .priority = 2
    },
    {
        .x = -8,
        .y = 0,
        .shape = SPRITE_SHAPE(16x16),
        .size = SPRITE_SIZE(16x16),
        .tileOffset = 4,
        .priority = 3
    }
};

const struct Subsprite gObjectEventSpriteOamTable_16x32_4[] = {
    {
        .x = -8,
        .y = -16,
        .shape = SPRITE_SHAPE(16x16),
        .size = SPRITE_SIZE(16x16),
        .tileOffset = 0,
        .priority = 1
    },
    {
        .x = -8,
        .y = 0,
        .shape = SPRITE_SHAPE(16x16),
        .size = SPRITE_SIZE(16x16),
        .tileOffset = 4,
        .priority = 3
    }
};

const struct SubspriteTable gObjectEventSpriteOamTables_16x32[] = {
    {0, NULL},
    {1, gObjectEventSpriteOamTable_16x32_0},
    {1, gObjectEventSpriteOamTable_16x32_1},
    {3, gObjectEventSpriteOamTable_16x32_2},
    {2, gObjectEventSpriteOamTable_16x32_3},
    {2, gObjectEventSpriteOamTable_16x32_4},
};

const struct Subsprite gObjectEventSpriteOamTable_32x32_0[] = {
    {
        .x = -16,
        .y = -16,
        .shape = SPRITE_SHAPE(32x32),
        .size = SPRITE_SIZE(32x32),
        .tileOffset = 0,
        .priority = 2
    }
};

const struct Subsprite gObjectEventSpriteOamTable_32x32_1[] = {
    {
        .x = -16,
        .y = -16,
        .shape = SPRITE_SHAPE(32x32),
        .size = SPRITE_SIZE(32x32),
        .tileOffset = 0,
        .priority = 1
    }
};

const struct Subsprite gObjectEventSpriteOamTable_32x32_2[] = {
    {
        .x = -16,
        .y = -16,
        .shape = SPRITE_SHAPE(32x16),
        .size = SPRITE_SIZE(32x16),
        .tileOffset = 0,
        .priority = 2
    },
    {
        .x = -16,
        .y = 0,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 8,
        .priority = 2
    },
    {
        .x = -16, 
        .y = 8, 
        .shape = SPRITE_SHAPE(32x8), 
        .size = SPRITE_SIZE(32x8), 
        .tileOffset = 12, 
        .priority = 3
    }
};

const struct Subsprite gObjectEventSpriteOamTable_32x32_3[] = {
    {
        .x = -16,
        .y = -16,
        .shape = SPRITE_SHAPE(32x16),
        .size = SPRITE_SIZE(32x16),
        .tileOffset = 0,
        .priority = 2
    },
    {
        .x = -16,
        .y = 0,
        .shape = SPRITE_SHAPE(32x16),
        .size = SPRITE_SIZE(32x16),
        .tileOffset = 8,
        .priority = 3
    }
};

const struct Subsprite gObjectEventSpriteOamTable_32x32_4[] = {
    {
        .x = -16,
        .y = -16,
        .shape = SPRITE_SHAPE(32x16),
        .size = SPRITE_SIZE(32x16),
        .tileOffset = 0,
        .priority = 1
    },
    {
        .x = -16,
        .y = 0,
        .shape = SPRITE_SHAPE(32x16),
        .size = SPRITE_SIZE(32x16),
        .tileOffset = 8,
        .priority = 3
    }
};

const struct SubspriteTable gObjectEventSpriteOamTables_32x32[] = {
    {0, NULL},
    {1, gObjectEventSpriteOamTable_32x32_0},
    {1, gObjectEventSpriteOamTable_32x32_1},
    {3, gObjectEventSpriteOamTable_32x32_2},
    {2, gObjectEventSpriteOamTable_32x32_3},
    {2, gObjectEventSpriteOamTable_32x32_4},
};

const struct Subsprite gObjectEventSpriteOamTable_48x48[] = {
    {
        .x = -24,
        .y = -24,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 0,
        .priority = 2
    },
    {
        .x = 8,
        .y = -24,
        .shape = SPRITE_SHAPE(16x8),
        .size = SPRITE_SIZE(16x8),
        .tileOffset = 4,
        .priority = 2
    },
    {
        .x = -24,
        .y = -16,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 6,
        .priority = 2
    },
    {
        .x = 8,
        .y = -16,
        .shape = SPRITE_SHAPE(16x8),
        .size = SPRITE_SIZE(16x8),
        .tileOffset = 10,
        .priority = 2
    },
    {
        .x = -24,
        .y = -8,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 12,
        .priority = 2
    },
    {
        .x = 8,
        .y = -8,
        .shape = SPRITE_SHAPE(16x8),
        .size = SPRITE_SIZE(16x8),
        .tileOffset = 16,
        .priority = 2
    },
    {
        .x = -24,
        .y = 0,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 18,
        .priority = 2
    },
    {
        .x = 8,
        .y = 0,
        .shape = SPRITE_SHAPE(16x8),
        .size = SPRITE_SIZE(16x8),
        .tileOffset = 22,
        .priority = 2
    },
    {
        .x = -24,
        .y = 8,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 24,
        .priority = 2
    },
    {
        .x = 8,
        .y = 8,
        .shape = SPRITE_SHAPE(16x8),
        .size = SPRITE_SIZE(16x8),
        .tileOffset = 28,
        .priority = 2
    },
    {
        .x = -24,
        .y = 16,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 30,
        .priority = 2
    },
    {
        .x = 8,
        .y = 16,
        .shape = SPRITE_SHAPE(16x8),
        .size = SPRITE_SIZE(16x8),
        .tileOffset = 34,
        .priority = 2
    }
};

// Unused. Used by the moving truck in RS
const struct SubspriteTable gObjectEventSpriteOamTables_48x48[] = {
    {12, gObjectEventSpriteOamTable_48x48},
    {12, gObjectEventSpriteOamTable_48x48},
    {12, gObjectEventSpriteOamTable_48x48},
    {12, gObjectEventSpriteOamTable_48x48},
    {12, gObjectEventSpriteOamTable_48x48},
    {12, gObjectEventSpriteOamTable_48x48},
};

const struct Subsprite gObjectEventSpriteOamTable_64x32_0[] = {
    {
        .x = -32,
        .y = -16,
        .shape = SPRITE_SHAPE(64x32),
        .size = SPRITE_SIZE(64x32),
        .tileOffset = 0,
        .priority = 2
    }
};

const struct Subsprite gObjectEventSpriteOamTable_64x32_1[] = {
    {
        .x = -32,
        .y = -16,
        .shape = SPRITE_SHAPE(64x32),
        .size = SPRITE_SIZE(64x32),
        .tileOffset = 0,
        .priority = 1
    }
};

const struct Subsprite gObjectEventSpriteOamTable_64x32_2[] = {
    {
        .x = -32,
        .y = -16,
        .shape = SPRITE_SHAPE(64x32),
        .size = SPRITE_SIZE(64x32),
        .tileOffset = 0,
        .priority = 2
    }
};

const struct Subsprite gObjectEventSpriteOamTable_64x32_3[] = {
    {
        .x = -32,
        .y = -16,
        .shape = SPRITE_SHAPE(64x32),
        .size = SPRITE_SIZE(64x32),
        .tileOffset = 0,
        .priority = 2
    }
};

// Unused
const struct SubspriteTable gObjectEventSpriteOamTables_64x32[] = {
    {0, NULL},
    {1, gObjectEventSpriteOamTable_64x32_0},
    {1, gObjectEventSpriteOamTable_64x32_1},
    {1, gObjectEventSpriteOamTable_64x32_2},
    {1, gObjectEventSpriteOamTable_64x32_3},
    {1, gObjectEventSpriteOamTable_64x32_3},
};

const struct Subsprite gObjectEventSpriteOamTable_64x64_0[] = {
    {
        .x = -32,
        .y = -32,
        .shape = SPRITE_SHAPE(64x64),
        .size = SPRITE_SIZE(64x64),
        .tileOffset = 0,
        .priority = 2
    }
};

const struct Subsprite gObjectEventSpriteOamTable_64x64_1[] = {
    {
        .x = -32,
        .y = -32,
        .shape = SPRITE_SHAPE(64x64),
        .size = SPRITE_SIZE(64x64),
        .tileOffset = 0,
        .priority = 1
    }
};

const struct Subsprite gObjectEventSpriteOamTable_64x64_2[] = {
    {
        .x = -32,
        .y = -32,
        .shape = SPRITE_SHAPE(64x64),
        .size = SPRITE_SIZE(64x64),
        .tileOffset = 0,
        .priority = 2
    }
};

const struct Subsprite gObjectEventSpriteOamTable_64x64_3[] = {
    {
        .x = -32,
        .y = -32,
        .shape = SPRITE_SHAPE(64x64),
        .size = SPRITE_SIZE(64x64),
        .tileOffset = 0,
        .priority = 2
    }
};

const struct SubspriteTable gObjectEventSpriteOamTables_64x64[] = {
    {0, NULL},
    {1, gObjectEventSpriteOamTable_64x64_0},
    {1, gObjectEventSpriteOamTable_64x64_1},
    {1, gObjectEventSpriteOamTable_64x64_2},
    {1, gObjectEventSpriteOamTable_64x64_3},
    {1, gObjectEventSpriteOamTable_64x64_3},
};

const struct Subsprite gObjectEventSpriteOamTable_96x40_0[] = {
    {
        .x = -48,
        .y = -20,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 0,
        .priority = 2
    },
    {
        .x = -16,
        .y = -20,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 4,
        .priority = 2
    },
    {
        .x = 16,
        .y = -20,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 8,
        .priority = 2
    },
    {
        .x = -48,
        .y = -12,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 12,
        .priority = 2
    },
    {
        .x = -16,
        .y = -12,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 16,
        .priority = 2
    },
    {
        .x = 16,
        .y = -12,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 20,
        .priority = 2
    },
    {
        .x = -48,
        .y = -4,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 24,
        .priority = 2
    },
    {
        .x = -16,
        .y = -4,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 28,
        .priority = 2
    },
    {
        .x = 16,
        .y = -4,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 32,
        .priority = 2
    },
    {
        .x = -48,
        .y = 4,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 36,
        .priority = 2
    },
    {
        .x = -16,
        .y = 4,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 40,
        .priority = 2
    },
    {
        .x = 16,
        .y = 4,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 44,
        .priority = 2
    },
    {
        .x = -48,
        .y = 12,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 48,
        .priority = 2
    },
    {
        .x = -16,
        .y = 12,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 52,
        .priority = 2
    },
    {
        .x = 16,
        .y = 12,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 56,
        .priority = 2
    }
};

const struct Subsprite gObjectEventSpriteOamTable_96x40_1[] = {
    {
        .x = -48,
        .y = -20,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 0,
        .priority = 1
    },
    {
        .x = -16,
        .y = -20,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 4,
        .priority = 1
    },
    {
        .x = 16,
        .y = -20,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 8,
        .priority = 1
    },
    {
        .x = -48,
        .y = -12,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 12,
        .priority = 1
    },
    {
        .x = -16,
        .y = -12,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 16,
        .priority = 1
    },
    {
        .x = 16,
        .y = -12,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 20,
        .priority = 1
    },
    {
        .x = -48,
        .y = -4,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 24,
        .priority = 1
    },
    {
        .x = -16,
        .y = -4,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 28,
        .priority = 1
    },
    {
        .x = 16,
        .y = -4,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 32,
        .priority = 1
    },
    {
        .x = -48,
        .y = 4,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 36,
        .priority = 1
    },
    {
        .x = -16,
        .y = 4,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 40,
        .priority = 1
    },
    {
        .x = 16,
        .y = 4,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 44,
        .priority = 1
    },
    {
        .x = -48,
        .y = 12,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 48,
        .priority = 1
    },
    {
        .x = -16,
        .y = 12,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 52,
        .priority = 1
    },
    {
        .x = 16,
        .y = 12,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 56,
        .priority = 1
    }
};

const struct Subsprite gObjectEventSpriteOamTable_96x40_2[] = {
    {
        .x = -48,
        .y = -20,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 0,
        .priority = 2
    },
    {
        .x = -16,
        .y = -20,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 4,
        .priority = 2
    },
    {
        .x = 16,
        .y = -20,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 8,
        .priority = 2
    },
    {
        .x = -48,
        .y = -12,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 12,
        .priority = 2
    },
    {
        .x = -16,
        .y = -12,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 16,
        .priority = 2
    },
    {
        .x = 16,
        .y = -12,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 20,
        .priority = 2
    },
    {
        .x = -48,
        .y = -4,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 24,
        .priority = 2
    },
    {
        .x = -16,
        .y = -4,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 28,
        .priority = 2
    },
    {
        .x = 16,
        .y = -4,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 32,
        .priority = 2
    },
    {
        .x = -48,
        .y = 4,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 36,
        .priority = 2
    },
    {
        .x = -16,
        .y = 4,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 40,
        .priority = 2
    },
    {
        .x = 16,
        .y = 4,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 44,
        .priority = 2
    },
    {
        .x = -48,
        .y = 12,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 48,
        .priority = 2
    },
    {
        .x = -16,
        .y = 12,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 52,
        .priority = 2
    },
    {
        .x = 16,
        .y = 12,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 56,
        .priority = 2
    }
};

const struct Subsprite gObjectEventSpriteOamTable_96x40_3[] = {
    {
        .x = -48,
        .y = -20,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 0,
        .priority = 1
    },
    {
        .x = -16,
        .y = -20,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 4,
        .priority = 1
    },
    {
        .x = 16,
        .y = -20,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 8,
        .priority = 1
    },
    {
        .x = -48,
        .y = -12,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 12,
        .priority = 1
    },
    {
        .x = -16,
        .y = -12,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 16,
        .priority = 1
    },
    {
        .x = 16,
        .y = -12,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 20,
        .priority = 1
    },
    {
        .x = -48,
        .y = -4,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 24,
        .priority = 2
    },
    {
        .x = -16,
        .y = -4,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 28,
        .priority = 2
    },
    {
        .x = 16,
        .y = -4,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 32,
        .priority = 2
    },
    {
        .x = -48,
        .y = 4,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 36,
        .priority = 2
    },
    {
        .x = -16,
        .y = 4,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 40,
        .priority = 2
    },
    {
        .x = 16,
        .y = 4,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 44,
        .priority = 2
    },
    {
        .x = -48,
        .y = 12,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 48,
        .priority = 2
    },
    {
        .x = -16,
        .y = 12,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 52,
        .priority = 2
    },
    {
        .x = 16,
        .y = 12,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 56,
        .priority = 2
    }
};

// Unused. Used by the SS Tidal in RS
const struct SubspriteTable gObjectEventSpriteOamTables_96x40[] = {
    {15, gObjectEventSpriteOamTable_96x40_0},
    {15, gObjectEventSpriteOamTable_96x40_0},
    {15, gObjectEventSpriteOamTable_96x40_1},
    {15, gObjectEventSpriteOamTable_96x40_2},
    {15, gObjectEventSpriteOamTable_96x40_3},
    {15, gObjectEventSpriteOamTable_96x40_3},
};

const struct Subsprite gObjectEventSpriteOamTable_128x64_0[] = {
    {
        .x = -32,
        .y = -16,
        .shape = SPRITE_SHAPE(64x32),
        .size = SPRITE_SIZE(64x32),
        .tileOffset = 0,
        .priority = 2
    },
    {
        .x = 32,
        .y = -16,
        .shape = SPRITE_SHAPE(64x32),
        .size = SPRITE_SIZE(64x32),
        .tileOffset = 32,
        .priority = 2
    },
    {
        .x = -32,
        .y = 16,
        .shape = SPRITE_SHAPE(64x32),
        .size = SPRITE_SIZE(64x32),
        .tileOffset = 64,
        .priority = 2
    },
    {
        .x = 32,
        .y = 16,
        .shape = SPRITE_SHAPE(64x32),
        .size = SPRITE_SIZE(64x32),
        .tileOffset = 96,
        .priority = 2
    }
};

const struct Subsprite gObjectEventSpriteOamTable_128x64_1[] = {
    {
        .x = -32,
        .y = -16,
        .shape = SPRITE_SHAPE(64x32),
        .size = SPRITE_SIZE(64x32),
        .tileOffset = 0,
        .priority = 1
    },
    {
        .x = 32,
        .y = -16,
        .shape = SPRITE_SHAPE(64x32),
        .size = SPRITE_SIZE(64x32),
        .tileOffset = 32,
        .priority = 1
    },
    {
        .x = -32,
        .y = 16,
        .shape = SPRITE_SHAPE(64x32),
        .size = SPRITE_SIZE(64x32),
        .tileOffset = 64,
        .priority = 1
    },
    {
        .x = 32,
        .y = 16,
        .shape = SPRITE_SHAPE(64x32),
        .size = SPRITE_SIZE(64x32),
        .tileOffset = 96,
        .priority = 1
    }
};

const struct Subsprite gObjectEventSpriteOamTable_128x64_2[] = {
    {
        .x = -32,
        .y = -16,
        .shape = SPRITE_SHAPE(64x32),
        .size = SPRITE_SIZE(64x32),
        .tileOffset = 0,
        .priority = 1
    },
    {
        .x = 32,
        .y = -16,
        .shape = SPRITE_SHAPE(64x32),
        .size = SPRITE_SIZE(64x32),
        .tileOffset = 32,
        .priority = 1
    },
    {
        .x = -32,
        .y = 16,
        .shape = SPRITE_SHAPE(64x32),
        .size = SPRITE_SIZE(64x32),
        .tileOffset = 64,
        .priority = 2
    },
    {
        .x = 32,
        .y = 16,
        .shape = SPRITE_SHAPE(64x32),
        .size = SPRITE_SIZE(64x32),
        .tileOffset = 96,
        .priority = 2
    }
};

const struct SubspriteTable gObjectEventSpriteOamTables_128x64[] = {
    {4, gObjectEventSpriteOamTable_128x64_0},
    {4, gObjectEventSpriteOamTable_128x64_0},
    {4, gObjectEventSpriteOamTable_128x64_1},
    {4, gObjectEventSpriteOamTable_128x64_2},
    {4, gObjectEventSpriteOamTable_128x64_2},
    {4, gObjectEventSpriteOamTable_128x64_2},
};

const struct Subsprite gObjectEventSpriteOamTable_88x32_0[] = {
    {
        .x = -48,
        .y = -20,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 0,
        .priority = 2
    },
    {
        .x = -16,
        .y = -20,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 4,
        .priority = 2
    },
    {
        .x = 16,
        .y = -20,
        .shape = SPRITE_SHAPE(16x8),
        .size = SPRITE_SIZE(16x8),
        .tileOffset = 8,
        .priority = 2
    },
    {
        .x = 32,
        .y = -20,
        .shape = SPRITE_SHAPE(8x8),
        .size = SPRITE_SIZE(8x8),
        .tileOffset = 10,
        .priority = 2
    },
    {
        .x = -48,
        .y = -12,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 11,
        .priority = 2
    },
    {
        .x = -16,
        .y = -12,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 15,
        .priority = 2
    },
    {
        .x = 16,
        .y = -12,
        .shape = SPRITE_SHAPE(16x8),
        .size = SPRITE_SIZE(16x8),
        .tileOffset = 19,
        .priority = 2
    },
    {
        .x = 32,
        .y = -12,
        .shape = SPRITE_SHAPE(8x8),
        .size = SPRITE_SIZE(8x8),
        .tileOffset = 21,
        .priority = 2
    },
    {
        .x = -48,
        .y = -4,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 22,
        .priority = 2
    },
    {
        .x = -16,
        .y = -4,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 26,
        .priority = 2
    },
    {
        .x = 16,
        .y = -4,
        .shape = SPRITE_SHAPE(16x8),
        .size = SPRITE_SIZE(16x8),
        .tileOffset = 30,
        .priority = 2
    },
    {
        .x = 32,
        .y = -4,
        .shape = SPRITE_SHAPE(8x8),
        .size = SPRITE_SIZE(8x8),
        .tileOffset = 32,
        .priority = 2
    },
    {
        .x = -48,
        .y = 4,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 33,
        .priority = 2
    },
    {
        .x = -16,
        .y = 4,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 37,
        .priority = 2
    },
    {
        .x = 16,
        .y = 4,
        .shape = SPRITE_SHAPE(16x8),
        .size = SPRITE_SIZE(16x8),
        .tileOffset = 41,
        .priority = 2
    },
    {
        .x = 32,
        .y = 4,
        .shape = SPRITE_SHAPE(8x8),
        .size = SPRITE_SIZE(8x8),
        .tileOffset = 43,
        .priority = 2
    }
};

const struct Subsprite gObjectEventSpriteOamTable_88x32_1[] = {
    {
        .x = -48,
        .y = -20,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 0,
        .priority = 1
    },
    {
        .x = -16,
        .y = -20,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 4,
        .priority = 1
    },
    {
        .x = 16,
        .y = -20,
        .shape = SPRITE_SHAPE(16x8),
        .size = SPRITE_SIZE(16x8),
        .tileOffset = 8,
        .priority = 1
    },
    {
        .x = 32,
        .y = -20,
        .shape = SPRITE_SHAPE(8x8),
        .size = SPRITE_SIZE(8x8),
        .tileOffset = 10,
        .priority = 1
    },
    {
        .x = -48,
        .y = -12,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 11,
        .priority = 1
    },
    {
        .x = -16,
        .y = -12,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 15,
        .priority = 1
    },
    {
        .x = 16,
        .y = -12,
        .shape = SPRITE_SHAPE(16x8),
        .size = SPRITE_SIZE(16x8),
        .tileOffset = 19,
        .priority = 1
    },
    {
        .x = 32,
        .y = -12,
        .shape = SPRITE_SHAPE(8x8),
        .size = SPRITE_SIZE(8x8),
        .tileOffset = 21,
        .priority = 1
    },
    {
        .x = -48,
        .y = -4,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 22,
        .priority = 1
    },
    {
        .x = -16,
        .y = -4,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 26,
        .priority = 1
    },
    {
        .x = 16,
        .y = -4,
        .shape = SPRITE_SHAPE(16x8),
        .size = SPRITE_SIZE(16x8),
        .tileOffset = 30,
        .priority = 1
    },
    {
        .x = 32,
        .y = -4,
        .shape = SPRITE_SHAPE(8x8),
        .size = SPRITE_SIZE(8x8),
        .tileOffset = 32,
        .priority = 1
    },
    {
        .x = -48,
        .y = 4,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 33,
        .priority = 1
    },
    {
        .x = -16,
        .y = 4,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 37,
        .priority = 1
    },
    {
        .x = 16,
        .y = 4,
        .shape = SPRITE_SHAPE(16x8),
        .size = SPRITE_SIZE(16x8),
        .tileOffset = 41,
        .priority = 1
    },
    {
        .x = 32,
        .y = 4,
        .shape = SPRITE_SHAPE(8x8),
        .size = SPRITE_SIZE(8x8),
        .tileOffset = 43,
        .priority = 1
    }
};

const struct Subsprite gObjectEventSpriteOamTable_88x32_2[] = {
    {
        .x = -48,
        .y = -20,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 0,
        .priority = 2
    },
    {
        .x = -16,
        .y = -20,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 4,
        .priority = 2
    },
    {
        .x = 16,
        .y = -20,
        .shape = SPRITE_SHAPE(16x8),
        .size = SPRITE_SIZE(16x8),
        .tileOffset = 8,
        .priority = 2
    },
    {
        .x = 32,
        .y = -20,
        .shape = SPRITE_SHAPE(8x8),
        .size = SPRITE_SIZE(8x8),
        .tileOffset = 10,
        .priority = 2
    },
    {
        .x = -48,
        .y = -12,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 11,
        .priority = 2
    },
    {
        .x = -16,
        .y = -12,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 15,
        .priority = 2
    },
    {
        .x = 16,
        .y = -12,
        .shape = SPRITE_SHAPE(16x8),
        .size = SPRITE_SIZE(16x8),
        .tileOffset = 19,
        .priority = 2
    },
    {
        .x = 32,
        .y = -12,
        .shape = SPRITE_SHAPE(8x8),
        .size = SPRITE_SIZE(8x8),
        .tileOffset = 21,
        .priority = 2
    },
    {
        .x = -48,
        .y = -4,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 22,
        .priority = 2
    },
    {
        .x = -16,
        .y = -4,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 26,
        .priority = 2
    },
    {
        .x = 16,
        .y = -4,
        .shape = SPRITE_SHAPE(16x8),
        .size = SPRITE_SIZE(16x8),
        .tileOffset = 30,
        .priority = 2
    },
    {
        .x = 32,
        .y = -4,
        .shape = SPRITE_SHAPE(8x8),
        .size = SPRITE_SIZE(8x8),
        .tileOffset = 32,
        .priority = 2
    },
    {
        .x = -48,
        .y = 4,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 33,
        .priority = 2
    },
    {
        .x = -16,
        .y = 4,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 37,
        .priority = 2
    },
    {
        .x = 16,
        .y = 4,
        .shape = SPRITE_SHAPE(16x8),
        .size = SPRITE_SIZE(16x8),
        .tileOffset = 41,
        .priority = 2
    },
    {
        .x = 32,
        .y = 4,
        .shape = SPRITE_SHAPE(8x8),
        .size = SPRITE_SIZE(8x8),
        .tileOffset = 43,
        .priority = 2
    }
};

const struct Subsprite gObjectEventSpriteOamTable_88x32_3[] = {
    {
        .x = -48,
        .y = -20,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 0,
        .priority = 1
    },
    {
        .x = -16,
        .y = -20,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 4,
        .priority = 1
    },
    {
        .x = 16,
        .y = -20,
        .shape = SPRITE_SHAPE(16x8),
        .size = SPRITE_SIZE(16x8),
        .tileOffset = 8,
        .priority = 1
    },
    {
        .x = 32,
        .y = -20,
        .shape = SPRITE_SHAPE(8x8),
        .size = SPRITE_SIZE(8x8),
        .tileOffset = 10,
        .priority = 1
    },
    {
        .x = -48,
        .y = -12,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 11,
        .priority = 1
    },
    {
        .x = -16,
        .y = -12,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 15,
        .priority = 1
    },
    {
        .x = 16,
        .y = -12,
        .shape = SPRITE_SHAPE(16x8),
        .size = SPRITE_SIZE(16x8),
        .tileOffset = 19,
        .priority = 1
    },
    {
        .x = 32,
        .y = -12,
        .shape = SPRITE_SHAPE(8x8),
        .size = SPRITE_SIZE(8x8),
        .tileOffset = 21,
        .priority = 1
    },
    {
        .x = -48,
        .y = -4,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 22,
        .priority = 2
    },
    {
        .x = -16,
        .y = -4,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 26,
        .priority = 2
    },
    {
        .x = 16,
        .y = -4,
        .shape = SPRITE_SHAPE(16x8),
        .size = SPRITE_SIZE(16x8),
        .tileOffset = 30,
        .priority = 2
    },
    {
        .x = 32,
        .y = -4,
        .shape = SPRITE_SHAPE(8x8),
        .size = SPRITE_SIZE(8x8),
        .tileOffset = 32,
        .priority = 2
    },
    {
        .x = -48,
        .y = 4,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 33,
        .priority = 2
    },
    {
        .x = -16,
        .y = 4,
        .shape = SPRITE_SHAPE(32x8),
        .size = SPRITE_SIZE(32x8),
        .tileOffset = 37,
        .priority = 2
    },
    {
        .x = 16,
        .y = 4,
        .shape = SPRITE_SHAPE(16x8),
        .size = SPRITE_SIZE(16x8),
        .tileOffset = 41,
        .priority = 2
    },
    {
        .x = 32,
        .y = 4,
        .shape = SPRITE_SHAPE(8x8),
        .size = SPRITE_SIZE(8x8),
        .tileOffset = 43,
        .priority = 2
    }
};

// Unused. Used by the submarine shadow in RS
const struct SubspriteTable gObjectEventSpriteOamTables_88x32[] = {
    {16, gObjectEventSpriteOamTable_88x32_0},
    {16, gObjectEventSpriteOamTable_88x32_0},
    {16, gObjectEventSpriteOamTable_88x32_1},
    {16, gObjectEventSpriteOamTable_88x32_2},
    {16, gObjectEventSpriteOamTable_88x32_3},
    {16, gObjectEventSpriteOamTable_88x32_3},
};
// ===== END src/data/object_events/object_event_subsprites.h =====
// ===== BEGIN src/data/object_events/object_event_graphics_info.h =====
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_RedNormal = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_PLAYER_RED,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_BRIDGE_REFLECTION,
    .size = 512,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_PLAYER,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x32,
    .subspriteTables = gObjectEventSpriteOamTables_16x32,
    .anims = sAnimTable_RedGreenNormal,
    .images = sPicTable_RedNormal,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_RedBike = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_PLAYER_RED,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_BRIDGE_REFLECTION,
    .size = 512,
    .width = 32,
    .height = 32,
    .paletteSlot = PALSLOT_PLAYER,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_BIKE_TIRE,
    .oam = &gObjectEventBaseOam_32x32,
    .subspriteTables = gObjectEventSpriteOamTables_32x32,
    .anims = sAnimTable_Standard,
    .images = sPicTable_RedBike,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_RedSurf = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_PLAYER_RED,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_PLAYER,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = TRUE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x32,
    .subspriteTables = gObjectEventSpriteOamTables_16x32,
    .anims = sAnimTable_RedGreenSurf,
    .images = sPicTable_RedSurf,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_RedFieldMove = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_PLAYER_RED,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_BRIDGE_REFLECTION,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_PLAYER,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x32,
    .subspriteTables = gObjectEventSpriteOamTables_16x32,
    .anims = sAnimTable_RedGreenFieldMove,
    .images = sPicTable_RedItem,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Policeman = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_BLUE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_1,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x32,
    .subspriteTables = gObjectEventSpriteOamTables_16x32,
    .anims = sAnimTable_Standard,
    .images = sPicTable_Policeman,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_RSBrendan = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x32,
    .subspriteTables = gObjectEventSpriteOamTables_16x32,
    .anims = sAnimTable_Standard,
    .images = sPicTable_RSBrendan,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_RSMay = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x32,
    .subspriteTables = gObjectEventSpriteOamTables_16x32,
    .anims = sAnimTable_Standard,
    .images = sPicTable_RSMay,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_LittleBoy = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x16,
    .subspriteTables = gObjectEventSpriteOamTables_16x16,
    .anims = sAnimTable_Standard,
    .images = sPicTable_LittleBoy,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_LittleGirl = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_PINK,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_2,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x16,
    .subspriteTables = gObjectEventSpriteOamTables_16x16,
    .anims = sAnimTable_Standard,
    .images = sPicTable_LittleGirl,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_SittingBoy = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x32,
    .subspriteTables = gObjectEventSpriteOamTables_16x32,
    .anims = sAnimTable_Standard,
    .images = sPicTable_SittingBoy,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Lass = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_BLUE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_1,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x32,
    .subspriteTables = gObjectEventSpriteOamTables_16x32,
    .anims = sAnimTable_Standard,
    .images = sPicTable_Lass,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Youngster = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_BLUE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_1,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x32,
    .subspriteTables = gObjectEventSpriteOamTables_16x32,
    .anims = sAnimTable_Standard,
    .images = sPicTable_Youngster,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Woman1 = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_GREEN,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_3,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x32,
    .subspriteTables = gObjectEventSpriteOamTables_16x32,
    .anims = sAnimTable_Standard,
    .images = sPicTable_Woman1,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Woman3 = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x32,
    .subspriteTables = gObjectEventSpriteOamTables_16x32,
    .anims = sAnimTable_Standard,
    .images = sPicTable_Woman3,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Boy = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_GREEN,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_3,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x32,
    .subspriteTables = gObjectEventSpriteOamTables_16x32,
    .anims = sAnimTable_Standard,
    .images = sPicTable_Boy,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_CrushGirl = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x32,
    .subspriteTables = gObjectEventSpriteOamTables_16x32,
    .anims = sAnimTable_Standard,
    .images = sPicTable_CrushGirl,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_BugCatcher = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_GREEN,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_3,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x32,
    .subspriteTables = gObjectEventSpriteOamTables_16x32,
    .anims = sAnimTable_Standard,
    .images = sPicTable_BugCatcher,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_FatMan = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x32,
    .subspriteTables = gObjectEventSpriteOamTables_16x32,
    .anims = sAnimTable_Standard,
    .images = sPicTable_FatMan,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_BaldingMan = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x32,
    .subspriteTables = gObjectEventSpriteOamTables_16x32,
    .anims = sAnimTable_Standard,
    .images = sPicTable_BaldingMan,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Woman2 = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x32,
    .subspriteTables = gObjectEventSpriteOamTables_16x32,
    .anims = sAnimTable_Standard,
    .images = sPicTable_Woman2,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_OldMan1 = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_PINK,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_2,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x32,
    .subspriteTables = gObjectEventSpriteOamTables_16x32,
    .anims = sAnimTable_Standard,
    .images = sPicTable_OldMan1,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_WorkerM = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x32,
    .subspriteTables = gObjectEventSpriteOamTables_16x32,
    .anims = sAnimTable_Standard,
    .images = sPicTable_WorkerM,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_WorkerF = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_GREEN,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_3,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x32,
    .subspriteTables = gObjectEventSpriteOamTables_16x32,
    .anims = sAnimTable_Standard,
    .images = sPicTable_WorkerF,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Beauty = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_BLUE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_1,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x32,
    .subspriteTables = gObjectEventSpriteOamTables_16x32,
    .anims = sAnimTable_Standard,
    .images = sPicTable_Beauty,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Chef = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x32,
    .subspriteTables = gObjectEventSpriteOamTables_16x32,
    .anims = sAnimTable_Standard,
    .images = sPicTable_Chef,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_OldMan2 = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x32,
    .subspriteTables = gObjectEventSpriteOamTables_16x32,
    .anims = sAnimTable_Standard,
    .images = sPicTable_OldMan2,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_OldWoman = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_PINK,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_2,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x32,
    .subspriteTables = gObjectEventSpriteOamTables_16x32,
    .anims = sAnimTable_Standard,
    .images = sPicTable_OldWoman,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Camper = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_GREEN,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_3,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x32,
    .subspriteTables = gObjectEventSpriteOamTables_16x32,
    .anims = sAnimTable_Standard,
    .images = sPicTable_Camper,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Picnicker = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_GREEN,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_3,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x32,
    .subspriteTables = gObjectEventSpriteOamTables_16x32,
    .anims = sAnimTable_Standard,
    .images = sPicTable_Picnicker,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_CooltrainerM = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_BLUE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_1,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x32,
    .subspriteTables = gObjectEventSpriteOamTables_16x32,
    .anims = sAnimTable_Standard,
    .images = sPicTable_CooltrainerM,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_CooltrainerF = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_BLUE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_1,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x32,
    .subspriteTables = gObjectEventSpriteOamTables_16x32,
    .anims = sAnimTable_Standard,
    .images = sPicTable_CooltrainerF,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_PokeManiac = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_PINK,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_2,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x32,
    .subspriteTables = gObjectEventSpriteOamTables_16x32,
    .anims = sAnimTable_Standard,
    .images = sPicTable_PokeManiac,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Channeler = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x32,
    .subspriteTables = gObjectEventSpriteOamTables_16x32,
    .anims = sAnimTable_Standard,
    .images = sPicTable_Channeler,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_RocketF = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x32,
    .subspriteTables = gObjectEventSpriteOamTables_16x32,
    .anims = sAnimTable_Standard,
    .images = sPicTable_RocketF,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_SwimmerMWater = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x32,
    .subspriteTables = gObjectEventSpriteOamTables_16x32,
    .anims = sAnimTable_Standard,
    .images = sPicTable_SwimmerMWater,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_SwimmerFWater = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_GREEN,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_3,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x32,
    .subspriteTables = gObjectEventSpriteOamTables_16x32,
    .anims = sAnimTable_Standard,
    .images = sPicTable_SwimmerFWater,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_SwimmerMLand = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x32,
    .subspriteTables = gObjectEventSpriteOamTables_16x32,
    .anims = sAnimTable_Standard,
    .images = sPicTable_SwimmerMLand,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_SwimmerFLand = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_BLUE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_1,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x32,
    .subspriteTables = gObjectEventSpriteOamTables_16x32,
    .anims = sAnimTable_Standard,
    .images = sPicTable_SwimmerFLand,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_BlackBelt = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x32,
    .subspriteTables = gObjectEventSpriteOamTables_16x32,
    .anims = sAnimTable_Standard,
    .images = sPicTable_BlackBelt,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Scientist = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x32,
    .subspriteTables = gObjectEventSpriteOamTables_16x32,
    .anims = sAnimTable_Standard,
    .images = sPicTable_Scientist,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Gentleman = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x32,
    .subspriteTables = gObjectEventSpriteOamTables_16x32,
    .anims = sAnimTable_Standard,
    .images = sPicTable_Gentleman,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Sailor = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_PINK,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_2,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x32,
    .subspriteTables = gObjectEventSpriteOamTables_16x32,
    .anims = sAnimTable_Standard,
    .images = sPicTable_Sailor,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Captain = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x32,
    .subspriteTables = gObjectEventSpriteOamTables_16x32,
    .anims = sAnimTable_Standard,
    .images = sPicTable_Captain,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Fisher = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x32,
    .subspriteTables = gObjectEventSpriteOamTables_16x32,
    .anims = sAnimTable_Standard,
    .images = sPicTable_Fisher,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_TeachyTVHost = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x32,
    .subspriteTables = gObjectEventSpriteOamTables_16x32,
    .anims = sAnimTable_Standard,
    .images = sPicTable_TeachyTVHost,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_UnusedWoman = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_PINK,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_2,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x32,
    .subspriteTables = gObjectEventSpriteOamTables_16x32,
    .anims = sAnimTable_Standard,
    .images = sPicTable_UnusedWoman,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_TuberF = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x16,
    .subspriteTables = gObjectEventSpriteOamTables_16x16,
    .anims = sAnimTable_Standard,
    .images = sPicTable_TuberF,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_TuberMWater = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_BLUE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_1,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x16,
    .subspriteTables = gObjectEventSpriteOamTables_16x16,
    .anims = sAnimTable_Standard,
    .images = sPicTable_TuberMWater,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_TuberMLand = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_BLUE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_1,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x16,
    .subspriteTables = gObjectEventSpriteOamTables_16x16,
    .anims = sAnimTable_Standard,
    .images = sPicTable_TuberMLand,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Hiker = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x32,
    .subspriteTables = gObjectEventSpriteOamTables_16x32,
    .anims = sAnimTable_Standard,
    .images = sPicTable_Hiker,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Biker = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_PINK,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 512,
    .width = 32,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_2,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_BIKE_TIRE,
    .oam = &gObjectEventBaseOam_32x32,
    .subspriteTables = gObjectEventSpriteOamTables_32x32,
    .anims = sAnimTable_Standard,
    .images = sPicTable_Biker,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_GymGuy = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_PINK,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_2,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_BIKE_TIRE,
    .oam = &gObjectEventBaseOam_16x32,
    .subspriteTables = gObjectEventSpriteOamTables_16x32,
    .anims = sAnimTable_Standard,
    .images = sPicTable_GymGuy,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Nurse = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_PINK,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_2,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x32,
    .subspriteTables = gObjectEventSpriteOamTables_16x32,
    .anims = sAnimTable_Nurse,
    .images = sPicTable_Nurse,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_UnusedMaleReceptionist = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x32,
    .subspriteTables = gObjectEventSpriteOamTables_16x32,
    .anims = sAnimTable_Standard,
    .images = sPicTable_UnusedMaleReceptionist,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_ItemBall = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_S,
    .inanimate = TRUE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_NONE,
    .oam = &gObjectEventBaseOam_16x16,
    .subspriteTables = gObjectEventSpriteOamTables_16x16,
    .anims = sAnimTable_Inanimate,
    .images = sPicTable_ItemBall,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_ProfOak = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x32,
    .subspriteTables = gObjectEventSpriteOamTables_16x32,
    .anims = sAnimTable_Standard,
    .images = sPicTable_ProfOak,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Man = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x32,
    .subspriteTables = gObjectEventSpriteOamTables_16x32,
    .anims = sAnimTable_Standard,
    .images = sPicTable_Man,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Rocker = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_BLUE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_1,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x32,
    .subspriteTables = gObjectEventSpriteOamTables_16x32,
    .anims = sAnimTable_Standard,
    .images = sPicTable_Rocker,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_MrFuji = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x32,
    .subspriteTables = gObjectEventSpriteOamTables_16x32,
    .anims = sAnimTable_Standard,
    .images = sPicTable_MrFuji,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Bruno = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x32,
    .subspriteTables = gObjectEventSpriteOamTables_16x32,
    .anims = sAnimTable_Standard,
    .images = sPicTable_Bruno,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_OldManLyingDown = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_PINK,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 512,
    .width = 32,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_2,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_32x32,
    .subspriteTables = gObjectEventSpriteOamTables_32x32,
    .anims = sAnimTable_Standard,
    .images = sPicTable_OldManLyingDown,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_CutTree = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_GREEN,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_3,
    .shadowSize = SHADOW_SIZE_S,
    .inanimate = TRUE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_NONE,
    .oam = &gObjectEventBaseOam_16x16,
    .subspriteTables = gObjectEventSpriteOamTables_16x16,
    .anims = sAnimTable_CutTree,
    .images = sPicTable_CutTree,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Clerk = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x32,
    .subspriteTables = gObjectEventSpriteOamTables_16x32,
    .anims = sAnimTable_Standard,
    .images = sPicTable_Clerk,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_MGDeliveryman = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_GREEN,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_3,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x32,
    .subspriteTables = gObjectEventSpriteOamTables_16x32,
    .anims = sAnimTable_Standard,
    .images = sPicTable_MGDeliveryman,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_TrainerTowerDude = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x32,
    .subspriteTables = gObjectEventSpriteOamTables_16x32,
    .anims = sAnimTable_Standard,
    .images = sPicTable_TrainerTowerDude,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_CableClubReceptionist = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x32,
    .subspriteTables = gObjectEventSpriteOamTables_16x32,
    .anims = sAnimTable_Standard,
    .images = sPicTable_CableClubReceptionist,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_UnionRoomReceptionist = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x32,
    .subspriteTables = gObjectEventSpriteOamTables_16x32,
    .anims = sAnimTable_Standard,
    .images = sPicTable_UnionRoomReceptionist,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_RockSmashRock = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_S,
    .inanimate = TRUE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_NONE,
    .oam = &gObjectEventBaseOam_16x16,
    .subspriteTables = gObjectEventSpriteOamTables_16x16,
    .anims = sAnimTable_RockSmashRock,
    .images = sPicTable_RockSmashRock,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_StrengthBoulder = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_S,
    .inanimate = TRUE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_NONE,
    .oam = &gObjectEventBaseOam_16x16,
    .subspriteTables = gObjectEventSpriteOamTables_16x16,
    .anims = sAnimTable_Inanimate,
    .images = sPicTable_StrengthBoulder,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_GreenNormal = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_PLAYER_GREEN,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_BRIDGE_REFLECTION,
    .size = 512,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_PLAYER,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x32,
    .subspriteTables = gObjectEventSpriteOamTables_16x32,
    .anims = sAnimTable_RedGreenNormal,
    .images = sPicTable_GreenNormal,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_GreenBike = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_PLAYER_GREEN,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_BRIDGE_REFLECTION,
    .size = 512,
    .width = 32,
    .height = 32,
    .paletteSlot = PALSLOT_PLAYER,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_BIKE_TIRE,
    .oam = &gObjectEventBaseOam_32x32,
    .subspriteTables = gObjectEventSpriteOamTables_32x32,
    .anims = sAnimTable_Standard,
    .images = sPicTable_GreenBike,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_GreenSurf = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_PLAYER_GREEN,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_PLAYER,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = TRUE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x32,
    .subspriteTables = gObjectEventSpriteOamTables_16x32,
    .anims = sAnimTable_RedGreenSurf,
    .images = sPicTable_GreenSurf,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_GreenFieldMove = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_PLAYER_GREEN,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_BRIDGE_REFLECTION,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_PLAYER,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x32,
    .subspriteTables = gObjectEventSpriteOamTables_16x32,
    .anims = sAnimTable_RedGreenFieldMove,
    .images = sPicTable_GreenItem,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_RedBikeAlt = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_PLAYER_RED,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_BRIDGE_REFLECTION,
    .size = 512,
    .width = 32,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_SPECIAL,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_BIKE_TIRE,
    .oam = &gObjectEventBaseOam_32x32,
    .subspriteTables = gObjectEventSpriteOamTables_32x32,
    .anims = sAnimTable_Standard,
    .images = sPicTable_RedBike,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_RocketM = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x32,
    .subspriteTables = gObjectEventSpriteOamTables_16x32,
    .anims = sAnimTable_Standard,
    .images = sPicTable_RocketM,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Celio = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x32,
    .subspriteTables = gObjectEventSpriteOamTables_16x32,
    .anims = sAnimTable_Standard,
    .images = sPicTable_Celio,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Agatha = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_PINK,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_2,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x32,
    .subspriteTables = gObjectEventSpriteOamTables_16x32,
    .anims = sAnimTable_Standard,
    .images = sPicTable_Agatha,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Brock = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_GREEN,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_3,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x32,
    .subspriteTables = gObjectEventSpriteOamTables_16x32,
    .anims = sAnimTable_Standard,
    .images = sPicTable_Brock,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Misty = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_BLUE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_1,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x32,
    .subspriteTables = gObjectEventSpriteOamTables_16x32,
    .anims = sAnimTable_Standard,
    .images = sPicTable_Misty,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_LtSurge = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_GREEN,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_3,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x32,
    .subspriteTables = gObjectEventSpriteOamTables_16x32,
    .anims = sAnimTable_Standard,
    .images = sPicTable_LtSurge,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Erika = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_BLUE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_1,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x32,
    .subspriteTables = gObjectEventSpriteOamTables_16x32,
    .anims = sAnimTable_Standard,
    .images = sPicTable_Erika,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Koga = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x32,
    .subspriteTables = gObjectEventSpriteOamTables_16x32,
    .anims = sAnimTable_Standard,
    .images = sPicTable_Koga,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Giovanni = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x32,
    .subspriteTables = gObjectEventSpriteOamTables_16x32,
    .anims = sAnimTable_Standard,
    .images = sPicTable_Giovanni,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Blaine = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_PINK,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_2,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x32,
    .subspriteTables = gObjectEventSpriteOamTables_16x32,
    .anims = sAnimTable_Standard,
    .images = sPicTable_Blaine,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Sabrina = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_BLUE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_1,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x32,
    .subspriteTables = gObjectEventSpriteOamTables_16x32,
    .anims = sAnimTable_Standard,
    .images = sPicTable_Sabrina,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Bill = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_BLUE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_1,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x32,
    .subspriteTables = gObjectEventSpriteOamTables_16x32,
    .anims = sAnimTable_Standard,
    .images = sPicTable_Bill,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Daisy = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_GREEN,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_3,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x32,
    .subspriteTables = gObjectEventSpriteOamTables_16x32,
    .anims = sAnimTable_Standard,
    .images = sPicTable_Daisy,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Lorelei = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x32,
    .subspriteTables = gObjectEventSpriteOamTables_16x32,
    .anims = sAnimTable_Standard,
    .images = sPicTable_Lorelei,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Lance = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x32,
    .subspriteTables = gObjectEventSpriteOamTables_16x32,
    .anims = sAnimTable_Standard,
    .images = sPicTable_Lance,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Blue = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_GREEN,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_3,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x32,
    .subspriteTables = gObjectEventSpriteOamTables_16x32,
    .anims = sAnimTable_Standard,
    .images = sPicTable_Blue,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_RedFish = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_PLAYER_RED,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_BRIDGE_REFLECTION,
    .size = 512,
    .width = 32,
    .height = 32,
    .paletteSlot = PALSLOT_PLAYER,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_32x32,
    .subspriteTables = gObjectEventSpriteOamTables_32x32,
    .anims = sAnimTable_RedGreenFish,
    .images = sPicTable_RedFish,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_GreenFish = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_PLAYER_GREEN,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_BRIDGE_REFLECTION,
    .size = 512,
    .width = 32,
    .height = 32,
    .paletteSlot = PALSLOT_PLAYER,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_32x32,
    .subspriteTables = gObjectEventSpriteOamTables_32x32,
    .anims = sAnimTable_RedGreenFish,
    .images = sPicTable_GreenFish,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_RedVSSeeker = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_PLAYER_RED,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_BRIDGE_REFLECTION,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_PLAYER,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x32,
    .subspriteTables = gObjectEventSpriteOamTables_16x32,
    .anims = sAnimTable_RedGreenVSSeeker,
    .images = sPicTable_RedItem,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_RedVSSeekerBike = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_PLAYER_RED,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_BRIDGE_REFLECTION,
    .size = 512,
    .width = 32,
    .height = 32,
    .paletteSlot = PALSLOT_PLAYER,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_32x32,
    .subspriteTables = gObjectEventSpriteOamTables_32x32,
    .anims = sAnimTable_RedGreenVSSeekerBike,
    .images = sPicTable_RedVSSeekerBike,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_GreenVSSeeker = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_PLAYER_RED,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_BRIDGE_REFLECTION,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_PLAYER,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x32,
    .subspriteTables = gObjectEventSpriteOamTables_16x32,
    .anims = sAnimTable_RedGreenVSSeeker,
    .images = sPicTable_GreenItem,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_GreenVSSeekerBike = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_PLAYER_RED,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_BRIDGE_REFLECTION,
    .size = 512,
    .width = 32,
    .height = 32,
    .paletteSlot = PALSLOT_PLAYER,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_32x32,
    .subspriteTables = gObjectEventSpriteOamTables_32x32,
    .anims = sAnimTable_RedGreenVSSeekerBike,
    .images = sPicTable_GreenVSSeekerBike,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_TownMap = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_BLUE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 32,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_1,
    .shadowSize = SHADOW_SIZE_S,
    .inanimate = TRUE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_NONE,
    .oam = &gObjectEventBaseOam_32x16,
    .subspriteTables = gObjectEventSpriteOamTables_16x16,
    .anims = sAnimTable_Inanimate,
    .images = sPicTable_TownMap,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Pokedex = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_BLUE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_1,
    .shadowSize = SHADOW_SIZE_S,
    .inanimate = TRUE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_NONE,
    .oam = &gObjectEventBaseOam_16x16,
    .subspriteTables = gObjectEventSpriteOamTables_16x16,
    .anims = sAnimTable_Inanimate,
    .images = sPicTable_Pokedex,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_GBAKid = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_PINK,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_2,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x32,
    .subspriteTables = gObjectEventSpriteOamTables_16x32,
    .anims = sAnimTable_Standard,
    .images = sPicTable_GBAKid,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Snorlax = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_BLUE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 512,
    .width = 32,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_1,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_32x32,
    .subspriteTables = gObjectEventSpriteOamTables_32x32,
    .anims = sAnimTable_Standard,
    .images = sPicTable_Snorlax,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Fossil = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_S,
    .inanimate = TRUE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_NONE,
    .oam = &gObjectEventBaseOam_16x16,
    .subspriteTables = gObjectEventSpriteOamTables_16x16,
    .anims = sAnimTable_Inanimate,
    .images = sPicTable_Fossil,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Ruby = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_BLUE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_1,
    .shadowSize = SHADOW_SIZE_S,
    .inanimate = TRUE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_NONE,
    .oam = &gObjectEventBaseOam_16x16,
    .subspriteTables = gObjectEventSpriteOamTables_16x16,
    .anims = sAnimTable_Inanimate,
    .images = sPicTable_Ruby,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Sapphire = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_BLUE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_1,
    .shadowSize = SHADOW_SIZE_S,
    .inanimate = TRUE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_NONE,
    .oam = &gObjectEventBaseOam_16x16,
    .subspriteTables = gObjectEventSpriteOamTables_16x16,
    .anims = sAnimTable_Inanimate,
    .images = sPicTable_Sapphire,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_OldAmber = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_BLUE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_1,
    .shadowSize = SHADOW_SIZE_S,
    .inanimate = TRUE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_NONE,
    .oam = &gObjectEventBaseOam_16x16,
    .subspriteTables = gObjectEventSpriteOamTables_16x16,
    .anims = sAnimTable_Inanimate,
    .images = sPicTable_OldAmber,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_GymSign = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_S,
    .inanimate = TRUE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_NONE,
    .oam = &gObjectEventBaseOam_16x32,
    .subspriteTables = gObjectEventSpriteOamTables_16x32,
    .anims = sAnimTable_Inanimate,
    .images = sPicTable_GymSign,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Sign = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_S,
    .inanimate = TRUE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_NONE,
    .oam = &gObjectEventBaseOam_16x16,
    .subspriteTables = gObjectEventSpriteOamTables_16x16,
    .anims = sAnimTable_Inanimate,
    .images = sPicTable_Sign,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_TrainerTips = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_S,
    .inanimate = TRUE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_NONE,
    .oam = &gObjectEventBaseOam_16x16,
    .subspriteTables = gObjectEventSpriteOamTables_16x16,
    .anims = sAnimTable_Inanimate,
    .images = sPicTable_WoodenSign,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Clipboard = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_S,
    .inanimate = TRUE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_NONE,
    .oam = &gObjectEventBaseOam_16x16,
    .subspriteTables = gObjectEventSpriteOamTables_16x16,
    .anims = sAnimTable_Inanimate,
    .images = sPicTable_Clipboard,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Meteorite = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_METEORITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 512,
    .width = 32,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_SPECIAL,
    .shadowSize = SHADOW_SIZE_S,
    .inanimate = TRUE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_NONE,
    .oam = &gObjectEventBaseOam_32x32,
    .subspriteTables = gObjectEventSpriteOamTables_32x32,
    .anims = sAnimTable_Inanimate,
    .images = sPicTable_BirthIslandStone,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_LaprasDoll = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_PINK,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 512,
    .width = 32,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_2,
    .shadowSize = SHADOW_SIZE_S,
    .inanimate = TRUE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_NONE,
    .oam = &gObjectEventBaseOam_32x32,
    .subspriteTables = gObjectEventSpriteOamTables_32x32,
    .anims = sAnimTable_Inanimate,
    .images = sPicTable_LaprasDoll,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Spearow = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x16,
    .subspriteTables = gObjectEventSpriteOamTables_16x16,
    .anims = sAnimTable_Standard,
    .images = sPicTable_Spearow,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Omanyte = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_BLUE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_1,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x16,
    .subspriteTables = gObjectEventSpriteOamTables_16x16,
    .anims = sAnimTable_Standard,
    .images = sPicTable_Omanyte,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Kangaskhan = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_BLUE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_1,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x16,
    .subspriteTables = gObjectEventSpriteOamTables_16x16,
    .anims = sAnimTable_Standard,
    .images = sPicTable_Kangaskhan,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Psyduck = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_BLUE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_1,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x16,
    .subspriteTables = gObjectEventSpriteOamTables_16x16,
    .anims = sAnimTable_Standard,
    .images = sPicTable_Psyduck,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_NidoranF = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_PINK,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_2,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x16,
    .subspriteTables = gObjectEventSpriteOamTables_16x16,
    .anims = sAnimTable_Standard,
    .images = sPicTable_NidoranF,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_NidoranM = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_GREEN,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_3,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x16,
    .subspriteTables = gObjectEventSpriteOamTables_16x16,
    .anims = sAnimTable_Standard,
    .images = sPicTable_NidoranM,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Nidorino = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_GREEN,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_3,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x16,
    .subspriteTables = gObjectEventSpriteOamTables_16x16,
    .anims = sAnimTable_Standard,
    .images = sPicTable_Nidorino,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Meowth = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_BLUE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_1,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x16,
    .subspriteTables = gObjectEventSpriteOamTables_16x16,
    .anims = sAnimTable_Standard,
    .images = sPicTable_Meowth,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Seel = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_PINK,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_2,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x16,
    .subspriteTables = gObjectEventSpriteOamTables_16x16,
    .anims = sAnimTable_Standard,
    .images = sPicTable_Seel,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Voltorb = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x16,
    .subspriteTables = gObjectEventSpriteOamTables_16x16,
    .anims = sAnimTable_Standard,
    .images = sPicTable_Voltorb,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Slowpoke = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_PINK,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_2,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x16,
    .subspriteTables = gObjectEventSpriteOamTables_16x16,
    .anims = sAnimTable_Standard,
    .images = sPicTable_Slowpoke,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Slowbro = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_PINK,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_2,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x16,
    .subspriteTables = gObjectEventSpriteOamTables_16x16,
    .anims = sAnimTable_Standard,
    .images = sPicTable_Slowbro,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Machop = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_PINK,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_2,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x16,
    .subspriteTables = gObjectEventSpriteOamTables_16x16,
    .anims = sAnimTable_Standard,
    .images = sPicTable_Machop,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Wigglytuff = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_PINK,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_2,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x16,
    .subspriteTables = gObjectEventSpriteOamTables_16x16,
    .anims = sAnimTable_Standard,
    .images = sPicTable_Wigglytuff,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Doduo = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_BLUE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_1,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x16,
    .subspriteTables = gObjectEventSpriteOamTables_16x16,
    .anims = sAnimTable_Standard,
    .images = sPicTable_Doduo,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Fearow = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x16,
    .subspriteTables = gObjectEventSpriteOamTables_16x16,
    .anims = sAnimTable_Standard,
    .images = sPicTable_Fearow,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Lapras = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_PINK,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_2,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x16,
    .subspriteTables = gObjectEventSpriteOamTables_16x16,
    .anims = sAnimTable_Standard,
    .images = sPicTable_Lapras,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Zapdos = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_BLUE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 512,
    .width = 32,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_1,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_32x32,
    .subspriteTables = gObjectEventSpriteOamTables_32x32,
    .anims = sAnimTable_Standard,
    .images = sPicTable_Zapdos,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Moltres = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_BLUE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 512,
    .width = 32,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_1,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_32x32,
    .subspriteTables = gObjectEventSpriteOamTables_32x32,
    .anims = sAnimTable_Standard,
    .images = sPicTable_Moltres,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Articuno = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_PINK,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 512,
    .width = 32,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_2,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_32x32,
    .subspriteTables = gObjectEventSpriteOamTables_32x32,
    .anims = sAnimTable_Standard,
    .images = sPicTable_Articuno,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_DeoxysD = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_BLUE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 512,
    .width = 32,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_1,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_32x32,
    .subspriteTables = gObjectEventSpriteOamTables_32x32,
    .anims = sAnimTable_Standard,
    .images = sPicTable_DeoxysD,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_DeoxysA = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_BLUE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 512,
    .width = 32,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_1,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_32x32,
    .subspriteTables = gObjectEventSpriteOamTables_32x32,
    .anims = sAnimTable_Standard,
    .images = sPicTable_DeoxysA,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_DeoxysN = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_BLUE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 512,
    .width = 32,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_1,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_32x32,
    .subspriteTables = gObjectEventSpriteOamTables_32x32,
    .anims = sAnimTable_Standard,
    .images = sPicTable_DeoxysN,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Mewtwo = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_PINK,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_2,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x16,
    .subspriteTables = gObjectEventSpriteOamTables_16x16,
    .anims = sAnimTable_Standard,
    .images = sPicTable_Mewtwo,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Mew = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_GREEN,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_3,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x16,
    .subspriteTables = gObjectEventSpriteOamTables_16x16,
    .anims = sAnimTable_Standard,
    .images = sPicTable_Mew,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Entei = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_BLUE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_1,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x16,
    .subspriteTables = gObjectEventSpriteOamTables_16x16,
    .anims = sAnimTable_Standard,
    .images = sPicTable_Entei,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Raikou = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_GREEN,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_3,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x16,
    .subspriteTables = gObjectEventSpriteOamTables_16x16,
    .anims = sAnimTable_Standard,
    .images = sPicTable_Raikou,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Suicune = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_PINK,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_2,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x16,
    .subspriteTables = gObjectEventSpriteOamTables_16x16,
    .anims = sAnimTable_Standard,
    .images = sPicTable_Suicune,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Lugia = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_PINK,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 512,
    .width = 32,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_2,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_32x32,
    .subspriteTables = gObjectEventSpriteOamTables_32x32,
    .anims = sAnimTable_Standard,
    .images = sPicTable_Lugia,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_HoOh = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_BLUE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 512,
    .width = 32,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_1,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_32x32,
    .subspriteTables = gObjectEventSpriteOamTables_32x32,
    .anims = sAnimTable_HoOh,
    .images = sPicTable_HoOh,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Celebi = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_GREEN,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_3,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x16,
    .subspriteTables = gObjectEventSpriteOamTables_16x16,
    .anims = sAnimTable_Standard,
    .images = sPicTable_Celebi,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Cubone = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_WHITE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_4,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x16,
    .subspriteTables = gObjectEventSpriteOamTables_16x16,
    .anims = sAnimTable_Standard,
    .images = sPicTable_Cubone,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Machoke = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_BLUE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_1,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x16,
    .subspriteTables = gObjectEventSpriteOamTables_16x16,
    .anims = sAnimTable_Standard,
    .images = sPicTable_Machoke,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Kabuto = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_BLUE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_1,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x16,
    .subspriteTables = gObjectEventSpriteOamTables_16x16,
    .anims = sAnimTable_Standard,
    .images = sPicTable_Kabuto,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Poliwrath = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_BLUE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_1,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x16,
    .subspriteTables = gObjectEventSpriteOamTables_16x16,
    .anims = sAnimTable_Standard,
    .images = sPicTable_Poliwrath,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Pidgeot = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_BLUE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_1,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x16,
    .subspriteTables = gObjectEventSpriteOamTables_16x16,
    .anims = sAnimTable_Standard,
    .images = sPicTable_Pidgeot,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Chansey = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_PINK,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_2,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x16,
    .subspriteTables = gObjectEventSpriteOamTables_16x16,
    .anims = sAnimTable_Standard,
    .images = sPicTable_Chansey,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Pikachu = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_BLUE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_1,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x16,
    .subspriteTables = gObjectEventSpriteOamTables_16x16,
    .anims = sAnimTable_Standard,
    .images = sPicTable_Pikachu,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Jigglypuff = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_PINK,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_2,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x16,
    .subspriteTables = gObjectEventSpriteOamTables_16x16,
    .anims = sAnimTable_Standard,
    .images = sPicTable_Jigglypuff,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Pidgey = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_BLUE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_1,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x16,
    .subspriteTables = gObjectEventSpriteOamTables_16x16,
    .anims = sAnimTable_Standard,
    .images = sPicTable_Pidgey,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Clefairy = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_PINK,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 128,
    .width = 16,
    .height = 16,
    .paletteSlot = PALSLOT_NPC_2,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x16,
    .subspriteTables = gObjectEventSpriteOamTables_16x16,
    .anims = sAnimTable_Standard,
    .images = sPicTable_Clefairy,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Mom = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_NPC_BLUE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_1,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x32,
    .subspriteTables = gObjectEventSpriteOamTables_16x32,
    .anims = sAnimTable_Standard,
    .images = sPicTable_Mom,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Seagallop = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_SEAGALLOP,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 2048,
    .width = 64,
    .height = 64,
    .paletteSlot = PALSLOT_NPC_SPECIAL,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_NONE,
    .oam = &gObjectEventBaseOam_64x64,
    .subspriteTables = gObjectEventSpriteOamTables_64x64,
    .anims = sAnimTable_Standard,
    .images = sPicTable_Seagallop,
    .affineAnims = gDummySpriteAffineAnimTable,
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_SSAnne = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_SS_ANNE,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 4096,
    .width = 128,
    .height = 64,
    .paletteSlot = PALSLOT_NPC_SPECIAL,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .disableReflectionPaletteLoad = FALSE,
    .tracks = TRACKS_NONE,
    .oam = &gObjectEventBaseOam_8x8,
    .subspriteTables = gObjectEventSpriteOamTables_128x64,
    .anims = sAnimTable_Standard,
    .images = sPicTable_SSAnne,
    .affineAnims = gDummySpriteAffineAnimTable,
};
// ===== END src/data/object_events/object_event_graphics_info.h =====

static const struct SpritePalette sObjectEventSpritePalettes[] = {
    {gObjectEventPal_NpcBlue,                 OBJ_EVENT_PAL_TAG_NPC_BLUE},
    {gObjectEventPal_NpcPink,                 OBJ_EVENT_PAL_TAG_NPC_PINK},
    {gObjectEventPal_NpcGreen,                OBJ_EVENT_PAL_TAG_NPC_GREEN},
    {gObjectEventPal_NpcWhite,                OBJ_EVENT_PAL_TAG_NPC_WHITE},
    {gObjectEventPal_NpcBlueReflection,       OBJ_EVENT_PAL_TAG_NPC_BLUE_REFLECTION},
    {gObjectEventPal_NpcPinkReflection,       OBJ_EVENT_PAL_TAG_NPC_PINK_REFLECTION},
    {gObjectEventPal_NpcGreenReflection,      OBJ_EVENT_PAL_TAG_NPC_GREEN_REFLECTION},
    {gObjectEventPal_NpcWhiteReflection,      OBJ_EVENT_PAL_TAG_NPC_WHITE_REFLECTION},
    {gObjectEventPal_Player,                  OBJ_EVENT_PAL_TAG_PLAYER_RED},
    {gObjectEventPal_PlayerReflection,        OBJ_EVENT_PAL_TAG_PLAYER_RED_REFLECTION},
    {gObjectEventPal_BridgeReflection,        OBJ_EVENT_PAL_TAG_BRIDGE_REFLECTION},
    {gObjectEventPal_RSQuintyPlump,           OBJ_EVENT_PAL_TAG_RS_QUINTY_PLUMP},
    {gObjectEventPal_RSQuintyPlumpReflection, OBJ_EVENT_PAL_TAG_RS_QUINTY_PLUMP_REFLECTION},
    {gObjectEventPal_Player,                  OBJ_EVENT_PAL_TAG_PLAYER_GREEN},
    {gObjectEventPal_PlayerReflection,        OBJ_EVENT_PAL_TAG_PLAYER_GREEN_REFLECTION},
    {gObjectEventPal_Meteorite,               OBJ_EVENT_PAL_TAG_METEORITE},
    {gObjectEventPal_SSAnne,                  OBJ_EVENT_PAL_TAG_SS_ANNE},
    {gObjectEventPal_Seagallop,               OBJ_EVENT_PAL_TAG_SEAGALLOP},
    {},
};

static const u16 sPlayerReflectionPaletteTags[] = {
    OBJ_EVENT_PAL_TAG_PLAYER_RED_REFLECTION,
    OBJ_EVENT_PAL_TAG_PLAYER_RED_REFLECTION,
    OBJ_EVENT_PAL_TAG_PLAYER_RED_REFLECTION,
    OBJ_EVENT_PAL_TAG_PLAYER_RED_REFLECTION,
};

static const u16 sUnusedPlayerReflectionPaletteTags[] = {
    OBJ_EVENT_PAL_TAG_PLAYER_GREEN_REFLECTION,
    OBJ_EVENT_PAL_TAG_PLAYER_GREEN_REFLECTION,
    OBJ_EVENT_PAL_TAG_PLAYER_GREEN_REFLECTION,
    OBJ_EVENT_PAL_TAG_PLAYER_GREEN_REFLECTION,
};

static const u16 sPlayerUnderwaterReflectionPaletteTags[] = {
    OBJ_EVENT_PAL_TAG_RS_PLAYER_UNDERWATER,
    OBJ_EVENT_PAL_TAG_RS_PLAYER_UNDERWATER,
    OBJ_EVENT_PAL_TAG_RS_PLAYER_UNDERWATER,
    OBJ_EVENT_PAL_TAG_RS_PLAYER_UNDERWATER,
};

static const struct PairedPalettes gPlayerReflectionPaletteSets[] = {
    {OBJ_EVENT_PAL_TAG_PLAYER_RED,           sPlayerReflectionPaletteTags},
    {OBJ_EVENT_PAL_TAG_PLAYER_GREEN,         sPlayerReflectionPaletteTags},
    {OBJ_EVENT_PAL_TAG_RS_PLAYER_UNDERWATER, sPlayerUnderwaterReflectionPaletteTags},
    {OBJ_EVENT_PAL_TAG_NONE, NULL},
};

static const u16 sRSQuintyPlumpReflectionPaletteTags[] = {
    OBJ_EVENT_PAL_TAG_RS_QUINTY_PLUMP_REFLECTION,
    OBJ_EVENT_PAL_TAG_RS_QUINTY_PLUMP_REFLECTION,
    OBJ_EVENT_PAL_TAG_RS_QUINTY_PLUMP_REFLECTION,
    OBJ_EVENT_PAL_TAG_RS_QUINTY_PLUMP_REFLECTION,
};

static const u16 sRSTruckReflectionPaletteTags[] = {
    OBJ_EVENT_PAL_TAG_RS_TRUCK,
    OBJ_EVENT_PAL_TAG_RS_TRUCK,
    OBJ_EVENT_PAL_TAG_RS_TRUCK,
    OBJ_EVENT_PAL_TAG_RS_TRUCK,
};

static const u16 sRSMachokeReflectionPaletteTags[] = {
    OBJ_EVENT_PAL_TAG_RS_MACHOKE,
    OBJ_EVENT_PAL_TAG_RS_MACHOKE,
    OBJ_EVENT_PAL_TAG_RS_MACHOKE,
    OBJ_EVENT_PAL_TAG_RS_MACHOKE,
};

static const u16 sRSMovingBoxReflectionPaletteTags[] = {
    OBJ_EVENT_PAL_TAG_RS_MOVING_BOX,
    OBJ_EVENT_PAL_TAG_RS_MOVING_BOX,
    OBJ_EVENT_PAL_TAG_RS_MOVING_BOX,
    OBJ_EVENT_PAL_TAG_RS_MOVING_BOX,
};

static const u16 sMeteoriteReflectionPaletteTags[] = {
    OBJ_EVENT_PAL_TAG_METEORITE,
    OBJ_EVENT_PAL_TAG_METEORITE,
    OBJ_EVENT_PAL_TAG_METEORITE,
    OBJ_EVENT_PAL_TAG_METEORITE,
};

static const u16 sSeagallopReflectionPaletteTags[] = {
    OBJ_EVENT_PAL_TAG_SEAGALLOP,
    OBJ_EVENT_PAL_TAG_SEAGALLOP,
    OBJ_EVENT_PAL_TAG_SEAGALLOP,
    OBJ_EVENT_PAL_TAG_SEAGALLOP,
};

static const u16 sRSSubmarineShadowReflectionPaletteTags[] = {
    OBJ_EVENT_PAL_TAG_RS_SUBMARINE_SHADOW,
    OBJ_EVENT_PAL_TAG_RS_SUBMARINE_SHADOW,
    OBJ_EVENT_PAL_TAG_RS_SUBMARINE_SHADOW,
    OBJ_EVENT_PAL_TAG_RS_SUBMARINE_SHADOW,
};

static const u16 sRSKyogreReflectionPaletteTags[] = {
    OBJ_EVENT_PAL_TAG_RS_KYOGRE_REFLECTION,
    OBJ_EVENT_PAL_TAG_RS_KYOGRE_REFLECTION,
    OBJ_EVENT_PAL_TAG_RS_KYOGRE_REFLECTION,
    OBJ_EVENT_PAL_TAG_RS_KYOGRE_REFLECTION,
};

static const u16 sRSGroudonReflectionPaletteTags[] = {
    OBJ_EVENT_PAL_TAG_RS_GROUDON_REFLECTION,
    OBJ_EVENT_PAL_TAG_RS_GROUDON_REFLECTION,
    OBJ_EVENT_PAL_TAG_RS_GROUDON_REFLECTION,
    OBJ_EVENT_PAL_TAG_RS_GROUDON_REFLECTION,
};

static const u16 sGreenNPCReflectionPaletteTags[] = {
    OBJ_EVENT_PAL_TAG_NPC_GREEN_REFLECTION,
    OBJ_EVENT_PAL_TAG_NPC_GREEN_REFLECTION,
    OBJ_EVENT_PAL_TAG_NPC_GREEN_REFLECTION,
    OBJ_EVENT_PAL_TAG_NPC_GREEN_REFLECTION,
};

static const struct PairedPalettes gSpecialObjectReflectionPaletteSets[] = {
    {OBJ_EVENT_PAL_TAG_PLAYER_RED,          sPlayerReflectionPaletteTags},
    {OBJ_EVENT_PAL_TAG_PLAYER_GREEN,        sPlayerReflectionPaletteTags},
    {OBJ_EVENT_PAL_TAG_RS_QUINTY_PLUMP,     sRSQuintyPlumpReflectionPaletteTags},
    {OBJ_EVENT_PAL_TAG_RS_TRUCK,            sRSTruckReflectionPaletteTags},
    {OBJ_EVENT_PAL_TAG_RS_MACHOKE,          sRSMachokeReflectionPaletteTags},
    {OBJ_EVENT_PAL_TAG_RS_MOVING_BOX,       sRSMovingBoxReflectionPaletteTags},
    {OBJ_EVENT_PAL_TAG_METEORITE,           sMeteoriteReflectionPaletteTags},
    {OBJ_EVENT_PAL_TAG_SEAGALLOP,           sSeagallopReflectionPaletteTags},
    {OBJ_EVENT_PAL_TAG_RS_KYOGRE,           sRSKyogreReflectionPaletteTags},
    {OBJ_EVENT_PAL_TAG_RS_GROUDON,          sRSGroudonReflectionPaletteTags},
    {OBJ_EVENT_PAL_TAG_NPC_GREEN,           sGreenNPCReflectionPaletteTags},
    {OBJ_EVENT_PAL_TAG_RS_SUBMARINE_SHADOW, sRSSubmarineShadowReflectionPaletteTags},
    {OBJ_EVENT_PAL_TAG_NONE, NULL},
};

static const u16 sObjectPaletteTags0[] = {
    OBJ_EVENT_PAL_TAG_PLAYER_RED,
    OBJ_EVENT_PAL_TAG_PLAYER_RED_REFLECTION,
    OBJ_EVENT_PAL_TAG_NPC_BLUE,
    OBJ_EVENT_PAL_TAG_NPC_PINK,
    OBJ_EVENT_PAL_TAG_NPC_GREEN,
    OBJ_EVENT_PAL_TAG_NPC_WHITE,
    OBJ_EVENT_PAL_TAG_NPC_BLUE_REFLECTION,
    OBJ_EVENT_PAL_TAG_NPC_PINK_REFLECTION,
    OBJ_EVENT_PAL_TAG_NPC_GREEN_REFLECTION,
    OBJ_EVENT_PAL_TAG_NPC_WHITE_REFLECTION,
};

static const u16 sObjectPaletteTags1[] = {
    OBJ_EVENT_PAL_TAG_PLAYER_RED,
    OBJ_EVENT_PAL_TAG_PLAYER_GREEN,
    OBJ_EVENT_PAL_TAG_NPC_BLUE,
    OBJ_EVENT_PAL_TAG_NPC_PINK,
    OBJ_EVENT_PAL_TAG_NPC_GREEN,
    OBJ_EVENT_PAL_TAG_NPC_WHITE,
    OBJ_EVENT_PAL_TAG_NPC_BLUE_REFLECTION,
    OBJ_EVENT_PAL_TAG_NPC_PINK_REFLECTION,
    OBJ_EVENT_PAL_TAG_NPC_GREEN_REFLECTION,
    OBJ_EVENT_PAL_TAG_NPC_WHITE_REFLECTION,
};

static const u16 sObjectPaletteTags2[] = {
    OBJ_EVENT_PAL_TAG_PLAYER_RED,
    OBJ_EVENT_PAL_TAG_PLAYER_RED_REFLECTION,
    OBJ_EVENT_PAL_TAG_NPC_BLUE,
    OBJ_EVENT_PAL_TAG_NPC_PINK,
    OBJ_EVENT_PAL_TAG_NPC_GREEN,
    OBJ_EVENT_PAL_TAG_NPC_WHITE,
    OBJ_EVENT_PAL_TAG_NPC_BLUE_REFLECTION,
    OBJ_EVENT_PAL_TAG_NPC_PINK_REFLECTION,
    OBJ_EVENT_PAL_TAG_NPC_GREEN_REFLECTION,
    OBJ_EVENT_PAL_TAG_NPC_WHITE_REFLECTION,
};

static const u16 sObjectPaletteTags3[] = {
    OBJ_EVENT_PAL_TAG_PLAYER_RED,
    OBJ_EVENT_PAL_TAG_PLAYER_RED_REFLECTION,
    OBJ_EVENT_PAL_TAG_NPC_BLUE,
    OBJ_EVENT_PAL_TAG_NPC_PINK,
    OBJ_EVENT_PAL_TAG_NPC_GREEN,
    OBJ_EVENT_PAL_TAG_NPC_WHITE,
    OBJ_EVENT_PAL_TAG_NPC_BLUE_REFLECTION,
    OBJ_EVENT_PAL_TAG_NPC_PINK_REFLECTION,
    OBJ_EVENT_PAL_TAG_NPC_GREEN_REFLECTION,
    OBJ_EVENT_PAL_TAG_NPC_WHITE_REFLECTION,
};

static const u16 *const gObjectPaletteTagSets[] = {
    sObjectPaletteTags0,
    sObjectPaletteTags1,
    sObjectPaletteTags2,
    sObjectPaletteTags3,
};

//#include "data/object_events/berry_tree_graphics_tables.h"
// ===== BEGIN src/data/field_effects/field_effect_objects.h =====
const struct SpritePalette gSpritePalette_GeneralFieldEffect0 = { .data = gFieldEffectObjectPalette0, .tag = FLDEFF_PAL_TAG_GENERAL_0 };
const struct SpritePalette gSpritePalette_GeneralFieldEffect1 = { .data = gFieldEffectObjectPalette1, .tag = FLDEFF_PAL_TAG_GENERAL_1 };

static const union AnimCmd sAnim_Shadow[] =
{
    ANIMCMD_FRAME(0, 1),
    ANIMCMD_END,
};

static const union AnimCmd *const sAnimTable_Shadow[] =
{
    sAnim_Shadow,
};

static const struct SpriteFrameImage sPicTable_ShadowSmall[] = {obj_frame_tiles(gFieldEffectObjectPic_ShadowSmall) };
static const struct SpriteFrameImage sPicTable_ShadowMedium[] = {obj_frame_tiles(gFieldEffectObjectPic_ShadowMedium) };
static const struct SpriteFrameImage sPicTable_ShadowLarge[] = {obj_frame_tiles(gFieldEffectObjectPic_ShadowLarge) };
static const struct SpriteFrameImage sPicTable_ShadowExtraLarge[] = { obj_frame_tiles(gFieldEffectObjectPic_ShadowExtraLarge) };

const struct SpriteTemplate gFieldEffectObjectTemplate_ShadowSmall =
{
    .tileTag = TAG_NONE,
    .paletteTag = TAG_NONE,
    .oam = &gObjectEventBaseOam_8x8,
    .anims = sAnimTable_Shadow,
    .images = sPicTable_ShadowSmall,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = UpdateShadowFieldEffect,
};

const struct SpriteTemplate gFieldEffectObjectTemplate_ShadowMedium =
{
    .tileTag = TAG_NONE,
    .paletteTag = TAG_NONE,
    .oam = &gObjectEventBaseOam_16x8,
    .anims = sAnimTable_Shadow,
    .images = sPicTable_ShadowMedium,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = UpdateShadowFieldEffect,
};

const struct SpriteTemplate gFieldEffectObjectTemplate_ShadowLarge =
{
    .tileTag = TAG_NONE,
    .paletteTag = TAG_NONE,
    .oam = &gObjectEventBaseOam_32x8,
    .anims = sAnimTable_Shadow,
    .images = sPicTable_ShadowLarge,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = UpdateShadowFieldEffect,
};

const struct SpriteTemplate gFieldEffectObjectTemplate_ShadowExtraLarge =
{
    .tileTag = TAG_NONE,
    .paletteTag = TAG_NONE,
    .oam = &gObjectEventBaseOam_64x32,
    .anims = sAnimTable_Shadow,
    .images = sPicTable_ShadowExtraLarge,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = UpdateShadowFieldEffect,
};

static const struct SpriteFrameImage sPicTable_TallGrass[] =
{
    overworld_frame(gFieldEffectObjectPic_TallGrass, 2, 2, 0),
    overworld_frame(gFieldEffectObjectPic_TallGrass, 2, 2, 1),
    overworld_frame(gFieldEffectObjectPic_TallGrass, 2, 2, 2),
    overworld_frame(gFieldEffectObjectPic_TallGrass, 2, 2, 3),
    overworld_frame(gFieldEffectObjectPic_TallGrass, 2, 2, 4),
};

static const union AnimCmd sAnim_TallGrass[] =
{
    ANIMCMD_FRAME(1, 10),
    ANIMCMD_FRAME(2, 10),
    ANIMCMD_FRAME(3, 10),
    ANIMCMD_FRAME(4, 10),
    ANIMCMD_FRAME(0, 10),
    ANIMCMD_END,
};

static const union AnimCmd *const sAnimTable_TallGrass[] =
{
    sAnim_TallGrass,
};

const struct SpriteTemplate gFieldEffectObjectTemplate_TallGrass =
{
    .tileTag = TAG_NONE,
    .paletteTag = FLDEFF_PAL_TAG_GENERAL_1,
    .oam = &gObjectEventBaseOam_16x16,
    .anims = sAnimTable_TallGrass,
    .images = sPicTable_TallGrass,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = UpdateTallGrassFieldEffect,
};

static const struct SpriteFrameImage sPicTable_Ripple[] =
{
    overworld_frame(gFieldEffectObjectPic_Ripple, 2, 2, 0),
    overworld_frame(gFieldEffectObjectPic_Ripple, 2, 2, 1),
    overworld_frame(gFieldEffectObjectPic_Ripple, 2, 2, 2),
    overworld_frame(gFieldEffectObjectPic_Ripple, 2, 2, 3),
    overworld_frame(gFieldEffectObjectPic_Ripple, 2, 2, 4),
};

static const union AnimCmd sAnim_Ripple[] =
{
    ANIMCMD_FRAME(0, 12),
    ANIMCMD_FRAME(1, 9),
    ANIMCMD_FRAME(2, 9),
    ANIMCMD_FRAME(3, 9),
    ANIMCMD_FRAME(0, 9),
    ANIMCMD_FRAME(1, 9),
    ANIMCMD_FRAME(2, 11),
    ANIMCMD_FRAME(4, 11),
    ANIMCMD_END,
};

static const union AnimCmd *const sAnimTable_Ripple[] =
{
    sAnim_Ripple,
};

const struct SpriteTemplate gFieldEffectObjectTemplate_Ripple =
{
    .tileTag = TAG_NONE,
    .paletteTag = FLDEFF_PAL_TAG_GENERAL_1,
    .oam = &gObjectEventBaseOam_16x16,
    .anims = sAnimTable_Ripple,
    .images = sPicTable_Ripple,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = WaitFieldEffectSpriteAnim,
};

static const struct SpriteFrameImage sPicTable_Ash[] =
{
    overworld_frame(gFieldEffectObjectPic_Ash, 2, 2, 0),
    overworld_frame(gFieldEffectObjectPic_Ash, 2, 2, 1),
    overworld_frame(gFieldEffectObjectPic_Ash, 2, 2, 2),
    overworld_frame(gFieldEffectObjectPic_Ash, 2, 2, 3),
    overworld_frame(gFieldEffectObjectPic_Ash, 2, 2, 4),
};

static const union AnimCmd sAnim_Ash[] =
{
    ANIMCMD_FRAME(0, 12),
    ANIMCMD_FRAME(1, 12),
    ANIMCMD_FRAME(2, 8),
    ANIMCMD_FRAME(3, 12),
    ANIMCMD_FRAME(4, 12),
    ANIMCMD_END,
};

static const union AnimCmd *const sAnimTable_Ash[] =
{
    sAnim_Ash,
};

const struct SpriteTemplate gFieldEffectObjectTemplate_Ash =
{
    .tileTag = TAG_NONE,
    .paletteTag = FLDEFF_PAL_TAG_GENERAL_1,
    .oam = &gObjectEventBaseOam_16x16,
    .anims = sAnimTable_Ash,
    .images = sPicTable_Ash,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = UpdateAshFieldEffect,
};

static const struct SpriteFrameImage sPicTable_SurfBlob[] =
{
    overworld_frame(gObjectEventPic_SurfBlob, 2, 8, 0),
    overworld_frame(gObjectEventPic_SurfBlob, 2, 8, 1),
    overworld_frame(gObjectEventPic_SurfBlob, 2, 8, 2),
    overworld_frame(gObjectEventPic_SurfBlob, 2, 8, 3),
    overworld_frame(gObjectEventPic_SurfBlob, 2, 8, 4),
    overworld_frame(gObjectEventPic_SurfBlob, 2, 8, 5),
};

static const union AnimCmd sSurfBlobAnim_FaceSouth[] =
{
    ANIMCMD_FRAME(0, 48),
    ANIMCMD_FRAME(1, 48),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sSurfBlobAnim_FaceNorth[] =
{
    ANIMCMD_FRAME(2, 48),
    ANIMCMD_FRAME(3, 48),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sSurfBlobAnim_FaceWest[] =
{
    ANIMCMD_FRAME(4, 48),
    ANIMCMD_FRAME(5, 48),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sSurfBlobAnim_FaceEast[] =
{
    ANIMCMD_FRAME(4, 48, .hFlip = TRUE),
    ANIMCMD_FRAME(5, 48, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd *const sAnimTable_SurfBlob[] =
{
    [DIR_SOUTH - 1] = sSurfBlobAnim_FaceSouth,
    [DIR_NORTH - 1] = sSurfBlobAnim_FaceNorth,
    [DIR_WEST  - 1] = sSurfBlobAnim_FaceWest,
    [DIR_EAST  - 1] = sSurfBlobAnim_FaceEast,
};

const struct SpriteTemplate gFieldEffectObjectTemplate_SurfBlob =
{
    .tileTag = TAG_NONE,
    .paletteTag = TAG_NONE,
    .oam = &gObjectEventBaseOam_32x32,
    .anims = sAnimTable_SurfBlob,
    .images = sPicTable_SurfBlob,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = UpdateSurfBlobFieldEffect,
};

static const struct SpriteFrameImage sPicTable_Arrow[] =
{
    overworld_frame(gFieldEffectObjectPic_Arrow, 2, 2, 0),
    overworld_frame(gFieldEffectObjectPic_Arrow, 2, 2, 1),
    overworld_frame(gFieldEffectObjectPic_Arrow, 2, 2, 2),
    overworld_frame(gFieldEffectObjectPic_Arrow, 2, 2, 3),
    overworld_frame(gFieldEffectObjectPic_Arrow, 2, 2, 4),
    overworld_frame(gFieldEffectObjectPic_Arrow, 2, 2, 5),
    overworld_frame(gFieldEffectObjectPic_Arrow, 2, 2, 6),
    overworld_frame(gFieldEffectObjectPic_Arrow, 2, 2, 7),
};

static const union AnimCmd sArrowAnim_South[] =
{
    ANIMCMD_FRAME(2, 32),
    ANIMCMD_FRAME(3, 32),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sArrowAnim_North[] =
{
    ANIMCMD_FRAME(0, 32),
    ANIMCMD_FRAME(1, 32),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sArrowAnim_West[] =
{
    ANIMCMD_FRAME(4, 32),
    ANIMCMD_FRAME(5, 32),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sArrowAnim_East[] =
{
    ANIMCMD_FRAME(6, 32),
    ANIMCMD_FRAME(7, 32),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd *const sAnimTable_Arrow[] =
{
    [DIR_SOUTH - 1] = sArrowAnim_South,
    [DIR_NORTH - 1] = sArrowAnim_North,
    [DIR_WEST  - 1] = sArrowAnim_West,
    [DIR_EAST  - 1] = sArrowAnim_East,
};

const struct SpriteTemplate gFieldEffectObjectTemplate_Arrow =
{
    .tileTag = TAG_NONE,
    .paletteTag = TAG_NONE,
    .oam = &gObjectEventBaseOam_16x16,
    .anims = sAnimTable_Arrow,
    .images = sPicTable_Arrow,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

static const struct SpriteFrameImage sPicTable_GroundImpactDust[] =
{
    overworld_frame(gFieldEffectObjectPic_GroundImpactDust, 2, 1, 0),
    overworld_frame(gFieldEffectObjectPic_GroundImpactDust, 2, 1, 1),
    overworld_frame(gFieldEffectObjectPic_GroundImpactDust, 2, 1, 2),
};

static const union AnimCmd sAnim_GroundImpactDust[] =
{
    ANIMCMD_FRAME(0, 8),
    ANIMCMD_FRAME(1, 8),
    ANIMCMD_FRAME(2, 8),
    ANIMCMD_END,
};

static const union AnimCmd *const sAnimTable_GroundImpactDust[] =
{
    sAnim_GroundImpactDust,
};

const struct SpriteTemplate gFieldEffectObjectTemplate_GroundImpactDust =
{
    .tileTag = TAG_NONE,
    .paletteTag = FLDEFF_PAL_TAG_GENERAL_0,
    .oam = &gObjectEventBaseOam_16x8,
    .anims = sAnimTable_GroundImpactDust,
    .images = sPicTable_GroundImpactDust,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = UpdateJumpImpactEffect,
};

static const struct SpriteFrameImage sPicTable_JumpTallGrass[] =
{
    overworld_frame(gFieldEffectObjectPic_JumpTallGrass, 2, 1, 0),
    overworld_frame(gFieldEffectObjectPic_JumpTallGrass, 2, 1, 1),
    overworld_frame(gFieldEffectObjectPic_JumpTallGrass, 2, 1, 2),
    overworld_frame(gFieldEffectObjectPic_JumpTallGrass, 2, 1, 3),
};

static const union AnimCmd sAnim_JumpTallGrass[] =
{
    ANIMCMD_FRAME(0, 8),
    ANIMCMD_FRAME(1, 8),
    ANIMCMD_FRAME(2, 8),
    ANIMCMD_FRAME(3, 8),
    ANIMCMD_END,
};

static const union AnimCmd *const sAnimTable_JumpTallGrass[] =
{
    sAnim_JumpTallGrass,
};

const struct SpriteTemplate gFieldEffectObjectTemplate_JumpTallGrass =
{
    .tileTag = TAG_NONE,
    .paletteTag = FLDEFF_PAL_TAG_GENERAL_1,
    .oam = &gObjectEventBaseOam_16x8,
    .anims = sAnimTable_JumpTallGrass,
    .images = sPicTable_JumpTallGrass,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = UpdateJumpImpactEffect,
};

static const struct SpriteFrameImage sPicTable_SandFootprints[] =
{
    overworld_frame(gFieldEffectObjectPic_SandFootprints, 2, 2, 0),
    overworld_frame(gFieldEffectObjectPic_SandFootprints, 2, 2, 1),
};

static const union AnimCmd sSandFootprintsAnim_South[] =
{
    ANIMCMD_FRAME(0, 1, .vFlip = TRUE),
    ANIMCMD_END,
};

static const union AnimCmd sSandFootprintsAnim_North[] =
{
    ANIMCMD_FRAME(0, 1),
    ANIMCMD_END,
};

static const union AnimCmd sSandFootprintsAnim_West[] =
{
    ANIMCMD_FRAME(1, 1),
    ANIMCMD_END,
};

static const union AnimCmd sSandFootprintsAnim_East[] =
{
    ANIMCMD_FRAME(1, 1, .hFlip = TRUE),
    ANIMCMD_END,
};

static const union AnimCmd *const sAnimTable_SandFootprints[] =
{
    [DIR_NONE]  = sSandFootprintsAnim_South,
    [DIR_SOUTH] = sSandFootprintsAnim_South,
    [DIR_NORTH] = sSandFootprintsAnim_North,
    [DIR_WEST]  = sSandFootprintsAnim_West,
    [DIR_EAST]  = sSandFootprintsAnim_East,
};

const struct SpriteTemplate gFieldEffectObjectTemplate_SandFootprints =
{
    .tileTag = TAG_NONE,
    .paletteTag = FLDEFF_PAL_TAG_GENERAL_0,
    .oam = &gObjectEventBaseOam_16x16,
    .anims = sAnimTable_SandFootprints,
    .images = sPicTable_SandFootprints,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = UpdateFootprintsTireTracksFieldEffect,
};

static const struct SpriteFrameImage sPicTable_DeepSandFootprints[] =
{
    overworld_frame(gFieldEffectObjectPic_DeepSandFootprints, 2, 2, 0),
    overworld_frame(gFieldEffectObjectPic_DeepSandFootprints, 2, 2, 1),
};

static const union AnimCmd sDeepSandFootprintsAnim_South[] =
{
    ANIMCMD_FRAME(0, 1, .vFlip = TRUE),
    ANIMCMD_END,
};

static const union AnimCmd sDeepSandFootprintsAnim_North[] =
{
    ANIMCMD_FRAME(0, 1),
    ANIMCMD_END,
};

static const union AnimCmd sDeepSandFootprintsAnim_West[] =
{
    ANIMCMD_FRAME(1, 1),
    ANIMCMD_END,
};

static const union AnimCmd sDeepSandFootprintsAnim_East[] =
{
    ANIMCMD_FRAME(1, 1, .hFlip = TRUE),
    ANIMCMD_END,
};

static const union AnimCmd *const sAnimTable_DeepSandFootprints[] =
{
    [DIR_NONE]  = sDeepSandFootprintsAnim_South,
    [DIR_SOUTH] = sDeepSandFootprintsAnim_South,
    [DIR_NORTH] = sDeepSandFootprintsAnim_North,
    [DIR_WEST]  = sDeepSandFootprintsAnim_West,
    [DIR_EAST]  = sDeepSandFootprintsAnim_East,
};

const struct SpriteTemplate gFieldEffectObjectTemplate_DeepSandFootprints =
{
    .tileTag = TAG_NONE,
    .paletteTag = FLDEFF_PAL_TAG_GENERAL_0,
    .oam = &gObjectEventBaseOam_16x16,
    .anims = sAnimTable_DeepSandFootprints,
    .images = sPicTable_DeepSandFootprints,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = UpdateFootprintsTireTracksFieldEffect,
};

static const struct SpriteFrameImage sPicTable_BikeTireTracks[] =
{
    overworld_frame(gFieldEffectObjectPic_BikeTireTracks, 2, 2, 0),
    overworld_frame(gFieldEffectObjectPic_BikeTireTracks, 2, 2, 1),
    overworld_frame(gFieldEffectObjectPic_BikeTireTracks, 2, 2, 2),
    overworld_frame(gFieldEffectObjectPic_BikeTireTracks, 2, 2, 3),
};

static const union AnimCmd sBikeTireTracksAnim_South[] =
{
    ANIMCMD_FRAME(2, 1),
    ANIMCMD_END,
};

static const union AnimCmd sBikeTireTracksAnim_North[] =
{
    ANIMCMD_FRAME(2, 1),
    ANIMCMD_END,
};

static const union AnimCmd sBikeTireTracksAnim_West[] =
{
    ANIMCMD_FRAME(1, 1),
    ANIMCMD_END,
};

static const union AnimCmd sBikeTireTracksAnim_East[] =
{
    ANIMCMD_FRAME(1, 1),
    ANIMCMD_END,
};

static const union AnimCmd sBikeTireTracksAnim_SECornerTurn[] =
{
    ANIMCMD_FRAME(0, 1),
    ANIMCMD_END,
};

static const union AnimCmd sBikeTireTracksAnim_SWCornerTurn[] =
{
    ANIMCMD_FRAME(0, 1, .hFlip = TRUE),
    ANIMCMD_END,
};

static const union AnimCmd sBikeTireTracksAnim_NWCornerTurn[] =
{
    ANIMCMD_FRAME(3, 1, .hFlip = TRUE),
    ANIMCMD_END,
};

static const union AnimCmd sBikeTireTracksAnim_NECornerTurn[] =
{
    ANIMCMD_FRAME(3, 1),
    ANIMCMD_END,
};

static const union AnimCmd *const sAnimTable_BikeTireTracks[] =
{
    [DIR_NONE]      = sBikeTireTracksAnim_South,
    [DIR_SOUTH]     = sBikeTireTracksAnim_South,
    [DIR_NORTH]     = sBikeTireTracksAnim_North,
    [DIR_WEST]      = sBikeTireTracksAnim_West,
    [DIR_EAST]      = sBikeTireTracksAnim_East,
    [DIR_SOUTHWEST] = sBikeTireTracksAnim_SECornerTurn,
    [DIR_SOUTHEAST] = sBikeTireTracksAnim_SWCornerTurn,
    [DIR_NORTHWEST] = sBikeTireTracksAnim_NWCornerTurn,
    [DIR_NORTHEAST] = sBikeTireTracksAnim_NECornerTurn,
};

const struct SpriteTemplate gFieldEffectObjectTemplate_BikeTireTracks =
{
    .tileTag = TAG_NONE,
    .paletteTag = FLDEFF_PAL_TAG_GENERAL_0,
    .oam = &gObjectEventBaseOam_16x16,
    .anims = sAnimTable_BikeTireTracks,
    .images = sPicTable_BikeTireTracks,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = UpdateFootprintsTireTracksFieldEffect,
};

static const struct SpriteFrameImage sPicTable_JumpBigSplash[] =
{
    overworld_frame(gFieldEffectObjectPic_JumpBigSplash, 2, 2, 0),
    overworld_frame(gFieldEffectObjectPic_JumpBigSplash, 2, 2, 1),
    overworld_frame(gFieldEffectObjectPic_JumpBigSplash, 2, 2, 2),
    overworld_frame(gFieldEffectObjectPic_JumpBigSplash, 2, 2, 3),
};

static const union AnimCmd sAnim_JumpBigSplash[] =
{
    ANIMCMD_FRAME(0, 8),
    ANIMCMD_FRAME(1, 8),
    ANIMCMD_FRAME(2, 8),
    ANIMCMD_FRAME(3, 8),
    ANIMCMD_END,
};

static const union AnimCmd *const sAnimTable_JumpBigSplash[] =
{
    sAnim_JumpBigSplash,
};

const struct SpriteTemplate gFieldEffectObjectTemplate_JumpBigSplash =
{
    .tileTag = TAG_NONE,
    .paletteTag = FLDEFF_PAL_TAG_GENERAL_0,
    .oam = &gObjectEventBaseOam_16x16,
    .anims = sAnimTable_JumpBigSplash,
    .images = sPicTable_JumpBigSplash,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = UpdateJumpImpactEffect,
};

static const struct SpriteFrameImage sPicTable_Splash[] =
{
    overworld_frame(gFieldEffectObjectPic_Splash, 2, 1, 0),
    overworld_frame(gFieldEffectObjectPic_Splash, 2, 1, 1),
};

static const union AnimCmd sAnim_Splash_0[] =
{
    ANIMCMD_FRAME(0, 4),
    ANIMCMD_FRAME(1, 4),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_Splash_1[] =
{
    ANIMCMD_FRAME(0, 4),
    ANIMCMD_FRAME(1, 4),
    ANIMCMD_FRAME(0, 6),
    ANIMCMD_FRAME(1, 6),
    ANIMCMD_FRAME(0, 8),
    ANIMCMD_FRAME(1, 8),
    ANIMCMD_FRAME(0, 6),
    ANIMCMD_FRAME(1, 6),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd *const sAnimTable_Splash[] =
{
    sAnim_Splash_0,
    sAnim_Splash_1,
};

const struct SpriteTemplate gFieldEffectObjectTemplate_Splash =
{
    .tileTag = TAG_NONE,
    .paletteTag = FLDEFF_PAL_TAG_GENERAL_0,
    .oam = &gObjectEventBaseOam_16x8,
    .anims = sAnimTable_Splash,
    .images = sPicTable_Splash,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = UpdateSplashFieldEffect,
};

static const struct SpriteFrameImage sPicTable_JumpSmallSplash[] =
{
    overworld_frame(gFieldEffectObjectPic_JumpSmallSplash, 2, 1, 0),
    overworld_frame(gFieldEffectObjectPic_JumpSmallSplash, 2, 1, 1),
    overworld_frame(gFieldEffectObjectPic_JumpSmallSplash, 2, 1, 2),
};

static const union AnimCmd sAnim_JumpSmallSplash[] =
{
    ANIMCMD_FRAME(0, 4),
    ANIMCMD_FRAME(1, 4),
    ANIMCMD_FRAME(2, 4),
    ANIMCMD_END,
};

static const union AnimCmd *const sAnimTable_JumpSmallSplash[] =
{
    sAnim_JumpSmallSplash,
};

const struct SpriteTemplate gFieldEffectObjectTemplate_JumpSmallSplash =
{
    .tileTag = TAG_NONE,
    .paletteTag = FLDEFF_PAL_TAG_GENERAL_0,
    .oam = &gObjectEventBaseOam_16x8,
    .anims = sAnimTable_JumpSmallSplash,
    .images = sPicTable_JumpSmallSplash,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = UpdateJumpImpactEffect,
};

static const struct SpriteFrameImage sPicTable_LongGrass[] =
{
    overworld_frame(gFieldEffectObjectPic_LongGrass, 2, 2, 0),
    overworld_frame(gFieldEffectObjectPic_LongGrass, 2, 2, 1),
    overworld_frame(gFieldEffectObjectPic_LongGrass, 2, 2, 2),
    overworld_frame(gFieldEffectObjectPic_LongGrass, 2, 2, 3),
};

static const union AnimCmd sAnim_LongGrass[] =
{
    ANIMCMD_FRAME(1, 3),
    ANIMCMD_FRAME(2, 3),
    ANIMCMD_FRAME(0, 4),
    ANIMCMD_FRAME(3, 4),
    ANIMCMD_FRAME(0, 4),
    ANIMCMD_FRAME(3, 4),
    ANIMCMD_FRAME(0, 4),
    ANIMCMD_END,
};

static const union AnimCmd *const sAnimTable_LongGrass[] =
{
    sAnim_LongGrass,
};

const struct SpriteTemplate gFieldEffectObjectTemplate_LongGrass =
{
    .tileTag = TAG_NONE,
    .paletteTag = FLDEFF_PAL_TAG_GENERAL_1,
    .oam = &gObjectEventBaseOam_16x16,
    .anims = sAnimTable_LongGrass,
    .images = sPicTable_LongGrass,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = UpdateLongGrassFieldEffect,
};

static const struct SpriteFrameImage sPicTable_JumpLongGrass[] =
{
    overworld_frame(gFieldEffectObjectPic_JumpLongGrass, 2, 2, 0),
    overworld_frame(gFieldEffectObjectPic_JumpLongGrass, 2, 2, 1),
    overworld_frame(gFieldEffectObjectPic_JumpLongGrass, 2, 2, 2),
    overworld_frame(gFieldEffectObjectPic_JumpLongGrass, 2, 2, 3),
    overworld_frame(gFieldEffectObjectPic_JumpLongGrass, 2, 2, 4),
    overworld_frame(gFieldEffectObjectPic_JumpLongGrass, 2, 2, 6),
};

static const union AnimCmd sAnim_JumpLongGrass[] =
{
    ANIMCMD_FRAME(0, 4),
    ANIMCMD_FRAME(1, 4),
    ANIMCMD_FRAME(2, 8),
    ANIMCMD_FRAME(3, 8),
    ANIMCMD_FRAME(4, 8),
    ANIMCMD_FRAME(5, 8),
    ANIMCMD_END,
};

static const union AnimCmd *const sAnimTable_JumpLongGrass[] =
{
    sAnim_JumpLongGrass,
};

const struct SpriteTemplate gFieldEffectObjectTemplate_JumpLongGrass =
{
    .tileTag = TAG_NONE,
    .paletteTag = FLDEFF_PAL_TAG_GENERAL_1,
    .oam = &gObjectEventBaseOam_16x16,
    .anims = sAnimTable_JumpLongGrass,
    .images = sPicTable_JumpLongGrass,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = UpdateJumpImpactEffect,
};

static const struct SpriteFrameImage sPicTable_UnusedGrass[] =
{
    overworld_frame(gFieldEffectObjectPic_UnusedGrass, 2, 2, 0),
    overworld_frame(gFieldEffectObjectPic_UnusedGrass, 2, 2, 1),
    overworld_frame(gFieldEffectObjectPic_UnusedGrass, 2, 2, 2),
    overworld_frame(gFieldEffectObjectPic_UnusedGrass, 2, 2, 3),
    overworld_frame(gFieldEffectObjectPic_UnusedGrass, 2, 2, 4),
    overworld_frame(gFieldEffectObjectPic_UnusedGrass, 2, 2, 5),
    overworld_frame(gFieldEffectObjectPic_UnusedGrass, 2, 2, 6),
    overworld_frame(gFieldEffectObjectPic_UnusedGrass, 2, 2, 7),
    overworld_frame(gFieldEffectObjectPic_UnusedGrass, 2, 2, 8),
};

static const union AnimCmd sAnim_UnusedGrass[] =
{
    ANIMCMD_FRAME(0, 10),
    ANIMCMD_FRAME(1, 4),
    ANIMCMD_FRAME(2, 4),
    ANIMCMD_FRAME(3, 4),
    ANIMCMD_FRAME(4, 4),
    ANIMCMD_FRAME(5, 4),
    ANIMCMD_FRAME(6, 4),
    ANIMCMD_FRAME(7, 4),
    ANIMCMD_FRAME(8, 4),
    ANIMCMD_JUMP(7),
};

static const union AnimCmd *const sAnimTable_UnusedGrass[] =
{
    sAnim_UnusedGrass,
};

const struct SpriteTemplate gFieldEffectObjectTemplate_UnusedGrass =
{
    .tileTag = TAG_NONE,
    .paletteTag = FLDEFF_PAL_TAG_GENERAL_1,
    .oam = &gObjectEventBaseOam_16x16,
    .anims = sAnimTable_UnusedGrass,
    .images = sPicTable_UnusedGrass,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = WaitFieldEffectSpriteAnim,
};

static const struct SpriteFrameImage sPicTable_UnusedGrass2[] =
{
    overworld_frame(gFieldEffectObjectPic_UnusedGrass2, 2, 2, 0),
    overworld_frame(gFieldEffectObjectPic_UnusedGrass2, 2, 2, 1),
    overworld_frame(gFieldEffectObjectPic_UnusedGrass2, 2, 2, 2),
    overworld_frame(gFieldEffectObjectPic_UnusedGrass2, 2, 2, 3),
};

static const union AnimCmd sAnim_UnusedGrass2[] =
{
    ANIMCMD_FRAME(0, 4),
    ANIMCMD_FRAME(1, 4),
    ANIMCMD_FRAME(2, 4),
    ANIMCMD_FRAME(3, 4),
    ANIMCMD_FRAME(2, 4),
    ANIMCMD_FRAME(1, 4),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd *const sAnimTable_UnusedGrass2[] =
{
    sAnim_UnusedGrass2,
};

const struct SpriteTemplate gFieldEffectObjectTemplate_UnusedGrass2 =
{
    .tileTag = TAG_NONE,
    .paletteTag = FLDEFF_PAL_TAG_GENERAL_1,
    .oam = &gObjectEventBaseOam_16x16,
    .anims = sAnimTable_UnusedGrass2,
    .images = sPicTable_UnusedGrass2,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = WaitFieldEffectSpriteAnim,
};

static const struct SpriteFrameImage sPicTable_UnusedSand[] =
{
    overworld_frame(gFieldEffectObjectPic_UnusedSand, 2, 2, 0),
    overworld_frame(gFieldEffectObjectPic_UnusedSand, 2, 2, 1),
    overworld_frame(gFieldEffectObjectPic_UnusedSand, 2, 2, 2),
    overworld_frame(gFieldEffectObjectPic_UnusedSand, 2, 2, 3),
};

static const union AnimCmd sAnim_UnusedSand[] =
{
    ANIMCMD_FRAME(0, 4),
    ANIMCMD_FRAME(1, 4),
    ANIMCMD_FRAME(2, 4),
    ANIMCMD_FRAME(3, 4),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd *const sAnimTable_UnusedSand[] =
{
    sAnim_UnusedSand,
};

const struct SpriteTemplate gFieldEffectObjectTemplate_UnusedSand =
{
    .tileTag = TAG_NONE,
    .paletteTag = FLDEFF_PAL_TAG_GENERAL_0,
    .oam = &gObjectEventBaseOam_16x16,
    .anims = sAnimTable_UnusedSand,
    .images = sPicTable_UnusedSand,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = WaitFieldEffectSpriteAnim,
};

static const struct SpriteFrameImage sPicTable_SandPile[] =
{
    overworld_frame(gFieldEffectObjectPic_SandPile, 2, 1, 0),
    overworld_frame(gFieldEffectObjectPic_SandPile, 2, 1, 1),
    overworld_frame(gFieldEffectObjectPic_SandPile, 2, 1, 2),
};

static const union AnimCmd sAnim_SandPile[] =
{
    ANIMCMD_FRAME(0, 4),
    ANIMCMD_FRAME(1, 4),
    ANIMCMD_FRAME(2, 4),
    ANIMCMD_END,
};

static const union AnimCmd *const sAnimTable_SandPile[] =
{
    sAnim_SandPile,
};

const struct SpriteTemplate gFieldEffectObjectTemplate_SandPile =
{
    .tileTag = TAG_NONE,
    .paletteTag = FLDEFF_PAL_TAG_GENERAL_0,
    .oam = &gObjectEventBaseOam_16x8,
    .anims = sAnimTable_SandPile,
    .images = sPicTable_SandPile,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = UpdateSandPileFieldEffect,
};

static const struct SpriteFrameImage sPicTable_WaterSurfacing[] =
{
    overworld_frame(gFieldEffectObjectPic_WaterSurfacing, 2, 2, 0),
    overworld_frame(gFieldEffectObjectPic_WaterSurfacing, 2, 2, 1),
    overworld_frame(gFieldEffectObjectPic_WaterSurfacing, 2, 2, 2),
    overworld_frame(gFieldEffectObjectPic_WaterSurfacing, 2, 2, 3),
};

static const union AnimCmd sAnim_WaterSurfacing[] =
{
    ANIMCMD_FRAME(0, 4),
    ANIMCMD_FRAME(1, 4),
    ANIMCMD_FRAME(2, 4),
    ANIMCMD_FRAME(3, 4),
    ANIMCMD_FRAME(2, 4),
    ANIMCMD_FRAME(1, 4),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd *const sAnimTable_WaterSurfacing[] =
{
    sAnim_WaterSurfacing,
};

const struct SpriteTemplate gFieldEffectObjectTemplate_WaterSurfacing =
{
    .tileTag = TAG_NONE,
    .paletteTag = FLDEFF_PAL_TAG_GENERAL_0,
    .oam = &gObjectEventBaseOam_16x16,
    .anims = sAnimTable_WaterSurfacing,
    .images = sPicTable_WaterSurfacing,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = WaitFieldEffectSpriteAnim,
};

const union AffineAnimCmd sAffineAnim_ReflectionDistortion_0[] =
{
    AFFINEANIMCMD_FRAME(-256, 256, 128, 0),
    AFFINEANIMCMD_FRAME(1, 0, 0, 4),
    AFFINEANIMCMD_FRAME(0, 0, 0, 8),
    AFFINEANIMCMD_FRAME(-1, 0, 0, 4),
    AFFINEANIMCMD_FRAME(0, 0, 0, 8),
    AFFINEANIMCMD_FRAME(-1, 0, 0, 4),
    AFFINEANIMCMD_FRAME(0, 0, 0, 8),
    AFFINEANIMCMD_FRAME(1, 0, 0, 4),
    AFFINEANIMCMD_FRAME(0, 0, 0, 8),
    AFFINEANIMCMD_JUMP(1),
};

const union AffineAnimCmd sAffineAnim_ReflectionDistortion_1[] =
{
    AFFINEANIMCMD_FRAME(256, 256, 128, 0),
    AFFINEANIMCMD_FRAME(-1, 0, 0, 4),
    AFFINEANIMCMD_FRAME(0, 0, 0, 8),
    AFFINEANIMCMD_FRAME(1, 0, 0, 4),
    AFFINEANIMCMD_FRAME(0, 0, 0, 8),
    AFFINEANIMCMD_FRAME(1, 0, 0, 4),
    AFFINEANIMCMD_FRAME(0, 0, 0, 8),
    AFFINEANIMCMD_FRAME(-1, 0, 0, 4),
    AFFINEANIMCMD_FRAME(0, 0, 0, 8),
    AFFINEANIMCMD_JUMP(1),
};

const union AffineAnimCmd *const sAffineAnims_ReflectionDistortion[] =
{
    sAffineAnim_ReflectionDistortion_0,
    sAffineAnim_ReflectionDistortion_1,
};

const struct SpriteTemplate gFieldEffectObjectTemplate_ReflectionDistortion =
{
    .tileTag = 0x0,
    .paletteTag = TAG_NONE,
    .oam = &gDummyOamData,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = sAffineAnims_ReflectionDistortion,
    .callback = SpriteCallbackDummy,
};

/*
static const struct SpriteFrameImage sPicTable_Sparkle[] = {
    overworld_frame(gFieldEffectObjectPic_Sparkle, 2, 2, 0),
    overworld_frame(gFieldEffectObjectPic_Sparkle, 2, 2, 1),
    overworld_frame(gFieldEffectObjectPic_Sparkle, 2, 2, 2),
    overworld_frame(gFieldEffectObjectPic_Sparkle, 2, 2, 3),
    overworld_frame(gFieldEffectObjectPic_Sparkle, 2, 2, 4),
    overworld_frame(gFieldEffectObjectPic_Sparkle, 2, 2, 5),
};

static const union AnimCmd sAnim_Sparkle[] =
{
    ANIMCMD_FRAME(0, 8),
    ANIMCMD_FRAME(1, 8),
    ANIMCMD_FRAME(2, 8),
    ANIMCMD_FRAME(3, 8),
    ANIMCMD_FRAME(4, 8),
    ANIMCMD_FRAME(5, 8),
    ANIMCMD_LOOP(0),
    ANIMCMD_FRAME(0, 4),
    ANIMCMD_FRAME(1, 4),
    ANIMCMD_FRAME(2, 4),
    ANIMCMD_FRAME(3, 4),
    ANIMCMD_FRAME(4, 4),
    ANIMCMD_FRAME(5, 4),
    ANIMCMD_LOOP(3),
    ANIMCMD_FRAME(0, 8),
    ANIMCMD_FRAME(1, 8),
    ANIMCMD_FRAME(2, 8),
    ANIMCMD_FRAME(3, 8),
    ANIMCMD_FRAME(4, 8),
    ANIMCMD_FRAME(5, 8),
    ANIMCMD_END,
};

static const union AnimCmd *const sAnimTable_Sparkle[] =
{
    sAnim_Sparkle,
};

const struct SpriteTemplate gFieldEffectObjectTemplate_Sparkle = {
    .tileTag = 0xFFFF,
    .paletteTag = 0xFFFF,
    .oam = &gObjectEventBaseOam_16x16,
    .anims = sAnimTable_Sparkle,
    .images = sPicTable_Sparkle,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = WaitFieldEffectSpriteAnim,
};
*/

static const struct SpriteFrameImage sPicTable_TreeDisguise[] =
{
    overworld_frame(gFieldEffectObjectPic_TreeDisguise, 2, 4, 0),
    overworld_frame(gFieldEffectObjectPic_TreeDisguise, 2, 4, 1),
    overworld_frame(gFieldEffectObjectPic_TreeDisguise, 2, 4, 2),
    overworld_frame(gFieldEffectObjectPic_TreeDisguise, 2, 4, 3),
    overworld_frame(gFieldEffectObjectPic_TreeDisguise, 2, 4, 4),
    overworld_frame(gFieldEffectObjectPic_TreeDisguise, 2, 4, 5),
    overworld_frame(gFieldEffectObjectPic_TreeDisguise, 2, 4, 6),
};

static const union AnimCmd sAnim_TreeDisguise[] =
{
    ANIMCMD_FRAME(0, 16),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_TreeDisguiseReveal[] =
{
    ANIMCMD_FRAME(0, 4),
    ANIMCMD_FRAME(1, 4),
    ANIMCMD_FRAME(2, 4),
    ANIMCMD_FRAME(3, 4),
    ANIMCMD_FRAME(4, 4),
    ANIMCMD_FRAME(5, 4),
    ANIMCMD_FRAME(6, 4),
    ANIMCMD_END,
};

static const union AnimCmd *const sAnimTable_TreeDisguise[] =
{
    sAnim_TreeDisguise,
    sAnim_TreeDisguiseReveal,
};

const struct SpriteTemplate gFieldEffectObjectTemplate_TreeDisguise =
{
    .tileTag = TAG_NONE,
    .paletteTag = TAG_NONE,
    .oam = &gObjectEventBaseOam_16x32,
    .anims = sAnimTable_TreeDisguise,
    .images = sPicTable_TreeDisguise,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = UpdateDisguiseFieldEffect,
};

static const struct SpriteFrameImage sPicTable_MountainDisguise[] =
{
    overworld_frame(gFieldEffectObjectPic_MountainDisguise, 2, 4, 0),
    overworld_frame(gFieldEffectObjectPic_MountainDisguise, 2, 4, 1),
    overworld_frame(gFieldEffectObjectPic_MountainDisguise, 2, 4, 2),
    overworld_frame(gFieldEffectObjectPic_MountainDisguise, 2, 4, 3),
    overworld_frame(gFieldEffectObjectPic_MountainDisguise, 2, 4, 4),
    overworld_frame(gFieldEffectObjectPic_MountainDisguise, 2, 4, 5),
    overworld_frame(gFieldEffectObjectPic_MountainDisguise, 2, 4, 6),
};

static const union AnimCmd sAnim_MountainDisguise[] =
{
    ANIMCMD_FRAME(0, 16),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_MountainDisguiseReveal[] =
{
    ANIMCMD_FRAME(0, 4),
    ANIMCMD_FRAME(1, 4),
    ANIMCMD_FRAME(2, 4),
    ANIMCMD_FRAME(3, 4),
    ANIMCMD_FRAME(4, 4),
    ANIMCMD_FRAME(5, 4),
    ANIMCMD_FRAME(6, 4),
    ANIMCMD_END,
};

static const union AnimCmd *const sAnimTable_MountainDisguise[] =
{
    sAnim_MountainDisguise,
    sAnim_MountainDisguiseReveal,
};

const struct SpriteTemplate gFieldEffectObjectTemplate_MountainDisguise =
{
    .tileTag = TAG_NONE,
    .paletteTag = TAG_NONE,
    .oam = &gObjectEventBaseOam_16x32,
    .anims = sAnimTable_MountainDisguise,
    .images = sPicTable_MountainDisguise,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = UpdateDisguiseFieldEffect,
};

static const struct SpriteFrameImage sPicTable_SandDisguisePlaceholder[] =
{
    overworld_frame(gFieldEffectObjectPic_SandDisguisePlaceholder, 2, 4, 0),
    overworld_frame(gFieldEffectObjectPic_SandDisguisePlaceholder, 2, 4, 1),
    overworld_frame(gFieldEffectObjectPic_SandDisguisePlaceholder, 2, 4, 2),
    overworld_frame(gFieldEffectObjectPic_SandDisguisePlaceholder, 2, 4, 3),
    overworld_frame(gFieldEffectObjectPic_SandDisguisePlaceholder, 2, 4, 4),
    overworld_frame(gFieldEffectObjectPic_SandDisguisePlaceholder, 2, 4, 5),
    overworld_frame(gFieldEffectObjectPic_SandDisguisePlaceholder, 2, 4, 6),
};

const struct SpriteTemplate gFieldEffectObjectTemplate_SandDisguisePlaceholder =
{
    .tileTag = TAG_NONE,
    .paletteTag = TAG_NONE,
    .oam = &gObjectEventBaseOam_16x32,
    .anims = sAnimTable_TreeDisguise,
    .images = sPicTable_SandDisguisePlaceholder,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = UpdateDisguiseFieldEffect,
};

static const struct SpriteFrameImage sPicTable_Bird[] =
{
    overworld_frame(gFieldEffectObjectPic_Bird, 8, 8, 0),
    overworld_frame(gFieldEffectObjectPic_Bird, 8, 8, 1),
    overworld_frame(gFieldEffectObjectPic_Bird, 8, 8, 2),
    overworld_frame(gFieldEffectObjectPic_Bird, 8, 8, 3),
    overworld_frame(gFieldEffectObjectPic_Bird, 8, 8, 4),
};

static const union AnimCmd sAnim_Bird_WithoutPlayer[] =
{
    ANIMCMD_FRAME(0, 1),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_Bird_Red_FlyOut[] =
{
    ANIMCMD_FRAME(1, 1),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_Bird_Red_FlyIn[] =
{
    ANIMCMD_FRAME(2, 1),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_Bird_Green_FlyOut[] =
{
    ANIMCMD_FRAME(3, 1),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_Bird_Green_FlyIn[] =
{
    ANIMCMD_FRAME(4, 1),
    ANIMCMD_END,
};

static const union AnimCmd *const sAnimTable_Bird[] =
{
    sAnim_Bird_WithoutPlayer,
    sAnim_Bird_Red_FlyOut,
    sAnim_Bird_Red_FlyIn,
    sAnim_Bird_Green_FlyOut,
    sAnim_Bird_Green_FlyIn,
};

const struct SpriteTemplate gFieldEffectObjectTemplate_Bird =
{
    .tileTag = TAG_NONE,
    .paletteTag = TAG_NONE,
    .oam = &gObjectEventBaseOam_64x64,
    .anims = sAnimTable_Bird,
    .images = sPicTable_Bird,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

static const struct SpriteFrameImage sPicTable_ShortGrass[] =
{
    overworld_frame(gFieldEffectObjectPic_ShortGrass, 2, 2, 0),
    overworld_frame(gFieldEffectObjectPic_ShortGrass, 2, 2, 1),
};

static const union AnimCmd sAnim_ShortGrass[] =
{
    ANIMCMD_FRAME(0, 4),
    ANIMCMD_FRAME(1, 4),
    ANIMCMD_END,
};

static const union AnimCmd *const sAnimTable_ShortGrass[] =
{
    sAnim_ShortGrass,
};

const struct SpriteTemplate gFieldEffectObjectTemplate_ShortGrass =
{
    .tileTag = TAG_NONE,
    .paletteTag = FLDEFF_PAL_TAG_GENERAL_1,
    .oam = &gObjectEventBaseOam_16x16,
    .anims = sAnimTable_ShortGrass,
    .images = sPicTable_ShortGrass,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = UpdateShortGrassFieldEffect,
};

static const struct SpriteFrameImage sPicTable_HotSpringsWater[] =
{
    obj_frame_tiles(gFieldEffectObjectPic_HotSpringsWater),
};

static const union AnimCmd sAnim_HotSpringsWater[] =
{
    ANIMCMD_FRAME(0, 4),
    ANIMCMD_END,
};

static const union AnimCmd *const sAnimTable_HotSpringsWater[] =
{
    sAnim_HotSpringsWater,
};

const struct SpriteTemplate gFieldEffectObjectTemplate_HotSpringsWater =
{
    .tileTag = TAG_NONE,
    .paletteTag = FLDEFF_PAL_TAG_GENERAL_1,
    .oam = &gObjectEventBaseOam_16x16,
    .anims = sAnimTable_HotSpringsWater,
    .images = sPicTable_HotSpringsWater,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = UpdateHotSpringsWaterFieldEffect,
};

static const struct SpriteFrameImage sPicTable_AshPuff[] =
{
    overworld_frame(gFieldEffectObjectPic_AshPuff, 2, 2, 0),
    overworld_frame(gFieldEffectObjectPic_AshPuff, 2, 2, 1),
    overworld_frame(gFieldEffectObjectPic_AshPuff, 2, 2, 2),
    overworld_frame(gFieldEffectObjectPic_AshPuff, 2, 2, 3),
    overworld_frame(gFieldEffectObjectPic_AshPuff, 2, 2, 4),
};

static const union AnimCmd sAnim_AshPuff[] =
{
    ANIMCMD_FRAME(0, 6),
    ANIMCMD_FRAME(1, 6),
    ANIMCMD_FRAME(2, 6),
    ANIMCMD_FRAME(3, 6),
    ANIMCMD_FRAME(4, 6),
    ANIMCMD_END,
};

static const union AnimCmd *const sAnimTable_AshPuff[] =
{
    sAnim_AshPuff,
};

const struct SpriteTemplate gFieldEffectObjectTemplate_AshPuff =
{
    .tileTag = TAG_NONE,
    .paletteTag = FLDEFF_PAL_TAG_ASH,
    .oam = &gObjectEventBaseOam_16x16,
    .anims = sAnimTable_AshPuff,
    .images = sPicTable_AshPuff,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCB_PopOutOfAsh,
};

const struct SpritePalette gSpritePalette_Ash = { .data = gFieldEffectPal_Ash, .tag = FLDEFF_PAL_TAG_ASH };

static const struct SpriteFrameImage sPicTable_AshLaunch[] =
{
    overworld_frame(gFieldEffectObjectPic_AshLaunch, 2, 2, 0),
    overworld_frame(gFieldEffectObjectPic_AshLaunch, 2, 2, 1),
    overworld_frame(gFieldEffectObjectPic_AshLaunch, 2, 2, 2),
    overworld_frame(gFieldEffectObjectPic_AshLaunch, 2, 2, 3),
    overworld_frame(gFieldEffectObjectPic_AshLaunch, 2, 2, 4),
};

static const union AnimCmd sAnim_AshLaunch[] =
{
    ANIMCMD_FRAME(0, 6),
    ANIMCMD_FRAME(1, 6),
    ANIMCMD_FRAME(2, 6),
    ANIMCMD_FRAME(3, 6),
    ANIMCMD_FRAME(4, 6),
    ANIMCMD_END,
};

static const union AnimCmd *const sAnimTable_AshLaunch[] =
{
    sAnim_AshLaunch,
};

const struct SpriteTemplate gFieldEffectObjectTemplate_AshLaunch =
{
    .tileTag = TAG_NONE,
    .paletteTag = FLDEFF_PAL_TAG_ASH,
    .oam = &gObjectEventBaseOam_16x16,
    .anims = sAnimTable_AshLaunch,
    .images = sPicTable_AshLaunch,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCB_AshLaunch,
};

static const struct SpriteFrameImage sPicTable_Bubbles[] =
{
    overworld_frame(gFieldEffectObjectPic_Bubbles, 2, 4, 0),
    overworld_frame(gFieldEffectObjectPic_Bubbles, 2, 4, 1),
    overworld_frame(gFieldEffectObjectPic_Bubbles, 2, 4, 2),
    overworld_frame(gFieldEffectObjectPic_Bubbles, 2, 4, 3),
    overworld_frame(gFieldEffectObjectPic_Bubbles, 2, 4, 4),
    overworld_frame(gFieldEffectObjectPic_Bubbles, 2, 4, 5),
    overworld_frame(gFieldEffectObjectPic_Bubbles, 2, 4, 6),
    overworld_frame(gFieldEffectObjectPic_Bubbles, 2, 4, 7),
};

static const union AnimCmd sAnim_Bubbles[] =
{
    ANIMCMD_FRAME(0, 4),
    ANIMCMD_FRAME(1, 4),
    ANIMCMD_FRAME(2, 4),
    ANIMCMD_FRAME(3, 6),
    ANIMCMD_FRAME(4, 6),
    ANIMCMD_FRAME(5, 4),
    ANIMCMD_FRAME(6, 4),
    ANIMCMD_FRAME(7, 4),
    ANIMCMD_END,
};

static const union AnimCmd *const sAnimTable_Bubbles[] =
{
    sAnim_Bubbles,
};

const struct SpriteTemplate gFieldEffectObjectTemplate_Bubbles =
{
    .tileTag = TAG_NONE,
    .paletteTag = FLDEFF_PAL_TAG_GENERAL_0,
    .oam = &gObjectEventBaseOam_16x32,
    .anims = sAnimTable_Bubbles,
    .images = sPicTable_Bubbles,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = UpdateBubblesFieldEffect,
};

static const struct SpriteFrameImage sPicTable_SmallSparkle[] =
{
    overworld_frame(gFieldEffectObjectPic_SmallSparkle, 2, 2, 0),
    overworld_frame(gFieldEffectObjectPic_SmallSparkle, 2, 2, 1),
};

static const union AnimCmd sAnim_SmallSparkle[] =
{
    ANIMCMD_FRAME(0, 3),
    ANIMCMD_FRAME(1, 5),
    ANIMCMD_FRAME(0, 5),
    ANIMCMD_END,
};

static const union AnimCmd *const sAnimTable_SmallSparkle[] =
{
    sAnim_SmallSparkle,
};

const struct SpriteTemplate gFieldEffectObjectTemplate_SmallSparkle =
{
    .tileTag = TAG_NONE,
    .paletteTag = FLDEFF_PAL_TAG_SMALL_SPARKLE,
    .oam = &gObjectEventBaseOam_16x16,
    .anims = sAnimTable_SmallSparkle,
    .images = sPicTable_SmallSparkle,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = UpdateSparkleFieldEffect,
};

const struct SpritePalette gSpritePalette_SmallSparkle = { .data = gFieldEffectPal_SmallSparkle, .tag = FLDEFF_PAL_TAG_SMALL_SPARKLE };
// ===== END src/data/field_effects/field_effect_objects.h =====

static const s16 gMovementDelaysMedium[] = {32, 64,  96, 128};
static const s16 gMovementDelaysLong[] =   {32, 64, 128, 192};
static const s16 gMovementDelaysShort[] =  {32, 48,  64,  80};

// ===== BEGIN src/data/object_events/movement_type_func_tables.h =====
static bool8 MovementType_WanderAround_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_WanderAround_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_WanderAround_Step2(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_WanderAround_Step3(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_WanderAround_Step4(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_WanderAround_Step5(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_WanderAround_Step5Slower(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_WanderAround_Step6(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_LookAround_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_LookAround_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_LookAround_Step2(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_LookAround_Step3(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_LookAround_Step4(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_WanderUpAndDown_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_WanderUpAndDown_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_WanderUpAndDown_Step2(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_WanderUpAndDown_Step3(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_WanderUpAndDown_Step4(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_WanderUpAndDown_Step5(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_WanderUpAndDown_Step6(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_WanderLeftAndRight_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_WanderLeftAndRight_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_WanderLeftAndRight_Step2(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_WanderLeftAndRight_Step3(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_WanderLeftAndRight_Step4(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_WanderLeftAndRight_Step5(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_WanderLeftAndRight_Step6(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_FaceDirection_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_FaceDirection_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_FaceDirection_Step2(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_FaceDownAndUp_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_FaceDownAndUp_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_FaceDownAndUp_Step2(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_FaceDownAndUp_Step3(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_FaceDownAndUp_Step4(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_FaceLeftAndRight_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_FaceLeftAndRight_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_FaceLeftAndRight_Step2(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_FaceLeftAndRight_Step3(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_FaceLeftAndRight_Step4(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_FaceUpAndLeft_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_FaceUpAndLeft_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_FaceUpAndLeft_Step2(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_FaceUpAndLeft_Step3(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_FaceUpAndLeft_Step4(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_FaceUpAndRight_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_FaceUpAndRight_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_FaceUpAndRight_Step2(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_FaceUpAndRight_Step3(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_FaceUpAndRight_Step4(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_FaceDownAndLeft_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_FaceDownAndLeft_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_FaceDownAndLeft_Step2(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_FaceDownAndLeft_Step3(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_FaceDownAndLeft_Step4(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_FaceDownAndRight_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_FaceDownAndRight_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_FaceDownAndRight_Step2(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_FaceDownAndRight_Step3(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_FaceDownAndRight_Step4(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_FaceDownUpAndLeft_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_FaceDownUpAndLeft_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_FaceDownUpAndLeft_Step2(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_FaceDownUpAndLeft_Step3(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_FaceDownUpAndLeft_Step4(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_FaceDownUpAndRight_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_FaceDownUpAndRight_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_FaceDownUpAndRight_Step2(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_FaceDownUpAndRight_Step3(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_FaceDownUpAndRight_Step4(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_FaceUpLeftAndRight_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_FaceUpLeftAndRight_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_FaceUpLeftAndRight_Step2(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_FaceUpLeftAndRight_Step3(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_FaceUpLeftAndRight_Step4(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_FaceDownLeftAndRight_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_FaceDownLeftAndRight_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_FaceDownLeftAndRight_Step2(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_FaceDownLeftAndRight_Step3(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_FaceDownLeftAndRight_Step4(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_RotateCounterclockwise_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_RotateCounterclockwise_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_RotateCounterclockwise_Step2(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_RotateCounterclockwise_Step3(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_RotateClockwise_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_RotateClockwise_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_RotateClockwise_Step2(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_RotateClockwise_Step3(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_WalkBackAndForth_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_WalkBackAndForth_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_WalkBackAndForth_Step2(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_WalkBackAndForth_Step3(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_WalkSequence_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_WalkSequence_Step2(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_WalkSequenceUpRightLeftDown_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_WalkSequenceRightLeftDownUp_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_WalkSequenceDownUpRightLeft_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_WalkSequenceLeftDownUpRight_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_WalkSequenceUpLeftRightDown_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_WalkSequenceLeftRightDownUp_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_WalkSequenceDownUpLeftRight_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_WalkSequenceRightDownUpLeft_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_WalkSequenceLeftUpDownRight_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_WalkSequenceUpDownRightLeft_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_WalkSequenceRightLeftUpDown_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_WalkSequenceDownRightLeftUp_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_WalkSequenceRightUpDownLeft_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_WalkSequenceUpDownLeftRight_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_WalkSequenceLeftRightUpDown_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_WalkSequenceDownLeftRightUp_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_WalkSequenceUpLeftDownRight_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_WalkSequenceDownRightUpLeft_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_WalkSequenceLeftDownRightUp_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_WalkSequenceRightUpLeftDown_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_WalkSequenceUpRightDownLeft_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_WalkSequenceDownLeftUpRight_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_WalkSequenceLeftUpRightDown_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_WalkSequenceRightDownLeftUp_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_CopyPlayer_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_CopyPlayer_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_CopyPlayer_Step2(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 CopyablePlayerMovement_None(struct ObjectEvent *objectEvent, struct Sprite *sprite, u8 playerDirection, bool8 tileCallback(u8));
static bool8 CopyablePlayerMovement_FaceDirection(struct ObjectEvent *objectEvent, struct Sprite *sprite, u8 playerDirection, bool8 tileCallback(u8));
static bool8 CopyablePlayerMovement_GoSpeed0(struct ObjectEvent *objectEvent, struct Sprite *sprite, u8 playerDirection, bool8 tileCallback(u8));
static bool8 CopyablePlayerMovement_GoSpeed1(struct ObjectEvent *objectEvent, struct Sprite *sprite, u8 playerDirection, bool8 tileCallback(u8));
static bool8 CopyablePlayerMovement_GoSpeed2(struct ObjectEvent *objectEvent, struct Sprite *sprite, u8 playerDirection, bool8 tileCallback(u8));
static bool8 CopyablePlayerMovement_Slide(struct ObjectEvent *objectEvent, struct Sprite *sprite, u8 playerDirection, bool8 tileCallback(u8));
static bool8 cph_IM_DIFFERENT(struct ObjectEvent *objectEvent, struct Sprite *sprite, u8 playerDirection, bool8 tileCallback(u8));
static bool8 CopyablePlayerMovement_GoSpeed4(struct ObjectEvent *objectEvent, struct Sprite *sprite, u8 playerDirection, bool8 tileCallback(u8));
static bool8 CopyablePlayerMovement_Jump(struct ObjectEvent *objectEvent, struct Sprite *sprite, u8 playerDirection, bool8 tileCallback(u8));
static bool8 MovementType_CopyPlayer_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_CopyPlayerInGrass_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_CopyPlayer_Step2(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_Buried_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_WalkInPlace_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_MoveInPlace_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_WalkInPlaceFast_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_MoveInPlace_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_JogInPlace_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_MoveInPlace_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_Invisible_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_Invisible_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_Invisible_Step2(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_RaiseHandAndStop_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_RaiseHandAndStop_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_RaiseHandAndStop_Step2(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_RaiseHandAndJump_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_RaiseHandAndSwim_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite);
static bool8 MovementType_RaiseHandAndMove_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite);

static u8 GetVectorDirection(s16 dx, s16 dy, s16 absdx, s16 absdy);
static u8 GetLimitedVectorDirection_SouthNorth(s16 dx, s16 dy, s16 absdx, s16 absdy);
static u8 GetLimitedVectorDirection_WestEast(s16 dx, s16 dy, s16 absdx, s16 absdy);
static u8 GetLimitedVectorDirection_WestNorth(s16 dx, s16 dy, s16 absdx, s16 absdy);
static u8 GetLimitedVectorDirection_EastNorth(s16 dx, s16 dy, s16 absdx, s16 absdy);
static u8 GetLimitedVectorDirection_WestSouth(s16 dx, s16 dy, s16 absdx, s16 absdy);
static u8 GetLimitedVectorDirection_EastSouth(s16 dx, s16 dy, s16 absdx, s16 absdy);
static u8 GetLimitedVectorDirection_SouthNorthWest(s16 dx, s16 dy, s16 absdx, s16 absdy);
static u8 GetLimitedVectorDirection_SouthNorthEast(s16 dx, s16 dy, s16 absdx, s16 absdy);
static u8 GetLimitedVectorDirection_NorthWestEast(s16 dx, s16 dy, s16 absdx, s16 absdy);
static u8 GetLimitedVectorDirection_SouthWestEast(s16 dx, s16 dy, s16 absdx, s16 absdy);

u8 (*const gMovementTypeFuncs_WanderAround[])(struct ObjectEvent *, struct Sprite *) = {
    MovementType_WanderAround_Step0,
    MovementType_WanderAround_Step1,
    MovementType_WanderAround_Step2,
    MovementType_WanderAround_Step3,
    MovementType_WanderAround_Step4,
    MovementType_WanderAround_Step5,
    MovementType_WanderAround_Step6,
};

u8 (*const gMovementTypeFuncs_WanderAroundSlower[])(struct ObjectEvent *, struct Sprite *) = {
    MovementType_WanderAround_Step0,
    MovementType_WanderAround_Step1,
    MovementType_WanderAround_Step2,
    MovementType_WanderAround_Step3,
    MovementType_WanderAround_Step4,
    MovementType_WanderAround_Step5Slower,
    MovementType_WanderAround_Step6,
};

const u8 gStandardDirections[] = {DIR_SOUTH, DIR_NORTH, DIR_WEST, DIR_EAST};

u8 (*const gGetVectorDirectionFuncs[])(s16, s16, s16, s16) = {
    GetVectorDirection,
    GetLimitedVectorDirection_SouthNorth,
    GetLimitedVectorDirection_WestEast,
    GetLimitedVectorDirection_WestNorth,
    GetLimitedVectorDirection_EastNorth,
    GetLimitedVectorDirection_WestSouth,
    GetLimitedVectorDirection_EastSouth,
    GetLimitedVectorDirection_SouthNorthWest,
    GetLimitedVectorDirection_SouthNorthEast,
    GetLimitedVectorDirection_NorthWestEast,
    GetLimitedVectorDirection_SouthWestEast,
};

u8 (*const gMovementTypeFuncs_LookAround[])(struct ObjectEvent *, struct Sprite *) = {
    MovementType_LookAround_Step0,
    MovementType_LookAround_Step1,
    MovementType_LookAround_Step2,
    MovementType_LookAround_Step3,
    MovementType_LookAround_Step4,
};

u8 (*const gMovementTypeFuncs_WanderUpAndDown[])(struct ObjectEvent *, struct Sprite *) = {
    MovementType_WanderUpAndDown_Step0,
    MovementType_WanderUpAndDown_Step1,
    MovementType_WanderUpAndDown_Step2,
    MovementType_WanderUpAndDown_Step3,
    MovementType_WanderUpAndDown_Step4,
    MovementType_WanderUpAndDown_Step5,
    MovementType_WanderUpAndDown_Step6,
};

const u8 gUpAndDownDirections[] = {DIR_SOUTH, DIR_NORTH};

u8 (*const gMovementTypeFuncs_WanderLeftAndRight[])(struct ObjectEvent *, struct Sprite *) = {
    MovementType_WanderLeftAndRight_Step0,
    MovementType_WanderLeftAndRight_Step1,
    MovementType_WanderLeftAndRight_Step2,
    MovementType_WanderLeftAndRight_Step3,
    MovementType_WanderLeftAndRight_Step4,
    MovementType_WanderLeftAndRight_Step5,
    MovementType_WanderLeftAndRight_Step6,
};

const u8 gLeftAndRightDirections[] = {DIR_WEST, DIR_EAST};

u8 (*const gMovementTypeFuncs_FaceDirection[])(struct ObjectEvent *, struct Sprite *) = {
    MovementType_FaceDirection_Step0,
    MovementType_FaceDirection_Step1,
    MovementType_FaceDirection_Step2,
};

u8 (*const gMovementTypeFuncs_FaceDownAndUp[])(struct ObjectEvent *, struct Sprite *) = {
    MovementType_FaceDownAndUp_Step0,
    MovementType_FaceDownAndUp_Step1,
    MovementType_FaceDownAndUp_Step2,
    MovementType_FaceDownAndUp_Step3,
    MovementType_FaceDownAndUp_Step4,
};

u8 (*const gMovementTypeFuncs_FaceLeftAndRight[])(struct ObjectEvent *, struct Sprite *) = {
    MovementType_FaceLeftAndRight_Step0,
    MovementType_FaceLeftAndRight_Step1,
    MovementType_FaceLeftAndRight_Step2,
    MovementType_FaceLeftAndRight_Step3,
    MovementType_FaceLeftAndRight_Step4,
};

u8 (*const gMovementTypeFuncs_FaceUpAndLeft[])(struct ObjectEvent *, struct Sprite *) = {
    MovementType_FaceUpAndLeft_Step0,
    MovementType_FaceUpAndLeft_Step1,
    MovementType_FaceUpAndLeft_Step2,
    MovementType_FaceUpAndLeft_Step3,
    MovementType_FaceUpAndLeft_Step4,
};

const u8 gUpAndLeftDirections[] = {DIR_NORTH, DIR_WEST};

u8 (*const gMovementTypeFuncs_FaceUpAndRight[])(struct ObjectEvent *, struct Sprite *) = {
    MovementType_FaceUpAndRight_Step0,
    MovementType_FaceUpAndRight_Step1,
    MovementType_FaceUpAndRight_Step2,
    MovementType_FaceUpAndRight_Step3,
    MovementType_FaceUpAndRight_Step4,
};

const u8 gUpAndRightDirections[] = {DIR_NORTH, DIR_EAST};

u8 (*const gMovementTypeFuncs_FaceDownAndLeft[])(struct ObjectEvent *, struct Sprite *) = {
    MovementType_FaceDownAndLeft_Step0,
    MovementType_FaceDownAndLeft_Step1,
    MovementType_FaceDownAndLeft_Step2,
    MovementType_FaceDownAndLeft_Step3,
    MovementType_FaceDownAndLeft_Step4,
};

const u8 gDownAndLeftDirections[] = {DIR_SOUTH, DIR_WEST};

u8 (*const gMovementTypeFuncs_FaceDownAndRight[])(struct ObjectEvent *, struct Sprite *) = {
    MovementType_FaceDownAndRight_Step0,
    MovementType_FaceDownAndRight_Step1,
    MovementType_FaceDownAndRight_Step2,
    MovementType_FaceDownAndRight_Step3,
    MovementType_FaceDownAndRight_Step4,
};

const u8 gDownAndRightDirections[] = {DIR_SOUTH, DIR_EAST};

u8 (*const gMovementTypeFuncs_FaceDownUpAndLeft[])(struct ObjectEvent *, struct Sprite *) = {
    MovementType_FaceDownUpAndLeft_Step0,
    MovementType_FaceDownUpAndLeft_Step1,
    MovementType_FaceDownUpAndLeft_Step2,
    MovementType_FaceDownUpAndLeft_Step3,
    MovementType_FaceDownUpAndLeft_Step4,
};

const u8 gDownUpAndLeftDirections[] = {DIR_NORTH, DIR_SOUTH, DIR_WEST, DIR_SOUTH};

u8 (*const gMovementTypeFuncs_FaceDownUpAndRight[])(struct ObjectEvent *, struct Sprite *) = {
    MovementType_FaceDownUpAndRight_Step0,
    MovementType_FaceDownUpAndRight_Step1,
    MovementType_FaceDownUpAndRight_Step2,
    MovementType_FaceDownUpAndRight_Step3,
    MovementType_FaceDownUpAndRight_Step4,
};

const u8 gDownUpAndRightDirections[] = {DIR_SOUTH, DIR_NORTH, DIR_EAST, DIR_SOUTH};

u8 (*const gMovementTypeFuncs_FaceUpLeftAndRight[])(struct ObjectEvent *, struct Sprite *) = {
    MovementType_FaceUpLeftAndRight_Step0,
    MovementType_FaceUpLeftAndRight_Step1,
    MovementType_FaceUpLeftAndRight_Step2,
    MovementType_FaceUpLeftAndRight_Step3,
    MovementType_FaceUpLeftAndRight_Step4,
};

const u8 gUpLeftAndRightDirections[] = {DIR_NORTH, DIR_WEST, DIR_EAST, DIR_NORTH};

u8 (*const gMovementTypeFuncs_FaceDownLeftAndRight[])(struct ObjectEvent *, struct Sprite *) = {
    MovementType_FaceDownLeftAndRight_Step0,
    MovementType_FaceDownLeftAndRight_Step1,
    MovementType_FaceDownLeftAndRight_Step2,
    MovementType_FaceDownLeftAndRight_Step3,
    MovementType_FaceDownLeftAndRight_Step4,
};

const u8 gDownLeftAndRightDirections[] = {DIR_WEST, DIR_EAST, DIR_SOUTH, DIR_SOUTH};

u8 (*const gMovementTypeFuncs_RotateCounterclockwise[])(struct ObjectEvent *, struct Sprite *) = {
    MovementType_RotateCounterclockwise_Step0,
    MovementType_RotateCounterclockwise_Step1,
    MovementType_RotateCounterclockwise_Step2,
    MovementType_RotateCounterclockwise_Step3,
};

const u8 gCounterclockwiseDirections[] = {DIR_SOUTH, DIR_EAST, DIR_WEST, DIR_SOUTH, DIR_NORTH};

u8 (*const gMovementTypeFuncs_RotateClockwise[])(struct ObjectEvent *, struct Sprite *) = {
    MovementType_RotateClockwise_Step0,
    MovementType_RotateClockwise_Step1,
    MovementType_RotateClockwise_Step2,
    MovementType_RotateClockwise_Step3,
};

const u8 gClockwiseDirections[] = {DIR_SOUTH, DIR_WEST, DIR_EAST, DIR_NORTH, DIR_SOUTH};

u8 (*const gMovementTypeFuncs_WalkBackAndForth[])(struct ObjectEvent *, struct Sprite *) = {
    MovementType_WalkBackAndForth_Step0,
    MovementType_WalkBackAndForth_Step1,
    MovementType_WalkBackAndForth_Step2,
    MovementType_WalkBackAndForth_Step3,
};

u8 (*const gMovementTypeFuncs_WalkSequenceUpRightLeftDown[])(struct ObjectEvent *, struct Sprite *) = {
    MovementType_WalkSequence_Step0,
    MovementType_WalkSequenceUpRightLeftDown_Step1,
    MovementType_WalkSequence_Step2,
};

const u8 gUpRightLeftDownDirections[] = {DIR_NORTH, DIR_EAST, DIR_WEST, DIR_SOUTH};

u8 (*const gMovementTypeFuncs_WalkSequenceRightLeftDownUp[])(struct ObjectEvent *, struct Sprite *) = {
    MovementType_WalkSequence_Step0,
    MovementType_WalkSequenceRightLeftDownUp_Step1,
    MovementType_WalkSequence_Step2,
};

const u8 gRightLeftDownUpDirections[] = {DIR_EAST, DIR_WEST, DIR_SOUTH, DIR_NORTH};

u8 (*const gMovementTypeFuncs_WalkSequenceDownUpRightLeft[])(struct ObjectEvent *, struct Sprite *) = {
    MovementType_WalkSequence_Step0,
    MovementType_WalkSequenceDownUpRightLeft_Step1,
    MovementType_WalkSequence_Step2,
};

const u8 gDownUpRightLeftDirections[] = {DIR_SOUTH, DIR_NORTH, DIR_EAST, DIR_WEST};

u8 (*const gMovementTypeFuncs_WalkSequenceLeftDownUpRight[])(struct ObjectEvent *, struct Sprite *) = {
    MovementType_WalkSequence_Step0,
    MovementType_WalkSequenceLeftDownUpRight_Step1,
    MovementType_WalkSequence_Step2,
};

const u8 gLeftDownUpRightDirections[] = {DIR_WEST, DIR_SOUTH, DIR_NORTH, DIR_EAST};

u8 (*const gMovementTypeFuncs_WalkSequenceUpLeftRightDown[])(struct ObjectEvent *, struct Sprite *) = {
    MovementType_WalkSequence_Step0,
    MovementType_WalkSequenceUpLeftRightDown_Step1,
    MovementType_WalkSequence_Step2,
};

const u8 gUpLeftRightDownDirections[] = {DIR_NORTH, DIR_WEST, DIR_EAST, DIR_SOUTH};

u8 (*const gMovementTypeFuncs_WalkSequenceLeftRightDownUp[])(struct ObjectEvent *, struct Sprite *) = {
    MovementType_WalkSequence_Step0,
    MovementType_WalkSequenceLeftRightDownUp_Step1,
    MovementType_WalkSequence_Step2,
};

const u8 gLeftRightDownUpDirections[] = {DIR_WEST, DIR_EAST, DIR_SOUTH, DIR_NORTH};

u8 (*const gMovementTypeFuncs_WalkSequenceDownUpLeftRight[])(struct ObjectEvent *, struct Sprite *) = {
    MovementType_WalkSequence_Step0,
    MovementType_WalkSequenceDownUpLeftRight_Step1,
    MovementType_WalkSequence_Step2,
};

u8 (*const gMovementTypeFuncs_WalkSequenceRightDownUpLeft[])(struct ObjectEvent *, struct Sprite *) = {
    MovementType_WalkSequence_Step0,
    MovementType_WalkSequenceRightDownUpLeft_Step1,
    MovementType_WalkSequence_Step2,
};

const u8 gRightDownUpLeftDirections[] = {DIR_EAST, DIR_SOUTH, DIR_NORTH, DIR_WEST};

u8 (*const gMovementTypeFuncs_WalkSequenceLeftUpDownRight[])(struct ObjectEvent *, struct Sprite *) = {
    MovementType_WalkSequence_Step0,
    MovementType_WalkSequenceLeftUpDownRight_Step1,
    MovementType_WalkSequence_Step2,
};

const u8 gLeftUpDownRightDirections[] = {DIR_WEST, DIR_NORTH, DIR_SOUTH, DIR_EAST};

u8 (*const gMovementTypeFuncs_WalkSequenceUpDownRightLeft[])(struct ObjectEvent *, struct Sprite *) = {
    MovementType_WalkSequence_Step0,
    MovementType_WalkSequenceUpDownRightLeft_Step1,
    MovementType_WalkSequence_Step2,
};

const u8 gUpDownRightLeftDirections[] = {DIR_NORTH, DIR_SOUTH, DIR_EAST, DIR_WEST};

u8 (*const gMovementTypeFuncs_WalkSequenceRightLeftUpDown[])(struct ObjectEvent *, struct Sprite *) = {
    MovementType_WalkSequence_Step0,
    MovementType_WalkSequenceRightLeftUpDown_Step1,
    MovementType_WalkSequence_Step2,
};

const u8 gRightLeftUpDownDirections[] = {DIR_EAST, DIR_WEST, DIR_NORTH, DIR_SOUTH};

u8 (*const gMovementTypeFuncs_WalkSequenceDownRightLeftUp[])(struct ObjectEvent *, struct Sprite *) = {
    MovementType_WalkSequence_Step0,
    MovementType_WalkSequenceDownRightLeftUp_Step1,
    MovementType_WalkSequence_Step2,
};

const u8 gDownRightLeftUpDirections[] = {DIR_SOUTH, DIR_EAST, DIR_WEST, DIR_NORTH};

u8 (*const gMovementTypeFuncs_WalkSequenceRightUpDownLeft[])(struct ObjectEvent *, struct Sprite *) = {
    MovementType_WalkSequence_Step0,
    MovementType_WalkSequenceRightUpDownLeft_Step1,
    MovementType_WalkSequence_Step2,
};

const u8 gRightUpDownLeftDirections[] = {DIR_EAST, DIR_NORTH, DIR_SOUTH, DIR_WEST};

u8 (*const gMovementTypeFuncs_WalkSequenceUpDownLeftRight[])(struct ObjectEvent *, struct Sprite *) = {
    MovementType_WalkSequence_Step0,
    MovementType_WalkSequenceUpDownLeftRight_Step1,
    MovementType_WalkSequence_Step2,
};

const u8 gUpDownLeftRightDirections[] = {DIR_NORTH, DIR_SOUTH, DIR_WEST, DIR_EAST};

u8 (*const gMovementTypeFuncs_WalkSequenceLeftRightUpDown[])(struct ObjectEvent *, struct Sprite *) = {
    MovementType_WalkSequence_Step0,
    MovementType_WalkSequenceLeftRightUpDown_Step1,
    MovementType_WalkSequence_Step2,
};

const u8 gLeftRightUpDownDirections[] = {DIR_WEST, DIR_EAST, DIR_NORTH, DIR_SOUTH};

u8 (*const gMovementTypeFuncs_WalkSequenceDownLeftRightUp[])(struct ObjectEvent *, struct Sprite *) = {
    MovementType_WalkSequence_Step0,
    MovementType_WalkSequenceDownLeftRightUp_Step1,
    MovementType_WalkSequence_Step2,
};

const u8 gDownLeftRightUpDirections[] = {DIR_SOUTH, DIR_WEST, DIR_EAST, DIR_NORTH};

u8 (*const gMovementTypeFuncs_WalkSequenceUpLeftDownRight[])(struct ObjectEvent *, struct Sprite *) = {
    MovementType_WalkSequence_Step0,
    MovementType_WalkSequenceUpLeftDownRight_Step1,
    MovementType_WalkSequence_Step2,
};

const u8 gUpLeftDownRightDirections[] = {DIR_NORTH, DIR_WEST, DIR_SOUTH, DIR_EAST};

u8 (*const gMovementTypeFuncs_WalkSequenceDownRightUpLeft[])(struct ObjectEvent *, struct Sprite *) = {
    MovementType_WalkSequence_Step0,
    MovementType_WalkSequenceDownRightUpLeft_Step1,
    MovementType_WalkSequence_Step2,
};

const u8 gDownRightUpLeftDirections[] = {DIR_SOUTH, DIR_EAST, DIR_NORTH, DIR_WEST};

u8 (*const gMovementTypeFuncs_WalkSequenceLeftDownRightUp[])(struct ObjectEvent *, struct Sprite *) = {
    MovementType_WalkSequence_Step0,
    MovementType_WalkSequenceLeftDownRightUp_Step1,
    MovementType_WalkSequence_Step2,
};

const u8 gLeftDownRightUpDirections[] = {DIR_WEST, DIR_SOUTH, DIR_EAST, DIR_NORTH};

u8 (*const gMovementTypeFuncs_WalkSequenceRightUpLeftDown[])(struct ObjectEvent *, struct Sprite *) = {
    MovementType_WalkSequence_Step0,
    MovementType_WalkSequenceRightUpLeftDown_Step1,
    MovementType_WalkSequence_Step2,
};

const u8 gRightUpLeftDownDirections[] = {DIR_EAST, DIR_NORTH, DIR_WEST, DIR_SOUTH};

u8 (*const gMovementTypeFuncs_WalkSequenceUpRightDownLeft[])(struct ObjectEvent *, struct Sprite *) = {
    MovementType_WalkSequence_Step0,
    MovementType_WalkSequenceUpRightDownLeft_Step1,
    MovementType_WalkSequence_Step2,
};

const u8 gUpRightDownLeftDirections[] = {DIR_NORTH, DIR_EAST, DIR_SOUTH, DIR_WEST};

u8 (*const gMovementTypeFuncs_WalkSequenceDownLeftUpRight[])(struct ObjectEvent *, struct Sprite *) = {
    MovementType_WalkSequence_Step0,
    MovementType_WalkSequenceDownLeftUpRight_Step1,
    MovementType_WalkSequence_Step2,
};

const u8 gDownLeftUpRightDirections[] = {DIR_SOUTH, DIR_WEST, DIR_NORTH, DIR_EAST};

u8 (*const gMovementTypeFuncs_WalkSequenceLeftUpRightDown[])(struct ObjectEvent *, struct Sprite *) = {
    MovementType_WalkSequence_Step0,
    MovementType_WalkSequenceLeftUpRightDown_Step1,
    MovementType_WalkSequence_Step2,
};

const u8 gLeftUpRightDownDirections[] = {DIR_WEST, DIR_NORTH, DIR_EAST, DIR_SOUTH};

u8 (*const gMovementTypeFuncs_WalkSequenceRightDownLeftUp[])(struct ObjectEvent *, struct Sprite *) = {
    MovementType_WalkSequence_Step0,
    MovementType_WalkSequenceRightDownLeftUp_Step1,
    MovementType_WalkSequence_Step2,
};

const u8 gRightDownLeftUpDirections[] = {DIR_EAST, DIR_SOUTH, DIR_WEST, DIR_NORTH};

u8 (*const gMovementTypeFuncs_CopyPlayer[])(struct ObjectEvent *, struct Sprite *) = {
    MovementType_CopyPlayer_Step0,
    MovementType_CopyPlayer_Step1,
    MovementType_CopyPlayer_Step2,
};

bool8 (*const gCopyPlayerMovementFuncs[])(struct ObjectEvent *, struct Sprite *, u8, bool8(u8)) = {
    CopyablePlayerMovement_None,
    CopyablePlayerMovement_FaceDirection,
    CopyablePlayerMovement_GoSpeed0,
    CopyablePlayerMovement_GoSpeed1,
    CopyablePlayerMovement_GoSpeed2,
    CopyablePlayerMovement_Slide,
    cph_IM_DIFFERENT,
    CopyablePlayerMovement_GoSpeed4,
    CopyablePlayerMovement_Jump,
    CopyablePlayerMovement_None,
    CopyablePlayerMovement_None,
};

u8 (*const gMovementTypeFuncs_CopyPlayerInGrass[])(struct ObjectEvent *, struct Sprite *) = {
    MovementType_CopyPlayer_Step0,
    MovementType_CopyPlayerInGrass_Step1,
    MovementType_CopyPlayer_Step2,
};

u8 (*const gMovementTypeFuncs_Buried[])(struct ObjectEvent *, struct Sprite *) = {
    MovementType_Buried_Step0,
};

u8 (*const gMovementTypeFuncs_WalkInPlace[])(struct ObjectEvent *, struct Sprite *) = {
    MovementType_WalkInPlace_Step0,
    MovementType_MoveInPlace_Step1,
};

u8 (*const gMovementTypeFuncs_WalkInPlaceFast[])(struct ObjectEvent *, struct Sprite *) = {
    MovementType_WalkInPlaceFast_Step0,
    MovementType_MoveInPlace_Step1,
};

u8 (*const gMovementTypeFuncs_JogInPlace[])(struct ObjectEvent *, struct Sprite *) = {
    MovementType_JogInPlace_Step0,
    MovementType_MoveInPlace_Step1,
};

u8 (*const gMovementTypeFuncs_Invisible[])(struct ObjectEvent *, struct Sprite *) = {
    MovementType_Invisible_Step0,
    MovementType_Invisible_Step1,
    MovementType_Invisible_Step2,
};

u8 (*const gMovementTypeFuncs_RaiseHandAndStop[])(struct ObjectEvent *, struct Sprite *) = {
    MovementType_RaiseHandAndStop_Step0,
    MovementType_RaiseHandAndStop_Step1,
    MovementType_RaiseHandAndStop_Step2,
};

u8 (*const gMovementTypeFuncs_RaiseHandAndJump[])(struct ObjectEvent *, struct Sprite *) = {
    MovementType_RaiseHandAndJump_Step0,
    MovementType_RaiseHandAndMove_Step1,
};

u8 (*const gMovementTypeFuncs_RaiseHandAndSwim[])(struct ObjectEvent *, struct Sprite *) = {
    MovementType_RaiseHandAndSwim_Step0,
    MovementType_RaiseHandAndMove_Step1,
};
// ===== END src/data/object_events/movement_type_func_tables.h =====

static const u8 sFaceDirectionAnimNums[] = {
    [DIR_NONE]      = ANIM_STD_FACE_SOUTH,
    [DIR_SOUTH]     = ANIM_STD_FACE_SOUTH,
    [DIR_NORTH]     = ANIM_STD_FACE_NORTH,
    [DIR_WEST]      = ANIM_STD_FACE_WEST,
    [DIR_EAST]      = ANIM_STD_FACE_EAST,
    [DIR_SOUTHWEST] = ANIM_STD_FACE_SOUTH,
    [DIR_SOUTHEAST] = ANIM_STD_FACE_SOUTH,
    [DIR_NORTHWEST] = ANIM_STD_FACE_NORTH,
    [DIR_NORTHEAST] = ANIM_STD_FACE_NORTH,
};

static const u8 sMoveDirectionAnimNums[] = {
    [DIR_NONE]      = ANIM_STD_GO_SOUTH,
    [DIR_SOUTH]     = ANIM_STD_GO_SOUTH,
    [DIR_NORTH]     = ANIM_STD_GO_NORTH,
    [DIR_WEST]      = ANIM_STD_GO_WEST,
    [DIR_EAST]      = ANIM_STD_GO_EAST,
    [DIR_SOUTHWEST] = ANIM_STD_GO_SOUTH,
    [DIR_SOUTHEAST] = ANIM_STD_GO_SOUTH,
    [DIR_NORTHWEST] = ANIM_STD_GO_NORTH,
    [DIR_NORTHEAST] = ANIM_STD_GO_NORTH,
};

static const u8 sMoveDirectionFastAnimNums[] = {
    [DIR_NONE]      = ANIM_STD_GO_FAST_SOUTH,
    [DIR_SOUTH]     = ANIM_STD_GO_FAST_SOUTH,
    [DIR_NORTH]     = ANIM_STD_GO_FAST_NORTH,
    [DIR_WEST]      = ANIM_STD_GO_FAST_WEST,
    [DIR_EAST]      = ANIM_STD_GO_FAST_EAST,
    [DIR_SOUTHWEST] = ANIM_STD_GO_FAST_SOUTH,
    [DIR_SOUTHEAST] = ANIM_STD_GO_FAST_SOUTH,
    [DIR_NORTHWEST] = ANIM_STD_GO_FAST_NORTH,
    [DIR_NORTHEAST] = ANIM_STD_GO_FAST_NORTH,
};

static const u8 sMoveDirectionFasterAnimNums[] = {
    [DIR_NONE]      = ANIM_STD_GO_FASTER_SOUTH,
    [DIR_SOUTH]     = ANIM_STD_GO_FASTER_SOUTH,
    [DIR_NORTH]     = ANIM_STD_GO_FASTER_NORTH,
    [DIR_WEST]      = ANIM_STD_GO_FASTER_WEST,
    [DIR_EAST]      = ANIM_STD_GO_FASTER_EAST,
    [DIR_SOUTHWEST] = ANIM_STD_GO_FASTER_SOUTH,
    [DIR_SOUTHEAST] = ANIM_STD_GO_FASTER_SOUTH,
    [DIR_NORTHWEST] = ANIM_STD_GO_FASTER_NORTH,
    [DIR_NORTHEAST] = ANIM_STD_GO_FASTER_NORTH,
};

static const u8 sMoveDirectionFastestAnimNums[] = {
    [DIR_NONE]      = ANIM_STD_GO_FASTEST_SOUTH,
    [DIR_SOUTH]     = ANIM_STD_GO_FASTEST_SOUTH,
    [DIR_NORTH]     = ANIM_STD_GO_FASTEST_NORTH,
    [DIR_WEST]      = ANIM_STD_GO_FASTEST_WEST,
    [DIR_EAST]      = ANIM_STD_GO_FASTEST_EAST,
    [DIR_SOUTHWEST] = ANIM_STD_GO_FASTEST_SOUTH,
    [DIR_SOUTHEAST] = ANIM_STD_GO_FASTEST_SOUTH,
    [DIR_NORTHWEST] = ANIM_STD_GO_FASTEST_NORTH,
    [DIR_NORTHEAST] = ANIM_STD_GO_FASTEST_NORTH,
};

static const u8 sJumpSpecialDirectionAnimNums[] = {
    [DIR_NONE]      = ANIM_GET_ON_OFF_POKEMON_SOUTH,
    [DIR_SOUTH]     = ANIM_GET_ON_OFF_POKEMON_SOUTH,
    [DIR_NORTH]     = ANIM_GET_ON_OFF_POKEMON_NORTH,
    [DIR_WEST]      = ANIM_GET_ON_OFF_POKEMON_WEST,
    [DIR_EAST]      = ANIM_GET_ON_OFF_POKEMON_EAST,
    [DIR_SOUTHWEST] = ANIM_GET_ON_OFF_POKEMON_SOUTH,
    [DIR_SOUTHEAST] = ANIM_GET_ON_OFF_POKEMON_SOUTH,
    [DIR_NORTHWEST] = ANIM_GET_ON_OFF_POKEMON_NORTH,
    [DIR_NORTHEAST] = ANIM_GET_ON_OFF_POKEMON_NORTH,
};

static const u8 sAcroBunnyHopBackWheelDirectionAnimNums[] = {
    [DIR_NONE]      = ANIM_BUNNY_HOP_BACK_WHEEL_SOUTH,
    [DIR_SOUTH]     = ANIM_BUNNY_HOP_BACK_WHEEL_SOUTH,
    [DIR_NORTH]     = ANIM_BUNNY_HOP_BACK_WHEEL_NORTH,
    [DIR_WEST]      = ANIM_BUNNY_HOP_BACK_WHEEL_WEST,
    [DIR_EAST]      = ANIM_BUNNY_HOP_BACK_WHEEL_EAST,
    [DIR_SOUTHWEST] = ANIM_BUNNY_HOP_BACK_WHEEL_SOUTH,
    [DIR_SOUTHEAST] = ANIM_BUNNY_HOP_BACK_WHEEL_SOUTH,
    [DIR_NORTHWEST] = ANIM_BUNNY_HOP_BACK_WHEEL_NORTH,
    [DIR_NORTHEAST] = ANIM_BUNNY_HOP_BACK_WHEEL_NORTH,
};

static const u8 sAcroBunnyHopFrontWheelDirectionAnimNums[] = {
    [DIR_NONE]      = ANIM_BUNNY_HOP_FRONT_WHEEL_SOUTH,
    [DIR_SOUTH]     = ANIM_BUNNY_HOP_FRONT_WHEEL_SOUTH,
    [DIR_NORTH]     = ANIM_BUNNY_HOP_FRONT_WHEEL_NORTH,
    [DIR_WEST]      = ANIM_BUNNY_HOP_FRONT_WHEEL_WEST,
    [DIR_EAST]      = ANIM_BUNNY_HOP_FRONT_WHEEL_EAST,
    [DIR_SOUTHWEST] = ANIM_BUNNY_HOP_FRONT_WHEEL_SOUTH,
    [DIR_SOUTHEAST] = ANIM_BUNNY_HOP_FRONT_WHEEL_SOUTH,
    [DIR_NORTHWEST] = ANIM_BUNNY_HOP_FRONT_WHEEL_NORTH,
    [DIR_NORTHEAST] = ANIM_BUNNY_HOP_FRONT_WHEEL_NORTH,
};

static const u8 sAcroStandingWheelieBackWheelDirectionAnimNums[] = {
    [DIR_NONE]      = ANIM_STANDING_WHEELIE_BACK_WHEEL_SOUTH,
    [DIR_SOUTH]     = ANIM_STANDING_WHEELIE_BACK_WHEEL_SOUTH,
    [DIR_NORTH]     = ANIM_STANDING_WHEELIE_BACK_WHEEL_NORTH,
    [DIR_WEST]      = ANIM_STANDING_WHEELIE_BACK_WHEEL_WEST,
    [DIR_EAST]      = ANIM_STANDING_WHEELIE_BACK_WHEEL_EAST,
    [DIR_SOUTHWEST] = ANIM_STANDING_WHEELIE_BACK_WHEEL_SOUTH,
    [DIR_SOUTHEAST] = ANIM_STANDING_WHEELIE_BACK_WHEEL_SOUTH,
    [DIR_NORTHWEST] = ANIM_STANDING_WHEELIE_BACK_WHEEL_NORTH,
    [DIR_NORTHEAST] = ANIM_STANDING_WHEELIE_BACK_WHEEL_NORTH,
};

static const u8 sSpinDirectionAnimNums[] = {
    [DIR_NONE]      = ANIM_SPIN_SOUTH,
    [DIR_SOUTH]     = ANIM_SPIN_SOUTH,
    [DIR_NORTH]     = ANIM_SPIN_NORTH,
    [DIR_WEST]      = ANIM_SPIN_WEST,
    [DIR_EAST]      = ANIM_SPIN_EAST,
    [DIR_SOUTHWEST] = ANIM_SPIN_SOUTH,
    [DIR_SOUTHEAST] = ANIM_SPIN_NORTH,
    [DIR_NORTHWEST] = ANIM_SPIN_WEST,
    [DIR_NORTHEAST] = ANIM_SPIN_EAST,
};

static const u8 sAcroStandingWheelieFrontWheelDirectionAnimNums[] = {
    [DIR_NONE]      = ANIM_STANDING_WHEELIE_FRONT_WHEEL_SOUTH,
    [DIR_SOUTH]     = ANIM_STANDING_WHEELIE_FRONT_WHEEL_SOUTH,
    [DIR_NORTH]     = ANIM_STANDING_WHEELIE_FRONT_WHEEL_NORTH,
    [DIR_WEST]      = ANIM_STANDING_WHEELIE_FRONT_WHEEL_WEST,
    [DIR_EAST]      = ANIM_STANDING_WHEELIE_FRONT_WHEEL_EAST,
    [DIR_SOUTHWEST] = ANIM_STANDING_WHEELIE_FRONT_WHEEL_SOUTH,
    [DIR_SOUTHEAST] = ANIM_STANDING_WHEELIE_FRONT_WHEEL_SOUTH,
    [DIR_NORTHWEST] = ANIM_STANDING_WHEELIE_FRONT_WHEEL_NORTH,
    [DIR_NORTHEAST] = ANIM_STANDING_WHEELIE_FRONT_WHEEL_NORTH,
};

static const u8 sAcroMovingWheelieDirectionAnimNums[] = {
    [DIR_NONE]      = ANIM_MOVING_WHEELIE_SOUTH,
    [DIR_SOUTH]     = ANIM_MOVING_WHEELIE_SOUTH,
    [DIR_NORTH]     = ANIM_MOVING_WHEELIE_NORTH,
    [DIR_WEST]      = ANIM_MOVING_WHEELIE_WEST,
    [DIR_EAST]      = ANIM_MOVING_WHEELIE_EAST,
    [DIR_SOUTHWEST] = ANIM_MOVING_WHEELIE_SOUTH,
    [DIR_SOUTHEAST] = ANIM_MOVING_WHEELIE_SOUTH,
    [DIR_NORTHWEST] = ANIM_MOVING_WHEELIE_NORTH,
    [DIR_NORTHEAST] = ANIM_MOVING_WHEELIE_NORTH,
};

static const u8 sFishingDirectionAnimNums[] = {
    [DIR_NONE]      = ANIM_TAKE_OUT_ROD_SOUTH,
    [DIR_SOUTH]     = ANIM_TAKE_OUT_ROD_SOUTH,
    [DIR_NORTH]     = ANIM_TAKE_OUT_ROD_NORTH,
    [DIR_WEST]      = ANIM_TAKE_OUT_ROD_WEST,
    [DIR_EAST]      = ANIM_TAKE_OUT_ROD_EAST,
    [DIR_SOUTHWEST] = ANIM_TAKE_OUT_ROD_SOUTH,
    [DIR_SOUTHEAST] = ANIM_TAKE_OUT_ROD_SOUTH,
    [DIR_NORTHWEST] = ANIM_TAKE_OUT_ROD_NORTH,
    [DIR_NORTHEAST] = ANIM_TAKE_OUT_ROD_NORTH,
};

static const u8 sFishingNoCatchDirectionAnimNums[] = {
    [DIR_NONE]      = ANIM_PUT_AWAY_ROD_SOUTH,
    [DIR_SOUTH]     = ANIM_PUT_AWAY_ROD_SOUTH,
    [DIR_NORTH]     = ANIM_PUT_AWAY_ROD_NORTH,
    [DIR_WEST]      = ANIM_PUT_AWAY_ROD_WEST,
    [DIR_EAST]      = ANIM_PUT_AWAY_ROD_EAST,
    [DIR_SOUTHWEST] = ANIM_PUT_AWAY_ROD_SOUTH,
    [DIR_SOUTHEAST] = ANIM_PUT_AWAY_ROD_SOUTH,
    [DIR_NORTHWEST] = ANIM_PUT_AWAY_ROD_NORTH,
    [DIR_NORTHEAST] = ANIM_PUT_AWAY_ROD_NORTH,
};

static const u8 sFishingBiteDirectionAnimNums[] = {
    [DIR_NONE]      = ANIM_HOOKED_POKEMON_SOUTH,
    [DIR_SOUTH]     = ANIM_HOOKED_POKEMON_SOUTH,
    [DIR_NORTH]     = ANIM_HOOKED_POKEMON_NORTH,
    [DIR_WEST]      = ANIM_HOOKED_POKEMON_WEST,
    [DIR_EAST]      = ANIM_HOOKED_POKEMON_EAST,
    [DIR_SOUTHWEST] = ANIM_HOOKED_POKEMON_SOUTH,
    [DIR_SOUTHEAST] = ANIM_HOOKED_POKEMON_SOUTH,
    [DIR_NORTHWEST] = ANIM_HOOKED_POKEMON_NORTH,
    [DIR_NORTHEAST] = ANIM_HOOKED_POKEMON_NORTH,
};

static const u8 sRunningDirectionAnimNums[] = {
    [DIR_NONE]      = ANIM_RUN_SOUTH,
    [DIR_SOUTH]     = ANIM_RUN_SOUTH,
    [DIR_NORTH]     = ANIM_RUN_NORTH,
    [DIR_WEST]      = ANIM_RUN_WEST,
    [DIR_EAST]      = ANIM_RUN_EAST,
    [DIR_SOUTHWEST] = ANIM_RUN_SOUTH,
    [DIR_SOUTHEAST] = ANIM_RUN_SOUTH,
    [DIR_NORTHWEST] = ANIM_RUN_NORTH,
    [DIR_NORTHEAST] = ANIM_RUN_NORTH,
};

static const u8 sTrainerFacingDirectionMovementTypes[] = {
    [DIR_NONE]      = MOVEMENT_TYPE_FACE_DOWN,
    [DIR_SOUTH]     = MOVEMENT_TYPE_FACE_DOWN,
    [DIR_NORTH]     = MOVEMENT_TYPE_FACE_UP,
    [DIR_WEST]      = MOVEMENT_TYPE_FACE_LEFT,
    [DIR_EAST]      = MOVEMENT_TYPE_FACE_RIGHT,
    [DIR_SOUTHWEST] = MOVEMENT_TYPE_FACE_DOWN,
    [DIR_SOUTHEAST] = MOVEMENT_TYPE_FACE_DOWN,
    [DIR_NORTHWEST] = MOVEMENT_TYPE_FACE_UP,
    [DIR_NORTHEAST] = MOVEMENT_TYPE_FACE_UP,
};

bool8 (*const gOppositeDirectionBlockedMetatileFuncs[])(u8) = {
    MetatileBehavior_IsSouthBlocked,
    MetatileBehavior_IsNorthBlocked,
    MetatileBehavior_IsWestBlocked,
    MetatileBehavior_IsEastBlocked
};

bool8 (*const gDirectionBlockedMetatileFuncs[])(u8) = {
    MetatileBehavior_IsNorthBlocked,
    MetatileBehavior_IsSouthBlocked,
    MetatileBehavior_IsEastBlocked,
    MetatileBehavior_IsWestBlocked
};

static const struct Coords16 sDirectionToVectors[] = {
    [DIR_NONE]      = { 0,  0},
    [DIR_SOUTH]     = { 0,  1},
    [DIR_NORTH]     = { 0, -1},
    [DIR_WEST]      = {-1,  0},
    [DIR_EAST]      = { 1,  0},
    [DIR_SOUTHWEST] = {-1,  1},
    [DIR_SOUTHEAST] = { 1,  1},
    [DIR_NORTHWEST] = {-1, -1},
    [DIR_NORTHEAST] = { 1, -1},
};

static const u8 sFaceDirectionMovementActions[] = {
    [DIR_NONE]  = MOVEMENT_ACTION_FACE_DOWN,
    [DIR_SOUTH] = MOVEMENT_ACTION_FACE_DOWN,
    [DIR_NORTH] = MOVEMENT_ACTION_FACE_UP,
    [DIR_WEST]  = MOVEMENT_ACTION_FACE_LEFT,
    [DIR_EAST]  = MOVEMENT_ACTION_FACE_RIGHT,
};

static const u8 sFaceDirectionFastMovementActions[] = {
    [DIR_NONE]  = MOVEMENT_ACTION_FACE_DOWN_FAST,
    [DIR_SOUTH] = MOVEMENT_ACTION_FACE_DOWN_FAST,
    [DIR_NORTH] = MOVEMENT_ACTION_FACE_UP_FAST,
    [DIR_WEST]  = MOVEMENT_ACTION_FACE_LEFT_FAST,
    [DIR_EAST]  = MOVEMENT_ACTION_FACE_RIGHT_FAST,
};

static const u8 sWalkSlowestMovementActions[] = {
    [DIR_NONE]  = MOVEMENT_ACTION_WALK_SLOWEST_DOWN,
    [DIR_SOUTH] = MOVEMENT_ACTION_WALK_SLOWEST_DOWN,
    [DIR_NORTH] = MOVEMENT_ACTION_WALK_SLOWEST_UP,
    [DIR_WEST]  = MOVEMENT_ACTION_WALK_SLOWEST_LEFT,
    [DIR_EAST]  = MOVEMENT_ACTION_WALK_SLOWEST_RIGHT,
};

static const u8 sWalkSlowerMovementActions[] = {
    [DIR_NONE]  = MOVEMENT_ACTION_WALK_SLOWER_DOWN,
    [DIR_SOUTH] = MOVEMENT_ACTION_WALK_SLOWER_DOWN,
    [DIR_NORTH] = MOVEMENT_ACTION_WALK_SLOWER_UP,
    [DIR_WEST]  = MOVEMENT_ACTION_WALK_SLOWER_LEFT,
    [DIR_EAST]  = MOVEMENT_ACTION_WALK_SLOWER_RIGHT,
};

static const u8 sWalkSlowMovementActions[] = {
    [DIR_NONE]  = MOVEMENT_ACTION_WALK_SLOW_DOWN,
    [DIR_SOUTH] = MOVEMENT_ACTION_WALK_SLOW_DOWN,
    [DIR_NORTH] = MOVEMENT_ACTION_WALK_SLOW_UP,
    [DIR_WEST]  = MOVEMENT_ACTION_WALK_SLOW_LEFT,
    [DIR_EAST]  = MOVEMENT_ACTION_WALK_SLOW_RIGHT,
};

static const u8 sWalkNormalMovementActions[] = {
    [DIR_NONE]  = MOVEMENT_ACTION_WALK_NORMAL_DOWN,
    [DIR_SOUTH] = MOVEMENT_ACTION_WALK_NORMAL_DOWN,
    [DIR_NORTH] = MOVEMENT_ACTION_WALK_NORMAL_UP,
    [DIR_WEST]  = MOVEMENT_ACTION_WALK_NORMAL_LEFT,
    [DIR_EAST]  = MOVEMENT_ACTION_WALK_NORMAL_RIGHT,
};

static const u8 sWalkFastMovementActions[] = {
    [DIR_NONE]  = MOVEMENT_ACTION_WALK_FAST_DOWN,
    [DIR_SOUTH] = MOVEMENT_ACTION_WALK_FAST_DOWN,
    [DIR_NORTH] = MOVEMENT_ACTION_WALK_FAST_UP,
    [DIR_WEST]  = MOVEMENT_ACTION_WALK_FAST_LEFT,
    [DIR_EAST]  = MOVEMENT_ACTION_WALK_FAST_RIGHT,
};

static const u8 sGlideMovementActions[] = {
    [DIR_NONE]  = MOVEMENT_ACTION_GLIDE_DOWN,
    [DIR_SOUTH] = MOVEMENT_ACTION_GLIDE_DOWN,
    [DIR_NORTH] = MOVEMENT_ACTION_GLIDE_UP,
    [DIR_WEST]  = MOVEMENT_ACTION_GLIDE_LEFT,
    [DIR_EAST]  = MOVEMENT_ACTION_GLIDE_RIGHT,
};

static const u8 sRideWaterCurrentMovementActions[] = {
    [DIR_NONE]  = MOVEMENT_ACTION_RIDE_WATER_CURRENT_DOWN,
    [DIR_SOUTH] = MOVEMENT_ACTION_RIDE_WATER_CURRENT_DOWN,
    [DIR_NORTH] = MOVEMENT_ACTION_RIDE_WATER_CURRENT_UP,
    [DIR_WEST]  = MOVEMENT_ACTION_RIDE_WATER_CURRENT_LEFT,
    [DIR_EAST]  = MOVEMENT_ACTION_RIDE_WATER_CURRENT_RIGHT,
};

static const u8 sWalkFasterMovementActions[] = {
    [DIR_NONE]  = MOVEMENT_ACTION_WALK_FASTER_DOWN,
    [DIR_SOUTH] = MOVEMENT_ACTION_WALK_FASTER_DOWN,
    [DIR_NORTH] = MOVEMENT_ACTION_WALK_FASTER_UP,
    [DIR_WEST]  = MOVEMENT_ACTION_WALK_FASTER_LEFT,
    [DIR_EAST]  = MOVEMENT_ACTION_WALK_FASTER_RIGHT,
};

static const u8 sSlideMovementActions[] = {
    [DIR_NONE]  = MOVEMENT_ACTION_SLIDE_DOWN,
    [DIR_SOUTH] = MOVEMENT_ACTION_SLIDE_DOWN,
    [DIR_NORTH] = MOVEMENT_ACTION_SLIDE_UP,
    [DIR_WEST]  = MOVEMENT_ACTION_SLIDE_LEFT,
    [DIR_EAST]  = MOVEMENT_ACTION_SLIDE_RIGHT,
};

static const u8 sPlayerRunMovementActions[] = {
    [DIR_NONE]  = MOVEMENT_ACTION_PLAYER_RUN_DOWN,
    [DIR_SOUTH] = MOVEMENT_ACTION_PLAYER_RUN_DOWN,
    [DIR_NORTH] = MOVEMENT_ACTION_PLAYER_RUN_UP,
    [DIR_WEST]  = MOVEMENT_ACTION_PLAYER_RUN_LEFT,
    [DIR_EAST]  = MOVEMENT_ACTION_PLAYER_RUN_RIGHT,
};

static const u8 sPlayerRunSlowMovementActions[] = {
    [DIR_NONE]  = MOVEMENT_ACTION_PLAYER_RUN_DOWN_SLOW,
    [DIR_SOUTH] = MOVEMENT_ACTION_PLAYER_RUN_DOWN_SLOW,
    [DIR_NORTH] = MOVEMENT_ACTION_PLAYER_RUN_UP_SLOW,
    [DIR_WEST]  = MOVEMENT_ACTION_PLAYER_RUN_LEFT_SLOW,
    [DIR_EAST]  = MOVEMENT_ACTION_PLAYER_RUN_RIGHT_SLOW,
};

static const u8 sSpinMovementActions[] = {
    [DIR_NONE]  = MOVEMENT_ACTION_SPIN_DOWN,
    [DIR_SOUTH] = MOVEMENT_ACTION_SPIN_DOWN,
    [DIR_NORTH] = MOVEMENT_ACTION_SPIN_UP,
    [DIR_WEST]  = MOVEMENT_ACTION_SPIN_LEFT,
    [DIR_EAST]  = MOVEMENT_ACTION_SPIN_RIGHT,
};

static const u8 sJump2MovementActions[] = {
    [DIR_NONE]  = MOVEMENT_ACTION_JUMP_2_DOWN,
    [DIR_SOUTH] = MOVEMENT_ACTION_JUMP_2_DOWN,
    [DIR_NORTH] = MOVEMENT_ACTION_JUMP_2_UP,
    [DIR_WEST]  = MOVEMENT_ACTION_JUMP_2_LEFT,
    [DIR_EAST]  = MOVEMENT_ACTION_JUMP_2_RIGHT,
};

static const u8 sJumpInPlaceMovementActions[] = {
    [DIR_NONE]  = MOVEMENT_ACTION_JUMP_IN_PLACE_DOWN,
    [DIR_SOUTH] = MOVEMENT_ACTION_JUMP_IN_PLACE_DOWN,
    [DIR_NORTH] = MOVEMENT_ACTION_JUMP_IN_PLACE_UP,
    [DIR_WEST]  = MOVEMENT_ACTION_JUMP_IN_PLACE_LEFT,
    [DIR_EAST]  = MOVEMENT_ACTION_JUMP_IN_PLACE_RIGHT,
};

static const u8 sJumpInPlaceTurnAroundMovementActions[] = {
    [DIR_NONE]  = MOVEMENT_ACTION_JUMP_IN_PLACE_UP_DOWN,
    [DIR_SOUTH] = MOVEMENT_ACTION_JUMP_IN_PLACE_UP_DOWN,
    [DIR_NORTH] = MOVEMENT_ACTION_JUMP_IN_PLACE_DOWN_UP,
    [DIR_WEST]  = MOVEMENT_ACTION_JUMP_IN_PLACE_RIGHT_LEFT,
    [DIR_EAST]  = MOVEMENT_ACTION_JUMP_IN_PLACE_LEFT_RIGHT,
};

static const u8 sJumpMovementActions[] = {
    [DIR_NONE]  = MOVEMENT_ACTION_JUMP_DOWN,
    [DIR_SOUTH] = MOVEMENT_ACTION_JUMP_DOWN,
    [DIR_NORTH] = MOVEMENT_ACTION_JUMP_UP,
    [DIR_WEST]  = MOVEMENT_ACTION_JUMP_LEFT,
    [DIR_EAST]  = MOVEMENT_ACTION_JUMP_RIGHT,
};

static const u8 sJumpSpecialMovementActions[] = {
    [DIR_NONE]  = MOVEMENT_ACTION_JUMP_SPECIAL_DOWN,
    [DIR_SOUTH] = MOVEMENT_ACTION_JUMP_SPECIAL_DOWN,
    [DIR_NORTH] = MOVEMENT_ACTION_JUMP_SPECIAL_UP,
    [DIR_WEST]  = MOVEMENT_ACTION_JUMP_SPECIAL_LEFT,
    [DIR_EAST]  = MOVEMENT_ACTION_JUMP_SPECIAL_RIGHT,
};

static const u8 sJumpSpecialWithEffectMovementActions[] = {
    [DIR_NONE]  = MOVEMENT_ACTION_JUMP_SPECIAL_WITH_EFFECT_DOWN,
    [DIR_SOUTH] = MOVEMENT_ACTION_JUMP_SPECIAL_WITH_EFFECT_DOWN,
    [DIR_NORTH] = MOVEMENT_ACTION_JUMP_SPECIAL_WITH_EFFECT_UP,
    [DIR_WEST]  = MOVEMENT_ACTION_JUMP_SPECIAL_WITH_EFFECT_LEFT,
    [DIR_EAST]  = MOVEMENT_ACTION_JUMP_SPECIAL_WITH_EFFECT_RIGHT,
};

static const u8 sWalkInPlaceSlowMovementActions[] = {
    [DIR_NONE]  = MOVEMENT_ACTION_WALK_IN_PLACE_SLOW_DOWN,
    [DIR_SOUTH] = MOVEMENT_ACTION_WALK_IN_PLACE_SLOW_DOWN,
    [DIR_NORTH] = MOVEMENT_ACTION_WALK_IN_PLACE_SLOW_UP,
    [DIR_WEST]  = MOVEMENT_ACTION_WALK_IN_PLACE_SLOW_LEFT,
    [DIR_EAST]  = MOVEMENT_ACTION_WALK_IN_PLACE_SLOW_RIGHT,
};

static const u8 sWalkInPlaceNormalMovementActions[] = {
    [DIR_NONE]  = MOVEMENT_ACTION_WALK_IN_PLACE_NORMAL_DOWN,
    [DIR_SOUTH] = MOVEMENT_ACTION_WALK_IN_PLACE_NORMAL_DOWN,
    [DIR_NORTH] = MOVEMENT_ACTION_WALK_IN_PLACE_NORMAL_UP,
    [DIR_WEST]  = MOVEMENT_ACTION_WALK_IN_PLACE_NORMAL_LEFT,
    [DIR_EAST]  = MOVEMENT_ACTION_WALK_IN_PLACE_NORMAL_RIGHT,
};

static const u8 sWalkInPlaceFastMovementActions[] = {
    [DIR_NONE]  = MOVEMENT_ACTION_WALK_IN_PLACE_FAST_DOWN,
    [DIR_SOUTH] = MOVEMENT_ACTION_WALK_IN_PLACE_FAST_DOWN,
    [DIR_NORTH] = MOVEMENT_ACTION_WALK_IN_PLACE_FAST_UP,
    [DIR_WEST]  = MOVEMENT_ACTION_WALK_IN_PLACE_FAST_LEFT,
    [DIR_EAST]  = MOVEMENT_ACTION_WALK_IN_PLACE_FAST_RIGHT,
};

static const u8 sWalkInPlaceFasterMovementActions[] = {
    [DIR_NONE]  = MOVEMENT_ACTION_WALK_IN_PLACE_FASTER_DOWN,
    [DIR_SOUTH] = MOVEMENT_ACTION_WALK_IN_PLACE_FASTER_DOWN,
    [DIR_NORTH] = MOVEMENT_ACTION_WALK_IN_PLACE_FASTER_UP,
    [DIR_WEST]  = MOVEMENT_ACTION_WALK_IN_PLACE_FASTER_LEFT,
    [DIR_EAST]  = MOVEMENT_ACTION_WALK_IN_PLACE_FASTER_RIGHT,
};

static const u8 sAcroWheelieFaceDirectionMovementActions[] = {
    [DIR_NONE]  = MOVEMENT_ACTION_ACRO_WHEELIE_FACE_DOWN,
    [DIR_SOUTH] = MOVEMENT_ACTION_ACRO_WHEELIE_FACE_DOWN,
    [DIR_NORTH] = MOVEMENT_ACTION_ACRO_WHEELIE_FACE_UP,
    [DIR_WEST]  = MOVEMENT_ACTION_ACRO_WHEELIE_FACE_LEFT,
    [DIR_EAST]  = MOVEMENT_ACTION_ACRO_WHEELIE_FACE_RIGHT,
};

static const u8 sAcroPopWheelieFaceDirectionMovementActions[] = {
    [DIR_NONE]  = MOVEMENT_ACTION_ACRO_POP_WHEELIE_DOWN,
    [DIR_SOUTH] = MOVEMENT_ACTION_ACRO_POP_WHEELIE_DOWN,
    [DIR_NORTH] = MOVEMENT_ACTION_ACRO_POP_WHEELIE_UP,
    [DIR_WEST]  = MOVEMENT_ACTION_ACRO_POP_WHEELIE_LEFT,
    [DIR_EAST]  = MOVEMENT_ACTION_ACRO_POP_WHEELIE_RIGHT,
};

static const u8 sAcroEndWheelieFaceDirectionMovementActions[] = {
    [DIR_NONE]  = MOVEMENT_ACTION_ACRO_END_WHEELIE_FACE_DOWN,
    [DIR_SOUTH] = MOVEMENT_ACTION_ACRO_END_WHEELIE_FACE_DOWN,
    [DIR_NORTH] = MOVEMENT_ACTION_ACRO_END_WHEELIE_FACE_UP,
    [DIR_WEST]  = MOVEMENT_ACTION_ACRO_END_WHEELIE_FACE_LEFT,
    [DIR_EAST]  = MOVEMENT_ACTION_ACRO_END_WHEELIE_FACE_RIGHT,
};

static const u8 sAcroWheelieHopFaceDirectionMovementActions[] = {
    [DIR_NONE]  = MOVEMENT_ACTION_ACRO_WHEELIE_HOP_FACE_DOWN,
    [DIR_SOUTH] = MOVEMENT_ACTION_ACRO_WHEELIE_HOP_FACE_DOWN,
    [DIR_NORTH] = MOVEMENT_ACTION_ACRO_WHEELIE_HOP_FACE_UP,
    [DIR_WEST]  = MOVEMENT_ACTION_ACRO_WHEELIE_HOP_FACE_LEFT,
    [DIR_EAST]  = MOVEMENT_ACTION_ACRO_WHEELIE_HOP_FACE_RIGHT,
};

static const u8 sAcroWheelieHopMovementActions[] = {
    [DIR_NONE]  = MOVEMENT_ACTION_ACRO_WHEELIE_HOP_DOWN,
    [DIR_SOUTH] = MOVEMENT_ACTION_ACRO_WHEELIE_HOP_DOWN,
    [DIR_NORTH] = MOVEMENT_ACTION_ACRO_WHEELIE_HOP_UP,
    [DIR_WEST]  = MOVEMENT_ACTION_ACRO_WHEELIE_HOP_LEFT,
    [DIR_EAST]  = MOVEMENT_ACTION_ACRO_WHEELIE_HOP_RIGHT,
};

static const u8 sAcroWheelieJumpMovementActions[] = {
    [DIR_NONE]  = MOVEMENT_ACTION_ACRO_WHEELIE_JUMP_DOWN,
    [DIR_SOUTH] = MOVEMENT_ACTION_ACRO_WHEELIE_JUMP_DOWN,
    [DIR_NORTH] = MOVEMENT_ACTION_ACRO_WHEELIE_JUMP_UP,
    [DIR_WEST]  = MOVEMENT_ACTION_ACRO_WHEELIE_JUMP_LEFT,
    [DIR_EAST]  = MOVEMENT_ACTION_ACRO_WHEELIE_JUMP_RIGHT,
};

static const u8 sAcroWheelieInPlaceMovementActions[] = {
    [DIR_NONE]  = MOVEMENT_ACTION_ACRO_WHEELIE_IN_PLACE_DOWN,
    [DIR_SOUTH] = MOVEMENT_ACTION_ACRO_WHEELIE_IN_PLACE_DOWN,
    [DIR_NORTH] = MOVEMENT_ACTION_ACRO_WHEELIE_IN_PLACE_UP,
    [DIR_WEST]  = MOVEMENT_ACTION_ACRO_WHEELIE_IN_PLACE_LEFT,
    [DIR_EAST]  = MOVEMENT_ACTION_ACRO_WHEELIE_IN_PLACE_RIGHT,
};

static const u8 sAcroPopWheelieMoveMovementActions[] = {
    [DIR_NONE]  = MOVEMENT_ACTION_ACRO_POP_WHEELIE_MOVE_DOWN,
    [DIR_SOUTH] = MOVEMENT_ACTION_ACRO_POP_WHEELIE_MOVE_DOWN,
    [DIR_NORTH] = MOVEMENT_ACTION_ACRO_POP_WHEELIE_MOVE_UP,
    [DIR_WEST]  = MOVEMENT_ACTION_ACRO_POP_WHEELIE_MOVE_LEFT,
    [DIR_EAST]  = MOVEMENT_ACTION_ACRO_POP_WHEELIE_MOVE_RIGHT,
};

static const u8 sAcroWheelieMoveMovementActions[] = {
    [DIR_NONE]  = MOVEMENT_ACTION_ACRO_WHEELIE_MOVE_DOWN,
    [DIR_SOUTH] = MOVEMENT_ACTION_ACRO_WHEELIE_MOVE_DOWN,
    [DIR_NORTH] = MOVEMENT_ACTION_ACRO_WHEELIE_MOVE_UP,
    [DIR_WEST]  = MOVEMENT_ACTION_ACRO_WHEELIE_MOVE_LEFT,
    [DIR_EAST]  = MOVEMENT_ACTION_ACRO_WHEELIE_MOVE_RIGHT,
};

static const u8 gOppositeDirections[] = {
    DIR_NORTH,
    DIR_SOUTH,
    DIR_EAST,
    DIR_WEST,
    DIR_NORTHEAST,
    DIR_NORTHWEST,
    DIR_SOUTHEAST,
    DIR_SOUTHWEST,
};

static const u8 sPlayerDirectionsForCopy[][4] = {
    {2, 1, 4, 3},
    {1, 2, 3, 4},
    {3, 4, 2, 1},
    {4, 3, 1, 2}
};

static const u8 sPlayerDirectionToCopyDirection[][4] = {
    {2, 1, 4, 3},
    {1, 2, 3, 4},
    {4, 3, 1, 2},
    {3, 4, 2, 1}
};

// ===== BEGIN src/data/object_events/movement_action_func_tables.h =====
static bool8 MovementAction_FaceDown_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_FaceUp_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_FaceLeft_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_FaceRight_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_PauseSpriteAnim(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_FaceDownFast_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_FaceUpFast_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_FaceLeftFast_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_FaceRightFast_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_WalkSlowerDown_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_WalkSlowerDown_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_WalkSlowerUp_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_WalkSlowerUp_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_WalkSlowerLeft_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_WalkSlowerLeft_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_WalkSlowerRight_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_WalkSlowerRight_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_WalkSlowDown_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_WalkSlowDown_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_WalkSlowUp_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_WalkSlowUp_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_WalkSlowLeft_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_WalkSlowLeft_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_WalkSlowRight_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_WalkSlowRight_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_WalkNormalDown_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_WalkNormalDown_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_WalkNormalUp_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_WalkNormalUp_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_WalkNormalLeft_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_WalkNormalLeft_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_WalkNormalRight_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_WalkNormalRight_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_WalkInPlaceSlowDown_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_WalkInPlaceSlowUp_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_WalkInPlaceSlowLeft_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_WalkInPlaceSlowRight_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_WalkInPlaceSlow_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_WalkInPlaceNormalDown_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_WalkInPlaceNormalUp_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_WalkInPlaceNormalLeft_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_WalkInPlaceNormalRight_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_WalkInPlace_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_WalkInPlaceFastDown_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_WalkInPlaceFastUp_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_WalkInPlaceFastLeft_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_WalkInPlaceFastRight_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_WalkInPlaceFasterDown_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_WalkInPlaceFasterUp_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_WalkInPlaceFasterLeft_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_WalkInPlaceFasterRight_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_Jump2Down_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_Jump2Down_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_Jump2Up_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_Jump2Up_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_Jump2Left_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_Jump2Left_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_Jump2Right_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_Jump2Right_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_Delay1_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_Delay2_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_Delay4_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_Delay8_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_Delay16_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_Delay_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_WalkFastDown_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_WalkFastDown_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_WalkFastUp_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_WalkFastUp_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_WalkFastLeft_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_WalkFastLeft_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_WalkFastRight_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_WalkFastRight_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_RideWaterCurrentDown_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_RideWaterCurrentDown_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_RideWaterCurrentUp_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_RideWaterCurrentUp_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_RideWaterCurrentLeft_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_RideWaterCurrentLeft_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_RideWaterCurrentRight_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_RideWaterCurrentRight_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_WalkFasterDown_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_WalkFasterDown_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_WalkFasterUp_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_WalkFasterUp_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_WalkFasterLeft_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_WalkFasterLeft_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_WalkFasterRight_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_WalkFasterRight_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_SlideDown_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_SlideDown_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_SlideUp_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_SlideUp_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_SlideLeft_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_SlideLeft_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_SlideRight_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_SlideRight_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_PlayerRunDown_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_PlayerRunDown_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_PlayerRunUp_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_PlayerRunUp_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_PlayerRunLeft_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_PlayerRunLeft_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_PlayerRunRight_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_PlayerRunRight_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_RunDownSlow_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_RunDownSlow_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_RunUpSlow_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_RunUpSlow_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_RunLeftSlow_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_RunLeftSlow_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_RunRightSlow_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_RunRightSlow_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_StartAnimInDirection_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_JumpSpecialDown_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_JumpSpecialDown_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_JumpSpecialUp_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_JumpSpecialUp_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_JumpSpecialLeft_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_JumpSpecialLeft_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_JumpSpecialRight_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_JumpSpecialRight_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_FacePlayer_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_FaceAwayPlayer_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_LockFacingDirection_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_UnlockFacingDirection_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_JumpDown_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_JumpDown_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_JumpUp_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_JumpUp_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_JumpLeft_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_JumpLeft_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_JumpRight_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_JumpRight_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_JumpInPlaceDown_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_JumpInPlaceDown_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_JumpInPlaceUp_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_JumpInPlaceUp_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_JumpInPlaceLeft_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_JumpInPlaceLeft_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_JumpInPlaceRight_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_JumpInPlaceRight_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_JumpInPlaceDownUp_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_JumpInPlaceDownUp_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_JumpInPlaceUpDown_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_JumpInPlaceUpDown_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_JumpInPlaceLeftRight_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_JumpInPlaceLeftRight_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_JumpInPlaceRightLeft_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_JumpInPlaceRightLeft_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_FaceOriginalDirection_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_NurseJoyBowDown_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_EnableJumpLandingGroundEffect_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_DisableJumpLandingGroundEffect_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_DisableAnimation_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_RestoreAnimation_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_SetInvisible_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_SetVisible_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_EmoteExclamationMark_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_EmoteQuestionMark_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_EmoteX_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_EmoteDoubleExclamationMark_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_EmoteSmile_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_RevealTrainer_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_RevealTrainer_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_RockSmashBreak_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_RockSmashBreak_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_RockSmashBreak_Step2(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_CutTree_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_CutTree_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_CutTree_Step2(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_SetFixedPriority_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_ClearFixedPriority_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_InitAffineAnim_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_ClearAffineAnim_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_WalkDownStartAffine_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_WalkDownStartAffine_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_WalkDownAffine_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_WalkDownAffine_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_AcroWheelieFaceDown_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_AcroWheelieFaceUp_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_AcroWheelieFaceLeft_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_AcroWheelieFaceRight_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_AcroPopWheelieDown_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_AcroPopWheelieDown_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_AcroPopWheelieUp_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_AcroPopWheelieUp_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_AcroPopWheelieLeft_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_AcroPopWheelieLeft_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_AcroPopWheelieRight_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_AcroPopWheelieRight_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_AcroEndWheelieFaceDown_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_AcroEndWheelieFaceUp_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_AcroEndWheelieFaceLeft_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_AcroEndWheelieFaceRight_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_UnusedAcroActionDown_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_UnusedAcroActionUp_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_UnusedAcroActionLeft_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_UnusedAcroActionRight_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_AcroWheelieHopFaceDown_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_AcroWheelieHopFaceDown_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_AcroWheelieHopFaceUp_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_AcroWheelieHopFaceUp_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_AcroWheelieHopFaceLeft_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_AcroWheelieHopFaceLeft_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_AcroWheelieHopFaceRight_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_AcroWheelieHopFaceRight_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_AcroWheelieHopDown_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_AcroWheelieHopDown_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_AcroWheelieHopUp_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_AcroWheelieHopUp_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_AcroWheelieHopLeft_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_AcroWheelieHopLeft_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_AcroWheelieHopRight_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_AcroWheelieHopRight_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_AcroWheelieJumpDown_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_AcroWheelieJumpDown_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_AcroWheelieJumpUp_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_AcroWheelieJumpUp_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_AcroWheelieJumpLeft_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_AcroWheelieJumpLeft_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_AcroWheelieJumpRight_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_AcroWheelieJumpRight_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_AcroWheelieInPlaceDown_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_AcroWheelieInPlaceUp_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_AcroWheelieInPlaceLeft_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_AcroWheelieInPlaceRight_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_AcroPopWheelieMoveDown_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_AcroPopWheelieMoveDown_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_AcroPopWheelieMoveUp_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_AcroPopWheelieMoveUp_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_AcroPopWheelieMoveLeft_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_AcroPopWheelieMoveLeft_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_AcroPopWheelieMoveRight_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_AcroPopWheelieMoveRight_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_AcroWheelieMoveDown_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_AcroWheelieMoveDown_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_AcroWheelieMoveUp_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_AcroWheelieMoveUp_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_AcroWheelieMoveLeft_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_AcroWheelieMoveLeft_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_AcroWheelieMoveRight_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_AcroWheelieMoveRight_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_SpinDown_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_SpinDown_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_SpinUp_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_SpinUp_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_SpinLeft_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_SpinLeft_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_SpinRight_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_SpinRight_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_RaiseHand_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_RaiseHandAndStop_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_RaiseHandAndJump_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_RaiseHandAndSwim_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_WalkSlowestDown_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_WalkSlowestDown_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_WalkSlowestUp_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_WalkSlowestUp_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_WalkSlowestLeft_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_WalkSlowestLeft_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_WalkSlowestRight_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_WalkSlowestRight_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_ShakeHeadOrWalkInPlace_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_ShakeHeadOrWalkInPlace_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_GlideDown_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_GlideDown_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_GlideUp_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_GlideUp_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_GlideLeft_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_GlideLeft_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_GlideRight_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_GlideRight_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_FlyUp_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_FlyUp_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_FlyUp_Step2(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_FlyDown_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_FlyDown_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_JumpSpecialWithEffectDown_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_JumpSpecialWithEffectDown_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_JumpSpecialWithEffectUp_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_JumpSpecialWithEffectUp_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_JumpSpecialWithEffectLeft_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_JumpSpecialWithEffectLeft_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_JumpSpecialWithEffectRight_Step0(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_JumpSpecialWithEffectRight_Step1(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_WaitSpriteAnim(struct ObjectEvent *, struct Sprite *);
static bool8 MovementAction_Finish(struct ObjectEvent *, struct Sprite *);

static bool8 (*const sMovementActionFuncs_FaceDown[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_FaceUp[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_FaceLeft[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_FaceRight[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_FaceDownFast[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_FaceUpFast[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_FaceLeftFast[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_FaceRightFast[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_WalkSlowerDown[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_WalkSlowerUp[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_WalkSlowerLeft[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_WalkSlowerRight[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_WalkSlowUp[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_WalkSlowDown[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_WalkSlowLeft[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_WalkSlowRight[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_WalkNormalDown[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_WalkNormalUp[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_WalkNormalLeft[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_WalkNormalRight[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_Jump2Down[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_Jump2Up[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_Jump2Left[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_Jump2Right[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_Delay1[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_Delay2[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_Delay4[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_Delay8[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_Delay16[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_WalkFastDown[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_WalkFastUp[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_WalkFastLeft[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_WalkFastRight[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_WalkInPlaceSlowDown[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_WalkInPlaceSlowUp[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_WalkInPlaceSlowLeft[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_WalkInPlaceSlowRight[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_WalkInPlaceNormalDown[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_WalkInPlaceNormalUp[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_WalkInPlaceNormalLeft[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_WalkInPlaceNormalRight[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_WalkInPlaceFastDown[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_WalkInPlaceFastUp[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_WalkInPlaceFastLeft[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_WalkInPlaceFastRight[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_WalkInPlaceFasterDown[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_WalkInPlaceFasterUp[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_WalkInPlaceFasterLeft[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_WalkInPlaceFasterRight[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_RideWaterCurrentDown[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_RideWaterCurrentUp[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_RideWaterCurrentLeft[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_RideWaterCurrentRight[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_WalkFasterDown[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_WalkFasterUp[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_WalkFasterLeft[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_WalkFasterRight[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_SlideDown[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_SlideUp[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_SlideLeft[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_SlideRight[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_PlayerRunDown[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_PlayerRunUp[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_PlayerRunLeft[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_PlayerRunRight[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_PlayerRunDownSlow[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_PlayerRunUpSlow[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_PlayerRunLeftSlow[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_PlayerRunRightSlow[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_StartAnimInDirection[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_JumpSpecialDown[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_JumpSpecialUp[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_JumpSpecialLeft[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_JumpSpecialRight[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_FacePlayer[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_FaceAwayPlayer[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_LockFacingDirection[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_UnlockFacingDirection[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_JumpDown[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_JumpUp[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_JumpLeft[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_JumpRight[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_JumpInPlaceDown[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_JumpInPlaceUp[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_JumpInPlaceLeft[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_JumpInPlaceRight[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_JumpInPlaceDownUp[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_JumpInPlaceUpDown[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_JumpInPlaceLeftRight[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_JumpInPlaceRightLeft[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_FaceOriginalDirection[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_NurseJoyBowDown[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_EnableJumpLandingGroundEffect[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_DisableJumpLandingGroundEffect[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_DisableAnimation[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_RestoreAnimation[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_SetInvisible[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_SetVisible[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_EmoteExclamationMark[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_EmoteQuestionMark[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_EmoteX[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_EmoteDoubleExclMark[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_EmoteSmile[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_RevealTrainer[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_RockSmashBreak[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_CutTree[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_SetFixedPriority[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_ClearFixedPriority[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_InitAffineAnim[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_ClearAffineAnim[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_WalkDownStartAffine[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_WalkDownAffine[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_AcroWheelieFaceDown[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_AcroWheelieFaceUp[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_AcroWheelieFaceLeft[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_AcroWheelieFaceRight[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_AcroPopWheelieDown[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_AcroPopWheelieUp[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_AcroPopWheelieLeft[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_AcroPopWheelieRight[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_AcroEndWheelieFaceDown[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_AcroEndWheelieFaceUp[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_AcroEndWheelieFaceLeft[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_AcroEndWheelieFaceRight[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_AcroWheelieHopFaceDown[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_AcroWheelieHopFaceUp[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_AcroWheelieHopFaceLeft[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_AcroWheelieHopFaceRight[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_AcroWheelieHopDown[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_AcroWheelieHopUp[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_AcroWheelieHopLeft[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_AcroWheelieHopRight[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_AcroWheelieJumpDown[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_AcroWheelieJumpUp[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_AcroWheelieJumpLeft[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_AcroWheelieJumpRight[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_AcroWheelieInPlaceDown[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_AcroWheelieInPlaceUp[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_AcroWheelieInPlaceLeft[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_AcroWheelieInPlaceRight[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_AcroPopWheelieMoveDown[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_AcroPopWheelieMoveUp[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_AcroPopWheelieMoveLeft[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_AcroPopWheelieMoveRight[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_AcroWheelieMoveDown[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_AcroWheelieMoveUp[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_AcroWheelieMoveLeft[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_AcroWheelieMoveRight[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_SpinDown[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_SpinUp[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_SpinLeft[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_SpinRight[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_RaiseHandAndStop[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_RaiseHandAndJump[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_RaiseHandAndSwim[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_WalkSlowestDown[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_WalkSlowestUp[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_WalkSlowestLeft[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_WalkSlowestRight[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_ShakeHeadOrWalkInPlace[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_GlideDown[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_GlideUp[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_GlideLeft[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_GlideRight[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_FlyUp[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_FlyDown[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_JumpSpecialWithEffectDown[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_JumpSpecialWithEffectUp[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_JumpSpecialWithEffectLeft[])(struct ObjectEvent *, struct Sprite *);
static bool8 (*const sMovementActionFuncs_JumpSpecialWithEffectRight[])(struct ObjectEvent *, struct Sprite *);

static u8 GetMoveDirectionFastAnimNum(u8 direction);
static u8 GetMoveDirectionFasterAnimNum(u8 direction);
static u8 GetMoveDirectionFastestAnimNum(u8 direction);

static bool8 (*const *const sMovementActionFuncs[])(struct ObjectEvent *, struct Sprite *) = {
    [MOVEMENT_ACTION_FACE_DOWN]                          = sMovementActionFuncs_FaceDown,
    [MOVEMENT_ACTION_FACE_UP]                            = sMovementActionFuncs_FaceUp,
    [MOVEMENT_ACTION_FACE_LEFT]                          = sMovementActionFuncs_FaceLeft,
    [MOVEMENT_ACTION_FACE_RIGHT]                         = sMovementActionFuncs_FaceRight,
    [MOVEMENT_ACTION_FACE_DOWN_FAST]                     = sMovementActionFuncs_FaceDownFast,
    [MOVEMENT_ACTION_FACE_UP_FAST]                       = sMovementActionFuncs_FaceUpFast,
    [MOVEMENT_ACTION_FACE_LEFT_FAST]                     = sMovementActionFuncs_FaceLeftFast,
    [MOVEMENT_ACTION_FACE_RIGHT_FAST]                    = sMovementActionFuncs_FaceRightFast,
    [MOVEMENT_ACTION_WALK_SLOWER_DOWN]                   = sMovementActionFuncs_WalkSlowerDown,
    [MOVEMENT_ACTION_WALK_SLOWER_UP]                     = sMovementActionFuncs_WalkSlowerUp,
    [MOVEMENT_ACTION_WALK_SLOWER_LEFT]                   = sMovementActionFuncs_WalkSlowerLeft,
    [MOVEMENT_ACTION_WALK_SLOWER_RIGHT]                  = sMovementActionFuncs_WalkSlowerRight,
    [MOVEMENT_ACTION_WALK_SLOW_DOWN]                     = sMovementActionFuncs_WalkSlowDown,
    [MOVEMENT_ACTION_WALK_SLOW_UP]                       = sMovementActionFuncs_WalkSlowUp,
    [MOVEMENT_ACTION_WALK_SLOW_LEFT]                     = sMovementActionFuncs_WalkSlowLeft,
    [MOVEMENT_ACTION_WALK_SLOW_RIGHT]                    = sMovementActionFuncs_WalkSlowRight,
    [MOVEMENT_ACTION_WALK_NORMAL_DOWN]                   = sMovementActionFuncs_WalkNormalDown,
    [MOVEMENT_ACTION_WALK_NORMAL_UP]                     = sMovementActionFuncs_WalkNormalUp,
    [MOVEMENT_ACTION_WALK_NORMAL_LEFT]                   = sMovementActionFuncs_WalkNormalLeft,
    [MOVEMENT_ACTION_WALK_NORMAL_RIGHT]                  = sMovementActionFuncs_WalkNormalRight,
    [MOVEMENT_ACTION_JUMP_2_DOWN]                        = sMovementActionFuncs_Jump2Down,
    [MOVEMENT_ACTION_JUMP_2_UP]                          = sMovementActionFuncs_Jump2Up,
    [MOVEMENT_ACTION_JUMP_2_LEFT]                        = sMovementActionFuncs_Jump2Left,
    [MOVEMENT_ACTION_JUMP_2_RIGHT]                       = sMovementActionFuncs_Jump2Right,
    [MOVEMENT_ACTION_DELAY_1]                            = sMovementActionFuncs_Delay1,
    [MOVEMENT_ACTION_DELAY_2]                            = sMovementActionFuncs_Delay2,
    [MOVEMENT_ACTION_DELAY_4]                            = sMovementActionFuncs_Delay4,
    [MOVEMENT_ACTION_DELAY_8]                            = sMovementActionFuncs_Delay8,
    [MOVEMENT_ACTION_DELAY_16]                           = sMovementActionFuncs_Delay16,
    [MOVEMENT_ACTION_WALK_FAST_DOWN]                     = sMovementActionFuncs_WalkFastDown,
    [MOVEMENT_ACTION_WALK_FAST_UP]                       = sMovementActionFuncs_WalkFastUp,
    [MOVEMENT_ACTION_WALK_FAST_LEFT]                     = sMovementActionFuncs_WalkFastLeft,
    [MOVEMENT_ACTION_WALK_FAST_RIGHT]                    = sMovementActionFuncs_WalkFastRight,
    [MOVEMENT_ACTION_WALK_IN_PLACE_SLOW_DOWN]            = sMovementActionFuncs_WalkInPlaceSlowDown,
    [MOVEMENT_ACTION_WALK_IN_PLACE_SLOW_UP]              = sMovementActionFuncs_WalkInPlaceSlowUp,
    [MOVEMENT_ACTION_WALK_IN_PLACE_SLOW_LEFT]            = sMovementActionFuncs_WalkInPlaceSlowLeft,
    [MOVEMENT_ACTION_WALK_IN_PLACE_SLOW_RIGHT]           = sMovementActionFuncs_WalkInPlaceSlowRight,
    [MOVEMENT_ACTION_WALK_IN_PLACE_NORMAL_DOWN]          = sMovementActionFuncs_WalkInPlaceNormalDown,
    [MOVEMENT_ACTION_WALK_IN_PLACE_NORMAL_UP]            = sMovementActionFuncs_WalkInPlaceNormalUp,
    [MOVEMENT_ACTION_WALK_IN_PLACE_NORMAL_LEFT]          = sMovementActionFuncs_WalkInPlaceNormalLeft,
    [MOVEMENT_ACTION_WALK_IN_PLACE_NORMAL_RIGHT]         = sMovementActionFuncs_WalkInPlaceNormalRight,
    [MOVEMENT_ACTION_WALK_IN_PLACE_FAST_DOWN]            = sMovementActionFuncs_WalkInPlaceFastDown,
    [MOVEMENT_ACTION_WALK_IN_PLACE_FAST_UP]              = sMovementActionFuncs_WalkInPlaceFastUp,
    [MOVEMENT_ACTION_WALK_IN_PLACE_FAST_LEFT]            = sMovementActionFuncs_WalkInPlaceFastLeft,
    [MOVEMENT_ACTION_WALK_IN_PLACE_FAST_RIGHT]           = sMovementActionFuncs_WalkInPlaceFastRight,
    [MOVEMENT_ACTION_WALK_IN_PLACE_FASTER_DOWN]          = sMovementActionFuncs_WalkInPlaceFasterDown,
    [MOVEMENT_ACTION_WALK_IN_PLACE_FASTER_UP]            = sMovementActionFuncs_WalkInPlaceFasterUp,
    [MOVEMENT_ACTION_WALK_IN_PLACE_FASTER_LEFT]          = sMovementActionFuncs_WalkInPlaceFasterLeft,
    [MOVEMENT_ACTION_WALK_IN_PLACE_FASTER_RIGHT]         = sMovementActionFuncs_WalkInPlaceFasterRight,
    [MOVEMENT_ACTION_RIDE_WATER_CURRENT_DOWN]            = sMovementActionFuncs_RideWaterCurrentDown,
    [MOVEMENT_ACTION_RIDE_WATER_CURRENT_UP]              = sMovementActionFuncs_RideWaterCurrentUp,
    [MOVEMENT_ACTION_RIDE_WATER_CURRENT_LEFT]            = sMovementActionFuncs_RideWaterCurrentLeft,
    [MOVEMENT_ACTION_RIDE_WATER_CURRENT_RIGHT]           = sMovementActionFuncs_RideWaterCurrentRight,
    [MOVEMENT_ACTION_WALK_FASTER_DOWN]                   = sMovementActionFuncs_WalkFasterDown,
    [MOVEMENT_ACTION_WALK_FASTER_UP]                     = sMovementActionFuncs_WalkFasterUp,
    [MOVEMENT_ACTION_WALK_FASTER_LEFT]                   = sMovementActionFuncs_WalkFasterLeft,
    [MOVEMENT_ACTION_WALK_FASTER_RIGHT]                  = sMovementActionFuncs_WalkFasterRight,
    [MOVEMENT_ACTION_SLIDE_DOWN]                         = sMovementActionFuncs_SlideDown,
    [MOVEMENT_ACTION_SLIDE_UP]                           = sMovementActionFuncs_SlideUp,
    [MOVEMENT_ACTION_SLIDE_LEFT]                         = sMovementActionFuncs_SlideLeft,
    [MOVEMENT_ACTION_SLIDE_RIGHT]                        = sMovementActionFuncs_SlideRight,
    [MOVEMENT_ACTION_PLAYER_RUN_DOWN]                    = sMovementActionFuncs_PlayerRunDown,
    [MOVEMENT_ACTION_PLAYER_RUN_UP]                      = sMovementActionFuncs_PlayerRunUp,
    [MOVEMENT_ACTION_PLAYER_RUN_LEFT]                    = sMovementActionFuncs_PlayerRunLeft,
    [MOVEMENT_ACTION_PLAYER_RUN_RIGHT]                   = sMovementActionFuncs_PlayerRunRight,
    [MOVEMENT_ACTION_PLAYER_RUN_DOWN_SLOW]               = sMovementActionFuncs_PlayerRunDownSlow,
    [MOVEMENT_ACTION_PLAYER_RUN_UP_SLOW]                 = sMovementActionFuncs_PlayerRunUpSlow,
    [MOVEMENT_ACTION_PLAYER_RUN_LEFT_SLOW]               = sMovementActionFuncs_PlayerRunLeftSlow,
    [MOVEMENT_ACTION_PLAYER_RUN_RIGHT_SLOW]              = sMovementActionFuncs_PlayerRunRightSlow,
    [MOVEMENT_ACTION_START_ANIM_IN_DIRECTION]            = sMovementActionFuncs_StartAnimInDirection,
    [MOVEMENT_ACTION_JUMP_SPECIAL_DOWN]                  = sMovementActionFuncs_JumpSpecialDown,
    [MOVEMENT_ACTION_JUMP_SPECIAL_UP]                    = sMovementActionFuncs_JumpSpecialUp,
    [MOVEMENT_ACTION_JUMP_SPECIAL_LEFT]                  = sMovementActionFuncs_JumpSpecialLeft,
    [MOVEMENT_ACTION_JUMP_SPECIAL_RIGHT]                 = sMovementActionFuncs_JumpSpecialRight,
    [MOVEMENT_ACTION_FACE_PLAYER]                        = sMovementActionFuncs_FacePlayer,
    [MOVEMENT_ACTION_FACE_AWAY_PLAYER]                   = sMovementActionFuncs_FaceAwayPlayer,
    [MOVEMENT_ACTION_LOCK_FACING_DIRECTION]              = sMovementActionFuncs_LockFacingDirection,
    [MOVEMENT_ACTION_UNLOCK_FACING_DIRECTION]            = sMovementActionFuncs_UnlockFacingDirection,
    [MOVEMENT_ACTION_JUMP_DOWN]                          = sMovementActionFuncs_JumpDown,
    [MOVEMENT_ACTION_JUMP_UP]                            = sMovementActionFuncs_JumpUp,
    [MOVEMENT_ACTION_JUMP_LEFT]                          = sMovementActionFuncs_JumpLeft,
    [MOVEMENT_ACTION_JUMP_RIGHT]                         = sMovementActionFuncs_JumpRight,
    [MOVEMENT_ACTION_JUMP_IN_PLACE_DOWN]                 = sMovementActionFuncs_JumpInPlaceDown,
    [MOVEMENT_ACTION_JUMP_IN_PLACE_UP]                   = sMovementActionFuncs_JumpInPlaceUp,
    [MOVEMENT_ACTION_JUMP_IN_PLACE_LEFT]                 = sMovementActionFuncs_JumpInPlaceLeft,
    [MOVEMENT_ACTION_JUMP_IN_PLACE_RIGHT]                = sMovementActionFuncs_JumpInPlaceRight,
    [MOVEMENT_ACTION_JUMP_IN_PLACE_DOWN_UP]              = sMovementActionFuncs_JumpInPlaceDownUp,
    [MOVEMENT_ACTION_JUMP_IN_PLACE_UP_DOWN]              = sMovementActionFuncs_JumpInPlaceUpDown,
    [MOVEMENT_ACTION_JUMP_IN_PLACE_LEFT_RIGHT]           = sMovementActionFuncs_JumpInPlaceLeftRight,
    [MOVEMENT_ACTION_JUMP_IN_PLACE_RIGHT_LEFT]           = sMovementActionFuncs_JumpInPlaceRightLeft,
    [MOVEMENT_ACTION_FACE_ORIGINAL_DIRECTION]            = sMovementActionFuncs_FaceOriginalDirection,
    [MOVEMENT_ACTION_NURSE_JOY_BOW_DOWN]                 = sMovementActionFuncs_NurseJoyBowDown,
    [MOVEMENT_ACTION_ENABLE_JUMP_LANDING_GROUND_EFFECT]  = sMovementActionFuncs_EnableJumpLandingGroundEffect,
    [MOVEMENT_ACTION_DISABLE_JUMP_LANDING_GROUND_EFFECT] = sMovementActionFuncs_DisableJumpLandingGroundEffect,
    [MOVEMENT_ACTION_DISABLE_ANIMATION]                  = sMovementActionFuncs_DisableAnimation,
    [MOVEMENT_ACTION_RESTORE_ANIMATION]                  = sMovementActionFuncs_RestoreAnimation,
    [MOVEMENT_ACTION_SET_INVISIBLE]                      = sMovementActionFuncs_SetInvisible,
    [MOVEMENT_ACTION_SET_VISIBLE]                        = sMovementActionFuncs_SetVisible,
    [MOVEMENT_ACTION_EMOTE_EXCLAMATION_MARK]             = sMovementActionFuncs_EmoteExclamationMark,
    [MOVEMENT_ACTION_EMOTE_QUESTION_MARK]                = sMovementActionFuncs_EmoteQuestionMark,
    [MOVEMENT_ACTION_EMOTE_X]                            = sMovementActionFuncs_EmoteX,
    [MOVEMENT_ACTION_EMOTE_DOUBLE_EXCL_MARK]             = sMovementActionFuncs_EmoteDoubleExclMark,
    [MOVEMENT_ACTION_EMOTE_SMILE]                        = sMovementActionFuncs_EmoteSmile,
    [MOVEMENT_ACTION_REVEAL_TRAINER]                     = sMovementActionFuncs_RevealTrainer,
    [MOVEMENT_ACTION_ROCK_SMASH_BREAK]                   = sMovementActionFuncs_RockSmashBreak,
    [MOVEMENT_ACTION_CUT_TREE]                           = sMovementActionFuncs_CutTree,
    [MOVEMENT_ACTION_SET_FIXED_PRIORITY]                 = sMovementActionFuncs_SetFixedPriority,
    [MOVEMENT_ACTION_CLEAR_FIXED_PRIORITY]               = sMovementActionFuncs_ClearFixedPriority,
    [MOVEMENT_ACTION_INIT_AFFINE_ANIM]                   = sMovementActionFuncs_InitAffineAnim,
    [MOVEMENT_ACTION_CLEAR_AFFINE_ANIM]                  = sMovementActionFuncs_ClearAffineAnim,
    [MOVEMENT_ACTION_WALK_DOWN_START_AFFINE]             = sMovementActionFuncs_WalkDownStartAffine,
    [MOVEMENT_ACTION_WALK_DOWN_AFFINE]                   = sMovementActionFuncs_WalkDownAffine,
    [MOVEMENT_ACTION_ACRO_WHEELIE_FACE_DOWN]             = sMovementActionFuncs_AcroWheelieFaceDown,
    [MOVEMENT_ACTION_ACRO_WHEELIE_FACE_UP]               = sMovementActionFuncs_AcroWheelieFaceUp,
    [MOVEMENT_ACTION_ACRO_WHEELIE_FACE_LEFT]             = sMovementActionFuncs_AcroWheelieFaceLeft,
    [MOVEMENT_ACTION_ACRO_WHEELIE_FACE_RIGHT]            = sMovementActionFuncs_AcroWheelieFaceRight,
    [MOVEMENT_ACTION_ACRO_POP_WHEELIE_DOWN]              = sMovementActionFuncs_AcroPopWheelieDown,
    [MOVEMENT_ACTION_ACRO_POP_WHEELIE_UP]                = sMovementActionFuncs_AcroPopWheelieUp,
    [MOVEMENT_ACTION_ACRO_POP_WHEELIE_LEFT]              = sMovementActionFuncs_AcroPopWheelieLeft,
    [MOVEMENT_ACTION_ACRO_POP_WHEELIE_RIGHT]             = sMovementActionFuncs_AcroPopWheelieRight,
    [MOVEMENT_ACTION_ACRO_END_WHEELIE_FACE_DOWN]         = sMovementActionFuncs_AcroEndWheelieFaceDown,
    [MOVEMENT_ACTION_ACRO_END_WHEELIE_FACE_UP]           = sMovementActionFuncs_AcroEndWheelieFaceUp,
    [MOVEMENT_ACTION_ACRO_END_WHEELIE_FACE_LEFT]         = sMovementActionFuncs_AcroEndWheelieFaceLeft,
    [MOVEMENT_ACTION_ACRO_END_WHEELIE_FACE_RIGHT]        = sMovementActionFuncs_AcroEndWheelieFaceRight,
    [MOVEMENT_ACTION_ACRO_WHEELIE_HOP_FACE_DOWN]         = sMovementActionFuncs_AcroWheelieHopFaceDown,
    [MOVEMENT_ACTION_ACRO_WHEELIE_HOP_FACE_UP]           = sMovementActionFuncs_AcroWheelieHopFaceUp,
    [MOVEMENT_ACTION_ACRO_WHEELIE_HOP_FACE_LEFT]         = sMovementActionFuncs_AcroWheelieHopFaceLeft,
    [MOVEMENT_ACTION_ACRO_WHEELIE_HOP_FACE_RIGHT]        = sMovementActionFuncs_AcroWheelieHopFaceRight,
    [MOVEMENT_ACTION_ACRO_WHEELIE_HOP_DOWN]              = sMovementActionFuncs_AcroWheelieHopDown,
    [MOVEMENT_ACTION_ACRO_WHEELIE_HOP_UP]                = sMovementActionFuncs_AcroWheelieHopUp,
    [MOVEMENT_ACTION_ACRO_WHEELIE_HOP_LEFT]              = sMovementActionFuncs_AcroWheelieHopLeft,
    [MOVEMENT_ACTION_ACRO_WHEELIE_HOP_RIGHT]             = sMovementActionFuncs_AcroWheelieHopRight,
    [MOVEMENT_ACTION_ACRO_WHEELIE_JUMP_DOWN]             = sMovementActionFuncs_AcroWheelieJumpDown,
    [MOVEMENT_ACTION_ACRO_WHEELIE_JUMP_UP]               = sMovementActionFuncs_AcroWheelieJumpUp,
    [MOVEMENT_ACTION_ACRO_WHEELIE_JUMP_LEFT]             = sMovementActionFuncs_AcroWheelieJumpLeft,
    [MOVEMENT_ACTION_ACRO_WHEELIE_JUMP_RIGHT]            = sMovementActionFuncs_AcroWheelieJumpRight,
    [MOVEMENT_ACTION_ACRO_WHEELIE_IN_PLACE_DOWN]         = sMovementActionFuncs_AcroWheelieInPlaceDown,
    [MOVEMENT_ACTION_ACRO_WHEELIE_IN_PLACE_UP]           = sMovementActionFuncs_AcroWheelieInPlaceUp,
    [MOVEMENT_ACTION_ACRO_WHEELIE_IN_PLACE_LEFT]         = sMovementActionFuncs_AcroWheelieInPlaceLeft,
    [MOVEMENT_ACTION_ACRO_WHEELIE_IN_PLACE_RIGHT]        = sMovementActionFuncs_AcroWheelieInPlaceRight,
    [MOVEMENT_ACTION_ACRO_POP_WHEELIE_MOVE_DOWN]         = sMovementActionFuncs_AcroPopWheelieMoveDown,
    [MOVEMENT_ACTION_ACRO_POP_WHEELIE_MOVE_UP]           = sMovementActionFuncs_AcroPopWheelieMoveUp,
    [MOVEMENT_ACTION_ACRO_POP_WHEELIE_MOVE_LEFT]         = sMovementActionFuncs_AcroPopWheelieMoveLeft,
    [MOVEMENT_ACTION_ACRO_POP_WHEELIE_MOVE_RIGHT]        = sMovementActionFuncs_AcroPopWheelieMoveRight,
    [MOVEMENT_ACTION_ACRO_WHEELIE_MOVE_DOWN]             = sMovementActionFuncs_AcroWheelieMoveDown,
    [MOVEMENT_ACTION_ACRO_WHEELIE_MOVE_UP]               = sMovementActionFuncs_AcroWheelieMoveUp,
    [MOVEMENT_ACTION_ACRO_WHEELIE_MOVE_LEFT]             = sMovementActionFuncs_AcroWheelieMoveLeft,
    [MOVEMENT_ACTION_ACRO_WHEELIE_MOVE_RIGHT]            = sMovementActionFuncs_AcroWheelieMoveRight,
    [MOVEMENT_ACTION_SPIN_DOWN]                          = sMovementActionFuncs_SpinDown,
    [MOVEMENT_ACTION_SPIN_UP]                            = sMovementActionFuncs_SpinUp,
    [MOVEMENT_ACTION_SPIN_LEFT]                          = sMovementActionFuncs_SpinLeft,
    [MOVEMENT_ACTION_SPIN_RIGHT]                         = sMovementActionFuncs_SpinRight,
    [MOVEMENT_ACTION_RAISE_HAND_AND_STOP]                = sMovementActionFuncs_RaiseHandAndStop,
    [MOVEMENT_ACTION_RAISE_HAND_AND_JUMP]                = sMovementActionFuncs_RaiseHandAndJump,
    [MOVEMENT_ACTION_RAISE_HAND_AND_SWIM]                = sMovementActionFuncs_RaiseHandAndSwim,
    [MOVEMENT_ACTION_WALK_SLOWEST_DOWN]                  = sMovementActionFuncs_WalkSlowestDown,
    [MOVEMENT_ACTION_WALK_SLOWEST_UP]                    = sMovementActionFuncs_WalkSlowestUp,
    [MOVEMENT_ACTION_WALK_SLOWEST_LEFT]                  = sMovementActionFuncs_WalkSlowestLeft,
    [MOVEMENT_ACTION_WALK_SLOWEST_RIGHT]                 = sMovementActionFuncs_WalkSlowestRight,
    [MOVEMENT_ACTION_SHAKE_HEAD_OR_WALK_IN_PLACE]        = sMovementActionFuncs_ShakeHeadOrWalkInPlace,
    [MOVEMENT_ACTION_GLIDE_DOWN]                         = sMovementActionFuncs_GlideDown,
    [MOVEMENT_ACTION_GLIDE_UP]                           = sMovementActionFuncs_GlideUp,
    [MOVEMENT_ACTION_GLIDE_LEFT]                         = sMovementActionFuncs_GlideLeft,
    [MOVEMENT_ACTION_GLIDE_RIGHT]                        = sMovementActionFuncs_GlideRight,
    [MOVEMENT_ACTION_FLY_UP]                             = sMovementActionFuncs_FlyUp,
    [MOVEMENT_ACTION_FLY_DOWN]                           = sMovementActionFuncs_FlyDown,
    [MOVEMENT_ACTION_JUMP_SPECIAL_WITH_EFFECT_DOWN]      = sMovementActionFuncs_JumpSpecialWithEffectDown,
    [MOVEMENT_ACTION_JUMP_SPECIAL_WITH_EFFECT_UP]        = sMovementActionFuncs_JumpSpecialWithEffectUp,
    [MOVEMENT_ACTION_JUMP_SPECIAL_WITH_EFFECT_LEFT]      = sMovementActionFuncs_JumpSpecialWithEffectLeft,
    [MOVEMENT_ACTION_JUMP_SPECIAL_WITH_EFFECT_RIGHT]     = sMovementActionFuncs_JumpSpecialWithEffectRight,
};

static bool8 (*const sMovementActionFuncs_FaceDown[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_FaceDown_Step0,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_FaceUp[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_FaceUp_Step0,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_FaceLeft[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_FaceLeft_Step0,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_FaceRight[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_FaceRight_Step0,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sDirectionAnimFuncsBySpeed[])(u8) = {
    [MOVE_SPEED_NORMAL] = GetMoveDirectionAnimNum,
    [MOVE_SPEED_FAST_1] = GetMoveDirectionFastAnimNum,
    [MOVE_SPEED_FAST_2] = GetMoveDirectionFastAnimNum,
    [MOVE_SPEED_FASTER] = GetMoveDirectionFasterAnimNum,
    [MOVE_SPEED_FASTEST] = GetMoveDirectionFastestAnimNum,
};

static bool8 (*const sMovementActionFuncs_WalkSlowestDown[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_WalkSlowestDown_Step0,
    MovementAction_WalkSlowestDown_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_WalkSlowestUp[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_WalkSlowestUp_Step0,
    MovementAction_WalkSlowestUp_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_WalkSlowestLeft[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_WalkSlowestLeft_Step0,
    MovementAction_WalkSlowestLeft_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_WalkSlowestRight[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_WalkSlowestRight_Step0,
    MovementAction_WalkSlowestRight_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_WalkSlowerDown[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_WalkSlowerDown_Step0,
    MovementAction_WalkSlowerDown_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_WalkSlowerUp[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_WalkSlowerUp_Step0,
    MovementAction_WalkSlowerUp_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_WalkSlowerLeft[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_WalkSlowerLeft_Step0,
    MovementAction_WalkSlowerLeft_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_WalkSlowerRight[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_WalkSlowerRight_Step0,
    MovementAction_WalkSlowerRight_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_WalkSlowUp[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_WalkSlowUp_Step0,
    MovementAction_WalkSlowUp_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_WalkSlowDown[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_WalkSlowDown_Step0,
    MovementAction_WalkSlowDown_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_WalkSlowLeft[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_WalkSlowLeft_Step0,
    MovementAction_WalkSlowLeft_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_WalkSlowRight[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_WalkSlowRight_Step0,
    MovementAction_WalkSlowRight_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_WalkNormalDown[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_WalkNormalDown_Step0,
    MovementAction_WalkNormalDown_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_WalkNormalUp[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_WalkNormalUp_Step0,
    MovementAction_WalkNormalUp_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_WalkNormalLeft[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_WalkNormalLeft_Step0,
    MovementAction_WalkNormalLeft_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_WalkNormalRight[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_WalkNormalRight_Step0,
    MovementAction_WalkNormalRight_Step1,
    MovementAction_PauseSpriteAnim,
};

static const s16 sJumpInitDisplacements[] = {
    [JUMP_DISTANCE_IN_PLACE] = 0,
    [JUMP_DISTANCE_NORMAL] = 1,
    [JUMP_DISTANCE_FAR] = 1,
};

static const s16 sJumpDisplacements[] = {
    [JUMP_DISTANCE_IN_PLACE] = 0,
    [JUMP_DISTANCE_NORMAL] = 0,
    [JUMP_DISTANCE_FAR] = 1,
};

static bool8 (*const sMovementActionFuncs_Jump2Down[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_Jump2Down_Step0,
    MovementAction_Jump2Down_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_Jump2Up[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_Jump2Up_Step0,
    MovementAction_Jump2Up_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_Jump2Left[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_Jump2Left_Step0,
    MovementAction_Jump2Left_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_Jump2Right[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_Jump2Right_Step0,
    MovementAction_Jump2Right_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_Delay1[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_Delay1_Step0,
    MovementAction_Delay_Step1,
    MovementAction_Finish,
};

static bool8 (*const sMovementActionFuncs_Delay2[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_Delay2_Step0,
    MovementAction_Delay_Step1,
    MovementAction_Finish,
};

static bool8 (*const sMovementActionFuncs_Delay4[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_Delay4_Step0,
    MovementAction_Delay_Step1,
    MovementAction_Finish,
};

static bool8 (*const sMovementActionFuncs_Delay8[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_Delay8_Step0,
    MovementAction_Delay_Step1,
    MovementAction_Finish,
};

static bool8 (*const sMovementActionFuncs_Delay16[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_Delay16_Step0,
    MovementAction_Delay_Step1,
    MovementAction_Finish,
};

static bool8 (*const sMovementActionFuncs_WalkFastDown[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_WalkFastDown_Step0,
    MovementAction_WalkFastDown_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_WalkFastUp[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_WalkFastUp_Step0,
    MovementAction_WalkFastUp_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_WalkFastLeft[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_WalkFastLeft_Step0,
    MovementAction_WalkFastLeft_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_WalkFastRight[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_WalkFastRight_Step0,
    MovementAction_WalkFastRight_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_GlideDown[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_GlideDown_Step0,
    MovementAction_GlideDown_Step1,
    MovementAction_Finish,
};

static bool8 (*const sMovementActionFuncs_GlideUp[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_GlideUp_Step0,
    MovementAction_GlideUp_Step1,
    MovementAction_Finish,
};

static bool8 (*const sMovementActionFuncs_GlideLeft[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_GlideLeft_Step0,
    MovementAction_GlideLeft_Step1,
    MovementAction_Finish,
};

static bool8 (*const sMovementActionFuncs_GlideRight[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_GlideRight_Step0,
    MovementAction_GlideRight_Step1,
    MovementAction_Finish,
};

static bool8 (*const sMovementActionFuncs_FaceDownFast[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_FaceDownFast_Step0,
    MovementAction_Finish,
};

static bool8 (*const sMovementActionFuncs_FaceUpFast[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_FaceUpFast_Step0,
    MovementAction_Finish,
};

static bool8 (*const sMovementActionFuncs_FaceLeftFast[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_FaceLeftFast_Step0,
    MovementAction_Finish,
};

static bool8 (*const sMovementActionFuncs_FaceRightFast[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_FaceRightFast_Step0,
    MovementAction_Finish,
};

static bool8 (*const sMovementActionFuncs_WalkInPlaceSlowDown[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_WalkInPlaceSlowDown_Step0,
    MovementAction_WalkInPlaceSlow_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_WalkInPlaceSlowUp[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_WalkInPlaceSlowUp_Step0,
    MovementAction_WalkInPlaceSlow_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_WalkInPlaceSlowLeft[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_WalkInPlaceSlowLeft_Step0,
    MovementAction_WalkInPlaceSlow_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_WalkInPlaceSlowRight[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_WalkInPlaceSlowRight_Step0,
    MovementAction_WalkInPlaceSlow_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_WalkInPlaceNormalDown[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_WalkInPlaceNormalDown_Step0,
    MovementAction_WalkInPlace_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_WalkInPlaceNormalUp[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_WalkInPlaceNormalUp_Step0,
    MovementAction_WalkInPlace_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_WalkInPlaceNormalLeft[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_WalkInPlaceNormalLeft_Step0,
    MovementAction_WalkInPlace_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_WalkInPlaceNormalRight[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_WalkInPlaceNormalRight_Step0,
    MovementAction_WalkInPlace_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_WalkInPlaceFastDown[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_WalkInPlaceFastDown_Step0,
    MovementAction_WalkInPlace_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_WalkInPlaceFastUp[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_WalkInPlaceFastUp_Step0,
    MovementAction_WalkInPlace_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_WalkInPlaceFastLeft[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_WalkInPlaceFastLeft_Step0,
    MovementAction_WalkInPlace_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_WalkInPlaceFastRight[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_WalkInPlaceFastRight_Step0,
    MovementAction_WalkInPlace_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_WalkInPlaceFasterDown[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_WalkInPlaceFasterDown_Step0,
    MovementAction_WalkInPlace_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_WalkInPlaceFasterUp[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_WalkInPlaceFasterUp_Step0,
    MovementAction_WalkInPlace_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_WalkInPlaceFasterLeft[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_WalkInPlaceFasterLeft_Step0,
    MovementAction_WalkInPlace_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_WalkInPlaceFasterRight[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_WalkInPlaceFasterRight_Step0,
    MovementAction_WalkInPlace_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_RideWaterCurrentDown[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_RideWaterCurrentDown_Step0,
    MovementAction_RideWaterCurrentDown_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_RideWaterCurrentUp[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_RideWaterCurrentUp_Step0,
    MovementAction_RideWaterCurrentUp_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_RideWaterCurrentLeft[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_RideWaterCurrentLeft_Step0,
    MovementAction_RideWaterCurrentLeft_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_RideWaterCurrentRight[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_RideWaterCurrentRight_Step0,
    MovementAction_RideWaterCurrentRight_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_WalkFasterDown[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_WalkFasterDown_Step0,
    MovementAction_WalkFasterDown_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_WalkFasterUp[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_WalkFasterUp_Step0,
    MovementAction_WalkFasterUp_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_WalkFasterLeft[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_WalkFasterLeft_Step0,
    MovementAction_WalkFasterLeft_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_WalkFasterRight[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_WalkFasterRight_Step0,
    MovementAction_WalkFasterRight_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_SlideDown[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_SlideDown_Step0,
    MovementAction_SlideDown_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_SlideUp[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_SlideUp_Step0,
    MovementAction_SlideUp_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_SlideLeft[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_SlideLeft_Step0,
    MovementAction_SlideLeft_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_SlideRight[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_SlideRight_Step0,
    MovementAction_SlideRight_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_PlayerRunDown[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_PlayerRunDown_Step0,
    MovementAction_PlayerRunDown_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_PlayerRunUp[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_PlayerRunUp_Step0,
    MovementAction_PlayerRunUp_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_PlayerRunLeft[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_PlayerRunLeft_Step0,
    MovementAction_PlayerRunLeft_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_PlayerRunRight[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_PlayerRunRight_Step0,
    MovementAction_PlayerRunRight_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_PlayerRunDownSlow[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_RunDownSlow_Step0,
    MovementAction_RunDownSlow_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_PlayerRunUpSlow[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_RunUpSlow_Step0,
    MovementAction_RunUpSlow_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_PlayerRunLeftSlow[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_RunLeftSlow_Step0,
    MovementAction_RunLeftSlow_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_PlayerRunRightSlow[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_RunRightSlow_Step0,
    MovementAction_RunRightSlow_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_StartAnimInDirection[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_StartAnimInDirection_Step0,
    MovementAction_WaitSpriteAnim,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_JumpSpecialDown[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_JumpSpecialDown_Step0,
    MovementAction_JumpSpecialDown_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_JumpSpecialUp[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_JumpSpecialUp_Step0,
    MovementAction_JumpSpecialUp_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_JumpSpecialLeft[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_JumpSpecialLeft_Step0,
    MovementAction_JumpSpecialLeft_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_JumpSpecialRight[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_JumpSpecialRight_Step0,
    MovementAction_JumpSpecialRight_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_JumpSpecialWithEffectDown[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_JumpSpecialWithEffectDown_Step0,
    MovementAction_JumpSpecialWithEffectDown_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_JumpSpecialWithEffectUp[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_JumpSpecialWithEffectUp_Step0,
    MovementAction_JumpSpecialWithEffectUp_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_JumpSpecialWithEffectLeft[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_JumpSpecialWithEffectLeft_Step0,
    MovementAction_JumpSpecialWithEffectLeft_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_JumpSpecialWithEffectRight[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_JumpSpecialWithEffectRight_Step0,
    MovementAction_JumpSpecialWithEffectRight_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_FacePlayer[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_FacePlayer_Step0,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_FaceAwayPlayer[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_FaceAwayPlayer_Step0,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_LockFacingDirection[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_LockFacingDirection_Step0,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_UnlockFacingDirection[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_UnlockFacingDirection_Step0,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_JumpDown[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_JumpDown_Step0,
    MovementAction_JumpDown_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_JumpUp[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_JumpUp_Step0,
    MovementAction_JumpUp_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_JumpLeft[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_JumpLeft_Step0,
    MovementAction_JumpLeft_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_JumpRight[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_JumpRight_Step0,
    MovementAction_JumpRight_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_JumpInPlaceDown[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_JumpInPlaceDown_Step0,
    MovementAction_JumpInPlaceDown_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_JumpInPlaceUp[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_JumpInPlaceUp_Step0,
    MovementAction_JumpInPlaceUp_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_JumpInPlaceLeft[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_JumpInPlaceLeft_Step0,
    MovementAction_JumpInPlaceLeft_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_JumpInPlaceRight[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_JumpInPlaceRight_Step0,
    MovementAction_JumpInPlaceRight_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_JumpInPlaceDownUp[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_JumpInPlaceDownUp_Step0,
    MovementAction_JumpInPlaceDownUp_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_JumpInPlaceUpDown[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_JumpInPlaceUpDown_Step0,
    MovementAction_JumpInPlaceUpDown_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_JumpInPlaceLeftRight[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_JumpInPlaceLeftRight_Step0,
    MovementAction_JumpInPlaceLeftRight_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_JumpInPlaceRightLeft[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_JumpInPlaceRightLeft_Step0,
    MovementAction_JumpInPlaceRightLeft_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_FaceOriginalDirection[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_FaceOriginalDirection_Step0,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_NurseJoyBowDown[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_NurseJoyBowDown_Step0,
    MovementAction_WaitSpriteAnim,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_EnableJumpLandingGroundEffect[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_EnableJumpLandingGroundEffect_Step0,
    MovementAction_Finish,
};

static bool8 (*const sMovementActionFuncs_DisableJumpLandingGroundEffect[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_DisableJumpLandingGroundEffect_Step0,
    MovementAction_Finish,
};

static bool8 (*const sMovementActionFuncs_DisableAnimation[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_DisableAnimation_Step0,
    MovementAction_Finish,
};

static bool8 (*const sMovementActionFuncs_RestoreAnimation[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_RestoreAnimation_Step0,
    MovementAction_Finish,
};

static bool8 (*const sMovementActionFuncs_SetInvisible[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_SetInvisible_Step0,
    MovementAction_Finish,
};

static bool8 (*const sMovementActionFuncs_SetVisible[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_SetVisible_Step0,
    MovementAction_Finish,
};

static bool8 (*const sMovementActionFuncs_EmoteExclamationMark[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_EmoteExclamationMark_Step0,
    MovementAction_Finish,
};

static bool8 (*const sMovementActionFuncs_EmoteQuestionMark[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_EmoteQuestionMark_Step0,
    MovementAction_Finish,
};

static bool8 (*const sMovementActionFuncs_EmoteX[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_EmoteX_Step0,
    MovementAction_Finish,
};

static bool8 (*const sMovementActionFuncs_EmoteDoubleExclMark[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_EmoteDoubleExclamationMark_Step0,
    MovementAction_Finish,
};

static bool8 (*const sMovementActionFuncs_EmoteSmile[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_EmoteSmile_Step0,
    MovementAction_Finish,
};

static bool8 (*const sMovementActionFuncs_RevealTrainer[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_RevealTrainer_Step0,
    MovementAction_RevealTrainer_Step1,
    MovementAction_Finish,
};

static bool8 (*const sMovementActionFuncs_RockSmashBreak[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_RockSmashBreak_Step0,
    MovementAction_RockSmashBreak_Step1,
    MovementAction_RockSmashBreak_Step2,
    MovementAction_Finish,
};

static bool8 (*const sMovementActionFuncs_CutTree[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_CutTree_Step0,
    MovementAction_CutTree_Step1,
    MovementAction_CutTree_Step2,
    MovementAction_Finish,
};

static bool8 (*const sMovementActionFuncs_SetFixedPriority[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_SetFixedPriority_Step0,
    MovementAction_Finish,
};

static bool8 (*const sMovementActionFuncs_ClearFixedPriority[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_ClearFixedPriority_Step0,
    MovementAction_Finish,
};

static bool8 (*const sMovementActionFuncs_InitAffineAnim[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_InitAffineAnim_Step0,
    MovementAction_Finish,
};

static bool8 (*const sMovementActionFuncs_ClearAffineAnim[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_ClearAffineAnim_Step0,
    MovementAction_Finish,
};

static bool8 (*const sMovementActionFuncs_WalkDownStartAffine[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_WalkDownStartAffine_Step0,
    MovementAction_WalkDownStartAffine_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_WalkDownAffine[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_WalkDownAffine_Step0,
    MovementAction_WalkDownAffine_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_AcroWheelieFaceDown[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_AcroWheelieFaceDown_Step0,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_AcroWheelieFaceUp[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_AcroWheelieFaceUp_Step0,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_AcroWheelieFaceLeft[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_AcroWheelieFaceLeft_Step0,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_AcroWheelieFaceRight[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_AcroWheelieFaceRight_Step0,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_AcroPopWheelieDown[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_AcroPopWheelieDown_Step0,
    MovementAction_WaitSpriteAnim,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_AcroPopWheelieUp[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_AcroPopWheelieUp_Step0,
    MovementAction_WaitSpriteAnim,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_AcroPopWheelieLeft[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_AcroPopWheelieLeft_Step0,
    MovementAction_WaitSpriteAnim,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_AcroPopWheelieRight[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_AcroPopWheelieRight_Step0,
    MovementAction_WaitSpriteAnim,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_AcroEndWheelieFaceDown[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_AcroEndWheelieFaceDown_Step0,
    MovementAction_WaitSpriteAnim,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_AcroEndWheelieFaceUp[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_AcroEndWheelieFaceUp_Step0,
    MovementAction_WaitSpriteAnim,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_AcroEndWheelieFaceLeft[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_AcroEndWheelieFaceLeft_Step0,
    MovementAction_WaitSpriteAnim,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_AcroEndWheelieFaceRight[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_AcroEndWheelieFaceRight_Step0,
    MovementAction_WaitSpriteAnim,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const MovementActionFuncs_UnusedAcroActionDown[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_UnusedAcroActionDown_Step0,
    MovementAction_WaitSpriteAnim,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const MovementActionFuncs_UnusedAcroActionUp[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_UnusedAcroActionUp_Step0,
    MovementAction_WaitSpriteAnim,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const MovementActionFuncs_UnusedAcroActionLeft[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_UnusedAcroActionLeft_Step0,
    MovementAction_WaitSpriteAnim,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const MovementActionFuncs_UnusedAcroActionRight[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_UnusedAcroActionRight_Step0,
    MovementAction_WaitSpriteAnim,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_AcroWheelieHopFaceDown[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_AcroWheelieHopFaceDown_Step0,
    MovementAction_AcroWheelieHopFaceDown_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_AcroWheelieHopFaceUp[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_AcroWheelieHopFaceUp_Step0,
    MovementAction_AcroWheelieHopFaceUp_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_AcroWheelieHopFaceLeft[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_AcroWheelieHopFaceLeft_Step0,
    MovementAction_AcroWheelieHopFaceLeft_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_AcroWheelieHopFaceRight[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_AcroWheelieHopFaceRight_Step0,
    MovementAction_AcroWheelieHopFaceRight_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_AcroWheelieHopDown[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_AcroWheelieHopDown_Step0,
    MovementAction_AcroWheelieHopDown_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_AcroWheelieHopUp[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_AcroWheelieHopUp_Step0,
    MovementAction_AcroWheelieHopUp_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_AcroWheelieHopLeft[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_AcroWheelieHopLeft_Step0,
    MovementAction_AcroWheelieHopLeft_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_AcroWheelieHopRight[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_AcroWheelieHopRight_Step0,
    MovementAction_AcroWheelieHopRight_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_AcroWheelieJumpDown[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_AcroWheelieJumpDown_Step0,
    MovementAction_AcroWheelieJumpDown_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_AcroWheelieJumpUp[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_AcroWheelieJumpUp_Step0,
    MovementAction_AcroWheelieJumpUp_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_AcroWheelieJumpLeft[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_AcroWheelieJumpLeft_Step0,
    MovementAction_AcroWheelieJumpLeft_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_AcroWheelieJumpRight[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_AcroWheelieJumpRight_Step0,
    MovementAction_AcroWheelieJumpRight_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_AcroWheelieInPlaceDown[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_AcroWheelieInPlaceDown_Step0,
    MovementAction_WalkInPlace_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_AcroWheelieInPlaceUp[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_AcroWheelieInPlaceUp_Step0,
    MovementAction_WalkInPlace_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_AcroWheelieInPlaceLeft[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_AcroWheelieInPlaceLeft_Step0,
    MovementAction_WalkInPlace_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_AcroWheelieInPlaceRight[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_AcroWheelieInPlaceRight_Step0,
    MovementAction_WalkInPlace_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_AcroPopWheelieMoveDown[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_AcroPopWheelieMoveDown_Step0,
    MovementAction_AcroPopWheelieMoveDown_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_AcroPopWheelieMoveUp[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_AcroPopWheelieMoveUp_Step0,
    MovementAction_AcroPopWheelieMoveUp_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_AcroPopWheelieMoveLeft[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_AcroPopWheelieMoveLeft_Step0,
    MovementAction_AcroPopWheelieMoveLeft_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_AcroPopWheelieMoveRight[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_AcroPopWheelieMoveRight_Step0,
    MovementAction_AcroPopWheelieMoveRight_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_AcroWheelieMoveDown[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_AcroWheelieMoveDown_Step0,
    MovementAction_AcroWheelieMoveDown_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_AcroWheelieMoveUp[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_AcroWheelieMoveUp_Step0,
    MovementAction_AcroWheelieMoveUp_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_AcroWheelieMoveLeft[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_AcroWheelieMoveLeft_Step0,
    MovementAction_AcroWheelieMoveLeft_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_AcroWheelieMoveRight[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_AcroWheelieMoveRight_Step0,
    MovementAction_AcroWheelieMoveRight_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_SpinDown[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_SpinDown_Step0,
    MovementAction_SpinDown_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_SpinUp[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_SpinUp_Step0,
    MovementAction_SpinUp_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_SpinLeft[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_SpinLeft_Step0,
    MovementAction_SpinLeft_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_SpinRight[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_SpinRight_Step0,
    MovementAction_SpinRight_Step1,
    MovementAction_PauseSpriteAnim,
};

static bool8 (*const sMovementActionFuncs_RaiseHandAndStop[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_RaiseHand_Step0,
    MovementAction_RaiseHandAndStop_Step1,
};

static bool8 (*const sMovementActionFuncs_RaiseHandAndJump[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_RaiseHand_Step0,
    MovementAction_RaiseHandAndJump_Step1,
};

static bool8 (*const sMovementActionFuncs_RaiseHandAndSwim[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_RaiseHand_Step0,
    MovementAction_RaiseHandAndSwim_Step1,
};

static bool8 (*const sMovementActionFuncs_ShakeHeadOrWalkInPlace[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_ShakeHeadOrWalkInPlace_Step0,
    MovementAction_ShakeHeadOrWalkInPlace_Step1,
};

static bool8 (*const sMovementActionFuncs_FlyUp[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_FlyUp_Step0,
    MovementAction_FlyUp_Step1,
    MovementAction_FlyUp_Step2,
};

static bool8 (*const sMovementActionFuncs_FlyDown[])(struct ObjectEvent *, struct Sprite *) = {
    MovementAction_FlyDown_Step0,
    MovementAction_FlyDown_Step1,
    MovementAction_FlyUp_Step2,
};
// ===== END src/data/object_events/movement_action_func_tables.h =====

static void ClearObjectEvent(struct ObjectEvent *objectEvent)
{
    *objectEvent = (struct ObjectEvent){};
    objectEvent->localId = LOCALID_PLAYER;
    objectEvent->mapNum = MAP_NUM(MAP_UNDEFINED);
    objectEvent->mapGroup = MAP_GROUP(MAP_UNDEFINED);
    objectEvent->movementActionId = MOVEMENT_ACTION_NONE;
}

static void ClearAllObjectEvents(void)
{
    u8 i;

    for (i = 0; i < OBJECT_EVENTS_COUNT; i++)
        ClearObjectEvent(&gObjectEvents[i]);
}

void ResetObjectEvents(void)
{
    ClearLinkPlayerObjectEvents();
    ClearAllObjectEvents();
    ClearPlayerAvatarInfo();
    CreateReflectionEffectSprites();
}

static void CreateReflectionEffectSprites(void)
{
    u8 spriteId = CreateSpriteAtEnd(gFieldEffectObjectTemplatePointers[FLDEFFOBJ_REFLECTION_DISTORTION], 0, 0, 31);
    gSprites[spriteId].oam.affineMode = ST_OAM_AFFINE_NORMAL;
    InitSpriteAffineAnim(&gSprites[spriteId]);
    StartSpriteAffineAnim(&gSprites[spriteId], 0);
    gSprites[spriteId].invisible = TRUE;

    spriteId = CreateSpriteAtEnd(gFieldEffectObjectTemplatePointers[FLDEFFOBJ_REFLECTION_DISTORTION], 0, 0, 31);
    gSprites[spriteId].oam.affineMode = ST_OAM_AFFINE_NORMAL;
    InitSpriteAffineAnim(&gSprites[spriteId]);
    StartSpriteAffineAnim(&gSprites[spriteId], 1);
    gSprites[spriteId].invisible = TRUE;
}

u8 GetFirstInactiveObjectEventId(void)
{
    u8 i;
    for (i = 0; i < OBJECT_EVENTS_COUNT; i++)
    {
        if (!gObjectEvents[i].active)
            break;
    }

    return i;
}

u8 GetObjectEventIdByLocalIdAndMap(u8 localId, u8 mapNum, u8 mapGroupId)
{
    if (localId < LOCALID_PLAYER)
    {
        return GetObjectEventIdByLocalIdAndMapInternal(localId, mapNum, mapGroupId);
    }
    return GetObjectEventIdByLocalId(localId);
}

bool8 TryGetObjectEventIdByLocalIdAndMap(u8 localId, u8 mapNum, u8 mapGroupId, u8 *objectEventId)
{
    *objectEventId = GetObjectEventIdByLocalIdAndMap(localId, mapNum, mapGroupId);
    if (*objectEventId == OBJECT_EVENTS_COUNT)
        return TRUE;
    else
        return FALSE;
}

u8 GetObjectEventIdByXY(s16 x, s16 y)
{
    u8 i;
    for (i = 0; i < OBJECT_EVENTS_COUNT; i++)
    {
        if (gObjectEvents[i].active && gObjectEvents[i].currentCoords.x == x && gObjectEvents[i].currentCoords.y == y)
            break;
    }

    return i;
}

static u8 GetObjectEventIdByLocalIdAndMapInternal(u8 localId, u8 mapNum, u8 mapGroupId)
{
    u8 i;
    for (i = 0; i < OBJECT_EVENTS_COUNT; i++)
    {
        if (gObjectEvents[i].active && gObjectEvents[i].localId == localId && gObjectEvents[i].mapNum == mapNum && gObjectEvents[i].mapGroup == mapGroupId)
            return i;
    }

    return OBJECT_EVENTS_COUNT;
}

static u8 GetObjectEventIdByLocalId(u8 localId)
{
    u8 i;
    for (i = 0; i < OBJECT_EVENTS_COUNT; i++)
    {
        if (gObjectEvents[i].active && gObjectEvents[i].localId == localId)
            return i;
    }

    return OBJECT_EVENTS_COUNT;
}

static u8 InitObjectEventStateFromTemplate(const struct ObjectEventTemplate *template, u8 mapNum, u8 mapGroup)
{
    struct ObjectEvent *objectEvent;
    const struct MapHeader *mapHeader;
    u8 objectEventId;
    s16 x;
    s16 y;
    bool8 isClone = FALSE;
    u8 localId = LOCALID_NONE;
    s16 x2 = 0;
    s16 y2 = 0;
    s16 x3 = 0;
    s16 y3 = 0;
    
    if (template->kind == OBJ_KIND_CLONE)
    {
        isClone = TRUE;
        localId = template->objUnion.clone.targetLocalId;
        mapNum = template->objUnion.clone.targetMapNum;
        mapGroup = template->objUnion.clone.targetMapGroup;
        x2 = template->x;
        y2 = template->y;
        x3 = template->x;
        y3 = template->y;
        mapHeader = Overworld_GetMapHeaderByGroupAndId(mapGroup, mapNum);
        template = &(mapHeader->events->objectEvents[localId - 1]);
    }

    if (GetAvailableObjectEventId(template->localId, mapNum, mapGroup, &objectEventId))
        return OBJECT_EVENTS_COUNT;

    if (!ShouldInitObjectEventStateFromTemplate(template, isClone, x3, y3))
        return OBJECT_EVENTS_COUNT;

    objectEvent = &gObjectEvents[objectEventId];
    ClearObjectEvent(objectEvent);
    if (isClone)
    {
        x = x2 + MAP_OFFSET;
        y = y2 + MAP_OFFSET;
    }
    else
    {
        x = template->x + MAP_OFFSET;
        y = template->y + MAP_OFFSET;
    }
    objectEvent->active = TRUE;
    objectEvent->triggerGroundEffectsOnMove = TRUE;
    objectEvent->graphicsId = template->graphicsId;
    objectEvent->movementType = template->objUnion.normal.movementType;
    objectEvent->localId = template->localId;
    objectEvent->mapNum = mapNum;
    objectEvent->mapGroup = mapGroup;
    objectEvent->initialCoords.x = x;
    objectEvent->initialCoords.y = y;
    objectEvent->currentCoords.x = x;
    objectEvent->currentCoords.y = y;
    objectEvent->previousCoords.x = x;
    objectEvent->previousCoords.y = y;
    objectEvent->currentElevation = template->objUnion.normal.elevation;
    objectEvent->previousElevation = template->objUnion.normal.elevation;
    objectEvent->rangeX = template->objUnion.normal.movementRangeX;
    objectEvent->rangeY = template->objUnion.normal.movementRangeY;
    objectEvent->trainerType = template->objUnion.normal.trainerType;
    objectEvent->trainerRange_berryTreeId = template->objUnion.normal.trainerRange_berryTreeId;
    objectEvent->mapNum = mapNum; // oops (yes this is required for matching)
    objectEvent->previousMovementDirection = gInitialMovementTypeFacingDirections[template->objUnion.normal.movementType];
    SetObjectEventDirection(objectEvent, objectEvent->previousMovementDirection);
    SetObjectEventDynamicGraphicsId(objectEvent);
    if (gRangedMovementTypes[objectEvent->movementType])
    {
        if (objectEvent->rangeX == 0)
            objectEvent->rangeX++;
        if (objectEvent->rangeY == 0)
            objectEvent->rangeY++;
    }
    return objectEventId;
}

static bool8 ShouldInitObjectEventStateFromTemplate(const struct ObjectEventTemplate *template, bool8 isClone, s16 x, s16 y)
{
    if (isClone && !TemplateIsObstacleAndWithinView(template, x, y))
        return FALSE;

    if (!TemplateIsObstacleAndVisibleFromConnectingMap(template, x, y))
        return FALSE;
    
    return TRUE;
}

static bool8 TemplateIsObstacleAndWithinView(const struct ObjectEventTemplate *template, s16 x, s16 y)
{
    if (template->graphicsId == OBJ_EVENT_GFX_CUT_TREE || template->graphicsId == OBJ_EVENT_GFX_ROCK_SMASH_ROCK)
    {
        if (gSaveBlock1Ptr->pos.x < x)
        {
            if (gSaveBlock1Ptr->pos.x + (MAP_OFFSET + 1) < x)
                return TRUE;
            if (gSaveBlock1Ptr->pos.y - (MAP_OFFSET - 1) <= y && gSaveBlock1Ptr->pos.y + (MAP_OFFSET - 1) >= y)
                return FALSE;
        }
        else
        {
            if (gSaveBlock1Ptr->pos.x - (MAP_OFFSET + 1) > x)
                return TRUE;

            if (gSaveBlock1Ptr->pos.y - (MAP_OFFSET - 1) <= y && gSaveBlock1Ptr->pos.y + (MAP_OFFSET - 1) >= y)
                return FALSE;
        }
    }
    return TRUE;
}

static bool8 TemplateIsObstacleAndVisibleFromConnectingMap(const struct ObjectEventTemplate *template, s16 unused1, s16 unused2)
{
    if (IsMapTypeOutdoors(GetCurrentMapType()))
    {
        s32 width = VMap.Xsize - MAP_OFFSET_W - 1;
        s32 height = VMap.Ysize - MAP_OFFSET_H - 1;

        if (template->graphicsId == OBJ_EVENT_GFX_CUT_TREE || template->graphicsId == OBJ_EVENT_GFX_ROCK_SMASH_ROCK)
        {
            if (gSaveBlock1Ptr->pos.x == 0 && template->x <= (MAP_OFFSET + 1))
            {
                SetHideObstacleFlag(template);
                return FALSE;
            }

            if (gSaveBlock1Ptr->pos.x == width && template->x >= width - (MAP_OFFSET + 1))
            {
                SetHideObstacleFlag(template);
                return FALSE;
            }

            if (gSaveBlock1Ptr->pos.y == 0 && template->y <= (MAP_OFFSET - 1))
            {
                SetHideObstacleFlag(template);
                return FALSE;
            }

            if (gSaveBlock1Ptr->pos.y == height && template->y >= height - (MAP_OFFSET - 1))
            {
                SetHideObstacleFlag(template);
                return FALSE;
            }
        }
    }
    return TRUE;
}

static void SetHideObstacleFlag(const struct ObjectEventTemplate *template)
{
    if (template->flagId >= FLAG_TEMP_11 && template->flagId <= FLAG_TEMP_1F)
        FlagSet(template->flagId);
}

u8 Unref_TryInitLocalObjectEvent(u8 localId)
{
    u8 i;
    u8 objectEventCount;
    struct ObjectEventTemplate *template;

    if (gMapHeader.events == NULL)
        return OBJECT_EVENTS_COUNT;

    objectEventCount = gMapHeader.events->objectEventCount;
    
    for (i = 0; i < objectEventCount; i++)
    {
        template = &gSaveBlock1Ptr->objectEventTemplates[i];
        if (template->localId == localId && !FlagGet(template->flagId))
            return InitObjectEventStateFromTemplate(template, gSaveBlock1Ptr->location.mapNum, gSaveBlock1Ptr->location.mapGroup);
    }

    return OBJECT_EVENTS_COUNT;
}

static bool8 GetAvailableObjectEventId(u16 localId, u8 mapNum, u8 mapGroup, u8 *objectEventId)
// Looks for an empty slot.
// Returns FALSE and the location of the available slot
// in *objectEventId.
// If no slots are available, or if the object is already
// loaded, returns TRUE.
{
    u8 i = 0;

    for (i = 0; i < OBJECT_EVENTS_COUNT && gObjectEvents[i].active; i++)
    {
        if (gObjectEvents[i].localId == localId && gObjectEvents[i].mapNum == mapNum && gObjectEvents[i].mapGroup == mapGroup)
            return TRUE;
    }
    if (i >= OBJECT_EVENTS_COUNT)
        return TRUE;
    *objectEventId = i;
    for (; i < OBJECT_EVENTS_COUNT; i++)
    {
        if (gObjectEvents[i].active && gObjectEvents[i].localId == localId && gObjectEvents[i].mapNum == mapNum && gObjectEvents[i].mapGroup == mapGroup)
            return TRUE;
    }
    return FALSE;
}

static void RemoveObjectEvent(struct ObjectEvent *objectEvent)
{
    objectEvent->active = FALSE;
    RemoveObjectEventInternal(objectEvent);
}

void RemoveObjectEventByLocalIdAndMap(u8 localId, u8 mapNum, u8 mapGroup)
{
    u8 objectEventId;
    if (!TryGetObjectEventIdByLocalIdAndMap(localId, mapNum, mapGroup, &objectEventId))
    {
        FlagSet(GetObjectEventFlagIdByObjectEventId(objectEventId));
        RemoveObjectEvent(&gObjectEvents[objectEventId]);
    }
}

static void RemoveObjectEventInternal(struct ObjectEvent *objectEvent)
{
    struct SpriteFrameImage image;
    image.size = GetObjectEventGraphicsInfo(objectEvent->graphicsId)->size;
    gSprites[objectEvent->spriteId].images = &image;
    DestroySprite(&gSprites[objectEvent->spriteId]);
}

void Unref_RemoveAllObjectEventsExceptPlayer(void)
{
    u8 i;

    for (i = 0; i < OBJECT_EVENTS_COUNT; i++)
    {
        if (i != gPlayerAvatar.objectEventId)
            RemoveObjectEvent(&gObjectEvents[i]);
    }
}

static u8 TrySetupObjectEventSprite(const struct ObjectEventTemplate *objectEventTemplate, struct SpriteTemplate *spriteTemplate, u8 mapNum, u8 mapGroup, s16 cameraX, s16 cameraY)
{
    u8 spriteId;
    u8 objectEventId;
    struct Sprite *sprite;
    struct ObjectEvent *objectEvent;
    const struct ObjectEventGraphicsInfo *graphicsInfo;

    objectEventId = InitObjectEventStateFromTemplate(objectEventTemplate, mapNum, mapGroup);
    if (objectEventId == OBJECT_EVENTS_COUNT)
        return OBJECT_EVENTS_COUNT;

    objectEvent = &gObjectEvents[objectEventId];
    graphicsInfo = GetObjectEventGraphicsInfo(objectEvent->graphicsId);
    if (graphicsInfo->paletteSlot == PALSLOT_PLAYER)
        LoadPlayerObjectReflectionPalette(graphicsInfo->paletteTag, graphicsInfo->paletteSlot);
    else if (graphicsInfo->paletteSlot == PALSLOT_NPC_SPECIAL)
        LoadSpecialObjectReflectionPalette(graphicsInfo->paletteTag, graphicsInfo->paletteSlot);


    if (objectEvent->movementType == MOVEMENT_TYPE_INVISIBLE)
        objectEvent->invisible = TRUE;

    *(u16 *)&spriteTemplate->paletteTag = TAG_NONE;
    spriteId = CreateSprite(spriteTemplate, 0, 0, 0);
    if (spriteId == MAX_SPRITES)
    {
        gObjectEvents[objectEventId].active = FALSE;
        return OBJECT_EVENTS_COUNT;
    }

    sprite = &gSprites[spriteId];
    GetMapCoordsFromSpritePos(objectEvent->currentCoords.x + cameraX, objectEvent->currentCoords.y + cameraY, &sprite->x, &sprite->y);
    sprite->centerToCornerVecX = -(graphicsInfo->width >> 1);
    sprite->centerToCornerVecY = -(graphicsInfo->height >> 1);
    sprite->x += 8;
    sprite->y += 16 + sprite->centerToCornerVecY;
    sprite->oam.paletteNum = graphicsInfo->paletteSlot;
    sprite->coordOffsetEnabled = TRUE;
    sprite->data[0] = objectEventId;
    objectEvent->spriteId = spriteId;
    objectEvent->inanimate = graphicsInfo->inanimate;
    if (!objectEvent->inanimate)
        StartSpriteAnim(sprite, GetFaceDirectionAnimNum(objectEvent->facingDirection));

    SetObjectSubpriorityByElevation(objectEvent->previousElevation, sprite, 1);
    UpdateObjectEventVisibility(objectEvent, sprite);
    return objectEventId;
}

static u8 TrySpawnObjectEventTemplate(const struct ObjectEventTemplate *objectEventTemplate, u8 mapNum, u8 mapGroup, s16 cameraX, s16 cameraY)
{
    u8 objectEventId;
    struct SpriteTemplate spriteTemplate;
    struct SpriteFrameImage spriteFrameImage;
    const struct ObjectEventGraphicsInfo *graphicsInfo;
    const struct SubspriteTable *subspriteTables = NULL;

    graphicsInfo = GetObjectEventGraphicsInfo(objectEventTemplate->graphicsId);
    MakeObjectTemplateFromObjectEventTemplate(objectEventTemplate, &spriteTemplate, &subspriteTables);
    spriteFrameImage.size = graphicsInfo->size;
    spriteTemplate.images = &spriteFrameImage;
    objectEventId = TrySetupObjectEventSprite(objectEventTemplate, &spriteTemplate, mapNum, mapGroup, cameraX, cameraY);
    if (objectEventId == OBJECT_EVENTS_COUNT)
        return OBJECT_EVENTS_COUNT;

    gSprites[gObjectEvents[objectEventId].spriteId].images = graphicsInfo->images;
    if (subspriteTables)
        SetSubspriteTables(&gSprites[gObjectEvents[objectEventId].spriteId], subspriteTables);

    return objectEventId;
}

u8 SpawnSpecialObjectEvent(struct ObjectEventTemplate *objectEventTemplate)
{
    s16 cameraX;
    s16 cameraY;

    GetObjectEventMovingCameraOffset(&cameraX, &cameraY);
    return TrySpawnObjectEventTemplate(objectEventTemplate, gSaveBlock1Ptr->location.mapNum, gSaveBlock1Ptr->location.mapGroup, cameraX, cameraY);
}

int SpawnSpecialObjectEventParameterized(u8 graphicsId, u8 movementBehavior, u8 localId, s16 x, s16 y, u8 elevation)
{
    struct ObjectEventTemplate objectEventTemplate;

    x -= MAP_OFFSET;
    y -= MAP_OFFSET;
    objectEventTemplate.localId = localId;
    objectEventTemplate.graphicsId = graphicsId;
    objectEventTemplate.kind = OBJ_KIND_NORMAL;
    objectEventTemplate.x = x;
    objectEventTemplate.y = y;
    objectEventTemplate.objUnion.normal.elevation = elevation;
    objectEventTemplate.objUnion.normal.movementType = movementBehavior;
    objectEventTemplate.objUnion.normal.movementRangeX = 0;
    objectEventTemplate.objUnion.normal.movementRangeY = 0;
    objectEventTemplate.objUnion.normal.trainerType = TRAINER_TYPE_NONE;
    objectEventTemplate.objUnion.normal.trainerRange_berryTreeId = 0;
    return SpawnSpecialObjectEvent(&objectEventTemplate);
}

u8 TrySpawnObjectEvent(u8 localId, u8 mapNum, u8 mapGroup)
{
    const struct ObjectEventTemplate *objectEventTemplate;
    s16 cameraX, cameraY;

    objectEventTemplate = GetObjectEventTemplateByLocalIdAndMap(localId, mapNum, mapGroup);
    if (!objectEventTemplate)
        return OBJECT_EVENTS_COUNT;

    GetObjectEventMovingCameraOffset(&cameraX, &cameraY);
    return TrySpawnObjectEventTemplate(objectEventTemplate, mapNum, mapGroup, cameraX, cameraY);
}

void CopyObjectGraphicsInfoToSpriteTemplate(u16 graphicsId, void (*callback)(struct Sprite *), struct SpriteTemplate *spriteTemplate, const struct SubspriteTable **subspriteTables)
{
    const struct ObjectEventGraphicsInfo *graphicsInfo = GetObjectEventGraphicsInfo(graphicsId);

    spriteTemplate->tileTag = graphicsInfo->tileTag;
    spriteTemplate->paletteTag = graphicsInfo->paletteTag;
    spriteTemplate->oam = graphicsInfo->oam;
    spriteTemplate->anims = graphicsInfo->anims;
    spriteTemplate->images = graphicsInfo->images;
    spriteTemplate->affineAnims = graphicsInfo->affineAnims;
    
    do
    {
        if (ScriptContext_IsEnabled() != TRUE && QL_GetPlaybackState() == QL_PLAYBACK_STATE_RUNNING)
            spriteTemplate->callback = QL_UpdateObject;
        else
            spriteTemplate->callback = callback;
    } while (0);
    
    *subspriteTables = graphicsInfo->subspriteTables;
}

static void CopyObjectGraphicsInfoToSpriteTemplate_WithMovementType(u16 graphicsId, u16 movementType, struct SpriteTemplate *spriteTemplate, const struct SubspriteTable **subspriteTables)
{
    CopyObjectGraphicsInfoToSpriteTemplate(graphicsId, sMovementTypeCallbacks[movementType], spriteTemplate, subspriteTables);
}

static void MakeObjectTemplateFromObjectEventTemplate(const struct ObjectEventTemplate *objectEventTemplate, struct SpriteTemplate *spriteTemplate, const struct SubspriteTable **subspriteTables)
{
    CopyObjectGraphicsInfoToSpriteTemplate_WithMovementType(objectEventTemplate->graphicsId, objectEventTemplate->objUnion.normal.movementType, spriteTemplate, subspriteTables);
}

// Used to create a sprite using a graphicsId associated with object events.
u8 CreateObjectGraphicsSprite(u16 graphicsId, SpriteCallback callback, s16 x, s16 y, u8 subpriority)
{
    struct SpriteTemplate spriteTemplate;
    const struct SubspriteTable *subspriteTables;
    u8 spriteId;

    CopyObjectGraphicsInfoToSpriteTemplate(graphicsId, callback, &spriteTemplate, &subspriteTables);
    if (spriteTemplate.paletteTag != TAG_NONE)
        LoadObjectEventPalette(spriteTemplate.paletteTag);

    spriteId = CreateSprite(&spriteTemplate, x, y, subpriority);
    if (spriteId != MAX_SPRITES && subspriteTables != NULL)
    {
        SetSubspriteTables(&gSprites[spriteId], subspriteTables);
        gSprites[spriteId].subspriteMode = SUBSPRITES_IGNORE_PRIORITY;
    }
    return spriteId;
}

#define sVirtualObjId   data[0]
#define sVirtualObjElev data[1]

u8 CreateVirtualObject(u8 graphicsId, u8 virtualObjId, s16 x, s16 y, u8 elevation, u8 direction)
{
    u8 spriteId;
    struct Sprite *sprite;
    struct SpriteTemplate spriteTemplate;
    const struct SubspriteTable *subspriteTables;
    const struct ObjectEventGraphicsInfo *graphicsInfo;

    graphicsInfo = GetObjectEventGraphicsInfo(graphicsId);
    CopyObjectGraphicsInfoToSpriteTemplate(graphicsId, SpriteCB_VirtualObject, &spriteTemplate, &subspriteTables);
    *(u16 *)&spriteTemplate.paletteTag = TAG_NONE;
    x += MAP_OFFSET;
    y += MAP_OFFSET;
    SetSpritePosToOffsetMapCoords(&x, &y, 8, 16);
    spriteId = CreateSpriteAtEnd(&spriteTemplate, x, y, 0);
    if (spriteId != MAX_SPRITES)
    {
        sprite = &gSprites[spriteId];
        sprite->centerToCornerVecX = -(graphicsInfo->width >> 1);
        sprite->centerToCornerVecY = -(graphicsInfo->height >> 1);
        sprite->y += sprite->centerToCornerVecY;
        sprite->oam.paletteNum = graphicsInfo->paletteSlot;
        sprite->coordOffsetEnabled = TRUE;
        sprite->sVirtualObjId = virtualObjId;
        sprite->sVirtualObjElev = elevation;
        if (graphicsInfo->paletteSlot == PALSLOT_NPC_SPECIAL)
            LoadSpecialObjectReflectionPalette(graphicsInfo->paletteTag, graphicsInfo->paletteSlot);

        if (subspriteTables != NULL)
        {
            SetSubspriteTables(sprite, subspriteTables);
            sprite->subspriteMode = SUBSPRITES_IGNORE_PRIORITY;
        }
        InitObjectPriorityByElevation(sprite, elevation);
        SetObjectSubpriorityByElevation(elevation, sprite, 1);
        StartSpriteAnim(sprite, GetFaceDirectionAnimNum(direction));
    }
    return spriteId;
}

u8 CreateFameCheckerObject(u8 graphicsId, u8 localId, s16 x, s16 y)
{
    u8 spriteId;
    struct Sprite *sprite;
    struct SpriteTemplate spriteTemplate;
    const struct SubspriteTable *subspriteTables;
    const struct ObjectEventGraphicsInfo *graphicsInfo;

    graphicsInfo = GetObjectEventGraphicsInfo(graphicsId);
    CopyObjectGraphicsInfoToSpriteTemplate(graphicsId, SpriteCallbackDummy, &spriteTemplate, &subspriteTables);
    *(u16 *)&spriteTemplate.paletteTag = TAG_NONE;

    spriteId = CreateSpriteAtEnd(&spriteTemplate, x, y, 0);
    if (spriteId != MAX_SPRITES)
    {
        sprite = &gSprites[spriteId];
        sprite->centerToCornerVecY = -(graphicsInfo->height >> 1);
        sprite->y += sprite->centerToCornerVecY;
        sprite->oam.paletteNum = graphicsInfo->paletteSlot;
        sprite->data[0] = localId;
        if (graphicsInfo->paletteSlot == PALSLOT_NPC_SPECIAL)
            LoadSpecialObjectReflectionPalette(graphicsInfo->paletteTag, graphicsInfo->paletteSlot);

        if (subspriteTables != NULL)
        {
            SetSubspriteTables(sprite, subspriteTables);
            sprite->subspriteMode = SUBSPRITES_IGNORE_PRIORITY;
        }
        StartSpriteAnim(sprite, GetFaceDirectionAnimNum(DIR_SOUTH));
    }
    return spriteId;
}

void TrySpawnObjectEvents(s16 cameraX, s16 cameraY)
{
    u8 i;
    u8 objectCount;

    if (gMapHeader.events != NULL)
    {
        s16 left = gSaveBlock1Ptr->pos.x - 2;
        s16 right = gSaveBlock1Ptr->pos.x + MAP_OFFSET_W + 2;
        s16 top = gSaveBlock1Ptr->pos.y;
        s16 bottom = gSaveBlock1Ptr->pos.y + MAP_OFFSET_H + 2;

        objectCount = gMapHeader.events->objectEventCount;

        for (i = 0; i < objectCount; i++)
        {
            struct ObjectEventTemplate *template = &gSaveBlock1Ptr->objectEventTemplates[i];
            s16 npcX = template->x + MAP_OFFSET;
            s16 npcY = template->y + MAP_OFFSET;

            if (top <= npcY && bottom >= npcY && left <= npcX && right >= npcX
                && !FlagGet(template->flagId))
                TrySpawnObjectEventTemplate(template, gSaveBlock1Ptr->location.mapNum, gSaveBlock1Ptr->location.mapGroup, cameraX, cameraY);
        }
    }
}

void RemoveObjectEventsOutsideView(void)
{
    u8 i, j;
    bool8 isActiveLinkPlayer;

    for (i = 0; i < OBJECT_EVENTS_COUNT; i++)
    {
        for (j = 0, isActiveLinkPlayer = FALSE; j < NELEMS(gLinkPlayerObjectEvents); j++)
        {
            if (gLinkPlayerObjectEvents[j].active && i == gLinkPlayerObjectEvents[j].objEventId)
                isActiveLinkPlayer = TRUE;
        }
        if (!isActiveLinkPlayer)
        {
            struct ObjectEvent *objectEvent = &gObjectEvents[i];

            if (objectEvent->active && !objectEvent->isPlayer)
                RemoveObjectEventIfOutsideView(objectEvent);
        }
    }
}

static void RemoveObjectEventIfOutsideView(struct ObjectEvent *objectEvent)
{
    s16 left =   gSaveBlock1Ptr->pos.x - 2;
    s16 right =  gSaveBlock1Ptr->pos.x + MAP_OFFSET_W + 2;
    s16 top =    gSaveBlock1Ptr->pos.y;
    s16 bottom = gSaveBlock1Ptr->pos.y + MAP_OFFSET_H + 2;

    if (objectEvent->currentCoords.x >= left && objectEvent->currentCoords.x <= right
     && objectEvent->currentCoords.y >= top && objectEvent->currentCoords.y <= bottom)
        return;
    if (objectEvent->initialCoords.x >= left && objectEvent->initialCoords.x <= right
     && objectEvent->initialCoords.y >= top && objectEvent->initialCoords.y <= bottom)
        return;
    RemoveObjectEvent(objectEvent);
}

void SpawnObjectEventsOnReturnToField(s16 x, s16 y)
{
    u8 i;

    ClearPlayerAvatarInfo();
    for (i = 0; i < OBJECT_EVENTS_COUNT; i++)
    {
        if (gObjectEvents[i].active)
            SpawnObjectEventOnReturnToField(i, x, y);
    }
    CreateReflectionEffectSprites();
}

static void SpawnObjectEventOnReturnToField(u8 objectEventId, s16 x, s16 y)
{
    u8 spriteId;
    struct Sprite *sprite;
    struct ObjectEvent *objectEvent;
    struct SpriteTemplate spriteTemplate;
    struct SpriteFrameImage spriteFrameImage;
    const struct SubspriteTable *subspriteTables;
    const struct ObjectEventGraphicsInfo *graphicsInfo;

#define i spriteId
    for (i = 0; i < NELEMS(gLinkPlayerObjectEvents); i++)
    {
        if (gLinkPlayerObjectEvents[i].active && objectEventId == gLinkPlayerObjectEvents[i].objEventId)
            return;
    }
#undef i

    objectEvent = &gObjectEvents[objectEventId];
    objectEvent++;objectEvent--; // fakematch
    subspriteTables = NULL;
    graphicsInfo = GetObjectEventGraphicsInfo(objectEvent->graphicsId);
    spriteFrameImage.size = graphicsInfo->size;
    CopyObjectGraphicsInfoToSpriteTemplate_WithMovementType(objectEvent->graphicsId, objectEvent->movementType, &spriteTemplate, &subspriteTables);
    spriteTemplate.images = &spriteFrameImage;

    *(u16 *)&spriteTemplate.paletteTag = TAG_NONE;
    if (graphicsInfo->paletteSlot == PALSLOT_PLAYER)
        LoadPlayerObjectReflectionPalette(graphicsInfo->paletteTag, graphicsInfo->paletteSlot);

    if (graphicsInfo->paletteSlot >= PALSLOT_NPC_SPECIAL)
        LoadSpecialObjectReflectionPalette(graphicsInfo->paletteTag, graphicsInfo->paletteSlot);

    *(u16 *)&spriteTemplate.paletteTag = TAG_NONE;
    spriteId = CreateSprite(&spriteTemplate, 0, 0, 0);
    if (spriteId != MAX_SPRITES)
    {
        sprite = &gSprites[spriteId];
        GetMapCoordsFromSpritePos(x + objectEvent->currentCoords.x, y + objectEvent->currentCoords.y, &sprite->x, &sprite->y);
        sprite->centerToCornerVecX = -(graphicsInfo->width >> 1);
        sprite->centerToCornerVecY = -(graphicsInfo->height >> 1);
        sprite->x += 8;
        sprite->y += 16 + sprite->centerToCornerVecY;
        sprite->images = graphicsInfo->images;
        if (objectEvent->movementType == MOVEMENT_TYPE_PLAYER)
        {
            SetPlayerAvatarObjectEventIdAndObjectId(objectEventId, spriteId);
            objectEvent->warpArrowSpriteId = CreateWarpArrowSprite();
        }
        if (subspriteTables != NULL)
            SetSubspriteTables(sprite, subspriteTables);

        sprite->oam.paletteNum = graphicsInfo->paletteSlot;
        sprite->coordOffsetEnabled = TRUE;
        sprite->data[0] = objectEventId;
        objectEvent->spriteId = spriteId;
        if (!objectEvent->inanimate && objectEvent->movementType != MOVEMENT_TYPE_PLAYER)
            StartSpriteAnim(sprite, GetFaceDirectionAnimNum(objectEvent->facingDirection));

        ResetObjectEventFldEffData(objectEvent);
        SetObjectSubpriorityByElevation(objectEvent->previousElevation, sprite, 1);
    }
}

static void ResetObjectEventFldEffData(struct ObjectEvent *objectEvent)
{
    objectEvent->singleMovementActive = FALSE;
    objectEvent->triggerGroundEffectsOnMove = TRUE;
    objectEvent->hasShadow = FALSE;
    objectEvent->hasReflection = FALSE;
    objectEvent->inShortGrass = FALSE;
    objectEvent->inShallowFlowingWater = FALSE;
    objectEvent->inSandPile = FALSE;
    objectEvent->inHotSprings = FALSE;
    ObjectEventClearHeldMovement(objectEvent);
}

static void SetPlayerAvatarObjectEventIdAndObjectId(u8 objectEventId, u8 spriteId)
{
    gPlayerAvatar.objectEventId = objectEventId;
    gPlayerAvatar.spriteId = spriteId;
    gPlayerAvatar.gender = GetPlayerAvatarGenderByGraphicsId(gObjectEvents[objectEventId].graphicsId);
    SetPlayerAvatarExtraStateTransition(gObjectEvents[objectEventId].graphicsId, PLAYER_AVATAR_FLAG_CONTROLLABLE);
}

void ObjectEventSetGraphicsId(struct ObjectEvent *objectEvent, u8 graphicsId)
{
    const struct ObjectEventGraphicsInfo *graphicsInfo;
    struct Sprite *sprite;
    u8 var;
    u8 var3;

    graphicsInfo = GetObjectEventGraphicsInfo(graphicsId);
    sprite = &gSprites[objectEvent->spriteId];
    if (graphicsInfo->paletteSlot == PALSLOT_PLAYER)
        PatchObjectPalette(graphicsInfo->paletteTag, graphicsInfo->paletteSlot);

    if (graphicsInfo->paletteSlot == PALSLOT_NPC_SPECIAL)
        LoadSpecialObjectReflectionPalette(graphicsInfo->paletteTag, graphicsInfo->paletteSlot);
    
    var = sprite->images->size / TILE_SIZE_4BPP;
    if (!sprite->usingSheet)
    {
        FreeSpriteTilesIfNotUsingSheet(sprite);
    }
    sprite->oam.shape = graphicsInfo->oam->shape;
    sprite->oam.size = graphicsInfo->oam->size;
    sprite->images = graphicsInfo->images;
    sprite->anims = graphicsInfo->anims;
    sprite->subspriteTables = graphicsInfo->subspriteTables;
    sprite->oam.paletteNum = graphicsInfo->paletteSlot;
    if (!sprite->usingSheet)
    {
        s32 var2;
        var3 = sprite->images->size / TILE_SIZE_4BPP;
        var2 = AllocSpriteTiles(var3);
        if (var2 == -1)
        {
            var2 = AllocSpriteTiles(var);    
        }
        sprite->oam.tileNum = var2;
    }
    objectEvent->inanimate = graphicsInfo->inanimate;
    objectEvent->graphicsId = graphicsId;  
    SetSpritePosToMapCoords(objectEvent->currentCoords.x, objectEvent->currentCoords.y, &sprite->x, &sprite->y);
    sprite->centerToCornerVecX = -(graphicsInfo->width >> 1);
    sprite->centerToCornerVecY = -(graphicsInfo->height >> 1);
    sprite->x += 8;
    sprite->y += 16 + sprite->centerToCornerVecY;
    if (objectEvent->trackedByCamera)
    {
        CameraObjectReset1();
    }
}

void ObjectEventSetGraphicsIdByLocalIdAndMap(u8 localId, u8 mapNum, u8 mapGroup, u8 graphicsId)
{
    u8 objectEventId;

    if (!TryGetObjectEventIdByLocalIdAndMap(localId, mapNum, mapGroup, &objectEventId))
    {
        ObjectEventSetGraphicsId(&gObjectEvents[objectEventId], graphicsId);
    }
}

void ObjectEventTurn(struct ObjectEvent *objectEvent, u8 direction)
{
    SetObjectEventDirection(objectEvent, direction);
    if (!objectEvent->inanimate)
    {
        StartSpriteAnim(&gSprites[objectEvent->spriteId], GetFaceDirectionAnimNum(objectEvent->facingDirection));
        SeekSpriteAnim(&gSprites[objectEvent->spriteId], 0);
    }
}

void ObjectEventTurnByLocalIdAndMap(u8 localId, u8 mapNum, u8 mapGroup, u8 direction)
{
    u8 objectEventId;

    if (!TryGetObjectEventIdByLocalIdAndMap(localId, mapNum, mapGroup, &objectEventId))
    {
        ObjectEventTurn(&gObjectEvents[objectEventId], direction);
    }
}

void PlayerObjectTurn(struct PlayerAvatar *playerAvatar, u8 direction)
{
    ObjectEventTurn(&gObjectEvents[playerAvatar->objectEventId], direction);
}

const struct ObjectEventGraphicsInfo *GetObjectEventGraphicsInfo(u8 graphicsId)
{
    if (graphicsId >= OBJ_EVENT_GFX_VARS)
        graphicsId = VarGetObjectEventGraphicsId(graphicsId - OBJ_EVENT_GFX_VARS);
    
    if (graphicsId >= NUM_OBJ_EVENT_GFX)
        graphicsId = OBJ_EVENT_GFX_LITTLE_BOY;
    
    return gObjectEventGraphicsInfoPointers[graphicsId];
}

static void SetObjectEventDynamicGraphicsId(struct ObjectEvent *objectEvent)
{
    if (objectEvent->graphicsId >= OBJ_EVENT_GFX_VARS)
    {
        objectEvent->graphicsId = VarGetObjectEventGraphicsId(objectEvent->graphicsId - OBJ_EVENT_GFX_VARS);
    }
}

void SetObjectInvisibility(u8 localId, u8 mapNum, u8 mapGroup, u8 state)
{
    u8 objectEventId;

    if (!TryGetObjectEventIdByLocalIdAndMap(localId, mapNum, mapGroup, &objectEventId))
    {
        gObjectEvents[objectEventId].invisible = state;
    }
}

void ObjectEventGetLocalIdAndMap(struct ObjectEvent *objectEvent, void *localId, void *mapNum, void *mapGroup)
{
    *(u8 *)(localId) = objectEvent->localId;
    *(u8 *)(mapNum) = objectEvent->mapNum;
    *(u8 *)(mapGroup) = objectEvent->mapGroup;
}

void EnableObjectGroundEffectsByXY(s16 x, s16 y)
{
    u8 objectEventId;
    struct ObjectEvent *objectEvent;

    objectEventId = GetObjectEventIdByXY(x, y);
    if (objectEventId != OBJECT_EVENTS_COUNT)
    {
        objectEvent = &gObjectEvents[objectEventId];
        objectEvent->triggerGroundEffectsOnMove = TRUE;
    }
}

void SetObjectSubpriority(u8 localId, u8 mapNum, u8 mapGroup, u8 subpriority)
{
    u8 objectEventId;
    struct ObjectEvent *objectEvent;
    struct Sprite *sprite;

    if (!TryGetObjectEventIdByLocalIdAndMap(localId, mapNum, mapGroup, &objectEventId))
    {
        objectEvent = &gObjectEvents[objectEventId];
        sprite = &gSprites[objectEvent->spriteId];
        objectEvent->fixedPriority = TRUE;
        sprite->subpriority = subpriority;
    }
}

void ResetObjectSubpriority(u8 localId, u8 mapNum, u8 mapGroup)
{
    u8 objectEventId;
    struct ObjectEvent *objectEvent;

    if (!TryGetObjectEventIdByLocalIdAndMap(localId, mapNum, mapGroup, &objectEventId))
    {
        objectEvent = &gObjectEvents[objectEventId];
        objectEvent->fixedPriority = FALSE;
        objectEvent->triggerGroundEffectsOnMove = TRUE;
    }
}

void SetObjectPositionByLocalIdAndMap(u8 localId, u8 mapNum, u8 mapGroup, s16 x, s16 y)
{
    u8 objectEventId;
    struct Sprite *sprite;

    if (!TryGetObjectEventIdByLocalIdAndMap(localId, mapNum, mapGroup, &objectEventId))
    {
        sprite = &gSprites[gObjectEvents[objectEventId].spriteId];
        sprite->x2 = x;
        sprite->y2 = y;
    }
}

void FreeAndReserveObjectSpritePalettes(void)
{
    FreeAllSpritePalettes();
    gReservedSpritePaletteCount = OBJ_PALSLOT_COUNT;
}

static void LoadObjectEventPalette(u16 paletteTag)
{
    u16 i = FindObjectEventPaletteIndexByTag(paletteTag);

#ifdef BUGFIX
    if (sObjectEventSpritePalettes[i].tag != OBJ_EVENT_PAL_TAG_NONE)
#else
    if (i != OBJ_EVENT_PAL_TAG_NONE) // always true
#endif
    {
        TryLoadObjectPalette(&sObjectEventSpritePalettes[i]);
    }
}

// Unused
void LoadObjectEventPaletteSet(u16 *paletteTags)
{
    u8 i;

    for (i = 0; paletteTags[i] != OBJ_EVENT_PAL_TAG_NONE; i++)
    {
        LoadObjectEventPalette(paletteTags[i]);
    }
}

static u8 TryLoadObjectPalette(const struct SpritePalette *spritePalette)
{
    if (IndexOfSpritePaletteTag(spritePalette->tag) != 0xFF)
    {
        // Already loaded
        return 0xFF;
    }
    return LoadSpritePalette(spritePalette);
}

void PatchObjectPalette(u16 paletteTag, u8 paletteSlot)
{
    u8 paletteIndex = FindObjectEventPaletteIndexByTag(paletteTag);

    LoadPalette(sObjectEventSpritePalettes[paletteIndex].data, OBJ_PLTT_ID(paletteSlot), PLTT_SIZE_4BPP);
    ApplyGlobalFieldPaletteTint(paletteSlot);
}

void PatchObjectPaletteRange(const u16 *paletteTags, u8 minSlot, u8 maxSlot)
{
    while (minSlot < maxSlot)
    {
        PatchObjectPalette(*paletteTags, minSlot);
        paletteTags++;
        minSlot++;
    }
}

static u8 FindObjectEventPaletteIndexByTag(u16 tag)
{
    u8 i;

    for (i = 0; sObjectEventSpritePalettes[i].tag != OBJ_EVENT_PAL_TAG_NONE; i++)
    {
        if (sObjectEventSpritePalettes[i].tag == tag)
        {
            return i;
        }
    }
    return 0xFF;
}

void LoadPlayerObjectReflectionPalette(u16 tag, u8 slot)
{
    u8 i;

    PatchObjectPalette(tag, slot);
    for (i = 0; gPlayerReflectionPaletteSets[i].tag != OBJ_EVENT_PAL_TAG_NONE; i++)
    {
        if (gPlayerReflectionPaletteSets[i].tag == tag)
        {
            PatchObjectPalette(gPlayerReflectionPaletteSets[i].data[sCurrentReflectionType], gReflectionEffectPaletteMap[slot]);
            return;
        }
    }
}

void LoadSpecialObjectReflectionPalette(u16 tag, u8 slot)
{
    u8 i;

    sCurrentSpecialObjectPaletteTag = tag;
    PatchObjectPalette(tag, slot);
    for (i = 0; gSpecialObjectReflectionPaletteSets[i].tag != OBJ_EVENT_PAL_TAG_NONE; i++)
    {
        if (gSpecialObjectReflectionPaletteSets[i].tag == tag)
        {
            PatchObjectPalette(gSpecialObjectReflectionPaletteSets[i].data[sCurrentReflectionType], gReflectionEffectPaletteMap[slot]);
            return;
        }
    }
}

// Unused
static u8 GetReflectionEffectPaletteSlot(u8 slot)
{
    return gReflectionEffectPaletteMap[slot];
}

// Unused
void IncrementObjectEventCoords(struct ObjectEvent *objectEvent, s16 x, s16 y)
{
    objectEvent->previousCoords.x = objectEvent->currentCoords.x;
    objectEvent->previousCoords.y = objectEvent->currentCoords.y;
    objectEvent->currentCoords.x += x;
    objectEvent->currentCoords.y += y;
}

void ShiftObjectEventCoords(struct ObjectEvent *objectEvent, s16 x, s16 y)
{
    objectEvent->previousCoords.x = objectEvent->currentCoords.x;
    objectEvent->previousCoords.y = objectEvent->currentCoords.y;
    objectEvent->currentCoords.x = x;
    objectEvent->currentCoords.y = y;
}

static void SetObjectEventCoords(struct ObjectEvent *objectEvent, s16 x, s16 y)
{
    objectEvent->previousCoords.x = x;
    objectEvent->previousCoords.y = y;
    objectEvent->currentCoords.x = x;
    objectEvent->currentCoords.y = y;
}

void MoveObjectEventToMapCoords(struct ObjectEvent *objectEvent, s16 x, s16 y)
{
    struct Sprite *sprite;
    const struct ObjectEventGraphicsInfo *graphicsInfo;

    sprite = &gSprites[objectEvent->spriteId];
    graphicsInfo = GetObjectEventGraphicsInfo(objectEvent->graphicsId);
    SetObjectEventCoords(objectEvent, x, y);
    SetSpritePosToMapCoords(objectEvent->currentCoords.x, objectEvent->currentCoords.y, &sprite->x, &sprite->y);
    sprite->centerToCornerVecX = -(graphicsInfo->width >> 1);
    sprite->centerToCornerVecY = -(graphicsInfo->height >> 1);
    sprite->x += 8;
    sprite->y += 16 + sprite->centerToCornerVecY;
    ResetObjectEventFldEffData(objectEvent);
    if (objectEvent->trackedByCamera)
        CameraObjectReset1();
}

void TryMoveObjectEventToMapCoords(u8 localId, u8 mapNum, u8 mapGroup, s16 x, s16 y)
{
    u8 objectEventId;
    if (!TryGetObjectEventIdByLocalIdAndMap(localId, mapNum, mapGroup, &objectEventId))
    {
        x += MAP_OFFSET;
        y += MAP_OFFSET;
        MoveObjectEventToMapCoords(&gObjectEvents[objectEventId], x, y);
    }
}

void ShiftStillObjectEventCoords(struct ObjectEvent *objectEvent)
{
    ShiftObjectEventCoords(objectEvent, objectEvent->currentCoords.x, objectEvent->currentCoords.y);
}

void UpdateObjectEventCoordsForCameraUpdate(void)
{
    u8 i;
    s16 dx;
    s16 dy;

    if (gCamera.active)
    {
        dx = gCamera.x;
        dy = gCamera.y;
        for (i = 0; i < OBJECT_EVENTS_COUNT; i++)
        {
            if (gObjectEvents[i].active)
            {
                gObjectEvents[i].initialCoords.x -= dx;
                gObjectEvents[i].initialCoords.y -= dy;
                gObjectEvents[i].currentCoords.x -= dx;
                gObjectEvents[i].currentCoords.y -= dy;
                gObjectEvents[i].previousCoords.x -= dx;
                gObjectEvents[i].previousCoords.y -= dy;
            }
        }
    }
}

u8 GetObjectEventIdByPosition(u16 x, u16 y, u8 elevation)
{
    u8 i;

    for (i = 0; i < OBJECT_EVENTS_COUNT; i++)
    {
        if (gObjectEvents[i].active)
        {
            if (gObjectEvents[i].currentCoords.x == x
             && gObjectEvents[i].currentCoords.y == y
             && ObjectEventDoesElevationMatch(&gObjectEvents[i], elevation))
                return i;
        }
    }
    return OBJECT_EVENTS_COUNT;
}

static bool8 ObjectEventDoesElevationMatch(struct ObjectEvent *objectEvent, u8 elevation)
{
    if (objectEvent->currentElevation != 0 && elevation != 0 && objectEvent->currentElevation != elevation)
        return FALSE;

    return TRUE;
}

void UpdateObjectEventsForCameraUpdate(s16 x, s16 y)
{
    UpdateObjectEventCoordsForCameraUpdate();
    TrySpawnObjectEvents(x, y);
    RemoveObjectEventsOutsideView();
}

u8 AddCameraObject(u8 linkedSpriteId)
{
    u8 spriteId = CreateSprite(&gCameraSpriteTemplate, 0, 0, 4);

    gSprites[spriteId].invisible = TRUE;
    gSprites[spriteId].data[0] = linkedSpriteId;
    return spriteId;
}

static void ObjectCB_CameraObject(struct Sprite *sprite)
{
    void (*callbacks[NELEMS(gCameraObjectFuncs)])(struct Sprite *);

    memcpy(callbacks, gCameraObjectFuncs, sizeof gCameraObjectFuncs);
    callbacks[sprite->data[1]](sprite);
}

static void CameraObject_0(struct Sprite *sprite)
{
    sprite->x = gSprites[sprite->data[0]].x;
    sprite->y = gSprites[sprite->data[0]].y;
    sprite->invisible = TRUE;
    sprite->data[1] = 1;
    CameraObject_1(sprite);
}

static void CameraObject_1(struct Sprite *sprite)
{
    s16 x = gSprites[sprite->data[0]].x;
    s16 y = gSprites[sprite->data[0]].y;

    sprite->data[2] = x - sprite->x;
    sprite->data[3] = y - sprite->y;
    sprite->x = x;
    sprite->y = y;
}

static void CameraObject_2(struct Sprite *sprite)
{
    sprite->x = gSprites[sprite->data[0]].x;
    sprite->y = gSprites[sprite->data[0]].y;
    sprite->data[2] = 0;
    sprite->data[3] = 0;
}

static struct Sprite *FindCameraObject(void)
{
    u8 i;

    for (i = 0; i < MAX_SPRITES; i++)
    {
        if (gSprites[i].inUse && gSprites[i].callback == ObjectCB_CameraObject)
        {
            return &gSprites[i];
        }
    }
    return NULL;
}

void CameraObjectReset1(void)
{
    struct Sprite *cameraObject;

    cameraObject = FindCameraObject();
    if (cameraObject != NULL)
    {
        cameraObject->data[1] = 0;
        cameraObject->callback(cameraObject);
    }
}

void CameraObjectSetFollowedObjectId(u8 objectId)
{
    struct Sprite *cameraObject;

    cameraObject = FindCameraObject();
    if (cameraObject != NULL)
    {
        cameraObject->data[0] = objectId;
        CameraObjectReset1();
    }
}

u8 CameraObjectGetFollowedObjectId(void)
{
    struct Sprite *cameraObject;

    cameraObject = FindCameraObject();
    if (cameraObject == NULL)
    {
        return MAX_SPRITES;
    }
    return cameraObject->data[0];
}

void CameraObjectReset2(void)
{
    struct Sprite *cameraObject = FindCameraObject();
#ifdef UBFIX
    if (cameraObject == NULL)
        return;
#endif
    cameraObject->data[1] = 2;
}

u8 CopySprite(struct Sprite *sprite, s16 x, s16 y, u8 subpriority)
{
    u8 i;

    for (i = 0; i < MAX_SPRITES; i++)
    {
        if (!gSprites[i].inUse)
        {
            gSprites[i] = *sprite;
            gSprites[i].x = x;
            gSprites[i].y = y;
            gSprites[i].subpriority = subpriority;
            break;
        }
    }
    return i;
}

u8 CreateCopySpriteAt(struct Sprite *sprite, s16 x, s16 y, u8 subpriority)
{
    s16 i;

    for (i = MAX_SPRITES - 1; i > -1; i--)
    {
        if (!gSprites[i].inUse)
        {
            gSprites[i] = *sprite;
            gSprites[i].x = x;
            gSprites[i].y = y;
            gSprites[i].subpriority = subpriority;
            return i;
        }
    }
    return MAX_SPRITES;
}

void SetObjectEventDirection(struct ObjectEvent *objectEvent, u8 direction)
{
    s8 d2;
    objectEvent->previousMovementDirection = objectEvent->facingDirection;
    if (!objectEvent->facingDirectionLocked)
    {
        d2 = direction;
        objectEvent->facingDirection = d2;
    }
    objectEvent->movementDirection = direction;
}

static const u8 *GetObjectEventScriptPointerByLocalIdAndMap(u8 localId, u8 mapNum, u8 mapGroup)
{
    return GetObjectEventTemplateByLocalIdAndMap(localId, mapNum, mapGroup)->script;
}

const u8 *GetObjectEventScriptPointerByObjectEventId(u8 objectEventId)
{
    return GetObjectEventScriptPointerByLocalIdAndMap(gObjectEvents[objectEventId].localId, gObjectEvents[objectEventId].mapNum, gObjectEvents[objectEventId].mapGroup);
}

static u16 GetObjectEventFlagIdByLocalIdAndMap(u8 localId, u8 mapNum, u8 mapGroup)
{
    const struct ObjectEventTemplate *obj = GetObjectEventTemplateByLocalIdAndMap(localId, mapNum, mapGroup);
#ifdef UBFIX
    // BUG: The function may return NULL, and attempting to read from NULL may freeze the game using modern compilers.
    if (obj == NULL)
        return 0;
#endif // UBFIX
    return obj->flagId;
}

static u16 GetObjectEventFlagIdByObjectEventId(u8 objectEventId)
{
    return GetObjectEventFlagIdByLocalIdAndMap(gObjectEvents[objectEventId].localId, gObjectEvents[objectEventId].mapNum, gObjectEvents[objectEventId].mapGroup);
}

// Unused
u8 GetObjectTrainerTypeByLocalIdAndMap(u8 localId, u8 mapNum, u8 mapGroup)
{
    u8 objectEventId;

    if (TryGetObjectEventIdByLocalIdAndMap(localId, mapNum, mapGroup, &objectEventId))
        return 0xFF;

    return gObjectEvents[objectEventId].trainerType;
}

u16 GetBoulderRevealFlagByLocalIdAndMap(u8 localId, u8 mapNum, u8 mapGroup)
{
    // Pushable boulder object events store the flag to reveal the boulder
    // on the floor below in their trainer type field.
    return GetObjectEventTemplateByLocalIdAndMap(localId, mapNum, mapGroup)->objUnion.normal.trainerType;
}

// Unused
u8 GetObjectTrainerTypeByObjectEventId(u8 objectEventId)
{
    return gObjectEvents[objectEventId].trainerType;
}

// Unused
u8 GetObjectEventBerryTreeIdByLocalIdAndMap(u8 localId, u8 mapNum, u8 mapGroup)
{
    u8 objectEventId;

    if (TryGetObjectEventIdByLocalIdAndMap(localId, mapNum, mapGroup, &objectEventId))
        return 0xFF;

    return gObjectEvents[objectEventId].trainerRange_berryTreeId;
}

// Unused
u8 GetObjectEventBerryTreeId(u8 objectEventId)
{
    return gObjectEvents[objectEventId].trainerRange_berryTreeId;
}

static const struct ObjectEventTemplate *GetObjectEventTemplateByLocalIdAndMap(u8 localId, u8 mapNum, u8 mapGroup)
{
    const struct ObjectEventTemplate *templates;
    const struct MapHeader *mapHeader;
    u8 count;

    if (gSaveBlock1Ptr->location.mapNum == mapNum && gSaveBlock1Ptr->location.mapGroup == mapGroup)
    {
        templates = gSaveBlock1Ptr->objectEventTemplates;
        count = gMapHeader.events->objectEventCount;
    }
    else
    {
        mapHeader = Overworld_GetMapHeaderByGroupAndId(mapGroup, mapNum);
        templates = mapHeader->events->objectEvents;
        count = mapHeader->events->objectEventCount;
    }
    return FindObjectEventTemplateByLocalId(localId, templates, count);
}

static const struct ObjectEventTemplate *FindObjectEventTemplateByLocalId(u8 localId, const struct ObjectEventTemplate *templates, u8 count)
{
    u8 i;

    for (i = 0; i < count; i++)
    {
        if (templates[i].localId == localId)
        {
            return &templates[i];
        }
    }
    return NULL;
}

struct ObjectEventTemplate *GetBaseTemplateForObjectEvent(const struct ObjectEvent *objectEvent)
{
    int i;

    if (objectEvent->mapNum != gSaveBlock1Ptr->location.mapNum || objectEvent->mapGroup != gSaveBlock1Ptr->location.mapGroup)
    {
        return NULL;
    }
    for (i = 0; i < OBJECT_EVENT_TEMPLATES_COUNT; i++)
    {
        if ((objectEvent->localId == gSaveBlock1Ptr->objectEventTemplates[i].localId)
         && (objectEvent->mapNum == gSaveBlock1Ptr->location.mapNum)
         && (objectEvent->mapGroup == gSaveBlock1Ptr->location.mapGroup))
            return &gSaveBlock1Ptr->objectEventTemplates[i];
    }
    return NULL;
}

void OverrideTemplateCoordsForObjectEvent(const struct ObjectEvent *objectEvent)
{
    struct ObjectEventTemplate *objectEventTemplate;

    objectEventTemplate = GetBaseTemplateForObjectEvent(objectEvent);
    if (objectEventTemplate != NULL)
    {
        objectEventTemplate->x = objectEvent->currentCoords.x - MAP_OFFSET;
        objectEventTemplate->y = objectEvent->currentCoords.y - MAP_OFFSET;
    }
}

void OverrideMovementTypeForObjectEvent(const struct ObjectEvent *objectEvent, u8 movementType)
{
    struct ObjectEventTemplate *objectEventTemplate;

    objectEventTemplate = GetBaseTemplateForObjectEvent(objectEvent);
    if (objectEventTemplate != NULL)
    {
        objectEventTemplate->objUnion.normal.movementType = movementType;
    }
}

void TryOverrideObjectEventTemplateCoords(u8 localId, u8 mapNum, u8 mapGroup)
{
    u8 objectEventId;
    if (!TryGetObjectEventIdByLocalIdAndMap(localId, mapNum, mapGroup, &objectEventId))
        OverrideTemplateCoordsForObjectEvent(&gObjectEvents[objectEventId]);
}

void InitObjectEventPalettes(u8 palSlot)
{
    FreeAndReserveObjectSpritePalettes();
    sCurrentSpecialObjectPaletteTag = OBJ_EVENT_PAL_TAG_NONE;
    sCurrentReflectionType = palSlot;
    if (palSlot == 1)
    {
        PatchObjectPaletteRange(gObjectPaletteTagSets[sCurrentReflectionType], 0, 6);
        gReservedSpritePaletteCount = 8;
    }
    else
    {
        PatchObjectPaletteRange(gObjectPaletteTagSets[sCurrentReflectionType], 0, 10);
    }
}

u16 GetObjectPaletteTag(u8 palSlot)
{
    u8 i;

    if (palSlot < 10)
    {
        return gObjectPaletteTagSets[sCurrentReflectionType][palSlot];
    }
    for (i = 0; gSpecialObjectReflectionPaletteSets[i].tag != OBJ_EVENT_PAL_TAG_NONE; i++)
    {
        if (gSpecialObjectReflectionPaletteSets[i].tag == sCurrentSpecialObjectPaletteTag)
        {
            return gSpecialObjectReflectionPaletteSets[i].data[sCurrentReflectionType];
        }
    }
    return OBJ_EVENT_PAL_TAG_NONE;
}

movement_type_empty_callback(MovementType_None)
movement_type_def(MovementType_WanderAround, gMovementTypeFuncs_WanderAround)
movement_type_def(MovementType_WanderAroundSlower, gMovementTypeFuncs_WanderAroundSlower)

static bool8 MovementType_WanderAround_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    ClearObjectEventMovement(objectEvent, sprite);
    sprite->data[1] = 1;
    return TRUE;
}

static bool8 MovementType_WanderAround_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    ObjectEventSetSingleMovement(objectEvent, sprite, GetFaceDirectionMovementAction(objectEvent->facingDirection));
    sprite->data[1] = 2;
    return TRUE;
}

static bool8 MovementType_WanderAround_Step2(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (!ObjectEventExecSingleMovementAction(objectEvent, sprite))
    {
        return FALSE;
    }
    SetMovementDelay(sprite, gMovementDelaysMedium[Random() & 3]);
    sprite->data[1] = 3;
    return TRUE;
}

static bool8 MovementType_WanderAround_Step3(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (WaitForMovementDelay(sprite))
    {
        sprite->data[1] = 4;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementType_WanderAround_Step4(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    u8 directions[4];
    u8 chosenDirection;

    memcpy(directions, gStandardDirections, sizeof directions);
    chosenDirection = directions[Random() & 3];
    SetObjectEventDirection(objectEvent, chosenDirection);
    sprite->data[1] = 5;
    if (GetCollisionInDirection(objectEvent, chosenDirection))
        sprite->data[1] = 1;

    return TRUE;
}

static bool8 MovementType_WanderAround_Step5(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    ObjectEventSetSingleMovement(objectEvent, sprite, GetWalkNormalMovementAction(objectEvent->movementDirection));
    objectEvent->singleMovementActive = TRUE;
    sprite->data[1] = 6;
    return TRUE;
}

static bool8 MovementType_WanderAround_Step5Slower(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    ObjectEventSetSingleMovement(objectEvent, sprite, GetWalkSlowerMovementAction(objectEvent->movementDirection));
    objectEvent->singleMovementActive = TRUE;
    sprite->data[1] = 6;
    return TRUE;
}

static bool8 MovementType_WanderAround_Step6(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (ObjectEventExecSingleMovementAction(objectEvent, sprite))
    {
        objectEvent->singleMovementActive = FALSE;
        sprite->data[1] = 1;
    }
    return FALSE;
}

bool8 ObjectEventIsTrainerAndCloseToPlayer(struct ObjectEvent *objectEvent)
{
    s16 playerX;
    s16 playerY;
    s16 objX;
    s16 objY;
    s16 minX;
    s16 maxX;
    s16 minY;
    s16 maxY;

    if (!TestPlayerAvatarFlags(PLAYER_AVATAR_FLAG_DASH))
        return FALSE;
    if (objectEvent->trainerType != TRAINER_TYPE_NORMAL && objectEvent->trainerType != TRAINER_TYPE_BURIED)
        return FALSE;
    PlayerGetDestCoords(&playerX, &playerY);
    objX = objectEvent->currentCoords.x;
    objY = objectEvent->currentCoords.y;
    minX = objX - objectEvent->trainerRange_berryTreeId;
    minY = objY - objectEvent->trainerRange_berryTreeId;
    maxX = objX + objectEvent->trainerRange_berryTreeId;
    maxY = objY + objectEvent->trainerRange_berryTreeId;
    if (minX > playerX || maxX < playerX || minY > playerY || maxY < playerY)
    {
        return FALSE;
    }
    return TRUE;
}

static u8 GetVectorDirection(s16 dx, s16 dy, s16 absdx, s16 absdy)
{
    u8 direction;

    if (absdx > absdy)
    {
        direction = DIR_EAST;
        if (dx < 0)
        {
            direction = DIR_WEST;
        }
    }
    else
    {
        direction = DIR_SOUTH;
        if (dy < 0)
        {
            direction = DIR_NORTH;
        }
    }
    return direction;
}

static u8 GetLimitedVectorDirection_SouthNorth(s16 dx, s16 dy, s16 absdx, s16 absdy)
{
    u8 direction;

    direction = DIR_SOUTH;
    if (dy < 0)
    {
        direction = DIR_NORTH;
    }
    return direction;
}

static u8 GetLimitedVectorDirection_WestEast(s16 dx, s16 dy, s16 absdx, s16 absdy)
{
    u8 direction;

    direction = DIR_EAST;
    if (dx < 0)
    {
        direction = DIR_WEST;
    }
    return direction;
}

static u8 GetLimitedVectorDirection_WestNorth(s16 dx, s16 dy, s16 absdx, s16 absdy)
{
    u8 direction;

    direction = GetVectorDirection(dx, dy, absdx, absdy);
    if (direction == DIR_SOUTH)
    {
        direction = GetLimitedVectorDirection_WestEast(dx, dy, absdx, absdy);
        if (direction == DIR_EAST)
        {
            direction = DIR_NORTH;
        }
    }
    else if (direction == DIR_EAST)
    {
        direction = GetLimitedVectorDirection_SouthNorth(dx, dy, absdx, absdy);
        if (direction == DIR_SOUTH)
        {
            direction = DIR_NORTH;
        }
    }
    return direction;
}

static u8 GetLimitedVectorDirection_EastNorth(s16 dx, s16 dy, s16 absdx, s16 absdy)
{
    u8 direction;

    direction = GetVectorDirection(dx, dy, absdx, absdy);
    if (direction == DIR_SOUTH)
    {
        direction = GetLimitedVectorDirection_WestEast(dx, dy, absdx, absdy);
        if (direction == DIR_WEST)
        {
            direction = DIR_NORTH;
        }
    }
    else if (direction == DIR_WEST)
    {
        direction = GetLimitedVectorDirection_SouthNorth(dx, dy, absdx, absdy);
        if (direction == DIR_SOUTH)
        {
            direction = DIR_NORTH;
        }
    }
    return direction;
}

static u8 GetLimitedVectorDirection_WestSouth(s16 dx, s16 dy, s16 absdx, s16 absdy)
{
    u8 direction;

    direction = GetVectorDirection(dx, dy, absdx, absdy);
    if (direction == DIR_NORTH)
    {
        direction = GetLimitedVectorDirection_WestEast(dx, dy, absdx, absdy);
        if (direction == DIR_EAST)
        {
            direction = DIR_SOUTH;
        }
    }
    else if (direction == DIR_EAST)
    {
        direction = GetLimitedVectorDirection_SouthNorth(dx, dy, absdx, absdy);
        if (direction == DIR_NORTH)
        {
            direction = DIR_SOUTH;
        }
    }
    return direction;
}

static u8 GetLimitedVectorDirection_EastSouth(s16 dx, s16 dy, s16 absdx, s16 absdy)
{
    u8 direction;

    direction = GetVectorDirection(dx, dy, absdx, absdy);
    if (direction == DIR_NORTH)
    {
        direction = GetLimitedVectorDirection_WestEast(dx, dy, absdx, absdy);
        if (direction == DIR_WEST)
        {
            direction = DIR_SOUTH;
        }
    }
    else if (direction == DIR_WEST)
    {
        direction = GetLimitedVectorDirection_SouthNorth(dx, dy, absdx, absdy);
        if (direction == DIR_NORTH)
        {
            direction = DIR_SOUTH;
        }
    }
    return direction;
}

static u8 GetLimitedVectorDirection_SouthNorthWest(s16 dx, s16 dy, s16 absdx, s16 absdy)
{
    u8 direction;

    direction = GetVectorDirection(dx, dy, absdx, absdy);
    if (direction == DIR_EAST)
    {
        direction = GetLimitedVectorDirection_SouthNorth(dx, dy, absdx, absdy);
    }
    return direction;
}

static u8 GetLimitedVectorDirection_SouthNorthEast(s16 dx, s16 dy, s16 absdx, s16 absdy)
{
    u8 direction;

    direction = GetVectorDirection(dx, dy, absdx, absdy);
    if (direction == DIR_WEST)
    {
        direction = GetLimitedVectorDirection_SouthNorth(dx, dy, absdx, absdy);
    }
    return direction;
}

static u8 GetLimitedVectorDirection_NorthWestEast(s16 dx, s16 dy, s16 absdx, s16 absdy)
{
    u8 direction;

    direction = GetVectorDirection(dx, dy, absdx, absdy);
    if (direction == DIR_SOUTH)
    {
        direction = GetLimitedVectorDirection_WestEast(dx, dy, absdx, absdy);
    }
    return direction;
}

static u8 GetLimitedVectorDirection_SouthWestEast(s16 dx, s16 dy, s16 absdx, s16 absdy)
{
    u8 direction;

    direction = GetVectorDirection(dx, dy, absdx, absdy);
    if (direction == DIR_NORTH)
    {
        direction = GetLimitedVectorDirection_WestEast(dx, dy, absdx, absdy);
    }
    return direction;
}

u8 TryGetTrainerEncounterDirection(struct ObjectEvent *objectEvent, u8 movementType)
{
    s16 dx, dy;
    s16 absdx, absdy;

    if (!ObjectEventIsTrainerAndCloseToPlayer(objectEvent))
    {
        return 0;
    }
    PlayerGetDestCoords(&dx, &dy);
    dx -= objectEvent->currentCoords.x;
    dy -= objectEvent->currentCoords.y;
    absdx = dx;
    absdy = dy;
    if (absdx < 0)
    {
        absdx = -absdx;
    }
    if (absdy < 0)
    {
        absdy = -absdy;
    }
    return gGetVectorDirectionFuncs[movementType](dx, dy, absdx, absdy);
}

movement_type_def(MovementType_LookAround, gMovementTypeFuncs_LookAround)

static bool8 MovementType_LookAround_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    ClearObjectEventMovement(objectEvent, sprite);
    sprite->data[1] = 1;
    return TRUE;
}

static bool8 MovementType_LookAround_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    ObjectEventSetSingleMovement(objectEvent, sprite, GetFaceDirectionMovementAction(objectEvent->facingDirection));
    sprite->data[1] = 2;
    return TRUE;
}

static bool8 MovementType_LookAround_Step2(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (ObjectEventExecSingleMovementAction(objectEvent, sprite))
    {
        SetMovementDelay(sprite, gMovementDelaysMedium[Random() & 3]);
        objectEvent->singleMovementActive = FALSE;
        sprite->data[1] = 3;
    }
    return FALSE;
}

static bool8 MovementType_LookAround_Step3(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (WaitForMovementDelay(sprite) || ObjectEventIsTrainerAndCloseToPlayer(objectEvent))
    {
        sprite->data[1] = 4;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementType_LookAround_Step4(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    u8 direction;
    u8 directions[4];
    memcpy(directions, gStandardDirections, sizeof directions);
    direction = TryGetTrainerEncounterDirection(objectEvent, RUNFOLLOW_ANY);
    if (direction == DIR_NONE)
        direction = directions[Random() & 3];

    SetObjectEventDirection(objectEvent, direction);
    sprite->data[1] = 1;
    return TRUE;
}

movement_type_def(MovementType_WanderUpAndDown, gMovementTypeFuncs_WanderUpAndDown)

static bool8 MovementType_WanderUpAndDown_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    ClearObjectEventMovement(objectEvent, sprite);
    sprite->data[1] = 1;
    return TRUE;
}

static bool8 MovementType_WanderUpAndDown_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    ObjectEventSetSingleMovement(objectEvent, sprite, GetFaceDirectionMovementAction(objectEvent->facingDirection));
    sprite->data[1] = 2;
    return TRUE;
}

static bool8 MovementType_WanderUpAndDown_Step2(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (!ObjectEventExecSingleMovementAction(objectEvent, sprite))
    {
        return FALSE;
    }
    SetMovementDelay(sprite, gMovementDelaysMedium[Random() & 3]);
    sprite->data[1] = 3;
    return TRUE;
}

static bool8 MovementType_WanderUpAndDown_Step3(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (WaitForMovementDelay(sprite))
    {
        sprite->data[1] = 4;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementType_WanderUpAndDown_Step4(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    u8 direction;
    u8 directions[2];
    memcpy(directions, gUpAndDownDirections, sizeof directions);
    direction = directions[Random() & 1];
    SetObjectEventDirection(objectEvent, direction);
    sprite->data[1] = 5;
    if (GetCollisionInDirection(objectEvent, direction))
        sprite->data[1] = 1;

    return TRUE;
}

static bool8 MovementType_WanderUpAndDown_Step5(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    ObjectEventSetSingleMovement(objectEvent, sprite, GetWalkNormalMovementAction(objectEvent->movementDirection));
    objectEvent->singleMovementActive = TRUE;
    sprite->data[1] = 6;
    return TRUE;
}

static bool8 MovementType_WanderUpAndDown_Step6(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (ObjectEventExecSingleMovementAction(objectEvent, sprite))
    {
        objectEvent->singleMovementActive = FALSE;
        sprite->data[1] = 1;
    }
    return FALSE;
}

movement_type_def(MovementType_WanderLeftAndRight, gMovementTypeFuncs_WanderLeftAndRight)

static bool8 MovementType_WanderLeftAndRight_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    ClearObjectEventMovement(objectEvent, sprite);
    sprite->data[1] = 1;
    return TRUE;
}

static bool8 MovementType_WanderLeftAndRight_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    ObjectEventSetSingleMovement(objectEvent, sprite, GetFaceDirectionMovementAction(objectEvent->facingDirection));
    sprite->data[1] = 2;
    return TRUE;
}

static bool8 MovementType_WanderLeftAndRight_Step2(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (!ObjectEventExecSingleMovementAction(objectEvent, sprite))
    {
        return FALSE;
    }
    SetMovementDelay(sprite, gMovementDelaysMedium[Random() & 3]);
    sprite->data[1] = 3;
    return TRUE;
}

static bool8 MovementType_WanderLeftAndRight_Step3(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (WaitForMovementDelay(sprite))
    {
        sprite->data[1] = 4;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementType_WanderLeftAndRight_Step4(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    u8 direction;
    u8 directions[2];
    memcpy(directions, gLeftAndRightDirections, sizeof directions);
    direction = directions[Random() & 1];
    SetObjectEventDirection(objectEvent, direction);
    sprite->data[1] = 5;
    if (GetCollisionInDirection(objectEvent, direction))
        sprite->data[1] = 1;

    return TRUE;
}

static bool8 MovementType_WanderLeftAndRight_Step5(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    ObjectEventSetSingleMovement(objectEvent, sprite, GetWalkNormalMovementAction(objectEvent->movementDirection));
    objectEvent->singleMovementActive = TRUE;
    sprite->data[1] = 6;
    return TRUE;
}

static bool8 MovementType_WanderLeftAndRight_Step6(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (ObjectEventExecSingleMovementAction(objectEvent, sprite))
    {
        objectEvent->singleMovementActive = FALSE;
        sprite->data[1] = 1;
    }
    return FALSE;
}

movement_type_def(MovementType_FaceDirection, gMovementTypeFuncs_FaceDirection)

static bool8 MovementType_FaceDirection_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    ClearObjectEventMovement(objectEvent, sprite);
    ObjectEventSetSingleMovement(objectEvent, sprite, GetFaceDirectionMovementAction(objectEvent->facingDirection));
    sprite->data[1] = 1;
    return TRUE;
}

static bool8 MovementType_FaceDirection_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (ObjectEventExecSingleMovementAction(objectEvent, sprite))
    {
        sprite->data[1] = 2;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementType_FaceDirection_Step2(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    objectEvent->singleMovementActive = FALSE;
    return FALSE;
}

movement_type_def(MovementType_FaceDownAndUp, gMovementTypeFuncs_FaceDownAndUp)

static bool8 MovementType_FaceDownAndUp_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    ClearObjectEventMovement(objectEvent, sprite);
    sprite->data[1] = 1;
    return TRUE;
}

static bool8 MovementType_FaceDownAndUp_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    ObjectEventSetSingleMovement(objectEvent, sprite, GetFaceDirectionMovementAction(objectEvent->facingDirection));
    sprite->data[1] = 2;
    return TRUE;
}

static bool8 MovementType_FaceDownAndUp_Step2(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (ObjectEventExecSingleMovementAction(objectEvent, sprite))
    {
        SetMovementDelay(sprite, gMovementDelaysMedium[Random() & 3]);
        objectEvent->singleMovementActive = FALSE;
        sprite->data[1] = 3;
    }
    return FALSE;
}

static bool8 MovementType_FaceDownAndUp_Step3(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (WaitForMovementDelay(sprite) || ObjectEventIsTrainerAndCloseToPlayer(objectEvent))
    {
        sprite->data[1] = 4;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementType_FaceDownAndUp_Step4(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    u8 direction;
    u8 directions[2];
    memcpy(directions, gUpAndDownDirections, sizeof gUpAndDownDirections);
    direction = TryGetTrainerEncounterDirection(objectEvent, RUNFOLLOW_NORTH_SOUTH);
    if (direction == DIR_NONE)
    {
        direction = directions[Random() & 1];
    }
    SetObjectEventDirection(objectEvent, direction);
    sprite->data[1] = 1;
    return TRUE;
}

movement_type_def(MovementType_FaceLeftAndRight, gMovementTypeFuncs_FaceLeftAndRight)

static bool8 MovementType_FaceLeftAndRight_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    ClearObjectEventMovement(objectEvent, sprite);
    sprite->data[1] = 1;
    return TRUE;
}

static bool8 MovementType_FaceLeftAndRight_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    ObjectEventSetSingleMovement(objectEvent, sprite, GetFaceDirectionMovementAction(objectEvent->facingDirection));
    sprite->data[1] = 2;
    return TRUE;
}

static bool8 MovementType_FaceLeftAndRight_Step2(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (ObjectEventExecSingleMovementAction(objectEvent, sprite))
    {
        SetMovementDelay(sprite, gMovementDelaysMedium[Random() & 3]);
        objectEvent->singleMovementActive = FALSE;
        sprite->data[1] = 3;
    }
    return FALSE;
}

static bool8 MovementType_FaceLeftAndRight_Step3(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (WaitForMovementDelay(sprite) || ObjectEventIsTrainerAndCloseToPlayer(objectEvent))
    {
        sprite->data[1] = 4;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementType_FaceLeftAndRight_Step4(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    u8 direction;
    u8 directions[2];
    memcpy(directions, gLeftAndRightDirections, sizeof gLeftAndRightDirections);
    direction = TryGetTrainerEncounterDirection(objectEvent, RUNFOLLOW_EAST_WEST);
    if (direction == DIR_NONE)
    {
        direction = directions[Random() & 1];
    }
    SetObjectEventDirection(objectEvent, direction);
    sprite->data[1] = 1;
    return TRUE;
}

movement_type_def(MovementType_FaceUpAndLeft, gMovementTypeFuncs_FaceUpAndLeft)

static bool8 MovementType_FaceUpAndLeft_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    ClearObjectEventMovement(objectEvent, sprite);
    sprite->data[1] = 1;
    return TRUE;
}

static bool8 MovementType_FaceUpAndLeft_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    ObjectEventSetSingleMovement(objectEvent, sprite, GetFaceDirectionMovementAction(objectEvent->facingDirection));
    sprite->data[1] = 2;
    return TRUE;
}

static bool8 MovementType_FaceUpAndLeft_Step2(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (ObjectEventExecSingleMovementAction(objectEvent, sprite))
    {
        SetMovementDelay(sprite, gMovementDelaysShort[Random() & 3]);
        objectEvent->singleMovementActive = FALSE;
        sprite->data[1] = 3;
    }
    return FALSE;
}

static bool8 MovementType_FaceUpAndLeft_Step3(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (WaitForMovementDelay(sprite) || ObjectEventIsTrainerAndCloseToPlayer(objectEvent))
    {
        sprite->data[1] = 4;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementType_FaceUpAndLeft_Step4(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    u8 direction;
    u8 directions[2];
    memcpy(directions, gUpAndLeftDirections, sizeof gUpAndLeftDirections);
    direction = TryGetTrainerEncounterDirection(objectEvent, RUNFOLLOW_NORTH_WEST);
    if (direction == DIR_NONE)
    {
        direction = directions[Random() & 1];
    }
    SetObjectEventDirection(objectEvent, direction);
    sprite->data[1] = 1;
    return TRUE;
}

movement_type_def(MovementType_FaceUpAndRight, gMovementTypeFuncs_FaceUpAndRight)

static bool8 MovementType_FaceUpAndRight_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    ClearObjectEventMovement(objectEvent, sprite);
    sprite->data[1] = 1;
    return TRUE;
}

static bool8 MovementType_FaceUpAndRight_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    ObjectEventSetSingleMovement(objectEvent, sprite, GetFaceDirectionMovementAction(objectEvent->facingDirection));
    sprite->data[1] = 2;
    return TRUE;
}

static bool8 MovementType_FaceUpAndRight_Step2(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (ObjectEventExecSingleMovementAction(objectEvent, sprite))
    {
        SetMovementDelay(sprite, gMovementDelaysShort[Random() & 3]);
        objectEvent->singleMovementActive = FALSE;
        sprite->data[1] = 3;
    }
    return FALSE;
}

static bool8 MovementType_FaceUpAndRight_Step3(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (WaitForMovementDelay(sprite) || ObjectEventIsTrainerAndCloseToPlayer(objectEvent))
    {
        sprite->data[1] = 4;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementType_FaceUpAndRight_Step4(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    u8 direction;
    u8 directions[2];
    memcpy(directions, gUpAndRightDirections, sizeof gUpAndRightDirections);
    direction = TryGetTrainerEncounterDirection(objectEvent, RUNFOLLOW_NORTH_EAST);
    if (direction == DIR_NONE)
    {
        direction = directions[Random() & 1];
    }
    SetObjectEventDirection(objectEvent, direction);
    sprite->data[1] = 1;
    return TRUE;
}

movement_type_def(MovementType_FaceDownAndLeft, gMovementTypeFuncs_FaceDownAndLeft)

static bool8 MovementType_FaceDownAndLeft_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    ClearObjectEventMovement(objectEvent, sprite);
    sprite->data[1] = 1;
    return TRUE;
}

static bool8 MovementType_FaceDownAndLeft_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    ObjectEventSetSingleMovement(objectEvent, sprite, GetFaceDirectionMovementAction(objectEvent->facingDirection));
    sprite->data[1] = 2;
    return TRUE;
}

static bool8 MovementType_FaceDownAndLeft_Step2(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (ObjectEventExecSingleMovementAction(objectEvent, sprite))
    {
        SetMovementDelay(sprite, gMovementDelaysShort[Random() & 3]);
        objectEvent->singleMovementActive = FALSE;
        sprite->data[1] = 3;
    }
    return FALSE;
}

static bool8 MovementType_FaceDownAndLeft_Step3(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (WaitForMovementDelay(sprite) || ObjectEventIsTrainerAndCloseToPlayer(objectEvent))
    {
        sprite->data[1] = 4;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementType_FaceDownAndLeft_Step4(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    u8 direction;
    u8 directions[2];
    memcpy(directions, gDownAndLeftDirections, sizeof gDownAndLeftDirections);
    direction = TryGetTrainerEncounterDirection(objectEvent, RUNFOLLOW_SOUTH_WEST);
    if (direction == DIR_NONE)
    {
        direction = directions[Random() & 1];
    }
    SetObjectEventDirection(objectEvent, direction);
    sprite->data[1] = 1;
    return TRUE;
}

movement_type_def(MovementType_FaceDownAndRight, gMovementTypeFuncs_FaceDownAndRight)

static bool8 MovementType_FaceDownAndRight_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    ClearObjectEventMovement(objectEvent, sprite);
    sprite->data[1] = 1;
    return TRUE;
}

static bool8 MovementType_FaceDownAndRight_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    ObjectEventSetSingleMovement(objectEvent, sprite, GetFaceDirectionMovementAction(objectEvent->facingDirection));
    sprite->data[1] = 2;
    return TRUE;
}

static bool8 MovementType_FaceDownAndRight_Step2(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (ObjectEventExecSingleMovementAction(objectEvent, sprite))
    {
        SetMovementDelay(sprite, gMovementDelaysShort[Random() & 3]);
        objectEvent->singleMovementActive = FALSE;
        sprite->data[1] = 3;
    }
    return FALSE;
}

static bool8 MovementType_FaceDownAndRight_Step3(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (WaitForMovementDelay(sprite) || ObjectEventIsTrainerAndCloseToPlayer(objectEvent))
    {
        sprite->data[1] = 4;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementType_FaceDownAndRight_Step4(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    u8 direction;
    u8 directions[2];
    memcpy(directions, gDownAndRightDirections, sizeof gDownAndRightDirections);
    direction = TryGetTrainerEncounterDirection(objectEvent, RUNFOLLOW_SOUTH_EAST);
    if (direction == DIR_NONE)
    {
        direction = directions[Random() & 1];
    }
    SetObjectEventDirection(objectEvent, direction);
    sprite->data[1] = 1;
    return TRUE;
}

movement_type_def(MovementType_FaceDownUpAndLeft, gMovementTypeFuncs_FaceDownUpAndLeft)

static bool8 MovementType_FaceDownUpAndLeft_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    ClearObjectEventMovement(objectEvent, sprite);
    sprite->data[1] = 1;
    return TRUE;
}

static bool8 MovementType_FaceDownUpAndLeft_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    ObjectEventSetSingleMovement(objectEvent, sprite, GetFaceDirectionMovementAction(objectEvent->facingDirection));
    sprite->data[1] = 2;
    return TRUE;
}

static bool8 MovementType_FaceDownUpAndLeft_Step2(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (ObjectEventExecSingleMovementAction(objectEvent, sprite))
    {
        SetMovementDelay(sprite, gMovementDelaysShort[Random() & 3]);
        objectEvent->singleMovementActive = FALSE;
        sprite->data[1] = 3;
    }
    return FALSE;
}

static bool8 MovementType_FaceDownUpAndLeft_Step3(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (WaitForMovementDelay(sprite) || ObjectEventIsTrainerAndCloseToPlayer(objectEvent))
    {
        sprite->data[1] = 4;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementType_FaceDownUpAndLeft_Step4(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    u8 direction;
    u8 directions[4];
    memcpy(directions, gDownUpAndLeftDirections, sizeof gDownUpAndLeftDirections);
    direction = TryGetTrainerEncounterDirection(objectEvent, RUNFOLLOW_NORTH_SOUTH_WEST);
    if (direction == DIR_NONE)
    {
        direction = directions[Random() & 3];
    }
    SetObjectEventDirection(objectEvent, direction);
    sprite->data[1] = 1;
    return TRUE;
}

movement_type_def(MovementType_FaceDownUpAndRight, gMovementTypeFuncs_FaceDownUpAndRight)

static bool8 MovementType_FaceDownUpAndRight_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    ClearObjectEventMovement(objectEvent, sprite);
    sprite->data[1] = 1;
    return TRUE;
}

static bool8 MovementType_FaceDownUpAndRight_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    ObjectEventSetSingleMovement(objectEvent, sprite, GetFaceDirectionMovementAction(objectEvent->facingDirection));
    sprite->data[1] = 2;
    return TRUE;
}

static bool8 MovementType_FaceDownUpAndRight_Step2(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (ObjectEventExecSingleMovementAction(objectEvent, sprite))
    {
        SetMovementDelay(sprite, gMovementDelaysShort[Random() & 3]);
        objectEvent->singleMovementActive = FALSE;
        sprite->data[1] = 3;
    }
    return FALSE;
}

static bool8 MovementType_FaceDownUpAndRight_Step3(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (WaitForMovementDelay(sprite) || ObjectEventIsTrainerAndCloseToPlayer(objectEvent))
    {
        sprite->data[1] = 4;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementType_FaceDownUpAndRight_Step4(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    u8 direction;
    u8 directions[4];
    memcpy(directions, gDownUpAndRightDirections, sizeof gDownUpAndRightDirections);
    direction = TryGetTrainerEncounterDirection(objectEvent, RUNFOLLOW_NORTH_SOUTH_EAST);
    if (direction == DIR_NONE)
    {
        direction = directions[Random() & 3];
    }
    SetObjectEventDirection(objectEvent, direction);
    sprite->data[1] = 1;
    return TRUE;
}

movement_type_def(MovementType_FaceUpRightAndLeft, gMovementTypeFuncs_FaceUpLeftAndRight)

static bool8 MovementType_FaceUpLeftAndRight_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    ClearObjectEventMovement(objectEvent, sprite);
    sprite->data[1] = 1;
    return TRUE;
}

static bool8 MovementType_FaceUpLeftAndRight_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    ObjectEventSetSingleMovement(objectEvent, sprite, GetFaceDirectionMovementAction(objectEvent->facingDirection));
    sprite->data[1] = 2;
    return TRUE;
}

static bool8 MovementType_FaceUpLeftAndRight_Step2(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (ObjectEventExecSingleMovementAction(objectEvent, sprite))
    {
        SetMovementDelay(sprite, gMovementDelaysShort[Random() & 3]);
        objectEvent->singleMovementActive = FALSE;
        sprite->data[1] = 3;
    }
    return FALSE;
}

static bool8 MovementType_FaceUpLeftAndRight_Step3(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (WaitForMovementDelay(sprite) || ObjectEventIsTrainerAndCloseToPlayer(objectEvent))
    {
        sprite->data[1] = 4;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementType_FaceUpLeftAndRight_Step4(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    u8 direction;
    u8 directions[4];
    memcpy(directions, gUpLeftAndRightDirections, sizeof gUpLeftAndRightDirections);
    direction = TryGetTrainerEncounterDirection(objectEvent, RUNFOLLOW_NORTH_EAST_WEST);
    if (direction == DIR_NONE)
    {
        direction = directions[Random() & 3];
    }
    SetObjectEventDirection(objectEvent, direction);
    sprite->data[1] = 1;
    return TRUE;
}

movement_type_def(MovementType_FaceDownRightAndLeft, gMovementTypeFuncs_FaceDownLeftAndRight)

static bool8 MovementType_FaceDownLeftAndRight_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    ClearObjectEventMovement(objectEvent, sprite);
    sprite->data[1] = 1;
    return TRUE;
}

static bool8 MovementType_FaceDownLeftAndRight_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    ObjectEventSetSingleMovement(objectEvent, sprite, GetFaceDirectionMovementAction(objectEvent->facingDirection));
    sprite->data[1] = 2;
    return TRUE;
}

static bool8 MovementType_FaceDownLeftAndRight_Step2(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (ObjectEventExecSingleMovementAction(objectEvent, sprite))
    {
        SetMovementDelay(sprite, gMovementDelaysShort[Random() & 3]);
        objectEvent->singleMovementActive = FALSE;
        sprite->data[1] = 3;
    }
    return FALSE;
}

static bool8 MovementType_FaceDownLeftAndRight_Step3(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (WaitForMovementDelay(sprite) || ObjectEventIsTrainerAndCloseToPlayer(objectEvent))
    {
        sprite->data[1] = 4;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementType_FaceDownLeftAndRight_Step4(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    u8 direction;
    u8 directions[4];
    memcpy(directions, gDownLeftAndRightDirections, sizeof gDownLeftAndRightDirections);
    direction = TryGetTrainerEncounterDirection(objectEvent, RUNFOLLOW_SOUTH_EAST_WEST);
    if (direction == DIR_NONE)
    {
        direction = directions[Random() & 3];
    }
    SetObjectEventDirection(objectEvent, direction);
    sprite->data[1] = 1;
    return TRUE;
}

movement_type_def(MovementType_RotateCounterclockwise, gMovementTypeFuncs_RotateCounterclockwise)

static bool8 MovementType_RotateCounterclockwise_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    ClearObjectEventMovement(objectEvent, sprite);
    ObjectEventSetSingleMovement(objectEvent, sprite, GetFaceDirectionMovementAction(objectEvent->facingDirection));
    sprite->data[1] = 1;
    return TRUE;
}

static bool8 MovementType_RotateCounterclockwise_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (ObjectEventExecSingleMovementAction(objectEvent, sprite))
    {
        SetMovementDelay(sprite, 48);
        sprite->data[1] = 2;
    }
    return FALSE;
}

static bool8 MovementType_RotateCounterclockwise_Step2(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (WaitForMovementDelay(sprite) || ObjectEventIsTrainerAndCloseToPlayer(objectEvent))
    {
        sprite->data[1] = 3;
    }
    return FALSE;
}

static bool8 MovementType_RotateCounterclockwise_Step3(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    u8 direction;
    u8 directions[5];
    memcpy(directions, gCounterclockwiseDirections, sizeof gCounterclockwiseDirections);
    direction = TryGetTrainerEncounterDirection(objectEvent, RUNFOLLOW_ANY);
    if (direction == DIR_NONE)
    {
        direction = directions[objectEvent->facingDirection];
    }
    SetObjectEventDirection(objectEvent, direction);
    sprite->data[1] = 0;
    return TRUE;
}

movement_type_def(MovementType_RotateClockwise, gMovementTypeFuncs_RotateClockwise)

static bool8 MovementType_RotateClockwise_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    ClearObjectEventMovement(objectEvent, sprite);
    ObjectEventSetSingleMovement(objectEvent, sprite, GetFaceDirectionMovementAction(objectEvent->facingDirection));
    sprite->data[1] = 1;
    return TRUE;
}

static bool8 MovementType_RotateClockwise_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (ObjectEventExecSingleMovementAction(objectEvent, sprite))
    {
        SetMovementDelay(sprite, 48);
        sprite->data[1] = 2;
    }
    return FALSE;
}

static bool8 MovementType_RotateClockwise_Step2(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (WaitForMovementDelay(sprite) || ObjectEventIsTrainerAndCloseToPlayer(objectEvent))
    {
        sprite->data[1] = 3;
    }
    return FALSE;
}

static bool8 MovementType_RotateClockwise_Step3(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    u8 direction;
    u8 directions[5];
    memcpy(directions, gClockwiseDirections, sizeof gClockwiseDirections);
    direction = TryGetTrainerEncounterDirection(objectEvent, RUNFOLLOW_ANY);
    if (direction == DIR_NONE)
    {
        direction = directions[objectEvent->facingDirection];
    }
    SetObjectEventDirection(objectEvent, direction);
    sprite->data[1] = 0;
    return TRUE;
}

movement_type_def(MovementType_WalkBackAndForth, gMovementTypeFuncs_WalkBackAndForth)

static bool8 MovementType_WalkBackAndForth_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    ClearObjectEventMovement(objectEvent, sprite);
    sprite->data[1] = 1;
    return TRUE;
}

static bool8 MovementType_WalkBackAndForth_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    u8 direction;

    direction = gInitialMovementTypeFacingDirections[objectEvent->movementType];
    if (objectEvent->directionSequenceIndex)
    {
        direction = GetOppositeDirection(direction);
    }
    SetObjectEventDirection(objectEvent, direction);
    sprite->data[1] = 2;
    return TRUE;
}

static bool8 MovementType_WalkBackAndForth_Step2(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    bool8 collision;
    u8 movementActionId;

    if (objectEvent->directionSequenceIndex && objectEvent->initialCoords.x == objectEvent->currentCoords.x && objectEvent->initialCoords.y == objectEvent->currentCoords.y)
    {
        objectEvent->directionSequenceIndex = 0;
        SetObjectEventDirection(objectEvent, GetOppositeDirection(objectEvent->movementDirection));
    }
    collision = GetCollisionInDirection(objectEvent, objectEvent->movementDirection);
    movementActionId = GetWalkNormalMovementAction(objectEvent->movementDirection);
    if (collision == COLLISION_OUTSIDE_RANGE)
    {
        objectEvent->directionSequenceIndex++;
        SetObjectEventDirection(objectEvent, GetOppositeDirection(objectEvent->movementDirection));
        movementActionId = GetWalkNormalMovementAction(objectEvent->movementDirection);
        collision = GetCollisionInDirection(objectEvent, objectEvent->movementDirection);
    }

    if (collision)
        movementActionId = GetWalkInPlaceNormalMovementAction(objectEvent->facingDirection);

    ObjectEventSetSingleMovement(objectEvent, sprite, movementActionId);
    objectEvent->singleMovementActive = TRUE;
    sprite->data[1] = 3;
    return TRUE;
}

static bool8 MovementType_WalkBackAndForth_Step3(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (ObjectEventExecSingleMovementAction(objectEvent, sprite))
    {
        objectEvent->singleMovementActive = FALSE;
        sprite->data[1] = 1;
    }
    return FALSE;
}

static bool8 MovementType_WalkSequence_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    ClearObjectEventMovement(objectEvent, sprite);
    sprite->data[1] = 1;
    return TRUE;
}

bool8 MoveNextDirectionInSequence(struct ObjectEvent *objectEvent, struct Sprite *sprite, u8 *route)
{
    u8 collision;
    u8 movementActionId;

    if (objectEvent->directionSequenceIndex == 3 && objectEvent->initialCoords.x == objectEvent->currentCoords.x && objectEvent->initialCoords.y == objectEvent->currentCoords.y)
        objectEvent->directionSequenceIndex = 0;

    SetObjectEventDirection(objectEvent, route[objectEvent->directionSequenceIndex]);
    movementActionId = GetWalkNormalMovementAction(objectEvent->movementDirection);
    collision = GetCollisionInDirection(objectEvent, objectEvent->movementDirection);
    if (collision == COLLISION_OUTSIDE_RANGE)
    {
        objectEvent->directionSequenceIndex++;
        SetObjectEventDirection(objectEvent, route[objectEvent->directionSequenceIndex]);
        movementActionId = GetWalkNormalMovementAction(objectEvent->movementDirection);
        collision = GetCollisionInDirection(objectEvent, objectEvent->movementDirection);
    }

    if (collision)
        movementActionId = GetWalkInPlaceNormalMovementAction(objectEvent->facingDirection);

    ObjectEventSetSingleMovement(objectEvent, sprite, movementActionId);
    objectEvent->singleMovementActive = TRUE;
    sprite->data[1] = 2;
    return TRUE;
}

static bool8 MovementType_WalkSequence_Step2(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (ObjectEventExecSingleMovementAction(objectEvent, sprite))
    {
        objectEvent->singleMovementActive = FALSE;
        sprite->data[1] = 1;
    }
    return FALSE;
}

movement_type_def(MovementType_WalkSequenceUpRightLeftDown, gMovementTypeFuncs_WalkSequenceUpRightLeftDown)

u8 MovementType_WalkSequenceUpRightLeftDown_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    u8 directions[sizeof(gUpRightLeftDownDirections)];
    memcpy(directions, gUpRightLeftDownDirections, sizeof(gUpRightLeftDownDirections));
    if (objectEvent->directionSequenceIndex == 2 && objectEvent->initialCoords.x == objectEvent->currentCoords.x)
    {
        objectEvent->directionSequenceIndex = 3;
    }
    return MoveNextDirectionInSequence(objectEvent, sprite, directions);
}

movement_type_def(MovementType_WalkSequenceRightLeftDownUp, gMovementTypeFuncs_WalkSequenceRightLeftDownUp)

u8 MovementType_WalkSequenceRightLeftDownUp_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    u8 directions[sizeof(gRightLeftDownUpDirections)];
    memcpy(directions, gRightLeftDownUpDirections, sizeof(gRightLeftDownUpDirections));
    if (objectEvent->directionSequenceIndex == 1 && objectEvent->initialCoords.x == objectEvent->currentCoords.x)
    {
        objectEvent->directionSequenceIndex = 2;
    }
    return MoveNextDirectionInSequence(objectEvent, sprite, directions);
}

movement_type_def(MovementType_WalkSequenceDownUpRightLeft, gMovementTypeFuncs_WalkSequenceDownUpRightLeft)

u8 MovementType_WalkSequenceDownUpRightLeft_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    u8 directions[sizeof(gDownUpRightLeftDirections)];
    memcpy(directions, gDownUpRightLeftDirections, sizeof(gDownUpRightLeftDirections));
    if (objectEvent->directionSequenceIndex == 1 && objectEvent->initialCoords.y == objectEvent->currentCoords.y)
    {
        objectEvent->directionSequenceIndex = 2;
    }
    return MoveNextDirectionInSequence(objectEvent, sprite, directions);
}

movement_type_def(MovementType_WalkSequenceLeftDownUpRight, gMovementTypeFuncs_WalkSequenceLeftDownUpRight)

u8 MovementType_WalkSequenceLeftDownUpRight_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    u8 directions[sizeof(gLeftDownUpRightDirections)];
    memcpy(directions, gLeftDownUpRightDirections, sizeof(gLeftDownUpRightDirections));
    if (objectEvent->directionSequenceIndex == 2 && objectEvent->initialCoords.y == objectEvent->currentCoords.y)
    {
        objectEvent->directionSequenceIndex = 3;
    }
    return MoveNextDirectionInSequence(objectEvent, sprite, directions);
}

movement_type_def(MovementType_WalkSequenceUpLeftRightDown, gMovementTypeFuncs_WalkSequenceUpLeftRightDown)

u8 MovementType_WalkSequenceUpLeftRightDown_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    u8 directions[sizeof(gUpLeftRightDownDirections)];
    memcpy(directions, gUpLeftRightDownDirections, sizeof(gUpLeftRightDownDirections));
    if (objectEvent->directionSequenceIndex == 2 && objectEvent->initialCoords.x == objectEvent->currentCoords.x)
    {
        objectEvent->directionSequenceIndex = 3;
    }
    return MoveNextDirectionInSequence(objectEvent, sprite, directions);
}

movement_type_def(MovementType_WalkSequenceLeftRightDownUp, gMovementTypeFuncs_WalkSequenceLeftRightDownUp)

u8 MovementType_WalkSequenceLeftRightDownUp_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    u8 directions[sizeof(gLeftRightDownUpDirections)];
    memcpy(directions, gLeftRightDownUpDirections, sizeof(gLeftRightDownUpDirections));
    if (objectEvent->directionSequenceIndex == 1 && objectEvent->initialCoords.x == objectEvent->currentCoords.x)
    {
        objectEvent->directionSequenceIndex = 2;
    }
    return MoveNextDirectionInSequence(objectEvent, sprite, directions);
}

movement_type_def(MovementType_WalkSequenceDownUpLeftRight, gMovementTypeFuncs_WalkSequenceDownUpLeftRight)

u8 MovementType_WalkSequenceDownUpLeftRight_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    u8 directions[sizeof(gStandardDirections)];
    memcpy(directions, gStandardDirections, sizeof(gStandardDirections));
    if (objectEvent->directionSequenceIndex == 1 && objectEvent->initialCoords.y == objectEvent->currentCoords.y)
    {
        objectEvent->directionSequenceIndex = 2;
    }
    return MoveNextDirectionInSequence(objectEvent, sprite, directions);
}

movement_type_def(MovementType_WalkSequenceRightDownUpLeft, gMovementTypeFuncs_WalkSequenceRightDownUpLeft)

u8 MovementType_WalkSequenceRightDownUpLeft_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    u8 directions[sizeof(gRightDownUpLeftDirections)];
    memcpy(directions, gRightDownUpLeftDirections, sizeof(gRightDownUpLeftDirections));
    if (objectEvent->directionSequenceIndex == 2 && objectEvent->initialCoords.y == objectEvent->currentCoords.y)
    {
        objectEvent->directionSequenceIndex = 3;
    }
    return MoveNextDirectionInSequence(objectEvent, sprite, directions);
}

movement_type_def(MovementType_WalkSequenceLeftUpDownRight, gMovementTypeFuncs_WalkSequenceLeftUpDownRight)

u8 MovementType_WalkSequenceLeftUpDownRight_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    u8 directions[sizeof(gLeftUpDownRightDirections)];
    memcpy(directions, gLeftUpDownRightDirections, sizeof(gLeftUpDownRightDirections));
    if (objectEvent->directionSequenceIndex == 2 && objectEvent->initialCoords.y == objectEvent->currentCoords.y)
    {
        objectEvent->directionSequenceIndex = 3;
    }
    return MoveNextDirectionInSequence(objectEvent, sprite, directions);
}

movement_type_def(MovementType_WalkSequenceUpDownRightLeft, gMovementTypeFuncs_WalkSequenceUpDownRightLeft)

u8 MovementType_WalkSequenceUpDownRightLeft_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    u8 directions[sizeof(gUpDownRightLeftDirections)];
    memcpy(directions, gUpDownRightLeftDirections, sizeof(gUpDownRightLeftDirections));
    if (objectEvent->directionSequenceIndex == 1 && objectEvent->initialCoords.y == objectEvent->currentCoords.y)
    {
        objectEvent->directionSequenceIndex = 2;
    }
    return MoveNextDirectionInSequence(objectEvent, sprite, directions);
}

movement_type_def(MovementType_WalkSequenceRightLeftUpDown, gMovementTypeFuncs_WalkSequenceRightLeftUpDown)

u8 MovementType_WalkSequenceRightLeftUpDown_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    u8 directions[sizeof(gRightLeftUpDownDirections)];
    memcpy(directions, gRightLeftUpDownDirections, sizeof(gRightLeftUpDownDirections));
    if (objectEvent->directionSequenceIndex == 1 && objectEvent->initialCoords.x == objectEvent->currentCoords.x)
    {
        objectEvent->directionSequenceIndex = 2;
    }
    return MoveNextDirectionInSequence(objectEvent, sprite, directions);
}

movement_type_def(MovementType_WalkSequenceDownRightLeftUp, gMovementTypeFuncs_WalkSequenceDownRightLeftUp)

u8 MovementType_WalkSequenceDownRightLeftUp_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    u8 directions[sizeof(gDownRightLeftUpDirections)];
    memcpy(directions, gDownRightLeftUpDirections, sizeof(gDownRightLeftUpDirections));
    if (objectEvent->directionSequenceIndex == 2 && objectEvent->initialCoords.x == objectEvent->currentCoords.x)
    {
        objectEvent->directionSequenceIndex = 3;
    }
    return MoveNextDirectionInSequence(objectEvent, sprite, directions);
}

movement_type_def(MovementType_WalkSequenceRightUpDownLeft, gMovementTypeFuncs_WalkSequenceRightUpDownLeft)

u8 MovementType_WalkSequenceRightUpDownLeft_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    u8 directions[sizeof(gRightUpDownLeftDirections)];
    memcpy(directions, gRightUpDownLeftDirections, sizeof(gRightUpDownLeftDirections));
    if (objectEvent->directionSequenceIndex == 2 && objectEvent->initialCoords.y == objectEvent->currentCoords.y)
    {
        objectEvent->directionSequenceIndex = 3;
    }
    return MoveNextDirectionInSequence(objectEvent, sprite, directions);
}

movement_type_def(MovementType_WalkSequenceUpDownLeftRight, gMovementTypeFuncs_WalkSequenceUpDownLeftRight)

u8 MovementType_WalkSequenceUpDownLeftRight_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    u8 directions[sizeof(gUpDownLeftRightDirections)];
    memcpy(directions, gUpDownLeftRightDirections, sizeof(gUpDownLeftRightDirections));
    if (objectEvent->directionSequenceIndex == 1 && objectEvent->initialCoords.y == objectEvent->currentCoords.y)
    {
        objectEvent->directionSequenceIndex = 2;
    }
    return MoveNextDirectionInSequence(objectEvent, sprite, directions);
}

movement_type_def(MovementType_WalkSequenceLeftRightUpDown, gMovementTypeFuncs_WalkSequenceLeftRightUpDown)

u8 MovementType_WalkSequenceLeftRightUpDown_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    u8 directions[sizeof(gLeftRightUpDownDirections)];
    memcpy(directions, gLeftRightUpDownDirections, sizeof(gLeftRightUpDownDirections));
    if (objectEvent->directionSequenceIndex == 1 && objectEvent->initialCoords.x == objectEvent->currentCoords.x)
    {
        objectEvent->directionSequenceIndex = 2;
    }
    return MoveNextDirectionInSequence(objectEvent, sprite, directions);
}

movement_type_def(MovementType_WalkSequenceDownLeftRightUp, gMovementTypeFuncs_WalkSequenceDownLeftRightUp)

u8 MovementType_WalkSequenceDownLeftRightUp_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    u8 directions[sizeof(gDownLeftRightUpDirections)];
    memcpy(directions, gDownLeftRightUpDirections, sizeof(gDownLeftRightUpDirections));
    if (objectEvent->directionSequenceIndex == 2 && objectEvent->initialCoords.x == objectEvent->currentCoords.x)
    {
        objectEvent->directionSequenceIndex = 3;
    }
    return MoveNextDirectionInSequence(objectEvent, sprite, directions);
}

movement_type_def(MovementType_WalkSequenceUpLeftDownRight, gMovementTypeFuncs_WalkSequenceUpLeftDownRight)

u8 MovementType_WalkSequenceUpLeftDownRight_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    u8 directions[sizeof(gUpLeftDownRightDirections)];
    memcpy(directions, gUpLeftDownRightDirections, sizeof(gUpLeftDownRightDirections));
    if (objectEvent->directionSequenceIndex == 2 && objectEvent->initialCoords.y == objectEvent->currentCoords.y)
    {
        objectEvent->directionSequenceIndex = 3;
    }
    return MoveNextDirectionInSequence(objectEvent, sprite, directions);
}

movement_type_def(MovementType_WalkSequenceDownRightUpLeft, gMovementTypeFuncs_WalkSequenceDownRightUpLeft)

u8 MovementType_WalkSequenceDownRightUpLeft_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    u8 directions[sizeof(gDownRightUpLeftDirections)];
    memcpy(directions, gDownRightUpLeftDirections, sizeof(gDownRightUpLeftDirections));
    if (objectEvent->directionSequenceIndex == 2 && objectEvent->initialCoords.y == objectEvent->currentCoords.y)
    {
        objectEvent->directionSequenceIndex = 3;
    }
    return MoveNextDirectionInSequence(objectEvent, sprite, directions);
}

movement_type_def(MovementType_WalkSequenceLeftDownRightUp, gMovementTypeFuncs_WalkSequenceLeftDownRightUp)

u8 MovementType_WalkSequenceLeftDownRightUp_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    u8 directions[sizeof(gLeftDownRightUpDirections)];
    memcpy(directions, gLeftDownRightUpDirections, sizeof(gLeftDownRightUpDirections));
    if (objectEvent->directionSequenceIndex == 2 && objectEvent->initialCoords.x == objectEvent->currentCoords.x)
    {
        objectEvent->directionSequenceIndex = 3;
    }
    return MoveNextDirectionInSequence(objectEvent, sprite, directions);
}

movement_type_def(MovementType_WalkSequenceRightUpLeftDown, gMovementTypeFuncs_WalkSequenceRightUpLeftDown)

u8 MovementType_WalkSequenceRightUpLeftDown_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    u8 directions[sizeof(gRightUpLeftDownDirections)];
    memcpy(directions, gRightUpLeftDownDirections, sizeof(gRightUpLeftDownDirections));
    if (objectEvent->directionSequenceIndex == 2 && objectEvent->initialCoords.x == objectEvent->currentCoords.x)
    {
        objectEvent->directionSequenceIndex = 3;
    }
    return MoveNextDirectionInSequence(objectEvent, sprite, directions);
}

movement_type_def(MovementType_WalkSequenceUpRightDownLeft, gMovementTypeFuncs_WalkSequenceUpRightDownLeft)

u8 MovementType_WalkSequenceUpRightDownLeft_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    u8 directions[sizeof(gUpRightDownLeftDirections)];
    memcpy(directions, gUpRightDownLeftDirections, sizeof(gUpRightDownLeftDirections));
    if (objectEvent->directionSequenceIndex == 2 && objectEvent->initialCoords.y == objectEvent->currentCoords.y)
    {
        objectEvent->directionSequenceIndex = 3;
    }
    return MoveNextDirectionInSequence(objectEvent, sprite, directions);
}

movement_type_def(MovementType_WalkSequenceDownLeftUpRight, gMovementTypeFuncs_WalkSequenceDownLeftUpRight)

u8 MovementType_WalkSequenceDownLeftUpRight_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    u8 directions[sizeof(gDownLeftUpRightDirections)];
    memcpy(directions, gDownLeftUpRightDirections, sizeof(gDownLeftUpRightDirections));
    if (objectEvent->directionSequenceIndex == 2 && objectEvent->initialCoords.y == objectEvent->currentCoords.y)
    {
        objectEvent->directionSequenceIndex = 3;
    }
    return MoveNextDirectionInSequence(objectEvent, sprite, directions);
}

movement_type_def(MovementType_WalkSequenceLeftUpRightDown, gMovementTypeFuncs_WalkSequenceLeftUpRightDown)

u8 MovementType_WalkSequenceLeftUpRightDown_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    u8 directions[sizeof(gLeftUpRightDownDirections)];
    memcpy(directions, gLeftUpRightDownDirections, sizeof(gLeftUpRightDownDirections));
    if (objectEvent->directionSequenceIndex == 2 && objectEvent->initialCoords.x == objectEvent->currentCoords.x)
    {
        objectEvent->directionSequenceIndex = 3;
    }
    return MoveNextDirectionInSequence(objectEvent, sprite, directions);
}

movement_type_def(MovementType_WalkSequenceRightDownLeftUp, gMovementTypeFuncs_WalkSequenceRightDownLeftUp)

u8 MovementType_WalkSequenceRightDownLeftUp_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    u8 directions[sizeof(gRightDownLeftUpDirections)];
    memcpy(directions, gRightDownLeftUpDirections, sizeof(gRightDownLeftUpDirections));
    if (objectEvent->directionSequenceIndex == 2 && objectEvent->initialCoords.x == objectEvent->currentCoords.x)
    {
        objectEvent->directionSequenceIndex = 3;
    }
    return MoveNextDirectionInSequence(objectEvent, sprite, directions);
}

movement_type_def(MovementType_CopyPlayer, gMovementTypeFuncs_CopyPlayer)

static bool8 MovementType_CopyPlayer_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    ClearObjectEventMovement(objectEvent, sprite);
    if (objectEvent->directionSequenceIndex == 0)
    {
        objectEvent->directionSequenceIndex = GetPlayerFacingDirection();
    }
    sprite->data[1] = 1;
    return TRUE;
}

static bool8 MovementType_CopyPlayer_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (gObjectEvents[gPlayerAvatar.objectEventId].movementActionId == MOVEMENT_ACTION_NONE || gPlayerAvatar.tileTransitionState == T_TILE_CENTER)
    {
        return FALSE;
    }
    return gCopyPlayerMovementFuncs[PlayerGetCopyableMovement()](objectEvent, sprite, GetPlayerMovementDirection(), NULL);
}

static bool8 MovementType_CopyPlayer_Step2(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (ObjectEventExecSingleMovementAction(objectEvent, sprite))
    {
        objectEvent->singleMovementActive = FALSE;
        sprite->data[1] = 1;
    }
    return FALSE;
}

static bool8 CopyablePlayerMovement_None(struct ObjectEvent *objectEvent, struct Sprite *sprite, u8 playerDirection, bool8 tileCallback(u8))
{
    return FALSE;
}

static bool8 CopyablePlayerMovement_FaceDirection(struct ObjectEvent *objectEvent, struct Sprite *sprite, u8 playerDirection, bool8 tileCallback(u8))
{
    ObjectEventSetSingleMovement(objectEvent, sprite, GetFaceDirectionMovementAction(GetCopyDirection(gInitialMovementTypeFacingDirections[objectEvent->movementType], objectEvent->directionSequenceIndex, playerDirection)));
    objectEvent->singleMovementActive = TRUE;
    sprite->data[1] = 2;
    return TRUE;
}

static bool8 CopyablePlayerMovement_GoSpeed0(struct ObjectEvent *objectEvent, struct Sprite *sprite, u8 playerDirection, bool8 tileCallback(u8))
{
    u32 direction;
    s16 x;
    s16 y;

    direction = playerDirection;
    direction = GetCopyDirection(gInitialMovementTypeFacingDirections[objectEvent->movementType], objectEvent->directionSequenceIndex, direction);
    ObjectEventMoveDestCoords(objectEvent, direction, &x, &y);
    ObjectEventSetSingleMovement(objectEvent, sprite, GetWalkNormalMovementAction(direction));
    if (GetCollisionAtCoords(objectEvent, x, y, direction) || (tileCallback != NULL && !tileCallback(MapGridGetMetatileBehaviorAt(x, y))))
    {
        ObjectEventSetSingleMovement(objectEvent, sprite, GetFaceDirectionMovementAction(direction));
    }
    objectEvent->singleMovementActive = TRUE;
    sprite->data[1] = 2;
    return TRUE;
}

static bool8 CopyablePlayerMovement_GoSpeed1(struct ObjectEvent *objectEvent, struct Sprite *sprite, u8 playerDirection, bool8 tileCallback(u8))
{
    u32 direction;
    s16 x;
    s16 y;

    direction = playerDirection;
    direction = GetCopyDirection(gInitialMovementTypeFacingDirections[objectEvent->movementType], objectEvent->directionSequenceIndex, direction);
    ObjectEventMoveDestCoords(objectEvent, direction, &x, &y);
    ObjectEventSetSingleMovement(objectEvent, sprite, GetWalkFastMovementAction(direction));
    if (GetCollisionAtCoords(objectEvent, x, y, direction) || (tileCallback != NULL && !tileCallback(MapGridGetMetatileBehaviorAt(x, y))))
    {
        ObjectEventSetSingleMovement(objectEvent, sprite, GetFaceDirectionMovementAction(direction));
    }
    objectEvent->singleMovementActive = TRUE;
    sprite->data[1] = 2;
    return TRUE;
}

static bool8 CopyablePlayerMovement_GoSpeed2(struct ObjectEvent *objectEvent, struct Sprite *sprite, u8 playerDirection, bool8 tileCallback(u8))
{
    u32 direction;
    s16 x;
    s16 y;

    direction = playerDirection;
    direction = GetCopyDirection(gInitialMovementTypeFacingDirections[objectEvent->movementType], objectEvent->directionSequenceIndex, direction);
    ObjectEventMoveDestCoords(objectEvent, direction, &x, &y);
    ObjectEventSetSingleMovement(objectEvent, sprite, GetWalkFasterMovementAction(direction));
    if (GetCollisionAtCoords(objectEvent, x, y, direction) || (tileCallback != NULL && !tileCallback(MapGridGetMetatileBehaviorAt(x, y))))
    {
        ObjectEventSetSingleMovement(objectEvent, sprite, GetFaceDirectionMovementAction(direction));
    }
    objectEvent->singleMovementActive = TRUE;
    sprite->data[1] = 2;
    return TRUE;
}

static bool8 CopyablePlayerMovement_Slide(struct ObjectEvent *objectEvent, struct Sprite *sprite, u8 playerDirection, bool8 tileCallback(u8))
{
    u32 direction;
    s16 x;
    s16 y;

    direction = playerDirection;
    direction = GetCopyDirection(gInitialMovementTypeFacingDirections[objectEvent->movementType], objectEvent->directionSequenceIndex, direction);
    ObjectEventMoveDestCoords(objectEvent, direction, &x, &y);
    ObjectEventSetSingleMovement(objectEvent, sprite, GetSlideMovementAction(direction));
    if (GetCollisionAtCoords(objectEvent, x, y, direction) || (tileCallback != NULL && !tileCallback(MapGridGetMetatileBehaviorAt(x, y))))
    {
        ObjectEventSetSingleMovement(objectEvent, sprite, GetFaceDirectionMovementAction(direction));
    }
    objectEvent->singleMovementActive = TRUE;
    sprite->data[1] = 2;
    return TRUE;
}

static bool8 cph_IM_DIFFERENT(struct ObjectEvent *objectEvent, struct Sprite *sprite, u8 playerDirection, bool8 tileCallback(u8))
{
    u32 direction;

    direction = playerDirection;
    direction = GetCopyDirection(gInitialMovementTypeFacingDirections[objectEvent->movementType], objectEvent->directionSequenceIndex, direction);
    ObjectEventSetSingleMovement(objectEvent, sprite, GetJumpInPlaceMovementAction(direction));
    objectEvent->singleMovementActive = TRUE;
    sprite->data[1] = 2;
    return TRUE;
}

static bool8 CopyablePlayerMovement_GoSpeed4(struct ObjectEvent *objectEvent, struct Sprite *sprite, u8 playerDirection, bool8 tileCallback(u8))
{
    u32 direction;
    s16 x;
    s16 y;

    direction = playerDirection;
    direction = GetCopyDirection(gInitialMovementTypeFacingDirections[objectEvent->movementType], objectEvent->directionSequenceIndex, direction);
    ObjectEventMoveDestCoords(objectEvent, direction, &x, &y);
    ObjectEventSetSingleMovement(objectEvent, sprite, GetJumpMovementAction(direction));
    if (GetCollisionAtCoords(objectEvent, x, y, direction) || (tileCallback != NULL && !tileCallback(MapGridGetMetatileBehaviorAt(x, y))))
    {
        ObjectEventSetSingleMovement(objectEvent, sprite, GetFaceDirectionMovementAction(direction));
    }
    objectEvent->singleMovementActive = TRUE;
    sprite->data[1] = 2;
    return TRUE;
}

static bool8 CopyablePlayerMovement_Jump(struct ObjectEvent *objectEvent, struct Sprite *sprite, u8 playerDirection, bool8 tileCallback(u8))
{
    u32 direction;
    s16 x;
    s16 y;

    direction = playerDirection;
    direction = GetCopyDirection(gInitialMovementTypeFacingDirections[objectEvent->movementType], objectEvent->directionSequenceIndex, direction);
    x = objectEvent->currentCoords.x;
    y = objectEvent->currentCoords.y;
    MoveCoordsInDirection(direction, &x, &y, 2, 2);
    ObjectEventSetSingleMovement(objectEvent, sprite, GetJump2MovementAction(direction));
    if (GetCollisionAtCoords(objectEvent, x, y, direction) || (tileCallback != NULL && !tileCallback(MapGridGetMetatileBehaviorAt(x, y))))
    {
        ObjectEventSetSingleMovement(objectEvent, sprite, GetFaceDirectionMovementAction(direction));
    }
    objectEvent->singleMovementActive = TRUE;
    sprite->data[1] = 2;
    return TRUE;
}

movement_type_def(MovementType_CopyPlayerInGrass, gMovementTypeFuncs_CopyPlayerInGrass)

static bool8 MovementType_CopyPlayerInGrass_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (gObjectEvents[gPlayerAvatar.objectEventId].movementActionId == MOVEMENT_ACTION_NONE || gPlayerAvatar.tileTransitionState == T_TILE_CENTER)
    {
        return FALSE;
    }
    return gCopyPlayerMovementFuncs[PlayerGetCopyableMovement()](objectEvent, sprite, GetPlayerMovementDirection(), MetatileBehavior_IsPokeGrass);
}

static void MovementType_TreeDisguise(struct Sprite *sprite)
{
    struct ObjectEvent *objectEvent;

    objectEvent = &gObjectEvents[sprite->data[0]];
    if (objectEvent->directionSequenceIndex == 0 || (objectEvent->directionSequenceIndex == 1 && !sprite->data[7]))
    {
        ObjectEventGetLocalIdAndMap(objectEvent, &gFieldEffectArguments[0], &gFieldEffectArguments[1], &gFieldEffectArguments[2]);
        objectEvent->fieldEffectSpriteId = FieldEffectStart(FLDEFF_TREE_DISGUISE);
        objectEvent->directionSequenceIndex = 1;
        sprite->data[7]++;
    }
    UpdateObjectEventCurrentMovement(&gObjectEvents[sprite->data[0]], sprite, MovementType_Disguise_Callback);
}

static bool8 MovementType_Disguise_Callback(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    ClearObjectEventMovement(objectEvent, sprite);
    return FALSE;
}

static void MovementType_MountainDisguise(struct Sprite *sprite)
{
    struct ObjectEvent *objectEvent;

    objectEvent = &gObjectEvents[sprite->data[0]];
    if (objectEvent->directionSequenceIndex == 0 || (objectEvent->directionSequenceIndex == 1 && !sprite->data[7]))
    {
        ObjectEventGetLocalIdAndMap(objectEvent, &gFieldEffectArguments[0], &gFieldEffectArguments[1], &gFieldEffectArguments[2]);
        objectEvent->fieldEffectSpriteId = FieldEffectStart(FLDEFF_MOUNTAIN_DISGUISE);
        objectEvent->directionSequenceIndex = 1;
        sprite->data[7]++;
    }
    UpdateObjectEventCurrentMovement(&gObjectEvents[sprite->data[0]], sprite, MovementType_Disguise_Callback);
}

static void MovementType_Buried(struct Sprite *sprite)
{
    if (!sprite->data[7])
    {
        gObjectEvents[sprite->data[0]].fixedPriority = TRUE;
        sprite->subspriteMode = SUBSPRITES_IGNORE_PRIORITY;
        sprite->oam.priority = 3;
        sprite->data[7]++;
    }
    UpdateObjectEventCurrentMovement(&gObjectEvents[sprite->data[0]], sprite, MovementType_Buried_Callback);
}

static bool8 MovementType_Buried_Callback(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    return gMovementTypeFuncs_Buried[sprite->data[1]](objectEvent, sprite);
}

static bool8 MovementType_Buried_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    ClearObjectEventMovement(objectEvent, sprite);
    return FALSE;
}

static bool8 MovementType_MoveInPlace_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (ObjectEventExecSingleMovementAction(objectEvent, sprite))
    {
        sprite->data[1] = 0;
    }
    return FALSE;
}

movement_type_def(MovementType_WalkInPlace, gMovementTypeFuncs_WalkInPlace)

static bool8 MovementType_WalkInPlace_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    ClearObjectEventMovement(objectEvent, sprite);
    ObjectEventSetSingleMovement(objectEvent, sprite, GetWalkInPlaceNormalMovementAction(objectEvent->facingDirection));
    sprite->data[1] = 1;
    return TRUE;
}

movement_type_def(MovementType_WalkInPlaceFast, gMovementTypeFuncs_WalkInPlaceFast)

static bool8 MovementType_WalkInPlaceFast_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    ClearObjectEventMovement(objectEvent, sprite);
    ObjectEventSetSingleMovement(objectEvent, sprite, GetWalkInPlaceFastMovementAction(objectEvent->facingDirection));
    sprite->data[1] = 1;
    return TRUE;
}

movement_type_def(MovementType_JogInPlace, gMovementTypeFuncs_JogInPlace)

static bool8 MovementType_JogInPlace_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    ClearObjectEventMovement(objectEvent, sprite);
    ObjectEventSetSingleMovement(objectEvent, sprite, GetWalkInPlaceFasterMovementAction(objectEvent->facingDirection));
    sprite->data[1] = 1;
    return TRUE;
}

movement_type_def(MovementType_Invisible, gMovementTypeFuncs_Invisible)

static bool8 MovementType_Invisible_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    ClearObjectEventMovement(objectEvent, sprite);
    ObjectEventSetSingleMovement(objectEvent, sprite, GetFaceDirectionMovementAction(objectEvent->facingDirection));
    objectEvent->invisible = TRUE;
    sprite->data[1] = 1;
    return TRUE;
}

static bool8 MovementType_Invisible_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (ObjectEventExecSingleMovementAction(objectEvent, sprite))
    {
        sprite->data[1] = 2;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementType_Invisible_Step2(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    objectEvent->singleMovementActive = FALSE;
    return FALSE;
}

void MovementType_RaiseHandAndStop(struct Sprite *sprite)
{
    UpdateObjectEventCurrentMovement(&gObjectEvents[sprite->data[0]], sprite, MovementType_RaiseHandAndStop_Callback);
}

void MovementType_RaiseHandAndJump(struct Sprite *sprite)
{
    UpdateObjectEventCurrentMovement(&gObjectEvents[sprite->data[0]], sprite, MovementType_RaiseHandAndJump_Callback);
}

void MovementType_RaiseHandAndSwim(struct Sprite *sprite)
{
    UpdateObjectEventCurrentMovement(&gObjectEvents[sprite->data[0]], sprite, MovementType_RaiseHandAndSwim_Callback);
}

static u8 MovementType_RaiseHandAndStop_Callback(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    return gMovementTypeFuncs_RaiseHandAndStop[sprite->data[1]](objectEvent, sprite);
}

static u8 MovementType_RaiseHandAndJump_Callback(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    return gMovementTypeFuncs_RaiseHandAndJump[sprite->data[1]](objectEvent, sprite);
}

static u8 MovementType_RaiseHandAndSwim_Callback(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    return gMovementTypeFuncs_RaiseHandAndSwim[sprite->data[1]](objectEvent, sprite);
}

static bool8 MovementType_RaiseHandAndStop_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    ClearObjectEventMovement(objectEvent, sprite);
    ObjectEventSetSingleMovement(objectEvent, sprite, MOVEMENT_ACTION_RAISE_HAND_AND_STOP);
    sprite->data[1] = 1;
    return TRUE;
}

static bool8 MovementType_RaiseHandAndStop_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (ObjectEventExecSingleMovementAction(objectEvent, sprite))
    {
        sprite->data[1] = 2;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementType_RaiseHandAndStop_Step2(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    objectEvent->singleMovementActive = FALSE;
    return FALSE;
}

static bool8 MovementType_RaiseHandAndJump_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    ClearObjectEventMovement(objectEvent, sprite);
    ObjectEventSetSingleMovement(objectEvent, sprite, MOVEMENT_ACTION_RAISE_HAND_AND_JUMP);
    sprite->data[1] = 1;
    return FALSE;
}

static bool8 MovementType_RaiseHandAndSwim_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    ClearObjectEventMovement(objectEvent, sprite);
    ObjectEventSetSingleMovement(objectEvent, sprite, MOVEMENT_ACTION_RAISE_HAND_AND_SWIM);
    sprite->data[1] = 1;
    return FALSE;
}

static bool8 MovementType_RaiseHandAndMove_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (ObjectEventExecSingleMovementAction(objectEvent, sprite))
    {
        sprite->data[1] = 0;
    }
    return FALSE;
}

static void ClearObjectEventMovement(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    objectEvent->singleMovementActive = FALSE;
    objectEvent->heldMovementActive = FALSE;
    objectEvent->heldMovementFinished = FALSE;
    objectEvent->movementActionId = MOVEMENT_ACTION_NONE;
    sprite->data[1] = 0;
}

u8 GetFaceDirectionAnimNum(u8 direction)
{
    return sFaceDirectionAnimNums[direction];
}

u8 GetMoveDirectionAnimNum(u8 direction)
{
    return sMoveDirectionAnimNums[direction];
}

static u8 GetMoveDirectionFastAnimNum(u8 direction)
{
    return sMoveDirectionFastAnimNums[direction];
}

static u8 GetMoveDirectionFasterAnimNum(u8 direction)
{
    return sMoveDirectionFasterAnimNums[direction];
}

static u8 GetMoveDirectionFastestAnimNum(u8 direction)
{
    return sMoveDirectionFastestAnimNums[direction];
}

u8 GetJumpSpecialDirectionAnimNum(u8 direction)
{
    return sJumpSpecialDirectionAnimNums[direction];
}

u8 GetAcroWheelieDirectionAnimNum(u8 direction)
{
    return sAcroBunnyHopBackWheelDirectionAnimNums[direction];
}

u8 GetAcroBunnyHopFrontWheelDirectionAnimNum(u8 direction)
{
    return sAcroBunnyHopFrontWheelDirectionAnimNums[direction];
}

u8 GetAcroEndWheelieDirectionAnimNum(u8 direction)
{
    return sAcroStandingWheelieBackWheelDirectionAnimNums[direction];
}

u8 GetSpinDirectionAnimNum(u8 direction)
{
    return sSpinDirectionAnimNums[direction];
}

u8 GetAcroUnusedActionDirectionAnimNum(u8 direction)
{
    return sAcroStandingWheelieFrontWheelDirectionAnimNums[direction];
}

u8 GetAcroWheeliePedalDirectionAnimNum(u8 direction)
{
    return sAcroMovingWheelieDirectionAnimNums[direction];
}

u8 GetFishingDirectionAnimNum(u8 direction)
{
    return sFishingDirectionAnimNums[direction];
}

u8 GetFishingNoCatchDirectionAnimNum(u8 direction)
{
    return sFishingNoCatchDirectionAnimNums[direction];
}

u8 GetFishingBiteDirectionAnimNum(u8 direction)
{
    return sFishingBiteDirectionAnimNums[direction];
}

u8 GetRunningDirectionAnimNum(u8 direction)
{
    return sRunningDirectionAnimNums[direction];
}

static const struct StepAnimTable *GetStepAnimTable(const union AnimCmd *const *anims)
{
    const struct StepAnimTable *stepTable;

    for (stepTable = sStepAnimTables; stepTable->anims != NULL; stepTable++)
        if (stepTable->anims == anims)
            return stepTable;

    return NULL;
}

void SetStepAnimHandleAlternation(struct ObjectEvent *objectEvent, struct Sprite *sprite, u8 animNum)
{
    const struct StepAnimTable *stepTable;

    if (!objectEvent->inanimate)
    {
        sprite->animNum = animNum;
        stepTable = GetStepAnimTable(sprite->anims);
        if (stepTable != NULL)
        {
            if (sprite->animCmdIndex == stepTable->animPos[0])
                sprite->animCmdIndex = stepTable->animPos[3];
            else if (sprite->animCmdIndex == stepTable->animPos[1])
                sprite->animCmdIndex = stepTable->animPos[2];
        }
        SeekSpriteAnim(sprite, sprite->animCmdIndex);
    }
}

void SetStepAnim(struct ObjectEvent *objectEvent, struct Sprite *sprite, u8 animNum)
{
    const struct StepAnimTable *stepTable;

    if (!objectEvent->inanimate)
    {
        u8 animPos;

        sprite->animNum = animNum;
        stepTable = GetStepAnimTable(sprite->anims);
        if (stepTable != NULL)
        {
            animPos = stepTable->animPos[1];
            if (sprite->animCmdIndex <= stepTable->animPos[0])
                animPos = stepTable->animPos[0];

            SeekSpriteAnim(sprite, animPos);
        }
    }
}

// file boundary?

u8 GetDirectionToFace(s16 x1, s16 y1, s16 x2, s16 y2)
{
    if (x1 > x2)
    {
        return DIR_WEST;
    }
    if (x1 < x2)
    {
        return DIR_EAST;
    }
    if (y1 > y2)
    {
        return DIR_NORTH;
    }
    return DIR_SOUTH;
}

void SetTrainerMovementType(struct ObjectEvent *objectEvent, u8 movementType)
{
    objectEvent->movementType = movementType;
    objectEvent->directionSequenceIndex = 0;
    objectEvent->playerCopyableMovement = 0;
    gSprites[objectEvent->spriteId].callback = sMovementTypeCallbacks[movementType];
    gSprites[objectEvent->spriteId].data[1] = 0;
}

u8 GetTrainerFacingDirectionMovementType(u8 direction)
{
    return sTrainerFacingDirectionMovementTypes[direction];
}

static u8 GetCollisionInDirection(struct ObjectEvent *objectEvent, u8 direction)
{
    s16 x;
    s16 y;
    x = objectEvent->currentCoords.x;
    y = objectEvent->currentCoords.y;
    MoveCoords(direction, &x, &y);
    return GetCollisionAtCoords(objectEvent, x, y, direction);
}

u8 GetCollisionAtCoords(struct ObjectEvent *objectEvent, s16 x, s16 y, u32 dir)
{
    u8 direction = dir;
    if (IsCoordOutsideObjectEventMovementRange(objectEvent, x, y))
        return COLLISION_OUTSIDE_RANGE;
    else if (MapGridGetCollisionAt(x, y) || GetMapBorderIdAt(x, y) == CONNECTION_INVALID || IsMetatileDirectionallyImpassable(objectEvent, x, y, direction))
        return COLLISION_IMPASSABLE;
    else if (objectEvent->trackedByCamera && !CanCameraMoveInDirection(direction))
        return COLLISION_IMPASSABLE;
    else if (IsElevationMismatchAt(objectEvent->currentElevation, x, y))
        return COLLISION_ELEVATION_MISMATCH;
    else if (DoesObjectCollideWithObjectAt(objectEvent, x, y))
        return COLLISION_OBJECT_EVENT;
    return COLLISION_NONE;
}

u8 GetCollisionFlagsAtCoords(struct ObjectEvent *objectEvent, s16 x, s16 y, u8 direction)
{
    u8 flags = 0;

    if (IsCoordOutsideObjectEventMovementRange(objectEvent, x, y))
        flags |= 1;
    if (MapGridGetCollisionAt(x, y) || GetMapBorderIdAt(x, y) == CONNECTION_INVALID || IsMetatileDirectionallyImpassable(objectEvent, x, y, direction) || (objectEvent->trackedByCamera && !CanCameraMoveInDirection(direction)))
        flags |= 2;
    if (IsElevationMismatchAt(objectEvent->currentElevation, x, y))
        flags |= 4;
    if (DoesObjectCollideWithObjectAt(objectEvent, x, y))
        flags |= 8;
    return flags;
}

static bool8 IsCoordOutsideObjectEventMovementRange(struct ObjectEvent *objectEvent, s16 x, s16 y)
{
    s16 left;
    s16 right;
    s16 top;
    s16 bottom;

    if (objectEvent->rangeX != 0)
    {
        left = objectEvent->initialCoords.x - objectEvent->rangeX;
        right = objectEvent->initialCoords.x + objectEvent->rangeX;
        if (left > x || right < x)
        {
            return TRUE;
        }
    }
    if (objectEvent->rangeY != 0)
    {
        top = objectEvent->initialCoords.y - objectEvent->rangeY;
        bottom = objectEvent->initialCoords.y + objectEvent->rangeY;
        if (top > y || bottom < y)
        {
            return TRUE;
        }
    }
    return FALSE;
}

static bool8 IsMetatileDirectionallyImpassable(struct ObjectEvent *objectEvent, s16 x, s16 y, u8 direction)
{
    if (gOppositeDirectionBlockedMetatileFuncs[direction - 1](objectEvent->currentMetatileBehavior)
        || gDirectionBlockedMetatileFuncs[direction - 1](MapGridGetMetatileBehaviorAt(x, y)))
    {
        return TRUE;
    }
    return FALSE;
}

static bool8 DoesObjectCollideWithObjectAt(struct ObjectEvent *objectEvent, s16 x, s16 y)
{
    u8 i;
    struct ObjectEvent *curObject;

    for (i = 0; i < OBJECT_EVENTS_COUNT; i++)
    {
        curObject = &gObjectEvents[i];
        if (curObject->active && curObject != objectEvent)
        {
            if ((curObject->currentCoords.x == x && curObject->currentCoords.y == y) || (curObject->previousCoords.x == x && curObject->previousCoords.y == y))
            {
                if (AreElevationsCompatible(objectEvent->currentElevation, curObject->currentElevation))
                    return TRUE;
            }
        }
    }
    return FALSE;
}

bool8 IsBerryTreeSparkling(u8 localId, u8 mapNum, u8 mapGroup)
{
    u8 objectEventId;

    if (!TryGetObjectEventIdByLocalIdAndMap(localId, mapNum, mapGroup, &objectEventId)
        && gSprites[gObjectEvents[objectEventId].spriteId].data[7] & 2)
    {
        return TRUE;
    }

    return FALSE;
}

static void SetBerryTreeJustPicked(u8 localId, u8 mapNum, u8 mapGroup)
{
    u8 objectEventId;

    if (!TryGetObjectEventIdByLocalIdAndMap(localId, mapNum, mapGroup, &objectEventId))
        gSprites[gObjectEvents[objectEventId].spriteId].data[7] |= 0x04;
}

void MoveCoords(u8 direction, s16 *x, s16 *y)
{
    *x += sDirectionToVectors[direction].x;
    *y += sDirectionToVectors[direction].y;
}

// Unused
static void MoveCoordsInMapCoordIncrement(u8 direction, s16 *x, s16 *y)
{
    *x += sDirectionToVectors[direction].x << 4;
    *y += sDirectionToVectors[direction].y << 4;
}

static void MoveCoordsInDirection(u32 dir, s16 *x, s16 *y, s16 deltaX, s16 deltaY)
{
    u8 direction = dir;
    s16 dx2 = (u16)deltaX;
    s16 dy2 = (u16)deltaY;
    if (sDirectionToVectors[direction].x > 0)
        *x += dx2;
    if (sDirectionToVectors[direction].x < 0)
        *x -= dx2;
    if (sDirectionToVectors[direction].y > 0)
        *y += dy2;
    if (sDirectionToVectors[direction].y < 0)
        *y -= dy2;
}

void GetMapCoordsFromSpritePos(s16 x, s16 y, s16 *destX, s16 *destY)
{
    *destX = (x - gSaveBlock1Ptr->pos.x) << 4;
    *destY = (y - gSaveBlock1Ptr->pos.y) << 4;
    *destX -= gTotalCameraPixelOffsetX;
    *destY -= gTotalCameraPixelOffsetY;
}

void SetSpritePosToMapCoords(s16 mapX, s16 mapY, s16 *destX, s16 *destY)
{
    s16 dx = -gTotalCameraPixelOffsetX - gFieldCamera.x;
    s16 dy = -gTotalCameraPixelOffsetY - gFieldCamera.y;
    if (gFieldCamera.x > 0)
        dx += 1 << 4;

    if (gFieldCamera.x < 0)
        dx -= 1 << 4;

    if (gFieldCamera.y > 0)
        dy += 1 << 4;

    if (gFieldCamera.y < 0)
        dy -= 1 << 4;

    *destX = ((mapX - gSaveBlock1Ptr->pos.x) << 4) + dx;
    *destY = ((mapY - gSaveBlock1Ptr->pos.y) << 4) + dy;
}

void SetSpritePosToOffsetMapCoords(s16 *x, s16 *y, s16 dx, s16 dy)
{
    SetSpritePosToMapCoords(*x, *y, x, y);
    *x += dx;
    *y += dy;
}

static void GetObjectEventMovingCameraOffset(s16 *x, s16 *y)
{
    *x = 0;
    *y = 0;
    if (gFieldCamera.x > 0)
    {
        (*x)++;
    }
    if (gFieldCamera.x < 0)
    {
        (*x)--;
    }
    if (gFieldCamera.y > 0)
    {
        (*y)++;
    }
    if (gFieldCamera.y < 0)
    {
        (*y)--;
    }
}

void ObjectEventMoveDestCoords(struct ObjectEvent *objectEvent, u32 direction, s16 *x, s16 *y)
{
    u8 newDirn = direction;
    *x = objectEvent->currentCoords.x;
    *y = objectEvent->currentCoords.y;
    MoveCoords(newDirn, x, y);
}

bool8 ObjectEventIsMovementOverridden(struct ObjectEvent *objectEvent)
{
    if (objectEvent->singleMovementActive || objectEvent->heldMovementActive)
        return TRUE;

    return FALSE;
}

bool8 ObjectEventIsHeldMovementActive(struct ObjectEvent *objectEvent)
{
    if (objectEvent->heldMovementActive && objectEvent->movementActionId != MOVEMENT_ACTION_NONE)
        return TRUE;

    return FALSE;
}

bool8 ObjectEventSetHeldMovement(struct ObjectEvent *objectEvent, u8 movementActionId)
{
    if (QL_GetPlaybackState() == QL_PLAYBACK_STATE_RUNNING)
        ObjectEventClearHeldMovementIfActive(objectEvent);
    else if (ObjectEventIsMovementOverridden(objectEvent))
        return TRUE;

    UnfreezeObjectEvent(objectEvent);
    objectEvent->movementActionId = movementActionId;
    objectEvent->heldMovementActive = TRUE;
    objectEvent->heldMovementFinished = FALSE;
    gSprites[objectEvent->spriteId].data[2] = 0;
    return FALSE;
}

void ObjectEventForceSetHeldMovement(struct ObjectEvent *objectEvent, u8 movementActionId)
{
    ObjectEventClearHeldMovementIfActive(objectEvent);
    ObjectEventSetHeldMovement(objectEvent, movementActionId);
}

void ObjectEventClearHeldMovementIfActive(struct ObjectEvent *objectEvent)
{
    if (objectEvent->heldMovementActive)
        ObjectEventClearHeldMovement(objectEvent);
}

void ObjectEventClearHeldMovement(struct ObjectEvent *objectEvent)
{
    objectEvent->movementActionId = MOVEMENT_ACTION_NONE;
    objectEvent->heldMovementActive = FALSE;
    objectEvent->heldMovementFinished = FALSE;
    gSprites[objectEvent->spriteId].data[1] = 0;
    gSprites[objectEvent->spriteId].data[2] = 0;
}

u8 ObjectEventCheckHeldMovementStatus(struct ObjectEvent *objectEvent)
{
    if (objectEvent->heldMovementActive)
        return objectEvent->heldMovementFinished;

    return 16;
}

u8 ObjectEventClearHeldMovementIfFinished(struct ObjectEvent *objectEvent)
{
    u8 heldMovementStatus = ObjectEventCheckHeldMovementStatus(objectEvent);
    if (heldMovementStatus != 0 && heldMovementStatus != 16)
        ObjectEventClearHeldMovementIfActive(objectEvent);

    return heldMovementStatus;
}

u8 ObjectEventGetHeldMovementActionId(struct ObjectEvent *objectEvent)
{
    if (objectEvent->heldMovementActive)
        return objectEvent->movementActionId;

    return MOVEMENT_ACTION_NONE;
}

void UpdateObjectEventCurrentMovement(struct ObjectEvent *objectEvent, struct Sprite *sprite, bool8 (*callback)(struct ObjectEvent *, struct Sprite *))
{
    DoGroundEffects_OnSpawn(objectEvent, sprite);
    TryEnableObjectEventAnim(objectEvent, sprite);

    if (ObjectEventIsHeldMovementActive(objectEvent))
        ObjectEventExecHeldMovementAction(objectEvent, sprite);
    else if (!objectEvent->frozen)
        while (callback(objectEvent, sprite));

    DoGroundEffects_OnBeginStep(objectEvent, sprite);
    DoGroundEffects_OnFinishStep(objectEvent, sprite);
    UpdateObjectEventSpriteAnimPause(objectEvent, sprite);
    UpdateObjectEventVisibility(objectEvent, sprite);
    ObjectEventUpdateSubpriority(objectEvent, sprite);
}

void QL_UpdateObjectEventCurrentMovement(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    DoGroundEffects_OnSpawn(objectEvent, sprite);
    TryEnableObjectEventAnim(objectEvent, sprite);

    if (ObjectEventIsHeldMovementActive(objectEvent) && !sprite->animBeginning)
        QuestLogObjectEventExecHeldMovementAction(objectEvent, sprite);
    
    if (MetatileBehavior_IsIce_2(objectEvent->currentMetatileBehavior) == TRUE
        || MetatileBehavior_IsTrickHouseSlipperyFloor(objectEvent->currentMetatileBehavior) == TRUE)
        objectEvent->disableAnim = TRUE;
    else
        objectEvent->disableAnim = FALSE;

    DoGroundEffects_OnBeginStep(objectEvent, sprite);
    DoGroundEffects_OnFinishStep(objectEvent, sprite);
    UpdateObjectEventSpriteAnimPause(objectEvent, sprite);
    UpdateObjectEventVisibility(objectEvent, sprite);
    ObjectEventUpdateSubpriority(objectEvent, sprite);
}

#define dirn_to_anim(name, table)                   \
u8 name(u32 idx)                                    \
{                                                   \
    u8 direction;                                   \
    u8 animIds[sizeof(table)];                      \
    direction = idx;                                \
    memcpy(animIds, (table), sizeof(table));        \
    if (direction > DIR_EAST) direction = DIR_NONE; \
    return animIds[direction];                      \
}

dirn_to_anim(GetFaceDirectionMovementAction, sFaceDirectionMovementActions);
dirn_to_anim(GetFaceDirectionFastMovementAction, sFaceDirectionFastMovementActions);

u8 GetWalkSlowestMovementAction(u32 idx)
{
    u8 direction = idx;
    if (direction > DIR_EAST)
        direction = DIR_NONE;

    return sWalkSlowestMovementActions[direction];
}

dirn_to_anim(GetWalkSlowerMovementAction, sWalkSlowerMovementActions);
dirn_to_anim(GetWalkSlowMovementAction, sWalkSlowMovementActions);
dirn_to_anim(GetWalkNormalMovementAction, sWalkNormalMovementActions);
dirn_to_anim(GetWalkFastMovementAction, sWalkFastMovementActions);
dirn_to_anim(GetGlideMovementAction, sGlideMovementActions);
dirn_to_anim(GetRideWaterCurrentMovementAction, sRideWaterCurrentMovementActions);
dirn_to_anim(GetWalkFasterMovementAction, sWalkFasterMovementActions);
dirn_to_anim(GetSlideMovementAction, sSlideMovementActions);
dirn_to_anim(GetPlayerRunMovementAction, sPlayerRunMovementActions);
dirn_to_anim(GetPlayerRunSlowMovementAction, sPlayerRunSlowMovementActions);
dirn_to_anim(GetSpinMovementAction, sSpinMovementActions);
dirn_to_anim(GetJump2MovementAction, sJump2MovementActions);
dirn_to_anim(GetJumpInPlaceMovementAction, sJumpInPlaceMovementActions);
dirn_to_anim(GetJumpInPlaceTurnAroundMovementAction, sJumpInPlaceTurnAroundMovementActions);
dirn_to_anim(GetJumpMovementAction, sJumpMovementActions);
dirn_to_anim(GetJumpSpecialMovementAction, sJumpSpecialMovementActions);
dirn_to_anim(GetJumpSpecialWithEffectMovementAction, sJumpSpecialWithEffectMovementActions);
dirn_to_anim(GetWalkInPlaceSlowMovementAction, sWalkInPlaceSlowMovementActions);
dirn_to_anim(GetWalkInPlaceNormalMovementAction, sWalkInPlaceNormalMovementActions);
dirn_to_anim(GetWalkInPlaceFastMovementAction, sWalkInPlaceFastMovementActions);
dirn_to_anim(GetWalkInPlaceFasterMovementAction, sWalkInPlaceFasterMovementActions);

bool8 ObjectEventFaceOppositeDirection(struct ObjectEvent *objectEvent, u8 direction)
{
    return ObjectEventSetHeldMovement(objectEvent, GetFaceDirectionMovementAction(GetOppositeDirection(direction)));
}

dirn_to_anim(GetAcroWheelieFaceDirectionMovementAction, sAcroWheelieFaceDirectionMovementActions);
dirn_to_anim(GetAcroPopWheelieFaceDirectionMovementAction, sAcroPopWheelieFaceDirectionMovementActions);
dirn_to_anim(GetAcroEndWheelieFaceDirectionMovementAction, sAcroEndWheelieFaceDirectionMovementActions);
dirn_to_anim(GetAcroWheelieHopFaceDirectionMovementAction, sAcroWheelieHopFaceDirectionMovementActions);
dirn_to_anim(GetAcroWheelieHopMovementAction, sAcroWheelieHopMovementActions);
dirn_to_anim(GetAcroWheelieJumpMovementAction, sAcroWheelieJumpMovementActions);
dirn_to_anim(GetAcroWheelieInPlaceMovementAction, sAcroWheelieInPlaceMovementActions);
dirn_to_anim(GetAcroPopWheelieMoveMovementAction, sAcroPopWheelieMoveMovementActions);
dirn_to_anim(GetAcroWheelieMoveMovementAction, sAcroWheelieMoveMovementActions);

u8 GetOppositeDirection(u8 direction)
{
    u8 directions[sizeof gOppositeDirections];

    memcpy(directions, gOppositeDirections, sizeof gOppositeDirections);
    if (direction < 1 || direction > (sizeof gOppositeDirections))
    {
        return direction;
    }
    return directions[direction - 1];
}

static u32 GetPlayerDirectionForCopy(u8 initDir, u8 moveDir)
{
    return sPlayerDirectionsForCopy[initDir - 1][moveDir - 1];
}

static u32 GetCopyDirection(u8 copyInitDir, u32 playerInitDir, u32 playerMoveDir)
{
    u32 dir;
    u8 _playerInitDir = playerInitDir;
    u8 _playerMoveDir = playerMoveDir;
    if (_playerInitDir == DIR_NONE || _playerMoveDir == DIR_NONE
      || _playerInitDir > DIR_EAST || _playerMoveDir > DIR_EAST)
        return DIR_NONE;

    dir = GetPlayerDirectionForCopy(_playerInitDir, playerMoveDir);
    return sPlayerDirectionToCopyDirection[copyInitDir - 1][dir - 1];
}

static void ObjectEventExecHeldMovementAction(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (sMovementActionFuncs[objectEvent->movementActionId][sprite->data[2]](objectEvent, sprite))
    {
        objectEvent->heldMovementFinished = TRUE;
    }
}

static void QuestLogObjectEventExecHeldMovementAction(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (sMovementActionFuncs[objectEvent->movementActionId][sprite->data[2]](objectEvent, sprite))
    {
        objectEvent->heldMovementFinished = TRUE;
        if (objectEvent->graphicsId == OBJ_EVENT_GFX_PUSHABLE_BOULDER)
            HandleBoulderFallThroughHole(objectEvent);
    }
}

static bool8 ObjectEventExecSingleMovementAction(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (sMovementActionFuncs[objectEvent->movementActionId][sprite->data[2]](objectEvent, sprite))
    {
        objectEvent->movementActionId = MOVEMENT_ACTION_NONE;
        sprite->data[2] = 0;
        return TRUE;
    }
    return FALSE;
}

static void ObjectEventSetSingleMovement(struct ObjectEvent *objectEvent, struct Sprite *sprite, u8 movementActionId)
{
    objectEvent->movementActionId = movementActionId;
    sprite->data[2] = 0;
    
    if (gQuestLogPlaybackState == QL_PLAYBACK_STATE_RECORDING)
        QuestLogRecordNPCStep(objectEvent->localId, objectEvent->mapNum, objectEvent->mapGroup, movementActionId);
}

static void FaceDirection(struct ObjectEvent *objectEvent, struct Sprite *sprite, u8 direction)
{
    SetObjectEventDirection(objectEvent, direction);
    ShiftStillObjectEventCoords(objectEvent);
    SetStepAnim(objectEvent, sprite, GetMoveDirectionAnimNum(objectEvent->facingDirection));
    sprite->animPaused = TRUE;
    sprite->data[2] = 1;
}

static bool8 MovementAction_FaceDown_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    FaceDirection(objectEvent, sprite, DIR_SOUTH);
    return TRUE;
}

static bool8 MovementAction_FaceUp_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    FaceDirection(objectEvent, sprite, DIR_NORTH);
    return TRUE;
}

static bool8 MovementAction_FaceLeft_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    FaceDirection(objectEvent, sprite, DIR_WEST);
    return TRUE;
}

static bool8 MovementAction_FaceRight_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    FaceDirection(objectEvent, sprite, DIR_EAST);
    return TRUE;
}

void InitNpcForMovement(struct ObjectEvent *objectEvent, struct Sprite *sprite, u8 direction, u8 speed)
{
    s16 x;
    s16 y;

    x = objectEvent->currentCoords.x;
    y = objectEvent->currentCoords.y;
    SetObjectEventDirection(objectEvent, direction);
    MoveCoords(direction, &x, &y);
    ShiftObjectEventCoords(objectEvent, x, y);
    SetSpriteDataForNormalStep(sprite, direction, speed);
    sprite->animPaused = FALSE;
    objectEvent->triggerGroundEffectsOnMove = TRUE;
    sprite->data[2] = 1;
}

void InitMovementNormal(struct ObjectEvent *objectEvent, struct Sprite *sprite, u8 direction, u8 speed)
{
    u8 (*functions[NELEMS(sDirectionAnimFuncsBySpeed)])(u8);
    memcpy(functions, sDirectionAnimFuncsBySpeed, sizeof sDirectionAnimFuncsBySpeed);
    InitNpcForMovement(objectEvent, sprite, direction, speed);
    SetStepAnimHandleAlternation(objectEvent, sprite, functions[speed](objectEvent->facingDirection));
}

void StartRunningAnim(struct ObjectEvent *objectEvent, struct Sprite *sprite, u8 direction)
{
    InitNpcForMovement(objectEvent, sprite, direction, MOVE_SPEED_FAST_1);
    SetStepAnimHandleAlternation(objectEvent, sprite, GetRunningDirectionAnimNum(objectEvent->facingDirection));
}

bool8 UpdateMovementNormal(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (NpcTakeStep(sprite))
    {
        ShiftStillObjectEventCoords(objectEvent);
        objectEvent->triggerGroundEffectsOnStop = TRUE;
        sprite->animPaused = TRUE;
        return TRUE;
    }
    return FALSE;
}

void InitNpcForWalkSlower(struct ObjectEvent *objectEvent, struct Sprite *sprite, u8 direction)
{
    s16 x;
    s16 y;

    x = objectEvent->currentCoords.x;
    y = objectEvent->currentCoords.y;
    SetObjectEventDirection(objectEvent, direction);
    MoveCoords(direction, &x, &y);
    ShiftObjectEventCoords(objectEvent, x, y);
    SetWalkSlowerSpriteData(sprite, direction);
    sprite->animPaused = FALSE;
    objectEvent->triggerGroundEffectsOnMove = TRUE;
    sprite->data[2] = 1;
}

void InitWalkSlower(struct ObjectEvent *objectEvent, struct Sprite *sprite, u8 direction)
{
    InitNpcForWalkSlower(objectEvent, sprite, direction);
    SetStepAnimHandleAlternation(objectEvent, sprite, GetMoveDirectionAnimNum(objectEvent->facingDirection));
}

bool8 UpdateWalkSlower(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (UpdateWalkSlowerAnim(sprite))
    {
        ShiftStillObjectEventCoords(objectEvent);
        objectEvent->triggerGroundEffectsOnStop = TRUE;
        sprite->animPaused = TRUE;
        return TRUE;
    }
    return FALSE;
}

void InitNpcForWalkSlowest(struct ObjectEvent *objectEvent, struct Sprite *sprite, u8 direction)
{
    s16 x;
    s16 y;

    x = objectEvent->currentCoords.x;
    y = objectEvent->currentCoords.y;
    SetObjectEventDirection(objectEvent, direction);
    MoveCoords(direction, &x, &y);
    ShiftObjectEventCoords(objectEvent, x, y);
    SetWalkSlowestSpriteData(sprite, direction);
    sprite->animPaused = FALSE;
    objectEvent->triggerGroundEffectsOnMove = TRUE;
    sprite->data[2] = 1;
}

void InitWalkSlowest(struct ObjectEvent *objectEvent, struct Sprite *sprite, u8 direction)
{
    InitNpcForWalkSlowest(objectEvent, sprite, direction);
    SetStepAnimHandleAlternation(objectEvent, sprite, GetMoveDirectionAnimNum(objectEvent->facingDirection));
}

bool8 UpdateWalkSlowest(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (UpdateWalkSlowestAnim(sprite))
    {
        ShiftStillObjectEventCoords(objectEvent);
        objectEvent->triggerGroundEffectsOnStop = TRUE;
        sprite->animPaused = TRUE;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementAction_WalkSlowestDown_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitWalkSlowest(objectEvent, sprite, DIR_SOUTH);
    return MovementAction_WalkSlowestDown_Step1(objectEvent, sprite);
}

static bool8 MovementAction_WalkSlowestDown_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (UpdateWalkSlowest(objectEvent, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementAction_WalkSlowestUp_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitWalkSlowest(objectEvent, sprite, DIR_NORTH);
    return MovementAction_WalkSlowestUp_Step1(objectEvent, sprite);
}

static bool8 MovementAction_WalkSlowestUp_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (UpdateWalkSlowest(objectEvent, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementAction_WalkSlowestLeft_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitWalkSlowest(objectEvent, sprite, DIR_WEST);
    return MovementAction_WalkSlowestLeft_Step1(objectEvent, sprite);
}

static bool8 MovementAction_WalkSlowestLeft_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (UpdateWalkSlowest(objectEvent, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementAction_WalkSlowestRight_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitWalkSlowest(objectEvent, sprite, DIR_EAST);
    return MovementAction_WalkSlowestRight_Step1(objectEvent, sprite);
}

static bool8 MovementAction_WalkSlowestRight_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (UpdateWalkSlowest(objectEvent, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementAction_WalkSlowerDown_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitWalkSlower(objectEvent, sprite, DIR_SOUTH);
    return MovementAction_WalkSlowerDown_Step1(objectEvent, sprite);
}

static bool8 MovementAction_WalkSlowerDown_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (UpdateWalkSlower(objectEvent, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementAction_WalkSlowerUp_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitWalkSlower(objectEvent, sprite, DIR_NORTH);
    return MovementAction_WalkSlowerUp_Step1(objectEvent, sprite);
}

static bool8 MovementAction_WalkSlowerUp_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (UpdateWalkSlower(objectEvent, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementAction_WalkSlowerLeft_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitWalkSlower(objectEvent, sprite, DIR_WEST);
    return MovementAction_WalkSlowerLeft_Step1(objectEvent, sprite);
}

static bool8 MovementAction_WalkSlowerLeft_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (UpdateWalkSlower(objectEvent, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementAction_WalkSlowerRight_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitWalkSlower(objectEvent, sprite, DIR_EAST);
    return MovementAction_WalkSlowerRight_Step1(objectEvent, sprite);
}

static bool8 MovementAction_WalkSlowerRight_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (UpdateWalkSlower(objectEvent, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

// InitNpcForWalkSlow, InitNpcForWalkSlower, InitNpcForWalkSlowest, and
// InitNpcForRunSlow are functionally equivalent
void InitNpcForWalkSlow(struct ObjectEvent *objectEvent, struct Sprite *sprite, u8 direction)
{
    s16 x;
    s16 y;

    x = objectEvent->currentCoords.x;
    y = objectEvent->currentCoords.y;
    SetObjectEventDirection(objectEvent, direction);
    MoveCoords(direction, &x, &y);
    ShiftObjectEventCoords(objectEvent, x, y);
    SetWalkSlowSpriteData(sprite, direction);
    sprite->animPaused = FALSE;
    objectEvent->triggerGroundEffectsOnMove = TRUE;
    sprite->data[2] = 1;
}

// InitWalkSlow, InitWalkSlower, InitWalkSlowest, and InitRunSlow are
// functionally equivalent
void InitWalkSlow(struct ObjectEvent *objectEvent, struct Sprite *sprite, u8 direction)
{
    InitNpcForWalkSlow(objectEvent, sprite, direction);
    SetStepAnimHandleAlternation(objectEvent, sprite, GetMoveDirectionAnimNum(objectEvent->facingDirection));
}

bool8 UpdateWalkSlow(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (UpdateWalkSlowAnim(sprite))
    {
        ShiftStillObjectEventCoords(objectEvent);
        objectEvent->triggerGroundEffectsOnStop = TRUE;
        sprite->animPaused = TRUE;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementAction_WalkSlowUp_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitWalkSlow(objectEvent, sprite, DIR_NORTH);
    return MovementAction_WalkSlowUp_Step1(objectEvent, sprite);
}

static bool8 MovementAction_WalkSlowUp_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (UpdateWalkSlow(objectEvent, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementAction_WalkSlowDown_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitWalkSlow(objectEvent, sprite, DIR_SOUTH);
    return MovementAction_WalkSlowDown_Step1(objectEvent, sprite);
}

static bool8 MovementAction_WalkSlowDown_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (UpdateWalkSlow(objectEvent, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementAction_WalkSlowLeft_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitWalkSlow(objectEvent, sprite, DIR_WEST);
    return MovementAction_WalkSlowLeft_Step1(objectEvent, sprite);
}

static bool8 MovementAction_WalkSlowLeft_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (UpdateWalkSlow(objectEvent, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementAction_WalkSlowRight_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitWalkSlow(objectEvent, sprite, DIR_EAST);
    return MovementAction_WalkSlowRight_Step1(objectEvent, sprite);
}

static bool8 MovementAction_WalkSlowRight_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (UpdateWalkSlow(objectEvent, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementAction_WalkNormalDown_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitMovementNormal(objectEvent, sprite, DIR_SOUTH, MOVE_SPEED_NORMAL);
    return MovementAction_WalkNormalDown_Step1(objectEvent, sprite);
}

static bool8 MovementAction_WalkNormalDown_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (UpdateMovementNormal(objectEvent, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementAction_WalkNormalUp_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitMovementNormal(objectEvent, sprite, DIR_NORTH, MOVE_SPEED_NORMAL);
    return MovementAction_WalkNormalUp_Step1(objectEvent, sprite);
}

static bool8 MovementAction_WalkNormalUp_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (UpdateMovementNormal(objectEvent, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementAction_WalkNormalLeft_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitMovementNormal(objectEvent, sprite, DIR_WEST, MOVE_SPEED_NORMAL);
    return MovementAction_WalkNormalLeft_Step1(objectEvent, sprite);
}

static bool8 MovementAction_WalkNormalLeft_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (UpdateMovementNormal(objectEvent, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementAction_WalkNormalRight_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitMovementNormal(objectEvent, sprite, DIR_EAST, MOVE_SPEED_NORMAL);
    return MovementAction_WalkNormalRight_Step1(objectEvent, sprite);
}

static bool8 MovementAction_WalkNormalRight_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (UpdateMovementNormal(objectEvent, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

#define JUMP_HALFWAY  1
#define JUMP_FINISHED ((u8)-1)

enum {
    JUMP_TYPE_HIGH,
    JUMP_TYPE_LOW,
    JUMP_TYPE_NORMAL,
};

void InitJump(struct ObjectEvent *objectEvent, struct Sprite *sprite, u8 direction, u8 distance, u8 type)
{
    s16 displacements[NELEMS(sJumpInitDisplacements)];
    s16 x;
    s16 y;

    memcpy(displacements, sJumpInitDisplacements, sizeof sJumpInitDisplacements);
    x = 0;
    y = 0;
    SetObjectEventDirection(objectEvent, direction);
    MoveCoordsInDirection(direction, &x, &y, displacements[distance], displacements[distance]);
    ShiftObjectEventCoords(objectEvent, objectEvent->currentCoords.x + x, objectEvent->currentCoords.y + y);
    SetJumpSpriteData(sprite, direction, distance, type);
    sprite->data[2] = 1;
    sprite->animPaused = 0;
    objectEvent->triggerGroundEffectsOnMove = 1;
    objectEvent->disableCoveringGroundEffects = 1;
}

void InitJumpRegular(struct ObjectEvent *objectEvent, struct Sprite *sprite, u8 direction, u8 distance, u8 type)
{
    InitJump(objectEvent, sprite, direction, distance, type);
    SetStepAnimHandleAlternation(objectEvent, sprite, GetMoveDirectionAnimNum(objectEvent->facingDirection));
    DoShadowFieldEffect(objectEvent);
}

u8 UpdateJumpAnim(struct ObjectEvent *objectEvent, struct Sprite *sprite, u8 callback(struct Sprite *))
{
    s16 displacements[NELEMS(sJumpDisplacements)];
    s16 x;
    s16 y;
    u8 result;

    memcpy(displacements, sJumpDisplacements, sizeof sJumpDisplacements);
    result = callback(sprite);
    if (result == JUMP_HALFWAY && displacements[sprite->data[4]] != 0)
    {
        x = 0;
        y = 0;
        MoveCoordsInDirection(objectEvent->movementDirection, &x, &y, displacements[sprite->data[4]], displacements[sprite->data[4]]);
        ShiftObjectEventCoords(objectEvent, objectEvent->currentCoords.x + x, objectEvent->currentCoords.y + y);
        objectEvent->triggerGroundEffectsOnMove = TRUE;
        objectEvent->disableCoveringGroundEffects = TRUE;
    }
    else if (result == JUMP_FINISHED)
    {
        ShiftStillObjectEventCoords(objectEvent);
        objectEvent->triggerGroundEffectsOnStop = TRUE;
        objectEvent->landingJump = TRUE;
        sprite->animPaused = TRUE;
    }
    return result;
}

u8 DoJumpAnimStep(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    return UpdateJumpAnim(objectEvent, sprite, DoJumpSpriteMovement);
}

u8 DoJumpSpecialAnimStep(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    return UpdateJumpAnim(objectEvent, sprite, DoJumpSpecialSpriteMovement);
}

bool8 DoJumpAnim(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (DoJumpAnimStep(objectEvent, sprite) == JUMP_FINISHED)
        return TRUE;

    return FALSE;
}

bool8 DoJumpSpecialAnim(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (DoJumpSpecialAnimStep(objectEvent, sprite) == JUMP_FINISHED)
        return TRUE;

    return FALSE;
}

bool8 DoJumpInPlaceAnim(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    switch (DoJumpAnimStep(objectEvent, sprite))
    {
    case JUMP_FINISHED:
        return TRUE;
    case JUMP_HALFWAY:
        SetObjectEventDirection(objectEvent, GetOppositeDirection(objectEvent->movementDirection));
        SetStepAnim(objectEvent, sprite, GetMoveDirectionAnimNum(objectEvent->facingDirection));
    default:
        return FALSE;
    }
}

static bool8 MovementAction_Jump2Down_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitJumpRegular(objectEvent, sprite, DIR_SOUTH, JUMP_DISTANCE_FAR, JUMP_TYPE_HIGH);
    return MovementAction_Jump2Down_Step1(objectEvent, sprite);
}

static bool8 MovementAction_Jump2Down_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (DoJumpAnim(objectEvent, sprite))
    {
        objectEvent->hasShadow = FALSE;
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementAction_Jump2Up_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitJumpRegular(objectEvent, sprite, DIR_NORTH, JUMP_DISTANCE_FAR, JUMP_TYPE_HIGH);
    return MovementAction_Jump2Up_Step1(objectEvent, sprite);
}

static bool8 MovementAction_Jump2Up_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (DoJumpAnim(objectEvent, sprite))
    {
        objectEvent->hasShadow = FALSE;
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementAction_Jump2Left_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitJumpRegular(objectEvent, sprite, DIR_WEST, JUMP_DISTANCE_FAR, JUMP_TYPE_HIGH);
    return MovementAction_Jump2Left_Step1(objectEvent, sprite);
}

static bool8 MovementAction_Jump2Left_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (DoJumpAnim(objectEvent, sprite))
    {
        objectEvent->hasShadow = FALSE;
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementAction_Jump2Right_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitJumpRegular(objectEvent, sprite, DIR_EAST, JUMP_DISTANCE_FAR, JUMP_TYPE_HIGH);
    return MovementAction_Jump2Right_Step1(objectEvent, sprite);
}

static bool8 MovementAction_Jump2Right_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (DoJumpAnim(objectEvent, sprite))
    {
        objectEvent->hasShadow = FALSE;
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

void InitMovementDelay(struct Sprite *sprite, u16 duration)
{
    sprite->data[2] = 1;
    sprite->data[3] = duration;
}

static bool8 MovementAction_Delay_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (--sprite->data[3] == 0)
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementAction_Delay1_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitMovementDelay(sprite, 1);
    return MovementAction_Delay_Step1(objectEvent, sprite);
}

static bool8 MovementAction_Delay2_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitMovementDelay(sprite, 2);
    return MovementAction_Delay_Step1(objectEvent, sprite);
}

static bool8 MovementAction_Delay4_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitMovementDelay(sprite, 4);
    return MovementAction_Delay_Step1(objectEvent, sprite);
}

static bool8 MovementAction_Delay8_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitMovementDelay(sprite, 8);
    return MovementAction_Delay_Step1(objectEvent, sprite);
}

static bool8 MovementAction_Delay16_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitMovementDelay(sprite, 16);
    return MovementAction_Delay_Step1(objectEvent, sprite);
}

static bool8 MovementAction_WalkFastDown_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitMovementNormal(objectEvent, sprite, DIR_SOUTH, MOVE_SPEED_FAST_1);
    return MovementAction_WalkFastDown_Step1(objectEvent, sprite);
}

static bool8 MovementAction_WalkFastDown_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (UpdateMovementNormal(objectEvent, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementAction_WalkFastUp_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitMovementNormal(objectEvent, sprite, DIR_NORTH, MOVE_SPEED_FAST_1);
    return MovementAction_WalkFastUp_Step1(objectEvent, sprite);
}

static bool8 MovementAction_WalkFastUp_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (UpdateMovementNormal(objectEvent, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementAction_WalkFastLeft_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitMovementNormal(objectEvent, sprite, DIR_WEST, MOVE_SPEED_FAST_1);
    return MovementAction_WalkFastLeft_Step1(objectEvent, sprite);
}

static bool8 MovementAction_WalkFastLeft_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (UpdateMovementNormal(objectEvent, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementAction_WalkFastRight_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitMovementNormal(objectEvent, sprite, DIR_EAST, MOVE_SPEED_FAST_1);
    return MovementAction_WalkFastRight_Step1(objectEvent, sprite);
}

static bool8 MovementAction_WalkFastRight_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (UpdateMovementNormal(objectEvent, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

bool8 UpdateMovementGlide(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (NpcTakeStep(sprite))
    {
        ShiftStillObjectEventCoords(objectEvent);
        objectEvent->triggerGroundEffectsOnStop = TRUE;
        return TRUE;
    }
    return FALSE;
}

u8 MovementAction_GlideDown_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if(objectEvent->facingDirection != DIR_SOUTH)
        StartSpriteAnim(sprite, GetFaceDirectionAnimNum(DIR_SOUTH));
    
    InitNpcForMovement(objectEvent, sprite, DIR_SOUTH, MOVE_SPEED_FAST_1);
    return MovementAction_GlideDown_Step1(objectEvent, sprite);
}

static bool8 MovementAction_GlideDown_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    AnimateSprite(sprite);
    if (UpdateMovementGlide(objectEvent, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

u8 MovementAction_GlideUp_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if(objectEvent->facingDirection != DIR_NORTH)
        StartSpriteAnim(sprite, GetFaceDirectionAnimNum(DIR_NORTH));
    
    InitNpcForMovement(objectEvent, sprite, DIR_NORTH, MOVE_SPEED_FAST_1);
    return MovementAction_GlideUp_Step1(objectEvent, sprite);
}

static bool8 MovementAction_GlideUp_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    AnimateSprite(sprite);
    if (UpdateMovementGlide(objectEvent, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

u8 MovementAction_GlideLeft_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if(objectEvent->facingDirection != DIR_WEST)
        StartSpriteAnim(sprite, GetFaceDirectionAnimNum(DIR_WEST));
    
    InitNpcForMovement(objectEvent, sprite, DIR_WEST, MOVE_SPEED_FAST_1);
    return MovementAction_GlideLeft_Step1(objectEvent, sprite);
}

static bool8 MovementAction_GlideLeft_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    AnimateSprite(sprite);
    if (UpdateMovementGlide(objectEvent, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

u8 MovementAction_GlideRight_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if(objectEvent->facingDirection != DIR_EAST)
        StartSpriteAnim(sprite, GetFaceDirectionAnimNum(DIR_EAST));
    
    InitNpcForMovement(objectEvent, sprite, DIR_EAST, MOVE_SPEED_FAST_1);
    return MovementAction_GlideRight_Step1(objectEvent, sprite);
}

static bool8 MovementAction_GlideRight_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    AnimateSprite(sprite);
    if (UpdateMovementGlide(objectEvent, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

void FaceDirectionFast(struct ObjectEvent *objectEvent, struct Sprite *sprite, u8 direction)
{
    SetObjectEventDirection(objectEvent, direction);
    ShiftStillObjectEventCoords(objectEvent);
    sprite->animPaused = FALSE;
    sprite->data[2] = 1;
}

u8 MovementAction_FaceDownFast_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if(objectEvent->facingDirection != DIR_SOUTH)
        StartSpriteAnim(sprite, GetFaceDirectionAnimNum(DIR_SOUTH));
    
    AnimateSprite(sprite);
    FaceDirectionFast(objectEvent, sprite, DIR_SOUTH);
    return TRUE;
}

u8 MovementAction_FaceUpFast_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if(objectEvent->facingDirection != DIR_NORTH)
        StartSpriteAnim(sprite, GetFaceDirectionAnimNum(DIR_NORTH));
    
    AnimateSprite(sprite);
    FaceDirectionFast(objectEvent, sprite, DIR_NORTH);
    return TRUE;
}

u8 MovementAction_FaceLeftFast_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if(objectEvent->facingDirection != DIR_WEST)
        StartSpriteAnim(sprite, GetFaceDirectionAnimNum(DIR_WEST));
    
    AnimateSprite(sprite);
    FaceDirectionFast(objectEvent, sprite, DIR_WEST);
    return TRUE;
}

u8 MovementAction_FaceRightFast_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if(objectEvent->facingDirection != DIR_EAST)
        StartSpriteAnim(sprite, GetFaceDirectionAnimNum(DIR_EAST));
    
    AnimateSprite(sprite);
    FaceDirectionFast(objectEvent, sprite, DIR_EAST);
    return TRUE;
}

void InitMoveInPlace(struct ObjectEvent *objectEvent, struct Sprite *sprite, u8 direction, u8 animNum, u16 duration)
{
    SetObjectEventDirection(objectEvent, direction);
    SetStepAnimHandleAlternation(objectEvent, sprite, animNum);
    sprite->animPaused = FALSE;
    sprite->data[2] = 1;
    sprite->data[3] = duration;
}

static bool8 MovementAction_WalkInPlace_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (--sprite->data[3] == 0)
    {
        sprite->data[2] = 2;
        sprite->animPaused = TRUE;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementAction_WalkInPlaceSlow_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (sprite->data[3] & 1)
        sprite->animDelayCounter++;

    return MovementAction_WalkInPlace_Step1(objectEvent, sprite);
}

static bool8 MovementAction_WalkInPlaceSlowDown_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitMoveInPlace(objectEvent, sprite, DIR_SOUTH, GetMoveDirectionAnimNum(DIR_SOUTH), 32);
    return MovementAction_WalkInPlaceSlow_Step1(objectEvent, sprite);
}

static bool8 MovementAction_WalkInPlaceSlowUp_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitMoveInPlace(objectEvent, sprite, DIR_NORTH, GetMoveDirectionAnimNum(DIR_NORTH), 32);
    return MovementAction_WalkInPlaceSlow_Step1(objectEvent, sprite);
}

static bool8 MovementAction_WalkInPlaceSlowLeft_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitMoveInPlace(objectEvent, sprite, DIR_WEST, GetMoveDirectionAnimNum(DIR_WEST), 32);
    return MovementAction_WalkInPlaceSlow_Step1(objectEvent, sprite);
}

static bool8 MovementAction_WalkInPlaceSlowRight_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitMoveInPlace(objectEvent, sprite, DIR_EAST, GetMoveDirectionAnimNum(DIR_EAST), 32);
    return MovementAction_WalkInPlaceSlow_Step1(objectEvent, sprite);
}

static bool8 MovementAction_WalkInPlaceNormalDown_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitMoveInPlace(objectEvent, sprite, DIR_SOUTH, GetMoveDirectionAnimNum(DIR_SOUTH), 16);
    return MovementAction_WalkInPlace_Step1(objectEvent, sprite);
}

static bool8 MovementAction_WalkInPlaceNormalUp_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitMoveInPlace(objectEvent, sprite, DIR_NORTH, GetMoveDirectionAnimNum(DIR_NORTH), 16);
    return MovementAction_WalkInPlace_Step1(objectEvent, sprite);
}

static bool8 MovementAction_WalkInPlaceNormalLeft_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitMoveInPlace(objectEvent, sprite, DIR_WEST, GetMoveDirectionAnimNum(DIR_WEST), 16);
    return MovementAction_WalkInPlace_Step1(objectEvent, sprite);
}

static bool8 MovementAction_WalkInPlaceNormalRight_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitMoveInPlace(objectEvent, sprite, DIR_EAST, GetMoveDirectionAnimNum(DIR_EAST), 16);
    return MovementAction_WalkInPlace_Step1(objectEvent, sprite);
}

static bool8 MovementAction_WalkInPlaceFastDown_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitMoveInPlace(objectEvent, sprite, DIR_SOUTH, GetMoveDirectionFastAnimNum(DIR_SOUTH), 8);
    return MovementAction_WalkInPlace_Step1(objectEvent, sprite);
}

static bool8 MovementAction_WalkInPlaceFastUp_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitMoveInPlace(objectEvent, sprite, DIR_NORTH, GetMoveDirectionFastAnimNum(DIR_NORTH), 8);
    return MovementAction_WalkInPlace_Step1(objectEvent, sprite);
}

static bool8 MovementAction_WalkInPlaceFastLeft_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitMoveInPlace(objectEvent, sprite, DIR_WEST, GetMoveDirectionFastAnimNum(DIR_WEST), 8);
    return MovementAction_WalkInPlace_Step1(objectEvent, sprite);
}

static bool8 MovementAction_WalkInPlaceFastRight_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitMoveInPlace(objectEvent, sprite, DIR_EAST, GetMoveDirectionFastAnimNum(DIR_EAST), 8);
    return MovementAction_WalkInPlace_Step1(objectEvent, sprite);
}

static bool8 MovementAction_WalkInPlaceFasterDown_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitMoveInPlace(objectEvent, sprite, DIR_SOUTH, GetMoveDirectionFasterAnimNum(DIR_SOUTH), 4);
    return MovementAction_WalkInPlace_Step1(objectEvent, sprite);
}

static bool8 MovementAction_WalkInPlaceFasterUp_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitMoveInPlace(objectEvent, sprite, DIR_NORTH, GetMoveDirectionFasterAnimNum(DIR_NORTH), 4);
    return MovementAction_WalkInPlace_Step1(objectEvent, sprite);
}

static bool8 MovementAction_WalkInPlaceFasterLeft_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitMoveInPlace(objectEvent, sprite, DIR_WEST, GetMoveDirectionFasterAnimNum(DIR_WEST), 4);
    return MovementAction_WalkInPlace_Step1(objectEvent, sprite);
}

static bool8 MovementAction_WalkInPlaceFasterRight_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitMoveInPlace(objectEvent, sprite, DIR_EAST, GetMoveDirectionFasterAnimNum(DIR_EAST), 4);
    return MovementAction_WalkInPlace_Step1(objectEvent, sprite);
}

static bool8 MovementAction_RideWaterCurrentDown_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitMovementNormal(objectEvent, sprite, DIR_SOUTH, MOVE_SPEED_FAST_2);
    return MovementAction_RideWaterCurrentDown_Step1(objectEvent, sprite);
}

static bool8 MovementAction_RideWaterCurrentDown_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (UpdateMovementNormal(objectEvent, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementAction_RideWaterCurrentUp_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitMovementNormal(objectEvent, sprite, DIR_NORTH, MOVE_SPEED_FAST_2);
    return MovementAction_RideWaterCurrentUp_Step1(objectEvent, sprite);
}

static bool8 MovementAction_RideWaterCurrentUp_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (UpdateMovementNormal(objectEvent, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementAction_RideWaterCurrentLeft_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitMovementNormal(objectEvent, sprite, DIR_WEST, MOVE_SPEED_FAST_2);
    return MovementAction_RideWaterCurrentLeft_Step1(objectEvent, sprite);
}

static bool8 MovementAction_RideWaterCurrentLeft_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (UpdateMovementNormal(objectEvent, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementAction_RideWaterCurrentRight_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitMovementNormal(objectEvent, sprite, DIR_EAST, MOVE_SPEED_FAST_2);
    return MovementAction_RideWaterCurrentRight_Step1(objectEvent, sprite);
}

static bool8 MovementAction_RideWaterCurrentRight_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (UpdateMovementNormal(objectEvent, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementAction_WalkFasterDown_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitMovementNormal(objectEvent, sprite, DIR_SOUTH, MOVE_SPEED_FASTER);
    return MovementAction_WalkFasterDown_Step1(objectEvent, sprite);
}

static bool8 MovementAction_WalkFasterDown_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (UpdateMovementNormal(objectEvent, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementAction_WalkFasterUp_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitMovementNormal(objectEvent, sprite, DIR_NORTH, MOVE_SPEED_FASTER);
    return MovementAction_WalkFasterUp_Step1(objectEvent, sprite);
}

static bool8 MovementAction_WalkFasterUp_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (UpdateMovementNormal(objectEvent, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementAction_WalkFasterLeft_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitMovementNormal(objectEvent, sprite, DIR_WEST, MOVE_SPEED_FASTER);
    return MovementAction_WalkFasterLeft_Step1(objectEvent, sprite);
}

static bool8 MovementAction_WalkFasterLeft_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (UpdateMovementNormal(objectEvent, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementAction_WalkFasterRight_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitMovementNormal(objectEvent, sprite, DIR_EAST, MOVE_SPEED_FASTER);
    return MovementAction_WalkFasterRight_Step1(objectEvent, sprite);
}

static bool8 MovementAction_WalkFasterRight_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (UpdateMovementNormal(objectEvent, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementAction_SlideDown_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitMovementNormal(objectEvent, sprite, DIR_SOUTH, MOVE_SPEED_FASTEST);
    return MovementAction_SlideDown_Step1(objectEvent, sprite);
}

static bool8 MovementAction_SlideDown_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (UpdateMovementNormal(objectEvent, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementAction_SlideUp_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitMovementNormal(objectEvent, sprite, DIR_NORTH, MOVE_SPEED_FASTEST);
    return MovementAction_SlideUp_Step1(objectEvent, sprite);
}

static bool8 MovementAction_SlideUp_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (UpdateMovementNormal(objectEvent, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementAction_SlideLeft_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitMovementNormal(objectEvent, sprite, DIR_WEST, MOVE_SPEED_FASTEST);
    return MovementAction_SlideLeft_Step1(objectEvent, sprite);
}

static bool8 MovementAction_SlideLeft_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (UpdateMovementNormal(objectEvent, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementAction_SlideRight_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitMovementNormal(objectEvent, sprite, DIR_EAST, MOVE_SPEED_FASTEST);
    return MovementAction_SlideRight_Step1(objectEvent, sprite);
}

static bool8 MovementAction_SlideRight_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (UpdateMovementNormal(objectEvent, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementAction_PlayerRunDown_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    StartRunningAnim(objectEvent, sprite, DIR_SOUTH);
    return MovementAction_PlayerRunDown_Step1(objectEvent, sprite);
}

static bool8 MovementAction_PlayerRunDown_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (UpdateMovementNormal(objectEvent, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementAction_PlayerRunUp_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    StartRunningAnim(objectEvent, sprite, DIR_NORTH);
    return MovementAction_PlayerRunUp_Step1(objectEvent, sprite);
}

static bool8 MovementAction_PlayerRunUp_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (UpdateMovementNormal(objectEvent, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementAction_PlayerRunLeft_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    StartRunningAnim(objectEvent, sprite, DIR_WEST);
    return MovementAction_PlayerRunLeft_Step1(objectEvent, sprite);
}

static bool8 MovementAction_PlayerRunLeft_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (UpdateMovementNormal(objectEvent, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementAction_PlayerRunRight_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    StartRunningAnim(objectEvent, sprite, DIR_EAST);
    return MovementAction_PlayerRunRight_Step1(objectEvent, sprite);
}

static bool8 MovementAction_PlayerRunRight_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (UpdateMovementNormal(objectEvent, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

void InitNpcForRunSlow(struct ObjectEvent *objectEvent, struct Sprite *sprite, u8 direction)
{
    s16 x;
    s16 y;

    x = objectEvent->currentCoords.x;
    y = objectEvent->currentCoords.y;
    SetObjectEventDirection(objectEvent, direction);
    MoveCoords(direction, &x, &y);
    ShiftObjectEventCoords(objectEvent, x, y);
    SetRunSlowSpriteData(sprite, direction);
    sprite->animPaused = FALSE;
    objectEvent->triggerGroundEffectsOnMove = TRUE;
    sprite->data[2] = 1;
}

void InitRunSlow(struct ObjectEvent *objectEvent, struct Sprite *sprite, u8 direction)
{
    InitNpcForRunSlow(objectEvent, sprite, direction);
    SetStepAnimHandleAlternation(objectEvent, sprite, GetRunningDirectionAnimNum(objectEvent->facingDirection));
}

bool8 UpdateRunSlow(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (UpdateRunSlowAnim(sprite))
    {
        ShiftStillObjectEventCoords(objectEvent);
        objectEvent->triggerGroundEffectsOnStop = TRUE;
        sprite->animPaused = TRUE;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementAction_RunDownSlow_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitRunSlow(objectEvent, sprite, DIR_SOUTH);
    return MovementAction_RunDownSlow_Step1(objectEvent, sprite);
}

static bool8 MovementAction_RunDownSlow_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (UpdateRunSlow(objectEvent, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementAction_RunUpSlow_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitRunSlow(objectEvent, sprite, DIR_NORTH);
    return MovementAction_RunUpSlow_Step1(objectEvent, sprite);
}

static bool8 MovementAction_RunUpSlow_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (UpdateRunSlow(objectEvent, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementAction_RunLeftSlow_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitRunSlow(objectEvent, sprite, DIR_WEST);
    return MovementAction_RunLeftSlow_Step1(objectEvent, sprite);
}

static bool8 MovementAction_RunLeftSlow_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (UpdateRunSlow(objectEvent, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementAction_RunRightSlow_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitRunSlow(objectEvent, sprite, DIR_SOUTH);
    return MovementAction_RunRightSlow_Step1(objectEvent, sprite);
}

static bool8 MovementAction_RunRightSlow_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (UpdateRunSlow(objectEvent, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

void StartSpriteAnimInDirection(struct ObjectEvent *objectEvent, struct Sprite *sprite, u8 direction, u8 animNum)
{
    SetAndStartSpriteAnim(sprite, animNum, 0);
    SetObjectEventDirection(objectEvent, direction);
    sprite->data[2] = 1;
}

static bool8 MovementAction_StartAnimInDirection_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    StartSpriteAnimInDirection(objectEvent, sprite, objectEvent->movementDirection, sprite->animNum);
    return FALSE;
}

static bool8 MovementAction_WaitSpriteAnim(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (SpriteAnimEnded(sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

void InitJumpSpecial(struct ObjectEvent *objectEvent, struct Sprite *sprite, u8 direction)
{
    InitJump(objectEvent, sprite, direction, JUMP_DISTANCE_NORMAL, JUMP_TYPE_HIGH);
    StartSpriteAnim(sprite, GetJumpSpecialDirectionAnimNum(direction));
}

static bool8 MovementAction_JumpSpecialDown_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitJumpSpecial(objectEvent, sprite, DIR_SOUTH);
    return MovementAction_JumpSpecialDown_Step1(objectEvent, sprite);
}

static bool8 MovementAction_JumpSpecialDown_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (DoJumpSpecialAnim(objectEvent, sprite))
    {
        sprite->data[2] = 2;
        objectEvent->landingJump = FALSE;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementAction_JumpSpecialUp_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitJumpSpecial(objectEvent, sprite, DIR_NORTH);
    return MovementAction_JumpSpecialUp_Step1(objectEvent, sprite);
}

static bool8 MovementAction_JumpSpecialUp_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (DoJumpSpecialAnim(objectEvent, sprite))
    {
        sprite->data[2] = 2;
        objectEvent->landingJump = FALSE;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementAction_JumpSpecialLeft_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitJumpSpecial(objectEvent, sprite, DIR_WEST);
    return MovementAction_JumpSpecialLeft_Step1(objectEvent, sprite);
}

static bool8 MovementAction_JumpSpecialLeft_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (DoJumpSpecialAnim(objectEvent, sprite))
    {
        sprite->data[2] = 2;
        objectEvent->landingJump = FALSE;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementAction_JumpSpecialRight_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitJumpSpecial(objectEvent, sprite, DIR_EAST);
    return MovementAction_JumpSpecialRight_Step1(objectEvent, sprite);
}

static bool8 MovementAction_JumpSpecialRight_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (DoJumpSpecialAnim(objectEvent, sprite))
    {
        sprite->data[2] = 2;
        objectEvent->landingJump = FALSE;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementAction_JumpSpecialWithEffectDown_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitJumpSpecial(objectEvent, sprite, DIR_SOUTH);
    return MovementAction_JumpSpecialWithEffectDown_Step1(objectEvent, sprite);
}

static bool8 MovementAction_JumpSpecialWithEffectDown_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (DoJumpSpecialAnim(objectEvent, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementAction_JumpSpecialWithEffectUp_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitJumpSpecial(objectEvent, sprite, DIR_NORTH);
    return MovementAction_JumpSpecialWithEffectUp_Step1(objectEvent, sprite);
}

static bool8 MovementAction_JumpSpecialWithEffectUp_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (DoJumpSpecialAnim(objectEvent, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementAction_JumpSpecialWithEffectLeft_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitJumpSpecial(objectEvent, sprite, DIR_WEST);
    return MovementAction_JumpSpecialWithEffectLeft_Step1(objectEvent, sprite);
}

static bool8 MovementAction_JumpSpecialWithEffectLeft_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (DoJumpSpecialAnim(objectEvent, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementAction_JumpSpecialWithEffectRight_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitJumpSpecial(objectEvent, sprite, DIR_EAST);
    return MovementAction_JumpSpecialWithEffectRight_Step1(objectEvent, sprite);
}

static bool8 MovementAction_JumpSpecialWithEffectRight_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (DoJumpSpecialAnim(objectEvent, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementAction_FacePlayer_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    u8 playerObjectId;

    if (!TryGetObjectEventIdByLocalIdAndMap(LOCALID_PLAYER, 0, 0, &playerObjectId))
    {
        FaceDirection(objectEvent, sprite, GetDirectionToFace(objectEvent->currentCoords.x, objectEvent->currentCoords.y, gObjectEvents[playerObjectId].currentCoords.x, gObjectEvents[playerObjectId].currentCoords.y));
    }
    sprite->data[2] = 1;
    return TRUE;
}

static bool8 MovementAction_FaceAwayPlayer_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    u8 playerObjectId;

    if (!TryGetObjectEventIdByLocalIdAndMap(LOCALID_PLAYER, 0, 0, &playerObjectId))
    {
        FaceDirection(objectEvent, sprite, GetOppositeDirection(GetDirectionToFace(objectEvent->currentCoords.x, objectEvent->currentCoords.y, gObjectEvents[playerObjectId].currentCoords.x, gObjectEvents[playerObjectId].currentCoords.y)));
    }
    sprite->data[2] = 1;
    return TRUE;
}

static bool8 MovementAction_LockFacingDirection_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    objectEvent->facingDirectionLocked = TRUE;
    sprite->data[2] = 1;
    return TRUE;
}

static bool8 MovementAction_UnlockFacingDirection_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    objectEvent->facingDirectionLocked = FALSE;
    sprite->data[2] = 1;
    return TRUE;
}

static bool8 MovementAction_JumpDown_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitJumpRegular(objectEvent, sprite, DIR_SOUTH, JUMP_DISTANCE_NORMAL, JUMP_TYPE_NORMAL);
    return MovementAction_JumpDown_Step1(objectEvent, sprite);
}

static bool8 MovementAction_JumpDown_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (DoJumpAnim(objectEvent, sprite))
    {
        objectEvent->hasShadow = FALSE;
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementAction_JumpUp_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitJumpRegular(objectEvent, sprite, DIR_NORTH, JUMP_DISTANCE_NORMAL, JUMP_TYPE_NORMAL);
    return MovementAction_JumpUp_Step1(objectEvent, sprite);
}

static bool8 MovementAction_JumpUp_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (DoJumpAnim(objectEvent, sprite))
    {
        objectEvent->hasShadow = FALSE;
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementAction_JumpLeft_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitJumpRegular(objectEvent, sprite, DIR_WEST, JUMP_DISTANCE_NORMAL, JUMP_TYPE_NORMAL);
    return MovementAction_JumpLeft_Step1(objectEvent, sprite);
}

static bool8 MovementAction_JumpLeft_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (DoJumpAnim(objectEvent, sprite))
    {
        objectEvent->hasShadow = FALSE;
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementAction_JumpRight_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitJumpRegular(objectEvent, sprite, DIR_EAST, JUMP_DISTANCE_NORMAL, JUMP_TYPE_NORMAL);
    return MovementAction_JumpRight_Step1(objectEvent, sprite);
}

static bool8 MovementAction_JumpRight_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (DoJumpAnim(objectEvent, sprite))
    {
        objectEvent->hasShadow = FALSE;
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementAction_JumpInPlaceDown_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitJumpRegular(objectEvent, sprite, DIR_SOUTH, JUMP_DISTANCE_IN_PLACE, JUMP_TYPE_HIGH);
    return MovementAction_JumpInPlaceDown_Step1(objectEvent, sprite);
}

static bool8 MovementAction_JumpInPlaceDown_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (DoJumpAnim(objectEvent, sprite))
    {
        objectEvent->hasShadow = FALSE;
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementAction_JumpInPlaceUp_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitJumpRegular(objectEvent, sprite, DIR_NORTH, JUMP_DISTANCE_IN_PLACE, JUMP_TYPE_HIGH);
    return MovementAction_JumpInPlaceUp_Step1(objectEvent, sprite);
}

static bool8 MovementAction_JumpInPlaceUp_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (DoJumpAnim(objectEvent, sprite))
    {
        objectEvent->hasShadow = FALSE;
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementAction_JumpInPlaceLeft_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitJumpRegular(objectEvent, sprite, DIR_WEST, JUMP_DISTANCE_IN_PLACE, JUMP_TYPE_HIGH);
    return MovementAction_JumpInPlaceLeft_Step1(objectEvent, sprite);
}

static bool8 MovementAction_JumpInPlaceLeft_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (DoJumpAnim(objectEvent, sprite))
    {
        objectEvent->hasShadow = FALSE;
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementAction_JumpInPlaceRight_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitJumpRegular(objectEvent, sprite, DIR_EAST, JUMP_DISTANCE_IN_PLACE, JUMP_TYPE_HIGH);
    return MovementAction_JumpInPlaceRight_Step1(objectEvent, sprite);
}

static bool8 MovementAction_JumpInPlaceRight_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (DoJumpAnim(objectEvent, sprite))
    {
        objectEvent->hasShadow = FALSE;
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementAction_JumpInPlaceDownUp_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitJumpRegular(objectEvent, sprite, DIR_SOUTH, JUMP_DISTANCE_IN_PLACE, JUMP_TYPE_NORMAL);
    return MovementAction_JumpInPlaceDownUp_Step1(objectEvent, sprite);
}

static bool8 MovementAction_JumpInPlaceDownUp_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (DoJumpInPlaceAnim(objectEvent, sprite))
    {
        objectEvent->hasShadow = FALSE;
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementAction_JumpInPlaceUpDown_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitJumpRegular(objectEvent, sprite, DIR_NORTH, JUMP_DISTANCE_IN_PLACE, JUMP_TYPE_NORMAL);
    return MovementAction_JumpInPlaceUpDown_Step1(objectEvent, sprite);
}

static bool8 MovementAction_JumpInPlaceUpDown_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (DoJumpInPlaceAnim(objectEvent, sprite))
    {
        objectEvent->hasShadow = FALSE;
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementAction_JumpInPlaceLeftRight_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitJumpRegular(objectEvent, sprite, DIR_WEST, JUMP_DISTANCE_IN_PLACE, JUMP_TYPE_NORMAL);
    return MovementAction_JumpInPlaceLeftRight_Step1(objectEvent, sprite);
}

static bool8 MovementAction_JumpInPlaceLeftRight_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (DoJumpInPlaceAnim(objectEvent, sprite))
    {
        objectEvent->hasShadow = FALSE;
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementAction_JumpInPlaceRightLeft_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitJumpRegular(objectEvent, sprite, DIR_EAST, JUMP_DISTANCE_IN_PLACE, JUMP_TYPE_NORMAL);
    return MovementAction_JumpInPlaceRightLeft_Step1(objectEvent, sprite);
}

static bool8 MovementAction_JumpInPlaceRightLeft_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (DoJumpInPlaceAnim(objectEvent, sprite))
    {
        objectEvent->hasShadow = FALSE;
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementAction_FaceOriginalDirection_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    FaceDirection(objectEvent, sprite, gInitialMovementTypeFacingDirections[objectEvent->movementType]);
    return TRUE;
}

static bool8 MovementAction_NurseJoyBowDown_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    StartSpriteAnimInDirection(objectEvent, sprite, DIR_SOUTH, ANIM_NURSE_BOW);
    return FALSE;
}

static bool8 MovementAction_EnableJumpLandingGroundEffect_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    objectEvent->disableJumpLandingGroundEffect = FALSE;
    sprite->data[2] = 1;
    return TRUE;
}

static bool8 MovementAction_DisableJumpLandingGroundEffect_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    objectEvent->disableJumpLandingGroundEffect = TRUE;
    sprite->data[2] = 1;
    return TRUE;
}

static bool8 MovementAction_DisableAnimation_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    objectEvent->inanimate = TRUE;
    sprite->data[2] = 1;
    return TRUE;
}

static bool8 MovementAction_RestoreAnimation_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    objectEvent->inanimate = GetObjectEventGraphicsInfo(objectEvent->graphicsId)->inanimate;
    sprite->data[2] = 1;
    return TRUE;
}

static bool8 MovementAction_SetInvisible_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    objectEvent->invisible = TRUE;
    sprite->data[2] = 1;
    return TRUE;
}

static bool8 MovementAction_SetVisible_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    objectEvent->invisible = FALSE;
    sprite->data[2] = 1;
    return TRUE;
}

static bool8 MovementAction_EmoteExclamationMark_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    ObjectEventGetLocalIdAndMap(objectEvent, &gFieldEffectArguments[0], &gFieldEffectArguments[1], &gFieldEffectArguments[2]);
    FieldEffectStart(FLDEFF_EXCLAMATION_MARK_ICON);
    sprite->data[2] = 1;
    return TRUE;
}

static bool8 MovementAction_EmoteQuestionMark_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    ObjectEventGetLocalIdAndMap(objectEvent, &gFieldEffectArguments[0], &gFieldEffectArguments[1], &gFieldEffectArguments[2]);
    FieldEffectStart(FLDEFF_QUESTION_MARK_ICON);
    sprite->data[2] = 1;
    return TRUE;
}

static bool8 MovementAction_EmoteX_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    ObjectEventGetLocalIdAndMap(objectEvent, &gFieldEffectArguments[0], &gFieldEffectArguments[1], &gFieldEffectArguments[2]);
    FieldEffectStart(FLDEFF_X_ICON);
    sprite->data[2] = 1;
    return TRUE;
}

static bool8 MovementAction_EmoteDoubleExclamationMark_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    ObjectEventGetLocalIdAndMap(objectEvent, &gFieldEffectArguments[0], &gFieldEffectArguments[1], &gFieldEffectArguments[2]);
    FieldEffectStart(FLDEFF_DOUBLE_EXCL_MARK_ICON);
    sprite->data[2] = 1;
    return TRUE;
}

static bool8 MovementAction_EmoteSmile_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    ObjectEventGetLocalIdAndMap(objectEvent, &gFieldEffectArguments[0], &gFieldEffectArguments[1], &gFieldEffectArguments[2]);
    FieldEffectStart(FLDEFF_SMILEY_FACE_ICON);
    sprite->data[2] = 1;
    return TRUE;
}

static bool8 MovementAction_RevealTrainer_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (objectEvent->movementType == MOVEMENT_TYPE_BURIED)
    {
        MovementAction_RevealTrainer_RunTrainerSeeFuncList(objectEvent);
        return FALSE;
    }
    if (objectEvent->movementType != MOVEMENT_TYPE_TREE_DISGUISE && objectEvent->movementType != MOVEMENT_TYPE_MOUNTAIN_DISGUISE)
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    StartRevealDisguise(objectEvent);
    sprite->data[2] = 1;
    return MovementAction_RevealTrainer_Step1(objectEvent, sprite);
}

static bool8 MovementAction_RevealTrainer_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (UpdateRevealDisguise(objectEvent))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementAction_RockSmashBreak_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    SetAndStartSpriteAnim(sprite, ANIM_REMOVE_OBSTACLE, 0);
    sprite->data[2] = 1;
    return FALSE;
}

static bool8 MovementAction_RockSmashBreak_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (SpriteAnimEnded(sprite))
    {
        SetMovementDelay(sprite, 32);
        sprite->data[2] = 2;
    }
    return FALSE;
}

static bool8 MovementAction_RockSmashBreak_Step2(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    objectEvent->invisible ^= TRUE;
    if (WaitForMovementDelay(sprite))
    {
        objectEvent->invisible = TRUE;
        sprite->data[2] = 3;
    }
    return FALSE;
}

static bool8 MovementAction_CutTree_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    SetAndStartSpriteAnim(sprite, ANIM_REMOVE_OBSTACLE, 0);
    sprite->data[2] = 1;
    return FALSE;
}

static bool8 MovementAction_CutTree_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (SpriteAnimEnded(sprite))
    {
        SetMovementDelay(sprite, 32);
        sprite->data[2] = 2;
    }
    return FALSE;
}

static bool8 MovementAction_CutTree_Step2(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    objectEvent->invisible ^= TRUE;
    if (WaitForMovementDelay(sprite))
    {
        objectEvent->invisible = TRUE;
        sprite->data[2] = 3;
    }
    return FALSE;
}

static bool8 MovementAction_SetFixedPriority_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    objectEvent->fixedPriority = TRUE;
    sprite->data[2] = 1;
    return TRUE;
}

static bool8 MovementAction_ClearFixedPriority_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    objectEvent->fixedPriority = FALSE;
    sprite->data[2] = 1;
    return TRUE;
}

static bool8 MovementAction_InitAffineAnim_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    sprite->oam.affineMode = ST_OAM_AFFINE_DOUBLE;
    InitSpriteAffineAnim(sprite);
    sprite->affineAnimPaused = TRUE;
    sprite->subspriteMode = SUBSPRITES_OFF;
    return TRUE;
}

static bool8 MovementAction_ClearAffineAnim_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    FreeOamMatrix(sprite->oam.matrixNum);
    sprite->oam.affineMode = ST_OAM_AFFINE_OFF;
    CalcCenterToCornerVec(sprite, sprite->oam.shape, sprite->oam.size, sprite->oam.affineMode);
    return TRUE;
}

static bool8 MovementAction_WalkDownStartAffine_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitWalkSlower(objectEvent, sprite, DIR_SOUTH);
    sprite->affineAnimPaused = FALSE;
    StartSpriteAffineAnimIfDifferent(sprite, 0);
    return MovementAction_WalkDownStartAffine_Step1(objectEvent, sprite);
}

static bool8 MovementAction_WalkDownStartAffine_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (UpdateWalkSlower(objectEvent, sprite))
    {
        sprite->affineAnimPaused = TRUE;
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementAction_WalkDownAffine_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitWalkSlower(objectEvent, sprite, DIR_SOUTH);
    sprite->affineAnimPaused = FALSE;
    ChangeSpriteAffineAnimIfDifferent(sprite, 1);
    return MovementAction_WalkDownAffine_Step1(objectEvent, sprite);
}

static bool8 MovementAction_WalkDownAffine_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (UpdateWalkSlower(objectEvent, sprite))
    {
        sprite->affineAnimPaused = TRUE;
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

void AcroWheelieFaceDirection(struct ObjectEvent *objectEvent, struct Sprite *sprite, u8 direction)
{
    SetObjectEventDirection(objectEvent, direction);
    ShiftStillObjectEventCoords(objectEvent);
    SetStepAnim(objectEvent, sprite, GetAcroWheeliePedalDirectionAnimNum(direction));
    sprite->animPaused = TRUE;
    sprite->data[2] = 1;
}

static bool8 MovementAction_AcroWheelieFaceDown_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    AcroWheelieFaceDirection(objectEvent, sprite, DIR_SOUTH);
    return TRUE;
}

static bool8 MovementAction_AcroWheelieFaceUp_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    AcroWheelieFaceDirection(objectEvent, sprite, DIR_NORTH);
    return TRUE;
}

static bool8 MovementAction_AcroWheelieFaceLeft_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    AcroWheelieFaceDirection(objectEvent, sprite, DIR_WEST);
    return TRUE;
}

static bool8 MovementAction_AcroWheelieFaceRight_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    AcroWheelieFaceDirection(objectEvent, sprite, DIR_EAST);
    return TRUE;
}

static bool8 MovementAction_AcroPopWheelieDown_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    StartSpriteAnimInDirection(objectEvent, sprite, DIR_SOUTH, GetAcroWheelieDirectionAnimNum(DIR_SOUTH));
    return FALSE;
}

static bool8 MovementAction_AcroPopWheelieUp_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    StartSpriteAnimInDirection(objectEvent, sprite, DIR_NORTH, GetAcroWheelieDirectionAnimNum(DIR_NORTH));
    return FALSE;
}

static bool8 MovementAction_AcroPopWheelieLeft_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    StartSpriteAnimInDirection(objectEvent, sprite, DIR_WEST, GetAcroWheelieDirectionAnimNum(DIR_WEST));
    return FALSE;
}

static bool8 MovementAction_AcroPopWheelieRight_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    StartSpriteAnimInDirection(objectEvent, sprite, DIR_EAST, GetAcroWheelieDirectionAnimNum(DIR_EAST));
    return FALSE;
}

static bool8 MovementAction_AcroEndWheelieFaceDown_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    StartSpriteAnimInDirection(objectEvent, sprite, DIR_SOUTH, GetAcroEndWheelieDirectionAnimNum(DIR_SOUTH));
    return FALSE;
}

static bool8 MovementAction_AcroEndWheelieFaceUp_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    StartSpriteAnimInDirection(objectEvent, sprite, DIR_NORTH, GetAcroEndWheelieDirectionAnimNum(DIR_NORTH));
    return FALSE;
}

static bool8 MovementAction_AcroEndWheelieFaceLeft_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    StartSpriteAnimInDirection(objectEvent, sprite, DIR_WEST, GetAcroEndWheelieDirectionAnimNum(DIR_WEST));
    return FALSE;
}

static bool8 MovementAction_AcroEndWheelieFaceRight_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    StartSpriteAnimInDirection(objectEvent, sprite, DIR_EAST, GetAcroEndWheelieDirectionAnimNum(DIR_EAST));
    return FALSE;
}

static bool8 MovementAction_UnusedAcroActionDown_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    StartSpriteAnimInDirection(objectEvent, sprite, DIR_SOUTH, GetAcroUnusedActionDirectionAnimNum(DIR_SOUTH));
    return FALSE;
}

static bool8 MovementAction_UnusedAcroActionUp_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    StartSpriteAnimInDirection(objectEvent, sprite, DIR_NORTH, GetAcroUnusedActionDirectionAnimNum(DIR_NORTH));
    return FALSE;
}

static bool8 MovementAction_UnusedAcroActionLeft_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    StartSpriteAnimInDirection(objectEvent, sprite, DIR_WEST, GetAcroUnusedActionDirectionAnimNum(DIR_WEST));
    return FALSE;
}

static bool8 MovementAction_UnusedAcroActionRight_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    StartSpriteAnimInDirection(objectEvent, sprite, DIR_EAST, GetAcroUnusedActionDirectionAnimNum(DIR_EAST));
    return FALSE;
}

void InitAcroWheelieJump(struct ObjectEvent *objectEvent, struct Sprite *sprite, u8 direction, u8 distance, u8 type)
{
    InitJump(objectEvent, sprite, direction, distance, type);
    StartSpriteAnimIfDifferent(sprite, GetAcroWheelieDirectionAnimNum(direction));
    DoShadowFieldEffect(objectEvent);
}

static bool8 MovementAction_AcroWheelieHopFaceDown_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitAcroWheelieJump(objectEvent, sprite, DIR_SOUTH, JUMP_DISTANCE_IN_PLACE, JUMP_TYPE_LOW);
    return MovementAction_AcroWheelieHopFaceDown_Step1(objectEvent, sprite);
}

static bool8 MovementAction_AcroWheelieHopFaceDown_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (DoJumpAnim(objectEvent, sprite))
    {
        objectEvent->hasShadow = FALSE;
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementAction_AcroWheelieHopFaceUp_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitAcroWheelieJump(objectEvent, sprite, DIR_NORTH, JUMP_DISTANCE_IN_PLACE, JUMP_TYPE_LOW);
    return MovementAction_AcroWheelieHopFaceUp_Step1(objectEvent, sprite);
}

static bool8 MovementAction_AcroWheelieHopFaceUp_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (DoJumpAnim(objectEvent, sprite))
    {
        objectEvent->hasShadow = FALSE;
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementAction_AcroWheelieHopFaceLeft_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitAcroWheelieJump(objectEvent, sprite, DIR_WEST, JUMP_DISTANCE_IN_PLACE, JUMP_TYPE_LOW);
    return MovementAction_AcroWheelieHopFaceLeft_Step1(objectEvent, sprite);
}

static bool8 MovementAction_AcroWheelieHopFaceLeft_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (DoJumpAnim(objectEvent, sprite))
    {
        objectEvent->hasShadow = FALSE;
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementAction_AcroWheelieHopFaceRight_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitAcroWheelieJump(objectEvent, sprite, DIR_EAST, JUMP_DISTANCE_IN_PLACE, JUMP_TYPE_LOW);
    return MovementAction_AcroWheelieHopFaceRight_Step1(objectEvent, sprite);
}

static bool8 MovementAction_AcroWheelieHopFaceRight_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (DoJumpAnim(objectEvent, sprite))
    {
        objectEvent->hasShadow = FALSE;
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementAction_AcroWheelieHopDown_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitAcroWheelieJump(objectEvent, sprite, DIR_SOUTH, JUMP_DISTANCE_NORMAL, JUMP_TYPE_LOW);
    return MovementAction_AcroWheelieHopDown_Step1(objectEvent, sprite);
}

static bool8 MovementAction_AcroWheelieHopDown_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (DoJumpAnim(objectEvent, sprite))
    {
        objectEvent->hasShadow = FALSE;
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementAction_AcroWheelieHopUp_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitAcroWheelieJump(objectEvent, sprite, DIR_NORTH, JUMP_DISTANCE_NORMAL, JUMP_TYPE_LOW);
    return MovementAction_AcroWheelieHopUp_Step1(objectEvent, sprite);
}

static bool8 MovementAction_AcroWheelieHopUp_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (DoJumpAnim(objectEvent, sprite))
    {
        objectEvent->hasShadow = FALSE;
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementAction_AcroWheelieHopLeft_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitAcroWheelieJump(objectEvent, sprite, DIR_WEST, JUMP_DISTANCE_NORMAL, JUMP_TYPE_LOW);
    return MovementAction_AcroWheelieHopLeft_Step1(objectEvent, sprite);
}

static bool8 MovementAction_AcroWheelieHopLeft_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (DoJumpAnim(objectEvent, sprite))
    {
        objectEvent->hasShadow = FALSE;
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementAction_AcroWheelieHopRight_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitAcroWheelieJump(objectEvent, sprite, DIR_EAST, JUMP_DISTANCE_NORMAL, JUMP_TYPE_LOW);
    return MovementAction_AcroWheelieHopRight_Step1(objectEvent, sprite);
}

static bool8 MovementAction_AcroWheelieHopRight_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (DoJumpAnim(objectEvent, sprite))
    {
        objectEvent->hasShadow = FALSE;
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementAction_AcroWheelieJumpDown_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitAcroWheelieJump(objectEvent, sprite, DIR_SOUTH, JUMP_DISTANCE_FAR, JUMP_TYPE_HIGH);
    return MovementAction_AcroWheelieJumpDown_Step1(objectEvent, sprite);
}

static bool8 MovementAction_AcroWheelieJumpDown_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (DoJumpAnim(objectEvent, sprite))
    {
        objectEvent->hasShadow = FALSE;
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementAction_AcroWheelieJumpUp_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitAcroWheelieJump(objectEvent, sprite, DIR_NORTH, JUMP_DISTANCE_FAR, JUMP_TYPE_HIGH);
    return MovementAction_AcroWheelieJumpUp_Step1(objectEvent, sprite);
}

static bool8 MovementAction_AcroWheelieJumpUp_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (DoJumpAnim(objectEvent, sprite))
    {
        objectEvent->hasShadow = FALSE;
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementAction_AcroWheelieJumpLeft_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitAcroWheelieJump(objectEvent, sprite, DIR_WEST, JUMP_DISTANCE_FAR, JUMP_TYPE_HIGH);
    return MovementAction_AcroWheelieJumpLeft_Step1(objectEvent, sprite);
}

static bool8 MovementAction_AcroWheelieJumpLeft_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (DoJumpAnim(objectEvent, sprite))
    {
        objectEvent->hasShadow = FALSE;
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementAction_AcroWheelieJumpRight_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitAcroWheelieJump(objectEvent, sprite, DIR_EAST, JUMP_DISTANCE_FAR, JUMP_TYPE_HIGH);
    return MovementAction_AcroWheelieJumpRight_Step1(objectEvent, sprite);
}

static bool8 MovementAction_AcroWheelieJumpRight_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (DoJumpAnim(objectEvent, sprite))
    {
        objectEvent->hasShadow = FALSE;
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementAction_AcroWheelieInPlaceDown_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitMoveInPlace(objectEvent, sprite, DIR_SOUTH, GetAcroWheeliePedalDirectionAnimNum(DIR_SOUTH), 8);
    return MovementAction_WalkInPlace_Step1(objectEvent, sprite);
}

static bool8 MovementAction_AcroWheelieInPlaceUp_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitMoveInPlace(objectEvent, sprite, DIR_NORTH, GetAcroWheeliePedalDirectionAnimNum(DIR_NORTH), 8);
    return MovementAction_WalkInPlace_Step1(objectEvent, sprite);
}

static bool8 MovementAction_AcroWheelieInPlaceLeft_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitMoveInPlace(objectEvent, sprite, DIR_WEST, GetAcroWheeliePedalDirectionAnimNum(DIR_WEST), 8);
    return MovementAction_WalkInPlace_Step1(objectEvent, sprite);
}

static bool8 MovementAction_AcroWheelieInPlaceRight_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitMoveInPlace(objectEvent, sprite, DIR_EAST, GetAcroWheeliePedalDirectionAnimNum(DIR_EAST), 8);
    return MovementAction_WalkInPlace_Step1(objectEvent, sprite);
}

void InitAcroPopWheelie(struct ObjectEvent *objectEvent, struct Sprite *sprite, u8 direction, u8 speed)
{
    InitNpcForMovement(objectEvent, sprite, direction, speed);
    StartSpriteAnim(sprite, GetAcroWheelieDirectionAnimNum(objectEvent->facingDirection));
    SeekSpriteAnim(sprite, 0);
}

static bool8 MovementAction_AcroPopWheelieMoveDown_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitAcroPopWheelie(objectEvent, sprite, DIR_SOUTH, MOVE_SPEED_FAST_1);
    return MovementAction_AcroPopWheelieMoveDown_Step1(objectEvent, sprite);
}

static bool8 MovementAction_AcroPopWheelieMoveDown_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (UpdateMovementNormal(objectEvent, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementAction_AcroPopWheelieMoveUp_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitAcroPopWheelie(objectEvent, sprite, DIR_NORTH, MOVE_SPEED_FAST_1);
    return MovementAction_AcroPopWheelieMoveUp_Step1(objectEvent, sprite);
}

static bool8 MovementAction_AcroPopWheelieMoveUp_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (UpdateMovementNormal(objectEvent, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementAction_AcroPopWheelieMoveLeft_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitAcroPopWheelie(objectEvent, sprite, DIR_WEST, MOVE_SPEED_FAST_1);
    return MovementAction_AcroPopWheelieMoveLeft_Step1(objectEvent, sprite);
}

static bool8 MovementAction_AcroPopWheelieMoveLeft_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (UpdateMovementNormal(objectEvent, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementAction_AcroPopWheelieMoveRight_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitAcroPopWheelie(objectEvent, sprite, DIR_EAST, MOVE_SPEED_FAST_1);
    return MovementAction_AcroPopWheelieMoveRight_Step1(objectEvent, sprite);
}

static bool8 MovementAction_AcroPopWheelieMoveRight_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (UpdateMovementNormal(objectEvent, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

void InitAcroWheelieMove(struct ObjectEvent *objectEvent, struct Sprite *sprite, u8 direction, u8 speed)
{
    InitNpcForMovement(objectEvent, sprite, direction, speed);
    SetStepAnimHandleAlternation(objectEvent, sprite, GetAcroWheeliePedalDirectionAnimNum(objectEvent->facingDirection));
}

static bool8 MovementAction_AcroWheelieMoveDown_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitAcroWheelieMove(objectEvent, sprite, DIR_SOUTH, MOVE_SPEED_FAST_1);
    return MovementAction_AcroWheelieMoveDown_Step1(objectEvent, sprite);
}

static bool8 MovementAction_AcroWheelieMoveDown_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (UpdateMovementNormal(objectEvent, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementAction_AcroWheelieMoveUp_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitAcroWheelieMove(objectEvent, sprite, DIR_NORTH, MOVE_SPEED_FAST_1);
    return MovementAction_AcroWheelieMoveUp_Step1(objectEvent, sprite);
}

static bool8 MovementAction_AcroWheelieMoveUp_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (UpdateMovementNormal(objectEvent, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementAction_AcroWheelieMoveLeft_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitAcroWheelieMove(objectEvent, sprite, DIR_WEST, MOVE_SPEED_FAST_1);
    return MovementAction_AcroWheelieMoveLeft_Step1(objectEvent, sprite);
}

static bool8 MovementAction_AcroWheelieMoveLeft_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (UpdateMovementNormal(objectEvent, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementAction_AcroWheelieMoveRight_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitAcroWheelieMove(objectEvent, sprite, DIR_EAST, MOVE_SPEED_FAST_1);
    return MovementAction_AcroWheelieMoveRight_Step1(objectEvent, sprite);
}

static bool8 MovementAction_AcroWheelieMoveRight_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (UpdateMovementNormal(objectEvent, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

void InitSpin(struct ObjectEvent *objectEvent, struct Sprite *sprite, u8 direction, u8 speed)
{
    InitNpcForMovement(objectEvent, sprite, direction, speed);
    SetStepAnimHandleAlternation(objectEvent, sprite, GetSpinDirectionAnimNum(objectEvent->facingDirection));
    SeekSpriteAnim(sprite, 0);
}

static bool8 MovementAction_SpinDown_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitSpin(objectEvent, sprite, DIR_SOUTH, MOVE_SPEED_FAST_1);
    return MovementAction_SpinDown_Step1(objectEvent, sprite);
}

static bool8 MovementAction_SpinDown_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (UpdateMovementNormal(objectEvent, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementAction_SpinUp_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitSpin(objectEvent, sprite, DIR_NORTH, MOVE_SPEED_FAST_1);
    return MovementAction_SpinUp_Step1(objectEvent, sprite);
}

static bool8 MovementAction_SpinUp_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (UpdateMovementNormal(objectEvent, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementAction_SpinLeft_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitSpin(objectEvent, sprite, DIR_WEST, MOVE_SPEED_FAST_1);
    return MovementAction_SpinLeft_Step1(objectEvent, sprite);
}

static bool8 MovementAction_SpinLeft_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (UpdateMovementNormal(objectEvent, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementAction_SpinRight_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    InitSpin(objectEvent, sprite, DIR_EAST, MOVE_SPEED_FAST_1);
    return MovementAction_SpinRight_Step1(objectEvent, sprite);
}

static bool8 MovementAction_SpinRight_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (UpdateMovementNormal(objectEvent, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

static bool8 MovementAction_RaiseHand_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    StartSpriteAnim(sprite, ANIM_RAISE_HAND);
    sprite->animPaused = FALSE;
    objectEvent->disableAnim = FALSE;
    sprite->data[2] = 1;
    sprite->data[4] = 0;
    sprite->data[5] = 0;
    sprite->data[6] = 0;
    sprite->data[7] = 0;
    return FALSE;
}

static bool8 MovementAction_RaiseHandAndStop_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    return sprite->animEnded;
}

static bool8 MovementAction_RaiseHandAndJump_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    switch (sprite->data[7])
    {
    case 0:
        if((sprite->data[6] += 10) > 127)
        {
            sprite->data[6] = 0;
            sprite->data[5]++;
            sprite->data[7] = sprite->data[5];
            StartSpriteAnim(sprite, ANIM_STD_FACE_SOUTH);
            sprite->animPaused = FALSE;
            objectEvent->disableAnim = FALSE;
        }
        sprite->y2 = -(3 * gSineTable[sprite->data[6]] >> 7);
        objectEvent->singleMovementActive = sprite->y2 != 0;
        return FALSE;
    case 1:
        if (++sprite->data[4] > 16)
        {
            sprite->data[4] = 0;
            StartSpriteAnim(sprite, ANIM_RAISE_HAND);
            sprite->animPaused = FALSE;
            objectEvent->disableAnim = FALSE;
            sprite->data[7] = 0;
        }
        else
        {
            objectEvent->singleMovementActive = FALSE;
        }
        return FALSE;
    case 2:
        objectEvent->singleMovementActive = FALSE;
        if (++sprite->data[4] > 80)
        {
            sprite->data[4] = 0;
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }
    return FALSE;
}

static bool8 MovementAction_RaiseHandAndSwim_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    bool8 ret;
    sprite->data[7] = (sprite->data[7] + 4) & 0xFF;
    sprite->x2 = gSineTable[sprite->data[7]] >> 7;
    if (sprite->data[7] == 0)
        ret = TRUE;
    else
        ret = FALSE;
    return ret;
}

static bool8 MovementAction_ShakeHeadOrWalkInPlace_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    StartSpriteAnim(sprite, ANIM_SHAKE_HEAD_OR_WALK_IN_PLACE);
    sprite->animPaused = FALSE;
    objectEvent->disableAnim = FALSE;
    sprite->data[2] = 1;
    return FALSE;
}

static bool8 MovementAction_ShakeHeadOrWalkInPlace_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    return sprite->animEnded;
}

u8 MovementAction_Finish(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    return TRUE;
}

static bool8 MovementAction_PauseSpriteAnim(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    sprite->animPaused = TRUE;
    return TRUE;
}

static bool8 MovementAction_FlyUp_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    sprite->y2 = 0;
    sprite->data[2]++;
    return FALSE;
}

static bool8 MovementAction_FlyUp_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    sprite->y2 -= 8;
    if (sprite->y2 == -160)
        sprite->data[2]++;
    return FALSE;
}

static bool8 MovementAction_FlyDown_Step0(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    sprite->y2 = -160;
    sprite->data[2]++;
    return FALSE;
}

static bool8 MovementAction_FlyDown_Step1(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    sprite->y2 += 8;
    if (sprite->y2 == 0)
        sprite->data[2]++;
    return FALSE;
}

u8 MovementAction_FlyUp_Step2(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    return TRUE;
}

static void UpdateObjectEventSpriteAnimPause(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (objectEvent->disableAnim)
    {
        sprite->animPaused = TRUE;
    }
}

static void TryEnableObjectEventAnim(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    if (objectEvent->enableAnim)
    {
        sprite->animPaused = FALSE;
        objectEvent->disableAnim = FALSE;
        objectEvent->enableAnim = FALSE;
    }
}

static void UpdateObjectEventVisibility(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    CalcWhetherObjectIsOffscreen(objectEvent, sprite);
    UpdateObjEventSpriteVisibility(objectEvent, sprite);
}

static void CalcWhetherObjectIsOffscreen(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    u16 x, y;
    u16 x2, y2;
    const struct ObjectEventGraphicsInfo *graphicsInfo;
    s16 minX;

    objectEvent->offScreen = FALSE;
    graphicsInfo = GetObjectEventGraphicsInfo(objectEvent->graphicsId);
    if (sprite->coordOffsetEnabled)
    {
        x = sprite->x + sprite->x2 + sprite->centerToCornerVecX + gSpriteCoordOffsetX;
        y = sprite->y + sprite->y2 + sprite->centerToCornerVecY + gSpriteCoordOffsetY;
    }
    else
    {
        x = sprite->x + sprite->x2 + sprite->centerToCornerVecX;
        y = sprite->y + sprite->y2 + sprite->centerToCornerVecY;
    }
    x2 = graphicsInfo->width + (s16)x;
    y2 = graphicsInfo->height + (s16)y;
    
    if (gSaveBlock1Ptr->location.mapGroup == MAP_GROUP(MAP_SSANNE_EXTERIOR)
     && gSaveBlock1Ptr->location.mapNum == MAP_NUM(MAP_SSANNE_EXTERIOR)
     && objectEvent->localId == LOCALID_SS_ANNE)
    {
        minX = -32;
    }
    else
    {
        minX = -16;
    }
    if ((s16)x >= (DISPLAY_WIDTH + 16) || (s16)x2 < minX)
    {
        objectEvent->offScreen = TRUE;
    }
    if ((s16)y >= (DISPLAY_HEIGHT + 16) || (s16)y2 < -16)
    {
        objectEvent->offScreen = TRUE;
    }
}

static void UpdateObjEventSpriteVisibility(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    sprite->invisible = FALSE;
    if (objectEvent->invisible || objectEvent->offScreen)
    {
        sprite->invisible = TRUE;
    }
}

static void GetAllGroundEffectFlags_OnSpawn(struct ObjectEvent *objEvent, u32 *flags)
{
    ObjectEventUpdateMetatileBehaviors(objEvent);
    GetGroundEffectFlags_Reflection(objEvent, flags);
    GetGroundEffectFlags_TallGrassOnSpawn(objEvent, flags);
    GetGroundEffectFlags_LongGrassOnSpawn(objEvent, flags);
    GetGroundEffectFlags_SandHeap(objEvent, flags);
    GetGroundEffectFlags_ShallowFlowingWater(objEvent, flags);
    GetGroundEffectFlags_ShortGrass(objEvent, flags);
    GetGroundEffectFlags_HotSprings(objEvent, flags);
}

static void GetAllGroundEffectFlags_OnBeginStep(struct ObjectEvent *objEvent, u32 *flags)
{
    ObjectEventUpdateMetatileBehaviors(objEvent);
    GetGroundEffectFlags_Reflection(objEvent, flags);
    GetGroundEffectFlags_TallGrassOnBeginStep(objEvent, flags);
    GetGroundEffectFlags_LongGrassOnBeginStep(objEvent, flags);
    GetGroundEffectFlags_Tracks(objEvent, flags);
    GetGroundEffectFlags_SandHeap(objEvent, flags);
    GetGroundEffectFlags_ShallowFlowingWater(objEvent, flags);
    GetGroundEffectFlags_Puddle(objEvent, flags);
    GetGroundEffectFlags_ShortGrass(objEvent, flags);
    GetGroundEffectFlags_HotSprings(objEvent, flags);
}

static void GetAllGroundEffectFlags_OnFinishStep(struct ObjectEvent *objEvent, u32 *flags)
{
    ObjectEventUpdateMetatileBehaviors(objEvent);
    GetGroundEffectFlags_ShallowFlowingWater(objEvent, flags);
    GetGroundEffectFlags_SandHeap(objEvent, flags);
    GetGroundEffectFlags_Puddle(objEvent, flags);
    GetGroundEffectFlags_Ripple(objEvent, flags);
    GetGroundEffectFlags_ShortGrass(objEvent, flags);
    GetGroundEffectFlags_HotSprings(objEvent, flags);
    GetGroundEffectFlags_Seaweed(objEvent, flags);
    GetGroundEffectFlags_JumpLanding(objEvent, flags);
}

static void ObjectEventUpdateMetatileBehaviors(struct ObjectEvent *objEvent)
{
    objEvent->previousMetatileBehavior = MapGridGetMetatileBehaviorAt(objEvent->previousCoords.x, objEvent->previousCoords.y);
    objEvent->currentMetatileBehavior = MapGridGetMetatileBehaviorAt(objEvent->currentCoords.x, objEvent->currentCoords.y);
}

static void GetGroundEffectFlags_Reflection(struct ObjectEvent *objEvent, u32 *flags)
{
    u32 reflectionFlags[2] = { GROUND_EFFECT_FLAG_REFLECTION, GROUND_EFFECT_FLAG_ICE_REFLECTION };
    u8 type = ObjectEventCheckForReflectiveSurface(objEvent);

    if (type)
    {
        if (!objEvent->hasReflection)
        {
            objEvent->hasReflection = 0;
            objEvent->hasReflection = 1;
            *flags |= reflectionFlags[type - 1];
        }
    }
    else
    {
        objEvent->hasReflection = 0;
    }
}

static void GetGroundEffectFlags_TallGrassOnSpawn(struct ObjectEvent *objEvent, u32 *flags)
{
    if (MetatileBehavior_IsTallGrass(objEvent->currentMetatileBehavior))
        *flags |= GROUND_EFFECT_FLAG_TALL_GRASS_ON_SPAWN;
}

static void GetGroundEffectFlags_TallGrassOnBeginStep(struct ObjectEvent *objEvent, u32 *flags)
{
    if (MetatileBehavior_IsTallGrass(objEvent->currentMetatileBehavior))
        *flags |= GROUND_EFFECT_FLAG_TALL_GRASS_ON_MOVE;
}

static void GetGroundEffectFlags_LongGrassOnSpawn(struct ObjectEvent *objEvent, u32 *flags)
{
    if (MetatileBehavior_IsLongGrass(objEvent->currentMetatileBehavior))
        *flags |= GROUND_EFFECT_FLAG_LONG_GRASS_ON_SPAWN;
}

static void GetGroundEffectFlags_LongGrassOnBeginStep(struct ObjectEvent *objEvent, u32 *flags)
{
    if (MetatileBehavior_IsLongGrass(objEvent->currentMetatileBehavior))
        *flags |= GROUND_EFFECT_FLAG_LONG_GRASS_ON_MOVE;
}

static void GetGroundEffectFlags_Tracks(struct ObjectEvent *objEvent, u32 *flags)
{
    if (MetatileBehavior_IsDeepSand(objEvent->previousMetatileBehavior))
    {
        *flags |= GROUND_EFFECT_FLAG_DEEP_SAND;
    }
    else if (MetatileBehavior_IsSand(objEvent->previousMetatileBehavior)
             || MetatileBehavior_IsFootprints(objEvent->previousMetatileBehavior))
    {
        *flags |= GROUND_EFFECT_FLAG_SAND;
    }
}

static void GetGroundEffectFlags_SandHeap(struct ObjectEvent *objEvent, u32 *flags)
{
    if (MetatileBehavior_IsDeepSand(objEvent->currentMetatileBehavior)
        && MetatileBehavior_IsDeepSand(objEvent->previousMetatileBehavior))
    {
        if (!objEvent->inSandPile)
        {
            objEvent->inSandPile = 0;
            objEvent->inSandPile = 1;
            *flags |= GROUND_EFFECT_FLAG_SAND_PILE;
        }
    }
    else
    {
        objEvent->inSandPile = 0;
    }
}

static void GetGroundEffectFlags_ShallowFlowingWater(struct ObjectEvent *objEvent, u32 *flags)
{
    if ((MetatileBehavior_IsShallowFlowingWater(objEvent->currentMetatileBehavior)
         && MetatileBehavior_IsShallowFlowingWater(objEvent->previousMetatileBehavior))
        || (MetatileBehavior_IsPacifidlogLog(objEvent->currentMetatileBehavior)
            && MetatileBehavior_IsPacifidlogLog(objEvent->previousMetatileBehavior)))
    {
        if (!objEvent->inShallowFlowingWater)
        {
            objEvent->inShallowFlowingWater = 0;
            objEvent->inShallowFlowingWater = 1;
            *flags |= GROUND_EFFECT_FLAG_SHALLOW_FLOWING_WATER;
        }
    }
    else
    {
        objEvent->inShallowFlowingWater = 0;
    }
}

static void GetGroundEffectFlags_Puddle(struct ObjectEvent *objEvent, u32 *flags)
{
    if (MetatileBehavior_IsPuddle(objEvent->currentMetatileBehavior)
        && MetatileBehavior_IsPuddle(objEvent->previousMetatileBehavior))
    {
        *flags |= GROUND_EFFECT_FLAG_PUDDLE;
    }
}

static void GetGroundEffectFlags_Ripple(struct ObjectEvent *objEvent, u32 *flags)
{
    if (MetatileBehavior_HasRipples(objEvent->currentMetatileBehavior))
        *flags |= GROUND_EFFECT_FLAG_RIPPLES;
}

static void GetGroundEffectFlags_ShortGrass(struct ObjectEvent *objEvent, u32 *flags)
{
    if (MetatileBehavior_IsShortGrass(objEvent->currentMetatileBehavior)
        && MetatileBehavior_IsShortGrass(objEvent->previousMetatileBehavior))
    {
        if (!objEvent->inShortGrass)
        {
            objEvent->inShortGrass = 0;
            objEvent->inShortGrass = 1;
            *flags |= GROUND_EFFECT_FLAG_SHORT_GRASS;
        }
    }
    else
    {
        objEvent->inShortGrass = 0;
    }
}

static void GetGroundEffectFlags_HotSprings(struct ObjectEvent *objEvent, u32 *flags)
{
    if (MetatileBehavior_IsHotSprings(objEvent->currentMetatileBehavior)
        && MetatileBehavior_IsHotSprings(objEvent->previousMetatileBehavior))
    {
        if (!objEvent->inHotSprings)
        {
            objEvent->inHotSprings = 0;
            objEvent->inHotSprings = 1;
            *flags |= GROUND_EFFECT_FLAG_HOT_SPRINGS;
        }
    }
    else
    {
        objEvent->inHotSprings = 0;
    }
}

static void GetGroundEffectFlags_Seaweed(struct ObjectEvent *objEvent, u32 *flags)
{
    if (MetatileBehavior_IsSeaweed(objEvent->currentMetatileBehavior))
        *flags |= GROUND_EFFECT_FLAG_SEAWEED;
}

static void GetGroundEffectFlags_JumpLanding(struct ObjectEvent *objEvent, u32 *flags)
{
    typedef bool8 (*MetatileFunc)(u8);

    static const MetatileFunc metatileFuncs[] = {
        MetatileBehavior_IsTallGrass,
        MetatileBehavior_IsLongGrass,
        MetatileBehavior_IsPuddle,
        MetatileBehavior_IsSurfable,
        MetatileBehavior_IsShallowFlowingWater,
        MetatileBehavior_IsATile,
    };

    static const u32 jumpLandingFlags[] = {
        GROUND_EFFECT_FLAG_LAND_IN_TALL_GRASS,
        GROUND_EFFECT_FLAG_LAND_IN_LONG_GRASS,
        GROUND_EFFECT_FLAG_LAND_IN_SHALLOW_WATER,
        GROUND_EFFECT_FLAG_LAND_IN_DEEP_WATER,
        GROUND_EFFECT_FLAG_LAND_IN_SHALLOW_WATER,
        GROUND_EFFECT_FLAG_LAND_ON_NORMAL_GROUND,
    };

    if (objEvent->landingJump && !objEvent->disableJumpLandingGroundEffect)
    {
        u8 i;

        for (i = 0; i < NELEMS(metatileFuncs); i++)
        {
            if (metatileFuncs[i](objEvent->currentMetatileBehavior))
            {
                *flags |= jumpLandingFlags[i];
                return;
            }
        }
    }
}

static u8 ObjectEventCheckForReflectiveSurface(struct ObjectEvent *objEvent)
{
    const struct ObjectEventGraphicsInfo *info = GetObjectEventGraphicsInfo(objEvent->graphicsId);

    // ceil div by tile width?
    s16 width = 1;
    s16 height = 2;
    s16 i;
    s16 j;
    u8 result;
    u8 b;
    s16 one;

#define RETURN_REFLECTION_TYPE_AT(x, y)              \
    b = MapGridGetMetatileBehaviorAt(x, y);          \
    result = GetReflectionTypeByMetatileBehavior(b); \
    if (result != 0)                                 \
        return result;

    for (i = 0, one = 1; i < height; i++)
    {
        RETURN_REFLECTION_TYPE_AT(objEvent->currentCoords.x, objEvent->currentCoords.y + one + i)
        RETURN_REFLECTION_TYPE_AT(objEvent->previousCoords.x, objEvent->previousCoords.y + one + i)
        for (j = 1; j < width; j++)
        {
            RETURN_REFLECTION_TYPE_AT(objEvent->currentCoords.x + j, objEvent->currentCoords.y + one + i)
            RETURN_REFLECTION_TYPE_AT(objEvent->currentCoords.x - j, objEvent->currentCoords.y + one + i)
            RETURN_REFLECTION_TYPE_AT(objEvent->previousCoords.x + j, objEvent->previousCoords.y + one + i)
            RETURN_REFLECTION_TYPE_AT(objEvent->previousCoords.x - j, objEvent->previousCoords.y + one + i)
        }
    }
    return 0;

#undef RETURN_REFLECTION_TYPE_AT
}

static u8 GetReflectionTypeByMetatileBehavior(u32 behavior)
{
    if (MetatileBehavior_IsIce(behavior))
        return 1;
    else if (MetatileBehavior_IsReflective(behavior))
        return 2;
    else
        return 0;
}

u8 GetLedgeJumpDirection(s16 x, s16 y, u8 direction)
{
    static bool8 (*const ledgeBehaviorFuncs[])(u8) = {
        [DIR_SOUTH - 1] = MetatileBehavior_IsJumpSouth,
        [DIR_NORTH - 1] = MetatileBehavior_IsJumpNorth,
        [DIR_WEST - 1]  = MetatileBehavior_IsJumpWest,
        [DIR_EAST - 1]  = MetatileBehavior_IsJumpEast,
    };

    u8 behavior;
    u8 index = direction;

    if (index == DIR_NONE)
        return DIR_NONE;
    else if (index > DIR_EAST)
        index -= DIR_EAST;

    index--;
    behavior = MapGridGetMetatileBehaviorAt(x, y);

    if (ledgeBehaviorFuncs[index](behavior) == TRUE)
        return index + 1;

    return DIR_NONE;
}

static void SetObjectEventSpriteOamTableForLongGrass(struct ObjectEvent *objEvent, struct Sprite *sprite)
{
    if (objEvent->disableCoveringGroundEffects)
        return;

    if (!MetatileBehavior_IsLongGrass(objEvent->currentMetatileBehavior))
        return;

    if (!MetatileBehavior_IsLongGrass(objEvent->previousMetatileBehavior))
        return;

    sprite->subspriteTableNum = 4;

    if (ElevationToPriority(objEvent->previousElevation) == 1)
        sprite->subspriteTableNum = 5;
}

static bool8 IsElevationMismatchAt(u8 elevation, s16 x, s16 y)
{
    u8 mapElevation;

    if (elevation == 0)
        return FALSE;

    mapElevation = MapGridGetElevationAt(x, y);

    if (mapElevation == 0 || mapElevation == 15)
        return FALSE;

    if (mapElevation != elevation)
        return TRUE;

    return FALSE;
}

static const u8 sElevationToSubpriority[] = {
    115, 115, 83, 115, 83, 115, 83, 115, 83, 115, 83, 115, 83, 0, 0, 115
};

static const u8 sElevationToPriority[] = {
    2, 2, 2, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 0, 0, 2
};

// 1 = Above player sprite
// 2 = Below player sprite
static const u8 sElevationToSubspriteTableNum[] = {
    1, 1, 1, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 0, 0, 1,
};

static void UpdateObjectEventElevationAndPriority(struct ObjectEvent *objEvent, struct Sprite *sprite)
{
    if (objEvent->fixedPriority)
        return;

    ObjectEventUpdateElevation(objEvent);

    sprite->subspriteTableNum = sElevationToSubspriteTableNum[objEvent->previousElevation];
    sprite->oam.priority = sElevationToPriority[objEvent->previousElevation];
}

static void InitObjectPriorityByElevation(struct Sprite *sprite, u8 elevation)
{
    sprite->subspriteTableNum = sElevationToSubspriteTableNum[elevation];
    sprite->oam.priority = sElevationToPriority[elevation];
}

u8 ElevationToPriority(u8 elevation)
{
    return sElevationToPriority[elevation];
}

void ObjectEventUpdateElevation(struct ObjectEvent *objEvent)
{
    u8 curElevation = MapGridGetElevationAt(objEvent->currentCoords.x, objEvent->currentCoords.y);
    u8 prevElevation = MapGridGetElevationAt(objEvent->previousCoords.x, objEvent->previousCoords.y);

    if (curElevation == 15 || prevElevation == 15)
        return;

    objEvent->currentElevation = curElevation;

    if (curElevation != 0 && curElevation != 15)
        objEvent->previousElevation = curElevation;
}

void SetObjectSubpriorityByElevation(u8 elevation, struct Sprite *sprite, u8 subpriority)
{
    u16 y;

    y = (sprite->y - sprite->centerToCornerVecY + gSpriteCoordOffsetY + 8) & 0xFF;
    y = (16 - (y >> 4)) << 1;

    sprite->subpriority = sElevationToSubpriority[elevation] + y + subpriority;
}

static void ObjectEventUpdateSubpriority(struct ObjectEvent *objEvent, struct Sprite *sprite)
{
    if (objEvent->fixedPriority)
        return;

    SetObjectSubpriorityByElevation(objEvent->previousElevation, sprite, 1);
}

static bool8 AreElevationsCompatible(u8 a, u8 b)
{
    if (a == 0 || b == 0)
        return TRUE;

    if (a != b)
        return FALSE;

    return TRUE;
}

void GroundEffect_SpawnOnTallGrass(struct ObjectEvent *objEvent, struct Sprite *sprite)
{
    gFieldEffectArguments[0] = objEvent->currentCoords.x;
    gFieldEffectArguments[1] = objEvent->currentCoords.y;
    gFieldEffectArguments[2] = objEvent->previousElevation;
    gFieldEffectArguments[3] = 2;
    gFieldEffectArguments[4] = objEvent->localId << 8 | objEvent->mapNum;
    gFieldEffectArguments[5] = objEvent->mapGroup;
    gFieldEffectArguments[6] = (u8)gSaveBlock1Ptr->location.mapNum << 8 | (u8)gSaveBlock1Ptr->location.mapGroup;
    gFieldEffectArguments[7] = 1;
    FieldEffectStart(FLDEFF_TALL_GRASS);
}

void GroundEffect_StepOnTallGrass(struct ObjectEvent *objEvent, struct Sprite *sprite)
{
    gFieldEffectArguments[0] = objEvent->currentCoords.x;
    gFieldEffectArguments[1] = objEvent->currentCoords.y;
    gFieldEffectArguments[2] = objEvent->previousElevation;
    gFieldEffectArguments[3] = 2;
    gFieldEffectArguments[4] = objEvent->localId << 8 | objEvent->mapNum;
    gFieldEffectArguments[5] = objEvent->mapGroup;
    gFieldEffectArguments[6] = (u8)gSaveBlock1Ptr->location.mapNum << 8 | (u8)gSaveBlock1Ptr->location.mapGroup;
    gFieldEffectArguments[7] = 0;
    FieldEffectStart(FLDEFF_TALL_GRASS);
}

void GroundEffect_SpawnOnLongGrass(struct ObjectEvent *objEvent, struct Sprite *sprite)
{
    gFieldEffectArguments[0] = objEvent->currentCoords.x;
    gFieldEffectArguments[1] = objEvent->currentCoords.y;
    gFieldEffectArguments[2] = objEvent->previousElevation;
    gFieldEffectArguments[3] = 2;
    gFieldEffectArguments[4] = objEvent->localId << 8 | objEvent->mapNum;
    gFieldEffectArguments[5] = objEvent->mapGroup;
    gFieldEffectArguments[6] = (u8)gSaveBlock1Ptr->location.mapNum << 8 | (u8)gSaveBlock1Ptr->location.mapGroup;
    gFieldEffectArguments[7] = 1;
    FieldEffectStart(FLDEFF_LONG_GRASS);
}

void GroundEffect_StepOnLongGrass(struct ObjectEvent *objEvent, struct Sprite *sprite)
{
    gFieldEffectArguments[0] = objEvent->currentCoords.x;
    gFieldEffectArguments[1] = objEvent->currentCoords.y;
    gFieldEffectArguments[2] = objEvent->previousElevation;
    gFieldEffectArguments[3] = 2;
    gFieldEffectArguments[4] = (objEvent->localId << 8) | objEvent->mapNum;
    gFieldEffectArguments[5] = objEvent->mapGroup;
    gFieldEffectArguments[6] = (u8)gSaveBlock1Ptr->location.mapNum << 8 | (u8)gSaveBlock1Ptr->location.mapGroup;
    gFieldEffectArguments[7] = 0;
    FieldEffectStart(FLDEFF_LONG_GRASS);
}

void GroundEffect_WaterReflection(struct ObjectEvent *objEvent, struct Sprite *sprite)
{
    SetUpReflection(objEvent, sprite, 0);
}

void GroundEffect_IceReflection(struct ObjectEvent *objEvent, struct Sprite *sprite)
{
    SetUpReflection(objEvent, sprite, 1);
}

void GroundEffect_FlowingWater(struct ObjectEvent *objEvent, struct Sprite *sprite)
{
    StartFieldEffectForObjectEvent(FLDEFF_FEET_IN_FLOWING_WATER, objEvent);
}

static void (*const sGroundEffectTracksFuncs[])(struct ObjectEvent *objEvent, struct Sprite *sprite, u8 a) = {
    DoTracksGroundEffect_None,
    DoTracksGroundEffect_Footprints,
    DoTracksGroundEffect_BikeTireTracks,
};

void GroundEffect_SandTracks(struct ObjectEvent *objEvent, struct Sprite *sprite)
{
    const struct ObjectEventGraphicsInfo *info = GetObjectEventGraphicsInfo(objEvent->graphicsId);
    sGroundEffectTracksFuncs[info->tracks](objEvent, sprite, 0);
}

void GroundEffect_DeepSandTracks(struct ObjectEvent *objEvent, struct Sprite *sprite)
{
    const struct ObjectEventGraphicsInfo *info = GetObjectEventGraphicsInfo(objEvent->graphicsId);
    sGroundEffectTracksFuncs[info->tracks](objEvent, sprite, 1);
}

static void DoTracksGroundEffect_None(struct ObjectEvent *objEvent, struct Sprite *sprite, u8 a)
{
}

static void DoTracksGroundEffect_Footprints(struct ObjectEvent *objEvent, struct Sprite *sprite, u8 a)
{
    // First half-word is a Field Effect script id. (gFieldEffectScriptPointers)
    u16 sandFootprints_FieldEffectData[2] = {
        FLDEFF_SAND_FOOTPRINTS,
        FLDEFF_DEEP_SAND_FOOTPRINTS
    };

    gFieldEffectArguments[0] = objEvent->previousCoords.x;
    gFieldEffectArguments[1] = objEvent->previousCoords.y;
    gFieldEffectArguments[2] = 149;
    gFieldEffectArguments[3] = 2;
    gFieldEffectArguments[4] = objEvent->facingDirection;
    FieldEffectStart(sandFootprints_FieldEffectData[a]);
}

static void DoTracksGroundEffect_BikeTireTracks(struct ObjectEvent *objEvent, struct Sprite *sprite, u8 a)
{
    //  Specifies which bike track shape to show next.
    //  For example, when the bike turns from up to right, it will show
    //  a track that curves to the right.
    //  Each 4-byte row corresponds to the initial direction of the bike, and
    //  each byte in that row is for the next direction of the bike in the order
    //  of down, up, left, right.
    static const u8 bikeTireTracks_Transitions[4][4] = {
        1, 2, 7, 8,
        1, 2, 6, 5,
        5, 8, 3, 4,
        6, 7, 3, 4,
    };

    if (objEvent->currentCoords.x != objEvent->previousCoords.x || objEvent->currentCoords.y != objEvent->previousCoords.y)
    {
        gFieldEffectArguments[0] = objEvent->previousCoords.x;
        gFieldEffectArguments[1] = objEvent->previousCoords.y;
        gFieldEffectArguments[2] = 149;
        gFieldEffectArguments[3] = 2;
        gFieldEffectArguments[4] =
            bikeTireTracks_Transitions[objEvent->previousMovementDirection][objEvent->facingDirection - 5];
        FieldEffectStart(FLDEFF_BIKE_TIRE_TRACKS);
    }
}

void GroundEffect_Ripple(struct ObjectEvent *objEvent, struct Sprite *sprite)
{
    DoRippleFieldEffect(objEvent, sprite);
}

void GroundEffect_StepOnPuddle(struct ObjectEvent *objEvent, struct Sprite *sprite)
{
    StartFieldEffectForObjectEvent(FLDEFF_SPLASH, objEvent);
}

void GroundEffect_SandHeap(struct ObjectEvent *objEvent, struct Sprite *sprite)
{
    StartFieldEffectForObjectEvent(FLDEFF_SAND_PILE, objEvent);
}

void GroundEffect_JumpOnTallGrass(struct ObjectEvent *objEvent, struct Sprite *sprite)
{
    u8 spriteId;

    gFieldEffectArguments[0] = objEvent->currentCoords.x;
    gFieldEffectArguments[1] = objEvent->currentCoords.y;
    gFieldEffectArguments[2] = objEvent->previousElevation;
    gFieldEffectArguments[3] = 2;
    FieldEffectStart(FLDEFF_JUMP_TALL_GRASS);

    spriteId = FindTallGrassFieldEffectSpriteId(
        objEvent->localId,
        objEvent->mapNum,
        objEvent->mapGroup,
        objEvent->currentCoords.x,
        objEvent->currentCoords.y);

    if (spriteId == MAX_SPRITES)
        GroundEffect_SpawnOnTallGrass(objEvent, sprite);
}

void GroundEffect_JumpOnLongGrass(struct ObjectEvent *objEvent, struct Sprite *sprite)
{
    gFieldEffectArguments[0] = objEvent->currentCoords.x;
    gFieldEffectArguments[1] = objEvent->currentCoords.y;
    gFieldEffectArguments[2] = objEvent->previousElevation;
    gFieldEffectArguments[3] = 2;
    FieldEffectStart(FLDEFF_JUMP_LONG_GRASS);
}

void GroundEffect_JumpOnShallowWater(struct ObjectEvent *objEvent, struct Sprite *sprite)
{
    gFieldEffectArguments[0] = objEvent->currentCoords.x;
    gFieldEffectArguments[1] = objEvent->currentCoords.y;
    gFieldEffectArguments[2] = objEvent->previousElevation;
    gFieldEffectArguments[3] = sprite->oam.priority;
    FieldEffectStart(FLDEFF_JUMP_SMALL_SPLASH);
}

void GroundEffect_JumpOnWater(struct ObjectEvent *objEvent, struct Sprite *sprite)
{
    gFieldEffectArguments[0] = objEvent->currentCoords.x;
    gFieldEffectArguments[1] = objEvent->currentCoords.y;
    gFieldEffectArguments[2] = objEvent->previousElevation;
    gFieldEffectArguments[3] = sprite->oam.priority;
    FieldEffectStart(FLDEFF_JUMP_BIG_SPLASH);
}

void GroundEffect_JumpLandingDust(struct ObjectEvent *objEvent, struct Sprite *sprite)
{
    gFieldEffectArguments[0] = objEvent->currentCoords.x;
    gFieldEffectArguments[1] = objEvent->currentCoords.y;
    gFieldEffectArguments[2] = objEvent->previousElevation;
    gFieldEffectArguments[3] = sprite->oam.priority;
    FieldEffectStart(FLDEFF_DUST);
}

void GroundEffect_ShortGrass(struct ObjectEvent *objEvent, struct Sprite *sprite)
{
    StartFieldEffectForObjectEvent(FLDEFF_SHORT_GRASS, objEvent);
}

void GroundEffect_HotSprings(struct ObjectEvent *objEvent, struct Sprite *sprite)
{
    StartFieldEffectForObjectEvent(FLDEFF_HOT_SPRINGS_WATER, objEvent);
}

void GroundEffect_Seaweed(struct ObjectEvent *objEvent, struct Sprite *sprite)
{
    gFieldEffectArguments[0] = objEvent->currentCoords.x;
    gFieldEffectArguments[1] = objEvent->currentCoords.y;
    FieldEffectStart(FLDEFF_BUBBLES);
}

static void (*const sGroundEffectFuncs[])(struct ObjectEvent *objEvent, struct Sprite *sprite) = {
    GroundEffect_SpawnOnTallGrass,
    GroundEffect_StepOnTallGrass,
    GroundEffect_SpawnOnLongGrass,
    GroundEffect_StepOnLongGrass,
    GroundEffect_WaterReflection,
    GroundEffect_IceReflection,
    GroundEffect_FlowingWater,
    GroundEffect_SandTracks,
    GroundEffect_DeepSandTracks,
    GroundEffect_Ripple,
    GroundEffect_StepOnPuddle,
    GroundEffect_SandHeap,
    GroundEffect_JumpOnTallGrass,
    GroundEffect_JumpOnLongGrass,
    GroundEffect_JumpOnShallowWater,
    GroundEffect_JumpOnWater,
    GroundEffect_JumpLandingDust,
    GroundEffect_ShortGrass,
    GroundEffect_HotSprings,
    GroundEffect_Seaweed
};

static void DoFlaggedGroundEffects(struct ObjectEvent *objEvent, struct Sprite *sprite, u32 flags)
{
    u8 i;

    if (objEvent->localId == LOCALID_CAMERA && objEvent->invisible)
        return;

    for (i = 0; i < NELEMS(sGroundEffectFuncs); i++, flags >>= 1)
        if (flags & 1)
            sGroundEffectFuncs[i](objEvent, sprite);
}

void filters_out_some_ground_effects(struct ObjectEvent *objEvent, u32 *flags)
{
    if (objEvent->disableCoveringGroundEffects)
    {
        objEvent->inShortGrass = 0;
        objEvent->inSandPile = 0;
        objEvent->inShallowFlowingWater = 0;
        objEvent->inHotSprings = 0;
        *flags &= ~(GROUND_EFFECT_FLAG_HOT_SPRINGS
                  | GROUND_EFFECT_FLAG_SHORT_GRASS
                  | GROUND_EFFECT_FLAG_SAND_PILE
                  | GROUND_EFFECT_FLAG_SHALLOW_FLOWING_WATER
                  | GROUND_EFFECT_FLAG_TALL_GRASS_ON_MOVE);
    }
}

void FilterOutStepOnPuddleGroundEffectIfJumping(struct ObjectEvent *objEvent, u32 *flags)
{
    if (objEvent->landingJump)
        *flags &= ~GROUND_EFFECT_FLAG_PUDDLE;
}

static void DoGroundEffects_OnSpawn(struct ObjectEvent *objEvent, struct Sprite *sprite)
{
    u32 flags;

    if (objEvent->triggerGroundEffectsOnMove)
    {
        flags = 0;
        UpdateObjectEventElevationAndPriority(objEvent, sprite);
        GetAllGroundEffectFlags_OnSpawn(objEvent, &flags);
        SetObjectEventSpriteOamTableForLongGrass(objEvent, sprite);
        DoFlaggedGroundEffects(objEvent, sprite, flags);
        objEvent->triggerGroundEffectsOnMove = 0;
        objEvent->disableCoveringGroundEffects = 0;
    }
}

static void DoGroundEffects_OnBeginStep(struct ObjectEvent *objEvent, struct Sprite *sprite)
{
    u32 flags;

    if (objEvent->triggerGroundEffectsOnMove)
    {
        flags = 0;
        UpdateObjectEventElevationAndPriority(objEvent, sprite);
        GetAllGroundEffectFlags_OnBeginStep(objEvent, &flags);
        SetObjectEventSpriteOamTableForLongGrass(objEvent, sprite);
        filters_out_some_ground_effects(objEvent, &flags);
        DoFlaggedGroundEffects(objEvent, sprite, flags);
        objEvent->triggerGroundEffectsOnMove = 0;
        objEvent->disableCoveringGroundEffects = 0;
    }
}

static void DoGroundEffects_OnFinishStep(struct ObjectEvent *objEvent, struct Sprite *sprite)
{
    u32 flags;

    if (objEvent->triggerGroundEffectsOnStop)
    {
        flags = 0;
        UpdateObjectEventElevationAndPriority(objEvent, sprite);
        GetAllGroundEffectFlags_OnFinishStep(objEvent, &flags);
        SetObjectEventSpriteOamTableForLongGrass(objEvent, sprite);
        FilterOutStepOnPuddleGroundEffectIfJumping(objEvent, &flags);
        DoFlaggedGroundEffects(objEvent, sprite, flags);
        objEvent->triggerGroundEffectsOnStop = 0;
        objEvent->landingJump = 0;
    }
}

bool8 FreezeObjectEvent(struct ObjectEvent *objectEvent)
{
    if (objectEvent->heldMovementActive || objectEvent->frozen)
        return TRUE;
    objectEvent->frozen = TRUE;
    objectEvent->spriteAnimPausedBackup = gSprites[objectEvent->spriteId].animPaused;
    objectEvent->spriteAffineAnimPausedBackup = gSprites[objectEvent->spriteId].affineAnimPaused;
    gSprites[objectEvent->spriteId].animPaused = TRUE;
    gSprites[objectEvent->spriteId].affineAnimPaused = TRUE;
    return FALSE;
}

void FreezeObjectEvents(void)
{
    u8 i;
    for (i = 0; i < OBJECT_EVENTS_COUNT; i++)
    {
        if (gObjectEvents[i].active && i != gPlayerAvatar.objectEventId)
            FreezeObjectEvent(&gObjectEvents[i]);
    }
}

void FreezeObjectEventsExceptOne(u8 noFreeze)
{
    u8 i;
    for (i = 0; i < OBJECT_EVENTS_COUNT; i++)
    {
        if (i != noFreeze && gObjectEvents[i].active && i != gPlayerAvatar.objectEventId)
            FreezeObjectEvent(&gObjectEvents[i]);
    }
}

void UnfreezeObjectEvent(struct ObjectEvent *objectEvent)
{
    if (objectEvent->active && objectEvent->frozen)
    {
        objectEvent->frozen = FALSE;
        gSprites[objectEvent->spriteId].animPaused = objectEvent->spriteAnimPausedBackup;
        gSprites[objectEvent->spriteId].affineAnimPaused = objectEvent->spriteAffineAnimPausedBackup;
    }
}

void UnfreezeObjectEvents(void)
{
    u8 i;
    for (i = 0; i < OBJECT_EVENTS_COUNT; i++)
    {
        if (gObjectEvents[i].active)
            UnfreezeObjectEvent(&gObjectEvents[i]);
    }
}

#define tDirection data[3]
#define tSpeed     data[4]
#define tStepNo    data[5]

static void Step1(struct Sprite *sprite, u8 direction)
{
    sprite->x += sDirectionToVectors[direction].x;
    sprite->y += sDirectionToVectors[direction].y;
}

static void Step2(struct Sprite *sprite, u8 direction)
{
    sprite->x += 2 * (u16)sDirectionToVectors[direction].x;
    sprite->y += 2 * (u16)sDirectionToVectors[direction].y;
}

static void Step3(struct Sprite *sprite, u8 direction)
{
    sprite->x += 2 * (u16)sDirectionToVectors[direction].x + (u16)sDirectionToVectors[direction].x;
    sprite->y += 2 * (u16)sDirectionToVectors[direction].y + (u16)sDirectionToVectors[direction].y;
}

static void Step4(struct Sprite *sprite, u8 direction)
{
    sprite->x += 4 * (u16)sDirectionToVectors[direction].x;
    sprite->y += 4 * (u16)sDirectionToVectors[direction].y;
}

static void Step8(struct Sprite *sprite, u8 direction)
{
    sprite->x += 8 * (u16)sDirectionToVectors[direction].x;
    sprite->y += 8 * (u16)sDirectionToVectors[direction].y;
}

void SetSpriteDataForNormalStep(struct Sprite *sprite, u8 direction, u8 speed)
{
    sprite->tDirection = direction;
    sprite->tSpeed = speed;
    sprite->tStepNo = 0;
}

typedef void (*SpriteStepFunc)(struct Sprite *sprite, u8 direction);

static const SpriteStepFunc sSpeedNormalStepFuncs[] = {
    Step1,
    Step1,
    Step1,
    Step1,
    Step1,
    Step1,
    Step1,
    Step1,
    Step1,
    Step1,
    Step1,
    Step1,
    Step1,
    Step1,
    Step1,
    Step1
};

static const SpriteStepFunc sSpeedFast1StepFuncs[] = {
    Step2,
    Step2,
    Step2,
    Step2,
    Step2,
    Step2,
    Step2,
    Step2
};

static const SpriteStepFunc sSpeedFast2StepFuncs[] = {
    Step2,
    Step3,
    Step3,
    Step2,
    Step3,
    Step3
};

static const SpriteStepFunc sSpeedFasterStepFuncs[] = {
    Step4,
    Step4,
    Step4,
    Step4
};

static const SpriteStepFunc sSpeedFastestStepFuncs[] = {
    Step8,
    Step8
};

static const SpriteStepFunc *const sNpcStepFuncTables[] = {
    [MOVE_SPEED_NORMAL]  = sSpeedNormalStepFuncs,
    [MOVE_SPEED_FAST_1]  = sSpeedFast1StepFuncs,
    [MOVE_SPEED_FAST_2]  = sSpeedFast2StepFuncs,
    [MOVE_SPEED_FASTER]  = sSpeedFasterStepFuncs,
    [MOVE_SPEED_FASTEST] = sSpeedFastestStepFuncs,
};

static const s16 sStepTimes[] = {
    [MOVE_SPEED_NORMAL]  = NELEMS(sSpeedNormalStepFuncs),
    [MOVE_SPEED_FAST_1]  = NELEMS(sSpeedFast1StepFuncs),
    [MOVE_SPEED_FAST_2]  = NELEMS(sSpeedFast2StepFuncs),
    [MOVE_SPEED_FASTER]  = NELEMS(sSpeedFasterStepFuncs),
    [MOVE_SPEED_FASTEST] = NELEMS(sSpeedFastestStepFuncs),
};

bool8 NpcTakeStep(struct Sprite *sprite)
{
    if (sprite->tStepNo >= sStepTimes[sprite->tSpeed])
        return FALSE;

    sNpcStepFuncTables[sprite->tSpeed][sprite->tStepNo](sprite, sprite->tDirection);

    sprite->tStepNo++;

    if (sprite->tStepNo < sStepTimes[sprite->tSpeed])
        return FALSE;

    return TRUE;
}

#undef tSpeed

#define tDelay     data[4]

void SetWalkSlowerSpriteData(struct Sprite *sprite, u8 direction)
{
    sprite->tDirection = direction;
    sprite->tDelay = 0;
    sprite->tStepNo = 0;
}

bool8 UpdateWalkSlowerAnim(struct Sprite *sprite)
{
    if (!(sprite->tDelay & 1))
    {
        Step1(sprite, sprite->tDirection);
        sprite->tStepNo++;
    }

    sprite->tDelay++;

    if (sprite->tStepNo > 15)
        return TRUE;
    else
        return FALSE;
}

// SetWalkSlowSpriteData, SetWalkSlowerSpriteData, SetWalkSlowestSpriteData,
// and SetRunSlowSpriteData are functionally equivalent
void SetWalkSlowSpriteData(struct Sprite *sprite, u8 direction)
{
    sprite->tDirection = direction;
    sprite->tDelay = 0;
    sprite->tStepNo = 0;
}

bool8 UpdateWalkSlowAnim(struct Sprite *sprite)
{
    if (++sprite->tDelay < 3)
    {
        Step1(sprite, sprite->tDirection);
        sprite->tStepNo++;
    }
    else
        sprite->tDelay = 0;

    if (sprite->tStepNo > 15)
        return TRUE;
    else
        return FALSE;
}

void SetWalkSlowestSpriteData(struct Sprite *sprite, u8 direction)
{
    sprite->tDirection = direction;
    sprite->tDelay = 0;
    sprite->tStepNo = 0;
}

bool8 UpdateWalkSlowestAnim(struct Sprite *sprite)
{
    if (++sprite->tDelay > 9)
    {
        sprite->tDelay = 0;
        Step1(sprite, sprite->tDirection);
        sprite->tStepNo++;
    }

    if (sprite->tStepNo > 15)
        return TRUE;
    else
        return FALSE;
}

void SetRunSlowSpriteData(struct Sprite *sprite, u8 direction)
{
    sprite->tDirection = direction;
    sprite->tDelay = 0;
    sprite->tStepNo = 0;
}

bool8 UpdateRunSlowAnim(struct Sprite *sprite)
{
    if ((++sprite->tDelay) & 1)
    {
        Step1(sprite, sprite->tDirection);
        sprite->tStepNo++;
    }
    else
    {
        Step2(sprite, sprite->tDirection);
        sprite->tStepNo += 2;
    }

    if (sprite->tStepNo > 15)
        return TRUE;
    else
        return FALSE;
}

#undef tStepNo
#undef tDelay

static const s8 sJumpY_High[] = {
     -4,  -6,  -8, -10, -11, -12, -12, -12,
    -11, -10,  -9,  -8,  -6,  -4,   0,   0
};

static const s8 sJumpY_Low[] = {
    0,   -2,  -3,  -4,  -5,  -6,  -6,  -6,
    -5,  -5,  -4,  -3,  -2,   0,   0,   0
};

static const s8 sJumpY_Normal[] = {
    -2,  -4,  -6,  -8,  -9, -10, -10, -10,
    -9,  -8,  -6,  -5,  -3,  -2,   0,   0
};

#define sJumpDistance  data[4]
#define sJumpType      data[5]
#define sTimer         data[6]

static const s8 *const sJumpYTable[] = {
    [JUMP_TYPE_HIGH]   = sJumpY_High,
    [JUMP_TYPE_LOW]    = sJumpY_Low,
    [JUMP_TYPE_NORMAL] = sJumpY_Normal,
};

static s16 GetJumpY(s16 i, u8 type)
{
    return sJumpYTable[type][i];
}

void SetJumpSpriteData(struct Sprite *sprite, u8 direction, u8 distance, u8 type)
{
    sprite->tDirection = direction;
    sprite->sJumpDistance = distance;
    sprite->sJumpType = type;
    sprite->sTimer = 0;
}

u8 DoJumpSpriteMovement(struct Sprite *sprite)
{
    s16 distanceToTime[] = {
        [JUMP_DISTANCE_IN_PLACE] = 16,
        [JUMP_DISTANCE_NORMAL]   = 16,
        [JUMP_DISTANCE_FAR]      = 32,
    };
    u8 distanceToShift[] = {
        [JUMP_DISTANCE_IN_PLACE] = 0,
        [JUMP_DISTANCE_NORMAL]   = 0,
        [JUMP_DISTANCE_FAR]      = 1,
    };
    u8 jumpPhase = 0;

    if (sprite->sJumpDistance != JUMP_DISTANCE_IN_PLACE)
        Step1(sprite, sprite->tDirection);

    sprite->y2 = GetJumpY(sprite->sTimer >> distanceToShift[sprite->sJumpDistance], sprite->sJumpType);

    sprite->sTimer++;

    if (sprite->sTimer == (distanceToTime[sprite->sJumpDistance] >> 1))
        jumpPhase = JUMP_HALFWAY;

    if (sprite->sTimer >= distanceToTime[sprite->sJumpDistance])
    {
        sprite->y2 = 0;
        jumpPhase = JUMP_FINISHED;
    }

    return jumpPhase;
}

u8 DoJumpSpecialSpriteMovement(struct Sprite *sprite)
{
    s16 duration[3] = {0x20, 0x20, 0x40};
    u8 shifts[3] = {1, 1, 2};
    u8 jumpPhase = 0;

    if (sprite->sJumpDistance != JUMP_DISTANCE_IN_PLACE && !(sprite->sTimer & 1))
        Step1(sprite, sprite->tDirection);

    sprite->y2 = GetJumpY(sprite->sTimer >> shifts[sprite->sJumpDistance], sprite->sJumpType);

    sprite->sTimer++;

    if (sprite->sTimer == (duration[sprite->sJumpDistance] >> 1))
        jumpPhase = JUMP_HALFWAY;

    if (sprite->sTimer >= duration[sprite->sJumpDistance])
    {
        sprite->y2 = 0;
        jumpPhase = JUMP_FINISHED;
    }

    return jumpPhase;
}

#undef sTimer
#undef sJumpType
#undef sJumpDistance
#undef tDirection

#define tDelay data[3]

void SetMovementDelay(struct Sprite *sprite, s16 delay)
{
    sprite->tDelay = delay;
}

bool8 WaitForMovementDelay(struct Sprite *sprite)
{
    sprite->tDelay--;

    if (sprite->tDelay == 0)
        return TRUE;
    else
        return FALSE;
}

#undef tDelay

void SetAndStartSpriteAnim(struct Sprite *sprite, u8 animNum, u8 animCmdIndex)
{
    sprite->animNum = animNum;
    sprite->animPaused = FALSE;
    SeekSpriteAnim(sprite, animCmdIndex);
}

bool8 SpriteAnimEnded(struct Sprite *sprite)
{
    if (sprite->animEnded)
        return TRUE;
    else
        return FALSE;
}

void UpdateObjectEventSpriteInvisibility(struct Sprite *sprite, bool8 invisible)
{
    u16 x, y;
    s16 x2, y2;

    sprite->invisible = invisible;

    if (sprite->coordOffsetEnabled)
    {
        x = sprite->x + sprite->x2 + sprite->centerToCornerVecX + gSpriteCoordOffsetX;
        y = sprite->y + sprite->y2 + sprite->centerToCornerVecY + gSpriteCoordOffsetY;
    }
    else
    {
        x = sprite->x + sprite->x2 + sprite->centerToCornerVecX;
        y = sprite->y + sprite->y2 + sprite->centerToCornerVecY;
    }

    x2 = x - (sprite->centerToCornerVecX >> 1);
    y2 = y - (sprite->centerToCornerVecY >> 1);

    if ((s16)x >= DISPLAY_WIDTH + 16 || x2 < -16)
        sprite->invisible = TRUE;
    if ((s16)y >= DISPLAY_HEIGHT + 16 || y2 < -16)
        sprite->invisible = TRUE;
}

#define sInvisible     data[2]
#define sAnimNum       data[3]
#define sAnimState     data[4]

void SpriteCB_VirtualObject(struct Sprite *sprite)
{
    VirtualObject_UpdateAnim(sprite);
    SetObjectSubpriorityByElevation(sprite->sVirtualObjElev, sprite, 1);
    UpdateObjectEventSpriteInvisibility(sprite, sprite->sInvisible);
}

// Unused
static void DestroyVirtualObjects(void)
{
    s32 i;
    for (i = 0; i < MAX_SPRITES; i++)
    {
        struct Sprite *sprite = &gSprites[i];
        if (sprite->inUse && sprite->callback == SpriteCB_VirtualObject)
            DestroySprite(sprite);
    }
}

static int GetVirtualObjectSpriteId(u8 virtualObjId)
{
    int i;
    for (i = 0; i < MAX_SPRITES; i++)
    {
        struct Sprite *sprite = &gSprites[i];
        if (sprite->inUse && sprite->callback == SpriteCB_VirtualObject && (u8)sprite->sVirtualObjId == virtualObjId)
            return i;
    }
    return MAX_SPRITES;
}

void TurnVirtualObject(u8 virtualObjId, u8 direction)
{
    u8 animNum;
    u8 spriteId = GetVirtualObjectSpriteId(virtualObjId);
    if (spriteId != MAX_SPRITES)
    {
        struct Sprite *sprite = &gSprites[spriteId];
        StartSpriteAnim(sprite, GetFaceDirectionAnimNum(direction));
    }
}

void SetVirtualObjectGraphics(u8 virtualObjId, u8 direction)
{
    int spriteId = GetVirtualObjectSpriteId(virtualObjId);
    if (spriteId != MAX_SPRITES)
    {
        struct Sprite *sprite = &gSprites[spriteId];
        const struct ObjectEventGraphicsInfo *info = GetObjectEventGraphicsInfo(direction);
        u16 baseBlock = sprite->oam.tileNum;
        sprite->oam = *info->oam;
        sprite->oam.tileNum = baseBlock;
        sprite->oam.paletteNum = info->paletteSlot;
        sprite->images = info->images;
        if (info->subspriteTables == NULL)
        {
            sprite->subspriteTables = NULL;
            sprite->subspriteTableNum = 0;
            sprite->subspriteMode = SUBSPRITES_OFF;
        }
        else
        {
            SetSubspriteTables(sprite, info->subspriteTables);
            sprite->subspriteMode = SUBSPRITES_IGNORE_PRIORITY;
        }
        StartSpriteAnim(sprite, 0);
    }
}

void SetVirtualObjectInvisibility(u8 virtualObjId, bool32 invisible)
{
    u8 spriteId = GetVirtualObjectSpriteId(virtualObjId);
    if (spriteId != MAX_SPRITES)
    {
        if (invisible)
            gSprites[spriteId].sInvisible = TRUE;
        else
            gSprites[spriteId].sInvisible = FALSE;
    }
}

bool32 IsVirtualObjectInvisible(u8 virtualObjId)
{
    u8 spriteId = GetVirtualObjectSpriteId(virtualObjId);
    if (spriteId == MAX_SPRITES)
        return FALSE;
    return gSprites[spriteId].sInvisible == TRUE;
}

void SetVirtualObjectSpriteAnim(u8 virtualObjId, u8 animNo)
{
    u8 spriteId = GetVirtualObjectSpriteId(virtualObjId);
    if (spriteId != MAX_SPRITES)
    {
        gSprites[spriteId].sAnimNum = animNo;
        gSprites[spriteId].sAnimState = 0;
    }
}

static void MoveUnionRoomObjectUp(struct Sprite *sprite)
{
    switch (sprite->sAnimState)
    {
    case 0:
        sprite->y2 = 0;
        sprite->sAnimState++;
        // fallthrough
    case 1:
        if ((sprite->y2 -= 8) == -DISPLAY_HEIGHT)
        {
            sprite->y2 = 0;
            sprite->sInvisible = TRUE;
            sprite->sAnimNum = 0;
            sprite->sAnimState = 0;
        }
        break;
    }
}

static void MoveUnionRoomObjectDown(struct Sprite *sprite)
{
    switch (sprite->sAnimState)
    {
    case 0:
        sprite->y2 = -DISPLAY_HEIGHT;
        sprite->sAnimState++;
        // fallthrough
    case 1:
        if ((sprite->y2 += 8) == 0)
        {
            sprite->sAnimNum = 0;
            sprite->sAnimState = 0;
        }
        break;
    }
}

static void VirtualObject_UpdateAnim(struct Sprite *sprite)
{
    switch (sprite->sAnimNum)
    {
    case UNION_ROOM_SPAWN_NONE:
        break;
    case UNION_ROOM_SPAWN_IN:
        MoveUnionRoomObjectDown(sprite);
        break;
    case UNION_ROOM_SPAWN_OUT:
        MoveUnionRoomObjectUp(sprite);
        break;
    default:
        sprite->sAnimNum = 0;
        AGB_ASSERT_EX(0, ABSPATH("evobjmv.c"), 13331);
    }
}

bool32 IsVirtualObjectAnimating(u8 virtualObjId)
{
    u8 spriteId = GetVirtualObjectSpriteId(virtualObjId);
    if (spriteId == MAX_SPRITES)
        return FALSE;
    if (gSprites[spriteId].sAnimNum)
        return TRUE;
    else
        return FALSE;
}

#undef sVirtualObjId
#undef sVirtualObjElev
#undef sInvisible
#undef sAnimNum
#undef sAnimState

u32 StartFieldEffectForObjectEvent(u8 fieldEffectId, struct ObjectEvent *objectEvent)
{
    ObjectEventGetLocalIdAndMap(objectEvent, (u8 *)&gFieldEffectArguments[0], (u8 *)&gFieldEffectArguments[1], (u8 *)&gFieldEffectArguments[2]);
    return FieldEffectStart(fieldEffectId);
}

void DoShadowFieldEffect(struct ObjectEvent *objectEvent)
{
    if (!objectEvent->hasShadow)
    {
        objectEvent->hasShadow = TRUE;
        StartFieldEffectForObjectEvent(FLDEFF_SHADOW, objectEvent);
    }
}

static void DoRippleFieldEffect(struct ObjectEvent *objectEvent, struct Sprite *sprite)
{
    const struct ObjectEventGraphicsInfo *graphicsInfo = GetObjectEventGraphicsInfo(objectEvent->graphicsId);
    gFieldEffectArguments[0] = sprite->x;
    gFieldEffectArguments[1] = sprite->y + (graphicsInfo->height >> 1) - 2;
    gFieldEffectArguments[2] = 151;
    gFieldEffectArguments[3] = 3;
    FieldEffectStart(FLDEFF_RIPPLE);
}
