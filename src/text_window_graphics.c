#include "global.h"
#include "text_window_graphics.h"

const u16 gSignpostWindow_Gfx[] = INCBIN_U16("assets/graphics.bin", 0x2A7AA0, 0x260);

static const u16 sUserFrame_Type1_Gfx[] = INCBIN_U16("assets/graphics.bin", 0x2A7D00, 0x120);
static const u16 sUserFrame_Type2_Gfx[] = INCBIN_U16("assets/graphics.bin", 0x2A7E20, 0x120);
static const u16 sUserFrame_Empty1[16] = {0};
static const u16 sUserFrame_Type3_Gfx[] = INCBIN_U16("assets/graphics.bin", 0x2A7F40, 0x120);
static const u16 sUserFrame_Type4_Gfx[] = INCBIN_U16("assets/graphics.bin", 0x2A8060, 0x120);
static const u16 sUserFrame_Type5_Gfx[] = INCBIN_U16("assets/graphics.bin", 0x2A8180, 0x120);
static const u16 sUserFrame_Type6_Gfx[] = INCBIN_U16("assets/graphics.bin", 0x2A82A0, 0x120);
static const u16 sUserFrame_Type7_Gfx[] = INCBIN_U16("assets/graphics.bin", 0x2A83C0, 0x120);
static const u16 sUserFrame_Type8_Gfx[] = INCBIN_U16("assets/graphics.bin", 0x2A84E0, 0x120);
static const u16 sUserFrame_Empty2[16] = {0};
static const u16 sUserFrame_Type9_Gfx[] = INCBIN_U16("assets/graphics.bin", 0x2A8600, 0x120);
static const u16 sUserFrame_Type10_Gfx[] = INCBIN_U16("assets/graphics.bin", 0x2A8720, 0x120);
static const u16 sUserFrame_Empty3[16] = {0};

static const u16 sUserFrame_Type1_Pal[] = INCBIN_U16("assets/graphics.bin", 0x2A8840, 0x20);
static const u16 sUserFrame_Type2_Pal[] = INCBIN_U16("assets/graphics.bin", 0x2A8860, 0x20);
static const u16 sUserFrame_Type3_Pal[] = INCBIN_U16("assets/graphics.bin", 0x2A8880, 0x20);
static const u16 sUserFrame_Type4_Pal[] = INCBIN_U16("assets/graphics.bin", 0x2A88A0, 0x20);
static const u16 sUserFrame_Type5_Pal[] = INCBIN_U16("assets/graphics.bin", 0x2A88C0, 0x20);
static const u16 sUserFrame_Type6_Pal[] = INCBIN_U16("assets/graphics.bin", 0x2A88E0, 0x20);
static const u16 sUserFrame_Type7_Pal[] = INCBIN_U16("assets/graphics.bin", 0x2A8900, 0x20);
static const u16 sUserFrame_Type8_Pal[] = INCBIN_U16("assets/graphics.bin", 0x2A8920, 0x20);
static const u16 sUserFrame_Type9_Pal[] = INCBIN_U16("assets/graphics.bin", 0x2A8940, 0x20);
static const u16 sUserFrame_Type10_Pal[] = INCBIN_U16("assets/graphics.bin", 0x2A8960, 0x20);

const u16 gStdTextWindow_Gfx[] = INCBIN_U16("assets/graphics.bin", 0x2A8980, 0x120);
const u16 gQuestLogWindow_Gfx[] = INCBIN_U16("assets/graphics.bin", 0x2A8AA0, 0x280);

const u16 gTextWindowPalettes[][16] = {
    INCBIN_U16("assets/graphics.bin", 0x2A8D20, 0x20),
    INCBIN_U16("assets/graphics.bin", 0x2A8D40, 0x20),
    INCBIN_U16("assets/graphics.bin", 0x2A8D60, 0x20),
    INCBIN_U16("assets/graphics.bin", 0x2A8D80, 0x20),
    INCBIN_U16("assets/graphics.bin", 0x2A8DA0, 0x20)
};

const struct TextWindowGraphics gUserFrames[] = {
    {sUserFrame_Type1_Gfx,  sUserFrame_Type1_Pal},
    {sUserFrame_Type2_Gfx,  sUserFrame_Type2_Pal},
    {sUserFrame_Type3_Gfx,  sUserFrame_Type3_Pal},
    {sUserFrame_Type4_Gfx,  sUserFrame_Type4_Pal},
    {sUserFrame_Type5_Gfx,  sUserFrame_Type5_Pal},
    {sUserFrame_Type6_Gfx,  sUserFrame_Type6_Pal},
    {sUserFrame_Type7_Gfx,  sUserFrame_Type7_Pal},
    {sUserFrame_Type8_Gfx,  sUserFrame_Type8_Pal},
    {sUserFrame_Type9_Gfx,  sUserFrame_Type9_Pal},
    {sUserFrame_Type10_Gfx, sUserFrame_Type10_Pal},
};

const struct TextWindowGraphics *GetUserWindowGraphics(u8 idx)
{
#ifdef BUGFIX
    if (idx >= ARRAY_COUNT(gUserFrames))
#else
    if (idx >= 20) // Using the RSE number of elements
#endif
        return &gUserFrames[0];
    else
        return &gUserFrames[idx];
}
