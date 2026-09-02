#include "global.h"

const u32 gBattleInterface_Textbox_Gfx[] = INCBIN_U32("assets/graphics.bin", 0x6BAF8, 0x4D8);
const u32 gBattleInterface_Textbox_Pal[] = INCBIN_U32("assets/graphics.bin", 0x6BFD0, 0x44);
const u32 gBattleInterface_Textbox_Tilemap[] = INCBIN_U32("assets/graphics.bin", 0x6C014, 0x22C);

const u32 gMonFrontPic_CircledQuestionMark[] = INCBIN_U32("assets/graphics.bin", 0x6C240, 0x244);
const u32 gMonBackPic_CircledQuestionMark[] = INCBIN_U32("assets/graphics.bin", 0x6C484, 0x244);
const u32 gMonPalette_CircledQuestionMark[] = INCBIN_U32("assets/graphics.bin", 0x6C6C8, 0x18);
const u32 gMonShinyPalette_CircledQuestionMark[] = INCBIN_U32("assets/graphics.bin", 0x6C6E0, 0x18);

// From Ruby.
const u32 gUnusedGfx_OldCharmap[] = INCBIN_U32("assets/graphics.bin", 0x6C6F8, 0x7D8);
const u32 gUnusedTimemap_OldCharmap[] = INCBIN_U32("assets/graphics.bin", 0x6CED0, 0x22C);
const u32 gUnusedPal_OldCharmap[] = INCBIN_U32("assets/graphics.bin", 0x6D0FC, 0x28);

const u32 gSmokescreenImpactTiles[] = INCBIN_U32("assets/graphics.bin", 0x6D124, 0xE0);
const u32 gSmokescreenImpactPalette[] = INCBIN_U32("assets/graphics.bin", 0x6D204, 0x18);

// ===== BEGIN src/data/graphics/interface_pokeballs.h =====
const u32 gBallGfx_Poke[] = INCBIN_U32("assets/graphics.bin", 0x6D21C, 0xBC);
const u32 gBallPal_Poke[] = INCBIN_U32("assets/graphics.bin", 0x6D2D8, 0x20);

const u32 gBallGfx_Great[] = INCBIN_U32("assets/graphics.bin", 0x6D2F8, 0xBC);
const u32 gBallPal_Great[] = INCBIN_U32("assets/graphics.bin", 0x6D3B4, 0x24);

const u32 gBallGfx_Safari[] = INCBIN_U32("assets/graphics.bin", 0x6D3D8, 0xC4);
const u32 gBallPal_Safari[] = INCBIN_U32("assets/graphics.bin", 0x6D49C, 0x24);

const u32 gBallGfx_Ultra[] = INCBIN_U32("assets/graphics.bin", 0x6D4C0, 0xB4);
const u32 gBallPal_Ultra[] = INCBIN_U32("assets/graphics.bin", 0x6D574, 0x20);

const u32 gBallGfx_Master[] = INCBIN_U32("assets/graphics.bin", 0x6D594, 0xC0);
const u32 gBallPal_Master[] = INCBIN_U32("assets/graphics.bin", 0x6D654, 0x24);

const u32 gBallGfx_Net[] = INCBIN_U32("assets/graphics.bin", 0x6D678, 0xC0);
const u32 gBallPal_Net[] = INCBIN_U32("assets/graphics.bin", 0x6D738, 0x20);

const u32 gBallGfx_Dive[] = INCBIN_U32("assets/graphics.bin", 0x6D758, 0x114);
const u32 gBallPal_Dive[] = INCBIN_U32("assets/graphics.bin", 0x6D86C, 0x28);

const u32 gBallGfx_Nest[] = INCBIN_U32("assets/graphics.bin", 0x6D894, 0xC4);
const u32 gBallPal_Nest[] = INCBIN_U32("assets/graphics.bin", 0x6D958, 0x24);

const u32 gBallGfx_Repeat[] = INCBIN_U32("assets/graphics.bin", 0x6D97C, 0xC0);
const u32 gBallPal_Repeat[] = INCBIN_U32("assets/graphics.bin", 0x6DA3C, 0x24);

const u32 gBallGfx_Timer[] = INCBIN_U32("assets/graphics.bin", 0x6DA60, 0xF8);
const u32 gBallPal_Timer[] = INCBIN_U32("assets/graphics.bin", 0x6DB58, 0x24);

const u32 gBallGfx_Luxury[] = INCBIN_U32("assets/graphics.bin", 0x6DB7C, 0x12C);
const u32 gBallPal_Luxury[] = INCBIN_U32("assets/graphics.bin", 0x6DCA8, 0x28);

const u32 gBallGfx_Premier[] = INCBIN_U32("assets/graphics.bin", 0x6DCD0, 0xF0);
const u32 gBallPal_Premier[] = INCBIN_U32("assets/graphics.bin", 0x6DDC0, 0x20);

const u32 gOpenPokeballGfx[] = INCBIN_U32("assets/graphics.bin", 0x6DDE0, 0x7C);
// ===== END src/data/graphics/interface_pokeballs.h =====

const u32 gBlankGfxCompressed[] = INCBIN_U32("assets/graphics.bin", 0x6DE5C, 0xFC);

const u32 gBattleAnimSpriteGfx_Bubble[] = INCBIN_U32("assets/graphics.bin", 0x6DF58, 0xC0);
const u32 gBattleAnimSpriteGfx_Bone[] = INCBIN_U32("assets/graphics.bin", 0x6E018, 0xB0);
const u32 gBattleAnimSpriteGfx_AirWave[] = INCBIN_U32("assets/graphics.bin", 0x6E0C8, 0x74);
const u32 gBattleAnimSpriteGfx_Orb[] = INCBIN_U32("assets/graphics.bin", 0x6E13C, 0xB0);
const u32 gBattleAnimSpriteGfx_Sword[] = INCBIN_U32("assets/graphics.bin", 0x6E1EC, 0xD4);
const u32 gBattleAnimSpriteGfx_Seed[] = INCBIN_U32("assets/graphics.bin", 0x6E2C0, 0xCC);

const u32 gBattleAnimSpritePal_RainDrops[] = INCBIN_U32("assets/graphics.bin", 0x6E38C, 0x20);
const u32 gBattleAnimSpritePal_Bone[] = INCBIN_U32("assets/graphics.bin", 0x6E3AC, 0x24);
const u32 gBattleAnimSpritePal_AirWave[] = INCBIN_U32("assets/graphics.bin", 0x6E3D0, 0x28);
const u32 gBattleAnimSpritePal_Orb[] = INCBIN_U32("assets/graphics.bin", 0x6E3F8, 0x14);
const u32 gBattleAnimSpritePal_Sword[] = INCBIN_U32("assets/graphics.bin", 0x6E40C, 0x28);
const u32 gBattleAnimSpritePal_Seed[] = INCBIN_U32("assets/graphics.bin", 0x6E434, 0x28);

const u32 gBattleAnimSpriteGfx_Needle[] = INCBIN_U32("assets/graphics.bin", 0x6E45C, 0x28);
const u32 gBattleAnimSpritePal_Needle[] = INCBIN_U32("assets/graphics.bin", 0x6E484, 0x28);

const u32 gBattleAnimSpriteGfx_Explosion6[] = INCBIN_U32("assets/graphics.bin", 0x6E4AC, 0x17C);
const u32 gBattleAnimSpritePal_Explosion6[] = INCBIN_U32("assets/graphics.bin", 0x6E628, 0x20);

const u32 gBattleAnimSpriteGfx_PinkOrb[] = INCBIN_U32("assets/graphics.bin", 0x6E648, 0x20);
const u32 gBattleAnimSpritePal_PinkOrb[] = INCBIN_U32("assets/graphics.bin", 0x6E668, 0x1C);

const u32 gBattleAnimSpritePal_IceCube[] = INCBIN_U32("assets/graphics.bin", 0x6E684, 0x20);
const u32 gBattleAnimSpriteGfx_IceCube[] = INCBIN_U32("assets/graphics.bin", 0x6E6A4, 0x3E0);

const u32 gBattleAnimSpriteGfx_Gust[] = INCBIN_U32("assets/graphics.bin", 0x6EA84, 0x2E8);
const u32 gBattleAnimSpritePal_Gust[] = INCBIN_U32("assets/graphics.bin", 0x6ED6C, 0x20);

const u32 gBattleAnimSpriteGfx_Spark2[] = INCBIN_U32("assets/graphics.bin", 0x6ED8C, 0x78);
const u32 gBattleAnimSpritePal_Spark2[] = INCBIN_U32("assets/graphics.bin", 0x6EE04, 0x28);

const u32 gBattleAnimSpriteGfx_Orange[] = INCBIN_U32("assets/graphics.bin", 0x6EE2C, 0x68);
const u32 gBattleAnimSpritePal_Orange[] = INCBIN_U32("assets/graphics.bin", 0x6EE94, 0x18);

const u32 gBattleAnimSpriteGfx_Spikes[] = INCBIN_U32("assets/graphics.bin", 0x6EEAC, 0x48);
const u32 gBattleAnimSpritePal_Spikes[] = INCBIN_U32("assets/graphics.bin", 0x6EEF4, 0x24);

const u32 gBattleAnimSpriteGfx_YellowBall[] = INCBIN_U32("assets/graphics.bin", 0x6EF18, 0x34);
const u32 gBattleAnimSpritePal_YellowBall[] = INCBIN_U32("assets/graphics.bin", 0x6EF4C, 0x18);

const u32 gBattleAnimSpriteGfx_TiedBag[] = INCBIN_U32("assets/graphics.bin", 0x6EF64, 0x6C);
const u32 gBattleAnimSpritePal_TiedBag[] = INCBIN_U32("assets/graphics.bin", 0x6EFD0, 0x28);

const u32 gBattleAnimSpriteGfx_BlackSmoke[] = INCBIN_U32("assets/graphics.bin", 0x6EFF8, 0x70);
const u32 gBattleAnimSpritePal_BlackSmoke[] = INCBIN_U32("assets/graphics.bin", 0x6F068, 0x10);

const u32 gBattleAnimSpriteGfx_BlackBall[] = INCBIN_U32("assets/graphics.bin", 0x6F078, 0x20);
const u32 gBattleAnimSpritePal_BlackBall[] = INCBIN_U32("assets/graphics.bin", 0x6F098, 0x24);

const u32 gBattleAnimSpritePal_Glass[] = INCBIN_U32("assets/graphics.bin", 0x6F0BC, 0x1C);
const u32 gBattleAnimSpriteGfx_Glass[] = INCBIN_U32("assets/graphics.bin", 0x6F0D8, 0xC0);

const u32 gBattleAnimSpriteGfx_HornHit[] = INCBIN_U32("assets/graphics.bin", 0x6F198, 0xCC);
const u32 gBattleAnimSpritePal_HornHit[] = INCBIN_U32("assets/graphics.bin", 0x6F264, 0x28);

const u32 gBattleAnimSpritePal_BlueShards[] = INCBIN_U32("assets/graphics.bin", 0x6F28C, 0x28);
const u32 gBattleAnimSpriteGfx_BlueShards[] = INCBIN_U32("assets/graphics.bin", 0x6F2B4, 0x108);

const u32 gUnused_BattleSpritePalette_023[] = INCBIN_U32("assets/graphics.bin", 0x6F3BC, 0x28);

const u32 gUnusedGfx_MusicNotes[] = INCBIN_U32("assets/graphics.bin", 0x6F3E4, 0xFC);

const u32 gBattleAnimSpritePal_Hit[] = INCBIN_U32("assets/graphics.bin", 0x6F4E0, 0x28);
const u32 gBattleAnimSpriteGfx_Hit[] = INCBIN_U32("assets/graphics.bin", 0x6F508, 0x338);

const u32 gBattleAnimSpritePal_Hit2[] = INCBIN_U32("assets/graphics.bin", 0x6F840, 0x28);

const u32 gBattleAnimSpritePal_WavingHand[] = INCBIN_U32("assets/graphics.bin", 0x6F868, 0x28);
const u32 gBattleAnimSpriteGfx_WavingHand[] = INCBIN_U32("assets/graphics.bin", 0x6F890, 0xF0);

const u32 gBattleAnimSpriteGfx_ClosingEye[] = INCBIN_U32("assets/graphics.bin", 0x6F980, 0xCC);
const u32 gBattleAnimSpritePal_ClosingEye[] = INCBIN_U32("assets/graphics.bin", 0x6FA4C, 0x14);

const u32 gBattleAnimSpriteGfx_BlueStar[] = INCBIN_U32("assets/graphics.bin", 0x6FA60, 0x3E0);
const u32 gBattleAnimSpritePal_BlueStar[] = INCBIN_U32("assets/graphics.bin", 0x6FE40, 0x20);

const u32 gBattleAnimSpritePal_BubbleBurst[] = INCBIN_U32("assets/graphics.bin", 0x6FE60, 0x28);
const u32 gBattleAnimSpriteGfx_BubbleBurst[] = INCBIN_U32("assets/graphics.bin", 0x6FE88, 0xEC);

const u32 gBattleAnimSpriteGfx_HitDuplicate[] = INCBIN_U32("assets/graphics.bin", 0x6FF74, 0x338);
const u32 gBattleAnimSpritePal_HitDuplicate[] = INCBIN_U32("assets/graphics.bin", 0x702AC, 0x28);

const u32 gBattleAnimSpritePal_Leer[] = INCBIN_U32("assets/graphics.bin", 0x702D4, 0x28);
const u32 gBattleAnimSpriteGfx_Leer[] = INCBIN_U32("assets/graphics.bin", 0x702FC, 0x2FC);

const u32 gBattleAnimSpritePal_BlueBurst[] = INCBIN_U32("assets/graphics.bin", 0x705F8, 0x28);
const u32 gBattleAnimSpriteGfx_BlueBurst[] = INCBIN_U32("assets/graphics.bin", 0x70620, 0x350);

const u32 gBattleAnimSpriteGfx_SmallEmber[] = INCBIN_U32("assets/graphics.bin", 0x70970, 0x2B8);
const u32 gBattleAnimSpritePal_SmallEmber[] = INCBIN_U32("assets/graphics.bin", 0x70C28, 0x28);

const u32 gBattleAnimSpriteGfx_GraySmoke[] = INCBIN_U32("assets/graphics.bin", 0x70C50, 0x3C0);
const u32 gBattleAnimSpritePal_GraySmoke[] = INCBIN_U32("assets/graphics.bin", 0x71010, 0x24);

const u32 gBattleAnimSpritePal_Fire[] = INCBIN_U32("assets/graphics.bin", 0x71034, 0x28);
const u32 gBattleAnimSpriteGfx_Fire[] = INCBIN_U32("assets/graphics.bin", 0x7105C, 0x970);

const u32 gBattleAnimSpriteGfx_SpinningFire[] = INCBIN_U32("assets/graphics.bin", 0x719CC, 0x3CC);
const u32 gBattleAnimSpriteGfx_FirePlume[] = INCBIN_U32("assets/graphics.bin", 0x71D98, 0x398);

const u32 gBattleAnimSpritePal_Lightning2[] = INCBIN_U32("assets/graphics.bin", 0x72130, 0x28);
const u32 gBattleAnimSpriteGfx_Lightning2[] = INCBIN_U32("assets/graphics.bin", 0x72158, 0x3D4);

const u32 gBattleAnimSpriteGfx_Lightning[] = INCBIN_U32("assets/graphics.bin", 0x7252C, 0x34C);

const u32 gBattleAnimSpriteGfx_SpinningBall[] = INCBIN_U32("assets/graphics.bin", 0x72878, 0x44);
const u32 gBattleAnimSpritePal_SpinningBall[] = INCBIN_U32("assets/graphics.bin", 0x728BC, 0x14);
const u32 gBattleAnimSpritePal_SpinningBall2[] = INCBIN_U32("assets/graphics.bin", 0x728D0, 0x34);

// old battle interface data, unused
const u32 gOldBattleInterfaceGfx[] = INCBIN_U32("assets/graphics.bin", 0x72904, 0x364);
const u32 gOldBattleInterfacePal_1_2_3[] = INCBIN_U32("assets/graphics.bin", 0x72C68, 0x44); // palettes 1-3
const u32 gOldBattleInterfacePal4[] = INCBIN_U32("assets/graphics.bin", 0x72CAC, 0x18); // 4 is by itself
const u32 gOldBattleInterfacePal_5_6_7[] = INCBIN_U32("assets/graphics.bin", 0x72CC4, 0x58); // palettes 5-7
const u32 gOldBattleInterfaceGfx2[] = INCBIN_U32("assets/graphics.bin", 0x72D1C, 0x5C8);
const u32 gOldBattleInterfaceTilemap[] = INCBIN_U32("assets/graphics.bin", 0x732E4, 0x110);

const u32 gBattleAnimSpritePal_ClawSlash2[] = INCBIN_U32("assets/graphics.bin", 0x733F4, 0x28);
const u32 gBattleAnimSpritePal_ClawSlash[] = INCBIN_U32("assets/graphics.bin", 0x7341C, 0x28);

const u32 gBattleAnimSpriteGfx_ClawSlash2[] = INCBIN_U32("assets/graphics.bin", 0x73444, 0x224);
const u32 gBattleAnimSpriteGfx_ClawSlash[] = INCBIN_U32("assets/graphics.bin", 0x73668, 0x2FC);
const u32 gBattleAnimSpriteGfx_Scratch3[] = INCBIN_U32("assets/graphics.bin", 0x73964, 0x20C);
const u32 gBattleAnimSpriteGfx_Scratch2[] = INCBIN_U32("assets/graphics.bin", 0x73B70, 0x1A0);

const u32 gUnusedHpBar_Gfx[] = INCBIN_U32("assets/graphics.bin", 0x73D10, 0x94);

const u32 gBattleAnimSpriteGfx_BubbleBurst2[] = INCBIN_U32("assets/graphics.bin", 0x73DA4, 0x2D0);

const u32 gBattleAnimSpritePal_BubbleBurst2[] = INCBIN_U32("assets/graphics.bin", 0x74074, 0x28);

const u32 gBattleAnimSpriteGfx_IceChunk[] = INCBIN_U32("assets/graphics.bin", 0x7409C, 0x400);
const u32 gBattleAnimSpritePal_IceChunk[] = INCBIN_U32("assets/graphics.bin", 0x7449C, 0x28);

const u32 gBattleAnimSpritePal_Glass2[] = INCBIN_U32("assets/graphics.bin", 0x744C4, 0x28);
const u32 gBattleAnimSpriteGfx_Glass2[] = INCBIN_U32("assets/graphics.bin", 0x744EC, 0x26C);

const u32 gBattleAnimSpritePal_PinkHeart2[] = INCBIN_U32("assets/graphics.bin", 0x74758, 0x28);
const u32 gBattleAnimSpriteGfx_PinkHeart2[] = INCBIN_U32("assets/graphics.bin", 0x74780, 0x26C);

const u32 gInterfaceGfx_UnusedWindow[] = INCBIN_U32("assets/graphics.bin", 0x749EC, 0x4BC);
const u32 gInterfacePal_UnusedWindow[] = INCBIN_U32("assets/graphics.bin", 0x74EA8, 0x28);

const u32 gInterfaceGfx_HPNumbers[] = INCBIN_U32("assets/graphics.bin", 0x74ED0, 0x214);

const u32 gBattleAnimSpriteGfx_SapDrip[] = INCBIN_U32("assets/graphics.bin", 0x750E4, 0x3E0);
const u32 gBattleAnimSpritePal_SapDrip[] = INCBIN_U32("assets/graphics.bin", 0x754C4, 0x20);

const u32 gBattleAnimSpritePal_SapDrip2[] = INCBIN_U32("assets/graphics.bin", 0x754E4, 0x24);

const u32 gUnusedGfx_Window2[] = INCBIN_U32("assets/graphics.bin", 0x75508, 0x29C);
const u32 gUnusedGfx_Window2Bar[] = INCBIN_U32("assets/graphics.bin", 0x757A4, 0x2C);

const u32 gBattleAnimSpriteGfx_Sparkle1[] = INCBIN_U32("assets/graphics.bin", 0x757D0, 0x298);
const u32 gBattleAnimSpritePal_Sparkle1[] = INCBIN_U32("assets/graphics.bin", 0x75A68, 0x28);

const u32 gBattleAnimSpritePal_Sparkle2[] = INCBIN_U32("assets/graphics.bin", 0x75A90, 0x28);
const u32 gBattleAnimSpritePal_HumanoidFoot[] = INCBIN_U32("assets/graphics.bin", 0x75AB8, 0x24);

const u32 gBattleAnimSpriteGfx_HumanoidFoot[] = INCBIN_U32("assets/graphics.bin", 0x75ADC, 0xA0);
const u32 gBattleAnimSpriteGfx_MonsterFoot[] = INCBIN_U32("assets/graphics.bin", 0x75B7C, 0xAC);
const u32 gBattleAnimSpriteGfx_HumanoidHand[] = INCBIN_U32("assets/graphics.bin", 0x75C28, 0xCC);

const u32 gUnusedGfx_LineSketch[] = INCBIN_U32("assets/graphics.bin", 0x75CF4, 0x184);
const u32 gUnusedPal_LineSketch[] = INCBIN_U32("assets/graphics.bin", 0x75E78, 0x10);

const u32 gBattleAnimSpriteGfx_YellowUnk[] = INCBIN_U32("assets/graphics.bin", 0x75E88, 0x2C);
const u32 gBattleAnimSpritePal_YellowUnk[] = INCBIN_U32("assets/graphics.bin", 0x75EB4, 0x18);

const u32 gBattleAnimSpriteGfx_SlamHit[] = INCBIN_U32("assets/graphics.bin", 0x75ECC, 0x4A8);
const u32 gBattleAnimSpritePal_SlamHit[] = INCBIN_U32("assets/graphics.bin", 0x76374, 0x28);

const u32 gBattleAnimSpriteGfx_RedFist[] = INCBIN_U32("assets/graphics.bin", 0x7639C, 0xC4);

const u32 gBattleAnimSpriteGfx_Ring[] = INCBIN_U32("assets/graphics.bin", 0x76460, 0x88);
const u32 gBattleAnimSpritePal_Ring[] = INCBIN_U32("assets/graphics.bin", 0x764E8, 0x24);

const u32 gBattleAnimSpriteGfx_Rocks[] = INCBIN_U32("assets/graphics.bin", 0x7650C, 0x468);
const u32 gBattleAnimSpritePal_Rocks[] = INCBIN_U32("assets/graphics.bin", 0x76974, 0x28);

const u32 gBattleAnimSpriteGfx_Z[] = INCBIN_U32("assets/graphics.bin", 0x7699C, 0x60);
const u32 gBattleAnimSpritePal_Z[] = INCBIN_U32("assets/graphics.bin", 0x769FC, 0x1C);

const u32 gBattleAnimSpriteGfx_YellowUnk2[] = INCBIN_U32("assets/graphics.bin", 0x76A18, 0x28);
const u32 gBattleAnimSpritePal_YellowUnk2[] = INCBIN_U32("assets/graphics.bin", 0x76A40, 0x1C);

const u32 gBattleAnimSpriteGfx_AirSlash[] = INCBIN_U32("assets/graphics.bin", 0x76A5C, 0xB0);
const u32 gBattleAnimSpritePal_AirSlash[] = INCBIN_U32("assets/graphics.bin", 0x76B0C, 0x20);

const u32 gBattleAnimSpriteGfx_SpinningGreenOrbs[] = INCBIN_U32("assets/graphics.bin", 0x76B2C, 0x3D0);
const u32 gBattleAnimSpritePal_SpinningGreenOrbs[] = INCBIN_U32("assets/graphics.bin", 0x76EFC, 0x28);

const u32 gBattleAnimSpriteGfx_Leaf[] = INCBIN_U32("assets/graphics.bin", 0x76F24, 0x1BC);
const u32 gBattleAnimSpritePal_Leaf[] = INCBIN_U32("assets/graphics.bin", 0x770E0, 0x28);

const u32 gUnusedGfx_Metronome[] = INCBIN_U32("assets/graphics.bin", 0x77108, 0x70); // unused, was for metronome at one point

const u32 gBattleAnimSpritePal_Clapping[] = INCBIN_U32("assets/graphics.bin", 0x77178, 0x24);

const u32 gBattleAnimSpriteGfx_PoisonPowder[] = INCBIN_U32("assets/graphics.bin", 0x7719C, 0x114);
const u32 gBattleAnimSpritePal_PoisonPowder[] = INCBIN_U32("assets/graphics.bin", 0x772B0, 0x20);

const u32 gBattleAnimSpriteGfx_BrownTriangle[] = INCBIN_U32("assets/graphics.bin", 0x772D0, 0x4C);
const u32 gBattleAnimSpritePal_BrownTriangle[] = INCBIN_U32("assets/graphics.bin", 0x7731C, 0x28);

const u32 gBattleAnimSpriteGfx_Sparkle3[] = INCBIN_U32("assets/graphics.bin", 0x77344, 0x80);
const u32 gBattleAnimSpritePal_Sparkle3[] = INCBIN_U32("assets/graphics.bin", 0x773C4, 0x28);

const u32 gBattleAnimSpriteGfx_Sparkle4[] = INCBIN_U32("assets/graphics.bin", 0x773EC, 0x22C);

const u32 gBattleAnimSpriteGfx_MusicNotes[] = INCBIN_U32("assets/graphics.bin", 0x77618, 0xD0);
const u32 gBattleAnimSpritePal_MusicNotes[] = INCBIN_U32("assets/graphics.bin", 0x776E8, 0x18);

const u32 gBattleAnimSpriteGfx_Duck[] = INCBIN_U32("assets/graphics.bin", 0x77700, 0x11C);
const u32 gBattleAnimSpritePal_Duck[] = INCBIN_U32("assets/graphics.bin", 0x7781C, 0x20);

const u32 gBattleAnimSpriteGfx_Alert[] = INCBIN_U32("assets/graphics.bin", 0x7783C, 0x27C);
const u32 gBattleAnimSpritePal_Alert[] = INCBIN_U32("assets/graphics.bin", 0x77AB8, 0x24);

const u32 gBattleAnimSpriteGfx_Shock4[] = INCBIN_U32("assets/graphics.bin", 0x77ADC, 0x198);
const u32 gBattleAnimSpritePal_Shock4[] = INCBIN_U32("assets/graphics.bin", 0x77C74, 0x28);

const u32 gBattleAnimSpriteGfx_Shock[] = INCBIN_U32("assets/graphics.bin", 0x77C9C, 0x430);

const u32 gBattleAnimSpriteGfx_Bell2[] = INCBIN_U32("assets/graphics.bin", 0x780CC, 0x364);
const u32 gBattleAnimSpritePal_Bell2[] = INCBIN_U32("assets/graphics.bin", 0x78430, 0x24);

const u32 gBattleAnimSpriteGfx_PinkGlove[] = INCBIN_U32("assets/graphics.bin", 0x78454, 0x84);
const u32 gBattleAnimSpritePal_PinkGlove[] = INCBIN_U32("assets/graphics.bin", 0x784D8, 0x24);

const u16 gBattleAnimUnused_Unknown1[] = INCBIN_U16("assets/graphics.bin", 0x784FC, 0x24);
const u16 gBattleAnimUnused_Unknown2[] = INCBIN_U16("assets/graphics.bin", 0x78520, 0x24);
const u16 gBattleAnimUnused_Unknown3[] = INCBIN_U16("assets/graphics.bin", 0x78544, 0x24);

const u32 gBattleAnimUnusedGfx_LineSketch2[] = INCBIN_U32("assets/graphics.bin", 0x78568, 0x58);
const u16 gBattleAnimUnusedPal_LineSketch2[] = INCBIN_U16("assets/graphics.bin", 0x785C0, 0x20);
const u32 gBattleAnimUnusedTilemap_LineSketch2[] = INCBIN_U32("assets/graphics.bin", 0x785E0, 0x90);

const u32 gBattleAnimSpriteGfx_BlueLines[] = INCBIN_U32("assets/graphics.bin", 0x78670, 0x24);
const u32 gBattleAnimSpritePal_BlueLines[] = INCBIN_U32("assets/graphics.bin", 0x78694, 0x14);

const u32 gBattleAnimSpritePal_Impact3[] = INCBIN_U32("assets/graphics.bin", 0x786A8, 0x28);
const u32 gBattleAnimSpritePal_Impact2[] = INCBIN_U32("assets/graphics.bin", 0x786D0, 0x28);
const u32 gBattleAnimSpritePal_Reticle[] = INCBIN_U32("assets/graphics.bin", 0x786F8, 0x18);
const u32 gBattleAnimSpritePal_Breath[] = INCBIN_U32("assets/graphics.bin", 0x78710, 0x28);
const u32 gBattleAnimSpritePal_Snowball[] = INCBIN_U32("assets/graphics.bin", 0x78738, 0x1C);
const u32 gBattleAnimSpritePal_Vine[] = INCBIN_U32("assets/graphics.bin", 0x78754, 0x28);
const u32 gBattleAnimSpritePal_Sword2[] = INCBIN_U32("assets/graphics.bin", 0x7877C, 0x24);
const u32 gBattleAnimSpritePal_RedTube[] = INCBIN_U32("assets/graphics.bin", 0x787A0, 0x1C);
const u32 gBattleAnimSpritePal_Amnesia[] = INCBIN_U32("assets/graphics.bin", 0x787BC, 0x28);
const u32 gBattleAnimSpritePal_String2[] = INCBIN_U32("assets/graphics.bin", 0x787E4, 0x20);

const u32 gBattleAnimUnused_Unknown4[] = INCBIN_U32("assets/graphics.bin", 0x78804, 0x20);

const u32 gBattleAnimSpritePal_Pencil2[] = INCBIN_U32("assets/graphics.bin", 0x78824, 0x28);
const u32 gBattleAnimSpritePal_Petal[] = INCBIN_U32("assets/graphics.bin", 0x7884C, 0x1C);
const u32 gBattleAnimSpritePal_BentSpoon[] = INCBIN_U32("assets/graphics.bin", 0x78868, 0x28);
const u32 gBattleAnimSpritePal_Coin[] = INCBIN_U32("assets/graphics.bin", 0x78890, 0x1C);
const u32 gBattleAnimSpritePal_CrackedEgg[] = INCBIN_U32("assets/graphics.bin", 0x788AC, 0x28);
const u32 gBattleAnimSpritePal_FreshEgg[] = INCBIN_U32("assets/graphics.bin", 0x788D4, 0x24);

const u32 gBattleAnimSpriteGfx_Impact3[] = INCBIN_U32("assets/graphics.bin", 0x788F8, 0x4A4);
const u32 gBattleAnimSpriteGfx_Impact2[] = INCBIN_U32("assets/graphics.bin", 0x78D9C, 0x3C4);
const u32 gBattleAnimSpriteGfx_Reticle[] = INCBIN_U32("assets/graphics.bin", 0x79160, 0xB8);
const u32 gBattleAnimSpriteGfx_Breath[] = INCBIN_U32("assets/graphics.bin", 0x79218, 0x170);
const u32 gBattleAnimSpriteGfx_Snowball[] = INCBIN_U32("assets/graphics.bin", 0x79388, 0x50);
const u32 gBattleAnimSpriteGfx_Vine[] = INCBIN_U32("assets/graphics.bin", 0x793D8, 0x274);
const u32 gBattleAnimSpriteGfx_Sword2[] = INCBIN_U32("assets/graphics.bin", 0x7964C, 0x90);
const u32 gBattleAnimSpriteGfx_Clapping[] = INCBIN_U32("assets/graphics.bin", 0x796DC, 0x134);
const u32 gBattleAnimSpriteGfx_RedTube[] = INCBIN_U32("assets/graphics.bin", 0x79810, 0x7C);
const u32 gBattleAnimSpriteGfx_Amnesia[] = INCBIN_U32("assets/graphics.bin", 0x7988C, 0x6D0);
const u32 gBattleAnimSpriteGfx_String2[] = INCBIN_U32("assets/graphics.bin", 0x79F5C, 0x1A4);
const u32 gBattleAnimSpriteGfx_Pencil2[] = INCBIN_U32("assets/graphics.bin", 0x7A100, 0xB0);
const u32 gBattleAnimSpriteGfx_Petal[] = INCBIN_U32("assets/graphics.bin", 0x7A1B0, 0x170);
const u32 gBattleAnimSpriteGfx_BentSpoon[] = INCBIN_U32("assets/graphics.bin", 0x7A320, 0x1E0);
const u32 gBattleAnimSpriteGfx_Web[] = INCBIN_U32("assets/graphics.bin", 0x7A500, 0x138);
const u32 gBattleAnimSpriteGfx_Coin[] = INCBIN_U32("assets/graphics.bin", 0x7A638, 0x100);
const u32 gBattleAnimSpriteGfx_CrackedEgg[] = INCBIN_U32("assets/graphics.bin", 0x7A738, 0x130);
const u32 gBattleAnimSpriteGfx_HatchedEgg[] = INCBIN_U32("assets/graphics.bin", 0x7A868, 0x198);
const u32 gBattleAnimSpriteGfx_FreshEgg[] = INCBIN_U32("assets/graphics.bin", 0x7AA00, 0x6C);

const u32 gBattleAnimSpriteGfx_Fangs[] = INCBIN_U32("assets/graphics.bin", 0x7AA6C, 0x1C0);
const u32 gBattleAnimSpritePal_Fangs[] = INCBIN_U32("assets/graphics.bin", 0x7AC2C, 0x28);

const u32 gBattleAnimSpriteGfx_Explosion2[] = INCBIN_U32("assets/graphics.bin", 0x7AC54, 0x584);
const u32 gBattleAnimSpritePal_Explosion2[] = INCBIN_U32("assets/graphics.bin", 0x7B1D8, 0x28);

const u32 gBattleAnimSpriteGfx_Explosion3[] = INCBIN_U32("assets/graphics.bin", 0x7B200, 0xF0);

const u32 gBattleAnimSpriteGfx_WaterDroplet[] = INCBIN_U32("assets/graphics.bin", 0x7B2F0, 0x3AC);
const u32 gBattleAnimSpritePal_WaterDroplet[] = INCBIN_U32("assets/graphics.bin", 0x7B69C, 0x28);

const u32 gBattleAnimSpriteGfx_WaterDroplet2[] = INCBIN_U32("assets/graphics.bin", 0x7B6C4, 0x384);

const u32 gBattleAnimSpriteGfx_Seed2[] = INCBIN_U32("assets/graphics.bin", 0x7BA48, 0x28);
const u32 gBattleAnimSpritePal_Seed2[] = INCBIN_U32("assets/graphics.bin", 0x7BA70, 0x28);

const u32 gBattleAnimSpriteGfx_Sprout[] = INCBIN_U32("assets/graphics.bin", 0x7BA98, 0x3E4);

const u32 gBattleAnimSpriteGfx_RedWand[] = INCBIN_U32("assets/graphics.bin", 0x7BE7C, 0x44);
const u32 gBattleAnimSpritePal_RedWand[] = INCBIN_U32("assets/graphics.bin", 0x7BEC0, 0x24);

const u32 gBattleAnimSpriteGfx_PurpleGreenUnk[] = INCBIN_U32("assets/graphics.bin", 0x7BEE4, 0x328);
const u32 gBattleAnimSpritePal_PurpleGreenUnk[] = INCBIN_U32("assets/graphics.bin", 0x7C20C, 0x28);

const u32 gBattleAnimSpriteGfx_WaterColumn[] = INCBIN_U32("assets/graphics.bin", 0x7C234, 0x26C);
const u32 gBattleAnimSpritePal_WaterColumn[] = INCBIN_U32("assets/graphics.bin", 0x7C4A0, 0x28);

const u32 gBattleAnimSpriteGfx_MudUnk[] = INCBIN_U32("assets/graphics.bin", 0x7C4C8, 0xF4);
const u32 gBattleAnimSpritePal_MudUnk[] = INCBIN_U32("assets/graphics.bin", 0x7C5BC, 0x28);

const u32 gUnusedTilemap_BlueFrame[] = INCBIN_U32("assets/graphics.bin", 0x7C5E4, 0x118); // P1, P2, P3 and P4 tilemaps?
const u32 gUnusedTilemap_RedYellowGreenFrame[] = INCBIN_U32("assets/graphics.bin", 0x7C6FC, 0x400);
const u32 gUnusedGfx_ColorFrames[] = INCBIN_U32("assets/graphics.bin", 0x7CAFC, 0x5A0);
const u32 gUnusedPal_ColorFrames[] = INCBIN_U32("assets/graphics.bin", 0x7D09C, 0x28);

const u32 gBattleAnimSpriteGfx_RainDrops[] = INCBIN_U32("assets/graphics.bin", 0x7D0C4, 0x130);

const u32 gUnusedGfx8bpp_WaterSplash [] = INCBIN_U32("assets/graphics.bin", 0x7D1F4, 0x188);
const u32 gUnusedTilemap_WaterSplash[] = INCBIN_U32("assets/graphics.bin", 0x7D37C, 0xE0);
const u32 gUnusedPalette_WaterSplash[] = INCBIN_U32("assets/graphics.bin", 0x7D45C, 0x60);

const u32 gUnusedGfx_BasicFrame[] = INCBIN_U32("assets/graphics.bin", 0x7D4BC, 0x8C);
const u32 gUnusedPal_BasicFrame[] = INCBIN_U32("assets/graphics.bin", 0x7D548, 0x28);
const u32 gUnusedTilemap_BasicFrame[] = INCBIN_U32("assets/graphics.bin", 0x7D570, 0x10C);

const u16 gBattleInterface_Healthbox_Pal[] = INCBIN_U16("assets/graphics.bin", 0x7D67C, 0x20);
const u16 gBattleInterface_Healthbar_Pal[] = INCBIN_U16("assets/graphics.bin", 0x7D69C, 0x20);
const u8 gBattleInterface_Gfx[] = INCBIN_U8("assets/graphics.bin", 0x7D6BC, 0xF00);

const u32 gBattleInterfaceGfx_UnusedWindow3[] = INCBIN_U32("assets/graphics.bin", 0x7E5BC, 0x13C);
const u32 gBattleInterfaceGfx_UnusedWindow4[] = INCBIN_U32("assets/graphics.bin", 0x7E6F8, 0x2B0);

const u32 gBattleAnimSpriteGfx_FurySwipes[] = INCBIN_U32("assets/graphics.bin", 0x7E9A8, 0x2AC);
const u32 gBattleAnimSpritePal_FurySwipes[] = INCBIN_U32("assets/graphics.bin", 0x7EC54, 0x28);

const u32 gBattleAnimSpriteGfx_Vine2[] = INCBIN_U32("assets/graphics.bin", 0x7EC7C, 0x23C);
const u32 gBattleAnimSpritePal_Vine2[] = INCBIN_U32("assets/graphics.bin", 0x7EEB8, 0x1C);

const u32 gBattleAnimSpriteGfx_Teeth[] = INCBIN_U32("assets/graphics.bin", 0x7EED4, 0x198);
const u32 gBattleAnimSpritePal_Teeth[] = INCBIN_U32("assets/graphics.bin", 0x7F06C, 0x1C);

const u32 gBattleAnimSpriteGfx_Bone2[] = INCBIN_U32("assets/graphics.bin", 0x7F088, 0x290);
const u32 gBattleAnimSpritePal_Bone2[] = INCBIN_U32("assets/graphics.bin", 0x7F318, 0x28);

const u32 gBattleAnimSpriteGfx_WhiteBag[] = INCBIN_U32("assets/graphics.bin", 0x7F340, 0xF4);
const u32 gBattleAnimSpritePal_WhiteBag[] = INCBIN_U32("assets/graphics.bin", 0x7F434, 0x28);

const u32 gBattleAnimSpriteGfx_Unknown[] = INCBIN_U32("assets/graphics.bin", 0x7F45C, 0x2C);
const u32 gBattleAnimSpritePal_Unknown[] = INCBIN_U32("assets/graphics.bin", 0x7F488, 0x24);

const u32 gBattleAnimSpriteGfx_PurpleCoral[] = INCBIN_U32("assets/graphics.bin", 0x7F4AC, 0xFC);
const u32 gBattleAnimSpritePal_PurpleCoral[] = INCBIN_U32("assets/graphics.bin", 0x7F5A8, 0x1C);

const u32 gBattleAnimSpriteGfx_PurpleDroplet[] = INCBIN_U32("assets/graphics.bin", 0x7F5C4, 0x13C);

const u32 gBattleAnimSpriteGfx_Shock2[] = INCBIN_U32("assets/graphics.bin", 0x7F700, 0x298);
const u32 gBattleAnimSpritePal_Shock2[] = INCBIN_U32("assets/graphics.bin", 0x7F998, 0x28);

const u32 gBattleAnimSpriteGfx_ClosingEye2[] = INCBIN_U32("assets/graphics.bin", 0x7F9C0, 0xEC);
const u32 gBattleAnimSpritePal_ClosingEye2[] = INCBIN_U32("assets/graphics.bin", 0x7FAAC, 0x28);

const u32 gBattleAnimSpriteGfx_MetalBall[] = INCBIN_U32("assets/graphics.bin", 0x7FAD4, 0x68);
const u32 gBattleAnimSpritePal_MetalBall[] = INCBIN_U32("assets/graphics.bin", 0x7FB3C, 0x20);

const u32 gBattleAnimSpriteGfx_MonsterDoll[] = INCBIN_U32("assets/graphics.bin", 0x7FB5C, 0x1A0);
const u32 gBattleAnimSpritePal_MonsterDoll[] = INCBIN_U32("assets/graphics.bin", 0x7FCFC, 0x24);

const u32 gBattleAnimSpriteGfx_Whirlwind[] = INCBIN_U32("assets/graphics.bin", 0x7FD20, 0x26C);
const u32 gBattleAnimSpritePal_Whirlwind[] = INCBIN_U32("assets/graphics.bin", 0x7FF8C, 0x20);

const u32 gBattleAnimSpriteGfx_Whirlwind2[] = INCBIN_U32("assets/graphics.bin", 0x7FFAC, 0x64);

const u32 gBattleAnimSpriteGfx_Explosion4[] = INCBIN_U32("assets/graphics.bin", 0x80010, 0x3D0);
const u32 gBattleAnimSpritePal_Explosion4[] = INCBIN_U32("assets/graphics.bin", 0x803E0, 0x28);

const u32 gBattleAnimSpriteGfx_Explosion5[] = INCBIN_U32("assets/graphics.bin", 0x80408, 0x170);

const u32 gBattleAnimSpriteGfx_Tongue[] = INCBIN_U32("assets/graphics.bin", 0x80578, 0x100);
const u32 gBattleAnimSpritePal_Tongue[] = INCBIN_U32("assets/graphics.bin", 0x80678, 0x20);

const u32 gBattleAnimSpriteGfx_Smoke[] = INCBIN_U32("assets/graphics.bin", 0x80698, 0x7C);
const u32 gBattleAnimSpritePal_Smoke[] = INCBIN_U32("assets/graphics.bin", 0x80714, 0x28);

const u32 gBattleAnimSpriteGfx_Smoke2[] = INCBIN_U32("assets/graphics.bin", 0x8073C, 0xD0);

const u32 gBattleAnimSpriteGfx_BlueFlames[] = INCBIN_U32("assets/graphics.bin", 0x8080C, 0x23C);
const u32 gBattleAnimSpritePal_BlueFlames[] = INCBIN_U32("assets/graphics.bin", 0x80A48, 0x28);

const u32 gBattleAnimSpriteGfx_BlueFlames2[] = INCBIN_U32("assets/graphics.bin", 0x80A70, 0xD4);

// Contest (unused)

const u32 gJpContest_Gfx1[] = INCBIN_U32("assets/graphics.bin", 0x80B44, 0x914);
const u32 gJpContest_Pal[] = INCBIN_U32("assets/graphics.bin", 0x81458, 0x104);
const u32 gJpContest_Bg_Tilemap[] = INCBIN_U32("assets/graphics.bin", 0x8155C, 0x184);
const u32 gJpContest_Windows_Tilemap[] = INCBIN_U32("assets/graphics.bin", 0x816E0, 0x2C0);
const u32 gJpContest_Numbers_Gfx[] = INCBIN_U32("assets/graphics.bin", 0x819A0, 0xF0);
const u32 gJpContest_Numbers_Pal[] = INCBIN_U32("assets/graphics.bin", 0x81A90, 0x20);
const u32 gJpContest_Gfx2[] = INCBIN_U32("assets/graphics.bin", 0x81AB0, 0x1010);

const u32 gContest_Interface_Pal[] = INCBIN_U32("assets/graphics.bin", 0x82AC0, 0x118);
const u32 gContest_Audience_Tilemap[] = INCBIN_U32("assets/graphics.bin", 0x82BD8, 0x1C8);
const u32 gContest_Interface_Tilemap[] = INCBIN_U32("assets/graphics.bin", 0x82DA0, 0x2A0);

const u32 gJpContest_Interface_Tilemap[] = INCBIN_U32("assets/graphics.bin", 0x83040, 0x10C);
const u32 gJpContest_Audience_Tilemap[] = INCBIN_U32("assets/graphics.bin", 0x8314C, 0x464);

const u32 gContest_Curtain_Tilemap[] = INCBIN_U32("assets/graphics.bin", 0x835B0, 0x130);
const u32 gContest_Interface_Gfx[] = INCBIN_U32("assets/graphics.bin", 0x836E0, 0xB98);
const u32 gContest_Audience_Gfx[] = INCBIN_U32("assets/graphics.bin", 0x84278, 0xC5C);
const u32 gContest_Faces_Gfx[] = INCBIN_U32("assets/graphics.bin", 0x84ED4, 0x11C);
const u32 gContest_JudgeSymbols_Gfx[] = INCBIN_U32("assets/graphics.bin", 0x84FF0, 0x1A4);
const u32 gContest_JudgeSymbols_Pal[] = INCBIN_U32("assets/graphics.bin", 0x85194, 0x28);
const u8 gContest_SliderHeart_Gfx[] = INCBIN_U8("assets/graphics.bin", 0x851BC, 0x20);

const u32 gJpContest_Voltage_Gfx[] = INCBIN_U32("assets/graphics.bin", 0x851DC, 0xF0);
const u32 gJpContest_Voltage_Pal[] = INCBIN_U32("assets/graphics.bin", 0x852CC, 0x28);

const u32 gJpContestResults_Gfx[] = INCBIN_U32("assets/graphics.bin", 0x852F4, 0x868);

const u32 gContestResults_WinnerBanner_Tilemap[] = INCBIN_U32("assets/graphics.bin", 0x85B5C, 0x114);
const u32 gContestResults_Interface_Tilemap[] = INCBIN_U32("assets/graphics.bin", 0x85C70, 0x12C);
const u32 gContestResults_Bg_Tilemap[] = INCBIN_U32("assets/graphics.bin", 0x85D9C, 0x188);
const u32 gContestResults_Pal[] = INCBIN_U32("assets/graphics.bin", 0x85F24, 0xEC);


const u32 gBattleAnimSpriteGfx_Impact[] = INCBIN_U32("assets/graphics.bin", 0x86010, 0xD8);
const u32 gBattleAnimSpritePal_Impact[] = INCBIN_U32("assets/graphics.bin", 0x860E8, 0x18);

const u32 gBattleAnimSpriteGfx_Particles[] = INCBIN_U32("assets/graphics.bin", 0x86100, 0xB0);

const u32 gBattleAnimSpriteGfx_CircleImpact[] = INCBIN_U32("assets/graphics.bin", 0x861B0, 0x24);
const u32 gBattleAnimSpritePal_CircleImpact[] = INCBIN_U32("assets/graphics.bin", 0x861D4, 0x28);

const u32 gBattleAnimSpriteGfx_Scratch[] = INCBIN_U32("assets/graphics.bin", 0x861FC, 0x204);

const u32 gBattleAnimSpriteGfx_SharpTeeth[] = INCBIN_U32("assets/graphics.bin", 0x86400, 0x1F0);
const u32 gBattleAnimSpritePal_SharpTeeth[] = INCBIN_U32("assets/graphics.bin", 0x865F0, 0x20);

const u32 gBattleAnimSpriteGfx_Clamp[] = INCBIN_U32("assets/graphics.bin", 0x86610, 0x1A0);

const u32 gBattleAnimSpriteGfx_Cut[] = INCBIN_U32("assets/graphics.bin", 0x867B0, 0x14C);

const u32 gBattleAnimSpriteGfx_RainbowRings[] = INCBIN_U32("assets/graphics.bin", 0x868FC, 0x80);
const u32 gBattleAnimSpritePal_RainbowRings[] = INCBIN_U32("assets/graphics.bin", 0x8697C, 0x20);

const u32 gBattleAnimSpriteGfx_IceCrystals[] = INCBIN_U32("assets/graphics.bin", 0x8699C, 0x108);
const u32 gBattleAnimSpritePal_IceCrystals[] = INCBIN_U32("assets/graphics.bin", 0x86AA4, 0x20);

const u32 gBattleAnimSpriteGfx_IceSpikes[] = INCBIN_U32("assets/graphics.bin", 0x86AC4, 0x60);

const u32 gUnusedGfx_OldBeatUp[] = INCBIN_U32("assets/graphics.bin", 0x86B24, 0x9C);
const u32 gUnusedPal_OldBeatUp[] = INCBIN_U32("assets/graphics.bin", 0x86BC0, 0x1C);

const u32 gBattleAnimSpriteGfx_Orbs[] = INCBIN_U32("assets/graphics.bin", 0x86BDC, 0x114);
const u32 gBattleAnimSpritePal_Orbs[] = INCBIN_U32("assets/graphics.bin", 0x86CF0, 0x28);

const u32 gBattleAnimSpriteGfx_WaterOrb[] = INCBIN_U32("assets/graphics.bin", 0x86D18, 0xD0);

const u32 gBattleAnimSpriteGfx_WaterImpact[] = INCBIN_U32("assets/graphics.bin", 0x86DE8, 0xE4);
const u32 gBattleAnimSpritePal_WaterImpact[] = INCBIN_U32("assets/graphics.bin", 0x86ECC, 0x20);

const u32 gBattleAnimSpritePal_BrownOrb[] = INCBIN_U32("assets/graphics.bin", 0x86EEC, 0x20);

const u32 gBattleAnimSpriteGfx_MudSand[] = INCBIN_U32("assets/graphics.bin", 0x86F0C, 0x68);
const u32 gBattleAnimSpritePal_MudSand[] = INCBIN_U32("assets/graphics.bin", 0x86F74, 0x24);

const u32 gBattleAnimSpriteGfx_PoisonBubble[] = INCBIN_U32("assets/graphics.bin", 0x86F98, 0xD4);
const u32 gBattleAnimSpritePal_PoisonBubble[] = INCBIN_U32("assets/graphics.bin", 0x8706C, 0x1C);

const u32 gBattleAnimSpriteGfx_ToxicBubble[] = INCBIN_U32("assets/graphics.bin", 0x87088, 0xF8);

const u32 gBattleAnimSpriteGfx_HornHit2[] = INCBIN_U32("assets/graphics.bin", 0x87180, 0x6C);
const u32 gBattleAnimSpritePal_HornHit2[] = INCBIN_U32("assets/graphics.bin", 0x871EC, 0x18);

const u32 gBattleAnimSpriteGfx_AirWave2[] = INCBIN_U32("assets/graphics.bin", 0x87204, 0xAC);
const u32 gBattleAnimSpritePal_AirWave2[] = INCBIN_U32("assets/graphics.bin", 0x872B0, 0x20);

const u32 gBattleAnimSpriteGfx_SmallBubbles[] = INCBIN_U32("assets/graphics.bin", 0x872D0, 0xC8);
const u32 gBattleAnimSpritePal_SmallBubbles[] = INCBIN_U32("assets/graphics.bin", 0x87398, 0x20);

const u32 gBattleAnimSpriteGfx_RoundShadow[] = INCBIN_U32("assets/graphics.bin", 0x873B8, 0x218);
const u32 gBattleAnimSpritePal_RoundShadow[] = INCBIN_U32("assets/graphics.bin", 0x875D0, 0x28);

const u32 gBattleAnimSpriteGfx_Sunlight[] = INCBIN_U32("assets/graphics.bin", 0x875F8, 0x64);
const u32 gBattleAnimSpritePal_Sunlight[] = INCBIN_U32("assets/graphics.bin", 0x8765C, 0x18);

const u32 gBattleAnimSpriteGfx_Spore[] = INCBIN_U32("assets/graphics.bin", 0x87674, 0xC8);

const u32 gBattleAnimSpritePal_Spore[] = INCBIN_U32("assets/graphics.bin", 0x8773C, 0x24);

const u32 gBattleAnimSpriteGfx_Flower[] = INCBIN_U32("assets/graphics.bin", 0x87760, 0x7C);
const u32 gBattleAnimSpritePal_Flower[] = INCBIN_U32("assets/graphics.bin", 0x877DC, 0x28);

const u32 gBattleAnimSpriteGfx_RazorLeaf[] = INCBIN_U32("assets/graphics.bin", 0x87804, 0xA8);
const u32 gBattleAnimSpritePal_RazorLeaf[] = INCBIN_U32("assets/graphics.bin", 0x878AC, 0x28);

const u32 gBattleAnimSpriteGfx_MistCloud[] = INCBIN_U32("assets/graphics.bin", 0x878D4, 0x78);
const u32 gBattleAnimSpritePal_MistCloud[] = INCBIN_U32("assets/graphics.bin", 0x8794C, 0x20);

const u32 gBattleAnimUnusedGfx_Lights[] = INCBIN_U32("assets/graphics.bin", 0x8796C, 0x28);
const u32 gBattleAnimUnusedPal_Lights[] = INCBIN_U32("assets/graphics.bin", 0x87994, 0x18);
const u32 gBattleAnimUnusedTilemap_Lights[] = INCBIN_U32("assets/graphics.bin", 0x879AC, 0x104);

const u32 gBattleAnimSpriteGfx_WhirlwindLines[] = INCBIN_U32("assets/graphics.bin", 0x87AB0, 0x84);
const u32 gBattleAnimSpritePal_WhirlwindLines[] = INCBIN_U32("assets/graphics.bin", 0x87B34, 0x20);

const u32 gBattleAnimSpriteGfx_GoldRing[] = INCBIN_U32("assets/graphics.bin", 0x87B54, 0x60);
const u32 gBattleAnimSpritePal_GoldRing[] = INCBIN_U32("assets/graphics.bin", 0x87BB4, 0x18);

const u32 gBattleAnimSpritePal_BlueRing2[] = INCBIN_U32("assets/graphics.bin", 0x87BCC, 0x18);
const u32 gBattleAnimSpritePal_PurpleRing[] = INCBIN_U32("assets/graphics.bin", 0x87BE4, 0x18);
const u32 gBattleAnimSpritePal_BlueRing[] = INCBIN_U32("assets/graphics.bin", 0x87BFC, 0x18);

const u32 gBattleAnimSpriteGfx_GreenLightWall[] = INCBIN_U32("assets/graphics.bin", 0x87C14, 0x30C);
const u32 gBattleAnimSpritePal_GreenLightWall[] = INCBIN_U32("assets/graphics.bin", 0x87F20, 0x20);

const u32 gBattleAnimSpritePal_BlueLightWall[] = INCBIN_U32("assets/graphics.bin", 0x87F40, 0x20);
const u32 gBattleAnimSpritePal_RedLightWall[] = INCBIN_U32("assets/graphics.bin", 0x87F60, 0x20);
const u32 gBattleAnimSpritePal_GrayLightWall[] = INCBIN_U32("assets/graphics.bin", 0x87F80, 0x20);
const u32 gBattleAnimSpritePal_OrangeLightWall[] = INCBIN_U32("assets/graphics.bin", 0x87FA0, 0x20);

const u32 gBattleAnimSpriteGfx_BlackBall2[] = INCBIN_U32("assets/graphics.bin", 0x87FC0, 0x4C);
const u32 gBattleAnimSpritePal_BlackBall2[] = INCBIN_U32("assets/graphics.bin", 0x8800C, 0x28);

const u32 gBattleAnimSpritePal_PurpleGasCloud[] = INCBIN_U32("assets/graphics.bin", 0x88034, 0x20);

const u32 gContestJudgeGfx[] = INCBIN_U32("assets/graphics.bin", 0x88054, 0x2D4);
const u32 gContestJudgePal[] = INCBIN_U32("assets/graphics.bin", 0x88328, 0x28);

const u32 gBattleAnimSpriteGfx_Spark[] = INCBIN_U32("assets/graphics.bin", 0x88350, 0xB4);
const u32 gBattleAnimSpritePal_Spark[] = INCBIN_U32("assets/graphics.bin", 0x88404, 0x28);

const u32 gBattleAnimSpriteGfx_SparkH[] = INCBIN_U32("assets/graphics.bin", 0x8842C, 0x88);

const u32 gBattleAnimBgImage_Dark[] = INCBIN_U32("assets/graphics.bin", 0x884B4, 0x5F8);
const u32 gBattleAnimBgPalette_Dark[] = INCBIN_U32("assets/graphics.bin", 0x88AAC, 0x20);
const u32 gBattleAnimBgTilemap_Dark[] = INCBIN_U32("assets/graphics.bin", 0x88ACC, 0x250);

const u32 gMetalShineGfx[] = INCBIN_U32("assets/graphics.bin", 0x88D1C, 0x13C);
const u32 gMetalShinePalette[] = INCBIN_U32("assets/graphics.bin", 0x88E58, 0x28);
const u32 gMetalShineTilemap[] = INCBIN_U32("assets/graphics.bin", 0x88E80, 0x174);

const u32 gUnusedGfx_Goosuto[] = INCBIN_U32("assets/graphics.bin", 0x88FF4, 0x110); // ghost
const u32 gUnusedPal_Goosuto[] = INCBIN_U32("assets/graphics.bin", 0x89104, 0x18);
const u32 gUnusedTilemap_Goosuto[] = INCBIN_U32("assets/graphics.bin", 0x8911C, 0x150);

const u32 gBattleAnimSpriteGfx_YellowStar[] = INCBIN_U32("assets/graphics.bin", 0x8926C, 0xA0);
const u32 gBattleAnimSpritePal_YellowStar[] = INCBIN_U32("assets/graphics.bin", 0x8930C, 0x28);

const u32 gBattleAnimSpriteGfx_LargeFreshEgg[] = INCBIN_U32("assets/graphics.bin", 0x89334, 0x64);
const u32 gBattleAnimSpritePal_LargeFreshEgg[] = INCBIN_U32("assets/graphics.bin", 0x89398, 0x28);

const u32 gBattleAnimSpriteGfx_ShadowBall[] = INCBIN_U32("assets/graphics.bin", 0x893C0, 0x158);
const u32 gBattleAnimSpritePal_ShadowBall[] = INCBIN_U32("assets/graphics.bin", 0x89518, 0x28);

const u32 gBattleAnimSpriteGfx_Lick[] = INCBIN_U32("assets/graphics.bin", 0x89540, 0xC4);
const u32 gBattleAnimSpritePal_Lick[] = INCBIN_U32("assets/graphics.bin", 0x89604, 0x18);

const u32 gBattleAnimSpriteGfx_VoidLines[] = INCBIN_U32("assets/graphics.bin", 0x8961C, 0x168);
const u32 gBattleAnimSpritePal_VoidLines[] = INCBIN_U32("assets/graphics.bin", 0x89784, 0x28);

const u32 gBattleAnimSpritePal_String[] = INCBIN_U32("assets/graphics.bin", 0x897AC, 0x28);
const u32 gBattleAnimSpriteGfx_String[] = INCBIN_U32("assets/graphics.bin", 0x897D4, 0xDC);

const u32 gBattleAnimSpriteGfx_WebThread[] = INCBIN_U32("assets/graphics.bin", 0x898B0, 0x18);
const u32 gBattleAnimSpriteGfx_SpiderWeb[] = INCBIN_U32("assets/graphics.bin", 0x898C8, 0x390);

const u32 gBattleAnimSpriteGfx_Lightbulb[] = INCBIN_U32("assets/graphics.bin", 0x89C58, 0xA4);
const u32 gBattleAnimSpritePal_Lightbulb[] = INCBIN_U32("assets/graphics.bin", 0x89CFC, 0x28);

const u32 gBattleAnimSpriteGfx_Slash[] = INCBIN_U32("assets/graphics.bin", 0x89D24, 0x278);
const u32 gBattleAnimSpritePal_Slash[] = INCBIN_U32("assets/graphics.bin", 0x89F9C, 0x28);

const u32 gBattleAnimSpriteGfx_FocusEnergy[] = INCBIN_U32("assets/graphics.bin", 0x89FC4, 0x154);
const u32 gBattleAnimSpritePal_FocusEnergy[] = INCBIN_U32("assets/graphics.bin", 0x8A118, 0x28);

const u32 gBattleAnimSpriteGfx_SphereToCube[] = INCBIN_U32("assets/graphics.bin", 0x8A140, 0x414);
const u32 gBattleAnimSpritePal_SphereToCube[] = INCBIN_U32("assets/graphics.bin", 0x8A554, 0x28);

const u32 gBattleAnimBgImage_Psychic[] = INCBIN_U32("assets/graphics.bin", 0x8A57C, 0x1D0);
const u32 gBattleAnimBgPalette_Psychic[] = INCBIN_U32("assets/graphics.bin", 0x8A74C, 0x24);
const u32 gBattleAnimBgTilemap_Psychic[] = INCBIN_U32("assets/graphics.bin", 0x8A770, 0xC8);

const u32 gBattleAnimSpriteGfx_Eye[] = INCBIN_U32("assets/graphics.bin", 0x8A838, 0x1F0);
const u32 gBattleAnimSpritePal_Eye[] = INCBIN_U32("assets/graphics.bin", 0x8AA28, 0x20);

const u32 gBattleAnimSpriteGfx_Tendrils[] = INCBIN_U32("assets/graphics.bin", 0x8AA48, 0x3CC);
const u32 gBattleAnimSpritePal_Tendrils[] = INCBIN_U32("assets/graphics.bin", 0x8AE14, 0x24);

const u32 gHealthboxSinglesPlayerGfx[] = INCBIN_U32("assets/graphics.bin", 0x8AE38, 0x2C4);
const u32 gHealthboxSinglesOpponentGfx[] = INCBIN_U32("assets/graphics.bin", 0x8B0FC, 0x190);
const u32 gHealthboxDoublesPlayerGfx[] = INCBIN_U32("assets/graphics.bin", 0x8B28C, 0x194);
const u32 gHealthboxDoublesOpponentGfx[] = INCBIN_U32("assets/graphics.bin", 0x8B420, 0x194);
const u32 gHealthboxSafariGfx[] = INCBIN_U32("assets/graphics.bin", 0x8B5B4, 0x278);

const u32 gUnusedGfx_Shadow[] = INCBIN_U32("assets/graphics.bin", 0x8B82C, 0x60);
const u32 gUnusedPal_Shadow[] = INCBIN_U32("assets/graphics.bin", 0x8B88C, 0x14);

const u32 gBattleAnimSpriteGfx_LockOn[] = INCBIN_U32("assets/graphics.bin", 0x8B8A0, 0x94);
const u32 gBattleAnimSpritePal_LockOn[] = INCBIN_U32("assets/graphics.bin", 0x8B934, 0x1C);

const u32 gBattleAnimSpriteGfx_OpeningEye[] = INCBIN_U32("assets/graphics.bin", 0x8B950, 0x25C);
const u32 gBattleAnimSpritePal_OpeningEye[] = INCBIN_U32("assets/graphics.bin", 0x8BBAC, 0x24);

const u32 gBattleAnimSpriteGfx_RoundWhiteHalo[] = INCBIN_U32("assets/graphics.bin", 0x8BBD0, 0x26C);
const u32 gBattleAnimSpritePal_RoundWhiteHalo[] = INCBIN_U32("assets/graphics.bin", 0x8BE3C, 0x28);

const u32 gBattleAnimSpriteGfx_TealAlert[] = INCBIN_U32("assets/graphics.bin", 0x8BE64, 0x84);
const u32 gBattleAnimSpritePal_TealAlert[] = INCBIN_U32("assets/graphics.bin", 0x8BEE8, 0x20);

const u32 gBattleAnimSpriteGfx_FangAttack[] = INCBIN_U32("assets/graphics.bin", 0x8BF08, 0x280);
const u32 gBattleAnimSpritePal_FangAttack[] = INCBIN_U32("assets/graphics.bin", 0x8C188, 0x28);

const u32 gBattleAnimSpriteGfx_PurpleHandOutline[] = INCBIN_U32("assets/graphics.bin", 0x8C1B0, 0x15C);
const u32 gBattleAnimSpritePal_PurpleHandOutline[] = INCBIN_U32("assets/graphics.bin", 0x8C30C, 0x28);

const u32 gFile_graphics_battle_anims_masks_curse_sheet[] = INCBIN_U32("assets/graphics.bin", 0x8C334, 0x1C);
const u32 gFile_graphics_battle_anims_masks_curse_tilemap[] = INCBIN_U32("assets/graphics.bin", 0x8C350, 0x100);

const u32 gBattleAnimSpriteGfx_Pencil[] = INCBIN_U32("assets/graphics.bin", 0x8C450, 0xE4);
const u32 gBattleAnimSpritePal_Pencil[] = INCBIN_U32("assets/graphics.bin", 0x8C534, 0x28);

const u32 gBattleAnimSpriteGfx_Spiral[] = INCBIN_U32("assets/graphics.bin", 0x8C55C, 0x3A4);
const u32 gBattleAnimSpritePal_Spiral[] = INCBIN_U32("assets/graphics.bin", 0x8C900, 0x18);

const u32 gBattleAnimSpriteGfx_Moon[] = INCBIN_U32("assets/graphics.bin", 0x8C918, 0x338);
const u32 gBattleAnimSpritePal_Moon[] = INCBIN_U32("assets/graphics.bin", 0x8CC50, 0x28);

const u32 gBattleAnimSpriteGfx_GreenSparkle[] = INCBIN_U32("assets/graphics.bin", 0x8CC78, 0xB8);
const u32 gBattleAnimSpritePal_GreenSparkle[] = INCBIN_U32("assets/graphics.bin", 0x8CD30, 0x20);

const u32 gBattleAnimSpriteGfx_SnoreZ[] = INCBIN_U32("assets/graphics.bin", 0x8CD50, 0x170);
const u32 gBattleAnimSpritePal_SnoreZ[] = INCBIN_U32("assets/graphics.bin", 0x8CEC0, 0x28);

const u32 gBattleAnimSpriteGfx_Explosion[] = INCBIN_U32("assets/graphics.bin", 0x8CEE8, 0x3F0);
const u32 gBattleAnimSpritePal_Explosion[] = INCBIN_U32("assets/graphics.bin", 0x8D2D8, 0x28);

const u32 gBattleAnimSpriteGfx_Nail[] = INCBIN_U32("assets/graphics.bin", 0x8D300, 0xC8);
const u32 gBattleAnimSpritePal_Nail[] = INCBIN_U32("assets/graphics.bin", 0x8D3C8, 0x1C);

const u32 gBattleAnimSpriteGfx_GhostlySpirit[] = INCBIN_U32("assets/graphics.bin", 0x8D3E4, 0x140);
const u32 gBattleAnimSpritePal_GhostlySpirit[] = INCBIN_U32("assets/graphics.bin", 0x8D524, 0x1C);

const u32 gBattleAnimSpriteGfx_WarmRock[] = INCBIN_U32("assets/graphics.bin", 0x8D540, 0x670);
const u32 gBattleAnimSpritePal_WarmRock[] = INCBIN_U32("assets/graphics.bin", 0x8DBB0, 0x28);

const u32 gBattleAnimSpriteGfx_PunchImpact[] = INCBIN_U32("assets/graphics.bin", 0x8DBD8, 0x174);
const u32 gBattleAnimSpritePal_PunchImpact[] = INCBIN_U32("assets/graphics.bin", 0x8DD4C, 0x28);

const u32 gBattleAnimSpriteGfx_BreakingEgg[] = INCBIN_U32("assets/graphics.bin", 0x8DD74, 0x168);
const u32 gBattleAnimSpritePal_BreakingEgg[] = INCBIN_U32("assets/graphics.bin", 0x8DEDC, 0x24);

const u32 gBattleAnimSpriteGfx_ThinRing[] = INCBIN_U32("assets/graphics.bin", 0x8DF00, 0x1AC);
const u32 gBattleAnimSpritePal_ThinRing[] = INCBIN_U32("assets/graphics.bin", 0x8E0AC, 0x24);

const u32 gBattleAnimSpriteGfx_MusicNotes2[] = INCBIN_U32("assets/graphics.bin", 0x8E0D0, 0x20C);
const u32 gBattleAnimSpritePal_MusicNotes2[] = INCBIN_U32("assets/graphics.bin", 0x8E2DC, 0x94);

const u32 gBattleAnimSpriteGfx_Bell[] = INCBIN_U32("assets/graphics.bin", 0x8E370, 0x234);
const u32 gBattleAnimSpritePal_Bell[] = INCBIN_U32("assets/graphics.bin", 0x8E5A4, 0x24);

const u32 gBattleAnimSpriteGfx_SpeedDust[] = INCBIN_U32("assets/graphics.bin", 0x8E5C8, 0xCC);
const u32 gBattleAnimSpritePal_SpeedDust[] = INCBIN_U32("assets/graphics.bin", 0x8E694, 0x24);

const u32 gBattleAnimSpriteGfx_TornMetal[] = INCBIN_U32("assets/graphics.bin", 0x8E6B8, 0x3F0);

const u32 gBattleAnimSpriteGfx_ThoughtBubble[] = INCBIN_U32("assets/graphics.bin", 0x8EAA8, 0x308);
const u32 gBattleAnimSpritePal_ThoughtBubble[] = INCBIN_U32("assets/graphics.bin", 0x8EDB0, 0x20);

const u32 gBattleAnimSpriteGfx_Finger[] = INCBIN_U32("assets/graphics.bin", 0x8EDD0, 0xF0);
const u32 gBattleAnimSpritePal_Finger[] = INCBIN_U32("assets/graphics.bin", 0x8EEC0, 0x24);

const u32 gBattleAnimSpriteGfx_MagentaHeart[] = INCBIN_U32("assets/graphics.bin", 0x8EEE4, 0x68);

const u32 gBattleAnimSpritePal_PinkHeart[] = INCBIN_U32("assets/graphics.bin", 0x8EF4C, 0x20);
const u32 gBattleAnimSpritePal_MagentaHeart[] = INCBIN_U32("assets/graphics.bin", 0x8EF6C, 0x20);
const u32 gBattleAnimSpritePal_RedHeart[] = INCBIN_U32("assets/graphics.bin", 0x8EF8C, 0x20);

const u32 gBattleAnimBg_AttractGfx[] = INCBIN_U32("assets/graphics.bin", 0x8EFAC, 0xA70);
const u32 gBattleAnimBg_AttractPal[] = INCBIN_U32("assets/graphics.bin", 0x8FA1C, 0x28);
const u32 gBattleAnimBg_AttractTilemap[] = INCBIN_U32("assets/graphics.bin", 0x8FA44, 0x27C);

const u32 gBattleAnimSpriteGfx_RedOrb[] = INCBIN_U32("assets/graphics.bin", 0x8FCC0, 0x68);
const u32 gBattleAnimSpritePal_RedOrb[] = INCBIN_U32("assets/graphics.bin", 0x8FD28, 0x20);

const u32 gBattleAnimSpriteGfx_CircleOfLight[] = INCBIN_U32("assets/graphics.bin", 0x8FD48, 0x234);
const u32 gBattleAnimSpriteGfx_ElectricOrbs[] = INCBIN_U32("assets/graphics.bin", 0x8FF7C, 0x50);
const u32 gBattleAnimSpriteGfx_Electricity[] = INCBIN_U32("assets/graphics.bin", 0x8FFCC, 0x26C);

const u32 gBattleAnimSpritePal_ElectricOrbs[] = INCBIN_U32("assets/graphics.bin", 0x90238, 0x24);

const u32 gBattleAnimSpriteGfx_Finger2[] = INCBIN_U32("assets/graphics.bin", 0x9025C, 0x290);

const u32 gBattleAnimSpriteGfx_MovementWaves[] = INCBIN_U32("assets/graphics.bin", 0x904EC, 0x18C);
const u32 gBattleAnimSpritePal_MovementWaves[] = INCBIN_U32("assets/graphics.bin", 0x90678, 0x24);

const u32 gBattleAnim_ScaryFacePal[] = INCBIN_U32("assets/graphics.bin", 0x9069C, 0x28);
const u32 gBattleAnim_ScaryFaceGfx[] = INCBIN_U32("assets/graphics.bin", 0x906C4, 0x230);

const u32 gBattleAnimSpritePal_EyeSparkle[] = INCBIN_U32("assets/graphics.bin", 0x908F4, 0x28);
const u32 gBattleAnimSpriteGfx_EyeSparkle[] = INCBIN_U32("assets/graphics.bin", 0x9091C, 0xAC);

const u32 gBattleAnimSpriteGfx_Anger[] = INCBIN_U32("assets/graphics.bin", 0x909C8, 0x58);
const u32 gBattleAnimSpritePal_Anger[] = INCBIN_U32("assets/graphics.bin", 0x90A20, 0x28);

const u32 gBattleAnimSpriteGfx_Conversion[] = INCBIN_U32("assets/graphics.bin", 0x90A48, 0x3C);
const u32 gBattleAnimSpritePal_Conversion[] = INCBIN_U32("assets/graphics.bin", 0x90A84, 0x1C);

const u32 gBattleAnimSpritePal_Angel[] = INCBIN_U32("assets/graphics.bin", 0x90AA0, 0x28);
const u32 gBattleAnimSpriteGfx_Angel[] = INCBIN_U32("assets/graphics.bin", 0x90AC8, 0x12C);

const u32 gBattleAnimSpritePal_Devil[] = INCBIN_U32("assets/graphics.bin", 0x90BF4, 0x20);
const u32 gBattleAnimSpriteGfx_Devil[] = INCBIN_U32("assets/graphics.bin", 0x90C14, 0x264);

const u32 gBattleAnimSpriteGfx_Swipe[] = INCBIN_U32("assets/graphics.bin", 0x90E78, 0x2EC);
const u32 gBattleAnimSpritePal_Swipe[] = INCBIN_U32("assets/graphics.bin", 0x91164, 0x28);

const u32 gBattleAnimSpritePal_Roots[] = INCBIN_U32("assets/graphics.bin", 0x9118C, 0x20);
const u32 gBattleAnimSpriteGfx_Roots[] = INCBIN_U32("assets/graphics.bin", 0x911AC, 0x294);

const u32 gBattleAnimSpritePal_ItemBag[] = INCBIN_U32("assets/graphics.bin", 0x91440, 0x20);
const u32 gBattleAnimSpriteGfx_ItemBag[] = INCBIN_U32("assets/graphics.bin", 0x91460, 0xFC);

const u32 gBattleAnimSpritePal_TriAttackTriangle[] = INCBIN_U32("assets/graphics.bin", 0x9155C, 0x28);
const u32 gBattleAnimSpriteGfx_TriAttackTriangle[] = INCBIN_U32("assets/graphics.bin", 0x91584, 0x244);

const u32 gBattleAnimSpritePal_LetterZ[] = INCBIN_U32("assets/graphics.bin", 0x917C8, 0x20);
const u32 gBattleAnimSpriteGfx_LetterZ[] = INCBIN_U32("assets/graphics.bin", 0x917E8, 0xA8);

const u32 gBattleAnimBgPalette_Impact[] = INCBIN_U32("assets/graphics.bin", 0x91890, 0x28);
const u32 gBattleAnimBgImage_Impact[] = INCBIN_U32("assets/graphics.bin", 0x918B8, 0xD6C);
const u32 gBattleAnimBgTilemap_ImpactOpponent[] = INCBIN_U32("assets/graphics.bin", 0x92624, 0x4FC);

const u32 gBattleAnimBgTilemap_ImpactPlayer[] = INCBIN_U32("assets/graphics.bin", 0x92B20, 0x4D0);
const u32 gBattleAnimBgTilemap_ImpactContests[] = INCBIN_U32("assets/graphics.bin", 0x92FF0, 0x440);

const u32 gBattleAnimSpriteGfx_JaggedMusicNote[] = INCBIN_U32("assets/graphics.bin", 0x93430, 0x184);
const u32 gBattleAnimSpritePal_JaggedMusicNote[] = INCBIN_U32("assets/graphics.bin", 0x935B4, 0x28);

const u32 gBattleAnimSpriteGfx_Spotlight[] = INCBIN_U32("assets/graphics.bin", 0x935DC, 0x148);

const u32 gBattleAnimSpriteGfx_Pokeball[] = INCBIN_U32("assets/graphics.bin", 0x93724, 0x8C);
const u32 gBattleAnimSpritePal_Pokeball[] = INCBIN_U32("assets/graphics.bin", 0x937B0, 0x24);

const u32 gBattleAnimSpriteGfx_RapidSpin[] = INCBIN_U32("assets/graphics.bin", 0x937D4, 0x1BC);
const u32 gBattleAnimSpritePal_RapidSpin[] = INCBIN_U32("assets/graphics.bin", 0x93990, 0x28);

const u32 gBattleAnimSpriteGfx_MilkBottle[] = INCBIN_U32("assets/graphics.bin", 0x939B8, 0x120);
const u32 gBattleAnimSpritePal_MilkBottle[] = INCBIN_U32("assets/graphics.bin", 0x93AD8, 0x28);

const u32 gBattleAnimSpriteGfx_WispFire[] = INCBIN_U32("assets/graphics.bin", 0x93B00, 0x538);

const u32 gBattleAnimSpritePal_WispOrb[] = INCBIN_U32("assets/graphics.bin", 0x94038, 0x28);
const u32 gBattleAnimSpriteGfx_WispOrb[] = INCBIN_U32("assets/graphics.bin", 0x94060, 0x1D0);

const u32 gBattleAnimSpriteGfx_GoldStars[] = INCBIN_U32("assets/graphics.bin", 0x94230, 0x84);
const u32 gBattleAnimSpritePal_GoldStars[] = INCBIN_U32("assets/graphics.bin", 0x942B4, 0x28);

const u32 gBattleAnimSpriteGfx_EclipsingOrb[] = INCBIN_U32("assets/graphics.bin", 0x942DC, 0x1C0);
const u32 gBattleAnimSpritePal_EclipsingOrb[] = INCBIN_U32("assets/graphics.bin", 0x9449C, 0x24);

const u32 gBattleAnimSpriteGfx_PinkPetal[] = INCBIN_U32("assets/graphics.bin", 0x944C0, 0x68);
const u32 gBattleAnimSpritePal_PinkPetal[] = INCBIN_U32("assets/graphics.bin", 0x94528, 0x24);

const u32 gBattleAnimSpriteGfx_GrayOrb[] = INCBIN_U32("assets/graphics.bin", 0x9454C, 0x50);
const u32 gBattleAnimSpritePal_GrayOrb[] = INCBIN_U32("assets/graphics.bin", 0x9459C, 0x1C);

const u32 gBattleAnimSpritePal_BlueOrb[] = INCBIN_U32("assets/graphics.bin", 0x945B8, 0x1C);
const u32 gBattleAnimSpritePal_RedOrb2[] = INCBIN_U32("assets/graphics.bin", 0x945D4, 0x1C);

const u32 gBattleAnimBgImage_Drill[] = INCBIN_U32("assets/graphics.bin", 0x945F0, 0x1A8);
const u32 gBattleAnimBgPalette_Drill[] = INCBIN_U32("assets/graphics.bin", 0x94798, 0x28);

const u32 gBattleAnimBgPalette_Sky[] = INCBIN_U32("assets/graphics.bin", 0x947C0, 0x28);

const u32 gBattleAnimBgTilemap_Drill[] = INCBIN_U32("assets/graphics.bin", 0x947E8, 0x190);
const u32 gBattleAnimBgTilemap_DrillContests[] = INCBIN_U32("assets/graphics.bin", 0x94978, 0x18C);

const u32 gBattleAnimBgImage_Aurora[] = INCBIN_U32("assets/graphics.bin", 0x94B04, 0xA28);
const u32 gBattleAnimBgPalette_Aurora[] = INCBIN_U32("assets/graphics.bin", 0x9552C, 0x20);
const u32 gBattleAnimBgTilemap_Aurora[] = INCBIN_U32("assets/graphics.bin", 0x9554C, 0x204);

const u32 gBattleAnimBgTilemap_HighspeedOpponent[] = INCBIN_U32("assets/graphics.bin", 0x95750, 0x2F8);
const u32 gBattleAnimBgPalette_Highspeed[] = INCBIN_U32("assets/graphics.bin", 0x95A48, 0x20);

const u32 gBattleAnimBgPalette_Bug[] = INCBIN_U32("assets/graphics.bin", 0x95A68, 0x20);

const u32 gBattleAnimBgImage_Highspeed[] = INCBIN_U32("assets/graphics.bin", 0x95A88, 0x580);
const u32 gBattleAnimBgTilemap_HighspeedPlayer[] = INCBIN_U32("assets/graphics.bin", 0x96008, 0x2F8);

const u32 gBattleAnim_MorningSunGfx[] = INCBIN_U32("assets/graphics.bin", 0x96300, 0xA0);
const u32 gBattleAnim_MorningSunPal[] = INCBIN_U32("assets/graphics.bin", 0x963A0, 0x18);
const u32 gBattleAnim_MorningSunTilemap[] = INCBIN_U32("assets/graphics.bin", 0x963B8, 0x11C);

const u32 gBattleAnimBgTilemap_GuillotineOpponent[] = INCBIN_U32("assets/graphics.bin", 0x964D4, 0x2C8);
const u32 gBattleAnimBgTilemap_GuillotinePlayer[] = INCBIN_U32("assets/graphics.bin", 0x9679C, 0x2FC);
const u32 gBattleAnimBgTilemap_GuillotineContests[] = INCBIN_U32("assets/graphics.bin", 0x96A98, 0x290);

const u32 gBattleAnimBgImage_Guillotine[] = INCBIN_U32("assets/graphics.bin", 0x96D28, 0xD68);
const u32 gBattleAnimBgPalette_Guillotine[] = INCBIN_U32("assets/graphics.bin", 0x97A90, 0x20);

const u32 gBattleAnimBgImage_Thunder[] = INCBIN_U32("assets/graphics.bin", 0x97AB0, 0x99C);
const u32 gBattleAnimBgPalette_Thunder[] = INCBIN_U32("assets/graphics.bin", 0x9844C, 0x28);
const u32 gBattleAnimBgTilemap_Thunder[] = INCBIN_U32("assets/graphics.bin", 0x98474, 0x2F8);

const u32 gBattleAnimSpriteGfx_PainSplit[] = INCBIN_U32("assets/graphics.bin", 0x9876C, 0xE4);
const u32 gBattleAnimSpritePal_PainSplit[] = INCBIN_U32("assets/graphics.bin", 0x98850, 0x28);

const u32 gBattleAnimSpriteGfx_HandsAndFeet[] = INCBIN_U32("assets/graphics.bin", 0x98878, 0x230);
const u32 gBattleAnimSpritePal_HandsAndFeet[] = INCBIN_U32("assets/graphics.bin", 0x98AA8, 0x18);

const u32 gBattleAnimSpriteGfx_Confetti[] = INCBIN_U32("assets/graphics.bin", 0x98AC0, 0xA0);
const u32 gBattleAnimSpritePal_Confetti[] = INCBIN_U32("assets/graphics.bin", 0x98B60, 0x28);

const u32 gSubstituteDollPal[] = INCBIN_U32("assets/graphics.bin", 0x98B88, 0x24);
const u32 gSubstituteDollFrontGfx[] = INCBIN_U32("assets/graphics.bin", 0x98BAC, 0x240);
const u32 gSubstituteDollBackGfx[] = INCBIN_U32("assets/graphics.bin", 0x98DEC, 0x228);

const u32 gBattleAnimSpriteGfx_GreenStar[] = INCBIN_U32("assets/graphics.bin", 0x99014, 0xC4);
const u32 gBattleAnimSpritePal_GreenStar[] = INCBIN_U32("assets/graphics.bin", 0x990D8, 0x1C);

const u32 gFile_graphics_misc_confetti_sheet[] = INCBIN_U32("assets/graphics.bin", 0x990F4, 0x120);
const u32 gFile_graphics_misc_confetti_palette[] = INCBIN_U32("assets/graphics.bin", 0x99214, 0x28);

const u32 gBattleAnimSpriteGfx_PinkCloud[] = INCBIN_U32("assets/graphics.bin", 0x9923C, 0x13C);
const u32 gBattleAnimSpritePal_PinkCloud[] = INCBIN_U32("assets/graphics.bin", 0x99378, 0x24);

const u32 gBattleAnimSpriteGfx_SweatDrop[] = INCBIN_U32("assets/graphics.bin", 0x9939C, 0x28);
const u32 gBattleAnimSpritePal_SweatDrop[] = INCBIN_U32("assets/graphics.bin", 0x993C4, 0x28);

const u32 gBattleStatMask_Gfx[] = INCBIN_U32("assets/graphics.bin", 0x993EC, 0x210);
const u32 gBattleStatMask1_Tilemap[] = INCBIN_U32("assets/graphics.bin", 0x995FC, 0x11C);
const u32 gBattleStatMask2_Tilemap[] = INCBIN_U32("assets/graphics.bin", 0x99718, 0x11C);

const u32 gBattleStatMask1_Pal[] = INCBIN_U32("assets/graphics.bin", 0x99834, 0x20);
const u32 gBattleStatMask2_Pal[] = INCBIN_U32("assets/graphics.bin", 0x99854, 0x20);
const u32 gBattleStatMask3_Pal[] = INCBIN_U32("assets/graphics.bin", 0x99874, 0x20);
const u32 gBattleStatMask4_Pal[] = INCBIN_U32("assets/graphics.bin", 0x99894, 0x20);
const u32 gBattleStatMask5_Pal[] = INCBIN_U32("assets/graphics.bin", 0x998B4, 0x20);
const u32 gBattleStatMask6_Pal[] = INCBIN_U32("assets/graphics.bin", 0x998D4, 0x20);
const u32 gBattleStatMask7_Pal[] = INCBIN_U32("assets/graphics.bin", 0x998F4, 0x20);
const u32 gBattleStatMask8_Pal[] = INCBIN_U32("assets/graphics.bin", 0x99914, 0x20);

const u32 gCureBubblesGfx[] = INCBIN_U32("assets/graphics.bin", 0x99934, 0x13C);
const u32 gCureBubblesPal[] = INCBIN_U32("assets/graphics.bin", 0x99A70, 0x20);
const u32 gCureBubblesTilemap[] = INCBIN_U32("assets/graphics.bin", 0x99A90, 0x11C);

const u32 gBattleAnimSpritePal_PurpleScratch[] = INCBIN_U32("assets/graphics.bin", 0x99BAC, 0x28);
const u32 gBattleAnimSpriteGfx_PurpleScratch[] = INCBIN_U32("assets/graphics.bin", 0x99BD4, 0x1A4);

const u32 gBattleAnimSpriteGfx_PurpleSwipe[] = INCBIN_U32("assets/graphics.bin", 0x99D78, 0x4A8);

const u32 gBattleAnimSpriteGfx_GuardRing[] = INCBIN_U32("assets/graphics.bin", 0x9A220, 0xDC);
const u32 gBattleAnimSpritePal_GuardRing[] = INCBIN_U32("assets/graphics.bin", 0x9A2FC, 0x1C);

const u32 gBattleAnimSpriteGfx_TagHand[] = INCBIN_U32("assets/graphics.bin", 0x9A318, 0x1E4);

const u32 gBattleAnimSpriteGfx_NoiseLine[] = INCBIN_U32("assets/graphics.bin", 0x9A4FC, 0x220);

const u32 gUnusedLevelupAnimationGfx[] = INCBIN_U32("assets/graphics.bin", 0x9A71C, 0x4C);
const u32 gUnusedLevelupAnimationTilemap[] = INCBIN_U32("assets/graphics.bin", 0x9A768, 0x108);

const u32 gBattleAnimSpriteGfx_SmallRedEye[] = INCBIN_U32("assets/graphics.bin", 0x9A870, 0x18);
const u32 gBattleAnimSpritePal_SmallRedEye[] = INCBIN_U32("assets/graphics.bin", 0x9A888, 0x18);

const u32 gBattleAnimSpriteGfx_HollowOrb[] = INCBIN_U32("assets/graphics.bin", 0x9A8A0, 0x50);
const u32 gBattleAnimSpritePal_HollowOrb[] = INCBIN_U32("assets/graphics.bin", 0x9A8F0, 0x20);

const u32 gBattleAnimSpriteGfx_XSign[] = INCBIN_U32("assets/graphics.bin", 0x9A910, 0x1F4);

const u32 gBattleAnimSpriteGfx_BluegreenOrb[] = INCBIN_U32("assets/graphics.bin", 0x9AB04, 0x64);
const u32 gBattleAnimSpritePal_BluegreenOrb[] = INCBIN_U32("assets/graphics.bin", 0x9AB68, 0x18);

const u32 gBattleAnimSpriteGfx_PawPrint[] = INCBIN_U32("assets/graphics.bin", 0x9AB80, 0x118);
const u32 gBattleAnimSpritePal_PawPrint[] = INCBIN_U32("assets/graphics.bin", 0x9AC98, 0x24);

const u32 gBattleAnimSpriteGfx_PurpleFlame[] = INCBIN_U32("assets/graphics.bin", 0x9ACBC, 0x1DC);
const u32 gBattleAnimSpritePal_PurpleFlame[] = INCBIN_U32("assets/graphics.bin", 0x9AE98, 0x28);

const u32 gBattleAnimSpriteGfx_RedBall[] = INCBIN_U32("assets/graphics.bin", 0x9AEC0, 0x138);
const u32 gBattleAnimSpritePal_RedBall[] = INCBIN_U32("assets/graphics.bin", 0x9AFF8, 0x28);

const u32 gBattleAnimSpriteGfx_SmellingsaltEffect[] = INCBIN_U32("assets/graphics.bin", 0x9B020, 0x78);
const u32 gBattleAnimSpritePal_SmellingsaltEffect[] = INCBIN_U32("assets/graphics.bin", 0x9B098, 0x14);

const u32 gBattleAnimSpriteGfx_MagnifyingGlass[] = INCBIN_U32("assets/graphics.bin", 0x9B0AC, 0xE8);
const u32 gBattleAnimSpritePal_MagnifyingGlass[] = INCBIN_U32("assets/graphics.bin", 0x9B194, 0x28);

const u32 gBattleAnimSpriteGfx_Meteor[] = INCBIN_U32("assets/graphics.bin", 0x9B1BC, 0x38C);
const u32 gBattleAnimSpritePal_Meteor[] = INCBIN_U32("assets/graphics.bin", 0x9B548, 0x28);

const u32 gBattleAnimSpriteGfx_FlatRock[] = INCBIN_U32("assets/graphics.bin", 0x9B570, 0x11C);
const u32 gBattleAnimSpritePal_FlatRock[] = INCBIN_U32("assets/graphics.bin", 0x9B68C, 0x20);

const u16 gPPTextPalette[] = INCBIN_U16("assets/graphics.bin", 0x9B6AC, 0x20);

// ===== BEGIN src/data/graphics/pokemon.h =====
const u32 gMonFrontPic_Bulbasaur[] = INCBIN_U32("assets/graphics.bin", 0x9B6CC, 0x2A4);
const u32 gMonPalette_Bulbasaur[] = INCBIN_U32("assets/graphics.bin", 0x9B970, 0x28);
const u32 gMonBackPic_Bulbasaur[] = INCBIN_U32("assets/graphics.bin", 0x9B998, 0x2C4);
const u32 gMonShinyPalette_Bulbasaur[] = INCBIN_U32("assets/graphics.bin", 0x9BC5C, 0x28);
const u8 gMonIcon_Bulbasaur[] = INCBIN_U8("assets/graphics.bin", 0x9BC84, 0x400);
const u8 gMonFootprint_Bulbasaur[] = INCBIN_U8("assets/graphics.bin", 0x9C084, 0x20);

const u32 gMonFrontPic_Ivysaur[] = INCBIN_U32("assets/graphics.bin", 0x9C0A4, 0x33C);
const u32 gMonPalette_Ivysaur[] = INCBIN_U32("assets/graphics.bin", 0x9C3E0, 0x28);
const u32 gMonBackPic_Ivysaur[] = INCBIN_U32("assets/graphics.bin", 0x9C408, 0x354);
const u32 gMonShinyPalette_Ivysaur[] = INCBIN_U32("assets/graphics.bin", 0x9C75C, 0x28);
const u8 gMonIcon_Ivysaur[] = INCBIN_U8("assets/graphics.bin", 0x9C784, 0x400);
const u8 gMonFootprint_Ivysaur[] = INCBIN_U8("assets/graphics.bin", 0x9CB84, 0x20);

const u32 gMonFrontPic_Venusaur[] = INCBIN_U32("assets/graphics.bin", 0x9CBA4, 0x540);
const u32 gMonPalette_Venusaur[] = INCBIN_U32("assets/graphics.bin", 0x9D0E4, 0x28);
const u32 gMonBackPic_Venusaur[] = INCBIN_U32("assets/graphics.bin", 0x9D10C, 0x4C8);
const u32 gMonShinyPalette_Venusaur[] = INCBIN_U32("assets/graphics.bin", 0x9D5D4, 0x28);
const u8 gMonIcon_Venusaur[] = INCBIN_U8("assets/graphics.bin", 0x9D5FC, 0x400);
const u8 gMonFootprint_Venusaur[] = INCBIN_U8("assets/graphics.bin", 0x9D9FC, 0x20);

const u32 gMonFrontPic_Charmander[] = INCBIN_U32("assets/graphics.bin", 0x9DA1C, 0x2A0);
const u32 gMonPalette_Charmander[] = INCBIN_U32("assets/graphics.bin", 0x9DCBC, 0x28);
const u32 gMonBackPic_Charmander[] = INCBIN_U32("assets/graphics.bin", 0x9DCE4, 0x284);
const u32 gMonShinyPalette_Charmander[] = INCBIN_U32("assets/graphics.bin", 0x9DF68, 0x28);
const u8 gMonIcon_Charmander[] = INCBIN_U8("assets/graphics.bin", 0x9DF90, 0x400);
const u8 gMonFootprint_Charmander[] = INCBIN_U8("assets/graphics.bin", 0x9E390, 0x20);

const u32 gMonFrontPic_Charmeleon[] = INCBIN_U32("assets/graphics.bin", 0x9E3B0, 0x3AC);
const u32 gMonPalette_Charmeleon[] = INCBIN_U32("assets/graphics.bin", 0x9E75C, 0x28);
const u32 gMonBackPic_Charmeleon[] = INCBIN_U32("assets/graphics.bin", 0x9E784, 0x2F4);
const u32 gMonShinyPalette_Charmeleon[] = INCBIN_U32("assets/graphics.bin", 0x9EA78, 0x28);
const u8 gMonIcon_Charmeleon[] = INCBIN_U8("assets/graphics.bin", 0x9EAA0, 0x400);
const u8 gMonFootprint_Charmeleon[] = INCBIN_U8("assets/graphics.bin", 0x9EEA0, 0x20);

const u32 gMonFrontPic_Charizard[] = INCBIN_U32("assets/graphics.bin", 0x9EEC0, 0x4FC);
const u32 gMonPalette_Charizard[] = INCBIN_U32("assets/graphics.bin", 0x9F3BC, 0x28);
const u32 gMonBackPic_Charizard[] = INCBIN_U32("assets/graphics.bin", 0x9F3E4, 0x40C);
const u32 gMonShinyPalette_Charizard[] = INCBIN_U32("assets/graphics.bin", 0x9F7F0, 0x28);
const u8 gMonIcon_Charizard[] = INCBIN_U8("assets/graphics.bin", 0x9F818, 0x400);
const u8 gMonFootprint_Charizard[] = INCBIN_U8("assets/graphics.bin", 0x9FC18, 0x20);

const u32 gMonFrontPic_Squirtle[] = INCBIN_U32("assets/graphics.bin", 0x9FC38, 0x29C);
const u32 gMonPalette_Squirtle[] = INCBIN_U32("assets/graphics.bin", 0x9FED4, 0x28);
const u32 gMonBackPic_Squirtle[] = INCBIN_U32("assets/graphics.bin", 0x9FEFC, 0x288);
const u32 gMonShinyPalette_Squirtle[] = INCBIN_U32("assets/graphics.bin", 0xA0184, 0x28);
const u8 gMonIcon_Squirtle[] = INCBIN_U8("assets/graphics.bin", 0xA01AC, 0x400);
const u8 gMonFootprint_Squirtle[] = INCBIN_U8("assets/graphics.bin", 0xA05AC, 0x20);

const u32 gMonFrontPic_Wartortle[] = INCBIN_U32("assets/graphics.bin", 0xA05CC, 0x3AC);
const u32 gMonPalette_Wartortle[] = INCBIN_U32("assets/graphics.bin", 0xA0978, 0x28);
const u32 gMonBackPic_Wartortle[] = INCBIN_U32("assets/graphics.bin", 0xA09A0, 0x348);
const u32 gMonShinyPalette_Wartortle[] = INCBIN_U32("assets/graphics.bin", 0xA0CE8, 0x28);
const u8 gMonIcon_Wartortle[] = INCBIN_U8("assets/graphics.bin", 0xA0D10, 0x400);
const u8 gMonFootprint_Wartortle[] = INCBIN_U8("assets/graphics.bin", 0xA1110, 0x20);

const u32 gMonFrontPic_Blastoise[] = INCBIN_U32("assets/graphics.bin", 0xA1130, 0x504);
const u32 gMonPalette_Blastoise[] = INCBIN_U32("assets/graphics.bin", 0xA1634, 0x28);
const u32 gMonBackPic_Blastoise[] = INCBIN_U32("assets/graphics.bin", 0xA165C, 0x414);
const u32 gMonShinyPalette_Blastoise[] = INCBIN_U32("assets/graphics.bin", 0xA1A70, 0x28);
const u8 gMonIcon_Blastoise[] = INCBIN_U8("assets/graphics.bin", 0xA1A98, 0x400);
const u8 gMonFootprint_Blastoise[] = INCBIN_U8("assets/graphics.bin", 0xA1E98, 0x20);

const u32 gMonFrontPic_Caterpie[] = INCBIN_U32("assets/graphics.bin", 0xA1EB8, 0x258);
const u32 gMonPalette_Caterpie[] = INCBIN_U32("assets/graphics.bin", 0xA2110, 0x28);
const u32 gMonBackPic_Caterpie[] = INCBIN_U32("assets/graphics.bin", 0xA2138, 0x288);
const u32 gMonShinyPalette_Caterpie[] = INCBIN_U32("assets/graphics.bin", 0xA23C0, 0x28);
const u8 gMonIcon_Caterpie[] = INCBIN_U8("assets/graphics.bin", 0xA23E8, 0x400);
const u8 gMonFootprint_Caterpie[] = INCBIN_U8("assets/graphics.bin", 0xA27E8, 0x20);

const u32 gMonFrontPic_Metapod[] = INCBIN_U32("assets/graphics.bin", 0xA2808, 0x21C);
const u32 gMonPalette_Metapod[] = INCBIN_U32("assets/graphics.bin", 0xA2A24, 0x20);
const u32 gMonBackPic_Metapod[] = INCBIN_U32("assets/graphics.bin", 0xA2A44, 0x21C);
const u32 gMonShinyPalette_Metapod[] = INCBIN_U32("assets/graphics.bin", 0xA2C60, 0x20);
const u8 gMonIcon_Metapod[] = INCBIN_U8("assets/graphics.bin", 0xA2C80, 0x400);
const u8 gMonFootprint_Metapod[] = INCBIN_U8("assets/graphics.bin", 0xA3080, 0x20);

const u32 gMonFrontPic_Butterfree[] = INCBIN_U32("assets/graphics.bin", 0xA30A0, 0x378);
const u32 gMonPalette_Butterfree[] = INCBIN_U32("assets/graphics.bin", 0xA3418, 0x28);
const u32 gMonBackPic_Butterfree[] = INCBIN_U32("assets/graphics.bin", 0xA3440, 0x404);
const u32 gMonShinyPalette_Butterfree[] = INCBIN_U32("assets/graphics.bin", 0xA3844, 0x28);
const u8 gMonIcon_Butterfree[] = INCBIN_U8("assets/graphics.bin", 0xA386C, 0x400);
const u8 gMonFootprint_Butterfree[] = INCBIN_U8("assets/graphics.bin", 0xA3C6C, 0x20);

const u32 gMonFrontPic_Weedle[] = INCBIN_U32("assets/graphics.bin", 0xA3C8C, 0x23C);
const u32 gMonPalette_Weedle[] = INCBIN_U32("assets/graphics.bin", 0xA3EC8, 0x28);
const u32 gMonBackPic_Weedle[] = INCBIN_U32("assets/graphics.bin", 0xA3EF0, 0x268);
const u32 gMonShinyPalette_Weedle[] = INCBIN_U32("assets/graphics.bin", 0xA4158, 0x28);
const u8 gMonIcon_Weedle[] = INCBIN_U8("assets/graphics.bin", 0xA4180, 0x400);
const u8 gMonFootprint_Weedle[] = INCBIN_U8("assets/graphics.bin", 0xA4580, 0x20);

const u32 gMonFrontPic_Kakuna[] = INCBIN_U32("assets/graphics.bin", 0xA45A0, 0x240);
const u32 gMonPalette_Kakuna[] = INCBIN_U32("assets/graphics.bin", 0xA47E0, 0x24);
const u32 gMonBackPic_Kakuna[] = INCBIN_U32("assets/graphics.bin", 0xA4804, 0x284);
const u32 gMonShinyPalette_Kakuna[] = INCBIN_U32("assets/graphics.bin", 0xA4A88, 0x24);
const u8 gMonIcon_Kakuna[] = INCBIN_U8("assets/graphics.bin", 0xA4AAC, 0x400);
const u8 gMonFootprint_Kakuna[] = INCBIN_U8("assets/graphics.bin", 0xA4EAC, 0x20);

const u32 gMonFrontPic_Beedrill[] = INCBIN_U32("assets/graphics.bin", 0xA4ECC, 0x420);
const u32 gMonPalette_Beedrill[] = INCBIN_U32("assets/graphics.bin", 0xA52EC, 0x28);
const u32 gMonBackPic_Beedrill[] = INCBIN_U32("assets/graphics.bin", 0xA5314, 0x374);
const u32 gMonShinyPalette_Beedrill[] = INCBIN_U32("assets/graphics.bin", 0xA5688, 0x28);
const u8 gMonIcon_Beedrill[] = INCBIN_U8("assets/graphics.bin", 0xA56B0, 0x400);
const u8 gMonFootprint_Beedrill[] = INCBIN_U8("assets/graphics.bin", 0xA5AB0, 0x20);

const u32 gMonFrontPic_Pidgey[] = INCBIN_U32("assets/graphics.bin", 0xA5AD0, 0x278);
const u32 gMonPalette_Pidgey[] = INCBIN_U32("assets/graphics.bin", 0xA5D48, 0x28);
const u32 gMonBackPic_Pidgey[] = INCBIN_U32("assets/graphics.bin", 0xA5D70, 0x354);
const u32 gMonShinyPalette_Pidgey[] = INCBIN_U32("assets/graphics.bin", 0xA60C4, 0x28);
const u8 gMonIcon_Pidgey[] = INCBIN_U8("assets/graphics.bin", 0xA60EC, 0x400);
const u8 gMonFootprint_Pidgey[] = INCBIN_U8("assets/graphics.bin", 0xA64EC, 0x20);

const u32 gMonFrontPic_Pidgeotto[] = INCBIN_U32("assets/graphics.bin", 0xA650C, 0x398);
const u32 gMonPalette_Pidgeotto[] = INCBIN_U32("assets/graphics.bin", 0xA68A4, 0x28);
const u32 gMonBackPic_Pidgeotto[] = INCBIN_U32("assets/graphics.bin", 0xA68CC, 0x34C);
const u32 gMonShinyPalette_Pidgeotto[] = INCBIN_U32("assets/graphics.bin", 0xA6C18, 0x28);
const u8 gMonIcon_Pidgeotto[] = INCBIN_U8("assets/graphics.bin", 0xA6C40, 0x400);
const u8 gMonFootprint_Pidgeotto[] = INCBIN_U8("assets/graphics.bin", 0xA7040, 0x20);

const u32 gMonFrontPic_Pidgeot[] = INCBIN_U32("assets/graphics.bin", 0xA7060, 0x4EC);
const u32 gMonPalette_Pidgeot[] = INCBIN_U32("assets/graphics.bin", 0xA754C, 0x28);
const u32 gMonBackPic_Pidgeot[] = INCBIN_U32("assets/graphics.bin", 0xA7574, 0x3E8);
const u32 gMonShinyPalette_Pidgeot[] = INCBIN_U32("assets/graphics.bin", 0xA795C, 0x28);
const u8 gMonIcon_Pidgeot[] = INCBIN_U8("assets/graphics.bin", 0xA7984, 0x400);
const u8 gMonFootprint_Pidgeot[] = INCBIN_U8("assets/graphics.bin", 0xA7D84, 0x20);

const u32 gMonFrontPic_Rattata[] = INCBIN_U32("assets/graphics.bin", 0xA7DA4, 0x258);
const u32 gMonPalette_Rattata[] = INCBIN_U32("assets/graphics.bin", 0xA7FFC, 0x28);
const u32 gMonBackPic_Rattata[] = INCBIN_U32("assets/graphics.bin", 0xA8024, 0x2B8);
const u32 gMonShinyPalette_Rattata[] = INCBIN_U32("assets/graphics.bin", 0xA82DC, 0x28);
const u8 gMonIcon_Rattata[] = INCBIN_U8("assets/graphics.bin", 0xA8304, 0x400);
const u8 gMonFootprint_Rattata[] = INCBIN_U8("assets/graphics.bin", 0xA8704, 0x20);

const u32 gMonFrontPic_Raticate[] = INCBIN_U32("assets/graphics.bin", 0xA8724, 0x390);
const u32 gMonPalette_Raticate[] = INCBIN_U32("assets/graphics.bin", 0xA8AB4, 0x28);
const u32 gMonBackPic_Raticate[] = INCBIN_U32("assets/graphics.bin", 0xA8ADC, 0x310);
const u32 gMonShinyPalette_Raticate[] = INCBIN_U32("assets/graphics.bin", 0xA8DEC, 0x28);
const u8 gMonIcon_Raticate[] = INCBIN_U8("assets/graphics.bin", 0xA8E14, 0x400);
const u8 gMonFootprint_Raticate[] = INCBIN_U8("assets/graphics.bin", 0xA9214, 0x20);

const u32 gMonFrontPic_Spearow[] = INCBIN_U32("assets/graphics.bin", 0xA9234, 0x2C0);
const u32 gMonPalette_Spearow[] = INCBIN_U32("assets/graphics.bin", 0xA94F4, 0x28);
const u32 gMonBackPic_Spearow[] = INCBIN_U32("assets/graphics.bin", 0xA951C, 0x2DC);
const u32 gMonShinyPalette_Spearow[] = INCBIN_U32("assets/graphics.bin", 0xA97F8, 0x28);
const u8 gMonIcon_Spearow[] = INCBIN_U8("assets/graphics.bin", 0xA9820, 0x400);
const u8 gMonFootprint_Spearow[] = INCBIN_U8("assets/graphics.bin", 0xA9C20, 0x20);

const u32 gMonFrontPic_Fearow[] = INCBIN_U32("assets/graphics.bin", 0xA9C40, 0x4BC);
const u32 gMonPalette_Fearow[] = INCBIN_U32("assets/graphics.bin", 0xAA0FC, 0x28);
const u32 gMonBackPic_Fearow[] = INCBIN_U32("assets/graphics.bin", 0xAA124, 0x2F8);
const u32 gMonShinyPalette_Fearow[] = INCBIN_U32("assets/graphics.bin", 0xAA41C, 0x28);
const u8 gMonIcon_Fearow[] = INCBIN_U8("assets/graphics.bin", 0xAA444, 0x400);
const u8 gMonFootprint_Fearow[] = INCBIN_U8("assets/graphics.bin", 0xAA844, 0x20);

const u32 gMonFrontPic_Ekans[] = INCBIN_U32("assets/graphics.bin", 0xAA864, 0x2C8);
const u32 gMonPalette_Ekans[] = INCBIN_U32("assets/graphics.bin", 0xAAB2C, 0x28);
const u32 gMonBackPic_Ekans[] = INCBIN_U32("assets/graphics.bin", 0xAAB54, 0x2F0);
const u32 gMonShinyPalette_Ekans[] = INCBIN_U32("assets/graphics.bin", 0xAAE44, 0x28);
const u8 gMonIcon_Ekans[] = INCBIN_U8("assets/graphics.bin", 0xAAE6C, 0x400);
const u8 gMonFootprint_Ekans[] = INCBIN_U8("assets/graphics.bin", 0xAB26C, 0x20);

const u32 gMonFrontPic_Arbok[] = INCBIN_U32("assets/graphics.bin", 0xAB28C, 0x474);
const u32 gMonPalette_Arbok[] = INCBIN_U32("assets/graphics.bin", 0xAB700, 0x28);
const u32 gMonBackPic_Arbok[] = INCBIN_U32("assets/graphics.bin", 0xAB728, 0x288);
const u32 gMonShinyPalette_Arbok[] = INCBIN_U32("assets/graphics.bin", 0xAB9B0, 0x28);
const u8 gMonIcon_Arbok[] = INCBIN_U8("assets/graphics.bin", 0xAB9D8, 0x400);
const u8 gMonFootprint_Arbok[] = INCBIN_U8("assets/graphics.bin", 0xABDD8, 0x20);

const u32 gMonFrontPic_Pikachu[] = INCBIN_U32("assets/graphics.bin", 0xABDF8, 0x2D0);
const u32 gMonPalette_Pikachu[] = INCBIN_U32("assets/graphics.bin", 0xAC0C8, 0x28);
const u32 gMonBackPic_Pikachu[] = INCBIN_U32("assets/graphics.bin", 0xAC0F0, 0x2D8);
const u32 gMonShinyPalette_Pikachu[] = INCBIN_U32("assets/graphics.bin", 0xAC3C8, 0x28);
const u8 gMonIcon_Pikachu[] = INCBIN_U8("assets/graphics.bin", 0xAC3F0, 0x400);
const u8 gMonFootprint_Pikachu[] = INCBIN_U8("assets/graphics.bin", 0xAC7F0, 0x20);

const u32 gMonFrontPic_Raichu[] = INCBIN_U32("assets/graphics.bin", 0xAC810, 0x3F8);
const u32 gMonPalette_Raichu[] = INCBIN_U32("assets/graphics.bin", 0xACC08, 0x28);
const u32 gMonBackPic_Raichu[] = INCBIN_U32("assets/graphics.bin", 0xACC30, 0x320);
const u32 gMonShinyPalette_Raichu[] = INCBIN_U32("assets/graphics.bin", 0xACF50, 0x28);
const u8 gMonIcon_Raichu[] = INCBIN_U8("assets/graphics.bin", 0xACF78, 0x400);
const u8 gMonFootprint_Raichu[] = INCBIN_U8("assets/graphics.bin", 0xAD378, 0x20);

const u32 gMonFrontPic_Sandshrew[] = INCBIN_U32("assets/graphics.bin", 0xAD398, 0x2DC);
const u32 gMonPalette_Sandshrew[] = INCBIN_U32("assets/graphics.bin", 0xAD674, 0x28);
const u32 gMonBackPic_Sandshrew[] = INCBIN_U32("assets/graphics.bin", 0xAD69C, 0x328);
const u32 gMonShinyPalette_Sandshrew[] = INCBIN_U32("assets/graphics.bin", 0xAD9C4, 0x28);
const u8 gMonIcon_Sandshrew[] = INCBIN_U8("assets/graphics.bin", 0xAD9EC, 0x400);
const u8 gMonFootprint_Sandshrew[] = INCBIN_U8("assets/graphics.bin", 0xADDEC, 0x20);

const u32 gMonFrontPic_Sandslash[] = INCBIN_U32("assets/graphics.bin", 0xADE0C, 0x418);
const u32 gMonPalette_Sandslash[] = INCBIN_U32("assets/graphics.bin", 0xAE224, 0x28);
const u32 gMonBackPic_Sandslash[] = INCBIN_U32("assets/graphics.bin", 0xAE24C, 0x41C);
const u32 gMonShinyPalette_Sandslash[] = INCBIN_U32("assets/graphics.bin", 0xAE668, 0x28);
const u8 gMonIcon_Sandslash[] = INCBIN_U8("assets/graphics.bin", 0xAE690, 0x400);
const u8 gMonFootprint_Sandslash[] = INCBIN_U8("assets/graphics.bin", 0xAEA90, 0x20);

const u32 gMonFrontPic_NidoranF[] = INCBIN_U32("assets/graphics.bin", 0xAEAB0, 0x264);
const u32 gMonPalette_NidoranF[] = INCBIN_U32("assets/graphics.bin", 0xAED14, 0x28);
const u32 gMonBackPic_NidoranF[] = INCBIN_U32("assets/graphics.bin", 0xAED3C, 0x2E0);
const u32 gMonShinyPalette_NidoranF[] = INCBIN_U32("assets/graphics.bin", 0xAF01C, 0x28);
const u8 gMonIcon_NidoranF[] = INCBIN_U8("assets/graphics.bin", 0xAF044, 0x400);
const u8 gMonFootprint_NidoranF[] = INCBIN_U8("assets/graphics.bin", 0xAF444, 0x20);

const u32 gMonFrontPic_Nidorina[] = INCBIN_U32("assets/graphics.bin", 0xAF464, 0x320);
const u32 gMonPalette_Nidorina[] = INCBIN_U32("assets/graphics.bin", 0xAF784, 0x28);
const u32 gMonBackPic_Nidorina[] = INCBIN_U32("assets/graphics.bin", 0xAF7AC, 0x394);
const u32 gMonShinyPalette_Nidorina[] = INCBIN_U32("assets/graphics.bin", 0xAFB40, 0x28);
const u8 gMonIcon_Nidorina[] = INCBIN_U8("assets/graphics.bin", 0xAFB68, 0x400);
const u8 gMonFootprint_Nidorina[] = INCBIN_U8("assets/graphics.bin", 0xAFF68, 0x20);

const u32 gMonFrontPic_Nidoqueen[] = INCBIN_U32("assets/graphics.bin", 0xAFF88, 0x42C);
const u32 gMonPalette_Nidoqueen[] = INCBIN_U32("assets/graphics.bin", 0xB03B4, 0x28);
const u32 gMonBackPic_Nidoqueen[] = INCBIN_U32("assets/graphics.bin", 0xB03DC, 0x3C4);
const u32 gMonShinyPalette_Nidoqueen[] = INCBIN_U32("assets/graphics.bin", 0xB07A0, 0x28);
const u8 gMonIcon_Nidoqueen[] = INCBIN_U8("assets/graphics.bin", 0xB07C8, 0x400);
const u8 gMonFootprint_Nidoqueen[] = INCBIN_U8("assets/graphics.bin", 0xB0BC8, 0x20);

const u32 gMonFrontPic_NidoranM[] = INCBIN_U32("assets/graphics.bin", 0xB0BE8, 0x28C);
const u32 gMonPalette_NidoranM[] = INCBIN_U32("assets/graphics.bin", 0xB0E74, 0x28);
const u32 gMonBackPic_NidoranM[] = INCBIN_U32("assets/graphics.bin", 0xB0E9C, 0x334);
const u32 gMonShinyPalette_NidoranM[] = INCBIN_U32("assets/graphics.bin", 0xB11D0, 0x28);
const u8 gMonIcon_NidoranM[] = INCBIN_U8("assets/graphics.bin", 0xB11F8, 0x400);
const u8 gMonFootprint_NidoranM[] = INCBIN_U8("assets/graphics.bin", 0xB15F8, 0x20);

const u32 gMonFrontPic_Nidorino[] = INCBIN_U32("assets/graphics.bin", 0xB1618, 0x384);
const u32 gMonPalette_Nidorino[] = INCBIN_U32("assets/graphics.bin", 0xB199C, 0x28);
const u32 gMonBackPic_Nidorino[] = INCBIN_U32("assets/graphics.bin", 0xB19C4, 0x3BC);
const u32 gMonShinyPalette_Nidorino[] = INCBIN_U32("assets/graphics.bin", 0xB1D80, 0x28);
const u8 gMonIcon_Nidorino[] = INCBIN_U8("assets/graphics.bin", 0xB1DA8, 0x400);
const u8 gMonFootprint_Nidorino[] = INCBIN_U8("assets/graphics.bin", 0xB21A8, 0x20);

const u32 gMonFrontPic_Nidoking[] = INCBIN_U32("assets/graphics.bin", 0xB21C8, 0x53C);
const u32 gMonPalette_Nidoking[] = INCBIN_U32("assets/graphics.bin", 0xB2704, 0x28);
const u32 gMonBackPic_Nidoking[] = INCBIN_U32("assets/graphics.bin", 0xB272C, 0x43C);
const u32 gMonShinyPalette_Nidoking[] = INCBIN_U32("assets/graphics.bin", 0xB2B68, 0x28);
const u8 gMonIcon_Nidoking[] = INCBIN_U8("assets/graphics.bin", 0xB2B90, 0x400);
const u8 gMonFootprint_Nidoking[] = INCBIN_U8("assets/graphics.bin", 0xB2F90, 0x20);

const u32 gMonFrontPic_Clefairy[] = INCBIN_U32("assets/graphics.bin", 0xB2FB0, 0x29C);
const u32 gMonPalette_Clefairy[] = INCBIN_U32("assets/graphics.bin", 0xB324C, 0x28);
const u32 gMonBackPic_Clefairy[] = INCBIN_U32("assets/graphics.bin", 0xB3274, 0x2D0);
const u32 gMonShinyPalette_Clefairy[] = INCBIN_U32("assets/graphics.bin", 0xB3544, 0x28);
const u8 gMonIcon_Clefairy[] = INCBIN_U8("assets/graphics.bin", 0xB356C, 0x400);
const u8 gMonFootprint_Clefairy[] = INCBIN_U8("assets/graphics.bin", 0xB396C, 0x20);

const u32 gMonFrontPic_Clefable[] = INCBIN_U32("assets/graphics.bin", 0xB398C, 0x340);
const u32 gMonPalette_Clefable[] = INCBIN_U32("assets/graphics.bin", 0xB3CCC, 0x28);
const u32 gMonBackPic_Clefable[] = INCBIN_U32("assets/graphics.bin", 0xB3CF4, 0x338);
const u32 gMonShinyPalette_Clefable[] = INCBIN_U32("assets/graphics.bin", 0xB402C, 0x28);
const u8 gMonIcon_Clefable[] = INCBIN_U8("assets/graphics.bin", 0xB4054, 0x400);
const u8 gMonFootprint_Clefable[] = INCBIN_U8("assets/graphics.bin", 0xB4454, 0x20);

const u32 gMonFrontPic_Vulpix[] = INCBIN_U32("assets/graphics.bin", 0xB4474, 0x32C);
const u32 gMonPalette_Vulpix[] = INCBIN_U32("assets/graphics.bin", 0xB47A0, 0x28);
const u32 gMonBackPic_Vulpix[] = INCBIN_U32("assets/graphics.bin", 0xB47C8, 0x304);
const u32 gMonShinyPalette_Vulpix[] = INCBIN_U32("assets/graphics.bin", 0xB4ACC, 0x28);
const u8 gMonIcon_Vulpix[] = INCBIN_U8("assets/graphics.bin", 0xB4AF4, 0x400);
const u8 gMonFootprint_Vulpix[] = INCBIN_U8("assets/graphics.bin", 0xB4EF4, 0x20);

const u32 gMonFrontPic_Ninetales[] = INCBIN_U32("assets/graphics.bin", 0xB4F14, 0x454);
const u32 gMonPalette_Ninetales[] = INCBIN_U32("assets/graphics.bin", 0xB5368, 0x24);
const u32 gMonBackPic_Ninetales[] = INCBIN_U32("assets/graphics.bin", 0xB538C, 0x3F0);
const u32 gMonShinyPalette_Ninetales[] = INCBIN_U32("assets/graphics.bin", 0xB577C, 0x24);
const u8 gMonIcon_Ninetales[] = INCBIN_U8("assets/graphics.bin", 0xB57A0, 0x400);
const u8 gMonFootprint_Ninetales[] = INCBIN_U8("assets/graphics.bin", 0xB5BA0, 0x20);

const u32 gMonFrontPic_Jigglypuff[] = INCBIN_U32("assets/graphics.bin", 0xB5BC0, 0x284);
const u32 gMonPalette_Jigglypuff[] = INCBIN_U32("assets/graphics.bin", 0xB5E44, 0x28);
const u32 gMonBackPic_Jigglypuff[] = INCBIN_U32("assets/graphics.bin", 0xB5E6C, 0x25C);
const u32 gMonShinyPalette_Jigglypuff[] = INCBIN_U32("assets/graphics.bin", 0xB60C8, 0x28);
const u8 gMonIcon_Jigglypuff[] = INCBIN_U8("assets/graphics.bin", 0xB60F0, 0x400);
const u8 gMonFootprint_Jigglypuff[] = INCBIN_U8("assets/graphics.bin", 0xB64F0, 0x20);

const u32 gMonFrontPic_Wigglytuff[] = INCBIN_U32("assets/graphics.bin", 0xB6510, 0x374);
const u32 gMonPalette_Wigglytuff[] = INCBIN_U32("assets/graphics.bin", 0xB6884, 0x28);
const u32 gMonBackPic_Wigglytuff[] = INCBIN_U32("assets/graphics.bin", 0xB68AC, 0x298);
const u32 gMonShinyPalette_Wigglytuff[] = INCBIN_U32("assets/graphics.bin", 0xB6B44, 0x28);
const u8 gMonIcon_Wigglytuff[] = INCBIN_U8("assets/graphics.bin", 0xB6B6C, 0x400);
const u8 gMonFootprint_Wigglytuff[] = INCBIN_U8("assets/graphics.bin", 0xB6F6C, 0x20);

const u32 gMonFrontPic_Zubat[] = INCBIN_U32("assets/graphics.bin", 0xB6F8C, 0x2BC);
const u32 gMonPalette_Zubat[] = INCBIN_U32("assets/graphics.bin", 0xB7248, 0x28);
const u32 gMonBackPic_Zubat[] = INCBIN_U32("assets/graphics.bin", 0xB7270, 0x2BC);
const u32 gMonShinyPalette_Zubat[] = INCBIN_U32("assets/graphics.bin", 0xB752C, 0x28);
const u8 gMonIcon_Zubat[] = INCBIN_U8("assets/graphics.bin", 0xB7554, 0x400);
const u8 gMonFootprint_Zubat[] = INCBIN_U8("assets/graphics.bin", 0xB7954, 0x20);

const u32 gMonFrontPic_Golbat[] = INCBIN_U32("assets/graphics.bin", 0xB7974, 0x3A0);
const u32 gMonPalette_Golbat[] = INCBIN_U32("assets/graphics.bin", 0xB7D14, 0x28);
const u32 gMonBackPic_Golbat[] = INCBIN_U32("assets/graphics.bin", 0xB7D3C, 0x2BC);
const u32 gMonShinyPalette_Golbat[] = INCBIN_U32("assets/graphics.bin", 0xB7FF8, 0x28);
const u8 gMonIcon_Golbat[] = INCBIN_U8("assets/graphics.bin", 0xB8020, 0x400);
const u8 gMonFootprint_Golbat[] = INCBIN_U8("assets/graphics.bin", 0xB8420, 0x20);

const u32 gMonFrontPic_Oddish[] = INCBIN_U32("assets/graphics.bin", 0xB8440, 0x240);
const u32 gMonPalette_Oddish[] = INCBIN_U32("assets/graphics.bin", 0xB8680, 0x28);
const u32 gMonBackPic_Oddish[] = INCBIN_U32("assets/graphics.bin", 0xB86A8, 0x2C4);
const u32 gMonShinyPalette_Oddish[] = INCBIN_U32("assets/graphics.bin", 0xB896C, 0x28);
const u8 gMonIcon_Oddish[] = INCBIN_U8("assets/graphics.bin", 0xB8994, 0x400);
const u8 gMonFootprint_Oddish[] = INCBIN_U8("assets/graphics.bin", 0xB8D94, 0x20);

const u32 gMonFrontPic_Gloom[] = INCBIN_U32("assets/graphics.bin", 0xB8DB4, 0x368);
const u32 gMonPalette_Gloom[] = INCBIN_U32("assets/graphics.bin", 0xB911C, 0x28);
const u32 gMonBackPic_Gloom[] = INCBIN_U32("assets/graphics.bin", 0xB9144, 0x380);
const u32 gMonShinyPalette_Gloom[] = INCBIN_U32("assets/graphics.bin", 0xB94C4, 0x28);
const u8 gMonIcon_Gloom[] = INCBIN_U8("assets/graphics.bin", 0xB94EC, 0x400);
const u8 gMonFootprint_Gloom[] = INCBIN_U8("assets/graphics.bin", 0xB98EC, 0x20);

const u32 gMonFrontPic_Vileplume[] = INCBIN_U32("assets/graphics.bin", 0xB990C, 0x354);
const u32 gMonPalette_Vileplume[] = INCBIN_U32("assets/graphics.bin", 0xB9C60, 0x28);
const u32 gMonBackPic_Vileplume[] = INCBIN_U32("assets/graphics.bin", 0xB9C88, 0x44C);
const u32 gMonShinyPalette_Vileplume[] = INCBIN_U32("assets/graphics.bin", 0xBA0D4, 0x28);
const u8 gMonIcon_Vileplume[] = INCBIN_U8("assets/graphics.bin", 0xBA0FC, 0x400);
const u8 gMonFootprint_Vileplume[] = INCBIN_U8("assets/graphics.bin", 0xBA4FC, 0x20);

const u32 gMonFrontPic_Paras[] = INCBIN_U32("assets/graphics.bin", 0xBA51C, 0x26C);
const u32 gMonPalette_Paras[] = INCBIN_U32("assets/graphics.bin", 0xBA788, 0x28);
const u32 gMonBackPic_Paras[] = INCBIN_U32("assets/graphics.bin", 0xBA7B0, 0x2A0);
const u32 gMonShinyPalette_Paras[] = INCBIN_U32("assets/graphics.bin", 0xBAA50, 0x28);
const u8 gMonIcon_Paras[] = INCBIN_U8("assets/graphics.bin", 0xBAA78, 0x400);
const u8 gMonFootprint_Paras[] = INCBIN_U8("assets/graphics.bin", 0xBAE78, 0x20);

const u32 gMonFrontPic_Parasect[] = INCBIN_U32("assets/graphics.bin", 0xBAE98, 0x390);
const u32 gMonPalette_Parasect[] = INCBIN_U32("assets/graphics.bin", 0xBB228, 0x28);
const u32 gMonBackPic_Parasect[] = INCBIN_U32("assets/graphics.bin", 0xBB250, 0x2FC);
const u32 gMonShinyPalette_Parasect[] = INCBIN_U32("assets/graphics.bin", 0xBB54C, 0x28);
const u8 gMonIcon_Parasect[] = INCBIN_U8("assets/graphics.bin", 0xBB574, 0x400);
const u8 gMonFootprint_Parasect[] = INCBIN_U8("assets/graphics.bin", 0xBB974, 0x20);

const u32 gMonFrontPic_Venonat[] = INCBIN_U32("assets/graphics.bin", 0xBB994, 0x320);
const u32 gMonPalette_Venonat[] = INCBIN_U32("assets/graphics.bin", 0xBBCB4, 0x28);
const u32 gMonBackPic_Venonat[] = INCBIN_U32("assets/graphics.bin", 0xBBCDC, 0x330);
const u32 gMonShinyPalette_Venonat[] = INCBIN_U32("assets/graphics.bin", 0xBC00C, 0x28);
const u8 gMonIcon_Venonat[] = INCBIN_U8("assets/graphics.bin", 0xBC034, 0x400);
const u8 gMonFootprint_Venonat[] = INCBIN_U8("assets/graphics.bin", 0xBC434, 0x20);

const u32 gMonFrontPic_Venomoth[] = INCBIN_U32("assets/graphics.bin", 0xBC454, 0x404);
const u32 gMonPalette_Venomoth[] = INCBIN_U32("assets/graphics.bin", 0xBC858, 0x28);
const u32 gMonBackPic_Venomoth[] = INCBIN_U32("assets/graphics.bin", 0xBC880, 0x3A4);
const u32 gMonShinyPalette_Venomoth[] = INCBIN_U32("assets/graphics.bin", 0xBCC24, 0x28);
const u8 gMonIcon_Venomoth[] = INCBIN_U8("assets/graphics.bin", 0xBCC4C, 0x400);
const u8 gMonFootprint_Venomoth[] = INCBIN_U8("assets/graphics.bin", 0xBD04C, 0x20);

const u32 gMonFrontPic_Diglett[] = INCBIN_U32("assets/graphics.bin", 0xBD06C, 0x210);
const u32 gMonPalette_Diglett[] = INCBIN_U32("assets/graphics.bin", 0xBD27C, 0x28);
const u32 gMonBackPic_Diglett[] = INCBIN_U32("assets/graphics.bin", 0xBD2A4, 0x20C);
const u32 gMonShinyPalette_Diglett[] = INCBIN_U32("assets/graphics.bin", 0xBD4B0, 0x28);
const u8 gMonIcon_Diglett[] = INCBIN_U8("assets/graphics.bin", 0xBD4D8, 0x400);
const u8 gMonFootprint_Diglett[] = INCBIN_U8("assets/graphics.bin", 0xBD8D8, 0x20);

const u32 gMonFrontPic_Dugtrio[] = INCBIN_U32("assets/graphics.bin", 0xBD8F8, 0x32C);
const u32 gMonPalette_Dugtrio[] = INCBIN_U32("assets/graphics.bin", 0xBDC24, 0x28);
const u32 gMonBackPic_Dugtrio[] = INCBIN_U32("assets/graphics.bin", 0xBDC4C, 0x2AC);
const u32 gMonShinyPalette_Dugtrio[] = INCBIN_U32("assets/graphics.bin", 0xBDEF8, 0x28);
const u8 gMonIcon_Dugtrio[] = INCBIN_U8("assets/graphics.bin", 0xBDF20, 0x400);
const u8 gMonFootprint_Dugtrio[] = INCBIN_U8("assets/graphics.bin", 0xBE320, 0x20);

const u32 gMonFrontPic_Meowth[] = INCBIN_U32("assets/graphics.bin", 0xBE340, 0x2EC);
const u32 gMonPalette_Meowth[] = INCBIN_U32("assets/graphics.bin", 0xBE62C, 0x28);
const u32 gMonBackPic_Meowth[] = INCBIN_U32("assets/graphics.bin", 0xBE654, 0x2E4);
const u32 gMonShinyPalette_Meowth[] = INCBIN_U32("assets/graphics.bin", 0xBE938, 0x28);
const u8 gMonIcon_Meowth[] = INCBIN_U8("assets/graphics.bin", 0xBE960, 0x400);
const u8 gMonFootprint_Meowth[] = INCBIN_U8("assets/graphics.bin", 0xBED60, 0x20);

const u32 gMonFrontPic_Persian[] = INCBIN_U32("assets/graphics.bin", 0xBED80, 0x378);
const u32 gMonPalette_Persian[] = INCBIN_U32("assets/graphics.bin", 0xBF0F8, 0x28);
const u32 gMonBackPic_Persian[] = INCBIN_U32("assets/graphics.bin", 0xBF120, 0x340);
const u32 gMonShinyPalette_Persian[] = INCBIN_U32("assets/graphics.bin", 0xBF460, 0x28);
const u8 gMonIcon_Persian[] = INCBIN_U8("assets/graphics.bin", 0xBF488, 0x400);
const u8 gMonFootprint_Persian[] = INCBIN_U8("assets/graphics.bin", 0xBF888, 0x20);

const u32 gMonFrontPic_Psyduck[] = INCBIN_U32("assets/graphics.bin", 0xBF8A8, 0x2E4);
const u32 gMonPalette_Psyduck[] = INCBIN_U32("assets/graphics.bin", 0xBFB8C, 0x28);
const u32 gMonBackPic_Psyduck[] = INCBIN_U32("assets/graphics.bin", 0xBFBB4, 0x29C);
const u32 gMonShinyPalette_Psyduck[] = INCBIN_U32("assets/graphics.bin", 0xBFE50, 0x28);
const u8 gMonIcon_Psyduck[] = INCBIN_U8("assets/graphics.bin", 0xBFE78, 0x400);
const u8 gMonFootprint_Psyduck[] = INCBIN_U8("assets/graphics.bin", 0xC0278, 0x20);

const u32 gMonFrontPic_Golduck[] = INCBIN_U32("assets/graphics.bin", 0xC0298, 0x3B8);
const u32 gMonPalette_Golduck[] = INCBIN_U32("assets/graphics.bin", 0xC0650, 0x28);
const u32 gMonBackPic_Golduck[] = INCBIN_U32("assets/graphics.bin", 0xC0678, 0x32C);
const u32 gMonShinyPalette_Golduck[] = INCBIN_U32("assets/graphics.bin", 0xC09A4, 0x28);
const u8 gMonIcon_Golduck[] = INCBIN_U8("assets/graphics.bin", 0xC09CC, 0x400);
const u8 gMonFootprint_Golduck[] = INCBIN_U8("assets/graphics.bin", 0xC0DCC, 0x20);

const u32 gMonFrontPic_Mankey[] = INCBIN_U32("assets/graphics.bin", 0xC0DEC, 0x2F8);
const u32 gMonPalette_Mankey[] = INCBIN_U32("assets/graphics.bin", 0xC10E4, 0x28);
const u32 gMonBackPic_Mankey[] = INCBIN_U32("assets/graphics.bin", 0xC110C, 0x368);
const u32 gMonShinyPalette_Mankey[] = INCBIN_U32("assets/graphics.bin", 0xC1474, 0x28);
const u8 gMonIcon_Mankey[] = INCBIN_U8("assets/graphics.bin", 0xC149C, 0x400);
const u8 gMonFootprint_Mankey[] = INCBIN_U8("assets/graphics.bin", 0xC189C, 0x20);

const u32 gMonFrontPic_Primeape[] = INCBIN_U32("assets/graphics.bin", 0xC18BC, 0x38C);
const u32 gMonPalette_Primeape[] = INCBIN_U32("assets/graphics.bin", 0xC1C48, 0x28);
const u32 gMonBackPic_Primeape[] = INCBIN_U32("assets/graphics.bin", 0xC1C70, 0x370);
const u32 gMonShinyPalette_Primeape[] = INCBIN_U32("assets/graphics.bin", 0xC1FE0, 0x28);
const u8 gMonIcon_Primeape[] = INCBIN_U8("assets/graphics.bin", 0xC2008, 0x400);
const u8 gMonFootprint_Primeape[] = INCBIN_U8("assets/graphics.bin", 0xC2408, 0x20);

const u32 gMonFrontPic_Growlithe[] = INCBIN_U32("assets/graphics.bin", 0xC2428, 0x328);
const u32 gMonPalette_Growlithe[] = INCBIN_U32("assets/graphics.bin", 0xC2750, 0x28);
const u32 gMonBackPic_Growlithe[] = INCBIN_U32("assets/graphics.bin", 0xC2778, 0x33C);
const u32 gMonShinyPalette_Growlithe[] = INCBIN_U32("assets/graphics.bin", 0xC2AB4, 0x28);
const u8 gMonIcon_Growlithe[] = INCBIN_U8("assets/graphics.bin", 0xC2ADC, 0x400);
const u8 gMonFootprint_Growlithe[] = INCBIN_U8("assets/graphics.bin", 0xC2EDC, 0x20);

const u32 gMonFrontPic_Arcanine[] = INCBIN_U32("assets/graphics.bin", 0xC2EFC, 0x4FC);
const u32 gMonPalette_Arcanine[] = INCBIN_U32("assets/graphics.bin", 0xC33F8, 0x28);
const u32 gMonBackPic_Arcanine[] = INCBIN_U32("assets/graphics.bin", 0xC3420, 0x3E0);
const u32 gMonShinyPalette_Arcanine[] = INCBIN_U32("assets/graphics.bin", 0xC3800, 0x28);
const u8 gMonIcon_Arcanine[] = INCBIN_U8("assets/graphics.bin", 0xC3828, 0x400);
const u8 gMonFootprint_Arcanine[] = INCBIN_U8("assets/graphics.bin", 0xC3C28, 0x20);

const u32 gMonFrontPic_Poliwag[] = INCBIN_U32("assets/graphics.bin", 0xC3C48, 0x29C);
const u32 gMonPalette_Poliwag[] = INCBIN_U32("assets/graphics.bin", 0xC3EE4, 0x28);
const u32 gMonBackPic_Poliwag[] = INCBIN_U32("assets/graphics.bin", 0xC3F0C, 0x264);
const u32 gMonShinyPalette_Poliwag[] = INCBIN_U32("assets/graphics.bin", 0xC4170, 0x28);
const u8 gMonIcon_Poliwag[] = INCBIN_U8("assets/graphics.bin", 0xC4198, 0x400);
const u8 gMonFootprint_Poliwag[] = INCBIN_U8("assets/graphics.bin", 0xC4598, 0x20);

const u32 gMonFrontPic_Poliwhirl[] = INCBIN_U32("assets/graphics.bin", 0xC45B8, 0x380);
const u32 gMonPalette_Poliwhirl[] = INCBIN_U32("assets/graphics.bin", 0xC4938, 0x28);
const u32 gMonBackPic_Poliwhirl[] = INCBIN_U32("assets/graphics.bin", 0xC4960, 0x27C);
const u32 gMonShinyPalette_Poliwhirl[] = INCBIN_U32("assets/graphics.bin", 0xC4BDC, 0x28);
const u8 gMonIcon_Poliwhirl[] = INCBIN_U8("assets/graphics.bin", 0xC4C04, 0x400);
const u8 gMonFootprint_Poliwhirl[] = INCBIN_U8("assets/graphics.bin", 0xC5004, 0x20);

const u32 gMonFrontPic_Poliwrath[] = INCBIN_U32("assets/graphics.bin", 0xC5024, 0x3C4);
const u32 gMonPalette_Poliwrath[] = INCBIN_U32("assets/graphics.bin", 0xC53E8, 0x28);
const u32 gMonBackPic_Poliwrath[] = INCBIN_U32("assets/graphics.bin", 0xC5410, 0x2F4);
const u32 gMonShinyPalette_Poliwrath[] = INCBIN_U32("assets/graphics.bin", 0xC5704, 0x28);
const u8 gMonIcon_Poliwrath[] = INCBIN_U8("assets/graphics.bin", 0xC572C, 0x400);
const u8 gMonFootprint_Poliwrath[] = INCBIN_U8("assets/graphics.bin", 0xC5B2C, 0x20);

const u32 gMonFrontPic_Abra[] = INCBIN_U32("assets/graphics.bin", 0xC5B4C, 0x2D4);
const u32 gMonPalette_Abra[] = INCBIN_U32("assets/graphics.bin", 0xC5E20, 0x24);
const u32 gMonBackPic_Abra[] = INCBIN_U32("assets/graphics.bin", 0xC5E44, 0x2D4);
const u32 gMonShinyPalette_Abra[] = INCBIN_U32("assets/graphics.bin", 0xC6118, 0x24);
const u8 gMonIcon_Abra[] = INCBIN_U8("assets/graphics.bin", 0xC613C, 0x400);
const u8 gMonFootprint_Abra[] = INCBIN_U8("assets/graphics.bin", 0xC653C, 0x20);

const u32 gMonFrontPic_Kadabra[] = INCBIN_U32("assets/graphics.bin", 0xC655C, 0x4C8);
const u32 gMonPalette_Kadabra[] = INCBIN_U32("assets/graphics.bin", 0xC6A24, 0x28);
const u32 gMonBackPic_Kadabra[] = INCBIN_U32("assets/graphics.bin", 0xC6A4C, 0x3AC);
const u32 gMonShinyPalette_Kadabra[] = INCBIN_U32("assets/graphics.bin", 0xC6DF8, 0x28);
const u8 gMonIcon_Kadabra[] = INCBIN_U8("assets/graphics.bin", 0xC6E20, 0x400);
const u8 gMonFootprint_Kadabra[] = INCBIN_U8("assets/graphics.bin", 0xC7220, 0x20);

const u32 gMonFrontPic_Alakazam[] = INCBIN_U32("assets/graphics.bin", 0xC7240, 0x498);
const u32 gMonPalette_Alakazam[] = INCBIN_U32("assets/graphics.bin", 0xC76D8, 0x28);
const u32 gMonBackPic_Alakazam[] = INCBIN_U32("assets/graphics.bin", 0xC7700, 0x380);
const u32 gMonShinyPalette_Alakazam[] = INCBIN_U32("assets/graphics.bin", 0xC7A80, 0x28);
const u8 gMonIcon_Alakazam[] = INCBIN_U8("assets/graphics.bin", 0xC7AA8, 0x400);
const u8 gMonFootprint_Alakazam[] = INCBIN_U8("assets/graphics.bin", 0xC7EA8, 0x20);

const u32 gMonFrontPic_Machop[] = INCBIN_U32("assets/graphics.bin", 0xC7EC8, 0x28C);
const u32 gMonPalette_Machop[] = INCBIN_U32("assets/graphics.bin", 0xC8154, 0x28);
const u32 gMonBackPic_Machop[] = INCBIN_U32("assets/graphics.bin", 0xC817C, 0x2E0);
const u32 gMonShinyPalette_Machop[] = INCBIN_U32("assets/graphics.bin", 0xC845C, 0x28);
const u8 gMonIcon_Machop[] = INCBIN_U8("assets/graphics.bin", 0xC8484, 0x400);
const u8 gMonFootprint_Machop[] = INCBIN_U8("assets/graphics.bin", 0xC8884, 0x20);

const u32 gMonFrontPic_Machoke[] = INCBIN_U32("assets/graphics.bin", 0xC88A4, 0x3CC);
const u32 gMonPalette_Machoke[] = INCBIN_U32("assets/graphics.bin", 0xC8C70, 0x28);
const u32 gMonBackPic_Machoke[] = INCBIN_U32("assets/graphics.bin", 0xC8C98, 0x350);
const u32 gMonShinyPalette_Machoke[] = INCBIN_U32("assets/graphics.bin", 0xC8FE8, 0x28);
const u8 gMonIcon_Machoke[] = INCBIN_U8("assets/graphics.bin", 0xC9010, 0x400);
const u8 gMonFootprint_Machoke[] = INCBIN_U8("assets/graphics.bin", 0xC9410, 0x20);

const u32 gMonFrontPic_Machamp[] = INCBIN_U32("assets/graphics.bin", 0xC9430, 0x4EC);
const u32 gMonPalette_Machamp[] = INCBIN_U32("assets/graphics.bin", 0xC991C, 0x28);
const u32 gMonBackPic_Machamp[] = INCBIN_U32("assets/graphics.bin", 0xC9944, 0x45C);
const u32 gMonShinyPalette_Machamp[] = INCBIN_U32("assets/graphics.bin", 0xC9DA0, 0x28);
const u8 gMonIcon_Machamp[] = INCBIN_U8("assets/graphics.bin", 0xC9DC8, 0x400);
const u8 gMonFootprint_Machamp[] = INCBIN_U8("assets/graphics.bin", 0xCA1C8, 0x20);

const u32 gMonFrontPic_Bellsprout[] = INCBIN_U32("assets/graphics.bin", 0xCA1E8, 0x28C);
const u32 gMonPalette_Bellsprout[] = INCBIN_U32("assets/graphics.bin", 0xCA474, 0x28);
const u32 gMonBackPic_Bellsprout[] = INCBIN_U32("assets/graphics.bin", 0xCA49C, 0x29C);
const u32 gMonShinyPalette_Bellsprout[] = INCBIN_U32("assets/graphics.bin", 0xCA738, 0x28);
const u8 gMonIcon_Bellsprout[] = INCBIN_U8("assets/graphics.bin", 0xCA760, 0x400);
const u8 gMonFootprint_Bellsprout[] = INCBIN_U8("assets/graphics.bin", 0xCAB60, 0x20);

const u32 gMonFrontPic_Weepinbell[] = INCBIN_U32("assets/graphics.bin", 0xCAB80, 0x324);
const u32 gMonPalette_Weepinbell[] = INCBIN_U32("assets/graphics.bin", 0xCAEA4, 0x28);
const u32 gMonBackPic_Weepinbell[] = INCBIN_U32("assets/graphics.bin", 0xCAECC, 0x2FC);
const u32 gMonShinyPalette_Weepinbell[] = INCBIN_U32("assets/graphics.bin", 0xCB1C8, 0x28);
const u8 gMonIcon_Weepinbell[] = INCBIN_U8("assets/graphics.bin", 0xCB1F0, 0x400);
const u8 gMonFootprint_Weepinbell[] = INCBIN_U8("assets/graphics.bin", 0xCB5F0, 0x20);

const u32 gMonFrontPic_Victreebel[] = INCBIN_U32("assets/graphics.bin", 0xCB610, 0x42C);
const u32 gMonPalette_Victreebel[] = INCBIN_U32("assets/graphics.bin", 0xCBA3C, 0x28);
const u32 gMonBackPic_Victreebel[] = INCBIN_U32("assets/graphics.bin", 0xCBA64, 0x398);
const u32 gMonShinyPalette_Victreebel[] = INCBIN_U32("assets/graphics.bin", 0xCBDFC, 0x28);
const u8 gMonIcon_Victreebel[] = INCBIN_U8("assets/graphics.bin", 0xCBE24, 0x400);
const u8 gMonFootprint_Victreebel[] = INCBIN_U8("assets/graphics.bin", 0xCC224, 0x20);

const u32 gMonFrontPic_Tentacool[] = INCBIN_U32("assets/graphics.bin", 0xCC244, 0x2A8);
const u32 gMonPalette_Tentacool[] = INCBIN_U32("assets/graphics.bin", 0xCC4EC, 0x28);
const u32 gMonBackPic_Tentacool[] = INCBIN_U32("assets/graphics.bin", 0xCC514, 0x2CC);
const u32 gMonShinyPalette_Tentacool[] = INCBIN_U32("assets/graphics.bin", 0xCC7E0, 0x28);
const u8 gMonIcon_Tentacool[] = INCBIN_U8("assets/graphics.bin", 0xCC808, 0x400);
const u8 gMonFootprint_Tentacool[] = INCBIN_U8("assets/graphics.bin", 0xCCC08, 0x20);

const u32 gMonFrontPic_Tentacruel[] = INCBIN_U32("assets/graphics.bin", 0xCCC28, 0x4F4);
const u32 gMonPalette_Tentacruel[] = INCBIN_U32("assets/graphics.bin", 0xCD11C, 0x28);
const u32 gMonBackPic_Tentacruel[] = INCBIN_U32("assets/graphics.bin", 0xCD144, 0x39C);
const u32 gMonShinyPalette_Tentacruel[] = INCBIN_U32("assets/graphics.bin", 0xCD4E0, 0x28);
const u8 gMonIcon_Tentacruel[] = INCBIN_U8("assets/graphics.bin", 0xCD508, 0x400);
const u8 gMonFootprint_Tentacruel[] = INCBIN_U8("assets/graphics.bin", 0xCD908, 0x20);

const u32 gMonFrontPic_Geodude[] = INCBIN_U32("assets/graphics.bin", 0xCD928, 0x294);
const u32 gMonPalette_Geodude[] = INCBIN_U32("assets/graphics.bin", 0xCDBBC, 0x1C);
const u32 gMonBackPic_Geodude[] = INCBIN_U32("assets/graphics.bin", 0xCDBD8, 0x294);
const u32 gMonShinyPalette_Geodude[] = INCBIN_U32("assets/graphics.bin", 0xCDE6C, 0x1C);
const u8 gMonIcon_Geodude[] = INCBIN_U8("assets/graphics.bin", 0xCDE88, 0x400);
const u8 gMonFootprint_Geodude[] = INCBIN_U8("assets/graphics.bin", 0xCE288, 0x20);

const u32 gMonFrontPic_Graveler[] = INCBIN_U32("assets/graphics.bin", 0xCE2A8, 0x3FC);
const u32 gMonPalette_Graveler[] = INCBIN_U32("assets/graphics.bin", 0xCE6A4, 0x24);
const u32 gMonBackPic_Graveler[] = INCBIN_U32("assets/graphics.bin", 0xCE6C8, 0x27C);
const u32 gMonShinyPalette_Graveler[] = INCBIN_U32("assets/graphics.bin", 0xCE944, 0x24);
const u8 gMonIcon_Graveler[] = INCBIN_U8("assets/graphics.bin", 0xCE968, 0x400);
const u8 gMonFootprint_Graveler[] = INCBIN_U8("assets/graphics.bin", 0xCED68, 0x20);

const u32 gMonFrontPic_Golem[] = INCBIN_U32("assets/graphics.bin", 0xCED88, 0x430);
const u32 gMonPalette_Golem[] = INCBIN_U32("assets/graphics.bin", 0xCF1B8, 0x28);
const u32 gMonBackPic_Golem[] = INCBIN_U32("assets/graphics.bin", 0xCF1E0, 0x2C0);
const u32 gMonShinyPalette_Golem[] = INCBIN_U32("assets/graphics.bin", 0xCF4A0, 0x28);
const u8 gMonIcon_Golem[] = INCBIN_U8("assets/graphics.bin", 0xCF4C8, 0x400);
const u8 gMonFootprint_Golem[] = INCBIN_U8("assets/graphics.bin", 0xCF8C8, 0x20);

const u32 gMonFrontPic_Ponyta[] = INCBIN_U32("assets/graphics.bin", 0xCF8E8, 0x390);
const u32 gMonPalette_Ponyta[] = INCBIN_U32("assets/graphics.bin", 0xCFC78, 0x28);
const u32 gMonBackPic_Ponyta[] = INCBIN_U32("assets/graphics.bin", 0xCFCA0, 0x33C);
const u32 gMonShinyPalette_Ponyta[] = INCBIN_U32("assets/graphics.bin", 0xCFFDC, 0x28);
const u8 gMonIcon_Ponyta[] = INCBIN_U8("assets/graphics.bin", 0xD0004, 0x400);
const u8 gMonFootprint_Ponyta[] = INCBIN_U8("assets/graphics.bin", 0xD0404, 0x20);

const u32 gMonFrontPic_Rapidash[] = INCBIN_U32("assets/graphics.bin", 0xD0424, 0x488);
const u32 gMonPalette_Rapidash[] = INCBIN_U32("assets/graphics.bin", 0xD08AC, 0x28);
const u32 gMonBackPic_Rapidash[] = INCBIN_U32("assets/graphics.bin", 0xD08D4, 0x410);
const u32 gMonShinyPalette_Rapidash[] = INCBIN_U32("assets/graphics.bin", 0xD0CE4, 0x28);
const u8 gMonIcon_Rapidash[] = INCBIN_U8("assets/graphics.bin", 0xD0D0C, 0x400);
const u8 gMonFootprint_Rapidash[] = INCBIN_U8("assets/graphics.bin", 0xD110C, 0x20);

const u32 gMonFrontPic_Slowpoke[] = INCBIN_U32("assets/graphics.bin", 0xD112C, 0x2D4);
const u32 gMonPalette_Slowpoke[] = INCBIN_U32("assets/graphics.bin", 0xD1400, 0x28);
const u32 gMonBackPic_Slowpoke[] = INCBIN_U32("assets/graphics.bin", 0xD1428, 0x264);
const u32 gMonShinyPalette_Slowpoke[] = INCBIN_U32("assets/graphics.bin", 0xD168C, 0x28);
const u8 gMonIcon_Slowpoke[] = INCBIN_U8("assets/graphics.bin", 0xD16B4, 0x400);
const u8 gMonFootprint_Slowpoke[] = INCBIN_U8("assets/graphics.bin", 0xD1AB4, 0x20);

const u32 gMonFrontPic_Slowbro[] = INCBIN_U32("assets/graphics.bin", 0xD1AD4, 0x4A0);
const u32 gMonPalette_Slowbro[] = INCBIN_U32("assets/graphics.bin", 0xD1F74, 0x28);
const u32 gMonBackPic_Slowbro[] = INCBIN_U32("assets/graphics.bin", 0xD1F9C, 0x39C);
const u32 gMonShinyPalette_Slowbro[] = INCBIN_U32("assets/graphics.bin", 0xD2338, 0x28);
const u8 gMonIcon_Slowbro[] = INCBIN_U8("assets/graphics.bin", 0xD2360, 0x400);
const u8 gMonFootprint_Slowbro[] = INCBIN_U8("assets/graphics.bin", 0xD2760, 0x20);

const u32 gMonFrontPic_Magnemite[] = INCBIN_U32("assets/graphics.bin", 0xD2780, 0x1D8);
const u32 gMonPalette_Magnemite[] = INCBIN_U32("assets/graphics.bin", 0xD2958, 0x28);
const u32 gMonBackPic_Magnemite[] = INCBIN_U32("assets/graphics.bin", 0xD2980, 0x1E8);
const u32 gMonShinyPalette_Magnemite[] = INCBIN_U32("assets/graphics.bin", 0xD2B68, 0x24);
const u8 gMonIcon_Magnemite[] = INCBIN_U8("assets/graphics.bin", 0xD2B8C, 0x400);
const u8 gMonFootprint_Magnemite[] = INCBIN_U8("assets/graphics.bin", 0xD2F8C, 0x20);

const u32 gMonFrontPic_Magneton[] = INCBIN_U32("assets/graphics.bin", 0xD2FAC, 0x33C);
const u32 gMonPalette_Magneton[] = INCBIN_U32("assets/graphics.bin", 0xD32E8, 0x28);
const u32 gMonBackPic_Magneton[] = INCBIN_U32("assets/graphics.bin", 0xD3310, 0x380);
const u32 gMonShinyPalette_Magneton[] = INCBIN_U32("assets/graphics.bin", 0xD3690, 0x28);
const u8 gMonIcon_Magneton[] = INCBIN_U8("assets/graphics.bin", 0xD36B8, 0x400);
const u8 gMonFootprint_Magneton[] = INCBIN_U8("assets/graphics.bin", 0xD3AB8, 0x20);

const u32 gMonFrontPic_Farfetchd[] = INCBIN_U32("assets/graphics.bin", 0xD3AD8, 0x354);
const u32 gMonPalette_Farfetchd[] = INCBIN_U32("assets/graphics.bin", 0xD3E2C, 0x28);
const u32 gMonBackPic_Farfetchd[] = INCBIN_U32("assets/graphics.bin", 0xD3E54, 0x36C);
const u32 gMonShinyPalette_Farfetchd[] = INCBIN_U32("assets/graphics.bin", 0xD41C0, 0x28);
const u8 gMonIcon_Farfetchd[] = INCBIN_U8("assets/graphics.bin", 0xD41E8, 0x400);
const u8 gMonFootprint_Farfetchd[] = INCBIN_U8("assets/graphics.bin", 0xD45E8, 0x20);

const u32 gMonFrontPic_Doduo[] = INCBIN_U32("assets/graphics.bin", 0xD4608, 0x2EC);
const u32 gMonPalette_Doduo[] = INCBIN_U32("assets/graphics.bin", 0xD48F4, 0x24);
const u32 gMonBackPic_Doduo[] = INCBIN_U32("assets/graphics.bin", 0xD4918, 0x318);
const u32 gMonShinyPalette_Doduo[] = INCBIN_U32("assets/graphics.bin", 0xD4C30, 0x24);
const u8 gMonIcon_Doduo[] = INCBIN_U8("assets/graphics.bin", 0xD4C54, 0x400);
const u8 gMonFootprint_Doduo[] = INCBIN_U8("assets/graphics.bin", 0xD5054, 0x20);

const u32 gMonFrontPic_Dodrio[] = INCBIN_U32("assets/graphics.bin", 0xD5074, 0x440);
const u32 gMonPalette_Dodrio[] = INCBIN_U32("assets/graphics.bin", 0xD54B4, 0x28);
const u32 gMonBackPic_Dodrio[] = INCBIN_U32("assets/graphics.bin", 0xD54DC, 0x464);
const u32 gMonShinyPalette_Dodrio[] = INCBIN_U32("assets/graphics.bin", 0xD5940, 0x28);
const u8 gMonIcon_Dodrio[] = INCBIN_U8("assets/graphics.bin", 0xD5968, 0x400);
const u8 gMonFootprint_Dodrio[] = INCBIN_U8("assets/graphics.bin", 0xD5D68, 0x20);

const u32 gMonFrontPic_Seel[] = INCBIN_U32("assets/graphics.bin", 0xD5D88, 0x324);
const u32 gMonPalette_Seel[] = INCBIN_U32("assets/graphics.bin", 0xD60AC, 0x28);
const u32 gMonBackPic_Seel[] = INCBIN_U32("assets/graphics.bin", 0xD60D4, 0x2EC);
const u32 gMonShinyPalette_Seel[] = INCBIN_U32("assets/graphics.bin", 0xD63C0, 0x28);
const u8 gMonIcon_Seel[] = INCBIN_U8("assets/graphics.bin", 0xD63E8, 0x400);
const u8 gMonFootprint_Seel[] = INCBIN_U8("assets/graphics.bin", 0xD67E8, 0x20);

const u32 gMonFrontPic_Dewgong[] = INCBIN_U32("assets/graphics.bin", 0xD6808, 0x3D0);
const u32 gMonPalette_Dewgong[] = INCBIN_U32("assets/graphics.bin", 0xD6BD8, 0x24);
const u32 gMonBackPic_Dewgong[] = INCBIN_U32("assets/graphics.bin", 0xD6BFC, 0x294);
const u32 gMonShinyPalette_Dewgong[] = INCBIN_U32("assets/graphics.bin", 0xD6E90, 0x24);
const u8 gMonIcon_Dewgong[] = INCBIN_U8("assets/graphics.bin", 0xD6EB4, 0x400);
const u8 gMonFootprint_Dewgong[] = INCBIN_U8("assets/graphics.bin", 0xD72B4, 0x20);

const u32 gMonFrontPic_Grimer[] = INCBIN_U32("assets/graphics.bin", 0xD72D4, 0x328);
const u32 gMonPalette_Grimer[] = INCBIN_U32("assets/graphics.bin", 0xD75FC, 0x24);
const u32 gMonBackPic_Grimer[] = INCBIN_U32("assets/graphics.bin", 0xD7620, 0x2C4);
const u32 gMonShinyPalette_Grimer[] = INCBIN_U32("assets/graphics.bin", 0xD78E4, 0x24);
const u8 gMonIcon_Grimer[] = INCBIN_U8("assets/graphics.bin", 0xD7908, 0x400);
const u8 gMonFootprint_Grimer[] = INCBIN_U8("assets/graphics.bin", 0xD7D08, 0x20);

const u32 gMonFrontPic_Muk[] = INCBIN_U32("assets/graphics.bin", 0xD7D28, 0x390);
const u32 gMonPalette_Muk[] = INCBIN_U32("assets/graphics.bin", 0xD80B8, 0x24);
const u32 gMonBackPic_Muk[] = INCBIN_U32("assets/graphics.bin", 0xD80DC, 0x2F8);
const u32 gMonShinyPalette_Muk[] = INCBIN_U32("assets/graphics.bin", 0xD83D4, 0x24);
const u8 gMonIcon_Muk[] = INCBIN_U8("assets/graphics.bin", 0xD83F8, 0x400);
const u8 gMonFootprint_Muk[] = INCBIN_U8("assets/graphics.bin", 0xD87F8, 0x20);

const u32 gMonFrontPic_Shellder[] = INCBIN_U32("assets/graphics.bin", 0xD8818, 0x274);
const u32 gMonPalette_Shellder[] = INCBIN_U32("assets/graphics.bin", 0xD8A8C, 0x24);
const u32 gMonBackPic_Shellder[] = INCBIN_U32("assets/graphics.bin", 0xD8AB0, 0x314);
const u32 gMonShinyPalette_Shellder[] = INCBIN_U32("assets/graphics.bin", 0xD8DC4, 0x24);
const u8 gMonIcon_Shellder[] = INCBIN_U8("assets/graphics.bin", 0xD8DE8, 0x400);
const u8 gMonFootprint_Shellder[] = INCBIN_U8("assets/graphics.bin", 0xD91E8, 0x20);

const u32 gMonFrontPic_Cloyster[] = INCBIN_U32("assets/graphics.bin", 0xD9208, 0x43C);
const u32 gMonPalette_Cloyster[] = INCBIN_U32("assets/graphics.bin", 0xD9644, 0x24);
const u32 gMonBackPic_Cloyster[] = INCBIN_U32("assets/graphics.bin", 0xD9668, 0x40C);
const u32 gMonShinyPalette_Cloyster[] = INCBIN_U32("assets/graphics.bin", 0xD9A74, 0x24);
const u8 gMonIcon_Cloyster[] = INCBIN_U8("assets/graphics.bin", 0xD9A98, 0x400);
const u8 gMonFootprint_Cloyster[] = INCBIN_U8("assets/graphics.bin", 0xD9E98, 0x20);

const u32 gMonFrontPic_Gastly[] = INCBIN_U32("assets/graphics.bin", 0xD9EB8, 0x3B8);
const u32 gMonPalette_Gastly[] = INCBIN_U32("assets/graphics.bin", 0xDA270, 0x28);
const u32 gMonBackPic_Gastly[] = INCBIN_U32("assets/graphics.bin", 0xDA298, 0x324);
const u32 gMonShinyPalette_Gastly[] = INCBIN_U32("assets/graphics.bin", 0xDA5BC, 0x28);
const u8 gMonIcon_Gastly[] = INCBIN_U8("assets/graphics.bin", 0xDA5E4, 0x400);
const u8 gMonFootprint_Gastly[] = INCBIN_U8("assets/graphics.bin", 0xDA9E4, 0x20);

const u32 gMonFrontPic_Haunter[] = INCBIN_U32("assets/graphics.bin", 0xDAA04, 0x3E8);
const u32 gMonPalette_Haunter[] = INCBIN_U32("assets/graphics.bin", 0xDADEC, 0x24);
const u32 gMonBackPic_Haunter[] = INCBIN_U32("assets/graphics.bin", 0xDAE10, 0x2E4);
const u32 gMonShinyPalette_Haunter[] = INCBIN_U32("assets/graphics.bin", 0xDB0F4, 0x24);
const u8 gMonIcon_Haunter[] = INCBIN_U8("assets/graphics.bin", 0xDB118, 0x400);
const u8 gMonFootprint_Haunter[] = INCBIN_U8("assets/graphics.bin", 0xDB518, 0x20);

const u32 gMonFrontPic_Gengar[] = INCBIN_U32("assets/graphics.bin", 0xDB538, 0x35C);
const u32 gMonPalette_Gengar[] = INCBIN_U32("assets/graphics.bin", 0xDB894, 0x24);
const u32 gMonBackPic_Gengar[] = INCBIN_U32("assets/graphics.bin", 0xDB8B8, 0x344);
const u32 gMonShinyPalette_Gengar[] = INCBIN_U32("assets/graphics.bin", 0xDBBFC, 0x24);
const u8 gMonIcon_Gengar[] = INCBIN_U8("assets/graphics.bin", 0xDBC20, 0x400);
const u8 gMonFootprint_Gengar[] = INCBIN_U8("assets/graphics.bin", 0xDC020, 0x20);

const u32 gMonFrontPic_Onix[] = INCBIN_U32("assets/graphics.bin", 0xDC040, 0x4D0);
const u32 gMonPalette_Onix[] = INCBIN_U32("assets/graphics.bin", 0xDC510, 0x1C);
const u32 gMonBackPic_Onix[] = INCBIN_U32("assets/graphics.bin", 0xDC52C, 0x37C);
const u32 gMonShinyPalette_Onix[] = INCBIN_U32("assets/graphics.bin", 0xDC8A8, 0x1C);
const u8 gMonIcon_Onix[] = INCBIN_U8("assets/graphics.bin", 0xDC8C4, 0x400);
const u8 gMonFootprint_Onix[] = INCBIN_U8("assets/graphics.bin", 0xDCCC4, 0x20);

const u32 gMonFrontPic_Drowzee[] = INCBIN_U32("assets/graphics.bin", 0xDCCE4, 0x340);
const u32 gMonPalette_Drowzee[] = INCBIN_U32("assets/graphics.bin", 0xDD024, 0x24);
const u32 gMonBackPic_Drowzee[] = INCBIN_U32("assets/graphics.bin", 0xDD048, 0x23C);
const u32 gMonShinyPalette_Drowzee[] = INCBIN_U32("assets/graphics.bin", 0xDD284, 0x24);
const u8 gMonIcon_Drowzee[] = INCBIN_U8("assets/graphics.bin", 0xDD2A8, 0x400);
const u8 gMonFootprint_Drowzee[] = INCBIN_U8("assets/graphics.bin", 0xDD6A8, 0x20);

const u32 gMonFrontPic_Hypno[] = INCBIN_U32("assets/graphics.bin", 0xDD6C8, 0x438);
const u32 gMonPalette_Hypno[] = INCBIN_U32("assets/graphics.bin", 0xDDB00, 0x24);
const u32 gMonBackPic_Hypno[] = INCBIN_U32("assets/graphics.bin", 0xDDB24, 0x330);
const u32 gMonShinyPalette_Hypno[] = INCBIN_U32("assets/graphics.bin", 0xDDE54, 0x24);
const u8 gMonIcon_Hypno[] = INCBIN_U8("assets/graphics.bin", 0xDDE78, 0x400);
const u8 gMonFootprint_Hypno[] = INCBIN_U8("assets/graphics.bin", 0xDE278, 0x20);

const u32 gMonFrontPic_Krabby[] = INCBIN_U32("assets/graphics.bin", 0xDE298, 0x324);
const u32 gMonPalette_Krabby[] = INCBIN_U32("assets/graphics.bin", 0xDE5BC, 0x28);
const u32 gMonBackPic_Krabby[] = INCBIN_U32("assets/graphics.bin", 0xDE5E4, 0x38C);
const u32 gMonShinyPalette_Krabby[] = INCBIN_U32("assets/graphics.bin", 0xDE970, 0x28);
const u8 gMonIcon_Krabby[] = INCBIN_U8("assets/graphics.bin", 0xDE998, 0x400);
const u8 gMonFootprint_Krabby[] = INCBIN_U8("assets/graphics.bin", 0xDED98, 0x20);

const u32 gMonFrontPic_Kingler[] = INCBIN_U32("assets/graphics.bin", 0xDEDB8, 0x480);
const u32 gMonPalette_Kingler[] = INCBIN_U32("assets/graphics.bin", 0xDF238, 0x28);
const u32 gMonBackPic_Kingler[] = INCBIN_U32("assets/graphics.bin", 0xDF260, 0x384);
const u32 gMonShinyPalette_Kingler[] = INCBIN_U32("assets/graphics.bin", 0xDF5E4, 0x28);
const u8 gMonIcon_Kingler[] = INCBIN_U8("assets/graphics.bin", 0xDF60C, 0x400);
const u8 gMonFootprint_Kingler[] = INCBIN_U8("assets/graphics.bin", 0xDFA0C, 0x20);

const u32 gMonFrontPic_Voltorb[] = INCBIN_U32("assets/graphics.bin", 0xDFA2C, 0x208);
const u32 gMonPalette_Voltorb[] = INCBIN_U32("assets/graphics.bin", 0xDFC34, 0x24);
const u32 gMonBackPic_Voltorb[] = INCBIN_U32("assets/graphics.bin", 0xDFC58, 0x274);
const u32 gMonShinyPalette_Voltorb[] = INCBIN_U32("assets/graphics.bin", 0xDFECC, 0x24);
const u8 gMonIcon_Voltorb[] = INCBIN_U8("assets/graphics.bin", 0xDFEF0, 0x400);
const u8 gMonFootprint_Voltorb[] = INCBIN_U8("assets/graphics.bin", 0xE02F0, 0x20);

const u32 gMonFrontPic_Electrode[] = INCBIN_U32("assets/graphics.bin", 0xE0310, 0x26C);
const u32 gMonPalette_Electrode[] = INCBIN_U32("assets/graphics.bin", 0xE057C, 0x24);
const u32 gMonBackPic_Electrode[] = INCBIN_U32("assets/graphics.bin", 0xE05A0, 0x270);
const u32 gMonShinyPalette_Electrode[] = INCBIN_U32("assets/graphics.bin", 0xE0810, 0x24);
const u8 gMonIcon_Electrode[] = INCBIN_U8("assets/graphics.bin", 0xE0834, 0x400);
const u8 gMonFootprint_Electrode[] = INCBIN_U8("assets/graphics.bin", 0xE0C34, 0x20);

const u32 gMonFrontPic_Exeggcute[] = INCBIN_U32("assets/graphics.bin", 0xE0C54, 0x390);
const u32 gMonPalette_Exeggcute[] = INCBIN_U32("assets/graphics.bin", 0xE0FE4, 0x24);
const u32 gMonBackPic_Exeggcute[] = INCBIN_U32("assets/graphics.bin", 0xE1008, 0x308);
const u32 gMonShinyPalette_Exeggcute[] = INCBIN_U32("assets/graphics.bin", 0xE1310, 0x24);
const u8 gMonIcon_Exeggcute[] = INCBIN_U8("assets/graphics.bin", 0xE1334, 0x400);
const u8 gMonFootprint_Exeggcute[] = INCBIN_U8("assets/graphics.bin", 0xE1734, 0x20);

const u32 gMonFrontPic_Exeggutor[] = INCBIN_U32("assets/graphics.bin", 0xE1754, 0x450);
const u32 gMonPalette_Exeggutor[] = INCBIN_U32("assets/graphics.bin", 0xE1BA4, 0x28);
const u32 gMonBackPic_Exeggutor[] = INCBIN_U32("assets/graphics.bin", 0xE1BCC, 0x3CC);
const u32 gMonShinyPalette_Exeggutor[] = INCBIN_U32("assets/graphics.bin", 0xE1F98, 0x28);
const u8 gMonIcon_Exeggutor[] = INCBIN_U8("assets/graphics.bin", 0xE1FC0, 0x400);
const u8 gMonFootprint_Exeggutor[] = INCBIN_U8("assets/graphics.bin", 0xE23C0, 0x20);

const u32 gMonFrontPic_Cubone[] = INCBIN_U32("assets/graphics.bin", 0xE23E0, 0x2BC);
const u32 gMonPalette_Cubone[] = INCBIN_U32("assets/graphics.bin", 0xE269C, 0x28);
const u32 gMonBackPic_Cubone[] = INCBIN_U32("assets/graphics.bin", 0xE26C4, 0x340);
const u32 gMonShinyPalette_Cubone[] = INCBIN_U32("assets/graphics.bin", 0xE2A04, 0x28);
const u8 gMonIcon_Cubone[] = INCBIN_U8("assets/graphics.bin", 0xE2A2C, 0x400);
const u8 gMonFootprint_Cubone[] = INCBIN_U8("assets/graphics.bin", 0xE2E2C, 0x20);

const u32 gMonFrontPic_Marowak[] = INCBIN_U32("assets/graphics.bin", 0xE2E4C, 0x380);
const u32 gMonPalette_Marowak[] = INCBIN_U32("assets/graphics.bin", 0xE31CC, 0x28);
const u32 gMonBackPic_Marowak[] = INCBIN_U32("assets/graphics.bin", 0xE31F4, 0x314);
const u32 gMonShinyPalette_Marowak[] = INCBIN_U32("assets/graphics.bin", 0xE3508, 0x28);
const u8 gMonIcon_Marowak[] = INCBIN_U8("assets/graphics.bin", 0xE3530, 0x400);
const u8 gMonFootprint_Marowak[] = INCBIN_U8("assets/graphics.bin", 0xE3930, 0x20);

const u32 gMonFrontPic_Hitmonlee[] = INCBIN_U32("assets/graphics.bin", 0xE3950, 0x374);
const u32 gMonPalette_Hitmonlee[] = INCBIN_U32("assets/graphics.bin", 0xE3CC4, 0x28);
const u32 gMonBackPic_Hitmonlee[] = INCBIN_U32("assets/graphics.bin", 0xE3CEC, 0x2A4);
const u32 gMonShinyPalette_Hitmonlee[] = INCBIN_U32("assets/graphics.bin", 0xE3F90, 0x28);
const u8 gMonIcon_Hitmonlee[] = INCBIN_U8("assets/graphics.bin", 0xE3FB8, 0x400);
const u8 gMonFootprint_Hitmonlee[] = INCBIN_U8("assets/graphics.bin", 0xE43B8, 0x20);

const u32 gMonFrontPic_Hitmonchan[] = INCBIN_U32("assets/graphics.bin", 0xE43D8, 0x340);
const u32 gMonPalette_Hitmonchan[] = INCBIN_U32("assets/graphics.bin", 0xE4718, 0x28);
const u32 gMonBackPic_Hitmonchan[] = INCBIN_U32("assets/graphics.bin", 0xE4740, 0x344);
const u32 gMonShinyPalette_Hitmonchan[] = INCBIN_U32("assets/graphics.bin", 0xE4A84, 0x28);
const u8 gMonIcon_Hitmonchan[] = INCBIN_U8("assets/graphics.bin", 0xE4AAC, 0x400);
const u8 gMonFootprint_Hitmonchan[] = INCBIN_U8("assets/graphics.bin", 0xE4EAC, 0x20);

const u32 gMonFrontPic_Lickitung[] = INCBIN_U32("assets/graphics.bin", 0xE4ECC, 0x3D8);
const u32 gMonPalette_Lickitung[] = INCBIN_U32("assets/graphics.bin", 0xE52A4, 0x28);
const u32 gMonBackPic_Lickitung[] = INCBIN_U32("assets/graphics.bin", 0xE52CC, 0x2A4);
const u32 gMonShinyPalette_Lickitung[] = INCBIN_U32("assets/graphics.bin", 0xE5570, 0x28);
const u8 gMonIcon_Lickitung[] = INCBIN_U8("assets/graphics.bin", 0xE5598, 0x400);
const u8 gMonFootprint_Lickitung[] = INCBIN_U8("assets/graphics.bin", 0xE5998, 0x20);

const u32 gMonFrontPic_Koffing[] = INCBIN_U32("assets/graphics.bin", 0xE59B8, 0x300);
const u32 gMonPalette_Koffing[] = INCBIN_U32("assets/graphics.bin", 0xE5CB8, 0x28);
const u32 gMonBackPic_Koffing[] = INCBIN_U32("assets/graphics.bin", 0xE5CE0, 0x300);
const u32 gMonShinyPalette_Koffing[] = INCBIN_U32("assets/graphics.bin", 0xE5FE0, 0x28);
const u8 gMonIcon_Koffing[] = INCBIN_U8("assets/graphics.bin", 0xE6008, 0x400);
const u8 gMonFootprint_Koffing[] = INCBIN_U8("assets/graphics.bin", 0xE6408, 0x20);

const u32 gMonFrontPic_Weezing[] = INCBIN_U32("assets/graphics.bin", 0xE6428, 0x4BC);
const u32 gMonPalette_Weezing[] = INCBIN_U32("assets/graphics.bin", 0xE68E4, 0x28);
const u32 gMonBackPic_Weezing[] = INCBIN_U32("assets/graphics.bin", 0xE690C, 0x384);
const u32 gMonShinyPalette_Weezing[] = INCBIN_U32("assets/graphics.bin", 0xE6C90, 0x28);
const u8 gMonIcon_Weezing[] = INCBIN_U8("assets/graphics.bin", 0xE6CB8, 0x400);
const u8 gMonFootprint_Weezing[] = INCBIN_U8("assets/graphics.bin", 0xE70B8, 0x20);

const u32 gMonFrontPic_Rhyhorn[] = INCBIN_U32("assets/graphics.bin", 0xE70D8, 0x3FC);
const u32 gMonPalette_Rhyhorn[] = INCBIN_U32("assets/graphics.bin", 0xE74D4, 0x20);
const u32 gMonBackPic_Rhyhorn[] = INCBIN_U32("assets/graphics.bin", 0xE74F4, 0x348);
const u32 gMonShinyPalette_Rhyhorn[] = INCBIN_U32("assets/graphics.bin", 0xE783C, 0x20);
const u8 gMonIcon_Rhyhorn[] = INCBIN_U8("assets/graphics.bin", 0xE785C, 0x400);
const u8 gMonFootprint_Rhyhorn[] = INCBIN_U8("assets/graphics.bin", 0xE7C5C, 0x20);

const u32 gMonFrontPic_Rhydon[] = INCBIN_U32("assets/graphics.bin", 0xE7C7C, 0x4F4);
const u32 gMonPalette_Rhydon[] = INCBIN_U32("assets/graphics.bin", 0xE8170, 0x28);
const u32 gMonBackPic_Rhydon[] = INCBIN_U32("assets/graphics.bin", 0xE8198, 0x450);
const u32 gMonShinyPalette_Rhydon[] = INCBIN_U32("assets/graphics.bin", 0xE85E8, 0x28);
const u8 gMonIcon_Rhydon[] = INCBIN_U8("assets/graphics.bin", 0xE8610, 0x400);
const u8 gMonFootprint_Rhydon[] = INCBIN_U8("assets/graphics.bin", 0xE8A10, 0x20);

const u32 gMonFrontPic_Chansey[] = INCBIN_U32("assets/graphics.bin", 0xE8A30, 0x33C);
const u32 gMonPalette_Chansey[] = INCBIN_U32("assets/graphics.bin", 0xE8D6C, 0x24);
const u32 gMonBackPic_Chansey[] = INCBIN_U32("assets/graphics.bin", 0xE8D90, 0x250);
const u32 gMonShinyPalette_Chansey[] = INCBIN_U32("assets/graphics.bin", 0xE8FE0, 0x24);
const u8 gMonIcon_Chansey[] = INCBIN_U8("assets/graphics.bin", 0xE9004, 0x400);
const u8 gMonFootprint_Chansey[] = INCBIN_U8("assets/graphics.bin", 0xE9404, 0x20);

const u32 gMonFrontPic_Tangela[] = INCBIN_U32("assets/graphics.bin", 0xE9424, 0x3D4);
const u32 gMonPalette_Tangela[] = INCBIN_U32("assets/graphics.bin", 0xE97F8, 0x24);
const u32 gMonBackPic_Tangela[] = INCBIN_U32("assets/graphics.bin", 0xE981C, 0x3AC);
const u32 gMonShinyPalette_Tangela[] = INCBIN_U32("assets/graphics.bin", 0xE9BC8, 0x24);
const u8 gMonIcon_Tangela[] = INCBIN_U8("assets/graphics.bin", 0xE9BEC, 0x400);
const u8 gMonFootprint_Tangela[] = INCBIN_U8("assets/graphics.bin", 0xE9FEC, 0x20);

const u32 gMonFrontPic_Kangaskhan[] = INCBIN_U32("assets/graphics.bin", 0xEA00C, 0x4A8);
const u32 gMonPalette_Kangaskhan[] = INCBIN_U32("assets/graphics.bin", 0xEA4B4, 0x28);
const u32 gMonBackPic_Kangaskhan[] = INCBIN_U32("assets/graphics.bin", 0xEA4DC, 0x430);
const u32 gMonShinyPalette_Kangaskhan[] = INCBIN_U32("assets/graphics.bin", 0xEA90C, 0x28);
const u8 gMonIcon_Kangaskhan[] = INCBIN_U8("assets/graphics.bin", 0xEA934, 0x400);
const u8 gMonFootprint_Kangaskhan[] = INCBIN_U8("assets/graphics.bin", 0xEAD34, 0x20);

const u32 gMonFrontPic_Horsea[] = INCBIN_U32("assets/graphics.bin", 0xEAD54, 0x26C);
const u32 gMonPalette_Horsea[] = INCBIN_U32("assets/graphics.bin", 0xEAFC0, 0x28);
const u32 gMonBackPic_Horsea[] = INCBIN_U32("assets/graphics.bin", 0xEAFE8, 0x2E0);
const u32 gMonShinyPalette_Horsea[] = INCBIN_U32("assets/graphics.bin", 0xEB2C8, 0x28);
const u8 gMonIcon_Horsea[] = INCBIN_U8("assets/graphics.bin", 0xEB2F0, 0x400);
const u8 gMonFootprint_Horsea[] = INCBIN_U8("assets/graphics.bin", 0xEB6F0, 0x20);

const u32 gMonFrontPic_Seadra[] = INCBIN_U32("assets/graphics.bin", 0xEB710, 0x388);
const u32 gMonPalette_Seadra[] = INCBIN_U32("assets/graphics.bin", 0xEBA98, 0x28);
const u32 gMonBackPic_Seadra[] = INCBIN_U32("assets/graphics.bin", 0xEBAC0, 0x3A0);
const u32 gMonShinyPalette_Seadra[] = INCBIN_U32("assets/graphics.bin", 0xEBE60, 0x28);
const u8 gMonIcon_Seadra[] = INCBIN_U8("assets/graphics.bin", 0xEBE88, 0x400);
const u8 gMonFootprint_Seadra[] = INCBIN_U8("assets/graphics.bin", 0xEC288, 0x20);

const u32 gMonFrontPic_Goldeen[] = INCBIN_U32("assets/graphics.bin", 0xEC2A8, 0x368);
const u32 gMonPalette_Goldeen[] = INCBIN_U32("assets/graphics.bin", 0xEC610, 0x28);
const u32 gMonBackPic_Goldeen[] = INCBIN_U32("assets/graphics.bin", 0xEC638, 0x370);
const u32 gMonShinyPalette_Goldeen[] = INCBIN_U32("assets/graphics.bin", 0xEC9A8, 0x28);
const u8 gMonIcon_Goldeen[] = INCBIN_U8("assets/graphics.bin", 0xEC9D0, 0x400);
const u8 gMonFootprint_Goldeen[] = INCBIN_U8("assets/graphics.bin", 0xECDD0, 0x20);

const u32 gMonFrontPic_Seaking[] = INCBIN_U32("assets/graphics.bin", 0xECDF0, 0x474);
const u32 gMonPalette_Seaking[] = INCBIN_U32("assets/graphics.bin", 0xED264, 0x28);
const u32 gMonBackPic_Seaking[] = INCBIN_U32("assets/graphics.bin", 0xED28C, 0x350);
const u32 gMonShinyPalette_Seaking[] = INCBIN_U32("assets/graphics.bin", 0xED5DC, 0x28);
const u8 gMonIcon_Seaking[] = INCBIN_U8("assets/graphics.bin", 0xED604, 0x400);
const u8 gMonFootprint_Seaking[] = INCBIN_U8("assets/graphics.bin", 0xEDA04, 0x20);

const u32 gMonFrontPic_Staryu[] = INCBIN_U32("assets/graphics.bin", 0xEDA24, 0x2B0);
const u32 gMonPalette_Staryu[] = INCBIN_U32("assets/graphics.bin", 0xEDCD4, 0x28);
const u32 gMonBackPic_Staryu[] = INCBIN_U32("assets/graphics.bin", 0xEDCFC, 0x268);
const u32 gMonShinyPalette_Staryu[] = INCBIN_U32("assets/graphics.bin", 0xEDF64, 0x28);
const u8 gMonIcon_Staryu[] = INCBIN_U8("assets/graphics.bin", 0xEDF8C, 0x400);
const u8 gMonFootprint_Staryu[] = INCBIN_U8("assets/graphics.bin", 0xEE38C, 0x20);

const u32 gMonFrontPic_Starmie[] = INCBIN_U32("assets/graphics.bin", 0xEE3AC, 0x3A0);
const u32 gMonPalette_Starmie[] = INCBIN_U32("assets/graphics.bin", 0xEE74C, 0x28);
const u32 gMonBackPic_Starmie[] = INCBIN_U32("assets/graphics.bin", 0xEE774, 0x2A4);
const u32 gMonShinyPalette_Starmie[] = INCBIN_U32("assets/graphics.bin", 0xEEA18, 0x28);
const u8 gMonIcon_Starmie[] = INCBIN_U8("assets/graphics.bin", 0xEEA40, 0x400);
const u8 gMonFootprint_Starmie[] = INCBIN_U8("assets/graphics.bin", 0xEEE40, 0x20);

const u32 gMonFrontPic_Mrmime[] = INCBIN_U32("assets/graphics.bin", 0xEEE60, 0x3BC);
const u32 gMonPalette_Mrmime[] = INCBIN_U32("assets/graphics.bin", 0xEF21C, 0x28);
const u32 gMonBackPic_Mrmime[] = INCBIN_U32("assets/graphics.bin", 0xEF244, 0x334);
const u32 gMonShinyPalette_Mrmime[] = INCBIN_U32("assets/graphics.bin", 0xEF578, 0x28);
const u8 gMonIcon_Mrmime[] = INCBIN_U8("assets/graphics.bin", 0xEF5A0, 0x400);
const u8 gMonFootprint_Mrmime[] = INCBIN_U8("assets/graphics.bin", 0xEF9A0, 0x20);

const u32 gMonFrontPic_Scyther[] = INCBIN_U32("assets/graphics.bin", 0xEF9C0, 0x428);
const u32 gMonPalette_Scyther[] = INCBIN_U32("assets/graphics.bin", 0xEFDE8, 0x28);
const u32 gMonBackPic_Scyther[] = INCBIN_U32("assets/graphics.bin", 0xEFE10, 0x418);
const u32 gMonShinyPalette_Scyther[] = INCBIN_U32("assets/graphics.bin", 0xF0228, 0x28);
const u8 gMonIcon_Scyther[] = INCBIN_U8("assets/graphics.bin", 0xF0250, 0x400);
const u8 gMonFootprint_Scyther[] = INCBIN_U8("assets/graphics.bin", 0xF0650, 0x20);

const u32 gMonFrontPic_Jynx[] = INCBIN_U32("assets/graphics.bin", 0xF0670, 0x3CC);
const u32 gMonPalette_Jynx[] = INCBIN_U32("assets/graphics.bin", 0xF0A3C, 0x28);
const u32 gMonBackPic_Jynx[] = INCBIN_U32("assets/graphics.bin", 0xF0A64, 0x2EC);
const u32 gMonShinyPalette_Jynx[] = INCBIN_U32("assets/graphics.bin", 0xF0D50, 0x28);
const u8 gMonIcon_Jynx[] = INCBIN_U8("assets/graphics.bin", 0xF0D78, 0x400);
const u8 gMonFootprint_Jynx[] = INCBIN_U8("assets/graphics.bin", 0xF1178, 0x20);

const u32 gMonFrontPic_Electabuzz[] = INCBIN_U32("assets/graphics.bin", 0xF1198, 0x458);
const u32 gMonPalette_Electabuzz[] = INCBIN_U32("assets/graphics.bin", 0xF15F0, 0x28);
const u32 gMonBackPic_Electabuzz[] = INCBIN_U32("assets/graphics.bin", 0xF1618, 0x310);
const u32 gMonShinyPalette_Electabuzz[] = INCBIN_U32("assets/graphics.bin", 0xF1928, 0x28);
const u8 gMonIcon_Electabuzz[] = INCBIN_U8("assets/graphics.bin", 0xF1950, 0x400);
const u8 gMonFootprint_Electabuzz[] = INCBIN_U8("assets/graphics.bin", 0xF1D50, 0x20);

const u32 gMonFrontPic_Magmar[] = INCBIN_U32("assets/graphics.bin", 0xF1D70, 0x430);
const u32 gMonPalette_Magmar[] = INCBIN_U32("assets/graphics.bin", 0xF21A0, 0x28);
const u32 gMonBackPic_Magmar[] = INCBIN_U32("assets/graphics.bin", 0xF21C8, 0x338);
const u32 gMonShinyPalette_Magmar[] = INCBIN_U32("assets/graphics.bin", 0xF2500, 0x28);
const u8 gMonIcon_Magmar[] = INCBIN_U8("assets/graphics.bin", 0xF2528, 0x400);
const u8 gMonFootprint_Magmar[] = INCBIN_U8("assets/graphics.bin", 0xF2928, 0x20);

const u32 gMonFrontPic_Pinsir[] = INCBIN_U32("assets/graphics.bin", 0xF2948, 0x430);
const u32 gMonPalette_Pinsir[] = INCBIN_U32("assets/graphics.bin", 0xF2D78, 0x24);
const u32 gMonBackPic_Pinsir[] = INCBIN_U32("assets/graphics.bin", 0xF2D9C, 0x354);
const u32 gMonShinyPalette_Pinsir[] = INCBIN_U32("assets/graphics.bin", 0xF30F0, 0x24);
const u8 gMonIcon_Pinsir[] = INCBIN_U8("assets/graphics.bin", 0xF3114, 0x400);
const u8 gMonFootprint_Pinsir[] = INCBIN_U8("assets/graphics.bin", 0xF3514, 0x20);

const u32 gMonFrontPic_Tauros[] = INCBIN_U32("assets/graphics.bin", 0xF3534, 0x460);
const u32 gMonPalette_Tauros[] = INCBIN_U32("assets/graphics.bin", 0xF3994, 0x28);
const u32 gMonBackPic_Tauros[] = INCBIN_U32("assets/graphics.bin", 0xF39BC, 0x2B4);
const u32 gMonShinyPalette_Tauros[] = INCBIN_U32("assets/graphics.bin", 0xF3C70, 0x28);
const u8 gMonIcon_Tauros[] = INCBIN_U8("assets/graphics.bin", 0xF3C98, 0x400);
const u8 gMonFootprint_Tauros[] = INCBIN_U8("assets/graphics.bin", 0xF4098, 0x20);

const u32 gMonFrontPic_Magikarp[] = INCBIN_U32("assets/graphics.bin", 0xF40B8, 0x348);
const u32 gMonPalette_Magikarp[] = INCBIN_U32("assets/graphics.bin", 0xF4400, 0x28);
const u32 gMonBackPic_Magikarp[] = INCBIN_U32("assets/graphics.bin", 0xF4428, 0x330);
const u32 gMonShinyPalette_Magikarp[] = INCBIN_U32("assets/graphics.bin", 0xF4758, 0x28);
const u8 gMonIcon_Magikarp[] = INCBIN_U8("assets/graphics.bin", 0xF4780, 0x400);
const u8 gMonFootprint_Magikarp[] = INCBIN_U8("assets/graphics.bin", 0xF4B80, 0x20);

const u32 gMonFrontPic_Gyarados[] = INCBIN_U32("assets/graphics.bin", 0xF4BA0, 0x5A4);
const u32 gMonPalette_Gyarados[] = INCBIN_U32("assets/graphics.bin", 0xF5144, 0x28);
const u32 gMonBackPic_Gyarados[] = INCBIN_U32("assets/graphics.bin", 0xF516C, 0x4B8);
const u32 gMonShinyPalette_Gyarados[] = INCBIN_U32("assets/graphics.bin", 0xF5624, 0x28);
const u8 gMonIcon_Gyarados[] = INCBIN_U8("assets/graphics.bin", 0xF564C, 0x400);
const u8 gMonFootprint_Gyarados[] = INCBIN_U8("assets/graphics.bin", 0xF5A4C, 0x20);

const u32 gMonFrontPic_Lapras[] = INCBIN_U32("assets/graphics.bin", 0xF5A6C, 0x3E0);
const u32 gMonPalette_Lapras[] = INCBIN_U32("assets/graphics.bin", 0xF5E4C, 0x28);
const u32 gMonBackPic_Lapras[] = INCBIN_U32("assets/graphics.bin", 0xF5E74, 0x344);
const u32 gMonShinyPalette_Lapras[] = INCBIN_U32("assets/graphics.bin", 0xF61B8, 0x28);
const u8 gMonIcon_Lapras[] = INCBIN_U8("assets/graphics.bin", 0xF61E0, 0x400);
const u8 gMonFootprint_Lapras[] = INCBIN_U8("assets/graphics.bin", 0xF65E0, 0x20);

const u32 gMonFrontPic_Ditto[] = INCBIN_U32("assets/graphics.bin", 0xF6600, 0x1F0);
const u32 gMonPalette_Ditto[] = INCBIN_U32("assets/graphics.bin", 0xF67F0, 0x20);
const u32 gMonBackPic_Ditto[] = INCBIN_U32("assets/graphics.bin", 0xF6810, 0x200);
const u32 gMonShinyPalette_Ditto[] = INCBIN_U32("assets/graphics.bin", 0xF6A10, 0x20);
const u8 gMonIcon_Ditto[] = INCBIN_U8("assets/graphics.bin", 0xF6A30, 0x400);
const u8 gMonFootprint_Ditto[] = INCBIN_U8("assets/graphics.bin", 0xF6E30, 0x20);

const u32 gMonFrontPic_Eevee[] = INCBIN_U32("assets/graphics.bin", 0xF6E50, 0x2EC);
const u32 gMonPalette_Eevee[] = INCBIN_U32("assets/graphics.bin", 0xF713C, 0x28);
const u32 gMonBackPic_Eevee[] = INCBIN_U32("assets/graphics.bin", 0xF7164, 0x328);
const u32 gMonShinyPalette_Eevee[] = INCBIN_U32("assets/graphics.bin", 0xF748C, 0x28);
const u8 gMonIcon_Eevee[] = INCBIN_U8("assets/graphics.bin", 0xF74B4, 0x400);
const u8 gMonFootprint_Eevee[] = INCBIN_U8("assets/graphics.bin", 0xF78B4, 0x20);

const u32 gMonFrontPic_Vaporeon[] = INCBIN_U32("assets/graphics.bin", 0xF78D4, 0x394);
const u32 gMonPalette_Vaporeon[] = INCBIN_U32("assets/graphics.bin", 0xF7C68, 0x28);
const u32 gMonBackPic_Vaporeon[] = INCBIN_U32("assets/graphics.bin", 0xF7C90, 0x2C8);
const u32 gMonShinyPalette_Vaporeon[] = INCBIN_U32("assets/graphics.bin", 0xF7F58, 0x28);
const u8 gMonIcon_Vaporeon[] = INCBIN_U8("assets/graphics.bin", 0xF7F80, 0x400);
const u8 gMonFootprint_Vaporeon[] = INCBIN_U8("assets/graphics.bin", 0xF8380, 0x20);

const u32 gMonFrontPic_Jolteon[] = INCBIN_U32("assets/graphics.bin", 0xF83A0, 0x350);
const u32 gMonPalette_Jolteon[] = INCBIN_U32("assets/graphics.bin", 0xF86F0, 0x28);
const u32 gMonBackPic_Jolteon[] = INCBIN_U32("assets/graphics.bin", 0xF8718, 0x3AC);
const u32 gMonShinyPalette_Jolteon[] = INCBIN_U32("assets/graphics.bin", 0xF8AC4, 0x28);
const u8 gMonIcon_Jolteon[] = INCBIN_U8("assets/graphics.bin", 0xF8AEC, 0x400);
const u8 gMonFootprint_Jolteon[] = INCBIN_U8("assets/graphics.bin", 0xF8EEC, 0x20);

const u32 gMonFrontPic_Flareon[] = INCBIN_U32("assets/graphics.bin", 0xF8F0C, 0x384);
const u32 gMonPalette_Flareon[] = INCBIN_U32("assets/graphics.bin", 0xF9290, 0x28);
const u32 gMonBackPic_Flareon[] = INCBIN_U32("assets/graphics.bin", 0xF92B8, 0x390);
const u32 gMonShinyPalette_Flareon[] = INCBIN_U32("assets/graphics.bin", 0xF9648, 0x28);
const u8 gMonIcon_Flareon[] = INCBIN_U8("assets/graphics.bin", 0xF9670, 0x400);
const u8 gMonFootprint_Flareon[] = INCBIN_U8("assets/graphics.bin", 0xF9A70, 0x20);

const u32 gMonFrontPic_Porygon[] = INCBIN_U32("assets/graphics.bin", 0xF9A90, 0x2B8);
const u32 gMonPalette_Porygon[] = INCBIN_U32("assets/graphics.bin", 0xF9D48, 0x24);
const u32 gMonBackPic_Porygon[] = INCBIN_U32("assets/graphics.bin", 0xF9D6C, 0x2B8);
const u32 gMonShinyPalette_Porygon[] = INCBIN_U32("assets/graphics.bin", 0xFA024, 0x24);
const u8 gMonIcon_Porygon[] = INCBIN_U8("assets/graphics.bin", 0xFA048, 0x400);
const u8 gMonFootprint_Porygon[] = INCBIN_U8("assets/graphics.bin", 0xFA448, 0x20);

const u32 gMonFrontPic_Omanyte[] = INCBIN_U32("assets/graphics.bin", 0xFA468, 0x290);
const u32 gMonPalette_Omanyte[] = INCBIN_U32("assets/graphics.bin", 0xFA6F8, 0x28);
const u32 gMonBackPic_Omanyte[] = INCBIN_U32("assets/graphics.bin", 0xFA720, 0x34C);
const u32 gMonShinyPalette_Omanyte[] = INCBIN_U32("assets/graphics.bin", 0xFAA6C, 0x28);
const u8 gMonIcon_Omanyte[] = INCBIN_U8("assets/graphics.bin", 0xFAA94, 0x400);
const u8 gMonFootprint_Omanyte[] = INCBIN_U8("assets/graphics.bin", 0xFAE94, 0x20);

const u32 gMonFrontPic_Omastar[] = INCBIN_U32("assets/graphics.bin", 0xFAEB4, 0x3C0);
const u32 gMonPalette_Omastar[] = INCBIN_U32("assets/graphics.bin", 0xFB274, 0x28);
const u32 gMonBackPic_Omastar[] = INCBIN_U32("assets/graphics.bin", 0xFB29C, 0x340);
const u32 gMonShinyPalette_Omastar[] = INCBIN_U32("assets/graphics.bin", 0xFB5DC, 0x28);
const u8 gMonIcon_Omastar[] = INCBIN_U8("assets/graphics.bin", 0xFB604, 0x400);
const u8 gMonFootprint_Omastar[] = INCBIN_U8("assets/graphics.bin", 0xFBA04, 0x20);

const u32 gMonFrontPic_Kabuto[] = INCBIN_U32("assets/graphics.bin", 0xFBA24, 0x228);
const u32 gMonPalette_Kabuto[] = INCBIN_U32("assets/graphics.bin", 0xFBC4C, 0x28);
const u32 gMonBackPic_Kabuto[] = INCBIN_U32("assets/graphics.bin", 0xFBC74, 0x298);
const u32 gMonShinyPalette_Kabuto[] = INCBIN_U32("assets/graphics.bin", 0xFBF0C, 0x28);
const u8 gMonIcon_Kabuto[] = INCBIN_U8("assets/graphics.bin", 0xFBF34, 0x400);
const u8 gMonFootprint_Kabuto[] = INCBIN_U8("assets/graphics.bin", 0xFC334, 0x20);

const u32 gMonFrontPic_Kabutops[] = INCBIN_U32("assets/graphics.bin", 0xFC354, 0x410);
const u32 gMonPalette_Kabutops[] = INCBIN_U32("assets/graphics.bin", 0xFC764, 0x24);
const u32 gMonBackPic_Kabutops[] = INCBIN_U32("assets/graphics.bin", 0xFC788, 0x3A4);
const u32 gMonShinyPalette_Kabutops[] = INCBIN_U32("assets/graphics.bin", 0xFCB2C, 0x24);
const u8 gMonIcon_Kabutops[] = INCBIN_U8("assets/graphics.bin", 0xFCB50, 0x400);
const u8 gMonFootprint_Kabutops[] = INCBIN_U8("assets/graphics.bin", 0xFCF50, 0x20);

const u32 gMonFrontPic_Aerodactyl[] = INCBIN_U32("assets/graphics.bin", 0xFCF70, 0x450);
const u32 gMonPalette_Aerodactyl[] = INCBIN_U32("assets/graphics.bin", 0xFD3C0, 0x28);
const u32 gMonBackPic_Aerodactyl[] = INCBIN_U32("assets/graphics.bin", 0xFD3E8, 0x304);
const u32 gMonShinyPalette_Aerodactyl[] = INCBIN_U32("assets/graphics.bin", 0xFD6EC, 0x28);
const u8 gMonIcon_Aerodactyl[] = INCBIN_U8("assets/graphics.bin", 0xFD714, 0x400);
const u8 gMonFootprint_Aerodactyl[] = INCBIN_U8("assets/graphics.bin", 0xFDB14, 0x20);

const u32 gMonFrontPic_Snorlax[] = INCBIN_U32("assets/graphics.bin", 0xFDB34, 0x3D4);
const u32 gMonPalette_Snorlax[] = INCBIN_U32("assets/graphics.bin", 0xFDF08, 0x28);
const u32 gMonBackPic_Snorlax[] = INCBIN_U32("assets/graphics.bin", 0xFDF30, 0x21C);
const u32 gMonShinyPalette_Snorlax[] = INCBIN_U32("assets/graphics.bin", 0xFE14C, 0x28);
const u8 gMonIcon_Snorlax[] = INCBIN_U8("assets/graphics.bin", 0xFE174, 0x400);
const u8 gMonFootprint_Snorlax[] = INCBIN_U8("assets/graphics.bin", 0xFE574, 0x20);

const u32 gMonFrontPic_Articuno[] = INCBIN_U32("assets/graphics.bin", 0xFE594, 0x4F8);
const u32 gMonPalette_Articuno[] = INCBIN_U32("assets/graphics.bin", 0xFEA8C, 0x28);
const u32 gMonBackPic_Articuno[] = INCBIN_U32("assets/graphics.bin", 0xFEAB4, 0x25C);
const u32 gMonShinyPalette_Articuno[] = INCBIN_U32("assets/graphics.bin", 0xFED10, 0x28);
const u8 gMonIcon_Articuno[] = INCBIN_U8("assets/graphics.bin", 0xFED38, 0x400);
const u8 gMonFootprint_Articuno[] = INCBIN_U8("assets/graphics.bin", 0xFF138, 0x20);

const u32 gMonFrontPic_Zapdos[] = INCBIN_U32("assets/graphics.bin", 0xFF158, 0x450);
const u32 gMonPalette_Zapdos[] = INCBIN_U32("assets/graphics.bin", 0xFF5A8, 0x28);
const u32 gMonBackPic_Zapdos[] = INCBIN_U32("assets/graphics.bin", 0xFF5D0, 0x33C);
const u32 gMonShinyPalette_Zapdos[] = INCBIN_U32("assets/graphics.bin", 0xFF90C, 0x28);
const u8 gMonIcon_Zapdos[] = INCBIN_U8("assets/graphics.bin", 0xFF934, 0x400);
const u8 gMonFootprint_Zapdos[] = INCBIN_U8("assets/graphics.bin", 0xFFD34, 0x20);

const u32 gMonFrontPic_Moltres[] = INCBIN_U32("assets/graphics.bin", 0xFFD54, 0x4CC);
const u32 gMonPalette_Moltres[] = INCBIN_U32("assets/graphics.bin", 0x100220, 0x28);
const u32 gMonBackPic_Moltres[] = INCBIN_U32("assets/graphics.bin", 0x100248, 0x33C);
const u32 gMonShinyPalette_Moltres[] = INCBIN_U32("assets/graphics.bin", 0x100584, 0x28);
const u8 gMonIcon_Moltres[] = INCBIN_U8("assets/graphics.bin", 0x1005AC, 0x400);
const u8 gMonFootprint_Moltres[] = INCBIN_U8("assets/graphics.bin", 0x1009AC, 0x20);

const u32 gMonFrontPic_Dratini[] = INCBIN_U32("assets/graphics.bin", 0x1009CC, 0x2BC);
const u32 gMonPalette_Dratini[] = INCBIN_U32("assets/graphics.bin", 0x100C88, 0x24);
const u32 gMonBackPic_Dratini[] = INCBIN_U32("assets/graphics.bin", 0x100CAC, 0x290);
const u32 gMonShinyPalette_Dratini[] = INCBIN_U32("assets/graphics.bin", 0x100F3C, 0x24);
const u8 gMonIcon_Dratini[] = INCBIN_U8("assets/graphics.bin", 0x100F60, 0x400);
const u8 gMonFootprint_Dratini[] = INCBIN_U8("assets/graphics.bin", 0x101360, 0x20);

const u32 gMonFrontPic_Dragonair[] = INCBIN_U32("assets/graphics.bin", 0x101380, 0x398);
const u32 gMonPalette_Dragonair[] = INCBIN_U32("assets/graphics.bin", 0x101718, 0x28);
const u32 gMonBackPic_Dragonair[] = INCBIN_U32("assets/graphics.bin", 0x101740, 0x310);
const u32 gMonShinyPalette_Dragonair[] = INCBIN_U32("assets/graphics.bin", 0x101A50, 0x28);
const u8 gMonIcon_Dragonair[] = INCBIN_U8("assets/graphics.bin", 0x101A78, 0x400);
const u8 gMonFootprint_Dragonair[] = INCBIN_U8("assets/graphics.bin", 0x101E78, 0x20);

const u32 gMonFrontPic_Dragonite[] = INCBIN_U32("assets/graphics.bin", 0x101E98, 0x550);
const u32 gMonPalette_Dragonite[] = INCBIN_U32("assets/graphics.bin", 0x1023E8, 0x28);
const u32 gMonBackPic_Dragonite[] = INCBIN_U32("assets/graphics.bin", 0x102410, 0x2F8);
const u32 gMonShinyPalette_Dragonite[] = INCBIN_U32("assets/graphics.bin", 0x102708, 0x28);
const u8 gMonIcon_Dragonite[] = INCBIN_U8("assets/graphics.bin", 0x102730, 0x400);
const u8 gMonFootprint_Dragonite[] = INCBIN_U8("assets/graphics.bin", 0x102B30, 0x20);

const u32 gMonFrontPic_Mewtwo[] = INCBIN_U32("assets/graphics.bin", 0x102B50, 0x43C);
const u32 gMonPalette_Mewtwo[] = INCBIN_U32("assets/graphics.bin", 0x102F8C, 0x24);
const u32 gMonBackPic_Mewtwo[] = INCBIN_U32("assets/graphics.bin", 0x102FB0, 0x3CC);
const u32 gMonShinyPalette_Mewtwo[] = INCBIN_U32("assets/graphics.bin", 0x10337C, 0x24);
const u8 gMonIcon_Mewtwo[] = INCBIN_U8("assets/graphics.bin", 0x1033A0, 0x400);
const u8 gMonFootprint_Mewtwo[] = INCBIN_U8("assets/graphics.bin", 0x1037A0, 0x20);

const u32 gMonFrontPic_Mew[] = INCBIN_U32("assets/graphics.bin", 0x1037C0, 0x2C0);
const u32 gMonPalette_Mew[] = INCBIN_U32("assets/graphics.bin", 0x103A80, 0x24);
const u32 gMonBackPic_Mew[] = INCBIN_U32("assets/graphics.bin", 0x103AA4, 0x350);
const u32 gMonShinyPalette_Mew[] = INCBIN_U32("assets/graphics.bin", 0x103DF4, 0x24);
const u8 gMonIcon_Mew[] = INCBIN_U8("assets/graphics.bin", 0x103E18, 0x400);
const u8 gMonFootprint_Mew[] = INCBIN_U8("assets/graphics.bin", 0x104218, 0x20);

const u32 gMonFrontPic_Chikorita[] = INCBIN_U32("assets/graphics.bin", 0x104238, 0x268);
const u32 gMonPalette_Chikorita[] = INCBIN_U32("assets/graphics.bin", 0x1044A0, 0x28);
const u32 gMonBackPic_Chikorita[] = INCBIN_U32("assets/graphics.bin", 0x1044C8, 0x2C4);
const u32 gMonShinyPalette_Chikorita[] = INCBIN_U32("assets/graphics.bin", 0x10478C, 0x28);
const u8 gMonIcon_Chikorita[] = INCBIN_U8("assets/graphics.bin", 0x1047B4, 0x400);
const u8 gMonFootprint_Chikorita[] = INCBIN_U8("assets/graphics.bin", 0x104BB4, 0x20);

const u32 gMonFrontPic_Bayleef[] = INCBIN_U32("assets/graphics.bin", 0x104BD4, 0x3D4);
const u32 gMonPalette_Bayleef[] = INCBIN_U32("assets/graphics.bin", 0x104FA8, 0x28);
const u32 gMonBackPic_Bayleef[] = INCBIN_U32("assets/graphics.bin", 0x104FD0, 0x390);
const u32 gMonShinyPalette_Bayleef[] = INCBIN_U32("assets/graphics.bin", 0x105360, 0x28);
const u8 gMonIcon_Bayleef[] = INCBIN_U8("assets/graphics.bin", 0x105388, 0x400);
const u8 gMonFootprint_Bayleef[] = INCBIN_U8("assets/graphics.bin", 0x105788, 0x20);

const u32 gMonFrontPic_Meganium[] = INCBIN_U32("assets/graphics.bin", 0x1057A8, 0x55C);
const u32 gMonPalette_Meganium[] = INCBIN_U32("assets/graphics.bin", 0x105D04, 0x28);
const u32 gMonBackPic_Meganium[] = INCBIN_U32("assets/graphics.bin", 0x105D2C, 0x350);
const u32 gMonShinyPalette_Meganium[] = INCBIN_U32("assets/graphics.bin", 0x10607C, 0x28);
const u8 gMonIcon_Meganium[] = INCBIN_U8("assets/graphics.bin", 0x1060A4, 0x400);
const u8 gMonFootprint_Meganium[] = INCBIN_U8("assets/graphics.bin", 0x1064A4, 0x20);

const u32 gMonFrontPic_Cyndaquil[] = INCBIN_U32("assets/graphics.bin", 0x1064C4, 0x28C);
const u32 gMonPalette_Cyndaquil[] = INCBIN_U32("assets/graphics.bin", 0x106750, 0x28);
const u32 gMonBackPic_Cyndaquil[] = INCBIN_U32("assets/graphics.bin", 0x106778, 0x32C);
const u32 gMonShinyPalette_Cyndaquil[] = INCBIN_U32("assets/graphics.bin", 0x106AA4, 0x28);
const u8 gMonIcon_Cyndaquil[] = INCBIN_U8("assets/graphics.bin", 0x106ACC, 0x400);
const u8 gMonFootprint_Cyndaquil[] = INCBIN_U8("assets/graphics.bin", 0x106ECC, 0x20);

const u32 gMonFrontPic_Quilava[] = INCBIN_U32("assets/graphics.bin", 0x106EEC, 0x31C);
const u32 gMonPalette_Quilava[] = INCBIN_U32("assets/graphics.bin", 0x107208, 0x28);
const u32 gMonBackPic_Quilava[] = INCBIN_U32("assets/graphics.bin", 0x107230, 0x374);
const u32 gMonShinyPalette_Quilava[] = INCBIN_U32("assets/graphics.bin", 0x1075A4, 0x28);
const u8 gMonIcon_Quilava[] = INCBIN_U8("assets/graphics.bin", 0x1075CC, 0x400);
const u8 gMonFootprint_Quilava[] = INCBIN_U8("assets/graphics.bin", 0x1079CC, 0x20);

const u32 gMonFrontPic_Typhlosion[] = INCBIN_U32("assets/graphics.bin", 0x1079EC, 0x428);
const u32 gMonPalette_Typhlosion[] = INCBIN_U32("assets/graphics.bin", 0x107E14, 0x28);
const u32 gMonBackPic_Typhlosion[] = INCBIN_U32("assets/graphics.bin", 0x107E3C, 0x404);
const u32 gMonShinyPalette_Typhlosion[] = INCBIN_U32("assets/graphics.bin", 0x108240, 0x28);
const u8 gMonIcon_Typhlosion[] = INCBIN_U8("assets/graphics.bin", 0x108268, 0x400);
const u8 gMonFootprint_Typhlosion[] = INCBIN_U8("assets/graphics.bin", 0x108668, 0x20);

const u32 gMonFrontPic_Totodile[] = INCBIN_U32("assets/graphics.bin", 0x108688, 0x2A4);
const u32 gMonPalette_Totodile[] = INCBIN_U32("assets/graphics.bin", 0x10892C, 0x28);
const u32 gMonBackPic_Totodile[] = INCBIN_U32("assets/graphics.bin", 0x108954, 0x2E0);
const u32 gMonShinyPalette_Totodile[] = INCBIN_U32("assets/graphics.bin", 0x108C34, 0x28);
const u8 gMonIcon_Totodile[] = INCBIN_U8("assets/graphics.bin", 0x108C5C, 0x400);
const u8 gMonFootprint_Totodile[] = INCBIN_U8("assets/graphics.bin", 0x10905C, 0x20);

const u32 gMonFrontPic_Croconaw[] = INCBIN_U32("assets/graphics.bin", 0x10907C, 0x368);
const u32 gMonPalette_Croconaw[] = INCBIN_U32("assets/graphics.bin", 0x1093E4, 0x28);
const u32 gMonBackPic_Croconaw[] = INCBIN_U32("assets/graphics.bin", 0x10940C, 0x350);
const u32 gMonShinyPalette_Croconaw[] = INCBIN_U32("assets/graphics.bin", 0x10975C, 0x28);
const u8 gMonIcon_Croconaw[] = INCBIN_U8("assets/graphics.bin", 0x109784, 0x400);
const u8 gMonFootprint_Croconaw[] = INCBIN_U8("assets/graphics.bin", 0x109B84, 0x20);

const u32 gMonFrontPic_Feraligatr[] = INCBIN_U32("assets/graphics.bin", 0x109BA4, 0x56C);
const u32 gMonPalette_Feraligatr[] = INCBIN_U32("assets/graphics.bin", 0x10A110, 0x28);
const u32 gMonBackPic_Feraligatr[] = INCBIN_U32("assets/graphics.bin", 0x10A138, 0x4CC);
const u32 gMonShinyPalette_Feraligatr[] = INCBIN_U32("assets/graphics.bin", 0x10A604, 0x28);
const u8 gMonIcon_Feraligatr[] = INCBIN_U8("assets/graphics.bin", 0x10A62C, 0x400);
const u8 gMonFootprint_Feraligatr[] = INCBIN_U8("assets/graphics.bin", 0x10AA2C, 0x20);

const u32 gMonFrontPic_Sentret[] = INCBIN_U32("assets/graphics.bin", 0x10AA4C, 0x2DC);
const u32 gMonPalette_Sentret[] = INCBIN_U32("assets/graphics.bin", 0x10AD28, 0x28);
const u32 gMonBackPic_Sentret[] = INCBIN_U32("assets/graphics.bin", 0x10AD50, 0x2A4);
const u32 gMonShinyPalette_Sentret[] = INCBIN_U32("assets/graphics.bin", 0x10AFF4, 0x28);
const u8 gMonIcon_Sentret[] = INCBIN_U8("assets/graphics.bin", 0x10B01C, 0x400);
const u8 gMonFootprint_Sentret[] = INCBIN_U8("assets/graphics.bin", 0x10B41C, 0x20);

const u32 gMonFrontPic_Furret[] = INCBIN_U32("assets/graphics.bin", 0x10B43C, 0x334);
const u32 gMonPalette_Furret[] = INCBIN_U32("assets/graphics.bin", 0x10B770, 0x28);
const u32 gMonBackPic_Furret[] = INCBIN_U32("assets/graphics.bin", 0x10B798, 0x328);
const u32 gMonShinyPalette_Furret[] = INCBIN_U32("assets/graphics.bin", 0x10BAC0, 0x28);
const u8 gMonIcon_Furret[] = INCBIN_U8("assets/graphics.bin", 0x10BAE8, 0x400);
const u8 gMonFootprint_Furret[] = INCBIN_U8("assets/graphics.bin", 0x10BEE8, 0x20);

const u32 gMonFrontPic_Hoothoot[] = INCBIN_U32("assets/graphics.bin", 0x10BF08, 0x284);
const u32 gMonPalette_Hoothoot[] = INCBIN_U32("assets/graphics.bin", 0x10C18C, 0x28);
const u32 gMonBackPic_Hoothoot[] = INCBIN_U32("assets/graphics.bin", 0x10C1B4, 0x308);
const u32 gMonShinyPalette_Hoothoot[] = INCBIN_U32("assets/graphics.bin", 0x10C4BC, 0x28);
const u8 gMonIcon_Hoothoot[] = INCBIN_U8("assets/graphics.bin", 0x10C4E4, 0x400);
const u8 gMonFootprint_Hoothoot[] = INCBIN_U8("assets/graphics.bin", 0x10C8E4, 0x20);

const u32 gMonFrontPic_Noctowl[] = INCBIN_U32("assets/graphics.bin", 0x10C904, 0x354);
const u32 gMonPalette_Noctowl[] = INCBIN_U32("assets/graphics.bin", 0x10CC58, 0x28);
const u32 gMonBackPic_Noctowl[] = INCBIN_U32("assets/graphics.bin", 0x10CC80, 0x35C);
const u32 gMonShinyPalette_Noctowl[] = INCBIN_U32("assets/graphics.bin", 0x10CFDC, 0x28);
const u8 gMonIcon_Noctowl[] = INCBIN_U8("assets/graphics.bin", 0x10D004, 0x400);
const u8 gMonFootprint_Noctowl[] = INCBIN_U8("assets/graphics.bin", 0x10D404, 0x20);

const u32 gMonFrontPic_Ledyba[] = INCBIN_U32("assets/graphics.bin", 0x10D424, 0x2F4);
const u32 gMonPalette_Ledyba[] = INCBIN_U32("assets/graphics.bin", 0x10D718, 0x28);
const u32 gMonBackPic_Ledyba[] = INCBIN_U32("assets/graphics.bin", 0x10D740, 0x330);
const u32 gMonShinyPalette_Ledyba[] = INCBIN_U32("assets/graphics.bin", 0x10DA70, 0x28);
const u8 gMonIcon_Ledyba[] = INCBIN_U8("assets/graphics.bin", 0x10DA98, 0x400);
const u8 gMonFootprint_Ledyba[] = INCBIN_U8("assets/graphics.bin", 0x10DE98, 0x20);

const u32 gMonFrontPic_Ledian[] = INCBIN_U32("assets/graphics.bin", 0x10DEB8, 0x388);
const u32 gMonPalette_Ledian[] = INCBIN_U32("assets/graphics.bin", 0x10E240, 0x28);
const u32 gMonBackPic_Ledian[] = INCBIN_U32("assets/graphics.bin", 0x10E268, 0x358);
const u32 gMonShinyPalette_Ledian[] = INCBIN_U32("assets/graphics.bin", 0x10E5C0, 0x28);
const u8 gMonIcon_Ledian[] = INCBIN_U8("assets/graphics.bin", 0x10E5E8, 0x400);
const u8 gMonFootprint_Ledian[] = INCBIN_U8("assets/graphics.bin", 0x10E9E8, 0x20);

const u32 gMonFrontPic_Spinarak[] = INCBIN_U32("assets/graphics.bin", 0x10EA08, 0x274);
const u32 gMonPalette_Spinarak[] = INCBIN_U32("assets/graphics.bin", 0x10EC7C, 0x28);
const u32 gMonBackPic_Spinarak[] = INCBIN_U32("assets/graphics.bin", 0x10ECA4, 0x264);
const u32 gMonShinyPalette_Spinarak[] = INCBIN_U32("assets/graphics.bin", 0x10EF08, 0x28);
const u8 gMonIcon_Spinarak[] = INCBIN_U8("assets/graphics.bin", 0x10EF30, 0x400);
const u8 gMonFootprint_Spinarak[] = INCBIN_U8("assets/graphics.bin", 0x10F330, 0x20);

const u32 gMonFrontPic_Ariados[] = INCBIN_U32("assets/graphics.bin", 0x10F350, 0x3C0);
const u32 gMonPalette_Ariados[] = INCBIN_U32("assets/graphics.bin", 0x10F710, 0x28);
const u32 gMonBackPic_Ariados[] = INCBIN_U32("assets/graphics.bin", 0x10F738, 0x378);
const u32 gMonShinyPalette_Ariados[] = INCBIN_U32("assets/graphics.bin", 0x10FAB0, 0x28);
const u8 gMonIcon_Ariados[] = INCBIN_U8("assets/graphics.bin", 0x10FAD8, 0x400);
const u8 gMonFootprint_Ariados[] = INCBIN_U8("assets/graphics.bin", 0x10FED8, 0x20);

const u32 gMonFrontPic_Crobat[] = INCBIN_U32("assets/graphics.bin", 0x10FEF8, 0x3B0);
const u32 gMonPalette_Crobat[] = INCBIN_U32("assets/graphics.bin", 0x1102A8, 0x28);
const u32 gMonBackPic_Crobat[] = INCBIN_U32("assets/graphics.bin", 0x1102D0, 0x308);
const u32 gMonShinyPalette_Crobat[] = INCBIN_U32("assets/graphics.bin", 0x1105D8, 0x28);
const u8 gMonIcon_Crobat[] = INCBIN_U8("assets/graphics.bin", 0x110600, 0x400);
const u8 gMonFootprint_Crobat[] = INCBIN_U8("assets/graphics.bin", 0x110A00, 0x20);

const u32 gMonFrontPic_Chinchou[] = INCBIN_U32("assets/graphics.bin", 0x110A20, 0x2D8);
const u32 gMonPalette_Chinchou[] = INCBIN_U32("assets/graphics.bin", 0x110CF8, 0x28);
const u32 gMonBackPic_Chinchou[] = INCBIN_U32("assets/graphics.bin", 0x110D20, 0x2F8);
const u32 gMonShinyPalette_Chinchou[] = INCBIN_U32("assets/graphics.bin", 0x111018, 0x28);
const u8 gMonIcon_Chinchou[] = INCBIN_U8("assets/graphics.bin", 0x111040, 0x400);
const u8 gMonFootprint_Chinchou[] = INCBIN_U8("assets/graphics.bin", 0x111440, 0x20);

const u32 gMonFrontPic_Lanturn[] = INCBIN_U32("assets/graphics.bin", 0x111460, 0x370);
const u32 gMonPalette_Lanturn[] = INCBIN_U32("assets/graphics.bin", 0x1117D0, 0x28);
const u32 gMonBackPic_Lanturn[] = INCBIN_U32("assets/graphics.bin", 0x1117F8, 0x300);
const u32 gMonShinyPalette_Lanturn[] = INCBIN_U32("assets/graphics.bin", 0x111AF8, 0x28);
const u8 gMonIcon_Lanturn[] = INCBIN_U8("assets/graphics.bin", 0x111B20, 0x400);
const u8 gMonFootprint_Lanturn[] = INCBIN_U8("assets/graphics.bin", 0x111F20, 0x20);

const u32 gMonFrontPic_Pichu[] = INCBIN_U32("assets/graphics.bin", 0x111F40, 0x21C);
const u32 gMonPalette_Pichu[] = INCBIN_U32("assets/graphics.bin", 0x11215C, 0x28);
const u32 gMonBackPic_Pichu[] = INCBIN_U32("assets/graphics.bin", 0x112184, 0x25C);
const u32 gMonShinyPalette_Pichu[] = INCBIN_U32("assets/graphics.bin", 0x1123E0, 0x28);
const u8 gMonIcon_Pichu[] = INCBIN_U8("assets/graphics.bin", 0x112408, 0x400);
const u8 gMonFootprint_Pichu[] = INCBIN_U8("assets/graphics.bin", 0x112808, 0x20);

const u32 gMonFrontPic_Cleffa[] = INCBIN_U32("assets/graphics.bin", 0x112828, 0x1E0);
const u32 gMonPalette_Cleffa[] = INCBIN_U32("assets/graphics.bin", 0x112A08, 0x28);
const u32 gMonBackPic_Cleffa[] = INCBIN_U32("assets/graphics.bin", 0x112A30, 0x23C);
const u32 gMonShinyPalette_Cleffa[] = INCBIN_U32("assets/graphics.bin", 0x112C6C, 0x28);
const u8 gMonIcon_Cleffa[] = INCBIN_U8("assets/graphics.bin", 0x112C94, 0x400);
const u8 gMonFootprint_Cleffa[] = INCBIN_U8("assets/graphics.bin", 0x113094, 0x20);

const u32 gMonFrontPic_Igglybuff[] = INCBIN_U32("assets/graphics.bin", 0x1130B4, 0x1E8);
const u32 gMonPalette_Igglybuff[] = INCBIN_U32("assets/graphics.bin", 0x11329C, 0x28);
const u32 gMonBackPic_Igglybuff[] = INCBIN_U32("assets/graphics.bin", 0x1132C4, 0x23C);
const u32 gMonShinyPalette_Igglybuff[] = INCBIN_U32("assets/graphics.bin", 0x113500, 0x28);
const u8 gMonIcon_Igglybuff[] = INCBIN_U8("assets/graphics.bin", 0x113528, 0x400);
const u8 gMonFootprint_Igglybuff[] = INCBIN_U8("assets/graphics.bin", 0x113928, 0x20);

const u32 gMonFrontPic_Togepi[] = INCBIN_U32("assets/graphics.bin", 0x113948, 0x1D4);
const u32 gMonPalette_Togepi[] = INCBIN_U32("assets/graphics.bin", 0x113B1C, 0x28);
const u32 gMonBackPic_Togepi[] = INCBIN_U32("assets/graphics.bin", 0x113B44, 0x274);
const u32 gMonShinyPalette_Togepi[] = INCBIN_U32("assets/graphics.bin", 0x113DB8, 0x28);
const u8 gMonIcon_Togepi[] = INCBIN_U8("assets/graphics.bin", 0x113DE0, 0x400);
const u8 gMonFootprint_Togepi[] = INCBIN_U8("assets/graphics.bin", 0x1141E0, 0x20);

const u32 gMonFrontPic_Togetic[] = INCBIN_U32("assets/graphics.bin", 0x114200, 0x274);
const u32 gMonPalette_Togetic[] = INCBIN_U32("assets/graphics.bin", 0x114474, 0x28);
const u32 gMonBackPic_Togetic[] = INCBIN_U32("assets/graphics.bin", 0x11449C, 0x32C);
const u32 gMonShinyPalette_Togetic[] = INCBIN_U32("assets/graphics.bin", 0x1147C8, 0x28);
const u8 gMonIcon_Togetic[] = INCBIN_U8("assets/graphics.bin", 0x1147F0, 0x400);
const u8 gMonFootprint_Togetic[] = INCBIN_U8("assets/graphics.bin", 0x114BF0, 0x20);

const u32 gMonFrontPic_Natu[] = INCBIN_U32("assets/graphics.bin", 0x114C10, 0x1CC);
const u32 gMonPalette_Natu[] = INCBIN_U32("assets/graphics.bin", 0x114DDC, 0x28);
const u32 gMonBackPic_Natu[] = INCBIN_U32("assets/graphics.bin", 0x114E04, 0x214);
const u32 gMonShinyPalette_Natu[] = INCBIN_U32("assets/graphics.bin", 0x115018, 0x28);
const u8 gMonIcon_Natu[] = INCBIN_U8("assets/graphics.bin", 0x115040, 0x400);
const u8 gMonFootprint_Natu[] = INCBIN_U8("assets/graphics.bin", 0x115440, 0x20);

const u32 gMonFrontPic_Xatu[] = INCBIN_U32("assets/graphics.bin", 0x115460, 0x2DC);
const u32 gMonPalette_Xatu[] = INCBIN_U32("assets/graphics.bin", 0x11573C, 0x28);
const u32 gMonBackPic_Xatu[] = INCBIN_U32("assets/graphics.bin", 0x115764, 0x378);
const u32 gMonShinyPalette_Xatu[] = INCBIN_U32("assets/graphics.bin", 0x115ADC, 0x28);
const u8 gMonIcon_Xatu[] = INCBIN_U8("assets/graphics.bin", 0x115B04, 0x400);
const u8 gMonFootprint_Xatu[] = INCBIN_U8("assets/graphics.bin", 0x115F04, 0x20);

const u32 gMonFrontPic_Mareep[] = INCBIN_U32("assets/graphics.bin", 0x115F24, 0x2B4);
const u32 gMonPalette_Mareep[] = INCBIN_U32("assets/graphics.bin", 0x1161D8, 0x28);
const u32 gMonBackPic_Mareep[] = INCBIN_U32("assets/graphics.bin", 0x116200, 0x2F4);
const u32 gMonShinyPalette_Mareep[] = INCBIN_U32("assets/graphics.bin", 0x1164F4, 0x28);
const u8 gMonIcon_Mareep[] = INCBIN_U8("assets/graphics.bin", 0x11651C, 0x400);
const u8 gMonFootprint_Mareep[] = INCBIN_U8("assets/graphics.bin", 0x11691C, 0x20);

const u32 gMonFrontPic_Flaaffy[] = INCBIN_U32("assets/graphics.bin", 0x11693C, 0x300);
const u32 gMonPalette_Flaaffy[] = INCBIN_U32("assets/graphics.bin", 0x116C3C, 0x28);
const u32 gMonBackPic_Flaaffy[] = INCBIN_U32("assets/graphics.bin", 0x116C64, 0x31C);
const u32 gMonShinyPalette_Flaaffy[] = INCBIN_U32("assets/graphics.bin", 0x116F80, 0x28);
const u8 gMonIcon_Flaaffy[] = INCBIN_U8("assets/graphics.bin", 0x116FA8, 0x400);
const u8 gMonFootprint_Flaaffy[] = INCBIN_U8("assets/graphics.bin", 0x1173A8, 0x20);

const u32 gMonFrontPic_Ampharos[] = INCBIN_U32("assets/graphics.bin", 0x1173C8, 0x35C);
const u32 gMonPalette_Ampharos[] = INCBIN_U32("assets/graphics.bin", 0x117724, 0x28);
const u32 gMonBackPic_Ampharos[] = INCBIN_U32("assets/graphics.bin", 0x11774C, 0x378);
const u32 gMonShinyPalette_Ampharos[] = INCBIN_U32("assets/graphics.bin", 0x117AC4, 0x28);
const u8 gMonIcon_Ampharos[] = INCBIN_U8("assets/graphics.bin", 0x117AEC, 0x400);
const u8 gMonFootprint_Ampharos[] = INCBIN_U8("assets/graphics.bin", 0x117EEC, 0x20);

const u32 gMonFrontPic_Bellossom[] = INCBIN_U32("assets/graphics.bin", 0x117F0C, 0x270);
const u32 gMonPalette_Bellossom[] = INCBIN_U32("assets/graphics.bin", 0x11817C, 0x28);
const u32 gMonBackPic_Bellossom[] = INCBIN_U32("assets/graphics.bin", 0x1181A4, 0x324);
const u32 gMonShinyPalette_Bellossom[] = INCBIN_U32("assets/graphics.bin", 0x1184C8, 0x28);
const u8 gMonIcon_Bellossom[] = INCBIN_U8("assets/graphics.bin", 0x1184F0, 0x400);
const u8 gMonFootprint_Bellossom[] = INCBIN_U8("assets/graphics.bin", 0x1188F0, 0x20);

const u32 gMonFrontPic_Marill[] = INCBIN_U32("assets/graphics.bin", 0x118910, 0x2C4);
const u32 gMonPalette_Marill[] = INCBIN_U32("assets/graphics.bin", 0x118BD4, 0x28);
const u32 gMonBackPic_Marill[] = INCBIN_U32("assets/graphics.bin", 0x118BFC, 0x2AC);
const u32 gMonShinyPalette_Marill[] = INCBIN_U32("assets/graphics.bin", 0x118EA8, 0x28);
const u8 gMonIcon_Marill[] = INCBIN_U8("assets/graphics.bin", 0x118ED0, 0x400);
const u8 gMonFootprint_Marill[] = INCBIN_U8("assets/graphics.bin", 0x1192D0, 0x20);

const u32 gMonFrontPic_Azumarill[] = INCBIN_U32("assets/graphics.bin", 0x1192F0, 0x300);
const u32 gMonPalette_Azumarill[] = INCBIN_U32("assets/graphics.bin", 0x1195F0, 0x28);
const u32 gMonBackPic_Azumarill[] = INCBIN_U32("assets/graphics.bin", 0x119618, 0x2BC);
const u32 gMonShinyPalette_Azumarill[] = INCBIN_U32("assets/graphics.bin", 0x1198D4, 0x28);
const u8 gMonIcon_Azumarill[] = INCBIN_U8("assets/graphics.bin", 0x1198FC, 0x400);
const u8 gMonFootprint_Azumarill[] = INCBIN_U8("assets/graphics.bin", 0x119CFC, 0x20);

const u32 gMonFrontPic_Sudowoodo[] = INCBIN_U32("assets/graphics.bin", 0x119D1C, 0x318);
const u32 gMonPalette_Sudowoodo[] = INCBIN_U32("assets/graphics.bin", 0x11A034, 0x28);
const u32 gMonBackPic_Sudowoodo[] = INCBIN_U32("assets/graphics.bin", 0x11A05C, 0x35C);
const u32 gMonShinyPalette_Sudowoodo[] = INCBIN_U32("assets/graphics.bin", 0x11A3B8, 0x28);
const u8 gMonIcon_Sudowoodo[] = INCBIN_U8("assets/graphics.bin", 0x11A3E0, 0x400);
const u8 gMonFootprint_Sudowoodo[] = INCBIN_U8("assets/graphics.bin", 0x11A7E0, 0x20);

const u32 gMonFrontPic_Politoed[] = INCBIN_U32("assets/graphics.bin", 0x11A800, 0x33C);
const u32 gMonPalette_Politoed[] = INCBIN_U32("assets/graphics.bin", 0x11AB3C, 0x28);
const u32 gMonBackPic_Politoed[] = INCBIN_U32("assets/graphics.bin", 0x11AB64, 0x2BC);
const u32 gMonShinyPalette_Politoed[] = INCBIN_U32("assets/graphics.bin", 0x11AE20, 0x28);
const u8 gMonIcon_Politoed[] = INCBIN_U8("assets/graphics.bin", 0x11AE48, 0x400);
const u8 gMonFootprint_Politoed[] = INCBIN_U8("assets/graphics.bin", 0x11B248, 0x20);

const u32 gMonFrontPic_Hoppip[] = INCBIN_U32("assets/graphics.bin", 0x11B268, 0x2B4);
const u32 gMonPalette_Hoppip[] = INCBIN_U32("assets/graphics.bin", 0x11B51C, 0x28);
const u32 gMonBackPic_Hoppip[] = INCBIN_U32("assets/graphics.bin", 0x11B544, 0x2E0);
const u32 gMonShinyPalette_Hoppip[] = INCBIN_U32("assets/graphics.bin", 0x11B824, 0x28);
const u8 gMonIcon_Hoppip[] = INCBIN_U8("assets/graphics.bin", 0x11B84C, 0x400);
const u8 gMonFootprint_Hoppip[] = INCBIN_U8("assets/graphics.bin", 0x11BC4C, 0x20);

const u32 gMonFrontPic_Skiploom[] = INCBIN_U32("assets/graphics.bin", 0x11BC6C, 0x288);
const u32 gMonPalette_Skiploom[] = INCBIN_U32("assets/graphics.bin", 0x11BEF4, 0x28);
const u32 gMonBackPic_Skiploom[] = INCBIN_U32("assets/graphics.bin", 0x11BF1C, 0x2E0);
const u32 gMonShinyPalette_Skiploom[] = INCBIN_U32("assets/graphics.bin", 0x11C1FC, 0x28);
const u8 gMonIcon_Skiploom[] = INCBIN_U8("assets/graphics.bin", 0x11C224, 0x400);
const u8 gMonFootprint_Skiploom[] = INCBIN_U8("assets/graphics.bin", 0x11C624, 0x20);

const u32 gMonFrontPic_Jumpluff[] = INCBIN_U32("assets/graphics.bin", 0x11C644, 0x36C);
const u32 gMonPalette_Jumpluff[] = INCBIN_U32("assets/graphics.bin", 0x11C9B0, 0x28);
const u32 gMonBackPic_Jumpluff[] = INCBIN_U32("assets/graphics.bin", 0x11C9D8, 0x3F8);
const u32 gMonShinyPalette_Jumpluff[] = INCBIN_U32("assets/graphics.bin", 0x11CDD0, 0x28);
const u8 gMonIcon_Jumpluff[] = INCBIN_U8("assets/graphics.bin", 0x11CDF8, 0x400);
const u8 gMonFootprint_Jumpluff[] = INCBIN_U8("assets/graphics.bin", 0x11D1F8, 0x20);

const u32 gMonFrontPic_Aipom[] = INCBIN_U32("assets/graphics.bin", 0x11D218, 0x2FC);
const u32 gMonPalette_Aipom[] = INCBIN_U32("assets/graphics.bin", 0x11D514, 0x28);
const u32 gMonBackPic_Aipom[] = INCBIN_U32("assets/graphics.bin", 0x11D53C, 0x2F4);
const u32 gMonShinyPalette_Aipom[] = INCBIN_U32("assets/graphics.bin", 0x11D830, 0x28);
const u8 gMonIcon_Aipom[] = INCBIN_U8("assets/graphics.bin", 0x11D858, 0x400);
const u8 gMonFootprint_Aipom[] = INCBIN_U8("assets/graphics.bin", 0x11DC58, 0x20);

const u32 gMonFrontPic_Sunkern[] = INCBIN_U32("assets/graphics.bin", 0x11DC78, 0x238);
const u32 gMonPalette_Sunkern[] = INCBIN_U32("assets/graphics.bin", 0x11DEB0, 0x28);
const u32 gMonBackPic_Sunkern[] = INCBIN_U32("assets/graphics.bin", 0x11DED8, 0x2C4);
const u32 gMonShinyPalette_Sunkern[] = INCBIN_U32("assets/graphics.bin", 0x11E19C, 0x28);
const u8 gMonIcon_Sunkern[] = INCBIN_U8("assets/graphics.bin", 0x11E1C4, 0x400);
const u8 gMonFootprint_Sunkern[] = INCBIN_U8("assets/graphics.bin", 0x11E5C4, 0x20);

const u32 gMonFrontPic_Sunflora[] = INCBIN_U32("assets/graphics.bin", 0x11E5E4, 0x358);
const u32 gMonPalette_Sunflora[] = INCBIN_U32("assets/graphics.bin", 0x11E93C, 0x28);
const u32 gMonBackPic_Sunflora[] = INCBIN_U32("assets/graphics.bin", 0x11E964, 0x3A0);
const u32 gMonShinyPalette_Sunflora[] = INCBIN_U32("assets/graphics.bin", 0x11ED04, 0x28);
const u8 gMonIcon_Sunflora[] = INCBIN_U8("assets/graphics.bin", 0x11ED2C, 0x400);
const u8 gMonFootprint_Sunflora[] = INCBIN_U8("assets/graphics.bin", 0x11F12C, 0x20);

const u32 gMonFrontPic_Yanma[] = INCBIN_U32("assets/graphics.bin", 0x11F14C, 0x384);
const u32 gMonPalette_Yanma[] = INCBIN_U32("assets/graphics.bin", 0x11F4D0, 0x28);
const u32 gMonBackPic_Yanma[] = INCBIN_U32("assets/graphics.bin", 0x11F4F8, 0x3B4);
const u32 gMonShinyPalette_Yanma[] = INCBIN_U32("assets/graphics.bin", 0x11F8AC, 0x28);
const u8 gMonIcon_Yanma[] = INCBIN_U8("assets/graphics.bin", 0x11F8D4, 0x400);
const u8 gMonFootprint_Yanma[] = INCBIN_U8("assets/graphics.bin", 0x11FCD4, 0x20);

const u32 gMonFrontPic_Wooper[] = INCBIN_U32("assets/graphics.bin", 0x11FCF4, 0x240);
const u32 gMonPalette_Wooper[] = INCBIN_U32("assets/graphics.bin", 0x11FF34, 0x28);
const u32 gMonBackPic_Wooper[] = INCBIN_U32("assets/graphics.bin", 0x11FF5C, 0x28C);
const u32 gMonShinyPalette_Wooper[] = INCBIN_U32("assets/graphics.bin", 0x1201E8, 0x28);
const u8 gMonIcon_Wooper[] = INCBIN_U8("assets/graphics.bin", 0x120210, 0x400);
const u8 gMonFootprint_Wooper[] = INCBIN_U8("assets/graphics.bin", 0x120610, 0x20);

const u32 gMonFrontPic_Quagsire[] = INCBIN_U32("assets/graphics.bin", 0x120630, 0x374);
const u32 gMonPalette_Quagsire[] = INCBIN_U32("assets/graphics.bin", 0x1209A4, 0x28);
const u32 gMonBackPic_Quagsire[] = INCBIN_U32("assets/graphics.bin", 0x1209CC, 0x2FC);
const u32 gMonShinyPalette_Quagsire[] = INCBIN_U32("assets/graphics.bin", 0x120CC8, 0x28);
const u8 gMonIcon_Quagsire[] = INCBIN_U8("assets/graphics.bin", 0x120CF0, 0x400);
const u8 gMonFootprint_Quagsire[] = INCBIN_U8("assets/graphics.bin", 0x1210F0, 0x20);

const u32 gMonFrontPic_Espeon[] = INCBIN_U32("assets/graphics.bin", 0x121110, 0x340);
const u32 gMonPalette_Espeon[] = INCBIN_U32("assets/graphics.bin", 0x121450, 0x24);
const u32 gMonBackPic_Espeon[] = INCBIN_U32("assets/graphics.bin", 0x121474, 0x2DC);
const u32 gMonShinyPalette_Espeon[] = INCBIN_U32("assets/graphics.bin", 0x121750, 0x24);
const u8 gMonIcon_Espeon[] = INCBIN_U8("assets/graphics.bin", 0x121774, 0x400);
const u8 gMonFootprint_Espeon[] = INCBIN_U8("assets/graphics.bin", 0x121B74, 0x20);

const u32 gMonFrontPic_Umbreon[] = INCBIN_U32("assets/graphics.bin", 0x121B94, 0x314);
const u32 gMonPalette_Umbreon[] = INCBIN_U32("assets/graphics.bin", 0x121EA8, 0x28);
const u32 gMonBackPic_Umbreon[] = INCBIN_U32("assets/graphics.bin", 0x121ED0, 0x314);
const u32 gMonShinyPalette_Umbreon[] = INCBIN_U32("assets/graphics.bin", 0x1221E4, 0x28);
const u8 gMonIcon_Umbreon[] = INCBIN_U8("assets/graphics.bin", 0x12220C, 0x400);
const u8 gMonFootprint_Umbreon[] = INCBIN_U8("assets/graphics.bin", 0x12260C, 0x20);

const u32 gMonFrontPic_Murkrow[] = INCBIN_U32("assets/graphics.bin", 0x12262C, 0x2E0);
const u32 gMonPalette_Murkrow[] = INCBIN_U32("assets/graphics.bin", 0x12290C, 0x28);
const u32 gMonBackPic_Murkrow[] = INCBIN_U32("assets/graphics.bin", 0x122934, 0x318);
const u32 gMonShinyPalette_Murkrow[] = INCBIN_U32("assets/graphics.bin", 0x122C4C, 0x28);
const u8 gMonIcon_Murkrow[] = INCBIN_U8("assets/graphics.bin", 0x122C74, 0x400);
const u8 gMonFootprint_Murkrow[] = INCBIN_U8("assets/graphics.bin", 0x123074, 0x20);

const u32 gMonFrontPic_Slowking[] = INCBIN_U32("assets/graphics.bin", 0x123094, 0x3B4);
const u32 gMonPalette_Slowking[] = INCBIN_U32("assets/graphics.bin", 0x123448, 0x28);
const u32 gMonBackPic_Slowking[] = INCBIN_U32("assets/graphics.bin", 0x123470, 0x38C);
const u32 gMonShinyPalette_Slowking[] = INCBIN_U32("assets/graphics.bin", 0x1237FC, 0x28);
const u8 gMonIcon_Slowking[] = INCBIN_U8("assets/graphics.bin", 0x123824, 0x400);
const u8 gMonFootprint_Slowking[] = INCBIN_U8("assets/graphics.bin", 0x123C24, 0x20);

const u32 gMonFrontPic_Misdreavus[] = INCBIN_U32("assets/graphics.bin", 0x123C44, 0x2C0);
const u32 gMonPalette_Misdreavus[] = INCBIN_U32("assets/graphics.bin", 0x123F04, 0x28);
const u32 gMonBackPic_Misdreavus[] = INCBIN_U32("assets/graphics.bin", 0x123F2C, 0x324);
const u32 gMonShinyPalette_Misdreavus[] = INCBIN_U32("assets/graphics.bin", 0x124250, 0x28);
const u8 gMonIcon_Misdreavus[] = INCBIN_U8("assets/graphics.bin", 0x124278, 0x400);
const u8 gMonFootprint_Misdreavus[] = INCBIN_U8("assets/graphics.bin", 0x124678, 0x20);

const u32 gMonFrontPic_UnownA[] = INCBIN_U32("assets/graphics.bin", 0x124698, 0x1D4);
const u32 gMonPalette_Unown[] = INCBIN_U32("assets/graphics.bin", 0x12486C, 0x20);
const u32 gMonBackPic_UnownA[] = INCBIN_U32("assets/graphics.bin", 0x12488C, 0x200);
const u32 gMonShinyPalette_Unown[] = INCBIN_U32("assets/graphics.bin", 0x124A8C, 0x20);
const u8 gMonIcon_UnownA[] = INCBIN_U8("assets/graphics.bin", 0x124AAC, 0x400);
const u8 gMonFootprint_Unown[] = INCBIN_U8("assets/graphics.bin", 0x124EAC, 0x20);

const u32 gMonFrontPic_Wobbuffet[] = INCBIN_U32("assets/graphics.bin", 0x124ECC, 0x350);
const u32 gMonPalette_Wobbuffet[] = INCBIN_U32("assets/graphics.bin", 0x12521C, 0x28);
const u32 gMonBackPic_Wobbuffet[] = INCBIN_U32("assets/graphics.bin", 0x125244, 0x244);
const u32 gMonShinyPalette_Wobbuffet[] = INCBIN_U32("assets/graphics.bin", 0x125488, 0x28);
const u8 gMonIcon_Wobbuffet[] = INCBIN_U8("assets/graphics.bin", 0x1254B0, 0x400);
const u8 gMonFootprint_Wobbuffet[] = INCBIN_U8("assets/graphics.bin", 0x1258B0, 0x20);

const u32 gMonFrontPic_Girafarig[] = INCBIN_U32("assets/graphics.bin", 0x1258D0, 0x404);
const u32 gMonPalette_Girafarig[] = INCBIN_U32("assets/graphics.bin", 0x125CD4, 0x28);
const u32 gMonBackPic_Girafarig[] = INCBIN_U32("assets/graphics.bin", 0x125CFC, 0x3AC);
const u32 gMonShinyPalette_Girafarig[] = INCBIN_U32("assets/graphics.bin", 0x1260A8, 0x28);
const u8 gMonIcon_Girafarig[] = INCBIN_U8("assets/graphics.bin", 0x1260D0, 0x400);
const u8 gMonFootprint_Girafarig[] = INCBIN_U8("assets/graphics.bin", 0x1264D0, 0x20);

const u32 gMonFrontPic_Pineco[] = INCBIN_U32("assets/graphics.bin", 0x1264F0, 0x340);
const u32 gMonPalette_Pineco[] = INCBIN_U32("assets/graphics.bin", 0x126830, 0x24);
const u32 gMonBackPic_Pineco[] = INCBIN_U32("assets/graphics.bin", 0x126854, 0x2D8);
const u32 gMonShinyPalette_Pineco[] = INCBIN_U32("assets/graphics.bin", 0x126B2C, 0x24);
const u8 gMonIcon_Pineco[] = INCBIN_U8("assets/graphics.bin", 0x126B50, 0x400);
const u8 gMonFootprint_Pineco[] = INCBIN_U8("assets/graphics.bin", 0x126F50, 0x20);

const u32 gMonFrontPic_Forretress[] = INCBIN_U32("assets/graphics.bin", 0x126F70, 0x41C);
const u32 gMonPalette_Forretress[] = INCBIN_U32("assets/graphics.bin", 0x12738C, 0x28);
const u32 gMonBackPic_Forretress[] = INCBIN_U32("assets/graphics.bin", 0x1273B4, 0x2C0);
const u32 gMonShinyPalette_Forretress[] = INCBIN_U32("assets/graphics.bin", 0x127674, 0x28);
const u8 gMonIcon_Forretress[] = INCBIN_U8("assets/graphics.bin", 0x12769C, 0x400);
const u8 gMonFootprint_Forretress[] = INCBIN_U8("assets/graphics.bin", 0x127A9C, 0x20);

const u32 gMonFrontPic_Dunsparce[] = INCBIN_U32("assets/graphics.bin", 0x127ABC, 0x310);
const u32 gMonPalette_Dunsparce[] = INCBIN_U32("assets/graphics.bin", 0x127DCC, 0x28);
const u32 gMonBackPic_Dunsparce[] = INCBIN_U32("assets/graphics.bin", 0x127DF4, 0x2FC);
const u32 gMonShinyPalette_Dunsparce[] = INCBIN_U32("assets/graphics.bin", 0x1280F0, 0x28);
const u8 gMonIcon_Dunsparce[] = INCBIN_U8("assets/graphics.bin", 0x128118, 0x400);
const u8 gMonFootprint_Dunsparce[] = INCBIN_U8("assets/graphics.bin", 0x128518, 0x20);

const u32 gMonFrontPic_Gligar[] = INCBIN_U32("assets/graphics.bin", 0x128538, 0x428);
const u32 gMonPalette_Gligar[] = INCBIN_U32("assets/graphics.bin", 0x128960, 0x28);
const u32 gMonBackPic_Gligar[] = INCBIN_U32("assets/graphics.bin", 0x128988, 0x3D8);
const u32 gMonShinyPalette_Gligar[] = INCBIN_U32("assets/graphics.bin", 0x128D60, 0x28);
const u8 gMonIcon_Gligar[] = INCBIN_U8("assets/graphics.bin", 0x128D88, 0x400);
const u8 gMonFootprint_Gligar[] = INCBIN_U8("assets/graphics.bin", 0x129188, 0x20);

const u32 gMonFrontPic_Steelix[] = INCBIN_U32("assets/graphics.bin", 0x1291A8, 0x4C8);
const u32 gMonPalette_Steelix[] = INCBIN_U32("assets/graphics.bin", 0x129670, 0x24);
const u32 gMonBackPic_Steelix[] = INCBIN_U32("assets/graphics.bin", 0x129694, 0x40C);
const u32 gMonShinyPalette_Steelix[] = INCBIN_U32("assets/graphics.bin", 0x129AA0, 0x24);
const u8 gMonIcon_Steelix[] = INCBIN_U8("assets/graphics.bin", 0x129AC4, 0x400);
const u8 gMonFootprint_Steelix[] = INCBIN_U8("assets/graphics.bin", 0x129EC4, 0x20);

const u32 gMonFrontPic_Snubbull[] = INCBIN_U32("assets/graphics.bin", 0x129EE4, 0x2D4);
const u32 gMonPalette_Snubbull[] = INCBIN_U32("assets/graphics.bin", 0x12A1B8, 0x28);
const u32 gMonBackPic_Snubbull[] = INCBIN_U32("assets/graphics.bin", 0x12A1E0, 0x328);
const u32 gMonShinyPalette_Snubbull[] = INCBIN_U32("assets/graphics.bin", 0x12A508, 0x28);
const u8 gMonIcon_Snubbull[] = INCBIN_U8("assets/graphics.bin", 0x12A530, 0x400);
const u8 gMonFootprint_Snubbull[] = INCBIN_U8("assets/graphics.bin", 0x12A930, 0x20);

const u32 gMonFrontPic_Granbull[] = INCBIN_U32("assets/graphics.bin", 0x12A950, 0x38C);
const u32 gMonPalette_Granbull[] = INCBIN_U32("assets/graphics.bin", 0x12ACDC, 0x28);
const u32 gMonBackPic_Granbull[] = INCBIN_U32("assets/graphics.bin", 0x12AD04, 0x324);
const u32 gMonShinyPalette_Granbull[] = INCBIN_U32("assets/graphics.bin", 0x12B028, 0x28);
const u8 gMonIcon_Granbull[] = INCBIN_U8("assets/graphics.bin", 0x12B050, 0x400);
const u8 gMonFootprint_Granbull[] = INCBIN_U8("assets/graphics.bin", 0x12B450, 0x20);

const u32 gMonFrontPic_Qwilfish[] = INCBIN_U32("assets/graphics.bin", 0x12B470, 0x2C0);
const u32 gMonPalette_Qwilfish[] = INCBIN_U32("assets/graphics.bin", 0x12B730, 0x28);
const u32 gMonBackPic_Qwilfish[] = INCBIN_U32("assets/graphics.bin", 0x12B758, 0x2E0);
const u32 gMonShinyPalette_Qwilfish[] = INCBIN_U32("assets/graphics.bin", 0x12BA38, 0x28);
const u8 gMonIcon_Qwilfish[] = INCBIN_U8("assets/graphics.bin", 0x12BA60, 0x400);
const u8 gMonFootprint_Qwilfish[] = INCBIN_U8("assets/graphics.bin", 0x12BE60, 0x20);

const u32 gMonFrontPic_Scizor[] = INCBIN_U32("assets/graphics.bin", 0x12BE80, 0x4E8);
const u32 gMonPalette_Scizor[] = INCBIN_U32("assets/graphics.bin", 0x12C368, 0x28);
const u32 gMonBackPic_Scizor[] = INCBIN_U32("assets/graphics.bin", 0x12C390, 0x380);
const u32 gMonShinyPalette_Scizor[] = INCBIN_U32("assets/graphics.bin", 0x12C710, 0x28);
const u8 gMonIcon_Scizor[] = INCBIN_U8("assets/graphics.bin", 0x12C738, 0x400);
const u8 gMonFootprint_Scizor[] = INCBIN_U8("assets/graphics.bin", 0x12CB38, 0x20);

const u32 gMonFrontPic_Shuckle[] = INCBIN_U32("assets/graphics.bin", 0x12CB58, 0x2C8);
const u32 gMonPalette_Shuckle[] = INCBIN_U32("assets/graphics.bin", 0x12CE20, 0x28);
const u32 gMonBackPic_Shuckle[] = INCBIN_U32("assets/graphics.bin", 0x12CE48, 0x258);
const u32 gMonShinyPalette_Shuckle[] = INCBIN_U32("assets/graphics.bin", 0x12D0A0, 0x28);
const u8 gMonIcon_Shuckle[] = INCBIN_U8("assets/graphics.bin", 0x12D0C8, 0x400);
const u8 gMonFootprint_Shuckle[] = INCBIN_U8("assets/graphics.bin", 0x12D4C8, 0x20);

const u32 gMonFrontPic_Heracross[] = INCBIN_U32("assets/graphics.bin", 0x12D4E8, 0x3F0);
const u32 gMonPalette_Heracross[] = INCBIN_U32("assets/graphics.bin", 0x12D8D8, 0x28);
const u32 gMonBackPic_Heracross[] = INCBIN_U32("assets/graphics.bin", 0x12D900, 0x370);
const u32 gMonShinyPalette_Heracross[] = INCBIN_U32("assets/graphics.bin", 0x12DC70, 0x28);
const u8 gMonIcon_Heracross[] = INCBIN_U8("assets/graphics.bin", 0x12DC98, 0x400);
const u8 gUnknown_heracross_icon[] = INCBIN_U8("assets/graphics.bin", 0x12E098, 0x400);
const u8 gMonFootprint_Heracross[] = INCBIN_U8("assets/graphics.bin", 0x12E498, 0x20);

const u32 gMonFrontPic_Sneasel[] = INCBIN_U32("assets/graphics.bin", 0x12E4B8, 0x344);
const u32 gMonPalette_Sneasel[] = INCBIN_U32("assets/graphics.bin", 0x12E7FC, 0x28);
const u32 gMonBackPic_Sneasel[] = INCBIN_U32("assets/graphics.bin", 0x12E824, 0x324);
const u32 gMonShinyPalette_Sneasel[] = INCBIN_U32("assets/graphics.bin", 0x12EB48, 0x28);
const u8 gMonIcon_Sneasel[] = INCBIN_U8("assets/graphics.bin", 0x12EB70, 0x400);
const u8 gMonFootprint_Sneasel[] = INCBIN_U8("assets/graphics.bin", 0x12EF70, 0x20);

const u32 gMonFrontPic_Teddiursa[] = INCBIN_U32("assets/graphics.bin", 0x12EF90, 0x2A8);
const u32 gMonPalette_Teddiursa[] = INCBIN_U32("assets/graphics.bin", 0x12F238, 0x28);
const u32 gMonBackPic_Teddiursa[] = INCBIN_U32("assets/graphics.bin", 0x12F260, 0x278);
const u32 gMonShinyPalette_Teddiursa[] = INCBIN_U32("assets/graphics.bin", 0x12F4D8, 0x28);
const u8 gMonIcon_Teddiursa[] = INCBIN_U8("assets/graphics.bin", 0x12F500, 0x400);
const u8 gMonFootprint_Teddiursa[] = INCBIN_U8("assets/graphics.bin", 0x12F900, 0x20);

const u32 gMonFrontPic_Ursaring[] = INCBIN_U32("assets/graphics.bin", 0x12F920, 0x438);
const u32 gMonPalette_Ursaring[] = INCBIN_U32("assets/graphics.bin", 0x12FD58, 0x28);
const u32 gMonBackPic_Ursaring[] = INCBIN_U32("assets/graphics.bin", 0x12FD80, 0x388);
const u32 gMonShinyPalette_Ursaring[] = INCBIN_U32("assets/graphics.bin", 0x130108, 0x28);
const u8 gMonIcon_Ursaring[] = INCBIN_U8("assets/graphics.bin", 0x130130, 0x400);
const u8 gMonFootprint_Ursaring[] = INCBIN_U8("assets/graphics.bin", 0x130530, 0x20);

const u32 gMonFrontPic_Slugma[] = INCBIN_U32("assets/graphics.bin", 0x130550, 0x274);
const u32 gMonPalette_Slugma[] = INCBIN_U32("assets/graphics.bin", 0x1307C4, 0x24);
const u32 gMonBackPic_Slugma[] = INCBIN_U32("assets/graphics.bin", 0x1307E8, 0x2E8);
const u32 gMonShinyPalette_Slugma[] = INCBIN_U32("assets/graphics.bin", 0x130AD0, 0x24);
const u8 gMonIcon_Slugma[] = INCBIN_U8("assets/graphics.bin", 0x130AF4, 0x400);
const u8 gMonFootprint_Slugma[] = INCBIN_U8("assets/graphics.bin", 0x130EF4, 0x20);

const u32 gMonFrontPic_Magcargo[] = INCBIN_U32("assets/graphics.bin", 0x130F14, 0x348);
const u32 gMonPalette_Magcargo[] = INCBIN_U32("assets/graphics.bin", 0x13125C, 0x28);
const u32 gMonBackPic_Magcargo[] = INCBIN_U32("assets/graphics.bin", 0x131284, 0x418);
const u32 gMonShinyPalette_Magcargo[] = INCBIN_U32("assets/graphics.bin", 0x13169C, 0x28);
const u8 gMonIcon_Magcargo[] = INCBIN_U8("assets/graphics.bin", 0x1316C4, 0x400);
const u8 gMonFootprint_Magcargo[] = INCBIN_U8("assets/graphics.bin", 0x131AC4, 0x20);

const u32 gMonFrontPic_Swinub[] = INCBIN_U32("assets/graphics.bin", 0x131AE4, 0x1FC);
const u32 gMonPalette_Swinub[] = INCBIN_U32("assets/graphics.bin", 0x131CE0, 0x28);
const u32 gMonBackPic_Swinub[] = INCBIN_U32("assets/graphics.bin", 0x131D08, 0x23C);
const u32 gMonShinyPalette_Swinub[] = INCBIN_U32("assets/graphics.bin", 0x131F44, 0x28);
const u8 gMonIcon_Swinub[] = INCBIN_U8("assets/graphics.bin", 0x131F6C, 0x400);
const u8 gMonFootprint_Swinub[] = INCBIN_U8("assets/graphics.bin", 0x13236C, 0x20);

const u32 gMonFrontPic_Piloswine[] = INCBIN_U32("assets/graphics.bin", 0x13238C, 0x328);
const u32 gMonPalette_Piloswine[] = INCBIN_U32("assets/graphics.bin", 0x1326B4, 0x28);
const u32 gMonBackPic_Piloswine[] = INCBIN_U32("assets/graphics.bin", 0x1326DC, 0x24C);
const u32 gMonShinyPalette_Piloswine[] = INCBIN_U32("assets/graphics.bin", 0x132928, 0x28);
const u8 gMonIcon_Piloswine[] = INCBIN_U8("assets/graphics.bin", 0x132950, 0x400);
const u8 gMonFootprint_Piloswine[] = INCBIN_U8("assets/graphics.bin", 0x132D50, 0x20);

const u32 gMonFrontPic_Corsola[] = INCBIN_U32("assets/graphics.bin", 0x132D70, 0x2E8);
const u32 gMonPalette_Corsola[] = INCBIN_U32("assets/graphics.bin", 0x133058, 0x28);
const u32 gMonBackPic_Corsola[] = INCBIN_U32("assets/graphics.bin", 0x133080, 0x2C0);
const u32 gMonShinyPalette_Corsola[] = INCBIN_U32("assets/graphics.bin", 0x133340, 0x28);
const u8 gMonIcon_Corsola[] = INCBIN_U8("assets/graphics.bin", 0x133368, 0x400);
const u8 gMonFootprint_Corsola[] = INCBIN_U8("assets/graphics.bin", 0x133768, 0x20);

const u32 gMonFrontPic_Remoraid[] = INCBIN_U32("assets/graphics.bin", 0x133788, 0x268);
const u32 gMonPalette_Remoraid[] = INCBIN_U32("assets/graphics.bin", 0x1339F0, 0x28);
const u32 gMonBackPic_Remoraid[] = INCBIN_U32("assets/graphics.bin", 0x133A18, 0x314);
const u32 gMonShinyPalette_Remoraid[] = INCBIN_U32("assets/graphics.bin", 0x133D2C, 0x28);
const u8 gMonIcon_Remoraid[] = INCBIN_U8("assets/graphics.bin", 0x133D54, 0x400);
const u8 gMonFootprint_Remoraid[] = INCBIN_U8("assets/graphics.bin", 0x134154, 0x20);

const u32 gMonFrontPic_Octillery[] = INCBIN_U32("assets/graphics.bin", 0x134174, 0x334);
const u32 gMonPalette_Octillery[] = INCBIN_U32("assets/graphics.bin", 0x1344A8, 0x28);
const u32 gMonBackPic_Octillery[] = INCBIN_U32("assets/graphics.bin", 0x1344D0, 0x2B8);
const u32 gMonShinyPalette_Octillery[] = INCBIN_U32("assets/graphics.bin", 0x134788, 0x28);
const u8 gMonIcon_Octillery[] = INCBIN_U8("assets/graphics.bin", 0x1347B0, 0x400);
const u8 gMonFootprint_Octillery[] = INCBIN_U8("assets/graphics.bin", 0x134BB0, 0x20);

const u32 gMonFrontPic_Delibird[] = INCBIN_U32("assets/graphics.bin", 0x134BD0, 0x370);
const u32 gMonPalette_Delibird[] = INCBIN_U32("assets/graphics.bin", 0x134F40, 0x28);
const u32 gMonBackPic_Delibird[] = INCBIN_U32("assets/graphics.bin", 0x134F68, 0x3C0);
const u32 gMonShinyPalette_Delibird[] = INCBIN_U32("assets/graphics.bin", 0x135328, 0x28);
const u8 gMonIcon_Delibird[] = INCBIN_U8("assets/graphics.bin", 0x135350, 0x400);
const u8 gMonFootprint_Delibird[] = INCBIN_U8("assets/graphics.bin", 0x135750, 0x20);

const u32 gMonFrontPic_Mantine[] = INCBIN_U32("assets/graphics.bin", 0x135770, 0x49C);
const u32 gMonPalette_Mantine[] = INCBIN_U32("assets/graphics.bin", 0x135C0C, 0x28);
const u32 gMonBackPic_Mantine[] = INCBIN_U32("assets/graphics.bin", 0x135C34, 0x2A0);
const u32 gMonShinyPalette_Mantine[] = INCBIN_U32("assets/graphics.bin", 0x135ED4, 0x28);
const u8 gMonIcon_Mantine[] = INCBIN_U8("assets/graphics.bin", 0x135EFC, 0x400);
const u8 gMonFootprint_Mantine[] = INCBIN_U8("assets/graphics.bin", 0x1362FC, 0x20);

const u32 gMonFrontPic_Skarmory[] = INCBIN_U32("assets/graphics.bin", 0x13631C, 0x4E0);
const u32 gMonPalette_Skarmory[] = INCBIN_U32("assets/graphics.bin", 0x1367FC, 0x28);
const u32 gMonBackPic_Skarmory[] = INCBIN_U32("assets/graphics.bin", 0x136824, 0x304);
const u32 gMonShinyPalette_Skarmory[] = INCBIN_U32("assets/graphics.bin", 0x136B28, 0x28);
const u8 gMonIcon_Skarmory[] = INCBIN_U8("assets/graphics.bin", 0x136B50, 0x400);
const u8 gMonFootprint_Skarmory[] = INCBIN_U8("assets/graphics.bin", 0x136F50, 0x20);

const u32 gMonFrontPic_Houndour[] = INCBIN_U32("assets/graphics.bin", 0x136F70, 0x2B8);
const u32 gMonPalette_Houndour[] = INCBIN_U32("assets/graphics.bin", 0x137228, 0x28);
const u32 gMonBackPic_Houndour[] = INCBIN_U32("assets/graphics.bin", 0x137250, 0x280);
const u32 gMonShinyPalette_Houndour[] = INCBIN_U32("assets/graphics.bin", 0x1374D0, 0x28);
const u8 gMonIcon_Houndour[] = INCBIN_U8("assets/graphics.bin", 0x1374F8, 0x400);
const u8 gMonFootprint_Houndour[] = INCBIN_U8("assets/graphics.bin", 0x1378F8, 0x20);

const u32 gMonFrontPic_Houndoom[] = INCBIN_U32("assets/graphics.bin", 0x137918, 0x400);
const u32 gMonPalette_Houndoom[] = INCBIN_U32("assets/graphics.bin", 0x137D18, 0x28);
const u32 gMonBackPic_Houndoom[] = INCBIN_U32("assets/graphics.bin", 0x137D40, 0x324);
const u32 gMonShinyPalette_Houndoom[] = INCBIN_U32("assets/graphics.bin", 0x138064, 0x28);
const u8 gMonIcon_Houndoom[] = INCBIN_U8("assets/graphics.bin", 0x13808C, 0x400);
const u8 gMonFootprint_Houndoom[] = INCBIN_U8("assets/graphics.bin", 0x13848C, 0x20);

const u32 gMonFrontPic_Kingdra[] = INCBIN_U32("assets/graphics.bin", 0x1384AC, 0x420);
const u32 gMonPalette_Kingdra[] = INCBIN_U32("assets/graphics.bin", 0x1388CC, 0x28);
const u32 gMonBackPic_Kingdra[] = INCBIN_U32("assets/graphics.bin", 0x1388F4, 0x3B4);
const u32 gMonShinyPalette_Kingdra[] = INCBIN_U32("assets/graphics.bin", 0x138CA8, 0x28);
const u8 gMonIcon_Kingdra[] = INCBIN_U8("assets/graphics.bin", 0x138CD0, 0x400);
const u8 gMonFootprint_Kingdra[] = INCBIN_U8("assets/graphics.bin", 0x1390D0, 0x20);

const u32 gMonFrontPic_Phanpy[] = INCBIN_U32("assets/graphics.bin", 0x1390F0, 0x25C);
const u32 gMonPalette_Phanpy[] = INCBIN_U32("assets/graphics.bin", 0x13934C, 0x28);
const u32 gMonBackPic_Phanpy[] = INCBIN_U32("assets/graphics.bin", 0x139374, 0x2C4);
const u32 gMonShinyPalette_Phanpy[] = INCBIN_U32("assets/graphics.bin", 0x139638, 0x28);
const u8 gMonIcon_Phanpy[] = INCBIN_U8("assets/graphics.bin", 0x139660, 0x400);
const u8 gMonFootprint_Phanpy[] = INCBIN_U8("assets/graphics.bin", 0x139A60, 0x20);

const u32 gMonFrontPic_Donphan[] = INCBIN_U32("assets/graphics.bin", 0x139A80, 0x474);
const u32 gMonPalette_Donphan[] = INCBIN_U32("assets/graphics.bin", 0x139EF4, 0x28);
const u32 gMonBackPic_Donphan[] = INCBIN_U32("assets/graphics.bin", 0x139F1C, 0x2FC);
const u32 gMonShinyPalette_Donphan[] = INCBIN_U32("assets/graphics.bin", 0x13A218, 0x28);
const u8 gMonIcon_Donphan[] = INCBIN_U8("assets/graphics.bin", 0x13A240, 0x400);
const u8 gMonFootprint_Donphan[] = INCBIN_U8("assets/graphics.bin", 0x13A640, 0x20);

const u32 gMonFrontPic_Porygon2[] = INCBIN_U32("assets/graphics.bin", 0x13A660, 0x288);
const u32 gMonPalette_Porygon2[] = INCBIN_U32("assets/graphics.bin", 0x13A8E8, 0x28);
const u32 gMonBackPic_Porygon2[] = INCBIN_U32("assets/graphics.bin", 0x13A910, 0x31C);
const u32 gMonShinyPalette_Porygon2[] = INCBIN_U32("assets/graphics.bin", 0x13AC2C, 0x28);
const u8 gMonIcon_Porygon2[] = INCBIN_U8("assets/graphics.bin", 0x13AC54, 0x400);
const u8 gMonFootprint_Porygon2[] = INCBIN_U8("assets/graphics.bin", 0x13B054, 0x20);

const u32 gMonFrontPic_Stantler[] = INCBIN_U32("assets/graphics.bin", 0x13B074, 0x414);
const u32 gMonPalette_Stantler[] = INCBIN_U32("assets/graphics.bin", 0x13B488, 0x28);
const u32 gMonBackPic_Stantler[] = INCBIN_U32("assets/graphics.bin", 0x13B4B0, 0x34C);
const u32 gMonShinyPalette_Stantler[] = INCBIN_U32("assets/graphics.bin", 0x13B7FC, 0x28);
const u8 gMonIcon_Stantler[] = INCBIN_U8("assets/graphics.bin", 0x13B824, 0x400);
const u8 gMonFootprint_Stantler[] = INCBIN_U8("assets/graphics.bin", 0x13BC24, 0x20);

const u32 gMonFrontPic_Smeargle[] = INCBIN_U32("assets/graphics.bin", 0x13BC44, 0x394);
const u32 gMonPalette_Smeargle[] = INCBIN_U32("assets/graphics.bin", 0x13BFD8, 0x28);
const u32 gMonBackPic_Smeargle[] = INCBIN_U32("assets/graphics.bin", 0x13C000, 0x324);
const u32 gMonShinyPalette_Smeargle[] = INCBIN_U32("assets/graphics.bin", 0x13C324, 0x28);
const u8 gMonIcon_Smeargle[] = INCBIN_U8("assets/graphics.bin", 0x13C34C, 0x400);
const u8 gMonFootprint_Smeargle[] = INCBIN_U8("assets/graphics.bin", 0x13C74C, 0x20);

const u32 gMonFrontPic_Tyrogue[] = INCBIN_U32("assets/graphics.bin", 0x13C76C, 0x28C);
const u32 gMonPalette_Tyrogue[] = INCBIN_U32("assets/graphics.bin", 0x13C9F8, 0x28);
const u32 gMonBackPic_Tyrogue[] = INCBIN_U32("assets/graphics.bin", 0x13CA20, 0x31C);
const u32 gMonShinyPalette_Tyrogue[] = INCBIN_U32("assets/graphics.bin", 0x13CD3C, 0x28);
const u8 gMonIcon_Tyrogue[] = INCBIN_U8("assets/graphics.bin", 0x13CD64, 0x400);
const u8 gMonFootprint_Tyrogue[] = INCBIN_U8("assets/graphics.bin", 0x13D164, 0x20);

const u32 gMonFrontPic_Hitmontop[] = INCBIN_U32("assets/graphics.bin", 0x13D184, 0x38C);
const u32 gMonPalette_Hitmontop[] = INCBIN_U32("assets/graphics.bin", 0x13D510, 0x28);
const u32 gMonBackPic_Hitmontop[] = INCBIN_U32("assets/graphics.bin", 0x13D538, 0x428);
const u32 gMonShinyPalette_Hitmontop[] = INCBIN_U32("assets/graphics.bin", 0x13D960, 0x28);
const u8 gMonIcon_Hitmontop[] = INCBIN_U8("assets/graphics.bin", 0x13D988, 0x400);

// This might be undefined memory garbage. Its all 00s except for 1 0F. Its also not referenced.
const u32 gUnusedGarbage[] = INCBIN_U32("assets/graphics.bin", 0x13DD88, 0x200);

const u8 gMonFootprint_Hitmontop[] = INCBIN_U8("assets/graphics.bin", 0x13DF88, 0x20);

const u32 gMonFrontPic_Smoochum[] = INCBIN_U32("assets/graphics.bin", 0x13DFA8, 0x258);
const u32 gMonPalette_Smoochum[] = INCBIN_U32("assets/graphics.bin", 0x13E200, 0x28);
const u32 gMonBackPic_Smoochum[] = INCBIN_U32("assets/graphics.bin", 0x13E228, 0x278);
const u32 gMonShinyPalette_Smoochum[] = INCBIN_U32("assets/graphics.bin", 0x13E4A0, 0x28);
const u8 gMonIcon_Smoochum[] = INCBIN_U8("assets/graphics.bin", 0x13E4C8, 0x400);
const u8 gMonFootprint_Smoochum[] = INCBIN_U8("assets/graphics.bin", 0x13E8C8, 0x20);

const u32 gMonFrontPic_Elekid[] = INCBIN_U32("assets/graphics.bin", 0x13E8E8, 0x308);
const u32 gMonPalette_Elekid[] = INCBIN_U32("assets/graphics.bin", 0x13EBF0, 0x28);
const u32 gMonBackPic_Elekid[] = INCBIN_U32("assets/graphics.bin", 0x13EC18, 0x358);
const u32 gMonShinyPalette_Elekid[] = INCBIN_U32("assets/graphics.bin", 0x13EF70, 0x28);
const u8 gMonIcon_Elekid[] = INCBIN_U8("assets/graphics.bin", 0x13EF98, 0x400);
const u8 gMonFootprint_Elekid[] = INCBIN_U8("assets/graphics.bin", 0x13F398, 0x20);

const u32 gMonFrontPic_Magby[] = INCBIN_U32("assets/graphics.bin", 0x13F3B8, 0x284);
const u32 gMonPalette_Magby[] = INCBIN_U32("assets/graphics.bin", 0x13F63C, 0x28);
const u32 gMonBackPic_Magby[] = INCBIN_U32("assets/graphics.bin", 0x13F664, 0x2AC);
const u32 gMonShinyPalette_Magby[] = INCBIN_U32("assets/graphics.bin", 0x13F910, 0x28);
const u8 gMonIcon_Magby[] = INCBIN_U8("assets/graphics.bin", 0x13F938, 0x400);
const u8 gMonFootprint_Magby[] = INCBIN_U8("assets/graphics.bin", 0x13FD38, 0x20);

const u32 gMonFrontPic_Miltank[] = INCBIN_U32("assets/graphics.bin", 0x13FD58, 0x3B0);
const u32 gMonPalette_Miltank[] = INCBIN_U32("assets/graphics.bin", 0x140108, 0x28);
const u32 gMonBackPic_Miltank[] = INCBIN_U32("assets/graphics.bin", 0x140130, 0x39C);
const u32 gMonShinyPalette_Miltank[] = INCBIN_U32("assets/graphics.bin", 0x1404CC, 0x28);
const u8 gMonIcon_Miltank[] = INCBIN_U8("assets/graphics.bin", 0x1404F4, 0x400);
const u8 gMonFootprint_Miltank[] = INCBIN_U8("assets/graphics.bin", 0x1408F4, 0x20);

const u32 gMonFrontPic_Blissey[] = INCBIN_U32("assets/graphics.bin", 0x140914, 0x3E8);
const u32 gMonPalette_Blissey[] = INCBIN_U32("assets/graphics.bin", 0x140CFC, 0x28);
const u32 gMonBackPic_Blissey[] = INCBIN_U32("assets/graphics.bin", 0x140D24, 0x2CC);
const u32 gMonShinyPalette_Blissey[] = INCBIN_U32("assets/graphics.bin", 0x140FF0, 0x28);
const u8 gMonIcon_Blissey[] = INCBIN_U8("assets/graphics.bin", 0x141018, 0x400);
const u8 gMonFootprint_Blissey[] = INCBIN_U8("assets/graphics.bin", 0x141418, 0x20);

const u32 gMonFrontPic_Raikou[] = INCBIN_U32("assets/graphics.bin", 0x141438, 0x57C);
const u32 gMonPalette_Raikou[] = INCBIN_U32("assets/graphics.bin", 0x1419B4, 0x28);
const u32 gMonBackPic_Raikou[] = INCBIN_U32("assets/graphics.bin", 0x1419DC, 0x3A8);
const u32 gMonShinyPalette_Raikou[] = INCBIN_U32("assets/graphics.bin", 0x141D84, 0x28);
const u8 gMonIcon_Raikou[] = INCBIN_U8("assets/graphics.bin", 0x141DAC, 0x400);
const u8 gMonFootprint_Raikou[] = INCBIN_U8("assets/graphics.bin", 0x1421AC, 0x20);

const u32 gMonFrontPic_Entei[] = INCBIN_U32("assets/graphics.bin", 0x1421CC, 0x5FC);
const u32 gMonPalette_Entei[] = INCBIN_U32("assets/graphics.bin", 0x1427C8, 0x28);
const u32 gMonBackPic_Entei[] = INCBIN_U32("assets/graphics.bin", 0x1427F0, 0x424);
const u32 gMonShinyPalette_Entei[] = INCBIN_U32("assets/graphics.bin", 0x142C14, 0x28);
const u8 gMonIcon_Entei[] = INCBIN_U8("assets/graphics.bin", 0x142C3C, 0x400);
const u8 gMonFootprint_Entei[] = INCBIN_U8("assets/graphics.bin", 0x14303C, 0x20);

const u32 gMonFrontPic_Suicune[] = INCBIN_U32("assets/graphics.bin", 0x14305C, 0x584);
const u32 gMonPalette_Suicune[] = INCBIN_U32("assets/graphics.bin", 0x1435E0, 0x28);
const u32 gMonBackPic_Suicune[] = INCBIN_U32("assets/graphics.bin", 0x143608, 0x4DC);
const u32 gMonShinyPalette_Suicune[] = INCBIN_U32("assets/graphics.bin", 0x143AE4, 0x28);
const u8 gMonIcon_Suicune[] = INCBIN_U8("assets/graphics.bin", 0x143B0C, 0x400);
const u8 gMonFootprint_Suicune[] = INCBIN_U8("assets/graphics.bin", 0x143F0C, 0x20);

const u32 gMonFrontPic_Larvitar[] = INCBIN_U32("assets/graphics.bin", 0x143F2C, 0x25C);
const u32 gMonPalette_Larvitar[] = INCBIN_U32("assets/graphics.bin", 0x144188, 0x28);
const u32 gMonBackPic_Larvitar[] = INCBIN_U32("assets/graphics.bin", 0x1441B0, 0x2AC);
const u32 gMonShinyPalette_Larvitar[] = INCBIN_U32("assets/graphics.bin", 0x14445C, 0x28);
const u8 gMonIcon_Larvitar[] = INCBIN_U8("assets/graphics.bin", 0x144484, 0x400);
const u8 gMonFootprint_Larvitar[] = INCBIN_U8("assets/graphics.bin", 0x144884, 0x20);

const u32 gMonFrontPic_Pupitar[] = INCBIN_U32("assets/graphics.bin", 0x1448A4, 0x2F0);
const u32 gMonPalette_Pupitar[] = INCBIN_U32("assets/graphics.bin", 0x144B94, 0x28);
const u32 gMonBackPic_Pupitar[] = INCBIN_U32("assets/graphics.bin", 0x144BBC, 0x338);
const u32 gMonShinyPalette_Pupitar[] = INCBIN_U32("assets/graphics.bin", 0x144EF4, 0x28);
const u8 gMonIcon_Pupitar[] = INCBIN_U8("assets/graphics.bin", 0x144F1C, 0x400);
const u8 gMonFootprint_Pupitar[] = INCBIN_U8("assets/graphics.bin", 0x14531C, 0x20);

const u32 gMonFrontPic_Tyranitar[] = INCBIN_U32("assets/graphics.bin", 0x14533C, 0x53C);
const u32 gMonPalette_Tyranitar[] = INCBIN_U32("assets/graphics.bin", 0x145878, 0x28);
const u32 gMonBackPic_Tyranitar[] = INCBIN_U32("assets/graphics.bin", 0x1458A0, 0x3EC);
const u32 gMonShinyPalette_Tyranitar[] = INCBIN_U32("assets/graphics.bin", 0x145C8C, 0x28);
const u8 gMonIcon_Tyranitar[] = INCBIN_U8("assets/graphics.bin", 0x145CB4, 0x400);
const u8 gMonFootprint_Tyranitar[] = INCBIN_U8("assets/graphics.bin", 0x1460B4, 0x20);

const u32 gMonFrontPic_Lugia[] = INCBIN_U32("assets/graphics.bin", 0x1460D4, 0x4C4);
const u32 gMonPalette_Lugia[] = INCBIN_U32("assets/graphics.bin", 0x146598, 0x28);
const u32 gMonBackPic_Lugia[] = INCBIN_U32("assets/graphics.bin", 0x1465C0, 0x3D4);
const u32 gMonShinyPalette_Lugia[] = INCBIN_U32("assets/graphics.bin", 0x146994, 0x28);
const u8 gMonIcon_Lugia[] = INCBIN_U8("assets/graphics.bin", 0x1469BC, 0x400);
const u8 gMonFootprint_Lugia[] = INCBIN_U8("assets/graphics.bin", 0x146DBC, 0x20);

const u32 gMonFrontPic_HoOh[] = INCBIN_U32("assets/graphics.bin", 0x146DDC, 0x654);
const u32 gMonPalette_HoOh[] = INCBIN_U32("assets/graphics.bin", 0x147430, 0x28);
const u32 gMonBackPic_HoOh[] = INCBIN_U32("assets/graphics.bin", 0x147458, 0x410);
const u32 gMonShinyPalette_HoOh[] = INCBIN_U32("assets/graphics.bin", 0x147868, 0x28);
const u8 gMonIcon_HoOh[] = INCBIN_U8("assets/graphics.bin", 0x147890, 0x400);
const u8 gMonFootprint_HoOh[] = INCBIN_U8("assets/graphics.bin", 0x147C90, 0x20);

const u32 gMonFrontPic_Celebi[] = INCBIN_U32("assets/graphics.bin", 0x147CB0, 0x278);
const u32 gMonPalette_Celebi[] = INCBIN_U32("assets/graphics.bin", 0x147F28, 0x28);
const u32 gMonBackPic_Celebi[] = INCBIN_U32("assets/graphics.bin", 0x147F50, 0x3AC);
const u32 gMonShinyPalette_Celebi[] = INCBIN_U32("assets/graphics.bin", 0x1482FC, 0x28);
const u8 gMonIcon_Celebi[] = INCBIN_U8("assets/graphics.bin", 0x148324, 0x400);
const u8 gMonFootprint_Celebi[] = INCBIN_U8("assets/graphics.bin", 0x148724, 0x20);

const u32 gMonFrontPic_DoubleQuestionMark[] = INCBIN_U32("assets/graphics.bin", 0x148744, 0x184);
const u32 gMonPalette_DoubleQuestionMark[] = INCBIN_U32("assets/graphics.bin", 0x1488C8, 0x14);
const u32 gMonBackPic_DoubleQuestionMark[] = INCBIN_U32("assets/graphics.bin", 0x1488DC, 0x184);
const u32 gMonShinyPalette_DoubleQuestionMark[] = INCBIN_U32("assets/graphics.bin", 0x148A60, 0x14);

const u32 gMonFrontPic_Treecko[] = INCBIN_U32("assets/graphics.bin", 0x148A74, 0x308);
const u32 gMonPalette_Treecko[] = INCBIN_U32("assets/graphics.bin", 0x148D7C, 0x28);
const u32 gMonBackPic_Treecko[] = INCBIN_U32("assets/graphics.bin", 0x148DA4, 0x300);
const u32 gMonShinyPalette_Treecko[] = INCBIN_U32("assets/graphics.bin", 0x1490A4, 0x28);
const u8 gMonIcon_Treecko[] = INCBIN_U8("assets/graphics.bin", 0x1490CC, 0x400);
const u8 gMonFootprint_Treecko[] = INCBIN_U8("assets/graphics.bin", 0x1494CC, 0x20);

const u32 gMonFrontPic_Grovyle[] = INCBIN_U32("assets/graphics.bin", 0x1494EC, 0x48C);
const u32 gMonPalette_Grovyle[] = INCBIN_U32("assets/graphics.bin", 0x149978, 0x28);
const u32 gMonBackPic_Grovyle[] = INCBIN_U32("assets/graphics.bin", 0x1499A0, 0x33C);
const u32 gMonShinyPalette_Grovyle[] = INCBIN_U32("assets/graphics.bin", 0x149CDC, 0x28);
const u8 gMonIcon_Grovyle[] = INCBIN_U8("assets/graphics.bin", 0x149D04, 0x400);
const u8 gMonFootprint_Grovyle[] = INCBIN_U8("assets/graphics.bin", 0x14A104, 0x20);

const u32 gMonFrontPic_Sceptile[] = INCBIN_U32("assets/graphics.bin", 0x14A124, 0x504);
const u32 gMonPalette_Sceptile[] = INCBIN_U32("assets/graphics.bin", 0x14A628, 0x28);
const u32 gMonBackPic_Sceptile[] = INCBIN_U32("assets/graphics.bin", 0x14A650, 0x3FC);
const u32 gMonShinyPalette_Sceptile[] = INCBIN_U32("assets/graphics.bin", 0x14AA4C, 0x28);
const u8 gMonIcon_Sceptile[] = INCBIN_U8("assets/graphics.bin", 0x14AA74, 0x400);
const u8 gMonFootprint_Sceptile[] = INCBIN_U8("assets/graphics.bin", 0x14AE74, 0x20);

const u32 gMonFrontPic_Torchic[] = INCBIN_U32("assets/graphics.bin", 0x14AE94, 0x29C);
const u32 gMonPalette_Torchic[] = INCBIN_U32("assets/graphics.bin", 0x14B130, 0x28);
const u32 gMonBackPic_Torchic[] = INCBIN_U32("assets/graphics.bin", 0x14B158, 0x2D8);
const u32 gMonShinyPalette_Torchic[] = INCBIN_U32("assets/graphics.bin", 0x14B430, 0x28);
const u8 gMonIcon_Torchic[] = INCBIN_U8("assets/graphics.bin", 0x14B458, 0x400);
const u8 gMonFootprint_Torchic[] = INCBIN_U8("assets/graphics.bin", 0x14B858, 0x20);

const u32 gMonFrontPic_Combusken[] = INCBIN_U32("assets/graphics.bin", 0x14B878, 0x3EC);
const u32 gMonPalette_Combusken[] = INCBIN_U32("assets/graphics.bin", 0x14BC64, 0x28);
const u32 gMonBackPic_Combusken[] = INCBIN_U32("assets/graphics.bin", 0x14BC8C, 0x3D0);
const u32 gMonShinyPalette_Combusken[] = INCBIN_U32("assets/graphics.bin", 0x14C05C, 0x28);
const u8 gMonIcon_Combusken[] = INCBIN_U8("assets/graphics.bin", 0x14C084, 0x400);
const u8 gMonFootprint_Combusken[] = INCBIN_U8("assets/graphics.bin", 0x14C484, 0x20);

const u32 gMonFrontPic_Blaziken[] = INCBIN_U32("assets/graphics.bin", 0x14C4A4, 0x478);
const u32 gMonPalette_Blaziken[] = INCBIN_U32("assets/graphics.bin", 0x14C91C, 0x28);
const u32 gMonBackPic_Blaziken[] = INCBIN_U32("assets/graphics.bin", 0x14C944, 0x3DC);
const u32 gMonShinyPalette_Blaziken[] = INCBIN_U32("assets/graphics.bin", 0x14CD20, 0x28);
const u8 gMonIcon_Blaziken[] = INCBIN_U8("assets/graphics.bin", 0x14CD48, 0x400);
const u8 gMonFootprint_Blaziken[] = INCBIN_U8("assets/graphics.bin", 0x14D148, 0x20);

const u32 gMonFrontPic_Mudkip[] = INCBIN_U32("assets/graphics.bin", 0x14D168, 0x2B8);
const u32 gMonPalette_Mudkip[] = INCBIN_U32("assets/graphics.bin", 0x14D420, 0x28);
const u32 gMonBackPic_Mudkip[] = INCBIN_U32("assets/graphics.bin", 0x14D448, 0x2E0);
const u32 gMonShinyPalette_Mudkip[] = INCBIN_U32("assets/graphics.bin", 0x14D728, 0x28);
const u8 gMonIcon_Mudkip[] = INCBIN_U8("assets/graphics.bin", 0x14D750, 0x400);
const u8 gMonFootprint_Mudkip[] = INCBIN_U8("assets/graphics.bin", 0x14DB50, 0x20);

const u32 gMonFrontPic_Marshtomp[] = INCBIN_U32("assets/graphics.bin", 0x14DB70, 0x388);
const u32 gMonPalette_Marshtomp[] = INCBIN_U32("assets/graphics.bin", 0x14DEF8, 0x28);
const u32 gMonBackPic_Marshtomp[] = INCBIN_U32("assets/graphics.bin", 0x14DF20, 0x3B0);
const u32 gMonShinyPalette_Marshtomp[] = INCBIN_U32("assets/graphics.bin", 0x14E2D0, 0x28);
const u8 gMonIcon_Marshtomp[] = INCBIN_U8("assets/graphics.bin", 0x14E2F8, 0x400);
const u8 gMonFootprint_Marshtomp[] = INCBIN_U8("assets/graphics.bin", 0x14E6F8, 0x20);

const u32 gMonFrontPic_Swampert[] = INCBIN_U32("assets/graphics.bin", 0x14E718, 0x57C);
const u32 gMonPalette_Swampert[] = INCBIN_U32("assets/graphics.bin", 0x14EC94, 0x28);
const u32 gMonBackPic_Swampert[] = INCBIN_U32("assets/graphics.bin", 0x14ECBC, 0x3B4);
const u32 gMonShinyPalette_Swampert[] = INCBIN_U32("assets/graphics.bin", 0x14F070, 0x28);
const u8 gMonIcon_Swampert[] = INCBIN_U8("assets/graphics.bin", 0x14F098, 0x400);
const u8 gMonFootprint_Swampert[] = INCBIN_U8("assets/graphics.bin", 0x14F498, 0x20);

const u32 gMonFrontPic_Poochyena[] = INCBIN_U32("assets/graphics.bin", 0x14F4B8, 0x2C8);
const u32 gMonPalette_Poochyena[] = INCBIN_U32("assets/graphics.bin", 0x14F780, 0x28);
const u32 gMonBackPic_Poochyena[] = INCBIN_U32("assets/graphics.bin", 0x14F7A8, 0x32C);
const u32 gMonShinyPalette_Poochyena[] = INCBIN_U32("assets/graphics.bin", 0x14FAD4, 0x28);
const u8 gMonIcon_Poochyena[] = INCBIN_U8("assets/graphics.bin", 0x14FAFC, 0x400);
const u8 gMonFootprint_Poochyena[] = INCBIN_U8("assets/graphics.bin", 0x14FEFC, 0x20);

const u32 gMonFrontPic_Mightyena[] = INCBIN_U32("assets/graphics.bin", 0x14FF1C, 0x438);
const u32 gMonPalette_Mightyena[] = INCBIN_U32("assets/graphics.bin", 0x150354, 0x28);
const u32 gMonBackPic_Mightyena[] = INCBIN_U32("assets/graphics.bin", 0x15037C, 0x378);
const u32 gMonShinyPalette_Mightyena[] = INCBIN_U32("assets/graphics.bin", 0x1506F4, 0x28);
const u8 gMonIcon_Mightyena[] = INCBIN_U8("assets/graphics.bin", 0x15071C, 0x400);
const u8 gMonFootprint_Mightyena[] = INCBIN_U8("assets/graphics.bin", 0x150B1C, 0x20);

const u32 gMonFrontPic_Zigzagoon[] = INCBIN_U32("assets/graphics.bin", 0x150B3C, 0x3D0);
const u32 gMonPalette_Zigzagoon[] = INCBIN_U32("assets/graphics.bin", 0x150F0C, 0x28);
const u32 gMonBackPic_Zigzagoon[] = INCBIN_U32("assets/graphics.bin", 0x150F34, 0x340);
const u32 gMonShinyPalette_Zigzagoon[] = INCBIN_U32("assets/graphics.bin", 0x151274, 0x28);
const u8 gMonIcon_Zigzagoon[] = INCBIN_U8("assets/graphics.bin", 0x15129C, 0x400);
const u8 gMonFootprint_Zigzagoon[] = INCBIN_U8("assets/graphics.bin", 0x15169C, 0x20);

const u32 gMonFrontPic_Linoone[] = INCBIN_U32("assets/graphics.bin", 0x1516BC, 0x370);
const u32 gMonPalette_Linoone[] = INCBIN_U32("assets/graphics.bin", 0x151A2C, 0x28);
const u32 gMonBackPic_Linoone[] = INCBIN_U32("assets/graphics.bin", 0x151A54, 0x2D4);
const u32 gMonShinyPalette_Linoone[] = INCBIN_U32("assets/graphics.bin", 0x151D28, 0x28);
const u8 gMonIcon_Linoone[] = INCBIN_U8("assets/graphics.bin", 0x151D50, 0x400);
const u8 gMonFootprint_Linoone[] = INCBIN_U8("assets/graphics.bin", 0x152150, 0x20);

const u32 gMonFrontPic_Wurmple[] = INCBIN_U32("assets/graphics.bin", 0x152170, 0x288);
const u32 gMonPalette_Wurmple[] = INCBIN_U32("assets/graphics.bin", 0x1523F8, 0x28);
const u32 gMonBackPic_Wurmple[] = INCBIN_U32("assets/graphics.bin", 0x152420, 0x24C);
const u32 gMonShinyPalette_Wurmple[] = INCBIN_U32("assets/graphics.bin", 0x15266C, 0x28);
const u8 gMonIcon_Wurmple[] = INCBIN_U8("assets/graphics.bin", 0x152694, 0x400);
const u8 gMonFootprint_Wurmple[] = INCBIN_U8("assets/graphics.bin", 0x152A94, 0x20);

const u32 gMonFrontPic_Silcoon[] = INCBIN_U32("assets/graphics.bin", 0x152AB4, 0x280);
const u32 gMonPalette_Silcoon[] = INCBIN_U32("assets/graphics.bin", 0x152D34, 0x28);
const u32 gMonBackPic_Silcoon[] = INCBIN_U32("assets/graphics.bin", 0x152D5C, 0x21C);
const u32 gMonShinyPalette_Silcoon[] = INCBIN_U32("assets/graphics.bin", 0x152F78, 0x28);
const u8 gMonIcon_Silcoon[] = INCBIN_U8("assets/graphics.bin", 0x152FA0, 0x400);
const u8 gMonFootprint_Silcoon[] = INCBIN_U8("assets/graphics.bin", 0x1533A0, 0x20);

const u32 gMonFrontPic_Beautifly[] = INCBIN_U32("assets/graphics.bin", 0x1533C0, 0x358);
const u32 gMonPalette_Beautifly[] = INCBIN_U32("assets/graphics.bin", 0x153718, 0x28);
const u32 gMonBackPic_Beautifly[] = INCBIN_U32("assets/graphics.bin", 0x153740, 0x3B0);
const u32 gMonShinyPalette_Beautifly[] = INCBIN_U32("assets/graphics.bin", 0x153AF0, 0x28);
const u8 gMonIcon_Beautifly[] = INCBIN_U8("assets/graphics.bin", 0x153B18, 0x400);
const u8 gMonFootprint_Beautifly[] = INCBIN_U8("assets/graphics.bin", 0x153F18, 0x20);

const u32 gMonFrontPic_Cascoon[] = INCBIN_U32("assets/graphics.bin", 0x153F38, 0x26C);
const u32 gMonPalette_Cascoon[] = INCBIN_U32("assets/graphics.bin", 0x1541A4, 0x28);
const u32 gMonBackPic_Cascoon[] = INCBIN_U32("assets/graphics.bin", 0x1541CC, 0x210);
const u32 gMonShinyPalette_Cascoon[] = INCBIN_U32("assets/graphics.bin", 0x1543DC, 0x28);
const u8 gMonIcon_Cascoon[] = INCBIN_U8("assets/graphics.bin", 0x154404, 0x400);
const u8 gMonFootprint_Cascoon[] = INCBIN_U8("assets/graphics.bin", 0x154804, 0x20);

const u32 gMonFrontPic_Dustox[] = INCBIN_U32("assets/graphics.bin", 0x154824, 0x368);
const u32 gMonPalette_Dustox[] = INCBIN_U32("assets/graphics.bin", 0x154B8C, 0x28);
const u32 gMonBackPic_Dustox[] = INCBIN_U32("assets/graphics.bin", 0x154BB4, 0x258);
const u32 gMonShinyPalette_Dustox[] = INCBIN_U32("assets/graphics.bin", 0x154E0C, 0x28);
const u8 gMonIcon_Dustox[] = INCBIN_U8("assets/graphics.bin", 0x154E34, 0x400);
const u8 gMonFootprint_Dustox[] = INCBIN_U8("assets/graphics.bin", 0x155234, 0x20);

const u32 gMonFrontPic_Lotad[] = INCBIN_U32("assets/graphics.bin", 0x155254, 0x260);
const u32 gMonPalette_Lotad[] = INCBIN_U32("assets/graphics.bin", 0x1554B4, 0x28);
const u32 gMonBackPic_Lotad[] = INCBIN_U32("assets/graphics.bin", 0x1554DC, 0x2E8);
const u32 gMonShinyPalette_Lotad[] = INCBIN_U32("assets/graphics.bin", 0x1557C4, 0x28);
const u8 gMonIcon_Lotad[] = INCBIN_U8("assets/graphics.bin", 0x1557EC, 0x400);
const u8 gMonFootprint_Lotad[] = INCBIN_U8("assets/graphics.bin", 0x155BEC, 0x20);

const u32 gMonFrontPic_Lombre[] = INCBIN_U32("assets/graphics.bin", 0x155C0C, 0x318);
const u32 gMonPalette_Lombre[] = INCBIN_U32("assets/graphics.bin", 0x155F24, 0x28);
const u32 gMonBackPic_Lombre[] = INCBIN_U32("assets/graphics.bin", 0x155F4C, 0x2FC);
const u32 gMonShinyPalette_Lombre[] = INCBIN_U32("assets/graphics.bin", 0x156248, 0x28);
const u8 gMonIcon_Lombre[] = INCBIN_U8("assets/graphics.bin", 0x156270, 0x400);
const u8 gMonFootprint_Lombre[] = INCBIN_U8("assets/graphics.bin", 0x156670, 0x20);

const u32 gMonFrontPic_Ludicolo[] = INCBIN_U32("assets/graphics.bin", 0x156690, 0x4E4);
const u32 gMonPalette_Ludicolo[] = INCBIN_U32("assets/graphics.bin", 0x156B74, 0x28);
const u32 gMonBackPic_Ludicolo[] = INCBIN_U32("assets/graphics.bin", 0x156B9C, 0x2FC);
const u32 gMonShinyPalette_Ludicolo[] = INCBIN_U32("assets/graphics.bin", 0x156E98, 0x28);
const u8 gMonIcon_Ludicolo[] = INCBIN_U8("assets/graphics.bin", 0x156EC0, 0x400);
const u8 gMonFootprint_Ludicolo[] = INCBIN_U8("assets/graphics.bin", 0x1572C0, 0x20);

const u32 gMonFrontPic_Seedot[] = INCBIN_U32("assets/graphics.bin", 0x1572E0, 0x294);
const u32 gMonPalette_Seedot[] = INCBIN_U32("assets/graphics.bin", 0x157574, 0x28);
const u32 gMonBackPic_Seedot[] = INCBIN_U32("assets/graphics.bin", 0x15759C, 0x2E0);
const u32 gMonShinyPalette_Seedot[] = INCBIN_U32("assets/graphics.bin", 0x15787C, 0x28);
const u8 gMonIcon_Seedot[] = INCBIN_U8("assets/graphics.bin", 0x1578A4, 0x400);
const u8 gMonFootprint_Seedot[] = INCBIN_U8("assets/graphics.bin", 0x157CA4, 0x20);

const u32 gMonFrontPic_Nuzleaf[] = INCBIN_U32("assets/graphics.bin", 0x157CC4, 0x2EC);
const u32 gMonPalette_Nuzleaf[] = INCBIN_U32("assets/graphics.bin", 0x157FB0, 0x28);
const u32 gMonBackPic_Nuzleaf[] = INCBIN_U32("assets/graphics.bin", 0x157FD8, 0x2C8);
const u32 gMonShinyPalette_Nuzleaf[] = INCBIN_U32("assets/graphics.bin", 0x1582A0, 0x28);
const u8 gMonIcon_Nuzleaf[] = INCBIN_U8("assets/graphics.bin", 0x1582C8, 0x400);
const u8 gMonFootprint_Nuzleaf[] = INCBIN_U8("assets/graphics.bin", 0x1586C8, 0x20);

const u32 gMonFrontPic_Shiftry[] = INCBIN_U32("assets/graphics.bin", 0x1586E8, 0x4BC);
const u32 gMonPalette_Shiftry[] = INCBIN_U32("assets/graphics.bin", 0x158BA4, 0x28);
const u32 gMonBackPic_Shiftry[] = INCBIN_U32("assets/graphics.bin", 0x158BCC, 0x2C4);
const u32 gMonShinyPalette_Shiftry[] = INCBIN_U32("assets/graphics.bin", 0x158E90, 0x28);
const u8 gMonIcon_Shiftry[] = INCBIN_U8("assets/graphics.bin", 0x158EB8, 0x400);
const u8 gMonFootprint_Shiftry[] = INCBIN_U8("assets/graphics.bin", 0x1592B8, 0x20);

const u32 gMonFrontPic_Nincada[] = INCBIN_U32("assets/graphics.bin", 0x1592D8, 0x2A0);
const u32 gMonPalette_Nincada[] = INCBIN_U32("assets/graphics.bin", 0x159578, 0x28);
const u32 gMonBackPic_Nincada[] = INCBIN_U32("assets/graphics.bin", 0x1595A0, 0x2B8);
const u32 gMonShinyPalette_Nincada[] = INCBIN_U32("assets/graphics.bin", 0x159858, 0x28);
const u8 gMonIcon_Nincada[] = INCBIN_U8("assets/graphics.bin", 0x159880, 0x400);
const u8 gMonFootprint_Nincada[] = INCBIN_U8("assets/graphics.bin", 0x159C80, 0x20);

const u32 gMonFrontPic_Ninjask[] = INCBIN_U32("assets/graphics.bin", 0x159CA0, 0x370);
const u32 gMonPalette_Ninjask[] = INCBIN_U32("assets/graphics.bin", 0x15A010, 0x28);
const u32 gMonBackPic_Ninjask[] = INCBIN_U32("assets/graphics.bin", 0x15A038, 0x3CC);
const u32 gMonShinyPalette_Ninjask[] = INCBIN_U32("assets/graphics.bin", 0x15A404, 0x28);
const u8 gMonIcon_Ninjask[] = INCBIN_U8("assets/graphics.bin", 0x15A42C, 0x400);
const u8 gMonFootprint_Ninjask[] = INCBIN_U8("assets/graphics.bin", 0x15A82C, 0x20);

const u32 gMonFrontPic_Shedinja[] = INCBIN_U32("assets/graphics.bin", 0x15A84C, 0x320);
const u32 gMonPalette_Shedinja[] = INCBIN_U32("assets/graphics.bin", 0x15AB6C, 0x28);
const u32 gMonBackPic_Shedinja[] = INCBIN_U32("assets/graphics.bin", 0x15AB94, 0x3A0);
const u32 gMonShinyPalette_Shedinja[] = INCBIN_U32("assets/graphics.bin", 0x15AF34, 0x28);
const u8 gMonIcon_Shedinja[] = INCBIN_U8("assets/graphics.bin", 0x15AF5C, 0x400);
const u8 gMonFootprint_Shedinja[] = INCBIN_U8("assets/graphics.bin", 0x15B35C, 0x20);

const u32 gMonFrontPic_Taillow[] = INCBIN_U32("assets/graphics.bin", 0x15B37C, 0x258);
const u32 gMonPalette_Taillow[] = INCBIN_U32("assets/graphics.bin", 0x15B5D4, 0x28);
const u32 gMonBackPic_Taillow[] = INCBIN_U32("assets/graphics.bin", 0x15B5FC, 0x220);
const u32 gMonShinyPalette_Taillow[] = INCBIN_U32("assets/graphics.bin", 0x15B81C, 0x28);
const u8 gMonIcon_Taillow[] = INCBIN_U8("assets/graphics.bin", 0x15B844, 0x400);
const u8 gMonFootprint_Taillow[] = INCBIN_U8("assets/graphics.bin", 0x15BC44, 0x20);

const u32 gMonFrontPic_Swellow[] = INCBIN_U32("assets/graphics.bin", 0x15BC64, 0x3C4);
const u32 gMonPalette_Swellow[] = INCBIN_U32("assets/graphics.bin", 0x15C028, 0x28);
const u32 gMonBackPic_Swellow[] = INCBIN_U32("assets/graphics.bin", 0x15C050, 0x338);
const u32 gMonShinyPalette_Swellow[] = INCBIN_U32("assets/graphics.bin", 0x15C388, 0x28);
const u8 gMonIcon_Swellow[] = INCBIN_U8("assets/graphics.bin", 0x15C3B0, 0x400);
const u8 gMonFootprint_Swellow[] = INCBIN_U8("assets/graphics.bin", 0x15C7B0, 0x20);

const u32 gMonFrontPic_Shroomish[] = INCBIN_U32("assets/graphics.bin", 0x15C7D0, 0x268);
const u32 gMonPalette_Shroomish[] = INCBIN_U32("assets/graphics.bin", 0x15CA38, 0x28);
const u32 gMonBackPic_Shroomish[] = INCBIN_U32("assets/graphics.bin", 0x15CA60, 0x2E0);
const u32 gMonShinyPalette_Shroomish[] = INCBIN_U32("assets/graphics.bin", 0x15CD40, 0x28);
const u8 gMonIcon_Shroomish[] = INCBIN_U8("assets/graphics.bin", 0x15CD68, 0x400);
const u8 gMonFootprint_Shroomish[] = INCBIN_U8("assets/graphics.bin", 0x15D168, 0x20);

const u32 gMonFrontPic_Breloom[] = INCBIN_U32("assets/graphics.bin", 0x15D188, 0x3E8);
const u32 gMonPalette_Breloom[] = INCBIN_U32("assets/graphics.bin", 0x15D570, 0x28);
const u32 gMonBackPic_Breloom[] = INCBIN_U32("assets/graphics.bin", 0x15D598, 0x3E0);
const u32 gMonShinyPalette_Breloom[] = INCBIN_U32("assets/graphics.bin", 0x15D978, 0x28);
const u8 gMonIcon_Breloom[] = INCBIN_U8("assets/graphics.bin", 0x15D9A0, 0x400);
const u8 gMonFootprint_Breloom[] = INCBIN_U8("assets/graphics.bin", 0x15DDA0, 0x20);

const u32 gMonFrontPic_Spinda[] = INCBIN_U32("assets/graphics.bin", 0x15DDC0, 0x300);
const u32 gMonPalette_Spinda[] = INCBIN_U32("assets/graphics.bin", 0x15E0C0, 0x28);
const u32 gMonBackPic_Spinda[] = INCBIN_U32("assets/graphics.bin", 0x15E0E8, 0x33C);
const u32 gMonShinyPalette_Spinda[] = INCBIN_U32("assets/graphics.bin", 0x15E424, 0x28);
const u8 gMonIcon_Spinda[] = INCBIN_U8("assets/graphics.bin", 0x15E44C, 0x400);
const u8 gMonFootprint_Spinda[] = INCBIN_U8("assets/graphics.bin", 0x15E84C, 0x20);

const u32 gMonFrontPic_Wingull[] = INCBIN_U32("assets/graphics.bin", 0x15E86C, 0x23C);
const u32 gMonPalette_Wingull[] = INCBIN_U32("assets/graphics.bin", 0x15EAA8, 0x28);
const u32 gMonBackPic_Wingull[] = INCBIN_U32("assets/graphics.bin", 0x15EAD0, 0x350);
const u32 gMonShinyPalette_Wingull[] = INCBIN_U32("assets/graphics.bin", 0x15EE20, 0x28);
const u8 gMonIcon_Wingull[] = INCBIN_U8("assets/graphics.bin", 0x15EE48, 0x400);
const u8 gMonFootprint_Wingull[] = INCBIN_U8("assets/graphics.bin", 0x15F248, 0x20);

const u32 gMonFrontPic_Pelipper[] = INCBIN_U32("assets/graphics.bin", 0x15F268, 0x398);
const u32 gMonPalette_Pelipper[] = INCBIN_U32("assets/graphics.bin", 0x15F600, 0x28);
const u32 gMonBackPic_Pelipper[] = INCBIN_U32("assets/graphics.bin", 0x15F628, 0x380);
const u32 gMonShinyPalette_Pelipper[] = INCBIN_U32("assets/graphics.bin", 0x15F9A8, 0x28);
const u8 gMonIcon_Pelipper[] = INCBIN_U8("assets/graphics.bin", 0x15F9D0, 0x400);
const u8 gMonFootprint_Pelipper[] = INCBIN_U8("assets/graphics.bin", 0x15FDD0, 0x20);

const u32 gMonFrontPic_Surskit[] = INCBIN_U32("assets/graphics.bin", 0x15FDF0, 0x20C);
const u32 gMonPalette_Surskit[] = INCBIN_U32("assets/graphics.bin", 0x15FFFC, 0x28);
const u32 gMonBackPic_Surskit[] = INCBIN_U32("assets/graphics.bin", 0x160024, 0x238);
const u32 gMonShinyPalette_Surskit[] = INCBIN_U32("assets/graphics.bin", 0x16025C, 0x28);
const u8 gMonIcon_Surskit[] = INCBIN_U8("assets/graphics.bin", 0x160284, 0x400);
const u8 gMonFootprint_Surskit[] = INCBIN_U8("assets/graphics.bin", 0x160684, 0x20);

const u32 gMonFrontPic_Masquerain[] = INCBIN_U32("assets/graphics.bin", 0x1606A4, 0x39C);
const u32 gMonPalette_Masquerain[] = INCBIN_U32("assets/graphics.bin", 0x160A40, 0x28);
const u32 gMonBackPic_Masquerain[] = INCBIN_U32("assets/graphics.bin", 0x160A68, 0x358);
const u32 gMonShinyPalette_Masquerain[] = INCBIN_U32("assets/graphics.bin", 0x160DC0, 0x28);
const u8 gMonIcon_Masquerain[] = INCBIN_U8("assets/graphics.bin", 0x160DE8, 0x400);
const u8 gMonFootprint_Masquerain[] = INCBIN_U8("assets/graphics.bin", 0x1611E8, 0x20);

const u32 gMonFrontPic_Wailmer[] = INCBIN_U32("assets/graphics.bin", 0x161208, 0x2E0);
const u32 gMonPalette_Wailmer[] = INCBIN_U32("assets/graphics.bin", 0x1614E8, 0x28);
const u32 gMonBackPic_Wailmer[] = INCBIN_U32("assets/graphics.bin", 0x161510, 0x1E4);
const u32 gMonShinyPalette_Wailmer[] = INCBIN_U32("assets/graphics.bin", 0x1616F4, 0x28);
const u8 gMonIcon_Wailmer[] = INCBIN_U8("assets/graphics.bin", 0x16171C, 0x400);
const u8 gMonFootprint_Wailmer[] = INCBIN_U8("assets/graphics.bin", 0x161B1C, 0x20);

const u32 gMonFrontPic_Wailord[] = INCBIN_U32("assets/graphics.bin", 0x161B3C, 0x3C4);
const u32 gMonPalette_Wailord[] = INCBIN_U32("assets/graphics.bin", 0x161F00, 0x28);
const u32 gMonBackPic_Wailord[] = INCBIN_U32("assets/graphics.bin", 0x161F28, 0x218);
const u32 gMonShinyPalette_Wailord[] = INCBIN_U32("assets/graphics.bin", 0x162140, 0x28);
const u8 gMonIcon_Wailord[] = INCBIN_U8("assets/graphics.bin", 0x162168, 0x400);
const u8 gMonFootprint_Wailord[] = INCBIN_U8("assets/graphics.bin", 0x162568, 0x20);

const u32 gMonFrontPic_Skitty[] = INCBIN_U32("assets/graphics.bin", 0x162588, 0x300);
const u32 gMonPalette_Skitty[] = INCBIN_U32("assets/graphics.bin", 0x162888, 0x28);
const u32 gMonBackPic_Skitty[] = INCBIN_U32("assets/graphics.bin", 0x1628B0, 0x348);
const u32 gMonShinyPalette_Skitty[] = INCBIN_U32("assets/graphics.bin", 0x162BF8, 0x28);
const u8 gMonIcon_Skitty[] = INCBIN_U8("assets/graphics.bin", 0x162C20, 0x400);
const u8 gMonFootprint_Skitty[] = INCBIN_U8("assets/graphics.bin", 0x163020, 0x20);

const u32 gMonFrontPic_Delcatty[] = INCBIN_U32("assets/graphics.bin", 0x163040, 0x38C);
const u32 gMonPalette_Delcatty[] = INCBIN_U32("assets/graphics.bin", 0x1633CC, 0x28);
const u32 gMonBackPic_Delcatty[] = INCBIN_U32("assets/graphics.bin", 0x1633F4, 0x39C);
const u32 gMonShinyPalette_Delcatty[] = INCBIN_U32("assets/graphics.bin", 0x163790, 0x28);
const u8 gMonIcon_Delcatty[] = INCBIN_U8("assets/graphics.bin", 0x1637B8, 0x400);
const u8 gMonFootprint_Delcatty[] = INCBIN_U8("assets/graphics.bin", 0x163BB8, 0x20);

const u32 gMonFrontPic_Kecleon[] = INCBIN_U32("assets/graphics.bin", 0x163BD8, 0x380);
const u32 gMonPalette_Kecleon[] = INCBIN_U32("assets/graphics.bin", 0x163F58, 0x28);
const u32 gMonBackPic_Kecleon[] = INCBIN_U32("assets/graphics.bin", 0x163F80, 0x3D8);
const u32 gMonShinyPalette_Kecleon[] = INCBIN_U32("assets/graphics.bin", 0x164358, 0x28);
const u8 gMonIcon_Kecleon[] = INCBIN_U8("assets/graphics.bin", 0x164380, 0x400);
const u8 gMonFootprint_Kecleon[] = INCBIN_U8("assets/graphics.bin", 0x164780, 0x20);

const u32 gMonFrontPic_Baltoy[] = INCBIN_U32("assets/graphics.bin", 0x1647A0, 0x224);
const u32 gMonPalette_Baltoy[] = INCBIN_U32("assets/graphics.bin", 0x1649C4, 0x20);
const u32 gMonBackPic_Baltoy[] = INCBIN_U32("assets/graphics.bin", 0x1649E4, 0x2A8);
const u32 gMonShinyPalette_Baltoy[] = INCBIN_U32("assets/graphics.bin", 0x164C8C, 0x20);
const u8 gMonIcon_Baltoy[] = INCBIN_U8("assets/graphics.bin", 0x164CAC, 0x400);
const u8 gMonFootprint_Baltoy[] = INCBIN_U8("assets/graphics.bin", 0x1650AC, 0x20);

const u32 gMonFrontPic_Claydol[] = INCBIN_U32("assets/graphics.bin", 0x1650CC, 0x3B8);
const u32 gMonPalette_Claydol[] = INCBIN_U32("assets/graphics.bin", 0x165484, 0x28);
const u32 gMonBackPic_Claydol[] = INCBIN_U32("assets/graphics.bin", 0x1654AC, 0x3D4);
const u32 gMonShinyPalette_Claydol[] = INCBIN_U32("assets/graphics.bin", 0x165880, 0x28);
const u8 gMonIcon_Claydol[] = INCBIN_U8("assets/graphics.bin", 0x1658A8, 0x400);
const u8 gMonFootprint_Claydol[] = INCBIN_U8("assets/graphics.bin", 0x165CA8, 0x20);

const u32 gMonFrontPic_Nosepass[] = INCBIN_U32("assets/graphics.bin", 0x165CC8, 0x2CC);
const u32 gMonPalette_Nosepass[] = INCBIN_U32("assets/graphics.bin", 0x165F94, 0x28);
const u32 gMonBackPic_Nosepass[] = INCBIN_U32("assets/graphics.bin", 0x165FBC, 0x2A0);
const u32 gMonShinyPalette_Nosepass[] = INCBIN_U32("assets/graphics.bin", 0x16625C, 0x28);
const u8 gMonIcon_Nosepass[] = INCBIN_U8("assets/graphics.bin", 0x166284, 0x400);
const u8 gMonFootprint_Nosepass[] = INCBIN_U8("assets/graphics.bin", 0x166684, 0x20);

const u32 gMonFrontPic_Torkoal[] = INCBIN_U32("assets/graphics.bin", 0x1666A4, 0x4AC);
const u32 gMonPalette_Torkoal[] = INCBIN_U32("assets/graphics.bin", 0x166B50, 0x28);
const u32 gMonBackPic_Torkoal[] = INCBIN_U32("assets/graphics.bin", 0x166B78, 0x2C8);
const u32 gMonShinyPalette_Torkoal[] = INCBIN_U32("assets/graphics.bin", 0x166E40, 0x28);
const u8 gMonIcon_Torkoal[] = INCBIN_U8("assets/graphics.bin", 0x166E68, 0x400);
const u8 gMonFootprint_Torkoal[] = INCBIN_U8("assets/graphics.bin", 0x167268, 0x20);

const u32 gMonFrontPic_Sableye[] = INCBIN_U32("assets/graphics.bin", 0x167288, 0x2D4);
const u32 gMonPalette_Sableye[] = INCBIN_U32("assets/graphics.bin", 0x16755C, 0x28);
const u32 gMonBackPic_Sableye[] = INCBIN_U32("assets/graphics.bin", 0x167584, 0x328);
const u32 gMonShinyPalette_Sableye[] = INCBIN_U32("assets/graphics.bin", 0x1678AC, 0x28);
const u8 gMonIcon_Sableye[] = INCBIN_U8("assets/graphics.bin", 0x1678D4, 0x400);
const u8 gMonFootprint_Sableye[] = INCBIN_U8("assets/graphics.bin", 0x167CD4, 0x20);

const u32 gMonFrontPic_Barboach[] = INCBIN_U32("assets/graphics.bin", 0x167CF4, 0x290);
const u32 gMonPalette_Barboach[] = INCBIN_U32("assets/graphics.bin", 0x167F84, 0x28);
const u32 gMonBackPic_Barboach[] = INCBIN_U32("assets/graphics.bin", 0x167FAC, 0x290);
const u32 gMonShinyPalette_Barboach[] = INCBIN_U32("assets/graphics.bin", 0x16823C, 0x28);
const u8 gMonIcon_Barboach[] = INCBIN_U8("assets/graphics.bin", 0x168264, 0x400);
const u8 gMonFootprint_Barboach[] = INCBIN_U8("assets/graphics.bin", 0x168664, 0x20);

const u32 gMonFrontPic_Whiscash[] = INCBIN_U32("assets/graphics.bin", 0x168684, 0x378);
const u32 gMonPalette_Whiscash[] = INCBIN_U32("assets/graphics.bin", 0x1689FC, 0x28);
const u32 gMonBackPic_Whiscash[] = INCBIN_U32("assets/graphics.bin", 0x168A24, 0x34C);
const u32 gMonShinyPalette_Whiscash[] = INCBIN_U32("assets/graphics.bin", 0x168D70, 0x28);
const u8 gMonIcon_Whiscash[] = INCBIN_U8("assets/graphics.bin", 0x168D98, 0x400);
const u8 gMonFootprint_Whiscash[] = INCBIN_U8("assets/graphics.bin", 0x169198, 0x20);

const u32 gMonFrontPic_Luvdisc[] = INCBIN_U32("assets/graphics.bin", 0x1691B8, 0x1C0);
const u32 gMonPalette_Luvdisc[] = INCBIN_U32("assets/graphics.bin", 0x169378, 0x24);
const u32 gMonBackPic_Luvdisc[] = INCBIN_U32("assets/graphics.bin", 0x16939C, 0x1D4);
const u32 gMonShinyPalette_Luvdisc[] = INCBIN_U32("assets/graphics.bin", 0x169570, 0x24);
const u8 gMonIcon_Luvdisc[] = INCBIN_U8("assets/graphics.bin", 0x169594, 0x400);
const u8 gMonFootprint_Luvdisc[] = INCBIN_U8("assets/graphics.bin", 0x169994, 0x20);

const u32 gMonFrontPic_Corphish[] = INCBIN_U32("assets/graphics.bin", 0x1699B4, 0x35C);
const u32 gMonPalette_Corphish[] = INCBIN_U32("assets/graphics.bin", 0x169D10, 0x28);
const u32 gMonBackPic_Corphish[] = INCBIN_U32("assets/graphics.bin", 0x169D38, 0x31C);
const u32 gMonShinyPalette_Corphish[] = INCBIN_U32("assets/graphics.bin", 0x16A054, 0x28);
const u8 gMonIcon_Corphish[] = INCBIN_U8("assets/graphics.bin", 0x16A07C, 0x400);
const u8 gMonFootprint_Corphish[] = INCBIN_U8("assets/graphics.bin", 0x16A47C, 0x20);

const u32 gMonFrontPic_Crawdaunt[] = INCBIN_U32("assets/graphics.bin", 0x16A49C, 0x490);
const u32 gMonPalette_Crawdaunt[] = INCBIN_U32("assets/graphics.bin", 0x16A92C, 0x28);
const u32 gMonBackPic_Crawdaunt[] = INCBIN_U32("assets/graphics.bin", 0x16A954, 0x3E4);
const u32 gMonShinyPalette_Crawdaunt[] = INCBIN_U32("assets/graphics.bin", 0x16AD38, 0x28);
const u8 gMonIcon_Crawdaunt[] = INCBIN_U8("assets/graphics.bin", 0x16AD60, 0x400);
const u8 gMonFootprint_Crawdaunt[] = INCBIN_U8("assets/graphics.bin", 0x16B160, 0x20);

const u32 gMonFrontPic_Feebas[] = INCBIN_U32("assets/graphics.bin", 0x16B180, 0x28C);
const u32 gMonPalette_Feebas[] = INCBIN_U32("assets/graphics.bin", 0x16B40C, 0x28);
const u32 gMonBackPic_Feebas[] = INCBIN_U32("assets/graphics.bin", 0x16B434, 0x338);
const u32 gMonShinyPalette_Feebas[] = INCBIN_U32("assets/graphics.bin", 0x16B76C, 0x28);
const u8 gMonIcon_Feebas[] = INCBIN_U8("assets/graphics.bin", 0x16B794, 0x400);
const u8 gMonFootprint_Feebas[] = INCBIN_U8("assets/graphics.bin", 0x16BB94, 0x20);

const u32 gMonFrontPic_Milotic[] = INCBIN_U32("assets/graphics.bin", 0x16BBB4, 0x490);
const u32 gMonPalette_Milotic[] = INCBIN_U32("assets/graphics.bin", 0x16C044, 0x28);
const u32 gMonBackPic_Milotic[] = INCBIN_U32("assets/graphics.bin", 0x16C06C, 0x2F4);
const u32 gMonShinyPalette_Milotic[] = INCBIN_U32("assets/graphics.bin", 0x16C360, 0x28);
const u8 gMonIcon_Milotic[] = INCBIN_U8("assets/graphics.bin", 0x16C388, 0x400);
const u8 gMonFootprint_Milotic[] = INCBIN_U8("assets/graphics.bin", 0x16C788, 0x20);

const u32 gMonFrontPic_Carvanha[] = INCBIN_U32("assets/graphics.bin", 0x16C7A8, 0x32C);
const u32 gMonPalette_Carvanha[] = INCBIN_U32("assets/graphics.bin", 0x16CAD4, 0x28);
const u32 gMonBackPic_Carvanha[] = INCBIN_U32("assets/graphics.bin", 0x16CAFC, 0x310);
const u32 gMonShinyPalette_Carvanha[] = INCBIN_U32("assets/graphics.bin", 0x16CE0C, 0x28);
const u8 gMonIcon_Carvanha[] = INCBIN_U8("assets/graphics.bin", 0x16CE34, 0x400);
const u8 gMonFootprint_Carvanha[] = INCBIN_U8("assets/graphics.bin", 0x16D234, 0x20);

const u32 gMonFrontPic_Sharpedo[] = INCBIN_U32("assets/graphics.bin", 0x16D254, 0x390);
const u32 gMonPalette_Sharpedo[] = INCBIN_U32("assets/graphics.bin", 0x16D5E4, 0x28);
const u32 gMonBackPic_Sharpedo[] = INCBIN_U32("assets/graphics.bin", 0x16D60C, 0x358);
const u32 gMonShinyPalette_Sharpedo[] = INCBIN_U32("assets/graphics.bin", 0x16D964, 0x28);
const u8 gMonIcon_Sharpedo[] = INCBIN_U8("assets/graphics.bin", 0x16D98C, 0x400);
const u8 gMonFootprint_Sharpedo[] = INCBIN_U8("assets/graphics.bin", 0x16DD8C, 0x20);

const u32 gMonFrontPic_Trapinch[] = INCBIN_U32("assets/graphics.bin", 0x16DDAC, 0x21C);
const u32 gMonPalette_Trapinch[] = INCBIN_U32("assets/graphics.bin", 0x16DFC8, 0x28);
const u32 gMonBackPic_Trapinch[] = INCBIN_U32("assets/graphics.bin", 0x16DFF0, 0x220);
const u32 gMonShinyPalette_Trapinch[] = INCBIN_U32("assets/graphics.bin", 0x16E210, 0x28);
const u8 gMonIcon_Trapinch[] = INCBIN_U8("assets/graphics.bin", 0x16E238, 0x400);
const u8 gMonFootprint_Trapinch[] = INCBIN_U8("assets/graphics.bin", 0x16E638, 0x20);

const u32 gMonFrontPic_Vibrava[] = INCBIN_U32("assets/graphics.bin", 0x16E658, 0x370);
const u32 gMonPalette_Vibrava[] = INCBIN_U32("assets/graphics.bin", 0x16E9C8, 0x28);
const u32 gMonBackPic_Vibrava[] = INCBIN_U32("assets/graphics.bin", 0x16E9F0, 0x278);
const u32 gMonShinyPalette_Vibrava[] = INCBIN_U32("assets/graphics.bin", 0x16EC68, 0x28);
const u8 gMonIcon_Vibrava[] = INCBIN_U8("assets/graphics.bin", 0x16EC90, 0x400);
const u8 gMonFootprint_Vibrava[] = INCBIN_U8("assets/graphics.bin", 0x16F090, 0x20);

const u32 gMonFrontPic_Flygon[] = INCBIN_U32("assets/graphics.bin", 0x16F0B0, 0x4F0);
const u32 gMonPalette_Flygon[] = INCBIN_U32("assets/graphics.bin", 0x16F5A0, 0x28);
const u32 gMonBackPic_Flygon[] = INCBIN_U32("assets/graphics.bin", 0x16F5C8, 0x43C);
const u32 gMonShinyPalette_Flygon[] = INCBIN_U32("assets/graphics.bin", 0x16FA04, 0x28);
const u8 gMonIcon_Flygon[] = INCBIN_U8("assets/graphics.bin", 0x16FA2C, 0x400);
const u8 gMonFootprint_Flygon[] = INCBIN_U8("assets/graphics.bin", 0x16FE2C, 0x20);

const u32 gMonFrontPic_Makuhita[] = INCBIN_U32("assets/graphics.bin", 0x16FE4C, 0x318);
const u32 gMonPalette_Makuhita[] = INCBIN_U32("assets/graphics.bin", 0x170164, 0x28);
const u32 gMonBackPic_Makuhita[] = INCBIN_U32("assets/graphics.bin", 0x17018C, 0x2F0);
const u32 gMonShinyPalette_Makuhita[] = INCBIN_U32("assets/graphics.bin", 0x17047C, 0x24);
const u8 gMonIcon_Makuhita[] = INCBIN_U8("assets/graphics.bin", 0x1704A0, 0x400);
const u8 gMonFootprint_Makuhita[] = INCBIN_U8("assets/graphics.bin", 0x1708A0, 0x20);

const u32 gMonFrontPic_Hariyama[] = INCBIN_U32("assets/graphics.bin", 0x1708C0, 0x4B0);
const u32 gMonPalette_Hariyama[] = INCBIN_U32("assets/graphics.bin", 0x170D70, 0x28);
const u32 gMonBackPic_Hariyama[] = INCBIN_U32("assets/graphics.bin", 0x170D98, 0x3E0);
const u32 gMonShinyPalette_Hariyama[] = INCBIN_U32("assets/graphics.bin", 0x171178, 0x28);
const u8 gMonIcon_Hariyama[] = INCBIN_U8("assets/graphics.bin", 0x1711A0, 0x400);
const u8 gMonFootprint_Hariyama[] = INCBIN_U8("assets/graphics.bin", 0x1715A0, 0x20);

const u32 gMonFrontPic_Electrike[] = INCBIN_U32("assets/graphics.bin", 0x1715C0, 0x290);
const u32 gMonPalette_Electrike[] = INCBIN_U32("assets/graphics.bin", 0x171850, 0x28);
const u32 gMonBackPic_Electrike[] = INCBIN_U32("assets/graphics.bin", 0x171878, 0x28C);
const u32 gMonShinyPalette_Electrike[] = INCBIN_U32("assets/graphics.bin", 0x171B04, 0x28);
const u8 gMonIcon_Electrike[] = INCBIN_U8("assets/graphics.bin", 0x171B2C, 0x400);
const u8 gMonFootprint_Electrike[] = INCBIN_U8("assets/graphics.bin", 0x171F2C, 0x20);

const u32 gMonFrontPic_Manectric[] = INCBIN_U32("assets/graphics.bin", 0x171F4C, 0x330);
const u32 gMonPalette_Manectric[] = INCBIN_U32("assets/graphics.bin", 0x17227C, 0x28);
const u32 gMonBackPic_Manectric[] = INCBIN_U32("assets/graphics.bin", 0x1722A4, 0x22C);
const u32 gMonShinyPalette_Manectric[] = INCBIN_U32("assets/graphics.bin", 0x1724D0, 0x28);
const u8 gMonIcon_Manectric[] = INCBIN_U8("assets/graphics.bin", 0x1724F8, 0x400);
const u8 gMonFootprint_Manectric[] = INCBIN_U8("assets/graphics.bin", 0x1728F8, 0x20);

const u32 gMonFrontPic_Numel[] = INCBIN_U32("assets/graphics.bin", 0x172918, 0x2D0);
const u32 gMonPalette_Numel[] = INCBIN_U32("assets/graphics.bin", 0x172BE8, 0x28);
const u32 gMonBackPic_Numel[] = INCBIN_U32("assets/graphics.bin", 0x172C10, 0x2BC);
const u32 gMonShinyPalette_Numel[] = INCBIN_U32("assets/graphics.bin", 0x172ECC, 0x28);
const u8 gMonIcon_Numel[] = INCBIN_U8("assets/graphics.bin", 0x172EF4, 0x400);
const u8 gMonFootprint_Numel[] = INCBIN_U8("assets/graphics.bin", 0x1732F4, 0x20);

const u32 gMonFrontPic_Camerupt[] = INCBIN_U32("assets/graphics.bin", 0x173314, 0x418);
const u32 gMonPalette_Camerupt[] = INCBIN_U32("assets/graphics.bin", 0x17372C, 0x28);
const u32 gMonBackPic_Camerupt[] = INCBIN_U32("assets/graphics.bin", 0x173754, 0x2C4);
const u32 gMonShinyPalette_Camerupt[] = INCBIN_U32("assets/graphics.bin", 0x173A18, 0x28);
const u8 gMonIcon_Camerupt[] = INCBIN_U8("assets/graphics.bin", 0x173A40, 0x400);
const u8 gMonFootprint_Camerupt[] = INCBIN_U8("assets/graphics.bin", 0x173E40, 0x20);

const u32 gMonFrontPic_Spheal[] = INCBIN_U32("assets/graphics.bin", 0x173E60, 0x274);
const u32 gMonPalette_Spheal[] = INCBIN_U32("assets/graphics.bin", 0x1740D4, 0x28);
const u32 gMonBackPic_Spheal[] = INCBIN_U32("assets/graphics.bin", 0x1740FC, 0x1FC);
const u32 gMonShinyPalette_Spheal[] = INCBIN_U32("assets/graphics.bin", 0x1742F8, 0x28);
const u8 gMonIcon_Spheal[] = INCBIN_U8("assets/graphics.bin", 0x174320, 0x400);
const u8 gMonFootprint_Spheal[] = INCBIN_U8("assets/graphics.bin", 0x174720, 0x20);

const u32 gMonFrontPic_Sealeo[] = INCBIN_U32("assets/graphics.bin", 0x174740, 0x380);
const u32 gMonPalette_Sealeo[] = INCBIN_U32("assets/graphics.bin", 0x174AC0, 0x28);
const u32 gMonBackPic_Sealeo[] = INCBIN_U32("assets/graphics.bin", 0x174AE8, 0x27C);
const u32 gMonShinyPalette_Sealeo[] = INCBIN_U32("assets/graphics.bin", 0x174D64, 0x28);
const u8 gMonIcon_Sealeo[] = INCBIN_U8("assets/graphics.bin", 0x174D8C, 0x400);
const u8 gMonFootprint_Sealeo[] = INCBIN_U8("assets/graphics.bin", 0x17518C, 0x20);

const u32 gMonFrontPic_Walrein[] = INCBIN_U32("assets/graphics.bin", 0x1751AC, 0x4A0);
const u32 gMonPalette_Walrein[] = INCBIN_U32("assets/graphics.bin", 0x17564C, 0x28);
const u32 gMonBackPic_Walrein[] = INCBIN_U32("assets/graphics.bin", 0x175674, 0x388);
const u32 gMonShinyPalette_Walrein[] = INCBIN_U32("assets/graphics.bin", 0x1759FC, 0x28);
const u8 gMonIcon_Walrein[] = INCBIN_U8("assets/graphics.bin", 0x175A24, 0x400);
const u8 gMonFootprint_Walrein[] = INCBIN_U8("assets/graphics.bin", 0x175E24, 0x20);

const u32 gMonFrontPic_Cacnea[] = INCBIN_U32("assets/graphics.bin", 0x175E44, 0x310);
const u32 gMonPalette_Cacnea[] = INCBIN_U32("assets/graphics.bin", 0x176154, 0x28);
const u32 gMonBackPic_Cacnea[] = INCBIN_U32("assets/graphics.bin", 0x17617C, 0x360);
const u32 gMonShinyPalette_Cacnea[] = INCBIN_U32("assets/graphics.bin", 0x1764DC, 0x28);
const u8 gMonIcon_Cacnea[] = INCBIN_U8("assets/graphics.bin", 0x176504, 0x400);
const u8 gMonFootprint_Cacnea[] = INCBIN_U8("assets/graphics.bin", 0x176904, 0x20);

const u32 gMonFrontPic_Cacturne[] = INCBIN_U32("assets/graphics.bin", 0x176924, 0x438);
const u32 gMonPalette_Cacturne[] = INCBIN_U32("assets/graphics.bin", 0x176D5C, 0x28);
const u32 gMonBackPic_Cacturne[] = INCBIN_U32("assets/graphics.bin", 0x176D84, 0x300);
const u32 gMonShinyPalette_Cacturne[] = INCBIN_U32("assets/graphics.bin", 0x177084, 0x28);
const u8 gMonIcon_Cacturne[] = INCBIN_U8("assets/graphics.bin", 0x1770AC, 0x400);
const u8 gMonFootprint_Cacturne[] = INCBIN_U8("assets/graphics.bin", 0x1774AC, 0x20);

const u32 gMonFrontPic_Snorunt[] = INCBIN_U32("assets/graphics.bin", 0x1774CC, 0x2C4);
const u32 gMonPalette_Snorunt[] = INCBIN_U32("assets/graphics.bin", 0x177790, 0x28);
const u32 gMonBackPic_Snorunt[] = INCBIN_U32("assets/graphics.bin", 0x1777B8, 0x2E4);
const u32 gMonShinyPalette_Snorunt[] = INCBIN_U32("assets/graphics.bin", 0x177A9C, 0x28);
const u8 gMonIcon_Snorunt[] = INCBIN_U8("assets/graphics.bin", 0x177AC4, 0x400);
const u8 gMonFootprint_Snorunt[] = INCBIN_U8("assets/graphics.bin", 0x177EC4, 0x20);

const u32 gMonFrontPic_Glalie[] = INCBIN_U32("assets/graphics.bin", 0x177EE4, 0x3C8);
const u32 gMonPalette_Glalie[] = INCBIN_U32("assets/graphics.bin", 0x1782AC, 0x28);
const u32 gMonBackPic_Glalie[] = INCBIN_U32("assets/graphics.bin", 0x1782D4, 0x3B0);
const u32 gMonShinyPalette_Glalie[] = INCBIN_U32("assets/graphics.bin", 0x178684, 0x28);
const u8 gMonIcon_Glalie[] = INCBIN_U8("assets/graphics.bin", 0x1786AC, 0x400);
const u8 gMonFootprint_Glalie[] = INCBIN_U8("assets/graphics.bin", 0x178AAC, 0x20);

const u32 gMonFrontPic_Lunatone[] = INCBIN_U32("assets/graphics.bin", 0x178ACC, 0x328);
const u32 gMonPalette_Lunatone[] = INCBIN_U32("assets/graphics.bin", 0x178DF4, 0x28);
const u32 gMonBackPic_Lunatone[] = INCBIN_U32("assets/graphics.bin", 0x178E1C, 0x358);
const u32 gMonShinyPalette_Lunatone[] = INCBIN_U32("assets/graphics.bin", 0x179174, 0x28);
const u8 gMonIcon_Lunatone[] = INCBIN_U8("assets/graphics.bin", 0x17919C, 0x400);
const u8 gMonFootprint_Lunatone[] = INCBIN_U8("assets/graphics.bin", 0x17959C, 0x20);

const u32 gMonFrontPic_Solrock[] = INCBIN_U32("assets/graphics.bin", 0x1795BC, 0x44C);
const u32 gMonPalette_Solrock[] = INCBIN_U32("assets/graphics.bin", 0x179A08, 0x28);
const u32 gMonBackPic_Solrock[] = INCBIN_U32("assets/graphics.bin", 0x179A30, 0x3EC);
const u32 gMonShinyPalette_Solrock[] = INCBIN_U32("assets/graphics.bin", 0x179E1C, 0x28);
const u8 gMonIcon_Solrock[] = INCBIN_U8("assets/graphics.bin", 0x179E44, 0x400);
const u8 gMonFootprint_Solrock[] = INCBIN_U8("assets/graphics.bin", 0x17A244, 0x20);

const u32 gMonFrontPic_Azurill[] = INCBIN_U32("assets/graphics.bin", 0x17A264, 0x2C8);
const u32 gMonPalette_Azurill[] = INCBIN_U32("assets/graphics.bin", 0x17A52C, 0x28);
const u32 gMonBackPic_Azurill[] = INCBIN_U32("assets/graphics.bin", 0x17A554, 0x318);
const u32 gMonShinyPalette_Azurill[] = INCBIN_U32("assets/graphics.bin", 0x17A86C, 0x28);
const u8 gMonIcon_Azurill[] = INCBIN_U8("assets/graphics.bin", 0x17A894, 0x400);
const u8 gMonFootprint_Azurill[] = INCBIN_U8("assets/graphics.bin", 0x17AC94, 0x20);

const u32 gMonFrontPic_Spoink[] = INCBIN_U32("assets/graphics.bin", 0x17ACB4, 0x26C);
const u32 gMonPalette_Spoink[] = INCBIN_U32("assets/graphics.bin", 0x17AF20, 0x28);
const u32 gMonBackPic_Spoink[] = INCBIN_U32("assets/graphics.bin", 0x17AF48, 0x240);
const u32 gMonShinyPalette_Spoink[] = INCBIN_U32("assets/graphics.bin", 0x17B188, 0x28);
const u8 gMonIcon_Spoink[] = INCBIN_U8("assets/graphics.bin", 0x17B1B0, 0x400);
const u8 gMonFootprint_Spoink[] = INCBIN_U8("assets/graphics.bin", 0x17B5B0, 0x20);

const u32 gMonFrontPic_Grumpig[] = INCBIN_U32("assets/graphics.bin", 0x17B5D0, 0x3BC);
const u32 gMonPalette_Grumpig[] = INCBIN_U32("assets/graphics.bin", 0x17B98C, 0x28);
const u32 gMonBackPic_Grumpig[] = INCBIN_U32("assets/graphics.bin", 0x17B9B4, 0x360);
const u32 gMonShinyPalette_Grumpig[] = INCBIN_U32("assets/graphics.bin", 0x17BD14, 0x28);
const u8 gMonIcon_Grumpig[] = INCBIN_U8("assets/graphics.bin", 0x17BD3C, 0x400);
const u8 gMonFootprint_Grumpig[] = INCBIN_U8("assets/graphics.bin", 0x17C13C, 0x20);

const u32 gMonFrontPic_Plusle[] = INCBIN_U32("assets/graphics.bin", 0x17C15C, 0x28C);
const u32 gMonPalette_Plusle[] = INCBIN_U32("assets/graphics.bin", 0x17C3E8, 0x28);
const u32 gMonBackPic_Plusle[] = INCBIN_U32("assets/graphics.bin", 0x17C410, 0x2B8);
const u32 gMonShinyPalette_Plusle[] = INCBIN_U32("assets/graphics.bin", 0x17C6C8, 0x28);
const u8 gMonIcon_Plusle[] = INCBIN_U8("assets/graphics.bin", 0x17C6F0, 0x400);
const u8 gMonFootprint_Plusle[] = INCBIN_U8("assets/graphics.bin", 0x17CAF0, 0x20);

const u32 gMonFrontPic_Minun[] = INCBIN_U32("assets/graphics.bin", 0x17CB10, 0x268);
const u32 gMonPalette_Minun[] = INCBIN_U32("assets/graphics.bin", 0x17CD78, 0x28);
const u32 gMonBackPic_Minun[] = INCBIN_U32("assets/graphics.bin", 0x17CDA0, 0x2C8);
const u32 gMonShinyPalette_Minun[] = INCBIN_U32("assets/graphics.bin", 0x17D068, 0x28);
const u8 gMonIcon_Minun[] = INCBIN_U8("assets/graphics.bin", 0x17D090, 0x400);
const u8 gMonFootprint_Minun[] = INCBIN_U8("assets/graphics.bin", 0x17D490, 0x20);

const u32 gMonFrontPic_Mawile[] = INCBIN_U32("assets/graphics.bin", 0x17D4B0, 0x3BC);
const u32 gMonPalette_Mawile[] = INCBIN_U32("assets/graphics.bin", 0x17D86C, 0x28);
const u32 gMonBackPic_Mawile[] = INCBIN_U32("assets/graphics.bin", 0x17D894, 0x400);
const u32 gMonShinyPalette_Mawile[] = INCBIN_U32("assets/graphics.bin", 0x17DC94, 0x28);
const u8 gMonIcon_Mawile[] = INCBIN_U8("assets/graphics.bin", 0x17DCBC, 0x400);
const u8 gMonFootprint_Mawile[] = INCBIN_U8("assets/graphics.bin", 0x17E0BC, 0x20);

const u32 gMonFrontPic_Meditite[] = INCBIN_U32("assets/graphics.bin", 0x17E0DC, 0x2B8);
const u32 gMonPalette_Meditite[] = INCBIN_U32("assets/graphics.bin", 0x17E394, 0x28);
const u32 gMonBackPic_Meditite[] = INCBIN_U32("assets/graphics.bin", 0x17E3BC, 0x2C8);
const u32 gMonShinyPalette_Meditite[] = INCBIN_U32("assets/graphics.bin", 0x17E684, 0x24);
const u8 gMonIcon_Meditite[] = INCBIN_U8("assets/graphics.bin", 0x17E6A8, 0x400);
const u8 gMonFootprint_Meditite[] = INCBIN_U8("assets/graphics.bin", 0x17EAA8, 0x20);

const u32 gMonFrontPic_Medicham[] = INCBIN_U32("assets/graphics.bin", 0x17EAC8, 0x330);
const u32 gMonPalette_Medicham[] = INCBIN_U32("assets/graphics.bin", 0x17EDF8, 0x28);
const u32 gMonBackPic_Medicham[] = INCBIN_U32("assets/graphics.bin", 0x17EE20, 0x338);
const u32 gMonShinyPalette_Medicham[] = INCBIN_U32("assets/graphics.bin", 0x17F158, 0x28);
const u8 gMonIcon_Medicham[] = INCBIN_U8("assets/graphics.bin", 0x17F180, 0x400);
const u8 gMonFootprint_Medicham[] = INCBIN_U8("assets/graphics.bin", 0x17F580, 0x20);

const u32 gMonFrontPic_Swablu[] = INCBIN_U32("assets/graphics.bin", 0x17F5A0, 0x2D8);
const u32 gMonPalette_Swablu[] = INCBIN_U32("assets/graphics.bin", 0x17F878, 0x28);
const u32 gMonBackPic_Swablu[] = INCBIN_U32("assets/graphics.bin", 0x17F8A0, 0x3B8);
const u32 gMonShinyPalette_Swablu[] = INCBIN_U32("assets/graphics.bin", 0x17FC58, 0x28);
const u8 gMonIcon_Swablu[] = INCBIN_U8("assets/graphics.bin", 0x17FC80, 0x400);
const u8 gMonFootprint_Swablu[] = INCBIN_U8("assets/graphics.bin", 0x180080, 0x20);

const u32 gMonFrontPic_Altaria[] = INCBIN_U32("assets/graphics.bin", 0x1800A0, 0x3DC);
const u32 gMonPalette_Altaria[] = INCBIN_U32("assets/graphics.bin", 0x18047C, 0x28);
const u32 gMonBackPic_Altaria[] = INCBIN_U32("assets/graphics.bin", 0x1804A4, 0x378);
const u32 gMonShinyPalette_Altaria[] = INCBIN_U32("assets/graphics.bin", 0x18081C, 0x28);
const u8 gMonIcon_Altaria[] = INCBIN_U8("assets/graphics.bin", 0x180844, 0x400);
const u8 gMonFootprint_Altaria[] = INCBIN_U8("assets/graphics.bin", 0x180C44, 0x20);

const u32 gMonFrontPic_Wynaut[] = INCBIN_U32("assets/graphics.bin", 0x180C64, 0x298);
const u32 gMonPalette_Wynaut[] = INCBIN_U32("assets/graphics.bin", 0x180EFC, 0x28);
const u32 gMonBackPic_Wynaut[] = INCBIN_U32("assets/graphics.bin", 0x180F24, 0x290);
const u32 gMonShinyPalette_Wynaut[] = INCBIN_U32("assets/graphics.bin", 0x1811B4, 0x28);
const u8 gMonIcon_Wynaut[] = INCBIN_U8("assets/graphics.bin", 0x1811DC, 0x400);
const u8 gMonFootprint_Wynaut[] = INCBIN_U8("assets/graphics.bin", 0x1815DC, 0x20);

const u32 gMonFrontPic_Duskull[] = INCBIN_U32("assets/graphics.bin", 0x1815FC, 0x2F0);
const u32 gMonPalette_Duskull[] = INCBIN_U32("assets/graphics.bin", 0x1818EC, 0x28);
const u32 gMonBackPic_Duskull[] = INCBIN_U32("assets/graphics.bin", 0x181914, 0x2B0);
const u32 gMonShinyPalette_Duskull[] = INCBIN_U32("assets/graphics.bin", 0x181BC4, 0x28);
const u8 gMonIcon_Duskull[] = INCBIN_U8("assets/graphics.bin", 0x181BEC, 0x400);
const u8 gMonFootprint_Duskull[] = INCBIN_U8("assets/graphics.bin", 0x181FEC, 0x20);

const u32 gMonFrontPic_Dusclops[] = INCBIN_U32("assets/graphics.bin", 0x18200C, 0x3A0);
const u32 gMonPalette_Dusclops[] = INCBIN_U32("assets/graphics.bin", 0x1823AC, 0x28);
const u32 gMonBackPic_Dusclops[] = INCBIN_U32("assets/graphics.bin", 0x1823D4, 0x2EC);
const u32 gMonShinyPalette_Dusclops[] = INCBIN_U32("assets/graphics.bin", 0x1826C0, 0x28);
const u8 gMonIcon_Dusclops[] = INCBIN_U8("assets/graphics.bin", 0x1826E8, 0x400);
const u8 gMonFootprint_Dusclops[] = INCBIN_U8("assets/graphics.bin", 0x182AE8, 0x20);

const u32 gMonFrontPic_Roselia[] = INCBIN_U32("assets/graphics.bin", 0x182B08, 0x36C);
const u32 gMonPalette_Roselia[] = INCBIN_U32("assets/graphics.bin", 0x182E74, 0x28);
const u32 gMonBackPic_Roselia[] = INCBIN_U32("assets/graphics.bin", 0x182E9C, 0x3C8);
const u32 gMonShinyPalette_Roselia[] = INCBIN_U32("assets/graphics.bin", 0x183264, 0x28);
const u8 gMonIcon_Roselia[] = INCBIN_U8("assets/graphics.bin", 0x18328C, 0x400);
const u8 gMonFootprint_Roselia[] = INCBIN_U8("assets/graphics.bin", 0x18368C, 0x20);

const u32 gMonFrontPic_Slakoth[] = INCBIN_U32("assets/graphics.bin", 0x1836AC, 0x2E8);
const u32 gMonPalette_Slakoth[] = INCBIN_U32("assets/graphics.bin", 0x183994, 0x28);
const u32 gMonBackPic_Slakoth[] = INCBIN_U32("assets/graphics.bin", 0x1839BC, 0x2E8);
const u32 gMonShinyPalette_Slakoth[] = INCBIN_U32("assets/graphics.bin", 0x183CA4, 0x28);
const u8 gMonIcon_Slakoth[] = INCBIN_U8("assets/graphics.bin", 0x183CCC, 0x400);
const u8 gMonFootprint_Slakoth[] = INCBIN_U8("assets/graphics.bin", 0x1840CC, 0x20);

const u32 gMonFrontPic_Vigoroth[] = INCBIN_U32("assets/graphics.bin", 0x1840EC, 0x3FC);
const u32 gMonPalette_Vigoroth[] = INCBIN_U32("assets/graphics.bin", 0x1844E8, 0x28);
const u32 gMonBackPic_Vigoroth[] = INCBIN_U32("assets/graphics.bin", 0x184510, 0x2C8);
const u32 gMonShinyPalette_Vigoroth[] = INCBIN_U32("assets/graphics.bin", 0x1847D8, 0x28);
const u8 gMonIcon_Vigoroth[] = INCBIN_U8("assets/graphics.bin", 0x184800, 0x400);
const u8 gMonFootprint_Vigoroth[] = INCBIN_U8("assets/graphics.bin", 0x184C00, 0x20);

const u32 gMonFrontPic_Slaking[] = INCBIN_U32("assets/graphics.bin", 0x184C20, 0x4D4);
const u32 gMonPalette_Slaking[] = INCBIN_U32("assets/graphics.bin", 0x1850F4, 0x28);
const u32 gMonBackPic_Slaking[] = INCBIN_U32("assets/graphics.bin", 0x18511C, 0x3C4);
const u32 gMonShinyPalette_Slaking[] = INCBIN_U32("assets/graphics.bin", 0x1854E0, 0x28);
const u8 gMonIcon_Slaking[] = INCBIN_U8("assets/graphics.bin", 0x185508, 0x400);
const u8 gMonFootprint_Slaking[] = INCBIN_U8("assets/graphics.bin", 0x185908, 0x20);

const u32 gMonFrontPic_Gulpin[] = INCBIN_U32("assets/graphics.bin", 0x185928, 0x218);
const u32 gMonPalette_Gulpin[] = INCBIN_U32("assets/graphics.bin", 0x185B40, 0x28);
const u32 gMonBackPic_Gulpin[] = INCBIN_U32("assets/graphics.bin", 0x185B68, 0x284);
const u32 gMonShinyPalette_Gulpin[] = INCBIN_U32("assets/graphics.bin", 0x185DEC, 0x28);
const u8 gMonIcon_Gulpin[] = INCBIN_U8("assets/graphics.bin", 0x185E14, 0x400);
const u8 gMonFootprint_Gulpin[] = INCBIN_U8("assets/graphics.bin", 0x186214, 0x20);

const u32 gMonFrontPic_Swalot[] = INCBIN_U32("assets/graphics.bin", 0x186234, 0x344);
const u32 gMonPalette_Swalot[] = INCBIN_U32("assets/graphics.bin", 0x186578, 0x28);
const u32 gMonBackPic_Swalot[] = INCBIN_U32("assets/graphics.bin", 0x1865A0, 0x348);
const u32 gMonShinyPalette_Swalot[] = INCBIN_U32("assets/graphics.bin", 0x1868E8, 0x28);
const u8 gMonIcon_Swalot[] = INCBIN_U8("assets/graphics.bin", 0x186910, 0x400);
const u8 gMonFootprint_Swalot[] = INCBIN_U8("assets/graphics.bin", 0x186D10, 0x20);

const u32 gMonFrontPic_Tropius[] = INCBIN_U32("assets/graphics.bin", 0x186D30, 0x578);
const u32 gMonPalette_Tropius[] = INCBIN_U32("assets/graphics.bin", 0x1872A8, 0x28);
const u32 gMonBackPic_Tropius[] = INCBIN_U32("assets/graphics.bin", 0x1872D0, 0x324);
const u32 gMonShinyPalette_Tropius[] = INCBIN_U32("assets/graphics.bin", 0x1875F4, 0x28);
const u8 gMonIcon_Tropius[] = INCBIN_U8("assets/graphics.bin", 0x18761C, 0x400);
const u8 gMonFootprint_Tropius[] = INCBIN_U8("assets/graphics.bin", 0x187A1C, 0x20);

const u32 gMonFrontPic_Whismur[] = INCBIN_U32("assets/graphics.bin", 0x187A3C, 0x294);
const u32 gMonPalette_Whismur[] = INCBIN_U32("assets/graphics.bin", 0x187CD0, 0x28);
const u32 gMonBackPic_Whismur[] = INCBIN_U32("assets/graphics.bin", 0x187CF8, 0x270);
const u32 gMonShinyPalette_Whismur[] = INCBIN_U32("assets/graphics.bin", 0x187F68, 0x28);
const u8 gMonIcon_Whismur[] = INCBIN_U8("assets/graphics.bin", 0x187F90, 0x400);
const u8 gMonFootprint_Whismur[] = INCBIN_U8("assets/graphics.bin", 0x188390, 0x20);

const u32 gMonFrontPic_Loudred[] = INCBIN_U32("assets/graphics.bin", 0x1883B0, 0x478);
const u32 gMonPalette_Loudred[] = INCBIN_U32("assets/graphics.bin", 0x188828, 0x28);
const u32 gMonBackPic_Loudred[] = INCBIN_U32("assets/graphics.bin", 0x188850, 0x370);
const u32 gMonShinyPalette_Loudred[] = INCBIN_U32("assets/graphics.bin", 0x188BC0, 0x28);
const u8 gMonIcon_Loudred[] = INCBIN_U8("assets/graphics.bin", 0x188BE8, 0x400);
const u8 gMonFootprint_Loudred[] = INCBIN_U8("assets/graphics.bin", 0x188FE8, 0x20);

const u32 gMonFrontPic_Exploud[] = INCBIN_U32("assets/graphics.bin", 0x189008, 0x568);
const u32 gMonPalette_Exploud[] = INCBIN_U32("assets/graphics.bin", 0x189570, 0x28);
const u32 gMonBackPic_Exploud[] = INCBIN_U32("assets/graphics.bin", 0x189598, 0x40C);
const u32 gMonShinyPalette_Exploud[] = INCBIN_U32("assets/graphics.bin", 0x1899A4, 0x28);
const u8 gMonIcon_Exploud[] = INCBIN_U8("assets/graphics.bin", 0x1899CC, 0x400);
const u8 gMonFootprint_Exploud[] = INCBIN_U8("assets/graphics.bin", 0x189DCC, 0x20);

const u32 gMonFrontPic_Clamperl[] = INCBIN_U32("assets/graphics.bin", 0x189DEC, 0x2D8);
const u32 gMonPalette_Clamperl[] = INCBIN_U32("assets/graphics.bin", 0x18A0C4, 0x28);
const u32 gMonBackPic_Clamperl[] = INCBIN_U32("assets/graphics.bin", 0x18A0EC, 0x294);
const u32 gMonShinyPalette_Clamperl[] = INCBIN_U32("assets/graphics.bin", 0x18A380, 0x28);
const u8 gMonIcon_Clamperl[] = INCBIN_U8("assets/graphics.bin", 0x18A3A8, 0x400);
const u8 gMonFootprint_Clamperl[] = INCBIN_U8("assets/graphics.bin", 0x18A7A8, 0x20);

const u32 gMonFrontPic_Huntail[] = INCBIN_U32("assets/graphics.bin", 0x18A7C8, 0x3CC);
const u32 gMonPalette_Huntail[] = INCBIN_U32("assets/graphics.bin", 0x18AB94, 0x28);
const u32 gMonBackPic_Huntail[] = INCBIN_U32("assets/graphics.bin", 0x18ABBC, 0x354);
const u32 gMonShinyPalette_Huntail[] = INCBIN_U32("assets/graphics.bin", 0x18AF10, 0x28);
const u8 gMonIcon_Huntail[] = INCBIN_U8("assets/graphics.bin", 0x18AF38, 0x400);
const u8 gMonFootprint_Huntail[] = INCBIN_U8("assets/graphics.bin", 0x18B338, 0x20);

const u32 gMonFrontPic_Gorebyss[] = INCBIN_U32("assets/graphics.bin", 0x18B358, 0x310);
const u32 gMonPalette_Gorebyss[] = INCBIN_U32("assets/graphics.bin", 0x18B668, 0x28);
const u32 gMonBackPic_Gorebyss[] = INCBIN_U32("assets/graphics.bin", 0x18B690, 0x2E8);
const u32 gMonShinyPalette_Gorebyss[] = INCBIN_U32("assets/graphics.bin", 0x18B978, 0x28);
const u8 gMonIcon_Gorebyss[] = INCBIN_U8("assets/graphics.bin", 0x18B9A0, 0x400);
const u8 gMonFootprint_Gorebyss[] = INCBIN_U8("assets/graphics.bin", 0x18BDA0, 0x20);

const u32 gMonFrontPic_Absol[] = INCBIN_U32("assets/graphics.bin", 0x18BDC0, 0x430);
const u32 gMonPalette_Absol[] = INCBIN_U32("assets/graphics.bin", 0x18C1F0, 0x28);
const u32 gMonBackPic_Absol[] = INCBIN_U32("assets/graphics.bin", 0x18C218, 0x360);
const u32 gMonShinyPalette_Absol[] = INCBIN_U32("assets/graphics.bin", 0x18C578, 0x28);
const u8 gMonIcon_Absol[] = INCBIN_U8("assets/graphics.bin", 0x18C5A0, 0x400);
const u8 gMonFootprint_Absol[] = INCBIN_U8("assets/graphics.bin", 0x18C9A0, 0x20);

const u32 gMonFrontPic_Shuppet[] = INCBIN_U32("assets/graphics.bin", 0x18C9C0, 0x238);
const u32 gMonPalette_Shuppet[] = INCBIN_U32("assets/graphics.bin", 0x18CBF8, 0x28);
const u32 gMonBackPic_Shuppet[] = INCBIN_U32("assets/graphics.bin", 0x18CC20, 0x298);
const u32 gMonShinyPalette_Shuppet[] = INCBIN_U32("assets/graphics.bin", 0x18CEB8, 0x28);
const u8 gMonIcon_Shuppet[] = INCBIN_U8("assets/graphics.bin", 0x18CEE0, 0x400);
const u8 gMonFootprint_Shuppet[] = INCBIN_U8("assets/graphics.bin", 0x18D2E0, 0x20);

const u32 gMonFrontPic_Banette[] = INCBIN_U32("assets/graphics.bin", 0x18D300, 0x2B4);
const u32 gMonPalette_Banette[] = INCBIN_U32("assets/graphics.bin", 0x18D5B4, 0x28);
const u32 gMonBackPic_Banette[] = INCBIN_U32("assets/graphics.bin", 0x18D5DC, 0x27C);
const u32 gMonShinyPalette_Banette[] = INCBIN_U32("assets/graphics.bin", 0x18D858, 0x28);
const u8 gMonIcon_Banette[] = INCBIN_U8("assets/graphics.bin", 0x18D880, 0x400);
const u8 gMonFootprint_Banette[] = INCBIN_U8("assets/graphics.bin", 0x18DC80, 0x20);

const u32 gMonFrontPic_Seviper[] = INCBIN_U32("assets/graphics.bin", 0x18DCA0, 0x420);
const u32 gMonPalette_Seviper[] = INCBIN_U32("assets/graphics.bin", 0x18E0C0, 0x28);
const u32 gMonBackPic_Seviper[] = INCBIN_U32("assets/graphics.bin", 0x18E0E8, 0x48C);
const u32 gMonShinyPalette_Seviper[] = INCBIN_U32("assets/graphics.bin", 0x18E574, 0x28);
const u8 gMonIcon_Seviper[] = INCBIN_U8("assets/graphics.bin", 0x18E59C, 0x400);
const u8 gMonFootprint_Seviper[] = INCBIN_U8("assets/graphics.bin", 0x18E99C, 0x20);

const u32 gMonFrontPic_Zangoose[] = INCBIN_U32("assets/graphics.bin", 0x18E9BC, 0x3CC);
const u32 gMonPalette_Zangoose[] = INCBIN_U32("assets/graphics.bin", 0x18ED88, 0x28);
const u32 gMonBackPic_Zangoose[] = INCBIN_U32("assets/graphics.bin", 0x18EDB0, 0x374);
const u32 gMonShinyPalette_Zangoose[] = INCBIN_U32("assets/graphics.bin", 0x18F124, 0x28);
const u8 gMonIcon_Zangoose[] = INCBIN_U8("assets/graphics.bin", 0x18F14C, 0x400);
const u8 gMonFootprint_Zangoose[] = INCBIN_U8("assets/graphics.bin", 0x18F54C, 0x20);

const u32 gMonFrontPic_Relicanth[] = INCBIN_U32("assets/graphics.bin", 0x18F56C, 0x394);
const u32 gMonPalette_Relicanth[] = INCBIN_U32("assets/graphics.bin", 0x18F900, 0x28);
const u32 gMonBackPic_Relicanth[] = INCBIN_U32("assets/graphics.bin", 0x18F928, 0x358);
const u32 gMonShinyPalette_Relicanth[] = INCBIN_U32("assets/graphics.bin", 0x18FC80, 0x28);
const u8 gMonIcon_Relicanth[] = INCBIN_U8("assets/graphics.bin", 0x18FCA8, 0x400);
const u8 gMonFootprint_Relicanth[] = INCBIN_U8("assets/graphics.bin", 0x1900A8, 0x20);

const u32 gMonFrontPic_Aron[] = INCBIN_U32("assets/graphics.bin", 0x1900C8, 0x1E8);
const u32 gMonPalette_Aron[] = INCBIN_U32("assets/graphics.bin", 0x1902B0, 0x28);
const u32 gMonBackPic_Aron[] = INCBIN_U32("assets/graphics.bin", 0x1902D8, 0x228);
const u32 gMonShinyPalette_Aron[] = INCBIN_U32("assets/graphics.bin", 0x190500, 0x28);
const u8 gMonIcon_Aron[] = INCBIN_U8("assets/graphics.bin", 0x190528, 0x400);
const u8 gMonFootprint_Aron[] = INCBIN_U8("assets/graphics.bin", 0x190928, 0x20);

const u32 gMonFrontPic_Lairon[] = INCBIN_U32("assets/graphics.bin", 0x190948, 0x3CC);
const u32 gMonPalette_Lairon[] = INCBIN_U32("assets/graphics.bin", 0x190D14, 0x28);
const u32 gMonBackPic_Lairon[] = INCBIN_U32("assets/graphics.bin", 0x190D3C, 0x2EC);
const u32 gMonShinyPalette_Lairon[] = INCBIN_U32("assets/graphics.bin", 0x191028, 0x28);
const u8 gMonIcon_Lairon[] = INCBIN_U8("assets/graphics.bin", 0x191050, 0x400);
const u8 gMonFootprint_Lairon[] = INCBIN_U8("assets/graphics.bin", 0x191450, 0x20);

const u32 gMonFrontPic_Aggron[] = INCBIN_U32("assets/graphics.bin", 0x191470, 0x57C);
const u32 gMonPalette_Aggron[] = INCBIN_U32("assets/graphics.bin", 0x1919EC, 0x28);
const u32 gMonBackPic_Aggron[] = INCBIN_U32("assets/graphics.bin", 0x191A14, 0x428);
const u32 gMonShinyPalette_Aggron[] = INCBIN_U32("assets/graphics.bin", 0x191E3C, 0x28);
const u8 gMonIcon_Aggron[] = INCBIN_U8("assets/graphics.bin", 0x191E64, 0x400);
const u8 gMonFootprint_Aggron[] = INCBIN_U8("assets/graphics.bin", 0x192264, 0x20);

const u32 gMonFrontPic_Castform[] = INCBIN_U32("assets/graphics.bin", 0x192284, 0xA88);
const u32 gMonPalette_Castform[] = INCBIN_U32("assets/graphics.bin", 0x192D0C, 0x80);
const u32 gMonBackPic_Castform[] = INCBIN_U32("assets/graphics.bin", 0x192D8C, 0x9BC);
const u32 gMonShinyPalette_Castform[] = INCBIN_U32("assets/graphics.bin", 0x193748, 0x7C);
const u8 gMonIcon_Castform[] = INCBIN_U8("assets/graphics.bin", 0x1937C4, 0x400);
const u8 gMonFootprint_Castform[] = INCBIN_U8("assets/graphics.bin", 0x193BC4, 0x20);

const u32 gMonFrontPic_Volbeat[] = INCBIN_U32("assets/graphics.bin", 0x193BE4, 0x390);
const u32 gMonPalette_Volbeat[] = INCBIN_U32("assets/graphics.bin", 0x193F74, 0x28);
const u32 gMonBackPic_Volbeat[] = INCBIN_U32("assets/graphics.bin", 0x193F9C, 0x360);
const u32 gMonShinyPalette_Volbeat[] = INCBIN_U32("assets/graphics.bin", 0x1942FC, 0x28);
const u8 gMonIcon_Volbeat[] = INCBIN_U8("assets/graphics.bin", 0x194324, 0x400);
const u8 gMonFootprint_Volbeat[] = INCBIN_U8("assets/graphics.bin", 0x194724, 0x20);

const u32 gMonFrontPic_Illumise[] = INCBIN_U32("assets/graphics.bin", 0x194744, 0x374);
const u32 gMonPalette_Illumise[] = INCBIN_U32("assets/graphics.bin", 0x194AB8, 0x28);
const u32 gMonBackPic_Illumise[] = INCBIN_U32("assets/graphics.bin", 0x194AE0, 0x31C);
const u32 gMonShinyPalette_Illumise[] = INCBIN_U32("assets/graphics.bin", 0x194DFC, 0x28);
const u8 gMonIcon_Illumise[] = INCBIN_U8("assets/graphics.bin", 0x194E24, 0x400);
const u8 gMonFootprint_Illumise[] = INCBIN_U8("assets/graphics.bin", 0x195224, 0x20);

const u32 gMonFrontPic_Lileep[] = INCBIN_U32("assets/graphics.bin", 0x195244, 0x344);
const u32 gMonPalette_Lileep[] = INCBIN_U32("assets/graphics.bin", 0x195588, 0x28);
const u32 gMonBackPic_Lileep[] = INCBIN_U32("assets/graphics.bin", 0x1955B0, 0x344);
const u32 gMonShinyPalette_Lileep[] = INCBIN_U32("assets/graphics.bin", 0x1958F4, 0x28);
const u8 gMonIcon_Lileep[] = INCBIN_U8("assets/graphics.bin", 0x19591C, 0x400);
const u8 gMonFootprint_Lileep[] = INCBIN_U8("assets/graphics.bin", 0x195D1C, 0x20);

const u32 gMonFrontPic_Cradily[] = INCBIN_U32("assets/graphics.bin", 0x195D3C, 0x41C);
const u32 gMonPalette_Cradily[] = INCBIN_U32("assets/graphics.bin", 0x196158, 0x28);
const u32 gMonBackPic_Cradily[] = INCBIN_U32("assets/graphics.bin", 0x196180, 0x3FC);
const u32 gMonShinyPalette_Cradily[] = INCBIN_U32("assets/graphics.bin", 0x19657C, 0x28);
const u8 gMonIcon_Cradily[] = INCBIN_U8("assets/graphics.bin", 0x1965A4, 0x400);
const u8 gMonFootprint_Cradily[] = INCBIN_U8("assets/graphics.bin", 0x1969A4, 0x20);

const u32 gMonFrontPic_Anorith[] = INCBIN_U32("assets/graphics.bin", 0x1969C4, 0x324);
const u32 gMonPalette_Anorith[] = INCBIN_U32("assets/graphics.bin", 0x196CE8, 0x28);
const u32 gMonBackPic_Anorith[] = INCBIN_U32("assets/graphics.bin", 0x196D10, 0x248);
const u32 gMonShinyPalette_Anorith[] = INCBIN_U32("assets/graphics.bin", 0x196F58, 0x28);
const u8 gMonIcon_Anorith[] = INCBIN_U8("assets/graphics.bin", 0x196F80, 0x400);
const u8 gMonFootprint_Anorith[] = INCBIN_U8("assets/graphics.bin", 0x197380, 0x20);

const u32 gMonFrontPic_Armaldo[] = INCBIN_U32("assets/graphics.bin", 0x1973A0, 0x580);
const u32 gMonPalette_Armaldo[] = INCBIN_U32("assets/graphics.bin", 0x197920, 0x28);
const u32 gMonBackPic_Armaldo[] = INCBIN_U32("assets/graphics.bin", 0x197948, 0x438);
const u32 gMonShinyPalette_Armaldo[] = INCBIN_U32("assets/graphics.bin", 0x197D80, 0x28);
const u8 gMonIcon_Armaldo[] = INCBIN_U8("assets/graphics.bin", 0x197DA8, 0x400);
const u8 gMonFootprint_Armaldo[] = INCBIN_U8("assets/graphics.bin", 0x1981A8, 0x20);

const u32 gMonFrontPic_Ralts[] = INCBIN_U32("assets/graphics.bin", 0x1981C8, 0x230);
const u32 gMonPalette_Ralts[] = INCBIN_U32("assets/graphics.bin", 0x1983F8, 0x28);
const u32 gMonBackPic_Ralts[] = INCBIN_U32("assets/graphics.bin", 0x198420, 0x23C);
const u32 gMonShinyPalette_Ralts[] = INCBIN_U32("assets/graphics.bin", 0x19865C, 0x28);
const u8 gMonIcon_Ralts[] = INCBIN_U8("assets/graphics.bin", 0x198684, 0x400);
const u8 gMonFootprint_Ralts[] = INCBIN_U8("assets/graphics.bin", 0x198A84, 0x20);

const u32 gMonFrontPic_Kirlia[] = INCBIN_U32("assets/graphics.bin", 0x198AA4, 0x2FC);
const u32 gMonPalette_Kirlia[] = INCBIN_U32("assets/graphics.bin", 0x198DA0, 0x28);
const u32 gMonBackPic_Kirlia[] = INCBIN_U32("assets/graphics.bin", 0x198DC8, 0x374);
const u32 gMonShinyPalette_Kirlia[] = INCBIN_U32("assets/graphics.bin", 0x19913C, 0x28);
const u8 gMonIcon_Kirlia[] = INCBIN_U8("assets/graphics.bin", 0x199164, 0x400);
const u8 gMonFootprint_Kirlia[] = INCBIN_U8("assets/graphics.bin", 0x199564, 0x20);

const u32 gMonFrontPic_Gardevoir[] = INCBIN_U32("assets/graphics.bin", 0x199584, 0x37C);
const u32 gMonPalette_Gardevoir[] = INCBIN_U32("assets/graphics.bin", 0x199900, 0x28);
const u32 gMonBackPic_Gardevoir[] = INCBIN_U32("assets/graphics.bin", 0x199928, 0x334);
const u32 gMonShinyPalette_Gardevoir[] = INCBIN_U32("assets/graphics.bin", 0x199C5C, 0x28);
const u8 gMonIcon_Gardevoir[] = INCBIN_U8("assets/graphics.bin", 0x199C84, 0x400);
const u8 gMonFootprint_Gardevoir[] = INCBIN_U8("assets/graphics.bin", 0x19A084, 0x20);

const u32 gMonFrontPic_Bagon[] = INCBIN_U32("assets/graphics.bin", 0x19A0A4, 0x278);
const u32 gMonPalette_Bagon[] = INCBIN_U32("assets/graphics.bin", 0x19A31C, 0x28);
const u32 gMonBackPic_Bagon[] = INCBIN_U32("assets/graphics.bin", 0x19A344, 0x2E8);
const u32 gMonShinyPalette_Bagon[] = INCBIN_U32("assets/graphics.bin", 0x19A62C, 0x28);
const u8 gMonIcon_Bagon[] = INCBIN_U8("assets/graphics.bin", 0x19A654, 0x400);
const u8 gMonFootprint_Bagon[] = INCBIN_U8("assets/graphics.bin", 0x19AA54, 0x20);

const u32 gMonFrontPic_Shelgon[] = INCBIN_U32("assets/graphics.bin", 0x19AA74, 0x304);
const u32 gMonPalette_Shelgon[] = INCBIN_U32("assets/graphics.bin", 0x19AD78, 0x28);
const u32 gMonBackPic_Shelgon[] = INCBIN_U32("assets/graphics.bin", 0x19ADA0, 0x2E8);
const u32 gMonShinyPalette_Shelgon[] = INCBIN_U32("assets/graphics.bin", 0x19B088, 0x28);
const u8 gMonIcon_Shelgon[] = INCBIN_U8("assets/graphics.bin", 0x19B0B0, 0x400);
const u8 gMonFootprint_Shelgon[] = INCBIN_U8("assets/graphics.bin", 0x19B4B0, 0x20);

const u32 gMonFrontPic_Salamence[] = INCBIN_U32("assets/graphics.bin", 0x19B4D0, 0x464);
const u32 gMonPalette_Salamence[] = INCBIN_U32("assets/graphics.bin", 0x19B934, 0x28);
const u32 gMonBackPic_Salamence[] = INCBIN_U32("assets/graphics.bin", 0x19B95C, 0x2E4);
const u32 gMonShinyPalette_Salamence[] = INCBIN_U32("assets/graphics.bin", 0x19BC40, 0x28);
const u8 gMonIcon_Salamence[] = INCBIN_U8("assets/graphics.bin", 0x19BC68, 0x400);
const u8 gMonFootprint_Salamence[] = INCBIN_U8("assets/graphics.bin", 0x19C068, 0x20);

const u32 gMonFrontPic_Beldum[] = INCBIN_U32("assets/graphics.bin", 0x19C088, 0x270);
const u32 gMonPalette_Beldum[] = INCBIN_U32("assets/graphics.bin", 0x19C2F8, 0x28);
const u32 gMonBackPic_Beldum[] = INCBIN_U32("assets/graphics.bin", 0x19C320, 0x2F0);
const u32 gMonShinyPalette_Beldum[] = INCBIN_U32("assets/graphics.bin", 0x19C610, 0x28);
const u8 gMonIcon_Beldum[] = INCBIN_U8("assets/graphics.bin", 0x19C638, 0x400);
const u8 gMonFootprint_Beldum[] = INCBIN_U8("assets/graphics.bin", 0x19CA38, 0x20);

const u32 gMonFrontPic_Metang[] = INCBIN_U32("assets/graphics.bin", 0x19CA58, 0x45C);
const u32 gMonPalette_Metang[] = INCBIN_U32("assets/graphics.bin", 0x19CEB4, 0x28);
const u32 gMonBackPic_Metang[] = INCBIN_U32("assets/graphics.bin", 0x19CEDC, 0x324);
const u32 gMonShinyPalette_Metang[] = INCBIN_U32("assets/graphics.bin", 0x19D200, 0x28);
const u8 gMonIcon_Metang[] = INCBIN_U8("assets/graphics.bin", 0x19D228, 0x400);
const u8 gMonFootprint_Metang[] = INCBIN_U8("assets/graphics.bin", 0x19D628, 0x20);

const u32 gMonFrontPic_Metagross[] = INCBIN_U32("assets/graphics.bin", 0x19D648, 0x464);
const u32 gMonPalette_Metagross[] = INCBIN_U32("assets/graphics.bin", 0x19DAAC, 0x28);
const u32 gMonBackPic_Metagross[] = INCBIN_U32("assets/graphics.bin", 0x19DAD4, 0x2CC);
const u32 gMonShinyPalette_Metagross[] = INCBIN_U32("assets/graphics.bin", 0x19DDA0, 0x28);
const u8 gMonIcon_Metagross[] = INCBIN_U8("assets/graphics.bin", 0x19DDC8, 0x400);
const u8 gMonFootprint_Metagross[] = INCBIN_U8("assets/graphics.bin", 0x19E1C8, 0x20);

const u32 gMonFrontPic_Regirock[] = INCBIN_U32("assets/graphics.bin", 0x19E1E8, 0x4BC);
const u32 gMonPalette_Regirock[] = INCBIN_U32("assets/graphics.bin", 0x19E6A4, 0x28);
const u32 gMonBackPic_Regirock[] = INCBIN_U32("assets/graphics.bin", 0x19E6CC, 0x44C);
const u32 gMonShinyPalette_Regirock[] = INCBIN_U32("assets/graphics.bin", 0x19EB18, 0x28);
const u8 gMonIcon_Regirock[] = INCBIN_U8("assets/graphics.bin", 0x19EB40, 0x400);
const u8 gMonFootprint_Regirock[] = INCBIN_U8("assets/graphics.bin", 0x19EF40, 0x20);

const u32 gMonFrontPic_Regice[] = INCBIN_U32("assets/graphics.bin", 0x19EF60, 0x448);
const u32 gMonPalette_Regice[] = INCBIN_U32("assets/graphics.bin", 0x19F3A8, 0x28);
const u32 gMonBackPic_Regice[] = INCBIN_U32("assets/graphics.bin", 0x19F3D0, 0x2F0);
const u32 gMonShinyPalette_Regice[] = INCBIN_U32("assets/graphics.bin", 0x19F6C0, 0x28);
const u8 gMonIcon_Regice[] = INCBIN_U8("assets/graphics.bin", 0x19F6E8, 0x400);
const u8 gMonFootprint_Regice[] = INCBIN_U8("assets/graphics.bin", 0x19FAE8, 0x20);

const u32 gMonFrontPic_Registeel[] = INCBIN_U32("assets/graphics.bin", 0x19FB08, 0x488);
const u32 gMonPalette_Registeel[] = INCBIN_U32("assets/graphics.bin", 0x19FF90, 0x28);
const u32 gMonBackPic_Registeel[] = INCBIN_U32("assets/graphics.bin", 0x19FFB8, 0x338);
const u32 gMonShinyPalette_Registeel[] = INCBIN_U32("assets/graphics.bin", 0x1A02F0, 0x28);
const u8 gMonIcon_Registeel[] = INCBIN_U8("assets/graphics.bin", 0x1A0318, 0x400);
const u8 gMonFootprint_Registeel[] = INCBIN_U8("assets/graphics.bin", 0x1A0718, 0x20);

const u32 gMonFrontPic_Kyogre[] = INCBIN_U32("assets/graphics.bin", 0x1A0738, 0x470);
const u32 gMonPalette_Kyogre[] = INCBIN_U32("assets/graphics.bin", 0x1A0BA8, 0x28);
const u32 gMonBackPic_Kyogre[] = INCBIN_U32("assets/graphics.bin", 0x1A0BD0, 0x278);
const u32 gMonShinyPalette_Kyogre[] = INCBIN_U32("assets/graphics.bin", 0x1A0E48, 0x28);
const u8 gMonIcon_Kyogre[] = INCBIN_U8("assets/graphics.bin", 0x1A0E70, 0x400);
const u8 gMonFootprint_Kyogre[] = INCBIN_U8("assets/graphics.bin", 0x1A1270, 0x20);

const u32 gMonFrontPic_Groudon[] = INCBIN_U32("assets/graphics.bin", 0x1A1290, 0x594);
const u32 gMonPalette_Groudon[] = INCBIN_U32("assets/graphics.bin", 0x1A1824, 0x28);
const u32 gMonBackPic_Groudon[] = INCBIN_U32("assets/graphics.bin", 0x1A184C, 0x468);
const u32 gMonShinyPalette_Groudon[] = INCBIN_U32("assets/graphics.bin", 0x1A1CB4, 0x28);
const u8 gMonIcon_Groudon[] = INCBIN_U8("assets/graphics.bin", 0x1A1CDC, 0x400);
const u8 gMonFootprint_Groudon[] = INCBIN_U8("assets/graphics.bin", 0x1A20DC, 0x20);

const u32 gMonFrontPic_Rayquaza[] = INCBIN_U32("assets/graphics.bin", 0x1A20FC, 0x510);
const u32 gMonPalette_Rayquaza[] = INCBIN_U32("assets/graphics.bin", 0x1A260C, 0x28);
const u32 gMonBackPic_Rayquaza[] = INCBIN_U32("assets/graphics.bin", 0x1A2634, 0x338);
const u32 gMonShinyPalette_Rayquaza[] = INCBIN_U32("assets/graphics.bin", 0x1A296C, 0x28);
const u8 gMonIcon_Rayquaza[] = INCBIN_U8("assets/graphics.bin", 0x1A2994, 0x400);
const u8 gMonFootprint_Rayquaza[] = INCBIN_U8("assets/graphics.bin", 0x1A2D94, 0x20);

const u32 gMonFrontPic_Latias[] = INCBIN_U32("assets/graphics.bin", 0x1A2DB4, 0x424);
const u32 gMonPalette_Latias[] = INCBIN_U32("assets/graphics.bin", 0x1A31D8, 0x28);
const u32 gMonBackPic_Latias[] = INCBIN_U32("assets/graphics.bin", 0x1A3200, 0x2FC);
const u32 gMonShinyPalette_Latias[] = INCBIN_U32("assets/graphics.bin", 0x1A34FC, 0x28);
const u8 gMonIcon_Latias[] = INCBIN_U8("assets/graphics.bin", 0x1A3524, 0x400);
const u8 gMonFootprint_Latias[] = INCBIN_U8("assets/graphics.bin", 0x1A3924, 0x20);

const u32 gMonFrontPic_Latios[] = INCBIN_U32("assets/graphics.bin", 0x1A3944, 0x454);
const u32 gMonPalette_Latios[] = INCBIN_U32("assets/graphics.bin", 0x1A3D98, 0x28);
const u32 gMonBackPic_Latios[] = INCBIN_U32("assets/graphics.bin", 0x1A3DC0, 0x360);
const u32 gMonShinyPalette_Latios[] = INCBIN_U32("assets/graphics.bin", 0x1A4120, 0x28);
const u8 gMonIcon_Latios[] = INCBIN_U8("assets/graphics.bin", 0x1A4148, 0x400);
const u8 gMonFootprint_Latios[] = INCBIN_U8("assets/graphics.bin", 0x1A4548, 0x20);

const u32 gMonFrontPic_Jirachi[] = INCBIN_U32("assets/graphics.bin", 0x1A4568, 0x30C);
const u32 gMonPalette_Jirachi[] = INCBIN_U32("assets/graphics.bin", 0x1A4874, 0x28);
const u32 gMonBackPic_Jirachi[] = INCBIN_U32("assets/graphics.bin", 0x1A489C, 0x3A0);
const u32 gMonShinyPalette_Jirachi[] = INCBIN_U32("assets/graphics.bin", 0x1A4C3C, 0x28);
const u8 gMonIcon_Jirachi[] = INCBIN_U8("assets/graphics.bin", 0x1A4C64, 0x400);
const u8 gMonFootprint_Jirachi[] = INCBIN_U8("assets/graphics.bin", 0x1A5064, 0x20);

#ifdef FIRERED
const u32 gMonFrontPic_Deoxys[] = INCBIN_U32("assets/graphics.bin", 0x1A5084, 0x7BC);
const u32 gMonPalette_Deoxys[] = INCBIN_U32("assets/graphics.bin", 0x1A5840, 0x28);
const u32 gMonBackPic_Deoxys[] = INCBIN_U32("assets/graphics.bin", 0x1A5868, 0x5F0);
const u32 gMonShinyPalette_Deoxys[] = INCBIN_U32("assets/graphics.bin", 0x1A5E58, 0x28);
const u8 gMonIcon_Deoxys[] = INCBIN_U8("assets/graphics.bin", 0x1A5E80, 0x400, "assets/graphics.bin", 0x1A6280, 0x400);
const u8 gMonFootprint_Deoxys[] = INCBIN_U8("assets/graphics.bin", 0x1A6680, 0x20);
#endif

#ifdef LEAFGREEN
const u32 gMonFrontPic_Deoxys[] = INCBIN_U32("assets/graphics.bin", 0x1A66A0, 0x834);
const u32 gMonPalette_Deoxys[] = INCBIN_U32("assets/graphics.bin", 0x1A5840, 0x28);
const u32 gMonBackPic_Deoxys[] = INCBIN_U32("assets/graphics.bin", 0x1A6ED4, 0x5F8);
const u32 gMonShinyPalette_Deoxys[] = INCBIN_U32("assets/graphics.bin", 0x1A5E58, 0x28);
const u8 gMonIcon_Deoxys[] = INCBIN_U8("assets/graphics.bin", 0x1A5E80, 0x400, "assets/graphics.bin", 0x1A74CC, 0x400);
const u8 gMonFootprint_Deoxys[] = INCBIN_U8("assets/graphics.bin", 0x1A6680, 0x20);
#endif

const u32 gMonFrontPic_Chimecho[] = INCBIN_U32("assets/graphics.bin", 0x1A78CC, 0x24C);
const u32 gMonPalette_Chimecho[] = INCBIN_U32("assets/graphics.bin", 0x1A7B18, 0x28);
const u32 gMonBackPic_Chimecho[] = INCBIN_U32("assets/graphics.bin", 0x1A7B40, 0x274);
const u32 gMonShinyPalette_Chimecho[] = INCBIN_U32("assets/graphics.bin", 0x1A7DB4, 0x28);
const u8 gMonIcon_Chimecho[] = INCBIN_U8("assets/graphics.bin", 0x1A7DDC, 0x400);
const u8 gMonFootprint_Chimecho[] = INCBIN_U8("assets/graphics.bin", 0x1A81DC, 0x20);

const u32 gMonFrontPic_Egg[] = INCBIN_U32("assets/graphics.bin", 0x1A81FC, 0x1B4);
const u32 gMonPalette_Egg[] = INCBIN_U32("assets/graphics.bin", 0x1A83B0, 0x20);

const u32 gMonFrontPic_UnownB[] = INCBIN_U32("assets/graphics.bin", 0x1A83D0, 0x1D8);
const u32 gMonBackPic_UnownB[] = INCBIN_U32("assets/graphics.bin", 0x1A85A8, 0x204);
const u8 gMonIcon_UnownB[] = INCBIN_U8("assets/graphics.bin", 0x1A87AC, 0x400);

const u32 gMonFrontPic_UnownC[] = INCBIN_U32("assets/graphics.bin", 0x1A8BAC, 0x214);
const u32 gMonBackPic_UnownC[] = INCBIN_U32("assets/graphics.bin", 0x1A8DC0, 0x2AC);
const u8 gMonIcon_UnownC[] = INCBIN_U8("assets/graphics.bin", 0x1A906C, 0x400);

const u32 gMonFrontPic_UnownD[] = INCBIN_U32("assets/graphics.bin", 0x1A946C, 0x1F8);
const u32 gMonBackPic_UnownD[] = INCBIN_U32("assets/graphics.bin", 0x1A9664, 0x258);
const u8 gMonIcon_UnownD[] = INCBIN_U8("assets/graphics.bin", 0x1A98BC, 0x400);

const u32 gMonFrontPic_UnownE[] = INCBIN_U32("assets/graphics.bin", 0x1A9CBC, 0x1B8);
const u32 gMonBackPic_UnownE[] = INCBIN_U32("assets/graphics.bin", 0x1A9E74, 0x200);
const u8 gMonIcon_UnownE[] = INCBIN_U8("assets/graphics.bin", 0x1AA074, 0x400);

const u32 gMonFrontPic_UnownF[] = INCBIN_U32("assets/graphics.bin", 0x1AA474, 0x1F4);
const u32 gMonBackPic_UnownF[] = INCBIN_U32("assets/graphics.bin", 0x1AA668, 0x21C);
const u8 gMonIcon_UnownF[] = INCBIN_U8("assets/graphics.bin", 0x1AA884, 0x400);

const u32 gMonFrontPic_UnownG[] = INCBIN_U32("assets/graphics.bin", 0x1AAC84, 0x1DC);
const u32 gMonBackPic_UnownG[] = INCBIN_U32("assets/graphics.bin", 0x1AAE60, 0x24C);
const u8 gMonIcon_UnownG[] = INCBIN_U8("assets/graphics.bin", 0x1AB0AC, 0x400);

const u32 gMonFrontPic_UnownH[] = INCBIN_U32("assets/graphics.bin", 0x1AB4AC, 0x244);
const u32 gMonBackPic_UnownH[] = INCBIN_U32("assets/graphics.bin", 0x1AB6F0, 0x2C4);
const u8 gMonIcon_UnownH[] = INCBIN_U8("assets/graphics.bin", 0x1AB9B4, 0x400);

const u32 gMonFrontPic_UnownI[] = INCBIN_U32("assets/graphics.bin", 0x1ABDB4, 0x198);
const u32 gMonBackPic_UnownI[] = INCBIN_U32("assets/graphics.bin", 0x1ABF4C, 0x1A8);
const u8 gMonIcon_UnownI[] = INCBIN_U8("assets/graphics.bin", 0x1AC0F4, 0x400);

const u32 gMonFrontPic_UnownJ[] = INCBIN_U32("assets/graphics.bin", 0x1AC4F4, 0x1C4);
const u32 gMonBackPic_UnownJ[] = INCBIN_U32("assets/graphics.bin", 0x1AC6B8, 0x1E8);
const u8 gMonIcon_UnownJ[] = INCBIN_U8("assets/graphics.bin", 0x1AC8A0, 0x400);

const u32 gMonFrontPic_UnownK[] = INCBIN_U32("assets/graphics.bin", 0x1ACCA0, 0x1D0);
const u32 gMonBackPic_UnownK[] = INCBIN_U32("assets/graphics.bin", 0x1ACE70, 0x1F8);
const u8 gMonIcon_UnownK[] = INCBIN_U8("assets/graphics.bin", 0x1AD068, 0x400);

const u32 gMonFrontPic_UnownL[] = INCBIN_U32("assets/graphics.bin", 0x1AD468, 0x1B0);
const u32 gMonBackPic_UnownL[] = INCBIN_U32("assets/graphics.bin", 0x1AD618, 0x1D4);
const u8 gMonIcon_UnownL[] = INCBIN_U8("assets/graphics.bin", 0x1AD7EC, 0x400);

const u32 gMonFrontPic_UnownM[] = INCBIN_U32("assets/graphics.bin", 0x1ADBEC, 0x224);
const u32 gMonBackPic_UnownM[] = INCBIN_U32("assets/graphics.bin", 0x1ADE10, 0x2A8);
const u8 gMonIcon_UnownM[] = INCBIN_U8("assets/graphics.bin", 0x1AE0B8, 0x400);

const u32 gMonFrontPic_UnownN[] = INCBIN_U32("assets/graphics.bin", 0x1AE4B8, 0x1F8);
const u32 gMonBackPic_UnownN[] = INCBIN_U32("assets/graphics.bin", 0x1AE6B0, 0x26C);
const u8 gMonIcon_UnownN[] = INCBIN_U8("assets/graphics.bin", 0x1AE91C, 0x400);

const u32 gMonFrontPic_UnownO[] = INCBIN_U32("assets/graphics.bin", 0x1AED1C, 0x238);
const u32 gMonBackPic_UnownO[] = INCBIN_U32("assets/graphics.bin", 0x1AEF54, 0x2C0);
const u8 gMonIcon_UnownO[] = INCBIN_U8("assets/graphics.bin", 0x1AF214, 0x400);

const u32 gMonFrontPic_UnownP[] = INCBIN_U32("assets/graphics.bin", 0x1AF614, 0x1A0);
const u32 gMonBackPic_UnownP[] = INCBIN_U32("assets/graphics.bin", 0x1AF7B4, 0x1C4);
const u8 gMonIcon_UnownP[] = INCBIN_U8("assets/graphics.bin", 0x1AF978, 0x400);

const u32 gMonFrontPic_UnownQ[] = INCBIN_U32("assets/graphics.bin", 0x1AFD78, 0x1B4);
const u32 gMonBackPic_UnownQ[] = INCBIN_U32("assets/graphics.bin", 0x1AFF2C, 0x1CC);
const u8 gMonIcon_UnownQ[] = INCBIN_U8("assets/graphics.bin", 0x1B00F8, 0x400);

const u32 gMonFrontPic_UnownR[] = INCBIN_U32("assets/graphics.bin", 0x1B04F8, 0x1A4);
const u32 gMonBackPic_UnownR[] = INCBIN_U32("assets/graphics.bin", 0x1B069C, 0x1C8);
const u8 gMonIcon_UnownR[] = INCBIN_U8("assets/graphics.bin", 0x1B0864, 0x400);

const u32 gMonFrontPic_UnownS[] = INCBIN_U32("assets/graphics.bin", 0x1B0C64, 0x1E8);
const u32 gMonBackPic_UnownS[] = INCBIN_U32("assets/graphics.bin", 0x1B0E4C, 0x254);
const u8 gMonIcon_UnownS[] = INCBIN_U8("assets/graphics.bin", 0x1B10A0, 0x400);

const u32 gMonFrontPic_UnownT[] = INCBIN_U32("assets/graphics.bin", 0x1B14A0, 0x1B0);
const u32 gMonBackPic_UnownT[] = INCBIN_U32("assets/graphics.bin", 0x1B1650, 0x1B4);
const u8 gMonIcon_UnownT[] = INCBIN_U8("assets/graphics.bin", 0x1B1804, 0x400);

const u32 gMonFrontPic_UnownU[] = INCBIN_U32("assets/graphics.bin", 0x1B1C04, 0x218);
const u32 gMonBackPic_UnownU[] = INCBIN_U32("assets/graphics.bin", 0x1B1E1C, 0x254);
const u8 gMonIcon_UnownU[] = INCBIN_U8("assets/graphics.bin", 0x1B2070, 0x400);

const u32 gMonFrontPic_UnownV[] = INCBIN_U32("assets/graphics.bin", 0x1B2470, 0x1E4);
const u32 gMonBackPic_UnownV[] = INCBIN_U32("assets/graphics.bin", 0x1B2654, 0x230);
const u8 gMonIcon_UnownV[] = INCBIN_U8("assets/graphics.bin", 0x1B2884, 0x400);

const u32 gMonFrontPic_UnownW[] = INCBIN_U32("assets/graphics.bin", 0x1B2C84, 0x1D4);
const u32 gMonBackPic_UnownW[] = INCBIN_U32("assets/graphics.bin", 0x1B2E58, 0x204);
const u8 gMonIcon_UnownW[] = INCBIN_U8("assets/graphics.bin", 0x1B305C, 0x400);

const u32 gMonFrontPic_UnownX[] = INCBIN_U32("assets/graphics.bin", 0x1B345C, 0x1C4);
const u32 gMonBackPic_UnownX[] = INCBIN_U32("assets/graphics.bin", 0x1B3620, 0x1F0);
const u8 gMonIcon_UnownX[] = INCBIN_U8("assets/graphics.bin", 0x1B3810, 0x400);

const u32 gMonFrontPic_UnownY[] = INCBIN_U32("assets/graphics.bin", 0x1B3C10, 0x1D8);
const u32 gMonBackPic_UnownY[] = INCBIN_U32("assets/graphics.bin", 0x1B3DE8, 0x1F4);
const u8 gMonIcon_UnownY[] = INCBIN_U8("assets/graphics.bin", 0x1B3FDC, 0x400);

const u32 gMonFrontPic_UnownZ[] = INCBIN_U32("assets/graphics.bin", 0x1B43DC, 0x1B0);
const u32 gMonBackPic_UnownZ[] = INCBIN_U32("assets/graphics.bin", 0x1B458C, 0x1DC);
const u8 gMonIcon_UnownZ[] = INCBIN_U8("assets/graphics.bin", 0x1B4768, 0x400);

const u32 gMonFrontPic_UnownExclamationMark[] = INCBIN_U32("assets/graphics.bin", 0x1B4B68, 0x190);
const u32 gMonBackPic_UnownExclamationMark[] = INCBIN_U32("assets/graphics.bin", 0x1B4CF8, 0x1C8);
const u8 gMonIcon_UnownExclamationMark[] = INCBIN_U8("assets/graphics.bin", 0x1B4EC0, 0x400);

const u32 gMonFrontPic_UnownQuestionMark[] = INCBIN_U32("assets/graphics.bin", 0x1B52C0, 0x1BC);
const u32 gMonBackPic_UnownQuestionMark[] = INCBIN_U32("assets/graphics.bin", 0x1B547C, 0x200);
const u8 gMonIcon_UnownQuestionMark[] = INCBIN_U8("assets/graphics.bin", 0x1B567C, 0x400);
// ===== END src/data/graphics/pokemon.h =====
// ===== BEGIN src/data/graphics/trainers.h =====
const u32 gTrainerFrontPic_AquaLeaderArchie[] = INCBIN_U32("assets/graphics.bin", 0x1B5A7C, 0x33C);
const u32 gTrainerPalette_AquaLeaderArchie[] = INCBIN_U32("assets/graphics.bin", 0x1B5DB8, 0x28);

const u32 gTrainerFrontPic_AquaGruntM[] = INCBIN_U32("assets/graphics.bin", 0x1B5DE0, 0x360);
const u32 gTrainerPalette_AquaGruntM[] = INCBIN_U32("assets/graphics.bin", 0x1B6140, 0x28);

const u32 gTrainerFrontPic_AquaGruntF[] = INCBIN_U32("assets/graphics.bin", 0x1B6168, 0x33C);
const u32 gTrainerPalette_AquaGruntF[] = INCBIN_U32("assets/graphics.bin", 0x1B64A4, 0x28);

const u32 gTrainerFrontPic_RSAromaLady[] = INCBIN_U32("assets/graphics.bin", 0x1B64CC, 0x2C4);
const u32 gTrainerPalette_RSAromaLady[] = INCBIN_U32("assets/graphics.bin", 0x1B6790, 0x28);

const u32 gTrainerFrontPic_RSRuinManiac[] = INCBIN_U32("assets/graphics.bin", 0x1B67B8, 0x39C);
const u32 gTrainerPalette_RSRuinManiac[] = INCBIN_U32("assets/graphics.bin", 0x1B6B54, 0x28);

const u32 gTrainerFrontPic_Interviewer[] = INCBIN_U32("assets/graphics.bin", 0x1B6B7C, 0x4A4);
const u32 gTrainerPalette_Interviewer[] = INCBIN_U32("assets/graphics.bin", 0x1B7020, 0x28);

const u32 gTrainerFrontPic_RSTuberF[] = INCBIN_U32("assets/graphics.bin", 0x1B7048, 0x2A4);
const u32 gTrainerPalette_RSTuberF[] = INCBIN_U32("assets/graphics.bin", 0x1B72EC, 0x28);

const u32 gTrainerFrontPic_TuberM[] = INCBIN_U32("assets/graphics.bin", 0x1B7314, 0x28C);
const u32 gTrainerPalette_TuberM[] = INCBIN_U32("assets/graphics.bin", 0x1B75A0, 0x28);

const u32 gTrainerFrontPic_RSCooltrainerM[] = INCBIN_U32("assets/graphics.bin", 0x1B75C8, 0x2E8);
const u32 gTrainerPalette_RSCooltrainerM[] = INCBIN_U32("assets/graphics.bin", 0x1B78B0, 0x28);

const u32 gTrainerFrontPic_RSCooltrainerF[] = INCBIN_U32("assets/graphics.bin", 0x1B78D8, 0x314);
const u32 gTrainerPalette_RSCooltrainerF[] = INCBIN_U32("assets/graphics.bin", 0x1B7BEC, 0x28);

const u32 gTrainerFrontPic_HexManiac[] = INCBIN_U32("assets/graphics.bin", 0x1B7C14, 0x36C);
const u32 gTrainerPalette_HexManiac[] = INCBIN_U32("assets/graphics.bin", 0x1B7F80, 0x28);

const u32 gTrainerFrontPic_RSLady[] = INCBIN_U32("assets/graphics.bin", 0x1B7FA8, 0x3B4);
const u32 gTrainerPalette_RSLady[] = INCBIN_U32("assets/graphics.bin", 0x1B835C, 0x28);

const u32 gTrainerFrontPic_RSBeauty[] = INCBIN_U32("assets/graphics.bin", 0x1B8384, 0x2E8);
const u32 gTrainerPalette_RSBeauty[] = INCBIN_U32("assets/graphics.bin", 0x1B866C, 0x28);

const u32 gTrainerFrontPic_RichBoy[] = INCBIN_U32("assets/graphics.bin", 0x1B8694, 0x2B4);
const u32 gTrainerPalette_RichBoy[] = INCBIN_U32("assets/graphics.bin", 0x1B8948, 0x28);

const u32 gTrainerFrontPic_RSPokeManiac[] = INCBIN_U32("assets/graphics.bin", 0x1B8970, 0x370);
const u32 gTrainerPalette_RSPokeManiac[] = INCBIN_U32("assets/graphics.bin", 0x1B8CE0, 0x28);

const u32 gTrainerFrontPic_RSSwimmerM[] = INCBIN_U32("assets/graphics.bin", 0x1B8D08, 0x2C0);
const u32 gTrainerPalette_RSSwimmerM[] = INCBIN_U32("assets/graphics.bin", 0x1B8FC8, 0x28);

const u32 gTrainerFrontPic_RSBlackBelt[] = INCBIN_U32("assets/graphics.bin", 0x1B8FF0, 0x364);
const u32 gTrainerPalette_RSBlackBelt[] = INCBIN_U32("assets/graphics.bin", 0x1B9354, 0x28);

const u32 gTrainerFrontPic_Guitarist[] = INCBIN_U32("assets/graphics.bin", 0x1B937C, 0x384);
const u32 gTrainerPalette_Guitarist[] = INCBIN_U32("assets/graphics.bin", 0x1B9700, 0x28);

const u32 gTrainerFrontPic_Kindler[] = INCBIN_U32("assets/graphics.bin", 0x1B9728, 0x36C);
const u32 gTrainerPalette_Kindler[] = INCBIN_U32("assets/graphics.bin", 0x1B9A94, 0x28);

const u32 gTrainerFrontPic_RSCamper[] = INCBIN_U32("assets/graphics.bin", 0x1B9ABC, 0x2E8);
const u32 gTrainerPalette_RSCamper[] = INCBIN_U32("assets/graphics.bin", 0x1B9DA4, 0x28);

const u32 gTrainerFrontPic_BugManiac[] = INCBIN_U32("assets/graphics.bin", 0x1B9DCC, 0x450);
const u32 gTrainerPalette_BugManiac[] = INCBIN_U32("assets/graphics.bin", 0x1BA21C, 0x28);

const u32 gTrainerFrontPic_RSPsychicM[] = INCBIN_U32("assets/graphics.bin", 0x1BA244, 0x32C);
const u32 gTrainerPalette_RSPsychicM[] = INCBIN_U32("assets/graphics.bin", 0x1BA570, 0x28);

const u32 gTrainerFrontPic_RSPsychicF[] = INCBIN_U32("assets/graphics.bin", 0x1BA598, 0x328);
const u32 gTrainerPalette_RSPsychicF[] = INCBIN_U32("assets/graphics.bin", 0x1BA8C0, 0x28);

const u32 gTrainerFrontPic_RSGentleman[] = INCBIN_U32("assets/graphics.bin", 0x1BA8E8, 0x300);
const u32 gTrainerPalette_RSGentleman[] = INCBIN_U32("assets/graphics.bin", 0x1BABE8, 0x28);

const u32 gTrainerFrontPic_EliteFourSidney[] = INCBIN_U32("assets/graphics.bin", 0x1BAC10, 0x334);
const u32 gTrainerPalette_EliteFourSidney[] = INCBIN_U32("assets/graphics.bin", 0x1BAF44, 0x28);

const u32 gTrainerFrontPic_EliteFourPhoebe[] = INCBIN_U32("assets/graphics.bin", 0x1BAF6C, 0x300);
const u32 gTrainerPalette_EliteFourPhoebe[] = INCBIN_U32("assets/graphics.bin", 0x1BB26C, 0x28);

const u32 gTrainerFrontPic_LeaderRoxanne[] = INCBIN_U32("assets/graphics.bin", 0x1BB294, 0x2EC);
const u32 gTrainerPalette_LeaderRoxanne[] = INCBIN_U32("assets/graphics.bin", 0x1BB580, 0x28);

const u32 gTrainerFrontPic_LeaderBrawly[] = INCBIN_U32("assets/graphics.bin", 0x1BB5A8, 0x394);
const u32 gTrainerPalette_LeaderBrawly[] = INCBIN_U32("assets/graphics.bin", 0x1BB93C, 0x28);

const u32 gTrainerFrontPic_LeaderTateAndLiza[] = INCBIN_U32("assets/graphics.bin", 0x1BB964, 0x444);
const u32 gTrainerPalette_LeaderTateAndLiza[] = INCBIN_U32("assets/graphics.bin", 0x1BBDA8, 0x28);

const u32 gTrainerFrontPic_SchoolKidM[] = INCBIN_U32("assets/graphics.bin", 0x1BBDD0, 0x2C0);
const u32 gTrainerPalette_SchoolKidM[] = INCBIN_U32("assets/graphics.bin", 0x1BC090, 0x28);

const u32 gTrainerFrontPic_SchoolKidF[] = INCBIN_U32("assets/graphics.bin", 0x1BC0B8, 0x29C);
const u32 gTrainerPalette_SchoolKidF[] = INCBIN_U32("assets/graphics.bin", 0x1BC354, 0x28);

const u32 gTrainerFrontPic_SrAndJr[] = INCBIN_U32("assets/graphics.bin", 0x1BC37C, 0x470);
const u32 gTrainerPalette_SrAndJr[] = INCBIN_U32("assets/graphics.bin", 0x1BC7EC, 0x28);

const u32 gTrainerFrontPic_PokefanM[] = INCBIN_U32("assets/graphics.bin", 0x1BC814, 0x3BC);
const u32 gTrainerPalette_PokefanM[] = INCBIN_U32("assets/graphics.bin", 0x1BCBD0, 0x28);

const u32 gTrainerFrontPic_PokefanF[] = INCBIN_U32("assets/graphics.bin", 0x1BCBF8, 0x3CC);
const u32 gTrainerPalette_PokefanF[] = INCBIN_U32("assets/graphics.bin", 0x1BCFC4, 0x28);

const u32 gTrainerFrontPic_ExpertM[] = INCBIN_U32("assets/graphics.bin", 0x1BCFEC, 0x340);
const u32 gTrainerPalette_ExpertM[] = INCBIN_U32("assets/graphics.bin", 0x1BD32C, 0x28);

const u32 gTrainerFrontPic_ExpertF[] = INCBIN_U32("assets/graphics.bin", 0x1BD354, 0x31C);
const u32 gTrainerPalette_ExpertF[] = INCBIN_U32("assets/graphics.bin", 0x1BD670, 0x28);

const u32 gTrainerFrontPic_RSYoungster[] = INCBIN_U32("assets/graphics.bin", 0x1BD698, 0x2A8);
const u32 gTrainerPalette_RSYoungster[] = INCBIN_U32("assets/graphics.bin", 0x1BD940, 0x28);

const u32 gTrainerFrontPic_ChampionSteven[] = INCBIN_U32("assets/graphics.bin", 0x1BD968, 0x338);
const u32 gTrainerPalette_ChampionSteven[] = INCBIN_U32("assets/graphics.bin", 0x1BDCA0, 0x28);

const u32 gTrainerFrontPic_RSFisherman[] = INCBIN_U32("assets/graphics.bin", 0x1BDCC8, 0x3E4);
const u32 gTrainerPalette_RSFisherman[] = INCBIN_U32("assets/graphics.bin", 0x1BE0AC, 0x28);

const u32 gTrainerFrontPic_CyclingTriathleteM[] = INCBIN_U32("assets/graphics.bin", 0x1BE0D4, 0x410);
const u32 gTrainerPalette_CyclingTriathleteM[] = INCBIN_U32("assets/graphics.bin", 0x1BE4E4, 0x28);

const u32 gTrainerFrontPic_CyclingTriathleteF[] = INCBIN_U32("assets/graphics.bin", 0x1BE50C, 0x40C);
const u32 gTrainerPalette_CyclingTriathleteF[] = INCBIN_U32("assets/graphics.bin", 0x1BE918, 0x28);

const u32 gTrainerFrontPic_RunningTriathleteM[] = INCBIN_U32("assets/graphics.bin", 0x1BE940, 0x2B8);
const u32 gTrainerPalette_RunningTriathleteM[] = INCBIN_U32("assets/graphics.bin", 0x1BEBF8, 0x28);

const u32 gTrainerFrontPic_RunningTriathleteF[] = INCBIN_U32("assets/graphics.bin", 0x1BEC20, 0x2A4);
const u32 gTrainerPalette_RunningTriathleteF[] = INCBIN_U32("assets/graphics.bin", 0x1BEEC4, 0x28);

const u32 gTrainerFrontPic_SwimmingTriathleteM[] = INCBIN_U32("assets/graphics.bin", 0x1BEEEC, 0x32C);
const u32 gTrainerPalette_SwimmingTriathleteM[] = INCBIN_U32("assets/graphics.bin", 0x1BF218, 0x28);

const u32 gTrainerFrontPic_SwimmingTriathleteF[] = INCBIN_U32("assets/graphics.bin", 0x1BF240, 0x2DC);
const u32 gTrainerPalette_SwimmingTriathleteF[] = INCBIN_U32("assets/graphics.bin", 0x1BF51C, 0x28);

const u32 gTrainerFrontPic_DragonTamer[] = INCBIN_U32("assets/graphics.bin", 0x1BF544, 0x354);
const u32 gTrainerPalette_DragonTamer[] = INCBIN_U32("assets/graphics.bin", 0x1BF898, 0x28);

const u32 gTrainerFrontPic_RSBirdKeeper[] = INCBIN_U32("assets/graphics.bin", 0x1BF8C0, 0x338);
const u32 gTrainerPalette_RSBirdKeeper[] = INCBIN_U32("assets/graphics.bin", 0x1BFBF8, 0x28);

const u32 gTrainerFrontPic_NinjaBoy[] = INCBIN_U32("assets/graphics.bin", 0x1BFC20, 0x2DC);
const u32 gTrainerPalette_NinjaBoy[] = INCBIN_U32("assets/graphics.bin", 0x1BFEFC, 0x28);

const u32 gTrainerFrontPic_BattleGirl[] = INCBIN_U32("assets/graphics.bin", 0x1BFF24, 0x320);
const u32 gTrainerPalette_BattleGirl[] = INCBIN_U32("assets/graphics.bin", 0x1C0244, 0x28);

const u32 gTrainerFrontPic_ParasolLady[] = INCBIN_U32("assets/graphics.bin", 0x1C026C, 0x338);
const u32 gTrainerPalette_ParasolLady[] = INCBIN_U32("assets/graphics.bin", 0x1C05A4, 0x28);

const u32 gTrainerFrontPic_RSSwimmerF[] = INCBIN_U32("assets/graphics.bin", 0x1C05CC, 0x2D0);
const u32 gTrainerPalette_RSSwimmerF[] = INCBIN_U32("assets/graphics.bin", 0x1C089C, 0x28);

const u32 gTrainerFrontPic_RSPicnicker[] = INCBIN_U32("assets/graphics.bin", 0x1C08C4, 0x2E0);
const u32 gTrainerPalette_RSPicnicker[] = INCBIN_U32("assets/graphics.bin", 0x1C0BA4, 0x28);

const u32 gTrainerFrontPic_RSTwins[] = INCBIN_U32("assets/graphics.bin", 0x1C0BCC, 0x3C4);
const u32 gTrainerPalette_RSTwins[] = INCBIN_U32("assets/graphics.bin", 0x1C0F90, 0x28);

const u32 gTrainerFrontPic_RSSailor[] = INCBIN_U32("assets/graphics.bin", 0x1C0FB8, 0x3B0);
const u32 gTrainerPalette_RSSailor[] = INCBIN_U32("assets/graphics.bin", 0x1C1368, 0x28);

const u32 gTrainerFrontPic_Collector[] = INCBIN_U32("assets/graphics.bin", 0x1C1390, 0x404);
const u32 gTrainerPalette_Collector[] = INCBIN_U32("assets/graphics.bin", 0x1C1794, 0x28);

const u32 gTrainerFrontPic_Wally[] = INCBIN_U32("assets/graphics.bin", 0x1C17BC, 0x2D0);
const u32 gTrainerPalette_Wally[] = INCBIN_U32("assets/graphics.bin", 0x1C1A8C, 0x28);

const u32 gTrainerFrontPic_RSBrendan1[] = INCBIN_U32("assets/graphics.bin", 0x1C1AB4, 0x314);
const u32 gTrainerPalette_RSBrendan1[] = INCBIN_U32("assets/graphics.bin", 0x1C1DC8, 0x28);

const u32 gTrainerFrontPic_RSMay1[] = INCBIN_U32("assets/graphics.bin", 0x1C1DF0, 0x300);
const u32 gTrainerPalette_RSMay1[] = INCBIN_U32("assets/graphics.bin", 0x1C20F0, 0x28);

const u32 gTrainerFrontPic_RSPokemonBreederM[] = INCBIN_U32("assets/graphics.bin", 0x1C2118, 0x330);
const u32 gTrainerPalette_RSPokemonBreederM[] = INCBIN_U32("assets/graphics.bin", 0x1C2448, 0x28);

const u32 gTrainerFrontPic_RSPokemonBreederF[] = INCBIN_U32("assets/graphics.bin", 0x1C2470, 0x334);
const u32 gTrainerPalette_RSPokemonBreederF[] = INCBIN_U32("assets/graphics.bin", 0x1C27A4, 0x28);

const u32 gTrainerFrontPic_RSPokemonRangerM[] = INCBIN_U32("assets/graphics.bin", 0x1C27CC, 0x348);
const u32 gTrainerPalette_RSPokemonRangerM[] = INCBIN_U32("assets/graphics.bin", 0x1C2B14, 0x28);

const u32 gTrainerFrontPic_RSPokemonRangerF[] = INCBIN_U32("assets/graphics.bin", 0x1C2B3C, 0x334);
const u32 gTrainerPalette_RSPokemonRangerF[] = INCBIN_U32("assets/graphics.bin", 0x1C2E70, 0x28);

const u32 gTrainerFrontPic_MagmaLeaderMaxie[] = INCBIN_U32("assets/graphics.bin", 0x1C2E98, 0x2F4);
const u32 gTrainerPalette_MagmaLeaderMaxie[] = INCBIN_U32("assets/graphics.bin", 0x1C318C, 0x28);

const u32 gTrainerFrontPic_MagmaGruntM[] = INCBIN_U32("assets/graphics.bin", 0x1C31B4, 0x380);
const u32 gTrainerPalette_MagmaGruntM[] = INCBIN_U32("assets/graphics.bin", 0x1C3534, 0x28);

const u32 gTrainerFrontPic_MagmaGruntF[] = INCBIN_U32("assets/graphics.bin", 0x1C355C, 0x38C);
const u32 gTrainerPalette_MagmaGruntF[] = INCBIN_U32("assets/graphics.bin", 0x1C38E8, 0x28);

const u32 gTrainerFrontPic_RSLass[] = INCBIN_U32("assets/graphics.bin", 0x1C3910, 0x2D8);
const u32 gTrainerPalette_RSLass[] = INCBIN_U32("assets/graphics.bin", 0x1C3BE8, 0x28);

const u32 gTrainerFrontPic_RSBugCatcher[] = INCBIN_U32("assets/graphics.bin", 0x1C3C10, 0x32C);
const u32 gTrainerPalette_RSBugCatcher[] = INCBIN_U32("assets/graphics.bin", 0x1C3F3C, 0x28);

const u32 gTrainerFrontPic_RSHiker[] = INCBIN_U32("assets/graphics.bin", 0x1C3F64, 0x480);
const u32 gTrainerPalette_RSHiker[] = INCBIN_U32("assets/graphics.bin", 0x1C43E4, 0x28);

const u32 gTrainerFrontPic_RSYoungCouple[] = INCBIN_U32("assets/graphics.bin", 0x1C440C, 0x3C0);
const u32 gTrainerPalette_RSYoungCouple[] = INCBIN_U32("assets/graphics.bin", 0x1C47CC, 0x28);

const u32 gTrainerFrontPic_OldCouple[] = INCBIN_U32("assets/graphics.bin", 0x1C47F4, 0x510);
const u32 gTrainerPalette_OldCouple[] = INCBIN_U32("assets/graphics.bin", 0x1C4D04, 0x28);

const u32 gTrainerFrontPic_RSSisAndBro[] = INCBIN_U32("assets/graphics.bin", 0x1C4D2C, 0x44C);
const u32 gTrainerPalette_RSSisAndBro[] = INCBIN_U32("assets/graphics.bin", 0x1C5178, 0x28);

const u32 gTrainerFrontPic_AquaAdminM[] = INCBIN_U32("assets/graphics.bin", 0x1C51A0, 0x3B4);
const u32 gTrainerPalette_AquaAdminM[] = INCBIN_U32("assets/graphics.bin", 0x1C5554, 0x28);

const u32 gTrainerFrontPic_AquaAdminF[] = INCBIN_U32("assets/graphics.bin", 0x1C557C, 0x3C4);
const u32 gTrainerPalette_AquaAdminF[] = INCBIN_U32("assets/graphics.bin", 0x1C5940, 0x28);

const u32 gTrainerFrontPic_MagmaAdminM[] = INCBIN_U32("assets/graphics.bin", 0x1C5968, 0x3D8);
const u32 gTrainerPalette_MagmaAdminM[] = INCBIN_U32("assets/graphics.bin", 0x1C5D40, 0x28);

const u32 gTrainerFrontPic_MagmaAdminF[] = INCBIN_U32("assets/graphics.bin", 0x1C5D68, 0x3B0);
const u32 gTrainerPalette_MagmaAdminF[] = INCBIN_U32("assets/graphics.bin", 0x1C6118, 0x28);

const u32 gTrainerFrontPic_LeaderWattson[] = INCBIN_U32("assets/graphics.bin", 0x1C6140, 0x348);
const u32 gTrainerPalette_LeaderWattson[] = INCBIN_U32("assets/graphics.bin", 0x1C6488, 0x28);

const u32 gTrainerFrontPic_LeaderFlannery[] = INCBIN_U32("assets/graphics.bin", 0x1C64B0, 0x380);
const u32 gTrainerPalette_LeaderFlannery[] = INCBIN_U32("assets/graphics.bin", 0x1C6830, 0x28);

const u32 gTrainerFrontPic_LeaderNorman[] = INCBIN_U32("assets/graphics.bin", 0x1C6858, 0x33C);
const u32 gTrainerPalette_LeaderNorman[] = INCBIN_U32("assets/graphics.bin", 0x1C6B94, 0x28);

const u32 gTrainerFrontPic_LeaderWinona[] = INCBIN_U32("assets/graphics.bin", 0x1C6BBC, 0x380);
const u32 gTrainerPalette_LeaderWinona[] = INCBIN_U32("assets/graphics.bin", 0x1C6F3C, 0x28);

const u32 gTrainerFrontPic_LeaderWallace[] = INCBIN_U32("assets/graphics.bin", 0x1C6F64, 0x378);
const u32 gTrainerPalette_LeaderWallace[] = INCBIN_U32("assets/graphics.bin", 0x1C72DC, 0x28);

const u32 gTrainerFrontPic_EliteFourGlacia[] = INCBIN_U32("assets/graphics.bin", 0x1C7304, 0x384);
const u32 gTrainerPalette_EliteFourGlacia[] = INCBIN_U32("assets/graphics.bin", 0x1C7688, 0x28);

const u32 gTrainerFrontPic_EliteFourDrake[] = INCBIN_U32("assets/graphics.bin", 0x1C76B0, 0x3A8);
const u32 gTrainerPalette_EliteFourDrake[] = INCBIN_U32("assets/graphics.bin", 0x1C7A58, 0x28);

const u32 gTrainerFrontPic_Youngster[] = INCBIN_U32("assets/graphics.bin", 0x1C7A80, 0x2A0);
const u32 gTrainerPalette_Youngster[] = INCBIN_U32("assets/graphics.bin", 0x1C7D20, 0x28);

const u32 gTrainerFrontPic_BugCatcher[] = INCBIN_U32("assets/graphics.bin", 0x1C7D48, 0x348);
const u32 gTrainerPalette_BugCatcher[] = INCBIN_U32("assets/graphics.bin", 0x1C8090, 0x28);

const u32 gTrainerFrontPic_Lass[] = INCBIN_U32("assets/graphics.bin", 0x1C80B8, 0x2EC);
const u32 gTrainerPalette_Lass[] = INCBIN_U32("assets/graphics.bin", 0x1C83A4, 0x28);

const u32 gTrainerFrontPic_Sailor[] = INCBIN_U32("assets/graphics.bin", 0x1C83CC, 0x320);
const u32 gTrainerPalette_Sailor[] = INCBIN_U32("assets/graphics.bin", 0x1C86EC, 0x28);

const u32 gTrainerFrontPic_Camper[] = INCBIN_U32("assets/graphics.bin", 0x1C8714, 0x2E0);
const u32 gTrainerPalette_Camper[] = INCBIN_U32("assets/graphics.bin", 0x1C89F4, 0x28);

const u32 gTrainerFrontPic_Picnicker[] = INCBIN_U32("assets/graphics.bin", 0x1C8A1C, 0x2E8);
const u32 gTrainerPalette_Picnicker[] = INCBIN_U32("assets/graphics.bin", 0x1C8D04, 0x28);

const u32 gTrainerFrontPic_PokeManiac[] = INCBIN_U32("assets/graphics.bin", 0x1C8D2C, 0x3BC);
const u32 gTrainerPalette_PokeManiac[] = INCBIN_U32("assets/graphics.bin", 0x1C90E8, 0x28);

const u32 gTrainerFrontPic_SuperNerd[] = INCBIN_U32("assets/graphics.bin", 0x1C9110, 0x318);
const u32 gTrainerPalette_SuperNerd[] = INCBIN_U32("assets/graphics.bin", 0x1C9428, 0x28);

const u32 gTrainerFrontPic_Hiker[] = INCBIN_U32("assets/graphics.bin", 0x1C9450, 0x470);
const u32 gTrainerPalette_Hiker[] = INCBIN_U32("assets/graphics.bin", 0x1C98C0, 0x28);

const u32 gTrainerFrontPic_Biker[] = INCBIN_U32("assets/graphics.bin", 0x1C98E8, 0x568);
const u32 gTrainerPalette_Biker[] = INCBIN_U32("assets/graphics.bin", 0x1C9E50, 0x28);

const u32 gTrainerFrontPic_Burglar[] = INCBIN_U32("assets/graphics.bin", 0x1C9E78, 0x34C);
const u32 gTrainerPalette_Burglar[] = INCBIN_U32("assets/graphics.bin", 0x1CA1C4, 0x28);

const u32 gTrainerFrontPic_Engineer[] = INCBIN_U32("assets/graphics.bin", 0x1CA1EC, 0x40C);
const u32 gTrainerPalette_Engineer[] = INCBIN_U32("assets/graphics.bin", 0x1CA5F8, 0x28);

const u32 gTrainerFrontPic_Fisherman[] = INCBIN_U32("assets/graphics.bin", 0x1CA620, 0x3AC);
const u32 gTrainerPalette_Fisherman[] = INCBIN_U32("assets/graphics.bin", 0x1CA9CC, 0x28);

const u32 gTrainerFrontPic_SwimmerM[] = INCBIN_U32("assets/graphics.bin", 0x1CA9F4, 0x2D8);
const u32 gTrainerPalette_SwimmerM[] = INCBIN_U32("assets/graphics.bin", 0x1CACCC, 0x28);

const u32 gTrainerFrontPic_CueBall[] = INCBIN_U32("assets/graphics.bin", 0x1CACF4, 0x5C8);
const u32 gTrainerPalette_CueBall[] = INCBIN_U32("assets/graphics.bin", 0x1CB2BC, 0x28);

const u32 gTrainerFrontPic_Gamer[] = INCBIN_U32("assets/graphics.bin", 0x1CB2E4, 0x394);
const u32 gTrainerPalette_Gamer[] = INCBIN_U32("assets/graphics.bin", 0x1CB678, 0x28);

const u32 gTrainerFrontPic_Beauty[] = INCBIN_U32("assets/graphics.bin", 0x1CB6A0, 0x35C);
const u32 gTrainerPalette_Beauty[] = INCBIN_U32("assets/graphics.bin", 0x1CB9FC, 0x28);

const u32 gTrainerFrontPic_SwimmerF[] = INCBIN_U32("assets/graphics.bin", 0x1CBA24, 0x2EC);
const u32 gTrainerPalette_SwimmerF[] = INCBIN_U32("assets/graphics.bin", 0x1CBD10, 0x28);

const u32 gTrainerFrontPic_PsychicM[] = INCBIN_U32("assets/graphics.bin", 0x1CBD38, 0x360);
const u32 gTrainerPalette_PsychicM[] = INCBIN_U32("assets/graphics.bin", 0x1CC098, 0x28);

const u32 gTrainerFrontPic_Rocker[] = INCBIN_U32("assets/graphics.bin", 0x1CC0C0, 0x45C);
const u32 gTrainerPalette_Rocker[] = INCBIN_U32("assets/graphics.bin", 0x1CC51C, 0x28);

const u32 gTrainerFrontPic_Juggler[] = INCBIN_U32("assets/graphics.bin", 0x1CC544, 0x43C);
const u32 gTrainerPalette_Juggler[] = INCBIN_U32("assets/graphics.bin", 0x1CC980, 0x28);

const u32 gTrainerFrontPic_Tamer[] = INCBIN_U32("assets/graphics.bin", 0x1CC9A8, 0x3B4);
const u32 gTrainerPalette_Tamer[] = INCBIN_U32("assets/graphics.bin", 0x1CCD5C, 0x28);

const u32 gTrainerFrontPic_BirdKeeper[] = INCBIN_U32("assets/graphics.bin", 0x1CCD84, 0x3C4);
const u32 gTrainerPalette_BirdKeeper[] = INCBIN_U32("assets/graphics.bin", 0x1CD148, 0x28);

const u32 gTrainerFrontPic_BlackBelt[] = INCBIN_U32("assets/graphics.bin", 0x1CD170, 0x420);
const u32 gTrainerPalette_BlackBelt[] = INCBIN_U32("assets/graphics.bin", 0x1CD590, 0x28);

const u32 gTrainerFrontPic_RivalEarly[] = INCBIN_U32("assets/graphics.bin", 0x1CD5B8, 0x2B8);
const u32 gTrainerPalette_RivalEarly[] = INCBIN_U32("assets/graphics.bin", 0x1CD870, 0x28);

const u32 gTrainerFrontPic_Scientist[] = INCBIN_U32("assets/graphics.bin", 0x1CD898, 0x3DC);
const u32 gTrainerPalette_Scientist[] = INCBIN_U32("assets/graphics.bin", 0x1CDC74, 0x28);

const u32 gTrainerFrontPic_LeaderGiovanni[] = INCBIN_U32("assets/graphics.bin", 0x1CDC9C, 0x310);
const u32 gTrainerPalette_LeaderGiovanni[] = INCBIN_U32("assets/graphics.bin", 0x1CDFAC, 0x28);

const u32 gTrainerFrontPic_RocketGruntM[] = INCBIN_U32("assets/graphics.bin", 0x1CDFD4, 0x334);
const u32 gTrainerPalette_RocketGruntM[] = INCBIN_U32("assets/graphics.bin", 0x1CE308, 0x28);

const u32 gTrainerFrontPic_CooltrainerM[] = INCBIN_U32("assets/graphics.bin", 0x1CE330, 0x2D0);
const u32 gTrainerPalette_CooltrainerM[] = INCBIN_U32("assets/graphics.bin", 0x1CE600, 0x28);

const u32 gTrainerFrontPic_CooltrainerF[] = INCBIN_U32("assets/graphics.bin", 0x1CE628, 0x318);
const u32 gTrainerPalette_CooltrainerF[] = INCBIN_U32("assets/graphics.bin", 0x1CE940, 0x28);

const u32 gTrainerFrontPic_EliteFourLorelei[] = INCBIN_U32("assets/graphics.bin", 0x1CE968, 0x32C);
const u32 gTrainerPalette_EliteFourLorelei[] = INCBIN_U32("assets/graphics.bin", 0x1CEC94, 0x28);

const u32 gTrainerFrontPic_EliteFourBruno[] = INCBIN_U32("assets/graphics.bin", 0x1CECBC, 0x44C);
const u32 gTrainerPalette_EliteFourBruno[] = INCBIN_U32("assets/graphics.bin", 0x1CF108, 0x28);

const u32 gTrainerFrontPic_EliteFourAgatha[] = INCBIN_U32("assets/graphics.bin", 0x1CF130, 0x31C);
const u32 gTrainerPalette_EliteFourAgatha[] = INCBIN_U32("assets/graphics.bin", 0x1CF44C, 0x28);

const u32 gTrainerFrontPic_EliteFourLance[] = INCBIN_U32("assets/graphics.bin", 0x1CF474, 0x3C8);
const u32 gTrainerPalette_EliteFourLance[] = INCBIN_U32("assets/graphics.bin", 0x1CF83C, 0x28);

const u32 gTrainerFrontPic_LeaderBrock[] = INCBIN_U32("assets/graphics.bin", 0x1CF864, 0x34C);
const u32 gTrainerPalette_LeaderBrock[] = INCBIN_U32("assets/graphics.bin", 0x1CFBB0, 0x28);

const u32 gTrainerFrontPic_LeaderMisty[] = INCBIN_U32("assets/graphics.bin", 0x1CFBD8, 0x300);
const u32 gTrainerPalette_LeaderMisty[] = INCBIN_U32("assets/graphics.bin", 0x1CFED8, 0x28);

const u32 gTrainerFrontPic_LeaderLtSurge[] = INCBIN_U32("assets/graphics.bin", 0x1CFF00, 0x390);
const u32 gTrainerPalette_LeaderLtSurge[] = INCBIN_U32("assets/graphics.bin", 0x1D0290, 0x28);

const u32 gTrainerFrontPic_LeaderErika[] = INCBIN_U32("assets/graphics.bin", 0x1D02B8, 0x2F4);
const u32 gTrainerPalette_LeaderErika[] = INCBIN_U32("assets/graphics.bin", 0x1D05AC, 0x28);

const u32 gTrainerFrontPic_LeaderKoga[] = INCBIN_U32("assets/graphics.bin", 0x1D05D4, 0x368);
const u32 gTrainerPalette_LeaderKoga[] = INCBIN_U32("assets/graphics.bin", 0x1D093C, 0x28);

const u32 gTrainerFrontPic_LeaderBlaine[] = INCBIN_U32("assets/graphics.bin", 0x1D0964, 0x40C);
const u32 gTrainerPalette_LeaderBlaine[] = INCBIN_U32("assets/graphics.bin", 0x1D0D70, 0x28);

const u32 gTrainerFrontPic_LeaderSabrina[] = INCBIN_U32("assets/graphics.bin", 0x1D0D98, 0x308);
const u32 gTrainerPalette_LeaderSabrina[] = INCBIN_U32("assets/graphics.bin", 0x1D10A0, 0x28);

const u32 gTrainerFrontPic_Gentleman[] = INCBIN_U32("assets/graphics.bin", 0x1D10C8, 0x338);
const u32 gTrainerPalette_Gentleman[] = INCBIN_U32("assets/graphics.bin", 0x1D1400, 0x28);

const u32 gTrainerFrontPic_RivalLate[] = INCBIN_U32("assets/graphics.bin", 0x1D1428, 0x2F4);
const u32 gTrainerPalette_RivalLate[] = INCBIN_U32("assets/graphics.bin", 0x1D171C, 0x28);

const u32 gTrainerFrontPic_ChampionRival[] = INCBIN_U32("assets/graphics.bin", 0x1D1744, 0x2FC);
const u32 gTrainerPalette_ChampionRival[] = INCBIN_U32("assets/graphics.bin", 0x1D1A40, 0x28);

const u32 gTrainerFrontPic_Channeler[] = INCBIN_U32("assets/graphics.bin", 0x1D1A68, 0x3D8);
const u32 gTrainerPalette_Channeler[] = INCBIN_U32("assets/graphics.bin", 0x1D1E40, 0x28);

const u32 gTrainerFrontPic_Twins[] = INCBIN_U32("assets/graphics.bin", 0x1D1E68, 0x350);
const u32 gTrainerPalette_Twins[] = INCBIN_U32("assets/graphics.bin", 0x1D21B8, 0x28);

const u32 gTrainerFrontPic_CoolCouple[] = INCBIN_U32("assets/graphics.bin", 0x1D21E0, 0x4E0);
const u32 gTrainerPalette_CoolCouple[] = INCBIN_U32("assets/graphics.bin", 0x1D26C0, 0x28);

const u32 gTrainerFrontPic_YoungCouple[] = INCBIN_U32("assets/graphics.bin", 0x1D26E8, 0x44C);
const u32 gTrainerPalette_YoungCouple[] = INCBIN_U32("assets/graphics.bin", 0x1D2B34, 0x28);

const u32 gTrainerFrontPic_CrushKin[] = INCBIN_U32("assets/graphics.bin", 0x1D2B5C, 0x5A0);
const u32 gTrainerPalette_CrushKin[] = INCBIN_U32("assets/graphics.bin", 0x1D30FC, 0x28);

const u32 gTrainerFrontPic_SisAndBro[] = INCBIN_U32("assets/graphics.bin", 0x1D3124, 0x460);
const u32 gTrainerPalette_SisAndBro[] = INCBIN_U32("assets/graphics.bin", 0x1D3584, 0x28);

const u32 gTrainerFrontPic_ProfessorOak[] = INCBIN_U32("assets/graphics.bin", 0x1D35AC, 0x36C);
const u32 gTrainerPalette_ProfessorOak[] = INCBIN_U32("assets/graphics.bin", 0x1D3918, 0x28);

const u32 gTrainerFrontPic_RSBrendan2[] = INCBIN_U32("assets/graphics.bin", 0x1C1AB4, 0x314);
const u32 gTrainerPalette_RSBrendan2[] = INCBIN_U32("assets/graphics.bin", 0x1C1DC8, 0x28);

const u32 gTrainerFrontPic_RSMay2[] = INCBIN_U32("assets/graphics.bin", 0x1C1DF0, 0x300);
const u32 gTrainerPalette_RSMay2[] = INCBIN_U32("assets/graphics.bin", 0x1C20F0, 0x28);

const u32 gTrainerFrontPic_Red[] = INCBIN_U32("assets/graphics.bin", 0x1D3940, 0x30C);
const u32 gTrainerPalette_Red[] = INCBIN_U32("assets/graphics.bin", 0x1D3C4C, 0x28);

const u32 gTrainerFrontPic_Leaf[] = INCBIN_U32("assets/graphics.bin", 0x1D3C74, 0x33C);
const u32 gTrainerPalette_Leaf[] = INCBIN_U32("assets/graphics.bin", 0x1D3FB0, 0x28);

const u32 gTrainerFrontPic_RocketGruntF[] = INCBIN_U32("assets/graphics.bin", 0x1D3FD8, 0x318);
const u32 gTrainerPalette_RocketGruntF[] = INCBIN_U32("assets/graphics.bin", 0x1D42F0, 0x28);

const u32 gTrainerFrontPic_PsychicF[] = INCBIN_U32("assets/graphics.bin", 0x1D4318, 0x3A0);
const u32 gTrainerPalette_PsychicF[] = INCBIN_U32("assets/graphics.bin", 0x1D46B8, 0x28);

const u32 gTrainerFrontPic_CrushGirl[] = INCBIN_U32("assets/graphics.bin", 0x1D46E0, 0x30C);
const u32 gTrainerPalette_CrushGirl[] = INCBIN_U32("assets/graphics.bin", 0x1D49EC, 0x28);

const u32 gTrainerFrontPic_TuberF[] = INCBIN_U32("assets/graphics.bin", 0x1D4A14, 0x304);
const u32 gTrainerPalette_TuberF[] = INCBIN_U32("assets/graphics.bin", 0x1D4D18, 0x28);

const u32 gTrainerFrontPic_PokemonBreeder[] = INCBIN_U32("assets/graphics.bin", 0x1D4D40, 0x340);
const u32 gTrainerPalette_PokemonBreeder[] = INCBIN_U32("assets/graphics.bin", 0x1D5080, 0x28);

const u32 gTrainerFrontPic_PokemonRangerM[] = INCBIN_U32("assets/graphics.bin", 0x1D50A8, 0x360);
const u32 gTrainerPalette_PokemonRangerM[] = INCBIN_U32("assets/graphics.bin", 0x1D5408, 0x28);

const u32 gTrainerFrontPic_PokemonRangerF[] = INCBIN_U32("assets/graphics.bin", 0x1D5430, 0x334);
const u32 gTrainerPalette_PokemonRangerF[] = INCBIN_U32("assets/graphics.bin", 0x1D5764, 0x28);

const u32 gTrainerFrontPic_AromaLady[] = INCBIN_U32("assets/graphics.bin", 0x1D578C, 0x350);
const u32 gTrainerPalette_AromaLady[] = INCBIN_U32("assets/graphics.bin", 0x1D5ADC, 0x28);

const u32 gTrainerFrontPic_RuinManiac[] = INCBIN_U32("assets/graphics.bin", 0x1D5B04, 0x40C);
const u32 gTrainerPalette_RuinManiac[] = INCBIN_U32("assets/graphics.bin", 0x1D5F10, 0x28);

const u32 gTrainerFrontPic_Lady[] = INCBIN_U32("assets/graphics.bin", 0x1D5F38, 0x328);
const u32 gTrainerPalette_Lady[] = INCBIN_U32("assets/graphics.bin", 0x1D6260, 0x28);

const u32 gTrainerFrontPic_Painter[] = INCBIN_U32("assets/graphics.bin", 0x1D6288, 0x2CC);
const u32 gTrainerPalette_Painter[] = INCBIN_U32("assets/graphics.bin", 0x1D6554, 0x28);

const u8 gTrainerBackPic_Red[] = INCBIN_U8("assets/graphics.bin", 0x1D657C, 0x2800);
const u8 gTrainerBackPic_Leaf[] = INCBIN_U8("assets/graphics.bin", 0x1D8D7C, 0x2800);
const u8 gTrainerBackPic_Pokedude[] = INCBIN_U8("assets/graphics.bin", 0x1DB57C, 0x2000);
const u8 gTrainerBackPic_OldMan[] = INCBIN_U8("assets/graphics.bin", 0x1DD57C, 0x2000);

const u8 gTrainerBackPic_RSBrendan[] = INCBIN_U8("assets/graphics.bin", 0x1DF57C, 0x2000);
const u8 gTrainerBackPic_RSMay[] = INCBIN_U8("assets/graphics.bin", 0x1E157C, 0x2000);

const u32 gTrainerPalette_RedBackPic[] = INCBIN_U32("assets/graphics.bin", 0x1E357C, 0x28);
const u32 gTrainerPalette_LeafBackPic[] = INCBIN_U32("assets/graphics.bin", 0x1E35A4, 0x28);
const u32 gTrainerPalette_PokedudeBackPic[] = INCBIN_U32("assets/graphics.bin", 0x1E35CC, 0x28);
const u32 gTrainerPalette_OldManBackPic[] = INCBIN_U32("assets/graphics.bin", 0x1E35F4, 0x28);
// ===== END src/data/graphics/trainers.h =====

const u8 gMonIcon_QuestionMark[] = INCBIN_U8("assets/graphics.bin", 0x1E361C, 0x400);
const u8 gMonFootprint_QuestionMark[] = INCBIN_U8("assets/graphics.bin", 0x1E3A1C, 0x20);

const u32 gFile_graphics_battle_transitions_vs_frame_sheet[] = INCBIN_U32("assets/graphics.bin", 0x1E3A3C, 0xE8);
const u32 gFile_graphics_battle_transitions_vs_frame_tilemap[] = INCBIN_U32("assets/graphics.bin", 0x1E3B24, 0x10C);
const u32 gFile_graphics_battle_transitions_vs_frame_palette[] = INCBIN_U32("assets/graphics.bin", 0x1E3C30, 0x28);

const u32 gVsLettersGfx[] = INCBIN_U32("assets/graphics.bin", 0x1E3C58, 0x210);

// ===== BEGIN src/data/graphics/battle_terrain_unused.h =====

// All graphics in this file go completely unused.

const u32 gUnusedBattleTerrain_Plain_Palette[] = INCBIN_U32("assets/graphics.bin", 0x1E3E68, 0x3C);

const u32 gUnusedBattleTerrain_Building_Tiles_Sheet[] = INCBIN_U32("assets/graphics.bin", 0x1E3EA4, 0x5AC);

const u32 gUnusedBattleTerrain_Stadium_Battle_Frontier_Palette[] = INCBIN_U32("assets/graphics.bin", 0x1E4450, 0x3C);

const u32 gUnusedBattleTerrain_Building_Map_Tilemap[] = INCBIN_U32("assets/graphics.bin", 0x1E448C, 0x2B0);

const u32 gUnusedBattleTerrain_Stadium_Tiles_Sheet[] = INCBIN_U32("assets/graphics.bin", 0x1E473C, 0x608);
const u32 gUnusedBattleTerrain_Stadium_Map_Tilemap[] = INCBIN_U32("assets/graphics.bin", 0x1E4D44, 0x2B0);

const u32 gUnusedBattleTerrain_Building_Palette[] = INCBIN_U32("assets/graphics.bin", 0x1E4FF4, 0x40);

const u32 gUnusedBattleTerrain_Kyogre_Palette[] = INCBIN_U32("assets/graphics.bin", 0x1E5034, 0x3C);
const u32 gUnusedBattleTerrain_Groudon_Palette[] = INCBIN_U32("assets/graphics.bin", 0x1E5070, 0x58);

const u32 gUnusedBattleTerrain_Building_Palette2[] = INCBIN_U32("assets/graphics.bin", 0x1E50C8, 0x3C);
const u32 gUnusedBattleTerrain_Building_Palette3[] = INCBIN_U32("assets/graphics.bin", 0x1E5104, 0x3C);

const u32 gUnusedBattleTerrain_Stadium_Palette1[] = INCBIN_U32("assets/graphics.bin", 0x1E5140, 0x60);
const u32 gUnusedBattleTerrain_Stadium_Palette2[] = INCBIN_U32("assets/graphics.bin", 0x1E51A0, 0x6C);
const u32 gUnusedBattleTerrain_Stadium_Palette3[] = INCBIN_U32("assets/graphics.bin", 0x1E520C, 0x50);
const u32 gUnusedBattleTerrain_Stadium_Palette4[] = INCBIN_U32("assets/graphics.bin", 0x1E525C, 0x48);
const u32 gUnusedBattleTerrain_Stadium_Palette5[] = INCBIN_U32("assets/graphics.bin", 0x1E52A4, 0x44);
const u32 gUnusedBattleTerrain_Stadium_Palette6[] = INCBIN_U32("assets/graphics.bin", 0x1E52E8, 0x50);
const u32 gUnusedBattleTerrain_Stadium_Palette7[] = INCBIN_U32("assets/graphics.bin", 0x1E5338, 0x3C);

const u32 gUnusedBattleTerrain_Building_Anim_Tiles_Sheet[] = INCBIN_U32("assets/graphics.bin", 0x1E5374, 0x410);
const u32 gUnusedBattleTerrain_Building_Anim_Map_Tilemap[] = INCBIN_U32("assets/graphics.bin", 0x1E5784, 0x124);
// ===== END src/data/graphics/battle_terrain_unused.h =====

const u32 gBattleAnimSpriteGfx_FlyingDirt[] = INCBIN_U32("assets/graphics.bin", 0x1E58A8, 0x16C);

const u32 gFile_graphics_battle_anims_backgrounds_sandstorm_brew_tilemap[] = INCBIN_U32("assets/graphics.bin", 0x1E5A14, 0x17C);
const u32 gFile_graphics_battle_anims_backgrounds_sandstorm_brew_sheet[] = INCBIN_U32("assets/graphics.bin", 0x1E5B90, 0x52C);

const u32 gBattleAnimSpritePal_FlyingDirt[] = INCBIN_U32("assets/graphics.bin", 0x1E60BC, 0x28);

const u32 gBattleAnimSpriteGfx_MetalSoundWaves[] = INCBIN_U32("assets/graphics.bin", 0x1E60E4, 0x1BC);
const u32 gBattleAnimSpritePal_MetalSoundWaves[] = INCBIN_U32("assets/graphics.bin", 0x1E62A0, 0x18);

const u32 gBattleAnimBgImage_Ice[] = INCBIN_U32("assets/graphics.bin", 0x1E62B8, 0x970);
const u32 gBattleAnimBgPalette_Ice[] = INCBIN_U32("assets/graphics.bin", 0x1E6C28, 0x24);
const u32 gBattleAnimBgTilemap_Ice[] = INCBIN_U32("assets/graphics.bin", 0x1E6C4C, 0x1F8);

const u32 gBattleAnimSpriteGfx_IcicleSpear[] = INCBIN_U32("assets/graphics.bin", 0x1E6E44, 0xD4);
const u32 gBattleAnimSpritePal_IcicleSpear[] = INCBIN_U32("assets/graphics.bin", 0x1E6F18, 0x28);

const u32 gContestNextTurnGfx[] = INCBIN_U32("assets/graphics.bin", 0x1E6F40, 0x5C);
const u8 gContestNextTurnNumbersGfx[] = INCBIN_U8("assets/graphics.bin", 0x1E6F9C, 0x80);
const u8 gContestNextTurnRandomGfx[] = INCBIN_U8("assets/graphics.bin", 0x1E701C, 0x20);

const u32 gBattleAnimSpriteGfx_GlowyRedOrb[] = INCBIN_U32("assets/graphics.bin", 0x1E703C, 0x20);
const u32 gBattleAnimSpritePal_GlowyRedOrb[] = INCBIN_U32("assets/graphics.bin", 0x1E705C, 0x18);
const u32 gBattleAnimSpritePal_GlowyGreenOrb[] = INCBIN_U32("assets/graphics.bin", 0x1E7074, 0x18);
const u32 gBattleAnimSpritePal_SleepPowder[] = INCBIN_U32("assets/graphics.bin", 0x1E708C, 0x20);
const u32 gBattleAnimSpritePal_StunSpore[] = INCBIN_U32("assets/graphics.bin", 0x1E70AC, 0x20);

const u32 gContestApplauseGfx[] = INCBIN_U32("assets/graphics.bin", 0x1E70CC, 0x12C);
const u8 gContestApplauseMeterGfx[] = INCBIN_U8("assets/graphics.bin", 0x1E71F8, 0x80);

const u16 gContestNextTurnPal[] = INCBIN_U16("assets/graphics.bin", 0x1E7278, 0x20);

const u32 gBattleAnimSpriteGfx_Splash[] = INCBIN_U32("assets/graphics.bin", 0x1E7298, 0x21C);
const u32 gBattleAnimSpritePal_Splash[] = INCBIN_U32("assets/graphics.bin", 0x1E74B4, 0x24);

const u32 gBattleAnimSpriteGfx_SweatBead[] = INCBIN_U32("assets/graphics.bin", 0x1E74D8, 0x28);

const u32 gBattleAnimSpriteGfx_SafariBait[] = INCBIN_U32("assets/graphics.bin", 0x1E7500, 0x54);
const u32 gBattleAnimSpritePal_SafariBait[] = INCBIN_U32("assets/graphics.bin", 0x1E7554, 0x18);

const u32 gBattleAnimSpriteGfx_Gem1[] = INCBIN_U32("assets/graphics.bin", 0x1E756C, 0x180);
const u32 gBattleAnimSpriteGfx_Gem2[] = INCBIN_U32("assets/graphics.bin", 0x1E76EC, 0x16C);
const u32 gBattleAnimSpriteGfx_Gem3[] = INCBIN_U32("assets/graphics.bin", 0x1E7858, 0x168);

const u32 gBattleAnimSpritePal_Gem1[] = INCBIN_U32("assets/graphics.bin", 0x1E79C0, 0x28);

const u32 gBattleAnimBgImage_InAir[] = INCBIN_U32("assets/graphics.bin", 0x1E79E8, 0x15C);
const u32 gBattleAnimBgPalette_InAir[] = INCBIN_U32("assets/graphics.bin", 0x1E7B44, 0x28);
const u32 gBattleAnimBgTilemap_InAir[] = INCBIN_U32("assets/graphics.bin", 0x1E7B6C, 0x1E8);

const u32 gBattleAnimSpriteGfx_Protect[] = INCBIN_U32("assets/graphics.bin", 0x1E7D54, 0x3FC);
const u32 gBattleAnimSpritePal_Protect[] = INCBIN_U32("assets/graphics.bin", 0x1E8150, 0x20);

const u32 gBattleAnimBgPalette_MuddyWater[] = INCBIN_U32("assets/graphics.bin", 0x1E8170, 0x24);

const u32 gEnemyMonShadow_Gfx[] = INCBIN_U32("assets/graphics.bin", 0x1E8194, 0x30);

const u32 gBattleInterface_PartySummaryBar_Gfx[] = INCBIN_U32("assets/graphics.bin", 0x1E81C4, 0x84);

const u8 gMonIcon_Egg[] = INCBIN_U8("assets/graphics.bin", 0x1E8248, 0x400);

const u32 gBattleAnimBgImage_Ghost[] = INCBIN_U32("assets/graphics.bin", 0x1E8648, 0xCC8);
const u32 gBattleAnimBgPalette_Ghost[] = INCBIN_U32("assets/graphics.bin", 0x1E9310, 0x1C);
const u32 gBattleAnimBgTilemap_Ghost[] = INCBIN_U32("assets/graphics.bin", 0x1E932C, 0x2F4);

const u32 gBattleAnimSpritePal_WhipHit[] = INCBIN_U32("assets/graphics.bin", 0x1E9620, 0x28);

const u32 gBattleAnimBgPalette_SolarBeam[] = INCBIN_U32("assets/graphics.bin", 0x1E9648, 0x28);
const u32 gBattleAnimBgTilemap_SolarBeam[] = INCBIN_U32("assets/graphics.bin", 0x1E9670, 0x4FC); // Unused

const u32 gFile_graphics_berry_blender_center_sheet[] = INCBIN_U32("assets/graphics.bin", 0x1E9B6C, 0x820);

const u32 gFile_graphics_berry_blender_outer_sheet[] = INCBIN_U32("assets/graphics.bin", 0x1EA38C, 0xA34);
const u32 gFile_graphics_berry_blender_outer_map_tilemap[] = INCBIN_U32("assets/graphics.bin", 0x1EADC0, 0x314);

const u32 gBattleAnimBgPalette_Cosmic[] = INCBIN_U32("assets/graphics.bin", 0x1EB0D4, 0x28);
const u32 gBattleAnimBgImage_Cosmic[] = INCBIN_U32("assets/graphics.bin", 0x1EB0FC, 0x260);
const u32 gBattleAnimBgTilemap_Cosmic[] = INCBIN_U32("assets/graphics.bin", 0x1EB35C, 0x13C);

const u32 gBattleAnimSpritePal_SlamHit2[] = INCBIN_U32("assets/graphics.bin", 0x1EB498, 0x28);
const u32 gBattleAnimSpriteGfx_SlamHit2[] = INCBIN_U32("assets/graphics.bin", 0x1EB4C0, 0x3F4);

const u32 gBattleAnimFogTilemap[] = INCBIN_U32("assets/graphics.bin", 0x1EB8B4, 0x178);

const u32 gBattleAnimSpritePal_WeatherBall[] = INCBIN_U32("assets/graphics.bin", 0x1EBA2C, 0x1C);
const u32 gBattleAnimSpriteGfx_WeatherBall[] = INCBIN_U32("assets/graphics.bin", 0x1EBA48, 0x124);

const u32 gBattleAnimBgTilemap_ScaryFacePlayer[] = INCBIN_U32("assets/graphics.bin", 0x1EBB6C, 0x1E4);
const u32 gBattleAnimBgTilemap_ScaryFaceOpponent[] = INCBIN_U32("assets/graphics.bin", 0x1EBD50, 0x1E4);
const u32 gBattleAnimBgTilemap_ScaryFaceContest[] = INCBIN_U32("assets/graphics.bin", 0x1EBF34, 0x1E4);

const u32 gBattleAnimSpriteGfx_Hail[] = INCBIN_U32("assets/graphics.bin", 0x1EC118, 0x40);
const u32 gBattleAnimSpritePal_Hail[] = INCBIN_U32("assets/graphics.bin", 0x1EC158, 0x18);

const u32 gBattleAnimSpriteGfx_GreenSpike[] = INCBIN_U32("assets/graphics.bin", 0x1EC170, 0x40);
const u32 gBattleAnimSpritePal_GreenSpike[] = INCBIN_U32("assets/graphics.bin", 0x1EC1B0, 0x18);
const u32 gBattleAnimSpritePal_WhiteCircleOfLight[] = INCBIN_U32("assets/graphics.bin", 0x1EC1C8, 0x18);
const u32 gBattleAnimSpritePal_GlowyBlueOrb[] = INCBIN_U32("assets/graphics.bin", 0x1EC1E0, 0x18);

const u32 gBattleAnimSpriteGfx_Recycle[] = INCBIN_U32("assets/graphics.bin", 0x1EC1F8, 0x20C);
const u32 gBattleAnimSpritePal_Recycle[] = INCBIN_U32("assets/graphics.bin", 0x1EC404, 0x1C);

const u32 gBattleAnimSpriteGfx_RedParticles[] = INCBIN_U32("assets/graphics.bin", 0x1EC420, 0x4C);
const u32 gBattleAnimSpritePal_RedParticles[] = INCBIN_U32("assets/graphics.bin", 0x1EC46C, 0x1C);

const u32 gBattleAnimSpriteGfx_DirtMound[] = INCBIN_U32("assets/graphics.bin", 0x1EC488, 0x188);
const u32 gBattleAnimSpritePal_DirtMound[] = INCBIN_U32("assets/graphics.bin", 0x1EC610, 0x20);

const u32 gBattleAnimBgImage_Fissure[] = INCBIN_U32("assets/graphics.bin", 0x1EC630, 0x2F4);
const u32 gBattleAnimBgPalette_Fissure[] = INCBIN_U32("assets/graphics.bin", 0x1EC924, 0x1C);
const u32 gBattleAnimBgTilemap_Fissure[] = INCBIN_U32("assets/graphics.bin", 0x1EC940, 0x2EC);

const u32 gBattleAnimSpriteGfx_Bird[] = INCBIN_U32("assets/graphics.bin", 0x1ECC2C, 0x37C);
const u32 gBattleAnimSpritePal_Bird[] = INCBIN_U32("assets/graphics.bin", 0x1ECFA8, 0x1C);

const u32 gBattleAnimSpriteGfx_CrossImpact[] = INCBIN_U32("assets/graphics.bin", 0x1ECFC4, 0xA0);
const u32 gBattleAnimSpritePal_CrossImpact[] = INCBIN_U32("assets/graphics.bin", 0x1ED064, 0x28);

const u32 gBattleAnimBgImage_Surf[] = INCBIN_U32("assets/graphics.bin", 0x1ED08C, 0x1320);
const u32 gBattleAnimBgPalette_Surf[] = INCBIN_U32("assets/graphics.bin", 0x1EE3AC, 0x28);

const u32 gBattleAnimBgTilemap_SurfOpponent[] = INCBIN_U32("assets/graphics.bin", 0x1EE3D4, 0x2D0);
const u32 gBattleAnimBgTilemap_SurfPlayer[] = INCBIN_U32("assets/graphics.bin", 0x1EE6A4, 0x2D4);
const u32 gBattleAnimBgTilemap_SurfContest[] = INCBIN_U32("assets/graphics.bin", 0x1EE978, 0x2F4);

const u32 gBattleAnimSpritePal_Slash2[] = INCBIN_U32("assets/graphics.bin", 0x1EEC6C, 0x28);

const u32 gBattleAnimSpriteGfx_WhiteShadow[] = INCBIN_U32("assets/graphics.bin", 0x1EEC94, 0x114);
const u32 gBattleAnimSpritePal_WhiteShadow[] = INCBIN_U32("assets/graphics.bin", 0x1EEDA8, 0x18);

const u32 gPartyMenuBg_Gfx[] = INCBIN_U32("assets/graphics.bin", 0x1EEDC0, 0x2C8);
const u32 gPartyMenuBg_Pal[] = INCBIN_U32("assets/graphics.bin", 0x1EF088, 0xE8);
const u32 gPartyMenuBg_Tilemap[] = INCBIN_U32("assets/graphics.bin", 0x1EF170, 0x138);

const u32 gPartyMenuPokeball_Gfx[] = INCBIN_U32("assets/graphics.bin", 0x1EF2A8, 0x180);
const u32 gPartyMenuPokeballSmall_Gfx[] = INCBIN_U32("assets/graphics.bin", 0x1EF428, 0x114); //unused
const u32 gPartyMenuPokeball_Pal[] = INCBIN_U32("assets/graphics.bin", 0x1EF53C, 0x24);

const u32 gStatusGfx_Icons[] = INCBIN_U32("assets/graphics.bin", 0x1EF560, 0x204);
const u32 gStatusPal_Icons[] = INCBIN_U32("assets/graphics.bin", 0x1EF764, 0x28);

const u32 gBagBg_Gfx[] = INCBIN_U32("assets/graphics.bin", 0x1EF78C, 0x1F4);
const u32 gBagBg_Tilemap[] = INCBIN_U32("assets/graphics.bin", 0x1EF980, 0x184);
const u32 gBagBg_ItemPC_Tilemap[] = INCBIN_U32("assets/graphics.bin", 0x1EFB04, 0x170);
const u32 gBagBgPalette[] = INCBIN_U32("assets/graphics.bin", 0x1EFC74, 0x50); // palette 1 (Boy + misc Pal)
const u32 gBagBgPalette_FemaleOverride[] = INCBIN_U32("assets/graphics.bin", 0x1EFCC4, 0x28); // palette 2 (Girl)

const u32 gBagMale_Gfx[] = INCBIN_U32("assets/graphics.bin", 0x1EFCEC, 0x790);
const u32 gBagFemale_Gfx[] = INCBIN_U32("assets/graphics.bin", 0x1F047C, 0x7A4);
const u32 gBag_Pal[] = INCBIN_U32("assets/graphics.bin", 0x1F0C20, 0x28);

const u32 gSwapLine_Gfx[] = INCBIN_U32("assets/graphics.bin", 0x1F0C48, 0x40);
const u32 gSwapLine_Pal[] = INCBIN_U32("assets/graphics.bin", 0x1F0C88, 0x10);

const u32 gTMCase_Gfx[] = INCBIN_U32("assets/graphics.bin", 0x1F0C98, 0x44C);
const u32 gTMCaseMenu_Tilemap[] = INCBIN_U32("assets/graphics.bin", 0x1F10E4, 0x14C);
const u32 gTMCase_Tilemap[] = INCBIN_U32("assets/graphics.bin", 0x1F1230, 0x140);
const u32 gTMCaseMenu_Male_Pal[] = INCBIN_U32("assets/graphics.bin", 0x1F1370, 0x70);
const u32 gTMCaseMenu_Female_Pal[] = INCBIN_U32("assets/graphics.bin", 0x1F13E0, 0x70);
const u32 gTMCaseDisc_Gfx[] = INCBIN_U32("assets/graphics.bin", 0x1F1450, 0x190);
const u32 gTMCaseDiscTypes1_Pal[] = INCBIN_U32("assets/graphics.bin", 0x1F15E0, 0x148);
const u32 gTMCaseDiscTypes2_Pal[] = INCBIN_U32("assets/graphics.bin", 0x1F1728, 0x28);

const u8 gItemPcTiles[] = INCBIN_U8("assets/graphics.bin", 0x1F1750, 0x378);
const u32 gItemPcBgPals[] = INCBIN_U32("assets/graphics.bin", 0x1F1AC8, 0x50);
const u8 gItemPcTilemap[] = INCBIN_U8("assets/graphics.bin", 0x1F1B18, 0x1B4);

const u32 gBerryPouchSpriteTiles[] = INCBIN_U32("assets/graphics.bin", 0x1F1CCC, 0x3C4);
const u8 gBerryPouchBgGfx[] = INCBIN_U8("assets/graphics.bin", 0x1F2090, 0x1D4);
const u32 gBerryPouchBgPals[] = INCBIN_U32("assets/graphics.bin", 0x1F2264, 0x50);
const u32 gBerryPouchBgPal0FemaleOverride[] = INCBIN_U32("assets/graphics.bin", 0x1F22B4, 0x28);
const u32 gBerryPouchSpritePalette[] = INCBIN_U32("assets/graphics.bin", 0x1F22DC, 0x28);
const u8 gBerryPouchBg1Tilemap[] = INCBIN_U8("assets/graphics.bin", 0x1F2304, 0x184);

const u32 gBuyMenuFrame_Gfx[] = INCBIN_U32("assets/graphics.bin", 0x1F2488, 0x134);
const u32 gBuyMenuFrame_Tilemap[] = INCBIN_U32("assets/graphics.bin", 0x1F25BC, 0x13C);
const u32 gBuyMenuFrame_TmHmTilemap[] = INCBIN_U32("assets/graphics.bin", 0x1F26F8, 0x138);
const u32 gBuyMenuFrame_Pal[] = INCBIN_U32("assets/graphics.bin", 0x1F2830, 0x38);

const u8 gTeachyTv_Border_Gfx[] = INCBIN_U8("assets/graphics.bin", 0x1F2868, 0x98); // Unused
const u8 gTeachyTv_Gfx[] = INCBIN_U8("assets/graphics.bin", 0x1F2900, 0x9A8);
const u8 gTeachyTvScreen_Tilemap[] = INCBIN_U8("assets/graphics.bin", 0x1F32A8, 0x184);
const u8 gTeachyTvTitle_Tilemap[] = INCBIN_U8("assets/graphics.bin", 0x1F342C, 0x22C);
const u32 gTeachyTv_Pal[] = INCBIN_U32("assets/graphics.bin", 0x1F3658, 0x78);

const u32 gUnusedGrayPalette[] = INCBIN_U32("assets/graphics.bin", 0x1F36D0, 0x18);

// ===== BEGIN src/data/graphics/items.h =====
const u32 gItemIcon_QuestionMark[] = INCBIN_U32("assets/graphics.bin", 0x1F36E8, 0x78);
const u32 gItemIconPalette_QuestionMark[] = INCBIN_U32("assets/graphics.bin", 0x1F3760, 0x14);

const u32 gItemIcon_ReturnToFieldArrow[] = INCBIN_U32("assets/graphics.bin", 0x1F3774, 0x88);
const u32 gItemIconPalette_ReturnToFieldArrow[] = INCBIN_U32("assets/graphics.bin", 0x1F37FC, 0x18);

// Pokeballs

const u32 gItemIcon_MasterBall[] = INCBIN_U32("assets/graphics.bin", 0x1F3814, 0xD0);
const u32 gItemIconPalette_MasterBall[] = INCBIN_U32("assets/graphics.bin", 0x1F38E4, 0x28);

const u32 gItemIcon_UltraBall[] = INCBIN_U32("assets/graphics.bin", 0x1F390C, 0xC0);
const u32 gItemIconPalette_UltraBall[] = INCBIN_U32("assets/graphics.bin", 0x1F39CC, 0x28);

const u32 gItemIcon_GreatBall[] = INCBIN_U32("assets/graphics.bin", 0x1F39F4, 0xD0);
const u32 gItemIconPalette_GreatBall[] = INCBIN_U32("assets/graphics.bin", 0x1F3AC4, 0x28);

const u32 gItemIcon_PokeBall[] = INCBIN_U32("assets/graphics.bin", 0x1F3AEC, 0xB0);
const u32 gItemIconPalette_PokeBall[] = INCBIN_U32("assets/graphics.bin", 0x1F3B9C, 0x24);

const u32 gItemIcon_SafariBall[] = INCBIN_U32("assets/graphics.bin", 0x1F3BC0, 0xD0);
const u32 gItemIconPalette_SafariBall[] = INCBIN_U32("assets/graphics.bin", 0x1F3C90, 0x28);

const u32 gItemIcon_NetBall[] = INCBIN_U32("assets/graphics.bin", 0x1F3CB8, 0xD4);
const u32 gItemIconPalette_NetBall[] = INCBIN_U32("assets/graphics.bin", 0x1F3D8C, 0x24);

const u32 gItemIcon_DiveBall[] = INCBIN_U32("assets/graphics.bin", 0x1F3DB0, 0xC8);
const u32 gItemIconPalette_DiveBall[] = INCBIN_U32("assets/graphics.bin", 0x1F3E78, 0x24);

const u32 gItemIcon_NestBall[] = INCBIN_U32("assets/graphics.bin", 0x1F3E9C, 0xC4);
const u32 gItemIconPalette_NestBall[] = INCBIN_U32("assets/graphics.bin", 0x1F3F60, 0x28);

const u32 gItemIcon_RepeatBall[] = INCBIN_U32("assets/graphics.bin", 0x1F3F88, 0xC4);
const u32 gItemIconPalette_RepeatBall[] = INCBIN_U32("assets/graphics.bin", 0x1F404C, 0x28);

const u32 gItemIcon_TimerBall[] = INCBIN_U32("assets/graphics.bin", 0x1F4074, 0xC8);

const u32 gItemIcon_LuxuryBall[] = INCBIN_U32("assets/graphics.bin", 0x1F413C, 0xBC);
const u32 gItemIconPalette_LuxuryBall[] = INCBIN_U32("assets/graphics.bin", 0x1F41F8, 0x28);

const u32 gItemIcon_PremierBall[] = INCBIN_U32("assets/graphics.bin", 0x1F4220, 0xA4);

// Medicine

const u32 gItemIcon_Potion[] = INCBIN_U32("assets/graphics.bin", 0x1F42C4, 0xC8);
const u32 gItemIconPalette_Potion[] = INCBIN_U32("assets/graphics.bin", 0x1F438C, 0x24);

const u32 gItemIcon_Antidote[] = INCBIN_U32("assets/graphics.bin", 0x1F43B0, 0xB0);
const u32 gItemIconPalette_Antidote[] = INCBIN_U32("assets/graphics.bin", 0x1F4460, 0x24);

const u32 gItemIconPalette_BurnHeal[] = INCBIN_U32("assets/graphics.bin", 0x1F4484, 0x24);
const u32 gItemIconPalette_IceHeal[] = INCBIN_U32("assets/graphics.bin", 0x1F44A8, 0x24);
const u32 gItemIcon_StatusHeal[] = INCBIN_U32("assets/graphics.bin", 0x1F44CC, 0xB0);
const u32 gItemIconPalette_Awakening[] = INCBIN_U32("assets/graphics.bin", 0x1F457C, 0x24);
const u32 gItemIconPalette_ParalyzeHeal[] = INCBIN_U32("assets/graphics.bin", 0x1F45A0, 0x24);

const u32 gItemIcon_LargePotion[] = INCBIN_U32("assets/graphics.bin", 0x1F45C4, 0xE4);
const u32 gItemIconPalette_FullRestore[] = INCBIN_U32("assets/graphics.bin", 0x1F46A8, 0x24);
const u32 gItemIconPalette_MaxPotion[] = INCBIN_U32("assets/graphics.bin", 0x1F46CC, 0x24);

const u32 gItemIconPalette_HyperPotion[] = INCBIN_U32("assets/graphics.bin", 0x1F46F0, 0x24);

const u32 gItemIconPalette_SuperPotion[] = INCBIN_U32("assets/graphics.bin", 0x1F4714, 0x24);

const u32 gItemIcon_FullHeal[] = INCBIN_U32("assets/graphics.bin", 0x1F4738, 0xA8);
const u32 gItemIconPalette_FullHeal[] = INCBIN_U32("assets/graphics.bin", 0x1F47E0, 0x28);

const u32 gItemIcon_Revive[] = INCBIN_U32("assets/graphics.bin", 0x1F4808, 0x5C);

const u32 gItemIcon_MaxRevive[] = INCBIN_U32("assets/graphics.bin", 0x1F4864, 0xCC);

const u32 gItemIconPalette_Revive[] = INCBIN_U32("assets/graphics.bin", 0x1F4930, 0x1C);

const u32 gItemIcon_FreshWater[] = INCBIN_U32("assets/graphics.bin", 0x1F494C, 0xB0);
const u32 gItemIconPalette_FreshWater[] = INCBIN_U32("assets/graphics.bin", 0x1F49FC, 0x24);

const u32 gItemIcon_SodaPop[] = INCBIN_U32("assets/graphics.bin", 0x1F4A20, 0x94);
const u32 gItemIconPalette_SodaPop[] = INCBIN_U32("assets/graphics.bin", 0x1F4AB4, 0x28);

const u32 gItemIcon_Lemonade[] = INCBIN_U32("assets/graphics.bin", 0x1F4ADC, 0xC0);
const u32 gItemIconPalette_Lemonade[] = INCBIN_U32("assets/graphics.bin", 0x1F4B9C, 0x28);

const u32 gItemIcon_MoomooMilk[] = INCBIN_U32("assets/graphics.bin", 0x1F4BC4, 0xB0);
const u32 gItemIconPalette_MoomooMilk[] = INCBIN_U32("assets/graphics.bin", 0x1F4C74, 0x28);

const u32 gItemIcon_Powder[] = INCBIN_U32("assets/graphics.bin", 0x1F4C9C, 0x8C);
const u32 gItemIconPalette_EnergyPowder[] = INCBIN_U32("assets/graphics.bin", 0x1F4D28, 0x20);

const u32 gItemIcon_EnergyRoot[] = INCBIN_U32("assets/graphics.bin", 0x1F4D48, 0xCC);
const u32 gItemIconPalette_EnergyRoot[] = INCBIN_U32("assets/graphics.bin", 0x1F4E14, 0x1C);

const u32 gItemIconPalette_HealPowder[] = INCBIN_U32("assets/graphics.bin", 0x1F4E30, 0x20);

const u32 gItemIcon_RevivalHerb[] = INCBIN_U32("assets/graphics.bin", 0x1F4E50, 0xD0);
const u32 gItemIconPalette_RevivalHerb[] = INCBIN_U32("assets/graphics.bin", 0x1F4F20, 0x20);

const u32 gItemIcon_Ether[] = INCBIN_U32("assets/graphics.bin", 0x1F4F40, 0xC0);
const u32 gItemIconPalette_Ether[] = INCBIN_U32("assets/graphics.bin", 0x1F5000, 0x24);
const u32 gItemIconPalette_MaxEther[] = INCBIN_U32("assets/graphics.bin", 0x1F5024, 0x24);
const u32 gItemIconPalette_Elixir[] = INCBIN_U32("assets/graphics.bin", 0x1F5048, 0x24);
const u32 gItemIconPalette_MaxElixir[] = INCBIN_U32("assets/graphics.bin", 0x1F506C, 0x24);

const u32 gItemIcon_LavaCookie[] = INCBIN_U32("assets/graphics.bin", 0x1F5090, 0xCC);
const u32 gItemIconPalette_LavaCookieAndLetter[] = INCBIN_U32("assets/graphics.bin", 0x1F515C, 0x24);

const u32 gItemIcon_Flute[] = INCBIN_U32("assets/graphics.bin", 0x1F5180, 0xB4);
const u32 gItemIconPalette_BlueFlute[] = INCBIN_U32("assets/graphics.bin", 0x1F5234, 0x24);
const u32 gItemIconPalette_YellowFlute[] = INCBIN_U32("assets/graphics.bin", 0x1F5258, 0x24);
const u32 gItemIconPalette_RedFlute[] = INCBIN_U32("assets/graphics.bin", 0x1F527C, 0x24);
const u32 gItemIconPalette_BlackFlute[] = INCBIN_U32("assets/graphics.bin", 0x1F52A0, 0x24);
const u32 gItemIconPalette_WhiteFlute[] = INCBIN_U32("assets/graphics.bin", 0x1F52C4, 0x24);

const u32 gItemIcon_BerryJuice[] = INCBIN_U32("assets/graphics.bin", 0x1F52E8, 0xE0);
const u32 gItemIconPalette_BerryJuice[] = INCBIN_U32("assets/graphics.bin", 0x1F53C8, 0x28);

const u32 gItemIcon_SacredAsh[] = INCBIN_U32("assets/graphics.bin", 0x1F53F0, 0xC0);
const u32 gItemIconPalette_SacredAsh[] = INCBIN_U32("assets/graphics.bin", 0x1F54B0, 0x24);

// Collectibles

const u32 gItemIconPalette_ShoalSalt[] = INCBIN_U32("assets/graphics.bin", 0x1F54D4, 0x20);

const u32 gItemIcon_ShoalShell[] = INCBIN_U32("assets/graphics.bin", 0x1F54F4, 0xF4);
const u32 gItemIconPalette_Shell[] = INCBIN_U32("assets/graphics.bin", 0x1F55E8, 0x28);

const u32 gItemIcon_Shard[] = INCBIN_U32("assets/graphics.bin", 0x1F5610, 0x5C);
const u32 gItemIconPalette_RedShard[] = INCBIN_U32("assets/graphics.bin", 0x1F566C, 0x18);
const u32 gItemIconPalette_BlueShard[] = INCBIN_U32("assets/graphics.bin", 0x1F5684, 0x18);
const u32 gItemIconPalette_YellowShard[] = INCBIN_U32("assets/graphics.bin", 0x1F569C, 0x18);
const u32 gItemIconPalette_GreenShard[] = INCBIN_U32("assets/graphics.bin", 0x1F56B4, 0x18);

// Vitamins

const u32 gItemIcon_HPUp[] = INCBIN_U32("assets/graphics.bin", 0x1F56CC, 0xB8);
const u32 gItemIconPalette_HPUp[] = INCBIN_U32("assets/graphics.bin", 0x1F5784, 0x28);

const u32 gItemIcon_Vitamin[] = INCBIN_U32("assets/graphics.bin", 0x1F57AC, 0xB0);
const u32 gItemIconPalette_Protein[] = INCBIN_U32("assets/graphics.bin", 0x1F585C, 0x28);
const u32 gItemIconPalette_Iron[] = INCBIN_U32("assets/graphics.bin", 0x1F5884, 0x28);
const u32 gItemIconPalette_Carbos[] = INCBIN_U32("assets/graphics.bin", 0x1F58AC, 0x28);
const u32 gItemIconPalette_Calcium[] = INCBIN_U32("assets/graphics.bin", 0x1F58D4, 0x28);

const u32 gItemIcon_RareCandy[] = INCBIN_U32("assets/graphics.bin", 0x1F58FC, 0xC4);
const u32 gItemIconPalette_RareCandy[] = INCBIN_U32("assets/graphics.bin", 0x1F59C0, 0x1C);

const u32 gItemIcon_PPUp[] = INCBIN_U32("assets/graphics.bin", 0x1F59DC, 0xB0);
const u32 gItemIconPalette_PPUp[] = INCBIN_U32("assets/graphics.bin", 0x1F5A8C, 0x28);

const u32 gItemIconPalette_Zinc[] = INCBIN_U32("assets/graphics.bin", 0x1F5AB4, 0x28);

const u32 gItemIcon_PPMax[] = INCBIN_U32("assets/graphics.bin", 0x1F5ADC, 0xA8);
const u32 gItemIconPalette_PPMax[] = INCBIN_U32("assets/graphics.bin", 0x1F5B84, 0x28);

// Battle items

const u32 gItemIconPalette_GuardSpec[] = INCBIN_U32("assets/graphics.bin", 0x1F5BAC, 0x24);
const u32 gItemIconPalette_DireHit[] = INCBIN_U32("assets/graphics.bin", 0x1F5BD0, 0x24);
const u32 gItemIconPalette_XAttack[] = INCBIN_U32("assets/graphics.bin", 0x1F5BF4, 0x24);
const u32 gItemIcon_BattleStatItem[] = INCBIN_U32("assets/graphics.bin", 0x1F5C18, 0xE4);
const u32 gItemIconPalette_XDefend[] = INCBIN_U32("assets/graphics.bin", 0x1F5CFC, 0x24);
const u32 gItemIconPalette_XSpeed[] = INCBIN_U32("assets/graphics.bin", 0x1F5D20, 0x24);
const u32 gItemIconPalette_XAccuracy[] = INCBIN_U32("assets/graphics.bin", 0x1F5D44, 0x24);
const u32 gItemIconPalette_XSpecial[] = INCBIN_U32("assets/graphics.bin", 0x1F5D68, 0x24);

const u32 gItemIcon_PokeDoll[] = INCBIN_U32("assets/graphics.bin", 0x1F5D8C, 0xF0);
const u32 gItemIconPalette_PokeDoll[] = INCBIN_U32("assets/graphics.bin", 0x1F5E7C, 0x1C);

const u32 gItemIcon_FluffyTail[] = INCBIN_U32("assets/graphics.bin", 0x1F5E98, 0xF0);
const u32 gItemIconPalette_FluffyTail[] = INCBIN_U32("assets/graphics.bin", 0x1F5F88, 0x24);

// Field items

const u32 gItemIcon_Repel[] = INCBIN_U32("assets/graphics.bin", 0x1F5FAC, 0xA0);
const u32 gItemIconPalette_SuperRepel[] = INCBIN_U32("assets/graphics.bin", 0x1F604C, 0x28);
const u32 gItemIconPalette_MaxRepel[] = INCBIN_U32("assets/graphics.bin", 0x1F6074, 0x28);

const u32 gItemIcon_EscapeRope[] = INCBIN_U32("assets/graphics.bin", 0x1F609C, 0xB4);

const u32 gItemIconPalette_EscapeRope[] = INCBIN_U32("assets/graphics.bin", 0x1F6150, 0x24);

const u32 gItemIconPalette_Repel[] = INCBIN_U32("assets/graphics.bin", 0x1F6174, 0x28);

// Evolution stones

const u32 gItemIcon_SunStone[] = INCBIN_U32("assets/graphics.bin", 0x1F619C, 0xF8);
const u32 gItemIconPalette_SunStone[] = INCBIN_U32("assets/graphics.bin", 0x1F6294, 0x1C);

const u32 gItemIcon_MoonStone[] = INCBIN_U32("assets/graphics.bin", 0x1F62B0, 0xD4);
const u32 gItemIconPalette_MoonStone[] = INCBIN_U32("assets/graphics.bin", 0x1F6384, 0x20);

const u32 gItemIcon_FireStone[] = INCBIN_U32("assets/graphics.bin", 0x1F63A4, 0xF4);
const u32 gItemIconPalette_FireStone[] = INCBIN_U32("assets/graphics.bin", 0x1F6498, 0x28);

const u32 gItemIcon_ThunderStone[] = INCBIN_U32("assets/graphics.bin", 0x1F64C0, 0xE8);
const u32 gItemIconPalette_ThunderStone[] = INCBIN_U32("assets/graphics.bin", 0x1F65A8, 0x20);

const u32 gItemIcon_WaterStone[] = INCBIN_U32("assets/graphics.bin", 0x1F65C8, 0xE0);
const u32 gItemIconPalette_WaterStone[] = INCBIN_U32("assets/graphics.bin", 0x1F66A8, 0x24);

const u32 gItemIcon_LeafStone[] = INCBIN_U32("assets/graphics.bin", 0x1F66CC, 0xF4);
const u32 gItemIconPalette_LeafStone[] = INCBIN_U32("assets/graphics.bin", 0x1F67C0, 0x28);

// Valuables

const u32 gItemIcon_TinyMushroom[] = INCBIN_U32("assets/graphics.bin", 0x1F67E8, 0x80);
const u32 gItemIcon_BigMushroom[] = INCBIN_U32("assets/graphics.bin", 0x1F6868, 0xB8);
const u32 gItemIconPalette_Mushroom[] = INCBIN_U32("assets/graphics.bin", 0x1F6920, 0x24);

const u32 gItemIcon_Pearl[] = INCBIN_U32("assets/graphics.bin", 0x1F6944, 0x7C);
const u32 gItemIconPalette_Pearl[] = INCBIN_U32("assets/graphics.bin", 0x1F69C0, 0x28);
const u32 gItemIcon_BigPearl[] = INCBIN_U32("assets/graphics.bin", 0x1F69E8, 0xB8);

const u32 gItemIcon_Stardust[] = INCBIN_U32("assets/graphics.bin", 0x1F6AA0, 0xC0);
const u32 gItemIconPalette_Star[] = INCBIN_U32("assets/graphics.bin", 0x1F6B60, 0x24);
const u32 gItemIcon_StarPiece[] = INCBIN_U32("assets/graphics.bin", 0x1F6B84, 0x84);

const u32 gItemIcon_Nugget[] = INCBIN_U32("assets/graphics.bin", 0x1F6C08, 0x8C);
const u32 gItemIconPalette_Nugget[] = INCBIN_U32("assets/graphics.bin", 0x1F6C94, 0x20);

const u32 gItemIcon_HeartScale[] = INCBIN_U32("assets/graphics.bin", 0x1F6CB4, 0xA0);
const u32 gItemIconPalette_HeartScale[] = INCBIN_U32("assets/graphics.bin", 0x1F6D54, 0x1C);

// Mail

const u32 gItemIcon_OrangeMail[] = INCBIN_U32("assets/graphics.bin", 0x1F6D70, 0xD4);
const u32 gItemIconPalette_OrangeMail[] = INCBIN_U32("assets/graphics.bin", 0x1F6E44, 0x20);

const u32 gItemIcon_HarborMail[] = INCBIN_U32("assets/graphics.bin", 0x1F6E64, 0xC8);
const u32 gItemIconPalette_HarborMail[] = INCBIN_U32("assets/graphics.bin", 0x1F6F2C, 0x20);

const u32 gItemIcon_GlitterMail[] = INCBIN_U32("assets/graphics.bin", 0x1F6F4C, 0xDC);
const u32 gItemIconPalette_GlitterMail[] = INCBIN_U32("assets/graphics.bin", 0x1F7028, 0x28);

const u32 gItemIcon_MechMail[] = INCBIN_U32("assets/graphics.bin", 0x1F7050, 0xDC);
const u32 gItemIconPalette_MechMail[] = INCBIN_U32("assets/graphics.bin", 0x1F712C, 0x20);

const u32 gItemIcon_WoodMail[] = INCBIN_U32("assets/graphics.bin", 0x1F714C, 0xE0);
const u32 gItemIconPalette_WoodMail[] = INCBIN_U32("assets/graphics.bin", 0x1F722C, 0x20);

const u32 gItemIcon_WaveMail[] = INCBIN_U32("assets/graphics.bin", 0x1F724C, 0xD8);
const u32 gItemIconPalette_WaveMail[] = INCBIN_U32("assets/graphics.bin", 0x1F7324, 0x20);

const u32 gItemIcon_BeadMail[] = INCBIN_U32("assets/graphics.bin", 0x1F7344, 0xC0);
const u32 gItemIconPalette_BeadMail[] = INCBIN_U32("assets/graphics.bin", 0x1F7404, 0x20);

const u32 gItemIcon_ShadowMail[] = INCBIN_U32("assets/graphics.bin", 0x1F7424, 0xD4);
const u32 gItemIconPalette_ShadowMail[] = INCBIN_U32("assets/graphics.bin", 0x1F74F8, 0x24);

const u32 gItemIcon_TropicMail[] = INCBIN_U32("assets/graphics.bin", 0x1F751C, 0xE4);
const u32 gItemIconPalette_TropicMail[] = INCBIN_U32("assets/graphics.bin", 0x1F7600, 0x24);

const u32 gItemIcon_DreamMail[] = INCBIN_U32("assets/graphics.bin", 0x1F7624, 0xE0);
const u32 gItemIconPalette_DreamMail[] = INCBIN_U32("assets/graphics.bin", 0x1F7704, 0x20);

const u32 gItemIcon_FabMail[] = INCBIN_U32("assets/graphics.bin", 0x1F7724, 0xC8);
const u32 gItemIconPalette_FabMail[] = INCBIN_U32("assets/graphics.bin", 0x1F77EC, 0x1C);

const u32 gItemIcon_RetroMail[] = INCBIN_U32("assets/graphics.bin", 0x1F7808, 0x98);
const u32 gItemIconPalette_RetroMail[] = INCBIN_U32("assets/graphics.bin", 0x1F78A0, 0x20);

// Berries

const u32 gItemIcon_CheriBerry[] = INCBIN_U32("assets/graphics.bin", 0x1F78C0, 0xE8);
const u32 gItemIconPalette_CheriBerry[] = INCBIN_U32("assets/graphics.bin", 0x1F79A8, 0x28);

const u32 gItemIcon_ChestoBerry[] = INCBIN_U32("assets/graphics.bin", 0x1F79D0, 0xC0);
const u32 gItemIconPalette_ChestoBerry[] = INCBIN_U32("assets/graphics.bin", 0x1F7A90, 0x24);

const u32 gItemIcon_PechaBerry[] = INCBIN_U32("assets/graphics.bin", 0x1F7AB4, 0xC0);
const u32 gItemIconPalette_PechaBerry[] = INCBIN_U32("assets/graphics.bin", 0x1F7B74, 0x24);

const u32 gItemIcon_RawstBerry[] = INCBIN_U32("assets/graphics.bin", 0x1F7B98, 0xE4);
const u32 gItemIconPalette_RawstBerry[] = INCBIN_U32("assets/graphics.bin", 0x1F7C7C, 0x24);

const u32 gItemIcon_AspearBerry[] = INCBIN_U32("assets/graphics.bin", 0x1F7CA0, 0xE8);
const u32 gItemIconPalette_AspearBerry[] = INCBIN_U32("assets/graphics.bin", 0x1F7D88, 0x24);

const u32 gItemIcon_LeppaBerry[] = INCBIN_U32("assets/graphics.bin", 0x1F7DAC, 0xB8);
const u32 gItemIconPalette_LeppaBerry[] = INCBIN_U32("assets/graphics.bin", 0x1F7E64, 0x24);

const u32 gItemIcon_OranBerry[] = INCBIN_U32("assets/graphics.bin", 0x1F7E88, 0xC4);
const u32 gItemIconPalette_OranBerry[] = INCBIN_U32("assets/graphics.bin", 0x1F7F4C, 0x24);

const u32 gItemIcon_PersimBerry[] = INCBIN_U32("assets/graphics.bin", 0x1F7F70, 0xD4);
const u32 gItemIconPalette_PersimBerry[] = INCBIN_U32("assets/graphics.bin", 0x1F8044, 0x24);

const u32 gItemIcon_LumBerry[] = INCBIN_U32("assets/graphics.bin", 0x1F8068, 0xB8);
const u32 gItemIconPalette_LumBerry[] = INCBIN_U32("assets/graphics.bin", 0x1F8120, 0x1C);

const u32 gItemIcon_SitrusBerry[] = INCBIN_U32("assets/graphics.bin", 0x1F813C, 0xCC);
const u32 gItemIconPalette_SitrusBerry[] = INCBIN_U32("assets/graphics.bin", 0x1F8208, 0x24);

const u32 gItemIcon_FigyBerry[] = INCBIN_U32("assets/graphics.bin", 0x1F822C, 0xC8);
const u32 gItemIconPalette_FigyBerry[] = INCBIN_U32("assets/graphics.bin", 0x1F82F4, 0x24);

const u32 gItemIcon_WikiBerry[] = INCBIN_U32("assets/graphics.bin", 0x1F8318, 0xE4);
const u32 gItemIconPalette_WikiBerry[] = INCBIN_U32("assets/graphics.bin", 0x1F83FC, 0x24);

const u32 gItemIcon_MagoBerry[] = INCBIN_U32("assets/graphics.bin", 0x1F8420, 0xBC);
const u32 gItemIconPalette_MagoBerry[] = INCBIN_U32("assets/graphics.bin", 0x1F84DC, 0x24);

const u32 gItemIcon_AguavBerry[] = INCBIN_U32("assets/graphics.bin", 0x1F8500, 0xEC);
const u32 gItemIconPalette_AguavBerry[] = INCBIN_U32("assets/graphics.bin", 0x1F85EC, 0x20);

const u32 gItemIcon_IapapaBerry[] = INCBIN_U32("assets/graphics.bin", 0x1F860C, 0xE8);
const u32 gItemIconPalette_IapapaBerry[] = INCBIN_U32("assets/graphics.bin", 0x1F86F4, 0x24);

const u32 gItemIcon_RazzBerry[] = INCBIN_U32("assets/graphics.bin", 0x1F8718, 0xE0);
const u32 gItemIconPalette_RazzBerry[] = INCBIN_U32("assets/graphics.bin", 0x1F87F8, 0x24);

const u32 gItemIcon_BlukBerry[] = INCBIN_U32("assets/graphics.bin", 0x1F881C, 0xF0);
const u32 gItemIconPalette_BlukBerry[] = INCBIN_U32("assets/graphics.bin", 0x1F890C, 0x24);

const u32 gItemIcon_NanabBerry[] = INCBIN_U32("assets/graphics.bin", 0x1F8930, 0xE4);
const u32 gItemIconPalette_NanabBerry[] = INCBIN_U32("assets/graphics.bin", 0x1F8A14, 0x24);

const u32 gItemIcon_WepearBerry[] = INCBIN_U32("assets/graphics.bin", 0x1F8A38, 0xC8);
const u32 gItemIconPalette_WepearBerry[] = INCBIN_U32("assets/graphics.bin", 0x1F8B00, 0x1C);

const u32 gItemIcon_PinapBerry[] = INCBIN_U32("assets/graphics.bin", 0x1F8B1C, 0xF4);
const u32 gItemIconPalette_PinapBerry[] = INCBIN_U32("assets/graphics.bin", 0x1F8C10, 0x24);

const u32 gItemIcon_PomegBerry[] = INCBIN_U32("assets/graphics.bin", 0x1F8C34, 0xB4);
const u32 gItemIconPalette_PomegBerry[] = INCBIN_U32("assets/graphics.bin", 0x1F8CE8, 0x24);

const u32 gItemIcon_KelpsyBerry[] = INCBIN_U32("assets/graphics.bin", 0x1F8D0C, 0xD0);
const u32 gItemIconPalette_KelpsyBerry[] = INCBIN_U32("assets/graphics.bin", 0x1F8DDC, 0x20);

const u32 gItemIcon_QualotBerry[] = INCBIN_U32("assets/graphics.bin", 0x1F8DFC, 0xCC);
const u32 gItemIconPalette_QualotBerry[] = INCBIN_U32("assets/graphics.bin", 0x1F8EC8, 0x24);

const u32 gItemIcon_HondewBerry[] = INCBIN_U32("assets/graphics.bin", 0x1F8EEC, 0xE0);
const u32 gItemIconPalette_HondewBerry[] = INCBIN_U32("assets/graphics.bin", 0x1F8FCC, 0x24);

const u32 gItemIcon_GrepaBerry[] = INCBIN_U32("assets/graphics.bin", 0x1F8FF0, 0xB4);
const u32 gItemIconPalette_GrepaBerry[] = INCBIN_U32("assets/graphics.bin", 0x1F90A4, 0x24);

const u32 gItemIcon_TamatoBerry[] = INCBIN_U32("assets/graphics.bin", 0x1F90C8, 0xDC);
const u32 gItemIconPalette_TamatoBerry[] = INCBIN_U32("assets/graphics.bin", 0x1F91A4, 0x24);

const u32 gItemIcon_CornnBerry[] = INCBIN_U32("assets/graphics.bin", 0x1F91C8, 0xEC);
const u32 gItemIconPalette_CornnBerry[] = INCBIN_U32("assets/graphics.bin", 0x1F92B4, 0x28);

const u32 gItemIcon_MagostBerry[] = INCBIN_U32("assets/graphics.bin", 0x1F92DC, 0xA8);
const u32 gItemIconPalette_MagostBerry[] = INCBIN_U32("assets/graphics.bin", 0x1F9384, 0x24);

const u32 gItemIcon_RabutaBerry[] = INCBIN_U32("assets/graphics.bin", 0x1F93A8, 0xFC);
const u32 gItemIconPalette_RabutaBerry[] = INCBIN_U32("assets/graphics.bin", 0x1F94A4, 0x24);

const u32 gItemIcon_NomelBerry[] = INCBIN_U32("assets/graphics.bin", 0x1F94C8, 0xA4);
const u32 gItemIconPalette_NomelBerry[] = INCBIN_U32("assets/graphics.bin", 0x1F956C, 0x1C);

const u32 gItemIcon_SpelonBerry[] = INCBIN_U32("assets/graphics.bin", 0x1F9588, 0xC4);
const u32 gItemIconPalette_SpelonBerry[] = INCBIN_U32("assets/graphics.bin", 0x1F964C, 0x20);

const u32 gItemIcon_PamtreBerry[] = INCBIN_U32("assets/graphics.bin", 0x1F966C, 0xE0);
const u32 gItemIconPalette_PamtreBerry[] = INCBIN_U32("assets/graphics.bin", 0x1F974C, 0x28);

const u32 gItemIcon_WatmelBerry[] = INCBIN_U32("assets/graphics.bin", 0x1F9774, 0x110);
const u32 gItemIconPalette_WatmelBerry[] = INCBIN_U32("assets/graphics.bin", 0x1F9884, 0x24);

const u32 gItemIcon_DurinBerry[] = INCBIN_U32("assets/graphics.bin", 0x1F98A8, 0x104);
const u32 gItemIconPalette_DurinBerry[] = INCBIN_U32("assets/graphics.bin", 0x1F99AC, 0x24);

const u32 gItemIcon_BelueBerry[] = INCBIN_U32("assets/graphics.bin", 0x1F99D0, 0xE4);
const u32 gItemIconPalette_BelueBerry[] = INCBIN_U32("assets/graphics.bin", 0x1F9AB4, 0x24);

const u32 gItemIcon_LiechiBerry[] = INCBIN_U32("assets/graphics.bin", 0x1F9AD8, 0xE0);
const u32 gItemIconPalette_LiechiBerry[] = INCBIN_U32("assets/graphics.bin", 0x1F9BB8, 0x20);

const u32 gItemIcon_GanlonBerry[] = INCBIN_U32("assets/graphics.bin", 0x1F9BD8, 0xE0);
const u32 gItemIconPalette_GanlonBerry[] = INCBIN_U32("assets/graphics.bin", 0x1F9CB8, 0x20);

const u32 gItemIcon_SalacBerry[] = INCBIN_U32("assets/graphics.bin", 0x1F9CD8, 0xE8);
const u32 gItemIconPalette_SalacBerry[] = INCBIN_U32("assets/graphics.bin", 0x1F9DC0, 0x20);

const u32 gItemIcon_PetayaBerry[] = INCBIN_U32("assets/graphics.bin", 0x1F9DE0, 0xF8);
const u32 gItemIconPalette_PetayaBerry[] = INCBIN_U32("assets/graphics.bin", 0x1F9ED8, 0x24);

const u32 gItemIcon_ApicotBerry[] = INCBIN_U32("assets/graphics.bin", 0x1F9EFC, 0xB8);
const u32 gItemIconPalette_ApicotBerry[] = INCBIN_U32("assets/graphics.bin", 0x1F9FB4, 0x28);

const u32 gItemIcon_LansatBerry[] = INCBIN_U32("assets/graphics.bin", 0x1F9FDC, 0xE0);
const u32 gItemIconPalette_LansatBerry[] = INCBIN_U32("assets/graphics.bin", 0x1FA0BC, 0x24);

const u32 gItemIcon_StarfBerry[] = INCBIN_U32("assets/graphics.bin", 0x1FA0E0, 0xD0);
const u32 gItemIconPalette_StarfBerry[] = INCBIN_U32("assets/graphics.bin", 0x1FA1B0, 0x24);

const u32 gItemIcon_EnigmaBerry[] = INCBIN_U32("assets/graphics.bin", 0x1FA1D4, 0xCC);
const u32 gItemIconPalette_EnigmaBerry[] = INCBIN_U32("assets/graphics.bin", 0x1FA2A0, 0x20);

// Hold items

const u32 gItemIcon_BrightPowder[] = INCBIN_U32("assets/graphics.bin", 0x1FA2C0, 0xBC);
const u32 gItemIconPalette_BrightPowder[] = INCBIN_U32("assets/graphics.bin", 0x1FA37C, 0x20);

const u32 gItemIcon_InBattleHerb[] = INCBIN_U32("assets/graphics.bin", 0x1FA39C, 0xAC);
const u32 gItemIconPalette_WhiteHerb[] = INCBIN_U32("assets/graphics.bin", 0x1FA448, 0x20);

const u32 gItemIcon_MachoBrace[] = INCBIN_U32("assets/graphics.bin", 0x1FA468, 0xEC);
const u32 gItemIconPalette_MachoBrace[] = INCBIN_U32("assets/graphics.bin", 0x1FA554, 0x28);

const u32 gItemIcon_ExpShare[] = INCBIN_U32("assets/graphics.bin", 0x1FA57C, 0xEC);
const u32 gItemIconPalette_ExpShare[] = INCBIN_U32("assets/graphics.bin", 0x1FA668, 0x28);

const u32 gItemIcon_QuickClaw[] = INCBIN_U32("assets/graphics.bin", 0x1FA690, 0x98);
const u32 gItemIconPalette_QuickClaw[] = INCBIN_U32("assets/graphics.bin", 0x1FA728, 0x20);

const u32 gItemIcon_SootheBell[] = INCBIN_U32("assets/graphics.bin", 0x1FA748, 0xC4);
const u32 gItemIconPalette_SootheBell[] = INCBIN_U32("assets/graphics.bin", 0x1FA80C, 0x24);

const u32 gItemIconPalette_MentalHerb[] = INCBIN_U32("assets/graphics.bin", 0x1FA830, 0x20);

const u32 gItemIcon_ChoiceBand[] = INCBIN_U32("assets/graphics.bin", 0x1FA850, 0xEC);
const u32 gItemIconPalette_ChoiceBand[] = INCBIN_U32("assets/graphics.bin", 0x1FA93C, 0x28);

const u32 gItemIcon_KingsRock[] = INCBIN_U32("assets/graphics.bin", 0x1FA964, 0xF0);
const u32 gItemIconPalette_KingsRock[] = INCBIN_U32("assets/graphics.bin", 0x1FAA54, 0x1C);

const u32 gItemIcon_SilverPowder[] = INCBIN_U32("assets/graphics.bin", 0x1FAA70, 0x8C);
const u32 gItemIconPalette_SilverPowder[] = INCBIN_U32("assets/graphics.bin", 0x1FAAFC, 0x24);

const u32 gItemIcon_AmuletCoin[] = INCBIN_U32("assets/graphics.bin", 0x1FAB20, 0x98);
const u32 gItemIconPalette_AmuletCoin[] = INCBIN_U32("assets/graphics.bin", 0x1FABB8, 0x24);

const u32 gItemIcon_CleanseTag[] = INCBIN_U32("assets/graphics.bin", 0x1FABDC, 0xA4);
const u32 gItemIconPalette_CleanseTag[] = INCBIN_U32("assets/graphics.bin", 0x1FAC80, 0x20);

const u32 gItemIcon_SoulDew[] = INCBIN_U32("assets/graphics.bin", 0x1FACA0, 0x94);
const u32 gItemIconPalette_SoulDew[] = INCBIN_U32("assets/graphics.bin", 0x1FAD34, 0x20);

const u32 gItemIcon_DeepSeaTooth[] = INCBIN_U32("assets/graphics.bin", 0x1FAD54, 0xB4);
const u32 gItemIconPalette_DeepSeaTooth[] = INCBIN_U32("assets/graphics.bin", 0x1FAE08, 0x24);

const u32 gItemIcon_DeepSeaScale[] = INCBIN_U32("assets/graphics.bin", 0x1FAE2C, 0xA8);
const u32 gItemIconPalette_DeepSeaScale[] = INCBIN_U32("assets/graphics.bin", 0x1FAED4, 0x20);

const u32 gItemIcon_SmokeBall[] = INCBIN_U32("assets/graphics.bin", 0x1FAEF4, 0xB8);
const u32 gItemIconPalette_SmokeBall[] = INCBIN_U32("assets/graphics.bin", 0x1FAFAC, 0x24);

const u32 gItemIcon_Everstone[] = INCBIN_U32("assets/graphics.bin", 0x1FAFD0, 0xB4);
const u32 gItemIconPalette_Everstone[] = INCBIN_U32("assets/graphics.bin", 0x1FB084, 0x1C);

const u32 gItemIcon_FocusBand[] = INCBIN_U32("assets/graphics.bin", 0x1FB0A0, 0xF0);
const u32 gItemIconPalette_FocusBand[] = INCBIN_U32("assets/graphics.bin", 0x1FB190, 0x28);

const u32 gItemIcon_LuckyEgg[] = INCBIN_U32("assets/graphics.bin", 0x1FB1B8, 0x88);
const u32 gItemIconPalette_LuckyEgg[] = INCBIN_U32("assets/graphics.bin", 0x1FB240, 0x18);

const u32 gItemIcon_ScopeLens[] = INCBIN_U32("assets/graphics.bin", 0x1FB258, 0x100);
const u32 gItemIconPalette_ScopeLens[] = INCBIN_U32("assets/graphics.bin", 0x1FB358, 0x28);

const u32 gItemIcon_MetalCoat[] = INCBIN_U32("assets/graphics.bin", 0x1FB380, 0xBC);
const u32 gItemIconPalette_MetalCoat[] = INCBIN_U32("assets/graphics.bin", 0x1FB43C, 0x20);

const u32 gItemIcon_Leftovers[] = INCBIN_U32("assets/graphics.bin", 0x1FB45C, 0xA4);
const u32 gItemIconPalette_Leftovers[] = INCBIN_U32("assets/graphics.bin", 0x1FB500, 0x24);

const u32 gItemIcon_DragonScale[] = INCBIN_U32("assets/graphics.bin", 0x1FB524, 0xB4);
const u32 gItemIconPalette_DragonScale[] = INCBIN_U32("assets/graphics.bin", 0x1FB5D8, 0x20);

const u32 gItemIcon_LightBall[] = INCBIN_U32("assets/graphics.bin", 0x1FB5F8, 0x94);
const u32 gItemIconPalette_LightBall[] = INCBIN_U32("assets/graphics.bin", 0x1FB68C, 0x24);

const u32 gItemIcon_SoftSand[] = INCBIN_U32("assets/graphics.bin", 0x1FB6B0, 0xBC);
const u32 gItemIconPalette_SoftSand[] = INCBIN_U32("assets/graphics.bin", 0x1FB76C, 0x20);

const u32 gItemIcon_HardStone[] = INCBIN_U32("assets/graphics.bin", 0x1FB78C, 0xB4);
const u32 gItemIconPalette_HardStone[] = INCBIN_U32("assets/graphics.bin", 0x1FB840, 0x24);

const u32 gItemIcon_MiracleSeed[] = INCBIN_U32("assets/graphics.bin", 0x1FB864, 0xB0);
const u32 gItemIconPalette_MiracleSeed[] = INCBIN_U32("assets/graphics.bin", 0x1FB914, 0x1C);

const u32 gItemIcon_BlackGlasses[] = INCBIN_U32("assets/graphics.bin", 0x1FB930, 0x88);
const u32 gItemIconPalette_BlackTypeEnhancingItem[] = INCBIN_U32("assets/graphics.bin", 0x1FB9B8, 0x18);

const u32 gItemIcon_BlackBelt[] = INCBIN_U32("assets/graphics.bin", 0x1FB9D0, 0xC8);

const u32 gItemIcon_Magnet[] = INCBIN_U32("assets/graphics.bin", 0x1FBA98, 0xB0);
const u32 gItemIconPalette_Magnet[] = INCBIN_U32("assets/graphics.bin", 0x1FBB48, 0x28);

const u32 gItemIcon_MysticWater[] = INCBIN_U32("assets/graphics.bin", 0x1FBB70, 0x98);
const u32 gItemIconPalette_MysticWater[] = INCBIN_U32("assets/graphics.bin", 0x1FBC08, 0x20);

const u32 gItemIcon_SharpBeak[] = INCBIN_U32("assets/graphics.bin", 0x1FBC28, 0xBC);
const u32 gItemIconPalette_SharpBeak[] = INCBIN_U32("assets/graphics.bin", 0x1FBCE4, 0x20);

const u32 gItemIcon_PoisonBarb[] = INCBIN_U32("assets/graphics.bin", 0x1FBD04, 0x88);
const u32 gItemIconPalette_PoisonBarb[] = INCBIN_U32("assets/graphics.bin", 0x1FBD8C, 0x20);

const u32 gItemIcon_NeverMeltIce[] = INCBIN_U32("assets/graphics.bin", 0x1FBDAC, 0xCC);
const u32 gItemIconPalette_NeverMeltIce[] = INCBIN_U32("assets/graphics.bin", 0x1FBE78, 0x1C);

const u32 gItemIcon_SpellTag[] = INCBIN_U32("assets/graphics.bin", 0x1FBE94, 0xA0);
const u32 gItemIconPalette_SpellTag[] = INCBIN_U32("assets/graphics.bin", 0x1FBF34, 0x20);

const u32 gItemIcon_TwistedSpoon[] = INCBIN_U32("assets/graphics.bin", 0x1FBF54, 0xA0);
const u32 gItemIconPalette_TwistedSpoon[] = INCBIN_U32("assets/graphics.bin", 0x1FBFF4, 0x18);

const u32 gItemIcon_Charcoal[] = INCBIN_U32("assets/graphics.bin", 0x1FC00C, 0xD0);
const u32 gItemIconPalette_Charcoal[] = INCBIN_U32("assets/graphics.bin", 0x1FC0DC, 0x1C);

const u32 gItemIcon_DragonFang[] = INCBIN_U32("assets/graphics.bin", 0x1FC0F8, 0xB4);
const u32 gItemIconPalette_DragonFang[] = INCBIN_U32("assets/graphics.bin", 0x1FC1AC, 0x20);

const u32 gItemIcon_SilkScarf[] = INCBIN_U32("assets/graphics.bin", 0x1FC1CC, 0x108);
const u32 gItemIconPalette_SilkScarf[] = INCBIN_U32("assets/graphics.bin", 0x1FC2D4, 0x20);

const u32 gItemIcon_UpGrade[] = INCBIN_U32("assets/graphics.bin", 0x1FC2F4, 0xBC);
const u32 gItemIconPalette_UpGrade[] = INCBIN_U32("assets/graphics.bin", 0x1FC3B0, 0x28);

const u32 gItemIcon_ShellBell[] = INCBIN_U32("assets/graphics.bin", 0x1FC3D8, 0xE0);

const u32 gItemIcon_SeaIncense[] = INCBIN_U32("assets/graphics.bin", 0x1FC4B8, 0xE8);
const u32 gItemIconPalette_SeaIncense[] = INCBIN_U32("assets/graphics.bin", 0x1FC5A0, 0x28);

const u32 gItemIcon_LaxIncense[] = INCBIN_U32("assets/graphics.bin", 0x1FC5C8, 0xE8);
const u32 gItemIconPalette_LaxIncense[] = INCBIN_U32("assets/graphics.bin", 0x1FC6B0, 0x28);

const u32 gItemIcon_LuckyPunch[] = INCBIN_U32("assets/graphics.bin", 0x1FC6D8, 0xC4);
const u32 gItemIconPalette_LuckyPunch[] = INCBIN_U32("assets/graphics.bin", 0x1FC79C, 0x20);

const u32 gItemIcon_MetalPowder[] = INCBIN_U32("assets/graphics.bin", 0x1FC7BC, 0xC0);
const u32 gItemIconPalette_MetalPowder[] = INCBIN_U32("assets/graphics.bin", 0x1FC87C, 0x24);

const u32 gItemIcon_ThickClub[] = INCBIN_U32("assets/graphics.bin", 0x1FC8A0, 0x94);
const u32 gItemIconPalette_ThickClub[] = INCBIN_U32("assets/graphics.bin", 0x1FC934, 0x1C);

const u32 gItemIcon_Stick[] = INCBIN_U32("assets/graphics.bin", 0x1FC950, 0xA0);
const u32 gItemIconPalette_Stick[] = INCBIN_U32("assets/graphics.bin", 0x1FC9F0, 0x24);

const u32 gItemIcon_Scarf[] = INCBIN_U32("assets/graphics.bin", 0x1FCA14, 0xCC);
const u32 gItemIconPalette_RedScarf[] = INCBIN_U32("assets/graphics.bin", 0x1FCAE0, 0x1C);
const u32 gItemIconPalette_BlueScarf[] = INCBIN_U32("assets/graphics.bin", 0x1FCAFC, 0x1C);
const u32 gItemIconPalette_PinkScarf[] = INCBIN_U32("assets/graphics.bin", 0x1FCB18, 0x1C);
const u32 gItemIconPalette_GreenScarf[] = INCBIN_U32("assets/graphics.bin", 0x1FCB34, 0x1C);
const u32 gItemIconPalette_YellowScarf[] = INCBIN_U32("assets/graphics.bin", 0x1FCB50, 0x1C);

// Key items

const u32 gItemIcon_MachBike[] = INCBIN_U32("assets/graphics.bin", 0x1FCB6C, 0x108);
const u32 gItemIconPalette_MachBike[] = INCBIN_U32("assets/graphics.bin", 0x1FCC74, 0x24);

const u32 gItemIcon_CoinCase[] = INCBIN_U32("assets/graphics.bin", 0x1FCC98, 0xC0);
const u32 gItemIconPalette_CoinCase[] = INCBIN_U32("assets/graphics.bin", 0x1FCD58, 0x20);

const u32 gItemIcon_Itemfinder[] = INCBIN_U32("assets/graphics.bin", 0x1FCD78, 0xBC);
const u32 gItemIconPalette_Itemfinder[] = INCBIN_U32("assets/graphics.bin", 0x1FCE34, 0x28);

const u32 gItemIcon_OldRod[] = INCBIN_U32("assets/graphics.bin", 0x1FCE5C, 0xAC);
const u32 gItemIconPalette_OldRod[] = INCBIN_U32("assets/graphics.bin", 0x1FCF08, 0x24);

const u32 gItemIcon_GoodRod[] = INCBIN_U32("assets/graphics.bin", 0x1FCF2C, 0x9C);
const u32 gItemIconPalette_GoodRod[] = INCBIN_U32("assets/graphics.bin", 0x1FCFC8, 0x28);

const u32 gItemIcon_SuperRod[] = INCBIN_U32("assets/graphics.bin", 0x1FCFF0, 0xB0);
const u32 gItemIconPalette_SuperRod[] = INCBIN_U32("assets/graphics.bin", 0x1FD0A0, 0x28);

const u32 gItemIcon_SSTicket[] = INCBIN_U32("assets/graphics.bin", 0x1FD0C8, 0x94);
const u32 gItemIconPalette_SSTicket[] = INCBIN_U32("assets/graphics.bin", 0x1FD15C, 0x18);

const u32 gItemIcon_ContestPass[] = INCBIN_U32("assets/graphics.bin", 0x1FD174, 0xAC);
const u32 gItemIconPalette_ContestPass[] = INCBIN_U32("assets/graphics.bin", 0x1FD220, 0x28);

const u32 gItemIcon_WailmerPail[] = INCBIN_U32("assets/graphics.bin", 0x1FD248, 0xCC);
const u32 gItemIconPalette_WailmerPail[] = INCBIN_U32("assets/graphics.bin", 0x1FD314, 0x24);

const u32 gItemIcon_DevonGoods[] = INCBIN_U32("assets/graphics.bin", 0x1FD338, 0xA8);
const u32 gItemIconPalette_DevonGoods[] = INCBIN_U32("assets/graphics.bin", 0x1FD3E0, 0x1C);

const u32 gItemIcon_SootSack[] = INCBIN_U32("assets/graphics.bin", 0x1FD3FC, 0xD8);
const u32 gItemIconPalette_SootSack[] = INCBIN_U32("assets/graphics.bin", 0x1FD4D4, 0x28);

const u32 gItemIcon_BasementKey[] = INCBIN_U32("assets/graphics.bin", 0x1FD4FC, 0xA8);
const u32 gItemIconPalette_OldKey[] = INCBIN_U32("assets/graphics.bin", 0x1FD5A4, 0x28);

const u32 gItemIcon_AcroBike[] = INCBIN_U32("assets/graphics.bin", 0x1FD5CC, 0xFC);
const u32 gItemIconPalette_AcroBike[] = INCBIN_U32("assets/graphics.bin", 0x1FD6C8, 0x20);

const u32 gItemIcon_PokeblockCase[] = INCBIN_U32("assets/graphics.bin", 0x1FD6E8, 0xE8);
const u32 gItemIconPalette_PokeblockCase[] = INCBIN_U32("assets/graphics.bin", 0x1FD7D0, 0x28);

const u32 gItemIcon_Letter[] = INCBIN_U32("assets/graphics.bin", 0x1FD7F8, 0x80);
const u32 gItemIcon_EonTicket[] = INCBIN_U32("assets/graphics.bin", 0x1FD878, 0x9C);

const u32 gItemIconPalette_EonTicket[] = INCBIN_U32("assets/graphics.bin", 0x1FD914, 0x24);

const u32 gItemIcon_Orb[] = INCBIN_U32("assets/graphics.bin", 0x1FD938, 0xB8);
const u32 gItemIconPalette_RedOrb[] = INCBIN_U32("assets/graphics.bin", 0x1FD9F0, 0x1C);
const u32 gItemIconPalette_BlueOrb[] = INCBIN_U32("assets/graphics.bin", 0x1FDA0C, 0x1C);

const u32 gItemIcon_Scanner[] = INCBIN_U32("assets/graphics.bin", 0x1FDA28, 0xC8);
const u32 gItemIconPalette_Scanner[] = INCBIN_U32("assets/graphics.bin", 0x1FDAF0, 0x24);

const u32 gItemIcon_GoGoggles[] = INCBIN_U32("assets/graphics.bin", 0x1FDB14, 0xB4);
const u32 gItemIconPalette_GoGoggles[] = INCBIN_U32("assets/graphics.bin", 0x1FDBC8, 0x20);

const u32 gItemIcon_Meteorite[] = INCBIN_U32("assets/graphics.bin", 0x1FDBE8, 0xE0);
const u32 gItemIconPalette_Meteorite[] = INCBIN_U32("assets/graphics.bin", 0x1FDCC8, 0x20);

const u32 gItemIcon_Room1Key[] = INCBIN_U32("assets/graphics.bin", 0x1FDCE8, 0xB8);

const u32 gItemIcon_Room2Key[] = INCBIN_U32("assets/graphics.bin", 0x1FDDA0, 0xBC);

const u32 gItemIcon_Room4Key[] = INCBIN_U32("assets/graphics.bin", 0x1FDE5C, 0xC0);

const u32 gItemIcon_Room6Key[] = INCBIN_U32("assets/graphics.bin", 0x1FDF1C, 0xBC);

const u32 gItemIcon_StorageKey[] = INCBIN_U32("assets/graphics.bin", 0x1FDFD8, 0xA8);

const u32 gItemIcon_RootFossil[] = INCBIN_U32("assets/graphics.bin", 0x1FE080, 0x10C);
const u32 gItemIconPalette_HoennFossil[] = INCBIN_U32("assets/graphics.bin", 0x1FE18C, 0x28);
const u32 gItemIcon_ClawFossil[] = INCBIN_U32("assets/graphics.bin", 0x1FE1B4, 0xF0);

const u32 gItemIcon_DevonScope[] = INCBIN_U32("assets/graphics.bin", 0x1FE2A4, 0xBC);
const u32 gItemIconPalette_DevonScope[] = INCBIN_U32("assets/graphics.bin", 0x1FE360, 0x28);

// TMs/HMs

const u32 gItemIcon_TMHM[] = INCBIN_U32("assets/graphics.bin", 0x1FE388, 0xFC);

const u32 gItemIconPalette_FightingTMHM[] = INCBIN_U32("assets/graphics.bin", 0x1FE484, 0x28);
const u32 gItemIconPalette_DragonTMHM[]   = INCBIN_U32("assets/graphics.bin", 0x1FE4AC, 0x28);
const u32 gItemIconPalette_WaterTMHM[]    = INCBIN_U32("assets/graphics.bin", 0x1FE4D4, 0x28);
const u32 gItemIconPalette_PsychicTMHM[]  = INCBIN_U32("assets/graphics.bin", 0x1FE4FC, 0x28);
const u32 gItemIconPalette_NormalTMHM[]   = INCBIN_U32("assets/graphics.bin", 0x1FE524, 0x28);
const u32 gItemIconPalette_PoisonTMHM[]   = INCBIN_U32("assets/graphics.bin", 0x1FE54C, 0x28);
const u32 gItemIconPalette_IceTMHM[]      = INCBIN_U32("assets/graphics.bin", 0x1FE574, 0x28);
const u32 gItemIconPalette_GrassTMHM[]    = INCBIN_U32("assets/graphics.bin", 0x1FE59C, 0x28);
const u32 gItemIconPalette_FireTMHM[]     = INCBIN_U32("assets/graphics.bin", 0x1FE5C4, 0x28);
const u32 gItemIconPalette_DarkTMHM[]     = INCBIN_U32("assets/graphics.bin", 0x1FE5EC, 0x28);
const u32 gItemIconPalette_SteelTMHM[]    = INCBIN_U32("assets/graphics.bin", 0x1FE614, 0x28);
const u32 gItemIconPalette_ElectricTMHM[] = INCBIN_U32("assets/graphics.bin", 0x1FE63C, 0x28);
const u32 gItemIconPalette_GroundTMHM[]   = INCBIN_U32("assets/graphics.bin", 0x1FE664, 0x28);
const u32 gItemIconPalette_GhostTMHM[]    = INCBIN_U32("assets/graphics.bin", 0x1FE68C, 0x28);
const u32 gItemIconPalette_RockTMHM[]     = INCBIN_U32("assets/graphics.bin", 0x1FE6B4, 0x28);
const u32 gItemIconPalette_FlyingTMHM[]   = INCBIN_U32("assets/graphics.bin", 0x1FE6DC, 0x28);

// FireRed/LeafGreen key items

const u32 gItemIcon_OaksParcel[] = INCBIN_U32("assets/graphics.bin", 0x1FE704, 0xB8);
const u32 gItemIconPalette_OaksParcel[] = INCBIN_U32("assets/graphics.bin", 0x1FE7BC, 0x20);

const u32 gItemIcon_PokeFlute[] = INCBIN_U32("assets/graphics.bin", 0x1FE7DC, 0xC4);
const u32 gItemIconPalette_PokeFlute[] = INCBIN_U32("assets/graphics.bin", 0x1FE8A0, 0x28);

const u32 gItemIcon_SecretKey[] = INCBIN_U32("assets/graphics.bin", 0x1FE8C8, 0xCC);
const u32 gItemIconPalette_SecretKey[] = INCBIN_U32("assets/graphics.bin", 0x1FE994, 0x28);

const u32 gItemIcon_BikeVoucher[] = INCBIN_U32("assets/graphics.bin", 0x1FE9BC, 0xA0);
const u32 gItemIconPalette_BikeVoucher[] = INCBIN_U32("assets/graphics.bin", 0x1FEA5C, 0x20);

const u32 gItemIcon_GoldTeeth[] = INCBIN_U32("assets/graphics.bin", 0x1FEA7C, 0xEC);
const u32 gItemIconPalette_GoldTeeth[] = INCBIN_U32("assets/graphics.bin", 0x1FEB68, 0x24);

const u32 gItemIcon_OldAmber[] = INCBIN_U32("assets/graphics.bin", 0x1FEB8C, 0xE0);
const u32 gItemIconPalette_OldAmber[] = INCBIN_U32("assets/graphics.bin", 0x1FEC6C, 0x24);

const u32 gItemIcon_CardKey[] = INCBIN_U32("assets/graphics.bin", 0x1FEC90, 0xA8);
const u32 gItemIconPalette_CardKey[] = INCBIN_U32("assets/graphics.bin", 0x1FED38, 0x20);

const u32 gItemIcon_LiftKey[] = INCBIN_U32("assets/graphics.bin", 0x1FED58, 0xBC);
const u32 gItemIconPalette_Key[] = INCBIN_U32("assets/graphics.bin", 0x1FEE14, 0x20);

const u32 gItemIcon_HelixFossil[] = INCBIN_U32("assets/graphics.bin", 0x1FEE34, 0xF4);
const u32 gItemIconPalette_KantoFossil[] = INCBIN_U32("assets/graphics.bin", 0x1FEF28, 0x20);
const u32 gItemIcon_DomeFossil[] = INCBIN_U32("assets/graphics.bin", 0x1FEF48, 0xF0);

const u32 gItemIcon_SilphScope[] = INCBIN_U32("assets/graphics.bin", 0x1FF038, 0xD4);
const u32 gItemIconPalette_SilphScope[] = INCBIN_U32("assets/graphics.bin", 0x1FF10C, 0x24);

const u32 gItemIcon_Bicycle[] = INCBIN_U32("assets/graphics.bin", 0x1FF130, 0x104);
const u32 gItemIconPalette_Bicycle[] = INCBIN_U32("assets/graphics.bin", 0x1FF234, 0x20);

const u32 gItemIcon_TownMap[] = INCBIN_U32("assets/graphics.bin", 0x1FF254, 0xBC);
const u32 gItemIconPalette_TownMap[] = INCBIN_U32("assets/graphics.bin", 0x1FF310, 0x28);

const u32 gItemIcon_VSSeeker[] = INCBIN_U32("assets/graphics.bin", 0x1FF338, 0xC8);
const u32 gItemIconPalette_VSSeeker[] = INCBIN_U32("assets/graphics.bin", 0x1FF400, 0x20);

const u32 gItemIcon_FameChecker[] = INCBIN_U32("assets/graphics.bin", 0x1FF420, 0xB8);
const u32 gItemIconPalette_FameChecker[] = INCBIN_U32("assets/graphics.bin", 0x1FF4D8, 0x24);

const u32 gItemIcon_TMCase[] = INCBIN_U32("assets/graphics.bin", 0x1FF4FC, 0xC4);
const u32 gItemIconPalette_TMCase[] = INCBIN_U32("assets/graphics.bin", 0x1FF5C0, 0x28);

const u32 gItemIcon_BerryPouch[] = INCBIN_U32("assets/graphics.bin", 0x1FF5E8, 0x100);
const u32 gItemIconPalette_BerryPouch[] = INCBIN_U32("assets/graphics.bin", 0x1FF6E8, 0x28);

const u32 gItemIcon_TeachyTV[] = INCBIN_U32("assets/graphics.bin", 0x1FF710, 0xF8);
const u32 gItemIconPalette_TeachyTV[] = INCBIN_U32("assets/graphics.bin", 0x1FF808, 0x28);

const u32 gItemIcon_TriPass[] = INCBIN_U32("assets/graphics.bin", 0x1FF830, 0xA4);
const u32 gItemIconPalette_TriPass[] = INCBIN_U32("assets/graphics.bin", 0x1FF8D4, 0x20);

const u32 gItemIcon_RainbowPass[] = INCBIN_U32("assets/graphics.bin", 0x1FF8F4, 0xA8);
const u32 gItemIconPalette_RainbowPass[] = INCBIN_U32("assets/graphics.bin", 0x1FF99C, 0x28);

const u32 gItemIcon_Tea[] = INCBIN_U32("assets/graphics.bin", 0x1FF9C4, 0xC8);
const u32 gItemIconPalette_Tea[] = INCBIN_U32("assets/graphics.bin", 0x1FFA8C, 0x24);

const u32 gItemIcon_MysticTicket[] = INCBIN_U32("assets/graphics.bin", 0x1FFAB0, 0x98);
const u32 gItemIconPalette_MysticTicket[] = INCBIN_U32("assets/graphics.bin", 0x1FFB48, 0x20);

const u32 gItemIcon_AuroraTicket[] = INCBIN_U32("assets/graphics.bin", 0x1FFB68, 0x9C);
const u32 gItemIconPalette_AuroraTicket[] = INCBIN_U32("assets/graphics.bin", 0x1FFC04, 0x24);

const u32 gItemIcon_PowderJar[] = INCBIN_U32("assets/graphics.bin", 0x1FFC28, 0xA0);
const u32 gItemIconPalette_PowderJar[] = INCBIN_U32("assets/graphics.bin", 0x1FFCC8, 0x28);

const u32 gItemIconPalette_Ruby[] = INCBIN_U32("assets/graphics.bin", 0x1FFCF0, 0x28);
const u32 gItemIcon_Gem[] = INCBIN_U32("assets/graphics.bin", 0x1FFD18, 0xC8);
const u32 gItemIconPalette_Sapphire[] = INCBIN_U32("assets/graphics.bin", 0x1FFDE0, 0x28);
// ===== END src/data/graphics/items.h =====

const u32 gBattleAnimSpritePal_Shock3[] = INCBIN_U32("assets/graphics.bin", 0x1FFE08, 0x28);
const u32 gBattleAnimSpriteGfx_Shock3[] = INCBIN_U32("assets/graphics.bin", 0x1FFE30, 0x1E8);

const u32 gBattleAnimSpritePal_WhiteFeather[] = INCBIN_U32("assets/graphics.bin", 0x200018, 0x1C);
const u32 gBattleAnimSpriteGfx_WhiteFeather[] = INCBIN_U32("assets/graphics.bin", 0x200034, 0x128);

const u32 gBattleAnimSpritePal_Sparkle6[] = INCBIN_U32("assets/graphics.bin", 0x20015C, 0x18);
const u32 gBattleAnimSpriteGfx_Sparkle6[] = INCBIN_U32("assets/graphics.bin", 0x200174, 0x60);

const u32 gGhostPalette[] = INCBIN_U32("assets/graphics.bin", 0x2001D4, 0x24);
const u32 gGhostFrontPic[] = INCBIN_U32("assets/graphics.bin", 0x2001F8, 0x368);

// ===== BEGIN src/data/graphics/mail.h =====
const u16 gFile_graphics_mail_orange_palette_pal[] = INCBIN_U16("assets/graphics.bin", 0x200560, 0x20);
const u16 gFile_graphics_mail_harbor_palette_pal[] = INCBIN_U16("assets/graphics.bin", 0x200580, 0x20);
const u16 gFile_graphics_mail_glitter_palette_pal[] = INCBIN_U16("assets/graphics.bin", 0x2005A0, 0x20);
const u16 gFile_graphics_mail_mech_palette_pal[] = INCBIN_U16("assets/graphics.bin", 0x2005C0, 0x20);
const u16 gFile_graphics_mail_wood_palette_pal[] = INCBIN_U16("assets/graphics.bin", 0x2005E0, 0x20);
const u16 gFile_graphics_mail_wave_palette_pal[] = INCBIN_U16("assets/graphics.bin", 0x200600, 0x20);
const u16 gFile_graphics_mail_bead_palette_pal[] = INCBIN_U16("assets/graphics.bin", 0x200620, 0x20);
const u16 gFile_graphics_mail_shadow_palette_pal[] = INCBIN_U16("assets/graphics.bin", 0x200640, 0x20);
const u16 gFile_graphics_mail_tropic_palette_pal[] = INCBIN_U16("assets/graphics.bin", 0x200660, 0x20);
const u16 gFile_graphics_mail_dream_palette_pal[] = INCBIN_U16("assets/graphics.bin", 0x200680, 0x20);
const u16 gFile_graphics_mail_fab_palette_pal[] = INCBIN_U16("assets/graphics.bin", 0x2006A0, 0x20);
const u16 gFile_graphics_mail_retro_palette_pal[] = INCBIN_U16("assets/graphics.bin", 0x2006C0, 0x20);

const u32 gFile_graphics_mail_orange_tiles_sheet[] = INCBIN_U32("assets/graphics.bin", 0x2006E0, 0x1A0);
const u32 gFile_graphics_mail_harbor_tiles_sheet[] = INCBIN_U32("assets/graphics.bin", 0x200880, 0x13C);
const u32 gFile_graphics_mail_glitter_tiles_sheet[] = INCBIN_U32("assets/graphics.bin", 0x2009BC, 0x210);
const u32 gFile_graphics_mail_mech_tiles_sheet[] = INCBIN_U32("assets/graphics.bin", 0x200BCC, 0xD8);
const u32 gFile_graphics_mail_wood_tiles_sheet[] = INCBIN_U32("assets/graphics.bin", 0x200CA4, 0x1F8);
const u32 gFile_graphics_mail_wave_tiles_sheet[] = INCBIN_U32("assets/graphics.bin", 0x200E9C, 0x180);
const u32 gFile_graphics_mail_bead_tiles_sheet[] = INCBIN_U32("assets/graphics.bin", 0x20101C, 0xA8);
const u32 gFile_graphics_mail_shadow_tiles_sheet[] = INCBIN_U32("assets/graphics.bin", 0x2010C4, 0x190);
const u32 gFile_graphics_mail_tropic_tiles_sheet[] = INCBIN_U32("assets/graphics.bin", 0x201254, 0x140);
const u32 gFile_graphics_mail_dream_tiles_sheet[] = INCBIN_U32("assets/graphics.bin", 0x201394, 0x168);
const u32 gFile_graphics_mail_fab_tiles_sheet[] = INCBIN_U32("assets/graphics.bin", 0x2014FC, 0x150);
const u32 gFile_graphics_mail_retro_tiles_sheet[] = INCBIN_U32("assets/graphics.bin", 0x20164C, 0x2A0);

const u32 gFile_graphics_mail_orange_map_tilemap[] = INCBIN_U32("assets/graphics.bin", 0x2018EC, 0xD8);
const u32 gFile_graphics_mail_harbor_map_tilemap[] = INCBIN_U32("assets/graphics.bin", 0x2019C4, 0xE0);
const u32 gFile_graphics_mail_glitter_map_tilemap[] = INCBIN_U32("assets/graphics.bin", 0x201AA4, 0x10C);
const u32 gFile_graphics_mail_mech_map_tilemap[] = INCBIN_U32("assets/graphics.bin", 0x201BB0, 0xDC);
const u32 gFile_graphics_mail_wood_map_tilemap[] = INCBIN_U32("assets/graphics.bin", 0x201C8C, 0xF0);
const u32 gFile_graphics_mail_wave_map_tilemap[] = INCBIN_U32("assets/graphics.bin", 0x201D7C, 0xE0);
const u32 gFile_graphics_mail_bead_map_tilemap[] = INCBIN_U32("assets/graphics.bin", 0x201E5C, 0xE0);
const u32 gFile_graphics_mail_shadow_map_tilemap[] = INCBIN_U32("assets/graphics.bin", 0x201F3C, 0x10C);
const u32 gFile_graphics_mail_tropic_map_tilemap[] = INCBIN_U32("assets/graphics.bin", 0x202048, 0xF0);
const u32 gFile_graphics_mail_dream_map_tilemap[] = INCBIN_U32("assets/graphics.bin", 0x202138, 0xF8);
const u32 gFile_graphics_mail_fab_map_tilemap[] = INCBIN_U32("assets/graphics.bin", 0x202230, 0x118);
const u32 gFile_graphics_mail_retro_map_tilemap[] = INCBIN_U32("assets/graphics.bin", 0x202348, 0x114);
// ===== END src/data/graphics/mail.h =====

const u16 gMenuInfoElements1_Pal[] = INCBIN_U16("assets/graphics.bin", 0x20245C, 0x20);
const u16 gMenuInfoElements2_Pal[] = INCBIN_U16("assets/graphics.bin", 0x20247C, 0x20);
const u8 gMenuInfoElements_Gfx[] = INCBIN_U8("assets/graphics.bin", 0x20249C, 0x2000);

const u16 gMoveRelearner_Pal[] = INCBIN_U16("assets/graphics.bin", 0x20449C, 0x20);
const u32 gMoveRelearner_Gfx[] = INCBIN_U32("assets/graphics.bin", 0x2044BC, 0xC8);
const u32 gMoveRelearner_Tilemap[] = INCBIN_U32("assets/graphics.bin", 0x204584, 0x120);

const u16 gNamingScreenKeyboard_Pal[] = INCBIN_U16("assets/graphics.bin", 0x2046A4, 0x20);
const u16 gNamingScreenRival_Pal[]    = INCBIN_U16("assets/graphics.bin", 0x2046C4, 0x20);
const u16 gNamingScreenMenu_Pal[6][16] =
{
    INCBIN_U16("assets/graphics.bin", 0x2046E4, 0x20),
    INCBIN_U16("assets/graphics.bin", 0x204704, 0x20),
    INCBIN_U16("assets/graphics.bin", 0x204724, 0x20),
    INCBIN_U16("assets/graphics.bin", 0x204744, 0x20),
    INCBIN_U16("assets/graphics.bin", 0x204764, 0x20),
    INCBIN_U16("assets/graphics.bin", 0x204784, 0x20),
};

const u32 gNamingScreenMenu_Gfx[]                = INCBIN_U32("assets/graphics.bin", 0x2047A4, 0x1D8);
const u32 gNamingScreenBackground_Tilemap[]      = INCBIN_U32("assets/graphics.bin", 0x20497C, 0xDC);
const u32 gNamingScreenKeyboardUpper_Tilemap[]   = INCBIN_U32("assets/graphics.bin", 0x204A58, 0xC0);
const u32 gNamingScreenKeyboardLower_Tilemap[]   = INCBIN_U32("assets/graphics.bin", 0x204B18, 0xC0);
const u32 gNamingScreenKeyboardSymbols_Tilemap[] = INCBIN_U32("assets/graphics.bin", 0x204BD8, 0xC0);

const u32 gNamingScreenPageSwapFrame_Gfx[]  = INCBIN_U32("assets/graphics.bin", 0x204C98, 0x280);
const u32 gNamingScreenBackButton_Gfx[]     = INCBIN_U32("assets/graphics.bin", 0x204F18, 0x1E0);
const u32 gNamingScreenOKButton_Gfx[]       = INCBIN_U32("assets/graphics.bin", 0x2050F8, 0x1E0);
const u32 gNamingScreenPageSwapUpper_Gfx[]  = INCBIN_U32("assets/graphics.bin", 0x2052D8, 0xA0);
const u32 gNamingScreenPageSwapLower_Gfx[]  = INCBIN_U32("assets/graphics.bin", 0x205378, 0xA0);
const u32 gNamingScreenPageSwapOthers_Gfx[] = INCBIN_U32("assets/graphics.bin", 0x205418, 0xA0);
const u32 gNamingScreenCursor_Gfx[]         = INCBIN_U32("assets/graphics.bin", 0x2054B8, 0xA0);
const u32 gNamingScreenCursorSquished_Gfx[] = INCBIN_U32("assets/graphics.bin", 0x205558, 0xA0);
const u32 gNamingScreenCursorFilled_Gfx[]   = INCBIN_U32("assets/graphics.bin", 0x2055F8, 0xA0);
const u32 gNamingScreenPageSwapButton_Gfx[] = INCBIN_U32("assets/graphics.bin", 0x205698, 0x100);
const u32 gNamingScreenInputArrow_Gfx[]     = INCBIN_U32("assets/graphics.bin", 0x205798, 0x20);
const u32 gNamingScreenUnderscore_Gfx[]     = INCBIN_U32("assets/graphics.bin", 0x2057B8, 0x20);

const u8 gTMCaseHM_Gfx[] = INCBIN_U8("assets/graphics.bin", 0x2057D8, 0x80);

const u16 gKantoTrainerCardBlue_Pal[] = INCBIN_U16("assets/graphics.bin", 0x205858, 0x60);
const u32 gKantoTrainerCard_Gfx[] = INCBIN_U32("assets/graphics.bin", 0x2058B8, 0x674);
const u16 gHoennTrainerCardGreen_Pal[] = INCBIN_U16("assets/graphics.bin", 0x205F2C, 0x60);
const u32 gHoennTrainerCard_Gfx[] = INCBIN_U32("assets/graphics.bin", 0x205F8C, 0x4C0);

const u16 gEasyChatWindow_Pal[] = INCBIN_U16("assets/graphics.bin", 0x20644C, 0x20);
const u32 gEasyChatWindow_Gfx[] = INCBIN_U32("assets/graphics.bin", 0x20646C, 0xC8);
const u32 gEasyChatWindow_Tilemap[] = INCBIN_U32("assets/graphics.bin", 0x206534, 0xB0);

const u16 gEasyChatButtonWindow_Pal[] = INCBIN_U16("assets/graphics.bin", 0x2065E4, 0x20);
const u32 gEasyChatButtonWindow_Gfx[] = INCBIN_U32("assets/graphics.bin", 0x206604, 0x224);
const u32 gEasyChatMode_Gfx[] = INCBIN_U32("assets/graphics.bin", 0x206828, 0x2F8);

const u32 gSummaryScreen_Bg_Gfx[] = INCBIN_U32("assets/graphics.bin", 0x206B20, 0xEB0);
const u32 gSummaryScreen_Bg_Pal[] = INCBIN_U32("assets/graphics.bin", 0x2079D0, 0xE0);
const u32 gSummaryScreen_ExpBar_Gfx[] = INCBIN_U32("assets/graphics.bin", 0x207AB0, 0xC8);
const u32 gSummaryScreen_HpBar_Gfx[] = INCBIN_U32("assets/graphics.bin", 0x207B78, 0xC0);
const u16 gSummaryScreen_HpExpBar_Pal[] = INCBIN_U16("assets/graphics.bin", 0x207C38, 0x20); // hp bar uses this too
const u32 gSummaryScreen_PageInfo_Tilemap[] = INCBIN_U32("assets/graphics.bin", 0x207C58, 0x1B8);
const u32 gSummaryScreen_PageSkills_Tilemap[] = INCBIN_U32("assets/graphics.bin", 0x207E10, 0x200);
const u32 gSummaryScreen_PageMoves_Tilemap[] = INCBIN_U32("assets/graphics.bin", 0x208010, 0x14C);
const u32 gSummaryScreen_PageMovesInfo_Tilemap[] = INCBIN_U32("assets/graphics.bin", 0x20815C, 0x130);
const u32 gSummaryScreen_PageEgg_Tilemap[] = INCBIN_U32("assets/graphics.bin", 0x20828C, 0x13C);

const u16 gUnusedRedPalette[] = INCBIN_U16("assets/graphics.bin", 0x2083C8, 0x20);

const u32 gEasyChatRectangleCursor_Gfx[] = INCBIN_U32("assets/graphics.bin", 0x2083E8, 0x200);
const u16 gSummaryScreen_StatusAilmentIcon_Pal[] = INCBIN_U16("assets/graphics.bin", 0x2085E8, 0x20);
const u32 gSummaryScreen_StatusAilmentIcon_Gfx[] = INCBIN_U32("assets/graphics.bin", 0x208608, 0x204);

const u16 gDexScreen_TopMenuIconPals_AtoZ[] = INCBIN_U16("assets/graphics.bin", 0x20880C, 0x20);
const u32 gDexScreen_TopMenuIconTiles_AtoZ[] = INCBIN_U32("assets/graphics.bin", 0x20882C, 0x26C);

const u16 gPokeStoragePartyMenu_Pal[] = INCBIN_U16("assets/graphics.bin", 0x208A98, 0x20);
const u16 gPokeStorageInterface_Pal[] = INCBIN_U16("assets/graphics.bin", 0x208AB8, 0x20);
const u16 gPokeStorageInterface_NoDisplayMon_Pal[] = INCBIN_U16("assets/graphics.bin", 0x208AD8, 0x20);
const u32 gPokeStorageMenu_Gfx[] = INCBIN_U32("assets/graphics.bin", 0x208AF8, 0x6B4);
const u32 gPokeStoragePartyMenu_Tilemap[] = INCBIN_U32("assets/graphics.bin", 0x2091AC, 0xB0);
const u16 gMonMarkingsMenu_Pal[] = INCBIN_U16("assets/graphics.bin", 0x20925C, 0x20);
const u16 gMonMarkingsMenu_Gfx[] = INCBIN_U16("assets/graphics.bin", 0x20927C, 0x320);

const u16 gTradeMenu_Pal[] = INCBIN_U16("assets/graphics.bin", 0x20959C, 0x60);
const u16 gTradeCursor_Pal[] = INCBIN_U16("assets/graphics.bin", 0x2095FC, 0x20);
const u16 gTradeMenu_Gfx[] = INCBIN_U16("assets/graphics.bin", 0x20961C, 0x1280);
const u16 gTradeCursor_Gfx[] = INCBIN_U16("assets/graphics.bin", 0x20A89C, 0x800);
const u16 gTradeUnused_Tilemap[] = INCBIN_U16("assets/graphics.bin", 0x20B09C, 0x20);
const u16 gTradeMenu_Tilemap[] = INCBIN_U16("assets/graphics.bin", 0x20B0BC, 0x800);
const u16 gTradeMenuMonBox_Tilemap[] = INCBIN_U16("assets/graphics.bin", 0x20B8BC, 0x24);

const u16 gFameCheckerBgPals[][16] = INCBIN_U16("assets/graphics.bin", 0x20B8E0, 0x40);
const u16 gFameCheckerBgTiles[] = INCBIN_U16("assets/graphics.bin", 0x20B920, 0x14A0);
const u16 gFameCheckerBg3Tilemap[] = INCBIN_U16("assets/graphics.bin", 0x20CDC0, 0x800);
const u16 gFameCheckerBg2Tilemap[] = INCBIN_U16("assets/graphics.bin", 0x20D5C0, 0x800);

const u16 gUnionRoomChat_Bg_Pal[] = INCBIN_U16("assets/graphics.bin", 0x20DDC0, 0x20);
const u32 gUnionRoomChat_Bg_Gfx[] = INCBIN_U32("assets/graphics.bin", 0x20DDE0, 0x238);
const u32 gUnionRoomChat_Bg_Tilemap[] = INCBIN_U32("assets/graphics.bin", 0x20E018, 0xF8);
const u32 gUnionRoomChat_Icons_Gfx[] = INCBIN_U32("assets/graphics.bin", 0x20E110, 0x118);

const u16 gTilesetPalettes_General[][16] =
{
    INCBIN_U16("assets/graphics.bin", 0x20E228, 0x20),
    INCBIN_U16("assets/graphics.bin", 0x20E248, 0x20),
    INCBIN_U16("assets/graphics.bin", 0x20E268, 0x20),
    INCBIN_U16("assets/graphics.bin", 0x20E288, 0x20),
    INCBIN_U16("assets/graphics.bin", 0x20E2A8, 0x20),
    INCBIN_U16("assets/graphics.bin", 0x20E2C8, 0x20),
    INCBIN_U16("assets/graphics.bin", 0x20E2E8, 0x20),
    INCBIN_U16("assets/graphics.bin", 0x20E308, 0x20),
    INCBIN_U16("assets/graphics.bin", 0x20E328, 0x20),
    INCBIN_U16("assets/graphics.bin", 0x20E348, 0x20),
    INCBIN_U16("assets/graphics.bin", 0x20E368, 0x20),
    INCBIN_U16("assets/graphics.bin", 0x20E388, 0x20),
    INCBIN_U16("assets/graphics.bin", 0x20E3A8, 0x20),
    INCBIN_U16("assets/graphics.bin", 0x20E3C8, 0x20),
    INCBIN_U16("assets/graphics.bin", 0x20E3E8, 0x20),
    INCBIN_U16("assets/graphics.bin", 0x20E408, 0x20),
};

const u32 gTilesetTiles_General[] = INCBIN_U32("assets/graphics.bin", 0x20E428, 0x28D4);

const u8 gBerryFixGameboy_Pal[] = INCBIN_U8("assets/graphics.bin", 0x210CFC, 0x40);
const u8 gBerryFixGameboy_Gfx[] = INCBIN_U8("assets/graphics.bin", 0x210D3C, 0xC3C);
const u8 gBerryFixGameboy_Tilemap[] = INCBIN_U8("assets/graphics.bin", 0x211978, 0x34C);
const u8 gBerryFixGameboyLogo_Pal[] = INCBIN_U8("assets/graphics.bin", 0x211CC4, 0x60);
const u8 gBerryFixGameboyLogo_Gfx[] = INCBIN_U8("assets/graphics.bin", 0x211D24, 0xA64);
const u8 gBerryFixGameboyLogo_Tilemap[] = INCBIN_U8("assets/graphics.bin", 0x212788, 0x300);
const u8 gBerryFixGbaTransfer_Pal[] = INCBIN_U8("assets/graphics.bin", 0x212A88, 0x40);
const u8 gBerryFixGbaTransfer_Gfx[] = INCBIN_U8("assets/graphics.bin", 0x212AC8, 0xC20);
const u8 gBerryFixGbaTransfer_Tilemap[] = INCBIN_U8("assets/graphics.bin", 0x2136E8, 0x2B8);
const u8 gBerryFixGbaTransferHighlight_Pal[] = INCBIN_U8("assets/graphics.bin", 0x2139A0, 0x40);
const u8 gBerryFixGbaTransferHighlight_Gfx[] = INCBIN_U8("assets/graphics.bin", 0x2139E0, 0xDF8);
const u8 gBerryFixGbaTransferHighlight_Tilemap[] = INCBIN_U8("assets/graphics.bin", 0x2147D8, 0x2B0);
const u8 gBerryFixGbaTransferError_Pal[] = INCBIN_U8("assets/graphics.bin", 0x214A88, 0x40);
const u8 gBerryFixGbaTransferError_Gfx[] = INCBIN_U8("assets/graphics.bin", 0x214AC8, 0x8C0);
const u8 gBerryFixGbaTransferError_Tilemap[] = INCBIN_U8("assets/graphics.bin", 0x215388, 0x238);
const u8 gBerryFixWindow_Pal[] = INCBIN_U8("assets/graphics.bin", 0x2155C0, 0x40);
const u8 gBerryFixWindow_Gfx[] = INCBIN_U8("assets/graphics.bin", 0x215600, 0x648);
const u8 gBerryFixWindow_Tilemap[] = INCBIN_U8("assets/graphics.bin", 0x215C48, 0x26C);

const u16 gTilesetPalettes_GenericBuilding1[][16] =
{
    INCBIN_U16("assets/graphics.bin", 0x215EB4, 0x20),
    INCBIN_U16("assets/graphics.bin", 0x215ED4, 0x20),
    INCBIN_U16("assets/graphics.bin", 0x215EF4, 0x20),
    INCBIN_U16("assets/graphics.bin", 0x215F14, 0x20),
    INCBIN_U16("assets/graphics.bin", 0x215F34, 0x20),
    INCBIN_U16("assets/graphics.bin", 0x215F54, 0x20),
    INCBIN_U16("assets/graphics.bin", 0x215F74, 0x20),
    INCBIN_U16("assets/graphics.bin", 0x215F94, 0x20),
    INCBIN_U16("assets/graphics.bin", 0x215FB4, 0x20),
    INCBIN_U16("assets/graphics.bin", 0x215FD4, 0x20),
    INCBIN_U16("assets/graphics.bin", 0x215FF4, 0x20),
    INCBIN_U16("assets/graphics.bin", 0x216014, 0x20),
    INCBIN_U16("assets/graphics.bin", 0x216034, 0x20),
    INCBIN_U16("assets/graphics.bin", 0x216054, 0x20),
    INCBIN_U16("assets/graphics.bin", 0x216074, 0x20),
    INCBIN_U16("assets/graphics.bin", 0x216094, 0x20),
};

const u32 gTilesetTiles_GenericBuilding1[] = INCBIN_U32("assets/graphics.bin", 0x2160B4, 0x394);

const u16 gTilesetPalettes_DepartmentStore[][16] =
{
    INCBIN_U16("assets/graphics.bin", 0x216448, 0x20),
    INCBIN_U16("assets/graphics.bin", 0x216468, 0x20),
    INCBIN_U16("assets/graphics.bin", 0x216488, 0x20),
    INCBIN_U16("assets/graphics.bin", 0x2164A8, 0x20),
    INCBIN_U16("assets/graphics.bin", 0x2164C8, 0x20),
    INCBIN_U16("assets/graphics.bin", 0x2164E8, 0x20),
    INCBIN_U16("assets/graphics.bin", 0x216508, 0x20),
    INCBIN_U16("assets/graphics.bin", 0x216528, 0x20),
    INCBIN_U16("assets/graphics.bin", 0x216548, 0x20),
    INCBIN_U16("assets/graphics.bin", 0x216568, 0x20),
    INCBIN_U16("assets/graphics.bin", 0x216588, 0x20),
    INCBIN_U16("assets/graphics.bin", 0x2165A8, 0x20),
    INCBIN_U16("assets/graphics.bin", 0x2165C8, 0x20),
    INCBIN_U16("assets/graphics.bin", 0x2165E8, 0x20),
    INCBIN_U16("assets/graphics.bin", 0x216608, 0x20),
    INCBIN_U16("assets/graphics.bin", 0x216628, 0x20),
};

const u32 gTilesetTiles_DepartmentStore[] = INCBIN_U32("assets/graphics.bin", 0x216648, 0xA68);

const u16 gUnionRoomChat_Panel_Pal[] = INCBIN_U16("assets/graphics.bin", 0x2170B0, 0x20);
const u32 gUnionRoomChat_Panel_Gfx[] = INCBIN_U32("assets/graphics.bin", 0x2170D0, 0x5C);
const u32 gUnionRoomChat_Panel_Tilemap[] = INCBIN_U32("assets/graphics.bin", 0x21712C, 0xAC);

const u16 gCreditsMonPokeball_Pals[][16] =
{
    INCBIN_U16("assets/graphics.bin", 0x2171D8, 0x20),
    INCBIN_U16("assets/graphics.bin", 0x2171F8, 0x20),
    INCBIN_U16("assets/graphics.bin", 0x217218, 0x20),
    INCBIN_U16("assets/graphics.bin", 0x217238, 0x20),
};

const u32 gCreditsMonPokeball_Tiles[] = INCBIN_U32("assets/graphics.bin", 0x217258, 0x774);
const u32 gCreditsMonPokeball_Tilemap[] = INCBIN_U32("assets/graphics.bin", 0x2179CC, 0x3B8);

#ifdef FIRERED
const u16 gGraphics_TitleScreen_GameTitleLogoPals[] = INCBIN_U16("assets/graphics.bin", 0x217D84, 0x200);
const u8 gGraphics_TitleScreen_GameTitleLogoTiles[] = INCBIN_U8("assets/graphics.bin", 0x217F84, 0x1ACC);
const u8 gGraphics_TitleScreen_GameTitleLogoMap[] = INCBIN_U8("assets/graphics.bin", 0x219A50, 0x258);
const u16 gGraphics_TitleScreen_BoxArtMonPals[] = INCBIN_U16("assets/graphics.bin", 0x219CA8, 0x20);
const u8 gGraphics_TitleScreen_BoxArtMonTiles[] = INCBIN_U8("assets/graphics.bin", 0x219CC8, 0x8DC);
const u8 gGraphics_TitleScreen_BoxArtMonMap[] = INCBIN_U8("assets/graphics.bin", 0x21A5A4, 0x1B0);
const u16 gGraphics_TitleScreen_BackgroundPals[] = INCBIN_U16("assets/graphics.bin", 0x21A754, 0x20);
const u8 gGraphics_TitleScreen_CopyrightPressStartTiles[] = INCBIN_U8("assets/graphics.bin", 0x21A774, 0x2C0);
const u8 gGraphics_TitleScreen_CopyrightPressStartMap[] = INCBIN_U8("assets/graphics.bin", 0x21AA34, 0x114);
const u16 gTitleScreen_Slash_Pal[] = INCBIN_U16("assets/graphics.bin", 0x21AB48, 0x20);
#endif

#ifdef LEAFGREEN
const u16 gGraphics_TitleScreen_GameTitleLogoPals[] = INCBIN_U16("assets/graphics.bin", 0x21AB68, 0x200);
const u8 gGraphics_TitleScreen_GameTitleLogoTiles[] = INCBIN_U8("assets/graphics.bin", 0x21AD68, 0x1BC4);
const u8 gGraphics_TitleScreen_GameTitleLogoMap[] = INCBIN_U8("assets/graphics.bin", 0x21C92C, 0x260);
const u16 gGraphics_TitleScreen_BoxArtMonPals[] = INCBIN_U16("assets/graphics.bin", 0x21CB8C, 0x20);
const u8 gGraphics_TitleScreen_BoxArtMonTiles[] = INCBIN_U8("assets/graphics.bin", 0x21CBAC, 0xA64);
const u8 gGraphics_TitleScreen_BoxArtMonMap[] = INCBIN_U8("assets/graphics.bin", 0x21D610, 0x19C);
const u16 gGraphics_TitleScreen_BackgroundPals[] = INCBIN_U16("assets/graphics.bin", 0x21D7AC, 0x20);
const u8 gGraphics_TitleScreen_CopyrightPressStartTiles[] = INCBIN_U8("assets/graphics.bin", 0x21A774, 0x2C0);
const u8 gGraphics_TitleScreen_CopyrightPressStartMap[] = INCBIN_U8("assets/graphics.bin", 0x21AA34, 0x114);
const u16 gTitleScreen_Slash_Pal[] = INCBIN_U16("assets/graphics.bin", 0x21D7CC, 0x20);
#endif

const u32 gTitleScreen_BlankSprite_Tiles[] = INCBIN_U32("assets/graphics.bin", 0x21D7EC, 0x80);

const u16 gCreditsCopyright_Pal[] = INCBIN_U16("assets/graphics.bin", 0x21D86C, 0x20);
const u8 gCreditsCopyright_Tiles[] = INCBIN_U8("assets/graphics.bin", 0x21D88C, 0x3B8);
const u8 gCreditsCopyright_Tilemap[] = INCBIN_U8("assets/graphics.bin", 0x21DC44, 0x100);

const u32 gTradeGba_Pal[] = INCBIN_U32("assets/graphics.bin", 0x21DD44, 0x20);
const u32 gTradeGba2_Pal[] = INCBIN_U32("assets/graphics.bin", 0x21DD64, 0x60);
const u32 gTradeGba_Gfx[] = INCBIN_U32("assets/graphics.bin", 0x21DDC4, 0x1400);

const u16 sEmptyPal[16] = {0};

const u16 gBerryCrush_Crusher_Pal[] = INCBIN_U16("assets/graphics.bin", 0x21F1C4, 0x120);
const u32 gBerryCrush_Crusher_Gfx[] = INCBIN_U32("assets/graphics.bin", 0x21F2E4, 0xB1C);
const u32 gBerryCrush_TextWindows_Tilemap[] = INCBIN_U32("assets/graphics.bin", 0x21FE00, 0x44);
