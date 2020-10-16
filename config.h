/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 4;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=16", "-misc-font awesome 5 brands regular-medium-r-normal--17-120-100-100-p-0-iso10646-1", "-misc-font awesome 5 free regular-medium-r-normal--17-120-100-100-p-0-iso10646-1", "-misc-font awesome 5 free solid-black-r-normal--17-120-100-100-p-0-iso10646-1"};
static const char dmenufont[]       = "monospace:size=10";
static const char focussed[]        = "#0000ff";
static const char col_gray1[]       = "#2c2c2c";
//static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  focussed  },
	[SchemeStatus]  = { "#F8F8F2", col_gray1,  "#000000"  }, // Statusbar right {text,background,not used but cannot be empty}
	[SchemeTagsSel]  = {  "#F8F8F2", col_cyan,  "#000000"  }, // Tagbar left selected {text,background,not used but cannot be empty}
	[SchemeTagsNorm]  = {   "#F8F8F2", col_gray1,  "#000000"  }, // Tagbar left unselected {text,background,not used but cannot be empty}
    [SchemeInfoSel]  = {    "#F8F8F2", col_cyan,  "#000000"  }, // infobar middle  selected {text,background,not used but cannot be empty}
    [SchemeInfoNorm]  = {     "#F8F8F2", col_gray1,  "#000000"  }, // infobar middle  unselected {text,background,not used but cannot be empty}
};

/* tagging */
#define MAX_TAGLEN 16
static char tags[][MAX_TAGLEN] = { "1", "2", "3:web", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class                             instance  title           tags mask  iscentered  isfloating  isterminal  noswallow  monitor */
	{ "Gimp",                            NULL,     NULL,           0,         0,          1,          0,           0,        -1 },
	{ "jetbrains-phpstorm",              NULL,     NULL,           0,         0,          1,          0,           1,        -1 },
	{ "Thunderbird",                     NULL,     NULL,           1 << 8,    0,          0,          0,          -1,         0 },
	{ "whatsapp-nativefier-d40211",      NULL,     NULL,           1 << 7,    0,          0,          0,          -1,         0 },
	{ "TelegramDesktop",                 NULL,     NULL,           1 << 7,    0,          0,          0,          -1,         0 },
	{ "Signal",                          NULL,     NULL,           1 << 7,    0,          0,          0,          -1,         0 },
	{ "threemawebqt",                    NULL,     NULL,           1 << 7,    0,          0,          0,          -1,         0 },
	{ "firefox",                         NULL,     NULL,           1 << 2,    0,          0,          0,          -1,        -1 },
	{ "Tor Browser",                     NULL,     NULL,           1 << 2,    0,          0,          0,          -1,        -1 },
	{ "Bitwarden",                       NULL,     NULL,           1 << 6,    0,          0,          0,          -1,         0 },
	{ "KeePassXC",                       NULL,     NULL,           1 << 6,    0,          0,          0,          -1,         0 },
	{ "Alacritty",                       NULL,     NULL,           0,         0,          0,          1,          -1,        -1 },
	{ "zoom",                            NULL,     NULL,           0,         0,          1,          0,          -1,        -1 },
	{ "zoom",                            NULL,     "as_toolbar",   0,         1,          1,          0,          -1,        -1 },
	{ "jetbrains-studio",                NULL,     NULL,           0,         0,          0,          0,          -1,        -1 },
    { NULL,                              NULL,     "ranger",       0,         0,          0,          0,           1,        -1 },
	{ NULL,                              NULL,     "calc",         0,         0,          1,          0,          -1,        -1 },
	{ NULL,                              NULL,     "mpvfloat",     0,         0,          1,          0,          -1,        -1 },
	{ NULL,                              NULL,     "Event Tester", 0,         0,          1,          0,           1,        -1 }, /* xev */
};

int warpactive = 1;

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int attachdirection = 2;    /* 0 default, 1 above, 2 aside, 3 below, 4 bottom, 5 top */

#include "fibonacci.c"
#include "gaplessgrid.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
 	{ "[\\]",     dwindle },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
 	{ "[@]",      spiral },
	{ "[]=",      tile },    /* first entry is default */
 	{ "|M|",      centeredmaster },
 	{ ">M>",      centeredfloatingmaster },
    { "###",      gaplessgrid },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
#define HOLDKEY 0xffeb // replace 0 with the keysym to activate holdbar

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "alacritty", NULL };

#include "movestack.c"
#include "focusurgent.c"
static Key keys[] = {
	/* modifier                     key        function        argument */
    { MODKEY|ControlMask,           XK_t,      spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
    /* { MODKEY,                       XK_Tab,    view,           {0} }, */
	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY|ShiftMask,             XK_t,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY|ShiftMask,             XK_u,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_r,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY|ShiftMask,             XK_r,      setlayout,      {.v = &layouts[0]} },
 	{ MODKEY,                       XK_z,      setlayout,      {.v = &layouts[5]} },
 	{ MODKEY|ShiftMask,             XK_z,      setlayout,      {.v = &layouts[6]} },
    { MODKEY,                       XK_g,      setlayout,      {.v = &layouts[7]} },
	{ MODKEY,                       XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_m,      nametag,        {0} },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
    { MODKEY|ShiftMask,             XK_c,      quit,           {1} },
	{ MODKEY|ControlMask|ShiftMask, XK_c,      quit,           {0} },
 	{ MODKEY,                       XK_u,      focusurgent,    {0} },
 	{ MODKEY,                       XK_w,      togglewarp,         },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

/* signal definitions */
/* signum must be greater than 0 */
/* trigger signals using `xsetroot -name "fsignal:<signum>"` */
static Signal signals[] = {
	/* signum       function        argument  */
	{ 1,            setlayout,      {.v = &layouts[0]} },
	{ 2,            setlayout,      {.v = &layouts[1]} },
	{ 3,            setlayout,      {.v = &layouts[2]} },
	{ 4,            setlayout,      {.v = &layouts[3]} },
	{ 5,            setlayout,      {.v = &layouts[4]} },
	{ 6,            setlayout,      {.v = &layouts[5]} },
	{ 7,            setlayout,      {.v = &layouts[6]} },
};
